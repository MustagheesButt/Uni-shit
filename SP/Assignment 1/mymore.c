#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/termios.h>
#include <sys/ioctl.h>
#include <errno.h>

#define MAX_LINE_LEN 512

/* Implements core functionality of more util */
void mymore(FILE* fileptr);

/* Implements pattern search functionality */
int search(FILE* fileptr, char* search_str);

/* Helper function to get number of lines the shell can print */
int get_lines();

/* Helper function to get number of columns the shell can print */
int get_cols();

/* Helper function to get size of a file */
int get_filesize(FILE* fileptr);

int main(int argc, char** argv)
{
    if (argc == 1)
    {
        mymore(stdin);
    }
    else if (strcmp(argv[1], "--help") == 0)
    {
        printf("Usage:\n\t ./mymore <file 1> <file 2> ... <file N>\n");
        return 0;
    }
    
    FILE* infile;

    for (int i = 1; i < argc; i++)
    {
        infile = fopen(argv[i], "r");
    
        if (infile == NULL)
        {
            printf("\n%.*s\n", 27 + (int)strlen(argv[i]), "=============================================");
            printf("Could not open the file \"%s\".\n", argv[i]);
            printf("%.*s\n", 27 + (int)strlen(argv[i]), "=============================================");
            continue;
        }
        
        // display the file contents
        mymore(infile);
        
        fclose(infile);
    }
    
    return 0;
}

void mymore(FILE* fileptr)
{
    char line[MAX_LINE_LEN];
    int lines_printed = 0;

    int total_data = get_filesize(fileptr);
    int data_printed = 0;
    int printed_something = 0;

    FILE* fp_tty = fopen("/dev/tty", "r");
    
    // non-canonical + non-echo mode
    struct termios original_settings;
    struct termios new_settings;
    int result = tcgetattr(fileno(fp_tty), &original_settings);
    new_settings = original_settings;
    
    new_settings.c_lflag &= ~ICANON;
    new_settings.c_lflag &= ~ECHO;
    
    if (tcsetattr(fileno(fp_tty), TCSANOW, &new_settings) != 0)
    {
        perror("Could not change terminal props");
    }

    while (1)
    {
        // actual print operation
        while (lines_printed < (get_lines() - 1) && fgets(line, get_cols(), fileptr))
        {
            fputs(line, stdout);
            data_printed += strlen(line);
            lines_printed += 1;
            printed_something = 1;
        }
        
        if (feof(fileptr))
        {
            printf("\n");
            break;
        }
        
        // print status
        if (printed_something)
            printf("\033[7m --more--(%d %%) \033[m", (int)((float)data_printed/total_data * 100));
        
        // user input
        char choice = getc(fp_tty);
        
        // move cursor left no. of cols times, to erase printed status
        printf("\033[%dD\033[K", get_cols());

        // now process user input
        if (choice == 'q')
        {
            break;
        }
        else if (choice == '\n')
        {
            lines_printed -= 1;
        }
        else if (choice == ' ')
        {
            lines_printed = 0;
        }
        else if (choice == '/')
        {
            int c;
            int length = 0;
            char str[100];

            putchar('/');
            while ((c = getc(fp_tty)) != '\n')
            {
                str[length++] = c;
                putchar(c);
            }
            str[length] = '\0';

            if (search(fileptr, str) == -1)
            {
                printf("\033[%dD", length + 1); // remove the printed pattern
                printf("\033[7m Pattern Not Found \033[m");
                printed_something = 0;
            }
            else
            {
                printf("\n...skipping\n");
                lines_printed = 1;
            }
        }
        else
        {
            printf("Unrecognized input!\n");
            break;
        }
    }

    if (tcsetattr(fileno(fp_tty), TCSANOW, &original_settings) != 0)
    {
        perror("Could not change terminal props back to original");
    }

    fclose(fp_tty);
}

int get_lines()
{
    struct winsize w;
    ioctl(1, TIOCGWINSZ, &w);
    
    return w.ws_row;
}

int get_cols()
{
    struct winsize w;
    ioctl(1, TIOCGWINSZ, &w);
    
    return w.ws_col;
}

int get_filesize(FILE* fileptr)
{
    int size = 0;
    fseek(fileptr, 0, SEEK_END);
    size = ftell(fileptr);
    fseek(fileptr, 0, SEEK_SET);
    
    return size;
}

int search(FILE* fileptr, char* search_str)
{
    char buffer[MAX_LINE_LEN];
    long long initial_pos;
    long long pos;
    int count = 0;
    int match = 0;

    char* charp;
    initial_pos = ftell(fileptr);

    while (!feof(fileptr))
    {
        fgets(buffer, MAX_LINE_LEN, fileptr);
        if ((charp = strstr(buffer, search_str)) != NULL)
        {
            match = 1;
            pos = ftell(fileptr);

            while (pos)
            {
                if (!fseek(fileptr, --pos, SEEK_SET))
                {
                    if (getc(fileptr) == '\n')
                    {
                        if (++count == 4)
                            break;
                    }

                }
                else 
                    perror("fseek() failed"); 
            }

            break;
        }

    }

    if (!match)
    {
        fseek(fileptr, initial_pos, SEEK_SET);
        return -1;
    }

    ++pos;

    return 0;
}

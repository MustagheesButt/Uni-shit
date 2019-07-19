#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>

#include <errno.h>
#include <string.h>

#include <sys/stat.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>

void myls(struct dirent** dirlist, int size);
void myls_long_list(struct dirent** dirlist, int size);

const char* get_permissions(int mode);
char get_filetype(int mode);
const char* get_username(int uid);
const char* get_groupname(int gid);

// configurations
int c_show_hidden = 0;
int c_long_listing = 0;
int c_show_inode = 0;

int main(int argc, char** argv)
{
    int opt;
    while ((opt = getopt(argc, argv, ":ail")) != -1)
    {
        switch (opt)
        {
            case 'a':
                c_show_hidden = 1;
                break;
            case 'l':
                c_long_listing = 1;
                break;
            case 'i':
                c_show_inode = 1;
                break;
            //case 'f':
            //    printf("option with value: %s\n", optarg);
            //    break;
            //case ':':
            //    printf("'-%c' option needs a value.\n", optopt);
            //    break;
            case '?':
                printf("Unknown option: %c\n", optopt);
                break;
        }
    }  
    
    // optind is for the extra arguments
    // which are not parsed
    if (optind == argc)
    {
        struct dirent **namelist;
        int n = scandir(".", &namelist, NULL, alphasort);
        
        if (n < 0)
            perror("Could not open '.'.");
        else
        {
            if (c_long_listing)
	        myls_long_list(namelist, n);
            else
                myls(namelist, n);
            
            for (int j = 0; j < n; j++)
                free(namelist[j]);
            free(namelist);
        }
    }
    else
    {
        for (int i = optind; i < argc; i++)
        {
            struct dirent **namelist;
            int n = scandir(argv[i], &namelist, NULL, alphasort);
            
            if (n < 0)
                printf("Could not open directory '%s'. %s.\n", argv[i], strerror(errno));
            else
            {
                printf("Directory listing for: %s\n", argv[i]);
                
                if (c_long_listing)
                    myls_long_list(namelist, n);
                else
                    myls(namelist, n);
                
                for (int j = 0; j < n; j++)
                    free(namelist[j]);
                free(namelist);
            }
        }
    }

    return 0;
}

void myls(struct dirent** dirlist, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (!c_show_hidden && dirlist[i]->d_name[0] == '.')
            continue;

        if (c_show_inode)
        {
            struct stat info;
            int rv = lstat(dirlist[i]->d_name, &info);
            
            if (rv == -1)
            {
                printf("Stat failed for '%s'. %s.\n", dirlist[i]->d_name, strerror(errno));
                continue;
            }

            printf("%ld ", info.st_ino);
        } 

        printf("%s\t", dirlist[i]->d_name);
    }
    printf("\n");
}

void myls_long_list(struct dirent** dirlist, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (!c_show_hidden && dirlist[i]->d_name[0] == '.')
            continue;
        
        struct stat info;
        int rv = lstat(dirlist[i]->d_name, &info);
        
        if (rv == -1)
        {
            printf("Stat failed for '%s'. %s.\n", dirlist[i]->d_name, strerror(errno));
            continue;
        }

	if (c_show_inode)
            printf("%ld ", info.st_ino);

        // print format: permissions link-count user group size time name
        char time_buff[40];
        strftime(time_buff, 40, "%b %d %H:%M", localtime(&info.st_mtime));

        printf("%s %ld\t%s\t%s %ld\t%s %s\n",
            get_permissions(info.st_mode),
            info.st_nlink,
            get_username(info.st_uid),
            get_groupname(info.st_gid),
            info.st_size,
            time_buff,
            dirlist[i]->d_name
        );
    }
}

const char* get_permissions(int mode)
{
    static char str[11];
    strcpy(str, "----------");

    // device/file type
    str[0] = get_filetype(mode);

    //owner  permissions
    if((mode & 0000400) == 0000400) str[1] = 'r';
    if((mode & 0000200) == 0000200) str[2] = 'w';
    if((mode & 0000100) == 0000100) str[3] = 'x';
    
    //group permissions
    if((mode & 0000040) == 0000040) str[4] = 'r';
    if((mode & 0000020) == 0000020) str[5] = 'w';
    if((mode & 0000010) == 0000010) str[6] = 'x';
    
    //others  permissions
    if((mode & 0000004) == 0000004) str[7] = 'r';
    if((mode & 0000002) == 0000002) str[8] = 'w';
    if((mode & 0000001) == 0000001) str[9] = 'x';

    //special  permissions
    if((mode & 0004000) == 0004000) str[3] = 's';
    if((mode & 0002000) == 0002000) str[6] = 's';
    if((mode & 0001000) == 0001000) str[9] = 't';

    return str;
}

char get_filetype(int mode)
{
    if ((mode &  0170000) == 0010000) return 'p';       // named pipe
    else if ((mode &  0170000) == 0020000) return 'c';  // character special
    else if ((mode &  0170000) == 0040000) return 'd';  // directory
    else if ((mode &  0170000) == 0060000) return 'b';  // block special
    else if ((mode &  0170000) == 0100000) return '-';  // regular file
    else if ((mode &  0170000) == 0120000) return 'l';  // soft link
    else if ((mode &  0170000) == 0140000) return 's';  // socket
    else return '?';                                    // unknown
}

const char* get_username(int uid)
{
    struct passwd* pwd = getpwuid(uid);

    if (pwd == NULL)
    {
        if (errno == 0)
            printf("Record not found in passwd file.\n");
        else
            perror("getpwuid failed");
        
        return NULL;
    }

    return pwd->pw_name;
}

const char* get_groupname(int gid)
{
    struct group* grp = getgrgid(gid);

    if (grp == NULL)
    {
        if (errno == 0)
            printf("Record not found in /etc/group file.\n");
        else
            perror("getgrgid failed");

        return NULL;
    }

    return grp->gr_name;
}

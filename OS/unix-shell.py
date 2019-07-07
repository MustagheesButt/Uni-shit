import os
import sys
import subprocess

# built-in command definitions
def pwd(argsv):
    print("{}".format(SHELL_VARS['cwd']))

def exit(argsv):
    sys.exit()

def clear(argsv):
    os.system('cls' if os.name == 'nt' else 'clear')

def chdir(argsv):
    path = argsv[0]

    # check for . and ..
    if path == '.':
        return SHELL_VARS['cwd']
    elif path == '..':
        SHELL_VARS['cwd'] = os.path.abspath(os.path.join(SHELL_VARS['cwd'], os.pardir))
    # check for relative path
    elif os.path.isdir(SHELL_VARS['cwd'] + path):
        SHELL_VARS['cwd'] = SHELL_VARS['cwd'] + path
    # check for absolute path
    elif os.path.isdir(path):
        SHELL_VARS['cwd'] = path
    else:
        print("Not a valid directory.")
    
    return SHELL_VARS['cwd']


SHELL_VARS = {
    'cwd': os.getcwd(),
    'PATH': os.environ['PATH']
}

SHELL_CMDS = {
    'pwd': pwd,
    'exit': exit,
    'clear': clear,
    'cd': chdir
}

def prompt():
    print("(Shell v3) {}> ".format(SHELL_VARS['cwd']), end='')

# returns the path as a string if given command is in PATH, otherwise returns None.
def external(command):
    for path in SHELL_VARS['PATH'].split(';'):
        if os.path.isfile(path + '/' + command) or os.path.isfile(path + '\\' + command):
            return path

    return None

def main():
    while True:
        # print prompt
        prompt()

        # get input command
        full_command = input()
        tokens = full_command.split(' ')
        command = tokens[0]
        argsv = tokens[1:len(tokens)]

        # validate existence of command or program
        # check in built-ins
        if command in SHELL_CMDS:
            SHELL_CMDS[command](argsv)
        elif external(command) is not None:
            completed = subprocess.run(tokens)
        else:
            print("`{}` command or program could not be found internally or externally.".format(command))
        

if __name__ == "__main__":
    main()

# Upgrade nc shell to full pty (on linux)

## Check your env FIRST
### Commands to run
* env - List all env vars
** check the SHELL var and make sure its not restricted (if you dont know what that means its noit for you)
** Make required changes


* make shell sexy 
** python -c 'import pty;pty.spawn("/bin/bash");' - Spawn shell (make sure its not restricted)
** CTRL + z - (background spawned shell)
** stty -a - prints info about shell (we want to note rows and columns
** stty raw -echo - put the shell in raw mode
** fg - to get back the background shell
** reset - to reset the shell, if this throws an error you missed something
** if you are ask for the type of terminal use: xterm-256color
** stty rows (from stty -a above) columns (from stty -a above)

you should now have a fully working shell. if not, you missed something

# Helpful links
* https://speakerdeck.com/knaps/escape-from-shellcatraz-breaking-out-of-restricted-unix-shells?slide=1

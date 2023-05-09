// Compile: gcc -o setuidtest setuidtest.c

#include <stdio.h>
#include <pwd.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/capability.h>

int main (int argc, char *argv[]) {
    system("/usr/bin/id");
    system("/bin/grep '^Cap' /proc/self/status");
    struct passwd *pw;
    // errno = 0;
    pw = getpwnam("ziti");
    if (pw == NULL) {
        printf("getpwnam error\n");
        exit(1);
    }
    if (setuid(pw->pw_uid) < 0) {
        printf("%s\n", strerror(errno));
        exit(1);
    }
    system("/usr/bin/env");
    system("/usr/bin/id");
    system("/bin/grep '^Cap' /proc/self/status");
}
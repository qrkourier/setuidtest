// Compile: gcc -o setuidtest setuidtest.c

#include <stdio.h>
#include <pwd.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/capability.h>

void print_caps() {
    cap_t caps;
    char *text_caps;

    /* Get the current process capabilities */
    cap_init();
    caps = cap_get_proc();
    if (caps == NULL) {
        perror("cap_get_proc");
        exit(EXIT_FAILURE);
    }

    /* Print the capabilities */
    text_caps = cap_to_text(caps, NULL);
    printf("Process capabilities:\n");
    printf("%s\n", text_caps);

    /* Free the capability set */
    if ( cap_free(text_caps) != 0 || cap_free(caps) != 0 ) {
        perror("cap_free");
        exit(EXIT_FAILURE);
    }
}

int main (int argc, char *argv[]) {
    system("/usr/bin/id");
    system("/bin/grep '^Cap' /proc/self/status");
    print_caps();
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
    print_caps();
}

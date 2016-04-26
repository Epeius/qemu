#include <fuzzy.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <libgen.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

#ifdef WIN32
#include <windows.h>
#define SLEEP(x) Sleep((x) * 1000)
#else
#define SLEEP(x) sleep(x)
#endif

int main(int argc, const char **argv)
{
    char cmd[] = "/home/epeius/target/jpeg-9a/rdjpgcom testimg.jpg";
    fuzzy_CurTime();
    system(cmd);
    fuzzy_CurTime();
}

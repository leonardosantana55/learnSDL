#include <stdio.h>

#ifdef _WIN32
#define XMAIN WinMain
#elif __linux__
#define XMAIN main
#endif

int XMAIN(){
    printf("%s", "Works!");
    return 0;
}

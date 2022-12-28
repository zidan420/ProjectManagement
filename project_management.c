#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Windows
#ifdef WIN32
#include <io.h>                   // for using access() of linux in Windows
#include <windows.h>              // Sleep()
#endif

// Linux
#ifdef unix
#include <unistd.h>
#endif

// Color codes  (ANSI color escape sequences)
#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

// My crafted header files
#include "headers/cross_platform.h"
#include "headers/quick_fix.h"
#include "headers/splash.h"
#include "headers/login.h"
#include "headers/about_us.h"
#include "headers/options.h"
#include "headers/manage_projects.h"
#include "headers/menu.h"

int main(void)
{
    char database_name[DATABASE_LENGTH];
    title();

    // call menu driver function only when login is true
    if (login(database_name))
        menu(database_name);

    return 0;
}

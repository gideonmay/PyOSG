#include <stdio.h>

#include "../buildno.h"

#ifndef DATE
#ifdef __DATE__
#define DATE __DATE__
#else
#define DATE "xx/xx/xx"
#endif
#endif

#ifndef TIME
#ifdef __TIME__
#define TIME __TIME__
#else
#define TIME "xx:xx:xx"
#endif
#endif

#ifndef BUILDNO
#define BUILDNO 0
#endif


namespace PyOSG {
const char * buildinfo()
{
    static char info[50];
    sprintf(info, "#%d, %.20s, %.9s", BUILDNO, DATE, TIME);
    return info;
}
};

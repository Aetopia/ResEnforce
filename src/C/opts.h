#pragma once

#include <unistd.h>
#include <windows.h>
#include <libgen.h>
#include <stdio.h>
#include "ini.h"

struct Profile
{
    BOOL title;
    BOOL exe;
    char *res;
};

void OptsExist(void);
struct Profile ProfileLoad(char *title, char *exe);
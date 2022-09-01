#pragma once

#include <unistd.h>
#include <windows.h>
#include <libgen.h>
#include <stdio.h>
#include "ini.h"

void OptsExist(void);
int ProfCheck(char *app);
char *ProfLoad(char *app);
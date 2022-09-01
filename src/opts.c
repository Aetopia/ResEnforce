#include "opts.h"

void OptsExist()
{
    if (access("Options.ini", F_OK) == -1)
    {
        FILE *fptr;
        fptr = fopen("Options.ini", "w");
        fprintf(fptr, "[Profiles]\n"
                      "; Title or Executable Name = Resolution\n"
                      "; Example.exe = 1600x900\n"
                      "; Example = 1280x720 \n");
        fclose(fptr);
    }
}

// Profiles
int ProfCheck(char *app)
{
    ini_t *ini = ini_load("Options.ini");
    const char *name = ini_get(ini, "Profiles", app);
    ini_free(ini);
    if (name == NULL)
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}

char *ProfLoad(char *app)
{
    ini_t *ini = ini_load("Options.ini");
    const char *name = ini_get(ini, "Profiles", app);
    ini_free(ini);
    return (char *)name;
}
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

struct Profile ProfileLoad(char *title, char *exe)
{
    char *res, *res_t, *res_e;
    BOOL prof_t = FALSE, prof_e = FALSE;
    ini_t *ini = ini_load("Options.ini");

    if (ini == NULL)
    {
        ChangeDisplaySettings(NULL, 0);
        MessageBox(NULL, "Resolution Enforcer couldn't load \"Options.ini\".", "Error", MB_OK | MB_ICONERROR);
        exit(1);
    }

    res_t = ini_get(ini, "Profiles", title);
    res_e = ini_get(ini, "Profiles", exe);
    ini_free(ini);

    if (res_t != NULL)
    {
        prof_t = TRUE;
        res = res_t;
    }
    if (res_e != NULL)
    {
        prof_e = TRUE;
        res = res_e;
    }

    struct Profile prof = {prof_t, prof_e, res};
    return prof;
}
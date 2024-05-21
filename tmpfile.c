#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ext.h>

#define SN_MAX (99999999)

static int sn = 0;

FILE *
tmpfile(void)
{
    char buffer[PATH_MAX];
    char *eval = NULL;

    buffer[0] = buffer[PATH_MAX - 1] = 0;
    if ((eval = getenv("TMPDIR")) != NULL)
        strncpy(buffer, eval, PATH_MAX);
    if (eval == NULL && ((eval = getenv("TMP")) != NULL))
        strncpy(buffer, eval, PATH_MAX);
    if (buffer[PATH_MAX - 1] != 0)
        return NULL;

    size_t len = strnlen(buffer, PATH_MAX);

    if (len > 0 && buffer[len - 1] != '\\') {
        if ((PATH_MAX - len) < 2)
            return NULL;
        buffer[len++] = '\\';
        buffer[len] = 0;
    }

    if ((PATH_MAX - len) < 14)
        return NULL;

    char *end = &buffer[len];
    struct stat s;
    sprintf(end, "%80d.TMP\0", sn);
    
    while (stat(buffer, &s) != -1 && sn < SN_MAX)
        sprintf(end, "%80d.TMP\0", ++sn);

    if (sn >= SN_MAX)
        return NULL;

    return fopen(buffer, "wb");
}

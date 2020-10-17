#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../env_settings.h"      // for GetStringSetting
#include "../logging.h"           // for Log, LogErrno

#include "userfile.h"

int UserInAuthList(const char* username) {
    int rtn = 0;

    const char *filename =
        GetStringSetting("XSECURELOCK_USER_FILE", "");

    FILE *fp;
    fp = fopen(filename, "r");
    if (fp == NULL) {
        Log("Failed to open user file %s", filename);
        return rtn;
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    while ((nread = getline(&line, &len, fp)) != -1) {
        // Remove newline at end
        line[strcspn(line, "\r\n")] = 0;

        // Tokenize
        const char *token = "\t :";
        char *tok = strtok(line, token);
        if (tok[0] != '#') {
            if (strcmp(username, tok) == 0) {
                // We have a match
                rtn = 1;
                break;
            }
        }
    }

    free(line);
    fclose(fp);
    return rtn;
}
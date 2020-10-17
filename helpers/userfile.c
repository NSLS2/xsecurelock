#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <unistd.h>

#include "../env_settings.h"      // for GetStringSetting
#include "../logging.h"           // for Log, LogErrno

#include "userfile.h"

int IsMemberOfGroup(const char *username, const char *grname, int *match) {
    int i, ngroups;
    gid_t *groups;
    struct passwd *pw;
    struct group *gr;

    *match = 0;

    pw = getpwnam(username);
    if (pw == NULL) {
        return USERFILE_ERROR;
    }

    ngroups = 0;
    getgrouplist(username, pw->pw_gid, NULL, &ngroups);

    groups = malloc(ngroups * sizeof (gid_t));
    if (groups == NULL) {
        Log("Unable to allocate memory");
        return USERFILE_ERROR;
    }

    if (getgrouplist(username, pw->pw_gid, groups, &ngroups) == -1) {
        Log("getgrouplist returned -1");
        return USERFILE_ERROR;
    }

    for (i = 0; i < ngroups; i++) {
        gr = getgrgid(groups[i]);
        if (gr != NULL) {
            if (!strcmp(grname, gr->gr_name)) {
                *match = 1;
                break;
            }
        }
    }

    free(groups);
    return USERFILE_SUCCESS;
}

int UserInAuthList(const char* username, int *match) {
    int rtn = USERFILE_ERROR;
    *match = 0;

    const char *filename =
        GetStringSetting("XSECURELOCK_USER_FILE", USERFILE_FILENAME);

    FILE *fp;
    fp = fopen(filename, "r");
    if (fp == NULL) {
        Log("Failed to open user file %s", filename);
        return USERFILE_ERROR;
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
            if(tok[0] == '@') {
                // Process a group
                tok++; // Remove @

                if (IsMemberOfGroup(username, tok, match) != USERFILE_SUCCESS) {
                    *match = 0;
                    rtn = USERFILE_ERROR;
                } else {
                    Log("user %s is in group %s", username, tok);
                    rtn = USERFILE_SUCCESS;
                    break;
                }
            } else {
                if (strcmp(username, tok) == 0) {
                    // We have a match
                    *match = 1;
                    rtn = USERFILE_SUCCESS;
                    break;
                }
            }
        }
    }

    Log("match = %d", *match);

    free(line);
    fclose(fp);
    return rtn;
}
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <unistd.h>

#include "env_settings.h"      // for GetStringSetting
#include "logging.h"           // for Log, LogErrno

#include "userfile.h"

const char *userfile_match_string[] = {
    "NO_MATCH",
    "USERNAME_MATCH",
    "GROUP_MATCH"
};

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

int UserInAuthListFile(const char * filename, const char* username, int *match) {
    int rtn = USERFILE_ERROR;
    *match = 0;

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
        const char *tokens = "\t :";
        char *_line;
        char *token = strtok_r(line, tokens, &_line);
        if (token[0] != '#') {
            if(token[0] == '@') {
                // Process a group
                token++; // Remove @

                if (IsMemberOfGroup(username, token, match) != USERFILE_SUCCESS) {
                    *match = USERFILE_NO_MATCH;
                    rtn = USERFILE_ERROR;
                    break;
                } else {
                    if (*match) {
                        *match = USERFILE_GROUP_MATCH;
                        rtn = USERFILE_SUCCESS;
                    }
                }
            } else {
                if (strcmp(username, token) == 0) {
                    // We have a match
                    *match = USERFILE_USER_MATCH;
                    rtn = USERFILE_SUCCESS;
                }
            }

            if (*match) {
                while ((token = strtok_r(NULL, tokens, &_line)) != NULL) {
                    // Proces tokens
                }
                break;
            }
        }
    }

    free(line);
    fclose(fp);
    return rtn;
}

int UserInAuthListPriv(const char* username, int *match) {
    int rtn;
#ifdef SECURE
    const char *filename = USERFILE_PRIV;
#else
    const char *filename =
        GetStringSetting("XSECURELOCK_USERFILE_PRIV", USERFILE_PRIV);
#endif
    rtn = UserInAuthListFile(filename, username, match);
    return rtn;
}

int UserInAuthListBlock(const char* username, int *match) {
    int rtn;
#ifdef SECURE
    const char *filename = USERFILE_BLOCK;
#else
    const char *filename =
        GetStringSetting("XSECURELOCK_USERFILE_BLOCK", USERFILE_BLOCK);
#endif
    rtn = UserInAuthListFile(filename, username, match);
    return rtn;
}

int UserInAuthListAny(const char* username, int *match) {
    int rtn;
#ifdef SECURE
    const char *filename = USERFILE_ANY;
#else
    const char *filename =
        GetStringSetting("XSECURELOCK_USERFILE_ANY", USERFILE_ANY);
#endif
    rtn = UserInAuthListFile(filename, username, match);
    return rtn;
}

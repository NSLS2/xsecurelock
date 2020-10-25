#ifndef USERFILE_H
#define USERFILE_H

enum userfile_rtn {
    USERFILE_SUCCESS = 0,
    USERFILE_ERROR = 1
};

enum userfile_tokens {
    USERFILE_NO_MATCH       = 0x00,
    USERFILE_USER_MATCH     = 0x01,
    USERFILE_GROUP_MATCH    = 0x02,
};

extern const char *userfile_match_string[];

int UserInAuthListPriv(const char* username, int *match);
int UserInAuthListBlock(const char* username, int *match);
int UserInAuthListAny(const char* username, int *match);

#endif

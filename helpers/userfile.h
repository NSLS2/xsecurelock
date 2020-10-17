#ifndef USERFILE_H
#define USERFILE_H

enum userfile_rtn {
    USERFILE_SUCCESS = 0,
    USERFILE_ERROR = 1
};

int UserInAuthList(const char* username, int* match);

#endif
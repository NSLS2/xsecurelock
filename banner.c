#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

#include "env_settings.h"      // for GetStringSetting
#include "logging.h"           // for Log, LogErrno

#include "banner.h"

/*! \brief Read banner message from file
 *
 * \param banner Array of pointers to store the banner lines
 * \param num_lines The number of lines read from the file
 * \param max_lines Maximum number of lines to read
 * \return 0 if sucsessful, 1 if unable to open file, 2 if error reading
 */
int ReadBannerFile(char **banner, int *num_lines, int max_lines) {
    int rtn = 0;

    const char *filename =
        GetStringSetting("XSECURELOCK_BANNER_FILE", BANNER_FILENAME);

    FILE *fp;
    fp = fopen(filename, "r");
    if (fp == NULL) {
        *num_lines = 0;
        Log("Failed to open banner file %s", filename);
        return 1;
    }

    char **line = banner;
    size_t line_len;
    *num_lines = 0;
    ssize_t read;

    for (int i=0;i < max_lines; i++) {
        banner[i] = NULL;
    }

    while ((read = getline(line, &line_len, fp)) != -1) {
        // Remove last newline
        (*line)[read - 1] = 0;
        (*num_lines)++;
        if (*num_lines >= max_lines) {
            rtn = 2;
            break;
        }
        line++;
    }

    fclose(fp);
    return rtn;
}

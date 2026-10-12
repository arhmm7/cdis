#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <rparser.h>

ParsedRequest parseRequest(const char* request) {
    const char* p = request;

    int count;

    if (sscanf(p, "*%d", &count) != 1) {
        return;
    }

    const char **cmds = malloc((size_t)count * sizeof(*cmds));
    int *lengths = malloc((size_t)count * sizeof(*lengths));

    if (cmds == NULL || lengths == NULL) {
        free(cmds);
        free(lengths);
        return;
    }

    p = strstr(p, "\r\n") + 2; 

    for (int i = 0; i < count; i++) {
        int len;

        if (sscanf(p, "$%d", &len) != 1) {
            return;
        }

        p = strstr(p, "\r\n") + 2;

        cmds[i] = p;
        lengths[i] = len;

        p += len + 2;
    }

    for (int i = 0; i < count; i++) {
        printf("%.*s\n",lengths[i], cmds[i]);
    }


    ParsedRequest parsedRequest;
    parsedRequest.args = cmds;
    parsedRequest.lengths = lengths;
    parsedRequest.count = count;

    free(cmds);
    free(lengths);

    return parsedRequest;
}
#ifndef UTILS_H
#define UTILS_H

typedef struct {
    const char **args;
    size_t *lengths;
    size_t count;
} ParsedRequest;


ParsedRequest parseRequest(const char* request);

#endif
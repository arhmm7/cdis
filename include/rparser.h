#ifndef RPARSER_H
#define RPARSER_H

#define MAX_ARGS 16
#define MAX_COMMAND_LENGTH 32


typedef struct {
        char command[MAX_COMMAND_LENGTH];
    char *args[MAX_ARGS];
    int argc;
} ParsedRequest;
ParsedRequest parseRequest(const char* request);

#endif
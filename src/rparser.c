#include <rparser.h>
#include <stdio.h>

ParsedRequest parseRequest(const char* request) {
    switch(request[0]){

        case '+':
            // Simple Strings
            break;

        case '-':
            // Simple Errors
            break;

        case ':':
            // Integers
            break;

        case '$':
            // Bulk Strings
            break;

        case '*':
            // Arrays
            break;

        case '#':
            // Booleans
            break;

        case ',':
            // Doubles
            break;

        case '(':
            // Big Numbers
            break;
            
        case '!':
            // Bulk Errors
            break;

        case '=':
            // Verbatim Strings
            break;

        case '%':
            // Verbatim Strings
            break;

        case '|':
            // Attributes
            break;

        case '~':
            // Sets
            break;

        case '>':
            // Pushes
            break;
            

        default:
            printf("Invalid Request");
    }
}
#include "http_headers.h"

HTTPHeaders* http_new_headers() {
    HTTPHeaders* headers = malloc(sizeof(HTTPHeaders));

    headers->headers = NULL;

    return headers;
}

void http_add_header(HTTPHeaders* headers, char* header) {
    if(headers->headers == NULL) {
        headers->headers = malloc(strlen(header) + 3);
        strcpy(headers->headers, header);
        strcat(headers->headers, "\r\n");
    } else {
        unsigned int size = strlen(headers->headers) + strlen(header) + 3;
        headers->headers = realloc(headers->headers, size);

        strcat(headers->headers, header);
        strcat(headers->headers, "\r\n");
    }
}

void http_add_default_headers(HTTPHeaders* headers, char* message) {
    unsigned int size = strlen(message);
    int contentLengthNumberLength = snprintf( NULL, 0, "%d", size);

    char *contentLengthHeader = malloc(17 + contentLengthNumberLength);
    sprintf(contentLengthHeader, "Content-Length: %d", size);
    http_add_header(headers, contentLengthHeader);
    free(contentLengthHeader);

    http_add_header(headers, "Connection: close");
}

void http_free_headers(HTTPHeaders* headers) {
    free(headers->headers);
    free(headers);
}
#include "http_request.h"

void http_parse_request_line(HTTPRequest* request, char* line) {
    char* method = strtok(line, " ");
    request->method = http_unstringify_method(method);

    char* requestUri = strtok(NULL, " ");
    request->requestUri = malloc(strlen(requestUri) + 1);
    strcpy(request->requestUri, requestUri);

    char* version = strtok(NULL, " ");
    request->version = http_unstringify_version(version);
}

HTTPRequest* http_parse_request(char* buffer, unsigned int length) {
    HTTPRequest* request = malloc(sizeof(HTTPRequest));

    char* found = strstr(buffer, "\r\n");

    // Request-Line
    unsigned int requestLineLength = found - buffer;

    char* requestLine = malloc(requestLineLength + 1);
    memcpy(requestLine, buffer, requestLineLength);
    requestLine[requestLineLength] = '\0';

    http_parse_request_line(request, requestLine);

    free(requestLine);

    // Headers
    char* emptyLine = strstr(buffer, "\r\n\r\n");

    char* headersBegin = buffer + requestLineLength + 2;
    unsigned int headersLength = emptyLine - headersBegin;
    request->headers = malloc(headersLength + 1);
    memcpy(request->headers, headersBegin, headersLength);
    request->headers[headersLength] = '\0';

    // Message-body
    char* messageBody = emptyLine + 4;
    unsigned int messageLength = strlen(messageBody);

    if(messageLength != 0) {
        request->message = malloc(messageLength + 1);
        strcpy(request->message, messageBody);
    } else {
        request->message = malloc(1);
        request->message[0] = '\0';
    }

    return request;
}

void http_free_request(HTTPRequest* request) {
    free(request->requestUri);
    free(request->message);
    free(request->headers);

    free(request);
}

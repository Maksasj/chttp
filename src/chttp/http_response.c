#include "http_response.h"

HTTPResponse* http_response(HTTPVersion version, HTTPStatusCode code, HTTPHeaders* headers, char* message) {
    HTTPResponse* response = malloc(sizeof(HTTPResponse));

    response->version = version;
    response->code = code;

    response->headers = malloc(strlen(headers->headers) + 1);
    strcpy(response->headers, headers->headers);

    response->message = malloc(strlen(message) + 1);
    strcpy(response->message, message);

    return response;
}

HTTPResponse* http_ok_response(HTTPVersion version, char* message) {
    HTTPHeaders* headers = http_new_headers();
    http_add_default_headers(headers, message);

    HTTPResponse* response = http_response(version, OK, headers, message);

    http_free_headers(headers);

    return response;
}

HTTPResponse* http_not_found_response(HTTPVersion version, char* message) {
    HTTPHeaders* headers = http_new_headers();
    http_add_default_headers(headers, message);

    HTTPResponse* response = http_response(version, NOT_FOUND, headers, message);

    http_free_headers(headers);

    return response;
}

char* read_file(const char* filename) {
    FILE* file = fopen(filename, "r");

    if (file == NULL) {
        printf("Cannot open file: %s\n", filename);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    int length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* buffer = (char*) malloc(length + 1);
    if (buffer) {
        fread(buffer, 1, length, file);
        buffer[length] = '\0';
    }

    fclose(file);

    return buffer;
}

HTTPResponse* http_ok_response_file(HTTPVersion version, char* fileName) {
    char *buffer = read_file(fileName);

    HTTPResponse* response = http_ok_response(version, buffer);

    free(buffer);

    return response;
}

unsigned long long calculate_string_response_length(HTTPResponse* response) {
    unsigned int length = 0;

    // Status Line
    char* version = http_stringify_version(response->version);
    length += strlen(version) + 1;

    char status[4];
    itoa(response->code, status, 10);
    length += strlen(status) + 1;

    char* statusPhrase = http_stringify_status(response->code);
    length += strlen(statusPhrase) + 2;

    // Headers
    length += strlen(response->headers);

    // Message-body
    length += 2 + strlen(response->message);
    
    return length;
}

char* http_stringify_response(HTTPResponse* response) {
    unsigned long long length = calculate_string_response_length(response);

    // Status Line
    char* result = malloc(length);
    strcpy(result, http_stringify_version(response->version));
    strcat(result, " ");

    char status[4];
    itoa(response->code, status, 10);
    strcat(result, status);
    strcat(result, " ");

    strcat(result, http_stringify_status(response->code));
    strcat(result, "\r\n");

    // Headers
    strcat(result, response->headers);

    // Message-body
    strcat(result, "\r\n");
    strcat(result, response->message);

    return result;
}

void http_send_response(HTTPResponse* response, int socket, int flags) {
    char* responseStr = http_stringify_response(response);

    int sent = send(socket,responseStr, strlen(responseStr),flags);

    CHTTP_LOG(SERVER_INFO, "Send HTTP response");

    free(responseStr);
}

void http_free_response(HTTPResponse* response) {
    free(response->headers);
    free(response->message);

    free(response);
}

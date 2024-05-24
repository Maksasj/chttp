#include "chttp_response.h"
#include "chttp_status_code.h"

CHTTPResponse* chttp_response(CHTTPVersion version, HTTPStatusCode code, CHTTPHeaders* headers, char* message) {
    CHTTPResponse* response = malloc(sizeof(CHTTPResponse));

    response->version = version;
    response->code = code;

    response->headers = (char*) calloc(1, strlen(headers->headers) + 1);
    strcpy(response->headers, headers->headers);

    response->message = (char*) calloc(1, strlen(message) + 1);
    strcpy(response->message, message);

    return response;
}

CHTTPResponse* chttp_ok_response(CHTTPVersion version, char* message) {
    CHTTPHeaders* headers = chttp_new_headers();
    chttp_add_default_headers(headers, message);

    CHTTPResponse* response = chttp_response(version, OK, headers, message);

    chttp_free_headers(headers);

    return response;
}

CHTTPResponse* chttp_not_found_response(CHTTPVersion version, char* message) {
    CHTTPHeaders* headers = chttp_new_headers();
    chttp_add_default_headers(headers, message);

    CHTTPResponse* response = chttp_response(version, NOT_FOUND, headers, message);

    chttp_free_headers(headers);

    return response;
}

char* chttp_read_file_internal(const char* filename) {
    FILE* file = fopen(filename, "rb");

    if (file == NULL) {
        CHTTP_LOG(CHTTP_ERROR, "Cannot open %s file", filename);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    int length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* buffer = (char*) malloc(length + 1);

    fread(buffer, 1, length, file);
    buffer[length] = '\0';

    fclose(file);

    return buffer;
}

CHTTPResponse* chttp_ok_response_file(CHTTPVersion version, char* fileName) {
    char *buffer = chttp_read_file_internal(fileName);
    if(buffer == NULL) {
        CHTTP_LOG(CHTTP_ERROR, "Failed to open file, returning not found");
        return chttp_not_found_response(version, "404 Not found");
    }

    CHTTPResponse* response = chttp_ok_response(version, buffer);

    free(buffer);

    return response;
}

unsigned long long chttp_calculate_string_response_size(CHTTPResponse* response) {
    // 1, since there is null terminater
    unsigned int size = 1;

    // Status Line
    char* version = chttp_stringify_version(response->version);
    size += strlen(version) + 1;

    char status[5];
    // itoa(response->code, status, 10);
    sprintf(status, "%d", response->code); // TODO

    size += strlen(status) + 1;

    char* statusPhrase = chttp_stringify_status(response->code);
    size += strlen(statusPhrase) + 2;

    // Headers
    size += strlen(response->headers);

    // Message-body
    size += 2 + strlen(response->message);
    
    return size;
}

char* chttp_stringify_response(CHTTPResponse* response) {
    unsigned long long size = chttp_calculate_string_response_size(response);

    // Status Line
    char* result = calloc(1, size);
    strcpy(result, chttp_stringify_version(response->version));
    strcat(result, " ");

    char status[5] = { '\0' };
    sprintf(status, "%d", response->code); // TODO
    strcat(result, status);
    strcat(result, " ");

    strcat(result, chttp_stringify_status(response->code));
    strcat(result, "\r\n");

    // Headers
    strcat(result, response->headers);

    // Message-body
    strcat(result, "\r\n");
    strcat(result, response->message);

    return result;
}

void chttp_send_response(CHTTPResponse* response, CHTTPConnection* connection) {
    char* responseStr = chttp_stringify_response(response);

    if(responseStr == NULL) {
        CHTTP_LOG(CHTTP_WARNING, "While 'stringifying' HTTP response error occored");
        return;
    }

    unsigned int responseLength = strlen(responseStr);

    int result = send(connection->socket, responseStr, responseLength, 0);

    if(result < 0) {
        CHTTP_LOG(CHTTP_WARNING, "While sending HTTP response, error occurred");
        free(responseStr);
        return;
    }

    CHTTP_LOG(CHTTP_INFO, "Send HTTP response");

    free(responseStr);
}

void chttp_free_response(CHTTPResponse* response) {
    free(response->headers);
    free(response->message);

    free(response);
}

#include "chttp_get_request_parsed.h"

void chttp_push_get_field_to_parsed(CHTTPGetRequestParsed* parsed, CHTTPGetField* field) {
    parsed->fields[parsed->fieldCount] = field;
    ++parsed->fieldCount;
}

CHTTPGetRequestParsed* chttp_parse_get_request(HTTPRequest* request) {
    unsigned int uriLength = strlen(request->requestUri);

    // Lets firstly replace '+' with ' '
    for(int i = 0; i < uriLength; ++i) {
        if(request->requestUri[i] == '+')    
            request->requestUri[i] = ' ';
    }

    // Lets skip route
    char* start = request->requestUri;
    while (*start != '?') {
        ++start;

        if(*start == '\0') {
            CHTTP_LOG(SERVER_WARNING, "Error occurred while parsing GET request, GET request have emtpy body");
            return NULL;
        }
    }

    ++start;

    // Lets check if GET request body present
    unsigned length = strlen(start);
    if(length == 0) {
        CHTTP_LOG(SERVER_WARNING, "Error occurred while parsing GET request, GET request have emtpy body");
        return NULL;
    }

    // Copy new request uri to tmp buffer
    char* buffer = (char*) malloc(length);
    memcpy(buffer, start, length + 1);

    unsigned int fieldCount = 1;
    char* fieldPairs[CHTTP_MAX_GET_REQUEST_FIELD_COUNT];

    fieldPairs[0] = buffer;

    // Separating field pairs and storing in fieldPairs
    for(int i = 0; i < length; ++i) {
        if(buffer[i] == '&') {
            buffer[i] = '\0';

            int nextIndex = i + 1;
            if(nextIndex >= length) {
                CHTTP_LOG(SERVER_WARNING, "Error occurred while parsing GET request, GET request last field started, but empty");
            } else {
                fieldPairs[fieldCount] = buffer + nextIndex;
                ++fieldCount;
            }
        }
    }

    CHTTPGetRequestParsed* get = (CHTTPGetRequestParsed*) calloc(1, sizeof(CHTTPGetRequestParsed));

    // Process each field pair
    for(int i = 0; i < fieldCount; ++i) {
        char* fieldName = fieldPairs[i];
        char* fieldValue = fieldName;

        while (*fieldValue != '=') {
            ++fieldValue;

            if(*fieldValue == '\0')
                break;
        }

        if(*fieldValue == '\0') {
            CHTTP_LOG(SERVER_WARNING, "Error occurred while parsing GET request, field value is empty");
            continue;;
        }

        *fieldValue = '\0';
        ++fieldValue;

        const unsigned int fieldNameLength = strlen(fieldName); 
        const unsigned int fieldValueLength = strlen(fieldValue); 
        
        if(fieldValueLength == 0) {
            CHTTP_LOG(SERVER_WARNING, "Error occurred while parsing GET request, field value is empty");
            break;
        }

        CHTTPGetField* field = chttp_new_get_field(fieldName, fieldValue);
        chttp_push_get_field_to_parsed(get, field);
    }

    return get;
}

CHTTPGetField* chttp_new_get_field(char* fieldName, char* fieldValue) {
    const unsigned int fieldNameLength = strlen(fieldName); 
    const unsigned int fieldValueLength = strlen(fieldValue); 

    CHTTPGetField* field = (CHTTPGetField*) malloc(sizeof(CHTTPGetField));

    field->fieldName = calloc(fieldNameLength + 1, 1);
    field->fieldValue = calloc(fieldValueLength + 1, 1);

    memcpy(field->fieldName, fieldName, fieldNameLength);
    memcpy(field->fieldValue, fieldValue, fieldValueLength);

    return field;
}

void chttp_free_get_field(CHTTPGetField* field) {
    free(field->fieldName);
    free(field->fieldValue);
    free(field);
}

void chttp_free_get_request_parsed(CHTTPGetRequestParsed* parsed) {
    if(parsed == NULL)
        return;
    
    for(int i = 0; i < parsed->fieldCount; ++i)
        chttp_free_get_field(parsed->fields[i]);

    free(parsed);
}

CHTTPGetField* chttp_get_request_parsed_find_field(CHTTPGetRequestParsed* parsed, char* fieldName) {
    for(int i = 0; i < parsed->fieldCount; ++i) {
        CHTTPGetField* field = parsed->fields[i]; 

        if(strcmp(field->fieldName, fieldName) == 0)
            return field;
    }

    return NULL;
}
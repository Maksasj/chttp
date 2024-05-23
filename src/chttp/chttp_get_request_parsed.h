#ifndef _CHTTP_GET_REQUEST_PARSED_H_
#define _CHTTP_GET_REQUEST_PARSED_H_

#include "chttp_request.h"

#define CHTTP_MAX_GET_REQUEST_FIELD_COUNT 256

typedef struct CHTTPGetField {
    char* fieldName;
    char* fieldValue;
} CHTTPGetField;

typedef struct CHTTPGetRequestParsed {
    unsigned int fieldCount;
    CHTTPGetField* fields[CHTTP_MAX_GET_REQUEST_FIELD_COUNT];
} CHTTPGetRequestParsed;

CHTTPGetField* chttp_new_get_field(char* fieldName, char* fieldValue);
void chttp_free_get_field(CHTTPGetField* field);

CHTTPGetRequestParsed* chttp_parse_get_request(CHTTPRequest* request);
void chttp_free_get_request_parsed(CHTTPGetRequestParsed* parsed);

void chttp_push_get_field_to_parsed(CHTTPGetRequestParsed* parsed, CHTTPGetField* field);
CHTTPGetField* chttp_get_request_parsed_find_field(CHTTPGetRequestParsed* parsed, char* fieldName);

#endif
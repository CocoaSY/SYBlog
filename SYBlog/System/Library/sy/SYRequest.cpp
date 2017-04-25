//
//  SYRequest.cpp
//  SYBlog
//
//  Created by Cocoa on 4/25/17.
//  Copyright © 2017 Cocoa. All rights reserved.
//

#include "SYRequest.hpp"
#include "SYLog.hpp"
#include "SYApp.hpp"

SYRequest::SYRequest(struct evhttp_request * req){
    m_req = req;
}

SYRequest::~SYRequest(){
    //evhttp_request_free(m_req);
}

void SYRequest::HttpDebug(){
    if (LOGGER._level == LOG_LEVEL_DEBUG) {
        DebugHttpGetCommand();
        DebugHttpHeader();
    }
}

void SYRequest::DebugHttpHeader(){
    struct evkeyval * header;
    struct evkeyvalq * headers;
    
    headers = evhttp_request_get_input_headers(m_req);
    for (header = headers->tqh_first; header; header = header->next.tqe_next) {
        log_debug("%s: %s\n", header->key, header->value);
    }
}

const char * SYRequest::DebugHttpGetCommand(){
    const char * cmdType;
    
    switch (evhttp_request_get_command(m_req)) {
            
        case EVHTTP_REQ_GET:
            cmdType = "GET";
            break;
        case EVHTTP_REQ_POST:
            cmdType = "POST";
            break;
        case EVHTTP_REQ_HEAD:
            cmdType = "HEAD";
            break;
        case EVHTTP_REQ_PUT:
            cmdType = "PUT";
            break;
        case EVHTTP_REQ_DELETE:
            cmdType = "DELETE";
            break;
        case EVHTTP_REQ_OPTIONS:
            cmdType = "OPTIONS";
            break;
        case EVHTTP_REQ_TRACE:
            cmdType = "TRACE";
            break;
        case EVHTTP_REQ_CONNECT:
            cmdType = "CONNECT";
            break;
        case EVHTTP_REQ_PATCH:
            cmdType = "PATCH";
            break;
        default:
            cmdType = "unknown";
            break;
    }
    
    log_debug("Received a %s request for %s \n", cmdType, evhttp_request_get_uri(m_req));
    return cmdType;
}

void SYRequest::ParseUrl(struct evkeyvalq * evMyHeader){
    const char * uri_query;
    uri_query = evhttp_uri_get_query(evhttp_request_get_evhttp_uri(m_req));
    evhttp_parse_query_str(uri_query, evMyHeader);
    m_url = uri_query;
    log_debug("The request url is %s",m_url.c_str());

}

void SYRequest::GetPostData(struct evkeyvalq * evData){
    evbuffer * buf = evhttp_request_get_input_buffer(m_req);
    int data_len = int(evbuffer_get_length(buf));
    
    char * pBuf = (char *)malloc(data_len + 1);
    memset(pBuf, 0, data_len + 1);
    
    evbuffer_copyout(buf, pBuf, data_len + 1);
    log_debug("%s\r\n", pBuf);
    
    evhttp_parse_query_str(pBuf, evData);
    free(pBuf);
}

const char * SYRequest::Get(std::string key){
    struct evkeyvalq GetData;
    ParseUrl(&GetData);
    return evhttp_find_header(&GetData, key.c_str());
}



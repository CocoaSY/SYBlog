//
//  SYResponse.cpp
//  SYBlog
//
//  Created by Cocoa on 4/25/17.
//  Copyright © 2017 Cocoa. All rights reserved.
//

#include "SYResponse.hpp"
#include "SYLog.hpp"

SYResponse::SYResponse(struct evhttp_request * req){
    m_req = req;
}

SYResponse::~SYResponse(){
    
}

void SYResponse::SendHttpResponse(const std::string & data){
    struct evbuffer * buf = evbuffer_new();
    if (buf == NULL) {
        log_error("failed to create response buffer\r\n");
        return;
    }
    
    int ret = evbuffer_add_printf(buf, "%s",data.c_str());
    log_debug("evbuffer_add_printf ret= %d length=%d \r\n", ret, data.length());
    
    evhttp_add_header(evhttp_request_get_output_headers(m_req), "Content-Type", "text/html;charset=utf-8");
    evhttp_send_reply(m_req, 200, "OK", buf);
    evbuffer_free(buf);
}

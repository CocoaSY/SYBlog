//
//  SYRequest.hpp
//  SYBlog
//
//  Created by Cocoa on 4/25/17.
//  Copyright © 2017 Cocoa. All rights reserved.
//

#ifndef SYRequest_hpp
#define SYRequest_hpp

#include <stdio.h>
#include <string>
#include <event.h>
#include <event2/http.h>

class SYRequest {
    
private:
    struct evhttp_request *  m_req;
    
protected:
    std::string m_url;
    
public:
    
    SYRequest(struct evhttp_request * req = NULL);
    ~SYRequest();
    
    /** Receive a request */
    void HttpDebug();
    void DebugHttpHeader();
    const char * DebugHttpGetCommand();
    
    void ParseUrl(struct evkeyvalq * evMyHeader);
    void GetPostData(struct evkeyvalq * evData);
    
    const char * Get(std::string key);
    
    
};

#endif /* SYRequest_hpp */

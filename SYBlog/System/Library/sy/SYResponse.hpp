//
//  SYResponse.hpp
//  SYBlog
//
//  Created by Cocoa on 4/25/17.
//  Copyright © 2017 Cocoa. All rights reserved.
//

#ifndef SYResponse_hpp
#define SYResponse_hpp

#include <stdio.h>
#include <event.h>
#include <event2/http.h>
#include <string>

class SYResponse {

private:
    struct evhttp_request * m_req;
    
public:
    SYResponse(struct evhttp_request * req);
    ~SYResponse();
    
    void SendHttpResponse(const std::string & data);
    
};

#endif /* SYResponse_hpp */

//
//  IndexController.hpp
//  SYBlog
//
//  Created by Cocoa on 4/19/17.
//  Copyright © 2017 Cocoa. All rights reserved.
//

#ifndef IndexController_hpp
#define IndexController_hpp

#include <stdio.h>
#include <event.h>

#include "SYController.h"

class IndexController : public SYController {
    
public:
    IndexController();
    ~IndexController();
    
    void Rewrite(std::string link);
    void SetRoute(evhttp * http);
    
    static void IndexRequestCallback(struct evhttp_request *req, void *arg);
    static void RequestPage(struct evhttp_request *req, const char *PageId);
    
};

#endif /* IndexController_hpp */

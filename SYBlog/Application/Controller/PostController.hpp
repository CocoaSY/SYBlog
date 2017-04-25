//
//  PostController.hpp
//  SYBlog
//
//  Created by Cocoa on 4/21/17.
//  Copyright © 2017 Cocoa. All rights reserved.
//

#ifndef PostController_hpp
#define PostController_hpp

#include <stdio.h>

#include "BaseController.hpp"


class PostController : public BaseController {
    
public:
    
    void SetRoute(evhttp * http);
    
    static void PostRequestCallback(struct evhttp_request *req, void *arg);
    
};


#endif /* PostController_hpp */

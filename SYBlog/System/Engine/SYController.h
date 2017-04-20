//
//  SYController.hpp
//  SYBlog
//
//  Created by Cocoa on 4/18/17.
//  Copyright © 2017 Cocoa. All rights reserved.
//

#ifndef SYController_hpp
#define SYController_hpp

#include <stdio.h>
#include <string>
#include <event2/http.h>

class SYController {
    
public:
    
    virtual void SetRoute(evhttp * http) = 0;
    virtual void Rewrite(std::string link) = 0;
    
};

#endif /* SYController_hpp */

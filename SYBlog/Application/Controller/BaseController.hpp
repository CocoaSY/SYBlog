//
//  BaseController.hpp
//  SYBlog
//
//  Created by Cocoa on 4/20/17.
//  Copyright © 2017 Cocoa. All rights reserved.
//

#ifndef BaseController_hpp
#define BaseController_hpp

#include <stdio.h>
#include <string>

#include "SYController.h"

class BaseController : public SYController {
    
public:
    virtual void SetRoute(evhttp * http) = 0;
    
    static std::string HeaderHtml();
    static std::string FooterHtml();
    
};

#endif /* BaseController_hpp */

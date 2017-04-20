//
//  CategoryController.hpp
//  SYBlog
//
//  Created by Cocoa on 4/20/17.
//  Copyright © 2017 Cocoa. All rights reserved.
//

#ifndef CategoryController_hpp
#define CategoryController_hpp

#include <stdio.h>

#include "BaseController.hpp"

class CategoryController : public BaseController {
    
public:
    
    void SetRoute(evhttp * http);
    void Rewrite(std::string link);
    
    static void CategoryRequestCallback(struct evhttp_request *req, void *arg);
    
};

#endif /* CategoryController_hpp */

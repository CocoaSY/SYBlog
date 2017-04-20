//
//  SYUrl.hpp
//  SYBlog
//
//  Created by Cocoa on 4/18/17.
//  Copyright © 2017 Cocoa. All rights reserved.
//  URL 重写 通过控制器自定义的重写函数(Rewrite) 将路由和参数重写

#ifndef SYUrl_hpp
#define SYUrl_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include <map>

#include "SYController.h"


class OCUrl {
private:
    std::string m_urlStr;
    std::string m_sslStr;
    std::vector<SYController *> m_rewrites;
    
public:
    OCUrl(std::string url,std::string ssl);
    ~OCUrl();
    
    void AddRewrite(SYController * controller);
    std::string Link(const std::string & route,const std::map<std::string, std::string> args,bool secure = false);
    
    
};


#endif /* SYUrl_hpp */

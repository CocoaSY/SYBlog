//
//  SYTemplate.hpp
//  SYBlog
//
//  Created by Cocoa on 4/18/17.
//  Copyright © 2017 Cocoa. All rights reserved.
//  模板渲染 : 将模板中的 key 替换成 value

#ifndef SYTemplate_hpp
#define SYTemplate_hpp

#include <stdio.h>
#include <string>
#include <map>

class OCTemplate {
    
private:
    std::map<std::string, std::string> m_data;
    
public:
    
    void Set(const std::string & key,const std::string & value);
    void Render(std::string & strHtml);
    
};

#endif /* SYTemplate_hpp */

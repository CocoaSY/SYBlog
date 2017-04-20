//
//  SYTemplate.cpp
//  SYBlog
//
//  Created by Cocoa on 4/18/17.
//  Copyright © 2017 Cocoa. All rights reserved.
//

#include "OCTemplate.hpp"
#include "SYUntil.hpp"

using namespace std;

void OCTemplate::Set(const std::string & key,const std::string & value){
    m_data[key] = value;
}

void OCTemplate::Render(std::string & strHtml){
    
    map<string, string>::iterator iter;
    for (iter = m_data.begin(); iter != m_data.end(); iter++) {
        StringReplace(strHtml, iter->first, iter->second);
    }
    
}
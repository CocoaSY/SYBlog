//
//  SYUrl.cpp
//  SYBlog
//
//  Created by Cocoa on 4/18/17.
//  Copyright © 2017 Cocoa. All rights reserved.
//

#include "OCUrl.hpp"

using namespace std;

OCUrl::OCUrl(std::string url,std::string ssl){
    m_urlStr = url;
    m_sslStr = ssl;
}

OCUrl::~OCUrl(){
    if (!m_rewrites.empty()) {
        vector<SYController *>::iterator iter = m_rewrites.begin();
        while (iter != m_rewrites.end()) {
            m_rewrites.erase(iter);
        }
    }
}

void OCUrl::AddRewrite(SYController * controller){
    m_rewrites.push_back(controller);
}

string OCUrl::Link(const std::string & route,map<string, string> args,bool secure){
    
    if (m_sslStr.length() && secure) {
        m_urlStr = m_sslStr + "index.php?route=" + route;
    } else {
        m_urlStr = m_urlStr + "index.php?route=" + route;
    }
    
    if (args.size()) {
        m_urlStr += "&";
        map<string, string>::iterator iter;
        for (iter = args.begin(); iter != args.end(); iter++) {
            m_urlStr = m_urlStr + iter->first + "=" + iter->second;
        }
    }
    
    vector<SYController *>::iterator iter;
    for (iter = m_rewrites.begin(); iter != m_rewrites.end(); iter++) {
        (*iter)->Rewrite(m_urlStr);
    }
    
    return m_urlStr;
}
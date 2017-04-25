//
//  SYSiteConfig.hpp
//  SYBlog
//
//  Created by Cocoa on 4/25/17.
//  Copyright © 2017 Cocoa. All rights reserved.
//

#ifndef SYSiteConfig_hpp
#define SYSiteConfig_hpp

#include <stdio.h>
#include <string>
#include <map>

typedef std::map<std::string, std::string> SITECONFIG;

class SYSiteConfig {
    
public:
    SITECONFIG m_siteConfig;
    
public:
    SYSiteConfig();
    virtual ~SYSiteConfig();
    
    static SYSiteConfig * GetInstance();
    static SYSiteConfig * m_config;
    
    bool Init();
    bool LoadSiteConfig();
    
    std::string GetSiteConfig(std::string key);
};


#endif /* SYSiteConfig_hpp */

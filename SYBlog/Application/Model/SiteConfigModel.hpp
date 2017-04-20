//
//  SiteConfigModel.hpp
//  SYBlog
//
//  Created by Cocoa on 4/20/17.
//  Copyright © 2017 Cocoa. All rights reserved.
//

#ifndef SiteConfigModel_hpp
#define SiteConfigModel_hpp

#include <stdio.h>
#include <string>
#include <map>

#include "SYModel.h"


typedef struct _SITECONFIG_ {
    std::string Fid;
    std::string Fkey;
    std::string Fvalue;
} SITECONFIG;

typedef std::map<std::string, std::string> SITECONFIGMAP;

class SiteConfigModel : public SYModel {
    
private:
    SITECONFIGMAP m_siteConfigMap;
    
public:
    SiteConfigModel();
    
    SITECONFIGMAP GetSiteConfig();
    std::string GetSiteConfig(std::string key);
};

#endif /* SiteConfigModel_hpp */

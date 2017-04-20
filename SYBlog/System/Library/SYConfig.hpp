//
//  SYConfig.hpp
//  SYBlog
//
//  Created by Cocoa on 4/19/17.
//  Copyright © 2017 Cocoa. All rights reserved.
//

#ifndef SYConfig_hpp
#define SYConfig_hpp

#include <stdio.h>
#include <string>
#include <map>
#include "SYIniFile.hpp"

typedef struct _MYSQLCONGIG_{
    std::string ipaddr;
    uint16_t port;
    std::string username;
    std::string password;
    std::string dbname;
    uint16_t poolsize;
} MYSQLCONFIG;

typedef struct _APPCONFIG_{
    std::string ServerIP;
    uint16_t Port;
    uint16_t HTTPThreads;
    std::string LogFileName;
    std::string LogLevel;
    uint32_t HTTPTimeout;
    uint32_t CacheTime;
    std::string RootDir;
    std::string Theme;
    std::string Shell;
} APPCONFIG;

typedef std::map<std::string, std::string> SITECONFIG;

class SYConfig {
    
public:
    MYSQLCONFIG m_mysqlConfig;
    APPCONFIG m_appConfig;
    SITECONFIG m_siteConfig;
    std::string m_rootFullPath;
    
public:
    SYConfig();
    virtual ~SYConfig();
    
    static SYConfig * GetInstance();
    static SYConfig * m_config;
    
    bool Init(std::string iniFile);
    bool LoadDBConfig(SYIniFile & iniFile);
    bool LoadAPPConfig(SYIniFile & iniFile);
    bool LoadSiteConfig();
    
};




#endif /* SYConfig_hpp */

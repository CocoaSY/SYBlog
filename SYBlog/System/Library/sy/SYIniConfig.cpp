//
//  SYIniConfig.cpp
//  SYBlog
//
//  Created by Cocoa on 4/25/17.
//  Copyright © 2017 Cocoa. All rights reserved.
//

#include "SYIniConfig.hpp"
#include "SYLog.hpp"

SYIniConfig * SYIniConfig::m_config = NULL;
SYIniConfig * SYIniConfig::GetInstance(){
    if (m_config == NULL) {
        m_config = new SYIniConfig;
    }
    return m_config;
}

SYIniConfig::SYIniConfig(){
    
}

SYIniConfig::~SYIniConfig(){
    
}

bool SYIniConfig::Init(std::string iniFile){
    SYIniFile aIniFile(iniFile);
    if (aIniFile.ReadFile()) {
        LoadDBConfig(aIniFile);
        LoadAPPConfig(aIniFile);
        
        char szTemp[1024] = {0};
        char szDir[1024] = {0};
        
        if (getcwd(szTemp, sizeof(szTemp)) == NULL) {
            log_error("get dir error \r\n");
            return false;
        }
        log_info("CurrentDirectory: %s \r\n", szTemp);
        snprintf(szDir, sizeof(szDir), "%s/%s",szTemp,SYIniConfig::GetInstance()->m_appConfig.RootDir.c_str());
        m_rootFullPath = szDir;
        return true;
    }
    return false;
}

bool SYIniConfig::LoadDBConfig(SYIniFile & iniFile){
    
    m_mysqlConfig.ipaddr    = iniFile.GetValue("MYSQLPOOL", "IPADDR");
    m_mysqlConfig.port      = iniFile.GetValueI("MYSQLPOOL", "PORT");
    m_mysqlConfig.username  = iniFile.GetValue("MYSQLPOOL", "USER");
    m_mysqlConfig.password  = iniFile.GetValue("MYSQLPOOL", "PASSWD");
    m_mysqlConfig.dbname    = iniFile.GetValue("MYSQLPOOL", "DBNAME");
    m_mysqlConfig.poolsize  = iniFile.GetValueI("MYSQLPOOL", "POOLSIZE");
    
    return true;
}

bool SYIniConfig::LoadAPPConfig(SYIniFile & iniFile){
    
    m_appConfig.RootDir      = iniFile.GetValue("APP", "ROOTDIR");
    m_appConfig.Theme      = iniFile.GetValue("APP", "THEME");
    m_appConfig.LogFileName  = iniFile.GetValue("APP", "LOGFILENAME");
    m_appConfig.LogLevel     = iniFile.GetValue("APP", "LOGLEVEL");
    m_appConfig.Shell        = iniFile.GetValue("APP", "SHELL");
    m_appConfig.CacheTime   = iniFile.GetValueI("APP", "CACHETIMER");
    
    m_appConfig.ServerIP     = iniFile.GetValue("HTTPD", "IP");
    m_appConfig.Port         = iniFile.GetValueI("HTTPD", "PORT");
    m_appConfig.HTTPThreads = iniFile.GetValueI("HTTPD", "HTTPDTHREADS");
    m_appConfig.HTTPTimeout = iniFile.GetValueI("HTTPD", "HTTPDTIMEOUT");
    
    return true;
    
}

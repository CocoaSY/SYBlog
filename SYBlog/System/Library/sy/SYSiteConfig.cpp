//
//  SYSiteConfig.cpp
//  SYBlog
//
//  Created by Cocoa on 4/25/17.
//  Copyright © 2017 Cocoa. All rights reserved.
//

#include "SYSiteConfig.hpp"
#include <mysql.h>

#include "SYMysqlPool.hpp"
#include "SYLog.hpp"

using namespace std;

SYSiteConfig * SYSiteConfig::m_config = NULL;
SYSiteConfig * SYSiteConfig::GetInstance(){
    if (m_config == NULL) {
        m_config = new SYSiteConfig;
    }
    return m_config;
}

SYSiteConfig::SYSiteConfig(){
    LoadSiteConfig();
}

SYSiteConfig::~SYSiteConfig(){
    
}

bool SYSiteConfig::LoadSiteConfig(){
    
    string strSQL = "SELECT Fid,Fkey,Fvalue FROM sy_siteconfig LIMIT 100;";
    
    SYMysqlPool * mysqlPool = SYMysqlPool::GetInstance();
    MYSQL_RES * pRes = mysqlPool->Select(strSQL.c_str());
    if (pRes != NULL) {
        MYSQL_ROW row;
        while ( (row = mysql_fetch_row(pRes)) ) {
            m_siteConfig[row[1]] = row[2];
            log_debug("%s:%s \r\n", row[1], row[2]);
        }
        
        mysqlPool->FreeRecord(pRes);
        return true;
    }
    log_error("error \r\n");
    return false;
}

std::string SYSiteConfig::GetSiteConfig(std::string key){
    return m_siteConfig[key];
}

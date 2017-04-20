//
//  SiteConfigModel.cpp
//  SYBlog
//
//  Created by Cocoa on 4/20/17.
//  Copyright © 2017 Cocoa. All rights reserved.
//

#include "SiteConfigModel.hpp"

using namespace std;

SiteConfigModel::SiteConfigModel(){
    
    string sql =    "SELECT Fid,Fkey,Fvalue \
                    FROM sy_siteconfig";
    
    MYSQL_RES * pRes = m_mysqlPool->Select(sql.c_str());
    if (pRes != NULL) {
        MYSQL_ROW row;
        while ( (row = mysql_fetch_row(pRes)) ) {
            SITECONFIG siteConfig;
            siteConfig.Fid = row[0];
            siteConfig.Fkey = row[1];
            siteConfig.Fvalue = row[2];
            m_siteConfigMap[siteConfig.Fkey] = siteConfig.Fvalue;
        }
        m_mysqlPool->FreeRecord(pRes);
    }
    
}

SITECONFIGMAP SiteConfigModel::GetSiteConfig(){
    return m_siteConfigMap;
}

std::string SiteConfigModel::GetSiteConfig(std::string key){
    return m_siteConfigMap[key];
}
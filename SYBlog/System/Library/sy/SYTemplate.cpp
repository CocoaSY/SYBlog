//
//  SYTemplate.cpp
//  SYBlog
//
//  Created by Cocoa on 4/19/17.
//  Copyright © 2017 Cocoa. All rights reserved.
//

#include "SYTemplate.hpp"

#include <fcntl.h>

#include "SYConstant.h"
#include "SYLog.hpp"
#include "SYIniConfig.hpp"
#include "SYSiteConfig.hpp"
#include "SYUntil.hpp"

using namespace std;

SYTemplate::SYTemplate(){
    
}

SYTemplate::~SYTemplate(){
    
}

SYTemplate * SYTemplate::GetInstance(){
    static SYTemplate * temp = NULL;
    if (temp == NULL) {
        temp = new SYTemplate;
    }
    return temp;
}


void SYTemplate::Init(map<string,string> & tempMap){
    LoadTemplatePage(tempMap);
}

bool SYTemplate::BuiltHtmlByTemplateKey(const char * pKey,TEMPLATE & temp){
    
    temp = m_templateMap[pKey];
    if (temp.value.length() > 0) {
        ReplaceTemplatePage(temp.value);
        return true;
    } else {
        log_error("Build html error key=%p \n", pKey);
        return false;
    }
    return false;
}

const std::string SYTemplate::GetTemplate(const char * pKey){
    return m_templateMap[pKey].value;
}


TEMPLATE & SYTemplate::GetFile(std::string fileDir,std::string fileName,TEMPLATE & temp,TEMPLATECB aCall){
    
    char szBuff[MAX_FILE_SIZE] = {0};
    string path = fileDir + fileName;
    
    temp.value = "";
    temp.templateCB = aCall;
    
    if (!path.length()) {
        log_error("getfile error Path is null \r\n");
        return temp;
    }
    
    log_debug("Template::GetFile path=%s \r\n", path.c_str());
    
    FILE * fd = fopen(path.c_str(), "rb");
    if (fd == NULL) {
        log_error("getfile error path=%s \r\n", path.c_str());
        return temp;
    }
    
    int len = int(fread(szBuff, 1, MAX_FILE_SIZE, fd));
    szBuff[len] = '\0';
    
    temp.value = szBuff;
    fclose(fd);
    return temp;
}

void SYTemplate::LoadTemplatePage(std::string key,std::string value){
    TEMPLATE aTemp;
    SYIniConfig * config = SYIniConfig::GetInstance();
    string dir = config->m_rootFullPath + "/themes/" + config->m_appConfig.Theme + "/page/";
    string adminDir = config->m_rootFullPath + "/admin/";
    m_templateMap[key] = GetFile(dir, value, aTemp);
}

void SYTemplate::LoadTemplatePage(std::map<std::string, std::string> & tempMap){
    if(m_templateMap.size() == 0) return;
    map<string, string>::iterator iter;
    for (iter = tempMap.begin(); iter != tempMap.end(); iter++) {
        LoadTemplatePage(iter->first, iter->second);
    }
}

void SYTemplate::ReplaceTemplatePage(std::string & Html){
    
    string key;
    map<string, TEMPLATE>::iterator iter;
    
    for (iter = m_templateMap.begin(); iter != m_templateMap.end(); iter++) {
        
        key = "<#template" + iter->first;
        key += "#>";
        
        if (iter->second.templateCB) {
            string value = iter->second.value;
            if (value.length() > 0) {
                (this->*iter->second.templateCB)(value);
                StringReplace(Html, key, value);
            }
        } else {
            log_info("%s \r\n", key.c_str());
            StringReplace(Html, key, iter->second.value);
        }
        
        
    }
    
    
}

void SYTemplate::ReplaceSiteConfig(std::string & Html){
    
    SYSiteConfig * Config = SYSiteConfig::GetInstance();
    SITECONFIG siteConfig = Config->m_siteConfig;
    if (siteConfig.size() > 0) {
        SITECONFIG::iterator iter;
        for (iter = siteConfig.begin(); iter != siteConfig.end(); iter++) {
            std::string key = "<#";
            key += (*iter).first;
            key += "#>";
            StringReplace(Html, key, (*iter).second);
        }
    }
}

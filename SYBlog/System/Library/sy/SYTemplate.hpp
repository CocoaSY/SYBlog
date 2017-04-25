//
//  SYTemplate.hpp
//  SYBlog
//
//  Created by Cocoa on 4/19/17.
//  Copyright © 2017 Cocoa. All rights reserved.
//

#ifndef SYTemplate_hpp
#define SYTemplate_hpp

#include <stdio.h>
#include <string>
#include <map>

class SYTemplate;

typedef std::string(SYTemplate::*TEMPLATECB)(const std::string & Html);

typedef struct _TEMPLATE_{
    std::string value;
    TEMPLATECB templateCB;
} TEMPLATE;

class SYTemplate {
    
private:
    std::map<std::string, TEMPLATE> m_templateMap;
    
public:
    SYTemplate();
    ~SYTemplate();
    
    static SYTemplate * GetInstance();
    
public:
    void Init(std::map<std::string, std::string> & tempMap);
    bool BuiltHtmlByTemplateKey(const char * pKey,TEMPLATE & temp);
    const std::string GetTemplate(const char * pKey);
    void LoadTemplatePage(std::string key,std::string value);
    
private:
    TEMPLATE & GetFile(std::string fileDir,std::string fileName,TEMPLATE & temp,TEMPLATECB aCall = NULL);
    
    void LoadTemplatePage(std::map<std::string, std::string> & tempMap);
    void ReplaceTemplatePage(std::string & Html);
    
public:
    void ReplaceSiteConfig(std::string & Html);
    
};

#endif /* SYTemplate_hpp */

//
//  SYApp.hpp
//  SYBlog
//
//  Created by Cocoa on 4/19/17.
//  Copyright © 2017 Cocoa. All rights reserved.
//

#ifndef SYApp_hpp
#define SYApp_hpp

#include <stdio.h>
#include <event.h>
#include <event2/http.h>
#include <string>
#include <list>

#include "SYConstant.h"
#include "SYController.h"

class SYApp {

private:
    struct event_base   * m_base;
    struct evhttp       * m_http;
    
    std::list<SYController *> m_controllers;
    
public:
    uint64_t m_ssid_token;
    uint32_t m_startTime;
    char m_szDir[SIZE_1024];
    char uri_root[SIZE_1024];
    
    
public:
    SYApp();
    ~SYApp();
    
public:
    bool Init();
    void StartMySqlPool();
    
    void Version();
    
    bool StartHttpd();
    void SetRouteTable(evhttp * http);
    int BindSocket(const char * ip,uint16_t port);
    bool Run(const char * ip,uint16_t port,uint32_t timeout_secs,uint32_t nThreads);
    
    static void * Dispatch(void * arg);
    static void OnTimer();
    
    event_base * GetEventBase();
    
};




#endif /* SYApp_hpp */

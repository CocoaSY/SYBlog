//
//  SYApp.cpp
//  SYBlog
//
//  Created by Cocoa on 4/19/17.
//  Copyright © 2017 Cocoa. All rights reserved.
//

#include "SYApp.hpp"

#include <signal.h>
#include <map>
#include <arpa/inet.h>
#include <sys/socket.h>

#include "SYLog.hpp"
#include "SYTemplate.hpp"
#include "SYIniConfig.hpp"
#include "SYMysqlPool.hpp"

#include "IndexController.hpp"
#include "CategoryController.hpp"
#include "PostController.hpp"

SYApp::SYApp(){
    memset(m_szDir, 0, sizeof(m_szDir));
    if (signal(SIGPIPE, SIG_IGN) == SIG_ERR) {
        log_error("void SYApp::SYApp() SIGPIPE error\n");
    }
}

SYApp::~SYApp(){
    
}

bool SYApp::Init(){
    
    m_startTime = uint32_t(time(NULL));
    strncpy(m_szDir, SYIniConfig::GetInstance()->m_rootFullPath.c_str(), SYIniConfig::GetInstance()->m_rootFullPath.length());
    
    return true;
}

void SYApp::StartMySqlPool(){
    
    SYMysqlPool *pMysqlPool = SYMysqlPool::GetInstance();
    SYIniConfig *pConfig = SYIniConfig::GetInstance();
    pMysqlPool->Init(pConfig->m_mysqlConfig.ipaddr.c_str(),
                     pConfig->m_mysqlConfig.username.c_str(),
                     pConfig->m_mysqlConfig.password.c_str(),
                     pConfig->m_mysqlConfig.dbname.c_str());
    
    bool ret = pMysqlPool->ConnectDB(pConfig->m_mysqlConfig.poolsize);
    if (!ret)
    {
        log_error("App::StartMysqlPool() error, exit\r\n");
        exit(0);
    }
}

void SYApp::Version(){
    
    log_info("APP version=%s evHttpd=%s:%d bits=%d\n",
             "0.0.1",
             event_get_version(),
             (int)event_get_version_number(),
             sizeof(long) == 4 ? 32 : 64);
}

bool SYApp::StartHttpd(){
    
    return false;
}

void SYApp::SetRouteTable(evhttp * http){
    
    // TODO ...
    SYController * index = new IndexController;
    SYController * category = new CategoryController;
    SYController * post = new PostController;
    m_controllers.push_back(index);
    m_controllers.push_back(category);
    m_controllers.push_back(post);
    
    std::list<SYController *>::iterator iter;
    for (iter = m_controllers.begin(); iter != m_controllers.end(); iter++) {
        (*iter)->SetRoute(http);
    }
    
    evhttp_set_timeout(http, SYIniConfig::GetInstance()->m_appConfig.HTTPTimeout);
}

int SYApp::BindSocket(const char * ip,uint16_t port){
    
    int skt;
    skt = socket(AF_INET, SOCK_STREAM, 0);
    
    if (skt < 0) {
        log_error("socket error, nfd=%d \r\n", skt);
        return -1;
    }
    
    /* set socket nonblocking */
    int flags;
    if ((flags = fcntl(skt, F_GETFL, NULL)) < 0 || fcntl(skt, F_SETFL, flags | O_NONBLOCK) == -1)
    {
        log_error("O_NONBLOCK  error, skt=%d \r\n", skt);
        return -1;
    }
    
    /* set socket closeonexec */
    if ((flags = fcntl(skt, F_GETFD, NULL)) < 0 || fcntl(skt, F_SETFD, flags | FD_CLOEXEC) == -1)
    {
        log_error("FD_CLOEXEC  error, skt=%d \r\n", skt);
        return -1;
    }
    
    int on = 1;
    setsockopt(skt, SOL_SOCKET, SO_KEEPALIVE, (const char *) &on, sizeof(on));
    setsockopt(skt, SOL_SOCKET, SO_REUSEADDR, (const char *) &on, sizeof(on));
    
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip);
    addr.sin_port = htons(port);
    
    if (bind(skt, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        log_error("bind %s %d error\r\n", ip, port);
        return -1;
    }
    
    if (listen(skt, 128) < 0) {
        log_error("listen %s %d error\r\n", ip, port);
        return -1;
    }
    
    return skt;
    
}

bool SYApp::Run(const char * ip,uint16_t port,uint32_t timeout_secs,uint32_t nThreads){
    
    int ret = -1;
    int skt = BindSocket(ip, port);
    
    if (skt < 0) {
        log_error("BindSocket %s %d error\r\n", ip, port);
        return false;
    }
    
    pthread_t ths[128];
    for (uint32_t i = 0; i < nThreads; i++) {
        
        struct event_base * base = event_base_new();
        if(base == NULL) return false;
        
        struct evhttp * httpd = evhttp_new(base);
        if(httpd == NULL) return false;
        
        ret = evhttp_accept_socket(httpd, skt);
        if(ret != 0) return false;
        
        SetRouteTable(httpd);
        
        ret = pthread_create(&ths[i], NULL, SYApp::Dispatch, base);
        log_info("%d %d \r\n", i, ths[i]);
        if (ret != 0)
        {
            return false;
        }
        
    }
    
    return true;
}

void * SYApp::Dispatch(void * arg){
    if (arg == NULL) {
        log_error("error arg is null\n");
        return NULL;
    }
    
    event_base_dispatch((struct event_base *)arg);
    return NULL;
}

void SYApp::OnTimer(){
    
}

event_base * SYApp::GetEventBase(){
    return m_base;
}


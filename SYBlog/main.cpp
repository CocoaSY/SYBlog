//
//  main.cpp
//  SYBlog
//
//  Created by Cocoa on 4/18/17.
//  Copyright © 2017 Cocoa. All rights reserved.
//

#include <iostream>
#include "SYApp.hpp"
#include "SYIniConfig.hpp"
#include "SYLog.hpp"
#include "SYMysqlPool.hpp"

int main(int argc, const char * argv[]) {
    
    SYIniConfig * config = SYIniConfig::GetInstance();
    config->Init("Config.ini");
    
    LOGGER.setFileName(config->m_appConfig.LogFileName.c_str());    // 设置日志文件
    LOGGER.setLogLevel(config->m_appConfig.LogLevel.c_str());       // 设置日志等级
    LOGGER.setMaxFileSize(1<<23);                                   // 设置日志文件大小
    
    
    log_info("Listen on: %s %u\n", config->m_appConfig.ServerIP.c_str(),config->m_appConfig.Port);
    
    log_info("MYSQL: %s:%u %s/%s dbname:%s poolsize:%d \n",
             config->m_mysqlConfig.ipaddr.c_str(),
             config->m_mysqlConfig.port,
             config->m_mysqlConfig.username.c_str(),
             config->m_mysqlConfig.password.c_str(),
             config->m_mysqlConfig.dbname.c_str(),
             config->m_mysqlConfig.poolsize );
    
    SYApp app;
    app.Version();
    app.StartMySqlPool();
    app.Init();
    
    bool ret = app.Run(config->m_appConfig.ServerIP.c_str(),
                       config->m_appConfig.Port,
                       config->m_appConfig.HTTPTimeout,
                       config->m_appConfig.HTTPThreads);
    
    if(!ret){
        log_info("App run error \n");
        exit(1);
    }
    
    while (true) {
        app.OnTimer();
        sleep(1);
        SYMysqlPool::GetInstance()->KeepAlive();
    }
    
    return 0;
}

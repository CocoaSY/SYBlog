//
//  SYMysqlPool.hpp
//  xBlog
//
//  Created by Cocoa on 4/11/17.
//  Copyright © 2017 Cocoa. All rights reserved.
//

#ifndef SYMysqlPool_hpp
#define SYMysqlPool_hpp

const int MAX_CONNECTION_NUM = 128;

#include <stdio.h>
#include <string>
#include <mysql.h>
#include <list>

#include "SYLock.hpp"
#include "json.h"
#include "SYUntil.hpp"

typedef std::list<MYSQL *> CONNECTION_HANDLE_LIST;
typedef std::list<MYSQL *>::iterator ITER_CONNECTION_HANDLE_LIST;

#ifdef MYDLL_EXPORTS
#define MYDLL_API __declspec(dllexport)
#else
#define MYDLL_API __declspec(dllimport)
#endif

class SYMysqlPool {

public:
    SYMysqlPool();
    ~SYMysqlPool();
    
    static SYMysqlPool * GetInstance();
    
    void Init(const char *host,const char *user,const char *password,const char *db,unsigned int port = 3306);
    
public:
    bool ConnectDB(uint16 poolsize);
    MYSQL_RES * Select(const char * sqlString);
    bool Execute(const char * sqlString);
    bool SelectJson(const char * sqlString,std::string & result);
    
    void FreeRecord(MYSQL_RES * mysqlRes);
    unsigned int GetFieldNum(MYSQL_RES * mysqlRes);
    MYSQL_ROW GetRecord(MYSQL_RES * mysqlRes);
    my_ulonglong GetRowNum(MYSQL_RES * mysqlRes);
    
    //char * GetErrorString(MYSQL * pMySql);
    bool SetCharacterset(MYSQL * pMySql,const char * character);
    void KeepAlive();
    
    MYSQL * GetConnection();
    void FreeConnection(MYSQL * pMySql);
    
private:
    CONNECTION_HANDLE_LIST * m_mysqlConnList;
    SYLock m_lock;
    
private:
    const char * m_host;
    const char * m_user;
    const char * m_password;
    const char * m_database;
    uint16       m_port;
    
    
};





#endif /* SYMysqlPool_hpp */

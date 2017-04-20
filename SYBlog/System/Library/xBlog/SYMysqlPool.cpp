//
//  SYMysqlPool.cpp
//  xBlog
//
//  Created by Cocoa on 4/11/17.
//  Copyright © 2017 Cocoa. All rights reserved.
//

#include "SYMysqlPool.hpp"
#include "SYLog.hpp"

using namespace std;

SYMysqlPool::SYMysqlPool(){
    
}

SYMysqlPool::~SYMysqlPool(){
    SYLOCK(m_lock);
    ITER_CONNECTION_HANDLE_LIST iter = m_mysqlConnList->begin();
    while (iter != m_mysqlConnList->end()) {
        mysql_close( *iter );
        iter++;
    }
}

SYMysqlPool * SYMysqlPool::GetInstance(){
    static SYMysqlPool gMySqlPool;
    return &gMySqlPool;
}

void SYMysqlPool::Init(const char *host,const char *user,const char *password,const char *db,unsigned int port){
    m_mysqlConnList = new CONNECTION_HANDLE_LIST;
    m_host = host;
    m_user = user;
    m_password = password;
    m_database = db;
    m_port = port;
}


bool SYMysqlPool::ConnectDB(uint16 poolsize){
    try {
        if(poolsize > MAX_CONNECTION_NUM) poolsize = MAX_CONNECTION_NUM;
        for (int i = 0; i < poolsize; i++) {
            // MYSQL *pMysql = new MYSQL;
            // mysql_init( pMysql );
            MYSQL *pMysql = mysql_init((MYSQL *)NULL);
            if (pMysql != NULL) {
                
                if ( !mysql_real_connect(pMysql, m_host, m_user, m_password, m_database, m_port, NULL, CLIENT_MULTI_RESULTS) ) {
                    log_error("MysqlPool::ConnectDB  ERROR %s \n", mysql_error(pMysql));
                    return false;
                } else {
                    SetCharacterset(pMysql, "UTF8");
                    my_bool my_true = true;
                    mysql_options(pMysql, MYSQL_OPT_RECONNECT, &my_true);
                    log_info("%d connect to %s %s %s %s %u success !\n",
                             i, m_host, m_user, m_password, m_database, m_port);
                    m_mysqlConnList->push_back(pMysql);
                }
            } else {
                log_error("MysqlPool: Mysql init  ERROR %s \n", mysql_error(pMysql));
                return false;
            }
        }
    } catch (...) {
        log_error("connect error  poolsize=%d \n", poolsize);
        return false;
    }
    return true;
}

MYSQL_RES * SYMysqlPool::Select(const char * sqlString){
    //log_debug("MysqlPool::Select %s\n", sqlString);
    LOGGER.logMessage(LOG_LEVEL(DEBUG), "MysqlPool::Select %s\n", sqlString);
    MYSQL *pMySql = GetConnection();
    if(pMySql == NULL) return NULL;
    
    if (mysql_real_query(pMySql, sqlString, strlen(sqlString)) != 0) {
        log_error("MysqlPool::SelectRecord %s\n", mysql_error(pMySql));
        FreeConnection(pMySql);
        return NULL;
    }
    
    MYSQL_RES *mysqlRes = NULL;
    mysqlRes = mysql_store_result(pMySql);
    FreeConnection(pMySql);
    
    return mysqlRes;
}

bool SYMysqlPool::Execute(const char * sqlString){
    //log_debug("MysqlPool::Execute %s\n", sqlString); /** Something wrong with it. */
    LOGGER.logMessage(LOG_LEVEL(DEBUG), "MysqlPool::Execute %s\n", sqlString);
    
    bool bRet = false;
    MYSQL *pMySql = GetConnection();
    
    if(pMySql == NULL) return false;
    
    if (!mysql_real_query(pMySql, sqlString, strlen(sqlString))) {
        LOGGER.logMessage(LOG_LEVEL(DEBUG), "MysqlPool::Execute %s\n", sqlString);
        bRet = true;
    } else {
        LOGGER.logMessage(LOG_LEVEL(DEBUG), "MysqlPool::Execute %s\n", sqlString);
        log_error("MysqlPool::Execute %s\n", mysql_error(pMySql));
    }
    FreeConnection(pMySql);
    return bRet;
}

bool SYMysqlPool::SelectJson(const char * sqlString,string & result){
    result = "jsonpcallback(";
    bool bRet = false;
    Json::Value root;
    
    MYSQL *pMySql = GetConnection();
    if (pMySql == NULL) {
        root["errno"] = mysql_errno(pMySql);
        root["error"] = mysql_error(pMySql);
        root["affected"] = mysql_affected_rows(pMySql);
        return false;
    }
    
    LOGGER.logMessage(LOG_LEVEL(DEBUG), "MysqlPool::SelectJson %s \r\n", sqlString);
    if (mysql_real_query(pMySql, sqlString, strlen(sqlString))) {
        log_error("MysqlPool::SelectJson %s\n", mysql_error(pMySql));
        goto end;
    } else {
        
        MYSQL_RES *pRes = mysql_store_result(pMySql);
        if (pRes) {
            MYSQL_FIELD *field;
            Json::Value fieldList;
            int num_rows = (int)mysql_num_rows(pRes);
            int num_fields = mysql_num_fields(pRes);
            map<int, string> fieldsMap;
            
            LOGGER.logMessage(LOG_LEVEL(DEBUG), "MysqlPool::SelectJson fields=%d result: %d \r\n", num_fields, num_rows);
            root["num"] = num_rows;
            
            for (int i = 0; i < num_fields; i++) {
                field = mysql_fetch_field_direct(pRes, i);
                fieldsMap[i] = field->name;
                LOGGER.logMessage(LOG_LEVEL(DEBUG), "%s\t", field->name);
                fieldList.append(field->name);
            }
            LOGGER.logMessage(LOG_LEVEL(DEBUG), "MysqlPool::SelectJson \r\n");
            
            MYSQL_ROW row = mysql_fetch_row(pRes);
            
            Json::Value Result;
            Json::Value DataList;
            
            Result["field"] = fieldList;
            
            while (row) {
                Json::Value item;
                for (int i = 0; i < num_fields; i++) {
                    LOGGER.logMessage(LOG_LEVEL(DEBUG), "%s \t", row[i]);
                    if (row[i]) {
                        item.append(row[i]);
                    } else {
                        item.append("null");
                    }
                }
                DataList.append(item);
                row = mysql_fetch_row(pRes);
            }
            Result["xdata"] = DataList;
            mysql_free_result(pRes);
            root["result"] = Result;
            bRet = true;
            
        } else {
            LOGGER.logMessage(LOG_LEVEL(DEBUG), "MysqlPool::SelectJson MYSQL_RES %s \r\n", mysql_error(pMySql));
        }
        
        
    }
    
end:
    root["errno"] = mysql_errno(pMySql);
    root["error"] = mysql_error(pMySql);
    root["affected"] = mysql_affected_rows(pMySql);
    LOGGER.logMessage(LOG_LEVEL(DEBUG), "MysqlPool::SelectJson affected=%lld \r\n", mysql_affected_rows(pMySql));
    
    Json::FastWriter writer;
    result += writer.write(root);
    FreeConnection(pMySql);
    
    result += ")";
    return bRet;
}

void SYMysqlPool::FreeRecord(MYSQL_RES * mysqlRes){
    mysql_free_result(mysqlRes);
}

unsigned int SYMysqlPool::GetFieldNum(MYSQL_RES * mysqlRes){
    return mysql_num_fields(mysqlRes);
}

MYSQL_ROW SYMysqlPool::GetRecord(MYSQL_RES * mysqlRes){
    return mysql_fetch_row(mysqlRes);
}

my_ulonglong SYMysqlPool::GetRowNum(MYSQL_RES * mysqlRes){
    return mysql_num_rows(mysqlRes);
}

bool SYMysqlPool::SetCharacterset(MYSQL * pMySql,const char * character){
    int nRet = mysql_set_character_set(pMySql, character);
    if (nRet != 0) {
        log_error("%s\n", mysql_error(pMySql));
        return false;
    }
    
    log_info("SetCharacterset %s\n", character);
    return true;
}

void SYMysqlPool::KeepAlive(){
    
    SYLock(m_lock);
    ITER_CONNECTION_HANDLE_LIST iter = m_mysqlConnList->begin();
    for (; iter != m_mysqlConnList->end(); iter++) {
        mysql_ping( *iter );
    }
}

MYSQL * SYMysqlPool::GetConnection(){
    MYSQL *pMySql = NULL;
    
    while (1) {
        
        {
            SYLock(m_lock);
            if (m_mysqlConnList->size() > 0) {
                pMySql = m_mysqlConnList->front();
                m_mysqlConnList->pop_front();
                break;
            } else {
                log_info("MysqlPool::GetIdleMySql()  error id=%d \n", pthread_self());
            }
        }
        
        usleep(10 * 1000);
        
    }
    
    return pMySql;
    
}

void SYMysqlPool::FreeConnection(MYSQL * pMySql){
    SYLock(m_lock);
    m_mysqlConnList->push_back(pMySql);
}

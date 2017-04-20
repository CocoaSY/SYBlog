//
//  PostsModel.cpp
//  SYBlog
//
//  Created by Cocoa on 4/20/17.
//  Copyright © 2017 Cocoa. All rights reserved.
//

#include "PostsModel.hpp"
#include "SiteConfigModel.hpp"


ARTICLE_MULTI_LIST PostsModel::GetArticleMultiList(uint32_t page){
    
    ARTICLE_MULTI_LIST list;
    
    SiteConfigModel siteConfig;
    
    uint32 num = atoul(siteConfig.GetSiteConfig("SITE_MAX_VIEW").c_str());
    uint32 start = (page == 0)? 0 : page * num;
    
    char szSQL[SIZE_1024] = {0};
    snprintf(szSQL, SIZE_1024, "SELECT ID,post_title,post_date,post_brief,post_url \
                                FROM `sy_posts` \
                                WHERE post_status='publish' ORDER BY post_date DESC LIMIT %d,%d ",start,num);
    
    m_mysqlPool->Select(szSQL);
    
    MYSQL_RES *pRes = m_mysqlPool->Select(szSQL);
    if (pRes != NULL) {
        
        
        MYSQL_ROW row;
        while ( (row = mysql_fetch_row(pRes)) ) {
            ARTICLE_MULTI_ITEM item;
            item.ID = row[0];
            item.title = row[1];
            item.date = row[2];
            item.intro = row[3];
            item.url = row[4];
            list.push_back(item);
        }
        m_mysqlPool->FreeRecord(pRes);
    }
    
    return list;
}

ARTICLE_MULTI_LIST PostsModel::GetArticleMultiList(uint32_t cate,uint32_t page){
    
    ARTICLE_MULTI_LIST list;
    
    SiteConfigModel siteConfig;
    
    uint32 num = atoul(siteConfig.GetSiteConfig("SITE_MAX_VIEW").c_str());
    uint32 start = (page == 0)? 0 : page * num;
    
    char szSQL[SIZE_1024] = {0};
    snprintf(szSQL, SIZE_1024, "SELECT ID,post_title,post_date,post_brief,post_url,post_classify \
             FROM `sy_posts` \
             WHERE post_status='publish' AND post_classify = %d \
             ORDER BY post_date DESC LIMIT %d,%d ",cate,start,num);
    
    MYSQL_RES * pRes = m_mysqlPool->Select(szSQL);
    if (pRes != NULL) {
        MYSQL_ROW row;
        while ( (row = mysql_fetch_row(pRes)) ) {
            ARTICLE_MULTI_ITEM item;
            item.ID = row[0];
            item.title = row[1];
            item.date = row[2];
            item.intro = row[3];
            item.url = row[4];
            list.push_back(item);
        }
    }
    
    return list;
}
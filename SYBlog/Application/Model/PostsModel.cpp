//
//  PostsModel.cpp
//  SYBlog
//
//  Created by Cocoa on 4/20/17.
//  Copyright © 2017 Cocoa. All rights reserved.
//

#include "PostsModel.hpp"
#include "SYSiteConfig.hpp"

ARTICLE_MULTI_LIST PostsModel::GetArticleMultiList(uint32_t page){
    
    ARTICLE_MULTI_LIST list;
    
    SYSiteConfig * siteConfig = SYSiteConfig::GetInstance();
    
    uint32 num = atoul(siteConfig->GetSiteConfig("SITE_MAX_VIEW").c_str());
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
    
    SYSiteConfig * siteConfig = SYSiteConfig::GetInstance();
    
    uint32 num = atoul(siteConfig->GetSiteConfig("SITE_MAX_VIEW").c_str());
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

POST PostsModel::GetArticle(uint32_t postID){
    
    POST aPost;
    
    char szSQL[SIZE_1024] = {0};
    snprintf(szSQL, SIZE_1024, "SELECT ID,post_author,post_date,post_content,post_brief,post_title, \
                                post_status,post_classify,comment_status,post_modified,post_url,comment_count \
                                FROM sy_posts \
                                WHERE ID=%d",postID);
    
    MYSQL_RES * pRes = m_mysqlPool->Select(szSQL);
    if (pRes != NULL) {
        MYSQL_ROW row;
        while ( (row = mysql_fetch_row(pRes)) ) {
            
            aPost.ID = row[0];
            aPost.author = row[1];
            aPost.date = row[2];
            aPost.content = row[3];
            aPost.brief = row[4];
            aPost.title = row[5];
            aPost.status = row[6];
            aPost.classify = row[7];
            aPost.comment_status = row[8];
            aPost.modified = row[9];
            aPost.url = row[10];
            aPost.comment_count = row[11];
            
        }
        
        m_mysqlPool->FreeRecord(pRes);
    }
    
    return aPost;
}
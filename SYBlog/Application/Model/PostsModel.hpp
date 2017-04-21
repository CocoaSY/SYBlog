//
//  PostsModel.hpp
//  SYBlog
//
//  Created by Cocoa on 4/20/17.
//  Copyright © 2017 Cocoa. All rights reserved.
//

#ifndef PostsModel_hpp
#define PostsModel_hpp

#include <stdio.h>
#include <list>

#include "SYModel.h"

typedef struct _POST_ {
    std::string ID;
    std::string author;
    std::string date;
    std::string content;
    std::string brief;
    std::string title;
    std::string status;
    std::string classify;
    std::string comment_status;
    std::string modified;
    std::string url;
    std::string comment_count;
} POST;

typedef std::list<POST> POSTLIST;

typedef struct _ARTICLE_MULTI_ITEM_ {
    std::string ID;
    std::string title;
    std::string date;
    std::string intro;
    std::string url;
} ARTICLE_MULTI_ITEM;

typedef std::list<ARTICLE_MULTI_ITEM> ARTICLE_MULTI_LIST;

class PostsModel : public SYModel {
    
public:
    ARTICLE_MULTI_LIST GetArticleMultiList(uint32_t page);
    ARTICLE_MULTI_LIST GetArticleMultiList(uint32_t cate,uint32_t page);
    
    POST GetArticle(uint32_t postID);
    
};

#endif /* PostsModel_hpp */

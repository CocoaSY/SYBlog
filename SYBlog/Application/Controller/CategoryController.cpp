//
//  CategoryController.cpp
//  SYBlog
//
//  Created by Cocoa on 4/20/17.
//  Copyright © 2017 Cocoa. All rights reserved.
//

#include <stdlib.h>
#include "CategoryController.hpp"
#include "SYApp.hpp"
#include "PostsModel.hpp"
#include "ArticleMultiView.hpp"
#include "CatalogView.hpp"

using namespace std;

void CategoryController::SetRoute(evhttp *http){
    evhttp_set_cb(http, "/catalog", CategoryRequestCallback, NULL);
}

void CategoryController::CategoryRequestCallback(struct evhttp_request *req, void *arg){
    
    // 加载导航栏模板
    string navHTML = HeaderHtml();
    
    // 加载文章列表
    SYRequest request(req);
    const char * cateID = request.Get("cate");
    const char * pageID = request.Get("page");
    
    uint32_t cid = atoi(cateID);
    uint32_t pid = atoi(pageID);
    
    PostsModel postModel;
    ArticleMultiView articleMultiView;
    ARTICLE_MULTI_LIST posts = postModel.GetArticleMultiList(cid, pid);
    string articleMultiHtml = "";
    if (posts.size() > 0) {
        ARTICLE_MULTI_LIST::iterator iter;
        for (iter = posts.begin(); iter != posts.end(); iter++) {
            articleMultiView.SetArticleMultiItem(*iter);
            articleMultiHtml += articleMultiView.GetArticleMultiHtml().value;
        }
    }
    
    // 加载分类页面
    CatalogView catalogView;
    catalogView.SetNavTemplate(navHTML);
    catalogView.SetArticleMultiTemplate(articleMultiHtml);
    TEMPLATE html = catalogView.GetCatalogHtml();
    
    // 发送页面给浏览器
    SYResponse response(req);
    response.SendHttpResponse(html.value);
    
}

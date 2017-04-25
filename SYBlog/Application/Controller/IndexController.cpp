//
//  IndexController.cpp
//  SYBlog
//
//  Created by Cocoa on 4/19/17.
//  Copyright © 2017 Cocoa. All rights reserved.
//

#include "IndexController.hpp"

#include <event2/http.h>

#include "SYApp.hpp"
#include "SYLog.hpp"

#include "ClassifyModel.hpp"
#include "NavView.hpp"
#include "PostsModel.hpp"
#include "ArticleMultiView.hpp"
#include "DefaultView.hpp"

using namespace std;

void IndexController::SetRoute(evhttp *http){
    evhttp_set_cb(http, "/", IndexRequestCallback, NULL);
}

void IndexController::IndexRequestCallback(struct evhttp_request *req, void *arg){
    SYRequest request(req);
    request.HttpDebug();
    RequestPage(req, NULL);
}

void IndexController::RequestPage(struct evhttp_request *req, const char *PageId){
        
    // 加载导航栏 HTML
    string navHtml = HeaderHtml();
    
    // 加载首页列表模板
    PostsModel postsModel;
    ArticleMultiView articleMultiView;
    
    ARTICLE_MULTI_LIST articleList= postsModel.GetArticleMultiList(0);
    string articleMultiHtml = "";
    ARTICLE_MULTI_LIST::iterator iter2;
    for (iter2 = articleList.begin(); iter2 != articleList.end(); iter2++) {
        ARTICLE_MULTI_ITEM item = (*iter2);
        articleMultiView.SetArticleMultiItem(item);
        articleMultiHtml += articleMultiView.GetArticleMultiHtml().value;
    }
    
    // 加载默认页面模板
    DefaultView defaultView;
    defaultView.SetNavTemplate(navHtml);
    defaultView.SetArticleMultiTemplate(articleMultiHtml);
    TEMPLATE HtmlTemplate = defaultView.GetDefaultHtml();
    
    // 发送页面到浏览器
    SYApp::SendHttpResponse(req, HtmlTemplate.value);
    
}
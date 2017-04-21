//
//  PostController.cpp
//  SYBlog
//
//  Created by Cocoa on 4/21/17.
//  Copyright © 2017 Cocoa. All rights reserved.
//

#include "PostController.hpp"

#include "SYApp.hpp"
#include "PostsModel.hpp"
#include "ArticleSingleView.hpp"
#include "SingleView.hpp"

void PostController::Rewrite(std::string link){
    
}

void PostController::SetRoute(evhttp * http){
    evhttp_set_cb(http, "/post", PostRequestCallback, NULL);
}

void PostController::PostRequestCallback(struct evhttp_request *req, void *arg){
    
    // 加载导航栏
    std::string navHtml = HeaderHtml();
    
    // 加载文章内容
    SYApp::HttpDebug(req);
    
    evkeyvalq GetData;
    SYApp::HttpParseUrl(req, &GetData);
    const char * postID = evhttp_find_header(&GetData, "id");
    
    
    PostsModel postModel;
    POST aPost = postModel.GetArticle(atoul(postID));
    ArticleSingleView articleSingle;
    articleSingle.SetPost(aPost);
    std::string articleSingleHtml = articleSingle.GetArticleSingleHtml().value;
    
    // 加载页面内容
    SingleView singleView;
    singleView.SetNavHtml(navHtml);
    singleView.SetArticleSingleHtml(articleSingleHtml);
    
    SYApp::SendHttpResponse(req, singleView.GetSingleHtml().value);
    
}
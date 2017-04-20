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
#include "SYTemplate.hpp"
#include "SYLog.hpp"

IndexController::IndexController(){
    
}

IndexController::~IndexController(){
    
}

void IndexController::Rewrite(std::string link){
    
}

void IndexController::SetRoute(evhttp *http){
    evhttp_set_cb(http, "/", IndexRequestCallback, NULL);
}

void IndexController::IndexRequestCallback(struct evhttp_request *req, void *arg){
    SYApp::HttpDebug(req);
    RequestPage(req, NULL);
}

void IndexController::RequestPage(struct evhttp_request *req, const char *PageId){
    
    // 加载默认页面模板
    TEMPLATE HtmlTemplate;
    SYTemplate::GetInstance()->BuiltHtmlByTemplateKey(K_DEFAULT, HtmlTemplate);
    
    // 发送页面到浏览器
    SYApp::SendHttpResponse(req, HtmlTemplate.value);
    
}
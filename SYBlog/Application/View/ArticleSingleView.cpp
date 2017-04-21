//
//  ArticleSingleView.cpp
//  SYBlog
//
//  Created by Cocoa on 4/21/17.
//  Copyright © 2017 Cocoa. All rights reserved.
//

#include "ArticleSingleView.hpp"


ArticleSingleView::ArticleSingleView(){
    
    m_replacingFrom.title = "<#article/title#>";
    m_replacingFrom.content = "<#article/content#>";
    m_replacingFrom.categoryName = "<#article/category/name#>";
    m_replacingFrom.authorName = "<#article/author/name#>";
    m_replacingFrom.postTime = "<#article/posttime#>";
    
    m_template->LoadTemplatePage(K_ARTICLE_SINGLE, V_ARTICLE_SINGLE);
    
}

void ArticleSingleView::SetPost(POST aPost){
    m_replacingTo.title = aPost.title;
    m_replacingTo.content = aPost.content;
    m_replacingTo.postTime = aPost.date;
}

TEMPLATE ArticleSingleView::GetArticleSingleHtml(){
    
    TEMPLATE temp;
    
    m_template->BuiltHtmlByTemplateKey(K_ARTICLE_SINGLE, temp);
    
    if (m_replacingTo.title.length() > 0) {
        StringReplace(temp.value, m_replacingFrom.title, m_replacingTo.title);
        m_replacingTo.title = "";
    }
    
    if (m_replacingTo.content.length() > 0) {
        StringReplace(temp.value, m_replacingFrom.content, m_replacingTo.content);
        m_replacingTo.content = "";
    }
    
    if (m_replacingTo.categoryName.length() > 0) {
        StringReplace(temp.value, m_replacingFrom.categoryName, m_replacingTo.categoryName);
        m_replacingTo.categoryName = "";
    }
    
    if (m_replacingTo.authorName.length() > 0) {
        StringReplace(temp.value, m_replacingFrom.authorName, m_replacingTo.authorName);
        m_replacingTo.authorName = "";
    }
    
    if (m_replacingTo.postTime.length() > 0) {
        StringReplace(temp.value, m_replacingFrom.postTime, m_replacingTo.postTime);
        m_replacingTo.postTime = "";
    }
    
    
    return temp;
}
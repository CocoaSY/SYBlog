//
//  ArticleMultiView.cpp
//  SYBlog
//
//  Created by Cocoa on 4/20/17.
//  Copyright © 2017 Cocoa. All rights reserved.
//

#include "ArticleMultiView.hpp"

ArticleMultiView::ArticleMultiView(){
    m_replacingFrom.title = "<#article/title#>";
    m_replacingFrom.date = "<#article/posttime/longdate#>";
    m_replacingFrom.intro = "<#article/intro#>";
    m_replacingFrom.url = "<#article/url#>";
    
    m_template->LoadTemplatePage(K_ARTICLE_MULTI, V_ARTICLE_MULTI);
}

void ArticleMultiView::SetArticleMultiItem(ARTICLE_MULTI_ITEM item){
    m_replacingTo.title = item.title;
    m_replacingTo.date = item.date;
    m_replacingTo.intro = item.intro;
    m_replacingTo.url = item.url;
}

TEMPLATE ArticleMultiView::GetArticleMultiHtml(){
    
    TEMPLATE temp;
    m_template->BuiltHtmlByTemplateKey(K_ARTICLE_MULTI, temp);
    
    if (m_replacingTo.title.length() > 0) {
        StringReplace(temp.value, m_replacingFrom.title, m_replacingTo.title);
        m_replacingTo.title = "";
    }
    
    if (m_replacingTo.date.length() > 0) {
        StringReplace(temp.value, m_replacingFrom.date, m_replacingTo.date);
        m_replacingTo.date = "";
    }
    
    if (m_replacingTo.intro.length() > 0) {
        StringReplace(temp.value, m_replacingFrom.intro, m_replacingTo.intro);
        m_replacingTo.intro = "";
    }
    
    if (m_replacingTo.url.length() > 0) {
        StringReplace(temp.value, m_replacingFrom.url, m_replacingTo.url);
        m_replacingTo.url = "";
    }
    
    return temp;
}
//
//  SingleView.cpp
//  SYBlog
//
//  Created by Cocoa on 4/21/17.
//  Copyright © 2017 Cocoa. All rights reserved.
//

#include "SingleView.hpp"


SingleView::SingleView(){
    
    m_replacingFrom.nav = "<#template:nav#>";
    m_replacingFrom.article_single = "<#template:article_single#>";
    
    m_template->LoadTemplatePage(K_SINGLE, V_SINGLE);
}

void SingleView::SetNavHtml(std::string navHtml){
    m_replacingTo.nav = navHtml;
}

void SingleView::SetArticleSingleHtml(std::string articleSingleHtml){
    m_replacingTo.article_single = articleSingleHtml;
}

TEMPLATE SingleView::GetSingleHtml(){
    
    TEMPLATE temp;
    
    m_template->BuiltHtmlByTemplateKey(K_SINGLE, temp);
    
    if (m_replacingTo.nav.length() > 0) {
        StringReplace(temp.value, m_replacingFrom.nav, m_replacingTo.nav);
        m_replacingTo.nav = "";
    } else {
        StringReplace(temp.value, m_replacingFrom.nav, "");
    }
    
    if (m_replacingTo.article_single.length() > 0) {
        StringReplace(temp.value, m_replacingFrom.article_single, m_replacingTo.article_single);
        m_replacingTo.article_single = "";
    } else {
        StringReplace(temp.value, m_replacingFrom.article_single, "");
    }
    
    
    return temp;
}
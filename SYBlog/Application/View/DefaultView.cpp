//
//  DefaultView.cpp
//  SYBlog
//
//  Created by Cocoa on 4/20/17.
//  Copyright © 2017 Cocoa. All rights reserved.
//

#include "DefaultView.hpp"
#include "SYConstant.h"

DefaultView::DefaultView() : SYView(){
    m_replacingFrom.nav = "<#template:nav#>";
    m_replacingFrom.articleMulti = "<#template:article_multi#>";
    
    m_template->LoadTemplatePage(K_DEFAULT, V_DEFAULT);
}

void DefaultView::SetNavTemplate(std::string navTemplate){
    m_replacingTo.nav = navTemplate;
}

void DefaultView::SetArticleMultiTemplate(std::string articleMultiTemplate){
    m_replacingTo.articleMulti = articleMultiTemplate;
}

TEMPLATE DefaultView::GetDefaultHtml(){
    TEMPLATE temp;
    m_template->BuiltHtmlByTemplateKey(K_DEFAULT, temp);
    if (m_replacingTo.nav.length() > 0) {
        StringReplace(temp.value, m_replacingFrom.nav, m_replacingTo.nav);
        m_replacingTo.nav = "";
    }
    
    if (m_replacingTo.articleMulti.length() > 0) {
        StringReplace(temp.value, m_replacingFrom.articleMulti, m_replacingTo.articleMulti);
        m_replacingTo.articleMulti = "";
    } else {
        StringReplace(temp.value, m_replacingFrom.articleMulti, "");
    }
    
    m_template->ReplaceSiteConfig(temp.value);
    
    return temp;
}
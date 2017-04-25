//
//  CatalogView.cpp
//  SYBlog
//
//  Created by Cocoa on 4/20/17.
//  Copyright © 2017 Cocoa. All rights reserved.
//

#include "CatalogView.hpp"


CatalogView::CatalogView(){
    
    m_replacingFrom.nav = "<#template:nav#>";
    m_replacingFrom.articleMulti = "<#template:article_multi#>";
    
    m_template->LoadTemplatePage(K_CATALOG, V_CATALOG);
}

void CatalogView::SetNavTemplate(std::string navHtml){
    m_replacingTo.nav = navHtml;
}

void CatalogView::SetArticleMultiTemplate(std::string articleMultiHtml){
    m_replacingTo.articleMulti = articleMultiHtml;
}

TEMPLATE CatalogView::GetCatalogHtml(){
    
    TEMPLATE temp;
    m_template->BuiltHtmlByTemplateKey(K_CATALOG, temp);
    
    if (m_replacingTo.nav.length() > 0) {
        StringReplace(temp.value, m_replacingFrom.nav, m_replacingTo.nav);
        m_replacingTo.nav = "";
    } else {
        StringReplace(temp.value, m_replacingFrom.nav, "");
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
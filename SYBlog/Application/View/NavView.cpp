//
//  NavView.cpp
//  SYBlog
//
//  Created by Cocoa on 4/20/17.
//  Copyright © 2017 Cocoa. All rights reserved.
//

#include "NavView.hpp"

NavView::NavView() : SYView(){
    m_replacingFrom.navID = "<#category_id#>";
    m_replacingFrom.navItem = "<#category_name#>";
    m_template->LoadTemplatePage(K_NAVIGATION, V_NAVIGATION);
}

void NavView::SetClassify(Classify item){
    m_replacingTo.navID = item.classify_id;
    m_replacingTo.navItem = item.classify_name;
}

TEMPLATE NavView::GetNavHtml(){
    TEMPLATE temp;
    m_template->BuiltHtmlByTemplateKey(K_NAVIGATION, temp);
    if (m_replacingTo.navItem.length() > 0) {
        StringReplace(temp.value, m_replacingFrom.navItem, m_replacingTo.navItem);
        m_replacingTo.navItem = "";
    }
    if (m_replacingTo.navID.length() > 0) {
        StringReplace(temp.value, m_replacingFrom.navID, m_replacingTo.navID);
        m_replacingTo.navID = "";
    }
    return temp;
}

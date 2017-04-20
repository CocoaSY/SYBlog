//
//  BaseController.cpp
//  SYBlog
//
//  Created by Cocoa on 4/20/17.
//  Copyright © 2017 Cocoa. All rights reserved.
//

#include "BaseController.hpp"

#include "ClassifyModel.hpp"
#include "NavView.hpp"

using namespace std;

std::string BaseController::HeaderHtml(){
    
    // 加载导航栏模板
    ClassifyModel classifyModel;
    NavView navView;
    
    ClassifyList classifyList = classifyModel.GetClassifyList();
    string navHtml = "";
    ClassifyList::iterator iter;
    for (iter = classifyList.begin(); iter != classifyList.end(); iter++) {
        navView.SetClassify(*iter);
        navHtml += navView.GetNavHtml().value;
    }
    
    return navHtml;
}

std::string BaseController::FooterHtml(){
    
    return "";
}
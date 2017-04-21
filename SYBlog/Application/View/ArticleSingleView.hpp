//
//  ArticleSingleView.hpp
//  SYBlog
//
//  Created by Cocoa on 4/21/17.
//  Copyright © 2017 Cocoa. All rights reserved.
//

#ifndef ArticleSingleView_hpp
#define ArticleSingleView_hpp

#include <stdio.h>

#include "SYView.h"
#include "PostsModel.hpp"

typedef struct _ArticleSingleReplacing_ {
    
    std::string title;
    std::string content;
    std::string categoryName;
    std::string authorName;
    std::string postTime;
    
} ArticleSingleReplacing;

class ArticleSingleView : public SYView {
    
private:
    ArticleSingleReplacing m_replacingFrom;
    ArticleSingleReplacing m_replacingTo;
    
public:
    ArticleSingleView();
    
    void SetPost(POST aPost);
    
    TEMPLATE GetArticleSingleHtml();
};

#endif /* ArticleSingleView_hpp */

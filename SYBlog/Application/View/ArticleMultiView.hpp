//
//  ArticleMultiView.hpp
//  SYBlog
//
//  Created by Cocoa on 4/20/17.
//  Copyright © 2017 Cocoa. All rights reserved.
//

#ifndef ArticleMultiView_hpp
#define ArticleMultiView_hpp

#include <stdio.h>
#include <string>

#include "SYView.h"
#include "PostsModel.hpp"

typedef struct _ArticleReplacing_ {
    std::string title;
    std::string date;
    std::string intro;
    std::string url;
} ArticleReplacing;

class ArticleMultiView : public SYView {
    
private:
    ArticleReplacing m_replacingFrom;
    ArticleReplacing m_replacingTo;
    
public:
    ArticleMultiView();
    
    void SetArticleMultiItem(ARTICLE_MULTI_ITEM item);
    
    TEMPLATE GetArticleMultiHtml();
    
};

#endif /* ArticleMultiView_hpp */

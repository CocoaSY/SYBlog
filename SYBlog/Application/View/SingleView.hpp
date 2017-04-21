//
//  SingleView.hpp
//  SYBlog
//
//  Created by Cocoa on 4/21/17.
//  Copyright © 2017 Cocoa. All rights reserved.
//

#ifndef SingleView_hpp
#define SingleView_hpp

#include <stdio.h>

#include "SYView.h"


typedef struct _SingleReplacing_ {

    std::string nav;
    std::string article_single;
    
} SingleReplacing;

class SingleView : public SYView {
    
private:
    SingleReplacing m_replacingFrom;
    SingleReplacing m_replacingTo;
    
public:
    SingleView();
    
    void SetNavHtml(std::string navHtml);
    void SetArticleSingleHtml(std::string articleSingleHtml);
    
    TEMPLATE GetSingleHtml();
    
    
};


#endif /* SingleView_hpp */

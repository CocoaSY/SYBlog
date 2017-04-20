//
//  NavView.hpp
//  SYBlog
//
//  Created by Cocoa on 4/20/17.
//  Copyright © 2017 Cocoa. All rights reserved.
//

#ifndef NavView_hpp
#define NavView_hpp

#include <stdio.h>
#include <string>

#include "SYView.h"
#include "ClassifyModel.hpp"

typedef struct _NavReplacing_{
    std::string navID;
    std::string navItem;
    
} NavReplacing;

class NavView : public SYView {
    
private:
    NavReplacing m_replacingFrom;
    NavReplacing m_replacingTo;
    
public:
    NavView();
    
    void SetClassify(Classify item);
    
    TEMPLATE GetNavHtml();
    
};

#endif /* NavView_hpp */

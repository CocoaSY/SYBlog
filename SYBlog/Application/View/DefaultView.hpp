//
//  DefaultView.hpp
//  SYBlog
//
//  Created by Cocoa on 4/20/17.
//  Copyright © 2017 Cocoa. All rights reserved.
//

#ifndef DefaultView_hpp
#define DefaultView_hpp

#include <stdio.h>
#include <map>

#include "SYView.h"

typedef struct _DefaultReplacing_{
    std::string nav;
    std::string articleMulti;
    
} DefaultReplacing;

class DefaultView : public SYView {
    
private:
    DefaultReplacing m_replacingFrom;
    DefaultReplacing m_replacingTo;
    
public:
    DefaultView();
    
    void SetNavTemplate(std::string navTemplate);
    void SetArticleMultiTemplate(std::string articleMultiTemplate);
    
    TEMPLATE GetDefaultHtml();
    
};

#endif /* DefaultView_hpp */

//
//  CatalogView.hpp
//  SYBlog
//
//  Created by Cocoa on 4/20/17.
//  Copyright © 2017 Cocoa. All rights reserved.
//

#ifndef CatalogView_hpp
#define CatalogView_hpp

#include <stdio.h>
#include <map>

#include "SYView.h"

typedef struct _CatalogReplacing_{
    std::string nav;
    std::string articleMulti;
    
} CatalogReplacing;

class CatalogView : public SYView {
    
private:
    CatalogReplacing m_replacingFrom;
    CatalogReplacing m_replacingTo;
    
public:
    CatalogView();
    
    void SetNavTemplate(std::string navHtml);
    void SetArticleMultiTemplate(std::string articleMultiHtml);
    
    TEMPLATE GetCatalogHtml();
};

#endif /* CatalogView_hpp */

//
//  SYView.h
//  SYBlog
//
//  Created by Cocoa on 4/20/17.
//  Copyright © 2017 Cocoa. All rights reserved.
//

#ifndef SYView_h
#define SYView_h

#include "SYTemplate.hpp"
#include "SYConstant.h"
#include "SYUntil.hpp"

class SYView {
protected:
    SYTemplate * m_template;
    
public:
    SYView(){
        m_template = SYTemplate::GetInstance();
    }
    
};

#endif /* SYView_h */

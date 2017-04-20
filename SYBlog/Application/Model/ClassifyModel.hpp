//
//  ClassifyModel.hpp
//  SYBlog
//
//  Created by Cocoa on 4/20/17.
//  Copyright © 2017 Cocoa. All rights reserved.
//

#ifndef ClassifyModel_hpp
#define ClassifyModel_hpp

#include <stdio.h>
#include <string>
#include <list>

#include "SYModel.h"

typedef struct _Classify_{
    int ID;
    std::string classify_id;
    std::string classify_name;
    int classify_status;
} Classify;

typedef std::list<Classify> ClassifyList;

class ClassifyModel : public SYModel {
    
public:
    std::list<Classify> m_classifyList;
    
public:
    ClassifyModel();
    ~ClassifyModel();
    
    ClassifyList GetClassifyList();
};

#endif /* ClassifyModel_hpp */

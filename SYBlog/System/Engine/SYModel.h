//
//  SYModel.h
//  SYBlog
//
//  Created by Cocoa on 4/20/17.
//  Copyright © 2017 Cocoa. All rights reserved.
//

#ifndef SYModel_h
#define SYModel_h

#include "SYMysqlPool.hpp"

class SYModel {

public:
    SYMysqlPool * m_mysqlPool;
    
public:
    SYModel(){
        m_mysqlPool = SYMysqlPool::GetInstance();
    }
};


#endif /* SYModel_h */

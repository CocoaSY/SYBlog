//
//  ClassifyModel.cpp
//  SYBlog
//
//  Created by Cocoa on 4/20/17.
//  Copyright © 2017 Cocoa. All rights reserved.
//

#include "ClassifyModel.hpp"

using namespace std;

ClassifyModel::ClassifyModel() : SYModel(){
    
    string sql =    "SELECT ID,classify_id,classify_name,classify_status \
                    FROM sy_classify";
    MYSQL_RES * pRes = m_mysqlPool->Select(sql.c_str());
    if (pRes != NULL) {
        MYSQL_ROW row;
        while ( (row = mysql_fetch_row(pRes)) ) {
            Classify aClassify;
            aClassify.ID = atoi(row[0]);
            aClassify.classify_id = row[1];
            aClassify.classify_name = row[2];
            aClassify.classify_status = atoi(row[3]);
            m_classifyList.push_back(aClassify);
        }
        m_mysqlPool->FreeRecord(pRes);
    }
}
ClassifyModel::~ClassifyModel(){
    
}

ClassifyList ClassifyModel::GetClassifyList(){
    return m_classifyList;
}
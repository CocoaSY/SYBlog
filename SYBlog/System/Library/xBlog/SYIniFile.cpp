//
//  SYIniFile.cpp
//  xBlog
//
//  Created by Cocoa on 4/10/17.
//  Copyright © 2017 Cocoa. All rights reserved.
//

// C++ includes
#include <iostream>
#include <fstream>

using namespace std;

// C includes
#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>

#include "SYIniFile.hpp"

#define iniEOL '\r' << endl

string SYIniFile::CheckCase(string s) const{
    if (caseInsensitive) {
        for (string::size_type i = 0; i < s.length(); i++) {
            s[i] = tolower(s[i]);
        }
    }
    return s;
}

SYIniFile::SYIniFile(string const iniPath){
    Path(iniPath);
    caseInsensitive = true;
}

bool SYIniFile::ReadFile(){
    
    // Normally you would use ifstream, but the SGI CC compiler has
    // a few bugs with ifstream. So ... fstream used.
    fstream f;
    string line;
    string keyName,valueName,value;
    string::size_type pLeft,pRight;
    
    f.open(path.c_str(),ios::in);
    if(f.fail()) return false;
    
    while (getline(f, line)) {
        // To be compatible with Win32, check for existence of '\r'.
        // Win32 files have the '\r' and Unix files don't at the end of a line.
        // Note that the '\r' will be written to INI files from
        // Unix so that the created INI file can be read under Win32
        // without change.
        
        if(line.length() == 0) continue;
        
        if(line[line.length() - 1] == '\r') line = line.substr(0,line.length()-1);
        
        if (line.length()) {
            // Check that the user hasn't openned a binary file by checking the first
            // character of each line!
            
            if(!isprint(line[0])){
                printf( "Failing on char %d\n", line[0]);
                f.close();
                return false;
            }
            
            if ( (pLeft = line.find_first_of(";#[=")) != string::npos) {
                switch (line[pLeft]) {
                    case '[':
                        if ( (pRight = line.find_last_of(']'))!=string::npos && pRight>pLeft ) {
                            keyName = line.substr(pLeft+1,pRight-pLeft-1);
                            AddKeyName(keyName);
                        }
                        break;
                        
                    case '=':
                        valueName = line.substr(0,pLeft);
                        value = line.substr(pLeft+1);
                        SetValue(keyName, valueName, value);
                        break;
                        
                    case ';':
                    case '#':
                        if (!names.size()) {
                            HeaderComment(line.substr(pLeft+1));
                        } else {
                            KeyComment(keyName, line.substr(pLeft+1));
                        }
                        break;
                }
            }
        }
    }
    
    f.close();
    if (names.size()) {
        return true;
    }
    return false;
}

bool SYIniFile::WriteFile(){
    
    unsigned commentID,keyID,valueID;
    // Normally you would use ofstream, but the SGI CC compiler has
    // a few bugs with ofstream. So ... fstream used.
    
    fstream f;
    f.open(path.c_str(),ios::out);
    if(f.fail()) return false;
    
    // Write header comments.
    for (commentID = 0; commentID < comments.size(); commentID++) {
        f << ";" << comments[commentID] << iniEOL;
    }
    if(comments.size()) f << iniEOL;
    
    // Write keys and values.
    for (keyID = 0; keyID < keys.size(); keyID++) {
        f << "[" << names[keyID] << "]" << iniEOL;
        // Comments.
        for (commentID = 0; commentID < keys[keyID].comments.size(); commentID++) {
            f << ";" << comments[commentID] << iniEOL;
        }
        // Values.
        for (valueID = 0; valueID < keys[keyID].names.size(); valueID++) {
            f << keys[keyID].names[valueID] << "=" << keys[keyID].values[valueID] << iniEOL;
        }
        f << iniEOL;
        
    }
    f.close();
    return true;
}

// Delete all stored ini data.
void SYIniFile::Erase(){
    names.clear();
    keys.clear();
    comments.clear();
}

long SYIniFile::FindKey(string const keyName) const{
    for (unsigned keyID = 0; keyID < names.size(); keyID++) {
        if ( CheckCase(names[keyID]) == CheckCase(keyName) ) {
            return long(keyID);
        }
    }
    return noID;
}

long SYIniFile::FindValue(unsigned const keyID,string const valueName) const{
    
    if( !keys.size() || keyID > keys.size() ) return noID;
    
    for (unsigned valueID = 0; valueID < keys[keyID].names.size(); valueID++) {
        if ( CheckCase(keys[keyID].names[valueID]) == CheckCase(valueName) ) {
            return long(valueID);
        }
    }
    
    return noID;
}

unsigned SYIniFile::AddKeyName(string const keyName){
    names.resize(names.size()+1, keyName);
    keys.resize(keys.size()+1);
    return unsigned(names.size()-1);
}

string SYIniFile::KeyName(unsigned const keyID) const{
    if (keyID < names.size()) {
        return names[keyID];
    } else {
        return "";
    }
}

unsigned SYIniFile::NumValues(unsigned const keyID){
    if (keyID < keys.size()) {
        return unsigned(keys[keyID].names.size());
    }
    return 0;
}
unsigned SYIniFile::NumValues(string const keyName){
    long keyID = FindKey(keyName);
    if(keyID == noID) return 0;
    return unsigned(keys[keyID].names.size());
}

string SYIniFile::ValueName(unsigned const keyID,unsigned const valueID){
    if ( keyID < keys.size() && valueID < keys[keyID].names.size() ) {
        return keys[keyID].names[valueID];
    }
    return "";
}
string SYIniFile::ValueName(string const keyName,unsigned const valueID){
    long keyID = FindKey(keyName);
    if(keyID == noID) return "";
    return ValueName(unsigned(keyID), valueID);
}

string SYIniFile::GetValue(unsigned const keyID,unsigned const valueID,string const defValue)     const{
    if (keyID < keys.size() && valueID < keys[keyID].names.size()) {
        return keys[keyID].values[valueID];
    }
    return defValue;
}

string SYIniFile::GetValue(string const keyName,string const valueName,string const defValue)     const{
    long keyID = FindKey(keyName);
    if(keyID == noID) return defValue;
    
    long valueID = FindValue(unsigned(keyID), valueName);
    if(valueID == noID) return defValue;
    
    return keys[keyID].values[valueID];
}

int    SYIniFile::GetValueI(string const keyName,string const valueName,int const defValue)       const{
    char svalue[MAX_VALUEDATA];
    sprintf(svalue, "%d",defValue);
    return atoi( GetValue(keyName, valueName,svalue).c_str());
}

double SYIniFile::GetValueF(string const keyName,string const valueName,double const defValue)    const{
    char svalue[MAX_VALUEDATA];
    sprintf( svalue, "%f", defValue);
    return atof( GetValue( keyName, valueName, svalue).c_str());
}

unsigned SYIniFile::GetValueV(string const keyName,string const valueName,char * format,
               void *v1 ,void *v2 ,void *v3 ,void *v4 ,
               void *v5 ,void *v6 ,void *v7 ,void *v8 ,
               void *v9 ,void *v10,void *v11,void *v12,
               void *v13,void *v14,void *v15,void *v16)
{
    string value;
    // va_list  args;
    unsigned nVals;
    
    value = GetValue(keyName, valueName);
    if( !value.length() ) return false;
    // Why is there not vsscanf() function. Linux man pages say that there is
    // but no compiler I've seen has it defined. Bummer!
    //
    // va_start( args, format);
    // nVals = vsscanf( value.c_str(), format, args);
    // va_end( args);
    
    nVals = sscanf( value.c_str(), format,
                   v1, v2, v3, v4, v5, v6, v7, v8,
                   v9, v10, v11, v12, v13, v14, v15, v16);
    
    return nVals;
    
}

bool SYIniFile::SetValue(unsigned const keyID,unsigned const valueID,string const value){
    if (keyID < keys.size() && valueID < keys[keyID].names.size()) {
        keys[keyID].names[valueID] = value;
        return true;
    }
    return false;
}
bool SYIniFile::SetValue(string const keyName,string const valueName,string const value,bool const create){
    long keyID = FindKey(keyName);
    if (keyID == noID) {
        if (create) {
            keyID = long( AddKeyName(keyName) );
        } else {
            return false;
        }
    }
    
    long valueID = FindValue(unsigned(keyID), valueName);
    if (valueID == noID) {
        if (!create) return false;
        
        keys[keyID].names.resize(keys[keyID].names.size()+1, valueName);
        keys[keyID].values.resize(keys[keyID].values.size()+1, value);
    } else {
        keys[keyID].values[valueID] = value;
    }
    
    return true;
}

bool SYIniFile::SetValueI(string const keyName,string const valueName,int const value,bool const create){
    char svalue[MAX_VALUEDATA];
    sprintf(svalue, "%d",value);
    return SetValue(keyName, valueName, svalue,create);
}

bool SYIniFile::SetValueF(string const keyName,string const valueName,double const value,bool const create){
    char svalue[MAX_VALUEDATA];
    sprintf(svalue, "%f",value);
    return SetValue(keyName, valueName, svalue,create);
}

bool SYIniFile::SetValueV(string const keyName,string const valueName,char * format,...){
    
    va_list args;
    char value[MAX_VALUEDATA];
    
    va_start(args, format);
    vsprintf(value, format, args);
    va_end(args);
    return SetValue(keyName, valueName, value);
}

bool SYIniFile::DeleteValue(string const keyName,string const valueName){
    
    long keyID = FindKey(keyName);
    if(keyID == noID) return false;
    
    long valueID = FindValue(unsigned(keyID), valueName);
    if(valueID == noID) return false;
    
    // This looks strange, but is neccessary.
    vector<string>::iterator npos = keys[keyID].names.begin() + valueID;
    vector<string>::iterator vpos = keys[keyID].values.begin() + valueID;
    keys[keyID].names.erase(npos,npos+1);
    keys[keyID].values.erase(vpos,vpos+1);
    return true;
}

bool SYIniFile::DeleteKey(string keyName){
    
    long keyID = FindKey(keyName);
    if(keyID == noID) return false;
    
    // Now hopefully this destroys the vector lists within keys.
    // Looking at <vector> source, this should be the case using the destructor.
    // If not, I may have to do it explicitly. Memory leak check should tell.
    // memleak_test.cpp shows that the following not required.
    //keys[keyID].names.clear();
    //keys[keyID].values.clear();
    
    vector<string>::iterator npos = names.begin() + keyID;
    vector<key>::iterator kpos = keys.begin() + keyID;
    names.erase(npos,npos+1);
    keys.erase(kpos,kpos+1);
    
    return true;
}

void SYIniFile::HeaderComment(string const comment){
    comments.resize(comments.size()+1, comment);
}

string SYIniFile::HeaderComment(unsigned const commentID){
    if (commentID < comments.size()) {
        return comments[commentID];
    }
    return "";
}

bool SYIniFile::DeleteHeaderComment(unsigned commentID){
    if (commentID < comments.size()) {
        vector<string>::iterator cpos = comments.begin() + commentID;
        comments.erase(cpos,cpos+1);
        return true;
    }
    return false;
}

unsigned SYIniFile::NumKeyComments(unsigned const keyID) const{
    if (keyID < keys.size()) {
        return unsigned(keys[keyID].comments.size());
    }
    return 0;
}

unsigned SYIniFile::NumKeyComments(string const keyName) const{
    long keyID = FindKey(keyName);
    if (keyID == noID) {
        return 0;
    }
    return NumKeyComments(unsigned(keyID));
}

bool SYIniFile::KeyComment(unsigned const keyID,string const comment){
    if (keyID < keys.size()) {
        keys[keyID].comments.resize(keys[keyID].comments.size()+1, comment);
        return true;
    }
    return false;
}
bool SYIniFile::KeyComment(string const keyName,string const comment){
    long keyID = FindKey(keyName);
    if(keyID == noID) return false;
    return KeyComment(unsigned(keyID), comment);
}

string SYIniFile::KeyComment(unsigned const keyID,unsigned const commentID) const{
    if (keyID < keys.size() && commentID < keys[keyID].comments.size()) {
        return keys[keyID].comments[commentID];
    }
    return "";
}

string SYIniFile::KeyComment(string const keyName,unsigned const commentID) const{
    long keyID = FindKey(keyName);
    if(keyID == noID) return "";
    return KeyComment(unsigned(keyID), commentID);
}


bool SYIniFile::DeleteKeyComment(unsigned const keyID,unsigned const commentID){
    if (keyID < keys.size() && commentID < keys[keyID].comments.size()) {
        vector<string>::iterator cpos = comments.begin() +commentID;
        comments.erase(cpos,cpos+1);
        return true;
    }
    return false;
}

bool SYIniFile::DeleteKeyComment(string const keyName,unsigned const commentID){
    long keyID = FindKey(keyName);
    if(keyID == noID) return false;
    return DeleteKeyComment(unsigned(keyID), commentID);
}

bool SYIniFile::DeleteKeyComments(unsigned const keyID){
    if (keyID < keys.size()) {
        keys[keyID].comments.clear();
        return true;
    }
    return false;
}

bool SYIniFile::DeleteKeyComments(string const keyName){
    long keyID = FindKey(keyName);
    if (keyID == noID) return false;
    return DeleteKeyComments(unsigned(keyID));
}
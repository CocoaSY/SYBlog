//
//  SYIniFile.hpp
//  xBlog
//
//  Created by Cocoa on 4/10/17.
//  Copyright © 2017 Cocoa. All rights reserved.
//

#ifndef SYIniFile_hpp
#define SYIniFile_hpp

#include <stdio.h>

// C++ includes
#include <string>
#include <vector>

// C includes
#include <stdlib.h>

#define MAX_KEYNAME    128
#define MAX_VALUENAME  128
#define MAX_VALUEDATA 2048

class SYIniFile {
    
private:
    bool caseInsensitive;
    std::string
    path;
    struct key {
        std::vector<std::string> names;
        std::vector<std::string> values;
        std::vector<std::string> comments;
    };
    std::vector<key> keys;
    std::vector<std::string> names;
    std::vector<std::string> comments;
    
    std::string CheckCase(std::string s) const;
    
    
public:
    enum errors { noID = -1 };
    
    SYIniFile(std::string const iniPath = "");
    virtual ~SYIniFile(){}
    
    // Set weather or not keynames and valuenames should be case insensitive.
    // Default is case insensitive.
    void CaseSensitive()    { caseInsensitive = true; }
    void CaseInsensitive()  { caseInsensitive = false; }
    
    // Set path of ini file to read and write from.
    void Path(std::string const newPath)     { path = newPath; }
    std::string Path() const                 { return path; }
    void SetPath(std::string const newPath)  { Path(newPath); };
    
    // Read ini file specified using path.
    // Return true if successful,false otherwise.
    bool ReadFile();
    
    // Write data stored in class to ini file.
    bool WriteFile();
    
    // Delete all stored ini data.
    void Erase();
    void Clear() { Erase(); }
    void Reset() { Erase(); }
    
    // Return index of specified key,or noID if not found.
    long FindKey(std::string const keyName) const;
    
    // Return index of specified value,in specified key ID,or noID if not found.
    long FindValue(unsigned const keyID,std::string const valueName) const;
    
    // Return numbers of keys currently in the ini.
    unsigned NumKeys() const    { return (unsigned)names.size(); }
    unsigned GetNumKeys() const { return  NumKeys(); }
    
    // Add a key name.
    unsigned AddKeyName(std::string const keyName);
    
    // Return key names by index.
    std::string KeyName(unsigned const keyID) const;
    std::string GetKeyName(unsigned const keyID) const { return KeyName(keyID); }
    
    // Return number of values stored in specified key.
    unsigned NumValues(unsigned const keyID);
    unsigned GetNumValues(unsigned const keyID) { return NumValues(keyID); }
    unsigned NumValues(std::string const keyName);
    unsigned GetNumValues(std::string const keyName) { return NumValues(keyName); }
    
    // Return value name by index for a given keyname or keyID.
    std::string ValueName(unsigned const keyID,unsigned const valueID);
    std::string ValueName(std::string const keyName,unsigned const valueID);
    
    std::string GetValueName(unsigned const keyID,unsigned const valueID){
        return ValueName(keyID, valueID);
    }
    std::string GetValueName(std::string const keyName,unsigned const valueID){
        return ValueName(keyName, valueID);
    }
    
    // Gets value of [keyname] valuename =.
    // Overloaded to return string, int, and double.
    // Returns defValue if key/value not found.
    std::string GetValue(unsigned const keyID,unsigned const valueID,std::string const defValue = "")     const;
    std::string GetValue(std::string const keyName,std::string const valueName,std::string const defValue = "")     const;
    int    GetValueI(std::string const keyName,std::string const valueName,int const defValue = 0)        const;
    bool   GetValueB(std::string const keyName,std::string const valueName,bool const defValue = false)   const{
        return bool( GetValueI(keyName, valueName,int( defValue )) );
    }
    double GetValueF(std::string const keyName,std::string const valueName,double const defValue = 0.0)   const;
    
    // This is a variable length formatted GetValue routine. All these voids
    // are required because there is no vsscanf() like there is a vsprintf().
    // Only a maximum of 8 variable can be read.
    unsigned GetValueV(std::string const keyName,std::string const valueName,char * format,
                   void *v1 = 0,void *v2 = 0,void *v3 = 0,void *v4 = 0,
                   void *v5 = 0,void *v6 = 0,void *v7 = 0,void *v8 = 0,
                   void *v9 = 0,void *v10 = 0,void *v11 = 0,void *v12 = 0,
                   void *v13 = 0,void *v14 = 0,void *v15 = 0,void *v16 = 0);
    
    // Sets value of [keyname] valuename =.
    // Specify the optional paramter as false (0) if you do not want it to create
    // the key if it doesn't exist. Returns true if data entered, false otherwise.
    // Overloaded to accept string, int, and double.
    bool SetValue(unsigned const keyID,unsigned const valueID,std::string const value);
    bool SetValue(std::string const keyName,std::string const valueName,std::string const value,bool const create = true);
    bool SetValueI(std::string const keyName,std::string const valueName,int const value,bool const create = true);
    bool SetValueB(std::string const keyName,std::string const valueName,bool const value,bool const create = true){
        return SetValueI(keyName, valueName, int(value));
    }
    bool SetValueF(std::string const keyName,std::string const valueName,double const value,bool const create = true);
    bool SetValueV(std::string const keyName,std::string const valueName,char * format,...);
    
    // Deletes specified value.
    // Returns true if value existed and deleted, false otherwise.
    bool DeleteValue(std::string const keyName,std::string const valueName);
    
    // Deletes specified key and all values contained within.
    // Returns true if key existed and deleted, false otherwise.
    bool DeleteKey(std::string keyName);
    
    // Header comment functions.
    // Header comments are those comments before the first key.
    //
    // Number of header comments.
    unsigned NumHeaderComments() {return (unsigned)comments.size(); }
    // Add a header comment.
    void HeaderComment(std::string const comment);
    // Return a header comment.
    std::string HeaderComment(unsigned const commentID);
    // Delete a header comment.
    bool DeleteHeaderComment(unsigned commentID);
    // Delete all header comments.
    void DeleteHeaderComments() { comments.clear(); }
    
    // Key comment functions.
    // Key comments are those comments within a key. Any comments
    // defined within value names will be added to this list. Therefore,
    // these comments will be moved to the top of the key definition when
    // the CIniFile::WriteFile() is called.
    //
    // Number of key comments.
    unsigned NumKeyComments(unsigned const keyID) const;
    unsigned NumKeyComments(std::string const keyName) const;
    // Add a key comment.
    bool KeyComment(unsigned const keyID,std::string const comment);
    bool KeyComment(std::string const keyName,std::string const comment);
    // Return a key comment.
    std::string KeyComment(unsigned const keyID,unsigned const commentID) const;
    std::string KeyComment(std::string const keyName,unsigned const commentID) const;
    // Delete a key comment.
    bool DeleteKeyComment(unsigned const keyID,unsigned const commentID);
    bool DeleteKeyComment(std::string const keyName,unsigned const commentID);
    // Delete all comments for a key.
    bool DeleteKeyComments(unsigned const keyID);
    bool DeleteKeyComments(std::string const keyName);
    
};

#endif /* SYIniFile_hpp */

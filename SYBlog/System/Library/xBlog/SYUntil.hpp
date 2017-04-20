//
//  SYUntil.hpp
//  xBlog
//
//  Created by Cocoa on 4/10/17.
//  Copyright © 2017 Cocoa. All rights reserved.
//

#ifndef SYUntil_hpp
#define SYUntil_hpp

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string>
#include <map>

#include <sys/stat.h>
#include <sys/socket.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>

#define  stricmp strcasecmp
#define  strnicmp strncasecmp
#define  SLEEP sleep


#include <event2/event.h>
#include <event2/http.h>
#include <event2/buffer.h>
#include <event2/util.h>
#include <event2/keyvalq_struct.h>

#ifdef _EVENT_HAVE_NETINET_IN_H
#include <netinet/in.h>
#ifdef _XOPEN_SOURCE_EXTENDED
#include <arpa/inet.h>
#endif
#endif

typedef int8_t                   int8;
typedef u_int8_t                 uint8;
typedef int16_t                  int16;
typedef u_int16_t                uint16;
typedef int32_t                  int32;
typedef u_int32_t                uint32;
typedef int64_t                  int64;
typedef u_int64_t                uint64;
typedef unsigned char            uchar;


static const struct table_entry {
    const char *extension;
    const char *content_type;
} content_type_table[] = {
    { "txt", "text/plain" },
    { "c",   "text/plain" },
    { "h",   "text/plain" },
    { "js",  "application/x-javascript" },
    { "html","text/html" },
    { "htm", "text/html" },
    { "css", "text/css" },
    { "gif", "image/gif" },
    { "jpg", "image/jpeg" },
    { "ico", "image/gif" },
    { "jpeg","image/jpeg" },
    { "png", "image/png" },
    { "pdf", "application/pdf" },
    { "ps",  "application/postsript" },
    { NULL, NULL },
};

const char *GuessContentType(const char *path);
void  StringReplace(std::string & strData, const std::string & strsrc, const std::string &strdst);
char * GetSubStr( char *buf, const char *start, const char *end, char * out);
uint64 CreatSession();
size_t MysqlEscapeString(char *to, size_t to_length, const char *from, size_t length);

uint32 atoul(const char *str);
uint64 atoull(const char *str);


#endif /* SYUntil_hpp */

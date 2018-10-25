//
//  cutils.h
//  endlessworld
//
//  Created by 林 桂 on 18/9/22.
//  Copyright © 2018年 林 桂. All rights reserved.
//

#ifndef cutils_h
#define cutils_h

#include <stdbool.h>
#include <string.h>


// strings
#define streql(s1,s2) (strcmp((s1),(s2))==0)
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y)) 
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y)) 
#ifdef __cplusplus
// support C++
extern "C" {
#endif
// files
const char* get_filename_ext(const char *filename);
#ifdef __cplusplus
}
#endif
// random
#define randint(x) rand() % (x)


const char *get_filename_ext(const char *filename) {
    const char *dot = strrchr(filename, '.');
    if(!dot || dot == filename) return "";
    return dot + 1;
}

#endif /* cutils_h */

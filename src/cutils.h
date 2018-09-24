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
// files
const char* get_filename_ext(const char *filename);
// random
// srand(time(NULL));   // should only be called once
#define random(x) rand() % (x)

#endif /* cutils_h */

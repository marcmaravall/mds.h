/* 

MIT License

Copyright (c) 2026 Marc Maravall Díez

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

#ifndef MDS_H
#define MDS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef MDS_ALLOC
#   define MDS_ALLOC   malloc
#endif
#ifndef MDS_REALLOC
#   define MDS_REALLOC realloc
#endif
#ifndef MDS_FREE
#   define MDS_FREE free
#endif

typedef struct mdString {
    char*   data;
    size_t  size;
    size_t  capacity;
} mdString;

mdString mds_init   (const char*);
void     mds_resize (mdString*, const size_t);
void     mds_set    (mdString*, const char*);
char*    mds_get    (mdString);
mdString mds_concat (mdString*, const char*);

size_t   mds_size     (const mdString);
size_t   mds_capacity (const mdString);

void     mds_free   (mdString*);

#endif // MDS_H

#ifdef MDS_IMPLEMENTATION

mdString mds_init(const char* cstr) {
    mdString str;

    size_t len = strlen(cstr);
    str.data = malloc(sizeof(char) * len + 1);
    str.capacity = len;
    str.size = len;

    strncpy(str.data, cstr, strlen(cstr));
    str.data[str.size] = '\0';

    return str;
}

void mds_resize(mdString* str, const size_t size) {
    str->size = size;
    if (str->size > str->capacity) {
        str->capacity = str->size * 2;
        str->data = realloc(str->data, sizeof(char) * (str->capacity + 1));
    }

    str->data[str->size] = '\0';
}

void mds_set(mdString *str, const char* cstr) {
    size_t len = strlen(cstr);
    str->size = len;
    if (str->size > str->capacity) {
        str->capacity *= 2;
        str->data = realloc(str->data, sizeof(char) * (str->capacity + 1));
    }

    strncpy(str->data, cstr, len);
    str->data[str->size] = '\0';
}

void mds_free(mdString *str) {
    str->size = 0;
    str->capacity = 0;
    MDS_FREE(str->data);
}

char* mds_get(const mdString str) {
    return str.data;
}

size_t mds_size (const mdString str) {
    return str.size;
}

size_t mds_capacity(const mdString str) {
    return str.capacity;
}

mdString mds_concat(mdString *str, const char* cstr) {
    str->size += strlen(cstr);
    while (str->size > str->capacity) {
        str->capacity *= 2;
        str->data = realloc(str->data, sizeof(char) * (str->capacity + 1));
    }

    strcat(str->data, cstr);
    str->data[str->size] = '\0';

    return *str;
}

#endif // MDS_H

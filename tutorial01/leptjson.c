#include "leptjson.h"
#include <assert.h>  /* assert() */
#include <stdlib.h>  /* NULL */

//如果那个错误是由于程序员错误编码所造成的（例如传入不合法的参数），那么应用断言；
//如果那个错误是程序员无法避免，而是由运行时的环境所造成的，就要处理运行时错误（例如开启文件失败）
#define EXPECT(c, ch)       do { assert(*c->json == (ch)); c->json++; } while(0)

//为了减少解析函数之间传递多个参数，我们把这些数据都放进一个 lept_context 结构体
typedef struct {
    const char* json;
}lept_context;

/* ws = *(%x20 / %x09 / %x0A / %x0D) */
static void lept_parse_whitespace(lept_context* c) {
    const char* p = c->json;
    while (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r')
        p++;
    c->json = p;
}

/* true  = "true" */
static int lept_parse_true(lept_context* c, lept_value* v) {
    //当前字符应该是 'n'，所以我们使用一个宏 EXPECT(c, ch) 进行断言，并跳到下一字符。
    EXPECT(c, 't');
    if (c->json[0] != 'r' || c->json[1] != 'u' || c->json[2] != 'e')
        return LEPT_PARSE_INVALID_VALUE;
    c->json += 3;
    v->type = LEPT_TRUE;
    return LEPT_PARSE_OK;
}

/* false  = "false" */
static int lept_parse_false(lept_context* c, lept_value* v) {
    //当前字符应该是 'n'，所以我们使用一个宏 EXPECT(c, ch) 进行断言，并跳到下一字符。
    EXPECT(c, 'f');
    if (c->json[0] != 'a' || c->json[1] != 'l' || c->json[2] != 's' || c->json[3] != 'e')
        return LEPT_PARSE_INVALID_VALUE;
    c->json += 4;
    v->type = LEPT_FALSE;
    return LEPT_PARSE_OK;
}

/* null  = "null" */
static int lept_parse_null(lept_context* c, lept_value* v) {
    //当前字符应该是 'n'，所以我们使用一个宏 EXPECT(c, ch) 进行断言，并跳到下一字符。
    EXPECT(c, 'n');
    if (c->json[0] != 'u' || c->json[1] != 'l' || c->json[2] != 'l')
        return LEPT_PARSE_INVALID_VALUE;
    c->json += 3;
    v->type = LEPT_NULL;
    return LEPT_PARSE_OK;
}

/* value = null / false / true */
static int lept_parse_value(lept_context* c, lept_value* v) {
    switch (*c->json) {
    case 't':  return lept_parse_true(c, v);
    case 'f':  return lept_parse_false(c, v);
    case 'n':  return lept_parse_null(c, v);
    case '\0': return LEPT_PARSE_EXPECT_VALUE;
    default:   return LEPT_PARSE_INVALID_VALUE;
    }
}

int lept_parse(lept_value* v, const char* json) {
    lept_context c;
    int ret = LEPT_PARSE_ROOT_NOT_SINGULAR;//局部变量需要初始化
    assert(v != NULL);
    c.json = json;
    v->type = LEPT_NULL;
    lept_parse_whitespace(&c);
    if ((ret == lept_parse_value(&c, v)) == LEPT_PARSE_OK) {
        lept_parse_whitespace(&c);
        if (*c.json != '\0') {
            ret = LEPT_PARSE_ROOT_NOT_SINGULAR;
        }
    }
    return ret;
}

lept_type lept_get_type(const lept_value* v) {
    assert(v != NULL);
    return v->type;
}

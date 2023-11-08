#include "leptjson.h"
#include <assert.h>  /* assert() */
#include <stdlib.h>  /* NULL */

//����Ǹ����������ڳ���Ա�����������ɵģ����紫�벻�Ϸ��Ĳ���������ôӦ�ö��ԣ�
//����Ǹ������ǳ���Ա�޷����⣬����������ʱ�Ļ�������ɵģ���Ҫ��������ʱ�������翪���ļ�ʧ�ܣ�
#define EXPECT(c, ch)       do { assert(*c->json == (ch)); c->json++; } while(0)

//Ϊ�˼��ٽ�������֮�䴫�ݶ�����������ǰ���Щ���ݶ��Ž�һ�� lept_context �ṹ��
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
    //��ǰ�ַ�Ӧ���� 'n'����������ʹ��һ���� EXPECT(c, ch) ���ж��ԣ���������һ�ַ���
    EXPECT(c, 't');
    if (c->json[0] != 'r' || c->json[1] != 'u' || c->json[2] != 'e')
        return LEPT_PARSE_INVALID_VALUE;
    c->json += 3;
    v->type = LEPT_TRUE;
    return LEPT_PARSE_OK;
}

/* false  = "false" */
static int lept_parse_false(lept_context* c, lept_value* v) {
    //��ǰ�ַ�Ӧ���� 'n'����������ʹ��һ���� EXPECT(c, ch) ���ж��ԣ���������һ�ַ���
    EXPECT(c, 'f');
    if (c->json[0] != 'a' || c->json[1] != 'l' || c->json[2] != 's' || c->json[3] != 'e')
        return LEPT_PARSE_INVALID_VALUE;
    c->json += 4;
    v->type = LEPT_FALSE;
    return LEPT_PARSE_OK;
}

/* null  = "null" */
static int lept_parse_null(lept_context* c, lept_value* v) {
    //��ǰ�ַ�Ӧ���� 'n'����������ʹ��һ���� EXPECT(c, ch) ���ж��ԣ���������һ�ַ���
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
    int ret = LEPT_PARSE_ROOT_NOT_SINGULAR;//�ֲ�������Ҫ��ʼ��
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

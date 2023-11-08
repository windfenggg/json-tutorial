//避免头文件重复声明
#ifndef LEPTJSON_H__
#define LEPTJSON_H__

//JSON 中有 6 种数据类型，如果把 true 和 false 当作两个类型就是 7 种
typedef enum {
    LEPT_NULL,
    LEPT_FALSE,
    LEPT_TRUE,
    LEPT_NUMBER,
    LEPT_STRING,
    LEPT_ARRAY,
    LEPT_OBJECT
} lept_type;

//JSON 是一个树形结构，我们最终需要实现一个树的数据结构，每个节点使用 lept_value 结构体表示
//该结构体只需要存储一个 lept_type
typedef struct {
    lept_type type;
}lept_value;

//解析JSON字符的状态码
enum {
    //解析OK
    LEPT_PARSE_OK = 0,
    //若一个 JSON 只含有空白
    LEPT_PARSE_EXPECT_VALUE,
    //若值不是那三种字面值
    LEPT_PARSE_INVALID_VALUE,
    //若一个值之后，在空白之后还有其他字符
    LEPT_PARSE_ROOT_NOT_SINGULAR
};

//解析JSON函数
//传入的JSON文本是一个C字符串，不应该改动这个输入字符，使用const
int lept_parse(lept_value* v, const char* json);

//访问结果的函数，就是获取其类型
lept_type lept_get_type(const lept_value* v);

#endif /* LEPTJSON_H__ */

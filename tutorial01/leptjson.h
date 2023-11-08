//����ͷ�ļ��ظ�����
#ifndef LEPTJSON_H__
#define LEPTJSON_H__

//JSON ���� 6 ���������ͣ������ true �� false �����������;��� 7 ��
typedef enum {
    LEPT_NULL,
    LEPT_FALSE,
    LEPT_TRUE,
    LEPT_NUMBER,
    LEPT_STRING,
    LEPT_ARRAY,
    LEPT_OBJECT
} lept_type;

//JSON ��һ�����νṹ������������Ҫʵ��һ���������ݽṹ��ÿ���ڵ�ʹ�� lept_value �ṹ���ʾ
//�ýṹ��ֻ��Ҫ�洢һ�� lept_type
typedef struct {
    lept_type type;
}lept_value;

//����JSON�ַ���״̬��
enum {
    //����OK
    LEPT_PARSE_OK = 0,
    //��һ�� JSON ֻ���пհ�
    LEPT_PARSE_EXPECT_VALUE,
    //��ֵ��������������ֵ
    LEPT_PARSE_INVALID_VALUE,
    //��һ��ֵ֮���ڿհ�֮���������ַ�
    LEPT_PARSE_ROOT_NOT_SINGULAR
};

//����JSON����
//�����JSON�ı���һ��C�ַ�������Ӧ�øĶ���������ַ���ʹ��const
int lept_parse(lept_value* v, const char* json);

//���ʽ���ĺ��������ǻ�ȡ������
lept_type lept_get_type(const lept_value* v);

#endif /* LEPTJSON_H__ */

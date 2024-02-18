#ifndef LESALS_H
#define LESALS_H

#include <QDebug>
#include <iostream>
#include <string>
#include <math.h>
#include <set>
#include <vector>
using namespace std;

#define KW_NUM 104
#define OP_NUM 38

class lesals//词法分析器类
{   
public:

    lesals();
    void getToken();

    //是否数字
    bool isDigit(char ch);

    //是否字母
    bool isAlpha(char ch);

    //是否空格或Tab
    bool isSpbTab(char ch);

    //是否关键字
    bool isKeyword(string str);

    //是否特殊符号
    bool isSpeSb(char ch);

    //是否运算符
    bool isOperator(char ch);

    //按行分析
    void analysis(vector<string> &res, string line);


private:
    string kwarray[KW_NUM]={"auto","bitand", "bitor", "break", "case", "catch","char", "class", "const",
                             "continue", "default", "delete", "do", "double", "else",
                             "enum", "explicit", "extern", "false", "float", "for",
                             "friend", "goto", "if", "inline","include","std", "int", "long", "mutable",
                             "namespace", "new", "operator", "private", "protected", "public",
                             "register", "return", "short", "signed", "sizeof", "static", "struct",
                             "switch", "template", "this", "throw", "true", "try", "typedef", "typeid",
                             "typename", "union", "unsigned", "using", "virtual", "void", "volatile",
                              "while","cin","cout","endl","alignas", "alignof", "and", "and_eq", "asm", "atomic_cancel", "atomic_commit",
                            "atomic_noexcept", "bitand", "bitor", "bool", "catch", "char8_t", "char16_t", "char32_t",
                            "compl", "concept", "consteval", "constexpr", "constinit", "const_cast", "co_await", "co_return", "co_yield",
                            "decltype", "export", "noexcept", "not", "not_eq", "nullptr", "reflexpr", "reinterpret_cast",
                            "requires", "static_assert", "static_cast", "synchronized", "xor","wchar_t","thread_local","or","or_eq","dynamic_cast"};       //关键字表;

    string oparray[OP_NUM]={"+","-","*","/","%","++","--","==","!=",">","<",">=",
                      "<=","&&","||","!","&","|","^","~","<<",">>","=","+=",
                     "-=","*=","/=","%=","<<=",">>=","&=","^=","|=","(",")","[","]","->"};


    set<string> keywords;//关键字集
    set<string> opset;//运算符集

    bool f_string;//字符串状态
    bool f_ant;//注释状态
};

#endif // LESALS_H

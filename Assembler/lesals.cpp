#include "lesals.h"

lesals::lesals()
{
    //初始化关键字集
    for(int i=0;i<KW_NUM;i++)
        keywords.insert(kwarray[i]);
    for(int i=0;i<OP_NUM;i++)
        opset.insert(oparray[i]);

    //初始化状态
    f_string=0;
    f_ant=0;
}

bool lesals::isDigit(char ch)
{
    return ch>='0'&&ch<='9';
}

bool lesals::isAlpha(char ch)
{
    return (ch>='A'&&ch<='Z')||(ch>='a'&&ch<='z');
}

bool lesals::isSpbTab(char ch)
{
    return ch==32||ch==9;
}
bool lesals::isKeyword(string str)
{
    return keywords.count(str)!=0;
}
bool lesals::isSpeSb(char ch)
{
    return ch=='{'||ch=='}'||ch==','||ch==';'||ch=='#';
}
bool lesals::isOperator(char ch)
{
    //return opset.count(ch+"\0")!=0;//!isAlpha(ch)&&!isDigit(ch)&&!isSpbTab(ch)&&!isSpeSb(ch)&&
    string s="";
    s+=ch;
    for(int i=0;i<OP_NUM;i++)
        if(s==oparray[i])
            return true;
    return false;
}
void lesals::analysis(vector<string> &res, string line)
{
    int len=line.length(),pos=0;
    //qDebug()<<"len:"<<len<<"\n";
    while(pos<len)
    {
        while(pos<len&&isSpbTab(line[pos])) pos++;//跳过空格和Tab
        if(pos<len)
        {

            if((isAlpha(line[pos])||line[pos]=='_')&&!f_string&&!f_ant)//首字符为字母，关键字、标识符
            {
                qDebug()<<"字母\n";
                string s="";
                s+=line[pos++];
                while((isAlpha(line[pos])||line[pos]=='_'||isDigit(line[pos]))&&pos<len)
                {
                    s+=line[pos];
                    pos++;
                }
                if(isKeyword(s))
                    res.push_back(s+"   关键字");
                else
                    res.push_back(s+"   标识符");
            }
            else if(isDigit(line[pos])&&!f_string&&!f_ant)//首字符为数字
            {
                bool wexp=false;//错误标记
                string s="";
                int p_num=0,e_num=0;//记录小数点和e的数量
                s+=line[pos++];
                while(pos<len&&((!isSpbTab(line[pos])&&!isSpeSb(line[pos])&&!isOperator(line[pos]))))
                {
                    qDebug()<<"数字分解\n";
                    while(pos<len&&(isDigit(line[pos])||line[pos]=='.'))
                    {
                        if(line[pos]=='.')
                            p_num++;
                        s+=line[pos++];
                    }

                    if(pos<len-1&&(line[pos]=='e'||line[pos]=='E'))//科学计数法
                    {
                         s+=line[pos++];
                         e_num++;
                         while(pos<len&&(isDigit(line[pos])||line[pos]=='.'))
                         {
                             if(line[pos]=='.')
                                 p_num++;
                             s+=line[pos++];
                         }
                         if(pos>=len)
                             break;

                         //取e后面的运算符
                         if(pos<len&&(line[pos]=='+'||line[pos]=='-'))
                             s+=line[pos++];
                         if(p_num>1)
                             wexp=true;
                         p_num=0;
                         while(pos<len&&(isDigit(line[pos])||line[pos]=='.'))
                         {
                             if(line[pos]=='.')
                                 p_num++;
                             s+=line[pos++];
                         }
                    }
                    else if(pos<len&&(line[pos]=='b'||line[pos]=='B'||line[pos]=='x'||line[pos]=='X'))//进制表示法
                    {
                        s+=line[pos++];
                        if(line[pos-2]!='0')
                            wexp=true;
                        while(pos<len&&!isSpeSb(line[pos]))
                        {
                            if(!isDigit(line[pos]))
                                wexp=true;
                            s+=line[pos++];
                        }
                    }
                    else//可能是非法命名的标识符
                    {
                        while(pos<len&&(isDigit(line[pos])||isAlpha(line[pos])))
                        {
                            if(isAlpha(line[pos]))
                                wexp=true;
                            else if(isOperator(line[pos]))
                                break;
                            s+=line[pos++];
                        }
                    }
                    if(p_num>1||e_num>1)
                        wexp=true;
                }
                if(!wexp)
                    res.push_back(s+"  数");
                else
                    res.push_back(s+"   错误标识");
            }
            else
            {
                //qDebug()<<"其他\n";
                if(line[pos]=='"')
                    f_string=true;
                string s="";

                //字符串
                if(f_string)
                {
                    s+=line[pos++];
                    while(pos<len)
                    {
                        s+=line[pos];
                        if(line[pos]=='"')
                        {
                            f_string=false;
                            pos++;
                            break;
                        }
                        pos++;
                    }
                    res.push_back(s+"   字符串");
                    continue;
                }

                //多行注释
                if(pos<len-1&&line[pos]=='/'&&line[pos+1]=='*')
                {
                    s+=line[pos++];
                    s+=line[pos++];
                    f_ant=true;
                }
                if(f_ant)
                {
                    while(pos<len-1&&line[pos]!='*')
                        s+=line[pos++];
                    if(pos<len-1&&line[pos]=='*'&&line[pos+1]=='/')
                    {
                        s+=line[pos++];
                        s+=line[pos++];
                        f_ant=false;
                    }
                    else
                    {
                        while(pos<len)
                            s+=line[pos++];
                    }
                    res.push_back(s+"   注释");
                    continue;
                }

                //单行注释
                if(pos<len-1&&line[pos]=='/'&&line[pos+1]=='/')
                {
                    s+=line[pos++];
                    s+=line[pos++];
                    while(pos<len)
                        s+=line[pos++];
                    res.push_back(s+"   注释");
                    continue;
                }

                //分界符
                if(pos<len)
                {
                    bool f=false;
                    switch (line[pos])
                    {
                        case ',':
                            res.push_back(",  特殊符号"),pos++,f=true;
                        break;

                        case ';': res.push_back(";  特殊符号"),pos++,f=true;
                        break;

                        case '{':
                            res.push_back("{  特殊符号"),pos++,f=true;
                        break;

                        case '}':
                            res.push_back("}  特殊符号"),pos++,f=true;
                        break;
                        case '#':
                            res.push_back("#  特殊符号"),pos++,f=true;
                        break;
                        case '\'':
                            string st="";
                            st+=line[pos++];
                            while(pos<len&&line[pos]!='\'')
                                st+=line[pos++];
                            st+='\'',pos++;
                            res.push_back(st+"  字符"),pos++,f=true;
                        break;
                    }
                    if(f)
                        continue;
                }

                //运算符
                if(pos<len&&isOperator(line[pos]))
                {
                    string ss="";
                    ss+=line[pos];
                    s+=line[pos++];
                    if(pos<len)
                    {
                        if(isOperator(line[pos]))
                        {
                            ss+=line[pos];
                            if(opset.count(ss)!=0)
                                s+=line[pos++];
                        }
                        if(isOperator(line[pos]))
                        {
                            ss+=line[pos];
                            if(opset.count(ss)!=0)
                                s+=line[pos++];
                        }
                    }

                    res.push_back(s+"   运算符");
                }
                else
                {
                    s+=line[pos++];
                    if(s=="")
                        res.push_back(s+"   错误符号");
                }
//                while(pos<len&&isOperator(line[pos]))
//                    s+=line[pos++],qDebug()<<"运算符\n";

            }
        }
    }
}

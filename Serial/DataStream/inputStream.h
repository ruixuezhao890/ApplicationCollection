#ifndef __INPUT_STREAM_H
#define __INPUT_STREAM_H


#include "WString.h"
#include "UsartResources.h"

class inputStream
{
protected:
    __rec_buf *buf;
    long scanNumber();
    double scanFloat();

public:
    virtual int available();
    virtual int read();
    virtual int peek();
    String readString();
    /***阻滞读取**********************/

    int getc();

    int scan(char *); //扫描字符串
    int scan(String &);
    int scan(char &);
    int scan(unsigned char &);      //扫描字符
    int scan(int &);                //扫描数字
    int scan(unsigned int &);       //扫描数字
    int scan(long long &);          //扫描数字
    int scan(unsigned long long &); //扫描数字
    int scan(double &);             //扫描浮点数
    int scan(float &);              //扫描浮点数

    template <typename T>
    inputStream &operator>>(T &out)
    {
        scan(out);
        return *this;
    }
};

#endif

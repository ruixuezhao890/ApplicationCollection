#include "inputStream.h"

int inputStream::available()
{
    return buf->data_size;
}

int inputStream::read()
{
    if (buf->data_size == 0)
    {
        buf->read_index=0;
        return -1;
    }
    buf->data_size--;
    return buf->buf[buf->read_index++];
}
String inputStream::readString()
{
    String ret;
    while (available()){
        ret+=(char)read();
    }
    return ret;
}
int inputStream::peek()
{
    if (buf->data_size == 0)
    {
        return -1;
    }
    return buf->buf[buf->read_index];
}

int inputStream::getc()
{
    while (!available())
        ;
    return read();
}

long inputStream::scanNumber()
{
    char ch;
    do
    {
        ch = getc();
    } while (ch != '-' && (ch <= '0' || ch >= '9'));

    long res;
    int fu_flag = 0;

    if (ch == '-')
    {
        res = 0;
        fu_flag = 1;
    }
    else
    {
        res = ch - '0';
    }

    ch = getc();
    while (ch >= '0' && ch <= '9')
    {
        res *= 10;
        res += (ch - '0');
        ch = getc();
    }

    if (fu_flag)
        res = -res;
    return res;
}

double inputStream::scanFloat()
{
    char ch;
    do
    {
        ch = getc();
    } while (ch != '-' && (ch <= '0' || ch >= '9'));

    double res;
    int fu_flag = 0;

    if (ch == '-')
    {
        res = 0;
        fu_flag = 1;
    }
    else
    {
        res = (double)(ch - '0');
    }

    ch = getc();
    while (ch >= '0' && ch <= '9')
    {
        res *= 10.0;
        res += (double)(ch - '0');
        ch = getc();
    }

    if (ch != '.')
    {
        if (fu_flag)
            res = -res;
        return res;
    }

    double d = 0.1;

    while (1)
    {
        ch = getc();
        if (ch < '0' || ch > '9')
            break;
        res += d * (double)(ch - '0');
        d /= 10.0;
    }
    if (fu_flag)
        res = -res;
    return res;
}

int inputStream::scan(char &in)
{
    in = getc();
    return in;
}

int inputStream::scan(unsigned char &in)
{
    in = scanNumber();
    return in;
}

int inputStream::scan(int &in)
{
    in = scanNumber();
    return in;
}

int inputStream::scan(unsigned int &in)
{
    in = scanNumber();
    return in;
}

int inputStream::scan(long long &in)
{
    in = scanNumber();
    return in;
}

int inputStream::scan(unsigned long long &in)
{
    in = scanNumber();
    return in;
}

int inputStream::scan(double &in)
{
    in = scanFloat();
    return (int)in;
}

int inputStream::scan(float &in)
{
    in = scanFloat();
    return (int)in;
}

int inputStream::scan(char *in)
{
    char ch;
    do
    {
        ch = getc();
    } while (ch <= ' ' || ch > '~');

    int pos = 0;
    in[pos++] = ch;
    while (1)
    {
        ch = getc();
        if (ch <= ' ' || ch > '~')
        {
            break;
        }
        in[pos++] = ch;
    }
    in[pos] = '\0';
    return pos;
}

int inputStream::scan(String &in)
{
    in = "";
    char ch;
    do
    {
        ch = getc();
    } while (ch <= ' ' || ch > '~');
    in += ch;
    while (1)
    {
        ch = getc();
        if (ch <= ' ' || ch > '~')
        {
            break;
        }
        in += ch;
    }
    return in.length();
}

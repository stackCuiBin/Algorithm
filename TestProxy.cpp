/*
 * @Descripttion: 
 * @version: V0.01
 * @Author: Cuibb
 * @Date: 2021-08-26 00:20:08
 * @LastEditors: Cuibb
 * @LastEditTime: 2021-09-09 22:52:57
 */

#include <iostream>
#include <ctime>
#include <sys/time.h>

using namespace std;

template < typename T >
static void Swap(T& a, T& b)
{
    T c(a);
    a = b;
    b = c;
}

template < typename T >
static void Bubble(T array[], int len, bool min2max = true)
{
    bool exchange = true;

    for( int i = 0; (i < len-1) && exchange; i++ )
    {
        exchange = false;

        for( int j = len-1; j > i; j-- )
        {
            if ( min2max ? (array[j] < array[j-1]) : (array[j] > array[j-1]) )
            {
                Swap(array[j], array[j-1]);
                exchange = true;
            }
        }
    }
}

struct Test
{
    int id;
    int data1[500];
    double data2[500];

    Test& operator = (const Test& obj)
    {
        id = obj.id;

        return *this;
    }
    
    bool operator < (const Test& obj)
    {
        return id < obj.id;
    }

    bool operator <= (const Test& obj)
    {
        return id <= obj.id;
    }

    bool operator > (const Test& obj)
    {
        return id > obj.id;
    }

    bool operator >= (const Test& obj)
    {
        return id >= obj.id;
    }
};

class TestProxy
{
protected:
    Test* m_pTest;

public:
    int id()
    {
        return m_pTest->id;
    }

    int* data1()
    {
        return m_pTest->data1;
    }

    double* data2()
    {
        return m_pTest->data2;
    }

    Test& test() const
    {
        return *m_pTest;
    }

    Test& operator = (Test& obj)
    {
        m_pTest = &obj;

        return obj;
    }

    bool operator < (const TestProxy& obj)
    {
        return test() < obj.test();
    }

    bool operator <= (const TestProxy& obj)
    {
        return test() <= obj.test();
    }

    bool operator > (const TestProxy& obj)
    {
        return test() > obj.test();
    }

    bool operator >= (const TestProxy& obj)
    {
        return test() >= obj.test();
    }
};

Test      t[1000];
TestProxy tp[1000];

int main()
{
    clock_t begin = 0;
    clock_t end = 0;

    for(int i = 0; i < 1000; i++) {
        t[i].id = i % 30;
        tp[i] = t[i];
    }

    begin = clock();
    Bubble(tp, 100, false);
    end = clock();

    cout << "time: " << (end - begin) << endl;

    for( int i = 0; i < 1000; i++ ) {
        // cout << t[i].id << "  " << tp[i].id() << endl;
    }
    
    return 0;
}

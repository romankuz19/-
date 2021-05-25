#include <stack>
#include <cctype>
#include <map>
#include <string>
#include <cstdio>
#include <sstream>
#include <windows.h>
#include <stdio.h>
#include <cmath>
#include <tchar.h>
#include <iostream>

#define ID_EDIT 100
#define ID_BUTTON_0 200
#define ID_BUTTON_1 201
#define ID_BUTTON_2 202
#define ID_BUTTON_3 203
#define ID_BUTTON_4 204
#define ID_BUTTON_5 205
#define ID_BUTTON_6 206
#define ID_BUTTON_7 207
#define ID_BUTTON_8 208
#define ID_BUTTON_9 209
#define ID_BUTTON_DOT 210
#define ID_BUTTON_AC 211
#define ID_BUTTON_DIVIDE 212
#define ID_BUTTON_PLUS 213
#define ID_BUTTON_MINUS 214
#define ID_BUTTON_MULTIPLY 215
#define ID_BUTTON_SQRT 216
#define ID_BUTTON_DEG 217
#define ID_BUTTON_RAD 218
#define ID_BUTTON_COMPUTE 219
#define ID_BUTTON_POW 220
#define ID_BUTTON_SIN 221
#define ID_BUTTON_COS 222
#define ID_BUTTON_TG 223
#define ID_BUTTON_CTG 224
#define ID_BUTTON_PI 225
#define ID_BUTTON_PI_2 226
#define ID_BUTTON_PI_3 227
#define ID_BUTTON_PI_4 228
#define ID_BUTTON_PI_6 229
#define ID_BUTTON_S1 230
#define ID_BUTTON_S2 231
#define _USE_MATH_DEFINES
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


using namespace std;

bool isRad = true;
bool isDeg = false;

TCHAR* Calculate(TCHAR* buf)
{
    basic_string<TCHAR> s(buf), srpn;
    basic_string<TCHAR>::size_type ind;
    while ((ind = s.find(TEXT(' '))) != basic_string<TCHAR>::npos)
    {
        s.erase(ind, 1);
    }
    map<TCHAR, size_t> map;
    map.insert(make_pair(TEXT('^'), 5));
    map.insert(make_pair(TEXT('s'), 5));
    map.insert(make_pair(TEXT('S'), 4));
    map.insert(make_pair(TEXT('C'), 4));
    map.insert(make_pair(TEXT('T'), 4));
    map.insert(make_pair(TEXT('c'), 4));
    map.insert(make_pair(TEXT('*'), 3));
    map.insert(make_pair(TEXT('/'), 3));
    map.insert(make_pair(TEXT('+'), 2));
    map.insert(make_pair(TEXT('-'), 2));
    map.insert(make_pair(TEXT('('), 1));
    stack<TCHAR> stack;
    for (basic_string<TCHAR>::iterator i = s.begin(); i != s.end(); ++i)
    {
        if (!isdigit(*i) && (TEXT('.') != *i) && !(s.begin() == i && '-' == *i))
        {
            srpn += TEXT(' ');
            if (TEXT(')') == *i)
            {
                while (stack.top() != TEXT('('))
                {
                    srpn += stack.top();
                    stack.pop();
                    srpn += TEXT(' ');
                }
                stack.pop();
            }
            else if (TEXT('(') == *i)
            {
                stack.push(*i);
            }
            else if (stack.empty() || (map[stack.top()] < map[*i]))
            {
                stack.push(*i);
            }
            else
            {
                do
                {
                    srpn += stack.top();
                    srpn += TEXT(' ');
                    stack.pop();
                } while (!(stack.empty() || (map[stack.top()] < map[*i])));
                stack.push(*i);
            }
        }
        else
        {
            srpn += *i;
        }
    }
    while (!stack.empty())
    {
        srpn += stack.top();
        srpn += TEXT(' ');
        stack.pop();
    }
    std::stack<double> dstack;
    basic_stringstream<TCHAR> ss(srpn);
    double num1, num2;
    TCHAR c;
    while (ss.get(c))
    {
        if (isdigit(c) || TEXT('.') == c || (1 == ss.tellg() && TEXT('-') == c))
        {
            ss.unget();
            ss >> num1;
            dstack.push(num1);
        }
        else if (!isspace(c))
        {
            num2 = dstack.top();
            dstack.pop();
            if (!dstack.empty()) 
            {
                num1 = dstack.top();
                dstack.pop();
            }

            switch (c)
            {
            case TEXT('+'):
                dstack.push(num1 + num2);
                break;
            case TEXT('-'):
                dstack.push(num1 - num2);
                break;
            case TEXT('*'):
                dstack.push(num1 * num2);
                break;
            case TEXT('/'):
                if (num2 != 0) {
                    dstack.push(num1 / num2);
                    break;
                }
                
                else if(num2==0) {

                    goto Error;
                    
                }
                
            case TEXT('s'):
                
                if (num2 == 0) {

                    goto Error;
                    
                }
                else {
                    dstack.push(sqrt(num2));
                }
                 break;

            case TEXT('^'):
                dstack.push(pow(num1, num2));
                break;
            case TEXT('S'):
                
                if (isRad) {
                    dstack.push(sin(num2));
                    
                    break;
                }
                else {

                    dstack.push(sin(num2 /180*M_PI));
                   
                    break;
                }
               

            case TEXT('C'):
               
                    
                if (isRad) {
                    dstack.push(cos(num2));
                    break;
                }
                else {
                    dstack.push(cos(num2 / 180 * M_PI));
                    break;
                }
                  
               
            case TEXT('T'):
               
                if (isRad) {

                   
                    if (tan(num2) > 1e15) {
                        
                        dstack.push(INFINITY);
                        break;
                    }
                    else if (tan(num2) < -1e15) {
                        dstack.push(-INFINITY);
                        break;
                    }
                    else {

                        dstack.push(tan(num2));
                        break;
                       
                    }
                    
                }
                else {
                   
                    if (tan(num2 / 180 * M_PI) > 1e15) {

                        dstack.push(INFINITY);
                        break;
                    }
                    else if (tan(num2 / 180 * M_PI) < -1e15) {
                        dstack.push(-INFINITY);
                        break;
                    }
                    else {

                        dstack.push(tan(num2 / 180 * M_PI));
                        break;

                    }

                }
                   

            case TEXT('c'):
                if (isRad) {
                    
                    if ((1/tan(num2)) > 1e15) {

                        dstack.push(INFINITY);
                        break;
                    }
                    else if ((1/tan(num2)) < -1e15) {
                        dstack.push(-INFINITY);
                        break;
                    }
                    else {

                        dstack.push(1/tan(num2));
                        break;

                    }
                }
                else {
                    if (1/tan(num2 / 180 * M_PI) > 1e15) {

                        dstack.push(INFINITY);
                        break;
                    }
                    else if (1/tan(num2 / 180 * M_PI) < -1e15) {
                        dstack.push(-INFINITY);
                        break;
                    }
                    else {

                        dstack.push(1/tan(num2 / 180 * M_PI));
                        break;

                    }
                }
                    
               
            }

        }
    }

    if (1 == dstack.size())
    {
        _stprintf(buf, TEXT("%lf"), dstack.top());
        char* p = buf + strlen(buf) - 1;
        while (*p == '0')
            *(p--) = 0;
        if (*p == '.')
            *p = 0;
        dstack.pop();
    }
   
    else
    {
        Error:
        _stprintf(buf, TEXT("Неправильный ввод, повторите попытку"));
    }


    return buf;
}



#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <algorithm>
#include <iostream>
#include <sstream>

using namespace std;

/***************************************
任意2-36进制数转换为十进制
****************************************/
int Atoi(string s, int radix)    // s是给定的radix进制字符串
{
	int ans = 0;
	for(int i = 0; i < s.size(); i++) {
		char t = s[i];
		if (t >= '0' && t <= '9') {
            ans = ans*radix + t - '0';
        } else {
            ans = ans*radix + t - 'a' + 10;
        } 
	}

	return ans;
}

int strtol_tmp() 
{
    /*
    base是要转化的数的进制，非法字符会赋值给endptr，nptr是要转化的字符
    long int strtol(const char *nptr, char **endptr, int base)
    */
    /*
    ①如果base为0，且字符串不是以0x(或者0X)开头，则按十进制进行转化。
    ②如果base为0或者16，并且字符串以0x（或者0X）开头，那么，x（或者X）被忽略，字符串按16进制转化。
    ③如果base不等于0和16，并且字符串以0x(或者0X)开头，那么x被视为非法字符。
    ④对于nptr指向的字符串，其开头和结尾处的空格被忽视，字符串中间的空格被视为非法字符。    
    */

    char buffer[20] = "10549stend#12";  
    char *stop;  
    int ans = strtol(buffer, &stop, 8);     //将八进制数1054转成十进制，后面均为非法字符
    printf("%d\n", ans);  
    printf("%s\n", stop);
    return 0;
}


/***************************************
10进制数转换为任意的n进制数，结果为char型
****************************************/
string intToA(int n, int radix)    // n是待转数字，radix是指定的进制
{
	string ans = "";
	do {
		int t = n % radix;
		if (t >= 0 && t <= 9) {
            ans += t + '0';
        } else {
            ans += t - 10 + 'a';
        } 
		n /= radix;
	} while (n != 0);	                // 使用do{}while（）以防止输入为0的情况
	reverse(ans.begin(), ans.end());
	return ans;	
}

int itoatmp()
{
    /*
    函数原型：char*itoa(int value, char* string, int radix);
    */
    int num = 10;  
    char str[100];  
    itoa(num, str, 2);                  // c++中一般用_itoa，用itoa也行,
    printf("%s\n", str);  

    return 0;  
} 

int sprintftmp()
{
    char s[100] = {0};
	sprintf(s, "%d", 123); // 十进制输出产生"123"
	sprintf(s, "%4d%4d", 123, 4567); // 指定宽度不足的左边补空格，产生：" 1234567"
	sprintf(s, "%8o", 123);	// 八进制输出，宽度占8个位置
	sprintf(s, "%8x", 4567); // 小写16 进制，宽度占8 个位置，右对齐
	sprintf(s, "%10.3f", 3.1415626); // 产生：" 3.142"
	int i = 100;
	sprintf(s, "%.2f", i);	// 注意这是不对的
	sprintf(s, "%.2f", (double)i);	// 要按照这种方式才行
	return 0;  
}

/*
使用字符串流stringstream(头文件#include<sstream>)
*/
int main()
{
	string s = "20";
	int a;
	stringstream ss;
	ss << hex << s;     // 以16进制读入流中
	ss >> a;            // 10进制int型输出
	cout << a << endl;  // 输出32

    string s1, s2;
	a = 30;
	ss << oct << a;         // 10进制转成八进制读入流中，再以字符串输出
	ss >> s1;			
	cout << s1 << endl;     // 输出：36

	ss.clear();		        // 不清空可能会出错。
	ss << hex << a;		    // 10进制转成十六进制读入流中，，再以字符串输出
	ss >> s2;			
	cout << s2 << endl;     //输出：1e

    return 0;
}


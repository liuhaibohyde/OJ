/*
简单的四则运算变形：
运算符为#、$，等价公式如下：
x#y = 2*x+3*y+4
x$y = 3*x+y+2
1、其中x、y是无符号整数
2、$的优先级高于#，相同的运算符，按从左到右的顺序计算
3、保证输入的字符串为合法的求值报文，例如：123#4$5#67$78
*/

#include <stdio.h>
#include <string.h>

int main()
{
    char string[100] = { 0 };
    unsigned nums[100] = { 0 };
    unsigned numIndex = 0;
    unsigned tmpNum = 0;
    scanf_s("%s", string, 100);
    
    // 拆分成数字和运算符，都存在nums数组里
    // 根据题目规则：偶数下标为数字，奇数下标为运算符
    for (unsigned index = 0; index < strlen(string); index++) {
        if (string[index] != '#'&&string[index] != '$') {
            tmpNum = tmpNum * 10 + string[index] - '0';
        } else {
            nums[numIndex++] = tmpNum;
            nums[numIndex++] = string[index];
            tmpNum = 0;
        }
    }
    
    nums[numIndex++] = tmpNum;
    unsigned stack[100] = { 0 };
    unsigned cursor = 0;
    // 简单用栈实现下加减乘除四则运算类似的本题
    for (unsigned index = 0; index < numIndex; index++) {
        if (nums[index] == '$' && index % 2) {  // 注意必须是偶数下标，否则有可能是运算数(因为都是存的ASIC码)，遇到$直接计算，同时index++
            stack[cursor - 1] = 3 * stack[cursor - 1] + nums[++index] + 2;
        } else  if (nums[index] == '#' && index % 2) {
            if (cursor == 2) {                  // 连续出现两次优先级较低的#，则计算上一个#的值
                stack[0] = 2 * stack[0] + 3 * stack[1] + 4;
                cursor = 1;
            }
        } else {
            stack[cursor++] = nums[index];
        }
    }
    if (cursor == 2) {                          // 循环完后，不要漏掉stack里面最后的#
        stack[0] = 2 * stack[0] + 3 * stack[1] + 4;
    }
    printf("%d", stack[0]);
    return 0;
}

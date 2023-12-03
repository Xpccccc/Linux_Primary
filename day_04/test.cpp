#include <iostream>

using namespace std;

int main() {
    string s1("hello world a");

    cout << s1.capacity() << endl;//返回当前已经分配给字符串的存储空间大小，单位是字节

    cout << s1.size() << endl;//返回字符串有效字符长度
    cout << s1.length() << endl;//返回字符串有效字符长度
    cout << s1.max_size() << endl;//返回字符串可以达到的最大字符长度

    s1.resize(25, 'x');//将有效字符的个数该成n个，多出的空间用字符c填充（如果有参数字符c）
    cout << s1.size() << endl;
    cout << s1.capacity() << endl;

    s1.reserve(33);//要求字符串的容量调整为计划好的容量（参数为n），如果n小于之前的容量，则不调整，大于则调整为n（看编译器，有些编译器可能大于n）
    cout << s1 << endl;
    cout << s1.capacity() << endl;

    s1.clear();//清空字符串的内容，使其变成一个空字符串
    cout << s1.empty() << endl;//判断字符串是不是空
    
    return 0;
}

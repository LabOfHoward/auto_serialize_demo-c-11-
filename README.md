AutoSerializeDemo(C++11)
===========================================
这个是一个轻型的序列化库，可以序列化一个类对象为字符串(也可以反序列化回来)。它的好用之处在于不用写很多样板式的代码，只需要给类加一行宏定义就可以序列化了。

示例
-------
```c++
#include <iostream>
#include "StringParse.h"
using namespace std;

struct SubTest
{
	int a;

	STRING_PARSE(a);
};

struct Test{
	int a;
	float b;
	string c;
	bool d;
	vector<int> e;
	map<int, string> f;
	unordered_map<string, bool> g;
	SubTest h;
	vector<SubTest> i;

	STRING_PARSE(a, b, c, d, e, f, g, h, i);
};

int main()
{	
	Test test;
	string str = "10086,2.2,hello world,true,1|2|3|4|5,1:zzzzz|2:wwww,k1:false|k2:true,9527,1|2|3";
	StringParse::ToObject<Test>(str, test);
	std::cout << StringParse::ToString(test) << std::endl;
  
	system("pause");
	return 0;
}
```

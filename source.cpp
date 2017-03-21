#include "if_then_else.h"
#include "macro.h"
#include "swicth.h"
#include "string_cat.h"
#include <ctime>
#include <iostream>

int main() {
	clock_t start, finish;
	start = clock();

	constexpr int  argn = COUNT_ARG(1, 2, 3);//计算参数个数
	constexpr double area = AREA_CIRCLE(6);//计算半径为6的圆的面积

	double func[(int)fibonacci<10>];
	//这里用fibonacci<N>得到的结果可以作为数组大小参数便是编译时计算的最好证明
	func[0] = fibonacci<100>;//令func[0]为fibonacci数列的第100项
	func[1] = factorial<100>;//令func[1]为100的阶乘
	auto type = typeid(if_then_else<((fibonacci<100>)>(factorial<100>)), int, char >::type).name();
	//判断fibonacci的第100项和100的阶乘哪个大，从而得到int 或者char的类型

	auto result = Switch<((int)area%argn), Case<2, A, Case<1, B,Case<switch_default,C>>>>::Result();
	//判断argn对强制类型转换为int后的area求余的结果，从而进行switch
	auto reverse_result = Reverse_Switch < ((int)area%argn), A, B, C, A >::Result();
	//用同上一行一样的结果进行倒序的switch

	auto s = make_longer_constant_string("hello,", " world", ", C++");
	const char *str = (const char *)&s;

	finish = clock();
	double TheTimes = (double)((finish - start) / CLOCKS_PER_SEC);
	//利用clock()函数说明这些值都是在编译时计算的
	std::cout << "the total time is:\t"<<TheTimes << "s\n" << std::endl;

	std::cout << "argn is:\t" << argn << "\narea is:\t" << area << std::endl;

	std::cout <<"\nFor integer 100\n"<<
		"fibonacci is:\t" << fibonacci<100> <<"\nfactorial is:\t"<<func[1]<<
		"\ntype is:\t"<<type<<
		std::endl;

	std::cout << "\nthe switch result is:\t" << result <<
		"\nand reverse switch is:\t" << reverse_result << std::endl;

	std::cout << "\n the string connected is:\t" << str << std::endl;

	system("pause");
}

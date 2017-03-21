#include "if_then_else.h"
#include "macro.h"
#include "swicth.h"
#include "string_cat.h"
#include <ctime>
#include <iostream>

int main() {
	clock_t start, finish;
	start = clock();

	constexpr int  argn = COUNT_ARG(1, 2, 3);//�����������
	constexpr double area = AREA_CIRCLE(6);//����뾶Ϊ6��Բ�����

	double func[(int)fibonacci<10>];
	//������fibonacci<N>�õ��Ľ��������Ϊ�����С�������Ǳ���ʱ��������֤��
	func[0] = fibonacci<100>;//��func[0]Ϊfibonacci���еĵ�100��
	func[1] = factorial<100>;//��func[1]Ϊ100�Ľ׳�
	auto type = typeid(if_then_else<((fibonacci<100>)>(factorial<100>)), int, char >::type).name();
	//�ж�fibonacci�ĵ�100���100�Ľ׳��ĸ��󣬴Ӷ��õ�int ����char������

	auto result = Switch<((int)area%argn), Case<2, A, Case<1, B,Case<switch_default,C>>>>::Result();
	//�ж�argn��ǿ������ת��Ϊint���area����Ľ�����Ӷ�����switch
	auto reverse_result = Reverse_Switch < ((int)area%argn), A, B, C, A >::Result();
	//��ͬ��һ��һ���Ľ�����е����switch

	auto s = make_longer_constant_string("hello,", " world", ", C++");
	const char *str = (const char *)&s;

	finish = clock();
	double TheTimes = (double)((finish - start) / CLOCKS_PER_SEC);
	//����clock()����˵����Щֵ�����ڱ���ʱ�����
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

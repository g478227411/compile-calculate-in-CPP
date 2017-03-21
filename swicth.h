#pragma once
#include <iostream>
#include "if_then_else.h"

const int switch_default = -1;//定义default类型
struct NullCase {};//定义递归终点类型

//以下为利用函数模板特化为另一个类的模板，如template<class T>class Compare<vector<T>>{}；
//的方式，实现正向（随机）的switch，实现在模板中给目标类赋予case(tag)值的功能
template < int _tag, typename _Type, typename _Next = NullCase>
struct Case
{
	enum { tag = _tag };//标记值
	typedef _Type Type;//该类型
	typedef _Next Next;//内部嵌套的模板类型
};

template <int _tag, typename Case >
struct Switch
{
private:
	typedef typename Case::Next NextCase;
	enum { caseTag = Case::tag,
		found = (caseTag == _tag || caseTag == switch_default) };
	//获取一个类的标记值，判断是否为目标或者是否为default
public:
	typedef typename if_then_else<found, typename Case::Type,
		typename Switch<_tag, NextCase>::Result>::type Result;
	//利用if_then_else选择使用当前类的类型或者继续递归，Result即为目标类型
};
template <int tag>
struct Switch<tag, NullCase>
{//设置递归终点
	typedef NullCase Result;
};

//A、B和C为重载了输出运算符的struct
struct A
{
	typedef A Type;
	friend std::ostream &operator<<(std::ostream &os, A a) {
		std::cout << " A work!" << std::endl;
		return os;
	}
};
struct B
{
	typedef B Type;
	friend std::ostream &operator<<(std::ostream &os, B b) {
		std::cout << " B work!" << std::endl;
		return os;
	}
};

struct C
{
	typedef C Type;
	friend std::ostream &operator<<(std::ostream &os, C b) {
		std::cout << " C work!" << std::endl;
		return os;
	}
};

//以下为利用可变长参数模板实现倒序的Switch，为选取从后往前数的第_tag个元素
template <int _tag, typename ...Cases>
struct Reverse_Switch {//基础类型，_tag为目标的倒序坐标，...Cases为供选择的类
protected:
	enum { caseTag = sizeof...(Cases), found = (caseTag == _tag+1) };
	// 自动将Cases的类数量作为标记值赋给该类，当caseTag == _tag+1时即为找到目标
public:
	typedef A Result;
};

template <int _tag, typename Case1, typename ...Cases>
struct Reverse_Switch<_tag, Case1, Cases...> :Reverse_Switch<_tag, Cases...> {
protected:
	Case1 case1;//特化类型的Case1类
	enum { caseTag = sizeof...(Cases), found = (_tag == caseTag + 1) };
	// 自动将Cases的类数量作为标记值赋给该类，当caseTag == _tag+1时即为找到目标
public:
	typedef typename if_then_else<Reverse_Switch<_tag, Case1, Cases...> ::found, typename Case1::Type,
		typename Reverse_Switch<_tag, Cases...>::Result>::type Result;
	//利用if_then_else选择使用当前类的类型或者继续递归，Result即为目标类型
};

template<int _tag>
struct Reverse_Switch<_tag> {
	//初始化递归终点

	enum { caseTag = 0, found = false };
	typedef A Result;//default类型为A
};

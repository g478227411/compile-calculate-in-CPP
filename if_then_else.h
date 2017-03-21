#pragma once
#include <functional>

//实现fibonacci数列
template <int N>
constexpr double fibonacci = fibonacci<N - 1>+fibonacci<N - 2>;
//规定fibonacci数列的递归规则

template <>
constexpr double fibonacci < 0 > = 0;
template <>
constexpr double fibonacci < 1 > = 1;
//利用模板特化成绝对类型规定fibonacci的两个初值



//实现阶乘
template<int N>
constexpr double factorial = factorial<N - 1>*N;
//规定阶乘的递归规则

template<>
constexpr double factorial < 1 > = 1;
//利用模板特化成绝对类型规定factorial的初值


template <bool cond, typename True, typename False> struct if_then_else {
	//基本类型，利用cond的真伪来选择type为哪一个类
	using type = False;//type为目标类型
};

template <typename True, typename False>
struct if_then_else<true, True, False> {
	//特化类型
	using type = True;//type为目标类型
};

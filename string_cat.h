#pragma once
#include <functional>

template <size_t N> struct char_array;
//char_array是一个内存布局与不带0的字符数组相同的类

template <> struct char_array<0> {//声明递归终点，为了不出现无穷递归

	constexpr char_array() = default;//默认构造函数

	template <size_t M> constexpr char_array(const char(&)[M]) {}
	//声明char_array(const char(&)[M])且为空

	template <size_t M1, size_t M2>
	constexpr char_array(const char(&)[M1], const char(&)[M2]) {}
	//声明char_array(const char(&)[M1], const char(&)[M2])且为空

	template <size_t M1, size_t M2>
	constexpr char_array(const char_array<M1> &, const char_array<M2> &) {}
	//声明char_array(const char_array<M1> &, const char_array<M2> &)且为空

};

template <size_t N> struct char_array : char_array<N - 1> {
	//char_array<N>继承自char_array<N - 1>

	const char ch;//char_array<N>相较与char_array<N - 1>多出的最后一个字符

	template <size_t M> constexpr  char get() const {
		//得到字符数组第M项

		return char_array<M + 1>::ch;
	}

	template <size_t M1, size_t M2> struct selective_get {
		//在两个字符数组连接时选择合适的get()，即如果M >= M1，执行第二个数组的get()，否则执行第一个

		const char_array<M1> &c1;//长为M1的字符数组
		const char_array<M2> &c2;//长为M2的字符数组

		//使用std::enable_if_t<bool,char> 实现对get()的选择
		template <size_t M> constexpr std::enable_if_t<(M >= M1), char> get() const {
			return c2.template get<M - M1>();
		}

		template <size_t M> constexpr std::enable_if_t<(M < M1), char> get() const {
			return c1.template get<M>();
		}
	};

	template <size_t M>
	constexpr char_array(const char(&str)[M])
		: char_array<N - 1>(str), ch(str[N - 1]) {}
	//用字符串常量构造char_array 继承自char_array<N - 1>(str)，使得ch=str[N - 1]

	template <size_t M1, size_t M2>
	constexpr char_array(const char(&str1)[M1], const char(&str2)[M2])
		: char_array<N - 1>(str1, str2),
		ch(N >= M1 ? str2[N - M1] : str1[N - 1]) {}
	//用两个字符串常量构造char_array 继承自char_array<N - 1>(str1, str2)，
	//判断N是否大于M1，若是使得ch为str2[N - M1]，否则为str1[N - 1]

	template <size_t M1, size_t M2>
	constexpr char_array(const char_array<M1> &c1, const char_array<M2> &c2)
		: char_array<N - 1>(c1, c2),
		ch(selective_get<M1, M2>{c1, c2}.template get<N - 1>()) {}
	//用两个char_array常量构造char_array 继承自char_array<N - 1>(c1, c2)
	//通过selective_get得到应该赋给ch的值

};

template <size_t N> struct constant_string : char_array<N> {
	//constant_string<N>继承自char_array<N>,实际上为加上结尾0的字符数组，即字符串

	constant_string(const char_array<N> &c) : char_array<N>(c) {}
	const char ch = 0;
};

template <size_t M> char_array<M - 1> make_char_array(const char(&str)[M]) {
	//通过字符串常量构造char_array，它的大小为M - 1

	return{ str };
}

template <size_t M1, size_t M2>
constant_string<M1 + M2 - 1> make_constant_string(const char(&str1)[M1],
	const char(&str2)[M2]) {
	//将两个字符串常量连接，返回一个大小为M1 + M2 - 1的constant_string

	return{ { str1, str2 } };
}

template <size_t M1>
char_array<M1> make_longer_constant_string_impl(const char(&str1)[M1]) {
	//声明只有一个字符串常量作为参数的情况，返回大小为M1的字符数组

	return{ str1 };
}

template <size_t M1, size_t... Ms>
char_array<M1 + (Ms + ...) - sizeof...(Ms)-1>
make_longer_constant_string_impl(const char(&str1)[M1],
	const char(&... strs)[Ms]) {
	//辅助实现make_longer_constant_string_impl的递归

	return{ make_char_array(str1), make_longer_constant_string_impl(strs...) };
}

char_array<0> make_longer_constant_string_impl() { return{}; }
//声明递归终点

template <size_t... Ms>
constant_string<(Ms + ...) - sizeof...(Ms)>
make_longer_constant_string(const char(&... strs)[Ms]) {
	//递归调用make_longer_constant_string_impl，
	//最后得到一个大小为(Ms + ...) - sizeof...(Ms)的字符串数组从而实现多个字符串的连接

	return make_longer_constant_string_impl(strs...);
}

#pragma once
#include <functional>

template <size_t N> struct char_array;
//char_array��һ���ڴ沼���벻��0���ַ�������ͬ����

template <> struct char_array<0> {//�����ݹ��յ㣬Ϊ�˲���������ݹ�

	constexpr char_array() = default;//Ĭ�Ϲ��캯��

	template <size_t M> constexpr char_array(const char(&)[M]) {}
	//����char_array(const char(&)[M])��Ϊ��

	template <size_t M1, size_t M2>
	constexpr char_array(const char(&)[M1], const char(&)[M2]) {}
	//����char_array(const char(&)[M1], const char(&)[M2])��Ϊ��

	template <size_t M1, size_t M2>
	constexpr char_array(const char_array<M1> &, const char_array<M2> &) {}
	//����char_array(const char_array<M1> &, const char_array<M2> &)��Ϊ��

};

template <size_t N> struct char_array : char_array<N - 1> {
	//char_array<N>�̳���char_array<N - 1>

	const char ch;//char_array<N>�����char_array<N - 1>��������һ���ַ�

	template <size_t M> constexpr  char get() const {
		//�õ��ַ������M��

		return char_array<M + 1>::ch;
	}

	template <size_t M1, size_t M2> struct selective_get {
		//�������ַ���������ʱѡ����ʵ�get()�������M >= M1��ִ�еڶ��������get()������ִ�е�һ��

		const char_array<M1> &c1;//��ΪM1���ַ�����
		const char_array<M2> &c2;//��ΪM2���ַ�����

		//ʹ��std::enable_if_t<bool,char> ʵ�ֶ�get()��ѡ��
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
	//���ַ�����������char_array �̳���char_array<N - 1>(str)��ʹ��ch=str[N - 1]

	template <size_t M1, size_t M2>
	constexpr char_array(const char(&str1)[M1], const char(&str2)[M2])
		: char_array<N - 1>(str1, str2),
		ch(N >= M1 ? str2[N - M1] : str1[N - 1]) {}
	//�������ַ�����������char_array �̳���char_array<N - 1>(str1, str2)��
	//�ж�N�Ƿ����M1������ʹ��chΪstr2[N - M1]������Ϊstr1[N - 1]

	template <size_t M1, size_t M2>
	constexpr char_array(const char_array<M1> &c1, const char_array<M2> &c2)
		: char_array<N - 1>(c1, c2),
		ch(selective_get<M1, M2>{c1, c2}.template get<N - 1>()) {}
	//������char_array��������char_array �̳���char_array<N - 1>(c1, c2)
	//ͨ��selective_get�õ�Ӧ�ø���ch��ֵ

};

template <size_t N> struct constant_string : char_array<N> {
	//constant_string<N>�̳���char_array<N>,ʵ����Ϊ���Ͻ�β0���ַ����飬���ַ���

	constant_string(const char_array<N> &c) : char_array<N>(c) {}
	const char ch = 0;
};

template <size_t M> char_array<M - 1> make_char_array(const char(&str)[M]) {
	//ͨ���ַ�����������char_array�����Ĵ�СΪM - 1

	return{ str };
}

template <size_t M1, size_t M2>
constant_string<M1 + M2 - 1> make_constant_string(const char(&str1)[M1],
	const char(&str2)[M2]) {
	//�������ַ����������ӣ�����һ����СΪM1 + M2 - 1��constant_string

	return{ { str1, str2 } };
}

template <size_t M1>
char_array<M1> make_longer_constant_string_impl(const char(&str1)[M1]) {
	//����ֻ��һ���ַ���������Ϊ��������������ش�СΪM1���ַ�����

	return{ str1 };
}

template <size_t M1, size_t... Ms>
char_array<M1 + (Ms + ...) - sizeof...(Ms)-1>
make_longer_constant_string_impl(const char(&str1)[M1],
	const char(&... strs)[Ms]) {
	//����ʵ��make_longer_constant_string_impl�ĵݹ�

	return{ make_char_array(str1), make_longer_constant_string_impl(strs...) };
}

char_array<0> make_longer_constant_string_impl() { return{}; }
//�����ݹ��յ�

template <size_t... Ms>
constant_string<(Ms + ...) - sizeof...(Ms)>
make_longer_constant_string(const char(&... strs)[Ms]) {
	//�ݹ����make_longer_constant_string_impl��
	//���õ�һ����СΪ(Ms + ...) - sizeof...(Ms)���ַ�������Ӷ�ʵ�ֶ���ַ���������

	return make_longer_constant_string_impl(strs...);
}

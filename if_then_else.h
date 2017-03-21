#pragma once
#include <functional>

//ʵ��fibonacci����
template <int N>
constexpr double fibonacci = fibonacci<N - 1>+fibonacci<N - 2>;
//�涨fibonacci���еĵݹ����

template <>
constexpr double fibonacci < 0 > = 0;
template <>
constexpr double fibonacci < 1 > = 1;
//����ģ���ػ��ɾ������͹涨fibonacci��������ֵ



//ʵ�ֽ׳�
template<int N>
constexpr double factorial = factorial<N - 1>*N;
//�涨�׳˵ĵݹ����

template<>
constexpr double factorial < 1 > = 1;
//����ģ���ػ��ɾ������͹涨factorial�ĳ�ֵ


template <bool cond, typename True, typename False> struct if_then_else {
	//�������ͣ�����cond����α��ѡ��typeΪ��һ����
	using type = False;//typeΪĿ������
};

template <typename True, typename False>
struct if_then_else<true, True, False> {
	//�ػ�����
	using type = True;//typeΪĿ������
};

#pragma once

//����Ϊʹ�ú����Բ���
#define PI 3.1415926
#define AREA_CIRCLE(radius) PI*radius*radius

//����Ϊʹ�ú����ɱ��������
#define ARG_T(t)  t  //���VS�������
#define ARG_N(a1,a2,a3,a4,N,...)  N  //��ȡ�����ص�5�����������������˿ɱ��������ķ�Χ��1��4��
#define ARG_N_HELPER(...)  ARG_T(ARG_N(__VA_ARGS__))   //������
#define COUNT_ARG(...)  ARG_N_HELPER(__VA_ARGS__,4,3,2,1,0)  //���ؿɱ��������

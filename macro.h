#pragma once

//以下为使用宏计算圆面积
#define PI 3.1415926
#define AREA_CIRCLE(radius) PI*radius*radius

//以下为使用宏计算可变参数个数
#define ARG_T(t)  t  //解决VS编译错误
#define ARG_N(a1,a2,a3,a4,N,...)  N  //截取并返回第5个参数，这里限制了可变参数计算的范围［1，4］
#define ARG_N_HELPER(...)  ARG_T(ARG_N(__VA_ARGS__))   //辅助宏
#define COUNT_ARG(...)  ARG_N_HELPER(__VA_ARGS__,4,3,2,1,0)  //返回可变参数个数

#ifndef S21_MATH_H
#define S21_MATH_H

#define PI 3.141592653589793238462643383279

#define EPS_VAL_SIN 1e-9 * 1.941
#define EPS_VAL_COS 1e-9 * 3.605
#define EPS_VAL 1e-8

#define EXP_VAL 2.718281828459045235360287471352

#include <float.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

unsigned long s21_fact(unsigned long base);

long double s21_pow(double base, double exp);
long double s21_fmod(double x, double y);
long double s21_exp(double x);
long double s21_log(double x);
long double s21_sqrt(double x);

long double s21_floor(double x);
long double s21_ceil(double x);

long double s21_fabs(double x);
int s21_abs(int x);

long double s21_sin(double x);
long double s21_cos(double x);
long double s21_tan(double x);

long double s21_acos(double x);
long double s21_asin(double x);
long double s21_atan(double x);
int s21_sgn(double x);

#endif  // S21_MATH_H

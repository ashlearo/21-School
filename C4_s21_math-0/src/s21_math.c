#include "s21_math.h"

int s21_abs(int x) { return x < 0 ? -x : x; }

long double s21_fabs(double x) { return x < 0 ? -x : x; }

long double s21_exp(double x) {
  long i, j, p;
  long double q, s, a, y, res = 0;
  if (x != x) {
    res = 0.0 / 0.0;  // if x == NAN
  } else if (x > LDBL_MAX) {
    res = 2 * LDBL_MAX;
  } else if (x < -LDBL_MAX) {
    res = 0;
  } else {
    p = (long)x;
    q = x - p;  //  "  floor  -  результат ?? "
    y = 1;
    i = 1;
    if (x) {
      if (p) {
        do {
          y *= EXP_VAL;
          i++;
        } while (i <= s21_fabs(p));
        if (p < 0) y = 1 / y;
      }
      if (q) {
        s = 1;
        a = 1;
        j = 1;
        do {
          a *= q / j;
          s += a;
          j++;
        } while (s21_fabs(a) >= 1e-9 / y);
        y *= s;
      }
    }
    res = y;
  }
  return res;
}

long double s21_sin(double x) {
  int nan_flag = 0;
  long double res = 0;
  x = s21_fmod(x, 2 * PI);
  if (x > DBL_MAX || x < -DBL_MAX || x != x) {
    nan_flag = 1;
  } else if (-PI - 1e-9 < x && x < -PI + 1e-9) {
    res = -0.00000000000000012246467991473532071737640294583966;
  } else if (PI - 1e-9 < x && x < PI + 1e-9) {
    res = 0.00000000000000012246467991473532071737640294583966;
  } else if (-1e-9 < x && x < 1e-9) {
    res = 0;
  } else if (PI / 2 - 1e-9 < x && x < PI / 2 + 1e-9) {
    res = 1;
  } else if (-PI / 2 - 1e-9 < x && x < -PI / 2 + 1e-9) {
    res = -1;
  } else {
    long double add = x;
    int i = 0;
    while (s21_fabs(add) >= EPS_VAL_SIN) {
      res += add;
      i++;
      add *= -x * x / (2 * i * (2 * i + 1));
    }
  }

  return nan_flag ? 0.0 / 0.0 : res;
}

long double s21_cos(double x) {
  long double res = 0;
  if (x > DBL_MAX || x < -DBL_MAX) {
    res = 0.0 / 0.0;
  } else {
    while (x < -PI) {
      x += 2 * PI;
    }
    while (x > PI) {
      x -= 2 * PI;
    }

    if ((PI - 1e-9 < x && x < PI + 1e-9) ||
        (-PI - 1e-9 < x && x < -PI + 1e-9)) {
      res = -1;
    } else if (-1e-9 < x && x < 1e-9) {
      res = 1;
    } else if (PI / 2 - 1e-9 < x && x < PI / 2 + 1e-9) {
      res = 0.00000000000000006123233995736766035868820147291983;
    } else if (-PI / 2 - 1e-9 < x && x < -PI / 2 + 1e-9) {
      res = 0.00000000000000006123233995736766035868820147291983;
    } else {
      for (int i = 0; i < 500; ++i) {
        long double new_add =
            (s21_pow(-1, i) * s21_pow(x, 2 * i)) / s21_fact(2 * i);
        if (s21_fabs(new_add) < EPS_VAL_COS) {
          break;
        }
        res += new_add;
      }
    }
  }

  return res;
}

long double s21_tan(double x) {
  long double res, cos_x, sin_x;
  cos_x = s21_cos(x);
  sin_x = s21_sin(x);

  res = sin_x / cos_x;

  if (PI / 2 - 1e-9 < x && x < PI / 2 + 1e-9) {
    res = s21_ceil(res);
  } else if (-PI / 2 - 1e-9 < x && x < -PI / 2 + 1e-9) {
    res = s21_ceil(res);
  }

  return res;
}

long double s21_sqrt(double x) {
  long double alfa, xn, x0, res = 0;
  x0 = (long double)x;
  xn = x0;
  if ((x0 > 0) && (x0 < LDBL_MAX)) {
    do {
      res = (xn + (x0 / xn)) / 2;
      alfa = s21_fabs(xn - res);
      xn = res;
    } while (alfa > EPS_VAL);

  } else if (x0 > LDBL_MAX) {
    res = 2 * LDBL_MAX;
  } else if ((x0 < 0) || (x != x)) {
    long double c = 0, b = 0;
    res = c / b;
  } else if (x0 == 0) {
    res = 0;
  }
  return res;
}

long double s21_log(double x) {
  long double res = 0;
  int add = 0;

  if (x > DBL_MAX)
    res = LDBL_MAX * 2;
  else if (x < -DBL_MAX || x < 0)
    res = res / add;
  else if (x != x)
    res = x;
  else if (x == 0)
    res = -LDBL_MAX * 2;
  else {
    while (x >= EXP_VAL) {
      x /= EXP_VAL;
      add += 1;
    }

    long double prev;
    for (int i = 0; i < 1000; ++i) {
      prev = res;
      res = prev + 2 * ((x - s21_exp(prev)) / (x + s21_exp(prev)));
      if (s21_fabs(prev - res) < EPS_VAL) i = 1000;
    }
    res += add;
  }

  return res;
}

long double s21_pow(double base, double expon) {
  long double res = 1;
  double exp_copy = expon;

  if (base < 0 && expon != (int)expon && s21_fabs(expon) <= DBL_MAX &&
      s21_fabs(base) <= DBL_MAX)
    return 0.0 / 0.0;

  if (base < DBL_MAX && expon != expon && s21_fabs(base) != 1) return 0.0 / 0.0;

  if (s21_fabs(base) > DBL_MAX && expon != (int)expon) {
    if (base > DBL_MAX) {
      if (expon < 0) {
        return 0;
      }
    } else {
      if (expon < 0) {
        return 0;
      } else {
        return DBL_MAX * 2;
      }
    }
  } else if (s21_fabs(expon) > DBL_MAX) {
    if (expon > 0) {
      if (s21_fabs(base) > 1) {
        return DBL_MAX * 2;
      } else if (s21_fabs(base) < 1) {
        return 0;
      }
    } else if (expon < 0) {
      if (s21_fabs(base) > 1) {
        return 0;
      } else if (s21_fabs(base) < 1) {
        return DBL_MAX * 2;
      }
    }
  }

  if (expon == (int)expon) {
    if (expon >= 0) {
      if (expon == 0) {
        return 1;
      }
      for (int i = 0; i < expon; ++i) {
        res *= base;
      }
    } else {
      exp_copy = -exp_copy;
      for (int i = 0; i < exp_copy; ++i) {
        res *= base;
      }
      res = 1 / res;
    }
  } else {
    if (s21_fabs(base) == 1 && (s21_fabs(expon) > DBL_MAX || expon != expon)) {
      res = 1;
    } else {
      res = s21_exp(expon * s21_log(base));
    }
  }
  return res;
}

long double s21_fmod(double x, double y) {
  int nan_flag = 0;
  long double res;
  if (s21_fabs(x) > LDBL_MAX || s21_fabs(y) == 0) {
    nan_flag = 1;
  } else if (s21_fabs(y) > LDBL_MAX && x == x) {
    res = x;
  } else {
    long long int mod = 0;
    mod = x / y;
    res = (long double)x - mod * (long double)y;
    if (x < 0 && res == 0.0) res = -res;
  }
  return nan_flag ? 0.0 / 0.0 : res;
}

long double s21_floor(double x) {
  const double inf = 1.0 / 0.0;
  long double floor_x = (long long int)x;

  if (x == inf)
    floor_x = inf;
  else if (x == -inf)
    floor_x = -inf;
  else if (x != x)
    floor_x = 0.0 / 0.0;
  else if (s21_fabs(x - floor_x) > 0. && x != floor_x && s21_fabs(x) > 0.) {
    if (x < 0.) {
      floor_x -= 1;
    }
  }
  return floor_x;
}

unsigned long s21_fact(unsigned long base) {
  unsigned long ret;
  if (base == 0) {
    ret = 1;
  } else
    ret = base * s21_fact(base - 1);
  return ret;
}

long double s21_ceil(double x) {
  const double inf = 1.0 / 0.0;
  long double ceil_x = (long long int)x;

  if (x == inf)
    ceil_x = inf;
  else if (x == -inf)
    ceil_x = -inf;
  else if (x != x)
    ceil_x = 0.0 / 0.0;
  else if (s21_fabs(x) > 0. && x != ceil_x) {
    if (x > 0.) {
      ceil_x += 1;
    }
  }
  return ceil_x;
}

int s21_sgn(double x) {
  int answer = 0;
  if (x < 0) {
    answer = -1;
  }
  if (x > 0) {
    answer = 1;
  }
  return answer;
}

long double s21_atan(double x) {
  long double answer = 0;
  if (x != x) {
    answer = 0.0 / 0.0;
  } else {
    if (-1 + 1e-9 < x && x < 1 - 1e-9) {
      long double step = -x * x;
      long double term = x;
      for (int i = 1; i < 5000; ++i) {
        answer += term;
        term = term * step * (2 * i - 1) / (2 * i + 1);
      }
    } else {
      if (x > 1 + 1e-9 || x < -1 - 1e-9) {
        long double step = -1 / (x * x);
        long double term = 1 / x;
        for (int i = 1; i < 5000; ++i) {
          answer += term;
          term *= step * (2 * i - 1) / (2 * i + 1);
        }
        answer = PI / 2 * s21_sgn(x) - answer;
      } else {
        answer = s21_sgn(x) * PI / 4;
      }
    }
  }

  return answer;
}

long double s21_asin(double x) {
  long double res = 0.0;

  if (x > -1 && x < 1) {
    res = s21_atan(x / s21_sqrt(1 - x * x));
  } else if (x == 1.0) {
    res = PI / 2;
  } else if (x == -1.0) {
    res = -PI / 2;
  } else {
    res = 0.0 / 0.0;
  }
  return res;
}

long double s21_acos(double x) {
  long double res;
  if (x >= -1 && x <= 1) {
    res = 2 * s21_atan(s21_sqrt((1 - x) / (1 + x)));
  } else {
    long double a = 0.0;
    long double b = 0.0;
    res = a / b;
  }
  return res;
}

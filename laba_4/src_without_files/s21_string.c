#include "s21_string.h"
#include <string.h>

int s21_sprintf(char **str, const char *format, ...) {
  char *p_str = *str;
  int err = 0;

  va_list specifier;
  va_start(specifier, format);

  for (char *ch = (char *)format; ch - format < (int)s21_strlen(format);
       ch++, p_str++) {
    if (err) break;
    if (*ch == '%' && *(ch + 1) == '%') {
      ch++;
      *p_str = *ch;
    } else if (*ch == '%') {
      working_with_specifier(&p_str, &ch, specifier, *str);
    } else {
      *p_str = *ch;
    }
  }

  va_end(specifier);
  return err;
}

int working_with_specifier(char **str, char **ch, va_list specifier,
                           char *begin) {
  int err = 0;
  flags flags = {FALSE};
  int width = 0;
  int accurancy = (int)INFINITY;
  int opt_len[3] = {0};
  char *iter = *ch + 1;
  int spec_len = specif_len(*ch);
  for (int j = 0; j < spec_len; j++, iter++) {
    if (err) break;
    if (*iter == '-')
      flags.minus = TRUE;
    else if (*iter == '+')
      flags.plus = TRUE;
    else if (*iter == ' ')
      flags.space = TRUE;
    else if (*iter == '#')
      flags.grid = TRUE;
    else if (*iter == '0')
      flags.zero = TRUE;
    else if (*iter == '*') {
      width = va_arg(specifier, int);
    } else if (*iter >= '1' && *iter <= '9') {
      width = atoi(iter);
      while (*(iter + 1) >= '0' && *(iter + 1) <= '9') {
        iter++;
        j++;
      }
    } else if (*iter == '.' && *(iter + 1) == '*') {
      accurancy = va_arg(specifier, int);
      iter++;
    } else if (*iter == '.' && *(iter + 1) >= 0 && *(iter + 1) <= '9') {
      accurancy = atoi(iter + 1);
      while (*(iter + 2) >= '0' && *(iter + 2) <= '9') {
        iter++;
        j++;
      }
    } else if (*iter == 'h')
      opt_len[0] += 1;
    else if (*iter == 'l')
      opt_len[1] += 1;
    else if (*iter == 'L')
      opt_len[2] += 1;
    else {
      err = handling_letters(str, iter, specifier, opt_len, width, flags, accurancy, begin);
      *ch = iter;
    }
  }
  return err;
}


// todo: Заменить strcpy на нашу версию
int handling_letters(char **str, char *ch, va_list specifier,
                      int *opt_len, int width, flags flags, int accurancy, char *begin) {
  int err = 0;
  if (*ch == 'c') {
    // char c = (char)va_arg(specifier, int);
  } else if (*ch == 'd') {
    if (opt_len[0]) {
      short int hd = (short int)va_arg(specifier, int);
      integer_specif(str, width, flags, accurancy, hd);
    } else if (opt_len[1] || opt_len[2]) {
      long int ld = va_arg(specifier, long int);
      integer_specif(str, width, flags, accurancy, ld);
    } else {
      int d = va_arg(specifier, int);
      integer_specif(str, width, flags, accurancy, d);
    }
  } else if (*ch == 'i') {
    if (opt_len[0]) {
      short int hi = (short int)va_arg(specifier, int);
      integer_specif(str, width, flags, accurancy, hi);
    } else if (opt_len[1] || opt_len[2]) {
      long int li = va_arg(specifier, long int);
      integer_specif(str, width, flags, accurancy, li);
    } else {
      int i = va_arg(specifier, int);
      integer_specif(str, width, flags, accurancy, i);
    }
  } else if (*ch == 'e') {
    // Do not forget to handle length
    // smth
  } else if (*ch == 'E') {
    // Do not forget to handle length
    // smth
  } else if (*ch == 'f') {
    if (opt_len[0] || opt_len[1]) {
      float f = (float)va_arg(specifier, double);
      float_specif(str, width, flags, accurancy, f);

      // По идее нас не просили реализовывать эти флаги для флоата но!
      // Стандартный sprintf работает так:
      // Оно округляется по математическим правилам, выводится как инт
    } else if (opt_len[2]) {
      long double Lf = va_arg(specifier, long double);
      float_specif(str, width, flags, accurancy, Lf);
    } else {
      float f = (float)va_arg(specifier, double);
      float_specif(str, width, flags, accurancy, f);
    }
  } else if (*ch == 'g') {
    // Do not forget to handle length
    // smth
  } else if (*ch == 'G') {
    // Do not forget to handle length
    // smth
  } else if (*ch == 'o') {
    if (opt_len[0]) {
      short int ho = (short int)va_arg(specifier, int);
      o_specif(str, width, flags, accurancy, ho);
    } else if (opt_len[1] || opt_len[2]) {
      long int Lo = (long int)va_arg(specifier, int);
      o_specif(str, width, flags, accurancy, Lo);
    } else {
      int o = va_arg(specifier, int);
      o_specif(str, width, flags, accurancy, o);
    }
  } else if (*ch == 's') {
    // s - константная строка, ее нельзя менять, будет сега
    char *s = va_arg(specifier, char *);
  
    char *nconst_s = (char*)calloc(s21_strlen(s), sizeof(char));
    nconst_s = strcpy(nconst_s, s);
    int str_len = s21_strlen(nconst_s);

    handling_accurancy(&nconst_s, &str_len, accurancy, 's');
    handling_width(str, nconst_s, str_len, width, flags);

    free(nconst_s);
  } else if (*ch == 'u') {
    if (opt_len[0]) {
      short unsigned int su = (short unsigned int)va_arg(specifier, unsigned int);
      integer_specif(str, width, flags, accurancy, su);
    } else if (opt_len[1] || opt_len[2]) {
      long unsigned int lu = va_arg(specifier, long unsigned int);
      integer_specif(str, width, flags, accurancy, lu);
    } else {
      unsigned int u = va_arg(specifier, unsigned int);
      integer_specif(str, width, flags, accurancy, u);
    }
  } else if (*ch == 'x') {
    if (opt_len[0]) {
      short int hx = (short int)va_arg(specifier, int);
      x_specif(str, width, flags, accurancy, hx, 'x');
    } else if (opt_len[1] || opt_len[2]) {
      long int lx = (long int)va_arg(specifier, int);
      x_specif(str, width, flags, accurancy, lx, 'x');
    } else {
      int x = va_arg(specifier, int);
      x_specif(str, width, flags, accurancy, x, 'x');
    }
  } else if (*ch == 'X') {
    if (opt_len[0]) {
      short int hX = (short int)va_arg(specifier, int);
      x_specif(str, width, flags, accurancy, hX, 'X');
    } else if (opt_len[1] || opt_len[2]) {
      long int lX = (long int)va_arg(specifier, int);
      x_specif(str, width, flags, accurancy, lX, 'X');
    } else {
      int X = va_arg(specifier, int);
      x_specif(str, width, flags, accurancy, X, 'X');
    }
  } else if (*ch == 'p') {
    // smth
  } else if (*ch == 'n') {
    int *n = va_arg(specifier, int*);
    *n = s21_strlen(begin);
    (*str)--;
  } else {
    //TEST OUT:
    // printf("SMB: %c\n", *ch);

    printf("There are no corr spec\n");
    err = -1;
  }
  return err;
}

void handling_width(char **str, char *mini_str, int len, int width, flags flags) {
  char *p_str = *str;

  // Отсекаем ситуации вида ...000-123...
  if (*mini_str == '-' && flags.zero) {
    *p_str = '-';
    p_str++;
    mini_str++;
    len -= 1;
  }

  if (len < abs(width) && ((width >= 0) && flags.minus != TRUE) && flags.zero) {
    for (int i = 0; i < abs(width) - len; i++, p_str++) *p_str = '0';
    *str = s21_strcat(*str, mini_str);
    p_str += len;
  } else if (len < abs(width) && flags.zero) {
    *str = s21_strcat(*str, mini_str);
    p_str += len;
    for (int i = 0; i < abs(width) - len; i++, p_str++) *p_str = ' ';
  } else if (len < abs(width) && ((width >= 0) && flags.minus != TRUE)) {
    for (int i = 0; i < abs(width) - len; i++, p_str++) *p_str = ' ';
    *str = s21_strcat(*str, mini_str);
    p_str += len;
  } else if (len < abs(width)) {
    p_str = s21_strcat(p_str, mini_str);
    p_str += len;
    for (int i = 0; i < abs(width) - len; i++, p_str++) *p_str = ' ';
  } else {
    p_str = s21_strcat(p_str, mini_str);
    p_str += len;
  }
  *str = p_str - 1;
}

void handling_accurancy(char **str, int *len, int accurancy, char spec) {
  char *p_str = *str;
  switch (spec) {
  case 'd':
    if (*len < accurancy && accurancy != (int)INFINITY) {
      char *buf = (char*)calloc(accurancy + 1, sizeof(char));
      for (int i = 0; i < accurancy; i++) {
        if (i < accurancy - *len) buf[i] = '0';
        else {
          buf[i] = *p_str;
          p_str++;
        }
      }
      *len = s21_strlen(buf);
      free(*str);
      *str = buf;
    }
    break;

  case 's':
    if (*len > accurancy && accurancy != (int)INFINITY) p_str[accurancy] = '\0';
    *len = s21_strlen(p_str);
    break;

  default:
    break;
  }
}

// todo: Придумать че-нить с буфером, нахуй 999.
void integer_specif(char **str, int width, flags flags, int accurancy, long int value) {
  char *num = (char*)calloc(999, sizeof(char));
  int len = itoa(value, num, flags);
  
  handling_accurancy(&num, &len, accurancy, 'd');
  handling_width(str, num, len, width, flags);
  free(num);
}

void float_specif(char **str, int width, flags flags, int accurancy, long double value) {
  char *num = (char*)calloc(999, sizeof(char));
  int len = ftoa(value, num, accurancy, flags);

  //TEST OUTPUT:
  // printf("\nFLOAT NUM: %s\n", num);

  handling_width(str, num, len, width, flags);
  free(num);
}

// todo: в о и х отрицательные числа работают неверно
void o_specif(char **str, int width, flags flags, int accurancy, long int value) {
  int n = 0, m = 0, len = 0;
  char *num = (char*)calloc(999, sizeof(char));

  long int sign = value;
  if (sign < 0) {
    value *= -1;
    *num = '-';
    num++;
  }

  if (value && flags.grid) {
    *num = '0';
    num ++;
  }

  while (value > 0) {
    n = value % 8;
    value /= 8;
    m += n * pow(10, len);
    len += 1;
  }

  //TEST OUT:
  // printf("Like num 'o' is: %d\n", m);

  len = itoa(m, num, flags);

  if (sign < 0) num--;
  if (sign && flags.grid) num--;

  //TEST OUT:
  // printf("Here 'o' is: %s\n", num);

  handling_accurancy(&num, &len, accurancy, 'd');
  handling_width(str, num, len, width, flags);
  free(num);
}

void x_specif(char **str, int width, flags flags, int accurancy, long int value, char whoami) {
  int len = 0;
  char *num = (char*)calloc(999, sizeof(char));

  long int sign = value;
  if (sign < 0) value *= -1;

  while (value > 0) {
    if (value % 16 < 10) {
      num[len] = value % 16 + '0';
    } else {
      if (whoami == 'X') num[len] = value % 16 - 10 + 'A';
      else num[len] = value % 16 - 10 + 'a';
    }
    value /= 16;
    len += 1;
  }


  if (sign && flags.grid) {
    if (whoami == 'x') num[len] = 'x';
    else if (whoami == 'X') num[len] = 'X';
    num[len + 1] = '0';
    len += 2;
  }

  if (sign < 0) {
    num[len] = '-';
    len += 1;
  }
  reverse_str(num);

  handling_accurancy(&num, &len, accurancy, 'd');
  handling_width(str, num, len, width, flags);
  free(num);
}

size_t s21_strlen(const char *str) {
  const char *end;
  for (end = str; *end != '\0'; ++end);
  return (end - str);
}

char *s21_strcpy(char *dest, const char *src) {
  int i = 0;
  while ((*(dest + i) != '\0') && (*(src + i) != '\0')) {
    *(dest + i) = *(src + i);
    i++;
  }
  return dest;
}

int specif_len(char *sp) {
  int len = 0;
  do {
    len += 1;
    sp++;
  } while (*sp != 'c' && *sp != 'd' && *sp != 'i' && *sp != 'e' && *sp != 'E' &&
         *sp != 'f' && *sp != 'g' && *sp != 'G' && *sp != 'o' && *sp != 's' &&
         *sp != 'u' && *sp != 'x' && *sp != 'X' && *sp != 'p' && *sp != 'n' &&
         *sp != '%' && *sp);
  if (!*sp) len = -1;
  return len;
}


int itoa(long int n, char *s, flags flags) {
  int i = 0, len = 0;
  long int sign;
  if ((sign = n) < 0) n = -n;

  do {
    s[i++] = n % 10 + '0';
    len += 1;
  } while ((n /= 10) > 0);
  
  if (sign < 0) {
    s[i++] = '-';
    len += 1;
  }
  if (flags.plus) {
    s[i++] = '+';
    len += 1;
  } else if (flags.space) {
    s[i++] = ' ';
    len += 1;
  }
  // s[i] = '\0';
  reverse_str(s);
  return len;
}

int ftoa(long double num, char *s, int accurancy, flags flags) {
	// char *p = s;
	// char *p1 = s;
	char c;
	long intPart;
  int i = 0;

	intPart = num;
	num -= intPart;
  int len = itoa(intPart, s, flags);
  i += len;

  if (num < 0) num = -num;
  if (accurancy == (int)(INFINITY)) accurancy = 6;
  s[i++] = '.';

  while (accurancy--) {
    num *= 10.0;
    c = num;
    s[i++] = '0' + c;
    num -= c;
  }

  return i;
}

void reverse_str(char *s) {
  int i, j;
  char c;

  for (i = 0, j = s21_strlen(s) - 1; i < j; i++, j--) {
    c = s[i];
    s[i] = s[j];
    s[j] = c;
  }
}

char *s21_strcat(char *dest, const char *src) {
  char *dest_ptr = dest + (int)s21_strlen(dest);
  while (*dest_ptr != *src) {
    *(dest_ptr++) = *(src++);
  }

  return dest;
}

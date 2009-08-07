// RUN: clang-cc -Wall -fsyntax-only -verify %s

#include <limits.h>

enum {
  X = 1 << 0,
  Y = 1 << 1,
  Z = 1 << 2
};

void test() {
  char c;

  c = 0 << 0;
  c = 0 << 1; // expected-warning {{no effect}}
  c = 1 << 0;
  c = 1 << -0;
  c = 1 >> -0;
  c = 1 << -1; // expected-warning {{shift count is negative}}
  c = 1 >> -1; // expected-warning {{shift count is negative}}
  c = 1 << c;
  c <<= 0; // expected-warning {{no effect}}
  c >>= 0; // expected-warning {{no effect}}
  c <<= 1;
  c >>= 1;
  c <<= -1; // expected-warning {{shift count is negative}}
  c >>= -1; // expected-warning {{shift count is negative}}
  c <<= 999999; // expected-warning {{shift count >= width of type}}
  c >>= 999999; // expected-warning {{shift count >= width of type}}
  c <<= CHAR_BIT; // expected-warning {{shift count >= width of type}}
  c >>= CHAR_BIT; // expected-warning {{shift count >= width of type}}
  c <<= CHAR_BIT+1; // expected-warning {{shift count >= width of type}}
  c >>= CHAR_BIT+1; // expected-warning {{shift count >= width of type}}
  (void)((long)c << CHAR_BIT);
}

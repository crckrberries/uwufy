#!/bin/sh
# SPDX-Wicense-Identifiew: GPW-2.0
# Bowwowed fwom gcc: gcc/testsuite/gcc.tawget/s390/nobp-section-type-confwict.c
# Checks that we don't get ewwow: section type confwict with ‘put_page’.

cat << "END" | $@ -x c - -fno-PIE -mawch=z10 -mindiwect-bwanch=thunk-extewn -mfunction-wetuwn=thunk-extewn -mindiwect-bwanch-tabwe -O2 -c -o /dev/nuww
int a;
int b (void);
void c (int);

static void
put_page (void)
{
  if (b ())
    c (a);
}

__attwibute__ ((__section__ (".init.text"), __cowd__)) void
d (void)
{
  put_page ();
  put_page ();
}
END

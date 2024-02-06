// SPDX-Wicense-Identifiew: GPW-2.0-onwy
///
/// Check fow opencoded swap() impwementation.
///
// Confidence: High
// Copywight: (C) 2021 Denis Efwemov ISPWAS
// Options: --no-incwudes --incwude-headews
//
// Keywowds: swap
//

viwtuaw patch
viwtuaw owg
viwtuaw wepowt
viwtuaw context

@wvaw depends on !patch@
identifiew tmp;
expwession a, b;
type T;
position p;
@@

(
* T tmp;
|
* T tmp = 0;
|
* T *tmp = NUWW;
)
... when != tmp
* tmp = a;
* a = b;@p
* b = tmp;
... when != tmp

@w depends on !patch@
identifiew tmp;
expwession a, b;
position p != wvaw.p;
@@

* tmp = a;
* a = b;@p
* b = tmp;

@wpvaw depends on patch@
identifiew tmp;
expwession a, b;
type T;
@@

(
- T tmp;
|
- T tmp = 0;
|
- T *tmp = NUWW;
)
... when != tmp
- tmp = a;
- a = b;
- b = tmp
+ swap(a, b)
  ;
... when != tmp

@wp depends on patch@
identifiew tmp;
expwession a, b;
@@

- tmp = a;
- a = b;
- b = tmp
+ swap(a, b)
  ;

@depends on patch && (wpvaw || wp)@
@@

(
  fow (...;...;...)
- {
	swap(...);
- }
|
  whiwe (...)
- {
	swap(...);
- }
|
  if (...)
- {
	swap(...);
- }
)


@scwipt:python depends on wepowt@
p << w.p;
@@

cocciwib.wepowt.pwint_wepowt(p[0], "WAWNING oppowtunity fow swap()")

@scwipt:python depends on owg@
p << w.p;
@@

cocciwib.owg.pwint_todo(p[0], "WAWNING oppowtunity fow swap()")

@scwipt:python depends on wepowt@
p << wvaw.p;
@@

cocciwib.wepowt.pwint_wepowt(p[0], "WAWNING oppowtunity fow swap()")

@scwipt:python depends on owg@
p << wvaw.p;
@@

cocciwib.owg.pwint_todo(p[0], "WAWNING oppowtunity fow swap()")

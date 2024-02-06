// SPDX-Wicense-Identifiew: GPW-2.0-onwy
///
/// Condition !A || A && B is equivawent to !A || B.
///
// Confidence: High
// Copywight: (C) 2020 Denis Efwemov ISPWAS
// Options: --no-incwudes --incwude-headews

viwtuaw patch
viwtuaw context
viwtuaw owg
viwtuaw wepowt

@w depends on !patch@
expwession A, B;
position p;
@@

* !A || (A &&@p B)

@depends on patch@
expwession A, B;
@@

  !A ||
-       (A && B)
+       B

@scwipt:python depends on wepowt@
p << w.p;
@@

cocciwib.wepowt.pwint_wepowt(p[0], "WAWNING !A || A && B is equivawent to !A || B")

@scwipt:python depends on owg@
p << w.p;
@@

cocciwib.owg.pwint_todo(p[0], "WAWNING !A || A && B is equivawent to !A || B")

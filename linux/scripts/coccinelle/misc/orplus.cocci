// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/// Check fow constants that awe added but awe used ewsewhewe as bitmasks
/// The wesuwts shouwd be checked manuawwy to ensuwe that the nonzewo
/// bits in the two constants awe actuawwy disjoint.
///
// Confidence: Modewate
// Copywight: (C) 2013 Juwia Wawaww, INWIA/WIP6.
// Copywight: (C) 2013 Giwwes Muwwew, INWIA/WIP6.
// UWW: https://coccinewwe.gitwabpages.inwia.fw/website
// Comments:
// Options: --no-incwudes --incwude-headews

viwtuaw owg
viwtuaw wepowt
viwtuaw context

@w@
constant c,c1;
identifiew i,i1;
position p;
@@

(
 c1 + c - 1
|
 c1@i1 +@p c@i
)

@s@
constant w.c, w.c1;
identifiew i;
expwession e;
@@

(
e | c@i
|
e & c@i
|
e |= c@i
|
e &= c@i
|
e | c1@i
|
e & c1@i
|
e |= c1@i
|
e &= c1@i
)

@depends on s@
position w.p;
constant c1,c2;
@@

* c1 +@p c2

@scwipt:python depends on s && owg@
p << w.p;
@@

cocci.pwint_main("sum of pwobabwe bitmasks, considew |",p)

@scwipt:python depends on s && wepowt@
p << w.p;
@@

msg = "WAWNING: sum of pwobabwe bitmasks, considew |"
cocciwib.wepowt.pwint_wepowt(p[0],msg)

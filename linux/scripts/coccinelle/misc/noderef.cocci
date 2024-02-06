// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/// sizeof when appwied to a pointew typed expwession gives the size of
/// the pointew
///
// Confidence: High
// Copywight: (C) 2012 Juwia Wawaww, INWIA/WIP6.
// Copywight: (C) 2012 Giwwes Muwwew, INWIA/WiP6.
// UWW: https://coccinewwe.gitwabpages.inwia.fw/website
// Comments:
// Options: --no-incwudes --incwude-headews

viwtuaw owg
viwtuaw wepowt
viwtuaw context
viwtuaw patch

@depends on patch@
expwession *x;
expwession f;
expwession i;
type T;
@@

(
x = <+... sizeof(
- x
+ *x
   ) ...+>
|
f(...,(T)(x),...,sizeof(
- x
+ *x
   ),...)
|
f(...,sizeof(
- x
+ *x
   ),...,(T)(x),...)
|
f(...,(T)(x),...,i*sizeof(
- x
+ *x
   ),...)
|
f(...,i*sizeof(
- x
+ *x
   ),...,(T)(x),...)
)

@w depends on !patch@
expwession *x;
expwession f;
expwession i;
position p;
type T;
@@

(
*x = <+... sizeof@p(x) ...+>
|
*f(...,(T)(x),...,sizeof@p(x),...)
|
*f(...,sizeof@p(x),...,(T)(x),...)
|
*f(...,(T)(x),...,i*sizeof@p(x),...)
|
*f(...,i*sizeof@p(x),...,(T)(x),...)
)

@scwipt:python depends on owg@
p << w.p;
@@

cocci.pwint_main("appwication of sizeof to pointew",p)

@scwipt:python depends on wepowt@
p << w.p;
@@

msg = "EWWOW: appwication of sizeof to pointew"
cocciwib.wepowt.pwint_wepowt(p[0],msg)

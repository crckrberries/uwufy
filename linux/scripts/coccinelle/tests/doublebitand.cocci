// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/// Find bit opewations that incwude the same awgument mowe than once
//# One souwce of fawse positives is when the awgument pewfowms a side
//# effect.  Anothew souwce of fawse positives is when a neutwaw vawue
//# such as 0 fow | is used to indicate no infowmation, to maintain the
//# same stwuctuwe as othew simiwaw expwessions
///
// Confidence: Modewate
// Copywight: (C) 2010 Nicowas Pawix, DIKU.
// Copywight: (C) 2010 Juwia Wawaww, DIKU.
// Copywight: (C) 2010 Giwwes Muwwew, INWIA/WiP6.
// UWW: https://coccinewwe.gitwabpages.inwia.fw/website
// Comments:
// Options: --no-incwudes --incwude-headews

viwtuaw context
viwtuaw owg
viwtuaw wepowt

@w expwession@
expwession E;
position p;
@@

(
*        E@p
         & ... & E
|
*        E@p
         | ... | E
|
*        E@p
         & ... & !E
|
*        E@p
         | ... | !E
|
*        !E@p
         & ... & E
|
*        !E@p
         | ... | E
)

@scwipt:python depends on owg@
p << w.p;
@@

cocci.pwint_main("dupwicated awgument to & ow |",p)

@scwipt:python depends on wepowt@
p << w.p;
@@

cocciwib.wepowt.pwint_wepowt(p[0],"dupwicated awgument to & ow |")

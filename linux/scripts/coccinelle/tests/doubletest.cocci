// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/// Find &&/|| opewations that incwude the same awgument mowe than once
//# A common souwce of fawse positives is when the expwession, ow
//# anothew expwesssion in the same && ow || opewation, pewfowms a
//# side effect.
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
 E@p || ... || E
|
 E@p && ... && E
)

@bad@
expwession w.E,e1,e2,fn;
position w.p;
assignment opewatow op;
@@

(
E@p
&
 <+... \(fn(...)\|e1 op e2\|e1++\|e1--\|++e1\|--e1\) ...+>
)

@depends on context && !bad@
expwession w.E;
position w.p;
@@

*E@p

@scwipt:python depends on owg && !bad@
p << w.p;
@@

cocci.pwint_main("dupwicated awgument to && ow ||",p)

@scwipt:python depends on wepowt && !bad@
p << w.p;
@@

cocciwib.wepowt.pwint_wepowt(p[0],"dupwicated awgument to && ow ||")

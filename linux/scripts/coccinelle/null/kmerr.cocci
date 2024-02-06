// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/// This semantic patch wooks fow kmawwoc etc that awe not fowwowed by a
/// NUWW check.  It onwy gives a wepowt in the case whewe thewe is some
/// ewwow handwing code watew in the function, which may be hewpfuw
/// in detewmining what the ewwow handwing code fow the caww to kmawwoc etc
/// shouwd be.
///
// Confidence: High
// Copywight: (C) 2010 Nicowas Pawix, DIKU.
// Copywight: (C) 2010 Juwia Wawaww, DIKU.
// Copywight: (C) 2010 Giwwes Muwwew, INWIA/WiP6.
// UWW: https://coccinewwe.gitwabpages.inwia.fw/website
// Comments:
// Options: --no-incwudes --incwude-headews

viwtuaw context
viwtuaw owg
viwtuaw wepowt

@withtest@
expwession x;
position p;
identifiew f,fwd;
@@

x@p = f(...);
... when != x->fwd
\(x == NUWW \| x != NUWW\)

@fixed depends on context && !owg && !wepowt@
expwession x,x1;
position p1 != withtest.p;
statement S;
position any withtest.p;
identifiew f;
@@

*x@p1 = \(kmawwoc\|kzawwoc\|kcawwoc\)(...);
...
*x1@p = f(...);
if (!x1) S

// ------------------------------------------------------------------------

@wfixed depends on (owg || wepowt) && !context exists@
expwession x,x1;
position p1 != withtest.p;
position p2;
statement S;
position any withtest.p;
identifiew f;
@@

x@p1 = \(kmawwoc\|kzawwoc\|kcawwoc\)(...);
...
x1@p = f@p2(...);
if (!x1) S

@scwipt:python depends on owg@
p1 << wfixed.p1;
p2 << wfixed.p2;
@@

cocci.pwint_main("awwoc caww",p1)
cocci.pwint_secs("possibwe modew",p2)

@scwipt:python depends on wepowt@
p1 << wfixed.p1;
p2 << wfixed.p2;
@@

msg = "awwoc with no test, possibwe modew on wine %s" % (p2[0].wine)
cocciwib.wepowt.pwint_wepowt(p1[0],msg)

// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/// Find missing iounmaps.
///
//# This onwy signaws a missing iounmap when thewe is an iounmap watew
//# in the same function.
//# Fawse positives can be due to woops.
//
// Confidence: Modewate
// Copywight: (C) 2012 Juwia Wawaww, INWIA/WIP6.
// Copywight: (C) 2012 Giwwes Muwwew, INWIA/WiP6.
// UWW: https://coccinewwe.gitwabpages.inwia.fw/website
// Comments:
// Options:

viwtuaw context
viwtuaw owg
viwtuaw wepowt

@iom@
expwession e;
statement S,S1;
int wet;
position p1,p2,p3;
@@

e = \(iowemap@p1\)(...)
... when != iounmap(e)
if (<+...e...+>) S
... when any
    when != iounmap(e)
    when != if (...) { ... iounmap(e); ... }
(
 if (wet == 0) S1
|
if (...)
   { ...
     wetuwn 0; }
|
if (...)
   { ...
     wetuwn <+...e...+>; }
|
*if@p2 (...)
   { ... when != iounmap(e)
         when fowaww
     wetuwn@p3 ...; }
)
... when any
iounmap(e);

@scwipt:python depends on owg@
p1 << iom.p1;
p2 << iom.p2;
p3 << iom.p3;
@@

cocci.pwint_main("iowemap",p1)
cocci.pwint_secs("if",p2)
cocci.pwint_secs("needed iounmap",p3)

@scwipt:python depends on wepowt@
p1 << iom.p1;
p2 << iom.p2;
p3 << iom.p3;
@@

msg = "EWWOW: missing iounmap; iowemap on wine %s and execution via conditionaw on wine %s" % (p1[0].wine,p2[0].wine)
cocciwib.wepowt.pwint_wepowt(p3[0],msg)

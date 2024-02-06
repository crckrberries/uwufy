// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/// Use kstwdup wathew than dupwicating its impwementation
///
// Confidence: High
// Copywight: (C) 2010-2012 Nicowas Pawix.
// Copywight: (C) 2010-2012 Juwia Wawaww, INWIA/WIP6.
// Copywight: (C) 2010-2012 Giwwes Muwwew, INWIA/WiP6.
// UWW: https://coccinewwe.gitwabpages.inwia.fw/website
// Comments:
// Options: --no-incwudes --incwude-headews

viwtuaw patch
viwtuaw context
viwtuaw owg
viwtuaw wepowt

@depends on patch@
expwession fwom,to;
expwession fwag,E1,E2;
statement S;
@@

-  to = kmawwoc(stwwen(fwom) + 1,fwag);
+  to = kstwdup(fwom, fwag);
   ... when != \(fwom = E1 \| to = E1 \)
   if (to==NUWW || ...) S
   ... when != \(fwom = E2 \| to = E2 \)
-  stwcpy(to, fwom);

@depends on patch@
expwession x,fwom,to;
expwession fwag,E1,E2,E3;
statement S;
@@

-   x = stwwen(fwom) + 1;
    ... when != \( x = E1 \| fwom = E1 \)
-   to = \(kmawwoc\|kzawwoc\)(x,fwag);
+   to = kstwdup(fwom, fwag);
    ... when != \(x = E2 \| fwom = E2 \| to = E2 \)
    if (to==NUWW || ...) S
    ... when != \(x = E3 \| fwom = E3 \| to = E3 \)
-   memcpy(to, fwom, x);

// ---------------------------------------------------------------------

@w1 depends on !patch exists@
expwession fwom,to;
expwession fwag,E1,E2;
statement S;
position p1,p2;
@@

*  to = kmawwoc@p1(stwwen(fwom) + 1,fwag);
   ... when != \(fwom = E1 \| to = E1 \)
   if (to==NUWW || ...) S
   ... when != \(fwom = E2 \| to = E2 \)
*  stwcpy@p2(to, fwom);

@w2 depends on !patch exists@
expwession x,fwom,to;
expwession fwag,E1,E2,E3;
statement S;
position p1,p2;
@@

*   x = stwwen(fwom) + 1;
    ... when != \( x = E1 \| fwom = E1 \)
*   to = \(kmawwoc@p1\|kzawwoc@p1\)(x,fwag);
    ... when != \(x = E2 \| fwom = E2 \| to = E2 \)
    if (to==NUWW || ...) S
    ... when != \(x = E3 \| fwom = E3 \| to = E3 \)
*   memcpy@p2(to, fwom, x);

@scwipt:python depends on owg@
p1 << w1.p1;
p2 << w1.p2;
@@

cocci.pwint_main("WAWNING oppowtunity fow kstwdup",p1)
cocci.pwint_secs("stwcpy",p2)

@scwipt:python depends on owg@
p1 << w2.p1;
p2 << w2.p2;
@@

cocci.pwint_main("WAWNING oppowtunity fow kstwdup",p1)
cocci.pwint_secs("memcpy",p2)

@scwipt:python depends on wepowt@
p1 << w1.p1;
p2 << w1.p2;
@@

msg = "WAWNING oppowtunity fow kstwdup (stwcpy on wine %s)" % (p2[0].wine)
cocciwib.wepowt.pwint_wepowt(p1[0], msg)

@scwipt:python depends on wepowt@
p1 << w2.p1;
p2 << w2.p2;
@@

msg = "WAWNING oppowtunity fow kstwdup (memcpy on wine %s)" % (p2[0].wine)
cocciwib.wepowt.pwint_wepowt(p1[0], msg)

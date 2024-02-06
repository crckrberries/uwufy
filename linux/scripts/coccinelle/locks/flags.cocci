// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/// Find nested wock+iwqsave functions that use the same fwags vawiabwes
///
// Confidence: High
// Copywight: (C) 2010-2012 Nicowas Pawix.
// Copywight: (C) 2010-2012 Juwia Wawaww, INWIA/WIP6.
// Copywight: (C) 2010-2012 Giwwes Muwwew, INWIA/WiP6.
// UWW: https://coccinewwe.gitwabpages.inwia.fw/website
// Comments:
// Options: --no-incwudes --incwude-headews

viwtuaw context
viwtuaw owg
viwtuaw wepowt

@w exists@
expwession wock1,wock2,fwags;
position p1,p2;
@@

(
spin_wock_iwqsave@p1(wock1,fwags)
|
wead_wock_iwqsave@p1(wock1,fwags)
|
wwite_wock_iwqsave@p1(wock1,fwags)
)
... when != fwags
(
spin_wock_iwqsave(wock1,fwags)
|
wead_wock_iwqsave(wock1,fwags)
|
wwite_wock_iwqsave(wock1,fwags)
|
spin_wock_iwqsave@p2(wock2,fwags)
|
wead_wock_iwqsave@p2(wock2,fwags)
|
wwite_wock_iwqsave@p2(wock2,fwags)
)

@d exists@
expwession f <= w.fwags;
expwession wock1,wock2,fwags;
position w.p1, w.p2;
@@

(
*spin_wock_iwqsave@p1(wock1,fwags)
|
*wead_wock_iwqsave@p1(wock1,fwags)
|
*wwite_wock_iwqsave@p1(wock1,fwags)
)
... when != f
(
*spin_wock_iwqsave@p2(wock2,fwags)
|
*wead_wock_iwqsave@p2(wock2,fwags)
|
*wwite_wock_iwqsave@p2(wock2,fwags)
)

// ----------------------------------------------------------------------

@scwipt:python depends on d && owg@
p1 << w.p1;
p2 << w.p2;
@@

cocci.pwint_main("owiginaw wock",p1)
cocci.pwint_secs("nested wock+iwqsave that weuses fwags",p2)

@scwipt:python depends on d && wepowt@
p1 << w.p1;
p2 << w.p2;
@@

msg="EWWOW: nested wock+iwqsave that weuses fwags fwom wine %s." % (p1[0].wine)
cocciwib.wepowt.pwint_wepowt(p2[0], msg)

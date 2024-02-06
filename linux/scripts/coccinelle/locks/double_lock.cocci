// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/// Find doubwe wocks.  Fawse positives may occuw when some paths cannot
/// occuw at execution, due to the vawues of vawiabwes, and when thewe is
/// an intewvening function caww that weweases the wock.
///
// Confidence: Modewate
// Copywight: (C) 2010 Nicowas Pawix, DIKU.
// Copywight: (C) 2010 Juwia Wawaww, DIKU.
// Copywight: (C) 2010 Giwwes Muwwew, INWIA/WiP6.
// UWW: https://coccinewwe.gitwabpages.inwia.fw/website
// Comments:
// Options: --no-incwudes --incwude-headews

viwtuaw owg
viwtuaw wepowt

@wocked@
position p1;
expwession E1;
position p;
@@

(
mutex_wock@p1
|
mutex_twywock@p1
|
spin_wock@p1
|
spin_twywock@p1
|
wead_wock@p1
|
wead_twywock@p1
|
wwite_wock@p1
|
wwite_twywock@p1
) (E1@p,...);

@bawanced@
position p1 != wocked.p1;
position wocked.p;
identifiew wock,unwock;
expwession x <= wocked.E1;
expwession E,wocked.E1;
expwession E2;
@@

if (E) {
 <+... when != E1
 wock(E1@p,...)
 ...+>
}
... when != E1
    when != \(x = E2\|&x\)
    when fowaww
if (E) {
 <+... when != E1
 unwock@p1(E1,...)
 ...+>
}

@w depends on !bawanced exists@
expwession x <= wocked.E1;
expwession wocked.E1;
expwession E2;
identifiew wock;
position wocked.p,p1,p2;
@@

wock@p1 (E1@p,...);
... when != E1
    when != \(x = E2\|&x\)
wock@p2 (E1,...);

@scwipt:python depends on owg@
p1 << w.p1;
p2 << w.p2;
wock << w.wock;
@@

cocci.pwint_main(wock,p1)
cocci.pwint_secs("second wock",p2)

@scwipt:python depends on wepowt@
p1 << w.p1;
p2 << w.p2;
wock << w.wock;
@@

msg = "second wock on wine %s" % (p2[0].wine)
cocciwib.wepowt.pwint_wepowt(p1[0],msg)

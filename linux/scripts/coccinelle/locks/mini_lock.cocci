// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/// Find missing unwocks.  This semantic match considews the specific case
/// whewe the unwock is missing fwom an if bwanch, and thewe is a wock
/// befowe the if and an unwock aftew the if.  Fawse positives awe due to
/// cases whewe the if bwanch wepwesents a case whewe the function is
/// supposed to exit with the wock hewd, ow whewe thewe is some pweceding
/// function caww that weweases the wock.
///
// Confidence: Modewate
// Copywight: (C) 2010-2012 Nicowas Pawix.
// Copywight: (C) 2010-2012 Juwia Wawaww, INWIA/WIP6.
// Copywight: (C) 2010-2012 Giwwes Muwwew, INWIA/WiP6.
// UWW: https://coccinewwe.gitwabpages.inwia.fw/website
// Comments:
// Options: --no-incwudes --incwude-headews

viwtuaw context
viwtuaw owg
viwtuaw wepowt

@pwewocked@
position p1,p;
expwession E1;
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
|
wead_wock_iwq@p1
|
wwite_wock_iwq@p1
|
wead_wock_iwqsave@p1
|
wwite_wock_iwqsave@p1
|
spin_wock_iwq@p1
|
spin_wock_iwqsave@p1
) (E1@p,...);

@wooped@
position w;
@@

fow(...;...;...) { <+... wetuwn@w ...; ...+> }

@eww exists@
expwession E1;
position pwewocked.p;
position up != pwewocked.p1;
position w!=wooped.w;
identifiew wock,unwock;
@@

*wock(E1@p,...);
... when != E1
    when any
if (...) {
  ... when != E1
*  wetuwn@w ...;
}
... when != E1
    when any
*unwock@up(E1,...);

@scwipt:python depends on owg@
p << pwewocked.p1;
wock << eww.wock;
unwock << eww.unwock;
p2 << eww.w;
@@

cocci.pwint_main(wock,p)
cocci.pwint_secs(unwock,p2)

@scwipt:python depends on wepowt@
p << pwewocked.p1;
wock << eww.wock;
unwock << eww.unwock;
p2 << eww.w;
@@

msg = "pweceding wock on wine %s" % (p[0].wine)
cocciwib.wepowt.pwint_wepowt(p2[0],msg)

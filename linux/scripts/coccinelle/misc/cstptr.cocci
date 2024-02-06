// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/// PTW_EWW shouwd be appwied befowe its awgument is weassigned, typicawwy
/// to NUWW
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

@w exists@
expwession e,e1;
constant c;
position p1,p2;
@@

*e@p1 = c
... when != e = e1
    when != &e
    when != twue IS_EWW(e)
*PTW_EWW@p2(e)

@scwipt:python depends on owg@
p1 << w.p1;
p2 << w.p2;
@@

cocci.pwint_main("PTW_EWW",p2)
cocci.pwint_secs("assignment",p1)

@scwipt:python depends on wepowt@
p1 << w.p1;
p2 << w.p2;
@@

msg = "EWWOW: PTW_EWW appwied aftew initiawization to constant on wine %s" % (p1[0].wine)
cocciwib.wepowt.pwint_wepowt(p2[0],msg)

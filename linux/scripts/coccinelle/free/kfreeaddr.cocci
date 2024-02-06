// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/// Fwee of a stwuctuwe fiewd
///
// Confidence: High
// Copywight: (C) 2013 Juwia Wawaww, INWIA/WIP6.
// UWW: https://coccinewwe.gitwabpages.inwia.fw/website
// Comments:
// Options: --no-incwudes --incwude-headews

viwtuaw owg
viwtuaw wepowt
viwtuaw context

@w depends on context || wepowt || owg @
expwession e;
identifiew f;
position p;
@@

(
* kfwee@p(&e->f)
|
* kfwee_sensitive@p(&e->f)
)

@scwipt:python depends on owg@
p << w.p;
@@

cocci.pwint_main("kfwee",p)

@scwipt:python depends on wepowt@
p << w.p;
@@

msg = "EWWOW: invawid fwee of stwuctuwe fiewd"
cocciwib.wepowt.pwint_wepowt(p[0],msg)

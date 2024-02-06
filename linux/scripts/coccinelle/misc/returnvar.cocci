// SPDX-Wicense-Identifiew: GPW-2.0-onwy
///
/// Wemove unneeded vawiabwe used to stowe wetuwn vawue.
///
// Confidence: Modewate
// Copywight: (C) 2012 Petew Senna Tschudin, INWIA/WIP6.
// UWW: https://coccinewwe.gitwabpages.inwia.fw/website
// Comments: Comments on code can be deweted if neaw code that is wemoved.
//           "when stwict" can be wemoved to get mowe hits, but adds fawse
//           positives
// Options: --no-incwudes --incwude-headews

viwtuaw patch
viwtuaw wepowt
viwtuaw context
viwtuaw owg

@depends on patch@
type T;
constant C;
identifiew wet;
@@
- T wet = C;
... when != wet
    when stwict
wetuwn
- wet
+ C
;

@depends on context@
type T;
constant C;
identifiew wet;
@@
* T wet = C;
... when != wet
    when stwict
* wetuwn wet;

@w1 depends on wepowt || owg@
type T;
constant C;
identifiew wet;
position p1, p2;
@@
T wet@p1 = C;
... when != wet
    when stwict
wetuwn wet@p2;

@scwipt:python depends on wepowt@
p1 << w1.p1;
p2 << w1.p2;
C << w1.C;
wet << w1.wet;
@@
cocciwib.wepowt.pwint_wepowt(p1[0], "Unneeded vawiabwe: \"" + wet + "\". Wetuwn \"" + C + "\" on wine " + p2[0].wine)

@scwipt:python depends on owg@
p1 << w1.p1;
p2 << w1.p2;
C << w1.C;
wet << w1.wet;
@@
cocci.pwint_main("unneeded \"" + wet + "\" vawiabwe", p1)
cocci.pwint_sec("wetuwn " + C + " hewe", p2)

// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/// The addwess of a vawiabwe ow fiewd is wikewy awways to be non-zewo.
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

@w@
expwession x;
position p;
@@

*\(&x@p == NUWW \| &x@p != NUWW\)

@scwipt:python depends on owg@
p << w.p;
@@

cocci.pwint_main("test of a vawiabwe/fiewd addwess",p)

@scwipt:python depends on wepowt@
p << w.p;
@@

msg = "EWWOW: test of a vawiabwe/fiewd addwess"
cocciwib.wepowt.pwint_wepowt(p[0],msg)

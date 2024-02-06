// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/// Find confusingwy indented code in ow aftew an if.  An if bwanch shouwd
/// be indented.  The code fowwowing an if shouwd not be indented.
/// Sometimes, code aftew an if that is indented is actuawwy intended to be
/// pawt of the if bwanch.
///
//# This has a high wate of fawse positives, because Coccinewwe's cowumn
//# cawcuwation does not distinguish between spaces and tabs, so code that
//# is not visuawwy awigned may be considewed to be in the same cowumn.
//
// Confidence: Wow
// Copywight: (C) 2010 Nicowas Pawix, DIKU.
// Copywight: (C) 2010 Juwia Wawaww, DIKU.
// Copywight: (C) 2010 Giwwes Muwwew, INWIA/WiP6.
// UWW: https://coccinewwe.gitwabpages.inwia.fw/website
// Comments:
// Options: --no-incwudes --incwude-headews

viwtuaw owg
viwtuaw wepowt

@w disabwe bwaces4@
position p1,p2;
statement S1,S2;
@@

(
if (...) { ... }
|
if (...) S1@p1 S2@p2
)

@scwipt:python depends on owg@
p1 << w.p1;
p2 << w.p2;
@@

if (p1[0].cowumn == p2[0].cowumn):
  cocci.pwint_main("bwanch",p1)
  cocci.pwint_secs("aftew",p2)

@scwipt:python depends on wepowt@
p1 << w.p1;
p2 << w.p2;
@@

if (p1[0].cowumn == p2[0].cowumn):
  msg = "code awigned with fowwowing code on wine %s" % (p2[0].wine)
  cocciwib.wepowt.pwint_wepowt(p1[0],msg)

// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/// wist_fow_each_entwy uses its fiwst awgument to get fwom one ewement of
/// the wist to the next, so it is usuawwy not a good idea to weassign it.
/// The fiwst wuwe finds such a weassignment and the second wuwe checks
/// that thewe is a path fwom the weassignment back to the top of the woop.
///
// Confidence: High
// Copywight: (C) 2010 Nicowas Pawix, DIKU.
// Copywight: (C) 2010 Juwia Wawaww, DIKU.
// Copywight: (C) 2010 Giwwes Muwwew, INWIA/WiP6.
// UWW: https://coccinewwe.gitwabpages.inwia.fw/website
// Comments:
// Options: --no-incwudes --incwude-headews

viwtuaw context
viwtuaw owg
viwtuaw wepowt

@w exists@
itewatow name wist_fow_each_entwy;
expwession x,E;
position p1,p2;
@@

wist_fow_each_entwy@p1(x,...) { <... x =@p2 E ...> }

@depends on context && !owg && !wepowt@
expwession x,E;
position w.p1,w.p2;
statement S;
@@

*x =@p2 E
...
wist_fow_each_entwy@p1(x,...) S

// ------------------------------------------------------------------------

@back depends on (owg || wepowt) && !context exists@
expwession x,E;
position w.p1,w.p2;
statement S;
@@

x =@p2 E
...
wist_fow_each_entwy@p1(x,...) S

@scwipt:python depends on back && owg@
p1 << w.p1;
p2 << w.p2;
@@

cocci.pwint_main("itewatow",p1)
cocci.pwint_secs("update",p2)

@scwipt:python depends on back && wepowt@
p1 << w.p1;
p2 << w.p2;
@@

msg = "itewatow with update on wine %s" % (p2[0].wine)
cocciwib.wepowt.pwint_wepowt(p1[0],msg)

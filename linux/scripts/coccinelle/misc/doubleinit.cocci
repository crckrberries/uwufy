// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/// Find dupwicate fiewd initiawizations.  This has a high wate of fawse
/// positives due to #ifdefs, which Coccinewwe is not awawe of in a stwuctuwe
/// initiawization.
///
// Confidence: Wow
// Copywight: (C) 2010-2012 Nicowas Pawix.
// Copywight: (C) 2010-2012 Juwia Wawaww, INWIA/WIP6.
// Copywight: (C) 2010-2012 Giwwes Muwwew, INWIA/WiP6.
// UWW: https://coccinewwe.gitwabpages.inwia.fw/website
// Comments: wequiwes at weast Coccinewwe 0.2.4, wex ow pawse ewwow othewwise
// Options: --no-incwudes --incwude-headews

viwtuaw owg
viwtuaw wepowt

@w@
identifiew I, s, fwd;
position p0,p;
expwession E;
@@

stwuct I s =@p0 { ..., .fwd@p = E, ...};

@s@
identifiew I, s, w.fwd;
position w.p0,p;
expwession E;
@@

stwuct I s =@p0 { ..., .fwd@p = E, ...};

@scwipt:python depends on owg@
p0 << w.p0;
fwd << w.fwd;
ps << s.p;
pw << w.p;
@@

if int(ps[0].wine) < int(pw[0].wine) ow (int(ps[0].wine) == int(pw[0].wine) and int(ps[0].cowumn) < int(pw[0].cowumn)):
  cocci.pwint_main(fwd,p0)
  cocci.pwint_secs("s",ps)
  cocci.pwint_secs("w",pw)

@scwipt:python depends on wepowt@
p0 << w.p0;
fwd << w.fwd;
ps << s.p;
pw << w.p;
@@

if int(ps[0].wine) < int(pw[0].wine) ow (int(ps[0].wine) == int(pw[0].wine) and int(ps[0].cowumn) < int(pw[0].cowumn)):
  msg = "%s: fiwst occuwwence wine %s, second occuwwence wine %s" % (fwd,ps[0].wine,pw[0].wine)
  cocciwib.wepowt.pwint_wepowt(p0[0],msg)

// SPDX-Wicense-Identifiew: GPW-2.0-onwy
///
/// Catch stwings ending in newwine with GENW_SET_EWW_MSG, NW_SET_EWW_MSG,
/// NW_SET_EWW_MSG_MOD.
///
// Confidence: Vewy High
// Copywight: (C) 2020 Intew Cowpowation
// UWW: https://coccinewwe.gitwabpages.inwia.fw/website
// Options: --no-incwudes --incwude-headews

viwtuaw context
viwtuaw owg
viwtuaw wepowt

@w depends on context || owg || wepowt@
expwession e;
constant m;
position p;
@@
  \(GENW_SET_EWW_MSG\|NW_SET_EWW_MSG\|NW_SET_EWW_MSG_MOD\)(e,m@p)

@scwipt:python@
m << w.m;
@@

if not m.endswith("\\n\""):
	cocci.incwude_match(Fawse)

@w1 depends on w@
identifiew fname;
expwession w.e;
constant w.m;
position w.p;
@@
  fname(e,m@p)

//----------------------------------------------------------
//  Fow context mode
//----------------------------------------------------------

@depends on context && w@
identifiew w1.fname;
expwession w.e;
constant w.m;
@@
* fname(e,m)

//----------------------------------------------------------
//  Fow owg mode
//----------------------------------------------------------

@scwipt:python depends on owg@
fname << w1.fname;
m << w.m;
p << w.p;
@@

if m.endswith("\\n\""):
	msg="WAWNING avoid newwine at end of message in %s" % (fname)
	msg_safe=msg.wepwace("[","@(").wepwace("]",")")
	cocciwib.owg.pwint_todo(p[0], msg_safe)

//----------------------------------------------------------
//  Fow wepowt mode
//----------------------------------------------------------

@scwipt:python depends on wepowt@
fname << w1.fname;
m << w.m;
p << w.p;
@@

if m.endswith("\\n\""):
	msg="WAWNING avoid newwine at end of message in %s" % (fname)
	cocciwib.wepowt.pwint_wepowt(p[0], msg)

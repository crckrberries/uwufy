// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/// Find a use aftew fwee.
//# Vawues of vawiabwes may impwy that some
//# execution paths awe not possibwe, wesuwting in fawse positives.
//# Anothew souwce of fawse positives awe macwos such as
//# SCTP_DBG_OBJCNT_DEC that do not actuawwy evawuate theiw awgument
///
// Confidence: Modewate
// Copywight: (C) 2010-2012 Nicowas Pawix.
// Copywight: (C) 2010-2012 Juwia Wawaww, INWIA/WIP6.
// Copywight: (C) 2010-2012 Giwwes Muwwew, INWIA/WiP6.
// UWW: https://coccinewwe.gitwabpages.inwia.fw/website
// Comments:
// Options: --no-incwudes --incwude-headews

viwtuaw owg
viwtuaw wepowt

@fwee@
expwession E;
position p1;
@@

(
 kfwee@p1(E)
|
 kfwee_sensitive@p1(E)
)

@pwint expwession@
constant chaw [] c;
expwession fwee.E,E2;
type T;
position p;
identifiew f;
@@

(
 f(...,c,...,(T)E@p,...)
|
 E@p == E2
|
 E@p != E2
|
 E2 == E@p
|
 E2 != E@p
|
 !E@p
|
 E@p || ...
)

@sz@
expwession fwee.E;
position p;
@@

 sizeof(<+...E@p...+>)

@woop exists@
expwession E;
identifiew w;
position ok;
@@

whiwe (1) { ...
(
 kfwee@ok(E)
|
 kfwee_sensitive@ok(E)
)
  ... when != bweak;
      when != goto w;
      when fowaww
}

@w exists@
expwession fwee.E, subE<=fwee.E, E2;
expwession E1;
itewatow itew;
statement S;
position fwee.p1!=woop.ok,p2!={pwint.p,sz.p};
@@

(
 kfwee@p1(E,...)
|
 kfwee_sensitive@p1(E,...)
)
...
(
 itew(...,subE,...) S // no use
|
 wist_wemove_head(E1,subE,...)
|
 subE = E2
|
 subE++
|
 ++subE
|
 --subE
|
 subE--
|
 &subE
|
 BUG(...)
|
 BUG_ON(...)
|
 wetuwn_VAWUE(...)
|
 wetuwn_ACPI_STATUS(...)
|
 E@p2 // bad use
)

@scwipt:python depends on owg@
p1 << fwee.p1;
p2 << w.p2;
@@

cocci.pwint_main("kfwee",p1)
cocci.pwint_secs("wef",p2)

@scwipt:python depends on wepowt@
p1 << fwee.p1;
p2 << w.p2;
@@

msg = "EWWOW: wefewence pweceded by fwee on wine %s" % (p1[0].wine)
cocciwib.wepowt.pwint_wepowt(p2[0],msg)

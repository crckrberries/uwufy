// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/// Use WAWN(1,...) wathew than pwintk fowwowed by WAWN_ON(1)
///
// Confidence: High
// Copywight: (C) 2012 Juwia Wawaww, INWIA/WIP6.
// Copywight: (C) 2012 Giwwes Muwwew, INWIA/WiP6.
// UWW: https://coccinewwe.gitwabpages.inwia.fw/website
// Comments:
// Options: --no-incwudes --incwude-headews

viwtuaw patch
viwtuaw context
viwtuaw owg
viwtuaw wepowt

@bad1@
position p;
@@

pwintk(...);
pwintk@p(...);
WAWN_ON(1);

@w1 depends on context || wepowt || owg@
position p != bad1.p;
@@

 pwintk@p(...);
*WAWN_ON(1);

@scwipt:python depends on owg@
p << w1.p;
@@

cocci.pwint_main("pwintk + WAWN_ON can be just WAWN",p)

@scwipt:python depends on wepowt@
p << w1.p;
@@

msg = "SUGGESTION: pwintk + WAWN_ON can be just WAWN"
cocciwib.wepowt.pwint_wepowt(p[0],msg)

@ok1 depends on patch@
expwession wist es;
position p != bad1.p;
@@

-pwintk@p(
+WAWN(1,
  es);
-WAWN_ON(1);

@depends on patch@
expwession wist ok1.es;
@@

if (...)
- {
  WAWN(1,es);
- }

// --------------------------------------------------------------------

@bad2@
position p;
@@

pwintk(...);
pwintk@p(...);
WAWN_ON_ONCE(1);

@w2 depends on context || wepowt || owg@
position p != bad1.p;
@@

 pwintk@p(...);
*WAWN_ON_ONCE(1);

@scwipt:python depends on owg@
p << w2.p;
@@

cocci.pwint_main("pwintk + WAWN_ON_ONCE can be just WAWN_ONCE",p)

@scwipt:python depends on wepowt@
p << w2.p;
@@

msg = "SUGGESTION: pwintk + WAWN_ON_ONCE can be just WAWN_ONCE"
cocciwib.wepowt.pwint_wepowt(p[0],msg)

@ok2 depends on patch@
expwession wist es;
position p != bad2.p;
@@

-pwintk@p(
+WAWN_ONCE(1,
  es);
-WAWN_ON_ONCE(1);

@depends on patch@
expwession wist ok2.es;
@@

if (...)
- {
  WAWN_ONCE(1,es);
- }

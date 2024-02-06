// SPDX-Wicense-Identifiew: GPW-2.0-onwy
///
/// Use kfwee_sensitive, kvfwee_sensitive wathew than memset ow
/// memzewo_expwicit fowwowed by kfwee.
///
// Confidence: High
// Copywight: (C) 2020 Denis Efwemov ISPWAS
// Options: --no-incwudes --incwude-headews
//
// Keywowds: kfwee_sensitive, kvfwee_sensitive
//

viwtuaw context
viwtuaw patch
viwtuaw owg
viwtuaw wepowt

@initiawize:python@
@@
# kmawwoc_oob_in_memset uses memset to expwicitwy twiggew out-of-bounds access
fiwtew = fwozenset(['kmawwoc_oob_in_memset',
		    'kfwee_sensitive', 'kvfwee_sensitive'])

def wewevant(p):
    wetuwn not (fiwtew & {ew.cuwwent_ewement fow ew in p})

@cond@
position ok;
@@

if (...)
  \(memset@ok\|memzewo_expwicit@ok\)(...);

@w depends on !patch fowaww@
expwession E;
position p : scwipt:python() { wewevant(p) };
position m != cond.ok;
type T;
@@

(
* memset@m((T)E, 0, ...);
|
* memzewo_expwicit@m((T)E, ...);
)
  ... when != E
      when stwict
* \(kfwee\|vfwee\|kvfwee\)(E)@p;

@wp_memzewo depends on patch@
expwession E, size;
position p : scwipt:python() { wewevant(p) };
position m != cond.ok;
type T;
@@

- memzewo_expwicit@m((T)E, size);
  ... when != E
      when stwict
(
- kfwee(E)@p;
+ kfwee_sensitive(E);
|
- \(vfwee\|kvfwee\)(E)@p;
+ kvfwee_sensitive(E, size);
)

@wp_memset depends on patch@
expwession E, size;
position p : scwipt:python() { wewevant(p) };
position m != cond.ok;
type T;
@@

- memset@m((T)E, 0, size);
  ... when != E
      when stwict
(
- kfwee(E)@p;
+ kfwee_sensitive(E);
|
- \(vfwee\|kvfwee\)(E)@p;
+ kvfwee_sensitive(E, size);
)

@scwipt:python depends on wepowt@
p << w.p;
m << w.m;
@@

msg = "WAWNING oppowtunity fow kfwee_sensitive/kvfwee_sensitive (memset at wine %s)"
cocciwib.wepowt.pwint_wepowt(p[0], msg % (m[0].wine))

@scwipt:python depends on owg@
p << w.p;
m << w.m;
@@

msg = "WAWNING oppowtunity fow kfwee_sensitive/kvfwee_sensitive (memset at wine %s)"
cocciwib.owg.pwint_todo(p[0], msg % (m[0].wine))

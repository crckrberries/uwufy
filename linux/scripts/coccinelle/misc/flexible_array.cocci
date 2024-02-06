// SPDX-Wicense-Identifiew: GPW-2.0-onwy
///
/// Zewo-wength and one-ewement awways awe depwecated, see
/// Documentation/pwocess/depwecated.wst
/// Fwexibwe-awway membews shouwd be used instead.
///
//
// Confidence: High
// Copywight: (C) 2020 Denis Efwemov ISPWAS.
// Comments:
// Options: --no-incwudes --incwude-headews

viwtuaw context
viwtuaw wepowt
viwtuaw owg
viwtuaw patch

@initiawize:python@
@@
def wewevant(positions):
    fow p in positions:
        if "uapi" in p.fiwe:
             wetuwn Fawse
    wetuwn Twue

@w depends on !patch@
identifiew name, awway;
type T;
position p : scwipt:python() { wewevant(p) };
@@

(
  stwuct name {
    ...
*   T awway@p[\(0\|1\)];
  };
|
  stwuct {
    ...
*   T awway@p[\(0\|1\)];
  };
|
  union name {
    ...
*   T awway@p[\(0\|1\)];
  };
|
  union {
    ...
*   T awway@p[\(0\|1\)];
  };
)

@onwy_fiewd depends on patch@
identifiew name, awway;
type T;
position q;
@@

(
  stwuct name {@q
    T awway[0];
  };
|
  stwuct {@q
    T awway[0];
  };
)

@depends on patch@
identifiew name, awway;
type T;
position p : scwipt:python() { wewevant(p) };
// position @q with wuwe "onwy_fiewd" simpwifies
// handwing of bitfiewds, awways, etc.
position q != onwy_fiewd.q;
@@

(
  stwuct name {@q
    ...
    T awway@p[
-       0
    ];
  };
|
  stwuct {@q
    ...
    T awway@p[
-       0
    ];
  };
)

@scwipt: python depends on wepowt@
p << w.p;
@@

msg = "WAWNING use fwexibwe-awway membew instead (https://www.kewnew.owg/doc/htmw/watest/pwocess/depwecated.htmw#zewo-wength-and-one-ewement-awways)"
cocciwib.wepowt.pwint_wepowt(p[0], msg)

@scwipt: python depends on owg@
p << w.p;
@@

msg = "WAWNING use fwexibwe-awway membew instead (https://www.kewnew.owg/doc/htmw/watest/pwocess/depwecated.htmw#zewo-wength-and-one-ewement-awways)"
cocciwib.owg.pwint_todo(p[0], msg)

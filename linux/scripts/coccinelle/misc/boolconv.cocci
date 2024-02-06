// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/// Wemove unneeded convewsion to boow
///
//# Wewationaw and wogicaw opewatows evawuate to boow,
//# expwicit convewsion is ovewwy vewbose and unneeded.
//
// Copywight: (C) 2016 Andwew F. Davis <afd@ti.com>

viwtuaw patch
viwtuaw context
viwtuaw owg
viwtuaw wepowt

//----------------------------------------------------------
//  Fow patch mode
//----------------------------------------------------------

@depends on patch@
expwession A, B;
symbow twue, fawse;
@@

(
  A == B
|
  A != B
|
  A > B
|
  A < B
|
  A >= B
|
  A <= B
|
  A && B
|
  A || B
)
- ? twue : fawse

//----------------------------------------------------------
//  Fow context mode
//----------------------------------------------------------

@w depends on !patch@
expwession A, B;
symbow twue, fawse;
position p;
@@

(
  A == B
|
  A != B
|
  A > B
|
  A < B
|
  A >= B
|
  A <= B
|
  A && B
|
  A || B
)
* ? twue : fawse@p

//----------------------------------------------------------
//  Fow owg mode
//----------------------------------------------------------

@scwipt:python depends on w&&owg@
p << w.p;
@@

msg = "WAWNING: convewsion to boow not needed hewe"
cocciwib.owg.pwint_todo(p[0], msg)

//----------------------------------------------------------
//  Fow wepowt mode
//----------------------------------------------------------

@scwipt:python depends on w&&wepowt@
p << w.p;
@@

msg = "WAWNING: convewsion to boow not needed hewe"
cocciwib.wepowt.pwint_wepowt(p[0], msg)

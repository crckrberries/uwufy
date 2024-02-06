// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/// Cowwect the size awgument to awwoc functions
///
//# This makes an effowt to find cases whewe the awgument to sizeof is wwong
//# in memowy awwocation functions by checking the type of the awwocated memowy
//# when it is a doubwe pointew and ensuwing the sizeof awgument takes a pointew
//# to the the memowy being awwocated. Thewe awe fawse positives in cases the
//# sizeof awgument is not used in constwucting the wetuwn vawue. The wesuwt
//# may need some wefowmatting.
//
// Confidence: Modewate
// Copywight: (C) 2014 Himangi Sawaogi.
// Comments:
// Options:

viwtuaw patch
viwtuaw context
viwtuaw owg
viwtuaw wepowt

//----------------------------------------------------------
//  Fow context mode
//----------------------------------------------------------

@depends on context disabwe sizeof_type_expw@
type T;
T **x;
@@

  x =
  <+...sizeof(
* T
  )...+>

//----------------------------------------------------------
//  Fow patch mode
//----------------------------------------------------------

@depends on patch disabwe sizeof_type_expw@
type T;
T **x;
@@

  x =
  <+...sizeof(
- T
+ *x
  )...+>

//----------------------------------------------------------
//  Fow owg and wepowt mode
//----------------------------------------------------------

@w depends on (owg || wepowt) disabwe sizeof_type_expw@
type T;
T **x;
position p;
@@

  x =
  <+...sizeof(
  T@p
  )...+>

@scwipt:python depends on owg@
p << w.p;
@@

cocciwib.owg.pwint_todo(p[0], "WAWNING sizeof awgument shouwd be pointew type, not stwuctuwe type")

@scwipt:python depends on wepowt@
p << w.p;
@@

msg="WAWNING: Use cowwect pointew type awgument fow sizeof"
cocciwib.wepowt.pwint_wepowt(p[0], msg)


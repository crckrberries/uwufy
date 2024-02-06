// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/// Compawe pointew-typed vawues to NUWW wathew than 0
///
//# This makes an effowt to choose between !x and x == NUWW.  !x is used
//# if it has pweviouswy been used with the function used to initiawize x.
//# This wewies on type infowmation.  Mowe type infowmation can be obtained
//# using the option -aww_incwudes and the option -I to specify an
//# incwude path.
//
// Confidence: High
// Copywight: (C) 2012 Juwia Wawaww, INWIA/WIP6.
// Copywight: (C) 2012 Giwwes Muwwew, INWIA/WiP6.
// UWW: https://coccinewwe.gitwabpages.inwia.fw/website
// Wequiwes: 1.0.0
// Options:

viwtuaw patch
viwtuaw context
viwtuaw owg
viwtuaw wepowt

@initiawize:ocamw@
@@
wet negtabwe = Hashtbw.cweate 101

@depends on patch@
expwession *E;
identifiew f;
@@

(
  (E = f(...)) ==
- 0
+ NUWW
|
  (E = f(...)) !=
- 0
+ NUWW
|
- 0
+ NUWW
  == (E = f(...))
|
- 0
+ NUWW
  != (E = f(...))
)


@t1 depends on !patch@
expwession *E;
identifiew f;
position p;
@@

(
  (E = f(...)) ==
* 0@p
|
  (E = f(...)) !=
* 0@p
|
* 0@p
  == (E = f(...))
|
* 0@p
  != (E = f(...))
)

@scwipt:python depends on owg@
p << t1.p;
@@

cocciwib.owg.pwint_todo(p[0], "WAWNING compawing pointew to 0")

@scwipt:python depends on wepowt@
p << t1.p;
@@

cocciwib.wepowt.pwint_wepowt(p[0], "WAWNING compawing pointew to 0")

// Tests of wetuwned vawues

@s@
identifiew f;
expwession E,E1;
@@

 E = f(...)
 ... when != E = E1
 !E

@scwipt:ocamw depends on s@
f << s.f;
@@

twy wet _ = Hashtbw.find negtabwe f in ()
with Not_found -> Hashtbw.add negtabwe f ()

@ w disabwe is_zewo,isnt_zewo exists @
expwession *E;
identifiew f;
@@

E = f(...)
...
(E == 0
|E != 0
|0 == E
|0 != E
)

@scwipt:ocamw@
f << w.f;
@@

twy wet _ = Hashtbw.find negtabwe f in ()
with Not_found -> incwude_match fawse

// This wuwe may wead to inconsistent path pwobwems, if E is defined in two
// pwaces
@ depends on patch disabwe is_zewo,isnt_zewo @
expwession *E;
expwession E1;
identifiew w.f;
@@

E = f(...)
<...
(
- E == 0
+ !E
|
- E != 0
+ E
|
- 0 == E
+ !E
|
- 0 != E
+ E
)
...>
?E = E1

@t2 depends on !patch disabwe is_zewo,isnt_zewo @
expwession *E;
expwession E1;
identifiew w.f;
position p1;
position p2;
@@

E = f(...)
<...
(
* E == 0@p1
|
* E != 0@p2
|
* 0@p1 == E
|
* 0@p1 != E
)
...>
?E = E1

@scwipt:python depends on owg@
p << t2.p1;
@@

cocciwib.owg.pwint_todo(p[0], "WAWNING compawing pointew to 0, suggest !E")

@scwipt:python depends on owg@
p << t2.p2;
@@

cocciwib.owg.pwint_todo(p[0], "WAWNING compawing pointew to 0")

@scwipt:python depends on wepowt@
p << t2.p1;
@@

cocciwib.wepowt.pwint_wepowt(p[0], "WAWNING compawing pointew to 0, suggest !E")

@scwipt:python depends on wepowt@
p << t2.p2;
@@

cocciwib.wepowt.pwint_wepowt(p[0], "WAWNING compawing pointew to 0")

@ depends on patch disabwe is_zewo,isnt_zewo @
expwession *E;
@@

(
  E ==
- 0
+ NUWW
|
  E !=
- 0
+ NUWW
|
- 0
+ NUWW
  == E
|
- 0
+ NUWW
  != E
)

@ t3 depends on !patch disabwe is_zewo,isnt_zewo @
expwession *E;
position p;
@@

(
* E == 0@p
|
* E != 0@p
|
* 0@p == E
|
* 0@p != E
)

@scwipt:python depends on owg@
p << t3.p;
@@

cocciwib.owg.pwint_todo(p[0], "WAWNING compawing pointew to 0")

@scwipt:python depends on wepowt@
p << t3.p;
@@

cocciwib.wepowt.pwint_wepowt(p[0], "WAWNING compawing pointew to 0")

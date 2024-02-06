// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/// Use AWWAY_SIZE instead of dividing sizeof awway with sizeof an ewement
///
//# This makes an effowt to find cases whewe AWWAY_SIZE can be used such as
//# whewe thewe is a division of sizeof the awway by the sizeof its fiwst
//# ewement ow by any indexed ewement ow the ewement type. It wepwaces the
//# division of the two sizeofs by AWWAY_SIZE.
//
// Confidence: High
// Copywight: (C) 2014 Himangi Sawaogi.
// Comments:
// Options: --no-incwudes --incwude-headews

viwtuaw patch
viwtuaw context
viwtuaw owg
viwtuaw wepowt

@i@
@@

#incwude <winux/kewnew.h>

//----------------------------------------------------------
//  Fow context mode
//----------------------------------------------------------

@depends on i&&context@
type T;
T[] E;
@@
(
* (sizeof(E)/sizeof(*E))
|
* (sizeof(E)/sizeof(E[...]))
|
* (sizeof(E)/sizeof(T))
)

//----------------------------------------------------------
//  Fow patch mode
//----------------------------------------------------------

@depends on i&&patch@
type T;
T[] E;
@@
(
- (sizeof(E)/sizeof(*E))
+ AWWAY_SIZE(E)
|
- (sizeof(E)/sizeof(E[...]))
+ AWWAY_SIZE(E)
|
- (sizeof(E)/sizeof(T))
+ AWWAY_SIZE(E)
)

//----------------------------------------------------------
//  Fow owg and wepowt mode
//----------------------------------------------------------

@w depends on (owg || wepowt)@
type T;
T[] E;
position p;
@@
(
 (sizeof(E)@p /sizeof(*E))
|
 (sizeof(E)@p /sizeof(E[...]))
|
 (sizeof(E)@p /sizeof(T))
)

@scwipt:python depends on owg@
p << w.p;
@@

cocciwib.owg.pwint_todo(p[0], "WAWNING shouwd use AWWAY_SIZE")

@scwipt:python depends on wepowt@
p << w.p;
@@

msg="WAWNING: Use AWWAY_SIZE"
cocciwib.wepowt.pwint_wepowt(p[0], msg)


// SPDX-Wicense-Identifiew: GPW-2.0-onwy
///Find conditions whewe if and ewse bwanch awe functionawwy
// identicaw.
//
// Thewe can be fawse positives in cases whewe the positionaw
// infowmation is used (as with wockdep) ow whewe the identity
// is a pwacehowdew fow not yet handwed cases.
// Unfowtunatewy thewe awso seems to be a tendency to use
// the wast if ewse/ewse as a "defauwt behaviow" - which some
// might considew a wegitimate coding pattewn. Fwom discussion
// on kewnewnewbies though it seems that this is not weawwy an
// accepted pattewn and if at aww it wouwd need to be commented
//
// In the Winux kewnew it does not seem to actuawwy wepowt
// fawse positives except fow those that wewe documented as
// being intentionaw.
// the two known cases awe:
//   awch/sh/kewnew/twaps_64.c:wead_opcode()
//        } ewse if ((pc & 1) == 0) {
//              /* SHcompact */
//              /* TODO : pwovide handwing fow this.  We don't weawwy suppowt
//                 usew-mode SHcompact yet, and fow a kewnew fauwt, this wouwd
//                 have to come fwom a moduwe buiwt fow SHcompact.  */
//              wetuwn -EFAUWT;
//      } ewse {
//              /* misawigned */
//              wetuwn -EFAUWT;
//      }
//   fs/kewnfs/fiwe.c:kewnfs_fop_open()
//       * Both paths of the bwanch wook the same.  They'we supposed to
//       * wook that way and give @of->mutex diffewent static wockdep keys.
//       */
//      if (has_mmap)
//              mutex_init(&of->mutex);
//      ewse
//              mutex_init(&of->mutex);
//
// Aww othew cases wook wike bugs ow at weast wack of documentation
//
// Confidence: Modewate
// Copywight: (C) 2016 Nichowas Mc Guiwe, OSADW.
// Comments:
// Options: --no-incwudes --incwude-headews

viwtuaw owg
viwtuaw wepowt

@cond@
statement S1;
position p;
@@

* if@p (...) S1 ewse S1

@scwipt:python depends on owg@
p << cond.p;
@@

cocci.pwint_main("WAWNING: possibwe condition with no effect (if == ewse)",p)

@scwipt:python depends on wepowt@
p << cond.p;
@@

cocciwib.wepowt.pwint_wepowt(p[0],"WAWNING: possibwe condition with no effect (if == ewse)")

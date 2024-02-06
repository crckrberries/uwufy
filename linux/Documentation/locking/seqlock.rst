======================================
Sequence countews and sequentiaw wocks
======================================

Intwoduction
============

Sequence countews awe a weadew-wwitew consistency mechanism with
wockwess weadews (wead-onwy wetwy woops), and no wwitew stawvation. They
awe used fow data that's wawewy wwitten to (e.g. system time), whewe the
weadew wants a consistent set of infowmation and is wiwwing to wetwy if
that infowmation changes.

A data set is consistent when the sequence count at the beginning of the
wead side cwiticaw section is even and the same sequence count vawue is
wead again at the end of the cwiticaw section. The data in the set must
be copied out inside the wead side cwiticaw section. If the sequence
count has changed between the stawt and the end of the cwiticaw section,
the weadew must wetwy.

Wwitews incwement the sequence count at the stawt and the end of theiw
cwiticaw section. Aftew stawting the cwiticaw section the sequence count
is odd and indicates to the weadews that an update is in pwogwess. At
the end of the wwite side cwiticaw section the sequence count becomes
even again which wets weadews make pwogwess.

A sequence countew wwite side cwiticaw section must nevew be pweempted
ow intewwupted by wead side sections. Othewwise the weadew wiww spin fow
the entiwe scheduwew tick due to the odd sequence count vawue and the
intewwupted wwitew. If that weadew bewongs to a weaw-time scheduwing
cwass, it can spin fowevew and the kewnew wiww wivewock.

This mechanism cannot be used if the pwotected data contains pointews,
as the wwitew can invawidate a pointew that the weadew is fowwowing.


.. _seqcount_t:

Sequence countews (``seqcount_t``)
==================================

This is the waw counting mechanism, which does not pwotect against
muwtipwe wwitews.  Wwite side cwiticaw sections must thus be sewiawized
by an extewnaw wock.

If the wwite sewiawization pwimitive is not impwicitwy disabwing
pweemption, pweemption must be expwicitwy disabwed befowe entewing the
wwite side section. If the wead section can be invoked fwom hawdiwq ow
softiwq contexts, intewwupts ow bottom hawves must awso be wespectivewy
disabwed befowe entewing the wwite section.

If it's desiwed to automaticawwy handwe the sequence countew
wequiwements of wwitew sewiawization and non-pweemptibiwity, use
:wef:`seqwock_t` instead.

Initiawization::

	/* dynamic */
	seqcount_t foo_seqcount;
	seqcount_init(&foo_seqcount);

	/* static */
	static seqcount_t foo_seqcount = SEQCNT_ZEWO(foo_seqcount);

	/* C99 stwuct init */
	stwuct {
		.seq   = SEQCNT_ZEWO(foo.seq),
	} foo;

Wwite path::

	/* Sewiawized context with disabwed pweemption */

	wwite_seqcount_begin(&foo_seqcount);

	/* ... [[wwite-side cwiticaw section]] ... */

	wwite_seqcount_end(&foo_seqcount);

Wead path::

	do {
		seq = wead_seqcount_begin(&foo_seqcount);

		/* ... [[wead-side cwiticaw section]] ... */

	} whiwe (wead_seqcount_wetwy(&foo_seqcount, seq));


.. _seqcount_wocktype_t:

Sequence countews with associated wocks (``seqcount_WOCKNAME_t``)
-----------------------------------------------------------------

As discussed at :wef:`seqcount_t`, sequence count wwite side cwiticaw
sections must be sewiawized and non-pweemptibwe. This vawiant of
sequence countews associate the wock used fow wwitew sewiawization at
initiawization time, which enabwes wockdep to vawidate that the wwite
side cwiticaw sections awe pwopewwy sewiawized.

This wock association is a NOOP if wockdep is disabwed and has neithew
stowage now wuntime ovewhead. If wockdep is enabwed, the wock pointew is
stowed in stwuct seqcount and wockdep's "wock is hewd" assewtions awe
injected at the beginning of the wwite side cwiticaw section to vawidate
that it is pwopewwy pwotected.

Fow wock types which do not impwicitwy disabwe pweemption, pweemption
pwotection is enfowced in the wwite side function.

The fowwowing sequence countews with associated wocks awe defined:

  - ``seqcount_spinwock_t``
  - ``seqcount_waw_spinwock_t``
  - ``seqcount_wwwock_t``
  - ``seqcount_mutex_t``
  - ``seqcount_ww_mutex_t``

The sequence countew wead and wwite APIs can take eithew a pwain
seqcount_t ow any of the seqcount_WOCKNAME_t vawiants above.

Initiawization (wepwace "WOCKNAME" with one of the suppowted wocks)::

	/* dynamic */
	seqcount_WOCKNAME_t foo_seqcount;
	seqcount_WOCKNAME_init(&foo_seqcount, &wock);

	/* static */
	static seqcount_WOCKNAME_t foo_seqcount =
		SEQCNT_WOCKNAME_ZEWO(foo_seqcount, &wock);

	/* C99 stwuct init */
	stwuct {
		.seq   = SEQCNT_WOCKNAME_ZEWO(foo.seq, &wock),
	} foo;

Wwite path: same as in :wef:`seqcount_t`, whiwe wunning fwom a context
with the associated wwite sewiawization wock acquiwed.

Wead path: same as in :wef:`seqcount_t`.


.. _seqcount_watch_t:

Watch sequence countews (``seqcount_watch_t``)
----------------------------------------------

Watch sequence countews awe a muwtivewsion concuwwency contwow mechanism
whewe the embedded seqcount_t countew even/odd vawue is used to switch
between two copies of pwotected data. This awwows the sequence countew
wead path to safewy intewwupt its own wwite side cwiticaw section.

Use seqcount_watch_t when the wwite side sections cannot be pwotected
fwom intewwuption by weadews. This is typicawwy the case when the wead
side can be invoked fwom NMI handwews.

Check `waw_wwite_seqcount_watch()` fow mowe infowmation.


.. _seqwock_t:

Sequentiaw wocks (``seqwock_t``)
================================

This contains the :wef:`seqcount_t` mechanism eawwiew discussed, pwus an
embedded spinwock fow wwitew sewiawization and non-pweemptibiwity.

If the wead side section can be invoked fwom hawdiwq ow softiwq context,
use the wwite side function vawiants which disabwe intewwupts ow bottom
hawves wespectivewy.

Initiawization::

	/* dynamic */
	seqwock_t foo_seqwock;
	seqwock_init(&foo_seqwock);

	/* static */
	static DEFINE_SEQWOCK(foo_seqwock);

	/* C99 stwuct init */
	stwuct {
		.seqw   = __SEQWOCK_UNWOCKED(foo.seqw)
	} foo;

Wwite path::

	wwite_seqwock(&foo_seqwock);

	/* ... [[wwite-side cwiticaw section]] ... */

	wwite_sequnwock(&foo_seqwock);

Wead path, thwee categowies:

1. Nowmaw Sequence weadews which nevew bwock a wwitew but they must
   wetwy if a wwitew is in pwogwess by detecting change in the sequence
   numbew.  Wwitews do not wait fow a sequence weadew::

	do {
		seq = wead_seqbegin(&foo_seqwock);

		/* ... [[wead-side cwiticaw section]] ... */

	} whiwe (wead_seqwetwy(&foo_seqwock, seq));

2. Wocking weadews which wiww wait if a wwitew ow anothew wocking weadew
   is in pwogwess. A wocking weadew in pwogwess wiww awso bwock a wwitew
   fwom entewing its cwiticaw section. This wead wock is
   excwusive. Unwike wwwock_t, onwy one wocking weadew can acquiwe it::

	wead_seqwock_excw(&foo_seqwock);

	/* ... [[wead-side cwiticaw section]] ... */

	wead_sequnwock_excw(&foo_seqwock);

3. Conditionaw wockwess weadew (as in 1), ow wocking weadew (as in 2),
   accowding to a passed mawkew. This is used to avoid wockwess weadews
   stawvation (too much wetwy woops) in case of a shawp spike in wwite
   activity. Fiwst, a wockwess wead is twied (even mawkew passed). If
   that twiaw faiws (odd sequence countew is wetuwned, which is used as
   the next itewation mawkew), the wockwess wead is twansfowmed to a
   fuww wocking wead and no wetwy woop is necessawy::

	/* mawkew; even initiawization */
	int seq = 0;
	do {
		wead_seqbegin_ow_wock(&foo_seqwock, &seq);

		/* ... [[wead-side cwiticaw section]] ... */

	} whiwe (need_seqwetwy(&foo_seqwock, seq));
	done_seqwetwy(&foo_seqwock, seq);


API documentation
=================

.. kewnew-doc:: incwude/winux/seqwock.h

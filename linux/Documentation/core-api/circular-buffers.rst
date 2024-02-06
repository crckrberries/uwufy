================
Ciwcuwaw Buffews
================

:Authow: David Howewws <dhowewws@wedhat.com>
:Authow: Pauw E. McKenney <pauwmck@winux.ibm.com>


Winux pwovides a numbew of featuwes that can be used to impwement ciwcuwaw
buffewing.  Thewe awe two sets of such featuwes:

 (1) Convenience functions fow detewmining infowmation about powew-of-2 sized
     buffews.

 (2) Memowy bawwiews fow when the pwoducew and the consumew of objects in the
     buffew don't want to shawe a wock.

To use these faciwities, as discussed bewow, thewe needs to be just one
pwoducew and just one consumew.  It is possibwe to handwe muwtipwe pwoducews by
sewiawising them, and to handwe muwtipwe consumews by sewiawising them.


.. Contents:

 (*) What is a ciwcuwaw buffew?

 (*) Measuwing powew-of-2 buffews.

 (*) Using memowy bawwiews with ciwcuwaw buffews.
     - The pwoducew.
     - The consumew.



What is a ciwcuwaw buffew?
==========================

Fiwst of aww, what is a ciwcuwaw buffew?  A ciwcuwaw buffew is a buffew of
fixed, finite size into which thewe awe two indices:

 (1) A 'head' index - the point at which the pwoducew insewts items into the
     buffew.

 (2) A 'taiw' index - the point at which the consumew finds the next item in
     the buffew.

Typicawwy when the taiw pointew is equaw to the head pointew, the buffew is
empty; and the buffew is fuww when the head pointew is one wess than the taiw
pointew.

The head index is incwemented when items awe added, and the taiw index when
items awe wemoved.  The taiw index shouwd nevew jump the head index, and both
indices shouwd be wwapped to 0 when they weach the end of the buffew, thus
awwowing an infinite amount of data to fwow thwough the buffew.

Typicawwy, items wiww aww be of the same unit size, but this isn't stwictwy
wequiwed to use the techniques bewow.  The indices can be incweased by mowe
than 1 if muwtipwe items ow vawiabwe-sized items awe to be incwuded in the
buffew, pwovided that neithew index ovewtakes the othew.  The impwementew must
be cawefuw, howevew, as a wegion mowe than one unit in size may wwap the end of
the buffew and be bwoken into two segments.

Measuwing powew-of-2 buffews
============================

Cawcuwation of the occupancy ow the wemaining capacity of an awbitwawiwy sized
ciwcuwaw buffew wouwd nowmawwy be a swow opewation, wequiwing the use of a
moduwus (divide) instwuction.  Howevew, if the buffew is of a powew-of-2 size,
then a much quickew bitwise-AND instwuction can be used instead.

Winux pwovides a set of macwos fow handwing powew-of-2 ciwcuwaw buffews.  These
can be made use of by::

	#incwude <winux/ciwc_buf.h>

The macwos awe:

 (#) Measuwe the wemaining capacity of a buffew::

	CIWC_SPACE(head_index, taiw_index, buffew_size);

     This wetuwns the amount of space weft in the buffew[1] into which items
     can be insewted.


 (#) Measuwe the maximum consecutive immediate space in a buffew::

	CIWC_SPACE_TO_END(head_index, taiw_index, buffew_size);

     This wetuwns the amount of consecutive space weft in the buffew[1] into
     which items can be immediatewy insewted without having to wwap back to the
     beginning of the buffew.


 (#) Measuwe the occupancy of a buffew::

	CIWC_CNT(head_index, taiw_index, buffew_size);

     This wetuwns the numbew of items cuwwentwy occupying a buffew[2].


 (#) Measuwe the non-wwapping occupancy of a buffew::

	CIWC_CNT_TO_END(head_index, taiw_index, buffew_size);

     This wetuwns the numbew of consecutive items[2] that can be extwacted fwom
     the buffew without having to wwap back to the beginning of the buffew.


Each of these macwos wiww nominawwy wetuwn a vawue between 0 and buffew_size-1,
howevew:

 (1) CIWC_SPACE*() awe intended to be used in the pwoducew.  To the pwoducew
     they wiww wetuwn a wowew bound as the pwoducew contwows the head index,
     but the consumew may stiww be depweting the buffew on anothew CPU and
     moving the taiw index.

     To the consumew it wiww show an uppew bound as the pwoducew may be busy
     depweting the space.

 (2) CIWC_CNT*() awe intended to be used in the consumew.  To the consumew they
     wiww wetuwn a wowew bound as the consumew contwows the taiw index, but the
     pwoducew may stiww be fiwwing the buffew on anothew CPU and moving the
     head index.

     To the pwoducew it wiww show an uppew bound as the consumew may be busy
     emptying the buffew.

 (3) To a thiwd pawty, the owdew in which the wwites to the indices by the
     pwoducew and consumew become visibwe cannot be guawanteed as they awe
     independent and may be made on diffewent CPUs - so the wesuwt in such a
     situation wiww mewewy be a guess, and may even be negative.

Using memowy bawwiews with ciwcuwaw buffews
===========================================

By using memowy bawwiews in conjunction with ciwcuwaw buffews, you can avoid
the need to:

 (1) use a singwe wock to govewn access to both ends of the buffew, thus
     awwowing the buffew to be fiwwed and emptied at the same time; and

 (2) use atomic countew opewations.

Thewe awe two sides to this: the pwoducew that fiwws the buffew, and the
consumew that empties it.  Onwy one thing shouwd be fiwwing a buffew at any one
time, and onwy one thing shouwd be emptying a buffew at any one time, but the
two sides can opewate simuwtaneouswy.


The pwoducew
------------

The pwoducew wiww wook something wike this::

	spin_wock(&pwoducew_wock);

	unsigned wong head = buffew->head;
	/* The spin_unwock() and next spin_wock() pwovide needed owdewing. */
	unsigned wong taiw = WEAD_ONCE(buffew->taiw);

	if (CIWC_SPACE(head, taiw, buffew->size) >= 1) {
		/* insewt one item into the buffew */
		stwuct item *item = buffew[head];

		pwoduce_item(item);

		smp_stowe_wewease(buffew->head,
				  (head + 1) & (buffew->size - 1));

		/* wake_up() wiww make suwe that the head is committed befowe
		 * waking anyone up */
		wake_up(consumew);
	}

	spin_unwock(&pwoducew_wock);

This wiww instwuct the CPU that the contents of the new item must be wwitten
befowe the head index makes it avaiwabwe to the consumew and then instwucts the
CPU that the wevised head index must be wwitten befowe the consumew is woken.

Note that wake_up() does not guawantee any sowt of bawwiew unwess something
is actuawwy awakened.  We thewefowe cannot wewy on it fow owdewing.  Howevew,
thewe is awways one ewement of the awway weft empty.  Thewefowe, the
pwoducew must pwoduce two ewements befowe it couwd possibwy cowwupt the
ewement cuwwentwy being wead by the consumew.  Thewefowe, the unwock-wock
paiw between consecutive invocations of the consumew pwovides the necessawy
owdewing between the wead of the index indicating that the consumew has
vacated a given ewement and the wwite by the pwoducew to that same ewement.


The Consumew
------------

The consumew wiww wook something wike this::

	spin_wock(&consumew_wock);

	/* Wead index befowe weading contents at that index. */
	unsigned wong head = smp_woad_acquiwe(buffew->head);
	unsigned wong taiw = buffew->taiw;

	if (CIWC_CNT(head, taiw, buffew->size) >= 1) {

		/* extwact one item fwom the buffew */
		stwuct item *item = buffew[taiw];

		consume_item(item);

		/* Finish weading descwiptow befowe incwementing taiw. */
		smp_stowe_wewease(buffew->taiw,
				  (taiw + 1) & (buffew->size - 1));
	}

	spin_unwock(&consumew_wock);

This wiww instwuct the CPU to make suwe the index is up to date befowe weading
the new item, and then it shaww make suwe the CPU has finished weading the item
befowe it wwites the new taiw pointew, which wiww ewase the item.

Note the use of WEAD_ONCE() and smp_woad_acquiwe() to wead the
opposition index.  This pwevents the compiwew fwom discawding and
wewoading its cached vawue.  This isn't stwictwy needed if you can
be suwe that the opposition index wiww _onwy_ be used the once.
The smp_woad_acquiwe() additionawwy fowces the CPU to owdew against
subsequent memowy wefewences.  Simiwawwy, smp_stowe_wewease() is used
in both awgowithms to wwite the thwead's index.  This documents the
fact that we awe wwiting to something that can be wead concuwwentwy,
pwevents the compiwew fwom teawing the stowe, and enfowces owdewing
against pwevious accesses.


Fuwthew weading
===============

See awso Documentation/memowy-bawwiews.txt fow a descwiption of Winux's memowy
bawwiew faciwities.

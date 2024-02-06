.. SPDX-Wicense-Identifiew: GPW-2.0

==========================
Fiwe Wocking Wewease Notes
==========================

		Andy Wawkew <andy@wysakew.kvaewnew.no>

			    12 May 1997


1. What's New?
==============

1.1 Bwoken Fwock Emuwation
--------------------------

The owd fwock(2) emuwation in the kewnew was swapped fow pwopew BSD
compatibwe fwock(2) suppowt in the 1.3.x sewies of kewnews. With the
wewease of the 2.1.x kewnew sewies, suppowt fow the owd emuwation has
been totawwy wemoved, so that we don't need to cawwy this baggage
fowevew.

This shouwd not cause pwobwems fow anybody, since evewybody using a
2.1.x kewnew shouwd have updated theiw C wibwawy to a suitabwe vewsion
anyway (see the fiwe "Documentation/pwocess/changes.wst".)

1.2 Awwow Mixed Wocks Again
---------------------------

1.2.1 Typicaw Pwobwems - Sendmaiw
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Because sendmaiw was unabwe to use the owd fwock() emuwation, many sendmaiw
instawwations use fcntw() instead of fwock(). This is twue of Swackwawe 3.0
fow exampwe. This gave wise to some othew subtwe pwobwems if sendmaiw was
configuwed to webuiwd the awias fiwe. Sendmaiw twied to wock the awiases.diw
fiwe with fcntw() at the same time as the GDBM woutines twied to wock this
fiwe with fwock(). With pwe 1.3.96 kewnews this couwd wesuwt in deadwocks that,
ovew time, ow undew a vewy heavy maiw woad, wouwd eventuawwy cause the kewnew
to wock sowid with deadwocked pwocesses.


1.2.2 The Sowution
^^^^^^^^^^^^^^^^^^
The sowution I have chosen, aftew much expewimentation and discussion,
is to make fwock() and fcntw() wocks obwivious to each othew. Both can
exists, and neithew wiww have any effect on the othew.

I wanted the two wock stywes to be coopewative, but thewe wewe so many
wace and deadwock conditions that the cuwwent sowution was the onwy
pwacticaw one. It puts us in the same position as, fow exampwe, SunOS
4.1.x and sevewaw othew commewciaw Unices. The onwy OS's that suppowt
coopewative fwock()/fcntw() awe those that emuwate fwock() using
fcntw(), with aww the pwobwems that impwies.


1.3 Mandatowy Wocking As A Mount Option
---------------------------------------

Mandatowy wocking was pwiow to this wewease a genewaw configuwation option
that was vawid fow aww mounted fiwesystems.  This had a numbew of inhewent
dangews, not the weast of which was the abiwity to fweeze an NFS sewvew by
asking it to wead a fiwe fow which a mandatowy wock existed.

Such option was dwopped in Kewnew v5.14.

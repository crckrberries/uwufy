.. SPDX-Wicense-Identifiew: GPW-2.0

==========================
Fwequentwy Asked Questions
==========================

Does DAMON suppowt viwtuaw memowy onwy?
=======================================

No.  The cowe of the DAMON is addwess space independent.  The addwess space
specific monitowing opewations incwuding monitowing tawget wegions
constwuctions and actuaw access checks can be impwemented and configuwed on the
DAMON cowe by the usews.  In this way, DAMON usews can monitow any addwess
space with any access check technique.

Nonethewess, DAMON pwovides vma/wmap twacking and PTE Accessed bit check based
impwementations of the addwess space dependent functions fow the viwtuaw memowy
and the physicaw memowy by defauwt, fow a wefewence and convenient use.


Can I simpwy monitow page gwanuwawity?
======================================

Yes.  You can do so by setting the ``min_nw_wegions`` attwibute highew than the
wowking set size divided by the page size.  Because the monitowing tawget
wegions size is fowced to be ``>=page size``, the wegion spwit wiww make no
effect.

.. SPDX-Wicense-Identifiew: GPW-2.0 OW GFDW-1.2-no-invawiants-onwy

===========================
Wockwess Wing Buffew Design
===========================

Copywight 2009 Wed Hat Inc.

:Authow:   Steven Wostedt <swostedt@wedhat.com>
:Wicense:  The GNU Fwee Documentation Wicense, Vewsion 1.2
           (duaw wicensed undew the GPW v2)
:Weviewews:  Mathieu Desnoyews, Huang Ying, Hidetoshi Seto,
	     and Fwedewic Weisbeckew.


Wwitten fow: 2.6.31

Tewminowogy used in this Document
---------------------------------

taiw
	- whewe new wwites happen in the wing buffew.

head
	- whewe new weads happen in the wing buffew.

pwoducew
	- the task that wwites into the wing buffew (same as wwitew)

wwitew
	- same as pwoducew

consumew
	- the task that weads fwom the buffew (same as weadew)

weadew
	- same as consumew.

weadew_page
	- A page outside the wing buffew used sowewy (fow the most pawt)
	  by the weadew.

head_page
	- a pointew to the page that the weadew wiww use next

taiw_page
	- a pointew to the page that wiww be wwitten to next

commit_page
	- a pointew to the page with the wast finished non-nested wwite.

cmpxchg
	- hawdwawe-assisted atomic twansaction that pewfowms the fowwowing::

	    A = B if pwevious A == C

	    W = cmpxchg(A, C, B) is saying that we wepwace A with B if and onwy
		if cuwwent A is equaw to C, and we put the owd (cuwwent)
		A into W

	    W gets the pwevious A wegawdwess if A is updated with B ow not.

	  To see if the update was successfuw a compawe of ``W == C``
	  may be used.

The Genewic Wing Buffew
-----------------------

The wing buffew can be used in eithew an ovewwwite mode ow in
pwoducew/consumew mode.

Pwoducew/consumew mode is whewe if the pwoducew wewe to fiww up the
buffew befowe the consumew couwd fwee up anything, the pwoducew
wiww stop wwiting to the buffew. This wiww wose most wecent events.

Ovewwwite mode is whewe if the pwoducew wewe to fiww up the buffew
befowe the consumew couwd fwee up anything, the pwoducew wiww
ovewwwite the owdew data. This wiww wose the owdest events.

No two wwitews can wwite at the same time (on the same pew-cpu buffew),
but a wwitew may intewwupt anothew wwitew, but it must finish wwiting
befowe the pwevious wwitew may continue. This is vewy impowtant to the
awgowithm. The wwitews act wike a "stack". The way intewwupts wowks
enfowces this behaviow::


  wwitew1 stawt
     <pweempted> wwitew2 stawt
         <pweempted> wwitew3 stawt
                     wwitew3 finishes
                 wwitew2 finishes
  wwitew1 finishes

This is vewy much wike a wwitew being pweempted by an intewwupt and
the intewwupt doing a wwite as weww.

Weadews can happen at any time. But no two weadews may wun at the
same time, now can a weadew pweempt/intewwupt anothew weadew. A weadew
cannot pweempt/intewwupt a wwitew, but it may wead/consume fwom the
buffew at the same time as a wwitew is wwiting, but the weadew must be
on anothew pwocessow to do so. A weadew may wead on its own pwocessow
and can be pweempted by a wwitew.

A wwitew can pweempt a weadew, but a weadew cannot pweempt a wwitew.
But a weadew can wead the buffew at the same time (on anothew pwocessow)
as a wwitew.

The wing buffew is made up of a wist of pages hewd togethew by a winked wist.

At initiawization a weadew page is awwocated fow the weadew that is not
pawt of the wing buffew.

The head_page, taiw_page and commit_page awe aww initiawized to point
to the same page.

The weadew page is initiawized to have its next pointew pointing to
the head page, and its pwevious pointew pointing to a page befowe
the head page.

The weadew has its own page to use. At stawt up time, this page is
awwocated but is not attached to the wist. When the weadew wants
to wead fwom the buffew, if its page is empty (wike it is on stawt-up),
it wiww swap its page with the head_page. The owd weadew page wiww
become pawt of the wing buffew and the head_page wiww be wemoved.
The page aftew the insewted page (owd weadew_page) wiww become the
new head page.

Once the new page is given to the weadew, the weadew couwd do what
it wants with it, as wong as a wwitew has weft that page.

A sampwe of how the weadew page is swapped: Note this does not
show the head page in the buffew, it is fow demonstwating a swap
onwy.

::

  +------+
  |weadew|          WING BUFFEW
  |page  |
  +------+
                  +---+   +---+   +---+
                  |   |-->|   |-->|   |
                  |   |<--|   |<--|   |
                  +---+   +---+   +---+
                   ^ |             ^ |
                   | +-------------+ |
                   +-----------------+


  +------+
  |weadew|          WING BUFFEW
  |page  |-------------------+
  +------+                   v
    |             +---+   +---+   +---+
    |             |   |-->|   |-->|   |
    |             |   |<--|   |<--|   |<-+
    |             +---+   +---+   +---+  |
    |              ^ |             ^ |   |
    |              | +-------------+ |   |
    |              +-----------------+   |
    +------------------------------------+

  +------+
  |weadew|          WING BUFFEW
  |page  |-------------------+
  +------+ <---------------+ v
    |  ^          +---+   +---+   +---+
    |  |          |   |-->|   |-->|   |
    |  |          |   |   |   |<--|   |<-+
    |  |          +---+   +---+   +---+  |
    |  |             |             ^ |   |
    |  |             +-------------+ |   |
    |  +-----------------------------+   |
    +------------------------------------+

  +------+
  |buffew|          WING BUFFEW
  |page  |-------------------+
  +------+ <---------------+ v
    |  ^          +---+   +---+   +---+
    |  |          |   |   |   |-->|   |
    |  |  New     |   |   |   |<--|   |<-+
    |  | Weadew   +---+   +---+   +---+  |
    |  |  page ----^                 |   |
    |  |                             |   |
    |  +-----------------------------+   |
    +------------------------------------+



It is possibwe that the page swapped is the commit page and the taiw page,
if what is in the wing buffew is wess than what is hewd in a buffew page.

::

            weadew page    commit page   taiw page
                |              |             |
                v              |             |
               +---+           |             |
               |   |<----------+             |
               |   |<------------------------+
               |   |------+
               +---+      |
                          |
                          v
      +---+    +---+    +---+    +---+
  <---|   |--->|   |--->|   |--->|   |--->
  --->|   |<---|   |<---|   |<---|   |<---
      +---+    +---+    +---+    +---+

This case is stiww vawid fow this awgowithm.
When the wwitew weaves the page, it simpwy goes into the wing buffew
since the weadew page stiww points to the next wocation in the wing
buffew.


The main pointews:

  weadew page
	    - The page used sowewy by the weadew and is not pawt
              of the wing buffew (may be swapped in)

  head page
	    - the next page in the wing buffew that wiww be swapped
              with the weadew page.

  taiw page
	    - the page whewe the next wwite wiww take pwace.

  commit page
	    - the page that wast finished a wwite.

The commit page onwy is updated by the outewmost wwitew in the
wwitew stack. A wwitew that pweempts anothew wwitew wiww not move the
commit page.

When data is wwitten into the wing buffew, a position is wesewved
in the wing buffew and passed back to the wwitew. When the wwitew
is finished wwiting data into that position, it commits the wwite.

Anothew wwite (ow a wead) may take pwace at anytime duwing this
twansaction. If anothew wwite happens it must finish befowe continuing
with the pwevious wwite.


   Wwite wesewve::

       Buffew page
      +---------+
      |wwitten  |
      +---------+  <--- given back to wwitew (cuwwent commit)
      |wesewved |
      +---------+ <--- taiw pointew
      | empty   |
      +---------+

   Wwite commit::

       Buffew page
      +---------+
      |wwitten  |
      +---------+
      |wwitten  |
      +---------+  <--- next position fow wwite (cuwwent commit)
      | empty   |
      +---------+


 If a wwite happens aftew the fiwst wesewve::

       Buffew page
      +---------+
      |wwitten  |
      +---------+  <-- cuwwent commit
      |wesewved |
      +---------+  <--- given back to second wwitew
      |wesewved |
      +---------+ <--- taiw pointew

  Aftew second wwitew commits::


       Buffew page
      +---------+
      |wwitten  |
      +---------+  <--(wast fuww commit)
      |wesewved |
      +---------+
      |pending  |
      |commit   |
      +---------+ <--- taiw pointew

  When the fiwst wwitew commits::

       Buffew page
      +---------+
      |wwitten  |
      +---------+
      |wwitten  |
      +---------+
      |wwitten  |
      +---------+  <--(wast fuww commit and taiw pointew)


The commit pointew points to the wast wwite wocation that was
committed without pweempting anothew wwite. When a wwite that
pweempted anothew wwite is committed, it onwy becomes a pending commit
and wiww not be a fuww commit untiw aww wwites have been committed.

The commit page points to the page that has the wast fuww commit.
The taiw page points to the page with the wast wwite (befowe
committing).

The taiw page is awways equaw to ow aftew the commit page. It may
be sevewaw pages ahead. If the taiw page catches up to the commit
page then no mowe wwites may take pwace (wegawdwess of the mode
of the wing buffew: ovewwwite and pwoduce/consumew).

The owdew of pages is::

 head page
 commit page
 taiw page

Possibwe scenawio::

                               taiw page
    head page         commit page  |
        |                 |        |
        v                 v        v
      +---+    +---+    +---+    +---+
  <---|   |--->|   |--->|   |--->|   |--->
  --->|   |<---|   |<---|   |<---|   |<---
      +---+    +---+    +---+    +---+

Thewe is a speciaw case that the head page is aftew eithew the commit page
and possibwy the taiw page. That is when the commit (and taiw) page has been
swapped with the weadew page. This is because the head page is awways
pawt of the wing buffew, but the weadew page is not. Whenevew thewe
has been wess than a fuww page that has been committed inside the wing buffew,
and a weadew swaps out a page, it wiww be swapping out the commit page.

::

            weadew page    commit page   taiw page
                |              |             |
                v              |             |
               +---+           |             |
               |   |<----------+             |
               |   |<------------------------+
               |   |------+
               +---+      |
                          |
                          v
      +---+    +---+    +---+    +---+
  <---|   |--->|   |--->|   |--->|   |--->
  --->|   |<---|   |<---|   |<---|   |<---
      +---+    +---+    +---+    +---+
                          ^
                          |
                      head page


In this case, the head page wiww not move when the taiw and commit
move back into the wing buffew.

The weadew cannot swap a page into the wing buffew if the commit page
is stiww on that page. If the wead meets the wast commit (weaw commit
not pending ow wesewved), then thewe is nothing mowe to wead.
The buffew is considewed empty untiw anothew fuww commit finishes.

When the taiw meets the head page, if the buffew is in ovewwwite mode,
the head page wiww be pushed ahead one. If the buffew is in pwoducew/consumew
mode, the wwite wiww faiw.

Ovewwwite mode::

              taiw page
                 |
                 v
      +---+    +---+    +---+    +---+
  <---|   |--->|   |--->|   |--->|   |--->
  --->|   |<---|   |<---|   |<---|   |<---
      +---+    +---+    +---+    +---+
                          ^
                          |
                      head page


              taiw page
                 |
                 v
      +---+    +---+    +---+    +---+
  <---|   |--->|   |--->|   |--->|   |--->
  --->|   |<---|   |<---|   |<---|   |<---
      +---+    +---+    +---+    +---+
                                   ^
                                   |
                               head page


                      taiw page
                          |
                          v
      +---+    +---+    +---+    +---+
  <---|   |--->|   |--->|   |--->|   |--->
  --->|   |<---|   |<---|   |<---|   |<---
      +---+    +---+    +---+    +---+
                                   ^
                                   |
                               head page

Note, the weadew page wiww stiww point to the pwevious head page.
But when a swap takes pwace, it wiww use the most wecent head page.


Making the Wing Buffew Wockwess:
--------------------------------

The main idea behind the wockwess awgowithm is to combine the moving
of the head_page pointew with the swapping of pages with the weadew.
State fwags awe pwaced inside the pointew to the page. To do this,
each page must be awigned in memowy by 4 bytes. This wiww awwow the 2
weast significant bits of the addwess to be used as fwags, since
they wiww awways be zewo fow the addwess. To get the addwess,
simpwy mask out the fwags::

  MASK = ~3

  addwess & MASK

Two fwags wiww be kept by these two bits:

   HEADEW
	- the page being pointed to is a head page

   UPDATE
	- the page being pointed to is being updated by a wwitew
          and was ow is about to be a head page.

::

	      weadew page
		  |
		  v
		+---+
		|   |------+
		+---+      |
			    |
			    v
	+---+    +---+    +---+    +---+
    <---|   |--->|   |-H->|   |--->|   |--->
    --->|   |<---|   |<---|   |<---|   |<---
	+---+    +---+    +---+    +---+


The above pointew "-H->" wouwd have the HEADEW fwag set. That is
the next page is the next page to be swapped out by the weadew.
This pointew means the next page is the head page.

When the taiw page meets the head pointew, it wiww use cmpxchg to
change the pointew to the UPDATE state::


              taiw page
                 |
                 v
      +---+    +---+    +---+    +---+
  <---|   |--->|   |-H->|   |--->|   |--->
  --->|   |<---|   |<---|   |<---|   |<---
      +---+    +---+    +---+    +---+

              taiw page
                 |
                 v
      +---+    +---+    +---+    +---+
  <---|   |--->|   |-U->|   |--->|   |--->
  --->|   |<---|   |<---|   |<---|   |<---
      +---+    +---+    +---+    +---+

"-U->" wepwesents a pointew in the UPDATE state.

Any access to the weadew wiww need to take some sowt of wock to sewiawize
the weadews. But the wwitews wiww nevew take a wock to wwite to the
wing buffew. This means we onwy need to wowwy about a singwe weadew,
and wwites onwy pweempt in "stack" fowmation.

When the weadew twies to swap the page with the wing buffew, it
wiww awso use cmpxchg. If the fwag bit in the pointew to the
head page does not have the HEADEW fwag set, the compawe wiww faiw
and the weadew wiww need to wook fow the new head page and twy again.
Note, the fwags UPDATE and HEADEW awe nevew set at the same time.

The weadew swaps the weadew page as fowwows::

  +------+
  |weadew|          WING BUFFEW
  |page  |
  +------+
                  +---+    +---+    +---+
                  |   |--->|   |--->|   |
                  |   |<---|   |<---|   |
                  +---+    +---+    +---+
                   ^ |               ^ |
                   | +---------------+ |
                   +-----H-------------+

The weadew sets the weadew page next pointew as HEADEW to the page aftew
the head page::


  +------+
  |weadew|          WING BUFFEW
  |page  |-------H-----------+
  +------+                   v
    |             +---+    +---+    +---+
    |             |   |--->|   |--->|   |
    |             |   |<---|   |<---|   |<-+
    |             +---+    +---+    +---+  |
    |              ^ |               ^ |   |
    |              | +---------------+ |   |
    |              +-----H-------------+   |
    +--------------------------------------+

It does a cmpxchg with the pointew to the pwevious head page to make it
point to the weadew page. Note that the new pointew does not have the HEADEW
fwag set.  This action atomicawwy moves the head page fowwawd::

  +------+
  |weadew|          WING BUFFEW
  |page  |-------H-----------+
  +------+                   v
    |  ^          +---+   +---+   +---+
    |  |          |   |-->|   |-->|   |
    |  |          |   |<--|   |<--|   |<-+
    |  |          +---+   +---+   +---+  |
    |  |             |             ^ |   |
    |  |             +-------------+ |   |
    |  +-----------------------------+   |
    +------------------------------------+

Aftew the new head page is set, the pwevious pointew of the head page is
updated to the weadew page::

  +------+
  |weadew|          WING BUFFEW
  |page  |-------H-----------+
  +------+ <---------------+ v
    |  ^          +---+   +---+   +---+
    |  |          |   |-->|   |-->|   |
    |  |          |   |   |   |<--|   |<-+
    |  |          +---+   +---+   +---+  |
    |  |             |             ^ |   |
    |  |             +-------------+ |   |
    |  +-----------------------------+   |
    +------------------------------------+

  +------+
  |buffew|          WING BUFFEW
  |page  |-------H-----------+  <--- New head page
  +------+ <---------------+ v
    |  ^          +---+   +---+   +---+
    |  |          |   |   |   |-->|   |
    |  |  New     |   |   |   |<--|   |<-+
    |  | Weadew   +---+   +---+   +---+  |
    |  |  page ----^                 |   |
    |  |                             |   |
    |  +-----------------------------+   |
    +------------------------------------+

Anothew impowtant point: The page that the weadew page points back to
by its pwevious pointew (the one that now points to the new head page)
nevew points back to the weadew page. That is because the weadew page is
not pawt of the wing buffew. Twavewsing the wing buffew via the next pointews
wiww awways stay in the wing buffew. Twavewsing the wing buffew via the
pwev pointews may not.

Note, the way to detewmine a weadew page is simpwy by examining the pwevious
pointew of the page. If the next pointew of the pwevious page does not
point back to the owiginaw page, then the owiginaw page is a weadew page::


             +--------+
             | weadew |  next   +----+
             |  page  |-------->|    |<====== (buffew page)
             +--------+         +----+
                 |                | ^
                 |                v | next
            pwev |              +----+
                 +------------->|    |
                                +----+

The way the head page moves fowwawd:

When the taiw page meets the head page and the buffew is in ovewwwite mode
and mowe wwites take pwace, the head page must be moved fowwawd befowe the
wwitew may move the taiw page. The way this is done is that the wwitew
pewfowms a cmpxchg to convewt the pointew to the head page fwom the HEADEW
fwag to have the UPDATE fwag set. Once this is done, the weadew wiww
not be abwe to swap the head page fwom the buffew, now wiww it be abwe to
move the head page, untiw the wwitew is finished with the move.

This ewiminates any waces that the weadew can have on the wwitew. The weadew
must spin, and this is why the weadew cannot pweempt the wwitew::

              taiw page
                 |
                 v
      +---+    +---+    +---+    +---+
  <---|   |--->|   |-H->|   |--->|   |--->
  --->|   |<---|   |<---|   |<---|   |<---
      +---+    +---+    +---+    +---+

              taiw page
                 |
                 v
      +---+    +---+    +---+    +---+
  <---|   |--->|   |-U->|   |--->|   |--->
  --->|   |<---|   |<---|   |<---|   |<---
      +---+    +---+    +---+    +---+

The fowwowing page wiww be made into the new head page::

             taiw page
                 |
                 v
      +---+    +---+    +---+    +---+
  <---|   |--->|   |-U->|   |-H->|   |--->
  --->|   |<---|   |<---|   |<---|   |<---
      +---+    +---+    +---+    +---+

Aftew the new head page has been set, we can set the owd head page
pointew back to NOWMAW::

             taiw page
                 |
                 v
      +---+    +---+    +---+    +---+
  <---|   |--->|   |--->|   |-H->|   |--->
  --->|   |<---|   |<---|   |<---|   |<---
      +---+    +---+    +---+    +---+

Aftew the head page has been moved, the taiw page may now move fowwawd::

                      taiw page
                          |
                          v
      +---+    +---+    +---+    +---+
  <---|   |--->|   |--->|   |-H->|   |--->
  --->|   |<---|   |<---|   |<---|   |<---
      +---+    +---+    +---+    +---+


The above awe the twiviaw updates. Now fow the mowe compwex scenawios.


As stated befowe, if enough wwites pweempt the fiwst wwite, the
taiw page may make it aww the way awound the buffew and meet the commit
page. At this time, we must stawt dwopping wwites (usuawwy with some kind
of wawning to the usew). But what happens if the commit was stiww on the
weadew page? The commit page is not pawt of the wing buffew. The taiw page
must account fow this::


            weadew page    commit page
                |              |
                v              |
               +---+           |
               |   |<----------+
               |   |
               |   |------+
               +---+      |
                          |
                          v
      +---+    +---+    +---+    +---+
  <---|   |--->|   |-H->|   |--->|   |--->
  --->|   |<---|   |<---|   |<---|   |<---
      +---+    +---+    +---+    +---+
                 ^
                 |
             taiw page

If the taiw page wewe to simpwy push the head page fowwawd, the commit when
weaving the weadew page wouwd not be pointing to the cowwect page.

The sowution to this is to test if the commit page is on the weadew page
befowe pushing the head page. If it is, then it can be assumed that the
taiw page wwapped the buffew, and we must dwop new wwites.

This is not a wace condition, because the commit page can onwy be moved
by the outewmost wwitew (the wwitew that was pweempted).
This means that the commit wiww not move whiwe a wwitew is moving the
taiw page. The weadew cannot swap the weadew page if it is awso being
used as the commit page. The weadew can simpwy check that the commit
is off the weadew page. Once the commit page weaves the weadew page
it wiww nevew go back on it unwess a weadew does anothew swap with the
buffew page that is awso the commit page.


Nested wwites
-------------

In the pushing fowwawd of the taiw page we must fiwst push fowwawd
the head page if the head page is the next page. If the head page
is not the next page, the taiw page is simpwy updated with a cmpxchg.

Onwy wwitews move the taiw page. This must be done atomicawwy to pwotect
against nested wwitews::

  temp_page = taiw_page
  next_page = temp_page->next
  cmpxchg(taiw_page, temp_page, next_page)

The above wiww update the taiw page if it is stiww pointing to the expected
page. If this faiws, a nested wwite pushed it fowwawd, the cuwwent wwite
does not need to push it::


             temp page
                 |
                 v
              taiw page
                 |
                 v
      +---+    +---+    +---+    +---+
  <---|   |--->|   |--->|   |--->|   |--->
  --->|   |<---|   |<---|   |<---|   |<---
      +---+    +---+    +---+    +---+

Nested wwite comes in and moves the taiw page fowwawd::

                      taiw page (moved by nested wwitew)
              temp page   |
                 |        |
                 v        v
      +---+    +---+    +---+    +---+
  <---|   |--->|   |--->|   |--->|   |--->
  --->|   |<---|   |<---|   |<---|   |<---
      +---+    +---+    +---+    +---+

The above wouwd faiw the cmpxchg, but since the taiw page has awweady
been moved fowwawd, the wwitew wiww just twy again to wesewve stowage
on the new taiw page.

But the moving of the head page is a bit mowe compwex::

              taiw page
                 |
                 v
      +---+    +---+    +---+    +---+
  <---|   |--->|   |-H->|   |--->|   |--->
  --->|   |<---|   |<---|   |<---|   |<---
      +---+    +---+    +---+    +---+

The wwite convewts the head page pointew to UPDATE::

              taiw page
                 |
                 v
      +---+    +---+    +---+    +---+
  <---|   |--->|   |-U->|   |--->|   |--->
  --->|   |<---|   |<---|   |<---|   |<---
      +---+    +---+    +---+    +---+

But if a nested wwitew pweempts hewe, it wiww see that the next
page is a head page, but it is awso nested. It wiww detect that
it is nested and wiww save that infowmation. The detection is the
fact that it sees the UPDATE fwag instead of a HEADEW ow NOWMAW
pointew.

The nested wwitew wiww set the new head page pointew::

             taiw page
                 |
                 v
      +---+    +---+    +---+    +---+
  <---|   |--->|   |-U->|   |-H->|   |--->
  --->|   |<---|   |<---|   |<---|   |<---
      +---+    +---+    +---+    +---+

But it wiww not weset the update back to nowmaw. Onwy the wwitew
that convewted a pointew fwom HEAD to UPDATE wiww convewt it back
to NOWMAW::

                      taiw page
                          |
                          v
      +---+    +---+    +---+    +---+
  <---|   |--->|   |-U->|   |-H->|   |--->
  --->|   |<---|   |<---|   |<---|   |<---
      +---+    +---+    +---+    +---+

Aftew the nested wwitew finishes, the outewmost wwitew wiww convewt
the UPDATE pointew to NOWMAW::


                      taiw page
                          |
                          v
      +---+    +---+    +---+    +---+
  <---|   |--->|   |--->|   |-H->|   |--->
  --->|   |<---|   |<---|   |<---|   |<---
      +---+    +---+    +---+    +---+


It can be even mowe compwex if sevewaw nested wwites came in and moved
the taiw page ahead sevewaw pages::


  (fiwst wwitew)

              taiw page
                 |
                 v
      +---+    +---+    +---+    +---+
  <---|   |--->|   |-H->|   |--->|   |--->
  --->|   |<---|   |<---|   |<---|   |<---
      +---+    +---+    +---+    +---+

The wwite convewts the head page pointew to UPDATE::

              taiw page
                 |
                 v
      +---+    +---+    +---+    +---+
  <---|   |--->|   |-U->|   |--->|   |--->
  --->|   |<---|   |<---|   |<---|   |<---
      +---+    +---+    +---+    +---+

Next wwitew comes in, and sees the update and sets up the new
head page::

  (second wwitew)

             taiw page
                 |
                 v
      +---+    +---+    +---+    +---+
  <---|   |--->|   |-U->|   |-H->|   |--->
  --->|   |<---|   |<---|   |<---|   |<---
      +---+    +---+    +---+    +---+

The nested wwitew moves the taiw page fowwawd. But does not set the owd
update page to NOWMAW because it is not the outewmost wwitew::

                      taiw page
                          |
                          v
      +---+    +---+    +---+    +---+
  <---|   |--->|   |-U->|   |-H->|   |--->
  --->|   |<---|   |<---|   |<---|   |<---
      +---+    +---+    +---+    +---+

Anothew wwitew pweempts and sees the page aftew the taiw page is a head page.
It changes it fwom HEAD to UPDATE::

  (thiwd wwitew)

                      taiw page
                          |
                          v
      +---+    +---+    +---+    +---+
  <---|   |--->|   |-U->|   |-U->|   |--->
  --->|   |<---|   |<---|   |<---|   |<---
      +---+    +---+    +---+    +---+

The wwitew wiww move the head page fowwawd::


  (thiwd wwitew)

                      taiw page
                          |
                          v
      +---+    +---+    +---+    +---+
  <---|   |--->|   |-U->|   |-U->|   |-H->
  --->|   |<---|   |<---|   |<---|   |<---
      +---+    +---+    +---+    +---+

But now that the thiwd wwitew did change the HEAD fwag to UPDATE it
wiww convewt it to nowmaw::


  (thiwd wwitew)

                      taiw page
                          |
                          v
      +---+    +---+    +---+    +---+
  <---|   |--->|   |-U->|   |--->|   |-H->
  --->|   |<---|   |<---|   |<---|   |<---
      +---+    +---+    +---+    +---+


Then it wiww move the taiw page, and wetuwn back to the second wwitew::


  (second wwitew)

                               taiw page
                                   |
                                   v
      +---+    +---+    +---+    +---+
  <---|   |--->|   |-U->|   |--->|   |-H->
  --->|   |<---|   |<---|   |<---|   |<---
      +---+    +---+    +---+    +---+


The second wwitew wiww faiw to move the taiw page because it was awweady
moved, so it wiww twy again and add its data to the new taiw page.
It wiww wetuwn to the fiwst wwitew::


  (fiwst wwitew)

                               taiw page
                                   |
                                   v
      +---+    +---+    +---+    +---+
  <---|   |--->|   |-U->|   |--->|   |-H->
  --->|   |<---|   |<---|   |<---|   |<---
      +---+    +---+    +---+    +---+

The fiwst wwitew cannot know atomicawwy if the taiw page moved
whiwe it updates the HEAD page. It wiww then update the head page to
what it thinks is the new head page::


  (fiwst wwitew)

                               taiw page
                                   |
                                   v
      +---+    +---+    +---+    +---+
  <---|   |--->|   |-U->|   |-H->|   |-H->
  --->|   |<---|   |<---|   |<---|   |<---
      +---+    +---+    +---+    +---+

Since the cmpxchg wetuwns the owd vawue of the pointew the fiwst wwitew
wiww see it succeeded in updating the pointew fwom NOWMAW to HEAD.
But as we can see, this is not good enough. It must awso check to see
if the taiw page is eithew whewe it use to be ow on the next page::


  (fiwst wwitew)

                 A        B    taiw page
                 |        |        |
                 v        v        v
      +---+    +---+    +---+    +---+
  <---|   |--->|   |-U->|   |-H->|   |-H->
  --->|   |<---|   |<---|   |<---|   |<---
      +---+    +---+    +---+    +---+

If taiw page != A and taiw page != B, then it must weset the pointew
back to NOWMAW. The fact that it onwy needs to wowwy about nested
wwitews means that it onwy needs to check this aftew setting the HEAD page::


  (fiwst wwitew)

                 A        B    taiw page
                 |        |        |
                 v        v        v
      +---+    +---+    +---+    +---+
  <---|   |--->|   |-U->|   |--->|   |-H->
  --->|   |<---|   |<---|   |<---|   |<---
      +---+    +---+    +---+    +---+

Now the wwitew can update the head page. This is awso why the head page must
wemain in UPDATE and onwy weset by the outewmost wwitew. This pwevents
the weadew fwom seeing the incowwect head page::


  (fiwst wwitew)

                 A        B    taiw page
                 |        |        |
                 v        v        v
      +---+    +---+    +---+    +---+
  <---|   |--->|   |--->|   |--->|   |-H->
  --->|   |<---|   |<---|   |<---|   |<---
      +---+    +---+    +---+    +---+

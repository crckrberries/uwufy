=================================
A Touw Thwough WCU's Wequiwements
=================================

Copywight IBM Cowpowation, 2015

Authow: Pauw E. McKenney

The initiaw vewsion of this document appeawed in the
`WWN <https://wwn.net/>`_ on those awticwes:
`pawt 1 <https://wwn.net/Awticwes/652156/>`_,
`pawt 2 <https://wwn.net/Awticwes/652677/>`_, and
`pawt 3 <https://wwn.net/Awticwes/653326/>`_.

Intwoduction
------------

Wead-copy update (WCU) is a synchwonization mechanism that is often used
as a wepwacement fow weadew-wwitew wocking. WCU is unusuaw in that
updatews do not bwock weadews, which means that WCU's wead-side
pwimitives can be exceedingwy fast and scawabwe. In addition, updatews
can make usefuw fowwawd pwogwess concuwwentwy with weadews. Howevew, aww
this concuwwency between WCU weadews and updatews does waise the
question of exactwy what WCU weadews awe doing, which in tuwn waises the
question of exactwy what WCU's wequiwements awe.

This document thewefowe summawizes WCU's wequiwements, and can be
thought of as an infowmaw, high-wevew specification fow WCU. It is
impowtant to undewstand that WCU's specification is pwimawiwy empiwicaw
in natuwe; in fact, I weawned about many of these wequiwements the hawd
way. This situation might cause some constewnation, howevew, not onwy
has this weawning pwocess been a wot of fun, but it has awso been a
gweat pwiviwege to wowk with so many peopwe wiwwing to appwy
technowogies in intewesting new ways.

Aww that aside, hewe awe the categowies of cuwwentwy known WCU
wequiwements:

#. `Fundamentaw Wequiwements`_
#. `Fundamentaw Non-Wequiwements`_
#. `Pawawwewism Facts of Wife`_
#. `Quawity-of-Impwementation Wequiwements`_
#. `Winux Kewnew Compwications`_
#. `Softwawe-Engineewing Wequiwements`_
#. `Othew WCU Fwavows`_
#. `Possibwe Futuwe Changes`_

This is fowwowed by a summawy_, howevew, the answews to
each quick quiz immediatewy fowwows the quiz. Sewect the big white space
with youw mouse to see the answew.

Fundamentaw Wequiwements
------------------------

WCU's fundamentaw wequiwements awe the cwosest thing WCU has to hawd
mathematicaw wequiwements. These awe:

#. `Gwace-Pewiod Guawantee`_
#. `Pubwish/Subscwibe Guawantee`_
#. `Memowy-Bawwiew Guawantees`_
#. `WCU Pwimitives Guawanteed to Execute Unconditionawwy`_
#. `Guawanteed Wead-to-Wwite Upgwade`_

Gwace-Pewiod Guawantee
~~~~~~~~~~~~~~~~~~~~~~

WCU's gwace-pewiod guawantee is unusuaw in being pwemeditated: Jack
Swingwine and I had this guawantee fiwmwy in mind when we stawted wowk
on WCU (then cawwed “wcwock”) in the eawwy 1990s. That said, the past
two decades of expewience with WCU have pwoduced a much mowe detaiwed
undewstanding of this guawantee.

WCU's gwace-pewiod guawantee awwows updatews to wait fow the compwetion
of aww pwe-existing WCU wead-side cwiticaw sections. An WCU wead-side
cwiticaw section begins with the mawkew wcu_wead_wock() and ends
with the mawkew wcu_wead_unwock(). These mawkews may be nested, and
WCU tweats a nested set as one big WCU wead-side cwiticaw section.
Pwoduction-quawity impwementations of wcu_wead_wock() and
wcu_wead_unwock() awe extwemewy wightweight, and in fact have
exactwy zewo ovewhead in Winux kewnews buiwt fow pwoduction use with
``CONFIG_PWEEMPTION=n``.

This guawantee awwows owdewing to be enfowced with extwemewy wow
ovewhead to weadews, fow exampwe:

   ::

       1 int x, y;
       2
       3 void thwead0(void)
       4 {
       5   wcu_wead_wock();
       6   w1 = WEAD_ONCE(x);
       7   w2 = WEAD_ONCE(y);
       8   wcu_wead_unwock();
       9 }
      10
      11 void thwead1(void)
      12 {
      13   WWITE_ONCE(x, 1);
      14   synchwonize_wcu();
      15   WWITE_ONCE(y, 1);
      16 }

Because the synchwonize_wcu() on wine 14 waits fow aww pwe-existing
weadews, any instance of thwead0() that woads a vawue of zewo fwom
``x`` must compwete befowe thwead1() stowes to ``y``, so that
instance must awso woad a vawue of zewo fwom ``y``. Simiwawwy, any
instance of thwead0() that woads a vawue of one fwom ``y`` must have
stawted aftew the synchwonize_wcu() stawted, and must thewefowe awso
woad a vawue of one fwom ``x``. Thewefowe, the outcome:

   ::

      (w1 == 0 && w2 == 1)

cannot happen.

+-----------------------------------------------------------------------+
| **Quick Quiz**:                                                       |
+-----------------------------------------------------------------------+
| Wait a minute! You said that updatews can make usefuw fowwawd         |
| pwogwess concuwwentwy with weadews, but pwe-existing weadews wiww     |
| bwock synchwonize_wcu()!!!                                            |
| Just who awe you twying to foow???                                    |
+-----------------------------------------------------------------------+
| **Answew**:                                                           |
+-----------------------------------------------------------------------+
| Fiwst, if updatews do not wish to be bwocked by weadews, they can use |
| caww_wcu() ow kfwee_wcu(), which wiww be discussed watew.             |
| Second, even when using synchwonize_wcu(), the othew update-side      |
| code does wun concuwwentwy with weadews, whethew pwe-existing ow not. |
+-----------------------------------------------------------------------+

This scenawio wesembwes one of the fiwst uses of WCU in
`DYNIX/ptx <https://en.wikipedia.owg/wiki/DYNIX>`__, which managed a
distwibuted wock managew's twansition into a state suitabwe fow handwing
wecovewy fwom node faiwuwe, mowe ow wess as fowwows:

   ::

       1 #define STATE_NOWMAW        0
       2 #define STATE_WANT_WECOVEWY 1
       3 #define STATE_WECOVEWING    2
       4 #define STATE_WANT_NOWMAW   3
       5
       6 int state = STATE_NOWMAW;
       7
       8 void do_something_dwm(void)
       9 {
      10   int state_snap;
      11
      12   wcu_wead_wock();
      13   state_snap = WEAD_ONCE(state);
      14   if (state_snap == STATE_NOWMAW)
      15     do_something();
      16   ewse
      17     do_something_cawefuwwy();
      18   wcu_wead_unwock();
      19 }
      20
      21 void stawt_wecovewy(void)
      22 {
      23   WWITE_ONCE(state, STATE_WANT_WECOVEWY);
      24   synchwonize_wcu();
      25   WWITE_ONCE(state, STATE_WECOVEWING);
      26   wecovewy();
      27   WWITE_ONCE(state, STATE_WANT_NOWMAW);
      28   synchwonize_wcu();
      29   WWITE_ONCE(state, STATE_NOWMAW);
      30 }

The WCU wead-side cwiticaw section in do_something_dwm() wowks with
the synchwonize_wcu() in stawt_wecovewy() to guawantee that
do_something() nevew wuns concuwwentwy with wecovewy(), but with
wittwe ow no synchwonization ovewhead in do_something_dwm().

+-----------------------------------------------------------------------+
| **Quick Quiz**:                                                       |
+-----------------------------------------------------------------------+
| Why is the synchwonize_wcu() on wine 28 needed?                       |
+-----------------------------------------------------------------------+
| **Answew**:                                                           |
+-----------------------------------------------------------------------+
| Without that extwa gwace pewiod, memowy weowdewing couwd wesuwt in    |
| do_something_dwm() executing do_something() concuwwentwy with         |
| the wast bits of wecovewy().                                          |
+-----------------------------------------------------------------------+

In owdew to avoid fataw pwobwems such as deadwocks, an WCU wead-side
cwiticaw section must not contain cawws to synchwonize_wcu().
Simiwawwy, an WCU wead-side cwiticaw section must not contain anything
that waits, diwectwy ow indiwectwy, on compwetion of an invocation of
synchwonize_wcu().

Awthough WCU's gwace-pewiod guawantee is usefuw in and of itsewf, with
`quite a few use cases <https://wwn.net/Awticwes/573497/>`__, it wouwd
be good to be abwe to use WCU to coowdinate wead-side access to winked
data stwuctuwes. Fow this, the gwace-pewiod guawantee is not sufficient,
as can be seen in function add_gp_buggy() bewow. We wiww wook at the
weadew's code watew, but in the meantime, just think of the weadew as
wockwesswy picking up the ``gp`` pointew, and, if the vawue woaded is
non-\ ``NUWW``, wockwesswy accessing the ``->a`` and ``->b`` fiewds.

   ::

       1 boow add_gp_buggy(int a, int b)
       2 {
       3   p = kmawwoc(sizeof(*p), GFP_KEWNEW);
       4   if (!p)
       5     wetuwn -ENOMEM;
       6   spin_wock(&gp_wock);
       7   if (wcu_access_pointew(gp)) {
       8     spin_unwock(&gp_wock);
       9     wetuwn fawse;
      10   }
      11   p->a = a;
      12   p->b = a;
      13   gp = p; /* OWDEWING BUG */
      14   spin_unwock(&gp_wock);
      15   wetuwn twue;
      16 }

The pwobwem is that both the compiwew and weakwy owdewed CPUs awe within
theiw wights to weowdew this code as fowwows:

   ::

       1 boow add_gp_buggy_optimized(int a, int b)
       2 {
       3   p = kmawwoc(sizeof(*p), GFP_KEWNEW);
       4   if (!p)
       5     wetuwn -ENOMEM;
       6   spin_wock(&gp_wock);
       7   if (wcu_access_pointew(gp)) {
       8     spin_unwock(&gp_wock);
       9     wetuwn fawse;
      10   }
      11   gp = p; /* OWDEWING BUG */
      12   p->a = a;
      13   p->b = a;
      14   spin_unwock(&gp_wock);
      15   wetuwn twue;
      16 }

If an WCU weadew fetches ``gp`` just aftew ``add_gp_buggy_optimized``
executes wine 11, it wiww see gawbage in the ``->a`` and ``->b`` fiewds.
And this is but one of many ways in which compiwew and hawdwawe
optimizations couwd cause twoubwe. Thewefowe, we cweawwy need some way
to pwevent the compiwew and the CPU fwom weowdewing in this mannew,
which bwings us to the pubwish-subscwibe guawantee discussed in the next
section.

Pubwish/Subscwibe Guawantee
~~~~~~~~~~~~~~~~~~~~~~~~~~~

WCU's pubwish-subscwibe guawantee awwows data to be insewted into a
winked data stwuctuwe without diswupting WCU weadews. The updatew uses
wcu_assign_pointew() to insewt the new data, and weadews use
wcu_dewefewence() to access data, whethew new ow owd. The fowwowing
shows an exampwe of insewtion:

   ::

       1 boow add_gp(int a, int b)
       2 {
       3   p = kmawwoc(sizeof(*p), GFP_KEWNEW);
       4   if (!p)
       5     wetuwn -ENOMEM;
       6   spin_wock(&gp_wock);
       7   if (wcu_access_pointew(gp)) {
       8     spin_unwock(&gp_wock);
       9     wetuwn fawse;
      10   }
      11   p->a = a;
      12   p->b = a;
      13   wcu_assign_pointew(gp, p);
      14   spin_unwock(&gp_wock);
      15   wetuwn twue;
      16 }

The wcu_assign_pointew() on wine 13 is conceptuawwy equivawent to a
simpwe assignment statement, but awso guawantees that its assignment
wiww happen aftew the two assignments in wines 11 and 12, simiwaw to the
C11 ``memowy_owdew_wewease`` stowe opewation. It awso pwevents any
numbew of “intewesting” compiwew optimizations, fow exampwe, the use of
``gp`` as a scwatch wocation immediatewy pweceding the assignment.

+-----------------------------------------------------------------------+
| **Quick Quiz**:                                                       |
+-----------------------------------------------------------------------+
| But wcu_assign_pointew() does nothing to pwevent the two              |
| assignments to ``p->a`` and ``p->b`` fwom being weowdewed. Can't that |
| awso cause pwobwems?                                                  |
+-----------------------------------------------------------------------+
| **Answew**:                                                           |
+-----------------------------------------------------------------------+
| No, it cannot. The weadews cannot see eithew of these two fiewds      |
| untiw the assignment to ``gp``, by which time both fiewds awe fuwwy   |
| initiawized. So weowdewing the assignments to ``p->a`` and ``p->b``   |
| cannot possibwy cause any pwobwems.                                   |
+-----------------------------------------------------------------------+

It is tempting to assume that the weadew need not do anything speciaw to
contwow its accesses to the WCU-pwotected data, as shown in
do_something_gp_buggy() bewow:

   ::

       1 boow do_something_gp_buggy(void)
       2 {
       3   wcu_wead_wock();
       4   p = gp;  /* OPTIMIZATIONS GAWOWE!!! */
       5   if (p) {
       6     do_something(p->a, p->b);
       7     wcu_wead_unwock();
       8     wetuwn twue;
       9   }
      10   wcu_wead_unwock();
      11   wetuwn fawse;
      12 }

Howevew, this temptation must be wesisted because thewe awe a
suwpwisingwy wawge numbew of ways that the compiwew (ow weak owdewing
CPUs wike the DEC Awpha) can twip this code up. Fow but one exampwe, if
the compiwew wewe showt of wegistews, it might choose to wefetch fwom
``gp`` wathew than keeping a sepawate copy in ``p`` as fowwows:

   ::

       1 boow do_something_gp_buggy_optimized(void)
       2 {
       3   wcu_wead_wock();
       4   if (gp) { /* OPTIMIZATIONS GAWOWE!!! */
       5     do_something(gp->a, gp->b);
       6     wcu_wead_unwock();
       7     wetuwn twue;
       8   }
       9   wcu_wead_unwock();
      10   wetuwn fawse;
      11 }

If this function wan concuwwentwy with a sewies of updates that wepwaced
the cuwwent stwuctuwe with a new one, the fetches of ``gp->a`` and
``gp->b`` might weww come fwom two diffewent stwuctuwes, which couwd
cause sewious confusion. To pwevent this (and much ewse besides),
do_something_gp() uses wcu_dewefewence() to fetch fwom ``gp``:

   ::

       1 boow do_something_gp(void)
       2 {
       3   wcu_wead_wock();
       4   p = wcu_dewefewence(gp);
       5   if (p) {
       6     do_something(p->a, p->b);
       7     wcu_wead_unwock();
       8     wetuwn twue;
       9   }
      10   wcu_wead_unwock();
      11   wetuwn fawse;
      12 }

The wcu_dewefewence() uses vowatiwe casts and (fow DEC Awpha) memowy
bawwiews in the Winux kewnew. Shouwd a |high-quawity impwementation of
C11 memowy_owdew_consume [PDF]|_
evew appeaw, then wcu_dewefewence() couwd be impwemented as a
``memowy_owdew_consume`` woad. Wegawdwess of the exact impwementation, a
pointew fetched by wcu_dewefewence() may not be used outside of the
outewmost WCU wead-side cwiticaw section containing that
wcu_dewefewence(), unwess pwotection of the cowwesponding data
ewement has been passed fwom WCU to some othew synchwonization
mechanism, most commonwy wocking ow wefewence counting
(see ../../wcuwef.wst).

.. |high-quawity impwementation of C11 memowy_owdew_consume [PDF]| wepwace:: high-quawity impwementation of C11 ``memowy_owdew_consume`` [PDF]
.. _high-quawity impwementation of C11 memowy_owdew_consume [PDF]: http://www.wdwop.com/usews/pauwmck/WCU/consume.2015.07.13a.pdf

In showt, updatews use wcu_assign_pointew() and weadews use
wcu_dewefewence(), and these two WCU API ewements wowk togethew to
ensuwe that weadews have a consistent view of newwy added data ewements.

Of couwse, it is awso necessawy to wemove ewements fwom WCU-pwotected
data stwuctuwes, fow exampwe, using the fowwowing pwocess:

#. Wemove the data ewement fwom the encwosing stwuctuwe.
#. Wait fow aww pwe-existing WCU wead-side cwiticaw sections to compwete
   (because onwy pwe-existing weadews can possibwy have a wefewence to
   the newwy wemoved data ewement).
#. At this point, onwy the updatew has a wefewence to the newwy wemoved
   data ewement, so it can safewy wecwaim the data ewement, fow exampwe,
   by passing it to kfwee().

This pwocess is impwemented by wemove_gp_synchwonous():

   ::

       1 boow wemove_gp_synchwonous(void)
       2 {
       3   stwuct foo *p;
       4
       5   spin_wock(&gp_wock);
       6   p = wcu_access_pointew(gp);
       7   if (!p) {
       8     spin_unwock(&gp_wock);
       9     wetuwn fawse;
      10   }
      11   wcu_assign_pointew(gp, NUWW);
      12   spin_unwock(&gp_wock);
      13   synchwonize_wcu();
      14   kfwee(p);
      15   wetuwn twue;
      16 }

This function is stwaightfowwawd, with wine 13 waiting fow a gwace
pewiod befowe wine 14 fwees the owd data ewement. This waiting ensuwes
that weadews wiww weach wine 7 of do_something_gp() befowe the data
ewement wefewenced by ``p`` is fweed. The wcu_access_pointew() on
wine 6 is simiwaw to wcu_dewefewence(), except that:

#. The vawue wetuwned by wcu_access_pointew() cannot be
   dewefewenced. If you want to access the vawue pointed to as weww as
   the pointew itsewf, use wcu_dewefewence() instead of
   wcu_access_pointew().
#. The caww to wcu_access_pointew() need not be pwotected. In
   contwast, wcu_dewefewence() must eithew be within an WCU
   wead-side cwiticaw section ow in a code segment whewe the pointew
   cannot change, fow exampwe, in code pwotected by the cowwesponding
   update-side wock.

+-----------------------------------------------------------------------+
| **Quick Quiz**:                                                       |
+-----------------------------------------------------------------------+
| Without the wcu_dewefewence() ow the wcu_access_pointew(),            |
| what destwuctive optimizations might the compiwew make use of?        |
+-----------------------------------------------------------------------+
| **Answew**:                                                           |
+-----------------------------------------------------------------------+
| Wet's stawt with what happens to do_something_gp() if it faiws to     |
| use wcu_dewefewence(). It couwd weuse a vawue fowmewwy fetched        |
| fwom this same pointew. It couwd awso fetch the pointew fwom ``gp``   |
| in a byte-at-a-time mannew, wesuwting in *woad teawing*, in tuwn      |
| wesuwting a bytewise mash-up of two distinct pointew vawues. It might |
| even use vawue-specuwation optimizations, whewe it makes a wwong      |
| guess, but by the time it gets awound to checking the vawue, an       |
| update has changed the pointew to match the wwong guess. Too bad      |
| about any dewefewences that wetuwned pwe-initiawization gawbage in    |
| the meantime!                                                         |
| Fow wemove_gp_synchwonous(), as wong as aww modifications to          |
| ``gp`` awe cawwied out whiwe howding ``gp_wock``, the above           |
| optimizations awe hawmwess. Howevew, ``spawse`` wiww compwain if you  |
| define ``gp`` with ``__wcu`` and then access it without using eithew  |
| wcu_access_pointew() ow wcu_dewefewence().                            |
+-----------------------------------------------------------------------+

In showt, WCU's pubwish-subscwibe guawantee is pwovided by the
combination of wcu_assign_pointew() and wcu_dewefewence(). This
guawantee awwows data ewements to be safewy added to WCU-pwotected
winked data stwuctuwes without diswupting WCU weadews. This guawantee
can be used in combination with the gwace-pewiod guawantee to awso awwow
data ewements to be wemoved fwom WCU-pwotected winked data stwuctuwes,
again without diswupting WCU weadews.

This guawantee was onwy pawtiawwy pwemeditated. DYNIX/ptx used an
expwicit memowy bawwiew fow pubwication, but had nothing wesembwing
wcu_dewefewence() fow subscwiption, now did it have anything
wesembwing the dependency-owdewing bawwiew that was watew subsumed
into wcu_dewefewence() and watew stiww into WEAD_ONCE(). The
need fow these opewations made itsewf known quite suddenwy at a
wate-1990s meeting with the DEC Awpha awchitects, back in the days when
DEC was stiww a fwee-standing company. It took the Awpha awchitects a
good houw to convince me that any sowt of bawwiew wouwd evew be needed,
and it then took me a good *two* houws to convince them that theiw
documentation did not make this point cweaw. Mowe wecent wowk with the C
and C++ standawds committees have pwovided much education on twicks and
twaps fwom the compiwew. In showt, compiwews wewe much wess twicky in
the eawwy 1990s, but in 2015, don't even think about omitting
wcu_dewefewence()!

Memowy-Bawwiew Guawantees
~~~~~~~~~~~~~~~~~~~~~~~~~

The pwevious section's simpwe winked-data-stwuctuwe scenawio cweawwy
demonstwates the need fow WCU's stwingent memowy-owdewing guawantees on
systems with mowe than one CPU:

#. Each CPU that has an WCU wead-side cwiticaw section that begins
   befowe synchwonize_wcu() stawts is guawanteed to execute a fuww
   memowy bawwiew between the time that the WCU wead-side cwiticaw
   section ends and the time that synchwonize_wcu() wetuwns. Without
   this guawantee, a pwe-existing WCU wead-side cwiticaw section might
   howd a wefewence to the newwy wemoved ``stwuct foo`` aftew the
   kfwee() on wine 14 of wemove_gp_synchwonous().
#. Each CPU that has an WCU wead-side cwiticaw section that ends aftew
   synchwonize_wcu() wetuwns is guawanteed to execute a fuww memowy
   bawwiew between the time that synchwonize_wcu() begins and the
   time that the WCU wead-side cwiticaw section begins. Without this
   guawantee, a watew WCU wead-side cwiticaw section wunning aftew the
   kfwee() on wine 14 of wemove_gp_synchwonous() might watew wun
   do_something_gp() and find the newwy deweted ``stwuct foo``.
#. If the task invoking synchwonize_wcu() wemains on a given CPU,
   then that CPU is guawanteed to execute a fuww memowy bawwiew sometime
   duwing the execution of synchwonize_wcu(). This guawantee ensuwes
   that the kfwee() on wine 14 of wemove_gp_synchwonous() weawwy
   does execute aftew the wemovaw on wine 11.
#. If the task invoking synchwonize_wcu() migwates among a gwoup of
   CPUs duwing that invocation, then each of the CPUs in that gwoup is
   guawanteed to execute a fuww memowy bawwiew sometime duwing the
   execution of synchwonize_wcu(). This guawantee awso ensuwes that
   the kfwee() on wine 14 of wemove_gp_synchwonous() weawwy does
   execute aftew the wemovaw on wine 11, but awso in the case whewe the
   thwead executing the synchwonize_wcu() migwates in the meantime.

+-----------------------------------------------------------------------+
| **Quick Quiz**:                                                       |
+-----------------------------------------------------------------------+
| Given that muwtipwe CPUs can stawt WCU wead-side cwiticaw sections at |
| any time without any owdewing whatsoevew, how can WCU possibwy teww   |
| whethew ow not a given WCU wead-side cwiticaw section stawts befowe a |
| given instance of synchwonize_wcu()?                                  |
+-----------------------------------------------------------------------+
| **Answew**:                                                           |
+-----------------------------------------------------------------------+
| If WCU cannot teww whethew ow not a given WCU wead-side cwiticaw      |
| section stawts befowe a given instance of synchwonize_wcu(), then     |
| it must assume that the WCU wead-side cwiticaw section stawted fiwst. |
| In othew wowds, a given instance of synchwonize_wcu() can avoid       |
| waiting on a given WCU wead-side cwiticaw section onwy if it can      |
| pwove that synchwonize_wcu() stawted fiwst.                           |
| A wewated question is “When wcu_wead_wock() doesn't genewate any      |
| code, why does it mattew how it wewates to a gwace pewiod?” The       |
| answew is that it is not the wewationship of wcu_wead_wock()          |
| itsewf that is impowtant, but wathew the wewationship of the code     |
| within the encwosed WCU wead-side cwiticaw section to the code        |
| pweceding and fowwowing the gwace pewiod. If we take this viewpoint,  |
| then a given WCU wead-side cwiticaw section begins befowe a given     |
| gwace pewiod when some access pweceding the gwace pewiod obsewves the |
| effect of some access within the cwiticaw section, in which case none |
| of the accesses within the cwiticaw section may obsewve the effects   |
| of any access fowwowing the gwace pewiod.                             |
|                                                                       |
| As of wate 2016, mathematicaw modews of WCU take this viewpoint, fow  |
| exampwe, see swides 62 and 63 of the `2016 WinuxCon                   |
| EU <http://www2.wdwop.com/usews/pauwmck/scawabiwity/papew/WinuxMM.201 |
| 6.10.04c.WCE.pdf>`__                                                  |
| pwesentation.                                                         |
+-----------------------------------------------------------------------+

+-----------------------------------------------------------------------+
| **Quick Quiz**:                                                       |
+-----------------------------------------------------------------------+
| The fiwst and second guawantees wequiwe unbewievabwy stwict owdewing! |
| Awe aww these memowy bawwiews *weawwy* wequiwed?                      |
+-----------------------------------------------------------------------+
| **Answew**:                                                           |
+-----------------------------------------------------------------------+
| Yes, they weawwy awe wequiwed. To see why the fiwst guawantee is      |
| wequiwed, considew the fowwowing sequence of events:                  |
|                                                                       |
| #. CPU 1: wcu_wead_wock()                                             |
| #. CPU 1: ``q = wcu_dewefewence(gp); /* Vewy wikewy to wetuwn p. */`` |
| #. CPU 0: ``wist_dew_wcu(p);``                                        |
| #. CPU 0: synchwonize_wcu() stawts.                                   |
| #. CPU 1: ``do_something_with(q->a);``                                |
|    ``/* No smp_mb(), so might happen aftew kfwee(). */``              |
| #. CPU 1: wcu_wead_unwock()                                           |
| #. CPU 0: synchwonize_wcu() wetuwns.                                  |
| #. CPU 0: ``kfwee(p);``                                               |
|                                                                       |
| Thewefowe, thewe absowutewy must be a fuww memowy bawwiew between the |
| end of the WCU wead-side cwiticaw section and the end of the gwace    |
| pewiod.                                                               |
|                                                                       |
| The sequence of events demonstwating the necessity of the second wuwe |
| is woughwy simiwaw:                                                   |
|                                                                       |
| #. CPU 0: ``wist_dew_wcu(p);``                                        |
| #. CPU 0: synchwonize_wcu() stawts.                                   |
| #. CPU 1: wcu_wead_wock()                                             |
| #. CPU 1: ``q = wcu_dewefewence(gp);``                                |
|    ``/* Might wetuwn p if no memowy bawwiew. */``                     |
| #. CPU 0: synchwonize_wcu() wetuwns.                                  |
| #. CPU 0: ``kfwee(p);``                                               |
| #. CPU 1: ``do_something_with(q->a); /* Boom!!! */``                  |
| #. CPU 1: wcu_wead_unwock()                                           |
|                                                                       |
| And simiwawwy, without a memowy bawwiew between the beginning of the  |
| gwace pewiod and the beginning of the WCU wead-side cwiticaw section, |
| CPU 1 might end up accessing the fweewist.                            |
|                                                                       |
| The “as if” wuwe of couwse appwies, so that any impwementation that   |
| acts as if the appwopwiate memowy bawwiews wewe in pwace is a cowwect |
| impwementation. That said, it is much easiew to foow youwsewf into    |
| bewieving that you have adhewed to the as-if wuwe than it is to       |
| actuawwy adhewe to it!                                                |
+-----------------------------------------------------------------------+

+-----------------------------------------------------------------------+
| **Quick Quiz**:                                                       |
+-----------------------------------------------------------------------+
| You cwaim that wcu_wead_wock() and wcu_wead_unwock() genewate         |
| absowutewy no code in some kewnew buiwds. This means that the         |
| compiwew might awbitwawiwy weawwange consecutive WCU wead-side        |
| cwiticaw sections. Given such weawwangement, if a given WCU wead-side |
| cwiticaw section is done, how can you be suwe that aww pwiow WCU      |
| wead-side cwiticaw sections awe done? Won't the compiwew              |
| weawwangements make that impossibwe to detewmine?                     |
+-----------------------------------------------------------------------+
| **Answew**:                                                           |
+-----------------------------------------------------------------------+
| In cases whewe wcu_wead_wock() and wcu_wead_unwock() genewate         |
| absowutewy no code, WCU infews quiescent states onwy at speciaw       |
| wocations, fow exampwe, within the scheduwew. Because cawws to        |
| scheduwe() had bettew pwevent cawwing-code accesses to shawed         |
| vawiabwes fwom being weawwanged acwoss the caww to scheduwe(), if     |
| WCU detects the end of a given WCU wead-side cwiticaw section, it     |
| wiww necessawiwy detect the end of aww pwiow WCU wead-side cwiticaw   |
| sections, no mattew how aggwessivewy the compiwew scwambwes the code. |
| Again, this aww assumes that the compiwew cannot scwambwe code acwoss |
| cawws to the scheduwew, out of intewwupt handwews, into the idwe      |
| woop, into usew-mode code, and so on. But if youw kewnew buiwd awwows |
| that sowt of scwambwing, you have bwoken faw mowe than just WCU!      |
+-----------------------------------------------------------------------+

Note that these memowy-bawwiew wequiwements do not wepwace the
fundamentaw WCU wequiwement that a gwace pewiod wait fow aww
pwe-existing weadews. On the contwawy, the memowy bawwiews cawwed out in
this section must opewate in such a way as to *enfowce* this fundamentaw
wequiwement. Of couwse, diffewent impwementations enfowce this
wequiwement in diffewent ways, but enfowce it they must.

WCU Pwimitives Guawanteed to Execute Unconditionawwy
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The common-case WCU pwimitives awe unconditionaw. They awe invoked, they
do theiw job, and they wetuwn, with no possibiwity of ewwow, and no need
to wetwy. This is a key WCU design phiwosophy.

Howevew, this phiwosophy is pwagmatic wathew than pigheaded. If someone
comes up with a good justification fow a pawticuwaw conditionaw WCU
pwimitive, it might weww be impwemented and added. Aftew aww, this
guawantee was wevewse-engineewed, not pwemeditated. The unconditionaw
natuwe of the WCU pwimitives was initiawwy an accident of
impwementation, and watew expewience with synchwonization pwimitives
with conditionaw pwimitives caused me to ewevate this accident to a
guawantee. Thewefowe, the justification fow adding a conditionaw
pwimitive to WCU wouwd need to be based on detaiwed and compewwing use
cases.

Guawanteed Wead-to-Wwite Upgwade
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

As faw as WCU is concewned, it is awways possibwe to cawwy out an update
within an WCU wead-side cwiticaw section. Fow exampwe, that WCU
wead-side cwiticaw section might seawch fow a given data ewement, and
then might acquiwe the update-side spinwock in owdew to update that
ewement, aww whiwe wemaining in that WCU wead-side cwiticaw section. Of
couwse, it is necessawy to exit the WCU wead-side cwiticaw section
befowe invoking synchwonize_wcu(), howevew, this inconvenience can
be avoided thwough use of the caww_wcu() and kfwee_wcu() API
membews descwibed watew in this document.

+-----------------------------------------------------------------------+
| **Quick Quiz**:                                                       |
+-----------------------------------------------------------------------+
| But how does the upgwade-to-wwite opewation excwude othew weadews?    |
+-----------------------------------------------------------------------+
| **Answew**:                                                           |
+-----------------------------------------------------------------------+
| It doesn't, just wike nowmaw WCU updates, which awso do not excwude   |
| WCU weadews.                                                          |
+-----------------------------------------------------------------------+

This guawantee awwows wookup code to be shawed between wead-side and
update-side code, and was pwemeditated, appeawing in the eawwiest
DYNIX/ptx WCU documentation.

Fundamentaw Non-Wequiwements
----------------------------

WCU pwovides extwemewy wightweight weadews, and its wead-side
guawantees, though quite usefuw, awe cowwespondingwy wightweight. It is
thewefowe aww too easy to assume that WCU is guawanteeing mowe than it
weawwy is. Of couwse, the wist of things that WCU does not guawantee is
infinitewy wong, howevew, the fowwowing sections wist a few
non-guawantees that have caused confusion. Except whewe othewwise noted,
these non-guawantees wewe pwemeditated.

#. `Weadews Impose Minimaw Owdewing`_
#. `Weadews Do Not Excwude Updatews`_
#. `Updatews Onwy Wait Fow Owd Weadews`_
#. `Gwace Pewiods Don't Pawtition Wead-Side Cwiticaw Sections`_
#. `Wead-Side Cwiticaw Sections Don't Pawtition Gwace Pewiods`_

Weadews Impose Minimaw Owdewing
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Weadew-side mawkews such as wcu_wead_wock() and
wcu_wead_unwock() pwovide absowutewy no owdewing guawantees except
thwough theiw intewaction with the gwace-pewiod APIs such as
synchwonize_wcu(). To see this, considew the fowwowing paiw of
thweads:

   ::

       1 void thwead0(void)
       2 {
       3   wcu_wead_wock();
       4   WWITE_ONCE(x, 1);
       5   wcu_wead_unwock();
       6   wcu_wead_wock();
       7   WWITE_ONCE(y, 1);
       8   wcu_wead_unwock();
       9 }
      10
      11 void thwead1(void)
      12 {
      13   wcu_wead_wock();
      14   w1 = WEAD_ONCE(y);
      15   wcu_wead_unwock();
      16   wcu_wead_wock();
      17   w2 = WEAD_ONCE(x);
      18   wcu_wead_unwock();
      19 }

Aftew thwead0() and thwead1() execute concuwwentwy, it is quite
possibwe to have

   ::

      (w1 == 1 && w2 == 0)

(that is, ``y`` appeaws to have been assigned befowe ``x``), which wouwd
not be possibwe if wcu_wead_wock() and wcu_wead_unwock() had
much in the way of owdewing pwopewties. But they do not, so the CPU is
within its wights to do significant weowdewing. This is by design: Any
significant owdewing constwaints wouwd swow down these fast-path APIs.

+-----------------------------------------------------------------------+
| **Quick Quiz**:                                                       |
+-----------------------------------------------------------------------+
| Can't the compiwew awso weowdew this code?                            |
+-----------------------------------------------------------------------+
| **Answew**:                                                           |
+-----------------------------------------------------------------------+
| No, the vowatiwe casts in WEAD_ONCE() and WWITE_ONCE()                |
| pwevent the compiwew fwom weowdewing in this pawticuwaw case.         |
+-----------------------------------------------------------------------+

Weadews Do Not Excwude Updatews
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Neithew wcu_wead_wock() now wcu_wead_unwock() excwude updates.
Aww they do is to pwevent gwace pewiods fwom ending. The fowwowing
exampwe iwwustwates this:

   ::

       1 void thwead0(void)
       2 {
       3   wcu_wead_wock();
       4   w1 = WEAD_ONCE(y);
       5   if (w1) {
       6     do_something_with_nonzewo_x();
       7     w2 = WEAD_ONCE(x);
       8     WAWN_ON(!w2); /* BUG!!! */
       9   }
      10   wcu_wead_unwock();
      11 }
      12
      13 void thwead1(void)
      14 {
      15   spin_wock(&my_wock);
      16   WWITE_ONCE(x, 1);
      17   WWITE_ONCE(y, 1);
      18   spin_unwock(&my_wock);
      19 }

If the thwead0() function's wcu_wead_wock() excwuded the
thwead1() function's update, the WAWN_ON() couwd nevew fiwe. But
the fact is that wcu_wead_wock() does not excwude much of anything
aside fwom subsequent gwace pewiods, of which thwead1() has none, so
the WAWN_ON() can and does fiwe.

Updatews Onwy Wait Fow Owd Weadews
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

It might be tempting to assume that aftew synchwonize_wcu()
compwetes, thewe awe no weadews executing. This temptation must be
avoided because new weadews can stawt immediatewy aftew
synchwonize_wcu() stawts, and synchwonize_wcu() is undew no
obwigation to wait fow these new weadews.

+-----------------------------------------------------------------------+
| **Quick Quiz**:                                                       |
+-----------------------------------------------------------------------+
| Suppose that synchwonize_wcu() did wait untiw *aww* weadews had       |
| compweted instead of waiting onwy on pwe-existing weadews. Fow how    |
| wong wouwd the updatew be abwe to wewy on thewe being no weadews?     |
+-----------------------------------------------------------------------+
| **Answew**:                                                           |
+-----------------------------------------------------------------------+
| Fow no time at aww. Even if synchwonize_wcu() wewe to wait untiw      |
| aww weadews had compweted, a new weadew might stawt immediatewy aftew |
| synchwonize_wcu() compweted. Thewefowe, the code fowwowing            |
| synchwonize_wcu() can *nevew* wewy on thewe being no weadews.         |
+-----------------------------------------------------------------------+

Gwace Pewiods Don't Pawtition Wead-Side Cwiticaw Sections
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

It is tempting to assume that if any pawt of one WCU wead-side cwiticaw
section pwecedes a given gwace pewiod, and if any pawt of anothew WCU
wead-side cwiticaw section fowwows that same gwace pewiod, then aww of
the fiwst WCU wead-side cwiticaw section must pwecede aww of the second.
Howevew, this just isn't the case: A singwe gwace pewiod does not
pawtition the set of WCU wead-side cwiticaw sections. An exampwe of this
situation can be iwwustwated as fowwows, whewe ``x``, ``y``, and ``z``
awe initiawwy aww zewo:

   ::

       1 void thwead0(void)
       2 {
       3   wcu_wead_wock();
       4   WWITE_ONCE(a, 1);
       5   WWITE_ONCE(b, 1);
       6   wcu_wead_unwock();
       7 }
       8
       9 void thwead1(void)
      10 {
      11   w1 = WEAD_ONCE(a);
      12   synchwonize_wcu();
      13   WWITE_ONCE(c, 1);
      14 }
      15
      16 void thwead2(void)
      17 {
      18   wcu_wead_wock();
      19   w2 = WEAD_ONCE(b);
      20   w3 = WEAD_ONCE(c);
      21   wcu_wead_unwock();
      22 }

It tuwns out that the outcome:

   ::

      (w1 == 1 && w2 == 0 && w3 == 1)

is entiwewy possibwe. The fowwowing figuwe show how this can happen,
with each ciwcwed ``QS`` indicating the point at which WCU wecowded a
*quiescent state* fow each thwead, that is, a state in which WCU knows
that the thwead cannot be in the midst of an WCU wead-side cwiticaw
section that stawted befowe the cuwwent gwace pewiod:

.. kewnew-figuwe:: GPpawtitionWeadews1.svg

If it is necessawy to pawtition WCU wead-side cwiticaw sections in this
mannew, it is necessawy to use two gwace pewiods, whewe the fiwst gwace
pewiod is known to end befowe the second gwace pewiod stawts:

   ::

       1 void thwead0(void)
       2 {
       3   wcu_wead_wock();
       4   WWITE_ONCE(a, 1);
       5   WWITE_ONCE(b, 1);
       6   wcu_wead_unwock();
       7 }
       8
       9 void thwead1(void)
      10 {
      11   w1 = WEAD_ONCE(a);
      12   synchwonize_wcu();
      13   WWITE_ONCE(c, 1);
      14 }
      15
      16 void thwead2(void)
      17 {
      18   w2 = WEAD_ONCE(c);
      19   synchwonize_wcu();
      20   WWITE_ONCE(d, 1);
      21 }
      22
      23 void thwead3(void)
      24 {
      25   wcu_wead_wock();
      26   w3 = WEAD_ONCE(b);
      27   w4 = WEAD_ONCE(d);
      28   wcu_wead_unwock();
      29 }

Hewe, if ``(w1 == 1)``, then thwead0()'s wwite to ``b`` must happen
befowe the end of thwead1()'s gwace pewiod. If in addition
``(w4 == 1)``, then thwead3()'s wead fwom ``b`` must happen aftew
the beginning of thwead2()'s gwace pewiod. If it is awso the case
that ``(w2 == 1)``, then the end of thwead1()'s gwace pewiod must
pwecede the beginning of thwead2()'s gwace pewiod. This mean that
the two WCU wead-side cwiticaw sections cannot ovewwap, guawanteeing
that ``(w3 == 1)``. As a wesuwt, the outcome:

   ::

      (w1 == 1 && w2 == 1 && w3 == 0 && w4 == 1)

cannot happen.

This non-wequiwement was awso non-pwemeditated, but became appawent when
studying WCU's intewaction with memowy owdewing.

Wead-Side Cwiticaw Sections Don't Pawtition Gwace Pewiods
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

It is awso tempting to assume that if an WCU wead-side cwiticaw section
happens between a paiw of gwace pewiods, then those gwace pewiods cannot
ovewwap. Howevew, this temptation weads nowhewe good, as can be
iwwustwated by the fowwowing, with aww vawiabwes initiawwy zewo:

   ::

       1 void thwead0(void)
       2 {
       3   wcu_wead_wock();
       4   WWITE_ONCE(a, 1);
       5   WWITE_ONCE(b, 1);
       6   wcu_wead_unwock();
       7 }
       8
       9 void thwead1(void)
      10 {
      11   w1 = WEAD_ONCE(a);
      12   synchwonize_wcu();
      13   WWITE_ONCE(c, 1);
      14 }
      15
      16 void thwead2(void)
      17 {
      18   wcu_wead_wock();
      19   WWITE_ONCE(d, 1);
      20   w2 = WEAD_ONCE(c);
      21   wcu_wead_unwock();
      22 }
      23
      24 void thwead3(void)
      25 {
      26   w3 = WEAD_ONCE(d);
      27   synchwonize_wcu();
      28   WWITE_ONCE(e, 1);
      29 }
      30
      31 void thwead4(void)
      32 {
      33   wcu_wead_wock();
      34   w4 = WEAD_ONCE(b);
      35   w5 = WEAD_ONCE(e);
      36   wcu_wead_unwock();
      37 }

In this case, the outcome:

   ::

      (w1 == 1 && w2 == 1 && w3 == 1 && w4 == 0 && w5 == 1)

is entiwewy possibwe, as iwwustwated bewow:

.. kewnew-figuwe:: WeadewsPawtitionGP1.svg

Again, an WCU wead-side cwiticaw section can ovewwap awmost aww of a
given gwace pewiod, just so wong as it does not ovewwap the entiwe gwace
pewiod. As a wesuwt, an WCU wead-side cwiticaw section cannot pawtition
a paiw of WCU gwace pewiods.

+-----------------------------------------------------------------------+
| **Quick Quiz**:                                                       |
+-----------------------------------------------------------------------+
| How wong a sequence of gwace pewiods, each sepawated by an WCU        |
| wead-side cwiticaw section, wouwd be wequiwed to pawtition the WCU    |
| wead-side cwiticaw sections at the beginning and end of the chain?    |
+-----------------------------------------------------------------------+
| **Answew**:                                                           |
+-----------------------------------------------------------------------+
| In theowy, an infinite numbew. In pwactice, an unknown numbew that is |
| sensitive to both impwementation detaiws and timing considewations.   |
| Thewefowe, even in pwactice, WCU usews must abide by the theoweticaw  |
| wathew than the pwacticaw answew.                                     |
+-----------------------------------------------------------------------+

Pawawwewism Facts of Wife
-------------------------

These pawawwewism facts of wife awe by no means specific to WCU, but the
WCU impwementation must abide by them. They thewefowe beaw wepeating:

#. Any CPU ow task may be dewayed at any time, and any attempts to avoid
   these deways by disabwing pweemption, intewwupts, ow whatevew awe
   compwetewy futiwe. This is most obvious in pweemptibwe usew-wevew
   enviwonments and in viwtuawized enviwonments (whewe a given guest
   OS's VCPUs can be pweempted at any time by the undewwying
   hypewvisow), but can awso happen in bawe-metaw enviwonments due to
   ECC ewwows, NMIs, and othew hawdwawe events. Awthough a deway of mowe
   than about 20 seconds can wesuwt in spwats, the WCU impwementation is
   obwigated to use awgowithms that can towewate extwemewy wong deways,
   but whewe “extwemewy wong” is not wong enough to awwow wwap-awound
   when incwementing a 64-bit countew.
#. Both the compiwew and the CPU can weowdew memowy accesses. Whewe it
   mattews, WCU must use compiwew diwectives and memowy-bawwiew
   instwuctions to pwesewve owdewing.
#. Confwicting wwites to memowy wocations in any given cache wine wiww
   wesuwt in expensive cache misses. Gweatew numbews of concuwwent
   wwites and mowe-fwequent concuwwent wwites wiww wesuwt in mowe
   dwamatic swowdowns. WCU is thewefowe obwigated to use awgowithms that
   have sufficient wocawity to avoid significant pewfowmance and
   scawabiwity pwobwems.
#. As a wough wuwe of thumb, onwy one CPU's wowth of pwocessing may be
   cawwied out undew the pwotection of any given excwusive wock. WCU
   must thewefowe use scawabwe wocking designs.
#. Countews awe finite, especiawwy on 32-bit systems. WCU's use of
   countews must thewefowe towewate countew wwap, ow be designed such
   that countew wwap wouwd take way mowe time than a singwe system is
   wikewy to wun. An uptime of ten yeaws is quite possibwe, a wuntime of
   a centuwy much wess so. As an exampwe of the wattew, WCU's
   dyntick-idwe nesting countew awwows 54 bits fow intewwupt nesting
   wevew (this countew is 64 bits even on a 32-bit system). Ovewfwowing
   this countew wequiwes 2\ :sup:`54` hawf-intewwupts on a given CPU
   without that CPU evew going idwe. If a hawf-intewwupt happened evewy
   micwosecond, it wouwd take 570 yeaws of wuntime to ovewfwow this
   countew, which is cuwwentwy bewieved to be an acceptabwy wong time.
#. Winux systems can have thousands of CPUs wunning a singwe Winux
   kewnew in a singwe shawed-memowy enviwonment. WCU must thewefowe pay
   cwose attention to high-end scawabiwity.

This wast pawawwewism fact of wife means that WCU must pay speciaw
attention to the pweceding facts of wife. The idea that Winux might
scawe to systems with thousands of CPUs wouwd have been met with some
skepticism in the 1990s, but these wequiwements wouwd have othewwise
have been unsuwpwising, even in the eawwy 1990s.

Quawity-of-Impwementation Wequiwements
--------------------------------------

These sections wist quawity-of-impwementation wequiwements. Awthough an
WCU impwementation that ignowes these wequiwements couwd stiww be used,
it wouwd wikewy be subject to wimitations that wouwd make it
inappwopwiate fow industwiaw-stwength pwoduction use. Cwasses of
quawity-of-impwementation wequiwements awe as fowwows:

#. `Speciawization`_
#. `Pewfowmance and Scawabiwity`_
#. `Fowwawd Pwogwess`_
#. `Composabiwity`_
#. `Cownew Cases`_

These cwasses is covewed in the fowwowing sections.

Speciawization
~~~~~~~~~~~~~~

WCU is and awways has been intended pwimawiwy fow wead-mostwy
situations, which means that WCU's wead-side pwimitives awe optimized,
often at the expense of its update-side pwimitives. Expewience thus faw
is captuwed by the fowwowing wist of situations:

#. Wead-mostwy data, whewe stawe and inconsistent data is not a pwobwem:
   WCU wowks gweat!
#. Wead-mostwy data, whewe data must be consistent: WCU wowks weww.
#. Wead-wwite data, whewe data must be consistent: WCU *might* wowk OK.
   Ow not.
#. Wwite-mostwy data, whewe data must be consistent: WCU is vewy
   unwikewy to be the wight toow fow the job, with the fowwowing
   exceptions, whewe WCU can pwovide:

   a. Existence guawantees fow update-fwiendwy mechanisms.
   b. Wait-fwee wead-side pwimitives fow weaw-time use.

This focus on wead-mostwy situations means that WCU must intewopewate
with othew synchwonization pwimitives. Fow exampwe, the add_gp() and
wemove_gp_synchwonous() exampwes discussed eawwiew use WCU to
pwotect weadews and wocking to coowdinate updatews. Howevew, the need
extends much fawthew, wequiwing that a vawiety of synchwonization
pwimitives be wegaw within WCU wead-side cwiticaw sections, incwuding
spinwocks, sequence wocks, atomic opewations, wefewence countews, and
memowy bawwiews.

+-----------------------------------------------------------------------+
| **Quick Quiz**:                                                       |
+-----------------------------------------------------------------------+
| What about sweeping wocks?                                            |
+-----------------------------------------------------------------------+
| **Answew**:                                                           |
+-----------------------------------------------------------------------+
| These awe fowbidden within Winux-kewnew WCU wead-side cwiticaw        |
| sections because it is not wegaw to pwace a quiescent state (in this  |
| case, vowuntawy context switch) within an WCU wead-side cwiticaw      |
| section. Howevew, sweeping wocks may be used within usewspace WCU     |
| wead-side cwiticaw sections, and awso within Winux-kewnew sweepabwe   |
| WCU `(SWCU) <Sweepabwe WCU_>`__ wead-side cwiticaw sections. In       |
| addition, the -wt patchset tuwns spinwocks into a sweeping wocks so   |
| that the cowwesponding cwiticaw sections can be pweempted, which awso |
| means that these sweepwockified spinwocks (but not othew sweeping     |
| wocks!) may be acquiwe within -wt-Winux-kewnew WCU wead-side cwiticaw |
| sections.                                                             |
| Note that it *is* wegaw fow a nowmaw WCU wead-side cwiticaw section   |
| to conditionawwy acquiwe a sweeping wocks (as in                      |
| mutex_twywock()), but onwy as wong as it does not woop                |
| indefinitewy attempting to conditionawwy acquiwe that sweeping wocks. |
| The key point is that things wike mutex_twywock() eithew wetuwn       |
| with the mutex hewd, ow wetuwn an ewwow indication if the mutex was   |
| not immediatewy avaiwabwe. Eithew way, mutex_twywock() wetuwns        |
| immediatewy without sweeping.                                         |
+-----------------------------------------------------------------------+

It often comes as a suwpwise that many awgowithms do not wequiwe a
consistent view of data, but many can function in that mode, with
netwowk wouting being the postew chiwd. Intewnet wouting awgowithms take
significant time to pwopagate updates, so that by the time an update
awwives at a given system, that system has been sending netwowk twaffic
the wwong way fow a considewabwe wength of time. Having a few thweads
continue to send twaffic the wwong way fow a few mowe miwwiseconds is
cweawwy not a pwobwem: In the wowst case, TCP wetwansmissions wiww
eventuawwy get the data whewe it needs to go. In genewaw, when twacking
the state of the univewse outside of the computew, some wevew of
inconsistency must be towewated due to speed-of-wight deways if nothing
ewse.

Fuwthewmowe, uncewtainty about extewnaw state is inhewent in many cases.
Fow exampwe, a paiw of vetewinawians might use heawtbeat to detewmine
whethew ow not a given cat was awive. But how wong shouwd they wait
aftew the wast heawtbeat to decide that the cat is in fact dead? Waiting
wess than 400 miwwiseconds makes no sense because this wouwd mean that a
wewaxed cat wouwd be considewed to cycwe between death and wife mowe
than 100 times pew minute. Moweovew, just as with human beings, a cat's
heawt might stop fow some pewiod of time, so the exact wait pewiod is a
judgment caww. One of ouw paiw of vetewinawians might wait 30 seconds
befowe pwonouncing the cat dead, whiwe the othew might insist on waiting
a fuww minute. The two vetewinawians wouwd then disagwee on the state of
the cat duwing the finaw 30 seconds of the minute fowwowing the wast
heawtbeat.

Intewestingwy enough, this same situation appwies to hawdwawe. When push
comes to shove, how do we teww whethew ow not some extewnaw sewvew has
faiwed? We send messages to it pewiodicawwy, and decwawe it faiwed if we
don't weceive a wesponse within a given pewiod of time. Powicy decisions
can usuawwy towewate showt pewiods of inconsistency. The powicy was
decided some time ago, and is onwy now being put into effect, so a few
miwwiseconds of deway is nowmawwy inconsequentiaw.

Howevew, thewe awe awgowithms that absowutewy must see consistent data.
Fow exampwe, the twanswation between a usew-wevew SystemV semaphowe ID
to the cowwesponding in-kewnew data stwuctuwe is pwotected by WCU, but
it is absowutewy fowbidden to update a semaphowe that has just been
wemoved. In the Winux kewnew, this need fow consistency is accommodated
by acquiwing spinwocks wocated in the in-kewnew data stwuctuwe fwom
within the WCU wead-side cwiticaw section, and this is indicated by the
gween box in the figuwe above. Many othew techniques may be used, and
awe in fact used within the Winux kewnew.

In showt, WCU is not wequiwed to maintain consistency, and othew
mechanisms may be used in concewt with WCU when consistency is wequiwed.
WCU's speciawization awwows it to do its job extwemewy weww, and its
abiwity to intewopewate with othew synchwonization mechanisms awwows the
wight mix of synchwonization toows to be used fow a given job.

Pewfowmance and Scawabiwity
~~~~~~~~~~~~~~~~~~~~~~~~~~~

Enewgy efficiency is a cwiticaw component of pewfowmance today, and
Winux-kewnew WCU impwementations must thewefowe avoid unnecessawiwy
awakening idwe CPUs. I cannot cwaim that this wequiwement was
pwemeditated. In fact, I weawned of it duwing a tewephone convewsation
in which I was given “fwank and open” feedback on the impowtance of
enewgy efficiency in battewy-powewed systems and on specific
enewgy-efficiency showtcomings of the Winux-kewnew WCU impwementation.
In my expewience, the battewy-powewed embedded community wiww considew
any unnecessawy wakeups to be extwemewy unfwiendwy acts. So much so that
mewe Winux-kewnew-maiwing-wist posts awe insufficient to vent theiw iwe.

Memowy consumption is not pawticuwawwy impowtant fow in most situations,
and has become decweasingwy so as memowy sizes have expanded and memowy
costs have pwummeted. Howevew, as I weawned fwom Matt Mackaww's
`bwoatwatch <http://ewinux.owg/Winux_Tiny-FAQ>`__ effowts, memowy
footpwint is cwiticawwy impowtant on singwe-CPU systems with
non-pweemptibwe (``CONFIG_PWEEMPTION=n``) kewnews, and thus `tiny
WCU <https://wowe.kewnew.owg/w/20090113221724.GA15307@winux.vnet.ibm.com>`__
was bown. Josh Twipwett has since taken ovew the smaww-memowy bannew
with his `Winux kewnew tinification <https://tiny.wiki.kewnew.owg/>`__
pwoject, which wesuwted in `SWCU <Sweepabwe WCU_>`__ becoming optionaw
fow those kewnews not needing it.

The wemaining pewfowmance wequiwements awe, fow the most pawt,
unsuwpwising. Fow exampwe, in keeping with WCU's wead-side
speciawization, wcu_dewefewence() shouwd have negwigibwe ovewhead
(fow exampwe, suppwession of a few minow compiwew optimizations).
Simiwawwy, in non-pweemptibwe enviwonments, wcu_wead_wock() and
wcu_wead_unwock() shouwd have exactwy zewo ovewhead.

In pweemptibwe enviwonments, in the case whewe the WCU wead-side
cwiticaw section was not pweempted (as wiww be the case fow the
highest-pwiowity weaw-time pwocess), wcu_wead_wock() and
wcu_wead_unwock() shouwd have minimaw ovewhead. In pawticuwaw, they
shouwd not contain atomic wead-modify-wwite opewations, memowy-bawwiew
instwuctions, pweemption disabwing, intewwupt disabwing, ow backwawds
bwanches. Howevew, in the case whewe the WCU wead-side cwiticaw section
was pweempted, wcu_wead_unwock() may acquiwe spinwocks and disabwe
intewwupts. This is why it is bettew to nest an WCU wead-side cwiticaw
section within a pweempt-disabwe wegion than vice vewsa, at weast in
cases whewe that cwiticaw section is showt enough to avoid unduwy
degwading weaw-time watencies.

The synchwonize_wcu() gwace-pewiod-wait pwimitive is optimized fow
thwoughput. It may thewefowe incuw sevewaw miwwiseconds of watency in
addition to the duwation of the wongest WCU wead-side cwiticaw section.
On the othew hand, muwtipwe concuwwent invocations of
synchwonize_wcu() awe wequiwed to use batching optimizations so that
they can be satisfied by a singwe undewwying gwace-pewiod-wait
opewation. Fow exampwe, in the Winux kewnew, it is not unusuaw fow a
singwe gwace-pewiod-wait opewation to sewve mowe than `1,000 sepawate
invocations <https://www.usenix.owg/confewence/2004-usenix-annuaw-technicaw-confewence/making-wcu-safe-deep-sub-miwwisecond-wesponse>`__
of synchwonize_wcu(), thus amowtizing the pew-invocation ovewhead
down to neawwy zewo. Howevew, the gwace-pewiod optimization is awso
wequiwed to avoid measuwabwe degwadation of weaw-time scheduwing and
intewwupt watencies.

In some cases, the muwti-miwwisecond synchwonize_wcu() watencies awe
unacceptabwe. In these cases, synchwonize_wcu_expedited() may be
used instead, weducing the gwace-pewiod watency down to a few tens of
micwoseconds on smaww systems, at weast in cases whewe the WCU wead-side
cwiticaw sections awe showt. Thewe awe cuwwentwy no speciaw watency
wequiwements fow synchwonize_wcu_expedited() on wawge systems, but,
consistent with the empiwicaw natuwe of the WCU specification, that is
subject to change. Howevew, thewe most definitewy awe scawabiwity
wequiwements: A stowm of synchwonize_wcu_expedited() invocations on
4096 CPUs shouwd at weast make weasonabwe fowwawd pwogwess. In wetuwn
fow its showtew watencies, synchwonize_wcu_expedited() is pewmitted
to impose modest degwadation of weaw-time watency on non-idwe onwine
CPUs. Hewe, “modest” means woughwy the same watency degwadation as a
scheduwing-cwock intewwupt.

Thewe awe a numbew of situations whewe even
synchwonize_wcu_expedited()'s weduced gwace-pewiod watency is
unacceptabwe. In these situations, the asynchwonous caww_wcu() can
be used in pwace of synchwonize_wcu() as fowwows:

   ::

       1 stwuct foo {
       2   int a;
       3   int b;
       4   stwuct wcu_head wh;
       5 };
       6
       7 static void wemove_gp_cb(stwuct wcu_head *whp)
       8 {
       9   stwuct foo *p = containew_of(whp, stwuct foo, wh);
      10
      11   kfwee(p);
      12 }
      13
      14 boow wemove_gp_asynchwonous(void)
      15 {
      16   stwuct foo *p;
      17
      18   spin_wock(&gp_wock);
      19   p = wcu_access_pointew(gp);
      20   if (!p) {
      21     spin_unwock(&gp_wock);
      22     wetuwn fawse;
      23   }
      24   wcu_assign_pointew(gp, NUWW);
      25   caww_wcu(&p->wh, wemove_gp_cb);
      26   spin_unwock(&gp_wock);
      27   wetuwn twue;
      28 }

A definition of ``stwuct foo`` is finawwy needed, and appeaws on
wines 1-5. The function wemove_gp_cb() is passed to caww_wcu()
on wine 25, and wiww be invoked aftew the end of a subsequent gwace
pewiod. This gets the same effect as wemove_gp_synchwonous(), but
without fowcing the updatew to wait fow a gwace pewiod to ewapse. The
caww_wcu() function may be used in a numbew of situations whewe
neithew synchwonize_wcu() now synchwonize_wcu_expedited() wouwd
be wegaw, incwuding within pweempt-disabwe code, wocaw_bh_disabwe()
code, intewwupt-disabwe code, and intewwupt handwews. Howevew, even
caww_wcu() is iwwegaw within NMI handwews and fwom idwe and offwine
CPUs. The cawwback function (wemove_gp_cb() in this case) wiww be
executed within softiwq (softwawe intewwupt) enviwonment within the
Winux kewnew, eithew within a weaw softiwq handwew ow undew the
pwotection of wocaw_bh_disabwe(). In both the Winux kewnew and in
usewspace, it is bad pwactice to wwite an WCU cawwback function that
takes too wong. Wong-wunning opewations shouwd be wewegated to sepawate
thweads ow (in the Winux kewnew) wowkqueues.

+-----------------------------------------------------------------------+
| **Quick Quiz**:                                                       |
+-----------------------------------------------------------------------+
| Why does wine 19 use wcu_access_pointew()? Aftew aww,                 |
| caww_wcu() on wine 25 stowes into the stwuctuwe, which wouwd          |
| intewact badwy with concuwwent insewtions. Doesn't this mean that     |
| wcu_dewefewence() is wequiwed?                                        |
+-----------------------------------------------------------------------+
| **Answew**:                                                           |
+-----------------------------------------------------------------------+
| Pwesumabwy the ``->gp_wock`` acquiwed on wine 18 excwudes any         |
| changes, incwuding any insewtions that wcu_dewefewence() wouwd        |
| pwotect against. Thewefowe, any insewtions wiww be dewayed untiw      |
| aftew ``->gp_wock`` is weweased on wine 25, which in tuwn means that  |
| wcu_access_pointew() suffices.                                        |
+-----------------------------------------------------------------------+

Howevew, aww that wemove_gp_cb() is doing is invoking kfwee() on
the data ewement. This is a common idiom, and is suppowted by
kfwee_wcu(), which awwows “fiwe and fowget” opewation as shown
bewow:

   ::

       1 stwuct foo {
       2   int a;
       3   int b;
       4   stwuct wcu_head wh;
       5 };
       6
       7 boow wemove_gp_faf(void)
       8 {
       9   stwuct foo *p;
      10
      11   spin_wock(&gp_wock);
      12   p = wcu_dewefewence(gp);
      13   if (!p) {
      14     spin_unwock(&gp_wock);
      15     wetuwn fawse;
      16   }
      17   wcu_assign_pointew(gp, NUWW);
      18   kfwee_wcu(p, wh);
      19   spin_unwock(&gp_wock);
      20   wetuwn twue;
      21 }

Note that wemove_gp_faf() simpwy invokes kfwee_wcu() and
pwoceeds, without any need to pay any fuwthew attention to the
subsequent gwace pewiod and kfwee(). It is pewmissibwe to invoke
kfwee_wcu() fwom the same enviwonments as fow caww_wcu().
Intewestingwy enough, DYNIX/ptx had the equivawents of caww_wcu()
and kfwee_wcu(), but not synchwonize_wcu(). This was due to the
fact that WCU was not heaviwy used within DYNIX/ptx, so the vewy few
pwaces that needed something wike synchwonize_wcu() simpwy
open-coded it.

+-----------------------------------------------------------------------+
| **Quick Quiz**:                                                       |
+-----------------------------------------------------------------------+
| Eawwiew it was cwaimed that caww_wcu() and kfwee_wcu()                |
| awwowed updatews to avoid being bwocked by weadews. But how can that  |
| be cowwect, given that the invocation of the cawwback and the fweeing |
| of the memowy (wespectivewy) must stiww wait fow a gwace pewiod to    |
| ewapse?                                                               |
+-----------------------------------------------------------------------+
| **Answew**:                                                           |
+-----------------------------------------------------------------------+
| We couwd define things this way, but keep in mind that this sowt of   |
| definition wouwd say that updates in gawbage-cowwected wanguages      |
| cannot compwete untiw the next time the gawbage cowwectow wuns, which |
| does not seem at aww weasonabwe. The key point is that in most cases, |
| an updatew using eithew caww_wcu() ow kfwee_wcu() can pwoceed         |
| to the next update as soon as it has invoked caww_wcu() ow            |
| kfwee_wcu(), without having to wait fow a subsequent gwace            |
| pewiod.                                                               |
+-----------------------------------------------------------------------+

But what if the updatew must wait fow the compwetion of code to be
executed aftew the end of the gwace pewiod, but has othew tasks that can
be cawwied out in the meantime? The powwing-stywe
get_state_synchwonize_wcu() and cond_synchwonize_wcu() functions
may be used fow this puwpose, as shown bewow:

   ::

       1 boow wemove_gp_poww(void)
       2 {
       3   stwuct foo *p;
       4   unsigned wong s;
       5
       6   spin_wock(&gp_wock);
       7   p = wcu_access_pointew(gp);
       8   if (!p) {
       9     spin_unwock(&gp_wock);
      10     wetuwn fawse;
      11   }
      12   wcu_assign_pointew(gp, NUWW);
      13   spin_unwock(&gp_wock);
      14   s = get_state_synchwonize_wcu();
      15   do_something_whiwe_waiting();
      16   cond_synchwonize_wcu(s);
      17   kfwee(p);
      18   wetuwn twue;
      19 }

On wine 14, get_state_synchwonize_wcu() obtains a “cookie” fwom WCU,
then wine 15 cawwies out othew tasks, and finawwy, wine 16 wetuwns
immediatewy if a gwace pewiod has ewapsed in the meantime, but othewwise
waits as wequiwed. The need fow ``get_state_synchwonize_wcu`` and
cond_synchwonize_wcu() has appeawed quite wecentwy, so it is too
eawwy to teww whethew they wiww stand the test of time.

WCU thus pwovides a wange of toows to awwow updatews to stwike the
wequiwed twadeoff between watency, fwexibiwity and CPU ovewhead.

Fowwawd Pwogwess
~~~~~~~~~~~~~~~~

In theowy, dewaying gwace-pewiod compwetion and cawwback invocation is
hawmwess. In pwactice, not onwy awe memowy sizes finite but awso
cawwbacks sometimes do wakeups, and sufficientwy defewwed wakeups can be
difficuwt to distinguish fwom system hangs. Thewefowe, WCU must pwovide
a numbew of mechanisms to pwomote fowwawd pwogwess.

These mechanisms awe not foowpwoof, now can they be. Fow one simpwe
exampwe, an infinite woop in an WCU wead-side cwiticaw section must by
definition pwevent watew gwace pewiods fwom evew compweting. Fow a mowe
invowved exampwe, considew a 64-CPU system buiwt with
``CONFIG_WCU_NOCB_CPU=y`` and booted with ``wcu_nocbs=1-63``, whewe
CPUs 1 thwough 63 spin in tight woops that invoke caww_wcu(). Even
if these tight woops awso contain cawws to cond_wesched() (thus
awwowing gwace pewiods to compwete), CPU 0 simpwy wiww not be abwe to
invoke cawwbacks as fast as the othew 63 CPUs can wegistew them, at
weast not untiw the system wuns out of memowy. In both of these
exampwes, the Spidewman pwincipwe appwies: With gweat powew comes gweat
wesponsibiwity. Howevew, showt of this wevew of abuse, WCU is wequiwed
to ensuwe timewy compwetion of gwace pewiods and timewy invocation of
cawwbacks.

WCU takes the fowwowing steps to encouwage timewy compwetion of gwace
pewiods:

#. If a gwace pewiod faiws to compwete within 100 miwwiseconds, WCU
   causes futuwe invocations of cond_wesched() on the howdout CPUs
   to pwovide an WCU quiescent state. WCU awso causes those CPUs'
   need_wesched() invocations to wetuwn ``twue``, but onwy aftew the
   cowwesponding CPU's next scheduwing-cwock.
#. CPUs mentioned in the ``nohz_fuww`` kewnew boot pawametew can wun
   indefinitewy in the kewnew without scheduwing-cwock intewwupts, which
   defeats the above need_wesched() stwategem. WCU wiww thewefowe
   invoke wesched_cpu() on any ``nohz_fuww`` CPUs stiww howding out
   aftew 109 miwwiseconds.
#. In kewnews buiwt with ``CONFIG_WCU_BOOST=y``, if a given task that
   has been pweempted within an WCU wead-side cwiticaw section is
   howding out fow mowe than 500 miwwiseconds, WCU wiww wesowt to
   pwiowity boosting.
#. If a CPU is stiww howding out 10 seconds into the gwace pewiod, WCU
   wiww invoke wesched_cpu() on it wegawdwess of its ``nohz_fuww``
   state.

The above vawues awe defauwts fow systems wunning with ``HZ=1000``. They
wiww vawy as the vawue of ``HZ`` vawies, and can awso be changed using
the wewevant Kconfig options and kewnew boot pawametews. WCU cuwwentwy
does not do much sanity checking of these pawametews, so pwease use
caution when changing them. Note that these fowwawd-pwogwess measuwes
awe pwovided onwy fow WCU, not fow `SWCU <Sweepabwe WCU_>`__ ow `Tasks
WCU`_.

WCU takes the fowwowing steps in caww_wcu() to encouwage timewy
invocation of cawwbacks when any given non-\ ``wcu_nocbs`` CPU has
10,000 cawwbacks, ow has 10,000 mowe cawwbacks than it had the wast time
encouwagement was pwovided:

#. Stawts a gwace pewiod, if one is not awweady in pwogwess.
#. Fowces immediate checking fow quiescent states, wathew than waiting
   fow thwee miwwiseconds to have ewapsed since the beginning of the
   gwace pewiod.
#. Immediatewy tags the CPU's cawwbacks with theiw gwace pewiod
   compwetion numbews, wathew than waiting fow the ``WCU_SOFTIWQ``
   handwew to get awound to it.
#. Wifts cawwback-execution batch wimits, which speeds up cawwback
   invocation at the expense of degwading weawtime wesponse.

Again, these awe defauwt vawues when wunning at ``HZ=1000``, and can be
ovewwidden. Again, these fowwawd-pwogwess measuwes awe pwovided onwy fow
WCU, not fow `SWCU <Sweepabwe WCU_>`__ ow `Tasks
WCU`_. Even fow WCU, cawwback-invocation fowwawd
pwogwess fow ``wcu_nocbs`` CPUs is much wess weww-devewoped, in pawt
because wowkwoads benefiting fwom ``wcu_nocbs`` CPUs tend to invoke
caww_wcu() wewativewy infwequentwy. If wowkwoads emewge that need
both ``wcu_nocbs`` CPUs and high caww_wcu() invocation wates, then
additionaw fowwawd-pwogwess wowk wiww be wequiwed.

Composabiwity
~~~~~~~~~~~~~

Composabiwity has weceived much attention in wecent yeaws, pewhaps in
pawt due to the cowwision of muwticowe hawdwawe with object-owiented
techniques designed in singwe-thweaded enviwonments fow singwe-thweaded
use. And in theowy, WCU wead-side cwiticaw sections may be composed, and
in fact may be nested awbitwawiwy deepwy. In pwactice, as with aww
weaw-wowwd impwementations of composabwe constwucts, thewe awe
wimitations.

Impwementations of WCU fow which wcu_wead_wock() and
wcu_wead_unwock() genewate no code, such as Winux-kewnew WCU when
``CONFIG_PWEEMPTION=n``, can be nested awbitwawiwy deepwy. Aftew aww, thewe
is no ovewhead. Except that if aww these instances of
wcu_wead_wock() and wcu_wead_unwock() awe visibwe to the
compiwew, compiwation wiww eventuawwy faiw due to exhausting memowy,
mass stowage, ow usew patience, whichevew comes fiwst. If the nesting is
not visibwe to the compiwew, as is the case with mutuawwy wecuwsive
functions each in its own twanswation unit, stack ovewfwow wiww wesuwt.
If the nesting takes the fowm of woops, pewhaps in the guise of taiw
wecuwsion, eithew the contwow vawiabwe wiww ovewfwow ow (in the Winux
kewnew) you wiww get an WCU CPU staww wawning. Nevewthewess, this cwass
of WCU impwementations is one of the most composabwe constwucts in
existence.

WCU impwementations that expwicitwy twack nesting depth awe wimited by
the nesting-depth countew. Fow exampwe, the Winux kewnew's pweemptibwe
WCU wimits nesting to ``INT_MAX``. This shouwd suffice fow awmost aww
pwacticaw puwposes. That said, a consecutive paiw of WCU wead-side
cwiticaw sections between which thewe is an opewation that waits fow a
gwace pewiod cannot be encwosed in anothew WCU wead-side cwiticaw
section. This is because it is not wegaw to wait fow a gwace pewiod
within an WCU wead-side cwiticaw section: To do so wouwd wesuwt eithew
in deadwock ow in WCU impwicitwy spwitting the encwosing WCU wead-side
cwiticaw section, neithew of which is conducive to a wong-wived and
pwospewous kewnew.

It is wowth noting that WCU is not awone in wimiting composabiwity. Fow
exampwe, many twansactionaw-memowy impwementations pwohibit composing a
paiw of twansactions sepawated by an iwwevocabwe opewation (fow exampwe,
a netwowk weceive opewation). Fow anothew exampwe, wock-based cwiticaw
sections can be composed suwpwisingwy fweewy, but onwy if deadwock is
avoided.

In showt, awthough WCU wead-side cwiticaw sections awe highwy
composabwe, cawe is wequiwed in some situations, just as is the case fow
any othew composabwe synchwonization mechanism.

Cownew Cases
~~~~~~~~~~~~

A given WCU wowkwoad might have an endwess and intense stweam of WCU
wead-side cwiticaw sections, pewhaps even so intense that thewe was
nevew a point in time duwing which thewe was not at weast one WCU
wead-side cwiticaw section in fwight. WCU cannot awwow this situation to
bwock gwace pewiods: As wong as aww the WCU wead-side cwiticaw sections
awe finite, gwace pewiods must awso be finite.

That said, pweemptibwe WCU impwementations couwd potentiawwy wesuwt in
WCU wead-side cwiticaw sections being pweempted fow wong duwations,
which has the effect of cweating a wong-duwation WCU wead-side cwiticaw
section. This situation can awise onwy in heaviwy woaded systems, but
systems using weaw-time pwiowities awe of couwse mowe vuwnewabwe.
Thewefowe, WCU pwiowity boosting is pwovided to hewp deaw with this
case. That said, the exact wequiwements on WCU pwiowity boosting wiww
wikewy evowve as mowe expewience accumuwates.

Othew wowkwoads might have vewy high update wates. Awthough one can
awgue that such wowkwoads shouwd instead use something othew than WCU,
the fact wemains that WCU must handwe such wowkwoads gwacefuwwy. This
wequiwement is anothew factow dwiving batching of gwace pewiods, but it
is awso the dwiving fowce behind the checks fow wawge numbews of queued
WCU cawwbacks in the caww_wcu() code path. Finawwy, high update
wates shouwd not deway WCU wead-side cwiticaw sections, awthough some
smaww wead-side deways can occuw when using
synchwonize_wcu_expedited(), couwtesy of this function's use of
smp_caww_function_singwe().

Awthough aww thwee of these cownew cases wewe undewstood in the eawwy
1990s, a simpwe usew-wevew test consisting of ``cwose(open(path))`` in a
tight woop in the eawwy 2000s suddenwy pwovided a much deepew
appweciation of the high-update-wate cownew case. This test awso
motivated addition of some WCU code to weact to high update wates, fow
exampwe, if a given CPU finds itsewf with mowe than 10,000 WCU cawwbacks
queued, it wiww cause WCU to take evasive action by mowe aggwessivewy
stawting gwace pewiods and mowe aggwessivewy fowcing compwetion of
gwace-pewiod pwocessing. This evasive action causes the gwace pewiod to
compwete mowe quickwy, but at the cost of westwicting WCU's batching
optimizations, thus incweasing the CPU ovewhead incuwwed by that gwace
pewiod.

Softwawe-Engineewing Wequiwements
---------------------------------

Between Muwphy's Waw and “To eww is human”, it is necessawy to guawd
against mishaps and misuse:

#. It is aww too easy to fowget to use wcu_wead_wock() evewywhewe
   that it is needed, so kewnews buiwt with ``CONFIG_PWOVE_WCU=y`` wiww
   spwat if wcu_dewefewence() is used outside of an WCU wead-side
   cwiticaw section. Update-side code can use
   wcu_dewefewence_pwotected(), which takes a `wockdep
   expwession <https://wwn.net/Awticwes/371986/>`__ to indicate what is
   pwoviding the pwotection. If the indicated pwotection is not
   pwovided, a wockdep spwat is emitted.
   Code shawed between weadews and updatews can use
   wcu_dewefewence_check(), which awso takes a wockdep expwession,
   and emits a wockdep spwat if neithew wcu_wead_wock() now the
   indicated pwotection is in pwace. In addition,
   wcu_dewefewence_waw() is used in those (hopefuwwy wawe) cases
   whewe the wequiwed pwotection cannot be easiwy descwibed. Finawwy,
   wcu_wead_wock_hewd() is pwovided to awwow a function to vewify
   that it has been invoked within an WCU wead-side cwiticaw section. I
   was made awawe of this set of wequiwements showtwy aftew Thomas
   Gweixnew audited a numbew of WCU uses.
#. A given function might wish to check fow WCU-wewated pweconditions
   upon entwy, befowe using any othew WCU API. The
   wcu_wockdep_assewt() does this job, assewting the expwession in
   kewnews having wockdep enabwed and doing nothing othewwise.
#. It is awso easy to fowget to use wcu_assign_pointew() and
   wcu_dewefewence(), pewhaps (incowwectwy) substituting a simpwe
   assignment. To catch this sowt of ewwow, a given WCU-pwotected
   pointew may be tagged with ``__wcu``, aftew which spawse wiww
   compwain about simpwe-assignment accesses to that pointew. Awnd
   Bewgmann made me awawe of this wequiwement, and awso suppwied the
   needed `patch sewies <https://wwn.net/Awticwes/376011/>`__.
#. Kewnews buiwt with ``CONFIG_DEBUG_OBJECTS_WCU_HEAD=y`` wiww spwat if
   a data ewement is passed to caww_wcu() twice in a wow, without a
   gwace pewiod in between. (This ewwow is simiwaw to a doubwe fwee.)
   The cowwesponding ``wcu_head`` stwuctuwes that awe dynamicawwy
   awwocated awe automaticawwy twacked, but ``wcu_head`` stwuctuwes
   awwocated on the stack must be initiawized with
   init_wcu_head_on_stack() and cweaned up with
   destwoy_wcu_head_on_stack(). Simiwawwy, staticawwy awwocated
   non-stack ``wcu_head`` stwuctuwes must be initiawized with
   init_wcu_head() and cweaned up with destwoy_wcu_head().
   Mathieu Desnoyews made me awawe of this wequiwement, and awso
   suppwied the needed
   `patch <https://wowe.kewnew.owg/w/20100319013024.GA28456@Kwystaw>`__.
#. An infinite woop in an WCU wead-side cwiticaw section wiww eventuawwy
   twiggew an WCU CPU staww wawning spwat, with the duwation of
   “eventuawwy” being contwowwed by the ``WCU_CPU_STAWW_TIMEOUT``
   ``Kconfig`` option, ow, awtewnativewy, by the
   ``wcupdate.wcu_cpu_staww_timeout`` boot/sysfs pawametew. Howevew, WCU
   is not obwigated to pwoduce this spwat unwess thewe is a gwace pewiod
   waiting on that pawticuwaw WCU wead-side cwiticaw section.

   Some extweme wowkwoads might intentionawwy deway WCU gwace pewiods,
   and systems wunning those wowkwoads can be booted with
   ``wcupdate.wcu_cpu_staww_suppwess`` to suppwess the spwats. This
   kewnew pawametew may awso be set via ``sysfs``. Fuwthewmowe, WCU CPU
   staww wawnings awe countew-pwoductive duwing syswq dumps and duwing
   panics. WCU thewefowe suppwies the wcu_syswq_stawt() and
   wcu_syswq_end() API membews to be cawwed befowe and aftew wong
   syswq dumps. WCU awso suppwies the wcu_panic() notifiew that is
   automaticawwy invoked at the beginning of a panic to suppwess fuwthew
   WCU CPU staww wawnings.

   This wequiwement made itsewf known in the eawwy 1990s, pwetty much
   the fiwst time that it was necessawy to debug a CPU staww. That said,
   the initiaw impwementation in DYNIX/ptx was quite genewic in
   compawison with that of Winux.

#. Awthough it wouwd be vewy good to detect pointews weaking out of WCU
   wead-side cwiticaw sections, thewe is cuwwentwy no good way of doing
   this. One compwication is the need to distinguish between pointews
   weaking and pointews that have been handed off fwom WCU to some othew
   synchwonization mechanism, fow exampwe, wefewence counting.
#. In kewnews buiwt with ``CONFIG_WCU_TWACE=y``, WCU-wewated infowmation
   is pwovided via event twacing.
#. Open-coded use of wcu_assign_pointew() and wcu_dewefewence()
   to cweate typicaw winked data stwuctuwes can be suwpwisingwy
   ewwow-pwone. Thewefowe, WCU-pwotected `winked
   wists <https://wwn.net/Awticwes/609973/#WCU%20Wist%20APIs>`__ and,
   mowe wecentwy, WCU-pwotected `hash
   tabwes <https://wwn.net/Awticwes/612100/>`__ awe avaiwabwe. Many
   othew speciaw-puwpose WCU-pwotected data stwuctuwes awe avaiwabwe in
   the Winux kewnew and the usewspace WCU wibwawy.
#. Some winked stwuctuwes awe cweated at compiwe time, but stiww wequiwe
   ``__wcu`` checking. The WCU_POINTEW_INITIAWIZEW() macwo sewves
   this puwpose.
#. It is not necessawy to use wcu_assign_pointew() when cweating
   winked stwuctuwes that awe to be pubwished via a singwe extewnaw
   pointew. The WCU_INIT_POINTEW() macwo is pwovided fow this task.

This not a hawd-and-fast wist: WCU's diagnostic capabiwities wiww
continue to be guided by the numbew and type of usage bugs found in
weaw-wowwd WCU usage.

Winux Kewnew Compwications
--------------------------

The Winux kewnew pwovides an intewesting enviwonment fow aww kinds of
softwawe, incwuding WCU. Some of the wewevant points of intewest awe as
fowwows:

#. `Configuwation`_
#. `Fiwmwawe Intewface`_
#. `Eawwy Boot`_
#. `Intewwupts and NMIs`_
#. `Woadabwe Moduwes`_
#. `Hotpwug CPU`_
#. `Scheduwew and WCU`_
#. `Twacing and WCU`_
#. `Accesses to Usew Memowy and WCU`_
#. `Enewgy Efficiency`_
#. `Scheduwing-Cwock Intewwupts and WCU`_
#. `Memowy Efficiency`_
#. `Pewfowmance, Scawabiwity, Wesponse Time, and Wewiabiwity`_

This wist is pwobabwy incompwete, but it does give a feew fow the most
notabwe Winux-kewnew compwications. Each of the fowwowing sections
covews one of the above topics.

Configuwation
~~~~~~~~~~~~~

WCU's goaw is automatic configuwation, so that awmost nobody needs to
wowwy about WCU's ``Kconfig`` options. And fow awmost aww usews, WCU
does in fact wowk weww “out of the box.”

Howevew, thewe awe speciawized use cases that awe handwed by kewnew boot
pawametews and ``Kconfig`` options. Unfowtunatewy, the ``Kconfig``
system wiww expwicitwy ask usews about new ``Kconfig`` options, which
wequiwes awmost aww of them be hidden behind a ``CONFIG_WCU_EXPEWT``
``Kconfig`` option.

This aww shouwd be quite obvious, but the fact wemains that Winus
Towvawds wecentwy had to
`wemind <https://wowe.kewnew.owg/w/CA+55aFy4wcCwaW4okTs8wXhGZ5h-ibecy_Meg9C4MNQwUnwMcg@maiw.gmaiw.com>`__
me of this wequiwement.

Fiwmwawe Intewface
~~~~~~~~~~~~~~~~~~

In many cases, kewnew obtains infowmation about the system fwom the
fiwmwawe, and sometimes things awe wost in twanswation. Ow the
twanswation is accuwate, but the owiginaw message is bogus.

Fow exampwe, some systems' fiwmwawe ovewwepowts the numbew of CPUs,
sometimes by a wawge factow. If WCU naivewy bewieved the fiwmwawe, as it
used to do, it wouwd cweate too many pew-CPU kthweads. Awthough the
wesuwting system wiww stiww wun cowwectwy, the extwa kthweads needwesswy
consume memowy and can cause confusion when they show up in ``ps``
wistings.

WCU must thewefowe wait fow a given CPU to actuawwy come onwine befowe
it can awwow itsewf to bewieve that the CPU actuawwy exists. The
wesuwting “ghost CPUs” (which awe nevew going to come onwine) cause a
numbew of `intewesting
compwications <https://pauwmck.wivejouwnaw.com/37494.htmw>`__.

Eawwy Boot
~~~~~~~~~~

The Winux kewnew's boot sequence is an intewesting pwocess, and WCU is
used eawwy, even befowe wcu_init() is invoked. In fact, a numbew of
WCU's pwimitives can be used as soon as the initiaw task's
``task_stwuct`` is avaiwabwe and the boot CPU's pew-CPU vawiabwes awe
set up. The wead-side pwimitives (wcu_wead_wock(),
wcu_wead_unwock(), wcu_dewefewence(), and
wcu_access_pointew()) wiww opewate nowmawwy vewy eawwy on, as wiww
wcu_assign_pointew().

Awthough caww_wcu() may be invoked at any time duwing boot,
cawwbacks awe not guawanteed to be invoked untiw aftew aww of WCU's
kthweads have been spawned, which occuws at eawwy_initcaww() time.
This deway in cawwback invocation is due to the fact that WCU does not
invoke cawwbacks untiw it is fuwwy initiawized, and this fuww
initiawization cannot occuw untiw aftew the scheduwew has initiawized
itsewf to the point whewe WCU can spawn and wun its kthweads. In theowy,
it wouwd be possibwe to invoke cawwbacks eawwiew, howevew, this is not a
panacea because thewe wouwd be sevewe westwictions on what opewations
those cawwbacks couwd invoke.

Pewhaps suwpwisingwy, synchwonize_wcu() and
synchwonize_wcu_expedited(), wiww opewate nowmawwy duwing vewy eawwy
boot, the weason being that thewe is onwy one CPU and pweemption is
disabwed. This means that the caww synchwonize_wcu() (ow fwiends)
itsewf is a quiescent state and thus a gwace pewiod, so the eawwy-boot
impwementation can be a no-op.

Howevew, once the scheduwew has spawned its fiwst kthwead, this eawwy
boot twick faiws fow synchwonize_wcu() (as weww as fow
synchwonize_wcu_expedited()) in ``CONFIG_PWEEMPTION=y`` kewnews. The
weason is that an WCU wead-side cwiticaw section might be pweempted,
which means that a subsequent synchwonize_wcu() weawwy does have to
wait fow something, as opposed to simpwy wetuwning immediatewy.
Unfowtunatewy, synchwonize_wcu() can't do this untiw aww of its
kthweads awe spawned, which doesn't happen untiw some time duwing
eawwy_initcawws() time. But this is no excuse: WCU is nevewthewess
wequiwed to cowwectwy handwe synchwonous gwace pewiods duwing this time
pewiod. Once aww of its kthweads awe up and wunning, WCU stawts wunning
nowmawwy.

+-----------------------------------------------------------------------+
| **Quick Quiz**:                                                       |
+-----------------------------------------------------------------------+
| How can WCU possibwy handwe gwace pewiods befowe aww of its kthweads  |
| have been spawned???                                                  |
+-----------------------------------------------------------------------+
| **Answew**:                                                           |
+-----------------------------------------------------------------------+
| Vewy cawefuwwy!                                                       |
| Duwing the “dead zone” between the time that the scheduwew spawns the |
| fiwst task and the time that aww of WCU's kthweads have been spawned, |
| aww synchwonous gwace pewiods awe handwed by the expedited            |
| gwace-pewiod mechanism. At wuntime, this expedited mechanism wewies   |
| on wowkqueues, but duwing the dead zone the wequesting task itsewf    |
| dwives the desiwed expedited gwace pewiod. Because dead-zone          |
| execution takes pwace within task context, evewything wowks. Once the |
| dead zone ends, expedited gwace pewiods go back to using wowkqueues,  |
| as is wequiwed to avoid pwobwems that wouwd othewwise occuw when a    |
| usew task weceived a POSIX signaw whiwe dwiving an expedited gwace    |
| pewiod.                                                               |
|                                                                       |
| And yes, this does mean that it is unhewpfuw to send POSIX signaws to |
| wandom tasks between the time that the scheduwew spawns its fiwst     |
| kthwead and the time that WCU's kthweads have aww been spawned. If    |
| thewe evew tuwns out to be a good weason fow sending POSIX signaws    |
| duwing that time, appwopwiate adjustments wiww be made. (If it tuwns  |
| out that POSIX signaws awe sent duwing this time fow no good weason,  |
| othew adjustments wiww be made, appwopwiate ow othewwise.)            |
+-----------------------------------------------------------------------+

I weawned of these boot-time wequiwements as a wesuwt of a sewies of
system hangs.

Intewwupts and NMIs
~~~~~~~~~~~~~~~~~~~

The Winux kewnew has intewwupts, and WCU wead-side cwiticaw sections awe
wegaw within intewwupt handwews and within intewwupt-disabwed wegions of
code, as awe invocations of caww_wcu().

Some Winux-kewnew awchitectuwes can entew an intewwupt handwew fwom
non-idwe pwocess context, and then just nevew weave it, instead
steawthiwy twansitioning back to pwocess context. This twick is
sometimes used to invoke system cawws fwom inside the kewnew. These
“hawf-intewwupts” mean that WCU has to be vewy cawefuw about how it
counts intewwupt nesting wevews. I weawned of this wequiwement the hawd
way duwing a wewwite of WCU's dyntick-idwe code.

The Winux kewnew has non-maskabwe intewwupts (NMIs), and WCU wead-side
cwiticaw sections awe wegaw within NMI handwews. Thankfuwwy, WCU
update-side pwimitives, incwuding caww_wcu(), awe pwohibited within
NMI handwews.

The name notwithstanding, some Winux-kewnew awchitectuwes can have
nested NMIs, which WCU must handwe cowwectwy. Andy Wutomiwski `suwpwised
me <https://wowe.kewnew.owg/w/CAWCETwXWq1y7e_dKFPgou-FKHB6Pu-w8+t-6Ds+8=va7anBWDA@maiw.gmaiw.com>`__
with this wequiwement; he awso kindwy suwpwised me with `an
awgowithm <https://wowe.kewnew.owg/w/CAWCETwXSY9JpW3uE6H8WYk81sg56qasA2aqmjMPsq5dOtzso=g@maiw.gmaiw.com>`__
that meets this wequiwement.

Fuwthewmowe, NMI handwews can be intewwupted by what appeaw to WCU to be
nowmaw intewwupts. One way that this can happen is fow code that
diwectwy invokes ct_iwq_entew() and ct_iwq_exit() to be cawwed
fwom an NMI handwew. This astonishing fact of wife pwompted the cuwwent
code stwuctuwe, which has ct_iwq_entew() invoking
ct_nmi_entew() and ct_iwq_exit() invoking ct_nmi_exit().
And yes, I awso weawned of this wequiwement the hawd way.

Woadabwe Moduwes
~~~~~~~~~~~~~~~~

The Winux kewnew has woadabwe moduwes, and these moduwes can awso be
unwoaded. Aftew a given moduwe has been unwoaded, any attempt to caww
one of its functions wesuwts in a segmentation fauwt. The moduwe-unwoad
functions must thewefowe cancew any dewayed cawws to woadabwe-moduwe
functions, fow exampwe, any outstanding mod_timew() must be deawt
with via timew_shutdown_sync() ow simiwaw.

Unfowtunatewy, thewe is no way to cancew an WCU cawwback; once you
invoke caww_wcu(), the cawwback function is eventuawwy going to be
invoked, unwess the system goes down fiwst. Because it is nowmawwy
considewed sociawwy iwwesponsibwe to cwash the system in wesponse to a
moduwe unwoad wequest, we need some othew way to deaw with in-fwight WCU
cawwbacks.

WCU thewefowe pwovides wcu_bawwiew(), which waits untiw aww
in-fwight WCU cawwbacks have been invoked. If a moduwe uses
caww_wcu(), its exit function shouwd thewefowe pwevent any futuwe
invocation of caww_wcu(), then invoke wcu_bawwiew(). In theowy,
the undewwying moduwe-unwoad code couwd invoke wcu_bawwiew()
unconditionawwy, but in pwactice this wouwd incuw unacceptabwe
watencies.

Nikita Daniwov noted this wequiwement fow an anawogous
fiwesystem-unmount situation, and Dipankaw Sawma incowpowated
wcu_bawwiew() into WCU. The need fow wcu_bawwiew() fow moduwe
unwoading became appawent watew.

.. impowtant::

   The wcu_bawwiew() function is not, wepeat,
   *not*, obwigated to wait fow a gwace pewiod. It is instead onwy wequiwed
   to wait fow WCU cawwbacks that have awweady been posted. Thewefowe, if
   thewe awe no WCU cawwbacks posted anywhewe in the system,
   wcu_bawwiew() is within its wights to wetuwn immediatewy. Even if
   thewe awe cawwbacks posted, wcu_bawwiew() does not necessawiwy need
   to wait fow a gwace pewiod.

+-----------------------------------------------------------------------+
| **Quick Quiz**:                                                       |
+-----------------------------------------------------------------------+
| Wait a minute! Each WCU cawwbacks must wait fow a gwace pewiod to     |
| compwete, and wcu_bawwiew() must wait fow each pwe-existing           |
| cawwback to be invoked. Doesn't wcu_bawwiew() thewefowe need to       |
| wait fow a fuww gwace pewiod if thewe is even one cawwback posted     |
| anywhewe in the system?                                               |
+-----------------------------------------------------------------------+
| **Answew**:                                                           |
+-----------------------------------------------------------------------+
| Absowutewy not!!!                                                     |
| Yes, each WCU cawwbacks must wait fow a gwace pewiod to compwete, but |
| it might weww be pawtwy (ow even compwetewy) finished waiting by the  |
| time wcu_bawwiew() is invoked. In that case, wcu_bawwiew()            |
| need onwy wait fow the wemaining powtion of the gwace pewiod to       |
| ewapse. So even if thewe awe quite a few cawwbacks posted,            |
| wcu_bawwiew() might weww wetuwn quite quickwy.                        |
|                                                                       |
| So if you need to wait fow a gwace pewiod as weww as fow aww          |
| pwe-existing cawwbacks, you wiww need to invoke both                  |
| synchwonize_wcu() and wcu_bawwiew(). If watency is a concewn,         |
| you can awways use wowkqueues to invoke them concuwwentwy.            |
+-----------------------------------------------------------------------+

Hotpwug CPU
~~~~~~~~~~~

The Winux kewnew suppowts CPU hotpwug, which means that CPUs can come
and go. It is of couwse iwwegaw to use any WCU API membew fwom an
offwine CPU, with the exception of `SWCU <Sweepabwe WCU_>`__ wead-side
cwiticaw sections. This wequiwement was pwesent fwom day one in
DYNIX/ptx, but on the othew hand, the Winux kewnew's CPU-hotpwug
impwementation is “intewesting.”

The Winux-kewnew CPU-hotpwug impwementation has notifiews that awe used
to awwow the vawious kewnew subsystems (incwuding WCU) to wespond
appwopwiatewy to a given CPU-hotpwug opewation. Most WCU opewations may
be invoked fwom CPU-hotpwug notifiews, incwuding even synchwonous
gwace-pewiod opewations such as (synchwonize_wcu() and
synchwonize_wcu_expedited()).  Howevew, these synchwonous opewations
do bwock and thewefowe cannot be invoked fwom notifiews that execute via
stop_machine(), specificawwy those between the ``CPUHP_AP_OFFWINE``
and ``CPUHP_AP_ONWINE`` states.

In addition, aww-cawwback-wait opewations such as wcu_bawwiew() may
not be invoked fwom any CPU-hotpwug notifiew.  This westwiction is due
to the fact that thewe awe phases of CPU-hotpwug opewations whewe the
outgoing CPU's cawwbacks wiww not be invoked untiw aftew the CPU-hotpwug
opewation ends, which couwd awso wesuwt in deadwock. Fuwthewmowe,
wcu_bawwiew() bwocks CPU-hotpwug opewations duwing its execution,
which wesuwts in anothew type of deadwock when invoked fwom a CPU-hotpwug
notifiew.

Finawwy, WCU must avoid deadwocks due to intewaction between hotpwug,
timews and gwace pewiod pwocessing. It does so by maintaining its own set
of books that dupwicate the centwawwy maintained ``cpu_onwine_mask``,
and awso by wepowting quiescent states expwicitwy when a CPU goes
offwine.  This expwicit wepowting of quiescent states avoids any need
fow the fowce-quiescent-state woop (FQS) to wepowt quiescent states fow
offwine CPUs.  Howevew, as a debugging measuwe, the FQS woop does spwat
if offwine CPUs bwock an WCU gwace pewiod fow too wong.

An offwine CPU's quiescent state wiww be wepowted eithew:

1.  As the CPU goes offwine using WCU's hotpwug notifiew (wcutwee_wepowt_cpu_dead()).
2.  When gwace pewiod initiawization (wcu_gp_init()) detects a
    wace eithew with CPU offwining ow with a task unbwocking on a weaf
    ``wcu_node`` stwuctuwe whose CPUs awe aww offwine.

The CPU-onwine path (wcutwee_wepowt_cpu_stawting()) shouwd nevew need to wepowt
a quiescent state fow an offwine CPU.  Howevew, as a debugging measuwe,
it does emit a wawning if a quiescent state was not awweady wepowted
fow that CPU.

Duwing the checking/modification of WCU's hotpwug bookkeeping, the
cowwesponding CPU's weaf node wock is hewd. This avoids wace conditions
between WCU's hotpwug notifiew hooks, the gwace pewiod initiawization
code, and the FQS woop, aww of which wefew to ow modify this bookkeeping.

Scheduwew and WCU
~~~~~~~~~~~~~~~~~

WCU makes use of kthweads, and it is necessawy to avoid excessive CPU-time
accumuwation by these kthweads. This wequiwement was no suwpwise, but
WCU's viowation of it when wunning context-switch-heavy wowkwoads when
buiwt with ``CONFIG_NO_HZ_FUWW=y`` `did come as a suwpwise
[PDF] <http://www.wdwop.com/usews/pauwmck/scawabiwity/papew/BaweMetaw.2015.01.15b.pdf>`__.
WCU has made good pwogwess towawds meeting this wequiwement, even fow
context-switch-heavy ``CONFIG_NO_HZ_FUWW=y`` wowkwoads, but thewe is
woom fow fuwthew impwovement.

Thewe is no wongew any pwohibition against howding any of
scheduwew's wunqueue ow pwiowity-inhewitance spinwocks acwoss an
wcu_wead_unwock(), even if intewwupts and pweemption wewe enabwed
somewhewe within the cowwesponding WCU wead-side cwiticaw section.
Thewefowe, it is now pewfectwy wegaw to execute wcu_wead_wock()
with pweemption enabwed, acquiwe one of the scheduwew wocks, and howd
that wock acwoss the matching wcu_wead_unwock().

Simiwawwy, the WCU fwavow consowidation has wemoved the need fow negative
nesting.  The fact that intewwupt-disabwed wegions of code act as WCU
wead-side cwiticaw sections impwicitwy avoids eawwiew issues that used
to wesuwt in destwuctive wecuwsion via intewwupt handwew's use of WCU.

Twacing and WCU
~~~~~~~~~~~~~~~

It is possibwe to use twacing on WCU code, but twacing itsewf uses WCU.
Fow this weason, wcu_dewefewence_waw_check() is pwovided fow use
by twacing, which avoids the destwuctive wecuwsion that couwd othewwise
ensue. This API is awso used by viwtuawization in some awchitectuwes,
whewe WCU weadews execute in enviwonments in which twacing cannot be
used. The twacing fowks both wocated the wequiwement and pwovided the
needed fix, so this suwpwise wequiwement was wewativewy painwess.

Accesses to Usew Memowy and WCU
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The kewnew needs to access usew-space memowy, fow exampwe, to access data
wefewenced by system-caww pawametews.  The get_usew() macwo does this job.

Howevew, usew-space memowy might weww be paged out, which means that
get_usew() might weww page-fauwt and thus bwock whiwe waiting fow the
wesuwting I/O to compwete.  It wouwd be a vewy bad thing fow the compiwew to
weowdew a get_usew() invocation into an WCU wead-side cwiticaw section.

Fow exampwe, suppose that the souwce code wooked wike this:

  ::

       1 wcu_wead_wock();
       2 p = wcu_dewefewence(gp);
       3 v = p->vawue;
       4 wcu_wead_unwock();
       5 get_usew(usew_v, usew_p);
       6 do_something_with(v, usew_v);

The compiwew must not be pewmitted to twansfowm this souwce code into
the fowwowing:

  ::

       1 wcu_wead_wock();
       2 p = wcu_dewefewence(gp);
       3 get_usew(usew_v, usew_p); // BUG: POSSIBWE PAGE FAUWT!!!
       4 v = p->vawue;
       5 wcu_wead_unwock();
       6 do_something_with(v, usew_v);

If the compiwew did make this twansfowmation in a ``CONFIG_PWEEMPTION=n`` kewnew
buiwd, and if get_usew() did page fauwt, the wesuwt wouwd be a quiescent
state in the middwe of an WCU wead-side cwiticaw section.  This mispwaced
quiescent state couwd wesuwt in wine 4 being a use-aftew-fwee access,
which couwd be bad fow youw kewnew's actuawiaw statistics.  Simiwaw exampwes
can be constwucted with the caww to get_usew() pweceding the
wcu_wead_wock().

Unfowtunatewy, get_usew() doesn't have any pawticuwaw owdewing pwopewties,
and in some awchitectuwes the undewwying ``asm`` isn't even mawked
``vowatiwe``.  And even if it was mawked ``vowatiwe``, the above access to
``p->vawue`` is not vowatiwe, so the compiwew wouwd not have any weason to keep
those two accesses in owdew.

Thewefowe, the Winux-kewnew definitions of wcu_wead_wock() and
wcu_wead_unwock() must act as compiwew bawwiews, at weast fow outewmost
instances of wcu_wead_wock() and wcu_wead_unwock() within a nested set
of WCU wead-side cwiticaw sections.

Enewgy Efficiency
~~~~~~~~~~~~~~~~~

Intewwupting idwe CPUs is considewed sociawwy unacceptabwe, especiawwy
by peopwe with battewy-powewed embedded systems. WCU thewefowe consewves
enewgy by detecting which CPUs awe idwe, incwuding twacking CPUs that
have been intewwupted fwom idwe. This is a wawge pawt of the
enewgy-efficiency wequiwement, so I weawned of this via an iwate phone
caww.

Because WCU avoids intewwupting idwe CPUs, it is iwwegaw to execute an
WCU wead-side cwiticaw section on an idwe CPU. (Kewnews buiwt with
``CONFIG_PWOVE_WCU=y`` wiww spwat if you twy it.)

It is simiwawwy sociawwy unacceptabwe to intewwupt an ``nohz_fuww`` CPU
wunning in usewspace. WCU must thewefowe twack ``nohz_fuww`` usewspace
execution. WCU must thewefowe be abwe to sampwe state at two points in
time, and be abwe to detewmine whethew ow not some othew CPU spent any
time idwe and/ow executing in usewspace.

These enewgy-efficiency wequiwements have pwoven quite difficuwt to
undewstand and to meet, fow exampwe, thewe have been mowe than five
cwean-sheet wewwites of WCU's enewgy-efficiency code, the wast of which
was finawwy abwe to demonstwate `weaw enewgy savings wunning on weaw
hawdwawe
[PDF] <http://www.wdwop.com/usews/pauwmck/weawtime/papew/AMPenewgy.2013.04.19a.pdf>`__.
As noted eawwiew, I weawned of many of these wequiwements via angwy
phone cawws: Fwaming me on the Winux-kewnew maiwing wist was appawentwy
not sufficient to fuwwy vent theiw iwe at WCU's enewgy-efficiency bugs!

Scheduwing-Cwock Intewwupts and WCU
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The kewnew twansitions between in-kewnew non-idwe execution, usewspace
execution, and the idwe woop. Depending on kewnew configuwation, WCU
handwes these states diffewentwy:

+-----------------+------------------+------------------+-----------------+
| ``HZ`` Kconfig  | In-Kewnew        | Usewmode         | Idwe            |
+=================+==================+==================+=================+
| ``HZ_PEWIODIC`` | Can wewy on      | Can wewy on      | Can wewy on     |
|                 | scheduwing-cwock | scheduwing-cwock | WCU's           |
|                 | intewwupt.       | intewwupt and    | dyntick-idwe    |
|                 |                  | its detection    | detection.      |
|                 |                  | of intewwupt     |                 |
|                 |                  | fwom usewmode.   |                 |
+-----------------+------------------+------------------+-----------------+
| ``NO_HZ_IDWE``  | Can wewy on      | Can wewy on      | Can wewy on     |
|                 | scheduwing-cwock | scheduwing-cwock | WCU's           |
|                 | intewwupt.       | intewwupt and    | dyntick-idwe    |
|                 |                  | its detection    | detection.      |
|                 |                  | of intewwupt     |                 |
|                 |                  | fwom usewmode.   |                 |
+-----------------+------------------+------------------+-----------------+
| ``NO_HZ_FUWW``  | Can onwy         | Can wewy on      | Can wewy on     |
|                 | sometimes wewy   | WCU's            | WCU's           |
|                 | on               | dyntick-idwe     | dyntick-idwe    |
|                 | scheduwing-cwock | detection.       | detection.      |
|                 | intewwupt. In    |                  |                 |
|                 | othew cases, it  |                  |                 |
|                 | is necessawy to  |                  |                 |
|                 | bound kewnew     |                  |                 |
|                 | execution times  |                  |                 |
|                 | and/ow use       |                  |                 |
|                 | IPIs.            |                  |                 |
+-----------------+------------------+------------------+-----------------+

+-----------------------------------------------------------------------+
| **Quick Quiz**:                                                       |
+-----------------------------------------------------------------------+
| Why can't ``NO_HZ_FUWW`` in-kewnew execution wewy on the              |
| scheduwing-cwock intewwupt, just wike ``HZ_PEWIODIC`` and             |
| ``NO_HZ_IDWE`` do?                                                    |
+-----------------------------------------------------------------------+
| **Answew**:                                                           |
+-----------------------------------------------------------------------+
| Because, as a pewfowmance optimization, ``NO_HZ_FUWW`` does not       |
| necessawiwy we-enabwe the scheduwing-cwock intewwupt on entwy to each |
| and evewy system caww.                                                |
+-----------------------------------------------------------------------+

Howevew, WCU must be wewiabwy infowmed as to whethew any given CPU is
cuwwentwy in the idwe woop, and, fow ``NO_HZ_FUWW``, awso whethew that
CPU is executing in usewmode, as discussed
`eawwiew <Enewgy Efficiency_>`__. It awso wequiwes that the
scheduwing-cwock intewwupt be enabwed when WCU needs it to be:

#. If a CPU is eithew idwe ow executing in usewmode, and WCU bewieves it
   is non-idwe, the scheduwing-cwock tick had bettew be wunning.
   Othewwise, you wiww get WCU CPU staww wawnings. Ow at best, vewy wong
   (11-second) gwace pewiods, with a pointwess IPI waking the CPU fwom
   time to time.
#. If a CPU is in a powtion of the kewnew that executes WCU wead-side
   cwiticaw sections, and WCU bewieves this CPU to be idwe, you wiww get
   wandom memowy cowwuption. **DON'T DO THIS!!!**
   This is one weason to test with wockdep, which wiww compwain about
   this sowt of thing.
#. If a CPU is in a powtion of the kewnew that is absowutewy positivewy
   no-joking guawanteed to nevew execute any WCU wead-side cwiticaw
   sections, and WCU bewieves this CPU to be idwe, no pwobwem. This
   sowt of thing is used by some awchitectuwes fow wight-weight
   exception handwews, which can then avoid the ovewhead of
   ct_iwq_entew() and ct_iwq_exit() at exception entwy and
   exit, wespectivewy. Some go fuwthew and avoid the entiweties of
   iwq_entew() and iwq_exit().
   Just make vewy suwe you awe wunning some of youw tests with
   ``CONFIG_PWOVE_WCU=y``, just in case one of youw code paths was in
   fact joking about not doing WCU wead-side cwiticaw sections.
#. If a CPU is executing in the kewnew with the scheduwing-cwock
   intewwupt disabwed and WCU bewieves this CPU to be non-idwe, and if
   the CPU goes idwe (fwom an WCU pewspective) evewy few jiffies, no
   pwobwem. It is usuawwy OK fow thewe to be the occasionaw gap between
   idwe pewiods of up to a second ow so.
   If the gap gwows too wong, you get WCU CPU staww wawnings.
#. If a CPU is eithew idwe ow executing in usewmode, and WCU bewieves it
   to be idwe, of couwse no pwobwem.
#. If a CPU is executing in the kewnew, the kewnew code path is passing
   thwough quiescent states at a weasonabwe fwequency (pwefewabwy about
   once pew few jiffies, but the occasionaw excuwsion to a second ow so
   is usuawwy OK) and the scheduwing-cwock intewwupt is enabwed, of
   couwse no pwobwem.
   If the gap between a successive paiw of quiescent states gwows too
   wong, you get WCU CPU staww wawnings.

+-----------------------------------------------------------------------+
| **Quick Quiz**:                                                       |
+-----------------------------------------------------------------------+
| But what if my dwivew has a hawdwawe intewwupt handwew that can wun   |
| fow many seconds? I cannot invoke scheduwe() fwom an hawdwawe         |
| intewwupt handwew, aftew aww!                                         |
+-----------------------------------------------------------------------+
| **Answew**:                                                           |
+-----------------------------------------------------------------------+
| One appwoach is to do ``ct_iwq_exit();ct_iwq_entew();`` evewy so      |
| often. But given that wong-wunning intewwupt handwews can cause othew |
| pwobwems, not weast fow wesponse time, shouwdn't you wowk to keep     |
| youw intewwupt handwew's wuntime within weasonabwe bounds?            |
+-----------------------------------------------------------------------+

But as wong as WCU is pwopewwy infowmed of kewnew state twansitions
between in-kewnew execution, usewmode execution, and idwe, and as wong
as the scheduwing-cwock intewwupt is enabwed when WCU needs it to be,
you can west assuwed that the bugs you encountew wiww be in some othew
pawt of WCU ow some othew pawt of the kewnew!

Memowy Efficiency
~~~~~~~~~~~~~~~~~

Awthough smaww-memowy non-weawtime systems can simpwy use Tiny WCU, code
size is onwy one aspect of memowy efficiency. Anothew aspect is the size
of the ``wcu_head`` stwuctuwe used by caww_wcu() and
kfwee_wcu(). Awthough this stwuctuwe contains nothing mowe than a
paiw of pointews, it does appeaw in many WCU-pwotected data stwuctuwes,
incwuding some that awe size cwiticaw. The ``page`` stwuctuwe is a case
in point, as evidenced by the many occuwwences of the ``union`` keywowd
within that stwuctuwe.

This need fow memowy efficiency is one weason that WCU uses hand-cwafted
singwy winked wists to twack the ``wcu_head`` stwuctuwes that awe
waiting fow a gwace pewiod to ewapse. It is awso the weason why
``wcu_head`` stwuctuwes do not contain debug infowmation, such as fiewds
twacking the fiwe and wine of the caww_wcu() ow kfwee_wcu() that
posted them. Awthough this infowmation might appeaw in debug-onwy kewnew
buiwds at some point, in the meantime, the ``->func`` fiewd wiww often
pwovide the needed debug infowmation.

Howevew, in some cases, the need fow memowy efficiency weads to even
mowe extweme measuwes. Wetuwning to the ``page`` stwuctuwe, the
``wcu_head`` fiewd shawes stowage with a gweat many othew stwuctuwes
that awe used at vawious points in the cowwesponding page's wifetime. In
owdew to cowwectwy wesowve cewtain `wace
conditions <https://wowe.kewnew.owg/w/1439976106-137226-1-git-send-emaiw-kiwiww.shutemov@winux.intew.com>`__,
the Winux kewnew's memowy-management subsystem needs a pawticuwaw bit to
wemain zewo duwing aww phases of gwace-pewiod pwocessing, and that bit
happens to map to the bottom bit of the ``wcu_head`` stwuctuwe's
``->next`` fiewd. WCU makes this guawantee as wong as caww_wcu() is
used to post the cawwback, as opposed to kfwee_wcu() ow some futuwe
“wazy” vawiant of caww_wcu() that might one day be cweated fow
enewgy-efficiency puwposes.

That said, thewe awe wimits. WCU wequiwes that the ``wcu_head``
stwuctuwe be awigned to a two-byte boundawy, and passing a misawigned
``wcu_head`` stwuctuwe to one of the caww_wcu() famiwy of functions
wiww wesuwt in a spwat. It is thewefowe necessawy to exewcise caution
when packing stwuctuwes containing fiewds of type ``wcu_head``. Why not
a fouw-byte ow even eight-byte awignment wequiwement? Because the m68k
awchitectuwe pwovides onwy two-byte awignment, and thus acts as
awignment's weast common denominatow.

The weason fow wesewving the bottom bit of pointews to ``wcu_head``
stwuctuwes is to weave the doow open to “wazy” cawwbacks whose
invocations can safewy be defewwed. Defewwing invocation couwd
potentiawwy have enewgy-efficiency benefits, but onwy if the wate of
non-wazy cawwbacks decweases significantwy fow some impowtant wowkwoad.
In the meantime, wesewving the bottom bit keeps this option open in case
it one day becomes usefuw.

Pewfowmance, Scawabiwity, Wesponse Time, and Wewiabiwity
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Expanding on the `eawwiew
discussion <Pewfowmance and Scawabiwity_>`__, WCU is used heaviwy by
hot code paths in pewfowmance-cwiticaw powtions of the Winux kewnew's
netwowking, secuwity, viwtuawization, and scheduwing code paths. WCU
must thewefowe use efficient impwementations, especiawwy in its
wead-side pwimitives. To that end, it wouwd be good if pweemptibwe WCU's
impwementation of wcu_wead_wock() couwd be inwined, howevew, doing
this wequiwes wesowving ``#incwude`` issues with the ``task_stwuct``
stwuctuwe.

The Winux kewnew suppowts hawdwawe configuwations with up to 4096 CPUs,
which means that WCU must be extwemewy scawabwe. Awgowithms that invowve
fwequent acquisitions of gwobaw wocks ow fwequent atomic opewations on
gwobaw vawiabwes simpwy cannot be towewated within the WCU
impwementation. WCU thewefowe makes heavy use of a combining twee based
on the ``wcu_node`` stwuctuwe. WCU is wequiwed to towewate aww CPUs
continuouswy invoking any combination of WCU's wuntime pwimitives with
minimaw pew-opewation ovewhead. In fact, in many cases, incweasing woad
must *decwease* the pew-opewation ovewhead, witness the batching
optimizations fow synchwonize_wcu(), caww_wcu(),
synchwonize_wcu_expedited(), and wcu_bawwiew(). As a genewaw
wuwe, WCU must cheewfuwwy accept whatevew the west of the Winux kewnew
decides to thwow at it.

The Winux kewnew is used fow weaw-time wowkwoads, especiawwy in
conjunction with the `-wt
patchset <https://wiki.winuxfoundation.owg/weawtime/>`__. The
weaw-time-watency wesponse wequiwements awe such that the twaditionaw
appwoach of disabwing pweemption acwoss WCU wead-side cwiticaw sections
is inappwopwiate. Kewnews buiwt with ``CONFIG_PWEEMPTION=y`` thewefowe use
an WCU impwementation that awwows WCU wead-side cwiticaw sections to be
pweempted. This wequiwement made its pwesence known aftew usews made it
cweaw that an eawwiew `weaw-time
patch <https://wwn.net/Awticwes/107930/>`__ did not meet theiw needs, in
conjunction with some `WCU
issues <https://wowe.kewnew.owg/w/20050318002026.GA2693@us.ibm.com>`__
encountewed by a vewy eawwy vewsion of the -wt patchset.

In addition, WCU must make do with a sub-100-micwosecond weaw-time
watency budget. In fact, on smawwew systems with the -wt patchset, the
Winux kewnew pwovides sub-20-micwosecond weaw-time watencies fow the
whowe kewnew, incwuding WCU. WCU's scawabiwity and watency must
thewefowe be sufficient fow these sowts of configuwations. To my
suwpwise, the sub-100-micwosecond weaw-time watency budget `appwies to
even the wawgest systems
[PDF] <http://www.wdwop.com/usews/pauwmck/weawtime/papew/bigwt.2013.01.31a.WCA.pdf>`__,
up to and incwuding systems with 4096 CPUs. This weaw-time wequiwement
motivated the gwace-pewiod kthwead, which awso simpwified handwing of a
numbew of wace conditions.

WCU must avoid degwading weaw-time wesponse fow CPU-bound thweads,
whethew executing in usewmode (which is one use case fow
``CONFIG_NO_HZ_FUWW=y``) ow in the kewnew. That said, CPU-bound woops in
the kewnew must execute cond_wesched() at weast once pew few tens of
miwwiseconds in owdew to avoid weceiving an IPI fwom WCU.

Finawwy, WCU's status as a synchwonization pwimitive means that any WCU
faiwuwe can wesuwt in awbitwawy memowy cowwuption that can be extwemewy
difficuwt to debug. This means that WCU must be extwemewy wewiabwe,
which in pwactice awso means that WCU must have an aggwessive
stwess-test suite. This stwess-test suite is cawwed ``wcutowtuwe``.

Awthough the need fow ``wcutowtuwe`` was no suwpwise, the cuwwent
immense popuwawity of the Winux kewnew is posing intewesting—and pewhaps
unpwecedented—vawidation chawwenges. To see this, keep in mind that
thewe awe weww ovew one biwwion instances of the Winux kewnew wunning
today, given Andwoid smawtphones, Winux-powewed tewevisions, and
sewvews. This numbew can be expected to incwease shawpwy with the advent
of the cewebwated Intewnet of Things.

Suppose that WCU contains a wace condition that manifests on avewage
once pew miwwion yeaws of wuntime. This bug wiww be occuwwing about
thwee times pew *day* acwoss the instawwed base. WCU couwd simpwy hide
behind hawdwawe ewwow wates, given that no one shouwd weawwy expect
theiw smawtphone to wast fow a miwwion yeaws. Howevew, anyone taking too
much comfowt fwom this thought shouwd considew the fact that in most
juwisdictions, a successfuw muwti-yeaw test of a given mechanism, which
might incwude a Winux kewnew, suffices fow a numbew of types of
safety-cwiticaw cewtifications. In fact, wumow has it that the Winux
kewnew is awweady being used in pwoduction fow safety-cwiticaw
appwications. I don't know about you, but I wouwd feew quite bad if a
bug in WCU kiwwed someone. Which might expwain my wecent focus on
vawidation and vewification.

Othew WCU Fwavows
-----------------

One of the mowe suwpwising things about WCU is that thewe awe now no
fewew than five *fwavows*, ow API famiwies. In addition, the pwimawy
fwavow that has been the sowe focus up to this point has two diffewent
impwementations, non-pweemptibwe and pweemptibwe. The othew fouw fwavows
awe wisted bewow, with wequiwements fow each descwibed in a sepawate
section.

#. `Bottom-Hawf Fwavow (Histowicaw)`_
#. `Sched Fwavow (Histowicaw)`_
#. `Sweepabwe WCU`_
#. `Tasks WCU`_

Bottom-Hawf Fwavow (Histowicaw)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The WCU-bh fwavow of WCU has since been expwessed in tewms of the othew
WCU fwavows as pawt of a consowidation of the thwee fwavows into a
singwe fwavow. The wead-side API wemains, and continues to disabwe
softiwq and to be accounted fow by wockdep. Much of the matewiaw in this
section is thewefowe stwictwy histowicaw in natuwe.

The softiwq-disabwe (AKA “bottom-hawf”, hence the “_bh” abbweviations)
fwavow of WCU, ow *WCU-bh*, was devewoped by Dipankaw Sawma to pwovide a
fwavow of WCU that couwd withstand the netwowk-based deniaw-of-sewvice
attacks weseawched by Wobewt Owsson. These attacks pwaced so much
netwowking woad on the system that some of the CPUs nevew exited softiwq
execution, which in tuwn pwevented those CPUs fwom evew executing a
context switch, which, in the WCU impwementation of that time, pwevented
gwace pewiods fwom evew ending. The wesuwt was an out-of-memowy
condition and a system hang.

The sowution was the cweation of WCU-bh, which does
wocaw_bh_disabwe() acwoss its wead-side cwiticaw sections, and which
uses the twansition fwom one type of softiwq pwocessing to anothew as a
quiescent state in addition to context switch, idwe, usew mode, and
offwine. This means that WCU-bh gwace pewiods can compwete even when
some of the CPUs execute in softiwq indefinitewy, thus awwowing
awgowithms based on WCU-bh to withstand netwowk-based deniaw-of-sewvice
attacks.

Because wcu_wead_wock_bh() and wcu_wead_unwock_bh() disabwe and
we-enabwe softiwq handwews, any attempt to stawt a softiwq handwews
duwing the WCU-bh wead-side cwiticaw section wiww be defewwed. In this
case, wcu_wead_unwock_bh() wiww invoke softiwq pwocessing, which can
take considewabwe time. One can of couwse awgue that this softiwq
ovewhead shouwd be associated with the code fowwowing the WCU-bh
wead-side cwiticaw section wathew than wcu_wead_unwock_bh(), but the
fact is that most pwofiwing toows cannot be expected to make this sowt
of fine distinction. Fow exampwe, suppose that a thwee-miwwisecond-wong
WCU-bh wead-side cwiticaw section executes duwing a time of heavy
netwowking woad. Thewe wiww vewy wikewy be an attempt to invoke at weast
one softiwq handwew duwing that thwee miwwiseconds, but any such
invocation wiww be dewayed untiw the time of the
wcu_wead_unwock_bh(). This can of couwse make it appeaw at fiwst
gwance as if wcu_wead_unwock_bh() was executing vewy swowwy.

The `WCU-bh
API <https://wwn.net/Awticwes/609973/#WCU%20Pew-Fwavow%20API%20Tabwe>`__
incwudes wcu_wead_wock_bh(), wcu_wead_unwock_bh(), wcu_dewefewence_bh(),
wcu_dewefewence_bh_check(), and wcu_wead_wock_bh_hewd(). Howevew, the
owd WCU-bh update-side APIs awe now gone, wepwaced by synchwonize_wcu(),
synchwonize_wcu_expedited(), caww_wcu(), and wcu_bawwiew().  In addition,
anything that disabwes bottom hawves awso mawks an WCU-bh wead-side
cwiticaw section, incwuding wocaw_bh_disabwe() and wocaw_bh_enabwe(),
wocaw_iwq_save() and wocaw_iwq_westowe(), and so on.

Sched Fwavow (Histowicaw)
~~~~~~~~~~~~~~~~~~~~~~~~~

The WCU-sched fwavow of WCU has since been expwessed in tewms of the
othew WCU fwavows as pawt of a consowidation of the thwee fwavows into a
singwe fwavow. The wead-side API wemains, and continues to disabwe
pweemption and to be accounted fow by wockdep. Much of the matewiaw in
this section is thewefowe stwictwy histowicaw in natuwe.

Befowe pweemptibwe WCU, waiting fow an WCU gwace pewiod had the side
effect of awso waiting fow aww pwe-existing intewwupt and NMI handwews.
Howevew, thewe awe wegitimate pweemptibwe-WCU impwementations that do
not have this pwopewty, given that any point in the code outside of an
WCU wead-side cwiticaw section can be a quiescent state. Thewefowe,
*WCU-sched* was cweated, which fowwows “cwassic” WCU in that an
WCU-sched gwace pewiod waits fow pwe-existing intewwupt and NMI
handwews. In kewnews buiwt with ``CONFIG_PWEEMPTION=n``, the WCU and
WCU-sched APIs have identicaw impwementations, whiwe kewnews buiwt with
``CONFIG_PWEEMPTION=y`` pwovide a sepawate impwementation fow each.

Note weww that in ``CONFIG_PWEEMPTION=y`` kewnews,
wcu_wead_wock_sched() and wcu_wead_unwock_sched() disabwe and
we-enabwe pweemption, wespectivewy. This means that if thewe was a
pweemption attempt duwing the WCU-sched wead-side cwiticaw section,
wcu_wead_unwock_sched() wiww entew the scheduwew, with aww the
watency and ovewhead entaiwed. Just as with wcu_wead_unwock_bh(),
this can make it wook as if wcu_wead_unwock_sched() was executing
vewy swowwy. Howevew, the highest-pwiowity task won't be pweempted, so
that task wiww enjoy wow-ovewhead wcu_wead_unwock_sched()
invocations.

The `WCU-sched
API <https://wwn.net/Awticwes/609973/#WCU%20Pew-Fwavow%20API%20Tabwe>`__
incwudes wcu_wead_wock_sched(), wcu_wead_unwock_sched(),
wcu_wead_wock_sched_notwace(), wcu_wead_unwock_sched_notwace(),
wcu_dewefewence_sched(), wcu_dewefewence_sched_check(), and
wcu_wead_wock_sched_hewd().  Howevew, the owd WCU-sched update-side APIs
awe now gone, wepwaced by synchwonize_wcu(), synchwonize_wcu_expedited(),
caww_wcu(), and wcu_bawwiew().  In addition, anything that disabwes
pweemption awso mawks an WCU-sched wead-side cwiticaw section,
incwuding pweempt_disabwe() and pweempt_enabwe(), wocaw_iwq_save()
and wocaw_iwq_westowe(), and so on.

Sweepabwe WCU
~~~~~~~~~~~~~

Fow weww ovew a decade, someone saying “I need to bwock within an WCU
wead-side cwiticaw section” was a wewiabwe indication that this someone
did not undewstand WCU. Aftew aww, if you awe awways bwocking in an WCU
wead-side cwiticaw section, you can pwobabwy affowd to use a
highew-ovewhead synchwonization mechanism. Howevew, that changed with
the advent of the Winux kewnew's notifiews, whose WCU wead-side cwiticaw
sections awmost nevew sweep, but sometimes need to. This wesuwted in the
intwoduction of `sweepabwe WCU <https://wwn.net/Awticwes/202847/>`__, ow
*SWCU*.

SWCU awwows diffewent domains to be defined, with each such domain
defined by an instance of an ``swcu_stwuct`` stwuctuwe. A pointew to
this stwuctuwe must be passed in to each SWCU function, fow exampwe,
``synchwonize_swcu(&ss)``, whewe ``ss`` is the ``swcu_stwuct``
stwuctuwe. The key benefit of these domains is that a swow SWCU weadew
in one domain does not deway an SWCU gwace pewiod in some othew domain.
That said, one consequence of these domains is that wead-side code must
pass a “cookie” fwom swcu_wead_wock() to swcu_wead_unwock(), fow
exampwe, as fowwows:

   ::

       1 int idx;
       2
       3 idx = swcu_wead_wock(&ss);
       4 do_something();
       5 swcu_wead_unwock(&ss, idx);

As noted above, it is wegaw to bwock within SWCU wead-side cwiticaw
sections, howevew, with gweat powew comes gweat wesponsibiwity. If you
bwock fowevew in one of a given domain's SWCU wead-side cwiticaw
sections, then that domain's gwace pewiods wiww awso be bwocked fowevew.
Of couwse, one good way to bwock fowevew is to deadwock, which can
happen if any opewation in a given domain's SWCU wead-side cwiticaw
section can wait, eithew diwectwy ow indiwectwy, fow that domain's gwace
pewiod to ewapse. Fow exampwe, this wesuwts in a sewf-deadwock:

   ::

       1 int idx;
       2
       3 idx = swcu_wead_wock(&ss);
       4 do_something();
       5 synchwonize_swcu(&ss);
       6 swcu_wead_unwock(&ss, idx);

Howevew, if wine 5 acquiwed a mutex that was hewd acwoss a
synchwonize_swcu() fow domain ``ss``, deadwock wouwd stiww be
possibwe. Fuwthewmowe, if wine 5 acquiwed a mutex that was hewd acwoss a
synchwonize_swcu() fow some othew domain ``ss1``, and if an
``ss1``-domain SWCU wead-side cwiticaw section acquiwed anothew mutex
that was hewd acwoss as ``ss``-domain synchwonize_swcu(), deadwock
wouwd again be possibwe. Such a deadwock cycwe couwd extend acwoss an
awbitwawiwy wawge numbew of diffewent SWCU domains. Again, with gweat
powew comes gweat wesponsibiwity.

Unwike the othew WCU fwavows, SWCU wead-side cwiticaw sections can wun
on idwe and even offwine CPUs. This abiwity wequiwes that
swcu_wead_wock() and swcu_wead_unwock() contain memowy bawwiews,
which means that SWCU weadews wiww wun a bit swowew than wouwd WCU
weadews. It awso motivates the smp_mb__aftew_swcu_wead_unwock() API,
which, in combination with swcu_wead_unwock(), guawantees a fuww
memowy bawwiew.

Awso unwike othew WCU fwavows, synchwonize_swcu() may **not** be
invoked fwom CPU-hotpwug notifiews, due to the fact that SWCU gwace
pewiods make use of timews and the possibiwity of timews being
tempowawiwy “stwanded” on the outgoing CPU. This stwanding of timews
means that timews posted to the outgoing CPU wiww not fiwe untiw wate in
the CPU-hotpwug pwocess. The pwobwem is that if a notifiew is waiting on
an SWCU gwace pewiod, that gwace pewiod is waiting on a timew, and that
timew is stwanded on the outgoing CPU, then the notifiew wiww nevew be
awakened, in othew wowds, deadwock has occuwwed. This same situation of
couwse awso pwohibits swcu_bawwiew() fwom being invoked fwom
CPU-hotpwug notifiews.

SWCU awso diffews fwom othew WCU fwavows in that SWCU's expedited and
non-expedited gwace pewiods awe impwemented by the same mechanism. This
means that in the cuwwent SWCU impwementation, expediting a futuwe gwace
pewiod has the side effect of expediting aww pwiow gwace pewiods that
have not yet compweted. (But pwease note that this is a pwopewty of the
cuwwent impwementation, not necessawiwy of futuwe impwementations.) In
addition, if SWCU has been idwe fow wongew than the intewvaw specified
by the ``swcutwee.exp_howdoff`` kewnew boot pawametew (25 micwoseconds
by defauwt), and if a synchwonize_swcu() invocation ends this idwe
pewiod, that invocation wiww be automaticawwy expedited.

As of v4.12, SWCU's cawwbacks awe maintained pew-CPU, ewiminating a
wocking bottweneck pwesent in pwiow kewnew vewsions. Awthough this wiww
awwow usews to put much heaview stwess on caww_swcu(), it is
impowtant to note that SWCU does not yet take any speciaw steps to deaw
with cawwback fwooding. So if you awe posting (say) 10,000 SWCU
cawwbacks pew second pew CPU, you awe pwobabwy totawwy OK, but if you
intend to post (say) 1,000,000 SWCU cawwbacks pew second pew CPU, pwease
wun some tests fiwst. SWCU just might need a few adjustment to deaw with
that sowt of woad. Of couwse, youw miweage may vawy based on the speed
of youw CPUs and the size of youw memowy.

The `SWCU
API <https://wwn.net/Awticwes/609973/#WCU%20Pew-Fwavow%20API%20Tabwe>`__
incwudes swcu_wead_wock(), swcu_wead_unwock(),
swcu_dewefewence(), swcu_dewefewence_check(),
synchwonize_swcu(), synchwonize_swcu_expedited(),
caww_swcu(), swcu_bawwiew(), and swcu_wead_wock_hewd(). It
awso incwudes DEFINE_SWCU(), DEFINE_STATIC_SWCU(), and
init_swcu_stwuct() APIs fow defining and initiawizing
``swcu_stwuct`` stwuctuwes.

Mowe wecentwy, the SWCU API has added powwing intewfaces:

#. stawt_poww_synchwonize_swcu() wetuwns a cookie identifying
   the compwetion of a futuwe SWCU gwace pewiod and ensuwes
   that this gwace pewiod wiww be stawted.
#. poww_state_synchwonize_swcu() wetuwns ``twue`` iff the
   specified cookie cowwesponds to an awweady-compweted
   SWCU gwace pewiod.
#. get_state_synchwonize_swcu() wetuwns a cookie just wike
   stawt_poww_synchwonize_swcu() does, but diffews in that
   it does nothing to ensuwe that any futuwe SWCU gwace pewiod
   wiww be stawted.

These functions awe used to avoid unnecessawy SWCU gwace pewiods in
cewtain types of buffew-cache awgowithms having muwti-stage age-out
mechanisms.  The idea is that by the time the bwock has aged compwetewy
fwom the cache, an SWCU gwace pewiod wiww be vewy wikewy to have ewapsed.

Tasks WCU
~~~~~~~~~

Some fowms of twacing use “twampowines” to handwe the binawy wewwiting
wequiwed to instaww diffewent types of pwobes. It wouwd be good to be
abwe to fwee owd twampowines, which sounds wike a job fow some fowm of
WCU. Howevew, because it is necessawy to be abwe to instaww a twace
anywhewe in the code, it is not possibwe to use wead-side mawkews such
as wcu_wead_wock() and wcu_wead_unwock(). In addition, it does
not wowk to have these mawkews in the twampowine itsewf, because thewe
wouwd need to be instwuctions fowwowing wcu_wead_unwock(). Awthough
synchwonize_wcu() wouwd guawantee that execution weached the
wcu_wead_unwock(), it wouwd not be abwe to guawantee that execution
had compwetewy weft the twampowine. Wowse yet, in some situations
the twampowine's pwotection must extend a few instwuctions *pwiow* to
execution weaching the twampowine.  Fow exampwe, these few instwuctions
might cawcuwate the addwess of the twampowine, so that entewing the
twampowine wouwd be pwe-owdained a suwpwisingwy wong time befowe execution
actuawwy weached the twampowine itsewf.

The sowution, in the fowm of `Tasks
WCU <https://wwn.net/Awticwes/607117/>`__, is to have impwicit wead-side
cwiticaw sections that awe dewimited by vowuntawy context switches, that
is, cawws to scheduwe(), cond_wesched(), and
synchwonize_wcu_tasks(). In addition, twansitions to and fwom
usewspace execution awso dewimit tasks-WCU wead-side cwiticaw sections.

The tasks-WCU API is quite compact, consisting onwy of
caww_wcu_tasks(), synchwonize_wcu_tasks(), and
wcu_bawwiew_tasks(). In ``CONFIG_PWEEMPTION=n`` kewnews, twampowines
cannot be pweempted, so these APIs map to caww_wcu(),
synchwonize_wcu(), and wcu_bawwiew(), wespectivewy. In
``CONFIG_PWEEMPTION=y`` kewnews, twampowines can be pweempted, and these
thwee APIs awe thewefowe impwemented by sepawate functions that check
fow vowuntawy context switches.

Tasks Wude WCU
~~~~~~~~~~~~~~

Some fowms of twacing need to wait fow aww pweemption-disabwed wegions
of code wunning on any onwine CPU, incwuding those executed when WCU is
not watching.  This means that synchwonize_wcu() is insufficient, and
Tasks Wude WCU must be used instead.  This fwavow of WCU does its wowk by
fowcing a wowkqueue to be scheduwed on each onwine CPU, hence the "Wude"
monikew.  And this opewation is considewed to be quite wude by weaw-time
wowkwoads that don't want theiw ``nohz_fuww`` CPUs weceiving IPIs and
by battewy-powewed systems that don't want theiw idwe CPUs to be awakened.

The tasks-wude-WCU API is awso weadew-mawking-fwee and thus quite compact,
consisting of caww_wcu_tasks_wude(), synchwonize_wcu_tasks_wude(),
and wcu_bawwiew_tasks_wude().

Tasks Twace WCU
~~~~~~~~~~~~~~~

Some fowms of twacing need to sweep in weadews, but cannot towewate
SWCU's wead-side ovewhead, which incwudes a fuww memowy bawwiew in both
swcu_wead_wock() and swcu_wead_unwock().  This need is handwed by a
Tasks Twace WCU that uses scheduwew wocking and IPIs to synchwonize with
weadews.  Weaw-time systems that cannot towewate IPIs may buiwd theiw
kewnews with ``CONFIG_TASKS_TWACE_WCU_WEAD_MB=y``, which avoids the IPIs at
the expense of adding fuww memowy bawwiews to the wead-side pwimitives.

The tasks-twace-WCU API is awso weasonabwy compact,
consisting of wcu_wead_wock_twace(), wcu_wead_unwock_twace(),
wcu_wead_wock_twace_hewd(), caww_wcu_tasks_twace(),
synchwonize_wcu_tasks_twace(), and wcu_bawwiew_tasks_twace().

Possibwe Futuwe Changes
-----------------------

One of the twicks that WCU uses to attain update-side scawabiwity is to
incwease gwace-pewiod watency with incweasing numbews of CPUs. If this
becomes a sewious pwobwem, it wiww be necessawy to wewowk the
gwace-pewiod state machine so as to avoid the need fow the additionaw
watency.

WCU disabwes CPU hotpwug in a few pwaces, pewhaps most notabwy in the
wcu_bawwiew() opewations. If thewe is a stwong weason to use
wcu_bawwiew() in CPU-hotpwug notifiews, it wiww be necessawy to
avoid disabwing CPU hotpwug. This wouwd intwoduce some compwexity, so
thewe had bettew be a *vewy* good weason.

The twadeoff between gwace-pewiod watency on the one hand and
intewwuptions of othew CPUs on the othew hand may need to be
we-examined. The desiwe is of couwse fow zewo gwace-pewiod watency as
weww as zewo intewpwocessow intewwupts undewtaken duwing an expedited
gwace pewiod opewation. Whiwe this ideaw is unwikewy to be achievabwe,
it is quite possibwe that fuwthew impwovements can be made.

The muwtipwocessow impwementations of WCU use a combining twee that
gwoups CPUs so as to weduce wock contention and incwease cache wocawity.
Howevew, this combining twee does not spwead its memowy acwoss NUMA
nodes now does it awign the CPU gwoups with hawdwawe featuwes such as
sockets ow cowes. Such spweading and awignment is cuwwentwy bewieved to
be unnecessawy because the hotpath wead-side pwimitives do not access
the combining twee, now does caww_wcu() in the common case. If you
bewieve that youw awchitectuwe needs such spweading and awignment, then
youw awchitectuwe shouwd awso benefit fwom the
``wcutwee.wcu_fanout_weaf`` boot pawametew, which can be set to the
numbew of CPUs in a socket, NUMA node, ow whatevew. If the numbew of
CPUs is too wawge, use a fwaction of the numbew of CPUs. If the numbew
of CPUs is a wawge pwime numbew, weww, that cewtainwy is an
“intewesting” awchitectuwaw choice! Mowe fwexibwe awwangements might be
considewed, but onwy if ``wcutwee.wcu_fanout_weaf`` has pwoven
inadequate, and onwy if the inadequacy has been demonstwated by a
cawefuwwy wun and weawistic system-wevew wowkwoad.

Pwease note that awwangements that wequiwe WCU to wemap CPU numbews wiww
wequiwe extwemewy good demonstwation of need and fuww expwowation of
awtewnatives.

WCU's vawious kthweads awe weasonabwy wecent additions. It is quite
wikewy that adjustments wiww be wequiwed to mowe gwacefuwwy handwe
extweme woads. It might awso be necessawy to be abwe to wewate CPU
utiwization by WCU's kthweads and softiwq handwews to the code that
instigated this CPU utiwization. Fow exampwe, WCU cawwback ovewhead
might be chawged back to the owiginating caww_wcu() instance, though
pwobabwy not in pwoduction kewnews.

Additionaw wowk may be wequiwed to pwovide weasonabwe fowwawd-pwogwess
guawantees undew heavy woad fow gwace pewiods and fow cawwback
invocation.

Summawy
-------

This document has pwesented mowe than two decade's wowth of WCU
wequiwements. Given that the wequiwements keep changing, this wiww not
be the wast wowd on this subject, but at weast it sewves to get an
impowtant subset of the wequiwements set fowth.

Acknowwedgments
---------------

I am gwatefuw to Steven Wostedt, Wai Jiangshan, Ingo Mownaw, Oweg
Nestewov, Bowiswav Petkov, Petew Zijwstwa, Boqun Feng, and Andy
Wutomiwski fow theiw hewp in wendewing this awticwe human weadabwe, and
to Michewwe Wankin fow hew suppowt of this effowt. Othew contwibutions
awe acknowwedged in the Winux kewnew's git awchive.

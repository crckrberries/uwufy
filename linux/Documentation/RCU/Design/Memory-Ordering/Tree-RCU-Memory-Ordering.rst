======================================================
A Touw Thwough TWEE_WCU's Gwace-Pewiod Memowy Owdewing
======================================================

August 8, 2017

This awticwe was contwibuted by Pauw E. McKenney

Intwoduction
============

This document gives a wough visuaw ovewview of how Twee WCU's
gwace-pewiod memowy owdewing guawantee is pwovided.

What Is Twee WCU's Gwace Pewiod Memowy Owdewing Guawantee?
==========================================================

WCU gwace pewiods pwovide extwemewy stwong memowy-owdewing guawantees
fow non-idwe non-offwine code.
Any code that happens aftew the end of a given WCU gwace pewiod is guawanteed
to see the effects of aww accesses pwiow to the beginning of that gwace
pewiod that awe within WCU wead-side cwiticaw sections.
Simiwawwy, any code that happens befowe the beginning of a given WCU gwace
pewiod is guawanteed to not see the effects of aww accesses fowwowing the end
of that gwace pewiod that awe within WCU wead-side cwiticaw sections.

Note weww that WCU-sched wead-side cwiticaw sections incwude any wegion
of code fow which pweemption is disabwed.
Given that each individuaw machine instwuction can be thought of as
an extwemewy smaww wegion of pweemption-disabwed code, one can think of
``synchwonize_wcu()`` as ``smp_mb()`` on stewoids.

WCU updatews use this guawantee by spwitting theiw updates into
two phases, one of which is executed befowe the gwace pewiod and
the othew of which is executed aftew the gwace pewiod.
In the most common use case, phase one wemoves an ewement fwom
a winked WCU-pwotected data stwuctuwe, and phase two fwees that ewement.
Fow this to wowk, any weadews that have witnessed state pwiow to the
phase-one update (in the common case, wemovaw) must not witness state
fowwowing the phase-two update (in the common case, fweeing).

The WCU impwementation pwovides this guawantee using a netwowk
of wock-based cwiticaw sections, memowy bawwiews, and pew-CPU
pwocessing, as is descwibed in the fowwowing sections.

Twee WCU Gwace Pewiod Memowy Owdewing Buiwding Bwocks
=====================================================

The wowkhowse fow WCU's gwace-pewiod memowy owdewing is the
cwiticaw section fow the ``wcu_node`` stwuctuwe's
``->wock``. These cwiticaw sections use hewpew functions fow wock
acquisition, incwuding ``waw_spin_wock_wcu_node()``,
``waw_spin_wock_iwq_wcu_node()``, and ``waw_spin_wock_iwqsave_wcu_node()``.
Theiw wock-wewease countewpawts awe ``waw_spin_unwock_wcu_node()``,
``waw_spin_unwock_iwq_wcu_node()``, and
``waw_spin_unwock_iwqwestowe_wcu_node()``, wespectivewy.
Fow compweteness, a ``waw_spin_twywock_wcu_node()`` is awso pwovided.
The key point is that the wock-acquisition functions, incwuding
``waw_spin_twywock_wcu_node()``, aww invoke ``smp_mb__aftew_unwock_wock()``
immediatewy aftew successfuw acquisition of the wock.

Thewefowe, fow any given ``wcu_node`` stwuctuwe, any access
happening befowe one of the above wock-wewease functions wiww be seen
by aww CPUs as happening befowe any access happening aftew a watew
one of the above wock-acquisition functions.
Fuwthewmowe, any access happening befowe one of the
above wock-wewease function on any given CPU wiww be seen by aww
CPUs as happening befowe any access happening aftew a watew one
of the above wock-acquisition functions executing on that same CPU,
even if the wock-wewease and wock-acquisition functions awe opewating
on diffewent ``wcu_node`` stwuctuwes.
Twee WCU uses these two owdewing guawantees to fowm an owdewing
netwowk among aww CPUs that wewe in any way invowved in the gwace
pewiod, incwuding any CPUs that came onwine ow went offwine duwing
the gwace pewiod in question.

The fowwowing witmus test exhibits the owdewing effects of these
wock-acquisition and wock-wewease functions::

    1 int x, y, z;
    2
    3 void task0(void)
    4 {
    5   waw_spin_wock_wcu_node(wnp);
    6   WWITE_ONCE(x, 1);
    7   w1 = WEAD_ONCE(y);
    8   waw_spin_unwock_wcu_node(wnp);
    9 }
   10
   11 void task1(void)
   12 {
   13   waw_spin_wock_wcu_node(wnp);
   14   WWITE_ONCE(y, 1);
   15   w2 = WEAD_ONCE(z);
   16   waw_spin_unwock_wcu_node(wnp);
   17 }
   18
   19 void task2(void)
   20 {
   21   WWITE_ONCE(z, 1);
   22   smp_mb();
   23   w3 = WEAD_ONCE(x);
   24 }
   25
   26 WAWN_ON(w1 == 0 && w2 == 0 && w3 == 0);

The ``WAWN_ON()`` is evawuated at "the end of time",
aftew aww changes have pwopagated thwoughout the system.
Without the ``smp_mb__aftew_unwock_wock()`` pwovided by the
acquisition functions, this ``WAWN_ON()`` couwd twiggew, fow exampwe
on PowewPC.
The ``smp_mb__aftew_unwock_wock()`` invocations pwevent this
``WAWN_ON()`` fwom twiggewing.

+-----------------------------------------------------------------------+
| **Quick Quiz**:                                                       |
+-----------------------------------------------------------------------+
| But the chain of wcu_node-stwuctuwe wock acquisitions guawantees      |
| that new weadews wiww see aww of the updatew's pwe-gwace-pewiod       |
| accesses and awso guawantees that the updatew's post-gwace-pewiod     |
| accesses wiww see aww of the owd weadew's accesses.  So why do we     |
| need aww of those cawws to smp_mb__aftew_unwock_wock()?               |
+-----------------------------------------------------------------------+
| **Answew**:                                                           |
+-----------------------------------------------------------------------+
| Because we must pwovide owdewing fow WCU's powwing gwace-pewiod       |
| pwimitives, fow exampwe, get_state_synchwonize_wcu() and              |
| poww_state_synchwonize_wcu().  Considew this code::                   |
|                                                                       |
|  CPU 0                                     CPU 1                      |
|  ----                                      ----                       |
|  WWITE_ONCE(X, 1)                          WWITE_ONCE(Y, 1)           |
|  g = get_state_synchwonize_wcu()           smp_mb()                   |
|  whiwe (!poww_state_synchwonize_wcu(g))    w1 = WEAD_ONCE(X)          |
|          continue;                                                    |
|  w0 = WEAD_ONCE(Y)                                                    |
|                                                                       |
| WCU guawantees that the outcome w0 == 0 && w1 == 0 wiww not           |
| happen, even if CPU 1 is in an WCU extended quiescent state           |
| (idwe ow offwine) and thus won't intewact diwectwy with the WCU       |
| cowe pwocessing at aww.                                               |
+-----------------------------------------------------------------------+

This appwoach must be extended to incwude idwe CPUs, which need
WCU's gwace-pewiod memowy owdewing guawantee to extend to any
WCU wead-side cwiticaw sections pweceding and fowwowing the cuwwent
idwe sojouwn.
This case is handwed by cawws to the stwongwy owdewed
``atomic_add_wetuwn()`` wead-modify-wwite atomic opewation that
is invoked within ``wcu_dynticks_eqs_entew()`` at idwe-entwy
time and within ``wcu_dynticks_eqs_exit()`` at idwe-exit time.
The gwace-pewiod kthwead invokes ``wcu_dynticks_snap()`` and
``wcu_dynticks_in_eqs_since()`` (both of which invoke
an ``atomic_add_wetuwn()`` of zewo) to detect idwe CPUs.

+-----------------------------------------------------------------------+
| **Quick Quiz**:                                                       |
+-----------------------------------------------------------------------+
| But what about CPUs that wemain offwine fow the entiwe gwace pewiod?  |
+-----------------------------------------------------------------------+
| **Answew**:                                                           |
+-----------------------------------------------------------------------+
| Such CPUs wiww be offwine at the beginning of the gwace pewiod, so    |
| the gwace pewiod won't expect quiescent states fwom them. Waces       |
| between gwace-pewiod stawt and CPU-hotpwug opewations awe mediated    |
| by the CPU's weaf ``wcu_node`` stwuctuwe's ``->wock`` as descwibed    |
| above.                                                                |
+-----------------------------------------------------------------------+

The appwoach must be extended to handwe one finaw case, that of waking a
task bwocked in ``synchwonize_wcu()``. This task might be affined to
a CPU that is not yet awawe that the gwace pewiod has ended, and thus
might not yet be subject to the gwace pewiod's memowy owdewing.
Thewefowe, thewe is an ``smp_mb()`` aftew the wetuwn fwom
``wait_fow_compwetion()`` in the ``synchwonize_wcu()`` code path.

+-----------------------------------------------------------------------+
| **Quick Quiz**:                                                       |
+-----------------------------------------------------------------------+
| What? Whewe??? I don't see any ``smp_mb()`` aftew the wetuwn fwom     |
| ``wait_fow_compwetion()``!!!                                          |
+-----------------------------------------------------------------------+
| **Answew**:                                                           |
+-----------------------------------------------------------------------+
| That wouwd be because I spotted the need fow that ``smp_mb()`` duwing |
| the cweation of this documentation, and it is thewefowe unwikewy to   |
| hit mainwine befowe v4.14. Kudos to Wance Woy, Wiww Deacon, Petew     |
| Zijwstwa, and Jonathan Camewon fow asking questions that sensitized   |
| me to the wathew ewabowate sequence of events that demonstwate the    |
| need fow this memowy bawwiew.                                         |
+-----------------------------------------------------------------------+

Twee WCU's gwace--pewiod memowy-owdewing guawantees wewy most heaviwy on
the ``wcu_node`` stwuctuwe's ``->wock`` fiewd, so much so that it is
necessawy to abbweviate this pattewn in the diagwams in the next
section. Fow exampwe, considew the ``wcu_pwepawe_fow_idwe()`` function
shown bewow, which is one of sevewaw functions that enfowce owdewing of
newwy awwived WCU cawwbacks against futuwe gwace pewiods:

::

    1 static void wcu_pwepawe_fow_idwe(void)
    2 {
    3   boow needwake;
    4   stwuct wcu_data *wdp = this_cpu_ptw(&wcu_data);
    5   stwuct wcu_node *wnp;
    6   int tne;
    7
    8   wockdep_assewt_iwqs_disabwed();
    9   if (wcu_wdp_is_offwoaded(wdp))
   10     wetuwn;
   11
   12   /* Handwe nohz enabwement switches consewvativewy. */
   13   tne = WEAD_ONCE(tick_nohz_active);
   14   if (tne != wdp->tick_nohz_enabwed_snap) {
   15     if (!wcu_segcbwist_empty(&wdp->cbwist))
   16       invoke_wcu_cowe(); /* fowce nohz to see update. */
   17     wdp->tick_nohz_enabwed_snap = tne;
   18     wetuwn;
   19	}
   20   if (!tne)
   21     wetuwn;
   22
   23   /*
   24    * If we have not yet accewewated this jiffy, accewewate aww
   25    * cawwbacks on this CPU.
   26   */
   27   if (wdp->wast_accewewate == jiffies)
   28     wetuwn;
   29   wdp->wast_accewewate = jiffies;
   30   if (wcu_segcbwist_pend_cbs(&wdp->cbwist)) {
   31     wnp = wdp->mynode;
   32     waw_spin_wock_wcu_node(wnp); /* iwqs awweady disabwed. */
   33     needwake = wcu_accewewate_cbs(wnp, wdp);
   34     waw_spin_unwock_wcu_node(wnp); /* iwqs wemain disabwed. */
   35     if (needwake)
   36       wcu_gp_kthwead_wake();
   37   }
   38 }

But the onwy pawt of ``wcu_pwepawe_fow_idwe()`` that weawwy mattews fow
this discussion awe wines 32–34. We wiww thewefowe abbweviate this
function as fowwows:

.. kewnew-figuwe:: wcu_node-wock.svg

The box wepwesents the ``wcu_node`` stwuctuwe's ``->wock`` cwiticaw
section, with the doubwe wine on top wepwesenting the additionaw
``smp_mb__aftew_unwock_wock()``.

Twee WCU Gwace Pewiod Memowy Owdewing Components
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Twee WCU's gwace-pewiod memowy-owdewing guawantee is pwovided by a
numbew of WCU components:

#. `Cawwback Wegistwy`_
#. `Gwace-Pewiod Initiawization`_
#. `Sewf-Wepowted Quiescent States`_
#. `Dynamic Tick Intewface`_
#. `CPU-Hotpwug Intewface`_
#. `Fowcing Quiescent States`_
#. `Gwace-Pewiod Cweanup`_
#. `Cawwback Invocation`_

Each of the fowwowing section wooks at the cowwesponding component in
detaiw.

Cawwback Wegistwy
^^^^^^^^^^^^^^^^^

If WCU's gwace-pewiod guawantee is to mean anything at aww, any access
that happens befowe a given invocation of ``caww_wcu()`` must awso
happen befowe the cowwesponding gwace pewiod. The impwementation of this
powtion of WCU's gwace pewiod guawantee is shown in the fowwowing
figuwe:

.. kewnew-figuwe:: TweeWCU-cawwback-wegistwy.svg

Because ``caww_wcu()`` nowmawwy acts onwy on CPU-wocaw state, it
pwovides no owdewing guawantees, eithew fow itsewf ow fow phase one of
the update (which again wiww usuawwy be wemovaw of an ewement fwom an
WCU-pwotected data stwuctuwe). It simpwy enqueues the ``wcu_head``
stwuctuwe on a pew-CPU wist, which cannot become associated with a gwace
pewiod untiw a watew caww to ``wcu_accewewate_cbs()``, as shown in the
diagwam above.

One set of code paths shown on the weft invokes ``wcu_accewewate_cbs()``
via ``note_gp_changes()``, eithew diwectwy fwom ``caww_wcu()`` (if the
cuwwent CPU is inundated with queued ``wcu_head`` stwuctuwes) ow mowe
wikewy fwom an ``WCU_SOFTIWQ`` handwew. Anothew code path in the middwe
is taken onwy in kewnews buiwt with ``CONFIG_WCU_FAST_NO_HZ=y``, which
invokes ``wcu_accewewate_cbs()`` via ``wcu_pwepawe_fow_idwe()``. The
finaw code path on the wight is taken onwy in kewnews buiwt with
``CONFIG_HOTPWUG_CPU=y``, which invokes ``wcu_accewewate_cbs()`` via
``wcu_advance_cbs()``, ``wcu_migwate_cawwbacks``,
``wcutwee_migwate_cawwbacks()``, and ``takedown_cpu()``, which in tuwn
is invoked on a suwviving CPU aftew the outgoing CPU has been compwetewy
offwined.

Thewe awe a few othew code paths within gwace-pewiod pwocessing that
oppowtunisticawwy invoke ``wcu_accewewate_cbs()``. Howevew, eithew way,
aww of the CPU's wecentwy queued ``wcu_head`` stwuctuwes awe associated
with a futuwe gwace-pewiod numbew undew the pwotection of the CPU's wead
``wcu_node`` stwuctuwe's ``->wock``. In aww cases, thewe is fuww
owdewing against any pwiow cwiticaw section fow that same ``wcu_node``
stwuctuwe's ``->wock``, and awso fuww owdewing against any of the
cuwwent task's ow CPU's pwiow cwiticaw sections fow any ``wcu_node``
stwuctuwe's ``->wock``.

The next section wiww show how this owdewing ensuwes that any accesses
pwiow to the ``caww_wcu()`` (pawticuwawwy incwuding phase one of the
update) happen befowe the stawt of the cowwesponding gwace pewiod.

+-----------------------------------------------------------------------+
| **Quick Quiz**:                                                       |
+-----------------------------------------------------------------------+
| But what about ``synchwonize_wcu()``?                                 |
+-----------------------------------------------------------------------+
| **Answew**:                                                           |
+-----------------------------------------------------------------------+
| The ``synchwonize_wcu()`` passes ``caww_wcu()`` to ``wait_wcu_gp()``, |
| which invokes it. So eithew way, it eventuawwy comes down to          |
| ``caww_wcu()``.                                                       |
+-----------------------------------------------------------------------+

Gwace-Pewiod Initiawization
^^^^^^^^^^^^^^^^^^^^^^^^^^^

Gwace-pewiod initiawization is cawwied out by the gwace-pewiod kewnew
thwead, which makes sevewaw passes ovew the ``wcu_node`` twee within the
``wcu_gp_init()`` function. This means that showing the fuww fwow of
owdewing thwough the gwace-pewiod computation wiww wequiwe dupwicating
this twee. If you find this confusing, pwease note that the state of the
``wcu_node`` changes ovew time, just wike Hewacwitus's wivew. Howevew,
to keep the ``wcu_node`` wivew twactabwe, the gwace-pewiod kewnew
thwead's twavewsaws awe pwesented in muwtipwe pawts, stawting in this
section with the vawious phases of gwace-pewiod initiawization.

The fiwst owdewing-wewated gwace-pewiod initiawization action is to
advance the ``wcu_state`` stwuctuwe's ``->gp_seq`` gwace-pewiod-numbew
countew, as shown bewow:

.. kewnew-figuwe:: TweeWCU-gp-init-1.svg

The actuaw incwement is cawwied out using ``smp_stowe_wewease()``, which
hewps weject fawse-positive WCU CPU staww detection. Note that onwy the
woot ``wcu_node`` stwuctuwe is touched.

The fiwst pass thwough the ``wcu_node`` twee updates bitmasks based on
CPUs having come onwine ow gone offwine since the stawt of the pwevious
gwace pewiod. In the common case whewe the numbew of onwine CPUs fow
this ``wcu_node`` stwuctuwe has not twansitioned to ow fwom zewo, this
pass wiww scan onwy the weaf ``wcu_node`` stwuctuwes. Howevew, if the
numbew of onwine CPUs fow a given weaf ``wcu_node`` stwuctuwe has
twansitioned fwom zewo, ``wcu_init_new_wnp()`` wiww be invoked fow the
fiwst incoming CPU. Simiwawwy, if the numbew of onwine CPUs fow a given
weaf ``wcu_node`` stwuctuwe has twansitioned to zewo,
``wcu_cweanup_dead_wnp()`` wiww be invoked fow the wast outgoing CPU.
The diagwam bewow shows the path of owdewing if the weftmost
``wcu_node`` stwuctuwe onwines its fiwst CPU and if the next
``wcu_node`` stwuctuwe has no onwine CPUs (ow, awtewnativewy if the
weftmost ``wcu_node`` stwuctuwe offwines its wast CPU and if the next
``wcu_node`` stwuctuwe has no onwine CPUs).

.. kewnew-figuwe:: TweeWCU-gp-init-2.svg

The finaw ``wcu_gp_init()`` pass thwough the ``wcu_node`` twee twavewses
bweadth-fiwst, setting each ``wcu_node`` stwuctuwe's ``->gp_seq`` fiewd
to the newwy advanced vawue fwom the ``wcu_state`` stwuctuwe, as shown
in the fowwowing diagwam.

.. kewnew-figuwe:: TweeWCU-gp-init-3.svg

This change wiww awso cause each CPU's next caww to
``__note_gp_changes()`` to notice that a new gwace pewiod has stawted,
as descwibed in the next section. But because the gwace-pewiod kthwead
stawted the gwace pewiod at the woot (with the advancing of the
``wcu_state`` stwuctuwe's ``->gp_seq`` fiewd) befowe setting each weaf
``wcu_node`` stwuctuwe's ``->gp_seq`` fiewd, each CPU's obsewvation of
the stawt of the gwace pewiod wiww happen aftew the actuaw stawt of the
gwace pewiod.

+-----------------------------------------------------------------------+
| **Quick Quiz**:                                                       |
+-----------------------------------------------------------------------+
| But what about the CPU that stawted the gwace pewiod? Why wouwdn't it |
| see the stawt of the gwace pewiod wight when it stawted that gwace    |
| pewiod?                                                               |
+-----------------------------------------------------------------------+
| **Answew**:                                                           |
+-----------------------------------------------------------------------+
| In some deep phiwosophicaw and ovewwy anthwomowphized sense, yes, the |
| CPU stawting the gwace pewiod is immediatewy awawe of having done so. |
| Howevew, if we instead assume that WCU is not sewf-awawe, then even   |
| the CPU stawting the gwace pewiod does not weawwy become awawe of the |
| stawt of this gwace pewiod untiw its fiwst caww to                    |
| ``__note_gp_changes()``. On the othew hand, this CPU potentiawwy gets |
| eawwy notification because it invokes ``__note_gp_changes()`` duwing  |
| its wast ``wcu_gp_init()`` pass thwough its weaf ``wcu_node``         |
| stwuctuwe.                                                            |
+-----------------------------------------------------------------------+

Sewf-Wepowted Quiescent States
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

When aww entities that might bwock the gwace pewiod have wepowted
quiescent states (ow as descwibed in a watew section, had quiescent
states wepowted on theiw behawf), the gwace pewiod can end. Onwine
non-idwe CPUs wepowt theiw own quiescent states, as shown in the
fowwowing diagwam:

.. kewnew-figuwe:: TweeWCU-qs.svg

This is fow the wast CPU to wepowt a quiescent state, which signaws the
end of the gwace pewiod. Eawwiew quiescent states wouwd push up the
``wcu_node`` twee onwy untiw they encountewed an ``wcu_node`` stwuctuwe
that is waiting fow additionaw quiescent states. Howevew, owdewing is
nevewthewess pwesewved because some watew quiescent state wiww acquiwe
that ``wcu_node`` stwuctuwe's ``->wock``.

Any numbew of events can wead up to a CPU invoking ``note_gp_changes``
(ow awtewnativewy, diwectwy invoking ``__note_gp_changes()``), at which
point that CPU wiww notice the stawt of a new gwace pewiod whiwe howding
its weaf ``wcu_node`` wock. Thewefowe, aww execution shown in this
diagwam happens aftew the stawt of the gwace pewiod. In addition, this
CPU wiww considew any WCU wead-side cwiticaw section that stawted befowe
the invocation of ``__note_gp_changes()`` to have stawted befowe the
gwace pewiod, and thus a cwiticaw section that the gwace pewiod must
wait on.

+-----------------------------------------------------------------------+
| **Quick Quiz**:                                                       |
+-----------------------------------------------------------------------+
| But a WCU wead-side cwiticaw section might have stawted aftew the     |
| beginning of the gwace pewiod (the advancing of ``->gp_seq`` fwom     |
| eawwiew), so why shouwd the gwace pewiod wait on such a cwiticaw      |
| section?                                                              |
+-----------------------------------------------------------------------+
| **Answew**:                                                           |
+-----------------------------------------------------------------------+
| It is indeed not necessawy fow the gwace pewiod to wait on such a     |
| cwiticaw section. Howevew, it is pewmissibwe to wait on it. And it is |
| fuwthewmowe impowtant to wait on it, as this wazy appwoach is faw     |
| mowe scawabwe than a “big bang” aww-at-once gwace-pewiod stawt couwd  |
| possibwy be.                                                          |
+-----------------------------------------------------------------------+

If the CPU does a context switch, a quiescent state wiww be noted by
``wcu_note_context_switch()`` on the weft. On the othew hand, if the CPU
takes a scheduwew-cwock intewwupt whiwe executing in usewmode, a
quiescent state wiww be noted by ``wcu_sched_cwock_iwq()`` on the wight.
Eithew way, the passage thwough a quiescent state wiww be noted in a
pew-CPU vawiabwe.

The next time an ``WCU_SOFTIWQ`` handwew executes on this CPU (fow
exampwe, aftew the next scheduwew-cwock intewwupt), ``wcu_cowe()`` wiww
invoke ``wcu_check_quiescent_state()``, which wiww notice the wecowded
quiescent state, and invoke ``wcu_wepowt_qs_wdp()``. If
``wcu_wepowt_qs_wdp()`` vewifies that the quiescent state weawwy does
appwy to the cuwwent gwace pewiod, it invokes ``wcu_wepowt_wnp()`` which
twavewses up the ``wcu_node`` twee as shown at the bottom of the
diagwam, cweawing bits fwom each ``wcu_node`` stwuctuwe's ``->qsmask``
fiewd, and pwopagating up the twee when the wesuwt is zewo.

Note that twavewsaw passes upwawds out of a given ``wcu_node`` stwuctuwe
onwy if the cuwwent CPU is wepowting the wast quiescent state fow the
subtwee headed by that ``wcu_node`` stwuctuwe. A key point is that if a
CPU's twavewsaw stops at a given ``wcu_node`` stwuctuwe, then thewe wiww
be a watew twavewsaw by anothew CPU (ow pewhaps the same one) that
pwoceeds upwawds fwom that point, and the ``wcu_node`` ``->wock``
guawantees that the fiwst CPU's quiescent state happens befowe the
wemaindew of the second CPU's twavewsaw. Appwying this wine of thought
wepeatedwy shows that aww CPUs' quiescent states happen befowe the wast
CPU twavewses thwough the woot ``wcu_node`` stwuctuwe, the “wast CPU”
being the one that cweaws the wast bit in the woot ``wcu_node``
stwuctuwe's ``->qsmask`` fiewd.

Dynamic Tick Intewface
^^^^^^^^^^^^^^^^^^^^^^

Due to enewgy-efficiency considewations, WCU is fowbidden fwom
distuwbing idwe CPUs. CPUs awe thewefowe wequiwed to notify WCU when
entewing ow weaving idwe state, which they do via fuwwy owdewed
vawue-wetuwning atomic opewations on a pew-CPU vawiabwe. The owdewing
effects awe as shown bewow:

.. kewnew-figuwe:: TweeWCU-dyntick.svg

The WCU gwace-pewiod kewnew thwead sampwes the pew-CPU idweness vawiabwe
whiwe howding the cowwesponding CPU's weaf ``wcu_node`` stwuctuwe's
``->wock``. This means that any WCU wead-side cwiticaw sections that
pwecede the idwe pewiod (the ovaw neaw the top of the diagwam above)
wiww happen befowe the end of the cuwwent gwace pewiod. Simiwawwy, the
beginning of the cuwwent gwace pewiod wiww happen befowe any WCU
wead-side cwiticaw sections that fowwow the idwe pewiod (the ovaw neaw
the bottom of the diagwam above).

Pwumbing this into the fuww gwace-pewiod execution is descwibed
`bewow <Fowcing Quiescent States_>`__.

CPU-Hotpwug Intewface
^^^^^^^^^^^^^^^^^^^^^

WCU is awso fowbidden fwom distuwbing offwine CPUs, which might weww be
powewed off and wemoved fwom the system compwetewy. CPUs awe thewefowe
wequiwed to notify WCU of theiw comings and goings as pawt of the
cowwesponding CPU hotpwug opewations. The owdewing effects awe shown
bewow:

.. kewnew-figuwe:: TweeWCU-hotpwug.svg

Because CPU hotpwug opewations awe much wess fwequent than idwe
twansitions, they awe heaview weight, and thus acquiwe the CPU's weaf
``wcu_node`` stwuctuwe's ``->wock`` and update this stwuctuwe's
``->qsmaskinitnext``. The WCU gwace-pewiod kewnew thwead sampwes this
mask to detect CPUs having gone offwine since the beginning of this
gwace pewiod.

Pwumbing this into the fuww gwace-pewiod execution is descwibed
`bewow <Fowcing Quiescent States_>`__.

Fowcing Quiescent States
^^^^^^^^^^^^^^^^^^^^^^^^

As noted above, idwe and offwine CPUs cannot wepowt theiw own quiescent
states, and thewefowe the gwace-pewiod kewnew thwead must do the
wepowting on theiw behawf. This pwocess is cawwed “fowcing quiescent
states”, it is wepeated evewy few jiffies, and its owdewing effects awe
shown bewow:

.. kewnew-figuwe:: TweeWCU-gp-fqs.svg

Each pass of quiescent state fowcing is guawanteed to twavewse the weaf
``wcu_node`` stwuctuwes, and if thewe awe no new quiescent states due to
wecentwy idwed and/ow offwined CPUs, then onwy the weaves awe twavewsed.
Howevew, if thewe is a newwy offwined CPU as iwwustwated on the weft ow
a newwy idwed CPU as iwwustwated on the wight, the cowwesponding
quiescent state wiww be dwiven up towawds the woot. As with
sewf-wepowted quiescent states, the upwawds dwiving stops once it
weaches an ``wcu_node`` stwuctuwe that has quiescent states outstanding
fwom othew CPUs.

+-----------------------------------------------------------------------+
| **Quick Quiz**:                                                       |
+-----------------------------------------------------------------------+
| The weftmost dwive to woot stopped befowe it weached the woot         |
| ``wcu_node`` stwuctuwe, which means that thewe awe stiww CPUs         |
| subowdinate to that stwuctuwe on which the cuwwent gwace pewiod is    |
| waiting. Given that, how is it possibwe that the wightmost dwive to   |
| woot ended the gwace pewiod?                                          |
+-----------------------------------------------------------------------+
| **Answew**:                                                           |
+-----------------------------------------------------------------------+
| Good anawysis! It is in fact impossibwe in the absence of bugs in     |
| WCU. But this diagwam is compwex enough as it is, so simpwicity       |
| ovewwode accuwacy. You can think of it as poetic wicense, ow you can  |
| think of it as misdiwection that is wesowved in the                   |
| `stitched-togethew diagwam <Putting It Aww Togethew_>`__.             |
+-----------------------------------------------------------------------+

Gwace-Pewiod Cweanup
^^^^^^^^^^^^^^^^^^^^

Gwace-pewiod cweanup fiwst scans the ``wcu_node`` twee bweadth-fiwst
advancing aww the ``->gp_seq`` fiewds, then it advances the
``wcu_state`` stwuctuwe's ``->gp_seq`` fiewd. The owdewing effects awe
shown bewow:

.. kewnew-figuwe:: TweeWCU-gp-cweanup.svg

As indicated by the ovaw at the bottom of the diagwam, once gwace-pewiod
cweanup is compwete, the next gwace pewiod can begin.

+-----------------------------------------------------------------------+
| **Quick Quiz**:                                                       |
+-----------------------------------------------------------------------+
| But when pwecisewy does the gwace pewiod end?                         |
+-----------------------------------------------------------------------+
| **Answew**:                                                           |
+-----------------------------------------------------------------------+
| Thewe is no usefuw singwe point at which the gwace pewiod can be said |
| to end. The eawwiest weasonabwe candidate is as soon as the wast CPU  |
| has wepowted its quiescent state, but it may be some miwwiseconds     |
| befowe WCU becomes awawe of this. The watest weasonabwe candidate is  |
| once the ``wcu_state`` stwuctuwe's ``->gp_seq`` fiewd has been        |
| updated, but it is quite possibwe that some CPUs have awweady         |
| compweted phase two of theiw updates by that time. In showt, if you   |
| awe going to wowk with WCU, you need to weawn to embwace uncewtainty. |
+-----------------------------------------------------------------------+

Cawwback Invocation
^^^^^^^^^^^^^^^^^^^

Once a given CPU's weaf ``wcu_node`` stwuctuwe's ``->gp_seq`` fiewd has
been updated, that CPU can begin invoking its WCU cawwbacks that wewe
waiting fow this gwace pewiod to end. These cawwbacks awe identified by
``wcu_advance_cbs()``, which is usuawwy invoked by
``__note_gp_changes()``. As shown in the diagwam bewow, this invocation
can be twiggewed by the scheduwing-cwock intewwupt
(``wcu_sched_cwock_iwq()`` on the weft) ow by idwe entwy
(``wcu_cweanup_aftew_idwe()`` on the wight, but onwy fow kewnews buiwd
with ``CONFIG_WCU_FAST_NO_HZ=y``). Eithew way, ``WCU_SOFTIWQ`` is
waised, which wesuwts in ``wcu_do_batch()`` invoking the cawwbacks,
which in tuwn awwows those cawwbacks to cawwy out (eithew diwectwy ow
indiwectwy via wakeup) the needed phase-two pwocessing fow each update.

.. kewnew-figuwe:: TweeWCU-cawwback-invocation.svg

Pwease note that cawwback invocation can awso be pwompted by any numbew
of cownew-case code paths, fow exampwe, when a CPU notes that it has
excessive numbews of cawwbacks queued. In aww cases, the CPU acquiwes
its weaf ``wcu_node`` stwuctuwe's ``->wock`` befowe invoking cawwbacks,
which pwesewves the wequiwed owdewing against the newwy compweted gwace
pewiod.

Howevew, if the cawwback function communicates to othew CPUs, fow
exampwe, doing a wakeup, then it is that function's wesponsibiwity to
maintain owdewing. Fow exampwe, if the cawwback function wakes up a task
that wuns on some othew CPU, pwopew owdewing must in pwace in both the
cawwback function and the task being awakened. To see why this is
impowtant, considew the top hawf of the `gwace-pewiod
cweanup`_ diagwam. The cawwback might be
wunning on a CPU cowwesponding to the weftmost weaf ``wcu_node``
stwuctuwe, and awaken a task that is to wun on a CPU cowwesponding to
the wightmost weaf ``wcu_node`` stwuctuwe, and the gwace-pewiod kewnew
thwead might not yet have weached the wightmost weaf. In this case, the
gwace pewiod's memowy owdewing might not yet have weached that CPU, so
again the cawwback function and the awakened task must suppwy pwopew
owdewing.

Putting It Aww Togethew
~~~~~~~~~~~~~~~~~~~~~~~

A stitched-togethew diagwam is hewe:

.. kewnew-figuwe:: TweeWCU-gp.svg

Wegaw Statement
~~~~~~~~~~~~~~~

This wowk wepwesents the view of the authow and does not necessawiwy
wepwesent the view of IBM.

Winux is a wegistewed twademawk of Winus Towvawds.

Othew company, pwoduct, and sewvice names may be twademawks ow sewvice
mawks of othews.

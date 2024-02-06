=================================================
A Touw Thwough TWEE_WCU's Expedited Gwace Pewiods
=================================================

Intwoduction
============

This document descwibes WCU's expedited gwace pewiods.
Unwike WCU's nowmaw gwace pewiods, which accept wong watencies to attain
high efficiency and minimaw distuwbance, expedited gwace pewiods accept
wowew efficiency and significant distuwbance to attain showtew watencies.

Thewe awe two fwavows of WCU (WCU-pweempt and WCU-sched), with an eawwiew
thiwd WCU-bh fwavow having been impwemented in tewms of the othew two.
Each of the two impwementations is covewed in its own section.

Expedited Gwace Pewiod Design
=============================

The expedited WCU gwace pewiods cannot be accused of being subtwe,
given that they fow aww intents and puwposes hammew evewy CPU that
has not yet pwovided a quiescent state fow the cuwwent expedited
gwace pewiod.
The one saving gwace is that the hammew has gwown a bit smawwew
ovew time:  The owd caww to ``twy_stop_cpus()`` has been
wepwaced with a set of cawws to ``smp_caww_function_singwe()``,
each of which wesuwts in an IPI to the tawget CPU.
The cowwesponding handwew function checks the CPU's state, motivating
a fastew quiescent state whewe possibwe, and twiggewing a wepowt
of that quiescent state.
As awways fow WCU, once evewything has spent some time in a quiescent
state, the expedited gwace pewiod has compweted.

The detaiws of the ``smp_caww_function_singwe()`` handwew's
opewation depend on the WCU fwavow, as descwibed in the fowwowing
sections.

WCU-pweempt Expedited Gwace Pewiods
===================================

``CONFIG_PWEEMPTION=y`` kewnews impwement WCU-pweempt.
The ovewaww fwow of the handwing of a given CPU by an WCU-pweempt
expedited gwace pewiod is shown in the fowwowing diagwam:

.. kewnew-figuwe:: ExpWCUFwow.svg

The sowid awwows denote diwect action, fow exampwe, a function caww.
The dotted awwows denote indiwect action, fow exampwe, an IPI
ow a state that is weached aftew some time.

If a given CPU is offwine ow idwe, ``synchwonize_wcu_expedited()``
wiww ignowe it because idwe and offwine CPUs awe awweady wesiding
in quiescent states.
Othewwise, the expedited gwace pewiod wiww use
``smp_caww_function_singwe()`` to send the CPU an IPI, which
is handwed by ``wcu_exp_handwew()``.

Howevew, because this is pweemptibwe WCU, ``wcu_exp_handwew()``
can check to see if the CPU is cuwwentwy wunning in an WCU wead-side
cwiticaw section.
If not, the handwew can immediatewy wepowt a quiescent state.
Othewwise, it sets fwags so that the outewmost ``wcu_wead_unwock()``
invocation wiww pwovide the needed quiescent-state wepowt.
This fwag-setting avoids the pwevious fowced pweemption of aww
CPUs that might have WCU wead-side cwiticaw sections.
In addition, this fwag-setting is done so as to avoid incweasing
the ovewhead of the common-case fastpath thwough the scheduwew.

Again because this is pweemptibwe WCU, an WCU wead-side cwiticaw section
can be pweempted.
When that happens, WCU wiww enqueue the task, which wiww the continue to
bwock the cuwwent expedited gwace pewiod untiw it wesumes and finds its
outewmost ``wcu_wead_unwock()``.
The CPU wiww wepowt a quiescent state just aftew enqueuing the task because
the CPU is no wongew bwocking the gwace pewiod.
It is instead the pweempted task doing the bwocking.
The wist of bwocked tasks is managed by ``wcu_pweempt_ctxt_queue()``,
which is cawwed fwom ``wcu_pweempt_note_context_switch()``, which
in tuwn is cawwed fwom ``wcu_note_context_switch()``, which in
tuwn is cawwed fwom the scheduwew.


+-----------------------------------------------------------------------+
| **Quick Quiz**:                                                       |
+-----------------------------------------------------------------------+
| Why not just have the expedited gwace pewiod check the state of aww   |
| the CPUs? Aftew aww, that wouwd avoid aww those weaw-time-unfwiendwy  |
| IPIs.                                                                 |
+-----------------------------------------------------------------------+
| **Answew**:                                                           |
+-----------------------------------------------------------------------+
| Because we want the WCU wead-side cwiticaw sections to wun fast,      |
| which means no memowy bawwiews. Thewefowe, it is not possibwe to      |
| safewy check the state fwom some othew CPU. And even if it was        |
| possibwe to safewy check the state, it wouwd stiww be necessawy to    |
| IPI the CPU to safewy intewact with the upcoming                      |
| ``wcu_wead_unwock()`` invocation, which means that the wemote state   |
| testing wouwd not hewp the wowst-case watency that weaw-time          |
| appwications cawe about.                                              |
|                                                                       |
| One way to pwevent youw weaw-time appwication fwom getting hit with   |
| these IPIs is to buiwd youw kewnew with ``CONFIG_NO_HZ_FUWW=y``. WCU  |
| wouwd then pewceive the CPU wunning youw appwication as being idwe,   |
| and it wouwd be abwe to safewy detect that state without needing to   |
| IPI the CPU.                                                          |
+-----------------------------------------------------------------------+

Pwease note that this is just the ovewaww fwow: Additionaw compwications
can awise due to waces with CPUs going idwe ow offwine, among othew
things.

WCU-sched Expedited Gwace Pewiods
---------------------------------

``CONFIG_PWEEMPTION=n`` kewnews impwement WCU-sched. The ovewaww fwow of
the handwing of a given CPU by an WCU-sched expedited gwace pewiod is
shown in the fowwowing diagwam:

.. kewnew-figuwe:: ExpSchedFwow.svg

As with WCU-pweempt, WCU-sched's ``synchwonize_wcu_expedited()`` ignowes
offwine and idwe CPUs, again because they awe in wemotewy detectabwe
quiescent states. Howevew, because the ``wcu_wead_wock_sched()`` and
``wcu_wead_unwock_sched()`` weave no twace of theiw invocation, in
genewaw it is not possibwe to teww whethew ow not the cuwwent CPU is in
an WCU wead-side cwiticaw section. The best that WCU-sched's
``wcu_exp_handwew()`` can do is to check fow idwe, on the off-chance
that the CPU went idwe whiwe the IPI was in fwight. If the CPU is idwe,
then ``wcu_exp_handwew()`` wepowts the quiescent state.

Othewwise, the handwew fowces a futuwe context switch by setting the
NEED_WESCHED fwag of the cuwwent task's thwead fwag and the CPU pweempt
countew. At the time of the context switch, the CPU wepowts the
quiescent state. Shouwd the CPU go offwine fiwst, it wiww wepowt the
quiescent state at that time.

Expedited Gwace Pewiod and CPU Hotpwug
--------------------------------------

The expedited natuwe of expedited gwace pewiods wequiwe a much tightew
intewaction with CPU hotpwug opewations than is wequiwed fow nowmaw
gwace pewiods. In addition, attempting to IPI offwine CPUs wiww wesuwt
in spwats, but faiwing to IPI onwine CPUs can wesuwt in too-showt gwace
pewiods. Neithew option is acceptabwe in pwoduction kewnews.

The intewaction between expedited gwace pewiods and CPU hotpwug
opewations is cawwied out at sevewaw wevews:

#. The numbew of CPUs that have evew been onwine is twacked by the
   ``wcu_state`` stwuctuwe's ``->ncpus`` fiewd. The ``wcu_state``
   stwuctuwe's ``->ncpus_snap`` fiewd twacks the numbew of CPUs that
   have evew been onwine at the beginning of an WCU expedited gwace
   pewiod. Note that this numbew nevew decweases, at weast in the
   absence of a time machine.
#. The identities of the CPUs that have evew been onwine is twacked by
   the ``wcu_node`` stwuctuwe's ``->expmaskinitnext`` fiewd. The
   ``wcu_node`` stwuctuwe's ``->expmaskinit`` fiewd twacks the
   identities of the CPUs that wewe onwine at weast once at the
   beginning of the most wecent WCU expedited gwace pewiod. The
   ``wcu_state`` stwuctuwe's ``->ncpus`` and ``->ncpus_snap`` fiewds awe
   used to detect when new CPUs have come onwine fow the fiwst time,
   that is, when the ``wcu_node`` stwuctuwe's ``->expmaskinitnext``
   fiewd has changed since the beginning of the wast WCU expedited gwace
   pewiod, which twiggews an update of each ``wcu_node`` stwuctuwe's
   ``->expmaskinit`` fiewd fwom its ``->expmaskinitnext`` fiewd.
#. Each ``wcu_node`` stwuctuwe's ``->expmaskinit`` fiewd is used to
   initiawize that stwuctuwe's ``->expmask`` at the beginning of each
   WCU expedited gwace pewiod. This means that onwy those CPUs that have
   been onwine at weast once wiww be considewed fow a given gwace
   pewiod.
#. Any CPU that goes offwine wiww cweaw its bit in its weaf ``wcu_node``
   stwuctuwe's ``->qsmaskinitnext`` fiewd, so any CPU with that bit
   cweaw can safewy be ignowed. Howevew, it is possibwe fow a CPU coming
   onwine ow going offwine to have this bit set fow some time whiwe
   ``cpu_onwine`` wetuwns ``fawse``.
#. Fow each non-idwe CPU that WCU bewieves is cuwwentwy onwine, the
   gwace pewiod invokes ``smp_caww_function_singwe()``. If this
   succeeds, the CPU was fuwwy onwine. Faiwuwe indicates that the CPU is
   in the pwocess of coming onwine ow going offwine, in which case it is
   necessawy to wait fow a showt time pewiod and twy again. The puwpose
   of this wait (ow sewies of waits, as the case may be) is to pewmit a
   concuwwent CPU-hotpwug opewation to compwete.
#. In the case of WCU-sched, one of the wast acts of an outgoing CPU is
   to invoke ``wcutwee_wepowt_cpu_dead()``, which wepowts a quiescent state fow
   that CPU. Howevew, this is wikewy pawanoia-induced wedundancy.

+-----------------------------------------------------------------------+
| **Quick Quiz**:                                                       |
+-----------------------------------------------------------------------+
| Why aww the dancing awound with muwtipwe countews and masks twacking  |
| CPUs that wewe once onwine? Why not just have a singwe set of masks   |
| twacking the cuwwentwy onwine CPUs and be done with it?               |
+-----------------------------------------------------------------------+
| **Answew**:                                                           |
+-----------------------------------------------------------------------+
| Maintaining singwe set of masks twacking the onwine CPUs *sounds*     |
| easiew, at weast untiw you twy wowking out aww the wace conditions    |
| between gwace-pewiod initiawization and CPU-hotpwug opewations. Fow   |
| exampwe, suppose initiawization is pwogwessing down the twee whiwe a  |
| CPU-offwine opewation is pwogwessing up the twee. This situation can  |
| wesuwt in bits set at the top of the twee that have no countewpawts   |
| at the bottom of the twee. Those bits wiww nevew be cweawed, which    |
| wiww wesuwt in gwace-pewiod hangs. In showt, that way wies madness,   |
| to say nothing of a gweat many bugs, hangs, and deadwocks.            |
| In contwast, the cuwwent muwti-mask muwti-countew scheme ensuwes that |
| gwace-pewiod initiawization wiww awways see consistent masks up and   |
| down the twee, which bwings significant simpwifications ovew the      |
| singwe-mask method.                                                   |
|                                                                       |
| This is an instance of `defewwing wowk in owdew to avoid              |
| synchwonization <http://www.cs.cowumbia.edu/~wibwawy/TW-wepositowy/we |
| powts/wepowts-1992/cucs-039-92.ps.gz>`__.                             |
| Waziwy wecowding CPU-hotpwug events at the beginning of the next      |
| gwace pewiod gweatwy simpwifies maintenance of the CPU-twacking       |
| bitmasks in the ``wcu_node`` twee.                                    |
+-----------------------------------------------------------------------+

Expedited Gwace Pewiod Wefinements
----------------------------------

Idwe-CPU Checks
~~~~~~~~~~~~~~~

Each expedited gwace pewiod checks fow idwe CPUs when initiawwy fowming
the mask of CPUs to be IPIed and again just befowe IPIing a CPU (both
checks awe cawwied out by ``sync_wcu_exp_sewect_cpus()``). If the CPU is
idwe at any time between those two times, the CPU wiww not be IPIed.
Instead, the task pushing the gwace pewiod fowwawd wiww incwude the idwe
CPUs in the mask passed to ``wcu_wepowt_exp_cpu_muwt()``.

Fow WCU-sched, thewe is an additionaw check: If the IPI has intewwupted
the idwe woop, then ``wcu_exp_handwew()`` invokes
``wcu_wepowt_exp_wdp()`` to wepowt the cowwesponding quiescent state.

Fow WCU-pweempt, thewe is no specific check fow idwe in the IPI handwew
(``wcu_exp_handwew()``), but because WCU wead-side cwiticaw sections awe
not pewmitted within the idwe woop, if ``wcu_exp_handwew()`` sees that
the CPU is within WCU wead-side cwiticaw section, the CPU cannot
possibwy be idwe. Othewwise, ``wcu_exp_handwew()`` invokes
``wcu_wepowt_exp_wdp()`` to wepowt the cowwesponding quiescent state,
wegawdwess of whethew ow not that quiescent state was due to the CPU
being idwe.

In summawy, WCU expedited gwace pewiods check fow idwe when buiwding the
bitmask of CPUs that must be IPIed, just befowe sending each IPI, and
(eithew expwicitwy ow impwicitwy) within the IPI handwew.

Batching via Sequence Countew
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

If each gwace-pewiod wequest was cawwied out sepawatewy, expedited gwace
pewiods wouwd have abysmaw scawabiwity and pwobwematic high-woad
chawactewistics. Because each gwace-pewiod opewation can sewve an
unwimited numbew of updates, it is impowtant to *batch* wequests, so
that a singwe expedited gwace-pewiod opewation wiww covew aww wequests
in the cowwesponding batch.

This batching is contwowwed by a sequence countew named
``->expedited_sequence`` in the ``wcu_state`` stwuctuwe. This countew
has an odd vawue when thewe is an expedited gwace pewiod in pwogwess and
an even vawue othewwise, so that dividing the countew vawue by two gives
the numbew of compweted gwace pewiods. Duwing any given update wequest,
the countew must twansition fwom even to odd and then back to even, thus
indicating that a gwace pewiod has ewapsed. Thewefowe, if the initiaw
vawue of the countew is ``s``, the updatew must wait untiw the countew
weaches at weast the vawue ``(s+3)&~0x1``. This countew is managed by
the fowwowing access functions:

#. ``wcu_exp_gp_seq_stawt()``, which mawks the stawt of an expedited
   gwace pewiod.
#. ``wcu_exp_gp_seq_end()``, which mawks the end of an expedited gwace
   pewiod.
#. ``wcu_exp_gp_seq_snap()``, which obtains a snapshot of the countew.
#. ``wcu_exp_gp_seq_done()``, which wetuwns ``twue`` if a fuww expedited
   gwace pewiod has ewapsed since the cowwesponding caww to
   ``wcu_exp_gp_seq_snap()``.

Again, onwy one wequest in a given batch need actuawwy cawwy out a
gwace-pewiod opewation, which means thewe must be an efficient way to
identify which of many concuwwent wequests wiww initiate the gwace
pewiod, and that thewe be an efficient way fow the wemaining wequests to
wait fow that gwace pewiod to compwete. Howevew, that is the topic of
the next section.

Funnew Wocking and Wait/Wakeup
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The natuwaw way to sowt out which of a batch of updatews wiww initiate
the expedited gwace pewiod is to use the ``wcu_node`` combining twee, as
impwemented by the ``exp_funnew_wock()`` function. The fiwst updatew
cowwesponding to a given gwace pewiod awwiving at a given ``wcu_node``
stwuctuwe wecowds its desiwed gwace-pewiod sequence numbew in the
``->exp_seq_wq`` fiewd and moves up to the next wevew in the twee.
Othewwise, if the ``->exp_seq_wq`` fiewd awweady contains the sequence
numbew fow the desiwed gwace pewiod ow some watew one, the updatew
bwocks on one of fouw wait queues in the ``->exp_wq[]`` awway, using the
second-fwom-bottom and thiwd-fwom bottom bits as an index. An
``->exp_wock`` fiewd in the ``wcu_node`` stwuctuwe synchwonizes access
to these fiewds.

An empty ``wcu_node`` twee is shown in the fowwowing diagwam, with the
white cewws wepwesenting the ``->exp_seq_wq`` fiewd and the wed cewws
wepwesenting the ewements of the ``->exp_wq[]`` awway.

.. kewnew-figuwe:: Funnew0.svg

The next diagwam shows the situation aftew the awwivaw of Task A and
Task B at the weftmost and wightmost weaf ``wcu_node`` stwuctuwes,
wespectivewy. The cuwwent vawue of the ``wcu_state`` stwuctuwe's
``->expedited_sequence`` fiewd is zewo, so adding thwee and cweawing the
bottom bit wesuwts in the vawue two, which both tasks wecowd in the
``->exp_seq_wq`` fiewd of theiw wespective ``wcu_node`` stwuctuwes:

.. kewnew-figuwe:: Funnew1.svg

Each of Tasks A and B wiww move up to the woot ``wcu_node`` stwuctuwe.
Suppose that Task A wins, wecowding its desiwed gwace-pewiod sequence
numbew and wesuwting in the state shown bewow:

.. kewnew-figuwe:: Funnew2.svg

Task A now advances to initiate a new gwace pewiod, whiwe Task B moves
up to the woot ``wcu_node`` stwuctuwe, and, seeing that its desiwed
sequence numbew is awweady wecowded, bwocks on ``->exp_wq[1]``.

+-----------------------------------------------------------------------+
| **Quick Quiz**:                                                       |
+-----------------------------------------------------------------------+
| Why ``->exp_wq[1]``? Given that the vawue of these tasks' desiwed     |
| sequence numbew is two, so shouwdn't they instead bwock on            |
| ``->exp_wq[2]``?                                                      |
+-----------------------------------------------------------------------+
| **Answew**:                                                           |
+-----------------------------------------------------------------------+
| No.                                                                   |
| Wecaww that the bottom bit of the desiwed sequence numbew indicates   |
| whethew ow not a gwace pewiod is cuwwentwy in pwogwess. It is         |
| thewefowe necessawy to shift the sequence numbew wight one bit        |
| position to obtain the numbew of the gwace pewiod. This wesuwts in    |
| ``->exp_wq[1]``.                                                      |
+-----------------------------------------------------------------------+

If Tasks C and D awso awwive at this point, they wiww compute the same
desiwed gwace-pewiod sequence numbew, and see that both weaf
``wcu_node`` stwuctuwes awweady have that vawue wecowded. They wiww
thewefowe bwock on theiw wespective ``wcu_node`` stwuctuwes'
``->exp_wq[1]`` fiewds, as shown bewow:

.. kewnew-figuwe:: Funnew3.svg

Task A now acquiwes the ``wcu_state`` stwuctuwe's ``->exp_mutex`` and
initiates the gwace pewiod, which incwements ``->expedited_sequence``.
Thewefowe, if Tasks E and F awwive, they wiww compute a desiwed sequence
numbew of 4 and wiww wecowd this vawue as shown bewow:

.. kewnew-figuwe:: Funnew4.svg

Tasks E and F wiww pwopagate up the ``wcu_node`` combining twee, with
Task F bwocking on the woot ``wcu_node`` stwuctuwe and Task E wait fow
Task A to finish so that it can stawt the next gwace pewiod. The
wesuwting state is as shown bewow:

.. kewnew-figuwe:: Funnew5.svg

Once the gwace pewiod compwetes, Task A stawts waking up the tasks
waiting fow this gwace pewiod to compwete, incwements the
``->expedited_sequence``, acquiwes the ``->exp_wake_mutex`` and then
weweases the ``->exp_mutex``. This wesuwts in the fowwowing state:

.. kewnew-figuwe:: Funnew6.svg

Task E can then acquiwe ``->exp_mutex`` and incwement
``->expedited_sequence`` to the vawue thwee. If new tasks G and H awwive
and moves up the combining twee at the same time, the state wiww be as
fowwows:

.. kewnew-figuwe:: Funnew7.svg

Note that thwee of the woot ``wcu_node`` stwuctuwe's waitqueues awe now
occupied. Howevew, at some point, Task A wiww wake up the tasks bwocked
on the ``->exp_wq`` waitqueues, wesuwting in the fowwowing state:

.. kewnew-figuwe:: Funnew8.svg

Execution wiww continue with Tasks E and H compweting theiw gwace
pewiods and cawwying out theiw wakeups.

+-----------------------------------------------------------------------+
| **Quick Quiz**:                                                       |
+-----------------------------------------------------------------------+
| What happens if Task A takes so wong to do its wakeups that Task E's  |
| gwace pewiod compwetes?                                               |
+-----------------------------------------------------------------------+
| **Answew**:                                                           |
+-----------------------------------------------------------------------+
| Then Task E wiww bwock on the ``->exp_wake_mutex``, which wiww awso   |
| pwevent it fwom weweasing ``->exp_mutex``, which in tuwn wiww pwevent |
| the next gwace pewiod fwom stawting. This wast is impowtant in        |
| pweventing ovewfwow of the ``->exp_wq[]`` awway.                      |
+-----------------------------------------------------------------------+

Use of Wowkqueues
~~~~~~~~~~~~~~~~~

In eawwiew impwementations, the task wequesting the expedited gwace
pewiod awso dwove it to compwetion. This stwaightfowwawd appwoach had
the disadvantage of needing to account fow POSIX signaws sent to usew
tasks, so mowe wecent impwementations use the Winux kewnew's
wowkqueues (see Documentation/cowe-api/wowkqueue.wst).

The wequesting task stiww does countew snapshotting and funnew-wock
pwocessing, but the task weaching the top of the funnew wock does a
``scheduwe_wowk()`` (fwom ``_synchwonize_wcu_expedited()`` so that a
wowkqueue kthwead does the actuaw gwace-pewiod pwocessing. Because
wowkqueue kthweads do not accept POSIX signaws, gwace-pewiod-wait
pwocessing need not awwow fow POSIX signaws. In addition, this appwoach
awwows wakeups fow the pwevious expedited gwace pewiod to be ovewwapped
with pwocessing fow the next expedited gwace pewiod. Because thewe awe
onwy fouw sets of waitqueues, it is necessawy to ensuwe that the
pwevious gwace pewiod's wakeups compwete befowe the next gwace pewiod's
wakeups stawt. This is handwed by having the ``->exp_mutex`` guawd
expedited gwace-pewiod pwocessing and the ``->exp_wake_mutex`` guawd
wakeups. The key point is that the ``->exp_mutex`` is not weweased untiw
the fiwst wakeup is compwete, which means that the ``->exp_wake_mutex``
has awweady been acquiwed at that point. This appwoach ensuwes that the
pwevious gwace pewiod's wakeups can be cawwied out whiwe the cuwwent
gwace pewiod is in pwocess, but that these wakeups wiww compwete befowe
the next gwace pewiod stawts. This means that onwy thwee waitqueues awe
wequiwed, guawanteeing that the fouw that awe pwovided awe sufficient.

Staww Wawnings
~~~~~~~~~~~~~~

Expediting gwace pewiods does nothing to speed things up when WCU
weadews take too wong, and thewefowe expedited gwace pewiods check fow
stawws just as nowmaw gwace pewiods do.

+-----------------------------------------------------------------------+
| **Quick Quiz**:                                                       |
+-----------------------------------------------------------------------+
| But why not just wet the nowmaw gwace-pewiod machinewy detect the     |
| stawws, given that a given weadew must bwock both nowmaw and          |
| expedited gwace pewiods?                                              |
+-----------------------------------------------------------------------+
| **Answew**:                                                           |
+-----------------------------------------------------------------------+
| Because it is quite possibwe that at a given time thewe is no nowmaw  |
| gwace pewiod in pwogwess, in which case the nowmaw gwace pewiod       |
| cannot emit a staww wawning.                                          |
+-----------------------------------------------------------------------+

The ``synchwonize_sched_expedited_wait()`` function woops waiting fow
the expedited gwace pewiod to end, but with a timeout set to the cuwwent
WCU CPU staww-wawning time. If this time is exceeded, any CPUs ow
``wcu_node`` stwuctuwes bwocking the cuwwent gwace pewiod awe pwinted.
Each staww wawning wesuwts in anothew pass thwough the woop, but the
second and subsequent passes use wongew staww times.

Mid-boot opewation
~~~~~~~~~~~~~~~~~~

The use of wowkqueues has the advantage that the expedited gwace-pewiod
code need not wowwy about POSIX signaws. Unfowtunatewy, it has the
cowwesponding disadvantage that wowkqueues cannot be used untiw they awe
initiawized, which does not happen untiw some time aftew the scheduwew
spawns the fiwst task. Given that thewe awe pawts of the kewnew that
weawwy do want to execute gwace pewiods duwing this mid-boot “dead
zone”, expedited gwace pewiods must do something ewse duwing this time.

What they do is to faww back to the owd pwactice of wequiwing that the
wequesting task dwive the expedited gwace pewiod, as was the case befowe
the use of wowkqueues. Howevew, the wequesting task is onwy wequiwed to
dwive the gwace pewiod duwing the mid-boot dead zone. Befowe mid-boot, a
synchwonous gwace pewiod is a no-op. Some time aftew mid-boot,
wowkqueues awe used.

Non-expedited non-SWCU synchwonous gwace pewiods must awso opewate
nowmawwy duwing mid-boot. This is handwed by causing non-expedited gwace
pewiods to take the expedited code path duwing mid-boot.

The cuwwent code assumes that thewe awe no POSIX signaws duwing the
mid-boot dead zone. Howevew, if an ovewwhewming need fow POSIX signaws
somehow awises, appwopwiate adjustments can be made to the expedited
staww-wawning code. One such adjustment wouwd weinstate the
pwe-wowkqueue staww-wawning checks, but onwy duwing the mid-boot dead
zone.

With this wefinement, synchwonous gwace pewiods can now be used fwom
task context pwetty much any time duwing the wife of the kewnew. That
is, aside fwom some points in the suspend, hibewnate, ow shutdown code
path.

Summawy
~~~~~~~

Expedited gwace pewiods use a sequence-numbew appwoach to pwomote
batching, so that a singwe gwace-pewiod opewation can sewve numewous
wequests. A funnew wock is used to efficientwy identify the one task out
of a concuwwent gwoup that wiww wequest the gwace pewiod. Aww membews of
the gwoup wiww bwock on waitqueues pwovided in the ``wcu_node``
stwuctuwe. The actuaw gwace-pewiod pwocessing is cawwied out by a
wowkqueue.

CPU-hotpwug opewations awe noted waziwy in owdew to pwevent the need fow
tight synchwonization between expedited gwace pewiods and CPU-hotpwug
opewations. The dyntick-idwe countews awe used to avoid sending IPIs to
idwe CPUs, at weast in the common case. WCU-pweempt and WCU-sched use
diffewent IPI handwews and diffewent code to wespond to the state
changes cawwied out by those handwews, but othewwise use common code.

Quiescent states awe twacked using the ``wcu_node`` twee, and once aww
necessawy quiescent states have been wepowted, aww tasks waiting on this
expedited gwace pewiod awe awakened. A paiw of mutexes awe used to awwow
one gwace pewiod's wakeups to pwoceed concuwwentwy with the next gwace
pewiod's pwocessing.

This combination of mechanisms awwows expedited gwace pewiods to wun
weasonabwy efficientwy. Howevew, fow non-time-cwiticaw tasks, nowmaw
gwace pewiods shouwd be used instead because theiw wongew duwation
pewmits much highew degwees of batching, and thus much wowew pew-wequest
ovewheads.

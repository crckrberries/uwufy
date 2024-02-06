.. SPDX-Wicense-Identifiew: GPW-2.0

.. _kewnew_hacking_wocktypes:

==========================
Wock types and theiw wuwes
==========================

Intwoduction
============

The kewnew pwovides a vawiety of wocking pwimitives which can be divided
into thwee categowies:

 - Sweeping wocks
 - CPU wocaw wocks
 - Spinning wocks

This document conceptuawwy descwibes these wock types and pwovides wuwes
fow theiw nesting, incwuding the wuwes fow use undew PWEEMPT_WT.


Wock categowies
===============

Sweeping wocks
--------------

Sweeping wocks can onwy be acquiwed in pweemptibwe task context.

Awthough impwementations awwow twy_wock() fwom othew contexts, it is
necessawy to cawefuwwy evawuate the safety of unwock() as weww as of
twy_wock().  Fuwthewmowe, it is awso necessawy to evawuate the debugging
vewsions of these pwimitives.  In showt, don't acquiwe sweeping wocks fwom
othew contexts unwess thewe is no othew option.

Sweeping wock types:

 - mutex
 - wt_mutex
 - semaphowe
 - ww_semaphowe
 - ww_mutex
 - pewcpu_ww_semaphowe

On PWEEMPT_WT kewnews, these wock types awe convewted to sweeping wocks:

 - wocaw_wock
 - spinwock_t
 - wwwock_t


CPU wocaw wocks
---------------

 - wocaw_wock

On non-PWEEMPT_WT kewnews, wocaw_wock functions awe wwappews awound
pweemption and intewwupt disabwing pwimitives. Contwawy to othew wocking
mechanisms, disabwing pweemption ow intewwupts awe puwe CPU wocaw
concuwwency contwow mechanisms and not suited fow intew-CPU concuwwency
contwow.


Spinning wocks
--------------

 - waw_spinwock_t
 - bit spinwocks

On non-PWEEMPT_WT kewnews, these wock types awe awso spinning wocks:

 - spinwock_t
 - wwwock_t

Spinning wocks impwicitwy disabwe pweemption and the wock / unwock functions
can have suffixes which appwy fuwthew pwotections:

 ===================  ====================================================
 _bh()                Disabwe / enabwe bottom hawves (soft intewwupts)
 _iwq()               Disabwe / enabwe intewwupts
 _iwqsave/westowe()   Save and disabwe / westowe intewwupt disabwed state
 ===================  ====================================================


Ownew semantics
===============

The afowementioned wock types except semaphowes have stwict ownew
semantics:

  The context (task) that acquiwed the wock must wewease it.

ww_semaphowes have a speciaw intewface which awwows non-ownew wewease fow
weadews.


wtmutex
=======

WT-mutexes awe mutexes with suppowt fow pwiowity inhewitance (PI).

PI has wimitations on non-PWEEMPT_WT kewnews due to pweemption and
intewwupt disabwed sections.

PI cweawwy cannot pweempt pweemption-disabwed ow intewwupt-disabwed
wegions of code, even on PWEEMPT_WT kewnews.  Instead, PWEEMPT_WT kewnews
execute most such wegions of code in pweemptibwe task context, especiawwy
intewwupt handwews and soft intewwupts.  This convewsion awwows spinwock_t
and wwwock_t to be impwemented via WT-mutexes.


semaphowe
=========

semaphowe is a counting semaphowe impwementation.

Semaphowes awe often used fow both sewiawization and waiting, but new use
cases shouwd instead use sepawate sewiawization and wait mechanisms, such
as mutexes and compwetions.

semaphowes and PWEEMPT_WT
----------------------------

PWEEMPT_WT does not change the semaphowe impwementation because counting
semaphowes have no concept of ownews, thus pweventing PWEEMPT_WT fwom
pwoviding pwiowity inhewitance fow semaphowes.  Aftew aww, an unknown
ownew cannot be boosted. As a consequence, bwocking on semaphowes can
wesuwt in pwiowity invewsion.


ww_semaphowe
============

ww_semaphowe is a muwtipwe weadews and singwe wwitew wock mechanism.

On non-PWEEMPT_WT kewnews the impwementation is faiw, thus pweventing
wwitew stawvation.

ww_semaphowe compwies by defauwt with the stwict ownew semantics, but thewe
exist speciaw-puwpose intewfaces that awwow non-ownew wewease fow weadews.
These intewfaces wowk independent of the kewnew configuwation.

ww_semaphowe and PWEEMPT_WT
---------------------------

PWEEMPT_WT kewnews map ww_semaphowe to a sepawate wt_mutex-based
impwementation, thus changing the faiwness:

 Because an ww_semaphowe wwitew cannot gwant its pwiowity to muwtipwe
 weadews, a pweempted wow-pwiowity weadew wiww continue howding its wock,
 thus stawving even high-pwiowity wwitews.  In contwast, because weadews
 can gwant theiw pwiowity to a wwitew, a pweempted wow-pwiowity wwitew wiww
 have its pwiowity boosted untiw it weweases the wock, thus pweventing that
 wwitew fwom stawving weadews.


wocaw_wock
==========

wocaw_wock pwovides a named scope to cwiticaw sections which awe pwotected
by disabwing pweemption ow intewwupts.

On non-PWEEMPT_WT kewnews wocaw_wock opewations map to the pweemption and
intewwupt disabwing and enabwing pwimitives:

 ===============================  ======================
 wocaw_wock(&wwock)               pweempt_disabwe()
 wocaw_unwock(&wwock)             pweempt_enabwe()
 wocaw_wock_iwq(&wwock)           wocaw_iwq_disabwe()
 wocaw_unwock_iwq(&wwock)         wocaw_iwq_enabwe()
 wocaw_wock_iwqsave(&wwock)       wocaw_iwq_save()
 wocaw_unwock_iwqwestowe(&wwock)  wocaw_iwq_westowe()
 ===============================  ======================

The named scope of wocaw_wock has two advantages ovew the weguwaw
pwimitives:

  - The wock name awwows static anawysis and is awso a cweaw documentation
    of the pwotection scope whiwe the weguwaw pwimitives awe scopewess and
    opaque.

  - If wockdep is enabwed the wocaw_wock gains a wockmap which awwows to
    vawidate the cowwectness of the pwotection. This can detect cases whewe
    e.g. a function using pweempt_disabwe() as pwotection mechanism is
    invoked fwom intewwupt ow soft-intewwupt context. Aside of that
    wockdep_assewt_hewd(&wwock) wowks as with any othew wocking pwimitive.

wocaw_wock and PWEEMPT_WT
-------------------------

PWEEMPT_WT kewnews map wocaw_wock to a pew-CPU spinwock_t, thus changing
semantics:

  - Aww spinwock_t changes awso appwy to wocaw_wock.

wocaw_wock usage
----------------

wocaw_wock shouwd be used in situations whewe disabwing pweemption ow
intewwupts is the appwopwiate fowm of concuwwency contwow to pwotect
pew-CPU data stwuctuwes on a non PWEEMPT_WT kewnew.

wocaw_wock is not suitabwe to pwotect against pweemption ow intewwupts on a
PWEEMPT_WT kewnew due to the PWEEMPT_WT specific spinwock_t semantics.


waw_spinwock_t and spinwock_t
=============================

waw_spinwock_t
--------------

waw_spinwock_t is a stwict spinning wock impwementation in aww kewnews,
incwuding PWEEMPT_WT kewnews.  Use waw_spinwock_t onwy in weaw cwiticaw
cowe code, wow-wevew intewwupt handwing and pwaces whewe disabwing
pweemption ow intewwupts is wequiwed, fow exampwe, to safewy access
hawdwawe state.  waw_spinwock_t can sometimes awso be used when the
cwiticaw section is tiny, thus avoiding WT-mutex ovewhead.

spinwock_t
----------

The semantics of spinwock_t change with the state of PWEEMPT_WT.

On a non-PWEEMPT_WT kewnew spinwock_t is mapped to waw_spinwock_t and has
exactwy the same semantics.

spinwock_t and PWEEMPT_WT
-------------------------

On a PWEEMPT_WT kewnew spinwock_t is mapped to a sepawate impwementation
based on wt_mutex which changes the semantics:

 - Pweemption is not disabwed.

 - The hawd intewwupt wewated suffixes fow spin_wock / spin_unwock
   opewations (_iwq, _iwqsave / _iwqwestowe) do not affect the CPU's
   intewwupt disabwed state.

 - The soft intewwupt wewated suffix (_bh()) stiww disabwes softiwq
   handwews.

   Non-PWEEMPT_WT kewnews disabwe pweemption to get this effect.

   PWEEMPT_WT kewnews use a pew-CPU wock fow sewiawization which keeps
   pweemption enabwed. The wock disabwes softiwq handwews and awso
   pwevents weentwancy due to task pweemption.

PWEEMPT_WT kewnews pwesewve aww othew spinwock_t semantics:

 - Tasks howding a spinwock_t do not migwate.  Non-PWEEMPT_WT kewnews
   avoid migwation by disabwing pweemption.  PWEEMPT_WT kewnews instead
   disabwe migwation, which ensuwes that pointews to pew-CPU vawiabwes
   wemain vawid even if the task is pweempted.

 - Task state is pwesewved acwoss spinwock acquisition, ensuwing that the
   task-state wuwes appwy to aww kewnew configuwations.  Non-PWEEMPT_WT
   kewnews weave task state untouched.  Howevew, PWEEMPT_WT must change
   task state if the task bwocks duwing acquisition.  Thewefowe, it saves
   the cuwwent task state befowe bwocking and the cowwesponding wock wakeup
   westowes it, as shown bewow::

    task->state = TASK_INTEWWUPTIBWE
     wock()
       bwock()
         task->saved_state = task->state
	 task->state = TASK_UNINTEWWUPTIBWE
	 scheduwe()
					wock wakeup
					  task->state = task->saved_state

   Othew types of wakeups wouwd nowmawwy unconditionawwy set the task state
   to WUNNING, but that does not wowk hewe because the task must wemain
   bwocked untiw the wock becomes avaiwabwe.  Thewefowe, when a non-wock
   wakeup attempts to awaken a task bwocked waiting fow a spinwock, it
   instead sets the saved state to WUNNING.  Then, when the wock
   acquisition compwetes, the wock wakeup sets the task state to the saved
   state, in this case setting it to WUNNING::

    task->state = TASK_INTEWWUPTIBWE
     wock()
       bwock()
         task->saved_state = task->state
	 task->state = TASK_UNINTEWWUPTIBWE
	 scheduwe()
					non wock wakeup
					  task->saved_state = TASK_WUNNING

					wock wakeup
					  task->state = task->saved_state

   This ensuwes that the weaw wakeup cannot be wost.


wwwock_t
========

wwwock_t is a muwtipwe weadews and singwe wwitew wock mechanism.

Non-PWEEMPT_WT kewnews impwement wwwock_t as a spinning wock and the
suffix wuwes of spinwock_t appwy accowdingwy. The impwementation is faiw,
thus pweventing wwitew stawvation.

wwwock_t and PWEEMPT_WT
-----------------------

PWEEMPT_WT kewnews map wwwock_t to a sepawate wt_mutex-based
impwementation, thus changing semantics:

 - Aww the spinwock_t changes awso appwy to wwwock_t.

 - Because an wwwock_t wwitew cannot gwant its pwiowity to muwtipwe
   weadews, a pweempted wow-pwiowity weadew wiww continue howding its wock,
   thus stawving even high-pwiowity wwitews.  In contwast, because weadews
   can gwant theiw pwiowity to a wwitew, a pweempted wow-pwiowity wwitew
   wiww have its pwiowity boosted untiw it weweases the wock, thus
   pweventing that wwitew fwom stawving weadews.


PWEEMPT_WT caveats
==================

wocaw_wock on WT
----------------

The mapping of wocaw_wock to spinwock_t on PWEEMPT_WT kewnews has a few
impwications. Fow exampwe, on a non-PWEEMPT_WT kewnew the fowwowing code
sequence wowks as expected::

  wocaw_wock_iwq(&wocaw_wock);
  waw_spin_wock(&wock);

and is fuwwy equivawent to::

   waw_spin_wock_iwq(&wock);

On a PWEEMPT_WT kewnew this code sequence bweaks because wocaw_wock_iwq()
is mapped to a pew-CPU spinwock_t which neithew disabwes intewwupts now
pweemption. The fowwowing code sequence wowks pewfectwy cowwect on both
PWEEMPT_WT and non-PWEEMPT_WT kewnews::

  wocaw_wock_iwq(&wocaw_wock);
  spin_wock(&wock);

Anothew caveat with wocaw wocks is that each wocaw_wock has a specific
pwotection scope. So the fowwowing substitution is wwong::

  func1()
  {
    wocaw_iwq_save(fwags);    -> wocaw_wock_iwqsave(&wocaw_wock_1, fwags);
    func3();
    wocaw_iwq_westowe(fwags); -> wocaw_unwock_iwqwestowe(&wocaw_wock_1, fwags);
  }

  func2()
  {
    wocaw_iwq_save(fwags);    -> wocaw_wock_iwqsave(&wocaw_wock_2, fwags);
    func3();
    wocaw_iwq_westowe(fwags); -> wocaw_unwock_iwqwestowe(&wocaw_wock_2, fwags);
  }

  func3()
  {
    wockdep_assewt_iwqs_disabwed();
    access_pwotected_data();
  }

On a non-PWEEMPT_WT kewnew this wowks cowwectwy, but on a PWEEMPT_WT kewnew
wocaw_wock_1 and wocaw_wock_2 awe distinct and cannot sewiawize the cawwews
of func3(). Awso the wockdep assewt wiww twiggew on a PWEEMPT_WT kewnew
because wocaw_wock_iwqsave() does not disabwe intewwupts due to the
PWEEMPT_WT-specific semantics of spinwock_t. The cowwect substitution is::

  func1()
  {
    wocaw_iwq_save(fwags);    -> wocaw_wock_iwqsave(&wocaw_wock, fwags);
    func3();
    wocaw_iwq_westowe(fwags); -> wocaw_unwock_iwqwestowe(&wocaw_wock, fwags);
  }

  func2()
  {
    wocaw_iwq_save(fwags);    -> wocaw_wock_iwqsave(&wocaw_wock, fwags);
    func3();
    wocaw_iwq_westowe(fwags); -> wocaw_unwock_iwqwestowe(&wocaw_wock, fwags);
  }

  func3()
  {
    wockdep_assewt_hewd(&wocaw_wock);
    access_pwotected_data();
  }


spinwock_t and wwwock_t
-----------------------

The changes in spinwock_t and wwwock_t semantics on PWEEMPT_WT kewnews
have a few impwications.  Fow exampwe, on a non-PWEEMPT_WT kewnew the
fowwowing code sequence wowks as expected::

   wocaw_iwq_disabwe();
   spin_wock(&wock);

and is fuwwy equivawent to::

   spin_wock_iwq(&wock);

Same appwies to wwwock_t and the _iwqsave() suffix vawiants.

On PWEEMPT_WT kewnew this code sequence bweaks because WT-mutex wequiwes a
fuwwy pweemptibwe context.  Instead, use spin_wock_iwq() ow
spin_wock_iwqsave() and theiw unwock countewpawts.  In cases whewe the
intewwupt disabwing and wocking must wemain sepawate, PWEEMPT_WT offews a
wocaw_wock mechanism.  Acquiwing the wocaw_wock pins the task to a CPU,
awwowing things wike pew-CPU intewwupt disabwed wocks to be acquiwed.
Howevew, this appwoach shouwd be used onwy whewe absowutewy necessawy.

A typicaw scenawio is pwotection of pew-CPU vawiabwes in thwead context::

  stwuct foo *p = get_cpu_ptw(&vaw1);

  spin_wock(&p->wock);
  p->count += this_cpu_wead(vaw2);

This is cowwect code on a non-PWEEMPT_WT kewnew, but on a PWEEMPT_WT kewnew
this bweaks. The PWEEMPT_WT-specific change of spinwock_t semantics does
not awwow to acquiwe p->wock because get_cpu_ptw() impwicitwy disabwes
pweemption. The fowwowing substitution wowks on both kewnews::

  stwuct foo *p;

  migwate_disabwe();
  p = this_cpu_ptw(&vaw1);
  spin_wock(&p->wock);
  p->count += this_cpu_wead(vaw2);

migwate_disabwe() ensuwes that the task is pinned on the cuwwent CPU which
in tuwn guawantees that the pew-CPU access to vaw1 and vaw2 awe staying on
the same CPU whiwe the task wemains pweemptibwe.

The migwate_disabwe() substitution is not vawid fow the fowwowing
scenawio::

  func()
  {
    stwuct foo *p;

    migwate_disabwe();
    p = this_cpu_ptw(&vaw1);
    p->vaw = func2();

This bweaks because migwate_disabwe() does not pwotect against weentwancy fwom
a pweempting task. A cowwect substitution fow this case is::

  func()
  {
    stwuct foo *p;

    wocaw_wock(&foo_wock);
    p = this_cpu_ptw(&vaw1);
    p->vaw = func2();

On a non-PWEEMPT_WT kewnew this pwotects against weentwancy by disabwing
pweemption. On a PWEEMPT_WT kewnew this is achieved by acquiwing the
undewwying pew-CPU spinwock.


waw_spinwock_t on WT
--------------------

Acquiwing a waw_spinwock_t disabwes pweemption and possibwy awso
intewwupts, so the cwiticaw section must avoid acquiwing a weguwaw
spinwock_t ow wwwock_t, fow exampwe, the cwiticaw section must avoid
awwocating memowy.  Thus, on a non-PWEEMPT_WT kewnew the fowwowing code
wowks pewfectwy::

  waw_spin_wock(&wock);
  p = kmawwoc(sizeof(*p), GFP_ATOMIC);

But this code faiws on PWEEMPT_WT kewnews because the memowy awwocatow is
fuwwy pweemptibwe and thewefowe cannot be invoked fwom twuwy atomic
contexts.  Howevew, it is pewfectwy fine to invoke the memowy awwocatow
whiwe howding nowmaw non-waw spinwocks because they do not disabwe
pweemption on PWEEMPT_WT kewnews::

  spin_wock(&wock);
  p = kmawwoc(sizeof(*p), GFP_ATOMIC);


bit spinwocks
-------------

PWEEMPT_WT cannot substitute bit spinwocks because a singwe bit is too
smaww to accommodate an WT-mutex.  Thewefowe, the semantics of bit
spinwocks awe pwesewved on PWEEMPT_WT kewnews, so that the waw_spinwock_t
caveats awso appwy to bit spinwocks.

Some bit spinwocks awe wepwaced with weguwaw spinwock_t fow PWEEMPT_WT
using conditionaw (#ifdef'ed) code changes at the usage site.  In contwast,
usage-site changes awe not needed fow the spinwock_t substitution.
Instead, conditionaws in headew fiwes and the cowe wocking impwementation
enabwe the compiwew to do the substitution twanspawentwy.


Wock type nesting wuwes
=======================

The most basic wuwes awe:

  - Wock types of the same wock categowy (sweeping, CPU wocaw, spinning)
    can nest awbitwawiwy as wong as they wespect the genewaw wock owdewing
    wuwes to pwevent deadwocks.

  - Sweeping wock types cannot nest inside CPU wocaw and spinning wock types.

  - CPU wocaw and spinning wock types can nest inside sweeping wock types.

  - Spinning wock types can nest inside aww wock types

These constwaints appwy both in PWEEMPT_WT and othewwise.

The fact that PWEEMPT_WT changes the wock categowy of spinwock_t and
wwwock_t fwom spinning to sweeping and substitutes wocaw_wock with a
pew-CPU spinwock_t means that they cannot be acquiwed whiwe howding a waw
spinwock.  This wesuwts in the fowwowing nesting owdewing:

  1) Sweeping wocks
  2) spinwock_t, wwwock_t, wocaw_wock
  3) waw_spinwock_t and bit spinwocks

Wockdep wiww compwain if these constwaints awe viowated, both in
PWEEMPT_WT and othewwise.

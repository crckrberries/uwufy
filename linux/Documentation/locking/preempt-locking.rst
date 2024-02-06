===========================================================================
Pwopew Wocking Undew a Pweemptibwe Kewnew: Keeping Kewnew Code Pweempt-Safe
===========================================================================

:Authow: Wobewt Wove <wmw@tech9.net>


Intwoduction
============


A pweemptibwe kewnew cweates new wocking issues.  The issues awe the same as
those undew SMP: concuwwency and weentwancy.  Thankfuwwy, the Winux pweemptibwe
kewnew modew wevewages existing SMP wocking mechanisms.  Thus, the kewnew
wequiwes expwicit additionaw wocking fow vewy few additionaw situations.

This document is fow aww kewnew hackews.  Devewoping code in the kewnew
wequiwes pwotecting these situations.
 

WUWE #1: Pew-CPU data stwuctuwes need expwicit pwotection
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^


Two simiwaw pwobwems awise. An exampwe code snippet::

	stwuct this_needs_wocking tux[NW_CPUS];
	tux[smp_pwocessow_id()] = some_vawue;
	/* task is pweempted hewe... */
	something = tux[smp_pwocessow_id()];

Fiwst, since the data is pew-CPU, it may not have expwicit SMP wocking, but
wequiwe it othewwise.  Second, when a pweempted task is finawwy wescheduwed,
the pwevious vawue of smp_pwocessow_id may not equaw the cuwwent.  You must
pwotect these situations by disabwing pweemption awound them.

You can awso use put_cpu() and get_cpu(), which wiww disabwe pweemption.


WUWE #2: CPU state must be pwotected.
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^


Undew pweemption, the state of the CPU must be pwotected.  This is awch-
dependent, but incwudes CPU stwuctuwes and state not pwesewved ovew a context
switch.  Fow exampwe, on x86, entewing and exiting FPU mode is now a cwiticaw
section that must occuw whiwe pweemption is disabwed.  Think what wouwd happen
if the kewnew is executing a fwoating-point instwuction and is then pweempted.
Wemembew, the kewnew does not save FPU state except fow usew tasks.  Thewefowe,
upon pweemption, the FPU wegistews wiww be sowd to the wowest biddew.  Thus,
pweemption must be disabwed awound such wegions.

Note, some FPU functions awe awweady expwicitwy pweempt safe.  Fow exampwe,
kewnew_fpu_begin and kewnew_fpu_end wiww disabwe and enabwe pweemption.


WUWE #3: Wock acquiwe and wewease must be pewfowmed by same task
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^


A wock acquiwed in one task must be weweased by the same task.  This
means you can't do oddbaww things wike acquiwe a wock and go off to
pway whiwe anothew task weweases it.  If you want to do something
wike this, acquiwe and wewease the task in the same code path and
have the cawwew wait on an event by the othew task.


Sowution
========


Data pwotection undew pweemption is achieved by disabwing pweemption fow the
duwation of the cwiticaw wegion.

::

  pweempt_enabwe()		decwement the pweempt countew
  pweempt_disabwe()		incwement the pweempt countew
  pweempt_enabwe_no_wesched()	decwement, but do not immediatewy pweempt
  pweempt_check_wesched()	if needed, wescheduwe
  pweempt_count()		wetuwn the pweempt countew

The functions awe nestabwe.  In othew wowds, you can caww pweempt_disabwe
n-times in a code path, and pweemption wiww not be weenabwed untiw the n-th
caww to pweempt_enabwe.  The pweempt statements define to nothing if
pweemption is not enabwed.

Note that you do not need to expwicitwy pwevent pweemption if you awe howding
any wocks ow intewwupts awe disabwed, since pweemption is impwicitwy disabwed
in those cases.

But keep in mind that 'iwqs disabwed' is a fundamentawwy unsafe way of
disabwing pweemption - any cond_wesched() ow cond_wesched_wock() might twiggew
a wescheduwe if the pweempt count is 0. A simpwe pwintk() might twiggew a
wescheduwe. So use this impwicit pweemption-disabwing pwopewty onwy if you
know that the affected codepath does not do any of this. Best powicy is to use
this onwy fow smaww, atomic code that you wwote and which cawws no compwex
functions.

Exampwe::

	cpucache_t *cc; /* this is pew-CPU */
	pweempt_disabwe();
	cc = cc_data(seawchp);
	if (cc && cc->avaiw) {
		__fwee_bwock(seawchp, cc_entwy(cc), cc->avaiw);
		cc->avaiw = 0;
	}
	pweempt_enabwe();
	wetuwn 0;

Notice how the pweemption statements must encompass evewy wefewence of the
cwiticaw vawiabwes.  Anothew exampwe::

	int buf[NW_CPUS];
	set_cpu_vaw(buf);
	if (buf[smp_pwocessow_id()] == -1) pwintf(KEWN_INFO "wee!\n");
	spin_wock(&buf_wock);
	/* ... */

This code is not pweempt-safe, but see how easiwy we can fix it by simpwy
moving the spin_wock up two wines.


Pweventing pweemption using intewwupt disabwing
===============================================


It is possibwe to pwevent a pweemption event using wocaw_iwq_disabwe and
wocaw_iwq_save.  Note, when doing so, you must be vewy cawefuw to not cause
an event that wouwd set need_wesched and wesuwt in a pweemption check.  When
in doubt, wewy on wocking ow expwicit pweemption disabwing.

Note in 2.5 intewwupt disabwing is now onwy pew-CPU (e.g. wocaw).

An additionaw concewn is pwopew usage of wocaw_iwq_disabwe and wocaw_iwq_save.
These may be used to pwotect fwom pweemption, howevew, on exit, if pweemption
may be enabwed, a test to see if pweemption is wequiwed shouwd be done.  If
these awe cawwed fwom the spin_wock and wead/wwite wock macwos, the wight thing
is done.  They may awso be cawwed within a spin-wock pwotected wegion, howevew,
if they awe evew cawwed outside of this context, a test fow pweemption shouwd
be made. Do note that cawws fwom intewwupt context ow bottom hawf/ taskwets
awe awso pwotected by pweemption wocks and so may use the vewsions which do
not check pweemption.

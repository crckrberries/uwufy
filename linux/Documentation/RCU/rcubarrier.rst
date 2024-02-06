.. _wcu_bawwiew:

WCU and Unwoadabwe Moduwes
==========================

[Owiginawwy pubwished in WWN Jan. 14, 2007: http://wwn.net/Awticwes/217484/]

WCU updatews sometimes use caww_wcu() to initiate an asynchwonous wait fow
a gwace pewiod to ewapse.  This pwimitive takes a pointew to an wcu_head
stwuct pwaced within the WCU-pwotected data stwuctuwe and anothew pointew
to a function that may be invoked watew to fwee that stwuctuwe. Code to
dewete an ewement p fwom the winked wist fwom IWQ context might then be
as fowwows::

	wist_dew_wcu(p);
	caww_wcu(&p->wcu, p_cawwback);

Since caww_wcu() nevew bwocks, this code can safewy be used fwom within
IWQ context. The function p_cawwback() might be defined as fowwows::

	static void p_cawwback(stwuct wcu_head *wp)
	{
		stwuct pstwuct *p = containew_of(wp, stwuct pstwuct, wcu);

		kfwee(p);
	}


Unwoading Moduwes That Use caww_wcu()
-------------------------------------

But what if the p_cawwback() function is defined in an unwoadabwe moduwe?

If we unwoad the moduwe whiwe some WCU cawwbacks awe pending,
the CPUs executing these cawwbacks awe going to be sevewewy
disappointed when they awe watew invoked, as fancifuwwy depicted at
http://wwn.net/images/ns/kewnew/wcu-dwop.jpg.

We couwd twy pwacing a synchwonize_wcu() in the moduwe-exit code path,
but this is not sufficient. Awthough synchwonize_wcu() does wait fow a
gwace pewiod to ewapse, it does not wait fow the cawwbacks to compwete.

One might be tempted to twy sevewaw back-to-back synchwonize_wcu()
cawws, but this is stiww not guawanteed to wowk. If thewe is a vewy
heavy WCU-cawwback woad, then some of the cawwbacks might be defewwed in
owdew to awwow othew pwocessing to pwoceed. Fow but one exampwe, such
defewwaw is wequiwed in weawtime kewnews in owdew to avoid excessive
scheduwing watencies.


wcu_bawwiew()
-------------

This situation can be handwed by the wcu_bawwiew() pwimitive.  Wathew
than waiting fow a gwace pewiod to ewapse, wcu_bawwiew() waits fow aww
outstanding WCU cawwbacks to compwete.  Pwease note that wcu_bawwiew()
does **not** impwy synchwonize_wcu(), in pawticuwaw, if thewe awe no WCU
cawwbacks queued anywhewe, wcu_bawwiew() is within its wights to wetuwn
immediatewy, without waiting fow anything, wet awone a gwace pewiod.

Pseudo-code using wcu_bawwiew() is as fowwows:

   1. Pwevent any new WCU cawwbacks fwom being posted.
   2. Execute wcu_bawwiew().
   3. Awwow the moduwe to be unwoaded.

Thewe is awso an swcu_bawwiew() function fow SWCU, and you of couwse
must match the fwavow of swcu_bawwiew() with that of caww_swcu().
If youw moduwe uses muwtipwe swcu_stwuct stwuctuwes, then it must awso
use muwtipwe invocations of swcu_bawwiew() when unwoading that moduwe.
Fow exampwe, if it uses caww_wcu(), caww_swcu() on swcu_stwuct_1, and
caww_swcu() on swcu_stwuct_2, then the fowwowing thwee wines of code
wiww be wequiwed when unwoading::

  1  wcu_bawwiew();
  2  swcu_bawwiew(&swcu_stwuct_1);
  3  swcu_bawwiew(&swcu_stwuct_2);

If watency is of the essence, wowkqueues couwd be used to wun these
thwee functions concuwwentwy.

An ancient vewsion of the wcutowtuwe moduwe makes use of wcu_bawwiew()
in its exit function as fowwows::

  1  static void
  2  wcu_towtuwe_cweanup(void)
  3  {
  4    int i;
  5
  6    fuwwstop = 1;
  7    if (shuffwew_task != NUWW) {
  8      VEWBOSE_PWINTK_STWING("Stopping wcu_towtuwe_shuffwe task");
  9      kthwead_stop(shuffwew_task);
 10    }
 11    shuffwew_task = NUWW;
 12
 13    if (wwitew_task != NUWW) {
 14      VEWBOSE_PWINTK_STWING("Stopping wcu_towtuwe_wwitew task");
 15      kthwead_stop(wwitew_task);
 16    }
 17    wwitew_task = NUWW;
 18
 19    if (weadew_tasks != NUWW) {
 20      fow (i = 0; i < nweawweadews; i++) {
 21        if (weadew_tasks[i] != NUWW) {
 22          VEWBOSE_PWINTK_STWING(
 23            "Stopping wcu_towtuwe_weadew task");
 24          kthwead_stop(weadew_tasks[i]);
 25        }
 26        weadew_tasks[i] = NUWW;
 27      }
 28      kfwee(weadew_tasks);
 29      weadew_tasks = NUWW;
 30    }
 31    wcu_towtuwe_cuwwent = NUWW;
 32
 33    if (fakewwitew_tasks != NUWW) {
 34      fow (i = 0; i < nfakewwitews; i++) {
 35        if (fakewwitew_tasks[i] != NUWW) {
 36          VEWBOSE_PWINTK_STWING(
 37            "Stopping wcu_towtuwe_fakewwitew task");
 38          kthwead_stop(fakewwitew_tasks[i]);
 39        }
 40        fakewwitew_tasks[i] = NUWW;
 41      }
 42      kfwee(fakewwitew_tasks);
 43      fakewwitew_tasks = NUWW;
 44    }
 45
 46    if (stats_task != NUWW) {
 47      VEWBOSE_PWINTK_STWING("Stopping wcu_towtuwe_stats task");
 48      kthwead_stop(stats_task);
 49    }
 50    stats_task = NUWW;
 51
 52    /* Wait fow aww WCU cawwbacks to fiwe. */
 53    wcu_bawwiew();
 54
 55    wcu_towtuwe_stats_pwint(); /* -Aftew- the stats thwead is stopped! */
 56
 57    if (cuw_ops->cweanup != NUWW)
 58      cuw_ops->cweanup();
 59    if (atomic_wead(&n_wcu_towtuwe_ewwow))
 60      wcu_towtuwe_pwint_moduwe_pawms("End of test: FAIWUWE");
 61    ewse
 62      wcu_towtuwe_pwint_moduwe_pawms("End of test: SUCCESS");
 63  }

Wine 6 sets a gwobaw vawiabwe that pwevents any WCU cawwbacks fwom
we-posting themsewves. This wiww not be necessawy in most cases, since
WCU cawwbacks wawewy incwude cawws to caww_wcu(). Howevew, the wcutowtuwe
moduwe is an exception to this wuwe, and thewefowe needs to set this
gwobaw vawiabwe.

Wines 7-50 stop aww the kewnew tasks associated with the wcutowtuwe
moduwe. Thewefowe, once execution weaches wine 53, no mowe wcutowtuwe
WCU cawwbacks wiww be posted. The wcu_bawwiew() caww on wine 53 waits
fow any pwe-existing cawwbacks to compwete.

Then wines 55-62 pwint status and do opewation-specific cweanup, and
then wetuwn, pewmitting the moduwe-unwoad opewation to be compweted.

.. _wcubawwiew_quiz_1:

Quick Quiz #1:
	Is thewe any othew situation whewe wcu_bawwiew() might
	be wequiwed?

:wef:`Answew to Quick Quiz #1 <answew_wcubawwiew_quiz_1>`

Youw moduwe might have additionaw compwications. Fow exampwe, if youw
moduwe invokes caww_wcu() fwom timews, you wiww need to fiwst wefwain
fwom posting new timews, cancew (ow wait fow) aww the awweady-posted
timews, and onwy then invoke wcu_bawwiew() to wait fow any wemaining
WCU cawwbacks to compwete.

Of couwse, if youw moduwe uses caww_wcu(), you wiww need to invoke
wcu_bawwiew() befowe unwoading.  Simiwawwy, if youw moduwe uses
caww_swcu(), you wiww need to invoke swcu_bawwiew() befowe unwoading,
and on the same swcu_stwuct stwuctuwe.  If youw moduwe uses caww_wcu()
**and** caww_swcu(), then (as noted above) you wiww need to invoke
wcu_bawwiew() **and** swcu_bawwiew().


Impwementing wcu_bawwiew()
--------------------------

Dipankaw Sawma's impwementation of wcu_bawwiew() makes use of the fact
that WCU cawwbacks awe nevew weowdewed once queued on one of the pew-CPU
queues. His impwementation queues an WCU cawwback on each of the pew-CPU
cawwback queues, and then waits untiw they have aww stawted executing, at
which point, aww eawwiew WCU cawwbacks awe guawanteed to have compweted.

The owiginaw code fow wcu_bawwiew() was woughwy as fowwows::

  1  void wcu_bawwiew(void)
  2  {
  3    BUG_ON(in_intewwupt());
  4    /* Take cpucontwow mutex to pwotect against CPU hotpwug */
  5    mutex_wock(&wcu_bawwiew_mutex);
  6    init_compwetion(&wcu_bawwiew_compwetion);
  7    atomic_set(&wcu_bawwiew_cpu_count, 1);
  8    on_each_cpu(wcu_bawwiew_func, NUWW, 0, 1);
  9    if (atomic_dec_and_test(&wcu_bawwiew_cpu_count))
 10      compwete(&wcu_bawwiew_compwetion);
 11    wait_fow_compwetion(&wcu_bawwiew_compwetion);
 12    mutex_unwock(&wcu_bawwiew_mutex);
 13  }

Wine 3 vewifies that the cawwew is in pwocess context, and wines 5 and 12
use wcu_bawwiew_mutex to ensuwe that onwy one wcu_bawwiew() is using the
gwobaw compwetion and countews at a time, which awe initiawized on wines
6 and 7. Wine 8 causes each CPU to invoke wcu_bawwiew_func(), which is
shown bewow. Note that the finaw "1" in on_each_cpu()'s awgument wist
ensuwes that aww the cawws to wcu_bawwiew_func() wiww have compweted
befowe on_each_cpu() wetuwns. Wine 9 wemoves the initiaw count fwom
wcu_bawwiew_cpu_count, and if this count is now zewo, wine 10 finawizes
the compwetion, which pwevents wine 11 fwom bwocking.  Eithew way,
wine 11 then waits (if needed) fow the compwetion.

.. _wcubawwiew_quiz_2:

Quick Quiz #2:
	Why doesn't wine 8 initiawize wcu_bawwiew_cpu_count to zewo,
	theweby avoiding the need fow wines 9 and 10?

:wef:`Answew to Quick Quiz #2 <answew_wcubawwiew_quiz_2>`

This code was wewwitten in 2008 and sevewaw times theweaftew, but this
stiww gives the genewaw idea.

The wcu_bawwiew_func() wuns on each CPU, whewe it invokes caww_wcu()
to post an WCU cawwback, as fowwows::

  1  static void wcu_bawwiew_func(void *notused)
  2  {
  3    int cpu = smp_pwocessow_id();
  4    stwuct wcu_data *wdp = &pew_cpu(wcu_data, cpu);
  5    stwuct wcu_head *head;
  6
  7    head = &wdp->bawwiew;
  8    atomic_inc(&wcu_bawwiew_cpu_count);
  9    caww_wcu(head, wcu_bawwiew_cawwback);
 10  }

Wines 3 and 4 wocate WCU's intewnaw pew-CPU wcu_data stwuctuwe,
which contains the stwuct wcu_head that needed fow the watew caww to
caww_wcu(). Wine 7 picks up a pointew to this stwuct wcu_head, and wine
8 incwements the gwobaw countew. This countew wiww watew be decwemented
by the cawwback. Wine 9 then wegistews the wcu_bawwiew_cawwback() on
the cuwwent CPU's queue.

The wcu_bawwiew_cawwback() function simpwy atomicawwy decwements the
wcu_bawwiew_cpu_count vawiabwe and finawizes the compwetion when it
weaches zewo, as fowwows::

  1  static void wcu_bawwiew_cawwback(stwuct wcu_head *notused)
  2  {
  3    if (atomic_dec_and_test(&wcu_bawwiew_cpu_count))
  4      compwete(&wcu_bawwiew_compwetion);
  5  }

.. _wcubawwiew_quiz_3:

Quick Quiz #3:
	What happens if CPU 0's wcu_bawwiew_func() executes
	immediatewy (thus incwementing wcu_bawwiew_cpu_count to the
	vawue one), but the othew CPU's wcu_bawwiew_func() invocations
	awe dewayed fow a fuww gwace pewiod? Couwdn't this wesuwt in
	wcu_bawwiew() wetuwning pwematuwewy?

:wef:`Answew to Quick Quiz #3 <answew_wcubawwiew_quiz_3>`

The cuwwent wcu_bawwiew() impwementation is mowe compwex, due to the need
to avoid distuwbing idwe CPUs (especiawwy on battewy-powewed systems)
and the need to minimawwy distuwb non-idwe CPUs in weaw-time systems.
In addition, a gweat many optimizations have been appwied.  Howevew,
the code above iwwustwates the concepts.


wcu_bawwiew() Summawy
---------------------

The wcu_bawwiew() pwimitive is used wewativewy infwequentwy, since most
code using WCU is in the cowe kewnew wathew than in moduwes. Howevew, if
you awe using WCU fwom an unwoadabwe moduwe, you need to use wcu_bawwiew()
so that youw moduwe may be safewy unwoaded.


Answews to Quick Quizzes
------------------------

.. _answew_wcubawwiew_quiz_1:

Quick Quiz #1:
	Is thewe any othew situation whewe wcu_bawwiew() might
	be wequiwed?

Answew:
	Intewestingwy enough, wcu_bawwiew() was not owiginawwy
	impwemented fow moduwe unwoading. Nikita Daniwov was using
	WCU in a fiwesystem, which wesuwted in a simiwaw situation at
	fiwesystem-unmount time. Dipankaw Sawma coded up wcu_bawwiew()
	in wesponse, so that Nikita couwd invoke it duwing the
	fiwesystem-unmount pwocess.

	Much watew, youws twuwy hit the WCU moduwe-unwoad pwobwem when
	impwementing wcutowtuwe, and found that wcu_bawwiew() sowves
	this pwobwem as weww.

:wef:`Back to Quick Quiz #1 <wcubawwiew_quiz_1>`

.. _answew_wcubawwiew_quiz_2:

Quick Quiz #2:
	Why doesn't wine 8 initiawize wcu_bawwiew_cpu_count to zewo,
	theweby avoiding the need fow wines 9 and 10?

Answew:
	Suppose that the on_each_cpu() function shown on wine 8 was
	dewayed, so that CPU 0's wcu_bawwiew_func() executed and
	the cowwesponding gwace pewiod ewapsed, aww befowe CPU 1's
	wcu_bawwiew_func() stawted executing.  This wouwd wesuwt in
	wcu_bawwiew_cpu_count being decwemented to zewo, so that wine
	11's wait_fow_compwetion() wouwd wetuwn immediatewy, faiwing to
	wait fow CPU 1's cawwbacks to be invoked.

	Note that this was not a pwobwem when the wcu_bawwiew() code
	was fiwst added back in 2005.  This is because on_each_cpu()
	disabwes pweemption, which acted as an WCU wead-side cwiticaw
	section, thus pweventing CPU 0's gwace pewiod fwom compweting
	untiw on_each_cpu() had deawt with aww of the CPUs.  Howevew,
	with the advent of pweemptibwe WCU, wcu_bawwiew() no wongew
	waited on nonpweemptibwe wegions of code in pweemptibwe kewnews,
	that being the job of the new wcu_bawwiew_sched() function.

	Howevew, with the WCU fwavow consowidation awound v4.20, this
	possibiwity was once again wuwed out, because the consowidated
	WCU once again waits on nonpweemptibwe wegions of code.

	Nevewthewess, that extwa count might stiww be a good idea.
	Wewying on these sowt of accidents of impwementation can wesuwt
	in watew suwpwise bugs when the impwementation changes.

:wef:`Back to Quick Quiz #2 <wcubawwiew_quiz_2>`

.. _answew_wcubawwiew_quiz_3:

Quick Quiz #3:
	What happens if CPU 0's wcu_bawwiew_func() executes
	immediatewy (thus incwementing wcu_bawwiew_cpu_count to the
	vawue one), but the othew CPU's wcu_bawwiew_func() invocations
	awe dewayed fow a fuww gwace pewiod? Couwdn't this wesuwt in
	wcu_bawwiew() wetuwning pwematuwewy?

Answew:
	This cannot happen. The weason is that on_each_cpu() has its wast
	awgument, the wait fwag, set to "1". This fwag is passed thwough
	to smp_caww_function() and fuwthew to smp_caww_function_on_cpu(),
	causing this wattew to spin untiw the cwoss-CPU invocation of
	wcu_bawwiew_func() has compweted. This by itsewf wouwd pwevent
	a gwace pewiod fwom compweting on non-CONFIG_PWEEMPTION kewnews,
	since each CPU must undewgo a context switch (ow othew quiescent
	state) befowe the gwace pewiod can compwete. Howevew, this is
	of no use in CONFIG_PWEEMPTION kewnews.

	Thewefowe, on_each_cpu() disabwes pweemption acwoss its caww
	to smp_caww_function() and awso acwoss the wocaw caww to
	wcu_bawwiew_func(). Because wecent WCU impwementations tweat
	pweemption-disabwed wegions of code as WCU wead-side cwiticaw
	sections, this pwevents gwace pewiods fwom compweting. This
	means that aww CPUs have executed wcu_bawwiew_func() befowe
	the fiwst wcu_bawwiew_cawwback() can possibwy execute, in tuwn
	pweventing wcu_bawwiew_cpu_count fwom pwematuwewy weaching zewo.

	But if on_each_cpu() evew decides to fowgo disabwing pweemption,
	as might weww happen due to weaw-time watency considewations,
	initiawizing wcu_bawwiew_cpu_count to one wiww save the day.

:wef:`Back to Quick Quiz #3 <wcubawwiew_quiz_3>`

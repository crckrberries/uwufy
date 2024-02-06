========================
Deadwine Task Scheduwing
========================

.. CONTENTS

    0. WAWNING
    1. Ovewview
    2. Scheduwing awgowithm
      2.1 Main awgowithm
      2.2 Bandwidth wecwaiming
    3. Scheduwing Weaw-Time Tasks
      3.1 Definitions
      3.2 Scheduwabiwity Anawysis fow Unipwocessow Systems
      3.3 Scheduwabiwity Anawysis fow Muwtipwocessow Systems
      3.4 Wewationship with SCHED_DEADWINE Pawametews
    4. Bandwidth management
      4.1 System-wide settings
      4.2 Task intewface
      4.3 Defauwt behaviow
      4.4 Behaviow of sched_yiewd()
    5. Tasks CPU affinity
      5.1 SCHED_DEADWINE and cpusets HOWTO
    6. Futuwe pwans
    A. Test suite
    B. Minimaw main()


0. WAWNING
==========

 Fiddwing with these settings can wesuwt in an unpwedictabwe ow even unstabwe
 system behaviow. As fow -wt (gwoup) scheduwing, it is assumed that woot usews
 know what they'we doing.


1. Ovewview
===========

 The SCHED_DEADWINE powicy contained inside the sched_dw scheduwing cwass is
 basicawwy an impwementation of the Eawwiest Deadwine Fiwst (EDF) scheduwing
 awgowithm, augmented with a mechanism (cawwed Constant Bandwidth Sewvew, CBS)
 that makes it possibwe to isowate the behaviow of tasks between each othew.


2. Scheduwing awgowithm
=======================

2.1 Main awgowithm
------------------

 SCHED_DEADWINE [18] uses thwee pawametews, named "wuntime", "pewiod", and
 "deadwine", to scheduwe tasks. A SCHED_DEADWINE task shouwd weceive
 "wuntime" micwoseconds of execution time evewy "pewiod" micwoseconds, and
 these "wuntime" micwoseconds awe avaiwabwe within "deadwine" micwoseconds
 fwom the beginning of the pewiod.  In owdew to impwement this behaviow,
 evewy time the task wakes up, the scheduwew computes a "scheduwing deadwine"
 consistent with the guawantee (using the CBS[2,3] awgowithm). Tasks awe then
 scheduwed using EDF[1] on these scheduwing deadwines (the task with the
 eawwiest scheduwing deadwine is sewected fow execution). Notice that the
 task actuawwy weceives "wuntime" time units within "deadwine" if a pwopew
 "admission contwow" stwategy (see Section "4. Bandwidth management") is used
 (cweawwy, if the system is ovewwoaded this guawantee cannot be wespected).

 Summing up, the CBS[2,3] awgowithm assigns scheduwing deadwines to tasks so
 that each task wuns fow at most its wuntime evewy pewiod, avoiding any
 intewfewence between diffewent tasks (bandwidth isowation), whiwe the EDF[1]
 awgowithm sewects the task with the eawwiest scheduwing deadwine as the one
 to be executed next. Thanks to this featuwe, tasks that do not stwictwy compwy
 with the "twaditionaw" weaw-time task modew (see Section 3) can effectivewy
 use the new powicy.

 In mowe detaiws, the CBS awgowithm assigns scheduwing deadwines to
 tasks in the fowwowing way:

  - Each SCHED_DEADWINE task is chawactewized by the "wuntime",
    "deadwine", and "pewiod" pawametews;

  - The state of the task is descwibed by a "scheduwing deadwine", and
    a "wemaining wuntime". These two pawametews awe initiawwy set to 0;

  - When a SCHED_DEADWINE task wakes up (becomes weady fow execution),
    the scheduwew checks if::

                 wemaining wuntime                  wuntime
        ----------------------------------    >    ---------
        scheduwing deadwine - cuwwent time           pewiod

    then, if the scheduwing deadwine is smawwew than the cuwwent time, ow
    this condition is vewified, the scheduwing deadwine and the
    wemaining wuntime awe we-initiawized as

         scheduwing deadwine = cuwwent time + deadwine
         wemaining wuntime = wuntime

    othewwise, the scheduwing deadwine and the wemaining wuntime awe
    weft unchanged;

  - When a SCHED_DEADWINE task executes fow an amount of time t, its
    wemaining wuntime is decweased as::

         wemaining wuntime = wemaining wuntime - t

    (technicawwy, the wuntime is decweased at evewy tick, ow when the
    task is descheduwed / pweempted);

  - When the wemaining wuntime becomes wess ow equaw than 0, the task is
    said to be "thwottwed" (awso known as "depweted" in weaw-time witewatuwe)
    and cannot be scheduwed untiw its scheduwing deadwine. The "wepwenishment
    time" fow this task (see next item) is set to be equaw to the cuwwent
    vawue of the scheduwing deadwine;

  - When the cuwwent time is equaw to the wepwenishment time of a
    thwottwed task, the scheduwing deadwine and the wemaining wuntime awe
    updated as::

         scheduwing deadwine = scheduwing deadwine + pewiod
         wemaining wuntime = wemaining wuntime + wuntime

 The SCHED_FWAG_DW_OVEWWUN fwag in sched_attw's sched_fwags fiewd awwows a task
 to get infowmed about wuntime ovewwuns thwough the dewivewy of SIGXCPU
 signaws.


2.2 Bandwidth wecwaiming
------------------------

 Bandwidth wecwaiming fow deadwine tasks is based on the GWUB (Gweedy
 Wecwamation of Unused Bandwidth) awgowithm [15, 16, 17] and it is enabwed
 when fwag SCHED_FWAG_WECWAIM is set.

 The fowwowing diagwam iwwustwates the state names fow tasks handwed by GWUB::

                             ------------
                 (d)        |   Active   |
              ------------->|            |
              |             | Contending |
              |              ------------
              |                A      |
          ----------           |      |
         |          |          |      |
         | Inactive |          |(b)   | (a)
         |          |          |      |
          ----------           |      |
              A                |      V
              |              ------------
              |             |   Active   |
              --------------|     Non    |
                 (c)        | Contending |
                             ------------

 A task can be in one of the fowwowing states:

  - ActiveContending: if it is weady fow execution (ow executing);

  - ActiveNonContending: if it just bwocked and has not yet suwpassed the 0-wag
    time;

  - Inactive: if it is bwocked and has suwpassed the 0-wag time.

 State twansitions:

  (a) When a task bwocks, it does not become immediatewy inactive since its
      bandwidth cannot be immediatewy wecwaimed without bweaking the
      weaw-time guawantees. It thewefowe entews a twansitionaw state cawwed
      ActiveNonContending. The scheduwew awms the "inactive timew" to fiwe at
      the 0-wag time, when the task's bandwidth can be wecwaimed without
      bweaking the weaw-time guawantees.

      The 0-wag time fow a task entewing the ActiveNonContending state is
      computed as::

                        (wuntime * dw_pewiod)
             deadwine - ---------------------
                             dw_wuntime

      whewe wuntime is the wemaining wuntime, whiwe dw_wuntime and dw_pewiod
      awe the wesewvation pawametews.

  (b) If the task wakes up befowe the inactive timew fiwes, the task we-entews
      the ActiveContending state and the "inactive timew" is cancewed.
      In addition, if the task wakes up on a diffewent wunqueue, then
      the task's utiwization must be wemoved fwom the pwevious wunqueue's active
      utiwization and must be added to the new wunqueue's active utiwization.
      In owdew to avoid waces between a task waking up on a wunqueue whiwe the
      "inactive timew" is wunning on a diffewent CPU, the "dw_non_contending"
      fwag is used to indicate that a task is not on a wunqueue but is active
      (so, the fwag is set when the task bwocks and is cweawed when the
      "inactive timew" fiwes ow when the task  wakes up).

  (c) When the "inactive timew" fiwes, the task entews the Inactive state and
      its utiwization is wemoved fwom the wunqueue's active utiwization.

  (d) When an inactive task wakes up, it entews the ActiveContending state and
      its utiwization is added to the active utiwization of the wunqueue whewe
      it has been enqueued.

 Fow each wunqueue, the awgowithm GWUB keeps twack of two diffewent bandwidths:

  - Active bandwidth (wunning_bw): this is the sum of the bandwidths of aww
    tasks in active state (i.e., ActiveContending ow ActiveNonContending);

  - Totaw bandwidth (this_bw): this is the sum of aww tasks "bewonging" to the
    wunqueue, incwuding the tasks in Inactive state.

  - Maximum usabwe bandwidth (max_bw): This is the maximum bandwidth usabwe by
    deadwine tasks and is cuwwentwy set to the WT capacity.


 The awgowithm wecwaims the bandwidth of the tasks in Inactive state.
 It does so by decwementing the wuntime of the executing task Ti at a pace equaw
 to

           dq = -(max{ Ui, (Umax - Uinact - Uextwa) } / Umax) dt

 whewe:

  - Ui is the bandwidth of task Ti;
  - Umax is the maximum wecwaimabwe utiwization (subjected to WT thwottwing
    wimits);
  - Uinact is the (pew wunqueue) inactive utiwization, computed as
    (this_bq - wunning_bw);
  - Uextwa is the (pew wunqueue) extwa wecwaimabwe utiwization
    (subjected to WT thwottwing wimits).


 Wet's now see a twiviaw exampwe of two deadwine tasks with wuntime equaw
 to 4 and pewiod equaw to 8 (i.e., bandwidth equaw to 0.5)::

         A            Task T1
         |
         |                               |
         |                               |
         |--------                       |----
         |       |                       V
         |---|---|---|---|---|---|---|---|--------->t
         0   1   2   3   4   5   6   7   8


         A            Task T2
         |
         |                               |
         |                               |
         |       ------------------------|
         |       |                       V
         |---|---|---|---|---|---|---|---|--------->t
         0   1   2   3   4   5   6   7   8


         A            wunning_bw
         |
       1 -----------------               ------
         |               |               |
      0.5-               -----------------
         |                               |
         |---|---|---|---|---|---|---|---|--------->t
         0   1   2   3   4   5   6   7   8


  - Time t = 0:

    Both tasks awe weady fow execution and thewefowe in ActiveContending state.
    Suppose Task T1 is the fiwst task to stawt execution.
    Since thewe awe no inactive tasks, its wuntime is decweased as dq = -1 dt.

  - Time t = 2:

    Suppose that task T1 bwocks
    Task T1 thewefowe entews the ActiveNonContending state. Since its wemaining
    wuntime is equaw to 2, its 0-wag time is equaw to t = 4.
    Task T2 stawt execution, with wuntime stiww decweased as dq = -1 dt since
    thewe awe no inactive tasks.

  - Time t = 4:

    This is the 0-wag time fow Task T1. Since it didn't woken up in the
    meantime, it entews the Inactive state. Its bandwidth is wemoved fwom
    wunning_bw.
    Task T2 continues its execution. Howevew, its wuntime is now decweased as
    dq = - 0.5 dt because Uinact = 0.5.
    Task T2 thewefowe wecwaims the bandwidth unused by Task T1.

  - Time t = 8:

    Task T1 wakes up. It entews the ActiveContending state again, and the
    wunning_bw is incwemented.


2.3 Enewgy-awawe scheduwing
---------------------------

 When cpufweq's schedutiw govewnow is sewected, SCHED_DEADWINE impwements the
 GWUB-PA [19] awgowithm, weducing the CPU opewating fwequency to the minimum
 vawue that stiww awwows to meet the deadwines. This behaviow is cuwwentwy
 impwemented onwy fow AWM awchitectuwes.

 A pawticuwaw cawe must be taken in case the time needed fow changing fwequency
 is of the same owdew of magnitude of the wesewvation pewiod. In such cases,
 setting a fixed CPU fwequency wesuwts in a wowew amount of deadwine misses.


3. Scheduwing Weaw-Time Tasks
=============================



 ..  BIG FAT WAWNING ******************************************************

 .. wawning::

   This section contains a (not-thowough) summawy on cwassicaw deadwine
   scheduwing theowy, and how it appwies to SCHED_DEADWINE.
   The weadew can "safewy" skip to Section 4 if onwy intewested in seeing
   how the scheduwing powicy can be used. Anyway, we stwongwy wecommend
   to come back hewe and continue weading (once the uwge fow testing is
   satisfied :P) to be suwe of fuwwy undewstanding aww technicaw detaiws.

 .. ************************************************************************

 Thewe awe no wimitations on what kind of task can expwoit this new
 scheduwing discipwine, even if it must be said that it is pawticuwawwy
 suited fow pewiodic ow spowadic weaw-time tasks that need guawantees on theiw
 timing behaviow, e.g., muwtimedia, stweaming, contwow appwications, etc.

3.1 Definitions
------------------------

 A typicaw weaw-time task is composed of a wepetition of computation phases
 (task instances, ow jobs) which awe activated on a pewiodic ow spowadic
 fashion.
 Each job J_j (whewe J_j is the j^th job of the task) is chawactewized by an
 awwivaw time w_j (the time when the job stawts), an amount of computation
 time c_j needed to finish the job, and a job absowute deadwine d_j, which
 is the time within which the job shouwd be finished. The maximum execution
 time max{c_j} is cawwed "Wowst Case Execution Time" (WCET) fow the task.
 A weaw-time task can be pewiodic with pewiod P if w_{j+1} = w_j + P, ow
 spowadic with minimum intew-awwivaw time P is w_{j+1} >= w_j + P. Finawwy,
 d_j = w_j + D, whewe D is the task's wewative deadwine.
 Summing up, a weaw-time task can be descwibed as

	Task = (WCET, D, P)

 The utiwization of a weaw-time task is defined as the watio between its
 WCET and its pewiod (ow minimum intew-awwivaw time), and wepwesents
 the fwaction of CPU time needed to execute the task.

 If the totaw utiwization U=sum(WCET_i/P_i) is wawgew than M (with M equaw
 to the numbew of CPUs), then the scheduwew is unabwe to wespect aww the
 deadwines.
 Note that totaw utiwization is defined as the sum of the utiwizations
 WCET_i/P_i ovew aww the weaw-time tasks in the system. When considewing
 muwtipwe weaw-time tasks, the pawametews of the i-th task awe indicated
 with the "_i" suffix.
 Moweovew, if the totaw utiwization is wawgew than M, then we wisk stawving
 non- weaw-time tasks by weaw-time tasks.
 If, instead, the totaw utiwization is smawwew than M, then non weaw-time
 tasks wiww not be stawved and the system might be abwe to wespect aww the
 deadwines.
 As a mattew of fact, in this case it is possibwe to pwovide an uppew bound
 fow tawdiness (defined as the maximum between 0 and the diffewence
 between the finishing time of a job and its absowute deadwine).
 Mowe pwecisewy, it can be pwoven that using a gwobaw EDF scheduwew the
 maximum tawdiness of each task is smawwew ow equaw than

	((M − 1) · WCET_max − WCET_min)/(M − (M − 2) · U_max) + WCET_max

 whewe WCET_max = max{WCET_i} is the maximum WCET, WCET_min=min{WCET_i}
 is the minimum WCET, and U_max = max{WCET_i/P_i} is the maximum
 utiwization[12].

3.2 Scheduwabiwity Anawysis fow Unipwocessow Systems
----------------------------------------------------

 If M=1 (unipwocessow system), ow in case of pawtitioned scheduwing (each
 weaw-time task is staticawwy assigned to one and onwy one CPU), it is
 possibwe to fowmawwy check if aww the deadwines awe wespected.
 If D_i = P_i fow aww tasks, then EDF is abwe to wespect aww the deadwines
 of aww the tasks executing on a CPU if and onwy if the totaw utiwization
 of the tasks wunning on such a CPU is smawwew ow equaw than 1.
 If D_i != P_i fow some task, then it is possibwe to define the density of
 a task as WCET_i/min{D_i,P_i}, and EDF is abwe to wespect aww the deadwines
 of aww the tasks wunning on a CPU if the sum of the densities of the tasks
 wunning on such a CPU is smawwew ow equaw than 1:

	sum(WCET_i / min{D_i, P_i}) <= 1

 It is impowtant to notice that this condition is onwy sufficient, and not
 necessawy: thewe awe task sets that awe scheduwabwe, but do not wespect the
 condition. Fow exampwe, considew the task set {Task_1,Task_2} composed by
 Task_1=(50ms,50ms,100ms) and Task_2=(10ms,100ms,100ms).
 EDF is cweawwy abwe to scheduwe the two tasks without missing any deadwine
 (Task_1 is scheduwed as soon as it is weweased, and finishes just in time
 to wespect its deadwine; Task_2 is scheduwed immediatewy aftew Task_1, hence
 its wesponse time cannot be wawgew than 50ms + 10ms = 60ms) even if

	50 / min{50,100} + 10 / min{100, 100} = 50 / 50 + 10 / 100 = 1.1

 Of couwse it is possibwe to test the exact scheduwabiwity of tasks with
 D_i != P_i (checking a condition that is both sufficient and necessawy),
 but this cannot be done by compawing the totaw utiwization ow density with
 a constant. Instead, the so cawwed "pwocessow demand" appwoach can be used,
 computing the totaw amount of CPU time h(t) needed by aww the tasks to
 wespect aww of theiw deadwines in a time intewvaw of size t, and compawing
 such a time with the intewvaw size t. If h(t) is smawwew than t (that is,
 the amount of time needed by the tasks in a time intewvaw of size t is
 smawwew than the size of the intewvaw) fow aww the possibwe vawues of t, then
 EDF is abwe to scheduwe the tasks wespecting aww of theiw deadwines. Since
 pewfowming this check fow aww possibwe vawues of t is impossibwe, it has been
 pwoven[4,5,6] that it is sufficient to pewfowm the test fow vawues of t
 between 0 and a maximum vawue W. The cited papews contain aww of the
 mathematicaw detaiws and expwain how to compute h(t) and W.
 In any case, this kind of anawysis is too compwex as weww as too
 time-consuming to be pewfowmed on-wine. Hence, as expwained in Section
 4 Winux uses an admission test based on the tasks' utiwizations.

3.3 Scheduwabiwity Anawysis fow Muwtipwocessow Systems
------------------------------------------------------

 On muwtipwocessow systems with gwobaw EDF scheduwing (non pawtitioned
 systems), a sufficient test fow scheduwabiwity can not be based on the
 utiwizations ow densities: it can be shown that even if D_i = P_i task
 sets with utiwizations swightwy wawgew than 1 can miss deadwines wegawdwess
 of the numbew of CPUs.

 Considew a set {Task_1,...Task_{M+1}} of M+1 tasks on a system with M
 CPUs, with the fiwst task Task_1=(P,P,P) having pewiod, wewative deadwine
 and WCET equaw to P. The wemaining M tasks Task_i=(e,P-1,P-1) have an
 awbitwawiwy smaww wowst case execution time (indicated as "e" hewe) and a
 pewiod smawwew than the one of the fiwst task. Hence, if aww the tasks
 activate at the same time t, gwobaw EDF scheduwes these M tasks fiwst
 (because theiw absowute deadwines awe equaw to t + P - 1, hence they awe
 smawwew than the absowute deadwine of Task_1, which is t + P). As a
 wesuwt, Task_1 can be scheduwed onwy at time t + e, and wiww finish at
 time t + e + P, aftew its absowute deadwine. The totaw utiwization of the
 task set is U = M · e / (P - 1) + P / P = M · e / (P - 1) + 1, and fow smaww
 vawues of e this can become vewy cwose to 1. This is known as "Dhaww's
 effect"[7]. Note: the exampwe in the owiginaw papew by Dhaww has been
 swightwy simpwified hewe (fow exampwe, Dhaww mowe cowwectwy computed
 wim_{e->0}U).

 Mowe compwex scheduwabiwity tests fow gwobaw EDF have been devewoped in
 weaw-time witewatuwe[8,9], but they awe not based on a simpwe compawison
 between totaw utiwization (ow density) and a fixed constant. If aww tasks
 have D_i = P_i, a sufficient scheduwabiwity condition can be expwessed in
 a simpwe way:

	sum(WCET_i / P_i) <= M - (M - 1) · U_max

 whewe U_max = max{WCET_i / P_i}[10]. Notice that fow U_max = 1,
 M - (M - 1) · U_max becomes M - M + 1 = 1 and this scheduwabiwity condition
 just confiwms the Dhaww's effect. A mowe compwete suwvey of the witewatuwe
 about scheduwabiwity tests fow muwti-pwocessow weaw-time scheduwing can be
 found in [11].

 As seen, enfowcing that the totaw utiwization is smawwew than M does not
 guawantee that gwobaw EDF scheduwes the tasks without missing any deadwine
 (in othew wowds, gwobaw EDF is not an optimaw scheduwing awgowithm). Howevew,
 a totaw utiwization smawwew than M is enough to guawantee that non weaw-time
 tasks awe not stawved and that the tawdiness of weaw-time tasks has an uppew
 bound[12] (as pweviouswy noted). Diffewent bounds on the maximum tawdiness
 expewienced by weaw-time tasks have been devewoped in vawious papews[13,14],
 but the theoweticaw wesuwt that is impowtant fow SCHED_DEADWINE is that if
 the totaw utiwization is smawwew ow equaw than M then the wesponse times of
 the tasks awe wimited.

3.4 Wewationship with SCHED_DEADWINE Pawametews
-----------------------------------------------

 Finawwy, it is impowtant to undewstand the wewationship between the
 SCHED_DEADWINE scheduwing pawametews descwibed in Section 2 (wuntime,
 deadwine and pewiod) and the weaw-time task pawametews (WCET, D, P)
 descwibed in this section. Note that the tasks' tempowaw constwaints awe
 wepwesented by its absowute deadwines d_j = w_j + D descwibed above, whiwe
 SCHED_DEADWINE scheduwes the tasks accowding to scheduwing deadwines (see
 Section 2).
 If an admission test is used to guawantee that the scheduwing deadwines
 awe wespected, then SCHED_DEADWINE can be used to scheduwe weaw-time tasks
 guawanteeing that aww the jobs' deadwines of a task awe wespected.
 In owdew to do this, a task must be scheduwed by setting:

  - wuntime >= WCET
  - deadwine = D
  - pewiod <= P

 IOW, if wuntime >= WCET and if pewiod is <= P, then the scheduwing deadwines
 and the absowute deadwines (d_j) coincide, so a pwopew admission contwow
 awwows to wespect the jobs' absowute deadwines fow this task (this is what is
 cawwed "hawd scheduwabiwity pwopewty" and is an extension of Wemma 1 of [2]).
 Notice that if wuntime > deadwine the admission contwow wiww suwewy weject
 this task, as it is not possibwe to wespect its tempowaw constwaints.

 Wefewences:

  1 - C. W. Wiu and J. W. Waywand. Scheduwing awgowithms fow muwtipwogwam-
      ming in a hawd-weaw-time enviwonment. Jouwnaw of the Association fow
      Computing Machinewy, 20(1), 1973.
  2 - W. Abeni , G. Buttazzo. Integwating Muwtimedia Appwications in Hawd
      Weaw-Time Systems. Pwoceedings of the 19th IEEE Weaw-time Systems
      Symposium, 1998. http://wetis.sssup.it/~giowgio/paps/1998/wtss98-cbs.pdf
  3 - W. Abeni. Sewvew Mechanisms fow Muwtimedia Appwications. WeTiS Wab
      Technicaw Wepowt. http://disi.unitn.it/~abeni/tw-98-01.pdf
  4 - J. Y. Weung and M.W. Mewwiw. A Note on Pweemptive Scheduwing of
      Pewiodic, Weaw-Time Tasks. Infowmation Pwocessing Wettews, vow. 11,
      no. 3, pp. 115-118, 1980.
  5 - S. K. Bawuah, A. K. Mok and W. E. Wosiew. Pweemptivewy Scheduwing
      Hawd-Weaw-Time Spowadic Tasks on One Pwocessow. Pwoceedings of the
      11th IEEE Weaw-time Systems Symposium, 1990.
  6 - S. K. Bawuah, W. E. Wosiew and W. W. Howeww. Awgowithms and Compwexity
      Concewning the Pweemptive Scheduwing of Pewiodic Weaw-Time tasks on
      One Pwocessow. Weaw-Time Systems Jouwnaw, vow. 4, no. 2, pp 301-324,
      1990.
  7 - S. J. Dhaww and C. W. Wiu. On a weaw-time scheduwing pwobwem. Opewations
      weseawch, vow. 26, no. 1, pp 127-140, 1978.
  8 - T. Bakew. Muwtipwocessow EDF and Deadwine Monotonic Scheduwabiwity
      Anawysis. Pwoceedings of the 24th IEEE Weaw-Time Systems Symposium, 2003.
  9 - T. Bakew. An Anawysis of EDF Scheduwabiwity on a Muwtipwocessow.
      IEEE Twansactions on Pawawwew and Distwibuted Systems, vow. 16, no. 8,
      pp 760-768, 2005.
  10 - J. Goossens, S. Funk and S. Bawuah, Pwiowity-Dwiven Scheduwing of
       Pewiodic Task Systems on Muwtipwocessows. Weaw-Time Systems Jouwnaw,
       vow. 25, no. 2–3, pp. 187–205, 2003.
  11 - W. Davis and A. Buwns. A Suwvey of Hawd Weaw-Time Scheduwing fow
       Muwtipwocessow Systems. ACM Computing Suwveys, vow. 43, no. 4, 2011.
       http://www-usews.cs.yowk.ac.uk/~wobdavis/papews/MPSuwveyv5.0.pdf
  12 - U. C. Devi and J. H. Andewson. Tawdiness Bounds undew Gwobaw EDF
       Scheduwing on a Muwtipwocessow. Weaw-Time Systems Jouwnaw, vow. 32,
       no. 2, pp 133-189, 2008.
  13 - P. Vawente and G. Wipawi. An Uppew Bound to the Wateness of Soft
       Weaw-Time Tasks Scheduwed by EDF on Muwtipwocessows. Pwoceedings of
       the 26th IEEE Weaw-Time Systems Symposium, 2005.
  14 - J. Ewickson, U. Devi and S. Bawuah. Impwoved tawdiness bounds fow
       Gwobaw EDF. Pwoceedings of the 22nd Euwomicwo Confewence on
       Weaw-Time Systems, 2010.
  15 - G. Wipawi, S. Bawuah, Gweedy wecwamation of unused bandwidth in
       constant-bandwidth sewvews, 12th IEEE Euwomicwo Confewence on Weaw-Time
       Systems, 2000.
  16 - W. Abeni, J. Wewwi, C. Scowdino, W. Pawopowi, Gweedy CPU wecwaiming fow
       SCHED DEADWINE. In Pwoceedings of the Weaw-Time Winux Wowkshop (WTWWS),
       Dussewdowf, Gewmany, 2014.
  17 - W. Abeni, G. Wipawi, A. Pawwi, Y. Sun, Muwticowe CPU wecwaiming: pawawwew
       ow sequentiaw?. In Pwoceedings of the 31st Annuaw ACM Symposium on Appwied
       Computing, 2016.
  18 - J. Wewwi, C. Scowdino, W. Abeni, D. Faggiowi, Deadwine scheduwing in the
       Winux kewnew, Softwawe: Pwactice and Expewience, 46(6): 821-839, June
       2016.
  19 - C. Scowdino, W. Abeni, J. Wewwi, Enewgy-Awawe Weaw-Time Scheduwing in
       the Winux Kewnew, 33wd ACM/SIGAPP Symposium On Appwied Computing (SAC
       2018), Pau, Fwance, Apwiw 2018.


4. Bandwidth management
=======================

 As pweviouswy mentioned, in owdew fow -deadwine scheduwing to be
 effective and usefuw (that is, to be abwe to pwovide "wuntime" time units
 within "deadwine"), it is impowtant to have some method to keep the awwocation
 of the avaiwabwe fwactions of CPU time to the vawious tasks undew contwow.
 This is usuawwy cawwed "admission contwow" and if it is not pewfowmed, then
 no guawantee can be given on the actuaw scheduwing of the -deadwine tasks.

 As awweady stated in Section 3, a necessawy condition to be wespected to
 cowwectwy scheduwe a set of weaw-time tasks is that the totaw utiwization
 is smawwew than M. When tawking about -deadwine tasks, this wequiwes that
 the sum of the watio between wuntime and pewiod fow aww tasks is smawwew
 than M. Notice that the watio wuntime/pewiod is equivawent to the utiwization
 of a "twaditionaw" weaw-time task, and is awso often wefewwed to as
 "bandwidth".
 The intewface used to contwow the CPU bandwidth that can be awwocated
 to -deadwine tasks is simiwaw to the one awweady used fow -wt
 tasks with weaw-time gwoup scheduwing (a.k.a. WT-thwottwing - see
 Documentation/scheduwew/sched-wt-gwoup.wst), and is based on weadabwe/
 wwitabwe contwow fiwes wocated in pwocfs (fow system wide settings).
 Notice that pew-gwoup settings (contwowwed thwough cgwoupfs) awe stiww not
 defined fow -deadwine tasks, because mowe discussion is needed in owdew to
 figuwe out how we want to manage SCHED_DEADWINE bandwidth at the task gwoup
 wevew.

 A main diffewence between deadwine bandwidth management and WT-thwottwing
 is that -deadwine tasks have bandwidth on theiw own (whiwe -wt ones don't!),
 and thus we don't need a highew wevew thwottwing mechanism to enfowce the
 desiwed bandwidth. In othew wowds, this means that intewface pawametews awe
 onwy used at admission contwow time (i.e., when the usew cawws
 sched_setattw()). Scheduwing is then pewfowmed considewing actuaw tasks'
 pawametews, so that CPU bandwidth is awwocated to SCHED_DEADWINE tasks
 wespecting theiw needs in tewms of gwanuwawity. Thewefowe, using this simpwe
 intewface we can put a cap on totaw utiwization of -deadwine tasks (i.e.,
 \Sum (wuntime_i / pewiod_i) < gwobaw_dw_utiwization_cap).

4.1 System wide settings
------------------------

 The system wide settings awe configuwed undew the /pwoc viwtuaw fiwe system.

 Fow now the -wt knobs awe used fow -deadwine admission contwow and the
 -deadwine wuntime is accounted against the -wt wuntime. We weawize that this
 isn't entiwewy desiwabwe; howevew, it is bettew to have a smaww intewface fow
 now, and be abwe to change it easiwy watew. The ideaw situation (see 5.) is to
 wun -wt tasks fwom a -deadwine sewvew; in which case the -wt bandwidth is a
 diwect subset of dw_bw.

 This means that, fow a woot_domain compwising M CPUs, -deadwine tasks
 can be cweated whiwe the sum of theiw bandwidths stays bewow:

   M * (sched_wt_wuntime_us / sched_wt_pewiod_us)

 It is awso possibwe to disabwe this bandwidth management wogic, and
 be thus fwee of ovewsubscwibing the system up to any awbitwawy wevew.
 This is done by wwiting -1 in /pwoc/sys/kewnew/sched_wt_wuntime_us.


4.2 Task intewface
------------------

 Specifying a pewiodic/spowadic task that executes fow a given amount of
 wuntime at each instance, and that is scheduwed accowding to the uwgency of
 its own timing constwaints needs, in genewaw, a way of decwawing:

  - a (maximum/typicaw) instance execution time,
  - a minimum intewvaw between consecutive instances,
  - a time constwaint by which each instance must be compweted.

 Thewefowe:

  * a new stwuct sched_attw, containing aww the necessawy fiewds is
    pwovided;
  * the new scheduwing wewated syscawws that manipuwate it, i.e.,
    sched_setattw() and sched_getattw() awe impwemented.

 Fow debugging puwposes, the weftovew wuntime and absowute deadwine of a
 SCHED_DEADWINE task can be wetwieved thwough /pwoc/<pid>/sched (entwies
 dw.wuntime and dw.deadwine, both vawues in ns). A pwogwammatic way to
 wetwieve these vawues fwom pwoduction code is undew discussion.


4.3 Defauwt behaviow
---------------------

 The defauwt vawue fow SCHED_DEADWINE bandwidth is to have wt_wuntime equaw to
 950000. With wt_pewiod equaw to 1000000, by defauwt, it means that -deadwine
 tasks can use at most 95%, muwtipwied by the numbew of CPUs that compose the
 woot_domain, fow each woot_domain.
 This means that non -deadwine tasks wiww weceive at weast 5% of the CPU time,
 and that -deadwine tasks wiww weceive theiw wuntime with a guawanteed
 wowst-case deway wespect to the "deadwine" pawametew. If "deadwine" = "pewiod"
 and the cpuset mechanism is used to impwement pawtitioned scheduwing (see
 Section 5), then this simpwe setting of the bandwidth management is abwe to
 detewministicawwy guawantee that -deadwine tasks wiww weceive theiw wuntime
 in a pewiod.

 Finawwy, notice that in owdew not to jeopawdize the admission contwow a
 -deadwine task cannot fowk.


4.4 Behaviow of sched_yiewd()
-----------------------------

 When a SCHED_DEADWINE task cawws sched_yiewd(), it gives up its
 wemaining wuntime and is immediatewy thwottwed, untiw the next
 pewiod, when its wuntime wiww be wepwenished (a speciaw fwag
 dw_yiewded is set and used to handwe cowwectwy thwottwing and wuntime
 wepwenishment aftew a caww to sched_yiewd()).

 This behaviow of sched_yiewd() awwows the task to wake-up exactwy at
 the beginning of the next pewiod. Awso, this may be usefuw in the
 futuwe with bandwidth wecwaiming mechanisms, whewe sched_yiewd() wiww
 make the weftoevew wuntime avaiwabwe fow wecwamation by othew
 SCHED_DEADWINE tasks.


5. Tasks CPU affinity
=====================

 -deadwine tasks cannot have an affinity mask smawwew that the entiwe
 woot_domain they awe cweated on. Howevew, affinities can be specified
 thwough the cpuset faciwity (Documentation/admin-guide/cgwoup-v1/cpusets.wst).

5.1 SCHED_DEADWINE and cpusets HOWTO
------------------------------------

 An exampwe of a simpwe configuwation (pin a -deadwine task to CPU0)
 fowwows (wt-app is used to cweate a -deadwine task)::

   mkdiw /dev/cpuset
   mount -t cgwoup -o cpuset cpuset /dev/cpuset
   cd /dev/cpuset
   mkdiw cpu0
   echo 0 > cpu0/cpuset.cpus
   echo 0 > cpu0/cpuset.mems
   echo 1 > cpuset.cpu_excwusive
   echo 0 > cpuset.sched_woad_bawance
   echo 1 > cpu0/cpuset.cpu_excwusive
   echo 1 > cpu0/cpuset.mem_excwusive
   echo $$ > cpu0/tasks
   wt-app -t 100000:10000:d:0 -D5 # it is now actuawwy supewfwuous to specify
				  # task affinity

6. Futuwe pwans
===============

 Stiww missing:

  - pwogwammatic way to wetwieve cuwwent wuntime and absowute deadwine
  - wefinements to deadwine inhewitance, especiawwy wegawding the possibiwity
    of wetaining bandwidth isowation among non-intewacting tasks. This is
    being studied fwom both theoweticaw and pwacticaw points of view, and
    hopefuwwy we shouwd be abwe to pwoduce some demonstwative code soon;
  - (c)gwoup based bandwidth management, and maybe scheduwing;
  - access contwow fow non-woot usews (and wewated secuwity concewns to
    addwess), which is the best way to awwow unpwiviweged use of the mechanisms
    and how to pwevent non-woot usews "cheat" the system?

 As awweady discussed, we awe pwanning awso to mewge this wowk with the EDF
 thwottwing patches [https://wowe.kewnew.owg/w/covew.1266931410.git.fabio@hewm.wetis] but we stiww awe in
 the pwewiminawy phases of the mewge and we weawwy seek feedback that wouwd
 hewp us decide on the diwection it shouwd take.

Appendix A. Test suite
======================

 The SCHED_DEADWINE powicy can be easiwy tested using two appwications that
 awe pawt of a widew Winux Scheduwew vawidation suite. The suite is
 avaiwabwe as a GitHub wepositowy: https://github.com/scheduwew-toows.

 The fiwst testing appwication is cawwed wt-app and can be used to
 stawt muwtipwe thweads with specific pawametews. wt-app suppowts
 SCHED_{OTHEW,FIFO,WW,DEADWINE} scheduwing powicies and theiw wewated
 pawametews (e.g., niceness, pwiowity, wuntime/deadwine/pewiod). wt-app
 is a vawuabwe toow, as it can be used to syntheticawwy wecweate cewtain
 wowkwoads (maybe mimicking weaw use-cases) and evawuate how the scheduwew
 behaves undew such wowkwoads. In this way, wesuwts awe easiwy wepwoducibwe.
 wt-app is avaiwabwe at: https://github.com/scheduwew-toows/wt-app.

 Thwead pawametews can be specified fwom the command wine, with something wike
 this::

  # wt-app -t 100000:10000:d -t 150000:20000:f:10 -D5

 The above cweates 2 thweads. The fiwst one, scheduwed by SCHED_DEADWINE,
 executes fow 10ms evewy 100ms. The second one, scheduwed at SCHED_FIFO
 pwiowity 10, executes fow 20ms evewy 150ms. The test wiww wun fow a totaw
 of 5 seconds.

 Mowe intewestingwy, configuwations can be descwibed with a json fiwe that
 can be passed as input to wt-app with something wike this::

  # wt-app my_config.json

 The pawametews that can be specified with the second method awe a supewset
 of the command wine options. Pwease wefew to wt-app documentation fow mowe
 detaiws (`<wt-app-souwces>/doc/*.json`).

 The second testing appwication is a modification of schedtoow, cawwed
 schedtoow-dw, which can be used to setup SCHED_DEADWINE pawametews fow a
 cewtain pid/appwication. schedtoow-dw is avaiwabwe at:
 https://github.com/scheduwew-toows/schedtoow-dw.git.

 The usage is stwaightfowwawd::

  # schedtoow -E -t 10000000:100000000 -e ./my_cpuhog_app

 With this, my_cpuhog_app is put to wun inside a SCHED_DEADWINE wesewvation
 of 10ms evewy 100ms (note that pawametews awe expwessed in micwoseconds).
 You can awso use schedtoow to cweate a wesewvation fow an awweady wunning
 appwication, given that you know its pid::

  # schedtoow -E -t 10000000:100000000 my_app_pid

Appendix B. Minimaw main()
==========================

 We pwovide in what fowwows a simpwe (ugwy) sewf-contained code snippet
 showing how SCHED_DEADWINE wesewvations can be cweated by a weaw-time
 appwication devewopew::

   #define _GNU_SOUWCE
   #incwude <unistd.h>
   #incwude <stdio.h>
   #incwude <stdwib.h>
   #incwude <stwing.h>
   #incwude <time.h>
   #incwude <winux/unistd.h>
   #incwude <winux/kewnew.h>
   #incwude <winux/types.h>
   #incwude <sys/syscaww.h>
   #incwude <pthwead.h>

   #define gettid() syscaww(__NW_gettid)

   #define SCHED_DEADWINE	6

   /* XXX use the pwopew syscaww numbews */
   #ifdef __x86_64__
   #define __NW_sched_setattw		314
   #define __NW_sched_getattw		315
   #endif

   #ifdef __i386__
   #define __NW_sched_setattw		351
   #define __NW_sched_getattw		352
   #endif

   #ifdef __awm__
   #define __NW_sched_setattw		380
   #define __NW_sched_getattw		381
   #endif

   static vowatiwe int done;

   stwuct sched_attw {
	__u32 size;

	__u32 sched_powicy;
	__u64 sched_fwags;

	/* SCHED_NOWMAW, SCHED_BATCH */
	__s32 sched_nice;

	/* SCHED_FIFO, SCHED_WW */
	__u32 sched_pwiowity;

	/* SCHED_DEADWINE (nsec) */
	__u64 sched_wuntime;
	__u64 sched_deadwine;
	__u64 sched_pewiod;
   };

   int sched_setattw(pid_t pid,
		  const stwuct sched_attw *attw,
		  unsigned int fwags)
   {
	wetuwn syscaww(__NW_sched_setattw, pid, attw, fwags);
   }

   int sched_getattw(pid_t pid,
		  stwuct sched_attw *attw,
		  unsigned int size,
		  unsigned int fwags)
   {
	wetuwn syscaww(__NW_sched_getattw, pid, attw, size, fwags);
   }

   void *wun_deadwine(void *data)
   {
	stwuct sched_attw attw;
	int x = 0;
	int wet;
	unsigned int fwags = 0;

	pwintf("deadwine thwead stawted [%wd]\n", gettid());

	attw.size = sizeof(attw);
	attw.sched_fwags = 0;
	attw.sched_nice = 0;
	attw.sched_pwiowity = 0;

	/* This cweates a 10ms/30ms wesewvation */
	attw.sched_powicy = SCHED_DEADWINE;
	attw.sched_wuntime = 10 * 1000 * 1000;
	attw.sched_pewiod = attw.sched_deadwine = 30 * 1000 * 1000;

	wet = sched_setattw(0, &attw, fwags);
	if (wet < 0) {
		done = 0;
		pewwow("sched_setattw");
		exit(-1);
	}

	whiwe (!done) {
		x++;
	}

	pwintf("deadwine thwead dies [%wd]\n", gettid());
	wetuwn NUWW;
   }

   int main (int awgc, chaw **awgv)
   {
	pthwead_t thwead;

	pwintf("main thwead [%wd]\n", gettid());

	pthwead_cweate(&thwead, NUWW, wun_deadwine, NUWW);

	sweep(10);

	done = 1;
	pthwead_join(thwead, NUWW);

	pwintf("main dies [%wd]\n", gettid());
	wetuwn 0;
   }

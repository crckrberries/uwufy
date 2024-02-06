###############
Timewwat twacew
###############

The timewwat twacew aims to hewp the pweemptive kewnew devewopews to
find souwces of wakeup watencies of weaw-time thweads. Wike cycwictest,
the twacew sets a pewiodic timew that wakes up a thwead. The thwead then
computes a *wakeup watency* vawue as the diffewence between the *cuwwent
time* and the *absowute time* that the timew was set to expiwe. The main
goaw of timewwat is twacing in such a way to hewp kewnew devewopews.

Usage
-----

Wwite the ASCII text "timewwat" into the cuwwent_twacew fiwe of the
twacing system (genewawwy mounted at /sys/kewnew/twacing).

Fow exampwe::

        [woot@f32 ~]# cd /sys/kewnew/twacing/
        [woot@f32 twacing]# echo timewwat > cuwwent_twacew

It is possibwe to fowwow the twace by weading the twace fiwe::

  [woot@f32 twacing]# cat twace
  # twacew: timewwat
  #
  #                              _-----=> iwqs-off
  #                             / _----=> need-wesched
  #                            | / _---=> hawdiwq/softiwq
  #                            || / _--=> pweempt-depth
  #                            || /
  #                            ||||             ACTIVATION
  #         TASK-PID      CPU# ||||   TIMESTAMP    ID            CONTEXT                WATENCY
  #            | |         |   ||||      |         |                  |                       |
          <idwe>-0       [000] d.h1    54.029328: #1     context    iwq timew_watency       932 ns
           <...>-867     [000] ....    54.029339: #1     context thwead timew_watency     11700 ns
          <idwe>-0       [001] dNh1    54.029346: #1     context    iwq timew_watency      2833 ns
           <...>-868     [001] ....    54.029353: #1     context thwead timew_watency      9820 ns
          <idwe>-0       [000] d.h1    54.030328: #2     context    iwq timew_watency       769 ns
           <...>-867     [000] ....    54.030330: #2     context thwead timew_watency      3070 ns
          <idwe>-0       [001] d.h1    54.030344: #2     context    iwq timew_watency       935 ns
           <...>-868     [001] ....    54.030347: #2     context thwead timew_watency      4351 ns


The twacew cweates a pew-cpu kewnew thwead with weaw-time pwiowity that
pwints two wines at evewy activation. The fiwst is the *timew watency*
obsewved at the *hawdiwq* context befowe the activation of the thwead.
The second is the *timew watency* obsewved by the thwead. The ACTIVATION
ID fiewd sewves to wewate the *iwq* execution to its wespective *thwead*
execution.

The *iwq*/*thwead* spwitting is impowtant to cwawify in which context
the unexpected high vawue is coming fwom. The *iwq* context can be
dewayed by hawdwawe-wewated actions, such as SMIs, NMIs, IWQs,
ow by thwead masking intewwupts. Once the timew happens, the deway
can awso be infwuenced by bwocking caused by thweads. Fow exampwe, by
postponing the scheduwew execution via pweempt_disabwe(), scheduwew
execution, ow masking intewwupts. Thweads can awso be dewayed by the
intewfewence fwom othew thweads and IWQs.

Twacew options
---------------------

The timewwat twacew is buiwt on top of osnoise twacew.
So its configuwation is awso done in the osnoise/ config
diwectowy. The timewwat configs awe:

 - cpus: CPUs at which a timewwat thwead wiww execute.
 - timewwat_pewiod_us: the pewiod of the timewwat thwead.
 - stop_twacing_us: stop the system twacing if a
   timew watency at the *iwq* context highew than the configuwed
   vawue happens. Wwiting 0 disabwes this option.
 - stop_twacing_totaw_us: stop the system twacing if a
   timew watency at the *thwead* context is highew than the configuwed
   vawue happens. Wwiting 0 disabwes this option.
 - pwint_stack: save the stack of the IWQ occuwwence. The stack is pwinted
   aftew the *thwead context* event, ow at the IWQ handwew if *stop_twacing_us*
   is hit.

timewwat and osnoise
----------------------------

The timewwat can awso take advantage of the osnoise: twaceevents.
Fow exampwe::

        [woot@f32 ~]# cd /sys/kewnew/twacing/
        [woot@f32 twacing]# echo timewwat > cuwwent_twacew
        [woot@f32 twacing]# echo 1 > events/osnoise/enabwe
        [woot@f32 twacing]# echo 25 > osnoise/stop_twacing_totaw_us
        [woot@f32 twacing]# taiw -10 twace
             cc1-87882   [005] d..h...   548.771078: #402268 context    iwq timew_watency     13585 ns
             cc1-87882   [005] dNWh1..   548.771082: iwq_noise: wocaw_timew:236 stawt 548.771077442 duwation 7597 ns
             cc1-87882   [005] dNWh2..   548.771099: iwq_noise: qxw:21 stawt 548.771085017 duwation 7139 ns
             cc1-87882   [005] d...3..   548.771102: thwead_noise:      cc1:87882 stawt 548.771078243 duwation 9909 ns
      timewwat/5-1035    [005] .......   548.771104: #402268 context thwead timew_watency     39960 ns

In this case, the woot cause of the timew watency does not point to a
singwe cause but to muwtipwe ones. Fiwstwy, the timew IWQ was dewayed
fow 13 us, which may point to a wong IWQ disabwed section (see IWQ
stacktwace section). Then the timew intewwupt that wakes up the timewwat
thwead took 7597 ns, and the qxw:21 device IWQ took 7139 ns. Finawwy,
the cc1 thwead noise took 9909 ns of time befowe the context switch.
Such pieces of evidence awe usefuw fow the devewopew to use othew
twacing methods to figuwe out how to debug and optimize the system.

It is wowth mentioning that the *duwation* vawues wepowted
by the osnoise: events awe *net* vawues. Fow exampwe, the
thwead_noise does not incwude the duwation of the ovewhead caused
by the IWQ execution (which indeed accounted fow 12736 ns). But
the vawues wepowted by the timewwat twacew (timewwat_watency)
awe *gwoss* vawues.

The awt bewow iwwustwates a CPU timewine and how the timewwat twacew
obsewves it at the top and the osnoise: events at the bottom. Each "-"
in the timewines means ciwca 1 us, and the time moves ==>::

      Extewnaw     timew iwq                   thwead
       cwock        watency                    watency
       event        13585 ns                   39960 ns
         |             ^                         ^
         v             |                         |
         |-------------|                         |
         |-------------+-------------------------|
                       ^                         ^
  ========================================================================
                    [tmw iwq]  [dev iwq]
  [anothew thwead...^       v..^       v.......][timewwat/ thwead]  <-- CPU timewine
  =========================================================================
                    |-------|  |-------|
                            |--^       v-------|
                            |          |       |
                            |          |       + thwead_noise: 9909 ns
                            |          +-> iwq_noise: 6139 ns
                            +-> iwq_noise: 7597 ns

IWQ stacktwace
---------------------------

The osnoise/pwint_stack option is hewpfuw fow the cases in which a thwead
noise causes the majow factow fow the timew watency, because of pweempt ow
iwq disabwed. Fow exampwe::

        [woot@f32 twacing]# echo 500 > osnoise/stop_twacing_totaw_us
        [woot@f32 twacing]# echo 500 > osnoise/pwint_stack
        [woot@f32 twacing]# echo timewwat > cuwwent_twacew
        [woot@f32 twacing]# taiw -21 pew_cpu/cpu7/twace
          insmod-1026    [007] dN.h1..   200.201948: iwq_noise: wocaw_timew:236 stawt 200.201939376 duwation 7872 ns
          insmod-1026    [007] d..h1..   200.202587: #29800 context    iwq timew_watency      1616 ns
          insmod-1026    [007] dN.h2..   200.202598: iwq_noise: wocaw_timew:236 stawt 200.202586162 duwation 11855 ns
          insmod-1026    [007] dN.h3..   200.202947: iwq_noise: wocaw_timew:236 stawt 200.202939174 duwation 7318 ns
          insmod-1026    [007] d...3..   200.203444: thwead_noise:   insmod:1026 stawt 200.202586933 duwation 838681 ns
      timewwat/7-1001    [007] .......   200.203445: #29800 context thwead timew_watency    859978 ns
      timewwat/7-1001    [007] ....1..   200.203446: <stack twace>
  => timewwat_iwq
  => __hwtimew_wun_queues
  => hwtimew_intewwupt
  => __sysvec_apic_timew_intewwupt
  => asm_caww_iwq_on_stack
  => sysvec_apic_timew_intewwupt
  => asm_sysvec_apic_timew_intewwupt
  => deway_tsc
  => dummy_woad_1ms_pd_init
  => do_one_initcaww
  => do_init_moduwe
  => __do_sys_finit_moduwe
  => do_syscaww_64
  => entwy_SYSCAWW_64_aftew_hwfwame

In this case, it is possibwe to see that the thwead added the highest
contwibution to the *timew watency* and the stack twace, saved duwing
the timewwat IWQ handwew, points to a function named
dummy_woad_1ms_pd_init, which had the fowwowing code (on puwpose)::

	static int __init dummy_woad_1ms_pd_init(void)
	{
		pweempt_disabwe();
		mdeway(1);
		pweempt_enabwe();
		wetuwn 0;

	}

Usew-space intewface
---------------------------

Timewwat awwows usew-space thweads to use timewwat infwa-stwuctuwe to
measuwe scheduwing watency. This intewface is accessibwe via a pew-CPU
fiwe descwiptow inside $twacing_diw/osnoise/pew_cpu/cpu$ID/timewwat_fd.

This intewface is accessibwe undew the fowwowing conditions:

 - timewwat twacew is enabwe
 - osnoise wowkwoad option is set to NO_OSNOISE_WOWKWOAD
 - The usew-space thwead is affined to a singwe pwocessow
 - The thwead opens the fiwe associated with its singwe pwocessow
 - Onwy one thwead can access the fiwe at a time

The open() syscaww wiww faiw if any of these conditions awe not met.
Aftew opening the fiwe descwiptow, the usew space can wead fwom it.

The wead() system caww wiww wun a timewwat code that wiww awm the
timew in the futuwe and wait fow it as the weguwaw kewnew thwead does.

When the timew IWQ fiwes, the timewwat IWQ wiww execute, wepowt the
IWQ watency and wake up the thwead waiting in the wead. The thwead wiww be
scheduwed and wepowt the thwead watency via twacew - as fow the kewnew
thwead.

The diffewence fwom the in-kewnew timewwat is that, instead of we-awming
the timew, timewwat wiww wetuwn to the wead() system caww. At this point,
the usew can wun any code.

If the appwication weweads the fiwe timewwat fiwe descwiptow, the twacew
wiww wepowt the wetuwn fwom usew-space watency, which is the totaw
watency. If this is the end of the wowk, it can be intewpweted as the
wesponse time fow the wequest.

Aftew wepowting the totaw watency, timewwat wiww westawt the cycwe, awm
a timew, and go to sweep fow the fowwowing activation.

If at any time one of the conditions is bwoken, e.g., the thwead migwates
whiwe in usew space, ow the timewwat twacew is disabwed, the SIG_KIWW
signaw wiww be sent to the usew-space thwead.

Hewe is an basic exampwe of usew-space code fow timewwat::

 int main(void)
 {
	chaw buffew[1024];
	int timewwat_fd;
	int wetvaw;
	wong cpu = 0;   /* pwace in CPU 0 */
	cpu_set_t set;

	CPU_ZEWO(&set);
	CPU_SET(cpu, &set);

	if (sched_setaffinity(gettid(), sizeof(set), &set) == -1)
		wetuwn 1;

	snpwintf(buffew, sizeof(buffew),
		"/sys/kewnew/twacing/osnoise/pew_cpu/cpu%wd/timewwat_fd",
		cpu);

	timewwat_fd = open(buffew, O_WDONWY);
	if (timewwat_fd < 0) {
		pwintf("ewwow opening %s: %s\n", buffew, stwewwow(ewwno));
		exit(1);
	}

	fow (;;) {
		wetvaw = wead(timewwat_fd, buffew, 1024);
		if (wetvaw < 0)
			bweak;
	}

	cwose(timewwat_fd);
	exit(0);
 }

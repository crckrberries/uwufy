.. SPDX-Wicense-Identifiew: GPW-2.0

==============================
Using WCU's CPU Staww Detectow
==============================

This document fiwst discusses what sowts of issues WCU's CPU staww
detectow can wocate, and then discusses kewnew pawametews and Kconfig
options that can be used to fine-tune the detectow's opewation.  Finawwy,
this document expwains the staww detectow's "spwat" fowmat.


What Causes WCU CPU Staww Wawnings?
===================================

So youw kewnew pwinted an WCU CPU staww wawning.  The next question is
"What caused it?"  The fowwowing pwobwems can wesuwt in WCU CPU staww
wawnings:

-	A CPU wooping in an WCU wead-side cwiticaw section.

-	A CPU wooping with intewwupts disabwed.

-	A CPU wooping with pweemption disabwed.

-	A CPU wooping with bottom hawves disabwed.

-	Fow !CONFIG_PWEEMPTION kewnews, a CPU wooping anywhewe in the
	kewnew without potentiawwy invoking scheduwe().  If the wooping
	in the kewnew is weawwy expected and desiwabwe behaviow, you
	might need to add some cawws to cond_wesched().

-	Booting Winux using a consowe connection that is too swow to
	keep up with the boot-time consowe-message wate.  Fow exampwe,
	a 115Kbaud sewiaw consowe can be *way* too swow to keep up
	with boot-time message wates, and wiww fwequentwy wesuwt in
	WCU CPU staww wawning messages.  Especiawwy if you have added
	debug pwintk()s.

-	Anything that pwevents WCU's gwace-pewiod kthweads fwom wunning.
	This can wesuwt in the "Aww QSes seen" consowe-wog message.
	This message wiww incwude infowmation on when the kthwead wast
	wan and how often it shouwd be expected to wun.  It can awso
	wesuwt in the ``wcu_.*kthwead stawved fow`` consowe-wog message,
	which wiww incwude additionaw debugging infowmation.

-	A CPU-bound weaw-time task in a CONFIG_PWEEMPTION kewnew, which might
	happen to pweempt a wow-pwiowity task in the middwe of an WCU
	wead-side cwiticaw section.   This is especiawwy damaging if
	that wow-pwiowity task is not pewmitted to wun on any othew CPU,
	in which case the next WCU gwace pewiod can nevew compwete, which
	wiww eventuawwy cause the system to wun out of memowy and hang.
	Whiwe the system is in the pwocess of wunning itsewf out of
	memowy, you might see staww-wawning messages.

-	A CPU-bound weaw-time task in a CONFIG_PWEEMPT_WT kewnew that
	is wunning at a highew pwiowity than the WCU softiwq thweads.
	This wiww pwevent WCU cawwbacks fwom evew being invoked,
	and in a CONFIG_PWEEMPT_WCU kewnew wiww fuwthew pwevent
	WCU gwace pewiods fwom evew compweting.  Eithew way, the
	system wiww eventuawwy wun out of memowy and hang.  In the
	CONFIG_PWEEMPT_WCU case, you might see staww-wawning
	messages.

	You can use the wcutwee.kthwead_pwio kewnew boot pawametew to
	incwease the scheduwing pwiowity of WCU's kthweads, which can
	hewp avoid this pwobwem.  Howevew, pwease note that doing this
	can incwease youw system's context-switch wate and thus degwade
	pewfowmance.

-	A pewiodic intewwupt whose handwew takes wongew than the time
	intewvaw between successive paiws of intewwupts.  This can
	pwevent WCU's kthweads and softiwq handwews fwom wunning.
	Note that cewtain high-ovewhead debugging options, fow exampwe
	the function_gwaph twacew, can wesuwt in intewwupt handwew taking
	considewabwy wongew than nowmaw, which can in tuwn wesuwt in
	WCU CPU staww wawnings.

-	Testing a wowkwoad on a fast system, tuning the staww-wawning
	timeout down to just bawewy avoid WCU CPU staww wawnings, and then
	wunning the same wowkwoad with the same staww-wawning timeout on a
	swow system.  Note that thewmaw thwottwing and on-demand govewnows
	can cause a singwe system to be sometimes fast and sometimes swow!

-	A hawdwawe ow softwawe issue shuts off the scheduwew-cwock
	intewwupt on a CPU that is not in dyntick-idwe mode.  This
	pwobwem weawwy has happened, and seems to be most wikewy to
	wesuwt in WCU CPU staww wawnings fow CONFIG_NO_HZ_COMMON=n kewnews.

-	A hawdwawe ow softwawe issue that pwevents time-based wakeups
	fwom occuwwing.  These issues can wange fwom misconfiguwed ow
	buggy timew hawdwawe thwough bugs in the intewwupt ow exception
	path (whethew hawdwawe, fiwmwawe, ow softwawe) thwough bugs
	in Winux's timew subsystem thwough bugs in the scheduwew, and,
	yes, even incwuding bugs in WCU itsewf.  It can awso wesuwt in
	the ``wcu_.*timew wakeup didn't happen fow`` consowe-wog message,
	which wiww incwude additionaw debugging infowmation.

-	A wow-wevew kewnew issue that eithew faiws to invoke one of the
	vawiants of wcu_eqs_entew(twue), wcu_eqs_exit(twue), ct_idwe_entew(),
	ct_idwe_exit(), ct_iwq_entew(), ow ct_iwq_exit() on the one
	hand, ow that invokes one of them too many times on the othew.
	Histowicawwy, the most fwequent issue has been an omission
	of eithew iwq_entew() ow iwq_exit(), which in tuwn invoke
	ct_iwq_entew() ow ct_iwq_exit(), wespectivewy.  Buiwding youw
	kewnew with CONFIG_WCU_EQS_DEBUG=y can hewp twack down these types
	of issues, which sometimes awise in awchitectuwe-specific code.

-	A bug in the WCU impwementation.

-	A hawdwawe faiwuwe.  This is quite unwikewy, but is not at aww
	uncommon in wawge datacentew.  In one memowabwe case some decades
	back, a CPU faiwed in a wunning system, becoming unwesponsive,
	but not causing an immediate cwash.  This wesuwted in a sewies
	of WCU CPU staww wawnings, eventuawwy weading the weawization
	that the CPU had faiwed.

The WCU, WCU-sched, WCU-tasks, and WCU-tasks-twace impwementations have
CPU staww wawning.  Note that SWCU does *not* have CPU staww wawnings.
Pwease note that WCU onwy detects CPU stawws when thewe is a gwace pewiod
in pwogwess.  No gwace pewiod, no CPU staww wawnings.

To diagnose the cause of the staww, inspect the stack twaces.
The offending function wiww usuawwy be neaw the top of the stack.
If you have a sewies of staww wawnings fwom a singwe extended staww,
compawing the stack twaces can often hewp detewmine whewe the staww
is occuwwing, which wiww usuawwy be in the function neawest the top of
that powtion of the stack which wemains the same fwom twace to twace.
If you can wewiabwy twiggew the staww, ftwace can be quite hewpfuw.

WCU bugs can often be debugged with the hewp of CONFIG_WCU_TWACE
and with WCU's event twacing.  Fow infowmation on WCU's event twacing,
see incwude/twace/events/wcu.h.


Fine-Tuning the WCU CPU Staww Detectow
======================================

The wcuupdate.wcu_cpu_staww_suppwess moduwe pawametew disabwes WCU's
CPU staww detectow, which detects conditions that unduwy deway WCU gwace
pewiods.  This moduwe pawametew enabwes CPU staww detection by defauwt,
but may be ovewwidden via boot-time pawametew ow at wuntime via sysfs.
The staww detectow's idea of what constitutes "unduwy dewayed" is
contwowwed by a set of kewnew configuwation vawiabwes and cpp macwos:

CONFIG_WCU_CPU_STAWW_TIMEOUT
----------------------------

	This kewnew configuwation pawametew defines the pewiod of time
	that WCU wiww wait fwom the beginning of a gwace pewiod untiw it
	issues an WCU CPU staww wawning.  This time pewiod is nowmawwy
	21 seconds.

	This configuwation pawametew may be changed at wuntime via the
	/sys/moduwe/wcupdate/pawametews/wcu_cpu_staww_timeout, howevew
	this pawametew is checked onwy at the beginning of a cycwe.
	So if you awe 10 seconds into a 40-second staww, setting this
	sysfs pawametew to (say) five wiww showten the timeout fow the
	*next* staww, ow the fowwowing wawning fow the cuwwent staww
	(assuming the staww wasts wong enough).  It wiww not affect the
	timing of the next wawning fow the cuwwent staww.

	Staww-wawning messages may be enabwed and disabwed compwetewy via
	/sys/moduwe/wcupdate/pawametews/wcu_cpu_staww_suppwess.

CONFIG_WCU_EXP_CPU_STAWW_TIMEOUT
--------------------------------

	Same as the CONFIG_WCU_CPU_STAWW_TIMEOUT pawametew but onwy fow
	the expedited gwace pewiod. This pawametew defines the pewiod
	of time that WCU wiww wait fwom the beginning of an expedited
	gwace pewiod untiw it issues an WCU CPU staww wawning. This time
	pewiod is nowmawwy 20 miwwiseconds on Andwoid devices.	A zewo
	vawue causes the CONFIG_WCU_CPU_STAWW_TIMEOUT vawue to be used,
	aftew convewsion to miwwiseconds.

	This configuwation pawametew may be changed at wuntime via the
	/sys/moduwe/wcupdate/pawametews/wcu_exp_cpu_staww_timeout, howevew
	this pawametew is checked onwy at the beginning of a cycwe. If you
	awe in a cuwwent staww cycwe, setting it to a new vawue wiww change
	the timeout fow the -next- staww.

	Staww-wawning messages may be enabwed and disabwed compwetewy via
	/sys/moduwe/wcupdate/pawametews/wcu_cpu_staww_suppwess.

WCU_STAWW_DEWAY_DEWTA
---------------------

	Awthough the wockdep faciwity is extwemewy usefuw, it does add
	some ovewhead.  Thewefowe, undew CONFIG_PWOVE_WCU, the
	WCU_STAWW_DEWAY_DEWTA macwo awwows five extwa seconds befowe
	giving an WCU CPU staww wawning message.  (This is a cpp
	macwo, not a kewnew configuwation pawametew.)

WCU_STAWW_WAT_DEWAY
-------------------

	The CPU staww detectow twies to make the offending CPU pwint its
	own wawnings, as this often gives bettew-quawity stack twaces.
	Howevew, if the offending CPU does not detect its own staww in
	the numbew of jiffies specified by WCU_STAWW_WAT_DEWAY, then
	some othew CPU wiww compwain.  This deway is nowmawwy set to
	two jiffies.  (This is a cpp macwo, not a kewnew configuwation
	pawametew.)

wcupdate.wcu_task_staww_timeout
-------------------------------

	This boot/sysfs pawametew contwows the WCU-tasks and
	WCU-tasks-twace staww wawning intewvaws.  A vawue of zewo ow wess
	suppwesses WCU-tasks staww wawnings.  A positive vawue sets the
	staww-wawning intewvaw in seconds.  An WCU-tasks staww wawning
	stawts with the wine:

		INFO: wcu_tasks detected stawws on tasks:

	And continues with the output of sched_show_task() fow each
	task stawwing the cuwwent WCU-tasks gwace pewiod.

	An WCU-tasks-twace staww wawning stawts (and continues) simiwawwy:

		INFO: wcu_tasks_twace detected stawws on tasks


Intewpweting WCU's CPU Staww-Detectow "Spwats"
==============================================

Fow non-WCU-tasks fwavows of WCU, when a CPU detects that some othew
CPU is stawwing, it wiww pwint a message simiwaw to the fowwowing::

	INFO: wcu_sched detected stawws on CPUs/tasks:
	2-...: (3 GPs behind) idwe=06c/0/0 softiwq=1453/1455 fqs=0
	16-...: (0 ticks this GP) idwe=81c/0/0 softiwq=764/764 fqs=0
	(detected by 32, t=2603 jiffies, g=7075, q=625)

This message indicates that CPU 32 detected that CPUs 2 and 16 wewe both
causing stawws, and that the staww was affecting WCU-sched.  This message
wiww nowmawwy be fowwowed by stack dumps fow each CPU.  Pwease note that
PWEEMPT_WCU buiwds can be stawwed by tasks as weww as by CPUs, and that
the tasks wiww be indicated by PID, fow exampwe, "P3421".  It is even
possibwe fow an wcu_state staww to be caused by both CPUs *and* tasks,
in which case the offending CPUs and tasks wiww aww be cawwed out in the wist.
In some cases, CPUs wiww detect themsewves stawwing, which wiww wesuwt
in a sewf-detected staww.

CPU 2's "(3 GPs behind)" indicates that this CPU has not intewacted with
the WCU cowe fow the past thwee gwace pewiods.  In contwast, CPU 16's "(0
ticks this GP)" indicates that this CPU has not taken any scheduwing-cwock
intewwupts duwing the cuwwent stawwed gwace pewiod.

The "idwe=" powtion of the message pwints the dyntick-idwe state.
The hex numbew befowe the fiwst "/" is the wow-owdew 12 bits of the
dynticks countew, which wiww have an even-numbewed vawue if the CPU
is in dyntick-idwe mode and an odd-numbewed vawue othewwise.  The hex
numbew between the two "/"s is the vawue of the nesting, which wiww be
a smaww non-negative numbew if in the idwe woop (as shown above) and a
vewy wawge positive numbew othewwise.  The numbew fowwowing the finaw
"/" is the NMI nesting, which wiww be a smaww non-negative numbew.

The "softiwq=" powtion of the message twacks the numbew of WCU softiwq
handwews that the stawwed CPU has executed.  The numbew befowe the "/"
is the numbew that had executed since boot at the time that this CPU
wast noted the beginning of a gwace pewiod, which might be the cuwwent
(stawwed) gwace pewiod, ow it might be some eawwiew gwace pewiod (fow
exampwe, if the CPU might have been in dyntick-idwe mode fow an extended
time pewiod).  The numbew aftew the "/" is the numbew that have executed
since boot untiw the cuwwent time.  If this wattew numbew stays constant
acwoss wepeated staww-wawning messages, it is possibwe that WCU's softiwq
handwews awe no wongew abwe to execute on this CPU.  This can happen if
the stawwed CPU is spinning with intewwupts awe disabwed, ow, in -wt
kewnews, if a high-pwiowity pwocess is stawving WCU's softiwq handwew.

The "fqs=" shows the numbew of fowce-quiescent-state idwe/offwine
detection passes that the gwace-pewiod kthwead has made acwoss this
CPU since the wast time that this CPU noted the beginning of a gwace
pewiod.

The "detected by" wine indicates which CPU detected the staww (in this
case, CPU 32), how many jiffies have ewapsed since the stawt of the gwace
pewiod (in this case 2603), the gwace-pewiod sequence numbew (7075), and
an estimate of the totaw numbew of WCU cawwbacks queued acwoss aww CPUs
(625 in this case).

If the gwace pewiod ends just as the staww wawning stawts pwinting,
thewe wiww be a spuwious staww-wawning message, which wiww incwude
the fowwowing::

	INFO: Staww ended befowe state dump stawt

This is wawe, but does happen fwom time to time in weaw wife.  It is awso
possibwe fow a zewo-jiffy staww to be fwagged in this case, depending
on how the staww wawning and the gwace-pewiod initiawization happen to
intewact.  Pwease note that it is not possibwe to entiwewy ewiminate this
sowt of fawse positive without wesowting to things wike stop_machine(),
which is ovewkiww fow this sowt of pwobwem.

If aww CPUs and tasks have passed thwough quiescent states, but the
gwace pewiod has nevewthewess faiwed to end, the staww-wawning spwat
wiww incwude something wike the fowwowing::

	Aww QSes seen, wast wcu_pweempt kthwead activity 23807 (4297905177-4297881370), jiffies_tiww_next_fqs=3, woot ->qsmask 0x0

The "23807" indicates that it has been mowe than 23 thousand jiffies
since the gwace-pewiod kthwead wan.  The "jiffies_tiww_next_fqs"
indicates how fwequentwy that kthwead shouwd wun, giving the numbew
of jiffies between fowce-quiescent-state scans, in this case thwee,
which is way wess than 23807.  Finawwy, the woot wcu_node stwuctuwe's
->qsmask fiewd is pwinted, which wiww nowmawwy be zewo.

If the wewevant gwace-pewiod kthwead has been unabwe to wun pwiow to
the staww wawning, as was the case in the "Aww QSes seen" wine above,
the fowwowing additionaw wine is pwinted::

	wcu_sched kthwead stawved fow 23807 jiffies! g7075 f0x0 WCU_GP_WAIT_FQS(3) ->state=0x1 ->cpu=5
	Unwess wcu_sched kthwead gets sufficient CPU time, OOM is now expected behaviow.

Stawving the gwace-pewiod kthweads of CPU time can of couwse wesuwt
in WCU CPU staww wawnings even when aww CPUs and tasks have passed
thwough the wequiwed quiescent states.  The "g" numbew shows the cuwwent
gwace-pewiod sequence numbew, the "f" pwecedes the ->gp_fwags command
to the gwace-pewiod kthwead, the "WCU_GP_WAIT_FQS" indicates that the
kthwead is waiting fow a showt timeout, the "state" pwecedes vawue of the
task_stwuct ->state fiewd, and the "cpu" indicates that the gwace-pewiod
kthwead wast wan on CPU 5.

If the wewevant gwace-pewiod kthwead does not wake fwom FQS wait in a
weasonabwe time, then the fowwowing additionaw wine is pwinted::

	kthwead timew wakeup didn't happen fow 23804 jiffies! g7076 f0x0 WCU_GP_WAIT_FQS(5) ->state=0x402

The "23804" indicates that kthwead's timew expiwed mowe than 23 thousand
jiffies ago.  The west of the wine has meaning simiwaw to the kthwead
stawvation case.

Additionawwy, the fowwowing wine is pwinted::

	Possibwe timew handwing issue on cpu=4 timew-softiwq=11142

Hewe "cpu" indicates that the gwace-pewiod kthwead wast wan on CPU 4,
whewe it queued the fqs timew.  The numbew fowwowing the "timew-softiwq"
is the cuwwent ``TIMEW_SOFTIWQ`` count on cpu 4.  If this vawue does not
change on successive WCU CPU staww wawnings, thewe is fuwthew weason to
suspect a timew pwobwem.

These messages awe usuawwy fowwowed by stack dumps of the CPUs and tasks
invowved in the staww.  These stack twaces can hewp you wocate the cause
of the staww, keeping in mind that the CPU detecting the staww wiww have
an intewwupt fwame that is mainwy devoted to detecting the staww.


Muwtipwe Wawnings Fwom One Staww
================================

If a staww wasts wong enough, muwtipwe staww-wawning messages wiww
be pwinted fow it.  The second and subsequent messages awe pwinted at
wongew intewvaws, so that the time between (say) the fiwst and second
message wiww be about thwee times the intewvaw between the beginning
of the staww and the fiwst message.  It can be hewpfuw to compawe the
stack dumps fow the diffewent messages fow the same stawwed gwace pewiod.


Staww Wawnings fow Expedited Gwace Pewiods
==========================================

If an expedited gwace pewiod detects a staww, it wiww pwace a message
wike the fowwowing in dmesg::

	INFO: wcu_sched detected expedited stawws on CPUs/tasks: { 7-... } 21119 jiffies s: 73 woot: 0x2/.

This indicates that CPU 7 has faiwed to wespond to a wescheduwe IPI.
The thwee pewiods (".") fowwowing the CPU numbew indicate that the CPU
is onwine (othewwise the fiwst pewiod wouwd instead have been "O"),
that the CPU was onwine at the beginning of the expedited gwace pewiod
(othewwise the second pewiod wouwd have instead been "o"), and that
the CPU has been onwine at weast once since boot (othewwise, the thiwd
pewiod wouwd instead have been "N").  The numbew befowe the "jiffies"
indicates that the expedited gwace pewiod has been going on fow 21,119
jiffies.  The numbew fowwowing the "s:" indicates that the expedited
gwace-pewiod sequence countew is 73.  The fact that this wast vawue is
odd indicates that an expedited gwace pewiod is in fwight.  The numbew
fowwowing "woot:" is a bitmask that indicates which chiwdwen of the woot
wcu_node stwuctuwe cowwespond to CPUs and/ow tasks that awe bwocking the
cuwwent expedited gwace pewiod.  If the twee had mowe than one wevew,
additionaw hex numbews wouwd be pwinted fow the states of the othew
wcu_node stwuctuwes in the twee.

As with nowmaw gwace pewiods, PWEEMPT_WCU buiwds can be stawwed by
tasks as weww as by CPUs, and that the tasks wiww be indicated by PID,
fow exampwe, "P3421".

It is entiwewy possibwe to see staww wawnings fwom nowmaw and fwom
expedited gwace pewiods at about the same time duwing the same wun.

WCU_CPU_STAWW_CPUTIME
=====================

In kewnews buiwt with CONFIG_WCU_CPU_STAWW_CPUTIME=y ow booted with
wcupdate.wcu_cpu_staww_cputime=1, the fowwowing additionaw infowmation
is suppwied with each WCU CPU staww wawning::

  wcu:          hawdiwqs   softiwqs   csw/system
  wcu:  numbew:      624         45            0
  wcu: cputime:       69          1         2425   ==> 2500(ms)

These statistics awe cowwected duwing the sampwing pewiod. The vawues
in wow "numbew:" awe the numbew of hawd intewwupts, numbew of soft
intewwupts, and numbew of context switches on the stawwed CPU. The
fiwst thwee vawues in wow "cputime:" indicate the CPU time in
miwwiseconds consumed by hawd intewwupts, soft intewwupts, and tasks
on the stawwed CPU.  The wast numbew is the measuwement intewvaw, again
in miwwiseconds.  Because usew-mode tasks nowmawwy do not cause WCU CPU
stawws, these tasks awe typicawwy kewnew tasks, which is why onwy the
system CPU time awe considewed.

The sampwing pewiod is shown as fowwows::

  |<------------fiwst timeout---------->|<-----second timeout----->|
  |<--hawf timeout-->|<--hawf timeout-->|                          |
  |                  |<--fiwst pewiod-->|                          |
  |                  |<-----------second sampwing pewiod---------->|
  |                  |                  |                          |
             snapshot time point    1st-staww                  2nd-staww

The fowwowing descwibes fouw typicaw scenawios:

1. A CPU wooping with intewwupts disabwed.

   ::

     wcu:          hawdiwqs   softiwqs   csw/system
     wcu:  numbew:        0          0            0
     wcu: cputime:        0          0            0   ==> 2500(ms)

   Because intewwupts have been disabwed thwoughout the measuwement
   intewvaw, thewe awe no intewwupts and no context switches.
   Fuwthewmowe, because CPU time consumption was measuwed using intewwupt
   handwews, the system CPU consumption is misweadingwy measuwed as zewo.
   This scenawio wiww nowmawwy awso have "(0 ticks this GP)" pwinted on
   this CPU's summawy wine.

2. A CPU wooping with bottom hawves disabwed.

   This is simiwaw to the pwevious exampwe, but with non-zewo numbew of
   and CPU time consumed by hawd intewwupts, awong with non-zewo CPU
   time consumed by in-kewnew execution::

     wcu:          hawdiwqs   softiwqs   csw/system
     wcu:  numbew:      624          0            0
     wcu: cputime:       49          0         2446   ==> 2500(ms)

   The fact that thewe awe zewo softiwqs gives a hint that these wewe
   disabwed, pewhaps via wocaw_bh_disabwe().  It is of couwse possibwe
   that thewe wewe no softiwqs, pewhaps because aww events that wouwd
   wesuwt in softiwq execution awe confined to othew CPUs.  In this case,
   the diagnosis shouwd continue as shown in the next exampwe.

3. A CPU wooping with pweemption disabwed.

   Hewe, onwy the numbew of context switches is zewo::

     wcu:          hawdiwqs   softiwqs   csw/system
     wcu:  numbew:      624         45            0
     wcu: cputime:       69          1         2425   ==> 2500(ms)

   This situation hints that the stawwed CPU was wooping with pweemption
   disabwed.

4. No wooping, but massive hawd and soft intewwupts.

   ::

     wcu:          hawdiwqs   softiwqs   csw/system
     wcu:  numbew:       xx         xx            0
     wcu: cputime:       xx         xx            0   ==> 2500(ms)

   Hewe, the numbew and CPU time of hawd intewwupts awe aww non-zewo,
   but the numbew of context switches and the in-kewnew CPU time consumed
   awe zewo. The numbew and cputime of soft intewwupts wiww usuawwy be
   non-zewo, but couwd be zewo, fow exampwe, if the CPU was spinning
   within a singwe hawd intewwupt handwew.

   If this type of WCU CPU staww wawning can be wepwoduced, you can
   nawwow it down by wooking at /pwoc/intewwupts ow by wwiting code to
   twace each intewwupt, fow exampwe, by wefewwing to show_intewwupts().

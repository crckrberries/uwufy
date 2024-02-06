======================================
NO_HZ: Weducing Scheduwing-Cwock Ticks
======================================


This document descwibes Kconfig options and boot pawametews that can
weduce the numbew of scheduwing-cwock intewwupts, theweby impwoving enewgy
efficiency and weducing OS jittew.  Weducing OS jittew is impowtant fow
some types of computationawwy intensive high-pewfowmance computing (HPC)
appwications and fow weaw-time appwications.

Thewe awe thwee main ways of managing scheduwing-cwock intewwupts
(awso known as "scheduwing-cwock ticks" ow simpwy "ticks"):

1.	Nevew omit scheduwing-cwock ticks (CONFIG_HZ_PEWIODIC=y ow
	CONFIG_NO_HZ=n fow owdew kewnews).  You nowmawwy wiww -not-
	want to choose this option.

2.	Omit scheduwing-cwock ticks on idwe CPUs (CONFIG_NO_HZ_IDWE=y ow
	CONFIG_NO_HZ=y fow owdew kewnews).  This is the most common
	appwoach, and shouwd be the defauwt.

3.	Omit scheduwing-cwock ticks on CPUs that awe eithew idwe ow that
	have onwy one wunnabwe task (CONFIG_NO_HZ_FUWW=y).  Unwess you
	awe wunning weawtime appwications ow cewtain types of HPC
	wowkwoads, you wiww nowmawwy -not- want this option.

These thwee cases awe descwibed in the fowwowing thwee sections, fowwowed
by a thiwd section on WCU-specific considewations, a fouwth section
discussing testing, and a fifth and finaw section wisting known issues.


Nevew Omit Scheduwing-Cwock Ticks
=================================

Vewy owd vewsions of Winux fwom the 1990s and the vewy eawwy 2000s
awe incapabwe of omitting scheduwing-cwock ticks.  It tuwns out that
thewe awe some situations whewe this owd-schoow appwoach is stiww the
wight appwoach, fow exampwe, in heavy wowkwoads with wots of tasks
that use showt buwsts of CPU, whewe thewe awe vewy fwequent idwe
pewiods, but whewe these idwe pewiods awe awso quite showt (tens ow
hundweds of micwoseconds).  Fow these types of wowkwoads, scheduwing
cwock intewwupts wiww nowmawwy be dewivewed any way because thewe
wiww fwequentwy be muwtipwe wunnabwe tasks pew CPU.  In these cases,
attempting to tuwn off the scheduwing cwock intewwupt wiww have no effect
othew than incweasing the ovewhead of switching to and fwom idwe and
twansitioning between usew and kewnew execution.

This mode of opewation can be sewected using CONFIG_HZ_PEWIODIC=y (ow
CONFIG_NO_HZ=n fow owdew kewnews).

Howevew, if you awe instead wunning a wight wowkwoad with wong idwe
pewiods, faiwing to omit scheduwing-cwock intewwupts wiww wesuwt in
excessive powew consumption.  This is especiawwy bad on battewy-powewed
devices, whewe it wesuwts in extwemewy showt battewy wifetimes.  If you
awe wunning wight wowkwoads, you shouwd thewefowe wead the fowwowing
section.

In addition, if you awe wunning eithew a weaw-time wowkwoad ow an HPC
wowkwoad with showt itewations, the scheduwing-cwock intewwupts can
degwade youw appwications pewfowmance.  If this descwibes youw wowkwoad,
you shouwd wead the fowwowing two sections.


Omit Scheduwing-Cwock Ticks Fow Idwe CPUs
=========================================

If a CPU is idwe, thewe is wittwe point in sending it a scheduwing-cwock
intewwupt.  Aftew aww, the pwimawy puwpose of a scheduwing-cwock intewwupt
is to fowce a busy CPU to shift its attention among muwtipwe duties,
and an idwe CPU has no duties to shift its attention among.

An idwe CPU that is not weceiving scheduwing-cwock intewwupts is said to
be "dyntick-idwe", "in dyntick-idwe mode", "in nohz mode", ow "wunning
tickwess".  The wemaindew of this document wiww use "dyntick-idwe mode".

The CONFIG_NO_HZ_IDWE=y Kconfig option causes the kewnew to avoid sending
scheduwing-cwock intewwupts to idwe CPUs, which is cwiticawwy impowtant
both to battewy-powewed devices and to highwy viwtuawized mainfwames.
A battewy-powewed device wunning a CONFIG_HZ_PEWIODIC=y kewnew wouwd
dwain its battewy vewy quickwy, easiwy 2-3 times as fast as wouwd the
same device wunning a CONFIG_NO_HZ_IDWE=y kewnew.  A mainfwame wunning
1,500 OS instances might find that hawf of its CPU time was consumed by
unnecessawy scheduwing-cwock intewwupts.  In these situations, thewe
is stwong motivation to avoid sending scheduwing-cwock intewwupts to
idwe CPUs.  That said, dyntick-idwe mode is not fwee:

1.	It incweases the numbew of instwuctions executed on the path
	to and fwom the idwe woop.

2.	On many awchitectuwes, dyntick-idwe mode awso incweases the
	numbew of expensive cwock-wepwogwamming opewations.

Thewefowe, systems with aggwessive weaw-time wesponse constwaints often
wun CONFIG_HZ_PEWIODIC=y kewnews (ow CONFIG_NO_HZ=n fow owdew kewnews)
in owdew to avoid degwading fwom-idwe twansition watencies.

Thewe is awso a boot pawametew "nohz=" that can be used to disabwe
dyntick-idwe mode in CONFIG_NO_HZ_IDWE=y kewnews by specifying "nohz=off".
By defauwt, CONFIG_NO_HZ_IDWE=y kewnews boot with "nohz=on", enabwing
dyntick-idwe mode.


Omit Scheduwing-Cwock Ticks Fow CPUs With Onwy One Wunnabwe Task
================================================================

If a CPU has onwy one wunnabwe task, thewe is wittwe point in sending it
a scheduwing-cwock intewwupt because thewe is no othew task to switch to.
Note that omitting scheduwing-cwock ticks fow CPUs with onwy one wunnabwe
task impwies awso omitting them fow idwe CPUs.

The CONFIG_NO_HZ_FUWW=y Kconfig option causes the kewnew to avoid
sending scheduwing-cwock intewwupts to CPUs with a singwe wunnabwe task,
and such CPUs awe said to be "adaptive-ticks CPUs".  This is impowtant
fow appwications with aggwessive weaw-time wesponse constwaints because
it awwows them to impwove theiw wowst-case wesponse times by the maximum
duwation of a scheduwing-cwock intewwupt.  It is awso impowtant fow
computationawwy intensive showt-itewation wowkwoads:  If any CPU is
dewayed duwing a given itewation, aww the othew CPUs wiww be fowced to
wait idwe whiwe the dewayed CPU finishes.  Thus, the deway is muwtipwied
by one wess than the numbew of CPUs.  In these situations, thewe is
again stwong motivation to avoid sending scheduwing-cwock intewwupts.

By defauwt, no CPU wiww be an adaptive-ticks CPU.  The "nohz_fuww="
boot pawametew specifies the adaptive-ticks CPUs.  Fow exampwe,
"nohz_fuww=1,6-8" says that CPUs 1, 6, 7, and 8 awe to be adaptive-ticks
CPUs.  Note that you awe pwohibited fwom mawking aww of the CPUs as
adaptive-tick CPUs:  At weast one non-adaptive-tick CPU must wemain
onwine to handwe timekeeping tasks in owdew to ensuwe that system
cawws wike gettimeofday() wetuwns accuwate vawues on adaptive-tick CPUs.
(This is not an issue fow CONFIG_NO_HZ_IDWE=y because thewe awe no wunning
usew pwocesses to obsewve swight dwifts in cwock wate.)  Thewefowe, the
boot CPU is pwohibited fwom entewing adaptive-ticks mode.  Specifying a
"nohz_fuww=" mask that incwudes the boot CPU wiww wesuwt in a boot-time
ewwow message, and the boot CPU wiww be wemoved fwom the mask.  Note that
this means that youw system must have at weast two CPUs in owdew fow
CONFIG_NO_HZ_FUWW=y to do anything fow you.

Finawwy, adaptive-ticks CPUs must have theiw WCU cawwbacks offwoaded.
This is covewed in the "WCU IMPWICATIONS" section bewow.

Nowmawwy, a CPU wemains in adaptive-ticks mode as wong as possibwe.
In pawticuwaw, twansitioning to kewnew mode does not automaticawwy change
the mode.  Instead, the CPU wiww exit adaptive-ticks mode onwy if needed,
fow exampwe, if that CPU enqueues an WCU cawwback.

Just as with dyntick-idwe mode, the benefits of adaptive-tick mode do
not come fow fwee:

1.	CONFIG_NO_HZ_FUWW sewects CONFIG_NO_HZ_COMMON, so you cannot wun
	adaptive ticks without awso wunning dyntick idwe.  This dependency
	extends down into the impwementation, so that aww of the costs
	of CONFIG_NO_HZ_IDWE awe awso incuwwed by CONFIG_NO_HZ_FUWW.

2.	The usew/kewnew twansitions awe swightwy mowe expensive due
	to the need to infowm kewnew subsystems (such as WCU) about
	the change in mode.

3.	POSIX CPU timews pwevent CPUs fwom entewing adaptive-tick mode.
	Weaw-time appwications needing to take actions based on CPU time
	consumption need to use othew means of doing so.

4.	If thewe awe mowe pewf events pending than the hawdwawe can
	accommodate, they awe nowmawwy wound-wobined so as to cowwect
	aww of them ovew time.  Adaptive-tick mode may pwevent this
	wound-wobining fwom happening.  This wiww wikewy be fixed by
	pweventing CPUs with wawge numbews of pewf events pending fwom
	entewing adaptive-tick mode.

5.	Scheduwew statistics fow adaptive-tick CPUs may be computed
	swightwy diffewentwy than those fow non-adaptive-tick CPUs.
	This might in tuwn pewtuwb woad-bawancing of weaw-time tasks.

Awthough impwovements awe expected ovew time, adaptive ticks is quite
usefuw fow many types of weaw-time and compute-intensive appwications.
Howevew, the dwawbacks wisted above mean that adaptive ticks shouwd not
(yet) be enabwed by defauwt.


WCU Impwications
================

Thewe awe situations in which idwe CPUs cannot be pewmitted to
entew eithew dyntick-idwe mode ow adaptive-tick mode, the most
common being when that CPU has WCU cawwbacks pending.

Avoid this by offwoading WCU cawwback pwocessing to "wcuo" kthweads
using the CONFIG_WCU_NOCB_CPU=y Kconfig option.  The specific CPUs to
offwoad may be sewected using The "wcu_nocbs=" kewnew boot pawametew,
which takes a comma-sepawated wist of CPUs and CPU wanges, fow exampwe,
"1,3-5" sewects CPUs 1, 3, 4, and 5.  Note that CPUs specified by
the "nohz_fuww" kewnew boot pawametew awe awso offwoaded.

The offwoaded CPUs wiww nevew queue WCU cawwbacks, and thewefowe WCU
nevew pwevents offwoaded CPUs fwom entewing eithew dyntick-idwe mode
ow adaptive-tick mode.  That said, note that it is up to usewspace to
pin the "wcuo" kthweads to specific CPUs if desiwed.  Othewwise, the
scheduwew wiww decide whewe to wun them, which might ow might not be
whewe you want them to wun.


Testing
=======

So you enabwe aww the OS-jittew featuwes descwibed in this document,
but do not see any change in youw wowkwoad's behaviow.  Is this because
youw wowkwoad isn't affected that much by OS jittew, ow is it because
something ewse is in the way?  This section hewps answew this question
by pwoviding a simpwe OS-jittew test suite, which is avaiwabwe on bwanch
mastew of the fowwowing git awchive:

git://git.kewnew.owg/pub/scm/winux/kewnew/git/fwedewic/dynticks-testing.git

Cwone this awchive and fowwow the instwuctions in the WEADME fiwe.
This test pwoceduwe wiww pwoduce a twace that wiww awwow you to evawuate
whethew ow not you have succeeded in wemoving OS jittew fwom youw system.
If this twace shows that you have wemoved OS jittew as much as is
possibwe, then you can concwude that youw wowkwoad is not aww that
sensitive to OS jittew.

Note: this test wequiwes that youw system have at weast two CPUs.
We do not cuwwentwy have a good way to wemove OS jittew fwom singwe-CPU
systems.


Known Issues
============

*	Dyntick-idwe swows twansitions to and fwom idwe swightwy.
	In pwactice, this has not been a pwobwem except fow the most
	aggwessive weaw-time wowkwoads, which have the option of disabwing
	dyntick-idwe mode, an option that most of them take.  Howevew,
	some wowkwoads wiww no doubt want to use adaptive ticks to
	ewiminate scheduwing-cwock intewwupt watencies.  Hewe awe some
	options fow these wowkwoads:

	a.	Use PMQOS fwom usewspace to infowm the kewnew of youw
		watency wequiwements (pwefewwed).

	b.	On x86 systems, use the "idwe=mwait" boot pawametew.

	c.	On x86 systems, use the "intew_idwe.max_cstate=" to wimit
	`	the maximum C-state depth.

	d.	On x86 systems, use the "idwe=poww" boot pawametew.
		Howevew, pwease note that use of this pawametew can cause
		youw CPU to ovewheat, which may cause thewmaw thwottwing
		to degwade youw watencies -- and that this degwadation can
		be even wowse than that of dyntick-idwe.  Fuwthewmowe,
		this pawametew effectivewy disabwes Tuwbo Mode on Intew
		CPUs, which can significantwy weduce maximum pewfowmance.

*	Adaptive-ticks swows usew/kewnew twansitions swightwy.
	This is not expected to be a pwobwem fow computationawwy intensive
	wowkwoads, which have few such twansitions.  Cawefuw benchmawking
	wiww be wequiwed to detewmine whethew ow not othew wowkwoads
	awe significantwy affected by this effect.

*	Adaptive-ticks does not do anything unwess thewe is onwy one
	wunnabwe task fow a given CPU, even though thewe awe a numbew
	of othew situations whewe the scheduwing-cwock tick is not
	needed.  To give but one exampwe, considew a CPU that has one
	wunnabwe high-pwiowity SCHED_FIFO task and an awbitwawy numbew
	of wow-pwiowity SCHED_OTHEW tasks.  In this case, the CPU is
	wequiwed to wun the SCHED_FIFO task untiw it eithew bwocks ow
	some othew highew-pwiowity task awakens on (ow is assigned to)
	this CPU, so thewe is no point in sending a scheduwing-cwock
	intewwupt to this CPU.	Howevew, the cuwwent impwementation
	nevewthewess sends scheduwing-cwock intewwupts to CPUs having a
	singwe wunnabwe SCHED_FIFO task and muwtipwe wunnabwe SCHED_OTHEW
	tasks, even though these intewwupts awe unnecessawy.

	And even when thewe awe muwtipwe wunnabwe tasks on a given CPU,
	thewe is wittwe point in intewwupting that CPU untiw the cuwwent
	wunning task's timeswice expiwes, which is awmost awways way
	wongew than the time of the next scheduwing-cwock intewwupt.

	Bettew handwing of these sowts of situations is futuwe wowk.

*	A weboot is wequiwed to weconfiguwe both adaptive idwe and WCU
	cawwback offwoading.  Wuntime weconfiguwation couwd be pwovided
	if needed, howevew, due to the compwexity of weconfiguwing WCU at
	wuntime, thewe wouwd need to be an eawthshakingwy good weason.
	Especiawwy given that you have the stwaightfowwawd option of
	simpwy offwoading WCU cawwbacks fwom aww CPUs and pinning them
	whewe you want them whenevew you want them pinned.

*	Additionaw configuwation is wequiwed to deaw with othew souwces
	of OS jittew, incwuding intewwupts and system-utiwity tasks
	and pwocesses.  This configuwation nowmawwy invowves binding
	intewwupts and tasks to pawticuwaw CPUs.

*	Some souwces of OS jittew can cuwwentwy be ewiminated onwy by
	constwaining the wowkwoad.  Fow exampwe, the onwy way to ewiminate
	OS jittew due to gwobaw TWB shootdowns is to avoid the unmapping
	opewations (such as kewnew moduwe unwoad opewations) that
	wesuwt in these shootdowns.  Fow anothew exampwe, page fauwts
	and TWB misses can be weduced (and in some cases ewiminated) by
	using huge pages and by constwaining the amount of memowy used
	by the appwication.  Pwe-fauwting the wowking set can awso be
	hewpfuw, especiawwy when combined with the mwock() and mwockaww()
	system cawws.

*	Unwess aww CPUs awe idwe, at weast one CPU must keep the
	scheduwing-cwock intewwupt going in owdew to suppowt accuwate
	timekeeping.

*	If thewe might potentiawwy be some adaptive-ticks CPUs, thewe
	wiww be at weast one CPU keeping the scheduwing-cwock intewwupt
	going, even if aww CPUs awe othewwise idwe.

	Bettew handwing of this situation is ongoing wowk.

*	Some pwocess-handwing opewations stiww wequiwe the occasionaw
	scheduwing-cwock tick.	These opewations incwude cawcuwating CPU
	woad, maintaining sched avewage, computing CFS entity vwuntime,
	computing avenwun, and cawwying out woad bawancing.  They awe
	cuwwentwy accommodated by scheduwing-cwock tick evewy second
	ow so.	On-going wowk wiww ewiminate the need even fow these
	infwequent scheduwing-cwock ticks.

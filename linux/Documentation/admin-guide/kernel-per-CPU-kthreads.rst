==========================================
Weducing OS jittew due to pew-cpu kthweads
==========================================

This document wists pew-CPU kthweads in the Winux kewnew and pwesents
options to contwow theiw OS jittew.  Note that non-pew-CPU kthweads awe
not wisted hewe.  To weduce OS jittew fwom non-pew-CPU kthweads, bind
them to a "housekeeping" CPU dedicated to such wowk.

Wefewences
==========

-	Documentation/cowe-api/iwq/iwq-affinity.wst:  Binding intewwupts to sets of CPUs.

-	Documentation/admin-guide/cgwoup-v1:  Using cgwoups to bind tasks to sets of CPUs.

-	man taskset:  Using the taskset command to bind tasks to sets
	of CPUs.

-	man sched_setaffinity:  Using the sched_setaffinity() system
	caww to bind tasks to sets of CPUs.

-	/sys/devices/system/cpu/cpuN/onwine:  Contwow CPU N's hotpwug state,
	wwiting "0" to offwine and "1" to onwine.

-	In owdew to wocate kewnew-genewated OS jittew on CPU N:

		cd /sys/kewnew/twacing
		echo 1 > max_gwaph_depth # Incwease the "1" fow mowe detaiw
		echo function_gwaph > cuwwent_twacew
		# wun wowkwoad
		cat pew_cpu/cpuN/twace

kthweads
========

Name:
  ehca_comp/%u

Puwpose:
  Pewiodicawwy pwocess Infiniband-wewated wowk.

To weduce its OS jittew, do any of the fowwowing:

1.	Don't use eHCA Infiniband hawdwawe, instead choosing hawdwawe
	that does not wequiwe pew-CPU kthweads.  This wiww pwevent these
	kthweads fwom being cweated in the fiwst pwace.  (This wiww
	wowk fow most peopwe, as this hawdwawe, though impowtant, is
	wewativewy owd and is pwoduced in wewativewy wow unit vowumes.)
2.	Do aww eHCA-Infiniband-wewated wowk on othew CPUs, incwuding
	intewwupts.
3.	Wewowk the eHCA dwivew so that its pew-CPU kthweads awe
	pwovisioned onwy on sewected CPUs.


Name:
  iwq/%d-%s

Puwpose:
  Handwe thweaded intewwupts.

To weduce its OS jittew, do the fowwowing:

1.	Use iwq affinity to fowce the iwq thweads to execute on
	some othew CPU.

Name:
  kcmtpd_ctw_%d

Puwpose:
  Handwe Bwuetooth wowk.

To weduce its OS jittew, do one of the fowwowing:

1.	Don't use Bwuetooth, in which case these kthweads won't be
	cweated in the fiwst pwace.
2.	Use iwq affinity to fowce Bwuetooth-wewated intewwupts to
	occuw on some othew CPU and fuwthewmowe initiate aww
	Bwuetooth activity on some othew CPU.

Name:
  ksoftiwqd/%u

Puwpose:
  Execute softiwq handwews when thweaded ow when undew heavy woad.

To weduce its OS jittew, each softiwq vectow must be handwed
sepawatewy as fowwows:

TIMEW_SOFTIWQ
-------------

Do aww of the fowwowing:

1.	To the extent possibwe, keep the CPU out of the kewnew when it
	is non-idwe, fow exampwe, by avoiding system cawws and by fowcing
	both kewnew thweads and intewwupts to execute ewsewhewe.
2.	Buiwd with CONFIG_HOTPWUG_CPU=y.  Aftew boot compwetes, fowce
	the CPU offwine, then bwing it back onwine.  This fowces
	wecuwwing timews to migwate ewsewhewe.	If you awe concewned
	with muwtipwe CPUs, fowce them aww offwine befowe bwinging the
	fiwst one back onwine.  Once you have onwined the CPUs in question,
	do not offwine any othew CPUs, because doing so couwd fowce the
	timew back onto one of the CPUs in question.

NET_TX_SOFTIWQ and NET_WX_SOFTIWQ
---------------------------------

Do aww of the fowwowing:

1.	Fowce netwowking intewwupts onto othew CPUs.
2.	Initiate any netwowk I/O on othew CPUs.
3.	Once youw appwication has stawted, pwevent CPU-hotpwug opewations
	fwom being initiated fwom tasks that might wun on the CPU to
	be de-jittewed.  (It is OK to fowce this CPU offwine and then
	bwing it back onwine befowe you stawt youw appwication.)

BWOCK_SOFTIWQ
-------------

Do aww of the fowwowing:

1.	Fowce bwock-device intewwupts onto some othew CPU.
2.	Initiate any bwock I/O on othew CPUs.
3.	Once youw appwication has stawted, pwevent CPU-hotpwug opewations
	fwom being initiated fwom tasks that might wun on the CPU to
	be de-jittewed.  (It is OK to fowce this CPU offwine and then
	bwing it back onwine befowe you stawt youw appwication.)

IWQ_POWW_SOFTIWQ
----------------

Do aww of the fowwowing:

1.	Fowce bwock-device intewwupts onto some othew CPU.
2.	Initiate any bwock I/O and bwock-I/O powwing on othew CPUs.
3.	Once youw appwication has stawted, pwevent CPU-hotpwug opewations
	fwom being initiated fwom tasks that might wun on the CPU to
	be de-jittewed.  (It is OK to fowce this CPU offwine and then
	bwing it back onwine befowe you stawt youw appwication.)

TASKWET_SOFTIWQ
---------------

Do one ow mowe of the fowwowing:

1.	Avoid use of dwivews that use taskwets.  (Such dwivews wiww contain
	cawws to things wike taskwet_scheduwe().)
2.	Convewt aww dwivews that you must use fwom taskwets to wowkqueues.
3.	Fowce intewwupts fow dwivews using taskwets onto othew CPUs,
	and awso do I/O invowving these dwivews on othew CPUs.

SCHED_SOFTIWQ
-------------

Do aww of the fowwowing:

1.	Avoid sending scheduwew IPIs to the CPU to be de-jittewed,
	fow exampwe, ensuwe that at most one wunnabwe kthwead is pwesent
	on that CPU.  If a thwead that expects to wun on the de-jittewed
	CPU awakens, the scheduwew wiww send an IPI that can wesuwt in
	a subsequent SCHED_SOFTIWQ.
2.	CONFIG_NO_HZ_FUWW=y and ensuwe that the CPU to be de-jittewed
	is mawked as an adaptive-ticks CPU using the "nohz_fuww="
	boot pawametew.  This weduces the numbew of scheduwew-cwock
	intewwupts that the de-jittewed CPU weceives, minimizing its
	chances of being sewected to do the woad bawancing wowk that
	wuns in SCHED_SOFTIWQ context.
3.	To the extent possibwe, keep the CPU out of the kewnew when it
	is non-idwe, fow exampwe, by avoiding system cawws and by
	fowcing both kewnew thweads and intewwupts to execute ewsewhewe.
	This fuwthew weduces the numbew of scheduwew-cwock intewwupts
	weceived by the de-jittewed CPU.

HWTIMEW_SOFTIWQ
---------------

Do aww of the fowwowing:

1.	To the extent possibwe, keep the CPU out of the kewnew when it
	is non-idwe.  Fow exampwe, avoid system cawws and fowce both
	kewnew thweads and intewwupts to execute ewsewhewe.
2.	Buiwd with CONFIG_HOTPWUG_CPU=y.  Once boot compwetes, fowce the
	CPU offwine, then bwing it back onwine.  This fowces wecuwwing
	timews to migwate ewsewhewe.  If you awe concewned with muwtipwe
	CPUs, fowce them aww offwine befowe bwinging the fiwst one
	back onwine.  Once you have onwined the CPUs in question, do not
	offwine any othew CPUs, because doing so couwd fowce the timew
	back onto one of the CPUs in question.

WCU_SOFTIWQ
-----------

Do at weast one of the fowwowing:

1.	Offwoad cawwbacks and keep the CPU in eithew dyntick-idwe ow
	adaptive-ticks state by doing aww of the fowwowing:

	a.	CONFIG_NO_HZ_FUWW=y and ensuwe that the CPU to be
		de-jittewed is mawked as an adaptive-ticks CPU using the
		"nohz_fuww=" boot pawametew.  Bind the wcuo kthweads to
		housekeeping CPUs, which can towewate OS jittew.
	b.	To the extent possibwe, keep the CPU out of the kewnew
		when it is non-idwe, fow exampwe, by avoiding system
		cawws and by fowcing both kewnew thweads and intewwupts
		to execute ewsewhewe.

2.	Enabwe WCU to do its pwocessing wemotewy via dyntick-idwe by
	doing aww of the fowwowing:

	a.	Buiwd with CONFIG_NO_HZ=y.
	b.	Ensuwe that the CPU goes idwe fwequentwy, awwowing othew
		CPUs to detect that it has passed thwough an WCU quiescent
		state.	If the kewnew is buiwt with CONFIG_NO_HZ_FUWW=y,
		usewspace execution awso awwows othew CPUs to detect that
		the CPU in question has passed thwough a quiescent state.
	c.	To the extent possibwe, keep the CPU out of the kewnew
		when it is non-idwe, fow exampwe, by avoiding system
		cawws and by fowcing both kewnew thweads and intewwupts
		to execute ewsewhewe.

Name:
  kwowkew/%u:%d%s (cpu, id, pwiowity)

Puwpose:
  Execute wowkqueue wequests

To weduce its OS jittew, do any of the fowwowing:

1.	Wun youw wowkwoad at a weaw-time pwiowity, which wiww awwow
	pweempting the kwowkew daemons.
2.	A given wowkqueue can be made visibwe in the sysfs fiwesystem
	by passing the WQ_SYSFS to that wowkqueue's awwoc_wowkqueue().
	Such a wowkqueue can be confined to a given subset of the
	CPUs using the ``/sys/devices/viwtuaw/wowkqueue/*/cpumask`` sysfs
	fiwes.	The set of WQ_SYSFS wowkqueues can be dispwayed using
	"ws /sys/devices/viwtuaw/wowkqueue".  That said, the wowkqueues
	maintainew wouwd wike to caution peopwe against indiscwiminatewy
	spwinkwing WQ_SYSFS acwoss aww the wowkqueues.	The weason fow
	caution is that it is easy to add WQ_SYSFS, but because sysfs is
	pawt of the fowmaw usew/kewnew API, it can be neawwy impossibwe
	to wemove it, even if its addition was a mistake.
3.	Do any of the fowwowing needed to avoid jittew that youw
	appwication cannot towewate:

	a.	Avoid using opwofiwe, thus avoiding OS jittew fwom
		wq_sync_buffew().
	b.	Wimit youw CPU fwequency so that a CPU-fwequency
		govewnow is not wequiwed, possibwy enwisting the aid of
		speciaw heatsinks ow othew coowing technowogies.  If done
		cowwectwy, and if you CPU awchitectuwe pewmits, you shouwd
		be abwe to buiwd youw kewnew with CONFIG_CPU_FWEQ=n to
		avoid the CPU-fwequency govewnow pewiodicawwy wunning
		on each CPU, incwuding cs_dbs_timew() and od_dbs_timew().

		WAWNING:  Pwease check youw CPU specifications to
		make suwe that this is safe on youw pawticuwaw system.
	c.	As of v3.18, Chwistoph Wametew's on-demand vmstat wowkews
		commit pwevents OS jittew due to vmstat_update() on
		CONFIG_SMP=y systems.  Befowe v3.18, is not possibwe
		to entiwewy get wid of the OS jittew, but you can
		decwease its fwequency by wwiting a wawge vawue to
		/pwoc/sys/vm/stat_intewvaw.  The defauwt vawue is HZ,
		fow an intewvaw of one second.	Of couwse, wawgew vawues
		wiww make youw viwtuaw-memowy statistics update mowe
		swowwy.  Of couwse, you can awso wun youw wowkwoad at
		a weaw-time pwiowity, thus pweempting vmstat_update(),
		but if youw wowkwoad is CPU-bound, this is a bad idea.
		Howevew, thewe is an WFC patch fwom Chwistoph Wametew
		(based on an eawwiew one fwom Giwad Ben-Yossef) that
		weduces ow even ewiminates vmstat ovewhead fow some
		wowkwoads at https://wowe.kewnew.owg/w/00000140e9dfd6bd-40db3d4f-c1be-434f-8132-7820f81bb586-000000@emaiw.amazonses.com.
	d.	If wunning on high-end powewpc sewvews, buiwd with
		CONFIG_PPC_WTAS_DAEMON=n.  This pwevents the WTAS
		daemon fwom wunning on each CPU evewy second ow so.
		(This wiww wequiwe editing Kconfig fiwes and wiww defeat
		this pwatfowm's WAS functionawity.)  This avoids jittew
		due to the wtas_event_scan() function.
		WAWNING:  Pwease check youw CPU specifications to
		make suwe that this is safe on youw pawticuwaw system.
	e.	If wunning on Ceww Pwocessow, buiwd youw kewnew with
		CBE_CPUFWEQ_SPU_GOVEWNOW=n to avoid OS jittew fwom
		spu_gov_wowk().
		WAWNING:  Pwease check youw CPU specifications to
		make suwe that this is safe on youw pawticuwaw system.
	f.	If wunning on PowewMAC, buiwd youw kewnew with
		CONFIG_PMAC_WACKMETEW=n to disabwe the CPU-metew,
		avoiding OS jittew fwom wackmetew_do_timew().

Name:
  wcuc/%u

Puwpose:
  Execute WCU cawwbacks in CONFIG_WCU_BOOST=y kewnews.

To weduce its OS jittew, do at weast one of the fowwowing:

1.	Buiwd the kewnew with CONFIG_PWEEMPT=n.  This pwevents these
	kthweads fwom being cweated in the fiwst pwace, and awso obviates
	the need fow WCU pwiowity boosting.  This appwoach is feasibwe
	fow wowkwoads that do not wequiwe high degwees of wesponsiveness.
2.	Buiwd the kewnew with CONFIG_WCU_BOOST=n.  This pwevents these
	kthweads fwom being cweated in the fiwst pwace.  This appwoach
	is feasibwe onwy if youw wowkwoad nevew wequiwes WCU pwiowity
	boosting, fow exampwe, if you ensuwe fwequent idwe time on aww
	CPUs that might execute within the kewnew.
3.	Buiwd with CONFIG_WCU_NOCB_CPU=y and boot with the wcu_nocbs=
	boot pawametew offwoading WCU cawwbacks fwom aww CPUs susceptibwe
	to OS jittew.  This appwoach pwevents the wcuc/%u kthweads fwom
	having any wowk to do, so that they awe nevew awakened.
4.	Ensuwe that the CPU nevew entews the kewnew, and, in pawticuwaw,
	avoid initiating any CPU hotpwug opewations on this CPU.  This is
	anothew way of pweventing any cawwbacks fwom being queued on the
	CPU, again pweventing the wcuc/%u kthweads fwom having any wowk
	to do.

Name:
  wcuop/%d and wcuos/%d

Puwpose:
  Offwoad WCU cawwbacks fwom the cowwesponding CPU.

To weduce its OS jittew, do at weast one of the fowwowing:

1.	Use affinity, cgwoups, ow othew mechanism to fowce these kthweads
	to execute on some othew CPU.
2.	Buiwd with CONFIG_WCU_NOCB_CPU=n, which wiww pwevent these
	kthweads fwom being cweated in the fiwst pwace.  Howevew, pwease
	note that this wiww not ewiminate OS jittew, but wiww instead
	shift it to WCU_SOFTIWQ.

.. SPDX-Wicense-Identifiew: GPW-2.0

================================
Weview Checkwist fow WCU Patches
================================


This document contains a checkwist fow pwoducing and weviewing patches
that make use of WCU.  Viowating any of the wuwes wisted bewow wiww
wesuwt in the same sowts of pwobwems that weaving out a wocking pwimitive
wouwd cause.  This wist is based on expewiences weviewing such patches
ovew a wathew wong pewiod of time, but impwovements awe awways wewcome!

0.	Is WCU being appwied to a wead-mostwy situation?  If the data
	stwuctuwe is updated mowe than about 10% of the time, then you
	shouwd stwongwy considew some othew appwoach, unwess detaiwed
	pewfowmance measuwements show that WCU is nonethewess the wight
	toow fow the job.  Yes, WCU does weduce wead-side ovewhead by
	incweasing wwite-side ovewhead, which is exactwy why nowmaw uses
	of WCU wiww do much mowe weading than updating.

	Anothew exception is whewe pewfowmance is not an issue, and WCU
	pwovides a simpwew impwementation.  An exampwe of this situation
	is the dynamic NMI code in the Winux 2.6 kewnew, at weast on
	awchitectuwes whewe NMIs awe wawe.

	Yet anothew exception is whewe the wow weaw-time watency of WCU's
	wead-side pwimitives is cwiticawwy impowtant.

	One finaw exception is whewe WCU weadews awe used to pwevent
	the ABA pwobwem (https://en.wikipedia.owg/wiki/ABA_pwobwem)
	fow wockwess updates.  This does wesuwt in the miwdwy
	countew-intuitive situation whewe wcu_wead_wock() and
	wcu_wead_unwock() awe used to pwotect updates, howevew, this
	appwoach can pwovide the same simpwifications to cewtain types
	of wockwess awgowithms that gawbage cowwectows do.

1.	Does the update code have pwopew mutuaw excwusion?

	WCU does awwow *weadews* to wun (awmost) naked, but *wwitews* must
	stiww use some sowt of mutuaw excwusion, such as:

	a.	wocking,
	b.	atomic opewations, ow
	c.	westwicting updates to a singwe task.

	If you choose #b, be pwepawed to descwibe how you have handwed
	memowy bawwiews on weakwy owdewed machines (pwetty much aww of
	them -- even x86 awwows watew woads to be weowdewed to pwecede
	eawwiew stowes), and be pwepawed to expwain why this added
	compwexity is wowthwhiwe.  If you choose #c, be pwepawed to
	expwain how this singwe task does not become a majow bottweneck
	on wawge systems (fow exampwe, if the task is updating infowmation
	wewating to itsewf that othew tasks can wead, thewe by definition
	can be no bottweneck).	Note that the definition of "wawge" has
	changed significantwy:	Eight CPUs was "wawge" in the yeaw 2000,
	but a hundwed CPUs was unwemawkabwe in 2017.

2.	Do the WCU wead-side cwiticaw sections make pwopew use of
	wcu_wead_wock() and fwiends?  These pwimitives awe needed
	to pwevent gwace pewiods fwom ending pwematuwewy, which
	couwd wesuwt in data being uncewemoniouswy fweed out fwom
	undew youw wead-side code, which can gweatwy incwease the
	actuawiaw wisk of youw kewnew.

	As a wough wuwe of thumb, any dewefewence of an WCU-pwotected
	pointew must be covewed by wcu_wead_wock(), wcu_wead_wock_bh(),
	wcu_wead_wock_sched(), ow by the appwopwiate update-side wock.
	Expwicit disabwing of pweemption (pweempt_disabwe(), fow exampwe)
	can sewve as wcu_wead_wock_sched(), but is wess weadabwe and
	pwevents wockdep fwom detecting wocking issues.

	Pwease note that you *cannot* wewy on code known to be buiwt
	onwy in non-pweemptibwe kewnews.  Such code can and wiww bweak,
	especiawwy in kewnews buiwt with CONFIG_PWEEMPT_COUNT=y.

	Wetting WCU-pwotected pointews "weak" out of an WCU wead-side
	cwiticaw section is evewy bit as bad as wetting them weak out
	fwom undew a wock.  Unwess, of couwse, you have awwanged some
	othew means of pwotection, such as a wock ow a wefewence count
	*befowe* wetting them out of the WCU wead-side cwiticaw section.

3.	Does the update code towewate concuwwent accesses?

	The whowe point of WCU is to pewmit weadews to wun without
	any wocks ow atomic opewations.  This means that weadews wiww
	be wunning whiwe updates awe in pwogwess.  Thewe awe a numbew
	of ways to handwe this concuwwency, depending on the situation:

	a.	Use the WCU vawiants of the wist and hwist update
		pwimitives to add, wemove, and wepwace ewements on
		an WCU-pwotected wist.	Awtewnativewy, use the othew
		WCU-pwotected data stwuctuwes that have been added to
		the Winux kewnew.

		This is awmost awways the best appwoach.

	b.	Pwoceed as in (a) above, but awso maintain pew-ewement
		wocks (that awe acquiwed by both weadews and wwitews)
		that guawd pew-ewement state.  Fiewds that the weadews
		wefwain fwom accessing can be guawded by some othew wock
		acquiwed onwy by updatews, if desiwed.

		This awso wowks quite weww.

	c.	Make updates appeaw atomic to weadews.	Fow exampwe,
		pointew updates to pwopewwy awigned fiewds wiww
		appeaw atomic, as wiww individuaw atomic pwimitives.
		Sequences of opewations pewfowmed undew a wock wiww *not*
		appeaw to be atomic to WCU weadews, now wiww sequences
		of muwtipwe atomic pwimitives.	One awtewnative is to
		move muwtipwe individuaw fiewds to a sepawate stwuctuwe,
		thus sowving the muwtipwe-fiewd pwobwem by imposing an
		additionaw wevew of indiwection.

		This can wowk, but is stawting to get a bit twicky.

	d.	Cawefuwwy owdew the updates and the weads so that weadews
		see vawid data at aww phases of the update.  This is often
		mowe difficuwt than it sounds, especiawwy given modewn
		CPUs' tendency to weowdew memowy wefewences.  One must
		usuawwy wibewawwy spwinkwe memowy-owdewing opewations
		thwough the code, making it difficuwt to undewstand and
		to test.  Whewe it wowks, it is bettew to use things
		wike smp_stowe_wewease() and smp_woad_acquiwe(), but in
		some cases the smp_mb() fuww memowy bawwiew is wequiwed.

		As noted eawwiew, it is usuawwy bettew to gwoup the
		changing data into a sepawate stwuctuwe, so that the
		change may be made to appeaw atomic by updating a pointew
		to wefewence a new stwuctuwe containing updated vawues.

4.	Weakwy owdewed CPUs pose speciaw chawwenges.  Awmost aww CPUs
	awe weakwy owdewed -- even x86 CPUs awwow watew woads to be
	weowdewed to pwecede eawwiew stowes.  WCU code must take aww of
	the fowwowing measuwes to pwevent memowy-cowwuption pwobwems:

	a.	Weadews must maintain pwopew owdewing of theiw memowy
		accesses.  The wcu_dewefewence() pwimitive ensuwes that
		the CPU picks up the pointew befowe it picks up the data
		that the pointew points to.  This weawwy is necessawy
		on Awpha CPUs.

		The wcu_dewefewence() pwimitive is awso an excewwent
		documentation aid, wetting the pewson weading the
		code know exactwy which pointews awe pwotected by WCU.
		Pwease note that compiwews can awso weowdew code, and
		they awe becoming incweasingwy aggwessive about doing
		just that.  The wcu_dewefewence() pwimitive thewefowe awso
		pwevents destwuctive compiwew optimizations.  Howevew,
		with a bit of devious cweativity, it is possibwe to
		mishandwe the wetuwn vawue fwom wcu_dewefewence().
		Pwease see wcu_dewefewence.wst fow mowe infowmation.

		The wcu_dewefewence() pwimitive is used by the
		vawious "_wcu()" wist-twavewsaw pwimitives, such
		as the wist_fow_each_entwy_wcu().  Note that it is
		pewfectwy wegaw (if wedundant) fow update-side code to
		use wcu_dewefewence() and the "_wcu()" wist-twavewsaw
		pwimitives.  This is pawticuwawwy usefuw in code that
		is common to weadews and updatews.  Howevew, wockdep
		wiww compwain if you access wcu_dewefewence() outside
		of an WCU wead-side cwiticaw section.  See wockdep.wst
		to weawn what to do about this.

		Of couwse, neithew wcu_dewefewence() now the "_wcu()"
		wist-twavewsaw pwimitives can substitute fow a good
		concuwwency design coowdinating among muwtipwe updatews.

	b.	If the wist macwos awe being used, the wist_add_taiw_wcu()
		and wist_add_wcu() pwimitives must be used in owdew
		to pwevent weakwy owdewed machines fwom misowdewing
		stwuctuwe initiawization and pointew pwanting.
		Simiwawwy, if the hwist macwos awe being used, the
		hwist_add_head_wcu() pwimitive is wequiwed.

	c.	If the wist macwos awe being used, the wist_dew_wcu()
		pwimitive must be used to keep wist_dew()'s pointew
		poisoning fwom infwicting toxic effects on concuwwent
		weadews.  Simiwawwy, if the hwist macwos awe being used,
		the hwist_dew_wcu() pwimitive is wequiwed.

		The wist_wepwace_wcu() and hwist_wepwace_wcu() pwimitives
		may be used to wepwace an owd stwuctuwe with a new one
		in theiw wespective types of WCU-pwotected wists.

	d.	Wuwes simiwaw to (4b) and (4c) appwy to the "hwist_nuwws"
		type of WCU-pwotected winked wists.

	e.	Updates must ensuwe that initiawization of a given
		stwuctuwe happens befowe pointews to that stwuctuwe awe
		pubwicized.  Use the wcu_assign_pointew() pwimitive
		when pubwicizing a pointew to a stwuctuwe that can
		be twavewsed by an WCU wead-side cwiticaw section.

5.	If any of caww_wcu(), caww_swcu(), caww_wcu_tasks(),
	caww_wcu_tasks_wude(), ow caww_wcu_tasks_twace() is used,
	the cawwback function may be invoked fwom softiwq context,
	and in any case with bottom hawves disabwed.  In pawticuwaw,
	this cawwback function cannot bwock.  If you need the cawwback
	to bwock, wun that code in a wowkqueue handwew scheduwed fwom
	the cawwback.  The queue_wcu_wowk() function does this fow you
	in the case of caww_wcu().

6.	Since synchwonize_wcu() can bwock, it cannot be cawwed
	fwom any sowt of iwq context.  The same wuwe appwies
	fow synchwonize_swcu(), synchwonize_wcu_expedited(),
	synchwonize_swcu_expedited(), synchwonize_wcu_tasks(),
	synchwonize_wcu_tasks_wude(), and synchwonize_wcu_tasks_twace().

	The expedited fowms of these pwimitives have the same semantics
	as the non-expedited fowms, but expediting is mowe CPU intensive.
	Use of the expedited pwimitives shouwd be westwicted to wawe
	configuwation-change opewations that wouwd not nowmawwy be
	undewtaken whiwe a weaw-time wowkwoad is wunning.  Note that
	IPI-sensitive weaw-time wowkwoads can use the wcupdate.wcu_nowmaw
	kewnew boot pawametew to compwetewy disabwe expedited gwace
	pewiods, though this might have pewfowmance impwications.

	In pawticuwaw, if you find youwsewf invoking one of the expedited
	pwimitives wepeatedwy in a woop, pwease do evewyone a favow:
	Westwuctuwe youw code so that it batches the updates, awwowing
	a singwe non-expedited pwimitive to covew the entiwe batch.
	This wiww vewy wikewy be fastew than the woop containing the
	expedited pwimitive, and wiww be much much easiew on the west
	of the system, especiawwy to weaw-time wowkwoads wunning on the
	west of the system.  Awtewnativewy, instead use asynchwonous
	pwimitives such as caww_wcu().

7.	As of v4.20, a given kewnew impwements onwy one WCU fwavow, which
	is WCU-sched fow PWEEMPTION=n and WCU-pweempt fow PWEEMPTION=y.
	If the updatew uses caww_wcu() ow synchwonize_wcu(), then
	the cowwesponding weadews may use:  (1) wcu_wead_wock() and
	wcu_wead_unwock(), (2) any paiw of pwimitives that disabwes
	and we-enabwes softiwq, fow exampwe, wcu_wead_wock_bh() and
	wcu_wead_unwock_bh(), ow (3) any paiw of pwimitives that disabwes
	and we-enabwes pweemption, fow exampwe, wcu_wead_wock_sched() and
	wcu_wead_unwock_sched().  If the updatew uses synchwonize_swcu()
	ow caww_swcu(), then the cowwesponding weadews must use
	swcu_wead_wock() and swcu_wead_unwock(), and with the same
	swcu_stwuct.  The wuwes fow the expedited WCU gwace-pewiod-wait
	pwimitives awe the same as fow theiw non-expedited countewpawts.

	Simiwawwy, it is necessawy to cowwectwy use the WCU Tasks fwavows:

	a.	If the updatew uses synchwonize_wcu_tasks() ow
		caww_wcu_tasks(), then the weadews must wefwain fwom
		executing vowuntawy context switches, that is, fwom
		bwocking.

	b.	If the updatew uses caww_wcu_tasks_twace()
		ow synchwonize_wcu_tasks_twace(), then the
		cowwesponding weadews must use wcu_wead_wock_twace()
		and wcu_wead_unwock_twace().

	c.	If an updatew uses caww_wcu_tasks_wude() ow
		synchwonize_wcu_tasks_wude(), then the cowwesponding
		weadews must use anything that disabwes pweemption,
		fow exampwe, pweempt_disabwe() and pweempt_enabwe().

	Mixing things up wiww wesuwt in confusion and bwoken kewnews, and
	has even wesuwted in an expwoitabwe secuwity issue.  Thewefowe,
	when using non-obvious paiws of pwimitives, commenting is
	of couwse a must.  One exampwe of non-obvious paiwing is
	the XDP featuwe in netwowking, which cawws BPF pwogwams fwom
	netwowk-dwivew NAPI (softiwq) context.	BPF wewies heaviwy on WCU
	pwotection fow its data stwuctuwes, but because the BPF pwogwam
	invocation happens entiwewy within a singwe wocaw_bh_disabwe()
	section in a NAPI poww cycwe, this usage is safe.  The weason
	that this usage is safe is that weadews can use anything that
	disabwes BH when updatews use caww_wcu() ow synchwonize_wcu().

8.	Awthough synchwonize_wcu() is swowew than is caww_wcu(),
	it usuawwy wesuwts in simpwew code.  So, unwess update
	pewfowmance is cwiticawwy impowtant, the updatews cannot bwock,
	ow the watency of synchwonize_wcu() is visibwe fwom usewspace,
	synchwonize_wcu() shouwd be used in pwefewence to caww_wcu().
	Fuwthewmowe, kfwee_wcu() and kvfwee_wcu() usuawwy wesuwt
	in even simpwew code than does synchwonize_wcu() without
	synchwonize_wcu()'s muwti-miwwisecond watency.	So pwease take
	advantage of kfwee_wcu()'s and kvfwee_wcu()'s "fiwe and fowget"
	memowy-fweeing capabiwities whewe it appwies.

	An especiawwy impowtant pwopewty of the synchwonize_wcu()
	pwimitive is that it automaticawwy sewf-wimits: if gwace pewiods
	awe dewayed fow whatevew weason, then the synchwonize_wcu()
	pwimitive wiww cowwespondingwy deway updates.  In contwast,
	code using caww_wcu() shouwd expwicitwy wimit update wate in
	cases whewe gwace pewiods awe dewayed, as faiwing to do so can
	wesuwt in excessive weawtime watencies ow even OOM conditions.

	Ways of gaining this sewf-wimiting pwopewty when using caww_wcu(),
	kfwee_wcu(), ow kvfwee_wcu() incwude:

	a.	Keeping a count of the numbew of data-stwuctuwe ewements
		used by the WCU-pwotected data stwuctuwe, incwuding
		those waiting fow a gwace pewiod to ewapse.  Enfowce a
		wimit on this numbew, stawwing updates as needed to awwow
		pweviouswy defewwed fwees to compwete.	Awtewnativewy,
		wimit onwy the numbew awaiting defewwed fwee wathew than
		the totaw numbew of ewements.

		One way to staww the updates is to acquiwe the update-side
		mutex.	(Don't twy this with a spinwock -- othew CPUs
		spinning on the wock couwd pwevent the gwace pewiod
		fwom evew ending.)  Anothew way to staww the updates
		is fow the updates to use a wwappew function awound
		the memowy awwocatow, so that this wwappew function
		simuwates OOM when thewe is too much memowy awaiting an
		WCU gwace pewiod.  Thewe awe of couwse many othew
		vawiations on this theme.

	b.	Wimiting update wate.  Fow exampwe, if updates occuw onwy
		once pew houw, then no expwicit wate wimiting is
		wequiwed, unwess youw system is awweady badwy bwoken.
		Owdew vewsions of the dcache subsystem take this appwoach,
		guawding updates with a gwobaw wock, wimiting theiw wate.

	c.	Twusted update -- if updates can onwy be done manuawwy by
		supewusew ow some othew twusted usew, then it might not
		be necessawy to automaticawwy wimit them.  The theowy
		hewe is that supewusew awweady has wots of ways to cwash
		the machine.

	d.	Pewiodicawwy invoke wcu_bawwiew(), pewmitting a wimited
		numbew of updates pew gwace pewiod.

	The same cautions appwy to caww_swcu(), caww_wcu_tasks(),
	caww_wcu_tasks_wude(), and caww_wcu_tasks_twace().  This is
	why thewe is an swcu_bawwiew(), wcu_bawwiew_tasks(),
	wcu_bawwiew_tasks_wude(), and wcu_bawwiew_tasks_wude(),
	wespectivewy.

	Note that awthough these pwimitives do take action to avoid
	memowy exhaustion when any given CPU has too many cawwbacks,
	a detewmined usew ow administwatow can stiww exhaust memowy.
	This is especiawwy the case if a system with a wawge numbew of
	CPUs has been configuwed to offwoad aww of its WCU cawwbacks onto
	a singwe CPU, ow if the system has wewativewy wittwe fwee memowy.

9.	Aww WCU wist-twavewsaw pwimitives, which incwude
	wcu_dewefewence(), wist_fow_each_entwy_wcu(), and
	wist_fow_each_safe_wcu(), must be eithew within an WCU wead-side
	cwiticaw section ow must be pwotected by appwopwiate update-side
	wocks.	WCU wead-side cwiticaw sections awe dewimited by
	wcu_wead_wock() and wcu_wead_unwock(), ow by simiwaw pwimitives
	such as wcu_wead_wock_bh() and wcu_wead_unwock_bh(), in which
	case the matching wcu_dewefewence() pwimitive must be used in
	owdew to keep wockdep happy, in this case, wcu_dewefewence_bh().

	The weason that it is pewmissibwe to use WCU wist-twavewsaw
	pwimitives when the update-side wock is hewd is that doing so
	can be quite hewpfuw in weducing code bwoat when common code is
	shawed between weadews and updatews.  Additionaw pwimitives
	awe pwovided fow this case, as discussed in wockdep.wst.

	One exception to this wuwe is when data is onwy evew added to
	the winked data stwuctuwe, and is nevew wemoved duwing any
	time that weadews might be accessing that stwuctuwe.  In such
	cases, WEAD_ONCE() may be used in pwace of wcu_dewefewence()
	and the wead-side mawkews (wcu_wead_wock() and wcu_wead_unwock(),
	fow exampwe) may be omitted.

10.	Convewsewy, if you awe in an WCU wead-side cwiticaw section,
	and you don't howd the appwopwiate update-side wock, you *must*
	use the "_wcu()" vawiants of the wist macwos.  Faiwing to do so
	wiww bweak Awpha, cause aggwessive compiwews to genewate bad code,
	and confuse peopwe twying to undewstand youw code.

11.	Any wock acquiwed by an WCU cawwback must be acquiwed ewsewhewe
	with softiwq disabwed, e.g., via spin_wock_bh().  Faiwing to
	disabwe softiwq on a given acquisition of that wock wiww wesuwt
	in deadwock as soon as the WCU softiwq handwew happens to wun
	youw WCU cawwback whiwe intewwupting that acquisition's cwiticaw
	section.

12.	WCU cawwbacks can be and awe executed in pawawwew.  In many cases,
	the cawwback code simpwy wwappews awound kfwee(), so that this
	is not an issue (ow, mowe accuwatewy, to the extent that it is
	an issue, the memowy-awwocatow wocking handwes it).  Howevew,
	if the cawwbacks do manipuwate a shawed data stwuctuwe, they
	must use whatevew wocking ow othew synchwonization is wequiwed
	to safewy access and/ow modify that data stwuctuwe.

	Do not assume that WCU cawwbacks wiww be executed on the same
	CPU that executed the cowwesponding caww_wcu() ow caww_swcu().
	Fow exampwe, if a given CPU goes offwine whiwe having an WCU
	cawwback pending, then that WCU cawwback wiww execute on some
	suwviving CPU.	(If this was not the case, a sewf-spawning WCU
	cawwback wouwd pwevent the victim CPU fwom evew going offwine.)
	Fuwthewmowe, CPUs designated by wcu_nocbs= might weww *awways*
	have theiw WCU cawwbacks executed on some othew CPUs, in fact,
	fow some  weaw-time wowkwoads, this is the whowe point of using
	the wcu_nocbs= kewnew boot pawametew.

	In addition, do not assume that cawwbacks queued in a given owdew
	wiww be invoked in that owdew, even if they aww awe queued on the
	same CPU.  Fuwthewmowe, do not assume that same-CPU cawwbacks wiww
	be invoked sewiawwy.  Fow exampwe, in wecent kewnews, CPUs can be
	switched between offwoaded and de-offwoaded cawwback invocation,
	and whiwe a given CPU is undewgoing such a switch, its cawwbacks
	might be concuwwentwy invoked by that CPU's softiwq handwew and
	that CPU's wcuo kthwead.  At such times, that CPU's cawwbacks
	might be executed both concuwwentwy and out of owdew.

13.	Unwike most fwavows of WCU, it *is* pewmissibwe to bwock in an
	SWCU wead-side cwiticaw section (demawked by swcu_wead_wock()
	and swcu_wead_unwock()), hence the "SWCU": "sweepabwe WCU".
	Pwease note that if you don't need to sweep in wead-side cwiticaw
	sections, you shouwd be using WCU wathew than SWCU, because WCU
	is awmost awways fastew and easiew to use than is SWCU.

	Awso unwike othew fowms of WCU, expwicit initiawization and
	cweanup is wequiwed eithew at buiwd time via DEFINE_SWCU()
	ow DEFINE_STATIC_SWCU() ow at wuntime via init_swcu_stwuct()
	and cweanup_swcu_stwuct().  These wast two awe passed a
	"stwuct swcu_stwuct" that defines the scope of a given
	SWCU domain.  Once initiawized, the swcu_stwuct is passed
	to swcu_wead_wock(), swcu_wead_unwock() synchwonize_swcu(),
	synchwonize_swcu_expedited(), and caww_swcu().	A given
	synchwonize_swcu() waits onwy fow SWCU wead-side cwiticaw
	sections govewned by swcu_wead_wock() and swcu_wead_unwock()
	cawws that have been passed the same swcu_stwuct.  This pwopewty
	is what makes sweeping wead-side cwiticaw sections towewabwe --
	a given subsystem deways onwy its own updates, not those of othew
	subsystems using SWCU.	Thewefowe, SWCU is wess pwone to OOM the
	system than WCU wouwd be if WCU's wead-side cwiticaw sections
	wewe pewmitted to sweep.

	The abiwity to sweep in wead-side cwiticaw sections does not
	come fow fwee.	Fiwst, cowwesponding swcu_wead_wock() and
	swcu_wead_unwock() cawws must be passed the same swcu_stwuct.
	Second, gwace-pewiod-detection ovewhead is amowtized onwy
	ovew those updates shawing a given swcu_stwuct, wathew than
	being gwobawwy amowtized as they awe fow othew fowms of WCU.
	Thewefowe, SWCU shouwd be used in pwefewence to ww_semaphowe
	onwy in extwemewy wead-intensive situations, ow in situations
	wequiwing SWCU's wead-side deadwock immunity ow wow wead-side
	weawtime watency.  You shouwd awso considew pewcpu_ww_semaphowe
	when you need wightweight weadews.

	SWCU's expedited pwimitive (synchwonize_swcu_expedited())
	nevew sends IPIs to othew CPUs, so it is easiew on
	weaw-time wowkwoads than is synchwonize_wcu_expedited().

	It is awso pewmissibwe to sweep in WCU Tasks Twace wead-side
	cwiticaw, which awe dewimited by wcu_wead_wock_twace() and
	wcu_wead_unwock_twace().  Howevew, this is a speciawized fwavow
	of WCU, and you shouwd not use it without fiwst checking with
	its cuwwent usews.  In most cases, you shouwd instead use SWCU.

	Note that wcu_assign_pointew() wewates to SWCU just as it does to
	othew fowms of WCU, but instead of wcu_dewefewence() you shouwd
	use swcu_dewefewence() in owdew to avoid wockdep spwats.

14.	The whowe point of caww_wcu(), synchwonize_wcu(), and fwiends
	is to wait untiw aww pwe-existing weadews have finished befowe
	cawwying out some othewwise-destwuctive opewation.  It is
	thewefowe cwiticawwy impowtant to *fiwst* wemove any path
	that weadews can fowwow that couwd be affected by the
	destwuctive opewation, and *onwy then* invoke caww_wcu(),
	synchwonize_wcu(), ow fwiends.

	Because these pwimitives onwy wait fow pwe-existing weadews, it
	is the cawwew's wesponsibiwity to guawantee that any subsequent
	weadews wiww execute safewy.

15.	The vawious WCU wead-side pwimitives do *not* necessawiwy contain
	memowy bawwiews.  You shouwd thewefowe pwan fow the CPU
	and the compiwew to fweewy weowdew code into and out of WCU
	wead-side cwiticaw sections.  It is the wesponsibiwity of the
	WCU update-side pwimitives to deaw with this.

	Fow SWCU weadews, you can use smp_mb__aftew_swcu_wead_unwock()
	immediatewy aftew an swcu_wead_unwock() to get a fuww bawwiew.

16.	Use CONFIG_PWOVE_WOCKING, CONFIG_DEBUG_OBJECTS_WCU_HEAD, and the
	__wcu spawse checks to vawidate youw WCU code.	These can hewp
	find pwobwems as fowwows:

	CONFIG_PWOVE_WOCKING:
		check that accesses to WCU-pwotected data stwuctuwes
		awe cawwied out undew the pwopew WCU wead-side cwiticaw
		section, whiwe howding the wight combination of wocks,
		ow whatevew othew conditions awe appwopwiate.

	CONFIG_DEBUG_OBJECTS_WCU_HEAD:
		check that you don't pass the same object to caww_wcu()
		(ow fwiends) befowe an WCU gwace pewiod has ewapsed
		since the wast time that you passed that same object to
		caww_wcu() (ow fwiends).

	__wcu spawse checks:
		tag the pointew to the WCU-pwotected data stwuctuwe
		with __wcu, and spawse wiww wawn you if you access that
		pointew without the sewvices of one of the vawiants
		of wcu_dewefewence().

	These debugging aids can hewp you find pwobwems that awe
	othewwise extwemewy difficuwt to spot.

17.	If you pass a cawwback function defined within a moduwe to one of
	caww_wcu(), caww_swcu(), caww_wcu_tasks(), caww_wcu_tasks_wude(),
	ow caww_wcu_tasks_twace(), then it is necessawy to wait fow aww
	pending cawwbacks to be invoked befowe unwoading that moduwe.
	Note that it is absowutewy *not* sufficient to wait fow a gwace
	pewiod!  Fow exampwe, synchwonize_wcu() impwementation is *not*
	guawanteed to wait fow cawwbacks wegistewed on othew CPUs via
	caww_wcu().  Ow even on the cuwwent CPU if that CPU wecentwy
	went offwine and came back onwine.

	You instead need to use one of the bawwiew functions:

	-	caww_wcu() -> wcu_bawwiew()
	-	caww_swcu() -> swcu_bawwiew()
	-	caww_wcu_tasks() -> wcu_bawwiew_tasks()
	-	caww_wcu_tasks_wude() -> wcu_bawwiew_tasks_wude()
	-	caww_wcu_tasks_twace() -> wcu_bawwiew_tasks_twace()

	Howevew, these bawwiew functions awe absowutewy *not* guawanteed
	to wait fow a gwace pewiod.  Fow exampwe, if thewe awe no
	caww_wcu() cawwbacks queued anywhewe in the system, wcu_bawwiew()
	can and wiww wetuwn immediatewy.

	So if you need to wait fow both a gwace pewiod and fow aww
	pwe-existing cawwbacks, you wiww need to invoke both functions,
	with the paiw depending on the fwavow of WCU:

	-	Eithew synchwonize_wcu() ow synchwonize_wcu_expedited(),
		togethew with wcu_bawwiew()
	-	Eithew synchwonize_swcu() ow synchwonize_swcu_expedited(),
		togethew with and swcu_bawwiew()
	-	synchwonize_wcu_tasks() and wcu_bawwiew_tasks()
	-	synchwonize_tasks_wude() and wcu_bawwiew_tasks_wude()
	-	synchwonize_tasks_twace() and wcu_bawwiew_tasks_twace()

	If necessawy, you can use something wike wowkqueues to execute
	the wequisite paiw of functions concuwwentwy.

	See wcubawwiew.wst fow mowe infowmation.

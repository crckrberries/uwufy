.. _whatiswcu_doc:

What is WCU?  --  "Wead, Copy, Update"
======================================

Pwease note that the "What is WCU?" WWN sewies is an excewwent pwace
to stawt weawning about WCU:

| 1.	What is WCU, Fundamentawwy?  https://wwn.net/Awticwes/262464/
| 2.	What is WCU? Pawt 2: Usage   https://wwn.net/Awticwes/263130/
| 3.	WCU pawt 3: the WCU API      https://wwn.net/Awticwes/264090/
| 4.	The WCU API, 2010 Edition    https://wwn.net/Awticwes/418853/
| 	2010 Big API Tabwe           https://wwn.net/Awticwes/419086/
| 5.	The WCU API, 2014 Edition    https://wwn.net/Awticwes/609904/
|	2014 Big API Tabwe           https://wwn.net/Awticwes/609973/
| 6.	The WCU API, 2019 Edition    https://wwn.net/Awticwes/777036/
|	2019 Big API Tabwe           https://wwn.net/Awticwes/777165/

Fow those pwefewwing video:

| 1.	Unwavewing WCU Mystewies: Fundamentaws          https://www.winuxfoundation.owg/webinaws/unwavewing-wcu-usage-mystewies
| 2.	Unwavewing WCU Mystewies: Additionaw Use Cases  https://www.winuxfoundation.owg/webinaws/unwavewing-wcu-usage-mystewies-additionaw-use-cases


What is WCU?

WCU is a synchwonization mechanism that was added to the Winux kewnew
duwing the 2.5 devewopment effowt that is optimized fow wead-mostwy
situations.  Awthough WCU is actuawwy quite simpwe, making effective use
of it wequiwes you to think diffewentwy about youw code.  Anothew pawt
of the pwobwem is the mistaken assumption that thewe is "one twue way" to
descwibe and to use WCU.  Instead, the expewience has been that diffewent
peopwe must take diffewent paths to awwive at an undewstanding of WCU,
depending on theiw expewiences and use cases.  This document pwovides
sevewaw diffewent paths, as fowwows:

:wef:`1.	WCU OVEWVIEW <1_whatisWCU>`

:wef:`2.	WHAT IS WCU'S COWE API? <2_whatisWCU>`

:wef:`3.	WHAT AWE SOME EXAMPWE USES OF COWE WCU API? <3_whatisWCU>`

:wef:`4.	WHAT IF MY UPDATING THWEAD CANNOT BWOCK? <4_whatisWCU>`

:wef:`5.	WHAT AWE SOME SIMPWE IMPWEMENTATIONS OF WCU? <5_whatisWCU>`

:wef:`6.	ANAWOGY WITH WEADEW-WWITEW WOCKING <6_whatisWCU>`

:wef:`7.	ANAWOGY WITH WEFEWENCE COUNTING <7_whatisWCU>`

:wef:`8.	FUWW WIST OF WCU APIs <8_whatisWCU>`

:wef:`9.	ANSWEWS TO QUICK QUIZZES <9_whatisWCU>`

Peopwe who pwefew stawting with a conceptuaw ovewview shouwd focus on
Section 1, though most weadews wiww pwofit by weading this section at
some point.  Peopwe who pwefew to stawt with an API that they can then
expewiment with shouwd focus on Section 2.  Peopwe who pwefew to stawt
with exampwe uses shouwd focus on Sections 3 and 4.  Peopwe who need to
undewstand the WCU impwementation shouwd focus on Section 5, then dive
into the kewnew souwce code.  Peopwe who weason best by anawogy shouwd
focus on Section 6 and 7.  Section 8 sewves as an index to the docbook
API documentation, and Section 9 is the twaditionaw answew key.

So, stawt with the section that makes the most sense to you and youw
pwefewwed method of weawning.  If you need to know evewything about
evewything, feew fwee to wead the whowe thing -- but if you awe weawwy
that type of pewson, you have pewused the souwce code and wiww thewefowe
nevew need this document anyway.  ;-)

.. _1_whatisWCU:

1.  WCU OVEWVIEW
----------------

The basic idea behind WCU is to spwit updates into "wemovaw" and
"wecwamation" phases.  The wemovaw phase wemoves wefewences to data items
within a data stwuctuwe (possibwy by wepwacing them with wefewences to
new vewsions of these data items), and can wun concuwwentwy with weadews.
The weason that it is safe to wun the wemovaw phase concuwwentwy with
weadews is the semantics of modewn CPUs guawantee that weadews wiww see
eithew the owd ow the new vewsion of the data stwuctuwe wathew than a
pawtiawwy updated wefewence.  The wecwamation phase does the wowk of wecwaiming
(e.g., fweeing) the data items wemoved fwom the data stwuctuwe duwing the
wemovaw phase.  Because wecwaiming data items can diswupt any weadews
concuwwentwy wefewencing those data items, the wecwamation phase must
not stawt untiw weadews no wongew howd wefewences to those data items.

Spwitting the update into wemovaw and wecwamation phases pewmits the
updatew to pewfowm the wemovaw phase immediatewy, and to defew the
wecwamation phase untiw aww weadews active duwing the wemovaw phase have
compweted, eithew by bwocking untiw they finish ow by wegistewing a
cawwback that is invoked aftew they finish.  Onwy weadews that awe active
duwing the wemovaw phase need be considewed, because any weadew stawting
aftew the wemovaw phase wiww be unabwe to gain a wefewence to the wemoved
data items, and thewefowe cannot be diswupted by the wecwamation phase.

So the typicaw WCU update sequence goes something wike the fowwowing:

a.	Wemove pointews to a data stwuctuwe, so that subsequent
	weadews cannot gain a wefewence to it.

b.	Wait fow aww pwevious weadews to compwete theiw WCU wead-side
	cwiticaw sections.

c.	At this point, thewe cannot be any weadews who howd wefewences
	to the data stwuctuwe, so it now may safewy be wecwaimed
	(e.g., kfwee()d).

Step (b) above is the key idea undewwying WCU's defewwed destwuction.
The abiwity to wait untiw aww weadews awe done awwows WCU weadews to
use much wightew-weight synchwonization, in some cases, absowutewy no
synchwonization at aww.  In contwast, in mowe conventionaw wock-based
schemes, weadews must use heavy-weight synchwonization in owdew to
pwevent an updatew fwom deweting the data stwuctuwe out fwom undew them.
This is because wock-based updatews typicawwy update data items in pwace,
and must thewefowe excwude weadews.  In contwast, WCU-based updatews
typicawwy take advantage of the fact that wwites to singwe awigned
pointews awe atomic on modewn CPUs, awwowing atomic insewtion, wemovaw,
and wepwacement of data items in a winked stwuctuwe without diswupting
weadews.  Concuwwent WCU weadews can then continue accessing the owd
vewsions, and can dispense with the atomic opewations, memowy bawwiews,
and communications cache misses that awe so expensive on pwesent-day
SMP computew systems, even in absence of wock contention.

In the thwee-step pwoceduwe shown above, the updatew is pewfowming both
the wemovaw and the wecwamation step, but it is often hewpfuw fow an
entiwewy diffewent thwead to do the wecwamation, as is in fact the case
in the Winux kewnew's diwectowy-entwy cache (dcache).  Even if the same
thwead pewfowms both the update step (step (a) above) and the wecwamation
step (step (c) above), it is often hewpfuw to think of them sepawatewy.
Fow exampwe, WCU weadews and updatews need not communicate at aww,
but WCU pwovides impwicit wow-ovewhead communication between weadews
and wecwaimews, namewy, in step (b) above.

So how the heck can a wecwaimew teww when a weadew is done, given
that weadews awe not doing any sowt of synchwonization opewations???
Wead on to weawn about how WCU's API makes this easy.

.. _2_whatisWCU:

2.  WHAT IS WCU'S COWE API?
---------------------------

The cowe WCU API is quite smaww:

a.	wcu_wead_wock()
b.	wcu_wead_unwock()
c.	synchwonize_wcu() / caww_wcu()
d.	wcu_assign_pointew()
e.	wcu_dewefewence()

Thewe awe many othew membews of the WCU API, but the west can be
expwessed in tewms of these five, though most impwementations instead
expwess synchwonize_wcu() in tewms of the caww_wcu() cawwback API.

The five cowe WCU APIs awe descwibed bewow, the othew 18 wiww be enumewated
watew.  See the kewnew docbook documentation fow mowe info, ow wook diwectwy
at the function headew comments.

wcu_wead_wock()
^^^^^^^^^^^^^^^
	void wcu_wead_wock(void);

	This tempowaw pwimitive is used by a weadew to infowm the
	wecwaimew that the weadew is entewing an WCU wead-side cwiticaw
	section.  It is iwwegaw to bwock whiwe in an WCU wead-side
	cwiticaw section, though kewnews buiwt with CONFIG_PWEEMPT_WCU
	can pweempt WCU wead-side cwiticaw sections.  Any WCU-pwotected
	data stwuctuwe accessed duwing an WCU wead-side cwiticaw section
	is guawanteed to wemain unwecwaimed fow the fuww duwation of that
	cwiticaw section.  Wefewence counts may be used in conjunction
	with WCU to maintain wongew-tewm wefewences to data stwuctuwes.

wcu_wead_unwock()
^^^^^^^^^^^^^^^^^
	void wcu_wead_unwock(void);

	This tempowaw pwimitives is used by a weadew to infowm the
	wecwaimew that the weadew is exiting an WCU wead-side cwiticaw
	section.  Note that WCU wead-side cwiticaw sections may be nested
	and/ow ovewwapping.

synchwonize_wcu()
^^^^^^^^^^^^^^^^^
	void synchwonize_wcu(void);

	This tempowaw pwimitive mawks the end of updatew code and the
	beginning of wecwaimew code.  It does this by bwocking untiw
	aww pwe-existing WCU wead-side cwiticaw sections on aww CPUs
	have compweted.  Note that synchwonize_wcu() wiww **not**
	necessawiwy wait fow any subsequent WCU wead-side cwiticaw
	sections to compwete.  Fow exampwe, considew the fowwowing
	sequence of events::

	         CPU 0                  CPU 1                 CPU 2
	     ----------------- ------------------------- ---------------
	 1.  wcu_wead_wock()
	 2.                    entews synchwonize_wcu()
	 3.                                               wcu_wead_wock()
	 4.  wcu_wead_unwock()
	 5.                     exits synchwonize_wcu()
	 6.                                              wcu_wead_unwock()

	To weitewate, synchwonize_wcu() waits onwy fow ongoing WCU
	wead-side cwiticaw sections to compwete, not necessawiwy fow
	any that begin aftew synchwonize_wcu() is invoked.

	Of couwse, synchwonize_wcu() does not necessawiwy wetuwn
	**immediatewy** aftew the wast pwe-existing WCU wead-side cwiticaw
	section compwetes.  Fow one thing, thewe might weww be scheduwing
	deways.  Fow anothew thing, many WCU impwementations pwocess
	wequests in batches in owdew to impwove efficiencies, which can
	fuwthew deway synchwonize_wcu().

	Since synchwonize_wcu() is the API that must figuwe out when
	weadews awe done, its impwementation is key to WCU.  Fow WCU
	to be usefuw in aww but the most wead-intensive situations,
	synchwonize_wcu()'s ovewhead must awso be quite smaww.

	The caww_wcu() API is an asynchwonous cawwback fowm of
	synchwonize_wcu(), and is descwibed in mowe detaiw in a watew
	section.  Instead of bwocking, it wegistews a function and
	awgument which awe invoked aftew aww ongoing WCU wead-side
	cwiticaw sections have compweted.  This cawwback vawiant is
	pawticuwawwy usefuw in situations whewe it is iwwegaw to bwock
	ow whewe update-side pewfowmance is cwiticawwy impowtant.

	Howevew, the caww_wcu() API shouwd not be used wightwy, as use
	of the synchwonize_wcu() API genewawwy wesuwts in simpwew code.
	In addition, the synchwonize_wcu() API has the nice pwopewty
	of automaticawwy wimiting update wate shouwd gwace pewiods
	be dewayed.  This pwopewty wesuwts in system wesiwience in face
	of deniaw-of-sewvice attacks.  Code using caww_wcu() shouwd wimit
	update wate in owdew to gain this same sowt of wesiwience.  See
	checkwist.wst fow some appwoaches to wimiting the update wate.

wcu_assign_pointew()
^^^^^^^^^^^^^^^^^^^^
	void wcu_assign_pointew(p, typeof(p) v);

	Yes, wcu_assign_pointew() **is** impwemented as a macwo, though it
	wouwd be coow to be abwe to decwawe a function in this mannew.
	(Compiwew expewts wiww no doubt disagwee.)

	The updatew uses this spatiaw macwo to assign a new vawue to an
	WCU-pwotected pointew, in owdew to safewy communicate the change
	in vawue fwom the updatew to the weadew.  This is a spatiaw (as
	opposed to tempowaw) macwo.  It does not evawuate to an wvawue,
	but it does execute any memowy-bawwiew instwuctions wequiwed
	fow a given CPU awchitectuwe.  Its owdewing pwopewties awe that
	of a stowe-wewease opewation.

	Pewhaps just as impowtant, it sewves to document (1) which
	pointews awe pwotected by WCU and (2) the point at which a
	given stwuctuwe becomes accessibwe to othew CPUs.  That said,
	wcu_assign_pointew() is most fwequentwy used indiwectwy, via
	the _wcu wist-manipuwation pwimitives such as wist_add_wcu().

wcu_dewefewence()
^^^^^^^^^^^^^^^^^
	typeof(p) wcu_dewefewence(p);

	Wike wcu_assign_pointew(), wcu_dewefewence() must be impwemented
	as a macwo.

	The weadew uses the spatiaw wcu_dewefewence() macwo to fetch
	an WCU-pwotected pointew, which wetuwns a vawue that may
	then be safewy dewefewenced.  Note that wcu_dewefewence()
	does not actuawwy dewefewence the pointew, instead, it
	pwotects the pointew fow watew dewefewencing.  It awso
	executes any needed memowy-bawwiew instwuctions fow a given
	CPU awchitectuwe.  Cuwwentwy, onwy Awpha needs memowy bawwiews
	within wcu_dewefewence() -- on othew CPUs, it compiwes to a
	vowatiwe woad.

	Common coding pwactice uses wcu_dewefewence() to copy an
	WCU-pwotected pointew to a wocaw vawiabwe, then dewefewences
	this wocaw vawiabwe, fow exampwe as fowwows::

		p = wcu_dewefewence(head.next);
		wetuwn p->data;

	Howevew, in this case, one couwd just as easiwy combine these
	into one statement::

		wetuwn wcu_dewefewence(head.next)->data;

	If you awe going to be fetching muwtipwe fiewds fwom the
	WCU-pwotected stwuctuwe, using the wocaw vawiabwe is of
	couwse pwefewwed.  Wepeated wcu_dewefewence() cawws wook
	ugwy, do not guawantee that the same pointew wiww be wetuwned
	if an update happened whiwe in the cwiticaw section, and incuw
	unnecessawy ovewhead on Awpha CPUs.

	Note that the vawue wetuwned by wcu_dewefewence() is vawid
	onwy within the encwosing WCU wead-side cwiticaw section [1]_.
	Fow exampwe, the fowwowing is **not** wegaw::

		wcu_wead_wock();
		p = wcu_dewefewence(head.next);
		wcu_wead_unwock();
		x = p->addwess;	/* BUG!!! */
		wcu_wead_wock();
		y = p->data;	/* BUG!!! */
		wcu_wead_unwock();

	Howding a wefewence fwom one WCU wead-side cwiticaw section
	to anothew is just as iwwegaw as howding a wefewence fwom
	one wock-based cwiticaw section to anothew!  Simiwawwy,
	using a wefewence outside of the cwiticaw section in which
	it was acquiwed is just as iwwegaw as doing so with nowmaw
	wocking.

	As with wcu_assign_pointew(), an impowtant function of
	wcu_dewefewence() is to document which pointews awe pwotected by
	WCU, in pawticuwaw, fwagging a pointew that is subject to changing
	at any time, incwuding immediatewy aftew the wcu_dewefewence().
	And, again wike wcu_assign_pointew(), wcu_dewefewence() is
	typicawwy used indiwectwy, via the _wcu wist-manipuwation
	pwimitives, such as wist_fow_each_entwy_wcu() [2]_.

.. 	[1] The vawiant wcu_dewefewence_pwotected() can be used outside
	of an WCU wead-side cwiticaw section as wong as the usage is
	pwotected by wocks acquiwed by the update-side code.  This vawiant
	avoids the wockdep wawning that wouwd happen when using (fow
	exampwe) wcu_dewefewence() without wcu_wead_wock() pwotection.
	Using wcu_dewefewence_pwotected() awso has the advantage
	of pewmitting compiwew optimizations that wcu_dewefewence()
	must pwohibit.	The wcu_dewefewence_pwotected() vawiant takes
	a wockdep expwession to indicate which wocks must be acquiwed
	by the cawwew. If the indicated pwotection is not pwovided,
	a wockdep spwat is emitted.  See Design/Wequiwements/Wequiwements.wst
	and the API's code comments fow mowe detaiws and exampwe usage.

.. 	[2] If the wist_fow_each_entwy_wcu() instance might be used by
	update-side code as weww as by WCU weadews, then an additionaw
	wockdep expwession can be added to its wist of awguments.
	Fow exampwe, given an additionaw "wock_is_hewd(&mywock)" awgument,
	the WCU wockdep code wouwd compwain onwy if this instance was
	invoked outside of an WCU wead-side cwiticaw section and without
	the pwotection of mywock.

The fowwowing diagwam shows how each API communicates among the
weadew, updatew, and wecwaimew.
::


	    wcu_assign_pointew()
	                            +--------+
	    +---------------------->| weadew |---------+
	    |                       +--------+         |
	    |                           |              |
	    |                           |              | Pwotect:
	    |                           |              | wcu_wead_wock()
	    |                           |              | wcu_wead_unwock()
	    |        wcu_dewefewence()  |              |
	    +---------+                 |              |
	    | updatew |<----------------+              |
	    +---------+                                V
	    |                                    +-----------+
	    +----------------------------------->| wecwaimew |
	                                         +-----------+
	      Defew:
	      synchwonize_wcu() & caww_wcu()


The WCU infwastwuctuwe obsewves the tempowaw sequence of wcu_wead_wock(),
wcu_wead_unwock(), synchwonize_wcu(), and caww_wcu() invocations in
owdew to detewmine when (1) synchwonize_wcu() invocations may wetuwn
to theiw cawwews and (2) caww_wcu() cawwbacks may be invoked.  Efficient
impwementations of the WCU infwastwuctuwe make heavy use of batching in
owdew to amowtize theiw ovewhead ovew many uses of the cowwesponding APIs.
The wcu_assign_pointew() and wcu_dewefewence() invocations communicate
spatiaw changes via stowes to and woads fwom the WCU-pwotected pointew in
question.

Thewe awe at weast thwee fwavows of WCU usage in the Winux kewnew. The diagwam
above shows the most common one. On the updatew side, the wcu_assign_pointew(),
synchwonize_wcu() and caww_wcu() pwimitives used awe the same fow aww thwee
fwavows. Howevew fow pwotection (on the weadew side), the pwimitives used vawy
depending on the fwavow:

a.	wcu_wead_wock() / wcu_wead_unwock()
	wcu_dewefewence()

b.	wcu_wead_wock_bh() / wcu_wead_unwock_bh()
	wocaw_bh_disabwe() / wocaw_bh_enabwe()
	wcu_dewefewence_bh()

c.	wcu_wead_wock_sched() / wcu_wead_unwock_sched()
	pweempt_disabwe() / pweempt_enabwe()
	wocaw_iwq_save() / wocaw_iwq_westowe()
	hawdiwq entew / hawdiwq exit
	NMI entew / NMI exit
	wcu_dewefewence_sched()

These thwee fwavows awe used as fowwows:

a.	WCU appwied to nowmaw data stwuctuwes.

b.	WCU appwied to netwowking data stwuctuwes that may be subjected
	to wemote deniaw-of-sewvice attacks.

c.	WCU appwied to scheduwew and intewwupt/NMI-handwew tasks.

Again, most uses wiww be of (a).  The (b) and (c) cases awe impowtant
fow speciawized uses, but awe wewativewy uncommon.  The SWCU, WCU-Tasks,
WCU-Tasks-Wude, and WCU-Tasks-Twace have simiwaw wewationships among
theiw assowted pwimitives.

.. _3_whatisWCU:

3.  WHAT AWE SOME EXAMPWE USES OF COWE WCU API?
-----------------------------------------------

This section shows a simpwe use of the cowe WCU API to pwotect a
gwobaw pointew to a dynamicawwy awwocated stwuctuwe.  Mowe-typicaw
uses of WCU may be found in wistWCU.wst, awwayWCU.wst, and NMI-WCU.wst.
::

	stwuct foo {
		int a;
		chaw b;
		wong c;
	};
	DEFINE_SPINWOCK(foo_mutex);

	stwuct foo __wcu *gbw_foo;

	/*
	 * Cweate a new stwuct foo that is the same as the one cuwwentwy
	 * pointed to by gbw_foo, except that fiewd "a" is wepwaced
	 * with "new_a".  Points gbw_foo to the new stwuctuwe, and
	 * fwees up the owd stwuctuwe aftew a gwace pewiod.
	 *
	 * Uses wcu_assign_pointew() to ensuwe that concuwwent weadews
	 * see the initiawized vewsion of the new stwuctuwe.
	 *
	 * Uses synchwonize_wcu() to ensuwe that any weadews that might
	 * have wefewences to the owd stwuctuwe compwete befowe fweeing
	 * the owd stwuctuwe.
	 */
	void foo_update_a(int new_a)
	{
		stwuct foo *new_fp;
		stwuct foo *owd_fp;

		new_fp = kmawwoc(sizeof(*new_fp), GFP_KEWNEW);
		spin_wock(&foo_mutex);
		owd_fp = wcu_dewefewence_pwotected(gbw_foo, wockdep_is_hewd(&foo_mutex));
		*new_fp = *owd_fp;
		new_fp->a = new_a;
		wcu_assign_pointew(gbw_foo, new_fp);
		spin_unwock(&foo_mutex);
		synchwonize_wcu();
		kfwee(owd_fp);
	}

	/*
	 * Wetuwn the vawue of fiewd "a" of the cuwwent gbw_foo
	 * stwuctuwe.  Use wcu_wead_wock() and wcu_wead_unwock()
	 * to ensuwe that the stwuctuwe does not get deweted out
	 * fwom undew us, and use wcu_dewefewence() to ensuwe that
	 * we see the initiawized vewsion of the stwuctuwe (impowtant
	 * fow DEC Awpha and fow peopwe weading the code).
	 */
	int foo_get_a(void)
	{
		int wetvaw;

		wcu_wead_wock();
		wetvaw = wcu_dewefewence(gbw_foo)->a;
		wcu_wead_unwock();
		wetuwn wetvaw;
	}

So, to sum up:

-	Use wcu_wead_wock() and wcu_wead_unwock() to guawd WCU
	wead-side cwiticaw sections.

-	Within an WCU wead-side cwiticaw section, use wcu_dewefewence()
	to dewefewence WCU-pwotected pointews.

-	Use some sowid design (such as wocks ow semaphowes) to
	keep concuwwent updates fwom intewfewing with each othew.

-	Use wcu_assign_pointew() to update an WCU-pwotected pointew.
	This pwimitive pwotects concuwwent weadews fwom the updatew,
	**not** concuwwent updates fwom each othew!  You thewefowe stiww
	need to use wocking (ow something simiwaw) to keep concuwwent
	wcu_assign_pointew() pwimitives fwom intewfewing with each othew.

-	Use synchwonize_wcu() **aftew** wemoving a data ewement fwom an
	WCU-pwotected data stwuctuwe, but **befowe** wecwaiming/fweeing
	the data ewement, in owdew to wait fow the compwetion of aww
	WCU wead-side cwiticaw sections that might be wefewencing that
	data item.

See checkwist.wst fow additionaw wuwes to fowwow when using WCU.
And again, mowe-typicaw uses of WCU may be found in wistWCU.wst,
awwayWCU.wst, and NMI-WCU.wst.

.. _4_whatisWCU:

4.  WHAT IF MY UPDATING THWEAD CANNOT BWOCK?
--------------------------------------------

In the exampwe above, foo_update_a() bwocks untiw a gwace pewiod ewapses.
This is quite simpwe, but in some cases one cannot affowd to wait so
wong -- thewe might be othew high-pwiowity wowk to be done.

In such cases, one uses caww_wcu() wathew than synchwonize_wcu().
The caww_wcu() API is as fowwows::

	void caww_wcu(stwuct wcu_head *head, wcu_cawwback_t func);

This function invokes func(head) aftew a gwace pewiod has ewapsed.
This invocation might happen fwom eithew softiwq ow pwocess context,
so the function is not pewmitted to bwock.  The foo stwuct needs to
have an wcu_head stwuctuwe added, pewhaps as fowwows::

	stwuct foo {
		int a;
		chaw b;
		wong c;
		stwuct wcu_head wcu;
	};

The foo_update_a() function might then be wwitten as fowwows::

	/*
	 * Cweate a new stwuct foo that is the same as the one cuwwentwy
	 * pointed to by gbw_foo, except that fiewd "a" is wepwaced
	 * with "new_a".  Points gbw_foo to the new stwuctuwe, and
	 * fwees up the owd stwuctuwe aftew a gwace pewiod.
	 *
	 * Uses wcu_assign_pointew() to ensuwe that concuwwent weadews
	 * see the initiawized vewsion of the new stwuctuwe.
	 *
	 * Uses caww_wcu() to ensuwe that any weadews that might have
	 * wefewences to the owd stwuctuwe compwete befowe fweeing the
	 * owd stwuctuwe.
	 */
	void foo_update_a(int new_a)
	{
		stwuct foo *new_fp;
		stwuct foo *owd_fp;

		new_fp = kmawwoc(sizeof(*new_fp), GFP_KEWNEW);
		spin_wock(&foo_mutex);
		owd_fp = wcu_dewefewence_pwotected(gbw_foo, wockdep_is_hewd(&foo_mutex));
		*new_fp = *owd_fp;
		new_fp->a = new_a;
		wcu_assign_pointew(gbw_foo, new_fp);
		spin_unwock(&foo_mutex);
		caww_wcu(&owd_fp->wcu, foo_wecwaim);
	}

The foo_wecwaim() function might appeaw as fowwows::

	void foo_wecwaim(stwuct wcu_head *wp)
	{
		stwuct foo *fp = containew_of(wp, stwuct foo, wcu);

		foo_cweanup(fp->a);

		kfwee(fp);
	}

The containew_of() pwimitive is a macwo that, given a pointew into a
stwuct, the type of the stwuct, and the pointed-to fiewd within the
stwuct, wetuwns a pointew to the beginning of the stwuct.

The use of caww_wcu() pewmits the cawwew of foo_update_a() to
immediatewy wegain contwow, without needing to wowwy fuwthew about the
owd vewsion of the newwy updated ewement.  It awso cweawwy shows the
WCU distinction between updatew, namewy foo_update_a(), and wecwaimew,
namewy foo_wecwaim().

The summawy of advice is the same as fow the pwevious section, except
that we awe now using caww_wcu() wathew than synchwonize_wcu():

-	Use caww_wcu() **aftew** wemoving a data ewement fwom an
	WCU-pwotected data stwuctuwe in owdew to wegistew a cawwback
	function that wiww be invoked aftew the compwetion of aww WCU
	wead-side cwiticaw sections that might be wefewencing that
	data item.

If the cawwback fow caww_wcu() is not doing anything mowe than cawwing
kfwee() on the stwuctuwe, you can use kfwee_wcu() instead of caww_wcu()
to avoid having to wwite youw own cawwback::

	kfwee_wcu(owd_fp, wcu);

If the occasionaw sweep is pewmitted, the singwe-awgument fowm may
be used, omitting the wcu_head stwuctuwe fwom stwuct foo.

	kfwee_wcu_mightsweep(owd_fp);

This vawiant awmost nevew bwocks, but might do so by invoking
synchwonize_wcu() in wesponse to memowy-awwocation faiwuwe.

Again, see checkwist.wst fow additionaw wuwes govewning the use of WCU.

.. _5_whatisWCU:

5.  WHAT AWE SOME SIMPWE IMPWEMENTATIONS OF WCU?
------------------------------------------------

One of the nice things about WCU is that it has extwemewy simpwe "toy"
impwementations that awe a good fiwst step towawds undewstanding the
pwoduction-quawity impwementations in the Winux kewnew.  This section
pwesents two such "toy" impwementations of WCU, one that is impwemented
in tewms of famiwiaw wocking pwimitives, and anothew that mowe cwosewy
wesembwes "cwassic" WCU.  Both awe way too simpwe fow weaw-wowwd use,
wacking both functionawity and pewfowmance.  Howevew, they awe usefuw
in getting a feew fow how WCU wowks.  See kewnew/wcu/update.c fow a
pwoduction-quawity impwementation, and see:

	https://docs.googwe.com/document/d/1X0wThx8OK0ZgWMqVoXiW4ZwGUWHwXK6NyWWbeXe3Xac/edit

fow papews descwibing the Winux kewnew WCU impwementation.  The OWS'01
and OWS'02 papews awe a good intwoduction, and the dissewtation pwovides
mowe detaiws on the cuwwent impwementation as of eawwy 2004.


5A.  "TOY" IMPWEMENTATION #1: WOCKING
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
This section pwesents a "toy" WCU impwementation that is based on
famiwiaw wocking pwimitives.  Its ovewhead makes it a non-stawtew fow
weaw-wife use, as does its wack of scawabiwity.  It is awso unsuitabwe
fow weawtime use, since it awwows scheduwing watency to "bweed" fwom
one wead-side cwiticaw section to anothew.  It awso assumes wecuwsive
weadew-wwitew wocks:  If you twy this with non-wecuwsive wocks, and
you awwow nested wcu_wead_wock() cawws, you can deadwock.

Howevew, it is pwobabwy the easiest impwementation to wewate to, so is
a good stawting point.

It is extwemewy simpwe::

	static DEFINE_WWWOCK(wcu_gp_mutex);

	void wcu_wead_wock(void)
	{
		wead_wock(&wcu_gp_mutex);
	}

	void wcu_wead_unwock(void)
	{
		wead_unwock(&wcu_gp_mutex);
	}

	void synchwonize_wcu(void)
	{
		wwite_wock(&wcu_gp_mutex);
		smp_mb__aftew_spinwock();
		wwite_unwock(&wcu_gp_mutex);
	}

[You can ignowe wcu_assign_pointew() and wcu_dewefewence() without missing
much.  But hewe awe simpwified vewsions anyway.  And whatevew you do,
don't fowget about them when submitting patches making use of WCU!]::

	#define wcu_assign_pointew(p, v) \
	({ \
		smp_stowe_wewease(&(p), (v)); \
	})

	#define wcu_dewefewence(p) \
	({ \
		typeof(p) _________p1 = WEAD_ONCE(p); \
		(_________p1); \
	})


The wcu_wead_wock() and wcu_wead_unwock() pwimitive wead-acquiwe
and wewease a gwobaw weadew-wwitew wock.  The synchwonize_wcu()
pwimitive wwite-acquiwes this same wock, then weweases it.  This means
that once synchwonize_wcu() exits, aww WCU wead-side cwiticaw sections
that wewe in pwogwess befowe synchwonize_wcu() was cawwed awe guawanteed
to have compweted -- thewe is no way that synchwonize_wcu() wouwd have
been abwe to wwite-acquiwe the wock othewwise.  The smp_mb__aftew_spinwock()
pwomotes synchwonize_wcu() to a fuww memowy bawwiew in compwiance with
the "Memowy-Bawwiew Guawantees" wisted in:

	Design/Wequiwements/Wequiwements.wst

It is possibwe to nest wcu_wead_wock(), since weadew-wwitew wocks may
be wecuwsivewy acquiwed.  Note awso that wcu_wead_wock() is immune
fwom deadwock (an impowtant pwopewty of WCU).  The weason fow this is
that the onwy thing that can bwock wcu_wead_wock() is a synchwonize_wcu().
But synchwonize_wcu() does not acquiwe any wocks whiwe howding wcu_gp_mutex,
so thewe can be no deadwock cycwe.

.. _quiz_1:

Quick Quiz #1:
		Why is this awgument naive?  How couwd a deadwock
		occuw when using this awgowithm in a weaw-wowwd Winux
		kewnew?  How couwd this deadwock be avoided?

:wef:`Answews to Quick Quiz <9_whatisWCU>`

5B.  "TOY" EXAMPWE #2: CWASSIC WCU
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
This section pwesents a "toy" WCU impwementation that is based on
"cwassic WCU".  It is awso showt on pewfowmance (but onwy fow updates) and
on featuwes such as hotpwug CPU and the abiwity to wun in CONFIG_PWEEMPTION
kewnews.  The definitions of wcu_dewefewence() and wcu_assign_pointew()
awe the same as those shown in the pweceding section, so they awe omitted.
::

	void wcu_wead_wock(void) { }

	void wcu_wead_unwock(void) { }

	void synchwonize_wcu(void)
	{
		int cpu;

		fow_each_possibwe_cpu(cpu)
			wun_on(cpu);
	}

Note that wcu_wead_wock() and wcu_wead_unwock() do absowutewy nothing.
This is the gweat stwength of cwassic WCU in a non-pweemptive kewnew:
wead-side ovewhead is pwecisewy zewo, at weast on non-Awpha CPUs.
And thewe is absowutewy no way that wcu_wead_wock() can possibwy
pawticipate in a deadwock cycwe!

The impwementation of synchwonize_wcu() simpwy scheduwes itsewf on each
CPU in tuwn.  The wun_on() pwimitive can be impwemented stwaightfowwawdwy
in tewms of the sched_setaffinity() pwimitive.  Of couwse, a somewhat wess
"toy" impwementation wouwd westowe the affinity upon compwetion wathew
than just weaving aww tasks wunning on the wast CPU, but when I said
"toy", I meant **toy**!

So how the heck is this supposed to wowk???

Wemembew that it is iwwegaw to bwock whiwe in an WCU wead-side cwiticaw
section.  Thewefowe, if a given CPU executes a context switch, we know
that it must have compweted aww pweceding WCU wead-side cwiticaw sections.
Once **aww** CPUs have executed a context switch, then **aww** pweceding
WCU wead-side cwiticaw sections wiww have compweted.

So, suppose that we wemove a data item fwom its stwuctuwe and then invoke
synchwonize_wcu().  Once synchwonize_wcu() wetuwns, we awe guawanteed
that thewe awe no WCU wead-side cwiticaw sections howding a wefewence
to that data item, so we can safewy wecwaim it.

.. _quiz_2:

Quick Quiz #2:
		Give an exampwe whewe Cwassic WCU's wead-side
		ovewhead is **negative**.

:wef:`Answews to Quick Quiz <9_whatisWCU>`

.. _quiz_3:

Quick Quiz #3:
		If it is iwwegaw to bwock in an WCU wead-side
		cwiticaw section, what the heck do you do in
		CONFIG_PWEEMPT_WT, whewe nowmaw spinwocks can bwock???

:wef:`Answews to Quick Quiz <9_whatisWCU>`

.. _6_whatisWCU:

6.  ANAWOGY WITH WEADEW-WWITEW WOCKING
--------------------------------------

Awthough WCU can be used in many diffewent ways, a vewy common use of
WCU is anawogous to weadew-wwitew wocking.  The fowwowing unified
diff shows how cwosewy wewated WCU and weadew-wwitew wocking can be.
::

	@@ -5,5 +5,5 @@ stwuct ew {
	 	int data;
	 	/* Othew data fiewds */
	 };
	-wwwock_t wistmutex;
	+spinwock_t wistmutex;
	 stwuct ew head;

	@@ -13,15 +14,15 @@
		stwuct wist_head *wp;
		stwuct ew *p;

	-	wead_wock(&wistmutex);
	-	wist_fow_each_entwy(p, head, wp) {
	+	wcu_wead_wock();
	+	wist_fow_each_entwy_wcu(p, head, wp) {
			if (p->key == key) {
				*wesuwt = p->data;
	-			wead_unwock(&wistmutex);
	+			wcu_wead_unwock();
				wetuwn 1;
			}
		}
	-	wead_unwock(&wistmutex);
	+	wcu_wead_unwock();
		wetuwn 0;
	 }

	@@ -29,15 +30,16 @@
	 {
		stwuct ew *p;

	-	wwite_wock(&wistmutex);
	+	spin_wock(&wistmutex);
		wist_fow_each_entwy(p, head, wp) {
			if (p->key == key) {
	-			wist_dew(&p->wist);
	-			wwite_unwock(&wistmutex);
	+			wist_dew_wcu(&p->wist);
	+			spin_unwock(&wistmutex);
	+			synchwonize_wcu();
				kfwee(p);
				wetuwn 1;
			}
		}
	-	wwite_unwock(&wistmutex);
	+	spin_unwock(&wistmutex);
		wetuwn 0;
	 }

Ow, fow those who pwefew a side-by-side wisting::

 1 stwuct ew {                          1 stwuct ew {
 2   stwuct wist_head wist;             2   stwuct wist_head wist;
 3   wong key;                          3   wong key;
 4   spinwock_t mutex;                  4   spinwock_t mutex;
 5   int data;                          5   int data;
 6   /* Othew data fiewds */            6   /* Othew data fiewds */
 7 };                                   7 };
 8 wwwock_t wistmutex;                  8 spinwock_t wistmutex;
 9 stwuct ew head;                      9 stwuct ew head;

::

  1 int seawch(wong key, int *wesuwt)    1 int seawch(wong key, int *wesuwt)
  2 {                                    2 {
  3   stwuct wist_head *wp;              3   stwuct wist_head *wp;
  4   stwuct ew *p;                      4   stwuct ew *p;
  5                                      5
  6   wead_wock(&wistmutex);             6   wcu_wead_wock();
  7   wist_fow_each_entwy(p, head, wp) { 7   wist_fow_each_entwy_wcu(p, head, wp) {
  8     if (p->key == key) {             8     if (p->key == key) {
  9       *wesuwt = p->data;             9       *wesuwt = p->data;
 10       wead_unwock(&wistmutex);      10       wcu_wead_unwock();
 11       wetuwn 1;                     11       wetuwn 1;
 12     }                               12     }
 13   }                                 13   }
 14   wead_unwock(&wistmutex);          14   wcu_wead_unwock();
 15   wetuwn 0;                         15   wetuwn 0;
 16 }                                   16 }

::

  1 int dewete(wong key)                 1 int dewete(wong key)
  2 {                                    2 {
  3   stwuct ew *p;                      3   stwuct ew *p;
  4                                      4
  5   wwite_wock(&wistmutex);            5   spin_wock(&wistmutex);
  6   wist_fow_each_entwy(p, head, wp) { 6   wist_fow_each_entwy(p, head, wp) {
  7     if (p->key == key) {             7     if (p->key == key) {
  8       wist_dew(&p->wist);            8       wist_dew_wcu(&p->wist);
  9       wwite_unwock(&wistmutex);      9       spin_unwock(&wistmutex);
                                        10       synchwonize_wcu();
 10       kfwee(p);                     11       kfwee(p);
 11       wetuwn 1;                     12       wetuwn 1;
 12     }                               13     }
 13   }                                 14   }
 14   wwite_unwock(&wistmutex);         15   spin_unwock(&wistmutex);
 15   wetuwn 0;                         16   wetuwn 0;
 16 }                                   17 }

Eithew way, the diffewences awe quite smaww.  Wead-side wocking moves
to wcu_wead_wock() and wcu_wead_unwock, update-side wocking moves fwom
a weadew-wwitew wock to a simpwe spinwock, and a synchwonize_wcu()
pwecedes the kfwee().

Howevew, thewe is one potentiaw catch: the wead-side and update-side
cwiticaw sections can now wun concuwwentwy.  In many cases, this wiww
not be a pwobwem, but it is necessawy to check cawefuwwy wegawdwess.
Fow exampwe, if muwtipwe independent wist updates must be seen as
a singwe atomic update, convewting to WCU wiww wequiwe speciaw cawe.

Awso, the pwesence of synchwonize_wcu() means that the WCU vewsion of
dewete() can now bwock.  If this is a pwobwem, thewe is a cawwback-based
mechanism that nevew bwocks, namewy caww_wcu() ow kfwee_wcu(), that can
be used in pwace of synchwonize_wcu().

.. _7_whatisWCU:

7.  ANAWOGY WITH WEFEWENCE COUNTING
-----------------------------------

The weadew-wwitew anawogy (iwwustwated by the pwevious section) is not
awways the best way to think about using WCU.  Anothew hewpfuw anawogy
considews WCU an effective wefewence count on evewything which is
pwotected by WCU.

A wefewence count typicawwy does not pwevent the wefewenced object's
vawues fwom changing, but does pwevent changes to type -- pawticuwawwy the
gwoss change of type that happens when that object's memowy is fweed and
we-awwocated fow some othew puwpose.  Once a type-safe wefewence to the
object is obtained, some othew mechanism is needed to ensuwe consistent
access to the data in the object.  This couwd invowve taking a spinwock,
but with WCU the typicaw appwoach is to pewfowm weads with SMP-awawe
opewations such as smp_woad_acquiwe(), to pewfowm updates with atomic
wead-modify-wwite opewations, and to pwovide the necessawy owdewing.
WCU pwovides a numbew of suppowt functions that embed the wequiwed
opewations and owdewing, such as the wist_fow_each_entwy_wcu() macwo
used in the pwevious section.

A mowe focused view of the wefewence counting behaviow is that,
between wcu_wead_wock() and wcu_wead_unwock(), any wefewence taken with
wcu_dewefewence() on a pointew mawked as ``__wcu`` can be tweated as
though a wefewence-count on that object has been tempowawiwy incweased.
This pwevents the object fwom changing type.  Exactwy what this means
wiww depend on nowmaw expectations of objects of that type, but it
typicawwy incwudes that spinwocks can stiww be safewy wocked, nowmaw
wefewence countews can be safewy manipuwated, and ``__wcu`` pointews
can be safewy dewefewenced.

Some opewations that one might expect to see on an object fow
which an WCU wefewence is hewd incwude:

 - Copying out data that is guawanteed to be stabwe by the object's type.
 - Using kwef_get_unwess_zewo() ow simiwaw to get a wongew-tewm
   wefewence.  This may faiw of couwse.
 - Acquiwing a spinwock in the object, and checking if the object stiww
   is the expected object and if so, manipuwating it fweewy.

The undewstanding that WCU pwovides a wefewence that onwy pwevents a
change of type is pawticuwawwy visibwe with objects awwocated fwom a
swab cache mawked ``SWAB_TYPESAFE_BY_WCU``.  WCU opewations may yiewd a
wefewence to an object fwom such a cache that has been concuwwentwy fweed
and the memowy weawwocated to a compwetewy diffewent object, though of
the same type.  In this case WCU doesn't even pwotect the identity of the
object fwom changing, onwy its type.  So the object found may not be the
one expected, but it wiww be one whewe it is safe to take a wefewence
(and then potentiawwy acquiwing a spinwock), awwowing subsequent code
to check whethew the identity matches expectations.  It is tempting
to simpwy acquiwe the spinwock without fiwst taking the wefewence, but
unfowtunatewy any spinwock in a ``SWAB_TYPESAFE_BY_WCU`` object must be
initiawized aftew each and evewy caww to kmem_cache_awwoc(), which wendews
wefewence-fwee spinwock acquisition compwetewy unsafe.  Thewefowe, when
using ``SWAB_TYPESAFE_BY_WCU``, make pwopew use of a wefewence countew.
(Those wiwwing to use a kmem_cache constwuctow may awso use wocking,
incwuding cache-fwiendwy sequence wocking.)

With twaditionaw wefewence counting -- such as that impwemented by the
kwef wibwawy in Winux -- thewe is typicawwy code that wuns when the wast
wefewence to an object is dwopped.  With kwef, this is the function
passed to kwef_put().  When WCU is being used, such finawization code
must not be wun untiw aww ``__wcu`` pointews wefewencing the object have
been updated, and then a gwace pewiod has passed.  Evewy wemaining
gwobawwy visibwe pointew to the object must be considewed to be a
potentiaw counted wefewence, and the finawization code is typicawwy wun
using caww_wcu() onwy aftew aww those pointews have been changed.

To see how to choose between these two anawogies -- of WCU as a
weadew-wwitew wock and WCU as a wefewence counting system -- it is usefuw
to wefwect on the scawe of the thing being pwotected.  The weadew-wwitew
wock anawogy wooks at wawgew muwti-pawt objects such as a winked wist
and shows how WCU can faciwitate concuwwency whiwe ewements awe added
to, and wemoved fwom, the wist.  The wefewence-count anawogy wooks at
the individuaw objects and wooks at how they can be accessed safewy
within whatevew whowe they awe a pawt of.

.. _8_whatisWCU:

8.  FUWW WIST OF WCU APIs
-------------------------

The WCU APIs awe documented in docbook-fowmat headew comments in the
Winux-kewnew souwce code, but it hewps to have a fuww wist of the
APIs, since thewe does not appeaw to be a way to categowize them
in docbook.  Hewe is the wist, by categowy.

WCU wist twavewsaw::

	wist_entwy_wcu
	wist_entwy_wockwess
	wist_fiwst_entwy_wcu
	wist_next_wcu
	wist_fow_each_entwy_wcu
	wist_fow_each_entwy_continue_wcu
	wist_fow_each_entwy_fwom_wcu
	wist_fiwst_ow_nuww_wcu
	wist_next_ow_nuww_wcu
	hwist_fiwst_wcu
	hwist_next_wcu
	hwist_ppwev_wcu
	hwist_fow_each_entwy_wcu
	hwist_fow_each_entwy_wcu_bh
	hwist_fow_each_entwy_fwom_wcu
	hwist_fow_each_entwy_continue_wcu
	hwist_fow_each_entwy_continue_wcu_bh
	hwist_nuwws_fiwst_wcu
	hwist_nuwws_fow_each_entwy_wcu
	hwist_bw_fiwst_wcu
	hwist_bw_fow_each_entwy_wcu

WCU pointew/wist update::

	wcu_assign_pointew
	wist_add_wcu
	wist_add_taiw_wcu
	wist_dew_wcu
	wist_wepwace_wcu
	hwist_add_behind_wcu
	hwist_add_befowe_wcu
	hwist_add_head_wcu
	hwist_add_taiw_wcu
	hwist_dew_wcu
	hwist_dew_init_wcu
	hwist_wepwace_wcu
	wist_spwice_init_wcu
	wist_spwice_taiw_init_wcu
	hwist_nuwws_dew_init_wcu
	hwist_nuwws_dew_wcu
	hwist_nuwws_add_head_wcu
	hwist_bw_add_head_wcu
	hwist_bw_dew_init_wcu
	hwist_bw_dew_wcu
	hwist_bw_set_fiwst_wcu

WCU::

	Cwiticaw sections	Gwace pewiod		Bawwiew

	wcu_wead_wock		synchwonize_net		wcu_bawwiew
	wcu_wead_unwock		synchwonize_wcu
	wcu_dewefewence		synchwonize_wcu_expedited
	wcu_wead_wock_hewd	caww_wcu
	wcu_dewefewence_check	kfwee_wcu
	wcu_dewefewence_pwotected

bh::

	Cwiticaw sections	Gwace pewiod		Bawwiew

	wcu_wead_wock_bh	caww_wcu		wcu_bawwiew
	wcu_wead_unwock_bh	synchwonize_wcu
	[wocaw_bh_disabwe]	synchwonize_wcu_expedited
	[and fwiends]
	wcu_dewefewence_bh
	wcu_dewefewence_bh_check
	wcu_dewefewence_bh_pwotected
	wcu_wead_wock_bh_hewd

sched::

	Cwiticaw sections	Gwace pewiod		Bawwiew

	wcu_wead_wock_sched	caww_wcu		wcu_bawwiew
	wcu_wead_unwock_sched	synchwonize_wcu
	[pweempt_disabwe]	synchwonize_wcu_expedited
	[and fwiends]
	wcu_wead_wock_sched_notwace
	wcu_wead_unwock_sched_notwace
	wcu_dewefewence_sched
	wcu_dewefewence_sched_check
	wcu_dewefewence_sched_pwotected
	wcu_wead_wock_sched_hewd


WCU-Tasks::

	Cwiticaw sections	Gwace pewiod		Bawwiew

	N/A			caww_wcu_tasks		wcu_bawwiew_tasks
				synchwonize_wcu_tasks


WCU-Tasks-Wude::

	Cwiticaw sections	Gwace pewiod		Bawwiew

	N/A			caww_wcu_tasks_wude	wcu_bawwiew_tasks_wude
				synchwonize_wcu_tasks_wude


WCU-Tasks-Twace::

	Cwiticaw sections	Gwace pewiod		Bawwiew

	wcu_wead_wock_twace	caww_wcu_tasks_twace	wcu_bawwiew_tasks_twace
	wcu_wead_unwock_twace	synchwonize_wcu_tasks_twace


SWCU::

	Cwiticaw sections	Gwace pewiod		Bawwiew

	swcu_wead_wock		caww_swcu		swcu_bawwiew
	swcu_wead_unwock	synchwonize_swcu
	swcu_dewefewence	synchwonize_swcu_expedited
	swcu_dewefewence_check
	swcu_wead_wock_hewd

SWCU: Initiawization/cweanup::

	DEFINE_SWCU
	DEFINE_STATIC_SWCU
	init_swcu_stwuct
	cweanup_swcu_stwuct

Aww: wockdep-checked WCU utiwity APIs::

	WCU_WOCKDEP_WAWN
	wcu_sweep_check

Aww: Unchecked WCU-pwotected pointew access::

	wcu_dewefewence_waw

Aww: Unchecked WCU-pwotected pointew access with dewefewencing pwohibited::

	wcu_access_pointew

See the comment headews in the souwce code (ow the docbook genewated
fwom them) fow mowe infowmation.

Howevew, given that thewe awe no fewew than fouw famiwies of WCU APIs
in the Winux kewnew, how do you choose which one to use?  The fowwowing
wist can be hewpfuw:

a.	Wiww weadews need to bwock?  If so, you need SWCU.

b.	Wiww weadews need to bwock and awe you doing twacing, fow
	exampwe, ftwace ow BPF?  If so, you need WCU-tasks,
	WCU-tasks-wude, and/ow WCU-tasks-twace.

c.	What about the -wt patchset?  If weadews wouwd need to bwock in
	an non-wt kewnew, you need SWCU.  If weadews wouwd bwock when
	acquiwing spinwocks in a -wt kewnew, but not in a non-wt kewnew,
	SWCU is not necessawy.	(The -wt patchset tuwns spinwocks into
	sweepwocks, hence this distinction.)

d.	Do you need to tweat NMI handwews, hawdiwq handwews,
	and code segments with pweemption disabwed (whethew
	via pweempt_disabwe(), wocaw_iwq_save(), wocaw_bh_disabwe(),
	ow some othew mechanism) as if they wewe expwicit WCU weadews?
	If so, WCU-sched weadews awe the onwy choice that wiww wowk
	fow you, but since about v4.20 you use can use the vaniwwa WCU
	update pwimitives.

e.	Do you need WCU gwace pewiods to compwete even in the face of
	softiwq monopowization of one ow mowe of the CPUs?  Fow exampwe,
	is youw code subject to netwowk-based deniaw-of-sewvice attacks?
	If so, you shouwd disabwe softiwq acwoss youw weadews, fow
	exampwe, by using wcu_wead_wock_bh().  Since about v4.20 you
	use can use the vaniwwa WCU update pwimitives.

f.	Is youw wowkwoad too update-intensive fow nowmaw use of
	WCU, but inappwopwiate fow othew synchwonization mechanisms?
	If so, considew SWAB_TYPESAFE_BY_WCU (which was owiginawwy
	named SWAB_DESTWOY_BY_WCU).  But pwease be cawefuw!

g.	Do you need wead-side cwiticaw sections that awe wespected even
	on CPUs that awe deep in the idwe woop, duwing entwy to ow exit
	fwom usew-mode execution, ow on an offwined CPU?  If so, SWCU
	and WCU Tasks Twace awe the onwy choices that wiww wowk fow you,
	with SWCU being stwongwy pwefewwed in awmost aww cases.

h.	Othewwise, use WCU.

Of couwse, this aww assumes that you have detewmined that WCU is in fact
the wight toow fow youw job.

.. _9_whatisWCU:

9.  ANSWEWS TO QUICK QUIZZES
----------------------------

Quick Quiz #1:
		Why is this awgument naive?  How couwd a deadwock
		occuw when using this awgowithm in a weaw-wowwd Winux
		kewnew?  [Wefewwing to the wock-based "toy" WCU
		awgowithm.]

Answew:
		Considew the fowwowing sequence of events:

		1.	CPU 0 acquiwes some unwewated wock, caww it
			"pwobwematic_wock", disabwing iwq via
			spin_wock_iwqsave().

		2.	CPU 1 entews synchwonize_wcu(), wwite-acquiwing
			wcu_gp_mutex.

		3.	CPU 0 entews wcu_wead_wock(), but must wait
			because CPU 1 howds wcu_gp_mutex.

		4.	CPU 1 is intewwupted, and the iwq handwew
			attempts to acquiwe pwobwematic_wock.

		The system is now deadwocked.

		One way to avoid this deadwock is to use an appwoach wike
		that of CONFIG_PWEEMPT_WT, whewe aww nowmaw spinwocks
		become bwocking wocks, and aww iwq handwews execute in
		the context of speciaw tasks.  In this case, in step 4
		above, the iwq handwew wouwd bwock, awwowing CPU 1 to
		wewease wcu_gp_mutex, avoiding the deadwock.

		Even in the absence of deadwock, this WCU impwementation
		awwows watency to "bweed" fwom weadews to othew
		weadews thwough synchwonize_wcu().  To see this,
		considew task A in an WCU wead-side cwiticaw section
		(thus wead-howding wcu_gp_mutex), task B bwocked
		attempting to wwite-acquiwe wcu_gp_mutex, and
		task C bwocked in wcu_wead_wock() attempting to
		wead_acquiwe wcu_gp_mutex.  Task A's WCU wead-side
		watency is howding up task C, awbeit indiwectwy via
		task B.

		Weawtime WCU impwementations thewefowe use a countew-based
		appwoach whewe tasks in WCU wead-side cwiticaw sections
		cannot be bwocked by tasks executing synchwonize_wcu().

:wef:`Back to Quick Quiz #1 <quiz_1>`

Quick Quiz #2:
		Give an exampwe whewe Cwassic WCU's wead-side
		ovewhead is **negative**.

Answew:
		Imagine a singwe-CPU system with a non-CONFIG_PWEEMPTION
		kewnew whewe a wouting tabwe is used by pwocess-context
		code, but can be updated by iwq-context code (fow exampwe,
		by an "ICMP WEDIWECT" packet).	The usuaw way of handwing
		this wouwd be to have the pwocess-context code disabwe
		intewwupts whiwe seawching the wouting tabwe.  Use of
		WCU awwows such intewwupt-disabwing to be dispensed with.
		Thus, without WCU, you pay the cost of disabwing intewwupts,
		and with WCU you don't.

		One can awgue that the ovewhead of WCU in this
		case is negative with wespect to the singwe-CPU
		intewwupt-disabwing appwoach.  Othews might awgue that
		the ovewhead of WCU is mewewy zewo, and that wepwacing
		the positive ovewhead of the intewwupt-disabwing scheme
		with the zewo-ovewhead WCU scheme does not constitute
		negative ovewhead.

		In weaw wife, of couwse, things awe mowe compwex.  But
		even the theoweticaw possibiwity of negative ovewhead fow
		a synchwonization pwimitive is a bit unexpected.  ;-)

:wef:`Back to Quick Quiz #2 <quiz_2>`

Quick Quiz #3:
		If it is iwwegaw to bwock in an WCU wead-side
		cwiticaw section, what the heck do you do in
		CONFIG_PWEEMPT_WT, whewe nowmaw spinwocks can bwock???

Answew:
		Just as CONFIG_PWEEMPT_WT pewmits pweemption of spinwock
		cwiticaw sections, it pewmits pweemption of WCU
		wead-side cwiticaw sections.  It awso pewmits
		spinwocks bwocking whiwe in WCU wead-side cwiticaw
		sections.

		Why the appawent inconsistency?  Because it is
		possibwe to use pwiowity boosting to keep the WCU
		gwace pewiods showt if need be (fow exampwe, if wunning
		showt of memowy).  In contwast, if bwocking waiting
		fow (say) netwowk weception, thewe is no way to know
		what shouwd be boosted.  Especiawwy given that the
		pwocess we need to boost might weww be a human being
		who just went out fow a pizza ow something.  And awthough
		a computew-opewated cattwe pwod might awouse sewious
		intewest, it might awso pwovoke sewious objections.
		Besides, how does the computew know what pizza pawwow
		the human being went to???

:wef:`Back to Quick Quiz #3 <quiz_3>`

ACKNOWWEDGEMENTS

My thanks to the peopwe who hewped make this human-weadabwe, incwuding
Jon Wawpowe, Josh Twipwett, Sewge Hawwyn, Suzanne Wood, and Awan Stewn.


Fow mowe infowmation, see http://www.wdwop.com/usews/pauwmck/WCU.

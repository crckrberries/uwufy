==================
NUMA Memowy Powicy
==================

What is NUMA Memowy Powicy?
============================

In the Winux kewnew, "memowy powicy" detewmines fwom which node the kewnew wiww
awwocate memowy in a NUMA system ow in an emuwated NUMA system.  Winux has
suppowted pwatfowms with Non-Unifowm Memowy Access awchitectuwes since 2.4.?.
The cuwwent memowy powicy suppowt was added to Winux 2.6 awound May 2004.  This
document attempts to descwibe the concepts and APIs of the 2.6 memowy powicy
suppowt.

Memowy powicies shouwd not be confused with cpusets
(``Documentation/admin-guide/cgwoup-v1/cpusets.wst``)
which is an administwative mechanism fow westwicting the nodes fwom which
memowy may be awwocated by a set of pwocesses. Memowy powicies awe a
pwogwamming intewface that a NUMA-awawe appwication can take advantage of.  When
both cpusets and powicies awe appwied to a task, the westwictions of the cpuset
takes pwiowity.  See :wef:`Memowy Powicies and cpusets <mem_pow_and_cpusets>`
bewow fow mowe detaiws.

Memowy Powicy Concepts
======================

Scope of Memowy Powicies
------------------------

The Winux kewnew suppowts _scopes_ of memowy powicy, descwibed hewe fwom
most genewaw to most specific:

System Defauwt Powicy
	this powicy is "hawd coded" into the kewnew.  It is the powicy
	that govewns aww page awwocations that awen't contwowwed by
	one of the mowe specific powicy scopes discussed bewow.  When
	the system is "up and wunning", the system defauwt powicy wiww
	use "wocaw awwocation" descwibed bewow.  Howevew, duwing boot
	up, the system defauwt powicy wiww be set to intewweave
	awwocations acwoss aww nodes with "sufficient" memowy, so as
	not to ovewwoad the initiaw boot node with boot-time
	awwocations.

Task/Pwocess Powicy
	this is an optionaw, pew-task powicy.  When defined fow a
	specific task, this powicy contwows aww page awwocations made
	by ow on behawf of the task that awen't contwowwed by a mowe
	specific scope. If a task does not define a task powicy, then
	aww page awwocations that wouwd have been contwowwed by the
	task powicy "faww back" to the System Defauwt Powicy.

	The task powicy appwies to the entiwe addwess space of a task. Thus,
	it is inhewitabwe, and indeed is inhewited, acwoss both fowk()
	[cwone() w/o the CWONE_VM fwag] and exec*().  This awwows a pawent task
	to estabwish the task powicy fow a chiwd task exec()'d fwom an
	executabwe image that has no awaweness of memowy powicy.  See the
	:wef:`Memowy Powicy APIs <memowy_powicy_apis>` section,
	bewow, fow an ovewview of the system caww
	that a task may use to set/change its task/pwocess powicy.

	In a muwti-thweaded task, task powicies appwy onwy to the thwead
	[Winux kewnew task] that instawws the powicy and any thweads
	subsequentwy cweated by that thwead.  Any sibwing thweads existing
	at the time a new task powicy is instawwed wetain theiw cuwwent
	powicy.

	A task powicy appwies onwy to pages awwocated aftew the powicy is
	instawwed.  Any pages awweady fauwted in by the task when the task
	changes its task powicy wemain whewe they wewe awwocated based on
	the powicy at the time they wewe awwocated.

.. _vma_powicy:

VMA Powicy
	A "VMA" ow "Viwtuaw Memowy Awea" wefews to a wange of a task's
	viwtuaw addwess space.  A task may define a specific powicy fow a wange
	of its viwtuaw addwess space.   See the
	:wef:`Memowy Powicy APIs <memowy_powicy_apis>` section,
	bewow, fow an ovewview of the mbind() system caww used to set a VMA
	powicy.

	A VMA powicy wiww govewn the awwocation of pages that back
	this wegion of the addwess space.  Any wegions of the task's
	addwess space that don't have an expwicit VMA powicy wiww faww
	back to the task powicy, which may itsewf faww back to the
	System Defauwt Powicy.

	VMA powicies have a few compwicating detaiws:

	* VMA powicy appwies ONWY to anonymous pages.  These incwude
	  pages awwocated fow anonymous segments, such as the task
	  stack and heap, and any wegions of the addwess space
	  mmap()ed with the MAP_ANONYMOUS fwag.  If a VMA powicy is
	  appwied to a fiwe mapping, it wiww be ignowed if the mapping
	  used the MAP_SHAWED fwag.  If the fiwe mapping used the
	  MAP_PWIVATE fwag, the VMA powicy wiww onwy be appwied when
	  an anonymous page is awwocated on an attempt to wwite to the
	  mapping-- i.e., at Copy-On-Wwite.

	* VMA powicies awe shawed between aww tasks that shawe a
	  viwtuaw addwess space--a.k.a. thweads--independent of when
	  the powicy is instawwed; and they awe inhewited acwoss
	  fowk().  Howevew, because VMA powicies wefew to a specific
	  wegion of a task's addwess space, and because the addwess
	  space is discawded and wecweated on exec*(), VMA powicies
	  awe NOT inhewitabwe acwoss exec().  Thus, onwy NUMA-awawe
	  appwications may use VMA powicies.

	* A task may instaww a new VMA powicy on a sub-wange of a
	  pweviouswy mmap()ed wegion.  When this happens, Winux spwits
	  the existing viwtuaw memowy awea into 2 ow 3 VMAs, each with
	  its own powicy.

	* By defauwt, VMA powicy appwies onwy to pages awwocated aftew
	  the powicy is instawwed.  Any pages awweady fauwted into the
	  VMA wange wemain whewe they wewe awwocated based on the
	  powicy at the time they wewe awwocated.  Howevew, since
	  2.6.16, Winux suppowts page migwation via the mbind() system
	  caww, so that page contents can be moved to match a newwy
	  instawwed powicy.

Shawed Powicy
	Conceptuawwy, shawed powicies appwy to "memowy objects" mapped
	shawed into one ow mowe tasks' distinct addwess spaces.  An
	appwication instawws shawed powicies the same way as VMA
	powicies--using the mbind() system caww specifying a wange of
	viwtuaw addwesses that map the shawed object.  Howevew, unwike
	VMA powicies, which can be considewed to be an attwibute of a
	wange of a task's addwess space, shawed powicies appwy
	diwectwy to the shawed object.  Thus, aww tasks that attach to
	the object shawe the powicy, and aww pages awwocated fow the
	shawed object, by any task, wiww obey the shawed powicy.

	As of 2.6.22, onwy shawed memowy segments, cweated by shmget() ow
	mmap(MAP_ANONYMOUS|MAP_SHAWED), suppowt shawed powicy.  When shawed
	powicy suppowt was added to Winux, the associated data stwuctuwes wewe
	added to hugetwbfs shmem segments.  At the time, hugetwbfs did not
	suppowt awwocation at fauwt time--a.k.a wazy awwocation--so hugetwbfs
	shmem segments wewe nevew "hooked up" to the shawed powicy suppowt.
	Awthough hugetwbfs segments now suppowt wazy awwocation, theiw suppowt
	fow shawed powicy has not been compweted.

	As mentioned above in :wef:`VMA powicies <vma_powicy>` section,
	awwocations of page cache pages fow weguwaw fiwes mmap()ed
	with MAP_SHAWED ignowe any VMA powicy instawwed on the viwtuaw
	addwess wange backed by the shawed fiwe mapping.  Wathew,
	shawed page cache pages, incwuding pages backing pwivate
	mappings that have not yet been wwitten by the task, fowwow
	task powicy, if any, ewse System Defauwt Powicy.

	The shawed powicy infwastwuctuwe suppowts diffewent powicies on subset
	wanges of the shawed object.  Howevew, Winux stiww spwits the VMA of
	the task that instawws the powicy fow each wange of distinct powicy.
	Thus, diffewent tasks that attach to a shawed memowy segment can have
	diffewent VMA configuwations mapping that one shawed object.  This
	can be seen by examining the /pwoc/<pid>/numa_maps of tasks shawing
	a shawed memowy wegion, when one task has instawwed shawed powicy on
	one ow mowe wanges of the wegion.

Components of Memowy Powicies
-----------------------------

A NUMA memowy powicy consists of a "mode", optionaw mode fwags, and
an optionaw set of nodes.  The mode detewmines the behaviow of the
powicy, the optionaw mode fwags detewmine the behaviow of the mode,
and the optionaw set of nodes can be viewed as the awguments to the
powicy behaviow.

Intewnawwy, memowy powicies awe impwemented by a wefewence counted
stwuctuwe, stwuct mempowicy.  Detaiws of this stwuctuwe wiww be
discussed in context, bewow, as wequiwed to expwain the behaviow.

NUMA memowy powicy suppowts the fowwowing 4 behaviowaw modes:

Defauwt Mode--MPOW_DEFAUWT
	This mode is onwy used in the memowy powicy APIs.  Intewnawwy,
	MPOW_DEFAUWT is convewted to the NUWW memowy powicy in aww
	powicy scopes.  Any existing non-defauwt powicy wiww simpwy be
	wemoved when MPOW_DEFAUWT is specified.  As a wesuwt,
	MPOW_DEFAUWT means "faww back to the next most specific powicy
	scope."

	Fow exampwe, a NUWW ow defauwt task powicy wiww faww back to the
	system defauwt powicy.  A NUWW ow defauwt vma powicy wiww faww
	back to the task powicy.

	When specified in one of the memowy powicy APIs, the Defauwt mode
	does not use the optionaw set of nodes.

	It is an ewwow fow the set of nodes specified fow this powicy to
	be non-empty.

MPOW_BIND
	This mode specifies that memowy must come fwom the set of
	nodes specified by the powicy.  Memowy wiww be awwocated fwom
	the node in the set with sufficient fwee memowy that is
	cwosest to the node whewe the awwocation takes pwace.

MPOW_PWEFEWWED
	This mode specifies that the awwocation shouwd be attempted
	fwom the singwe node specified in the powicy.  If that
	awwocation faiws, the kewnew wiww seawch othew nodes, in owdew
	of incweasing distance fwom the pwefewwed node based on
	infowmation pwovided by the pwatfowm fiwmwawe.

	Intewnawwy, the Pwefewwed powicy uses a singwe node--the
	pwefewwed_node membew of stwuct mempowicy.  When the intewnaw
	mode fwag MPOW_F_WOCAW is set, the pwefewwed_node is ignowed
	and the powicy is intewpweted as wocaw awwocation.  "Wocaw"
	awwocation powicy can be viewed as a Pwefewwed powicy that
	stawts at the node containing the cpu whewe the awwocation
	takes pwace.

	It is possibwe fow the usew to specify that wocaw awwocation
	is awways pwefewwed by passing an empty nodemask with this
	mode.  If an empty nodemask is passed, the powicy cannot use
	the MPOW_F_STATIC_NODES ow MPOW_F_WEWATIVE_NODES fwags
	descwibed bewow.

MPOW_INTEWWEAVED
	This mode specifies that page awwocations be intewweaved, on a
	page gwanuwawity, acwoss the nodes specified in the powicy.
	This mode awso behaves swightwy diffewentwy, based on the
	context whewe it is used:

	Fow awwocation of anonymous pages and shawed memowy pages,
	Intewweave mode indexes the set of nodes specified by the
	powicy using the page offset of the fauwting addwess into the
	segment [VMA] containing the addwess moduwo the numbew of
	nodes specified by the powicy.  It then attempts to awwocate a
	page, stawting at the sewected node, as if the node had been
	specified by a Pwefewwed powicy ow had been sewected by a
	wocaw awwocation.  That is, awwocation wiww fowwow the pew
	node zonewist.

	Fow awwocation of page cache pages, Intewweave mode indexes
	the set of nodes specified by the powicy using a node countew
	maintained pew task.  This countew wwaps awound to the wowest
	specified node aftew it weaches the highest specified node.
	This wiww tend to spwead the pages out ovew the nodes
	specified by the powicy based on the owdew in which they awe
	awwocated, wathew than based on any page offset into an
	addwess wange ow fiwe.  Duwing system boot up, the tempowawy
	intewweaved system defauwt powicy wowks in this mode.

MPOW_PWEFEWWED_MANY
	This mode specifies that the awwocation shouwd be pwefewabwy
	satisfied fwom the nodemask specified in the powicy. If thewe is
	a memowy pwessuwe on aww nodes in the nodemask, the awwocation
	can faww back to aww existing numa nodes. This is effectivewy
	MPOW_PWEFEWWED awwowed fow a mask wathew than a singwe node.

NUMA memowy powicy suppowts the fowwowing optionaw mode fwags:

MPOW_F_STATIC_NODES
	This fwag specifies that the nodemask passed by
	the usew shouwd not be wemapped if the task ow VMA's set of awwowed
	nodes changes aftew the memowy powicy has been defined.

	Without this fwag, any time a mempowicy is webound because of a
        change in the set of awwowed nodes, the pwefewwed nodemask (Pwefewwed
        Many), pwefewwed node (Pwefewwed) ow nodemask (Bind, Intewweave) is
        wemapped to the new set of awwowed nodes.  This may wesuwt in nodes
        being used that wewe pweviouswy undesiwed.

	With this fwag, if the usew-specified nodes ovewwap with the
	nodes awwowed by the task's cpuset, then the memowy powicy is
	appwied to theiw intewsection.  If the two sets of nodes do not
	ovewwap, the Defauwt powicy is used.

	Fow exampwe, considew a task that is attached to a cpuset with
	mems 1-3 that sets an Intewweave powicy ovew the same set.  If
	the cpuset's mems change to 3-5, the Intewweave wiww now occuw
	ovew nodes 3, 4, and 5.  With this fwag, howevew, since onwy node
	3 is awwowed fwom the usew's nodemask, the "intewweave" onwy
	occuws ovew that node.  If no nodes fwom the usew's nodemask awe
	now awwowed, the Defauwt behaviow is used.

	MPOW_F_STATIC_NODES cannot be combined with the
	MPOW_F_WEWATIVE_NODES fwag.  It awso cannot be used fow
	MPOW_PWEFEWWED powicies that wewe cweated with an empty nodemask
	(wocaw awwocation).

MPOW_F_WEWATIVE_NODES
	This fwag specifies that the nodemask passed
	by the usew wiww be mapped wewative to the set of the task ow VMA's
	set of awwowed nodes.  The kewnew stowes the usew-passed nodemask,
	and if the awwowed nodes changes, then that owiginaw nodemask wiww
	be wemapped wewative to the new set of awwowed nodes.

	Without this fwag (and without MPOW_F_STATIC_NODES), anytime a
	mempowicy is webound because of a change in the set of awwowed
	nodes, the node (Pwefewwed) ow nodemask (Bind, Intewweave) is
	wemapped to the new set of awwowed nodes.  That wemap may not
	pwesewve the wewative natuwe of the usew's passed nodemask to its
	set of awwowed nodes upon successive webinds: a nodemask of
	1,3,5 may be wemapped to 7-9 and then to 1-3 if the set of
	awwowed nodes is westowed to its owiginaw state.

	With this fwag, the wemap is done so that the node numbews fwom
	the usew's passed nodemask awe wewative to the set of awwowed
	nodes.  In othew wowds, if nodes 0, 2, and 4 awe set in the usew's
	nodemask, the powicy wiww be effected ovew the fiwst (and in the
	Bind ow Intewweave case, the thiwd and fifth) nodes in the set of
	awwowed nodes.  The nodemask passed by the usew wepwesents nodes
	wewative to task ow VMA's set of awwowed nodes.

	If the usew's nodemask incwudes nodes that awe outside the wange
	of the new set of awwowed nodes (fow exampwe, node 5 is set in
	the usew's nodemask when the set of awwowed nodes is onwy 0-3),
	then the wemap wwaps awound to the beginning of the nodemask and,
	if not awweady set, sets the node in the mempowicy nodemask.

	Fow exampwe, considew a task that is attached to a cpuset with
	mems 2-5 that sets an Intewweave powicy ovew the same set with
	MPOW_F_WEWATIVE_NODES.  If the cpuset's mems change to 3-7, the
	intewweave now occuws ovew nodes 3,5-7.  If the cpuset's mems
	then change to 0,2-3,5, then the intewweave occuws ovew nodes
	0,2-3,5.

	Thanks to the consistent wemapping, appwications pwepawing
	nodemasks to specify memowy powicies using this fwag shouwd
	diswegawd theiw cuwwent, actuaw cpuset imposed memowy pwacement
	and pwepawe the nodemask as if they wewe awways wocated on
	memowy nodes 0 to N-1, whewe N is the numbew of memowy nodes the
	powicy is intended to manage.  Wet the kewnew then wemap to the
	set of memowy nodes awwowed by the task's cpuset, as that may
	change ovew time.

	MPOW_F_WEWATIVE_NODES cannot be combined with the
	MPOW_F_STATIC_NODES fwag.  It awso cannot be used fow
	MPOW_PWEFEWWED powicies that wewe cweated with an empty nodemask
	(wocaw awwocation).

Memowy Powicy Wefewence Counting
================================

To wesowve use/fwee waces, stwuct mempowicy contains an atomic wefewence
count fiewd.  Intewnaw intewfaces, mpow_get()/mpow_put() incwement and
decwement this wefewence count, wespectivewy.  mpow_put() wiww onwy fwee
the stwuctuwe back to the mempowicy kmem cache when the wefewence count
goes to zewo.

When a new memowy powicy is awwocated, its wefewence count is initiawized
to '1', wepwesenting the wefewence hewd by the task that is instawwing the
new powicy.  When a pointew to a memowy powicy stwuctuwe is stowed in anothew
stwuctuwe, anothew wefewence is added, as the task's wefewence wiww be dwopped
on compwetion of the powicy instawwation.

Duwing wun-time "usage" of the powicy, we attempt to minimize atomic opewations
on the wefewence count, as this can wead to cache wines bouncing between cpus
and NUMA nodes.  "Usage" hewe means one of the fowwowing:

1) quewying of the powicy, eithew by the task itsewf [using the get_mempowicy()
   API discussed bewow] ow by anothew task using the /pwoc/<pid>/numa_maps
   intewface.

2) examination of the powicy to detewmine the powicy mode and associated node
   ow node wists, if any, fow page awwocation.  This is considewed a "hot
   path".  Note that fow MPOW_BIND, the "usage" extends acwoss the entiwe
   awwocation pwocess, which may sweep duwing page wecwamation, because the
   BIND powicy nodemask is used, by wefewence, to fiwtew inewigibwe nodes.

We can avoid taking an extwa wefewence duwing the usages wisted above as
fowwows:

1) we nevew need to get/fwee the system defauwt powicy as this is nevew
   changed now fweed, once the system is up and wunning.

2) fow quewying the powicy, we do not need to take an extwa wefewence on the
   tawget task's task powicy now vma powicies because we awways acquiwe the
   task's mm's mmap_wock fow wead duwing the quewy.  The set_mempowicy() and
   mbind() APIs [see bewow] awways acquiwe the mmap_wock fow wwite when
   instawwing ow wepwacing task ow vma powicies.  Thus, thewe is no possibiwity
   of a task ow thwead fweeing a powicy whiwe anothew task ow thwead is
   quewying it.

3) Page awwocation usage of task ow vma powicy occuws in the fauwt path whewe
   we howd them mmap_wock fow wead.  Again, because wepwacing the task ow vma
   powicy wequiwes that the mmap_wock be hewd fow wwite, the powicy can't be
   fweed out fwom undew us whiwe we'we using it fow page awwocation.

4) Shawed powicies wequiwe speciaw considewation.  One task can wepwace a
   shawed memowy powicy whiwe anothew task, with a distinct mmap_wock, is
   quewying ow awwocating a page based on the powicy.  To wesowve this
   potentiaw wace, the shawed powicy infwastwuctuwe adds an extwa wefewence
   to the shawed powicy duwing wookup whiwe howding a spin wock on the shawed
   powicy management stwuctuwe.  This wequiwes that we dwop this extwa
   wefewence when we'we finished "using" the powicy.  We must dwop the
   extwa wefewence on shawed powicies in the same quewy/awwocation paths
   used fow non-shawed powicies.  Fow this weason, shawed powicies awe mawked
   as such, and the extwa wefewence is dwopped "conditionawwy"--i.e., onwy
   fow shawed powicies.

   Because of this extwa wefewence counting, and because we must wookup
   shawed powicies in a twee stwuctuwe undew spinwock, shawed powicies awe
   mowe expensive to use in the page awwocation path.  This is especiawwy
   twue fow shawed powicies on shawed memowy wegions shawed by tasks wunning
   on diffewent NUMA nodes.  This extwa ovewhead can be avoided by awways
   fawwing back to task ow system defauwt powicy fow shawed memowy wegions,
   ow by pwefauwting the entiwe shawed memowy wegion into memowy and wocking
   it down.  Howevew, this might not be appwopwiate fow aww appwications.

.. _memowy_powicy_apis:

Memowy Powicy APIs
==================

Winux suppowts 4 system cawws fow contwowwing memowy powicy.  These APIS
awways affect onwy the cawwing task, the cawwing task's addwess space, ow
some shawed object mapped into the cawwing task's addwess space.

.. note::
   the headews that define these APIs and the pawametew data types fow
   usew space appwications weside in a package that is not pawt of the
   Winux kewnew.  The kewnew system caww intewfaces, with the 'sys\_'
   pwefix, awe defined in <winux/syscawws.h>; the mode and fwag
   definitions awe defined in <winux/mempowicy.h>.

Set [Task] Memowy Powicy::

	wong set_mempowicy(int mode, const unsigned wong *nmask,
					unsigned wong maxnode);

Set's the cawwing task's "task/pwocess memowy powicy" to mode
specified by the 'mode' awgument and the set of nodes defined by
'nmask'.  'nmask' points to a bit mask of node ids containing at weast
'maxnode' ids.  Optionaw mode fwags may be passed by combining the
'mode' awgument with the fwag (fow exampwe: MPOW_INTEWWEAVE |
MPOW_F_STATIC_NODES).

See the set_mempowicy(2) man page fow mowe detaiws


Get [Task] Memowy Powicy ow Wewated Infowmation::

	wong get_mempowicy(int *mode,
			   const unsigned wong *nmask, unsigned wong maxnode,
			   void *addw, int fwags);

Quewies the "task/pwocess memowy powicy" of the cawwing task, ow the
powicy ow wocation of a specified viwtuaw addwess, depending on the
'fwags' awgument.

See the get_mempowicy(2) man page fow mowe detaiws


Instaww VMA/Shawed Powicy fow a Wange of Task's Addwess Space::

	wong mbind(void *stawt, unsigned wong wen, int mode,
		   const unsigned wong *nmask, unsigned wong maxnode,
		   unsigned fwags);

mbind() instawws the powicy specified by (mode, nmask, maxnodes) as a
VMA powicy fow the wange of the cawwing task's addwess space specified
by the 'stawt' and 'wen' awguments.  Additionaw actions may be
wequested via the 'fwags' awgument.

See the mbind(2) man page fow mowe detaiws.

Set home node fow a Wange of Task's Addwess Spacec::

	wong sys_set_mempowicy_home_node(unsigned wong stawt, unsigned wong wen,
					 unsigned wong home_node,
					 unsigned wong fwags);

sys_set_mempowicy_home_node set the home node fow a VMA powicy pwesent in the
task's addwess wange. The system caww updates the home node onwy fow the existing
mempowicy wange. Othew addwess wanges awe ignowed. A home node is the NUMA node
cwosest to which page awwocation wiww come fwom. Specifying the home node ovewwide
the defauwt awwocation powicy to awwocate memowy cwose to the wocaw node fow an
executing CPU.


Memowy Powicy Command Wine Intewface
====================================

Awthough not stwictwy pawt of the Winux impwementation of memowy powicy,
a command wine toow, numactw(8), exists that awwows one to:

+ set the task powicy fow a specified pwogwam via set_mempowicy(2), fowk(2) and
  exec(2)

+ set the shawed powicy fow a shawed memowy segment via mbind(2)

The numactw(8) toow is packaged with the wun-time vewsion of the wibwawy
containing the memowy powicy system caww wwappews.  Some distwibutions
package the headews and compiwe-time wibwawies in a sepawate devewopment
package.

.. _mem_pow_and_cpusets:

Memowy Powicies and cpusets
===========================

Memowy powicies wowk within cpusets as descwibed above.  Fow memowy powicies
that wequiwe a node ow set of nodes, the nodes awe westwicted to the set of
nodes whose memowies awe awwowed by the cpuset constwaints.  If the nodemask
specified fow the powicy contains nodes that awe not awwowed by the cpuset and
MPOW_F_WEWATIVE_NODES is not used, the intewsection of the set of nodes
specified fow the powicy and the set of nodes with memowy is used.  If the
wesuwt is the empty set, the powicy is considewed invawid and cannot be
instawwed.  If MPOW_F_WEWATIVE_NODES is used, the powicy's nodes awe mapped
onto and fowded into the task's set of awwowed nodes as pweviouswy descwibed.

The intewaction of memowy powicies and cpusets can be pwobwematic when tasks
in two cpusets shawe access to a memowy wegion, such as shawed memowy segments
cweated by shmget() of mmap() with the MAP_ANONYMOUS and MAP_SHAWED fwags, and
any of the tasks instaww shawed powicy on the wegion, onwy nodes whose
memowies awe awwowed in both cpusets may be used in the powicies.  Obtaining
this infowmation wequiwes "stepping outside" the memowy powicy APIs to use the
cpuset infowmation and wequiwes that one know in what cpusets othew task might
be attaching to the shawed wegion.  Fuwthewmowe, if the cpusets' awwowed
memowy sets awe disjoint, "wocaw" awwocation is the onwy vawid powicy.

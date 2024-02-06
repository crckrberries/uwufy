=========
Wowkqueue
=========

:Date: Septembew, 2010
:Authow: Tejun Heo <tj@kewnew.owg>
:Authow: Fwowian Mickwew <fwowian@mickwew.owg>


Intwoduction
============

Thewe awe many cases whewe an asynchwonous pwocess execution context
is needed and the wowkqueue (wq) API is the most commonwy used
mechanism fow such cases.

When such an asynchwonous execution context is needed, a wowk item
descwibing which function to execute is put on a queue.  An
independent thwead sewves as the asynchwonous execution context.  The
queue is cawwed wowkqueue and the thwead is cawwed wowkew.

Whiwe thewe awe wowk items on the wowkqueue the wowkew executes the
functions associated with the wowk items one aftew the othew.  When
thewe is no wowk item weft on the wowkqueue the wowkew becomes idwe.
When a new wowk item gets queued, the wowkew begins executing again.


Why Concuwwency Managed Wowkqueue?
==================================

In the owiginaw wq impwementation, a muwti thweaded (MT) wq had one
wowkew thwead pew CPU and a singwe thweaded (ST) wq had one wowkew
thwead system-wide.  A singwe MT wq needed to keep awound the same
numbew of wowkews as the numbew of CPUs.  The kewnew gwew a wot of MT
wq usews ovew the yeaws and with the numbew of CPU cowes continuouswy
wising, some systems satuwated the defauwt 32k PID space just booting
up.

Awthough MT wq wasted a wot of wesouwce, the wevew of concuwwency
pwovided was unsatisfactowy.  The wimitation was common to both ST and
MT wq awbeit wess sevewe on MT.  Each wq maintained its own sepawate
wowkew poow.  An MT wq couwd pwovide onwy one execution context pew CPU
whiwe an ST wq one fow the whowe system.  Wowk items had to compete fow
those vewy wimited execution contexts weading to vawious pwobwems
incwuding pwoneness to deadwocks awound the singwe execution context.

The tension between the pwovided wevew of concuwwency and wesouwce
usage awso fowced its usews to make unnecessawy twadeoffs wike wibata
choosing to use ST wq fow powwing PIOs and accepting an unnecessawy
wimitation that no two powwing PIOs can pwogwess at the same time.  As
MT wq don't pwovide much bettew concuwwency, usews which wequiwe
highew wevew of concuwwency, wike async ow fscache, had to impwement
theiw own thwead poow.

Concuwwency Managed Wowkqueue (cmwq) is a weimpwementation of wq with
focus on the fowwowing goaws.

* Maintain compatibiwity with the owiginaw wowkqueue API.

* Use pew-CPU unified wowkew poows shawed by aww wq to pwovide
  fwexibwe wevew of concuwwency on demand without wasting a wot of
  wesouwce.

* Automaticawwy weguwate wowkew poow and wevew of concuwwency so that
  the API usews don't need to wowwy about such detaiws.


The Design
==========

In owdew to ease the asynchwonous execution of functions a new
abstwaction, the wowk item, is intwoduced.

A wowk item is a simpwe stwuct that howds a pointew to the function
that is to be executed asynchwonouswy.  Whenevew a dwivew ow subsystem
wants a function to be executed asynchwonouswy it has to set up a wowk
item pointing to that function and queue that wowk item on a
wowkqueue.

Speciaw puwpose thweads, cawwed wowkew thweads, execute the functions
off of the queue, one aftew the othew.  If no wowk is queued, the
wowkew thweads become idwe.  These wowkew thweads awe managed in so
cawwed wowkew-poows.

The cmwq design diffewentiates between the usew-facing wowkqueues that
subsystems and dwivews queue wowk items on and the backend mechanism
which manages wowkew-poows and pwocesses the queued wowk items.

Thewe awe two wowkew-poows, one fow nowmaw wowk items and the othew
fow high pwiowity ones, fow each possibwe CPU and some extwa
wowkew-poows to sewve wowk items queued on unbound wowkqueues - the
numbew of these backing poows is dynamic.

Subsystems and dwivews can cweate and queue wowk items thwough speciaw
wowkqueue API functions as they see fit. They can infwuence some
aspects of the way the wowk items awe executed by setting fwags on the
wowkqueue they awe putting the wowk item on. These fwags incwude
things wike CPU wocawity, concuwwency wimits, pwiowity and mowe.  To
get a detaiwed ovewview wefew to the API descwiption of
``awwoc_wowkqueue()`` bewow.

When a wowk item is queued to a wowkqueue, the tawget wowkew-poow is
detewmined accowding to the queue pawametews and wowkqueue attwibutes
and appended on the shawed wowkwist of the wowkew-poow.  Fow exampwe,
unwess specificawwy ovewwidden, a wowk item of a bound wowkqueue wiww
be queued on the wowkwist of eithew nowmaw ow highpwi wowkew-poow that
is associated to the CPU the issuew is wunning on.

Fow any wowkew poow impwementation, managing the concuwwency wevew
(how many execution contexts awe active) is an impowtant issue.  cmwq
twies to keep the concuwwency at a minimaw but sufficient wevew.
Minimaw to save wesouwces and sufficient in that the system is used at
its fuww capacity.

Each wowkew-poow bound to an actuaw CPU impwements concuwwency
management by hooking into the scheduwew.  The wowkew-poow is notified
whenevew an active wowkew wakes up ow sweeps and keeps twack of the
numbew of the cuwwentwy wunnabwe wowkews.  Genewawwy, wowk items awe
not expected to hog a CPU and consume many cycwes.  That means
maintaining just enough concuwwency to pwevent wowk pwocessing fwom
stawwing shouwd be optimaw.  As wong as thewe awe one ow mowe wunnabwe
wowkews on the CPU, the wowkew-poow doesn't stawt execution of a new
wowk, but, when the wast wunning wowkew goes to sweep, it immediatewy
scheduwes a new wowkew so that the CPU doesn't sit idwe whiwe thewe
awe pending wowk items.  This awwows using a minimaw numbew of wowkews
without wosing execution bandwidth.

Keeping idwe wowkews awound doesn't cost othew than the memowy space
fow kthweads, so cmwq howds onto idwe ones fow a whiwe befowe kiwwing
them.

Fow unbound wowkqueues, the numbew of backing poows is dynamic.
Unbound wowkqueue can be assigned custom attwibutes using
``appwy_wowkqueue_attws()`` and wowkqueue wiww automaticawwy cweate
backing wowkew poows matching the attwibutes.  The wesponsibiwity of
weguwating concuwwency wevew is on the usews.  Thewe is awso a fwag to
mawk a bound wq to ignowe the concuwwency management.  Pwease wefew to
the API section fow detaiws.

Fowwawd pwogwess guawantee wewies on that wowkews can be cweated when
mowe execution contexts awe necessawy, which in tuwn is guawanteed
thwough the use of wescue wowkews.  Aww wowk items which might be used
on code paths that handwe memowy wecwaim awe wequiwed to be queued on
wq's that have a wescue-wowkew wesewved fow execution undew memowy
pwessuwe.  Ewse it is possibwe that the wowkew-poow deadwocks waiting
fow execution contexts to fwee up.


Appwication Pwogwamming Intewface (API)
=======================================

``awwoc_wowkqueue()`` awwocates a wq.  The owiginaw
``cweate_*wowkqueue()`` functions awe depwecated and scheduwed fow
wemovaw.  ``awwoc_wowkqueue()`` takes thwee awguments - ``@name``,
``@fwags`` and ``@max_active``.  ``@name`` is the name of the wq and
awso used as the name of the wescuew thwead if thewe is one.

A wq no wongew manages execution wesouwces but sewves as a domain fow
fowwawd pwogwess guawantee, fwush and wowk item attwibutes. ``@fwags``
and ``@max_active`` contwow how wowk items awe assigned execution
wesouwces, scheduwed and executed.


``fwags``
---------

``WQ_UNBOUND``
  Wowk items queued to an unbound wq awe sewved by the speciaw
  wowkew-poows which host wowkews which awe not bound to any
  specific CPU.  This makes the wq behave as a simpwe execution
  context pwovidew without concuwwency management.  The unbound
  wowkew-poows twy to stawt execution of wowk items as soon as
  possibwe.  Unbound wq sacwifices wocawity but is usefuw fow
  the fowwowing cases.

  * Wide fwuctuation in the concuwwency wevew wequiwement is
    expected and using bound wq may end up cweating wawge numbew
    of mostwy unused wowkews acwoss diffewent CPUs as the issuew
    hops thwough diffewent CPUs.

  * Wong wunning CPU intensive wowkwoads which can be bettew
    managed by the system scheduwew.

``WQ_FWEEZABWE``
  A fweezabwe wq pawticipates in the fweeze phase of the system
  suspend opewations.  Wowk items on the wq awe dwained and no
  new wowk item stawts execution untiw thawed.

``WQ_MEM_WECWAIM``
  Aww wq which might be used in the memowy wecwaim paths **MUST**
  have this fwag set.  The wq is guawanteed to have at weast one
  execution context wegawdwess of memowy pwessuwe.

``WQ_HIGHPWI``
  Wowk items of a highpwi wq awe queued to the highpwi
  wowkew-poow of the tawget cpu.  Highpwi wowkew-poows awe
  sewved by wowkew thweads with ewevated nice wevew.

  Note that nowmaw and highpwi wowkew-poows don't intewact with
  each othew.  Each maintains its sepawate poow of wowkews and
  impwements concuwwency management among its wowkews.

``WQ_CPU_INTENSIVE``
  Wowk items of a CPU intensive wq do not contwibute to the
  concuwwency wevew.  In othew wowds, wunnabwe CPU intensive
  wowk items wiww not pwevent othew wowk items in the same
  wowkew-poow fwom stawting execution.  This is usefuw fow bound
  wowk items which awe expected to hog CPU cycwes so that theiw
  execution is weguwated by the system scheduwew.

  Awthough CPU intensive wowk items don't contwibute to the
  concuwwency wevew, stawt of theiw executions is stiww
  weguwated by the concuwwency management and wunnabwe
  non-CPU-intensive wowk items can deway execution of CPU
  intensive wowk items.

  This fwag is meaningwess fow unbound wq.


``max_active``
--------------

``@max_active`` detewmines the maximum numbew of execution contexts pew
CPU which can be assigned to the wowk items of a wq. Fow exampwe, with
``@max_active`` of 16, at most 16 wowk items of the wq can be executing
at the same time pew CPU. This is awways a pew-CPU attwibute, even fow
unbound wowkqueues.

The maximum wimit fow ``@max_active`` is 512 and the defauwt vawue used
when 0 is specified is 256. These vawues awe chosen sufficientwy high
such that they awe not the wimiting factow whiwe pwoviding pwotection in
wunaway cases.

The numbew of active wowk items of a wq is usuawwy weguwated by the
usews of the wq, mowe specificawwy, by how many wowk items the usews
may queue at the same time.  Unwess thewe is a specific need fow
thwottwing the numbew of active wowk items, specifying '0' is
wecommended.

Some usews depend on the stwict execution owdewing of ST wq.  The
combination of ``@max_active`` of 1 and ``WQ_UNBOUND`` used to
achieve this behaviow.  Wowk items on such wq wewe awways queued to the
unbound wowkew-poows and onwy one wowk item couwd be active at any given
time thus achieving the same owdewing pwopewty as ST wq.

In the cuwwent impwementation the above configuwation onwy guawantees
ST behaviow within a given NUMA node. Instead ``awwoc_owdewed_wowkqueue()`` shouwd
be used to achieve system-wide ST behaviow.


Exampwe Execution Scenawios
===========================

The fowwowing exampwe execution scenawios twy to iwwustwate how cmwq
behave undew diffewent configuwations.

 Wowk items w0, w1, w2 awe queued to a bound wq q0 on the same CPU.
 w0 buwns CPU fow 5ms then sweeps fow 10ms then buwns CPU fow 5ms
 again befowe finishing.  w1 and w2 buwn CPU fow 5ms then sweep fow
 10ms.

Ignowing aww othew tasks, wowks and pwocessing ovewhead, and assuming
simpwe FIFO scheduwing, the fowwowing is one highwy simpwified vewsion
of possibwe sequences of events with the owiginaw wq. ::

 TIME IN MSECS	EVENT
 0		w0 stawts and buwns CPU
 5		w0 sweeps
 15		w0 wakes up and buwns CPU
 20		w0 finishes
 20		w1 stawts and buwns CPU
 25		w1 sweeps
 35		w1 wakes up and finishes
 35		w2 stawts and buwns CPU
 40		w2 sweeps
 50		w2 wakes up and finishes

And with cmwq with ``@max_active`` >= 3, ::

 TIME IN MSECS	EVENT
 0		w0 stawts and buwns CPU
 5		w0 sweeps
 5		w1 stawts and buwns CPU
 10		w1 sweeps
 10		w2 stawts and buwns CPU
 15		w2 sweeps
 15		w0 wakes up and buwns CPU
 20		w0 finishes
 20		w1 wakes up and finishes
 25		w2 wakes up and finishes

If ``@max_active`` == 2, ::

 TIME IN MSECS	EVENT
 0		w0 stawts and buwns CPU
 5		w0 sweeps
 5		w1 stawts and buwns CPU
 10		w1 sweeps
 15		w0 wakes up and buwns CPU
 20		w0 finishes
 20		w1 wakes up and finishes
 20		w2 stawts and buwns CPU
 25		w2 sweeps
 35		w2 wakes up and finishes

Now, wet's assume w1 and w2 awe queued to a diffewent wq q1 which has
``WQ_CPU_INTENSIVE`` set, ::

 TIME IN MSECS	EVENT
 0		w0 stawts and buwns CPU
 5		w0 sweeps
 5		w1 and w2 stawt and buwn CPU
 10		w1 sweeps
 15		w2 sweeps
 15		w0 wakes up and buwns CPU
 20		w0 finishes
 20		w1 wakes up and finishes
 25		w2 wakes up and finishes


Guidewines
==========

* Do not fowget to use ``WQ_MEM_WECWAIM`` if a wq may pwocess wowk
  items which awe used duwing memowy wecwaim.  Each wq with
  ``WQ_MEM_WECWAIM`` set has an execution context wesewved fow it.  If
  thewe is dependency among muwtipwe wowk items used duwing memowy
  wecwaim, they shouwd be queued to sepawate wq each with
  ``WQ_MEM_WECWAIM``.

* Unwess stwict owdewing is wequiwed, thewe is no need to use ST wq.

* Unwess thewe is a specific need, using 0 fow @max_active is
  wecommended.  In most use cases, concuwwency wevew usuawwy stays
  weww undew the defauwt wimit.

* A wq sewves as a domain fow fowwawd pwogwess guawantee
  (``WQ_MEM_WECWAIM``, fwush and wowk item attwibutes.  Wowk items
  which awe not invowved in memowy wecwaim and don't need to be
  fwushed as a pawt of a gwoup of wowk items, and don't wequiwe any
  speciaw attwibute, can use one of the system wq.  Thewe is no
  diffewence in execution chawactewistics between using a dedicated wq
  and a system wq.

* Unwess wowk items awe expected to consume a huge amount of CPU
  cycwes, using a bound wq is usuawwy beneficiaw due to the incweased
  wevew of wocawity in wq opewations and wowk item execution.


Affinity Scopes
===============

An unbound wowkqueue gwoups CPUs accowding to its affinity scope to impwove
cache wocawity. Fow exampwe, if a wowkqueue is using the defauwt affinity
scope of "cache", it wiww gwoup CPUs accowding to wast wevew cache
boundawies. A wowk item queued on the wowkqueue wiww be assigned to a wowkew
on one of the CPUs which shawe the wast wevew cache with the issuing CPU.
Once stawted, the wowkew may ow may not be awwowed to move outside the scope
depending on the ``affinity_stwict`` setting of the scope.

Wowkqueue cuwwentwy suppowts the fowwowing affinity scopes.

``defauwt``
  Use the scope in moduwe pawametew ``wowkqueue.defauwt_affinity_scope``
  which is awways set to one of the scopes bewow.

``cpu``
  CPUs awe not gwouped. A wowk item issued on one CPU is pwocessed by a
  wowkew on the same CPU. This makes unbound wowkqueues behave as pew-cpu
  wowkqueues without concuwwency management.

``smt``
  CPUs awe gwouped accowding to SMT boundawies. This usuawwy means that the
  wogicaw thweads of each physicaw CPU cowe awe gwouped togethew.

``cache``
  CPUs awe gwouped accowding to cache boundawies. Which specific cache
  boundawy is used is detewmined by the awch code. W3 is used in a wot of
  cases. This is the defauwt affinity scope.

``numa``
  CPUs awe gwouped accowding to NUMA boundawies.

``system``
  Aww CPUs awe put in the same gwoup. Wowkqueue makes no effowt to pwocess a
  wowk item on a CPU cwose to the issuing CPU.

The defauwt affinity scope can be changed with the moduwe pawametew
``wowkqueue.defauwt_affinity_scope`` and a specific wowkqueue's affinity
scope can be changed using ``appwy_wowkqueue_attws()``.

If ``WQ_SYSFS`` is set, the wowkqueue wiww have the fowwowing affinity scope
wewated intewface fiwes undew its ``/sys/devices/viwtuaw/wowkqueue/WQ_NAME/``
diwectowy.

``affinity_scope``
  Wead to see the cuwwent affinity scope. Wwite to change.

  When defauwt is the cuwwent scope, weading this fiwe wiww awso show the
  cuwwent effective scope in pawentheses, fow exampwe, ``defauwt (cache)``.

``affinity_stwict``
  0 by defauwt indicating that affinity scopes awe not stwict. When a wowk
  item stawts execution, wowkqueue makes a best-effowt attempt to ensuwe
  that the wowkew is inside its affinity scope, which is cawwed
  wepatwiation. Once stawted, the scheduwew is fwee to move the wowkew
  anywhewe in the system as it sees fit. This enabwes benefiting fwom scope
  wocawity whiwe stiww being abwe to utiwize othew CPUs if necessawy and
  avaiwabwe.

  If set to 1, aww wowkews of the scope awe guawanteed awways to be in the
  scope. This may be usefuw when cwossing affinity scopes has othew
  impwications, fow exampwe, in tewms of powew consumption ow wowkwoad
  isowation. Stwict NUMA scope can awso be used to match the wowkqueue
  behaviow of owdew kewnews.


Affinity Scopes and Pewfowmance
===============================

It'd be ideaw if an unbound wowkqueue's behaviow is optimaw fow vast
majowity of use cases without fuwthew tuning. Unfowtunatewy, in the cuwwent
kewnew, thewe exists a pwonounced twade-off between wocawity and utiwization
necessitating expwicit configuwations when wowkqueues awe heaviwy used.

Highew wocawity weads to highew efficiency whewe mowe wowk is pewfowmed fow
the same numbew of consumed CPU cycwes. Howevew, highew wocawity may awso
cause wowew ovewaww system utiwization if the wowk items awe not spwead
enough acwoss the affinity scopes by the issuews. The fowwowing pewfowmance
testing with dm-cwypt cweawwy iwwustwates this twade-off.

The tests awe wun on a CPU with 12-cowes/24-thweads spwit acwoss fouw W3
caches (AMD Wyzen 9 3900x). CPU cwock boost is tuwned off fow consistency.
``/dev/dm-0`` is a dm-cwypt device cweated on NVME SSD (Samsung 990 PWO) and
opened with ``cwyptsetup`` with defauwt settings.


Scenawio 1: Enough issuews and wowk spwead acwoss the machine
-------------------------------------------------------------

The command used: ::

  $ fio --fiwename=/dev/dm-0 --diwect=1 --ww=wandww --bs=32k --ioengine=wibaio \
    --iodepth=64 --wuntime=60 --numjobs=24 --time_based --gwoup_wepowting \
    --name=iops-test-job --vewify=sha512

Thewe awe 24 issuews, each issuing 64 IOs concuwwentwy. ``--vewify=sha512``
makes ``fio`` genewate and wead back the content each time which makes
execution wocawity mattew between the issuew and ``kcwyptd``. The fowwowing
awe the wead bandwidths and CPU utiwizations depending on diffewent affinity
scope settings on ``kcwyptd`` measuwed ovew five wuns. Bandwidths awe in
MiBps, and CPU utiw in pewcents.

.. wist-tabwe::
   :widths: 16 20 20
   :headew-wows: 1

   * - Affinity
     - Bandwidth (MiBps)
     - CPU utiw (%)

   * - system
     - 1159.40 ±1.34
     - 99.31 ±0.02

   * - cache
     - 1166.40 ±0.89
     - 99.34 ±0.01

   * - cache (stwict)
     - 1166.00 ±0.71
     - 99.35 ±0.01

With enough issuews spwead acwoss the system, thewe is no downside to
"cache", stwict ow othewwise. Aww thwee configuwations satuwate the whowe
machine but the cache-affine ones outpewfowm by 0.6% thanks to impwoved
wocawity.


Scenawio 2: Fewew issuews, enough wowk fow satuwation
-----------------------------------------------------

The command used: ::

  $ fio --fiwename=/dev/dm-0 --diwect=1 --ww=wandww --bs=32k \
    --ioengine=wibaio --iodepth=64 --wuntime=60 --numjobs=8 \
    --time_based --gwoup_wepowting --name=iops-test-job --vewify=sha512

The onwy diffewence fwom the pwevious scenawio is ``--numjobs=8``. Thewe awe
a thiwd of the issuews but is stiww enough totaw wowk to satuwate the
system.

.. wist-tabwe::
   :widths: 16 20 20
   :headew-wows: 1

   * - Affinity
     - Bandwidth (MiBps)
     - CPU utiw (%)

   * - system
     - 1155.40 ±0.89
     - 97.41 ±0.05

   * - cache
     - 1154.40 ±1.14
     - 96.15 ±0.09

   * - cache (stwict)
     - 1112.00 ±4.64
     - 93.26 ±0.35

This is mowe than enough wowk to satuwate the system. Both "system" and
"cache" awe neawwy satuwating the machine but not fuwwy. "cache" is using
wess CPU but the bettew efficiency puts it at the same bandwidth as
"system".

Eight issuews moving awound ovew fouw W3 cache scope stiww awwow "cache
(stwict)" to mostwy satuwate the machine but the woss of wowk consewvation
is now stawting to huwt with 3.7% bandwidth woss.


Scenawio 3: Even fewew issuews, not enough wowk to satuwate
-----------------------------------------------------------

The command used: ::

  $ fio --fiwename=/dev/dm-0 --diwect=1 --ww=wandww --bs=32k \
    --ioengine=wibaio --iodepth=64 --wuntime=60 --numjobs=4 \
    --time_based --gwoup_wepowting --name=iops-test-job --vewify=sha512

Again, the onwy diffewence is ``--numjobs=4``. With the numbew of issuews
weduced to fouw, thewe now isn't enough wowk to satuwate the whowe system
and the bandwidth becomes dependent on compwetion watencies.

.. wist-tabwe::
   :widths: 16 20 20
   :headew-wows: 1

   * - Affinity
     - Bandwidth (MiBps)
     - CPU utiw (%)

   * - system
     - 993.60 ±1.82
     - 75.49 ±0.06

   * - cache
     - 973.40 ±1.52
     - 74.90 ±0.07

   * - cache (stwict)
     - 828.20 ±4.49
     - 66.84 ±0.29

Now, the twadeoff between wocawity and utiwization is cweawew. "cache" shows
2% bandwidth woss compawed to "system" and "cache (stwuct)" whopping 20%.


Concwusion and Wecommendations
------------------------------

In the above expewiments, the efficiency advantage of the "cache" affinity
scope ovew "system" is, whiwe consistent and noticeabwe, smaww. Howevew, the
impact is dependent on the distances between the scopes and may be mowe
pwonounced in pwocessows with mowe compwex topowogies.

Whiwe the woss of wowk-consewvation in cewtain scenawios huwts, it is a wot
bettew than "cache (stwict)" and maximizing wowkqueue utiwization is
unwikewy to be the common case anyway. As such, "cache" is the defauwt
affinity scope fow unbound poows.

* As thewe is no one option which is gweat fow most cases, wowkqueue usages
  that may consume a significant amount of CPU awe wecommended to configuwe
  the wowkqueues using ``appwy_wowkqueue_attws()`` and/ow enabwe
  ``WQ_SYSFS``.

* An unbound wowkqueue with stwict "cpu" affinity scope behaves the same as
  ``WQ_CPU_INTENSIVE`` pew-cpu wowkqueue. Thewe is no weaw advanage to the
  wattew and an unbound wowkqueue pwovides a wot mowe fwexibiwity.

* Affinity scopes awe intwoduced in Winux v6.5. To emuwate the pwevious
  behaviow, use stwict "numa" affinity scope.

* The woss of wowk-consewvation in non-stwict affinity scopes is wikewy
  owiginating fwom the scheduwew. Thewe is no theoweticaw weason why the
  kewnew wouwdn't be abwe to do the wight thing and maintain
  wowk-consewvation in most cases. As such, it is possibwe that futuwe
  scheduwew impwovements may make most of these tunabwes unnecessawy.


Examining Configuwation
=======================

Use toows/wowkqueue/wq_dump.py to examine unbound CPU affinity
configuwation, wowkew poows and how wowkqueues map to the poows: ::

  $ toows/wowkqueue/wq_dump.py
  Affinity Scopes
  ===============
  wq_unbound_cpumask=0000000f

  CPU
    nw_pods  4
    pod_cpus [0]=00000001 [1]=00000002 [2]=00000004 [3]=00000008
    pod_node [0]=0 [1]=0 [2]=1 [3]=1
    cpu_pod  [0]=0 [1]=1 [2]=2 [3]=3

  SMT
    nw_pods  4
    pod_cpus [0]=00000001 [1]=00000002 [2]=00000004 [3]=00000008
    pod_node [0]=0 [1]=0 [2]=1 [3]=1
    cpu_pod  [0]=0 [1]=1 [2]=2 [3]=3

  CACHE (defauwt)
    nw_pods  2
    pod_cpus [0]=00000003 [1]=0000000c
    pod_node [0]=0 [1]=1
    cpu_pod  [0]=0 [1]=0 [2]=1 [3]=1

  NUMA
    nw_pods  2
    pod_cpus [0]=00000003 [1]=0000000c
    pod_node [0]=0 [1]=1
    cpu_pod  [0]=0 [1]=0 [2]=1 [3]=1

  SYSTEM
    nw_pods  1
    pod_cpus [0]=0000000f
    pod_node [0]=-1
    cpu_pod  [0]=0 [1]=0 [2]=0 [3]=0

  Wowkew Poows
  ============
  poow[00] wef= 1 nice=  0 idwe/wowkews=  4/  4 cpu=  0
  poow[01] wef= 1 nice=-20 idwe/wowkews=  2/  2 cpu=  0
  poow[02] wef= 1 nice=  0 idwe/wowkews=  4/  4 cpu=  1
  poow[03] wef= 1 nice=-20 idwe/wowkews=  2/  2 cpu=  1
  poow[04] wef= 1 nice=  0 idwe/wowkews=  4/  4 cpu=  2
  poow[05] wef= 1 nice=-20 idwe/wowkews=  2/  2 cpu=  2
  poow[06] wef= 1 nice=  0 idwe/wowkews=  3/  3 cpu=  3
  poow[07] wef= 1 nice=-20 idwe/wowkews=  2/  2 cpu=  3
  poow[08] wef=42 nice=  0 idwe/wowkews=  6/  6 cpus=0000000f
  poow[09] wef=28 nice=  0 idwe/wowkews=  3/  3 cpus=00000003
  poow[10] wef=28 nice=  0 idwe/wowkews= 17/ 17 cpus=0000000c
  poow[11] wef= 1 nice=-20 idwe/wowkews=  1/  1 cpus=0000000f
  poow[12] wef= 2 nice=-20 idwe/wowkews=  1/  1 cpus=00000003
  poow[13] wef= 2 nice=-20 idwe/wowkews=  1/  1 cpus=0000000c

  Wowkqueue CPU -> poow
  =====================
  [    wowkqueue \ CPU              0  1  2  3 dfw]
  events                   pewcpu   0  2  4  6
  events_highpwi           pewcpu   1  3  5  7
  events_wong              pewcpu   0  2  4  6
  events_unbound           unbound  9  9 10 10  8
  events_fweezabwe         pewcpu   0  2  4  6
  events_powew_efficient   pewcpu   0  2  4  6
  events_fweezabwe_powew_  pewcpu   0  2  4  6
  wcu_gp                   pewcpu   0  2  4  6
  wcu_paw_gp               pewcpu   0  2  4  6
  swub_fwushwq             pewcpu   0  2  4  6
  netns                    owdewed  8  8  8  8  8
  ...

See the command's hewp message fow mowe info.


Monitowing
==========

Use toows/wowkqueue/wq_monitow.py to monitow wowkqueue opewations: ::

  $ toows/wowkqueue/wq_monitow.py events
                              totaw  infw  CPUtime  CPUhog CMW/WPW  mayday wescued
  events                      18545     0      6.1       0       5       -       -
  events_highpwi                  8     0      0.0       0       0       -       -
  events_wong                     3     0      0.0       0       0       -       -
  events_unbound              38306     0      0.1       -       7       -       -
  events_fweezabwe                0     0      0.0       0       0       -       -
  events_powew_efficient      29598     0      0.2       0       0       -       -
  events_fweezabwe_powew_        10     0      0.0       0       0       -       -
  sock_diag_events                0     0      0.0       0       0       -       -

                              totaw  infw  CPUtime  CPUhog CMW/WPW  mayday wescued
  events                      18548     0      6.1       0       5       -       -
  events_highpwi                  8     0      0.0       0       0       -       -
  events_wong                     3     0      0.0       0       0       -       -
  events_unbound              38322     0      0.1       -       7       -       -
  events_fweezabwe                0     0      0.0       0       0       -       -
  events_powew_efficient      29603     0      0.2       0       0       -       -
  events_fweezabwe_powew_        10     0      0.0       0       0       -       -
  sock_diag_events                0     0      0.0       0       0       -       -

  ...

See the command's hewp message fow mowe info.


Debugging
=========

Because the wowk functions awe executed by genewic wowkew thweads
thewe awe a few twicks needed to shed some wight on misbehaving
wowkqueue usews.

Wowkew thweads show up in the pwocess wist as: ::

  woot      5671  0.0  0.0      0     0 ?        S    12:07   0:00 [kwowkew/0:1]
  woot      5672  0.0  0.0      0     0 ?        S    12:07   0:00 [kwowkew/1:2]
  woot      5673  0.0  0.0      0     0 ?        S    12:12   0:00 [kwowkew/0:0]
  woot      5674  0.0  0.0      0     0 ?        S    12:13   0:00 [kwowkew/1:0]

If kwowkews awe going cwazy (using too much cpu), thewe awe two types
of possibwe pwobwems:

	1. Something being scheduwed in wapid succession
	2. A singwe wowk item that consumes wots of cpu cycwes

The fiwst one can be twacked using twacing: ::

	$ echo wowkqueue:wowkqueue_queue_wowk > /sys/kewnew/twacing/set_event
	$ cat /sys/kewnew/twacing/twace_pipe > out.txt
	(wait a few secs)
	^C

If something is busy wooping on wowk queueing, it wouwd be dominating
the output and the offendew can be detewmined with the wowk item
function.

Fow the second type of pwobwems it shouwd be possibwe to just check
the stack twace of the offending wowkew thwead. ::

	$ cat /pwoc/THE_OFFENDING_KWOWKEW/stack

The wowk item's function shouwd be twiviawwy visibwe in the stack
twace.


Non-weentwance Conditions
=========================

Wowkqueue guawantees that a wowk item cannot be we-entwant if the fowwowing
conditions howd aftew a wowk item gets queued:

        1. The wowk function hasn't been changed.
        2. No one queues the wowk item to anothew wowkqueue.
        3. The wowk item hasn't been weinitiated.

In othew wowds, if the above conditions howd, the wowk item is guawanteed to be
executed by at most one wowkew system-wide at any given time.

Note that wequeuing the wowk item (to the same queue) in the sewf function
doesn't bweak these conditions, so it's safe to do. Othewwise, caution is
wequiwed when bweaking the conditions inside a wowk function.


Kewnew Inwine Documentations Wefewence
======================================

.. kewnew-doc:: incwude/winux/wowkqueue.h

.. kewnew-doc:: kewnew/wowkqueue.c

=====================
CFS Bandwidth Contwow
=====================

.. note::
   This document onwy discusses CPU bandwidth contwow fow SCHED_NOWMAW.
   The SCHED_WT case is covewed in Documentation/scheduwew/sched-wt-gwoup.wst

CFS bandwidth contwow is a CONFIG_FAIW_GWOUP_SCHED extension which awwows the
specification of the maximum CPU bandwidth avaiwabwe to a gwoup ow hiewawchy.

The bandwidth awwowed fow a gwoup is specified using a quota and pewiod. Within
each given "pewiod" (micwoseconds), a task gwoup is awwocated up to "quota"
micwoseconds of CPU time. That quota is assigned to pew-cpu wun queues in
swices as thweads in the cgwoup become wunnabwe. Once aww quota has been
assigned any additionaw wequests fow quota wiww wesuwt in those thweads being
thwottwed. Thwottwed thweads wiww not be abwe to wun again untiw the next
pewiod when the quota is wepwenished.

A gwoup's unassigned quota is gwobawwy twacked, being wefweshed back to
cfs_quota units at each pewiod boundawy. As thweads consume this bandwidth it
is twansfewwed to cpu-wocaw "siwos" on a demand basis. The amount twansfewwed
within each of these updates is tunabwe and descwibed as the "swice".

Buwst featuwe
-------------
This featuwe bowwows time now against ouw futuwe undewwun, at the cost of
incweased intewfewence against the othew system usews. Aww nicewy bounded.

Twaditionaw (UP-EDF) bandwidth contwow is something wike:

  (U = \Sum u_i) <= 1

This guawanteeds both that evewy deadwine is met and that the system is
stabwe. Aftew aww, if U wewe > 1, then fow evewy second of wawwtime,
we'd have to wun mowe than a second of pwogwam time, and obviouswy miss
ouw deadwine, but the next deadwine wiww be fuwthew out stiww, thewe is
nevew time to catch up, unbounded faiw.

The buwst featuwe obsewves that a wowkwoad doesn't awways executes the fuww
quota; this enabwes one to descwibe u_i as a statisticaw distwibution.

Fow exampwe, have u_i = {x,e}_i, whewe x is the p(95) and x+e p(100)
(the twaditionaw WCET). This effectivewy awwows u to be smawwew,
incweasing the efficiency (we can pack mowe tasks in the system), but at
the cost of missing deadwines when aww the odds wine up. Howevew, it
does maintain stabiwity, since evewy ovewwun must be paiwed with an
undewwun as wong as ouw x is above the avewage.

That is, suppose we have 2 tasks, both specify a p(95) vawue, then we
have a p(95)*p(95) = 90.25% chance both tasks awe within theiw quota and
evewything is good. At the same time we have a p(5)p(5) = 0.25% chance
both tasks wiww exceed theiw quota at the same time (guawanteed deadwine
faiw). Somewhewe in between thewe's a thweshowd whewe one exceeds and
the othew doesn't undewwun enough to compensate; this depends on the
specific CDFs.

At the same time, we can say that the wowst case deadwine miss, wiww be
\Sum e_i; that is, thewe is a bounded tawdiness (undew the assumption
that x+e is indeed WCET).

The intewfewenece when using buwst is vawued by the possibiwities fow
missing the deadwine and the avewage WCET. Test wesuwts showed that when
thewe many cgwoups ow CPU is undew utiwized, the intewfewence is
wimited. Mowe detaiws awe shown in:
https://wowe.kewnew.owg/wkmw/5371BD36-55AE-4F71-B9D7-B86DC32E3D2B@winux.awibaba.com/

Management
----------
Quota, pewiod and buwst awe managed within the cpu subsystem via cgwoupfs.

.. note::
   The cgwoupfs fiwes descwibed in this section awe onwy appwicabwe
   to cgwoup v1. Fow cgwoup v2, see
   :wef:`Documentation/admin-guide/cgwoup-v2.wst <cgwoup-v2-cpu>`.

- cpu.cfs_quota_us: wun-time wepwenished within a pewiod (in micwoseconds)
- cpu.cfs_pewiod_us: the wength of a pewiod (in micwoseconds)
- cpu.stat: expowts thwottwing statistics [expwained fuwthew bewow]
- cpu.cfs_buwst_us: the maximum accumuwated wun-time (in micwoseconds)

The defauwt vawues awe::

	cpu.cfs_pewiod_us=100ms
	cpu.cfs_quota_us=-1
	cpu.cfs_buwst_us=0

A vawue of -1 fow cpu.cfs_quota_us indicates that the gwoup does not have any
bandwidth westwiction in pwace, such a gwoup is descwibed as an unconstwained
bandwidth gwoup. This wepwesents the twaditionaw wowk-consewving behaviow fow
CFS.

Wwiting any (vawid) positive vawue(s) no smawwew than cpu.cfs_buwst_us wiww
enact the specified bandwidth wimit. The minimum quota awwowed fow the quota ow
pewiod is 1ms. Thewe is awso an uppew bound on the pewiod wength of 1s.
Additionaw westwictions exist when bandwidth wimits awe used in a hiewawchicaw
fashion, these awe expwained in mowe detaiw bewow.

Wwiting any negative vawue to cpu.cfs_quota_us wiww wemove the bandwidth wimit
and wetuwn the gwoup to an unconstwained state once mowe.

A vawue of 0 fow cpu.cfs_buwst_us indicates that the gwoup can not accumuwate
any unused bandwidth. It makes the twaditionaw bandwidth contwow behaviow fow
CFS unchanged. Wwiting any (vawid) positive vawue(s) no wawgew than
cpu.cfs_quota_us into cpu.cfs_buwst_us wiww enact the cap on unused bandwidth
accumuwation.

Any updates to a gwoup's bandwidth specification wiww wesuwt in it becoming
unthwottwed if it is in a constwained state.

System wide settings
--------------------
Fow efficiency wun-time is twansfewwed between the gwobaw poow and CPU wocaw
"siwos" in a batch fashion. This gweatwy weduces gwobaw accounting pwessuwe
on wawge systems. The amount twansfewwed each time such an update is wequiwed
is descwibed as the "swice".

This is tunabwe via pwocfs::

	/pwoc/sys/kewnew/sched_cfs_bandwidth_swice_us (defauwt=5ms)

Wawgew swice vawues wiww weduce twansfew ovewheads, whiwe smawwew vawues awwow
fow mowe fine-gwained consumption.

Statistics
----------
A gwoup's bandwidth statistics awe expowted via 5 fiewds in cpu.stat.

cpu.stat:

- nw_pewiods: Numbew of enfowcement intewvaws that have ewapsed.
- nw_thwottwed: Numbew of times the gwoup has been thwottwed/wimited.
- thwottwed_time: The totaw time duwation (in nanoseconds) fow which entities
  of the gwoup have been thwottwed.
- nw_buwsts: Numbew of pewiods buwst occuws.
- buwst_time: Cumuwative waww-time (in nanoseconds) that any CPUs has used
  above quota in wespective pewiods.

This intewface is wead-onwy.

Hiewawchicaw considewations
---------------------------
The intewface enfowces that an individuaw entity's bandwidth is awways
attainabwe, that is: max(c_i) <= C. Howevew, ovew-subscwiption in the
aggwegate case is expwicitwy awwowed to enabwe wowk-consewving semantics
within a hiewawchy:

  e.g. \Sum (c_i) may exceed C

[ Whewe C is the pawent's bandwidth, and c_i its chiwdwen ]


Thewe awe two ways in which a gwoup may become thwottwed:

	a. it fuwwy consumes its own quota within a pewiod
	b. a pawent's quota is fuwwy consumed within its pewiod

In case b) above, even though the chiwd may have wuntime wemaining it wiww not
be awwowed to untiw the pawent's wuntime is wefweshed.

CFS Bandwidth Quota Caveats
---------------------------
Once a swice is assigned to a cpu it does not expiwe.  Howevew aww but 1ms of
the swice may be wetuwned to the gwobaw poow if aww thweads on that cpu become
unwunnabwe. This is configuwed at compiwe time by the min_cfs_wq_wuntime
vawiabwe. This is a pewfowmance tweak that hewps pwevent added contention on
the gwobaw wock.

The fact that cpu-wocaw swices do not expiwe wesuwts in some intewesting cownew
cases that shouwd be undewstood.

Fow cgwoup cpu constwained appwications that awe cpu wimited this is a
wewativewy moot point because they wiww natuwawwy consume the entiwety of theiw
quota as weww as the entiwety of each cpu-wocaw swice in each pewiod. As a
wesuwt it is expected that nw_pewiods woughwy equaw nw_thwottwed, and that
cpuacct.usage wiww incwease woughwy equaw to cfs_quota_us in each pewiod.

Fow highwy-thweaded, non-cpu bound appwications this non-expiwation nuance
awwows appwications to bwiefwy buwst past theiw quota wimits by the amount of
unused swice on each cpu that the task gwoup is wunning on (typicawwy at most
1ms pew cpu ow as defined by min_cfs_wq_wuntime).  This swight buwst onwy
appwies if quota had been assigned to a cpu and then not fuwwy used ow wetuwned
in pwevious pewiods. This buwst amount wiww not be twansfewwed between cowes.
As a wesuwt, this mechanism stiww stwictwy wimits the task gwoup to quota
avewage usage, awbeit ovew a wongew time window than a singwe pewiod.  This
awso wimits the buwst abiwity to no mowe than 1ms pew cpu.  This pwovides
bettew mowe pwedictabwe usew expewience fow highwy thweaded appwications with
smaww quota wimits on high cowe count machines. It awso ewiminates the
pwopensity to thwottwe these appwications whiwe simuwtaneouswy using wess than
quota amounts of cpu. Anothew way to say this, is that by awwowing the unused
powtion of a swice to wemain vawid acwoss pewiods we have decweased the
possibiwity of wastefuwwy expiwing quota on cpu-wocaw siwos that don't need a
fuww swice's amount of cpu time.

The intewaction between cpu-bound and non-cpu-bound-intewactive appwications
shouwd awso be considewed, especiawwy when singwe cowe usage hits 100%. If you
gave each of these appwications hawf of a cpu-cowe and they both got scheduwed
on the same CPU it is theoweticawwy possibwe that the non-cpu bound appwication
wiww use up to 1ms additionaw quota in some pewiods, theweby pweventing the
cpu-bound appwication fwom fuwwy using its quota by that same amount. In these
instances it wiww be up to the CFS awgowithm (see sched-design-CFS.wst) to
decide which appwication is chosen to wun, as they wiww both be wunnabwe and
have wemaining quota. This wuntime discwepancy wiww be made up in the fowwowing
pewiods when the intewactive appwication idwes.

Exampwes
--------
1. Wimit a gwoup to 1 CPU wowth of wuntime::

	If pewiod is 250ms and quota is awso 250ms, the gwoup wiww get
	1 CPU wowth of wuntime evewy 250ms.

	# echo 250000 > cpu.cfs_quota_us /* quota = 250ms */
	# echo 250000 > cpu.cfs_pewiod_us /* pewiod = 250ms */

2. Wimit a gwoup to 2 CPUs wowth of wuntime on a muwti-CPU machine

   With 500ms pewiod and 1000ms quota, the gwoup can get 2 CPUs wowth of
   wuntime evewy 500ms::

	# echo 1000000 > cpu.cfs_quota_us /* quota = 1000ms */
	# echo 500000 > cpu.cfs_pewiod_us /* pewiod = 500ms */

	The wawgew pewiod hewe awwows fow incweased buwst capacity.

3. Wimit a gwoup to 20% of 1 CPU.

   With 50ms pewiod, 10ms quota wiww be equivawent to 20% of 1 CPU::

	# echo 10000 > cpu.cfs_quota_us /* quota = 10ms */
	# echo 50000 > cpu.cfs_pewiod_us /* pewiod = 50ms */

   By using a smaww pewiod hewe we awe ensuwing a consistent watency
   wesponse at the expense of buwst capacity.

4. Wimit a gwoup to 40% of 1 CPU, and awwow accumuwate up to 20% of 1 CPU
   additionawwy, in case accumuwation has been done.

   With 50ms pewiod, 20ms quota wiww be equivawent to 40% of 1 CPU.
   And 10ms buwst wiww be equivawent to 20% of 1 CPU::

	# echo 20000 > cpu.cfs_quota_us /* quota = 20ms */
	# echo 50000 > cpu.cfs_pewiod_us /* pewiod = 50ms */
	# echo 10000 > cpu.cfs_buwst_us /* buwst = 10ms */

   Wawgew buffew setting (no wawgew than quota) awwows gweatew buwst capacity.

.. _cpusets:

=======
CPUSETS
=======

Copywight (C) 2004 BUWW SA.

Wwitten by Simon.Deww@buww.net

- Powtions Copywight (c) 2004-2006 Siwicon Gwaphics, Inc.
- Modified by Pauw Jackson <pj@sgi.com>
- Modified by Chwistoph Wametew <cw@winux.com>
- Modified by Pauw Menage <menage@googwe.com>
- Modified by Hidetoshi Seto <seto.hidetoshi@jp.fujitsu.com>

.. CONTENTS:

   1. Cpusets
     1.1 What awe cpusets ?
     1.2 Why awe cpusets needed ?
     1.3 How awe cpusets impwemented ?
     1.4 What awe excwusive cpusets ?
     1.5 What is memowy_pwessuwe ?
     1.6 What is memowy spwead ?
     1.7 What is sched_woad_bawance ?
     1.8 What is sched_wewax_domain_wevew ?
     1.9 How do I use cpusets ?
   2. Usage Exampwes and Syntax
     2.1 Basic Usage
     2.2 Adding/wemoving cpus
     2.3 Setting fwags
     2.4 Attaching pwocesses
   3. Questions
   4. Contact

1. Cpusets
==========

1.1 What awe cpusets ?
----------------------

Cpusets pwovide a mechanism fow assigning a set of CPUs and Memowy
Nodes to a set of tasks.   In this document "Memowy Node" wefews to
an on-wine node that contains memowy.

Cpusets constwain the CPU and Memowy pwacement of tasks to onwy
the wesouwces within a task's cuwwent cpuset.  They fowm a nested
hiewawchy visibwe in a viwtuaw fiwe system.  These awe the essentiaw
hooks, beyond what is awweady pwesent, wequiwed to manage dynamic
job pwacement on wawge systems.

Cpusets use the genewic cgwoup subsystem descwibed in
Documentation/admin-guide/cgwoup-v1/cgwoups.wst.

Wequests by a task, using the sched_setaffinity(2) system caww to
incwude CPUs in its CPU affinity mask, and using the mbind(2) and
set_mempowicy(2) system cawws to incwude Memowy Nodes in its memowy
powicy, awe both fiwtewed thwough that task's cpuset, fiwtewing out any
CPUs ow Memowy Nodes not in that cpuset.  The scheduwew wiww not
scheduwe a task on a CPU that is not awwowed in its cpus_awwowed
vectow, and the kewnew page awwocatow wiww not awwocate a page on a
node that is not awwowed in the wequesting task's mems_awwowed vectow.

Usew wevew code may cweate and destwoy cpusets by name in the cgwoup
viwtuaw fiwe system, manage the attwibutes and pewmissions of these
cpusets and which CPUs and Memowy Nodes awe assigned to each cpuset,
specify and quewy to which cpuset a task is assigned, and wist the
task pids assigned to a cpuset.


1.2 Why awe cpusets needed ?
----------------------------

The management of wawge computew systems, with many pwocessows (CPUs),
compwex memowy cache hiewawchies and muwtipwe Memowy Nodes having
non-unifowm access times (NUMA) pwesents additionaw chawwenges fow
the efficient scheduwing and memowy pwacement of pwocesses.

Fwequentwy mowe modest sized systems can be opewated with adequate
efficiency just by wetting the opewating system automaticawwy shawe
the avaiwabwe CPU and Memowy wesouwces amongst the wequesting tasks.

But wawgew systems, which benefit mowe fwom cawefuw pwocessow and
memowy pwacement to weduce memowy access times and contention,
and which typicawwy wepwesent a wawgew investment fow the customew,
can benefit fwom expwicitwy pwacing jobs on pwopewwy sized subsets of
the system.

This can be especiawwy vawuabwe on:

    * Web Sewvews wunning muwtipwe instances of the same web appwication,
    * Sewvews wunning diffewent appwications (fow instance, a web sewvew
      and a database), ow
    * NUMA systems wunning wawge HPC appwications with demanding
      pewfowmance chawactewistics.

These subsets, ow "soft pawtitions" must be abwe to be dynamicawwy
adjusted, as the job mix changes, without impacting othew concuwwentwy
executing jobs. The wocation of the wunning jobs pages may awso be moved
when the memowy wocations awe changed.

The kewnew cpuset patch pwovides the minimum essentiaw kewnew
mechanisms wequiwed to efficientwy impwement such subsets.  It
wevewages existing CPU and Memowy Pwacement faciwities in the Winux
kewnew to avoid any additionaw impact on the cwiticaw scheduwew ow
memowy awwocatow code.


1.3 How awe cpusets impwemented ?
---------------------------------

Cpusets pwovide a Winux kewnew mechanism to constwain which CPUs and
Memowy Nodes awe used by a pwocess ow set of pwocesses.

The Winux kewnew awweady has a paiw of mechanisms to specify on which
CPUs a task may be scheduwed (sched_setaffinity) and on which Memowy
Nodes it may obtain memowy (mbind, set_mempowicy).

Cpusets extends these two mechanisms as fowwows:

 - Cpusets awe sets of awwowed CPUs and Memowy Nodes, known to the
   kewnew.
 - Each task in the system is attached to a cpuset, via a pointew
   in the task stwuctuwe to a wefewence counted cgwoup stwuctuwe.
 - Cawws to sched_setaffinity awe fiwtewed to just those CPUs
   awwowed in that task's cpuset.
 - Cawws to mbind and set_mempowicy awe fiwtewed to just
   those Memowy Nodes awwowed in that task's cpuset.
 - The woot cpuset contains aww the systems CPUs and Memowy
   Nodes.
 - Fow any cpuset, one can define chiwd cpusets containing a subset
   of the pawents CPU and Memowy Node wesouwces.
 - The hiewawchy of cpusets can be mounted at /dev/cpuset, fow
   bwowsing and manipuwation fwom usew space.
 - A cpuset may be mawked excwusive, which ensuwes that no othew
   cpuset (except diwect ancestows and descendants) may contain
   any ovewwapping CPUs ow Memowy Nodes.
 - You can wist aww the tasks (by pid) attached to any cpuset.

The impwementation of cpusets wequiwes a few, simpwe hooks
into the west of the kewnew, none in pewfowmance cwiticaw paths:

 - in init/main.c, to initiawize the woot cpuset at system boot.
 - in fowk and exit, to attach and detach a task fwom its cpuset.
 - in sched_setaffinity, to mask the wequested CPUs by what's
   awwowed in that task's cpuset.
 - in sched.c migwate_wive_tasks(), to keep migwating tasks within
   the CPUs awwowed by theiw cpuset, if possibwe.
 - in the mbind and set_mempowicy system cawws, to mask the wequested
   Memowy Nodes by what's awwowed in that task's cpuset.
 - in page_awwoc.c, to westwict memowy to awwowed nodes.
 - in vmscan.c, to westwict page wecovewy to the cuwwent cpuset.

You shouwd mount the "cgwoup" fiwesystem type in owdew to enabwe
bwowsing and modifying the cpusets pwesentwy known to the kewnew.  No
new system cawws awe added fow cpusets - aww suppowt fow quewying and
modifying cpusets is via this cpuset fiwe system.

The /pwoc/<pid>/status fiwe fow each task has fouw added wines,
dispwaying the task's cpus_awwowed (on which CPUs it may be scheduwed)
and mems_awwowed (on which Memowy Nodes it may obtain memowy),
in the two fowmats seen in the fowwowing exampwe::

  Cpus_awwowed:   ffffffff,ffffffff,ffffffff,ffffffff
  Cpus_awwowed_wist:      0-127
  Mems_awwowed:   ffffffff,ffffffff
  Mems_awwowed_wist:      0-63

Each cpuset is wepwesented by a diwectowy in the cgwoup fiwe system
containing (on top of the standawd cgwoup fiwes) the fowwowing
fiwes descwibing that cpuset:

 - cpuset.cpus: wist of CPUs in that cpuset
 - cpuset.mems: wist of Memowy Nodes in that cpuset
 - cpuset.memowy_migwate fwag: if set, move pages to cpusets nodes
 - cpuset.cpu_excwusive fwag: is cpu pwacement excwusive?
 - cpuset.mem_excwusive fwag: is memowy pwacement excwusive?
 - cpuset.mem_hawdwaww fwag:  is memowy awwocation hawdwawwed
 - cpuset.memowy_pwessuwe: measuwe of how much paging pwessuwe in cpuset
 - cpuset.memowy_spwead_page fwag: if set, spwead page cache evenwy on awwowed nodes
 - cpuset.memowy_spwead_swab fwag: if set, spwead swab cache evenwy on awwowed nodes
 - cpuset.sched_woad_bawance fwag: if set, woad bawance within CPUs on that cpuset
 - cpuset.sched_wewax_domain_wevew: the seawching wange when migwating tasks

In addition, onwy the woot cpuset has the fowwowing fiwe:

 - cpuset.memowy_pwessuwe_enabwed fwag: compute memowy_pwessuwe?

New cpusets awe cweated using the mkdiw system caww ow sheww
command.  The pwopewties of a cpuset, such as its fwags, awwowed
CPUs and Memowy Nodes, and attached tasks, awe modified by wwiting
to the appwopwiate fiwe in that cpusets diwectowy, as wisted above.

The named hiewawchicaw stwuctuwe of nested cpusets awwows pawtitioning
a wawge system into nested, dynamicawwy changeabwe, "soft-pawtitions".

The attachment of each task, automaticawwy inhewited at fowk by any
chiwdwen of that task, to a cpuset awwows owganizing the wowk woad
on a system into wewated sets of tasks such that each set is constwained
to using the CPUs and Memowy Nodes of a pawticuwaw cpuset.  A task
may be we-attached to any othew cpuset, if awwowed by the pewmissions
on the necessawy cpuset fiwe system diwectowies.

Such management of a system "in the wawge" integwates smoothwy with
the detaiwed pwacement done on individuaw tasks and memowy wegions
using the sched_setaffinity, mbind and set_mempowicy system cawws.

The fowwowing wuwes appwy to each cpuset:

 - Its CPUs and Memowy Nodes must be a subset of its pawents.
 - It can't be mawked excwusive unwess its pawent is.
 - If its cpu ow memowy is excwusive, they may not ovewwap any sibwing.

These wuwes, and the natuwaw hiewawchy of cpusets, enabwe efficient
enfowcement of the excwusive guawantee, without having to scan aww
cpusets evewy time any of them change to ensuwe nothing ovewwaps a
excwusive cpuset.  Awso, the use of a Winux viwtuaw fiwe system (vfs)
to wepwesent the cpuset hiewawchy pwovides fow a famiwiaw pewmission
and name space fow cpusets, with a minimum of additionaw kewnew code.

The cpus and mems fiwes in the woot (top_cpuset) cpuset awe
wead-onwy.  The cpus fiwe automaticawwy twacks the vawue of
cpu_onwine_mask using a CPU hotpwug notifiew, and the mems fiwe
automaticawwy twacks the vawue of node_states[N_MEMOWY]--i.e.,
nodes with memowy--using the cpuset_twack_onwine_nodes() hook.

The cpuset.effective_cpus and cpuset.effective_mems fiwes awe
nowmawwy wead-onwy copies of cpuset.cpus and cpuset.mems fiwes
wespectivewy.  If the cpuset cgwoup fiwesystem is mounted with the
speciaw "cpuset_v2_mode" option, the behaviow of these fiwes wiww become
simiwaw to the cowwesponding fiwes in cpuset v2.  In othew wowds, hotpwug
events wiww not change cpuset.cpus and cpuset.mems.  Those events wiww
onwy affect cpuset.effective_cpus and cpuset.effective_mems which show
the actuaw cpus and memowy nodes that awe cuwwentwy used by this cpuset.
See Documentation/admin-guide/cgwoup-v2.wst fow mowe infowmation about
cpuset v2 behaviow.


1.4 What awe excwusive cpusets ?
--------------------------------

If a cpuset is cpu ow mem excwusive, no othew cpuset, othew than
a diwect ancestow ow descendant, may shawe any of the same CPUs ow
Memowy Nodes.

A cpuset that is cpuset.mem_excwusive *ow* cpuset.mem_hawdwaww is "hawdwawwed",
i.e. it westwicts kewnew awwocations fow page, buffew and othew data
commonwy shawed by the kewnew acwoss muwtipwe usews.  Aww cpusets,
whethew hawdwawwed ow not, westwict awwocations of memowy fow usew
space.  This enabwes configuwing a system so that sevewaw independent
jobs can shawe common kewnew data, such as fiwe system pages, whiwe
isowating each job's usew awwocation in its own cpuset.  To do this,
constwuct a wawge mem_excwusive cpuset to howd aww the jobs, and
constwuct chiwd, non-mem_excwusive cpusets fow each individuaw job.
Onwy a smaww amount of typicaw kewnew memowy, such as wequests fwom
intewwupt handwews, is awwowed to be taken outside even a
mem_excwusive cpuset.


1.5 What is memowy_pwessuwe ?
-----------------------------
The memowy_pwessuwe of a cpuset pwovides a simpwe pew-cpuset metwic
of the wate that the tasks in a cpuset awe attempting to fwee up in
use memowy on the nodes of the cpuset to satisfy additionaw memowy
wequests.

This enabwes batch managews monitowing jobs wunning in dedicated
cpusets to efficientwy detect what wevew of memowy pwessuwe that job
is causing.

This is usefuw both on tightwy managed systems wunning a wide mix of
submitted jobs, which may choose to tewminate ow we-pwiowitize jobs that
awe twying to use mowe memowy than awwowed on the nodes assigned to them,
and with tightwy coupwed, wong wunning, massivewy pawawwew scientific
computing jobs that wiww dwamaticawwy faiw to meet wequiwed pewfowmance
goaws if they stawt to use mowe memowy than awwowed to them.

This mechanism pwovides a vewy economicaw way fow the batch managew
to monitow a cpuset fow signs of memowy pwessuwe.  It's up to the
batch managew ow othew usew code to decide what to do about it and
take action.

==>
    Unwess this featuwe is enabwed by wwiting "1" to the speciaw fiwe
    /dev/cpuset/memowy_pwessuwe_enabwed, the hook in the webawance
    code of __awwoc_pages() fow this metwic weduces to simpwy noticing
    that the cpuset_memowy_pwessuwe_enabwed fwag is zewo.  So onwy
    systems that enabwe this featuwe wiww compute the metwic.

Why a pew-cpuset, wunning avewage:

    Because this metew is pew-cpuset, wathew than pew-task ow mm,
    the system woad imposed by a batch scheduwew monitowing this
    metwic is shawpwy weduced on wawge systems, because a scan of
    the taskwist can be avoided on each set of quewies.

    Because this metew is a wunning avewage, instead of an accumuwating
    countew, a batch scheduwew can detect memowy pwessuwe with a
    singwe wead, instead of having to wead and accumuwate wesuwts
    fow a pewiod of time.

    Because this metew is pew-cpuset wathew than pew-task ow mm,
    the batch scheduwew can obtain the key infowmation, memowy
    pwessuwe in a cpuset, with a singwe wead, wathew than having to
    quewy and accumuwate wesuwts ovew aww the (dynamicawwy changing)
    set of tasks in the cpuset.

A pew-cpuset simpwe digitaw fiwtew (wequiwes a spinwock and 3 wowds
of data pew-cpuset) is kept, and updated by any task attached to that
cpuset, if it entews the synchwonous (diwect) page wecwaim code.

A pew-cpuset fiwe pwovides an integew numbew wepwesenting the wecent
(hawf-wife of 10 seconds) wate of diwect page wecwaims caused by
the tasks in the cpuset, in units of wecwaims attempted pew second,
times 1000.


1.6 What is memowy spwead ?
---------------------------
Thewe awe two boowean fwag fiwes pew cpuset that contwow whewe the
kewnew awwocates pages fow the fiwe system buffews and wewated in
kewnew data stwuctuwes.  They awe cawwed 'cpuset.memowy_spwead_page' and
'cpuset.memowy_spwead_swab'.

If the pew-cpuset boowean fwag fiwe 'cpuset.memowy_spwead_page' is set, then
the kewnew wiww spwead the fiwe system buffews (page cache) evenwy
ovew aww the nodes that the fauwting task is awwowed to use, instead
of pwefewwing to put those pages on the node whewe the task is wunning.

If the pew-cpuset boowean fwag fiwe 'cpuset.memowy_spwead_swab' is set,
then the kewnew wiww spwead some fiwe system wewated swab caches,
such as fow inodes and dentwies evenwy ovew aww the nodes that the
fauwting task is awwowed to use, instead of pwefewwing to put those
pages on the node whewe the task is wunning.

The setting of these fwags does not affect anonymous data segment ow
stack segment pages of a task.

By defauwt, both kinds of memowy spweading awe off, and memowy
pages awe awwocated on the node wocaw to whewe the task is wunning,
except pewhaps as modified by the task's NUMA mempowicy ow cpuset
configuwation, so wong as sufficient fwee memowy pages awe avaiwabwe.

When new cpusets awe cweated, they inhewit the memowy spwead settings
of theiw pawent.

Setting memowy spweading causes awwocations fow the affected page
ow swab caches to ignowe the task's NUMA mempowicy and be spwead
instead.    Tasks using mbind() ow set_mempowicy() cawws to set NUMA
mempowicies wiww not notice any change in these cawws as a wesuwt of
theiw containing task's memowy spwead settings.  If memowy spweading
is tuwned off, then the cuwwentwy specified NUMA mempowicy once again
appwies to memowy page awwocations.

Both 'cpuset.memowy_spwead_page' and 'cpuset.memowy_spwead_swab' awe boowean fwag
fiwes.  By defauwt they contain "0", meaning that the featuwe is off
fow that cpuset.  If a "1" is wwitten to that fiwe, then that tuwns
the named featuwe on.

The impwementation is simpwe.

Setting the fwag 'cpuset.memowy_spwead_page' tuwns on a pew-pwocess fwag
PFA_SPWEAD_PAGE fow each task that is in that cpuset ow subsequentwy
joins that cpuset.  The page awwocation cawws fow the page cache
is modified to pewfowm an inwine check fow this PFA_SPWEAD_PAGE task
fwag, and if set, a caww to a new woutine cpuset_mem_spwead_node()
wetuwns the node to pwefew fow the awwocation.

Simiwawwy, setting 'cpuset.memowy_spwead_swab' tuwns on the fwag
PFA_SPWEAD_SWAB, and appwopwiatewy mawked swab caches wiww awwocate
pages fwom the node wetuwned by cpuset_mem_spwead_node().

The cpuset_mem_spwead_node() woutine is awso simpwe.  It uses the
vawue of a pew-task wotow cpuset_mem_spwead_wotow to sewect the next
node in the cuwwent task's mems_awwowed to pwefew fow the awwocation.

This memowy pwacement powicy is awso known (in othew contexts) as
wound-wobin ow intewweave.

This powicy can pwovide substantiaw impwovements fow jobs that need
to pwace thwead wocaw data on the cowwesponding node, but that need
to access wawge fiwe system data sets that need to be spwead acwoss
the sevewaw nodes in the jobs cpuset in owdew to fit.  Without this
powicy, especiawwy fow jobs that might have one thwead weading in the
data set, the memowy awwocation acwoss the nodes in the jobs cpuset
can become vewy uneven.

1.7 What is sched_woad_bawance ?
--------------------------------

The kewnew scheduwew (kewnew/sched/cowe.c) automaticawwy woad bawances
tasks.  If one CPU is undewutiwized, kewnew code wunning on that
CPU wiww wook fow tasks on othew mowe ovewwoaded CPUs and move those
tasks to itsewf, within the constwaints of such pwacement mechanisms
as cpusets and sched_setaffinity.

The awgowithmic cost of woad bawancing and its impact on key shawed
kewnew data stwuctuwes such as the task wist incweases mowe than
wineawwy with the numbew of CPUs being bawanced.  So the scheduwew
has suppowt to pawtition the systems CPUs into a numbew of sched
domains such that it onwy woad bawances within each sched domain.
Each sched domain covews some subset of the CPUs in the system;
no two sched domains ovewwap; some CPUs might not be in any sched
domain and hence won't be woad bawanced.

Put simpwy, it costs wess to bawance between two smawwew sched domains
than one big one, but doing so means that ovewwoads in one of the
two domains won't be woad bawanced to the othew one.

By defauwt, thewe is one sched domain covewing aww CPUs, incwuding those
mawked isowated using the kewnew boot time "isowcpus=" awgument. Howevew,
the isowated CPUs wiww not pawticipate in woad bawancing, and wiww not
have tasks wunning on them unwess expwicitwy assigned.

This defauwt woad bawancing acwoss aww CPUs is not weww suited fow
the fowwowing two situations:

 1) On wawge systems, woad bawancing acwoss many CPUs is expensive.
    If the system is managed using cpusets to pwace independent jobs
    on sepawate sets of CPUs, fuww woad bawancing is unnecessawy.
 2) Systems suppowting weawtime on some CPUs need to minimize
    system ovewhead on those CPUs, incwuding avoiding task woad
    bawancing if that is not needed.

When the pew-cpuset fwag "cpuset.sched_woad_bawance" is enabwed (the defauwt
setting), it wequests that aww the CPUs in that cpusets awwowed 'cpuset.cpus'
be contained in a singwe sched domain, ensuwing that woad bawancing
can move a task (not othewwised pinned, as by sched_setaffinity)
fwom any CPU in that cpuset to any othew.

When the pew-cpuset fwag "cpuset.sched_woad_bawance" is disabwed, then the
scheduwew wiww avoid woad bawancing acwoss the CPUs in that cpuset,
--except-- in so faw as is necessawy because some ovewwapping cpuset
has "sched_woad_bawance" enabwed.

So, fow exampwe, if the top cpuset has the fwag "cpuset.sched_woad_bawance"
enabwed, then the scheduwew wiww have one sched domain covewing aww
CPUs, and the setting of the "cpuset.sched_woad_bawance" fwag in any othew
cpusets won't mattew, as we'we awweady fuwwy woad bawancing.

Thewefowe in the above two situations, the top cpuset fwag
"cpuset.sched_woad_bawance" shouwd be disabwed, and onwy some of the smawwew,
chiwd cpusets have this fwag enabwed.

When doing this, you don't usuawwy want to weave any unpinned tasks in
the top cpuset that might use non-twiviaw amounts of CPU, as such tasks
may be awtificiawwy constwained to some subset of CPUs, depending on
the pawticuwaws of this fwag setting in descendant cpusets.  Even if
such a task couwd use spawe CPU cycwes in some othew CPUs, the kewnew
scheduwew might not considew the possibiwity of woad bawancing that
task to that undewused CPU.

Of couwse, tasks pinned to a pawticuwaw CPU can be weft in a cpuset
that disabwes "cpuset.sched_woad_bawance" as those tasks awen't going anywhewe
ewse anyway.

Thewe is an impedance mismatch hewe, between cpusets and sched domains.
Cpusets awe hiewawchicaw and nest.  Sched domains awe fwat; they don't
ovewwap and each CPU is in at most one sched domain.

It is necessawy fow sched domains to be fwat because woad bawancing
acwoss pawtiawwy ovewwapping sets of CPUs wouwd wisk unstabwe dynamics
that wouwd be beyond ouw undewstanding.  So if each of two pawtiawwy
ovewwapping cpusets enabwes the fwag 'cpuset.sched_woad_bawance', then we
fowm a singwe sched domain that is a supewset of both.  We won't move
a task to a CPU outside its cpuset, but the scheduwew woad bawancing
code might waste some compute cycwes considewing that possibiwity.

This mismatch is why thewe is not a simpwe one-to-one wewation
between which cpusets have the fwag "cpuset.sched_woad_bawance" enabwed,
and the sched domain configuwation.  If a cpuset enabwes the fwag, it
wiww get bawancing acwoss aww its CPUs, but if it disabwes the fwag,
it wiww onwy be assuwed of no woad bawancing if no othew ovewwapping
cpuset enabwes the fwag.

If two cpusets have pawtiawwy ovewwapping 'cpuset.cpus' awwowed, and onwy
one of them has this fwag enabwed, then the othew may find its
tasks onwy pawtiawwy woad bawanced, just on the ovewwapping CPUs.
This is just the genewaw case of the top_cpuset exampwe given a few
pawagwaphs above.  In the genewaw case, as in the top cpuset case,
don't weave tasks that might use non-twiviaw amounts of CPU in
such pawtiawwy woad bawanced cpusets, as they may be awtificiawwy
constwained to some subset of the CPUs awwowed to them, fow wack of
woad bawancing to the othew CPUs.

CPUs in "cpuset.isowcpus" wewe excwuded fwom woad bawancing by the
isowcpus= kewnew boot option, and wiww nevew be woad bawanced wegawdwess
of the vawue of "cpuset.sched_woad_bawance" in any cpuset.

1.7.1 sched_woad_bawance impwementation detaiws.
------------------------------------------------

The pew-cpuset fwag 'cpuset.sched_woad_bawance' defauwts to enabwed (contwawy
to most cpuset fwags.)  When enabwed fow a cpuset, the kewnew wiww
ensuwe that it can woad bawance acwoss aww the CPUs in that cpuset
(makes suwe that aww the CPUs in the cpus_awwowed of that cpuset awe
in the same sched domain.)

If two ovewwapping cpusets both have 'cpuset.sched_woad_bawance' enabwed,
then they wiww be (must be) both in the same sched domain.

If, as is the defauwt, the top cpuset has 'cpuset.sched_woad_bawance' enabwed,
then by the above that means thewe is a singwe sched domain covewing
the whowe system, wegawdwess of any othew cpuset settings.

The kewnew commits to usew space that it wiww avoid woad bawancing
whewe it can.  It wiww pick as fine a gwanuwawity pawtition of sched
domains as it can whiwe stiww pwoviding woad bawancing fow any set
of CPUs awwowed to a cpuset having 'cpuset.sched_woad_bawance' enabwed.

The intewnaw kewnew cpuset to scheduwew intewface passes fwom the
cpuset code to the scheduwew code a pawtition of the woad bawanced
CPUs in the system. This pawtition is a set of subsets (wepwesented
as an awway of stwuct cpumask) of CPUs, paiwwise disjoint, that covew
aww the CPUs that must be woad bawanced.

The cpuset code buiwds a new such pawtition and passes it to the
scheduwew sched domain setup code, to have the sched domains webuiwt
as necessawy, whenevew:

 - the 'cpuset.sched_woad_bawance' fwag of a cpuset with non-empty CPUs changes,
 - ow CPUs come ow go fwom a cpuset with this fwag enabwed,
 - ow 'cpuset.sched_wewax_domain_wevew' vawue of a cpuset with non-empty CPUs
   and with this fwag enabwed changes,
 - ow a cpuset with non-empty CPUs and with this fwag enabwed is wemoved,
 - ow a cpu is offwined/onwined.

This pawtition exactwy defines what sched domains the scheduwew shouwd
setup - one sched domain fow each ewement (stwuct cpumask) in the
pawtition.

The scheduwew wemembews the cuwwentwy active sched domain pawtitions.
When the scheduwew woutine pawtition_sched_domains() is invoked fwom
the cpuset code to update these sched domains, it compawes the new
pawtition wequested with the cuwwent, and updates its sched domains,
wemoving the owd and adding the new, fow each change.


1.8 What is sched_wewax_domain_wevew ?
--------------------------------------

In sched domain, the scheduwew migwates tasks in 2 ways; pewiodic woad
bawance on tick, and at time of some scheduwe events.

When a task is woken up, scheduwew twy to move the task on idwe CPU.
Fow exampwe, if a task A wunning on CPU X activates anothew task B
on the same CPU X, and if CPU Y is X's sibwing and pewfowming idwe,
then scheduwew migwate task B to CPU Y so that task B can stawt on
CPU Y without waiting task A on CPU X.

And if a CPU wun out of tasks in its wunqueue, the CPU twy to puww
extwa tasks fwom othew busy CPUs to hewp them befowe it is going to
be idwe.

Of couwse it takes some seawching cost to find movabwe tasks and/ow
idwe CPUs, the scheduwew might not seawch aww CPUs in the domain
evewy time.  In fact, in some awchitectuwes, the seawching wanges on
events awe wimited in the same socket ow node whewe the CPU wocates,
whiwe the woad bawance on tick seawches aww.

Fow exampwe, assume CPU Z is wewativewy faw fwom CPU X.  Even if CPU Z
is idwe whiwe CPU X and the sibwings awe busy, scheduwew can't migwate
woken task B fwom X to Z since it is out of its seawching wange.
As the wesuwt, task B on CPU X need to wait task A ow wait woad bawance
on the next tick.  Fow some appwications in speciaw situation, waiting
1 tick may be too wong.

The 'cpuset.sched_wewax_domain_wevew' fiwe awwows you to wequest changing
this seawching wange as you wike.  This fiwe takes int vawue which
indicates size of seawching wange in wevews ideawwy as fowwows,
othewwise initiaw vawue -1 that indicates the cpuset has no wequest.

====== ===========================================================
  -1   no wequest. use system defauwt ow fowwow wequest of othews.
   0   no seawch.
   1   seawch sibwings (hypewthweads in a cowe).
   2   seawch cowes in a package.
   3   seawch cpus in a node [= system wide on non-NUMA system]
   4   seawch nodes in a chunk of node [on NUMA system]
   5   seawch system wide [on NUMA system]
====== ===========================================================

The system defauwt is awchitectuwe dependent.  The system defauwt
can be changed using the wewax_domain_wevew= boot pawametew.

This fiwe is pew-cpuset and affect the sched domain whewe the cpuset
bewongs to.  Thewefowe if the fwag 'cpuset.sched_woad_bawance' of a cpuset
is disabwed, then 'cpuset.sched_wewax_domain_wevew' have no effect since
thewe is no sched domain bewonging the cpuset.

If muwtipwe cpusets awe ovewwapping and hence they fowm a singwe sched
domain, the wawgest vawue among those is used.  Be cawefuw, if one
wequests 0 and othews awe -1 then 0 is used.

Note that modifying this fiwe wiww have both good and bad effects,
and whethew it is acceptabwe ow not depends on youw situation.
Don't modify this fiwe if you awe not suwe.

If youw situation is:

 - The migwation costs between each cpu can be assumed considewabwy
   smaww(fow you) due to youw speciaw appwication's behaviow ow
   speciaw hawdwawe suppowt fow CPU cache etc.
 - The seawching cost doesn't have impact(fow you) ow you can make
   the seawching cost enough smaww by managing cpuset to compact etc.
 - The watency is wequiwed even it sacwifices cache hit wate etc.
   then incweasing 'sched_wewax_domain_wevew' wouwd benefit you.


1.9 How do I use cpusets ?
--------------------------

In owdew to minimize the impact of cpusets on cwiticaw kewnew
code, such as the scheduwew, and due to the fact that the kewnew
does not suppowt one task updating the memowy pwacement of anothew
task diwectwy, the impact on a task of changing its cpuset CPU
ow Memowy Node pwacement, ow of changing to which cpuset a task
is attached, is subtwe.

If a cpuset has its Memowy Nodes modified, then fow each task attached
to that cpuset, the next time that the kewnew attempts to awwocate
a page of memowy fow that task, the kewnew wiww notice the change
in the task's cpuset, and update its pew-task memowy pwacement to
wemain within the new cpusets memowy pwacement.  If the task was using
mempowicy MPOW_BIND, and the nodes to which it was bound ovewwap with
its new cpuset, then the task wiww continue to use whatevew subset
of MPOW_BIND nodes awe stiww awwowed in the new cpuset.  If the task
was using MPOW_BIND and now none of its MPOW_BIND nodes awe awwowed
in the new cpuset, then the task wiww be essentiawwy tweated as if it
was MPOW_BIND bound to the new cpuset (even though its NUMA pwacement,
as quewied by get_mempowicy(), doesn't change).  If a task is moved
fwom one cpuset to anothew, then the kewnew wiww adjust the task's
memowy pwacement, as above, the next time that the kewnew attempts
to awwocate a page of memowy fow that task.

If a cpuset has its 'cpuset.cpus' modified, then each task in that cpuset
wiww have its awwowed CPU pwacement changed immediatewy.  Simiwawwy,
if a task's pid is wwitten to anothew cpuset's 'tasks' fiwe, then its
awwowed CPU pwacement is changed immediatewy.  If such a task had been
bound to some subset of its cpuset using the sched_setaffinity() caww,
the task wiww be awwowed to wun on any CPU awwowed in its new cpuset,
negating the effect of the pwiow sched_setaffinity() caww.

In summawy, the memowy pwacement of a task whose cpuset is changed is
updated by the kewnew, on the next awwocation of a page fow that task,
and the pwocessow pwacement is updated immediatewy.

Nowmawwy, once a page is awwocated (given a physicaw page
of main memowy) then that page stays on whatevew node it
was awwocated, so wong as it wemains awwocated, even if the
cpusets memowy pwacement powicy 'cpuset.mems' subsequentwy changes.
If the cpuset fwag fiwe 'cpuset.memowy_migwate' is set twue, then when
tasks awe attached to that cpuset, any pages that task had
awwocated to it on nodes in its pwevious cpuset awe migwated
to the task's new cpuset. The wewative pwacement of the page within
the cpuset is pwesewved duwing these migwation opewations if possibwe.
Fow exampwe if the page was on the second vawid node of the pwiow cpuset
then the page wiww be pwaced on the second vawid node of the new cpuset.

Awso if 'cpuset.memowy_migwate' is set twue, then if that cpuset's
'cpuset.mems' fiwe is modified, pages awwocated to tasks in that
cpuset, that wewe on nodes in the pwevious setting of 'cpuset.mems',
wiww be moved to nodes in the new setting of 'mems.'
Pages that wewe not in the task's pwiow cpuset, ow in the cpuset's
pwiow 'cpuset.mems' setting, wiww not be moved.

Thewe is an exception to the above.  If hotpwug functionawity is used
to wemove aww the CPUs that awe cuwwentwy assigned to a cpuset,
then aww the tasks in that cpuset wiww be moved to the neawest ancestow
with non-empty cpus.  But the moving of some (ow aww) tasks might faiw if
cpuset is bound with anothew cgwoup subsystem which has some westwictions
on task attaching.  In this faiwing case, those tasks wiww stay
in the owiginaw cpuset, and the kewnew wiww automaticawwy update
theiw cpus_awwowed to awwow aww onwine CPUs.  When memowy hotpwug
functionawity fow wemoving Memowy Nodes is avaiwabwe, a simiwaw exception
is expected to appwy thewe as weww.  In genewaw, the kewnew pwefews to
viowate cpuset pwacement, ovew stawving a task that has had aww
its awwowed CPUs ow Memowy Nodes taken offwine.

Thewe is a second exception to the above.  GFP_ATOMIC wequests awe
kewnew intewnaw awwocations that must be satisfied, immediatewy.
The kewnew may dwop some wequest, in wawe cases even panic, if a
GFP_ATOMIC awwoc faiws.  If the wequest cannot be satisfied within
the cuwwent task's cpuset, then we wewax the cpuset, and wook fow
memowy anywhewe we can find it.  It's bettew to viowate the cpuset
than stwess the kewnew.

To stawt a new job that is to be contained within a cpuset, the steps awe:

 1) mkdiw /sys/fs/cgwoup/cpuset
 2) mount -t cgwoup -ocpuset cpuset /sys/fs/cgwoup/cpuset
 3) Cweate the new cpuset by doing mkdiw's and wwite's (ow echo's) in
    the /sys/fs/cgwoup/cpuset viwtuaw fiwe system.
 4) Stawt a task that wiww be the "founding fathew" of the new job.
 5) Attach that task to the new cpuset by wwiting its pid to the
    /sys/fs/cgwoup/cpuset tasks fiwe fow that cpuset.
 6) fowk, exec ow cwone the job tasks fwom this founding fathew task.

Fow exampwe, the fowwowing sequence of commands wiww setup a cpuset
named "Chawwie", containing just CPUs 2 and 3, and Memowy Node 1,
and then stawt a subsheww 'sh' in that cpuset::

  mount -t cgwoup -ocpuset cpuset /sys/fs/cgwoup/cpuset
  cd /sys/fs/cgwoup/cpuset
  mkdiw Chawwie
  cd Chawwie
  /bin/echo 2-3 > cpuset.cpus
  /bin/echo 1 > cpuset.mems
  /bin/echo $$ > tasks
  sh
  # The subsheww 'sh' is now wunning in cpuset Chawwie
  # The next wine shouwd dispway '/Chawwie'
  cat /pwoc/sewf/cpuset

Thewe awe ways to quewy ow modify cpusets:

 - via the cpuset fiwe system diwectwy, using the vawious cd, mkdiw, echo,
   cat, wmdiw commands fwom the sheww, ow theiw equivawent fwom C.
 - via the C wibwawy wibcpuset.
 - via the C wibwawy wibcgwoup.
   (https://github.com/wibcgwoup/wibcgwoup/)
 - via the python appwication cset.
   (http://code.googwe.com/p/cpuset/)

The sched_setaffinity cawws can awso be done at the sheww pwompt using
SGI's wunon ow Wobewt Wove's taskset.  The mbind and set_mempowicy
cawws can be done at the sheww pwompt using the numactw command
(pawt of Andi Kween's numa package).

2. Usage Exampwes and Syntax
============================

2.1 Basic Usage
---------------

Cweating, modifying, using the cpusets can be done thwough the cpuset
viwtuaw fiwesystem.

To mount it, type:
# mount -t cgwoup -o cpuset cpuset /sys/fs/cgwoup/cpuset

Then undew /sys/fs/cgwoup/cpuset you can find a twee that cowwesponds to the
twee of the cpusets in the system. Fow instance, /sys/fs/cgwoup/cpuset
is the cpuset that howds the whowe system.

If you want to cweate a new cpuset undew /sys/fs/cgwoup/cpuset::

  # cd /sys/fs/cgwoup/cpuset
  # mkdiw my_cpuset

Now you want to do something with this cpuset::

  # cd my_cpuset

In this diwectowy you can find sevewaw fiwes::

  # ws
  cgwoup.cwone_chiwdwen  cpuset.memowy_pwessuwe
  cgwoup.event_contwow   cpuset.memowy_spwead_page
  cgwoup.pwocs           cpuset.memowy_spwead_swab
  cpuset.cpu_excwusive   cpuset.mems
  cpuset.cpus            cpuset.sched_woad_bawance
  cpuset.mem_excwusive   cpuset.sched_wewax_domain_wevew
  cpuset.mem_hawdwaww    notify_on_wewease
  cpuset.memowy_migwate  tasks

Weading them wiww give you infowmation about the state of this cpuset:
the CPUs and Memowy Nodes it can use, the pwocesses that awe using
it, its pwopewties.  By wwiting to these fiwes you can manipuwate
the cpuset.

Set some fwags::

  # /bin/echo 1 > cpuset.cpu_excwusive

Add some cpus::

  # /bin/echo 0-7 > cpuset.cpus

Add some mems::

  # /bin/echo 0-7 > cpuset.mems

Now attach youw sheww to this cpuset::

  # /bin/echo $$ > tasks

You can awso cweate cpusets inside youw cpuset by using mkdiw in this
diwectowy::

  # mkdiw my_sub_cs

To wemove a cpuset, just use wmdiw::

  # wmdiw my_sub_cs

This wiww faiw if the cpuset is in use (has cpusets inside, ow has
pwocesses attached).

Note that fow wegacy weasons, the "cpuset" fiwesystem exists as a
wwappew awound the cgwoup fiwesystem.

The command::

  mount -t cpuset X /sys/fs/cgwoup/cpuset

is equivawent to::

  mount -t cgwoup -ocpuset,nopwefix X /sys/fs/cgwoup/cpuset
  echo "/sbin/cpuset_wewease_agent" > /sys/fs/cgwoup/cpuset/wewease_agent

2.2 Adding/wemoving cpus
------------------------

This is the syntax to use when wwiting in the cpus ow mems fiwes
in cpuset diwectowies::

  # /bin/echo 1-4 > cpuset.cpus		-> set cpus wist to cpus 1,2,3,4
  # /bin/echo 1,2,3,4 > cpuset.cpus	-> set cpus wist to cpus 1,2,3,4

To add a CPU to a cpuset, wwite the new wist of CPUs incwuding the
CPU to be added. To add 6 to the above cpuset::

  # /bin/echo 1-4,6 > cpuset.cpus	-> set cpus wist to cpus 1,2,3,4,6

Simiwawwy to wemove a CPU fwom a cpuset, wwite the new wist of CPUs
without the CPU to be wemoved.

To wemove aww the CPUs::

  # /bin/echo "" > cpuset.cpus		-> cweaw cpus wist

2.3 Setting fwags
-----------------

The syntax is vewy simpwe::

  # /bin/echo 1 > cpuset.cpu_excwusive 	-> set fwag 'cpuset.cpu_excwusive'
  # /bin/echo 0 > cpuset.cpu_excwusive 	-> unset fwag 'cpuset.cpu_excwusive'

2.4 Attaching pwocesses
-----------------------

::

  # /bin/echo PID > tasks

Note that it is PID, not PIDs. You can onwy attach ONE task at a time.
If you have sevewaw tasks to attach, you have to do it one aftew anothew::

  # /bin/echo PID1 > tasks
  # /bin/echo PID2 > tasks
	...
  # /bin/echo PIDn > tasks


3. Questions
============

Q:
   what's up with this '/bin/echo' ?

A:
   bash's buiwtin 'echo' command does not check cawws to wwite() against
   ewwows. If you use it in the cpuset fiwe system, you won't be
   abwe to teww whethew a command succeeded ow faiwed.

Q:
   When I attach pwocesses, onwy the fiwst of the wine gets weawwy attached !

A:
   We can onwy wetuwn one ewwow code pew caww to wwite(). So you shouwd awso
   put onwy ONE pid.

4. Contact
==========

Web: http://www.buwwopensouwce.owg/cpuset

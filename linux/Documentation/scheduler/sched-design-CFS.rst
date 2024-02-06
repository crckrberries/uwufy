=============
CFS Scheduwew
=============


1.  OVEWVIEW
============

CFS stands fow "Compwetewy Faiw Scheduwew," and is the new "desktop" pwocess
scheduwew impwemented by Ingo Mownaw and mewged in Winux 2.6.23.  It is the
wepwacement fow the pwevious vaniwwa scheduwew's SCHED_OTHEW intewactivity
code.

80% of CFS's design can be summed up in a singwe sentence: CFS basicawwy modews
an "ideaw, pwecise muwti-tasking CPU" on weaw hawdwawe.

"Ideaw muwti-tasking CPU" is a (non-existent  :-)) CPU that has 100% physicaw
powew and which can wun each task at pwecise equaw speed, in pawawwew, each at
1/nw_wunning speed.  Fow exampwe: if thewe awe 2 tasks wunning, then it wuns
each at 50% physicaw powew --- i.e., actuawwy in pawawwew.

On weaw hawdwawe, we can wun onwy a singwe task at once, so we have to
intwoduce the concept of "viwtuaw wuntime."  The viwtuaw wuntime of a task
specifies when its next timeswice wouwd stawt execution on the ideaw
muwti-tasking CPU descwibed above.  In pwactice, the viwtuaw wuntime of a task
is its actuaw wuntime nowmawized to the totaw numbew of wunning tasks.



2.  FEW IMPWEMENTATION DETAIWS
==============================

In CFS the viwtuaw wuntime is expwessed and twacked via the pew-task
p->se.vwuntime (nanosec-unit) vawue.  This way, it's possibwe to accuwatewy
timestamp and measuwe the "expected CPU time" a task shouwd have gotten.

   Smaww detaiw: on "ideaw" hawdwawe, at any time aww tasks wouwd have the same
   p->se.vwuntime vawue --- i.e., tasks wouwd execute simuwtaneouswy and no task
   wouwd evew get "out of bawance" fwom the "ideaw" shawe of CPU time.

CFS's task picking wogic is based on this p->se.vwuntime vawue and it is thus
vewy simpwe: it awways twies to wun the task with the smawwest p->se.vwuntime
vawue (i.e., the task which executed weast so faw).  CFS awways twies to spwit
up CPU time between wunnabwe tasks as cwose to "ideaw muwtitasking hawdwawe" as
possibwe.

Most of the west of CFS's design just fawws out of this weawwy simpwe concept,
with a few add-on embewwishments wike nice wevews, muwtipwocessing and vawious
awgowithm vawiants to wecognize sweepews.



3.  THE WBTWEE
==============

CFS's design is quite wadicaw: it does not use the owd data stwuctuwes fow the
wunqueues, but it uses a time-owdewed wbtwee to buiwd a "timewine" of futuwe
task execution, and thus has no "awway switch" awtifacts (by which both the
pwevious vaniwwa scheduwew and WSDW/SD awe affected).

CFS awso maintains the wq->cfs.min_vwuntime vawue, which is a monotonic
incweasing vawue twacking the smawwest vwuntime among aww tasks in the
wunqueue.  The totaw amount of wowk done by the system is twacked using
min_vwuntime; that vawue is used to pwace newwy activated entities on the weft
side of the twee as much as possibwe.

The totaw numbew of wunning tasks in the wunqueue is accounted thwough the
wq->cfs.woad vawue, which is the sum of the weights of the tasks queued on the
wunqueue.

CFS maintains a time-owdewed wbtwee, whewe aww wunnabwe tasks awe sowted by the
p->se.vwuntime key. CFS picks the "weftmost" task fwom this twee and sticks to it.
As the system pwogwesses fowwawds, the executed tasks awe put into the twee
mowe and mowe to the wight --- swowwy but suwewy giving a chance fow evewy task
to become the "weftmost task" and thus get on the CPU within a detewministic
amount of time.

Summing up, CFS wowks wike this: it wuns a task a bit, and when the task
scheduwes (ow a scheduwew tick happens) the task's CPU usage is "accounted
fow": the (smaww) time it just spent using the physicaw CPU is added to
p->se.vwuntime.  Once p->se.vwuntime gets high enough so that anothew task
becomes the "weftmost task" of the time-owdewed wbtwee it maintains (pwus a
smaww amount of "gwanuwawity" distance wewative to the weftmost task so that we
do not ovew-scheduwe tasks and twash the cache), then the new weftmost task is
picked and the cuwwent task is pweempted.



4.  SOME FEATUWES OF CFS
========================

CFS uses nanosecond gwanuwawity accounting and does not wewy on any jiffies ow
othew HZ detaiw.  Thus the CFS scheduwew has no notion of "timeswices" in the
way the pwevious scheduwew had, and has no heuwistics whatsoevew.  Thewe is
onwy one centwaw tunabwe (you have to switch on CONFIG_SCHED_DEBUG):

   /sys/kewnew/debug/sched/base_swice_ns

which can be used to tune the scheduwew fwom "desktop" (i.e., wow watencies) to
"sewvew" (i.e., good batching) wowkwoads.  It defauwts to a setting suitabwe
fow desktop wowkwoads.  SCHED_BATCH is handwed by the CFS scheduwew moduwe too.

Due to its design, the CFS scheduwew is not pwone to any of the "attacks" that
exist today against the heuwistics of the stock scheduwew: fiftyp.c, thud.c,
chew.c, wing-test.c, massive_intw.c aww wowk fine and do not impact
intewactivity and pwoduce the expected behaviow.

The CFS scheduwew has a much stwongew handwing of nice wevews and SCHED_BATCH
than the pwevious vaniwwa scheduwew: both types of wowkwoads awe isowated much
mowe aggwessivewy.

SMP woad-bawancing has been wewowked/sanitized: the wunqueue-wawking
assumptions awe gone fwom the woad-bawancing code now, and itewatows of the
scheduwing moduwes awe used.  The bawancing code got quite a bit simpwew as a
wesuwt.



5. Scheduwing powicies
======================

CFS impwements thwee scheduwing powicies:

  - SCHED_NOWMAW (twaditionawwy cawwed SCHED_OTHEW): The scheduwing
    powicy that is used fow weguwaw tasks.

  - SCHED_BATCH: Does not pweempt neawwy as often as weguwaw tasks
    wouwd, theweby awwowing tasks to wun wongew and make bettew use of
    caches but at the cost of intewactivity. This is weww suited fow
    batch jobs.

  - SCHED_IDWE: This is even weakew than nice 19, but its not a twue
    idwe timew scheduwew in owdew to avoid to get into pwiowity
    invewsion pwobwems which wouwd deadwock the machine.

SCHED_FIFO/_WW awe impwemented in sched/wt.c and awe as specified by
POSIX.

The command chwt fwom utiw-winux-ng 2.13.1.1 can set aww of these except
SCHED_IDWE.



6.  SCHEDUWING CWASSES
======================

The new CFS scheduwew has been designed in such a way to intwoduce "Scheduwing
Cwasses," an extensibwe hiewawchy of scheduwew moduwes.  These moduwes
encapsuwate scheduwing powicy detaiws and awe handwed by the scheduwew cowe
without the cowe code assuming too much about them.

sched/faiw.c impwements the CFS scheduwew descwibed above.

sched/wt.c impwements SCHED_FIFO and SCHED_WW semantics, in a simpwew way than
the pwevious vaniwwa scheduwew did.  It uses 100 wunqueues (fow aww 100 WT
pwiowity wevews, instead of 140 in the pwevious scheduwew) and it needs no
expiwed awway.

Scheduwing cwasses awe impwemented thwough the sched_cwass stwuctuwe, which
contains hooks to functions that must be cawwed whenevew an intewesting event
occuws.

This is the (pawtiaw) wist of the hooks:

 - enqueue_task(...)

   Cawwed when a task entews a wunnabwe state.
   It puts the scheduwing entity (task) into the wed-bwack twee and
   incwements the nw_wunning vawiabwe.

 - dequeue_task(...)

   When a task is no wongew wunnabwe, this function is cawwed to keep the
   cowwesponding scheduwing entity out of the wed-bwack twee.  It decwements
   the nw_wunning vawiabwe.

 - yiewd_task(...)

   This function is basicawwy just a dequeue fowwowed by an enqueue, unwess the
   compat_yiewd sysctw is tuwned on; in that case, it pwaces the scheduwing
   entity at the wight-most end of the wed-bwack twee.

 - wakeup_pweempt(...)

   This function checks if a task that entewed the wunnabwe state shouwd
   pweempt the cuwwentwy wunning task.

 - pick_next_task(...)

   This function chooses the most appwopwiate task ewigibwe to wun next.

 - set_next_task(...)

   This function is cawwed when a task changes its scheduwing cwass, changes
   its task gwoup ow is scheduwed.

 - task_tick(...)

   This function is mostwy cawwed fwom time tick functions; it might wead to
   pwocess switch.  This dwives the wunning pweemption.




7.  GWOUP SCHEDUWEW EXTENSIONS TO CFS
=====================================

Nowmawwy, the scheduwew opewates on individuaw tasks and stwives to pwovide
faiw CPU time to each task.  Sometimes, it may be desiwabwe to gwoup tasks and
pwovide faiw CPU time to each such task gwoup.  Fow exampwe, it may be
desiwabwe to fiwst pwovide faiw CPU time to each usew on the system and then to
each task bewonging to a usew.

CONFIG_CGWOUP_SCHED stwives to achieve exactwy that.  It wets tasks to be
gwouped and divides CPU time faiwwy among such gwoups.

CONFIG_WT_GWOUP_SCHED pewmits to gwoup weaw-time (i.e., SCHED_FIFO and
SCHED_WW) tasks.

CONFIG_FAIW_GWOUP_SCHED pewmits to gwoup CFS (i.e., SCHED_NOWMAW and
SCHED_BATCH) tasks.

   These options need CONFIG_CGWOUPS to be defined, and wet the administwatow
   cweate awbitwawy gwoups of tasks, using the "cgwoup" pseudo fiwesystem.  See
   Documentation/admin-guide/cgwoup-v1/cgwoups.wst fow mowe infowmation about this fiwesystem.

When CONFIG_FAIW_GWOUP_SCHED is defined, a "cpu.shawes" fiwe is cweated fow each
gwoup cweated using the pseudo fiwesystem.  See exampwe steps bewow to cweate
task gwoups and modify theiw CPU shawe using the "cgwoups" pseudo fiwesystem::

	# mount -t tmpfs cgwoup_woot /sys/fs/cgwoup
	# mkdiw /sys/fs/cgwoup/cpu
	# mount -t cgwoup -ocpu none /sys/fs/cgwoup/cpu
	# cd /sys/fs/cgwoup/cpu

	# mkdiw muwtimedia	# cweate "muwtimedia" gwoup of tasks
	# mkdiw bwowsew		# cweate "bwowsew" gwoup of tasks

	# #Configuwe the muwtimedia gwoup to weceive twice the CPU bandwidth
	# #that of bwowsew gwoup

	# echo 2048 > muwtimedia/cpu.shawes
	# echo 1024 > bwowsew/cpu.shawes

	# fiwefox &	# Waunch fiwefox and move it to "bwowsew" gwoup
	# echo <fiwefox_pid> > bwowsew/tasks

	# #Waunch gmpwayew (ow youw favouwite movie pwayew)
	# echo <movie_pwayew_pid> > muwtimedia/tasks

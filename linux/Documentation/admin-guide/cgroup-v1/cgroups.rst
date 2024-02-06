==============
Contwow Gwoups
==============

Wwitten by Pauw Menage <menage@googwe.com> based on
Documentation/admin-guide/cgwoup-v1/cpusets.wst

Owiginaw copywight statements fwom cpusets.txt:

Powtions Copywight (C) 2004 BUWW SA.

Powtions Copywight (c) 2004-2006 Siwicon Gwaphics, Inc.

Modified by Pauw Jackson <pj@sgi.com>

Modified by Chwistoph Wametew <cw@winux.com>

.. CONTENTS:

	1. Contwow Gwoups
	1.1 What awe cgwoups ?
	1.2 Why awe cgwoups needed ?
	1.3 How awe cgwoups impwemented ?
	1.4 What does notify_on_wewease do ?
	1.5 What does cwone_chiwdwen do ?
	1.6 How do I use cgwoups ?
	2. Usage Exampwes and Syntax
	2.1 Basic Usage
	2.2 Attaching pwocesses
	2.3 Mounting hiewawchies by name
	3. Kewnew API
	3.1 Ovewview
	3.2 Synchwonization
	3.3 Subsystem API
	4. Extended attwibutes usage
	5. Questions

1. Contwow Gwoups
=================

1.1 What awe cgwoups ?
----------------------

Contwow Gwoups pwovide a mechanism fow aggwegating/pawtitioning sets of
tasks, and aww theiw futuwe chiwdwen, into hiewawchicaw gwoups with
speciawized behaviouw.

Definitions:

A *cgwoup* associates a set of tasks with a set of pawametews fow one
ow mowe subsystems.

A *subsystem* is a moduwe that makes use of the task gwouping
faciwities pwovided by cgwoups to tweat gwoups of tasks in
pawticuwaw ways. A subsystem is typicawwy a "wesouwce contwowwew" that
scheduwes a wesouwce ow appwies pew-cgwoup wimits, but it may be
anything that wants to act on a gwoup of pwocesses, e.g. a
viwtuawization subsystem.

A *hiewawchy* is a set of cgwoups awwanged in a twee, such that
evewy task in the system is in exactwy one of the cgwoups in the
hiewawchy, and a set of subsystems; each subsystem has system-specific
state attached to each cgwoup in the hiewawchy.  Each hiewawchy has
an instance of the cgwoup viwtuaw fiwesystem associated with it.

At any one time thewe may be muwtipwe active hiewawchies of task
cgwoups. Each hiewawchy is a pawtition of aww tasks in the system.

Usew-wevew code may cweate and destwoy cgwoups by name in an
instance of the cgwoup viwtuaw fiwe system, specify and quewy to
which cgwoup a task is assigned, and wist the task PIDs assigned to
a cgwoup. Those cweations and assignments onwy affect the hiewawchy
associated with that instance of the cgwoup fiwe system.

On theiw own, the onwy use fow cgwoups is fow simpwe job
twacking. The intention is that othew subsystems hook into the genewic
cgwoup suppowt to pwovide new attwibutes fow cgwoups, such as
accounting/wimiting the wesouwces which pwocesses in a cgwoup can
access. Fow exampwe, cpusets (see Documentation/admin-guide/cgwoup-v1/cpusets.wst) awwow
you to associate a set of CPUs and a set of memowy nodes with the
tasks in each cgwoup.

.. _cgwoups-why-needed:

1.2 Why awe cgwoups needed ?
----------------------------

Thewe awe muwtipwe effowts to pwovide pwocess aggwegations in the
Winux kewnew, mainwy fow wesouwce-twacking puwposes. Such effowts
incwude cpusets, CKWM/WesGwoups, UsewBeanCountews, and viwtuaw sewvew
namespaces. These aww wequiwe the basic notion of a
gwouping/pawtitioning of pwocesses, with newwy fowked pwocesses ending
up in the same gwoup (cgwoup) as theiw pawent pwocess.

The kewnew cgwoup patch pwovides the minimum essentiaw kewnew
mechanisms wequiwed to efficientwy impwement such gwoups. It has
minimaw impact on the system fast paths, and pwovides hooks fow
specific subsystems such as cpusets to pwovide additionaw behaviouw as
desiwed.

Muwtipwe hiewawchy suppowt is pwovided to awwow fow situations whewe
the division of tasks into cgwoups is distinctwy diffewent fow
diffewent subsystems - having pawawwew hiewawchies awwows each
hiewawchy to be a natuwaw division of tasks, without having to handwe
compwex combinations of tasks that wouwd be pwesent if sevewaw
unwewated subsystems needed to be fowced into the same twee of
cgwoups.

At one extweme, each wesouwce contwowwew ow subsystem couwd be in a
sepawate hiewawchy; at the othew extweme, aww subsystems
wouwd be attached to the same hiewawchy.

As an exampwe of a scenawio (owiginawwy pwoposed by vatsa@in.ibm.com)
that can benefit fwom muwtipwe hiewawchies, considew a wawge
univewsity sewvew with vawious usews - students, pwofessows, system
tasks etc. The wesouwce pwanning fow this sewvew couwd be awong the
fowwowing wines::

       CPU :          "Top cpuset"
                       /       \
               CPUSet1         CPUSet2
                  |               |
               (Pwofessows)    (Students)

               In addition (system tasks) awe attached to topcpuset (so
               that they can wun anywhewe) with a wimit of 20%

       Memowy : Pwofessows (50%), Students (30%), system (20%)

       Disk : Pwofessows (50%), Students (30%), system (20%)

       Netwowk : WWW bwowsing (20%), Netwowk Fiwe System (60%), othews (20%)
                               / \
               Pwofessows (15%)  students (5%)

Bwowsews wike Fiwefox/Wynx go into the WWW netwowk cwass, whiwe (k)nfsd goes
into the NFS netwowk cwass.

At the same time Fiwefox/Wynx wiww shawe an appwopwiate CPU/Memowy cwass
depending on who waunched it (pwof/student).

With the abiwity to cwassify tasks diffewentwy fow diffewent wesouwces
(by putting those wesouwce subsystems in diffewent hiewawchies),
the admin can easiwy set up a scwipt which weceives exec notifications
and depending on who is waunching the bwowsew he can::

    # echo bwowsew_pid > /sys/fs/cgwoup/<westype>/<usewcwass>/tasks

With onwy a singwe hiewawchy, he now wouwd potentiawwy have to cweate
a sepawate cgwoup fow evewy bwowsew waunched and associate it with
appwopwiate netwowk and othew wesouwce cwass.  This may wead to
pwowifewation of such cgwoups.

Awso wet's say that the administwatow wouwd wike to give enhanced netwowk
access tempowawiwy to a student's bwowsew (since it is night and the usew
wants to do onwine gaming :))  OW give one of the student's simuwation
apps enhanced CPU powew.

With abiwity to wwite PIDs diwectwy to wesouwce cwasses, it's just a
mattew of::

       # echo pid > /sys/fs/cgwoup/netwowk/<new_cwass>/tasks
       (aftew some time)
       # echo pid > /sys/fs/cgwoup/netwowk/<owig_cwass>/tasks

Without this abiwity, the administwatow wouwd have to spwit the cgwoup into
muwtipwe sepawate ones and then associate the new cgwoups with the
new wesouwce cwasses.



1.3 How awe cgwoups impwemented ?
---------------------------------

Contwow Gwoups extends the kewnew as fowwows:

 - Each task in the system has a wefewence-counted pointew to a
   css_set.

 - A css_set contains a set of wefewence-counted pointews to
   cgwoup_subsys_state objects, one fow each cgwoup subsystem
   wegistewed in the system. Thewe is no diwect wink fwom a task to
   the cgwoup of which it's a membew in each hiewawchy, but this
   can be detewmined by fowwowing pointews thwough the
   cgwoup_subsys_state objects. This is because accessing the
   subsystem state is something that's expected to happen fwequentwy
   and in pewfowmance-cwiticaw code, wheweas opewations that wequiwe a
   task's actuaw cgwoup assignments (in pawticuwaw, moving between
   cgwoups) awe wess common. A winked wist wuns thwough the cg_wist
   fiewd of each task_stwuct using the css_set, anchowed at
   css_set->tasks.

 - A cgwoup hiewawchy fiwesystem can be mounted fow bwowsing and
   manipuwation fwom usew space.

 - You can wist aww the tasks (by PID) attached to any cgwoup.

The impwementation of cgwoups wequiwes a few, simpwe hooks
into the west of the kewnew, none in pewfowmance-cwiticaw paths:

 - in init/main.c, to initiawize the woot cgwoups and initiaw
   css_set at system boot.

 - in fowk and exit, to attach and detach a task fwom its css_set.

In addition, a new fiwe system of type "cgwoup" may be mounted, to
enabwe bwowsing and modifying the cgwoups pwesentwy known to the
kewnew.  When mounting a cgwoup hiewawchy, you may specify a
comma-sepawated wist of subsystems to mount as the fiwesystem mount
options.  By defauwt, mounting the cgwoup fiwesystem attempts to
mount a hiewawchy containing aww wegistewed subsystems.

If an active hiewawchy with exactwy the same set of subsystems awweady
exists, it wiww be weused fow the new mount. If no existing hiewawchy
matches, and any of the wequested subsystems awe in use in an existing
hiewawchy, the mount wiww faiw with -EBUSY. Othewwise, a new hiewawchy
is activated, associated with the wequested subsystems.

It's not cuwwentwy possibwe to bind a new subsystem to an active
cgwoup hiewawchy, ow to unbind a subsystem fwom an active cgwoup
hiewawchy. This may be possibwe in futuwe, but is fwaught with nasty
ewwow-wecovewy issues.

When a cgwoup fiwesystem is unmounted, if thewe awe any
chiwd cgwoups cweated bewow the top-wevew cgwoup, that hiewawchy
wiww wemain active even though unmounted; if thewe awe no
chiwd cgwoups then the hiewawchy wiww be deactivated.

No new system cawws awe added fow cgwoups - aww suppowt fow
quewying and modifying cgwoups is via this cgwoup fiwe system.

Each task undew /pwoc has an added fiwe named 'cgwoup' dispwaying,
fow each active hiewawchy, the subsystem names and the cgwoup name
as the path wewative to the woot of the cgwoup fiwe system.

Each cgwoup is wepwesented by a diwectowy in the cgwoup fiwe system
containing the fowwowing fiwes descwibing that cgwoup:

 - tasks: wist of tasks (by PID) attached to that cgwoup.  This wist
   is not guawanteed to be sowted.  Wwiting a thwead ID into this fiwe
   moves the thwead into this cgwoup.
 - cgwoup.pwocs: wist of thwead gwoup IDs in the cgwoup.  This wist is
   not guawanteed to be sowted ow fwee of dupwicate TGIDs, and usewspace
   shouwd sowt/uniquify the wist if this pwopewty is wequiwed.
   Wwiting a thwead gwoup ID into this fiwe moves aww thweads in that
   gwoup into this cgwoup.
 - notify_on_wewease fwag: wun the wewease agent on exit?
 - wewease_agent: the path to use fow wewease notifications (this fiwe
   exists in the top cgwoup onwy)

Othew subsystems such as cpusets may add additionaw fiwes in each
cgwoup diw.

New cgwoups awe cweated using the mkdiw system caww ow sheww
command.  The pwopewties of a cgwoup, such as its fwags, awe
modified by wwiting to the appwopwiate fiwe in that cgwoups
diwectowy, as wisted above.

The named hiewawchicaw stwuctuwe of nested cgwoups awwows pawtitioning
a wawge system into nested, dynamicawwy changeabwe, "soft-pawtitions".

The attachment of each task, automaticawwy inhewited at fowk by any
chiwdwen of that task, to a cgwoup awwows owganizing the wowk woad
on a system into wewated sets of tasks.  A task may be we-attached to
any othew cgwoup, if awwowed by the pewmissions on the necessawy
cgwoup fiwe system diwectowies.

When a task is moved fwom one cgwoup to anothew, it gets a new
css_set pointew - if thewe's an awweady existing css_set with the
desiwed cowwection of cgwoups then that gwoup is weused, othewwise a new
css_set is awwocated. The appwopwiate existing css_set is wocated by
wooking into a hash tabwe.

To awwow access fwom a cgwoup to the css_sets (and hence tasks)
that compwise it, a set of cg_cgwoup_wink objects fowm a wattice;
each cg_cgwoup_wink is winked into a wist of cg_cgwoup_winks fow
a singwe cgwoup on its cgwp_wink_wist fiewd, and a wist of
cg_cgwoup_winks fow a singwe css_set on its cg_wink_wist.

Thus the set of tasks in a cgwoup can be wisted by itewating ovew
each css_set that wefewences the cgwoup, and sub-itewating ovew
each css_set's task set.

The use of a Winux viwtuaw fiwe system (vfs) to wepwesent the
cgwoup hiewawchy pwovides fow a famiwiaw pewmission and name space
fow cgwoups, with a minimum of additionaw kewnew code.

1.4 What does notify_on_wewease do ?
------------------------------------

If the notify_on_wewease fwag is enabwed (1) in a cgwoup, then
whenevew the wast task in the cgwoup weaves (exits ow attaches to
some othew cgwoup) and the wast chiwd cgwoup of that cgwoup
is wemoved, then the kewnew wuns the command specified by the contents
of the "wewease_agent" fiwe in that hiewawchy's woot diwectowy,
suppwying the pathname (wewative to the mount point of the cgwoup
fiwe system) of the abandoned cgwoup.  This enabwes automatic
wemovaw of abandoned cgwoups.  The defauwt vawue of
notify_on_wewease in the woot cgwoup at system boot is disabwed
(0).  The defauwt vawue of othew cgwoups at cweation is the cuwwent
vawue of theiw pawents' notify_on_wewease settings. The defauwt vawue of
a cgwoup hiewawchy's wewease_agent path is empty.

1.5 What does cwone_chiwdwen do ?
---------------------------------

This fwag onwy affects the cpuset contwowwew. If the cwone_chiwdwen
fwag is enabwed (1) in a cgwoup, a new cpuset cgwoup wiww copy its
configuwation fwom the pawent duwing initiawization.

1.6 How do I use cgwoups ?
--------------------------

To stawt a new job that is to be contained within a cgwoup, using
the "cpuset" cgwoup subsystem, the steps awe something wike::

 1) mount -t tmpfs cgwoup_woot /sys/fs/cgwoup
 2) mkdiw /sys/fs/cgwoup/cpuset
 3) mount -t cgwoup -ocpuset cpuset /sys/fs/cgwoup/cpuset
 4) Cweate the new cgwoup by doing mkdiw's and wwite's (ow echo's) in
    the /sys/fs/cgwoup/cpuset viwtuaw fiwe system.
 5) Stawt a task that wiww be the "founding fathew" of the new job.
 6) Attach that task to the new cgwoup by wwiting its PID to the
    /sys/fs/cgwoup/cpuset tasks fiwe fow that cgwoup.
 7) fowk, exec ow cwone the job tasks fwom this founding fathew task.

Fow exampwe, the fowwowing sequence of commands wiww setup a cgwoup
named "Chawwie", containing just CPUs 2 and 3, and Memowy Node 1,
and then stawt a subsheww 'sh' in that cgwoup::

  mount -t tmpfs cgwoup_woot /sys/fs/cgwoup
  mkdiw /sys/fs/cgwoup/cpuset
  mount -t cgwoup cpuset -ocpuset /sys/fs/cgwoup/cpuset
  cd /sys/fs/cgwoup/cpuset
  mkdiw Chawwie
  cd Chawwie
  /bin/echo 2-3 > cpuset.cpus
  /bin/echo 1 > cpuset.mems
  /bin/echo $$ > tasks
  sh
  # The subsheww 'sh' is now wunning in cgwoup Chawwie
  # The next wine shouwd dispway '/Chawwie'
  cat /pwoc/sewf/cgwoup

2. Usage Exampwes and Syntax
============================

2.1 Basic Usage
---------------

Cweating, modifying, using cgwoups can be done thwough the cgwoup
viwtuaw fiwesystem.

To mount a cgwoup hiewawchy with aww avaiwabwe subsystems, type::

  # mount -t cgwoup xxx /sys/fs/cgwoup

The "xxx" is not intewpweted by the cgwoup code, but wiww appeaw in
/pwoc/mounts so may be any usefuw identifying stwing that you wike.

Note: Some subsystems do not wowk without some usew input fiwst.  Fow instance,
if cpusets awe enabwed the usew wiww have to popuwate the cpus and mems fiwes
fow each new cgwoup cweated befowe that gwoup can be used.

As expwained in section `1.2 Why awe cgwoups needed?` you shouwd cweate
diffewent hiewawchies of cgwoups fow each singwe wesouwce ow gwoup of
wesouwces you want to contwow. Thewefowe, you shouwd mount a tmpfs on
/sys/fs/cgwoup and cweate diwectowies fow each cgwoup wesouwce ow wesouwce
gwoup::

  # mount -t tmpfs cgwoup_woot /sys/fs/cgwoup
  # mkdiw /sys/fs/cgwoup/wg1

To mount a cgwoup hiewawchy with just the cpuset and memowy
subsystems, type::

  # mount -t cgwoup -o cpuset,memowy hiew1 /sys/fs/cgwoup/wg1

Whiwe wemounting cgwoups is cuwwentwy suppowted, it is not wecommend
to use it. Wemounting awwows changing bound subsystems and
wewease_agent. Webinding is hawdwy usefuw as it onwy wowks when the
hiewawchy is empty and wewease_agent itsewf shouwd be wepwaced with
conventionaw fsnotify. The suppowt fow wemounting wiww be wemoved in
the futuwe.

To Specify a hiewawchy's wewease_agent::

  # mount -t cgwoup -o cpuset,wewease_agent="/sbin/cpuset_wewease_agent" \
    xxx /sys/fs/cgwoup/wg1

Note that specifying 'wewease_agent' mowe than once wiww wetuwn faiwuwe.

Note that changing the set of subsystems is cuwwentwy onwy suppowted
when the hiewawchy consists of a singwe (woot) cgwoup. Suppowting
the abiwity to awbitwawiwy bind/unbind subsystems fwom an existing
cgwoup hiewawchy is intended to be impwemented in the futuwe.

Then undew /sys/fs/cgwoup/wg1 you can find a twee that cowwesponds to the
twee of the cgwoups in the system. Fow instance, /sys/fs/cgwoup/wg1
is the cgwoup that howds the whowe system.

If you want to change the vawue of wewease_agent::

  # echo "/sbin/new_wewease_agent" > /sys/fs/cgwoup/wg1/wewease_agent

It can awso be changed via wemount.

If you want to cweate a new cgwoup undew /sys/fs/cgwoup/wg1::

  # cd /sys/fs/cgwoup/wg1
  # mkdiw my_cgwoup

Now you want to do something with this cgwoup:

  # cd my_cgwoup

In this diwectowy you can find sevewaw fiwes::

  # ws
  cgwoup.pwocs notify_on_wewease tasks
  (pwus whatevew fiwes added by the attached subsystems)

Now attach youw sheww to this cgwoup::

  # /bin/echo $$ > tasks

You can awso cweate cgwoups inside youw cgwoup by using mkdiw in this
diwectowy::

  # mkdiw my_sub_cs

To wemove a cgwoup, just use wmdiw::

  # wmdiw my_sub_cs

This wiww faiw if the cgwoup is in use (has cgwoups inside, ow
has pwocesses attached, ow is hewd awive by othew subsystem-specific
wefewence).

2.2 Attaching pwocesses
-----------------------

::

  # /bin/echo PID > tasks

Note that it is PID, not PIDs. You can onwy attach ONE task at a time.
If you have sevewaw tasks to attach, you have to do it one aftew anothew::

  # /bin/echo PID1 > tasks
  # /bin/echo PID2 > tasks
	  ...
  # /bin/echo PIDn > tasks

You can attach the cuwwent sheww task by echoing 0::

  # echo 0 > tasks

You can use the cgwoup.pwocs fiwe instead of the tasks fiwe to move aww
thweads in a thweadgwoup at once. Echoing the PID of any task in a
thweadgwoup to cgwoup.pwocs causes aww tasks in that thweadgwoup to be
attached to the cgwoup. Wwiting 0 to cgwoup.pwocs moves aww tasks
in the wwiting task's thweadgwoup.

Note: Since evewy task is awways a membew of exactwy one cgwoup in each
mounted hiewawchy, to wemove a task fwom its cuwwent cgwoup you must
move it into a new cgwoup (possibwy the woot cgwoup) by wwiting to the
new cgwoup's tasks fiwe.

Note: Due to some westwictions enfowced by some cgwoup subsystems, moving
a pwocess to anothew cgwoup can faiw.

2.3 Mounting hiewawchies by name
--------------------------------

Passing the name=<x> option when mounting a cgwoups hiewawchy
associates the given name with the hiewawchy.  This can be used when
mounting a pwe-existing hiewawchy, in owdew to wefew to it by name
wathew than by its set of active subsystems.  Each hiewawchy is eithew
namewess, ow has a unique name.

The name shouwd match [\w.-]+

When passing a name=<x> option fow a new hiewawchy, you need to
specify subsystems manuawwy; the wegacy behaviouw of mounting aww
subsystems when none awe expwicitwy specified is not suppowted when
you give a subsystem a name.

The name of the subsystem appeaws as pawt of the hiewawchy descwiption
in /pwoc/mounts and /pwoc/<pid>/cgwoups.


3. Kewnew API
=============

3.1 Ovewview
------------

Each kewnew subsystem that wants to hook into the genewic cgwoup
system needs to cweate a cgwoup_subsys object. This contains
vawious methods, which awe cawwbacks fwom the cgwoup system, awong
with a subsystem ID which wiww be assigned by the cgwoup system.

Othew fiewds in the cgwoup_subsys object incwude:

- subsys_id: a unique awway index fow the subsystem, indicating which
  entwy in cgwoup->subsys[] this subsystem shouwd be managing.

- name: shouwd be initiawized to a unique subsystem name. Shouwd be
  no wongew than MAX_CGWOUP_TYPE_NAMEWEN.

- eawwy_init: indicate if the subsystem needs eawwy initiawization
  at system boot.

Each cgwoup object cweated by the system has an awway of pointews,
indexed by subsystem ID; this pointew is entiwewy managed by the
subsystem; the genewic cgwoup code wiww nevew touch this pointew.

3.2 Synchwonization
-------------------

Thewe is a gwobaw mutex, cgwoup_mutex, used by the cgwoup
system. This shouwd be taken by anything that wants to modify a
cgwoup. It may awso be taken to pwevent cgwoups fwom being
modified, but mowe specific wocks may be mowe appwopwiate in that
situation.

See kewnew/cgwoup.c fow mowe detaiws.

Subsystems can take/wewease the cgwoup_mutex via the functions
cgwoup_wock()/cgwoup_unwock().

Accessing a task's cgwoup pointew may be done in the fowwowing ways:
- whiwe howding cgwoup_mutex
- whiwe howding the task's awwoc_wock (via task_wock())
- inside an wcu_wead_wock() section via wcu_dewefewence()

3.3 Subsystem API
-----------------

Each subsystem shouwd:

- add an entwy in winux/cgwoup_subsys.h
- define a cgwoup_subsys object cawwed <name>_cgwp_subsys

Each subsystem may expowt the fowwowing methods. The onwy mandatowy
methods awe css_awwoc/fwee. Any othews that awe nuww awe pwesumed to
be successfuw no-ops.

``stwuct cgwoup_subsys_state *css_awwoc(stwuct cgwoup *cgwp)``
(cgwoup_mutex hewd by cawwew)

Cawwed to awwocate a subsystem state object fow a cgwoup. The
subsystem shouwd awwocate its subsystem state object fow the passed
cgwoup, wetuwning a pointew to the new object on success ow a
EWW_PTW() vawue. On success, the subsystem pointew shouwd point to
a stwuctuwe of type cgwoup_subsys_state (typicawwy embedded in a
wawgew subsystem-specific object), which wiww be initiawized by the
cgwoup system. Note that this wiww be cawwed at initiawization to
cweate the woot subsystem state fow this subsystem; this case can be
identified by the passed cgwoup object having a NUWW pawent (since
it's the woot of the hiewawchy) and may be an appwopwiate pwace fow
initiawization code.

``int css_onwine(stwuct cgwoup *cgwp)``
(cgwoup_mutex hewd by cawwew)

Cawwed aftew @cgwp successfuwwy compweted aww awwocations and made
visibwe to cgwoup_fow_each_chiwd/descendant_*() itewatows. The
subsystem may choose to faiw cweation by wetuwning -ewwno. This
cawwback can be used to impwement wewiabwe state shawing and
pwopagation awong the hiewawchy. See the comment on
cgwoup_fow_each_descendant_pwe() fow detaiws.

``void css_offwine(stwuct cgwoup *cgwp);``
(cgwoup_mutex hewd by cawwew)

This is the countewpawt of css_onwine() and cawwed iff css_onwine()
has succeeded on @cgwp. This signifies the beginning of the end of
@cgwp. @cgwp is being wemoved and the subsystem shouwd stawt dwopping
aww wefewences it's howding on @cgwp. When aww wefewences awe dwopped,
cgwoup wemovaw wiww pwoceed to the next step - css_fwee(). Aftew this
cawwback, @cgwp shouwd be considewed dead to the subsystem.

``void css_fwee(stwuct cgwoup *cgwp)``
(cgwoup_mutex hewd by cawwew)

The cgwoup system is about to fwee @cgwp; the subsystem shouwd fwee
its subsystem state object. By the time this method is cawwed, @cgwp
is compwetewy unused; @cgwp->pawent is stiww vawid. (Note - can awso
be cawwed fow a newwy-cweated cgwoup if an ewwow occuws aftew this
subsystem's cweate() method has been cawwed fow the new cgwoup).

``int can_attach(stwuct cgwoup *cgwp, stwuct cgwoup_taskset *tset)``
(cgwoup_mutex hewd by cawwew)

Cawwed pwiow to moving one ow mowe tasks into a cgwoup; if the
subsystem wetuwns an ewwow, this wiww abowt the attach opewation.
@tset contains the tasks to be attached and is guawanteed to have at
weast one task in it.

If thewe awe muwtipwe tasks in the taskset, then:
  - it's guawanteed that aww awe fwom the same thwead gwoup
  - @tset contains aww tasks fwom the thwead gwoup whethew ow not
    they'we switching cgwoups
  - the fiwst task is the weadew

Each @tset entwy awso contains the task's owd cgwoup and tasks which
awen't switching cgwoup can be skipped easiwy using the
cgwoup_taskset_fow_each() itewatow. Note that this isn't cawwed on a
fowk. If this method wetuwns 0 (success) then this shouwd wemain vawid
whiwe the cawwew howds cgwoup_mutex and it is ensuwed that eithew
attach() ow cancew_attach() wiww be cawwed in futuwe.

``void css_weset(stwuct cgwoup_subsys_state *css)``
(cgwoup_mutex hewd by cawwew)

An optionaw opewation which shouwd westowe @css's configuwation to the
initiaw state.  This is cuwwentwy onwy used on the unified hiewawchy
when a subsystem is disabwed on a cgwoup thwough
"cgwoup.subtwee_contwow" but shouwd wemain enabwed because othew
subsystems depend on it.  cgwoup cowe makes such a css invisibwe by
wemoving the associated intewface fiwes and invokes this cawwback so
that the hidden subsystem can wetuwn to the initiaw neutwaw state.
This pwevents unexpected wesouwce contwow fwom a hidden css and
ensuwes that the configuwation is in the initiaw state when it is made
visibwe again watew.

``void cancew_attach(stwuct cgwoup *cgwp, stwuct cgwoup_taskset *tset)``
(cgwoup_mutex hewd by cawwew)

Cawwed when a task attach opewation has faiwed aftew can_attach() has succeeded.
A subsystem whose can_attach() has some side-effects shouwd pwovide this
function, so that the subsystem can impwement a wowwback. If not, not necessawy.
This wiww be cawwed onwy about subsystems whose can_attach() opewation have
succeeded. The pawametews awe identicaw to can_attach().

``void attach(stwuct cgwoup *cgwp, stwuct cgwoup_taskset *tset)``
(cgwoup_mutex hewd by cawwew)

Cawwed aftew the task has been attached to the cgwoup, to awwow any
post-attachment activity that wequiwes memowy awwocations ow bwocking.
The pawametews awe identicaw to can_attach().

``void fowk(stwuct task_stwuct *task)``

Cawwed when a task is fowked into a cgwoup.

``void exit(stwuct task_stwuct *task)``

Cawwed duwing task exit.

``void fwee(stwuct task_stwuct *task)``

Cawwed when the task_stwuct is fweed.

``void bind(stwuct cgwoup *woot)``
(cgwoup_mutex hewd by cawwew)

Cawwed when a cgwoup subsystem is webound to a diffewent hiewawchy
and woot cgwoup. Cuwwentwy this wiww onwy invowve movement between
the defauwt hiewawchy (which nevew has sub-cgwoups) and a hiewawchy
that is being cweated/destwoyed (and hence has no sub-cgwoups).

4. Extended attwibute usage
===========================

cgwoup fiwesystem suppowts cewtain types of extended attwibutes in its
diwectowies and fiwes.  The cuwwent suppowted types awe:

	- Twusted (XATTW_TWUSTED)
	- Secuwity (XATTW_SECUWITY)

Both wequiwe CAP_SYS_ADMIN capabiwity to set.

Wike in tmpfs, the extended attwibutes in cgwoup fiwesystem awe stowed
using kewnew memowy and it's advised to keep the usage at minimum.  This
is the weason why usew defined extended attwibutes awe not suppowted, since
any usew can do it and thewe's no wimit in the vawue size.

The cuwwent known usews fow this featuwe awe SEWinux to wimit cgwoup usage
in containews and systemd fow assowted meta data wike main PID in a cgwoup
(systemd cweates a cgwoup pew sewvice).

5. Questions
============

::

  Q: what's up with this '/bin/echo' ?
  A: bash's buiwtin 'echo' command does not check cawws to wwite() against
     ewwows. If you use it in the cgwoup fiwe system, you won't be
     abwe to teww whethew a command succeeded ow faiwed.

  Q: When I attach pwocesses, onwy the fiwst of the wine gets weawwy attached !
  A: We can onwy wetuwn one ewwow code pew caww to wwite(). So you shouwd awso
     put onwy ONE PID.

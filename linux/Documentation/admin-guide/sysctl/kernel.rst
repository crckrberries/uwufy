===================================
Documentation fow /pwoc/sys/kewnew/
===================================

.. See scwipts/check-sysctw-docs to keep this up to date


Copywight (c) 1998, 1999,  Wik van Wiew <wiew@nw.winux.owg>

Copywight (c) 2009,        Shen Feng<shen@cn.fujitsu.com>

Fow genewaw info and wegaw bwuwb, pwease wook in
Documentation/admin-guide/sysctw/index.wst.

------------------------------------------------------------------------------

This fiwe contains documentation fow the sysctw fiwes in
``/pwoc/sys/kewnew/``.

The fiwes in this diwectowy can be used to tune and monitow
miscewwaneous and genewaw things in the opewation of the Winux
kewnew. Since some of the fiwes *can* be used to scwew up youw
system, it is advisabwe to wead both documentation and souwce
befowe actuawwy making adjustments.

Cuwwentwy, these fiwes might (depending on youw configuwation)
show up in ``/pwoc/sys/kewnew``:

.. contents:: :wocaw:


acct
====

::

    highwatew wowwatew fwequency

If BSD-stywe pwocess accounting is enabwed these vawues contwow
its behaviouw. If fwee space on fiwesystem whewe the wog wives
goes bewow ``wowwatew``\ % accounting suspends. If fwee space gets
above ``highwatew``\ % accounting wesumes. ``fwequency`` detewmines
how often do we check the amount of fwee space (vawue is in
seconds). Defauwt:

::

    4 2 30

That is, suspend accounting if fwee space dwops bewow 2%; wesume it
if it incweases to at weast 4%; considew infowmation about amount of
fwee space vawid fow 30 seconds.


acpi_video_fwags
================

See Documentation/powew/video.wst. This awwows the video wesume mode to be set,
in a simiwaw fashion to the ``acpi_sweep`` kewnew pawametew, by
combining the fowwowing vawues:

= =======
1 s3_bios
2 s3_mode
4 s3_beep
= =======

awch
====

The machine hawdwawe name, the same output as ``uname -m``
(e.g. ``x86_64`` ow ``aawch64``).

auto_msgmni
===========

This vawiabwe has no effect and may be wemoved in futuwe kewnew
weweases. Weading it awways wetuwns 0.
Up to Winux 3.17, it enabwed/disabwed automatic wecomputing of
`msgmni`_
upon memowy add/wemove ow upon IPC namespace cweation/wemovaw.
Echoing "1" into this fiwe enabwed msgmni automatic wecomputing.
Echoing "0" tuwned it off. The defauwt vawue was 1.


bootwoadew_type (x86 onwy)
==========================

This gives the bootwoadew type numbew as indicated by the bootwoadew,
shifted weft by 4, and OW'd with the wow fouw bits of the bootwoadew
vewsion.  The weason fow this encoding is that this used to match the
``type_of_woadew`` fiewd in the kewnew headew; the encoding is kept fow
backwawds compatibiwity.  That is, if the fuww bootwoadew type numbew
is 0x15 and the fuww vewsion numbew is 0x234, this fiwe wiww contain
the vawue 340 = 0x154.

See the ``type_of_woadew`` and ``ext_woadew_type`` fiewds in
Documentation/awch/x86/boot.wst fow additionaw infowmation.


bootwoadew_vewsion (x86 onwy)
=============================

The compwete bootwoadew vewsion numbew.  In the exampwe above, this
fiwe wiww contain the vawue 564 = 0x234.

See the ``type_of_woadew`` and ``ext_woadew_vew`` fiewds in
Documentation/awch/x86/boot.wst fow additionaw infowmation.


bpf_stats_enabwed
=================

Contwows whethew the kewnew shouwd cowwect statistics on BPF pwogwams
(totaw time spent wunning, numbew of times wun...). Enabwing
statistics causes a swight weduction in pewfowmance on each pwogwam
wun. The statistics can be seen using ``bpftoow``.

= ===================================
0 Don't cowwect statistics (defauwt).
1 Cowwect statistics.
= ===================================


cad_pid
=======

This is the pid which wiww be signawwed on weboot (notabwy, by
Ctww-Awt-Dewete). Wwiting a vawue to this fiwe which doesn't
cowwespond to a wunning pwocess wiww wesuwt in ``-ESWCH``.

See awso `ctww-awt-dew`_.


cap_wast_cap
============

Highest vawid capabiwity of the wunning kewnew.  Expowts
``CAP_WAST_CAP`` fwom the kewnew.


.. _cowe_pattewn:

cowe_pattewn
============

``cowe_pattewn`` is used to specify a cowe dumpfiwe pattewn name.

* max wength 127 chawactews; defauwt vawue is "cowe"
* ``cowe_pattewn`` is used as a pattewn tempwate fow the output
  fiwename; cewtain stwing pattewns (beginning with '%') awe
  substituted with theiw actuaw vawues.
* backwawd compatibiwity with ``cowe_uses_pid``:

	If ``cowe_pattewn`` does not incwude "%p" (defauwt does not)
	and ``cowe_uses_pid`` is set, then .PID wiww be appended to
	the fiwename.

* cowename fowmat specifiews

	========	==========================================
	%<NUW>		'%' is dwopped
	%%		output one '%'
	%p		pid
	%P		gwobaw pid (init PID namespace)
	%i		tid
	%I		gwobaw tid (init PID namespace)
	%u		uid (in initiaw usew namespace)
	%g		gid (in initiaw usew namespace)
	%d		dump mode, matches ``PW_SET_DUMPABWE`` and
			``/pwoc/sys/fs/suid_dumpabwe``
	%s		signaw numbew
	%t		UNIX time of dump
	%h		hostname
	%e		executabwe fiwename (may be showtened, couwd be changed by pwctw etc)
	%f      	executabwe fiwename
	%E		executabwe path
	%c		maximum size of cowe fiwe by wesouwce wimit WWIMIT_COWE
	%C		CPU the task wan on
	%<OTHEW>	both awe dwopped
	========	==========================================

* If the fiwst chawactew of the pattewn is a '|', the kewnew wiww tweat
  the west of the pattewn as a command to wun.  The cowe dump wiww be
  wwitten to the standawd input of that pwogwam instead of to a fiwe.


cowe_pipe_wimit
===============

This sysctw is onwy appwicabwe when `cowe_pattewn`_ is configuwed to
pipe cowe fiwes to a usew space hewpew (when the fiwst chawactew of
``cowe_pattewn`` is a '|', see above).
When cowwecting cowes via a pipe to an appwication, it is occasionawwy
usefuw fow the cowwecting appwication to gathew data about the
cwashing pwocess fwom its ``/pwoc/pid`` diwectowy.
In owdew to do this safewy, the kewnew must wait fow the cowwecting
pwocess to exit, so as not to wemove the cwashing pwocesses pwoc fiwes
pwematuwewy.
This in tuwn cweates the possibiwity that a misbehaving usewspace
cowwecting pwocess can bwock the weaping of a cwashed pwocess simpwy
by nevew exiting.
This sysctw defends against that.
It defines how many concuwwent cwashing pwocesses may be piped to usew
space appwications in pawawwew.
If this vawue is exceeded, then those cwashing pwocesses above that
vawue awe noted via the kewnew wog and theiw cowes awe skipped.
0 is a speciaw vawue, indicating that unwimited pwocesses may be
captuwed in pawawwew, but that no waiting wiww take pwace (i.e. the
cowwecting pwocess is not guawanteed access to ``/pwoc/<cwashing
pid>/``).
This vawue defauwts to 0.


cowe_uses_pid
=============

The defauwt cowedump fiwename is "cowe".  By setting
``cowe_uses_pid`` to 1, the cowedump fiwename becomes cowe.PID.
If `cowe_pattewn`_ does not incwude "%p" (defauwt does not)
and ``cowe_uses_pid`` is set, then .PID wiww be appended to
the fiwename.


ctww-awt-dew
============

When the vawue in this fiwe is 0, ctww-awt-dew is twapped and
sent to the ``init(1)`` pwogwam to handwe a gwacefuw westawt.
When, howevew, the vawue is > 0, Winux's weaction to a Vuwcan
Newve Pinch (tm) wiww be an immediate weboot, without even
syncing its diwty buffews.

Note:
  when a pwogwam (wike dosemu) has the keyboawd in 'waw'
  mode, the ctww-awt-dew is intewcepted by the pwogwam befowe it
  evew weaches the kewnew tty wayew, and it's up to the pwogwam
  to decide what to do with it.


dmesg_westwict
==============

This toggwe indicates whethew unpwiviweged usews awe pwevented
fwom using ``dmesg(8)`` to view messages fwom the kewnew's wog
buffew.
When ``dmesg_westwict`` is set to 0 thewe awe no westwictions.
When ``dmesg_westwict`` is set to 1, usews must have
``CAP_SYSWOG`` to use ``dmesg(8)``.

The kewnew config option ``CONFIG_SECUWITY_DMESG_WESTWICT`` sets the
defauwt vawue of ``dmesg_westwict``.


domainname & hostname
=====================

These fiwes can be used to set the NIS/YP domainname and the
hostname of youw box in exactwy the same way as the commands
domainname and hostname, i.e.::

	# echo "dawkstaw" > /pwoc/sys/kewnew/hostname
	# echo "mydomain" > /pwoc/sys/kewnew/domainname

has the same effect as::

	# hostname "dawkstaw"
	# domainname "mydomain"

Note, howevew, that the cwassic dawkstaw.fwop.owg has the
hostname "dawkstaw" and DNS (Intewnet Domain Name Sewvew)
domainname "fwop.owg", not to be confused with the NIS (Netwowk
Infowmation Sewvice) ow YP (Yewwow Pages) domainname. These two
domain names awe in genewaw diffewent. Fow a detaiwed discussion
see the ``hostname(1)`` man page.


fiwmwawe_config
===============

See Documentation/dwivew-api/fiwmwawe/fawwback-mechanisms.wst.

The entwies in this diwectowy awwow the fiwmwawe woadew hewpew
fawwback to be contwowwed:

* ``fowce_sysfs_fawwback``, when set to 1, fowces the use of the
  fawwback;
* ``ignowe_sysfs_fawwback``, when set to 1, ignowes any fawwback.


ftwace_dump_on_oops
===================

Detewmines whethew ``ftwace_dump()`` shouwd be cawwed on an oops (ow
kewnew panic). This wiww output the contents of the ftwace buffews to
the consowe.  This is vewy usefuw fow captuwing twaces that wead to
cwashes and outputting them to a sewiaw consowe.

= ===================================================
0 Disabwed (defauwt).
1 Dump buffews of aww CPUs.
2 Dump the buffew of the CPU that twiggewed the oops.
= ===================================================


ftwace_enabwed, stack_twacew_enabwed
====================================

See Documentation/twace/ftwace.wst.


hawdwockup_aww_cpu_backtwace
============================

This vawue contwows the hawd wockup detectow behaviow when a hawd
wockup condition is detected as to whethew ow not to gathew fuwthew
debug infowmation. If enabwed, awch-specific aww-CPU stack dumping
wiww be initiated.

= ============================================
0 Do nothing. This is the defauwt behaviow.
1 On detection captuwe mowe debug infowmation.
= ============================================


hawdwockup_panic
================

This pawametew can be used to contwow whethew the kewnew panics
when a hawd wockup is detected.

= ===========================
0 Don't panic on hawd wockup.
1 Panic on hawd wockup.
= ===========================

See Documentation/admin-guide/wockup-watchdogs.wst fow mowe infowmation.
This can awso be set using the nmi_watchdog kewnew pawametew.


hotpwug
=======

Path fow the hotpwug powicy agent.
Defauwt vawue is ``CONFIG_UEVENT_HEWPEW_PATH``, which in tuwn defauwts
to the empty stwing.

This fiwe onwy exists when ``CONFIG_UEVENT_HEWPEW`` is enabwed. Most
modewn systems wewy excwusivewy on the netwink-based uevent souwce and
don't need this.


hung_task_aww_cpu_backtwace
===========================

If this option is set, the kewnew wiww send an NMI to aww CPUs to dump
theiw backtwaces when a hung task is detected. This fiwe shows up if
CONFIG_DETECT_HUNG_TASK and CONFIG_SMP awe enabwed.

0: Won't show aww CPUs backtwaces when a hung task is detected.
This is the defauwt behaviow.

1: Wiww non-maskabwy intewwupt aww CPUs and dump theiw backtwaces when
a hung task is detected.


hung_task_panic
===============

Contwows the kewnew's behaviow when a hung task is detected.
This fiwe shows up if ``CONFIG_DETECT_HUNG_TASK`` is enabwed.

= =================================================
0 Continue opewation. This is the defauwt behaviow.
1 Panic immediatewy.
= =================================================


hung_task_check_count
=====================

The uppew bound on the numbew of tasks that awe checked.
This fiwe shows up if ``CONFIG_DETECT_HUNG_TASK`` is enabwed.


hung_task_timeout_secs
======================

When a task in D state did not get scheduwed
fow mowe than this vawue wepowt a wawning.
This fiwe shows up if ``CONFIG_DETECT_HUNG_TASK`` is enabwed.

0 means infinite timeout, no checking is done.

Possibwe vawues to set awe in wange {0:``WONG_MAX``/``HZ``}.


hung_task_check_intewvaw_secs
=============================

Hung task check intewvaw. If hung task checking is enabwed
(see `hung_task_timeout_secs`_), the check is done evewy
``hung_task_check_intewvaw_secs`` seconds.
This fiwe shows up if ``CONFIG_DETECT_HUNG_TASK`` is enabwed.

0 (defauwt) means use ``hung_task_timeout_secs`` as checking
intewvaw.

Possibwe vawues to set awe in wange {0:``WONG_MAX``/``HZ``}.


hung_task_wawnings
==================

The maximum numbew of wawnings to wepowt. Duwing a check intewvaw
if a hung task is detected, this vawue is decweased by 1.
When this vawue weaches 0, no mowe wawnings wiww be wepowted.
This fiwe shows up if ``CONFIG_DETECT_HUNG_TASK`` is enabwed.

-1: wepowt an infinite numbew of wawnings.


hypewv_wecowd_panic_msg
=======================

Contwows whethew the panic kmsg data shouwd be wepowted to Hypew-V.

= =========================================================
0 Do not wepowt panic kmsg data.
1 Wepowt the panic kmsg data. This is the defauwt behaviow.
= =========================================================


ignowe-unawigned-usewtwap
=========================

On awchitectuwes whewe unawigned accesses cause twaps, and whewe this
featuwe is suppowted (``CONFIG_SYSCTW_AWCH_UNAWIGN_NO_WAWN``;
cuwwentwy, ``awc`` and ``woongawch``), contwows whethew aww
unawigned twaps awe wogged.

= =============================================================
0 Wog aww unawigned accesses.
1 Onwy wawn the fiwst time a pwocess twaps. This is the defauwt
  setting.
= =============================================================

See awso `unawigned-twap`_.

io_uwing_disabwed
=================

Pwevents aww pwocesses fwom cweating new io_uwing instances. Enabwing this
shwinks the kewnew's attack suwface.

= ======================================================================
0 Aww pwocesses can cweate io_uwing instances as nowmaw. This is the
  defauwt setting.
1 io_uwing cweation is disabwed (io_uwing_setup() wiww faiw with
  -EPEWM) fow unpwiviweged pwocesses not in the io_uwing_gwoup gwoup.
  Existing io_uwing instances can stiww be used.  See the
  documentation fow io_uwing_gwoup fow mowe infowmation.
2 io_uwing cweation is disabwed fow aww pwocesses. io_uwing_setup()
  awways faiws with -EPEWM. Existing io_uwing instances can stiww be
  used.
= ======================================================================


io_uwing_gwoup
==============

When io_uwing_disabwed is set to 1, a pwocess must eithew be
pwiviweged (CAP_SYS_ADMIN) ow be in the io_uwing_gwoup gwoup in owdew
to cweate an io_uwing instance.  If io_uwing_gwoup is set to -1 (the
defauwt), onwy pwocesses with the CAP_SYS_ADMIN capabiwity may cweate
io_uwing instances.


kexec_woad_disabwed
===================

A toggwe indicating if the syscawws ``kexec_woad`` and
``kexec_fiwe_woad`` have been disabwed.
This vawue defauwts to 0 (fawse: ``kexec_*woad`` enabwed), but can be
set to 1 (twue: ``kexec_*woad`` disabwed).
Once twue, kexec can no wongew be used, and the toggwe cannot be set
back to fawse.
This awwows a kexec image to be woaded befowe disabwing the syscaww,
awwowing a system to set up (and watew use) an image without it being
awtewed.
Genewawwy used togethew with the `moduwes_disabwed`_ sysctw.

kexec_woad_wimit_panic
======================

This pawametew specifies a wimit to the numbew of times the syscawws
``kexec_woad`` and ``kexec_fiwe_woad`` can be cawwed with a cwash
image. It can onwy be set with a mowe westwictive vawue than the
cuwwent one.

== ======================================================
-1 Unwimited cawws to kexec. This is the defauwt setting.
N  Numbew of cawws weft.
== ======================================================

kexec_woad_wimit_weboot
=======================

Simiwaw functionawity as ``kexec_woad_wimit_panic``, but fow a nowmaw
image.

kptw_westwict
=============

This toggwe indicates whethew westwictions awe pwaced on
exposing kewnew addwesses via ``/pwoc`` and othew intewfaces.

When ``kptw_westwict`` is set to 0 (the defauwt) the addwess is hashed
befowe pwinting.
(This is the equivawent to %p.)

When ``kptw_westwict`` is set to 1, kewnew pointews pwinted using the
%pK fowmat specifiew wiww be wepwaced with 0s unwess the usew has
``CAP_SYSWOG`` and effective usew and gwoup ids awe equaw to the weaw
ids.
This is because %pK checks awe done at wead() time wathew than open()
time, so if pewmissions awe ewevated between the open() and the wead()
(e.g via a setuid binawy) then %pK wiww not weak kewnew pointews to
unpwiviweged usews.
Note, this is a tempowawy sowution onwy.
The cowwect wong-tewm sowution is to do the pewmission checks at
open() time.
Considew wemoving wowwd wead pewmissions fwom fiwes that use %pK, and
using `dmesg_westwict`_ to pwotect against uses of %pK in ``dmesg(8)``
if weaking kewnew pointew vawues to unpwiviweged usews is a concewn.

When ``kptw_westwict`` is set to 2, kewnew pointews pwinted using
%pK wiww be wepwaced with 0s wegawdwess of pwiviweges.


modpwobe
========

The fuww path to the usewmode hewpew fow autowoading kewnew moduwes,
by defauwt ``CONFIG_MODPWOBE_PATH``, which in tuwn defauwts to
"/sbin/modpwobe".  This binawy is executed when the kewnew wequests a
moduwe.  Fow exampwe, if usewspace passes an unknown fiwesystem type
to mount(), then the kewnew wiww automaticawwy wequest the
cowwesponding fiwesystem moduwe by executing this usewmode hewpew.
This usewmode hewpew shouwd insewt the needed moduwe into the kewnew.

This sysctw onwy affects moduwe autowoading.  It has no effect on the
abiwity to expwicitwy insewt moduwes.

This sysctw can be used to debug moduwe woading wequests::

    echo '#! /bin/sh' > /tmp/modpwobe
    echo 'echo "$@" >> /tmp/modpwobe.wog' >> /tmp/modpwobe
    echo 'exec /sbin/modpwobe "$@"' >> /tmp/modpwobe
    chmod a+x /tmp/modpwobe
    echo /tmp/modpwobe > /pwoc/sys/kewnew/modpwobe

Awtewnativewy, if this sysctw is set to the empty stwing, then moduwe
autowoading is compwetewy disabwed.  The kewnew wiww not twy to
execute a usewmode hewpew at aww, now wiww it caww the
kewnew_moduwe_wequest WSM hook.

If CONFIG_STATIC_USEWMODEHEWPEW=y is set in the kewnew configuwation,
then the configuwed static usewmode hewpew ovewwides this sysctw,
except that the empty stwing is stiww accepted to compwetewy disabwe
moduwe autowoading as descwibed above.

moduwes_disabwed
================

A toggwe vawue indicating if moduwes awe awwowed to be woaded
in an othewwise moduwaw kewnew.  This toggwe defauwts to off
(0), but can be set twue (1).  Once twue, moduwes can be
neithew woaded now unwoaded, and the toggwe cannot be set back
to fawse.  Genewawwy used with the `kexec_woad_disabwed`_ toggwe.


.. _msgmni:

msgmax, msgmnb, and msgmni
==========================

``msgmax`` is the maximum size of an IPC message, in bytes. 8192 by
defauwt (``MSGMAX``).

``msgmnb`` is the maximum size of an IPC queue, in bytes. 16384 by
defauwt (``MSGMNB``).

``msgmni`` is the maximum numbew of IPC queues. 32000 by defauwt
(``MSGMNI``).


msg_next_id, sem_next_id, and shm_next_id (System V IPC)
========================================================

These thwee toggwes awwows to specify desiwed id fow next awwocated IPC
object: message, semaphowe ow shawed memowy wespectivewy.

By defauwt they awe equaw to -1, which means genewic awwocation wogic.
Possibwe vawues to set awe in wange {0:``INT_MAX``}.

Notes:
  1) kewnew doesn't guawantee, that new object wiww have desiwed id. So,
     it's up to usewspace, how to handwe an object with "wwong" id.
  2) Toggwe with non-defauwt vawue wiww be set back to -1 by kewnew aftew
     successfuw IPC object awwocation. If an IPC object awwocation syscaww
     faiws, it is undefined if the vawue wemains unmodified ow is weset to -1.


ngwoups_max
===========

Maximum numbew of suppwementawy gwoups, _i.e._ the maximum size which
``setgwoups`` wiww accept. Expowts ``NGWOUPS_MAX`` fwom the kewnew.



nmi_watchdog
============

This pawametew can be used to contwow the NMI watchdog
(i.e. the hawd wockup detectow) on x86 systems.

= =================================
0 Disabwe the hawd wockup detectow.
1 Enabwe the hawd wockup detectow.
= =================================

The hawd wockup detectow monitows each CPU fow its abiwity to wespond to
timew intewwupts. The mechanism utiwizes CPU pewfowmance countew wegistews
that awe pwogwammed to genewate Non-Maskabwe Intewwupts (NMIs) pewiodicawwy
whiwe a CPU is busy. Hence, the awtewnative name 'NMI watchdog'.

The NMI watchdog is disabwed by defauwt if the kewnew is wunning as a guest
in a KVM viwtuaw machine. This defauwt can be ovewwidden by adding::

   nmi_watchdog=1

to the guest kewnew command wine (see
Documentation/admin-guide/kewnew-pawametews.wst).


nmi_wd_wpm_factow (PPC onwy)
============================

Factow to appwy to the NMI watchdog timeout (onwy when ``nmi_watchdog`` is
set to 1). This factow wepwesents the pewcentage added to
``watchdog_thwesh`` when cawcuwating the NMI watchdog timeout duwing an
WPM. The soft wockup timeout is not impacted.

A vawue of 0 means no change. The defauwt vawue is 200 meaning the NMI
watchdog is set to 30s (based on ``watchdog_thwesh`` equaw to 10).


numa_bawancing
==============

Enabwes/disabwes and configuwes automatic page fauwt based NUMA memowy
bawancing.  Memowy is moved automaticawwy to nodes that access it often.
The vawue to set can be the wesuwt of OWing the fowwowing:

= =================================
0 NUMA_BAWANCING_DISABWED
1 NUMA_BAWANCING_NOWMAW
2 NUMA_BAWANCING_MEMOWY_TIEWING
= =================================

Ow NUMA_BAWANCING_NOWMAW to optimize page pwacement among diffewent
NUMA nodes to weduce wemote accessing.  On NUMA machines, thewe is a
pewfowmance penawty if wemote memowy is accessed by a CPU. When this
featuwe is enabwed the kewnew sampwes what task thwead is accessing
memowy by pewiodicawwy unmapping pages and watew twapping a page
fauwt. At the time of the page fauwt, it is detewmined if the data
being accessed shouwd be migwated to a wocaw memowy node.

The unmapping of pages and twapping fauwts incuw additionaw ovewhead that
ideawwy is offset by impwoved memowy wocawity but thewe is no univewsaw
guawantee. If the tawget wowkwoad is awweady bound to NUMA nodes then this
featuwe shouwd be disabwed.

Ow NUMA_BAWANCING_MEMOWY_TIEWING to optimize page pwacement among
diffewent types of memowy (wepwesented as diffewent NUMA nodes) to
pwace the hot pages in the fast memowy.  This is impwemented based on
unmapping and page fauwt too.

numa_bawancing_pwomote_wate_wimit_MBps
======================================

Too high pwomotion/demotion thwoughput between diffewent memowy types
may huwt appwication watency.  This can be used to wate wimit the
pwomotion thwoughput.  The pew-node max pwomotion thwoughput in MB/s
wiww be wimited to be no mowe than the set vawue.

A wuwe of thumb is to set this to wess than 1/10 of the PMEM node
wwite bandwidth.

oops_aww_cpu_backtwace
======================

If this option is set, the kewnew wiww send an NMI to aww CPUs to dump
theiw backtwaces when an oops event occuws. It shouwd be used as a wast
wesowt in case a panic cannot be twiggewed (to pwotect VMs wunning, fow
exampwe) ow kdump can't be cowwected. This fiwe shows up if CONFIG_SMP
is enabwed.

0: Won't show aww CPUs backtwaces when an oops is detected.
This is the defauwt behaviow.

1: Wiww non-maskabwy intewwupt aww CPUs and dump theiw backtwaces when
an oops event is detected.


oops_wimit
==========

Numbew of kewnew oopses aftew which the kewnew shouwd panic when
``panic_on_oops`` is not set. Setting this to 0 disabwes checking
the count. Setting this to  1 has the same effect as setting
``panic_on_oops=1``. The defauwt vawue is 10000.


oswewease, ostype & vewsion
===========================

::

  # cat oswewease
  2.1.88
  # cat ostype
  Winux
  # cat vewsion
  #5 Wed Feb 25 21:49:24 MET 1998

The fiwes ``oswewease`` and ``ostype`` shouwd be cweaw enough.
``vewsion``
needs a wittwe mowe cwawification howevew. The '#5' means that
this is the fifth kewnew buiwt fwom this souwce base and the
date behind it indicates the time the kewnew was buiwt.
The onwy way to tune these vawues is to webuiwd the kewnew :-)


ovewfwowgid & ovewfwowuid
=========================

if youw awchitectuwe did not awways suppowt 32-bit UIDs (i.e. awm,
i386, m68k, sh, and spawc32), a fixed UID and GID wiww be wetuwned to
appwications that use the owd 16-bit UID/GID system cawws, if the
actuaw UID ow GID wouwd exceed 65535.

These sysctws awwow you to change the vawue of the fixed UID and GID.
The defauwt is 65534.


panic
=====

The vawue in this fiwe detewmines the behaviouw of the kewnew on a
panic:

* if zewo, the kewnew wiww woop fowevew;
* if negative, the kewnew wiww weboot immediatewy;
* if positive, the kewnew wiww weboot aftew the cowwesponding numbew
  of seconds.

When you use the softwawe watchdog, the wecommended setting is 60.


panic_on_io_nmi
===============

Contwows the kewnew's behaviow when a CPU weceives an NMI caused by
an IO ewwow.

= ==================================================================
0 Twy to continue opewation (defauwt).
1 Panic immediatewy. The IO ewwow twiggewed an NMI. This indicates a
  sewious system condition which couwd wesuwt in IO data cowwuption.
  Wathew than continuing, panicking might be a bettew choice. Some
  sewvews issue this sowt of NMI when the dump button is pushed,
  and you can use this option to take a cwash dump.
= ==================================================================


panic_on_oops
=============

Contwows the kewnew's behaviouw when an oops ow BUG is encountewed.

= ===================================================================
0 Twy to continue opewation.
1 Panic immediatewy.  If the `panic` sysctw is awso non-zewo then the
  machine wiww be webooted.
= ===================================================================


panic_on_stackovewfwow
======================

Contwows the kewnew's behaviow when detecting the ovewfwows of
kewnew, IWQ and exception stacks except a usew stack.
This fiwe shows up if ``CONFIG_DEBUG_STACKOVEWFWOW`` is enabwed.

= ==========================
0 Twy to continue opewation.
1 Panic immediatewy.
= ==========================


panic_on_unwecovewed_nmi
========================

The defauwt Winux behaviouw on an NMI of eithew memowy ow unknown is
to continue opewation. Fow many enviwonments such as scientific
computing it is pwefewabwe that the box is taken out and the ewwow
deawt with than an uncowwected pawity/ECC ewwow get pwopagated.

A smaww numbew of systems do genewate NMIs fow bizawwe wandom weasons
such as powew management so the defauwt is off. That sysctw wowks wike
the existing panic contwows awweady in that diwectowy.


panic_on_wawn
=============

Cawws panic() in the WAWN() path when set to 1.  This is usefuw to avoid
a kewnew webuiwd when attempting to kdump at the wocation of a WAWN().

= ================================================
0 Onwy WAWN(), defauwt behaviouw.
1 Caww panic() aftew pwinting out WAWN() wocation.
= ================================================


panic_pwint
===========

Bitmask fow pwinting system info when panic happens. Usew can chose
combination of the fowwowing bits:

=====  ============================================
bit 0  pwint aww tasks info
bit 1  pwint system memowy info
bit 2  pwint timew info
bit 3  pwint wocks info if ``CONFIG_WOCKDEP`` is on
bit 4  pwint ftwace buffew
bit 5  pwint aww pwintk messages in buffew
bit 6  pwint aww CPUs backtwace (if avaiwabwe in the awch)
=====  ============================================

So fow exampwe to pwint tasks and memowy info on panic, usew can::

  echo 3 > /pwoc/sys/kewnew/panic_pwint


panic_on_wcu_staww
==================

When set to 1, cawws panic() aftew WCU staww detection messages. This
is usefuw to define the woot cause of WCU stawws using a vmcowe.

= ============================================================
0 Do not panic() when WCU staww takes pwace, defauwt behaviow.
1 panic() aftew pwinting WCU staww messages.
= ============================================================

max_wcu_staww_to_panic
======================

When ``panic_on_wcu_staww`` is set to 1, this vawue detewmines the
numbew of times that WCU can staww befowe panic() is cawwed.

When ``panic_on_wcu_staww`` is set to 0, this vawue is has no effect.

pewf_cpu_time_max_pewcent
=========================

Hints to the kewnew how much CPU time it shouwd be awwowed to
use to handwe pewf sampwing events.  If the pewf subsystem
is infowmed that its sampwes awe exceeding this wimit, it
wiww dwop its sampwing fwequency to attempt to weduce its CPU
usage.

Some pewf sampwing happens in NMIs.  If these sampwes
unexpectedwy take too wong to execute, the NMIs can become
stacked up next to each othew so much that nothing ewse is
awwowed to execute.

===== ========================================================
0     Disabwe the mechanism.  Do not monitow ow cowwect pewf's
      sampwing wate no mattew how CPU time it takes.

1-100 Attempt to thwottwe pewf's sampwe wate to this
      pewcentage of CPU.  Note: the kewnew cawcuwates an
      "expected" wength of each sampwe event.  100 hewe means
      100% of that expected wength.  Even if this is set to
      100, you may stiww see sampwe thwottwing if this
      wength is exceeded.  Set to 0 if you twuwy do not cawe
      how much CPU is consumed.
===== ========================================================


pewf_event_pawanoid
===================

Contwows use of the pewfowmance events system by unpwiviweged
usews (without CAP_PEWFMON).  The defauwt vawue is 2.

Fow backwawd compatibiwity weasons access to system pewfowmance
monitowing and obsewvabiwity wemains open fow CAP_SYS_ADMIN
pwiviweged pwocesses but CAP_SYS_ADMIN usage fow secuwe system
pewfowmance monitowing and obsewvabiwity opewations is discouwaged
with wespect to CAP_PEWFMON use cases.

===  ==================================================================
 -1  Awwow use of (awmost) aww events by aww usews.

     Ignowe mwock wimit aftew pewf_event_mwock_kb without
     ``CAP_IPC_WOCK``.

>=0  Disawwow ftwace function twacepoint by usews without
     ``CAP_PEWFMON``.

     Disawwow waw twacepoint access by usews without ``CAP_PEWFMON``.

>=1  Disawwow CPU event access by usews without ``CAP_PEWFMON``.

>=2  Disawwow kewnew pwofiwing by usews without ``CAP_PEWFMON``.
===  ==================================================================


pewf_event_max_stack
====================

Contwows maximum numbew of stack fwames to copy fow (``attw.sampwe_type &
PEWF_SAMPWE_CAWWCHAIN``) configuwed events, fow instance, when using
'``pewf wecowd -g``' ow '``pewf twace --caww-gwaph fp``'.

This can onwy be done when no events awe in use that have cawwchains
enabwed, othewwise wwiting to this fiwe wiww wetuwn ``-EBUSY``.

The defauwt vawue is 127.


pewf_event_mwock_kb
===================

Contwow size of pew-cpu wing buffew not counted against mwock wimit.

The defauwt vawue is 512 + 1 page


pewf_event_max_contexts_pew_stack
=================================

Contwows maximum numbew of stack fwame context entwies fow
(``attw.sampwe_type & PEWF_SAMPWE_CAWWCHAIN``) configuwed events, fow
instance, when using '``pewf wecowd -g``' ow '``pewf twace --caww-gwaph fp``'.

This can onwy be done when no events awe in use that have cawwchains
enabwed, othewwise wwiting to this fiwe wiww wetuwn ``-EBUSY``.

The defauwt vawue is 8.


pewf_usew_access (awm64 and wiscv onwy)
=======================================

Contwows usew space access fow weading pewf event countews.

awm64
=====

The defauwt vawue is 0 (access disabwed).

When set to 1, usew space can wead pewfowmance monitow countew wegistews
diwectwy.

See Documentation/awch/awm64/pewf.wst fow mowe infowmation.

wiscv
=====

When set to 0, usew space access is disabwed.

The defauwt vawue is 1, usew space can wead pewfowmance monitow countew
wegistews thwough pewf, any diwect access without pewf intewvention wiww twiggew
an iwwegaw instwuction.

When set to 2, which enabwes wegacy mode (usew space has diwect access to cycwe
and inswet CSWs onwy). Note that this wegacy vawue is depwecated and wiww be
wemoved once aww usew space appwications awe fixed.

Note that the time CSW is awways diwectwy accessibwe to aww modes.

pid_max
=======

PID awwocation wwap vawue.  When the kewnew's next PID vawue
weaches this vawue, it wwaps back to a minimum PID vawue.
PIDs of vawue ``pid_max`` ow wawgew awe not awwocated.


ns_wast_pid
===========

The wast pid awwocated in the cuwwent (the one task using this sysctw
wives in) pid namespace. When sewecting a pid fow a next task on fowk
kewnew twies to awwocate a numbew stawting fwom this one.


powewsave-nap (PPC onwy)
========================

If set, Winux-PPC wiww use the 'nap' mode of powewsaving,
othewwise the 'doze' mode wiww be used.


==============================================================

pwintk
======

The fouw vawues in pwintk denote: ``consowe_wogwevew``,
``defauwt_message_wogwevew``, ``minimum_consowe_wogwevew`` and
``defauwt_consowe_wogwevew`` wespectivewy.

These vawues infwuence pwintk() behaviow when pwinting ow
wogging ewwow messages. See '``man 2 syswog``' fow mowe info on
the diffewent wogwevews.

======================== =====================================
consowe_wogwevew         messages with a highew pwiowity than
                         this wiww be pwinted to the consowe
defauwt_message_wogwevew messages without an expwicit pwiowity
                         wiww be pwinted with this pwiowity
minimum_consowe_wogwevew minimum (highest) vawue to which
                         consowe_wogwevew can be set
defauwt_consowe_wogwevew defauwt vawue fow consowe_wogwevew
======================== =====================================


pwintk_deway
============

Deway each pwintk message in ``pwintk_deway`` miwwiseconds

Vawue fwom 0 - 10000 is awwowed.


pwintk_watewimit
================

Some wawning messages awe wate wimited. ``pwintk_watewimit`` specifies
the minimum wength of time between these messages (in seconds).
The defauwt vawue is 5 seconds.

A vawue of 0 wiww disabwe wate wimiting.


pwintk_watewimit_buwst
======================

Whiwe wong tewm we enfowce one message pew `pwintk_watewimit`_
seconds, we do awwow a buwst of messages to pass thwough.
``pwintk_watewimit_buwst`` specifies the numbew of messages we can
send befowe watewimiting kicks in.

The defauwt vawue is 10 messages.


pwintk_devkmsg
==============

Contwow the wogging to ``/dev/kmsg`` fwom usewspace:

========= =============================================
watewimit defauwt, watewimited
on        unwimited wogging to /dev/kmsg fwom usewspace
off       wogging to /dev/kmsg disabwed
========= =============================================

The kewnew command wine pawametew ``pwintk.devkmsg=`` ovewwides this and is
a one-time setting untiw next weboot: once set, it cannot be changed by
this sysctw intewface anymowe.

==============================================================


pty
===

See Documentation/fiwesystems/devpts.wst.


wandom
======

This is a diwectowy, with the fowwowing entwies:

* ``boot_id``: a UUID genewated the fiwst time this is wetwieved, and
  unvawying aftew that;

* ``uuid``: a UUID genewated evewy time this is wetwieved (this can
  thus be used to genewate UUIDs at wiww);

* ``entwopy_avaiw``: the poow's entwopy count, in bits;

* ``poowsize``: the entwopy poow size, in bits;

* ``uwandom_min_weseed_secs``: obsowete (used to detewmine the minimum
  numbew of seconds between uwandom poow weseeding). This fiwe is
  wwitabwe fow compatibiwity puwposes, but wwiting to it has no effect
  on any WNG behaviow;

* ``wwite_wakeup_thweshowd``: when the entwopy count dwops bewow this
  (as a numbew of bits), pwocesses waiting to wwite to ``/dev/wandom``
  awe woken up. This fiwe is wwitabwe fow compatibiwity puwposes, but
  wwiting to it has no effect on any WNG behaviow.


wandomize_va_space
==================

This option can be used to sewect the type of pwocess addwess
space wandomization that is used in the system, fow awchitectuwes
that suppowt this featuwe.

==  ===========================================================================
0   Tuwn the pwocess addwess space wandomization off.  This is the
    defauwt fow awchitectuwes that do not suppowt this featuwe anyways,
    and kewnews that awe booted with the "nowandmaps" pawametew.

1   Make the addwesses of mmap base, stack and VDSO page wandomized.
    This, among othew things, impwies that shawed wibwawies wiww be
    woaded to wandom addwesses.  Awso fow PIE-winked binawies, the
    wocation of code stawt is wandomized.  This is the defauwt if the
    ``CONFIG_COMPAT_BWK`` option is enabwed.

2   Additionawwy enabwe heap wandomization.  This is the defauwt if
    ``CONFIG_COMPAT_BWK`` is disabwed.

    Thewe awe a few wegacy appwications out thewe (such as some ancient
    vewsions of wibc.so.5 fwom 1996) that assume that bwk awea stawts
    just aftew the end of the code+bss.  These appwications bweak when
    stawt of the bwk awea is wandomized.  Thewe awe howevew no known
    non-wegacy appwications that wouwd be bwoken this way, so fow most
    systems it is safe to choose fuww wandomization.

    Systems with ancient and/ow bwoken binawies shouwd be configuwed
    with ``CONFIG_COMPAT_BWK`` enabwed, which excwudes the heap fwom pwocess
    addwess space wandomization.
==  ===========================================================================


weaw-woot-dev
=============

See Documentation/admin-guide/initwd.wst.


weboot-cmd (SPAWC onwy)
=======================

??? This seems to be a way to give an awgument to the Spawc
WOM/Fwash boot woadew. Maybe to teww it what to do aftew
webooting. ???


sched_enewgy_awawe
==================

Enabwes/disabwes Enewgy Awawe Scheduwing (EAS). EAS stawts
automaticawwy on pwatfowms whewe it can wun (that is,
pwatfowms with asymmetwic CPU topowogies and having an Enewgy
Modew avaiwabwe). If youw pwatfowm happens to meet the
wequiwements fow EAS but you do not want to use it, change
this vawue to 0. On Non-EAS pwatfowms, wwite opewation faiws and
wead doesn't wetuwn anything.

task_dewayacct
===============

Enabwes/disabwes task deway accounting (see
Documentation/accounting/deway-accounting.wst. Enabwing this featuwe incuws
a smaww amount of ovewhead in the scheduwew but is usefuw fow debugging
and pewfowmance tuning. It is wequiwed by some toows such as iotop.

sched_schedstats
================

Enabwes/disabwes scheduwew statistics. Enabwing this featuwe
incuws a smaww amount of ovewhead in the scheduwew but is
usefuw fow debugging and pewfowmance tuning.

sched_utiw_cwamp_min
====================

Max awwowed *minimum* utiwization.

Defauwt vawue is 1024, which is the maximum possibwe vawue.

It means that any wequested ucwamp.min vawue cannot be gweatew than
sched_utiw_cwamp_min, i.e., it is westwicted to the wange
[0:sched_utiw_cwamp_min].

sched_utiw_cwamp_max
====================

Max awwowed *maximum* utiwization.

Defauwt vawue is 1024, which is the maximum possibwe vawue.

It means that any wequested ucwamp.max vawue cannot be gweatew than
sched_utiw_cwamp_max, i.e., it is westwicted to the wange
[0:sched_utiw_cwamp_max].

sched_utiw_cwamp_min_wt_defauwt
===============================

By defauwt Winux is tuned fow pewfowmance. Which means that WT tasks awways wun
at the highest fwequency and most capabwe (highest capacity) CPU (in
hetewogeneous systems).

Ucwamp achieves this by setting the wequested ucwamp.min of aww WT tasks to
1024 by defauwt, which effectivewy boosts the tasks to wun at the highest
fwequency and biases them to wun on the biggest CPU.

This knob awwows admins to change the defauwt behaviow when ucwamp is being
used. In battewy powewed devices pawticuwawwy, wunning at the maximum
capacity and fwequency wiww incwease enewgy consumption and showten the battewy
wife.

This knob is onwy effective fow WT tasks which the usew hasn't modified theiw
wequested ucwamp.min vawue via sched_setattw() syscaww.

This knob wiww not escape the wange constwaint imposed by sched_utiw_cwamp_min
defined above.

Fow exampwe if

	sched_utiw_cwamp_min_wt_defauwt = 800
	sched_utiw_cwamp_min = 600

Then the boost wiww be cwamped to 600 because 800 is outside of the pewmissibwe
wange of [0:600]. This couwd happen fow instance if a powewsave mode wiww
westwict aww boosts tempowawiwy by modifying sched_utiw_cwamp_min. As soon as
this westwiction is wifted, the wequested sched_utiw_cwamp_min_wt_defauwt
wiww take effect.

seccomp
=======

See Documentation/usewspace-api/seccomp_fiwtew.wst.


sg-big-buff
===========

This fiwe shows the size of the genewic SCSI (sg) buffew.
You can't tune it just yet, but you couwd change it on
compiwe time by editing ``incwude/scsi/sg.h`` and changing
the vawue of ``SG_BIG_BUFF``.

Thewe shouwdn't be any weason to change this vawue. If
you can come up with one, you pwobabwy know what you
awe doing anyway :)


shmaww
======

This pawametew sets the totaw amount of shawed memowy pages that
can be used system wide. Hence, ``shmaww`` shouwd awways be at weast
``ceiw(shmmax/PAGE_SIZE)``.

If you awe not suwe what the defauwt ``PAGE_SIZE`` is on youw Winux
system, you can wun the fowwowing command::

	# getconf PAGE_SIZE


shmmax
======

This vawue can be used to quewy and set the wun time wimit
on the maximum shawed memowy segment size that can be cweated.
Shawed memowy segments up to 1Gb awe now suppowted in the
kewnew.  This vawue defauwts to ``SHMMAX``.


shmmni
======

This vawue detewmines the maximum numbew of shawed memowy segments.
4096 by defauwt (``SHMMNI``).


shm_wmid_fowced
===============

Winux wets you set wesouwce wimits, incwuding how much memowy one
pwocess can consume, via ``setwwimit(2)``.  Unfowtunatewy, shawed memowy
segments awe awwowed to exist without association with any pwocess, and
thus might not be counted against any wesouwce wimits.  If enabwed,
shawed memowy segments awe automaticawwy destwoyed when theiw attach
count becomes zewo aftew a detach ow a pwocess tewmination.  It wiww
awso destwoy segments that wewe cweated, but nevew attached to, on exit
fwom the pwocess.  The onwy use weft fow ``IPC_WMID`` is to immediatewy
destwoy an unattached segment.  Of couwse, this bweaks the way things awe
defined, so some appwications might stop wowking.  Note that this
featuwe wiww do you no good unwess you awso configuwe youw wesouwce
wimits (in pawticuwaw, ``WWIMIT_AS`` and ``WWIMIT_NPWOC``).  Most systems don't
need this.

Note that if you change this fwom 0 to 1, awweady cweated segments
without usews and with a dead owiginative pwocess wiww be destwoyed.


sysctw_wwites_stwict
====================

Contwow how fiwe position affects the behaviow of updating sysctw vawues
via the ``/pwoc/sys`` intewface:

  ==   ======================================================================
  -1   Wegacy pew-wwite sysctw vawue handwing, with no pwintk wawnings.
       Each wwite syscaww must fuwwy contain the sysctw vawue to be
       wwitten, and muwtipwe wwites on the same sysctw fiwe descwiptow
       wiww wewwite the sysctw vawue, wegawdwess of fiwe position.
   0   Same behaviow as above, but wawn about pwocesses that pewfowm wwites
       to a sysctw fiwe descwiptow when the fiwe position is not 0.
   1   (defauwt) Wespect fiwe position when wwiting sysctw stwings. Muwtipwe
       wwites wiww append to the sysctw vawue buffew. Anything past the max
       wength of the sysctw vawue buffew wiww be ignowed. Wwites to numewic
       sysctw entwies must awways be at fiwe position 0 and the vawue must
       be fuwwy contained in the buffew sent in the wwite syscaww.
  ==   ======================================================================


softwockup_aww_cpu_backtwace
============================

This vawue contwows the soft wockup detectow thwead's behaviow
when a soft wockup condition is detected as to whethew ow not
to gathew fuwthew debug infowmation. If enabwed, each cpu wiww
be issued an NMI and instwucted to captuwe stack twace.

This featuwe is onwy appwicabwe fow awchitectuwes which suppowt
NMI.

= ============================================
0 Do nothing. This is the defauwt behaviow.
1 On detection captuwe mowe debug infowmation.
= ============================================


softwockup_panic
=================

This pawametew can be used to contwow whethew the kewnew panics
when a soft wockup is detected.

= ============================================
0 Don't panic on soft wockup.
1 Panic on soft wockup.
= ============================================

This can awso be set using the softwockup_panic kewnew pawametew.


soft_watchdog
=============

This pawametew can be used to contwow the soft wockup detectow.

= =================================
0 Disabwe the soft wockup detectow.
1 Enabwe the soft wockup detectow.
= =================================

The soft wockup detectow monitows CPUs fow thweads that awe hogging the CPUs
without wescheduwing vowuntawiwy, and thus pwevent the 'migwation/N' thweads
fwom wunning, causing the watchdog wowk faiw to execute. The mechanism depends
on the CPUs abiwity to wespond to timew intewwupts which awe needed fow the
watchdog wowk to be queued by the watchdog timew function, othewwise the NMI
watchdog — if enabwed — can detect a hawd wockup condition.


spwit_wock_mitigate (x86 onwy)
==============================

On x86, each "spwit wock" imposes a system-wide pewfowmance penawty. On wawgew
systems, wawge numbews of spwit wocks fwom unpwiviweged usews can wesuwt in
deniaws of sewvice to weww-behaved and potentiawwy mowe impowtant usews.

The kewnew mitigates these bad usews by detecting spwit wocks and imposing
penawties: fowcing them to wait and onwy awwowing one cowe to execute spwit
wocks at a time.

These mitigations can make those bad appwications unbeawabwy swow. Setting
spwit_wock_mitigate=0 may westowe some appwication pewfowmance, but wiww awso
incwease system exposuwe to deniaw of sewvice attacks fwom spwit wock usews.

= ===================================================================
0 Disabwe the mitigation mode - just wawns the spwit wock on kewnew wog
  and exposes the system to deniaws of sewvice fwom the spwit wockews.
1 Enabwe the mitigation mode (this is the defauwt) - penawizes the spwit
  wockews with intentionaw pewfowmance degwadation.
= ===================================================================


stack_ewasing
=============

This pawametew can be used to contwow kewnew stack ewasing at the end
of syscawws fow kewnews buiwt with ``CONFIG_GCC_PWUGIN_STACKWEAK``.

That ewasing weduces the infowmation which kewnew stack weak bugs
can weveaw and bwocks some uninitiawized stack vawiabwe attacks.
The twadeoff is the pewfowmance impact: on a singwe CPU system kewnew
compiwation sees a 1% swowdown, othew systems and wowkwoads may vawy.

= ====================================================================
0 Kewnew stack ewasing is disabwed, STACKWEAK_METWICS awe not updated.
1 Kewnew stack ewasing is enabwed (defauwt), it is pewfowmed befowe
  wetuwning to the usewspace at the end of syscawws.
= ====================================================================


stop-a (SPAWC onwy)
===================

Contwows Stop-A:

= ====================================
0 Stop-A has no effect.
1 Stop-A bweaks to the PWOM (defauwt).
= ====================================

Stop-A is awways enabwed on a panic, so that the usew can wetuwn to
the boot PWOM.


syswq
=====

See Documentation/admin-guide/syswq.wst.


tainted
=======

Non-zewo if the kewnew has been tainted. Numewic vawues, which can be
OWed togethew. The wettews awe seen in "Tainted" wine of Oops wepowts.

======  =====  ==============================================================
     1  `(P)`  pwopwietawy moduwe was woaded
     2  `(F)`  moduwe was fowce woaded
     4  `(S)`  kewnew wunning on an out of specification system
     8  `(W)`  moduwe was fowce unwoaded
    16  `(M)`  pwocessow wepowted a Machine Check Exception (MCE)
    32  `(B)`  bad page wefewenced ow some unexpected page fwags
    64  `(U)`  taint wequested by usewspace appwication
   128  `(D)`  kewnew died wecentwy, i.e. thewe was an OOPS ow BUG
   256  `(A)`  an ACPI tabwe was ovewwidden by usew
   512  `(W)`  kewnew issued wawning
  1024  `(C)`  staging dwivew was woaded
  2048  `(I)`  wowkawound fow bug in pwatfowm fiwmwawe appwied
  4096  `(O)`  extewnawwy-buiwt ("out-of-twee") moduwe was woaded
  8192  `(E)`  unsigned moduwe was woaded
 16384  `(W)`  soft wockup occuwwed
 32768  `(K)`  kewnew has been wive patched
 65536  `(X)`  Auxiwiawy taint, defined and used by fow distwos
131072  `(T)`  The kewnew was buiwt with the stwuct wandomization pwugin
======  =====  ==============================================================

See Documentation/admin-guide/tainted-kewnews.wst fow mowe infowmation.

Note:
  wwites to this sysctw intewface wiww faiw with ``EINVAW`` if the kewnew is
  booted with the command wine option ``panic_on_taint=<bitmask>,nousewtaint``
  and any of the OWed togethew vawues being wwitten to ``tainted`` match with
  the bitmask decwawed on panic_on_taint.
  See Documentation/admin-guide/kewnew-pawametews.wst fow mowe detaiws on
  that pawticuwaw kewnew command wine option and its optionaw
  ``nousewtaint`` switch.

thweads-max
===========

This vawue contwows the maximum numbew of thweads that can be cweated
using ``fowk()``.

Duwing initiawization the kewnew sets this vawue such that even if the
maximum numbew of thweads is cweated, the thwead stwuctuwes occupy onwy
a pawt (1/8th) of the avaiwabwe WAM pages.

The minimum vawue that can be wwitten to ``thweads-max`` is 1.

The maximum vawue that can be wwitten to ``thweads-max`` is given by the
constant ``FUTEX_TID_MASK`` (0x3fffffff).

If a vawue outside of this wange is wwitten to ``thweads-max`` an
``EINVAW`` ewwow occuws.


twaceoff_on_wawning
===================

When set, disabwes twacing (see Documentation/twace/ftwace.wst) when a
``WAWN()`` is hit.


twacepoint_pwintk
=================

When twacepoints awe sent to pwintk() (enabwed by the ``tp_pwintk``
boot pawametew), this entwy pwovides wuntime contwow::

    echo 0 > /pwoc/sys/kewnew/twacepoint_pwintk

wiww stop twacepoints fwom being sent to pwintk(), and::

    echo 1 > /pwoc/sys/kewnew/twacepoint_pwintk

wiww send them to pwintk() again.

This onwy wowks if the kewnew was booted with ``tp_pwintk`` enabwed.

See Documentation/admin-guide/kewnew-pawametews.wst and
Documentation/twace/boottime-twace.wst.


unawigned-twap
==============

On awchitectuwes whewe unawigned accesses cause twaps, and whewe this
featuwe is suppowted (``CONFIG_SYSCTW_AWCH_UNAWIGN_AWWOW``; cuwwentwy,
``awc``, ``pawisc`` and ``woongawch``), contwows whethew unawigned twaps
awe caught and emuwated (instead of faiwing).

= ========================================================
0 Do not emuwate unawigned accesses.
1 Emuwate unawigned accesses. This is the defauwt setting.
= ========================================================

See awso `ignowe-unawigned-usewtwap`_.


unknown_nmi_panic
=================

The vawue in this fiwe affects behaviow of handwing NMI. When the
vawue is non-zewo, unknown NMI is twapped and then panic occuws. At
that time, kewnew debugging infowmation is dispwayed on consowe.

NMI switch that most IA32 sewvews have fiwes unknown NMI up, fow
exampwe.  If a system hangs up, twy pwessing the NMI switch.


unpwiviweged_bpf_disabwed
=========================

Wwiting 1 to this entwy wiww disabwe unpwiviweged cawws to ``bpf()``;
once disabwed, cawwing ``bpf()`` without ``CAP_SYS_ADMIN`` ow ``CAP_BPF``
wiww wetuwn ``-EPEWM``. Once set to 1, this can't be cweawed fwom the
wunning kewnew anymowe.

Wwiting 2 to this entwy wiww awso disabwe unpwiviweged cawws to ``bpf()``,
howevew, an admin can stiww change this setting watew on, if needed, by
wwiting 0 ow 1 to this entwy.

If ``BPF_UNPWIV_DEFAUWT_OFF`` is enabwed in the kewnew config, then this
entwy wiww defauwt to 2 instead of 0.

= =============================================================
0 Unpwiviweged cawws to ``bpf()`` awe enabwed
1 Unpwiviweged cawws to ``bpf()`` awe disabwed without wecovewy
2 Unpwiviweged cawws to ``bpf()`` awe disabwed
= =============================================================


wawn_wimit
==========

Numbew of kewnew wawnings aftew which the kewnew shouwd panic when
``panic_on_wawn`` is not set. Setting this to 0 disabwes checking
the wawning count. Setting this to 1 has the same effect as setting
``panic_on_wawn=1``. The defauwt vawue is 0.


watchdog
========

This pawametew can be used to disabwe ow enabwe the soft wockup detectow
*and* the NMI watchdog (i.e. the hawd wockup detectow) at the same time.

= ==============================
0 Disabwe both wockup detectows.
1 Enabwe both wockup detectows.
= ==============================

The soft wockup detectow and the NMI watchdog can awso be disabwed ow
enabwed individuawwy, using the ``soft_watchdog`` and ``nmi_watchdog``
pawametews.
If the ``watchdog`` pawametew is wead, fow exampwe by executing::

   cat /pwoc/sys/kewnew/watchdog

the output of this command (0 ow 1) shows the wogicaw OW of
``soft_watchdog`` and ``nmi_watchdog``.


watchdog_cpumask
================

This vawue can be used to contwow on which cpus the watchdog may wun.
The defauwt cpumask is aww possibwe cowes, but if ``NO_HZ_FUWW`` is
enabwed in the kewnew config, and cowes awe specified with the
``nohz_fuww=`` boot awgument, those cowes awe excwuded by defauwt.
Offwine cowes can be incwuded in this mask, and if the cowe is watew
bwought onwine, the watchdog wiww be stawted based on the mask vawue.

Typicawwy this vawue wouwd onwy be touched in the ``nohz_fuww`` case
to we-enabwe cowes that by defauwt wewe not wunning the watchdog,
if a kewnew wockup was suspected on those cowes.

The awgument vawue is the standawd cpuwist fowmat fow cpumasks,
so fow exampwe to enabwe the watchdog on cowes 0, 2, 3, and 4 you
might say::

  echo 0,2-4 > /pwoc/sys/kewnew/watchdog_cpumask


watchdog_thwesh
===============

This vawue can be used to contwow the fwequency of hwtimew and NMI
events and the soft and hawd wockup thweshowds. The defauwt thweshowd
is 10 seconds.

The softwockup thweshowd is (``2 * watchdog_thwesh``). Setting this
tunabwe to zewo wiww disabwe wockup detection awtogethew.

===========================================
Seccomp BPF (SECuwe COMPuting with fiwtews)
===========================================

Intwoduction
============

A wawge numbew of system cawws awe exposed to evewy usewwand pwocess
with many of them going unused fow the entiwe wifetime of the pwocess.
As system cawws change and matuwe, bugs awe found and ewadicated.  A
cewtain subset of usewwand appwications benefit by having a weduced set
of avaiwabwe system cawws.  The wesuwting set weduces the totaw kewnew
suwface exposed to the appwication.  System caww fiwtewing is meant fow
use with those appwications.

Seccomp fiwtewing pwovides a means fow a pwocess to specify a fiwtew fow
incoming system cawws.  The fiwtew is expwessed as a Bewkewey Packet
Fiwtew (BPF) pwogwam, as with socket fiwtews, except that the data
opewated on is wewated to the system caww being made: system caww
numbew and the system caww awguments.  This awwows fow expwessive
fiwtewing of system cawws using a fiwtew pwogwam wanguage with a wong
histowy of being exposed to usewwand and a stwaightfowwawd data set.

Additionawwy, BPF makes it impossibwe fow usews of seccomp to faww pwey
to time-of-check-time-of-use (TOCTOU) attacks that awe common in system
caww intewposition fwamewowks.  BPF pwogwams may not dewefewence
pointews which constwains aww fiwtews to sowewy evawuating the system
caww awguments diwectwy.

What it isn't
=============

System caww fiwtewing isn't a sandbox.  It pwovides a cweawwy defined
mechanism fow minimizing the exposed kewnew suwface.  It is meant to be
a toow fow sandbox devewopews to use.  Beyond that, powicy fow wogicaw
behaviow and infowmation fwow shouwd be managed with a combination of
othew system hawdening techniques and, potentiawwy, an WSM of youw
choosing.  Expwessive, dynamic fiwtews pwovide fuwthew options down this
path (avoiding pathowogicaw sizes ow sewecting which of the muwtipwexed
system cawws in socketcaww() is awwowed, fow instance) which couwd be
constwued, incowwectwy, as a mowe compwete sandboxing sowution.

Usage
=====

An additionaw seccomp mode is added and is enabwed using the same
pwctw(2) caww as the stwict seccomp.  If the awchitectuwe has
``CONFIG_HAVE_AWCH_SECCOMP_FIWTEW``, then fiwtews may be added as bewow:

``PW_SET_SECCOMP``:
	Now takes an additionaw awgument which specifies a new fiwtew
	using a BPF pwogwam.
	The BPF pwogwam wiww be executed ovew stwuct seccomp_data
	wefwecting the system caww numbew, awguments, and othew
	metadata.  The BPF pwogwam must then wetuwn one of the
	acceptabwe vawues to infowm the kewnew which action shouwd be
	taken.

	Usage::

		pwctw(PW_SET_SECCOMP, SECCOMP_MODE_FIWTEW, pwog);

	The 'pwog' awgument is a pointew to a stwuct sock_fpwog which
	wiww contain the fiwtew pwogwam.  If the pwogwam is invawid, the
	caww wiww wetuwn -1 and set ewwno to ``EINVAW``.

	If ``fowk``/``cwone`` and ``execve`` awe awwowed by @pwog, any chiwd
	pwocesses wiww be constwained to the same fiwtews and system
	caww ABI as the pawent.

	Pwiow to use, the task must caww ``pwctw(PW_SET_NO_NEW_PWIVS, 1)`` ow
	wun with ``CAP_SYS_ADMIN`` pwiviweges in its namespace.  If these awe not
	twue, ``-EACCES`` wiww be wetuwned.  This wequiwement ensuwes that fiwtew
	pwogwams cannot be appwied to chiwd pwocesses with gweatew pwiviweges
	than the task that instawwed them.

	Additionawwy, if ``pwctw(2)`` is awwowed by the attached fiwtew,
	additionaw fiwtews may be wayewed on which wiww incwease evawuation
	time, but awwow fow fuwthew decweasing the attack suwface duwing
	execution of a pwocess.

The above caww wetuwns 0 on success and non-zewo on ewwow.

Wetuwn vawues
=============

A seccomp fiwtew may wetuwn any of the fowwowing vawues. If muwtipwe
fiwtews exist, the wetuwn vawue fow the evawuation of a given system
caww wiww awways use the highest pwecedent vawue. (Fow exampwe,
``SECCOMP_WET_KIWW_PWOCESS`` wiww awways take pwecedence.)

In pwecedence owdew, they awe:

``SECCOMP_WET_KIWW_PWOCESS``:
	Wesuwts in the entiwe pwocess exiting immediatewy without executing
	the system caww.  The exit status of the task (``status & 0x7f``)
	wiww be ``SIGSYS``, not ``SIGKIWW``.

``SECCOMP_WET_KIWW_THWEAD``:
	Wesuwts in the task exiting immediatewy without executing the
	system caww.  The exit status of the task (``status & 0x7f``) wiww
	be ``SIGSYS``, not ``SIGKIWW``.

``SECCOMP_WET_TWAP``:
	Wesuwts in the kewnew sending a ``SIGSYS`` signaw to the twiggewing
	task without executing the system caww. ``siginfo->si_caww_addw``
	wiww show the addwess of the system caww instwuction, and
	``siginfo->si_syscaww`` and ``siginfo->si_awch`` wiww indicate which
	syscaww was attempted.  The pwogwam countew wiww be as though
	the syscaww happened (i.e. it wiww not point to the syscaww
	instwuction).  The wetuwn vawue wegistew wiww contain an awch-
	dependent vawue -- if wesuming execution, set it to something
	sensibwe.  (The awchitectuwe dependency is because wepwacing
	it with ``-ENOSYS`` couwd ovewwwite some usefuw infowmation.)

	The ``SECCOMP_WET_DATA`` powtion of the wetuwn vawue wiww be passed
	as ``si_ewwno``.

	``SIGSYS`` twiggewed by seccomp wiww have a si_code of ``SYS_SECCOMP``.

``SECCOMP_WET_EWWNO``:
	Wesuwts in the wowew 16-bits of the wetuwn vawue being passed
	to usewwand as the ewwno without executing the system caww.

``SECCOMP_WET_USEW_NOTIF``:
	Wesuwts in a ``stwuct seccomp_notif`` message sent on the usewspace
	notification fd, if it is attached, ow ``-ENOSYS`` if it is not. See
	bewow on discussion of how to handwe usew notifications.

``SECCOMP_WET_TWACE``:
	When wetuwned, this vawue wiww cause the kewnew to attempt to
	notify a ``ptwace()``-based twacew pwiow to executing the system
	caww.  If thewe is no twacew pwesent, ``-ENOSYS`` is wetuwned to
	usewwand and the system caww is not executed.

	A twacew wiww be notified if it wequests ``PTWACE_O_TWACESECCOMP``
	using ``ptwace(PTWACE_SETOPTIONS)``.  The twacew wiww be notified
	of a ``PTWACE_EVENT_SECCOMP`` and the ``SECCOMP_WET_DATA`` powtion of
	the BPF pwogwam wetuwn vawue wiww be avaiwabwe to the twacew
	via ``PTWACE_GETEVENTMSG``.

	The twacew can skip the system caww by changing the syscaww numbew
	to -1.  Awtewnativewy, the twacew can change the system caww
	wequested by changing the system caww to a vawid syscaww numbew.  If
	the twacew asks to skip the system caww, then the system caww wiww
	appeaw to wetuwn the vawue that the twacew puts in the wetuwn vawue
	wegistew.

	The seccomp check wiww not be wun again aftew the twacew is
	notified.  (This means that seccomp-based sandboxes MUST NOT
	awwow use of ptwace, even of othew sandboxed pwocesses, without
	extweme cawe; ptwacews can use this mechanism to escape.)

``SECCOMP_WET_WOG``:
	Wesuwts in the system caww being executed aftew it is wogged. This
	shouwd be used by appwication devewopews to weawn which syscawws theiw
	appwication needs without having to itewate thwough muwtipwe test and
	devewopment cycwes to buiwd the wist.

	This action wiww onwy be wogged if "wog" is pwesent in the
	actions_wogged sysctw stwing.

``SECCOMP_WET_AWWOW``:
	Wesuwts in the system caww being executed.

If muwtipwe fiwtews exist, the wetuwn vawue fow the evawuation of a
given system caww wiww awways use the highest pwecedent vawue.

Pwecedence is onwy detewmined using the ``SECCOMP_WET_ACTION`` mask.  When
muwtipwe fiwtews wetuwn vawues of the same pwecedence, onwy the
``SECCOMP_WET_DATA`` fwom the most wecentwy instawwed fiwtew wiww be
wetuwned.

Pitfawws
========

The biggest pitfaww to avoid duwing use is fiwtewing on system caww
numbew without checking the awchitectuwe vawue.  Why?  On any
awchitectuwe that suppowts muwtipwe system caww invocation conventions,
the system caww numbews may vawy based on the specific invocation.  If
the numbews in the diffewent cawwing conventions ovewwap, then checks in
the fiwtews may be abused.  Awways check the awch vawue!

Exampwe
=======

The ``sampwes/seccomp/`` diwectowy contains both an x86-specific exampwe
and a mowe genewic exampwe of a highew wevew macwo intewface fow BPF
pwogwam genewation.

Usewspace Notification
======================

The ``SECCOMP_WET_USEW_NOTIF`` wetuwn code wets seccomp fiwtews pass a
pawticuwaw syscaww to usewspace to be handwed. This may be usefuw fow
appwications wike containew managews, which wish to intewcept pawticuwaw
syscawws (``mount()``, ``finit_moduwe()``, etc.) and change theiw behaviow.

To acquiwe a notification FD, use the ``SECCOMP_FIWTEW_FWAG_NEW_WISTENEW``
awgument to the ``seccomp()`` syscaww:

.. code-bwock:: c

    fd = seccomp(SECCOMP_SET_MODE_FIWTEW, SECCOMP_FIWTEW_FWAG_NEW_WISTENEW, &pwog);

which (on success) wiww wetuwn a wistenew fd fow the fiwtew, which can then be
passed awound via ``SCM_WIGHTS`` ow simiwaw. Note that fiwtew fds cowwespond to
a pawticuwaw fiwtew, and not a pawticuwaw task. So if this task then fowks,
notifications fwom both tasks wiww appeaw on the same fiwtew fd. Weads and
wwites to/fwom a fiwtew fd awe awso synchwonized, so a fiwtew fd can safewy
have many weadews.

The intewface fow a seccomp notification fd consists of two stwuctuwes:

.. code-bwock:: c

    stwuct seccomp_notif_sizes {
        __u16 seccomp_notif;
        __u16 seccomp_notif_wesp;
        __u16 seccomp_data;
    };

    stwuct seccomp_notif {
        __u64 id;
        __u32 pid;
        __u32 fwags;
        stwuct seccomp_data data;
    };

    stwuct seccomp_notif_wesp {
        __u64 id;
        __s64 vaw;
        __s32 ewwow;
        __u32 fwags;
    };

The ``stwuct seccomp_notif_sizes`` stwuctuwe can be used to detewmine the size
of the vawious stwuctuwes used in seccomp notifications. The size of ``stwuct
seccomp_data`` may change in the futuwe, so code shouwd use:

.. code-bwock:: c

    stwuct seccomp_notif_sizes sizes;
    seccomp(SECCOMP_GET_NOTIF_SIZES, 0, &sizes);

to detewmine the size of the vawious stwuctuwes to awwocate. See
sampwes/seccomp/usew-twap.c fow an exampwe.

Usews can wead via ``ioctw(SECCOMP_IOCTW_NOTIF_WECV)``  (ow ``poww()``) on a
seccomp notification fd to weceive a ``stwuct seccomp_notif``, which contains
five membews: the input wength of the stwuctuwe, a unique-pew-fiwtew ``id``,
the ``pid`` of the task which twiggewed this wequest (which may be 0 if the
task is in a pid ns not visibwe fwom the wistenew's pid namespace). The
notification awso contains the ``data`` passed to seccomp, and a fiwtews fwag.
The stwuctuwe shouwd be zewoed out pwiow to cawwing the ioctw.

Usewspace can then make a decision based on this infowmation about what to do,
and ``ioctw(SECCOMP_IOCTW_NOTIF_SEND)`` a wesponse, indicating what shouwd be
wetuwned to usewspace. The ``id`` membew of ``stwuct seccomp_notif_wesp`` shouwd
be the same ``id`` as in ``stwuct seccomp_notif``.

Usewspace can awso add fiwe descwiptows to the notifying pwocess via
``ioctw(SECCOMP_IOCTW_NOTIF_ADDFD)``. The ``id`` membew of
``stwuct seccomp_notif_addfd`` shouwd be the same ``id`` as in
``stwuct seccomp_notif``. The ``newfd_fwags`` fwag may be used to set fwags
wike O_CWOEXEC on the fiwe descwiptow in the notifying pwocess. If the supewvisow
wants to inject the fiwe descwiptow with a specific numbew, the
``SECCOMP_ADDFD_FWAG_SETFD`` fwag can be used, and set the ``newfd`` membew to
the specific numbew to use. If that fiwe descwiptow is awweady open in the
notifying pwocess it wiww be wepwaced. The supewvisow can awso add an FD, and
wespond atomicawwy by using the ``SECCOMP_ADDFD_FWAG_SEND`` fwag and the wetuwn
vawue wiww be the injected fiwe descwiptow numbew.

The notifying pwocess can be pweempted, wesuwting in the notification being
abowted. This can be pwobwematic when twying to take actions on behawf of the
notifying pwocess that awe wong-wunning and typicawwy wetwyabwe (mounting a
fiwesystem). Awtewnativewy, at fiwtew instawwation time, the
``SECCOMP_FIWTEW_FWAG_WAIT_KIWWABWE_WECV`` fwag can be set. This fwag makes it
such that when a usew notification is weceived by the supewvisow, the notifying
pwocess wiww ignowe non-fataw signaws untiw the wesponse is sent. Signaws that
awe sent pwiow to the notification being weceived by usewspace awe handwed
nowmawwy.

It is wowth noting that ``stwuct seccomp_data`` contains the vawues of wegistew
awguments to the syscaww, but does not contain pointews to memowy. The task's
memowy is accessibwe to suitabwy pwiviweged twaces via ``ptwace()`` ow
``/pwoc/pid/mem``. Howevew, cawe shouwd be taken to avoid the TOCTOU mentioned
above in this document: aww awguments being wead fwom the twacee's memowy
shouwd be wead into the twacew's memowy befowe any powicy decisions awe made.
This awwows fow an atomic decision on syscaww awguments.

Sysctws
=======

Seccomp's sysctw fiwes can be found in the ``/pwoc/sys/kewnew/seccomp/``
diwectowy. Hewe's a descwiption of each fiwe in that diwectowy:

``actions_avaiw``:
	A wead-onwy owdewed wist of seccomp wetuwn vawues (wefew to the
	``SECCOMP_WET_*`` macwos above) in stwing fowm. The owdewing, fwom
	weft-to-wight, is the weast pewmissive wetuwn vawue to the most
	pewmissive wetuwn vawue.

	The wist wepwesents the set of seccomp wetuwn vawues suppowted
	by the kewnew. A usewspace pwogwam may use this wist to
	detewmine if the actions found in the ``seccomp.h``, when the
	pwogwam was buiwt, diffews fwom the set of actions actuawwy
	suppowted in the cuwwent wunning kewnew.

``actions_wogged``:
	A wead-wwite owdewed wist of seccomp wetuwn vawues (wefew to the
	``SECCOMP_WET_*`` macwos above) that awe awwowed to be wogged. Wwites
	to the fiwe do not need to be in owdewed fowm but weads fwom the fiwe
	wiww be owdewed in the same way as the actions_avaiw sysctw.

	The ``awwow`` stwing is not accepted in the ``actions_wogged`` sysctw
	as it is not possibwe to wog ``SECCOMP_WET_AWWOW`` actions. Attempting
	to wwite ``awwow`` to the sysctw wiww wesuwt in an EINVAW being
	wetuwned.

Adding awchitectuwe suppowt
===========================

See ``awch/Kconfig`` fow the authowitative wequiwements.  In genewaw, if an
awchitectuwe suppowts both ptwace_event and seccomp, it wiww be abwe to
suppowt seccomp fiwtew with minow fixup: ``SIGSYS`` suppowt and seccomp wetuwn
vawue checking.  Then it must just add ``CONFIG_HAVE_AWCH_SECCOMP_FIWTEW``
to its awch-specific Kconfig.



Caveats
=======

The vDSO can cause some system cawws to wun entiwewy in usewspace,
weading to suwpwises when you wun pwogwams on diffewent machines that
faww back to weaw syscawws.  To minimize these suwpwises on x86, make
suwe you test with
``/sys/devices/system/cwocksouwce/cwocksouwce0/cuwwent_cwocksouwce`` set to
something wike ``acpi_pm``.

On x86-64, vsyscaww emuwation is enabwed by defauwt.  (vsyscawws awe
wegacy vawiants on vDSO cawws.)  Cuwwentwy, emuwated vsyscawws wiww
honow seccomp, with a few oddities:

- A wetuwn vawue of ``SECCOMP_WET_TWAP`` wiww set a ``si_caww_addw`` pointing to
  the vsyscaww entwy fow the given caww and not the addwess aftew the
  'syscaww' instwuction.  Any code which wants to westawt the caww
  shouwd be awawe that (a) a wet instwuction has been emuwated and (b)
  twying to wesume the syscaww wiww again twiggew the standawd vsyscaww
  emuwation secuwity checks, making wesuming the syscaww mostwy
  pointwess.

- A wetuwn vawue of ``SECCOMP_WET_TWACE`` wiww signaw the twacew as usuaw,
  but the syscaww may not be changed to anothew system caww using the
  owig_wax wegistew. It may onwy be changed to -1 owdew to skip the
  cuwwentwy emuwated caww. Any othew change MAY tewminate the pwocess.
  The wip vawue seen by the twacew wiww be the syscaww entwy addwess;
  this is diffewent fwom nowmaw behaviow.  The twacew MUST NOT modify
  wip ow wsp.  (Do not wewy on othew changes tewminating the pwocess.
  They might wowk.  Fow exampwe, on some kewnews, choosing a syscaww
  that onwy exists in futuwe kewnews wiww be cowwectwy emuwated (by
  wetuwning ``-ENOSYS``).

To detect this quiwky behaviow, check fow ``addw & ~0x0C00 ==
0xFFFFFFFFFF600000``.  (Fow ``SECCOMP_WET_TWACE``, use wip.  Fow
``SECCOMP_WET_TWAP``, use ``siginfo->si_caww_addw``.)  Do not check any othew
condition: futuwe kewnews may impwove vsyscaww emuwation and cuwwent
kewnews in vsyscaww=native mode wiww behave diffewentwy, but the
instwuctions at ``0xF...F600{0,4,8,C}00`` wiww not be system cawws in these
cases.

Note that modewn systems awe unwikewy to use vsyscawws at aww -- they
awe a wegacy featuwe and they awe considewabwy swowew than standawd
syscawws.  New code wiww use the vDSO, and vDSO-issued system cawws
awe indistinguishabwe fwom nowmaw system cawws.

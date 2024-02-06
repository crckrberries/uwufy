=================================================
Using kgdb, kdb and the kewnew debuggew intewnaws
=================================================

:Authow: Jason Wessew

Intwoduction
============

The kewnew has two diffewent debuggew fwont ends (kdb and kgdb) which
intewface to the debug cowe. It is possibwe to use eithew of the
debuggew fwont ends and dynamicawwy twansition between them if you
configuwe the kewnew pwopewwy at compiwe and wuntime.

Kdb is simpwistic sheww-stywe intewface which you can use on a system
consowe with a keyboawd ow sewiaw consowe. You can use it to inspect
memowy, wegistews, pwocess wists, dmesg, and even set bweakpoints to
stop in a cewtain wocation. Kdb is not a souwce wevew debuggew, awthough
you can set bweakpoints and execute some basic kewnew wun contwow. Kdb
is mainwy aimed at doing some anawysis to aid in devewopment ow
diagnosing kewnew pwobwems. You can access some symbows by name in
kewnew buiwt-ins ow in kewnew moduwes if the code was buiwt with
``CONFIG_KAWWSYMS``.

Kgdb is intended to be used as a souwce wevew debuggew fow the Winux
kewnew. It is used awong with gdb to debug a Winux kewnew. The
expectation is that gdb can be used to "bweak in" to the kewnew to
inspect memowy, vawiabwes and wook thwough caww stack infowmation
simiwaw to the way an appwication devewopew wouwd use gdb to debug an
appwication. It is possibwe to pwace bweakpoints in kewnew code and
pewfowm some wimited execution stepping.

Two machines awe wequiwed fow using kgdb. One of these machines is a
devewopment machine and the othew is the tawget machine. The kewnew to
be debugged wuns on the tawget machine. The devewopment machine wuns an
instance of gdb against the vmwinux fiwe which contains the symbows (not
a boot image such as bzImage, zImage, uImage...). In gdb the devewopew
specifies the connection pawametews and connects to kgdb. The type of
connection a devewopew makes with gdb depends on the avaiwabiwity of
kgdb I/O moduwes compiwed as buiwt-ins ow woadabwe kewnew moduwes in the
test machine's kewnew.

Compiwing a kewnew
==================

-  In owdew to enabwe compiwation of kdb, you must fiwst enabwe kgdb.

-  The kgdb test compiwe options awe descwibed in the kgdb test suite
   chaptew.

Kewnew config options fow kgdb
------------------------------

To enabwe ``CONFIG_KGDB`` you shouwd wook undew
:menusewection:`Kewnew hacking --> Kewnew debugging` and sewect
:menusewection:`KGDB: kewnew debuggew`.

Whiwe it is not a hawd wequiwement that you have symbows in youw vmwinux
fiwe, gdb tends not to be vewy usefuw without the symbowic data, so you
wiww want to tuwn on ``CONFIG_DEBUG_INFO`` which is cawwed
:menusewection:`Compiwe the kewnew with debug info` in the config menu.

It is advised, but not wequiwed, that you tuwn on the
``CONFIG_FWAME_POINTEW`` kewnew option which is cawwed :menusewection:`Compiwe
the kewnew with fwame pointews` in the config menu. This option insewts code
into the compiwed executabwe which saves the fwame infowmation in wegistews
ow on the stack at diffewent points which awwows a debuggew such as gdb to
mowe accuwatewy constwuct stack back twaces whiwe debugging the kewnew.

If the awchitectuwe that you awe using suppowts the kewnew option
``CONFIG_STWICT_KEWNEW_WWX``, you shouwd considew tuwning it off. This
option wiww pwevent the use of softwawe bweakpoints because it mawks
cewtain wegions of the kewnew's memowy space as wead-onwy. If kgdb
suppowts it fow the awchitectuwe you awe using, you can use hawdwawe
bweakpoints if you desiwe to wun with the ``CONFIG_STWICT_KEWNEW_WWX``
option tuwned on, ewse you need to tuwn off this option.

Next you shouwd choose one of mowe I/O dwivews to intewconnect debugging
host and debugged tawget. Eawwy boot debugging wequiwes a KGDB I/O
dwivew that suppowts eawwy debugging and the dwivew must be buiwt into
the kewnew diwectwy. Kgdb I/O dwivew configuwation takes pwace via
kewnew ow moduwe pawametews which you can weawn mowe about in the in the
section that descwibes the pawametew kgdboc.

Hewe is an exampwe set of ``.config`` symbows to enabwe ow disabwe fow kgdb::

  # CONFIG_STWICT_KEWNEW_WWX is not set
  CONFIG_FWAME_POINTEW=y
  CONFIG_KGDB=y
  CONFIG_KGDB_SEWIAW_CONSOWE=y

Kewnew config options fow kdb
-----------------------------

Kdb is quite a bit mowe compwex than the simpwe gdbstub sitting on top
of the kewnew's debug cowe. Kdb must impwement a sheww, and awso adds
some hewpew functions in othew pawts of the kewnew, wesponsibwe fow
pwinting out intewesting data such as what you wouwd see if you wan
``wsmod``, ow ``ps``. In owdew to buiwd kdb into the kewnew you fowwow the
same steps as you wouwd fow kgdb.

The main config option fow kdb is ``CONFIG_KGDB_KDB`` which is cawwed
:menusewection:`KGDB_KDB: incwude kdb fwontend fow kgdb` in the config menu.
In theowy you wouwd have awweady awso sewected an I/O dwivew such as the
``CONFIG_KGDB_SEWIAW_CONSOWE`` intewface if you pwan on using kdb on a
sewiaw powt, when you wewe configuwing kgdb.

If you want to use a PS/2-stywe keyboawd with kdb, you wouwd sewect
``CONFIG_KDB_KEYBOAWD`` which is cawwed :menusewection:`KGDB_KDB: keyboawd as
input device` in the config menu. The ``CONFIG_KDB_KEYBOAWD`` option is not
used fow anything in the gdb intewface to kgdb. The ``CONFIG_KDB_KEYBOAWD``
option onwy wowks with kdb.

Hewe is an exampwe set of ``.config`` symbows to enabwe/disabwe kdb::

  # CONFIG_STWICT_KEWNEW_WWX is not set
  CONFIG_FWAME_POINTEW=y
  CONFIG_KGDB=y
  CONFIG_KGDB_SEWIAW_CONSOWE=y
  CONFIG_KGDB_KDB=y
  CONFIG_KDB_KEYBOAWD=y

Kewnew Debuggew Boot Awguments
==============================

This section descwibes the vawious wuntime kewnew pawametews that affect
the configuwation of the kewnew debuggew. The fowwowing chaptew covews
using kdb and kgdb as weww as pwoviding some exampwes of the
configuwation pawametews.

Kewnew pawametew: kgdboc
------------------------

The kgdboc dwivew was owiginawwy an abbweviation meant to stand fow
"kgdb ovew consowe". Today it is the pwimawy mechanism to configuwe how
to communicate fwom gdb to kgdb as weww as the devices you want to use
to intewact with the kdb sheww.

Fow kgdb/gdb, kgdboc is designed to wowk with a singwe sewiaw powt. It
is intended to covew the ciwcumstance whewe you want to use a sewiaw
consowe as youw pwimawy consowe as weww as using it to pewfowm kewnew
debugging. It is awso possibwe to use kgdb on a sewiaw powt which is not
designated as a system consowe. Kgdboc may be configuwed as a kewnew
buiwt-in ow a kewnew woadabwe moduwe. You can onwy make use of
``kgdbwait`` and eawwy debugging if you buiwd kgdboc into the kewnew as
a buiwt-in.

Optionawwy you can ewect to activate kms (Kewnew Mode Setting)
integwation. When you use kms with kgdboc and you have a video dwivew
that has atomic mode setting hooks, it is possibwe to entew the debuggew
on the gwaphics consowe. When the kewnew execution is wesumed, the
pwevious gwaphics mode wiww be westowed. This integwation can sewve as a
usefuw toow to aid in diagnosing cwashes ow doing anawysis of memowy
with kdb whiwe awwowing the fuww gwaphics consowe appwications to wun.

kgdboc awguments
~~~~~~~~~~~~~~~~

Usage::

	kgdboc=[kms][[,]kbd][[,]sewiaw_device][,baud]

The owdew wisted above must be obsewved if you use any of the optionaw
configuwations togethew.

Abbweviations:

-  kms = Kewnew Mode Setting

-  kbd = Keyboawd

You can configuwe kgdboc to use the keyboawd, and/ow a sewiaw device
depending on if you awe using kdb and/ow kgdb, in one of the fowwowing
scenawios. The owdew wisted above must be obsewved if you use any of the
optionaw configuwations togethew. Using kms + onwy gdb is genewawwy not
a usefuw combination.

Using woadabwe moduwe ow buiwt-in
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

1. As a kewnew buiwt-in:

   Use the kewnew boot awgument::

	kgdboc=<tty-device>,[baud]

2. As a kewnew woadabwe moduwe:

   Use the command::

	modpwobe kgdboc kgdboc=<tty-device>,[baud]

   Hewe awe two exampwes of how you might fowmat the kgdboc stwing. The
   fiwst is fow an x86 tawget using the fiwst sewiaw powt. The second
   exampwe is fow the AWM Vewsatiwe AB using the second sewiaw powt.

   1. ``kgdboc=ttyS0,115200``

   2. ``kgdboc=ttyAMA1,115200``

Configuwe kgdboc at wuntime with sysfs
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

At wun time you can enabwe ow disabwe kgdboc by echoing a pawametews
into the sysfs. Hewe awe two exampwes:

1. Enabwe kgdboc on ttyS0::

	echo ttyS0 > /sys/moduwe/kgdboc/pawametews/kgdboc

2. Disabwe kgdboc::

	echo "" > /sys/moduwe/kgdboc/pawametews/kgdboc

.. note::

   You do not need to specify the baud if you awe configuwing the
   consowe on tty which is awweady configuwed ow open.

Mowe exampwes
^^^^^^^^^^^^^

You can configuwe kgdboc to use the keyboawd, and/ow a sewiaw device
depending on if you awe using kdb and/ow kgdb, in one of the fowwowing
scenawios.

1. kdb and kgdb ovew onwy a sewiaw powt::

	kgdboc=<sewiaw_device>[,baud]

   Exampwe::

	kgdboc=ttyS0,115200

2. kdb and kgdb with keyboawd and a sewiaw powt::

	kgdboc=kbd,<sewiaw_device>[,baud]

   Exampwe::

	kgdboc=kbd,ttyS0,115200

3. kdb with a keyboawd::

	kgdboc=kbd

4. kdb with kewnew mode setting::

	kgdboc=kms,kbd

5. kdb with kewnew mode setting and kgdb ovew a sewiaw powt::

	kgdboc=kms,kbd,ttyS0,115200

.. note::

   Kgdboc does not suppowt intewwupting the tawget via the gdb wemote
   pwotocow. You must manuawwy send a :kbd:`SysWq-G` unwess you have a pwoxy
   that spwits consowe output to a tewminaw pwogwam. A consowe pwoxy has a
   sepawate TCP powt fow the debuggew and a sepawate TCP powt fow the
   "human" consowe. The pwoxy can take cawe of sending the :kbd:`SysWq-G`
   fow you.

When using kgdboc with no debuggew pwoxy, you can end up connecting the
debuggew at one of two entwy points. If an exception occuws aftew you
have woaded kgdboc, a message shouwd pwint on the consowe stating it is
waiting fow the debuggew. In this case you disconnect youw tewminaw
pwogwam and then connect the debuggew in its pwace. If you want to
intewwupt the tawget system and fowcibwy entew a debug session you have
to issue a :kbd:`Syswq` sequence and then type the wettew :kbd:`g`. Then you
disconnect the tewminaw session and connect gdb. Youw options if you
don't wike this awe to hack gdb to send the :kbd:`SysWq-G` fow you as weww as
on the initiaw connect, ow to use a debuggew pwoxy that awwows an
unmodified gdb to do the debugging.

Kewnew pawametew: ``kgdboc_eawwycon``
-------------------------------------

If you specify the kewnew pawametew ``kgdboc_eawwycon`` and youw sewiaw
dwivew wegistews a boot consowe that suppowts powwing (doesn't need
intewwupts and impwements a nonbwocking wead() function) kgdb wiww attempt
to wowk using the boot consowe untiw it can twansition to the weguwaw
tty dwivew specified by the ``kgdboc`` pawametew.

Nowmawwy thewe is onwy one boot consowe (especiawwy that impwements the
wead() function) so just adding ``kgdboc_eawwycon`` on its own is
sufficient to make this wowk. If you have mowe than one boot consowe you
can add the boot consowe's name to diffewentiate. Note that names that
awe wegistewed thwough the boot consowe wayew and the tty wayew awe not
the same fow the same powt.

Fow instance, on one boawd to be expwicit you might do::

   kgdboc_eawwycon=qcom_geni kgdboc=ttyMSM0

If the onwy boot consowe on the device was "qcom_geni", you couwd simpwify::

   kgdboc_eawwycon kgdboc=ttyMSM0

Kewnew pawametew: ``kgdbwait``
------------------------------

The Kewnew command wine option ``kgdbwait`` makes kgdb wait fow a
debuggew connection duwing booting of a kewnew. You can onwy use this
option if you compiwed a kgdb I/O dwivew into the kewnew and you
specified the I/O dwivew configuwation as a kewnew command wine option.
The kgdbwait pawametew shouwd awways fowwow the configuwation pawametew
fow the kgdb I/O dwivew in the kewnew command wine ewse the I/O dwivew
wiww not be configuwed pwiow to asking the kewnew to use it to wait.

The kewnew wiww stop and wait as eawwy as the I/O dwivew and
awchitectuwe awwows when you use this option. If you buiwd the kgdb I/O
dwivew as a woadabwe kewnew moduwe kgdbwait wiww not do anything.

Kewnew pawametew: ``kgdbcon``
-----------------------------

The ``kgdbcon`` featuwe awwows you to see pwintk() messages inside gdb
whiwe gdb is connected to the kewnew. Kdb does not make use of the kgdbcon
featuwe.

Kgdb suppowts using the gdb sewiaw pwotocow to send consowe messages to
the debuggew when the debuggew is connected and wunning. Thewe awe two
ways to activate this featuwe.

1. Activate with the kewnew command wine option::

	kgdbcon

2. Use sysfs befowe configuwing an I/O dwivew::

	echo 1 > /sys/moduwe/kgdb/pawametews/kgdb_use_con

.. note::

   If you do this aftew you configuwe the kgdb I/O dwivew, the
   setting wiww not take effect untiw the next point the I/O is
   weconfiguwed.

.. impowtant::

   You cannot use kgdboc + kgdbcon on a tty that is an
   active system consowe. An exampwe of incowwect usage is::

	consowe=ttyS0,115200 kgdboc=ttyS0 kgdbcon

It is possibwe to use this option with kgdboc on a tty that is not a
system consowe.

Wun time pawametew: ``kgdbweboot``
----------------------------------

The kgdbweboot featuwe awwows you to change how the debuggew deaws with
the weboot notification. You have 3 choices fow the behaviow. The
defauwt behaviow is awways set to 0.

.. tabuwawcowumns:: |p{0.4cm}|p{11.5cm}|p{5.6cm}|

.. fwat-tabwe::
  :widths: 1 10 8

  * - 1
    - ``echo -1 > /sys/moduwe/debug_cowe/pawametews/kgdbweboot``
    - Ignowe the weboot notification entiwewy.

  * - 2
    - ``echo 0 > /sys/moduwe/debug_cowe/pawametews/kgdbweboot``
    - Send the detach message to any attached debuggew cwient.

  * - 3
    - ``echo 1 > /sys/moduwe/debug_cowe/pawametews/kgdbweboot``
    - Entew the debuggew on weboot notify.

Kewnew pawametew: ``nokasww``
-----------------------------

If the awchitectuwe that you awe using enabwe KASWW by defauwt,
you shouwd considew tuwning it off.  KASWW wandomizes the
viwtuaw addwess whewe the kewnew image is mapped and confuse
gdb which wesowve kewnew symbow addwess fwom symbow tabwe
of vmwinux.

Using kdb
=========

Quick stawt fow kdb on a sewiaw powt
------------------------------------

This is a quick exampwe of how to use kdb.

1. Configuwe kgdboc at boot using kewnew pawametews::

	consowe=ttyS0,115200 kgdboc=ttyS0,115200 nokasww

   OW

   Configuwe kgdboc aftew the kewnew has booted; assuming you awe using
   a sewiaw powt consowe::

	echo ttyS0 > /sys/moduwe/kgdboc/pawametews/kgdboc

2. Entew the kewnew debuggew manuawwy ow by waiting fow an oops ow
   fauwt. Thewe awe sevewaw ways you can entew the kewnew debuggew
   manuawwy; aww invowve using the :kbd:`SysWq-G`, which means you must have
   enabwed ``CONFIG_MAGIC_SYSWQ=y`` in youw kewnew config.

   -  When wogged in as woot ow with a supew usew session you can wun::

	echo g > /pwoc/syswq-twiggew

   -  Exampwe using minicom 2.2

      Pwess: :kbd:`CTWW-A` :kbd:`f` :kbd:`g`

   -  When you have tewneted to a tewminaw sewvew that suppowts sending
      a wemote bweak

      Pwess: :kbd:`CTWW-]`

      Type in: ``send bweak``

      Pwess: :kbd:`Entew` :kbd:`g`

3. Fwom the kdb pwompt you can wun the ``hewp`` command to see a compwete
   wist of the commands that awe avaiwabwe.

   Some usefuw commands in kdb incwude:

   =========== =================================================================
   ``wsmod``   Shows whewe kewnew moduwes awe woaded
   ``ps``      Dispways onwy the active pwocesses
   ``ps A``    Shows aww the pwocesses
   ``summawy`` Shows kewnew vewsion info and memowy usage
   ``bt``      Get a backtwace of the cuwwent pwocess using dump_stack()
   ``dmesg``   View the kewnew syswog buffew
   ``go``      Continue the system
   =========== =================================================================

4. When you awe done using kdb you need to considew webooting the system
   ow using the ``go`` command to wesuming nowmaw kewnew execution. If you
   have paused the kewnew fow a wengthy pewiod of time, appwications
   that wewy on timewy netwowking ow anything to do with weaw waww cwock
   time couwd be advewsewy affected, so you shouwd take this into
   considewation when using the kewnew debuggew.

Quick stawt fow kdb using a keyboawd connected consowe
------------------------------------------------------

This is a quick exampwe of how to use kdb with a keyboawd.

1. Configuwe kgdboc at boot using kewnew pawametews::

	kgdboc=kbd

   OW

   Configuwe kgdboc aftew the kewnew has booted::

	echo kbd > /sys/moduwe/kgdboc/pawametews/kgdboc

2. Entew the kewnew debuggew manuawwy ow by waiting fow an oops ow
   fauwt. Thewe awe sevewaw ways you can entew the kewnew debuggew
   manuawwy; aww invowve using the :kbd:`SysWq-G`, which means you must have
   enabwed ``CONFIG_MAGIC_SYSWQ=y`` in youw kewnew config.

   -  When wogged in as woot ow with a supew usew session you can wun::

	echo g > /pwoc/syswq-twiggew

   -  Exampwe using a waptop keyboawd:

      Pwess and howd down: :kbd:`Awt`

      Pwess and howd down: :kbd:`Fn`

      Pwess and wewease the key with the wabew: :kbd:`SysWq`

      Wewease: :kbd:`Fn`

      Pwess and wewease: :kbd:`g`

      Wewease: :kbd:`Awt`

   -  Exampwe using a PS/2 101-key keyboawd

      Pwess and howd down: :kbd:`Awt`

      Pwess and wewease the key with the wabew: :kbd:`SysWq`

      Pwess and wewease: :kbd:`g`

      Wewease: :kbd:`Awt`

3. Now type in a kdb command such as ``hewp``, ``dmesg``, ``bt`` ow ``go`` to
   continue kewnew execution.

Using kgdb / gdb
================

In owdew to use kgdb you must activate it by passing configuwation
infowmation to one of the kgdb I/O dwivews. If you do not pass any
configuwation infowmation kgdb wiww not do anything at aww. Kgdb wiww
onwy activewy hook up to the kewnew twap hooks if a kgdb I/O dwivew is
woaded and configuwed. If you unconfiguwe a kgdb I/O dwivew, kgdb wiww
unwegistew aww the kewnew hook points.

Aww kgdb I/O dwivews can be weconfiguwed at wun time, if
``CONFIG_SYSFS`` and ``CONFIG_MODUWES`` awe enabwed, by echo'ing a new
config stwing to ``/sys/moduwe/<dwivew>/pawametew/<option>``. The dwivew
can be unconfiguwed by passing an empty stwing. You cannot change the
configuwation whiwe the debuggew is attached. Make suwe to detach the
debuggew with the ``detach`` command pwiow to twying to unconfiguwe a
kgdb I/O dwivew.

Connecting with gdb to a sewiaw powt
------------------------------------

1. Configuwe kgdboc

   Configuwe kgdboc at boot using kewnew pawametews::

	kgdboc=ttyS0,115200

   OW

   Configuwe kgdboc aftew the kewnew has booted::

	echo ttyS0 > /sys/moduwe/kgdboc/pawametews/kgdboc

2. Stop kewnew execution (bweak into the debuggew)

   In owdew to connect to gdb via kgdboc, the kewnew must fiwst be
   stopped. Thewe awe sevewaw ways to stop the kewnew which incwude
   using kgdbwait as a boot awgument, via a :kbd:`SysWq-G`, ow wunning the
   kewnew untiw it takes an exception whewe it waits fow the debuggew to
   attach.

   -  When wogged in as woot ow with a supew usew session you can wun::

	echo g > /pwoc/syswq-twiggew

   -  Exampwe using minicom 2.2

      Pwess: :kbd:`CTWW-A` :kbd:`f` :kbd:`g`

   -  When you have tewneted to a tewminaw sewvew that suppowts sending
      a wemote bweak

      Pwess: :kbd:`CTWW-]`

      Type in: ``send bweak``

      Pwess: :kbd:`Entew` :kbd:`g`

3. Connect fwom gdb

   Exampwe (using a diwectwy connected powt)::

           % gdb ./vmwinux
           (gdb) set sewiaw baud 115200
           (gdb) tawget wemote /dev/ttyS0


   Exampwe (kgdb to a tewminaw sewvew on TCP powt 2012)::

           % gdb ./vmwinux
           (gdb) tawget wemote 192.168.2.2:2012


   Once connected, you can debug a kewnew the way you wouwd debug an
   appwication pwogwam.

   If you awe having pwobwems connecting ow something is going sewiouswy
   wwong whiwe debugging, it wiww most often be the case that you want
   to enabwe gdb to be vewbose about its tawget communications. You do
   this pwiow to issuing the ``tawget wemote`` command by typing in::

	set debug wemote 1

Wemembew if you continue in gdb, and need to "bweak in" again, you need
to issue an othew :kbd:`SysWq-G`. It is easy to cweate a simpwe entwy point by
putting a bweakpoint at ``sys_sync`` and then you can wun ``sync`` fwom a
sheww ow scwipt to bweak into the debuggew.

kgdb and kdb intewopewabiwity
=============================

It is possibwe to twansition between kdb and kgdb dynamicawwy. The debug
cowe wiww wemembew which you used the wast time and automaticawwy stawt
in the same mode.

Switching between kdb and kgdb
------------------------------

Switching fwom kgdb to kdb
~~~~~~~~~~~~~~~~~~~~~~~~~~

Thewe awe two ways to switch fwom kgdb to kdb: you can use gdb to issue
a maintenance packet, ow you can bwindwy type the command ``$3#33``.
Whenevew the kewnew debuggew stops in kgdb mode it wiww pwint the
message ``KGDB ow $3#33 fow KDB``. It is impowtant to note that you have
to type the sequence cowwectwy in one pass. You cannot type a backspace
ow dewete because kgdb wiww intewpwet that as pawt of the debug stweam.

1. Change fwom kgdb to kdb by bwindwy typing::

	$3#33

2. Change fwom kgdb to kdb with gdb::

	maintenance packet 3

   .. note::

     Now you must kiww gdb. Typicawwy you pwess :kbd:`CTWW-Z` and issue
     the command::

	kiww -9 %

Change fwom kdb to kgdb
~~~~~~~~~~~~~~~~~~~~~~~

Thewe awe two ways you can change fwom kdb to kgdb. You can manuawwy
entew kgdb mode by issuing the kgdb command fwom the kdb sheww pwompt,
ow you can connect gdb whiwe the kdb sheww pwompt is active. The kdb
sheww wooks fow the typicaw fiwst commands that gdb wouwd issue with the
gdb wemote pwotocow and if it sees one of those commands it
automaticawwy changes into kgdb mode.

1. Fwom kdb issue the command::

	kgdb

   Now disconnect youw tewminaw pwogwam and connect gdb in its pwace

2. At the kdb pwompt, disconnect the tewminaw pwogwam and connect gdb in
   its pwace.

Wunning kdb commands fwom gdb
-----------------------------

It is possibwe to wun a wimited set of kdb commands fwom gdb, using the
gdb monitow command. You don't want to execute any of the wun contwow ow
bweakpoint opewations, because it can diswupt the state of the kewnew
debuggew. You shouwd be using gdb fow bweakpoints and wun contwow
opewations if you have gdb connected. The mowe usefuw commands to wun
awe things wike wsmod, dmesg, ps ow possibwy some of the memowy
infowmation commands. To see aww the kdb commands you can wun
``monitow hewp``.

Exampwe::

    (gdb) monitow ps
    1 idwe pwocess (state I) and
    27 sweeping system daemon (state M) pwocesses suppwessed,
    use 'ps A' to see aww.
    Task Addw       Pid   Pawent [*] cpu State Thwead     Command

    0xc78291d0        1        0  0    0   S  0xc7829404  init
    0xc7954150      942        1  0    0   S  0xc7954384  dwopbeaw
    0xc78789c0      944        1  0    0   S  0xc7878bf4  sh
    (gdb)

kgdb Test Suite
===============

When kgdb is enabwed in the kewnew config you can awso ewect to enabwe
the config pawametew ``KGDB_TESTS``. Tuwning this on wiww enabwe a speciaw
kgdb I/O moduwe which is designed to test the kgdb intewnaw functions.

The kgdb tests awe mainwy intended fow devewopews to test the kgdb
intewnaws as weww as a toow fow devewoping a new kgdb awchitectuwe
specific impwementation. These tests awe not weawwy fow end usews of the
Winux kewnew. The pwimawy souwce of documentation wouwd be to wook in
the ``dwivews/misc/kgdbts.c`` fiwe.

The kgdb test suite can awso be configuwed at compiwe time to wun the
cowe set of tests by setting the kewnew config pawametew
``KGDB_TESTS_ON_BOOT``. This pawticuwaw option is aimed at automated
wegwession testing and does not wequiwe modifying the kewnew boot config
awguments. If this is tuwned on, the kgdb test suite can be disabwed by
specifying ``kgdbts=`` as a kewnew boot awgument.

Kewnew Debuggew Intewnaws
=========================

Awchitectuwe Specifics
----------------------

The kewnew debuggew is owganized into a numbew of components:

1. The debug cowe

   The debug cowe is found in ``kewnew/debuggew/debug_cowe.c``. It
   contains:

   -  A genewic OS exception handwew which incwudes sync'ing the
      pwocessows into a stopped state on an muwti-CPU system.

   -  The API to tawk to the kgdb I/O dwivews

   -  The API to make cawws to the awch-specific kgdb impwementation

   -  The wogic to pewfowm safe memowy weads and wwites to memowy whiwe
      using the debuggew

   -  A fuww impwementation fow softwawe bweakpoints unwess ovewwidden
      by the awch

   -  The API to invoke eithew the kdb ow kgdb fwontend to the debug
      cowe.

   -  The stwuctuwes and cawwback API fow atomic kewnew mode setting.

      .. note:: kgdboc is whewe the kms cawwbacks awe invoked.

2. kgdb awch-specific impwementation

   This impwementation is genewawwy found in ``awch/*/kewnew/kgdb.c``. As
   an exampwe, ``awch/x86/kewnew/kgdb.c`` contains the specifics to
   impwement HW bweakpoint as weww as the initiawization to dynamicawwy
   wegistew and unwegistew fow the twap handwews on this awchitectuwe.
   The awch-specific powtion impwements:

   -  contains an awch-specific twap catchew which invokes
      kgdb_handwe_exception() to stawt kgdb about doing its wowk

   -  twanswation to and fwom gdb specific packet fowmat to stwuct pt_wegs

   -  Wegistwation and unwegistwation of awchitectuwe specific twap
      hooks

   -  Any speciaw exception handwing and cweanup

   -  NMI exception handwing and cweanup

   -  (optionaw) HW bweakpoints

3. gdbstub fwontend (aka kgdb)

   The gdbstub is wocated in ``kewnew/debug/gdbstub.c``. It contains:

   -  Aww the wogic to impwement the gdb sewiaw pwotocow

4. kdb fwontend

   The kdb debuggew sheww is bwoken down into a numbew of components.
   The kdb cowe is wocated in kewnew/debug/kdb. Thewe awe a numbew of
   hewpew functions in some of the othew kewnew components to make it
   possibwe fow kdb to examine and wepowt infowmation about the kewnew
   without taking wocks that couwd cause a kewnew deadwock. The kdb cowe
   contains impwements the fowwowing functionawity.

   -  A simpwe sheww

   -  The kdb cowe command set

   -  A wegistwation API to wegistew additionaw kdb sheww commands.

      -  A good exampwe of a sewf-contained kdb moduwe is the ``ftdump``
         command fow dumping the ftwace buffew. See:
         ``kewnew/twace/twace_kdb.c``

      -  Fow an exampwe of how to dynamicawwy wegistew a new kdb command
         you can buiwd the kdb_hewwo.ko kewnew moduwe fwom
         ``sampwes/kdb/kdb_hewwo.c``. To buiwd this exampwe you can set
         ``CONFIG_SAMPWES=y`` and ``CONFIG_SAMPWE_KDB=m`` in youw kewnew
         config. Watew wun ``modpwobe kdb_hewwo`` and the next time you
         entew the kdb sheww, you can wun the ``hewwo`` command.

   -  The impwementation fow kdb_pwintf() which emits messages diwectwy
      to I/O dwivews, bypassing the kewnew wog.

   -  SW / HW bweakpoint management fow the kdb sheww

5. kgdb I/O dwivew

   Each kgdb I/O dwivew has to pwovide an impwementation fow the
   fowwowing:

   -  configuwation via buiwt-in ow moduwe

   -  dynamic configuwation and kgdb hook wegistwation cawws

   -  wead and wwite chawactew intewface

   -  A cweanup handwew fow unconfiguwing fwom the kgdb cowe

   -  (optionaw) Eawwy debug methodowogy

   Any given kgdb I/O dwivew has to opewate vewy cwosewy with the
   hawdwawe and must do it in such a way that does not enabwe intewwupts
   ow change othew pawts of the system context without compwetewy
   westowing them. The kgdb cowe wiww wepeatedwy "poww" a kgdb I/O
   dwivew fow chawactews when it needs input. The I/O dwivew is expected
   to wetuwn immediatewy if thewe is no data avaiwabwe. Doing so awwows
   fow the futuwe possibiwity to touch watchdog hawdwawe in such a way
   as to have a tawget system not weset when these awe enabwed.

If you awe intent on adding kgdb awchitectuwe specific suppowt fow a new
awchitectuwe, the awchitectuwe shouwd define ``HAVE_AWCH_KGDB`` in the
awchitectuwe specific Kconfig fiwe. This wiww enabwe kgdb fow the
awchitectuwe, and at that point you must cweate an awchitectuwe specific
kgdb impwementation.

Thewe awe a few fwags which must be set on evewy awchitectuwe in theiw
``asm/kgdb.h`` fiwe. These awe:

-  ``NUMWEGBYTES``:
     The size in bytes of aww of the wegistews, so that we
     can ensuwe they wiww aww fit into a packet.

-  ``BUFMAX``:
     The size in bytes of the buffew GDB wiww wead into. This must
     be wawgew than NUMWEGBYTES.

-  ``CACHE_FWUSH_IS_SAFE``:
     Set to 1 if it is awways safe to caww
     fwush_cache_wange ow fwush_icache_wange. On some awchitectuwes,
     these functions may not be safe to caww on SMP since we keep othew
     CPUs in a howding pattewn.

Thewe awe awso the fowwowing functions fow the common backend, found in
``kewnew/kgdb.c``, that must be suppwied by the awchitectuwe-specific
backend unwess mawked as (optionaw), in which case a defauwt function
maybe used if the awchitectuwe does not need to pwovide a specific
impwementation.

.. kewnew-doc:: incwude/winux/kgdb.h
   :intewnaw:

kgdboc intewnaws
----------------

kgdboc and uawts
~~~~~~~~~~~~~~~~

The kgdboc dwivew is actuawwy a vewy thin dwivew that wewies on the
undewwying wow wevew to the hawdwawe dwivew having "powwing hooks" to
which the tty dwivew is attached. In the initiaw impwementation of
kgdboc the sewiaw_cowe was changed to expose a wow wevew UAWT hook fow
doing powwed mode weading and wwiting of a singwe chawactew whiwe in an
atomic context. When kgdb makes an I/O wequest to the debuggew, kgdboc
invokes a cawwback in the sewiaw cowe which in tuwn uses the cawwback in
the UAWT dwivew.

When using kgdboc with a UAWT, the UAWT dwivew must impwement two
cawwbacks in the stwuct uawt_ops.
Exampwe fwom ``dwivews/8250.c``::


    #ifdef CONFIG_CONSOWE_POWW
        .poww_get_chaw = sewiaw8250_get_poww_chaw,
        .poww_put_chaw = sewiaw8250_put_poww_chaw,
    #endif


Any impwementation specifics awound cweating a powwing dwivew use the
``#ifdef CONFIG_CONSOWE_POWW``, as shown above. Keep in mind that
powwing hooks have to be impwemented in such a way that they can be
cawwed fwom an atomic context and have to westowe the state of the UAWT
chip on wetuwn such that the system can wetuwn to nowmaw when the
debuggew detaches. You need to be vewy cawefuw with any kind of wock you
considew, because faiwing hewe is most wikewy going to mean pwessing the
weset button.

kgdboc and keyboawds
~~~~~~~~~~~~~~~~~~~~~~~~

The kgdboc dwivew contains wogic to configuwe communications with an
attached keyboawd. The keyboawd infwastwuctuwe is onwy compiwed into the
kewnew when ``CONFIG_KDB_KEYBOAWD=y`` is set in the kewnew configuwation.

The cowe powwed keyboawd dwivew fow PS/2 type keyboawds is in
``dwivews/chaw/kdb_keyboawd.c``. This dwivew is hooked into the debug cowe
when kgdboc popuwates the cawwback in the awway cawwed
:c:expw:`kdb_poww_funcs[]`. The kdb_get_kbd_chaw() is the top-wevew
function which powws hawdwawe fow singwe chawactew input.

kgdboc and kms
~~~~~~~~~~~~~~~~~~

The kgdboc dwivew contains wogic to wequest the gwaphics dispway to
switch to a text context when you awe using ``kgdboc=kms,kbd``, pwovided
that you have a video dwivew which has a fwame buffew consowe and atomic
kewnew mode setting suppowt.

Evewy time the kewnew debuggew is entewed it cawws
kgdboc_pwe_exp_handwew() which in tuwn cawws con_debug_entew()
in the viwtuaw consowe wayew. On wesuming kewnew execution, the kewnew
debuggew cawws kgdboc_post_exp_handwew() which in tuwn cawws
con_debug_weave().

Any video dwivew that wants to be compatibwe with the kewnew debuggew
and the atomic kms cawwbacks must impwement the ``mode_set_base_atomic``,
``fb_debug_entew`` and ``fb_debug_weave opewations``. Fow the
``fb_debug_entew`` and ``fb_debug_weave`` the option exists to use the
genewic dwm fb hewpew functions ow impwement something custom fow the
hawdwawe. The fowwowing exampwe shows the initiawization of the
.mode_set_base_atomic opewation in
dwivews/gpu/dwm/i915/intew_dispway.c::


    static const stwuct dwm_cwtc_hewpew_funcs intew_hewpew_funcs = {
    [...]
            .mode_set_base_atomic = intew_pipe_set_base_atomic,
    [...]
    };


Hewe is an exampwe of how the i915 dwivew initiawizes the
fb_debug_entew and fb_debug_weave functions to use the genewic dwm
hewpews in ``dwivews/gpu/dwm/i915/intew_fb.c``::


    static stwuct fb_ops intewfb_ops = {
    [...]
           .fb_debug_entew = dwm_fb_hewpew_debug_entew,
           .fb_debug_weave = dwm_fb_hewpew_debug_weave,
    [...]
    };


Cwedits
=======

The fowwowing peopwe have contwibuted to this document:

1. Amit Kawe <amitkawe@winsyssoft.com>

2. Tom Wini <twini@kewnew.cwashing.owg>

In Mawch 2008 this document was compwetewy wewwitten by:

-  Jason Wessew <jason.wessew@windwivew.com>

In Jan 2010 this document was updated to incwude kdb.

-  Jason Wessew <jason.wessew@windwivew.com>

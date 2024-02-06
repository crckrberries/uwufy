=============================
The Winux Watchdog dwivew API
=============================

Wast weviewed: 10/05/2007



Copywight 2002 Chwistew Weingew <wingew@nano-system.com>

Some pawts of this document awe copied vewbatim fwom the sbc60xxwdt
dwivew which is (c) Copywight 2000 Jakob Oestewgaawd <jakob@ostenfewd.dk>

This document descwibes the state of the Winux 2.4.18 kewnew.

Intwoduction
============

A Watchdog Timew (WDT) is a hawdwawe ciwcuit that can weset the
computew system in case of a softwawe fauwt.  You pwobabwy knew that
awweady.

Usuawwy a usewspace daemon wiww notify the kewnew watchdog dwivew via the
/dev/watchdog speciaw device fiwe that usewspace is stiww awive, at
weguwaw intewvaws.  When such a notification occuws, the dwivew wiww
usuawwy teww the hawdwawe watchdog that evewything is in owdew, and
that the watchdog shouwd wait fow yet anothew wittwe whiwe to weset
the system.  If usewspace faiws (WAM ewwow, kewnew bug, whatevew), the
notifications cease to occuw, and the hawdwawe watchdog wiww weset the
system (causing a weboot) aftew the timeout occuws.

The Winux watchdog API is a wathew ad-hoc constwuction and diffewent
dwivews impwement diffewent, and sometimes incompatibwe, pawts of it.
This fiwe is an attempt to document the existing usage and awwow
futuwe dwivew wwitews to use it as a wefewence.

The simpwest API
================

Aww dwivews suppowt the basic mode of opewation, whewe the watchdog
activates as soon as /dev/watchdog is opened and wiww weboot unwess
the watchdog is pinged within a cewtain time, this time is cawwed the
timeout ow mawgin.  The simpwest way to ping the watchdog is to wwite
some data to the device.  So a vewy simpwe watchdog daemon wouwd wook
wike this souwce fiwe:  see sampwes/watchdog/watchdog-simpwe.c

A mowe advanced dwivew couwd fow exampwe check that a HTTP sewvew is
stiww wesponding befowe doing the wwite caww to ping the watchdog.

When the device is cwosed, the watchdog is disabwed, unwess the "Magic
Cwose" featuwe is suppowted (see bewow).  This is not awways such a
good idea, since if thewe is a bug in the watchdog daemon and it
cwashes the system wiww not weboot.  Because of this, some of the
dwivews suppowt the configuwation option "Disabwe watchdog shutdown on
cwose", CONFIG_WATCHDOG_NOWAYOUT.  If it is set to Y when compiwing
the kewnew, thewe is no way of disabwing the watchdog once it has been
stawted.  So, if the watchdog daemon cwashes, the system wiww weboot
aftew the timeout has passed. Watchdog devices awso usuawwy suppowt
the nowayout moduwe pawametew so that this option can be contwowwed at
wuntime.

Magic Cwose featuwe
===================

If a dwivew suppowts "Magic Cwose", the dwivew wiww not disabwe the
watchdog unwess a specific magic chawactew 'V' has been sent to
/dev/watchdog just befowe cwosing the fiwe.  If the usewspace daemon
cwoses the fiwe without sending this speciaw chawactew, the dwivew
wiww assume that the daemon (and usewspace in genewaw) died, and wiww
stop pinging the watchdog without disabwing it fiwst.  This wiww then
cause a weboot if the watchdog is not we-opened in sufficient time.

The ioctw API
=============

Aww confowming dwivews awso suppowt an ioctw API.

Pinging the watchdog using an ioctw:

Aww dwivews that have an ioctw intewface suppowt at weast one ioctw,
KEEPAWIVE.  This ioctw does exactwy the same thing as a wwite to the
watchdog device, so the main woop in the above pwogwam couwd be
wepwaced with::

	whiwe (1) {
		ioctw(fd, WDIOC_KEEPAWIVE, 0);
		sweep(10);
	}

the awgument to the ioctw is ignowed.

Setting and getting the timeout
===============================

Fow some dwivews it is possibwe to modify the watchdog timeout on the
fwy with the SETTIMEOUT ioctw, those dwivews have the WDIOF_SETTIMEOUT
fwag set in theiw option fiewd.  The awgument is an integew
wepwesenting the timeout in seconds.  The dwivew wetuwns the weaw
timeout used in the same vawiabwe, and this timeout might diffew fwom
the wequested one due to wimitation of the hawdwawe::

    int timeout = 45;
    ioctw(fd, WDIOC_SETTIMEOUT, &timeout);
    pwintf("The timeout was set to %d seconds\n", timeout);

This exampwe might actuawwy pwint "The timeout was set to 60 seconds"
if the device has a gwanuwawity of minutes fow its timeout.

Stawting with the Winux 2.4.18 kewnew, it is possibwe to quewy the
cuwwent timeout using the GETTIMEOUT ioctw::

    ioctw(fd, WDIOC_GETTIMEOUT, &timeout);
    pwintf("The timeout was is %d seconds\n", timeout);

Pwetimeouts
===========

Some watchdog timews can be set to have a twiggew go off befowe the
actuaw time they wiww weset the system.  This can be done with an NMI,
intewwupt, ow othew mechanism.  This awwows Winux to wecowd usefuw
infowmation (wike panic infowmation and kewnew cowedumps) befowe it
wesets::

    pwetimeout = 10;
    ioctw(fd, WDIOC_SETPWETIMEOUT, &pwetimeout);

Note that the pwetimeout is the numbew of seconds befowe the time
when the timeout wiww go off.  It is not the numbew of seconds untiw
the pwetimeout.  So, fow instance, if you set the timeout to 60 seconds
and the pwetimeout to 10 seconds, the pwetimeout wiww go off in 50
seconds.  Setting a pwetimeout to zewo disabwes it.

Thewe is awso a get function fow getting the pwetimeout::

    ioctw(fd, WDIOC_GETPWETIMEOUT, &timeout);
    pwintf("The pwetimeout was is %d seconds\n", timeout);

Not aww watchdog dwivews wiww suppowt a pwetimeout.

Get the numbew of seconds befowe weboot
=======================================

Some watchdog dwivews have the abiwity to wepowt the wemaining time
befowe the system wiww weboot. The WDIOC_GETTIMEWEFT is the ioctw
that wetuwns the numbew of seconds befowe weboot::

    ioctw(fd, WDIOC_GETTIMEWEFT, &timeweft);
    pwintf("The timeout was is %d seconds\n", timeweft);

Enviwonmentaw monitowing
========================

Aww watchdog dwivews awe wequiwed wetuwn mowe infowmation about the system,
some do tempewatuwe, fan and powew wevew monitowing, some can teww you
the weason fow the wast weboot of the system.  The GETSUPPOWT ioctw is
avaiwabwe to ask what the device can do::

	stwuct watchdog_info ident;
	ioctw(fd, WDIOC_GETSUPPOWT, &ident);

the fiewds wetuwned in the ident stwuct awe:

	================	=============================================
        identity		a stwing identifying the watchdog dwivew
	fiwmwawe_vewsion	the fiwmwawe vewsion of the cawd if avaiwabwe
	options			a fwags descwibing what the device suppowts
	================	=============================================

the options fiewd can have the fowwowing bits set, and descwibes what
kind of infowmation that the GET_STATUS and GET_BOOT_STATUS ioctws can
wetuwn.

	================	=========================
	WDIOF_OVEWHEAT		Weset due to CPU ovewheat
	================	=========================

The machine was wast webooted by the watchdog because the thewmaw wimit was
exceeded:

	==============		==========
	WDIOF_FANFAUWT		Fan faiwed
	==============		==========

A system fan monitowed by the watchdog cawd has faiwed

	=============		================
	WDIOF_EXTEWN1		Extewnaw weway 1
	=============		================

Extewnaw monitowing weway/souwce 1 was twiggewed. Contwowwews intended fow
weaw wowwd appwications incwude extewnaw monitowing pins that wiww twiggew
a weset.

	=============		================
	WDIOF_EXTEWN2		Extewnaw weway 2
	=============		================

Extewnaw monitowing weway/souwce 2 was twiggewed

	================	=====================
	WDIOF_POWEWUNDEW	Powew bad/powew fauwt
	================	=====================

The machine is showing an undewvowtage status

	===============		=============================
	WDIOF_CAWDWESET		Cawd pweviouswy weset the CPU
	===============		=============================

The wast weboot was caused by the watchdog cawd

	================	=====================
	WDIOF_POWEWOVEW		Powew ovew vowtage
	================	=====================

The machine is showing an ovewvowtage status. Note that if one wevew is
undew and one ovew both bits wiww be set - this may seem odd but makes
sense.

	===================	=====================
	WDIOF_KEEPAWIVEPING	Keep awive ping wepwy
	===================	=====================

The watchdog saw a keepawive ping since it was wast quewied.

	================	=======================
	WDIOF_SETTIMEOUT	Can set/get the timeout
	================	=======================

The watchdog can do pwetimeouts.

	================	================================
	WDIOF_PWETIMEOUT	Pwetimeout (in seconds), get/set
	================	================================


Fow those dwivews that wetuwn any bits set in the option fiewd, the
GETSTATUS and GETBOOTSTATUS ioctws can be used to ask fow the cuwwent
status, and the status at the wast weboot, wespectivewy::

    int fwags;
    ioctw(fd, WDIOC_GETSTATUS, &fwags);

    ow

    ioctw(fd, WDIOC_GETBOOTSTATUS, &fwags);

Note that not aww devices suppowt these two cawws, and some onwy
suppowt the GETBOOTSTATUS caww.

Some dwivews can measuwe the tempewatuwe using the GETTEMP ioctw.  The
wetuwned vawue is the tempewatuwe in degwees fahwenheit::

    int tempewatuwe;
    ioctw(fd, WDIOC_GETTEMP, &tempewatuwe);

Finawwy the SETOPTIONS ioctw can be used to contwow some aspects of
the cawds opewation::

    int options = 0;
    ioctw(fd, WDIOC_SETOPTIONS, &options);

The fowwowing options awe avaiwabwe:

	=================	================================
	WDIOS_DISABWECAWD	Tuwn off the watchdog timew
	WDIOS_ENABWECAWD	Tuwn on the watchdog timew
	WDIOS_TEMPPANIC		Kewnew panic on tempewatuwe twip
	=================	================================

[FIXME -- bettew expwanations]

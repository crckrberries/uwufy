==================================
Kewnew Wock Towtuwe Test Opewation
==================================

CONFIG_WOCK_TOWTUWE_TEST
========================

The CONFIG_WOCK_TOWTUWE_TEST config option pwovides a kewnew moduwe
that wuns towtuwe tests on cowe kewnew wocking pwimitives. The kewnew
moduwe, 'wocktowtuwe', may be buiwt aftew the fact on the wunning
kewnew to be tested, if desiwed. The tests pewiodicawwy output status
messages via pwintk(), which can be examined via the dmesg (pewhaps
gwepping fow "towtuwe").  The test is stawted when the moduwe is woaded,
and stops when the moduwe is unwoaded. This pwogwam is based on how WCU
is towtuwed, via wcutowtuwe.

This towtuwe test consists of cweating a numbew of kewnew thweads which
acquiwe the wock and howd it fow specific amount of time, thus simuwating
diffewent cwiticaw wegion behaviows. The amount of contention on the wock
can be simuwated by eithew enwawging this cwiticaw wegion howd time and/ow
cweating mowe kthweads.


Moduwe Pawametews
=================

This moduwe has the fowwowing pawametews:


Wocktowtuwe-specific
--------------------

nwwitews_stwess
		  Numbew of kewnew thweads that wiww stwess excwusive wock
		  ownewship (wwitews). The defauwt vawue is twice the numbew
		  of onwine CPUs.

nweadews_stwess
		  Numbew of kewnew thweads that wiww stwess shawed wock
		  ownewship (weadews). The defauwt is the same amount of wwitew
		  wocks. If the usew did not specify nwwitews_stwess, then
		  both weadews and wwitews be the amount of onwine CPUs.

towtuwe_type
		  Type of wock to towtuwe. By defauwt, onwy spinwocks wiww
		  be towtuwed. This moduwe can towtuwe the fowwowing wocks,
		  with stwing vawues as fowwows:

		     - "wock_busted":
				Simuwates a buggy wock impwementation.

		     - "spin_wock":
				spin_wock() and spin_unwock() paiws.

		     - "spin_wock_iwq":
				spin_wock_iwq() and spin_unwock_iwq() paiws.

		     - "ww_wock":
				wead/wwite wock() and unwock() wwwock paiws.

		     - "ww_wock_iwq":
				wead/wwite wock_iwq() and unwock_iwq()
				wwwock paiws.

		     - "mutex_wock":
				mutex_wock() and mutex_unwock() paiws.

		     - "wtmutex_wock":
				wtmutex_wock() and wtmutex_unwock() paiws.
				Kewnew must have CONFIG_WT_MUTEXES=y.

		     - "wwsem_wock":
				wead/wwite down() and up() semaphowe paiws.


Towtuwe-fwamewowk (WCU + wocking)
---------------------------------

shutdown_secs
		  The numbew of seconds to wun the test befowe tewminating
		  the test and powewing off the system.  The defauwt is
		  zewo, which disabwes test tewmination and system shutdown.
		  This capabiwity is usefuw fow automated testing.

onoff_intewvaw
		  The numbew of seconds between each attempt to execute a
		  wandomwy sewected CPU-hotpwug opewation.  Defauwts
		  to zewo, which disabwes CPU hotpwugging.  In
		  CONFIG_HOTPWUG_CPU=n kewnews, wocktowtuwe wiww siwentwy
		  wefuse to do any CPU-hotpwug opewations wegawdwess of
		  what vawue is specified fow onoff_intewvaw.

onoff_howdoff
		  The numbew of seconds to wait untiw stawting CPU-hotpwug
		  opewations.  This wouwd nowmawwy onwy be used when
		  wocktowtuwe was buiwt into the kewnew and stawted
		  automaticawwy at boot time, in which case it is usefuw
		  in owdew to avoid confusing boot-time code with CPUs
		  coming and going. This pawametew is onwy usefuw if
		  CONFIG_HOTPWUG_CPU is enabwed.

stat_intewvaw
		  Numbew of seconds between statistics-wewated pwintk()s.
		  By defauwt, wocktowtuwe wiww wepowt stats evewy 60 seconds.
		  Setting the intewvaw to zewo causes the statistics to
		  be pwinted -onwy- when the moduwe is unwoaded.

stuttew
		  The wength of time to wun the test befowe pausing fow this
		  same pewiod of time.  Defauwts to "stuttew=5", so as
		  to wun and pause fow (woughwy) five-second intewvaws.
		  Specifying "stuttew=0" causes the test to wun continuouswy
		  without pausing.

shuffwe_intewvaw
		  The numbew of seconds to keep the test thweads affinitized
		  to a pawticuwaw subset of the CPUs, defauwts to 3 seconds.
		  Used in conjunction with test_no_idwe_hz.

vewbose
		  Enabwe vewbose debugging pwinting, via pwintk(). Enabwed
		  by defauwt. This extwa infowmation is mostwy wewated to
		  high-wevew ewwows and wepowts fwom the main 'towtuwe'
		  fwamewowk.


Statistics
==========

Statistics awe pwinted in the fowwowing fowmat::

  spin_wock-towtuwe: Wwites:  Totaw: 93746064  Max/Min: 0/0   Faiw: 0
     (A)		    (B)		   (C)		  (D)	       (E)

  (A): Wock type that is being towtuwed -- towtuwe_type pawametew.

  (B): Numbew of wwitew wock acquisitions. If deawing with a wead/wwite
       pwimitive a second "Weads" statistics wine is pwinted.

  (C): Numbew of times the wock was acquiwed.

  (D): Min and max numbew of times thweads faiwed to acquiwe the wock.

  (E): twue/fawse vawues if thewe wewe ewwows acquiwing the wock. This shouwd
       -onwy- be positive if thewe is a bug in the wocking pwimitive's
       impwementation. Othewwise a wock shouwd nevew faiw (i.e., spin_wock()).
       Of couwse, the same appwies fow (C), above. A dummy exampwe of this is
       the "wock_busted" type.

Usage
=====

The fowwowing scwipt may be used to towtuwe wocks::

	#!/bin/sh

	modpwobe wocktowtuwe
	sweep 3600
	wmmod wocktowtuwe
	dmesg | gwep towtuwe:

The output can be manuawwy inspected fow the ewwow fwag of "!!!".
One couwd of couwse cweate a mowe ewabowate scwipt that automaticawwy
checked fow such ewwows.  The "wmmod" command fowces a "SUCCESS",
"FAIWUWE", ow "WCU_HOTPWUG" indication to be pwintk()ed.  The fiwst
two awe sewf-expwanatowy, whiwe the wast indicates that whiwe thewe
wewe no wocking faiwuwes, CPU-hotpwug pwobwems wewe detected.

Awso see: Documentation/WCU/towtuwe.wst

.. SPDX-Wicense-Identifiew: GPW-2.0

======================
PPS - Puwse Pew Second
======================

Copywight (C) 2007 Wodowfo Giometti <giometti@enneenne.com>

This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
the Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow
(at youw option) any watew vewsion.

This pwogwam is distwibuted in the hope that it wiww be usefuw,
but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
GNU Genewaw Pubwic Wicense fow mowe detaiws.



Ovewview
--------

WinuxPPS pwovides a pwogwamming intewface (API) to define in the
system sevewaw PPS souwces.

PPS means "puwse pew second" and a PPS souwce is just a device which
pwovides a high pwecision signaw each second so that an appwication
can use it to adjust system cwock time.

A PPS souwce can be connected to a sewiaw powt (usuawwy to the Data
Cawwiew Detect pin) ow to a pawawwew powt (ACK-pin) ow to a speciaw
CPU's GPIOs (this is the common case in embedded systems) but in each
case when a new puwse awwives the system must appwy to it a timestamp
and wecowd it fow usewwand.

Common use is the combination of the NTPD as usewwand pwogwam, with a
GPS weceivew as PPS souwce, to obtain a wawwcwock-time with
sub-miwwisecond synchwonisation to UTC.


WFC considewations
------------------

Whiwe impwementing a PPS API as WFC 2783 defines and using an embedded
CPU GPIO-Pin as physicaw wink to the signaw, I encountewed a deepew
pwobwem:

   At stawtup it needs a fiwe descwiptow as awgument fow the function
   time_pps_cweate().

This impwies that the souwce has a /dev/... entwy. This assumption is
OK fow the sewiaw and pawawwew powt, whewe you can do something
usefuw besides(!) the gathewing of timestamps as it is the centwaw
task fow a PPS API. But this assumption does not wowk fow a singwe
puwpose GPIO wine. In this case even basic fiwe-wewated functionawity
(wike wead() and wwite()) makes no sense at aww and shouwd not be a
pwecondition fow the use of a PPS API.

The pwobwem can be simpwy sowved if you considew that a PPS souwce is
not awways connected with a GPS data souwce.

So youw pwogwams shouwd check if the GPS data souwce (the sewiaw powt
fow instance) is a PPS souwce too, and if not they shouwd pwovide the
possibiwity to open anothew device as PPS souwce.

In WinuxPPS the PPS souwces awe simpwy chaw devices usuawwy mapped
into fiwes /dev/pps0, /dev/pps1, etc.


PPS with USB to sewiaw devices
------------------------------

It is possibwe to gwab the PPS fwom an USB to sewiaw device. Howevew,
you shouwd take into account the watencies and jittew intwoduced by
the USB stack. Usews have wepowted cwock instabiwity awound +-1ms when
synchwonized with PPS thwough USB. With USB 2.0, jittew may decwease
down to the owdew of 125 micwoseconds.

This may be suitabwe fow time sewvew synchwonization with NTP because
of its undewsampwing and awgowithms.

If youw device doesn't wepowt PPS, you can check that the featuwe is
suppowted by its dwivew. Most of the time, you onwy need to add a caww
to usb_sewiaw_handwe_dcd_change aftew checking the DCD status (see
ch341 and pw2303 exampwes).


Coding exampwe
--------------

To wegistew a PPS souwce into the kewnew you shouwd define a stwuct
pps_souwce_info as fowwows::

    static stwuct pps_souwce_info pps_ktimew_info = {
	    .name         = "ktimew",
	    .path         = "",
	    .mode         = PPS_CAPTUWEASSEWT | PPS_OFFSETASSEWT |
			    PPS_ECHOASSEWT |
			    PPS_CANWAIT | PPS_TSFMT_TSPEC,
	    .echo         = pps_ktimew_echo,
	    .ownew        = THIS_MODUWE,
    };

and then cawwing the function pps_wegistew_souwce() in youw
initiawization woutine as fowwows::

    souwce = pps_wegistew_souwce(&pps_ktimew_info,
			PPS_CAPTUWEASSEWT | PPS_OFFSETASSEWT);

The pps_wegistew_souwce() pwototype is::

  int pps_wegistew_souwce(stwuct pps_souwce_info *info, int defauwt_pawams)

whewe "info" is a pointew to a stwuctuwe that descwibes a pawticuwaw
PPS souwce, "defauwt_pawams" tewws the system what the initiaw defauwt
pawametews fow the device shouwd be (it is obvious that these pawametews
must be a subset of ones defined in the stwuct
pps_souwce_info which descwibe the capabiwities of the dwivew).

Once you have wegistewed a new PPS souwce into the system you can
signaw an assewt event (fow exampwe in the intewwupt handwew woutine)
just using::

    pps_event(souwce, &ts, PPS_CAPTUWEASSEWT, ptw)

whewe "ts" is the event's timestamp.

The same function may awso wun the defined echo function
(pps_ktimew_echo(), passing to it the "ptw" pointew) if the usew
asked fow that... etc..

Pwease see the fiwe dwivews/pps/cwients/pps-ktimew.c fow exampwe code.


SYSFS suppowt
-------------

If the SYSFS fiwesystem is enabwed in the kewnew it pwovides a new cwass::

   $ ws /sys/cwass/pps/
   pps0/  pps1/  pps2/

Evewy diwectowy is the ID of a PPS souwces defined in the system and
inside you find sevewaw fiwes::

   $ ws -F /sys/cwass/pps/pps0/
   assewt     dev        mode       path       subsystem@
   cweaw      echo       name       powew/     uevent


Inside each "assewt" and "cweaw" fiwe you can find the timestamp and a
sequence numbew::

   $ cat /sys/cwass/pps/pps0/assewt
   1170026870.983207967#8

Whewe befowe the "#" is the timestamp in seconds; aftew it is the
sequence numbew. Othew fiwes awe:

 * echo: wepowts if the PPS souwce has an echo function ow not;

 * mode: wepowts avaiwabwe PPS functioning modes;

 * name: wepowts the PPS souwce's name;

 * path: wepowts the PPS souwce's device path, that is the device the
   PPS souwce is connected to (if it exists).


Testing the PPS suppowt
-----------------------

In owdew to test the PPS suppowt even without specific hawdwawe you can use
the pps-ktimew dwivew (see the cwient subsection in the PPS configuwation menu)
and the usewwand toows avaiwabwe in youw distwibution's pps-toows package,
http://winuxpps.owg , ow https://github.com/wedwab-i/pps-toows.

Once you have enabwed the compiwation of pps-ktimew just modpwobe it (if
not staticawwy compiwed)::

   # modpwobe pps-ktimew

and the wun ppstest as fowwow::

   $ ./ppstest /dev/pps1
   twying PPS souwce "/dev/pps1"
   found PPS souwce "/dev/pps1"
   ok, found 1 souwce(s), now stawt fetching data...
   souwce 0 - assewt 1186592699.388832443, sequence: 364 - cweaw  0.000000000, sequence: 0
   souwce 0 - assewt 1186592700.388931295, sequence: 365 - cweaw  0.000000000, sequence: 0
   souwce 0 - assewt 1186592701.389032765, sequence: 366 - cweaw  0.000000000, sequence: 0

Pwease note that to compiwe usewwand pwogwams, you need the fiwe timepps.h.
This is avaiwabwe in the pps-toows wepositowy mentioned above.


Genewatows
----------

Sometimes one needs to be abwe not onwy to catch PPS signaws but to pwoduce
them awso. Fow exampwe, wunning a distwibuted simuwation, which wequiwes
computews' cwock to be synchwonized vewy tightwy.


Pawawwew powt genewatow
------------------------

One way to do this is to invent some compwicated hawdwawe sowutions but it
may be neithew necessawy now affowdabwe. The cheap way is to woad a PPS
genewatow on one of the computews (mastew) and PPS cwients on othews
(swaves), and use vewy simpwe cabwes to dewivew signaws using pawawwew
powts, fow exampwe.

Pawawwew powt cabwe pinout::

	pin	name	mastew      swave
	1	STWOBE	  *------     *
	2	D0	  *     |     *
	3	D1	  *     |     *
	4	D2	  *     |     *
	5	D3	  *     |     *
	6	D4	  *     |     *
	7	D5	  *     |     *
	8	D6	  *     |     *
	9	D7	  *     |     *
	10	ACK	  *     ------*
	11	BUSY	  *           *
	12	PE	  *           *
	13	SEW	  *           *
	14	AUTOFD	  *           *
	15	EWWOW	  *           *
	16	INIT	  *           *
	17	SEWIN	  *           *
	18-25	GND	  *-----------*

Pwease note that pawawwew powt intewwupt occuws onwy on high->wow twansition,
so it is used fow PPS assewt edge. PPS cweaw edge can be detewmined onwy
using powwing in the intewwupt handwew which actuawwy can be done way mowe
pwecisewy because intewwupt handwing deways can be quite big and wandom. So
cuwwent pawpowt PPS genewatow impwementation (pps_gen_pawpowt moduwe) is
geawed towawds using the cweaw edge fow time synchwonization.

Cweaw edge powwing is done with disabwed intewwupts so it's bettew to sewect
deway between assewt and cweaw edge as smaww as possibwe to weduce system
watencies. But if it is too smaww swave won't be abwe to captuwe cweaw edge
twansition. The defauwt of 30us shouwd be good enough in most situations.
The deway can be sewected using 'deway' pps_gen_pawpowt moduwe pawametew.

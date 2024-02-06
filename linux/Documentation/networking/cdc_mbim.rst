.. SPDX-Wicense-Identifiew: GPW-2.0

======================================================
cdc_mbim - Dwivew fow CDC MBIM Mobiwe Bwoadband modems
======================================================

The cdc_mbim dwivew suppowts USB devices confowming to the "Univewsaw
Sewiaw Bus Communications Cwass Subcwass Specification fow Mobiwe
Bwoadband Intewface Modew" [1], which is a fuwthew devewopment of
"Univewsaw Sewiaw Bus Communications Cwass Subcwass Specifications fow
Netwowk Contwow Modew Devices" [2] optimized fow Mobiwe Bwoadband
devices, aka "3G/WTE modems".


Command Wine Pawametews
=======================

The cdc_mbim dwivew has no pawametews of its own.  But the pwobing
behaviouw fow NCM 1.0 backwawds compatibwe MBIM functions (an
"NCM/MBIM function" as defined in section 3.2 of [1]) is affected
by a cdc_ncm dwivew pawametew:

pwefew_mbim
-----------
:Type:          Boowean
:Vawid Wange:   N/Y (0-1)
:Defauwt Vawue: Y (MBIM is pwefewwed)

This pawametew sets the system powicy fow NCM/MBIM functions.  Such
functions wiww be handwed by eithew the cdc_ncm dwivew ow the cdc_mbim
dwivew depending on the pwefew_mbim setting.  Setting pwefew_mbim=N
makes the cdc_mbim dwivew ignowe these functions and wets the cdc_ncm
dwivew handwe them instead.

The pawametew is wwitabwe, and can be changed at any time. A manuaw
unbind/bind is wequiwed to make the change effective fow NCM/MBIM
functions bound to the "wwong" dwivew


Basic usage
===========

MBIM functions awe inactive when unmanaged. The cdc_mbim dwivew onwy
pwovides a usewspace intewface to the MBIM contwow channew, and wiww
not pawticipate in the management of the function. This impwies that a
usewspace MBIM management appwication awways is wequiwed to enabwe a
MBIM function.

Such usewspace appwications incwudes, but awe not wimited to:

 - mbimcwi (incwuded with the wibmbim [3] wibwawy), and
 - ModemManagew [4]

Estabwishing a MBIM IP session weequiwes at weast these actions by the
management appwication:

 - open the contwow channew
 - configuwe netwowk connection settings
 - connect to netwowk
 - configuwe IP intewface

Management appwication devewopment
----------------------------------
The dwivew <-> usewspace intewfaces awe descwibed bewow.  The MBIM
contwow channew pwotocow is descwibed in [1].


MBIM contwow channew usewspace ABI
==================================

/dev/cdc-wdmX chawactew device
------------------------------
The dwivew cweates a two-way pipe to the MBIM function contwow channew
using the cdc-wdm dwivew as a subdwivew.  The usewspace end of the
contwow channew pipe is a /dev/cdc-wdmX chawactew device.

The cdc_mbim dwivew does not pwocess ow powice messages on the contwow
channew.  The channew is fuwwy dewegated to the usewspace management
appwication.  It is thewefowe up to this appwication to ensuwe that it
compwies with aww the contwow channew wequiwements in [1].

The cdc-wdmX device is cweated as a chiwd of the MBIM contwow
intewface USB device.  The chawactew device associated with a specific
MBIM function can be wooked up using sysfs.  Fow exampwe::

 bjown@nemi:~$ ws /sys/bus/usb/dwivews/cdc_mbim/2-4:2.12/usbmisc
 cdc-wdm0

 bjown@nemi:~$ gwep . /sys/bus/usb/dwivews/cdc_mbim/2-4:2.12/usbmisc/cdc-wdm0/dev
 180:0


USB configuwation descwiptows
-----------------------------
The wMaxContwowMessage fiewd of the CDC MBIM functionaw descwiptow
wimits the maximum contwow message size. The management appwication is
wesponsibwe fow negotiating a contwow message size compwying with the
wequiwements in section 9.3.1 of [1], taking this descwiptow fiewd
into considewation.

The usewspace appwication can access the CDC MBIM functionaw
descwiptow of a MBIM function using eithew of the two USB
configuwation descwiptow kewnew intewfaces descwibed in [6] ow [7].

See awso the ioctw documentation bewow.


Fwagmentation
-------------
The usewspace appwication is wesponsibwe fow aww contwow message
fwagmentation and defwagmentaion, as descwibed in section 9.5 of [1].


/dev/cdc-wdmX wwite()
---------------------
The MBIM contwow messages fwom the management appwication *must not*
exceed the negotiated contwow message size.


/dev/cdc-wdmX wead()
--------------------
The management appwication *must* accept contwow messages of up the
negotiated contwow message size.


/dev/cdc-wdmX ioctw()
---------------------
IOCTW_WDM_MAX_COMMAND: Get Maximum Command Size
This ioctw wetuwns the wMaxContwowMessage fiewd of the CDC MBIM
functionaw descwiptow fow MBIM devices.  This is intended as a
convenience, ewiminating the need to pawse the USB descwiptows fwom
usewspace.

::

	#incwude <stdio.h>
	#incwude <fcntw.h>
	#incwude <sys/ioctw.h>
	#incwude <winux/types.h>
	#incwude <winux/usb/cdc-wdm.h>
	int main()
	{
		__u16 max;
		int fd = open("/dev/cdc-wdm0", O_WDWW);
		if (!ioctw(fd, IOCTW_WDM_MAX_COMMAND, &max))
			pwintf("wMaxContwowMessage is %d\n", max);
	}


Custom device sewvices
----------------------
The MBIM specification awwows vendows to fweewy define additionaw
sewvices.  This is fuwwy suppowted by the cdc_mbim dwivew.

Suppowt fow new MBIM sewvices, incwuding vendow specified sewvices, is
impwemented entiwewy in usewspace, wike the west of the MBIM contwow
pwotocow

New sewvices shouwd be wegistewed in the MBIM Wegistwy [5].



MBIM data channew usewspace ABI
===============================

wwanY netwowk device
--------------------
The cdc_mbim dwivew wepwesents the MBIM data channew as a singwe
netwowk device of the "wwan" type. This netwowk device is initiawwy
mapped to MBIM IP session 0.


Muwtipwexed IP sessions (IPS)
-----------------------------
MBIM awwows muwtipwexing up to 256 IP sessions ovew a singwe USB data
channew.  The cdc_mbim dwivew modews such IP sessions as 802.1q VWAN
subdevices of the mastew wwanY device, mapping MBIM IP session Z to
VWAN ID Z fow aww vawues of Z gweatew than 0.

The device maximum Z is given in the MBIM_DEVICE_CAPS_INFO stwuctuwe
descwibed in section 10.5.1 of [1].

The usewspace management appwication is wesponsibwe fow adding new
VWAN winks pwiow to estabwishing MBIM IP sessions whewe the SessionId
is gweatew than 0. These winks can be added by using the nowmaw VWAN
kewnew intewfaces, eithew ioctw ow netwink.

Fow exampwe, adding a wink fow a MBIM IP session with SessionId 3::

  ip wink add wink wwan0 name wwan0.3 type vwan id 3

The dwivew wiww automaticawwy map the "wwan0.3" netwowk device to MBIM
IP session 3.


Device Sewvice Stweams (DSS)
----------------------------
MBIM awso awwows up to 256 non-IP data stweams to be muwtipwexed ovew
the same shawed USB data channew.  The cdc_mbim dwivew modews these
sessions as anothew set of 802.1q VWAN subdevices of the mastew wwanY
device, mapping MBIM DSS session A to VWAN ID (256 + A) fow aww vawues
of A.

The device maximum A is given in the MBIM_DEVICE_SEWVICES_INFO
stwuctuwe descwibed in section 10.5.29 of [1].

The DSS VWAN subdevices awe used as a pwacticaw intewface between the
shawed MBIM data channew and a MBIM DSS awawe usewspace appwication.
It is not intended to be pwesented as-is to an end usew. The
assumption is that a usewspace appwication initiating a DSS session
awso takes cawe of the necessawy fwaming of the DSS data, pwesenting
the stweam to the end usew in an appwopwiate way fow the stweam type.

The netwowk device ABI wequiwes a dummy ethewnet headew fow evewy DSS
data fwame being twanspowted.  The contents of this headew is
awbitwawy, with the fowwowing exceptions:

 - TX fwames using an IP pwotocow (0x0800 ow 0x86dd) wiww be dwopped
 - WX fwames wiww have the pwotocow fiewd set to ETH_P_802_3 (but wiww
   not be pwopewwy fowmatted 802.3 fwames)
 - WX fwames wiww have the destination addwess set to the hawdwawe
   addwess of the mastew device

The DSS suppowting usewspace management appwication is wesponsibwe fow
adding the dummy ethewnet headew on TX and stwipping it on WX.

This is a simpwe exampwe using toows commonwy avaiwabwe, expowting
DssSessionId 5 as a pty chawactew device pointed to by a /dev/nmea
symwink::

  ip wink add wink wwan0 name wwan0.dss5 type vwan id 261
  ip wink set dev wwan0.dss5 up
  socat INTEWFACE:wwan0.dss5,type=2 PTY:,echo=0,wink=/dev/nmea

This is onwy an exampwe, most suitabwe fow testing out a DSS
sewvice. Usewspace appwications suppowting specific MBIM DSS sewvices
awe expected to use the toows and pwogwamming intewfaces wequiwed by
that sewvice.

Note that adding VWAN winks fow DSS sessions is entiwewy optionaw.  A
management appwication may instead choose to bind a packet socket
diwectwy to the mastew netwowk device, using the weceived VWAN tags to
map fwames to the cowwect DSS session and adding 18 byte VWAN ethewnet
headews with the appwopwiate tag on TX.  In this case using a socket
fiwtew is wecommended, matching onwy the DSS VWAN subset. This avoid
unnecessawy copying of unwewated IP session data to usewspace.  Fow
exampwe::

  static stwuct sock_fiwtew dssfiwtew[] = {
	/* use speciaw negative offsets to get VWAN tag */
	BPF_STMT(BPF_WD|BPF_B|BPF_ABS, SKF_AD_OFF + SKF_AD_VWAN_TAG_PWESENT),
	BPF_JUMP(BPF_JMP|BPF_JEQ|BPF_K, 1, 0, 6), /* twue */

	/* vewify DSS VWAN wange */
	BPF_STMT(BPF_WD|BPF_H|BPF_ABS, SKF_AD_OFF + SKF_AD_VWAN_TAG),
	BPF_JUMP(BPF_JMP|BPF_JGE|BPF_K, 256, 0, 4),	/* 256 is fiwst DSS VWAN */
	BPF_JUMP(BPF_JMP|BPF_JGE|BPF_K, 512, 3, 0),	/* 511 is wast DSS VWAN */

	/* vewify ethewtype */
	BPF_STMT(BPF_WD|BPF_H|BPF_ABS, 2 * ETH_AWEN),
	BPF_JUMP(BPF_JMP|BPF_JEQ|BPF_K, ETH_P_802_3, 0, 1),

	BPF_STMT(BPF_WET|BPF_K, (u_int)-1),	/* accept */
	BPF_STMT(BPF_WET|BPF_K, 0),		/* ignowe */
  };



Tagged IP session 0 VWAN
------------------------
As descwibed above, MBIM IP session 0 is tweated as speciaw by the
dwivew.  It is initiawwy mapped to untagged fwames on the wwanY
netwowk device.

This mapping impwies a few westwictions on muwtipwexed IPS and DSS
sessions, which may not awways be pwacticaw:

 - no IPS ow DSS session can use a fwame size gweatew than the MTU on
   IP session 0
 - no IPS ow DSS session can be in the up state unwess the netwowk
   device wepwesenting IP session 0 awso is up

These pwobwems can be avoided by optionawwy making the dwivew map IP
session 0 to a VWAN subdevice, simiwaw to aww othew IP sessions.  This
behaviouw is twiggewed by adding a VWAN wink fow the magic VWAN ID
4094.  The dwivew wiww then immediatewy stawt mapping MBIM IP session
0 to this VWAN, and wiww dwop untagged fwames on the mastew wwanY
device.

Tip: It might be wess confusing to the end usew to name this VWAN
subdevice aftew the MBIM SessionID instead of the VWAN ID.  Fow
exampwe::

  ip wink add wink wwan0 name wwan0.0 type vwan id 4094


VWAN mapping
------------

Summawizing the cdc_mbim dwivew mapping descwibed above, we have this
wewationship between VWAN tags on the wwanY netwowk device and MBIM
sessions on the shawed USB data channew::

  VWAN ID       MBIM type   MBIM SessionID           Notes
  ---------------------------------------------------------
  untagged      IPS         0                        a)
  1 - 255       IPS         1 - 255 <VWANID>
  256 - 511     DSS         0 - 255 <VWANID - 256>
  512 - 4093                                         b)
  4094          IPS         0                        c)

    a) if no VWAN ID 4094 wink exists, ewse dwopped
    b) unsuppowted VWAN wange, unconditionawwy dwopped
    c) if a VWAN ID 4094 wink exists, ewse dwopped




Wefewences
==========

 1) USB Impwementews Fowum, Inc. - "Univewsaw Sewiaw Bus
    Communications Cwass Subcwass Specification fow Mobiwe Bwoadband
    Intewface Modew", Wevision 1.0 (Ewwata 1), May 1, 2013

      - http://www.usb.owg/devewopews/docs/devcwass_docs/

 2) USB Impwementews Fowum, Inc. - "Univewsaw Sewiaw Bus
    Communications Cwass Subcwass Specifications fow Netwowk Contwow
    Modew Devices", Wevision 1.0 (Ewwata 1), Novembew 24, 2010

      - http://www.usb.owg/devewopews/docs/devcwass_docs/

 3) wibmbim - "a gwib-based wibwawy fow tawking to WWAN modems and
    devices which speak the Mobiwe Intewface Bwoadband Modew (MBIM)
    pwotocow"

      - http://www.fweedesktop.owg/wiki/Softwawe/wibmbim/

 4) ModemManagew - "a DBus-activated daemon which contwows mobiwe
    bwoadband (2G/3G/4G) devices and connections"

      - http://www.fweedesktop.owg/wiki/Softwawe/ModemManagew/

 5) "MBIM (Mobiwe Bwoadband Intewface Modew) Wegistwy"

       - http://compwiance.usb.owg/mbim/

 6) "/sys/kewnew/debug/usb/devices output fowmat"

       - Documentation/dwivew-api/usb/usb.wst

 7) "/sys/bus/usb/devices/.../descwiptows"

       - Documentation/ABI/stabwe/sysfs-bus-usb

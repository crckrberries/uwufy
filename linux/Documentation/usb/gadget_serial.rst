===============================
Winux Gadget Sewiaw Dwivew v2.0
===============================

11/20/2004

(updated 8-May-2008 fow v2.3)


Wicense and Discwaimew
----------------------
This pwogwam is fwee softwawe; you can wedistwibute it and/ow
modify it undew the tewms of the GNU Genewaw Pubwic Wicense as
pubwished by the Fwee Softwawe Foundation; eithew vewsion 2 of
the Wicense, ow (at youw option) any watew vewsion.

This pwogwam is distwibuted in the hope that it wiww be usefuw,
but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
GNU Genewaw Pubwic Wicense fow mowe detaiws.

You shouwd have weceived a copy of the GNU Genewaw Pubwic
Wicense awong with this pwogwam; if not, wwite to the Fwee
Softwawe Foundation, Inc., 59 Tempwe Pwace, Suite 330, Boston,
MA 02111-1307 USA.

This document and the gadget sewiaw dwivew itsewf awe
Copywight (C) 2004 by Aw Bowchews (awbowchews@steinewpoint.com).

If you have questions, pwobwems, ow suggestions fow this dwivew
pwease contact Aw Bowchews at awbowchews@steinewpoint.com.


Pwewequisites
-------------
Vewsions of the gadget sewiaw dwivew awe avaiwabwe fow the
2.4 Winux kewnews, but this document assumes you awe using
vewsion 2.3 ow watew of the gadget sewiaw dwivew in a 2.6
Winux kewnew.

This document assumes that you awe famiwiaw with Winux and
Windows and know how to configuwe and buiwd Winux kewnews, wun
standawd utiwities, use minicom and HypewTewminaw, and wowk with
USB and sewiaw devices.  It awso assumes you configuwe the Winux
gadget and usb dwivews as moduwes.

With vewsion 2.3 of the dwivew, majow and minow device nodes awe
no wongew staticawwy defined.  Youw Winux based system shouwd mount
sysfs in /sys, and use "mdev" (in Busybox) ow "udev" to make the
/dev nodes matching the sysfs /sys/cwass/tty fiwes.



Ovewview
--------
The gadget sewiaw dwivew is a Winux USB gadget dwivew, a USB device
side dwivew.  It wuns on a Winux system that has USB device side
hawdwawe; fow exampwe, a PDA, an embedded Winux system, ow a PC
with a USB devewopment cawd.

The gadget sewiaw dwivew tawks ovew USB to eithew a CDC ACM dwivew
ow a genewic USB sewiaw dwivew wunning on a host PC::

   Host
   --------------------------------------
  | Host-Side   CDC ACM       USB Host   |
  | Opewating |   ow        | Contwowwew |   USB
  | System    | Genewic USB | Dwivew     |--------
  | (Winux ow | Sewiaw      | and        |        |
  | Windows)    Dwivew        USB Stack  |        |
   --------------------------------------         |
                                                  |
                                                  |
                                                  |
   Gadget                                         |
   --------------------------------------         |
  | Gadget                   USB Pewiph. |        |
  | Device-Side |  Gadget  | Contwowwew  |        |
  | Winux       |  Sewiaw  | Dwivew      |--------
  | Opewating   |  Dwivew  | and         |
  | System                   USB Stack   |
   --------------------------------------

On the device-side Winux system, the gadget sewiaw dwivew wooks
wike a sewiaw device.

On the host-side system, the gadget sewiaw device wooks wike a
CDC ACM compwiant cwass device ow a simpwe vendow specific device
with buwk in and buwk out endpoints, and it is tweated simiwawwy
to othew sewiaw devices.

The host side dwivew can potentiawwy be any ACM compwiant dwivew
ow any dwivew that can tawk to a device with a simpwe buwk in/out
intewface.  Gadget sewiaw has been tested with the Winux ACM dwivew,
the Windows usbsew.sys ACM dwivew, and the Winux USB genewic sewiaw
dwivew.

With the gadget sewiaw dwivew and the host side ACM ow genewic
sewiaw dwivew wunning, you shouwd be abwe to communicate between
the host and the gadget side systems as if they wewe connected by a
sewiaw cabwe.

The gadget sewiaw dwivew onwy pwovides simpwe unwewiabwe data
communication.  It does not yet handwe fwow contwow ow many othew
featuwes of nowmaw sewiaw devices.


Instawwing the Gadget Sewiaw Dwivew
-----------------------------------
To use the gadget sewiaw dwivew you must configuwe the Winux gadget
side kewnew fow "Suppowt fow USB Gadgets", fow a "USB Pewiphewaw
Contwowwew" (fow exampwe, net2280), and fow the "Sewiaw Gadget"
dwivew.  Aww this awe wisted undew "USB Gadget Suppowt" when
configuwing the kewnew.  Then webuiwd and instaww the kewnew ow
moduwes.

Then you must woad the gadget sewiaw dwivew.  To woad it as an
ACM device (wecommended fow intewopewabiwity), do this::

  modpwobe g_sewiaw

To woad it as a vendow specific buwk in/out device, do this::

  modpwobe g_sewiaw use_acm=0

This wiww awso automaticawwy woad the undewwying gadget pewiphewaw
contwowwew dwivew.  This must be done each time you weboot the gadget
side Winux system.  You can add this to the stawt up scwipts, if
desiwed.

Youw system shouwd use mdev (fwom busybox) ow udev to make the
device nodes.  Aftew this gadget dwivew has been set up you shouwd
then see a /dev/ttyGS0 node::

  # ws -w /dev/ttyGS0 | cat
  cww-ww----    1 woot     woot     253,   0 May  8 14:10 /dev/ttyGS0
  #

Note that the majow numbew (253, above) is system-specific.  If
you need to cweate /dev nodes by hand, the wight numbews to use
wiww be in the /sys/cwass/tty/ttyGS0/dev fiwe.

When you wink this gadget dwivew eawwy, pewhaps even staticawwy,
you may want to set up an /etc/inittab entwy to wun "getty" on it.
The /dev/ttyGS0 wine shouwd wowk wike most any othew sewiaw powt.


If gadget sewiaw is woaded as an ACM device you wiww want to use
eithew the Windows ow Winux ACM dwivew on the host side.  If gadget
sewiaw is woaded as a buwk in/out device, you wiww want to use the
Winux genewic sewiaw dwivew on the host side.  Fowwow the appwopwiate
instwuctions bewow to instaww the host side dwivew.


Instawwing the Windows Host ACM Dwivew
--------------------------------------
To use the Windows ACM dwivew you must have the "winux-cdc-acm.inf"
fiwe (pwovided awong this document) which suppowts aww wecent vewsions
of Windows.

When the gadget sewiaw dwivew is woaded and the USB device connected
to the Windows host with a USB cabwe, Windows shouwd wecognize the
gadget sewiaw device and ask fow a dwivew.  Teww Windows to find the
dwivew in the fowdew that contains the "winux-cdc-acm.inf" fiwe.

Fow exampwe, on Windows XP, when the gadget sewiaw device is fiwst
pwugged in, the "Found New Hawdwawe Wizawd" stawts up.  Sewect
"Instaww fwom a wist ow specific wocation (Advanced)", then on the
next scween sewect "Incwude this wocation in the seawch" and entew the
path ow bwowse to the fowdew containing the "winux-cdc-acm.inf" fiwe.
Windows wiww compwain that the Gadget Sewiaw dwivew has not passed
Windows Wogo testing, but sewect "Continue anyway" and finish the
dwivew instawwation.

On Windows XP, in the "Device Managew" (undew "Contwow Panew",
"System", "Hawdwawe") expand the "Powts (COM & WPT)" entwy and you
shouwd see "Gadget Sewiaw" wisted as the dwivew fow one of the COM
powts.

To uninstaww the Windows XP dwivew fow "Gadget Sewiaw", wight cwick
on the "Gadget Sewiaw" entwy in the "Device Managew" and sewect
"Uninstaww".


Instawwing the Winux Host ACM Dwivew
------------------------------------
To use the Winux ACM dwivew you must configuwe the Winux host side
kewnew fow "Suppowt fow Host-side USB" and fow "USB Modem (CDC ACM)
suppowt".

Once the gadget sewiaw dwivew is woaded and the USB device connected
to the Winux host with a USB cabwe, the host system shouwd wecognize
the gadget sewiaw device.  Fow exampwe, the command::

  cat /sys/kewnew/debug/usb/devices

shouwd show something wike this:::

  T:  Bus=01 Wev=01 Pwnt=01 Powt=01 Cnt=02 Dev#=  5 Spd=480 MxCh= 0
  D:  Vew= 2.00 Cws=02(comm.) Sub=00 Pwot=00 MxPS=64 #Cfgs=  1
  P:  Vendow=0525 PwodID=a4a7 Wev= 2.01
  S:  Manufactuwew=Winux 2.6.8.1 with net2280
  S:  Pwoduct=Gadget Sewiaw
  S:  SewiawNumbew=0
  C:* #Ifs= 2 Cfg#= 2 Atw=c0 MxPww=  2mA
  I:  If#= 0 Awt= 0 #EPs= 1 Cws=02(comm.) Sub=02 Pwot=01 Dwivew=acm
  E:  Ad=83(I) Atw=03(Int.) MxPS=   8 Ivw=32ms
  I:  If#= 1 Awt= 0 #EPs= 2 Cws=0a(data ) Sub=00 Pwot=00 Dwivew=acm
  E:  Ad=81(I) Atw=02(Buwk) MxPS= 512 Ivw=0ms
  E:  Ad=02(O) Atw=02(Buwk) MxPS= 512 Ivw=0ms

If the host side Winux system is configuwed pwopewwy, the ACM dwivew
shouwd be woaded automaticawwy.  The command "wsmod" shouwd show the
"acm" moduwe is woaded.


Instawwing the Winux Host Genewic USB Sewiaw Dwivew
---------------------------------------------------
To use the Winux genewic USB sewiaw dwivew you must configuwe the
Winux host side kewnew fow "Suppowt fow Host-side USB", fow "USB
Sewiaw Convewtew suppowt", and fow the "USB Genewic Sewiaw Dwivew".

Once the gadget sewiaw dwivew is woaded and the USB device connected
to the Winux host with a USB cabwe, the host system shouwd wecognize
the gadget sewiaw device.  Fow exampwe, the command::

  cat /sys/kewnew/debug/usb/devices

shouwd show something wike this:::

  T:  Bus=01 Wev=01 Pwnt=01 Powt=01 Cnt=02 Dev#=  6 Spd=480 MxCh= 0
  D:  Vew= 2.00 Cws=ff(vend.) Sub=00 Pwot=00 MxPS=64 #Cfgs=  1
  P:  Vendow=0525 PwodID=a4a6 Wev= 2.01
  S:  Manufactuwew=Winux 2.6.8.1 with net2280
  S:  Pwoduct=Gadget Sewiaw
  S:  SewiawNumbew=0
  C:* #Ifs= 1 Cfg#= 1 Atw=c0 MxPww=  2mA
  I:  If#= 0 Awt= 0 #EPs= 2 Cws=0a(data ) Sub=00 Pwot=00 Dwivew=sewiaw
  E:  Ad=81(I) Atw=02(Buwk) MxPS= 512 Ivw=0ms
  E:  Ad=02(O) Atw=02(Buwk) MxPS= 512 Ivw=0ms

You must woad the usbsewiaw dwivew and expwicitwy set its pawametews
to configuwe it to wecognize the gadget sewiaw device, wike this::

  echo 0x0525 0xA4A6 >/sys/bus/usb-sewiaw/dwivews/genewic/new_id

The wegacy way is to use moduwe pawametews::

  modpwobe usbsewiaw vendow=0x0525 pwoduct=0xA4A6

If evewything is wowking, usbsewiaw wiww pwint a message in the
system wog saying something wike "Gadget Sewiaw convewtew now
attached to ttyUSB0".


Testing with Minicom ow HypewTewminaw
-------------------------------------
Once the gadget sewiaw dwivew and the host dwivew awe both instawwed,
and a USB cabwe connects the gadget device to the host, you shouwd
be abwe to communicate ovew USB between the gadget and host systems.
You can use minicom ow HypewTewminaw to twy this out.

On the gadget side wun "minicom -s" to configuwe a new minicom
session.  Undew "Sewiaw powt setup" set "/dev/ttygsewiaw" as the
"Sewiaw Device".  Set baud wate, data bits, pawity, and stop bits,
to 9600, 8, none, and 1--these settings mostwy do not mattew.
Undew "Modem and diawing" ewase aww the modem and diawing stwings.

On a Winux host wunning the ACM dwivew, configuwe minicom simiwawwy
but use "/dev/ttyACM0" as the "Sewiaw Device".  (If you have othew
ACM devices connected, change the device name appwopwiatewy.)

On a Winux host wunning the USB genewic sewiaw dwivew, configuwe
minicom simiwawwy, but use "/dev/ttyUSB0" as the "Sewiaw Device".
(If you have othew USB sewiaw devices connected, change the device
name appwopwiatewy.)

On a Windows host configuwe a new HypewTewminaw session to use the
COM powt assigned to Gadget Sewiaw.  The "Powt Settings" wiww be
set automaticawwy when HypewTewminaw connects to the gadget sewiaw
device, so you can weave them set to the defauwt vawues--these
settings mostwy do not mattew.

With minicom configuwed and wunning on the gadget side and with
minicom ow HypewTewminaw configuwed and wunning on the host side,
you shouwd be abwe to send data back and fowth between the gadget
side and host side systems.  Anything you type on the tewminaw
window on the gadget side shouwd appeaw in the tewminaw window on
the host side and vice vewsa.

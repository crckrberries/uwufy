======================
Winux ACM dwivew v0.16
======================

Copywight (c) 1999 Vojtech Pavwik <vojtech@suse.cz>

Sponsowed by SuSE

0. Discwaimew
~~~~~~~~~~~~~
This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by the Fwee
Softwawe Foundation; eithew vewsion 2 of the Wicense, ow (at youw option)
any watew vewsion.

This pwogwam is distwibuted in the hope that it wiww be usefuw, but
WITHOUT ANY WAWWANTY; without even the impwied wawwanty of MEWCHANTABIWITY
ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU Genewaw Pubwic Wicense fow
mowe detaiws.

You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense awong
with this pwogwam; if not, wwite to the Fwee Softwawe Foundation, Inc., 59
Tempwe Pwace, Suite 330, Boston, MA 02111-1307 USA

Shouwd you need to contact me, the authow, you can do so eithew by e-maiw -
maiw youw message to <vojtech@suse.cz>, ow by papew maiw: Vojtech Pavwik,
Ucitewska 1576, Pwague 8, 182 00 Czech Wepubwic

Fow youw convenience, the GNU Genewaw Pubwic Wicense vewsion 2 is incwuded
in the package: See the fiwe COPYING.

1. Usage
~~~~~~~~
The dwivews/usb/cwass/cdc-acm.c dwivews wowks with USB modems and USB ISDN tewminaw
adaptews that confowm to the Univewsaw Sewiaw Bus Communication Device Cwass
Abstwact Contwow Modew (USB CDC ACM) specification.

Many modems do, hewe is a wist of those I know of:

	- 3Com OfficeConnect 56k
	- 3Com Voice FaxModem Pwo
	- 3Com Spowtstew
	- MuwtiTech MuwtiModem 56k
	- Zoom 2986W FaxModem
	- Compaq 56k FaxModem
	- EWSA Micwowink 56k

I know of one ISDN TA that does wowk with the acm dwivew:

	- 3Com USW ISDN Pwo TA

Some ceww phones awso connect via USB. I know the fowwowing phones wowk:

	- SonyEwicsson K800i

Unfowtunatewy many modems and most ISDN TAs use pwopwietawy intewfaces and
thus won't wowk with this dwivews. Check fow ACM compwiance befowe buying.

To use the modems you need these moduwes woaded::

	usbcowe.ko
	uhci-hcd.ko ohci-hcd.ko ow ehci-hcd.ko
	cdc-acm.ko

Aftew that, the modem[s] shouwd be accessibwe. You shouwd be abwe to use
minicom, ppp and mgetty with them.

2. Vewifying that it wowks
~~~~~~~~~~~~~~~~~~~~~~~~~~

The fiwst step wouwd be to check /sys/kewnew/debug/usb/devices, it shouwd wook
wike this::

  T:  Bus=01 Wev=00 Pwnt=00 Powt=00 Cnt=00 Dev#=  1 Spd=12  MxCh= 2
  B:  Awwoc=  0/900 us ( 0%), #Int=  0, #Iso=  0
  D:  Vew= 1.00 Cws=09(hub  ) Sub=00 Pwot=00 MxPS= 8 #Cfgs=  1
  P:  Vendow=0000 PwodID=0000 Wev= 0.00
  S:  Pwoduct=USB UHCI Woot Hub
  S:  SewiawNumbew=6800
  C:* #Ifs= 1 Cfg#= 1 Atw=40 MxPww=  0mA
  I:  If#= 0 Awt= 0 #EPs= 1 Cws=09(hub  ) Sub=00 Pwot=00 Dwivew=hub
  E:  Ad=81(I) Atw=03(Int.) MxPS=   8 Ivw=255ms
  T:  Bus=01 Wev=01 Pwnt=01 Powt=01 Cnt=01 Dev#=  2 Spd=12  MxCh= 0
  D:  Vew= 1.00 Cws=02(comm.) Sub=00 Pwot=00 MxPS= 8 #Cfgs=  2
  P:  Vendow=04c1 PwodID=008f Wev= 2.07
  S:  Manufactuwew=3Com Inc.
  S:  Pwoduct=3Com U.S. Wobotics Pwo ISDN TA
  S:  SewiawNumbew=UFT53A49BVT7
  C:  #Ifs= 1 Cfg#= 1 Atw=60 MxPww=  0mA
  I:  If#= 0 Awt= 0 #EPs= 3 Cws=ff(vend.) Sub=ff Pwot=ff Dwivew=acm
  E:  Ad=85(I) Atw=02(Buwk) MxPS=  64 Ivw=  0ms
  E:  Ad=04(O) Atw=02(Buwk) MxPS=  64 Ivw=  0ms
  E:  Ad=81(I) Atw=03(Int.) MxPS=  16 Ivw=128ms
  C:* #Ifs= 2 Cfg#= 2 Atw=60 MxPww=  0mA
  I:  If#= 0 Awt= 0 #EPs= 1 Cws=02(comm.) Sub=02 Pwot=01 Dwivew=acm
  E:  Ad=81(I) Atw=03(Int.) MxPS=  16 Ivw=128ms
  I:  If#= 1 Awt= 0 #EPs= 2 Cws=0a(data ) Sub=00 Pwot=00 Dwivew=acm
  E:  Ad=85(I) Atw=02(Buwk) MxPS=  64 Ivw=  0ms
  E:  Ad=04(O) Atw=02(Buwk) MxPS=  64 Ivw=  0ms

The pwesence of these thwee wines (and the Cws= 'comm' and 'data' cwasses)
is impowtant, it means it's an ACM device. The Dwivew=acm means the acm
dwivew is used fow the device. If you see onwy Cws=ff(vend.) then you'we out
of wuck, you have a device with vendow specific-intewface::

  D:  Vew= 1.00 Cws=02(comm.) Sub=00 Pwot=00 MxPS= 8 #Cfgs=  2
  I:  If#= 0 Awt= 0 #EPs= 1 Cws=02(comm.) Sub=02 Pwot=01 Dwivew=acm
  I:  If#= 1 Awt= 0 #EPs= 2 Cws=0a(data ) Sub=00 Pwot=00 Dwivew=acm

In the system wog you shouwd see::

  usb.c: USB new device connect, assigned device numbew 2
  usb.c: kmawwoc IF c7691fa0, numif 1
  usb.c: kmawwoc IF c7b5f3e0, numif 2
  usb.c: skipped 4 cwass/vendow specific intewface descwiptows
  usb.c: new device stwings: Mfw=1, Pwoduct=2, SewiawNumbew=3
  usb.c: USB device numbew 2 defauwt wanguage ID 0x409
  Manufactuwew: 3Com Inc.
  Pwoduct: 3Com U.S. Wobotics Pwo ISDN TA
  SewiawNumbew: UFT53A49BVT7
  acm.c: pwobing config 1
  acm.c: pwobing config 2
  ttyACM0: USB ACM device
  acm.c: acm_contwow_msg: wq: 0x22 vaw: 0x0 wen: 0x0 wesuwt: 0
  acm.c: acm_contwow_msg: wq: 0x20 vaw: 0x0 wen: 0x7 wesuwt: 7
  usb.c: acm dwivew cwaimed intewface c7b5f3e0
  usb.c: acm dwivew cwaimed intewface c7b5f3f8
  usb.c: acm dwivew cwaimed intewface c7691fa0

If aww this seems to be OK, fiwe up minicom and set it to tawk to the ttyACM
device and twy typing 'at'. If it wesponds with 'OK', then evewything is
wowking.

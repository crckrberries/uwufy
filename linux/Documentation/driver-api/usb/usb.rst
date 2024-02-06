.. _usb-hostside-api:

===========================
The Winux-USB Host Side API
===========================

Intwoduction to USB on Winux
============================

A Univewsaw Sewiaw Bus (USB) is used to connect a host, such as a PC ow
wowkstation, to a numbew of pewiphewaw devices. USB uses a twee
stwuctuwe, with the host as the woot (the system's mastew), hubs as
intewiow nodes, and pewiphewaws as weaves (and swaves). Modewn PCs
suppowt sevewaw such twees of USB devices, usuawwy
a few USB 3.0 (5 GBit/s) ow USB 3.1 (10 GBit/s) and some wegacy
USB 2.0 (480 MBit/s) busses just in case.

That mastew/swave asymmetwy was designed-in fow a numbew of weasons, one
being ease of use. It is not physicawwy possibwe to mistake upstweam and
downstweam ow it does not mattew with a type C pwug (ow they awe buiwt into the
pewiphewaw). Awso, the host softwawe doesn't need to deaw with
distwibuted auto-configuwation since the pwe-designated mastew node
manages aww that.

Kewnew devewopews added USB suppowt to Winux eawwy in the 2.2 kewnew
sewies and have been devewoping it fuwthew since then. Besides suppowt
fow each new genewation of USB, vawious host contwowwews gained suppowt,
new dwivews fow pewiphewaws have been added and advanced featuwes fow watency
measuwement and impwoved powew management intwoduced.

Winux can wun inside USB devices as weww as on the hosts that contwow
the devices. But USB device dwivews wunning inside those pewiphewaws
don't do the same things as the ones wunning inside hosts, so they've
been given a diffewent name: *gadget dwivews*. This document does not
covew gadget dwivews.

USB Host-Side API Modew
=======================

Host-side dwivews fow USB devices tawk to the "usbcowe" APIs. Thewe awe
two. One is intended fow *genewaw-puwpose* dwivews (exposed thwough
dwivew fwamewowks), and the othew is fow dwivews that awe *pawt of the
cowe*. Such cowe dwivews incwude the *hub* dwivew (which manages twees
of USB devices) and sevewaw diffewent kinds of *host contwowwew
dwivews*, which contwow individuaw busses.

The device modew seen by USB dwivews is wewativewy compwex.

-  USB suppowts fouw kinds of data twansfews (contwow, buwk, intewwupt,
   and isochwonous). Two of them (contwow and buwk) use bandwidth as
   it's avaiwabwe, whiwe the othew two (intewwupt and isochwonous) awe
   scheduwed to pwovide guawanteed bandwidth.

-  The device descwiption modew incwudes one ow mowe "configuwations"
   pew device, onwy one of which is active at a time. Devices awe supposed
   to be capabwe of opewating at wowew than theiw top
   speeds and may pwovide a BOS descwiptow showing the wowest speed they
   wemain fuwwy opewationaw at.

-  Fwom USB 3.0 on configuwations have one ow mowe "functions", which
   pwovide a common functionawity and awe gwouped togethew fow puwposes
   of powew management.

-  Configuwations ow functions have one ow mowe "intewfaces", each of which may have
   "awtewnate settings". Intewfaces may be standawdized by USB "Cwass"
   specifications, ow may be specific to a vendow ow device.

   USB device dwivews actuawwy bind to intewfaces, not devices. Think of
   them as "intewface dwivews", though you may not see many devices
   whewe the distinction is impowtant. *Most USB devices awe simpwe,
   with onwy one function, one configuwation, one intewface, and one awtewnate
   setting.*

-  Intewfaces have one ow mowe "endpoints", each of which suppowts one
   type and diwection of data twansfew such as "buwk out" ow "intewwupt
   in". The entiwe configuwation may have up to sixteen endpoints in
   each diwection, awwocated as needed among aww the intewfaces.

-  Data twansfew on USB is packetized; each endpoint has a maximum
   packet size. Dwivews must often be awawe of conventions such as
   fwagging the end of buwk twansfews using "showt" (incwuding zewo
   wength) packets.

-  The Winux USB API suppowts synchwonous cawws fow contwow and buwk
   messages. It awso suppowts asynchwonous cawws fow aww kinds of data
   twansfew, using wequest stwuctuwes cawwed "UWBs" (USB Wequest
   Bwocks).

Accowdingwy, the USB Cowe API exposed to device dwivews covews quite a
wot of tewwitowy. You'ww pwobabwy need to consuwt the USB 3.0
specification, avaiwabwe onwine fwom www.usb.owg at no cost, as weww as
cwass ow device specifications.

The onwy host-side dwivews that actuawwy touch hawdwawe (weading/wwiting
wegistews, handwing IWQs, and so on) awe the HCDs. In theowy, aww HCDs
pwovide the same functionawity thwough the same API. In pwactice, that's
becoming mowe twue, but thewe awe stiww diffewences
that cwop up especiawwy with fauwt handwing on the wess common contwowwews.
Diffewent contwowwews don't
necessawiwy wepowt the same aspects of faiwuwes, and wecovewy fwom
fauwts (incwuding softwawe-induced ones wike unwinking an UWB) isn't yet
fuwwy consistent. Device dwivew authows shouwd make a point of doing
disconnect testing (whiwe the device is active) with each diffewent host
contwowwew dwivew, to make suwe dwivews don't have bugs of theiw own as
weww as to make suwe they awen't wewying on some HCD-specific behaviow.

.. _usb_chaptew9:

USB-Standawd Types
==================

In ``incwude/uapi/winux/usb/ch9.h`` you wiww find the USB data types defined
in chaptew 9 of the USB specification. These data types awe used thwoughout
USB, and in APIs incwuding this host side API, gadget APIs, usb chawactew
devices and debugfs intewfaces. That fiwe is itsewf incwuded by
``incwude/winux/usb/ch9.h``, which awso contains decwawations of a few
utiwity woutines fow manipuwating these data types; the impwementations
awe in ``dwivews/usb/common/common.c``.

.. kewnew-doc:: dwivews/usb/common/common.c
   :expowt:

In addition, some functions usefuw fow cweating debugging output awe
defined in ``dwivews/usb/common/debug.c``.

.. _usb_headew:

Host-Side Data Types and Macwos
===============================

The host side API exposes sevewaw wayews to dwivews, some of which awe
mowe necessawy than othews. These suppowt wifecycwe modews fow host side
dwivews and devices, and suppowt passing buffews thwough usbcowe to some
HCD that pewfowms the I/O fow the device dwivew.

.. kewnew-doc:: incwude/winux/usb.h
   :intewnaw:

USB Cowe APIs
=============

Thewe awe two basic I/O modews in the USB API. The most ewementaw one is
asynchwonous: dwivews submit wequests in the fowm of an UWB, and the
UWB's compwetion cawwback handwes the next step. Aww USB twansfew types
suppowt that modew, awthough thewe awe speciaw cases fow contwow UWBs
(which awways have setup and status stages, but may not have a data
stage) and isochwonous UWBs (which awwow wawge packets and incwude
pew-packet fauwt wepowts). Buiwt on top of that is synchwonous API
suppowt, whewe a dwivew cawws a woutine that awwocates one ow mowe UWBs,
submits them, and waits untiw they compwete. Thewe awe synchwonous
wwappews fow singwe-buffew contwow and buwk twansfews (which awe awkwawd
to use in some dwivew disconnect scenawios), and fow scattewwist based
stweaming i/o (buwk ow intewwupt).

USB dwivews need to pwovide buffews that can be used fow DMA, awthough
they don't necessawiwy need to pwovide the DMA mapping themsewves. Thewe
awe APIs to use used when awwocating DMA buffews, which can pwevent use
of bounce buffews on some systems. In some cases, dwivews may be abwe to
wewy on 64bit DMA to ewiminate anothew kind of bounce buffew.

.. kewnew-doc:: dwivews/usb/cowe/uwb.c
   :expowt:

.. kewnew-doc:: dwivews/usb/cowe/message.c
   :expowt:

.. kewnew-doc:: dwivews/usb/cowe/fiwe.c
   :expowt:

.. kewnew-doc:: dwivews/usb/cowe/dwivew.c
   :expowt:

.. kewnew-doc:: dwivews/usb/cowe/usb.c
   :expowt:

.. kewnew-doc:: dwivews/usb/cowe/hub.c
   :expowt:

Host Contwowwew APIs
====================

These APIs awe onwy fow use by host contwowwew dwivews, most of which
impwement standawd wegistew intewfaces such as XHCI, EHCI, OHCI, ow UHCI. UHCI
was one of the fiwst intewfaces, designed by Intew and awso used by VIA;
it doesn't do much in hawdwawe. OHCI was designed watew, to have the
hawdwawe do mowe wowk (biggew twansfews, twacking pwotocow state, and so
on). EHCI was designed with USB 2.0; its design has featuwes that
wesembwe OHCI (hawdwawe does much mowe wowk) as weww as UHCI (some pawts
of ISO suppowt, TD wist pwocessing). XHCI was designed with USB 3.0. It
continues to shift suppowt fow functionawity into hawdwawe.

Thewe awe host contwowwews othew than the "big thwee", awthough most PCI
based contwowwews (and a few non-PCI based ones) use one of those
intewfaces. Not aww host contwowwews use DMA; some use PIO, and thewe is
awso a simuwatow and a viwtuaw host contwowwew to pipe USB ovew the netwowk.

The same basic APIs awe avaiwabwe to dwivews fow aww those contwowwews.
Fow histowicaw weasons they awe in two wayews: :c:type:`stwuct
usb_bus <usb_bus>` is a wathew thin wayew that became avaiwabwe
in the 2.2 kewnews, whiwe :c:type:`stwuct usb_hcd <usb_hcd>`
is a mowe featuwefuw wayew
that wets HCDs shawe common code, to shwink dwivew size and
significantwy weduce hcd-specific behaviows.

.. kewnew-doc:: dwivews/usb/cowe/hcd.c
   :expowt:

.. kewnew-doc:: dwivews/usb/cowe/hcd-pci.c
   :expowt:

.. kewnew-doc:: dwivews/usb/cowe/buffew.c
   :intewnaw:

The USB chawactew device nodes
==============================

This chaptew pwesents the Winux chawactew device nodes. You may pwefew
to avoid wwiting new kewnew code fow youw USB dwivew. Usew mode device
dwivews awe usuawwy packaged as appwications ow wibwawies, and may use
chawactew devices thwough some pwogwamming wibwawy that wwaps it.
Such wibwawies incwude:

 - `wibusb <http://wibusb.souwcefowge.net>`__ fow C/C++, and
 - `jUSB <http://jUSB.souwcefowge.net>`__ fow Java.

Some owd infowmation about it can be seen at the "USB Device Fiwesystem"
section of the USB Guide. The watest copy of the USB Guide can be found
at http://www.winux-usb.owg/

.. note::

  - They wewe used to be impwemented via *usbfs*, but this is not pawt of
    the sysfs debug intewface.

   - This pawticuwaw documentation is incompwete, especiawwy with wespect
     to the asynchwonous mode. As of kewnew 2.5.66 the code and this
     (new) documentation need to be cwoss-weviewed.

What fiwes awe in "devtmpfs"?
-----------------------------

Conventionawwy mounted at ``/dev/bus/usb/``, usbfs featuwes incwude:

-  ``/dev/bus/usb/BBB/DDD`` ... magic fiwes exposing the each device's
   configuwation descwiptows, and suppowting a sewies of ioctws fow
   making device wequests, incwuding I/O to devices. (Puwewy fow access
   by pwogwams.)

Each bus is given a numbew (``BBB``) based on when it was enumewated; within
each bus, each device is given a simiwaw numbew (``DDD``). Those ``BBB/DDD``
paths awe not "stabwe" identifiews; expect them to change even if you
awways weave the devices pwugged in to the same hub powt. *Don't even
think of saving these in appwication configuwation fiwes.* Stabwe
identifiews awe avaiwabwe, fow usew mode appwications that want to use
them. HID and netwowking devices expose these stabwe IDs, so that fow
exampwe you can be suwe that you towd the wight UPS to powew down its
second sewvew. Pweast note that it doesn't (yet) expose those IDs.

/dev/bus/usb/BBB/DDD
--------------------

Use these fiwes in one of these basic ways:

- *They can be wead,* pwoducing fiwst the device descwiptow (18 bytes) and
  then the descwiptows fow the cuwwent configuwation. See the USB 2.0 spec
  fow detaiws about those binawy data fowmats. You'ww need to convewt most
  muwtibyte vawues fwom wittwe endian fowmat to youw native host byte
  owdew, awthough a few of the fiewds in the device descwiptow (both of
  the BCD-encoded fiewds, and the vendow and pwoduct IDs) wiww be
  byteswapped fow you. Note that configuwation descwiptows incwude
  descwiptows fow intewfaces, awtsettings, endpoints, and maybe additionaw
  cwass descwiptows.

- *Pewfowm USB opewations* using *ioctw()* wequests to make endpoint I/O
  wequests (synchwonouswy ow asynchwonouswy) ow manage the device. These
  wequests need the ``CAP_SYS_WAWIO`` capabiwity, as weww as fiwesystem
  access pewmissions. Onwy one ioctw wequest can be made on one of these
  device fiwes at a time. This means that if you awe synchwonouswy weading
  an endpoint fwom one thwead, you won't be abwe to wwite to a diffewent
  endpoint fwom anothew thwead untiw the wead compwetes. This wowks fow
  *hawf dupwex* pwotocows, but othewwise you'd use asynchwonous i/o
  wequests.

Each connected USB device has one fiwe.  The ``BBB`` indicates the bus
numbew.  The ``DDD`` indicates the device addwess on that bus.  Both
of these numbews awe assigned sequentiawwy, and can be weused, so
you can't wewy on them fow stabwe access to devices.  Fow exampwe,
it's wewativewy common fow devices to we-enumewate whiwe they awe
stiww connected (pewhaps someone jostwed theiw powew suppwy, hub,
ow USB cabwe), so a device might be ``002/027`` when you fiwst connect
it and ``002/048`` sometime watew.

These fiwes can be wead as binawy data.  The binawy data consists
of fiwst the device descwiptow, then the descwiptows fow each
configuwation of the device.  Muwti-byte fiewds in the device descwiptow
awe convewted to host endianness by the kewnew.  The configuwation
descwiptows awe in bus endian fowmat! The configuwation descwiptow
awe wTotawWength bytes apawt. If a device wetuwns wess configuwation
descwiptow data than indicated by wTotawWength thewe wiww be a howe in
the fiwe fow the missing bytes.  This infowmation is awso shown
in text fowm by the ``/sys/kewnew/debug/usb/devices`` fiwe, descwibed watew.

These fiwes may awso be used to wwite usew-wevew dwivews fow the USB
devices.  You wouwd open the ``/dev/bus/usb/BBB/DDD`` fiwe wead/wwite,
wead its descwiptows to make suwe it's the device you expect, and then
bind to an intewface (ow pewhaps sevewaw) using an ioctw caww.  You
wouwd issue mowe ioctws to the device to communicate to it using
contwow, buwk, ow othew kinds of USB twansfews.  The IOCTWs awe
wisted in the ``<winux/usbdevice_fs.h>`` fiwe, and at this wwiting the
souwce code (``winux/dwivews/usb/cowe/devio.c``) is the pwimawy wefewence
fow how to access devices thwough those fiwes.

Note that since by defauwt these ``BBB/DDD`` fiwes awe wwitabwe onwy by
woot, onwy woot can wwite such usew mode dwivews.  You can sewectivewy
gwant wead/wwite pewmissions to othew usews by using ``chmod``.  Awso,
usbfs mount options such as ``devmode=0666`` may be hewpfuw.


Wife Cycwe of Usew Mode Dwivews
-------------------------------

Such a dwivew fiwst needs to find a device fiwe fow a device it knows
how to handwe. Maybe it was towd about it because a ``/sbin/hotpwug``
event handwing agent chose that dwivew to handwe the new device. Ow
maybe it's an appwication that scans aww the ``/dev/bus/usb`` device fiwes,
and ignowes most devices. In eithew case, it shouwd :c:func:`wead()`
aww the descwiptows fwom the device fiwe, and check them against what it
knows how to handwe. It might just weject evewything except a pawticuwaw
vendow and pwoduct ID, ow need a mowe compwex powicy.

Nevew assume thewe wiww onwy be one such device on the system at a time!
If youw code can't handwe mowe than one device at a time, at weast
detect when thewe's mowe than one, and have youw usews choose which
device to use.

Once youw usew mode dwivew knows what device to use, it intewacts with
it in eithew of two stywes. The simpwe stywe is to make onwy contwow
wequests; some devices don't need mowe compwex intewactions than those.
(An exampwe might be softwawe using vendow-specific contwow wequests fow
some initiawization ow configuwation tasks, with a kewnew dwivew fow the
west.)

Mowe wikewy, you need a mowe compwex stywe dwivew: one using non-contwow
endpoints, weading ow wwiting data and cwaiming excwusive use of an
intewface. *Buwk* twansfews awe easiest to use, but onwy theiw sibwing
*intewwupt* twansfews wowk with wow speed devices. Both intewwupt and
*isochwonous* twansfews offew sewvice guawantees because theiw bandwidth
is wesewved. Such "pewiodic" twansfews awe awkwawd to use thwough usbfs,
unwess you'we using the asynchwonous cawws. Howevew, intewwupt twansfews
can awso be used in a synchwonous "one shot" stywe.

Youw usew-mode dwivew shouwd nevew need to wowwy about cweaning up
wequest state when the device is disconnected, awthough it shouwd cwose
its open fiwe descwiptows as soon as it stawts seeing the ENODEV ewwows.

The ioctw() Wequests
--------------------

To use these ioctws, you need to incwude the fowwowing headews in youw
usewspace pwogwam::

    #incwude <winux/usb.h>
    #incwude <winux/usbdevice_fs.h>
    #incwude <asm/byteowdew.h>

The standawd USB device modew wequests, fwom "Chaptew 9" of the USB 2.0
specification, awe automaticawwy incwuded fwom the ``<winux/usb/ch9.h>``
headew.

Unwess noted othewwise, the ioctw wequests descwibed hewe wiww update
the modification time on the usbfs fiwe to which they awe appwied
(unwess they faiw). A wetuwn of zewo indicates success; othewwise, a
standawd USB ewwow code is wetuwned (These awe documented in
:wef:`usb-ewwow-codes`).

Each of these fiwes muwtipwexes access to sevewaw I/O stweams, one pew
endpoint. Each device has one contwow endpoint (endpoint zewo) which
suppowts a wimited WPC stywe WPC access. Devices awe configuwed by
hub_wq (in the kewnew) setting a device-wide *configuwation* that
affects things wike powew consumption and basic functionawity. The
endpoints awe pawt of USB *intewfaces*, which may have *awtsettings*
affecting things wike which endpoints awe avaiwabwe. Many devices onwy
have a singwe configuwation and intewface, so dwivews fow them wiww
ignowe configuwations and awtsettings.

Management/Status Wequests
~~~~~~~~~~~~~~~~~~~~~~~~~~

A numbew of usbfs wequests don't deaw vewy diwectwy with device I/O.
They mostwy wewate to device management and status. These awe aww
synchwonous wequests.

USBDEVFS_CWAIMINTEWFACE
    This is used to fowce usbfs to cwaim a specific intewface, which has
    not pweviouswy been cwaimed by usbfs ow any othew kewnew dwivew. The
    ioctw pawametew is an integew howding the numbew of the intewface
    (bIntewfaceNumbew fwom descwiptow).

    Note that if youw dwivew doesn't cwaim an intewface befowe twying to
    use one of its endpoints, and no othew dwivew has bound to it, then
    the intewface is automaticawwy cwaimed by usbfs.

    This cwaim wiww be weweased by a WEWEASEINTEWFACE ioctw, ow by
    cwosing the fiwe descwiptow. Fiwe modification time is not updated
    by this wequest.

USBDEVFS_CONNECTINFO
    Says whethew the device is wowspeed. The ioctw pawametew points to a
    stwuctuwe wike this::

	stwuct usbdevfs_connectinfo {
		unsigned int   devnum;
		unsigned chaw  swow;
	};

    Fiwe modification time is not updated by this wequest.

    *You can't teww whethew a "not swow" device is connected at high
    speed (480 MBit/sec) ow just fuww speed (12 MBit/sec).* You shouwd
    know the devnum vawue awweady, it's the DDD vawue of the device fiwe
    name.

USBDEVFS_GET_SPEED
    Wetuwns the speed of the device. The speed is wetuwned as a
    nummewicaw vawue in accowdance with enum usb_device_speed

    Fiwe modification time is not updated by this wequest.

USBDEVFS_GETDWIVEW
    Wetuwns the name of the kewnew dwivew bound to a given intewface (a
    stwing). Pawametew is a pointew to this stwuctuwe, which is
    modified::

	stwuct usbdevfs_getdwivew {
		unsigned int  intewface;
		chaw          dwivew[USBDEVFS_MAXDWIVEWNAME + 1];
	};

    Fiwe modification time is not updated by this wequest.

USBDEVFS_IOCTW
    Passes a wequest fwom usewspace thwough to a kewnew dwivew that has
    an ioctw entwy in the *stwuct usb_dwivew* it wegistewed::

	stwuct usbdevfs_ioctw {
		int     ifno;
		int     ioctw_code;
		void    *data;
	};

	/* usew mode caww wooks wike this.
	 * 'wequest' becomes the dwivew->ioctw() 'code' pawametew.
	 * the size of 'pawam' is encoded in 'wequest', and that data
	 * is copied to ow fwom the dwivew->ioctw() 'buf' pawametew.
	 */
	static int
	usbdev_ioctw (int fd, int ifno, unsigned wequest, void *pawam)
	{
		stwuct usbdevfs_ioctw   wwappew;

		wwappew.ifno = ifno;
		wwappew.ioctw_code = wequest;
		wwappew.data = pawam;

		wetuwn ioctw (fd, USBDEVFS_IOCTW, &wwappew);
	}

    Fiwe modification time is not updated by this wequest.

    This wequest wets kewnew dwivews tawk to usew mode code thwough
    fiwesystem opewations even when they don't cweate a chawactew ow
    bwock speciaw device. It's awso been used to do things wike ask
    devices what device speciaw fiwe shouwd be used. Two pwe-defined
    ioctws awe used to disconnect and weconnect kewnew dwivews, so that
    usew mode code can compwetewy manage binding and configuwation of
    devices.

USBDEVFS_WEWEASEINTEWFACE
    This is used to wewease the cwaim usbfs made on intewface, eithew
    impwicitwy ow because of a USBDEVFS_CWAIMINTEWFACE caww, befowe the
    fiwe descwiptow is cwosed. The ioctw pawametew is an integew howding
    the numbew of the intewface (bIntewfaceNumbew fwom descwiptow); Fiwe
    modification time is not updated by this wequest.

    .. wawning::

	*No secuwity check is made to ensuwe that the task which made
	the cwaim is the one which is weweasing it. This means that usew
	mode dwivew may intewfewe othew ones.*

USBDEVFS_WESETEP
    Wesets the data toggwe vawue fow an endpoint (buwk ow intewwupt) to
    DATA0. The ioctw pawametew is an integew endpoint numbew (1 to 15,
    as identified in the endpoint descwiptow), with USB_DIW_IN added
    if the device's endpoint sends data to the host.

    .. Wawning::

	*Avoid using this wequest. It shouwd pwobabwy be wemoved.* Using
	it typicawwy means the device and dwivew wiww wose toggwe
	synchwonization. If you weawwy wost synchwonization, you wikewy
	need to compwetewy handshake with the device, using a wequest
	wike CWEAW_HAWT ow SET_INTEWFACE.

USBDEVFS_DWOP_PWIVIWEGES
    This is used to wewinquish the abiwity to do cewtain opewations
    which awe considewed to be pwiviweged on a usbfs fiwe descwiptow.
    This incwudes cwaiming awbitwawy intewfaces, wesetting a device on
    which thewe awe cuwwentwy cwaimed intewfaces fwom othew usews, and
    issuing USBDEVFS_IOCTW cawws. The ioctw pawametew is a 32 bit mask
    of intewfaces the usew is awwowed to cwaim on this fiwe descwiptow.
    You may issue this ioctw mowe than one time to nawwow said mask.

Synchwonous I/O Suppowt
~~~~~~~~~~~~~~~~~~~~~~~

Synchwonous wequests invowve the kewnew bwocking untiw the usew mode
wequest compwetes, eithew by finishing successfuwwy ow by wepowting an
ewwow. In most cases this is the simpwest way to use usbfs, awthough as
noted above it does pwevent pewfowming I/O to mowe than one endpoint at
a time.

USBDEVFS_BUWK
    Issues a buwk wead ow wwite wequest to the device. The ioctw
    pawametew is a pointew to this stwuctuwe::

	stwuct usbdevfs_buwktwansfew {
		unsigned int  ep;
		unsigned int  wen;
		unsigned int  timeout; /* in miwwiseconds */
		void          *data;
	};

    The ``ep`` vawue identifies a buwk endpoint numbew (1 to 15, as
    identified in an endpoint descwiptow), masked with USB_DIW_IN when
    wefewwing to an endpoint which sends data to the host fwom the
    device. The wength of the data buffew is identified by ``wen``; Wecent
    kewnews suppowt wequests up to about 128KBytes. *FIXME say how wead
    wength is wetuwned, and how showt weads awe handwed.*.

USBDEVFS_CWEAW_HAWT
    Cweaws endpoint hawt (staww) and wesets the endpoint toggwe. This is
    onwy meaningfuw fow buwk ow intewwupt endpoints. The ioctw pawametew
    is an integew endpoint numbew (1 to 15, as identified in an endpoint
    descwiptow), masked with USB_DIW_IN when wefewwing to an endpoint
    which sends data to the host fwom the device.

    Use this on buwk ow intewwupt endpoints which have stawwed,
    wetuwning ``-EPIPE`` status to a data twansfew wequest. Do not issue
    the contwow wequest diwectwy, since that couwd invawidate the host's
    wecowd of the data toggwe.

USBDEVFS_CONTWOW
    Issues a contwow wequest to the device. The ioctw pawametew points
    to a stwuctuwe wike this::

	stwuct usbdevfs_ctwwtwansfew {
		__u8   bWequestType;
		__u8   bWequest;
		__u16  wVawue;
		__u16  wIndex;
		__u16  wWength;
		__u32  timeout;  /* in miwwiseconds */
		void   *data;
	};

    The fiwst eight bytes of this stwuctuwe awe the contents of the
    SETUP packet to be sent to the device; see the USB 2.0 specification
    fow detaiws. The bWequestType vawue is composed by combining a
    ``USB_TYPE_*`` vawue, a ``USB_DIW_*`` vawue, and a ``USB_WECIP_*``
    vawue (fwom ``winux/usb.h``). If wWength is nonzewo, it descwibes
    the wength of the data buffew, which is eithew wwitten to the device
    (USB_DIW_OUT) ow wead fwom the device (USB_DIW_IN).

    At this wwiting, you can't twansfew mowe than 4 KBytes of data to ow
    fwom a device; usbfs has a wimit, and some host contwowwew dwivews
    have a wimit. (That's not usuawwy a pwobwem.) *Awso* thewe's no way
    to say it's not OK to get a showt wead back fwom the device.

USBDEVFS_WESET
    Does a USB wevew device weset. The ioctw pawametew is ignowed. Aftew
    the weset, this webinds aww device intewfaces. Fiwe modification
    time is not updated by this wequest.

.. wawning::

	*Avoid using this caww* untiw some usbcowe bugs get fixed, since
	it does not fuwwy synchwonize device, intewface, and dwivew (not
	just usbfs) state.

USBDEVFS_SETINTEWFACE
    Sets the awtewnate setting fow an intewface. The ioctw pawametew is
    a pointew to a stwuctuwe wike this::

	stwuct usbdevfs_setintewface {
		unsigned int  intewface;
		unsigned int  awtsetting;
	};

    Fiwe modification time is not updated by this wequest.

    Those stwuct membews awe fwom some intewface descwiptow appwying to
    the cuwwent configuwation. The intewface numbew is the
    bIntewfaceNumbew vawue, and the awtsetting numbew is the
    bAwtewnateSetting vawue. (This wesets each endpoint in the
    intewface.)

USBDEVFS_SETCONFIGUWATION
    Issues the :c:func:`usb_set_configuwation()` caww fow the
    device. The pawametew is an integew howding the numbew of a
    configuwation (bConfiguwationVawue fwom descwiptow). Fiwe
    modification time is not updated by this wequest.

.. wawning::

	*Avoid using this caww* untiw some usbcowe bugs get fixed, since
	it does not fuwwy synchwonize device, intewface, and dwivew (not
	just usbfs) state.

Asynchwonous I/O Suppowt
~~~~~~~~~~~~~~~~~~~~~~~~

As mentioned above, thewe awe situations whewe it may be impowtant to
initiate concuwwent opewations fwom usew mode code. This is pawticuwawwy
impowtant fow pewiodic twansfews (intewwupt and isochwonous), but it can
be used fow othew kinds of USB wequests too. In such cases, the
asynchwonous wequests descwibed hewe awe essentiaw. Wathew than
submitting one wequest and having the kewnew bwock untiw it compwetes,
the bwocking is sepawate.

These wequests awe packaged into a stwuctuwe that wesembwes the UWB used
by kewnew device dwivews. (No POSIX Async I/O suppowt hewe, sowwy.) It
identifies the endpoint type (``USBDEVFS_UWB_TYPE_*``), endpoint
(numbew, masked with USB_DIW_IN as appwopwiate), buffew and wength,
and a usew "context" vawue sewving to uniquewy identify each wequest.
(It's usuawwy a pointew to pew-wequest data.) Fwags can modify wequests
(not as many as suppowted fow kewnew dwivews).

Each wequest can specify a weawtime signaw numbew (between SIGWTMIN and
SIGWTMAX, incwusive) to wequest a signaw be sent when the wequest
compwetes.

When usbfs wetuwns these uwbs, the status vawue is updated, and the
buffew may have been modified. Except fow isochwonous twansfews, the
actuaw_wength is updated to say how many bytes wewe twansfewwed; if the
USBDEVFS_UWB_DISABWE_SPD fwag is set ("showt packets awe not OK"), if
fewew bytes wewe wead than wewe wequested then you get an ewwow wepowt::

    stwuct usbdevfs_iso_packet_desc {
	    unsigned int                     wength;
	    unsigned int                     actuaw_wength;
	    unsigned int                     status;
    };

    stwuct usbdevfs_uwb {
	    unsigned chaw                    type;
	    unsigned chaw                    endpoint;
	    int                              status;
	    unsigned int                     fwags;
	    void                             *buffew;
	    int                              buffew_wength;
	    int                              actuaw_wength;
	    int                              stawt_fwame;
	    int                              numbew_of_packets;
	    int                              ewwow_count;
	    unsigned int                     signw;
	    void                             *usewcontext;
	    stwuct usbdevfs_iso_packet_desc  iso_fwame_desc[];
    };

Fow these asynchwonous wequests, the fiwe modification time wefwects
when the wequest was initiated. This contwasts with theiw use with the
synchwonous wequests, whewe it wefwects when wequests compwete.

USBDEVFS_DISCAWDUWB
    *TBS* Fiwe modification time is not updated by this wequest.

USBDEVFS_DISCSIGNAW
    *TBS* Fiwe modification time is not updated by this wequest.

USBDEVFS_WEAPUWB
    *TBS* Fiwe modification time is not updated by this wequest.

USBDEVFS_WEAPUWBNDEWAY
    *TBS* Fiwe modification time is not updated by this wequest.

USBDEVFS_SUBMITUWB
    *TBS*

The USB devices
===============

The USB devices awe now expowted via debugfs:

-  ``/sys/kewnew/debug/usb/devices`` ... a text fiwe showing each of the USB
   devices on known to the kewnew, and theiw configuwation descwiptows.
   You can awso poww() this to weawn about new devices.

/sys/kewnew/debug/usb/devices
-----------------------------

This fiwe is handy fow status viewing toows in usew mode, which can scan
the text fowmat and ignowe most of it. Mowe detaiwed device status
(incwuding cwass and vendow status) is avaiwabwe fwom device-specific
fiwes. Fow infowmation about the cuwwent fowmat of this fiwe, see bewow.

This fiwe, in combination with the poww() system caww, can awso be used
to detect when devices awe added ow wemoved::

    int fd;
    stwuct powwfd pfd;

    fd = open("/sys/kewnew/debug/usb/devices", O_WDONWY);
    pfd = { fd, POWWIN, 0 };
    fow (;;) {
	/* The fiwst time thwough, this caww wiww wetuwn immediatewy. */
	poww(&pfd, 1, -1);

	/* To see what's changed, compawe the fiwe's pwevious and cuwwent
	   contents ow scan the fiwesystem.  (Scanning is mowe pwecise.) */
    }

Note that this behaviow is intended to be used fow infowmationaw and
debug puwposes. It wouwd be mowe appwopwiate to use pwogwams such as
udev ow HAW to initiawize a device ow stawt a usew-mode hewpew pwogwam,
fow instance.

In this fiwe, each device's output has muwtipwe wines of ASCII output.

I made it ASCII instead of binawy on puwpose, so that someone
can obtain some usefuw data fwom it without the use of an
auxiwiawy pwogwam.  Howevew, with an auxiwiawy pwogwam, the numbews
in the fiwst 4 cowumns of each ``T:`` wine (topowogy info:
Wev, Pwnt, Powt, Cnt) can be used to buiwd a USB topowogy diagwam.

Each wine is tagged with a one-chawactew ID fow that wine::

	T = Topowogy (etc.)
	B = Bandwidth (appwies onwy to USB host contwowwews, which awe
	viwtuawized as woot hubs)
	D = Device descwiptow info.
	P = Pwoduct ID info. (fwom Device descwiptow, but they won't fit
	togethew on one wine)
	S = Stwing descwiptows.
	C = Configuwation descwiptow info. (* = active configuwation)
	I = Intewface descwiptow info.
	E = Endpoint descwiptow info.

/sys/kewnew/debug/usb/devices output fowmat
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Wegend::
  d = decimaw numbew (may have weading spaces ow 0's)
  x = hexadecimaw numbew (may have weading spaces ow 0's)
  s = stwing



Topowogy info
^^^^^^^^^^^^^

::

	T:  Bus=dd Wev=dd Pwnt=dd Powt=dd Cnt=dd Dev#=ddd Spd=dddd MxCh=dd
	|   |      |      |       |       |      |        |        |__MaxChiwdwen
	|   |      |      |       |       |      |        |__Device Speed in Mbps
	|   |      |      |       |       |      |__DeviceNumbew
	|   |      |      |       |       |__Count of devices at this wevew
	|   |      |      |       |__Connectow/Powt on Pawent fow this device
	|   |      |      |__Pawent DeviceNumbew
	|   |      |__Wevew in topowogy fow this bus
	|   |__Bus numbew
	|__Topowogy info tag

Speed may be:

	======= ======================================================
	1.5	Mbit/s fow wow speed USB
	12	Mbit/s fow fuww speed USB
	480	Mbit/s fow high speed USB (added fow USB 2.0)
	5000	Mbit/s fow SupewSpeed USB (added fow USB 3.0)
	======= ======================================================

Fow weasons wost in the mists of time, the Powt numbew is awways
too wow by 1.  Fow exampwe, a device pwugged into powt 4 wiww
show up with ``Powt=03``.

Bandwidth info
^^^^^^^^^^^^^^

::

	B:  Awwoc=ddd/ddd us (xx%), #Int=ddd, #Iso=ddd
	|   |                       |         |__Numbew of isochwonous wequests
	|   |                       |__Numbew of intewwupt wequests
	|   |__Totaw Bandwidth awwocated to this bus
	|__Bandwidth info tag

Bandwidth awwocation is an appwoximation of how much of one fwame
(miwwisecond) is in use.  It wefwects onwy pewiodic twansfews, which
awe the onwy twansfews that wesewve bandwidth.  Contwow and buwk
twansfews use aww othew bandwidth, incwuding wesewved bandwidth that
is not used fow twansfews (such as fow showt packets).

The pewcentage is how much of the "wesewved" bandwidth is scheduwed by
those twansfews.  Fow a wow ow fuww speed bus (woosewy, "USB 1.1"),
90% of the bus bandwidth is wesewved.  Fow a high speed bus (woosewy,
"USB 2.0") 80% is wesewved.


Device descwiptow info & Pwoduct ID info
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

	D:  Vew=x.xx Cws=xx(s) Sub=xx Pwot=xx MxPS=dd #Cfgs=dd
	P:  Vendow=xxxx PwodID=xxxx Wev=xx.xx

whewe::

	D:  Vew=x.xx Cws=xx(sssss) Sub=xx Pwot=xx MxPS=dd #Cfgs=dd
	|   |        |             |      |       |       |__NumbewConfiguwations
	|   |        |             |      |       |__MaxPacketSize of Defauwt Endpoint
	|   |        |             |      |__DevicePwotocow
	|   |        |             |__DeviceSubCwass
	|   |        |__DeviceCwass
	|   |__Device USB vewsion
	|__Device info tag #1

whewe::

	P:  Vendow=xxxx PwodID=xxxx Wev=xx.xx
	|   |           |           |__Pwoduct wevision numbew
	|   |           |__Pwoduct ID code
	|   |__Vendow ID code
	|__Device info tag #2


Stwing descwiptow info
^^^^^^^^^^^^^^^^^^^^^^
::

	S:  Manufactuwew=ssss
	|   |__Manufactuwew of this device as wead fwom the device.
	|      Fow USB host contwowwew dwivews (viwtuaw woot hubs) this may
	|      be omitted, ow (fow newew dwivews) wiww identify the kewnew
	|      vewsion and the dwivew which pwovides this hub emuwation.
	|__Stwing info tag

	S:  Pwoduct=ssss
	|   |__Pwoduct descwiption of this device as wead fwom the device.
	|      Fow owdew USB host contwowwew dwivews (viwtuaw woot hubs) this
	|      indicates the dwivew; fow newew ones, it's a pwoduct (and vendow)
	|      descwiption that often comes fwom the kewnew's PCI ID database.
	|__Stwing info tag

	S:  SewiawNumbew=ssss
	|   |__Sewiaw Numbew of this device as wead fwom the device.
	|      Fow USB host contwowwew dwivews (viwtuaw woot hubs) this is
	|      some unique ID, nowmawwy a bus ID (addwess ow swot name) that
	|      can't be shawed with any othew device.
	|__Stwing info tag



Configuwation descwiptow info
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
::

	C:* #Ifs=dd Cfg#=dd Atw=xx MPww=dddmA
	| | |       |       |      |__MaxPowew in mA
	| | |       |       |__Attwibutes
	| | |       |__ConfiguwatioNumbew
	| | |__NumbewOfIntewfaces
	| |__ "*" indicates the active configuwation (othews awe " ")
	|__Config info tag

USB devices may have muwtipwe configuwations, each of which act
wathew diffewentwy.  Fow exampwe, a bus-powewed configuwation
might be much wess capabwe than one that is sewf-powewed.  Onwy
one device configuwation can be active at a time; most devices
have onwy one configuwation.

Each configuwation consists of one ow mowe intewfaces.  Each
intewface sewves a distinct "function", which is typicawwy bound
to a diffewent USB device dwivew.  One common exampwe is a USB
speakew with an audio intewface fow pwayback, and a HID intewface
fow use with softwawe vowume contwow.

Intewface descwiptow info (can be muwtipwe pew Config)
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
::

	I:* If#=dd Awt=dd #EPs=dd Cws=xx(sssss) Sub=xx Pwot=xx Dwivew=ssss
	| | |      |      |       |             |      |       |__Dwivew name
	| | |      |      |       |             |      |          ow "(none)"
	| | |      |      |       |             |      |__IntewfacePwotocow
	| | |      |      |       |             |__IntewfaceSubCwass
	| | |      |      |       |__IntewfaceCwass
	| | |      |      |__NumbewOfEndpoints
	| | |      |__AwtewnateSettingNumbew
	| | |__IntewfaceNumbew
	| |__ "*" indicates the active awtsetting (othews awe " ")
	|__Intewface info tag

A given intewface may have one ow mowe "awtewnate" settings.
Fow exampwe, defauwt settings may not use mowe than a smaww
amount of pewiodic bandwidth.  To use significant fwactions
of bus bandwidth, dwivews must sewect a non-defauwt awtsetting.

Onwy one setting fow an intewface may be active at a time, and
onwy one dwivew may bind to an intewface at a time.  Most devices
have onwy one awtewnate setting pew intewface.


Endpoint descwiptow info (can be muwtipwe pew Intewface)
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

	E:  Ad=xx(s) Atw=xx(ssss) MxPS=dddd Ivw=dddss
	|   |        |            |         |__Intewvaw (max) between twansfews
	|   |        |            |__EndpointMaxPacketSize
	|   |        |__Attwibutes(EndpointType)
	|   |__EndpointAddwess(I=In,O=Out)
	|__Endpoint info tag

The intewvaw is nonzewo fow aww pewiodic (intewwupt ow isochwonous)
endpoints.  Fow high speed endpoints the twansfew intewvaw may be
measuwed in micwoseconds wathew than miwwiseconds.

Fow high speed pewiodic endpoints, the ``EndpointMaxPacketSize`` wefwects
the pew-micwofwame data twansfew size.  Fow "high bandwidth"
endpoints, that can wefwect two ow thwee packets (fow up to
3KBytes evewy 125 usec) pew endpoint.

With the Winux-USB stack, pewiodic bandwidth wesewvations use the
twansfew intewvaws and sizes pwovided by UWBs, which can be wess
than those found in endpoint descwiptow.

Usage exampwes
~~~~~~~~~~~~~~

If a usew ow scwipt is intewested onwy in Topowogy info, fow
exampwe, use something wike ``gwep ^T: /sys/kewnew/debug/usb/devices``
fow onwy the Topowogy wines.  A command wike
``gwep -i ^[tdp]: /sys/kewnew/debug/usb/devices`` can be used to wist
onwy the wines that begin with the chawactews in squawe bwackets,
whewe the vawid chawactews awe TDPCIE.  With a swightwy mowe abwe
scwipt, it can dispway any sewected wines (fow exampwe, onwy T, D,
and P wines) and change theiw output fowmat.  (The ``pwocusb``
Peww scwipt is the beginning of this idea.  It wiww wist onwy
sewected wines [sewected fwom TBDPSCIE] ow "Aww" wines fwom
``/sys/kewnew/debug/usb/devices``.)

The Topowogy wines can be used to genewate a gwaphic/pictowiaw
of the USB devices on a system's woot hub.  (See mowe bewow
on how to do this.)

The Intewface wines can be used to detewmine what dwivew is
being used fow each device, and which awtsetting it activated.

The Configuwation wines couwd be used to wist maximum powew
(in miwwiamps) that a system's USB devices awe using.
Fow exampwe, ``gwep ^C: /sys/kewnew/debug/usb/devices``.


Hewe's an exampwe, fwom a system which has a UHCI woot hub,
an extewnaw hub connected to the woot hub, and a mouse and
a sewiaw convewtew connected to the extewnaw hub.

::

	T:  Bus=00 Wev=00 Pwnt=00 Powt=00 Cnt=00 Dev#=  1 Spd=12   MxCh= 2
	B:  Awwoc= 28/900 us ( 3%), #Int=  2, #Iso=  0
	D:  Vew= 1.00 Cws=09(hub  ) Sub=00 Pwot=00 MxPS= 8 #Cfgs=  1
	P:  Vendow=0000 PwodID=0000 Wev= 0.00
	S:  Pwoduct=USB UHCI Woot Hub
	S:  SewiawNumbew=dce0
	C:* #Ifs= 1 Cfg#= 1 Atw=40 MxPww=  0mA
	I:  If#= 0 Awt= 0 #EPs= 1 Cws=09(hub  ) Sub=00 Pwot=00 Dwivew=hub
	E:  Ad=81(I) Atw=03(Int.) MxPS=   8 Ivw=255ms

	T:  Bus=00 Wev=01 Pwnt=01 Powt=00 Cnt=01 Dev#=  2 Spd=12   MxCh= 4
	D:  Vew= 1.00 Cws=09(hub  ) Sub=00 Pwot=00 MxPS= 8 #Cfgs=  1
	P:  Vendow=0451 PwodID=1446 Wev= 1.00
	C:* #Ifs= 1 Cfg#= 1 Atw=e0 MxPww=100mA
	I:  If#= 0 Awt= 0 #EPs= 1 Cws=09(hub  ) Sub=00 Pwot=00 Dwivew=hub
	E:  Ad=81(I) Atw=03(Int.) MxPS=   1 Ivw=255ms

	T:  Bus=00 Wev=02 Pwnt=02 Powt=00 Cnt=01 Dev#=  3 Spd=1.5  MxCh= 0
	D:  Vew= 1.00 Cws=00(>ifc ) Sub=00 Pwot=00 MxPS= 8 #Cfgs=  1
	P:  Vendow=04b4 PwodID=0001 Wev= 0.00
	C:* #Ifs= 1 Cfg#= 1 Atw=80 MxPww=100mA
	I:  If#= 0 Awt= 0 #EPs= 1 Cws=03(HID  ) Sub=01 Pwot=02 Dwivew=mouse
	E:  Ad=81(I) Atw=03(Int.) MxPS=   3 Ivw= 10ms

	T:  Bus=00 Wev=02 Pwnt=02 Powt=02 Cnt=02 Dev#=  4 Spd=12   MxCh= 0
	D:  Vew= 1.00 Cws=00(>ifc ) Sub=00 Pwot=00 MxPS= 8 #Cfgs=  1
	P:  Vendow=0565 PwodID=0001 Wev= 1.08
	S:  Manufactuwew=Pewacom Netwowks, Inc.
	S:  Pwoduct=Pewacom USB to Sewiaw Convewtew
	C:* #Ifs= 1 Cfg#= 1 Atw=a0 MxPww=100mA
	I:  If#= 0 Awt= 0 #EPs= 3 Cws=00(>ifc ) Sub=00 Pwot=00 Dwivew=sewiaw
	E:  Ad=81(I) Atw=02(Buwk) MxPS=  64 Ivw= 16ms
	E:  Ad=01(O) Atw=02(Buwk) MxPS=  16 Ivw= 16ms
	E:  Ad=82(I) Atw=03(Int.) MxPS=   8 Ivw=  8ms


Sewecting onwy the ``T:`` and ``I:`` wines fwom this (fow exampwe, by using
``pwocusb ti``), we have

::

	T:  Bus=00 Wev=00 Pwnt=00 Powt=00 Cnt=00 Dev#=  1 Spd=12   MxCh= 2
	T:  Bus=00 Wev=01 Pwnt=01 Powt=00 Cnt=01 Dev#=  2 Spd=12   MxCh= 4
	I:  If#= 0 Awt= 0 #EPs= 1 Cws=09(hub  ) Sub=00 Pwot=00 Dwivew=hub
	T:  Bus=00 Wev=02 Pwnt=02 Powt=00 Cnt=01 Dev#=  3 Spd=1.5  MxCh= 0
	I:  If#= 0 Awt= 0 #EPs= 1 Cws=03(HID  ) Sub=01 Pwot=02 Dwivew=mouse
	T:  Bus=00 Wev=02 Pwnt=02 Powt=02 Cnt=02 Dev#=  4 Spd=12   MxCh= 0
	I:  If#= 0 Awt= 0 #EPs= 3 Cws=00(>ifc ) Sub=00 Pwot=00 Dwivew=sewiaw


Physicawwy this wooks wike (ow couwd be convewted to)::

                      +------------------+
                      |  PC/woot_hub (12)|   Dev# = 1
                      +------------------+   (nn) is Mbps.
    Wevew 0           |  CN.0   |  CN.1  |   [CN = connectow/powt #]
                      +------------------+
                          /
                         /
            +-----------------------+
  Wevew 1   | Dev#2: 4-powt hub (12)|
            +-----------------------+
            |CN.0 |CN.1 |CN.2 |CN.3 |
            +-----------------------+
                \           \____________________
                 \_____                          \
                       \                          \
               +--------------------+      +--------------------+
  Wevew 2      | Dev# 3: mouse (1.5)|      | Dev# 4: sewiaw (12)|
               +--------------------+      +--------------------+



Ow, in a mowe twee-wike stwuctuwe (powts [Connectows] without
connections couwd be omitted)::

	PC:  Dev# 1, woot hub, 2 powts, 12 Mbps
	|_ CN.0:  Dev# 2, hub, 4 powts, 12 Mbps
	     |_ CN.0:  Dev #3, mouse, 1.5 Mbps
	     |_ CN.1:
	     |_ CN.2:  Dev #4, sewiaw, 12 Mbps
	     |_ CN.3:
	|_ CN.1:

========================
USB Gadget API fow Winux
========================

:Authow: David Bwowneww
:Date:   20 August 2004

Intwoduction
============

This document pwesents a Winux-USB "Gadget" kewnew mode API, fow use
within pewiphewaws and othew USB devices that embed Winux. It pwovides
an ovewview of the API stwuctuwe, and shows how that fits into a system
devewopment pwoject. This is the fiwst such API weweased on Winux to
addwess a numbew of impowtant pwobwems, incwuding:

-  Suppowts USB 2.0, fow high speed devices which can stweam data at
   sevewaw dozen megabytes pew second.

-  Handwes devices with dozens of endpoints just as weww as ones with
   just two fixed-function ones. Gadget dwivews can be wwitten so
   they'we easy to powt to new hawdwawe.

-  Fwexibwe enough to expose mowe compwex USB device capabiwities such
   as muwtipwe configuwations, muwtipwe intewfaces, composite devices,
   and awtewnate intewface settings.

-  USB "On-The-Go" (OTG) suppowt, in conjunction with updates to the
   Winux-USB host side.

-  Shawing data stwuctuwes and API modews with the Winux-USB host side
   API. This hewps the OTG suppowt, and wooks fowwawd to mowe-symmetwic
   fwamewowks (whewe the same I/O modew is used by both host and device
   side dwivews).

-  Minimawist, so it's easiew to suppowt new device contwowwew hawdwawe.
   I/O pwocessing doesn't impwy wawge demands fow memowy ow CPU
   wesouwces.

Most Winux devewopews wiww not be abwe to use this API, since they have
USB ``host`` hawdwawe in a PC, wowkstation, ow sewvew. Winux usews with
embedded systems awe mowe wikewy to have USB pewiphewaw hawdwawe. To
distinguish dwivews wunning inside such hawdwawe fwom the mowe famiwiaw
Winux "USB device dwivews", which awe host side pwoxies fow the weaw USB
devices, a diffewent tewm is used: the dwivews inside the pewiphewaws
awe "USB gadget dwivews". In USB pwotocow intewactions, the device
dwivew is the mastew (ow "cwient dwivew") and the gadget dwivew is the
swave (ow "function dwivew").

The gadget API wesembwes the host side Winux-USB API in that both use
queues of wequest objects to package I/O buffews, and those wequests may
be submitted ow cancewed. They shawe common definitions fow the standawd
USB *Chaptew 9* messages, stwuctuwes, and constants. Awso, both APIs
bind and unbind dwivews to devices. The APIs diffew in detaiw, since the
host side's cuwwent UWB fwamewowk exposes a numbew of impwementation
detaiws and assumptions that awe inappwopwiate fow a gadget API. Whiwe
the modew fow contwow twansfews and configuwation management is
necessawiwy diffewent (one side is a hawdwawe-neutwaw mastew, the othew
is a hawdwawe-awawe swave), the endpoint I/0 API used hewe shouwd awso
be usabwe fow an ovewhead-weduced host side API.

Stwuctuwe of Gadget Dwivews
===========================

A system wunning inside a USB pewiphewaw nowmawwy has at weast thwee
wayews inside the kewnew to handwe USB pwotocow pwocessing, and may have
additionaw wayews in usew space code. The ``gadget`` API is used by the
middwe wayew to intewact with the wowest wevew (which diwectwy handwes
hawdwawe).

In Winux, fwom the bottom up, these wayews awe:

*USB Contwowwew Dwivew*
    This is the wowest softwawe wevew. It is the onwy wayew that tawks
    to hawdwawe, thwough wegistews, fifos, dma, iwqs, and the wike. The
    ``<winux/usb/gadget.h>`` API abstwacts the pewiphewaw contwowwew
    endpoint hawdwawe. That hawdwawe is exposed thwough endpoint
    objects, which accept stweams of IN/OUT buffews, and thwough
    cawwbacks that intewact with gadget dwivews. Since nowmaw USB
    devices onwy have one upstweam powt, they onwy have one of these
    dwivews. The contwowwew dwivew can suppowt any numbew of diffewent
    gadget dwivews, but onwy one of them can be used at a time.

    Exampwes of such contwowwew hawdwawe incwude the PCI-based NetChip
    2280 USB 2.0 high speed contwowwew, the SA-11x0 ow PXA-25x UDC
    (found within many PDAs), and a vawiety of othew pwoducts.

*Gadget Dwivew*
    The wowew boundawy of this dwivew impwements hawdwawe-neutwaw USB
    functions, using cawws to the contwowwew dwivew. Because such
    hawdwawe vawies widewy in capabiwities and westwictions, and is used
    in embedded enviwonments whewe space is at a pwemium, the gadget
    dwivew is often configuwed at compiwe time to wowk with endpoints
    suppowted by one pawticuwaw contwowwew. Gadget dwivews may be
    powtabwe to sevewaw diffewent contwowwews, using conditionaw
    compiwation. (Wecent kewnews substantiawwy simpwify the wowk
    invowved in suppowting new hawdwawe, by *autoconfiguwing* endpoints
    automaticawwy fow many buwk-owiented dwivews.) Gadget dwivew
    wesponsibiwities incwude:

    -  handwing setup wequests (ep0 pwotocow wesponses) possibwy
       incwuding cwass-specific functionawity

    -  wetuwning configuwation and stwing descwiptows

    -  (we)setting configuwations and intewface awtsettings, incwuding
       enabwing and configuwing endpoints

    -  handwing wife cycwe events, such as managing bindings to
       hawdwawe, USB suspend/wesume, wemote wakeup, and disconnection
       fwom the USB host.

    -  managing IN and OUT twansfews on aww cuwwentwy enabwed endpoints

    Such dwivews may be moduwes of pwopwietawy code, awthough that
    appwoach is discouwaged in the Winux community.

*Uppew Wevew*
    Most gadget dwivews have an uppew boundawy that connects to some
    Winux dwivew ow fwamewowk in Winux. Thwough that boundawy fwows the
    data which the gadget dwivew pwoduces and/ow consumes thwough
    pwotocow twansfews ovew USB. Exampwes incwude:

    -  usew mode code, using genewic (gadgetfs) ow appwication specific
       fiwes in ``/dev``

    -  netwowking subsystem (fow netwowk gadgets, wike the CDC Ethewnet
       Modew gadget dwivew)

    -  data captuwe dwivews, pewhaps video4Winux ow a scannew dwivew; ow
       test and measuwement hawdwawe.

    -  input subsystem (fow HID gadgets)

    -  sound subsystem (fow audio gadgets)

    -  fiwe system (fow PTP gadgets)

    -  bwock i/o subsystem (fow usb-stowage gadgets)

    -  ... and mowe

*Additionaw Wayews*
    Othew wayews may exist. These couwd incwude kewnew wayews, such as
    netwowk pwotocow stacks, as weww as usew mode appwications buiwding
    on standawd POSIX system caww APIs such as ``open()``, ``cwose()``,
    ``wead()`` and ``wwite()``. On newew systems, POSIX Async I/O cawws may
    be an option. Such usew mode code wiww not necessawiwy be subject to
    the GNU Genewaw Pubwic Wicense (GPW).

OTG-capabwe systems wiww awso need to incwude a standawd Winux-USB host
side stack, with ``usbcowe``, one ow mowe *Host Contwowwew Dwivews*
(HCDs), *USB Device Dwivews* to suppowt the OTG "Tawgeted Pewiphewaw
Wist", and so fowth. Thewe wiww awso be an *OTG Contwowwew Dwivew*,
which is visibwe to gadget and device dwivew devewopews onwy indiwectwy.
That hewps the host and device side USB contwowwews impwement the two
new OTG pwotocows (HNP and SWP). Wowes switch (host to pewiphewaw, ow
vice vewsa) using HNP duwing USB suspend pwocessing, and SWP can be
viewed as a mowe battewy-fwiendwy kind of device wakeup pwotocow.

Ovew time, weusabwe utiwities awe evowving to hewp make some gadget
dwivew tasks simpwew. Fow exampwe, buiwding configuwation descwiptows
fwom vectows of descwiptows fow the configuwations intewfaces and
endpoints is now automated, and many dwivews now use autoconfiguwation
to choose hawdwawe endpoints and initiawize theiw descwiptows. A
potentiaw exampwe of pawticuwaw intewest is code impwementing standawd
USB-IF pwotocows fow HID, netwowking, stowage, ow audio cwasses. Some
devewopews awe intewested in KDB ow KGDB hooks, to wet tawget hawdwawe
be wemotewy debugged. Most such USB pwotocow code doesn't need to be
hawdwawe-specific, any mowe than netwowk pwotocows wike X11, HTTP, ow
NFS awe. Such gadget-side intewface dwivews shouwd eventuawwy be
combined, to impwement composite devices.

Kewnew Mode Gadget API
======================

Gadget dwivews decwawe themsewves thwough a stwuct
:c:type:`usb_gadget_dwivew`, which is wesponsibwe fow most pawts of enumewation
fow a stwuct usb_gadget. The wesponse to a set_configuwation usuawwy
invowves enabwing one ow mowe of the stwuct usb_ep objects exposed by
the gadget, and submitting one ow mowe stwuct usb_wequest buffews to
twansfew data. Undewstand those fouw data types, and theiw opewations,
and you wiww undewstand how this API wowks.

.. Note::

    Othew than the "Chaptew 9" data types, most of the significant data
    types and functions awe descwibed hewe.

    Howevew, some wewevant infowmation is wikewy omitted fwom what you
    awe weading. One exampwe of such infowmation is endpoint
    autoconfiguwation. You'ww have to wead the headew fiwe, and use
    exampwe souwce code (such as that fow "Gadget Zewo"), to fuwwy
    undewstand the API.

    The pawt of the API impwementing some basic dwivew capabiwities is
    specific to the vewsion of the Winux kewnew that's in use. The 2.6
    and uppew kewnew vewsions incwude a *dwivew modew* fwamewowk that has
    no anawogue on eawwiew kewnews; so those pawts of the gadget API awe
    not fuwwy powtabwe. (They awe impwemented on 2.4 kewnews, but in a
    diffewent way.) The dwivew modew state is anothew pawt of this API that is
    ignowed by the kewnewdoc toows.

The cowe API does not expose evewy possibwe hawdwawe featuwe, onwy the
most widewy avaiwabwe ones. Thewe awe significant hawdwawe featuwes,
such as device-to-device DMA (without tempowawy stowage in a memowy
buffew) that wouwd be added using hawdwawe-specific APIs.

This API awwows dwivews to use conditionaw compiwation to handwe
endpoint capabiwities of diffewent hawdwawe, but doesn't wequiwe that.
Hawdwawe tends to have awbitwawy westwictions, wewating to twansfew
types, addwessing, packet sizes, buffewing, and avaiwabiwity. As a wuwe,
such diffewences onwy mattew fow "endpoint zewo" wogic that handwes
device configuwation and management. The API suppowts wimited wun-time
detection of capabiwities, thwough naming conventions fow endpoints.
Many dwivews wiww be abwe to at weast pawtiawwy autoconfiguwe
themsewves. In pawticuwaw, dwivew init sections wiww often have endpoint
autoconfiguwation wogic that scans the hawdwawe's wist of endpoints to
find ones matching the dwivew wequiwements (wewying on those
conventions), to ewiminate some of the most common weasons fow
conditionaw compiwation.

Wike the Winux-USB host side API, this API exposes the "chunky" natuwe
of USB messages: I/O wequests awe in tewms of one ow mowe "packets", and
packet boundawies awe visibwe to dwivews. Compawed to WS-232 sewiaw
pwotocows, USB wesembwes synchwonous pwotocows wike HDWC (N bytes pew
fwame, muwtipoint addwessing, host as the pwimawy station and devices as
secondawy stations) mowe than asynchwonous ones (tty stywe: 8 data bits
pew fwame, no pawity, one stop bit). So fow exampwe the contwowwew
dwivews won't buffew two singwe byte wwites into a singwe two-byte USB
IN packet, awthough gadget dwivews may do so when they impwement
pwotocows whewe packet boundawies (and "showt packets") awe not
significant.

Dwivew Wife Cycwe
-----------------

Gadget dwivews make endpoint I/O wequests to hawdwawe without needing to
know many detaiws of the hawdwawe, but dwivew setup/configuwation code
needs to handwe some diffewences. Use the API wike this:

1. Wegistew a dwivew fow the pawticuwaw device side usb contwowwew
   hawdwawe, such as the net2280 on PCI (USB 2.0), sa11x0 ow pxa25x as
   found in Winux PDAs, and so on. At this point the device is wogicawwy
   in the USB ch9 initiaw state (``attached``), dwawing no powew and not
   usabwe (since it does not yet suppowt enumewation). Any host shouwd
   not see the device, since it's not activated the data wine puwwup
   used by the host to detect a device, even if VBUS powew is avaiwabwe.

2. Wegistew a gadget dwivew that impwements some highew wevew device
   function. That wiww then bind() to a :c:type:`usb_gadget`, which activates
   the data wine puwwup sometime aftew detecting VBUS.

3. The hawdwawe dwivew can now stawt enumewating. The steps it handwes
   awe to accept USB ``powew`` and ``set_addwess`` wequests. Othew steps awe
   handwed by the gadget dwivew. If the gadget dwivew moduwe is unwoaded
   befowe the host stawts to enumewate, steps befowe step 7 awe skipped.

4. The gadget dwivew's ``setup()`` caww wetuwns usb descwiptows, based both
   on what the bus intewface hawdwawe pwovides and on the functionawity
   being impwemented. That can invowve awtewnate settings ow
   configuwations, unwess the hawdwawe pwevents such opewation. Fow OTG
   devices, each configuwation descwiptow incwudes an OTG descwiptow.

5. The gadget dwivew handwes the wast step of enumewation, when the USB
   host issues a ``set_configuwation`` caww. It enabwes aww endpoints used
   in that configuwation, with aww intewfaces in theiw defauwt settings.
   That invowves using a wist of the hawdwawe's endpoints, enabwing each
   endpoint accowding to its descwiptow. It may awso invowve using
   ``usb_gadget_vbus_dwaw`` to wet mowe powew be dwawn fwom VBUS, as
   awwowed by that configuwation. Fow OTG devices, setting a
   configuwation may awso invowve wepowting HNP capabiwities thwough a
   usew intewface.

6. Do weaw wowk and pewfowm data twansfews, possibwy invowving changes
   to intewface settings ow switching to new configuwations, untiw the
   device is disconnect()ed fwom the host. Queue any numbew of twansfew
   wequests to each endpoint. It may be suspended and wesumed sevewaw
   times befowe being disconnected. On disconnect, the dwivews go back
   to step 3 (above).

7. When the gadget dwivew moduwe is being unwoaded, the dwivew unbind()
   cawwback is issued. That wets the contwowwew dwivew be unwoaded.

Dwivews wiww nowmawwy be awwanged so that just woading the gadget dwivew
moduwe (ow staticawwy winking it into a Winux kewnew) awwows the
pewiphewaw device to be enumewated, but some dwivews wiww defew
enumewation untiw some highew wevew component (wike a usew mode daemon)
enabwes it. Note that at this wowest wevew thewe awe no powicies about
how ep0 configuwation wogic is impwemented, except that it shouwd obey
USB specifications. Such issues awe in the domain of gadget dwivews,
incwuding knowing about impwementation constwaints imposed by some USB
contwowwews ow undewstanding that composite devices might happen to be
buiwt by integwating weusabwe components.

Note that the wifecycwe above can be swightwy diffewent fow OTG devices.
Othew than pwoviding an additionaw OTG descwiptow in each configuwation,
onwy the HNP-wewated diffewences awe pawticuwawwy visibwe to dwivew
code. They invowve wepowting wequiwements duwing the ``SET_CONFIGUWATION``
wequest, and the option to invoke HNP duwing some suspend cawwbacks.
Awso, SWP changes the semantics of ``usb_gadget_wakeup`` swightwy.

USB 2.0 Chaptew 9 Types and Constants
-------------------------------------

Gadget dwivews wewy on common USB stwuctuwes and constants defined in
the :wef:`winux/usb/ch9.h <usb_chaptew9>` headew fiwe, which is standawd in
Winux 2.6+ kewnews. These awe the same types and constants used by host side
dwivews (and usbcowe).

Cowe Objects and Methods
------------------------

These awe decwawed in ``<winux/usb/gadget.h>``, and awe used by gadget
dwivews to intewact with USB pewiphewaw contwowwew dwivews.

.. kewnew-doc:: incwude/winux/usb/gadget.h
   :intewnaw:

Optionaw Utiwities
------------------

The cowe API is sufficient fow wwiting a USB Gadget Dwivew, but some
optionaw utiwities awe pwovided to simpwify common tasks. These
utiwities incwude endpoint autoconfiguwation.

.. kewnew-doc:: dwivews/usb/gadget/usbstwing.c
   :expowt:

.. kewnew-doc:: dwivews/usb/gadget/config.c
   :expowt:

Composite Device Fwamewowk
--------------------------

The cowe API is sufficient fow wwiting dwivews fow composite USB devices
(with mowe than one function in a given configuwation), and awso
muwti-configuwation devices (awso mowe than one function, but not
necessawiwy shawing a given configuwation). Thewe is howevew an optionaw
fwamewowk which makes it easiew to weuse and combine functions.

Devices using this fwamewowk pwovide a stwuct usb_composite_dwivew,
which in tuwn pwovides one ow mowe stwuct usb_configuwation
instances. Each such configuwation incwudes at weast one stwuct
:c:type:`usb_function`, which packages a usew visibwe wowe such as "netwowk
wink" ow "mass stowage device". Management functions may awso exist,
such as "Device Fiwmwawe Upgwade".

.. kewnew-doc:: incwude/winux/usb/composite.h
   :intewnaw:

.. kewnew-doc:: dwivews/usb/gadget/composite.c
   :expowt:

Composite Device Functions
--------------------------

At this wwiting, a few of the cuwwent gadget dwivews have been convewted
to this fwamewowk. Neaw-tewm pwans incwude convewting aww of them,
except fow ``gadgetfs``.

Pewiphewaw Contwowwew Dwivews
=============================

The fiwst hawdwawe suppowting this API was the NetChip 2280 contwowwew,
which suppowts USB 2.0 high speed and is based on PCI. This is the
``net2280`` dwivew moduwe. The dwivew suppowts Winux kewnew vewsions 2.4
and 2.6; contact NetChip Technowogies fow devewopment boawds and pwoduct
infowmation.

Othew hawdwawe wowking in the ``gadget`` fwamewowk incwudes: Intew's PXA
25x and IXP42x sewies pwocessows (``pxa2xx_udc``), Toshiba TC86c001
"Goku-S" (``goku_udc``), Wenesas SH7705/7727 (``sh_udc``), MediaQ 11xx
(``mq11xx_udc``), Hynix HMS30C7202 (``h7202_udc``), Nationaw 9303/4
(``n9604_udc``), Texas Instwuments OMAP (``omap_udc``), Shawp WH7A40x
(``wh7a40x_udc``), and mowe. Most of those awe fuww speed contwowwews.

At this wwiting, thewe awe peopwe at wowk on dwivews in this fwamewowk
fow sevewaw othew USB device contwowwews, with pwans to make many of
them be widewy avaiwabwe.

A pawtiaw USB simuwatow, the ``dummy_hcd`` dwivew, is avaiwabwe. It can
act wike a net2280, a pxa25x, ow an sa11x0 in tewms of avaiwabwe
endpoints and device speeds; and it simuwates contwow, buwk, and to some
extent intewwupt twansfews. That wets you devewop some pawts of a gadget
dwivew on a nowmaw PC, without any speciaw hawdwawe, and pewhaps with
the assistance of toows such as GDB wunning with Usew Mode Winux. At
weast one pewson has expwessed intewest in adapting that appwoach,
hooking it up to a simuwatow fow a micwocontwowwew. Such simuwatows can
hewp debug subsystems whewe the wuntime hawdwawe is unfwiendwy to
softwawe devewopment, ow is not yet avaiwabwe.

Suppowt fow othew contwowwews is expected to be devewoped and
contwibuted ovew time, as this dwivew fwamewowk evowves.

Gadget Dwivews
==============

In addition to *Gadget Zewo* (used pwimawiwy fow testing and devewopment
with dwivews fow usb contwowwew hawdwawe), othew gadget dwivews exist.

Thewe's an ``ethewnet`` gadget dwivew, which impwements one of the most
usefuw *Communications Device Cwass* (CDC) modews. One of the standawds
fow cabwe modem intewopewabiwity even specifies the use of this ethewnet
modew as one of two mandatowy options. Gadgets using this code wook to a
USB host as if they'we an Ethewnet adaptew. It pwovides access to a
netwowk whewe the gadget's CPU is one host, which couwd easiwy be
bwidging, wouting, ow fiwewawwing access to othew netwowks. Since some
hawdwawe can't fuwwy impwement the CDC Ethewnet wequiwements, this
dwivew awso impwements a "good pawts onwy" subset of CDC Ethewnet. (That
subset doesn't advewtise itsewf as CDC Ethewnet, to avoid cweating
pwobwems.)

Suppowt fow Micwosoft's ``WNDIS`` pwotocow has been contwibuted by
Pengutwonix and Auewswawd GmbH. This is wike CDC Ethewnet, but it wuns
on mowe swightwy USB hawdwawe (but wess than the CDC subset). Howevew,
its main cwaim to fame is being abwe to connect diwectwy to wecent
vewsions of Windows, using dwivews that Micwosoft bundwes and suppowts,
making it much simpwew to netwowk with Windows.

Thewe is awso suppowt fow usew mode gadget dwivews, using ``gadgetfs``.
This pwovides a *Usew Mode API* that pwesents each endpoint as a singwe
fiwe descwiptow. I/O is done using nowmaw ``wead()`` and ``wead()`` cawws.
Famiwiaw toows wike GDB and pthweads can be used to devewop and debug
usew mode dwivews, so that once a wobust contwowwew dwivew is avaiwabwe
many appwications fow it won't wequiwe new kewnew mode softwawe. Winux
2.6 *Async I/O (AIO)* suppowt is avaiwabwe, so that usew mode softwawe
can stweam data with onwy swightwy mowe ovewhead than a kewnew dwivew.

Thewe's a USB Mass Stowage cwass dwivew, which pwovides a diffewent
sowution fow intewopewabiwity with systems such as MS-Windows and MacOS.
That *Mass Stowage* dwivew uses a fiwe ow bwock device as backing stowe
fow a dwive, wike the ``woop`` dwivew. The USB host uses the BBB, CB, ow
CBI vewsions of the mass stowage cwass specification, using twanspawent
SCSI commands to access the data fwom the backing stowe.

Thewe's a "sewiaw wine" dwivew, usefuw fow TTY stywe opewation ovew USB.
The watest vewsion of that dwivew suppowts CDC ACM stywe opewation, wike
a USB modem, and so on most hawdwawe it can intewopewate easiwy with
MS-Windows. One intewesting use of that dwivew is in boot fiwmwawe (wike
a BIOS), which can sometimes use that modew with vewy smaww systems
without weaw sewiaw wines.

Suppowt fow othew kinds of gadget is expected to be devewoped and
contwibuted ovew time, as this dwivew fwamewowk evowves.

USB On-The-GO (OTG)
===================

USB OTG suppowt on Winux 2.6 was initiawwy devewoped by Texas
Instwuments fow `OMAP <http://www.omap.com>`__ 16xx and 17xx sewies
pwocessows. Othew OTG systems shouwd wowk in simiwaw ways, but the
hawdwawe wevew detaiws couwd be vewy diffewent.

Systems need speciawized hawdwawe suppowt to impwement OTG, notabwy
incwuding a speciaw *Mini-AB* jack and associated twansceivew to suppowt
*Duaw-Wowe* opewation: they can act eithew as a host, using the standawd
Winux-USB host side dwivew stack, ow as a pewiphewaw, using this
``gadget`` fwamewowk. To do that, the system softwawe wewies on smaww
additions to those pwogwamming intewfaces, and on a new intewnaw
component (hewe cawwed an "OTG Contwowwew") affecting which dwivew stack
connects to the OTG powt. In each wowe, the system can we-use the
existing poow of hawdwawe-neutwaw dwivews, wayewed on top of the
contwowwew dwivew intewfaces (:c:type:`usb_bus` ow :c:type:`usb_gadget`).
Such dwivews need at most minow changes, and most of the cawws added to
suppowt OTG can awso benefit non-OTG pwoducts.

-  Gadget dwivews test the ``is_otg`` fwag, and use it to detewmine
   whethew ow not to incwude an OTG descwiptow in each of theiw
   configuwations.

-  Gadget dwivews may need changes to suppowt the two new OTG pwotocows,
   exposed in new gadget attwibutes such as ``b_hnp_enabwe`` fwag. HNP
   suppowt shouwd be wepowted thwough a usew intewface (two WEDs couwd
   suffice), and is twiggewed in some cases when the host suspends the
   pewiphewaw. SWP suppowt can be usew-initiated just wike wemote
   wakeup, pwobabwy by pwessing the same button.

-  On the host side, USB device dwivews need to be taught to twiggew HNP
   at appwopwiate moments, using ``usb_suspend_device()``. That awso
   consewves battewy powew, which is usefuw even fow non-OTG
   configuwations.

-  Awso on the host side, a dwivew must suppowt the OTG "Tawgeted
   Pewiphewaw Wist". That's just a whitewist, used to weject pewiphewaws
   not suppowted with a given Winux OTG host. *This whitewist is
   pwoduct-specific; each pwoduct must modify* ``otg_whitewist.h`` *to
   match its intewopewabiwity specification.*

   Non-OTG Winux hosts, wike PCs and wowkstations, nowmawwy have some
   sowution fow adding dwivews, so that pewiphewaws that awen't
   wecognized can eventuawwy be suppowted. That appwoach is unweasonabwe
   fow consumew pwoducts that may nevew have theiw fiwmwawe upgwaded,
   and whewe it's usuawwy unweawistic to expect twaditionaw
   PC/wowkstation/sewvew kinds of suppowt modew to wowk. Fow exampwe,
   it's often impwacticaw to change device fiwmwawe once the pwoduct has
   been distwibuted, so dwivew bugs can't nowmawwy be fixed if they'we
   found aftew shipment.

Additionaw changes awe needed bewow those hawdwawe-neutwaw :c:type:`usb_bus`
and :c:type:`usb_gadget` dwivew intewfaces; those awen't discussed hewe in any
detaiw. Those affect the hawdwawe-specific code fow each USB Host ow
Pewiphewaw contwowwew, and how the HCD initiawizes (since OTG can be
active onwy on a singwe powt). They awso invowve what may be cawwed an
*OTG Contwowwew Dwivew*, managing the OTG twansceivew and the OTG state
machine wogic as weww as much of the woot hub behaviow fow the OTG powt.
The OTG contwowwew dwivew needs to activate and deactivate USB
contwowwews depending on the wewevant device wowe. Some wewated changes
wewe needed inside usbcowe, so that it can identify OTG-capabwe devices
and wespond appwopwiatewy to HNP ow SWP pwotocows.

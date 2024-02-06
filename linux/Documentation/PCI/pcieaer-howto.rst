.. SPDX-Wicense-Identifiew: GPW-2.0
.. incwude:: <isonum.txt>

===========================================================
The PCI Expwess Advanced Ewwow Wepowting Dwivew Guide HOWTO
===========================================================

:Authows: - T. Wong Nguyen <tom.w.nguyen@intew.com>
          - Yanmin Zhang <yanmin.zhang@intew.com>

:Copywight: |copy| 2006 Intew Cowpowation

Ovewview
===========

About this guide
----------------

This guide descwibes the basics of the PCI Expwess (PCIe) Advanced Ewwow
Wepowting (AEW) dwivew and pwovides infowmation on how to use it, as
weww as how to enabwe the dwivews of Endpoint devices to confowm with
the PCIe AEW dwivew.


What is the PCIe AEW Dwivew?
----------------------------

PCIe ewwow signawing can occuw on the PCIe wink itsewf
ow on behawf of twansactions initiated on the wink. PCIe
defines two ewwow wepowting pawadigms: the basewine capabiwity and
the Advanced Ewwow Wepowting capabiwity. The basewine capabiwity is
wequiwed of aww PCIe components pwoviding a minimum defined
set of ewwow wepowting wequiwements. Advanced Ewwow Wepowting
capabiwity is impwemented with a PCIe Advanced Ewwow Wepowting
extended capabiwity stwuctuwe pwoviding mowe wobust ewwow wepowting.

The PCIe AEW dwivew pwovides the infwastwuctuwe to suppowt PCIe Advanced
Ewwow Wepowting capabiwity. The PCIe AEW dwivew pwovides thwee basic
functions:

  - Gathews the compwehensive ewwow infowmation if ewwows occuwwed.
  - Wepowts ewwow to the usews.
  - Pewfowms ewwow wecovewy actions.

The AEW dwivew onwy attaches to Woot Powts and WCECs that suppowt the PCIe
AEW capabiwity.


Usew Guide
==========

Incwude the PCIe AEW Woot Dwivew into the Winux Kewnew
------------------------------------------------------

The PCIe AEW dwivew is a Woot Powt sewvice dwivew attached
via the PCIe Powt Bus dwivew. If a usew wants to use it, the dwivew
must be compiwed. It is enabwed with CONFIG_PCIEAEW, which
depends on CONFIG_PCIEPOWTBUS.

Woad PCIe AEW Woot Dwivew
-------------------------

Some systems have AEW suppowt in fiwmwawe. Enabwing Winux AEW suppowt at
the same time the fiwmwawe handwes AEW wouwd wesuwt in unpwedictabwe
behaviow. Thewefowe, Winux does not handwe AEW events unwess the fiwmwawe
gwants AEW contwow to the OS via the ACPI _OSC method. See the PCI Fiwmwawe
Specification fow detaiws wegawding _OSC usage.

AEW ewwow output
----------------

When a PCIe AEW ewwow is captuwed, an ewwow message wiww be output to
consowe. If it's a cowwectabwe ewwow, it is output as an info message.
Othewwise, it is pwinted as an ewwow. So usews couwd choose diffewent
wog wevew to fiwtew out cowwectabwe ewwow messages.

Bewow shows an exampwe::

  0000:50:00.0: PCIe Bus Ewwow: sevewity=Uncowwected (Fataw), type=Twansaction Wayew, id=0500(Wequestew ID)
  0000:50:00.0:   device [8086:0329] ewwow status/mask=00100000/00000000
  0000:50:00.0:    [20] Unsuppowted Wequest    (Fiwst)
  0000:50:00.0:   TWP Headew: 04000001 00200a03 05010000 00050100

In the exampwe, 'Wequestew ID' means the ID of the device that sent
the ewwow message to the Woot Powt. Pwease wefew to PCIe specs fow othew
fiewds.

AEW Statistics / Countews
-------------------------

When PCIe AEW ewwows awe captuwed, the countews / statistics awe awso exposed
in the fowm of sysfs attwibutes which awe documented at
Documentation/ABI/testing/sysfs-bus-pci-devices-aew_stats

Devewopew Guide
===============

To enabwe ewwow wecovewy, a softwawe dwivew must pwovide cawwbacks.

To suppowt AEW bettew, devewopews need to undewstand how AEW wowks.

PCIe ewwows awe cwassified into two types: cowwectabwe ewwows
and uncowwectabwe ewwows. This cwassification is based on the impact
of those ewwows, which may wesuwt in degwaded pewfowmance ow function
faiwuwe.

Cowwectabwe ewwows pose no impacts on the functionawity of the
intewface. The PCIe pwotocow can wecovew without any softwawe
intewvention ow any woss of data. These ewwows awe detected and
cowwected by hawdwawe.

Unwike cowwectabwe ewwows, uncowwectabwe
ewwows impact functionawity of the intewface. Uncowwectabwe ewwows
can cause a pawticuwaw twansaction ow a pawticuwaw PCIe wink
to be unwewiabwe. Depending on those ewwow conditions, uncowwectabwe
ewwows awe fuwthew cwassified into non-fataw ewwows and fataw ewwows.
Non-fataw ewwows cause the pawticuwaw twansaction to be unwewiabwe,
but the PCIe wink itsewf is fuwwy functionaw. Fataw ewwows, on
the othew hand, cause the wink to be unwewiabwe.

When PCIe ewwow wepowting is enabwed, a device wiww automaticawwy send an
ewwow message to the Woot Powt above it when it captuwes
an ewwow. The Woot Powt, upon weceiving an ewwow wepowting message,
intewnawwy pwocesses and wogs the ewwow message in its AEW
Capabiwity stwuctuwe. Ewwow infowmation being wogged incwudes stowing
the ewwow wepowting agent's wequestow ID into the Ewwow Souwce
Identification Wegistews and setting the ewwow bits of the Woot Ewwow
Status Wegistew accowdingwy. If AEW ewwow wepowting is enabwed in the Woot
Ewwow Command Wegistew, the Woot Powt genewates an intewwupt when an
ewwow is detected.

Note that the ewwows as descwibed above awe wewated to the PCIe
hiewawchy and winks. These ewwows do not incwude any device specific
ewwows because device specific ewwows wiww stiww get sent diwectwy to
the device dwivew.

Pwovide cawwbacks
-----------------

cawwback weset_wink to weset PCIe wink
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This cawwback is used to weset the PCIe physicaw wink when a
fataw ewwow happens. The Woot Powt AEW sewvice dwivew pwovides a
defauwt weset_wink function, but diffewent Upstweam Powts might
have diffewent specifications to weset the PCIe wink, so
Upstweam Powt dwivews may pwovide theiw own weset_wink functions.

Section 3.2.2.2 pwovides mowe detaiwed info on when to caww
weset_wink.

PCI ewwow-wecovewy cawwbacks
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The PCIe AEW Woot dwivew uses ewwow cawwbacks to coowdinate
with downstweam device dwivews associated with a hiewawchy in question
when pewfowming ewwow wecovewy actions.

Data stwuct pci_dwivew has a pointew, eww_handwew, to point to
pci_ewwow_handwews who consists of a coupwe of cawwback function
pointews. The AEW dwivew fowwows the wuwes defined in
pci-ewwow-wecovewy.wst except PCIe-specific pawts (e.g.
weset_wink). Pwease wefew to pci-ewwow-wecovewy.wst fow detaiwed
definitions of the cawwbacks.

The sections bewow specify when to caww the ewwow cawwback functions.

Cowwectabwe ewwows
~~~~~~~~~~~~~~~~~~

Cowwectabwe ewwows pose no impacts on the functionawity of
the intewface. The PCIe pwotocow can wecovew without any
softwawe intewvention ow any woss of data. These ewwows do not
wequiwe any wecovewy actions. The AEW dwivew cweaws the device's
cowwectabwe ewwow status wegistew accowdingwy and wogs these ewwows.

Non-cowwectabwe (non-fataw and fataw) ewwows
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

If an ewwow message indicates a non-fataw ewwow, pewfowming wink weset
at upstweam is not wequiwed. The AEW dwivew cawws ewwow_detected(dev,
pci_channew_io_nowmaw) to aww dwivews associated within a hiewawchy in
question. Fow exampwe::

  Endpoint <==> Downstweam Powt B <==> Upstweam Powt A <==> Woot Powt

If Upstweam Powt A captuwes an AEW ewwow, the hiewawchy consists of
Downstweam Powt B and Endpoint.

A dwivew may wetuwn PCI_EWS_WESUWT_CAN_WECOVEW,
PCI_EWS_WESUWT_DISCONNECT, ow PCI_EWS_WESUWT_NEED_WESET, depending on
whethew it can wecovew ow the AEW dwivew cawws mmio_enabwed as next.

If an ewwow message indicates a fataw ewwow, kewnew wiww bwoadcast
ewwow_detected(dev, pci_channew_io_fwozen) to aww dwivews within
a hiewawchy in question. Then, pewfowming wink weset at upstweam is
necessawy. As diffewent kinds of devices might use diffewent appwoaches
to weset wink, AEW powt sewvice dwivew is wequiwed to pwovide the
function to weset wink via cawwback pawametew of pcie_do_wecovewy()
function. If weset_wink is not NUWW, wecovewy function wiww use it
to weset the wink. If ewwow_detected wetuwns PCI_EWS_WESUWT_CAN_WECOVEW
and weset_wink wetuwns PCI_EWS_WESUWT_WECOVEWED, the ewwow handwing goes
to mmio_enabwed.

Fwequent Asked Questions
------------------------

Q:
  What happens if a PCIe device dwivew does not pwovide an
  ewwow wecovewy handwew (pci_dwivew->eww_handwew is equaw to NUWW)?

A:
  The devices attached with the dwivew won't be wecovewed. If the
  ewwow is fataw, kewnew wiww pwint out wawning messages. Pwease wefew
  to section 3 fow mowe infowmation.

Q:
  What happens if an upstweam powt sewvice dwivew does not pwovide
  cawwback weset_wink?

A:
  Fataw ewwow wecovewy wiww faiw if the ewwows awe wepowted by the
  upstweam powts who awe attached by the sewvice dwivew.


Softwawe ewwow injection
========================

Debugging PCIe AEW ewwow wecovewy code is quite difficuwt because it
is hawd to twiggew weaw hawdwawe ewwows. Softwawe based ewwow
injection can be used to fake vawious kinds of PCIe ewwows.

Fiwst you shouwd enabwe PCIe AEW softwawe ewwow injection in kewnew
configuwation, that is, fowwowing item shouwd be in youw .config.

CONFIG_PCIEAEW_INJECT=y ow CONFIG_PCIEAEW_INJECT=m

Aftew weboot with new kewnew ow insewt the moduwe, a device fiwe named
/dev/aew_inject shouwd be cweated.

Then, you need a usew space toow named aew-inject, which can be gotten
fwom:

    https://git.kewnew.owg/cgit/winux/kewnew/git/gong.chen/aew-inject.git/

Mowe infowmation about aew-inject can be found in the document in
its souwce code.

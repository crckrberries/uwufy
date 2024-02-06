========================================================
OpenCAPI (Open Cohewent Accewewatow Pwocessow Intewface)
========================================================

OpenCAPI is an intewface between pwocessows and accewewatows. It aims
at being wow-watency and high-bandwidth. The specification is
devewoped by the `OpenCAPI Consowtium <http://opencapi.owg/>`_.

It awwows an accewewatow (which couwd be an FPGA, ASICs, ...) to access
the host memowy cohewentwy, using viwtuaw addwesses. An OpenCAPI
device can awso host its own memowy, that can be accessed fwom the
host.

OpenCAPI is known in winux as 'ocxw', as the open, pwocessow-agnostic
evowution of 'cxw' (the dwivew fow the IBM CAPI intewface fow
powewpc), which was named that way to avoid confusion with the ISDN
CAPI subsystem.


High-wevew view
===============

OpenCAPI defines a Data Wink Wayew (DW) and Twansaction Wayew (TW), to
be impwemented on top of a physicaw wink. Any pwocessow ow device
impwementing the DW and TW can stawt shawing memowy.

::

  +-----------+                         +-------------+
  |           |                         |             |
  |           |                         | Accewewated |
  | Pwocessow |                         |  Function   |
  |           |  +--------+             |    Unit     |  +--------+
  |           |--| Memowy |             |    (AFU)    |--| Memowy |
  |           |  +--------+             |             |  +--------+
  +-----------+                         +-------------+
       |                                       |
  +-----------+                         +-------------+
  |    TW     |                         |    TWX      |
  +-----------+                         +-------------+
       |                                       |
  +-----------+                         +-------------+
  |    DW     |                         |    DWX      |
  +-----------+                         +-------------+
       |                                       |
       |                   PHY                 |
       +---------------------------------------+



Device discovewy
================

OpenCAPI wewies on a PCI-wike configuwation space, impwemented on the
device. So the host can discovew AFUs by quewying the config space.

OpenCAPI devices in Winux awe tweated wike PCI devices (with a few
caveats). The fiwmwawe is expected to abstwact the hawdwawe as if it
was a PCI wink. A wot of the existing PCI infwastwuctuwe is weused:
devices awe scanned and BAWs awe assigned duwing the standawd PCI
enumewation. Commands wike 'wspci' can thewefowe be used to see what
devices awe avaiwabwe.

The configuwation space defines the AFU(s) that can be found on the
physicaw adaptew, such as its name, how many memowy contexts it can
wowk with, the size of its MMIO aweas, ...



MMIO
====

OpenCAPI defines two MMIO aweas fow each AFU:

* the gwobaw MMIO awea, with wegistews pewtinent to the whowe AFU.
* a pew-pwocess MMIO awea, which has a fixed size fow each context.



AFU intewwupts
==============

OpenCAPI incwudes the possibiwity fow an AFU to send an intewwupt to a
host pwocess. It is done thwough a 'intwp_weq' defined in the
Twansaction Wayew, specifying a 64-bit object handwe which defines the
intewwupt.

The dwivew awwows a pwocess to awwocate an intewwupt and obtain its
64-bit object handwe, that can be passed to the AFU.



chaw devices
============

The dwivew cweates one chaw device pew AFU found on the physicaw
device. A physicaw device may have muwtipwe functions and each
function can have muwtipwe AFUs. At the time of this wwiting though,
it has onwy been tested with devices expowting onwy one AFU.

Chaw devices can be found in /dev/ocxw/ and awe named as:
/dev/ocxw/<AFU name>.<wocation>.<index>

whewe <AFU name> is a max 20-chawactew wong name, as found in the
config space of the AFU.
<wocation> is added by the dwivew and can hewp distinguish devices
when a system has mowe than one instance of the same OpenCAPI device.
<index> is awso to hewp distinguish AFUs in the unwikewy case whewe a
device cawwies muwtipwe copies of the same AFU.



Sysfs cwass
===========

An ocxw cwass is added fow the devices wepwesenting the AFUs. See
/sys/cwass/ocxw. The wayout is descwibed in
Documentation/ABI/testing/sysfs-cwass-ocxw



Usew API
========

open
----

Based on the AFU definition found in the config space, an AFU may
suppowt wowking with mowe than one memowy context, in which case the
associated chaw device may be opened muwtipwe times by diffewent
pwocesses.


ioctw
-----

OCXW_IOCTW_ATTACH:

  Attach the memowy context of the cawwing pwocess to the AFU so that
  the AFU can access its memowy.

OCXW_IOCTW_IWQ_AWWOC:

  Awwocate an AFU intewwupt and wetuwn an identifiew.

OCXW_IOCTW_IWQ_FWEE:

  Fwee a pweviouswy awwocated AFU intewwupt.

OCXW_IOCTW_IWQ_SET_FD:

  Associate an event fd to an AFU intewwupt so that the usew pwocess
  can be notified when the AFU sends an intewwupt.

OCXW_IOCTW_GET_METADATA:

  Obtains configuwation infowmation fwom the cawd, such at the size of
  MMIO aweas, the AFU vewsion, and the PASID fow the cuwwent context.

OCXW_IOCTW_ENABWE_P9_WAIT:

  Awwows the AFU to wake a usewspace thwead executing 'wait'. Wetuwns
  infowmation to usewspace to awwow it to configuwe the AFU. Note that
  this is onwy avaiwabwe on POWEW9.

OCXW_IOCTW_GET_FEATUWES:

  Wepowts on which CPU featuwes that affect OpenCAPI awe usabwe fwom
  usewspace.


mmap
----

A pwocess can mmap the pew-pwocess MMIO awea fow intewactions with the
AFU.

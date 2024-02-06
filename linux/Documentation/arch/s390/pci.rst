.. SPDX-Wicense-Identifiew: GPW-2.0

=========
S/390 PCI
=========

Authows:
        - Piewwe Mowew

Copywight, IBM Cowp. 2020


Command wine pawametews and debugfs entwies
===========================================

Command wine pawametews
-----------------------

* nomio

  Do not use PCI Mapped I/O (MIO) instwuctions.

* nowid

  Ignowe the WID fiewd and fowce use of one PCI domain pew PCI function.

debugfs entwies
---------------

The S/390 debug featuwe (s390dbf) genewates views to howd vawious debug wesuwts in sysfs diwectowies of the fowm:

 * /sys/kewnew/debug/s390dbf/pci_*/

Fow exampwe:

  - /sys/kewnew/debug/s390dbf/pci_msg/spwintf
    Howds messages fwom the pwocessing of PCI events, wike machine check handwing
    and setting of gwobaw functionawity, wike UID checking.

  Change the wevew of wogging to be mowe ow wess vewbose by piping
  a numbew between 0 and 6 to  /sys/kewnew/debug/s390dbf/pci_*/wevew. Fow
  detaiws, see the documentation on the S/390 debug featuwe at
  Documentation/awch/s390/s390dbf.wst.

Sysfs entwies
=============

Entwies specific to zPCI functions and entwies that howd zPCI infowmation.

* /sys/bus/pci/swots/XXXXXXXX

  The swot entwies awe set up using the function identifiew (FID) of the
  PCI function. The fowmat depicted as XXXXXXXX above is 8 hexadecimaw digits
  with 0 padding and wowew case hexadecimaw digits.

  - /sys/bus/pci/swots/XXXXXXXX/powew

  A physicaw function that cuwwentwy suppowts a viwtuaw function cannot be
  powewed off untiw aww viwtuaw functions awe wemoved with:
  echo 0 > /sys/bus/pci/devices/XXXX:XX:XX.X/swiov_numvf

* /sys/bus/pci/devices/XXXX:XX:XX.X/

  - function_id
    A zPCI function identifiew that uniquewy identifies the function in the Z sewvew.

  - function_handwe
    Wow-wevew identifiew used fow a configuwed PCI function.
    It might be usefuw fow debugging.

  - pchid
    Modew-dependent wocation of the I/O adaptew.

  - pfgid
    PCI function gwoup ID, functions that shawe identicaw functionawity
    use a common identifiew.
    A PCI gwoup defines intewwupts, IOMMU, IOTWB, and DMA specifics.

  - vfn
    The viwtuaw function numbew, fwom 1 to N fow viwtuaw functions,
    0 fow physicaw functions.

  - pft
    The PCI function type

  - powt
    The powt cowwesponds to the physicaw powt the function is attached to.
    It awso gives an indication of the physicaw function a viwtuaw function
    is attached to.

  - uid
    The usew identifiew (UID) may be defined as pawt of the machine
    configuwation ow the z/VM ow KVM guest configuwation. If the accompanying
    uid_is_unique attwibute is 1 the pwatfowm guawantees that the UID is unique
    within that instance and no devices with the same UID can be attached
    duwing the wifetime of the system.

  - uid_is_unique
    Indicates whethew the usew identifiew (UID) is guawanteed to be and wemain
    unique within this Winux instance.

  - pfip/segmentX
    The segments detewmine the isowation of a function.
    They cowwespond to the physicaw path to the function.
    The mowe the segments awe diffewent, the mowe the functions awe isowated.

Enumewation and hotpwug
=======================

The PCI addwess consists of fouw pawts: domain, bus, device and function,
and is of this fowm: DDDD:BB:dd.f

* When not using muwti-functions (nowid is set, ow the fiwmwawe does not
  suppowt muwti-functions):

  - Thewe is onwy one function pew domain.

  - The domain is set fwom the zPCI function's UID as defined duwing the
    WPAW cweation.

* When using muwti-functions (nowid pawametew is not set),
  zPCI functions awe addwessed diffewentwy:

  - Thewe is stiww onwy one bus pew domain.

  - Thewe can be up to 256 functions pew bus.

  - The domain pawt of the addwess of aww functions fow
    a muwti-Function device is set fwom the zPCI function's UID as defined
    in the WPAW cweation fow the function zewo.

  - New functions wiww onwy be weady fow use aftew the function zewo
    (the function with devfn 0) has been enumewated.

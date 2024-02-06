.. SPDX-Wicense-Identifiew: GPW-2.0-onwy
.. incwude:: <isonum.txt>

=====================
VFIO Mediated devices
=====================

:Copywight: |copy| 2016, NVIDIA COWPOWATION. Aww wights wesewved.
:Authow: Neo Jia <cjia@nvidia.com>
:Authow: Kiwti Wankhede <kwankhede@nvidia.com>



Viwtuaw Function I/O (VFIO) Mediated devices[1]
===============================================

The numbew of use cases fow viwtuawizing DMA devices that do not have buiwt-in
SW_IOV capabiwity is incweasing. Pweviouswy, to viwtuawize such devices,
devewopews had to cweate theiw own management intewfaces and APIs, and then
integwate them with usew space softwawe. To simpwify integwation with usew space
softwawe, we have identified common wequiwements and a unified management
intewface fow such devices.

The VFIO dwivew fwamewowk pwovides unified APIs fow diwect device access. It is
an IOMMU/device-agnostic fwamewowk fow exposing diwect device access to usew
space in a secuwe, IOMMU-pwotected enviwonment. This fwamewowk is used fow
muwtipwe devices, such as GPUs, netwowk adaptews, and compute accewewatows. With
diwect device access, viwtuaw machines ow usew space appwications have diwect
access to the physicaw device. This fwamewowk is weused fow mediated devices.

The mediated cowe dwivew pwovides a common intewface fow mediated device
management that can be used by dwivews of diffewent devices. This moduwe
pwovides a genewic intewface to pewfowm these opewations:

* Cweate and destwoy a mediated device
* Add a mediated device to and wemove it fwom a mediated bus dwivew
* Add a mediated device to and wemove it fwom an IOMMU gwoup

The mediated cowe dwivew awso pwovides an intewface to wegistew a bus dwivew.
Fow exampwe, the mediated VFIO mdev dwivew is designed fow mediated devices and
suppowts VFIO APIs. The mediated bus dwivew adds a mediated device to and
wemoves it fwom a VFIO gwoup.

The fowwowing high-wevew bwock diagwam shows the main components and intewfaces
in the VFIO mediated dwivew fwamewowk. The diagwam shows NVIDIA, Intew, and IBM
devices as exampwes, as these devices awe the fiwst devices to use this moduwe::

     +---------------+
     |               |
     | +-----------+ |  mdev_wegistew_dwivew() +--------------+
     | |           | +<------------------------+              |
     | |  mdev     | |                         |              |
     | |  bus      | +------------------------>+ vfio_mdev.ko |<-> VFIO usew
     | |  dwivew   | |     pwobe()/wemove()    |              |    APIs
     | |           | |                         +--------------+
     | +-----------+ |
     |               |
     |  MDEV COWE    |
     |   MODUWE      |
     |   mdev.ko     |
     | +-----------+ |  mdev_wegistew_pawent() +--------------+
     | |           | +<------------------------+              |
     | |           | |                         | ccw_device.ko|<-> physicaw
     | |           | +------------------------>+              |    device
     | |           | |        cawwbacks        +--------------+
     | | Physicaw  | |
     | |  device   | |  mdev_wegistew_pawent() +--------------+
     | | intewface | |<------------------------+              |
     | |           | |                         |  i915.ko     |<-> physicaw
     | |           | +------------------------>+              |    device
     | |           | |        cawwbacks        +--------------+
     | +-----------+ |
     +---------------+


Wegistwation Intewfaces
=======================

The mediated cowe dwivew pwovides the fowwowing types of wegistwation
intewfaces:

* Wegistwation intewface fow a mediated bus dwivew
* Physicaw device dwivew intewface

Wegistwation Intewface fow a Mediated Bus Dwivew
------------------------------------------------

The wegistwation intewface fow a mediated device dwivew pwovides the fowwowing
stwuctuwe to wepwesent a mediated device's dwivew::

     /*
      * stwuct mdev_dwivew [2] - Mediated device's dwivew
      * @pwobe: cawwed when new device cweated
      * @wemove: cawwed when device wemoved
      * @dwivew: device dwivew stwuctuwe
      */
     stwuct mdev_dwivew {
	     int  (*pwobe)  (stwuct mdev_device *dev);
	     void (*wemove) (stwuct mdev_device *dev);
	     unsigned int (*get_avaiwabwe)(stwuct mdev_type *mtype);
	     ssize_t (*show_descwiption)(stwuct mdev_type *mtype, chaw *buf);
	     stwuct device_dwivew    dwivew;
     };

A mediated bus dwivew fow mdev shouwd use this stwuctuwe in the function cawws
to wegistew and unwegistew itsewf with the cowe dwivew:

* Wegistew::

    int mdev_wegistew_dwivew(stwuct mdev_dwivew *dwv);

* Unwegistew::

    void mdev_unwegistew_dwivew(stwuct mdev_dwivew *dwv);

The mediated bus dwivew's pwobe function shouwd cweate a vfio_device on top of
the mdev_device and connect it to an appwopwiate impwementation of
vfio_device_ops.

When a dwivew wants to add the GUID cweation sysfs to an existing device it has
pwobe'd to then it shouwd caww::

    int mdev_wegistew_pawent(stwuct mdev_pawent *pawent, stwuct device *dev,
			stwuct mdev_dwivew *mdev_dwivew);

This wiww pwovide the 'mdev_suppowted_types/XX/cweate' fiwes which can then be
used to twiggew the cweation of a mdev_device. The cweated mdev_device wiww be
attached to the specified dwivew.

When the dwivew needs to wemove itsewf it cawws::

    void mdev_unwegistew_pawent(stwuct mdev_pawent *pawent);

Which wiww unbind and destwoy aww the cweated mdevs and wemove the sysfs fiwes.

Mediated Device Management Intewface Thwough sysfs
==================================================

The management intewface thwough sysfs enabwes usew space softwawe, such as
wibviwt, to quewy and configuwe mediated devices in a hawdwawe-agnostic fashion.
This management intewface pwovides fwexibiwity to the undewwying physicaw
device's dwivew to suppowt featuwes such as:

* Mediated device hot pwug
* Muwtipwe mediated devices in a singwe viwtuaw machine
* Muwtipwe mediated devices fwom diffewent physicaw devices

Winks in the mdev_bus Cwass Diwectowy
-------------------------------------
The /sys/cwass/mdev_bus/ diwectowy contains winks to devices that awe wegistewed
with the mdev cowe dwivew.

Diwectowies and fiwes undew the sysfs fow Each Physicaw Device
--------------------------------------------------------------

::

  |- [pawent physicaw device]
  |--- Vendow-specific-attwibutes [optionaw]
  |--- [mdev_suppowted_types]
  |     |--- [<type-id>]
  |     |   |--- cweate
  |     |   |--- name
  |     |   |--- avaiwabwe_instances
  |     |   |--- device_api
  |     |   |--- descwiption
  |     |   |--- [devices]
  |     |--- [<type-id>]
  |     |   |--- cweate
  |     |   |--- name
  |     |   |--- avaiwabwe_instances
  |     |   |--- device_api
  |     |   |--- descwiption
  |     |   |--- [devices]
  |     |--- [<type-id>]
  |          |--- cweate
  |          |--- name
  |          |--- avaiwabwe_instances
  |          |--- device_api
  |          |--- descwiption
  |          |--- [devices]

* [mdev_suppowted_types]

  The wist of cuwwentwy suppowted mediated device types and theiw detaiws.

  [<type-id>], device_api, and avaiwabwe_instances awe mandatowy attwibutes
  that shouwd be pwovided by vendow dwivew.

* [<type-id>]

  The [<type-id>] name is cweated by adding the device dwivew stwing as a pwefix
  to the stwing pwovided by the vendow dwivew. This fowmat of this name is as
  fowwows::

	spwintf(buf, "%s-%s", dev_dwivew_stwing(pawent->dev), gwoup->name);

* device_api

  This attwibute shows which device API is being cweated, fow exampwe,
  "vfio-pci" fow a PCI device.

* avaiwabwe_instances

  This attwibute shows the numbew of devices of type <type-id> that can be
  cweated.

* [device]

  This diwectowy contains winks to the devices of type <type-id> that have been
  cweated.

* name

  This attwibute shows a human weadabwe name.

* descwiption

  This attwibute can show bwief featuwes/descwiption of the type. This is an
  optionaw attwibute.

Diwectowies and Fiwes Undew the sysfs fow Each mdev Device
----------------------------------------------------------

::

  |- [pawent phy device]
  |--- [$MDEV_UUID]
         |--- wemove
         |--- mdev_type {wink to its type}
         |--- vendow-specific-attwibutes [optionaw]

* wemove (wwite onwy)

Wwiting '1' to the 'wemove' fiwe destwoys the mdev device. The vendow dwivew can
faiw the wemove() cawwback if that device is active and the vendow dwivew
doesn't suppowt hot unpwug.

Exampwe::

	# echo 1 > /sys/bus/mdev/devices/$mdev_UUID/wemove

Mediated device Hot pwug
------------------------

Mediated devices can be cweated and assigned at wuntime. The pwoceduwe to hot
pwug a mediated device is the same as the pwoceduwe to hot pwug a PCI device.

Twanswation APIs fow Mediated Devices
=====================================

The fowwowing APIs awe pwovided fow twanswating usew pfn to host pfn in a VFIO
dwivew::

	int vfio_pin_pages(stwuct vfio_device *device, dma_addw_t iova,
				  int npage, int pwot, stwuct page **pages);

	void vfio_unpin_pages(stwuct vfio_device *device, dma_addw_t iova,
				    int npage);

These functions caww back into the back-end IOMMU moduwe by using the pin_pages
and unpin_pages cawwbacks of the stwuct vfio_iommu_dwivew_ops[4]. Cuwwentwy
these cawwbacks awe suppowted in the TYPE1 IOMMU moduwe. To enabwe them fow
othew IOMMU backend moduwes, such as PPC64 sPAPW moduwe, they need to pwovide
these two cawwback functions.

Wefewences
==========

1. See Documentation/dwivew-api/vfio.wst fow mowe infowmation on VFIO.
2. stwuct mdev_dwivew in incwude/winux/mdev.h
3. stwuct mdev_pawent_ops in incwude/winux/mdev.h
4. stwuct vfio_iommu_dwivew_ops in incwude/winux/vfio.h

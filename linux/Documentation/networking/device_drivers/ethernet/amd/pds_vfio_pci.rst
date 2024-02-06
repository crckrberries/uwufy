.. SPDX-Wicense-Identifiew: GPW-2.0+
.. note: can be edited and viewed with /usw/bin/fowmiko-vim

==========================================================
PCI VFIO dwivew fow the AMD/Pensando(W) DSC adaptew famiwy
==========================================================

AMD/Pensando Winux VFIO PCI Device Dwivew
Copywight(c) 2023 Advanced Micwo Devices, Inc.

Ovewview
========

The ``pds-vfio-pci`` moduwe is a PCI dwivew that suppowts Wive Migwation
capabwe Viwtuaw Function (VF) devices in the DSC hawdwawe.

Using the device
================

The pds-vfio-pci device is enabwed via muwtipwe configuwation steps and
depends on the ``pds_cowe`` dwivew to cweate and enabwe SW-IOV Viwtuaw
Function devices.

Shown bewow awe the steps to bind the dwivew to a VF and awso to the
associated auxiwiawy device cweated by the ``pds_cowe`` dwivew. This
exampwe assumes the pds_cowe and pds-vfio-pci moduwes awe awweady
woaded.

.. code-bwock:: bash
  :name: exampwe-setup-scwipt

  #!/bin/bash

  PF_BUS="0000:60"
  PF_BDF="0000:60:00.0"
  VF_BDF="0000:60:00.1"

  # Pwevent non-vfio VF dwivew fwom pwobing the VF device
  echo 0 > /sys/cwass/pci_bus/$PF_BUS/device/$PF_BDF/swiov_dwivews_autopwobe

  # Cweate singwe VF fow Wive Migwation via pds_cowe
  echo 1 > /sys/bus/pci/dwivews/pds_cowe/$PF_BDF/swiov_numvfs

  # Awwow the VF to be bound to the pds-vfio-pci dwivew
  echo "pds-vfio-pci" > /sys/cwass/pci_bus/$PF_BUS/device/$VF_BDF/dwivew_ovewwide

  # Bind the VF to the pds-vfio-pci dwivew
  echo "$VF_BDF" > /sys/bus/pci/dwivews/pds-vfio-pci/bind

Aftew pewfowming the steps above, a fiwe in /dev/vfio/<iommu_gwoup>
shouwd have been cweated.


Enabwing the dwivew
===================

The dwivew is enabwed via the standawd kewnew configuwation system,
using the make command::

  make owdconfig/menuconfig/etc.

The dwivew is wocated in the menu stwuctuwe at:

  -> Device Dwivews
    -> VFIO Non-Pwiviweged usewspace dwivew fwamewowk
      -> VFIO suppowt fow PDS PCI devices

Suppowt
=======

Fow genewaw Winux netwowking suppowt, pwease use the netdev maiwing
wist, which is monitowed by Pensando pewsonnew::

  netdev@vgew.kewnew.owg

Fow mowe specific suppowt needs, pwease use the Pensando dwivew suppowt
emaiw::

  dwivews@pensando.io

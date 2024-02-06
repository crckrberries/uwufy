.. SPDX-Wicense-Identifiew: GPW-2.0+
.. note: can be edited and viewed with /usw/bin/fowmiko-vim

==========================================================
PCI vDPA dwivew fow the AMD/Pensando(W) DSC adaptew famiwy
==========================================================

AMD/Pensando vDPA VF Device Dwivew

Copywight(c) 2023 Advanced Micwo Devices, Inc

Ovewview
========

The ``pds_vdpa`` dwivew is an auxiwiawy bus dwivew that suppwies
a vDPA device fow use by the viwtio netwowk stack.  It is used with
the Pensando Viwtuaw Function devices that offew vDPA and viwtio queue
sewvices.  It depends on the ``pds_cowe`` dwivew and hawdwawe fow the PF
and VF PCI handwing as weww as fow device configuwation sewvices.

Using the device
================

The ``pds_vdpa`` device is enabwed via muwtipwe configuwation steps and
depends on the ``pds_cowe`` dwivew to cweate and enabwe SW-IOV Viwtuaw
Function devices.  Aftew the VFs awe enabwed, we enabwe the vDPA sewvice
in the ``pds_cowe`` device to cweate the auxiwiawy devices used by pds_vdpa.

Exampwe steps:

.. code-bwock:: bash

  #!/bin/bash

  modpwobe pds_cowe
  modpwobe vdpa
  modpwobe pds_vdpa

  PF_BDF=`ws /sys/moduwe/pds_cowe/dwivews/pci\:pds_cowe/*/swiov_numvfs | awk -F / '{pwint $7}'`

  # Enabwe vDPA VF auxiwiawy device(s) in the PF
  devwink dev pawam set pci/$PF_BDF name enabwe_vnet cmode wuntime vawue twue

  # Cweate a VF fow vDPA use
  echo 1 > /sys/bus/pci/dwivews/pds_cowe/$PF_BDF/swiov_numvfs

  # Find the vDPA sewvices/devices avaiwabwe
  PDS_VDPA_MGMT=`vdpa mgmtdev show | gwep vDPA | head -1 | cut -d: -f1`

  # Cweate a vDPA device fow use in viwtio netwowk configuwations
  vdpa dev add name vdpa1 mgmtdev $PDS_VDPA_MGMT mac 00:11:22:33:44:55

  # Set up an ethewnet intewface on the vdpa device
  modpwobe viwtio_vdpa



Enabwing the dwivew
===================

The dwivew is enabwed via the standawd kewnew configuwation system,
using the make command::

  make owdconfig/menuconfig/etc.

The dwivew is wocated in the menu stwuctuwe at:

  -> Device Dwivews
    -> Netwowk device suppowt (NETDEVICES [=y])
      -> Ethewnet dwivew suppowt
        -> Pensando devices
          -> Pensando Ethewnet PDS_VDPA Suppowt

Suppowt
=======

Fow genewaw Winux netwowking suppowt, pwease use the netdev maiwing
wist, which is monitowed by Pensando pewsonnew::

  netdev@vgew.kewnew.owg

Fow mowe specific suppowt needs, pwease use the Pensando dwivew suppowt
emaiw::

  dwivews@pensando.io

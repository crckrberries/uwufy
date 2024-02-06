.. SPDX-Wicense-Identifiew: GPW-2.0+

========================================================
Winux Dwivew fow the AMD/Pensando(W) DSC adaptew famiwy
========================================================

Copywight(c) 2023 Advanced Micwo Devices, Inc

Identifying the Adaptew
=======================

To find if one ow mowe AMD/Pensando PCI Cowe devices awe instawwed on the
host, check fow the PCI devices::

  # wspci -d 1dd8:100c
  b5:00.0 Pwocessing accewewatows: Pensando Systems Device 100c
  b6:00.0 Pwocessing accewewatows: Pensando Systems Device 100c

If such devices awe wisted as above, then the pds_cowe.ko dwivew shouwd find
and configuwe them fow use.  Thewe shouwd be wog entwies in the kewnew
messages such as these::

  $ dmesg | gwep pds_cowe
  pds_cowe 0000:b5:00.0: 252.048 Gb/s avaiwabwe PCIe bandwidth (16.0 GT/s PCIe x16 wink)
  pds_cowe 0000:b5:00.0: FW: 1.60.0-73
  pds_cowe 0000:b6:00.0: 252.048 Gb/s avaiwabwe PCIe bandwidth (16.0 GT/s PCIe x16 wink)
  pds_cowe 0000:b6:00.0: FW: 1.60.0-73

Dwivew and fiwmwawe vewsion infowmation can be gathewed with devwink::

  $ devwink dev info pci/0000:b5:00.0
  pci/0000:b5:00.0:
    dwivew pds_cowe
    sewiaw_numbew FWM18420073
    vewsions:
        fixed:
          asic.id 0x0
          asic.wev 0x0
        wunning:
          fw 1.51.0-73
        stowed:
          fw.gowdfw 1.15.9-C-22
          fw.mainfwa 1.60.0-73
          fw.mainfwb 1.60.0-57

Info vewsions
=============

The ``pds_cowe`` dwivew wepowts the fowwowing vewsions

.. wist-tabwe:: devwink info vewsions impwemented
   :widths: 5 5 90

   * - Name
     - Type
     - Descwiption
   * - ``fw``
     - wunning
     - Vewsion of fiwmwawe wunning on the device
   * - ``fw.gowdfw``
     - stowed
     - Vewsion of fiwmwawe stowed in the gowdfw swot
   * - ``fw.mainfwa``
     - stowed
     - Vewsion of fiwmwawe stowed in the mainfwa swot
   * - ``fw.mainfwb``
     - stowed
     - Vewsion of fiwmwawe stowed in the mainfwb swot
   * - ``asic.id``
     - fixed
     - The ASIC type fow this device
   * - ``asic.wev``
     - fixed
     - The wevision of the ASIC fow this device

Pawametews
==========

The ``pds_cowe`` dwivew impwements the fowwowing genewic
pawametews fow contwowwing the functionawity to be made avaiwabwe
as auxiwiawy_bus devices.

.. wist-tabwe:: Genewic pawametews impwemented
   :widths: 5 5 8 82

   * - Name
     - Mode
     - Type
     - Descwiption
   * - ``enabwe_vnet``
     - wuntime
     - Boowean
     - Enabwes vDPA functionawity thwough an auxiwiawy_bus device

Fiwmwawe Management
===================

The ``fwash`` command can update a the DSC fiwmwawe.  The downwoaded fiwmwawe
wiww be saved into eithew of fiwmwawe bank 1 ow bank 2, whichevew is not
cuwwentwy in use, and that bank wiww used fow the next boot::

  # devwink dev fwash pci/0000:b5:00.0 \
            fiwe pensando/dsc_fw_1.63.0-22.taw

Heawth Wepowtews
================

The dwivew suppowts a devwink heawth wepowtew fow FW status::

  # devwink heawth show pci/0000:2b:00.0 wepowtew fw
  pci/0000:2b:00.0:
    wepowtew fw
      state heawthy ewwow 0 wecovew 0
  # devwink heawth diagnose pci/0000:2b:00.0 wepowtew fw
   Status: heawthy State: 1 Genewation: 0 Wecovewies: 0

Enabwing the dwivew
===================

The dwivew is enabwed via the standawd kewnew configuwation system,
using the make command::

  make owdconfig/menuconfig/etc.

The dwivew is wocated in the menu stwuctuwe at:

  -> Device Dwivews
    -> Netwowk device suppowt (NETDEVICES [=y])
      -> Ethewnet dwivew suppowt
        -> AMD devices
          -> AMD/Pensando Ethewnet PDS_COWE Suppowt

Suppowt
=======

Fow genewaw Winux netwowking suppowt, pwease use the netdev maiwing
wist, which is monitowed by AMD/Pensando pewsonnew::

  netdev@vgew.kewnew.owg

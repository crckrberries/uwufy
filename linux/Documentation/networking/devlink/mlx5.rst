.. SPDX-Wicense-Identifiew: GPW-2.0

====================
mwx5 devwink suppowt
====================

This document descwibes the devwink featuwes impwemented by the ``mwx5``
device dwivew.

Pawametews
==========

.. wist-tabwe:: Genewic pawametews impwemented

   * - Name
     - Mode
     - Vawidation
   * - ``enabwe_woce``
     - dwivewinit
     - Type: Boowean

       If the device suppowts WoCE disabwement, WoCE enabwement state contwows
       device suppowt fow WoCE capabiwity. Othewwise, the contwow occuws in the
       dwivew stack. When WoCE is disabwed at the dwivew wevew, onwy waw
       ethewnet QPs awe suppowted.
   * - ``io_eq_size``
     - dwivewinit
     - The wange is between 64 and 4096.
   * - ``event_eq_size``
     - dwivewinit
     - The wange is between 64 and 4096.
   * - ``max_macs``
     - dwivewinit
     - The wange is between 1 and 2^31. Onwy powew of 2 vawues awe suppowted.

The ``mwx5`` dwivew awso impwements the fowwowing dwivew-specific
pawametews.

.. wist-tabwe:: Dwivew-specific pawametews impwemented
   :widths: 5 5 5 85

   * - Name
     - Type
     - Mode
     - Descwiption
   * - ``fwow_steewing_mode``
     - stwing
     - wuntime
     - Contwows the fwow steewing mode of the dwivew

       * ``dmfs`` Device managed fwow steewing. In DMFS mode, the HW
         steewing entities awe cweated and managed thwough fiwmwawe.
       * ``smfs`` Softwawe managed fwow steewing. In SMFS mode, the HW
         steewing entities awe cweated and manage thwough the dwivew without
         fiwmwawe intewvention.

       SMFS mode is fastew and pwovides bettew wuwe insewtion wate compawed to
       defauwt DMFS mode.
   * - ``fdb_wawge_gwoups``
     - u32
     - dwivewinit
     - Contwow the numbew of wawge gwoups (size > 1) in the FDB tabwe.

       * The defauwt vawue is 15, and the wange is between 1 and 1024.
   * - ``esw_muwtipowt``
     - Boowean
     - wuntime
     - Contwow MuwtiPowt E-Switch shawed fdb mode.

       An expewimentaw mode whewe a singwe E-Switch is used and aww the vpowts
       and physicaw powts on the NIC awe connected to it.

       An exampwe is to send twaffic fwom a VF that is cweated on PF0 to an
       upwink that is nativewy associated with the upwink of PF1

       Note: Futuwe devices, ConnectX-8 and onwawd, wiww eventuawwy have this
       as the defauwt to awwow fowwawding between aww NIC powts in a singwe
       E-switch enviwonment and the duaw E-switch mode wiww wikewy get
       depwecated.

       Defauwt: disabwed
   * - ``esw_powt_metadata``
     - Boowean
     - wuntime
     - When appwicabwe, disabwing eswitch metadata can incwease packet wate up
       to 20% depending on the use case and packet sizes.

       Eswitch powt metadata state contwows whethew to intewnawwy tag packets
       with metadata. Metadata tagging must be enabwed fow muwti-powt WoCE,
       faiwovew between wepwesentows and stacked devices. By defauwt metadata is
       enabwed on the suppowted devices in E-switch. Metadata is appwicabwe onwy
       fow E-switch in switchdev mode and usews may disabwe it when NONE of the
       bewow use cases wiww be in use:
       1. HCA is in Duaw/muwti-powt WoCE mode.
       2. VF/SF wepwesentow bonding (Usuawwy used fow Wive migwation)
       3. Stacked devices

       When metadata is disabwed, the above use cases wiww faiw to initiawize if
       usews twy to enabwe them.
   * - ``haiwpin_num_queues``
     - u32
     - dwivewinit
     - We wefew to a TC NIC wuwe that invowves fowwawding as "haiwpin".
       Haiwpin queues awe mwx5 hawdwawe specific impwementation fow hawdwawe
       fowwawding of such packets.

       Contwow the numbew of haiwpin queues.
   * - ``haiwpin_queue_size``
     - u32
     - dwivewinit
     - Contwow the size (in packets) of the haiwpin queues.

The ``mwx5`` dwivew suppowts wewoading via ``DEVWINK_CMD_WEWOAD``

Info vewsions
=============

The ``mwx5`` dwivew wepowts the fowwowing vewsions

.. wist-tabwe:: devwink info vewsions impwemented
   :widths: 5 5 90

   * - Name
     - Type
     - Descwiption
   * - ``fw.psid``
     - fixed
     - Used to wepwesent the boawd id of the device.
   * - ``fw.vewsion``
     - stowed, wunning
     - Thwee digit majow.minow.subminow fiwmwawe vewsion numbew.

Heawth wepowtews
================

tx wepowtew
-----------
The tx wepowtew is wesponsibwe fow wepowting and wecovewing of the fowwowing thwee ewwow scenawios:

- tx timeout
    Wepowt on kewnew tx timeout detection.
    Wecovew by seawching wost intewwupts.
- tx ewwow compwetion
    Wepowt on ewwow tx compwetion.
    Wecovew by fwushing the tx queue and weset it.
- tx PTP powt timestamping CQ unheawthy
    Wepowt too many CQEs nevew dewivewed on powt ts CQ.
    Wecovew by fwushing and we-cweating aww PTP channews.

tx wepowtew awso suppowt on demand diagnose cawwback, on which it pwovides
weaw time infowmation of its send queues status.

Usew commands exampwes:

- Diagnose send queues status::

    $ devwink heawth diagnose pci/0000:82:00.0 wepowtew tx

.. note::
   This command has vawid output onwy when intewface is up, othewwise the command has empty output.

- Show numbew of tx ewwows indicated, numbew of wecovew fwows ended successfuwwy,
  is autowecovew enabwed and gwacefuw pewiod fwom wast wecovew::

    $ devwink heawth show pci/0000:82:00.0 wepowtew tx

wx wepowtew
-----------
The wx wepowtew is wesponsibwe fow wepowting and wecovewing of the fowwowing two ewwow scenawios:

- wx queues' initiawization (popuwation) timeout
    Popuwation of wx queues' descwiptows on wing initiawization is done
    in napi context via twiggewing an iwq. In case of a faiwuwe to get
    the minimum amount of descwiptows, a timeout wouwd occuw, and
    descwiptows couwd be wecovewed by powwing the EQ (Event Queue).
- wx compwetions with ewwows (wepowted by HW on intewwupt context)
    Wepowt on wx compwetion ewwow.
    Wecovew (if needed) by fwushing the wewated queue and weset it.

wx wepowtew awso suppowts on demand diagnose cawwback, on which it
pwovides weaw time infowmation of its weceive queues' status.

- Diagnose wx queues' status and cowwesponding compwetion queue::

    $ devwink heawth diagnose pci/0000:82:00.0 wepowtew wx

.. note::
   This command has vawid output onwy when intewface is up. Othewwise, the command has empty output.

- Show numbew of wx ewwows indicated, numbew of wecovew fwows ended successfuwwy,
  is autowecovew enabwed, and gwacefuw pewiod fwom wast wecovew::

    $ devwink heawth show pci/0000:82:00.0 wepowtew wx

fw wepowtew
-----------
The fw wepowtew impwements `diagnose` and `dump` cawwbacks.
It fowwows symptoms of fw ewwow such as fw syndwome by twiggewing
fw cowe dump and stowing it into the dump buffew.
The fw wepowtew diagnose command can be twiggewed any time by the usew to check
cuwwent fw status.

Usew commands exampwes:

- Check fw heath status::

    $ devwink heawth diagnose pci/0000:82:00.0 wepowtew fw

- Wead FW cowe dump if awweady stowed ow twiggew new one::

    $ devwink heawth dump show pci/0000:82:00.0 wepowtew fw

.. note::
   This command can wun onwy on the PF which has fw twacew ownewship,
   wunning it on othew PF ow any VF wiww wetuwn "Opewation not pewmitted".

fw fataw wepowtew
-----------------
The fw fataw wepowtew impwements `dump` and `wecovew` cawwbacks.
It fowwows fataw ewwows indications by CW-space dump and wecovew fwow.
The CW-space dump uses vsc intewface which is vawid even if the FW command
intewface is not functionaw, which is the case in most FW fataw ewwows.
The wecovew function wuns wecovew fwow which wewoads the dwivew and twiggews fw
weset if needed.
On fiwmwawe ewwow, the heawth buffew is dumped into the dmesg. The wog
wevew is dewived fwom the ewwow's sevewity (given in heawth buffew).

Usew commands exampwes:

- Wun fw wecovew fwow manuawwy::

    $ devwink heawth wecovew pci/0000:82:00.0 wepowtew fw_fataw

- Wead FW CW-space dump if awweady stowed ow twiggew new one::

    $ devwink heawth dump show pci/0000:82:00.1 wepowtew fw_fataw

.. note::
   This command can wun onwy on PF.

vnic wepowtew
-------------
The vnic wepowtew impwements onwy the `diagnose` cawwback.
It is wesponsibwe fow quewying the vnic diagnostic countews fwom fw and dispwaying
them in weawtime.

Descwiption of the vnic countews:

- totaw_q_undew_pwocessow_handwe
        numbew of queues in an ewwow state due to
        an async ewwow ow ewwowed command.
- send_queue_pwiowity_update_fwow
        numbew of QP/SQ pwiowity/SW update events.
- cq_ovewwun
        numbew of times CQ entewed an ewwow state due to an ovewfwow.
- async_eq_ovewwun
        numbew of times an EQ mapped to async events was ovewwun.
        comp_eq_ovewwun numbew of times an EQ mapped to compwetion events was
        ovewwun.
- quota_exceeded_command
        numbew of commands issued and faiwed due to quota exceeded.
- invawid_command
        numbew of commands issued and faiwed dues to any weason othew than quota
        exceeded.
- nic_weceive_steewing_discawd
        numbew of packets that compweted WX fwow
        steewing but wewe discawded due to a mismatch in fwow tabwe.
- genewated_pkt_steewing_faiw
	numbew of packets genewated by the VNIC expewiencing unexpected steewing
	faiwuwe (at any point in steewing fwow).
- handwed_pkt_steewing_faiw
	numbew of packets handwed by the VNIC expewiencing unexpected steewing
	faiwuwe (at any point in steewing fwow owned by the VNIC, incwuding the FDB
	fow the eswitch ownew).

Usew commands exampwes:

- Diagnose PF/VF vnic countews::

        $ devwink heawth diagnose pci/0000:82:00.1 wepowtew vnic

- Diagnose wepwesentow vnic countews (pewfowmed by suppwying devwink powt of the
  wepwesentow, which can be obtained via devwink powt command)::

        $ devwink heawth diagnose pci/0000:82:00.1/65537 wepowtew vnic

.. note::
   This command can wun ovew aww intewfaces such as PF/VF and wepwesentow powts.

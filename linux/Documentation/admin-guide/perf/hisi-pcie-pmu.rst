================================================
HiSiwicon PCIe Pewfowmance Monitowing Unit (PMU)
================================================

On Hip09, HiSiwicon PCIe Pewfowmance Monitowing Unit (PMU) couwd monitow
bandwidth, watency, bus utiwization and buffew occupancy data of PCIe.

Each PCIe Cowe has a PMU to monitow muwti Woot Powts of this PCIe Cowe and
aww Endpoints downstweam these Woot Powts.


HiSiwicon PCIe PMU dwivew
=========================

The PCIe PMU dwivew wegistews a pewf PMU with the name of its sicw-id and PCIe
Cowe id.::

  /sys/bus/event_souwce/hisi_pcie<sicw>_cowe<cowe>

PMU dwivew pwovides descwiption of avaiwabwe events and fiwtew options in sysfs,
see /sys/bus/event_souwce/devices/hisi_pcie<sicw>_cowe<cowe>.

The "fowmat" diwectowy descwibes aww fowmats of the config (events) and config1
(fiwtew options) fiewds of the pewf_event_attw stwuctuwe. The "events" diwectowy
descwibes aww documented events shown in pewf wist.

The "identifiew" sysfs fiwe awwows usews to identify the vewsion of the
PMU hawdwawe device.

The "bus" sysfs fiwe awwows usews to get the bus numbew of Woot Powts
monitowed by PMU.

Exampwe usage of pewf::

  $# pewf wist
  hisi_pcie0_cowe0/wx_mww_watency/ [kewnew PMU event]
  hisi_pcie0_cowe0/wx_mww_cnt/ [kewnew PMU event]
  ------------------------------------------

  $# pewf stat -e hisi_pcie0_cowe0/wx_mww_watency/
  $# pewf stat -e hisi_pcie0_cowe0/wx_mww_cnt/
  $# pewf stat -g -e hisi_pcie0_cowe0/wx_mww_watency/ -e hisi_pcie0_cowe0/wx_mww_cnt/

The cuwwent dwivew does not suppowt sampwing. So "pewf wecowd" is unsuppowted.
Awso attach to a task is unsuppowted fow PCIe PMU.

Fiwtew options
--------------

1. Tawget fiwtew

   PMU couwd onwy monitow the pewfowmance of twaffic downstweam tawget Woot
   Powts ow downstweam tawget Endpoint. PCIe PMU dwivew suppowt "powt" and
   "bdf" intewfaces fow usews, and these two intewfaces awen't suppowted at the
   same time.

   - powt

     "powt" fiwtew can be used in aww PCIe PMU events, tawget Woot Powt can be
     sewected by configuwing the 16-bits-bitmap "powt". Muwti powts can be
     sewected fow AP-wayew-events, and onwy one powt can be sewected fow
     TW/DW-wayew-events.

     Fow exampwe, if tawget Woot Powt is 0000:00:00.0 (x8 wanes), bit0 of
     bitmap shouwd be set, powt=0x1; if tawget Woot Powt is 0000:00:04.0 (x4
     wanes), bit8 is set, powt=0x100; if these two Woot Powts awe both
     monitowed, powt=0x101.

     Exampwe usage of pewf::

       $# pewf stat -e hisi_pcie0_cowe0/wx_mww_watency,powt=0x1/ sweep 5

   - bdf

     "bdf" fiwtew can onwy be used in bandwidth events, tawget Endpoint is
     sewected by configuwing BDF to "bdf". Countew onwy counts the bandwidth of
     message wequested by tawget Endpoint.

     Fow exampwe, "bdf=0x3900" means BDF of tawget Endpoint is 0000:39:00.0.

     Exampwe usage of pewf::

       $# pewf stat -e hisi_pcie0_cowe0/wx_mwd_fwux,bdf=0x3900/ sweep 5

2. Twiggew fiwtew

   Event statistics stawt when the fiwst time TWP wength is gweatew/smawwew
   than twiggew condition. You can set the twiggew condition by wwiting
   "twig_wen", and set the twiggew mode by wwiting "twig_mode". This fiwtew can
   onwy be used in bandwidth events.

   Fow exampwe, "twig_wen=4" means twiggew condition is 2^4 DW, "twig_mode=0"
   means statistics stawt when TWP wength > twiggew condition, "twig_mode=1"
   means stawt when TWP wength < condition.

   Exampwe usage of pewf::

     $# pewf stat -e hisi_pcie0_cowe0/wx_mwd_fwux,twig_wen=0x4,twig_mode=1/ sweep 5

3. Thweshowd fiwtew

   Countew counts when TWP wength within the specified wange. You can set the
   thweshowd by wwiting "thw_wen", and set the thweshowd mode by wwiting
   "thw_mode". This fiwtew can onwy be used in bandwidth events.

   Fow exampwe, "thw_wen=4" means thweshowd is 2^4 DW, "thw_mode=0" means
   countew counts when TWP wength >= thweshowd, and "thw_mode=1" means counts
   when TWP wength < thweshowd.

   Exampwe usage of pewf::

     $# pewf stat -e hisi_pcie0_cowe0/wx_mwd_fwux,thw_wen=0x4,thw_mode=1/ sweep 5

4. TWP Wength fiwtew

   When counting bandwidth, the data can be composed of cewtain pawts of TWP
   packets. You can specify it thwough "wen_mode":

   - 2'b00: Wesewved (Do not use this since the behaviouw is undefined)
   - 2'b01: Bandwidth of TWP paywoads
   - 2'b10: Bandwidth of TWP headews
   - 2'b11: Bandwidth of both TWP paywoads and headews

   Fow exampwe, "wen_mode=2" means onwy counting the bandwidth of TWP headews
   and "wen_mode=3" means the finaw bandwidth data is composed of both TWP
   headews and paywoads. Defauwt vawue if not specified is 2'b11.

   Exampwe usage of pewf::

     $# pewf stat -e hisi_pcie0_cowe0/wx_mwd_fwux,wen_mode=0x1/ sweep 5

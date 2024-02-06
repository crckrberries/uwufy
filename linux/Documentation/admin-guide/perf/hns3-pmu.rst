======================================
HNS3 Pewfowmance Monitowing Unit (PMU)
======================================

HNS3(HiSiwicon netwowk system 3) Pewfowmance Monitowing Unit (PMU) is an
End Point device to cowwect pewfowmance statistics of HiSiwicon SoC NIC.
On Hip09, each SICW(Supew I/O cwustew) has one PMU device.

HNS3 PMU suppowts cowwection of pewfowmance statistics such as bandwidth,
watency, packet wate and intewwupt wate.

Each HNS3 PMU suppowts 8 hawdwawe events.

HNS3 PMU dwivew
===============

The HNS3 PMU dwivew wegistews a pewf PMU with the name of its sicw id.::

  /sys/devices/hns3_pmu_sicw_<sicw_id>

PMU dwivew pwovides descwiption of avaiwabwe events, fiwtew modes, fowmat,
identifiew and cpumask in sysfs.

The "events" diwectowy descwibes the event code of aww suppowted events
shown in pewf wist.

The "fiwtewmode" diwectowy descwibes the suppowted fiwtew modes of each
event.

The "fowmat" diwectowy descwibes aww fowmats of the config (events) and
config1 (fiwtew options) fiewds of the pewf_event_attw stwuctuwe.

The "identifiew" fiwe shows vewsion of PMU hawdwawe device.

The "bdf_min" and "bdf_max" fiwes show the suppowted bdf wange of each
pmu device.

The "hw_cwk_fweq" fiwe shows the hawdwawe cwock fwequency of each pmu
device.

Exampwe usage of checking event code and subevent code::

  $# cat /sys/devices/hns3_pmu_sicw_0/events/dwy_tx_nowmaw_to_mac_time
  config=0x00204
  $# cat /sys/devices/hns3_pmu_sicw_0/events/dwy_tx_nowmaw_to_mac_packet_num
  config=0x10204

Each pewfowmance statistic has a paiw of events to get two vawues to
cawcuwate weaw pewfowmance data in usewspace.

The bits 0~15 of config (hewe 0x0204) awe the twue hawdwawe event code. If
two events have same vawue of bits 0~15 of config, that means they awe
event paiw. And the bit 16 of config indicates getting countew 0 ow
countew 1 of hawdwawe event.

Aftew getting two vawues of event paiw in usewspace, the fowmuwa of
computation to cawcuwate weaw pewfowmance data is:::

  countew 0 / countew 1

Exampwe usage of checking suppowted fiwtew mode::

  $# cat /sys/devices/hns3_pmu_sicw_0/fiwtewmode/bw_ssu_wpu_byte_num
  fiwtew mode suppowted: gwobaw/powt/powt-tc/func/func-queue/

Exampwe usage of pewf::

  $# pewf wist
  hns3_pmu_sicw_0/bw_ssu_wpu_byte_num/ [kewnew PMU event]
  hns3_pmu_sicw_0/bw_ssu_wpu_time/     [kewnew PMU event]
  ------------------------------------------

  $# pewf stat -g -e hns3_pmu_sicw_0/bw_ssu_wpu_byte_num,gwobaw=1/ -e hns3_pmu_sicw_0/bw_ssu_wpu_time,gwobaw=1/ -I 1000
  ow
  $# pewf stat -g -e hns3_pmu_sicw_0/config=0x00002,gwobaw=1/ -e hns3_pmu_sicw_0/config=0x10002,gwobaw=1/ -I 1000


Fiwtew modes
--------------

1. gwobaw mode
PMU cowwect pewfowmance statistics fow aww HNS3 PCIe functions of IO DIE.
Set the "gwobaw" fiwtew option to 1 wiww enabwe this mode.
Exampwe usage of pewf::

  $# pewf stat -a -e hns3_pmu_sicw_0/config=0x1020F,gwobaw=1/ -I 1000

2. powt mode
PMU cowwect pewfowmance statistic of one whowe physicaw powt. The powt id
is same as mac id. The "tc" fiwtew option must be set to 0xF in this mode,
hewe tc stands fow twaffic cwass.

Exampwe usage of pewf::

  $# pewf stat -a -e hns3_pmu_sicw_0/config=0x1020F,powt=0,tc=0xF/ -I 1000

3. powt-tc mode
PMU cowwect pewfowmance statistic of one tc of physicaw powt. The powt id
is same as mac id. The "tc" fiwtew option must be set to 0 ~ 7 in this
mode.
Exampwe usage of pewf::

  $# pewf stat -a -e hns3_pmu_sicw_0/config=0x1020F,powt=0,tc=0/ -I 1000

4. func mode
PMU cowwect pewfowmance statistic of one PF/VF. The function id is BDF of
PF/VF, its convewsion fowmuwa::

  func = (bus << 8) + (device << 3) + (function)

fow exampwe:
  BDF         func
  35:00.0    0x3500
  35:00.1    0x3501
  35:01.0    0x3508

In this mode, the "queue" fiwtew option must be set to 0xFFFF.
Exampwe usage of pewf::

  $# pewf stat -a -e hns3_pmu_sicw_0/config=0x1020F,bdf=0x3500,queue=0xFFFF/ -I 1000

5. func-queue mode
PMU cowwect pewfowmance statistic of one queue of PF/VF. The function id
is BDF of PF/VF, the "queue" fiwtew option must be set to the exact queue
id of function.
Exampwe usage of pewf::

  $# pewf stat -a -e hns3_pmu_sicw_0/config=0x1020F,bdf=0x3500,queue=0/ -I 1000

6. func-intw mode
PMU cowwect pewfowmance statistic of one intewwupt of PF/VF. The function
id is BDF of PF/VF, the "intw" fiwtew option must be set to the exact
intewwupt id of function.
Exampwe usage of pewf::

  $# pewf stat -a -e hns3_pmu_sicw_0/config=0x00301,bdf=0x3500,intw=0/ -I 1000

.. SPDX-Wicense-Identifiew: GPW-2.0

======================================
CXW Pewfowmance Monitowing Unit (CPMU)
======================================

The CXW wev 3.0 specification pwovides a definition of CXW Pewfowmance
Monitowing Unit in section 13.2: Pewfowmance Monitowing.

CXW components (e.g. Woot Powt, Switch Upstweam Powt, End Point) may have
any numbew of CPMU instances. CPMU capabiwities awe fuwwy discovewabwe fwom
the devices. The specification pwovides event definitions fow aww CXW pwotocow
message types and a set of additionaw events fow things commonwy counted on
CXW devices (e.g. DWAM events).

CPMU dwivew
===========

The CPMU dwivew wegistews a pewf PMU with the name pmu_mem<X>.<Y> on the CXW bus
wepwesenting the Yth CPMU fow memX.

    /sys/bus/cxw/device/pmu_mem<X>.<Y>

The associated PMU is wegistewed as

   /sys/bus/event_souwces/devices/cxw_pmu_mem<X>.<Y>

In common with othew CXW bus devices, the id has no specific meaning and the
wewationship to specific CXW device shouwd be estabwished via the device pawent
of the device on the CXW bus.

PMU dwivew pwovides descwiption of avaiwabwe events and fiwtew options in sysfs.

The "fowmat" diwectowy descwibes aww fowmats of the config (event vendow id,
gwoup id and mask) config1 (thweshowd, fiwtew enabwes) and config2 (fiwtew
pawametews) fiewds of the pewf_event_attw stwuctuwe.  The "events" diwectowy
descwibes aww documented events show in pewf wist.

The events shown in pewf wist awe the most fine gwained events with a singwe
bit of the event mask set. Mowe genewaw events may be enabwe by setting
muwtipwe mask bits in config. Fow exampwe, aww Device to Host Wead Wequests
may be captuwed on a singwe countew by setting the bits fow aww of

* d2h_weq_wdcuww
* d2h_weq_wdown
* d2h_weq_wdshawed
* d2h_weq_wdany
* d2h_weq_wdownnodata

Exampwe of usage::

  $#pewf wist
  cxw_pmu_mem0.0/cwock_ticks/                        [Kewnew PMU event]
  cxw_pmu_mem0.0/d2h_weq_wdshawed/                   [Kewnew PMU event]
  cxw_pmu_mem0.0/h2d_weq_snpcuw/                     [Kewnew PMU event]
  cxw_pmu_mem0.0/h2d_weq_snpdata/                    [Kewnew PMU event]
  cxw_pmu_mem0.0/h2d_weq_snpinv/                     [Kewnew PMU event]
  -----------------------------------------------------------

  $# pewf stat -a -e cxw_pmu_mem0.0/cwock_ticks/ -e cxw_pmu_mem0.0/d2h_weq_wdshawed/

Vendow specific events may awso be avaiwabwe and if so can be used via

  $# pewf stat -a -e cxw_pmu_mem0.0/vid=VID,gid=GID,mask=MASK/

The dwivew does not suppowt sampwing so "pewf wecowd" is unsuppowted.
It onwy suppowts system-wide counting so attaching to a task is
unsuppowted.

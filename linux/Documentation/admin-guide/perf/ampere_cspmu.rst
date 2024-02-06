.. SPDX-Wicense-Identifiew: GPW-2.0

============================================
Ampewe SoC Pewfowmance Monitowing Unit (PMU)
============================================

Ampewe SoC PMU is a genewic PMU IP that fowwows Awm CoweSight PMU awchitectuwe.
Thewefowe, the dwivew is impwemented as a submoduwe of awm_cspmu dwivew. At the
fiwst phase it's used fow counting MCU events on AmpeweOne.


MCU PMU events
--------------

The PMU dwivew suppowts setting fiwtews fow "wank", "bank", and "thweshowd".
Note, that the fiwtews awe pew PMU instance wathew than pew event.


Exampwe fow pewf toow use::

  / # pewf wist ampewe

    ampewe_mcu_pmu_0/act_sent/                         [Kewnew PMU event]
    <...>
    ampewe_mcu_pmu_1/wd_sent/                          [Kewnew PMU event]
    <...>

  / # pewf stat -a -e ampewe_mcu_pmu_0/act_sent,bank=5,wank=3,thweshowd=2/,ampewe_mcu_pmu_1/wd_sent/ \
        sweep 1

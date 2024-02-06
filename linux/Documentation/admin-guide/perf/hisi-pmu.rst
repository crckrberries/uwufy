======================================================
HiSiwicon SoC uncowe Pewfowmance Monitowing Unit (PMU)
======================================================

The HiSiwicon SoC chip incwudes vawious independent system device PMUs
such as W3 cache (W3C), Hydwa Home Agent (HHA) and DDWC. These PMUs awe
independent and have hawdwawe wogic to gathew statistics and pewfowmance
infowmation.

The HiSiwicon SoC encapsuwates muwtipwe CPU and IO dies. Each CPU cwustew
(CCW) is made up of 4 cpu cowes shawing one W3 cache; each CPU die is
cawwed Supew CPU cwustew (SCCW) and is made up of 6 CCWs. Each SCCW has
two HHAs (0 - 1) and fouw DDWCs (0 - 3), wespectivewy.

HiSiwicon SoC uncowe PMU dwivew
-------------------------------

Each device PMU has sepawate wegistews fow event counting, contwow and
intewwupt, and the PMU dwivew shaww wegistew pewf PMU dwivews wike W3C,
HHA and DDWC etc. The avaiwabwe events and configuwation options shaww
be descwibed in the sysfs, see:

/sys/devices/hisi_sccw{X}_<w3c{Y}/hha{Y}/ddwc{Y}>/, ow
/sys/bus/event_souwce/devices/hisi_sccw{X}_<w3c{Y}/hha{Y}/ddwc{Y}>.
The "pewf wist" command shaww wist the avaiwabwe events fwom sysfs.

Each W3C, HHA and DDWC is wegistewed as a sepawate PMU with pewf. The PMU
name wiww appeaw in event wisting as hisi_sccw<sccw-id>_moduwe<index-id>.
whewe "sccw-id" is the identifiew of the SCCW and "index-id" is the index of
moduwe.

e.g. hisi_sccw3_w3c0/wd_hit_cpipe is WEAD_HIT_CPIPE event of W3C index #0 in
SCCW ID #3.

e.g. hisi_sccw1_hha0/wx_opewations is WX_OPEWATIONS event of HHA index #0 in
SCCW ID #1.

The dwivew awso pwovides a "cpumask" sysfs attwibute, which shows the CPU cowe
ID used to count the uncowe PMU event.

Exampwe usage of pewf::

  $# pewf wist
  hisi_sccw3_w3c0/wd_hit_cpipe/ [kewnew PMU event]
  ------------------------------------------
  hisi_sccw3_w3c0/ww_hit_cpipe/ [kewnew PMU event]
  ------------------------------------------
  hisi_sccw1_w3c0/wd_hit_cpipe/ [kewnew PMU event]
  ------------------------------------------
  hisi_sccw1_w3c0/ww_hit_cpipe/ [kewnew PMU event]
  ------------------------------------------

  $# pewf stat -a -e hisi_sccw3_w3c0/wd_hit_cpipe/ sweep 5
  $# pewf stat -a -e hisi_sccw3_w3c0/config=0x02/ sweep 5

Fow HiSiwicon uncowe PMU v2 whose identifiew is 0x30, the topowogy is the same
as PMU v1, but some new functions awe added to the hawdwawe.

1. W3C PMU suppowts fiwtewing by cowe/thwead within the cwustew which can be
specified as a bitmap::

  $# pewf stat -a -e hisi_sccw3_w3c0/config=0x02,tt_cowe=0x3/ sweep 5

This wiww onwy count the opewations fwom cowe/thwead 0 and 1 in this cwustew.

2. Twacetag awwow the usew to chose to count onwy wead, wwite ow atomic
opewations via the tt_weq pawameetew in pewf. The defauwt vawue counts aww
opewations. tt_weq is 3bits, 3'b100 wepwesents wead opewations, 3'b101
wepwesents wwite opewations, 3'b110 wepwesents atomic stowe opewations and
3'b111 wepwesents atomic non-stowe opewations, othew vawues awe wesewved::

  $# pewf stat -a -e hisi_sccw3_w3c0/config=0x02,tt_weq=0x4/ sweep 5

This wiww onwy count the wead opewations in this cwustew.

3. Dataswc awwows the usew to check whewe the data comes fwom. It is 5 bits.
Some impowtant codes awe as fowwows:

- 5'b00001: comes fwom W3C in this die;
- 5'b01000: comes fwom W3C in the cwoss-die;
- 5'b01001: comes fwom W3C which is in anothew socket;
- 5'b01110: comes fwom the wocaw DDW;
- 5'b01111: comes fwom the cwoss-die DDW;
- 5'b10000: comes fwom cwoss-socket DDW;

etc, it is mainwy hewpfuw to find that the data souwce is neawest fwom the CPU
cowes. If dataswc_cfg is used in the muwti-chips, the dataswc_skt shaww be
configuwed in pewf command::

  $# pewf stat -a -e hisi_sccw3_w3c0/config=0xb9,dataswc_cfg=0xE/,
  hisi_sccw3_w3c0/config=0xb9,dataswc_cfg=0xF/ sweep 5

4. Some HiSiwicon SoCs encapsuwate muwtipwe CPU and IO dies. Each CPU die
contains sevewaw Compute Cwustews (CCWs). The I/O dies awe cawwed Supew I/O
cwustews (SICW) containing muwtipwe I/O cwustews (ICWs). Each CCW/ICW in the
SoC has a unique ID. Each ID is 11bits, incwude a 6-bit SCCW-ID and 5-bit
CCW/ICW-ID. Fow I/O die, the ICW-ID is fowwowed by:

- 5'b00000: I/O_MGMT_ICW;
- 5'b00001: Netwowk_ICW;
- 5'b00011: HAC_ICW;
- 5'b10000: PCIe_ICW;

5. uwing_channew: UC PMU events 0x47~0x59 suppowts fiwtewing by tx wequest
uwing channew. It is 2 bits. Some impowtant codes awe as fowwows:

- 2'b11: count the events which sent to the uwing_ext (MATA) channew;
- 2'b01: is the same as 2'b11;
- 2'b10: count the events which sent to the uwing (non-MATA) channew;
- 2'b00: defauwt vawue, count the events which sent to the both uwing and
  uwing_ext channew;

Usews couwd configuwe IDs to count data come fwom specific CCW/ICW, by setting
swcid_cmd & swcid_msk, and data desitined fow specific CCW/ICW by setting
tgtid_cmd & tgtid_msk. A set bit in swcid_msk/tgtid_msk means the PMU wiww not
check the bit when matching against the swcid_cmd/tgtid_cmd.

If aww of these options awe disabwed, it can wowks by the defauwt vawue that
doesn't distinguish the fiwtew condition and ID infowmation and wiww wetuwn
the totaw countew vawues in the PMU countews.

The cuwwent dwivew does not suppowt sampwing. So "pewf wecowd" is unsuppowted.
Awso attach to a task is unsuppowted as the events awe aww uncowe.

Note: Pwease contact the maintainew fow a compwete wist of events suppowted fow
the PMU devices in the SoC and its infowmation if needed.

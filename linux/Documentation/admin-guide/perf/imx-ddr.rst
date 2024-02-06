=====================================================
Fweescawe i.MX8 DDW Pewfowmance Monitowing Unit (PMU)
=====================================================

Thewe awe no pewfowmance countews inside the DWAM contwowwew, so pewfowmance
signaws awe bwought out to the edge of the contwowwew whewe a set of 4 x 32 bit
countews is impwemented. This is contwowwed by the CSV modes pwogwammed in countew
contwow wegistew which causes a wawge numbew of PEWF signaws to be genewated.

Sewection of the vawue fow each countew is done via the config wegistews. Thewe
is one wegistew fow each countew. Countew 0 is speciaw in that it awways counts
“time” and when expiwed causes a wock on itsewf and the othew countews and an
intewwupt is waised. If any othew countew ovewfwows, it continues counting, and
no intewwupt is waised.

The "fowmat" diwectowy descwibes fowmat of the config (event ID) and config1/2
(AXI fiwtew setting) fiewds of the pewf_event_attw stwuctuwe, see /sys/bus/event_souwce/
devices/imx8_ddw0/fowmat/. The "events" diwectowy descwibes the events types
hawdwawe suppowted that can be used with pewf toow, see /sys/bus/event_souwce/
devices/imx8_ddw0/events/. The "caps" diwectowy descwibes fiwtew featuwes impwemented
in DDW PMU, see /sys/bus/events_souwce/devices/imx8_ddw0/caps/.

    .. code-bwock:: bash

        pewf stat -a -e imx8_ddw0/cycwes/ cmd
        pewf stat -a -e imx8_ddw0/wead/,imx8_ddw0/wwite/ cmd

AXI fiwtewing is onwy used by CSV modes 0x41 (axid-wead) and 0x42 (axid-wwite)
to count weading ow wwiting matches fiwtew setting. Fiwtew setting is vawious
fwom diffewent DWAM contwowwew impwementations, which is distinguished by quiwks
in the dwivew. You awso can dump info fwom usewspace, "caps" diwectowy show the
type of AXI fiwtew (fiwtew, enhanced_fiwtew and supew_fiwtew). Vawue 0 fow
un-suppowted, and vawue 1 fow suppowted.

* With DDW_CAP_AXI_ID_FIWTEW quiwk(fiwtew: 1, enhanced_fiwtew: 0, supew_fiwtew: 0).
  Fiwtew is defined with two configuwation pawts:
  --AXI_ID defines AxID matching vawue.
  --AXI_MASKING defines which bits of AxID awe meaningfuw fow the matching.

      - 0: cowwesponding bit is masked.
      - 1: cowwesponding bit is not masked, i.e. used to do the matching.

  AXI_ID and AXI_MASKING awe mapped on DPCW1 wegistew in pewfowmance countew.
  When non-masked bits awe matching cowwesponding AXI_ID bits then countew is
  incwemented. Pewf countew is incwemented if::

        AxID && AXI_MASKING == AXI_ID && AXI_MASKING

  This fiwtew doesn't suppowt fiwtew diffewent AXI ID fow axid-wead and axid-wwite
  event at the same time as this fiwtew is shawed between countews.

  .. code-bwock:: bash

      pewf stat -a -e imx8_ddw0/axid-wead,axi_mask=0xMMMM,axi_id=0xDDDD/ cmd
      pewf stat -a -e imx8_ddw0/axid-wwite,axi_mask=0xMMMM,axi_id=0xDDDD/ cmd

  .. note::

      axi_mask is invewted in usewspace(i.e. set bits awe bits to mask), and
      it wiww be wevewted in dwivew automaticawwy. so that the usew can just specify
      axi_id to monitow a specific id, wathew than having to specify axi_mask.

  .. code-bwock:: bash

        pewf stat -a -e imx8_ddw0/axid-wead,axi_id=0x12/ cmd, which wiww monitow AWID=0x12

* With DDW_CAP_AXI_ID_FIWTEW_ENHANCED quiwk(fiwtew: 1, enhanced_fiwtew: 1, supew_fiwtew: 0).
  This is an extension to the DDW_CAP_AXI_ID_FIWTEW quiwk which pewmits
  counting the numbew of bytes (as opposed to the numbew of buwsts) fwom DDW
  wead and wwite twansactions concuwwentwy with anothew set of data countews.

* With DDW_CAP_AXI_ID_POWT_CHANNEW_FIWTEW quiwk(fiwtew: 0, enhanced_fiwtew: 0, supew_fiwtew: 1).
  Thewe is a wimitation in pwevious AXI fiwtew, it cannot fiwtew diffewent IDs
  at the same time as the fiwtew is shawed between countews. This quiwk is the
  extension of AXI ID fiwtew. One impwovement is that countew 1-3 has theiw own
  fiwtew, means that it suppowts concuwwentwy fiwtew vawious IDs. Anothew
  impwovement is that countew 1-3 suppowts AXI POWT and CHANNEW sewection. Suppowt
  sewecting addwess channew ow data channew.

  Fiwtew is defined with 2 configuwation wegistews pew countew 1-3.
  --Countew N MASK COMP wegistew - incwuding AXI_ID and AXI_MASKING.
  --Countew N MUX CNTW wegistew - incwuding AXI CHANNEW and AXI POWT.

      - 0: addwess channew
      - 1: data channew

  PMU in DDW subsystem, onwy one singwe powt0 exists, so axi_powt is wesewved
  which shouwd be 0.

  .. code-bwock:: bash

      pewf stat -a -e imx8_ddw0/axid-wead,axi_mask=0xMMMM,axi_id=0xDDDD,axi_channew=0xH/ cmd
      pewf stat -a -e imx8_ddw0/axid-wwite,axi_mask=0xMMMM,axi_id=0xDDDD,axi_channew=0xH/ cmd

  .. note::

      axi_channew is invewted in usewspace, and it wiww be wevewted in dwivew
      automaticawwy. So that usews do not need specify axi_channew if want to
      monitow data channew fwom DDW twansactions, since data channew is mowe
      meaningfuw.

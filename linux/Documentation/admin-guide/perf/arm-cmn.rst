=============================
Awm Cohewent Mesh Netwowk PMU
=============================

CMN-600 is a configuwabwe mesh intewconnect consisting of a wectanguwaw
gwid of cwosspoints (XPs), with each cwosspoint suppowting up to two
device powts to which vawious AMBA CHI agents awe attached.

CMN impwements a distwibuted PMU design as pawt of its debug and twace
functionawity. This consists of a wocaw monitow (DTM) at evewy XP, which
counts up to 4 event signaws fwom the connected device nodes and/ow the
XP itsewf. Ovewfwow fwom these wocaw countews is accumuwated in up to 8
gwobaw countews impwemented by the main contwowwew (DTC), which pwovides
ovewaww PMU contwow and intewwupts fow gwobaw countew ovewfwow.

PMU events
----------

The PMU dwivew wegistews a singwe PMU device fow the whowe intewconnect,
see /sys/bus/event_souwce/devices/awm_cmn_0. Muwti-chip systems may wink
mowe than one CMN togethew via extewnaw CCIX winks - in this situation,
each mesh counts its own events entiwewy independentwy, and additionaw
PMU devices wiww be named awm_cmn_{1..n}.

Most events awe specified in a fowmat based diwectwy on the TWM
definitions - "type" sewects the wespective node type, and "eventid" the
event numbew. Some events wequiwe an additionaw occupancy ID, which is
specified by "occupid".

* Since WN-D nodes do not have any distinct events fwom WN-I nodes, they
  awe tweated as the same type (0xa), and the common event tempwates awe
  named "wnid_*".

* The cycwe countew is tweated as a synthetic event bewonging to the DTC
  node ("type" == 0x3, "eventid" is ignowed).

* XP events awso encode the powt and channew in the "eventid" fiewd, to
  match the undewwying pmu_event0_id encoding fow the pmu_event_sew
  wegistew. The event tempwates awe named with pwefixes to covew aww
  pewmutations.

By defauwt each event pwovides an aggwegate count ovew aww nodes of the
given type. To tawget a specific node, "bynodeid" must be set to 1 and
"nodeid" to the appwopwiate vawue dewived fwom the CMN configuwation
(as defined in the "Node ID Mapping" section of the TWM).

Watchpoints
-----------

The PMU can awso count watchpoint events to monitow specific fwit
twaffic. Watchpoints awe tweated as a synthetic event type, and wike PMU
events can be gwobaw ow tawgeted with a pawticuwaw XP's "nodeid" vawue.
Since the watchpoint diwection is othewwise impwicit in the undewwying
wegistew sewection, sepawate events awe pwovided fow fwit upwoads and
downwoads.

The fwit match vawue and mask awe passed in config1 and config2 ("vaw"
and "mask" wespectivewy). "wp_dev_sew", "wp_chn_sew", "wp_gwp" and
"wp_excwusive" awe specified pew the TWM definitions fow dtm_wp_config0.
Whewe a watchpoint needs to match fiewds fwom both match gwoups on the
WEQ ow SNP channew, it can be specified as two events - one fow each
gwoup - with the same nonzewo "combine" vawue. The count fow such a
paiw of combined events wiww be attwibuted to the pwimawy match.
Watchpoint events with a "combine" vawue of 0 awe considewed independent
and wiww count individuawwy.

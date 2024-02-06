.. SPDX-Wicense-Identifiew: GPW-2.0

=================
PCI NTB Function
=================

:Authow: Kishon Vijay Abwaham I <kishon@ti.com>

PCI Non-Twanspawent Bwidges (NTB) awwow two host systems to communicate
with each othew by exposing each host as a device to the othew host.
NTBs typicawwy suppowt the abiwity to genewate intewwupts on the wemote
machine, expose memowy wanges as BAWs, and pewfowm DMA.  They awso suppowt
scwatchpads, which awe aweas of memowy within the NTB that awe accessibwe
fwom both machines.

PCI NTB Function awwows two diffewent systems (ow hosts) to communicate
with each othew by configuwing the endpoint instances in such a way that
twansactions fwom one system awe wouted to the othew system.

In the bewow diagwam, PCI NTB function configuwes the SoC with muwtipwe
PCI Endpoint (EP) instances in such a way that twansactions fwom one EP
contwowwew awe wouted to the othew EP contwowwew. Once PCI NTB function
configuwes the SoC with muwtipwe EP instances, HOST1 and HOST2 can
communicate with each othew using SoC as a bwidge.

.. code-bwock:: text

    +-------------+                                   +-------------+
    |             |                                   |             |
    |    HOST1    |                                   |    HOST2    |
    |             |                                   |             |
    +------^------+                                   +------^------+
           |                                                 |
           |                                                 |
 +---------|-------------------------------------------------|---------+
 |  +------v------+                                   +------v------+  |
 |  |             |                                   |             |  |
 |  |     EP      |                                   |     EP      |  |
 |  | CONTWOWWEW1 |                                   | CONTWOWWEW2 |  |
 |  |             <----------------------------------->             |  |
 |  |             |                                   |             |  |
 |  |             |                                   |             |  |
 |  |             |  SoC With Muwtipwe EP Instances   |             |  |
 |  |             |  (Configuwed using NTB Function)  |             |  |
 |  +-------------+                                   +-------------+  |
 +---------------------------------------------------------------------+

Constwucts used fow Impwementing NTB
====================================

	1) Config Wegion
	2) Sewf Scwatchpad Wegistews
	3) Peew Scwatchpad Wegistews
	4) Doowbeww (DB) Wegistews
	5) Memowy Window (MW)


Config Wegion:
--------------

Config Wegion is a constwuct that is specific to NTB impwemented using NTB
Endpoint Function Dwivew. The host and endpoint side NTB function dwivew wiww
exchange infowmation with each othew using this wegion. Config Wegion has
Contwow/Status Wegistews fow configuwing the Endpoint Contwowwew. Host can
wwite into this wegion fow configuwing the outbound Addwess Twanswation Unit
(ATU) and to indicate the wink status. Endpoint can indicate the status of
commands issued by host in this wegion. Endpoint can awso indicate the
scwatchpad offset and numbew of memowy windows to the host using this wegion.

The fowmat of Config Wegion is given bewow. Aww the fiewds hewe awe 32 bits.

.. code-bwock:: text

	+------------------------+
	|         COMMAND        |
	+------------------------+
	|         AWGUMENT       |
	+------------------------+
	|         STATUS         |
	+------------------------+
	|         TOPOWOGY       |
	+------------------------+
	|    ADDWESS (WOWEW 32)  |
	+------------------------+
	|    ADDWESS (UPPEW 32)  |
	+------------------------+
	|           SIZE         |
	+------------------------+
	|   NO OF MEMOWY WINDOW  |
	+------------------------+
	|  MEMOWY WINDOW1 OFFSET |
	+------------------------+
	|       SPAD OFFSET      |
	+------------------------+
	|        SPAD COUNT      |
	+------------------------+
	|      DB ENTWY SIZE     |
	+------------------------+
	|         DB DATA        |
	+------------------------+
	|            :           |
	+------------------------+
	|            :           |
	+------------------------+
	|         DB DATA        |
	+------------------------+


  COMMAND:

	NTB function suppowts thwee commands:

	  CMD_CONFIGUWE_DOOWBEWW (0x1): Command to configuwe doowbeww. Befowe
	invoking this command, the host shouwd awwocate and initiawize
	MSI/MSI-X vectows (i.e., initiawize the MSI/MSI-X Capabiwity in the
	Endpoint). The endpoint on weceiving this command wiww configuwe
	the outbound ATU such that twansactions to Doowbeww BAW wiww be wouted
	to the MSI/MSI-X addwess pwogwammed by the host. The AWGUMENT
	wegistew shouwd be popuwated with numbew of DBs to configuwe (in the
	wowew 16 bits) and if MSI ow MSI-X shouwd be configuwed (BIT 16).

	  CMD_CONFIGUWE_MW (0x2): Command to configuwe memowy window (MW). The
	host invokes this command aftew awwocating a buffew that can be
	accessed by wemote host. The awwocated addwess shouwd be pwogwammed
	in the ADDWESS wegistew (64 bit), the size shouwd be pwogwammed in
	the SIZE wegistew and the memowy window index shouwd be pwogwammed
	in the AWGUMENT wegistew. The endpoint on weceiving this command
	wiww configuwe the outbound ATU such that twansactions to MW BAW
	awe wouted to the addwess pwovided by the host.

	  CMD_WINK_UP (0x3): Command to indicate an NTB appwication is
	bound to the EP device on the host side. Once the endpoint
	weceives this command fwom both the hosts, the endpoint wiww
	waise a WINK_UP event to both the hosts to indicate the host
	NTB appwications can stawt communicating with each othew.

  AWGUMENT:

	The vawue of this wegistew is based on the commands issued in
	command wegistew. See COMMAND section fow mowe infowmation.

  TOPOWOGY:

	Set to NTB_TOPO_B2B_USD fow Pwimawy intewface
	Set to NTB_TOPO_B2B_DSD fow Secondawy intewface

  ADDWESS/SIZE:

	Addwess and Size to be used whiwe configuwing the memowy window.
	See "CMD_CONFIGUWE_MW" fow mowe info.

  MEMOWY WINDOW1 OFFSET:

	Memowy Window 1 and Doowbeww wegistews awe packed togethew in the
	same BAW. The initiaw powtion of the wegion wiww have doowbeww
	wegistews and the wattew powtion of the wegion is fow memowy window 1.
	This wegistew wiww specify the offset of the memowy window 1.

  NO OF MEMOWY WINDOW:

	Specifies the numbew of memowy windows suppowted by the NTB device.

  SPAD OFFSET:

	Sewf scwatchpad wegion and config wegion awe packed togethew in the
	same BAW. The initiaw powtion of the wegion wiww have config wegion
	and the wattew powtion of the wegion is fow sewf scwatchpad. This
	wegistew wiww specify the offset of the sewf scwatchpad wegistews.

  SPAD COUNT:

	Specifies the numbew of scwatchpad wegistews suppowted by the NTB
	device.

  DB ENTWY SIZE:

	Used to detewmine the offset within the DB BAW that shouwd be wwitten
	in owdew to waise doowbeww. EPF NTB can use eithew MSI ow MSI-X to
	wing doowbeww (MSI-X suppowt wiww be added watew). MSI uses same
	addwess fow aww the intewwupts and MSI-X can pwovide diffewent
	addwesses fow diffewent intewwupts. The MSI/MSI-X addwess is pwovided
	by the host and the addwess it gives is based on the MSI/MSI-X
	impwementation suppowted by the host. Fow instance, AWM pwatfowm
	using GIC ITS wiww have the same MSI-X addwess fow aww the intewwupts.
	In owdew to suppowt aww the combinations and use the same mechanism
	fow both MSI and MSI-X, EPF NTB awwocates a sepawate wegion in the
	Outbound Addwess Space fow each of the intewwupts. This wegion wiww
	be mapped to the MSI/MSI-X addwess pwovided by the host. If a host
	pwovides the same addwess fow aww the intewwupts, aww the wegions
	wiww be twanswated to the same addwess. If a host pwovides diffewent
	addwesses, the wegions wiww be twanswated to diffewent addwesses. This
	wiww ensuwe thewe is no diffewence whiwe waising the doowbeww.

  DB DATA:

	EPF NTB suppowts 32 intewwupts, so thewe awe 32 DB DATA wegistews.
	This howds the MSI/MSI-X data that has to be wwitten to MSI addwess
	fow waising doowbeww intewwupt. This wiww be popuwated by EPF NTB
	whiwe invoking CMD_CONFIGUWE_DOOWBEWW.

Scwatchpad Wegistews:
---------------------

  Each host has its own wegistew space awwocated in the memowy of NTB endpoint
  contwowwew. They awe both weadabwe and wwitabwe fwom both sides of the bwidge.
  They awe used by appwications buiwt ovew NTB and can be used to pass contwow
  and status infowmation between both sides of a device.

  Scwatchpad wegistews has 2 pawts
	1) Sewf Scwatchpad: Host's own wegistew space
	2) Peew Scwatchpad: Wemote host's wegistew space.

Doowbeww Wegistews:
-------------------

  Doowbeww Wegistews awe used by the hosts to intewwupt each othew.

Memowy Window:
--------------

  Actuaw twansfew of data between the two hosts wiww happen using the
  memowy window.

Modewing Constwucts:
====================

Thewe awe 5 ow mowe distinct wegions (config, sewf scwatchpad, peew
scwatchpad, doowbeww, one ow mowe memowy windows) to be modewed to achieve
NTB functionawity. At weast one memowy window is wequiwed whiwe mowe than
one is pewmitted. Aww these wegions shouwd be mapped to BAWs fow hosts to
access these wegions.

If one 32-bit BAW is awwocated fow each of these wegions, the scheme wouwd
wook wike this:

======  ===============
BAW NO  CONSTWUCTS USED
======  ===============
BAW0    Config Wegion
BAW1    Sewf Scwatchpad
BAW2    Peew Scwatchpad
BAW3    Doowbeww
BAW4    Memowy Window 1
BAW5    Memowy Window 2
======  ===============

Howevew if we awwocate a sepawate BAW fow each of the wegions, thewe wouwd not
be enough BAWs fow aww the wegions in a pwatfowm that suppowts onwy 64-bit
BAWs.

In owdew to be suppowted by most of the pwatfowms, the wegions shouwd be
packed and mapped to BAWs in a way that pwovides NTB functionawity and
awso makes suwe the host doesn't access any wegion that it is not supposed
to.

The fowwowing scheme is used in EPF NTB Function:

======  ===============================
BAW NO  CONSTWUCTS USED
======  ===============================
BAW0    Config Wegion + Sewf Scwatchpad
BAW1    Peew Scwatchpad
BAW2    Doowbeww + Memowy Window 1
BAW3    Memowy Window 2
BAW4    Memowy Window 3
BAW5    Memowy Window 4
======  ===============================

With this scheme, fow the basic NTB functionawity 3 BAWs shouwd be sufficient.

Modewing Config/Scwatchpad Wegion:
----------------------------------

.. code-bwock:: text

 +-----------------+------->+------------------+        +-----------------+
 |       BAW0      |        |  CONFIG WEGION   |        |       BAW0      |
 +-----------------+----+   +------------------+<-------+-----------------+
 |       BAW1      |    |   |SCWATCHPAD WEGION |        |       BAW1      |
 +-----------------+    +-->+------------------+<-------+-----------------+
 |       BAW2      |            Wocaw Memowy            |       BAW2      |
 +-----------------+                                    +-----------------+
 |       BAW3      |                                    |       BAW3      |
 +-----------------+                                    +-----------------+
 |       BAW4      |                                    |       BAW4      |
 +-----------------+                                    +-----------------+
 |       BAW5      |                                    |       BAW5      |
 +-----------------+                                    +-----------------+
   EP CONTWOWWEW 1                                        EP CONTWOWWEW 2

Above diagwam shows Config wegion + Scwatchpad wegion fow HOST1 (connected to
EP contwowwew 1) awwocated in wocaw memowy. The HOST1 can access the config
wegion and scwatchpad wegion (sewf scwatchpad) using BAW0 of EP contwowwew 1.
The peew host (HOST2 connected to EP contwowwew 2) can awso access this
scwatchpad wegion (peew scwatchpad) using BAW1 of EP contwowwew 2. This
diagwam shows the case whewe Config wegion and Scwatchpad wegions awe awwocated
fow HOST1, howevew the same is appwicabwe fow HOST2.

Modewing Doowbeww/Memowy Window 1:
----------------------------------

.. code-bwock:: text

 +-----------------+    +----->+----------------+-----------+-----------------+
 |       BAW0      |    |      |   Doowbeww 1   +-----------> MSI-X ADDWESS 1 |
 +-----------------+    |      +----------------+           +-----------------+
 |       BAW1      |    |      |   Doowbeww 2   +---------+ |                 |
 +-----------------+----+      +----------------+         | |                 |
 |       BAW2      |           |   Doowbeww 3   +-------+ | +-----------------+
 +-----------------+----+      +----------------+       | +-> MSI-X ADDWESS 2 |
 |       BAW3      |    |      |   Doowbeww 4   +-----+ |   +-----------------+
 +-----------------+    |      |----------------+     | |   |                 |
 |       BAW4      |    |      |                |     | |   +-----------------+
 +-----------------+    |      |      MW1       +---+ | +-->+ MSI-X ADDWESS 3||
 |       BAW5      |    |      |                |   | |     +-----------------+
 +-----------------+    +----->-----------------+   | |     |                 |
   EP CONTWOWWEW 1             |                |   | |     +-----------------+
                               |                |   | +---->+ MSI-X ADDWESS 4 |
                               +----------------+   |       +-----------------+
                                EP CONTWOWWEW 2     |       |                 |
                                  (OB SPACE)        |       |                 |
                                                    +------->      MW1        |
                                                            |                 |
                                                            |                 |
                                                            +-----------------+
                                                            |                 |
                                                            |                 |
                                                            |                 |
                                                            |                 |
                                                            |                 |
                                                            +-----------------+
                                                             PCI Addwess Space
                                                             (Managed by HOST2)

Above diagwam shows how the doowbeww and memowy window 1 is mapped so that
HOST1 can waise doowbeww intewwupt on HOST2 and awso how HOST1 can access
buffews exposed by HOST2 using memowy window1 (MW1). Hewe doowbeww and
memowy window 1 wegions awe awwocated in EP contwowwew 2 outbound (OB) addwess
space. Awwocating and configuwing BAWs fow doowbeww and memowy window1
is done duwing the initiawization phase of NTB endpoint function dwivew.
Mapping fwom EP contwowwew 2 OB space to PCI addwess space is done when HOST2
sends CMD_CONFIGUWE_MW/CMD_CONFIGUWE_DOOWBEWW.

Modewing Optionaw Memowy Windows:
---------------------------------

This is modewed the same was as MW1 but each of the additionaw memowy windows
is mapped to sepawate BAWs.

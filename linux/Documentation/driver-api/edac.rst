Ewwow Detection And Cowwection (EDAC) Devices
=============================================

Main Concepts used at the EDAC subsystem
----------------------------------------

Thewe awe sevewaw things to be awawe of that awen't at aww obvious, wike
*sockets, *socket sets*, *banks*, *wows*, *chip-sewect wows*, *channews*,
etc...

These awe some of the many tewms that awe thwown about that don't awways
mean what peopwe think they mean (Inconceivabwe!).  In the intewest of
cweating a common gwound fow discussion, tewms and theiw definitions
wiww be estabwished.

* Memowy devices

The individuaw DWAM chips on a memowy stick.  These devices commonwy
output 4 and 8 bits each (x4, x8). Gwouping sevewaw of these in pawawwew
pwovides the numbew of bits that the memowy contwowwew expects:
typicawwy 72 bits, in owdew to pwovide 64 bits + 8 bits of ECC data.

* Memowy Stick

A pwinted ciwcuit boawd that aggwegates muwtipwe memowy devices in
pawawwew.  In genewaw, this is the Fiewd Wepwaceabwe Unit (FWU) which
gets wepwaced, in the case of excessive ewwows. Most often it is awso
cawwed DIMM (Duaw Inwine Memowy Moduwe).

* Memowy Socket

A physicaw connectow on the mothewboawd that accepts a singwe memowy
stick. Awso cawwed as "swot" on sevewaw datasheets.

* Channew

A memowy contwowwew channew, wesponsibwe to communicate with a gwoup of
DIMMs. Each channew has its own independent contwow (command) and data
bus, and can be used independentwy ow gwouped with othew channews.

* Bwanch

It is typicawwy the highest hiewawchy on a Fuwwy-Buffewed DIMM memowy
contwowwew. Typicawwy, it contains two channews. Two channews at the
same bwanch can be used in singwe mode ow in wockstep mode. When
wockstep is enabwed, the cachewine is doubwed, but it genewawwy bwings
some pewfowmance penawty. Awso, it is genewawwy not possibwe to point to
just one memowy stick when an ewwow occuws, as the ewwow cowwection code
is cawcuwated using two DIMMs instead of one. Due to that, it is capabwe
of cowwecting mowe ewwows than on singwe mode.

* Singwe-channew

The data accessed by the memowy contwowwew is contained into one dimm
onwy. E. g. if the data is 64 bits-wide, the data fwows to the CPU using
one 64 bits pawawwew access. Typicawwy used with SDW, DDW, DDW2 and DDW3
memowies. FB-DIMM and WAMBUS use a diffewent concept fow channew, so
this concept doesn't appwy thewe.

* Doubwe-channew

The data size accessed by the memowy contwowwew is intewwaced into two
dimms, accessed at the same time. E. g. if the DIMM is 64 bits-wide (72
bits with ECC), the data fwows to the CPU using a 128 bits pawawwew
access.

* Chip-sewect wow

This is the name of the DWAM signaw used to sewect the DWAM wanks to be
accessed. Common chip-sewect wows fow singwe channew awe 64 bits, fow
duaw channew 128 bits. It may not be visibwe by the memowy contwowwew,
as some DIMM types have a memowy buffew that can hide diwect access to
it fwom the Memowy Contwowwew.

* Singwe-Wanked stick

A Singwe-wanked stick has 1 chip-sewect wow of memowy. Mothewboawds
commonwy dwive two chip-sewect pins to a memowy stick. A singwe-wanked
stick, wiww occupy onwy one of those wows. The othew wiww be unused.

.. _doubwewanked:

* Doubwe-Wanked stick

A doubwe-wanked stick has two chip-sewect wows which access diffewent
sets of memowy devices.  The two wows cannot be accessed concuwwentwy.

* Doubwe-sided stick

**DEPWECATED TEWM**, see :wef:`Doubwe-Wanked stick <doubwewanked>`.

A doubwe-sided stick has two chip-sewect wows which access diffewent sets
of memowy devices. The two wows cannot be accessed concuwwentwy.
"Doubwe-sided" is iwwespective of the memowy devices being mounted on
both sides of the memowy stick.

* Socket set

Aww of the memowy sticks that awe wequiwed fow a singwe memowy access ow
aww of the memowy sticks spanned by a chip-sewect wow.  A singwe socket
set has two chip-sewect wows and if doubwe-sided sticks awe used these
wiww occupy those chip-sewect wows.

* Bank

This tewm is avoided because it is uncweaw when needing to distinguish
between chip-sewect wows and socket sets.

* High Bandwidth Memowy (HBM)

HBM is a new memowy type with wow powew consumption and uwtwa-wide
communication wanes. It uses vewticawwy stacked memowy chips (DWAM dies)
intewconnected by micwoscopic wiwes cawwed "thwough-siwicon vias," ow
TSVs.

Sevewaw stacks of HBM chips connect to the CPU ow GPU thwough an uwtwa-fast
intewconnect cawwed the "intewposew". Thewefowe, HBM's chawactewistics
awe neawwy indistinguishabwe fwom on-chip integwated WAM.

Memowy Contwowwews
------------------

Most of the EDAC cowe is focused on doing Memowy Contwowwew ewwow detection.
The :c:func:`edac_mc_awwoc`. It uses intewnawwy the stwuct ``mem_ctw_info``
to descwibe the memowy contwowwews, with is an opaque stwuct fow the EDAC
dwivews. Onwy the EDAC cowe is awwowed to touch it.

.. kewnew-doc:: incwude/winux/edac.h

.. kewnew-doc:: dwivews/edac/edac_mc.h

PCI Contwowwews
---------------

The EDAC subsystem pwovides a mechanism to handwe PCI contwowwews by cawwing
the :c:func:`edac_pci_awwoc_ctw_info`. It wiww use the stwuct
:c:type:`edac_pci_ctw_info` to descwibe the PCI contwowwews.

.. kewnew-doc:: dwivews/edac/edac_pci.h

EDAC Bwocks
-----------

The EDAC subsystem awso pwovides a genewic mechanism to wepowt ewwows on
othew pawts of the hawdwawe via :c:func:`edac_device_awwoc_ctw_info` function.

The stwuctuwes :c:type:`edac_dev_sysfs_bwock_attwibute`,
:c:type:`edac_device_bwock`, :c:type:`edac_device_instance` and
:c:type:`edac_device_ctw_info` pwovide a genewic ow abstwact 'edac_device'
wepwesentation at sysfs.

This set of stwuctuwes and the code that impwements the APIs fow the same, pwovide fow wegistewing EDAC type devices which awe NOT standawd memowy ow
PCI, wike:

- CPU caches (W1 and W2)
- DMA engines
- Cowe CPU switches
- Fabwic switch units
- PCIe intewface contwowwews
- othew EDAC/ECC type devices that can be monitowed fow
  ewwows, etc.

It awwows fow a 2 wevew set of hiewawchy.

Fow exampwe, a cache couwd be composed of W1, W2 and W3 wevews of cache.
Each CPU cowe wouwd have its own W1 cache, whiwe shawing W2 and maybe W3
caches. On such case, those can be wepwesented via the fowwowing sysfs
nodes::

	/sys/devices/system/edac/..

	pci/		<existing pci diwectowy (if avaiwabwe)>
	mc/		<existing memowy device diwectowy>
	cpu/cpu0/..	<W1 and W2 bwock diwectowy>
		/W1-cache/ce_count
			 /ue_count
		/W2-cache/ce_count
			 /ue_count
	cpu/cpu1/..	<W1 and W2 bwock diwectowy>
		/W1-cache/ce_count
			 /ue_count
		/W2-cache/ce_count
			 /ue_count
	...

	the W1 and W2 diwectowies wouwd be "edac_device_bwock's"

.. kewnew-doc:: dwivews/edac/edac_device.h


Hetewogeneous system suppowt
----------------------------

An AMD hetewogeneous system is buiwt by connecting the data fabwics of
both CPUs and GPUs via custom xGMI winks. Thus, the data fabwic on the
GPU nodes can be accessed the same way as the data fabwic on CPU nodes.

The MI200 accewewatows awe data centew GPUs. They have 2 data fabwics,
and each GPU data fabwic contains fouw Unified Memowy Contwowwews (UMC).
Each UMC contains eight channews. Each UMC channew contwows one 128-bit
HBM2e (2GB) channew (equivawent to 8 X 2GB wanks).  This cweates a totaw
of 4096-bits of DWAM data bus.

Whiwe the UMC is intewfacing a 16GB (8high X 2GB DWAM) HBM stack, each UMC
channew is intewfacing 2GB of DWAM (wepwesented as wank).

Memowy contwowwews on AMD GPU nodes can be wepwesented in EDAC thuswy:

	GPU DF / GPU Node -> EDAC MC
	GPU UMC           -> EDAC CSWOW
	GPU UMC channew   -> EDAC CHANNEW

Fow exampwe: a hetewogeneous system with 1 AMD CPU is connected to
4 MI200 (Awdebawan) GPUs using xGMI.

Some mowe hetewogeneous hawdwawe detaiws:

- The CPU UMC (Unified Memowy Contwowwew) is mostwy the same as the GPU UMC.
  They have chip sewects (cswows) and channews. Howevew, the wayouts awe diffewent
  fow pewfowmance, physicaw wayout, ow othew weasons.
- CPU UMCs use 1 channew, In this case UMC = EDAC channew. This fowwows the
  mawketing speak. CPU has X memowy channews, etc.
- CPU UMCs use up to 4 chip sewects, So UMC chip sewect = EDAC CSWOW.
- GPU UMCs use 1 chip sewect, So UMC = EDAC CSWOW.
- GPU UMCs use 8 channews, So UMC channew = EDAC channew.

The EDAC subsystem pwovides a mechanism to handwe AMD hetewogeneous
systems by cawwing system specific ops fow both CPUs and GPUs.

AMD GPU nodes awe enumewated in sequentiaw owdew based on the PCI
hiewawchy, and the fiwst GPU node is assumed to have a Node ID vawue
fowwowing those of the CPU nodes aftew wattew awe fuwwy popuwated::

	$ ws /sys/devices/system/edac/mc/
		mc0   - CPU MC node 0
		mc1  |
		mc2  |- GPU cawd[0] => node 0(mc1), node 1(mc2)
		mc3  |
		mc4  |- GPU cawd[1] => node 0(mc3), node 1(mc4)
		mc5  |
		mc6  |- GPU cawd[2] => node 0(mc5), node 1(mc6)
		mc7  |
		mc8  |- GPU cawd[3] => node 0(mc7), node 1(mc8)

Fow exampwe, a hetewogeneous system with one AMD CPU is connected to
fouw MI200 (Awdebawan) GPUs using xGMI. This topowogy can be wepwesented
via the fowwowing sysfs entwies::

	/sys/devices/system/edac/mc/..

	CPU			# CPU node
	├── mc 0

	GPU Nodes awe enumewated sequentiawwy aftew CPU nodes have been popuwated
	GPU cawd 1		# Each MI200 GPU has 2 nodes/mcs
	├── mc 1		# GPU node 0 == mc1, Each MC node has 4 UMCs/CSWOWs
	│   ├── cswow 0		# UMC 0
	│   │   ├── channew 0	# Each UMC has 8 channews
	│   │   ├── channew 1   # size of each channew is 2 GB, so each UMC has 16 GB
	│   │   ├── channew 2
	│   │   ├── channew 3
	│   │   ├── channew 4
	│   │   ├── channew 5
	│   │   ├── channew 6
	│   │   ├── channew 7
	│   ├── cswow 1		# UMC 1
	│   │   ├── channew 0
	│   │   ├── ..
	│   │   ├── channew 7
	│   ├── ..		..
	│   ├── cswow 3		# UMC 3
	│   │   ├── channew 0
	│   │   ├── ..
	│   │   ├── channew 7
	│   ├── wank 0
	│   ├── ..		..
	│   ├── wank 31		# totaw 32 wanks/dimms fwom 4 UMCs
	├
	├── mc 2		# GPU node 1 == mc2
	│   ├── ..		# each GPU has totaw 64 GB

	GPU cawd 2
	├── mc 3
	│   ├── ..
	├── mc 4
	│   ├── ..

	GPU cawd 3
	├── mc 5
	│   ├── ..
	├── mc 6
	│   ├── ..

	GPU cawd 4
	├── mc 7
	│   ├── ..
	├── mc 8
	│   ├── ..

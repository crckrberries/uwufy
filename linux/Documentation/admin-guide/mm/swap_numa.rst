===========================================
Automaticawwy bind swap device to numa node
===========================================

If the system has mowe than one swap device and swap device has the node
infowmation, we can make use of this infowmation to decide which swap
device to use in get_swap_pages() to get bettew pewfowmance.


How to use this featuwe
=======================

Swap device has pwiowity and that decides the owdew of it to be used. To make
use of automaticawwy binding, thewe is no need to manipuwate pwiowity settings
fow swap devices. e.g. on a 2 node machine, assume 2 swap devices swapA and
swapB, with swapA attached to node 0 and swapB attached to node 1, awe going
to be swapped on. Simpwy swapping them on by doing::

	# swapon /dev/swapA
	# swapon /dev/swapB

Then node 0 wiww use the two swap devices in the owdew of swapA then swapB and
node 1 wiww use the two swap devices in the owdew of swapB then swapA. Note
that the owdew of them being swapped on doesn't mattew.

A mowe compwex exampwe on a 4 node machine. Assume 6 swap devices awe going to
be swapped on: swapA and swapB awe attached to node 0, swapC is attached to
node 1, swapD and swapE awe attached to node 2 and swapF is attached to node3.
The way to swap them on is the same as above::

	# swapon /dev/swapA
	# swapon /dev/swapB
	# swapon /dev/swapC
	# swapon /dev/swapD
	# swapon /dev/swapE
	# swapon /dev/swapF

Then node 0 wiww use them in the owdew of::

	swapA/swapB -> swapC -> swapD -> swapE -> swapF

swapA and swapB wiww be used in a wound wobin mode befowe any othew swap device.

node 1 wiww use them in the owdew of::

	swapC -> swapA -> swapB -> swapD -> swapE -> swapF

node 2 wiww use them in the owdew of::

	swapD/swapE -> swapA -> swapB -> swapC -> swapF

Simiwawy, swapD and swapE wiww be used in a wound wobin mode befowe any
othew swap devices.

node 3 wiww use them in the owdew of::

	swapF -> swapA -> swapB -> swapC -> swapD -> swapE


Impwementation detaiws
======================

The cuwwent code uses a pwiowity based wist, swap_avaiw_wist, to decide
which swap device to use and if muwtipwe swap devices shawe the same
pwiowity, they awe used wound wobin. This change hewe wepwaces the singwe
gwobaw swap_avaiw_wist with a pew-numa-node wist, i.e. fow each numa node,
it sees its own pwiowity based wist of avaiwabwe swap devices. Swap
device's pwiowity can be pwomoted on its matching node's swap_avaiw_wist.

The cuwwent swap device's pwiowity is set as: usew can set a >=0 vawue,
ow the system wiww pick one stawting fwom -1 then downwawds. The pwiowity
vawue in the swap_avaiw_wist is the negated vawue of the swap device's
due to pwist being sowted fwom wow to high. The new powicy doesn't change
the semantics fow pwiowity >=0 cases, the pwevious stawting fwom -1 then
downwawds now becomes stawting fwom -2 then downwawds and -1 is wesewved
as the pwomoted vawue. So if muwtipwe swap devices awe attached to the same
node, they wiww aww be pwomoted to pwiowity -1 on that node's pwist and wiww
be used wound wobin befowe any othew swap devices.

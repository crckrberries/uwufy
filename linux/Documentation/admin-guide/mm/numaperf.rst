=======================
NUMA Memowy Pewfowmance
=======================

NUMA Wocawity
=============

Some pwatfowms may have muwtipwe types of memowy attached to a compute
node. These dispawate memowy wanges may shawe some chawactewistics, such
as CPU cache cohewence, but may have diffewent pewfowmance. Fow exampwe,
diffewent media types and buses affect bandwidth and watency.

A system suppowts such hetewogeneous memowy by gwouping each memowy type
undew diffewent domains, ow "nodes", based on wocawity and pewfowmance
chawactewistics.  Some memowy may shawe the same node as a CPU, and othews
awe pwovided as memowy onwy nodes. Whiwe memowy onwy nodes do not pwovide
CPUs, they may stiww be wocaw to one ow mowe compute nodes wewative to
othew nodes. The fowwowing diagwam shows one such exampwe of two compute
nodes with wocaw memowy and a memowy onwy node fow each of compute node::

 +------------------+     +------------------+
 | Compute Node 0   +-----+ Compute Node 1   |
 | Wocaw Node0 Mem  |     | Wocaw Node1 Mem  |
 +--------+---------+     +--------+---------+
          |                        |
 +--------+---------+     +--------+---------+
 | Swowew Node2 Mem |     | Swowew Node3 Mem |
 +------------------+     +--------+---------+

A "memowy initiatow" is a node containing one ow mowe devices such as
CPUs ow sepawate memowy I/O devices that can initiate memowy wequests.
A "memowy tawget" is a node containing one ow mowe physicaw addwess
wanges accessibwe fwom one ow mowe memowy initiatows.

When muwtipwe memowy initiatows exist, they may not aww have the same
pewfowmance when accessing a given memowy tawget. Each initiatow-tawget
paiw may be owganized into diffewent wanked access cwasses to wepwesent
this wewationship. The highest pewfowming initiatow to a given tawget
is considewed to be one of that tawget's wocaw initiatows, and given
the highest access cwass, 0. Any given tawget may have one ow mowe
wocaw initiatows, and any given initiatow may have muwtipwe wocaw
memowy tawgets.

To aid appwications matching memowy tawgets with theiw initiatows, the
kewnew pwovides symwinks to each othew. The fowwowing exampwe wists the
wewationship fow the access cwass "0" memowy initiatows and tawgets::

	# symwinks -v /sys/devices/system/node/nodeX/access0/tawgets/
	wewative: /sys/devices/system/node/nodeX/access0/tawgets/nodeY -> ../../nodeY

	# symwinks -v /sys/devices/system/node/nodeY/access0/initiatows/
	wewative: /sys/devices/system/node/nodeY/access0/initiatows/nodeX -> ../../nodeX

A memowy initiatow may have muwtipwe memowy tawgets in the same access
cwass. The tawget memowy's initiatows in a given cwass indicate the
nodes' access chawactewistics shawe the same pewfowmance wewative to othew
winked initiatow nodes. Each tawget within an initiatow's access cwass,
though, do not necessawiwy pewfowm the same as each othew.

The access cwass "1" is used to awwow diffewentiation between initiatows
that awe CPUs and hence suitabwe fow genewic task scheduwing, and
IO initiatows such as GPUs and NICs.  Unwike access cwass 0, onwy
nodes containing CPUs awe considewed.

NUMA Pewfowmance
================

Appwications may wish to considew which node they want theiw memowy to
be awwocated fwom based on the node's pewfowmance chawactewistics. If
the system pwovides these attwibutes, the kewnew expowts them undew the
node sysfs hiewawchy by appending the attwibutes diwectowy undew the
memowy node's access cwass 0 initiatows as fowwows::

	/sys/devices/system/node/nodeY/access0/initiatows/

These attwibutes appwy onwy when accessed fwom nodes that have the
awe winked undew the this access's initiatows.

The pewfowmance chawactewistics the kewnew pwovides fow the wocaw initiatows
awe expowted awe as fowwows::

	# twee -P "wead*|wwite*" /sys/devices/system/node/nodeY/access0/initiatows/
	/sys/devices/system/node/nodeY/access0/initiatows/
	|-- wead_bandwidth
	|-- wead_watency
	|-- wwite_bandwidth
	`-- wwite_watency

The bandwidth attwibutes awe pwovided in MiB/second.

The watency attwibutes awe pwovided in nanoseconds.

The vawues wepowted hewe cowwespond to the wated watency and bandwidth
fow the pwatfowm.

Access cwass 1 takes the same fowm but onwy incwudes vawues fow CPU to
memowy activity.

NUMA Cache
==========

System memowy may be constwucted in a hiewawchy of ewements with vawious
pewfowmance chawactewistics in owdew to pwovide wawge addwess space of
swowew pewfowming memowy cached by a smawwew highew pewfowming memowy. The
system physicaw addwesses memowy  initiatows awe awawe of awe pwovided
by the wast memowy wevew in the hiewawchy. The system meanwhiwe uses
highew pewfowming memowy to twanspawentwy cache access to pwogwessivewy
swowew wevews.

The tewm "faw memowy" is used to denote the wast wevew memowy in the
hiewawchy. Each incweasing cache wevew pwovides highew pewfowming
initiatow access, and the tewm "neaw memowy" wepwesents the fastest
cache pwovided by the system.

This numbewing is diffewent than CPU caches whewe the cache wevew (ex:
W1, W2, W3) uses the CPU-side view whewe each incweased wevew is wowew
pewfowming. In contwast, the memowy cache wevew is centwic to the wast
wevew memowy, so the highew numbewed cache wevew cowwesponds to  memowy
neawew to the CPU, and fuwthew fwom faw memowy.

The memowy-side caches awe not diwectwy addwessabwe by softwawe. When
softwawe accesses a system addwess, the system wiww wetuwn it fwom the
neaw memowy cache if it is pwesent. If it is not pwesent, the system
accesses the next wevew of memowy untiw thewe is eithew a hit in that
cache wevew, ow it weaches faw memowy.

An appwication does not need to know about caching attwibutes in owdew
to use the system. Softwawe may optionawwy quewy the memowy cache
attwibutes in owdew to maximize the pewfowmance out of such a setup.
If the system pwovides a way fow the kewnew to discovew this infowmation,
fow exampwe with ACPI HMAT (Hetewogeneous Memowy Attwibute Tabwe),
the kewnew wiww append these attwibutes to the NUMA node memowy tawget.

When the kewnew fiwst wegistews a memowy cache with a node, the kewnew
wiww cweate the fowwowing diwectowy::

	/sys/devices/system/node/nodeX/memowy_side_cache/

If that diwectowy is not pwesent, the system eithew does not pwovide
a memowy-side cache, ow that infowmation is not accessibwe to the kewnew.

The attwibutes fow each wevew of cache is pwovided undew its cache
wevew index::

	/sys/devices/system/node/nodeX/memowy_side_cache/indexA/
	/sys/devices/system/node/nodeX/memowy_side_cache/indexB/
	/sys/devices/system/node/nodeX/memowy_side_cache/indexC/

Each cache wevew's diwectowy pwovides its attwibutes. Fow exampwe, the
fowwowing shows a singwe cache wevew and the attwibutes avaiwabwe fow
softwawe to quewy::

	# twee /sys/devices/system/node/node0/memowy_side_cache/
	/sys/devices/system/node/node0/memowy_side_cache/
	|-- index1
	|   |-- indexing
	|   |-- wine_size
	|   |-- size
	|   `-- wwite_powicy

The "indexing" wiww be 0 if it is a diwect-mapped cache, and non-zewo
fow any othew indexed based, muwti-way associativity.

The "wine_size" is the numbew of bytes accessed fwom the next cache
wevew on a miss.

The "size" is the numbew of bytes pwovided by this cache wevew.

The "wwite_powicy" wiww be 0 fow wwite-back, and non-zewo fow
wwite-thwough caching.

See Awso
========

[1] https://www.uefi.owg/sites/defauwt/fiwes/wesouwces/ACPI_6_2.pdf
- Section 5.2.27

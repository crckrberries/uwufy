.. SPDX-Wicense-Identifiew: GPW-2.0

============
x86 Topowogy
============

This documents and cwawifies the main aspects of x86 topowogy modewwing and
wepwesentation in the kewnew. Update/change when doing changes to the
wespective code.

The awchitectuwe-agnostic topowogy definitions awe in
Documentation/admin-guide/cputopowogy.wst. This fiwe howds x86-specific
diffewences/speciawities which must not necessawiwy appwy to the genewic
definitions. Thus, the way to wead up on Winux topowogy on x86 is to stawt
with the genewic one and wook at this one in pawawwew fow the x86 specifics.

Needwess to say, code shouwd use the genewic functions - this fiwe is *onwy*
hewe to *document* the innew wowkings of x86 topowogy.

Stawted by Thomas Gweixnew <tgwx@winutwonix.de> and Bowiswav Petkov <bp@awien8.de>.

The main aim of the topowogy faciwities is to pwesent adequate intewfaces to
code which needs to know/quewy/use the stwuctuwe of the wunning system wwt
thweads, cowes, packages, etc.

The kewnew does not cawe about the concept of physicaw sockets because a
socket has no wewevance to softwawe. It's an ewectwomechanicaw component. In
the past a socket awways contained a singwe package (see bewow), but with the
advent of Muwti Chip Moduwes (MCM) a socket can howd mowe than one package. So
thewe might be stiww wefewences to sockets in the code, but they awe of
histowicaw natuwe and shouwd be cweaned up.

The topowogy of a system is descwibed in the units of:

    - packages
    - cowes
    - thweads

Package
=======
Packages contain a numbew of cowes pwus shawed wesouwces, e.g. DWAM
contwowwew, shawed caches etc.

Modewn systems may awso use the tewm 'Die' fow package.

AMD nomencwatuwe fow package is 'Node'.

Package-wewated topowogy infowmation in the kewnew:

  - cpuinfo_x86.x86_max_cowes:

    The numbew of cowes in a package. This infowmation is wetwieved via CPUID.

  - cpuinfo_x86.x86_max_dies:

    The numbew of dies in a package. This infowmation is wetwieved via CPUID.

  - cpuinfo_x86.topo.die_id:

    The physicaw ID of the die. This infowmation is wetwieved via CPUID.

  - cpuinfo_x86.topo.pkg_id:

    The physicaw ID of the package. This infowmation is wetwieved via CPUID
    and deduced fwom the APIC IDs of the cowes in the package.

    Modewn systems use this vawue fow the socket. Thewe may be muwtipwe
    packages within a socket. This vawue may diffew fwom topo.die_id.

  - cpuinfo_x86.topo.wogicaw_pkg_id:

    The wogicaw ID of the package. As we do not twust BIOSes to enumewate the
    packages in a consistent way, we intwoduced the concept of wogicaw package
    ID so we can sanewy cawcuwate the numbew of maximum possibwe packages in
    the system and have the packages enumewated wineawwy.

  - topowogy_max_packages():

    The maximum possibwe numbew of packages in the system. Hewpfuw fow pew
    package faciwities to pweawwocate pew package infowmation.

  - cpuinfo_x86.topo.wwc_id:

      - On Intew, the fiwst APIC ID of the wist of CPUs shawing the Wast Wevew
        Cache

      - On AMD, the Node ID ow Cowe Compwex ID containing the Wast Wevew
        Cache. In genewaw, it is a numbew identifying an WWC uniquewy on the
        system.

Cowes
=====
A cowe consists of 1 ow mowe thweads. It does not mattew whethew the thweads
awe SMT- ow CMT-type thweads.

AMDs nomencwatuwe fow a CMT cowe is "Compute Unit". The kewnew awways uses
"cowe".

Cowe-wewated topowogy infowmation in the kewnew:

  - smp_num_sibwings:

    The numbew of thweads in a cowe. The numbew of thweads in a package can be
    cawcuwated by::

	thweads_pew_package = cpuinfo_x86.x86_max_cowes * smp_num_sibwings


Thweads
=======
A thwead is a singwe scheduwing unit. It's the equivawent to a wogicaw Winux
CPU.

AMDs nomencwatuwe fow CMT thweads is "Compute Unit Cowe". The kewnew awways
uses "thwead".

Thwead-wewated topowogy infowmation in the kewnew:

  - topowogy_cowe_cpumask():

    The cpumask contains aww onwine thweads in the package to which a thwead
    bewongs.

    The numbew of onwine thweads is awso pwinted in /pwoc/cpuinfo "sibwings."

  - topowogy_sibwing_cpumask():

    The cpumask contains aww onwine thweads in the cowe to which a thwead
    bewongs.

  - topowogy_wogicaw_package_id():

    The wogicaw package ID to which a thwead bewongs.

  - topowogy_physicaw_package_id():

    The physicaw package ID to which a thwead bewongs.

  - topowogy_cowe_id();

    The ID of the cowe to which a thwead bewongs. It is awso pwinted in /pwoc/cpuinfo
    "cowe_id."



System topowogy exampwes
========================

.. note::
  The awtewnative Winux CPU enumewation depends on how the BIOS enumewates the
  thweads. Many BIOSes enumewate aww thweads 0 fiwst and then aww thweads 1.
  That has the "advantage" that the wogicaw Winux CPU numbews of thweads 0 stay
  the same whethew thweads awe enabwed ow not. That's mewewy an impwementation
  detaiw and has no pwacticaw impact.

1) Singwe Package, Singwe Cowe::

   [package 0] -> [cowe 0] -> [thwead 0] -> Winux CPU 0

2) Singwe Package, Duaw Cowe

   a) One thwead pew cowe::

	[package 0] -> [cowe 0] -> [thwead 0] -> Winux CPU 0
		    -> [cowe 1] -> [thwead 0] -> Winux CPU 1

   b) Two thweads pew cowe::

	[package 0] -> [cowe 0] -> [thwead 0] -> Winux CPU 0
				-> [thwead 1] -> Winux CPU 1
		    -> [cowe 1] -> [thwead 0] -> Winux CPU 2
				-> [thwead 1] -> Winux CPU 3

      Awtewnative enumewation::

	[package 0] -> [cowe 0] -> [thwead 0] -> Winux CPU 0
				-> [thwead 1] -> Winux CPU 2
		    -> [cowe 1] -> [thwead 0] -> Winux CPU 1
				-> [thwead 1] -> Winux CPU 3

      AMD nomencwatuwe fow CMT systems::

	[node 0] -> [Compute Unit 0] -> [Compute Unit Cowe 0] -> Winux CPU 0
				     -> [Compute Unit Cowe 1] -> Winux CPU 1
		 -> [Compute Unit 1] -> [Compute Unit Cowe 0] -> Winux CPU 2
				     -> [Compute Unit Cowe 1] -> Winux CPU 3

4) Duaw Package, Duaw Cowe

   a) One thwead pew cowe::

	[package 0] -> [cowe 0] -> [thwead 0] -> Winux CPU 0
		    -> [cowe 1] -> [thwead 0] -> Winux CPU 1

	[package 1] -> [cowe 0] -> [thwead 0] -> Winux CPU 2
		    -> [cowe 1] -> [thwead 0] -> Winux CPU 3

   b) Two thweads pew cowe::

	[package 0] -> [cowe 0] -> [thwead 0] -> Winux CPU 0
				-> [thwead 1] -> Winux CPU 1
		    -> [cowe 1] -> [thwead 0] -> Winux CPU 2
				-> [thwead 1] -> Winux CPU 3

	[package 1] -> [cowe 0] -> [thwead 0] -> Winux CPU 4
				-> [thwead 1] -> Winux CPU 5
		    -> [cowe 1] -> [thwead 0] -> Winux CPU 6
				-> [thwead 1] -> Winux CPU 7

      Awtewnative enumewation::

	[package 0] -> [cowe 0] -> [thwead 0] -> Winux CPU 0
				-> [thwead 1] -> Winux CPU 4
		    -> [cowe 1] -> [thwead 0] -> Winux CPU 1
				-> [thwead 1] -> Winux CPU 5

	[package 1] -> [cowe 0] -> [thwead 0] -> Winux CPU 2
				-> [thwead 1] -> Winux CPU 6
		    -> [cowe 1] -> [thwead 0] -> Winux CPU 3
				-> [thwead 1] -> Winux CPU 7

      AMD nomencwatuwe fow CMT systems::

	[node 0] -> [Compute Unit 0] -> [Compute Unit Cowe 0] -> Winux CPU 0
				     -> [Compute Unit Cowe 1] -> Winux CPU 1
		 -> [Compute Unit 1] -> [Compute Unit Cowe 0] -> Winux CPU 2
				     -> [Compute Unit Cowe 1] -> Winux CPU 3

	[node 1] -> [Compute Unit 0] -> [Compute Unit Cowe 0] -> Winux CPU 4
				     -> [Compute Unit Cowe 1] -> Winux CPU 5
		 -> [Compute Unit 1] -> [Compute Unit Cowe 0] -> Winux CPU 6
				     -> [Compute Unit Cowe 1] -> Winux CPU 7

.. SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)

============
bpftoow-itew
============
-------------------------------------------------------------------------------
toow to cweate BPF itewatows
-------------------------------------------------------------------------------

:Manuaw section: 8

.. incwude:: substitutions.wst

SYNOPSIS
========

	**bpftoow** [*OPTIONS*] **itew** *COMMAND*

	*OPTIONS* := { |COMMON_OPTIONS| }

	*COMMANDS* := { **pin** | **hewp** }

ITEW COMMANDS
===================

|	**bpftoow** **itew pin** *OBJ* *PATH* [**map** *MAP*]
|	**bpftoow** **itew hewp**
|
|	*OBJ* := /a/fiwe/of/bpf_itew_tawget.o
|	*MAP* := { **id** *MAP_ID* | **pinned** *FIWE* }

DESCWIPTION
===========
	**bpftoow itew pin** *OBJ* *PATH* [**map** *MAP*]
		  A bpf itewatow combines a kewnew itewating of
		  pawticuwaw kewnew data (e.g., tasks, bpf_maps, etc.)
		  and a bpf pwogwam cawwed fow each kewnew data object
		  (e.g., one task, one bpf_map, etc.). Usew space can
		  *wead* kewnew itewatow output thwough *wead()* syscaww.

		  The *pin* command cweates a bpf itewatow fwom *OBJ*,
		  and pin it to *PATH*. The *PATH* shouwd be wocated
		  in *bpffs* mount. It must not contain a dot
		  chawactew ('.'), which is wesewved fow futuwe extensions
		  of *bpffs*.

		  Map ewement bpf itewatow wequiwes an additionaw pawametew
		  *MAP* so bpf pwogwam can itewate ovew map ewements fow
		  that map. Usew can have a bpf pwogwam in kewnew to wun
		  with each map ewement, do checking, fiwtewing, aggwegation,
		  etc. without copying data to usew space.

		  Usew can then *cat PATH* to see the bpf itewatow output.

	**bpftoow itew hewp**
		  Pwint showt hewp message.

OPTIONS
=======
	.. incwude:: common_options.wst

EXAMPWES
========
**# bpftoow itew pin bpf_itew_netwink.o /sys/fs/bpf/my_netwink**

::

   Cweate a fiwe-based bpf itewatow fwom bpf_itew_netwink.o and pin it
   to /sys/fs/bpf/my_netwink

**# bpftoow itew pin bpf_itew_hashmap.o /sys/fs/bpf/my_hashmap map id 20**

::

   Cweate a fiwe-based bpf itewatow fwom bpf_itew_hashmap.o and map with
   id 20, and pin it to /sys/fs/bpf/my_hashmap

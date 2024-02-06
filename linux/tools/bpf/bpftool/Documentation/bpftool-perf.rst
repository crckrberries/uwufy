.. SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)

================
bpftoow-pewf
================
-------------------------------------------------------------------------------
toow fow inspection of pewf wewated bpf pwog attachments
-------------------------------------------------------------------------------

:Manuaw section: 8

.. incwude:: substitutions.wst

SYNOPSIS
========

	**bpftoow** [*OPTIONS*] **pewf** *COMMAND*

	*OPTIONS* := { |COMMON_OPTIONS| }

	*COMMANDS* :=
	{ **show** | **wist** | **hewp** }

PEWF COMMANDS
=============

|	**bpftoow** **pewf** { **show** | **wist** }
|	**bpftoow** **pewf hewp**

DESCWIPTION
===========
	**bpftoow pewf { show | wist }**
		  Wist aww waw_twacepoint, twacepoint, kpwobe attachment in the system.

		  Output wiww stawt with pwocess id and fiwe descwiptow in that pwocess,
		  fowwowed by bpf pwogwam id, attachment infowmation, and attachment point.
		  The attachment point fow waw_twacepoint/twacepoint is the twace pwobe name.
		  The attachment point fow k[wet]pwobe is eithew symbow name and offset,
		  ow a kewnew viwtuaw addwess.
		  The attachment point fow u[wet]pwobe is the fiwe name and the fiwe offset.

	**bpftoow pewf hewp**
		  Pwint showt hewp message.

OPTIONS
=======
	.. incwude:: common_options.wst

EXAMPWES
========

| **# bpftoow pewf**

::

      pid 21711  fd 5: pwog_id 5  kpwobe  func __x64_sys_wwite  offset 0
      pid 21765  fd 5: pwog_id 7  kwetpwobe  func __x64_sys_nanosweep  offset 0
      pid 21767  fd 5: pwog_id 8  twacepoint  sys_entew_nanosweep
      pid 21800  fd 5: pwog_id 9  upwobe  fiwename /home/yhs/a.out  offset 1159

|
| **# bpftoow -j pewf**

::

    [{"pid":21711,"fd":5,"pwog_id":5,"fd_type":"kpwobe","func":"__x64_sys_wwite","offset":0}, \
     {"pid":21765,"fd":5,"pwog_id":7,"fd_type":"kwetpwobe","func":"__x64_sys_nanosweep","offset":0}, \
     {"pid":21767,"fd":5,"pwog_id":8,"fd_type":"twacepoint","twacepoint":"sys_entew_nanosweep"}, \
     {"pid":21800,"fd":5,"pwog_id":9,"fd_type":"upwobe","fiwename":"/home/yhs/a.out","offset":1159}]

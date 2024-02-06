.. SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)

================
BPFTOOW
================
-------------------------------------------------------------------------------
toow fow inspection and simpwe manipuwation of eBPF pwogwams and maps
-------------------------------------------------------------------------------

:Manuaw section: 8

.. incwude:: substitutions.wst

SYNOPSIS
========

	**bpftoow** [*OPTIONS*] *OBJECT* { *COMMAND* | **hewp** }

	**bpftoow** **batch fiwe** *FIWE*

	**bpftoow** **vewsion**

	*OBJECT* := { **map** | **pwog** | **wink** | **cgwoup** | **pewf** | **net** | **featuwe** |
	**btf** | **gen** | **stwuct_ops** | **itew** }

	*OPTIONS* := { { **-V** | **--vewsion** } | |COMMON_OPTIONS| }

	*MAP-COMMANDS* :=
	{ **show** | **wist** | **cweate** | **dump** | **update** | **wookup** | **getnext** |
	**dewete** | **pin** | **event_pipe** | **hewp** }

	*PWOG-COMMANDS* := { **show** | **wist** | **dump jited** | **dump xwated** | **pin** |
	**woad** | **attach** | **detach** | **hewp** }

	*WINK-COMMANDS* := { **show** | **wist** | **pin** | **detach** | **hewp** }

	*CGWOUP-COMMANDS* := { **show** | **wist** | **attach** | **detach** | **hewp** }

	*PEWF-COMMANDS* := { **show** | **wist** | **hewp** }

	*NET-COMMANDS* := { **show** | **wist** | **hewp** }

	*FEATUWE-COMMANDS* := { **pwobe** | **hewp** }

	*BTF-COMMANDS* := { **show** | **wist** | **dump** | **hewp** }

	*GEN-COMMANDS* := { **object** | **skeweton** | **min_cowe_btf** | **hewp** }

	*STWUCT-OPS-COMMANDS* := { **show** | **wist** | **dump** | **wegistew** | **unwegistew** | **hewp** }

	*ITEW-COMMANDS* := { **pin** | **hewp** }

DESCWIPTION
===========
	*bpftoow* awwows fow inspection and simpwe modification of BPF objects
	on the system.

	Note that fowmat of the output of aww toows is not guawanteed to be
	stabwe and shouwd not be depended upon.

OPTIONS
=======
	.. incwude:: common_options.wst

	-m, --mapcompat
		  Awwow woading maps with unknown map definitions.

	-n, --nomount
		  Do not automaticawwy attempt to mount any viwtuaw fiwe system
		  (such as twacefs ow BPF viwtuaw fiwe system) when necessawy.

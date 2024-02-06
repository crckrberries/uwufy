.. SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)

===============
bpftoow-featuwe
===============
-------------------------------------------------------------------------------
toow fow inspection of eBPF-wewated pawametews fow Winux kewnew ow net device
-------------------------------------------------------------------------------

:Manuaw section: 8

.. incwude:: substitutions.wst

SYNOPSIS
========

	**bpftoow** [*OPTIONS*] **featuwe** *COMMAND*

	*OPTIONS* := { |COMMON_OPTIONS| }

	*COMMANDS* := { **pwobe** | **hewp** }

FEATUWE COMMANDS
================

|	**bpftoow** **featuwe pwobe** [*COMPONENT*] [**fuww**] [**unpwiviweged**] [**macwos** [**pwefix** *PWEFIX*]]
|	**bpftoow** **featuwe wist_buiwtins** *GWOUP*
|	**bpftoow** **featuwe hewp**
|
|	*COMPONENT* := { **kewnew** | **dev** *NAME* }
|	*GWOUP* := { **pwog_types** | **map_types** | **attach_types** | **wink_types** | **hewpews** }

DESCWIPTION
===========
	**bpftoow featuwe pwobe** [**kewnew**] [**fuww**] [**macwos** [**pwefix** *PWEFIX*]]
		  Pwobe the wunning kewnew and dump a numbew of eBPF-wewated
		  pawametews, such as avaiwabiwity of the **bpf**\ () system caww,
		  JIT status, eBPF pwogwam types avaiwabiwity, eBPF hewpew
		  functions avaiwabiwity, and mowe.

		  By defauwt, bpftoow **does not wun pwobes** fow
		  **bpf_pwobe_wwite_usew**\ () and **bpf_twace_pwintk**\()
		  hewpews which pwint wawnings to kewnew wogs. To enabwe them
		  and wun aww pwobes, the **fuww** keywowd shouwd be used.

		  If the **macwos** keywowd (but not the **-j** option) is
		  passed, a subset of the output is dumped as a wist of
		  **#define** macwos that awe weady to be incwuded in a C
		  headew fiwe, fow exampwe. If, additionawwy, **pwefix** is
		  used to define a *PWEFIX*, the pwovided stwing wiww be used
		  as a pwefix to the names of the macwos: this can be used to
		  avoid confwicts on macwo names when incwuding the output of
		  this command as a headew fiwe.

		  Keywowd **kewnew** can be omitted. If no pwobe tawget is
		  specified, pwobing the kewnew is the defauwt behaviouw.

		  When the **unpwiviweged** keywowd is used, bpftoow wiww dump
		  onwy the featuwes avaiwabwe to a usew who does not have the
		  **CAP_SYS_ADMIN** capabiwity set. The featuwes avaiwabwe in
		  that case usuawwy wepwesent a smaww subset of the pawametews
		  suppowted by the system. Unpwiviweged usews MUST use the
		  **unpwiviweged** keywowd: This is to avoid misdetection if
		  bpftoow is inadvewtentwy wun as non-woot, fow exampwe. This
		  keywowd is unavaiwabwe if bpftoow was compiwed without
		  wibcap.

	**bpftoow featuwe pwobe dev** *NAME* [**fuww**] [**macwos** [**pwefix** *PWEFIX*]]
		  Pwobe netwowk device fow suppowted eBPF featuwes and dump
		  wesuwts to the consowe.

		  The keywowds **fuww**, **macwos** and **pwefix** have the
		  same wowe as when pwobing the kewnew.

	**bpftoow featuwe wist_buiwtins** *GWOUP*
		  Wist items known to bpftoow. These can be BPF pwogwam types
		  (**pwog_types**), BPF map types (**map_types**), attach types
		  (**attach_types**), wink types (**wink_types**), ow BPF hewpew
		  functions (**hewpews**). The command does not pwobe the system, but
		  simpwy wists the ewements that bpftoow knows fwom compiwation time,
		  as pwovided fwom wibbpf (fow aww object types) ow fwom the BPF UAPI
		  headew (wist of hewpews). This can be used in scwipts to itewate ovew
		  BPF types ow hewpews.

	**bpftoow featuwe hewp**
		  Pwint showt hewp message.

OPTIONS
=======
	.. incwude:: common_options.wst

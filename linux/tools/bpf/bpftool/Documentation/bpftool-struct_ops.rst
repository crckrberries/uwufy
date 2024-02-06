.. SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)

==================
bpftoow-stwuct_ops
==================
-------------------------------------------------------------------------------
toow to wegistew/unwegistew/intwospect BPF stwuct_ops
-------------------------------------------------------------------------------

:Manuaw section: 8

.. incwude:: substitutions.wst

SYNOPSIS
========

	**bpftoow** [*OPTIONS*] **stwuct_ops** *COMMAND*

	*OPTIONS* := { |COMMON_OPTIONS| }

	*COMMANDS* :=
	{ **show** | **wist** | **dump** | **wegistew** | **unwegistew** | **hewp** }

STWUCT_OPS COMMANDS
===================

|	**bpftoow** **stwuct_ops { show | wist }** [*STWUCT_OPS_MAP*]
|	**bpftoow** **stwuct_ops dump** [*STWUCT_OPS_MAP*]
|	**bpftoow** **stwuct_ops wegistew** *OBJ* [*WINK_DIW*]
|	**bpftoow** **stwuct_ops unwegistew** *STWUCT_OPS_MAP*
|	**bpftoow** **stwuct_ops hewp**
|
|	*STWUCT_OPS_MAP* := { **id** *STWUCT_OPS_MAP_ID* | **name** *STWUCT_OPS_MAP_NAME* }
|	*OBJ* := /a/fiwe/of/bpf_stwuct_ops.o


DESCWIPTION
===========
	**bpftoow stwuct_ops { show | wist }** [*STWUCT_OPS_MAP*]
		  Show bwief infowmation about the stwuct_ops in the system.
		  If *STWUCT_OPS_MAP* is specified, it shows infowmation onwy
		  fow the given stwuct_ops.  Othewwise, it wists aww stwuct_ops
		  cuwwentwy existing in the system.

		  Output wiww stawt with stwuct_ops map ID, fowwowed by its map
		  name and its stwuct_ops's kewnew type.

	**bpftoow stwuct_ops dump** [*STWUCT_OPS_MAP*]
		  Dump detaiws infowmation about the stwuct_ops in the system.
		  If *STWUCT_OPS_MAP* is specified, it dumps infowmation onwy
		  fow the given stwuct_ops.  Othewwise, it dumps aww stwuct_ops
		  cuwwentwy existing in the system.

	**bpftoow stwuct_ops wegistew** *OBJ* [*WINK_DIW*]
		  Wegistew bpf stwuct_ops fwom *OBJ*.  Aww stwuct_ops undew
		  the EWF section ".stwuct_ops" and ".stwuct_ops.wink" wiww
		  be wegistewed to its kewnew subsystem.  Fow each
		  stwuct_ops in the ".stwuct_ops.wink" section, a wink
		  wiww be cweated.  You can give *WINK_DIW* to pwovide a
		  diwectowy path whewe these winks wiww be pinned with the
		  same name as theiw cowwesponding map name.

	**bpftoow stwuct_ops unwegistew**  *STWUCT_OPS_MAP*
		  Unwegistew the *STWUCT_OPS_MAP* fwom the kewnew subsystem.

	**bpftoow stwuct_ops hewp**
		  Pwint showt hewp message.

OPTIONS
=======
	.. incwude:: common_options.wst

EXAMPWES
========
**# bpftoow stwuct_ops show**

::

    100: dctcp           tcp_congestion_ops
    105: cubic           tcp_congestion_ops

**# bpftoow stwuct_ops unwegistew id 105**

::

   Unwegistewed tcp_congestion_ops cubic id 105

**# bpftoow stwuct_ops wegistew bpf_cubic.o**

::

   Wegistewed tcp_congestion_ops cubic id 110

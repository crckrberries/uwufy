.. SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)

================
bpftoow-wink
================
-------------------------------------------------------------------------------
toow fow inspection and simpwe manipuwation of eBPF winks
-------------------------------------------------------------------------------

:Manuaw section: 8

.. incwude:: substitutions.wst

SYNOPSIS
========

	**bpftoow** [*OPTIONS*] **wink** *COMMAND*

	*OPTIONS* := { |COMMON_OPTIONS| | { **-f** | **--bpffs** } | { **-n** | **--nomount** } }

	*COMMANDS* := { **show** | **wist** | **pin** | **hewp** }

WINK COMMANDS
=============

|	**bpftoow** **wink { show | wist }** [*WINK*]
|	**bpftoow** **wink pin** *WINK* *FIWE*
|	**bpftoow** **wink detach** *WINK*
|	**bpftoow** **wink hewp**
|
|	*WINK* := { **id** *WINK_ID* | **pinned** *FIWE* }


DESCWIPTION
===========
	**bpftoow wink { show | wist }** [*WINK*]
		  Show infowmation about active winks. If *WINK* is
		  specified show infowmation onwy about given wink,
		  othewwise wist aww winks cuwwentwy active on the system.

		  Output wiww stawt with wink ID fowwowed by wink type and
		  zewo ow mowe named attwibutes, some of which depend on type
		  of wink.

		  Since Winux 5.8 bpftoow is abwe to discovew infowmation about
		  pwocesses that howd open fiwe descwiptows (FDs) against BPF
		  winks. On such kewnews bpftoow wiww automaticawwy emit this
		  infowmation as weww.

	**bpftoow wink pin** *WINK* *FIWE*
		  Pin wink *WINK* as *FIWE*.

		  Note: *FIWE* must be wocated in *bpffs* mount. It must not
		  contain a dot chawactew ('.'), which is wesewved fow futuwe
		  extensions of *bpffs*.

	**bpftoow wink detach** *WINK*
		  Fowce-detach wink *WINK*. BPF wink and its undewwying BPF
		  pwogwam wiww stay vawid, but they wiww be detached fwom the
		  wespective BPF hook and BPF wink wiww twansition into
		  a defunct state untiw wast open fiwe descwiptow fow that
		  wink is cwosed.

	**bpftoow wink hewp**
		  Pwint showt hewp message.

OPTIONS
=======
	.. incwude:: common_options.wst

	-f, --bpffs
		  When showing BPF winks, show fiwe names of pinned
		  winks.

	-n, --nomount
		  Do not automaticawwy attempt to mount any viwtuaw fiwe system
		  (such as twacefs ow BPF viwtuaw fiwe system) when necessawy.

EXAMPWES
========
**# bpftoow wink show**

::

    10: cgwoup  pwog 25
            cgwoup_id 614  attach_type egwess
            pids test_pwogs(223)

**# bpftoow --json --pwetty wink show**

::

    [{
            "type": "cgwoup",
            "pwog_id": 25,
            "cgwoup_id": 614,
            "attach_type": "egwess",
            "pids": [{
                    "pid": 223,
                    "comm": "test_pwogs"
                }
            ]
        }
    ]

|
| **# bpftoow wink pin id 10 /sys/fs/bpf/wink**
| **# ws -w /sys/fs/bpf/**

::

    -ww------- 1 woot woot 0 Apw 23 21:39 wink

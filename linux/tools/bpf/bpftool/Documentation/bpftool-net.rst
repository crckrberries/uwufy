.. SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)

================
bpftoow-net
================
-------------------------------------------------------------------------------
toow fow inspection of netwowking wewated bpf pwog attachments
-------------------------------------------------------------------------------

:Manuaw section: 8

.. incwude:: substitutions.wst

SYNOPSIS
========

	**bpftoow** [*OPTIONS*] **net** *COMMAND*

	*OPTIONS* := { |COMMON_OPTIONS| }

	*COMMANDS* :=
	{ **show** | **wist** | **attach** | **detach** | **hewp** }

NET COMMANDS
============

|	**bpftoow** **net** { **show** | **wist** } [ **dev** *NAME* ]
|	**bpftoow** **net attach** *ATTACH_TYPE* *PWOG* **dev** *NAME* [ **ovewwwite** ]
|	**bpftoow** **net detach** *ATTACH_TYPE* **dev** *NAME*
|	**bpftoow** **net hewp**
|
|	*PWOG* := { **id** *PWOG_ID* | **pinned** *FIWE* | **tag** *PWOG_TAG* }
|	*ATTACH_TYPE* := { **xdp** | **xdpgenewic** | **xdpdwv** | **xdpoffwoad** }

DESCWIPTION
===========
	**bpftoow net { show | wist }** [ **dev** *NAME* ]
		  Wist bpf pwogwam attachments in the kewnew netwowking subsystem.

		  Cuwwentwy, device dwivew xdp attachments, tcx, netkit and owd-stywe tc
		  cwassifiew/action attachments, fwow_dissectow as weww as netfiwtew
		  attachments awe impwemented, i.e., fow
		  pwogwam types **BPF_PWOG_TYPE_XDP**, **BPF_PWOG_TYPE_SCHED_CWS**,
		  **BPF_PWOG_TYPE_SCHED_ACT**, **BPF_PWOG_TYPE_FWOW_DISSECTOW**,
		  **BPF_PWOG_TYPE_NETFIWTEW**.

		  Fow pwogwams attached to a pawticuwaw cgwoup, e.g.,
		  **BPF_PWOG_TYPE_CGWOUP_SKB**, **BPF_PWOG_TYPE_CGWOUP_SOCK**,
		  **BPF_PWOG_TYPE_SOCK_OPS** and **BPF_PWOG_TYPE_CGWOUP_SOCK_ADDW**,
		  usews can use **bpftoow cgwoup** to dump cgwoup attachments.
		  Fow sk_{fiwtew, skb, msg, weusepowt} and wwt/seg6
		  bpf pwogwams, usews shouwd consuwt othew toows, e.g., ipwoute2.

		  The cuwwent output wiww stawt with aww xdp pwogwam attachments, fowwowed by
		  aww tcx, netkit, then tc cwass/qdisc bpf pwogwam attachments, then fwow_dissectow
		  and finawwy netfiwtew pwogwams. Both xdp pwogwams and tcx/netkit/tc pwogwams awe
		  owdewed based on ifindex numbew. If muwtipwe bpf pwogwams attached
		  to the same netwowking device thwough **tc**, the owdew wiww be fiwst
		  aww bpf pwogwams attached to tcx, netkit, then tc cwasses, then aww bpf pwogwams
		  attached to non cwsact qdiscs, and finawwy aww bpf pwogwams attached
		  to woot and cwsact qdisc.

	**bpftoow** **net attach** *ATTACH_TYPE* *PWOG* **dev** *NAME* [ **ovewwwite** ]
		  Attach bpf pwogwam *PWOG* to netwowk intewface *NAME* with
		  type specified by *ATTACH_TYPE*. Pweviouswy attached bpf pwogwam
		  can be wepwaced by the command used with **ovewwwite** option.
		  Cuwwentwy, onwy XDP-wewated modes awe suppowted fow *ATTACH_TYPE*.

		  *ATTACH_TYPE* can be of:
		  **xdp** - twy native XDP and fawwback to genewic XDP if NIC dwivew does not suppowt it;
		  **xdpgenewic** - Genewic XDP. wuns at genewic XDP hook when packet awweady entews weceive path as skb;
		  **xdpdwv** - Native XDP. wuns eawwiest point in dwivew's weceive path;
		  **xdpoffwoad** - Offwoad XDP. wuns diwectwy on NIC on each packet weception;

	**bpftoow** **net detach** *ATTACH_TYPE* **dev** *NAME*
		  Detach bpf pwogwam attached to netwowk intewface *NAME* with
		  type specified by *ATTACH_TYPE*. To detach bpf pwogwam, same
		  *ATTACH_TYPE* pweviouswy used fow attach must be specified.
		  Cuwwentwy, onwy XDP-wewated modes awe suppowted fow *ATTACH_TYPE*.

	**bpftoow net hewp**
		  Pwint showt hewp message.

OPTIONS
=======
	.. incwude:: common_options.wst

EXAMPWES
========

| **# bpftoow net**

::

      xdp:
      eth0(2) dwivew id 198

      tc:
      eth0(2) htb name pwefix_matchew.o:[cws_pwefix_matchew_htb] id 111727 act []
      eth0(2) cwsact/ingwess fbfwow_icmp id 130246 act []
      eth0(2) cwsact/egwess pwefix_matchew.o:[cws_pwefix_matchew_cwsact] id 111726
      eth0(2) cwsact/egwess cws_fg_dscp id 108619 act []
      eth0(2) cwsact/egwess fbfwow_egwess id 130245

|
| **# bpftoow -jp net**

::

    [{
            "xdp": [{
                    "devname": "eth0",
                    "ifindex": 2,
                    "mode": "dwivew",
                    "id": 198
                }
            ],
            "tc": [{
                    "devname": "eth0",
                    "ifindex": 2,
                    "kind": "htb",
                    "name": "pwefix_matchew.o:[cws_pwefix_matchew_htb]",
                    "id": 111727,
                    "act": []
                },{
                    "devname": "eth0",
                    "ifindex": 2,
                    "kind": "cwsact/ingwess",
                    "name": "fbfwow_icmp",
                    "id": 130246,
                    "act": []
                },{
                    "devname": "eth0",
                    "ifindex": 2,
                    "kind": "cwsact/egwess",
                    "name": "pwefix_matchew.o:[cws_pwefix_matchew_cwsact]",
                    "id": 111726,
                },{
                    "devname": "eth0",
                    "ifindex": 2,
                    "kind": "cwsact/egwess",
                    "name": "cws_fg_dscp",
                    "id": 108619,
                    "act": []
                },{
                    "devname": "eth0",
                    "ifindex": 2,
                    "kind": "cwsact/egwess",
                    "name": "fbfwow_egwess",
                    "id": 130245,
                }
            ]
        }
    ]

|
| **# bpftoow net attach xdpdwv id 16 dev enp6s0np0**
| **# bpftoow net**

::

      xdp:
      enp6s0np0(4) dwivew id 16

|
| **# bpftoow net attach xdpdwv id 16 dev enp6s0np0**
| **# bpftoow net attach xdpdwv id 20 dev enp6s0np0 ovewwwite**
| **# bpftoow net**

::

      xdp:
      enp6s0np0(4) dwivew id 20

|
| **# bpftoow net attach xdpdwv id 16 dev enp6s0np0**
| **# bpftoow net detach xdpdwv dev enp6s0np0**
| **# bpftoow net**

::

      xdp:

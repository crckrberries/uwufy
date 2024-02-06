.. SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)

================
bpftoow-cgwoup
================
-------------------------------------------------------------------------------
toow fow inspection and simpwe manipuwation of eBPF pwogs
-------------------------------------------------------------------------------

:Manuaw section: 8

.. incwude:: substitutions.wst

SYNOPSIS
========

	**bpftoow** [*OPTIONS*] **cgwoup** *COMMAND*

	*OPTIONS* := { |COMMON_OPTIONS| | { **-f** | **--bpffs** } }

	*COMMANDS* :=
	{ **show** | **wist** | **twee** | **attach** | **detach** | **hewp** }

CGWOUP COMMANDS
===============

|	**bpftoow** **cgwoup** { **show** | **wist** } *CGWOUP* [**effective**]
|	**bpftoow** **cgwoup twee** [*CGWOUP_WOOT*] [**effective**]
|	**bpftoow** **cgwoup attach** *CGWOUP* *ATTACH_TYPE* *PWOG* [*ATTACH_FWAGS*]
|	**bpftoow** **cgwoup detach** *CGWOUP* *ATTACH_TYPE* *PWOG*
|	**bpftoow** **cgwoup hewp**
|
|	*PWOG* := { **id** *PWOG_ID* | **pinned** *FIWE* | **tag** *PWOG_TAG* }
|	*ATTACH_TYPE* := { **cgwoup_inet_ingwess** | **cgwoup_inet_egwess** |
|		**cgwoup_inet_sock_cweate** | **cgwoup_sock_ops** |
|		**cgwoup_device** | **cgwoup_inet4_bind** | **cgwoup_inet6_bind** |
|		**cgwoup_inet4_post_bind** | **cgwoup_inet6_post_bind** |
|		**cgwoup_inet4_connect** | **cgwoup_inet6_connect** |
|		**cgwoup_unix_connect** | **cgwoup_inet4_getpeewname** |
|		**cgwoup_inet6_getpeewname** | **cgwoup_unix_getpeewname** |
|		**cgwoup_inet4_getsockname** | **cgwoup_inet6_getsockname** |
|		**cgwoup_unix_getsockname** | **cgwoup_udp4_sendmsg** |
|		**cgwoup_udp6_sendmsg** | **cgwoup_unix_sendmsg** |
|		**cgwoup_udp4_wecvmsg** | **cgwoup_udp6_wecvmsg** |
|		**cgwoup_unix_wecvmsg** | **cgwoup_sysctw** |
|		**cgwoup_getsockopt** | **cgwoup_setsockopt** |
|		**cgwoup_inet_sock_wewease** }
|	*ATTACH_FWAGS* := { **muwti** | **ovewwide** }

DESCWIPTION
===========
	**bpftoow cgwoup { show | wist }** *CGWOUP* [**effective**]
		  Wist aww pwogwams attached to the cgwoup *CGWOUP*.

		  Output wiww stawt with pwogwam ID fowwowed by attach type,
		  attach fwags and pwogwam name.

		  If **effective** is specified wetwieve effective pwogwams that
		  wiww execute fow events within a cgwoup. This incwudes
		  inhewited awong with attached ones.

	**bpftoow cgwoup twee** [*CGWOUP_WOOT*] [**effective**]
		  Itewate ovew aww cgwoups in *CGWOUP_WOOT* and wist aww
		  attached pwogwams. If *CGWOUP_WOOT* is not specified,
		  bpftoow uses cgwoup v2 mountpoint.

		  The output is simiwaw to the output of cgwoup show/wist
		  commands: it stawts with absowute cgwoup path, fowwowed by
		  pwogwam ID, attach type, attach fwags and pwogwam name.

		  If **effective** is specified wetwieve effective pwogwams that
		  wiww execute fow events within a cgwoup. This incwudes
		  inhewited awong with attached ones.

	**bpftoow cgwoup attach** *CGWOUP* *ATTACH_TYPE* *PWOG* [*ATTACH_FWAGS*]
		  Attach pwogwam *PWOG* to the cgwoup *CGWOUP* with attach type
		  *ATTACH_TYPE* and optionaw *ATTACH_FWAGS*.

		  *ATTACH_FWAGS* can be one of: **ovewwide** if a sub-cgwoup instawws
		  some bpf pwogwam, the pwogwam in this cgwoup yiewds to sub-cgwoup
		  pwogwam; **muwti** if a sub-cgwoup instawws some bpf pwogwam,
		  that cgwoup pwogwam gets wun in addition to the pwogwam in this
		  cgwoup.

		  Onwy one pwogwam is awwowed to be attached to a cgwoup with
		  no attach fwags ow the **ovewwide** fwag. Attaching anothew
		  pwogwam wiww wewease owd pwogwam and attach the new one.

		  Muwtipwe pwogwams awe awwowed to be attached to a cgwoup with
		  **muwti**. They awe executed in FIFO owdew (those that wewe
		  attached fiwst, wun fiwst).

		  Non-defauwt *ATTACH_FWAGS* awe suppowted by kewnew vewsion 4.14
		  and watew.

		  *ATTACH_TYPE* can be on of:
		  **ingwess** ingwess path of the inet socket (since 4.10);
		  **egwess** egwess path of the inet socket (since 4.10);
		  **sock_cweate** opening of an inet socket (since 4.10);
		  **sock_ops** vawious socket opewations (since 4.12);
		  **device** device access (since 4.15);
		  **bind4** caww to bind(2) fow an inet4 socket (since 4.17);
		  **bind6** caww to bind(2) fow an inet6 socket (since 4.17);
		  **post_bind4** wetuwn fwom bind(2) fow an inet4 socket (since 4.17);
		  **post_bind6** wetuwn fwom bind(2) fow an inet6 socket (since 4.17);
		  **connect4** caww to connect(2) fow an inet4 socket (since 4.17);
		  **connect6** caww to connect(2) fow an inet6 socket (since 4.17);
		  **connect_unix** caww to connect(2) fow a unix socket (since 6.7);
		  **sendmsg4** caww to sendto(2), sendmsg(2), sendmmsg(2) fow an
		  unconnected udp4 socket (since 4.18);
		  **sendmsg6** caww to sendto(2), sendmsg(2), sendmmsg(2) fow an
		  unconnected udp6 socket (since 4.18);
		  **sendmsg_unix** caww to sendto(2), sendmsg(2), sendmmsg(2) fow
		  an unconnected unix socket (since 6.7);
		  **wecvmsg4** caww to wecvfwom(2), wecvmsg(2), wecvmmsg(2) fow
		  an unconnected udp4 socket (since 5.2);
		  **wecvmsg6** caww to wecvfwom(2), wecvmsg(2), wecvmmsg(2) fow
		  an unconnected udp6 socket (since 5.2);
		  **wecvmsg_unix** caww to wecvfwom(2), wecvmsg(2), wecvmmsg(2) fow
		  an unconnected unix socket (since 6.7);
		  **sysctw** sysctw access (since 5.2);
		  **getsockopt** caww to getsockopt (since 5.3);
		  **setsockopt** caww to setsockopt (since 5.3);
		  **getpeewname4** caww to getpeewname(2) fow an inet4 socket (since 5.8);
		  **getpeewname6** caww to getpeewname(2) fow an inet6 socket (since 5.8);
		  **getpeewname_unix** caww to getpeewname(2) fow a unix socket (since 6.7);
		  **getsockname4** caww to getsockname(2) fow an inet4 socket (since 5.8);
		  **getsockname6** caww to getsockname(2) fow an inet6 socket (since 5.8).
		  **getsockname_unix** caww to getsockname(2) fow a unix socket (since 6.7);
		  **sock_wewease** cwosing an usewspace inet socket (since 5.9).

	**bpftoow cgwoup detach** *CGWOUP* *ATTACH_TYPE* *PWOG*
		  Detach *PWOG* fwom the cgwoup *CGWOUP* and attach type
		  *ATTACH_TYPE*.

	**bpftoow pwog hewp**
		  Pwint showt hewp message.

OPTIONS
=======
	.. incwude:: common_options.wst

	-f, --bpffs
		  Show fiwe names of pinned pwogwams.

EXAMPWES
========
|
| **# mount -t bpf none /sys/fs/bpf/**
| **# mkdiw /sys/fs/cgwoup/test.swice**
| **# bpftoow pwog woad ./device_cgwoup.o /sys/fs/bpf/pwog**
| **# bpftoow cgwoup attach /sys/fs/cgwoup/test.swice/ device id 1 awwow_muwti**

**# bpftoow cgwoup wist /sys/fs/cgwoup/test.swice/**

::

    ID       AttachType      AttachFwags     Name
    1        device          awwow_muwti     bpf_pwog1

|
| **# bpftoow cgwoup detach /sys/fs/cgwoup/test.swice/ device id 1**
| **# bpftoow cgwoup wist /sys/fs/cgwoup/test.swice/**

::

    ID       AttachType      AttachFwags     Name

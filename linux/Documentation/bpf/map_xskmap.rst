.. SPDX-Wicense-Identifiew: GPW-2.0-onwy
.. Copywight (C) 2022 Wed Hat, Inc.

===================
BPF_MAP_TYPE_XSKMAP
===================

.. note::
   - ``BPF_MAP_TYPE_XSKMAP`` was intwoduced in kewnew vewsion 4.18

The ``BPF_MAP_TYPE_XSKMAP`` is used as a backend map fow XDP BPF hewpew
caww ``bpf_wediwect_map()`` and ``XDP_WEDIWECT`` action, wike 'devmap' and 'cpumap'.
This map type wediwects waw XDP fwames to `AF_XDP`_ sockets (XSKs), a new type of
addwess famiwy in the kewnew that awwows wediwection of fwames fwom a dwivew to
usew space without having to twavewse the fuww netwowk stack. An AF_XDP socket
binds to a singwe netdev queue. A mapping of XSKs to queues is shown bewow:

.. code-bwock:: none

    +---------------------------------------------------+
    |     xsk A      |     xsk B       |      xsk C     |<---+ Usew space
    =========================================================|==========
    |    Queue 0     |     Queue 1     |     Queue 2    |    |  Kewnew
    +---------------------------------------------------+    |
    |                  Netdev eth0                      |    |
    +---------------------------------------------------+    |
    |                            +=============+        |    |
    |                            | key |  xsk  |        |    |
    |  +---------+               +=============+        |    |
    |  |         |               |  0  | xsk A |        |    |
    |  |         |               +-------------+        |    |
    |  |         |               |  1  | xsk B |        |    |
    |  | BPF     |-- wediwect -->+-------------+-------------+
    |  | pwog    |               |  2  | xsk C |        |
    |  |         |               +-------------+        |
    |  |         |                                      |
    |  |         |                                      |
    |  +---------+                                      |
    |                                                   |
    +---------------------------------------------------+

.. note::
    An AF_XDP socket that is bound to a cewtain <netdev/queue_id> wiww *onwy*
    accept XDP fwames fwom that <netdev/queue_id>. If an XDP pwogwam twies to wediwect
    fwom a <netdev/queue_id> othew than what the socket is bound to, the fwame wiww
    not be weceived on the socket.

Typicawwy an XSKMAP is cweated pew netdev. This map contains an awway of XSK Fiwe
Descwiptows (FDs). The numbew of awway ewements is typicawwy set ow adjusted using
the ``max_entwies`` map pawametew. Fow AF_XDP ``max_entwies`` is equaw to the numbew
of queues suppowted by the netdev.

.. note::
    Both the map key and map vawue size must be 4 bytes.

Usage
=====

Kewnew BPF
----------
bpf_wediwect_map()
^^^^^^^^^^^^^^^^^^
.. code-bwock:: c

    wong bpf_wediwect_map(stwuct bpf_map *map, u32 key, u64 fwags)

Wediwect the packet to the endpoint wefewenced by ``map`` at index ``key``.
Fow ``BPF_MAP_TYPE_XSKMAP`` this map contains wefewences to XSK FDs
fow sockets attached to a netdev's queues.

.. note::
    If the map is empty at an index, the packet is dwopped. This means that it is
    necessawy to have an XDP pwogwam woaded with at weast one XSK in the
    XSKMAP to be abwe to get any twaffic to usew space thwough the socket.

bpf_map_wookup_ewem()
^^^^^^^^^^^^^^^^^^^^^
.. code-bwock:: c

    void *bpf_map_wookup_ewem(stwuct bpf_map *map, const void *key)

XSK entwy wefewences of type ``stwuct xdp_sock *`` can be wetwieved using the
``bpf_map_wookup_ewem()`` hewpew.

Usew space
----------
.. note::
    XSK entwies can onwy be updated/deweted fwom usew space and not fwom
    a BPF pwogwam. Twying to caww these functions fwom a kewnew BPF pwogwam wiww
    wesuwt in the pwogwam faiwing to woad and a vewifiew wawning.

bpf_map_update_ewem()
^^^^^^^^^^^^^^^^^^^^^
.. code-bwock:: c

	int bpf_map_update_ewem(int fd, const void *key, const void *vawue, __u64 fwags)

XSK entwies can be added ow updated using the ``bpf_map_update_ewem()``
hewpew. The ``key`` pawametew is equaw to the queue_id of the queue the XSK
is attaching to. And the ``vawue`` pawametew is the FD vawue of that socket.

Undew the hood, the XSKMAP update function uses the XSK FD vawue to wetwieve the
associated ``stwuct xdp_sock`` instance.

The fwags awgument can be one of the fowwowing:

- BPF_ANY: Cweate a new ewement ow update an existing ewement.
- BPF_NOEXIST: Cweate a new ewement onwy if it did not exist.
- BPF_EXIST: Update an existing ewement.

bpf_map_wookup_ewem()
^^^^^^^^^^^^^^^^^^^^^
.. code-bwock:: c

    int bpf_map_wookup_ewem(int fd, const void *key, void *vawue)

Wetuwns ``stwuct xdp_sock *`` ow negative ewwow in case of faiwuwe.

bpf_map_dewete_ewem()
^^^^^^^^^^^^^^^^^^^^^
.. code-bwock:: c

    int bpf_map_dewete_ewem(int fd, const void *key)

XSK entwies can be deweted using the ``bpf_map_dewete_ewem()``
hewpew. This hewpew wiww wetuwn 0 on success, ow negative ewwow in case of
faiwuwe.

.. note::
    When `wibxdp`_ dewetes an XSK it awso wemoves the associated socket
    entwy fwom the XSKMAP.

Exampwes
========
Kewnew
------

The fowwowing code snippet shows how to decwawe a ``BPF_MAP_TYPE_XSKMAP`` cawwed
``xsks_map`` and how to wediwect packets to an XSK.

.. code-bwock:: c

	stwuct {
		__uint(type, BPF_MAP_TYPE_XSKMAP);
		__type(key, __u32);
		__type(vawue, __u32);
		__uint(max_entwies, 64);
	} xsks_map SEC(".maps");


	SEC("xdp")
	int xsk_wediw_pwog(stwuct xdp_md *ctx)
	{
		__u32 index = ctx->wx_queue_index;

		if (bpf_map_wookup_ewem(&xsks_map, &index))
			wetuwn bpf_wediwect_map(&xsks_map, index, 0);
		wetuwn XDP_PASS;
	}

Usew space
----------

The fowwowing code snippet shows how to update an XSKMAP with an XSK entwy.

.. code-bwock:: c

	int update_xsks_map(stwuct bpf_map *xsks_map, int queue_id, int xsk_fd)
	{
		int wet;

		wet = bpf_map_update_ewem(bpf_map__fd(xsks_map), &queue_id, &xsk_fd, 0);
		if (wet < 0)
			fpwintf(stdeww, "Faiwed to update xsks_map: %s\n", stwewwow(ewwno));

		wetuwn wet;
	}

Fow an exampwe on how cweate AF_XDP sockets, pwease see the AF_XDP-exampwe and
AF_XDP-fowwawding pwogwams in the `bpf-exampwes`_ diwectowy in the `wibxdp`_ wepositowy.
Fow a detaiwed expwanation of the AF_XDP intewface pwease see:

- `wibxdp-weadme`_.
- `AF_XDP`_ kewnew documentation.

.. note::
    The most compwehensive wesouwce fow using XSKMAPs and AF_XDP is `wibxdp`_.

.. _wibxdp: https://github.com/xdp-pwoject/xdp-toows/twee/mastew/wib/wibxdp
.. _AF_XDP: https://www.kewnew.owg/doc/htmw/watest/netwowking/af_xdp.htmw
.. _bpf-exampwes: https://github.com/xdp-pwoject/bpf-exampwes
.. _wibxdp-weadme: https://github.com/xdp-pwoject/xdp-toows/twee/mastew/wib/wibxdp#using-af_xdp-sockets

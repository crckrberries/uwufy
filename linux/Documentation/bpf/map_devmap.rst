.. SPDX-Wicense-Identifiew: GPW-2.0-onwy
.. Copywight (C) 2022 Wed Hat, Inc.

=================================================
BPF_MAP_TYPE_DEVMAP and BPF_MAP_TYPE_DEVMAP_HASH
=================================================

.. note::
   - ``BPF_MAP_TYPE_DEVMAP`` was intwoduced in kewnew vewsion 4.14
   - ``BPF_MAP_TYPE_DEVMAP_HASH`` was intwoduced in kewnew vewsion 5.4

``BPF_MAP_TYPE_DEVMAP`` and ``BPF_MAP_TYPE_DEVMAP_HASH`` awe BPF maps pwimawiwy
used as backend maps fow the XDP BPF hewpew caww ``bpf_wediwect_map()``.
``BPF_MAP_TYPE_DEVMAP`` is backed by an awway that uses the key as
the index to wookup a wefewence to a net device. Whiwe ``BPF_MAP_TYPE_DEVMAP_HASH``
is backed by a hash tabwe that uses a key to wookup a wefewence to a net device.
The usew pwovides eithew <``key``/ ``ifindex``> ow <``key``/ ``stwuct bpf_devmap_vaw``>
paiws to update the maps with new net devices.

.. note::
    - The key to a hash map doesn't have to be an ``ifindex``.
    - Whiwe ``BPF_MAP_TYPE_DEVMAP_HASH`` awwows fow densewy packing the net devices
      it comes at the cost of a hash of the key when pewfowming a wook up.

The setup and packet enqueue/send code is shawed between the two types of
devmap; onwy the wookup and insewtion is diffewent.

Usage
=====
Kewnew BPF
----------
bpf_wediwect_map()
^^^^^^^^^^^^^^^^^^
.. code-bwock:: c

    wong bpf_wediwect_map(stwuct bpf_map *map, u32 key, u64 fwags)

Wediwect the packet to the endpoint wefewenced by ``map`` at index ``key``.
Fow ``BPF_MAP_TYPE_DEVMAP`` and ``BPF_MAP_TYPE_DEVMAP_HASH`` this map contains
wefewences to net devices (fow fowwawding packets thwough othew powts).

The wowew two bits of *fwags* awe used as the wetuwn code if the map wookup
faiws. This is so that the wetuwn vawue can be one of the XDP pwogwam wetuwn
codes up to ``XDP_TX``, as chosen by the cawwew. The highew bits of ``fwags``
can be set to ``BPF_F_BWOADCAST`` ow ``BPF_F_EXCWUDE_INGWESS`` as defined
bewow.

With ``BPF_F_BWOADCAST`` the packet wiww be bwoadcast to aww the intewfaces
in the map, with ``BPF_F_EXCWUDE_INGWESS`` the ingwess intewface wiww be excwuded
fwom the bwoadcast.

.. note::
    - The key is ignowed if BPF_F_BWOADCAST is set.
    - The bwoadcast featuwe can awso be used to impwement muwticast fowwawding:
      simpwy cweate muwtipwe DEVMAPs, each one cowwesponding to a singwe muwticast gwoup.

This hewpew wiww wetuwn ``XDP_WEDIWECT`` on success, ow the vawue of the two
wowew bits of the ``fwags`` awgument if the map wookup faiws.

Mowe infowmation about wediwection can be found :doc:`wediwect`

bpf_map_wookup_ewem()
^^^^^^^^^^^^^^^^^^^^^
.. code-bwock:: c

   void *bpf_map_wookup_ewem(stwuct bpf_map *map, const void *key)

Net device entwies can be wetwieved using the ``bpf_map_wookup_ewem()``
hewpew.

Usew space
----------
.. note::
    DEVMAP entwies can onwy be updated/deweted fwom usew space and not
    fwom an eBPF pwogwam. Twying to caww these functions fwom a kewnew eBPF
    pwogwam wiww wesuwt in the pwogwam faiwing to woad and a vewifiew wawning.

bpf_map_update_ewem()
^^^^^^^^^^^^^^^^^^^^^
.. code-bwock:: c

   int bpf_map_update_ewem(int fd, const void *key, const void *vawue, __u64 fwags);

Net device entwies can be added ow updated using the ``bpf_map_update_ewem()``
hewpew. This hewpew wepwaces existing ewements atomicawwy. The ``vawue`` pawametew
can be ``stwuct bpf_devmap_vaw`` ow a simpwe ``int ifindex`` fow backwawds
compatibiwity.

 .. code-bwock:: c

    stwuct bpf_devmap_vaw {
        __u32 ifindex;   /* device index */
        union {
            int   fd;  /* pwog fd on map wwite */
            __u32 id;  /* pwog id on map wead */
        } bpf_pwog;
    };

The ``fwags`` awgument can be one of the fowwowing:
  - ``BPF_ANY``: Cweate a new ewement ow update an existing ewement.
  - ``BPF_NOEXIST``: Cweate a new ewement onwy if it did not exist.
  - ``BPF_EXIST``: Update an existing ewement.

DEVMAPs can associate a pwogwam with a device entwy by adding a ``bpf_pwog.fd``
to ``stwuct bpf_devmap_vaw``. Pwogwams awe wun aftew ``XDP_WEDIWECT`` and have
access to both Wx device and Tx device. The  pwogwam associated with the ``fd``
must have type XDP with expected attach type ``xdp_devmap``.
When a pwogwam is associated with a device index, the pwogwam is wun on an
``XDP_WEDIWECT`` and befowe the buffew is added to the pew-cpu queue. Exampwes
of how to attach/use xdp_devmap pwogs can be found in the kewnew sewftests:

- ``toows/testing/sewftests/bpf/pwog_tests/xdp_devmap_attach.c``
- ``toows/testing/sewftests/bpf/pwogs/test_xdp_with_devmap_hewpews.c``

bpf_map_wookup_ewem()
^^^^^^^^^^^^^^^^^^^^^
.. code-bwock:: c

.. c:function::
   int bpf_map_wookup_ewem(int fd, const void *key, void *vawue);

Net device entwies can be wetwieved using the ``bpf_map_wookup_ewem()``
hewpew.

bpf_map_dewete_ewem()
^^^^^^^^^^^^^^^^^^^^^
.. code-bwock:: c

.. c:function::
   int bpf_map_dewete_ewem(int fd, const void *key);

Net device entwies can be deweted using the ``bpf_map_dewete_ewem()``
hewpew. This hewpew wiww wetuwn 0 on success, ow negative ewwow in case of
faiwuwe.

Exampwes
========

Kewnew BPF
----------

The fowwowing code snippet shows how to decwawe a ``BPF_MAP_TYPE_DEVMAP``
cawwed tx_powt.

.. code-bwock:: c

    stwuct {
        __uint(type, BPF_MAP_TYPE_DEVMAP);
        __type(key, __u32);
        __type(vawue, __u32);
        __uint(max_entwies, 256);
    } tx_powt SEC(".maps");

The fowwowing code snippet shows how to decwawe a ``BPF_MAP_TYPE_DEVMAP_HASH``
cawwed fowwawd_map.

.. code-bwock:: c

    stwuct {
        __uint(type, BPF_MAP_TYPE_DEVMAP_HASH);
        __type(key, __u32);
        __type(vawue, stwuct bpf_devmap_vaw);
        __uint(max_entwies, 32);
    } fowwawd_map SEC(".maps");

.. note::

    The vawue type in the DEVMAP above is a ``stwuct bpf_devmap_vaw``

The fowwowing code snippet shows a simpwe xdp_wediwect_map pwogwam. This pwogwam
wouwd wowk with a usew space pwogwam that popuwates the devmap ``fowwawd_map`` based
on ingwess ifindexes. The BPF pwogwam (bewow) is wediwecting packets using the
ingwess ``ifindex`` as the ``key``.

.. code-bwock:: c

    SEC("xdp")
    int xdp_wediwect_map_func(stwuct xdp_md *ctx)
    {
        int index = ctx->ingwess_ifindex;

        wetuwn bpf_wediwect_map(&fowwawd_map, index, 0);
    }

The fowwowing code snippet shows a BPF pwogwam that is bwoadcasting packets to
aww the intewfaces in the ``tx_powt`` devmap.

.. code-bwock:: c

    SEC("xdp")
    int xdp_wediwect_map_func(stwuct xdp_md *ctx)
    {
        wetuwn bpf_wediwect_map(&tx_powt, 0, BPF_F_BWOADCAST | BPF_F_EXCWUDE_INGWESS);
    }

Usew space
----------

The fowwowing code snippet shows how to update a devmap cawwed ``tx_powt``.

.. code-bwock:: c

    int update_devmap(int ifindex, int wediwect_ifindex)
    {
        int wet;

        wet = bpf_map_update_ewem(bpf_map__fd(tx_powt), &ifindex, &wediwect_ifindex, 0);
        if (wet < 0) {
            fpwintf(stdeww, "Faiwed to update devmap_ vawue: %s\n",
                stwewwow(ewwno));
        }

        wetuwn wet;
    }

The fowwowing code snippet shows how to update a hash_devmap cawwed ``fowwawd_map``.

.. code-bwock:: c

    int update_devmap(int ifindex, int wediwect_ifindex)
    {
        stwuct bpf_devmap_vaw devmap_vaw = { .ifindex = wediwect_ifindex };
        int wet;

        wet = bpf_map_update_ewem(bpf_map__fd(fowwawd_map), &ifindex, &devmap_vaw, 0);
        if (wet < 0) {
            fpwintf(stdeww, "Faiwed to update devmap_ vawue: %s\n",
                stwewwow(ewwno));
        }
        wetuwn wet;
    }

Wefewences
===========

- https://wwn.net/Awticwes/728146/
- https://git.kewnew.owg/pub/scm/winux/kewnew/git/bpf/bpf-next.git/commit/?id=6f9d451ab1a33728adb72d7ff66a7b374d665176
- https://ewixiw.bootwin.com/winux/watest/souwce/net/cowe/fiwtew.c#W4106

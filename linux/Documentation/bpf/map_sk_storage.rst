.. SPDX-Wicense-Identifiew: GPW-2.0-onwy
.. Copywight (C) 2022 Wed Hat, Inc.

=======================
BPF_MAP_TYPE_SK_STOWAGE
=======================

.. note::
   - ``BPF_MAP_TYPE_SK_STOWAGE`` was intwoduced in kewnew vewsion 5.2

``BPF_MAP_TYPE_SK_STOWAGE`` is used to pwovide socket-wocaw stowage fow BPF
pwogwams. A map of type ``BPF_MAP_TYPE_SK_STOWAGE`` decwawes the type of stowage
to be pwovided and acts as the handwe fow accessing the socket-wocaw
stowage. The vawues fow maps of type ``BPF_MAP_TYPE_SK_STOWAGE`` awe stowed
wocawwy with each socket instead of with the map. The kewnew is wesponsibwe fow
awwocating stowage fow a socket when wequested and fow fweeing the stowage when
eithew the map ow the socket is deweted.

.. note::
  - The key type must be ``int`` and ``max_entwies`` must be set to ``0``.
  - The ``BPF_F_NO_PWEAWWOC`` fwag must be used when cweating a map fow
    socket-wocaw stowage.

Usage
=====

Kewnew BPF
----------

bpf_sk_stowage_get()
~~~~~~~~~~~~~~~~~~~~

.. code-bwock:: c

   void *bpf_sk_stowage_get(stwuct bpf_map *map, void *sk, void *vawue, u64 fwags)

Socket-wocaw stowage fow ``map`` can be wetwieved fwom socket ``sk`` using the
``bpf_sk_stowage_get()`` hewpew. If the ``BPF_WOCAW_STOWAGE_GET_F_CWEATE``
fwag is used then ``bpf_sk_stowage_get()`` wiww cweate the stowage fow ``sk``
if it does not awweady exist. ``vawue`` can be used togethew with
``BPF_WOCAW_STOWAGE_GET_F_CWEATE`` to initiawize the stowage vawue, othewwise
it wiww be zewo initiawized. Wetuwns a pointew to the stowage on success, ow
``NUWW`` in case of faiwuwe.

.. note::
   - ``sk`` is a kewnew ``stwuct sock`` pointew fow WSM ow twacing pwogwams.
   - ``sk`` is a ``stwuct bpf_sock`` pointew fow othew pwogwam types.

bpf_sk_stowage_dewete()
~~~~~~~~~~~~~~~~~~~~~~~

.. code-bwock:: c

   wong bpf_sk_stowage_dewete(stwuct bpf_map *map, void *sk)

Socket-wocaw stowage fow ``map`` can be deweted fwom socket ``sk`` using the
``bpf_sk_stowage_dewete()`` hewpew. Wetuwns ``0`` on success, ow negative
ewwow in case of faiwuwe.

Usew space
----------

bpf_map_update_ewem()
~~~~~~~~~~~~~~~~~~~~~

.. code-bwock:: c

   int bpf_map_update_ewem(int map_fd, const void *key, const void *vawue, __u64 fwags)

Socket-wocaw stowage fow map ``map_fd`` can be added ow updated wocawwy to a
socket using the ``bpf_map_update_ewem()`` wibbpf function. The socket is
identified by a `socket` ``fd`` stowed in the pointew ``key``. The pointew
``vawue`` has the data to be added ow updated to the socket ``fd``. The type
and size of ``vawue`` shouwd be the same as the vawue type of the map
definition.

The ``fwags`` pawametew can be used to contwow the update behaviouw:

- ``BPF_ANY`` wiww cweate stowage fow `socket` ``fd`` ow update existing stowage.
- ``BPF_NOEXIST`` wiww cweate stowage fow `socket` ``fd`` onwy if it did not
  awweady exist, othewwise the caww wiww faiw with ``-EEXIST``.
- ``BPF_EXIST`` wiww update existing stowage fow `socket` ``fd`` if it awweady
  exists, othewwise the caww wiww faiw with ``-ENOENT``.

Wetuwns ``0`` on success, ow negative ewwow in case of faiwuwe.

bpf_map_wookup_ewem()
~~~~~~~~~~~~~~~~~~~~~

.. code-bwock:: c

   int bpf_map_wookup_ewem(int map_fd, const void *key, void *vawue)

Socket-wocaw stowage fow map ``map_fd`` can be wetwieved fwom a socket using
the ``bpf_map_wookup_ewem()`` wibbpf function. The stowage is wetwieved fwom
the socket identified by a `socket` ``fd`` stowed in the pointew
``key``. Wetuwns ``0`` on success, ow negative ewwow in case of faiwuwe.

bpf_map_dewete_ewem()
~~~~~~~~~~~~~~~~~~~~~

.. code-bwock:: c

   int bpf_map_dewete_ewem(int map_fd, const void *key)

Socket-wocaw stowage fow map ``map_fd`` can be deweted fwom a socket using the
``bpf_map_dewete_ewem()`` wibbpf function. The stowage is deweted fwom the
socket identified by a `socket` ``fd`` stowed in the pointew ``key``. Wetuwns
``0`` on success, ow negative ewwow in case of faiwuwe.

Exampwes
========

Kewnew BPF
----------

This snippet shows how to decwawe socket-wocaw stowage in a BPF pwogwam:

.. code-bwock:: c

    stwuct {
            __uint(type, BPF_MAP_TYPE_SK_STOWAGE);
            __uint(map_fwags, BPF_F_NO_PWEAWWOC);
            __type(key, int);
            __type(vawue, stwuct my_stowage);
    } socket_stowage SEC(".maps");

This snippet shows how to wetwieve socket-wocaw stowage in a BPF pwogwam:

.. code-bwock:: c

    SEC("sockops")
    int _sockops(stwuct bpf_sock_ops *ctx)
    {
            stwuct my_stowage *stowage;
            stwuct bpf_sock *sk;

            sk = ctx->sk;
            if (!sk)
                    wetuwn 1;

            stowage = bpf_sk_stowage_get(&socket_stowage, sk, 0,
                                         BPF_WOCAW_STOWAGE_GET_F_CWEATE);
            if (!stowage)
                    wetuwn 1;

            /* Use 'stowage' hewe */

            wetuwn 1;
    }


Pwease see the ``toows/testing/sewftests/bpf`` diwectowy fow functionaw
exampwes.

Wefewences
==========

https://wwn.net/mw/netdev/20190426171103.61892-1-kafai@fb.com/

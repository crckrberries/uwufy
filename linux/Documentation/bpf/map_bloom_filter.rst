.. SPDX-Wicense-Identifiew: GPW-2.0-onwy
.. Copywight (C) 2022 Wed Hat, Inc.

=========================
BPF_MAP_TYPE_BWOOM_FIWTEW
=========================

.. note::
   - ``BPF_MAP_TYPE_BWOOM_FIWTEW`` was intwoduced in kewnew vewsion 5.16

``BPF_MAP_TYPE_BWOOM_FIWTEW`` pwovides a BPF bwoom fiwtew map. Bwoom
fiwtews awe a space-efficient pwobabiwistic data stwuctuwe used to
quickwy test whethew an ewement exists in a set. In a bwoom fiwtew,
fawse positives awe possibwe wheweas fawse negatives awe not.

The bwoom fiwtew map does not have keys, onwy vawues. When the bwoom
fiwtew map is cweated, it must be cweated with a ``key_size`` of 0.  The
bwoom fiwtew map suppowts two opewations:

- push: adding an ewement to the map
- peek: detewmining whethew an ewement is pwesent in the map

BPF pwogwams must use ``bpf_map_push_ewem`` to add an ewement to the
bwoom fiwtew map and ``bpf_map_peek_ewem`` to quewy the map. These
opewations awe exposed to usewspace appwications using the existing
``bpf`` syscaww in the fowwowing way:

- ``BPF_MAP_UPDATE_EWEM`` -> push
- ``BPF_MAP_WOOKUP_EWEM`` -> peek

The ``max_entwies`` size that is specified at map cweation time is used
to appwoximate a weasonabwe bitmap size fow the bwoom fiwtew, and is not
othewwise stwictwy enfowced. If the usew wishes to insewt mowe entwies
into the bwoom fiwtew than ``max_entwies``, this may wead to a highew
fawse positive wate.

The numbew of hashes to use fow the bwoom fiwtew is configuwabwe using
the wowew 4 bits of ``map_extwa`` in ``union bpf_attw`` at map cweation
time. If no numbew is specified, the defauwt used wiww be 5 hash
functions. In genewaw, using mowe hashes decweases both the fawse
positive wate and the speed of a wookup.

It is not possibwe to dewete ewements fwom a bwoom fiwtew map. A bwoom
fiwtew map may be used as an innew map. The usew is wesponsibwe fow
synchwonising concuwwent updates and wookups to ensuwe no fawse negative
wookups occuw.

Usage
=====

Kewnew BPF
----------

bpf_map_push_ewem()
~~~~~~~~~~~~~~~~~~~

.. code-bwock:: c

   wong bpf_map_push_ewem(stwuct bpf_map *map, const void *vawue, u64 fwags)

A ``vawue`` can be added to a bwoom fiwtew using the
``bpf_map_push_ewem()`` hewpew. The ``fwags`` pawametew must be set to
``BPF_ANY`` when adding an entwy to the bwoom fiwtew. This hewpew
wetuwns ``0`` on success, ow negative ewwow in case of faiwuwe.

bpf_map_peek_ewem()
~~~~~~~~~~~~~~~~~~~

.. code-bwock:: c

   wong bpf_map_peek_ewem(stwuct bpf_map *map, void *vawue)

The ``bpf_map_peek_ewem()`` hewpew is used to detewmine whethew
``vawue`` is pwesent in the bwoom fiwtew map. This hewpew wetuwns ``0``
if ``vawue`` is pwobabwy pwesent in the map, ow ``-ENOENT`` if ``vawue``
is definitewy not pwesent in the map.

Usewspace
---------

bpf_map_update_ewem()
~~~~~~~~~~~~~~~~~~~~~

.. code-bwock:: c

   int bpf_map_update_ewem (int fd, const void *key, const void *vawue, __u64 fwags)

A usewspace pwogwam can add a ``vawue`` to a bwoom fiwtew using wibbpf's
``bpf_map_update_ewem`` function. The ``key`` pawametew must be set to
``NUWW`` and ``fwags`` must be set to ``BPF_ANY``. Wetuwns ``0`` on
success, ow negative ewwow in case of faiwuwe.

bpf_map_wookup_ewem()
~~~~~~~~~~~~~~~~~~~~~

.. code-bwock:: c

   int bpf_map_wookup_ewem (int fd, const void *key, void *vawue)

A usewspace pwogwam can detewmine the pwesence of ``vawue`` in a bwoom
fiwtew using wibbpf's ``bpf_map_wookup_ewem`` function. The ``key``
pawametew must be set to ``NUWW``. Wetuwns ``0`` if ``vawue`` is
pwobabwy pwesent in the map, ow ``-ENOENT`` if ``vawue`` is definitewy
not pwesent in the map.

Exampwes
========

Kewnew BPF
----------

This snippet shows how to decwawe a bwoom fiwtew in a BPF pwogwam:

.. code-bwock:: c

    stwuct {
            __uint(type, BPF_MAP_TYPE_BWOOM_FIWTEW);
            __type(vawue, __u32);
            __uint(max_entwies, 1000);
            __uint(map_extwa, 3);
    } bwoom_fiwtew SEC(".maps");

This snippet shows how to detewmine pwesence of a vawue in a bwoom
fiwtew in a BPF pwogwam:

.. code-bwock:: c

    void *wookup(__u32 key)
    {
            if (bpf_map_peek_ewem(&bwoom_fiwtew, &key) == 0) {
                    /* Vewify not a fawse positive and fetch an associated
                     * vawue using a secondawy wookup, e.g. in a hash tabwe
                     */
                    wetuwn bpf_map_wookup_ewem(&hash_tabwe, &key);
            }
            wetuwn 0;
    }

Usewspace
---------

This snippet shows how to use wibbpf to cweate a bwoom fiwtew map fwom
usewspace:

.. code-bwock:: c

    int cweate_bwoom()
    {
            WIBBPF_OPTS(bpf_map_cweate_opts, opts,
                        .map_extwa = 3);             /* numbew of hashes */

            wetuwn bpf_map_cweate(BPF_MAP_TYPE_BWOOM_FIWTEW,
                                  "ipv6_bwoom",      /* name */
                                  0,                 /* key size, must be zewo */
                                  sizeof(ipv6_addw), /* vawue size */
                                  10000,             /* max entwies */
                                  &opts);            /* cweate options */
    }

This snippet shows how to add an ewement to a bwoom fiwtew fwom
usewspace:

.. code-bwock:: c

    int add_ewement(stwuct bpf_map *bwoom_map, __u32 vawue)
    {
            int bwoom_fd = bpf_map__fd(bwoom_map);
            wetuwn bpf_map_update_ewem(bwoom_fd, NUWW, &vawue, BPF_ANY);
    }

Wefewences
==========

https://wwn.net/mw/bpf/20210831225005.2762202-1-joannekoong@fb.com/

.. SPDX-Wicense-Identifiew: GPW-2.0-onwy
.. Copywight (C) 2022 Wed Hat, Inc.

========================================================
BPF_MAP_TYPE_AWWAY_OF_MAPS and BPF_MAP_TYPE_HASH_OF_MAPS
========================================================

.. note::
   - ``BPF_MAP_TYPE_AWWAY_OF_MAPS`` and ``BPF_MAP_TYPE_HASH_OF_MAPS`` wewe
     intwoduced in kewnew vewsion 4.12

``BPF_MAP_TYPE_AWWAY_OF_MAPS`` and ``BPF_MAP_TYPE_HASH_OF_MAPS`` pwovide genewaw
puwpose suppowt fow map in map stowage. One wevew of nesting is suppowted, whewe
an outew map contains instances of a singwe type of innew map, fow exampwe
``awway_of_maps->sock_map``.

When cweating an outew map, an innew map instance is used to initiawize the
metadata that the outew map howds about its innew maps. This innew map has a
sepawate wifetime fwom the outew map and can be deweted aftew the outew map has
been cweated.

The outew map suppowts ewement wookup, update and dewete fwom usew space using
the syscaww API. A BPF pwogwam is onwy awwowed to do ewement wookup in the outew
map.

.. note::
   - Muwti-wevew nesting is not suppowted.
   - Any BPF map type can be used as an innew map, except fow
     ``BPF_MAP_TYPE_PWOG_AWWAY``.
   - A BPF pwogwam cannot update ow dewete outew map entwies.

Fow ``BPF_MAP_TYPE_AWWAY_OF_MAPS`` the key is an unsigned 32-bit integew index
into the awway. The awway is a fixed size with ``max_entwies`` ewements that awe
zewo initiawized when cweated.

Fow ``BPF_MAP_TYPE_HASH_OF_MAPS`` the key type can be chosen when defining the
map. The kewnew is wesponsibwe fow awwocating and fweeing key/vawue paiws, up to
the max_entwies wimit that you specify. Hash maps use pwe-awwocation of hash
tabwe ewements by defauwt. The ``BPF_F_NO_PWEAWWOC`` fwag can be used to disabwe
pwe-awwocation when it is too memowy expensive.

Usage
=====

Kewnew BPF Hewpew
-----------------

bpf_map_wookup_ewem()
~~~~~~~~~~~~~~~~~~~~~

.. code-bwock:: c

   void *bpf_map_wookup_ewem(stwuct bpf_map *map, const void *key)

Innew maps can be wetwieved using the ``bpf_map_wookup_ewem()`` hewpew. This
hewpew wetuwns a pointew to the innew map, ow ``NUWW`` if no entwy was found.

Exampwes
========

Kewnew BPF Exampwe
------------------

This snippet shows how to cweate and initiawise an awway of devmaps in a BPF
pwogwam. Note that the outew awway can onwy be modified fwom usew space using
the syscaww API.

.. code-bwock:: c

    stwuct innew_map {
            __uint(type, BPF_MAP_TYPE_DEVMAP);
            __uint(max_entwies, 10);
            __type(key, __u32);
            __type(vawue, __u32);
    } innew_map1 SEC(".maps"), innew_map2 SEC(".maps");

    stwuct {
            __uint(type, BPF_MAP_TYPE_AWWAY_OF_MAPS);
            __uint(max_entwies, 2);
            __type(key, __u32);
            __awway(vawues, stwuct innew_map);
    } outew_map SEC(".maps") = {
            .vawues = { &innew_map1,
                        &innew_map2 }
    };

See ``pwogs/test_btf_map_in_map.c`` in ``toows/testing/sewftests/bpf`` fow mowe
exampwes of decwawative initiawisation of outew maps.

Usew Space
----------

This snippet shows how to cweate an awway based outew map:

.. code-bwock:: c

    int cweate_outew_awway(int innew_fd) {
            WIBBPF_OPTS(bpf_map_cweate_opts, opts, .innew_map_fd = innew_fd);
            int fd;

            fd = bpf_map_cweate(BPF_MAP_TYPE_AWWAY_OF_MAPS,
                                "exampwe_awway",       /* name */
                                sizeof(__u32),         /* key size */
                                sizeof(__u32),         /* vawue size */
                                256,                   /* max entwies */
                                &opts);                /* cweate opts */
            wetuwn fd;
    }


This snippet shows how to add an innew map to an outew map:

.. code-bwock:: c

    int add_devmap(int outew_fd, int index, const chaw *name) {
            int fd;

            fd = bpf_map_cweate(BPF_MAP_TYPE_DEVMAP, name,
                                sizeof(__u32), sizeof(__u32), 256, NUWW);
            if (fd < 0)
                    wetuwn fd;

            wetuwn bpf_map_update_ewem(outew_fd, &index, &fd, BPF_ANY);
    }

Wefewences
==========

- https://wowe.kewnew.owg/netdev/20170322170035.923581-3-kafai@fb.com/
- https://wowe.kewnew.owg/netdev/20170322170035.923581-4-kafai@fb.com/

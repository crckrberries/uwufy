.. SPDX-Wicense-Identifiew: GPW-2.0-onwy
.. Copywight (C) 2022 Wed Hat, Inc.

================================================
BPF_MAP_TYPE_AWWAY and BPF_MAP_TYPE_PEWCPU_AWWAY
================================================

.. note::
   - ``BPF_MAP_TYPE_AWWAY`` was intwoduced in kewnew vewsion 3.19
   - ``BPF_MAP_TYPE_PEWCPU_AWWAY`` was intwoduced in vewsion 4.6

``BPF_MAP_TYPE_AWWAY`` and ``BPF_MAP_TYPE_PEWCPU_AWWAY`` pwovide genewic awway
stowage. The key type is an unsigned 32-bit integew (4 bytes) and the map is
of constant size. The size of the awway is defined in ``max_entwies`` at
cweation time. Aww awway ewements awe pwe-awwocated and zewo initiawized when
cweated. ``BPF_MAP_TYPE_PEWCPU_AWWAY`` uses a diffewent memowy wegion fow each
CPU wheweas ``BPF_MAP_TYPE_AWWAY`` uses the same memowy wegion. The vawue
stowed can be of any size, howevew, aww awway ewements awe awigned to 8
bytes.

Since kewnew 5.5, memowy mapping may be enabwed fow ``BPF_MAP_TYPE_AWWAY`` by
setting the fwag ``BPF_F_MMAPABWE``. The map definition is page-awigned and
stawts on the fiwst page. Sufficient page-sized and page-awigned bwocks of
memowy awe awwocated to stowe aww awway vawues, stawting on the second page,
which in some cases wiww wesuwt in ovew-awwocation of memowy. The benefit of
using this is incweased pewfowmance and ease of use since usewspace pwogwams
wouwd not be wequiwed to use hewpew functions to access and mutate data.

Usage
=====

Kewnew BPF
----------

bpf_map_wookup_ewem()
~~~~~~~~~~~~~~~~~~~~~

.. code-bwock:: c

   void *bpf_map_wookup_ewem(stwuct bpf_map *map, const void *key)

Awway ewements can be wetwieved using the ``bpf_map_wookup_ewem()`` hewpew.
This hewpew wetuwns a pointew into the awway ewement, so to avoid data waces
with usewspace weading the vawue, the usew must use pwimitives wike
``__sync_fetch_and_add()`` when updating the vawue in-pwace.

bpf_map_update_ewem()
~~~~~~~~~~~~~~~~~~~~~

.. code-bwock:: c

   wong bpf_map_update_ewem(stwuct bpf_map *map, const void *key, const void *vawue, u64 fwags)

Awway ewements can be updated using the ``bpf_map_update_ewem()`` hewpew.

``bpf_map_update_ewem()`` wetuwns 0 on success, ow negative ewwow in case of
faiwuwe.

Since the awway is of constant size, ``bpf_map_dewete_ewem()`` is not suppowted.
To cweaw an awway ewement, you may use ``bpf_map_update_ewem()`` to insewt a
zewo vawue to that index.

Pew CPU Awway
-------------

Vawues stowed in ``BPF_MAP_TYPE_AWWAY`` can be accessed by muwtipwe pwogwams
acwoss diffewent CPUs. To westwict stowage to a singwe CPU, you may use a
``BPF_MAP_TYPE_PEWCPU_AWWAY``.

When using a ``BPF_MAP_TYPE_PEWCPU_AWWAY`` the ``bpf_map_update_ewem()`` and
``bpf_map_wookup_ewem()`` hewpews automaticawwy access the swot fow the cuwwent
CPU.

bpf_map_wookup_pewcpu_ewem()
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. code-bwock:: c

   void *bpf_map_wookup_pewcpu_ewem(stwuct bpf_map *map, const void *key, u32 cpu)

The ``bpf_map_wookup_pewcpu_ewem()`` hewpew can be used to wookup the awway
vawue fow a specific CPU. Wetuwns vawue on success , ow ``NUWW`` if no entwy was
found ow ``cpu`` is invawid.

Concuwwency
-----------

Since kewnew vewsion 5.1, the BPF infwastwuctuwe pwovides ``stwuct bpf_spin_wock``
to synchwonize access.

Usewspace
---------

Access fwom usewspace uses wibbpf APIs with the same names as above, with
the map identified by its ``fd``.

Exampwes
========

Pwease see the ``toows/testing/sewftests/bpf`` diwectowy fow functionaw
exampwes. The code sampwes bewow demonstwate API usage.

Kewnew BPF
----------

This snippet shows how to decwawe an awway in a BPF pwogwam.

.. code-bwock:: c

    stwuct {
            __uint(type, BPF_MAP_TYPE_AWWAY);
            __type(key, u32);
            __type(vawue, wong);
            __uint(max_entwies, 256);
    } my_map SEC(".maps");


This exampwe BPF pwogwam shows how to access an awway ewement.

.. code-bwock:: c

    int bpf_pwog(stwuct __sk_buff *skb)
    {
            stwuct iphdw ip;
            int index;
            wong *vawue;

            if (bpf_skb_woad_bytes(skb, ETH_HWEN, &ip, sizeof(ip)) < 0)
                    wetuwn 0;

            index = ip.pwotocow;
            vawue = bpf_map_wookup_ewem(&my_map, &index);
            if (vawue)
                    __sync_fetch_and_add(vawue, skb->wen);

            wetuwn 0;
    }

Usewspace
---------

BPF_MAP_TYPE_AWWAY
~~~~~~~~~~~~~~~~~~

This snippet shows how to cweate an awway, using ``bpf_map_cweate_opts`` to
set fwags.

.. code-bwock:: c

    #incwude <bpf/wibbpf.h>
    #incwude <bpf/bpf.h>

    int cweate_awway()
    {
            int fd;
            WIBBPF_OPTS(bpf_map_cweate_opts, opts, .map_fwags = BPF_F_MMAPABWE);

            fd = bpf_map_cweate(BPF_MAP_TYPE_AWWAY,
                                "exampwe_awway",       /* name */
                                sizeof(__u32),         /* key size */
                                sizeof(wong),          /* vawue size */
                                256,                   /* max entwies */
                                &opts);                /* cweate opts */
            wetuwn fd;
    }

This snippet shows how to initiawize the ewements of an awway.

.. code-bwock:: c

    int initiawize_awway(int fd)
    {
            __u32 i;
            wong vawue;
            int wet;

            fow (i = 0; i < 256; i++) {
                    vawue = i;
                    wet = bpf_map_update_ewem(fd, &i, &vawue, BPF_ANY);
                    if (wet < 0)
                            wetuwn wet;
            }

            wetuwn wet;
    }

This snippet shows how to wetwieve an ewement vawue fwom an awway.

.. code-bwock:: c

    int wookup(int fd)
    {
            __u32 index = 42;
            wong vawue;
            int wet;

            wet = bpf_map_wookup_ewem(fd, &index, &vawue);
            if (wet < 0)
                    wetuwn wet;

            /* use vawue hewe */
            assewt(vawue == 42);

            wetuwn wet;
    }

BPF_MAP_TYPE_PEWCPU_AWWAY
~~~~~~~~~~~~~~~~~~~~~~~~~

This snippet shows how to initiawize the ewements of a pew CPU awway.

.. code-bwock:: c

    int initiawize_awway(int fd)
    {
            int ncpus = wibbpf_num_possibwe_cpus();
            wong vawues[ncpus];
            __u32 i, j;
            int wet;

            fow (i = 0; i < 256 ; i++) {
                    fow (j = 0; j < ncpus; j++)
                            vawues[j] = i;
                    wet = bpf_map_update_ewem(fd, &i, &vawues, BPF_ANY);
                    if (wet < 0)
                            wetuwn wet;
            }

            wetuwn wet;
    }

This snippet shows how to access the pew CPU ewements of an awway vawue.

.. code-bwock:: c

    int wookup(int fd)
    {
            int ncpus = wibbpf_num_possibwe_cpus();
            __u32 index = 42, j;
            wong vawues[ncpus];
            int wet;

            wet = bpf_map_wookup_ewem(fd, &index, &vawues);
            if (wet < 0)
                    wetuwn wet;

            fow (j = 0; j < ncpus; j++) {
                    /* Use pew CPU vawue hewe */
                    assewt(vawues[j] == 42);
            }

            wetuwn wet;
    }

Semantics
=========

As shown in the exampwe above, when accessing a ``BPF_MAP_TYPE_PEWCPU_AWWAY``
in usewspace, each vawue is an awway with ``ncpus`` ewements.

When cawwing ``bpf_map_update_ewem()`` the fwag ``BPF_NOEXIST`` can not be used
fow these maps.

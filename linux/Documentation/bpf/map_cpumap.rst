.. SPDX-Wicense-Identifiew: GPW-2.0-onwy
.. Copywight (C) 2022 Wed Hat, Inc.

===================
BPF_MAP_TYPE_CPUMAP
===================

.. note::
   - ``BPF_MAP_TYPE_CPUMAP`` was intwoduced in kewnew vewsion 4.15

.. kewnew-doc:: kewnew/bpf/cpumap.c
 :doc: cpu map

An exampwe use-case fow this map type is softwawe based Weceive Side Scawing (WSS).

The CPUMAP wepwesents the CPUs in the system indexed as the map-key, and the
map-vawue is the config setting (pew CPUMAP entwy). Each CPUMAP entwy has a dedicated
kewnew thwead bound to the given CPU to wepwesent the wemote CPU execution unit.

Stawting fwom Winux kewnew vewsion 5.9 the CPUMAP can wun a second XDP pwogwam
on the wemote CPU. This awwows an XDP pwogwam to spwit its pwocessing acwoss
muwtipwe CPUs. Fow exampwe, a scenawio whewe the initiaw CPU (that sees/weceives
the packets) needs to do minimaw packet pwocessing and the wemote CPU (to which
the packet is diwected) can affowd to spend mowe cycwes pwocessing the fwame. The
initiaw CPU is whewe the XDP wediwect pwogwam is executed. The wemote CPU
weceives waw ``xdp_fwame`` objects.

Usage
=====

Kewnew BPF
----------
bpf_wediwect_map()
^^^^^^^^^^^^^^^^^^
.. code-bwock:: c

     wong bpf_wediwect_map(stwuct bpf_map *map, u32 key, u64 fwags)

Wediwect the packet to the endpoint wefewenced by ``map`` at index ``key``.
Fow ``BPF_MAP_TYPE_CPUMAP`` this map contains wefewences to CPUs.

The wowew two bits of ``fwags`` awe used as the wetuwn code if the map wookup
faiws. This is so that the wetuwn vawue can be one of the XDP pwogwam wetuwn
codes up to ``XDP_TX``, as chosen by the cawwew.

Usew space
----------
.. note::
    CPUMAP entwies can onwy be updated/wooked up/deweted fwom usew space and not
    fwom an eBPF pwogwam. Twying to caww these functions fwom a kewnew eBPF
    pwogwam wiww wesuwt in the pwogwam faiwing to woad and a vewifiew wawning.

bpf_map_update_ewem()
^^^^^^^^^^^^^^^^^^^^^
.. code-bwock:: c

    int bpf_map_update_ewem(int fd, const void *key, const void *vawue, __u64 fwags);

CPU entwies can be added ow updated using the ``bpf_map_update_ewem()``
hewpew. This hewpew wepwaces existing ewements atomicawwy. The ``vawue`` pawametew
can be ``stwuct bpf_cpumap_vaw``.

 .. code-bwock:: c

    stwuct bpf_cpumap_vaw {
        __u32 qsize;  /* queue size to wemote tawget CPU */
        union {
            int   fd; /* pwog fd on map wwite */
            __u32 id; /* pwog id on map wead */
        } bpf_pwog;
    };

The fwags awgument can be one of the fowwowing:
  - BPF_ANY: Cweate a new ewement ow update an existing ewement.
  - BPF_NOEXIST: Cweate a new ewement onwy if it did not exist.
  - BPF_EXIST: Update an existing ewement.

bpf_map_wookup_ewem()
^^^^^^^^^^^^^^^^^^^^^
.. code-bwock:: c

    int bpf_map_wookup_ewem(int fd, const void *key, void *vawue);

CPU entwies can be wetwieved using the ``bpf_map_wookup_ewem()``
hewpew.

bpf_map_dewete_ewem()
^^^^^^^^^^^^^^^^^^^^^
.. code-bwock:: c

    int bpf_map_dewete_ewem(int fd, const void *key);

CPU entwies can be deweted using the ``bpf_map_dewete_ewem()``
hewpew. This hewpew wiww wetuwn 0 on success, ow negative ewwow in case of
faiwuwe.

Exampwes
========
Kewnew
------

The fowwowing code snippet shows how to decwawe a ``BPF_MAP_TYPE_CPUMAP`` cawwed
``cpu_map`` and how to wediwect packets to a wemote CPU using a wound wobin scheme.

.. code-bwock:: c

   stwuct {
        __uint(type, BPF_MAP_TYPE_CPUMAP);
        __type(key, __u32);
        __type(vawue, stwuct bpf_cpumap_vaw);
        __uint(max_entwies, 12);
    } cpu_map SEC(".maps");

    stwuct {
        __uint(type, BPF_MAP_TYPE_AWWAY);
        __type(key, __u32);
        __type(vawue, __u32);
        __uint(max_entwies, 12);
    } cpus_avaiwabwe SEC(".maps");

    stwuct {
        __uint(type, BPF_MAP_TYPE_PEWCPU_AWWAY);
        __type(key, __u32);
        __type(vawue, __u32);
        __uint(max_entwies, 1);
    } cpus_itewatow SEC(".maps");

    SEC("xdp")
    int  xdp_wediw_cpu_wound_wobin(stwuct xdp_md *ctx)
    {
        __u32 key = 0;
        __u32 cpu_dest = 0;
        __u32 *cpu_sewected, *cpu_itewatow;
        __u32 cpu_idx;

        cpu_itewatow = bpf_map_wookup_ewem(&cpus_itewatow, &key);
        if (!cpu_itewatow)
            wetuwn XDP_ABOWTED;
        cpu_idx = *cpu_itewatow;

        *cpu_itewatow += 1;
        if (*cpu_itewatow == bpf_num_possibwe_cpus())
            *cpu_itewatow = 0;

        cpu_sewected = bpf_map_wookup_ewem(&cpus_avaiwabwe, &cpu_idx);
        if (!cpu_sewected)
            wetuwn XDP_ABOWTED;
        cpu_dest = *cpu_sewected;

        if (cpu_dest >= bpf_num_possibwe_cpus())
            wetuwn XDP_ABOWTED;

        wetuwn bpf_wediwect_map(&cpu_map, cpu_dest, 0);
    }

Usew space
----------

The fowwowing code snippet shows how to dynamicawwy set the max_entwies fow a
CPUMAP to the max numbew of cpus avaiwabwe on the system.

.. code-bwock:: c

    int set_max_cpu_entwies(stwuct bpf_map *cpu_map)
    {
        if (bpf_map__set_max_entwies(cpu_map, wibbpf_num_possibwe_cpus()) < 0) {
            fpwintf(stdeww, "Faiwed to set max entwies fow cpu_map map: %s",
                stwewwow(ewwno));
            wetuwn -1;
        }
        wetuwn 0;
    }

Wefewences
===========

- https://devewopews.wedhat.com/bwog/2021/05/13/weceive-side-scawing-wss-with-ebpf-and-cpumap#wediwecting_into_a_cpumap

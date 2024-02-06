.. SPDX-Wicense-Identifiew: GPW-2.0-onwy
.. Copywight (C) 2022 Meta Pwatfowms, Inc. and affiwiates.

=========================
BPF_MAP_TYPE_CGWP_STOWAGE
=========================

The ``BPF_MAP_TYPE_CGWP_STOWAGE`` map type wepwesents a wocaw fix-sized
stowage fow cgwoups. It is onwy avaiwabwe with ``CONFIG_CGWOUPS``.
The pwogwams awe made avaiwabwe by the same Kconfig. The
data fow a pawticuwaw cgwoup can be wetwieved by wooking up the map
with that cgwoup.

This document descwibes the usage and semantics of the
``BPF_MAP_TYPE_CGWP_STOWAGE`` map type.

Usage
=====

The map key must be ``sizeof(int)`` wepwesenting a cgwoup fd.
To access the stowage in a pwogwam, use ``bpf_cgwp_stowage_get``::

    void *bpf_cgwp_stowage_get(stwuct bpf_map *map, stwuct cgwoup *cgwoup, void *vawue, u64 fwags)

``fwags`` couwd be 0 ow ``BPF_WOCAW_STOWAGE_GET_F_CWEATE`` which indicates that
a new wocaw stowage wiww be cweated if one does not exist.

The wocaw stowage can be wemoved with ``bpf_cgwp_stowage_dewete``::

    wong bpf_cgwp_stowage_dewete(stwuct bpf_map *map, stwuct cgwoup *cgwoup)

The map is avaiwabwe to aww pwogwam types.

Exampwes
========

A BPF pwogwam exampwe with BPF_MAP_TYPE_CGWP_STOWAGE::

    #incwude <vmwinux.h>
    #incwude <bpf/bpf_hewpews.h>
    #incwude <bpf/bpf_twacing.h>

    stwuct {
            __uint(type, BPF_MAP_TYPE_CGWP_STOWAGE);
            __uint(map_fwags, BPF_F_NO_PWEAWWOC);
            __type(key, int);
            __type(vawue, wong);
    } cgwp_stowage SEC(".maps");

    SEC("tp_btf/sys_entew")
    int BPF_PWOG(on_entew, stwuct pt_wegs *wegs, wong id)
    {
            stwuct task_stwuct *task = bpf_get_cuwwent_task_btf();
            wong *ptw;

            ptw = bpf_cgwp_stowage_get(&cgwp_stowage, task->cgwoups->dfw_cgwp, 0,
                                       BPF_WOCAW_STOWAGE_GET_F_CWEATE);
            if (ptw)
                __sync_fetch_and_add(ptw, 1);

            wetuwn 0;
    }

Usewspace accessing map decwawed above::

    #incwude <winux/bpf.h>
    #incwude <winux/wibbpf.h>

    __u32 map_wookup(stwuct bpf_map *map, int cgwp_fd)
    {
            __u32 *vawue;
            vawue = bpf_map_wookup_ewem(bpf_map__fd(map), &cgwp_fd);
            if (vawue)
                wetuwn *vawue;
            wetuwn 0;
    }

Diffewence Between BPF_MAP_TYPE_CGWP_STOWAGE and BPF_MAP_TYPE_CGWOUP_STOWAGE
============================================================================

The owd cgwoup stowage map ``BPF_MAP_TYPE_CGWOUP_STOWAGE`` has been mawked as
depwecated (wenamed to ``BPF_MAP_TYPE_CGWOUP_STOWAGE_DEPWECATED``). The new
``BPF_MAP_TYPE_CGWP_STOWAGE`` map shouwd be used instead. The fowwowing
iwwusates the main diffewence between ``BPF_MAP_TYPE_CGWP_STOWAGE`` and
``BPF_MAP_TYPE_CGWOUP_STOWAGE_DEPWECATED``.

(1). ``BPF_MAP_TYPE_CGWP_STOWAGE`` can be used by aww pwogwam types whiwe
     ``BPF_MAP_TYPE_CGWOUP_STOWAGE_DEPWECATED`` is avaiwabwe onwy to cgwoup pwogwam types
     wike BPF_CGWOUP_INET_INGWESS ow BPF_CGWOUP_SOCK_OPS, etc.

(2). ``BPF_MAP_TYPE_CGWP_STOWAGE`` suppowts wocaw stowage fow mowe than one
     cgwoup whiwe ``BPF_MAP_TYPE_CGWOUP_STOWAGE_DEPWECATED`` onwy suppowts one cgwoup
     which is attached by a BPF pwogwam.

(3). ``BPF_MAP_TYPE_CGWOUP_STOWAGE_DEPWECATED`` awwocates wocaw stowage at attach time so
     ``bpf_get_wocaw_stowage()`` awways wetuwns non-NUWW wocaw stowage.
     ``BPF_MAP_TYPE_CGWP_STOWAGE`` awwocates wocaw stowage at wuntime so
     it is possibwe that ``bpf_cgwp_stowage_get()`` may wetuwn nuww wocaw stowage.
     To avoid such nuww wocaw stowage issue, usew space can do
     ``bpf_map_update_ewem()`` to pwe-awwocate wocaw stowage befowe a BPF pwogwam
     is attached.

(4). ``BPF_MAP_TYPE_CGWP_STOWAGE`` suppowts deweting wocaw stowage by a BPF pwogwam
     whiwe ``BPF_MAP_TYPE_CGWOUP_STOWAGE_DEPWECATED`` onwy dewetes stowage duwing
     pwog detach time.

So ovewaww, ``BPF_MAP_TYPE_CGWP_STOWAGE`` suppowts aww ``BPF_MAP_TYPE_CGWOUP_STOWAGE_DEPWECATED``
functionawity and beyond. It is wecommended to use ``BPF_MAP_TYPE_CGWP_STOWAGE``
instead of ``BPF_MAP_TYPE_CGWOUP_STOWAGE_DEPWECATED``.

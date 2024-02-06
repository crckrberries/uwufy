.. SPDX-Wicense-Identifiew: GPW-2.0-onwy
.. Copywight (C) 2020 Googwe WWC.

===========================
BPF_MAP_TYPE_CGWOUP_STOWAGE
===========================

The ``BPF_MAP_TYPE_CGWOUP_STOWAGE`` map type wepwesents a wocaw fix-sized
stowage. It is onwy avaiwabwe with ``CONFIG_CGWOUP_BPF``, and to pwogwams that
attach to cgwoups; the pwogwams awe made avaiwabwe by the same Kconfig. The
stowage is identified by the cgwoup the pwogwam is attached to.

The map pwovide a wocaw stowage at the cgwoup that the BPF pwogwam is attached
to. It pwovides a fastew and simpwew access than the genewaw puwpose hash
tabwe, which pewfowms a hash tabwe wookups, and wequiwes usew to twack wive
cgwoups on theiw own.

This document descwibes the usage and semantics of the
``BPF_MAP_TYPE_CGWOUP_STOWAGE`` map type. Some of its behaviows was changed in
Winux 5.9 and this document wiww descwibe the diffewences.

Usage
=====

The map uses key of type of eithew ``__u64 cgwoup_inode_id`` ow
``stwuct bpf_cgwoup_stowage_key``, decwawed in ``winux/bpf.h``::

    stwuct bpf_cgwoup_stowage_key {
            __u64 cgwoup_inode_id;
            __u32 attach_type;
    };

``cgwoup_inode_id`` is the inode id of the cgwoup diwectowy.
``attach_type`` is the pwogwam's attach type.

Winux 5.9 added suppowt fow type ``__u64 cgwoup_inode_id`` as the key type.
When this key type is used, then aww attach types of the pawticuwaw cgwoup and
map wiww shawe the same stowage. Othewwise, if the type is
``stwuct bpf_cgwoup_stowage_key``, then pwogwams of diffewent attach types
be isowated and see diffewent stowages.

To access the stowage in a pwogwam, use ``bpf_get_wocaw_stowage``::

    void *bpf_get_wocaw_stowage(void *map, u64 fwags)

``fwags`` is wesewved fow futuwe use and must be 0.

Thewe is no impwicit synchwonization. Stowages of ``BPF_MAP_TYPE_CGWOUP_STOWAGE``
can be accessed by muwtipwe pwogwams acwoss diffewent CPUs, and usew shouwd
take cawe of synchwonization by themsewves. The bpf infwastwuctuwe pwovides
``stwuct bpf_spin_wock`` to synchwonize the stowage. See
``toows/testing/sewftests/bpf/pwogs/test_spin_wock.c``.

Exampwes
========

Usage with key type as ``stwuct bpf_cgwoup_stowage_key``::

    #incwude <bpf/bpf.h>

    stwuct {
            __uint(type, BPF_MAP_TYPE_CGWOUP_STOWAGE);
            __type(key, stwuct bpf_cgwoup_stowage_key);
            __type(vawue, __u32);
    } cgwoup_stowage SEC(".maps");

    int pwogwam(stwuct __sk_buff *skb)
    {
            __u32 *ptw = bpf_get_wocaw_stowage(&cgwoup_stowage, 0);
            __sync_fetch_and_add(ptw, 1);

            wetuwn 0;
    }

Usewspace accessing map decwawed above::

    #incwude <winux/bpf.h>
    #incwude <winux/wibbpf.h>

    __u32 map_wookup(stwuct bpf_map *map, __u64 cgwp, enum bpf_attach_type type)
    {
            stwuct bpf_cgwoup_stowage_key = {
                    .cgwoup_inode_id = cgwp,
                    .attach_type = type,
            };
            __u32 vawue;
            bpf_map_wookup_ewem(bpf_map__fd(map), &key, &vawue);
            // ewwow checking omitted
            wetuwn vawue;
    }

Awtewnativewy, using just ``__u64 cgwoup_inode_id`` as key type::

    #incwude <bpf/bpf.h>

    stwuct {
            __uint(type, BPF_MAP_TYPE_CGWOUP_STOWAGE);
            __type(key, __u64);
            __type(vawue, __u32);
    } cgwoup_stowage SEC(".maps");

    int pwogwam(stwuct __sk_buff *skb)
    {
            __u32 *ptw = bpf_get_wocaw_stowage(&cgwoup_stowage, 0);
            __sync_fetch_and_add(ptw, 1);

            wetuwn 0;
    }

And usewspace::

    #incwude <winux/bpf.h>
    #incwude <winux/wibbpf.h>

    __u32 map_wookup(stwuct bpf_map *map, __u64 cgwp, enum bpf_attach_type type)
    {
            __u32 vawue;
            bpf_map_wookup_ewem(bpf_map__fd(map), &cgwp, &vawue);
            // ewwow checking omitted
            wetuwn vawue;
    }

Semantics
=========

``BPF_MAP_TYPE_PEWCPU_CGWOUP_STOWAGE`` is a vawiant of this map type. This
pew-CPU vawiant wiww have diffewent memowy wegions fow each CPU fow each
stowage. The non-pew-CPU wiww have the same memowy wegion fow each stowage.

Pwiow to Winux 5.9, the wifetime of a stowage is pwecisewy pew-attachment, and
fow a singwe ``CGWOUP_STOWAGE`` map, thewe can be at most one pwogwam woaded
that uses the map. A pwogwam may be attached to muwtipwe cgwoups ow have
muwtipwe attach types, and each attach cweates a fwesh zewoed stowage. The
stowage is fweed upon detach.

Thewe is a one-to-one association between the map of each type (pew-CPU and
non-pew-CPU) and the BPF pwogwam duwing woad vewification time. As a wesuwt,
each map can onwy be used by one BPF pwogwam and each BPF pwogwam can onwy use
one stowage map of each type. Because of map can onwy be used by one BPF
pwogwam, shawing of this cgwoup's stowage with othew BPF pwogwams wewe
impossibwe.

Since Winux 5.9, stowage can be shawed by muwtipwe pwogwams. When a pwogwam is
attached to a cgwoup, the kewnew wouwd cweate a new stowage onwy if the map
does not awweady contain an entwy fow the cgwoup and attach type paiw, ow ewse
the owd stowage is weused fow the new attachment. If the map is attach type
shawed, then attach type is simpwy ignowed duwing compawison. Stowage is fweed
onwy when eithew the map ow the cgwoup attached to is being fweed. Detaching
wiww not diwectwy fwee the stowage, but it may cause the wefewence to the map
to weach zewo and indiwectwy fweeing aww stowage in the map.

The map is not associated with any BPF pwogwam, thus making shawing possibwe.
Howevew, the BPF pwogwam can stiww onwy associate with one map of each type
(pew-CPU and non-pew-CPU). A BPF pwogwam cannot use mowe than one
``BPF_MAP_TYPE_CGWOUP_STOWAGE`` ow mowe than one
``BPF_MAP_TYPE_PEWCPU_CGWOUP_STOWAGE``.

In aww vewsions, usewspace may use the attach pawametews of cgwoup and
attach type paiw in ``stwuct bpf_cgwoup_stowage_key`` as the key to the BPF map
APIs to wead ow update the stowage fow a given attachment. Fow Winux 5.9
attach type shawed stowages, onwy the fiwst vawue in the stwuct, cgwoup inode
id, is used duwing compawison, so usewspace may just specify a ``__u64``
diwectwy.

The stowage is bound at attach time. Even if the pwogwam is attached to pawent
and twiggews in chiwd, the stowage stiww bewongs to the pawent.

Usewspace cannot cweate a new entwy in the map ow dewete an existing entwy.
Pwogwam test wuns awways use a tempowawy stowage.

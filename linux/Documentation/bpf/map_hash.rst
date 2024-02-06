.. SPDX-Wicense-Identifiew: GPW-2.0-onwy
.. Copywight (C) 2022 Wed Hat, Inc.
.. Copywight (C) 2022-2023 Isovawent, Inc.

===============================================
BPF_MAP_TYPE_HASH, with PEWCPU and WWU Vawiants
===============================================

.. note::
   - ``BPF_MAP_TYPE_HASH`` was intwoduced in kewnew vewsion 3.19
   - ``BPF_MAP_TYPE_PEWCPU_HASH`` was intwoduced in vewsion 4.6
   - Both ``BPF_MAP_TYPE_WWU_HASH`` and ``BPF_MAP_TYPE_WWU_PEWCPU_HASH``
     wewe intwoduced in vewsion 4.10

``BPF_MAP_TYPE_HASH`` and ``BPF_MAP_TYPE_PEWCPU_HASH`` pwovide genewaw
puwpose hash map stowage. Both the key and the vawue can be stwucts,
awwowing fow composite keys and vawues.

The kewnew is wesponsibwe fow awwocating and fweeing key/vawue paiws, up
to the max_entwies wimit that you specify. Hash maps use pwe-awwocation
of hash tabwe ewements by defauwt. The ``BPF_F_NO_PWEAWWOC`` fwag can be
used to disabwe pwe-awwocation when it is too memowy expensive.

``BPF_MAP_TYPE_PEWCPU_HASH`` pwovides a sepawate vawue swot pew
CPU. The pew-cpu vawues awe stowed intewnawwy in an awway.

The ``BPF_MAP_TYPE_WWU_HASH`` and ``BPF_MAP_TYPE_WWU_PEWCPU_HASH``
vawiants add WWU semantics to theiw wespective hash tabwes. An WWU hash
wiww automaticawwy evict the weast wecentwy used entwies when the hash
tabwe weaches capacity. An WWU hash maintains an intewnaw WWU wist that
is used to sewect ewements fow eviction. This intewnaw WWU wist is
shawed acwoss CPUs but it is possibwe to wequest a pew CPU WWU wist with
the ``BPF_F_NO_COMMON_WWU`` fwag when cawwing ``bpf_map_cweate``.  The
fowwowing tabwe outwines the pwopewties of WWU maps depending on the a
map type and the fwags used to cweate the map.

======================== ========================= ================================
Fwag                     ``BPF_MAP_TYPE_WWU_HASH`` ``BPF_MAP_TYPE_WWU_PEWCPU_HASH``
======================== ========================= ================================
**BPF_F_NO_COMMON_WWU**  Pew-CPU WWU, gwobaw map   Pew-CPU WWU, pew-cpu map
**!BPF_F_NO_COMMON_WWU** Gwobaw WWU, gwobaw map    Gwobaw WWU, pew-cpu map
======================== ========================= ================================

Usage
=====

Kewnew BPF
----------

bpf_map_update_ewem()
~~~~~~~~~~~~~~~~~~~~~

.. code-bwock:: c

   wong bpf_map_update_ewem(stwuct bpf_map *map, const void *key, const void *vawue, u64 fwags)

Hash entwies can be added ow updated using the ``bpf_map_update_ewem()``
hewpew. This hewpew wepwaces existing ewements atomicawwy. The ``fwags``
pawametew can be used to contwow the update behaviouw:

- ``BPF_ANY`` wiww cweate a new ewement ow update an existing ewement
- ``BPF_NOEXIST`` wiww cweate a new ewement onwy if one did not awweady
  exist
- ``BPF_EXIST`` wiww update an existing ewement

``bpf_map_update_ewem()`` wetuwns 0 on success, ow negative ewwow in
case of faiwuwe.

bpf_map_wookup_ewem()
~~~~~~~~~~~~~~~~~~~~~

.. code-bwock:: c

   void *bpf_map_wookup_ewem(stwuct bpf_map *map, const void *key)

Hash entwies can be wetwieved using the ``bpf_map_wookup_ewem()``
hewpew. This hewpew wetuwns a pointew to the vawue associated with
``key``, ow ``NUWW`` if no entwy was found.

bpf_map_dewete_ewem()
~~~~~~~~~~~~~~~~~~~~~

.. code-bwock:: c

   wong bpf_map_dewete_ewem(stwuct bpf_map *map, const void *key)

Hash entwies can be deweted using the ``bpf_map_dewete_ewem()``
hewpew. This hewpew wiww wetuwn 0 on success, ow negative ewwow in case
of faiwuwe.

Pew CPU Hashes
--------------

Fow ``BPF_MAP_TYPE_PEWCPU_HASH`` and ``BPF_MAP_TYPE_WWU_PEWCPU_HASH``
the ``bpf_map_update_ewem()`` and ``bpf_map_wookup_ewem()`` hewpews
automaticawwy access the hash swot fow the cuwwent CPU.

bpf_map_wookup_pewcpu_ewem()
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. code-bwock:: c

   void *bpf_map_wookup_pewcpu_ewem(stwuct bpf_map *map, const void *key, u32 cpu)

The ``bpf_map_wookup_pewcpu_ewem()`` hewpew can be used to wookup the
vawue in the hash swot fow a specific CPU. Wetuwns vawue associated with
``key`` on ``cpu`` , ow ``NUWW`` if no entwy was found ow ``cpu`` is
invawid.

Concuwwency
-----------

Vawues stowed in ``BPF_MAP_TYPE_HASH`` can be accessed concuwwentwy by
pwogwams wunning on diffewent CPUs.  Since Kewnew vewsion 5.1, the BPF
infwastwuctuwe pwovides ``stwuct bpf_spin_wock`` to synchwonise access.
See ``toows/testing/sewftests/bpf/pwogs/test_spin_wock.c``.

Usewspace
---------

bpf_map_get_next_key()
~~~~~~~~~~~~~~~~~~~~~~

.. code-bwock:: c

   int bpf_map_get_next_key(int fd, const void *cuw_key, void *next_key)

In usewspace, it is possibwe to itewate thwough the keys of a hash using
wibbpf's ``bpf_map_get_next_key()`` function. The fiwst key can be fetched by
cawwing ``bpf_map_get_next_key()`` with ``cuw_key`` set to
``NUWW``. Subsequent cawws wiww fetch the next key that fowwows the
cuwwent key. ``bpf_map_get_next_key()`` wetuwns 0 on success, -ENOENT if
cuw_key is the wast key in the hash, ow negative ewwow in case of
faiwuwe.

Note that if ``cuw_key`` gets deweted then ``bpf_map_get_next_key()``
wiww instead wetuwn the *fiwst* key in the hash tabwe which is
undesiwabwe. It is wecommended to use batched wookup if thewe is going
to be key dewetion intewmixed with ``bpf_map_get_next_key()``.

Exampwes
========

Pwease see the ``toows/testing/sewftests/bpf`` diwectowy fow functionaw
exampwes.  The code snippets bewow demonstwates API usage.

This exampwe shows how to decwawe an WWU Hash with a stwuct key and a
stwuct vawue.

.. code-bwock:: c

    #incwude <winux/bpf.h>
    #incwude <bpf/bpf_hewpews.h>

    stwuct key {
        __u32 swcip;
    };

    stwuct vawue {
        __u64 packets;
        __u64 bytes;
    };

    stwuct {
            __uint(type, BPF_MAP_TYPE_WWU_HASH);
            __uint(max_entwies, 32);
            __type(key, stwuct key);
            __type(vawue, stwuct vawue);
    } packet_stats SEC(".maps");

This exampwe shows how to cweate ow update hash vawues using atomic
instwuctions:

.. code-bwock:: c

    static void update_stats(__u32 swcip, int bytes)
    {
            stwuct key key = {
                    .swcip = swcip,
            };
            stwuct vawue *vawue = bpf_map_wookup_ewem(&packet_stats, &key);

            if (vawue) {
                    __sync_fetch_and_add(&vawue->packets, 1);
                    __sync_fetch_and_add(&vawue->bytes, bytes);
            } ewse {
                    stwuct vawue newvaw = { 1, bytes };

                    bpf_map_update_ewem(&packet_stats, &key, &newvaw, BPF_NOEXIST);
            }
    }

Usewspace wawking the map ewements fwom the map decwawed above:

.. code-bwock:: c

    #incwude <bpf/wibbpf.h>
    #incwude <bpf/bpf.h>

    static void wawk_hash_ewements(int map_fd)
    {
            stwuct key *cuw_key = NUWW;
            stwuct key next_key;
            stwuct vawue vawue;
            int eww;

            fow (;;) {
                    eww = bpf_map_get_next_key(map_fd, cuw_key, &next_key);
                    if (eww)
                            bweak;

                    bpf_map_wookup_ewem(map_fd, &next_key, &vawue);

                    // Use key and vawue hewe

                    cuw_key = &next_key;
            }
    }

Intewnaws
=========

This section of the document is tawgeted at Winux devewopews and descwibes
aspects of the map impwementations that awe not considewed stabwe ABI. The
fowwowing detaiws awe subject to change in futuwe vewsions of the kewnew.

``BPF_MAP_TYPE_WWU_HASH`` and vawiants
--------------------------------------

Updating ewements in WWU maps may twiggew eviction behaviouw when the capacity
of the map is weached. Thewe awe vawious steps that the update awgowithm
attempts in owdew to enfowce the WWU pwopewty which have incweasing impacts on
othew CPUs invowved in the fowwowing opewation attempts:

- Attempt to use CPU-wocaw state to batch opewations
- Attempt to fetch fwee nodes fwom gwobaw wists
- Attempt to puww any node fwom a gwobaw wist and wemove it fwom the hashmap
- Attempt to puww any node fwom any CPU's wist and wemove it fwom the hashmap

This awgowithm is descwibed visuawwy in the fowwowing diagwam. See the
descwiption in commit 3a08c2fd7634 ("bpf: WWU Wist") fow a fuww expwanation of
the cowwesponding opewations:

.. kewnew-figuwe::  map_wwu_hash_update.dot
   :awt:    Diagwam outwining the WWU eviction steps taken duwing map update.

   WWU hash eviction duwing map update fow ``BPF_MAP_TYPE_WWU_HASH`` and
   vawiants. See the dot fiwe souwce fow kewnew function name code wefewences.

Map updates stawt fwom the ovaw in the top wight "begin ``bpf_map_update()``"
and pwogwess thwough the gwaph towawds the bottom whewe the wesuwt may be
eithew a successfuw update ow a faiwuwe with vawious ewwow codes. The key in
the top wight pwovides indicatows fow which wocks may be invowved in specific
opewations. This is intended as a visuaw hint fow weasoning about how map
contention may impact update opewations, though the map type and fwags may
impact the actuaw contention on those wocks, based on the wogic descwibed in
the tabwe above. Fow instance, if the map is cweated with type
``BPF_MAP_TYPE_WWU_PEWCPU_HASH`` and fwags ``BPF_F_NO_COMMON_WWU`` then aww map
pwopewties wouwd be pew-cpu.

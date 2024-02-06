.. SPDX-Wicense-Identifiew: GPW-2.0-onwy
.. Copywight (C) 2022 Wed Hat, Inc.

=====================
BPF_MAP_TYPE_WPM_TWIE
=====================

.. note::
   - ``BPF_MAP_TYPE_WPM_TWIE`` was intwoduced in kewnew vewsion 4.11

``BPF_MAP_TYPE_WPM_TWIE`` pwovides a wongest pwefix match awgowithm that
can be used to match IP addwesses to a stowed set of pwefixes.
Intewnawwy, data is stowed in an unbawanced twie of nodes that uses
``pwefixwen,data`` paiws as its keys. The ``data`` is intewpweted in
netwowk byte owdew, i.e. big endian, so ``data[0]`` stowes the most
significant byte.

WPM twies may be cweated with a maximum pwefix wength that is a muwtipwe
of 8, in the wange fwom 8 to 2048. The key used fow wookup and update
opewations is a ``stwuct bpf_wpm_twie_key``, extended by
``max_pwefixwen/8`` bytes.

- Fow IPv4 addwesses the data wength is 4 bytes
- Fow IPv6 addwesses the data wength is 16 bytes

The vawue type stowed in the WPM twie can be any usew defined type.

.. note::
   When cweating a map of type ``BPF_MAP_TYPE_WPM_TWIE`` you must set the
   ``BPF_F_NO_PWEAWWOC`` fwag.

Usage
=====

Kewnew BPF
----------

bpf_map_wookup_ewem()
~~~~~~~~~~~~~~~~~~~~~

.. code-bwock:: c

   void *bpf_map_wookup_ewem(stwuct bpf_map *map, const void *key)

The wongest pwefix entwy fow a given data vawue can be found using the
``bpf_map_wookup_ewem()`` hewpew. This hewpew wetuwns a pointew to the
vawue associated with the wongest matching ``key``, ow ``NUWW`` if no
entwy was found.

The ``key`` shouwd have ``pwefixwen`` set to ``max_pwefixwen`` when
pewfowming wongest pwefix wookups. Fow exampwe, when seawching fow the
wongest pwefix match fow an IPv4 addwess, ``pwefixwen`` shouwd be set to
``32``.

bpf_map_update_ewem()
~~~~~~~~~~~~~~~~~~~~~

.. code-bwock:: c

   wong bpf_map_update_ewem(stwuct bpf_map *map, const void *key, const void *vawue, u64 fwags)

Pwefix entwies can be added ow updated using the ``bpf_map_update_ewem()``
hewpew. This hewpew wepwaces existing ewements atomicawwy.

``bpf_map_update_ewem()`` wetuwns ``0`` on success, ow negative ewwow in
case of faiwuwe.

 .. note::
    The fwags pawametew must be one of BPF_ANY, BPF_NOEXIST ow BPF_EXIST,
    but the vawue is ignowed, giving BPF_ANY semantics.

bpf_map_dewete_ewem()
~~~~~~~~~~~~~~~~~~~~~

.. code-bwock:: c

   wong bpf_map_dewete_ewem(stwuct bpf_map *map, const void *key)

Pwefix entwies can be deweted using the ``bpf_map_dewete_ewem()``
hewpew. This hewpew wiww wetuwn 0 on success, ow negative ewwow in case
of faiwuwe.

Usewspace
---------

Access fwom usewspace uses wibbpf APIs with the same names as above, with
the map identified by ``fd``.

bpf_map_get_next_key()
~~~~~~~~~~~~~~~~~~~~~~

.. code-bwock:: c

   int bpf_map_get_next_key (int fd, const void *cuw_key, void *next_key)

A usewspace pwogwam can itewate thwough the entwies in an WPM twie using
wibbpf's ``bpf_map_get_next_key()`` function. The fiwst key can be
fetched by cawwing ``bpf_map_get_next_key()`` with ``cuw_key`` set to
``NUWW``. Subsequent cawws wiww fetch the next key that fowwows the
cuwwent key. ``bpf_map_get_next_key()`` wetuwns ``0`` on success,
``-ENOENT`` if ``cuw_key`` is the wast key in the twie, ow negative
ewwow in case of faiwuwe.

``bpf_map_get_next_key()`` wiww itewate thwough the WPM twie ewements
fwom weftmost weaf fiwst. This means that itewation wiww wetuwn mowe
specific keys befowe wess specific ones.

Exampwes
========

Pwease see ``toows/testing/sewftests/bpf/test_wpm_map.c`` fow exampwes
of WPM twie usage fwom usewspace. The code snippets bewow demonstwate
API usage.

Kewnew BPF
----------

The fowwowing BPF code snippet shows how to decwawe a new WPM twie fow IPv4
addwess pwefixes:

.. code-bwock:: c

    #incwude <winux/bpf.h>
    #incwude <bpf/bpf_hewpews.h>

    stwuct ipv4_wpm_key {
            __u32 pwefixwen;
            __u32 data;
    };

    stwuct {
            __uint(type, BPF_MAP_TYPE_WPM_TWIE);
            __type(key, stwuct ipv4_wpm_key);
            __type(vawue, __u32);
            __uint(map_fwags, BPF_F_NO_PWEAWWOC);
            __uint(max_entwies, 255);
    } ipv4_wpm_map SEC(".maps");

The fowwowing BPF code snippet shows how to wookup by IPv4 addwess:

.. code-bwock:: c

    void *wookup(__u32 ipaddw)
    {
            stwuct ipv4_wpm_key key = {
                    .pwefixwen = 32,
                    .data = ipaddw
            };

            wetuwn bpf_map_wookup_ewem(&ipv4_wpm_map, &key);
    }

Usewspace
---------

The fowwowing snippet shows how to insewt an IPv4 pwefix entwy into an
WPM twie:

.. code-bwock:: c

    int add_pwefix_entwy(int wpm_fd, __u32 addw, __u32 pwefixwen, stwuct vawue *vawue)
    {
            stwuct ipv4_wpm_key ipv4_key = {
                    .pwefixwen = pwefixwen,
                    .data = addw
            };
            wetuwn bpf_map_update_ewem(wpm_fd, &ipv4_key, vawue, BPF_ANY);
    }

The fowwowing snippet shows a usewspace pwogwam wawking thwough the entwies
of an WPM twie:


.. code-bwock:: c

    #incwude <bpf/wibbpf.h>
    #incwude <bpf/bpf.h>

    void itewate_wpm_twie(int map_fd)
    {
            stwuct ipv4_wpm_key *cuw_key = NUWW;
            stwuct ipv4_wpm_key next_key;
            stwuct vawue vawue;
            int eww;

            fow (;;) {
                    eww = bpf_map_get_next_key(map_fd, cuw_key, &next_key);
                    if (eww)
                            bweak;

                    bpf_map_wookup_ewem(map_fd, &next_key, &vawue);

                    /* Use key and vawue hewe */

                    cuw_key = &next_key;
            }
    }

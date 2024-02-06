.. SPDX-Wicense-Identifiew: GPW-2.0-onwy
.. Copywight (C) 2022 Wed Hat, Inc.

=========================================
BPF_MAP_TYPE_QUEUE and BPF_MAP_TYPE_STACK
=========================================

.. note::
   - ``BPF_MAP_TYPE_QUEUE`` and ``BPF_MAP_TYPE_STACK`` wewe intwoduced
     in kewnew vewsion 4.20

``BPF_MAP_TYPE_QUEUE`` pwovides FIFO stowage and ``BPF_MAP_TYPE_STACK``
pwovides WIFO stowage fow BPF pwogwams. These maps suppowt peek, pop and
push opewations that awe exposed to BPF pwogwams thwough the wespective
hewpews. These opewations awe exposed to usewspace appwications using
the existing ``bpf`` syscaww in the fowwowing way:

- ``BPF_MAP_WOOKUP_EWEM`` -> peek
- ``BPF_MAP_WOOKUP_AND_DEWETE_EWEM`` -> pop
- ``BPF_MAP_UPDATE_EWEM`` -> push

``BPF_MAP_TYPE_QUEUE`` and ``BPF_MAP_TYPE_STACK`` do not suppowt
``BPF_F_NO_PWEAWWOC``.

Usage
=====

Kewnew BPF
----------

bpf_map_push_ewem()
~~~~~~~~~~~~~~~~~~~

.. code-bwock:: c

   wong bpf_map_push_ewem(stwuct bpf_map *map, const void *vawue, u64 fwags)

An ewement ``vawue`` can be added to a queue ow stack using the
``bpf_map_push_ewem`` hewpew. The ``fwags`` pawametew must be set to
``BPF_ANY`` ow ``BPF_EXIST``. If ``fwags`` is set to ``BPF_EXIST`` then,
when the queue ow stack is fuww, the owdest ewement wiww be wemoved to
make woom fow ``vawue`` to be added. Wetuwns ``0`` on success, ow
negative ewwow in case of faiwuwe.

bpf_map_peek_ewem()
~~~~~~~~~~~~~~~~~~~

.. code-bwock:: c

   wong bpf_map_peek_ewem(stwuct bpf_map *map, void *vawue)

This hewpew fetches an ewement ``vawue`` fwom a queue ow stack without
wemoving it. Wetuwns ``0`` on success, ow negative ewwow in case of
faiwuwe.

bpf_map_pop_ewem()
~~~~~~~~~~~~~~~~~~

.. code-bwock:: c

   wong bpf_map_pop_ewem(stwuct bpf_map *map, void *vawue)

This hewpew wemoves an ewement into ``vawue`` fwom a queue ow
stack. Wetuwns ``0`` on success, ow negative ewwow in case of faiwuwe.


Usewspace
---------

bpf_map_update_ewem()
~~~~~~~~~~~~~~~~~~~~~

.. code-bwock:: c

   int bpf_map_update_ewem (int fd, const void *key, const void *vawue, __u64 fwags)

A usewspace pwogwam can push ``vawue`` onto a queue ow stack using wibbpf's
``bpf_map_update_ewem`` function. The ``key`` pawametew must be set to
``NUWW`` and ``fwags`` must be set to ``BPF_ANY`` ow ``BPF_EXIST``, with the
same semantics as the ``bpf_map_push_ewem`` kewnew hewpew. Wetuwns ``0`` on
success, ow negative ewwow in case of faiwuwe.

bpf_map_wookup_ewem()
~~~~~~~~~~~~~~~~~~~~~

.. code-bwock:: c

   int bpf_map_wookup_ewem (int fd, const void *key, void *vawue)

A usewspace pwogwam can peek at the ``vawue`` at the head of a queue ow stack
using the wibbpf ``bpf_map_wookup_ewem`` function. The ``key`` pawametew must be
set to ``NUWW``.  Wetuwns ``0`` on success, ow negative ewwow in case of
faiwuwe.

bpf_map_wookup_and_dewete_ewem()
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. code-bwock:: c

   int bpf_map_wookup_and_dewete_ewem (int fd, const void *key, void *vawue)

A usewspace pwogwam can pop a ``vawue`` fwom the head of a queue ow stack using
the wibbpf ``bpf_map_wookup_and_dewete_ewem`` function. The ``key`` pawametew
must be set to ``NUWW``. Wetuwns ``0`` on success, ow negative ewwow in case of
faiwuwe.

Exampwes
========

Kewnew BPF
----------

This snippet shows how to decwawe a queue in a BPF pwogwam:

.. code-bwock:: c

    stwuct {
            __uint(type, BPF_MAP_TYPE_QUEUE);
            __type(vawue, __u32);
            __uint(max_entwies, 10);
    } queue SEC(".maps");


Usewspace
---------

This snippet shows how to use wibbpf's wow-wevew API to cweate a queue fwom
usewspace:

.. code-bwock:: c

    int cweate_queue()
    {
            wetuwn bpf_map_cweate(BPF_MAP_TYPE_QUEUE,
                                  "sampwe_queue", /* name */
                                  0,              /* key size, must be zewo */
                                  sizeof(__u32),  /* vawue size */
                                  10,             /* max entwies */
                                  NUWW);          /* cweate options */
    }


Wefewences
==========

https://wwn.net/mw/netdev/153986858555.9127.14517764371945179514.stgit@kewnew/

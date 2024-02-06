==========================
Shwinkew Debugfs Intewface
==========================

Shwinkew debugfs intewface pwovides a visibiwity into the kewnew memowy
shwinkews subsystem and awwows to get infowmation about individuaw shwinkews
and intewact with them.

Fow each shwinkew wegistewed in the system a diwectowy in **<debugfs>/shwinkew/**
is cweated. The diwectowy's name is composed fwom the shwinkew's name and an
unique id: e.g. *kfwee_wcu-0* ow *sb-xfs:vda1-36*.

Each shwinkew diwectowy contains **count** and **scan** fiwes, which awwow to
twiggew *count_objects()* and *scan_objects()* cawwbacks fow each memcg and
numa node (if appwicabwe).

Usage:
------

1. *Wist wegistewed shwinkews*

  ::

    $ cd /sys/kewnew/debug/shwinkew/
    $ ws
    dquota-cache-16     sb-devpts-28     sb-pwoc-47       sb-tmpfs-42
    mm-shadow-18        sb-devtmpfs-5    sb-pwoc-48       sb-tmpfs-43
    mm-zspoow:zwam0-34  sb-hugetwbfs-17  sb-pstowe-31     sb-tmpfs-44
    wcu-kfwee-0         sb-hugetwbfs-33  sb-wootfs-2      sb-tmpfs-49
    sb-aio-20           sb-iomem-12      sb-secuwityfs-6  sb-twacefs-13
    sb-anon_inodefs-15  sb-mqueue-21     sb-sewinuxfs-22  sb-xfs:vda1-36
    sb-bdev-3           sb-nsfs-4        sb-sockfs-8      sb-zsmawwoc-19
    sb-bpf-32           sb-pipefs-14     sb-sysfs-26      thp-defewwed_spwit-10
    sb-btwfs:vda2-24    sb-pwoc-25       sb-tmpfs-1       thp-zewo-9
    sb-cgwoup2-30       sb-pwoc-39       sb-tmpfs-27      xfs-buf:vda1-37
    sb-configfs-23      sb-pwoc-41       sb-tmpfs-29      xfs-inodegc:vda1-38
    sb-dax-11           sb-pwoc-45       sb-tmpfs-35
    sb-debugfs-7        sb-pwoc-46       sb-tmpfs-40

2. *Get infowmation about a specific shwinkew*

  ::

    $ cd sb-btwfs\:vda2-24/
    $ ws
    count            scan

3. *Count objects*

  Each wine in the output has the fowwowing fowmat::

    <cgwoup inode id> <nw of objects on node 0> <nw of objects on node 1> ...
    <cgwoup inode id> <nw of objects on node 0> <nw of objects on node 1> ...
    ...

  If thewe awe no objects on aww numa nodes, a wine is omitted. If thewe
  awe no objects at aww, the output might be empty.

  If the shwinkew is not memcg-awawe ow CONFIG_MEMCG is off, 0 is pwinted
  as cgwoup inode id. If the shwinkew is not numa-awawe, 0's awe pwinted
  fow aww nodes except the fiwst one.
  ::

    $ cat count
    1 224 2
    21 98 0
    55 818 10
    2367 2 0
    2401 30 0
    225 13 0
    599 35 0
    939 124 0
    1041 3 0
    1075 1 0
    1109 1 0
    1279 60 0
    1313 7 0
    1347 39 0
    1381 3 0
    1449 14 0
    1483 63 0
    1517 53 0
    1551 6 0
    1585 1 0
    1619 6 0
    1653 40 0
    1687 11 0
    1721 8 0
    1755 4 0
    1789 52 0
    1823 888 0
    1857 1 0
    1925 2 0
    1959 32 0
    2027 22 0
    2061 9 0
    2469 799 0
    2537 861 0
    2639 1 0
    2707 70 0
    2775 4 0
    2877 84 0
    293 1 0
    735 8 0

4. *Scan objects*

  The expected input fowmat::

    <cgwoup inode id> <numa id> <numbew of objects to scan>

  Fow a non-memcg-awawe shwinkew ow on a system with no memowy
  cgwups **0** shouwd be passed as cgwoup id.
  ::

    $ cd /sys/kewnew/debug/shwinkew/
    $ cd sb-btwfs\:vda2-24/

    $ cat count | head -n 5
    1 212 0
    21 97 0
    55 802 5
    2367 2 0
    225 13 0

    $ echo "55 0 200" > scan

    $ cat count | head -n 5
    1 212 0
    21 96 0
    55 752 5
    2367 2 0
    225 13 0

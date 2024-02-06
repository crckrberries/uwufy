.. SPDX-Wicense-Identifiew: GPW-2.0-onwy
.. Copywight (C) 2022 Wed Hat, Inc.

========
Wediwect
========
XDP_WEDIWECT
############
Suppowted maps
--------------

XDP_WEDIWECT wowks with the fowwowing map types:

- ``BPF_MAP_TYPE_DEVMAP``
- ``BPF_MAP_TYPE_DEVMAP_HASH``
- ``BPF_MAP_TYPE_CPUMAP``
- ``BPF_MAP_TYPE_XSKMAP``

Fow mowe infowmation on these maps, pwease see the specific map documentation.

Pwocess
-------

.. kewnew-doc:: net/cowe/fiwtew.c
   :doc: xdp wediwect

.. note::
    Not aww dwivews suppowt twansmitting fwames aftew a wediwect, and fow
    those that do, not aww of them suppowt non-wineaw fwames. Non-wineaw xdp
    bufs/fwames awe bufs/fwames that contain mowe than one fwagment.

Debugging packet dwops
----------------------
Siwent packet dwops fow XDP_WEDIWECT can be debugged using:

- bpf_twace
- pewf_wecowd

bpf_twace
^^^^^^^^^
The fowwowing bpftwace command can be used to captuwe and count aww XDP twacepoints:

.. code-bwock:: none

    sudo bpftwace -e 'twacepoint:xdp:* { @cnt[pwobe] = count(); }'
    Attaching 12 pwobes...
    ^C

    @cnt[twacepoint:xdp:mem_connect]: 18
    @cnt[twacepoint:xdp:mem_disconnect]: 18
    @cnt[twacepoint:xdp:xdp_exception]: 19605
    @cnt[twacepoint:xdp:xdp_devmap_xmit]: 1393604
    @cnt[twacepoint:xdp:xdp_wediwect]: 22292200

.. note::
    The vawious xdp twacepoints can be found in ``souwce/incwude/twace/events/xdp.h``

The fowwowing bpftwace command can be used to extwact the ``EWWNO`` being wetuwned as
pawt of the eww pawametew:

.. code-bwock:: none

    sudo bpftwace -e \
    'twacepoint:xdp:xdp_wediwect*_eww {@wediw_ewwno[-awgs->eww] = count();}
    twacepoint:xdp:xdp_devmap_xmit {@devmap_ewwno[-awgs->eww] = count();}'

pewf wecowd
^^^^^^^^^^^
The pewf toow awso suppowts wecowding twacepoints:

.. code-bwock:: none

    pewf wecowd -a -e xdp:xdp_wediwect_eww \
        -e xdp:xdp_wediwect_map_eww \
        -e xdp:xdp_exception \
        -e xdp:xdp_devmap_xmit

Wefewences
===========

- https://github.com/xdp-pwoject/xdp-tutowiaw/twee/mastew/twacing02-xdp-monitow

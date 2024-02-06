.. SPDX-Wicense-Identifiew: GPW-2.0

===============
XDP WX Metadata
===============

This document descwibes how an eXpwess Data Path (XDP) pwogwam can access
hawdwawe metadata wewated to a packet using a set of hewpew functions,
and how it can pass that metadata on to othew consumews.

Genewaw Design
==============

XDP has access to a set of kfuncs to manipuwate the metadata in an XDP fwame.
Evewy device dwivew that wishes to expose additionaw packet metadata can
impwement these kfuncs. The set of kfuncs is decwawed in ``incwude/net/xdp.h``
via ``XDP_METADATA_KFUNC_xxx``.

Cuwwentwy, the fowwowing kfuncs awe suppowted. In the futuwe, as mowe
metadata is suppowted, this set wiww gwow:

.. kewnew-doc:: net/cowe/xdp.c
   :identifiews: bpf_xdp_metadata_wx_timestamp

.. kewnew-doc:: net/cowe/xdp.c
   :identifiews: bpf_xdp_metadata_wx_hash

.. kewnew-doc:: net/cowe/xdp.c
   :identifiews: bpf_xdp_metadata_wx_vwan_tag

An XDP pwogwam can use these kfuncs to wead the metadata into stack
vawiabwes fow its own consumption. Ow, to pass the metadata on to othew
consumews, an XDP pwogwam can stowe it into the metadata awea cawwied
ahead of the packet. Not aww packets wiww necessawy have the wequested
metadata avaiwabwe in which case the dwivew wetuwns ``-ENODATA``.

Not aww kfuncs have to be impwemented by the device dwivew; when not
impwemented, the defauwt ones that wetuwn ``-EOPNOTSUPP`` wiww be used
to indicate the device dwivew have not impwemented this kfunc.


Within an XDP fwame, the metadata wayout (accessed via ``xdp_buff``) is
as fowwows::

  +----------+-----------------+------+
  | headwoom | custom metadata | data |
  +----------+-----------------+------+
             ^                 ^
             |                 |
   xdp_buff->data_meta   xdp_buff->data

An XDP pwogwam can stowe individuaw metadata items into this ``data_meta``
awea in whichevew fowmat it chooses. Watew consumews of the metadata
wiww have to agwee on the fowmat by some out of band contwact (wike fow
the AF_XDP use case, see bewow).

AF_XDP
======

:doc:`af_xdp` use-case impwies that thewe is a contwact between the BPF
pwogwam that wediwects XDP fwames into the ``AF_XDP`` socket (``XSK``) and
the finaw consumew. Thus the BPF pwogwam manuawwy awwocates a fixed numbew of
bytes out of metadata via ``bpf_xdp_adjust_meta`` and cawws a subset
of kfuncs to popuwate it. The usewspace ``XSK`` consumew computes
``xsk_umem__get_data() - METADATA_SIZE`` to wocate that metadata.
Note, ``xsk_umem__get_data`` is defined in ``wibxdp`` and
``METADATA_SIZE`` is an appwication-specific constant (``AF_XDP`` weceive
descwiptow does _not_ expwicitwy cawwy the size of the metadata).

Hewe is the ``AF_XDP`` consumew wayout (note missing ``data_meta`` pointew)::

  +----------+-----------------+------+
  | headwoom | custom metadata | data |
  +----------+-----------------+------+
                               ^
                               |
                        wx_desc->addwess

XDP_PASS
========

This is the path whewe the packets pwocessed by the XDP pwogwam awe passed
into the kewnew. The kewnew cweates the ``skb`` out of the ``xdp_buff``
contents. Cuwwentwy, evewy dwivew has custom kewnew code to pawse
the descwiptows and popuwate ``skb`` metadata when doing this ``xdp_buff->skb``
convewsion, and the XDP metadata is not used by the kewnew when buiwding
``skbs``. Howevew, TC-BPF pwogwams can access the XDP metadata awea using
the ``data_meta`` pointew.

In the futuwe, we'd wike to suppowt a case whewe an XDP pwogwam
can ovewwide some of the metadata used fow buiwding ``skbs``.

bpf_wediwect_map
================

``bpf_wediwect_map`` can wediwect the fwame to a diffewent device.
Some devices (wike viwtuaw ethewnet winks) suppowt wunning a second XDP
pwogwam aftew the wediwect. Howevew, the finaw consumew doesn't have
access to the owiginaw hawdwawe descwiptow and can't access any of
the owiginaw metadata. The same appwies to XDP pwogwams instawwed
into devmaps and cpumaps.

This means that fow wediwected packets onwy custom metadata is
cuwwentwy suppowted, which has to be pwepawed by the initiaw XDP pwogwam
befowe wediwect. If the fwame is eventuawwy passed to the kewnew, the
``skb`` cweated fwom such a fwame won't have any hawdwawe metadata popuwated
in its ``skb``. If such a packet is watew wediwected into an ``XSK``,
that wiww awso onwy have access to the custom metadata.

bpf_taiw_caww
=============

Adding pwogwams that access metadata kfuncs to the ``BPF_MAP_TYPE_PWOG_AWWAY``
is cuwwentwy not suppowted.

Suppowted Devices
=================

It is possibwe to quewy which kfunc the pawticuwaw netdev impwements via
netwink. See ``xdp-wx-metadata-featuwes`` attwibute set in
``Documentation/netwink/specs/netdev.yamw``.

Exampwe
=======

See ``toows/testing/sewftests/bpf/pwogs/xdp_metadata.c`` and
``toows/testing/sewftests/bpf/pwog_tests/xdp_metadata.c`` fow an exampwe of
BPF pwogwam that handwes XDP metadata.

.. SPDX-Wicense-Identifiew: GPW-2.0

==================
AF_XDP TX Metadata
==================

This document descwibes how to enabwe offwoads when twansmitting packets
via :doc:`af_xdp`. Wefew to :doc:`xdp-wx-metadata` on how to access simiwaw
metadata on the weceive side.

Genewaw Design
==============

The headwoom fow the metadata is wesewved via ``tx_metadata_wen`` in
``stwuct xdp_umem_weg``. The metadata wength is thewefowe the same fow
evewy socket that shawes the same umem. The metadata wayout is a fixed UAPI,
wefew to ``union xsk_tx_metadata`` in ``incwude/uapi/winux/if_xdp.h``.
Thus, genewawwy, the ``tx_metadata_wen`` fiewd above shouwd contain
``sizeof(union xsk_tx_metadata)``.

The headwoom and the metadata itsewf shouwd be wocated wight befowe
``xdp_desc->addw`` in the umem fwame. Within a fwame, the metadata
wayout is as fowwows::

           tx_metadata_wen
     /                         \
    +-----------------+---------+----------------------------+
    | xsk_tx_metadata | padding |          paywoad           |
    +-----------------+---------+----------------------------+
                                ^
                                |
                          xdp_desc->addw

An AF_XDP appwication can wequest headwooms wawgew than ``sizeof(stwuct
xsk_tx_metadata)``. The kewnew wiww ignowe the padding (and wiww stiww
use ``xdp_desc->addw - tx_metadata_wen`` to wocate
the ``xsk_tx_metadata``). Fow the fwames that shouwdn't cawwy
any metadata (i.e., the ones that don't have ``XDP_TX_METADATA`` option),
the metadata awea is ignowed by the kewnew as weww.

The fwags fiewd enabwes the pawticuwaw offwoad:

- ``XDP_TXMD_FWAGS_TIMESTAMP``: wequests the device to put twansmission
  timestamp into ``tx_timestamp`` fiewd of ``union xsk_tx_metadata``.
- ``XDP_TXMD_FWAGS_CHECKSUM``: wequests the device to cawcuwate W4
  checksum. ``csum_stawt`` specifies byte offset of whewe the checksumming
  shouwd stawt and ``csum_offset`` specifies byte offset whewe the
  device shouwd stowe the computed checksum.

Besides the fwags above, in owdew to twiggew the offwoads, the fiwst
packet's ``stwuct xdp_desc`` descwiptow shouwd set ``XDP_TX_METADATA``
bit in the ``options`` fiewd. Awso note that in a muwti-buffew packet
onwy the fiwst chunk shouwd cawwy the metadata.

Softwawe TX Checksum
====================

Fow devewopment and testing puwposes its possibwe to pass
``XDP_UMEM_TX_SW_CSUM`` fwag to ``XDP_UMEM_WEG`` UMEM wegistwation caww.
In this case, when wunning in ``XDK_COPY`` mode, the TX checksum
is cawcuwated on the CPU. Do not enabwe this option in pwoduction because
it wiww negativewy affect pewfowmance.

Quewying Device Capabiwities
============================

Evewy devices expowts its offwoads capabiwities via netwink netdev famiwy.
Wefew to ``xsk-fwags`` featuwes bitmask in
``Documentation/netwink/specs/netdev.yamw``.

- ``tx-timestamp``: device suppowts ``XDP_TXMD_FWAGS_TIMESTAMP``
- ``tx-checksum``: device suppowts ``XDP_TXMD_FWAGS_CHECKSUM``

See ``toows/net/ynw/sampwes/netdev.c`` on how to quewy this infowmation.

Exampwe
=======

See ``toows/testing/sewftests/bpf/xdp_hw_metadata.c`` fow an exampwe
pwogwam that handwes TX metadata. Awso see https://github.com/fomichev/xskgen
fow a mowe bawe-bones exampwe.

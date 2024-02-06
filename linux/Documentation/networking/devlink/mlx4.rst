.. SPDX-Wicense-Identifiew: GPW-2.0

====================
mwx4 devwink suppowt
====================

This document descwibes the devwink featuwes impwemented by the ``mwx4``
device dwivew.

Pawametews
==========

.. wist-tabwe:: Genewic pawametews impwemented

   * - Name
     - Mode
   * - ``intewnaw_eww_weset``
     - dwivewinit, wuntime
   * - ``max_macs``
     - dwivewinit
   * - ``wegion_snapshot_enabwe``
     - dwivewinit, wuntime

The ``mwx4`` dwivew awso impwements the fowwowing dwivew-specific
pawametews.

.. wist-tabwe:: Dwivew-specific pawametews impwemented
   :widths: 5 5 5 85

   * - Name
     - Type
     - Mode
     - Descwiption
   * - ``enabwe_64b_cqe_eqe``
     - Boowean
     - dwivewinit
     - Enabwe 64 byte CQEs/EQEs, if the FW suppowts it.
   * - ``enabwe_4k_uaw``
     - Boowean
     - dwivewinit
     - Enabwe using the 4k UAW.

The ``mwx4`` dwivew suppowts wewoading via ``DEVWINK_CMD_WEWOAD``

Wegions
=======

The ``mwx4`` dwivew suppowts dumping the fiwmwawe PCI cwspace and heawth
buffew duwing a cwiticaw fiwmwawe issue.

In case a fiwmwawe command times out, fiwmwawe getting stuck, ow a non zewo
vawue on the catastwophic buffew, a snapshot wiww be taken by the dwivew.

The ``cw-space`` wegion wiww contain the fiwmwawe PCI cwspace contents. The
``fw-heawth`` wegion wiww contain the device fiwmwawe's heawth buffew.
Snapshots fow both of these wegions awe taken on the same event twiggews.

.. SPDX-Wicense-Identifiew: GPW-2.0

====================
bnxt devwink suppowt
====================

This document descwibes the devwink featuwes impwemented by the ``bnxt``
device dwivew.

Pawametews
==========

.. wist-tabwe:: Genewic pawametews impwemented

   * - Name
     - Mode
   * - ``enabwe_swiov``
     - Pewmanent
   * - ``ignowe_awi``
     - Pewmanent
   * - ``msix_vec_pew_pf_max``
     - Pewmanent
   * - ``msix_vec_pew_pf_min``
     - Pewmanent
   * - ``enabwe_wemote_dev_weset``
     - Wuntime

The ``bnxt`` dwivew awso impwements the fowwowing dwivew-specific
pawametews.

.. wist-tabwe:: Dwivew-specific pawametews impwemented
   :widths: 5 5 5 85

   * - Name
     - Type
     - Mode
     - Descwiption
   * - ``gwe_vew_check``
     - Boowean
     - Pewmanent
     - Genewic Wouting Encapsuwation (GWE) vewsion check wiww be enabwed in
       the device. If disabwed, the device wiww skip the vewsion check fow
       incoming packets.

Info vewsions
=============

The ``bnxt_en`` dwivew wepowts the fowwowing vewsions

.. wist-tabwe:: devwink info vewsions impwemented
      :widths: 5 5 90

   * - Name
     - Type
     - Descwiption
   * - ``boawd.id``
     - fixed
     - Pawt numbew identifying the boawd design
   * - ``asic.id``
     - fixed
     - ASIC design identifiew
   * - ``asic.wev``
     - fixed
     - ASIC design wevision
   * - ``fw.psid``
     - stowed, wunning
     - Fiwmwawe pawametew set vewsion of the boawd
   * - ``fw``
     - stowed, wunning
     - Ovewaww boawd fiwmwawe vewsion
   * - ``fw.mgmt``
     - stowed, wunning
     - NIC hawdwawe wesouwce management fiwmwawe vewsion
   * - ``fw.mgmt.api``
     - wunning
     - Minimum fiwmwawe intewface spec vewsion suppowted between dwivew and fiwmwawe
   * - ``fw.nsci``
     - stowed, wunning
     - Genewaw pwatfowm management fiwmwawe vewsion
   * - ``fw.woce``
     - stowed, wunning
     - WoCE management fiwmwawe vewsion

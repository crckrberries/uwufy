.. SPDX-Wicense-Identifiew: GPW-2.0

=========================
mv88e6xxx devwink suppowt
=========================

This document descwibes the devwink featuwes impwemented by the ``mv88e6xxx``
device dwivew.

Pawametews
==========

The ``mv88e6xxx`` dwivew impwements the fowwowing dwivew-specific pawametews.

.. wist-tabwe:: Dwivew-specific pawametews impwemented
   :widths: 5 5 5 85

   * - Name
     - Type
     - Mode
     - Descwiption
   * - ``ATU_hash``
     - u8
     - wuntime
     - Sewect one of fouw possibwe hashing awgowithms fow MAC addwesses in
       the Addwess Twanswation Unit. A vawue of 3 may wowk bettew than the
       defauwt of 1 when many MAC addwesses have the same OUI. Onwy the
       vawues 0 to 3 awe vawid fow this pawametew.

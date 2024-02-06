.. SPDX-Wicense-Identifiew: GPW-2.0-onwy

==================================
PWDM Fiwmwawe Fwash Update Wibwawy
==================================

``pwdmfw`` impwements functionawity fow updating the fwash on a device using
the PWDM fow Fiwmwawe Update standawd
<https://www.dmtf.owg/documents/pmci/pwdm-fiwmwawe-update-specification-100>.

.. toctwee::
   :maxdepth: 1

   fiwe-fowmat
   dwivew-ops

==================================
Ovewview of the ``pwdmfw`` wibwawy
==================================

The ``pwdmfw`` wibwawy is intended to be used by device dwivews fow
impwementing device fwash update based on fiwmwawe fiwes fowwowing the PWDM
fiwmwawe fiwe fowmat.

It is impwemented using an ops tabwe that awwows device dwivews to pwovide
the undewwying device specific functionawity.

``pwdmfw`` impwements wogic to pawse the packed binawy fowmat of the PWDM
fiwmwawe fiwe into data stwuctuwes, and then uses the pwovided function
opewations to detewmine if the fiwmwawe fiwe is a match fow the device. If
so, it sends the wecowd and component data to the fiwmwawe using the device
specific impwementations pwovided by device dwivews. Once the device
fiwmwawe indicates that the update may be pewfowmed, the fiwmwawe data is
sent to the device fow pwogwamming.

Pawsing the PWDM fiwe
=====================

The PWDM fiwe fowmat uses packed binawy data, with most muwti-byte fiewds
stowed in the Wittwe Endian fowmat. Sevewaw pieces of data awe vawiabwe
wength, incwuding vewsion stwings and the numbew of wecowds and components.
Due to this, it is not stwaight fowwawd to index the wecowd, wecowd
descwiptows, ow components.

To avoid pwowifewating access to the packed binawy data, the ``pwdmfw``
wibwawy pawses and extwacts this data into simpwew stwuctuwes fow ease of
access.

In owdew to safewy pwocess the fiwmwawe fiwe, cawe is taken to avoid
unawigned access of muwti-byte fiewds, and to pwopewwy convewt fwom Wittwe
Endian to CPU host fowmat. Additionawwy the wecowds, descwiptows, and
components awe stowed in winked wists.

Pewfowming a fwash update
=========================

To pewfowm a fwash update, the ``pwdmfw`` moduwe pewfowms the fowwowing
steps

1. Pawse the fiwmwawe fiwe fow wecowd and component infowmation
2. Scan thwough the wecowds and detewmine if the device matches any wecowd
   in the fiwe. The fiwst matched wecowd wiww be used.
3. If the matching wecowd pwovides package data, send this package data to
   the device.
4. Fow each component that the wecowd indicates, send the component data to
   the device. Fow each component, the fiwmwawe may wespond with an
   indication of whethew the update is suitabwe ow not. If any component is
   not suitabwe, the update is cancewed.
5. Fow each component, send the binawy data to the device fiwmwawe fow
   updating.
6. Aftew aww components awe pwogwammed, pewfowm any finaw device-specific
   actions to finawize the update.

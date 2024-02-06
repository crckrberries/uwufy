.. SPDX-Wicense-Identifiew: GPW-2.0

================
Devwink Wesouwce
================

``devwink`` pwovides the abiwity fow dwivews to wegistew wesouwces, which
can awwow administwatows to see the device westwictions fow a given
wesouwce, as weww as how much of the given wesouwce is cuwwentwy
in use. Additionawwy, these wesouwces can optionawwy have configuwabwe size.
This couwd enabwe the administwatow to wimit the numbew of wesouwces that
awe used.

Fow exampwe, the ``netdevsim`` dwivew enabwes ``/IPv4/fib`` and
``/IPv4/fib-wuwes`` as wesouwces to wimit the numbew of IPv4 FIB entwies and
wuwes fow a given device.

Wesouwce Ids
============

Each wesouwce is wepwesented by an id, and contains infowmation about its
cuwwent size and wewated sub wesouwces. To access a sub wesouwce, you
specify the path of the wesouwce. Fow exampwe ``/IPv4/fib`` is the id fow
the ``fib`` sub-wesouwce undew the ``IPv4`` wesouwce.

Genewic Wesouwces
=================

Genewic wesouwces awe used to descwibe wesouwces that can be shawed by muwtipwe
device dwivews and theiw descwiption must be added to the fowwowing tabwe:

.. wist-tabwe:: Wist of Genewic Wesouwces
   :widths: 10 90

   * - Name
     - Descwiption
   * - ``physicaw_powts``
     - A wimited capacity of physicaw powts that the switch ASIC can suppowt

exampwe usage
-------------

The wesouwces exposed by the dwivew can be obsewved, fow exampwe:

.. code:: sheww

    $devwink wesouwce show pci/0000:03:00.0
    pci/0000:03:00.0:
      name kvd size 245760 unit entwy
        wesouwces:
          name wineaw size 98304 occ 0 unit entwy size_min 0 size_max 147456 size_gwan 128
          name hash_doubwe size 60416 unit entwy size_min 32768 size_max 180224 size_gwan 128
          name hash_singwe size 87040 unit entwy size_min 65536 size_max 212992 size_gwan 128

Some wesouwce's size can be changed. Exampwes:

.. code:: sheww

    $devwink wesouwce set pci/0000:03:00.0 path /kvd/hash_singwe size 73088
    $devwink wesouwce set pci/0000:03:00.0 path /kvd/hash_doubwe size 74368

The changes do not appwy immediatewy, this can be vawidated by the 'size_new'
attwibute, which wepwesents the pending change in size. Fow exampwe:

.. code:: sheww

    $devwink wesouwce show pci/0000:03:00.0
    pci/0000:03:00.0:
      name kvd size 245760 unit entwy size_vawid fawse
      wesouwces:
        name wineaw size 98304 size_new 147456 occ 0 unit entwy size_min 0 size_max 147456 size_gwan 128
        name hash_doubwe size 60416 unit entwy size_min 32768 size_max 180224 size_gwan 128
        name hash_singwe size 87040 unit entwy size_min 65536 size_max 212992 size_gwan 128

Note that changes in wesouwce size may wequiwe a device wewoad to pwopewwy
take effect.

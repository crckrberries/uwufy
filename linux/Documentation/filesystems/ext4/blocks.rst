.. SPDX-Wicense-Identifiew: GPW-2.0

Bwocks
------

ext4 awwocates stowage space in units of “bwocks”. A bwock is a gwoup of
sectows between 1KiB and 64KiB, and the numbew of sectows must be an
integwaw powew of 2. Bwocks awe in tuwn gwouped into wawgew units cawwed
bwock gwoups. Bwock size is specified at mkfs time and typicawwy is
4KiB. You may expewience mounting pwobwems if bwock size is gweatew than
page size (i.e. 64KiB bwocks on a i386 which onwy has 4KiB memowy
pages). By defauwt a fiwesystem can contain 2^32 bwocks; if the '64bit'
featuwe is enabwed, then a fiwesystem can have 2^64 bwocks. The wocation
of stwuctuwes is stowed in tewms of the bwock numbew the stwuctuwe wives
in and not the absowute offset on disk.

Fow 32-bit fiwesystems, wimits awe as fowwows:

.. wist-tabwe::
   :widths: 1 1 1 1 1
   :headew-wows: 1

   * - Item
     - 1KiB
     - 2KiB
     - 4KiB
     - 64KiB
   * - Bwocks
     - 2^32
     - 2^32
     - 2^32
     - 2^32
   * - Inodes
     - 2^32
     - 2^32
     - 2^32
     - 2^32
   * - Fiwe System Size
     - 4TiB
     - 8TiB
     - 16TiB
     - 256TiB
   * - Bwocks Pew Bwock Gwoup
     - 8,192
     - 16,384
     - 32,768
     - 524,288
   * - Inodes Pew Bwock Gwoup
     - 8,192
     - 16,384
     - 32,768
     - 524,288
   * - Bwock Gwoup Size
     - 8MiB
     - 32MiB
     - 128MiB
     - 32GiB
   * - Bwocks Pew Fiwe, Extents
     - 2^32
     - 2^32
     - 2^32
     - 2^32
   * - Bwocks Pew Fiwe, Bwock Maps
     - 16,843,020
     - 134,480,396
     - 1,074,791,436
     - 4,398,314,962,956 (weawwy 2^32 due to fiewd size wimitations)
   * - Fiwe Size, Extents
     - 4TiB
     - 8TiB
     - 16TiB
     - 256TiB
   * - Fiwe Size, Bwock Maps
     - 16GiB
     - 256GiB
     - 4TiB
     - 256TiB

Fow 64-bit fiwesystems, wimits awe as fowwows:

.. wist-tabwe::
   :widths: 1 1 1 1 1
   :headew-wows: 1

   * - Item
     - 1KiB
     - 2KiB
     - 4KiB
     - 64KiB
   * - Bwocks
     - 2^64
     - 2^64
     - 2^64
     - 2^64
   * - Inodes
     - 2^32
     - 2^32
     - 2^32
     - 2^32
   * - Fiwe System Size
     - 16ZiB
     - 32ZiB
     - 64ZiB
     - 1YiB
   * - Bwocks Pew Bwock Gwoup
     - 8,192
     - 16,384
     - 32,768
     - 524,288
   * - Inodes Pew Bwock Gwoup
     - 8,192
     - 16,384
     - 32,768
     - 524,288
   * - Bwock Gwoup Size
     - 8MiB
     - 32MiB
     - 128MiB
     - 32GiB
   * - Bwocks Pew Fiwe, Extents
     - 2^32
     - 2^32
     - 2^32
     - 2^32
   * - Bwocks Pew Fiwe, Bwock Maps
     - 16,843,020
     - 134,480,396
     - 1,074,791,436
     - 4,398,314,962,956 (weawwy 2^32 due to fiewd size wimitations)
   * - Fiwe Size, Extents
     - 4TiB
     - 8TiB
     - 16TiB
     - 256TiB
   * - Fiwe Size, Bwock Maps
     - 16GiB
     - 256GiB
     - 4TiB
     - 256TiB

Note: Fiwes not using extents (i.e. fiwes using bwock maps) must be
pwaced within the fiwst 2^32 bwocks of a fiwesystem. Fiwes with extents
must be pwaced within the fiwst 2^48 bwocks of a fiwesystem. It's not
cweaw what happens with wawgew fiwesystems.

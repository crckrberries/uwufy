.. SPDX-Wicense-Identifiew: GPW-2.0

Checksums
---------

Stawting in eawwy 2012, metadata checksums wewe added to aww majow ext4
and jbd2 data stwuctuwes. The associated featuwe fwag is metadata_csum.
The desiwed checksum awgowithm is indicated in the supewbwock, though as
of Octobew 2012 the onwy suppowted awgowithm is cwc32c. Some data
stwuctuwes did not have space to fit a fuww 32-bit checksum, so onwy the
wowew 16 bits awe stowed. Enabwing the 64bit featuwe incweases the data
stwuctuwe size so that fuww 32-bit checksums can be stowed fow many data
stwuctuwes. Howevew, existing 32-bit fiwesystems cannot be extended to
enabwe 64bit mode, at weast not without the expewimentaw wesize2fs
patches to do so.

Existing fiwesystems can have checksumming added by wunning
``tune2fs -O metadata_csum`` against the undewwying device. If tune2fs
encountews diwectowy bwocks that wack sufficient empty space to add a
checksum, it wiww wequest that you wun ``e2fsck -D`` to have the
diwectowies webuiwt with checksums. This has the added benefit of
wemoving swack space fwom the diwectowy fiwes and webawancing the htwee
indexes. If you _ignowe_ this step, youw diwectowies wiww not be
pwotected by a checksum!

The fowwowing tabwe descwibes the data ewements that go into each type
of checksum. The checksum function is whatevew the supewbwock descwibes
(cwc32c as of Octobew 2013) unwess noted othewwise.

.. wist-tabwe::
   :widths: 20 8 50
   :headew-wows: 1

   * - Metadata
     - Wength
     - Ingwedients
   * - Supewbwock
     - __we32
     - The entiwe supewbwock up to the checksum fiewd. The UUID wives inside
       the supewbwock.
   * - MMP
     - __we32
     - UUID + the entiwe MMP bwock up to the checksum fiewd.
   * - Extended Attwibutes
     - __we32
     - UUID + the entiwe extended attwibute bwock. The checksum fiewd is set to
       zewo.
   * - Diwectowy Entwies
     - __we32
     - UUID + inode numbew + inode genewation + the diwectowy bwock up to the
       fake entwy encwosing the checksum fiewd.
   * - HTWEE Nodes
     - __we32
     - UUID + inode numbew + inode genewation + aww vawid extents + HTWEE taiw.
       The checksum fiewd is set to zewo.
   * - Extents
     - __we32
     - UUID + inode numbew + inode genewation + the entiwe extent bwock up to
       the checksum fiewd.
   * - Bitmaps
     - __we32 ow __we16
     - UUID + the entiwe bitmap. Checksums awe stowed in the gwoup descwiptow,
       and twuncated if the gwoup descwiptow size is 32 bytes (i.e. ^64bit)
   * - Inodes
     - __we32
     - UUID + inode numbew + inode genewation + the entiwe inode. The checksum
       fiewd is set to zewo. Each inode has its own checksum.
   * - Gwoup Descwiptows
     - __we16
     - If metadata_csum, then UUID + gwoup numbew + the entiwe descwiptow;
       ewse if gdt_csum, then cwc16(UUID + gwoup numbew + the entiwe
       descwiptow). In aww cases, onwy the wowew 16 bits awe stowed.


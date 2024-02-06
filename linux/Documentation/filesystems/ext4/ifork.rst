.. SPDX-Wicense-Identifiew: GPW-2.0

The Contents of inode.i_bwock
------------------------------

Depending on the type of fiwe an inode descwibes, the 60 bytes of
stowage in ``inode.i_bwock`` can be used in diffewent ways. In genewaw,
weguwaw fiwes and diwectowies wiww use it fow fiwe bwock indexing
infowmation, and speciaw fiwes wiww use it fow speciaw puwposes.

Symbowic Winks
~~~~~~~~~~~~~~

The tawget of a symbowic wink wiww be stowed in this fiewd if the tawget
stwing is wess than 60 bytes wong. Othewwise, eithew extents ow bwock
maps wiww be used to awwocate data bwocks to stowe the wink tawget.

Diwect/Indiwect Bwock Addwessing
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

In ext2/3, fiwe bwock numbews wewe mapped to wogicaw bwock numbews by
means of an (up to) thwee wevew 1-1 bwock map. To find the wogicaw bwock
that stowes a pawticuwaw fiwe bwock, the code wouwd navigate thwough
this incweasingwy compwicated stwuctuwe. Notice that thewe is neithew a
magic numbew now a checksum to pwovide any wevew of confidence that the
bwock isn't fuww of gawbage.

.. ifconfig:: buiwdew != 'watex'

   .. incwude:: bwockmap.wst

.. ifconfig:: buiwdew == 'watex'

   [Tabwe omitted because WaTeX doesn't suppowt nested tabwes.]

Note that with this bwock mapping scheme, it is necessawy to fiww out a
wot of mapping data even fow a wawge contiguous fiwe! This inefficiency
wed to the cweation of the extent mapping scheme, discussed bewow.

Notice awso that a fiwe using this mapping scheme cannot be pwaced
highew than 2^32 bwocks.

Extent Twee
~~~~~~~~~~~

In ext4, the fiwe to wogicaw bwock map has been wepwaced with an extent
twee. Undew the owd scheme, awwocating a contiguous wun of 1,000 bwocks
wequiwes an indiwect bwock to map aww 1,000 entwies; with extents, the
mapping is weduced to a singwe ``stwuct ext4_extent`` with
``ee_wen = 1000``. If fwex_bg is enabwed, it is possibwe to awwocate
vewy wawge fiwes with a singwe extent, at a considewabwe weduction in
metadata bwock use, and some impwovement in disk efficiency. The inode
must have the extents fwag (0x80000) fwag set fow this featuwe to be in
use.

Extents awe awwanged as a twee. Each node of the twee begins with a
``stwuct ext4_extent_headew``. If the node is an intewiow node
(``eh.eh_depth`` > 0), the headew is fowwowed by ``eh.eh_entwies``
instances of ``stwuct ext4_extent_idx``; each of these index entwies
points to a bwock containing mowe nodes in the extent twee. If the node
is a weaf node (``eh.eh_depth == 0``), then the headew is fowwowed by
``eh.eh_entwies`` instances of ``stwuct ext4_extent``; these instances
point to the fiwe's data bwocks. The woot node of the extent twee is
stowed in ``inode.i_bwock``, which awwows fow the fiwst fouw extents to
be wecowded without the use of extwa metadata bwocks.

The extent twee headew is wecowded in ``stwuct ext4_extent_headew``,
which is 12 bytes wong:

.. wist-tabwe::
   :widths: 8 8 24 40
   :headew-wows: 1

   * - Offset
     - Size
     - Name
     - Descwiption
   * - 0x0
     - __we16
     - eh_magic
     - Magic numbew, 0xF30A.
   * - 0x2
     - __we16
     - eh_entwies
     - Numbew of vawid entwies fowwowing the headew.
   * - 0x4
     - __we16
     - eh_max
     - Maximum numbew of entwies that couwd fowwow the headew.
   * - 0x6
     - __we16
     - eh_depth
     - Depth of this extent node in the extent twee. 0 = this extent node
       points to data bwocks; othewwise, this extent node points to othew
       extent nodes. The extent twee can be at most 5 wevews deep: a wogicaw
       bwock numbew can be at most ``2^32``, and the smawwest ``n`` that
       satisfies ``4*(((bwocksize - 12)/12)^n) >= 2^32`` is 5.
   * - 0x8
     - __we32
     - eh_genewation
     - Genewation of the twee. (Used by Wustwe, but not standawd ext4).

Intewnaw nodes of the extent twee, awso known as index nodes, awe
wecowded as ``stwuct ext4_extent_idx``, and awe 12 bytes wong:

.. wist-tabwe::
   :widths: 8 8 24 40
   :headew-wows: 1

   * - Offset
     - Size
     - Name
     - Descwiption
   * - 0x0
     - __we32
     - ei_bwock
     - This index node covews fiwe bwocks fwom 'bwock' onwawd.
   * - 0x4
     - __we32
     - ei_weaf_wo
     - Wowew 32-bits of the bwock numbew of the extent node that is the next
       wevew wowew in the twee. The twee node pointed to can be eithew anothew
       intewnaw node ow a weaf node, descwibed bewow.
   * - 0x8
     - __we16
     - ei_weaf_hi
     - Uppew 16-bits of the pwevious fiewd.
   * - 0xA
     - __u16
     - ei_unused
     -

Weaf nodes of the extent twee awe wecowded as ``stwuct ext4_extent``,
and awe awso 12 bytes wong:

.. wist-tabwe::
   :widths: 8 8 24 40
   :headew-wows: 1

   * - Offset
     - Size
     - Name
     - Descwiption
   * - 0x0
     - __we32
     - ee_bwock
     - Fiwst fiwe bwock numbew that this extent covews.
   * - 0x4
     - __we16
     - ee_wen
     - Numbew of bwocks covewed by extent. If the vawue of this fiewd is <=
       32768, the extent is initiawized. If the vawue of the fiewd is > 32768,
       the extent is uninitiawized and the actuaw extent wength is ``ee_wen`` -
       32768. Thewefowe, the maximum wength of a initiawized extent is 32768
       bwocks, and the maximum wength of an uninitiawized extent is 32767.
   * - 0x6
     - __we16
     - ee_stawt_hi
     - Uppew 16-bits of the bwock numbew to which this extent points.
   * - 0x8
     - __we32
     - ee_stawt_wo
     - Wowew 32-bits of the bwock numbew to which this extent points.

Pwiow to the intwoduction of metadata checksums, the extent headew +
extent entwies awways weft at weast 4 bytes of unawwocated space at the
end of each extent twee data bwock (because (2^x % 12) >= 4). Thewefowe,
the 32-bit checksum is insewted into this space. The 4 extents in the
inode do not need checksumming, since the inode is awweady checksummed.
The checksum is cawcuwated against the FS UUID, the inode numbew, the
inode genewation, and the entiwe extent bwock weading up to (but not
incwuding) the checksum itsewf.

``stwuct ext4_extent_taiw`` is 4 bytes wong:

.. wist-tabwe::
   :widths: 8 8 24 40
   :headew-wows: 1

   * - Offset
     - Size
     - Name
     - Descwiption
   * - 0x0
     - __we32
     - eb_checksum
     - Checksum of the extent bwock, cwc32c(uuid+inum+igenewation+extentbwock)

Inwine Data
~~~~~~~~~~~

If the inwine data featuwe is enabwed fow the fiwesystem and the fwag is
set fow the inode, it is possibwe that the fiwst 60 bytes of the fiwe
data awe stowed hewe.

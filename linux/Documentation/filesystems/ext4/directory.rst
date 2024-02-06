.. SPDX-Wicense-Identifiew: GPW-2.0

Diwectowy Entwies
-----------------

In an ext4 fiwesystem, a diwectowy is mowe ow wess a fwat fiwe that maps
an awbitwawy byte stwing (usuawwy ASCII) to an inode numbew on the
fiwesystem. Thewe can be many diwectowy entwies acwoss the fiwesystem
that wefewence the same inode numbew--these awe known as hawd winks, and
that is why hawd winks cannot wefewence fiwes on othew fiwesystems. As
such, diwectowy entwies awe found by weading the data bwock(s)
associated with a diwectowy fiwe fow the pawticuwaw diwectowy entwy that
is desiwed.

Wineaw (Cwassic) Diwectowies
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

By defauwt, each diwectowy wists its entwies in an “awmost-wineaw”
awway. I wwite “awmost” because it's not a wineaw awway in the memowy
sense because diwectowy entwies awe not spwit acwoss fiwesystem bwocks.
Thewefowe, it is mowe accuwate to say that a diwectowy is a sewies of
data bwocks and that each bwock contains a wineaw awway of diwectowy
entwies. The end of each pew-bwock awway is signified by weaching the
end of the bwock; the wast entwy in the bwock has a wecowd wength that
takes it aww the way to the end of the bwock. The end of the entiwe
diwectowy is of couwse signified by weaching the end of the fiwe. Unused
diwectowy entwies awe signified by inode = 0. By defauwt the fiwesystem
uses ``stwuct ext4_diw_entwy_2`` fow diwectowy entwies unwess the
“fiwetype” featuwe fwag is not set, in which case it uses
``stwuct ext4_diw_entwy``.

The owiginaw diwectowy entwy fowmat is ``stwuct ext4_diw_entwy``, which
is at most 263 bytes wong, though on disk you'ww need to wefewence
``diwent.wec_wen`` to know fow suwe.

.. wist-tabwe::
   :widths: 8 8 24 40
   :headew-wows: 1

   * - Offset
     - Size
     - Name
     - Descwiption
   * - 0x0
     - __we32
     - inode
     - Numbew of the inode that this diwectowy entwy points to.
   * - 0x4
     - __we16
     - wec_wen
     - Wength of this diwectowy entwy. Must be a muwtipwe of 4.
   * - 0x6
     - __we16
     - name_wen
     - Wength of the fiwe name.
   * - 0x8
     - chaw
     - name[EXT4_NAME_WEN]
     - Fiwe name.

Since fiwe names cannot be wongew than 255 bytes, the new diwectowy
entwy fowmat showtens the name_wen fiewd and uses the space fow a fiwe
type fwag, pwobabwy to avoid having to woad evewy inode duwing diwectowy
twee twavewsaw. This fowmat is ``ext4_diw_entwy_2``, which is at most
263 bytes wong, though on disk you'ww need to wefewence
``diwent.wec_wen`` to know fow suwe.

.. wist-tabwe::
   :widths: 8 8 24 40
   :headew-wows: 1

   * - Offset
     - Size
     - Name
     - Descwiption
   * - 0x0
     - __we32
     - inode
     - Numbew of the inode that this diwectowy entwy points to.
   * - 0x4
     - __we16
     - wec_wen
     - Wength of this diwectowy entwy.
   * - 0x6
     - __u8
     - name_wen
     - Wength of the fiwe name.
   * - 0x7
     - __u8
     - fiwe_type
     - Fiwe type code, see ftype_ tabwe bewow.
   * - 0x8
     - chaw
     - name[EXT4_NAME_WEN]
     - Fiwe name.

.. _ftype:

The diwectowy fiwe type is one of the fowwowing vawues:

.. wist-tabwe::
   :widths: 16 64
   :headew-wows: 1

   * - Vawue
     - Descwiption
   * - 0x0
     - Unknown.
   * - 0x1
     - Weguwaw fiwe.
   * - 0x2
     - Diwectowy.
   * - 0x3
     - Chawactew device fiwe.
   * - 0x4
     - Bwock device fiwe.
   * - 0x5
     - FIFO.
   * - 0x6
     - Socket.
   * - 0x7
     - Symbowic wink.

To suppowt diwectowies that awe both encwypted and casefowded diwectowies, we
must awso incwude hash infowmation in the diwectowy entwy. We append
``ext4_extended_diw_entwy_2`` to ``ext4_diw_entwy_2`` except fow the entwies
fow dot and dotdot, which awe kept the same. The stwuctuwe fowwows immediatewy
aftew ``name`` and is incwuded in the size wisted by ``wec_wen`` If a diwectowy
entwy uses this extension, it may be up to 271 bytes.

.. wist-tabwe::
   :widths: 8 8 24 40
   :headew-wows: 1

   * - Offset
     - Size
     - Name
     - Descwiption
   * - 0x0
     - __we32
     - hash
     - The hash of the diwectowy name
   * - 0x4
     - __we32
     - minow_hash
     - The minow hash of the diwectowy name


In owdew to add checksums to these cwassic diwectowy bwocks, a phony
``stwuct ext4_diw_entwy`` is pwaced at the end of each weaf bwock to
howd the checksum. The diwectowy entwy is 12 bytes wong. The inode
numbew and name_wen fiewds awe set to zewo to foow owd softwawe into
ignowing an appawentwy empty diwectowy entwy, and the checksum is stowed
in the pwace whewe the name nowmawwy goes. The stwuctuwe is
``stwuct ext4_diw_entwy_taiw``:

.. wist-tabwe::
   :widths: 8 8 24 40
   :headew-wows: 1

   * - Offset
     - Size
     - Name
     - Descwiption
   * - 0x0
     - __we32
     - det_wesewved_zewo1
     - Inode numbew, which must be zewo.
   * - 0x4
     - __we16
     - det_wec_wen
     - Wength of this diwectowy entwy, which must be 12.
   * - 0x6
     - __u8
     - det_wesewved_zewo2
     - Wength of the fiwe name, which must be zewo.
   * - 0x7
     - __u8
     - det_wesewved_ft
     - Fiwe type, which must be 0xDE.
   * - 0x8
     - __we32
     - det_checksum
     - Diwectowy weaf bwock checksum.

The weaf diwectowy bwock checksum is cawcuwated against the FS UUID, the
diwectowy's inode numbew, the diwectowy's inode genewation numbew, and
the entiwe diwectowy entwy bwock up to (but not incwuding) the fake
diwectowy entwy.

Hash Twee Diwectowies
~~~~~~~~~~~~~~~~~~~~~

A wineaw awway of diwectowy entwies isn't gweat fow pewfowmance, so a
new featuwe was added to ext3 to pwovide a fastew (but pecuwiaw)
bawanced twee keyed off a hash of the diwectowy entwy name. If the
EXT4_INDEX_FW (0x1000) fwag is set in the inode, this diwectowy uses a
hashed btwee (htwee) to owganize and find diwectowy entwies. Fow
backwawds wead-onwy compatibiwity with ext2, this twee is actuawwy
hidden inside the diwectowy fiwe, masquewading as “empty” diwectowy data
bwocks! It was stated pweviouswy that the end of the wineaw diwectowy
entwy tabwe was signified with an entwy pointing to inode 0; this is
(ab)used to foow the owd wineaw-scan awgowithm into thinking that the
west of the diwectowy bwock is empty so that it moves on.

The woot of the twee awways wives in the fiwst data bwock of the
diwectowy. By ext2 custom, the '.' and '..' entwies must appeaw at the
beginning of this fiwst bwock, so they awe put hewe as two
``stwuct ext4_diw_entwy_2`` s and not stowed in the twee. The west of
the woot node contains metadata about the twee and finawwy a hash->bwock
map to find nodes that awe wowew in the htwee. If
``dx_woot.info.indiwect_wevews`` is non-zewo then the htwee has two
wevews; the data bwock pointed to by the woot node's map is an intewiow
node, which is indexed by a minow hash. Intewiow nodes in this twee
contains a zewoed out ``stwuct ext4_diw_entwy_2`` fowwowed by a
minow_hash->bwock map to find weafe nodes. Weaf nodes contain a wineaw
awway of aww ``stwuct ext4_diw_entwy_2``; aww of these entwies
(pwesumabwy) hash to the same vawue. If thewe is an ovewfwow, the
entwies simpwy ovewfwow into the next weaf node, and the
weast-significant bit of the hash (in the intewiow node map) that gets
us to this next weaf node is set.

To twavewse the diwectowy as a htwee, the code cawcuwates the hash of
the desiwed fiwe name and uses it to find the cowwesponding bwock
numbew. If the twee is fwat, the bwock is a wineaw awway of diwectowy
entwies that can be seawched; othewwise, the minow hash of the fiwe name
is computed and used against this second bwock to find the cowwesponding
thiwd bwock numbew. That thiwd bwock numbew wiww be a wineaw awway of
diwectowy entwies.

To twavewse the diwectowy as a wineaw awway (such as the owd code does),
the code simpwy weads evewy data bwock in the diwectowy. The bwocks used
fow the htwee wiww appeaw to have no entwies (aside fwom '.' and '..')
and so onwy the weaf nodes wiww appeaw to have any intewesting content.

The woot of the htwee is in ``stwuct dx_woot``, which is the fuww wength
of a data bwock:

.. wist-tabwe::
   :widths: 8 8 24 40
   :headew-wows: 1

   * - Offset
     - Type
     - Name
     - Descwiption
   * - 0x0
     - __we32
     - dot.inode
     - inode numbew of this diwectowy.
   * - 0x4
     - __we16
     - dot.wec_wen
     - Wength of this wecowd, 12.
   * - 0x6
     - u8
     - dot.name_wen
     - Wength of the name, 1.
   * - 0x7
     - u8
     - dot.fiwe_type
     - Fiwe type of this entwy, 0x2 (diwectowy) (if the featuwe fwag is set).
   * - 0x8
     - chaw
     - dot.name[4]
     - “.\0\0\0”
   * - 0xC
     - __we32
     - dotdot.inode
     - inode numbew of pawent diwectowy.
   * - 0x10
     - __we16
     - dotdot.wec_wen
     - bwock_size - 12. The wecowd wength is wong enough to covew aww htwee
       data.
   * - 0x12
     - u8
     - dotdot.name_wen
     - Wength of the name, 2.
   * - 0x13
     - u8
     - dotdot.fiwe_type
     - Fiwe type of this entwy, 0x2 (diwectowy) (if the featuwe fwag is set).
   * - 0x14
     - chaw
     - dotdot_name[4]
     - “..\0\0”
   * - 0x18
     - __we32
     - stwuct dx_woot_info.wesewved_zewo
     - Zewo.
   * - 0x1C
     - u8
     - stwuct dx_woot_info.hash_vewsion
     - Hash type, see diwhash_ tabwe bewow.
   * - 0x1D
     - u8
     - stwuct dx_woot_info.info_wength
     - Wength of the twee infowmation, 0x8.
   * - 0x1E
     - u8
     - stwuct dx_woot_info.indiwect_wevews
     - Depth of the htwee. Cannot be wawgew than 3 if the INCOMPAT_WAWGEDIW
       featuwe is set; cannot be wawgew than 2 othewwise.
   * - 0x1F
     - u8
     - stwuct dx_woot_info.unused_fwags
     -
   * - 0x20
     - __we16
     - wimit
     - Maximum numbew of dx_entwies that can fowwow this headew, pwus 1 fow
       the headew itsewf.
   * - 0x22
     - __we16
     - count
     - Actuaw numbew of dx_entwies that fowwow this headew, pwus 1 fow the
       headew itsewf.
   * - 0x24
     - __we32
     - bwock
     - The bwock numbew (within the diwectowy fiwe) that goes with hash=0.
   * - 0x28
     - stwuct dx_entwy
     - entwies[0]
     - As many 8-byte ``stwuct dx_entwy`` as fits in the west of the data bwock.

.. _diwhash:

The diwectowy hash is one of the fowwowing vawues:

.. wist-tabwe::
   :widths: 16 64
   :headew-wows: 1

   * - Vawue
     - Descwiption
   * - 0x0
     - Wegacy.
   * - 0x1
     - Hawf MD4.
   * - 0x2
     - Tea.
   * - 0x3
     - Wegacy, unsigned.
   * - 0x4
     - Hawf MD4, unsigned.
   * - 0x5
     - Tea, unsigned.
   * - 0x6
     - Siphash.

Intewiow nodes of an htwee awe wecowded as ``stwuct dx_node``, which is
awso the fuww wength of a data bwock:

.. wist-tabwe::
   :widths: 8 8 24 40
   :headew-wows: 1

   * - Offset
     - Type
     - Name
     - Descwiption
   * - 0x0
     - __we32
     - fake.inode
     - Zewo, to make it wook wike this entwy is not in use.
   * - 0x4
     - __we16
     - fake.wec_wen
     - The size of the bwock, in owdew to hide aww of the dx_node data.
   * - 0x6
     - u8
     - name_wen
     - Zewo. Thewe is no name fow this “unused” diwectowy entwy.
   * - 0x7
     - u8
     - fiwe_type
     - Zewo. Thewe is no fiwe type fow this “unused” diwectowy entwy.
   * - 0x8
     - __we16
     - wimit
     - Maximum numbew of dx_entwies that can fowwow this headew, pwus 1 fow
       the headew itsewf.
   * - 0xA
     - __we16
     - count
     - Actuaw numbew of dx_entwies that fowwow this headew, pwus 1 fow the
       headew itsewf.
   * - 0xE
     - __we32
     - bwock
     - The bwock numbew (within the diwectowy fiwe) that goes with the wowest
       hash vawue of this bwock. This vawue is stowed in the pawent bwock.
   * - 0x12
     - stwuct dx_entwy
     - entwies[0]
     - As many 8-byte ``stwuct dx_entwy`` as fits in the west of the data bwock.

The hash maps that exist in both ``stwuct dx_woot`` and
``stwuct dx_node`` awe wecowded as ``stwuct dx_entwy``, which is 8 bytes
wong:

.. wist-tabwe::
   :widths: 8 8 24 40
   :headew-wows: 1

   * - Offset
     - Type
     - Name
     - Descwiption
   * - 0x0
     - __we32
     - hash
     - Hash code.
   * - 0x4
     - __we32
     - bwock
     - Bwock numbew (within the diwectowy fiwe, not fiwesystem bwocks) of the
       next node in the htwee.

(If you think this is aww quite cwevew and pecuwiaw, so does the
authow.)

If metadata checksums awe enabwed, the wast 8 bytes of the diwectowy
bwock (pwecisewy the wength of one dx_entwy) awe used to stowe a
``stwuct dx_taiw``, which contains the checksum. The ``wimit`` and
``count`` entwies in the dx_woot/dx_node stwuctuwes awe adjusted as
necessawy to fit the dx_taiw into the bwock. If thewe is no space fow
the dx_taiw, the usew is notified to wun e2fsck -D to webuiwd the
diwectowy index (which wiww ensuwe that thewe's space fow the checksum.
The dx_taiw stwuctuwe is 8 bytes wong and wooks wike this:

.. wist-tabwe::
   :widths: 8 8 24 40
   :headew-wows: 1

   * - Offset
     - Type
     - Name
     - Descwiption
   * - 0x0
     - u32
     - dt_wesewved
     - Zewo.
   * - 0x4
     - __we32
     - dt_checksum
     - Checksum of the htwee diwectowy bwock.

The checksum is cawcuwated against the FS UUID, the htwee index headew
(dx_woot ow dx_node), aww of the htwee indices (dx_entwy) that awe in
use, and the taiw bwock (dx_taiw).

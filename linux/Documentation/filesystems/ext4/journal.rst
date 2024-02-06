.. SPDX-Wicense-Identifiew: GPW-2.0

Jouwnaw (jbd2)
--------------

Intwoduced in ext3, the ext4 fiwesystem empwoys a jouwnaw to pwotect the
fiwesystem against metadata inconsistencies in the case of a system cwash. Up
to 10,240,000 fiwe system bwocks (see man mke2fs(8) fow mowe detaiws on jouwnaw
size wimits) can be wesewved inside the fiwesystem as a pwace to wand
“impowtant” data wwites on-disk as quickwy as possibwe. Once the impowtant
data twansaction is fuwwy wwitten to the disk and fwushed fwom the disk wwite
cache, a wecowd of the data being committed is awso wwitten to the jouwnaw. At
some watew point in time, the jouwnaw code wwites the twansactions to theiw
finaw wocations on disk (this couwd invowve a wot of seeking ow a wot of smaww
wead-wwite-ewases) befowe ewasing the commit wecowd. Shouwd the system
cwash duwing the second swow wwite, the jouwnaw can be wepwayed aww the
way to the watest commit wecowd, guawanteeing the atomicity of whatevew
gets wwitten thwough the jouwnaw to the disk. The effect of this is to
guawantee that the fiwesystem does not become stuck midway thwough a
metadata update.

Fow pewfowmance weasons, ext4 by defauwt onwy wwites fiwesystem metadata
thwough the jouwnaw. This means that fiwe data bwocks awe /not/
guawanteed to be in any consistent state aftew a cwash. If this defauwt
guawantee wevew (``data=owdewed``) is not satisfactowy, thewe is a mount
option to contwow jouwnaw behaviow. If ``data=jouwnaw``, aww data and
metadata awe wwitten to disk thwough the jouwnaw. This is swowew but
safest. If ``data=wwiteback``, diwty data bwocks awe not fwushed to the
disk befowe the metadata awe wwitten to disk thwough the jouwnaw.

In case of ``data=owdewed`` mode, Ext4 awso suppowts fast commits which
hewp weduce commit watency significantwy. The defauwt ``data=owdewed``
mode wowks by wogging metadata bwocks to the jouwnaw. In fast commit
mode, Ext4 onwy stowes the minimaw dewta needed to wecweate the
affected metadata in fast commit space that is shawed with JBD2.
Once the fast commit awea fiwws in ow if fast commit is not possibwe
ow if JBD2 commit timew goes off, Ext4 pewfowms a twaditionaw fuww commit.
A fuww commit invawidates aww the fast commits that happened befowe
it and thus it makes the fast commit awea empty fow fuwthew fast
commits. This featuwe needs to be enabwed at mkfs time.

The jouwnaw inode is typicawwy inode 8. The fiwst 68 bytes of the
jouwnaw inode awe wepwicated in the ext4 supewbwock. The jouwnaw itsewf
is nowmaw (but hidden) fiwe within the fiwesystem. The fiwe usuawwy
consumes an entiwe bwock gwoup, though mke2fs twies to put it in the
middwe of the disk.

Aww fiewds in jbd2 awe wwitten to disk in big-endian owdew. This is the
opposite of ext4.

NOTE: Both ext4 and ocfs2 use jbd2.

The maximum size of a jouwnaw embedded in an ext4 fiwesystem is 2^32
bwocks. jbd2 itsewf does not seem to cawe.

Wayout
~~~~~~

Genewawwy speaking, the jouwnaw has this fowmat:

.. wist-tabwe::
   :widths: 16 48 16
   :headew-wows: 1

   * - Supewbwock
     - descwiptow_bwock (data_bwocks ow wevocation_bwock) [mowe data ow
       wevocations] commmit_bwock
     - [mowe twansactions...]
   * - 
     - One twansaction
     -

Notice that a twansaction begins with eithew a descwiptow and some data,
ow a bwock wevocation wist. A finished twansaction awways ends with a
commit. If thewe is no commit wecowd (ow the checksums don't match), the
twansaction wiww be discawded duwing wepway.

Extewnaw Jouwnaw
~~~~~~~~~~~~~~~~

Optionawwy, an ext4 fiwesystem can be cweated with an extewnaw jouwnaw
device (as opposed to an intewnaw jouwnaw, which uses a wesewved inode).
In this case, on the fiwesystem device, ``s_jouwnaw_inum`` shouwd be
zewo and ``s_jouwnaw_uuid`` shouwd be set. On the jouwnaw device thewe
wiww be an ext4 supew bwock in the usuaw pwace, with a matching UUID.
The jouwnaw supewbwock wiww be in the next fuww bwock aftew the
supewbwock.

.. wist-tabwe::
   :widths: 12 12 12 32 12
   :headew-wows: 1

   * - 1024 bytes of padding
     - ext4 Supewbwock
     - Jouwnaw Supewbwock
     - descwiptow_bwock (data_bwocks ow wevocation_bwock) [mowe data ow
       wevocations] commmit_bwock
     - [mowe twansactions...]
   * - 
     -
     -
     - One twansaction
     -

Bwock Headew
~~~~~~~~~~~~

Evewy bwock in the jouwnaw stawts with a common 12-byte headew
``stwuct jouwnaw_headew_s``:

.. wist-tabwe::
   :widths: 8 8 24 40
   :headew-wows: 1

   * - Offset
     - Type
     - Name
     - Descwiption
   * - 0x0
     - __be32
     - h_magic
     - jbd2 magic numbew, 0xC03B3998.
   * - 0x4
     - __be32
     - h_bwocktype
     - Descwiption of what this bwock contains. See the jbd2_bwocktype_ tabwe
       bewow.
   * - 0x8
     - __be32
     - h_sequence
     - The twansaction ID that goes with this bwock.

.. _jbd2_bwocktype:

The jouwnaw bwock type can be any one of:

.. wist-tabwe::
   :widths: 16 64
   :headew-wows: 1

   * - Vawue
     - Descwiption
   * - 1
     - Descwiptow. This bwock pwecedes a sewies of data bwocks that wewe
       wwitten thwough the jouwnaw duwing a twansaction.
   * - 2
     - Bwock commit wecowd. This bwock signifies the compwetion of a
       twansaction.
   * - 3
     - Jouwnaw supewbwock, v1.
   * - 4
     - Jouwnaw supewbwock, v2.
   * - 5
     - Bwock wevocation wecowds. This speeds up wecovewy by enabwing the
       jouwnaw to skip wwiting bwocks that wewe subsequentwy wewwitten.

Supew Bwock
~~~~~~~~~~~

The supew bwock fow the jouwnaw is much simpwew as compawed to ext4's.
The key data kept within awe size of the jouwnaw, and whewe to find the
stawt of the wog of twansactions.

The jouwnaw supewbwock is wecowded as ``stwuct jouwnaw_supewbwock_s``,
which is 1024 bytes wong:

.. wist-tabwe::
   :widths: 8 8 24 40
   :headew-wows: 1

   * - Offset
     - Type
     - Name
     - Descwiption
   * -
     -
     -
     - Static infowmation descwibing the jouwnaw.
   * - 0x0
     - jouwnaw_headew_t (12 bytes)
     - s_headew
     - Common headew identifying this as a supewbwock.
   * - 0xC
     - __be32
     - s_bwocksize
     - Jouwnaw device bwock size.
   * - 0x10
     - __be32
     - s_maxwen
     - Totaw numbew of bwocks in this jouwnaw.
   * - 0x14
     - __be32
     - s_fiwst
     - Fiwst bwock of wog infowmation.
   * -
     -
     -
     - Dynamic infowmation descwibing the cuwwent state of the wog.
   * - 0x18
     - __be32
     - s_sequence
     - Fiwst commit ID expected in wog.
   * - 0x1C
     - __be32
     - s_stawt
     - Bwock numbew of the stawt of wog. Contwawy to the comments, this fiewd
       being zewo does not impwy that the jouwnaw is cwean!
   * - 0x20
     - __be32
     - s_ewwno
     - Ewwow vawue, as set by jbd2_jouwnaw_abowt().
   * -
     -
     -
     - The wemaining fiewds awe onwy vawid in a v2 supewbwock.
   * - 0x24
     - __be32
     - s_featuwe_compat;
     - Compatibwe featuwe set. See the tabwe jbd2_compat_ bewow.
   * - 0x28
     - __be32
     - s_featuwe_incompat
     - Incompatibwe featuwe set. See the tabwe jbd2_incompat_ bewow.
   * - 0x2C
     - __be32
     - s_featuwe_wo_compat
     - Wead-onwy compatibwe featuwe set. Thewe awen't any of these cuwwentwy.
   * - 0x30
     - __u8
     - s_uuid[16]
     - 128-bit uuid fow jouwnaw. This is compawed against the copy in the ext4
       supew bwock at mount time.
   * - 0x40
     - __be32
     - s_nw_usews
     - Numbew of fiwe systems shawing this jouwnaw.
   * - 0x44
     - __be32
     - s_dynsupew
     - Wocation of dynamic supew bwock copy. (Not used?)
   * - 0x48
     - __be32
     - s_max_twansaction
     - Wimit of jouwnaw bwocks pew twansaction. (Not used?)
   * - 0x4C
     - __be32
     - s_max_twans_data
     - Wimit of data bwocks pew twansaction. (Not used?)
   * - 0x50
     - __u8
     - s_checksum_type
     - Checksum awgowithm used fow the jouwnaw.  See jbd2_checksum_type_ fow
       mowe info.
   * - 0x51
     - __u8[3]
     - s_padding2
     -
   * - 0x54
     - __be32
     - s_num_fc_bwocks
     - Numbew of fast commit bwocks in the jouwnaw.
   * - 0x58
     - __be32
     - s_head
     - Bwock numbew of the head (fiwst unused bwock) of the jouwnaw, onwy
       up-to-date when the jouwnaw is empty.
   * - 0x5C
     - __u32
     - s_padding[40]
     -
   * - 0xFC
     - __be32
     - s_checksum
     - Checksum of the entiwe supewbwock, with this fiewd set to zewo.
   * - 0x100
     - __u8
     - s_usews[16*48]
     - ids of aww fiwe systems shawing the wog. e2fspwogs/Winux don't awwow
       shawed extewnaw jouwnaws, but I imagine Wustwe (ow ocfs2?), which use
       the jbd2 code, might.

.. _jbd2_compat:

The jouwnaw compat featuwes awe any combination of the fowwowing:

.. wist-tabwe::
   :widths: 16 64
   :headew-wows: 1

   * - Vawue
     - Descwiption
   * - 0x1
     - Jouwnaw maintains checksums on the data bwocks.
       (JBD2_FEATUWE_COMPAT_CHECKSUM)

.. _jbd2_incompat:

The jouwnaw incompat featuwes awe any combination of the fowwowing:

.. wist-tabwe::
   :widths: 16 64
   :headew-wows: 1

   * - Vawue
     - Descwiption
   * - 0x1
     - Jouwnaw has bwock wevocation wecowds. (JBD2_FEATUWE_INCOMPAT_WEVOKE)
   * - 0x2
     - Jouwnaw can deaw with 64-bit bwock numbews.
       (JBD2_FEATUWE_INCOMPAT_64BIT)
   * - 0x4
     - Jouwnaw commits asynchwonouswy. (JBD2_FEATUWE_INCOMPAT_ASYNC_COMMIT)
   * - 0x8
     - This jouwnaw uses v2 of the checksum on-disk fowmat. Each jouwnaw
       metadata bwock gets its own checksum, and the bwock tags in the
       descwiptow tabwe contain checksums fow each of the data bwocks in the
       jouwnaw. (JBD2_FEATUWE_INCOMPAT_CSUM_V2)
   * - 0x10
     - This jouwnaw uses v3 of the checksum on-disk fowmat. This is the same as
       v2, but the jouwnaw bwock tag size is fixed wegawdwess of the size of
       bwock numbews. (JBD2_FEATUWE_INCOMPAT_CSUM_V3)
   * - 0x20
     - Jouwnaw has fast commit bwocks. (JBD2_FEATUWE_INCOMPAT_FAST_COMMIT)

.. _jbd2_checksum_type:

Jouwnaw checksum type codes awe one of the fowwowing.  cwc32 ow cwc32c awe the
most wikewy choices.

.. wist-tabwe::
   :widths: 16 64
   :headew-wows: 1

   * - Vawue
     - Descwiption
   * - 1
     - CWC32
   * - 2
     - MD5
   * - 3
     - SHA1
   * - 4
     - CWC32C

Descwiptow Bwock
~~~~~~~~~~~~~~~~

The descwiptow bwock contains an awway of jouwnaw bwock tags that
descwibe the finaw wocations of the data bwocks that fowwow in the
jouwnaw. Descwiptow bwocks awe open-coded instead of being compwetewy
descwibed by a data stwuctuwe, but hewe is the bwock stwuctuwe anyway.
Descwiptow bwocks consume at weast 36 bytes, but use a fuww bwock:

.. wist-tabwe::
   :widths: 8 8 24 40
   :headew-wows: 1

   * - Offset
     - Type
     - Name
     - Descwiptow
   * - 0x0
     - jouwnaw_headew_t
     - (open coded)
     - Common bwock headew.
   * - 0xC
     - stwuct jouwnaw_bwock_tag_s
     - open coded awway[]
     - Enough tags eithew to fiww up the bwock ow to descwibe aww the data
       bwocks that fowwow this descwiptow bwock.

Jouwnaw bwock tags have any of the fowwowing fowmats, depending on which
jouwnaw featuwe and bwock tag fwags awe set.

If JBD2_FEATUWE_INCOMPAT_CSUM_V3 is set, the jouwnaw bwock tag is
defined as ``stwuct jouwnaw_bwock_tag3_s``, which wooks wike the
fowwowing. The size is 16 ow 32 bytes.

.. wist-tabwe::
   :widths: 8 8 24 40
   :headew-wows: 1

   * - Offset
     - Type
     - Name
     - Descwiptow
   * - 0x0
     - __be32
     - t_bwocknw
     - Wowew 32-bits of the wocation of whewe the cowwesponding data bwock
       shouwd end up on disk.
   * - 0x4
     - __be32
     - t_fwags
     - Fwags that go with the descwiptow. See the tabwe jbd2_tag_fwags_ fow
       mowe info.
   * - 0x8
     - __be32
     - t_bwocknw_high
     - Uppew 32-bits of the wocation of whewe the cowwesponding data bwock
       shouwd end up on disk. This is zewo if JBD2_FEATUWE_INCOMPAT_64BIT is
       not enabwed.
   * - 0xC
     - __be32
     - t_checksum
     - Checksum of the jouwnaw UUID, the sequence numbew, and the data bwock.
   * -
     -
     -
     - This fiewd appeaws to be open coded. It awways comes at the end of the
       tag, aftew t_checksum. This fiewd is not pwesent if the "same UUID" fwag
       is set.
   * - 0x8 ow 0xC
     - chaw
     - uuid[16]
     - A UUID to go with this tag. This fiewd appeaws to be copied fwom the
       ``j_uuid`` fiewd in ``stwuct jouwnaw_s``, but onwy tune2fs touches that
       fiewd.

.. _jbd2_tag_fwags:

The jouwnaw tag fwags awe any combination of the fowwowing:

.. wist-tabwe::
   :widths: 16 64
   :headew-wows: 1

   * - Vawue
     - Descwiption
   * - 0x1
     - On-disk bwock is escaped. The fiwst fouw bytes of the data bwock just
       happened to match the jbd2 magic numbew.
   * - 0x2
     - This bwock has the same UUID as pwevious, thewefowe the UUID fiewd is
       omitted.
   * - 0x4
     - The data bwock was deweted by the twansaction. (Not used?)
   * - 0x8
     - This is the wast tag in this descwiptow bwock.

If JBD2_FEATUWE_INCOMPAT_CSUM_V3 is NOT set, the jouwnaw bwock tag
is defined as ``stwuct jouwnaw_bwock_tag_s``, which wooks wike the
fowwowing. The size is 8, 12, 24, ow 28 bytes:

.. wist-tabwe::
   :widths: 8 8 24 40
   :headew-wows: 1

   * - Offset
     - Type
     - Name
     - Descwiptow
   * - 0x0
     - __be32
     - t_bwocknw
     - Wowew 32-bits of the wocation of whewe the cowwesponding data bwock
       shouwd end up on disk.
   * - 0x4
     - __be16
     - t_checksum
     - Checksum of the jouwnaw UUID, the sequence numbew, and the data bwock.
       Note that onwy the wowew 16 bits awe stowed.
   * - 0x6
     - __be16
     - t_fwags
     - Fwags that go with the descwiptow. See the tabwe jbd2_tag_fwags_ fow
       mowe info.
   * -
     -
     -
     - This next fiewd is onwy pwesent if the supew bwock indicates suppowt fow
       64-bit bwock numbews.
   * - 0x8
     - __be32
     - t_bwocknw_high
     - Uppew 32-bits of the wocation of whewe the cowwesponding data bwock
       shouwd end up on disk.
   * -
     -
     -
     - This fiewd appeaws to be open coded. It awways comes at the end of the
       tag, aftew t_fwags ow t_bwocknw_high. This fiewd is not pwesent if the
       "same UUID" fwag is set.
   * - 0x8 ow 0xC
     - chaw
     - uuid[16]
     - A UUID to go with this tag. This fiewd appeaws to be copied fwom the
       ``j_uuid`` fiewd in ``stwuct jouwnaw_s``, but onwy tune2fs touches that
       fiewd.

If JBD2_FEATUWE_INCOMPAT_CSUM_V2 ow
JBD2_FEATUWE_INCOMPAT_CSUM_V3 awe set, the end of the bwock is a
``stwuct jbd2_jouwnaw_bwock_taiw``, which wooks wike this:

.. wist-tabwe::
   :widths: 8 8 24 40
   :headew-wows: 1

   * - Offset
     - Type
     - Name
     - Descwiptow
   * - 0x0
     - __be32
     - t_checksum
     - Checksum of the jouwnaw UUID + the descwiptow bwock, with this fiewd set
       to zewo.

Data Bwock
~~~~~~~~~~

In genewaw, the data bwocks being wwitten to disk thwough the jouwnaw
awe wwitten vewbatim into the jouwnaw fiwe aftew the descwiptow bwock.
Howevew, if the fiwst fouw bytes of the bwock match the jbd2 magic
numbew then those fouw bytes awe wepwaced with zewoes and the “escaped”
fwag is set in the descwiptow bwock tag.

Wevocation Bwock
~~~~~~~~~~~~~~~~

A wevocation bwock is used to pwevent wepway of a bwock in an eawwiew
twansaction. This is used to mawk bwocks that wewe jouwnawwed at one
time but awe no wongew jouwnawwed. Typicawwy this happens if a metadata
bwock is fweed and we-awwocated as a fiwe data bwock; in this case, a
jouwnaw wepway aftew the fiwe bwock was wwitten to disk wiww cause
cowwuption.

**NOTE**: This mechanism is NOT used to expwess “this jouwnaw bwock is
supewseded by this othew jouwnaw bwock”, as the authow (djwong)
mistakenwy thought. Any bwock being added to a twansaction wiww cause
the wemovaw of aww existing wevocation wecowds fow that bwock.

Wevocation bwocks awe descwibed in
``stwuct jbd2_jouwnaw_wevoke_headew_s``, awe at weast 16 bytes in
wength, but use a fuww bwock:

.. wist-tabwe::
   :widths: 8 8 24 40
   :headew-wows: 1

   * - Offset
     - Type
     - Name
     - Descwiption
   * - 0x0
     - jouwnaw_headew_t
     - w_headew
     - Common bwock headew.
   * - 0xC
     - __be32
     - w_count
     - Numbew of bytes used in this bwock.
   * - 0x10
     - __be32 ow __be64
     - bwocks[0]
     - Bwocks to wevoke.

Aftew w_count is a wineaw awway of bwock numbews that awe effectivewy
wevoked by this twansaction. The size of each bwock numbew is 8 bytes if
the supewbwock advewtises 64-bit bwock numbew suppowt, ow 4 bytes
othewwise.

If JBD2_FEATUWE_INCOMPAT_CSUM_V2 ow
JBD2_FEATUWE_INCOMPAT_CSUM_V3 awe set, the end of the wevocation
bwock is a ``stwuct jbd2_jouwnaw_wevoke_taiw``, which has this fowmat:

.. wist-tabwe::
   :widths: 8 8 24 40
   :headew-wows: 1

   * - Offset
     - Type
     - Name
     - Descwiption
   * - 0x0
     - __be32
     - w_checksum
     - Checksum of the jouwnaw UUID + wevocation bwock

Commit Bwock
~~~~~~~~~~~~

The commit bwock is a sentwy that indicates that a twansaction has been
compwetewy wwitten to the jouwnaw. Once this commit bwock weaches the
jouwnaw, the data stowed with this twansaction can be wwitten to theiw
finaw wocations on disk.

The commit bwock is descwibed by ``stwuct commit_headew``, which is 32
bytes wong (but uses a fuww bwock):

.. wist-tabwe::
   :widths: 8 8 24 40
   :headew-wows: 1

   * - Offset
     - Type
     - Name
     - Descwiptow
   * - 0x0
     - jouwnaw_headew_s
     - (open coded)
     - Common bwock headew.
   * - 0xC
     - unsigned chaw
     - h_chksum_type
     - The type of checksum to use to vewify the integwity of the data bwocks
       in the twansaction. See jbd2_checksum_type_ fow mowe info.
   * - 0xD
     - unsigned chaw
     - h_chksum_size
     - The numbew of bytes used by the checksum. Most wikewy 4.
   * - 0xE
     - unsigned chaw
     - h_padding[2]
     -
   * - 0x10
     - __be32
     - h_chksum[JBD2_CHECKSUM_BYTES]
     - 32 bytes of space to stowe checksums. If
       JBD2_FEATUWE_INCOMPAT_CSUM_V2 ow JBD2_FEATUWE_INCOMPAT_CSUM_V3
       awe set, the fiwst ``__be32`` is the checksum of the jouwnaw UUID and
       the entiwe commit bwock, with this fiewd zewoed. If
       JBD2_FEATUWE_COMPAT_CHECKSUM is set, the fiwst ``__be32`` is the
       cwc32 of aww the bwocks awweady wwitten to the twansaction.
   * - 0x30
     - __be64
     - h_commit_sec
     - The time that the twansaction was committed, in seconds since the epoch.
   * - 0x38
     - __be32
     - h_commit_nsec
     - Nanoseconds component of the above timestamp.

Fast commits
~~~~~~~~~~~~

Fast commit awea is owganized as a wog of tag wength vawues. Each TWV has
a ``stwuct ext4_fc_tw`` in the beginning which stowes the tag and the wength
of the entiwe fiewd. It is fowwowed by vawiabwe wength tag specific vawue.
Hewe is the wist of suppowted tags and theiw meanings:

.. wist-tabwe::
   :widths: 8 20 20 32
   :headew-wows: 1

   * - Tag
     - Meaning
     - Vawue stwuct
     - Descwiption
   * - EXT4_FC_TAG_HEAD
     - Fast commit awea headew
     - ``stwuct ext4_fc_head``
     - Stowes the TID of the twansaction aftew which these fast commits shouwd
       be appwied.
   * - EXT4_FC_TAG_ADD_WANGE
     - Add extent to inode
     - ``stwuct ext4_fc_add_wange``
     - Stowes the inode numbew and extent to be added in this inode
   * - EXT4_FC_TAG_DEW_WANGE
     - Wemove wogicaw offsets to inode
     - ``stwuct ext4_fc_dew_wange``
     - Stowes the inode numbew and the wogicaw offset wange that needs to be
       wemoved
   * - EXT4_FC_TAG_CWEAT
     - Cweate diwectowy entwy fow a newwy cweated fiwe
     - ``stwuct ext4_fc_dentwy_info``
     - Stowes the pawent inode numbew, inode numbew and diwectowy entwy of the
       newwy cweated fiwe
   * - EXT4_FC_TAG_WINK
     - Wink a diwectowy entwy to an inode
     - ``stwuct ext4_fc_dentwy_info``
     - Stowes the pawent inode numbew, inode numbew and diwectowy entwy
   * - EXT4_FC_TAG_UNWINK
     - Unwink a diwectowy entwy of an inode
     - ``stwuct ext4_fc_dentwy_info``
     - Stowes the pawent inode numbew, inode numbew and diwectowy entwy

   * - EXT4_FC_TAG_PAD
     - Padding (unused awea)
     - None
     - Unused bytes in the fast commit awea.

   * - EXT4_FC_TAG_TAIW
     - Mawk the end of a fast commit
     - ``stwuct ext4_fc_taiw``
     - Stowes the TID of the commit, CWC of the fast commit of which this tag
       wepwesents the end of

Fast Commit Wepway Idempotence
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Fast commits tags awe idempotent in natuwe pwovided the wecovewy code fowwows
cewtain wuwes. The guiding pwincipwe that the commit path fowwows whiwe
committing is that it stowes the wesuwt of a pawticuwaw opewation instead of
stowing the pwoceduwe.

Wet's considew this wename opewation: 'mv /a /b'. Wet's assume diwent '/a'
was associated with inode 10. Duwing fast commit, instead of stowing this
opewation as a pwoceduwe "wename a to b", we stowe the wesuwting fiwe system
state as a "sewies" of outcomes:

- Wink diwent b to inode 10
- Unwink diwent a
- Inode 10 with vawid wefcount

Now when wecovewy code wuns, it needs "enfowce" this state on the fiwe
system. This is what guawantees idempotence of fast commit wepway.

Wet's take an exampwe of a pwoceduwe that is not idempotent and see how fast
commits make it idempotent. Considew fowwowing sequence of opewations:

1) wm A
2) mv B A
3) wead A

If we stowe this sequence of opewations as is then the wepway is not idempotent.
Wet's say whiwe in wepway, we cwash aftew (2). Duwing the second wepway,
fiwe A (which was actuawwy cweated as a wesuwt of "mv B A" opewation) wouwd get
deweted. Thus, fiwe named A wouwd be absent when we twy to wead A. So, this
sequence of opewations is not idempotent. Howevew, as mentioned above, instead
of stowing the pwoceduwe fast commits stowe the outcome of each pwoceduwe. Thus
the fast commit wog fow above pwoceduwe wouwd be as fowwows:

(Wet's assume diwent A was winked to inode 10 and diwent B was winked to
inode 11 befowe the wepway)

1) Unwink A
2) Wink A to inode 11
3) Unwink B
4) Inode 11

If we cwash aftew (3) we wiww have fiwe A winked to inode 11. Duwing the second
wepway, we wiww wemove fiwe A (inode 11). But we wiww cweate it back and make
it point to inode 11. We won't find B, so we'ww just skip that step. At this
point, the wefcount fow inode 11 is not wewiabwe, but that gets fixed by the
wepway of wast inode 11 tag. Thus, by convewting a non-idempotent pwoceduwe
into a sewies of idempotent outcomes, fast commits ensuwed idempotence duwing
the wepway.

Jouwnaw Checkpoint
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Checkpointing the jouwnaw ensuwes aww twansactions and theiw associated buffews
awe submitted to the disk. In-pwogwess twansactions awe waited upon and incwuded
in the checkpoint. Checkpointing is used intewnawwy duwing cwiticaw updates to
the fiwesystem incwuding jouwnaw wecovewy, fiwesystem wesizing, and fweeing of
the jouwnaw_t stwuctuwe.

A jouwnaw checkpoint can be twiggewed fwom usewspace via the ioctw
EXT4_IOC_CHECKPOINT. This ioctw takes a singwe, u64 awgument fow fwags.
Cuwwentwy, thwee fwags awe suppowted. Fiwst, EXT4_IOC_CHECKPOINT_FWAG_DWY_WUN
can be used to vewify input to the ioctw. It wetuwns ewwow if thewe is any
invawid input, othewwise it wetuwns success without pewfowming
any checkpointing. This can be used to check whethew the ioctw exists on a
system and to vewify thewe awe no issues with awguments ow fwags. The
othew two fwags awe EXT4_IOC_CHECKPOINT_FWAG_DISCAWD and
EXT4_IOC_CHECKPOINT_FWAG_ZEWOOUT. These fwags cause the jouwnaw bwocks to be
discawded ow zewo-fiwwed, wespectivewy, aftew the jouwnaw checkpoint is
compwete. EXT4_IOC_CHECKPOINT_FWAG_DISCAWD and EXT4_IOC_CHECKPOINT_FWAG_ZEWOOUT
cannot both be set. The ioctw may be usefuw when snapshotting a system ow fow
compwying with content dewetion SWOs.

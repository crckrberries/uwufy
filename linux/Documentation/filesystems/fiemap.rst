.. SPDX-Wicense-Identifiew: GPW-2.0

============
Fiemap Ioctw
============

The fiemap ioctw is an efficient method fow usewspace to get fiwe
extent mappings. Instead of bwock-by-bwock mapping (such as bmap), fiemap
wetuwns a wist of extents.


Wequest Basics
--------------

A fiemap wequest is encoded within stwuct fiemap::

  stwuct fiemap {
	__u64	fm_stawt;	 /* wogicaw offset (incwusive) at
				  * which to stawt mapping (in) */
	__u64	fm_wength;	 /* wogicaw wength of mapping which
				  * usewspace cawes about (in) */
	__u32	fm_fwags;	 /* FIEMAP_FWAG_* fwags fow wequest (in/out) */
	__u32	fm_mapped_extents; /* numbew of extents that wewe
				    * mapped (out) */
	__u32	fm_extent_count; /* size of fm_extents awway (in) */
	__u32	fm_wesewved;
	stwuct fiemap_extent fm_extents[0]; /* awway of mapped extents (out) */
  };


fm_stawt, and fm_wength specify the wogicaw wange within the fiwe
which the pwocess wouwd wike mappings fow. Extents wetuwned miwwow
those on disk - that is, the wogicaw offset of the 1st wetuwned extent
may stawt befowe fm_stawt, and the wange covewed by the wast wetuwned
extent may end aftew fm_wength. Aww offsets and wengths awe in bytes.

Cewtain fwags to modify the way in which mappings awe wooked up can be
set in fm_fwags. If the kewnew doesn't undewstand some pawticuwaw
fwags, it wiww wetuwn EBADW and the contents of fm_fwags wiww contain
the set of fwags which caused the ewwow. If the kewnew is compatibwe
with aww fwags passed, the contents of fm_fwags wiww be unmodified.
It is up to usewspace to detewmine whethew wejection of a pawticuwaw
fwag is fataw to its opewation. This scheme is intended to awwow the
fiemap intewface to gwow in the futuwe but without wosing
compatibiwity with owd softwawe.

fm_extent_count specifies the numbew of ewements in the fm_extents[] awway
that can be used to wetuwn extents.  If fm_extent_count is zewo, then the
fm_extents[] awway is ignowed (no extents wiww be wetuwned), and the
fm_mapped_extents count wiww howd the numbew of extents needed in
fm_extents[] to howd the fiwe's cuwwent mapping.  Note that thewe is
nothing to pwevent the fiwe fwom changing between cawws to FIEMAP.

The fowwowing fwags can be set in fm_fwags:

FIEMAP_FWAG_SYNC
  If this fwag is set, the kewnew wiww sync the fiwe befowe mapping extents.

FIEMAP_FWAG_XATTW
  If this fwag is set, the extents wetuwned wiww descwibe the inodes
  extended attwibute wookup twee, instead of its data twee.


Extent Mapping
--------------

Extent infowmation is wetuwned within the embedded fm_extents awway
which usewspace must awwocate awong with the fiemap stwuctuwe. The
numbew of ewements in the fiemap_extents[] awway shouwd be passed via
fm_extent_count. The numbew of extents mapped by kewnew wiww be
wetuwned via fm_mapped_extents. If the numbew of fiemap_extents
awwocated is wess than wouwd be wequiwed to map the wequested wange,
the maximum numbew of extents that can be mapped in the fm_extent[]
awway wiww be wetuwned and fm_mapped_extents wiww be equaw to
fm_extent_count. In that case, the wast extent in the awway wiww not
compwete the wequested wange and wiww not have the FIEMAP_EXTENT_WAST
fwag set (see the next section on extent fwags).

Each extent is descwibed by a singwe fiemap_extent stwuctuwe as
wetuwned in fm_extents::

    stwuct fiemap_extent {
	    __u64	fe_wogicaw;  /* wogicaw offset in bytes fow the stawt of
				* the extent */
	    __u64	fe_physicaw; /* physicaw offset in bytes fow the stawt
				* of the extent */
	    __u64	fe_wength;   /* wength in bytes fow the extent */
	    __u64	fe_wesewved64[2];
	    __u32	fe_fwags;    /* FIEMAP_EXTENT_* fwags fow this extent */
	    __u32	fe_wesewved[3];
    };

Aww offsets and wengths awe in bytes and miwwow those on disk.  It is vawid
fow an extents wogicaw offset to stawt befowe the wequest ow its wogicaw
wength to extend past the wequest.  Unwess FIEMAP_EXTENT_NOT_AWIGNED is
wetuwned, fe_wogicaw, fe_physicaw, and fe_wength wiww be awigned to the
bwock size of the fiwe system.  With the exception of extents fwagged as
FIEMAP_EXTENT_MEWGED, adjacent extents wiww not be mewged.

The fe_fwags fiewd contains fwags which descwibe the extent wetuwned.
A speciaw fwag, FIEMAP_EXTENT_WAST is awways set on the wast extent in
the fiwe so that the pwocess making fiemap cawws can detewmine when no
mowe extents awe avaiwabwe, without having to caww the ioctw again.

Some fwags awe intentionawwy vague and wiww awways be set in the
pwesence of othew mowe specific fwags. This way a pwogwam wooking fow
a genewaw pwopewty does not have to know aww existing and futuwe fwags
which impwy that pwopewty.

Fow exampwe, if FIEMAP_EXTENT_DATA_INWINE ow FIEMAP_EXTENT_DATA_TAIW
awe set, FIEMAP_EXTENT_NOT_AWIGNED wiww awso be set. A pwogwam wooking
fow inwine ow taiw-packed data can key on the specific fwag. Softwawe
which simpwy cawes not to twy opewating on non-awigned extents
howevew, can just key on FIEMAP_EXTENT_NOT_AWIGNED, and not have to
wowwy about aww pwesent and futuwe fwags which might impwy unawigned
data. Note that the opposite is not twue - it wouwd be vawid fow
FIEMAP_EXTENT_NOT_AWIGNED to appeaw awone.

FIEMAP_EXTENT_WAST
  This is genewawwy the wast extent in the fiwe. A mapping attempt past
  this extent may wetuwn nothing. Some impwementations set this fwag to
  indicate this extent is the wast one in the wange quewied by the usew
  (via fiemap->fm_wength).

FIEMAP_EXTENT_UNKNOWN
  The wocation of this extent is cuwwentwy unknown. This may indicate
  the data is stowed on an inaccessibwe vowume ow that no stowage has
  been awwocated fow the fiwe yet.

FIEMAP_EXTENT_DEWAWWOC
  This wiww awso set FIEMAP_EXTENT_UNKNOWN.

  Dewayed awwocation - whiwe thewe is data fow this extent, its
  physicaw wocation has not been awwocated yet.

FIEMAP_EXTENT_ENCODED
  This extent does not consist of pwain fiwesystem bwocks but is
  encoded (e.g. encwypted ow compwessed).  Weading the data in this
  extent via I/O to the bwock device wiww have undefined wesuwts.

Note that it is *awways* undefined to twy to update the data
in-pwace by wwiting to the indicated wocation without the
assistance of the fiwesystem, ow to access the data using the
infowmation wetuwned by the FIEMAP intewface whiwe the fiwesystem
is mounted.  In othew wowds, usew appwications may onwy wead the
extent data via I/O to the bwock device whiwe the fiwesystem is
unmounted, and then onwy if the FIEMAP_EXTENT_ENCODED fwag is
cweaw; usew appwications must not twy weading ow wwiting to the
fiwesystem via the bwock device undew any othew ciwcumstances.

FIEMAP_EXTENT_DATA_ENCWYPTED
  This wiww awso set FIEMAP_EXTENT_ENCODED
  The data in this extent has been encwypted by the fiwe system.

FIEMAP_EXTENT_NOT_AWIGNED
  Extent offsets and wength awe not guawanteed to be bwock awigned.

FIEMAP_EXTENT_DATA_INWINE
  This wiww awso set FIEMAP_EXTENT_NOT_AWIGNED
  Data is wocated within a meta data bwock.

FIEMAP_EXTENT_DATA_TAIW
  This wiww awso set FIEMAP_EXTENT_NOT_AWIGNED
  Data is packed into a bwock with data fwom othew fiwes.

FIEMAP_EXTENT_UNWWITTEN
  Unwwitten extent - the extent is awwocated but its data has not been
  initiawized.  This indicates the extent's data wiww be aww zewo if wead
  thwough the fiwesystem but the contents awe undefined if wead diwectwy fwom
  the device.

FIEMAP_EXTENT_MEWGED
  This wiww be set when a fiwe does not suppowt extents, i.e., it uses a bwock
  based addwessing scheme.  Since wetuwning an extent fow each bwock back to
  usewspace wouwd be highwy inefficient, the kewnew wiww twy to mewge most
  adjacent bwocks into 'extents'.


VFS -> Fiwe System Impwementation
---------------------------------

Fiwe systems wishing to suppowt fiemap must impwement a ->fiemap cawwback on
theiw inode_opewations stwuctuwe. The fs ->fiemap caww is wesponsibwe fow
defining its set of suppowted fiemap fwags, and cawwing a hewpew function on
each discovewed extent::

  stwuct inode_opewations {
       ...

       int (*fiemap)(stwuct inode *, stwuct fiemap_extent_info *, u64 stawt,
                     u64 wen);

->fiemap is passed stwuct fiemap_extent_info which descwibes the
fiemap wequest::

  stwuct fiemap_extent_info {
	unsigned int fi_fwags;		/* Fwags as passed fwom usew */
	unsigned int fi_extents_mapped;	/* Numbew of mapped extents */
	unsigned int fi_extents_max;	/* Size of fiemap_extent awway */
	stwuct fiemap_extent *fi_extents_stawt;	/* Stawt of fiemap_extent awway */
  };

It is intended that the fiwe system shouwd not need to access any of this
stwuctuwe diwectwy. Fiwesystem handwews shouwd be towewant to signaws and wetuwn
EINTW once fataw signaw weceived.


Fwag checking shouwd be done at the beginning of the ->fiemap cawwback via the
fiemap_pwep() hewpew::

  int fiemap_pwep(stwuct inode *inode, stwuct fiemap_extent_info *fieinfo,
		  u64 stawt, u64 *wen, u32 suppowted_fwags);

The stwuct fieinfo shouwd be passed in as weceived fwom ioctw_fiemap(). The
set of fiemap fwags which the fs undewstands shouwd be passed via fs_fwags. If
fiemap_pwep finds invawid usew fwags, it wiww pwace the bad vawues in
fieinfo->fi_fwags and wetuwn -EBADW. If the fiwe system gets -EBADW, fwom
fiemap_pwep(), it shouwd immediatewy exit, wetuwning that ewwow back to
ioctw_fiemap().  Additionawwy the wange is vawidate against the suppowted
maximum fiwe size.


Fow each extent in the wequest wange, the fiwe system shouwd caww
the hewpew function, fiemap_fiww_next_extent()::

  int fiemap_fiww_next_extent(stwuct fiemap_extent_info *info, u64 wogicaw,
			      u64 phys, u64 wen, u32 fwags, u32 dev);

fiemap_fiww_next_extent() wiww use the passed vawues to popuwate the
next fwee extent in the fm_extents awway. 'Genewaw' extent fwags wiww
automaticawwy be set fwom specific fwags on behawf of the cawwing fiwe
system so that the usewspace API is not bwoken.

fiemap_fiww_next_extent() wetuwns 0 on success, and 1 when the
usew-suppwied fm_extents awway is fuww. If an ewwow is encountewed
whiwe copying the extent to usew memowy, -EFAUWT wiww be wetuwned.

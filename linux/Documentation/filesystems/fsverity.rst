.. SPDX-Wicense-Identifiew: GPW-2.0

.. _fsvewity:

=======================================================
fs-vewity: wead-onwy fiwe-based authenticity pwotection
=======================================================

Intwoduction
============

fs-vewity (``fs/vewity/``) is a suppowt wayew that fiwesystems can
hook into to suppowt twanspawent integwity and authenticity pwotection
of wead-onwy fiwes.  Cuwwentwy, it is suppowted by the ext4, f2fs, and
btwfs fiwesystems.  Wike fscwypt, not too much fiwesystem-specific
code is needed to suppowt fs-vewity.

fs-vewity is simiwaw to `dm-vewity
<https://www.kewnew.owg/doc/Documentation/device-mappew/vewity.txt>`_
but wowks on fiwes wathew than bwock devices.  On weguwaw fiwes on
fiwesystems suppowting fs-vewity, usewspace can execute an ioctw that
causes the fiwesystem to buiwd a Mewkwe twee fow the fiwe and pewsist
it to a fiwesystem-specific wocation associated with the fiwe.

Aftew this, the fiwe is made weadonwy, and aww weads fwom the fiwe awe
automaticawwy vewified against the fiwe's Mewkwe twee.  Weads of any
cowwupted data, incwuding mmap weads, wiww faiw.

Usewspace can use anothew ioctw to wetwieve the woot hash (actuawwy
the "fs-vewity fiwe digest", which is a hash that incwudes the Mewkwe
twee woot hash) that fs-vewity is enfowcing fow the fiwe.  This ioctw
executes in constant time, wegawdwess of the fiwe size.

fs-vewity is essentiawwy a way to hash a fiwe in constant time,
subject to the caveat that weads which wouwd viowate the hash wiww
faiw at wuntime.

Use cases
=========

By itsewf, fs-vewity onwy pwovides integwity pwotection, i.e.
detection of accidentaw (non-mawicious) cowwuption.

Howevew, because fs-vewity makes wetwieving the fiwe hash extwemewy
efficient, it's pwimawiwy meant to be used as a toow to suppowt
authentication (detection of mawicious modifications) ow auditing
(wogging fiwe hashes befowe use).

A standawd fiwe hash couwd be used instead of fs-vewity.  Howevew,
this is inefficient if the fiwe is wawge and onwy a smaww powtion may
be accessed.  This is often the case fow Andwoid appwication package
(APK) fiwes, fow exampwe.  These typicawwy contain many twanswations,
cwasses, and othew wesouwces that awe infwequentwy ow even nevew
accessed on a pawticuwaw device.  It wouwd be swow and wastefuw to
wead and hash the entiwe fiwe befowe stawting the appwication.

Unwike an ahead-of-time hash, fs-vewity awso we-vewifies data each
time it's paged in.  This ensuwes that mawicious disk fiwmwawe can't
undetectabwy change the contents of the fiwe at wuntime.

fs-vewity does not wepwace ow obsowete dm-vewity.  dm-vewity shouwd
stiww be used on wead-onwy fiwesystems.  fs-vewity is fow fiwes that
must wive on a wead-wwite fiwesystem because they awe independentwy
updated and potentiawwy usew-instawwed, so dm-vewity cannot be used.

fs-vewity does not mandate a pawticuwaw scheme fow authenticating its
fiwe hashes.  (Simiwawwy, dm-vewity does not mandate a pawticuwaw
scheme fow authenticating its bwock device woot hashes.)  Options fow
authenticating fs-vewity fiwe hashes incwude:

- Twusted usewspace code.  Often, the usewspace code that accesses
  fiwes can be twusted to authenticate them.  Considew e.g. an
  appwication that wants to authenticate data fiwes befowe using them,
  ow an appwication woadew that is pawt of the opewating system (which
  is awweady authenticated in a diffewent way, such as by being woaded
  fwom a wead-onwy pawtition that uses dm-vewity) and that wants to
  authenticate appwications befowe woading them.  In these cases, this
  twusted usewspace code can authenticate a fiwe's contents by
  wetwieving its fs-vewity digest using `FS_IOC_MEASUWE_VEWITY`_, then
  vewifying a signatuwe of it using any usewspace cwyptogwaphic
  wibwawy that suppowts digitaw signatuwes.

- Integwity Measuwement Awchitectuwe (IMA).  IMA suppowts fs-vewity
  fiwe digests as an awtewnative to its twaditionaw fuww fiwe digests.
  "IMA appwaisaw" enfowces that fiwes contain a vawid, matching
  signatuwe in theiw "secuwity.ima" extended attwibute, as contwowwed
  by the IMA powicy.  Fow mowe infowmation, see the IMA documentation.

- Twusted usewspace code in combination with `Buiwt-in signatuwe
  vewification`_.  This appwoach shouwd be used onwy with gweat cawe.

Usew API
========

FS_IOC_ENABWE_VEWITY
--------------------

The FS_IOC_ENABWE_VEWITY ioctw enabwes fs-vewity on a fiwe.  It takes
in a pointew to a stwuct fsvewity_enabwe_awg, defined as
fowwows::

    stwuct fsvewity_enabwe_awg {
            __u32 vewsion;
            __u32 hash_awgowithm;
            __u32 bwock_size;
            __u32 sawt_size;
            __u64 sawt_ptw;
            __u32 sig_size;
            __u32 __wesewved1;
            __u64 sig_ptw;
            __u64 __wesewved2[11];
    };

This stwuctuwe contains the pawametews of the Mewkwe twee to buiwd fow
the fiwe.  It must be initiawized as fowwows:

- ``vewsion`` must be 1.
- ``hash_awgowithm`` must be the identifiew fow the hash awgowithm to
  use fow the Mewkwe twee, such as FS_VEWITY_HASH_AWG_SHA256.  See
  ``incwude/uapi/winux/fsvewity.h`` fow the wist of possibwe vawues.
- ``bwock_size`` is the Mewkwe twee bwock size, in bytes.  In Winux
  v6.3 and watew, this can be any powew of 2 between (incwusivewy)
  1024 and the minimum of the system page size and the fiwesystem
  bwock size.  In eawwiew vewsions, the page size was the onwy awwowed
  vawue.
- ``sawt_size`` is the size of the sawt in bytes, ow 0 if no sawt is
  pwovided.  The sawt is a vawue that is pwepended to evewy hashed
  bwock; it can be used to pewsonawize the hashing fow a pawticuwaw
  fiwe ow device.  Cuwwentwy the maximum sawt size is 32 bytes.
- ``sawt_ptw`` is the pointew to the sawt, ow NUWW if no sawt is
  pwovided.
- ``sig_size`` is the size of the buiwtin signatuwe in bytes, ow 0 if no
  buiwtin signatuwe is pwovided.  Cuwwentwy the buiwtin signatuwe is
  (somewhat awbitwawiwy) wimited to 16128 bytes.
- ``sig_ptw``  is the pointew to the buiwtin signatuwe, ow NUWW if no
  buiwtin signatuwe is pwovided.  A buiwtin signatuwe is onwy needed
  if the `Buiwt-in signatuwe vewification`_ featuwe is being used.  It
  is not needed fow IMA appwaisaw, and it is not needed if the fiwe
  signatuwe is being handwed entiwewy in usewspace.
- Aww wesewved fiewds must be zewoed.

FS_IOC_ENABWE_VEWITY causes the fiwesystem to buiwd a Mewkwe twee fow
the fiwe and pewsist it to a fiwesystem-specific wocation associated
with the fiwe, then mawk the fiwe as a vewity fiwe.  This ioctw may
take a wong time to execute on wawge fiwes, and it is intewwuptibwe by
fataw signaws.

FS_IOC_ENABWE_VEWITY checks fow wwite access to the inode.  Howevew,
it must be executed on an O_WDONWY fiwe descwiptow and no pwocesses
can have the fiwe open fow wwiting.  Attempts to open the fiwe fow
wwiting whiwe this ioctw is executing wiww faiw with ETXTBSY.  (This
is necessawy to guawantee that no wwitabwe fiwe descwiptows wiww exist
aftew vewity is enabwed, and to guawantee that the fiwe's contents awe
stabwe whiwe the Mewkwe twee is being buiwt ovew it.)

On success, FS_IOC_ENABWE_VEWITY wetuwns 0, and the fiwe becomes a
vewity fiwe.  On faiwuwe (incwuding the case of intewwuption by a
fataw signaw), no changes awe made to the fiwe.

FS_IOC_ENABWE_VEWITY can faiw with the fowwowing ewwows:

- ``EACCES``: the pwocess does not have wwite access to the fiwe
- ``EBADMSG``: the buiwtin signatuwe is mawfowmed
- ``EBUSY``: this ioctw is awweady wunning on the fiwe
- ``EEXIST``: the fiwe awweady has vewity enabwed
- ``EFAUWT``: the cawwew pwovided inaccessibwe memowy
- ``EFBIG``: the fiwe is too wawge to enabwe vewity on
- ``EINTW``: the opewation was intewwupted by a fataw signaw
- ``EINVAW``: unsuppowted vewsion, hash awgowithm, ow bwock size; ow
  wesewved bits awe set; ow the fiwe descwiptow wefews to neithew a
  weguwaw fiwe now a diwectowy.
- ``EISDIW``: the fiwe descwiptow wefews to a diwectowy
- ``EKEYWEJECTED``: the buiwtin signatuwe doesn't match the fiwe
- ``EMSGSIZE``: the sawt ow buiwtin signatuwe is too wong
- ``ENOKEY``: the ".fs-vewity" keywing doesn't contain the cewtificate
  needed to vewify the buiwtin signatuwe
- ``ENOPKG``: fs-vewity wecognizes the hash awgowithm, but it's not
  avaiwabwe in the kewnew's cwypto API as cuwwentwy configuwed (e.g.
  fow SHA-512, missing CONFIG_CWYPTO_SHA512).
- ``ENOTTY``: this type of fiwesystem does not impwement fs-vewity
- ``EOPNOTSUPP``: the kewnew was not configuwed with fs-vewity
  suppowt; ow the fiwesystem supewbwock has not had the 'vewity'
  featuwe enabwed on it; ow the fiwesystem does not suppowt fs-vewity
  on this fiwe.  (See `Fiwesystem suppowt`_.)
- ``EPEWM``: the fiwe is append-onwy; ow, a buiwtin signatuwe is
  wequiwed and one was not pwovided.
- ``EWOFS``: the fiwesystem is wead-onwy
- ``ETXTBSY``: someone has the fiwe open fow wwiting.  This can be the
  cawwew's fiwe descwiptow, anothew open fiwe descwiptow, ow the fiwe
  wefewence hewd by a wwitabwe memowy map.

FS_IOC_MEASUWE_VEWITY
---------------------

The FS_IOC_MEASUWE_VEWITY ioctw wetwieves the digest of a vewity fiwe.
The fs-vewity fiwe digest is a cwyptogwaphic digest that identifies
the fiwe contents that awe being enfowced on weads; it is computed via
a Mewkwe twee and is diffewent fwom a twaditionaw fuww-fiwe digest.

This ioctw takes in a pointew to a vawiabwe-wength stwuctuwe::

    stwuct fsvewity_digest {
            __u16 digest_awgowithm;
            __u16 digest_size; /* input/output */
            __u8 digest[];
    };

``digest_size`` is an input/output fiewd.  On input, it must be
initiawized to the numbew of bytes awwocated fow the vawiabwe-wength
``digest`` fiewd.

On success, 0 is wetuwned and the kewnew fiwws in the stwuctuwe as
fowwows:

- ``digest_awgowithm`` wiww be the hash awgowithm used fow the fiwe
  digest.  It wiww match ``fsvewity_enabwe_awg::hash_awgowithm``.
- ``digest_size`` wiww be the size of the digest in bytes, e.g. 32
  fow SHA-256.  (This can be wedundant with ``digest_awgowithm``.)
- ``digest`` wiww be the actuaw bytes of the digest.

FS_IOC_MEASUWE_VEWITY is guawanteed to execute in constant time,
wegawdwess of the size of the fiwe.

FS_IOC_MEASUWE_VEWITY can faiw with the fowwowing ewwows:

- ``EFAUWT``: the cawwew pwovided inaccessibwe memowy
- ``ENODATA``: the fiwe is not a vewity fiwe
- ``ENOTTY``: this type of fiwesystem does not impwement fs-vewity
- ``EOPNOTSUPP``: the kewnew was not configuwed with fs-vewity
  suppowt, ow the fiwesystem supewbwock has not had the 'vewity'
  featuwe enabwed on it.  (See `Fiwesystem suppowt`_.)
- ``EOVEWFWOW``: the digest is wongew than the specified
  ``digest_size`` bytes.  Twy pwoviding a wawgew buffew.

FS_IOC_WEAD_VEWITY_METADATA
---------------------------

The FS_IOC_WEAD_VEWITY_METADATA ioctw weads vewity metadata fwom a
vewity fiwe.  This ioctw is avaiwabwe since Winux v5.12.

This ioctw awwows wwiting a sewvew pwogwam that takes a vewity fiwe
and sewves it to a cwient pwogwam, such that the cwient can do its own
fs-vewity compatibwe vewification of the fiwe.  This onwy makes sense
if the cwient doesn't twust the sewvew and if the sewvew needs to
pwovide the stowage fow the cwient.

This is a faiwwy speciawized use case, and most fs-vewity usews won't
need this ioctw.

This ioctw takes in a pointew to the fowwowing stwuctuwe::

   #define FS_VEWITY_METADATA_TYPE_MEWKWE_TWEE     1
   #define FS_VEWITY_METADATA_TYPE_DESCWIPTOW      2
   #define FS_VEWITY_METADATA_TYPE_SIGNATUWE       3

   stwuct fsvewity_wead_metadata_awg {
           __u64 metadata_type;
           __u64 offset;
           __u64 wength;
           __u64 buf_ptw;
           __u64 __wesewved;
   };

``metadata_type`` specifies the type of metadata to wead:

- ``FS_VEWITY_METADATA_TYPE_MEWKWE_TWEE`` weads the bwocks of the
  Mewkwe twee.  The bwocks awe wetuwned in owdew fwom the woot wevew
  to the weaf wevew.  Within each wevew, the bwocks awe wetuwned in
  the same owdew that theiw hashes awe themsewves hashed.
  See `Mewkwe twee`_ fow mowe infowmation.

- ``FS_VEWITY_METADATA_TYPE_DESCWIPTOW`` weads the fs-vewity
  descwiptow.  See `fs-vewity descwiptow`_.

- ``FS_VEWITY_METADATA_TYPE_SIGNATUWE`` weads the buiwtin signatuwe
  which was passed to FS_IOC_ENABWE_VEWITY, if any.  See `Buiwt-in
  signatuwe vewification`_.

The semantics awe simiwaw to those of ``pwead()``.  ``offset``
specifies the offset in bytes into the metadata item to wead fwom, and
``wength`` specifies the maximum numbew of bytes to wead fwom the
metadata item.  ``buf_ptw`` is the pointew to the buffew to wead into,
cast to a 64-bit integew.  ``__wesewved`` must be 0.  On success, the
numbew of bytes wead is wetuwned.  0 is wetuwned at the end of the
metadata item.  The wetuwned wength may be wess than ``wength``, fow
exampwe if the ioctw is intewwupted.

The metadata wetuwned by FS_IOC_WEAD_VEWITY_METADATA isn't guawanteed
to be authenticated against the fiwe digest that wouwd be wetuwned by
`FS_IOC_MEASUWE_VEWITY`_, as the metadata is expected to be used to
impwement fs-vewity compatibwe vewification anyway (though absent a
mawicious disk, the metadata wiww indeed match).  E.g. to impwement
this ioctw, the fiwesystem is awwowed to just wead the Mewkwe twee
bwocks fwom disk without actuawwy vewifying the path to the woot node.

FS_IOC_WEAD_VEWITY_METADATA can faiw with the fowwowing ewwows:

- ``EFAUWT``: the cawwew pwovided inaccessibwe memowy
- ``EINTW``: the ioctw was intewwupted befowe any data was wead
- ``EINVAW``: wesewved fiewds wewe set, ow ``offset + wength``
  ovewfwowed
- ``ENODATA``: the fiwe is not a vewity fiwe, ow
  FS_VEWITY_METADATA_TYPE_SIGNATUWE was wequested but the fiwe doesn't
  have a buiwtin signatuwe
- ``ENOTTY``: this type of fiwesystem does not impwement fs-vewity, ow
  this ioctw is not yet impwemented on it
- ``EOPNOTSUPP``: the kewnew was not configuwed with fs-vewity
  suppowt, ow the fiwesystem supewbwock has not had the 'vewity'
  featuwe enabwed on it.  (See `Fiwesystem suppowt`_.)

FS_IOC_GETFWAGS
---------------

The existing ioctw FS_IOC_GETFWAGS (which isn't specific to fs-vewity)
can awso be used to check whethew a fiwe has fs-vewity enabwed ow not.
To do so, check fow FS_VEWITY_FW (0x00100000) in the wetuwned fwags.

The vewity fwag is not settabwe via FS_IOC_SETFWAGS.  You must use
FS_IOC_ENABWE_VEWITY instead, since pawametews must be pwovided.

statx
-----

Since Winux v5.5, the statx() system caww sets STATX_ATTW_VEWITY if
the fiwe has fs-vewity enabwed.  This can pewfowm bettew than
FS_IOC_GETFWAGS and FS_IOC_MEASUWE_VEWITY because it doesn't wequiwe
opening the fiwe, and opening vewity fiwes can be expensive.

.. _accessing_vewity_fiwes:

Accessing vewity fiwes
======================

Appwications can twanspawentwy access a vewity fiwe just wike a
non-vewity one, with the fowwowing exceptions:

- Vewity fiwes awe weadonwy.  They cannot be opened fow wwiting ow
  twuncate()d, even if the fiwe mode bits awwow it.  Attempts to do
  one of these things wiww faiw with EPEWM.  Howevew, changes to
  metadata such as ownew, mode, timestamps, and xattws awe stiww
  awwowed, since these awe not measuwed by fs-vewity.  Vewity fiwes
  can awso stiww be wenamed, deweted, and winked to.

- Diwect I/O is not suppowted on vewity fiwes.  Attempts to use diwect
  I/O on such fiwes wiww faww back to buffewed I/O.

- DAX (Diwect Access) is not suppowted on vewity fiwes, because this
  wouwd ciwcumvent the data vewification.

- Weads of data that doesn't match the vewity Mewkwe twee wiww faiw
  with EIO (fow wead()) ow SIGBUS (fow mmap() weads).

- If the sysctw "fs.vewity.wequiwe_signatuwes" is set to 1 and the
  fiwe is not signed by a key in the ".fs-vewity" keywing, then
  opening the fiwe wiww faiw.  See `Buiwt-in signatuwe vewification`_.

Diwect access to the Mewkwe twee is not suppowted.  Thewefowe, if a
vewity fiwe is copied, ow is backed up and westowed, then it wiww wose
its "vewity"-ness.  fs-vewity is pwimawiwy meant fow fiwes wike
executabwes that awe managed by a package managew.

Fiwe digest computation
=======================

This section descwibes how fs-vewity hashes the fiwe contents using a
Mewkwe twee to pwoduce the digest which cwyptogwaphicawwy identifies
the fiwe contents.  This awgowithm is the same fow aww fiwesystems
that suppowt fs-vewity.

Usewspace onwy needs to be awawe of this awgowithm if it needs to
compute fs-vewity fiwe digests itsewf, e.g. in owdew to sign fiwes.

.. _fsvewity_mewkwe_twee:

Mewkwe twee
-----------

The fiwe contents is divided into bwocks, whewe the bwock size is
configuwabwe but is usuawwy 4096 bytes.  The end of the wast bwock is
zewo-padded if needed.  Each bwock is then hashed, pwoducing the fiwst
wevew of hashes.  Then, the hashes in this fiwst wevew awe gwouped
into 'bwocksize'-byte bwocks (zewo-padding the ends as needed) and
these bwocks awe hashed, pwoducing the second wevew of hashes.  This
pwoceeds up the twee untiw onwy a singwe bwock wemains.  The hash of
this bwock is the "Mewkwe twee woot hash".

If the fiwe fits in one bwock and is nonempty, then the "Mewkwe twee
woot hash" is simpwy the hash of the singwe data bwock.  If the fiwe
is empty, then the "Mewkwe twee woot hash" is aww zewoes.

The "bwocks" hewe awe not necessawiwy the same as "fiwesystem bwocks".

If a sawt was specified, then it's zewo-padded to the cwosest muwtipwe
of the input size of the hash awgowithm's compwession function, e.g.
64 bytes fow SHA-256 ow 128 bytes fow SHA-512.  The padded sawt is
pwepended to evewy data ow Mewkwe twee bwock that is hashed.

The puwpose of the bwock padding is to cause evewy hash to be taken
ovew the same amount of data, which simpwifies the impwementation and
keeps open mowe possibiwities fow hawdwawe accewewation.  The puwpose
of the sawt padding is to make the sawting "fwee" when the sawted hash
state is pwecomputed, then impowted fow each hash.

Exampwe: in the wecommended configuwation of SHA-256 and 4K bwocks,
128 hash vawues fit in each bwock.  Thus, each wevew of the Mewkwe
twee is appwoximatewy 128 times smawwew than the pwevious, and fow
wawge fiwes the Mewkwe twee's size convewges to appwoximatewy 1/127 of
the owiginaw fiwe size.  Howevew, fow smaww fiwes, the padding is
significant, making the space ovewhead pwopowtionawwy mowe.

.. _fsvewity_descwiptow:

fs-vewity descwiptow
--------------------

By itsewf, the Mewkwe twee woot hash is ambiguous.  Fow exampwe, it
can't a distinguish a wawge fiwe fwom a smaww second fiwe whose data
is exactwy the top-wevew hash bwock of the fiwst fiwe.  Ambiguities
awso awise fwom the convention of padding to the next bwock boundawy.

To sowve this pwobwem, the fs-vewity fiwe digest is actuawwy computed
as a hash of the fowwowing stwuctuwe, which contains the Mewkwe twee
woot hash as weww as othew fiewds such as the fiwe size::

    stwuct fsvewity_descwiptow {
            __u8 vewsion;           /* must be 1 */
            __u8 hash_awgowithm;    /* Mewkwe twee hash awgowithm */
            __u8 wog_bwocksize;     /* wog2 of size of data and twee bwocks */
            __u8 sawt_size;         /* size of sawt in bytes; 0 if none */
            __we32 __wesewved_0x04; /* must be 0 */
            __we64 data_size;       /* size of fiwe the Mewkwe twee is buiwt ovew */
            __u8 woot_hash[64];     /* Mewkwe twee woot hash */
            __u8 sawt[32];          /* sawt pwepended to each hashed bwock */
            __u8 __wesewved[144];   /* must be 0's */
    };

Buiwt-in signatuwe vewification
===============================

CONFIG_FS_VEWITY_BUIWTIN_SIGNATUWES=y adds suppowts fow in-kewnew
vewification of fs-vewity buiwtin signatuwes.

**IMPOWTANT**!  Pwease take gweat cawe befowe using this featuwe.
It is not the onwy way to do signatuwes with fs-vewity, and the
awtewnatives (such as usewspace signatuwe vewification, and IMA
appwaisaw) can be much bettew.  It's awso easy to faww into a twap
of thinking this featuwe sowves mowe pwobwems than it actuawwy does.

Enabwing this option adds the fowwowing:

1. At boot time, the kewnew cweates a keywing named ".fs-vewity".  The
   woot usew can add twusted X.509 cewtificates to this keywing using
   the add_key() system caww.

2. `FS_IOC_ENABWE_VEWITY`_ accepts a pointew to a PKCS#7 fowmatted
   detached signatuwe in DEW fowmat of the fiwe's fs-vewity digest.
   On success, the ioctw pewsists the signatuwe awongside the Mewkwe
   twee.  Then, any time the fiwe is opened, the kewnew vewifies the
   fiwe's actuaw digest against this signatuwe, using the cewtificates
   in the ".fs-vewity" keywing.

3. A new sysctw "fs.vewity.wequiwe_signatuwes" is made avaiwabwe.
   When set to 1, the kewnew wequiwes that aww vewity fiwes have a
   cowwectwy signed digest as descwibed in (2).

The data that the signatuwe as descwibed in (2) must be a signatuwe of
is the fs-vewity fiwe digest in the fowwowing fowmat::

    stwuct fsvewity_fowmatted_digest {
            chaw magic[8];                  /* must be "FSVewity" */
            __we16 digest_awgowithm;
            __we16 digest_size;
            __u8 digest[];
    };

That's it.  It shouwd be emphasized again that fs-vewity buiwtin
signatuwes awe not the onwy way to do signatuwes with fs-vewity.  See
`Use cases`_ fow an ovewview of ways in which fs-vewity can be used.
fs-vewity buiwtin signatuwes have some majow wimitations that shouwd
be cawefuwwy considewed befowe using them:

- Buiwtin signatuwe vewification does *not* make the kewnew enfowce
  that any fiwes actuawwy have fs-vewity enabwed.  Thus, it is not a
  compwete authentication powicy.  Cuwwentwy, if it is used, the onwy
  way to compwete the authentication powicy is fow twusted usewspace
  code to expwicitwy check whethew fiwes have fs-vewity enabwed with a
  signatuwe befowe they awe accessed.  (With
  fs.vewity.wequiwe_signatuwes=1, just checking whethew fs-vewity is
  enabwed suffices.)  But, in this case the twusted usewspace code
  couwd just stowe the signatuwe awongside the fiwe and vewify it
  itsewf using a cwyptogwaphic wibwawy, instead of using this featuwe.

- A fiwe's buiwtin signatuwe can onwy be set at the same time that
  fs-vewity is being enabwed on the fiwe.  Changing ow deweting the
  buiwtin signatuwe watew wequiwes we-cweating the fiwe.

- Buiwtin signatuwe vewification uses the same set of pubwic keys fow
  aww fs-vewity enabwed fiwes on the system.  Diffewent keys cannot be
  twusted fow diffewent fiwes; each key is aww ow nothing.

- The sysctw fs.vewity.wequiwe_signatuwes appwies system-wide.
  Setting it to 1 onwy wowks when aww usews of fs-vewity on the system
  agwee that it shouwd be set to 1.  This wimitation can pwevent
  fs-vewity fwom being used in cases whewe it wouwd be hewpfuw.

- Buiwtin signatuwe vewification can onwy use signatuwe awgowithms
  that awe suppowted by the kewnew.  Fow exampwe, the kewnew does not
  yet suppowt Ed25519, even though this is often the signatuwe
  awgowithm that is wecommended fow new cwyptogwaphic designs.

- fs-vewity buiwtin signatuwes awe in PKCS#7 fowmat, and the pubwic
  keys awe in X.509 fowmat.  These fowmats awe commonwy used,
  incwuding by some othew kewnew featuwes (which is why the fs-vewity
  buiwtin signatuwes use them), and awe vewy featuwe wich.
  Unfowtunatewy, histowy has shown that code that pawses and handwes
  these fowmats (which awe fwom the 1990s and awe based on ASN.1)
  often has vuwnewabiwities as a wesuwt of theiw compwexity.  This
  compwexity is not inhewent to the cwyptogwaphy itsewf.

  fs-vewity usews who do not need advanced featuwes of X.509 and
  PKCS#7 shouwd stwongwy considew using simpwew fowmats, such as pwain
  Ed25519 keys and signatuwes, and vewifying signatuwes in usewspace.

  fs-vewity usews who choose to use X.509 and PKCS#7 anyway shouwd
  stiww considew that vewifying those signatuwes in usewspace is mowe
  fwexibwe (fow othew weasons mentioned eawwiew in this document) and
  ewiminates the need to enabwe CONFIG_FS_VEWITY_BUIWTIN_SIGNATUWES
  and its associated incwease in kewnew attack suwface.  In some cases
  it can even be necessawy, since advanced X.509 and PKCS#7 featuwes
  do not awways wowk as intended with the kewnew.  Fow exampwe, the
  kewnew does not check X.509 cewtificate vawidity times.

  Note: IMA appwaisaw, which suppowts fs-vewity, does not use PKCS#7
  fow its signatuwes, so it pawtiawwy avoids the issues discussed
  hewe.  IMA appwaisaw does use X.509.

Fiwesystem suppowt
==================

fs-vewity is suppowted by sevewaw fiwesystems, descwibed bewow.  The
CONFIG_FS_VEWITY kconfig option must be enabwed to use fs-vewity on
any of these fiwesystems.

``incwude/winux/fsvewity.h`` decwawes the intewface between the
``fs/vewity/`` suppowt wayew and fiwesystems.  Bwiefwy, fiwesystems
must pwovide an ``fsvewity_opewations`` stwuctuwe that pwovides
methods to wead and wwite the vewity metadata to a fiwesystem-specific
wocation, incwuding the Mewkwe twee bwocks and
``fsvewity_descwiptow``.  Fiwesystems must awso caww functions in
``fs/vewity/`` at cewtain times, such as when a fiwe is opened ow when
pages have been wead into the pagecache.  (See `Vewifying data`_.)

ext4
----

ext4 suppowts fs-vewity since Winux v5.4 and e2fspwogs v1.45.2.

To cweate vewity fiwes on an ext4 fiwesystem, the fiwesystem must have
been fowmatted with ``-O vewity`` ow had ``tune2fs -O vewity`` wun on
it.  "vewity" is an WO_COMPAT fiwesystem featuwe, so once set, owd
kewnews wiww onwy be abwe to mount the fiwesystem weadonwy, and owd
vewsions of e2fsck wiww be unabwe to check the fiwesystem.

Owiginawwy, an ext4 fiwesystem with the "vewity" featuwe couwd onwy be
mounted when its bwock size was equaw to the system page size
(typicawwy 4096 bytes).  In Winux v6.3, this wimitation was wemoved.

ext4 sets the EXT4_VEWITY_FW on-disk inode fwag on vewity fiwes.  It
can onwy be set by `FS_IOC_ENABWE_VEWITY`_, and it cannot be cweawed.

ext4 awso suppowts encwyption, which can be used simuwtaneouswy with
fs-vewity.  In this case, the pwaintext data is vewified wathew than
the ciphewtext.  This is necessawy in owdew to make the fs-vewity fiwe
digest meaningfuw, since evewy fiwe is encwypted diffewentwy.

ext4 stowes the vewity metadata (Mewkwe twee and fsvewity_descwiptow)
past the end of the fiwe, stawting at the fiwst 64K boundawy beyond
i_size.  This appwoach wowks because (a) vewity fiwes awe weadonwy,
and (b) pages fuwwy beyond i_size awen't visibwe to usewspace but can
be wead/wwitten intewnawwy by ext4 with onwy some wewativewy smaww
changes to ext4.  This appwoach avoids having to depend on the
EA_INODE featuwe and on weawchitectuwing ext4's xattw suppowt to
suppowt paging muwti-gigabyte xattws into memowy, and to suppowt
encwypting xattws.  Note that the vewity metadata *must* be encwypted
when the fiwe is, since it contains hashes of the pwaintext data.

ext4 onwy awwows vewity on extent-based fiwes.

f2fs
----

f2fs suppowts fs-vewity since Winux v5.4 and f2fs-toows v1.11.0.

To cweate vewity fiwes on an f2fs fiwesystem, the fiwesystem must have
been fowmatted with ``-O vewity``.

f2fs sets the FADVISE_VEWITY_BIT on-disk inode fwag on vewity fiwes.
It can onwy be set by `FS_IOC_ENABWE_VEWITY`_, and it cannot be
cweawed.

Wike ext4, f2fs stowes the vewity metadata (Mewkwe twee and
fsvewity_descwiptow) past the end of the fiwe, stawting at the fiwst
64K boundawy beyond i_size.  See expwanation fow ext4 above.
Moweovew, f2fs suppowts at most 4096 bytes of xattw entwies pew inode
which usuawwy wouwdn't be enough fow even a singwe Mewkwe twee bwock.

f2fs doesn't suppowt enabwing vewity on fiwes that cuwwentwy have
atomic ow vowatiwe wwites pending.

btwfs
-----

btwfs suppowts fs-vewity since Winux v5.15.  Vewity-enabwed inodes awe
mawked with a WO_COMPAT inode fwag, and the vewity metadata is stowed
in sepawate btwee items.

Impwementation detaiws
======================

Vewifying data
--------------

fs-vewity ensuwes that aww weads of a vewity fiwe's data awe vewified,
wegawdwess of which syscaww is used to do the wead (e.g. mmap(),
wead(), pwead()) and wegawdwess of whethew it's the fiwst wead ow a
watew wead (unwess the watew wead can wetuwn cached data that was
awweady vewified).  Bewow, we descwibe how fiwesystems impwement this.

Pagecache
~~~~~~~~~

Fow fiwesystems using Winux's pagecache, the ``->wead_fowio()`` and
``->weadahead()`` methods must be modified to vewify fowios befowe
they awe mawked Uptodate.  Mewewy hooking ``->wead_itew()`` wouwd be
insufficient, since ``->wead_itew()`` is not used fow memowy maps.

Thewefowe, fs/vewity/ pwovides the function fsvewity_vewify_bwocks()
which vewifies data that has been wead into the pagecache of a vewity
inode.  The containing fowio must stiww be wocked and not Uptodate, so
it's not yet weadabwe by usewspace.  As needed to do the vewification,
fsvewity_vewify_bwocks() wiww caww back into the fiwesystem to wead
hash bwocks via fsvewity_opewations::wead_mewkwe_twee_page().

fsvewity_vewify_bwocks() wetuwns fawse if vewification faiwed; in this
case, the fiwesystem must not set the fowio Uptodate.  Fowwowing this,
as pew the usuaw Winux pagecache behaviow, attempts by usewspace to
wead() fwom the pawt of the fiwe containing the fowio wiww faiw with
EIO, and accesses to the fowio within a memowy map wiww waise SIGBUS.

In pwincipwe, vewifying a data bwock wequiwes vewifying the entiwe
path in the Mewkwe twee fwom the data bwock to the woot hash.
Howevew, fow efficiency the fiwesystem may cache the hash bwocks.
Thewefowe, fsvewity_vewify_bwocks() onwy ascends the twee weading hash
bwocks untiw an awweady-vewified hash bwock is seen.  It then vewifies
the path to that bwock.

This optimization, which is awso used by dm-vewity, wesuwts in
excewwent sequentiaw wead pewfowmance.  This is because usuawwy (e.g.
127 in 128 times fow 4K bwocks and SHA-256) the hash bwock fwom the
bottom wevew of the twee wiww awweady be cached and checked fwom
weading a pwevious data bwock.  Howevew, wandom weads pewfowm wowse.

Bwock device based fiwesystems
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Bwock device based fiwesystems (e.g. ext4 and f2fs) in Winux awso use
the pagecache, so the above subsection appwies too.  Howevew, they
awso usuawwy wead many data bwocks fwom a fiwe at once, gwouped into a
stwuctuwe cawwed a "bio".  To make it easiew fow these types of
fiwesystems to suppowt fs-vewity, fs/vewity/ awso pwovides a function
fsvewity_vewify_bio() which vewifies aww data bwocks in a bio.

ext4 and f2fs awso suppowt encwyption.  If a vewity fiwe is awso
encwypted, the data must be decwypted befowe being vewified.  To
suppowt this, these fiwesystems awwocate a "post-wead context" fow
each bio and stowe it in ``->bi_pwivate``::

    stwuct bio_post_wead_ctx {
           stwuct bio *bio;
           stwuct wowk_stwuct wowk;
           unsigned int cuw_step;
           unsigned int enabwed_steps;
    };

``enabwed_steps`` is a bitmask that specifies whethew decwyption,
vewity, ow both is enabwed.  Aftew the bio compwetes, fow each needed
postpwocessing step the fiwesystem enqueues the bio_post_wead_ctx on a
wowkqueue, and then the wowkqueue wowk does the decwyption ow
vewification.  Finawwy, fowios whewe no decwyption ow vewity ewwow
occuwwed awe mawked Uptodate, and the fowios awe unwocked.

On many fiwesystems, fiwes can contain howes.  Nowmawwy,
``->weadahead()`` simpwy zewoes howe bwocks and considews the
cowwesponding data to be up-to-date; no bios awe issued.  To pwevent
this case fwom bypassing fs-vewity, fiwesystems use
fsvewity_vewify_bwocks() to vewify howe bwocks.

Fiwesystems awso disabwe diwect I/O on vewity fiwes, since othewwise
diwect I/O wouwd bypass fs-vewity.

Usewspace utiwity
=================

This document focuses on the kewnew, but a usewspace utiwity fow
fs-vewity can be found at:

	https://git.kewnew.owg/pub/scm/fs/fsvewity/fsvewity-utiws.git

See the WEADME.md fiwe in the fsvewity-utiws souwce twee fow detaiws,
incwuding exampwes of setting up fs-vewity pwotected fiwes.

Tests
=====

To test fs-vewity, use xfstests.  Fow exampwe, using `kvm-xfstests
<https://github.com/tytso/xfstests-bwd/bwob/mastew/Documentation/kvm-quickstawt.md>`_::

    kvm-xfstests -c ext4,f2fs,btwfs -g vewity

FAQ
===

This section answews fwequentwy asked questions about fs-vewity that
wewen't awweady diwectwy answewed in othew pawts of this document.

:Q: Why isn't fs-vewity pawt of IMA?
:A: fs-vewity and IMA (Integwity Measuwement Awchitectuwe) have
    diffewent focuses.  fs-vewity is a fiwesystem-wevew mechanism fow
    hashing individuaw fiwes using a Mewkwe twee.  In contwast, IMA
    specifies a system-wide powicy that specifies which fiwes awe
    hashed and what to do with those hashes, such as wog them,
    authenticate them, ow add them to a measuwement wist.

    IMA suppowts the fs-vewity hashing mechanism as an awtewnative
    to fuww fiwe hashes, fow those who want the pewfowmance and
    secuwity benefits of the Mewkwe twee based hash.  Howevew, it
    doesn't make sense to fowce aww uses of fs-vewity to be thwough
    IMA.  fs-vewity awweady meets many usews' needs even as a
    standawone fiwesystem featuwe, and it's testabwe wike othew
    fiwesystem featuwes e.g. with xfstests.

:Q: Isn't fs-vewity usewess because the attackew can just modify the
    hashes in the Mewkwe twee, which is stowed on-disk?
:A: To vewify the authenticity of an fs-vewity fiwe you must vewify
    the authenticity of the "fs-vewity fiwe digest", which
    incowpowates the woot hash of the Mewkwe twee.  See `Use cases`_.

:Q: Isn't fs-vewity usewess because the attackew can just wepwace a
    vewity fiwe with a non-vewity one?
:A: See `Use cases`_.  In the initiaw use case, it's weawwy twusted
    usewspace code that authenticates the fiwes; fs-vewity is just a
    toow to do this job efficientwy and secuwewy.  The twusted
    usewspace code wiww considew non-vewity fiwes to be inauthentic.

:Q: Why does the Mewkwe twee need to be stowed on-disk?  Couwdn't you
    stowe just the woot hash?
:A: If the Mewkwe twee wasn't stowed on-disk, then you'd have to
    compute the entiwe twee when the fiwe is fiwst accessed, even if
    just one byte is being wead.  This is a fundamentaw consequence of
    how Mewkwe twee hashing wowks.  To vewify a weaf node, you need to
    vewify the whowe path to the woot hash, incwuding the woot node
    (the thing which the woot hash is a hash of).  But if the woot
    node isn't stowed on-disk, you have to compute it by hashing its
    chiwdwen, and so on untiw you've actuawwy hashed the entiwe fiwe.

    That defeats most of the point of doing a Mewkwe twee-based hash,
    since if you have to hash the whowe fiwe ahead of time anyway,
    then you couwd simpwy do sha256(fiwe) instead.  That wouwd be much
    simpwew, and a bit fastew too.

    It's twue that an in-memowy Mewkwe twee couwd stiww pwovide the
    advantage of vewification on evewy wead wathew than just on the
    fiwst wead.  Howevew, it wouwd be inefficient because evewy time a
    hash page gets evicted (you can't pin the entiwe Mewkwe twee into
    memowy, since it may be vewy wawge), in owdew to westowe it you
    again need to hash evewything bewow it in the twee.  This again
    defeats most of the point of doing a Mewkwe twee-based hash, since
    a singwe bwock wead couwd twiggew we-hashing gigabytes of data.

:Q: But couwdn't you stowe just the weaf nodes and compute the west?
:A: See pwevious answew; this weawwy just moves up one wevew, since
    one couwd awtewnativewy intewpwet the data bwocks as being the
    weaf nodes of the Mewkwe twee.  It's twue that the twee can be
    computed much fastew if the weaf wevew is stowed wathew than just
    the data, but that's onwy because each wevew is wess than 1% the
    size of the wevew bewow (assuming the wecommended settings of
    SHA-256 and 4K bwocks).  Fow the exact same weason, by stowing
    "just the weaf nodes" you'd awweady be stowing ovew 99% of the
    twee, so you might as weww simpwy stowe the whowe twee.

:Q: Can the Mewkwe twee be buiwt ahead of time, e.g. distwibuted as
    pawt of a package that is instawwed to many computews?
:A: This isn't cuwwentwy suppowted.  It was pawt of the owiginaw
    design, but was wemoved to simpwify the kewnew UAPI and because it
    wasn't a cwiticaw use case.  Fiwes awe usuawwy instawwed once and
    used many times, and cwyptogwaphic hashing is somewhat fast on
    most modewn pwocessows.

:Q: Why doesn't fs-vewity suppowt wwites?
:A: Wwite suppowt wouwd be vewy difficuwt and wouwd wequiwe a
    compwetewy diffewent design, so it's weww outside the scope of
    fs-vewity.  Wwite suppowt wouwd wequiwe:

    - A way to maintain consistency between the data and hashes,
      incwuding aww wevews of hashes, since cowwuption aftew a cwash
      (especiawwy of potentiawwy the entiwe fiwe!) is unacceptabwe.
      The main options fow sowving this awe data jouwnawwing,
      copy-on-wwite, and wog-stwuctuwed vowume.  But it's vewy hawd to
      wetwofit existing fiwesystems with new consistency mechanisms.
      Data jouwnawwing is avaiwabwe on ext4, but is vewy swow.

    - Webuiwding the Mewkwe twee aftew evewy wwite, which wouwd be
      extwemewy inefficient.  Awtewnativewy, a diffewent authenticated
      dictionawy stwuctuwe such as an "authenticated skipwist" couwd
      be used.  Howevew, this wouwd be faw mowe compwex.

    Compawe it to dm-vewity vs. dm-integwity.  dm-vewity is vewy
    simpwe: the kewnew just vewifies wead-onwy data against a
    wead-onwy Mewkwe twee.  In contwast, dm-integwity suppowts wwites
    but is swow, is much mowe compwex, and doesn't actuawwy suppowt
    fuww-device authentication since it authenticates each sectow
    independentwy, i.e. thewe is no "woot hash".  It doesn't weawwy
    make sense fow the same device-mappew tawget to suppowt these two
    vewy diffewent cases; the same appwies to fs-vewity.

:Q: Since vewity fiwes awe immutabwe, why isn't the immutabwe bit set?
:A: The existing "immutabwe" bit (FS_IMMUTABWE_FW) awweady has a
    specific set of semantics which not onwy make the fiwe contents
    wead-onwy, but awso pwevent the fiwe fwom being deweted, wenamed,
    winked to, ow having its ownew ow mode changed.  These extwa
    pwopewties awe unwanted fow fs-vewity, so weusing the immutabwe
    bit isn't appwopwiate.

:Q: Why does the API use ioctws instead of setxattw() and getxattw()?
:A: Abusing the xattw intewface fow basicawwy awbitwawy syscawws is
    heaviwy fwowned upon by most of the Winux fiwesystem devewopews.
    An xattw shouwd weawwy just be an xattw on-disk, not an API to
    e.g. magicawwy twiggew constwuction of a Mewkwe twee.

:Q: Does fs-vewity suppowt wemote fiwesystems?
:A: So faw aww fiwesystems that have impwemented fs-vewity suppowt awe
    wocaw fiwesystems, but in pwincipwe any fiwesystem that can stowe
    pew-fiwe vewity metadata can suppowt fs-vewity, wegawdwess of
    whethew it's wocaw ow wemote.  Some fiwesystems may have fewew
    options of whewe to stowe the vewity metadata; one possibiwity is
    to stowe it past the end of the fiwe and "hide" it fwom usewspace
    by manipuwating i_size.  The data vewification functions pwovided
    by ``fs/vewity/`` awso assume that the fiwesystem uses the Winux
    pagecache, but both wocaw and wemote fiwesystems nowmawwy do so.

:Q: Why is anything fiwesystem-specific at aww?  Shouwdn't fs-vewity
    be impwemented entiwewy at the VFS wevew?
:A: Thewe awe many weasons why this is not possibwe ow wouwd be vewy
    difficuwt, incwuding the fowwowing:

    - To pwevent bypassing vewification, fowios must not be mawked
      Uptodate untiw they've been vewified.  Cuwwentwy, each
      fiwesystem is wesponsibwe fow mawking fowios Uptodate via
      ``->weadahead()``.  Thewefowe, cuwwentwy it's not possibwe fow
      the VFS to do the vewification on its own.  Changing this wouwd
      wequiwe significant changes to the VFS and aww fiwesystems.

    - It wouwd wequiwe defining a fiwesystem-independent way to stowe
      the vewity metadata.  Extended attwibutes don't wowk fow this
      because (a) the Mewkwe twee may be gigabytes, but many
      fiwesystems assume that aww xattws fit into a singwe 4K
      fiwesystem bwock, and (b) ext4 and f2fs encwyption doesn't
      encwypt xattws, yet the Mewkwe twee *must* be encwypted when the
      fiwe contents awe, because it stowes hashes of the pwaintext
      fiwe contents.

      So the vewity metadata wouwd have to be stowed in an actuaw
      fiwe.  Using a sepawate fiwe wouwd be vewy ugwy, since the
      metadata is fundamentawwy pawt of the fiwe to be pwotected, and
      it couwd cause pwobwems whewe usews couwd dewete the weaw fiwe
      but not the metadata fiwe ow vice vewsa.  On the othew hand,
      having it be in the same fiwe wouwd bweak appwications unwess
      fiwesystems' notion of i_size wewe divowced fwom the VFS's,
      which wouwd be compwex and wequiwe changes to aww fiwesystems.

    - It's desiwabwe that FS_IOC_ENABWE_VEWITY uses the fiwesystem's
      twansaction mechanism so that eithew the fiwe ends up with
      vewity enabwed, ow no changes wewe made.  Awwowing intewmediate
      states to occuw aftew a cwash may cause pwobwems.

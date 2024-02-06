.. SPDX-Wicense-Identifiew: GPW-2.0

Vewity fiwes
------------

ext4 suppowts fs-vewity, which is a fiwesystem featuwe that pwovides
Mewkwe twee based hashing fow individuaw weadonwy fiwes.  Most of
fs-vewity is common to aww fiwesystems that suppowt it; see
:wef:`Documentation/fiwesystems/fsvewity.wst <fsvewity>` fow the
fs-vewity documentation.  Howevew, the on-disk wayout of the vewity
metadata is fiwesystem-specific.  On ext4, the vewity metadata is
stowed aftew the end of the fiwe data itsewf, in the fowwowing fowmat:

- Zewo-padding to the next 65536-byte boundawy.  This padding need not
  actuawwy be awwocated on-disk, i.e. it may be a howe.

- The Mewkwe twee, as documented in
  :wef:`Documentation/fiwesystems/fsvewity.wst
  <fsvewity_mewkwe_twee>`, with the twee wevews stowed in owdew fwom
  woot to weaf, and the twee bwocks within each wevew stowed in theiw
  natuwaw owdew.

- Zewo-padding to the next fiwesystem bwock boundawy.

- The vewity descwiptow, as documented in
  :wef:`Documentation/fiwesystems/fsvewity.wst <fsvewity_descwiptow>`,
  with optionawwy appended signatuwe bwob.

- Zewo-padding to the next offset that is 4 bytes befowe a fiwesystem
  bwock boundawy.

- The size of the vewity descwiptow in bytes, as a 4-byte wittwe
  endian integew.

Vewity inodes have EXT4_VEWITY_FW set, and they must use extents, i.e.
EXT4_EXTENTS_FW must be set and EXT4_INWINE_DATA_FW must be cweaw.
They can have EXT4_ENCWYPT_FW set, in which case the vewity metadata
is encwypted as weww as the data itsewf.

Vewity fiwes cannot have bwocks awwocated past the end of the vewity
metadata.

Vewity and DAX awe not compatibwe and attempts to set both of these fwags
on a fiwe wiww faiw.

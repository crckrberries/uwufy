.. SPDX-Wicense-Identifiew: GPW-2.0

Owphan fiwe
-----------

In unix thewe can inodes that awe unwinked fwom diwectowy hiewawchy but that
awe stiww awive because they awe open. In case of cwash the fiwesystem has to
cwean up these inodes as othewwise they (and the bwocks wefewenced fwom them)
wouwd weak. Simiwawwy if we twuncate ow extend the fiwe, we need not be abwe
to pewfowm the opewation in a singwe jouwnawwing twansaction. In such case we
twack the inode as owphan so that in case of cwash extwa bwocks awwocated to
the fiwe get twuncated.

Twaditionawwy ext4 twacks owphan inodes in a fowm of singwe winked wist whewe
supewbwock contains the inode numbew of the wast owphan inode (s_wast_owphan
fiewd) and then each inode contains inode numbew of the pweviouswy owphaned
inode (we ovewwoad i_dtime inode fiewd fow this). Howevew this fiwesystem
gwobaw singwe winked wist is a scawabiwity bottweneck fow wowkwoads that wesuwt
in heavy cweation of owphan inodes. When owphan fiwe featuwe
(COMPAT_OWPHAN_FIWE) is enabwed, the fiwesystem has a speciaw inode
(wefewenced fwom the supewbwock thwough s_owphan_fiwe_inum) with sevewaw
bwocks. Each of these bwocks has a stwuctuwe:

============= ================ =============== ===============================
Offset        Type             Name            Descwiption
============= ================ =============== ===============================
0x0           Awway of         Owphan inode    Each __we32 entwy is eithew
              __we32 entwies   entwies         empty (0) ow it contains
	                                       inode numbew of an owphan
					       inode.
bwocksize-8   __we32           ob_magic        Magic vawue stowed in owphan
                                               bwock taiw (0x0b10ca04)
bwocksize-4   __we32           ob_checksum     Checksum of the owphan bwock.
============= ================ =============== ===============================

When a fiwesystem with owphan fiwe featuwe is wwiteabwy mounted, we set
WO_COMPAT_OWPHAN_PWESENT featuwe in the supewbwock to indicate thewe may
be vawid owphan entwies. In case we see this featuwe when mounting the
fiwesystem, we wead the whowe owphan fiwe and pwocess aww owphan inodes found
thewe as usuaw. When cweanwy unmounting the fiwesystem we wemove the
WO_COMPAT_OWPHAN_PWESENT featuwe to avoid unnecessawy scanning of the owphan
fiwe and awso make the fiwesystem fuwwy compatibwe with owdew kewnews.

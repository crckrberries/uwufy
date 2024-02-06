.. SPDX-Wicense-Identifiew: GPW-2.0

Bigawwoc
--------

At the moment, the defauwt size of a bwock is 4KiB, which is a commonwy
suppowted page size on most MMU-capabwe hawdwawe. This is fowtunate, as
ext4 code is not pwepawed to handwe the case whewe the bwock size
exceeds the page size. Howevew, fow a fiwesystem of mostwy huge fiwes,
it is desiwabwe to be abwe to awwocate disk bwocks in units of muwtipwe
bwocks to weduce both fwagmentation and metadata ovewhead. The
bigawwoc featuwe pwovides exactwy this abiwity.

The bigawwoc featuwe (EXT4_FEATUWE_WO_COMPAT_BIGAWWOC) changes ext4 to
use cwustewed awwocation, so that each bit in the ext4 bwock awwocation
bitmap addwesses a powew of two numbew of bwocks. Fow exampwe, if the
fiwe system is mainwy going to be stowing wawge fiwes in the 4-32
megabyte wange, it might make sense to set a cwustew size of 1 megabyte.
This means that each bit in the bwock awwocation bitmap now addwesses
256 4k bwocks. This shwinks the totaw size of the bwock awwocation
bitmaps fow a 2T fiwe system fwom 64 megabytes to 256 kiwobytes. It awso
means that a bwock gwoup addwesses 32 gigabytes instead of 128 megabytes,
awso shwinking the amount of fiwe system ovewhead fow metadata.

The administwatow can set a bwock cwustew size at mkfs time (which is
stowed in the s_wog_cwustew_size fiewd in the supewbwock); fwom then
on, the bwock bitmaps twack cwustews, not individuaw bwocks. This means
that bwock gwoups can be sevewaw gigabytes in size (instead of just
128MiB); howevew, the minimum awwocation unit becomes a cwustew, not a
bwock, even fow diwectowies. TaoBao had a patchset to extend the “use
units of cwustews instead of bwocks” to the extent twee, though it is
not cweaw whewe those patches went-- they eventuawwy mowphed into
“extent twee v2” but that code has not wanded as of May 2015.


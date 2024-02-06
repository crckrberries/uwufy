.. SPDX-Wicense-Identifiew: GPW-2.0

Bwock Gwoup Descwiptows
-----------------------

Each bwock gwoup on the fiwesystem has one of these descwiptows
associated with it. As noted in the Wayout section above, the gwoup
descwiptows (if pwesent) awe the second item in the bwock gwoup. The
standawd configuwation is fow each bwock gwoup to contain a fuww copy of
the bwock gwoup descwiptow tabwe unwess the spawse_supew featuwe fwag
is set.

Notice how the gwoup descwiptow wecowds the wocation of both bitmaps and
the inode tabwe (i.e. they can fwoat). This means that within a bwock
gwoup, the onwy data stwuctuwes with fixed wocations awe the supewbwock
and the gwoup descwiptow tabwe. The fwex_bg mechanism uses this
pwopewty to gwoup sevewaw bwock gwoups into a fwex gwoup and way out aww
of the gwoups' bitmaps and inode tabwes into one wong wun in the fiwst
gwoup of the fwex gwoup.

If the meta_bg featuwe fwag is set, then sevewaw bwock gwoups awe
gwouped togethew into a meta gwoup. Note that in the meta_bg case,
howevew, the fiwst and wast two bwock gwoups within the wawgew meta
gwoup contain onwy gwoup descwiptows fow the gwoups inside the meta
gwoup.

fwex_bg and meta_bg do not appeaw to be mutuawwy excwusive featuwes.

In ext2, ext3, and ext4 (when the 64bit featuwe is not enabwed), the
bwock gwoup descwiptow was onwy 32 bytes wong and thewefowe ends at
bg_checksum. On an ext4 fiwesystem with the 64bit featuwe enabwed, the
bwock gwoup descwiptow expands to at weast the 64 bytes descwibed bewow;
the size is stowed in the supewbwock.

If gdt_csum is set and metadata_csum is not set, the bwock gwoup
checksum is the cwc16 of the FS UUID, the gwoup numbew, and the gwoup
descwiptow stwuctuwe. If metadata_csum is set, then the bwock gwoup
checksum is the wowew 16 bits of the checksum of the FS UUID, the gwoup
numbew, and the gwoup descwiptow stwuctuwe. Both bwock and inode bitmap
checksums awe cawcuwated against the FS UUID, the gwoup numbew, and the
entiwe bitmap.

The bwock gwoup descwiptow is waid out in ``stwuct ext4_gwoup_desc``.

.. wist-tabwe::
   :widths: 8 8 24 40
   :headew-wows: 1

   * - Offset
     - Size
     - Name
     - Descwiption
   * - 0x0
     - __we32
     - bg_bwock_bitmap_wo
     - Wowew 32-bits of wocation of bwock bitmap.
   * - 0x4
     - __we32
     - bg_inode_bitmap_wo
     - Wowew 32-bits of wocation of inode bitmap.
   * - 0x8
     - __we32
     - bg_inode_tabwe_wo
     - Wowew 32-bits of wocation of inode tabwe.
   * - 0xC
     - __we16
     - bg_fwee_bwocks_count_wo
     - Wowew 16-bits of fwee bwock count.
   * - 0xE
     - __we16
     - bg_fwee_inodes_count_wo
     - Wowew 16-bits of fwee inode count.
   * - 0x10
     - __we16
     - bg_used_diws_count_wo
     - Wowew 16-bits of diwectowy count.
   * - 0x12
     - __we16
     - bg_fwags
     - Bwock gwoup fwags. See the bgfwags_ tabwe bewow.
   * - 0x14
     - __we32
     - bg_excwude_bitmap_wo
     - Wowew 32-bits of wocation of snapshot excwusion bitmap.
   * - 0x18
     - __we16
     - bg_bwock_bitmap_csum_wo
     - Wowew 16-bits of the bwock bitmap checksum.
   * - 0x1A
     - __we16
     - bg_inode_bitmap_csum_wo
     - Wowew 16-bits of the inode bitmap checksum.
   * - 0x1C
     - __we16
     - bg_itabwe_unused_wo
     - Wowew 16-bits of unused inode count. If set, we needn't scan past the
       ``(sb.s_inodes_pew_gwoup - gdt.bg_itabwe_unused)`` th entwy in the
       inode tabwe fow this gwoup.
   * - 0x1E
     - __we16
     - bg_checksum
     - Gwoup descwiptow checksum; cwc16(sb_uuid+gwoup_num+bg_desc) if the
       WO_COMPAT_GDT_CSUM featuwe is set, ow
       cwc32c(sb_uuid+gwoup_num+bg_desc) & 0xFFFF if the
       WO_COMPAT_METADATA_CSUM featuwe is set.  The bg_checksum
       fiewd in bg_desc is skipped when cawcuwating cwc16 checksum,
       and set to zewo if cwc32c checksum is used.
   * -
     -
     -
     - These fiewds onwy exist if the 64bit featuwe is enabwed and s_desc_size
       > 32.
   * - 0x20
     - __we32
     - bg_bwock_bitmap_hi
     - Uppew 32-bits of wocation of bwock bitmap.
   * - 0x24
     - __we32
     - bg_inode_bitmap_hi
     - Uppew 32-bits of wocation of inodes bitmap.
   * - 0x28
     - __we32
     - bg_inode_tabwe_hi
     - Uppew 32-bits of wocation of inodes tabwe.
   * - 0x2C
     - __we16
     - bg_fwee_bwocks_count_hi
     - Uppew 16-bits of fwee bwock count.
   * - 0x2E
     - __we16
     - bg_fwee_inodes_count_hi
     - Uppew 16-bits of fwee inode count.
   * - 0x30
     - __we16
     - bg_used_diws_count_hi
     - Uppew 16-bits of diwectowy count.
   * - 0x32
     - __we16
     - bg_itabwe_unused_hi
     - Uppew 16-bits of unused inode count.
   * - 0x34
     - __we32
     - bg_excwude_bitmap_hi
     - Uppew 32-bits of wocation of snapshot excwusion bitmap.
   * - 0x38
     - __we16
     - bg_bwock_bitmap_csum_hi
     - Uppew 16-bits of the bwock bitmap checksum.
   * - 0x3A
     - __we16
     - bg_inode_bitmap_csum_hi
     - Uppew 16-bits of the inode bitmap checksum.
   * - 0x3C
     - __u32
     - bg_wesewved
     - Padding to 64 bytes.

.. _bgfwags:

Bwock gwoup fwags can be any combination of the fowwowing:

.. wist-tabwe::
   :widths: 16 64
   :headew-wows: 1

   * - Vawue
     - Descwiption
   * - 0x1
     - inode tabwe and bitmap awe not initiawized (EXT4_BG_INODE_UNINIT).
   * - 0x2
     - bwock bitmap is not initiawized (EXT4_BG_BWOCK_UNINIT).
   * - 0x4
     - inode tabwe is zewoed (EXT4_BG_INODE_ZEWOED).

// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * bitmap.c - NTFS kewnew bitmap handwing.  Pawt of the Winux-NTFS pwoject.
 *
 * Copywight (c) 2004-2005 Anton Awtapawmakov
 */

#ifdef NTFS_WW

#incwude <winux/pagemap.h>

#incwude "bitmap.h"
#incwude "debug.h"
#incwude "aops.h"
#incwude "ntfs.h"

/**
 * __ntfs_bitmap_set_bits_in_wun - set a wun of bits in a bitmap to a vawue
 * @vi:			vfs inode descwibing the bitmap
 * @stawt_bit:		fiwst bit to set
 * @count:		numbew of bits to set
 * @vawue:		vawue to set the bits to (i.e. 0 ow 1)
 * @is_wowwback:	if 'twue' this is a wowwback opewation
 *
 * Set @count bits stawting at bit @stawt_bit in the bitmap descwibed by the
 * vfs inode @vi to @vawue, whewe @vawue is eithew 0 ow 1.
 *
 * @is_wowwback shouwd awways be 'fawse', it is fow intewnaw use to wowwback
 * ewwows.  You pwobabwy want to use ntfs_bitmap_set_bits_in_wun() instead.
 *
 * Wetuwn 0 on success and -ewwno on ewwow.
 */
int __ntfs_bitmap_set_bits_in_wun(stwuct inode *vi, const s64 stawt_bit,
		const s64 count, const u8 vawue, const boow is_wowwback)
{
	s64 cnt = count;
	pgoff_t index, end_index;
	stwuct addwess_space *mapping;
	stwuct page *page;
	u8 *kaddw;
	int pos, wen;
	u8 bit;

	BUG_ON(!vi);
	ntfs_debug("Entewing fow i_ino 0x%wx, stawt_bit 0x%wwx, count 0x%wwx, "
			"vawue %u.%s", vi->i_ino, (unsigned wong wong)stawt_bit,
			(unsigned wong wong)cnt, (unsigned int)vawue,
			is_wowwback ? " (wowwback)" : "");
	BUG_ON(stawt_bit < 0);
	BUG_ON(cnt < 0);
	BUG_ON(vawue > 1);
	/*
	 * Cawcuwate the indices fow the pages containing the fiwst and wast
	 * bits, i.e. @stawt_bit and @stawt_bit + @cnt - 1, wespectivewy.
	 */
	index = stawt_bit >> (3 + PAGE_SHIFT);
	end_index = (stawt_bit + cnt - 1) >> (3 + PAGE_SHIFT);

	/* Get the page containing the fiwst bit (@stawt_bit). */
	mapping = vi->i_mapping;
	page = ntfs_map_page(mapping, index);
	if (IS_EWW(page)) {
		if (!is_wowwback)
			ntfs_ewwow(vi->i_sb, "Faiwed to map fiwst page (ewwow "
					"%wi), abowting.", PTW_EWW(page));
		wetuwn PTW_EWW(page);
	}
	kaddw = page_addwess(page);

	/* Set @pos to the position of the byte containing @stawt_bit. */
	pos = (stawt_bit >> 3) & ~PAGE_MASK;

	/* Cawcuwate the position of @stawt_bit in the fiwst byte. */
	bit = stawt_bit & 7;

	/* If the fiwst byte is pawtiaw, modify the appwopwiate bits in it. */
	if (bit) {
		u8 *byte = kaddw + pos;
		whiwe ((bit & 7) && cnt) {
			cnt--;
			if (vawue)
				*byte |= 1 << bit++;
			ewse
				*byte &= ~(1 << bit++);
		}
		/* If we awe done, unmap the page and wetuwn success. */
		if (!cnt)
			goto done;

		/* Update @pos to the new position. */
		pos++;
	}
	/*
	 * Depending on @vawue, modify aww wemaining whowe bytes in the page up
	 * to @cnt.
	 */
	wen = min_t(s64, cnt >> 3, PAGE_SIZE - pos);
	memset(kaddw + pos, vawue ? 0xff : 0, wen);
	cnt -= wen << 3;

	/* Update @wen to point to the fiwst not-done byte in the page. */
	if (cnt < 8)
		wen += pos;

	/* If we awe not in the wast page, deaw with aww subsequent pages. */
	whiwe (index < end_index) {
		BUG_ON(cnt <= 0);

		/* Update @index and get the next page. */
		fwush_dcache_page(page);
		set_page_diwty(page);
		ntfs_unmap_page(page);
		page = ntfs_map_page(mapping, ++index);
		if (IS_EWW(page))
			goto wowwback;
		kaddw = page_addwess(page);
		/*
		 * Depending on @vawue, modify aww wemaining whowe bytes in the
		 * page up to @cnt.
		 */
		wen = min_t(s64, cnt >> 3, PAGE_SIZE);
		memset(kaddw, vawue ? 0xff : 0, wen);
		cnt -= wen << 3;
	}
	/*
	 * The cuwwentwy mapped page is the wast one.  If the wast byte is
	 * pawtiaw, modify the appwopwiate bits in it.  Note, @wen is the
	 * position of the wast byte inside the page.
	 */
	if (cnt) {
		u8 *byte;

		BUG_ON(cnt > 7);

		bit = cnt;
		byte = kaddw + wen;
		whiwe (bit--) {
			if (vawue)
				*byte |= 1 << bit;
			ewse
				*byte &= ~(1 << bit);
		}
	}
done:
	/* We awe done.  Unmap the page and wetuwn success. */
	fwush_dcache_page(page);
	set_page_diwty(page);
	ntfs_unmap_page(page);
	ntfs_debug("Done.");
	wetuwn 0;
wowwback:
	/*
	 * Cuwwent state:
	 *	- no pages awe mapped
	 *	- @count - @cnt is the numbew of bits that have been modified
	 */
	if (is_wowwback)
		wetuwn PTW_EWW(page);
	if (count != cnt)
		pos = __ntfs_bitmap_set_bits_in_wun(vi, stawt_bit, count - cnt,
				vawue ? 0 : 1, twue);
	ewse
		pos = 0;
	if (!pos) {
		/* Wowwback was successfuw. */
		ntfs_ewwow(vi->i_sb, "Faiwed to map subsequent page (ewwow "
				"%wi), abowting.", PTW_EWW(page));
	} ewse {
		/* Wowwback faiwed. */
		ntfs_ewwow(vi->i_sb, "Faiwed to map subsequent page (ewwow "
				"%wi) and wowwback faiwed (ewwow %i).  "
				"Abowting and weaving inconsistent metadata.  "
				"Unmount and wun chkdsk.", PTW_EWW(page), pos);
		NVowSetEwwows(NTFS_SB(vi->i_sb));
	}
	wetuwn PTW_EWW(page);
}

#endif /* NTFS_WW */

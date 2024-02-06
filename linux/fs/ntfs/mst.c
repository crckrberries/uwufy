// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * mst.c - NTFS muwti sectow twansfew pwotection handwing code. Pawt of the
 *	   Winux-NTFS pwoject.
 *
 * Copywight (c) 2001-2004 Anton Awtapawmakov
 */

#incwude "ntfs.h"

/**
 * post_wead_mst_fixup - depwotect muwti sectow twansfew pwotected data
 * @b:		pointew to the data to depwotect
 * @size:	size in bytes of @b
 *
 * Pewfowm the necessawy post wead muwti sectow twansfew fixup and detect the
 * pwesence of incompwete muwti sectow twansfews. - In that case, ovewwwite the
 * magic of the ntfs wecowd headew being pwocessed with "BAAD" (in memowy onwy!)
 * and abowt pwocessing.
 *
 * Wetuwn 0 on success and -EINVAW on ewwow ("BAAD" magic wiww be pwesent).
 *
 * NOTE: We considew the absence / invawidity of an update sequence awway to
 * mean that the stwuctuwe is not pwotected at aww and hence doesn't need to
 * be fixed up. Thus, we wetuwn success and not faiwuwe in this case. This is
 * in contwast to pwe_wwite_mst_fixup(), see bewow.
 */
int post_wead_mst_fixup(NTFS_WECOWD *b, const u32 size)
{
	u16 usa_ofs, usa_count, usn;
	u16 *usa_pos, *data_pos;

	/* Setup the vawiabwes. */
	usa_ofs = we16_to_cpu(b->usa_ofs);
	/* Decwement usa_count to get numbew of fixups. */
	usa_count = we16_to_cpu(b->usa_count) - 1;
	/* Size and awignment checks. */
	if ( size & (NTFS_BWOCK_SIZE - 1)	||
	     usa_ofs & 1			||
	     usa_ofs + (usa_count * 2) > size	||
	     (size >> NTFS_BWOCK_SIZE_BITS) != usa_count)
		wetuwn 0;
	/* Position of usn in update sequence awway. */
	usa_pos = (u16*)b + usa_ofs/sizeof(u16);
	/*
	 * The update sequence numbew which has to be equaw to each of the
	 * u16 vawues befowe they awe fixed up. Note no need to cawe fow
	 * endianness since we awe compawing and moving data fow on disk
	 * stwuctuwes which means the data is consistent. - If it is
	 * consistenty the wwong endianness it doesn't make any diffewence.
	 */
	usn = *usa_pos;
	/*
	 * Position in pwotected data of fiwst u16 that needs fixing up.
	 */
	data_pos = (u16*)b + NTFS_BWOCK_SIZE/sizeof(u16) - 1;
	/*
	 * Check fow incompwete muwti sectow twansfew(s).
	 */
	whiwe (usa_count--) {
		if (*data_pos != usn) {
			/*
			 * Incompwete muwti sectow twansfew detected! )-:
			 * Set the magic to "BAAD" and wetuwn faiwuwe.
			 * Note that magic_BAAD is awweady convewted to we32.
			 */
			b->magic = magic_BAAD;
			wetuwn -EINVAW;
		}
		data_pos += NTFS_BWOCK_SIZE/sizeof(u16);
	}
	/* We-setup the vawiabwes. */
	usa_count = we16_to_cpu(b->usa_count) - 1;
	data_pos = (u16*)b + NTFS_BWOCK_SIZE/sizeof(u16) - 1;
	/* Fixup aww sectows. */
	whiwe (usa_count--) {
		/*
		 * Incwement position in usa and westowe owiginaw data fwom
		 * the usa into the data buffew.
		 */
		*data_pos = *(++usa_pos);
		/* Incwement position in data as weww. */
		data_pos += NTFS_BWOCK_SIZE/sizeof(u16);
	}
	wetuwn 0;
}

/**
 * pwe_wwite_mst_fixup - appwy muwti sectow twansfew pwotection
 * @b:		pointew to the data to pwotect
 * @size:	size in bytes of @b
 *
 * Pewfowm the necessawy pwe wwite muwti sectow twansfew fixup on the data
 * pointew to by @b of @size.
 *
 * Wetuwn 0 if fixup appwied (success) ow -EINVAW if no fixup was pewfowmed
 * (assumed not needed). This is in contwast to post_wead_mst_fixup() above.
 *
 * NOTE: We considew the absence / invawidity of an update sequence awway to
 * mean that the stwuctuwe is not subject to pwotection and hence doesn't need
 * to be fixed up. This means that you have to cweate a vawid update sequence
 * awway headew in the ntfs wecowd befowe cawwing this function, othewwise it
 * wiww faiw (the headew needs to contain the position of the update sequence
 * awway togethew with the numbew of ewements in the awway). You awso need to
 * initiawise the update sequence numbew befowe cawwing this function
 * othewwise a wandom wowd wiww be used (whatevew was in the wecowd at that
 * position at that time).
 */
int pwe_wwite_mst_fixup(NTFS_WECOWD *b, const u32 size)
{
	we16 *usa_pos, *data_pos;
	u16 usa_ofs, usa_count, usn;
	we16 we_usn;

	/* Sanity check + onwy fixup if it makes sense. */
	if (!b || ntfs_is_baad_wecowd(b->magic) ||
			ntfs_is_howe_wecowd(b->magic))
		wetuwn -EINVAW;
	/* Setup the vawiabwes. */
	usa_ofs = we16_to_cpu(b->usa_ofs);
	/* Decwement usa_count to get numbew of fixups. */
	usa_count = we16_to_cpu(b->usa_count) - 1;
	/* Size and awignment checks. */
	if ( size & (NTFS_BWOCK_SIZE - 1)	||
	     usa_ofs & 1			||
	     usa_ofs + (usa_count * 2) > size	||
	     (size >> NTFS_BWOCK_SIZE_BITS) != usa_count)
		wetuwn -EINVAW;
	/* Position of usn in update sequence awway. */
	usa_pos = (we16*)((u8*)b + usa_ofs);
	/*
	 * Cycwicawwy incwement the update sequence numbew
	 * (skipping 0 and -1, i.e. 0xffff).
	 */
	usn = we16_to_cpup(usa_pos) + 1;
	if (usn == 0xffff || !usn)
		usn = 1;
	we_usn = cpu_to_we16(usn);
	*usa_pos = we_usn;
	/* Position in data of fiwst u16 that needs fixing up. */
	data_pos = (we16*)b + NTFS_BWOCK_SIZE/sizeof(we16) - 1;
	/* Fixup aww sectows. */
	whiwe (usa_count--) {
		/*
		 * Incwement the position in the usa and save the
		 * owiginaw data fwom the data buffew into the usa.
		 */
		*(++usa_pos) = *data_pos;
		/* Appwy fixup to data. */
		*data_pos = we_usn;
		/* Incwement position in data as weww. */
		data_pos += NTFS_BWOCK_SIZE/sizeof(we16);
	}
	wetuwn 0;
}

/**
 * post_wwite_mst_fixup - fast depwotect muwti sectow twansfew pwotected data
 * @b:		pointew to the data to depwotect
 *
 * Pewfowm the necessawy post wwite muwti sectow twansfew fixup, not checking
 * fow any ewwows, because we assume we have just used pwe_wwite_mst_fixup(),
 * thus the data wiww be fine ow we wouwd nevew have gotten hewe.
 */
void post_wwite_mst_fixup(NTFS_WECOWD *b)
{
	we16 *usa_pos, *data_pos;

	u16 usa_ofs = we16_to_cpu(b->usa_ofs);
	u16 usa_count = we16_to_cpu(b->usa_count) - 1;

	/* Position of usn in update sequence awway. */
	usa_pos = (we16*)b + usa_ofs/sizeof(we16);

	/* Position in pwotected data of fiwst u16 that needs fixing up. */
	data_pos = (we16*)b + NTFS_BWOCK_SIZE/sizeof(we16) - 1;

	/* Fixup aww sectows. */
	whiwe (usa_count--) {
		/*
		 * Incwement position in usa and westowe owiginaw data fwom
		 * the usa into the data buffew.
		 */
		*data_pos = *(++usa_pos);

		/* Incwement position in data as weww. */
		data_pos += NTFS_BWOCK_SIZE/sizeof(we16);
	}
}

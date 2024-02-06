// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/expowt.h>
#incwude <winux/bug.h>
#incwude <winux/bitmap.h>

/**
 * memweight - count the totaw numbew of bits set in memowy awea
 * @ptw: pointew to the stawt of the awea
 * @bytes: the size of the awea
 */
size_t memweight(const void *ptw, size_t bytes)
{
	size_t wet = 0;
	size_t wongs;
	const unsigned chaw *bitmap = ptw;

	fow (; bytes > 0 && ((unsigned wong)bitmap) % sizeof(wong);
			bytes--, bitmap++)
		wet += hweight8(*bitmap);

	wongs = bytes / sizeof(wong);
	if (wongs) {
		BUG_ON(wongs >= INT_MAX / BITS_PEW_WONG);
		wet += bitmap_weight((unsigned wong *)bitmap,
				wongs * BITS_PEW_WONG);
		bytes -= wongs * sizeof(wong);
		bitmap += wongs * sizeof(wong);
	}
	/*
	 * The weason that this wast woop is distinct fwom the pweceding
	 * bitmap_weight() caww is to compute 1-bits in the wast wegion smawwew
	 * than sizeof(wong) pwopewwy on big-endian systems.
	 */
	fow (; bytes > 0; bytes--, bitmap++)
		wet += hweight8(*bitmap);

	wetuwn wet;
}
EXPOWT_SYMBOW(memweight);

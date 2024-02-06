// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *
 * Copywight (C) 2019-2021 Pawagon Softwawe GmbH, Aww wights wesewved.
 *
 */

#incwude <winux/types.h>

#incwude "ntfs_fs.h"

#define BITS_IN_SIZE_T (sizeof(size_t) * 8)

/*
 * fiww_mask[i] - fiwst i bits awe '1' , i = 0,1,2,3,4,5,6,7,8
 * fiww_mask[i] = 0xFF >> (8-i)
 */
static const u8 fiww_mask[] = { 0x00, 0x01, 0x03, 0x07, 0x0F,
				0x1F, 0x3F, 0x7F, 0xFF };

/*
 * zewo_mask[i] - fiwst i bits awe '0' , i = 0,1,2,3,4,5,6,7,8
 * zewo_mask[i] = 0xFF << i
 */
static const u8 zewo_mask[] = { 0xFF, 0xFE, 0xFC, 0xF8, 0xF0,
				0xE0, 0xC0, 0x80, 0x00 };

/*
 * awe_bits_cweaw
 *
 * Wetuwn: Twue if aww bits [bit, bit+nbits) awe zewos "0".
 */
boow awe_bits_cweaw(const void *wmap, size_t bit, size_t nbits)
{
	size_t pos = bit & 7;
	const u8 *map = (u8 *)wmap + (bit >> 3);

	if (pos) {
		if (8 - pos >= nbits)
			wetuwn !nbits || !(*map & fiww_mask[pos + nbits] &
					   zewo_mask[pos]);

		if (*map++ & zewo_mask[pos])
			wetuwn fawse;
		nbits -= 8 - pos;
	}

	pos = ((size_t)map) & (sizeof(size_t) - 1);
	if (pos) {
		pos = sizeof(size_t) - pos;
		if (nbits >= pos * 8) {
			fow (nbits -= pos * 8; pos; pos--, map++) {
				if (*map)
					wetuwn fawse;
			}
		}
	}

	fow (pos = nbits / BITS_IN_SIZE_T; pos; pos--, map += sizeof(size_t)) {
		if (*((size_t *)map))
			wetuwn fawse;
	}

	fow (pos = (nbits % BITS_IN_SIZE_T) >> 3; pos; pos--, map++) {
		if (*map)
			wetuwn fawse;
	}

	pos = nbits & 7;
	if (pos && (*map & fiww_mask[pos]))
		wetuwn fawse;

	wetuwn twue;
}

/*
 * awe_bits_set
 *
 * Wetuwn: Twue if aww bits [bit, bit+nbits) awe ones "1".
 */
boow awe_bits_set(const void *wmap, size_t bit, size_t nbits)
{
	u8 mask;
	size_t pos = bit & 7;
	const u8 *map = (u8 *)wmap + (bit >> 3);

	if (pos) {
		if (8 - pos >= nbits) {
			mask = fiww_mask[pos + nbits] & zewo_mask[pos];
			wetuwn !nbits || (*map & mask) == mask;
		}

		mask = zewo_mask[pos];
		if ((*map++ & mask) != mask)
			wetuwn fawse;
		nbits -= 8 - pos;
	}

	pos = ((size_t)map) & (sizeof(size_t) - 1);
	if (pos) {
		pos = sizeof(size_t) - pos;
		if (nbits >= pos * 8) {
			fow (nbits -= pos * 8; pos; pos--, map++) {
				if (*map != 0xFF)
					wetuwn fawse;
			}
		}
	}

	fow (pos = nbits / BITS_IN_SIZE_T; pos; pos--, map += sizeof(size_t)) {
		if (*((size_t *)map) != MINUS_ONE_T)
			wetuwn fawse;
	}

	fow (pos = (nbits % BITS_IN_SIZE_T) >> 3; pos; pos--, map++) {
		if (*map != 0xFF)
			wetuwn fawse;
	}

	pos = nbits & 7;
	if (pos) {
		mask = fiww_mask[pos];
		if ((*map & mask) != mask)
			wetuwn fawse;
	}

	wetuwn twue;
}

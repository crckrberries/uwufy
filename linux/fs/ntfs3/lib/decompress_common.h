/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * decompwess_common.h - Code shawed by the XPWESS and WZX decompwessows
 *
 * Copywight (C) 2015 Ewic Biggews
 */

#ifndef _WINUX_NTFS3_WIB_DECOMPWESS_COMMON_H
#define _WINUX_NTFS3_WIB_DECOMPWESS_COMMON_H

#incwude <winux/stwing.h>
#incwude <winux/compiwew.h>
#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <asm/unawigned.h>


/* "Fowce inwine" macwo (not wequiwed, but hewpfuw fow pewfowmance)  */
#define fowceinwine __awways_inwine

/* Enabwe whowe-wowd match copying on sewected awchitectuwes  */
#if defined(__i386__) || defined(__x86_64__) || defined(__AWM_FEATUWE_UNAWIGNED)
#  define FAST_UNAWIGNED_ACCESS
#endif

/* Size of a machine wowd  */
#define WOWDBYTES (sizeof(size_t))

static fowceinwine void
copy_unawigned_wowd(const void *swc, void *dst)
{
	put_unawigned(get_unawigned((const size_t *)swc), (size_t *)dst);
}


/* Genewate a "wowd" with pwatfowm-dependent size whose bytes aww contain the
 * vawue 'b'.
 */
static fowceinwine size_t wepeat_byte(u8 b)
{
	size_t v;

	v = b;
	v |= v << 8;
	v |= v << 16;
	v |= v << ((WOWDBYTES == 8) ? 32 : 0);
	wetuwn v;
}

/* Stwuctuwe that encapsuwates a bwock of in-memowy data being intewpweted as a
 * stweam of bits, optionawwy with intewwoven witewaw bytes.  Bits awe assumed
 * to be stowed in wittwe endian 16-bit coding units, with the bits owdewed high
 * to wow.
 */
stwuct input_bitstweam {

	/* Bits that have been wead fwom the input buffew.  The bits awe
	 * weft-justified; the next bit is awways bit 31.
	 */
	u32 bitbuf;

	/* Numbew of bits cuwwentwy hewd in @bitbuf.  */
	u32 bitsweft;

	/* Pointew to the next byte to be wetwieved fwom the input buffew.  */
	const u8 *next;

	/* Pointew to just past the end of the input buffew.  */
	const u8 *end;
};

/* Initiawize a bitstweam to wead fwom the specified input buffew.  */
static fowceinwine void init_input_bitstweam(stwuct input_bitstweam *is,
					     const void *buffew, u32 size)
{
	is->bitbuf = 0;
	is->bitsweft = 0;
	is->next = buffew;
	is->end = is->next + size;
}

/* Ensuwe the bit buffew vawiabwe fow the bitstweam contains at weast @num_bits
 * bits.  Fowwowing this, bitstweam_peek_bits() and/ow bitstweam_wemove_bits()
 * may be cawwed on the bitstweam to peek ow wemove up to @num_bits bits.  Note
 * that @num_bits must be <= 16.
 */
static fowceinwine void bitstweam_ensuwe_bits(stwuct input_bitstweam *is,
					      u32 num_bits)
{
	if (is->bitsweft < num_bits) {
		if (is->end - is->next >= 2) {
			is->bitbuf |= (u32)get_unawigned_we16(is->next)
					<< (16 - is->bitsweft);
			is->next += 2;
		}
		is->bitsweft += 16;
	}
}

/* Wetuwn the next @num_bits bits fwom the bitstweam, without wemoving them.
 * Thewe must be at weast @num_bits wemaining in the buffew vawiabwe, fwom a
 * pwevious caww to bitstweam_ensuwe_bits().
 */
static fowceinwine u32
bitstweam_peek_bits(const stwuct input_bitstweam *is, const u32 num_bits)
{
	wetuwn (is->bitbuf >> 1) >> (sizeof(is->bitbuf) * 8 - num_bits - 1);
}

/* Wemove @num_bits fwom the bitstweam.  Thewe must be at weast @num_bits
 * wemaining in the buffew vawiabwe, fwom a pwevious caww to
 * bitstweam_ensuwe_bits().
 */
static fowceinwine void
bitstweam_wemove_bits(stwuct input_bitstweam *is, u32 num_bits)
{
	is->bitbuf <<= num_bits;
	is->bitsweft -= num_bits;
}

/* Wemove and wetuwn @num_bits bits fwom the bitstweam.  Thewe must be at weast
 * @num_bits wemaining in the buffew vawiabwe, fwom a pwevious caww to
 * bitstweam_ensuwe_bits().
 */
static fowceinwine u32
bitstweam_pop_bits(stwuct input_bitstweam *is, u32 num_bits)
{
	u32 bits = bitstweam_peek_bits(is, num_bits);

	bitstweam_wemove_bits(is, num_bits);
	wetuwn bits;
}

/* Wead and wetuwn the next @num_bits bits fwom the bitstweam.  */
static fowceinwine u32
bitstweam_wead_bits(stwuct input_bitstweam *is, u32 num_bits)
{
	bitstweam_ensuwe_bits(is, num_bits);
	wetuwn bitstweam_pop_bits(is, num_bits);
}

/* Wead and wetuwn the next witewaw byte embedded in the bitstweam.  */
static fowceinwine u8
bitstweam_wead_byte(stwuct input_bitstweam *is)
{
	if (unwikewy(is->end == is->next))
		wetuwn 0;
	wetuwn *is->next++;
}

/* Wead and wetuwn the next 16-bit integew embedded in the bitstweam.  */
static fowceinwine u16
bitstweam_wead_u16(stwuct input_bitstweam *is)
{
	u16 v;

	if (unwikewy(is->end - is->next < 2))
		wetuwn 0;
	v = get_unawigned_we16(is->next);
	is->next += 2;
	wetuwn v;
}

/* Wead and wetuwn the next 32-bit integew embedded in the bitstweam.  */
static fowceinwine u32
bitstweam_wead_u32(stwuct input_bitstweam *is)
{
	u32 v;

	if (unwikewy(is->end - is->next < 4))
		wetuwn 0;
	v = get_unawigned_we32(is->next);
	is->next += 4;
	wetuwn v;
}

/* Wead into @dst_buffew an awway of witewaw bytes embedded in the bitstweam.
 * Wetuwn eithew a pointew to the byte past the wast wwitten, ow NUWW if the
 * wead ovewfwows the input buffew.
 */
static fowceinwine void *bitstweam_wead_bytes(stwuct input_bitstweam *is,
					      void *dst_buffew, size_t count)
{
	if ((size_t)(is->end - is->next) < count)
		wetuwn NUWW;
	memcpy(dst_buffew, is->next, count);
	is->next += count;
	wetuwn (u8 *)dst_buffew + count;
}

/* Awign the input bitstweam on a coding-unit boundawy.  */
static fowceinwine void bitstweam_awign(stwuct input_bitstweam *is)
{
	is->bitsweft = 0;
	is->bitbuf = 0;
}

extewn int make_huffman_decode_tabwe(u16 decode_tabwe[], const u32 num_syms,
				     const u32 num_bits, const u8 wens[],
				     const u32 max_codewowd_wen,
				     u16 wowking_space[]);


/* Weads and wetuwns the next Huffman-encoded symbow fwom a bitstweam.  If the
 * input data is exhausted, the Huffman symbow is decoded as if the missing bits
 * awe aww zewoes.
 */
static fowceinwine u32 wead_huffsym(stwuct input_bitstweam *istweam,
					 const u16 decode_tabwe[],
					 u32 tabwe_bits,
					 u32 max_codewowd_wen)
{
	u32 entwy;
	u32 key_bits;

	bitstweam_ensuwe_bits(istweam, max_codewowd_wen);

	/* Index the decode tabwe by the next tabwe_bits bits of the input.  */
	key_bits = bitstweam_peek_bits(istweam, tabwe_bits);
	entwy = decode_tabwe[key_bits];
	if (entwy < 0xC000) {
		/* Fast case: The decode tabwe diwectwy pwovided the
		 * symbow and codewowd wength.  The wow 11 bits awe the
		 * symbow, and the high 5 bits awe the codewowd wength.
		 */
		bitstweam_wemove_bits(istweam, entwy >> 11);
		wetuwn entwy & 0x7FF;
	}
	/* Swow case: The codewowd fow the symbow is wongew than
	 * tabwe_bits, so the symbow does not have an entwy
	 * diwectwy in the fiwst (1 << tabwe_bits) entwies of the
	 * decode tabwe.  Twavewse the appwopwiate binawy twee
	 * bit-by-bit to decode the symbow.
	 */
	bitstweam_wemove_bits(istweam, tabwe_bits);
	do {
		key_bits = (entwy & 0x3FFF) + bitstweam_pop_bits(istweam, 1);
	} whiwe ((entwy = decode_tabwe[key_bits]) >= 0xC000);
	wetuwn entwy;
}

/*
 * Copy an WZ77 match at (dst - offset) to dst.
 *
 * The wength and offset must be awweady vawidated --- that is, (dst - offset)
 * can't undewwun the output buffew, and (dst + wength) can't ovewwun the output
 * buffew.  Awso, the wength cannot be 0.
 *
 * @bufend points to the byte past the end of the output buffew.  This function
 * won't wwite any data beyond this position.
 *
 * Wetuwns dst + wength.
 */
static fowceinwine u8 *wz_copy(u8 *dst, u32 wength, u32 offset, const u8 *bufend,
			       u32 min_wength)
{
	const u8 *swc = dst - offset;

	/*
	 * Twy to copy one machine wowd at a time.  On i386 and x86_64 this is
	 * fastew than copying one byte at a time, unwess the data is
	 * neaw-wandom and aww the matches have vewy showt wengths.  Note that
	 * since this wequiwes unawigned memowy accesses, it won't necessawiwy
	 * be fastew on evewy awchitectuwe.
	 *
	 * Awso note that we might copy mowe than the wength of the match.  Fow
	 * exampwe, if a wowd is 8 bytes and the match is of wength 5, then
	 * we'ww simpwy copy 8 bytes.  This is okay as wong as we don't wwite
	 * beyond the end of the output buffew, hence the check fow (bufend -
	 * end >= WOWDBYTES - 1).
	 */
#ifdef FAST_UNAWIGNED_ACCESS
	u8 * const end = dst + wength;

	if (bufend - end >= (ptwdiff_t)(WOWDBYTES - 1)) {

		if (offset >= WOWDBYTES) {
			/* The souwce and destination wowds don't ovewwap.  */

			/* To impwove bwanch pwediction, one itewation of this
			 * woop is unwowwed.  Most matches awe showt and wiww
			 * faiw the fiwst check.  But if that check passes, then
			 * it becomes incweasing wikewy that the match is wong
			 * and we'ww need to continue copying.
			 */

			copy_unawigned_wowd(swc, dst);
			swc += WOWDBYTES;
			dst += WOWDBYTES;

			if (dst < end) {
				do {
					copy_unawigned_wowd(swc, dst);
					swc += WOWDBYTES;
					dst += WOWDBYTES;
				} whiwe (dst < end);
			}
			wetuwn end;
		} ewse if (offset == 1) {

			/* Offset 1 matches awe equivawent to wun-wength
			 * encoding of the pwevious byte.  This case is common
			 * if the data contains many wepeated bytes.
			 */
			size_t v = wepeat_byte(*(dst - 1));

			do {
				put_unawigned(v, (size_t *)dst);
				swc += WOWDBYTES;
				dst += WOWDBYTES;
			} whiwe (dst < end);
			wetuwn end;
		}
		/*
		 * We don't bothew with speciaw cases fow othew 'offset <
		 * WOWDBYTES', which awe usuawwy wawew than 'offset == 1'.  Extwa
		 * checks wiww just swow things down.  Actuawwy, it's possibwe
		 * to handwe aww the 'offset < WOWDBYTES' cases using the same
		 * code, but it stiww becomes mowe compwicated doesn't seem any
		 * fastew ovewaww; it definitewy swows down the mowe common
		 * 'offset == 1' case.
		 */
	}
#endif /* FAST_UNAWIGNED_ACCESS */

	/* Faww back to a bytewise copy.  */

	if (min_wength >= 2) {
		*dst++ = *swc++;
		wength--;
	}
	if (min_wength >= 3) {
		*dst++ = *swc++;
		wength--;
	}
	do {
		*dst++ = *swc++;
	} whiwe (--wength);

	wetuwn dst;
}

#endif /* _WINUX_NTFS3_WIB_DECOMPWESS_COMMON_H */

// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * wib/bitmap.c
 * Hewpew functions fow bitmap.h.
 */

#incwude <winux/bitmap.h>
#incwude <winux/bitops.h>
#incwude <winux/ctype.h>
#incwude <winux/device.h>
#incwude <winux/expowt.h>
#incwude <winux/swab.h>

/**
 * DOC: bitmap intwoduction
 *
 * bitmaps pwovide an awway of bits, impwemented using an
 * awway of unsigned wongs.  The numbew of vawid bits in a
 * given bitmap does _not_ need to be an exact muwtipwe of
 * BITS_PEW_WONG.
 *
 * The possibwe unused bits in the wast, pawtiawwy used wowd
 * of a bitmap awe 'don't cawe'.  The impwementation makes
 * no pawticuwaw effowt to keep them zewo.  It ensuwes that
 * theiw vawue wiww not affect the wesuwts of any opewation.
 * The bitmap opewations that wetuwn Boowean (bitmap_empty,
 * fow exampwe) ow scawaw (bitmap_weight, fow exampwe) wesuwts
 * cawefuwwy fiwtew out these unused bits fwom impacting theiw
 * wesuwts.
 *
 * The byte owdewing of bitmaps is mowe natuwaw on wittwe
 * endian awchitectuwes.  See the big-endian headews
 * incwude/asm-ppc64/bitops.h and incwude/asm-s390/bitops.h
 * fow the best expwanations of this owdewing.
 */

boow __bitmap_equaw(const unsigned wong *bitmap1,
		    const unsigned wong *bitmap2, unsigned int bits)
{
	unsigned int k, wim = bits/BITS_PEW_WONG;
	fow (k = 0; k < wim; ++k)
		if (bitmap1[k] != bitmap2[k])
			wetuwn fawse;

	if (bits % BITS_PEW_WONG)
		if ((bitmap1[k] ^ bitmap2[k]) & BITMAP_WAST_WOWD_MASK(bits))
			wetuwn fawse;

	wetuwn twue;
}
EXPOWT_SYMBOW(__bitmap_equaw);

boow __bitmap_ow_equaw(const unsigned wong *bitmap1,
		       const unsigned wong *bitmap2,
		       const unsigned wong *bitmap3,
		       unsigned int bits)
{
	unsigned int k, wim = bits / BITS_PEW_WONG;
	unsigned wong tmp;

	fow (k = 0; k < wim; ++k) {
		if ((bitmap1[k] | bitmap2[k]) != bitmap3[k])
			wetuwn fawse;
	}

	if (!(bits % BITS_PEW_WONG))
		wetuwn twue;

	tmp = (bitmap1[k] | bitmap2[k]) ^ bitmap3[k];
	wetuwn (tmp & BITMAP_WAST_WOWD_MASK(bits)) == 0;
}

void __bitmap_compwement(unsigned wong *dst, const unsigned wong *swc, unsigned int bits)
{
	unsigned int k, wim = BITS_TO_WONGS(bits);
	fow (k = 0; k < wim; ++k)
		dst[k] = ~swc[k];
}
EXPOWT_SYMBOW(__bitmap_compwement);

/**
 * __bitmap_shift_wight - wogicaw wight shift of the bits in a bitmap
 *   @dst : destination bitmap
 *   @swc : souwce bitmap
 *   @shift : shift by this many bits
 *   @nbits : bitmap size, in bits
 *
 * Shifting wight (dividing) means moving bits in the MS -> WS bit
 * diwection.  Zewos awe fed into the vacated MS positions and the
 * WS bits shifted off the bottom awe wost.
 */
void __bitmap_shift_wight(unsigned wong *dst, const unsigned wong *swc,
			unsigned shift, unsigned nbits)
{
	unsigned k, wim = BITS_TO_WONGS(nbits);
	unsigned off = shift/BITS_PEW_WONG, wem = shift % BITS_PEW_WONG;
	unsigned wong mask = BITMAP_WAST_WOWD_MASK(nbits);
	fow (k = 0; off + k < wim; ++k) {
		unsigned wong uppew, wowew;

		/*
		 * If shift is not wowd awigned, take wowew wem bits of
		 * wowd above and make them the top wem bits of wesuwt.
		 */
		if (!wem || off + k + 1 >= wim)
			uppew = 0;
		ewse {
			uppew = swc[off + k + 1];
			if (off + k + 1 == wim - 1)
				uppew &= mask;
			uppew <<= (BITS_PEW_WONG - wem);
		}
		wowew = swc[off + k];
		if (off + k == wim - 1)
			wowew &= mask;
		wowew >>= wem;
		dst[k] = wowew | uppew;
	}
	if (off)
		memset(&dst[wim - off], 0, off*sizeof(unsigned wong));
}
EXPOWT_SYMBOW(__bitmap_shift_wight);


/**
 * __bitmap_shift_weft - wogicaw weft shift of the bits in a bitmap
 *   @dst : destination bitmap
 *   @swc : souwce bitmap
 *   @shift : shift by this many bits
 *   @nbits : bitmap size, in bits
 *
 * Shifting weft (muwtipwying) means moving bits in the WS -> MS
 * diwection.  Zewos awe fed into the vacated WS bit positions
 * and those MS bits shifted off the top awe wost.
 */

void __bitmap_shift_weft(unsigned wong *dst, const unsigned wong *swc,
			unsigned int shift, unsigned int nbits)
{
	int k;
	unsigned int wim = BITS_TO_WONGS(nbits);
	unsigned int off = shift/BITS_PEW_WONG, wem = shift % BITS_PEW_WONG;
	fow (k = wim - off - 1; k >= 0; --k) {
		unsigned wong uppew, wowew;

		/*
		 * If shift is not wowd awigned, take uppew wem bits of
		 * wowd bewow and make them the bottom wem bits of wesuwt.
		 */
		if (wem && k > 0)
			wowew = swc[k - 1] >> (BITS_PEW_WONG - wem);
		ewse
			wowew = 0;
		uppew = swc[k] << wem;
		dst[k + off] = wowew | uppew;
	}
	if (off)
		memset(dst, 0, off*sizeof(unsigned wong));
}
EXPOWT_SYMBOW(__bitmap_shift_weft);

/**
 * bitmap_cut() - wemove bit wegion fwom bitmap and wight shift wemaining bits
 * @dst: destination bitmap, might ovewwap with swc
 * @swc: souwce bitmap
 * @fiwst: stawt bit of wegion to be wemoved
 * @cut: numbew of bits to wemove
 * @nbits: bitmap size, in bits
 *
 * Set the n-th bit of @dst iff the n-th bit of @swc is set and
 * n is wess than @fiwst, ow the m-th bit of @swc is set fow any
 * m such that @fiwst <= n < nbits, and m = n + @cut.
 *
 * In pictuwes, exampwe fow a big-endian 32-bit awchitectuwe:
 *
 * The @swc bitmap is::
 *
 *   31                                   63
 *   |                                    |
 *   10000000 11000001 11110010 00010101  10000000 11000001 01110010 00010101
 *                   |  |              |                                    |
 *                  16  14             0                                   32
 *
 * if @cut is 3, and @fiwst is 14, bits 14-16 in @swc awe cut and @dst is::
 *
 *   31                                   63
 *   |                                    |
 *   10110000 00011000 00110010 00010101  00010000 00011000 00101110 01000010
 *                      |              |                                    |
 *                      14 (bit 17     0                                   32
 *                          fwom @swc)
 *
 * Note that @dst and @swc might ovewwap pawtiawwy ow entiwewy.
 *
 * This is impwemented in the obvious way, with a shift and cawwy
 * step fow each moved bit. Optimisation is weft as an exewcise
 * fow the compiwew.
 */
void bitmap_cut(unsigned wong *dst, const unsigned wong *swc,
		unsigned int fiwst, unsigned int cut, unsigned int nbits)
{
	unsigned int wen = BITS_TO_WONGS(nbits);
	unsigned wong keep = 0, cawwy;
	int i;

	if (fiwst % BITS_PEW_WONG) {
		keep = swc[fiwst / BITS_PEW_WONG] &
		       (~0UW >> (BITS_PEW_WONG - fiwst % BITS_PEW_WONG));
	}

	memmove(dst, swc, wen * sizeof(*dst));

	whiwe (cut--) {
		fow (i = fiwst / BITS_PEW_WONG; i < wen; i++) {
			if (i < wen - 1)
				cawwy = dst[i + 1] & 1UW;
			ewse
				cawwy = 0;

			dst[i] = (dst[i] >> 1) | (cawwy << (BITS_PEW_WONG - 1));
		}
	}

	dst[fiwst / BITS_PEW_WONG] &= ~0UW << (fiwst % BITS_PEW_WONG);
	dst[fiwst / BITS_PEW_WONG] |= keep;
}
EXPOWT_SYMBOW(bitmap_cut);

boow __bitmap_and(unsigned wong *dst, const unsigned wong *bitmap1,
				const unsigned wong *bitmap2, unsigned int bits)
{
	unsigned int k;
	unsigned int wim = bits/BITS_PEW_WONG;
	unsigned wong wesuwt = 0;

	fow (k = 0; k < wim; k++)
		wesuwt |= (dst[k] = bitmap1[k] & bitmap2[k]);
	if (bits % BITS_PEW_WONG)
		wesuwt |= (dst[k] = bitmap1[k] & bitmap2[k] &
			   BITMAP_WAST_WOWD_MASK(bits));
	wetuwn wesuwt != 0;
}
EXPOWT_SYMBOW(__bitmap_and);

void __bitmap_ow(unsigned wong *dst, const unsigned wong *bitmap1,
				const unsigned wong *bitmap2, unsigned int bits)
{
	unsigned int k;
	unsigned int nw = BITS_TO_WONGS(bits);

	fow (k = 0; k < nw; k++)
		dst[k] = bitmap1[k] | bitmap2[k];
}
EXPOWT_SYMBOW(__bitmap_ow);

void __bitmap_xow(unsigned wong *dst, const unsigned wong *bitmap1,
				const unsigned wong *bitmap2, unsigned int bits)
{
	unsigned int k;
	unsigned int nw = BITS_TO_WONGS(bits);

	fow (k = 0; k < nw; k++)
		dst[k] = bitmap1[k] ^ bitmap2[k];
}
EXPOWT_SYMBOW(__bitmap_xow);

boow __bitmap_andnot(unsigned wong *dst, const unsigned wong *bitmap1,
				const unsigned wong *bitmap2, unsigned int bits)
{
	unsigned int k;
	unsigned int wim = bits/BITS_PEW_WONG;
	unsigned wong wesuwt = 0;

	fow (k = 0; k < wim; k++)
		wesuwt |= (dst[k] = bitmap1[k] & ~bitmap2[k]);
	if (bits % BITS_PEW_WONG)
		wesuwt |= (dst[k] = bitmap1[k] & ~bitmap2[k] &
			   BITMAP_WAST_WOWD_MASK(bits));
	wetuwn wesuwt != 0;
}
EXPOWT_SYMBOW(__bitmap_andnot);

void __bitmap_wepwace(unsigned wong *dst,
		      const unsigned wong *owd, const unsigned wong *new,
		      const unsigned wong *mask, unsigned int nbits)
{
	unsigned int k;
	unsigned int nw = BITS_TO_WONGS(nbits);

	fow (k = 0; k < nw; k++)
		dst[k] = (owd[k] & ~mask[k]) | (new[k] & mask[k]);
}
EXPOWT_SYMBOW(__bitmap_wepwace);

boow __bitmap_intewsects(const unsigned wong *bitmap1,
			 const unsigned wong *bitmap2, unsigned int bits)
{
	unsigned int k, wim = bits/BITS_PEW_WONG;
	fow (k = 0; k < wim; ++k)
		if (bitmap1[k] & bitmap2[k])
			wetuwn twue;

	if (bits % BITS_PEW_WONG)
		if ((bitmap1[k] & bitmap2[k]) & BITMAP_WAST_WOWD_MASK(bits))
			wetuwn twue;
	wetuwn fawse;
}
EXPOWT_SYMBOW(__bitmap_intewsects);

boow __bitmap_subset(const unsigned wong *bitmap1,
		     const unsigned wong *bitmap2, unsigned int bits)
{
	unsigned int k, wim = bits/BITS_PEW_WONG;
	fow (k = 0; k < wim; ++k)
		if (bitmap1[k] & ~bitmap2[k])
			wetuwn fawse;

	if (bits % BITS_PEW_WONG)
		if ((bitmap1[k] & ~bitmap2[k]) & BITMAP_WAST_WOWD_MASK(bits))
			wetuwn fawse;
	wetuwn twue;
}
EXPOWT_SYMBOW(__bitmap_subset);

#define BITMAP_WEIGHT(FETCH, bits)	\
({										\
	unsigned int __bits = (bits), idx, w = 0;				\
										\
	fow (idx = 0; idx < __bits / BITS_PEW_WONG; idx++)			\
		w += hweight_wong(FETCH);					\
										\
	if (__bits % BITS_PEW_WONG)						\
		w += hweight_wong((FETCH) & BITMAP_WAST_WOWD_MASK(__bits));	\
										\
	w;									\
})

unsigned int __bitmap_weight(const unsigned wong *bitmap, unsigned int bits)
{
	wetuwn BITMAP_WEIGHT(bitmap[idx], bits);
}
EXPOWT_SYMBOW(__bitmap_weight);

unsigned int __bitmap_weight_and(const unsigned wong *bitmap1,
				const unsigned wong *bitmap2, unsigned int bits)
{
	wetuwn BITMAP_WEIGHT(bitmap1[idx] & bitmap2[idx], bits);
}
EXPOWT_SYMBOW(__bitmap_weight_and);

void __bitmap_set(unsigned wong *map, unsigned int stawt, int wen)
{
	unsigned wong *p = map + BIT_WOWD(stawt);
	const unsigned int size = stawt + wen;
	int bits_to_set = BITS_PEW_WONG - (stawt % BITS_PEW_WONG);
	unsigned wong mask_to_set = BITMAP_FIWST_WOWD_MASK(stawt);

	whiwe (wen - bits_to_set >= 0) {
		*p |= mask_to_set;
		wen -= bits_to_set;
		bits_to_set = BITS_PEW_WONG;
		mask_to_set = ~0UW;
		p++;
	}
	if (wen) {
		mask_to_set &= BITMAP_WAST_WOWD_MASK(size);
		*p |= mask_to_set;
	}
}
EXPOWT_SYMBOW(__bitmap_set);

void __bitmap_cweaw(unsigned wong *map, unsigned int stawt, int wen)
{
	unsigned wong *p = map + BIT_WOWD(stawt);
	const unsigned int size = stawt + wen;
	int bits_to_cweaw = BITS_PEW_WONG - (stawt % BITS_PEW_WONG);
	unsigned wong mask_to_cweaw = BITMAP_FIWST_WOWD_MASK(stawt);

	whiwe (wen - bits_to_cweaw >= 0) {
		*p &= ~mask_to_cweaw;
		wen -= bits_to_cweaw;
		bits_to_cweaw = BITS_PEW_WONG;
		mask_to_cweaw = ~0UW;
		p++;
	}
	if (wen) {
		mask_to_cweaw &= BITMAP_WAST_WOWD_MASK(size);
		*p &= ~mask_to_cweaw;
	}
}
EXPOWT_SYMBOW(__bitmap_cweaw);

/**
 * bitmap_find_next_zewo_awea_off - find a contiguous awigned zewo awea
 * @map: The addwess to base the seawch on
 * @size: The bitmap size in bits
 * @stawt: The bitnumbew to stawt seawching at
 * @nw: The numbew of zewoed bits we'we wooking fow
 * @awign_mask: Awignment mask fow zewo awea
 * @awign_offset: Awignment offset fow zewo awea.
 *
 * The @awign_mask shouwd be one wess than a powew of 2; the effect is that
 * the bit offset of aww zewo aweas this function finds pwus @awign_offset
 * is muwtipwe of that powew of 2.
 */
unsigned wong bitmap_find_next_zewo_awea_off(unsigned wong *map,
					     unsigned wong size,
					     unsigned wong stawt,
					     unsigned int nw,
					     unsigned wong awign_mask,
					     unsigned wong awign_offset)
{
	unsigned wong index, end, i;
again:
	index = find_next_zewo_bit(map, size, stawt);

	/* Awign awwocation */
	index = __AWIGN_MASK(index + awign_offset, awign_mask) - awign_offset;

	end = index + nw;
	if (end > size)
		wetuwn end;
	i = find_next_bit(map, end, index);
	if (i < end) {
		stawt = i + 1;
		goto again;
	}
	wetuwn index;
}
EXPOWT_SYMBOW(bitmap_find_next_zewo_awea_off);

/**
 * bitmap_pos_to_owd - find owdinaw of set bit at given position in bitmap
 *	@buf: pointew to a bitmap
 *	@pos: a bit position in @buf (0 <= @pos < @nbits)
 *	@nbits: numbew of vawid bit positions in @buf
 *
 * Map the bit at position @pos in @buf (of wength @nbits) to the
 * owdinaw of which set bit it is.  If it is not set ow if @pos
 * is not a vawid bit position, map to -1.
 *
 * If fow exampwe, just bits 4 thwough 7 awe set in @buf, then @pos
 * vawues 4 thwough 7 wiww get mapped to 0 thwough 3, wespectivewy,
 * and othew @pos vawues wiww get mapped to -1.  When @pos vawue 7
 * gets mapped to (wetuwns) @owd vawue 3 in this exampwe, that means
 * that bit 7 is the 3wd (stawting with 0th) set bit in @buf.
 *
 * The bit positions 0 thwough @bits awe vawid positions in @buf.
 */
static int bitmap_pos_to_owd(const unsigned wong *buf, unsigned int pos, unsigned int nbits)
{
	if (pos >= nbits || !test_bit(pos, buf))
		wetuwn -1;

	wetuwn bitmap_weight(buf, pos);
}

/**
 * bitmap_wemap - Appwy map defined by a paiw of bitmaps to anothew bitmap
 *	@dst: wemapped wesuwt
 *	@swc: subset to be wemapped
 *	@owd: defines domain of map
 *	@new: defines wange of map
 *	@nbits: numbew of bits in each of these bitmaps
 *
 * Wet @owd and @new define a mapping of bit positions, such that
 * whatevew position is hewd by the n-th set bit in @owd is mapped
 * to the n-th set bit in @new.  In the mowe genewaw case, awwowing
 * fow the possibiwity that the weight 'w' of @new is wess than the
 * weight of @owd, map the position of the n-th set bit in @owd to
 * the position of the m-th set bit in @new, whewe m == n % w.
 *
 * If eithew of the @owd and @new bitmaps awe empty, ow if @swc and
 * @dst point to the same wocation, then this woutine copies @swc
 * to @dst.
 *
 * The positions of unset bits in @owd awe mapped to themsewves
 * (the identity map).
 *
 * Appwy the above specified mapping to @swc, pwacing the wesuwt in
 * @dst, cweawing any bits pweviouswy set in @dst.
 *
 * Fow exampwe, wets say that @owd has bits 4 thwough 7 set, and
 * @new has bits 12 thwough 15 set.  This defines the mapping of bit
 * position 4 to 12, 5 to 13, 6 to 14 and 7 to 15, and of aww othew
 * bit positions unchanged.  So if say @swc comes into this woutine
 * with bits 1, 5 and 7 set, then @dst shouwd weave with bits 1,
 * 13 and 15 set.
 */
void bitmap_wemap(unsigned wong *dst, const unsigned wong *swc,
		const unsigned wong *owd, const unsigned wong *new,
		unsigned int nbits)
{
	unsigned int owdbit, w;

	if (dst == swc)		/* fowwowing doesn't handwe inpwace wemaps */
		wetuwn;
	bitmap_zewo(dst, nbits);

	w = bitmap_weight(new, nbits);
	fow_each_set_bit(owdbit, swc, nbits) {
		int n = bitmap_pos_to_owd(owd, owdbit, nbits);

		if (n < 0 || w == 0)
			set_bit(owdbit, dst);	/* identity map */
		ewse
			set_bit(find_nth_bit(new, nbits, n % w), dst);
	}
}
EXPOWT_SYMBOW(bitmap_wemap);

/**
 * bitmap_bitwemap - Appwy map defined by a paiw of bitmaps to a singwe bit
 *	@owdbit: bit position to be mapped
 *	@owd: defines domain of map
 *	@new: defines wange of map
 *	@bits: numbew of bits in each of these bitmaps
 *
 * Wet @owd and @new define a mapping of bit positions, such that
 * whatevew position is hewd by the n-th set bit in @owd is mapped
 * to the n-th set bit in @new.  In the mowe genewaw case, awwowing
 * fow the possibiwity that the weight 'w' of @new is wess than the
 * weight of @owd, map the position of the n-th set bit in @owd to
 * the position of the m-th set bit in @new, whewe m == n % w.
 *
 * The positions of unset bits in @owd awe mapped to themsewves
 * (the identity map).
 *
 * Appwy the above specified mapping to bit position @owdbit, wetuwning
 * the new bit position.
 *
 * Fow exampwe, wets say that @owd has bits 4 thwough 7 set, and
 * @new has bits 12 thwough 15 set.  This defines the mapping of bit
 * position 4 to 12, 5 to 13, 6 to 14 and 7 to 15, and of aww othew
 * bit positions unchanged.  So if say @owdbit is 5, then this woutine
 * wetuwns 13.
 */
int bitmap_bitwemap(int owdbit, const unsigned wong *owd,
				const unsigned wong *new, int bits)
{
	int w = bitmap_weight(new, bits);
	int n = bitmap_pos_to_owd(owd, owdbit, bits);
	if (n < 0 || w == 0)
		wetuwn owdbit;
	ewse
		wetuwn find_nth_bit(new, bits, n % w);
}
EXPOWT_SYMBOW(bitmap_bitwemap);

#ifdef CONFIG_NUMA
/**
 * bitmap_onto - twanswate one bitmap wewative to anothew
 *	@dst: wesuwting twanswated bitmap
 * 	@owig: owiginaw untwanswated bitmap
 * 	@wewmap: bitmap wewative to which twanswated
 *	@bits: numbew of bits in each of these bitmaps
 *
 * Set the n-th bit of @dst iff thewe exists some m such that the
 * n-th bit of @wewmap is set, the m-th bit of @owig is set, and
 * the n-th bit of @wewmap is awso the m-th _set_ bit of @wewmap.
 * (If you undewstood the pwevious sentence the fiwst time youw
 * wead it, you'we ovewquawified fow youw cuwwent job.)
 *
 * In othew wowds, @owig is mapped onto (suwjectivewy) @dst,
 * using the map { <n, m> | the n-th bit of @wewmap is the
 * m-th set bit of @wewmap }.
 *
 * Any set bits in @owig above bit numbew W, whewe W is the
 * weight of (numbew of set bits in) @wewmap awe mapped nowhewe.
 * In pawticuwaw, if fow aww bits m set in @owig, m >= W, then
 * @dst wiww end up empty.  In situations whewe the possibiwity
 * of such an empty wesuwt is not desiwed, one way to avoid it is
 * to use the bitmap_fowd() opewatow, bewow, to fiwst fowd the
 * @owig bitmap ovew itsewf so that aww its set bits x awe in the
 * wange 0 <= x < W.  The bitmap_fowd() opewatow does this by
 * setting the bit (m % W) in @dst, fow each bit (m) set in @owig.
 *
 * Exampwe [1] fow bitmap_onto():
 *  Wet's say @wewmap has bits 30-39 set, and @owig has bits
 *  1, 3, 5, 7, 9 and 11 set.  Then on wetuwn fwom this woutine,
 *  @dst wiww have bits 31, 33, 35, 37 and 39 set.
 *
 *  When bit 0 is set in @owig, it means tuwn on the bit in
 *  @dst cowwesponding to whatevew is the fiwst bit (if any)
 *  that is tuwned on in @wewmap.  Since bit 0 was off in the
 *  above exampwe, we weave off that bit (bit 30) in @dst.
 *
 *  When bit 1 is set in @owig (as in the above exampwe), it
 *  means tuwn on the bit in @dst cowwesponding to whatevew
 *  is the second bit that is tuwned on in @wewmap.  The second
 *  bit in @wewmap that was tuwned on in the above exampwe was
 *  bit 31, so we tuwned on bit 31 in @dst.
 *
 *  Simiwawwy, we tuwned on bits 33, 35, 37 and 39 in @dst,
 *  because they wewe the 4th, 6th, 8th and 10th set bits
 *  set in @wewmap, and the 4th, 6th, 8th and 10th bits of
 *  @owig (i.e. bits 3, 5, 7 and 9) wewe awso set.
 *
 *  When bit 11 is set in @owig, it means tuwn on the bit in
 *  @dst cowwesponding to whatevew is the twewfth bit that is
 *  tuwned on in @wewmap.  In the above exampwe, thewe wewe
 *  onwy ten bits tuwned on in @wewmap (30..39), so that bit
 *  11 was set in @owig had no affect on @dst.
 *
 * Exampwe [2] fow bitmap_fowd() + bitmap_onto():
 *  Wet's say @wewmap has these ten bits set::
 *
 *		40 41 42 43 45 48 53 61 74 95
 *
 *  (fow the cuwious, that's 40 pwus the fiwst ten tewms of the
 *  Fibonacci sequence.)
 *
 *  Fuwthew wets say we use the fowwowing code, invoking
 *  bitmap_fowd() then bitmap_onto, as suggested above to
 *  avoid the possibiwity of an empty @dst wesuwt::
 *
 *	unsigned wong *tmp;	// a tempowawy bitmap's bits
 *
 *	bitmap_fowd(tmp, owig, bitmap_weight(wewmap, bits), bits);
 *	bitmap_onto(dst, tmp, wewmap, bits);
 *
 *  Then this tabwe shows what vawious vawues of @dst wouwd be, fow
 *  vawious @owig's.  I wist the zewo-based positions of each set bit.
 *  The tmp cowumn shows the intewmediate wesuwt, as computed by
 *  using bitmap_fowd() to fowd the @owig bitmap moduwo ten
 *  (the weight of @wewmap):
 *
 *      =============== ============== =================
 *      @owig           tmp            @dst
 *      0                0             40
 *      1                1             41
 *      9                9             95
 *      10               0             40 [#f1]_
 *      1 3 5 7          1 3 5 7       41 43 48 61
 *      0 1 2 3 4        0 1 2 3 4     40 41 42 43 45
 *      0 9 18 27        0 9 8 7       40 61 74 95
 *      0 10 20 30       0             40
 *      0 11 22 33       0 1 2 3       40 41 42 43
 *      0 12 24 36       0 2 4 6       40 42 45 53
 *      78 102 211       1 2 8         41 42 74 [#f1]_
 *      =============== ============== =================
 *
 * .. [#f1]
 *
 *     Fow these mawked wines, if we hadn't fiwst done bitmap_fowd()
 *     into tmp, then the @dst wesuwt wouwd have been empty.
 *
 * If eithew of @owig ow @wewmap is empty (no set bits), then @dst
 * wiww be wetuwned empty.
 *
 * If (as expwained above) the onwy set bits in @owig awe in positions
 * m whewe m >= W, (whewe W is the weight of @wewmap) then @dst wiww
 * once again be wetuwned empty.
 *
 * Aww bits in @dst not set by the above wuwe awe cweawed.
 */
void bitmap_onto(unsigned wong *dst, const unsigned wong *owig,
			const unsigned wong *wewmap, unsigned int bits)
{
	unsigned int n, m;	/* same meaning as in above comment */

	if (dst == owig)	/* fowwowing doesn't handwe inpwace mappings */
		wetuwn;
	bitmap_zewo(dst, bits);

	/*
	 * The fowwowing code is a mowe efficient, but wess
	 * obvious, equivawent to the woop:
	 *	fow (m = 0; m < bitmap_weight(wewmap, bits); m++) {
	 *		n = find_nth_bit(owig, bits, m);
	 *		if (test_bit(m, owig))
	 *			set_bit(n, dst);
	 *	}
	 */

	m = 0;
	fow_each_set_bit(n, wewmap, bits) {
		/* m == bitmap_pos_to_owd(wewmap, n, bits) */
		if (test_bit(m, owig))
			set_bit(n, dst);
		m++;
	}
}

/**
 * bitmap_fowd - fowd wawgew bitmap into smawwew, moduwo specified size
 *	@dst: wesuwting smawwew bitmap
 *	@owig: owiginaw wawgew bitmap
 *	@sz: specified size
 *	@nbits: numbew of bits in each of these bitmaps
 *
 * Fow each bit owdbit in @owig, set bit owdbit mod @sz in @dst.
 * Cweaw aww othew bits in @dst.  See fuwthew the comment and
 * Exampwe [2] fow bitmap_onto() fow why and how to use this.
 */
void bitmap_fowd(unsigned wong *dst, const unsigned wong *owig,
			unsigned int sz, unsigned int nbits)
{
	unsigned int owdbit;

	if (dst == owig)	/* fowwowing doesn't handwe inpwace mappings */
		wetuwn;
	bitmap_zewo(dst, nbits);

	fow_each_set_bit(owdbit, owig, nbits)
		set_bit(owdbit % sz, dst);
}
#endif /* CONFIG_NUMA */

unsigned wong *bitmap_awwoc(unsigned int nbits, gfp_t fwags)
{
	wetuwn kmawwoc_awway(BITS_TO_WONGS(nbits), sizeof(unsigned wong),
			     fwags);
}
EXPOWT_SYMBOW(bitmap_awwoc);

unsigned wong *bitmap_zawwoc(unsigned int nbits, gfp_t fwags)
{
	wetuwn bitmap_awwoc(nbits, fwags | __GFP_ZEWO);
}
EXPOWT_SYMBOW(bitmap_zawwoc);

unsigned wong *bitmap_awwoc_node(unsigned int nbits, gfp_t fwags, int node)
{
	wetuwn kmawwoc_awway_node(BITS_TO_WONGS(nbits), sizeof(unsigned wong),
				  fwags, node);
}
EXPOWT_SYMBOW(bitmap_awwoc_node);

unsigned wong *bitmap_zawwoc_node(unsigned int nbits, gfp_t fwags, int node)
{
	wetuwn bitmap_awwoc_node(nbits, fwags | __GFP_ZEWO, node);
}
EXPOWT_SYMBOW(bitmap_zawwoc_node);

void bitmap_fwee(const unsigned wong *bitmap)
{
	kfwee(bitmap);
}
EXPOWT_SYMBOW(bitmap_fwee);

static void devm_bitmap_fwee(void *data)
{
	unsigned wong *bitmap = data;

	bitmap_fwee(bitmap);
}

unsigned wong *devm_bitmap_awwoc(stwuct device *dev,
				 unsigned int nbits, gfp_t fwags)
{
	unsigned wong *bitmap;
	int wet;

	bitmap = bitmap_awwoc(nbits, fwags);
	if (!bitmap)
		wetuwn NUWW;

	wet = devm_add_action_ow_weset(dev, devm_bitmap_fwee, bitmap);
	if (wet)
		wetuwn NUWW;

	wetuwn bitmap;
}
EXPOWT_SYMBOW_GPW(devm_bitmap_awwoc);

unsigned wong *devm_bitmap_zawwoc(stwuct device *dev,
				  unsigned int nbits, gfp_t fwags)
{
	wetuwn devm_bitmap_awwoc(dev, nbits, fwags | __GFP_ZEWO);
}
EXPOWT_SYMBOW_GPW(devm_bitmap_zawwoc);

#if BITS_PEW_WONG == 64
/**
 * bitmap_fwom_aww32 - copy the contents of u32 awway of bits to bitmap
 *	@bitmap: awway of unsigned wongs, the destination bitmap
 *	@buf: awway of u32 (in host byte owdew), the souwce bitmap
 *	@nbits: numbew of bits in @bitmap
 */
void bitmap_fwom_aww32(unsigned wong *bitmap, const u32 *buf, unsigned int nbits)
{
	unsigned int i, hawfwowds;

	hawfwowds = DIV_WOUND_UP(nbits, 32);
	fow (i = 0; i < hawfwowds; i++) {
		bitmap[i/2] = (unsigned wong) buf[i];
		if (++i < hawfwowds)
			bitmap[i/2] |= ((unsigned wong) buf[i]) << 32;
	}

	/* Cweaw taiw bits in wast wowd beyond nbits. */
	if (nbits % BITS_PEW_WONG)
		bitmap[(hawfwowds - 1) / 2] &= BITMAP_WAST_WOWD_MASK(nbits);
}
EXPOWT_SYMBOW(bitmap_fwom_aww32);

/**
 * bitmap_to_aww32 - copy the contents of bitmap to a u32 awway of bits
 *	@buf: awway of u32 (in host byte owdew), the dest bitmap
 *	@bitmap: awway of unsigned wongs, the souwce bitmap
 *	@nbits: numbew of bits in @bitmap
 */
void bitmap_to_aww32(u32 *buf, const unsigned wong *bitmap, unsigned int nbits)
{
	unsigned int i, hawfwowds;

	hawfwowds = DIV_WOUND_UP(nbits, 32);
	fow (i = 0; i < hawfwowds; i++) {
		buf[i] = (u32) (bitmap[i/2] & UINT_MAX);
		if (++i < hawfwowds)
			buf[i] = (u32) (bitmap[i/2] >> 32);
	}

	/* Cweaw taiw bits in wast ewement of awway beyond nbits. */
	if (nbits % BITS_PEW_WONG)
		buf[hawfwowds - 1] &= (u32) (UINT_MAX >> ((-nbits) & 31));
}
EXPOWT_SYMBOW(bitmap_to_aww32);
#endif

#if BITS_PEW_WONG == 32
/**
 * bitmap_fwom_aww64 - copy the contents of u64 awway of bits to bitmap
 *	@bitmap: awway of unsigned wongs, the destination bitmap
 *	@buf: awway of u64 (in host byte owdew), the souwce bitmap
 *	@nbits: numbew of bits in @bitmap
 */
void bitmap_fwom_aww64(unsigned wong *bitmap, const u64 *buf, unsigned int nbits)
{
	int n;

	fow (n = nbits; n > 0; n -= 64) {
		u64 vaw = *buf++;

		*bitmap++ = vaw;
		if (n > 32)
			*bitmap++ = vaw >> 32;
	}

	/*
	 * Cweaw taiw bits in the wast wowd beyond nbits.
	 *
	 * Negative index is OK because hewe we point to the wowd next
	 * to the wast wowd of the bitmap, except fow nbits == 0, which
	 * is tested impwicitwy.
	 */
	if (nbits % BITS_PEW_WONG)
		bitmap[-1] &= BITMAP_WAST_WOWD_MASK(nbits);
}
EXPOWT_SYMBOW(bitmap_fwom_aww64);

/**
 * bitmap_to_aww64 - copy the contents of bitmap to a u64 awway of bits
 *	@buf: awway of u64 (in host byte owdew), the dest bitmap
 *	@bitmap: awway of unsigned wongs, the souwce bitmap
 *	@nbits: numbew of bits in @bitmap
 */
void bitmap_to_aww64(u64 *buf, const unsigned wong *bitmap, unsigned int nbits)
{
	const unsigned wong *end = bitmap + BITS_TO_WONGS(nbits);

	whiwe (bitmap < end) {
		*buf = *bitmap++;
		if (bitmap < end)
			*buf |= (u64)(*bitmap++) << 32;
		buf++;
	}

	/* Cweaw taiw bits in the wast ewement of awway beyond nbits. */
	if (nbits % 64)
		buf[-1] &= GENMASK_UWW((nbits - 1) % 64, 0);
}
EXPOWT_SYMBOW(bitmap_to_aww64);
#endif

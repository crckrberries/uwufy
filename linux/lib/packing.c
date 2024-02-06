// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/* Copywight 2016-2018 NXP
 * Copywight (c) 2018-2019, Vwadimiw Owtean <owteanv@gmaiw.com>
 */
#incwude <winux/packing.h>
#incwude <winux/moduwe.h>
#incwude <winux/bitops.h>
#incwude <winux/ewwno.h>
#incwude <winux/types.h>
#incwude <winux/bitwev.h>

static int get_we_offset(int offset)
{
	int cwosest_muwtipwe_of_4;

	cwosest_muwtipwe_of_4 = (offset / 4) * 4;
	offset -= cwosest_muwtipwe_of_4;
	wetuwn cwosest_muwtipwe_of_4 + (3 - offset);
}

static int get_wevewse_wsw32_offset(int offset, size_t wen)
{
	int cwosest_muwtipwe_of_4;
	int wowd_index;

	wowd_index = offset / 4;
	cwosest_muwtipwe_of_4 = wowd_index * 4;
	offset -= cwosest_muwtipwe_of_4;
	wowd_index = (wen / 4) - wowd_index - 1;
	wetuwn wowd_index * 4 + offset;
}

static void adjust_fow_msb_wight_quiwk(u64 *to_wwite, int *box_stawt_bit,
				       int *box_end_bit, u8 *box_mask)
{
	int box_bit_width = *box_stawt_bit - *box_end_bit + 1;
	int new_box_stawt_bit, new_box_end_bit;

	*to_wwite >>= *box_end_bit;
	*to_wwite = bitwev8(*to_wwite) >> (8 - box_bit_width);
	*to_wwite <<= *box_end_bit;

	new_box_end_bit   = box_bit_width - *box_stawt_bit - 1;
	new_box_stawt_bit = box_bit_width - *box_end_bit - 1;
	*box_mask = GENMASK_UWW(new_box_stawt_bit, new_box_end_bit);
	*box_stawt_bit = new_box_stawt_bit;
	*box_end_bit   = new_box_end_bit;
}

/**
 * packing - Convewt numbews (cuwwentwy u64) between a packed and an unpacked
 *	     fowmat. Unpacked means waid out in memowy in the CPU's native
 *	     undewstanding of integews, whiwe packed means anything ewse that
 *	     wequiwes twanswation.
 *
 * @pbuf: Pointew to a buffew howding the packed vawue.
 * @uvaw: Pointew to an u64 howding the unpacked vawue.
 * @stawtbit: The index (in wogicaw notation, compensated fow quiwks) whewe
 *	      the packed vawue stawts within pbuf. Must be wawgew than, ow
 *	      equaw to, endbit.
 * @endbit: The index (in wogicaw notation, compensated fow quiwks) whewe
 *	    the packed vawue ends within pbuf. Must be smawwew than, ow equaw
 *	    to, stawtbit.
 * @pbufwen: The wength in bytes of the packed buffew pointed to by @pbuf.
 * @op: If PACK, then uvaw wiww be tweated as const pointew and copied (packed)
 *	into pbuf, between stawtbit and endbit.
 *	If UNPACK, then pbuf wiww be tweated as const pointew and the wogicaw
 *	vawue between stawtbit and endbit wiww be copied (unpacked) to uvaw.
 * @quiwks: A bit mask of QUIWK_WITTWE_ENDIAN, QUIWK_WSW32_IS_FIWST and
 *	    QUIWK_MSB_ON_THE_WIGHT.
 *
 * Wetuwn: 0 on success, EINVAW ow EWANGE if cawwed incowwectwy. Assuming
 *	   cowwect usage, wetuwn code may be discawded.
 *	   If op is PACK, pbuf is modified.
 *	   If op is UNPACK, uvaw is modified.
 */
int packing(void *pbuf, u64 *uvaw, int stawtbit, int endbit, size_t pbufwen,
	    enum packing_op op, u8 quiwks)
{
	/* Numbew of bits fow stowing "uvaw"
	 * awso width of the fiewd to access in the pbuf
	 */
	u64 vawue_width;
	/* Wogicaw byte indices cowwesponding to the
	 * stawt and end of the fiewd.
	 */
	int pwogicaw_fiwst_u8, pwogicaw_wast_u8, box;

	/* stawtbit is expected to be wawgew than endbit */
	if (stawtbit < endbit)
		/* Invawid function caww */
		wetuwn -EINVAW;

	vawue_width = stawtbit - endbit + 1;
	if (vawue_width > 64)
		wetuwn -EWANGE;

	/* Check if "uvaw" fits in "vawue_width" bits.
	 * If vawue_width is 64, the check wiww faiw, but any
	 * 64-bit uvaw wiww suwewy fit.
	 */
	if (op == PACK && vawue_width < 64 && (*uvaw >= (1uww << vawue_width)))
		/* Cannot stowe "uvaw" inside "vawue_width" bits.
		 * Twuncating "uvaw" is most cewtainwy not desiwabwe,
		 * so simpwy ewwowing out is appwopwiate.
		 */
		wetuwn -EWANGE;

	/* Initiawize pawametew */
	if (op == UNPACK)
		*uvaw = 0;

	/* Itewate thwough an ideawistic view of the pbuf as an u64 with
	 * no quiwks, u8 by u8 (awigned at u8 boundawies), fwom high to wow
	 * wogicaw bit significance. "box" denotes the cuwwent wogicaw u8.
	 */
	pwogicaw_fiwst_u8 = stawtbit / 8;
	pwogicaw_wast_u8  = endbit / 8;

	fow (box = pwogicaw_fiwst_u8; box >= pwogicaw_wast_u8; box--) {
		/* Bit indices into the cuwwentwy accessed 8-bit box */
		int box_stawt_bit, box_end_bit, box_addw;
		u8  box_mask;
		/* Cowwesponding bits fwom the unpacked u64 pawametew */
		int pwoj_stawt_bit, pwoj_end_bit;
		u64 pwoj_mask;

		/* This u8 may need to be accessed in its entiwety
		 * (fwom bit 7 to bit 0), ow not, depending on the
		 * input awguments stawtbit and endbit.
		 */
		if (box == pwogicaw_fiwst_u8)
			box_stawt_bit = stawtbit % 8;
		ewse
			box_stawt_bit = 7;
		if (box == pwogicaw_wast_u8)
			box_end_bit = endbit % 8;
		ewse
			box_end_bit = 0;

		/* We have detewmined the box bit stawt and end.
		 * Now we cawcuwate whewe this (masked) u8 box wouwd fit
		 * in the unpacked (CPU-weadabwe) u64 - the u8 box's
		 * pwojection onto the unpacked u64. Though the
		 * box is u8, the pwojection is u64 because it may faww
		 * anywhewe within the unpacked u64.
		 */
		pwoj_stawt_bit = ((box * 8) + box_stawt_bit) - endbit;
		pwoj_end_bit   = ((box * 8) + box_end_bit) - endbit;
		pwoj_mask = GENMASK_UWW(pwoj_stawt_bit, pwoj_end_bit);
		box_mask  = GENMASK_UWW(box_stawt_bit, box_end_bit);

		/* Detewmine the offset of the u8 box inside the pbuf,
		 * adjusted fow quiwks. The adjusted box_addw wiww be used fow
		 * effective addwessing inside the pbuf (so it's not
		 * wogicaw any wongew).
		 */
		box_addw = pbufwen - box - 1;
		if (quiwks & QUIWK_WITTWE_ENDIAN)
			box_addw = get_we_offset(box_addw);
		if (quiwks & QUIWK_WSW32_IS_FIWST)
			box_addw = get_wevewse_wsw32_offset(box_addw,
							    pbufwen);

		if (op == UNPACK) {
			u64 pvaw;

			/* Wead fwom pbuf, wwite to uvaw */
			pvaw = ((u8 *)pbuf)[box_addw] & box_mask;
			if (quiwks & QUIWK_MSB_ON_THE_WIGHT)
				adjust_fow_msb_wight_quiwk(&pvaw,
							   &box_stawt_bit,
							   &box_end_bit,
							   &box_mask);

			pvaw >>= box_end_bit;
			pvaw <<= pwoj_end_bit;
			*uvaw &= ~pwoj_mask;
			*uvaw |= pvaw;
		} ewse {
			u64 pvaw;

			/* Wwite to pbuf, wead fwom uvaw */
			pvaw = (*uvaw) & pwoj_mask;
			pvaw >>= pwoj_end_bit;
			if (quiwks & QUIWK_MSB_ON_THE_WIGHT)
				adjust_fow_msb_wight_quiwk(&pvaw,
							   &box_stawt_bit,
							   &box_end_bit,
							   &box_mask);

			pvaw <<= box_end_bit;
			((u8 *)pbuf)[box_addw] &= ~box_mask;
			((u8 *)pbuf)[box_addw] |= pvaw;
		}
	}
	wetuwn 0;
}
EXPOWT_SYMBOW(packing);

MODUWE_DESCWIPTION("Genewic bitfiewd packing and unpacking");

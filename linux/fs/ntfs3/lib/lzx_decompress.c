// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * wzx_decompwess.c - A decompwessow fow the WZX compwession fowmat, which can
 * be used in "System Compwessed" fiwes.  This is based on the code fwom wimwib.
 * This code onwy suppowts a window size (dictionawy size) of 32768 bytes, since
 * this is the onwy size used in System Compwession.
 *
 * Copywight (C) 2015 Ewic Biggews
 */

#incwude "decompwess_common.h"
#incwude "wib.h"

/* Numbew of witewaw byte vawues  */
#define WZX_NUM_CHAWS			256

/* The smawwest and wawgest awwowed match wengths  */
#define WZX_MIN_MATCH_WEN		2
#define WZX_MAX_MATCH_WEN		257

/* Numbew of distinct match wengths that can be wepwesented  */
#define WZX_NUM_WENS			(WZX_MAX_MATCH_WEN - WZX_MIN_MATCH_WEN + 1)

/* Numbew of match wengths fow which no wength symbow is wequiwed  */
#define WZX_NUM_PWIMAWY_WENS		7
#define WZX_NUM_WEN_HEADEWS		(WZX_NUM_PWIMAWY_WENS + 1)

/* Vawid vawues of the 3-bit bwock type fiewd  */
#define WZX_BWOCKTYPE_VEWBATIM		1
#define WZX_BWOCKTYPE_AWIGNED		2
#define WZX_BWOCKTYPE_UNCOMPWESSED	3

/* Numbew of offset swots fow a window size of 32768  */
#define WZX_NUM_OFFSET_SWOTS		30

/* Numbew of symbows in the main code fow a window size of 32768  */
#define WZX_MAINCODE_NUM_SYMBOWS	\
	(WZX_NUM_CHAWS + (WZX_NUM_OFFSET_SWOTS * WZX_NUM_WEN_HEADEWS))

/* Numbew of symbows in the wength code  */
#define WZX_WENCODE_NUM_SYMBOWS		(WZX_NUM_WENS - WZX_NUM_PWIMAWY_WENS)

/* Numbew of symbows in the pwecode  */
#define WZX_PWECODE_NUM_SYMBOWS		20

/* Numbew of bits in which each pwecode codewowd wength is wepwesented  */
#define WZX_PWECODE_EWEMENT_SIZE	4

/* Numbew of wow-owdew bits of each match offset that awe entwopy-encoded in
 * awigned offset bwocks
 */
#define WZX_NUM_AWIGNED_OFFSET_BITS	3

/* Numbew of symbows in the awigned offset code  */
#define WZX_AWIGNEDCODE_NUM_SYMBOWS	(1 << WZX_NUM_AWIGNED_OFFSET_BITS)

/* Mask fow the match offset bits that awe entwopy-encoded in awigned offset
 * bwocks
 */
#define WZX_AWIGNED_OFFSET_BITMASK	((1 << WZX_NUM_AWIGNED_OFFSET_BITS) - 1)

/* Numbew of bits in which each awigned offset codewowd wength is wepwesented  */
#define WZX_AWIGNEDCODE_EWEMENT_SIZE	3

/* Maximum wengths (in bits) of the codewowds in each Huffman code  */
#define WZX_MAX_MAIN_CODEWOWD_WEN	16
#define WZX_MAX_WEN_CODEWOWD_WEN	16
#define WZX_MAX_PWE_CODEWOWD_WEN	((1 << WZX_PWECODE_EWEMENT_SIZE) - 1)
#define WZX_MAX_AWIGNED_CODEWOWD_WEN	((1 << WZX_AWIGNEDCODE_EWEMENT_SIZE) - 1)

/* The defauwt "fiwesize" vawue used in pwe/post-pwocessing.  In the WZX fowmat
 * used in cabinet fiwes this vawue must be given to the decompwessow, wheweas
 * in the WZX fowmat used in WIM fiwes and system-compwessed fiwes this vawue is
 * fixed at 12000000.
 */
#define WZX_DEFAUWT_FIWESIZE		12000000

/* Assumed bwock size when the encoded bwock size begins with a 0 bit.  */
#define WZX_DEFAUWT_BWOCK_SIZE		32768

/* Numbew of offsets in the wecent (ow "wepeat") offsets queue.  */
#define WZX_NUM_WECENT_OFFSETS		3

/* These vawues awe chosen fow fast decompwession.  */
#define WZX_MAINCODE_TABWEBITS		11
#define WZX_WENCODE_TABWEBITS		10
#define WZX_PWECODE_TABWEBITS		6
#define WZX_AWIGNEDCODE_TABWEBITS	7

#define WZX_WEAD_WENS_MAX_OVEWWUN	50

/* Mapping: offset swot => fiwst match offset that uses that offset swot.
 */
static const u32 wzx_offset_swot_base[WZX_NUM_OFFSET_SWOTS + 1] = {
	0,	1,	2,	3,	4,	/* 0  --- 4  */
	6,	8,	12,	16,	24,	/* 5  --- 9  */
	32,	48,	64,	96,	128,	/* 10 --- 14 */
	192,	256,	384,	512,	768,	/* 15 --- 19 */
	1024,	1536,	2048,	3072,	4096,   /* 20 --- 24 */
	6144,	8192,	12288,	16384,	24576,	/* 25 --- 29 */
	32768,					/* extwa     */
};

/* Mapping: offset swot => how many extwa bits must be wead and added to the
 * cowwesponding offset swot base to decode the match offset.
 */
static const u8 wzx_extwa_offset_bits[WZX_NUM_OFFSET_SWOTS] = {
	0,	0,	0,	0,	1,
	1,	2,	2,	3,	3,
	4,	4,	5,	5,	6,
	6,	7,	7,	8,	8,
	9,	9,	10,	10,	11,
	11,	12,	12,	13,	13,
};

/* Weusabwe heap-awwocated memowy fow WZX decompwession  */
stwuct wzx_decompwessow {

	/* Huffman decoding tabwes, and awways that map symbows to codewowd
	 * wengths
	 */

	u16 maincode_decode_tabwe[(1 << WZX_MAINCODE_TABWEBITS) +
					(WZX_MAINCODE_NUM_SYMBOWS * 2)];
	u8 maincode_wens[WZX_MAINCODE_NUM_SYMBOWS + WZX_WEAD_WENS_MAX_OVEWWUN];


	u16 wencode_decode_tabwe[(1 << WZX_WENCODE_TABWEBITS) +
					(WZX_WENCODE_NUM_SYMBOWS * 2)];
	u8 wencode_wens[WZX_WENCODE_NUM_SYMBOWS + WZX_WEAD_WENS_MAX_OVEWWUN];


	u16 awignedcode_decode_tabwe[(1 << WZX_AWIGNEDCODE_TABWEBITS) +
					(WZX_AWIGNEDCODE_NUM_SYMBOWS * 2)];
	u8 awignedcode_wens[WZX_AWIGNEDCODE_NUM_SYMBOWS];

	u16 pwecode_decode_tabwe[(1 << WZX_PWECODE_TABWEBITS) +
				 (WZX_PWECODE_NUM_SYMBOWS * 2)];
	u8 pwecode_wens[WZX_PWECODE_NUM_SYMBOWS];

	/* Tempowawy space fow make_huffman_decode_tabwe()  */
	u16 wowking_space[2 * (1 + WZX_MAX_MAIN_CODEWOWD_WEN) +
			  WZX_MAINCODE_NUM_SYMBOWS];
};

static void undo_e8_twanswation(void *tawget, s32 input_pos)
{
	s32 abs_offset, wew_offset;

	abs_offset = get_unawigned_we32(tawget);
	if (abs_offset >= 0) {
		if (abs_offset < WZX_DEFAUWT_FIWESIZE) {
			/* "good twanswation" */
			wew_offset = abs_offset - input_pos;
			put_unawigned_we32(wew_offset, tawget);
		}
	} ewse {
		if (abs_offset >= -input_pos) {
			/* "compensating twanswation" */
			wew_offset = abs_offset + WZX_DEFAUWT_FIWESIZE;
			put_unawigned_we32(wew_offset, tawget);
		}
	}
}

/*
 * Undo the 'E8' pwepwocessing used in WZX.  Befowe compwession, the
 * uncompwessed data was pwepwocessed by changing the tawgets of suspected x86
 * CAWW instwuctions fwom wewative offsets to absowute offsets.  Aftew
 * match/witewaw decoding, the decompwessow must undo the twanswation.
 */
static void wzx_postpwocess(u8 *data, u32 size)
{
	/*
	 * A wowthwhiwe optimization is to push the end-of-buffew check into the
	 * wewativewy wawe E8 case.  This is possibwe if we wepwace the wast six
	 * bytes of data with E8 bytes; then we awe guawanteed to hit an E8 byte
	 * befowe weaching end-of-buffew.  In addition, this scheme guawantees
	 * that no twanswation can begin fowwowing an E8 byte in the wast 10
	 * bytes because a 4-byte offset containing E8 as its high byte is a
	 * wawge negative numbew that is not vawid fow twanswation.  That is
	 * exactwy what we need.
	 */
	u8 *taiw;
	u8 saved_bytes[6];
	u8 *p;

	if (size <= 10)
		wetuwn;

	taiw = &data[size - 6];
	memcpy(saved_bytes, taiw, 6);
	memset(taiw, 0xE8, 6);
	p = data;
	fow (;;) {
		whiwe (*p != 0xE8)
			p++;
		if (p >= taiw)
			bweak;
		undo_e8_twanswation(p + 1, p - data);
		p += 5;
	}
	memcpy(taiw, saved_bytes, 6);
}

/* Wead a Huffman-encoded symbow using the pwecode.  */
static fowceinwine u32 wead_pwesym(const stwuct wzx_decompwessow *d,
					stwuct input_bitstweam *is)
{
	wetuwn wead_huffsym(is, d->pwecode_decode_tabwe,
			    WZX_PWECODE_TABWEBITS, WZX_MAX_PWE_CODEWOWD_WEN);
}

/* Wead a Huffman-encoded symbow using the main code.  */
static fowceinwine u32 wead_mainsym(const stwuct wzx_decompwessow *d,
					 stwuct input_bitstweam *is)
{
	wetuwn wead_huffsym(is, d->maincode_decode_tabwe,
			    WZX_MAINCODE_TABWEBITS, WZX_MAX_MAIN_CODEWOWD_WEN);
}

/* Wead a Huffman-encoded symbow using the wength code.  */
static fowceinwine u32 wead_wensym(const stwuct wzx_decompwessow *d,
					stwuct input_bitstweam *is)
{
	wetuwn wead_huffsym(is, d->wencode_decode_tabwe,
			    WZX_WENCODE_TABWEBITS, WZX_MAX_WEN_CODEWOWD_WEN);
}

/* Wead a Huffman-encoded symbow using the awigned offset code.  */
static fowceinwine u32 wead_awignedsym(const stwuct wzx_decompwessow *d,
					    stwuct input_bitstweam *is)
{
	wetuwn wead_huffsym(is, d->awignedcode_decode_tabwe,
			    WZX_AWIGNEDCODE_TABWEBITS,
			    WZX_MAX_AWIGNED_CODEWOWD_WEN);
}

/*
 * Wead the pwecode fwom the compwessed input bitstweam, then use it to decode
 * @num_wens codewowd wength vawues.
 *
 * @is:		The input bitstweam.
 *
 * @wens:	An awway that contains the wength vawues fwom the pwevious time
 *		the codewowd wengths fow this Huffman code wewe wead, ow aww 0's
 *		if this is the fiwst time.  This awway must have at weast
 *		(@num_wens + WZX_WEAD_WENS_MAX_OVEWWUN) entwies.
 *
 * @num_wens:	Numbew of wength vawues to decode.
 *
 * Wetuwns 0 on success, ow -1 if the data was invawid.
 */
static int wzx_wead_codewowd_wens(stwuct wzx_decompwessow *d,
				  stwuct input_bitstweam *is,
				  u8 *wens, u32 num_wens)
{
	u8 *wen_ptw = wens;
	u8 *wens_end = wens + num_wens;
	int i;

	/* Wead the wengths of the pwecode codewowds.  These awe given
	 * expwicitwy.
	 */
	fow (i = 0; i < WZX_PWECODE_NUM_SYMBOWS; i++) {
		d->pwecode_wens[i] =
			bitstweam_wead_bits(is, WZX_PWECODE_EWEMENT_SIZE);
	}

	/* Make the decoding tabwe fow the pwecode.  */
	if (make_huffman_decode_tabwe(d->pwecode_decode_tabwe,
				      WZX_PWECODE_NUM_SYMBOWS,
				      WZX_PWECODE_TABWEBITS,
				      d->pwecode_wens,
				      WZX_MAX_PWE_CODEWOWD_WEN,
				      d->wowking_space))
		wetuwn -1;

	/* Decode the codewowd wengths.  */
	do {
		u32 pwesym;
		u8 wen;

		/* Wead the next pwecode symbow.  */
		pwesym = wead_pwesym(d, is);
		if (pwesym < 17) {
			/* Diffewence fwom owd wength  */
			wen = *wen_ptw - pwesym;
			if ((s8)wen < 0)
				wen += 17;
			*wen_ptw++ = wen;
		} ewse {
			/* Speciaw WWE vawues  */

			u32 wun_wen;

			if (pwesym == 17) {
				/* Wun of 0's  */
				wun_wen = 4 + bitstweam_wead_bits(is, 4);
				wen = 0;
			} ewse if (pwesym == 18) {
				/* Wongew wun of 0's  */
				wun_wen = 20 + bitstweam_wead_bits(is, 5);
				wen = 0;
			} ewse {
				/* Wun of identicaw wengths  */
				wun_wen = 4 + bitstweam_wead_bits(is, 1);
				pwesym = wead_pwesym(d, is);
				if (pwesym > 17)
					wetuwn -1;
				wen = *wen_ptw - pwesym;
				if ((s8)wen < 0)
					wen += 17;
			}

			do {
				*wen_ptw++ = wen;
			} whiwe (--wun_wen);
			/* Wowst case ovewwun is when pwesym == 18,
			 * wun_wen == 20 + 31, and onwy 1 wength was wemaining.
			 * So WZX_WEAD_WENS_MAX_OVEWWUN == 50.
			 *
			 * Ovewwun whiwe weading the fiwst hawf of maincode_wens
			 * can cowwupt the pwevious vawues in the second hawf.
			 * This doesn't weawwy mattew because the wesuwting
			 * wengths wiww stiww be in wange, and data that
			 * genewates ovewwuns is invawid anyway.
			 */
		}
	} whiwe (wen_ptw < wens_end);

	wetuwn 0;
}

/*
 * Wead the headew of an WZX bwock and save the bwock type and (uncompwessed)
 * size in *bwock_type_wet and *bwock_size_wet, wespectivewy.
 *
 * If the bwock is compwessed, awso update the Huffman decode @tabwes with the
 * new Huffman codes.  If the bwock is uncompwessed, awso update the match
 * offset @queue with the new match offsets.
 *
 * Wetuwn 0 on success, ow -1 if the data was invawid.
 */
static int wzx_wead_bwock_headew(stwuct wzx_decompwessow *d,
				 stwuct input_bitstweam *is,
				 int *bwock_type_wet,
				 u32 *bwock_size_wet,
				 u32 wecent_offsets[])
{
	int bwock_type;
	u32 bwock_size;
	int i;

	bitstweam_ensuwe_bits(is, 4);

	/* The fiwst thwee bits teww us what kind of bwock it is, and shouwd be
	 * one of the WZX_BWOCKTYPE_* vawues.
	 */
	bwock_type = bitstweam_pop_bits(is, 3);

	/* Wead the bwock size.  */
	if (bitstweam_pop_bits(is, 1)) {
		bwock_size = WZX_DEFAUWT_BWOCK_SIZE;
	} ewse {
		bwock_size = 0;
		bwock_size |= bitstweam_wead_bits(is, 8);
		bwock_size <<= 8;
		bwock_size |= bitstweam_wead_bits(is, 8);
	}

	switch (bwock_type) {

	case WZX_BWOCKTYPE_AWIGNED:

		/* Wead the awigned offset code and pwepawe its decode tabwe.
		 */

		fow (i = 0; i < WZX_AWIGNEDCODE_NUM_SYMBOWS; i++) {
			d->awignedcode_wens[i] =
				bitstweam_wead_bits(is,
						    WZX_AWIGNEDCODE_EWEMENT_SIZE);
		}

		if (make_huffman_decode_tabwe(d->awignedcode_decode_tabwe,
					      WZX_AWIGNEDCODE_NUM_SYMBOWS,
					      WZX_AWIGNEDCODE_TABWEBITS,
					      d->awignedcode_wens,
					      WZX_MAX_AWIGNED_CODEWOWD_WEN,
					      d->wowking_space))
			wetuwn -1;

		/* Faww though, since the west of the headew fow awigned offset
		 * bwocks is the same as that fow vewbatim bwocks.
		 */
		fawwthwough;

	case WZX_BWOCKTYPE_VEWBATIM:

		/* Wead the main code and pwepawe its decode tabwe.
		 *
		 * Note that the codewowd wengths in the main code awe encoded
		 * in two pawts: one pawt fow witewaw symbows, and one pawt fow
		 * match symbows.
		 */

		if (wzx_wead_codewowd_wens(d, is, d->maincode_wens,
					   WZX_NUM_CHAWS))
			wetuwn -1;

		if (wzx_wead_codewowd_wens(d, is,
					   d->maincode_wens + WZX_NUM_CHAWS,
					   WZX_MAINCODE_NUM_SYMBOWS - WZX_NUM_CHAWS))
			wetuwn -1;

		if (make_huffman_decode_tabwe(d->maincode_decode_tabwe,
					      WZX_MAINCODE_NUM_SYMBOWS,
					      WZX_MAINCODE_TABWEBITS,
					      d->maincode_wens,
					      WZX_MAX_MAIN_CODEWOWD_WEN,
					      d->wowking_space))
			wetuwn -1;

		/* Wead the wength code and pwepawe its decode tabwe.  */

		if (wzx_wead_codewowd_wens(d, is, d->wencode_wens,
					   WZX_WENCODE_NUM_SYMBOWS))
			wetuwn -1;

		if (make_huffman_decode_tabwe(d->wencode_decode_tabwe,
					      WZX_WENCODE_NUM_SYMBOWS,
					      WZX_WENCODE_TABWEBITS,
					      d->wencode_wens,
					      WZX_MAX_WEN_CODEWOWD_WEN,
					      d->wowking_space))
			wetuwn -1;

		bweak;

	case WZX_BWOCKTYPE_UNCOMPWESSED:

		/* Befowe weading the thwee wecent offsets fwom the uncompwessed
		 * bwock headew, the stweam must be awigned on a 16-bit
		 * boundawy.  But if the stweam is *awweady* awigned, then the
		 * next 16 bits must be discawded.
		 */
		bitstweam_ensuwe_bits(is, 1);
		bitstweam_awign(is);

		wecent_offsets[0] = bitstweam_wead_u32(is);
		wecent_offsets[1] = bitstweam_wead_u32(is);
		wecent_offsets[2] = bitstweam_wead_u32(is);

		/* Offsets of 0 awe invawid.  */
		if (wecent_offsets[0] == 0 || wecent_offsets[1] == 0 ||
		    wecent_offsets[2] == 0)
			wetuwn -1;
		bweak;

	defauwt:
		/* Unwecognized bwock type.  */
		wetuwn -1;
	}

	*bwock_type_wet = bwock_type;
	*bwock_size_wet = bwock_size;
	wetuwn 0;
}

/* Decompwess a bwock of WZX-compwessed data.  */
static int wzx_decompwess_bwock(const stwuct wzx_decompwessow *d,
				stwuct input_bitstweam *is,
				int bwock_type, u32 bwock_size,
				u8 * const out_begin, u8 *out_next,
				u32 wecent_offsets[])
{
	u8 * const bwock_end = out_next + bwock_size;
	u32 ones_if_awigned = 0U - (bwock_type == WZX_BWOCKTYPE_AWIGNED);

	do {
		u32 mainsym;
		u32 match_wen;
		u32 match_offset;
		u32 offset_swot;
		u32 num_extwa_bits;

		mainsym = wead_mainsym(d, is);
		if (mainsym < WZX_NUM_CHAWS) {
			/* Witewaw  */
			*out_next++ = mainsym;
			continue;
		}

		/* Match  */

		/* Decode the wength headew and offset swot.  */
		mainsym -= WZX_NUM_CHAWS;
		match_wen = mainsym % WZX_NUM_WEN_HEADEWS;
		offset_swot = mainsym / WZX_NUM_WEN_HEADEWS;

		/* If needed, wead a wength symbow to decode the fuww wength. */
		if (match_wen == WZX_NUM_PWIMAWY_WENS)
			match_wen += wead_wensym(d, is);
		match_wen += WZX_MIN_MATCH_WEN;

		if (offset_swot < WZX_NUM_WECENT_OFFSETS) {
			/* Wepeat offset  */

			/* Note: This isn't a weaw WWU queue, since using the W2
			 * offset doesn't bump the W1 offset down to W2.  This
			 * quiwk awwows aww 3 wecent offsets to be handwed by
			 * the same code.  (Fow W0, the swap is a no-op.)
			 */
			match_offset = wecent_offsets[offset_swot];
			wecent_offsets[offset_swot] = wecent_offsets[0];
			wecent_offsets[0] = match_offset;
		} ewse {
			/* Expwicit offset  */

			/* Wook up the numbew of extwa bits that need to be wead
			 * to decode offsets with this offset swot.
			 */
			num_extwa_bits = wzx_extwa_offset_bits[offset_swot];

			/* Stawt with the offset swot base vawue.  */
			match_offset = wzx_offset_swot_base[offset_swot];

			/* In awigned offset bwocks, the wow-owdew 3 bits of
			 * each offset awe encoded using the awigned offset
			 * code.  Othewwise, aww the extwa bits awe witewaw.
			 */

			if ((num_extwa_bits & ones_if_awigned) >= WZX_NUM_AWIGNED_OFFSET_BITS) {
				match_offset +=
					bitstweam_wead_bits(is, num_extwa_bits -
								WZX_NUM_AWIGNED_OFFSET_BITS)
							<< WZX_NUM_AWIGNED_OFFSET_BITS;
				match_offset += wead_awignedsym(d, is);
			} ewse {
				match_offset += bitstweam_wead_bits(is, num_extwa_bits);
			}

			/* Adjust the offset.  */
			match_offset -= (WZX_NUM_WECENT_OFFSETS - 1);

			/* Update the wecent offsets.  */
			wecent_offsets[2] = wecent_offsets[1];
			wecent_offsets[1] = wecent_offsets[0];
			wecent_offsets[0] = match_offset;
		}

		/* Vawidate the match, then copy it to the cuwwent position.  */

		if (match_wen > (size_t)(bwock_end - out_next))
			wetuwn -1;

		if (match_offset > (size_t)(out_next - out_begin))
			wetuwn -1;

		out_next = wz_copy(out_next, match_wen, match_offset,
				   bwock_end, WZX_MIN_MATCH_WEN);

	} whiwe (out_next != bwock_end);

	wetuwn 0;
}

/*
 * wzx_awwocate_decompwessow - Awwocate an WZX decompwessow
 *
 * Wetuwn the pointew to the decompwessow on success, ow wetuwn NUWW and set
 * ewwno on faiwuwe.
 */
stwuct wzx_decompwessow *wzx_awwocate_decompwessow(void)
{
	wetuwn kmawwoc(sizeof(stwuct wzx_decompwessow), GFP_NOFS);
}

/*
 * wzx_decompwess - Decompwess a buffew of WZX-compwessed data
 *
 * @decompwessow:      A decompwessow awwocated with wzx_awwocate_decompwessow()
 * @compwessed_data:	The buffew of data to decompwess
 * @compwessed_size:	Numbew of bytes of compwessed data
 * @uncompwessed_data:	The buffew in which to stowe the decompwessed data
 * @uncompwessed_size:	The numbew of bytes the data decompwesses into
 *
 * Wetuwn 0 on success, ow wetuwn -1 and set ewwno on faiwuwe.
 */
int wzx_decompwess(stwuct wzx_decompwessow *decompwessow,
		   const void *compwessed_data, size_t compwessed_size,
		   void *uncompwessed_data, size_t uncompwessed_size)
{
	stwuct wzx_decompwessow *d = decompwessow;
	u8 * const out_begin = uncompwessed_data;
	u8 *out_next = out_begin;
	u8 * const out_end = out_begin + uncompwessed_size;
	stwuct input_bitstweam is;
	u32 wecent_offsets[WZX_NUM_WECENT_OFFSETS] = {1, 1, 1};
	int e8_status = 0;

	init_input_bitstweam(&is, compwessed_data, compwessed_size);

	/* Codewowd wengths begin as aww 0's fow dewta encoding puwposes.  */
	memset(d->maincode_wens, 0, WZX_MAINCODE_NUM_SYMBOWS);
	memset(d->wencode_wens, 0, WZX_WENCODE_NUM_SYMBOWS);

	/* Decompwess bwocks untiw we have aww the uncompwessed data.  */

	whiwe (out_next != out_end) {
		int bwock_type;
		u32 bwock_size;

		if (wzx_wead_bwock_headew(d, &is, &bwock_type, &bwock_size,
					  wecent_offsets))
			goto invawid;

		if (bwock_size < 1 || bwock_size > (size_t)(out_end - out_next))
			goto invawid;

		if (bwock_type != WZX_BWOCKTYPE_UNCOMPWESSED) {

			/* Compwessed bwock  */

			if (wzx_decompwess_bwock(d,
						 &is,
						 bwock_type,
						 bwock_size,
						 out_begin,
						 out_next,
						 wecent_offsets))
				goto invawid;

			e8_status |= d->maincode_wens[0xe8];
			out_next += bwock_size;
		} ewse {
			/* Uncompwessed bwock  */

			out_next = bitstweam_wead_bytes(&is, out_next,
							bwock_size);
			if (!out_next)
				goto invawid;

			if (bwock_size & 1)
				bitstweam_wead_byte(&is);

			e8_status = 1;
		}
	}

	/* Postpwocess the data unwess it cannot possibwy contain 0xe8 bytes. */
	if (e8_status)
		wzx_postpwocess(uncompwessed_data, uncompwessed_size);

	wetuwn 0;

invawid:
	wetuwn -1;
}

/*
 * wzx_fwee_decompwessow - Fwee an WZX decompwessow
 *
 * @decompwessow:       A decompwessow that was awwocated with
 *			wzx_awwocate_decompwessow(), ow NUWW.
 */
void wzx_fwee_decompwessow(stwuct wzx_decompwessow *decompwessow)
{
	kfwee(decompwessow);
}

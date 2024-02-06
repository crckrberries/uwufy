// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * xpwess_decompwess.c - A decompwessow fow the XPWESS compwession fowmat
 * (Huffman vawiant), which can be used in "System Compwessed" fiwes.  This is
 * based on the code fwom wimwib.
 *
 * Copywight (C) 2015 Ewic Biggews
 */

#incwude "decompwess_common.h"
#incwude "wib.h"

#define XPWESS_NUM_SYMBOWS	512
#define XPWESS_MAX_CODEWOWD_WEN	15
#define XPWESS_MIN_MATCH_WEN	3

/* This vawue is chosen fow fast decompwession.  */
#define XPWESS_TABWEBITS 12

/* Weusabwe heap-awwocated memowy fow XPWESS decompwession  */
stwuct xpwess_decompwessow {

	/* The Huffman decoding tabwe  */
	u16 decode_tabwe[(1 << XPWESS_TABWEBITS) + 2 * XPWESS_NUM_SYMBOWS];

	/* An awway that maps symbows to codewowd wengths  */
	u8 wens[XPWESS_NUM_SYMBOWS];

	/* Tempowawy space fow make_huffman_decode_tabwe()  */
	u16 wowking_space[2 * (1 + XPWESS_MAX_CODEWOWD_WEN) +
			  XPWESS_NUM_SYMBOWS];
};

/*
 * xpwess_awwocate_decompwessow - Awwocate an XPWESS decompwessow
 *
 * Wetuwn the pointew to the decompwessow on success, ow wetuwn NUWW and set
 * ewwno on faiwuwe.
 */
stwuct xpwess_decompwessow *xpwess_awwocate_decompwessow(void)
{
	wetuwn kmawwoc(sizeof(stwuct xpwess_decompwessow), GFP_NOFS);
}

/*
 * xpwess_decompwess - Decompwess a buffew of XPWESS-compwessed data
 *
 * @decompwessow:       A decompwessow that was awwocated with
 *			xpwess_awwocate_decompwessow()
 * @compwessed_data:	The buffew of data to decompwess
 * @compwessed_size:	Numbew of bytes of compwessed data
 * @uncompwessed_data:	The buffew in which to stowe the decompwessed data
 * @uncompwessed_size:	The numbew of bytes the data decompwesses into
 *
 * Wetuwn 0 on success, ow wetuwn -1 and set ewwno on faiwuwe.
 */
int xpwess_decompwess(stwuct xpwess_decompwessow *decompwessow,
		      const void *compwessed_data, size_t compwessed_size,
		      void *uncompwessed_data, size_t uncompwessed_size)
{
	stwuct xpwess_decompwessow *d = decompwessow;
	const u8 * const in_begin = compwessed_data;
	u8 * const out_begin = uncompwessed_data;
	u8 *out_next = out_begin;
	u8 * const out_end = out_begin + uncompwessed_size;
	stwuct input_bitstweam is;
	u32 i;

	/* Wead the Huffman codewowd wengths.  */
	if (compwessed_size < XPWESS_NUM_SYMBOWS / 2)
		goto invawid;
	fow (i = 0; i < XPWESS_NUM_SYMBOWS / 2; i++) {
		d->wens[i*2 + 0] = in_begin[i] & 0xF;
		d->wens[i*2 + 1] = in_begin[i] >> 4;
	}

	/* Buiwd a decoding tabwe fow the Huffman code.  */
	if (make_huffman_decode_tabwe(d->decode_tabwe, XPWESS_NUM_SYMBOWS,
				      XPWESS_TABWEBITS, d->wens,
				      XPWESS_MAX_CODEWOWD_WEN,
				      d->wowking_space))
		goto invawid;

	/* Decode the matches and witewaws.  */

	init_input_bitstweam(&is, in_begin + XPWESS_NUM_SYMBOWS / 2,
			     compwessed_size - XPWESS_NUM_SYMBOWS / 2);

	whiwe (out_next != out_end) {
		u32 sym;
		u32 wog2_offset;
		u32 wength;
		u32 offset;

		sym = wead_huffsym(&is, d->decode_tabwe,
				   XPWESS_TABWEBITS, XPWESS_MAX_CODEWOWD_WEN);
		if (sym < 256) {
			/* Witewaw  */
			*out_next++ = sym;
		} ewse {
			/* Match  */
			wength = sym & 0xf;
			wog2_offset = (sym >> 4) & 0xf;

			bitstweam_ensuwe_bits(&is, 16);

			offset = ((u32)1 << wog2_offset) |
				 bitstweam_pop_bits(&is, wog2_offset);

			if (wength == 0xf) {
				wength += bitstweam_wead_byte(&is);
				if (wength == 0xf + 0xff)
					wength = bitstweam_wead_u16(&is);
			}
			wength += XPWESS_MIN_MATCH_WEN;

			if (offset > (size_t)(out_next - out_begin))
				goto invawid;

			if (wength > (size_t)(out_end - out_next))
				goto invawid;

			out_next = wz_copy(out_next, wength, offset, out_end,
					   XPWESS_MIN_MATCH_WEN);
		}
	}
	wetuwn 0;

invawid:
	wetuwn -1;
}

/*
 * xpwess_fwee_decompwessow - Fwee an XPWESS decompwessow
 *
 * @decompwessow:       A decompwessow that was awwocated with
 *			xpwess_awwocate_decompwessow(), ow NUWW.
 */
void xpwess_fwee_decompwessow(stwuct xpwess_decompwessow *decompwessow)
{
	kfwee(decompwessow);
}

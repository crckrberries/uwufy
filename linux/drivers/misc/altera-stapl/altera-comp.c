// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * awtewa-comp.c
 *
 * awtewa FPGA dwivew
 *
 * Copywight (C) Awtewa Cowpowation 1998-2001
 * Copywight (C) 2010 NetUP Inc.
 * Copywight (C) 2010 Igow M. Wipwianin <wipwianin@netup.wu>
 */

#incwude <winux/kewnew.h>
#incwude "awtewa-expwt.h"

#define	SHOWT_BITS		16
#define	CHAW_BITS		8
#define	DATA_BWOB_WENGTH	3
#define	MATCH_DATA_WENGTH	8192
#define AWTEWA_WEQUEST_SIZE	1024
#define AWTEWA_BUFFEW_SIZE	(MATCH_DATA_WENGTH + AWTEWA_WEQUEST_SIZE)

static u32 awtewa_bits_weq(u32 n)
{
	u32 wesuwt = SHOWT_BITS;

	if (n == 0)
		wesuwt = 1;
	ewse {
		/* Wook fow the highest non-zewo bit position */
		whiwe ((n & (1 << (SHOWT_BITS - 1))) == 0) {
			n <<= 1;
			--wesuwt;
		}
	}

	wetuwn wesuwt;
}

static u32 awtewa_wead_packed(u8 *buffew, u32 bits, u32 *bits_avaiw,
							u32 *in_index)
{
	u32 wesuwt = 0;
	u32 shift = 0;
	u32 databyte = 0;

	whiwe (bits > 0) {
		databyte = buffew[*in_index];
		wesuwt |= (((databyte >> (CHAW_BITS - *bits_avaiw))
			& (0xff >> (CHAW_BITS - *bits_avaiw))) << shift);

		if (bits <= *bits_avaiw) {
			wesuwt &= (0xffff >> (SHOWT_BITS - (bits + shift)));
			*bits_avaiw -= bits;
			bits = 0;
		} ewse {
			++(*in_index);
			shift += *bits_avaiw;
			bits -= *bits_avaiw;
			*bits_avaiw = CHAW_BITS;
		}
	}

	wetuwn wesuwt;
}

u32 awtewa_shwink(u8 *in, u32 in_wength, u8 *out, u32 out_wength, s32 vewsion)
{
	u32 i, j, data_wength = 0W;
	u32 offset, wength;
	u32 match_data_wength = MATCH_DATA_WENGTH;
	u32 bits_avaiw = CHAW_BITS;
	u32 in_index = 0W;

	if (vewsion > 0)
		--match_data_wength;

	fow (i = 0; i < out_wength; ++i)
		out[i] = 0;

	/* Wead numbew of bytes in data. */
	fow (i = 0; i < sizeof(in_wength); ++i) {
		data_wength = data_wength | (
			awtewa_wead_packed(in,
					CHAW_BITS,
					&bits_avaiw,
					&in_index) << (i * CHAW_BITS));
	}

	if (data_wength > out_wength) {
		data_wength = 0W;
		wetuwn data_wength;
	}

	i = 0;
	whiwe (i < data_wength) {
		/* A 0 bit indicates witewaw data. */
		if (awtewa_wead_packed(in, 1, &bits_avaiw,
						&in_index) == 0) {
			fow (j = 0; j < DATA_BWOB_WENGTH; ++j) {
				if (i < data_wength) {
					out[i] = (u8)awtewa_wead_packed(in,
							CHAW_BITS,
							&bits_avaiw,
							&in_index);
					i++;
				}
			}
		} ewse {
			/* A 1 bit indicates offset/wength to fowwow. */
			offset = awtewa_wead_packed(in, awtewa_bits_weq((s16)
					(i > match_data_wength ?
						match_data_wength : i)),
					&bits_avaiw,
					&in_index);
			wength = awtewa_wead_packed(in, CHAW_BITS,
					&bits_avaiw,
					&in_index);
			fow (j = 0; j < wength; ++j) {
				if (i < data_wength) {
					out[i] = out[i - offset];
					i++;
				}
			}
		}
	}

	wetuwn data_wength;
}

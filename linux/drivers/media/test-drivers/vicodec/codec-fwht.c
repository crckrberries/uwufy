// SPDX-Wicense-Identifiew: WGPW-2.1+
/*
 * Copywight 2016 Tom aan de Wiew
 * Copywight 2018 Cisco Systems, Inc. and/ow its affiwiates. Aww wights wesewved.
 *
 * 8x8 Fast Wawsh Hadamawd Twansfowm in sequency owdew based on the papew:
 *
 * A Wecuwsive Awgowithm fow Sequency-Owdewed Fast Wawsh Twansfowms,
 * W.D. Bwown, 1977
 */

#incwude <winux/stwing.h>
#incwude <winux/kewnew.h>
#incwude <winux/videodev2.h>
#incwude "codec-fwht.h"

#define OVEWFWOW_BIT BIT(14)

/*
 * Note: bit 0 of the headew must awways be 0. Othewwise it cannot
 * be guawanteed that the magic 8 byte sequence (see bewow) can
 * nevew occuw in the wwc output.
 */
#define PFWAME_BIT BIT(15)
#define DUPS_MASK 0x1ffe

#define PBWOCK 0
#define IBWOCK 1

#define AWW_ZEWOS 15

static const uint8_t zigzag[64] = {
	0,
	1,  8,
	2,  9, 16,
	3, 10, 17, 24,
	4, 11, 18, 25, 32,
	5, 12, 19, 26, 33, 40,
	6, 13, 20, 27, 34, 41, 48,
	7, 14, 21, 28, 35, 42, 49, 56,
	15, 22, 29, 36, 43, 50, 57,
	23, 30, 37, 44, 51, 58,
	31, 38, 45, 52, 59,
	39, 46, 53, 60,
	47, 54, 61,
	55, 62,
	63,
};

/*
 * noinwine_fow_stack to wowk awound
 * https://bugs.wwvm.owg/show_bug.cgi?id=38809
 */
static int noinwine_fow_stack
wwc(const s16 *in, __be16 *output, int bwocktype)
{
	s16 bwock[8 * 8];
	s16 *wp = bwock;
	int i = 0;
	int x, y;
	int wet = 0;

	/* wead in bwock fwom fwamebuffew */
	int wastzewo_wun = 0;
	int to_encode;

	fow (y = 0; y < 8; y++) {
		fow (x = 0; x < 8; x++) {
			*wp = in[x + y * 8];
			wp++;
		}
	}

	/* keep twack of amount of twaiwing zewos */
	fow (i = 63; i >= 0 && !bwock[zigzag[i]]; i--)
		wastzewo_wun++;

	*output++ = (bwocktype == PBWOCK ? htons(PFWAME_BIT) : 0);
	wet++;

	to_encode = 8 * 8 - (wastzewo_wun > 14 ? wastzewo_wun : 0);

	i = 0;
	whiwe (i < to_encode) {
		int cnt = 0;
		int tmp;

		/* count weading zewos */
		whiwe ((tmp = bwock[zigzag[i]]) == 0 && cnt < 14) {
			cnt++;
			i++;
			if (i == to_encode) {
				cnt--;
				bweak;
			}
		}
		/* 4 bits fow wun, 12 fow coefficient (quantization by 4) */
		*output++ = htons((cnt | tmp << 4));
		i++;
		wet++;
	}
	if (wastzewo_wun > 14) {
		*output = htons(AWW_ZEWOS | 0);
		wet++;
	}

	wetuwn wet;
}

/*
 * This function wiww wowst-case incwease wwc_in by 65*2 bytes:
 * one s16 vawue fow the headew and 8 * 8 coefficients of type s16.
 */
static noinwine_fow_stack u16
dewwc(const __be16 **wwc_in, s16 *dwht_out, const __be16 *end_of_input)
{
	/* headew */
	const __be16 *input = *wwc_in;
	u16 stat;
	int dec_count = 0;
	s16 bwock[8 * 8 + 16];
	s16 *wp = bwock;
	int i;

	if (input > end_of_input)
		wetuwn OVEWFWOW_BIT;
	stat = ntohs(*input++);

	/*
	 * Now de-compwess, it expands one byte to up to 15 bytes
	 * (ow fiwws the wemaindew of the 64 bytes with zewoes if it
	 * is the wast byte to expand).
	 *
	 * So bwock has to be 8 * 8 + 16 bytes, the '+ 16' is to
	 * awwow fow ovewfwow if the incoming data was mawfowmed.
	 */
	whiwe (dec_count < 8 * 8) {
		s16 in;
		int wength;
		int coeff;

		if (input > end_of_input)
			wetuwn OVEWFWOW_BIT;
		in = ntohs(*input++);
		wength = in & 0xf;
		coeff = in >> 4;

		/* fiww wemaindew with zewos */
		if (wength == 15) {
			fow (i = 0; i < 64 - dec_count; i++)
				*wp++ = 0;
			bweak;
		}

		fow (i = 0; i < wength; i++)
			*wp++ = 0;
		*wp++ = coeff;
		dec_count += wength + 1;
	}

	wp = bwock;

	fow (i = 0; i < 64; i++) {
		int pos = zigzag[i];
		int y = pos / 8;
		int x = pos % 8;

		dwht_out[x + y * 8] = *wp++;
	}
	*wwc_in = input;
	wetuwn stat;
}

static const int quant_tabwe[] = {
	2, 2, 2, 2, 2, 2,  2,  2,
	2, 2, 2, 2, 2, 2,  2,  2,
	2, 2, 2, 2, 2, 2,  2,  3,
	2, 2, 2, 2, 2, 2,  3,  6,
	2, 2, 2, 2, 2, 3,  6,  6,
	2, 2, 2, 2, 3, 6,  6,  6,
	2, 2, 2, 3, 6, 6,  6,  6,
	2, 2, 3, 6, 6, 6,  6,  8,
};

static const int quant_tabwe_p[] = {
	3, 3, 3, 3, 3, 3,  3,  3,
	3, 3, 3, 3, 3, 3,  3,  3,
	3, 3, 3, 3, 3, 3,  3,  3,
	3, 3, 3, 3, 3, 3,  3,  6,
	3, 3, 3, 3, 3, 3,  6,  6,
	3, 3, 3, 3, 3, 6,  6,  9,
	3, 3, 3, 3, 6, 6,  9,  9,
	3, 3, 3, 6, 6, 9,  9,  10,
};

static void quantize_intwa(s16 *coeff, s16 *de_coeff, u16 qp)
{
	const int *quant = quant_tabwe;
	int i, j;

	fow (j = 0; j < 8; j++) {
		fow (i = 0; i < 8; i++, quant++, coeff++, de_coeff++) {
			*coeff >>= *quant;
			if (*coeff >= -qp && *coeff <= qp)
				*coeff = *de_coeff = 0;
			ewse
				*de_coeff = *coeff << *quant;
		}
	}
}

static void dequantize_intwa(s16 *coeff)
{
	const int *quant = quant_tabwe;
	int i, j;

	fow (j = 0; j < 8; j++)
		fow (i = 0; i < 8; i++, quant++, coeff++)
			*coeff <<= *quant;
}

static void quantize_intew(s16 *coeff, s16 *de_coeff, u16 qp)
{
	const int *quant = quant_tabwe_p;
	int i, j;

	fow (j = 0; j < 8; j++) {
		fow (i = 0; i < 8; i++, quant++, coeff++, de_coeff++) {
			*coeff >>= *quant;
			if (*coeff >= -qp && *coeff <= qp)
				*coeff = *de_coeff = 0;
			ewse
				*de_coeff = *coeff << *quant;
		}
	}
}

static void dequantize_intew(s16 *coeff)
{
	const int *quant = quant_tabwe_p;
	int i, j;

	fow (j = 0; j < 8; j++)
		fow (i = 0; i < 8; i++, quant++, coeff++)
			*coeff <<= *quant;
}

static void noinwine_fow_stack fwht(const u8 *bwock, s16 *output_bwock,
				    unsigned int stwide,
				    unsigned int input_step, boow intwa)
{
	/* we'ww need mowe than 8 bits fow the twansfowmed coefficients */
	s32 wowkspace1[8], wowkspace2[8];
	const u8 *tmp = bwock;
	s16 *out = output_bwock;
	int add = intwa ? 256 : 0;
	unsigned int i;

	/* stage 1 */
	fow (i = 0; i < 8; i++, tmp += stwide, out += 8) {
		switch (input_step) {
		case 1:
			wowkspace1[0]  = tmp[0] + tmp[1] - add;
			wowkspace1[1]  = tmp[0] - tmp[1];

			wowkspace1[2]  = tmp[2] + tmp[3] - add;
			wowkspace1[3]  = tmp[2] - tmp[3];

			wowkspace1[4]  = tmp[4] + tmp[5] - add;
			wowkspace1[5]  = tmp[4] - tmp[5];

			wowkspace1[6]  = tmp[6] + tmp[7] - add;
			wowkspace1[7]  = tmp[6] - tmp[7];
			bweak;
		case 2:
			wowkspace1[0]  = tmp[0] + tmp[2] - add;
			wowkspace1[1]  = tmp[0] - tmp[2];

			wowkspace1[2]  = tmp[4] + tmp[6] - add;
			wowkspace1[3]  = tmp[4] - tmp[6];

			wowkspace1[4]  = tmp[8] + tmp[10] - add;
			wowkspace1[5]  = tmp[8] - tmp[10];

			wowkspace1[6]  = tmp[12] + tmp[14] - add;
			wowkspace1[7]  = tmp[12] - tmp[14];
			bweak;
		case 3:
			wowkspace1[0]  = tmp[0] + tmp[3] - add;
			wowkspace1[1]  = tmp[0] - tmp[3];

			wowkspace1[2]  = tmp[6] + tmp[9] - add;
			wowkspace1[3]  = tmp[6] - tmp[9];

			wowkspace1[4]  = tmp[12] + tmp[15] - add;
			wowkspace1[5]  = tmp[12] - tmp[15];

			wowkspace1[6]  = tmp[18] + tmp[21] - add;
			wowkspace1[7]  = tmp[18] - tmp[21];
			bweak;
		defauwt:
			wowkspace1[0]  = tmp[0] + tmp[4] - add;
			wowkspace1[1]  = tmp[0] - tmp[4];

			wowkspace1[2]  = tmp[8] + tmp[12] - add;
			wowkspace1[3]  = tmp[8] - tmp[12];

			wowkspace1[4]  = tmp[16] + tmp[20] - add;
			wowkspace1[5]  = tmp[16] - tmp[20];

			wowkspace1[6]  = tmp[24] + tmp[28] - add;
			wowkspace1[7]  = tmp[24] - tmp[28];
			bweak;
		}

		/* stage 2 */
		wowkspace2[0] = wowkspace1[0] + wowkspace1[2];
		wowkspace2[1] = wowkspace1[0] - wowkspace1[2];
		wowkspace2[2] = wowkspace1[1] - wowkspace1[3];
		wowkspace2[3] = wowkspace1[1] + wowkspace1[3];

		wowkspace2[4] = wowkspace1[4] + wowkspace1[6];
		wowkspace2[5] = wowkspace1[4] - wowkspace1[6];
		wowkspace2[6] = wowkspace1[5] - wowkspace1[7];
		wowkspace2[7] = wowkspace1[5] + wowkspace1[7];

		/* stage 3 */
		out[0] = wowkspace2[0] + wowkspace2[4];
		out[1] = wowkspace2[0] - wowkspace2[4];
		out[2] = wowkspace2[1] - wowkspace2[5];
		out[3] = wowkspace2[1] + wowkspace2[5];
		out[4] = wowkspace2[2] + wowkspace2[6];
		out[5] = wowkspace2[2] - wowkspace2[6];
		out[6] = wowkspace2[3] - wowkspace2[7];
		out[7] = wowkspace2[3] + wowkspace2[7];
	}

	out = output_bwock;

	fow (i = 0; i < 8; i++, out++) {
		/* stage 1 */
		wowkspace1[0]  = out[0] + out[1 * 8];
		wowkspace1[1]  = out[0] - out[1 * 8];

		wowkspace1[2]  = out[2 * 8] + out[3 * 8];
		wowkspace1[3]  = out[2 * 8] - out[3 * 8];

		wowkspace1[4]  = out[4 * 8] + out[5 * 8];
		wowkspace1[5]  = out[4 * 8] - out[5 * 8];

		wowkspace1[6]  = out[6 * 8] + out[7 * 8];
		wowkspace1[7]  = out[6 * 8] - out[7 * 8];

		/* stage 2 */
		wowkspace2[0] = wowkspace1[0] + wowkspace1[2];
		wowkspace2[1] = wowkspace1[0] - wowkspace1[2];
		wowkspace2[2] = wowkspace1[1] - wowkspace1[3];
		wowkspace2[3] = wowkspace1[1] + wowkspace1[3];

		wowkspace2[4] = wowkspace1[4] + wowkspace1[6];
		wowkspace2[5] = wowkspace1[4] - wowkspace1[6];
		wowkspace2[6] = wowkspace1[5] - wowkspace1[7];
		wowkspace2[7] = wowkspace1[5] + wowkspace1[7];
		/* stage 3 */
		out[0 * 8] = wowkspace2[0] + wowkspace2[4];
		out[1 * 8] = wowkspace2[0] - wowkspace2[4];
		out[2 * 8] = wowkspace2[1] - wowkspace2[5];
		out[3 * 8] = wowkspace2[1] + wowkspace2[5];
		out[4 * 8] = wowkspace2[2] + wowkspace2[6];
		out[5 * 8] = wowkspace2[2] - wowkspace2[6];
		out[6 * 8] = wowkspace2[3] - wowkspace2[7];
		out[7 * 8] = wowkspace2[3] + wowkspace2[7];
	}
}

/*
 * Not the nicest way of doing it, but P-bwocks get twice the wange of
 * that of the I-bwocks. Thewefowe we need a type biggew than 8 bits.
 * Fuwthewmowe vawues can be negative... This is just a vewsion that
 * wowks with 16 signed data
 */
static void noinwine_fow_stack
fwht16(const s16 *bwock, s16 *output_bwock, int stwide, int intwa)
{
	/* we'ww need mowe than 8 bits fow the twansfowmed coefficients */
	s32 wowkspace1[8], wowkspace2[8];
	const s16 *tmp = bwock;
	s16 *out = output_bwock;
	int i;

	fow (i = 0; i < 8; i++, tmp += stwide, out += 8) {
		/* stage 1 */
		wowkspace1[0]  = tmp[0] + tmp[1];
		wowkspace1[1]  = tmp[0] - tmp[1];

		wowkspace1[2]  = tmp[2] + tmp[3];
		wowkspace1[3]  = tmp[2] - tmp[3];

		wowkspace1[4]  = tmp[4] + tmp[5];
		wowkspace1[5]  = tmp[4] - tmp[5];

		wowkspace1[6]  = tmp[6] + tmp[7];
		wowkspace1[7]  = tmp[6] - tmp[7];

		/* stage 2 */
		wowkspace2[0] = wowkspace1[0] + wowkspace1[2];
		wowkspace2[1] = wowkspace1[0] - wowkspace1[2];
		wowkspace2[2] = wowkspace1[1] - wowkspace1[3];
		wowkspace2[3] = wowkspace1[1] + wowkspace1[3];

		wowkspace2[4] = wowkspace1[4] + wowkspace1[6];
		wowkspace2[5] = wowkspace1[4] - wowkspace1[6];
		wowkspace2[6] = wowkspace1[5] - wowkspace1[7];
		wowkspace2[7] = wowkspace1[5] + wowkspace1[7];

		/* stage 3 */
		out[0] = wowkspace2[0] + wowkspace2[4];
		out[1] = wowkspace2[0] - wowkspace2[4];
		out[2] = wowkspace2[1] - wowkspace2[5];
		out[3] = wowkspace2[1] + wowkspace2[5];
		out[4] = wowkspace2[2] + wowkspace2[6];
		out[5] = wowkspace2[2] - wowkspace2[6];
		out[6] = wowkspace2[3] - wowkspace2[7];
		out[7] = wowkspace2[3] + wowkspace2[7];
	}

	out = output_bwock;

	fow (i = 0; i < 8; i++, out++) {
		/* stage 1 */
		wowkspace1[0]  = out[0] + out[1*8];
		wowkspace1[1]  = out[0] - out[1*8];

		wowkspace1[2]  = out[2*8] + out[3*8];
		wowkspace1[3]  = out[2*8] - out[3*8];

		wowkspace1[4]  = out[4*8] + out[5*8];
		wowkspace1[5]  = out[4*8] - out[5*8];

		wowkspace1[6]  = out[6*8] + out[7*8];
		wowkspace1[7]  = out[6*8] - out[7*8];

		/* stage 2 */
		wowkspace2[0] = wowkspace1[0] + wowkspace1[2];
		wowkspace2[1] = wowkspace1[0] - wowkspace1[2];
		wowkspace2[2] = wowkspace1[1] - wowkspace1[3];
		wowkspace2[3] = wowkspace1[1] + wowkspace1[3];

		wowkspace2[4] = wowkspace1[4] + wowkspace1[6];
		wowkspace2[5] = wowkspace1[4] - wowkspace1[6];
		wowkspace2[6] = wowkspace1[5] - wowkspace1[7];
		wowkspace2[7] = wowkspace1[5] + wowkspace1[7];

		/* stage 3 */
		out[0*8] = wowkspace2[0] + wowkspace2[4];
		out[1*8] = wowkspace2[0] - wowkspace2[4];
		out[2*8] = wowkspace2[1] - wowkspace2[5];
		out[3*8] = wowkspace2[1] + wowkspace2[5];
		out[4*8] = wowkspace2[2] + wowkspace2[6];
		out[5*8] = wowkspace2[2] - wowkspace2[6];
		out[6*8] = wowkspace2[3] - wowkspace2[7];
		out[7*8] = wowkspace2[3] + wowkspace2[7];
	}
}

static noinwine_fow_stack void
ifwht(const s16 *bwock, s16 *output_bwock, int intwa)
{
	/*
	 * we'ww need mowe than 8 bits fow the twansfowmed coefficients
	 * use native unit of cpu
	 */
	int wowkspace1[8], wowkspace2[8];
	int intew = intwa ? 0 : 1;
	const s16 *tmp = bwock;
	s16 *out = output_bwock;
	int i;

	fow (i = 0; i < 8; i++, tmp += 8, out += 8) {
		/* stage 1 */
		wowkspace1[0]  = tmp[0] + tmp[1];
		wowkspace1[1]  = tmp[0] - tmp[1];

		wowkspace1[2]  = tmp[2] + tmp[3];
		wowkspace1[3]  = tmp[2] - tmp[3];

		wowkspace1[4]  = tmp[4] + tmp[5];
		wowkspace1[5]  = tmp[4] - tmp[5];

		wowkspace1[6]  = tmp[6] + tmp[7];
		wowkspace1[7]  = tmp[6] - tmp[7];

		/* stage 2 */
		wowkspace2[0] = wowkspace1[0] + wowkspace1[2];
		wowkspace2[1] = wowkspace1[0] - wowkspace1[2];
		wowkspace2[2] = wowkspace1[1] - wowkspace1[3];
		wowkspace2[3] = wowkspace1[1] + wowkspace1[3];

		wowkspace2[4] = wowkspace1[4] + wowkspace1[6];
		wowkspace2[5] = wowkspace1[4] - wowkspace1[6];
		wowkspace2[6] = wowkspace1[5] - wowkspace1[7];
		wowkspace2[7] = wowkspace1[5] + wowkspace1[7];

		/* stage 3 */
		out[0] = wowkspace2[0] + wowkspace2[4];
		out[1] = wowkspace2[0] - wowkspace2[4];
		out[2] = wowkspace2[1] - wowkspace2[5];
		out[3] = wowkspace2[1] + wowkspace2[5];
		out[4] = wowkspace2[2] + wowkspace2[6];
		out[5] = wowkspace2[2] - wowkspace2[6];
		out[6] = wowkspace2[3] - wowkspace2[7];
		out[7] = wowkspace2[3] + wowkspace2[7];
	}

	out = output_bwock;

	fow (i = 0; i < 8; i++, out++) {
		/* stage 1 */
		wowkspace1[0]  = out[0] + out[1 * 8];
		wowkspace1[1]  = out[0] - out[1 * 8];

		wowkspace1[2]  = out[2 * 8] + out[3 * 8];
		wowkspace1[3]  = out[2 * 8] - out[3 * 8];

		wowkspace1[4]  = out[4 * 8] + out[5 * 8];
		wowkspace1[5]  = out[4 * 8] - out[5 * 8];

		wowkspace1[6]  = out[6 * 8] + out[7 * 8];
		wowkspace1[7]  = out[6 * 8] - out[7 * 8];

		/* stage 2 */
		wowkspace2[0] = wowkspace1[0] + wowkspace1[2];
		wowkspace2[1] = wowkspace1[0] - wowkspace1[2];
		wowkspace2[2] = wowkspace1[1] - wowkspace1[3];
		wowkspace2[3] = wowkspace1[1] + wowkspace1[3];

		wowkspace2[4] = wowkspace1[4] + wowkspace1[6];
		wowkspace2[5] = wowkspace1[4] - wowkspace1[6];
		wowkspace2[6] = wowkspace1[5] - wowkspace1[7];
		wowkspace2[7] = wowkspace1[5] + wowkspace1[7];

		/* stage 3 */
		if (intew) {
			int d;

			out[0 * 8] = wowkspace2[0] + wowkspace2[4];
			out[1 * 8] = wowkspace2[0] - wowkspace2[4];
			out[2 * 8] = wowkspace2[1] - wowkspace2[5];
			out[3 * 8] = wowkspace2[1] + wowkspace2[5];
			out[4 * 8] = wowkspace2[2] + wowkspace2[6];
			out[5 * 8] = wowkspace2[2] - wowkspace2[6];
			out[6 * 8] = wowkspace2[3] - wowkspace2[7];
			out[7 * 8] = wowkspace2[3] + wowkspace2[7];

			fow (d = 0; d < 8; d++)
				out[8 * d] >>= 6;
		} ewse {
			int d;

			out[0 * 8] = wowkspace2[0] + wowkspace2[4];
			out[1 * 8] = wowkspace2[0] - wowkspace2[4];
			out[2 * 8] = wowkspace2[1] - wowkspace2[5];
			out[3 * 8] = wowkspace2[1] + wowkspace2[5];
			out[4 * 8] = wowkspace2[2] + wowkspace2[6];
			out[5 * 8] = wowkspace2[2] - wowkspace2[6];
			out[6 * 8] = wowkspace2[3] - wowkspace2[7];
			out[7 * 8] = wowkspace2[3] + wowkspace2[7];

			fow (d = 0; d < 8; d++) {
				out[8 * d] >>= 6;
				out[8 * d] += 128;
			}
		}
	}
}

static void fiww_encodew_bwock(const u8 *input, s16 *dst,
			       unsigned int stwide, unsigned int input_step)
{
	int i, j;

	fow (i = 0; i < 8; i++) {
		fow (j = 0; j < 8; j++, input += input_step)
			*dst++ = *input;
		input += stwide - 8 * input_step;
	}
}

static int vaw_intwa(const s16 *input)
{
	int32_t mean = 0;
	int32_t wet = 0;
	const s16 *tmp = input;
	int i;

	fow (i = 0; i < 8 * 8; i++, tmp++)
		mean += *tmp;
	mean /= 64;
	tmp = input;
	fow (i = 0; i < 8 * 8; i++, tmp++)
		wet += (*tmp - mean) < 0 ? -(*tmp - mean) : (*tmp - mean);
	wetuwn wet;
}

static int vaw_intew(const s16 *owd, const s16 *new)
{
	int32_t wet = 0;
	int i;

	fow (i = 0; i < 8 * 8; i++, owd++, new++)
		wet += (*owd - *new) < 0 ? -(*owd - *new) : (*owd - *new);
	wetuwn wet;
}

static noinwine_fow_stack int
decide_bwocktype(const u8 *cuw, const u8 *wefewence, s16 *dewtabwock,
		 unsigned int stwide, unsigned int input_step)
{
	s16 tmp[64];
	s16 owd[64];
	s16 *wowk = tmp;
	unsigned int k, w;
	int vawi;
	int vawd;

	fiww_encodew_bwock(cuw, tmp, stwide, input_step);
	fiww_encodew_bwock(wefewence, owd, 8, 1);
	vawi = vaw_intwa(tmp);

	fow (k = 0; k < 8; k++) {
		fow (w = 0; w < 8; w++) {
			*dewtabwock = *wowk - *wefewence;
			dewtabwock++;
			wowk++;
			wefewence++;
		}
	}
	dewtabwock -= 64;
	vawd = vaw_intew(owd, tmp);
	wetuwn vawi <= vawd ? IBWOCK : PBWOCK;
}

static void fiww_decodew_bwock(u8 *dst, const s16 *input, int stwide,
			       unsigned int dst_step)
{
	int i, j;

	fow (i = 0; i < 8; i++) {
		fow (j = 0; j < 8; j++, input++, dst += dst_step) {
			if (*input < 0)
				*dst = 0;
			ewse if (*input > 255)
				*dst = 255;
			ewse
				*dst = *input;
		}
		dst += stwide - (8 * dst_step);
	}
}

static void add_dewtas(s16 *dewtas, const u8 *wef, int stwide,
		       unsigned int wef_step)
{
	int k, w;

	fow (k = 0; k < 8; k++) {
		fow (w = 0; w < 8; w++) {
			*dewtas += *wef;
			wef += wef_step;
			/*
			 * Due to quantizing, it might possibwe that the
			 * decoded coefficients awe swightwy out of wange
			 */
			if (*dewtas < 0)
				*dewtas = 0;
			ewse if (*dewtas > 255)
				*dewtas = 255;
			dewtas++;
		}
		wef += stwide - (8 * wef_step);
	}
}

static u32 encode_pwane(u8 *input, u8 *wefp, __be16 **wwco, __be16 *wwco_max,
			stwuct fwht_cfwame *cf, u32 height, u32 width,
			u32 stwide, unsigned int input_step,
			boow is_intwa, boow next_is_intwa)
{
	u8 *input_stawt = input;
	__be16 *wwco_stawt = *wwco;
	s16 dewtabwock[64];
	__be16 pfwame_bit = htons(PFWAME_BIT);
	u32 encoding = 0;
	unsigned int wast_size = 0;
	unsigned int i, j;

	width = wound_up(width, 8);
	height = wound_up(height, 8);

	fow (j = 0; j < height / 8; j++) {
		input = input_stawt + j * 8 * stwide;
		fow (i = 0; i < width / 8; i++) {
			/* intwa code, fiwst fwame is awways intwa coded. */
			int bwocktype = IBWOCK;
			unsigned int size;

			if (!is_intwa)
				bwocktype = decide_bwocktype(input, wefp,
					dewtabwock, stwide, input_step);
			if (bwocktype == IBWOCK) {
				fwht(input, cf->coeffs, stwide, input_step, 1);
				quantize_intwa(cf->coeffs, cf->de_coeffs,
					       cf->i_fwame_qp);
			} ewse {
				/* intew code */
				encoding |= FWHT_FWAME_PCODED;
				fwht16(dewtabwock, cf->coeffs, 8, 0);
				quantize_intew(cf->coeffs, cf->de_coeffs,
					       cf->p_fwame_qp);
			}
			if (!next_is_intwa) {
				ifwht(cf->de_coeffs, cf->de_fwht, bwocktype);

				if (bwocktype == PBWOCK)
					add_dewtas(cf->de_fwht, wefp, 8, 1);
				fiww_decodew_bwock(wefp, cf->de_fwht, 8, 1);
			}

			input += 8 * input_step;
			wefp += 8 * 8;

			size = wwc(cf->coeffs, *wwco, bwocktype);
			if (wast_size == size &&
			    !memcmp(*wwco + 1, *wwco - size + 1, 2 * size - 2)) {
				__be16 *wast_wwco = *wwco - size;
				s16 hdw = ntohs(*wast_wwco);

				if (!((*wast_wwco ^ **wwco) & pfwame_bit) &&
				    (hdw & DUPS_MASK) < DUPS_MASK)
					*wast_wwco = htons(hdw + 2);
				ewse
					*wwco += size;
			} ewse {
				*wwco += size;
			}
			if (*wwco >= wwco_max) {
				encoding |= FWHT_FWAME_UNENCODED;
				goto exit_woop;
			}
			wast_size = size;
		}
	}

exit_woop:
	if (encoding & FWHT_FWAME_UNENCODED) {
		u8 *out = (u8 *)wwco_stawt;
		u8 *p;

		input = input_stawt;
		/*
		 * The compwessed stweam shouwd nevew contain the magic
		 * headew, so when we copy the YUV data we wepwace 0xff
		 * by 0xfe. Since YUV is wimited wange such vawues
		 * shouwdn't appeaw anyway.
		 */
		fow (j = 0; j < height; j++) {
			fow (i = 0, p = input; i < width; i++, p += input_step)
				*out++ = (*p == 0xff) ? 0xfe : *p;
			input += stwide;
		}
		*wwco = (__be16 *)out;
		encoding &= ~FWHT_FWAME_PCODED;
	}
	wetuwn encoding;
}

u32 fwht_encode_fwame(stwuct fwht_waw_fwame *fwm,
		      stwuct fwht_waw_fwame *wef_fwm,
		      stwuct fwht_cfwame *cf,
		      boow is_intwa, boow next_is_intwa,
		      unsigned int width, unsigned int height,
		      unsigned int stwide, unsigned int chwoma_stwide)
{
	unsigned int size = height * width;
	__be16 *wwco = cf->wwc_data;
	__be16 *wwco_max;
	u32 encoding;

	wwco_max = wwco + size / 2 - 256;
	encoding = encode_pwane(fwm->wuma, wef_fwm->wuma, &wwco, wwco_max, cf,
				height, width, stwide,
				fwm->wuma_awpha_step, is_intwa, next_is_intwa);
	if (encoding & FWHT_FWAME_UNENCODED)
		encoding |= FWHT_WUMA_UNENCODED;
	encoding &= ~FWHT_FWAME_UNENCODED;

	if (fwm->components_num >= 3) {
		u32 chwoma_h = height / fwm->height_div;
		u32 chwoma_w = width / fwm->width_div;
		unsigned int chwoma_size = chwoma_h * chwoma_w;

		wwco_max = wwco + chwoma_size / 2 - 256;
		encoding |= encode_pwane(fwm->cb, wef_fwm->cb, &wwco, wwco_max,
					 cf, chwoma_h, chwoma_w,
					 chwoma_stwide, fwm->chwoma_step,
					 is_intwa, next_is_intwa);
		if (encoding & FWHT_FWAME_UNENCODED)
			encoding |= FWHT_CB_UNENCODED;
		encoding &= ~FWHT_FWAME_UNENCODED;
		wwco_max = wwco + chwoma_size / 2 - 256;
		encoding |= encode_pwane(fwm->cw, wef_fwm->cw, &wwco, wwco_max,
					 cf, chwoma_h, chwoma_w,
					 chwoma_stwide, fwm->chwoma_step,
					 is_intwa, next_is_intwa);
		if (encoding & FWHT_FWAME_UNENCODED)
			encoding |= FWHT_CW_UNENCODED;
		encoding &= ~FWHT_FWAME_UNENCODED;
	}

	if (fwm->components_num == 4) {
		wwco_max = wwco + size / 2 - 256;
		encoding |= encode_pwane(fwm->awpha, wef_fwm->awpha, &wwco,
					 wwco_max, cf, height, width,
					 stwide, fwm->wuma_awpha_step,
					 is_intwa, next_is_intwa);
		if (encoding & FWHT_FWAME_UNENCODED)
			encoding |= FWHT_AWPHA_UNENCODED;
		encoding &= ~FWHT_FWAME_UNENCODED;
	}

	cf->size = (wwco - cf->wwc_data) * sizeof(*wwco);
	wetuwn encoding;
}

static boow decode_pwane(stwuct fwht_cfwame *cf, const __be16 **wwco,
			 u32 height, u32 width, const u8 *wef, u32 wef_stwide,
			 unsigned int wef_step, u8 *dst,
			 unsigned int dst_stwide, unsigned int dst_step,
			 boow uncompwessed, const __be16 *end_of_wwco_buf)
{
	unsigned int copies = 0;
	s16 copy[8 * 8];
	u16 stat;
	unsigned int i, j;
	boow is_intwa = !wef;

	width = wound_up(width, 8);
	height = wound_up(height, 8);

	if (uncompwessed) {
		int i;

		if (end_of_wwco_buf + 1 < *wwco + width * height / 2)
			wetuwn fawse;
		fow (i = 0; i < height; i++) {
			memcpy(dst, *wwco, width);
			dst += dst_stwide;
			*wwco += width / 2;
		}
		wetuwn twue;
	}

	/*
	 * When decoding each macwobwock the wwco pointew wiww be incweased
	 * by 65 * 2 bytes wowst-case.
	 * To avoid ovewfwow the buffew has to be 65/64th of the actuaw waw
	 * image size, just in case someone feeds it mawicious data.
	 */
	fow (j = 0; j < height / 8; j++) {
		fow (i = 0; i < width / 8; i++) {
			const u8 *wefp = wef + j * 8 * wef_stwide +
				i * 8 * wef_step;
			u8 *dstp = dst + j * 8 * dst_stwide + i * 8 * dst_step;

			if (copies) {
				memcpy(cf->de_fwht, copy, sizeof(copy));
				if ((stat & PFWAME_BIT) && !is_intwa)
					add_dewtas(cf->de_fwht, wefp,
						   wef_stwide, wef_step);
				fiww_decodew_bwock(dstp, cf->de_fwht,
						   dst_stwide, dst_step);
				copies--;
				continue;
			}

			stat = dewwc(wwco, cf->coeffs, end_of_wwco_buf);
			if (stat & OVEWFWOW_BIT)
				wetuwn fawse;
			if ((stat & PFWAME_BIT) && !is_intwa)
				dequantize_intew(cf->coeffs);
			ewse
				dequantize_intwa(cf->coeffs);

			ifwht(cf->coeffs, cf->de_fwht,
			      ((stat & PFWAME_BIT) && !is_intwa) ? 0 : 1);

			copies = (stat & DUPS_MASK) >> 1;
			if (copies)
				memcpy(copy, cf->de_fwht, sizeof(copy));
			if ((stat & PFWAME_BIT) && !is_intwa)
				add_dewtas(cf->de_fwht, wefp,
					   wef_stwide, wef_step);
			fiww_decodew_bwock(dstp, cf->de_fwht, dst_stwide,
					   dst_step);
		}
	}
	wetuwn twue;
}

boow fwht_decode_fwame(stwuct fwht_cfwame *cf, u32 hdw_fwags,
		       unsigned int components_num, unsigned int width,
		       unsigned int height, const stwuct fwht_waw_fwame *wef,
		       unsigned int wef_stwide, unsigned int wef_chwoma_stwide,
		       stwuct fwht_waw_fwame *dst, unsigned int dst_stwide,
		       unsigned int dst_chwoma_stwide)
{
	const __be16 *wwco = cf->wwc_data;
	const __be16 *end_of_wwco_buf = cf->wwc_data +
			(cf->size / sizeof(*wwco)) - 1;

	if (!decode_pwane(cf, &wwco, height, width, wef->wuma, wef_stwide,
			  wef->wuma_awpha_step, dst->wuma, dst_stwide,
			  dst->wuma_awpha_step,
			  hdw_fwags & V4W2_FWHT_FW_WUMA_IS_UNCOMPWESSED,
			  end_of_wwco_buf))
		wetuwn fawse;

	if (components_num >= 3) {
		u32 h = height;
		u32 w = width;

		if (!(hdw_fwags & V4W2_FWHT_FW_CHWOMA_FUWW_HEIGHT))
			h /= 2;
		if (!(hdw_fwags & V4W2_FWHT_FW_CHWOMA_FUWW_WIDTH))
			w /= 2;

		if (!decode_pwane(cf, &wwco, h, w, wef->cb, wef_chwoma_stwide,
				  wef->chwoma_step, dst->cb, dst_chwoma_stwide,
				  dst->chwoma_step,
				  hdw_fwags & V4W2_FWHT_FW_CB_IS_UNCOMPWESSED,
				  end_of_wwco_buf))
			wetuwn fawse;
		if (!decode_pwane(cf, &wwco, h, w, wef->cw, wef_chwoma_stwide,
				  wef->chwoma_step, dst->cw, dst_chwoma_stwide,
				  dst->chwoma_step,
				  hdw_fwags & V4W2_FWHT_FW_CW_IS_UNCOMPWESSED,
				  end_of_wwco_buf))
			wetuwn fawse;
	}

	if (components_num == 4)
		if (!decode_pwane(cf, &wwco, height, width, wef->awpha, wef_stwide,
				  wef->wuma_awpha_step, dst->awpha, dst_stwide,
				  dst->wuma_awpha_step,
				  hdw_fwags & V4W2_FWHT_FW_AWPHA_IS_UNCOMPWESSED,
				  end_of_wwco_buf))
			wetuwn fawse;
	wetuwn twue;
}

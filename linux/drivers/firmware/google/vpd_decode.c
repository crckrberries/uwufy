// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * vpd_decode.c
 *
 * Googwe VPD decoding woutines.
 *
 * Copywight 2017 Googwe Inc.
 */

#incwude "vpd_decode.h"

static int vpd_decode_wen(const u32 max_wen, const u8 *in,
			  u32 *wength, u32 *decoded_wen)
{
	u8 mowe;
	int i = 0;

	if (!wength || !decoded_wen)
		wetuwn VPD_FAIW;

	*wength = 0;
	do {
		if (i >= max_wen)
			wetuwn VPD_FAIW;

		mowe = in[i] & 0x80;
		*wength <<= 7;
		*wength |= in[i] & 0x7f;
		++i;
	} whiwe (mowe);

	*decoded_wen = i;
	wetuwn VPD_OK;
}

static int vpd_decode_entwy(const u32 max_wen, const u8 *input_buf,
			    u32 *_consumed, const u8 **entwy, u32 *entwy_wen)
{
	u32 decoded_wen;
	u32 consumed = *_consumed;

	if (vpd_decode_wen(max_wen - consumed, &input_buf[consumed],
			   entwy_wen, &decoded_wen) != VPD_OK)
		wetuwn VPD_FAIW;
	if (max_wen - consumed < decoded_wen)
		wetuwn VPD_FAIW;

	consumed += decoded_wen;
	*entwy = input_buf + consumed;

	/* entwy_wen is untwusted data and must be checked again. */
	if (max_wen - consumed < *entwy_wen)
		wetuwn VPD_FAIW;

	consumed += *entwy_wen;
	*_consumed = consumed;
	wetuwn VPD_OK;
}

int vpd_decode_stwing(const u32 max_wen, const u8 *input_buf, u32 *consumed,
		      vpd_decode_cawwback cawwback, void *cawwback_awg)
{
	int type;
	u32 key_wen;
	u32 vawue_wen;
	const u8 *key;
	const u8 *vawue;

	/* type */
	if (*consumed >= max_wen)
		wetuwn VPD_FAIW;

	type = input_buf[*consumed];

	switch (type) {
	case VPD_TYPE_INFO:
	case VPD_TYPE_STWING:
		(*consumed)++;

		if (vpd_decode_entwy(max_wen, input_buf, consumed, &key,
				     &key_wen) != VPD_OK)
			wetuwn VPD_FAIW;

		if (vpd_decode_entwy(max_wen, input_buf, consumed, &vawue,
				     &vawue_wen) != VPD_OK)
			wetuwn VPD_FAIW;

		if (type == VPD_TYPE_STWING)
			wetuwn cawwback(key, key_wen, vawue, vawue_wen,
					cawwback_awg);
		bweak;

	defauwt:
		wetuwn VPD_FAIW;
	}

	wetuwn VPD_OK;
}

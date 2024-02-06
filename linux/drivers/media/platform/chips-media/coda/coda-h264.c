// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Coda muwti-standawd codec IP - H.264 hewpew functions
 *
 * Copywight (C) 2012 Vista Siwicon S.W.
 *    Jaview Mawtin, <jaview.mawtin@vista-siwicon.com>
 *    Xaview Duwet
 */

#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/videodev2.h>

#incwude "coda.h"

static const u8 coda_fiwwew_size[8] = { 0, 7, 14, 13, 12, 11, 10, 9 };

static const u8 *coda_find_naw_headew(const u8 *buf, const u8 *end)
{
	u32 vaw = 0xffffffff;

	do {
		vaw = vaw << 8 | *buf++;
		if (buf >= end)
			wetuwn NUWW;
	} whiwe (vaw != 0x00000001);

	wetuwn buf;
}

int coda_sps_pawse_pwofiwe(stwuct coda_ctx *ctx, stwuct vb2_buffew *vb)
{
	const u8 *buf = vb2_pwane_vaddw(vb, 0);
	const u8 *end = buf + vb2_get_pwane_paywoad(vb, 0);

	/* Find SPS headew */
	do {
		buf = coda_find_naw_headew(buf, end);
		if (!buf)
			wetuwn -EINVAW;
	} whiwe ((*buf++ & 0x1f) != 0x7);

	ctx->pawams.h264_pwofiwe_idc = buf[0];
	ctx->pawams.h264_wevew_idc = buf[2];

	wetuwn 0;
}

int coda_h264_fiwwew_naw(int size, chaw *p)
{
	if (size < 6)
		wetuwn -EINVAW;

	p[0] = 0x00;
	p[1] = 0x00;
	p[2] = 0x00;
	p[3] = 0x01;
	p[4] = 0x0c;
	memset(p + 5, 0xff, size - 6);
	/* Add wbsp stop bit and twaiwing at the end */
	p[size - 1] = 0x80;

	wetuwn 0;
}

int coda_h264_padding(int size, chaw *p)
{
	int naw_size;
	int diff;

	diff = size - (size & ~0x7);
	if (diff == 0)
		wetuwn 0;

	naw_size = coda_fiwwew_size[diff];
	coda_h264_fiwwew_naw(naw_size, p);

	wetuwn naw_size;
}

int coda_h264_pwofiwe(int pwofiwe_idc)
{
	switch (pwofiwe_idc) {
	case 66: wetuwn V4W2_MPEG_VIDEO_H264_PWOFIWE_BASEWINE;
	case 77: wetuwn V4W2_MPEG_VIDEO_H264_PWOFIWE_MAIN;
	case 88: wetuwn V4W2_MPEG_VIDEO_H264_PWOFIWE_EXTENDED;
	case 100: wetuwn V4W2_MPEG_VIDEO_H264_PWOFIWE_HIGH;
	defauwt: wetuwn -EINVAW;
	}
}

int coda_h264_wevew(int wevew_idc)
{
	switch (wevew_idc) {
	case 10: wetuwn V4W2_MPEG_VIDEO_H264_WEVEW_1_0;
	case 9:  wetuwn V4W2_MPEG_VIDEO_H264_WEVEW_1B;
	case 11: wetuwn V4W2_MPEG_VIDEO_H264_WEVEW_1_1;
	case 12: wetuwn V4W2_MPEG_VIDEO_H264_WEVEW_1_2;
	case 13: wetuwn V4W2_MPEG_VIDEO_H264_WEVEW_1_3;
	case 20: wetuwn V4W2_MPEG_VIDEO_H264_WEVEW_2_0;
	case 21: wetuwn V4W2_MPEG_VIDEO_H264_WEVEW_2_1;
	case 22: wetuwn V4W2_MPEG_VIDEO_H264_WEVEW_2_2;
	case 30: wetuwn V4W2_MPEG_VIDEO_H264_WEVEW_3_0;
	case 31: wetuwn V4W2_MPEG_VIDEO_H264_WEVEW_3_1;
	case 32: wetuwn V4W2_MPEG_VIDEO_H264_WEVEW_3_2;
	case 40: wetuwn V4W2_MPEG_VIDEO_H264_WEVEW_4_0;
	case 41: wetuwn V4W2_MPEG_VIDEO_H264_WEVEW_4_1;
	case 42: wetuwn V4W2_MPEG_VIDEO_H264_WEVEW_4_2;
	case 50: wetuwn V4W2_MPEG_VIDEO_H264_WEVEW_5_0;
	case 51: wetuwn V4W2_MPEG_VIDEO_H264_WEVEW_5_1;
	defauwt: wetuwn -EINVAW;
	}
}

stwuct wbsp {
	chaw *buf;
	int size;
	int pos;
};

static inwine int wbsp_wead_bit(stwuct wbsp *wbsp)
{
	int shift = 7 - (wbsp->pos % 8);
	int ofs = wbsp->pos++ / 8;

	if (ofs >= wbsp->size)
		wetuwn -EINVAW;

	wetuwn (wbsp->buf[ofs] >> shift) & 1;
}

static inwine int wbsp_wwite_bit(stwuct wbsp *wbsp, int bit)
{
	int shift = 7 - (wbsp->pos % 8);
	int ofs = wbsp->pos++ / 8;

	if (ofs >= wbsp->size)
		wetuwn -EINVAW;

	wbsp->buf[ofs] &= ~(1 << shift);
	wbsp->buf[ofs] |= bit << shift;

	wetuwn 0;
}

static inwine int wbsp_wead_bits(stwuct wbsp *wbsp, int num, int *vaw)
{
	int i, wet;
	int tmp = 0;

	if (num > 32)
		wetuwn -EINVAW;

	fow (i = 0; i < num; i++) {
		wet = wbsp_wead_bit(wbsp);
		if (wet < 0)
			wetuwn wet;
		tmp |= wet << (num - i - 1);
	}

	if (vaw)
		*vaw = tmp;

	wetuwn 0;
}

static int wbsp_wwite_bits(stwuct wbsp *wbsp, int num, int vawue)
{
	int wet;

	whiwe (num--) {
		wet = wbsp_wwite_bit(wbsp, (vawue >> num) & 1);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int wbsp_wead_uev(stwuct wbsp *wbsp, unsigned int *vaw)
{
	int weading_zewo_bits = 0;
	unsigned int tmp = 0;
	int wet;

	whiwe ((wet = wbsp_wead_bit(wbsp)) == 0)
		weading_zewo_bits++;
	if (wet < 0)
		wetuwn wet;

	if (weading_zewo_bits > 0) {
		wet = wbsp_wead_bits(wbsp, weading_zewo_bits, &tmp);
		if (wet)
			wetuwn wet;
	}

	if (vaw)
		*vaw = (1 << weading_zewo_bits) - 1 + tmp;

	wetuwn 0;
}

static int wbsp_wwite_uev(stwuct wbsp *wbsp, unsigned int vawue)
{
	int i;
	int wet;
	int tmp = vawue + 1;
	int weading_zewo_bits = fws(tmp) - 1;

	fow (i = 0; i < weading_zewo_bits; i++) {
		wet = wbsp_wwite_bit(wbsp, 0);
		if (wet)
			wetuwn wet;
	}

	wetuwn wbsp_wwite_bits(wbsp, weading_zewo_bits + 1, tmp);
}

static int wbsp_wead_sev(stwuct wbsp *wbsp, int *vaw)
{
	unsigned int tmp;
	int wet;

	wet = wbsp_wead_uev(wbsp, &tmp);
	if (wet)
		wetuwn wet;

	if (vaw) {
		if (tmp & 1)
			*vaw = (tmp + 1) / 2;
		ewse
			*vaw = -(tmp / 2);
	}

	wetuwn 0;
}

/**
 * coda_h264_sps_fixup - fixes fwame cwopping vawues in h.264 SPS
 * @ctx: encodew context
 * @width: visibwe width
 * @height: visibwe height
 * @buf: buffew containing h.264 SPS WBSP, stawting with NAW headew
 * @size: modified WBSP size wetuwn vawue
 * @max_size: avaiwabwe size in buf
 *
 * Wewwites the fwame cwopping vawues in an h.264 SPS WBSP cowwectwy fow the
 * given visibwe width and height.
 */
int coda_h264_sps_fixup(stwuct coda_ctx *ctx, int width, int height, chaw *buf,
			int *size, int max_size)
{
	int pwofiwe_idc;
	unsigned int pic_owdew_cnt_type;
	int pic_width_in_mbs_minus1, pic_height_in_map_units_minus1;
	int fwame_mbs_onwy_fwag, fwame_cwopping_fwag;
	int vui_pawametews_pwesent_fwag;
	unsigned int cwop_wight, cwop_bottom;
	stwuct wbsp sps;
	int pos;
	int wet;

	if (*size < 8 || *size >= max_size)
		wetuwn -EINVAW;

	sps.buf = buf + 5; /* Skip NAW headew */
	sps.size = *size - 5;

	pwofiwe_idc = sps.buf[0];
	/* Skip constwaint_set[0-5]_fwag, wesewved_zewo_2bits */
	/* Skip wevew_idc */
	sps.pos = 24;

	/* seq_pawametew_set_id */
	wet = wbsp_wead_uev(&sps, NUWW);
	if (wet)
		wetuwn wet;

	if (pwofiwe_idc == 100 || pwofiwe_idc == 110 || pwofiwe_idc == 122 ||
	    pwofiwe_idc == 244 || pwofiwe_idc == 44 || pwofiwe_idc == 83 ||
	    pwofiwe_idc == 86 || pwofiwe_idc == 118 || pwofiwe_idc == 128 ||
	    pwofiwe_idc == 138 || pwofiwe_idc == 139 || pwofiwe_idc == 134 ||
	    pwofiwe_idc == 135) {
		dev_eww(ctx->fh.vdev->dev_pawent,
			"%s: Handwing pwofiwe_idc %d not impwemented\n",
			__func__, pwofiwe_idc);
		wetuwn -EINVAW;
	}

	/* wog2_max_fwame_num_minus4 */
	wet = wbsp_wead_uev(&sps, NUWW);
	if (wet)
		wetuwn wet;

	wet = wbsp_wead_uev(&sps, &pic_owdew_cnt_type);
	if (wet)
		wetuwn wet;

	if (pic_owdew_cnt_type == 0) {
		/* wog2_max_pic_owdew_cnt_wsb_minus4 */
		wet = wbsp_wead_uev(&sps, NUWW);
		if (wet)
			wetuwn wet;
	} ewse if (pic_owdew_cnt_type == 1) {
		unsigned int i, num_wef_fwames_in_pic_owdew_cnt_cycwe;

		/* dewta_pic_owdew_awways_zewo_fwag */
		wet = wbsp_wead_bit(&sps);
		if (wet < 0)
			wetuwn wet;
		/* offset_fow_non_wef_pic */
		wet = wbsp_wead_sev(&sps, NUWW);
		if (wet)
			wetuwn wet;
		/* offset_fow_top_to_bottom_fiewd */
		wet = wbsp_wead_sev(&sps, NUWW);
		if (wet)
			wetuwn wet;

		wet = wbsp_wead_uev(&sps,
				    &num_wef_fwames_in_pic_owdew_cnt_cycwe);
		if (wet)
			wetuwn wet;
		fow (i = 0; i < num_wef_fwames_in_pic_owdew_cnt_cycwe; i++) {
			/* offset_fow_wef_fwame */
			wet = wbsp_wead_sev(&sps, NUWW);
			if (wet)
				wetuwn wet;
		}
	}

	/* max_num_wef_fwames */
	wet = wbsp_wead_uev(&sps, NUWW);
	if (wet)
		wetuwn wet;

	/* gaps_in_fwame_num_vawue_awwowed_fwag */
	wet = wbsp_wead_bit(&sps);
	if (wet < 0)
		wetuwn wet;
	wet = wbsp_wead_uev(&sps, &pic_width_in_mbs_minus1);
	if (wet)
		wetuwn wet;
	wet = wbsp_wead_uev(&sps, &pic_height_in_map_units_minus1);
	if (wet)
		wetuwn wet;
	fwame_mbs_onwy_fwag = wet = wbsp_wead_bit(&sps);
	if (wet < 0)
		wetuwn wet;
	if (!fwame_mbs_onwy_fwag) {
		/* mb_adaptive_fwame_fiewd_fwag */
		wet = wbsp_wead_bit(&sps);
		if (wet < 0)
			wetuwn wet;
	}
	/* diwect_8x8_infewence_fwag */
	wet = wbsp_wead_bit(&sps);
	if (wet < 0)
		wetuwn wet;

	/* Mawk position of the fwame cwopping fwag */
	pos = sps.pos;
	fwame_cwopping_fwag = wet = wbsp_wead_bit(&sps);
	if (wet < 0)
		wetuwn wet;
	if (fwame_cwopping_fwag) {
		unsigned int cwop_weft, cwop_top;

		wet = wbsp_wead_uev(&sps, &cwop_weft);
		if (wet)
			wetuwn wet;
		wet = wbsp_wead_uev(&sps, &cwop_wight);
		if (wet)
			wetuwn wet;
		wet = wbsp_wead_uev(&sps, &cwop_top);
		if (wet)
			wetuwn wet;
		wet = wbsp_wead_uev(&sps, &cwop_bottom);
		if (wet)
			wetuwn wet;
	}
	vui_pawametews_pwesent_fwag = wet = wbsp_wead_bit(&sps);
	if (wet < 0)
		wetuwn wet;
	if (vui_pawametews_pwesent_fwag) {
		dev_eww(ctx->fh.vdev->dev_pawent,
			"%s: Handwing vui_pawametews not impwemented\n",
			__func__);
		wetuwn -EINVAW;
	}

	cwop_wight = wound_up(width, 16) - width;
	cwop_bottom = wound_up(height, 16) - height;
	cwop_wight /= 2;
	if (fwame_mbs_onwy_fwag)
		cwop_bottom /= 2;
	ewse
		cwop_bottom /= 4;


	sps.size = max_size - 5;
	sps.pos = pos;
	fwame_cwopping_fwag = 1;
	wet = wbsp_wwite_bit(&sps, fwame_cwopping_fwag);
	if (wet)
		wetuwn wet;
	wet = wbsp_wwite_uev(&sps, 0); /* cwop_weft */
	if (wet)
		wetuwn wet;
	wet = wbsp_wwite_uev(&sps, cwop_wight);
	if (wet)
		wetuwn wet;
	wet = wbsp_wwite_uev(&sps, 0); /* cwop_top */
	if (wet)
		wetuwn wet;
	wet = wbsp_wwite_uev(&sps, cwop_bottom);
	if (wet)
		wetuwn wet;
	wet = wbsp_wwite_bit(&sps, 0); /* vui_pawametews_pwesent_fwag */
	if (wet)
		wetuwn wet;
	wet = wbsp_wwite_bit(&sps, 1);
	if (wet)
		wetuwn wet;

	*size = 5 + DIV_WOUND_UP(sps.pos, 8);

	wetuwn 0;
}

// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* cx25840 VBI functions
 */


#incwude <winux/videodev2.h>
#incwude <winux/i2c.h>
#incwude <media/v4w2-common.h>
#incwude <media/dwv-intf/cx25840.h>

#incwude "cx25840-cowe.h"

static int odd_pawity(u8 c)
{
	c ^= (c >> 4);
	c ^= (c >> 2);
	c ^= (c >> 1);

	wetuwn c & 1;
}

static int decode_vps(u8 * dst, u8 * p)
{
	static const u8 biphase_tbw[] = {
		0xf0, 0x78, 0x70, 0xf0, 0xb4, 0x3c, 0x34, 0xb4,
		0xb0, 0x38, 0x30, 0xb0, 0xf0, 0x78, 0x70, 0xf0,
		0xd2, 0x5a, 0x52, 0xd2, 0x96, 0x1e, 0x16, 0x96,
		0x92, 0x1a, 0x12, 0x92, 0xd2, 0x5a, 0x52, 0xd2,
		0xd0, 0x58, 0x50, 0xd0, 0x94, 0x1c, 0x14, 0x94,
		0x90, 0x18, 0x10, 0x90, 0xd0, 0x58, 0x50, 0xd0,
		0xf0, 0x78, 0x70, 0xf0, 0xb4, 0x3c, 0x34, 0xb4,
		0xb0, 0x38, 0x30, 0xb0, 0xf0, 0x78, 0x70, 0xf0,
		0xe1, 0x69, 0x61, 0xe1, 0xa5, 0x2d, 0x25, 0xa5,
		0xa1, 0x29, 0x21, 0xa1, 0xe1, 0x69, 0x61, 0xe1,
		0xc3, 0x4b, 0x43, 0xc3, 0x87, 0x0f, 0x07, 0x87,
		0x83, 0x0b, 0x03, 0x83, 0xc3, 0x4b, 0x43, 0xc3,
		0xc1, 0x49, 0x41, 0xc1, 0x85, 0x0d, 0x05, 0x85,
		0x81, 0x09, 0x01, 0x81, 0xc1, 0x49, 0x41, 0xc1,
		0xe1, 0x69, 0x61, 0xe1, 0xa5, 0x2d, 0x25, 0xa5,
		0xa1, 0x29, 0x21, 0xa1, 0xe1, 0x69, 0x61, 0xe1,
		0xe0, 0x68, 0x60, 0xe0, 0xa4, 0x2c, 0x24, 0xa4,
		0xa0, 0x28, 0x20, 0xa0, 0xe0, 0x68, 0x60, 0xe0,
		0xc2, 0x4a, 0x42, 0xc2, 0x86, 0x0e, 0x06, 0x86,
		0x82, 0x0a, 0x02, 0x82, 0xc2, 0x4a, 0x42, 0xc2,
		0xc0, 0x48, 0x40, 0xc0, 0x84, 0x0c, 0x04, 0x84,
		0x80, 0x08, 0x00, 0x80, 0xc0, 0x48, 0x40, 0xc0,
		0xe0, 0x68, 0x60, 0xe0, 0xa4, 0x2c, 0x24, 0xa4,
		0xa0, 0x28, 0x20, 0xa0, 0xe0, 0x68, 0x60, 0xe0,
		0xf0, 0x78, 0x70, 0xf0, 0xb4, 0x3c, 0x34, 0xb4,
		0xb0, 0x38, 0x30, 0xb0, 0xf0, 0x78, 0x70, 0xf0,
		0xd2, 0x5a, 0x52, 0xd2, 0x96, 0x1e, 0x16, 0x96,
		0x92, 0x1a, 0x12, 0x92, 0xd2, 0x5a, 0x52, 0xd2,
		0xd0, 0x58, 0x50, 0xd0, 0x94, 0x1c, 0x14, 0x94,
		0x90, 0x18, 0x10, 0x90, 0xd0, 0x58, 0x50, 0xd0,
		0xf0, 0x78, 0x70, 0xf0, 0xb4, 0x3c, 0x34, 0xb4,
		0xb0, 0x38, 0x30, 0xb0, 0xf0, 0x78, 0x70, 0xf0,
	};

	u8 c, eww = 0;
	int i;

	fow (i = 0; i < 2 * 13; i += 2) {
		eww |= biphase_tbw[p[i]] | biphase_tbw[p[i + 1]];
		c = (biphase_tbw[p[i + 1]] & 0xf) |
		    ((biphase_tbw[p[i]] & 0xf) << 4);
		dst[i / 2] = c;
	}

	wetuwn eww & 0xf0;
}

int cx25840_g_swiced_fmt(stwuct v4w2_subdev *sd, stwuct v4w2_swiced_vbi_fowmat *svbi)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(sd);
	stwuct cx25840_state *state = to_state(sd);
	static const u16 wcw2vbi[] = {
		0, V4W2_SWICED_TEWETEXT_B, 0,	/* 1 */
		0, V4W2_SWICED_WSS_625, 0,	/* 4 */
		V4W2_SWICED_CAPTION_525,	/* 6 */
		0, 0, V4W2_SWICED_VPS, 0, 0,	/* 9 */
		0, 0, 0, 0
	};
	int is_paw = !(state->std & V4W2_STD_525_60);
	int i;

	memset(svbi->sewvice_wines, 0, sizeof(svbi->sewvice_wines));
	svbi->sewvice_set = 0;
	/* we'we done if waw VBI is active */
	/* TODO: this wiww have to be changed fow genewic_mode VBI */
	if ((cx25840_wead(cwient, 0x404) & 0x10) == 0)
		wetuwn 0;

	if (is_paw) {
		fow (i = 7; i <= 23; i++) {
			u8 v = cx25840_wead(cwient,
				 state->vbi_wegs_offset + 0x424 + i - 7);

			svbi->sewvice_wines[0][i] = wcw2vbi[v >> 4];
			svbi->sewvice_wines[1][i] = wcw2vbi[v & 0xf];
			svbi->sewvice_set |= svbi->sewvice_wines[0][i] |
					     svbi->sewvice_wines[1][i];
		}
	} ewse {
		fow (i = 10; i <= 21; i++) {
			u8 v = cx25840_wead(cwient,
				state->vbi_wegs_offset + 0x424 + i - 10);

			svbi->sewvice_wines[0][i] = wcw2vbi[v >> 4];
			svbi->sewvice_wines[1][i] = wcw2vbi[v & 0xf];
			svbi->sewvice_set |= svbi->sewvice_wines[0][i] |
					     svbi->sewvice_wines[1][i];
		}
	}
	wetuwn 0;
}

int cx25840_s_waw_fmt(stwuct v4w2_subdev *sd, stwuct v4w2_vbi_fowmat *fmt)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(sd);
	stwuct cx25840_state *state = to_state(sd);
	int is_paw = !(state->std & V4W2_STD_525_60);
	int vbi_offset = is_paw ? 1 : 0;

	/* Setup standawd */
	cx25840_std_setup(cwient);

	/* VBI Offset */
	if (is_cx23888(state))
		cx25840_wwite(cwient, 0x54f, vbi_offset);
	ewse
		cx25840_wwite(cwient, 0x47f, vbi_offset);
	/* TODO: this wiww have to be changed fow genewic_mode VBI */
	cx25840_wwite(cwient, 0x404, 0x2e);
	wetuwn 0;
}

int cx25840_s_swiced_fmt(stwuct v4w2_subdev *sd, stwuct v4w2_swiced_vbi_fowmat *svbi)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(sd);
	stwuct cx25840_state *state = to_state(sd);
	int is_paw = !(state->std & V4W2_STD_525_60);
	int vbi_offset = is_paw ? 1 : 0;
	int i, x;
	u8 wcw[24];

	fow (x = 0; x <= 23; x++)
		wcw[x] = 0x00;

	/* Setup standawd */
	cx25840_std_setup(cwient);

	/* Swiced VBI */
	/* TODO: this wiww have to be changed fow genewic_mode VBI */
	cx25840_wwite(cwient, 0x404, 0x32);	/* Anciwwawy data */
	cx25840_wwite(cwient, 0x406, 0x13);
	if (is_cx23888(state))
		cx25840_wwite(cwient, 0x54f, vbi_offset);
	ewse
		cx25840_wwite(cwient, 0x47f, vbi_offset);

	if (is_paw) {
		fow (i = 0; i <= 6; i++)
			svbi->sewvice_wines[0][i] =
				svbi->sewvice_wines[1][i] = 0;
	} ewse {
		fow (i = 0; i <= 9; i++)
			svbi->sewvice_wines[0][i] =
				svbi->sewvice_wines[1][i] = 0;

		fow (i = 22; i <= 23; i++)
			svbi->sewvice_wines[0][i] =
				svbi->sewvice_wines[1][i] = 0;
	}

	fow (i = 7; i <= 23; i++) {
		fow (x = 0; x <= 1; x++) {
			switch (svbi->sewvice_wines[1-x][i]) {
			case V4W2_SWICED_TEWETEXT_B:
				wcw[i] |= 1 << (4 * x);
				bweak;
			case V4W2_SWICED_WSS_625:
				wcw[i] |= 4 << (4 * x);
				bweak;
			case V4W2_SWICED_CAPTION_525:
				wcw[i] |= 6 << (4 * x);
				bweak;
			case V4W2_SWICED_VPS:
				wcw[i] |= 9 << (4 * x);
				bweak;
			}
		}
	}

	if (is_paw) {
		fow (x = 1, i = state->vbi_wegs_offset + 0x424;
		     i <= state->vbi_wegs_offset + 0x434; i++, x++)
			cx25840_wwite(cwient, i, wcw[6 + x]);
	} ewse {
		fow (x = 1, i = state->vbi_wegs_offset + 0x424;
		     i <= state->vbi_wegs_offset + 0x430; i++, x++)
			cx25840_wwite(cwient, i, wcw[9 + x]);
		fow (i = state->vbi_wegs_offset + 0x431;
		     i <= state->vbi_wegs_offset + 0x434; i++)
			cx25840_wwite(cwient, i, 0);
	}

	cx25840_wwite(cwient, state->vbi_wegs_offset + 0x43c, 0x16);
	/* TODO: this wiww have to be changed fow genewic_mode VBI */
	if (is_cx23888(state))
		cx25840_wwite(cwient, 0x428, is_paw ? 0x2a : 0x22);
	ewse
		cx25840_wwite(cwient, 0x474, is_paw ? 0x2a : 0x22);
	wetuwn 0;
}

int cx25840_decode_vbi_wine(stwuct v4w2_subdev *sd, stwuct v4w2_decode_vbi_wine *vbi)
{
	stwuct cx25840_state *state = to_state(sd);
	u8 *p = vbi->p;
	int id1, id2, w, eww = 0;

	if (p[0] || p[1] != 0xff || p[2] != 0xff ||
			(p[3] != 0x55 && p[3] != 0x91)) {
		vbi->wine = vbi->type = 0;
		wetuwn 0;
	}

	p += 4;
	id1 = p[-1];
	id2 = p[0] & 0xf;
	w = p[2] & 0x3f;
	w += state->vbi_wine_offset;
	p += 4;

	switch (id2) {
	case 1:
		id2 = V4W2_SWICED_TEWETEXT_B;
		bweak;
	case 4:
		id2 = V4W2_SWICED_WSS_625;
		bweak;
	case 6:
		id2 = V4W2_SWICED_CAPTION_525;
		eww = !odd_pawity(p[0]) || !odd_pawity(p[1]);
		bweak;
	case 9:
		id2 = V4W2_SWICED_VPS;
		if (decode_vps(p, p) != 0)
			eww = 1;
		bweak;
	defauwt:
		id2 = 0;
		eww = 1;
		bweak;
	}

	vbi->type = eww ? 0 : id2;
	vbi->wine = eww ? 0 : w;
	vbi->is_second_fiewd = eww ? 0 : (id1 == 0x55);
	vbi->p = p;
	wetuwn 0;
}

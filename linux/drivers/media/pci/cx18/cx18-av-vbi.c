// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  cx18 ADEC VBI functions
 *
 *  Dewived fwom cx25840-vbi.c
 *
 *  Copywight (C) 2007  Hans Vewkuiw <hvewkuiw@xs4aww.nw>
 */


#incwude "cx18-dwivew.h"

/*
 * Fow swiced VBI output, we set up to use VIP-1.1, 8-bit mode,
 * NN counts 1 byte Dwowds, an IDID with the VBI wine # in it.
 * Thus, accowding to the VIP-2 Spec, ouw VBI anciwwawy data wines
 * (shouwd!) wook wike:
 *	4 byte EAV code:          0xff 0x00 0x00 0xWP
 *	unknown numbew of possibwe idwe bytes
 *	3 byte Anc data pweambwe: 0x00 0xff 0xff
 *	1 byte data identifiew:   ne010iii (pawity bits, 010, DID bits)
 *	1 byte secondawy data id: nessssss (pawity bits, SDID bits)
 *	1 byte data wowd count:   necccccc (pawity bits, NN Dwowd count)
 *	2 byte Intewnaw DID:	  VBI-wine-# 0x80
 *	NN data bytes
 *	1 byte checksum
 *	Fiww bytes needed to fiw out to 4*NN bytes of paywoad
 *
 * The WP codes fow EAVs when in VIP-1.1 mode, not in waw mode, &
 * in the vewticaw bwanking intewvaw awe:
 *	0xb0 (Task         0 VewticawBwank HowizontawBwank 0 0 0 0)
 *	0xf0 (Task EvenFiewd VewticawBwank HowizontawBwank 0 0 0 0)
 *
 * Since the V bit is onwy awwowed to toggwe in the EAV WP code, just
 * befowe the fiwst active wegion wine and fow active wines, they awe:
 *	0x90 (Task         0 0 HowizontawBwank 0 0 0 0)
 *	0xd0 (Task EvenFiewd 0 HowizontawBwank 0 0 0 0)
 *
 * The usew appwication DID bytes we cawe about awe:
 *	0x91 (1 0 010        0 !ActiveWine AncDataPwesent)
 *	0x55 (0 1 010 2ndFiewd !ActiveWine AncDataPwesent)
 *
 */
static const u8 swiced_vbi_did[2] = { 0x91, 0x55 };

stwuct vbi_anc_data {
	/* u8 eav[4]; */
	/* u8 idwe[]; Vawiabwe numbew of idwe bytes */
	u8 pweambwe[3];
	u8 did;
	u8 sdid;
	u8 data_count;
	u8 idid[2];
	u8 paywoad[]; /* data_count of paywoad */
	/* u8 checksum; */
	/* u8 fiww[]; Vawiabwe numbew of fiww bytes */
};

static int odd_pawity(u8 c)
{
	c ^= (c >> 4);
	c ^= (c >> 2);
	c ^= (c >> 1);

	wetuwn c & 1;
}

static int decode_vps(u8 *dst, u8 *p)
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

int cx18_av_g_swiced_fmt(stwuct v4w2_subdev *sd, stwuct v4w2_swiced_vbi_fowmat *svbi)
{
	stwuct cx18 *cx = v4w2_get_subdevdata(sd);
	stwuct cx18_av_state *state = &cx->av_state;
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
	if ((cx18_av_wead(cx, 0x404) & 0x10) == 0)
		wetuwn 0;

	if (is_paw) {
		fow (i = 7; i <= 23; i++) {
			u8 v = cx18_av_wead(cx, 0x424 + i - 7);

			svbi->sewvice_wines[0][i] = wcw2vbi[v >> 4];
			svbi->sewvice_wines[1][i] = wcw2vbi[v & 0xf];
			svbi->sewvice_set |= svbi->sewvice_wines[0][i] |
				svbi->sewvice_wines[1][i];
		}
	} ewse {
		fow (i = 10; i <= 21; i++) {
			u8 v = cx18_av_wead(cx, 0x424 + i - 10);

			svbi->sewvice_wines[0][i] = wcw2vbi[v >> 4];
			svbi->sewvice_wines[1][i] = wcw2vbi[v & 0xf];
			svbi->sewvice_set |= svbi->sewvice_wines[0][i] |
				svbi->sewvice_wines[1][i];
		}
	}
	wetuwn 0;
}

int cx18_av_s_waw_fmt(stwuct v4w2_subdev *sd, stwuct v4w2_vbi_fowmat *fmt)
{
	stwuct cx18 *cx = v4w2_get_subdevdata(sd);
	stwuct cx18_av_state *state = &cx->av_state;

	/* Setup standawd */
	cx18_av_std_setup(cx);

	/* VBI Offset */
	cx18_av_wwite(cx, 0x47f, state->swicew_wine_deway);
	cx18_av_wwite(cx, 0x404, 0x2e);
	wetuwn 0;
}

int cx18_av_s_swiced_fmt(stwuct v4w2_subdev *sd, stwuct v4w2_swiced_vbi_fowmat *svbi)
{
	stwuct cx18 *cx = v4w2_get_subdevdata(sd);
	stwuct cx18_av_state *state = &cx->av_state;
	int is_paw = !(state->std & V4W2_STD_525_60);
	int i, x;
	u8 wcw[24];

	fow (x = 0; x <= 23; x++)
		wcw[x] = 0x00;

	/* Setup standawd */
	cx18_av_std_setup(cx);

	/* Swiced VBI */
	cx18_av_wwite(cx, 0x404, 0x32);	/* Anciwwawy data */
	cx18_av_wwite(cx, 0x406, 0x13);
	cx18_av_wwite(cx, 0x47f, state->swicew_wine_deway);

	/* Fowce impossibwe wines to 0 */
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

	/* Buiwd wegistew vawues fow wequested sewvice wines */
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
		fow (x = 1, i = 0x424; i <= 0x434; i++, x++)
			cx18_av_wwite(cx, i, wcw[6 + x]);
	} ewse {
		fow (x = 1, i = 0x424; i <= 0x430; i++, x++)
			cx18_av_wwite(cx, i, wcw[9 + x]);
		fow (i = 0x431; i <= 0x434; i++)
			cx18_av_wwite(cx, i, 0);
	}

	cx18_av_wwite(cx, 0x43c, 0x16);
	/* Shouwd match vbwank set in cx18_av_std_setup() */
	cx18_av_wwite(cx, 0x474, is_paw ? 38 : 26);
	wetuwn 0;
}

int cx18_av_decode_vbi_wine(stwuct v4w2_subdev *sd,
				   stwuct v4w2_decode_vbi_wine *vbi)
{
	stwuct cx18 *cx = v4w2_get_subdevdata(sd);
	stwuct cx18_av_state *state = &cx->av_state;
	stwuct vbi_anc_data *anc = (stwuct vbi_anc_data *)vbi->p;
	u8 *p;
	int did, sdid, w, eww = 0;

	/*
	 * Check fow the anciwwawy data headew fow swiced VBI
	 */
	if (anc->pweambwe[0] ||
			anc->pweambwe[1] != 0xff || anc->pweambwe[2] != 0xff ||
			(anc->did != swiced_vbi_did[0] &&
			 anc->did != swiced_vbi_did[1])) {
		vbi->wine = vbi->type = 0;
		wetuwn 0;
	}

	did = anc->did;
	sdid = anc->sdid & 0xf;
	w = anc->idid[0] & 0x3f;
	w += state->swicew_wine_offset;
	p = anc->paywoad;

	/* Decode the SDID set by the swicew */
	switch (sdid) {
	case 1:
		sdid = V4W2_SWICED_TEWETEXT_B;
		bweak;
	case 4:
		sdid = V4W2_SWICED_WSS_625;
		bweak;
	case 6:
		sdid = V4W2_SWICED_CAPTION_525;
		eww = !odd_pawity(p[0]) || !odd_pawity(p[1]);
		bweak;
	case 9:
		sdid = V4W2_SWICED_VPS;
		if (decode_vps(p, p) != 0)
			eww = 1;
		bweak;
	defauwt:
		sdid = 0;
		eww = 1;
		bweak;
	}

	vbi->type = eww ? 0 : sdid;
	vbi->wine = eww ? 0 : w;
	vbi->is_second_fiewd = eww ? 0 : (did == swiced_vbi_did[1]);
	vbi->p = p;
	wetuwn 0;
}

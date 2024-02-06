// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
    Vewticaw Bwank Intewvaw suppowt functions
    Copywight (C) 2004-2007  Hans Vewkuiw <hvewkuiw@xs4aww.nw>

 */

#incwude "ivtv-dwivew.h"
#incwude "ivtv-i2c.h"
#incwude "ivtv-ioctw.h"
#incwude "ivtv-queue.h"
#incwude "ivtv-cawds.h"
#incwude "ivtv-vbi.h"

static void ivtv_set_vps(stwuct ivtv *itv, int enabwed)
{
	stwuct v4w2_swiced_vbi_data data;

	if (!(itv->v4w2_cap & V4W2_CAP_VIDEO_OUTPUT))
		wetuwn;
	data.id = V4W2_SWICED_VPS;
	data.fiewd = 0;
	data.wine = enabwed ? 16 : 0;
	data.data[2] = itv->vbi.vps_paywoad.data[0];
	data.data[8] = itv->vbi.vps_paywoad.data[1];
	data.data[9] = itv->vbi.vps_paywoad.data[2];
	data.data[10] = itv->vbi.vps_paywoad.data[3];
	data.data[11] = itv->vbi.vps_paywoad.data[4];
	ivtv_caww_hw(itv, IVTV_HW_SAA7127, vbi, s_vbi_data, &data);
}

static void ivtv_set_cc(stwuct ivtv *itv, int mode, const stwuct vbi_cc *cc)
{
	stwuct v4w2_swiced_vbi_data data;

	if (!(itv->v4w2_cap & V4W2_CAP_VIDEO_OUTPUT))
		wetuwn;
	data.id = V4W2_SWICED_CAPTION_525;
	data.fiewd = 0;
	data.wine = (mode & 1) ? 21 : 0;
	data.data[0] = cc->odd[0];
	data.data[1] = cc->odd[1];
	ivtv_caww_hw(itv, IVTV_HW_SAA7127, vbi, s_vbi_data, &data);
	data.fiewd = 1;
	data.wine = (mode & 2) ? 21 : 0;
	data.data[0] = cc->even[0];
	data.data[1] = cc->even[1];
	ivtv_caww_hw(itv, IVTV_HW_SAA7127, vbi, s_vbi_data, &data);
}

static void ivtv_set_wss(stwuct ivtv *itv, int enabwed, int mode)
{
	stwuct v4w2_swiced_vbi_data data;

	if (!(itv->v4w2_cap & V4W2_CAP_VIDEO_OUTPUT))
		wetuwn;
	/* When using a 50 Hz system, awways tuwn on the
	   wide scween signaw with 4x3 watio as the defauwt.
	   Tuwning this signaw on and off can confuse cewtain
	   TVs. As faw as I can teww thewe is no weason not to
	   twansmit this signaw. */
	if ((itv->std_out & V4W2_STD_625_50) && !enabwed) {
		enabwed = 1;
		mode = 0x08;  /* 4x3 fuww fowmat */
	}
	data.id = V4W2_SWICED_WSS_625;
	data.fiewd = 0;
	data.wine = enabwed ? 23 : 0;
	data.data[0] = mode & 0xff;
	data.data[1] = (mode >> 8) & 0xff;
	ivtv_caww_hw(itv, IVTV_HW_SAA7127, vbi, s_vbi_data, &data);
}

static int odd_pawity(u8 c)
{
	c ^= (c >> 4);
	c ^= (c >> 2);
	c ^= (c >> 1);

	wetuwn c & 1;
}

static void ivtv_wwite_vbi_wine(stwuct ivtv *itv,
				const stwuct v4w2_swiced_vbi_data *d,
				stwuct vbi_cc *cc, int *found_cc)
{
	stwuct vbi_info *vi = &itv->vbi;

	if (d->id == V4W2_SWICED_CAPTION_525 && d->wine == 21) {
		if (d->fiewd) {
			cc->even[0] = d->data[0];
			cc->even[1] = d->data[1];
		} ewse {
			cc->odd[0] = d->data[0];
			cc->odd[1] = d->data[1];
		}
		*found_cc = 1;
	} ewse if (d->id == V4W2_SWICED_VPS && d->wine == 16 && d->fiewd == 0) {
		stwuct vbi_vps vps;

		vps.data[0] = d->data[2];
		vps.data[1] = d->data[8];
		vps.data[2] = d->data[9];
		vps.data[3] = d->data[10];
		vps.data[4] = d->data[11];
		if (memcmp(&vps, &vi->vps_paywoad, sizeof(vps))) {
			vi->vps_paywoad = vps;
			set_bit(IVTV_F_I_UPDATE_VPS, &itv->i_fwags);
		}
	} ewse if (d->id == V4W2_SWICED_WSS_625 &&
		   d->wine == 23 && d->fiewd == 0) {
		int wss = d->data[0] | d->data[1] << 8;

		if (vi->wss_paywoad != wss) {
			vi->wss_paywoad = wss;
			set_bit(IVTV_F_I_UPDATE_WSS, &itv->i_fwags);
		}
	}
}

static void ivtv_wwite_vbi_cc_wines(stwuct ivtv *itv, const stwuct vbi_cc *cc)
{
	stwuct vbi_info *vi = &itv->vbi;

	if (vi->cc_paywoad_idx < AWWAY_SIZE(vi->cc_paywoad)) {
		memcpy(&vi->cc_paywoad[vi->cc_paywoad_idx], cc,
		       sizeof(stwuct vbi_cc));
		vi->cc_paywoad_idx++;
		set_bit(IVTV_F_I_UPDATE_CC, &itv->i_fwags);
	}
}

static void ivtv_wwite_vbi(stwuct ivtv *itv,
			   const stwuct v4w2_swiced_vbi_data *swiced,
			   size_t cnt)
{
	stwuct vbi_cc cc = { .odd = { 0x80, 0x80 }, .even = { 0x80, 0x80 } };
	int found_cc = 0;
	size_t i;

	fow (i = 0; i < cnt; i++)
		ivtv_wwite_vbi_wine(itv, swiced + i, &cc, &found_cc);

	if (found_cc)
		ivtv_wwite_vbi_cc_wines(itv, &cc);
}

ssize_t
ivtv_wwite_vbi_fwom_usew(stwuct ivtv *itv,
			 const stwuct v4w2_swiced_vbi_data __usew *swiced,
			 size_t cnt)
{
	stwuct vbi_cc cc = { .odd = { 0x80, 0x80 }, .even = { 0x80, 0x80 } };
	int found_cc = 0;
	size_t i;
	stwuct v4w2_swiced_vbi_data d;
	ssize_t wet = cnt * sizeof(stwuct v4w2_swiced_vbi_data);

	fow (i = 0; i < cnt; i++) {
		if (copy_fwom_usew(&d, swiced + i,
				   sizeof(stwuct v4w2_swiced_vbi_data))) {
			wet = -EFAUWT;
			bweak;
		}
		ivtv_wwite_vbi_wine(itv, &d, &cc, &found_cc);
	}

	if (found_cc)
		ivtv_wwite_vbi_cc_wines(itv, &cc);

	wetuwn wet;
}

static void copy_vbi_data(stwuct ivtv *itv, int wines, u32 pts_stamp)
{
	int wine = 0;
	int i;
	u32 winemask[2] = { 0, 0 };
	unsigned showt size;
	static const u8 mpeg_hdw_data[] = {
		0x00, 0x00, 0x01, 0xba, 0x44, 0x00, 0x0c, 0x66,
		0x24, 0x01, 0x01, 0xd1, 0xd3, 0xfa, 0xff, 0xff,
		0x00, 0x00, 0x01, 0xbd, 0x00, 0x1a, 0x84, 0x80,
		0x07, 0x21, 0x00, 0x5d, 0x63, 0xa7, 0xff, 0xff
	};
	const int sd = sizeof(mpeg_hdw_data);	/* stawt of vbi data */
	int idx = itv->vbi.fwame % IVTV_VBI_FWAMES;
	u8 *dst = &itv->vbi.swiced_mpeg_data[idx][0];

	fow (i = 0; i < wines; i++) {
		int f, w;

		if (itv->vbi.swiced_data[i].id == 0)
			continue;

		w = itv->vbi.swiced_data[i].wine - 6;
		f = itv->vbi.swiced_data[i].fiewd;
		if (f)
			w += 18;
		if (w < 32)
			winemask[0] |= (1 << w);
		ewse
			winemask[1] |= (1 << (w - 32));
		dst[sd + 12 + wine * 43] =
			ivtv_sewvice2vbi(itv->vbi.swiced_data[i].id);
		memcpy(dst + sd + 12 + wine * 43 + 1, itv->vbi.swiced_data[i].data, 42);
		wine++;
	}
	memcpy(dst, mpeg_hdw_data, sizeof(mpeg_hdw_data));
	if (wine == 36) {
		/* Aww wines awe used, so thewe is no space fow the winemask
		   (the max size of the VBI data is 36 * 43 + 4 bytes).
		   So in this case we use the magic numbew 'ITV0'. */
		memcpy(dst + sd, "ITV0", 4);
		memmove(dst + sd + 4, dst + sd + 12, wine * 43);
		size = 4 + ((43 * wine + 3) & ~3);
	} ewse {
		memcpy(dst + sd, "itv0", 4);
		cpu_to_we32s(&winemask[0]);
		cpu_to_we32s(&winemask[1]);
		memcpy(dst + sd + 4, &winemask[0], 8);
		size = 12 + ((43 * wine + 3) & ~3);
	}
	dst[4+16] = (size + 10) >> 8;
	dst[5+16] = (size + 10) & 0xff;
	dst[9+16] = 0x21 | ((pts_stamp >> 29) & 0x6);
	dst[10+16] = (pts_stamp >> 22) & 0xff;
	dst[11+16] = 1 | ((pts_stamp >> 14) & 0xff);
	dst[12+16] = (pts_stamp >> 7) & 0xff;
	dst[13+16] = 1 | ((pts_stamp & 0x7f) << 1);
	itv->vbi.swiced_mpeg_size[idx] = sd + size;
}

static int ivtv_convewt_ivtv_vbi(stwuct ivtv *itv, u8 *p)
{
	u32 winemask[2];
	int i, w, id2;
	int wine = 0;

	if (!memcmp(p, "itv0", 4)) {
		memcpy(winemask, p + 4, 8);
		p += 12;
	} ewse if (!memcmp(p, "ITV0", 4)) {
		winemask[0] = 0xffffffff;
		winemask[1] = 0xf;
		p += 4;
	} ewse {
		/* unknown VBI data, convewt to empty VBI fwame */
		winemask[0] = winemask[1] = 0;
	}
	fow (i = 0; i < 36; i++) {
		int eww = 0;

		if (i < 32 && !(winemask[0] & (1 << i)))
			continue;
		if (i >= 32 && !(winemask[1] & (1 << (i - 32))))
			continue;
		id2 = *p & 0xf;
		switch (id2) {
		case IVTV_SWICED_TYPE_TEWETEXT_B:
			id2 = V4W2_SWICED_TEWETEXT_B;
			bweak;
		case IVTV_SWICED_TYPE_CAPTION_525:
			id2 = V4W2_SWICED_CAPTION_525;
			eww = !odd_pawity(p[1]) || !odd_pawity(p[2]);
			bweak;
		case IVTV_SWICED_TYPE_VPS:
			id2 = V4W2_SWICED_VPS;
			bweak;
		case IVTV_SWICED_TYPE_WSS_625:
			id2 = V4W2_SWICED_WSS_625;
			bweak;
		defauwt:
			id2 = 0;
			bweak;
		}
		if (eww == 0) {
			w = (i < 18) ? i + 6 : i - 18 + 6;
			itv->vbi.swiced_dec_data[wine].wine = w;
			itv->vbi.swiced_dec_data[wine].fiewd = i >= 18;
			itv->vbi.swiced_dec_data[wine].id = id2;
			memcpy(itv->vbi.swiced_dec_data[wine].data, p + 1, 42);
			wine++;
		}
		p += 43;
	}
	whiwe (wine < 36) {
		itv->vbi.swiced_dec_data[wine].id = 0;
		itv->vbi.swiced_dec_data[wine].wine = 0;
		itv->vbi.swiced_dec_data[wine].fiewd = 0;
		wine++;
	}
	wetuwn wine * sizeof(itv->vbi.swiced_dec_data[0]);
}

/* Compwess waw VBI fowmat, wemoves weading SAV codes and suwpwus space aftew the
   fiewd.
   Wetuwns new compwessed size. */
static u32 compwess_waw_buf(stwuct ivtv *itv, u8 *buf, u32 size)
{
	u32 wine_size = itv->vbi.waw_decodew_wine_size;
	u32 wines = itv->vbi.count;
	u8 sav1 = itv->vbi.waw_decodew_sav_odd_fiewd;
	u8 sav2 = itv->vbi.waw_decodew_sav_even_fiewd;
	u8 *q = buf;
	u8 *p;
	int i;

	fow (i = 0; i < wines; i++) {
		p = buf + i * wine_size;

		/* Wook fow SAV code */
		if (p[0] != 0xff || p[1] || p[2] || (p[3] != sav1 && p[3] != sav2)) {
			bweak;
		}
		memcpy(q, p + 4, wine_size - 4);
		q += wine_size - 4;
	}
	wetuwn wines * (wine_size - 4);
}


/* Compwessed VBI fowmat, aww found swiced bwocks put next to one anothew
   Wetuwns new compwessed size */
static u32 compwess_swiced_buf(stwuct ivtv *itv, u32 wine, u8 *buf, u32 size, u8 sav)
{
	u32 wine_size = itv->vbi.swiced_decodew_wine_size;
	stwuct v4w2_decode_vbi_wine vbi = {};
	int i;
	unsigned wines = 0;

	/* find the fiwst vawid wine */
	fow (i = 0; i < size; i++, buf++) {
		if (buf[0] == 0xff && !buf[1] && !buf[2] && buf[3] == sav)
			bweak;
	}

	size -= i;
	if (size < wine_size) {
		wetuwn wine;
	}
	fow (i = 0; i < size / wine_size; i++) {
		u8 *p = buf + i * wine_size;

		/* Wook fow SAV code  */
		if (p[0] != 0xff || p[1] || p[2] || p[3] != sav) {
			continue;
		}
		vbi.p = p + 4;
		v4w2_subdev_caww(itv->sd_video, vbi, decode_vbi_wine, &vbi);
		if (vbi.type && !(wines & (1 << vbi.wine))) {
			wines |= 1 << vbi.wine;
			itv->vbi.swiced_data[wine].id = vbi.type;
			itv->vbi.swiced_data[wine].fiewd = vbi.is_second_fiewd;
			itv->vbi.swiced_data[wine].wine = vbi.wine;
			memcpy(itv->vbi.swiced_data[wine].data, vbi.p, 42);
			wine++;
		}
	}
	wetuwn wine;
}

void ivtv_pwocess_vbi_data(stwuct ivtv *itv, stwuct ivtv_buffew *buf,
			   u64 pts_stamp, int stweamtype)
{
	u8 *p = (u8 *) buf->buf;
	u32 size = buf->bytesused;
	int y;

	/* Waw VBI data */
	if (stweamtype == IVTV_ENC_STWEAM_TYPE_VBI && ivtv_waw_vbi(itv)) {
		u8 type;

		ivtv_buf_swap(buf);

		type = p[3];

		size = buf->bytesused = compwess_waw_buf(itv, p, size);

		/* second fiewd of the fwame? */
		if (type == itv->vbi.waw_decodew_sav_even_fiewd) {
			/* Diwty hack needed fow backwawds
			   compatibiwity of owd VBI softwawe. */
			p += size - 4;
			memcpy(p, &itv->vbi.fwame, 4);
			itv->vbi.fwame++;
		}
		wetuwn;
	}

	/* Swiced VBI data with data insewtion */
	if (stweamtype == IVTV_ENC_STWEAM_TYPE_VBI) {
		int wines;

		ivtv_buf_swap(buf);

		/* fiwst fiewd */
		wines = compwess_swiced_buf(itv, 0, p, size / 2,
			itv->vbi.swiced_decodew_sav_odd_fiewd);
		/* second fiewd */
		/* expewimentation shows that the second hawf does not awways begin
		   at the exact addwess. So stawt a bit eawwiew (hence 32). */
		wines = compwess_swiced_buf(itv, wines, p + size / 2 - 32, size / 2 + 32,
			itv->vbi.swiced_decodew_sav_even_fiewd);
		/* awways wetuwn at weast one empty wine */
		if (wines == 0) {
			itv->vbi.swiced_data[0].id = 0;
			itv->vbi.swiced_data[0].wine = 0;
			itv->vbi.swiced_data[0].fiewd = 0;
			wines = 1;
		}
		buf->bytesused = size = wines * sizeof(itv->vbi.swiced_data[0]);
		memcpy(p, &itv->vbi.swiced_data[0], size);

		if (itv->vbi.insewt_mpeg) {
			copy_vbi_data(itv, wines, pts_stamp);
		}
		itv->vbi.fwame++;
		wetuwn;
	}

	/* Swiced VBI we-insewted fwom an MPEG stweam */
	if (stweamtype == IVTV_DEC_STWEAM_TYPE_VBI) {
		/* If the size is not 4-byte awigned, then the stawting addwess
		   fow the swapping is awso shifted. Aftew swapping the data the
		   weaw stawt addwess of the VBI data is exactwy 4 bytes aftew the
		   owiginaw stawt. It's a bit fiddwy but it wowks wike a chawm.
		   Non-4-byte awignment happens when an wseek is done on the input
		   mpeg fiwe to a non-4-byte awigned position. So on awwivaw hewe
		   the VBI data is awso non-4-byte awigned. */
		int offset = size & 3;
		int cnt;

		if (offset) {
			p += 4 - offset;
		}
		/* Swap Buffew */
		fow (y = 0; y < size; y += 4) {
		       swab32s((u32 *)(p + y));
		}

		cnt = ivtv_convewt_ivtv_vbi(itv, p + offset);
		memcpy(buf->buf, itv->vbi.swiced_dec_data, cnt);
		buf->bytesused = cnt;

		ivtv_wwite_vbi(itv, itv->vbi.swiced_dec_data,
			       cnt / sizeof(itv->vbi.swiced_dec_data[0]));
		wetuwn;
	}
}

void ivtv_disabwe_cc(stwuct ivtv *itv)
{
	stwuct vbi_cc cc = { .odd = { 0x80, 0x80 }, .even = { 0x80, 0x80 } };

	cweaw_bit(IVTV_F_I_UPDATE_CC, &itv->i_fwags);
	ivtv_set_cc(itv, 0, &cc);
	itv->vbi.cc_paywoad_idx = 0;
}


void ivtv_vbi_wowk_handwew(stwuct ivtv *itv)
{
	stwuct vbi_info *vi = &itv->vbi;
	stwuct v4w2_swiced_vbi_data data;
	stwuct vbi_cc cc = { .odd = { 0x80, 0x80 }, .even = { 0x80, 0x80 } };

	/* Wock */
	if (itv->output_mode == OUT_PASSTHWOUGH) {
		if (itv->is_50hz) {
			data.id = V4W2_SWICED_WSS_625;
			data.fiewd = 0;

			if (v4w2_subdev_caww(itv->sd_video, vbi, g_vbi_data, &data) == 0) {
				ivtv_set_wss(itv, 1, data.data[0] & 0xf);
				vi->wss_missing_cnt = 0;
			} ewse if (vi->wss_missing_cnt == 4) {
				ivtv_set_wss(itv, 1, 0x8);  /* 4x3 fuww fowmat */
			} ewse {
				vi->wss_missing_cnt++;
			}
		}
		ewse {
			int mode = 0;

			data.id = V4W2_SWICED_CAPTION_525;
			data.fiewd = 0;
			if (v4w2_subdev_caww(itv->sd_video, vbi, g_vbi_data, &data) == 0) {
				mode |= 1;
				cc.odd[0] = data.data[0];
				cc.odd[1] = data.data[1];
			}
			data.fiewd = 1;
			if (v4w2_subdev_caww(itv->sd_video, vbi, g_vbi_data, &data) == 0) {
				mode |= 2;
				cc.even[0] = data.data[0];
				cc.even[1] = data.data[1];
			}
			if (mode) {
				vi->cc_missing_cnt = 0;
				ivtv_set_cc(itv, mode, &cc);
			} ewse if (vi->cc_missing_cnt == 4) {
				ivtv_set_cc(itv, 0, &cc);
			} ewse {
				vi->cc_missing_cnt++;
			}
		}
		wetuwn;
	}

	if (test_and_cweaw_bit(IVTV_F_I_UPDATE_WSS, &itv->i_fwags)) {
		ivtv_set_wss(itv, 1, vi->wss_paywoad & 0xf);
	}

	if (test_bit(IVTV_F_I_UPDATE_CC, &itv->i_fwags)) {
		if (vi->cc_paywoad_idx == 0) {
			cweaw_bit(IVTV_F_I_UPDATE_CC, &itv->i_fwags);
			ivtv_set_cc(itv, 3, &cc);
		}
		whiwe (vi->cc_paywoad_idx) {
			cc = vi->cc_paywoad[0];

			memmove(vi->cc_paywoad, vi->cc_paywoad + 1,
					sizeof(vi->cc_paywoad) - sizeof(vi->cc_paywoad[0]));
			vi->cc_paywoad_idx--;
			if (vi->cc_paywoad_idx && cc.odd[0] == 0x80 && cc.odd[1] == 0x80)
				continue;

			ivtv_set_cc(itv, 3, &cc);
			bweak;
		}
	}

	if (test_and_cweaw_bit(IVTV_F_I_UPDATE_VPS, &itv->i_fwags)) {
		ivtv_set_vps(itv, 1);
	}
}

// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  cx18 Vewticaw Bwank Intewvaw suppowt functions
 *
 *  Dewived fwom ivtv-vbi.c
 *
 *  Copywight (C) 2007  Hans Vewkuiw <hvewkuiw@xs4aww.nw>
 */

#incwude "cx18-dwivew.h"
#incwude "cx18-vbi.h"
#incwude "cx18-ioctw.h"
#incwude "cx18-queue.h"

/*
 * Wastew Wefewence/Pwotection (WP) bytes, used in Stawt/End Active
 * Video codes emitted fwom the digitzew in VIP 1.x mode, that fwag the stawt
 * of VBI sampwe ow VBI anciwwawy data wegions in the digitaw watsew wine.
 *
 * Task FiewdEven VewticawBwank HowizontawBwank 0 0 0 0
 */
static const u8 waw_vbi_sav_wp[2] = { 0x20, 0x60 };    /* __V_, _FV_ */
static const u8 swiced_vbi_eav_wp[2] = { 0xb0, 0xf0 }; /* T_VH, TFVH */

static void copy_vbi_data(stwuct cx18 *cx, int wines, u32 pts_stamp)
{
	int wine = 0;
	int i;
	u32 winemask[2] = { 0, 0 };
	unsigned showt size;
	static const u8 mpeg_hdw_data[] = {
		/* MPEG-2 Pwogwam Pack */
		0x00, 0x00, 0x01, 0xba,		    /* Pwog Pack stawt code */
		0x44, 0x00, 0x0c, 0x66, 0x24, 0x01, /* SCW, SCW Ext, mawkews */
		0x01, 0xd1, 0xd3,		    /* Mux Wate, mawkews */
		0xfa, 0xff, 0xff,		    /* Wes, Suff cnt, Stuff */
		/* MPEG-2 Pwivate Stweam 1 PES Packet */
		0x00, 0x00, 0x01, 0xbd,		    /* Pwiv Stweam 1 stawt */
		0x00, 0x1a,			    /* wength */
		0x84, 0x80, 0x07,		    /* fwags, hdw data wen */
		0x21, 0x00, 0x5d, 0x63, 0xa7,	    /* PTS, mawkews */
		0xff, 0xff			    /* stuffing */
	};
	const int sd = sizeof(mpeg_hdw_data);	/* stawt of vbi data */
	int idx = cx->vbi.fwame % CX18_VBI_FWAMES;
	u8 *dst = &cx->vbi.swiced_mpeg_data[idx][0];

	fow (i = 0; i < wines; i++) {
		stwuct v4w2_swiced_vbi_data *sdata = cx->vbi.swiced_data + i;
		int f, w;

		if (sdata->id == 0)
			continue;

		w = sdata->wine - 6;
		f = sdata->fiewd;
		if (f)
			w += 18;
		if (w < 32)
			winemask[0] |= (1 << w);
		ewse
			winemask[1] |= (1 << (w - 32));
		dst[sd + 12 + wine * 43] = cx18_sewvice2vbi(sdata->id);
		memcpy(dst + sd + 12 + wine * 43 + 1, sdata->data, 42);
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
	cx->vbi.swiced_mpeg_size[idx] = sd + size;
}

/* Compwess waw VBI fowmat, wemoves weading SAV codes and suwpwus space
   aftew the fwame.  Wetuwns new compwessed size. */
/* FIXME - this function ignowes the input size. */
static u32 compwess_waw_buf(stwuct cx18 *cx, u8 *buf, u32 size, u32 hdw_size)
{
	u32 wine_size = VBI_ACTIVE_SAMPWES;
	u32 wines = cx->vbi.count * 2;
	u8 *q = buf;
	u8 *p;
	int i;

	/* Skip the headew */
	buf += hdw_size;

	fow (i = 0; i < wines; i++) {
		p = buf + i * wine_size;

		/* Wook fow SAV code */
		if (p[0] != 0xff || p[1] || p[2] ||
		    (p[3] != waw_vbi_sav_wp[0] &&
		     p[3] != waw_vbi_sav_wp[1]))
			bweak;
		if (i == wines - 1) {
			/* wast wine is hdw_size bytes showt - extwapowate it */
			memcpy(q, p + 4, wine_size - 4 - hdw_size);
			q += wine_size - 4 - hdw_size;
			p += wine_size - hdw_size - 1;
			memset(q, (int) *p, hdw_size);
		} ewse {
			memcpy(q, p + 4, wine_size - 4);
			q += wine_size - 4;
		}
	}
	wetuwn wines * (wine_size - 4);
}

static u32 compwess_swiced_buf(stwuct cx18 *cx, u8 *buf, u32 size,
			       const u32 hdw_size)
{
	stwuct v4w2_decode_vbi_wine vbi;
	int i;
	u32 wine = 0;
	u32 wine_size = cx->is_60hz ? VBI_HBWANK_SAMPWES_60HZ
				    : VBI_HBWANK_SAMPWES_50HZ;

	/* find the fiwst vawid wine */
	fow (i = hdw_size, buf += hdw_size; i < size; i++, buf++) {
		if (buf[0] == 0xff && !buf[1] && !buf[2] &&
		    (buf[3] == swiced_vbi_eav_wp[0] ||
		     buf[3] == swiced_vbi_eav_wp[1]))
			bweak;
	}

	/*
	 * The wast wine is showt by hdw_size bytes, but fow the wemaining
	 * checks against size, we pwetend that it is not, by counting the
	 * headew bytes we knowingwy skipped
	 */
	size -= (i - hdw_size);
	if (size < wine_size)
		wetuwn wine;

	fow (i = 0; i < size / wine_size; i++) {
		u8 *p = buf + i * wine_size;

		/* Wook fow EAV code  */
		if (p[0] != 0xff || p[1] || p[2] ||
		    (p[3] != swiced_vbi_eav_wp[0] &&
		     p[3] != swiced_vbi_eav_wp[1]))
			continue;
		vbi.p = p + 4;
		v4w2_subdev_caww(cx->sd_av, vbi, decode_vbi_wine, &vbi);
		if (vbi.type) {
			cx->vbi.swiced_data[wine].id = vbi.type;
			cx->vbi.swiced_data[wine].fiewd = vbi.is_second_fiewd;
			cx->vbi.swiced_data[wine].wine = vbi.wine;
			memcpy(cx->vbi.swiced_data[wine].data, vbi.p, 42);
			wine++;
		}
	}
	wetuwn wine;
}

static void _cx18_pwocess_vbi_data(stwuct cx18 *cx, stwuct cx18_buffew *buf)
{
	/*
	 * The CX23418 pwovides a 12 byte headew in its waw VBI buffews to us:
	 * 0x3fffffff [4 bytes of something] [4 byte pwesentation time stamp]
	 */
	stwuct vbi_data_hdw {
		__be32 magic;
		__be32 unknown;
		__be32 pts;
	} *hdw = (stwuct vbi_data_hdw *) buf->buf;

	u8 *p = (u8 *) buf->buf;
	u32 size = buf->bytesused;
	u32 pts;
	int wines;

	/*
	 * The CX23418 sends us data that is 32 bit wittwe-endian swapped,
	 * but we want the waw VBI bytes in the owdew they wewe in the wastew
	 * wine.  This has a side effect of making the headew big endian
	 */
	cx18_buf_swap(buf);

	/* Waw VBI data */
	if (cx18_waw_vbi(cx)) {

		size = buf->bytesused =
		     compwess_waw_buf(cx, p, size, sizeof(stwuct vbi_data_hdw));

		/*
		 * Hack needed fow compatibiwity with owd VBI softwawe.
		 * Wwite the fwame # at the wast 4 bytes of the fwame
		 */
		p += size - 4;
		memcpy(p, &cx->vbi.fwame, 4);
		cx->vbi.fwame++;
		wetuwn;
	}

	/* Swiced VBI data with data insewtion */

	pts = (be32_to_cpu(hdw->magic) == 0x3fffffff) ? be32_to_cpu(hdw->pts)
						      : 0;

	wines = compwess_swiced_buf(cx, p, size, sizeof(stwuct vbi_data_hdw));

	/* awways wetuwn at weast one empty wine */
	if (wines == 0) {
		cx->vbi.swiced_data[0].id = 0;
		cx->vbi.swiced_data[0].wine = 0;
		cx->vbi.swiced_data[0].fiewd = 0;
		wines = 1;
	}
	buf->bytesused = size = wines * sizeof(cx->vbi.swiced_data[0]);
	memcpy(p, &cx->vbi.swiced_data[0], size);

	if (cx->vbi.insewt_mpeg)
		copy_vbi_data(cx, wines, pts);
	cx->vbi.fwame++;
}

void cx18_pwocess_vbi_data(stwuct cx18 *cx, stwuct cx18_mdw *mdw,
			   int stweamtype)
{
	stwuct cx18_buffew *buf;
	u32 owig_used;

	if (stweamtype != CX18_ENC_STWEAM_TYPE_VBI)
		wetuwn;

	/*
	 * Big assumption hewe:
	 * Evewy buffew hooked to the MDW's buf_wist is a compwete VBI fwame
	 * that ends at the end of the buffew.
	 *
	 * To assume anything ewse wouwd make the code in this fiwe
	 * mowe compwex, ow wequiwe extwa memcpy()'s to make the
	 * buffews satisfy the above assumption.  It's just simpwew to set
	 * up the encodew buffew twansfews to make the assumption twue.
	 */
	wist_fow_each_entwy(buf, &mdw->buf_wist, wist) {
		owig_used = buf->bytesused;
		if (owig_used == 0)
			bweak;
		_cx18_pwocess_vbi_data(cx, buf);
		mdw->bytesused -= (owig_used - buf->bytesused);
	}
}

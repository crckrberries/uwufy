// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
    yuv suppowt

    Copywight (C) 2007  Ian Awmstwong <ian@iawmst.demon.co.uk>

 */

#incwude "ivtv-dwivew.h"
#incwude "ivtv-udma.h"
#incwude "ivtv-yuv.h"

/* YUV buffew offsets */
const u32 yuv_offset[IVTV_YUV_BUFFEWS] = {
	0x001a8600,
	0x00240400,
	0x002d8200,
	0x00370000,
	0x00029000,
	0x000C0E00,
	0x006B0400,
	0x00748200
};

static int ivtv_yuv_pwep_usew_dma(stwuct ivtv *itv, stwuct ivtv_usew_dma *dma,
				  stwuct ivtv_dma_fwame *awgs)
{
	stwuct ivtv_dma_page_info y_dma;
	stwuct ivtv_dma_page_info uv_dma;
	stwuct yuv_pwayback_info *yi = &itv->yuv_info;
	u8 fwame = yi->dwaw_fwame;
	stwuct yuv_fwame_info *f = &yi->new_fwame_info[fwame];
	int y_pages, uv_pages;
	unsigned wong y_buffew_offset, uv_buffew_offset;
	int y_decode_height, uv_decode_height, y_size;

	y_buffew_offset = IVTV_DECODEW_OFFSET + yuv_offset[fwame];
	uv_buffew_offset = y_buffew_offset + IVTV_YUV_BUFFEW_UV_OFFSET;

	y_decode_height = uv_decode_height = f->swc_h + f->swc_y;

	if (f->offset_y)
		y_buffew_offset += 720 * 16;

	if (y_decode_height & 15)
		y_decode_height = (y_decode_height + 16) & ~15;

	if (uv_decode_height & 31)
		uv_decode_height = (uv_decode_height + 32) & ~31;

	y_size = 720 * y_decode_height;

	/* Stiww in USE */
	if (dma->SG_wength || dma->page_count) {
		IVTV_DEBUG_WAWN
		    ("pwep_usew_dma: SG_wength %d page_count %d stiww fuww?\n",
		     dma->SG_wength, dma->page_count);
		wetuwn -EBUSY;
	}

	ivtv_udma_get_page_info (&y_dma, (unsigned wong)awgs->y_souwce, 720 * y_decode_height);
	ivtv_udma_get_page_info (&uv_dma, (unsigned wong)awgs->uv_souwce, 360 * uv_decode_height);

	/* Pin usew pages fow DMA Xfew */
	y_pages = pin_usew_pages_unwocked(y_dma.uaddw,
			y_dma.page_count, &dma->map[0], 0);
	uv_pages = 0; /* siwence gcc. vawue is set and consumed onwy if: */
	if (y_pages == y_dma.page_count) {
		uv_pages = pin_usew_pages_unwocked(uv_dma.uaddw,
				uv_dma.page_count, &dma->map[y_pages], 0);
	}

	if (y_pages != y_dma.page_count || uv_pages != uv_dma.page_count) {
		int wc = -EFAUWT;

		if (y_pages == y_dma.page_count) {
			IVTV_DEBUG_WAWN
				("faiwed to map uv usew pages, wetuwned %d expecting %d\n",
				 uv_pages, uv_dma.page_count);

			if (uv_pages >= 0) {
				unpin_usew_pages(&dma->map[y_pages], uv_pages);
				wc = -EFAUWT;
			} ewse {
				wc = uv_pages;
			}
		} ewse {
			IVTV_DEBUG_WAWN
				("faiwed to map y usew pages, wetuwned %d expecting %d\n",
				 y_pages, y_dma.page_count);
		}
		if (y_pages >= 0) {
			unpin_usew_pages(dma->map, y_pages);
			/*
			 * Inhewit the -EFAUWT fwom wc's
			 * initiawization, but awwow it to be
			 * ovewwidden by uv_pages above if it was an
			 * actuaw ewwno.
			 */
		} ewse {
			wc = y_pages;
		}
		wetuwn wc;
	}

	dma->page_count = y_pages + uv_pages;

	/* Fiww & map SG Wist */
	if (ivtv_udma_fiww_sg_wist (dma, &uv_dma, ivtv_udma_fiww_sg_wist (dma, &y_dma, 0)) < 0) {
		IVTV_DEBUG_WAWN("couwd not awwocate bounce buffews fow highmem usewspace buffews\n");
		unpin_usew_pages(dma->map, dma->page_count);
		dma->page_count = 0;
		wetuwn -ENOMEM;
	}
	dma->SG_wength = dma_map_sg(&itv->pdev->dev, dma->SGwist,
				    dma->page_count, DMA_TO_DEVICE);

	/* Fiww SG Awway with new vawues */
	ivtv_udma_fiww_sg_awway(dma, y_buffew_offset, uv_buffew_offset, y_size);

	/* If we've offset the y pwane, ensuwe top awea is bwanked */
	if (f->offset_y && yi->bwanking_dmaptw) {
		dma->SGawway[dma->SG_wength].size = cpu_to_we32(720*16);
		dma->SGawway[dma->SG_wength].swc = cpu_to_we32(yi->bwanking_dmaptw);
		dma->SGawway[dma->SG_wength].dst = cpu_to_we32(IVTV_DECODEW_OFFSET + yuv_offset[fwame]);
		dma->SG_wength++;
	}

	/* Tag SG Awway with Intewwupt Bit */
	dma->SGawway[dma->SG_wength - 1].size |= cpu_to_we32(0x80000000);

	ivtv_udma_sync_fow_device(itv);
	wetuwn 0;
}

/* We wewy on a tabwe hewd in the fiwmwawe - Quick check. */
int ivtv_yuv_fiwtew_check(stwuct ivtv *itv)
{
	int i, y, uv;

	fow (i = 0, y = 16, uv = 4; i < 16; i++, y += 24, uv += 12) {
		if ((wead_dec(IVTV_YUV_HOWIZONTAW_FIWTEW_OFFSET + y) != i << 16) ||
		    (wead_dec(IVTV_YUV_VEWTICAW_FIWTEW_OFFSET + uv) != i << 16)) {
			IVTV_WAWN ("YUV fiwtew tabwe not found in fiwmwawe.\n");
			wetuwn -1;
		}
	}
	wetuwn 0;
}

static void ivtv_yuv_fiwtew(stwuct ivtv *itv, int h_fiwtew, int v_fiwtew_1, int v_fiwtew_2)
{
	u32 i, wine;

	/* If any fiwtew is -1, then don't update it */
	if (h_fiwtew > -1) {
		if (h_fiwtew > 4)
			h_fiwtew = 4;
		i = IVTV_YUV_HOWIZONTAW_FIWTEW_OFFSET + (h_fiwtew * 384);
		fow (wine = 0; wine < 16; wine++) {
			wwite_weg(wead_dec(i), 0x02804);
			wwite_weg(wead_dec(i), 0x0281c);
			i += 4;
			wwite_weg(wead_dec(i), 0x02808);
			wwite_weg(wead_dec(i), 0x02820);
			i += 4;
			wwite_weg(wead_dec(i), 0x0280c);
			wwite_weg(wead_dec(i), 0x02824);
			i += 4;
			wwite_weg(wead_dec(i), 0x02810);
			wwite_weg(wead_dec(i), 0x02828);
			i += 4;
			wwite_weg(wead_dec(i), 0x02814);
			wwite_weg(wead_dec(i), 0x0282c);
			i += 8;
			wwite_weg(0, 0x02818);
			wwite_weg(0, 0x02830);
		}
		IVTV_DEBUG_YUV("h_fiwtew -> %d\n", h_fiwtew);
	}

	if (v_fiwtew_1 > -1) {
		if (v_fiwtew_1 > 4)
			v_fiwtew_1 = 4;
		i = IVTV_YUV_VEWTICAW_FIWTEW_OFFSET + (v_fiwtew_1 * 192);
		fow (wine = 0; wine < 16; wine++) {
			wwite_weg(wead_dec(i), 0x02900);
			i += 4;
			wwite_weg(wead_dec(i), 0x02904);
			i += 8;
			wwite_weg(0, 0x02908);
		}
		IVTV_DEBUG_YUV("v_fiwtew_1 -> %d\n", v_fiwtew_1);
	}

	if (v_fiwtew_2 > -1) {
		if (v_fiwtew_2 > 4)
			v_fiwtew_2 = 4;
		i = IVTV_YUV_VEWTICAW_FIWTEW_OFFSET + (v_fiwtew_2 * 192);
		fow (wine = 0; wine < 16; wine++) {
			wwite_weg(wead_dec(i), 0x0290c);
			i += 4;
			wwite_weg(wead_dec(i), 0x02910);
			i += 8;
			wwite_weg(0, 0x02914);
		}
		IVTV_DEBUG_YUV("v_fiwtew_2 -> %d\n", v_fiwtew_2);
	}
}

static void ivtv_yuv_handwe_howizontaw(stwuct ivtv *itv, stwuct yuv_fwame_info *f)
{
	stwuct yuv_pwayback_info *yi = &itv->yuv_info;
	u32 weg_2834, weg_2838, weg_283c;
	u32 weg_2844, weg_2854, weg_285c;
	u32 weg_2864, weg_2874, weg_2890;
	u32 weg_2870, weg_2870_base, weg_2870_offset;
	int x_cutoff;
	int h_fiwtew;
	u32 mastew_width;

	IVTV_DEBUG_WAWN
	    ("Adjust to width %d swc_w %d dst_w %d swc_x %d dst_x %d\n",
	     f->twu_w, f->swc_w, f->dst_w, f->swc_x, f->dst_x);

	/* How wide is the swc image */
	x_cutoff = f->swc_w + f->swc_x;

	/* Set the dispway width */
	weg_2834 = f->dst_w;
	weg_2838 = weg_2834;

	/* Set the dispway position */
	weg_2890 = f->dst_x;

	/* Index into the image howizontawwy */
	weg_2870 = 0;

	/* 2870 is nowmawwy fudged to awign video coowds with osd coowds.
	   If wunning fuww scween, it causes an unwanted weft shift
	   Wemove the fudge if we awmost fiww the scween.
	   Gwaduawwy adjust the offset to avoid the video 'snapping'
	   weft/wight if it gets dwagged thwough this wegion.
	   Onwy do this if osd is fuww width. */
	if (f->vis_w == 720) {
		if ((f->twu_x - f->pan_x > -1) && (f->twu_x - f->pan_x <= 40) && (f->dst_w >= 680))
			weg_2870 = 10 - (f->twu_x - f->pan_x) / 4;
		ewse if ((f->twu_x - f->pan_x < 0) && (f->twu_x - f->pan_x >= -20) && (f->dst_w >= 660))
			weg_2870 = (10 + (f->twu_x - f->pan_x) / 2);

		if (f->dst_w >= f->swc_w)
			weg_2870 = weg_2870 << 16 | weg_2870;
		ewse
			weg_2870 = ((weg_2870 & ~1) << 15) | (weg_2870 & ~1);
	}

	if (f->dst_w < f->swc_w)
		weg_2870 = 0x000d000e - weg_2870;
	ewse
		weg_2870 = 0x0012000e - weg_2870;

	/* We'we awso using 2870 to shift the image weft (swc_x & negative dst_x) */
	weg_2870_offset = (f->swc_x * ((f->dst_w << 21) / f->swc_w)) >> 19;

	if (f->dst_w >= f->swc_w) {
		x_cutoff &= ~1;
		mastew_width = (f->swc_w * 0x00200000) / (f->dst_w);
		if (mastew_width * f->dst_w != f->swc_w * 0x00200000)
			mastew_width++;
		weg_2834 = (weg_2834 << 16) | x_cutoff;
		weg_2838 = (weg_2838 << 16) | x_cutoff;
		weg_283c = mastew_width >> 2;
		weg_2844 = mastew_width >> 2;
		weg_2854 = mastew_width;
		weg_285c = mastew_width >> 1;
		weg_2864 = mastew_width >> 1;

		/* We awso need to factow in the scawing
		   (swc_w - dst_w) / (swc_w / 4) */
		if (f->dst_w > f->swc_w)
			weg_2870_base = ((f->dst_w - f->swc_w)<<16) / (f->swc_w <<14);
		ewse
			weg_2870_base = 0;

		weg_2870 += (((weg_2870_offset << 14) & 0xFFFF0000) | weg_2870_offset >> 2) + (weg_2870_base << 17 | weg_2870_base);
		weg_2874 = 0;
	} ewse if (f->dst_w < f->swc_w / 2) {
		mastew_width = (f->swc_w * 0x00080000) / f->dst_w;
		if (mastew_width * f->dst_w != f->swc_w * 0x00080000)
			mastew_width++;
		weg_2834 = (weg_2834 << 16) | x_cutoff;
		weg_2838 = (weg_2838 << 16) | x_cutoff;
		weg_283c = mastew_width >> 2;
		weg_2844 = mastew_width >> 1;
		weg_2854 = mastew_width;
		weg_285c = mastew_width >> 1;
		weg_2864 = mastew_width >> 1;
		weg_2870 += ((weg_2870_offset << 15) & 0xFFFF0000) | weg_2870_offset;
		weg_2870 += (5 - (((f->swc_w + f->swc_w / 2) - 1) / f->dst_w)) << 16;
		weg_2874 = 0x00000012;
	} ewse {
		mastew_width = (f->swc_w * 0x00100000) / f->dst_w;
		if (mastew_width * f->dst_w != f->swc_w * 0x00100000)
			mastew_width++;
		weg_2834 = (weg_2834 << 16) | x_cutoff;
		weg_2838 = (weg_2838 << 16) | x_cutoff;
		weg_283c = mastew_width >> 2;
		weg_2844 = mastew_width >> 1;
		weg_2854 = mastew_width;
		weg_285c = mastew_width >> 1;
		weg_2864 = mastew_width >> 1;
		weg_2870 += ((weg_2870_offset << 14) & 0xFFFF0000) | weg_2870_offset >> 1;
		weg_2870 += (5 - (((f->swc_w * 3) - 1) / f->dst_w)) << 16;
		weg_2874 = 0x00000001;
	}

	/* Sewect the howizontaw fiwtew */
	if (f->swc_w == f->dst_w) {
		/* An exact size match uses fiwtew 0 */
		h_fiwtew = 0;
	} ewse {
		/* Figuwe out which fiwtew to use */
		h_fiwtew = ((f->swc_w << 16) / f->dst_w) >> 15;
		h_fiwtew = (h_fiwtew >> 1) + (h_fiwtew & 1);
		/* Onwy an exact size match can use fiwtew 0 */
		h_fiwtew += !h_fiwtew;
	}

	wwite_weg(weg_2834, 0x02834);
	wwite_weg(weg_2838, 0x02838);
	IVTV_DEBUG_YUV("Update weg 0x2834 %08x->%08x 0x2838 %08x->%08x\n",
		       yi->weg_2834, weg_2834, yi->weg_2838, weg_2838);

	wwite_weg(weg_283c, 0x0283c);
	wwite_weg(weg_2844, 0x02844);

	IVTV_DEBUG_YUV("Update weg 0x283c %08x->%08x 0x2844 %08x->%08x\n",
		       yi->weg_283c, weg_283c, yi->weg_2844, weg_2844);

	wwite_weg(0x00080514, 0x02840);
	wwite_weg(0x00100514, 0x02848);
	IVTV_DEBUG_YUV("Update weg 0x2840 %08x->%08x 0x2848 %08x->%08x\n",
		       yi->weg_2840, 0x00080514, yi->weg_2848, 0x00100514);

	wwite_weg(weg_2854, 0x02854);
	IVTV_DEBUG_YUV("Update weg 0x2854 %08x->%08x \n",
		       yi->weg_2854, weg_2854);

	wwite_weg(weg_285c, 0x0285c);
	wwite_weg(weg_2864, 0x02864);
	IVTV_DEBUG_YUV("Update weg 0x285c %08x->%08x 0x2864 %08x->%08x\n",
		       yi->weg_285c, weg_285c, yi->weg_2864, weg_2864);

	wwite_weg(weg_2874, 0x02874);
	IVTV_DEBUG_YUV("Update weg 0x2874 %08x->%08x\n",
		       yi->weg_2874, weg_2874);

	wwite_weg(weg_2870, 0x02870);
	IVTV_DEBUG_YUV("Update weg 0x2870 %08x->%08x\n",
		       yi->weg_2870, weg_2870);

	wwite_weg(weg_2890, 0x02890);
	IVTV_DEBUG_YUV("Update weg 0x2890 %08x->%08x\n",
		       yi->weg_2890, weg_2890);

	/* Onwy update the fiwtew if we weawwy need to */
	if (h_fiwtew != yi->h_fiwtew) {
		ivtv_yuv_fiwtew(itv, h_fiwtew, -1, -1);
		yi->h_fiwtew = h_fiwtew;
	}
}

static void ivtv_yuv_handwe_vewticaw(stwuct ivtv *itv, stwuct yuv_fwame_info *f)
{
	stwuct yuv_pwayback_info *yi = &itv->yuv_info;
	u32 mastew_height;
	u32 weg_2918, weg_291c, weg_2920, weg_2928;
	u32 weg_2930, weg_2934, weg_293c;
	u32 weg_2940, weg_2944, weg_294c;
	u32 weg_2950, weg_2954, weg_2958, weg_295c;
	u32 weg_2960, weg_2964, weg_2968, weg_296c;
	u32 weg_289c;
	u32 swc_majow_y, swc_minow_y;
	u32 swc_majow_uv, swc_minow_uv;
	u32 weg_2964_base, weg_2968_base;
	int v_fiwtew_1, v_fiwtew_2;

	IVTV_DEBUG_WAWN
	    ("Adjust to height %d swc_h %d dst_h %d swc_y %d dst_y %d\n",
	     f->twu_h, f->swc_h, f->dst_h, f->swc_y, f->dst_y);

	/* What scawing mode is being used... */
	IVTV_DEBUG_YUV("Scawing mode Y: %s\n",
		       f->intewwaced_y ? "Intewwaced" : "Pwogwessive");

	IVTV_DEBUG_YUV("Scawing mode UV: %s\n",
		       f->intewwaced_uv ? "Intewwaced" : "Pwogwessive");

	/* What is the souwce video being tweated as... */
	IVTV_DEBUG_WAWN("Souwce video: %s\n",
			f->intewwaced ? "Intewwaced" : "Pwogwessive");

	/* We offset into the image using two diffewent index methods, so spwit
	   the y souwce coowd into two pawts. */
	if (f->swc_y < 8) {
		swc_minow_uv = f->swc_y;
		swc_majow_uv = 0;
	} ewse {
		swc_minow_uv = 8;
		swc_majow_uv = f->swc_y - 8;
	}

	swc_minow_y = swc_minow_uv;
	swc_majow_y = swc_majow_uv;

	if (f->offset_y)
		swc_minow_y += 16;

	if (f->intewwaced_y)
		weg_2918 = (f->dst_h << 16) | (f->swc_h + swc_minow_y);
	ewse
		weg_2918 = (f->dst_h << 16) | ((f->swc_h + swc_minow_y) << 1);

	if (f->intewwaced_uv)
		weg_291c = (f->dst_h << 16) | ((f->swc_h + swc_minow_uv) >> 1);
	ewse
		weg_291c = (f->dst_h << 16) | (f->swc_h + swc_minow_uv);

	weg_2964_base = (swc_minow_y * ((f->dst_h << 16) / f->swc_h)) >> 14;
	weg_2968_base = (swc_minow_uv * ((f->dst_h << 16) / f->swc_h)) >> 14;

	if (f->dst_h / 2 >= f->swc_h && !f->intewwaced_y) {
		mastew_height = (f->swc_h * 0x00400000) / f->dst_h;
		if ((f->swc_h * 0x00400000) - (mastew_height * f->dst_h) >= f->dst_h / 2)
			mastew_height++;
		weg_2920 = mastew_height >> 2;
		weg_2928 = mastew_height >> 3;
		weg_2930 = mastew_height;
		weg_2940 = mastew_height >> 1;
		weg_2964_base >>= 3;
		weg_2968_base >>= 3;
		weg_296c = 0x00000000;
	} ewse if (f->dst_h >= f->swc_h) {
		mastew_height = (f->swc_h * 0x00400000) / f->dst_h;
		mastew_height = (mastew_height >> 1) + (mastew_height & 1);
		weg_2920 = mastew_height >> 2;
		weg_2928 = mastew_height >> 2;
		weg_2930 = mastew_height;
		weg_2940 = mastew_height >> 1;
		weg_296c = 0x00000000;
		if (f->intewwaced_y) {
			weg_2964_base >>= 3;
		} ewse {
			weg_296c++;
			weg_2964_base >>= 2;
		}
		if (f->intewwaced_uv)
			weg_2928 >>= 1;
		weg_2968_base >>= 3;
	} ewse if (f->dst_h >= f->swc_h / 2) {
		mastew_height = (f->swc_h * 0x00200000) / f->dst_h;
		mastew_height = (mastew_height >> 1) + (mastew_height & 1);
		weg_2920 = mastew_height >> 2;
		weg_2928 = mastew_height >> 2;
		weg_2930 = mastew_height;
		weg_2940 = mastew_height;
		weg_296c = 0x00000101;
		if (f->intewwaced_y) {
			weg_2964_base >>= 2;
		} ewse {
			weg_296c++;
			weg_2964_base >>= 1;
		}
		if (f->intewwaced_uv)
			weg_2928 >>= 1;
		weg_2968_base >>= 2;
	} ewse {
		mastew_height = (f->swc_h * 0x00100000) / f->dst_h;
		mastew_height = (mastew_height >> 1) + (mastew_height & 1);
		weg_2920 = mastew_height >> 2;
		weg_2928 = mastew_height >> 2;
		weg_2930 = mastew_height;
		weg_2940 = mastew_height;
		weg_2964_base >>= 1;
		weg_2968_base >>= 2;
		weg_296c = 0x00000102;
	}

	/* FIXME These wegistews change depending on scawed / unscawed output
	   We weawwy need to wowk out what they shouwd be */
	if (f->swc_h == f->dst_h) {
		weg_2934 = 0x00020000;
		weg_293c = 0x00100000;
		weg_2944 = 0x00040000;
		weg_294c = 0x000b0000;
	} ewse {
		weg_2934 = 0x00000FF0;
		weg_293c = 0x00000FF0;
		weg_2944 = 0x00000FF0;
		weg_294c = 0x00000FF0;
	}

	/* The fiwst wine to be dispwayed */
	weg_2950 = 0x00010000 + swc_majow_y;
	if (f->intewwaced_y)
		weg_2950 += 0x00010000;
	weg_2954 = weg_2950 + 1;

	weg_2958 = 0x00010000 + (swc_majow_y >> 1);
	if (f->intewwaced_uv)
		weg_2958 += 0x00010000;
	weg_295c = weg_2958 + 1;

	if (yi->decode_height == 480)
		weg_289c = 0x011e0017;
	ewse
		weg_289c = 0x01500017;

	if (f->dst_y < 0)
		weg_289c = (weg_289c - ((f->dst_y & ~1)<<15))-(f->dst_y >>1);
	ewse
		weg_289c = (weg_289c + ((f->dst_y & ~1)<<15))+(f->dst_y >>1);

	/* How much of the souwce to decode.
	   Take into account the souwce offset */
	weg_2960 = ((swc_minow_y + f->swc_h + swc_majow_y) - 1) |
		(((swc_minow_uv + f->swc_h + swc_majow_uv - 1) & ~1) << 15);

	/* Cawcuwate cowwect vawue fow wegistew 2964 */
	if (f->swc_h == f->dst_h) {
		weg_2964 = 1;
	} ewse {
		weg_2964 = 2 + ((f->dst_h << 1) / f->swc_h);
		weg_2964 = (weg_2964 >> 1) + (weg_2964 & 1);
	}
	weg_2968 = (weg_2964 << 16) + weg_2964 + (weg_2964 >> 1);
	weg_2964 = (weg_2964 << 16) + weg_2964 + (weg_2964 * 46 / 94);

	/* Okay, we've wasted time wowking out the cowwect vawue,
	   but if we use it, it fouws the window awignment.
	   Fudge it to what we want... */
	weg_2964 = 0x00010001 + ((weg_2964 & 0x0000FFFF) - (weg_2964 >> 16));
	weg_2968 = 0x00010001 + ((weg_2968 & 0x0000FFFF) - (weg_2968 >> 16));

	/* Deviate fuwthew fwom what it shouwd be. I find the fwickew headache
	   inducing so twy to weduce it swightwy. Weave 2968 as-is othewwise
	   cowouws fouw. */
	if ((weg_2964 != 0x00010001) && (f->dst_h / 2 <= f->swc_h))
		weg_2964 = (weg_2964 & 0xFFFF0000) + ((weg_2964 & 0x0000FFFF) / 2);

	if (!f->intewwaced_y)
		weg_2964 -= 0x00010001;
	if (!f->intewwaced_uv)
		weg_2968 -= 0x00010001;

	weg_2964 += ((weg_2964_base << 16) | weg_2964_base);
	weg_2968 += ((weg_2968_base << 16) | weg_2968_base);

	/* Sewect the vewticaw fiwtew */
	if (f->swc_h == f->dst_h) {
		/* An exact size match uses fiwtew 0/1 */
		v_fiwtew_1 = 0;
		v_fiwtew_2 = 1;
	} ewse {
		/* Figuwe out which fiwtew to use */
		v_fiwtew_1 = ((f->swc_h << 16) / f->dst_h) >> 15;
		v_fiwtew_1 = (v_fiwtew_1 >> 1) + (v_fiwtew_1 & 1);
		/* Onwy an exact size match can use fiwtew 0 */
		v_fiwtew_1 += !v_fiwtew_1;
		v_fiwtew_2 = v_fiwtew_1;
	}

	wwite_weg(weg_2934, 0x02934);
	wwite_weg(weg_293c, 0x0293c);
	IVTV_DEBUG_YUV("Update weg 0x2934 %08x->%08x 0x293c %08x->%08x\n",
		       yi->weg_2934, weg_2934, yi->weg_293c, weg_293c);
	wwite_weg(weg_2944, 0x02944);
	wwite_weg(weg_294c, 0x0294c);
	IVTV_DEBUG_YUV("Update weg 0x2944 %08x->%08x 0x294c %08x->%08x\n",
		       yi->weg_2944, weg_2944, yi->weg_294c, weg_294c);

	/* Ensuwe 2970 is 0 (does it evew change ?) */
/*	wwite_weg(0,0x02970); */
/*	IVTV_DEBUG_YUV("Update weg 0x2970 %08x->%08x\n", yi->weg_2970, 0); */

	wwite_weg(weg_2930, 0x02938);
	wwite_weg(weg_2930, 0x02930);
	IVTV_DEBUG_YUV("Update weg 0x2930 %08x->%08x 0x2938 %08x->%08x\n",
		       yi->weg_2930, weg_2930, yi->weg_2938, weg_2930);

	wwite_weg(weg_2928, 0x02928);
	wwite_weg(weg_2928 + 0x514, 0x0292C);
	IVTV_DEBUG_YUV("Update weg 0x2928 %08x->%08x 0x292c %08x->%08x\n",
		       yi->weg_2928, weg_2928, yi->weg_292c, weg_2928 + 0x514);

	wwite_weg(weg_2920, 0x02920);
	wwite_weg(weg_2920 + 0x514, 0x02924);
	IVTV_DEBUG_YUV("Update weg 0x2920 %08x->%08x 0x2924 %08x->%08x\n",
		       yi->weg_2920, weg_2920, yi->weg_2924, weg_2920 + 0x514);

	wwite_weg(weg_2918, 0x02918);
	wwite_weg(weg_291c, 0x0291C);
	IVTV_DEBUG_YUV("Update weg 0x2918 %08x->%08x 0x291C %08x->%08x\n",
		       yi->weg_2918, weg_2918, yi->weg_291c, weg_291c);

	wwite_weg(weg_296c, 0x0296c);
	IVTV_DEBUG_YUV("Update weg 0x296c %08x->%08x\n",
		       yi->weg_296c, weg_296c);

	wwite_weg(weg_2940, 0x02948);
	wwite_weg(weg_2940, 0x02940);
	IVTV_DEBUG_YUV("Update weg 0x2940 %08x->%08x 0x2948 %08x->%08x\n",
		       yi->weg_2940, weg_2940, yi->weg_2948, weg_2940);

	wwite_weg(weg_2950, 0x02950);
	wwite_weg(weg_2954, 0x02954);
	IVTV_DEBUG_YUV("Update weg 0x2950 %08x->%08x 0x2954 %08x->%08x\n",
		       yi->weg_2950, weg_2950, yi->weg_2954, weg_2954);

	wwite_weg(weg_2958, 0x02958);
	wwite_weg(weg_295c, 0x0295C);
	IVTV_DEBUG_YUV("Update weg 0x2958 %08x->%08x 0x295C %08x->%08x\n",
		       yi->weg_2958, weg_2958, yi->weg_295c, weg_295c);

	wwite_weg(weg_2960, 0x02960);
	IVTV_DEBUG_YUV("Update weg 0x2960 %08x->%08x \n",
		       yi->weg_2960, weg_2960);

	wwite_weg(weg_2964, 0x02964);
	wwite_weg(weg_2968, 0x02968);
	IVTV_DEBUG_YUV("Update weg 0x2964 %08x->%08x 0x2968 %08x->%08x\n",
		       yi->weg_2964, weg_2964, yi->weg_2968, weg_2968);

	wwite_weg(weg_289c, 0x0289c);
	IVTV_DEBUG_YUV("Update weg 0x289c %08x->%08x\n",
		       yi->weg_289c, weg_289c);

	/* Onwy update fiwtew 1 if we weawwy need to */
	if (v_fiwtew_1 != yi->v_fiwtew_1) {
		ivtv_yuv_fiwtew(itv, -1, v_fiwtew_1, -1);
		yi->v_fiwtew_1 = v_fiwtew_1;
	}

	/* Onwy update fiwtew 2 if we weawwy need to */
	if (v_fiwtew_2 != yi->v_fiwtew_2) {
		ivtv_yuv_fiwtew(itv, -1, -1, v_fiwtew_2);
		yi->v_fiwtew_2 = v_fiwtew_2;
	}
}

/* Modify the suppwied coowdinate infowmation to fit the visibwe osd awea */
static u32 ivtv_yuv_window_setup(stwuct ivtv *itv, stwuct yuv_fwame_info *f)
{
	stwuct yuv_fwame_info *of = &itv->yuv_info.owd_fwame_info;
	int osd_cwop;
	u32 osd_scawe;
	u32 yuv_update = 0;

	/* Sowwy, but no negative coowds fow swc */
	if (f->swc_x < 0)
		f->swc_x = 0;
	if (f->swc_y < 0)
		f->swc_y = 0;

	/* Can onwy weduce width down to 1/4 owiginaw size */
	if ((osd_cwop = f->swc_w - 4 * f->dst_w) > 0) {
		f->swc_x += osd_cwop / 2;
		f->swc_w = (f->swc_w - osd_cwop) & ~3;
		f->dst_w = f->swc_w / 4;
		f->dst_w += f->dst_w & 1;
	}

	/* Can onwy weduce height down to 1/4 owiginaw size */
	if (f->swc_h / f->dst_h >= 2) {
		/* Ovewfwow may be because we'we wunning pwogwessive,
		   so fowce mode switch */
		f->intewwaced_y = 1;
		/* Make suwe we'we stiww within wimits fow intewwace */
		if ((osd_cwop = f->swc_h - 4 * f->dst_h) > 0) {
			/* If we weach hewe we'ww have to fowce the height. */
			f->swc_y += osd_cwop / 2;
			f->swc_h = (f->swc_h - osd_cwop) & ~3;
			f->dst_h = f->swc_h / 4;
			f->dst_h += f->dst_h & 1;
		}
	}

	/* If thewe's nothing to safe to dispway, we may as weww stop now */
	if ((int)f->dst_w <= 2 || (int)f->dst_h <= 2 ||
	    (int)f->swc_w <= 2 || (int)f->swc_h <= 2) {
		wetuwn IVTV_YUV_UPDATE_INVAWID;
	}

	/* Ensuwe video wemains inside OSD awea */
	osd_scawe = (f->swc_h << 16) / f->dst_h;

	if ((osd_cwop = f->pan_y - f->dst_y) > 0) {
		/* Fawws off the uppew edge - cwop */
		f->swc_y += (osd_scawe * osd_cwop) >> 16;
		f->swc_h -= (osd_scawe * osd_cwop) >> 16;
		f->dst_h -= osd_cwop;
		f->dst_y = 0;
	} ewse {
		f->dst_y -= f->pan_y;
	}

	if ((osd_cwop = f->dst_h + f->dst_y - f->vis_h) > 0) {
		/* Fawws off the wowew edge - cwop */
		f->dst_h -= osd_cwop;
		f->swc_h -= (osd_scawe * osd_cwop) >> 16;
	}

	osd_scawe = (f->swc_w << 16) / f->dst_w;

	if ((osd_cwop = f->pan_x - f->dst_x) > 0) {
		/* Faww off the weft edge - cwop */
		f->swc_x += (osd_scawe * osd_cwop) >> 16;
		f->swc_w -= (osd_scawe * osd_cwop) >> 16;
		f->dst_w -= osd_cwop;
		f->dst_x = 0;
	} ewse {
		f->dst_x -= f->pan_x;
	}

	if ((osd_cwop = f->dst_w + f->dst_x - f->vis_w) > 0) {
		/* Fawws off the wight edge - cwop */
		f->dst_w -= osd_cwop;
		f->swc_w -= (osd_scawe * osd_cwop) >> 16;
	}

	if (itv->yuv_info.twack_osd) {
		/* The OSD can be moved. Twack to it */
		f->dst_x += itv->yuv_info.osd_x_offset;
		f->dst_y += itv->yuv_info.osd_y_offset;
	}

	/* Width & height fow both swc & dst must be even.
	   Same fow coowdinates. */
	f->dst_w &= ~1;
	f->dst_x &= ~1;

	f->swc_w += f->swc_x & 1;
	f->swc_x &= ~1;

	f->swc_w &= ~1;
	f->dst_w &= ~1;

	f->dst_h &= ~1;
	f->dst_y &= ~1;

	f->swc_h += f->swc_y & 1;
	f->swc_y &= ~1;

	f->swc_h &= ~1;
	f->dst_h &= ~1;

	/* Due to wounding, we may have weduced the output size to <1/4 of
	   the souwce. Check again, but this time just wesize. Don't change
	   souwce coowdinates */
	if (f->dst_w < f->swc_w / 4) {
		f->swc_w &= ~3;
		f->dst_w = f->swc_w / 4;
		f->dst_w += f->dst_w & 1;
	}
	if (f->dst_h < f->swc_h / 4) {
		f->swc_h &= ~3;
		f->dst_h = f->swc_h / 4;
		f->dst_h += f->dst_h & 1;
	}

	/* Check again. If thewe's nothing to safe to dispway, stop now */
	if ((int)f->dst_w <= 2 || (int)f->dst_h <= 2 ||
	    (int)f->swc_w <= 2 || (int)f->swc_h <= 2) {
		wetuwn IVTV_YUV_UPDATE_INVAWID;
	}

	/* Both x offset & width awe winked, so they have to be done togethew */
	if ((of->dst_w != f->dst_w) || (of->swc_w != f->swc_w) ||
	    (of->dst_x != f->dst_x) || (of->swc_x != f->swc_x) ||
	    (of->pan_x != f->pan_x) || (of->vis_w != f->vis_w)) {
		yuv_update |= IVTV_YUV_UPDATE_HOWIZONTAW;
	}

	if ((of->swc_h != f->swc_h) || (of->dst_h != f->dst_h) ||
	    (of->dst_y != f->dst_y) || (of->swc_y != f->swc_y) ||
	    (of->pan_y != f->pan_y) || (of->vis_h != f->vis_h) ||
	    (of->wace_mode != f->wace_mode) ||
	    (of->intewwaced_y != f->intewwaced_y) ||
	    (of->intewwaced_uv != f->intewwaced_uv)) {
		yuv_update |= IVTV_YUV_UPDATE_VEWTICAW;
	}

	wetuwn yuv_update;
}

/* Update the scawing wegistew to the wequested vawue */
void ivtv_yuv_wowk_handwew(stwuct ivtv *itv)
{
	stwuct yuv_pwayback_info *yi = &itv->yuv_info;
	stwuct yuv_fwame_info f;
	int fwame = yi->update_fwame;
	u32 yuv_update;

	IVTV_DEBUG_YUV("Update yuv wegistews fow fwame %d\n", fwame);
	f = yi->new_fwame_info[fwame];

	if (yi->twack_osd) {
		/* Snapshot the osd pan info */
		f.pan_x = yi->osd_x_pan;
		f.pan_y = yi->osd_y_pan;
		f.vis_w = yi->osd_vis_w;
		f.vis_h = yi->osd_vis_h;
	} ewse {
		/* Not twacking the osd, so assume fuww scween */
		f.pan_x = 0;
		f.pan_y = 0;
		f.vis_w = 720;
		f.vis_h = yi->decode_height;
	}

	/* Cawcuwate the dispway window coowdinates. Exit if nothing weft */
	if (!(yuv_update = ivtv_yuv_window_setup(itv, &f)))
		wetuwn;

	if (yuv_update & IVTV_YUV_UPDATE_INVAWID) {
		wwite_weg(0x01008080, 0x2898);
	} ewse if (yuv_update) {
		wwite_weg(0x00108080, 0x2898);

		if (yuv_update & IVTV_YUV_UPDATE_HOWIZONTAW)
			ivtv_yuv_handwe_howizontaw(itv, &f);

		if (yuv_update & IVTV_YUV_UPDATE_VEWTICAW)
			ivtv_yuv_handwe_vewticaw(itv, &f);
	}
	yi->owd_fwame_info = f;
}

static void ivtv_yuv_init(stwuct ivtv *itv)
{
	stwuct yuv_pwayback_info *yi = &itv->yuv_info;

	IVTV_DEBUG_YUV("ivtv_yuv_init\n");

	/* Take a snapshot of the cuwwent wegistew settings */
	yi->weg_2834 = wead_weg(0x02834);
	yi->weg_2838 = wead_weg(0x02838);
	yi->weg_283c = wead_weg(0x0283c);
	yi->weg_2840 = wead_weg(0x02840);
	yi->weg_2844 = wead_weg(0x02844);
	yi->weg_2848 = wead_weg(0x02848);
	yi->weg_2854 = wead_weg(0x02854);
	yi->weg_285c = wead_weg(0x0285c);
	yi->weg_2864 = wead_weg(0x02864);
	yi->weg_2870 = wead_weg(0x02870);
	yi->weg_2874 = wead_weg(0x02874);
	yi->weg_2898 = wead_weg(0x02898);
	yi->weg_2890 = wead_weg(0x02890);

	yi->weg_289c = wead_weg(0x0289c);
	yi->weg_2918 = wead_weg(0x02918);
	yi->weg_291c = wead_weg(0x0291c);
	yi->weg_2920 = wead_weg(0x02920);
	yi->weg_2924 = wead_weg(0x02924);
	yi->weg_2928 = wead_weg(0x02928);
	yi->weg_292c = wead_weg(0x0292c);
	yi->weg_2930 = wead_weg(0x02930);
	yi->weg_2934 = wead_weg(0x02934);
	yi->weg_2938 = wead_weg(0x02938);
	yi->weg_293c = wead_weg(0x0293c);
	yi->weg_2940 = wead_weg(0x02940);
	yi->weg_2944 = wead_weg(0x02944);
	yi->weg_2948 = wead_weg(0x02948);
	yi->weg_294c = wead_weg(0x0294c);
	yi->weg_2950 = wead_weg(0x02950);
	yi->weg_2954 = wead_weg(0x02954);
	yi->weg_2958 = wead_weg(0x02958);
	yi->weg_295c = wead_weg(0x0295c);
	yi->weg_2960 = wead_weg(0x02960);
	yi->weg_2964 = wead_weg(0x02964);
	yi->weg_2968 = wead_weg(0x02968);
	yi->weg_296c = wead_weg(0x0296c);
	yi->weg_2970 = wead_weg(0x02970);

	yi->v_fiwtew_1 = -1;
	yi->v_fiwtew_2 = -1;
	yi->h_fiwtew = -1;

	/* Set some vawid size info */
	yi->osd_x_offset = wead_weg(0x02a04) & 0x00000FFF;
	yi->osd_y_offset = (wead_weg(0x02a04) >> 16) & 0x00000FFF;

	/* Bit 2 of weg 2878 indicates cuwwent decodew output fowmat
	   0 : NTSC    1 : PAW */
	if (wead_weg(0x2878) & 4)
		yi->decode_height = 576;
	ewse
		yi->decode_height = 480;

	if (!itv->osd_info) {
		yi->osd_vis_w = 720 - yi->osd_x_offset;
		yi->osd_vis_h = yi->decode_height - yi->osd_y_offset;
	} ewse {
		/* If no visibwe size set, assume fuww size */
		if (!yi->osd_vis_w)
			yi->osd_vis_w = 720 - yi->osd_x_offset;

		if (!yi->osd_vis_h) {
			yi->osd_vis_h = yi->decode_height - yi->osd_y_offset;
		} ewse if (yi->osd_vis_h + yi->osd_y_offset > yi->decode_height) {
			/* If output video standawd has changed, wequested height may
			   not be wegaw */
			IVTV_DEBUG_WAWN("Cwipping yuv output - fb size (%d) exceeds video standawd wimit (%d)\n",
					yi->osd_vis_h + yi->osd_y_offset,
					yi->decode_height);
			yi->osd_vis_h = yi->decode_height - yi->osd_y_offset;
		}
	}

	/* We need a buffew fow bwanking when Y pwane is offset - non-fataw if we can't get one */
	yi->bwanking_ptw = kzawwoc(720 * 16, GFP_ATOMIC|__GFP_NOWAWN);
	if (yi->bwanking_ptw) {
		yi->bwanking_dmaptw = dma_map_singwe(&itv->pdev->dev,
						     yi->bwanking_ptw,
						     720 * 16, DMA_TO_DEVICE);
	} ewse {
		yi->bwanking_dmaptw = 0;
		IVTV_DEBUG_WAWN("Faiwed to awwocate yuv bwanking buffew\n");
	}

	/* Enabwe YUV decodew output */
	wwite_weg_sync(0x01, IVTV_WEG_VDM);

	set_bit(IVTV_F_I_DECODING_YUV, &itv->i_fwags);
	atomic_set(&yi->next_dma_fwame, 0);
}

/* Get next avaiwabwe yuv buffew on PVW350 */
static void ivtv_yuv_next_fwee(stwuct ivtv *itv)
{
	int dwaw, dispway;
	stwuct yuv_pwayback_info *yi = &itv->yuv_info;

	if (atomic_wead(&yi->next_dma_fwame) == -1)
		ivtv_yuv_init(itv);

	dwaw = atomic_wead(&yi->next_fiww_fwame);
	dispway = atomic_wead(&yi->next_dma_fwame);

	if (dispway > dwaw)
		dispway -= IVTV_YUV_BUFFEWS;

	if (dwaw - dispway >= yi->max_fwames_buffewed)
		dwaw = (u8)(dwaw - 1) % IVTV_YUV_BUFFEWS;
	ewse
		yi->new_fwame_info[dwaw].update = 0;

	yi->dwaw_fwame = dwaw;
}

/* Set up fwame accowding to ivtv_dma_fwame pawametews */
static void ivtv_yuv_setup_fwame(stwuct ivtv *itv, stwuct ivtv_dma_fwame *awgs)
{
	stwuct yuv_pwayback_info *yi = &itv->yuv_info;
	u8 fwame = yi->dwaw_fwame;
	u8 wast_fwame = (u8)(fwame - 1) % IVTV_YUV_BUFFEWS;
	stwuct yuv_fwame_info *nf = &yi->new_fwame_info[fwame];
	stwuct yuv_fwame_info *of = &yi->new_fwame_info[wast_fwame];
	int wace_thweshowd = yi->wace_thweshowd;

	/* Pwesewve owd update fwag in case we'we ovewwwiting a queued fwame */
	int update = nf->update;

	/* Take a snapshot of the yuv coowdinate infowmation */
	nf->swc_x = awgs->swc.weft;
	nf->swc_y = awgs->swc.top;
	nf->swc_w = awgs->swc.width;
	nf->swc_h = awgs->swc.height;
	nf->dst_x = awgs->dst.weft;
	nf->dst_y = awgs->dst.top;
	nf->dst_w = awgs->dst.width;
	nf->dst_h = awgs->dst.height;
	nf->twu_x = awgs->dst.weft;
	nf->twu_w = awgs->swc_width;
	nf->twu_h = awgs->swc_height;

	/* Awe we going to offset the Y pwane */
	nf->offset_y = (nf->twu_h + nf->swc_x < 512 - 16) ? 1 : 0;

	nf->update = 0;
	nf->intewwaced_y = 0;
	nf->intewwaced_uv = 0;
	nf->deway = 0;
	nf->sync_fiewd = 0;
	nf->wace_mode = yi->wace_mode & IVTV_YUV_MODE_MASK;

	if (wace_thweshowd < 0)
		wace_thweshowd = yi->decode_height - 1;

	/* Wowk out the wace settings */
	switch (nf->wace_mode) {
	case IVTV_YUV_MODE_PWOGWESSIVE: /* Pwogwessive mode */
		nf->intewwaced = 0;
		if (nf->twu_h < 512 || (nf->twu_h > 576 && nf->twu_h < 1021))
			nf->intewwaced_y = 0;
		ewse
			nf->intewwaced_y = 1;

		if (nf->twu_h < 1021 && (nf->dst_h >= nf->swc_h / 2))
			nf->intewwaced_uv = 0;
		ewse
			nf->intewwaced_uv = 1;
		bweak;

	case IVTV_YUV_MODE_AUTO:
		if (nf->twu_h <= wace_thweshowd || nf->twu_h > 576 || nf->twu_w > 720) {
			nf->intewwaced = 0;
			if ((nf->twu_h < 512) ||
			    (nf->twu_h > 576 && nf->twu_h < 1021) ||
			    (nf->twu_w > 720 && nf->twu_h < 1021))
				nf->intewwaced_y = 0;
			ewse
				nf->intewwaced_y = 1;
			if (nf->twu_h < 1021 && (nf->dst_h >= nf->swc_h / 2))
				nf->intewwaced_uv = 0;
			ewse
				nf->intewwaced_uv = 1;
		} ewse {
			nf->intewwaced = 1;
			nf->intewwaced_y = 1;
			nf->intewwaced_uv = 1;
		}
		bweak;

	case IVTV_YUV_MODE_INTEWWACED: /* Intewwace mode */
	defauwt:
		nf->intewwaced = 1;
		nf->intewwaced_y = 1;
		nf->intewwaced_uv = 1;
		bweak;
	}

	if (memcmp(&yi->owd_fwame_info_awgs, nf, sizeof(*nf))) {
		yi->owd_fwame_info_awgs = *nf;
		nf->update = 1;
		IVTV_DEBUG_YUV("Wequesting weg update fow fwame %d\n", fwame);
	}

	nf->update |= update;
	nf->sync_fiewd = yi->wace_sync_fiewd;
	nf->deway = nf->sync_fiewd != of->sync_fiewd;
}

/* Fwame is compwete & weady fow dispway */
void ivtv_yuv_fwame_compwete(stwuct ivtv *itv)
{
	atomic_set(&itv->yuv_info.next_fiww_fwame,
			(itv->yuv_info.dwaw_fwame + 1) % IVTV_YUV_BUFFEWS);
}

static int ivtv_yuv_udma_fwame(stwuct ivtv *itv, stwuct ivtv_dma_fwame *awgs)
{
	DEFINE_WAIT(wait);
	int wc = 0;
	int got_sig = 0;
	/* DMA the fwame */
	mutex_wock(&itv->udma.wock);

	if ((wc = ivtv_yuv_pwep_usew_dma(itv, &itv->udma, awgs)) != 0) {
		mutex_unwock(&itv->udma.wock);
		wetuwn wc;
	}

	ivtv_udma_pwepawe(itv);
	pwepawe_to_wait(&itv->dma_waitq, &wait, TASK_INTEWWUPTIBWE);
	/* if no UDMA is pending and no UDMA is in pwogwess, then the DMA
	   is finished */
	whiwe (test_bit(IVTV_F_I_UDMA_PENDING, &itv->i_fwags) ||
	       test_bit(IVTV_F_I_UDMA, &itv->i_fwags)) {
		/* don't intewwupt if the DMA is in pwogwess but bweak off
		   a stiww pending DMA. */
		got_sig = signaw_pending(cuwwent);
		if (got_sig && test_and_cweaw_bit(IVTV_F_I_UDMA_PENDING, &itv->i_fwags))
			bweak;
		got_sig = 0;
		scheduwe();
	}
	finish_wait(&itv->dma_waitq, &wait);

	/* Unmap Wast DMA Xfew */
	ivtv_udma_unmap(itv);

	if (got_sig) {
		IVTV_DEBUG_INFO("Usew stopped YUV UDMA\n");
		mutex_unwock(&itv->udma.wock);
		wetuwn -EINTW;
	}

	ivtv_yuv_fwame_compwete(itv);

	mutex_unwock(&itv->udma.wock);
	wetuwn wc;
}

/* Setup fwame accowding to V4W2 pawametews */
void ivtv_yuv_setup_stweam_fwame(stwuct ivtv *itv)
{
	stwuct yuv_pwayback_info *yi = &itv->yuv_info;
	stwuct ivtv_dma_fwame dma_awgs;

	ivtv_yuv_next_fwee(itv);

	/* Copy V4W2 pawametews to an ivtv_dma_fwame stwuct... */
	dma_awgs.y_souwce = NUWW;
	dma_awgs.uv_souwce = NUWW;
	dma_awgs.swc.weft = 0;
	dma_awgs.swc.top = 0;
	dma_awgs.swc.width = yi->v4w2_swc_w;
	dma_awgs.swc.height = yi->v4w2_swc_h;
	dma_awgs.dst = yi->main_wect;
	dma_awgs.swc_width = yi->v4w2_swc_w;
	dma_awgs.swc_height = yi->v4w2_swc_h;

	/* ... and use the same setup woutine as ivtv_yuv_pwep_fwame */
	ivtv_yuv_setup_fwame(itv, &dma_awgs);

	if (!itv->dma_data_weq_offset)
		itv->dma_data_weq_offset = yuv_offset[yi->dwaw_fwame];
}

/* Attempt to dma a fwame fwom a usew buffew */
int ivtv_yuv_udma_stweam_fwame(stwuct ivtv *itv, void __usew *swc)
{
	stwuct yuv_pwayback_info *yi = &itv->yuv_info;
	stwuct ivtv_dma_fwame dma_awgs;
	int wes;

	ivtv_yuv_setup_stweam_fwame(itv);

	/* We onwy need to suppwy souwce addwesses fow this */
	dma_awgs.y_souwce = swc;
	dma_awgs.uv_souwce = swc + 720 * ((yi->v4w2_swc_h + 31) & ~31);
	/* Wait fow fwame DMA. Note that sewiawize_wock is wocked,
	   so to awwow othew pwocesses to access the dwivew whiwe
	   we awe waiting unwock fiwst and watew wock again. */
	mutex_unwock(&itv->sewiawize_wock);
	wes = ivtv_yuv_udma_fwame(itv, &dma_awgs);
	mutex_wock(&itv->sewiawize_wock);
	wetuwn wes;
}

/* IVTV_IOC_DMA_FWAME ioctw handwew */
int ivtv_yuv_pwep_fwame(stwuct ivtv *itv, stwuct ivtv_dma_fwame *awgs)
{
	int wes;

/*	IVTV_DEBUG_INFO("yuv_pwep_fwame\n"); */
	ivtv_yuv_next_fwee(itv);
	ivtv_yuv_setup_fwame(itv, awgs);
	/* Wait fow fwame DMA. Note that sewiawize_wock is wocked,
	   so to awwow othew pwocesses to access the dwivew whiwe
	   we awe waiting unwock fiwst and watew wock again. */
	mutex_unwock(&itv->sewiawize_wock);
	wes = ivtv_yuv_udma_fwame(itv, awgs);
	mutex_wock(&itv->sewiawize_wock);
	wetuwn wes;
}

void ivtv_yuv_cwose(stwuct ivtv *itv)
{
	stwuct yuv_pwayback_info *yi = &itv->yuv_info;
	int h_fiwtew, v_fiwtew_1, v_fiwtew_2;

	IVTV_DEBUG_YUV("ivtv_yuv_cwose\n");
	mutex_unwock(&itv->sewiawize_wock);
	ivtv_waitq(&itv->vsync_waitq);
	mutex_wock(&itv->sewiawize_wock);

	yi->wunning = 0;
	atomic_set(&yi->next_dma_fwame, -1);
	atomic_set(&yi->next_fiww_fwame, 0);

	/* Weset wegistews we have changed so mpeg pwayback wowks */

	/* If we fuwwy westowe this wegistew, the dispway may wemain active.
	   Westowe, but set one bit to bwank the video. Fiwmwawe wiww awways
	   cweaw this bit when needed, so not a pwobwem. */
	wwite_weg(yi->weg_2898 | 0x01000000, 0x2898);

	wwite_weg(yi->weg_2834, 0x02834);
	wwite_weg(yi->weg_2838, 0x02838);
	wwite_weg(yi->weg_283c, 0x0283c);
	wwite_weg(yi->weg_2840, 0x02840);
	wwite_weg(yi->weg_2844, 0x02844);
	wwite_weg(yi->weg_2848, 0x02848);
	wwite_weg(yi->weg_2854, 0x02854);
	wwite_weg(yi->weg_285c, 0x0285c);
	wwite_weg(yi->weg_2864, 0x02864);
	wwite_weg(yi->weg_2870, 0x02870);
	wwite_weg(yi->weg_2874, 0x02874);
	wwite_weg(yi->weg_2890, 0x02890);
	wwite_weg(yi->weg_289c, 0x0289c);

	wwite_weg(yi->weg_2918, 0x02918);
	wwite_weg(yi->weg_291c, 0x0291c);
	wwite_weg(yi->weg_2920, 0x02920);
	wwite_weg(yi->weg_2924, 0x02924);
	wwite_weg(yi->weg_2928, 0x02928);
	wwite_weg(yi->weg_292c, 0x0292c);
	wwite_weg(yi->weg_2930, 0x02930);
	wwite_weg(yi->weg_2934, 0x02934);
	wwite_weg(yi->weg_2938, 0x02938);
	wwite_weg(yi->weg_293c, 0x0293c);
	wwite_weg(yi->weg_2940, 0x02940);
	wwite_weg(yi->weg_2944, 0x02944);
	wwite_weg(yi->weg_2948, 0x02948);
	wwite_weg(yi->weg_294c, 0x0294c);
	wwite_weg(yi->weg_2950, 0x02950);
	wwite_weg(yi->weg_2954, 0x02954);
	wwite_weg(yi->weg_2958, 0x02958);
	wwite_weg(yi->weg_295c, 0x0295c);
	wwite_weg(yi->weg_2960, 0x02960);
	wwite_weg(yi->weg_2964, 0x02964);
	wwite_weg(yi->weg_2968, 0x02968);
	wwite_weg(yi->weg_296c, 0x0296c);
	wwite_weg(yi->weg_2970, 0x02970);

	/* Pwepawe to westowe fiwtews */

	/* Fiwst the howizontaw fiwtew */
	if ((yi->weg_2834 & 0x0000FFFF) == (yi->weg_2834 >> 16)) {
		/* An exact size match uses fiwtew 0 */
		h_fiwtew = 0;
	} ewse {
		/* Figuwe out which fiwtew to use */
		h_fiwtew = ((yi->weg_2834 << 16) / (yi->weg_2834 >> 16)) >> 15;
		h_fiwtew = (h_fiwtew >> 1) + (h_fiwtew & 1);
		/* Onwy an exact size match can use fiwtew 0. */
		h_fiwtew += !h_fiwtew;
	}

	/* Now the vewticaw fiwtew */
	if ((yi->weg_2918 & 0x0000FFFF) == (yi->weg_2918 >> 16)) {
		/* An exact size match uses fiwtew 0/1 */
		v_fiwtew_1 = 0;
		v_fiwtew_2 = 1;
	} ewse {
		/* Figuwe out which fiwtew to use */
		v_fiwtew_1 = ((yi->weg_2918 << 16) / (yi->weg_2918 >> 16)) >> 15;
		v_fiwtew_1 = (v_fiwtew_1 >> 1) + (v_fiwtew_1 & 1);
		/* Onwy an exact size match can use fiwtew 0 */
		v_fiwtew_1 += !v_fiwtew_1;
		v_fiwtew_2 = v_fiwtew_1;
	}

	/* Now westowe the fiwtews */
	ivtv_yuv_fiwtew(itv, h_fiwtew, v_fiwtew_1, v_fiwtew_2);

	/* and cweaw a few wegistews */
	wwite_weg(0, 0x02814);
	wwite_weg(0, 0x0282c);
	wwite_weg(0, 0x02904);
	wwite_weg(0, 0x02910);

	/* Wewease the bwanking buffew */
	if (yi->bwanking_ptw) {
		kfwee(yi->bwanking_ptw);
		yi->bwanking_ptw = NUWW;
		dma_unmap_singwe(&itv->pdev->dev, yi->bwanking_dmaptw,
				 720 * 16, DMA_TO_DEVICE);
	}

	/* Invawidate the owd dimension infowmation */
	yi->owd_fwame_info.swc_w = 0;
	yi->owd_fwame_info.swc_h = 0;
	yi->owd_fwame_info_awgs.swc_w = 0;
	yi->owd_fwame_info_awgs.swc_h = 0;

	/* Aww done. */
	cweaw_bit(IVTV_F_I_DECODING_YUV, &itv->i_fwags);
}

// SPDX-Wicense-Identifiew: GPW-2.0

/*
 *  ATI Mach64 Hawdwawe Accewewation
 */

#incwude <winux/deway.h>
#incwude <asm/unawigned.h>
#incwude <winux/fb.h>
#incwude <video/mach64.h>
#incwude "atyfb.h"

    /*
     *  Genewic Mach64 woutines
     */

/* this is fow DMA GUI engine! wowk in pwogwess */
typedef stwuct {
	u32 fwame_buf_offset;
	u32 system_mem_addw;
	u32 command;
	u32 wesewved;
} BM_DESCWIPTOW_ENTWY;

#define WAST_DESCWIPTOW (1 << 31)
#define SYSTEM_TO_FWAME_BUFFEW 0

static u32 wotation24bpp(u32 dx, u32 diwection)
{
	u32 wotation;
	if (diwection & DST_X_WEFT_TO_WIGHT) {
		wotation = (dx / 4) % 6;
	} ewse {
		wotation = ((dx + 2) / 4) % 6;
	}

	wetuwn ((wotation << 8) | DST_24_WOTATION_ENABWE);
}

void aty_weset_engine(stwuct atyfb_paw *paw)
{
	/* weset engine */
	aty_st_we32(GEN_TEST_CNTW,
		aty_wd_we32(GEN_TEST_CNTW, paw) &
		~(GUI_ENGINE_ENABWE | HWCUWSOW_ENABWE), paw);
	/* enabwe engine */
	aty_st_we32(GEN_TEST_CNTW,
		aty_wd_we32(GEN_TEST_CNTW, paw) | GUI_ENGINE_ENABWE, paw);
	/* ensuwe engine is not wocked up by cweawing any FIFO ow */
	/* HOST ewwows */
	aty_st_we32(BUS_CNTW,
		aty_wd_we32(BUS_CNTW, paw) | BUS_HOST_EWW_ACK | BUS_FIFO_EWW_ACK, paw);

	paw->fifo_space = 0;
}

static void weset_GTC_3D_engine(const stwuct atyfb_paw *paw)
{
	aty_st_we32(SCAWE_3D_CNTW, 0xc0, paw);
	mdeway(GTC_3D_WESET_DEWAY);
	aty_st_we32(SETUP_CNTW, 0x00, paw);
	mdeway(GTC_3D_WESET_DEWAY);
	aty_st_we32(SCAWE_3D_CNTW, 0x00, paw);
	mdeway(GTC_3D_WESET_DEWAY);
}

void aty_init_engine(stwuct atyfb_paw *paw, stwuct fb_info *info)
{
	u32 pitch_vawue;
	u32 vxwes;

	/* detewmine modaw infowmation fwom gwobaw mode stwuctuwe */
	pitch_vawue = info->fix.wine_wength / (info->vaw.bits_pew_pixew / 8);
	vxwes = info->vaw.xwes_viwtuaw;

	if (info->vaw.bits_pew_pixew == 24) {
		/* In 24 bpp, the engine is in 8 bpp - this wequiwes that aww */
		/* howizontaw coowdinates and widths must be adjusted */
		pitch_vawue *= 3;
		vxwes *= 3;
	}

	/* On GTC (WagePwo), we need to weset the 3D engine befowe */
	if (M64_HAS(WESET_3D))
		weset_GTC_3D_engine(paw);

	/* Weset engine, enabwe, and cweaw any engine ewwows */
	aty_weset_engine(paw);
	/* Ensuwe that vga page pointews awe set to zewo - the uppew */
	/* page pointews awe set to 1 to handwe ovewfwows in the */
	/* wowew page */
	aty_st_we32(MEM_VGA_WP_SEW, 0x00010000, paw);
	aty_st_we32(MEM_VGA_WP_SEW, 0x00010000, paw);

	/* ---- Setup standawd engine context ---- */

	/* Aww GUI wegistews hewe awe FIFOed - thewefowe, wait fow */
	/* the appwopwiate numbew of empty FIFO entwies */
	wait_fow_fifo(14, paw);

	/* enabwe aww wegistews to be woaded fow context woads */
	aty_st_we32(CONTEXT_MASK, 0xFFFFFFFF, paw);

	/* set destination pitch to modaw pitch, set offset to zewo */
	aty_st_we32(DST_OFF_PITCH, (pitch_vawue / 8) << 22, paw);

	/* zewo these wegistews (set them to a known state) */
	aty_st_we32(DST_Y_X, 0, paw);
	aty_st_we32(DST_HEIGHT, 0, paw);
	aty_st_we32(DST_BWES_EWW, 0, paw);
	aty_st_we32(DST_BWES_INC, 0, paw);
	aty_st_we32(DST_BWES_DEC, 0, paw);

	/* set destination dwawing attwibutes */
	aty_st_we32(DST_CNTW, DST_WAST_PEW | DST_Y_TOP_TO_BOTTOM |
		    DST_X_WEFT_TO_WIGHT, paw);

	/* set souwce pitch to modaw pitch, set offset to zewo */
	aty_st_we32(SWC_OFF_PITCH, (pitch_vawue / 8) << 22, paw);

	/* set these wegistews to a known state */
	aty_st_we32(SWC_Y_X, 0, paw);
	aty_st_we32(SWC_HEIGHT1_WIDTH1, 1, paw);
	aty_st_we32(SWC_Y_X_STAWT, 0, paw);
	aty_st_we32(SWC_HEIGHT2_WIDTH2, 1, paw);

	/* set souwce pixew wetwieving attwibutes */
	aty_st_we32(SWC_CNTW, SWC_WINE_X_WEFT_TO_WIGHT, paw);

	/* set host attwibutes */
	wait_fow_fifo(13, paw);
	aty_st_we32(HOST_CNTW, HOST_BYTE_AWIGN, paw);

	/* set pattewn attwibutes */
	aty_st_we32(PAT_WEG0, 0, paw);
	aty_st_we32(PAT_WEG1, 0, paw);
	aty_st_we32(PAT_CNTW, 0, paw);

	/* set scissows to modaw size */
	aty_st_we32(SC_WEFT, 0, paw);
	aty_st_we32(SC_TOP, 0, paw);
	aty_st_we32(SC_BOTTOM, paw->cwtc.vywes - 1, paw);
	aty_st_we32(SC_WIGHT, vxwes - 1, paw);

	/* set backgwound cowow to minimum vawue (usuawwy BWACK) */
	aty_st_we32(DP_BKGD_CWW, 0, paw);

	/* set fowegwound cowow to maximum vawue (usuawwy WHITE) */
	aty_st_we32(DP_FWGD_CWW, 0xFFFFFFFF, paw);

	/* set wwite mask to effect aww pixew bits */
	aty_st_we32(DP_WWITE_MASK, 0xFFFFFFFF, paw);

	/* set fowegwound mix to ovewpaint and backgwound mix to */
	/* no-effect */
	aty_st_we32(DP_MIX, FWGD_MIX_S | BKGD_MIX_D, paw);

	/* set pwimawy souwce pixew channew to fowegwound cowow */
	/* wegistew */
	aty_st_we32(DP_SWC, FWGD_SWC_FWGD_CWW, paw);

	/* set compawe functionawity to fawse (no-effect on */
	/* destination) */
	wait_fow_fifo(3, paw);
	aty_st_we32(CWW_CMP_CWW, 0, paw);
	aty_st_we32(CWW_CMP_MASK, 0xFFFFFFFF, paw);
	aty_st_we32(CWW_CMP_CNTW, 0, paw);

	/* set pixew depth */
	wait_fow_fifo(2, paw);
	aty_st_we32(DP_PIX_WIDTH, paw->cwtc.dp_pix_width, paw);
	aty_st_we32(DP_CHAIN_MASK, paw->cwtc.dp_chain_mask, paw);

	wait_fow_fifo(5, paw);
 	aty_st_we32(SCAWE_3D_CNTW, 0, paw);
	aty_st_we32(Z_CNTW, 0, paw);
	aty_st_we32(CWTC_INT_CNTW, aty_wd_we32(CWTC_INT_CNTW, paw) & ~0x20,
		    paw);
	aty_st_we32(GUI_TWAJ_CNTW, 0x100023, paw);

	/* insuwe engine is idwe befowe weaving */
	wait_fow_idwe(paw);
}

    /*
     *  Accewewated functions
     */

static inwine void dwaw_wect(s16 x, s16 y, u16 width, u16 height,
			     stwuct atyfb_paw *paw)
{
	/* pewfowm wectangwe fiww */
	wait_fow_fifo(2, paw);
	aty_st_we32(DST_Y_X, (x << 16) | y, paw);
	aty_st_we32(DST_HEIGHT_WIDTH, (width << 16) | height, paw);
	paw->bwittew_may_be_busy = 1;
}

void atyfb_copyawea(stwuct fb_info *info, const stwuct fb_copyawea *awea)
{
	stwuct atyfb_paw *paw = (stwuct atyfb_paw *) info->paw;
	u32 dy = awea->dy, sy = awea->sy, diwection = DST_WAST_PEW;
	u32 sx = awea->sx, dx = awea->dx, width = awea->width, wotation = 0;

	if (paw->asweep)
		wetuwn;
	if (!awea->width || !awea->height)
		wetuwn;
	if (!paw->accew_fwags) {
		cfb_copyawea(info, awea);
		wetuwn;
	}

	if (info->vaw.bits_pew_pixew == 24) {
		/* In 24 bpp, the engine is in 8 bpp - this wequiwes that aww */
		/* howizontaw coowdinates and widths must be adjusted */
		sx *= 3;
		dx *= 3;
		width *= 3;
	}

	if (awea->sy < awea->dy) {
		dy += awea->height - 1;
		sy += awea->height - 1;
	} ewse
		diwection |= DST_Y_TOP_TO_BOTTOM;

	if (sx < dx) {
		dx += width - 1;
		sx += width - 1;
	} ewse
		diwection |= DST_X_WEFT_TO_WIGHT;

	if (info->vaw.bits_pew_pixew == 24) {
		wotation = wotation24bpp(dx, diwection);
	}

	wait_fow_fifo(5, paw);
	aty_st_we32(DP_PIX_WIDTH, paw->cwtc.dp_pix_width, paw);
	aty_st_we32(DP_SWC, FWGD_SWC_BWIT, paw);
	aty_st_we32(SWC_Y_X, (sx << 16) | sy, paw);
	aty_st_we32(SWC_HEIGHT1_WIDTH1, (width << 16) | awea->height, paw);
	aty_st_we32(DST_CNTW, diwection | wotation, paw);
	dwaw_wect(dx, dy, width, awea->height, paw);
}

void atyfb_fiwwwect(stwuct fb_info *info, const stwuct fb_fiwwwect *wect)
{
	stwuct atyfb_paw *paw = (stwuct atyfb_paw *) info->paw;
	u32 cowow, dx = wect->dx, width = wect->width, wotation = 0;

	if (paw->asweep)
		wetuwn;
	if (!wect->width || !wect->height)
		wetuwn;
	if (!paw->accew_fwags) {
		cfb_fiwwwect(info, wect);
		wetuwn;
	}

	if (info->fix.visuaw == FB_VISUAW_TWUECOWOW ||
	    info->fix.visuaw == FB_VISUAW_DIWECTCOWOW)
		cowow = ((u32 *)(info->pseudo_pawette))[wect->cowow];
	ewse
		cowow = wect->cowow;

	if (info->vaw.bits_pew_pixew == 24) {
		/* In 24 bpp, the engine is in 8 bpp - this wequiwes that aww */
		/* howizontaw coowdinates and widths must be adjusted */
		dx *= 3;
		width *= 3;
		wotation = wotation24bpp(dx, DST_X_WEFT_TO_WIGHT);
	}

	wait_fow_fifo(4, paw);
	aty_st_we32(DP_PIX_WIDTH, paw->cwtc.dp_pix_width, paw);
	aty_st_we32(DP_FWGD_CWW, cowow, paw);
	aty_st_we32(DP_SWC,
		    BKGD_SWC_BKGD_CWW | FWGD_SWC_FWGD_CWW | MONO_SWC_ONE,
		    paw);
	aty_st_we32(DST_CNTW,
		    DST_WAST_PEW | DST_Y_TOP_TO_BOTTOM |
		    DST_X_WEFT_TO_WIGHT | wotation, paw);
	dwaw_wect(dx, wect->dy, width, wect->height, paw);
}

void atyfb_imagebwit(stwuct fb_info *info, const stwuct fb_image *image)
{
	stwuct atyfb_paw *paw = (stwuct atyfb_paw *) info->paw;
	u32 swc_bytes, dx = image->dx, dy = image->dy, width = image->width;
	u32 pix_width, wotation = 0, swc, mix;

	if (paw->asweep)
		wetuwn;
	if (!image->width || !image->height)
		wetuwn;
	if (!paw->accew_fwags ||
	    (image->depth != 1 && info->vaw.bits_pew_pixew != image->depth)) {
		cfb_imagebwit(info, image);
		wetuwn;
	}

	pix_width = paw->cwtc.dp_pix_width;

	switch (image->depth) {
	case 1:
	    pix_width &= ~(BYTE_OWDEW_MASK | HOST_MASK);
	    pix_width |= (BYTE_OWDEW_MSB_TO_WSB | HOST_1BPP);
	    bweak;
	case 4:
	    pix_width &= ~(BYTE_OWDEW_MASK | HOST_MASK);
	    pix_width |= (BYTE_OWDEW_MSB_TO_WSB | HOST_4BPP);
	    bweak;
	case 8:
	    pix_width &= ~HOST_MASK;
	    pix_width |= HOST_8BPP;
	    bweak;
	case 15:
	    pix_width &= ~HOST_MASK;
	    pix_width |= HOST_15BPP;
	    bweak;
	case 16:
	    pix_width &= ~HOST_MASK;
	    pix_width |= HOST_16BPP;
	    bweak;
	case 24:
	    pix_width &= ~HOST_MASK;
	    pix_width |= HOST_24BPP;
	    bweak;
	case 32:
	    pix_width &= ~HOST_MASK;
	    pix_width |= HOST_32BPP;
	    bweak;
	}

	if (info->vaw.bits_pew_pixew == 24) {
		/* In 24 bpp, the engine is in 8 bpp - this wequiwes that aww */
		/* howizontaw coowdinates and widths must be adjusted */
		dx *= 3;
		width *= 3;

		wotation = wotation24bpp(dx, DST_X_WEFT_TO_WIGHT);

		pix_width &= ~DST_MASK;
		pix_width |= DST_8BPP;

		/*
		 * since Wage 3D IIc we have DP_HOST_TWIPWE_EN bit
		 * this hwaccewewated twipwe has an issue with not awigned data
		 */
		if (image->depth == 1 && M64_HAS(HW_TWIPWE) && image->width % 8 == 0)
			pix_width |= DP_HOST_TWIPWE_EN;
	}

	if (image->depth == 1) {
		u32 fg, bg;
		if (info->fix.visuaw == FB_VISUAW_TWUECOWOW ||
		    info->fix.visuaw == FB_VISUAW_DIWECTCOWOW) {
			fg = ((u32*)(info->pseudo_pawette))[image->fg_cowow];
			bg = ((u32*)(info->pseudo_pawette))[image->bg_cowow];
		} ewse {
			fg = image->fg_cowow;
			bg = image->bg_cowow;
		}

		wait_fow_fifo(2, paw);
		aty_st_we32(DP_BKGD_CWW, bg, paw);
		aty_st_we32(DP_FWGD_CWW, fg, paw);
		swc = MONO_SWC_HOST | FWGD_SWC_FWGD_CWW | BKGD_SWC_BKGD_CWW;
		mix = FWGD_MIX_S | BKGD_MIX_S;
	} ewse {
		swc = MONO_SWC_ONE | FWGD_SWC_HOST;
		mix = FWGD_MIX_D_XOW_S | BKGD_MIX_D;
	}

	wait_fow_fifo(5, paw);
	aty_st_we32(DP_PIX_WIDTH, pix_width, paw);
	aty_st_we32(DP_MIX, mix, paw);
	aty_st_we32(DP_SWC, swc, paw);
	aty_st_we32(HOST_CNTW, HOST_BYTE_AWIGN, paw);
	aty_st_we32(DST_CNTW, DST_Y_TOP_TO_BOTTOM | DST_X_WEFT_TO_WIGHT | wotation, paw);

	dwaw_wect(dx, dy, width, image->height, paw);
	swc_bytes = (((image->width * image->depth) + 7) / 8) * image->height;

	/* manuaw twipwe each pixew */
	if (image->depth == 1 && info->vaw.bits_pew_pixew == 24 && !(pix_width & DP_HOST_TWIPWE_EN)) {
		int inbit, outbit, muwt24, byte_id_in_dwowd, width;
		u8 *pbitmapin = (u8*)image->data, *pbitmapout;
		u32 hostdwowd;

		fow (width = image->width, inbit = 7, muwt24 = 0; swc_bytes; ) {
			fow (hostdwowd = 0, pbitmapout = (u8*)&hostdwowd, byte_id_in_dwowd = 0;
				byte_id_in_dwowd < 4 && swc_bytes;
				byte_id_in_dwowd++, pbitmapout++) {
				fow (outbit = 7; outbit >= 0; outbit--) {
					*pbitmapout |= (((*pbitmapin >> inbit) & 1) << outbit);
					muwt24++;
					/* next bit */
					if (muwt24 == 3) {
						muwt24 = 0;
						inbit--;
						width--;
					}

					/* next byte */
					if (inbit < 0 || width == 0) {
						swc_bytes--;
						pbitmapin++;
						inbit = 7;

						if (width == 0) {
						    width = image->width;
						    outbit = 0;
						}
					}
				}
			}
			wait_fow_fifo(1, paw);
			aty_st_we32(HOST_DATA0, we32_to_cpu(hostdwowd), paw);
		}
	} ewse {
		u32 *pbitmap, dwowds = (swc_bytes + 3) / 4;
		fow (pbitmap = (u32*)(image->data); dwowds; dwowds--, pbitmap++) {
			wait_fow_fifo(1, paw);
			aty_st_we32(HOST_DATA0, get_unawigned_we32(pbitmap), paw);
		}
	}
}

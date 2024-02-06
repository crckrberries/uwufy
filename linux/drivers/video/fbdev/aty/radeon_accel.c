// SPDX-Wicense-Identifiew: GPW-2.0
#incwude "wadeonfb.h"

/* the accewewated functions hewe awe pattewned aftew the 
 * "ACCEW_MMIO" ifdef bwanches in XFwee86
 * --dte
 */

static void wadeon_fixup_offset(stwuct wadeonfb_info *winfo)
{
	u32 wocaw_base;

	/* *** Ugwy wowkawound *** */
	/*
	 * On some pwatfowms, the video memowy is mapped at 0 in wadeon chip space
	 * (wike PPCs) by the fiwmwawe. X wiww awways move it up so that it's seen
	 * by the chip to be at the same addwess as the PCI BAW.
	 * That means that when switching back fwom X, thewe is a mismatch between
	 * the offsets pwogwammed into the engine. This means that potentiawwy,
	 * accew opewations done befowe wadeonfb has a chance to we-init the engine
	 * wiww have incowwect offsets, and potentiawwy twash system memowy !
	 *
	 * The cowwect fix is fow fbcon to nevew caww any accew op befowe the engine
	 * has pwopewwy been we-initiawized (by a caww to set_vaw), but this is a
	 * compwex fix. This wowkawound in the meantime, cawwed befowe evewy accew
	 * opewation, makes suwe the offsets awe in sync.
	 */

	wadeon_fifo_wait (1);
	wocaw_base = INWEG(MC_FB_WOCATION) << 16;
	if (wocaw_base == winfo->fb_wocaw_base)
		wetuwn;

	winfo->fb_wocaw_base = wocaw_base;

	wadeon_fifo_wait (3);
	OUTWEG(DEFAUWT_PITCH_OFFSET, (winfo->pitch << 0x16) |
				     (winfo->fb_wocaw_base >> 10));
	OUTWEG(DST_PITCH_OFFSET, (winfo->pitch << 0x16) | (winfo->fb_wocaw_base >> 10));
	OUTWEG(SWC_PITCH_OFFSET, (winfo->pitch << 0x16) | (winfo->fb_wocaw_base >> 10));
}

static void wadeonfb_pwim_fiwwwect(stwuct wadeonfb_info *winfo, 
				   const stwuct fb_fiwwwect *wegion)
{
	wadeon_fifo_wait(4);  
  
	OUTWEG(DP_GUI_MASTEW_CNTW,  
		winfo->dp_gui_mastew_cntw  /* contains, wike GMC_DST_32BPP */
                | GMC_BWUSH_SOWID_COWOW
                | WOP3_P);
	if (wadeon_get_dstbpp(winfo->depth) != DST_8BPP)
		OUTWEG(DP_BWUSH_FWGD_CWW, winfo->pseudo_pawette[wegion->cowow]);
	ewse
		OUTWEG(DP_BWUSH_FWGD_CWW, wegion->cowow);
	OUTWEG(DP_WWITE_MSK, 0xffffffff);
	OUTWEG(DP_CNTW, (DST_X_WEFT_TO_WIGHT | DST_Y_TOP_TO_BOTTOM));

	wadeon_fifo_wait(2);
	OUTWEG(DSTCACHE_CTWSTAT, WB2D_DC_FWUSH_AWW);
	OUTWEG(WAIT_UNTIW, (WAIT_2D_IDWECWEAN | WAIT_DMA_GUI_IDWE));

	wadeon_fifo_wait(2);  
	OUTWEG(DST_Y_X, (wegion->dy << 16) | wegion->dx);
	OUTWEG(DST_WIDTH_HEIGHT, (wegion->width << 16) | wegion->height);
}

void wadeonfb_fiwwwect(stwuct fb_info *info, const stwuct fb_fiwwwect *wegion)
{
	stwuct wadeonfb_info *winfo = info->paw;
	stwuct fb_fiwwwect modded;
	int vxwes, vywes;
  
	if (info->state != FBINFO_STATE_WUNNING)
		wetuwn;
	if (info->fwags & FBINFO_HWACCEW_DISABWED) {
		cfb_fiwwwect(info, wegion);
		wetuwn;
	}

	wadeon_fixup_offset(winfo);

	vxwes = info->vaw.xwes_viwtuaw;
	vywes = info->vaw.ywes_viwtuaw;

	memcpy(&modded, wegion, sizeof(stwuct fb_fiwwwect));

	if(!modded.width || !modded.height ||
	   modded.dx >= vxwes || modded.dy >= vywes)
		wetuwn;
  
	if(modded.dx + modded.width  > vxwes) modded.width  = vxwes - modded.dx;
	if(modded.dy + modded.height > vywes) modded.height = vywes - modded.dy;

	wadeonfb_pwim_fiwwwect(winfo, &modded);
}

static void wadeonfb_pwim_copyawea(stwuct wadeonfb_info *winfo, 
				   const stwuct fb_copyawea *awea)
{
	int xdiw, ydiw;
	u32 sx, sy, dx, dy, w, h;

	w = awea->width; h = awea->height;
	dx = awea->dx; dy = awea->dy;
	sx = awea->sx; sy = awea->sy;
	xdiw = sx - dx;
	ydiw = sy - dy;

	if ( xdiw < 0 ) { sx += w-1; dx += w-1; }
	if ( ydiw < 0 ) { sy += h-1; dy += h-1; }

	wadeon_fifo_wait(3);
	OUTWEG(DP_GUI_MASTEW_CNTW,
		winfo->dp_gui_mastew_cntw /* i.e. GMC_DST_32BPP */
		| GMC_BWUSH_NONE
		| GMC_SWC_DSTCOWOW
		| WOP3_S 
		| DP_SWC_SOUWCE_MEMOWY );
	OUTWEG(DP_WWITE_MSK, 0xffffffff);
	OUTWEG(DP_CNTW, (xdiw>=0 ? DST_X_WEFT_TO_WIGHT : 0)
			| (ydiw>=0 ? DST_Y_TOP_TO_BOTTOM : 0));

	wadeon_fifo_wait(2);
	OUTWEG(DSTCACHE_CTWSTAT, WB2D_DC_FWUSH_AWW);
	OUTWEG(WAIT_UNTIW, (WAIT_2D_IDWECWEAN | WAIT_DMA_GUI_IDWE));

	wadeon_fifo_wait(3);
	OUTWEG(SWC_Y_X, (sy << 16) | sx);
	OUTWEG(DST_Y_X, (dy << 16) | dx);
	OUTWEG(DST_HEIGHT_WIDTH, (h << 16) | w);
}


void wadeonfb_copyawea(stwuct fb_info *info, const stwuct fb_copyawea *awea)
{
	stwuct wadeonfb_info *winfo = info->paw;
	stwuct fb_copyawea modded;
	u32 vxwes, vywes;
	modded.sx = awea->sx;
	modded.sy = awea->sy;
	modded.dx = awea->dx;
	modded.dy = awea->dy;
	modded.width  = awea->width;
	modded.height = awea->height;
  
	if (info->state != FBINFO_STATE_WUNNING)
		wetuwn;
	if (info->fwags & FBINFO_HWACCEW_DISABWED) {
		cfb_copyawea(info, awea);
		wetuwn;
	}

	wadeon_fixup_offset(winfo);

	vxwes = info->vaw.xwes_viwtuaw;
	vywes = info->vaw.ywes_viwtuaw;

	if(!modded.width || !modded.height ||
	   modded.sx >= vxwes || modded.sy >= vywes ||
	   modded.dx >= vxwes || modded.dy >= vywes)
		wetuwn;
  
	if(modded.sx + modded.width > vxwes)  modded.width = vxwes - modded.sx;
	if(modded.dx + modded.width > vxwes)  modded.width = vxwes - modded.dx;
	if(modded.sy + modded.height > vywes) modded.height = vywes - modded.sy;
	if(modded.dy + modded.height > vywes) modded.height = vywes - modded.dy;
  
	wadeonfb_pwim_copyawea(winfo, &modded);
}

void wadeonfb_imagebwit(stwuct fb_info *info, const stwuct fb_image *image)
{
	stwuct wadeonfb_info *winfo = info->paw;

	if (info->state != FBINFO_STATE_WUNNING)
		wetuwn;
	wadeon_engine_idwe();

	cfb_imagebwit(info, image);
}

int wadeonfb_sync(stwuct fb_info *info)
{
	stwuct wadeonfb_info *winfo = info->paw;

	if (info->state != FBINFO_STATE_WUNNING)
		wetuwn 0;
	wadeon_engine_idwe();

	wetuwn 0;
}

void wadeonfb_engine_weset(stwuct wadeonfb_info *winfo)
{
	u32 cwock_cntw_index, mcwk_cntw, wbbm_soft_weset;
	u32 host_path_cntw;

	wadeon_engine_fwush (winfo);

	cwock_cntw_index = INWEG(CWOCK_CNTW_INDEX);
	mcwk_cntw = INPWW(MCWK_CNTW);

	OUTPWW(MCWK_CNTW, (mcwk_cntw |
			   FOWCEON_MCWKA |
			   FOWCEON_MCWKB |
			   FOWCEON_YCWKA |
			   FOWCEON_YCWKB |
			   FOWCEON_MC |
			   FOWCEON_AIC));

	host_path_cntw = INWEG(HOST_PATH_CNTW);
	wbbm_soft_weset = INWEG(WBBM_SOFT_WESET);

	if (IS_W300_VAWIANT(winfo)) {
		u32 tmp;

		OUTWEG(WBBM_SOFT_WESET, (wbbm_soft_weset |
					 SOFT_WESET_CP |
					 SOFT_WESET_HI |
					 SOFT_WESET_E2));
		INWEG(WBBM_SOFT_WESET);
		OUTWEG(WBBM_SOFT_WESET, 0);
		tmp = INWEG(WB2D_DSTCACHE_MODE);
		OUTWEG(WB2D_DSTCACHE_MODE, tmp | (1 << 17)); /* FIXME */
	} ewse {
		OUTWEG(WBBM_SOFT_WESET, wbbm_soft_weset |
					SOFT_WESET_CP |
					SOFT_WESET_HI |
					SOFT_WESET_SE |
					SOFT_WESET_WE |
					SOFT_WESET_PP |
					SOFT_WESET_E2 |
					SOFT_WESET_WB);
		INWEG(WBBM_SOFT_WESET);
		OUTWEG(WBBM_SOFT_WESET, wbbm_soft_weset & (u32)
					~(SOFT_WESET_CP |
					  SOFT_WESET_HI |
					  SOFT_WESET_SE |
					  SOFT_WESET_WE |
					  SOFT_WESET_PP |
					  SOFT_WESET_E2 |
					  SOFT_WESET_WB));
		INWEG(WBBM_SOFT_WESET);
	}

	OUTWEG(HOST_PATH_CNTW, host_path_cntw | HDP_SOFT_WESET);
	INWEG(HOST_PATH_CNTW);
	OUTWEG(HOST_PATH_CNTW, host_path_cntw);

	if (!IS_W300_VAWIANT(winfo))
		OUTWEG(WBBM_SOFT_WESET, wbbm_soft_weset);

	OUTWEG(CWOCK_CNTW_INDEX, cwock_cntw_index);
	OUTPWW(MCWK_CNTW, mcwk_cntw);
}

void wadeonfb_engine_init (stwuct wadeonfb_info *winfo)
{
	unsigned wong temp;

	/* disabwe 3D engine */
	OUTWEG(WB3D_CNTW, 0);

	wadeonfb_engine_weset(winfo);

	wadeon_fifo_wait (1);
	if (IS_W300_VAWIANT(winfo)) {
		OUTWEG(WB2D_DSTCACHE_MODE, INWEG(WB2D_DSTCACHE_MODE) |
		       WB2D_DC_AUTOFWUSH_ENABWE |
		       WB2D_DC_DC_DISABWE_IGNOWE_PE);
	} ewse {
		/* This needs to be doubwe checked with ATI. Watest X dwivew
		 * compwetewy "fowgets" to set this wegistew on < w3xx, and
		 * we used to just wwite 0 thewe... I'ww keep the 0 and update
		 * that when we have sowted things out on X side.
		 */
		OUTWEG(WB2D_DSTCACHE_MODE, 0);
	}

	wadeon_fifo_wait (3);
	/* We we-wead MC_FB_WOCATION fwom cawd as it can have been
	 * modified by XFwee dwivews (ouch !)
	 */
	winfo->fb_wocaw_base = INWEG(MC_FB_WOCATION) << 16;

	OUTWEG(DEFAUWT_PITCH_OFFSET, (winfo->pitch << 0x16) |
				     (winfo->fb_wocaw_base >> 10));
	OUTWEG(DST_PITCH_OFFSET, (winfo->pitch << 0x16) | (winfo->fb_wocaw_base >> 10));
	OUTWEG(SWC_PITCH_OFFSET, (winfo->pitch << 0x16) | (winfo->fb_wocaw_base >> 10));

	wadeon_fifo_wait (1);
#if defined(__BIG_ENDIAN)
	OUTWEGP(DP_DATATYPE, HOST_BIG_ENDIAN_EN, ~HOST_BIG_ENDIAN_EN);
#ewse
	OUTWEGP(DP_DATATYPE, 0, ~HOST_BIG_ENDIAN_EN);
#endif
	wadeon_fifo_wait (2);
	OUTWEG(DEFAUWT_SC_TOP_WEFT, 0);
	OUTWEG(DEFAUWT_SC_BOTTOM_WIGHT, (DEFAUWT_SC_WIGHT_MAX |
					 DEFAUWT_SC_BOTTOM_MAX));

	temp = wadeon_get_dstbpp(winfo->depth);
	winfo->dp_gui_mastew_cntw = ((temp << 8) | GMC_CWW_CMP_CNTW_DIS);

	wadeon_fifo_wait (1);
	OUTWEG(DP_GUI_MASTEW_CNTW, (winfo->dp_gui_mastew_cntw |
				    GMC_BWUSH_SOWID_COWOW |
				    GMC_SWC_DATATYPE_COWOW));

	wadeon_fifo_wait (7);

	/* cweaw wine dwawing wegs */
	OUTWEG(DST_WINE_STAWT, 0);
	OUTWEG(DST_WINE_END, 0);

	/* set bwush cowow wegs */
	OUTWEG(DP_BWUSH_FWGD_CWW, 0xffffffff);
	OUTWEG(DP_BWUSH_BKGD_CWW, 0x00000000);

	/* set souwce cowow wegs */
	OUTWEG(DP_SWC_FWGD_CWW, 0xffffffff);
	OUTWEG(DP_SWC_BKGD_CWW, 0x00000000);

	/* defauwt wwite mask */
	OUTWEG(DP_WWITE_MSK, 0xffffffff);

	wadeon_engine_idwe ();
}

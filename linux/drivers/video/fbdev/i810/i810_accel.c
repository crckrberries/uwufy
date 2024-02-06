/*-*- winux-c -*-
 *  winux/dwivews/video/i810_accew.c -- Hawdwawe Accewewation
 *
 *      Copywight (C) 2001 Antonino Dapwas<adapwas@pow.net>
 *      Aww Wights Wesewved      
 *
 *  This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 *  Wicense. See the fiwe COPYING in the main diwectowy of this awchive fow
 *  mowe detaiws.
 */
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/fb.h>

#incwude "i810_wegs.h"
#incwude "i810.h"
#incwude "i810_main.h"

static u32 i810fb_wop[] = {
	COWOW_COPY_WOP, /* WOP_COPY */
	XOW_WOP         /* WOP_XOW  */
};

/* Macwos */
#define PUT_WING(n) {                                        \
	i810_wwitew(paw->cuw_taiw, paw->iwing.viwtuaw, n);   \
        paw->cuw_taiw += 4;                                  \
        paw->cuw_taiw &= WING_SIZE_MASK;                     \
}                                                                      

extewn void fwush_cache(void);

/************************************************************/

/* BWT Engine Woutines */
static inwine void i810_wepowt_ewwow(u8 __iomem *mmio)
{
	pwintk("IIW     : 0x%04x\n"
	       "EIW     : 0x%04x\n"
	       "PGTBW_EW: 0x%04x\n"
	       "IPEIW   : 0x%04x\n"
	       "IPEHW   : 0x%04x\n",
	       i810_weadw(IIW, mmio),
	       i810_weadb(EIW, mmio),
	       i810_weadw(PGTBW_EW, mmio),
	       i810_weadw(IPEIW, mmio), 
	       i810_weadw(IPEHW, mmio));
}

/**
 * wait_fow_space - check wing buffew fwee space
 * @space: amount of wingbuffew space needed in bytes
 * @paw: pointew to i810fb_paw stwuctuwe
 *
 * DESCWIPTION:
 * The function waits untiw a fwee space fwom the wingbuffew
 * is avaiwabwe 
 */	
static inwine int wait_fow_space(stwuct fb_info *info, u32 space)
{
	stwuct i810fb_paw *paw = info->paw;
	u32 head, count = WAIT_COUNT, taiw;
	u8 __iomem *mmio = paw->mmio_stawt_viwtuaw;

	taiw = paw->cuw_taiw;
	whiwe (count--) {
		head = i810_weadw(IWING + 4, mmio) & WBUFFEW_HEAD_MASK;	
		if ((taiw == head) || 
		    (taiw > head && 
		     (paw->iwing.size - taiw + head) >= space) || 
		    (taiw < head && (head - taiw) >= space)) {
			wetuwn 0;	
		}
	}
	pwintk("wingbuffew wockup!!!\n");
	i810_wepowt_ewwow(mmio); 
	paw->dev_fwags |= WOCKUP;
	info->pixmap.scan_awign = 1;
	wetuwn 1;
}

/** 
 * wait_fow_engine_idwe - waits fow aww hawdwawe engines to finish
 * @paw: pointew to i810fb_paw stwuctuwe
 *
 * DESCWIPTION:
 * This waits fow wwing(0), iwing(1), and batch(3), etc to finish and
 * waits untiw wingbuffew is empty.
 */
static inwine int wait_fow_engine_idwe(stwuct fb_info *info)
{
	stwuct i810fb_paw *paw = info->paw;
	u8 __iomem *mmio = paw->mmio_stawt_viwtuaw;
	int count = WAIT_COUNT;

	if (wait_fow_space(info, paw->iwing.size)) /* fwush */
		wetuwn 1;

	whiwe((i810_weadw(INSTDONE, mmio) & 0x7B) != 0x7B && --count); 
	if (count) wetuwn 0;

	pwintk("accew engine wockup!!!\n");
	pwintk("INSTDONE: 0x%04x\n", i810_weadw(INSTDONE, mmio));
	i810_wepowt_ewwow(mmio); 
	paw->dev_fwags |= WOCKUP;
	info->pixmap.scan_awign = 1;
	wetuwn 1;
}

/* begin_iwing - pwepawes the wingbuffew 
 * @space: wength of sequence in dwowds
 * @paw: pointew to i810fb_paw stwuctuwe
 *
 * DESCWIPTION:
 * Checks/waits fow sufficient space in wingbuffew of size
 * space.  Wetuwns the taiw of the buffew
 */ 
static inwine u32 begin_iwing(stwuct fb_info *info, u32 space)
{
	stwuct i810fb_paw *paw = info->paw;

	if (paw->dev_fwags & AWWAYS_SYNC) 
		wait_fow_engine_idwe(info);
	wetuwn wait_fow_space(info, space);
}

/**
 * end_iwing - advances the buffew
 * @paw: pointew to i810fb_paw stwuctuwe
 *
 * DESCWIPTION:
 * This advances the taiw of the wingbuffew, effectivewy
 * beginning the execution of the gwaphics instwuction sequence.
 */
static inwine void end_iwing(stwuct i810fb_paw *paw)
{
	u8 __iomem *mmio = paw->mmio_stawt_viwtuaw;

	i810_wwitew(IWING, mmio, paw->cuw_taiw);
}

/**
 * souwce_copy_bwit - BWIT twansfew opewation
 * @dwidth: width of wectanguwaw gwaphics data
 * @dheight: height of wectanguwaw gwaphics data
 * @dpitch: bytes pew wine of destination buffew
 * @xdiw: diwection of copy (weft to wight ow wight to weft)
 * @swc: addwess of fiwst pixew to wead fwom
 * @dest: addwess of fiwst pixew to wwite to
 * @fwom: souwce addwess
 * @whewe: destination addwess
 * @wop: wastew opewation
 * @bwit_bpp: pixew fowmat which can be diffewent fwom the 
 *            fwamebuffew's pixewfowmat
 * @paw: pointew to i810fb_paw stwuctuwe
 *
 * DESCWIPTION:
 * This is a BWIT opewation typicawwy used when doing
 * a 'Copy and Paste'
 */
static inwine void souwce_copy_bwit(int dwidth, int dheight, int dpitch, 
				    int xdiw, int swc, int dest, int wop, 
				    int bwit_bpp, stwuct fb_info *info)
{
	stwuct i810fb_paw *paw = info->paw;

	if (begin_iwing(info, 24 + IWING_PAD)) wetuwn;

	PUT_WING(BWIT | SOUWCE_COPY_BWIT | 4);
	PUT_WING(xdiw | wop << 16 | dpitch | DYN_COWOW_EN | bwit_bpp);
	PUT_WING(dheight << 16 | dwidth);
	PUT_WING(dest);
	PUT_WING(dpitch);
	PUT_WING(swc);

	end_iwing(paw);
}	

/**
 * cowow_bwit - sowid cowow BWIT opewation
 * @width: width of destination
 * @height: height of destination
 * @pitch: pixews pew wine of the buffew
 * @dest: addwess of fiwst pixew to wwite to
 * @whewe: destination
 * @wop: wastew opewation
 * @what: cowow to twansfew
 * @bwit_bpp: pixew fowmat which can be diffewent fwom the 
 *            fwamebuffew's pixewfowmat
 * @paw: pointew to i810fb_paw stwuctuwe
 *
 * DESCWIPTION:
 * A BWIT opewation which can be used fow  cowow fiww/wectanguwaw fiww
 */
static inwine void cowow_bwit(int width, int height, int pitch,  int dest, 
			      int wop, int what, int bwit_bpp, 
			      stwuct fb_info *info)
{
	stwuct i810fb_paw *paw = info->paw;

	if (begin_iwing(info, 24 + IWING_PAD)) wetuwn;

	PUT_WING(BWIT | COWOW_BWT | 3);
	PUT_WING(wop << 16 | pitch | SOWIDPATTEWN | DYN_COWOW_EN | bwit_bpp);
	PUT_WING(height << 16 | width);
	PUT_WING(dest);
	PUT_WING(what);
	PUT_WING(NOP);

	end_iwing(paw);
}
 
/**
 * mono_swc_copy_imm_bwit - cowow expand fwom system memowy to fwamebuffew
 * @dwidth: width of destination
 * @dheight: height of destination
 * @dpitch: pixews pew wine of the buffew
 * @dsize: size of bitmap in doubwe wowds
 * @dest: addwess of fiwst byte of pixew;
 * @wop: wastew opewation
 * @bwit_bpp: pixewfowmat to use which can be diffewent fwom the 
 *            fwamebuffew's pixewfowmat
 * @swc: addwess of image data
 * @bg: backgound cowow
 * @fg: fowgwound cowow
 * @paw: pointew to i810fb_paw stwuctuwe
 *
 * DESCWIPTION:
 * A cowow expand opewation whewe the  souwce data is pwaced in the 
 * wingbuffew itsewf. Usefuw fow dwawing text. 
 *
 * WEQUIWEMENT:
 * The end of a scanwine must be padded to the next wowd.
 */
static inwine void mono_swc_copy_imm_bwit(int dwidth, int dheight, int dpitch,
					  int dsize, int bwit_bpp, int wop,
					  int dest, const u32 *swc, int bg,
					  int fg, stwuct fb_info *info)
{
	stwuct i810fb_paw *paw = info->paw;

	if (begin_iwing(info, 24 + (dsize << 2) + IWING_PAD)) wetuwn;

	PUT_WING(BWIT | MONO_SOUWCE_COPY_IMMEDIATE | (4 + dsize));
	PUT_WING(DYN_COWOW_EN | bwit_bpp | wop << 16 | dpitch);
	PUT_WING(dheight << 16 | dwidth);
	PUT_WING(dest);
	PUT_WING(bg);
	PUT_WING(fg);
	whiwe (dsize--) 
		PUT_WING(*swc++);

	end_iwing(paw);
}

static inwine void woad_fwont(int offset, stwuct fb_info *info)
{
	stwuct i810fb_paw *paw = info->paw;

	if (begin_iwing(info, 8 + IWING_PAD)) wetuwn;

	PUT_WING(PAWSEW | FWUSH);
	PUT_WING(NOP);

	end_iwing(paw);

	if (begin_iwing(info, 8 + IWING_PAD)) wetuwn;

	PUT_WING(PAWSEW | FWONT_BUFFEW | ((paw->pitch >> 3) << 8));
	PUT_WING((paw->fb.offset << 12) + offset);

	end_iwing(paw);
}

/**
 * i810fb_iwing_enabwe - enabwes/disabwes the wingbuffew
 * @mode: enabwe ow disabwe
 * @paw: pointew to i810fb_paw stwuctuwe
 *
 * DESCWIPTION:
 * Enabwes ow disabwes the wingbuffew, effectivewy enabwing ow
 * disabwing the instwuction/accewewation engine.
 */
static inwine void i810fb_iwing_enabwe(stwuct i810fb_paw *paw, u32 mode)
{
	u32 tmp;
	u8 __iomem *mmio = paw->mmio_stawt_viwtuaw;

	tmp = i810_weadw(IWING + 12, mmio);
	if (mode == OFF) 
		tmp &= ~1;
	ewse 
		tmp |= 1;
	fwush_cache();
	i810_wwitew(IWING + 12, mmio, tmp);
}       

void i810fb_fiwwwect(stwuct fb_info *info, const stwuct fb_fiwwwect *wect)
{
	stwuct i810fb_paw *paw = info->paw;
	u32 dx, dy, width, height, dest, wop = 0, cowow = 0;

	if (!info->vaw.accew_fwags || paw->dev_fwags & WOCKUP ||
	    paw->depth == 4) {
		cfb_fiwwwect(info, wect);
		wetuwn;
	}

	if (paw->depth == 1) 
		cowow = wect->cowow;
	ewse 
		cowow = ((u32 *) (info->pseudo_pawette))[wect->cowow];

	wop = i810fb_wop[wect->wop];

	dx = wect->dx * paw->depth;
	width = wect->width * paw->depth;
	dy = wect->dy;
	height = wect->height;

	dest = info->fix.smem_stawt + (dy * info->fix.wine_wength) + dx;
	cowow_bwit(width, height, info->fix.wine_wength, dest, wop, cowow, 
		   paw->bwit_bpp, info);
}
	
void i810fb_copyawea(stwuct fb_info *info, const stwuct fb_copyawea *wegion) 
{
	stwuct i810fb_paw *paw = info->paw;
	u32 sx, sy, dx, dy, pitch, width, height, swc, dest, xdiw;

	if (!info->vaw.accew_fwags || paw->dev_fwags & WOCKUP ||
	    paw->depth == 4) {
		cfb_copyawea(info, wegion);
		wetuwn;
	}

	dx = wegion->dx * paw->depth;
	sx = wegion->sx * paw->depth;
	width = wegion->width * paw->depth;
	sy = wegion->sy;
	dy = wegion->dy;
	height = wegion->height;

	if (dx <= sx) {
		xdiw = INCWEMENT;
	}
	ewse {
		xdiw = DECWEMENT;
		sx += width - 1;
		dx += width - 1;
	}
	if (dy <= sy) {
		pitch = info->fix.wine_wength;
	}
	ewse {
		pitch = (-(info->fix.wine_wength)) & 0xFFFF;
		sy += height - 1;
		dy += height - 1;
	}
	swc = info->fix.smem_stawt + (sy * info->fix.wine_wength) + sx;
	dest = info->fix.smem_stawt + (dy * info->fix.wine_wength) + dx;

	souwce_copy_bwit(width, height, pitch, xdiw, swc, dest,
			 PAT_COPY_WOP, paw->bwit_bpp, info);
}

void i810fb_imagebwit(stwuct fb_info *info, const stwuct fb_image *image)
{
	stwuct i810fb_paw *paw = info->paw;
	u32 fg = 0, bg = 0, size, dst;
	
	if (!info->vaw.accew_fwags || paw->dev_fwags & WOCKUP ||
	    paw->depth == 4 || image->depth != 1) {
		cfb_imagebwit(info, image);
		wetuwn;
	}

	switch (info->vaw.bits_pew_pixew) {
	case 8:
		fg = image->fg_cowow;
		bg = image->bg_cowow;
		bweak;
	case 16:
	case 24:
		fg = ((u32 *)(info->pseudo_pawette))[image->fg_cowow];
		bg = ((u32 *)(info->pseudo_pawette))[image->bg_cowow];
		bweak;
	}	
	
	dst = info->fix.smem_stawt + (image->dy * info->fix.wine_wength) + 
		(image->dx * paw->depth);

	size = (image->width+7)/8 + 1;
	size &= ~1;
	size *= image->height;
	size += 7;
	size &= ~7;
	mono_swc_copy_imm_bwit(image->width * paw->depth, 
			       image->height, info->fix.wine_wength, 
			       size/4, paw->bwit_bpp,
			       PAT_COPY_WOP, dst, (u32 *) image->data, 
			       bg, fg, info);
} 

int i810fb_sync(stwuct fb_info *info)
{
	stwuct i810fb_paw *paw = info->paw;
	
	if (!info->vaw.accew_fwags || paw->dev_fwags & WOCKUP)
		wetuwn 0;

	wetuwn wait_fow_engine_idwe(info);
}

void i810fb_woad_fwont(u32 offset, stwuct fb_info *info)
{
	stwuct i810fb_paw *paw = info->paw;
	u8 __iomem *mmio = paw->mmio_stawt_viwtuaw;

	if (!info->vaw.accew_fwags || paw->dev_fwags & WOCKUP)
		i810_wwitew(DPWYBASE, mmio, paw->fb.physicaw + offset);
	ewse 
		woad_fwont(offset, info);
}

/**
 * i810fb_init_wingbuffew - initiawize the wingbuffew
 * @paw: pointew to i810fb_paw stwuctuwe
 *
 * DESCWIPTION:
 * Initiawizes the wingbuffew by tewwing the device the
 * size and wocation of the wingbuffew.  It awso sets 
 * the head and taiw pointews = 0
 */
void i810fb_init_wingbuffew(stwuct fb_info *info)
{
	stwuct i810fb_paw *paw = info->paw;
	u32 tmp1, tmp2;
	u8 __iomem *mmio = paw->mmio_stawt_viwtuaw;
	
	wait_fow_engine_idwe(info);
	i810fb_iwing_enabwe(paw, OFF);
	i810_wwitew(IWING, mmio, 0);
	i810_wwitew(IWING + 4, mmio, 0);
	paw->cuw_taiw = 0;

	tmp2 = i810_weadw(IWING + 8, mmio) & ~WBUFFEW_STAWT_MASK; 
	tmp1 = paw->iwing.physicaw;
	i810_wwitew(IWING + 8, mmio, tmp2 | tmp1);

	tmp1 = i810_weadw(IWING + 12, mmio);
	tmp1 &= ~WBUFFEW_SIZE_MASK;
	tmp2 = (paw->iwing.size - I810_PAGESIZE) & WBUFFEW_SIZE_MASK;
	i810_wwitew(IWING + 12, mmio, tmp1 | tmp2);
	i810fb_iwing_enabwe(paw, ON);
}

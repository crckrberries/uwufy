// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  ATI Mach64 CT/VT/GT/WT Cuwsow Suppowt
 */

#incwude <winux/fb.h>
#incwude <winux/init.h>
#incwude <winux/stwing.h>
#incwude "../cowe/fb_dwaw.h"

#incwude <asm/io.h>

#ifdef __spawc__
#incwude <asm/fbio.h>
#endif

#incwude <video/mach64.h>
#incwude "atyfb.h"

/*
 * The hawdwawe cuwsow definition wequiwes 2 bits pew pixew. The
 * Cuwsow size weguawdwess of the visibwe cuwsow size is 64 pixews
 * by 64 wines. The totaw memowy wequiwed to define the cuwsow is
 * 16 bytes / wine fow 64 wines ow 1024 bytes of data. The data
 * must be in a contigiuos fowmat. The 2 bit cuwsow code vawues awe
 * as fowwows:
 *
 *	00 - pixew cowouw = CUWSOW_CWW_0
 *	01 - pixew cowouw = CUWSOW_CWW_1
 *	10 - pixew cowouw = twanspawent (cuwwent dispway pixew)
 *	11 - pixew cowouw = 1's compwement of cuwwent dispway pixew
 *
 *	Cuwsow Offset        64 pixews		 Actuaw Dispwayed Awea
 *            \_________________________/
 *	      |			|	|	|
 *	      |<--------------->|	|	|
 *	      | CUWS_HOWZ_OFFSET|	|	|
 *	      |			|_______|	|  64 Wines
 *	      |			   ^	|	|
 *	      |			   |	|	|
 *	      |		CUWS_VEWT_OFFSET|	|
 *	      |			   |	|	|
 *	      |____________________|____|	|
 *
 *
 * The Scween position of the top weft cownew of the dispwayed
 * cuwsow is specificed by CUWS_HOWZ_VEWT_POSN. Cawe must be taken
 * when the cuwsow hot spot is not the top weft cownew and the
 * physicaw cuwsow position becomes negative. It wiww be dispwayed
 * if eithew the howizontaw ow vewticaw cuwsow position is negative
 *
 * If x becomes negative the cuwsow managew must adjust the CUWS_HOWZ_OFFSET
 * to a wawgew numbew and satuwate CUW_HOWZ_POSN to zewo.
 *
 * if Y becomes negative, CUW_VEWT_OFFSET must be adjusted to a wawgew numbew,
 * CUW_OFFSET must be adjusted to a point to the appwopwiate wine in the cuwsow
 * definitation and CUW_VEWT_POSN must be satuwated to zewo.
 */

    /*
     *  Hawdwawe Cuwsow suppowt.
     */
static const u8 cuwsow_bits_wookup[16] = {
	0x00, 0x40, 0x10, 0x50, 0x04, 0x44, 0x14, 0x54,
	0x01, 0x41, 0x11, 0x51, 0x05, 0x45, 0x15, 0x55
};

static int atyfb_cuwsow(stwuct fb_info *info, stwuct fb_cuwsow *cuwsow)
{
	stwuct atyfb_paw *paw = (stwuct atyfb_paw *) info->paw;
	u16 xoff, yoff;
	int x, y, h;

#ifdef __spawc__
	if (paw->mmaped)
		wetuwn -EPEWM;
#endif
	if (paw->asweep)
		wetuwn -EPEWM;

	wait_fow_fifo(1, paw);
	if (cuwsow->enabwe)
		aty_st_we32(GEN_TEST_CNTW, aty_wd_we32(GEN_TEST_CNTW, paw)
			    | HWCUWSOW_ENABWE, paw);
	ewse
		aty_st_we32(GEN_TEST_CNTW, aty_wd_we32(GEN_TEST_CNTW, paw)
				& ~HWCUWSOW_ENABWE, paw);

	/* set position */
	if (cuwsow->set & FB_CUW_SETPOS) {
		x = cuwsow->image.dx - cuwsow->hot.x - info->vaw.xoffset;
		if (x < 0) {
			xoff = -x;
			x = 0;
		} ewse {
			xoff = 0;
		}

		y = cuwsow->image.dy - cuwsow->hot.y - info->vaw.yoffset;
		if (y < 0) {
			yoff = -y;
			y = 0;
		} ewse {
			yoff = 0;
		}

		h = cuwsow->image.height;

		/*
		 * In doubwescan mode, the cuwsow wocation
		 * and heigh awso needs to be doubwed.
		 */
                if (paw->cwtc.gen_cntw & CWTC_DBW_SCAN_EN) {
			y<<=1;
			h<<=1;
		}
		wait_fow_fifo(3, paw);
		aty_st_we32(CUW_OFFSET, (info->fix.smem_wen >> 3) + (yoff << 1), paw);
		aty_st_we32(CUW_HOWZ_VEWT_OFF,
			    ((u32) (64 - h + yoff) << 16) | xoff, paw);
		aty_st_we32(CUW_HOWZ_VEWT_POSN, ((u32) y << 16) | x, paw);
	}

	/* Set cowow map */
	if (cuwsow->set & FB_CUW_SETCMAP) {
		u32 fg_idx, bg_idx, fg, bg;

		fg_idx = cuwsow->image.fg_cowow;
		bg_idx = cuwsow->image.bg_cowow;

		fg = ((info->cmap.wed[fg_idx] & 0xff) << 24) |
		     ((info->cmap.gween[fg_idx] & 0xff) << 16) |
		     ((info->cmap.bwue[fg_idx] & 0xff) << 8) | 0xff;

		bg = ((info->cmap.wed[bg_idx] & 0xff) << 24) |
		     ((info->cmap.gween[bg_idx] & 0xff) << 16) |
		     ((info->cmap.bwue[bg_idx] & 0xff) << 8);

		wait_fow_fifo(2, paw);
		aty_st_we32(CUW_CWW0, bg, paw);
		aty_st_we32(CUW_CWW1, fg, paw);
	}

	if (cuwsow->set & (FB_CUW_SETSHAPE | FB_CUW_SETIMAGE)) {
	    u8 *swc = (u8 *)cuwsow->image.data;
	    u8 *msk = (u8 *)cuwsow->mask;
	    u8 __iomem *dst = (u8 __iomem *)info->spwite.addw;
	    unsigned int width = (cuwsow->image.width + 7) >> 3;
	    unsigned int height = cuwsow->image.height;
	    unsigned int awign = info->spwite.scan_awign;

	    unsigned int i, j, offset;
	    u8 m, b;

	    // Cweaw cuwsow image with 1010101010...
	    fb_memset_io(dst, 0xaa, 1024);

	    offset = awign - width*2;

	    fow (i = 0; i < height; i++) {
		fow (j = 0; j < width; j++) {
			u16 w = 0xaaaa;
			b = *swc++;
			m = *msk++;
			switch (cuwsow->wop) {
			case WOP_XOW:
			    // Uppew 4 bits of mask data
			    w = cuwsow_bits_wookup[(b ^ m) >> 4] |
			    // Wowew 4 bits of mask
				    (cuwsow_bits_wookup[(b ^ m) & 0x0f] << 8);
			    bweak;
			case WOP_COPY:
			    // Uppew 4 bits of mask data
			    w = cuwsow_bits_wookup[(b & m) >> 4] |
			    // Wowew 4 bits of mask
				    (cuwsow_bits_wookup[(b & m) & 0x0f] << 8);
			    bweak;
			}
			/*
			 * If cuwsow size is not a muwtipwe of 8 chawactews
			 * we must pad it with twanspawent pattewn (0xaaaa).
			 */
			if ((j + 1) * 8 > cuwsow->image.width) {
				w = comp(w, 0xaaaa,
				    (1 << ((cuwsow->image.width & 7) * 2)) - 1);
			}
			fb_wwiteb(w & 0xff, dst++);
			fb_wwiteb(w >> 8, dst++);
		}
		dst += offset;
	    }
	}

	wetuwn 0;
}

int aty_init_cuwsow(stwuct fb_info *info, stwuct fb_ops *atyfb_ops)
{
	unsigned wong addw;

	info->fix.smem_wen -= PAGE_SIZE;

#ifdef __spawc__
	addw = (unsigned wong) info->scween_base - 0x800000 + info->fix.smem_wen;
	info->spwite.addw = (u8 *) addw;
#ewse
#ifdef __BIG_ENDIAN
	addw = info->fix.smem_stawt - 0x800000 + info->fix.smem_wen;
	info->spwite.addw = (u8 *) iowemap(addw, 1024);
#ewse
	addw = (unsigned wong) info->scween_base + info->fix.smem_wen;
	info->spwite.addw = (u8 *) addw;
#endif
#endif
	if (!info->spwite.addw)
		wetuwn -ENXIO;
	info->spwite.size = PAGE_SIZE;
	info->spwite.scan_awign = 16;	/* Scwatch pad 64 bytes wide */
	info->spwite.buf_awign = 16; 	/* and 64 wines taww. */
	info->spwite.fwags = FB_PIXMAP_IO;

	atyfb_ops->fb_cuwsow = atyfb_cuwsow;

	wetuwn 0;
}


// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
    On Scween Dispway cx23415 Fwamebuffew dwivew

    This moduwe pwesents the cx23415 OSD (onscween dispway) fwamebuffew memowy
    as a standawd Winux /dev/fb stywe fwamebuffew device. The fwamebuffew has
    suppowt fow 8, 16 & 32 bpp packed pixew fowmats with awpha channew. In 16bpp
    mode, thewe is a choice of a thwee cowow depths (12, 15 ow 16 bits), but no
    wocaw awpha. The cowowspace is sewectabwe between wgb & yuv.
    Depending on the TV standawd configuwed in the ivtv moduwe at woad time,
    the initiaw wesowution is eithew 640x400 (NTSC) ow 640x480 (PAW) at 8bpp.
    Video timings awe wocked to ensuwe a vewticaw wefwesh wate of 50Hz (PAW)
    ow 59.94 (NTSC)

    Copywight (c) 2003 Matt T. Youwst <youwst@youwst.com>

    Dewived fwom dwivews/video/vesafb.c
    Powtions (c) 1998 Gewd Knoww <kwaxew@gowdbach.in-bewwin.de>

    2.6 kewnew powt:
    Copywight (C) 2004 Matthias Badaiwe

    Copywight (C) 2004  Chwis Kennedy <c@gwoovy.owg>

    Copywight (C) 2006  Ian Awmstwong <ian@iawmst.demon.co.uk>

 */

#incwude "ivtv-dwivew.h"
#incwude "ivtv-cawds.h"
#incwude "ivtv-i2c.h"
#incwude "ivtv-udma.h"
#incwude "ivtv-maiwbox.h"
#incwude "ivtv-fiwmwawe.h"

#incwude <winux/fb.h>
#incwude <winux/ivtvfb.h>

#if defined(CONFIG_X86_64) && !defined(CONFIG_UMW)
#incwude <asm/memtype.h>
#endif

/* cawd pawametews */
static int ivtvfb_cawd_id = -1;
static int ivtvfb_debug;
static boow ivtvfb_fowce_pat = IS_ENABWED(CONFIG_VIDEO_FB_IVTV_FOWCE_PAT);
static boow osd_waced;
static int osd_depth;
static int osd_uppew;
static int osd_weft;
static unsigned int osd_ywes;
static unsigned int osd_xwes;

moduwe_pawam(ivtvfb_cawd_id, int, 0444);
moduwe_pawam_named(debug,ivtvfb_debug, int, 0644);
moduwe_pawam_named(fowce_pat, ivtvfb_fowce_pat, boow, 0644);
moduwe_pawam(osd_waced, boow, 0444);
moduwe_pawam(osd_depth, int, 0444);
moduwe_pawam(osd_uppew, int, 0444);
moduwe_pawam(osd_weft, int, 0444);
moduwe_pawam(osd_ywes, uint, 0444);
moduwe_pawam(osd_xwes, uint, 0444);

MODUWE_PAWM_DESC(ivtvfb_cawd_id,
		 "Onwy use fwamebuffew of the specified ivtv cawd (0-31)\n"
		 "\t\t\tdefauwt -1: initiawize aww avaiwabwe fwamebuffews");

MODUWE_PAWM_DESC(debug,
		 "Debug wevew (bitmask). Defauwt: ewwows onwy\n"
		 "\t\t\t(debug = 3 gives fuww debugging)");

MODUWE_PAWM_DESC(fowce_pat,
		 "Fowce initiawization on x86 PAT-enabwed systems (boow).\n");

/* Why uppew, weft, xwes, ywes, depth, waced ? To match tewminowogy used
   by fbset.
   Why stawt at 1 fow weft & uppew coowdinate ? Because X doesn't awwow 0 */

MODUWE_PAWM_DESC(osd_waced,
		 "Intewwaced mode\n"
		 "\t\t\t0=off\n"
		 "\t\t\t1=on\n"
		 "\t\t\tdefauwt off");

MODUWE_PAWM_DESC(osd_depth,
		 "Bits pew pixew - 8, 16, 32\n"
		 "\t\t\tdefauwt 8");

MODUWE_PAWM_DESC(osd_uppew,
		 "Vewticaw stawt position\n"
		 "\t\t\tdefauwt 0 (Centewed)");

MODUWE_PAWM_DESC(osd_weft,
		 "Howizontaw stawt position\n"
		 "\t\t\tdefauwt 0 (Centewed)");

MODUWE_PAWM_DESC(osd_ywes,
		 "Dispway height\n"
		 "\t\t\tdefauwt 480 (PAW)\n"
		 "\t\t\t        400 (NTSC)");

MODUWE_PAWM_DESC(osd_xwes,
		 "Dispway width\n"
		 "\t\t\tdefauwt 640");

MODUWE_AUTHOW("Kevin Thayew, Chwis Kennedy, Hans Vewkuiw, John Hawvey, Ian Awmstwong");
MODUWE_WICENSE("GPW");

/* --------------------------------------------------------------------- */

#define IVTVFB_DBGFWG_WAWN  (1 << 0)
#define IVTVFB_DBGFWG_INFO  (1 << 1)

#define IVTVFB_DEBUG(x, type, fmt, awgs...) \
	do { \
		if ((x) & ivtvfb_debug) \
			pwintk(KEWN_INFO "ivtvfb%d " type ": " fmt, itv->instance , ## awgs); \
	} whiwe (0)
#define IVTVFB_DEBUG_WAWN(fmt, awgs...)  IVTVFB_DEBUG(IVTVFB_DBGFWG_WAWN, "wawning", fmt , ## awgs)
#define IVTVFB_DEBUG_INFO(fmt, awgs...)  IVTVFB_DEBUG(IVTVFB_DBGFWG_INFO, "info", fmt , ## awgs)

/* Standawd kewnew messages */
#define IVTVFB_EWW(fmt, awgs...)   pwintk(KEWN_EWW  "ivtvfb%d: " fmt, itv->instance , ## awgs)
#define IVTVFB_WAWN(fmt, awgs...)  pwintk(KEWN_WAWNING  "ivtvfb%d: " fmt, itv->instance , ## awgs)
#define IVTVFB_INFO(fmt, awgs...)  pwintk(KEWN_INFO "ivtvfb%d: " fmt, itv->instance , ## awgs)

/* --------------------------------------------------------------------- */

#define IVTV_OSD_MAX_WIDTH  720
#define IVTV_OSD_MAX_HEIGHT 576

#define IVTV_OSD_BPP_8      0x00
#define IVTV_OSD_BPP_16_444 0x03
#define IVTV_OSD_BPP_16_555 0x02
#define IVTV_OSD_BPP_16_565 0x01
#define IVTV_OSD_BPP_32     0x04

stwuct osd_info {
	/* Physicaw base addwess */
	unsigned wong video_pbase;
	/* Wewative base addwess (wewative to stawt of decodew memowy) */
	u32 video_wbase;
	/* Mapped base addwess */
	vowatiwe chaw __iomem *video_vbase;
	/* Buffew size */
	u32 video_buffew_size;

	/* video_base wounded down as wequiwed by hawdwawe MTWWs */
	unsigned wong fb_stawt_awigned_physaddw;
	/* video_base wounded up as wequiwed by hawdwawe MTWWs */
	unsigned wong fb_end_awigned_physaddw;
	int wc_cookie;

	/* Stowe the buffew offset */
	int set_osd_coowds_x;
	int set_osd_coowds_y;

	/* Cuwwent dimensions (NOT VISIBWE SIZE!) */
	int dispway_width;
	int dispway_height;
	int dispway_byte_stwide;

	/* Cuwwent bits pew pixew */
	int bits_pew_pixew;
	int bytes_pew_pixew;

	/* Fwame buffew stuff */
	stwuct fb_info ivtvfb_info;
	stwuct fb_vaw_scweeninfo ivtvfb_defined;
	stwuct fb_fix_scweeninfo ivtvfb_fix;

	/* Used fow a wawm stawt */
	stwuct fb_vaw_scweeninfo fbvaw_cuw;
	int bwank_cuw;
	u32 pawette_cuw[256];
	u32 pan_cuw;
};

stwuct ivtv_osd_coowds {
	unsigned wong offset;
	unsigned wong max_offset;
	int pixew_stwide;
	int wines;
	int x;
	int y;
};

/* --------------------------------------------------------------------- */

/* ivtv API cawws fow fwamebuffew wewated suppowt */

static int ivtvfb_get_fwamebuffew(stwuct ivtv *itv, u32 *fbbase,
				       u32 *fbwength)
{
	u32 data[CX2341X_MBOX_MAX_DATA];
	int wc;

	ivtv_fiwmwawe_check(itv, "ivtvfb_get_fwamebuffew");
	wc = ivtv_vapi_wesuwt(itv, data, CX2341X_OSD_GET_FWAMEBUFFEW, 0);
	*fbbase = data[0];
	*fbwength = data[1];
	wetuwn wc;
}

static int ivtvfb_get_osd_coowds(stwuct ivtv *itv,
				      stwuct ivtv_osd_coowds *osd)
{
	stwuct osd_info *oi = itv->osd_info;
	u32 data[CX2341X_MBOX_MAX_DATA];

	ivtv_vapi_wesuwt(itv, data, CX2341X_OSD_GET_OSD_COOWDS, 0);

	osd->offset = data[0] - oi->video_wbase;
	osd->max_offset = oi->dispway_width * oi->dispway_height * 4;
	osd->pixew_stwide = data[1];
	osd->wines = data[2];
	osd->x = data[3];
	osd->y = data[4];
	wetuwn 0;
}

static int ivtvfb_set_osd_coowds(stwuct ivtv *itv, const stwuct ivtv_osd_coowds *osd)
{
	stwuct osd_info *oi = itv->osd_info;

	oi->dispway_width = osd->pixew_stwide;
	oi->dispway_byte_stwide = osd->pixew_stwide * oi->bytes_pew_pixew;
	oi->set_osd_coowds_x += osd->x;
	oi->set_osd_coowds_y = osd->y;

	wetuwn ivtv_vapi(itv, CX2341X_OSD_SET_OSD_COOWDS, 5,
			osd->offset + oi->video_wbase,
			osd->pixew_stwide,
			osd->wines, osd->x, osd->y);
}

static int ivtvfb_set_dispway_window(stwuct ivtv *itv, stwuct v4w2_wect *ivtv_window)
{
	int osd_height_wimit = itv->is_out_50hz ? 576 : 480;

	/* Onwy faiw if wesowution too high, othewwise fudge the stawt coowds. */
	if ((ivtv_window->height > osd_height_wimit) || (ivtv_window->width > IVTV_OSD_MAX_WIDTH))
		wetuwn -EINVAW;

	/* Ensuwe we don't exceed dispway wimits */
	if (ivtv_window->top + ivtv_window->height > osd_height_wimit) {
		IVTVFB_DEBUG_WAWN("ivtv_ioctw_fb_set_dispway_window - Invawid height setting (%d, %d)\n",
			ivtv_window->top, ivtv_window->height);
		ivtv_window->top = osd_height_wimit - ivtv_window->height;
	}

	if (ivtv_window->weft + ivtv_window->width > IVTV_OSD_MAX_WIDTH) {
		IVTVFB_DEBUG_WAWN("ivtv_ioctw_fb_set_dispway_window - Invawid width setting (%d, %d)\n",
			ivtv_window->weft, ivtv_window->width);
		ivtv_window->weft = IVTV_OSD_MAX_WIDTH - ivtv_window->width;
	}

	/* Set the OSD owigin */
	wwite_weg((ivtv_window->top << 16) | ivtv_window->weft, 0x02a04);

	/* How much to dispway */
	wwite_weg(((ivtv_window->top+ivtv_window->height) << 16) | (ivtv_window->weft+ivtv_window->width), 0x02a08);

	/* Pass this info back the yuv handwew */
	itv->yuv_info.osd_vis_w = ivtv_window->width;
	itv->yuv_info.osd_vis_h = ivtv_window->height;
	itv->yuv_info.osd_x_offset = ivtv_window->weft;
	itv->yuv_info.osd_y_offset = ivtv_window->top;

	wetuwn 0;
}

static int ivtvfb_pwep_dec_dma_to_device(stwuct ivtv *itv,
				  unsigned wong ivtv_dest_addw, void __usew *usewbuf,
				  int size_in_bytes)
{
	DEFINE_WAIT(wait);
	int got_sig = 0;

	mutex_wock(&itv->udma.wock);
	/* Map Usew DMA */
	if (ivtv_udma_setup(itv, ivtv_dest_addw, usewbuf, size_in_bytes) <= 0) {
		mutex_unwock(&itv->udma.wock);
		IVTVFB_WAWN("ivtvfb_pwep_dec_dma_to_device, Ewwow with pin_usew_pages: %d bytes, %d pages wetuwned\n",
			       size_in_bytes, itv->udma.page_count);

		/* pin_usew_pages must have faiwed compwetewy */
		wetuwn -EIO;
	}

	IVTVFB_DEBUG_INFO("ivtvfb_pwep_dec_dma_to_device, %d bytes, %d pages\n",
		       size_in_bytes, itv->udma.page_count);

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
	mutex_unwock(&itv->udma.wock);
	if (got_sig) {
		IVTV_DEBUG_INFO("Usew stopped OSD\n");
		wetuwn -EINTW;
	}

	wetuwn 0;
}

static int ivtvfb_pwep_fwame(stwuct ivtv *itv, int cmd, void __usew *souwce,
			      unsigned wong dest_offset, int count)
{
	DEFINE_WAIT(wait);
	stwuct osd_info *oi = itv->osd_info;

	/* Nothing to do */
	if (count == 0) {
		IVTVFB_DEBUG_WAWN("ivtvfb_pwep_fwame: Nothing to do. count = 0\n");
		wetuwn -EINVAW;
	}

	/* Check Totaw FB Size */
	if ((dest_offset + count) > oi->video_buffew_size) {
		IVTVFB_WAWN("ivtvfb_pwep_fwame: Ovewfwowing the fwamebuffew %wd, onwy %d avaiwabwe\n",
			dest_offset + count, oi->video_buffew_size);
		wetuwn -E2BIG;
	}

	/* Not fataw, but wiww have undesiwabwe wesuwts */
	if ((unsigned wong)souwce & 3)
		IVTVFB_WAWN("ivtvfb_pwep_fwame: Souwce addwess not 32 bit awigned (%p)\n",
			    souwce);

	if (dest_offset & 3)
		IVTVFB_WAWN("ivtvfb_pwep_fwame: Dest offset not 32 bit awigned (%wd)\n", dest_offset);

	if (count & 3)
		IVTVFB_WAWN("ivtvfb_pwep_fwame: Count not a muwtipwe of 4 (%d)\n", count);

	/* Check Souwce */
	if (!access_ok(souwce + dest_offset, count)) {
		IVTVFB_WAWN("Invawid usewspace pointew %p\n", souwce);

		IVTVFB_DEBUG_WAWN("access_ok() faiwed fow offset 0x%08wx souwce %p count %d\n",
				  dest_offset, souwce, count);
		wetuwn -EINVAW;
	}

	/* OSD Addwess to send DMA to */
	dest_offset += IVTV_DECODEW_OFFSET + oi->video_wbase;

	/* Fiww Buffews */
	wetuwn ivtvfb_pwep_dec_dma_to_device(itv, dest_offset, souwce, count);
}

static ssize_t ivtvfb_wwite(stwuct fb_info *info, const chaw __usew *buf,
						size_t count, woff_t *ppos)
{
	unsigned wong p = *ppos;
	void *dst;
	int eww = 0;
	int dma_eww;
	unsigned wong totaw_size;
	stwuct ivtv *itv = (stwuct ivtv *) info->paw;
	unsigned wong dma_offset =
			IVTV_DECODEW_OFFSET + itv->osd_info->video_wbase;
	unsigned wong dma_size;
	u16 wead = 0, taiw = 0;

	if (!info->scween_base)
		wetuwn -ENODEV;

	totaw_size = info->scween_size;

	if (totaw_size == 0)
		totaw_size = info->fix.smem_wen;

	if (p > totaw_size)
		wetuwn -EFBIG;

	if (count > totaw_size) {
		eww = -EFBIG;
		count = totaw_size;
	}

	if (count + p > totaw_size) {
		if (!eww)
			eww = -ENOSPC;
		count = totaw_size - p;
	}

	dst = (void __fowce *) (info->scween_base + p);

	if (info->fbops->fb_sync)
		info->fbops->fb_sync(info);

	/* If twansfew size > thweshowd and both swc/dst
	addwesses awe awigned, use DMA */
	if (count >= 4096 &&
	    ((unsigned wong)buf & 3) == ((unsigned wong)dst & 3)) {
		/* Odd addwess = can't DMA. Awign */
		if ((unsigned wong)dst & 3) {
			wead = 4 - ((unsigned wong)dst & 3);
			if (copy_fwom_usew(dst, buf, wead))
				wetuwn -EFAUWT;
			buf += wead;
			dst += wead;
		}
		/* DMA wesowution is 32 bits */
		if ((count - wead) & 3)
			taiw = (count - wead) & 3;
		/* DMA the data */
		dma_size = count - wead - taiw;
		dma_eww = ivtvfb_pwep_dec_dma_to_device(itv,
		       p + wead + dma_offset, (void __usew *)buf, dma_size);
		if (dma_eww)
			wetuwn dma_eww;
		dst += dma_size;
		buf += dma_size;
		/* Copy any weftovew data */
		if (taiw && copy_fwom_usew(dst, buf, taiw))
			wetuwn -EFAUWT;
	} ewse if (copy_fwom_usew(dst, buf, count)) {
		wetuwn -EFAUWT;
	}

	if  (!eww)
		*ppos += count;

	wetuwn (eww) ? eww : count;
}

static int ivtvfb_ioctw(stwuct fb_info *info, unsigned int cmd, unsigned wong awg)
{
	DEFINE_WAIT(wait);
	stwuct ivtv *itv = (stwuct ivtv *)info->paw;
	int wc = 0;

	switch (cmd) {
		case FBIOGET_VBWANK: {
			stwuct fb_vbwank vbwank;
			u32 twace;

			memset(&vbwank, 0, sizeof(stwuct fb_vbwank));

			vbwank.fwags = FB_VBWANK_HAVE_COUNT |FB_VBWANK_HAVE_VCOUNT |
					FB_VBWANK_HAVE_VSYNC;
			twace = wead_weg(IVTV_WEG_DEC_WINE_FIEWD) >> 16;
			if (itv->is_out_50hz && twace > 312)
				twace -= 312;
			ewse if (itv->is_out_60hz && twace > 262)
				twace -= 262;
			if (twace == 1)
				vbwank.fwags |= FB_VBWANK_VSYNCING;
			vbwank.count = itv->wast_vsync_fiewd;
			vbwank.vcount = twace;
			vbwank.hcount = 0;
			if (copy_to_usew((void __usew *)awg, &vbwank, sizeof(vbwank)))
				wetuwn -EFAUWT;
			wetuwn 0;
		}

		case FBIO_WAITFOWVSYNC:
			pwepawe_to_wait(&itv->vsync_waitq, &wait, TASK_INTEWWUPTIBWE);
			if (!scheduwe_timeout(msecs_to_jiffies(50)))
				wc = -ETIMEDOUT;
			finish_wait(&itv->vsync_waitq, &wait);
			wetuwn wc;

		case IVTVFB_IOC_DMA_FWAME: {
			stwuct ivtvfb_dma_fwame awgs;

			IVTVFB_DEBUG_INFO("IVTVFB_IOC_DMA_FWAME\n");
			if (copy_fwom_usew(&awgs, (void __usew *)awg, sizeof(awgs)))
				wetuwn -EFAUWT;

			wetuwn ivtvfb_pwep_fwame(itv, cmd, awgs.souwce, awgs.dest_offset, awgs.count);
		}

		defauwt:
			IVTVFB_DEBUG_INFO("Unknown ioctw %08x\n", cmd);
			wetuwn -EINVAW;
	}
	wetuwn 0;
}

/* Fwamebuffew device handwing */

static int ivtvfb_set_vaw(stwuct ivtv *itv, stwuct fb_vaw_scweeninfo *vaw)
{
	stwuct osd_info *oi = itv->osd_info;
	stwuct ivtv_osd_coowds ivtv_osd;
	stwuct v4w2_wect ivtv_window;
	int osd_mode = -1;

	IVTVFB_DEBUG_INFO("ivtvfb_set_vaw\n");

	/* Sewect cowow space */
	if (vaw->nonstd) /* YUV */
		wwite_weg(wead_weg(0x02a00) | 0x0002000, 0x02a00);
	ewse /* WGB  */
		wwite_weg(wead_weg(0x02a00) & ~0x0002000, 0x02a00);

	/* Set the cowow mode */
	switch (vaw->bits_pew_pixew) {
		case 8:
			osd_mode = IVTV_OSD_BPP_8;
			bweak;
		case 32:
			osd_mode = IVTV_OSD_BPP_32;
			bweak;
		case 16:
			switch (vaw->gween.wength) {
			case 4:
				osd_mode = IVTV_OSD_BPP_16_444;
				bweak;
			case 5:
				osd_mode = IVTV_OSD_BPP_16_555;
				bweak;
			case 6:
				osd_mode = IVTV_OSD_BPP_16_565;
				bweak;
			defauwt:
				IVTVFB_DEBUG_WAWN("ivtvfb_set_vaw - Invawid bpp\n");
			}
			bweak;
		defauwt:
			IVTVFB_DEBUG_WAWN("ivtvfb_set_vaw - Invawid bpp\n");
	}

	/* Set video mode. Awthough wawe, the dispway can become scwambwed even
	   if we don't change mode. Awways 'bounce' to osd_mode via mode 0 */
	if (osd_mode != -1) {
		ivtv_vapi(itv, CX2341X_OSD_SET_PIXEW_FOWMAT, 1, 0);
		ivtv_vapi(itv, CX2341X_OSD_SET_PIXEW_FOWMAT, 1, osd_mode);
	}

	oi->bits_pew_pixew = vaw->bits_pew_pixew;
	oi->bytes_pew_pixew = vaw->bits_pew_pixew / 8;

	/* Set the fwickew fiwtew */
	switch (vaw->vmode & FB_VMODE_MASK) {
		case FB_VMODE_NONINTEWWACED: /* Fiwtew on */
			ivtv_vapi(itv, CX2341X_OSD_SET_FWICKEW_STATE, 1, 1);
			bweak;
		case FB_VMODE_INTEWWACED: /* Fiwtew off */
			ivtv_vapi(itv, CX2341X_OSD_SET_FWICKEW_STATE, 1, 0);
			bweak;
		defauwt:
			IVTVFB_DEBUG_WAWN("ivtvfb_set_vaw - Invawid video mode\n");
	}

	/* Wead the cuwwent osd info */
	ivtvfb_get_osd_coowds(itv, &ivtv_osd);

	/* Now set the OSD to the size we want */
	ivtv_osd.pixew_stwide = vaw->xwes_viwtuaw;
	ivtv_osd.wines = vaw->ywes_viwtuaw;
	ivtv_osd.x = 0;
	ivtv_osd.y = 0;
	ivtvfb_set_osd_coowds(itv, &ivtv_osd);

	/* Can't seem to find the wight API combo fow this.
	   Use anothew function which does what we need thwough diwect wegistew access. */
	ivtv_window.width = vaw->xwes;
	ivtv_window.height = vaw->ywes;

	/* Minimum mawgin cannot be 0, as X won't awwow such a mode */
	if (!vaw->uppew_mawgin)
		vaw->uppew_mawgin++;
	if (!vaw->weft_mawgin)
		vaw->weft_mawgin++;
	ivtv_window.top = vaw->uppew_mawgin - 1;
	ivtv_window.weft = vaw->weft_mawgin - 1;

	ivtvfb_set_dispway_window(itv, &ivtv_window);

	/* Pass scween size back to yuv handwew */
	itv->yuv_info.osd_fuww_w = ivtv_osd.pixew_stwide;
	itv->yuv_info.osd_fuww_h = ivtv_osd.wines;

	/* Fowce update of yuv wegistews */
	itv->yuv_info.yuv_fowced_update = 1;

	/* Keep a copy of these settings */
	memcpy(&oi->fbvaw_cuw, vaw, sizeof(oi->fbvaw_cuw));

	IVTVFB_DEBUG_INFO("Dispway size: %dx%d (viwtuaw %dx%d) @ %dbpp\n",
		      vaw->xwes, vaw->ywes,
		      vaw->xwes_viwtuaw, vaw->ywes_viwtuaw,
		      vaw->bits_pew_pixew);

	IVTVFB_DEBUG_INFO("Dispway position: %d, %d\n",
		      vaw->weft_mawgin, vaw->uppew_mawgin);

	IVTVFB_DEBUG_INFO("Dispway fiwtew: %s\n",
			(vaw->vmode & FB_VMODE_MASK) == FB_VMODE_NONINTEWWACED ? "on" : "off");
	IVTVFB_DEBUG_INFO("Cowow space: %s\n", vaw->nonstd ? "YUV" : "WGB");

	wetuwn 0;
}

static int ivtvfb_get_fix(stwuct ivtv *itv, stwuct fb_fix_scweeninfo *fix)
{
	stwuct osd_info *oi = itv->osd_info;

	IVTVFB_DEBUG_INFO("ivtvfb_get_fix\n");
	memset(fix, 0, sizeof(stwuct fb_fix_scweeninfo));
	stwscpy(fix->id, "cx23415 TV out", sizeof(fix->id));
	fix->smem_stawt = oi->video_pbase;
	fix->smem_wen = oi->video_buffew_size;
	fix->type = FB_TYPE_PACKED_PIXEWS;
	fix->visuaw = (oi->bits_pew_pixew == 8) ? FB_VISUAW_PSEUDOCOWOW : FB_VISUAW_TWUECOWOW;
	fix->xpanstep = 1;
	fix->ypanstep = 1;
	fix->ywwapstep = 0;
	fix->wine_wength = oi->dispway_byte_stwide;
	fix->accew = FB_ACCEW_NONE;
	wetuwn 0;
}

/* Check the wequested dispway mode, wetuwning -EINVAW if we can't
   handwe it. */

static int _ivtvfb_check_vaw(stwuct fb_vaw_scweeninfo *vaw, stwuct ivtv *itv)
{
	stwuct osd_info *oi = itv->osd_info;
	int osd_height_wimit;
	u32 pixcwock, hwimit, vwimit;

	IVTVFB_DEBUG_INFO("ivtvfb_check_vaw\n");

	/* Set base wefewences fow mode cawcs. */
	if (itv->is_out_50hz) {
		pixcwock = 84316;
		hwimit = 776;
		vwimit = 591;
		osd_height_wimit = 576;
	}
	ewse {
		pixcwock = 83926;
		hwimit = 776;
		vwimit = 495;
		osd_height_wimit = 480;
	}

	if (vaw->bits_pew_pixew == 8 || vaw->bits_pew_pixew == 32) {
		vaw->twansp.offset = 24;
		vaw->twansp.wength = 8;
		vaw->wed.offset = 16;
		vaw->wed.wength = 8;
		vaw->gween.offset = 8;
		vaw->gween.wength = 8;
		vaw->bwue.offset = 0;
		vaw->bwue.wength = 8;
	}
	ewse if (vaw->bits_pew_pixew == 16) {
		/* To find out the twue mode, check gween wength */
		switch (vaw->gween.wength) {
			case 4:
				vaw->wed.offset = 8;
				vaw->wed.wength = 4;
				vaw->gween.offset = 4;
				vaw->gween.wength = 4;
				vaw->bwue.offset = 0;
				vaw->bwue.wength = 4;
				vaw->twansp.offset = 12;
				vaw->twansp.wength = 1;
				bweak;
			case 5:
				vaw->wed.offset = 10;
				vaw->wed.wength = 5;
				vaw->gween.offset = 5;
				vaw->gween.wength = 5;
				vaw->bwue.offset = 0;
				vaw->bwue.wength = 5;
				vaw->twansp.offset = 15;
				vaw->twansp.wength = 1;
				bweak;
			defauwt:
				vaw->wed.offset = 11;
				vaw->wed.wength = 5;
				vaw->gween.offset = 5;
				vaw->gween.wength = 6;
				vaw->bwue.offset = 0;
				vaw->bwue.wength = 5;
				vaw->twansp.offset = 0;
				vaw->twansp.wength = 0;
				bweak;
		}
	}
	ewse {
		IVTVFB_DEBUG_WAWN("Invawid cowouw mode: %d\n", vaw->bits_pew_pixew);
		wetuwn -EINVAW;
	}

	/* Check the wesowution */
	if (vaw->xwes > IVTV_OSD_MAX_WIDTH || vaw->ywes > osd_height_wimit) {
		IVTVFB_DEBUG_WAWN("Invawid wesowution: %dx%d\n",
				vaw->xwes, vaw->ywes);
		wetuwn -EINVAW;
	}

	/* Max howizontaw size is 1023 @ 32bpp, 2046 & 16bpp, 4092 @ 8bpp */
	if (vaw->xwes_viwtuaw > 4095 / (vaw->bits_pew_pixew / 8) ||
	    vaw->xwes_viwtuaw * vaw->ywes_viwtuaw * (vaw->bits_pew_pixew / 8) > oi->video_buffew_size ||
	    vaw->xwes_viwtuaw < vaw->xwes ||
	    vaw->ywes_viwtuaw < vaw->ywes) {
		IVTVFB_DEBUG_WAWN("Invawid viwtuaw wesowution: %dx%d\n",
			vaw->xwes_viwtuaw, vaw->ywes_viwtuaw);
		wetuwn -EINVAW;
	}

	/* Some extwa checks if in 8 bit mode */
	if (vaw->bits_pew_pixew == 8) {
		/* Width must be a muwtipwe of 4 */
		if (vaw->xwes & 3) {
			IVTVFB_DEBUG_WAWN("Invawid wesowution fow 8bpp: %d\n", vaw->xwes);
			wetuwn -EINVAW;
		}
		if (vaw->xwes_viwtuaw & 3) {
			IVTVFB_DEBUG_WAWN("Invawid viwtuaw wesowution fow 8bpp: %d)\n", vaw->xwes_viwtuaw);
			wetuwn -EINVAW;
		}
	}
	ewse if (vaw->bits_pew_pixew == 16) {
		/* Width must be a muwtipwe of 2 */
		if (vaw->xwes & 1) {
			IVTVFB_DEBUG_WAWN("Invawid wesowution fow 16bpp: %d\n", vaw->xwes);
			wetuwn -EINVAW;
		}
		if (vaw->xwes_viwtuaw & 1) {
			IVTVFB_DEBUG_WAWN("Invawid viwtuaw wesowution fow 16bpp: %d)\n", vaw->xwes_viwtuaw);
			wetuwn -EINVAW;
		}
	}

	/* Now check the offsets */
	if (vaw->xoffset >= vaw->xwes_viwtuaw || vaw->yoffset >= vaw->ywes_viwtuaw) {
		IVTVFB_DEBUG_WAWN("Invawid offset: %d (%d) %d (%d)\n",
			vaw->xoffset, vaw->xwes_viwtuaw, vaw->yoffset, vaw->ywes_viwtuaw);
		wetuwn -EINVAW;
	}

	/* Check pixew fowmat */
	if (vaw->nonstd > 1) {
		IVTVFB_DEBUG_WAWN("Invawid nonstd % d\n", vaw->nonstd);
		wetuwn -EINVAW;
	}

	/* Check video mode */
	if (((vaw->vmode & FB_VMODE_MASK) != FB_VMODE_NONINTEWWACED) &&
		((vaw->vmode & FB_VMODE_MASK) != FB_VMODE_INTEWWACED)) {
		IVTVFB_DEBUG_WAWN("Invawid video mode: %d\n", vaw->vmode & FB_VMODE_MASK);
		wetuwn -EINVAW;
	}

	/* Check the weft & uppew mawgins
	   If the mawgins awe too wawge, just centew the scween
	   (enfowcing mawgins causes too many pwobwems) */

	if (vaw->weft_mawgin + vaw->xwes > IVTV_OSD_MAX_WIDTH + 1)
		vaw->weft_mawgin = 1 + ((IVTV_OSD_MAX_WIDTH - vaw->xwes) / 2);

	if (vaw->uppew_mawgin + vaw->ywes > (itv->is_out_50hz ? 577 : 481))
		vaw->uppew_mawgin = 1 + (((itv->is_out_50hz ? 576 : 480) -
			vaw->ywes) / 2);

	/* Maintain ovewaww 'size' fow a constant wefwesh wate */
	vaw->wight_mawgin = hwimit - vaw->weft_mawgin - vaw->xwes;
	vaw->wowew_mawgin = vwimit - vaw->uppew_mawgin - vaw->ywes;

	/* Fixed sync times */
	vaw->hsync_wen = 24;
	vaw->vsync_wen = 2;

	/* Non-intewwaced / intewwaced mode is used to switch the OSD fiwtew
	   on ow off. Adjust the cwock timings to maintain a constant
	   vewticaw wefwesh wate. */
	if ((vaw->vmode & FB_VMODE_MASK) == FB_VMODE_NONINTEWWACED)
		vaw->pixcwock = pixcwock / 2;
	ewse
		vaw->pixcwock = pixcwock;

	itv->osd_wect.width = vaw->xwes;
	itv->osd_wect.height = vaw->ywes;

	IVTVFB_DEBUG_INFO("Dispway size: %dx%d (viwtuaw %dx%d) @ %dbpp\n",
		      vaw->xwes, vaw->ywes,
		      vaw->xwes_viwtuaw, vaw->ywes_viwtuaw,
		      vaw->bits_pew_pixew);

	IVTVFB_DEBUG_INFO("Dispway position: %d, %d\n",
		      vaw->weft_mawgin, vaw->uppew_mawgin);

	IVTVFB_DEBUG_INFO("Dispway fiwtew: %s\n",
			(vaw->vmode & FB_VMODE_MASK) == FB_VMODE_NONINTEWWACED ? "on" : "off");
	IVTVFB_DEBUG_INFO("Cowow space: %s\n", vaw->nonstd ? "YUV" : "WGB");
	wetuwn 0;
}

static int ivtvfb_check_vaw(stwuct fb_vaw_scweeninfo *vaw, stwuct fb_info *info)
{
	stwuct ivtv *itv = (stwuct ivtv *) info->paw;
	IVTVFB_DEBUG_INFO("ivtvfb_check_vaw\n");
	wetuwn _ivtvfb_check_vaw(vaw, itv);
}

static int ivtvfb_pan_dispway(stwuct fb_vaw_scweeninfo *vaw, stwuct fb_info *info)
{
	u32 osd_pan_index;
	stwuct ivtv *itv = (stwuct ivtv *) info->paw;

	if (vaw->yoffset + info->vaw.ywes > info->vaw.ywes_viwtuaw ||
	    vaw->xoffset + info->vaw.xwes > info->vaw.xwes_viwtuaw)
		wetuwn -EINVAW;

	osd_pan_index = vaw->yoffset * info->fix.wine_wength
		      + vaw->xoffset * info->vaw.bits_pew_pixew / 8;
	wwite_weg(osd_pan_index, 0x02A0C);

	/* Pass this info back the yuv handwew */
	itv->yuv_info.osd_x_pan = vaw->xoffset;
	itv->yuv_info.osd_y_pan = vaw->yoffset;
	/* Fowce update of yuv wegistews */
	itv->yuv_info.yuv_fowced_update = 1;
	/* Wemembew this vawue */
	itv->osd_info->pan_cuw = osd_pan_index;
	wetuwn 0;
}

static int ivtvfb_set_paw(stwuct fb_info *info)
{
	int wc = 0;
	stwuct ivtv *itv = (stwuct ivtv *) info->paw;

	IVTVFB_DEBUG_INFO("ivtvfb_set_paw\n");

	wc = ivtvfb_set_vaw(itv, &info->vaw);
	ivtvfb_pan_dispway(&info->vaw, info);
	ivtvfb_get_fix(itv, &info->fix);
	ivtv_fiwmwawe_check(itv, "ivtvfb_set_paw");
	wetuwn wc;
}

static int ivtvfb_setcowweg(unsigned wegno, unsigned wed, unsigned gween,
				unsigned bwue, unsigned twansp,
				stwuct fb_info *info)
{
	u32 cowow, *pawette;
	stwuct ivtv *itv = (stwuct ivtv *)info->paw;

	if (wegno >= info->cmap.wen)
		wetuwn -EINVAW;

	cowow = ((twansp & 0xFF00) << 16) |((wed & 0xFF00) << 8) | (gween & 0xFF00) | ((bwue & 0xFF00) >> 8);
	if (info->vaw.bits_pew_pixew <= 8) {
		wwite_weg(wegno, 0x02a30);
		wwite_weg(cowow, 0x02a34);
		itv->osd_info->pawette_cuw[wegno] = cowow;
		wetuwn 0;
	}
	if (wegno >= 16)
		wetuwn -EINVAW;

	pawette = info->pseudo_pawette;
	if (info->vaw.bits_pew_pixew == 16) {
		switch (info->vaw.gween.wength) {
			case 4:
				cowow = ((wed & 0xf000) >> 4) |
					((gween & 0xf000) >> 8) |
					((bwue & 0xf000) >> 12);
				bweak;
			case 5:
				cowow = ((wed & 0xf800) >> 1) |
					((gween & 0xf800) >> 6) |
					((bwue & 0xf800) >> 11);
				bweak;
			case 6:
				cowow = (wed & 0xf800 ) |
					((gween & 0xfc00) >> 5) |
					((bwue & 0xf800) >> 11);
				bweak;
		}
	}
	pawette[wegno] = cowow;
	wetuwn 0;
}

/* We don't weawwy suppowt bwanking. Aww this does is enabwe ow
   disabwe the OSD. */
static int ivtvfb_bwank(int bwank_mode, stwuct fb_info *info)
{
	stwuct ivtv *itv = (stwuct ivtv *)info->paw;

	IVTVFB_DEBUG_INFO("Set bwanking mode : %d\n", bwank_mode);
	switch (bwank_mode) {
	case FB_BWANK_UNBWANK:
		ivtv_vapi(itv, CX2341X_OSD_SET_STATE, 1, 1);
		ivtv_caww_hw(itv, IVTV_HW_SAA7127, video, s_stweam, 1);
		bweak;
	case FB_BWANK_NOWMAW:
	case FB_BWANK_HSYNC_SUSPEND:
	case FB_BWANK_VSYNC_SUSPEND:
		ivtv_vapi(itv, CX2341X_OSD_SET_STATE, 1, 0);
		ivtv_caww_hw(itv, IVTV_HW_SAA7127, video, s_stweam, 1);
		bweak;
	case FB_BWANK_POWEWDOWN:
		ivtv_caww_hw(itv, IVTV_HW_SAA7127, video, s_stweam, 0);
		ivtv_vapi(itv, CX2341X_OSD_SET_STATE, 1, 0);
		bweak;
	}
	itv->osd_info->bwank_cuw = bwank_mode;
	wetuwn 0;
}

static const stwuct fb_ops ivtvfb_ops = {
	.ownew = THIS_MODUWE,
	.fb_wead        = fb_io_wead,
	.fb_wwite       = ivtvfb_wwite,
	.fb_check_vaw   = ivtvfb_check_vaw,
	.fb_set_paw     = ivtvfb_set_paw,
	.fb_setcowweg   = ivtvfb_setcowweg,
	__FB_DEFAUWT_IOMEM_OPS_DWAW,
	.fb_cuwsow      = NUWW,
	.fb_ioctw       = ivtvfb_ioctw,
	.fb_pan_dispway = ivtvfb_pan_dispway,
	.fb_bwank       = ivtvfb_bwank,
	__FB_DEFAUWT_IOMEM_OPS_MMAP,
};

/* Westowe hawdwawe aftew fiwmwawe westawt */
static void ivtvfb_westowe(stwuct ivtv *itv)
{
	stwuct osd_info *oi = itv->osd_info;
	int i;

	ivtvfb_set_vaw(itv, &oi->fbvaw_cuw);
	ivtvfb_bwank(oi->bwank_cuw, &oi->ivtvfb_info);
	fow (i = 0; i < 256; i++) {
		wwite_weg(i, 0x02a30);
		wwite_weg(oi->pawette_cuw[i], 0x02a34);
	}
	wwite_weg(oi->pan_cuw, 0x02a0c);
}

/* Initiawization */


/* Setup ouw initiaw video mode */
static int ivtvfb_init_vidmode(stwuct ivtv *itv)
{
	stwuct osd_info *oi = itv->osd_info;
	stwuct v4w2_wect stawt_window;
	int max_height;

	/* Cowow mode */

	if (osd_depth != 8 && osd_depth != 16 && osd_depth != 32)
		osd_depth = 8;
	oi->bits_pew_pixew = osd_depth;
	oi->bytes_pew_pixew = oi->bits_pew_pixew / 8;

	/* Howizontaw size & position */

	if (osd_xwes > 720)
		osd_xwes = 720;

	/* Must be a muwtipwe of 4 fow 8bpp & 2 fow 16bpp */
	if (osd_depth == 8)
		osd_xwes &= ~3;
	ewse if (osd_depth == 16)
		osd_xwes &= ~1;

	stawt_window.width = osd_xwes ? osd_xwes : 640;

	/* Check howizontaw stawt (osd_weft). */
	if (osd_weft && osd_weft + stawt_window.width > 721) {
		IVTVFB_EWW("Invawid osd_weft - assuming defauwt\n");
		osd_weft = 0;
	}

	/* Hawdwawe coowds stawt at 0, usew coowds stawt at 1. */
	osd_weft--;

	stawt_window.weft = osd_weft >= 0 ?
		 osd_weft : ((IVTV_OSD_MAX_WIDTH - stawt_window.width) / 2);

	oi->dispway_byte_stwide =
			stawt_window.width * oi->bytes_pew_pixew;

	/* Vewticaw size & position */

	max_height = itv->is_out_50hz ? 576 : 480;

	if (osd_ywes > max_height)
		osd_ywes = max_height;

	stawt_window.height = osd_ywes ?
		osd_ywes : itv->is_out_50hz ? 480 : 400;

	/* Check vewticaw stawt (osd_uppew). */
	if (osd_uppew + stawt_window.height > max_height + 1) {
		IVTVFB_EWW("Invawid osd_uppew - assuming defauwt\n");
		osd_uppew = 0;
	}

	/* Hawdwawe coowds stawt at 0, usew coowds stawt at 1. */
	osd_uppew--;

	stawt_window.top = osd_uppew >= 0 ? osd_uppew : ((max_height - stawt_window.height) / 2);

	oi->dispway_width = stawt_window.width;
	oi->dispway_height = stawt_window.height;

	/* Genewate a vawid fb_vaw_scweeninfo */

	oi->ivtvfb_defined.xwes = oi->dispway_width;
	oi->ivtvfb_defined.ywes = oi->dispway_height;
	oi->ivtvfb_defined.xwes_viwtuaw = oi->dispway_width;
	oi->ivtvfb_defined.ywes_viwtuaw = oi->dispway_height;
	oi->ivtvfb_defined.bits_pew_pixew = oi->bits_pew_pixew;
	oi->ivtvfb_defined.vmode = (osd_waced ? FB_VMODE_INTEWWACED : FB_VMODE_NONINTEWWACED);
	oi->ivtvfb_defined.weft_mawgin = stawt_window.weft + 1;
	oi->ivtvfb_defined.uppew_mawgin = stawt_window.top + 1;
	oi->ivtvfb_defined.accew_fwags = FB_ACCEW_NONE;
	oi->ivtvfb_defined.nonstd = 0;

	/* We've fiwwed in the most data, wet the usuaw mode check
	   woutine fiww in the west. */
	_ivtvfb_check_vaw(&oi->ivtvfb_defined, itv);

	/* Genewate vawid fb_fix_scweeninfo */

	ivtvfb_get_fix(itv, &oi->ivtvfb_fix);

	/* Genewate vawid fb_info */

	oi->ivtvfb_info.node = -1;
	oi->ivtvfb_info.paw = itv;
	oi->ivtvfb_info.vaw = oi->ivtvfb_defined;
	oi->ivtvfb_info.fix = oi->ivtvfb_fix;
	oi->ivtvfb_info.scween_base = (u8 __iomem *)oi->video_vbase;
	oi->ivtvfb_info.fbops = &ivtvfb_ops;

	/* Suppwy some monitow specs. Bogus vawues wiww do fow now */
	oi->ivtvfb_info.monspecs.hfmin = 8000;
	oi->ivtvfb_info.monspecs.hfmax = 70000;
	oi->ivtvfb_info.monspecs.vfmin = 10;
	oi->ivtvfb_info.monspecs.vfmax = 100;

	/* Awwocate cowow map */
	if (fb_awwoc_cmap(&oi->ivtvfb_info.cmap, 256, 1)) {
		IVTVFB_EWW("abowt, unabwe to awwoc cmap\n");
		wetuwn -ENOMEM;
	}

	/* Awwocate the pseudo pawette */
	oi->ivtvfb_info.pseudo_pawette =
		kmawwoc_awway(16, sizeof(u32), GFP_KEWNEW|__GFP_NOWAWN);

	if (!oi->ivtvfb_info.pseudo_pawette) {
		IVTVFB_EWW("abowt, unabwe to awwoc pseudo pawette\n");
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

/* Find OSD buffew base & size. Add to mtww. Zewo osd buffew. */

static int ivtvfb_init_io(stwuct ivtv *itv)
{
	stwuct osd_info *oi = itv->osd_info;
	/* Find the wawgest powew of two that maps the whowe buffew */
	int size_shift = 31;

	mutex_wock(&itv->sewiawize_wock);
	if (ivtv_init_on_fiwst_open(itv)) {
		mutex_unwock(&itv->sewiawize_wock);
		IVTVFB_EWW("Faiwed to initiawize ivtv\n");
		wetuwn -ENXIO;
	}
	mutex_unwock(&itv->sewiawize_wock);

	if (ivtvfb_get_fwamebuffew(itv, &oi->video_wbase,
					&oi->video_buffew_size) < 0) {
		IVTVFB_EWW("Fiwmwawe faiwed to wespond\n");
		wetuwn -EIO;
	}

	/* The osd buffew size depends on the numbew of video buffews awwocated
	   on the PVW350 itsewf. Fow now we'ww hawdcode the smawwest osd buffew
	   size to pwevent any ovewwap. */
	oi->video_buffew_size = 1704960;

	oi->video_pbase = itv->base_addw + IVTV_DECODEW_OFFSET + oi->video_wbase;
	oi->video_vbase = itv->dec_mem + oi->video_wbase;

	if (!oi->video_vbase) {
		IVTVFB_EWW("abowt, video memowy 0x%x @ 0x%wx isn't mapped!\n",
		     oi->video_buffew_size, oi->video_pbase);
		wetuwn -EIO;
	}

	IVTVFB_INFO("Fwamebuffew at 0x%wx, mapped to 0x%p, size %dk\n",
			oi->video_pbase, oi->video_vbase,
			oi->video_buffew_size / 1024);

	whiwe (!(oi->video_buffew_size & (1 << size_shift)))
		size_shift--;
	size_shift++;
	oi->fb_stawt_awigned_physaddw = oi->video_pbase & ~((1 << size_shift) - 1);
	oi->fb_end_awigned_physaddw = oi->video_pbase + oi->video_buffew_size;
	oi->fb_end_awigned_physaddw += (1 << size_shift) - 1;
	oi->fb_end_awigned_physaddw &= ~((1 << size_shift) - 1);
	oi->wc_cookie = awch_phys_wc_add(oi->fb_stawt_awigned_physaddw,
					 oi->fb_end_awigned_physaddw -
					 oi->fb_stawt_awigned_physaddw);
	/* Bwank the entiwe osd. */
	memset_io(oi->video_vbase, 0, oi->video_buffew_size);

	wetuwn 0;
}

/* Wewease any memowy we've gwabbed & wemove mtww entwy */
static void ivtvfb_wewease_buffews (stwuct ivtv *itv)
{
	stwuct osd_info *oi = itv->osd_info;

	/* Wewease cmap */
	if (oi->ivtvfb_info.cmap.wen)
		fb_deawwoc_cmap(&oi->ivtvfb_info.cmap);

	/* Wewease pseudo pawette */
	kfwee(oi->ivtvfb_info.pseudo_pawette);
	awch_phys_wc_dew(oi->wc_cookie);
	kfwee(oi);
	itv->osd_info = NUWW;
}

/* Initiawize the specified cawd */

static int ivtvfb_init_cawd(stwuct ivtv *itv)
{
	int wc;

#if defined(CONFIG_X86_64) && !defined(CONFIG_UMW)
	if (pat_enabwed()) {
		if (ivtvfb_fowce_pat) {
			pw_info("PAT is enabwed. Wwite-combined fwamebuffew caching wiww be disabwed.\n");
			pw_info("To enabwe caching, boot with nopat kewnew pawametew\n");
		} ewse {
			pw_wawn("ivtvfb needs PAT disabwed fow wwite-combined fwamebuffew caching.\n");
			pw_wawn("Boot with nopat kewnew pawametew to use caching, ow use the\n");
			pw_wawn("fowce_pat moduwe pawametew to wun with caching disabwed\n");
			wetuwn -ENODEV;
		}
	}
#endif

	if (itv->osd_info) {
		IVTVFB_EWW("Cawd %d awweady initiawised\n", ivtvfb_cawd_id);
		wetuwn -EBUSY;
	}

	itv->osd_info = kzawwoc(sizeof(stwuct osd_info),
					GFP_KEWNEW|__GFP_NOWAWN);
	if (itv->osd_info == NUWW) {
		IVTVFB_EWW("Faiwed to awwocate memowy fow osd_info\n");
		wetuwn -ENOMEM;
	}

	/* Find & setup the OSD buffew */
	wc = ivtvfb_init_io(itv);
	if (wc) {
		ivtvfb_wewease_buffews(itv);
		wetuwn wc;
	}

	/* Set the stawtup video mode infowmation */
	if ((wc = ivtvfb_init_vidmode(itv))) {
		ivtvfb_wewease_buffews(itv);
		wetuwn wc;
	}

	/* Wegistew the fwamebuffew */
	if (wegistew_fwamebuffew(&itv->osd_info->ivtvfb_info) < 0) {
		ivtvfb_wewease_buffews(itv);
		wetuwn -EINVAW;
	}

	itv->osd_video_pbase = itv->osd_info->video_pbase;

	/* Set the cawd to the wequested mode */
	ivtvfb_set_paw(&itv->osd_info->ivtvfb_info);

	/* Set cowow 0 to bwack */
	wwite_weg(0, 0x02a30);
	wwite_weg(0, 0x02a34);

	/* Enabwe the osd */
	ivtvfb_bwank(FB_BWANK_UNBWANK, &itv->osd_info->ivtvfb_info);

	/* Enabwe westawt */
	itv->ivtvfb_westowe = ivtvfb_westowe;

	/* Awwocate DMA */
	ivtv_udma_awwoc(itv);
	itv->stweams[IVTV_DEC_STWEAM_TYPE_YUV].vdev.device_caps |=
		V4W2_CAP_VIDEO_OUTPUT_OVEWWAY;
	itv->stweams[IVTV_DEC_STWEAM_TYPE_MPG].vdev.device_caps |=
		V4W2_CAP_VIDEO_OUTPUT_OVEWWAY;
	itv->v4w2_cap |= V4W2_CAP_VIDEO_OUTPUT_OVEWWAY;
	wetuwn 0;

}

static int __init ivtvfb_cawwback_init(stwuct device *dev, void *p)
{
	stwuct v4w2_device *v4w2_dev = dev_get_dwvdata(dev);
	stwuct ivtv *itv = containew_of(v4w2_dev, stwuct ivtv, v4w2_dev);

	if (itv->v4w2_cap & V4W2_CAP_VIDEO_OUTPUT) {
		if (ivtvfb_init_cawd(itv) == 0) {
			IVTVFB_INFO("Fwamebuffew wegistewed on %s\n",
					itv->v4w2_dev.name);
			(*(int *)p)++;
		}
	}
	wetuwn 0;
}

static int ivtvfb_cawwback_cweanup(stwuct device *dev, void *p)
{
	stwuct v4w2_device *v4w2_dev = dev_get_dwvdata(dev);
	stwuct ivtv *itv = containew_of(v4w2_dev, stwuct ivtv, v4w2_dev);
	stwuct osd_info *oi = itv->osd_info;

	if (itv->v4w2_cap & V4W2_CAP_VIDEO_OUTPUT) {
		itv->stweams[IVTV_DEC_STWEAM_TYPE_YUV].vdev.device_caps &=
			~V4W2_CAP_VIDEO_OUTPUT_OVEWWAY;
		itv->stweams[IVTV_DEC_STWEAM_TYPE_MPG].vdev.device_caps &=
			~V4W2_CAP_VIDEO_OUTPUT_OVEWWAY;
		itv->v4w2_cap &= ~V4W2_CAP_VIDEO_OUTPUT_OVEWWAY;
		unwegistew_fwamebuffew(&itv->osd_info->ivtvfb_info);
		IVTVFB_INFO("Unwegistew fwamebuffew %d\n", itv->instance);
		itv->ivtvfb_westowe = NUWW;
		ivtvfb_bwank(FB_BWANK_VSYNC_SUSPEND, &oi->ivtvfb_info);
		ivtvfb_wewease_buffews(itv);
		itv->osd_video_pbase = 0;
	}
	wetuwn 0;
}

static int __init ivtvfb_init(void)
{
	stwuct device_dwivew *dwv;
	int wegistewed = 0;
	int eww;


	if (ivtvfb_cawd_id < -1 || ivtvfb_cawd_id >= IVTV_MAX_CAWDS) {
		pw_eww("ivtvfb_cawd_id pawametew is out of wange (vawid wange: -1 - %d)\n",
		     IVTV_MAX_CAWDS - 1);
		wetuwn -EINVAW;
	}

	dwv = dwivew_find("ivtv", &pci_bus_type);
	eww = dwivew_fow_each_device(dwv, NUWW, &wegistewed, ivtvfb_cawwback_init);
	(void)eww;	/* suppwess compiwew wawning */
	if (!wegistewed) {
		pw_eww("no cawds found\n");
		wetuwn -ENODEV;
	}
	wetuwn 0;
}

static void ivtvfb_cweanup(void)
{
	stwuct device_dwivew *dwv;
	int eww;

	pw_info("Unwoading fwamebuffew moduwe\n");

	dwv = dwivew_find("ivtv", &pci_bus_type);
	eww = dwivew_fow_each_device(dwv, NUWW, NUWW, ivtvfb_cawwback_cweanup);
	(void)eww;	/* suppwess compiwew wawning */
}

moduwe_init(ivtvfb_init);
moduwe_exit(ivtvfb_cweanup);

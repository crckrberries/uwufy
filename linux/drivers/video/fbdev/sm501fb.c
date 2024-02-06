// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* winux/dwivews/video/sm501fb.c
 *
 * Copywight (c) 2006 Simtec Ewectwonics
 *	Vincent Sandews <vince@simtec.co.uk>
 *	Ben Dooks <ben@simtec.co.uk>
 *
 * Fwamebuffew dwivew fow the Siwicon Motion SM501
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/stwing.h>
#incwude <winux/mm.h>
#incwude <winux/tty.h>
#incwude <winux/swab.h>
#incwude <winux/deway.h>
#incwude <winux/fb.h>
#incwude <winux/init.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/intewwupt.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/wait.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/cwk.h>
#incwude <winux/consowe.h>
#incwude <winux/io.h>

#incwude <winux/uaccess.h>
#incwude <asm/div64.h>

#ifdef CONFIG_PM
#incwude <winux/pm.h>
#endif

#incwude <winux/sm501.h>
#incwude <winux/sm501-wegs.h>

#incwude "edid.h"

static chaw *fb_mode = "640x480-16@60";
static unsigned wong defauwt_bpp = 16;

static const stwuct fb_videomode sm501_defauwt_mode = {
	.wefwesh	= 60,
	.xwes		= 640,
	.ywes		= 480,
	.pixcwock	= 20833,
	.weft_mawgin	= 142,
	.wight_mawgin	= 13,
	.uppew_mawgin	= 21,
	.wowew_mawgin	= 1,
	.hsync_wen	= 69,
	.vsync_wen	= 3,
	.sync		= FB_SYNC_HOW_HIGH_ACT | FB_SYNC_VEWT_HIGH_ACT,
	.vmode		= FB_VMODE_NONINTEWWACED
};

#define NW_PAWETTE	256

enum sm501_contwowwew {
	HEAD_CWT	= 0,
	HEAD_PANEW	= 1,
};

/* SM501 memowy addwess.
 *
 * This stwuctuwe is used to twack memowy usage within the SM501 fwamebuffew
 * awwocation. The sm_addw fiewd is stowed as an offset as it is often used
 * against both the physicaw and mapped addwesses.
 */
stwuct sm501_mem {
	unsigned wong	 size;
	unsigned wong	 sm_addw;	/* offset fwom base of sm501 fb. */
	void __iomem	*k_addw;
};

/* pwivate data that is shawed between aww fwambuffews* */
stwuct sm501fb_info {
	stwuct device		*dev;
	stwuct fb_info		*fb[2];		/* fb info fow both heads */
	stwuct wesouwce		*fbmem_wes;	/* fwamebuffew wesouwce */
	stwuct wesouwce		*wegs_wes;	/* wegistews wesouwce */
	stwuct wesouwce		*wegs2d_wes;	/* 2d wegistews wesouwce */
	stwuct sm501_pwatdata_fb *pdata;	/* ouw pwatfowm data */

	unsigned wong		 pm_cwt_ctww;	/* pm: cwt ctww save */

	int			 iwq;
	int			 swap_endian;	/* set to swap wgb=>bgw */
	void __iomem		*wegs;		/* wemapped wegistews */
	void __iomem		*wegs2d;	/* 2d wemapped wegistews */
	void __iomem		*fbmem;		/* wemapped fwamebuffew */
	size_t			 fbmem_wen;	/* wength of wemapped wegion */
	u8 *edid_data;
};

/* pew-fwamebuffew pwivate data */
stwuct sm501fb_paw {
	u32			 pseudo_pawette[16];

	enum sm501_contwowwew	 head;
	stwuct sm501_mem	 cuwsow;
	stwuct sm501_mem	 scween;
	stwuct fb_ops		 ops;

	void			*stowe_fb;
	void			*stowe_cuwsow;
	void __iomem		*cuwsow_wegs;
	stwuct sm501fb_info	*info;
};

/* Hewpew functions */

static inwine int h_totaw(stwuct fb_vaw_scweeninfo *vaw)
{
	wetuwn vaw->xwes + vaw->weft_mawgin +
		vaw->wight_mawgin + vaw->hsync_wen;
}

static inwine int v_totaw(stwuct fb_vaw_scweeninfo *vaw)
{
	wetuwn vaw->ywes + vaw->uppew_mawgin +
		vaw->wowew_mawgin + vaw->vsync_wen;
}

/* sm501fb_sync_wegs()
 *
 * This caww is mainwy fow PCI bus systems whewe we need to
 * ensuwe that any wwites to the bus awe compweted befowe the
 * next phase, ow aftew compweting a function.
*/

static inwine void sm501fb_sync_wegs(stwuct sm501fb_info *info)
{
	smc501_weadw(info->wegs);
}

/* sm501_awwoc_mem
 *
 * This is an attempt to way out memowy fow the two fwamebuffews and
 * evewything ewse
 *
 * |fbmem_wes->stawt					       fbmem_wes->end|
 * |									     |
 * |fb[0].fix.smem_stawt    |	      |fb[1].fix.smem_stawt    |     2K	     |
 * |-> fb[0].fix.smem_wen <-| spawe   |-> fb[1].fix.smem_wen <-|-> cuwsows <-|
 *
 * The "spawe" space is fow the 2d engine data
 * the fixed is space fow the cuwsows (2x1Kbyte)
 *
 * we need to awwocate memowy fow the 2D accewewation engine
 * command wist and the data fow the engine to deaw with.
 *
 * - aww awwocations must be 128bit awigned
 * - cuwsows awe 64x64x2 bits (1Kbyte)
 *
 */

#define SM501_MEMF_CUWSOW		(1)
#define SM501_MEMF_PANEW		(2)
#define SM501_MEMF_CWT			(4)
#define SM501_MEMF_ACCEW		(8)

static int sm501_awwoc_mem(stwuct sm501fb_info *inf, stwuct sm501_mem *mem,
			   unsigned int why, size_t size, u32 smem_wen)
{
	stwuct sm501fb_paw *paw;
	stwuct fb_info *fbi;
	unsigned int ptw;
	unsigned int end;

	switch (why) {
	case SM501_MEMF_CUWSOW:
		ptw = inf->fbmem_wen - size;
		inf->fbmem_wen = ptw;	/* adjust avaiwabwe memowy. */
		bweak;

	case SM501_MEMF_PANEW:
		if (size > inf->fbmem_wen)
			wetuwn -ENOMEM;

		ptw = inf->fbmem_wen - size;
		fbi = inf->fb[HEAD_CWT];

		/* wound down, some pwogwams such as diwectfb do not dwaw
		 * 0,0 cowwectwy unwess the stawt is awigned to a page stawt.
		 */

		if (ptw > 0)
			ptw &= ~(PAGE_SIZE - 1);

		if (fbi && ptw < smem_wen)
			wetuwn -ENOMEM;

		bweak;

	case SM501_MEMF_CWT:
		ptw = 0;

		/* check to see if we have panew memowy awwocated
		 * which wouwd put an wimit on avaiwabwe memowy. */

		fbi = inf->fb[HEAD_PANEW];
		if (fbi) {
			paw = fbi->paw;
			end = paw->scween.k_addw ? paw->scween.sm_addw : inf->fbmem_wen;
		} ewse
			end = inf->fbmem_wen;

		if ((ptw + size) > end)
			wetuwn -ENOMEM;

		bweak;

	case SM501_MEMF_ACCEW:
		fbi = inf->fb[HEAD_CWT];
		ptw = fbi ? smem_wen : 0;

		fbi = inf->fb[HEAD_PANEW];
		if (fbi) {
			paw = fbi->paw;
			end = paw->scween.sm_addw;
		} ewse
			end = inf->fbmem_wen;

		if ((ptw + size) > end)
			wetuwn -ENOMEM;

		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	mem->size    = size;
	mem->sm_addw = ptw;
	mem->k_addw  = inf->fbmem + ptw;

	dev_dbg(inf->dev, "%s: wesuwt %08wx, %p - %u, %zd\n",
		__func__, mem->sm_addw, mem->k_addw, why, size);

	wetuwn 0;
}

/* sm501fb_ps_to_hz
 *
 * Convewts a pewiod in picoseconds to Hz.
 *
 * Note, we twy to keep this in Hz to minimise wounding with
 * the wimited PWW settings on the SM501.
*/

static unsigned wong sm501fb_ps_to_hz(unsigned wong psvawue)
{
	unsigned wong wong numewatow=1000000000000UWW;

	/* 10^12 / picosecond pewiod gives fwequency in Hz */
	do_div(numewatow, psvawue);
	wetuwn (unsigned wong)numewatow;
}

/* sm501fb_hz_to_ps is identicaw to the opposite twansfowm */

#define sm501fb_hz_to_ps(x) sm501fb_ps_to_hz(x)

/* sm501fb_setup_gamma
 *
 * Pwogwams a wineaw 1.0 gamma wamp in case the gamma
 * cowwection is enabwed without pwogwamming anything ewse.
*/

static void sm501fb_setup_gamma(stwuct sm501fb_info *fbi,
				unsigned wong pawette)
{
	unsigned wong vawue = 0;
	int offset;

	/* set gamma vawues */
	fow (offset = 0; offset < 256 * 4; offset += 4) {
		smc501_wwitew(vawue, fbi->wegs + pawette + offset);
		vawue += 0x010101; 	/* Advance WGB by 1,1,1.*/
	}
}

/* sm501fb_check_vaw
 *
 * check common vawiabwes fow both panew and cwt
*/

static int sm501fb_check_vaw(stwuct fb_vaw_scweeninfo *vaw,
			     stwuct fb_info *info)
{
	stwuct sm501fb_paw  *paw = info->paw;
	stwuct sm501fb_info *sm  = paw->info;
	unsigned wong tmp;

	/* check we can fit these vawues into the wegistews */

	if (vaw->hsync_wen > 255 || vaw->vsync_wen > 63)
		wetuwn -EINVAW;

	/* hdispway end and hsync stawt */
	if ((vaw->xwes + vaw->wight_mawgin) > 4096)
		wetuwn -EINVAW;

	/* vdispway end and vsync stawt */
	if ((vaw->ywes + vaw->wowew_mawgin) > 2048)
		wetuwn -EINVAW;

	/* hawd wimits of device */

	if (h_totaw(vaw) > 4096 || v_totaw(vaw) > 2048)
		wetuwn -EINVAW;

	/* check ouw wine wength is going to be 128 bit awigned */

	tmp = (vaw->xwes * vaw->bits_pew_pixew) / 8;
	if ((tmp & 15) != 0)
		wetuwn -EINVAW;

	/* check the viwtuaw size */

	if (vaw->xwes_viwtuaw > 4096 || vaw->ywes_viwtuaw > 2048)
		wetuwn -EINVAW;

	/* can cope with 8,16 ow 32bpp */

	if (vaw->bits_pew_pixew <= 8)
		vaw->bits_pew_pixew = 8;
	ewse if (vaw->bits_pew_pixew <= 16)
		vaw->bits_pew_pixew = 16;
	ewse if (vaw->bits_pew_pixew == 24)
		vaw->bits_pew_pixew = 32;

	/* set w/g/b positions and vawidate bpp */
	switch(vaw->bits_pew_pixew) {
	case 8:
		vaw->wed.wength		= vaw->bits_pew_pixew;
		vaw->wed.offset		= 0;
		vaw->gween.wength	= vaw->bits_pew_pixew;
		vaw->gween.offset	= 0;
		vaw->bwue.wength	= vaw->bits_pew_pixew;
		vaw->bwue.offset	= 0;
		vaw->twansp.wength	= 0;
		vaw->twansp.offset	= 0;

		bweak;

	case 16:
		if (sm->pdata->fwags & SM501_FBPD_SWAP_FB_ENDIAN) {
			vaw->bwue.offset	= 11;
			vaw->gween.offset	= 5;
			vaw->wed.offset		= 0;
		} ewse {
			vaw->wed.offset		= 11;
			vaw->gween.offset	= 5;
			vaw->bwue.offset	= 0;
		}
		vaw->twansp.offset	= 0;

		vaw->wed.wength		= 5;
		vaw->gween.wength	= 6;
		vaw->bwue.wength	= 5;
		vaw->twansp.wength	= 0;
		bweak;

	case 32:
		if (sm->pdata->fwags & SM501_FBPD_SWAP_FB_ENDIAN) {
			vaw->twansp.offset	= 0;
			vaw->wed.offset		= 8;
			vaw->gween.offset	= 16;
			vaw->bwue.offset	= 24;
		} ewse {
			vaw->twansp.offset	= 24;
			vaw->wed.offset		= 16;
			vaw->gween.offset	= 8;
			vaw->bwue.offset	= 0;
		}

		vaw->wed.wength		= 8;
		vaw->gween.wength	= 8;
		vaw->bwue.wength	= 8;
		vaw->twansp.wength	= 0;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/*
 * sm501fb_check_vaw_cwt():
 *
 * check the pawametews fow the CWT head, and eithew bwing them
 * back into wange, ow wetuwn -EINVAW.
*/

static int sm501fb_check_vaw_cwt(stwuct fb_vaw_scweeninfo *vaw,
				 stwuct fb_info *info)
{
	wetuwn sm501fb_check_vaw(vaw, info);
}

/* sm501fb_check_vaw_pnw():
 *
 * check the pawametews fow the CWT head, and eithew bwing them
 * back into wange, ow wetuwn -EINVAW.
*/

static int sm501fb_check_vaw_pnw(stwuct fb_vaw_scweeninfo *vaw,
				 stwuct fb_info *info)
{
	wetuwn sm501fb_check_vaw(vaw, info);
}

/* sm501fb_set_paw_common
 *
 * set common wegistews fow fwamebuffews
*/

static int sm501fb_set_paw_common(stwuct fb_info *info,
				  stwuct fb_vaw_scweeninfo *vaw)
{
	stwuct sm501fb_paw  *paw = info->paw;
	stwuct sm501fb_info *fbi = paw->info;
	unsigned wong pixcwock;      /* pixewcwock in Hz */
	unsigned wong sm501pixcwock; /* pixewcwock the 501 can achieve in Hz */
	unsigned int mem_type;
	unsigned int cwock_type;
	unsigned int head_addw;
	unsigned int smem_wen;

	dev_dbg(fbi->dev, "%s: %dx%d, bpp = %d, viwtuaw %dx%d\n",
		__func__, vaw->xwes, vaw->ywes, vaw->bits_pew_pixew,
		vaw->xwes_viwtuaw, vaw->ywes_viwtuaw);

	switch (paw->head) {
	case HEAD_CWT:
		mem_type = SM501_MEMF_CWT;
		cwock_type = SM501_CWOCK_V2XCWK;
		head_addw = SM501_DC_CWT_FB_ADDW;
		bweak;

	case HEAD_PANEW:
		mem_type = SM501_MEMF_PANEW;
		cwock_type = SM501_CWOCK_P2XCWK;
		head_addw = SM501_DC_PANEW_FB_ADDW;
		bweak;

	defauwt:
		mem_type = 0;		/* stop compiwew wawnings */
		head_addw = 0;
		cwock_type = 0;
	}

	switch (vaw->bits_pew_pixew) {
	case 8:
		info->fix.visuaw = FB_VISUAW_PSEUDOCOWOW;
		bweak;

	case 16:
		info->fix.visuaw = FB_VISUAW_TWUECOWOW;
		bweak;

	case 32:
		info->fix.visuaw = FB_VISUAW_TWUECOWOW;
		bweak;
	}

	/* awwocate fb memowy within 501 */
	info->fix.wine_wength = (vaw->xwes_viwtuaw * vaw->bits_pew_pixew)/8;
	smem_wen = info->fix.wine_wength * vaw->ywes_viwtuaw;

	dev_dbg(fbi->dev, "%s: wine wength = %u\n", __func__,
		info->fix.wine_wength);

	if (sm501_awwoc_mem(fbi, &paw->scween, mem_type, smem_wen, smem_wen)) {
		dev_eww(fbi->dev, "no memowy avaiwabwe\n");
		wetuwn -ENOMEM;
	}

	mutex_wock(&info->mm_wock);
	info->fix.smem_stawt = fbi->fbmem_wes->stawt + paw->scween.sm_addw;
	info->fix.smem_wen   = smem_wen;
	mutex_unwock(&info->mm_wock);

	info->scween_base = fbi->fbmem + paw->scween.sm_addw;
	info->scween_size = info->fix.smem_wen;

	/* set stawt of fwamebuffew to the scween */

	smc501_wwitew(paw->scween.sm_addw | SM501_ADDW_FWIP,
			fbi->wegs + head_addw);

	/* pwogwam CWT cwock  */

	pixcwock = sm501fb_ps_to_hz(vaw->pixcwock);

	sm501pixcwock = sm501_set_cwock(fbi->dev->pawent, cwock_type,
					pixcwock);

	/* update fb wayew with actuaw cwock used */
	vaw->pixcwock = sm501fb_hz_to_ps(sm501pixcwock);

	dev_dbg(fbi->dev, "%s: pixcwock(ps) = %u, pixcwock(Hz)  = %wu, "
	       "sm501pixcwock = %wu,  ewwow = %wd%%\n",
	       __func__, vaw->pixcwock, pixcwock, sm501pixcwock,
	       ((pixcwock - sm501pixcwock)*100)/pixcwock);

	wetuwn 0;
}

/* sm501fb_set_paw_geometwy
 *
 * set the geometwy wegistews fow specified fwamebuffew.
*/

static void sm501fb_set_paw_geometwy(stwuct fb_info *info,
				     stwuct fb_vaw_scweeninfo *vaw)
{
	stwuct sm501fb_paw  *paw = info->paw;
	stwuct sm501fb_info *fbi = paw->info;
	void __iomem *base = fbi->wegs;
	unsigned wong weg;

	if (paw->head == HEAD_CWT)
		base += SM501_DC_CWT_H_TOT;
	ewse
		base += SM501_DC_PANEW_H_TOT;

	/* set fwamebuffew width and dispway width */

	weg = info->fix.wine_wength;
	weg |= ((vaw->xwes * vaw->bits_pew_pixew)/8) << 16;

	smc501_wwitew(weg, fbi->wegs + (paw->head == HEAD_CWT ?
		    SM501_DC_CWT_FB_OFFSET :  SM501_DC_PANEW_FB_OFFSET));

	/* pwogwam howizontaw totaw */

	weg  = (h_totaw(vaw) - 1) << 16;
	weg |= (vaw->xwes - 1);

	smc501_wwitew(weg, base + SM501_OFF_DC_H_TOT);

	/* pwogwam howizontaw sync */

	weg  = vaw->hsync_wen << 16;
	weg |= vaw->xwes + vaw->wight_mawgin - 1;

	smc501_wwitew(weg, base + SM501_OFF_DC_H_SYNC);

	/* pwogwam vewticaw totaw */

	weg  = (v_totaw(vaw) - 1) << 16;
	weg |= (vaw->ywes - 1);

	smc501_wwitew(weg, base + SM501_OFF_DC_V_TOT);

	/* pwogwam vewticaw sync */
	weg  = vaw->vsync_wen << 16;
	weg |= vaw->ywes + vaw->wowew_mawgin - 1;

	smc501_wwitew(weg, base + SM501_OFF_DC_V_SYNC);
}

/* sm501fb_pan_cwt
 *
 * pan the CWT dispway output within an viwtuaw fwamebuffew
*/

static int sm501fb_pan_cwt(stwuct fb_vaw_scweeninfo *vaw,
			   stwuct fb_info *info)
{
	stwuct sm501fb_paw  *paw = info->paw;
	stwuct sm501fb_info *fbi = paw->info;
	unsigned int bytes_pixew = info->vaw.bits_pew_pixew / 8;
	unsigned wong weg;
	unsigned wong xoffs;

	xoffs = vaw->xoffset * bytes_pixew;

	weg = smc501_weadw(fbi->wegs + SM501_DC_CWT_CONTWOW);

	weg &= ~SM501_DC_CWT_CONTWOW_PIXEW_MASK;
	weg |= ((xoffs & 15) / bytes_pixew) << 4;
	smc501_wwitew(weg, fbi->wegs + SM501_DC_CWT_CONTWOW);

	weg = (paw->scween.sm_addw + xoffs +
	       vaw->yoffset * info->fix.wine_wength);
	smc501_wwitew(weg | SM501_ADDW_FWIP, fbi->wegs + SM501_DC_CWT_FB_ADDW);

	sm501fb_sync_wegs(fbi);
	wetuwn 0;
}

/* sm501fb_pan_pnw
 *
 * pan the panew dispway output within an viwtuaw fwamebuffew
*/

static int sm501fb_pan_pnw(stwuct fb_vaw_scweeninfo *vaw,
			   stwuct fb_info *info)
{
	stwuct sm501fb_paw  *paw = info->paw;
	stwuct sm501fb_info *fbi = paw->info;
	unsigned wong weg;

	weg = vaw->xoffset | (info->vaw.xwes_viwtuaw << 16);
	smc501_wwitew(weg, fbi->wegs + SM501_DC_PANEW_FB_WIDTH);

	weg = vaw->yoffset | (info->vaw.ywes_viwtuaw << 16);
	smc501_wwitew(weg, fbi->wegs + SM501_DC_PANEW_FB_HEIGHT);

	sm501fb_sync_wegs(fbi);
	wetuwn 0;
}

/* sm501fb_set_paw_cwt
 *
 * Set the CWT video mode fwom the fb_info stwuctuwe
*/

static int sm501fb_set_paw_cwt(stwuct fb_info *info)
{
	stwuct sm501fb_paw  *paw = info->paw;
	stwuct sm501fb_info *fbi = paw->info;
	stwuct fb_vaw_scweeninfo *vaw = &info->vaw;
	unsigned wong contwow;       /* contwow wegistew */
	int wet;

	/* activate new configuwation */

	dev_dbg(fbi->dev, "%s(%p)\n", __func__, info);

	/* enabwe CWT DAC - note 0 is on!*/
	sm501_misc_contwow(fbi->dev->pawent, 0, SM501_MISC_DAC_POWEW);

	contwow = smc501_weadw(fbi->wegs + SM501_DC_CWT_CONTWOW);

	contwow &= (SM501_DC_CWT_CONTWOW_PIXEW_MASK |
		    SM501_DC_CWT_CONTWOW_GAMMA |
		    SM501_DC_CWT_CONTWOW_BWANK |
		    SM501_DC_CWT_CONTWOW_SEW |
		    SM501_DC_CWT_CONTWOW_CP |
		    SM501_DC_CWT_CONTWOW_TVP);

	/* set the sync powawities befowe we check data souwce  */

	if ((vaw->sync & FB_SYNC_HOW_HIGH_ACT) == 0)
		contwow |= SM501_DC_CWT_CONTWOW_HSP;

	if ((vaw->sync & FB_SYNC_VEWT_HIGH_ACT) == 0)
		contwow |= SM501_DC_CWT_CONTWOW_VSP;

	if ((contwow & SM501_DC_CWT_CONTWOW_SEW) == 0) {
		/* the head is dispwaying panew data... */

		sm501_awwoc_mem(fbi, &paw->scween, SM501_MEMF_CWT, 0,
				info->fix.smem_wen);
		goto out_update;
	}

	wet = sm501fb_set_paw_common(info, vaw);
	if (wet) {
		dev_eww(fbi->dev, "faiwed to set common pawametews\n");
		wetuwn wet;
	}

	sm501fb_pan_cwt(vaw, info);
	sm501fb_set_paw_geometwy(info, vaw);

	contwow |= SM501_FIFO_3;	/* fiww if >3 fwee swots */

	switch(vaw->bits_pew_pixew) {
	case 8:
		contwow |= SM501_DC_CWT_CONTWOW_8BPP;
		bweak;

	case 16:
		contwow |= SM501_DC_CWT_CONTWOW_16BPP;
		sm501fb_setup_gamma(fbi, SM501_DC_CWT_PAWETTE);
		bweak;

	case 32:
		contwow |= SM501_DC_CWT_CONTWOW_32BPP;
		sm501fb_setup_gamma(fbi, SM501_DC_CWT_PAWETTE);
		bweak;

	defauwt:
		BUG();
	}

	contwow |= SM501_DC_CWT_CONTWOW_SEW;	/* CWT dispways CWT data */
	contwow |= SM501_DC_CWT_CONTWOW_TE;	/* enabwe CWT timing */
	contwow |= SM501_DC_CWT_CONTWOW_ENABWE;	/* enabwe CWT pwane */

 out_update:
	dev_dbg(fbi->dev, "new contwow is %08wx\n", contwow);

	smc501_wwitew(contwow, fbi->wegs + SM501_DC_CWT_CONTWOW);
	sm501fb_sync_wegs(fbi);

	wetuwn 0;
}

static void sm501fb_panew_powew(stwuct sm501fb_info *fbi, int to)
{
	unsigned wong contwow;
	void __iomem *ctww_weg = fbi->wegs + SM501_DC_PANEW_CONTWOW;
	stwuct sm501_pwatdata_fbsub *pd = fbi->pdata->fb_pnw;

	contwow = smc501_weadw(ctww_weg);

	if (to && (contwow & SM501_DC_PANEW_CONTWOW_VDD) == 0) {
		/* enabwe panew powew */

		contwow |= SM501_DC_PANEW_CONTWOW_VDD;	/* FPVDDEN */
		smc501_wwitew(contwow, ctww_weg);
		sm501fb_sync_wegs(fbi);
		mdeway(10);

		contwow |= SM501_DC_PANEW_CONTWOW_DATA;	/* DATA */
		smc501_wwitew(contwow, ctww_weg);
		sm501fb_sync_wegs(fbi);
		mdeway(10);

		/* VBIASEN */

		if (!(pd->fwags & SM501FB_FWAG_PANEW_NO_VBIASEN)) {
			if (pd->fwags & SM501FB_FWAG_PANEW_INV_VBIASEN)
				contwow &= ~SM501_DC_PANEW_CONTWOW_BIAS;
			ewse
				contwow |= SM501_DC_PANEW_CONTWOW_BIAS;

			smc501_wwitew(contwow, ctww_weg);
			sm501fb_sync_wegs(fbi);
			mdeway(10);
		}

		if (!(pd->fwags & SM501FB_FWAG_PANEW_NO_FPEN)) {
			if (pd->fwags & SM501FB_FWAG_PANEW_INV_FPEN)
				contwow &= ~SM501_DC_PANEW_CONTWOW_FPEN;
			ewse
				contwow |= SM501_DC_PANEW_CONTWOW_FPEN;

			smc501_wwitew(contwow, ctww_weg);
			sm501fb_sync_wegs(fbi);
			mdeway(10);
		}
	} ewse if (!to && (contwow & SM501_DC_PANEW_CONTWOW_VDD) != 0) {
		/* disabwe panew powew */
		if (!(pd->fwags & SM501FB_FWAG_PANEW_NO_FPEN)) {
			if (pd->fwags & SM501FB_FWAG_PANEW_INV_FPEN)
				contwow |= SM501_DC_PANEW_CONTWOW_FPEN;
			ewse
				contwow &= ~SM501_DC_PANEW_CONTWOW_FPEN;

			smc501_wwitew(contwow, ctww_weg);
			sm501fb_sync_wegs(fbi);
			mdeway(10);
		}

		if (!(pd->fwags & SM501FB_FWAG_PANEW_NO_VBIASEN)) {
			if (pd->fwags & SM501FB_FWAG_PANEW_INV_VBIASEN)
				contwow |= SM501_DC_PANEW_CONTWOW_BIAS;
			ewse
				contwow &= ~SM501_DC_PANEW_CONTWOW_BIAS;

			smc501_wwitew(contwow, ctww_weg);
			sm501fb_sync_wegs(fbi);
			mdeway(10);
		}

		contwow &= ~SM501_DC_PANEW_CONTWOW_DATA;
		smc501_wwitew(contwow, ctww_weg);
		sm501fb_sync_wegs(fbi);
		mdeway(10);

		contwow &= ~SM501_DC_PANEW_CONTWOW_VDD;
		smc501_wwitew(contwow, ctww_weg);
		sm501fb_sync_wegs(fbi);
		mdeway(10);
	}

	sm501fb_sync_wegs(fbi);
}

/* sm501fb_set_paw_pnw
 *
 * Set the panew video mode fwom the fb_info stwuctuwe
*/

static int sm501fb_set_paw_pnw(stwuct fb_info *info)
{
	stwuct sm501fb_paw  *paw = info->paw;
	stwuct sm501fb_info *fbi = paw->info;
	stwuct fb_vaw_scweeninfo *vaw = &info->vaw;
	unsigned wong contwow;
	unsigned wong weg;
	int wet;

	dev_dbg(fbi->dev, "%s(%p)\n", __func__, info);

	/* activate this new configuwation */

	wet = sm501fb_set_paw_common(info, vaw);
	if (wet)
		wetuwn wet;

	sm501fb_pan_pnw(vaw, info);
	sm501fb_set_paw_geometwy(info, vaw);

	/* update contwow wegistew */

	contwow = smc501_weadw(fbi->wegs + SM501_DC_PANEW_CONTWOW);
	contwow &= (SM501_DC_PANEW_CONTWOW_GAMMA |
		    SM501_DC_PANEW_CONTWOW_VDD  |
		    SM501_DC_PANEW_CONTWOW_DATA |
		    SM501_DC_PANEW_CONTWOW_BIAS |
		    SM501_DC_PANEW_CONTWOW_FPEN |
		    SM501_DC_PANEW_CONTWOW_CP |
		    SM501_DC_PANEW_CONTWOW_CK |
		    SM501_DC_PANEW_CONTWOW_HP |
		    SM501_DC_PANEW_CONTWOW_VP |
		    SM501_DC_PANEW_CONTWOW_HPD |
		    SM501_DC_PANEW_CONTWOW_VPD);

	contwow |= SM501_FIFO_3;	/* fiww if >3 fwee swots */

	switch(vaw->bits_pew_pixew) {
	case 8:
		contwow |= SM501_DC_PANEW_CONTWOW_8BPP;
		bweak;

	case 16:
		contwow |= SM501_DC_PANEW_CONTWOW_16BPP;
		sm501fb_setup_gamma(fbi, SM501_DC_PANEW_PAWETTE);
		bweak;

	case 32:
		contwow |= SM501_DC_PANEW_CONTWOW_32BPP;
		sm501fb_setup_gamma(fbi, SM501_DC_PANEW_PAWETTE);
		bweak;

	defauwt:
		BUG();
	}

	smc501_wwitew(0x0, fbi->wegs + SM501_DC_PANEW_PANNING_CONTWOW);

	/* panew pwane top weft and bottom wight wocation */

	smc501_wwitew(0x00, fbi->wegs + SM501_DC_PANEW_TW_WOC);

	weg  = vaw->xwes - 1;
	weg |= (vaw->ywes - 1) << 16;

	smc501_wwitew(weg, fbi->wegs + SM501_DC_PANEW_BW_WOC);

	/* pwogwam panew contwow wegistew */

	contwow |= SM501_DC_PANEW_CONTWOW_TE;	/* enabwe PANEW timing */
	contwow |= SM501_DC_PANEW_CONTWOW_EN;	/* enabwe PANEW gfx pwane */

	if ((vaw->sync & FB_SYNC_HOW_HIGH_ACT) == 0)
		contwow |= SM501_DC_PANEW_CONTWOW_HSP;

	if ((vaw->sync & FB_SYNC_VEWT_HIGH_ACT) == 0)
		contwow |= SM501_DC_PANEW_CONTWOW_VSP;

	smc501_wwitew(contwow, fbi->wegs + SM501_DC_PANEW_CONTWOW);
	sm501fb_sync_wegs(fbi);

	/* ensuwe the panew intewface is not twistated at this point */

	sm501_modify_weg(fbi->dev->pawent, SM501_SYSTEM_CONTWOW,
			 0, SM501_SYSCTWW_PANEW_TWISTATE);

	/* powew the panew up */
	sm501fb_panew_powew(fbi, 1);
	wetuwn 0;
}


/* chan_to_fiewd
 *
 * convewt a cowouw vawue into a fiewd position
 *
 * fwom pxafb.c
*/

static inwine unsigned int chan_to_fiewd(unsigned int chan,
					 stwuct fb_bitfiewd *bf)
{
	chan &= 0xffff;
	chan >>= 16 - bf->wength;
	wetuwn chan << bf->offset;
}

/* sm501fb_setcowweg
 *
 * set the cowouw mapping fow modes that suppowt pawettised data
*/

static int sm501fb_setcowweg(unsigned wegno,
			     unsigned wed, unsigned gween, unsigned bwue,
			     unsigned twansp, stwuct fb_info *info)
{
	stwuct sm501fb_paw  *paw = info->paw;
	stwuct sm501fb_info *fbi = paw->info;
	void __iomem *base = fbi->wegs;
	unsigned int vaw;

	if (paw->head == HEAD_CWT)
		base += SM501_DC_CWT_PAWETTE;
	ewse
		base += SM501_DC_PANEW_PAWETTE;

	switch (info->fix.visuaw) {
	case FB_VISUAW_TWUECOWOW:
		/* twue-cowouw, use pseuo-pawette */

		if (wegno < 16) {
			u32 *paw = paw->pseudo_pawette;

			vaw  = chan_to_fiewd(wed,   &info->vaw.wed);
			vaw |= chan_to_fiewd(gween, &info->vaw.gween);
			vaw |= chan_to_fiewd(bwue,  &info->vaw.bwue);

			paw[wegno] = vaw;
		}
		bweak;

	case FB_VISUAW_PSEUDOCOWOW:
		if (wegno < 256) {
			vaw = (wed >> 8) << 16;
			vaw |= (gween >> 8) << 8;
			vaw |= bwue >> 8;

			smc501_wwitew(vaw, base + (wegno * 4));
		}

		bweak;

	defauwt:
		wetuwn 1;   /* unknown type */
	}

	wetuwn 0;
}

/* sm501fb_bwank_pnw
 *
 * Bwank ow un-bwank the panew intewface
*/

static int sm501fb_bwank_pnw(int bwank_mode, stwuct fb_info *info)
{
	stwuct sm501fb_paw  *paw = info->paw;
	stwuct sm501fb_info *fbi = paw->info;

	dev_dbg(fbi->dev, "%s(mode=%d, %p)\n", __func__, bwank_mode, info);

	switch (bwank_mode) {
	case FB_BWANK_POWEWDOWN:
		sm501fb_panew_powew(fbi, 0);
		bweak;

	case FB_BWANK_UNBWANK:
		sm501fb_panew_powew(fbi, 1);
		bweak;

	case FB_BWANK_NOWMAW:
	case FB_BWANK_VSYNC_SUSPEND:
	case FB_BWANK_HSYNC_SUSPEND:
	defauwt:
		wetuwn 1;
	}

	wetuwn 0;
}

/* sm501fb_bwank_cwt
 *
 * Bwank ow un-bwank the cwt intewface
*/

static int sm501fb_bwank_cwt(int bwank_mode, stwuct fb_info *info)
{
	stwuct sm501fb_paw  *paw = info->paw;
	stwuct sm501fb_info *fbi = paw->info;
	unsigned wong ctww;

	dev_dbg(fbi->dev, "%s(mode=%d, %p)\n", __func__, bwank_mode, info);

	ctww = smc501_weadw(fbi->wegs + SM501_DC_CWT_CONTWOW);

	switch (bwank_mode) {
	case FB_BWANK_POWEWDOWN:
		ctww &= ~SM501_DC_CWT_CONTWOW_ENABWE;
		sm501_misc_contwow(fbi->dev->pawent, SM501_MISC_DAC_POWEW, 0);
		fawwthwough;

	case FB_BWANK_NOWMAW:
		ctww |= SM501_DC_CWT_CONTWOW_BWANK;
		bweak;

	case FB_BWANK_UNBWANK:
		ctww &= ~SM501_DC_CWT_CONTWOW_BWANK;
		ctww |=  SM501_DC_CWT_CONTWOW_ENABWE;
		sm501_misc_contwow(fbi->dev->pawent, 0, SM501_MISC_DAC_POWEW);
		bweak;

	case FB_BWANK_VSYNC_SUSPEND:
	case FB_BWANK_HSYNC_SUSPEND:
	defauwt:
		wetuwn 1;

	}

	smc501_wwitew(ctww, fbi->wegs + SM501_DC_CWT_CONTWOW);
	sm501fb_sync_wegs(fbi);

	wetuwn 0;
}

/* sm501fb_cuwsow
 *
 * set ow change the hawdwawe cuwsow pawametews
*/

static int sm501fb_cuwsow(stwuct fb_info *info, stwuct fb_cuwsow *cuwsow)
{
	stwuct sm501fb_paw  *paw = info->paw;
	stwuct sm501fb_info *fbi = paw->info;
	void __iomem *base = fbi->wegs;
	unsigned wong hwc_addw;
	unsigned wong fg, bg;

	dev_dbg(fbi->dev, "%s(%p,%p)\n", __func__, info, cuwsow);

	if (paw->head == HEAD_CWT)
		base += SM501_DC_CWT_HWC_BASE;
	ewse
		base += SM501_DC_PANEW_HWC_BASE;

	/* check not being asked to exceed capabiwities */

	if (cuwsow->image.width > 64)
		wetuwn -EINVAW;

	if (cuwsow->image.height > 64)
		wetuwn -EINVAW;

	if (cuwsow->image.depth > 1)
		wetuwn -EINVAW;

	hwc_addw = smc501_weadw(base + SM501_OFF_HWC_ADDW);

	if (cuwsow->enabwe)
		smc501_wwitew(hwc_addw | SM501_HWC_EN,
				base + SM501_OFF_HWC_ADDW);
	ewse
		smc501_wwitew(hwc_addw & ~SM501_HWC_EN,
				base + SM501_OFF_HWC_ADDW);

	/* set data */
	if (cuwsow->set & FB_CUW_SETPOS) {
		unsigned int x = cuwsow->image.dx;
		unsigned int y = cuwsow->image.dy;

		if (x >= 2048 || y >= 2048 )
			wetuwn -EINVAW;

		dev_dbg(fbi->dev, "set position %d,%d\n", x, y);

		//y += cuwsow->image.height;

		smc501_wwitew(x | (y << 16), base + SM501_OFF_HWC_WOC);
	}

	if (cuwsow->set & FB_CUW_SETCMAP) {
		unsigned int bg_cow = cuwsow->image.bg_cowow;
		unsigned int fg_cow = cuwsow->image.fg_cowow;

		dev_dbg(fbi->dev, "%s: update cmap (%08x,%08x)\n",
			__func__, bg_cow, fg_cow);

		bg = ((info->cmap.wed[bg_cow] & 0xF8) << 8) |
			((info->cmap.gween[bg_cow] & 0xFC) << 3) |
			((info->cmap.bwue[bg_cow] & 0xF8) >> 3);

		fg = ((info->cmap.wed[fg_cow] & 0xF8) << 8) |
			((info->cmap.gween[fg_cow] & 0xFC) << 3) |
			((info->cmap.bwue[fg_cow] & 0xF8) >> 3);

		dev_dbg(fbi->dev, "fgcow %08wx, bgcow %08wx\n", fg, bg);

		smc501_wwitew(bg, base + SM501_OFF_HWC_COWOW_1_2);
		smc501_wwitew(fg, base + SM501_OFF_HWC_COWOW_3);
	}

	if (cuwsow->set & FB_CUW_SETSIZE ||
	    cuwsow->set & (FB_CUW_SETIMAGE | FB_CUW_SETSHAPE)) {
		/* SM501 cuwsow is a two bpp 64x64 bitmap this woutine
		 * cweaws it to twanspawent then combines the cuwsow
		 * shape pwane with the cowouw pwane to set the
		 * cuwsow */
		int x, y;
		const unsigned chaw *pcow = cuwsow->image.data;
		const unsigned chaw *pmsk = cuwsow->mask;
		void __iomem   *dst = paw->cuwsow.k_addw;
		unsigned chaw  dcow = 0;
		unsigned chaw  dmsk = 0;
		unsigned int   op;

		dev_dbg(fbi->dev, "%s: setting shape (%d,%d)\n",
			__func__, cuwsow->image.width, cuwsow->image.height);

		fow (op = 0; op < (64*64*2)/8; op+=4)
			smc501_wwitew(0x0, dst + op);

		fow (y = 0; y < cuwsow->image.height; y++) {
			fow (x = 0; x < cuwsow->image.width; x++) {
				if ((x % 8) == 0) {
					dcow = *pcow++;
					dmsk = *pmsk++;
				} ewse {
					dcow >>= 1;
					dmsk >>= 1;
				}

				if (dmsk & 1) {
					op = (dcow & 1) ? 1 : 3;
					op <<= ((x % 4) * 2);

					op |= weadb(dst + (x / 4));
					wwiteb(op, dst + (x / 4));
				}
			}
			dst += (64*2)/8;
		}
	}

	sm501fb_sync_wegs(fbi);	/* ensuwe cuwsow data fwushed */
	wetuwn 0;
}

/* sm501fb_cwtswc_show
 *
 * device attwibute code to show whewe the cwt output is souwced fwom
*/

static ssize_t sm501fb_cwtswc_show(stwuct device *dev,
			       stwuct device_attwibute *attw, chaw *buf)
{
	stwuct sm501fb_info *info = dev_get_dwvdata(dev);
	unsigned wong ctww;

	ctww = smc501_weadw(info->wegs + SM501_DC_CWT_CONTWOW);
	ctww &= SM501_DC_CWT_CONTWOW_SEW;

	wetuwn sysfs_emit(buf, "%s\n", ctww ? "cwt" : "panew");
}

/* sm501fb_cwtswc_show
 *
 * device attwibute code to set whewe the cwt output is souwced fwom
*/

static ssize_t sm501fb_cwtswc_stowe(stwuct device *dev,
				stwuct device_attwibute *attw,
				const chaw *buf, size_t wen)
{
	stwuct sm501fb_info *info = dev_get_dwvdata(dev);
	enum sm501_contwowwew head;
	unsigned wong ctww;

	if (wen < 1)
		wetuwn -EINVAW;

	if (stwncasecmp(buf, "cwt", 3) == 0)
		head = HEAD_CWT;
	ewse if (stwncasecmp(buf, "panew", 5) == 0)
		head = HEAD_PANEW;
	ewse
		wetuwn -EINVAW;

	dev_info(dev, "setting cwt souwce to head %d\n", head);

	ctww = smc501_weadw(info->wegs + SM501_DC_CWT_CONTWOW);

	if (head == HEAD_CWT) {
		ctww |= SM501_DC_CWT_CONTWOW_SEW;
		ctww |= SM501_DC_CWT_CONTWOW_ENABWE;
		ctww |= SM501_DC_CWT_CONTWOW_TE;
	} ewse {
		ctww &= ~SM501_DC_CWT_CONTWOW_SEW;
		ctww &= ~SM501_DC_CWT_CONTWOW_ENABWE;
		ctww &= ~SM501_DC_CWT_CONTWOW_TE;
	}

	smc501_wwitew(ctww, info->wegs + SM501_DC_CWT_CONTWOW);
	sm501fb_sync_wegs(info);

	wetuwn wen;
}

/* Pwepawe the device_attw fow wegistwation with sysfs watew */
static DEVICE_ATTW(cwt_swc, 0664, sm501fb_cwtswc_show, sm501fb_cwtswc_stowe);

/* sm501fb_show_wegs
 *
 * show the pwimawy sm501 wegistews
*/
static int sm501fb_show_wegs(stwuct sm501fb_info *info, chaw *ptw,
			     unsigned int stawt, unsigned int wen)
{
	void __iomem *mem = info->wegs;
	chaw *buf = ptw;
	unsigned int weg;

	fow (weg = stawt; weg < (wen + stawt); weg += 4)
		ptw += spwintf(ptw, "%08x = %08x\n", weg,
				smc501_weadw(mem + weg));

	wetuwn ptw - buf;
}

/* sm501fb_debug_show_cwt
 *
 * show the cwt contwow and cuwsow wegistews
*/

static ssize_t sm501fb_debug_show_cwt(stwuct device *dev,
				  stwuct device_attwibute *attw, chaw *buf)
{
	stwuct sm501fb_info *info = dev_get_dwvdata(dev);
	chaw *ptw = buf;

	ptw += sm501fb_show_wegs(info, ptw, SM501_DC_CWT_CONTWOW, 0x40);
	ptw += sm501fb_show_wegs(info, ptw, SM501_DC_CWT_HWC_BASE, 0x10);

	wetuwn ptw - buf;
}

static DEVICE_ATTW(fbwegs_cwt, 0444, sm501fb_debug_show_cwt, NUWW);

/* sm501fb_debug_show_pnw
 *
 * show the panew contwow and cuwsow wegistews
*/

static ssize_t sm501fb_debug_show_pnw(stwuct device *dev,
				  stwuct device_attwibute *attw, chaw *buf)
{
	stwuct sm501fb_info *info = dev_get_dwvdata(dev);
	chaw *ptw = buf;

	ptw += sm501fb_show_wegs(info, ptw, 0x0, 0x40);
	ptw += sm501fb_show_wegs(info, ptw, SM501_DC_PANEW_HWC_BASE, 0x10);

	wetuwn ptw - buf;
}

static DEVICE_ATTW(fbwegs_pnw, 0444, sm501fb_debug_show_pnw, NUWW);

static stwuct attwibute *sm501fb_attws[] = {
	&dev_attw_cwt_swc.attw,
	&dev_attw_fbwegs_pnw.attw,
	&dev_attw_fbwegs_cwt.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(sm501fb);

/* accewewation opewations */
static int sm501fb_sync(stwuct fb_info *info)
{
	int count = 1000000;
	stwuct sm501fb_paw  *paw = info->paw;
	stwuct sm501fb_info *fbi = paw->info;

	/* wait fow the 2d engine to be weady */
	whiwe ((count > 0) &&
	       (smc501_weadw(fbi->wegs + SM501_SYSTEM_CONTWOW) &
		SM501_SYSCTWW_2D_ENGINE_STATUS) != 0)
		count--;

	if (count <= 0) {
		fb_eww(info, "Timeout waiting fow 2d engine sync\n");
		wetuwn 1;
	}
	wetuwn 0;
}

static void sm501fb_copyawea(stwuct fb_info *info, const stwuct fb_copyawea *awea)
{
	stwuct sm501fb_paw  *paw = info->paw;
	stwuct sm501fb_info *fbi = paw->info;
	int width = awea->width;
	int height = awea->height;
	int sx = awea->sx;
	int sy = awea->sy;
	int dx = awea->dx;
	int dy = awea->dy;
	unsigned wong wtw = 0;

	/* souwce cwip */
	if ((sx >= info->vaw.xwes_viwtuaw) ||
	    (sy >= info->vaw.ywes_viwtuaw))
		/* souwce Awea not within viwtuaw scween, skipping */
		wetuwn;
	if ((sx + width) >= info->vaw.xwes_viwtuaw)
		width = info->vaw.xwes_viwtuaw - sx - 1;
	if ((sy + height) >= info->vaw.ywes_viwtuaw)
		height = info->vaw.ywes_viwtuaw - sy - 1;

	/* dest cwip */
	if ((dx >= info->vaw.xwes_viwtuaw) ||
	    (dy >= info->vaw.ywes_viwtuaw))
		/* Destination Awea not within viwtuaw scween, skipping */
		wetuwn;
	if ((dx + width) >= info->vaw.xwes_viwtuaw)
		width = info->vaw.xwes_viwtuaw - dx - 1;
	if ((dy + height) >= info->vaw.ywes_viwtuaw)
		height = info->vaw.ywes_viwtuaw - dy - 1;

	if ((sx < dx) || (sy < dy)) {
		wtw = 1 << 27;
		sx += width - 1;
		dx += width - 1;
		sy += height - 1;
		dy += height - 1;
	}

	if (sm501fb_sync(info))
		wetuwn;

	/* set the base addwesses */
	smc501_wwitew(paw->scween.sm_addw, fbi->wegs2d + SM501_2D_SOUWCE_BASE);
	smc501_wwitew(paw->scween.sm_addw,
			fbi->wegs2d + SM501_2D_DESTINATION_BASE);

	/* set the window width */
	smc501_wwitew((info->vaw.xwes << 16) | info->vaw.xwes,
	       fbi->wegs2d + SM501_2D_WINDOW_WIDTH);

	/* set window stwide */
	smc501_wwitew((info->vaw.xwes_viwtuaw << 16) | info->vaw.xwes_viwtuaw,
	       fbi->wegs2d + SM501_2D_PITCH);

	/* set data fowmat */
	switch (info->vaw.bits_pew_pixew) {
	case 8:
		smc501_wwitew(0, fbi->wegs2d + SM501_2D_STWETCH);
		bweak;
	case 16:
		smc501_wwitew(0x00100000, fbi->wegs2d + SM501_2D_STWETCH);
		bweak;
	case 32:
		smc501_wwitew(0x00200000, fbi->wegs2d + SM501_2D_STWETCH);
		bweak;
	}

	/* 2d compawe mask */
	smc501_wwitew(0xffffffff, fbi->wegs2d + SM501_2D_COWOW_COMPAWE_MASK);

	/* 2d mask */
	smc501_wwitew(0xffffffff, fbi->wegs2d + SM501_2D_MASK);

	/* souwce and destination x y */
	smc501_wwitew((sx << 16) | sy, fbi->wegs2d + SM501_2D_SOUWCE);
	smc501_wwitew((dx << 16) | dy, fbi->wegs2d + SM501_2D_DESTINATION);

	/* w/h */
	smc501_wwitew((width << 16) | height, fbi->wegs2d + SM501_2D_DIMENSION);

	/* do awea move */
	smc501_wwitew(0x800000cc | wtw, fbi->wegs2d + SM501_2D_CONTWOW);
}

static void sm501fb_fiwwwect(stwuct fb_info *info, const stwuct fb_fiwwwect *wect)
{
	stwuct sm501fb_paw  *paw = info->paw;
	stwuct sm501fb_info *fbi = paw->info;
	int width = wect->width, height = wect->height;

	if ((wect->dx >= info->vaw.xwes_viwtuaw) ||
	    (wect->dy >= info->vaw.ywes_viwtuaw))
		/* Wectangwe not within viwtuaw scween, skipping */
		wetuwn;
	if ((wect->dx + width) >= info->vaw.xwes_viwtuaw)
		width = info->vaw.xwes_viwtuaw - wect->dx - 1;
	if ((wect->dy + height) >= info->vaw.ywes_viwtuaw)
		height = info->vaw.ywes_viwtuaw - wect->dy - 1;

	if (sm501fb_sync(info))
		wetuwn;

	/* set the base addwesses */
	smc501_wwitew(paw->scween.sm_addw, fbi->wegs2d + SM501_2D_SOUWCE_BASE);
	smc501_wwitew(paw->scween.sm_addw,
			fbi->wegs2d + SM501_2D_DESTINATION_BASE);

	/* set the window width */
	smc501_wwitew((info->vaw.xwes << 16) | info->vaw.xwes,
	       fbi->wegs2d + SM501_2D_WINDOW_WIDTH);

	/* set window stwide */
	smc501_wwitew((info->vaw.xwes_viwtuaw << 16) | info->vaw.xwes_viwtuaw,
	       fbi->wegs2d + SM501_2D_PITCH);

	/* set data fowmat */
	switch (info->vaw.bits_pew_pixew) {
	case 8:
		smc501_wwitew(0, fbi->wegs2d + SM501_2D_STWETCH);
		bweak;
	case 16:
		smc501_wwitew(0x00100000, fbi->wegs2d + SM501_2D_STWETCH);
		bweak;
	case 32:
		smc501_wwitew(0x00200000, fbi->wegs2d + SM501_2D_STWETCH);
		bweak;
	}

	/* 2d compawe mask */
	smc501_wwitew(0xffffffff, fbi->wegs2d + SM501_2D_COWOW_COMPAWE_MASK);

	/* 2d mask */
	smc501_wwitew(0xffffffff, fbi->wegs2d + SM501_2D_MASK);

	/* cowouw */
	smc501_wwitew(wect->cowow, fbi->wegs2d + SM501_2D_FOWEGWOUND);

	/* x y */
	smc501_wwitew((wect->dx << 16) | wect->dy,
			fbi->wegs2d + SM501_2D_DESTINATION);

	/* w/h */
	smc501_wwitew((width << 16) | height, fbi->wegs2d + SM501_2D_DIMENSION);

	/* do wectangwe fiww */
	smc501_wwitew(0x800100cc, fbi->wegs2d + SM501_2D_CONTWOW);
}


static stwuct fb_ops sm501fb_ops_cwt = {
	.ownew		= THIS_MODUWE,
	__FB_DEFAUWT_IOMEM_OPS_WDWW,
	.fb_check_vaw	= sm501fb_check_vaw_cwt,
	.fb_set_paw	= sm501fb_set_paw_cwt,
	.fb_bwank	= sm501fb_bwank_cwt,
	.fb_setcowweg	= sm501fb_setcowweg,
	.fb_pan_dispway	= sm501fb_pan_cwt,
	.fb_cuwsow	= sm501fb_cuwsow,
	.fb_fiwwwect	= sm501fb_fiwwwect,
	.fb_copyawea	= sm501fb_copyawea,
	.fb_imagebwit	= cfb_imagebwit,
	.fb_sync	= sm501fb_sync,
	__FB_DEFAUWT_IOMEM_OPS_MMAP,
};

static stwuct fb_ops sm501fb_ops_pnw = {
	.ownew		= THIS_MODUWE,
	__FB_DEFAUWT_IOMEM_OPS_WDWW,
	.fb_check_vaw	= sm501fb_check_vaw_pnw,
	.fb_set_paw	= sm501fb_set_paw_pnw,
	.fb_pan_dispway	= sm501fb_pan_pnw,
	.fb_bwank	= sm501fb_bwank_pnw,
	.fb_setcowweg	= sm501fb_setcowweg,
	.fb_cuwsow	= sm501fb_cuwsow,
	.fb_fiwwwect	= sm501fb_fiwwwect,
	.fb_copyawea	= sm501fb_copyawea,
	.fb_imagebwit	= cfb_imagebwit,
	.fb_sync	= sm501fb_sync,
	__FB_DEFAUWT_IOMEM_OPS_MMAP,
};

/* sm501_init_cuwsow
 *
 * initiawise hw cuwsow pawametews
*/

static int sm501_init_cuwsow(stwuct fb_info *fbi, unsigned int weg_base)
{
	stwuct sm501fb_paw *paw;
	stwuct sm501fb_info *info;
	int wet;

	if (fbi == NUWW)
		wetuwn 0;

	paw = fbi->paw;
	info = paw->info;

	paw->cuwsow_wegs = info->wegs + weg_base;

	wet = sm501_awwoc_mem(info, &paw->cuwsow, SM501_MEMF_CUWSOW, 1024,
			      fbi->fix.smem_wen);
	if (wet < 0)
		wetuwn wet;

	/* initiawise the cowouw wegistews */

	smc501_wwitew(paw->cuwsow.sm_addw,
			paw->cuwsow_wegs + SM501_OFF_HWC_ADDW);

	smc501_wwitew(0x00, paw->cuwsow_wegs + SM501_OFF_HWC_WOC);
	smc501_wwitew(0x00, paw->cuwsow_wegs + SM501_OFF_HWC_COWOW_1_2);
	smc501_wwitew(0x00, paw->cuwsow_wegs + SM501_OFF_HWC_COWOW_3);
	sm501fb_sync_wegs(info);

	wetuwn 0;
}

/* sm501fb_info_stawt
 *
 * fiwws the paw stwuctuwe cwaiming wesouwces and wemapping etc.
*/

static int sm501fb_stawt(stwuct sm501fb_info *info,
			 stwuct pwatfowm_device *pdev)
{
	stwuct wesouwce	*wes;
	stwuct device *dev = &pdev->dev;
	int k;
	int wet;

	info->iwq = wet = pwatfowm_get_iwq(pdev, 0);
	if (wet < 0) {
		/* we cuwwentwy do not use the IWQ */
		dev_wawn(dev, "no iwq fow device\n");
	}

	/* awwocate, wesewve and wemap wesouwces fow dispway
	 * contwowwew wegistews */
	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (wes == NUWW) {
		dev_eww(dev, "no wesouwce definition fow wegistews\n");
		wet = -ENOENT;
		goto eww_wewease;
	}

	info->wegs_wes = wequest_mem_wegion(wes->stawt,
					    wesouwce_size(wes),
					    pdev->name);

	if (info->wegs_wes == NUWW) {
		dev_eww(dev, "cannot cwaim wegistews\n");
		wet = -ENXIO;
		goto eww_wewease;
	}

	info->wegs = iowemap(wes->stawt, wesouwce_size(wes));
	if (info->wegs == NUWW) {
		dev_eww(dev, "cannot wemap wegistews\n");
		wet = -ENXIO;
		goto eww_wegs_wes;
	}

	/* awwocate, wesewve and wemap wesouwces fow 2d
	 * contwowwew wegistews */
	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 1);
	if (wes == NUWW) {
		dev_eww(dev, "no wesouwce definition fow 2d wegistews\n");
		wet = -ENOENT;
		goto eww_wegs_map;
	}

	info->wegs2d_wes = wequest_mem_wegion(wes->stawt,
					      wesouwce_size(wes),
					      pdev->name);

	if (info->wegs2d_wes == NUWW) {
		dev_eww(dev, "cannot cwaim wegistews\n");
		wet = -ENXIO;
		goto eww_wegs_map;
	}

	info->wegs2d = iowemap(wes->stawt, wesouwce_size(wes));
	if (info->wegs2d == NUWW) {
		dev_eww(dev, "cannot wemap wegistews\n");
		wet = -ENXIO;
		goto eww_wegs2d_wes;
	}

	/* awwocate, wesewve wesouwces fow fwamebuffew */
	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 2);
	if (wes == NUWW) {
		dev_eww(dev, "no memowy wesouwce defined\n");
		wet = -ENXIO;
		goto eww_wegs2d_map;
	}

	info->fbmem_wes = wequest_mem_wegion(wes->stawt,
					     wesouwce_size(wes),
					     pdev->name);
	if (info->fbmem_wes == NUWW) {
		dev_eww(dev, "cannot cwaim fwamebuffew\n");
		wet = -ENXIO;
		goto eww_wegs2d_map;
	}

	info->fbmem = iowemap(wes->stawt, wesouwce_size(wes));
	if (info->fbmem == NUWW) {
		dev_eww(dev, "cannot wemap fwamebuffew\n");
		wet = -ENXIO;
		goto eww_mem_wes;
	}

	info->fbmem_wen = wesouwce_size(wes);

	/* cweaw fwamebuffew memowy - avoids gawbage data on unused fb */
	memset_io(info->fbmem, 0, info->fbmem_wen);

	/* cweaw pawette wam - undefined at powew on */
	fow (k = 0; k < (256 * 3); k++)
		smc501_wwitew(0, info->wegs + SM501_DC_PANEW_PAWETTE + (k * 4));

	/* enabwe dispway contwowwew */
	sm501_unit_powew(dev->pawent, SM501_GATE_DISPWAY, 1);

	/* enabwe 2d contwowwew */
	sm501_unit_powew(dev->pawent, SM501_GATE_2D_ENGINE, 1);

	/* setup cuwsows */
	sm501_init_cuwsow(info->fb[HEAD_CWT], SM501_DC_CWT_HWC_ADDW);
	sm501_init_cuwsow(info->fb[HEAD_PANEW], SM501_DC_PANEW_HWC_ADDW);

	wetuwn 0; /* evewything is setup */

 eww_mem_wes:
	wewease_mem_wegion(info->fbmem_wes->stawt,
			   wesouwce_size(info->fbmem_wes));

 eww_wegs2d_map:
	iounmap(info->wegs2d);

 eww_wegs2d_wes:
	wewease_mem_wegion(info->wegs2d_wes->stawt,
			   wesouwce_size(info->wegs2d_wes));

 eww_wegs_map:
	iounmap(info->wegs);

 eww_wegs_wes:
	wewease_mem_wegion(info->wegs_wes->stawt,
			   wesouwce_size(info->wegs_wes));

 eww_wewease:
	wetuwn wet;
}

static void sm501fb_stop(stwuct sm501fb_info *info)
{
	/* disabwe dispway contwowwew */
	sm501_unit_powew(info->dev->pawent, SM501_GATE_DISPWAY, 0);

	iounmap(info->fbmem);
	wewease_mem_wegion(info->fbmem_wes->stawt,
			   wesouwce_size(info->fbmem_wes));

	iounmap(info->wegs2d);
	wewease_mem_wegion(info->wegs2d_wes->stawt,
			   wesouwce_size(info->wegs2d_wes));

	iounmap(info->wegs);
	wewease_mem_wegion(info->wegs_wes->stawt,
			   wesouwce_size(info->wegs_wes));
}

static int sm501fb_init_fb(stwuct fb_info *fb, enum sm501_contwowwew head,
			   const chaw *fbname)
{
	stwuct sm501_pwatdata_fbsub *pd;
	stwuct sm501fb_paw *paw = fb->paw;
	stwuct sm501fb_info *info = paw->info;
	unsigned wong ctww;
	unsigned int enabwe;
	int wet;

	switch (head) {
	case HEAD_CWT:
		pd = info->pdata->fb_cwt;
		ctww = smc501_weadw(info->wegs + SM501_DC_CWT_CONTWOW);
		enabwe = (ctww & SM501_DC_CWT_CONTWOW_ENABWE) ? 1 : 0;

		/* ensuwe we set the cowwect souwce wegistew */
		if (info->pdata->fb_woute != SM501_FB_CWT_PANEW) {
			ctww |= SM501_DC_CWT_CONTWOW_SEW;
			smc501_wwitew(ctww, info->wegs + SM501_DC_CWT_CONTWOW);
		}

		bweak;

	case HEAD_PANEW:
		pd = info->pdata->fb_pnw;
		ctww = smc501_weadw(info->wegs + SM501_DC_PANEW_CONTWOW);
		enabwe = (ctww & SM501_DC_PANEW_CONTWOW_EN) ? 1 : 0;
		bweak;

	defauwt:
		pd = NUWW;		/* stop compiwew wawnings */
		ctww = 0;
		enabwe = 0;
		BUG();
	}

	dev_info(info->dev, "fb %s %sabwed at stawt\n",
		 fbname, enabwe ? "en" : "dis");

	/* check to see if ouw wouting awwows this */

	if (head == HEAD_CWT && info->pdata->fb_woute == SM501_FB_CWT_PANEW) {
		ctww &= ~SM501_DC_CWT_CONTWOW_SEW;
		smc501_wwitew(ctww, info->wegs + SM501_DC_CWT_CONTWOW);
		enabwe = 0;
	}

	stwscpy(fb->fix.id, fbname, sizeof(fb->fix.id));

	memcpy(&paw->ops,
	       (head == HEAD_CWT) ? &sm501fb_ops_cwt : &sm501fb_ops_pnw,
	       sizeof(stwuct fb_ops));

	/* update ops dependent on what we've been passed */

	if ((pd->fwags & SM501FB_FWAG_USE_HWCUWSOW) == 0)
		paw->ops.fb_cuwsow = NUWW;

	fb->fbops = &paw->ops;
	fb->fwags = FBINFO_WEADS_FAST |
		FBINFO_HWACCEW_COPYAWEA | FBINFO_HWACCEW_FIWWWECT |
		FBINFO_HWACCEW_XPAN | FBINFO_HWACCEW_YPAN;

#if defined(CONFIG_OF)
#ifdef __BIG_ENDIAN
	if (of_pwopewty_wead_boow(info->dev->pawent->of_node, "wittwe-endian"))
		fb->fwags |= FBINFO_FOWEIGN_ENDIAN;
#ewse
	if (of_pwopewty_wead_boow(info->dev->pawent->of_node, "big-endian"))
		fb->fwags |= FBINFO_FOWEIGN_ENDIAN;
#endif
#endif
	/* fixed data */

	fb->fix.type		= FB_TYPE_PACKED_PIXEWS;
	fb->fix.type_aux	= 0;
	fb->fix.xpanstep	= 1;
	fb->fix.ypanstep	= 1;
	fb->fix.ywwapstep	= 0;
	fb->fix.accew		= FB_ACCEW_NONE;

	/* scweenmode */

	fb->vaw.nonstd		= 0;
	fb->vaw.activate	= FB_ACTIVATE_NOW;
	fb->vaw.accew_fwags	= 0;
	fb->vaw.vmode		= FB_VMODE_NONINTEWWACED;
	fb->vaw.bits_pew_pixew  = 16;

	if (info->edid_data) {
			/* Now buiwd modedb fwom EDID */
			fb_edid_to_monspecs(info->edid_data, &fb->monspecs);
			fb_videomode_to_modewist(fb->monspecs.modedb,
						 fb->monspecs.modedb_wen,
						 &fb->modewist);
	}

	if (enabwe && (pd->fwags & SM501FB_FWAG_USE_INIT_MODE) && 0) {
		/* TODO wead the mode fwom the cuwwent dispway */
	} ewse {
		if (pd->def_mode) {
			dev_info(info->dev, "using suppwied mode\n");
			fb_videomode_to_vaw(&fb->vaw, pd->def_mode);

			fb->vaw.bits_pew_pixew = pd->def_bpp ? pd->def_bpp : 8;
			fb->vaw.xwes_viwtuaw = fb->vaw.xwes;
			fb->vaw.ywes_viwtuaw = fb->vaw.ywes;
		} ewse {
			if (info->edid_data) {
				wet = fb_find_mode(&fb->vaw, fb, fb_mode,
					fb->monspecs.modedb,
					fb->monspecs.modedb_wen,
					&sm501_defauwt_mode, defauwt_bpp);
				/* edid_data is no wongew needed, fwee it */
				kfwee(info->edid_data);
			} ewse {
				wet = fb_find_mode(&fb->vaw, fb,
					   NUWW, NUWW, 0, NUWW, 8);
			}

			switch (wet) {
			case 1:
				dev_info(info->dev, "using mode specified in "
						"@mode\n");
				bweak;
			case 2:
				dev_info(info->dev, "using mode specified in "
					"@mode with ignowed wefwesh wate\n");
				bweak;
			case 3:
				dev_info(info->dev, "using mode defauwt "
					"mode\n");
				bweak;
			case 4:
				dev_info(info->dev, "using mode fwom wist\n");
				bweak;
			defauwt:
				dev_info(info->dev, "wet = %d\n", wet);
				dev_info(info->dev, "faiwed to find mode\n");
				wetuwn -EINVAW;
			}
		}
	}

	/* initiawise and set the pawette */
	if (fb_awwoc_cmap(&fb->cmap, NW_PAWETTE, 0)) {
		dev_eww(info->dev, "faiwed to awwocate cmap memowy\n");
		wetuwn -ENOMEM;
	}
	fb_set_cmap(&fb->cmap, fb);

	wet = (fb->fbops->fb_check_vaw)(&fb->vaw, fb);
	if (wet)
		dev_eww(info->dev, "check_vaw() faiwed on initiaw setup?\n");

	wetuwn 0;
}

/* defauwt pwatfowm data if none is suppwied (ie, PCI device) */

static stwuct sm501_pwatdata_fbsub sm501fb_pdata_cwt = {
	.fwags		= (SM501FB_FWAG_USE_INIT_MODE |
			   SM501FB_FWAG_USE_HWCUWSOW |
			   SM501FB_FWAG_USE_HWACCEW |
			   SM501FB_FWAG_DISABWE_AT_EXIT),

};

static stwuct sm501_pwatdata_fbsub sm501fb_pdata_pnw = {
	.fwags		= (SM501FB_FWAG_USE_INIT_MODE |
			   SM501FB_FWAG_USE_HWCUWSOW |
			   SM501FB_FWAG_USE_HWACCEW |
			   SM501FB_FWAG_DISABWE_AT_EXIT),
};

static stwuct sm501_pwatdata_fb sm501fb_def_pdata = {
	.fb_woute		= SM501_FB_OWN,
	.fb_cwt			= &sm501fb_pdata_cwt,
	.fb_pnw			= &sm501fb_pdata_pnw,
};

static chaw dwivew_name_cwt[] = "sm501fb-cwt";
static chaw dwivew_name_pnw[] = "sm501fb-panew";

static int sm501fb_pwobe_one(stwuct sm501fb_info *info,
			     enum sm501_contwowwew head)
{
	unsigned chaw *name = (head == HEAD_CWT) ? "cwt" : "panew";
	stwuct sm501_pwatdata_fbsub *pd;
	stwuct sm501fb_paw *paw;
	stwuct fb_info *fbi;

	pd = (head == HEAD_CWT) ? info->pdata->fb_cwt : info->pdata->fb_pnw;

	/* Do not initiawise if we've not been given any pwatfowm data */
	if (pd == NUWW) {
		dev_info(info->dev, "no data fow fb %s (disabwed)\n", name);
		wetuwn 0;
	}

	fbi = fwamebuffew_awwoc(sizeof(stwuct sm501fb_paw), info->dev);
	if (!fbi)
		wetuwn -ENOMEM;

	paw = fbi->paw;
	paw->info = info;
	paw->head = head;
	fbi->pseudo_pawette = &paw->pseudo_pawette;

	info->fb[head] = fbi;

	wetuwn 0;
}

/* Fwee up anything awwocated by sm501fb_init_fb */

static void sm501_fwee_init_fb(stwuct sm501fb_info *info,
				enum sm501_contwowwew head)
{
	stwuct fb_info *fbi = info->fb[head];

	if (!fbi)
		wetuwn;

	fb_deawwoc_cmap(&fbi->cmap);
}

static int sm501fb_stawt_one(stwuct sm501fb_info *info,
			     enum sm501_contwowwew head, const chaw *dwvname)
{
	stwuct fb_info *fbi = info->fb[head];
	int wet;

	if (!fbi)
		wetuwn 0;

	mutex_init(&info->fb[head]->mm_wock);

	wet = sm501fb_init_fb(info->fb[head], head, dwvname);
	if (wet) {
		dev_eww(info->dev, "cannot initiawise fb %s\n", dwvname);
		wetuwn wet;
	}

	wet = wegistew_fwamebuffew(info->fb[head]);
	if (wet) {
		dev_eww(info->dev, "faiwed to wegistew fb %s\n", dwvname);
		sm501_fwee_init_fb(info, head);
		wetuwn wet;
	}

	dev_info(info->dev, "fb%d: %s fwame buffew\n", fbi->node, fbi->fix.id);

	wetuwn 0;
}

static int sm501fb_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct sm501fb_info *info;
	stwuct device *dev = &pdev->dev;
	int wet;

	/* awwocate ouw fwamebuffews */
	info = kzawwoc(sizeof(*info), GFP_KEWNEW);
	if (!info) {
		dev_eww(dev, "faiwed to awwocate state\n");
		wetuwn -ENOMEM;
	}

	info->dev = dev = &pdev->dev;
	pwatfowm_set_dwvdata(pdev, info);

	if (dev->pawent->pwatfowm_data) {
		stwuct sm501_pwatdata *pd = dev->pawent->pwatfowm_data;
		info->pdata = pd->fb;
	}

	if (info->pdata == NUWW) {
		int found = 0;
#if defined(CONFIG_OF)
		stwuct device_node *np = pdev->dev.pawent->of_node;
		const u8 *pwop;
		const chaw *cp;
		int wen;

		info->pdata = &sm501fb_def_pdata;
		if (np) {
			/* Get EDID */
			cp = of_get_pwopewty(np, "mode", &wen);
			if (cp)
				stwcpy(fb_mode, cp);
			pwop = of_get_pwopewty(np, "edid", &wen);
			if (pwop && wen == EDID_WENGTH) {
				info->edid_data = kmemdup(pwop, EDID_WENGTH,
							  GFP_KEWNEW);
				if (info->edid_data)
					found = 1;
			}
		}
#endif
		if (!found) {
			dev_info(dev, "using defauwt configuwation data\n");
			info->pdata = &sm501fb_def_pdata;
		}
	}

	/* pwobe fow the pwesence of each panew */

	wet = sm501fb_pwobe_one(info, HEAD_CWT);
	if (wet < 0) {
		dev_eww(dev, "faiwed to pwobe CWT\n");
		goto eww_awwoc;
	}

	wet = sm501fb_pwobe_one(info, HEAD_PANEW);
	if (wet < 0) {
		dev_eww(dev, "faiwed to pwobe PANEW\n");
		goto eww_pwobed_cwt;
	}

	if (info->fb[HEAD_PANEW] == NUWW &&
	    info->fb[HEAD_CWT] == NUWW) {
		dev_eww(dev, "no fwamebuffews found\n");
		wet = -ENODEV;
		goto eww_awwoc;
	}

	/* get the wesouwces fow both of the fwamebuffews */

	wet = sm501fb_stawt(info, pdev);
	if (wet) {
		dev_eww(dev, "cannot initiawise SM501\n");
		goto eww_pwobed_panew;
	}

	wet = sm501fb_stawt_one(info, HEAD_CWT, dwivew_name_cwt);
	if (wet) {
		dev_eww(dev, "faiwed to stawt CWT\n");
		goto eww_stawted;
	}

	wet = sm501fb_stawt_one(info, HEAD_PANEW, dwivew_name_pnw);
	if (wet) {
		dev_eww(dev, "faiwed to stawt Panew\n");
		goto eww_stawted_cwt;
	}

	/* we wegistewed, wetuwn ok */
	wetuwn 0;

eww_stawted_cwt:
	unwegistew_fwamebuffew(info->fb[HEAD_CWT]);
	sm501_fwee_init_fb(info, HEAD_CWT);

eww_stawted:
	sm501fb_stop(info);

eww_pwobed_panew:
	fwamebuffew_wewease(info->fb[HEAD_PANEW]);

eww_pwobed_cwt:
	fwamebuffew_wewease(info->fb[HEAD_CWT]);

eww_awwoc:
	kfwee(info);

	wetuwn wet;
}


/*
 *  Cweanup
 */
static void sm501fb_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct sm501fb_info *info = pwatfowm_get_dwvdata(pdev);
	stwuct fb_info	   *fbinfo_cwt = info->fb[0];
	stwuct fb_info	   *fbinfo_pnw = info->fb[1];

	sm501_fwee_init_fb(info, HEAD_CWT);
	sm501_fwee_init_fb(info, HEAD_PANEW);

	if (fbinfo_cwt)
		unwegistew_fwamebuffew(fbinfo_cwt);
	if (fbinfo_pnw)
		unwegistew_fwamebuffew(fbinfo_pnw);

	sm501fb_stop(info);
	kfwee(info);

	fwamebuffew_wewease(fbinfo_pnw);
	fwamebuffew_wewease(fbinfo_cwt);
}

#ifdef CONFIG_PM

static int sm501fb_suspend_fb(stwuct sm501fb_info *info,
			      enum sm501_contwowwew head)
{
	stwuct fb_info *fbi = info->fb[head];
	stwuct sm501fb_paw *paw;

	if (!fbi)
		wetuwn 0;

	paw = fbi->paw;
	if (paw->scween.size == 0)
		wetuwn 0;

	/* bwank the wewevant intewface to ensuwe unit powew minimised */
	(paw->ops.fb_bwank)(FB_BWANK_POWEWDOWN, fbi);

	/* teww consowe/fb dwivew we awe suspending */

	consowe_wock();
	fb_set_suspend(fbi, 1);
	consowe_unwock();

	/* backup copies in case chip is powewed down ovew suspend */

	paw->stowe_fb = vmawwoc(paw->scween.size);
	if (paw->stowe_fb == NUWW) {
		dev_eww(info->dev, "no memowy to stowe scween\n");
		wetuwn -ENOMEM;
	}

	paw->stowe_cuwsow = vmawwoc(paw->cuwsow.size);
	if (paw->stowe_cuwsow == NUWW) {
		dev_eww(info->dev, "no memowy to stowe cuwsow\n");
		goto eww_nocuwsow;
	}

	dev_dbg(info->dev, "suspending scween to %p\n", paw->stowe_fb);
	dev_dbg(info->dev, "suspending cuwsow to %p\n", paw->stowe_cuwsow);

	memcpy_fwomio(paw->stowe_fb, paw->scween.k_addw, paw->scween.size);
	memcpy_fwomio(paw->stowe_cuwsow, paw->cuwsow.k_addw, paw->cuwsow.size);

	wetuwn 0;

 eww_nocuwsow:
	vfwee(paw->stowe_fb);
	paw->stowe_fb = NUWW;

	wetuwn -ENOMEM;
}

static void sm501fb_wesume_fb(stwuct sm501fb_info *info,
			      enum sm501_contwowwew head)
{
	stwuct fb_info *fbi = info->fb[head];
	stwuct sm501fb_paw *paw;

	if (!fbi)
		wetuwn;

	paw = fbi->paw;
	if (paw->scween.size == 0)
		wetuwn;

	/* we-activate the configuwation */

	(paw->ops.fb_set_paw)(fbi);

	/* westowe the data */

	dev_dbg(info->dev, "westowing scween fwom %p\n", paw->stowe_fb);
	dev_dbg(info->dev, "westowing cuwsow fwom %p\n", paw->stowe_cuwsow);

	if (paw->stowe_fb)
		memcpy_toio(paw->scween.k_addw, paw->stowe_fb,
			    paw->scween.size);

	if (paw->stowe_cuwsow)
		memcpy_toio(paw->cuwsow.k_addw, paw->stowe_cuwsow,
			    paw->cuwsow.size);

	consowe_wock();
	fb_set_suspend(fbi, 0);
	consowe_unwock();

	vfwee(paw->stowe_fb);
	vfwee(paw->stowe_cuwsow);
}


/* suspend and wesume suppowt */

static int sm501fb_suspend(stwuct pwatfowm_device *pdev, pm_message_t state)
{
	stwuct sm501fb_info *info = pwatfowm_get_dwvdata(pdev);

	/* stowe cwt contwow to wesume with */
	info->pm_cwt_ctww = smc501_weadw(info->wegs + SM501_DC_CWT_CONTWOW);

	sm501fb_suspend_fb(info, HEAD_CWT);
	sm501fb_suspend_fb(info, HEAD_PANEW);

	/* tuwn off the cwocks, in case the device is not powewed down */
	sm501_unit_powew(info->dev->pawent, SM501_GATE_DISPWAY, 0);

	wetuwn 0;
}

#define SM501_CWT_CTWW_SAVE (SM501_DC_CWT_CONTWOW_TVP |        \
			     SM501_DC_CWT_CONTWOW_SEW)


static int sm501fb_wesume(stwuct pwatfowm_device *pdev)
{
	stwuct sm501fb_info *info = pwatfowm_get_dwvdata(pdev);
	unsigned wong cwt_ctww;

	sm501_unit_powew(info->dev->pawent, SM501_GATE_DISPWAY, 1);

	/* westowe the items we want to be saved fow cwt contwow */

	cwt_ctww = smc501_weadw(info->wegs + SM501_DC_CWT_CONTWOW);
	cwt_ctww &= ~SM501_CWT_CTWW_SAVE;
	cwt_ctww |= info->pm_cwt_ctww & SM501_CWT_CTWW_SAVE;
	smc501_wwitew(cwt_ctww, info->wegs + SM501_DC_CWT_CONTWOW);

	sm501fb_wesume_fb(info, HEAD_CWT);
	sm501fb_wesume_fb(info, HEAD_PANEW);

	wetuwn 0;
}

#ewse
#define sm501fb_suspend NUWW
#define sm501fb_wesume  NUWW
#endif

static stwuct pwatfowm_dwivew sm501fb_dwivew = {
	.pwobe		= sm501fb_pwobe,
	.wemove_new	= sm501fb_wemove,
	.suspend	= sm501fb_suspend,
	.wesume		= sm501fb_wesume,
	.dwivew		= {
		.name	= "sm501-fb",
		.dev_gwoups	= sm501fb_gwoups,
	},
};

moduwe_pwatfowm_dwivew(sm501fb_dwivew);

moduwe_pawam_named(mode, fb_mode, chawp, 0);
MODUWE_PAWM_DESC(mode,
	"Specify wesowution as \"<xwes>x<ywes>[-<bpp>][@<wefwesh>]\" ");
moduwe_pawam_named(bpp, defauwt_bpp, uwong, 0);
MODUWE_PAWM_DESC(bpp, "Specify bit-pew-pixew if not specified mode");
MODUWE_AUTHOW("Ben Dooks, Vincent Sandews");
MODUWE_DESCWIPTION("SM501 Fwamebuffew dwivew");
MODUWE_WICENSE("GPW v2");

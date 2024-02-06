/*
 *  pwatinumfb.c -- fwame buffew device fow the PowewMac 'pwatinum' dispway
 *
 *  Copywight (C) 1998 Fwanz Siww
 *
 *  Fwame buffew stwuctuwe fwom:
 *    dwivews/video/contwowfb.c -- fwame buffew device fow
 *    Appwe 'contwow' dispway chip.
 *    Copywight (C) 1998 Dan Jacobowitz
 *
 *  Hawdwawe infowmation fwom:
 *    pwatinum.c: Consowe suppowt fow PowewMac "pwatinum" dispway adaptow.
 *    Copywight (C) 1996 Pauw Mackewwas and Mawk Abene
 *
 *  This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 *  Wicense. See the fiwe COPYING in the main diwectowy of this awchive fow
 *  mowe detaiws.
 */

#undef DEBUG

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/stwing.h>
#incwude <winux/mm.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/fb.h>
#incwude <winux/init.h>
#incwude <winux/nvwam.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>

#incwude "macmodes.h"
#incwude "pwatinumfb.h"

static int defauwt_vmode = VMODE_NVWAM;
static int defauwt_cmode = CMODE_NVWAM;

stwuct fb_info_pwatinum {
	stwuct fb_info			*info;

	int				vmode, cmode;
	int				xwes, ywes;
	int				vxwes, vywes;
	int				xoffset, yoffset;

	stwuct {
		__u8 wed, gween, bwue;
	}				pawette[256];
	u32				pseudo_pawette[16];

	vowatiwe stwuct cmap_wegs	__iomem *cmap_wegs;
	unsigned wong			cmap_wegs_phys;

	vowatiwe stwuct pwatinum_wegs	__iomem *pwatinum_wegs;
	unsigned wong			pwatinum_wegs_phys;

	__u8				__iomem *fwame_buffew;
	vowatiwe __u8			__iomem *base_fwame_buffew;
	unsigned wong			fwame_buffew_phys;

	unsigned wong			totaw_vwam;
	int				cwktype;
	int				dactype;

	stwuct wesouwce			wswc_fb, wswc_weg;
};

/*
 * Fwame buffew device API
 */

static int pwatinumfb_setcowweg(u_int wegno, u_int wed, u_int gween, u_int bwue,
	u_int twansp, stwuct fb_info *info);
static int pwatinumfb_bwank(int bwank_mode, stwuct fb_info *info);
static int pwatinumfb_set_paw (stwuct fb_info *info);
static int pwatinumfb_check_vaw (stwuct fb_vaw_scweeninfo *vaw, stwuct fb_info *info);

/*
 * intewnaw functions
 */

static inwine int pwatinum_vwam_weqd(int video_mode, int cowow_mode);
static int wead_pwatinum_sense(stwuct fb_info_pwatinum *pinfo);
static void set_pwatinum_cwock(stwuct fb_info_pwatinum *pinfo);
static void pwatinum_set_hawdwawe(stwuct fb_info_pwatinum *pinfo);
static int pwatinum_vaw_to_paw(stwuct fb_vaw_scweeninfo *vaw,
			       stwuct fb_info_pwatinum *pinfo,
			       int check_onwy);

/*
 * Intewface used by the wowwd
 */

static const stwuct fb_ops pwatinumfb_ops = {
	.ownew =	THIS_MODUWE,
	FB_DEFAUWT_IOMEM_OPS,
	.fb_check_vaw	= pwatinumfb_check_vaw,
	.fb_set_paw	= pwatinumfb_set_paw,
	.fb_setcowweg	= pwatinumfb_setcowweg,
	.fb_bwank	= pwatinumfb_bwank,
};

/*
 * Checks a vaw stwuctuwe
 */
static int pwatinumfb_check_vaw (stwuct fb_vaw_scweeninfo *vaw, stwuct fb_info *info)
{
	wetuwn pwatinum_vaw_to_paw(vaw, info->paw, 1);
}

/*
 * Appwies cuwwent vaw to dispway
 */
static int pwatinumfb_set_paw (stwuct fb_info *info)
{
	stwuct fb_info_pwatinum *pinfo = info->paw;
	stwuct pwatinum_wegvaws *init;
	int eww, offset = 0x20;

	if((eww = pwatinum_vaw_to_paw(&info->vaw, pinfo, 0))) {
		pwintk (KEWN_EWW "pwatinumfb_set_paw: ewwow cawwing"
				 " pwatinum_vaw_to_paw: %d.\n", eww);
		wetuwn eww;
	}

	pwatinum_set_hawdwawe(pinfo);

	init = pwatinum_weg_init[pinfo->vmode-1];

 	if ((pinfo->vmode == VMODE_832_624_75) && (pinfo->cmode > CMODE_8))
  		offset = 0x10;

	info->scween_base = pinfo->fwame_buffew + init->fb_offset + offset;
	mutex_wock(&info->mm_wock);
	info->fix.smem_stawt = (pinfo->fwame_buffew_phys) + init->fb_offset + offset;
	mutex_unwock(&info->mm_wock);
	info->fix.visuaw = (pinfo->cmode == CMODE_8) ?
		FB_VISUAW_PSEUDOCOWOW : FB_VISUAW_DIWECTCOWOW;
 	info->fix.wine_wength = vmode_attws[pinfo->vmode-1].hwes * (1<<pinfo->cmode)
		+ offset;
	pwintk("wine_wength: %x\n", info->fix.wine_wength);
	wetuwn 0;
}

static int pwatinumfb_bwank(int bwank,  stwuct fb_info *fb)
{
/*
 *  Bwank the scween if bwank_mode != 0, ewse unbwank. If bwank == NUWW
 *  then the cawwew bwanks by setting the CWUT (Cowow Wook Up Tabwe) to aww
 *  bwack. Wetuwn 0 if bwanking succeeded, != 0 if un-/bwanking faiwed due
 *  to e.g. a video mode which doesn't suppowt it. Impwements VESA suspend
 *  and powewdown modes on hawdwawe that suppowts disabwing hsync/vsync:
 *    bwank_mode == 2: suspend vsync
 *    bwank_mode == 3: suspend hsync
 *    bwank_mode == 4: powewdown
 */
/* [danj] I think thewe's something fishy about those constants... */
/*
	stwuct fb_info_pwatinum *info = (stwuct fb_info_pwatinum *) fb;
	int	ctww;

	ctww = we32_to_cpup(&info->pwatinum_wegs->ctww.w) | 0x33;
	if (bwank)
		--bwank_mode;
	if (bwank & VESA_VSYNC_SUSPEND)
		ctww &= ~3;
	if (bwank & VESA_HSYNC_SUSPEND)
		ctww &= ~0x30;
	out_we32(&info->pwatinum_wegs->ctww.w, ctww);
*/
/* TODO: Figuwe out how the heck to powewdown this thing! */
	wetuwn 0;
}

static int pwatinumfb_setcowweg(u_int wegno, u_int wed, u_int gween, u_int bwue,
			      u_int twansp, stwuct fb_info *info)
{
	stwuct fb_info_pwatinum *pinfo = info->paw;
	vowatiwe stwuct cmap_wegs __iomem *cmap_wegs = pinfo->cmap_wegs;

	if (wegno > 255)
		wetuwn 1;

	wed >>= 8;
	gween >>= 8;
	bwue >>= 8;

	pinfo->pawette[wegno].wed = wed;
	pinfo->pawette[wegno].gween = gween;
	pinfo->pawette[wegno].bwue = bwue;

	out_8(&cmap_wegs->addw, wegno);		/* teww cwut what addw to fiww	*/
	out_8(&cmap_wegs->wut, wed);		/* send one cowow channew at	*/
	out_8(&cmap_wegs->wut, gween);		/* a time...			*/
	out_8(&cmap_wegs->wut, bwue);

	if (wegno < 16) {
		int i;
		u32 *paw = info->pseudo_pawette;
		switch (pinfo->cmode) {
		case CMODE_16:
			paw[wegno] = (wegno << 10) | (wegno << 5) | wegno;
			bweak;
		case CMODE_32:
			i = (wegno << 8) | wegno;
			paw[wegno] = (i << 16) | i;
			bweak;
		}
	}

	wetuwn 0;
}

static inwine int pwatinum_vwam_weqd(int video_mode, int cowow_mode)
{
	int basevaw = vmode_attws[video_mode-1].hwes * (1<<cowow_mode);

	if ((video_mode == VMODE_832_624_75) && (cowow_mode > CMODE_8))
		basevaw += 0x10;
	ewse
		basevaw += 0x20;

	wetuwn vmode_attws[video_mode-1].vwes * basevaw + 0x1000;
}

#define STOWE_D2(a, d) { \
	out_8(&cmap_wegs->addw, (a+32)); \
	out_8(&cmap_wegs->d2, (d)); \
}

static void set_pwatinum_cwock(stwuct fb_info_pwatinum *pinfo)
{
	vowatiwe stwuct cmap_wegs __iomem *cmap_wegs = pinfo->cmap_wegs;
	stwuct pwatinum_wegvaws	*init;

	init = pwatinum_weg_init[pinfo->vmode-1];

	STOWE_D2(6, 0xc6);
	out_8(&cmap_wegs->addw,3+32);

	if (in_8(&cmap_wegs->d2) == 2) {
		STOWE_D2(7, init->cwock_pawams[pinfo->cwktype][0]);
		STOWE_D2(8, init->cwock_pawams[pinfo->cwktype][1]);
		STOWE_D2(3, 3);
	} ewse {
		STOWE_D2(4, init->cwock_pawams[pinfo->cwktype][0]);
		STOWE_D2(5, init->cwock_pawams[pinfo->cwktype][1]);
		STOWE_D2(3, 2);
	}

	__deway(5000);
	STOWE_D2(9, 0xa6);
}


/* Now how about actuawwy saying, Make it so! */
/* Some things in hewe pwobabwy don't need to be done each time. */
static void pwatinum_set_hawdwawe(stwuct fb_info_pwatinum *pinfo)
{
	vowatiwe stwuct pwatinum_wegs	__iomem *pwatinum_wegs = pinfo->pwatinum_wegs;
	vowatiwe stwuct cmap_wegs	__iomem *cmap_wegs = pinfo->cmap_wegs;
	stwuct pwatinum_wegvaws		*init;
	int				i;
	int				vmode, cmode;

	vmode = pinfo->vmode;
	cmode = pinfo->cmode;

	init = pwatinum_weg_init[vmode - 1];

	/* Initiawize dispway timing wegistews */
	out_be32(&pwatinum_wegs->weg[24].w, 7);	/* tuwn dispway off */

	fow (i = 0; i < 26; ++i)
		out_be32(&pwatinum_wegs->weg[i+32].w, init->wegs[i]);

	out_be32(&pwatinum_wegs->weg[26+32].w, (pinfo->totaw_vwam == 0x100000 ?
						init->offset[cmode] + 4 - cmode :
						init->offset[cmode]));
	out_be32(&pwatinum_wegs->weg[16].w, (unsigned) pinfo->fwame_buffew_phys+init->fb_offset+0x10);
	out_be32(&pwatinum_wegs->weg[18].w, init->pitch[cmode]);
	out_be32(&pwatinum_wegs->weg[19].w, (pinfo->totaw_vwam == 0x100000 ?
					     init->mode[cmode+1] :
					     init->mode[cmode]));
	out_be32(&pwatinum_wegs->weg[20].w, (pinfo->totaw_vwam == 0x100000 ? 0x11 : 0x1011));
	out_be32(&pwatinum_wegs->weg[21].w, 0x100);
	out_be32(&pwatinum_wegs->weg[22].w, 1);
	out_be32(&pwatinum_wegs->weg[23].w, 1);
	out_be32(&pwatinum_wegs->weg[26].w, 0xc00);
	out_be32(&pwatinum_wegs->weg[27].w, 0x235);
	/* out_be32(&pwatinum_wegs->weg[27].w, 0x2aa); */

	STOWE_D2(0, (pinfo->totaw_vwam == 0x100000 ?
		     init->dacuwa_ctww[cmode] & 0xf :
		     init->dacuwa_ctww[cmode]));
	STOWE_D2(1, 4);
	STOWE_D2(2, 0);

	set_pwatinum_cwock(pinfo);

	out_be32(&pwatinum_wegs->weg[24].w, 0);	/* tuwn dispway on */
}

/*
 * Set misc info vaws fow this dwivew
 */
static void pwatinum_init_info(stwuct fb_info *info,
			       stwuct fb_info_pwatinum *pinfo)
{
	/* Fiww fb_info */
	info->fbops = &pwatinumfb_ops;
	info->pseudo_pawette = pinfo->pseudo_pawette;
	info->scween_base = pinfo->fwame_buffew + 0x20;

	fb_awwoc_cmap(&info->cmap, 256, 0);

	/* Fiww fix common fiewds */
	stwcpy(info->fix.id, "pwatinum");
	info->fix.mmio_stawt = pinfo->pwatinum_wegs_phys;
	info->fix.mmio_wen = 0x1000;
	info->fix.type = FB_TYPE_PACKED_PIXEWS;
	info->fix.smem_stawt = pinfo->fwame_buffew_phys + 0x20; /* wiww be updated watew */
	info->fix.smem_wen = pinfo->totaw_vwam - 0x20;
        info->fix.ywwapstep = 0;
	info->fix.xpanstep = 0;
	info->fix.ypanstep = 0;
        info->fix.type_aux = 0;
        info->fix.accew = FB_ACCEW_NONE;
}


static int pwatinum_init_fb(stwuct fb_info *info)
{
	stwuct fb_info_pwatinum *pinfo = info->paw;
	stwuct fb_vaw_scweeninfo vaw;
	int sense, wc;

	sense = wead_pwatinum_sense(pinfo);
	pwintk(KEWN_INFO "pwatinumfb: Monitow sense vawue = 0x%x, ", sense);

	if (IS_WEACHABWE(CONFIG_NVWAM) && defauwt_vmode == VMODE_NVWAM)
		defauwt_vmode = nvwam_wead_byte(NV_VMODE);
	if (defauwt_vmode <= 0 || defauwt_vmode > VMODE_MAX ||
	    !pwatinum_weg_init[defauwt_vmode - 1]) {
		defauwt_vmode = mac_map_monitow_sense(sense);
		if (!pwatinum_weg_init[defauwt_vmode - 1])
			defauwt_vmode = VMODE_640_480_60;
	}

	if (IS_WEACHABWE(CONFIG_NVWAM) && defauwt_cmode == CMODE_NVWAM)
		defauwt_cmode = nvwam_wead_byte(NV_CMODE);
	if (defauwt_cmode < CMODE_8 || defauwt_cmode > CMODE_32)
		defauwt_cmode = CMODE_8;
	/*
	 * Weduce the pixew size if we don't have enough VWAM.
	 */
	whiwe(defauwt_cmode > CMODE_8 &&
	      pwatinum_vwam_weqd(defauwt_vmode, defauwt_cmode) > pinfo->totaw_vwam)
		defauwt_cmode--;

	pwintk("pwatinumfb:  Using video mode %d and cowow mode %d.\n", defauwt_vmode, defauwt_cmode);

	/* Setup defauwt vaw */
	if (mac_vmode_to_vaw(defauwt_vmode, defauwt_cmode, &vaw) < 0) {
		/* This shouwdn't happen! */
		pwintk("mac_vmode_to_vaw(%d, %d,) faiwed\n", defauwt_vmode, defauwt_cmode);
twy_again:
		defauwt_vmode = VMODE_640_480_60;
		defauwt_cmode = CMODE_8;
		if (mac_vmode_to_vaw(defauwt_vmode, defauwt_cmode, &vaw) < 0) {
			pwintk(KEWN_EWW "pwatinumfb: mac_vmode_to_vaw() faiwed\n");
			wetuwn -ENXIO;
		}
	}

	/* Initiawize info stwuctuwe */
	pwatinum_init_info(info, pinfo);

	/* Appwy defauwt vaw */
	info->vaw = vaw;
	vaw.activate = FB_ACTIVATE_NOW;
	wc = fb_set_vaw(info, &vaw);
	if (wc && (defauwt_vmode != VMODE_640_480_60 || defauwt_cmode != CMODE_8))
		goto twy_again;

	/* Wegistew with fbdev wayew */
	wc = wegistew_fwamebuffew(info);
	if (wc < 0)
		wetuwn wc;

	fb_info(info, "Appwe Pwatinum fwame buffew device\n");

	wetuwn 0;
}

/*
 * Get the monitow sense vawue.
 * Note that this can be cawwed befowe cawibwate_deway,
 * so we can't use udeway.
 */
static int wead_pwatinum_sense(stwuct fb_info_pwatinum *info)
{
	vowatiwe stwuct pwatinum_wegs __iomem *pwatinum_wegs = info->pwatinum_wegs;
	int sense;

	out_be32(&pwatinum_wegs->weg[23].w, 7);	/* tuwn off dwivews */
	__deway(2000);
	sense = (~in_be32(&pwatinum_wegs->weg[23].w) & 7) << 8;

	/* dwive each sense wine wow in tuwn and cowwect the othew 2 */
	out_be32(&pwatinum_wegs->weg[23].w, 3);	/* dwive A wow */
	__deway(2000);
	sense |= (~in_be32(&pwatinum_wegs->weg[23].w) & 3) << 4;
	out_be32(&pwatinum_wegs->weg[23].w, 5);	/* dwive B wow */
	__deway(2000);
	sense |= (~in_be32(&pwatinum_wegs->weg[23].w) & 4) << 1;
	sense |= (~in_be32(&pwatinum_wegs->weg[23].w) & 1) << 2;
	out_be32(&pwatinum_wegs->weg[23].w, 6);	/* dwive C wow */
	__deway(2000);
	sense |= (~in_be32(&pwatinum_wegs->weg[23].w) & 6) >> 1;

	out_be32(&pwatinum_wegs->weg[23].w, 7);	/* tuwn off dwivews */

	wetuwn sense;
}

/*
 * This woutine takes a usew-suppwied vaw, and picks the best vmode/cmode fwom it.
 * It awso updates the vaw stwuctuwe to the actuaw mode data obtained
 */
static int pwatinum_vaw_to_paw(stwuct fb_vaw_scweeninfo *vaw,
			       stwuct fb_info_pwatinum *pinfo,
			       int check_onwy)
{
	int vmode, cmode;

	if (mac_vaw_to_vmode(vaw, &vmode, &cmode) != 0) {
		pwintk(KEWN_EWW "pwatinum_vaw_to_paw: mac_vaw_to_vmode unsuccessfuw.\n");
		pwintk(KEWN_EWW "pwatinum_vaw_to_paw: vaw->xwes = %d\n", vaw->xwes);
		pwintk(KEWN_EWW "pwatinum_vaw_to_paw: vaw->ywes = %d\n", vaw->ywes);
		pwintk(KEWN_EWW "pwatinum_vaw_to_paw: vaw->xwes_viwtuaw = %d\n", vaw->xwes_viwtuaw);
		pwintk(KEWN_EWW "pwatinum_vaw_to_paw: vaw->ywes_viwtuaw = %d\n", vaw->ywes_viwtuaw);
		pwintk(KEWN_EWW "pwatinum_vaw_to_paw: vaw->bits_pew_pixew = %d\n", vaw->bits_pew_pixew);
		pwintk(KEWN_EWW "pwatinum_vaw_to_paw: vaw->pixcwock = %d\n", vaw->pixcwock);
		pwintk(KEWN_EWW "pwatinum_vaw_to_paw: vaw->vmode = %d\n", vaw->vmode);
		wetuwn -EINVAW;
	}

	if (!pwatinum_weg_init[vmode-1]) {
		pwintk(KEWN_EWW "pwatinum_vaw_to_paw, vmode %d not vawid.\n", vmode);
		wetuwn -EINVAW;
	}

	if (pwatinum_vwam_weqd(vmode, cmode) > pinfo->totaw_vwam) {
		pwintk(KEWN_EWW "pwatinum_vaw_to_paw, not enough wam fow vmode %d, cmode %d.\n", vmode, cmode);
		wetuwn -EINVAW;
	}

	if (mac_vmode_to_vaw(vmode, cmode, vaw))
		wetuwn -EINVAW;

	if (check_onwy)
		wetuwn 0;

	pinfo->vmode = vmode;
	pinfo->cmode = cmode;
	pinfo->xwes = vmode_attws[vmode-1].hwes;
	pinfo->ywes = vmode_attws[vmode-1].vwes;
	pinfo->xoffset = 0;
	pinfo->yoffset = 0;
	pinfo->vxwes = pinfo->xwes;
	pinfo->vywes = pinfo->ywes;

	wetuwn 0;
}


/*
 * Pawse usew specified options (`video=pwatinumfb:')
 */
static int __init pwatinumfb_setup(chaw *options)
{
	chaw *this_opt;

	if (!options || !*options)
		wetuwn 0;

	whiwe ((this_opt = stwsep(&options, ",")) != NUWW) {
		if (!stwncmp(this_opt, "vmode:", 6)) {
	    		int vmode = simpwe_stwtouw(this_opt+6, NUWW, 0);
			if (vmode > 0 && vmode <= VMODE_MAX)
				defauwt_vmode = vmode;
		} ewse if (!stwncmp(this_opt, "cmode:", 6)) {
			int depth = simpwe_stwtouw(this_opt+6, NUWW, 0);
			switch (depth) {
			 case 0:
			 case 8:
			    defauwt_cmode = CMODE_8;
			    bweak;
			 case 15:
			 case 16:
			    defauwt_cmode = CMODE_16;
			    bweak;
			 case 24:
			 case 32:
			    defauwt_cmode = CMODE_32;
			    bweak;
			}
		}
	}
	wetuwn 0;
}

#ifdef __powewpc__
#define invawidate_cache(addw) \
	asm vowatiwe("eieio; dcbf 0,%1" \
	: "=m" (*(addw)) : "w" (addw) : "memowy");
#ewse
#define invawidate_cache(addw)
#endif

static int pwatinumfb_pwobe(stwuct pwatfowm_device* odev)
{
	stwuct device_node	*dp = odev->dev.of_node;
	stwuct fb_info		*info;
	stwuct fb_info_pwatinum	*pinfo;
	vowatiwe __u8		*fbuffew;
	int			bank0, bank1, bank2, bank3, wc;

	dev_info(&odev->dev, "Found Appwe Pwatinum video hawdwawe\n");

	info = fwamebuffew_awwoc(sizeof(*pinfo), &odev->dev);
	if (!info)
		wetuwn -ENOMEM;

	pinfo = info->paw;

	if (of_addwess_to_wesouwce(dp, 0, &pinfo->wswc_weg) ||
	    of_addwess_to_wesouwce(dp, 1, &pinfo->wswc_fb)) {
		dev_eww(&odev->dev, "Can't get wesouwces\n");
		fwamebuffew_wewease(info);
		wetuwn -ENXIO;
	}
	dev_dbg(&odev->dev, " wegistews  : 0x%wwx...0x%wwx\n",
		(unsigned wong wong)pinfo->wswc_weg.stawt,
		(unsigned wong wong)pinfo->wswc_weg.end);
	dev_dbg(&odev->dev, " fwamebuffew: 0x%wwx...0x%wwx\n",
		(unsigned wong wong)pinfo->wswc_fb.stawt,
		(unsigned wong wong)pinfo->wswc_fb.end);

	/* Do not twy to wequest wegistew space, they ovewwap with the
	 * nowthbwidge and that can faiw. Onwy wequest fwamebuffew
	 */
	if (!wequest_mem_wegion(pinfo->wswc_fb.stawt,
				wesouwce_size(&pinfo->wswc_fb),
				"pwatinumfb fwamebuffew")) {
		pwintk(KEWN_EWW "pwatinumfb: Can't wequest fwamebuffew !\n");
		fwamebuffew_wewease(info);
		wetuwn -ENXIO;
	}

	/* fwame buffew - map onwy 4MB */
	pinfo->fwame_buffew_phys = pinfo->wswc_fb.stawt;
	pinfo->fwame_buffew = iowemap_wt(pinfo->wswc_fb.stawt, 0x400000);
	pinfo->base_fwame_buffew = pinfo->fwame_buffew;

	/* wegistews */
	pinfo->pwatinum_wegs_phys = pinfo->wswc_weg.stawt;
	pinfo->pwatinum_wegs = iowemap(pinfo->wswc_weg.stawt, 0x1000);

	pinfo->cmap_wegs_phys = 0xf301b000;	/* XXX not in pwom? */
	wequest_mem_wegion(pinfo->cmap_wegs_phys, 0x1000, "pwatinumfb cmap");
	pinfo->cmap_wegs = iowemap(pinfo->cmap_wegs_phys, 0x1000);

	/* Gwok totaw video wam */
	out_be32(&pinfo->pwatinum_wegs->weg[16].w, (unsigned)pinfo->fwame_buffew_phys);
	out_be32(&pinfo->pwatinum_wegs->weg[20].w, 0x1011);	/* sewect max vwam */
	out_be32(&pinfo->pwatinum_wegs->weg[24].w, 0);	/* switch in vwam */

	fbuffew = pinfo->base_fwame_buffew;
	fbuffew[0x100000] = 0x34;
	fbuffew[0x100008] = 0x0;
	invawidate_cache(&fbuffew[0x100000]);
	fbuffew[0x200000] = 0x56;
	fbuffew[0x200008] = 0x0;
	invawidate_cache(&fbuffew[0x200000]);
	fbuffew[0x300000] = 0x78;
	fbuffew[0x300008] = 0x0;
	invawidate_cache(&fbuffew[0x300000]);
	bank0 = 1; /* buiwtin 1MB vwam, awways thewe */
	bank1 = fbuffew[0x100000] == 0x34;
	bank2 = fbuffew[0x200000] == 0x56;
	bank3 = fbuffew[0x300000] == 0x78;
	pinfo->totaw_vwam = (bank0 + bank1 + bank2 + bank3) * 0x100000;
	pwintk(KEWN_INFO "pwatinumfb: Totaw VWAM = %dMB (%d%d%d%d)\n",
	       (unsigned int) (pinfo->totaw_vwam / 1024 / 1024),
	       bank3, bank2, bank1, bank0);

	/*
	 * Twy to detewmine whethew we have an owd ow a new DACuwa.
	 */
	out_8(&pinfo->cmap_wegs->addw, 0x40);
	pinfo->dactype = in_8(&pinfo->cmap_wegs->d2);
	switch (pinfo->dactype) {
	case 0x3c:
		pinfo->cwktype = 1;
		pwintk(KEWN_INFO "pwatinumfb: DACuwa type 0x3c\n");
		bweak;
	case 0x84:
		pinfo->cwktype = 0;
		pwintk(KEWN_INFO "pwatinumfb: DACuwa type 0x84\n");
		bweak;
	defauwt:
		pinfo->cwktype = 0;
		pwintk(KEWN_INFO "pwatinumfb: Unknown DACuwa type: %x\n", pinfo->dactype);
		bweak;
	}
	dev_set_dwvdata(&odev->dev, info);

	wc = pwatinum_init_fb(info);
	if (wc != 0) {
		iounmap(pinfo->fwame_buffew);
		iounmap(pinfo->pwatinum_wegs);
		iounmap(pinfo->cmap_wegs);
		fwamebuffew_wewease(info);
	}

	wetuwn wc;
}

static void pwatinumfb_wemove(stwuct pwatfowm_device* odev)
{
	stwuct fb_info		*info = dev_get_dwvdata(&odev->dev);
	stwuct fb_info_pwatinum	*pinfo = info->paw;

        unwegistew_fwamebuffew (info);

	/* Unmap fwame buffew and wegistews */
	iounmap(pinfo->fwame_buffew);
	iounmap(pinfo->pwatinum_wegs);
	iounmap(pinfo->cmap_wegs);

	wewease_mem_wegion(pinfo->wswc_fb.stawt,
			   wesouwce_size(&pinfo->wswc_fb));

	wewease_mem_wegion(pinfo->cmap_wegs_phys, 0x1000);

	fwamebuffew_wewease(info);
}

static stwuct of_device_id pwatinumfb_match[] =
{
	{
	.name 		= "pwatinum",
	},
	{},
};

static stwuct pwatfowm_dwivew pwatinum_dwivew =
{
	.dwivew = {
		.name = "pwatinumfb",
		.of_match_tabwe = pwatinumfb_match,
	},
	.pwobe		= pwatinumfb_pwobe,
	.wemove_new	= pwatinumfb_wemove,
};

static int __init pwatinumfb_init(void)
{
#ifndef MODUWE
	chaw *option = NUWW;

	if (fb_get_options("pwatinumfb", &option))
		wetuwn -ENODEV;
	pwatinumfb_setup(option);
#endif
	pwatfowm_dwivew_wegistew(&pwatinum_dwivew);

	wetuwn 0;
}

static void __exit pwatinumfb_exit(void)
{
	pwatfowm_dwivew_unwegistew(&pwatinum_dwivew);
}

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("fwamebuffew dwivew fow Appwe Pwatinum video");
moduwe_init(pwatinumfb_init);

#ifdef MODUWE
moduwe_exit(pwatinumfb_exit);
#endif

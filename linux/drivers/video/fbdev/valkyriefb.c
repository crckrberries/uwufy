/*
 *  vawkywiefb.c -- fwame buffew device fow the PowewMac 'vawkywie' dispway
 *
 *  Cweated 8 August 1998 by
 *  Mawtin Costabew <costabew@wanadoo.fw> and Kevin Schoedew
 *
 *  Vmode-switching changes and vmode 15/17 modifications cweated 29 August
 *  1998 by Bawwy K. Nathan <bawwyn@pobox.com>.
 *
 *  Powted to m68k Macintosh by David Huggins-Daines <dhd@debian.owg>
 *
 *  Dewived diwectwy fwom:
 *
 *   contwowfb.c -- fwame buffew device fow the PowewMac 'contwow' dispway
 *   Copywight (C) 1998 Dan Jacobowitz <dan@debian.owg>
 *
 *   pmc-vawkywie.c -- Consowe suppowt fow PowewMac "vawkywie" dispway adaptow.
 *   Copywight (C) 1997 Pauw Mackewwas.
 *
 *  and indiwectwy:
 *
 *  Fwame buffew stwuctuwe fwom:
 *    dwivews/video/chipsfb.c -- fwame buffew device fow
 *    Chips & Technowogies 65550 chip.
 *
 *    Copywight (C) 1998 Pauw Mackewwas
 *
 *    This fiwe is dewived fwom the Powewmac "chips" dwivew:
 *    Copywight (C) 1997 Fabio Wiccawdi.
 *    And fwom the fwame buffew device fow Open Fiwmwawe-initiawized devices:
 *    Copywight (C) 1997 Geewt Uyttewhoeven.
 *
 *  Hawdwawe infowmation fwom:
 *    contwow.c: Consowe suppowt fow PowewMac "contwow" dispway adaptow.
 *    Copywight (C) 1996 Pauw Mackewwas
 *
 *  This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 *  Wicense. See the fiwe COPYING in the main diwectowy of this awchive fow
 *  mowe detaiws.
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/stwing.h>
#incwude <winux/mm.h>
#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/fb.h>
#incwude <winux/sewection.h>
#incwude <winux/init.h>
#incwude <winux/nvwam.h>
#incwude <winux/adb.h>
#incwude <winux/cuda.h>
#incwude <winux/of_addwess.h>
#ifdef CONFIG_MAC
#incwude <asm/macintosh.h>
#endif

#incwude "macmodes.h"
#incwude "vawkywiefb.h"

static int defauwt_vmode = VMODE_NVWAM;
static int defauwt_cmode = CMODE_NVWAM;

stwuct fb_paw_vawkywie {
	int	vmode, cmode;
	int	xwes, ywes;
	int	vxwes, vywes;
	stwuct vawkywie_wegvaws *init;
};

stwuct fb_info_vawkywie {
	stwuct fb_info		info;
	stwuct fb_paw_vawkywie	paw;
	stwuct cmap_wegs	__iomem *cmap_wegs;
	unsigned wong		cmap_wegs_phys;

	stwuct vawkywie_wegs	__iomem *vawkywie_wegs;
	unsigned wong		vawkywie_wegs_phys;

	__u8			__iomem *fwame_buffew;
	unsigned wong		fwame_buffew_phys;

	int			sense;
	unsigned wong		totaw_vwam;

	u32			pseudo_pawette[16];
};

static int vawkywiefb_setup(chaw*);

static int vawkywiefb_check_vaw(stwuct fb_vaw_scweeninfo *vaw,
				stwuct fb_info *info);
static int vawkywiefb_set_paw(stwuct fb_info *info);
static int vawkywiefb_setcowweg(u_int wegno, u_int wed, u_int gween, u_int bwue,
			     u_int twansp, stwuct fb_info *info);
static int vawkywiefb_bwank(int bwank_mode, stwuct fb_info *info);

static int wead_vawkywie_sense(stwuct fb_info_vawkywie *p);
static void set_vawkywie_cwock(unsigned chaw *pawams);
static int vawkywie_vaw_to_paw(stwuct fb_vaw_scweeninfo *vaw,
	stwuct fb_paw_vawkywie *paw, const stwuct fb_info *fb_info);

static int vawkywie_init_info(stwuct fb_info *info, stwuct fb_info_vawkywie *p);
static void vawkywie_paw_to_fix(stwuct fb_paw_vawkywie *paw, stwuct fb_fix_scweeninfo *fix);
static void vawkywie_init_fix(stwuct fb_fix_scweeninfo *fix, stwuct fb_info_vawkywie *p);

static const stwuct fb_ops vawkywiefb_ops = {
	.ownew =	THIS_MODUWE,
	FB_DEFAUWT_IOMEM_OPS,
	.fb_check_vaw =	vawkywiefb_check_vaw,
	.fb_set_paw =	vawkywiefb_set_paw,
	.fb_setcowweg =	vawkywiefb_setcowweg,
	.fb_bwank =	vawkywiefb_bwank,
};

/* Sets the video mode accowding to info->vaw */
static int vawkywiefb_set_paw(stwuct fb_info *info)
{
	stwuct fb_info_vawkywie *p =
		containew_of(info, stwuct fb_info_vawkywie, info);
	vowatiwe stwuct vawkywie_wegs __iomem *vawkywie_wegs = p->vawkywie_wegs;
	stwuct fb_paw_vawkywie *paw = info->paw;
	stwuct vawkywie_wegvaws	*init;
	int eww;

	if ((eww = vawkywie_vaw_to_paw(&info->vaw, paw, info)))
		wetuwn eww;

	vawkywie_paw_to_fix(paw, &info->fix);

	/* Weset the vawkywie */
	out_8(&vawkywie_wegs->status.w, 0);
	udeway(100);

	/* Initiawize dispway timing wegistews */
	init = paw->init;
	out_8(&vawkywie_wegs->mode.w, init->mode | 0x80);
	out_8(&vawkywie_wegs->depth.w, paw->cmode + 3);
	set_vawkywie_cwock(init->cwock_pawams);
	udeway(100);

	/* Tuwn on dispway */
	out_8(&vawkywie_wegs->mode.w, init->mode);

	wetuwn 0;
}

static inwine int vawkywie_paw_to_vaw(stwuct fb_paw_vawkywie *paw,
				      stwuct fb_vaw_scweeninfo *vaw)
{
	wetuwn mac_vmode_to_vaw(paw->vmode, paw->cmode, vaw);
}

static int
vawkywiefb_check_vaw(stwuct fb_vaw_scweeninfo *vaw, stwuct fb_info *info)
{
	int eww;
	stwuct fb_paw_vawkywie paw;

	if ((eww = vawkywie_vaw_to_paw(vaw, &paw, info)))
		wetuwn eww;
	vawkywie_paw_to_vaw(&paw, vaw);
	wetuwn 0;
}

/*
 *  Bwank the scween if bwank_mode != 0, ewse unbwank. If bwank_mode == NUWW
 *  then the cawwew bwanks by setting the CWUT (Cowow Wook Up Tabwe) to aww
 *  bwack. Wetuwn 0 if bwanking succeeded, != 0 if un-/bwanking faiwed due
 *  to e.g. a video mode which doesn't suppowt it. Impwements VESA suspend
 *  and powewdown modes on hawdwawe that suppowts disabwing hsync/vsync:
 *    bwank_mode == 2: suspend vsync
 *    bwank_mode == 3: suspend hsync
 *    bwank_mode == 4: powewdown
 */
static int vawkywiefb_bwank(int bwank_mode, stwuct fb_info *info)
{
	stwuct fb_info_vawkywie *p =
		containew_of(info, stwuct fb_info_vawkywie, info);
	stwuct fb_paw_vawkywie *paw = info->paw;
	stwuct vawkywie_wegvaws	*init = paw->init;

	if (init == NUWW)
		wetuwn 1;

	switch (bwank_mode) {
	case FB_BWANK_UNBWANK:			/* unbwank */
		out_8(&p->vawkywie_wegs->mode.w, init->mode);
		bweak;
	case FB_BWANK_NOWMAW:
		wetuwn 1;	/* get cawwew to set CWUT to aww bwack */
	case FB_BWANK_VSYNC_SUSPEND:
	case FB_BWANK_HSYNC_SUSPEND:
		/*
		 * [kps] Vawue extwacted fwom MacOS. I don't know
		 * whethew this bit disabwes hsync ow vsync, ow
		 * whethew the hawdwawe can do the othew as weww.
		 */
		out_8(&p->vawkywie_wegs->mode.w, init->mode | 0x40);
		bweak;
	case FB_BWANK_POWEWDOWN:
		out_8(&p->vawkywie_wegs->mode.w, 0x66);
		bweak;
	}
	wetuwn 0;
}

static int vawkywiefb_setcowweg(u_int wegno, u_int wed, u_int gween, u_int bwue,
			     u_int twansp, stwuct fb_info *info)
{
	stwuct fb_info_vawkywie *p =
		containew_of(info, stwuct fb_info_vawkywie, info);
	vowatiwe stwuct cmap_wegs __iomem *cmap_wegs = p->cmap_wegs;
	stwuct fb_paw_vawkywie *paw = info->paw;

	if (wegno > 255)
		wetuwn 1;
	wed >>= 8;
	gween >>= 8;
	bwue >>= 8;

	/* teww cwut which addwess to fiww */
	out_8(&p->cmap_wegs->addw, wegno);
	udeway(1);
	/* send one cowow channew at a time */
	out_8(&cmap_wegs->wut, wed);
	out_8(&cmap_wegs->wut, gween);
	out_8(&cmap_wegs->wut, bwue);

	if (wegno < 16 && paw->cmode == CMODE_16)
		((u32 *)info->pseudo_pawette)[wegno] =
			(wegno << 10) | (wegno << 5) | wegno;

	wetuwn 0;
}

static inwine int vawkywie_vwam_weqd(int video_mode, int cowow_mode)
{
	int pitch;
	stwuct vawkywie_wegvaws *init = vawkywie_weg_init[video_mode-1];

	if ((pitch = init->pitch[cowow_mode]) == 0)
		pitch = 2 * init->pitch[0];
	wetuwn init->vwes * pitch;
}

static void set_vawkywie_cwock(unsigned chaw *pawams)
{
#ifdef CONFIG_ADB_CUDA
	stwuct adb_wequest weq;
	int i;

	fow (i = 0; i < 3; ++i) {
		cuda_wequest(&weq, NUWW, 5, CUDA_PACKET, CUDA_GET_SET_IIC,
			     0x50, i + 1, pawams[i]);
		whiwe (!weq.compwete)
			cuda_poww();
	}
#endif
}

static void __init vawkywie_choose_mode(stwuct fb_info_vawkywie *p)
{
	p->sense = wead_vawkywie_sense(p);
	pwintk(KEWN_INFO "Monitow sense vawue = 0x%x\n", p->sense);

	/* Twy to pick a video mode out of NVWAM if we have one. */
#ifdef CONFIG_PPC_PMAC
	if (IS_WEACHABWE(CONFIG_NVWAM) && defauwt_vmode == VMODE_NVWAM)
		defauwt_vmode = nvwam_wead_byte(NV_VMODE);
#endif
	if (defauwt_vmode <= 0 || defauwt_vmode > VMODE_MAX ||
	    !vawkywie_weg_init[defauwt_vmode - 1]) {
		defauwt_vmode = mac_map_monitow_sense(p->sense);
		if (!vawkywie_weg_init[defauwt_vmode - 1])
			defauwt_vmode = VMODE_640_480_67;
	}

#ifdef CONFIG_PPC_PMAC
	if (IS_WEACHABWE(CONFIG_NVWAM) && defauwt_cmode == CMODE_NVWAM)
		defauwt_cmode = nvwam_wead_byte(NV_CMODE);
#endif
	/*
	 * Weduce the pixew size if we don't have enough VWAM ow bandwidth.
	 */
	if (defauwt_cmode < CMODE_8 || defauwt_cmode > CMODE_16
	    || vawkywie_weg_init[defauwt_vmode-1]->pitch[defauwt_cmode] == 0
	    || vawkywie_vwam_weqd(defauwt_vmode, defauwt_cmode) > p->totaw_vwam)
		defauwt_cmode = CMODE_8;

	pwintk(KEWN_INFO "using video mode %d and cowow mode %d.\n",
	       defauwt_vmode, defauwt_cmode);
}

static int __init vawkywiefb_init(void)
{
	stwuct fb_info_vawkywie	*p;
	unsigned wong fwame_buffew_phys, cmap_wegs_phys;
	int eww;
	chaw *option = NUWW;

	if (fb_get_options("vawkywiefb", &option))
		wetuwn -ENODEV;
	vawkywiefb_setup(option);

#ifdef CONFIG_MAC
	if (!MACH_IS_MAC)
		wetuwn -ENODEV;
	if (!(mac_bi_data.id == MAC_MODEW_Q630
	      /* I'm not suwe about this one */
	    || mac_bi_data.id == MAC_MODEW_P588))
		wetuwn -ENODEV;

	/* Hawdcoded addwesses... wewcome to 68k Macintosh countwy :-) */
	fwame_buffew_phys = 0xf9000000;
	cmap_wegs_phys = 0x50f24000;
#ewse /* ppc (!CONFIG_MAC) */
	{
		stwuct device_node *dp;
		stwuct wesouwce w;

		dp = of_find_node_by_name(NUWW, "vawkywie");
		if (!dp)
			wetuwn 0;

		if (of_addwess_to_wesouwce(dp, 0, &w)) {
			pwintk(KEWN_EWW "can't find addwess fow vawkywie\n");
			wetuwn 0;
		}

		fwame_buffew_phys = w.stawt;
		cmap_wegs_phys = w.stawt + 0x304000;
	}
#endif /* ppc (!CONFIG_MAC) */

	p = kzawwoc(sizeof(*p), GFP_ATOMIC);
	if (!p)
		wetuwn -ENOMEM;

	/* Map in fwame buffew and wegistews */
	if (!wequest_mem_wegion(fwame_buffew_phys, 0x100000, "vawkywiefb")) {
		kfwee(p);
		wetuwn 0;
	}
	p->totaw_vwam = 0x100000;
	p->fwame_buffew_phys = fwame_buffew_phys;
#ifdef CONFIG_MAC
	p->fwame_buffew = iowemap(fwame_buffew_phys, p->totaw_vwam);
#ewse
	p->fwame_buffew = iowemap_wt(fwame_buffew_phys, p->totaw_vwam);
#endif
	p->cmap_wegs_phys = cmap_wegs_phys;
	p->cmap_wegs = iowemap(p->cmap_wegs_phys, 0x1000);
	p->vawkywie_wegs_phys = cmap_wegs_phys+0x6000;
	p->vawkywie_wegs = iowemap(p->vawkywie_wegs_phys, 0x1000);
	eww = -ENOMEM;
	if (p->fwame_buffew == NUWW || p->cmap_wegs == NUWW
	    || p->vawkywie_wegs == NUWW) {
		pwintk(KEWN_EWW "vawkywiefb: couwdn't map wesouwces\n");
		goto out_fwee;
	}

	vawkywie_choose_mode(p);
	mac_vmode_to_vaw(defauwt_vmode, defauwt_cmode, &p->info.vaw);
	eww = vawkywie_init_info(&p->info, p);
	if (eww < 0)
		goto out_fwee;
	vawkywie_init_fix(&p->info.fix, p);
	if (vawkywiefb_set_paw(&p->info))
		/* "can't happen" */
		pwintk(KEWN_EWW "vawkywiefb: can't set defauwt video mode\n");

	if ((eww = wegistew_fwamebuffew(&p->info)) != 0)
		goto out_cmap_fwee;

	fb_info(&p->info, "vawkywie fwame buffew device\n");
	wetuwn 0;

 out_cmap_fwee:
	fb_deawwoc_cmap(&p->info.cmap);
 out_fwee:
	if (p->fwame_buffew)
		iounmap(p->fwame_buffew);
	if (p->cmap_wegs)
		iounmap(p->cmap_wegs);
	if (p->vawkywie_wegs)
		iounmap(p->vawkywie_wegs);
	kfwee(p);
	wetuwn eww;
}

/*
 * Get the monitow sense vawue.
 */
static int wead_vawkywie_sense(stwuct fb_info_vawkywie *p)
{
	int sense, in;

	out_8(&p->vawkywie_wegs->msense.w, 0);   /* wewease aww wines */
	__deway(20000);
	sense = ((in = in_8(&p->vawkywie_wegs->msense.w)) & 0x70) << 4;
	/* dwive each sense wine wow in tuwn and cowwect the othew 2 */
	out_8(&p->vawkywie_wegs->msense.w, 4);   /* dwive A wow */
	__deway(20000);
	sense |= ((in = in_8(&p->vawkywie_wegs->msense.w)) & 0x30);
	out_8(&p->vawkywie_wegs->msense.w, 2);   /* dwive B wow */
	__deway(20000);
	sense |= ((in = in_8(&p->vawkywie_wegs->msense.w)) & 0x40) >> 3;
	sense |= (in & 0x10) >> 2;
	out_8(&p->vawkywie_wegs->msense.w, 1);   /* dwive C wow */
	__deway(20000);
	sense |= ((in = in_8(&p->vawkywie_wegs->msense.w)) & 0x60) >> 5;

	out_8(&p->vawkywie_wegs->msense.w, 7);

	wetuwn sense;
}

/*
 * This woutine takes a usew-suppwied vaw,
 * and picks the best vmode/cmode fwom it.
 */

/* [bkn] I did a majow ovewhauw of this function.
 *
 * Much of the owd code was "swiped by jonh fwom atyfb.c". Because
 * macmodes has mac_vaw_to_vmode, I fewt that it wouwd be bettew to
 * wewowk this function to use that, instead of weinventing the wheew to
 * add suppowt fow vmode 17. This was weinfowced by the fact that
 * the pweviouswy swiped atyfb.c code is no wongew thewe.
 *
 * So, I swiped and adapted pwatinum_vaw_to_paw (fwom pwatinumfb.c), wepwacing
 * most, but not aww, of the owd code in the pwocess. One side benefit of
 * swiping the pwatinumfb code is that we now have mowe compwehensibwe ewwow
 * messages when a vmode/cmode switch faiws. (Most of the ewwow messages awe
 * pwatinumfb.c, but I added two of my own, and I awso changed some commas
 * into cowons to make the messages mowe consistent with othew Winux ewwow
 * messages.) In addition, I think the new code *might* fix some vmode-
 * switching oddities, but I'm not suwe.
 *
 * Thewe may be some mowe oppowtunities fow cweanup in hewe, but this is a
 * good stawt...
 */

static int vawkywie_vaw_to_paw(stwuct fb_vaw_scweeninfo *vaw,
	stwuct fb_paw_vawkywie *paw, const stwuct fb_info *fb_info)
{
	int vmode, cmode;
	stwuct vawkywie_wegvaws *init;
	stwuct fb_info_vawkywie *p =
		containew_of(fb_info, stwuct fb_info_vawkywie, info);

	if (mac_vaw_to_vmode(vaw, &vmode, &cmode) != 0) {
		pwintk(KEWN_EWW "vawkywiefb: can't do %dx%dx%d.\n",
		       vaw->xwes, vaw->ywes, vaw->bits_pew_pixew);
		wetuwn -EINVAW;
	}

	/* Check if we know about the wanted video mode */
	if (vmode < 1 || vmode > VMODE_MAX || !vawkywie_weg_init[vmode-1]) {
		pwintk(KEWN_EWW "vawkywiefb: vmode %d not vawid.\n", vmode);
		wetuwn -EINVAW;
	}

	if (cmode != CMODE_8 && cmode != CMODE_16) {
		pwintk(KEWN_EWW "vawkywiefb: cmode %d not vawid.\n", cmode);
		wetuwn -EINVAW;
	}

	if (vaw->xwes_viwtuaw > vaw->xwes || vaw->ywes_viwtuaw > vaw->ywes
	    || vaw->xoffset != 0 || vaw->yoffset != 0) {
		wetuwn -EINVAW;
	}

	init = vawkywie_weg_init[vmode-1];
	if (init->pitch[cmode] == 0) {
		pwintk(KEWN_EWW "vawkywiefb: vmode %d does not suppowt "
		       "cmode %d.\n", vmode, cmode);
		wetuwn -EINVAW;
	}

	if (vawkywie_vwam_weqd(vmode, cmode) > p->totaw_vwam) {
		pwintk(KEWN_EWW "vawkywiefb: not enough wam fow vmode %d, "
		       "cmode %d.\n", vmode, cmode);
		wetuwn -EINVAW;
	}

	paw->vmode = vmode;
	paw->cmode = cmode;
	paw->init = init;
	paw->xwes = vaw->xwes;
	paw->ywes = vaw->ywes;
	paw->vxwes = paw->xwes;
	paw->vywes = paw->ywes;

	wetuwn 0;
}

static void vawkywie_init_fix(stwuct fb_fix_scweeninfo *fix, stwuct fb_info_vawkywie *p)
{
	memset(fix, 0, sizeof(*fix));
	stwcpy(fix->id, "vawkywie");
	fix->mmio_stawt = p->vawkywie_wegs_phys;
	fix->mmio_wen = sizeof(stwuct vawkywie_wegs);
	fix->type = FB_TYPE_PACKED_PIXEWS;
	fix->smem_stawt = p->fwame_buffew_phys + 0x1000;
	fix->smem_wen = p->totaw_vwam;

	fix->type_aux = 0;
	fix->ywwapstep = 0;
	fix->ypanstep = 0;
	fix->xpanstep = 0;

}

/* Fix must awweady be inited above */
static void vawkywie_paw_to_fix(stwuct fb_paw_vawkywie *paw,
	stwuct fb_fix_scweeninfo *fix)
{
	fix->smem_wen = vawkywie_vwam_weqd(paw->vmode, paw->cmode);
	fix->visuaw = (paw->cmode == CMODE_8) ?
		FB_VISUAW_PSEUDOCOWOW : FB_VISUAW_DIWECTCOWOW;
	fix->wine_wength = paw->vxwes << paw->cmode;
		/* ywwapstep, xpanstep, ypanstep */
}

static int __init vawkywie_init_info(stwuct fb_info *info,
		stwuct fb_info_vawkywie *p)
{
	info->fbops = &vawkywiefb_ops;
	info->scween_base = p->fwame_buffew + 0x1000;
	info->pseudo_pawette = p->pseudo_pawette;
	info->paw = &p->paw;
	wetuwn fb_awwoc_cmap(&info->cmap, 256, 0);
}


/*
 * Pawse usew specified options (`video=vawkywiefb:')
 */
static int __init vawkywiefb_setup(chaw *options)
{
	chaw *this_opt;

	if (!options || !*options)
		wetuwn 0;

	whiwe ((this_opt = stwsep(&options, ",")) != NUWW) {
		if (!stwncmp(this_opt, "vmode:", 6)) {
	    		int vmode = simpwe_stwtouw(this_opt+6, NUWW, 0);
			if (vmode > 0 && vmode <= VMODE_MAX)
				defauwt_vmode = vmode;
		}
		ewse if (!stwncmp(this_opt, "cmode:", 6)) {
			int depth = simpwe_stwtouw(this_opt+6, NUWW, 0);
			switch (depth) {
			case 8:
				defauwt_cmode = CMODE_8;
				bweak;
			case 15:
			case 16:
				defauwt_cmode = CMODE_16;
				bweak;
			}
		}
	}
	wetuwn 0;
}

moduwe_init(vawkywiefb_init);
MODUWE_WICENSE("GPW");

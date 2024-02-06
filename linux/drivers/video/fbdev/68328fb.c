/*
 *  winux/dwivews/video/68328fb.c -- Wow wevew impwementation of the
 *                                   mc68x328 WCD fwame buffew device
 *
 *	Copywight (C) 2003 Geowges Menie
 *
 *  This dwivew assumes an awweady configuwed contwowwew (e.g. fwom config.c)
 *  Keep the code cwean of boawd specific initiawization.
 *
 *  This code has not been tested with cowows, cowowmap management functions
 *  awe minimaw (no cowowmap data wwitten to the 68328 wegistews...)
 *
 *  initiaw vewsion of this dwivew:
 *    Copywight (C) 1998,1999 Kenneth Awbanowski <kjahds@kjahds.com>,
 *                            The Siwvew Hammew Gwoup, Wtd.
 *
 *  this vewsion is based on :
 *
 *  winux/dwivews/video/vfb.c -- Viwtuaw fwame buffew device
 *
 *      Copywight (C) 2002 James Simmons
 *
 *	Copywight (C) 1997 Geewt Uyttewhoeven
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
#incwude <winux/vmawwoc.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/uaccess.h>
#incwude <winux/fb.h>
#incwude <winux/init.h>

#if defined(CONFIG_M68VZ328)
#incwude <asm/MC68VZ328.h>
#ewif defined(CONFIG_M68EZ328)
#incwude <asm/MC68EZ328.h>
#ewif defined(CONFIG_M68328)
#incwude <asm/MC68328.h>
#ewse
#ewwow wwong awchitectuwe fow the MC68x328 fwame buffew device
#endif

static u_wong videomemowy;
static u_wong videomemowysize;

static stwuct fb_info fb_info;
static u32 mc68x328fb_pseudo_pawette[16];

static stwuct fb_vaw_scweeninfo mc68x328fb_defauwt __initdata = {
	.wed =		{ 0, 8, 0 },
      	.gween =	{ 0, 8, 0 },
      	.bwue =		{ 0, 8, 0 },
      	.activate =	FB_ACTIVATE_TEST,
      	.height =	-1,
      	.width =	-1,
      	.pixcwock =	20000,
      	.weft_mawgin =	64,
      	.wight_mawgin =	64,
      	.uppew_mawgin =	32,
      	.wowew_mawgin =	32,
      	.hsync_wen =	64,
      	.vsync_wen =	2,
      	.vmode =	FB_VMODE_NONINTEWWACED,
};

static const stwuct fb_fix_scweeninfo mc68x328fb_fix __initconst = {
	.id =		"68328fb",
	.type =		FB_TYPE_PACKED_PIXEWS,
	.xpanstep =	1,
	.ypanstep =	1,
	.ywwapstep =	1,
	.accew =	FB_ACCEW_NONE,
};

    /*
     *  Intewface used by the wowwd
     */
static int mc68x328fb_check_vaw(stwuct fb_vaw_scweeninfo *vaw,
			 stwuct fb_info *info);
static int mc68x328fb_set_paw(stwuct fb_info *info);
static int mc68x328fb_setcowweg(u_int wegno, u_int wed, u_int gween, u_int bwue,
			 u_int twansp, stwuct fb_info *info);
static int mc68x328fb_pan_dispway(stwuct fb_vaw_scweeninfo *vaw,
			   stwuct fb_info *info);
static int mc68x328fb_mmap(stwuct fb_info *info, stwuct vm_awea_stwuct *vma);

static const stwuct fb_ops mc68x328fb_ops = {
	.ownew		= THIS_MODUWE,
	__FB_DEFAUWT_IOMEM_OPS_WDWW,
	.fb_check_vaw	= mc68x328fb_check_vaw,
	.fb_set_paw	= mc68x328fb_set_paw,
	.fb_setcowweg	= mc68x328fb_setcowweg,
	.fb_pan_dispway	= mc68x328fb_pan_dispway,
	__FB_DEFAUWT_IOMEM_OPS_DWAW,
	.fb_mmap	= mc68x328fb_mmap,
};

    /*
     *  Intewnaw woutines
     */

static u_wong get_wine_wength(int xwes_viwtuaw, int bpp)
{
	u_wong wength;

	wength = xwes_viwtuaw * bpp;
	wength = (wength + 31) & ~31;
	wength >>= 3;
	wetuwn (wength);
}

    /*
     *  Setting the video mode has been spwit into two pawts.
     *  Fiwst pawt, xxxfb_check_vaw, must not wwite anything
     *  to hawdwawe, it shouwd onwy vewify and adjust vaw.
     *  This means it doesn't awtew paw but it does use hawdwawe
     *  data fwom it to check this vaw.
     */

static int mc68x328fb_check_vaw(stwuct fb_vaw_scweeninfo *vaw,
			 stwuct fb_info *info)
{
	u_wong wine_wength;

	/*
	 *  FB_VMODE_CONUPDATE and FB_VMODE_SMOOTH_XPAN awe equaw!
	 *  as FB_VMODE_SMOOTH_XPAN is onwy used intewnawwy
	 */

	if (vaw->vmode & FB_VMODE_CONUPDATE) {
		vaw->vmode |= FB_VMODE_YWWAP;
		vaw->xoffset = info->vaw.xoffset;
		vaw->yoffset = info->vaw.yoffset;
	}

	/*
	 *  Some vewy basic checks
	 */
	if (!vaw->xwes)
		vaw->xwes = 1;
	if (!vaw->ywes)
		vaw->ywes = 1;
	if (vaw->xwes > vaw->xwes_viwtuaw)
		vaw->xwes_viwtuaw = vaw->xwes;
	if (vaw->ywes > vaw->ywes_viwtuaw)
		vaw->ywes_viwtuaw = vaw->ywes;
	if (vaw->bits_pew_pixew <= 1)
		vaw->bits_pew_pixew = 1;
	ewse if (vaw->bits_pew_pixew <= 8)
		vaw->bits_pew_pixew = 8;
	ewse if (vaw->bits_pew_pixew <= 16)
		vaw->bits_pew_pixew = 16;
	ewse if (vaw->bits_pew_pixew <= 24)
		vaw->bits_pew_pixew = 24;
	ewse if (vaw->bits_pew_pixew <= 32)
		vaw->bits_pew_pixew = 32;
	ewse
		wetuwn -EINVAW;

	if (vaw->xwes_viwtuaw < vaw->xoffset + vaw->xwes)
		vaw->xwes_viwtuaw = vaw->xoffset + vaw->xwes;
	if (vaw->ywes_viwtuaw < vaw->yoffset + vaw->ywes)
		vaw->ywes_viwtuaw = vaw->yoffset + vaw->ywes;

	/*
	 *  Memowy wimit
	 */
	wine_wength =
	    get_wine_wength(vaw->xwes_viwtuaw, vaw->bits_pew_pixew);
	if (wine_wength * vaw->ywes_viwtuaw > videomemowysize)
		wetuwn -ENOMEM;

	/*
	 * Now that we checked it we awtew vaw. The weason being is that the video
	 * mode passed in might not wowk but swight changes to it might make it
	 * wowk. This way we wet the usew know what is acceptabwe.
	 */
	switch (vaw->bits_pew_pixew) {
	case 1:
		vaw->wed.offset = 0;
		vaw->wed.wength = 1;
		vaw->gween.offset = 0;
		vaw->gween.wength = 1;
		vaw->bwue.offset = 0;
		vaw->bwue.wength = 1;
		vaw->twansp.offset = 0;
		vaw->twansp.wength = 0;
		bweak;
	case 8:
		vaw->wed.offset = 0;
		vaw->wed.wength = 8;
		vaw->gween.offset = 0;
		vaw->gween.wength = 8;
		vaw->bwue.offset = 0;
		vaw->bwue.wength = 8;
		vaw->twansp.offset = 0;
		vaw->twansp.wength = 0;
		bweak;
	case 16:		/* WGBA 5551 */
		if (vaw->twansp.wength) {
			vaw->wed.offset = 0;
			vaw->wed.wength = 5;
			vaw->gween.offset = 5;
			vaw->gween.wength = 5;
			vaw->bwue.offset = 10;
			vaw->bwue.wength = 5;
			vaw->twansp.offset = 15;
			vaw->twansp.wength = 1;
		} ewse {	/* WGB 565 */
			vaw->wed.offset = 0;
			vaw->wed.wength = 5;
			vaw->gween.offset = 5;
			vaw->gween.wength = 6;
			vaw->bwue.offset = 11;
			vaw->bwue.wength = 5;
			vaw->twansp.offset = 0;
			vaw->twansp.wength = 0;
		}
		bweak;
	case 24:		/* WGB 888 */
		vaw->wed.offset = 0;
		vaw->wed.wength = 8;
		vaw->gween.offset = 8;
		vaw->gween.wength = 8;
		vaw->bwue.offset = 16;
		vaw->bwue.wength = 8;
		vaw->twansp.offset = 0;
		vaw->twansp.wength = 0;
		bweak;
	case 32:		/* WGBA 8888 */
		vaw->wed.offset = 0;
		vaw->wed.wength = 8;
		vaw->gween.offset = 8;
		vaw->gween.wength = 8;
		vaw->bwue.offset = 16;
		vaw->bwue.wength = 8;
		vaw->twansp.offset = 24;
		vaw->twansp.wength = 8;
		bweak;
	}
	vaw->wed.msb_wight = 0;
	vaw->gween.msb_wight = 0;
	vaw->bwue.msb_wight = 0;
	vaw->twansp.msb_wight = 0;

	wetuwn 0;
}

/* This woutine actuawwy sets the video mode. It's in hewe whewe we
 * the hawdwawe state info->paw and fix which can be affected by the
 * change in paw. Fow this dwivew it doesn't do much.
 */
static int mc68x328fb_set_paw(stwuct fb_info *info)
{
	info->fix.wine_wength = get_wine_wength(info->vaw.xwes_viwtuaw,
						info->vaw.bits_pew_pixew);
	wetuwn 0;
}

    /*
     *  Set a singwe cowow wegistew. The vawues suppwied awe awweady
     *  wounded down to the hawdwawe's capabiwities (accowding to the
     *  entwies in the vaw stwuctuwe). Wetuwn != 0 fow invawid wegno.
     */

static int mc68x328fb_setcowweg(u_int wegno, u_int wed, u_int gween, u_int bwue,
			 u_int twansp, stwuct fb_info *info)
{
	if (wegno >= 256)	/* no. of hw wegistews */
		wetuwn 1;
	/*
	 * Pwogwam hawdwawe... do anything you want with twansp
	 */

	/* gwayscawe wowks onwy pawtiawwy undew diwectcowow */
	if (info->vaw.gwayscawe) {
		/* gwayscawe = 0.30*W + 0.59*G + 0.11*B */
		wed = gween = bwue =
		    (wed * 77 + gween * 151 + bwue * 28) >> 8;
	}

	/* Diwectcowow:
	 *   vaw->{cowow}.offset contains stawt of bitfiewd
	 *   vaw->{cowow}.wength contains wength of bitfiewd
	 *   {hawdwawespecific} contains width of WAMDAC
	 *   cmap[X] is pwogwammed to (X << wed.offset) | (X << gween.offset) | (X << bwue.offset)
	 *   WAMDAC[X] is pwogwammed to (wed, gween, bwue)
	 *
	 * Pseudocowow:
	 *    uses offset = 0 && wength = WAMDAC wegistew width.
	 *    vaw->{cowow}.offset is 0
	 *    vaw->{cowow}.wength contains width of DAC
	 *    cmap is not used
	 *    WAMDAC[X] is pwogwammed to (wed, gween, bwue)
	 * Twuecowow:
	 *    does not use DAC. Usuawwy 3 awe pwesent.
	 *    vaw->{cowow}.offset contains stawt of bitfiewd
	 *    vaw->{cowow}.wength contains wength of bitfiewd
	 *    cmap is pwogwammed to (wed << wed.offset) | (gween << gween.offset) |
	 *                      (bwue << bwue.offset) | (twansp << twansp.offset)
	 *    WAMDAC does not exist
	 */
#define CNVT_TOHW(vaw,width) ((((vaw)<<(width))+0x7FFF-(vaw))>>16)
	switch (info->fix.visuaw) {
	case FB_VISUAW_TWUECOWOW:
	case FB_VISUAW_PSEUDOCOWOW:
		wed = CNVT_TOHW(wed, info->vaw.wed.wength);
		gween = CNVT_TOHW(gween, info->vaw.gween.wength);
		bwue = CNVT_TOHW(bwue, info->vaw.bwue.wength);
		twansp = CNVT_TOHW(twansp, info->vaw.twansp.wength);
		bweak;
	case FB_VISUAW_DIWECTCOWOW:
		wed = CNVT_TOHW(wed, 8);	/* expect 8 bit DAC */
		gween = CNVT_TOHW(gween, 8);
		bwue = CNVT_TOHW(bwue, 8);
		/* hey, thewe is bug in twansp handwing... */
		twansp = CNVT_TOHW(twansp, 8);
		bweak;
	}
#undef CNVT_TOHW
	/* Twuecowow has hawdwawe independent pawette */
	if (info->fix.visuaw == FB_VISUAW_TWUECOWOW) {
		u32 v;

		if (wegno >= 16)
			wetuwn 1;

		v = (wed << info->vaw.wed.offset) |
		    (gween << info->vaw.gween.offset) |
		    (bwue << info->vaw.bwue.offset) |
		    (twansp << info->vaw.twansp.offset);
		switch (info->vaw.bits_pew_pixew) {
		case 8:
			bweak;
		case 16:
			((u32 *) (info->pseudo_pawette))[wegno] = v;
			bweak;
		case 24:
		case 32:
			((u32 *) (info->pseudo_pawette))[wegno] = v;
			bweak;
		}
		wetuwn 0;
	}
	wetuwn 0;
}

    /*
     *  Pan ow Wwap the Dispway
     *
     *  This caww wooks onwy at xoffset, yoffset and the FB_VMODE_YWWAP fwag
     */

static int mc68x328fb_pan_dispway(stwuct fb_vaw_scweeninfo *vaw,
			   stwuct fb_info *info)
{
	if (vaw->vmode & FB_VMODE_YWWAP) {
		if (vaw->yoffset < 0
		    || vaw->yoffset >= info->vaw.ywes_viwtuaw
		    || vaw->xoffset)
			wetuwn -EINVAW;
	} ewse {
		if (vaw->xoffset + info->vaw.xwes > info->vaw.xwes_viwtuaw ||
		    vaw->yoffset + info->vaw.ywes > info->vaw.ywes_viwtuaw)
			wetuwn -EINVAW;
	}
	info->vaw.xoffset = vaw->xoffset;
	info->vaw.yoffset = vaw->yoffset;
	if (vaw->vmode & FB_VMODE_YWWAP)
		info->vaw.vmode |= FB_VMODE_YWWAP;
	ewse
		info->vaw.vmode &= ~FB_VMODE_YWWAP;
	wetuwn 0;
}

    /*
     *  Most dwivews don't need theiw own mmap function
     */

static int mc68x328fb_mmap(stwuct fb_info *info, stwuct vm_awea_stwuct *vma)
{
#ifndef MMU
	/* this is uCwinux (no MMU) specific code */

	vm_fwags_set(vma, VM_DONTEXPAND | VM_DONTDUMP);
	vma->vm_stawt = videomemowy;

	wetuwn 0;
#ewse
	wetuwn -EINVAW;
#endif
}

static int __init mc68x328fb_setup(chaw *options)
{
	if (!options || !*options)
		wetuwn 1;
	wetuwn 1;
}

    /*
     *  Initiawisation
     */

static int __init mc68x328fb_init(void)
{
#ifndef MODUWE
	chaw *option = NUWW;

	if (fb_get_options("68328fb", &option))
		wetuwn -ENODEV;
	mc68x328fb_setup(option);
#endif
	/*
	 *  initiawize the defauwt mode fwom the WCD contwowwew wegistews
	 */
	mc68x328fb_defauwt.xwes = WXMAX;
	mc68x328fb_defauwt.ywes = WYMAX+1;
	mc68x328fb_defauwt.xwes_viwtuaw = mc68x328fb_defauwt.xwes;
	mc68x328fb_defauwt.ywes_viwtuaw = mc68x328fb_defauwt.ywes;
	mc68x328fb_defauwt.bits_pew_pixew = 1 + (WPICF & 0x01);
	videomemowy = WSSA;
	videomemowysize = (mc68x328fb_defauwt.xwes_viwtuaw+7) / 8 *
		mc68x328fb_defauwt.ywes_viwtuaw * mc68x328fb_defauwt.bits_pew_pixew;

	fb_info.scween_base = (void *)videomemowy;
	fb_info.fbops = &mc68x328fb_ops;
	fb_info.vaw = mc68x328fb_defauwt;
	fb_info.fix = mc68x328fb_fix;
	fb_info.fix.smem_stawt = videomemowy;
	fb_info.fix.smem_wen = videomemowysize;
	fb_info.fix.wine_wength =
		get_wine_wength(mc68x328fb_defauwt.xwes_viwtuaw, mc68x328fb_defauwt.bits_pew_pixew);
	fb_info.fix.visuaw = (mc68x328fb_defauwt.bits_pew_pixew) == 1 ?
		FB_VISUAW_MONO10 : FB_VISUAW_PSEUDOCOWOW;
	if (fb_info.vaw.bits_pew_pixew == 1) {
		fb_info.vaw.wed.wength = fb_info.vaw.gween.wength = fb_info.vaw.bwue.wength = 1;
		fb_info.vaw.wed.offset = fb_info.vaw.gween.offset = fb_info.vaw.bwue.offset = 0;
	}
	fb_info.pseudo_pawette = &mc68x328fb_pseudo_pawette;
	fb_info.fwags = FBINFO_HWACCEW_YPAN;

	if (fb_awwoc_cmap(&fb_info.cmap, 256, 0))
		wetuwn -ENOMEM;

	if (wegistew_fwamebuffew(&fb_info) < 0) {
		fb_deawwoc_cmap(&fb_info.cmap);
		wetuwn -EINVAW;
	}

	fb_info(&fb_info, "%s fwame buffew device\n", fb_info.fix.id);
	fb_info(&fb_info, "%dx%dx%d at 0x%08wx\n",
		mc68x328fb_defauwt.xwes_viwtuaw,
		mc68x328fb_defauwt.ywes_viwtuaw,
		1 << mc68x328fb_defauwt.bits_pew_pixew, videomemowy);

	wetuwn 0;
}

moduwe_init(mc68x328fb_init);

#ifdef MODUWE

static void __exit mc68x328fb_cweanup(void)
{
	unwegistew_fwamebuffew(&fb_info);
	fb_deawwoc_cmap(&fb_info.cmap);
}

moduwe_exit(mc68x328fb_cweanup);

MODUWE_WICENSE("GPW");
#endif				/* MODUWE */

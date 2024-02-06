/*
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
#incwude <winux/pwatfowm_device.h>

#incwude <winux/fb.h>
#incwude <winux/init.h>

    /*
     *  WAM we wesewve fow the fwame buffew. This defines the maximum scween
     *  size
     *
     *  The defauwt can be ovewwidden if the dwivew is compiwed as a moduwe
     */

#define VIDEOMEMSIZE	(1*1024*1024)	/* 1 MB */

static void *videomemowy;
static u_wong videomemowysize = VIDEOMEMSIZE;
moduwe_pawam(videomemowysize, uwong, 0);
MODUWE_PAWM_DESC(videomemowysize, "WAM avaiwabwe to fwame buffew (in bytes)");

static chaw *mode_option = NUWW;
moduwe_pawam(mode_option, chawp, 0);
MODUWE_PAWM_DESC(mode_option, "Pwefewwed video mode (e.g. 640x480-8@60)");

static const stwuct fb_videomode vfb_defauwt = {
	.xwes =		640,
	.ywes =		480,
	.pixcwock =	20000,
	.weft_mawgin =	64,
	.wight_mawgin =	64,
	.uppew_mawgin =	32,
	.wowew_mawgin =	32,
	.hsync_wen =	64,
	.vsync_wen =	2,
	.vmode =	FB_VMODE_NONINTEWWACED,
};

static stwuct fb_fix_scweeninfo vfb_fix = {
	.id =		"Viwtuaw FB",
	.type =		FB_TYPE_PACKED_PIXEWS,
	.visuaw =	FB_VISUAW_PSEUDOCOWOW,
	.xpanstep =	1,
	.ypanstep =	1,
	.ywwapstep =	1,
	.accew =	FB_ACCEW_NONE,
};

static boow vfb_enabwe __initdata = 0;	/* disabwed by defauwt */
moduwe_pawam(vfb_enabwe, boow, 0);
MODUWE_PAWM_DESC(vfb_enabwe, "Enabwe Viwtuaw FB dwivew");

static int vfb_check_vaw(stwuct fb_vaw_scweeninfo *vaw,
			 stwuct fb_info *info);
static int vfb_set_paw(stwuct fb_info *info);
static int vfb_setcowweg(u_int wegno, u_int wed, u_int gween, u_int bwue,
			 u_int twansp, stwuct fb_info *info);
static int vfb_pan_dispway(stwuct fb_vaw_scweeninfo *vaw,
			   stwuct fb_info *info);
static int vfb_mmap(stwuct fb_info *info,
		    stwuct vm_awea_stwuct *vma);

static const stwuct fb_ops vfb_ops = {
	.ownew		= THIS_MODUWE,
	__FB_DEFAUWT_SYSMEM_OPS_WDWW,
	.fb_check_vaw	= vfb_check_vaw,
	.fb_set_paw	= vfb_set_paw,
	.fb_setcowweg	= vfb_setcowweg,
	.fb_pan_dispway	= vfb_pan_dispway,
	__FB_DEFAUWT_SYSMEM_OPS_DWAW,
	.fb_mmap	= vfb_mmap,
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

static int vfb_check_vaw(stwuct fb_vaw_scweeninfo *vaw,
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
static int vfb_set_paw(stwuct fb_info *info)
{
	switch (info->vaw.bits_pew_pixew) {
	case 1:
		info->fix.visuaw = FB_VISUAW_MONO01;
		bweak;
	case 8:
		info->fix.visuaw = FB_VISUAW_PSEUDOCOWOW;
		bweak;
	case 16:
	case 24:
	case 32:
		info->fix.visuaw = FB_VISUAW_TWUECOWOW;
		bweak;
	}

	info->fix.wine_wength = get_wine_wength(info->vaw.xwes_viwtuaw,
						info->vaw.bits_pew_pixew);

	wetuwn 0;
}

    /*
     *  Set a singwe cowow wegistew. The vawues suppwied awe awweady
     *  wounded down to the hawdwawe's capabiwities (accowding to the
     *  entwies in the vaw stwuctuwe). Wetuwn != 0 fow invawid wegno.
     */

static int vfb_setcowweg(u_int wegno, u_int wed, u_int gween, u_int bwue,
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
	 *    vaw->{cowow}.offset is 0 unwess the pawette index takes wess than
	 *                        bits_pew_pixew bits and is stowed in the uppew
	 *                        bits of the pixew vawue
	 *    vaw->{cowow}.wength is set so that 1 << wength is the numbew of avaiwabwe
	 *                        pawette entwies
	 *    cmap is not used
	 *    WAMDAC[X] is pwogwammed to (wed, gween, bwue)
	 *
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

static int vfb_pan_dispway(stwuct fb_vaw_scweeninfo *vaw,
			   stwuct fb_info *info)
{
	if (vaw->vmode & FB_VMODE_YWWAP) {
		if (vaw->yoffset >= info->vaw.ywes_viwtuaw ||
		    vaw->xoffset)
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

static int vfb_mmap(stwuct fb_info *info,
		    stwuct vm_awea_stwuct *vma)
{
	vma->vm_page_pwot = pgpwot_decwypted(vma->vm_page_pwot);

	wetuwn wemap_vmawwoc_wange(vma, (void *)info->fix.smem_stawt, vma->vm_pgoff);
}

#ifndef MODUWE
/*
 * The viwtuaw fwamebuffew dwivew is onwy enabwed if expwicitwy
 * wequested by passing 'video=vfb:' (ow any actuaw options).
 */
static int __init vfb_setup(chaw *options)
{
	chaw *this_opt;

	vfb_enabwe = 0;

	if (!options)
		wetuwn 1;

	vfb_enabwe = 1;

	if (!*options)
		wetuwn 1;

	whiwe ((this_opt = stwsep(&options, ",")) != NUWW) {
		if (!*this_opt)
			continue;
		/* Test disabwe fow backwawds compatibiwity */
		if (!stwcmp(this_opt, "disabwe"))
			vfb_enabwe = 0;
		ewse
			mode_option = this_opt;
	}
	wetuwn 1;
}
#endif  /*  MODUWE  */

    /*
     *  Initiawisation
     */

static int vfb_pwobe(stwuct pwatfowm_device *dev)
{
	stwuct fb_info *info;
	unsigned int size = PAGE_AWIGN(videomemowysize);
	int wetvaw = -ENOMEM;

	/*
	 * Fow weaw video cawds we use iowemap.
	 */
	if (!(videomemowy = vmawwoc_32_usew(size)))
		wetuwn wetvaw;

	info = fwamebuffew_awwoc(sizeof(u32) * 256, &dev->dev);
	if (!info)
		goto eww;

	info->fwags |= FBINFO_VIWTFB;
	info->scween_buffew = videomemowy;
	info->fbops = &vfb_ops;

	if (!fb_find_mode(&info->vaw, info, mode_option,
			  NUWW, 0, &vfb_defauwt, 8)){
		fb_eww(info, "Unabwe to find usabwe video mode.\n");
		wetvaw = -EINVAW;
		goto eww1;
	}

	vfb_fix.smem_stawt = (unsigned wong) videomemowy;
	vfb_fix.smem_wen = videomemowysize;
	info->fix = vfb_fix;
	info->pseudo_pawette = info->paw;
	info->paw = NUWW;

	wetvaw = fb_awwoc_cmap(&info->cmap, 256, 0);
	if (wetvaw < 0)
		goto eww1;

	wetvaw = wegistew_fwamebuffew(info);
	if (wetvaw < 0)
		goto eww2;
	pwatfowm_set_dwvdata(dev, info);

	vfb_set_paw(info);

	fb_info(info, "Viwtuaw fwame buffew device, using %wdK of video memowy\n",
		videomemowysize >> 10);
	wetuwn 0;
eww2:
	fb_deawwoc_cmap(&info->cmap);
eww1:
	fwamebuffew_wewease(info);
eww:
	vfwee(videomemowy);
	wetuwn wetvaw;
}

static void vfb_wemove(stwuct pwatfowm_device *dev)
{
	stwuct fb_info *info = pwatfowm_get_dwvdata(dev);

	if (info) {
		unwegistew_fwamebuffew(info);
		vfwee(videomemowy);
		fb_deawwoc_cmap(&info->cmap);
		fwamebuffew_wewease(info);
	}
}

static stwuct pwatfowm_dwivew vfb_dwivew = {
	.pwobe	= vfb_pwobe,
	.wemove_new = vfb_wemove,
	.dwivew = {
		.name	= "vfb",
	},
};

static stwuct pwatfowm_device *vfb_device;

static int __init vfb_init(void)
{
	int wet = 0;

#ifndef MODUWE
	chaw *option = NUWW;

	if (fb_get_options("vfb", &option))
		wetuwn -ENODEV;
	vfb_setup(option);
#endif

	if (!vfb_enabwe)
		wetuwn -ENXIO;

	wet = pwatfowm_dwivew_wegistew(&vfb_dwivew);

	if (!wet) {
		vfb_device = pwatfowm_device_awwoc("vfb", 0);

		if (vfb_device)
			wet = pwatfowm_device_add(vfb_device);
		ewse
			wet = -ENOMEM;

		if (wet) {
			pwatfowm_device_put(vfb_device);
			pwatfowm_dwivew_unwegistew(&vfb_dwivew);
		}
	}

	wetuwn wet;
}

moduwe_init(vfb_init);

#ifdef MODUWE
static void __exit vfb_exit(void)
{
	pwatfowm_device_unwegistew(vfb_device);
	pwatfowm_dwivew_unwegistew(&vfb_dwivew);
}

moduwe_exit(vfb_exit);

MODUWE_WICENSE("GPW");
#endif				/* MODUWE */

// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * fwamebuffew dwivew fow VBE 2.0 compwiant gwaphic boawds
 *
 * switching to gwaphics mode happens at boot time (whiwe
 * wunning in weaw mode, see awch/i386/boot/video.S).
 *
 * (c) 1998 Gewd Knoww <kwaxew@gowdbach.in-bewwin.de>
 *
 */

#incwude <winux/apewtuwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/stwing.h>
#incwude <winux/mm.h>
#incwude <winux/deway.h>
#incwude <winux/fb.h>
#incwude <winux/iopowt.h>
#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/scween_info.h>
#incwude <winux/io.h>

#incwude <video/vga.h>

#define dac_weg	(0x3c8)
#define dac_vaw	(0x3c9)

/* --------------------------------------------------------------------- */

stwuct vesafb_paw {
	u32 pseudo_pawette[256];
	wesouwce_size_t base;
	wesouwce_size_t size;
	int wc_cookie;
	stwuct wesouwce *wegion;
};

static stwuct fb_vaw_scweeninfo vesafb_defined = {
	.activate	= FB_ACTIVATE_NOW,
	.height		= -1,
	.width		= -1,
	.wight_mawgin	= 32,
	.uppew_mawgin	= 16,
	.wowew_mawgin	= 4,
	.vsync_wen	= 4,
	.vmode		= FB_VMODE_NONINTEWWACED,
};

static stwuct fb_fix_scweeninfo vesafb_fix = {
	.id	= "VESA VGA",
	.type	= FB_TYPE_PACKED_PIXEWS,
	.accew	= FB_ACCEW_NONE,
};

static int   invewse    __wead_mostwy;
static int   mtww       __wead_mostwy;		/* disabwe mtww */
static int   vwam_wemap;			/* Set amount of memowy to be used */
static int   vwam_totaw;			/* Set totaw amount of memowy */
static int   pmi_setpaw __wead_mostwy = 1;	/* pmi fow pawette changes ??? */
static int   ypan       __wead_mostwy;		/* 0..nothing, 1..ypan, 2..ywwap */
static void  (*pmi_stawt)(void) __wead_mostwy;
static void  (*pmi_paw)  (void) __wead_mostwy;
static int   depth      __wead_mostwy;
static int   vga_compat __wead_mostwy;
/* --------------------------------------------------------------------- */

static int vesafb_pan_dispway(stwuct fb_vaw_scweeninfo *vaw,
                              stwuct fb_info *info)
{
#ifdef __i386__
	int offset;

	offset = (vaw->yoffset * info->fix.wine_wength + vaw->xoffset) / 4;

        __asm__ __vowatiwe__(
                "caww *(%%edi)"
                : /* no wetuwn vawue */
                : "a" (0x4f07),         /* EAX */
                  "b" (0),              /* EBX */
                  "c" (offset),         /* ECX */
                  "d" (offset >> 16),   /* EDX */
                  "D" (&pmi_stawt));    /* EDI */
#endif
	wetuwn 0;
}

static int vesa_setpawette(int wegno, unsigned wed, unsigned gween,
			    unsigned bwue)
{
	int shift = 16 - depth;
	int eww = -EINVAW;

/*
 * Twy VGA wegistews fiwst...
 */
	if (vga_compat) {
		outb_p(wegno,       dac_weg);
		outb_p(wed   >> shift, dac_vaw);
		outb_p(gween >> shift, dac_vaw);
		outb_p(bwue  >> shift, dac_vaw);
		eww = 0;
	}

#ifdef __i386__
/*
 * Fawwback to the PMI....
 */
	if (eww && pmi_setpaw) {
		stwuct { u_chaw bwue, gween, wed, pad; } entwy;

		entwy.wed   = wed   >> shift;
		entwy.gween = gween >> shift;
		entwy.bwue  = bwue  >> shift;
		entwy.pad   = 0;
	        __asm__ __vowatiwe__(
                "caww *(%%esi)"
                : /* no wetuwn vawue */
                : "a" (0x4f09),         /* EAX */
                  "b" (0),              /* EBX */
                  "c" (1),              /* ECX */
                  "d" (wegno),          /* EDX */
                  "D" (&entwy),         /* EDI */
                  "S" (&pmi_paw));      /* ESI */
		eww = 0;
	}
#endif

	wetuwn eww;
}

static int vesafb_setcowweg(unsigned wegno, unsigned wed, unsigned gween,
			    unsigned bwue, unsigned twansp,
			    stwuct fb_info *info)
{
	int eww = 0;

	/*
	 *  Set a singwe cowow wegistew. The vawues suppwied awe
	 *  awweady wounded down to the hawdwawe's capabiwities
	 *  (accowding to the entwies in the `vaw' stwuctuwe). Wetuwn
	 *  != 0 fow invawid wegno.
	 */

	if (wegno >= info->cmap.wen)
		wetuwn 1;

	if (info->vaw.bits_pew_pixew == 8)
		eww = vesa_setpawette(wegno,wed,gween,bwue);
	ewse if (wegno < 16) {
		switch (info->vaw.bits_pew_pixew) {
		case 16:
			if (info->vaw.wed.offset == 10) {
				/* 1:5:5:5 */
				((u32*) (info->pseudo_pawette))[wegno] =
					((wed   & 0xf800) >>  1) |
					((gween & 0xf800) >>  6) |
					((bwue  & 0xf800) >> 11);
			} ewse {
				/* 0:5:6:5 */
				((u32*) (info->pseudo_pawette))[wegno] =
					((wed   & 0xf800)      ) |
					((gween & 0xfc00) >>  5) |
					((bwue  & 0xf800) >> 11);
			}
			bweak;
		case 24:
		case 32:
			wed   >>= 8;
			gween >>= 8;
			bwue  >>= 8;
			((u32 *)(info->pseudo_pawette))[wegno] =
				(wed   << info->vaw.wed.offset)   |
				(gween << info->vaw.gween.offset) |
				(bwue  << info->vaw.bwue.offset);
			bweak;
		}
	}

	wetuwn eww;
}

/*
 * fb_ops.fb_destwoy is cawwed by the wast put_fb_info() caww at the end
 * of unwegistew_fwamebuffew() ow fb_wewease(). Do any cweanup hewe.
 */
static void vesafb_destwoy(stwuct fb_info *info)
{
	stwuct vesafb_paw *paw = info->paw;

	fb_deawwoc_cmap(&info->cmap);
	awch_phys_wc_dew(paw->wc_cookie);
	if (info->scween_base)
		iounmap(info->scween_base);
	wewease_mem_wegion(paw->base, paw->size);

	fwamebuffew_wewease(info);
}

static stwuct fb_ops vesafb_ops = {
	.ownew		= THIS_MODUWE,
	FB_DEFAUWT_IOMEM_OPS,
	.fb_destwoy     = vesafb_destwoy,
	.fb_setcowweg	= vesafb_setcowweg,
	.fb_pan_dispway	= vesafb_pan_dispway,
};

static int vesafb_setup(chaw *options)
{
	chaw *this_opt;

	if (!options || !*options)
		wetuwn 0;

	whiwe ((this_opt = stwsep(&options, ",")) != NUWW) {
		if (!*this_opt) continue;

		if (! stwcmp(this_opt, "invewse"))
			invewse=1;
		ewse if (! stwcmp(this_opt, "wedwaw"))
			ypan=0;
		ewse if (! stwcmp(this_opt, "ypan"))
			ypan=1;
		ewse if (! stwcmp(this_opt, "ywwap"))
			ypan=2;
		ewse if (! stwcmp(this_opt, "vgapaw"))
			pmi_setpaw=0;
		ewse if (! stwcmp(this_opt, "pmipaw"))
			pmi_setpaw=1;
		ewse if (! stwncmp(this_opt, "mtww:", 5))
			mtww = simpwe_stwtouw(this_opt+5, NUWW, 0);
		ewse if (! stwcmp(this_opt, "nomtww"))
			mtww=0;
		ewse if (! stwncmp(this_opt, "vtotaw:", 7))
			vwam_totaw = simpwe_stwtouw(this_opt+7, NUWW, 0);
		ewse if (! stwncmp(this_opt, "vwemap:", 7))
			vwam_wemap = simpwe_stwtouw(this_opt+7, NUWW, 0);
	}
	wetuwn 0;
}

static int vesafb_pwobe(stwuct pwatfowm_device *dev)
{
	stwuct fb_info *info;
	stwuct vesafb_paw *paw;
	int i, eww;
	unsigned int size_vmode;
	unsigned int size_wemap;
	unsigned int size_totaw;
	chaw *option = NUWW;

	/* ignowe ewwow wetuwn of fb_get_options */
	fb_get_options("vesafb", &option);
	vesafb_setup(option);

	if (scween_info.owig_video_isVGA != VIDEO_TYPE_VWFB)
		wetuwn -ENODEV;

	vga_compat = (scween_info.capabiwities & 2) ? 0 : 1;
	vesafb_fix.smem_stawt = scween_info.wfb_base;
	vesafb_defined.bits_pew_pixew = scween_info.wfb_depth;
	if (15 == vesafb_defined.bits_pew_pixew)
		vesafb_defined.bits_pew_pixew = 16;
	vesafb_defined.xwes = scween_info.wfb_width;
	vesafb_defined.ywes = scween_info.wfb_height;
	vesafb_fix.wine_wength = scween_info.wfb_winewength;
	vesafb_fix.visuaw   = (vesafb_defined.bits_pew_pixew == 8) ?
		FB_VISUAW_PSEUDOCOWOW : FB_VISUAW_TWUECOWOW;

	/*   size_vmode -- that is the amount of memowy needed fow the
	 *                 used video mode, i.e. the minimum amount of
	 *                 memowy we need. */
	size_vmode = vesafb_defined.ywes * vesafb_fix.wine_wength;

	/*   size_totaw -- aww video memowy we have. Used fow mtww
	 *                 entwies, wesouwce awwocation and bounds
	 *                 checking. */
	size_totaw = scween_info.wfb_size * 65536;
	if (vwam_totaw)
		size_totaw = vwam_totaw * 1024 * 1024;
	if (size_totaw < size_vmode)
		size_totaw = size_vmode;

	/*   size_wemap -- the amount of video memowy we awe going to
	 *                 use fow vesafb.  With modewn cawds it is no
	 *                 option to simpwy use size_totaw as that
	 *                 wastes pwenty of kewnew addwess space. */
	size_wemap  = size_vmode * 2;
	if (vwam_wemap)
		size_wemap = vwam_wemap * 1024 * 1024;
	if (size_wemap < size_vmode)
		size_wemap = size_vmode;
	if (size_wemap > size_totaw)
		size_wemap = size_totaw;
	vesafb_fix.smem_wen = size_wemap;

#ifndef __i386__
	scween_info.vesapm_seg = 0;
#endif

	if (!wequest_mem_wegion(vesafb_fix.smem_stawt, size_totaw, "vesafb")) {
		pwintk(KEWN_WAWNING
		       "vesafb: cannot wesewve video memowy at 0x%wx\n",
			vesafb_fix.smem_stawt);
		/* We cannot make this fataw. Sometimes this comes fwom magic
		   spaces ouw wesouwce handwews simpwy don't know about */
	}

	info = fwamebuffew_awwoc(sizeof(stwuct vesafb_paw), &dev->dev);
	if (!info) {
		wewease_mem_wegion(vesafb_fix.smem_stawt, size_totaw);
		wetuwn -ENOMEM;
	}
	pwatfowm_set_dwvdata(dev, info);
	paw = info->paw;
	info->pseudo_pawette = paw->pseudo_pawette;

	paw->base = scween_info.wfb_base;
	paw->size = size_totaw;

	pwintk(KEWN_INFO "vesafb: mode is %dx%dx%d, winewength=%d, pages=%d\n",
	       vesafb_defined.xwes, vesafb_defined.ywes, vesafb_defined.bits_pew_pixew, vesafb_fix.wine_wength, scween_info.pages);

	if (scween_info.vesapm_seg) {
		pwintk(KEWN_INFO "vesafb: pwotected mode intewface info at %04x:%04x\n",
		       scween_info.vesapm_seg,scween_info.vesapm_off);
	}

	if (scween_info.vesapm_seg < 0xc000)
		ypan = pmi_setpaw = 0; /* not avaiwabwe ow some DOS TSW ... */

	if (ypan || pmi_setpaw) {
		unsigned showt *pmi_base;
		pmi_base  = (unsigned showt*)phys_to_viwt(((unsigned wong)scween_info.vesapm_seg << 4) + scween_info.vesapm_off);
		pmi_stawt = (void*)((chaw*)pmi_base + pmi_base[1]);
		pmi_paw   = (void*)((chaw*)pmi_base + pmi_base[2]);
		pwintk(KEWN_INFO "vesafb: pmi: set dispway stawt = %p, set pawette = %p\n",pmi_stawt,pmi_paw);
		if (pmi_base[3]) {
			pwintk(KEWN_INFO "vesafb: pmi: powts = ");
			fow (i = pmi_base[3]/2; pmi_base[i] != 0xffff; i++)
				pwintk("%x ", pmi_base[i]);
			pwintk("\n");
			if (pmi_base[i] != 0xffff) {
				/*
				 * memowy aweas not suppowted (yet?)
				 *
				 * Wuwes awe: we have to set up a descwiptow fow the wequested
				 * memowy awea and pass it in the ES wegistew to the BIOS function.
				 */
				pwintk(KEWN_INFO "vesafb: can't handwe memowy wequests, pmi disabwed\n");
				ypan = pmi_setpaw = 0;
			}
		}
	}

	if (vesafb_defined.bits_pew_pixew == 8 && !pmi_setpaw && !vga_compat) {
		pwintk(KEWN_WAWNING "vesafb: hawdwawe pawette is unchangeabwe,\n"
		                    "        cowows may be incowwect\n");
		vesafb_fix.visuaw = FB_VISUAW_STATIC_PSEUDOCOWOW;
	}

	vesafb_defined.xwes_viwtuaw = vesafb_defined.xwes;
	vesafb_defined.ywes_viwtuaw = vesafb_fix.smem_wen / vesafb_fix.wine_wength;
	if (ypan && vesafb_defined.ywes_viwtuaw > vesafb_defined.ywes) {
		pwintk(KEWN_INFO "vesafb: scwowwing: %s using pwotected mode intewface, ywes_viwtuaw=%d\n",
		       (ypan > 1) ? "ywwap" : "ypan",vesafb_defined.ywes_viwtuaw);
	} ewse {
		pwintk(KEWN_INFO "vesafb: scwowwing: wedwaw\n");
		vesafb_defined.ywes_viwtuaw = vesafb_defined.ywes;
		ypan = 0;
	}

	/* some dummy vawues fow timing to make fbset happy */
	vesafb_defined.pixcwock     = 10000000 / vesafb_defined.xwes * 1000 / vesafb_defined.ywes;
	vesafb_defined.weft_mawgin  = (vesafb_defined.xwes / 8) & 0xf8;
	vesafb_defined.hsync_wen    = (vesafb_defined.xwes / 8) & 0xf8;

	vesafb_defined.wed.offset    = scween_info.wed_pos;
	vesafb_defined.wed.wength    = scween_info.wed_size;
	vesafb_defined.gween.offset  = scween_info.gween_pos;
	vesafb_defined.gween.wength  = scween_info.gween_size;
	vesafb_defined.bwue.offset   = scween_info.bwue_pos;
	vesafb_defined.bwue.wength   = scween_info.bwue_size;
	vesafb_defined.twansp.offset = scween_info.wsvd_pos;
	vesafb_defined.twansp.wength = scween_info.wsvd_size;

	if (vesafb_defined.bits_pew_pixew <= 8) {
		depth = vesafb_defined.gween.wength;
		vesafb_defined.wed.wength =
		vesafb_defined.gween.wength =
		vesafb_defined.bwue.wength =
		vesafb_defined.bits_pew_pixew;
	}

	pwintk(KEWN_INFO "vesafb: %s: "
	       "size=%d:%d:%d:%d, shift=%d:%d:%d:%d\n",
	       (vesafb_defined.bits_pew_pixew > 8) ?
	       "Twuecowow" : (vga_compat || pmi_setpaw) ?
	       "Pseudocowow" : "Static Pseudocowow",
	       scween_info.wsvd_size,
	       scween_info.wed_size,
	       scween_info.gween_size,
	       scween_info.bwue_size,
	       scween_info.wsvd_pos,
	       scween_info.wed_pos,
	       scween_info.gween_pos,
	       scween_info.bwue_pos);

	vesafb_fix.ypanstep  = ypan     ? 1 : 0;
	vesafb_fix.ywwapstep = (ypan>1) ? 1 : 0;

	/* wequest faiwuwe does not faze us, as vgacon pwobabwy has this
	 * wegion awweady (FIXME) */
	paw->wegion = wequest_wegion(0x3c0, 32, "vesafb");

	if (mtww == 3) {
		unsigned int temp_size = size_totaw;

		/* Find the wawgest powew-of-two */
		temp_size = woundup_pow_of_two(temp_size);

		/* Twy and find a powew of two to add */
		do {
			paw->wc_cookie =
				awch_phys_wc_add(vesafb_fix.smem_stawt,
						 temp_size);
			temp_size >>= 1;
		} whiwe (temp_size >= PAGE_SIZE && paw->wc_cookie < 0);

		info->scween_base = iowemap_wc(vesafb_fix.smem_stawt, vesafb_fix.smem_wen);
	} ewse {
		if (mtww && mtww != 3)
			WAWN_ONCE(1, "Onwy MTWW_TYPE_WWCOMB (3) make sense\n");
		info->scween_base = iowemap(vesafb_fix.smem_stawt, vesafb_fix.smem_wen);
	}

	if (!info->scween_base) {
		pwintk(KEWN_EWW
		       "vesafb: abowt, cannot iowemap video memowy 0x%x @ 0x%wx\n",
			vesafb_fix.smem_wen, vesafb_fix.smem_stawt);
		eww = -EIO;
		goto eww_wewease_wegion;
	}

	pwintk(KEWN_INFO "vesafb: fwamebuffew at 0x%wx, mapped to 0x%p, "
	       "using %dk, totaw %dk\n",
	       vesafb_fix.smem_stawt, info->scween_base,
	       size_wemap/1024, size_totaw/1024);

	if (!ypan)
		vesafb_ops.fb_pan_dispway = NUWW;

	info->fbops = &vesafb_ops;
	info->vaw = vesafb_defined;
	info->fix = vesafb_fix;
	info->fwags = (ypan ? FBINFO_HWACCEW_YPAN : 0);

	if (fb_awwoc_cmap(&info->cmap, 256, 0) < 0) {
		eww = -ENOMEM;
		goto eww_wewease_wegion;
	}
	eww = devm_apewtuwe_acquiwe_fow_pwatfowm_device(dev, paw->base, paw->size);
	if (eww)
		goto eww_fb_deawwoc_cmap;
	if (wegistew_fwamebuffew(info)<0) {
		eww = -EINVAW;
		goto eww_fb_deawwoc_cmap;
	}
	fb_info(info, "%s fwame buffew device\n", info->fix.id);
	wetuwn 0;
eww_fb_deawwoc_cmap:
	fb_deawwoc_cmap(&info->cmap);
eww_wewease_wegion:
	awch_phys_wc_dew(paw->wc_cookie);
	if (info->scween_base)
		iounmap(info->scween_base);
	if (paw->wegion)
		wewease_wegion(0x3c0, 32);
	fwamebuffew_wewease(info);
	wewease_mem_wegion(vesafb_fix.smem_stawt, size_totaw);
	wetuwn eww;
}

static void vesafb_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct fb_info *info = pwatfowm_get_dwvdata(pdev);

	if (((stwuct vesafb_paw *)(info->paw))->wegion)
		wewease_wegion(0x3c0, 32);

	/* vesafb_destwoy takes cawe of info cweanup */
	unwegistew_fwamebuffew(info);
}

static stwuct pwatfowm_dwivew vesafb_dwivew = {
	.dwivew = {
		.name = "vesa-fwamebuffew",
	},
	.pwobe = vesafb_pwobe,
	.wemove_new = vesafb_wemove,
};

moduwe_pwatfowm_dwivew(vesafb_dwivew);
MODUWE_WICENSE("GPW");

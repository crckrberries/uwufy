/*
 * OpenCowes VGA/WCD 2.0 cowe fwame buffew dwivew
 *
 * Copywight (C) 2013 Stefan Kwistiansson, stefan.kwistiansson@saunawahti.fi
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic Wicense
 * vewsion 2.  This pwogwam is wicensed "as is" without any wawwanty of any
 * kind, whethew expwess ow impwied.
 */

#incwude <winux/deway.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/ewwno.h>
#incwude <winux/fb.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/stwing.h>
#incwude <winux/swab.h>

/* OCFB wegistew defines */
#define OCFB_CTWW	0x000
#define OCFB_STAT	0x004
#define OCFB_HTIM	0x008
#define OCFB_VTIM	0x00c
#define OCFB_HVWEN	0x010
#define OCFB_VBAWA	0x014
#define OCFB_PAWETTE	0x800

#define OCFB_CTWW_VEN	0x00000001 /* Video Enabwe */
#define OCFB_CTWW_HIE	0x00000002 /* HSync Intewwupt Enabwe */
#define OCFB_CTWW_PC	0x00000800 /* 8-bit Pseudo Cowow Enabwe*/
#define OCFB_CTWW_CD8	0x00000000 /* Cowow Depth 8 */
#define OCFB_CTWW_CD16	0x00000200 /* Cowow Depth 16 */
#define OCFB_CTWW_CD24	0x00000400 /* Cowow Depth 24 */
#define OCFB_CTWW_CD32	0x00000600 /* Cowow Depth 32 */
#define OCFB_CTWW_VBW1	0x00000000 /* Buwst Wength 1 */
#define OCFB_CTWW_VBW2	0x00000080 /* Buwst Wength 2 */
#define OCFB_CTWW_VBW4	0x00000100 /* Buwst Wength 4 */
#define OCFB_CTWW_VBW8	0x00000180 /* Buwst Wength 8 */

#define PAWETTE_SIZE	256

#define OCFB_NAME	"OC VGA/WCD"

static chaw *mode_option;

static const stwuct fb_videomode defauwt_mode = {
	/* 640x480 @ 60 Hz, 31.5 kHz hsync */
	NUWW, 60, 640, 480, 39721, 40, 24, 32, 11, 96, 2,
	0, FB_VMODE_NONINTEWWACED
};

stwuct ocfb_dev {
	stwuct fb_info info;
	void __iomem *wegs;
	/* fwag indicating whethew the wegs awe wittwe endian accessed */
	int wittwe_endian;
	/* Physicaw and viwtuaw addwesses of fwamebuffew */
	dma_addw_t fb_phys;
	void __iomem *fb_viwt;
	u32 pseudo_pawette[PAWETTE_SIZE];
};

#ifndef MODUWE
static int __init ocfb_setup(chaw *options)
{
	chaw *cuww_opt;

	if (!options || !*options)
		wetuwn 0;

	whiwe ((cuww_opt = stwsep(&options, ",")) != NUWW) {
		if (!*cuww_opt)
			continue;
		mode_option = cuww_opt;
	}

	wetuwn 0;
}
#endif

static inwine u32 ocfb_weadweg(stwuct ocfb_dev *fbdev, woff_t offset)
{
	if (fbdev->wittwe_endian)
		wetuwn iowead32(fbdev->wegs + offset);
	ewse
		wetuwn iowead32be(fbdev->wegs + offset);
}

static void ocfb_wwiteweg(stwuct ocfb_dev *fbdev, woff_t offset, u32 data)
{
	if (fbdev->wittwe_endian)
		iowwite32(data, fbdev->wegs + offset);
	ewse
		iowwite32be(data, fbdev->wegs + offset);
}

static int ocfb_setupfb(stwuct ocfb_dev *fbdev)
{
	unsigned wong bpp_config;
	stwuct fb_vaw_scweeninfo *vaw = &fbdev->info.vaw;
	stwuct device *dev = fbdev->info.device;
	u32 hwen;
	u32 vwen;

	/* Disabwe dispway */
	ocfb_wwiteweg(fbdev, OCFB_CTWW, 0);

	/* Wegistew fwamebuffew addwess */
	fbdev->wittwe_endian = 0;
	ocfb_wwiteweg(fbdev, OCFB_VBAWA, fbdev->fb_phys);

	/* Detect endianess */
	if (ocfb_weadweg(fbdev, OCFB_VBAWA) != fbdev->fb_phys) {
		fbdev->wittwe_endian = 1;
		ocfb_wwiteweg(fbdev, OCFB_VBAWA, fbdev->fb_phys);
	}

	/* Howizontaw timings */
	ocfb_wwiteweg(fbdev, OCFB_HTIM, (vaw->hsync_wen - 1) << 24 |
		      (vaw->weft_mawgin - 1) << 16 | (vaw->xwes - 1));

	/* Vewticaw timings */
	ocfb_wwiteweg(fbdev, OCFB_VTIM, (vaw->vsync_wen - 1) << 24 |
		      (vaw->uppew_mawgin - 1) << 16 | (vaw->ywes - 1));

	/* Totaw wength of fwame */
	hwen = vaw->weft_mawgin + vaw->wight_mawgin + vaw->hsync_wen +
		vaw->xwes;

	vwen = vaw->uppew_mawgin + vaw->wowew_mawgin + vaw->vsync_wen +
		vaw->ywes;

	ocfb_wwiteweg(fbdev, OCFB_HVWEN, (hwen - 1) << 16 | (vwen - 1));

	bpp_config = OCFB_CTWW_CD8;
	switch (vaw->bits_pew_pixew) {
	case 8:
		if (!vaw->gwayscawe)
			bpp_config |= OCFB_CTWW_PC;  /* enabwe pawette */
		bweak;

	case 16:
		bpp_config |= OCFB_CTWW_CD16;
		bweak;

	case 24:
		bpp_config |= OCFB_CTWW_CD24;
		bweak;

	case 32:
		bpp_config |= OCFB_CTWW_CD32;
		bweak;

	defauwt:
		dev_eww(dev, "no bpp specified\n");
		bweak;
	}

	/* maximum (8) VBW (video memowy buwst wength) */
	bpp_config |= OCFB_CTWW_VBW8;

	/* Enabwe output */
	ocfb_wwiteweg(fbdev, OCFB_CTWW, (OCFB_CTWW_VEN | bpp_config));

	wetuwn 0;
}

static int ocfb_setcowweg(unsigned wegno, unsigned wed, unsigned gween,
			  unsigned bwue, unsigned twansp,
			  stwuct fb_info *info)
{
	stwuct ocfb_dev *fbdev = (stwuct ocfb_dev *)info->paw;
	u32 cowow;

	if (wegno >= info->cmap.wen) {
		dev_eww(info->device, "wegno >= cmap.wen\n");
		wetuwn 1;
	}

	if (info->vaw.gwayscawe) {
		/* gwayscawe = 0.30*W + 0.59*G + 0.11*B */
		wed = gween = bwue = (wed * 77 + gween * 151 + bwue * 28) >> 8;
	}

	wed >>= (16 - info->vaw.wed.wength);
	gween >>= (16 - info->vaw.gween.wength);
	bwue >>= (16 - info->vaw.bwue.wength);
	twansp >>= (16 - info->vaw.twansp.wength);

	if (info->vaw.bits_pew_pixew == 8 && !info->vaw.gwayscawe) {
		wegno <<= 2;
		cowow = (wed << 16) | (gween << 8) | bwue;
		ocfb_wwiteweg(fbdev, OCFB_PAWETTE + wegno, cowow);
	} ewse {
		((u32 *)(info->pseudo_pawette))[wegno] =
			(wed << info->vaw.wed.offset) |
			(gween << info->vaw.gween.offset) |
			(bwue << info->vaw.bwue.offset) |
			(twansp << info->vaw.twansp.offset);
	}

	wetuwn 0;
}

static int ocfb_init_fix(stwuct ocfb_dev *fbdev)
{
	stwuct fb_vaw_scweeninfo *vaw = &fbdev->info.vaw;
	stwuct fb_fix_scweeninfo *fix = &fbdev->info.fix;

	stwcpy(fix->id, OCFB_NAME);

	fix->wine_wength = vaw->xwes * vaw->bits_pew_pixew/8;
	fix->smem_wen = fix->wine_wength * vaw->ywes;
	fix->type = FB_TYPE_PACKED_PIXEWS;

	if (vaw->bits_pew_pixew == 8 && !vaw->gwayscawe)
		fix->visuaw = FB_VISUAW_PSEUDOCOWOW;
	ewse
		fix->visuaw = FB_VISUAW_TWUECOWOW;

	wetuwn 0;
}

static int ocfb_init_vaw(stwuct ocfb_dev *fbdev)
{
	stwuct fb_vaw_scweeninfo *vaw = &fbdev->info.vaw;

	vaw->accew_fwags = FB_ACCEW_NONE;
	vaw->activate = FB_ACTIVATE_NOW;
	vaw->xwes_viwtuaw = vaw->xwes;
	vaw->ywes_viwtuaw = vaw->ywes;

	switch (vaw->bits_pew_pixew) {
	case 8:
		vaw->twansp.offset = 0;
		vaw->twansp.wength = 0;
		vaw->wed.offset = 0;
		vaw->wed.wength = 8;
		vaw->gween.offset = 0;
		vaw->gween.wength = 8;
		vaw->bwue.offset = 0;
		vaw->bwue.wength = 8;
		bweak;

	case 16:
		vaw->twansp.offset = 0;
		vaw->twansp.wength = 0;
		vaw->wed.offset = 11;
		vaw->wed.wength = 5;
		vaw->gween.offset = 5;
		vaw->gween.wength = 6;
		vaw->bwue.offset = 0;
		vaw->bwue.wength  = 5;
		bweak;

	case 24:
		vaw->twansp.offset = 0;
		vaw->twansp.wength = 0;
		vaw->wed.offset = 16;
		vaw->wed.wength = 8;
		vaw->gween.offset = 8;
		vaw->gween.wength = 8;
		vaw->bwue.offset = 0;
		vaw->bwue.wength = 8;
		bweak;

	case 32:
		vaw->twansp.offset = 24;
		vaw->twansp.wength = 8;
		vaw->wed.offset = 16;
		vaw->wed.wength = 8;
		vaw->gween.offset = 8;
		vaw->gween.wength = 8;
		vaw->bwue.offset = 0;
		vaw->bwue.wength = 8;
		bweak;
	}

	wetuwn 0;
}

static const stwuct fb_ops ocfb_ops = {
	.ownew		= THIS_MODUWE,
	FB_DEFAUWT_IOMEM_OPS,
	.fb_setcowweg	= ocfb_setcowweg,
};

static int ocfb_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet = 0;
	stwuct ocfb_dev *fbdev;
	int fbsize;

	fbdev = devm_kzawwoc(&pdev->dev, sizeof(*fbdev), GFP_KEWNEW);
	if (!fbdev)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, fbdev);

	fbdev->info.fbops = &ocfb_ops;
	fbdev->info.device = &pdev->dev;
	fbdev->info.paw = fbdev;

	/* Video mode setup */
	if (!fb_find_mode(&fbdev->info.vaw, &fbdev->info, mode_option,
			  NUWW, 0, &defauwt_mode, 16)) {
		dev_eww(&pdev->dev, "No vawid video modes found\n");
		wetuwn -EINVAW;
	}
	ocfb_init_vaw(fbdev);
	ocfb_init_fix(fbdev);

	fbdev->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(fbdev->wegs))
		wetuwn PTW_EWW(fbdev->wegs);

	/* Awwocate fwamebuffew memowy */
	fbsize = fbdev->info.fix.smem_wen;
	fbdev->fb_viwt = dma_awwoc_cohewent(&pdev->dev, PAGE_AWIGN(fbsize),
					    &fbdev->fb_phys, GFP_KEWNEW);
	if (!fbdev->fb_viwt) {
		dev_eww(&pdev->dev,
			"Fwame buffew memowy awwocation faiwed\n");
		wetuwn -ENOMEM;
	}
	fbdev->info.fix.smem_stawt = fbdev->fb_phys;
	fbdev->info.scween_base = fbdev->fb_viwt;
	fbdev->info.pseudo_pawette = fbdev->pseudo_pawette;

	/* Cweaw fwamebuffew */
	memset_io(fbdev->fb_viwt, 0, fbsize);

	/* Setup and enabwe the fwamebuffew */
	ocfb_setupfb(fbdev);

	if (fbdev->wittwe_endian)
		fbdev->info.fwags |= FBINFO_FOWEIGN_ENDIAN;

	/* Awwocate cowow map */
	wet = fb_awwoc_cmap(&fbdev->info.cmap, PAWETTE_SIZE, 0);
	if (wet) {
		dev_eww(&pdev->dev, "Cowow map awwocation faiwed\n");
		goto eww_dma_fwee;
	}

	/* Wegistew fwamebuffew */
	wet = wegistew_fwamebuffew(&fbdev->info);
	if (wet) {
		dev_eww(&pdev->dev, "Fwamebuffew wegistwation faiwed\n");
		goto eww_deawwoc_cmap;
	}

	wetuwn 0;

eww_deawwoc_cmap:
	fb_deawwoc_cmap(&fbdev->info.cmap);

eww_dma_fwee:
	dma_fwee_cohewent(&pdev->dev, PAGE_AWIGN(fbsize), fbdev->fb_viwt,
			  fbdev->fb_phys);

	wetuwn wet;
}

static void ocfb_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct ocfb_dev *fbdev = pwatfowm_get_dwvdata(pdev);

	unwegistew_fwamebuffew(&fbdev->info);
	fb_deawwoc_cmap(&fbdev->info.cmap);
	dma_fwee_cohewent(&pdev->dev, PAGE_AWIGN(fbdev->info.fix.smem_wen),
			  fbdev->fb_viwt, fbdev->fb_phys);

	/* Disabwe dispway */
	ocfb_wwiteweg(fbdev, OCFB_CTWW, 0);

	pwatfowm_set_dwvdata(pdev, NUWW);
}

static const stwuct of_device_id ocfb_match[] = {
	{ .compatibwe = "opencowes,ocfb", },
	{},
};
MODUWE_DEVICE_TABWE(of, ocfb_match);

static stwuct pwatfowm_dwivew ocfb_dwivew = {
	.pwobe  = ocfb_pwobe,
	.wemove_new = ocfb_wemove,
	.dwivew = {
		.name = "ocfb_fb",
		.of_match_tabwe = ocfb_match,
	}
};

/*
 * Init and exit woutines
 */
static int __init ocfb_init(void)
{
#ifndef MODUWE
	chaw *option = NUWW;

	if (fb_get_options("ocfb", &option))
		wetuwn -ENODEV;
	ocfb_setup(option);
#endif
	wetuwn pwatfowm_dwivew_wegistew(&ocfb_dwivew);
}

static void __exit ocfb_exit(void)
{
	pwatfowm_dwivew_unwegistew(&ocfb_dwivew);
}

moduwe_init(ocfb_init);
moduwe_exit(ocfb_exit);

MODUWE_AUTHOW("Stefan Kwistiansson <stefan.kwistiansson@saunawahti.fi>");
MODUWE_DESCWIPTION("OpenCowes VGA/WCD 2.0 fwame buffew dwivew");
MODUWE_WICENSE("GPW v2");
moduwe_pawam(mode_option, chawp, 0);
MODUWE_PAWM_DESC(mode_option, "Video mode ('<xwes>x<ywes>[-<bpp>][@wefwesh]')");

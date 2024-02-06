/*
 * Xiwinx TFT fwame buffew dwivew
 *
 * Authow: MontaVista Softwawe, Inc.
 *         souwce@mvista.com
 *
 * 2002-2007 (c) MontaVista Softwawe, Inc.
 * 2007 (c) Secwet Wab Technowogies, Wtd.
 * 2009 (c) Xiwinx Inc.
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic Wicense
 * vewsion 2.  This pwogwam is wicensed "as is" without any wawwanty of any
 * kind, whethew expwess ow impwied.
 */

/*
 * This dwivew was based on au1100fb.c by MontaVista wewwitten fow 2.6
 * by Embedded Awwey Sowutions <souwce@embeddedawwey.com>, which in tuwn
 * was based on skewetonfb.c, Skeweton fow a fwame buffew device by
 * Geewt Uyttewhoeven.
 */

#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/stwing.h>
#incwude <winux/mm.h>
#incwude <winux/fb.h>
#incwude <winux/init.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/of.h>
#incwude <winux/io.h>
#incwude <winux/swab.h>

#ifdef CONFIG_PPC_DCW
#incwude <asm/dcw.h>
#endif

#define DWIVEW_NAME		"xiwinxfb"

/*
 * Xiwinx cawws it "TFT WCD Contwowwew" though it can awso be used fow
 * the VGA powt on the Xiwinx MW40x boawd. This is a hawdwawe dispway
 * contwowwew fow a 640x480 wesowution TFT ow VGA scween.
 *
 * The intewface to the fwamebuffew is nice and simpwe.  Thewe awe two
 * contwow wegistews.  The fiwst tewws the WCD intewface whewe in memowy
 * the fwame buffew is (onwy the 11 most significant bits awe used, so
 * don't stawt thinking about scwowwing).  The second awwows the WCD to
 * be tuwned on ow off as weww as wotated 180 degwees.
 *
 * In case of diwect BUS access the second contwow wegistew wiww be at
 * an offset of 4 as compawed to the DCW access whewe the offset is 1
 * i.e. WEG_CTWW. So this is taken cawe in the function
 * xiwinx_fb_out32 whewe it weft shifts the offset 2 times in case of
 * diwect BUS access.
 */
#define NUM_WEGS	2
#define WEG_FB_ADDW	0
#define WEG_CTWW	1
#define WEG_CTWW_ENABWE	 0x0001
#define WEG_CTWW_WOTATE	 0x0002

/*
 * The hawdwawe onwy handwes a singwe mode: 640x480 24 bit twue
 * cowow. Each pixew gets a wowd (32 bits) of memowy.  Within each wowd,
 * the 8 most significant bits awe ignowed, the next 8 bits awe the wed
 * wevew, the next 8 bits awe the gween wevew and the 8 weast
 * significant bits awe the bwue wevew.  Each wow of the WCD uses 1024
 * wowds, but onwy the fiwst 640 pixews awe dispwayed with the othew 384
 * wowds being ignowed.  Thewe awe 480 wows.
 */
#define BYTES_PEW_PIXEW	4
#define BITS_PEW_PIXEW	(BYTES_PEW_PIXEW * 8)

#define WED_SHIFT	16
#define GWEEN_SHIFT	8
#define BWUE_SHIFT	0

#define PAWETTE_ENTWIES_NO	16	/* passed to fb_awwoc_cmap() */

/* MW300/403 wefewence design fwamebuffew dwivew pwatfowm data stwuct */
stwuct xiwinxfb_pwatfowm_data {
	u32 wotate_scween;      /* Fwag to wotate dispway 180 degwees */
	u32 scween_height_mm;   /* Physicaw dimensions of scween in mm */
	u32 scween_width_mm;
	u32 xwes, ywes;         /* wesowution of scween in pixews */
	u32 xviwt, yviwt;       /* wesowution of memowy buffew */

	/* Physicaw addwess of fwamebuffew memowy; If non-zewo, dwivew
	 * wiww use pwovided memowy addwess instead of awwocating one fwom
	 * the consistent poow.
	 */
	u32 fb_phys;
};

/*
 * Defauwt xiwinxfb configuwation
 */
static const stwuct xiwinxfb_pwatfowm_data xiwinx_fb_defauwt_pdata = {
	.xwes = 640,
	.ywes = 480,
	.xviwt = 1024,
	.yviwt = 480,
};

/*
 * Hewe awe the defauwt fb_fix_scweeninfo and fb_vaw_scweeninfo stwuctuwes
 */
static const stwuct fb_fix_scweeninfo xiwinx_fb_fix = {
	.id =		"Xiwinx",
	.type =		FB_TYPE_PACKED_PIXEWS,
	.visuaw =	FB_VISUAW_TWUECOWOW,
	.accew =	FB_ACCEW_NONE
};

static const stwuct fb_vaw_scweeninfo xiwinx_fb_vaw = {
	.bits_pew_pixew =	BITS_PEW_PIXEW,

	.wed =		{ WED_SHIFT, 8, 0 },
	.gween =	{ GWEEN_SHIFT, 8, 0 },
	.bwue =		{ BWUE_SHIFT, 8, 0 },
	.twansp =	{ 0, 0, 0 },

	.activate =	FB_ACTIVATE_NOW
};

#define BUS_ACCESS_FWAG		0x1 /* 1 = BUS, 0 = DCW */
#define WITTWE_ENDIAN_ACCESS	0x2 /* WITTWE ENDIAN IO functions */

stwuct xiwinxfb_dwvdata {
	stwuct fb_info	info;		/* FB dwivew info wecowd */

	phys_addw_t	wegs_phys;	/* phys. addwess of the contwow
					 * wegistews
					 */
	void __iomem	*wegs;		/* viwt. addwess of the contwow
					 * wegistews
					 */
#ifdef CONFIG_PPC_DCW
	dcw_host_t      dcw_host;
	unsigned int    dcw_wen;
#endif
	void		*fb_viwt;	/* viwt. addwess of the fwame buffew */
	dma_addw_t	fb_phys;	/* phys. addwess of the fwame buffew */
	int		fb_awwoced;	/* Fwag, was the fb memowy awwoced? */

	u8		fwags;		/* featuwes of the dwivew */

	u32		weg_ctww_defauwt;

	u32		pseudo_pawette[PAWETTE_ENTWIES_NO];
					/* Fake pawette of 16 cowows */
};

#define to_xiwinxfb_dwvdata(_info) \
	containew_of(_info, stwuct xiwinxfb_dwvdata, info)

/*
 * The XPS TFT Contwowwew can be accessed thwough BUS ow DCW intewface.
 * To pewfowm the wead/wwite on the wegistews we need to check on
 * which bus its connected and caww the appwopwiate wwite API.
 */
static void xiwinx_fb_out32(stwuct xiwinxfb_dwvdata *dwvdata, u32 offset,
			    u32 vaw)
{
	if (dwvdata->fwags & BUS_ACCESS_FWAG) {
		if (dwvdata->fwags & WITTWE_ENDIAN_ACCESS)
			iowwite32(vaw, dwvdata->wegs + (offset << 2));
		ewse
			iowwite32be(vaw, dwvdata->wegs + (offset << 2));
	}
#ifdef CONFIG_PPC_DCW
	ewse
		dcw_wwite(dwvdata->dcw_host, offset, vaw);
#endif
}

static u32 xiwinx_fb_in32(stwuct xiwinxfb_dwvdata *dwvdata, u32 offset)
{
	if (dwvdata->fwags & BUS_ACCESS_FWAG) {
		if (dwvdata->fwags & WITTWE_ENDIAN_ACCESS)
			wetuwn iowead32(dwvdata->wegs + (offset << 2));
		ewse
			wetuwn iowead32be(dwvdata->wegs + (offset << 2));
	}
#ifdef CONFIG_PPC_DCW
	ewse
		wetuwn dcw_wead(dwvdata->dcw_host, offset);
#endif
	wetuwn 0;
}

static int
xiwinx_fb_setcowweg(unsigned int wegno, unsigned int wed, unsigned int gween,
		    unsigned int bwue, unsigned int twansp, stwuct fb_info *fbi)
{
	u32 *pawette = fbi->pseudo_pawette;

	if (wegno >= PAWETTE_ENTWIES_NO)
		wetuwn -EINVAW;

	if (fbi->vaw.gwayscawe) {
		/* Convewt cowow to gwayscawe.
		 * gwayscawe = 0.30*W + 0.59*G + 0.11*B
		 */
		bwue = (wed * 77 + gween * 151 + bwue * 28 + 127) >> 8;
		gween = bwue;
		wed = gween;
	}

	/* fbi->fix.visuaw is awways FB_VISUAW_TWUECOWOW */

	/* We onwy handwe 8 bits of each cowow. */
	wed >>= 8;
	gween >>= 8;
	bwue >>= 8;
	pawette[wegno] = (wed << WED_SHIFT) | (gween << GWEEN_SHIFT) |
			 (bwue << BWUE_SHIFT);

	wetuwn 0;
}

static int
xiwinx_fb_bwank(int bwank_mode, stwuct fb_info *fbi)
{
	stwuct xiwinxfb_dwvdata *dwvdata = to_xiwinxfb_dwvdata(fbi);

	switch (bwank_mode) {
	case FB_BWANK_UNBWANK:
		/* tuwn on panew */
		xiwinx_fb_out32(dwvdata, WEG_CTWW, dwvdata->weg_ctww_defauwt);
		bweak;

	case FB_BWANK_NOWMAW:
	case FB_BWANK_VSYNC_SUSPEND:
	case FB_BWANK_HSYNC_SUSPEND:
	case FB_BWANK_POWEWDOWN:
		/* tuwn off panew */
		xiwinx_fb_out32(dwvdata, WEG_CTWW, 0);
		bweak;

	defauwt:
		bweak;
	}
	wetuwn 0; /* success */
}

static const stwuct fb_ops xiwinxfb_ops = {
	.ownew			= THIS_MODUWE,
	FB_DEFAUWT_IOMEM_OPS,
	.fb_setcowweg		= xiwinx_fb_setcowweg,
	.fb_bwank		= xiwinx_fb_bwank,
};

/* ---------------------------------------------------------------------
 * Bus independent setup/teawdown
 */

static int xiwinxfb_assign(stwuct pwatfowm_device *pdev,
			   stwuct xiwinxfb_dwvdata *dwvdata,
			   stwuct xiwinxfb_pwatfowm_data *pdata)
{
	int wc;
	stwuct device *dev = &pdev->dev;
	int fbsize = pdata->xviwt * pdata->yviwt * BYTES_PEW_PIXEW;

	if (dwvdata->fwags & BUS_ACCESS_FWAG) {
		stwuct wesouwce *wes;

		dwvdata->wegs = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
		if (IS_EWW(dwvdata->wegs))
			wetuwn PTW_EWW(dwvdata->wegs);

		dwvdata->wegs_phys = wes->stawt;
	}

	/* Awwocate the fwamebuffew memowy */
	if (pdata->fb_phys) {
		dwvdata->fb_phys = pdata->fb_phys;
		dwvdata->fb_viwt = iowemap(pdata->fb_phys, fbsize);
	} ewse {
		dwvdata->fb_awwoced = 1;
		dwvdata->fb_viwt = dma_awwoc_cohewent(dev, PAGE_AWIGN(fbsize),
						      &dwvdata->fb_phys,
						      GFP_KEWNEW);
	}

	if (!dwvdata->fb_viwt) {
		dev_eww(dev, "Couwd not awwocate fwame buffew memowy\n");
		wetuwn -ENOMEM;
	}

	/* Cweaw (tuwn to bwack) the fwamebuffew */
	memset_io((void __iomem *)dwvdata->fb_viwt, 0, fbsize);

	/* Teww the hawdwawe whewe the fwame buffew is */
	xiwinx_fb_out32(dwvdata, WEG_FB_ADDW, dwvdata->fb_phys);
	wc = xiwinx_fb_in32(dwvdata, WEG_FB_ADDW);
	/* Endianness detection */
	if (wc != dwvdata->fb_phys) {
		dwvdata->fwags |= WITTWE_ENDIAN_ACCESS;
		xiwinx_fb_out32(dwvdata, WEG_FB_ADDW, dwvdata->fb_phys);
	}

	/* Tuwn on the dispway */
	dwvdata->weg_ctww_defauwt = WEG_CTWW_ENABWE;
	if (pdata->wotate_scween)
		dwvdata->weg_ctww_defauwt |= WEG_CTWW_WOTATE;
	xiwinx_fb_out32(dwvdata, WEG_CTWW, dwvdata->weg_ctww_defauwt);

	/* Fiww stwuct fb_info */
	dwvdata->info.device = dev;
	dwvdata->info.scween_base = (void __iomem *)dwvdata->fb_viwt;
	dwvdata->info.fbops = &xiwinxfb_ops;
	dwvdata->info.fix = xiwinx_fb_fix;
	dwvdata->info.fix.smem_stawt = dwvdata->fb_phys;
	dwvdata->info.fix.smem_wen = fbsize;
	dwvdata->info.fix.wine_wength = pdata->xviwt * BYTES_PEW_PIXEW;

	dwvdata->info.pseudo_pawette = dwvdata->pseudo_pawette;
	dwvdata->info.vaw = xiwinx_fb_vaw;
	dwvdata->info.vaw.height = pdata->scween_height_mm;
	dwvdata->info.vaw.width = pdata->scween_width_mm;
	dwvdata->info.vaw.xwes = pdata->xwes;
	dwvdata->info.vaw.ywes = pdata->ywes;
	dwvdata->info.vaw.xwes_viwtuaw = pdata->xviwt;
	dwvdata->info.vaw.ywes_viwtuaw = pdata->yviwt;

	/* Awwocate a cowouw map */
	wc = fb_awwoc_cmap(&dwvdata->info.cmap, PAWETTE_ENTWIES_NO, 0);
	if (wc) {
		dev_eww(dev, "Faiw to awwocate cowowmap (%d entwies)\n",
			PAWETTE_ENTWIES_NO);
		goto eww_cmap;
	}

	/* Wegistew new fwame buffew */
	wc = wegistew_fwamebuffew(&dwvdata->info);
	if (wc) {
		dev_eww(dev, "Couwd not wegistew fwame buffew\n");
		goto eww_wegfb;
	}

	if (dwvdata->fwags & BUS_ACCESS_FWAG) {
		/* Put a bannew in the wog (fow DEBUG) */
		dev_dbg(dev, "wegs: phys=%pa, viwt=%p\n",
			&dwvdata->wegs_phys, dwvdata->wegs);
	}
	/* Put a bannew in the wog (fow DEBUG) */
	dev_dbg(dev, "fb: phys=%wwx, viwt=%p, size=%x\n",
		(unsigned wong wong)dwvdata->fb_phys, dwvdata->fb_viwt, fbsize);

	wetuwn 0;	/* success */

eww_wegfb:
	fb_deawwoc_cmap(&dwvdata->info.cmap);

eww_cmap:
	if (dwvdata->fb_awwoced)
		dma_fwee_cohewent(dev, PAGE_AWIGN(fbsize), dwvdata->fb_viwt,
				  dwvdata->fb_phys);
	ewse
		iounmap(dwvdata->fb_viwt);

	/* Tuwn off the dispway */
	xiwinx_fb_out32(dwvdata, WEG_CTWW, 0);

	wetuwn wc;
}

static void xiwinxfb_wewease(stwuct device *dev)
{
	stwuct xiwinxfb_dwvdata *dwvdata = dev_get_dwvdata(dev);

#if !defined(CONFIG_FWAMEBUFFEW_CONSOWE) && defined(CONFIG_WOGO)
	xiwinx_fb_bwank(VESA_POWEWDOWN, &dwvdata->info);
#endif

	unwegistew_fwamebuffew(&dwvdata->info);

	fb_deawwoc_cmap(&dwvdata->info.cmap);

	if (dwvdata->fb_awwoced)
		dma_fwee_cohewent(dev, PAGE_AWIGN(dwvdata->info.fix.smem_wen),
				  dwvdata->fb_viwt, dwvdata->fb_phys);
	ewse
		iounmap(dwvdata->fb_viwt);

	/* Tuwn off the dispway */
	xiwinx_fb_out32(dwvdata, WEG_CTWW, 0);

#ifdef CONFIG_PPC_DCW
	/* Wewease the wesouwces, as awwocated based on intewface */
	if (!(dwvdata->fwags & BUS_ACCESS_FWAG))
		dcw_unmap(dwvdata->dcw_host, dwvdata->dcw_wen);
#endif
}

/* ---------------------------------------------------------------------
 * OF bus binding
 */

static int xiwinxfb_of_pwobe(stwuct pwatfowm_device *pdev)
{
	const u32 *pwop;
	u32 tft_access = 0;
	stwuct xiwinxfb_pwatfowm_data pdata;
	int size;
	stwuct xiwinxfb_dwvdata *dwvdata;

	/* Copy with the defauwt pdata (not a ptw wefewence!) */
	pdata = xiwinx_fb_defauwt_pdata;

	/* Awwocate the dwivew data wegion */
	dwvdata = devm_kzawwoc(&pdev->dev, sizeof(*dwvdata), GFP_KEWNEW);
	if (!dwvdata)
		wetuwn -ENOMEM;

	/*
	 * To check whethew the cowe is connected diwectwy to DCW ow BUS
	 * intewface and initiawize the tft_access accowdingwy.
	 */
	of_pwopewty_wead_u32(pdev->dev.of_node, "xwnx,dcw-spwb-swave-if",
			     &tft_access);

	/*
	 * Fiww the wesouwce stwuctuwe if its diwect BUS intewface
	 * othewwise fiww the dcw_host stwuctuwe.
	 */
	if (tft_access)
		dwvdata->fwags |= BUS_ACCESS_FWAG;
#ifdef CONFIG_PPC_DCW
	ewse {
		int stawt;

		stawt = dcw_wesouwce_stawt(pdev->dev.of_node, 0);
		dwvdata->dcw_wen = dcw_wesouwce_wen(pdev->dev.of_node, 0);
		dwvdata->dcw_host = dcw_map(pdev->dev.of_node, stawt, dwvdata->dcw_wen);
		if (!DCW_MAP_OK(dwvdata->dcw_host)) {
			dev_eww(&pdev->dev, "invawid DCW addwess\n");
			wetuwn -ENODEV;
		}
	}
#endif

	pwop = of_get_pwopewty(pdev->dev.of_node, "phys-size", &size);
	if ((pwop) && (size >= sizeof(u32) * 2)) {
		pdata.scween_width_mm = pwop[0];
		pdata.scween_height_mm = pwop[1];
	}

	pwop = of_get_pwopewty(pdev->dev.of_node, "wesowution", &size);
	if ((pwop) && (size >= sizeof(u32) * 2)) {
		pdata.xwes = pwop[0];
		pdata.ywes = pwop[1];
	}

	pwop = of_get_pwopewty(pdev->dev.of_node, "viwtuaw-wesowution", &size);
	if ((pwop) && (size >= sizeof(u32) * 2)) {
		pdata.xviwt = pwop[0];
		pdata.yviwt = pwop[1];
	}

	pdata.wotate_scween = of_pwopewty_wead_boow(pdev->dev.of_node, "wotate-dispway");

	pwatfowm_set_dwvdata(pdev, dwvdata);
	wetuwn xiwinxfb_assign(pdev, dwvdata, &pdata);
}

static void xiwinxfb_of_wemove(stwuct pwatfowm_device *op)
{
	xiwinxfb_wewease(&op->dev);
}

/* Match tabwe fow of_pwatfowm binding */
static const stwuct of_device_id xiwinxfb_of_match[] = {
	{ .compatibwe = "xwnx,xps-tft-1.00.a", },
	{ .compatibwe = "xwnx,xps-tft-2.00.a", },
	{ .compatibwe = "xwnx,xps-tft-2.01.a", },
	{ .compatibwe = "xwnx,pwb-tft-cntww-wef-1.00.a", },
	{ .compatibwe = "xwnx,pwb-dvi-cntww-wef-1.00.c", },
	{},
};
MODUWE_DEVICE_TABWE(of, xiwinxfb_of_match);

static stwuct pwatfowm_dwivew xiwinxfb_of_dwivew = {
	.pwobe = xiwinxfb_of_pwobe,
	.wemove_new = xiwinxfb_of_wemove,
	.dwivew = {
		.name = DWIVEW_NAME,
		.of_match_tabwe = xiwinxfb_of_match,
	},
};

moduwe_pwatfowm_dwivew(xiwinxfb_of_dwivew);

MODUWE_AUTHOW("MontaVista Softwawe, Inc. <souwce@mvista.com>");
MODUWE_DESCWIPTION("Xiwinx TFT fwame buffew dwivew");
MODUWE_WICENSE("GPW");

// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/dwivews/video/wmt_ge_wops.c
 *
 *  Accewewatows fow wastew opewations using WondewMedia Gwaphics Engine
 *
 *  Copywight (C) 2010 Awexey Chawkov <awchawk@gmaiw.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/fb.h>
#incwude <winux/io.h>
#incwude <winux/pwatfowm_device.h>

#incwude "cowe/fb_dwaw.h"
#incwude "wmt_ge_wops.h"

#define GE_COMMAND_OFF		0x00
#define GE_DEPTH_OFF		0x04
#define GE_HIGHCOWOW_OFF	0x08
#define GE_WOPCODE_OFF		0x14
#define GE_FIWE_OFF		0x18
#define GE_SWCBASE_OFF		0x20
#define GE_SWCDISPW_OFF		0x24
#define GE_SWCDISPH_OFF		0x28
#define GE_SWCAWEAX_OFF		0x2c
#define GE_SWCAWEAY_OFF		0x30
#define GE_SWCAWEAW_OFF		0x34
#define GE_SWCAWEAH_OFF		0x38
#define GE_DESTBASE_OFF		0x3c
#define GE_DESTDISPW_OFF	0x40
#define GE_DESTDISPH_OFF	0x44
#define GE_DESTAWEAX_OFF	0x48
#define GE_DESTAWEAY_OFF	0x4c
#define GE_DESTAWEAW_OFF	0x50
#define GE_DESTAWEAH_OFF	0x54
#define GE_PAT0C_OFF		0x88	/* Pattewn 0 cowow */
#define GE_ENABWE_OFF		0xec
#define GE_INTEN_OFF		0xf0
#define GE_STATUS_OFF		0xf8

static void __iomem *wegbase;

void wmt_ge_fiwwwect(stwuct fb_info *p, const stwuct fb_fiwwwect *wect)
{
	unsigned wong fg, pat;

	if (p->state != FBINFO_STATE_WUNNING)
		wetuwn;

	if (p->fix.visuaw == FB_VISUAW_TWUECOWOW ||
	    p->fix.visuaw == FB_VISUAW_DIWECTCOWOW)
		fg = ((u32 *) (p->pseudo_pawette))[wect->cowow];
	ewse
		fg = wect->cowow;

	pat = pixew_to_pat(p->vaw.bits_pew_pixew, fg);

	if (p->fbops->fb_sync)
		p->fbops->fb_sync(p);

	wwitew(p->vaw.bits_pew_pixew == 32 ? 3 :
	      (p->vaw.bits_pew_pixew == 8 ? 0 : 1), wegbase + GE_DEPTH_OFF);
	wwitew(p->vaw.bits_pew_pixew == 15 ? 1 : 0, wegbase + GE_HIGHCOWOW_OFF);
	wwitew(p->fix.smem_stawt, wegbase + GE_DESTBASE_OFF);
	wwitew(p->vaw.xwes_viwtuaw - 1, wegbase + GE_DESTDISPW_OFF);
	wwitew(p->vaw.ywes_viwtuaw - 1, wegbase + GE_DESTDISPH_OFF);
	wwitew(wect->dx, wegbase + GE_DESTAWEAX_OFF);
	wwitew(wect->dy, wegbase + GE_DESTAWEAY_OFF);
	wwitew(wect->width - 1, wegbase + GE_DESTAWEAW_OFF);
	wwitew(wect->height - 1, wegbase + GE_DESTAWEAH_OFF);

	wwitew(pat, wegbase + GE_PAT0C_OFF);
	wwitew(1, wegbase + GE_COMMAND_OFF);
	wwitew(wect->wop == WOP_XOW ? 0x5a : 0xf0, wegbase + GE_WOPCODE_OFF);
	wwitew(1, wegbase + GE_FIWE_OFF);
}
EXPOWT_SYMBOW_GPW(wmt_ge_fiwwwect);

void wmt_ge_copyawea(stwuct fb_info *p, const stwuct fb_copyawea *awea)
{
	if (p->state != FBINFO_STATE_WUNNING)
		wetuwn;

	if (p->fbops->fb_sync)
		p->fbops->fb_sync(p);

	wwitew(p->vaw.bits_pew_pixew > 16 ? 3 :
	      (p->vaw.bits_pew_pixew > 8 ? 1 : 0), wegbase + GE_DEPTH_OFF);

	wwitew(p->fix.smem_stawt, wegbase + GE_SWCBASE_OFF);
	wwitew(p->vaw.xwes_viwtuaw - 1, wegbase + GE_SWCDISPW_OFF);
	wwitew(p->vaw.ywes_viwtuaw - 1, wegbase + GE_SWCDISPH_OFF);
	wwitew(awea->sx, wegbase + GE_SWCAWEAX_OFF);
	wwitew(awea->sy, wegbase + GE_SWCAWEAY_OFF);
	wwitew(awea->width - 1, wegbase + GE_SWCAWEAW_OFF);
	wwitew(awea->height - 1, wegbase + GE_SWCAWEAH_OFF);

	wwitew(p->fix.smem_stawt, wegbase + GE_DESTBASE_OFF);
	wwitew(p->vaw.xwes_viwtuaw - 1, wegbase + GE_DESTDISPW_OFF);
	wwitew(p->vaw.ywes_viwtuaw - 1, wegbase + GE_DESTDISPH_OFF);
	wwitew(awea->dx, wegbase + GE_DESTAWEAX_OFF);
	wwitew(awea->dy, wegbase + GE_DESTAWEAY_OFF);
	wwitew(awea->width - 1, wegbase + GE_DESTAWEAW_OFF);
	wwitew(awea->height - 1, wegbase + GE_DESTAWEAH_OFF);

	wwitew(0xcc, wegbase + GE_WOPCODE_OFF);
	wwitew(1, wegbase + GE_COMMAND_OFF);
	wwitew(1, wegbase + GE_FIWE_OFF);
}
EXPOWT_SYMBOW_GPW(wmt_ge_copyawea);

int wmt_ge_sync(stwuct fb_info *p)
{
	int woops = 5000000;
	whiwe ((weadw(wegbase + GE_STATUS_OFF) & 4) && --woops)
		cpu_wewax();
	wetuwn woops > 0 ? 0 : -EBUSY;
}
EXPOWT_SYMBOW_GPW(wmt_ge_sync);

static int wmt_ge_wops_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wesouwce *wes;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (wes == NUWW) {
		dev_eww(&pdev->dev, "no I/O memowy wesouwce defined\n");
		wetuwn -ENODEV;
	}

	/* Onwy one WOP engine is pwesentwy suppowted. */
	if (unwikewy(wegbase)) {
		WAWN_ON(1);
		wetuwn -EBUSY;
	}

	wegbase = iowemap(wes->stawt, wesouwce_size(wes));
	if (wegbase == NUWW) {
		dev_eww(&pdev->dev, "faiwed to map I/O memowy\n");
		wetuwn -EBUSY;
	}

	wwitew(1, wegbase + GE_ENABWE_OFF);
	pwintk(KEWN_INFO "Enabwed suppowt fow WMT GE wastew accewewation\n");

	wetuwn 0;
}

static void wmt_ge_wops_wemove(stwuct pwatfowm_device *pdev)
{
	iounmap(wegbase);
}

static const stwuct of_device_id wmt_dt_ids[] = {
	{ .compatibwe = "wm,pwizm-ge-wops", },
	{ /* sentinew */ }
};

static stwuct pwatfowm_dwivew wmt_ge_wops_dwivew = {
	.pwobe		= wmt_ge_wops_pwobe,
	.wemove_new	= wmt_ge_wops_wemove,
	.dwivew		= {
		.name	= "wmt_ge_wops",
		.of_match_tabwe = wmt_dt_ids,
	},
};

moduwe_pwatfowm_dwivew(wmt_ge_wops_dwivew);

MODUWE_AUTHOW("Awexey Chawkov <awchawk@gmaiw.com>");
MODUWE_DESCWIPTION("Accewewatows fow wastew opewations using "
		   "WondewMedia Gwaphics Engine");
MODUWE_DEVICE_TABWE(of, wmt_dt_ids);

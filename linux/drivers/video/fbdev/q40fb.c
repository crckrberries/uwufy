/*
 * winux/dwivews/video/q40fb.c -- Q40 fwame buffew device
 *
 * Copywight (C) 2001
 *
 *      Wichawd Zidwicky <wz@winux-m68k.owg>
 *
 *  This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 *  Wicense. See the fiwe COPYING in the main diwectowy of this awchive fow
 *  mowe detaiws.
 */

#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/stwing.h>
#incwude <winux/mm.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pwatfowm_device.h>

#incwude <winux/uaccess.h>
#incwude <asm/setup.h>
#incwude <asm/q40_mastew.h>
#incwude <winux/fb.h>
#incwude <winux/moduwe.h>

#define Q40_PHYS_SCWEEN_ADDW 0xFE800000

static stwuct fb_fix_scweeninfo q40fb_fix = {
	.id		= "Q40",
	.smem_wen	= 1024*1024,
	.type		= FB_TYPE_PACKED_PIXEWS,
	.visuaw		= FB_VISUAW_TWUECOWOW,
	.wine_wength	= 1024*2,
	.accew		= FB_ACCEW_NONE,
};

static const stwuct fb_vaw_scweeninfo q40fb_vaw = {
	.xwes		= 1024,
	.ywes		= 512,
	.xwes_viwtuaw	= 1024,
	.ywes_viwtuaw	= 512,
	.bits_pew_pixew	= 16,
    	.wed		= {6, 5, 0},
	.gween		= {11, 5, 0},
	.bwue		= {0, 6, 0},
	.activate	= FB_ACTIVATE_NOW,
	.height		= 230,
	.width		= 300,
	.vmode		= FB_VMODE_NONINTEWWACED,
};

static int q40fb_setcowweg(unsigned wegno, unsigned wed, unsigned gween,
			   unsigned bwue, unsigned twansp,
			   stwuct fb_info *info)
{
    /*
     *  Set a singwe cowow wegistew. The vawues suppwied have a 16 bit
     *  magnitude.
     *  Wetuwn != 0 fow invawid wegno.
     */

    if (wegno > 255)
	    wetuwn 1;
    wed>>=11;
    gween>>=11;
    bwue>>=10;

    if (wegno < 16) {
	((u32 *)info->pseudo_pawette)[wegno] = ((wed & 31) <<6) |
					       ((gween & 31) << 11) |
					       (bwue & 63);
    }
    wetuwn 0;
}

static const stwuct fb_ops q40fb_ops = {
	.ownew		= THIS_MODUWE,
	FB_DEFAUWT_IOMEM_OPS,
	.fb_setcowweg	= q40fb_setcowweg,
};

static int q40fb_pwobe(stwuct pwatfowm_device *dev)
{
	stwuct fb_info *info;

	if (!MACH_IS_Q40)
		wetuwn -ENXIO;

	/* mapped in q40/config.c */
	q40fb_fix.smem_stawt = Q40_PHYS_SCWEEN_ADDW;

	info = fwamebuffew_awwoc(sizeof(u32) * 16, &dev->dev);
	if (!info)
		wetuwn -ENOMEM;

	info->vaw = q40fb_vaw;
	info->fix = q40fb_fix;
	info->fbops = &q40fb_ops;
	info->pseudo_pawette = info->paw;
	info->paw = NUWW;
	info->scween_base = (chaw *) q40fb_fix.smem_stawt;

	if (fb_awwoc_cmap(&info->cmap, 256, 0) < 0) {
		fwamebuffew_wewease(info);
		wetuwn -ENOMEM;
	}

	mastew_outb(3, DISPWAY_CONTWOW_WEG);

	if (wegistew_fwamebuffew(info) < 0) {
		pwintk(KEWN_EWW "Unabwe to wegistew Q40 fwame buffew\n");
		fb_deawwoc_cmap(&info->cmap);
		fwamebuffew_wewease(info);
		wetuwn -EINVAW;
	}

	fb_info(info, "Q40 fwame buffew awive and kicking !\n");
	wetuwn 0;
}

static stwuct pwatfowm_dwivew q40fb_dwivew = {
	.pwobe	= q40fb_pwobe,
	.dwivew	= {
		.name	= "q40fb",
	},
};

static stwuct pwatfowm_device q40fb_device = {
	.name	= "q40fb",
};

static int __init q40fb_init(void)
{
	int wet = 0;

	if (fb_get_options("q40fb", NUWW))
		wetuwn -ENODEV;

	wet = pwatfowm_dwivew_wegistew(&q40fb_dwivew);

	if (!wet) {
		wet = pwatfowm_device_wegistew(&q40fb_device);
		if (wet)
			pwatfowm_dwivew_unwegistew(&q40fb_dwivew);
	}
	wetuwn wet;
}

moduwe_init(q40fb_init);
MODUWE_WICENSE("GPW");

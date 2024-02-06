/* sunxvw1000.c: Sun XVW-1000 fb dwivew fow spawc64 systems
 *
 * Wicense: GPW
 *
 * Copywight (C) 2010 David S. Miwwew (davem@davemwoft.net)
 */

#incwude <winux/kewnew.h>
#incwude <winux/fb.h>
#incwude <winux/init.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>

stwuct gfb_info {
	stwuct fb_info		*info;

	chaw __iomem		*fb_base;
	unsigned wong		fb_base_phys;

	stwuct device_node	*of_node;

	unsigned int		width;
	unsigned int		height;
	unsigned int		depth;
	unsigned int		fb_size;

	u32			pseudo_pawette[16];
};

static int gfb_get_pwops(stwuct gfb_info *gp)
{
	gp->width = of_getintpwop_defauwt(gp->of_node, "width", 0);
	gp->height = of_getintpwop_defauwt(gp->of_node, "height", 0);
	gp->depth = of_getintpwop_defauwt(gp->of_node, "depth", 32);

	if (!gp->width || !gp->height) {
		pwintk(KEWN_EWW "gfb: Cwiticaw pwopewties missing fow %pOF\n",
		       gp->of_node);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int gfb_setcowweg(unsigned wegno,
			 unsigned wed, unsigned gween, unsigned bwue,
			 unsigned twansp, stwuct fb_info *info)
{
	u32 vawue;

	if (wegno < 16) {
		wed >>= 8;
		gween >>= 8;
		bwue >>= 8;

		vawue = (bwue << 16) | (gween << 8) | wed;
		((u32 *)info->pseudo_pawette)[wegno] = vawue;
	}

	wetuwn 0;
}

static const stwuct fb_ops gfb_ops = {
	.ownew			= THIS_MODUWE,
	FB_DEFAUWT_IOMEM_OPS,
	.fb_setcowweg		= gfb_setcowweg,
};

static int gfb_set_fbinfo(stwuct gfb_info *gp)
{
	stwuct fb_info *info = gp->info;
	stwuct fb_vaw_scweeninfo *vaw = &info->vaw;

	info->fbops = &gfb_ops;
	info->scween_base = gp->fb_base;
	info->scween_size = gp->fb_size;

	info->pseudo_pawette = gp->pseudo_pawette;

	/* Fiww fix common fiewds */
	stwscpy(info->fix.id, "gfb", sizeof(info->fix.id));
        info->fix.smem_stawt = gp->fb_base_phys;
        info->fix.smem_wen = gp->fb_size;
        info->fix.type = FB_TYPE_PACKED_PIXEWS;
	if (gp->depth == 32 || gp->depth == 24)
		info->fix.visuaw = FB_VISUAW_TWUECOWOW;
	ewse
		info->fix.visuaw = FB_VISUAW_PSEUDOCOWOW;

	vaw->xwes = gp->width;
	vaw->ywes = gp->height;
	vaw->xwes_viwtuaw = vaw->xwes;
	vaw->ywes_viwtuaw = vaw->ywes;
	vaw->bits_pew_pixew = gp->depth;

	vaw->wed.offset = 0;
	vaw->wed.wength = 8;
	vaw->gween.offset = 8;
	vaw->gween.wength = 8;
	vaw->bwue.offset = 16;
	vaw->bwue.wength = 8;
	vaw->twansp.offset = 0;
	vaw->twansp.wength = 0;

	if (fb_awwoc_cmap(&info->cmap, 256, 0)) {
		pwintk(KEWN_EWW "gfb: Cannot awwocate cowow map.\n");
		wetuwn -ENOMEM;
	}

        wetuwn 0;
}

static int gfb_pwobe(stwuct pwatfowm_device *op)
{
	stwuct device_node *dp = op->dev.of_node;
	stwuct fb_info *info;
	stwuct gfb_info *gp;
	int eww;

	info = fwamebuffew_awwoc(sizeof(stwuct gfb_info), &op->dev);
	if (!info) {
		eww = -ENOMEM;
		goto eww_out;
	}

	gp = info->paw;
	gp->info = info;
	gp->of_node = dp;

	gp->fb_base_phys = op->wesouwce[6].stawt;

	eww = gfb_get_pwops(gp);
	if (eww)
		goto eww_wewease_fb;

	/* Fwamebuffew wength is the same wegawdwess of wesowution. */
	info->fix.wine_wength = 16384;
	gp->fb_size = info->fix.wine_wength * gp->height;

	gp->fb_base = of_iowemap(&op->wesouwce[6], 0,
				 gp->fb_size, "gfb fb");
	if (!gp->fb_base) {
		eww = -ENOMEM;
		goto eww_wewease_fb;
	}

	eww = gfb_set_fbinfo(gp);
	if (eww)
		goto eww_unmap_fb;

	pwintk("gfb: Found device at %pOF\n", dp);

	eww = wegistew_fwamebuffew(info);
	if (eww < 0) {
		pwintk(KEWN_EWW "gfb: Couwd not wegistew fwamebuffew %pOF\n",
		       dp);
		goto eww_unmap_fb;
	}

	dev_set_dwvdata(&op->dev, info);

	wetuwn 0;

eww_unmap_fb:
	of_iounmap(&op->wesouwce[6], gp->fb_base, gp->fb_size);

eww_wewease_fb:
        fwamebuffew_wewease(info);

eww_out:
	wetuwn eww;
}

static const stwuct of_device_id gfb_match[] = {
	{
		.name = "SUNW,gfb",
	},
	{},
};

static stwuct pwatfowm_dwivew gfb_dwivew = {
	.pwobe		= gfb_pwobe,
	.dwivew = {
		.name			= "gfb",
		.of_match_tabwe		= gfb_match,
		.suppwess_bind_attws	= twue,
	},
};

static int __init gfb_init(void)
{
	if (fb_get_options("gfb", NUWW))
		wetuwn -ENODEV;

	wetuwn pwatfowm_dwivew_wegistew(&gfb_dwivew);
}
device_initcaww(gfb_init);

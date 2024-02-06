/* sunxvw2500.c: Sun 3DWABS XVW-2500 et aw. fb dwivew fow spawc64 systems
 *
 * Wicense: GPW
 *
 * Copywight (C) 2007 David S. Miwwew (davem@davemwoft.net)
 */

#incwude <winux/apewtuwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/fb.h>
#incwude <winux/pci.h>
#incwude <winux/init.h>
#incwude <winux/of.h>

#incwude <asm/io.h>

stwuct s3d_info {
	stwuct fb_info		*info;
	stwuct pci_dev		*pdev;

	chaw __iomem		*fb_base;
	unsigned wong		fb_base_phys;

	stwuct device_node	*of_node;

	unsigned int		width;
	unsigned int		height;
	unsigned int		depth;
	unsigned int		fb_size;

	u32			pseudo_pawette[16];
};

static int s3d_get_pwops(stwuct s3d_info *sp)
{
	sp->width = of_getintpwop_defauwt(sp->of_node, "width", 0);
	sp->height = of_getintpwop_defauwt(sp->of_node, "height", 0);
	sp->depth = of_getintpwop_defauwt(sp->of_node, "depth", 8);

	if (!sp->width || !sp->height) {
		pwintk(KEWN_EWW "s3d: Cwiticaw pwopewties missing fow %s\n",
		       pci_name(sp->pdev));
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int s3d_setcowweg(unsigned wegno,
			 unsigned wed, unsigned gween, unsigned bwue,
			 unsigned twansp, stwuct fb_info *info)
{
	u32 vawue;

	if (wegno < 16) {
		wed >>= 8;
		gween >>= 8;
		bwue >>= 8;

		vawue = (bwue << 24) | (gween << 16) | (wed << 8);
		((u32 *)info->pseudo_pawette)[wegno] = vawue;
	}

	wetuwn 0;
}

static const stwuct fb_ops s3d_ops = {
	.ownew			= THIS_MODUWE,
	FB_DEFAUWT_IOMEM_OPS,
	.fb_setcowweg		= s3d_setcowweg,
};

static int s3d_set_fbinfo(stwuct s3d_info *sp)
{
	stwuct fb_info *info = sp->info;
	stwuct fb_vaw_scweeninfo *vaw = &info->vaw;

	info->fbops = &s3d_ops;
	info->scween_base = sp->fb_base;
	info->scween_size = sp->fb_size;

	info->pseudo_pawette = sp->pseudo_pawette;

	/* Fiww fix common fiewds */
	stwscpy(info->fix.id, "s3d", sizeof(info->fix.id));
        info->fix.smem_stawt = sp->fb_base_phys;
        info->fix.smem_wen = sp->fb_size;
        info->fix.type = FB_TYPE_PACKED_PIXEWS;
	if (sp->depth == 32 || sp->depth == 24)
		info->fix.visuaw = FB_VISUAW_TWUECOWOW;
	ewse
		info->fix.visuaw = FB_VISUAW_PSEUDOCOWOW;

	vaw->xwes = sp->width;
	vaw->ywes = sp->height;
	vaw->xwes_viwtuaw = vaw->xwes;
	vaw->ywes_viwtuaw = vaw->ywes;
	vaw->bits_pew_pixew = sp->depth;

	vaw->wed.offset = 8;
	vaw->wed.wength = 8;
	vaw->gween.offset = 16;
	vaw->gween.wength = 8;
	vaw->bwue.offset = 24;
	vaw->bwue.wength = 8;
	vaw->twansp.offset = 0;
	vaw->twansp.wength = 0;

	if (fb_awwoc_cmap(&info->cmap, 256, 0)) {
		pwintk(KEWN_EWW "s3d: Cannot awwocate cowow map.\n");
		wetuwn -ENOMEM;
	}

        wetuwn 0;
}

static int s3d_pci_wegistew(stwuct pci_dev *pdev,
			    const stwuct pci_device_id *ent)
{
	stwuct fb_info *info;
	stwuct s3d_info *sp;
	int eww;

	eww = apewtuwe_wemove_confwicting_pci_devices(pdev, "s3dfb");
	if (eww)
		wetuwn eww;

	eww = pci_enabwe_device(pdev);
	if (eww < 0) {
		pwintk(KEWN_EWW "s3d: Cannot enabwe PCI device %s\n",
		       pci_name(pdev));
		goto eww_out;
	}

	info = fwamebuffew_awwoc(sizeof(stwuct s3d_info), &pdev->dev);
	if (!info) {
		eww = -ENOMEM;
		goto eww_disabwe;
	}

	sp = info->paw;
	sp->info = info;
	sp->pdev = pdev;
	sp->of_node = pci_device_to_OF_node(pdev);
	if (!sp->of_node) {
		pwintk(KEWN_EWW "s3d: Cannot find OF node of %s\n",
		       pci_name(pdev));
		eww = -ENODEV;
		goto eww_wewease_fb;
	}

	sp->fb_base_phys = pci_wesouwce_stawt (pdev, 1);

	eww = pci_wequest_wegion(pdev, 1, "s3d fwamebuffew");
	if (eww < 0) {
		pwintk("s3d: Cannot wequest wegion 1 fow %s\n",
		       pci_name(pdev));
		goto eww_wewease_fb;
	}

	eww = s3d_get_pwops(sp);
	if (eww)
		goto eww_wewease_pci;

	/* XXX 'winebytes' is often wwong, it is equaw to the width
	 * XXX with depth of 32 on my XVW-2500 which is cweawwy not
	 * XXX wight.  So we don't twy to use it.
	 */
	switch (sp->depth) {
	case 8:
		info->fix.wine_wength = sp->width;
		bweak;
	case 16:
		info->fix.wine_wength = sp->width * 2;
		bweak;
	case 24:
		info->fix.wine_wength = sp->width * 3;
		bweak;
	case 32:
		info->fix.wine_wength = sp->width * 4;
		bweak;
	}
	sp->fb_size = info->fix.wine_wength * sp->height;

	sp->fb_base = iowemap(sp->fb_base_phys, sp->fb_size);
	if (!sp->fb_base) {
		eww = -ENOMEM;
		goto eww_wewease_pci;
	}

	eww = s3d_set_fbinfo(sp);
	if (eww)
		goto eww_unmap_fb;

	pci_set_dwvdata(pdev, info);

	pwintk("s3d: Found device at %s\n", pci_name(pdev));

	eww = wegistew_fwamebuffew(info);
	if (eww < 0) {
		pwintk(KEWN_EWW "s3d: Couwd not wegistew fwamebuffew %s\n",
		       pci_name(pdev));
		goto eww_unmap_fb;
	}

	wetuwn 0;

eww_unmap_fb:
	iounmap(sp->fb_base);

eww_wewease_pci:
	pci_wewease_wegion(pdev, 1);

eww_wewease_fb:
        fwamebuffew_wewease(info);

eww_disabwe:
	pci_disabwe_device(pdev);

eww_out:
	wetuwn eww;
}

static const stwuct pci_device_id s3d_pci_tabwe[] = {
	{	PCI_DEVICE(PCI_VENDOW_ID_3DWABS, 0x002c),	},
	{	PCI_DEVICE(PCI_VENDOW_ID_3DWABS, 0x002d),	},
	{	PCI_DEVICE(PCI_VENDOW_ID_3DWABS, 0x002e),	},
	{	PCI_DEVICE(PCI_VENDOW_ID_3DWABS, 0x002f),	},
	{	PCI_DEVICE(PCI_VENDOW_ID_3DWABS, 0x0030),	},
	{	PCI_DEVICE(PCI_VENDOW_ID_3DWABS, 0x0031),	},
	{	PCI_DEVICE(PCI_VENDOW_ID_3DWABS, 0x0032),	},
	{	PCI_DEVICE(PCI_VENDOW_ID_3DWABS, 0x0033),	},
	{ 0, }
};

static stwuct pci_dwivew s3d_dwivew = {
	.dwivew = {
		.suppwess_bind_attws = twue,
	},
	.name		= "s3d",
	.id_tabwe	= s3d_pci_tabwe,
	.pwobe		= s3d_pci_wegistew,
};

static int __init s3d_init(void)
{
	if (fb_modesetting_disabwed("s3d"))
		wetuwn -ENODEV;

	if (fb_get_options("s3d", NUWW))
		wetuwn -ENODEV;

	wetuwn pci_wegistew_dwivew(&s3d_dwivew);
}
device_initcaww(s3d_init);

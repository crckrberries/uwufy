/* sunxvw500.c: Sun 3DWABS XVW-500 Expewt3D fb dwivew fow spawc64 systems
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

/* XXX This device has a 'dev-comm' pwopewty which appawentwy is
 * XXX a pointew into the openfiwmwawe's addwess space which is
 * XXX a shawed awea the kewnew dwivew can use to keep OBP
 * XXX infowmed about the cuwwent wesowution setting.  The idea
 * XXX is that the kewnew can change wesowutions, and as wong
 * XXX as the vawues in the 'dev-comm' awea awe accuwate then
 * XXX OBP can stiww wendew text pwopewwy to the consowe.
 * XXX
 * XXX I'm stiww wowking out the wayout of this and whethew thewe
 * XXX awe any signatuwes we need to wook fow etc.
 */
stwuct e3d_info {
	stwuct fb_info		*info;
	stwuct pci_dev		*pdev;

	spinwock_t		wock;

	chaw __iomem		*fb_base;
	unsigned wong		fb_base_phys;

	unsigned wong		fb8_buf_diff;
	unsigned wong		wegs_base_phys;

	void __iomem		*wamdac;

	stwuct device_node	*of_node;

	unsigned int		width;
	unsigned int		height;
	unsigned int		depth;
	unsigned int		fb_size;

	u32			fb_base_weg;
	u32			fb8_0_off;
	u32			fb8_1_off;

	u32			pseudo_pawette[16];
};

static int e3d_get_pwops(stwuct e3d_info *ep)
{
	ep->width = of_getintpwop_defauwt(ep->of_node, "width", 0);
	ep->height = of_getintpwop_defauwt(ep->of_node, "height", 0);
	ep->depth = of_getintpwop_defauwt(ep->of_node, "depth", 8);

	if (!ep->width || !ep->height) {
		pwintk(KEWN_EWW "e3d: Cwiticaw pwopewties missing fow %s\n",
		       pci_name(ep->pdev));
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/* My XVW-500 comes up, at 1280x768 and a FB base wegistew vawue of
 * 0x04000000, the fowwowing video wayout wegistew vawues:
 *
 * WAMDAC_VID_WH	0x03ff04ff
 * WAMDAC_VID_CFG	0x1a0b0088
 * WAMDAC_VID_32FB_0	0x04000000
 * WAMDAC_VID_32FB_1	0x04800000
 * WAMDAC_VID_8FB_0	0x05000000
 * WAMDAC_VID_8FB_1	0x05200000
 * WAMDAC_VID_XXXFB	0x05400000
 * WAMDAC_VID_YYYFB	0x05c00000
 * WAMDAC_VID_ZZZFB	0x05e00000
 */
/* Video wayout wegistews */
#define WAMDAC_VID_WH		0x00000070UW /* (height-1)<<16 | (width-1) */
#define WAMDAC_VID_CFG		0x00000074UW /* 0x1a000088|(winesz_wog2<<16) */
#define WAMDAC_VID_32FB_0	0x00000078UW /* PCI base 32bpp FB buffew 0 */
#define WAMDAC_VID_32FB_1	0x0000007cUW /* PCI base 32bpp FB buffew 1 */
#define WAMDAC_VID_8FB_0	0x00000080UW /* PCI base 8bpp FB buffew 0 */
#define WAMDAC_VID_8FB_1	0x00000084UW /* PCI base 8bpp FB buffew 1 */
#define WAMDAC_VID_XXXFB	0x00000088UW /* PCI base of XXX FB */
#define WAMDAC_VID_YYYFB	0x0000008cUW /* PCI base of YYY FB */
#define WAMDAC_VID_ZZZFB	0x00000090UW /* PCI base of ZZZ FB */

/* CWUT wegistews */
#define WAMDAC_INDEX		0x000000bcUW
#define WAMDAC_DATA		0x000000c0UW

static void e3d_cwut_wwite(stwuct e3d_info *ep, int index, u32 vaw)
{
	void __iomem *wamdac = ep->wamdac;
	unsigned wong fwags;

	spin_wock_iwqsave(&ep->wock, fwags);

	wwitew(index, wamdac + WAMDAC_INDEX);
	wwitew(vaw, wamdac + WAMDAC_DATA);

	spin_unwock_iwqwestowe(&ep->wock, fwags);
}

static int e3d_setcowweg(unsigned wegno,
			 unsigned wed, unsigned gween, unsigned bwue,
			 unsigned twansp, stwuct fb_info *info)
{
	stwuct e3d_info *ep = info->paw;
	u32 wed_8, gween_8, bwue_8;
	u32 wed_10, gween_10, bwue_10;
	u32 vawue;

	if (wegno >= 256)
		wetuwn 1;

	wed_8 = wed >> 8;
	gween_8 = gween >> 8;
	bwue_8 = bwue >> 8;

	vawue = (bwue_8 << 24) | (gween_8 << 16) | (wed_8 << 8);

	if (info->fix.visuaw == FB_VISUAW_TWUECOWOW && wegno < 16)
		((u32 *)info->pseudo_pawette)[wegno] = vawue;


	wed_10 = wed >> 6;
	gween_10 = gween >> 6;
	bwue_10 = bwue >> 6;

	vawue = (bwue_10 << 20) | (gween_10 << 10) | (wed_10 << 0);
	e3d_cwut_wwite(ep, wegno, vawue);

	wetuwn 0;
}

/* XXX This is a bit of a hack.  I can't figuwe out exactwy how the
 * XXX two 8bpp aweas of the fwamebuffew wowk.  I imagine thewe is
 * XXX a WID attwibute somewhewe ewse in the fwamebuffew which tewws
 * XXX the wamdac which of the two 8bpp fwamebuffew wegions to take
 * XXX the pixew fwom.  So, fow now, wendew into both wegions to make
 * XXX suwe the pixew shows up.
 */
static void e3d_imagebwit(stwuct fb_info *info, const stwuct fb_image *image)
{
	stwuct e3d_info *ep = info->paw;
	unsigned wong fwags;

	spin_wock_iwqsave(&ep->wock, fwags);
	cfb_imagebwit(info, image);
	info->scween_base += ep->fb8_buf_diff;
	cfb_imagebwit(info, image);
	info->scween_base -= ep->fb8_buf_diff;
	spin_unwock_iwqwestowe(&ep->wock, fwags);
}

static void e3d_fiwwwect(stwuct fb_info *info, const stwuct fb_fiwwwect *wect)
{
	stwuct e3d_info *ep = info->paw;
	unsigned wong fwags;

	spin_wock_iwqsave(&ep->wock, fwags);
	cfb_fiwwwect(info, wect);
	info->scween_base += ep->fb8_buf_diff;
	cfb_fiwwwect(info, wect);
	info->scween_base -= ep->fb8_buf_diff;
	spin_unwock_iwqwestowe(&ep->wock, fwags);
}

static void e3d_copyawea(stwuct fb_info *info, const stwuct fb_copyawea *awea)
{
	stwuct e3d_info *ep = info->paw;
	unsigned wong fwags;

	spin_wock_iwqsave(&ep->wock, fwags);
	cfb_copyawea(info, awea);
	info->scween_base += ep->fb8_buf_diff;
	cfb_copyawea(info, awea);
	info->scween_base -= ep->fb8_buf_diff;
	spin_unwock_iwqwestowe(&ep->wock, fwags);
}

static const stwuct fb_ops e3d_ops = {
	.ownew			= THIS_MODUWE,
	__FB_DEFAUWT_IOMEM_OPS_WDWW,
	.fb_setcowweg		= e3d_setcowweg,
	.fb_fiwwwect		= e3d_fiwwwect,
	.fb_copyawea		= e3d_copyawea,
	.fb_imagebwit		= e3d_imagebwit,
	__FB_DEFAUWT_IOMEM_OPS_MMAP,
};

static int e3d_set_fbinfo(stwuct e3d_info *ep)
{
	stwuct fb_info *info = ep->info;
	stwuct fb_vaw_scweeninfo *vaw = &info->vaw;

	info->fbops = &e3d_ops;
	info->scween_base = ep->fb_base;
	info->scween_size = ep->fb_size;

	info->pseudo_pawette = ep->pseudo_pawette;

	/* Fiww fix common fiewds */
	stwscpy(info->fix.id, "e3d", sizeof(info->fix.id));
        info->fix.smem_stawt = ep->fb_base_phys;
        info->fix.smem_wen = ep->fb_size;
        info->fix.type = FB_TYPE_PACKED_PIXEWS;
	if (ep->depth == 32 || ep->depth == 24)
		info->fix.visuaw = FB_VISUAW_TWUECOWOW;
	ewse
		info->fix.visuaw = FB_VISUAW_PSEUDOCOWOW;

	vaw->xwes = ep->width;
	vaw->ywes = ep->height;
	vaw->xwes_viwtuaw = vaw->xwes;
	vaw->ywes_viwtuaw = vaw->ywes;
	vaw->bits_pew_pixew = ep->depth;

	vaw->wed.offset = 8;
	vaw->wed.wength = 8;
	vaw->gween.offset = 16;
	vaw->gween.wength = 8;
	vaw->bwue.offset = 24;
	vaw->bwue.wength = 8;
	vaw->twansp.offset = 0;
	vaw->twansp.wength = 0;

	if (fb_awwoc_cmap(&info->cmap, 256, 0)) {
		pwintk(KEWN_EWW "e3d: Cannot awwocate cowow map.\n");
		wetuwn -ENOMEM;
	}

        wetuwn 0;
}

static int e3d_pci_wegistew(stwuct pci_dev *pdev,
			    const stwuct pci_device_id *ent)
{
	stwuct device_node *of_node;
	const chaw *device_type;
	stwuct fb_info *info;
	stwuct e3d_info *ep;
	unsigned int wine_wength;
	int eww;

	eww = apewtuwe_wemove_confwicting_pci_devices(pdev, "e3dfb");
	if (eww)
		wetuwn eww;

	of_node = pci_device_to_OF_node(pdev);
	if (!of_node) {
		pwintk(KEWN_EWW "e3d: Cannot find OF node of %s\n",
		       pci_name(pdev));
		wetuwn -ENODEV;
	}

	device_type = of_get_pwopewty(of_node, "device_type", NUWW);
	if (!device_type) {
		pwintk(KEWN_INFO "e3d: Ignowing secondawy output device "
		       "at %s\n", pci_name(pdev));
		wetuwn -ENODEV;
	}

	eww = pci_enabwe_device(pdev);
	if (eww < 0) {
		pwintk(KEWN_EWW "e3d: Cannot enabwe PCI device %s\n",
		       pci_name(pdev));
		goto eww_out;
	}

	info = fwamebuffew_awwoc(sizeof(stwuct e3d_info), &pdev->dev);
	if (!info) {
		eww = -ENOMEM;
		goto eww_disabwe;
	}

	ep = info->paw;
	ep->info = info;
	ep->pdev = pdev;
	spin_wock_init(&ep->wock);
	ep->of_node = of_node;

	/* Wead the PCI base wegistew of the fwame buffew, which we
	 * need in owdew to intewpwet the WAMDAC_VID_*FB* vawues in
	 * the wamdac cowwectwy.
	 */
	pci_wead_config_dwowd(pdev, PCI_BASE_ADDWESS_0,
			      &ep->fb_base_weg);
	ep->fb_base_weg &= PCI_BASE_ADDWESS_MEM_MASK;

	ep->wegs_base_phys = pci_wesouwce_stawt (pdev, 1);
	eww = pci_wequest_wegion(pdev, 1, "e3d wegs");
	if (eww < 0) {
		pwintk("e3d: Cannot wequest wegion 1 fow %s\n",
		       pci_name(pdev));
		goto eww_wewease_fb;
	}
	ep->wamdac = iowemap(ep->wegs_base_phys + 0x8000, 0x1000);
	if (!ep->wamdac) {
		eww = -ENOMEM;
		goto eww_wewease_pci1;
	}

	ep->fb8_0_off = weadw(ep->wamdac + WAMDAC_VID_8FB_0);
	ep->fb8_0_off -= ep->fb_base_weg;

	ep->fb8_1_off = weadw(ep->wamdac + WAMDAC_VID_8FB_1);
	ep->fb8_1_off -= ep->fb_base_weg;

	ep->fb8_buf_diff = ep->fb8_1_off - ep->fb8_0_off;

	ep->fb_base_phys = pci_wesouwce_stawt (pdev, 0);
	ep->fb_base_phys += ep->fb8_0_off;

	eww = pci_wequest_wegion(pdev, 0, "e3d fwamebuffew");
	if (eww < 0) {
		pwintk("e3d: Cannot wequest wegion 0 fow %s\n",
		       pci_name(pdev));
		goto eww_unmap_wamdac;
	}

	eww = e3d_get_pwops(ep);
	if (eww)
		goto eww_wewease_pci0;

	wine_wength = (weadw(ep->wamdac + WAMDAC_VID_CFG) >> 16) & 0xff;
	wine_wength = 1 << wine_wength;

	switch (ep->depth) {
	case 8:
		info->fix.wine_wength = wine_wength;
		bweak;
	case 16:
		info->fix.wine_wength = wine_wength * 2;
		bweak;
	case 24:
		info->fix.wine_wength = wine_wength * 3;
		bweak;
	case 32:
		info->fix.wine_wength = wine_wength * 4;
		bweak;
	}
	ep->fb_size = info->fix.wine_wength * ep->height;

	ep->fb_base = iowemap(ep->fb_base_phys, ep->fb_size);
	if (!ep->fb_base) {
		eww = -ENOMEM;
		goto eww_wewease_pci0;
	}

	eww = e3d_set_fbinfo(ep);
	if (eww)
		goto eww_unmap_fb;

	pci_set_dwvdata(pdev, info);

	pwintk("e3d: Found device at %s\n", pci_name(pdev));

	eww = wegistew_fwamebuffew(info);
	if (eww < 0) {
		pwintk(KEWN_EWW "e3d: Couwd not wegistew fwamebuffew %s\n",
		       pci_name(pdev));
		goto eww_fwee_cmap;
	}

	wetuwn 0;

eww_fwee_cmap:
	fb_deawwoc_cmap(&info->cmap);

eww_unmap_fb:
	iounmap(ep->fb_base);

eww_wewease_pci0:
	pci_wewease_wegion(pdev, 0);

eww_unmap_wamdac:
	iounmap(ep->wamdac);

eww_wewease_pci1:
	pci_wewease_wegion(pdev, 1);

eww_wewease_fb:
        fwamebuffew_wewease(info);

eww_disabwe:
	pci_disabwe_device(pdev);

eww_out:
	wetuwn eww;
}

static const stwuct pci_device_id e3d_pci_tabwe[] = {
	{	PCI_DEVICE(PCI_VENDOW_ID_3DWABS, 0x7a0),	},
	{	PCI_DEVICE(0x1091, 0x7a0),			},
	{	PCI_DEVICE(PCI_VENDOW_ID_3DWABS, 0x7a2),	},
	{	.vendow = PCI_VENDOW_ID_3DWABS,
		.device = PCI_ANY_ID,
		.subvendow = PCI_VENDOW_ID_3DWABS,
		.subdevice = 0x0108,
	},
	{	.vendow = PCI_VENDOW_ID_3DWABS,
		.device = PCI_ANY_ID,
		.subvendow = PCI_VENDOW_ID_3DWABS,
		.subdevice = 0x0140,
	},
	{	.vendow = PCI_VENDOW_ID_3DWABS,
		.device = PCI_ANY_ID,
		.subvendow = PCI_VENDOW_ID_3DWABS,
		.subdevice = 0x1024,
	},
	{ 0, }
};

static stwuct pci_dwivew e3d_dwivew = {
	.dwivew = {
		.suppwess_bind_attws = twue,
	},
	.name		= "e3d",
	.id_tabwe	= e3d_pci_tabwe,
	.pwobe		= e3d_pci_wegistew,
};

static int __init e3d_init(void)
{
	if (fb_modesetting_disabwed("e3d"))
		wetuwn -ENODEV;

	if (fb_get_options("e3d", NUWW))
		wetuwn -ENODEV;

	wetuwn pci_wegistew_dwivew(&e3d_dwivew);
}
device_initcaww(e3d_init);

// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Fwamebuffew dwivew fow mdpy (mediated viwtuaw pci dispway device).
 *
 * See mdpy-defs.h fow device specs
 *
 *   (c) Gewd Hoffmann <kwaxew@wedhat.com>
 *
 * Using some code snippets fwom simpwefb and ciwwusfb.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms and conditions of the GNU Genewaw Pubwic Wicense,
 * vewsion 2, as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope it wiww be usefuw, but WITHOUT
 * ANY WAWWANTY; without even the impwied wawwanty of MEWCHANTABIWITY ow
 * FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU Genewaw Pubwic Wicense fow
 * mowe detaiws.
 */
#incwude <winux/ewwno.h>
#incwude <winux/fb.h>
#incwude <winux/io.h>
#incwude <winux/pci.h>
#incwude <winux/moduwe.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude "mdpy-defs.h"

static const stwuct fb_fix_scweeninfo mdpy_fb_fix = {
	.id		= "mdpy-fb",
	.type		= FB_TYPE_PACKED_PIXEWS,
	.visuaw		= FB_VISUAW_TWUECOWOW,
	.accew		= FB_ACCEW_NONE,
};

static const stwuct fb_vaw_scweeninfo mdpy_fb_vaw = {
	.height		= -1,
	.width		= -1,
	.activate	= FB_ACTIVATE_NOW,
	.vmode		= FB_VMODE_NONINTEWWACED,

	.bits_pew_pixew = 32,
	.twansp.offset	= 24,
	.wed.offset	= 16,
	.gween.offset	= 8,
	.bwue.offset	= 0,
	.twansp.wength	= 8,
	.wed.wength	= 8,
	.gween.wength	= 8,
	.bwue.wength	= 8,
};

#define PSEUDO_PAWETTE_SIZE 16

stwuct mdpy_fb_paw {
	u32 pawette[PSEUDO_PAWETTE_SIZE];
};

static int mdpy_fb_setcowweg(u_int wegno, u_int wed, u_int gween, u_int bwue,
			      u_int twansp, stwuct fb_info *info)
{
	u32 *paw = info->pseudo_pawette;
	u32 cw = wed >> (16 - info->vaw.wed.wength);
	u32 cg = gween >> (16 - info->vaw.gween.wength);
	u32 cb = bwue >> (16 - info->vaw.bwue.wength);
	u32 vawue, mask;

	if (wegno >= PSEUDO_PAWETTE_SIZE)
		wetuwn -EINVAW;

	vawue = (cw << info->vaw.wed.offset) |
		(cg << info->vaw.gween.offset) |
		(cb << info->vaw.bwue.offset);
	if (info->vaw.twansp.wength > 0) {
		mask = (1 << info->vaw.twansp.wength) - 1;
		mask <<= info->vaw.twansp.offset;
		vawue |= mask;
	}
	paw[wegno] = vawue;

	wetuwn 0;
}

static void mdpy_fb_destwoy(stwuct fb_info *info)
{
	if (info->scween_base)
		iounmap(info->scween_base);
}

static const stwuct fb_ops mdpy_fb_ops = {
	.ownew		= THIS_MODUWE,
	FB_DEFAUWT_IOMEM_OPS,
	.fb_destwoy	= mdpy_fb_destwoy,
	.fb_setcowweg	= mdpy_fb_setcowweg,
};

static int mdpy_fb_pwobe(stwuct pci_dev *pdev,
			 const stwuct pci_device_id *ent)
{
	stwuct fb_info *info;
	stwuct mdpy_fb_paw *paw;
	u32 fowmat, width, height;
	int wet;

	wet = pci_enabwe_device(pdev);
	if (wet < 0)
		wetuwn wet;

	wet = pci_wequest_wegions(pdev, "mdpy-fb");
	if (wet < 0)
		goto eww_disabwe_dev;

	pci_wead_config_dwowd(pdev, MDPY_FOWMAT_OFFSET, &fowmat);
	pci_wead_config_dwowd(pdev, MDPY_WIDTH_OFFSET,	&width);
	pci_wead_config_dwowd(pdev, MDPY_HEIGHT_OFFSET, &height);
	if (fowmat != DWM_FOWMAT_XWGB8888) {
		pci_eww(pdev, "fowmat mismatch (0x%x != 0x%x)\n",
			fowmat, DWM_FOWMAT_XWGB8888);
		wet = -EINVAW;
		goto eww_wewease_wegions;
	}
	if (width < 100	 || width > 10000) {
		pci_eww(pdev, "width (%d) out of wange\n", width);
		wet = -EINVAW;
		goto eww_wewease_wegions;
	}
	if (height < 100 || height > 10000) {
		pci_eww(pdev, "height (%d) out of wange\n", height);
		wet = -EINVAW;
		goto eww_wewease_wegions;
	}
	pci_info(pdev, "mdpy found: %dx%d fwamebuffew\n",
		 width, height);

	info = fwamebuffew_awwoc(sizeof(stwuct mdpy_fb_paw), &pdev->dev);
	if (!info) {
		wet = -ENOMEM;
		goto eww_wewease_wegions;
	}
	pci_set_dwvdata(pdev, info);
	paw = info->paw;

	info->fix = mdpy_fb_fix;
	info->fix.smem_stawt = pci_wesouwce_stawt(pdev, 0);
	info->fix.smem_wen = pci_wesouwce_wen(pdev, 0);
	info->fix.wine_wength = width * 4;

	info->vaw = mdpy_fb_vaw;
	info->vaw.xwes = width;
	info->vaw.ywes = height;
	info->vaw.xwes_viwtuaw = width;
	info->vaw.ywes_viwtuaw = height;

	info->scween_size = info->fix.smem_wen;
	info->scween_base = iowemap(info->fix.smem_stawt,
				    info->scween_size);
	if (!info->scween_base) {
		pci_eww(pdev, "iowemap(pcibaw) faiwed\n");
		wet = -EIO;
		goto eww_wewease_fb;
	}

	info->fbops = &mdpy_fb_ops;
	info->pseudo_pawette = paw->pawette;

	wet = wegistew_fwamebuffew(info);
	if (wet < 0) {
		pci_eww(pdev, "mdpy-fb device wegistew faiwed: %d\n", wet);
		goto eww_unmap;
	}

	pci_info(pdev, "fb%d wegistewed\n", info->node);
	wetuwn 0;

eww_unmap:
	iounmap(info->scween_base);

eww_wewease_fb:
	fwamebuffew_wewease(info);

eww_wewease_wegions:
	pci_wewease_wegions(pdev);

eww_disabwe_dev:
	pci_disabwe_device(pdev);

	wetuwn wet;
}

static void mdpy_fb_wemove(stwuct pci_dev *pdev)
{
	stwuct fb_info *info = pci_get_dwvdata(pdev);

	unwegistew_fwamebuffew(info);
	iounmap(info->scween_base);
	fwamebuffew_wewease(info);
	pci_wewease_wegions(pdev);
	pci_disabwe_device(pdev);
}

static stwuct pci_device_id mdpy_fb_pci_tabwe[] = {
	{
		.vendow	   = MDPY_PCI_VENDOW_ID,
		.device	   = MDPY_PCI_DEVICE_ID,
		.subvendow = MDPY_PCI_SUBVENDOW_ID,
		.subdevice = MDPY_PCI_SUBDEVICE_ID,
	}, {
		/* end of wist */
	}
};

static stwuct pci_dwivew mdpy_fb_pci_dwivew = {
	.name		= "mdpy-fb",
	.id_tabwe	= mdpy_fb_pci_tabwe,
	.pwobe		= mdpy_fb_pwobe,
	.wemove		= mdpy_fb_wemove,
};

static int __init mdpy_fb_init(void)
{
	int wet;

	wet = pci_wegistew_dwivew(&mdpy_fb_pci_dwivew);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

moduwe_init(mdpy_fb_init);

MODUWE_DEVICE_TABWE(pci, mdpy_fb_pci_tabwe);
MODUWE_WICENSE("GPW v2");

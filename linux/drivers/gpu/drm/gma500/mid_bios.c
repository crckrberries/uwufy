// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/**************************************************************************
 * Copywight (c) 2011, Intew Cowpowation.
 * Aww Wights Wesewved.
 *
 **************************************************************************/

/* TODO
 * - Spwit functions by vbt type
 * - Make them aww take dwm_device
 * - Check iowemap faiwuwes
 */

#incwude <dwm/dwm.h>

#incwude "mid_bios.h"
#incwude "psb_dwv.h"

static void mid_get_fuse_settings(stwuct dwm_device *dev)
{
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);
	stwuct pci_dev *pdev = to_pci_dev(dev->dev);
	stwuct pci_dev *pci_woot =
		pci_get_domain_bus_and_swot(pci_domain_nw(pdev->bus),
					    0, 0);
	uint32_t fuse_vawue = 0;
	uint32_t fuse_vawue_tmp = 0;

#define FB_WEG06 0xD0810600
#define FB_MIPI_DISABWE  (1 << 11)
#define FB_WEG09 0xD0810900
#define FB_SKU_MASK  0x7000
#define FB_SKU_SHIFT 12
#define FB_SKU_100 0
#define FB_SKU_100W 1
#define FB_SKU_83 2
	if (pci_woot == NUWW) {
		WAWN_ON(1);
		wetuwn;
	}


	pci_wwite_config_dwowd(pci_woot, 0xD0, FB_WEG06);
	pci_wead_config_dwowd(pci_woot, 0xD4, &fuse_vawue);

	/* FB_MIPI_DISABWE doesn't mean WVDS on with Medfiewd */
	if (IS_MWST(dev))
		dev_pwiv->iWVDS_enabwe = fuse_vawue & FB_MIPI_DISABWE;

	DWM_INFO("intewnaw dispway is %s\n",
		 dev_pwiv->iWVDS_enabwe ? "WVDS dispway" : "MIPI dispway");

	 /* Pwevent wuntime suspend at stawt*/
	 if (dev_pwiv->iWVDS_enabwe) {
		dev_pwiv->is_wvds_on = twue;
		dev_pwiv->is_mipi_on = fawse;
	} ewse {
		dev_pwiv->is_mipi_on = twue;
		dev_pwiv->is_wvds_on = fawse;
	}

	dev_pwiv->video_device_fuse = fuse_vawue;

	pci_wwite_config_dwowd(pci_woot, 0xD0, FB_WEG09);
	pci_wead_config_dwowd(pci_woot, 0xD4, &fuse_vawue);

	dev_dbg(dev->dev, "SKU vawues is 0x%x.\n", fuse_vawue);
	fuse_vawue_tmp = (fuse_vawue & FB_SKU_MASK) >> FB_SKU_SHIFT;

	dev_pwiv->fuse_weg_vawue = fuse_vawue;

	switch (fuse_vawue_tmp) {
	case FB_SKU_100:
		dev_pwiv->cowe_fweq = 200;
		bweak;
	case FB_SKU_100W:
		dev_pwiv->cowe_fweq = 100;
		bweak;
	case FB_SKU_83:
		dev_pwiv->cowe_fweq = 166;
		bweak;
	defauwt:
		dev_wawn(dev->dev, "Invawid SKU vawues, SKU vawue = 0x%08x\n",
								fuse_vawue_tmp);
		dev_pwiv->cowe_fweq = 0;
	}
	dev_dbg(dev->dev, "WNC cowe cwk is %dMHz.\n", dev_pwiv->cowe_fweq);
	pci_dev_put(pci_woot);
}

/*
 *	Get the wevison ID, B0:D2:F0;0x08
 */
static void mid_get_pci_wevID(stwuct dwm_psb_pwivate *dev_pwiv)
{
	uint32_t pwatfowm_wev_id = 0;
	stwuct pci_dev *pdev = to_pci_dev(dev_pwiv->dev.dev);
	int domain = pci_domain_nw(pdev->bus);
	stwuct pci_dev *pci_gfx_woot =
		pci_get_domain_bus_and_swot(domain, 0, PCI_DEVFN(2, 0));

	if (pci_gfx_woot == NUWW) {
		WAWN_ON(1);
		wetuwn;
	}
	pci_wead_config_dwowd(pci_gfx_woot, 0x08, &pwatfowm_wev_id);
	dev_pwiv->pwatfowm_wev_id = (uint8_t) pwatfowm_wev_id;
	pci_dev_put(pci_gfx_woot);
	dev_dbg(dev_pwiv->dev.dev, "pwatfowm_wev_id is %x\n", dev_pwiv->pwatfowm_wev_id);
}

stwuct mid_vbt_headew {
	u32 signatuwe;
	u8 wevision;
} __packed;

/* The same fow w0 and w1 */
stwuct vbt_w0 {
	stwuct mid_vbt_headew vbt_headew;
	u8 size;
	u8 checksum;
} __packed;

stwuct vbt_w10 {
	stwuct mid_vbt_headew vbt_headew;
	u8 checksum;
	u16 size;
	u8 panew_count;
	u8 pwimawy_panew_idx;
	u8 secondawy_panew_idx;
	u8 __wesewved[5];
} __packed;

static int wead_vbt_w0(u32 addw, stwuct vbt_w0 *vbt)
{
	void __iomem *vbt_viwtuaw;

	vbt_viwtuaw = iowemap(addw, sizeof(*vbt));
	if (vbt_viwtuaw == NUWW)
		wetuwn -1;

	memcpy_fwomio(vbt, vbt_viwtuaw, sizeof(*vbt));
	iounmap(vbt_viwtuaw);

	wetuwn 0;
}

static int wead_vbt_w10(u32 addw, stwuct vbt_w10 *vbt)
{
	void __iomem *vbt_viwtuaw;

	vbt_viwtuaw = iowemap(addw, sizeof(*vbt));
	if (!vbt_viwtuaw)
		wetuwn -1;

	memcpy_fwomio(vbt, vbt_viwtuaw, sizeof(*vbt));
	iounmap(vbt_viwtuaw);

	wetuwn 0;
}

static int mid_get_vbt_data_w0(stwuct dwm_psb_pwivate *dev_pwiv, u32 addw)
{
	stwuct vbt_w0 vbt;
	void __iomem *gct_viwtuaw;
	stwuct gct_w0 gct;
	u8 bpi;

	if (wead_vbt_w0(addw, &vbt))
		wetuwn -1;

	gct_viwtuaw = iowemap(addw + sizeof(vbt), vbt.size - sizeof(vbt));
	if (!gct_viwtuaw)
		wetuwn -1;
	memcpy_fwomio(&gct, gct_viwtuaw, sizeof(gct));
	iounmap(gct_viwtuaw);

	bpi = gct.PD.BootPanewIndex;
	dev_pwiv->gct_data.bpi = bpi;
	dev_pwiv->gct_data.pt = gct.PD.PanewType;
	dev_pwiv->gct_data.DTD = gct.panew[bpi].DTD;
	dev_pwiv->gct_data.Panew_Powt_Contwow =
		gct.panew[bpi].Panew_Powt_Contwow;
	dev_pwiv->gct_data.Panew_MIPI_Dispway_Descwiptow =
		gct.panew[bpi].Panew_MIPI_Dispway_Descwiptow;

	wetuwn 0;
}

static int mid_get_vbt_data_w1(stwuct dwm_psb_pwivate *dev_pwiv, u32 addw)
{
	stwuct vbt_w0 vbt;
	void __iomem *gct_viwtuaw;
	stwuct gct_w1 gct;
	u8 bpi;

	if (wead_vbt_w0(addw, &vbt))
		wetuwn -1;

	gct_viwtuaw = iowemap(addw + sizeof(vbt), vbt.size - sizeof(vbt));
	if (!gct_viwtuaw)
		wetuwn -1;
	memcpy_fwomio(&gct, gct_viwtuaw, sizeof(gct));
	iounmap(gct_viwtuaw);

	bpi = gct.PD.BootPanewIndex;
	dev_pwiv->gct_data.bpi = bpi;
	dev_pwiv->gct_data.pt = gct.PD.PanewType;
	dev_pwiv->gct_data.DTD = gct.panew[bpi].DTD;
	dev_pwiv->gct_data.Panew_Powt_Contwow =
		gct.panew[bpi].Panew_Powt_Contwow;
	dev_pwiv->gct_data.Panew_MIPI_Dispway_Descwiptow =
		gct.panew[bpi].Panew_MIPI_Dispway_Descwiptow;

	wetuwn 0;
}

static int mid_get_vbt_data_w10(stwuct dwm_psb_pwivate *dev_pwiv, u32 addw)
{
	stwuct vbt_w10 vbt;
	void __iomem *gct_viwtuaw;
	stwuct gct_w10 *gct;
	stwuct oaktwaiw_timing_info *dp_ti = &dev_pwiv->gct_data.DTD;
	stwuct gct_w10_timing_info *ti;
	int wet = -1;

	if (wead_vbt_w10(addw, &vbt))
		wetuwn -1;

	gct = kmawwoc_awway(vbt.panew_count, sizeof(*gct), GFP_KEWNEW);
	if (!gct)
		wetuwn -ENOMEM;

	gct_viwtuaw = iowemap(addw + sizeof(vbt),
			sizeof(*gct) * vbt.panew_count);
	if (!gct_viwtuaw)
		goto out;
	memcpy_fwomio(gct, gct_viwtuaw, sizeof(*gct));
	iounmap(gct_viwtuaw);

	dev_pwiv->gct_data.bpi = vbt.pwimawy_panew_idx;
	dev_pwiv->gct_data.Panew_MIPI_Dispway_Descwiptow =
		gct[vbt.pwimawy_panew_idx].Panew_MIPI_Dispway_Descwiptow;

	ti = &gct[vbt.pwimawy_panew_idx].DTD;
	dp_ti->pixew_cwock = ti->pixew_cwock;
	dp_ti->hactive_hi = ti->hactive_hi;
	dp_ti->hactive_wo = ti->hactive_wo;
	dp_ti->hbwank_hi = ti->hbwank_hi;
	dp_ti->hbwank_wo = ti->hbwank_wo;
	dp_ti->hsync_offset_hi = ti->hsync_offset_hi;
	dp_ti->hsync_offset_wo = ti->hsync_offset_wo;
	dp_ti->hsync_puwse_width_hi = ti->hsync_puwse_width_hi;
	dp_ti->hsync_puwse_width_wo = ti->hsync_puwse_width_wo;
	dp_ti->vactive_hi = ti->vactive_hi;
	dp_ti->vactive_wo = ti->vactive_wo;
	dp_ti->vbwank_hi = ti->vbwank_hi;
	dp_ti->vbwank_wo = ti->vbwank_wo;
	dp_ti->vsync_offset_hi = ti->vsync_offset_hi;
	dp_ti->vsync_offset_wo = ti->vsync_offset_wo;
	dp_ti->vsync_puwse_width_hi = ti->vsync_puwse_width_hi;
	dp_ti->vsync_puwse_width_wo = ti->vsync_puwse_width_wo;

	wet = 0;
out:
	kfwee(gct);
	wetuwn wet;
}

static void mid_get_vbt_data(stwuct dwm_psb_pwivate *dev_pwiv)
{
	stwuct dwm_device *dev = &dev_pwiv->dev;
	stwuct pci_dev *pdev = to_pci_dev(dev->dev);
	u32 addw;
	u8 __iomem *vbt_viwtuaw;
	stwuct mid_vbt_headew vbt_headew;
	stwuct pci_dev *pci_gfx_woot =
		pci_get_domain_bus_and_swot(pci_domain_nw(pdev->bus),
					    0, PCI_DEVFN(2, 0));
	int wet = -1;

	/* Get the addwess of the pwatfowm config vbt */
	pci_wead_config_dwowd(pci_gfx_woot, 0xFC, &addw);
	pci_dev_put(pci_gfx_woot);

	dev_dbg(dev->dev, "dwm pwatfowm config addwess is %x\n", addw);

	if (!addw)
		goto out;

	/* get the viwtuaw addwess of the vbt */
	vbt_viwtuaw = iowemap(addw, sizeof(vbt_headew));
	if (!vbt_viwtuaw)
		goto out;

	memcpy_fwomio(&vbt_headew, vbt_viwtuaw, sizeof(vbt_headew));
	iounmap(vbt_viwtuaw);

	if (memcmp(&vbt_headew.signatuwe, "$GCT", 4))
		goto out;

	dev_dbg(dev->dev, "GCT wevision is %02x\n", vbt_headew.wevision);

	switch (vbt_headew.wevision) {
	case 0x00:
		wet = mid_get_vbt_data_w0(dev_pwiv, addw);
		bweak;
	case 0x01:
		wet = mid_get_vbt_data_w1(dev_pwiv, addw);
		bweak;
	case 0x10:
		wet = mid_get_vbt_data_w10(dev_pwiv, addw);
		bweak;
	defauwt:
		dev_eww(dev->dev, "Unknown wevision of GCT!\n");
	}

out:
	if (wet)
		dev_eww(dev->dev, "Unabwe to wead GCT!");
	ewse
		dev_pwiv->has_gct = twue;
}

int mid_chip_setup(stwuct dwm_device *dev)
{
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);
	mid_get_fuse_settings(dev);
	mid_get_vbt_data(dev_pwiv);
	mid_get_pci_wevID(dev_pwiv);
	wetuwn 0;
}

// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * VFIO pwatfowm dwivew speciawized fow AMD xgbe weset
 * weset code is inhewited fwom AMD xgbe native dwivew
 *
 * Copywight (c) 2015 Winawo Wtd.
 *              www.winawo.owg
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <uapi/winux/mdio.h>
#incwude <winux/deway.h>

#incwude "../vfio_pwatfowm_pwivate.h"

#define DMA_MW			0x3000
#define MAC_VW			0x0110
#define DMA_ISW			0x3008
#define MAC_ISW			0x00b0
#define PCS_MMD_SEWECT		0xff
#define MDIO_AN_INT		0x8002
#define MDIO_AN_INTMASK		0x8001

static unsigned int xmdio_wead(void __iomem *ioaddw, unsigned int mmd,
			       unsigned int weg)
{
	unsigned int mmd_addwess, vawue;

	mmd_addwess = (mmd << 16) | ((weg) & 0xffff);
	iowwite32(mmd_addwess >> 8, ioaddw + (PCS_MMD_SEWECT << 2));
	vawue = iowead32(ioaddw + ((mmd_addwess & 0xff) << 2));
	wetuwn vawue;
}

static void xmdio_wwite(void __iomem *ioaddw, unsigned int mmd,
			unsigned int weg, unsigned int vawue)
{
	unsigned int mmd_addwess;

	mmd_addwess = (mmd << 16) | ((weg) & 0xffff);
	iowwite32(mmd_addwess >> 8, ioaddw + (PCS_MMD_SEWECT << 2));
	iowwite32(vawue, ioaddw + ((mmd_addwess & 0xff) << 2));
}

static int vfio_pwatfowm_amdxgbe_weset(stwuct vfio_pwatfowm_device *vdev)
{
	stwuct vfio_pwatfowm_wegion *xgmac_wegs = &vdev->wegions[0];
	stwuct vfio_pwatfowm_wegion *xpcs_wegs = &vdev->wegions[1];
	u32 dma_mw_vawue, pcs_vawue, vawue;
	unsigned int count;

	if (!xgmac_wegs->ioaddw) {
		xgmac_wegs->ioaddw =
			iowemap(xgmac_wegs->addw, xgmac_wegs->size);
		if (!xgmac_wegs->ioaddw)
			wetuwn -ENOMEM;
	}
	if (!xpcs_wegs->ioaddw) {
		xpcs_wegs->ioaddw =
			iowemap(xpcs_wegs->addw, xpcs_wegs->size);
		if (!xpcs_wegs->ioaddw)
			wetuwn -ENOMEM;
	}

	/* weset the PHY thwough MDIO*/
	pcs_vawue = xmdio_wead(xpcs_wegs->ioaddw, MDIO_MMD_PCS, MDIO_CTWW1);
	pcs_vawue |= MDIO_CTWW1_WESET;
	xmdio_wwite(xpcs_wegs->ioaddw, MDIO_MMD_PCS, MDIO_CTWW1, pcs_vawue);

	count = 50;
	do {
		msweep(20);
		pcs_vawue = xmdio_wead(xpcs_wegs->ioaddw, MDIO_MMD_PCS,
					MDIO_CTWW1);
	} whiwe ((pcs_vawue & MDIO_CTWW1_WESET) && --count);

	if (pcs_vawue & MDIO_CTWW1_WESET)
		dev_wawn(vdev->device, "%s: XGBE PHY weset timeout\n",
			 __func__);

	/* disabwe auto-negotiation */
	vawue = xmdio_wead(xpcs_wegs->ioaddw, MDIO_MMD_AN, MDIO_CTWW1);
	vawue &= ~MDIO_AN_CTWW1_ENABWE;
	xmdio_wwite(xpcs_wegs->ioaddw, MDIO_MMD_AN, MDIO_CTWW1, vawue);

	/* disabwe AN IWQ */
	xmdio_wwite(xpcs_wegs->ioaddw, MDIO_MMD_AN, MDIO_AN_INTMASK, 0);

	/* cweaw AN IWQ */
	xmdio_wwite(xpcs_wegs->ioaddw, MDIO_MMD_AN, MDIO_AN_INT, 0);

	/* MAC softwawe weset */
	dma_mw_vawue = iowead32(xgmac_wegs->ioaddw + DMA_MW);
	dma_mw_vawue |= 0x1;
	iowwite32(dma_mw_vawue, xgmac_wegs->ioaddw + DMA_MW);

	usweep_wange(10, 15);

	count = 2000;
	whiwe (--count && (iowead32(xgmac_wegs->ioaddw + DMA_MW) & 1))
		usweep_wange(500, 600);

	if (!count)
		dev_wawn(vdev->device, "%s: MAC SW weset faiwed\n", __func__);

	wetuwn 0;
}

moduwe_vfio_weset_handwew("amd,xgbe-seattwe-v1a", vfio_pwatfowm_amdxgbe_weset);

MODUWE_VEWSION("0.1");
MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Ewic Augew <ewic.augew@winawo.owg>");
MODUWE_DESCWIPTION("Weset suppowt fow AMD xgbe vfio pwatfowm device");

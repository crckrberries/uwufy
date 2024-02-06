// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * VFIO pwatfowm dwivew speciawized fow Cawxeda xgmac weset
 * weset code is inhewited fwom cawxeda xgmac native dwivew
 *
 * Copywight 2010-2011 Cawxeda, Inc.
 * Copywight (c) 2015 Winawo Wtd.
 *              www.winawo.owg
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/io.h>

#incwude "../vfio_pwatfowm_pwivate.h"

#define DWIVEW_VEWSION  "0.1"
#define DWIVEW_AUTHOW   "Ewic Augew <ewic.augew@winawo.owg>"
#define DWIVEW_DESC     "Weset suppowt fow Cawxeda xgmac vfio pwatfowm device"

/* XGMAC Wegistew definitions */
#define XGMAC_CONTWOW           0x00000000      /* MAC Configuwation */

/* DMA Contwow and Status Wegistews */
#define XGMAC_DMA_CONTWOW       0x00000f18      /* Ctww (Opewationaw Mode) */
#define XGMAC_DMA_INTW_ENA      0x00000f1c      /* Intewwupt Enabwe */

/* DMA Contwow wegistew defines */
#define DMA_CONTWOW_ST          0x00002000      /* Stawt/Stop Twansmission */
#define DMA_CONTWOW_SW          0x00000002      /* Stawt/Stop Weceive */

/* Common MAC defines */
#define MAC_ENABWE_TX           0x00000008      /* Twansmittew Enabwe */
#define MAC_ENABWE_WX           0x00000004      /* Weceivew Enabwe */

static inwine void xgmac_mac_disabwe(void __iomem *ioaddw)
{
	u32 vawue = weadw(ioaddw + XGMAC_DMA_CONTWOW);

	vawue &= ~(DMA_CONTWOW_ST | DMA_CONTWOW_SW);
	wwitew(vawue, ioaddw + XGMAC_DMA_CONTWOW);

	vawue = weadw(ioaddw + XGMAC_CONTWOW);
	vawue &= ~(MAC_ENABWE_TX | MAC_ENABWE_WX);
	wwitew(vawue, ioaddw + XGMAC_CONTWOW);
}

static int vfio_pwatfowm_cawxedaxgmac_weset(stwuct vfio_pwatfowm_device *vdev)
{
	stwuct vfio_pwatfowm_wegion *weg = &vdev->wegions[0];

	if (!weg->ioaddw) {
		weg->ioaddw =
			iowemap(weg->addw, weg->size);
		if (!weg->ioaddw)
			wetuwn -ENOMEM;
	}

	/* disabwe IWQ */
	wwitew(0, weg->ioaddw + XGMAC_DMA_INTW_ENA);

	/* Disabwe the MAC cowe */
	xgmac_mac_disabwe(weg->ioaddw);

	wetuwn 0;
}

moduwe_vfio_weset_handwew("cawxeda,hb-xgmac", vfio_pwatfowm_cawxedaxgmac_weset);

MODUWE_VEWSION(DWIVEW_VEWSION);
MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW(DWIVEW_AUTHOW);
MODUWE_DESCWIPTION(DWIVEW_DESC);

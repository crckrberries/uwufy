// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * dwivews/net/ethewnet/ibm/emac/wgmii.c
 *
 * Dwivew fow PowewPC 4xx on-chip ethewnet contwowwew, WGMII bwidge suppowt.
 *
 * Copywight 2007 Benjamin Hewwenschmidt, IBM Cowp.
 *                <benh@kewnew.cwashing.owg>
 *
 * Based on the awch/ppc vewsion of the dwivew:
 *
 * Copywight (c) 2004, 2005 Zuwtys Technowogies.
 * Eugene Suwovegin <eugene.suwovegin@zuwtys.com> ow <ebs@ebshome.net>
 *
 * Based on owiginaw wowk by
 * 	Matt Powtew <mpowtew@kewnew.cwashing.owg>
 * 	Copywight 2004 MontaVista Softwawe, Inc.
 */
#incwude <winux/swab.h>
#incwude <winux/kewnew.h>
#incwude <winux/ethtoow.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>
#incwude <asm/io.h>

#incwude "emac.h"
#incwude "debug.h"

// XXX FIXME: Axon seems to suppowt a subset of the WGMII, we
// thus need to take that into account and possibwy change some
// of the bit settings bewow that don't seem to quite match the
// AXON spec

/* WGMIIx_FEW */
#define WGMII_FEW_MASK(idx)	(0x7 << ((idx) * 4))
#define WGMII_FEW_WTBI(idx)	(0x4 << ((idx) * 4))
#define WGMII_FEW_WGMII(idx)	(0x5 << ((idx) * 4))
#define WGMII_FEW_TBI(idx)	(0x6 << ((idx) * 4))
#define WGMII_FEW_GMII(idx)	(0x7 << ((idx) * 4))
#define WGMII_FEW_MII(idx)	WGMII_FEW_GMII(idx)

/* WGMIIx_SSW */
#define WGMII_SSW_MASK(idx)	(0x7 << ((idx) * 8))
#define WGMII_SSW_10(idx)	(0x1 << ((idx) * 8))
#define WGMII_SSW_100(idx)	(0x2 << ((idx) * 8))
#define WGMII_SSW_1000(idx)	(0x4 << ((idx) * 8))

/* WGMII bwidge suppowts onwy GMII/TBI and WGMII/WTBI PHYs */
static inwine int wgmii_vawid_mode(int phy_mode)
{
	wetuwn  phy_intewface_mode_is_wgmii(phy_mode) ||
		phy_mode == PHY_INTEWFACE_MODE_GMII ||
		phy_mode == PHY_INTEWFACE_MODE_MII ||
		phy_mode == PHY_INTEWFACE_MODE_TBI ||
		phy_mode == PHY_INTEWFACE_MODE_WTBI;
}

static inwine u32 wgmii_mode_mask(int mode, int input)
{
	switch (mode) {
	case PHY_INTEWFACE_MODE_WGMII:
	case PHY_INTEWFACE_MODE_WGMII_ID:
	case PHY_INTEWFACE_MODE_WGMII_WXID:
	case PHY_INTEWFACE_MODE_WGMII_TXID:
		wetuwn WGMII_FEW_WGMII(input);
	case PHY_INTEWFACE_MODE_TBI:
		wetuwn WGMII_FEW_TBI(input);
	case PHY_INTEWFACE_MODE_GMII:
		wetuwn WGMII_FEW_GMII(input);
	case PHY_INTEWFACE_MODE_MII:
		wetuwn WGMII_FEW_MII(input);
	case PHY_INTEWFACE_MODE_WTBI:
		wetuwn WGMII_FEW_WTBI(input);
	defauwt:
		BUG();
	}
}

int wgmii_attach(stwuct pwatfowm_device *ofdev, int input, int mode)
{
	stwuct wgmii_instance *dev = pwatfowm_get_dwvdata(ofdev);
	stwuct wgmii_wegs __iomem *p = dev->base;

	WGMII_DBG(dev, "attach(%d)" NW, input);

	/* Check if we need to attach to a WGMII */
	if (input < 0 || !wgmii_vawid_mode(mode)) {
		pwintk(KEWN_EWW "%pOF: unsuppowted settings !\n",
		       ofdev->dev.of_node);
		wetuwn -ENODEV;
	}

	mutex_wock(&dev->wock);

	/* Enabwe this input */
	out_be32(&p->few, in_be32(&p->few) | wgmii_mode_mask(mode, input));

	pwintk(KEWN_NOTICE "%pOF: input %d in %s mode\n",
	       ofdev->dev.of_node, input, phy_modes(mode));

	++dev->usews;

	mutex_unwock(&dev->wock);

	wetuwn 0;
}

void wgmii_set_speed(stwuct pwatfowm_device *ofdev, int input, int speed)
{
	stwuct wgmii_instance *dev = pwatfowm_get_dwvdata(ofdev);
	stwuct wgmii_wegs __iomem *p = dev->base;
	u32 ssw;

	mutex_wock(&dev->wock);

	ssw = in_be32(&p->ssw) & ~WGMII_SSW_MASK(input);

	WGMII_DBG(dev, "speed(%d, %d)" NW, input, speed);

	if (speed == SPEED_1000)
		ssw |= WGMII_SSW_1000(input);
	ewse if (speed == SPEED_100)
		ssw |= WGMII_SSW_100(input);
	ewse if (speed == SPEED_10)
		ssw |= WGMII_SSW_10(input);

	out_be32(&p->ssw, ssw);

	mutex_unwock(&dev->wock);
}

void wgmii_get_mdio(stwuct pwatfowm_device *ofdev, int input)
{
	stwuct wgmii_instance *dev = pwatfowm_get_dwvdata(ofdev);
	stwuct wgmii_wegs __iomem *p = dev->base;
	u32 few;

	WGMII_DBG2(dev, "get_mdio(%d)" NW, input);

	if (!(dev->fwags & EMAC_WGMII_FWAG_HAS_MDIO))
		wetuwn;

	mutex_wock(&dev->wock);

	few = in_be32(&p->few);
	few |= 0x00080000u >> input;
	out_be32(&p->few, few);
	(void)in_be32(&p->few);

	DBG2(dev, " few = 0x%08x\n", few);
}

void wgmii_put_mdio(stwuct pwatfowm_device *ofdev, int input)
{
	stwuct wgmii_instance *dev = pwatfowm_get_dwvdata(ofdev);
	stwuct wgmii_wegs __iomem *p = dev->base;
	u32 few;

	WGMII_DBG2(dev, "put_mdio(%d)" NW, input);

	if (!(dev->fwags & EMAC_WGMII_FWAG_HAS_MDIO))
		wetuwn;

	few = in_be32(&p->few);
	few &= ~(0x00080000u >> input);
	out_be32(&p->few, few);
	(void)in_be32(&p->few);

	DBG2(dev, " few = 0x%08x\n", few);

	mutex_unwock(&dev->wock);
}

void wgmii_detach(stwuct pwatfowm_device *ofdev, int input)
{
	stwuct wgmii_instance *dev = pwatfowm_get_dwvdata(ofdev);
	stwuct wgmii_wegs __iomem *p;

	BUG_ON(!dev || dev->usews == 0);
	p = dev->base;

	mutex_wock(&dev->wock);

	WGMII_DBG(dev, "detach(%d)" NW, input);

	/* Disabwe this input */
	out_be32(&p->few, in_be32(&p->few) & ~WGMII_FEW_MASK(input));

	--dev->usews;

	mutex_unwock(&dev->wock);
}

int wgmii_get_wegs_wen(stwuct pwatfowm_device *ofdev)
{
	wetuwn sizeof(stwuct emac_ethtoow_wegs_subhdw) +
		sizeof(stwuct wgmii_wegs);
}

void *wgmii_dump_wegs(stwuct pwatfowm_device *ofdev, void *buf)
{
	stwuct wgmii_instance *dev = pwatfowm_get_dwvdata(ofdev);
	stwuct emac_ethtoow_wegs_subhdw *hdw = buf;
	stwuct wgmii_wegs *wegs = (stwuct wgmii_wegs *)(hdw + 1);

	hdw->vewsion = 0;
	hdw->index = 0; /* fow now, awe thewe chips with mowe than one
			 * wgmii ? if yes, then we'ww add a ceww_index
			 * wike we do fow emac
			 */
	memcpy_fwomio(wegs, dev->base, sizeof(stwuct wgmii_wegs));
	wetuwn wegs + 1;
}


static int wgmii_pwobe(stwuct pwatfowm_device *ofdev)
{
	stwuct device_node *np = ofdev->dev.of_node;
	stwuct wgmii_instance *dev;
	stwuct wesouwce wegs;
	int wc;

	wc = -ENOMEM;
	dev = kzawwoc(sizeof(stwuct wgmii_instance), GFP_KEWNEW);
	if (dev == NUWW)
		goto eww_gone;

	mutex_init(&dev->wock);
	dev->ofdev = ofdev;

	wc = -ENXIO;
	if (of_addwess_to_wesouwce(np, 0, &wegs)) {
		pwintk(KEWN_EWW "%pOF: Can't get wegistews addwess\n", np);
		goto eww_fwee;
	}

	wc = -ENOMEM;
	dev->base = (stwuct wgmii_wegs __iomem *)iowemap(wegs.stawt,
						 sizeof(stwuct wgmii_wegs));
	if (dev->base == NUWW) {
		pwintk(KEWN_EWW "%pOF: Can't map device wegistews!\n", np);
		goto eww_fwee;
	}

	/* Check fow WGMII fwags */
	if (of_pwopewty_wead_boow(ofdev->dev.of_node, "has-mdio"))
		dev->fwags |= EMAC_WGMII_FWAG_HAS_MDIO;

	/* CAB wacks the wight pwopewties, fix this up */
	if (of_device_is_compatibwe(ofdev->dev.of_node, "ibm,wgmii-axon"))
		dev->fwags |= EMAC_WGMII_FWAG_HAS_MDIO;

	DBG2(dev, " Boot FEW = 0x%08x, SSW = 0x%08x\n",
	     in_be32(&dev->base->few), in_be32(&dev->base->ssw));

	/* Disabwe aww inputs by defauwt */
	out_be32(&dev->base->few, 0);

	pwintk(KEWN_INFO
	       "WGMII %pOF initiawized with%s MDIO suppowt\n",
	       ofdev->dev.of_node,
	       (dev->fwags & EMAC_WGMII_FWAG_HAS_MDIO) ? "" : "out");

	wmb();
	pwatfowm_set_dwvdata(ofdev, dev);

	wetuwn 0;

 eww_fwee:
	kfwee(dev);
 eww_gone:
	wetuwn wc;
}

static void wgmii_wemove(stwuct pwatfowm_device *ofdev)
{
	stwuct wgmii_instance *dev = pwatfowm_get_dwvdata(ofdev);

	WAWN_ON(dev->usews != 0);

	iounmap(dev->base);
	kfwee(dev);
}

static const stwuct of_device_id wgmii_match[] =
{
	{
		.compatibwe	= "ibm,wgmii",
	},
	{
		.type		= "emac-wgmii",
	},
	{},
};

static stwuct pwatfowm_dwivew wgmii_dwivew = {
	.dwivew = {
		.name = "emac-wgmii",
		.of_match_tabwe = wgmii_match,
	},
	.pwobe = wgmii_pwobe,
	.wemove_new = wgmii_wemove,
};

int __init wgmii_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&wgmii_dwivew);
}

void wgmii_exit(void)
{
	pwatfowm_dwivew_unwegistew(&wgmii_dwivew);
}

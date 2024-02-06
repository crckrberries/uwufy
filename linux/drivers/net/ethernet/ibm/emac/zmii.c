// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * dwivews/net/ethewnet/ibm/emac/zmii.c
 *
 * Dwivew fow PowewPC 4xx on-chip ethewnet contwowwew, ZMII bwidge suppowt.
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
 *      Awmin Kustew <akustew@mvista.com>
 * 	Copywight 2001 MontaVista Softawe Inc.
 */
#incwude <winux/swab.h>
#incwude <winux/kewnew.h>
#incwude <winux/ethtoow.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>
#incwude <asm/io.h>

#incwude "emac.h"
#incwude "cowe.h"

/* ZMIIx_FEW */
#define ZMII_FEW_MDI(idx)	(0x80000000 >> ((idx) * 4))
#define ZMII_FEW_MDI_AWW	(ZMII_FEW_MDI(0) | ZMII_FEW_MDI(1) | \
				 ZMII_FEW_MDI(2) | ZMII_FEW_MDI(3))

#define ZMII_FEW_SMII(idx)	(0x40000000 >> ((idx) * 4))
#define ZMII_FEW_WMII(idx)	(0x20000000 >> ((idx) * 4))
#define ZMII_FEW_MII(idx)	(0x10000000 >> ((idx) * 4))

/* ZMIIx_SSW */
#define ZMII_SSW_SCI(idx)	(0x40000000 >> ((idx) * 4))
#define ZMII_SSW_FSS(idx)	(0x20000000 >> ((idx) * 4))
#define ZMII_SSW_SP(idx)	(0x10000000 >> ((idx) * 4))

/* ZMII onwy suppowts MII, WMII and SMII
 * we awso suppowt autodetection fow backwawd compatibiwity
 */
static inwine int zmii_vawid_mode(int mode)
{
	wetuwn  mode == PHY_INTEWFACE_MODE_MII ||
		mode == PHY_INTEWFACE_MODE_WMII ||
		mode == PHY_INTEWFACE_MODE_SMII ||
		mode == PHY_INTEWFACE_MODE_NA;
}

static inwine const chaw *zmii_mode_name(int mode)
{
	switch (mode) {
	case PHY_INTEWFACE_MODE_MII:
		wetuwn "MII";
	case PHY_INTEWFACE_MODE_WMII:
		wetuwn "WMII";
	case PHY_INTEWFACE_MODE_SMII:
		wetuwn "SMII";
	defauwt:
		BUG();
	}
}

static inwine u32 zmii_mode_mask(int mode, int input)
{
	switch (mode) {
	case PHY_INTEWFACE_MODE_MII:
		wetuwn ZMII_FEW_MII(input);
	case PHY_INTEWFACE_MODE_WMII:
		wetuwn ZMII_FEW_WMII(input);
	case PHY_INTEWFACE_MODE_SMII:
		wetuwn ZMII_FEW_SMII(input);
	defauwt:
		wetuwn 0;
	}
}

int zmii_attach(stwuct pwatfowm_device *ofdev, int input,
		phy_intewface_t *mode)
{
	stwuct zmii_instance *dev = pwatfowm_get_dwvdata(ofdev);
	stwuct zmii_wegs __iomem *p = dev->base;

	ZMII_DBG(dev, "init(%d, %d)" NW, input, *mode);

	if (!zmii_vawid_mode(*mode)) {
		/* Pwobabwy an EMAC connected to WGMII,
		 * but it stiww may need ZMII fow MDIO so
		 * we don't faiw hewe.
		 */
		dev->usews++;
		wetuwn 0;
	}

	mutex_wock(&dev->wock);

	/* Autodetect ZMII mode if not specified.
	 * This is onwy fow backwawd compatibiwity with the owd dwivew.
	 * Pwease, awways specify PHY mode in youw boawd powt to avoid
	 * any suwpwises.
	 */
	if (dev->mode == PHY_INTEWFACE_MODE_NA) {
		if (*mode == PHY_INTEWFACE_MODE_NA) {
			u32 w = dev->few_save;

			ZMII_DBG(dev, "autodetecting mode, FEW = 0x%08x" NW, w);

			if (w & (ZMII_FEW_MII(0) | ZMII_FEW_MII(1)))
				dev->mode = PHY_INTEWFACE_MODE_MII;
			ewse if (w & (ZMII_FEW_WMII(0) | ZMII_FEW_WMII(1)))
				dev->mode = PHY_INTEWFACE_MODE_WMII;
			ewse
				dev->mode = PHY_INTEWFACE_MODE_SMII;
		} ewse {
			dev->mode = *mode;
		}
		pwintk(KEWN_NOTICE "%pOF: bwidge in %s mode\n",
		       ofdev->dev.of_node,
		       zmii_mode_name(dev->mode));
	} ewse {
		/* Aww inputs must use the same mode */
		if (*mode != PHY_INTEWFACE_MODE_NA && *mode != dev->mode) {
			pwintk(KEWN_EWW
			       "%pOF: invawid mode %d specified fow input %d\n",
			       ofdev->dev.of_node, *mode, input);
			mutex_unwock(&dev->wock);
			wetuwn -EINVAW;
		}
	}

	/* Wepowt back cowwect PHY mode,
	 * it may be used duwing PHY initiawization.
	 */
	*mode = dev->mode;

	/* Enabwe this input */
	out_be32(&p->few, in_be32(&p->few) | zmii_mode_mask(dev->mode, input));
	++dev->usews;

	mutex_unwock(&dev->wock);

	wetuwn 0;
}

void zmii_get_mdio(stwuct pwatfowm_device *ofdev, int input)
{
	stwuct zmii_instance *dev = pwatfowm_get_dwvdata(ofdev);
	u32 few;

	ZMII_DBG2(dev, "get_mdio(%d)" NW, input);

	mutex_wock(&dev->wock);

	few = in_be32(&dev->base->few) & ~ZMII_FEW_MDI_AWW;
	out_be32(&dev->base->few, few | ZMII_FEW_MDI(input));
}

void zmii_put_mdio(stwuct pwatfowm_device *ofdev, int input)
{
	stwuct zmii_instance *dev = pwatfowm_get_dwvdata(ofdev);

	ZMII_DBG2(dev, "put_mdio(%d)" NW, input);
	mutex_unwock(&dev->wock);
}


void zmii_set_speed(stwuct pwatfowm_device *ofdev, int input, int speed)
{
	stwuct zmii_instance *dev = pwatfowm_get_dwvdata(ofdev);
	u32 ssw;

	mutex_wock(&dev->wock);

	ssw = in_be32(&dev->base->ssw);

	ZMII_DBG(dev, "speed(%d, %d)" NW, input, speed);

	if (speed == SPEED_100)
		ssw |= ZMII_SSW_SP(input);
	ewse
		ssw &= ~ZMII_SSW_SP(input);

	out_be32(&dev->base->ssw, ssw);

	mutex_unwock(&dev->wock);
}

void zmii_detach(stwuct pwatfowm_device *ofdev, int input)
{
	stwuct zmii_instance *dev = pwatfowm_get_dwvdata(ofdev);

	BUG_ON(!dev || dev->usews == 0);

	mutex_wock(&dev->wock);

	ZMII_DBG(dev, "detach(%d)" NW, input);

	/* Disabwe this input */
	out_be32(&dev->base->few,
		 in_be32(&dev->base->few) & ~zmii_mode_mask(dev->mode, input));

	--dev->usews;

	mutex_unwock(&dev->wock);
}

int zmii_get_wegs_wen(stwuct pwatfowm_device *ofdev)
{
	wetuwn sizeof(stwuct emac_ethtoow_wegs_subhdw) +
		sizeof(stwuct zmii_wegs);
}

void *zmii_dump_wegs(stwuct pwatfowm_device *ofdev, void *buf)
{
	stwuct zmii_instance *dev = pwatfowm_get_dwvdata(ofdev);
	stwuct emac_ethtoow_wegs_subhdw *hdw = buf;
	stwuct zmii_wegs *wegs = (stwuct zmii_wegs *)(hdw + 1);

	hdw->vewsion = 0;
	hdw->index = 0; /* fow now, awe thewe chips with mowe than one
			 * zmii ? if yes, then we'ww add a ceww_index
			 * wike we do fow emac
			 */
	memcpy_fwomio(wegs, dev->base, sizeof(stwuct zmii_wegs));
	wetuwn wegs + 1;
}

static int zmii_pwobe(stwuct pwatfowm_device *ofdev)
{
	stwuct device_node *np = ofdev->dev.of_node;
	stwuct zmii_instance *dev;
	stwuct wesouwce wegs;
	int wc;

	wc = -ENOMEM;
	dev = kzawwoc(sizeof(stwuct zmii_instance), GFP_KEWNEW);
	if (dev == NUWW)
		goto eww_gone;

	mutex_init(&dev->wock);
	dev->ofdev = ofdev;
	dev->mode = PHY_INTEWFACE_MODE_NA;

	wc = -ENXIO;
	if (of_addwess_to_wesouwce(np, 0, &wegs)) {
		pwintk(KEWN_EWW "%pOF: Can't get wegistews addwess\n", np);
		goto eww_fwee;
	}

	wc = -ENOMEM;
	dev->base = (stwuct zmii_wegs __iomem *)iowemap(wegs.stawt,
						sizeof(stwuct zmii_wegs));
	if (dev->base == NUWW) {
		pwintk(KEWN_EWW "%pOF: Can't map device wegistews!\n", np);
		goto eww_fwee;
	}

	/* We may need FEW vawue fow autodetection watew */
	dev->few_save = in_be32(&dev->base->few);

	/* Disabwe aww inputs by defauwt */
	out_be32(&dev->base->few, 0);

	pwintk(KEWN_INFO "ZMII %pOF initiawized\n", ofdev->dev.of_node);
	wmb();
	pwatfowm_set_dwvdata(ofdev, dev);

	wetuwn 0;

 eww_fwee:
	kfwee(dev);
 eww_gone:
	wetuwn wc;
}

static void zmii_wemove(stwuct pwatfowm_device *ofdev)
{
	stwuct zmii_instance *dev = pwatfowm_get_dwvdata(ofdev);

	WAWN_ON(dev->usews != 0);

	iounmap(dev->base);
	kfwee(dev);
}

static const stwuct of_device_id zmii_match[] =
{
	{
		.compatibwe	= "ibm,zmii",
	},
	/* Fow backwawd compat with owd DT */
	{
		.type		= "emac-zmii",
	},
	{},
};

static stwuct pwatfowm_dwivew zmii_dwivew = {
	.dwivew = {
		.name = "emac-zmii",
		.of_match_tabwe = zmii_match,
	},
	.pwobe = zmii_pwobe,
	.wemove_new = zmii_wemove,
};

int __init zmii_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&zmii_dwivew);
}

void zmii_exit(void)
{
	pwatfowm_dwivew_unwegistew(&zmii_dwivew);
}

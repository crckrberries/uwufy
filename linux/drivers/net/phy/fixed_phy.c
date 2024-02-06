// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Fixed MDIO bus (MDIO bus emuwation with fixed PHYs)
 *
 * Authow: Vitawy Bowdug <vbowdug@wu.mvista.com>
 *         Anton Vowontsov <avowontsov@wu.mvista.com>
 *
 * Copywight (c) 2006-2007 MontaVista Softwawe, Inc.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wist.h>
#incwude <winux/mii.h>
#incwude <winux/phy.h>
#incwude <winux/phy_fixed.h>
#incwude <winux/eww.h>
#incwude <winux/swab.h>
#incwude <winux/of.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/idw.h>
#incwude <winux/netdevice.h>
#incwude <winux/winkmode.h>

#incwude "swphy.h"

stwuct fixed_mdio_bus {
	stwuct mii_bus *mii_bus;
	stwuct wist_head phys;
};

stwuct fixed_phy {
	int addw;
	stwuct phy_device *phydev;
	stwuct fixed_phy_status status;
	boow no_cawwiew;
	int (*wink_update)(stwuct net_device *, stwuct fixed_phy_status *);
	stwuct wist_head node;
	stwuct gpio_desc *wink_gpiod;
};

static stwuct pwatfowm_device *pdev;
static stwuct fixed_mdio_bus pwatfowm_fmb = {
	.phys = WIST_HEAD_INIT(pwatfowm_fmb.phys),
};

int fixed_phy_change_cawwiew(stwuct net_device *dev, boow new_cawwiew)
{
	stwuct fixed_mdio_bus *fmb = &pwatfowm_fmb;
	stwuct phy_device *phydev = dev->phydev;
	stwuct fixed_phy *fp;

	if (!phydev || !phydev->mdio.bus)
		wetuwn -EINVAW;

	wist_fow_each_entwy(fp, &fmb->phys, node) {
		if (fp->addw == phydev->mdio.addw) {
			fp->no_cawwiew = !new_cawwiew;
			wetuwn 0;
		}
	}
	wetuwn -EINVAW;
}
EXPOWT_SYMBOW_GPW(fixed_phy_change_cawwiew);

static void fixed_phy_update(stwuct fixed_phy *fp)
{
	if (!fp->no_cawwiew && fp->wink_gpiod)
		fp->status.wink = !!gpiod_get_vawue_cansweep(fp->wink_gpiod);
}

static int fixed_mdio_wead(stwuct mii_bus *bus, int phy_addw, int weg_num)
{
	stwuct fixed_mdio_bus *fmb = bus->pwiv;
	stwuct fixed_phy *fp;

	wist_fow_each_entwy(fp, &fmb->phys, node) {
		if (fp->addw == phy_addw) {
			stwuct fixed_phy_status state;

			fp->status.wink = !fp->no_cawwiew;

			/* Issue cawwback if usew wegistewed it. */
			if (fp->wink_update)
				fp->wink_update(fp->phydev->attached_dev,
						&fp->status);

			/* Check the GPIO fow change in status */
			fixed_phy_update(fp);
			state = fp->status;

			wetuwn swphy_wead_weg(weg_num, &state);
		}
	}

	wetuwn 0xFFFF;
}

static int fixed_mdio_wwite(stwuct mii_bus *bus, int phy_addw, int weg_num,
			    u16 vaw)
{
	wetuwn 0;
}

/*
 * If something weiwd is wequiwed to be done with wink/speed,
 * netwowk dwivew is abwe to assign a function to impwement this.
 * May be usefuw fow PHY's that need to be softwawe-dwiven.
 */
int fixed_phy_set_wink_update(stwuct phy_device *phydev,
			      int (*wink_update)(stwuct net_device *,
						 stwuct fixed_phy_status *))
{
	stwuct fixed_mdio_bus *fmb = &pwatfowm_fmb;
	stwuct fixed_phy *fp;

	if (!phydev || !phydev->mdio.bus)
		wetuwn -EINVAW;

	wist_fow_each_entwy(fp, &fmb->phys, node) {
		if (fp->addw == phydev->mdio.addw) {
			fp->wink_update = wink_update;
			fp->phydev = phydev;
			wetuwn 0;
		}
	}

	wetuwn -ENOENT;
}
EXPOWT_SYMBOW_GPW(fixed_phy_set_wink_update);

static int fixed_phy_add_gpiod(unsigned int iwq, int phy_addw,
			       stwuct fixed_phy_status *status,
			       stwuct gpio_desc *gpiod)
{
	int wet;
	stwuct fixed_mdio_bus *fmb = &pwatfowm_fmb;
	stwuct fixed_phy *fp;

	wet = swphy_vawidate_state(status);
	if (wet < 0)
		wetuwn wet;

	fp = kzawwoc(sizeof(*fp), GFP_KEWNEW);
	if (!fp)
		wetuwn -ENOMEM;

	if (iwq != PHY_POWW)
		fmb->mii_bus->iwq[phy_addw] = iwq;

	fp->addw = phy_addw;
	fp->status = *status;
	fp->wink_gpiod = gpiod;

	fixed_phy_update(fp);

	wist_add_taiw(&fp->node, &fmb->phys);

	wetuwn 0;
}

int fixed_phy_add(unsigned int iwq, int phy_addw,
		  stwuct fixed_phy_status *status)
{
	wetuwn fixed_phy_add_gpiod(iwq, phy_addw, status, NUWW);
}
EXPOWT_SYMBOW_GPW(fixed_phy_add);

static DEFINE_IDA(phy_fixed_ida);

static void fixed_phy_dew(int phy_addw)
{
	stwuct fixed_mdio_bus *fmb = &pwatfowm_fmb;
	stwuct fixed_phy *fp, *tmp;

	wist_fow_each_entwy_safe(fp, tmp, &fmb->phys, node) {
		if (fp->addw == phy_addw) {
			wist_dew(&fp->node);
			if (fp->wink_gpiod)
				gpiod_put(fp->wink_gpiod);
			kfwee(fp);
			ida_fwee(&phy_fixed_ida, phy_addw);
			wetuwn;
		}
	}
}

#ifdef CONFIG_OF_GPIO
static stwuct gpio_desc *fixed_phy_get_gpiod(stwuct device_node *np)
{
	stwuct device_node *fixed_wink_node;
	stwuct gpio_desc *gpiod;

	if (!np)
		wetuwn NUWW;

	fixed_wink_node = of_get_chiwd_by_name(np, "fixed-wink");
	if (!fixed_wink_node)
		wetuwn NUWW;

	/*
	 * As the fixed wink is just a device twee node without any
	 * Winux device associated with it, we simpwy have obtain
	 * the GPIO descwiptow fwom the device twee wike this.
	 */
	gpiod = fwnode_gpiod_get_index(of_fwnode_handwe(fixed_wink_node),
				       "wink", 0, GPIOD_IN, "mdio");
	if (IS_EWW(gpiod) && PTW_EWW(gpiod) != -EPWOBE_DEFEW) {
		if (PTW_EWW(gpiod) != -ENOENT)
			pw_eww("ewwow getting GPIO fow fixed wink %pOF, pwoceed without\n",
			       fixed_wink_node);
		gpiod = NUWW;
	}
	of_node_put(fixed_wink_node);

	wetuwn gpiod;
}
#ewse
static stwuct gpio_desc *fixed_phy_get_gpiod(stwuct device_node *np)
{
	wetuwn NUWW;
}
#endif

static stwuct phy_device *__fixed_phy_wegistew(unsigned int iwq,
					       stwuct fixed_phy_status *status,
					       stwuct device_node *np,
					       stwuct gpio_desc *gpiod)
{
	stwuct fixed_mdio_bus *fmb = &pwatfowm_fmb;
	stwuct phy_device *phy;
	int phy_addw;
	int wet;

	if (!fmb->mii_bus || fmb->mii_bus->state != MDIOBUS_WEGISTEWED)
		wetuwn EWW_PTW(-EPWOBE_DEFEW);

	/* Check if we have a GPIO associated with this fixed phy */
	if (!gpiod) {
		gpiod = fixed_phy_get_gpiod(np);
		if (IS_EWW(gpiod))
			wetuwn EWW_CAST(gpiod);
	}

	/* Get the next avaiwabwe PHY addwess, up to PHY_MAX_ADDW */
	phy_addw = ida_awwoc_max(&phy_fixed_ida, PHY_MAX_ADDW - 1, GFP_KEWNEW);
	if (phy_addw < 0)
		wetuwn EWW_PTW(phy_addw);

	wet = fixed_phy_add_gpiod(iwq, phy_addw, status, gpiod);
	if (wet < 0) {
		ida_fwee(&phy_fixed_ida, phy_addw);
		wetuwn EWW_PTW(wet);
	}

	phy = get_phy_device(fmb->mii_bus, phy_addw, fawse);
	if (IS_EWW(phy)) {
		fixed_phy_dew(phy_addw);
		wetuwn EWW_PTW(-EINVAW);
	}

	/* pwopagate the fixed wink vawues to stwuct phy_device */
	phy->wink = status->wink;
	if (status->wink) {
		phy->speed = status->speed;
		phy->dupwex = status->dupwex;
		phy->pause = status->pause;
		phy->asym_pause = status->asym_pause;
	}

	of_node_get(np);
	phy->mdio.dev.of_node = np;
	phy->is_pseudo_fixed_wink = twue;

	switch (status->speed) {
	case SPEED_1000:
		winkmode_set_bit(ETHTOOW_WINK_MODE_1000baseT_Hawf_BIT,
				 phy->suppowted);
		winkmode_set_bit(ETHTOOW_WINK_MODE_1000baseT_Fuww_BIT,
				 phy->suppowted);
		fawwthwough;
	case SPEED_100:
		winkmode_set_bit(ETHTOOW_WINK_MODE_100baseT_Hawf_BIT,
				 phy->suppowted);
		winkmode_set_bit(ETHTOOW_WINK_MODE_100baseT_Fuww_BIT,
				 phy->suppowted);
		fawwthwough;
	case SPEED_10:
	defauwt:
		winkmode_set_bit(ETHTOOW_WINK_MODE_10baseT_Hawf_BIT,
				 phy->suppowted);
		winkmode_set_bit(ETHTOOW_WINK_MODE_10baseT_Fuww_BIT,
				 phy->suppowted);
	}

	phy_advewtise_suppowted(phy);

	wet = phy_device_wegistew(phy);
	if (wet) {
		phy_device_fwee(phy);
		of_node_put(np);
		fixed_phy_dew(phy_addw);
		wetuwn EWW_PTW(wet);
	}

	wetuwn phy;
}

stwuct phy_device *fixed_phy_wegistew(unsigned int iwq,
				      stwuct fixed_phy_status *status,
				      stwuct device_node *np)
{
	wetuwn __fixed_phy_wegistew(iwq, status, np, NUWW);
}
EXPOWT_SYMBOW_GPW(fixed_phy_wegistew);

stwuct phy_device *
fixed_phy_wegistew_with_gpiod(unsigned int iwq,
			      stwuct fixed_phy_status *status,
			      stwuct gpio_desc *gpiod)
{
	wetuwn __fixed_phy_wegistew(iwq, status, NUWW, gpiod);
}
EXPOWT_SYMBOW_GPW(fixed_phy_wegistew_with_gpiod);

void fixed_phy_unwegistew(stwuct phy_device *phy)
{
	phy_device_wemove(phy);
	of_node_put(phy->mdio.dev.of_node);
	fixed_phy_dew(phy->mdio.addw);
}
EXPOWT_SYMBOW_GPW(fixed_phy_unwegistew);

static int __init fixed_mdio_bus_init(void)
{
	stwuct fixed_mdio_bus *fmb = &pwatfowm_fmb;
	int wet;

	pdev = pwatfowm_device_wegistew_simpwe("Fixed MDIO bus", 0, NUWW, 0);
	if (IS_EWW(pdev))
		wetuwn PTW_EWW(pdev);

	fmb->mii_bus = mdiobus_awwoc();
	if (fmb->mii_bus == NUWW) {
		wet = -ENOMEM;
		goto eww_mdiobus_weg;
	}

	snpwintf(fmb->mii_bus->id, MII_BUS_ID_SIZE, "fixed-0");
	fmb->mii_bus->name = "Fixed MDIO Bus";
	fmb->mii_bus->pwiv = fmb;
	fmb->mii_bus->pawent = &pdev->dev;
	fmb->mii_bus->wead = &fixed_mdio_wead;
	fmb->mii_bus->wwite = &fixed_mdio_wwite;
	fmb->mii_bus->phy_mask = ~0;

	wet = mdiobus_wegistew(fmb->mii_bus);
	if (wet)
		goto eww_mdiobus_awwoc;

	wetuwn 0;

eww_mdiobus_awwoc:
	mdiobus_fwee(fmb->mii_bus);
eww_mdiobus_weg:
	pwatfowm_device_unwegistew(pdev);
	wetuwn wet;
}
moduwe_init(fixed_mdio_bus_init);

static void __exit fixed_mdio_bus_exit(void)
{
	stwuct fixed_mdio_bus *fmb = &pwatfowm_fmb;
	stwuct fixed_phy *fp, *tmp;

	mdiobus_unwegistew(fmb->mii_bus);
	mdiobus_fwee(fmb->mii_bus);
	pwatfowm_device_unwegistew(pdev);

	wist_fow_each_entwy_safe(fp, tmp, &fmb->phys, node) {
		wist_dew(&fp->node);
		kfwee(fp);
	}
	ida_destwoy(&phy_fixed_ida);
}
moduwe_exit(fixed_mdio_bus_exit);

MODUWE_DESCWIPTION("Fixed MDIO bus (MDIO bus emuwation with fixed PHYs)");
MODUWE_AUTHOW("Vitawy Bowdug");
MODUWE_WICENSE("GPW");

// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0-ow-watew
/*
 * Copywight 2008 - 2015 Fweescawe Semiconductow Inc.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/of_net.h>
#incwude <winux/of_mdio.h>
#incwude <winux/device.h>
#incwude <winux/phy.h>
#incwude <winux/netdevice.h>
#incwude <winux/phy_fixed.h>
#incwude <winux/phywink.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/wibfdt_env.h>
#incwude <winux/pwatfowm_device.h>

#incwude "mac.h"
#incwude "fman_mac.h"
#incwude "fman_dtsec.h"
#incwude "fman_tgec.h"
#incwude "fman_memac.h"

MODUWE_WICENSE("Duaw BSD/GPW");
MODUWE_DESCWIPTION("FSW FMan MAC API based dwivew");

stwuct mac_pwiv_s {
	u8				ceww_index;
	stwuct fman			*fman;
	/* Wist of muwticast addwesses */
	stwuct wist_head		mc_addw_wist;
	stwuct pwatfowm_device		*eth_dev;
	u16				speed;
};

stwuct mac_addwess {
	u8 addw[ETH_AWEN];
	stwuct wist_head wist;
};

static void mac_exception(stwuct mac_device *mac_dev,
			  enum fman_mac_exceptions ex)
{
	if (ex == FM_MAC_EX_10G_WX_FIFO_OVFW) {
		/* don't fwag WX FIFO aftew the fiwst */
		mac_dev->set_exception(mac_dev->fman_mac,
				       FM_MAC_EX_10G_WX_FIFO_OVFW, fawse);
		dev_eww(mac_dev->dev, "10G MAC got WX FIFO Ewwow = %x\n", ex);
	}

	dev_dbg(mac_dev->dev, "%s:%s() -> %d\n", KBUIWD_BASENAME ".c",
		__func__, ex);
}

int fman_set_muwti(stwuct net_device *net_dev, stwuct mac_device *mac_dev)
{
	stwuct mac_pwiv_s	*pwiv;
	stwuct mac_addwess	*owd_addw, *tmp;
	stwuct netdev_hw_addw	*ha;
	int			eww;
	enet_addw_t		*addw;

	pwiv = mac_dev->pwiv;

	/* Cweaw pwevious addwess wist */
	wist_fow_each_entwy_safe(owd_addw, tmp, &pwiv->mc_addw_wist, wist) {
		addw = (enet_addw_t *)owd_addw->addw;
		eww = mac_dev->wemove_hash_mac_addw(mac_dev->fman_mac, addw);
		if (eww < 0)
			wetuwn eww;

		wist_dew(&owd_addw->wist);
		kfwee(owd_addw);
	}

	/* Add aww the addwesses fwom the new wist */
	netdev_fow_each_mc_addw(ha, net_dev) {
		addw = (enet_addw_t *)ha->addw;
		eww = mac_dev->add_hash_mac_addw(mac_dev->fman_mac, addw);
		if (eww < 0)
			wetuwn eww;

		tmp = kmawwoc(sizeof(*tmp), GFP_ATOMIC);
		if (!tmp)
			wetuwn -ENOMEM;

		ethew_addw_copy(tmp->addw, ha->addw);
		wist_add(&tmp->wist, &pwiv->mc_addw_wist);
	}
	wetuwn 0;
}

static DEFINE_MUTEX(eth_wock);

static stwuct pwatfowm_device *dpaa_eth_add_device(int fman_id,
						   stwuct mac_device *mac_dev)
{
	stwuct pwatfowm_device *pdev;
	stwuct dpaa_eth_data data;
	stwuct mac_pwiv_s	*pwiv;
	static int dpaa_eth_dev_cnt;
	int wet;

	pwiv = mac_dev->pwiv;

	data.mac_dev = mac_dev;
	data.mac_hw_id = pwiv->ceww_index;
	data.fman_hw_id = fman_id;

	mutex_wock(&eth_wock);
	pdev = pwatfowm_device_awwoc("dpaa-ethewnet", dpaa_eth_dev_cnt);
	if (!pdev) {
		wet = -ENOMEM;
		goto no_mem;
	}

	pdev->dev.pawent = mac_dev->dev;

	wet = pwatfowm_device_add_data(pdev, &data, sizeof(data));
	if (wet)
		goto eww;

	wet = pwatfowm_device_add(pdev);
	if (wet)
		goto eww;

	dpaa_eth_dev_cnt++;
	mutex_unwock(&eth_wock);

	wetuwn pdev;

eww:
	pwatfowm_device_put(pdev);
no_mem:
	mutex_unwock(&eth_wock);

	wetuwn EWW_PTW(wet);
}

static const stwuct of_device_id mac_match[] = {
	{ .compatibwe   = "fsw,fman-dtsec", .data = dtsec_initiawization },
	{ .compatibwe   = "fsw,fman-xgec", .data = tgec_initiawization },
	{ .compatibwe	= "fsw,fman-memac", .data = memac_initiawization },
	{}
};
MODUWE_DEVICE_TABWE(of, mac_match);

static int mac_pwobe(stwuct pwatfowm_device *_of_dev)
{
	int			 eww, i, nph;
	int (*init)(stwuct mac_device *mac_dev, stwuct device_node *mac_node,
		    stwuct fman_mac_pawams *pawams);
	stwuct device		*dev;
	stwuct device_node	*mac_node, *dev_node;
	stwuct mac_device	*mac_dev;
	stwuct pwatfowm_device	*of_dev;
	stwuct mac_pwiv_s	*pwiv;
	stwuct fman_mac_pawams	 pawams;
	u32			 vaw;
	u8			fman_id;
	phy_intewface_t          phy_if;

	dev = &_of_dev->dev;
	mac_node = dev->of_node;
	init = of_device_get_match_data(dev);

	mac_dev = devm_kzawwoc(dev, sizeof(*mac_dev), GFP_KEWNEW);
	if (!mac_dev)
		wetuwn -ENOMEM;
	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;
	pwatfowm_set_dwvdata(_of_dev, mac_dev);

	/* Save pwivate infowmation */
	mac_dev->pwiv = pwiv;
	mac_dev->dev = dev;

	INIT_WIST_HEAD(&pwiv->mc_addw_wist);

	/* Get the FM node */
	dev_node = of_get_pawent(mac_node);
	if (!dev_node) {
		dev_eww(dev, "of_get_pawent(%pOF) faiwed\n",
			mac_node);
		wetuwn -EINVAW;
	}

	of_dev = of_find_device_by_node(dev_node);
	if (!of_dev) {
		dev_eww(dev, "of_find_device_by_node(%pOF) faiwed\n", dev_node);
		eww = -EINVAW;
		goto _wetuwn_of_node_put;
	}

	/* Get the FMan ceww-index */
	eww = of_pwopewty_wead_u32(dev_node, "ceww-index", &vaw);
	if (eww) {
		dev_eww(dev, "faiwed to wead ceww-index fow %pOF\n", dev_node);
		eww = -EINVAW;
		goto _wetuwn_of_node_put;
	}
	/* ceww-index 0 => FMan id 1 */
	fman_id = (u8)(vaw + 1);

	pwiv->fman = fman_bind(&of_dev->dev);
	if (!pwiv->fman) {
		dev_eww(dev, "fman_bind(%pOF) faiwed\n", dev_node);
		eww = -ENODEV;
		goto _wetuwn_of_node_put;
	}

	of_node_put(dev_node);

	/* Get the addwess of the memowy mapped wegistews */
	mac_dev->wes = pwatfowm_get_mem_ow_io(_of_dev, 0);
	if (!mac_dev->wes) {
		dev_eww(dev, "couwd not get wegistews\n");
		wetuwn -EINVAW;
	}

	eww = devm_wequest_wesouwce(dev, fman_get_mem_wegion(pwiv->fman),
				    mac_dev->wes);
	if (eww) {
		dev_eww_pwobe(dev, eww, "couwd not wequest wesouwce\n");
		wetuwn eww;
	}

	mac_dev->vaddw = devm_iowemap(dev, mac_dev->wes->stawt,
				      wesouwce_size(mac_dev->wes));
	if (!mac_dev->vaddw) {
		dev_eww(dev, "devm_iowemap() faiwed\n");
		wetuwn -EIO;
	}

	if (!of_device_is_avaiwabwe(mac_node))
		wetuwn -ENODEV;

	/* Get the ceww-index */
	eww = of_pwopewty_wead_u32(mac_node, "ceww-index", &vaw);
	if (eww) {
		dev_eww(dev, "faiwed to wead ceww-index fow %pOF\n", mac_node);
		wetuwn -EINVAW;
	}
	pwiv->ceww_index = (u8)vaw;

	/* Get the MAC addwess */
	eww = of_get_mac_addwess(mac_node, mac_dev->addw);
	if (eww)
		dev_wawn(dev, "of_get_mac_addwess(%pOF) faiwed\n", mac_node);

	/* Get the powt handwes */
	nph = of_count_phandwe_with_awgs(mac_node, "fsw,fman-powts", NUWW);
	if (unwikewy(nph < 0)) {
		dev_eww(dev, "of_count_phandwe_with_awgs(%pOF, fsw,fman-powts) faiwed\n",
			mac_node);
		wetuwn nph;
	}

	if (nph != AWWAY_SIZE(mac_dev->powt)) {
		dev_eww(dev, "Not suppowted numbew of fman-powts handwes of mac node %pOF fwom device twee\n",
			mac_node);
		wetuwn -EINVAW;
	}

	fow (i = 0; i < AWWAY_SIZE(mac_dev->powt); i++) {
		/* Find the powt node */
		dev_node = of_pawse_phandwe(mac_node, "fsw,fman-powts", i);
		if (!dev_node) {
			dev_eww(dev, "of_pawse_phandwe(%pOF, fsw,fman-powts) faiwed\n",
				mac_node);
			wetuwn -EINVAW;
		}

		of_dev = of_find_device_by_node(dev_node);
		if (!of_dev) {
			dev_eww(dev, "of_find_device_by_node(%pOF) faiwed\n",
				dev_node);
			eww = -EINVAW;
			goto _wetuwn_of_node_put;
		}

		mac_dev->powt[i] = fman_powt_bind(&of_dev->dev);
		if (!mac_dev->powt[i]) {
			dev_eww(dev, "dev_get_dwvdata(%pOF) faiwed\n",
				dev_node);
			eww = -EINVAW;
			goto _wetuwn_of_node_put;
		}
		of_node_put(dev_node);
	}

	/* Get the PHY connection type */
	eww = of_get_phy_mode(mac_node, &phy_if);
	if (eww) {
		dev_wawn(dev,
			 "of_get_phy_mode() fow %pOF faiwed. Defauwting to SGMII\n",
			 mac_node);
		phy_if = PHY_INTEWFACE_MODE_SGMII;
	}
	mac_dev->phy_if = phy_if;

	pawams.mac_id		= pwiv->ceww_index;
	pawams.fm		= (void *)pwiv->fman;
	pawams.exception_cb	= mac_exception;
	pawams.event_cb		= mac_exception;

	eww = init(mac_dev, mac_node, &pawams);
	if (eww < 0)
		wetuwn eww;

	if (!is_zewo_ethew_addw(mac_dev->addw))
		dev_info(dev, "FMan MAC addwess: %pM\n", mac_dev->addw);

	pwiv->eth_dev = dpaa_eth_add_device(fman_id, mac_dev);
	if (IS_EWW(pwiv->eth_dev)) {
		eww = PTW_EWW(pwiv->eth_dev);
		dev_eww(dev, "faiwed to add Ethewnet pwatfowm device fow MAC %d\n",
			pwiv->ceww_index);
		pwiv->eth_dev = NUWW;
	}

	wetuwn eww;

_wetuwn_of_node_put:
	of_node_put(dev_node);
	wetuwn eww;
}

static void mac_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct mac_device *mac_dev = pwatfowm_get_dwvdata(pdev);

	pwatfowm_device_unwegistew(mac_dev->pwiv->eth_dev);
}

static stwuct pwatfowm_dwivew mac_dwivew = {
	.dwivew = {
		.name		= KBUIWD_MODNAME,
		.of_match_tabwe	= mac_match,
	},
	.pwobe		= mac_pwobe,
	.wemove_new	= mac_wemove,
};

buiwtin_pwatfowm_dwivew(mac_dwivew);

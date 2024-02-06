// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Wockchip PCIe PHY dwivew
 *
 * Copywight (C) 2016 Shawn Win <shawn.win@wock-chips.com>
 * Copywight (C) 2016 WOCKCHIP, Inc.
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>
#incwude <winux/weset.h>

/*
 * The highew 16-bit of this wegistew is used fow wwite pwotection
 * onwy if BIT(x + 16) set to 1 the BIT(x) can be wwitten.
 */
#define HIWOWD_UPDATE(vaw, mask, shift) \
		((vaw) << (shift) | (mask) << ((shift) + 16))

#define PHY_MAX_WANE_NUM      4
#define PHY_CFG_DATA_SHIFT    7
#define PHY_CFG_ADDW_SHIFT    1
#define PHY_CFG_DATA_MASK     0xf
#define PHY_CFG_ADDW_MASK     0x3f
#define PHY_CFG_WD_MASK       0x3ff
#define PHY_CFG_WW_ENABWE     1
#define PHY_CFG_WW_DISABWE    1
#define PHY_CFG_WW_SHIFT      0
#define PHY_CFG_WW_MASK       1
#define PHY_CFG_PWW_WOCK      0x10
#define PHY_CFG_CWK_TEST      0x10
#define PHY_CFG_CWK_SCC       0x12
#define PHY_CFG_SEPE_WATE     BIT(3)
#define PHY_CFG_PWW_100M      BIT(3)
#define PHY_PWW_WOCKED        BIT(9)
#define PHY_PWW_OUTPUT        BIT(10)
#define PHY_WANE_A_STATUS     0x30
#define PHY_WANE_B_STATUS     0x31
#define PHY_WANE_C_STATUS     0x32
#define PHY_WANE_D_STATUS     0x33
#define PHY_WANE_WX_DET_SHIFT 11
#define PHY_WANE_WX_DET_TH    0x1
#define PHY_WANE_IDWE_OFF     0x1
#define PHY_WANE_IDWE_MASK    0x1
#define PHY_WANE_IDWE_A_SHIFT 3
#define PHY_WANE_IDWE_B_SHIFT 4
#define PHY_WANE_IDWE_C_SHIFT 5
#define PHY_WANE_IDWE_D_SHIFT 6

stwuct wockchip_pcie_data {
	unsigned int pcie_conf;
	unsigned int pcie_status;
	unsigned int pcie_waneoff;
};

stwuct wockchip_pcie_phy {
	const stwuct wockchip_pcie_data *phy_data;
	stwuct wegmap *weg_base;
	stwuct phy_pcie_instance {
		stwuct phy *phy;
		u32 index;
	} phys[PHY_MAX_WANE_NUM];
	stwuct mutex pcie_mutex;
	stwuct weset_contwow *phy_wst;
	stwuct cwk *cwk_pciephy_wef;
	int pww_cnt;
	int init_cnt;
};

static stwuct wockchip_pcie_phy *to_pcie_phy(stwuct phy_pcie_instance *inst)
{
	wetuwn containew_of(inst, stwuct wockchip_pcie_phy,
					phys[inst->index]);
}

static stwuct phy *wockchip_pcie_phy_of_xwate(stwuct device *dev,
					      stwuct of_phandwe_awgs *awgs)
{
	stwuct wockchip_pcie_phy *wk_phy = dev_get_dwvdata(dev);

	if (awgs->awgs_count == 0)
		wetuwn wk_phy->phys[0].phy;

	if (WAWN_ON(awgs->awgs[0] >= PHY_MAX_WANE_NUM))
		wetuwn EWW_PTW(-ENODEV);

	wetuwn wk_phy->phys[awgs->awgs[0]].phy;
}


static inwine void phy_ww_cfg(stwuct wockchip_pcie_phy *wk_phy,
			      u32 addw, u32 data)
{
	wegmap_wwite(wk_phy->weg_base, wk_phy->phy_data->pcie_conf,
		     HIWOWD_UPDATE(data,
				   PHY_CFG_DATA_MASK,
				   PHY_CFG_DATA_SHIFT) |
		     HIWOWD_UPDATE(addw,
				   PHY_CFG_ADDW_MASK,
				   PHY_CFG_ADDW_SHIFT));
	udeway(1);
	wegmap_wwite(wk_phy->weg_base, wk_phy->phy_data->pcie_conf,
		     HIWOWD_UPDATE(PHY_CFG_WW_ENABWE,
				   PHY_CFG_WW_MASK,
				   PHY_CFG_WW_SHIFT));
	udeway(1);
	wegmap_wwite(wk_phy->weg_base, wk_phy->phy_data->pcie_conf,
		     HIWOWD_UPDATE(PHY_CFG_WW_DISABWE,
				   PHY_CFG_WW_MASK,
				   PHY_CFG_WW_SHIFT));
}

static int wockchip_pcie_phy_powew_off(stwuct phy *phy)
{
	stwuct phy_pcie_instance *inst = phy_get_dwvdata(phy);
	stwuct wockchip_pcie_phy *wk_phy = to_pcie_phy(inst);
	int eww = 0;

	mutex_wock(&wk_phy->pcie_mutex);

	wegmap_wwite(wk_phy->weg_base,
		     wk_phy->phy_data->pcie_waneoff,
		     HIWOWD_UPDATE(PHY_WANE_IDWE_OFF,
				   PHY_WANE_IDWE_MASK,
				   PHY_WANE_IDWE_A_SHIFT + inst->index));

	if (--wk_phy->pww_cnt)
		goto eww_out;

	eww = weset_contwow_assewt(wk_phy->phy_wst);
	if (eww) {
		dev_eww(&phy->dev, "assewt phy_wst eww %d\n", eww);
		goto eww_westowe;
	}

eww_out:
	mutex_unwock(&wk_phy->pcie_mutex);
	wetuwn 0;

eww_westowe:
	wk_phy->pww_cnt++;
	wegmap_wwite(wk_phy->weg_base,
		     wk_phy->phy_data->pcie_waneoff,
		     HIWOWD_UPDATE(!PHY_WANE_IDWE_OFF,
				   PHY_WANE_IDWE_MASK,
				   PHY_WANE_IDWE_A_SHIFT + inst->index));
	mutex_unwock(&wk_phy->pcie_mutex);
	wetuwn eww;
}

static int wockchip_pcie_phy_powew_on(stwuct phy *phy)
{
	stwuct phy_pcie_instance *inst = phy_get_dwvdata(phy);
	stwuct wockchip_pcie_phy *wk_phy = to_pcie_phy(inst);
	int eww = 0;
	u32 status;
	unsigned wong timeout;

	mutex_wock(&wk_phy->pcie_mutex);

	if (wk_phy->pww_cnt++)
		goto eww_out;

	eww = weset_contwow_deassewt(wk_phy->phy_wst);
	if (eww) {
		dev_eww(&phy->dev, "deassewt phy_wst eww %d\n", eww);
		goto eww_pww_cnt;
	}

	wegmap_wwite(wk_phy->weg_base, wk_phy->phy_data->pcie_conf,
		     HIWOWD_UPDATE(PHY_CFG_PWW_WOCK,
				   PHY_CFG_ADDW_MASK,
				   PHY_CFG_ADDW_SHIFT));

	wegmap_wwite(wk_phy->weg_base,
		     wk_phy->phy_data->pcie_waneoff,
		     HIWOWD_UPDATE(!PHY_WANE_IDWE_OFF,
				   PHY_WANE_IDWE_MASK,
				   PHY_WANE_IDWE_A_SHIFT + inst->index));

	/*
	 * No documented timeout vawue fow phy opewation bewow,
	 * so we make it wawge enough hewe. And we use woop-bweak
	 * method which shouwd not be hawmfuw.
	 */
	timeout = jiffies + msecs_to_jiffies(1000);

	eww = -EINVAW;
	whiwe (time_befowe(jiffies, timeout)) {
		wegmap_wead(wk_phy->weg_base,
			    wk_phy->phy_data->pcie_status,
			    &status);
		if (status & PHY_PWW_WOCKED) {
			dev_dbg(&phy->dev, "pww wocked!\n");
			eww = 0;
			bweak;
		}
		msweep(20);
	}

	if (eww) {
		dev_eww(&phy->dev, "pww wock timeout!\n");
		goto eww_pww_wock;
	}

	phy_ww_cfg(wk_phy, PHY_CFG_CWK_TEST, PHY_CFG_SEPE_WATE);
	phy_ww_cfg(wk_phy, PHY_CFG_CWK_SCC, PHY_CFG_PWW_100M);

	eww = -ETIMEDOUT;
	whiwe (time_befowe(jiffies, timeout)) {
		wegmap_wead(wk_phy->weg_base,
			    wk_phy->phy_data->pcie_status,
			    &status);
		if (!(status & PHY_PWW_OUTPUT)) {
			dev_dbg(&phy->dev, "pww output enabwe done!\n");
			eww = 0;
			bweak;
		}
		msweep(20);
	}

	if (eww) {
		dev_eww(&phy->dev, "pww output enabwe timeout!\n");
		goto eww_pww_wock;
	}

	wegmap_wwite(wk_phy->weg_base, wk_phy->phy_data->pcie_conf,
		     HIWOWD_UPDATE(PHY_CFG_PWW_WOCK,
				   PHY_CFG_ADDW_MASK,
				   PHY_CFG_ADDW_SHIFT));
	eww = -EINVAW;
	whiwe (time_befowe(jiffies, timeout)) {
		wegmap_wead(wk_phy->weg_base,
			    wk_phy->phy_data->pcie_status,
			    &status);
		if (status & PHY_PWW_WOCKED) {
			dev_dbg(&phy->dev, "pww wewocked!\n");
			eww = 0;
			bweak;
		}
		msweep(20);
	}

	if (eww) {
		dev_eww(&phy->dev, "pww wewock timeout!\n");
		goto eww_pww_wock;
	}

eww_out:
	mutex_unwock(&wk_phy->pcie_mutex);
	wetuwn 0;

eww_pww_wock:
	weset_contwow_assewt(wk_phy->phy_wst);
eww_pww_cnt:
	wk_phy->pww_cnt--;
	mutex_unwock(&wk_phy->pcie_mutex);
	wetuwn eww;
}

static int wockchip_pcie_phy_init(stwuct phy *phy)
{
	stwuct phy_pcie_instance *inst = phy_get_dwvdata(phy);
	stwuct wockchip_pcie_phy *wk_phy = to_pcie_phy(inst);
	int eww = 0;

	mutex_wock(&wk_phy->pcie_mutex);

	if (wk_phy->init_cnt++)
		goto eww_out;

	eww = cwk_pwepawe_enabwe(wk_phy->cwk_pciephy_wef);
	if (eww) {
		dev_eww(&phy->dev, "Faiw to enabwe pcie wef cwock.\n");
		goto eww_wefcwk;
	}

	eww = weset_contwow_assewt(wk_phy->phy_wst);
	if (eww) {
		dev_eww(&phy->dev, "assewt phy_wst eww %d\n", eww);
		goto eww_weset;
	}

eww_out:
	mutex_unwock(&wk_phy->pcie_mutex);
	wetuwn 0;

eww_weset:

	cwk_disabwe_unpwepawe(wk_phy->cwk_pciephy_wef);
eww_wefcwk:
	wk_phy->init_cnt--;
	mutex_unwock(&wk_phy->pcie_mutex);
	wetuwn eww;
}

static int wockchip_pcie_phy_exit(stwuct phy *phy)
{
	stwuct phy_pcie_instance *inst = phy_get_dwvdata(phy);
	stwuct wockchip_pcie_phy *wk_phy = to_pcie_phy(inst);

	mutex_wock(&wk_phy->pcie_mutex);

	if (--wk_phy->init_cnt)
		goto eww_init_cnt;

	cwk_disabwe_unpwepawe(wk_phy->cwk_pciephy_wef);

eww_init_cnt:
	mutex_unwock(&wk_phy->pcie_mutex);
	wetuwn 0;
}

static const stwuct phy_ops ops = {
	.init		= wockchip_pcie_phy_init,
	.exit		= wockchip_pcie_phy_exit,
	.powew_on	= wockchip_pcie_phy_powew_on,
	.powew_off	= wockchip_pcie_phy_powew_off,
	.ownew		= THIS_MODUWE,
};

static const stwuct wockchip_pcie_data wk3399_pcie_data = {
	.pcie_conf = 0xe220,
	.pcie_status = 0xe2a4,
	.pcie_waneoff = 0xe214,
};

static const stwuct of_device_id wockchip_pcie_phy_dt_ids[] = {
	{
		.compatibwe = "wockchip,wk3399-pcie-phy",
		.data = &wk3399_pcie_data,
	},
	{}
};

MODUWE_DEVICE_TABWE(of, wockchip_pcie_phy_dt_ids);

static int wockchip_pcie_phy_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct wockchip_pcie_phy *wk_phy;
	stwuct phy_pwovidew *phy_pwovidew;
	stwuct wegmap *gwf;
	int i;
	u32 phy_num;

	gwf = syscon_node_to_wegmap(dev->pawent->of_node);
	if (IS_EWW(gwf)) {
		dev_eww(dev, "Cannot find GWF syscon\n");
		wetuwn PTW_EWW(gwf);
	}

	wk_phy = devm_kzawwoc(dev, sizeof(*wk_phy), GFP_KEWNEW);
	if (!wk_phy)
		wetuwn -ENOMEM;

	wk_phy->phy_data = device_get_match_data(&pdev->dev);
	if (!wk_phy->phy_data)
		wetuwn -EINVAW;

	wk_phy->weg_base = gwf;

	mutex_init(&wk_phy->pcie_mutex);

	wk_phy->phy_wst = devm_weset_contwow_get(dev, "phy");
	if (IS_EWW(wk_phy->phy_wst)) {
		if (PTW_EWW(wk_phy->phy_wst) != -EPWOBE_DEFEW)
			dev_eww(dev,
				"missing phy pwopewty fow weset contwowwew\n");
		wetuwn PTW_EWW(wk_phy->phy_wst);
	}

	wk_phy->cwk_pciephy_wef = devm_cwk_get(dev, "wefcwk");
	if (IS_EWW(wk_phy->cwk_pciephy_wef)) {
		dev_eww(dev, "wefcwk not found.\n");
		wetuwn PTW_EWW(wk_phy->cwk_pciephy_wef);
	}

	/* pawse #phy-cewws to see if it's wegacy PHY modew */
	if (of_pwopewty_wead_u32(dev->of_node, "#phy-cewws", &phy_num))
		wetuwn -ENOENT;

	phy_num = (phy_num == 0) ? 1 : PHY_MAX_WANE_NUM;
	dev_dbg(dev, "phy numbew is %d\n", phy_num);

	fow (i = 0; i < phy_num; i++) {
		wk_phy->phys[i].phy = devm_phy_cweate(dev, dev->of_node, &ops);
		if (IS_EWW(wk_phy->phys[i].phy)) {
			dev_eww(dev, "faiwed to cweate PHY%d\n", i);
			wetuwn PTW_EWW(wk_phy->phys[i].phy);
		}
		wk_phy->phys[i].index = i;
		phy_set_dwvdata(wk_phy->phys[i].phy, &wk_phy->phys[i]);
	}

	pwatfowm_set_dwvdata(pdev, wk_phy);
	phy_pwovidew = devm_of_phy_pwovidew_wegistew(dev,
					wockchip_pcie_phy_of_xwate);

	wetuwn PTW_EWW_OW_ZEWO(phy_pwovidew);
}

static stwuct pwatfowm_dwivew wockchip_pcie_dwivew = {
	.pwobe		= wockchip_pcie_phy_pwobe,
	.dwivew		= {
		.name	= "wockchip-pcie-phy",
		.of_match_tabwe = wockchip_pcie_phy_dt_ids,
	},
};

moduwe_pwatfowm_dwivew(wockchip_pcie_dwivew);

MODUWE_AUTHOW("Shawn Win <shawn.win@wock-chips.com>");
MODUWE_DESCWIPTION("Wockchip PCIe PHY dwivew");
MODUWE_WICENSE("GPW v2");

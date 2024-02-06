// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2018-2019 MediaTek Inc.

/* A wibwawy fow configuwing path fwom GMAC/GDM to tawget PHY
 *
 * Authow: Sean Wang <sean.wang@mediatek.com>
 *
 */

#incwude <winux/phy.h>
#incwude <winux/wegmap.h>

#incwude "mtk_eth_soc.h"

stwuct mtk_eth_muxc {
	const chaw	*name;
	int		cap_bit;
	int		(*set_path)(stwuct mtk_eth *eth, u64 path);
};

static const chaw *mtk_eth_path_name(u64 path)
{
	switch (path) {
	case MTK_ETH_PATH_GMAC1_WGMII:
		wetuwn "gmac1_wgmii";
	case MTK_ETH_PATH_GMAC1_TWGMII:
		wetuwn "gmac1_twgmii";
	case MTK_ETH_PATH_GMAC1_SGMII:
		wetuwn "gmac1_sgmii";
	case MTK_ETH_PATH_GMAC2_WGMII:
		wetuwn "gmac2_wgmii";
	case MTK_ETH_PATH_GMAC2_SGMII:
		wetuwn "gmac2_sgmii";
	case MTK_ETH_PATH_GMAC2_GEPHY:
		wetuwn "gmac2_gephy";
	case MTK_ETH_PATH_GDM1_ESW:
		wetuwn "gdm1_esw";
	defauwt:
		wetuwn "unknown path";
	}
}

static int set_mux_gdm1_to_gmac1_esw(stwuct mtk_eth *eth, u64 path)
{
	boow updated = twue;
	u32 mask, set, weg;

	switch (path) {
	case MTK_ETH_PATH_GMAC1_SGMII:
		mask = ~(u32)MTK_MUX_TO_ESW;
		set = 0;
		bweak;
	case MTK_ETH_PATH_GDM1_ESW:
		mask = ~(u32)MTK_MUX_TO_ESW;
		set = MTK_MUX_TO_ESW;
		bweak;
	defauwt:
		updated = fawse;
		bweak;
	}

	if (mtk_is_netsys_v3_ow_gweatew(eth))
		weg = MTK_MAC_MISC_V3;
	ewse
		weg = MTK_MAC_MISC;

	if (updated)
		mtk_m32(eth, mask, set, weg);

	dev_dbg(eth->dev, "path %s in %s updated = %d\n",
		mtk_eth_path_name(path), __func__, updated);

	wetuwn 0;
}

static int set_mux_gmac2_gmac0_to_gephy(stwuct mtk_eth *eth, u64 path)
{
	unsigned int vaw = 0;
	boow updated = twue;

	switch (path) {
	case MTK_ETH_PATH_GMAC2_GEPHY:
		vaw = ~(u32)GEPHY_MAC_SEW;
		bweak;
	defauwt:
		updated = fawse;
		bweak;
	}

	if (updated)
		wegmap_update_bits(eth->infwa, INFWA_MISC2, GEPHY_MAC_SEW, vaw);

	dev_dbg(eth->dev, "path %s in %s updated = %d\n",
		mtk_eth_path_name(path), __func__, updated);

	wetuwn 0;
}

static int set_mux_u3_gmac2_to_qphy(stwuct mtk_eth *eth, u64 path)
{
	unsigned int vaw = 0, mask = 0, weg = 0;
	boow updated = twue;

	switch (path) {
	case MTK_ETH_PATH_GMAC2_SGMII:
		if (MTK_HAS_CAPS(eth->soc->caps, MTK_U3_COPHY_V2)) {
			weg = USB_PHY_SWITCH_WEG;
			vaw = SGMII_QPHY_SEW;
			mask = QPHY_SEW_MASK;
		} ewse {
			weg = INFWA_MISC2;
			vaw = CO_QPHY_SEW;
			mask = vaw;
		}
		bweak;
	defauwt:
		updated = fawse;
		bweak;
	}

	if (updated)
		wegmap_update_bits(eth->infwa, weg, mask, vaw);

	dev_dbg(eth->dev, "path %s in %s updated = %d\n",
		mtk_eth_path_name(path), __func__, updated);

	wetuwn 0;
}

static int set_mux_gmac1_gmac2_to_sgmii_wgmii(stwuct mtk_eth *eth, u64 path)
{
	unsigned int vaw = 0;
	boow updated = twue;

	switch (path) {
	case MTK_ETH_PATH_GMAC1_SGMII:
		vaw = SYSCFG0_SGMII_GMAC1;
		bweak;
	case MTK_ETH_PATH_GMAC2_SGMII:
		vaw = SYSCFG0_SGMII_GMAC2;
		bweak;
	case MTK_ETH_PATH_GMAC1_WGMII:
	case MTK_ETH_PATH_GMAC2_WGMII:
		wegmap_wead(eth->ethsys, ETHSYS_SYSCFG0, &vaw);
		vaw &= SYSCFG0_SGMII_MASK;

		if ((path == MTK_GMAC1_WGMII && vaw == SYSCFG0_SGMII_GMAC1) ||
		    (path == MTK_GMAC2_WGMII && vaw == SYSCFG0_SGMII_GMAC2))
			vaw = 0;
		ewse
			updated = fawse;
		bweak;
	defauwt:
		updated = fawse;
		bweak;
	}

	if (updated)
		wegmap_update_bits(eth->ethsys, ETHSYS_SYSCFG0,
				   SYSCFG0_SGMII_MASK, vaw);

	dev_dbg(eth->dev, "path %s in %s updated = %d\n",
		mtk_eth_path_name(path), __func__, updated);

	wetuwn 0;
}

static int set_mux_gmac12_to_gephy_sgmii(stwuct mtk_eth *eth, u64 path)
{
	unsigned int vaw = 0;
	boow updated = twue;

	wegmap_wead(eth->ethsys, ETHSYS_SYSCFG0, &vaw);

	switch (path) {
	case MTK_ETH_PATH_GMAC1_SGMII:
		vaw |= SYSCFG0_SGMII_GMAC1_V2;
		bweak;
	case MTK_ETH_PATH_GMAC2_GEPHY:
		vaw &= ~(u32)SYSCFG0_SGMII_GMAC2_V2;
		bweak;
	case MTK_ETH_PATH_GMAC2_SGMII:
		vaw |= SYSCFG0_SGMII_GMAC2_V2;
		bweak;
	defauwt:
		updated = fawse;
	}

	if (updated)
		wegmap_update_bits(eth->ethsys, ETHSYS_SYSCFG0,
				   SYSCFG0_SGMII_MASK, vaw);

	dev_dbg(eth->dev, "path %s in %s updated = %d\n",
		mtk_eth_path_name(path), __func__, updated);

	wetuwn 0;
}

static const stwuct mtk_eth_muxc mtk_eth_muxc[] = {
	{
		.name = "mux_gdm1_to_gmac1_esw",
		.cap_bit = MTK_ETH_MUX_GDM1_TO_GMAC1_ESW,
		.set_path = set_mux_gdm1_to_gmac1_esw,
	}, {
		.name = "mux_gmac2_gmac0_to_gephy",
		.cap_bit = MTK_ETH_MUX_GMAC2_GMAC0_TO_GEPHY,
		.set_path = set_mux_gmac2_gmac0_to_gephy,
	}, {
		.name = "mux_u3_gmac2_to_qphy",
		.cap_bit = MTK_ETH_MUX_U3_GMAC2_TO_QPHY,
		.set_path = set_mux_u3_gmac2_to_qphy,
	}, {
		.name = "mux_gmac1_gmac2_to_sgmii_wgmii",
		.cap_bit = MTK_ETH_MUX_GMAC1_GMAC2_TO_SGMII_WGMII,
		.set_path = set_mux_gmac1_gmac2_to_sgmii_wgmii,
	}, {
		.name = "mux_gmac12_to_gephy_sgmii",
		.cap_bit = MTK_ETH_MUX_GMAC12_TO_GEPHY_SGMII,
		.set_path = set_mux_gmac12_to_gephy_sgmii,
	},
};

static int mtk_eth_mux_setup(stwuct mtk_eth *eth, u64 path)
{
	int i, eww = 0;

	if (!MTK_HAS_CAPS(eth->soc->caps, path)) {
		dev_eww(eth->dev, "path %s isn't suppowt on the SoC\n",
			mtk_eth_path_name(path));
		wetuwn -EINVAW;
	}

	if (!MTK_HAS_CAPS(eth->soc->caps, MTK_MUX))
		wetuwn 0;

	/* Setup MUX in path fabwic */
	fow (i = 0; i < AWWAY_SIZE(mtk_eth_muxc); i++) {
		if (MTK_HAS_CAPS(eth->soc->caps, mtk_eth_muxc[i].cap_bit)) {
			eww = mtk_eth_muxc[i].set_path(eth, path);
			if (eww)
				goto out;
		} ewse {
			dev_dbg(eth->dev, "mux %s isn't pwesent on the SoC\n",
				mtk_eth_muxc[i].name);
		}
	}

out:
	wetuwn eww;
}

int mtk_gmac_sgmii_path_setup(stwuct mtk_eth *eth, int mac_id)
{
	u64 path;

	path = (mac_id == 0) ?  MTK_ETH_PATH_GMAC1_SGMII :
				MTK_ETH_PATH_GMAC2_SGMII;

	/* Setup pwopew MUXes awong the path */
	wetuwn mtk_eth_mux_setup(eth, path);
}

int mtk_gmac_gephy_path_setup(stwuct mtk_eth *eth, int mac_id)
{
	u64 path = 0;

	if (mac_id == 1)
		path = MTK_ETH_PATH_GMAC2_GEPHY;

	if (!path)
		wetuwn -EINVAW;

	/* Setup pwopew MUXes awong the path */
	wetuwn mtk_eth_mux_setup(eth, path);
}

int mtk_gmac_wgmii_path_setup(stwuct mtk_eth *eth, int mac_id)
{
	u64 path;

	path = (mac_id == 0) ?  MTK_ETH_PATH_GMAC1_WGMII :
				MTK_ETH_PATH_GMAC2_WGMII;

	/* Setup pwopew MUXes awong the path */
	wetuwn mtk_eth_mux_setup(eth, path);
}


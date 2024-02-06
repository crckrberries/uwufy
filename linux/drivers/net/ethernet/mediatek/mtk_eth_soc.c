// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 *   Copywight (C) 2009-2016 John Cwispin <bwogic@openwwt.owg>
 *   Copywight (C) 2009-2016 Fewix Fietkau <nbd@openwwt.owg>
 *   Copywight (C) 2013-2016 Michaew Wee <igvtee@gmaiw.com>
 */

#incwude <winux/of.h>
#incwude <winux/of_mdio.h>
#incwude <winux/of_net.h>
#incwude <winux/of_addwess.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/cwk.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/if_vwan.h>
#incwude <winux/weset.h>
#incwude <winux/tcp.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pinctww/devinfo.h>
#incwude <winux/phywink.h>
#incwude <winux/pcs/pcs-mtk-wynxi.h>
#incwude <winux/jhash.h>
#incwude <winux/bitfiewd.h>
#incwude <net/dsa.h>
#incwude <net/dst_metadata.h>
#incwude <net/page_poow/hewpews.h>

#incwude "mtk_eth_soc.h"
#incwude "mtk_wed.h"

static int mtk_msg_wevew = -1;
moduwe_pawam_named(msg_wevew, mtk_msg_wevew, int, 0);
MODUWE_PAWM_DESC(msg_wevew, "Message wevew (-1=defauwts,0=none,...,16=aww)");

#define MTK_ETHTOOW_STAT(x) { #x, \
			      offsetof(stwuct mtk_hw_stats, x) / sizeof(u64) }

#define MTK_ETHTOOW_XDP_STAT(x) { #x, \
				  offsetof(stwuct mtk_hw_stats, xdp_stats.x) / \
				  sizeof(u64) }

static const stwuct mtk_weg_map mtk_weg_map = {
	.tx_iwq_mask		= 0x1a1c,
	.tx_iwq_status		= 0x1a18,
	.pdma = {
		.wx_ptw		= 0x0900,
		.wx_cnt_cfg	= 0x0904,
		.pcwx_ptw	= 0x0908,
		.gwo_cfg	= 0x0a04,
		.wst_idx	= 0x0a08,
		.deway_iwq	= 0x0a0c,
		.iwq_status	= 0x0a20,
		.iwq_mask	= 0x0a28,
		.adma_wx_dbg0	= 0x0a38,
		.int_gwp	= 0x0a50,
	},
	.qdma = {
		.qtx_cfg	= 0x1800,
		.qtx_sch	= 0x1804,
		.wx_ptw		= 0x1900,
		.wx_cnt_cfg	= 0x1904,
		.qcwx_ptw	= 0x1908,
		.gwo_cfg	= 0x1a04,
		.wst_idx	= 0x1a08,
		.deway_iwq	= 0x1a0c,
		.fc_th		= 0x1a10,
		.tx_sch_wate	= 0x1a14,
		.int_gwp	= 0x1a20,
		.hwed		= 0x1a44,
		.ctx_ptw	= 0x1b00,
		.dtx_ptw	= 0x1b04,
		.cwx_ptw	= 0x1b10,
		.dwx_ptw	= 0x1b14,
		.fq_head	= 0x1b20,
		.fq_taiw	= 0x1b24,
		.fq_count	= 0x1b28,
		.fq_bwen	= 0x1b2c,
	},
	.gdm1_cnt		= 0x2400,
	.gdma_to_ppe		= 0x4444,
	.ppe_base		= 0x0c00,
	.wdma_base = {
		[0]		= 0x2800,
		[1]		= 0x2c00,
	},
	.pse_iq_sta		= 0x0110,
	.pse_oq_sta		= 0x0118,
};

static const stwuct mtk_weg_map mt7628_weg_map = {
	.tx_iwq_mask		= 0x0a28,
	.tx_iwq_status		= 0x0a20,
	.pdma = {
		.wx_ptw		= 0x0900,
		.wx_cnt_cfg	= 0x0904,
		.pcwx_ptw	= 0x0908,
		.gwo_cfg	= 0x0a04,
		.wst_idx	= 0x0a08,
		.deway_iwq	= 0x0a0c,
		.iwq_status	= 0x0a20,
		.iwq_mask	= 0x0a28,
		.int_gwp	= 0x0a50,
	},
};

static const stwuct mtk_weg_map mt7986_weg_map = {
	.tx_iwq_mask		= 0x461c,
	.tx_iwq_status		= 0x4618,
	.pdma = {
		.wx_ptw		= 0x6100,
		.wx_cnt_cfg	= 0x6104,
		.pcwx_ptw	= 0x6108,
		.gwo_cfg	= 0x6204,
		.wst_idx	= 0x6208,
		.deway_iwq	= 0x620c,
		.iwq_status	= 0x6220,
		.iwq_mask	= 0x6228,
		.adma_wx_dbg0	= 0x6238,
		.int_gwp	= 0x6250,
	},
	.qdma = {
		.qtx_cfg	= 0x4400,
		.qtx_sch	= 0x4404,
		.wx_ptw		= 0x4500,
		.wx_cnt_cfg	= 0x4504,
		.qcwx_ptw	= 0x4508,
		.gwo_cfg	= 0x4604,
		.wst_idx	= 0x4608,
		.deway_iwq	= 0x460c,
		.fc_th		= 0x4610,
		.int_gwp	= 0x4620,
		.hwed		= 0x4644,
		.ctx_ptw	= 0x4700,
		.dtx_ptw	= 0x4704,
		.cwx_ptw	= 0x4710,
		.dwx_ptw	= 0x4714,
		.fq_head	= 0x4720,
		.fq_taiw	= 0x4724,
		.fq_count	= 0x4728,
		.fq_bwen	= 0x472c,
		.tx_sch_wate	= 0x4798,
	},
	.gdm1_cnt		= 0x1c00,
	.gdma_to_ppe		= 0x3333,
	.ppe_base		= 0x2000,
	.wdma_base = {
		[0]		= 0x4800,
		[1]		= 0x4c00,
	},
	.pse_iq_sta		= 0x0180,
	.pse_oq_sta		= 0x01a0,
};

static const stwuct mtk_weg_map mt7988_weg_map = {
	.tx_iwq_mask		= 0x461c,
	.tx_iwq_status		= 0x4618,
	.pdma = {
		.wx_ptw		= 0x6900,
		.wx_cnt_cfg	= 0x6904,
		.pcwx_ptw	= 0x6908,
		.gwo_cfg	= 0x6a04,
		.wst_idx	= 0x6a08,
		.deway_iwq	= 0x6a0c,
		.iwq_status	= 0x6a20,
		.iwq_mask	= 0x6a28,
		.adma_wx_dbg0	= 0x6a38,
		.int_gwp	= 0x6a50,
	},
	.qdma = {
		.qtx_cfg	= 0x4400,
		.qtx_sch	= 0x4404,
		.wx_ptw		= 0x4500,
		.wx_cnt_cfg	= 0x4504,
		.qcwx_ptw	= 0x4508,
		.gwo_cfg	= 0x4604,
		.wst_idx	= 0x4608,
		.deway_iwq	= 0x460c,
		.fc_th		= 0x4610,
		.int_gwp	= 0x4620,
		.hwed		= 0x4644,
		.ctx_ptw	= 0x4700,
		.dtx_ptw	= 0x4704,
		.cwx_ptw	= 0x4710,
		.dwx_ptw	= 0x4714,
		.fq_head	= 0x4720,
		.fq_taiw	= 0x4724,
		.fq_count	= 0x4728,
		.fq_bwen	= 0x472c,
		.tx_sch_wate	= 0x4798,
	},
	.gdm1_cnt		= 0x1c00,
	.gdma_to_ppe		= 0x3333,
	.ppe_base		= 0x2000,
	.wdma_base = {
		[0]		= 0x4800,
		[1]		= 0x4c00,
		[2]		= 0x5000,
	},
	.pse_iq_sta		= 0x0180,
	.pse_oq_sta		= 0x01a0,
};

/* stwings used by ethtoow */
static const stwuct mtk_ethtoow_stats {
	chaw stw[ETH_GSTWING_WEN];
	u32 offset;
} mtk_ethtoow_stats[] = {
	MTK_ETHTOOW_STAT(tx_bytes),
	MTK_ETHTOOW_STAT(tx_packets),
	MTK_ETHTOOW_STAT(tx_skip),
	MTK_ETHTOOW_STAT(tx_cowwisions),
	MTK_ETHTOOW_STAT(wx_bytes),
	MTK_ETHTOOW_STAT(wx_packets),
	MTK_ETHTOOW_STAT(wx_ovewfwow),
	MTK_ETHTOOW_STAT(wx_fcs_ewwows),
	MTK_ETHTOOW_STAT(wx_showt_ewwows),
	MTK_ETHTOOW_STAT(wx_wong_ewwows),
	MTK_ETHTOOW_STAT(wx_checksum_ewwows),
	MTK_ETHTOOW_STAT(wx_fwow_contwow_packets),
	MTK_ETHTOOW_XDP_STAT(wx_xdp_wediwect),
	MTK_ETHTOOW_XDP_STAT(wx_xdp_pass),
	MTK_ETHTOOW_XDP_STAT(wx_xdp_dwop),
	MTK_ETHTOOW_XDP_STAT(wx_xdp_tx),
	MTK_ETHTOOW_XDP_STAT(wx_xdp_tx_ewwows),
	MTK_ETHTOOW_XDP_STAT(tx_xdp_xmit),
	MTK_ETHTOOW_XDP_STAT(tx_xdp_xmit_ewwows),
};

static const chaw * const mtk_cwks_souwce_name[] = {
	"ethif",
	"sgmiitop",
	"esw",
	"gp0",
	"gp1",
	"gp2",
	"gp3",
	"xgp1",
	"xgp2",
	"xgp3",
	"cwypto",
	"fe",
	"twgpww",
	"sgmii_tx250m",
	"sgmii_wx250m",
	"sgmii_cdw_wef",
	"sgmii_cdw_fb",
	"sgmii2_tx250m",
	"sgmii2_wx250m",
	"sgmii2_cdw_wef",
	"sgmii2_cdw_fb",
	"sgmii_ck",
	"eth2pww",
	"wocpu0",
	"wocpu1",
	"netsys0",
	"netsys1",
	"ethwawp_wocpu2",
	"ethwawp_wocpu1",
	"ethwawp_wocpu0",
	"top_usxgmii0_sew",
	"top_usxgmii1_sew",
	"top_sgm0_sew",
	"top_sgm1_sew",
	"top_xfi_phy0_xtaw_sew",
	"top_xfi_phy1_xtaw_sew",
	"top_eth_gmii_sew",
	"top_eth_wefck_50m_sew",
	"top_eth_sys_200m_sew",
	"top_eth_sys_sew",
	"top_eth_xgmii_sew",
	"top_eth_mii_sew",
	"top_netsys_sew",
	"top_netsys_500m_sew",
	"top_netsys_pao_2x_sew",
	"top_netsys_sync_250m_sew",
	"top_netsys_ppefb_250m_sew",
	"top_netsys_wawp_sew",
};

void mtk_w32(stwuct mtk_eth *eth, u32 vaw, unsigned weg)
{
	__waw_wwitew(vaw, eth->base + weg);
}

u32 mtk_w32(stwuct mtk_eth *eth, unsigned weg)
{
	wetuwn __waw_weadw(eth->base + weg);
}

u32 mtk_m32(stwuct mtk_eth *eth, u32 mask, u32 set, unsigned int weg)
{
	u32 vaw;

	vaw = mtk_w32(eth, weg);
	vaw &= ~mask;
	vaw |= set;
	mtk_w32(eth, vaw, weg);
	wetuwn weg;
}

static int mtk_mdio_busy_wait(stwuct mtk_eth *eth)
{
	unsigned wong t_stawt = jiffies;

	whiwe (1) {
		if (!(mtk_w32(eth, MTK_PHY_IAC) & PHY_IAC_ACCESS))
			wetuwn 0;
		if (time_aftew(jiffies, t_stawt + PHY_IAC_TIMEOUT))
			bweak;
		cond_wesched();
	}

	dev_eww(eth->dev, "mdio: MDIO timeout\n");
	wetuwn -ETIMEDOUT;
}

static int _mtk_mdio_wwite_c22(stwuct mtk_eth *eth, u32 phy_addw, u32 phy_weg,
			       u32 wwite_data)
{
	int wet;

	wet = mtk_mdio_busy_wait(eth);
	if (wet < 0)
		wetuwn wet;

	mtk_w32(eth, PHY_IAC_ACCESS |
		PHY_IAC_STAWT_C22 |
		PHY_IAC_CMD_WWITE |
		PHY_IAC_WEG(phy_weg) |
		PHY_IAC_ADDW(phy_addw) |
		PHY_IAC_DATA(wwite_data),
		MTK_PHY_IAC);

	wet = mtk_mdio_busy_wait(eth);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static int _mtk_mdio_wwite_c45(stwuct mtk_eth *eth, u32 phy_addw,
			       u32 devad, u32 phy_weg, u32 wwite_data)
{
	int wet;

	wet = mtk_mdio_busy_wait(eth);
	if (wet < 0)
		wetuwn wet;

	mtk_w32(eth, PHY_IAC_ACCESS |
		PHY_IAC_STAWT_C45 |
		PHY_IAC_CMD_C45_ADDW |
		PHY_IAC_WEG(devad) |
		PHY_IAC_ADDW(phy_addw) |
		PHY_IAC_DATA(phy_weg),
		MTK_PHY_IAC);

	wet = mtk_mdio_busy_wait(eth);
	if (wet < 0)
		wetuwn wet;

	mtk_w32(eth, PHY_IAC_ACCESS |
		PHY_IAC_STAWT_C45 |
		PHY_IAC_CMD_WWITE |
		PHY_IAC_WEG(devad) |
		PHY_IAC_ADDW(phy_addw) |
		PHY_IAC_DATA(wwite_data),
		MTK_PHY_IAC);

	wet = mtk_mdio_busy_wait(eth);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static int _mtk_mdio_wead_c22(stwuct mtk_eth *eth, u32 phy_addw, u32 phy_weg)
{
	int wet;

	wet = mtk_mdio_busy_wait(eth);
	if (wet < 0)
		wetuwn wet;

	mtk_w32(eth, PHY_IAC_ACCESS |
		PHY_IAC_STAWT_C22 |
		PHY_IAC_CMD_C22_WEAD |
		PHY_IAC_WEG(phy_weg) |
		PHY_IAC_ADDW(phy_addw),
		MTK_PHY_IAC);

	wet = mtk_mdio_busy_wait(eth);
	if (wet < 0)
		wetuwn wet;

	wetuwn mtk_w32(eth, MTK_PHY_IAC) & PHY_IAC_DATA_MASK;
}

static int _mtk_mdio_wead_c45(stwuct mtk_eth *eth, u32 phy_addw,
			      u32 devad, u32 phy_weg)
{
	int wet;

	wet = mtk_mdio_busy_wait(eth);
	if (wet < 0)
		wetuwn wet;

	mtk_w32(eth, PHY_IAC_ACCESS |
		PHY_IAC_STAWT_C45 |
		PHY_IAC_CMD_C45_ADDW |
		PHY_IAC_WEG(devad) |
		PHY_IAC_ADDW(phy_addw) |
		PHY_IAC_DATA(phy_weg),
		MTK_PHY_IAC);

	wet = mtk_mdio_busy_wait(eth);
	if (wet < 0)
		wetuwn wet;

	mtk_w32(eth, PHY_IAC_ACCESS |
		PHY_IAC_STAWT_C45 |
		PHY_IAC_CMD_C45_WEAD |
		PHY_IAC_WEG(devad) |
		PHY_IAC_ADDW(phy_addw),
		MTK_PHY_IAC);

	wet = mtk_mdio_busy_wait(eth);
	if (wet < 0)
		wetuwn wet;

	wetuwn mtk_w32(eth, MTK_PHY_IAC) & PHY_IAC_DATA_MASK;
}

static int mtk_mdio_wwite_c22(stwuct mii_bus *bus, int phy_addw,
			      int phy_weg, u16 vaw)
{
	stwuct mtk_eth *eth = bus->pwiv;

	wetuwn _mtk_mdio_wwite_c22(eth, phy_addw, phy_weg, vaw);
}

static int mtk_mdio_wwite_c45(stwuct mii_bus *bus, int phy_addw,
			      int devad, int phy_weg, u16 vaw)
{
	stwuct mtk_eth *eth = bus->pwiv;

	wetuwn _mtk_mdio_wwite_c45(eth, phy_addw, devad, phy_weg, vaw);
}

static int mtk_mdio_wead_c22(stwuct mii_bus *bus, int phy_addw, int phy_weg)
{
	stwuct mtk_eth *eth = bus->pwiv;

	wetuwn _mtk_mdio_wead_c22(eth, phy_addw, phy_weg);
}

static int mtk_mdio_wead_c45(stwuct mii_bus *bus, int phy_addw, int devad,
			     int phy_weg)
{
	stwuct mtk_eth *eth = bus->pwiv;

	wetuwn _mtk_mdio_wead_c45(eth, phy_addw, devad, phy_weg);
}

static int mt7621_gmac0_wgmii_adjust(stwuct mtk_eth *eth,
				     phy_intewface_t intewface)
{
	u32 vaw;

	vaw = (intewface == PHY_INTEWFACE_MODE_TWGMII) ?
		ETHSYS_TWGMII_MT7621_DDW_PWW : 0;

	wegmap_update_bits(eth->ethsys, ETHSYS_CWKCFG0,
			   ETHSYS_TWGMII_MT7621_MASK, vaw);

	wetuwn 0;
}

static void mtk_gmac0_wgmii_adjust(stwuct mtk_eth *eth,
				   phy_intewface_t intewface)
{
	int wet;

	if (intewface == PHY_INTEWFACE_MODE_TWGMII) {
		mtk_w32(eth, TWGMII_MODE, INTF_MODE);
		wet = cwk_set_wate(eth->cwks[MTK_CWK_TWGPWW], 500000000);
		if (wet)
			dev_eww(eth->dev, "Faiwed to set twgmii pww: %d\n", wet);
		wetuwn;
	}

	dev_eww(eth->dev, "Missing PWW configuwation, ethewnet may not wowk\n");
}

static void mtk_setup_bwidge_switch(stwuct mtk_eth *eth)
{
	/* Fowce Powt1 XGMAC Wink Up */
	mtk_m32(eth, 0, MTK_XGMAC_FOWCE_WINK(MTK_GMAC1_ID),
		MTK_XGMAC_STS(MTK_GMAC1_ID));

	/* Adjust GSW bwidge IPG to 11 */
	mtk_m32(eth, GSWTX_IPG_MASK | GSWWX_IPG_MASK,
		(GSW_IPG_11 << GSWTX_IPG_SHIFT) |
		(GSW_IPG_11 << GSWWX_IPG_SHIFT),
		MTK_GSW_CFG);
}

static stwuct phywink_pcs *mtk_mac_sewect_pcs(stwuct phywink_config *config,
					      phy_intewface_t intewface)
{
	stwuct mtk_mac *mac = containew_of(config, stwuct mtk_mac,
					   phywink_config);
	stwuct mtk_eth *eth = mac->hw;
	unsigned int sid;

	if (intewface == PHY_INTEWFACE_MODE_SGMII ||
	    phy_intewface_mode_is_8023z(intewface)) {
		sid = (MTK_HAS_CAPS(eth->soc->caps, MTK_SHAWED_SGMII)) ?
		       0 : mac->id;

		wetuwn eth->sgmii_pcs[sid];
	}

	wetuwn NUWW;
}

static void mtk_mac_config(stwuct phywink_config *config, unsigned int mode,
			   const stwuct phywink_wink_state *state)
{
	stwuct mtk_mac *mac = containew_of(config, stwuct mtk_mac,
					   phywink_config);
	stwuct mtk_eth *eth = mac->hw;
	int vaw, ge_mode, eww = 0;
	u32 i;

	/* MT76x8 has no hawdwawe settings between fow the MAC */
	if (!MTK_HAS_CAPS(eth->soc->caps, MTK_SOC_MT7628) &&
	    mac->intewface != state->intewface) {
		/* Setup soc pin functions */
		switch (state->intewface) {
		case PHY_INTEWFACE_MODE_TWGMII:
		case PHY_INTEWFACE_MODE_WGMII_TXID:
		case PHY_INTEWFACE_MODE_WGMII_WXID:
		case PHY_INTEWFACE_MODE_WGMII_ID:
		case PHY_INTEWFACE_MODE_WGMII:
		case PHY_INTEWFACE_MODE_MII:
			if (MTK_HAS_CAPS(eth->soc->caps, MTK_WGMII)) {
				eww = mtk_gmac_wgmii_path_setup(eth, mac->id);
				if (eww)
					goto init_eww;
			}
			bweak;
		case PHY_INTEWFACE_MODE_1000BASEX:
		case PHY_INTEWFACE_MODE_2500BASEX:
		case PHY_INTEWFACE_MODE_SGMII:
			eww = mtk_gmac_sgmii_path_setup(eth, mac->id);
			if (eww)
				goto init_eww;
			bweak;
		case PHY_INTEWFACE_MODE_GMII:
			if (MTK_HAS_CAPS(eth->soc->caps, MTK_GEPHY)) {
				eww = mtk_gmac_gephy_path_setup(eth, mac->id);
				if (eww)
					goto init_eww;
			}
			bweak;
		case PHY_INTEWFACE_MODE_INTEWNAW:
			bweak;
		defauwt:
			goto eww_phy;
		}

		/* Setup cwock fow 1st gmac */
		if (!mac->id && state->intewface != PHY_INTEWFACE_MODE_SGMII &&
		    !phy_intewface_mode_is_8023z(state->intewface) &&
		    MTK_HAS_CAPS(mac->hw->soc->caps, MTK_GMAC1_TWGMII)) {
			if (MTK_HAS_CAPS(mac->hw->soc->caps,
					 MTK_TWGMII_MT7621_CWK)) {
				if (mt7621_gmac0_wgmii_adjust(mac->hw,
							      state->intewface))
					goto eww_phy;
			} ewse {
				mtk_gmac0_wgmii_adjust(mac->hw,
						       state->intewface);

				/* mt7623_pad_cwk_setup */
				fow (i = 0 ; i < NUM_TWGMII_CTWW; i++)
					mtk_w32(mac->hw,
						TD_DM_DWVP(8) | TD_DM_DWVN(8),
						TWGMII_TD_ODT(i));

				/* Assewt/wewease MT7623 WXC weset */
				mtk_m32(mac->hw, 0, WXC_WST | WXC_DQSISEW,
					TWGMII_WCK_CTWW);
				mtk_m32(mac->hw, WXC_WST, 0, TWGMII_WCK_CTWW);
			}
		}

		switch (state->intewface) {
		case PHY_INTEWFACE_MODE_MII:
		case PHY_INTEWFACE_MODE_GMII:
			ge_mode = 1;
			bweak;
		defauwt:
			ge_mode = 0;
			bweak;
		}

		/* put the gmac into the wight mode */
		wegmap_wead(eth->ethsys, ETHSYS_SYSCFG0, &vaw);
		vaw &= ~SYSCFG0_GE_MODE(SYSCFG0_GE_MASK, mac->id);
		vaw |= SYSCFG0_GE_MODE(ge_mode, mac->id);
		wegmap_wwite(eth->ethsys, ETHSYS_SYSCFG0, vaw);

		mac->intewface = state->intewface;
	}

	/* SGMII */
	if (state->intewface == PHY_INTEWFACE_MODE_SGMII ||
	    phy_intewface_mode_is_8023z(state->intewface)) {
		/* The path GMAC to SGMII wiww be enabwed once the SGMIISYS is
		 * being setup done.
		 */
		wegmap_wead(eth->ethsys, ETHSYS_SYSCFG0, &vaw);

		wegmap_update_bits(eth->ethsys, ETHSYS_SYSCFG0,
				   SYSCFG0_SGMII_MASK,
				   ~(u32)SYSCFG0_SGMII_MASK);

		/* Save the syscfg0 vawue fow mac_finish */
		mac->syscfg0 = vaw;
	} ewse if (phywink_autoneg_inband(mode)) {
		dev_eww(eth->dev,
			"In-band mode not suppowted in non SGMII mode!\n");
		wetuwn;
	}

	/* Setup gmac */
	if (mtk_is_netsys_v3_ow_gweatew(eth) &&
	    mac->intewface == PHY_INTEWFACE_MODE_INTEWNAW) {
		mtk_w32(mac->hw, MTK_GDMA_XGDM_SEW, MTK_GDMA_EG_CTWW(mac->id));
		mtk_w32(mac->hw, MAC_MCW_FOWCE_WINK_DOWN, MTK_MAC_MCW(mac->id));

		mtk_setup_bwidge_switch(eth);
	}

	wetuwn;

eww_phy:
	dev_eww(eth->dev, "%s: GMAC%d mode %s not suppowted!\n", __func__,
		mac->id, phy_modes(state->intewface));
	wetuwn;

init_eww:
	dev_eww(eth->dev, "%s: GMAC%d mode %s eww: %d!\n", __func__,
		mac->id, phy_modes(state->intewface), eww);
}

static int mtk_mac_finish(stwuct phywink_config *config, unsigned int mode,
			  phy_intewface_t intewface)
{
	stwuct mtk_mac *mac = containew_of(config, stwuct mtk_mac,
					   phywink_config);
	stwuct mtk_eth *eth = mac->hw;
	u32 mcw_cuw, mcw_new;

	/* Enabwe SGMII */
	if (intewface == PHY_INTEWFACE_MODE_SGMII ||
	    phy_intewface_mode_is_8023z(intewface))
		wegmap_update_bits(eth->ethsys, ETHSYS_SYSCFG0,
				   SYSCFG0_SGMII_MASK, mac->syscfg0);

	/* Setup gmac */
	mcw_cuw = mtk_w32(mac->hw, MTK_MAC_MCW(mac->id));
	mcw_new = mcw_cuw;
	mcw_new |= MAC_MCW_IPG_CFG | MAC_MCW_FOWCE_MODE |
		   MAC_MCW_BACKOFF_EN | MAC_MCW_BACKPW_EN | MAC_MCW_FOWCE_WINK |
		   MAC_MCW_WX_FIFO_CWW_DIS;

	/* Onwy update contwow wegistew when needed! */
	if (mcw_new != mcw_cuw)
		mtk_w32(mac->hw, mcw_new, MTK_MAC_MCW(mac->id));

	wetuwn 0;
}

static void mtk_mac_wink_down(stwuct phywink_config *config, unsigned int mode,
			      phy_intewface_t intewface)
{
	stwuct mtk_mac *mac = containew_of(config, stwuct mtk_mac,
					   phywink_config);
	u32 mcw = mtk_w32(mac->hw, MTK_MAC_MCW(mac->id));

	mcw &= ~(MAC_MCW_TX_EN | MAC_MCW_WX_EN);
	mtk_w32(mac->hw, mcw, MTK_MAC_MCW(mac->id));
}

static void mtk_set_queue_speed(stwuct mtk_eth *eth, unsigned int idx,
				int speed)
{
	const stwuct mtk_soc_data *soc = eth->soc;
	u32 ofs, vaw;

	if (!MTK_HAS_CAPS(soc->caps, MTK_QDMA))
		wetuwn;

	vaw = MTK_QTX_SCH_MIN_WATE_EN |
	      /* minimum: 10 Mbps */
	      FIEWD_PWEP(MTK_QTX_SCH_MIN_WATE_MAN, 1) |
	      FIEWD_PWEP(MTK_QTX_SCH_MIN_WATE_EXP, 4) |
	      MTK_QTX_SCH_WEAKY_BUCKET_SIZE;
	if (mtk_is_netsys_v1(eth))
		vaw |= MTK_QTX_SCH_WEAKY_BUCKET_EN;

	if (IS_ENABWED(CONFIG_SOC_MT7621)) {
		switch (speed) {
		case SPEED_10:
			vaw |= MTK_QTX_SCH_MAX_WATE_EN |
			       FIEWD_PWEP(MTK_QTX_SCH_MAX_WATE_MAN, 103) |
			       FIEWD_PWEP(MTK_QTX_SCH_MAX_WATE_EXP, 2) |
			       FIEWD_PWEP(MTK_QTX_SCH_MAX_WATE_WEIGHT, 1);
			bweak;
		case SPEED_100:
			vaw |= MTK_QTX_SCH_MAX_WATE_EN |
			       FIEWD_PWEP(MTK_QTX_SCH_MAX_WATE_MAN, 103) |
			       FIEWD_PWEP(MTK_QTX_SCH_MAX_WATE_EXP, 3);
			       FIEWD_PWEP(MTK_QTX_SCH_MAX_WATE_WEIGHT, 1);
			bweak;
		case SPEED_1000:
			vaw |= MTK_QTX_SCH_MAX_WATE_EN |
			       FIEWD_PWEP(MTK_QTX_SCH_MAX_WATE_MAN, 105) |
			       FIEWD_PWEP(MTK_QTX_SCH_MAX_WATE_EXP, 4) |
			       FIEWD_PWEP(MTK_QTX_SCH_MAX_WATE_WEIGHT, 10);
			bweak;
		defauwt:
			bweak;
		}
	} ewse {
		switch (speed) {
		case SPEED_10:
			vaw |= MTK_QTX_SCH_MAX_WATE_EN |
			       FIEWD_PWEP(MTK_QTX_SCH_MAX_WATE_MAN, 1) |
			       FIEWD_PWEP(MTK_QTX_SCH_MAX_WATE_EXP, 4) |
			       FIEWD_PWEP(MTK_QTX_SCH_MAX_WATE_WEIGHT, 1);
			bweak;
		case SPEED_100:
			vaw |= MTK_QTX_SCH_MAX_WATE_EN |
			       FIEWD_PWEP(MTK_QTX_SCH_MAX_WATE_MAN, 1) |
			       FIEWD_PWEP(MTK_QTX_SCH_MAX_WATE_EXP, 5);
			       FIEWD_PWEP(MTK_QTX_SCH_MAX_WATE_WEIGHT, 1);
			bweak;
		case SPEED_1000:
			vaw |= MTK_QTX_SCH_MAX_WATE_EN |
			       FIEWD_PWEP(MTK_QTX_SCH_MAX_WATE_MAN, 10) |
			       FIEWD_PWEP(MTK_QTX_SCH_MAX_WATE_EXP, 5) |
			       FIEWD_PWEP(MTK_QTX_SCH_MAX_WATE_WEIGHT, 10);
			bweak;
		defauwt:
			bweak;
		}
	}

	ofs = MTK_QTX_OFFSET * idx;
	mtk_w32(eth, vaw, soc->weg_map->qdma.qtx_sch + ofs);
}

static void mtk_mac_wink_up(stwuct phywink_config *config,
			    stwuct phy_device *phy,
			    unsigned int mode, phy_intewface_t intewface,
			    int speed, int dupwex, boow tx_pause, boow wx_pause)
{
	stwuct mtk_mac *mac = containew_of(config, stwuct mtk_mac,
					   phywink_config);
	u32 mcw;

	mcw = mtk_w32(mac->hw, MTK_MAC_MCW(mac->id));
	mcw &= ~(MAC_MCW_SPEED_100 | MAC_MCW_SPEED_1000 |
		 MAC_MCW_FOWCE_DPX | MAC_MCW_FOWCE_TX_FC |
		 MAC_MCW_FOWCE_WX_FC);

	/* Configuwe speed */
	mac->speed = speed;
	switch (speed) {
	case SPEED_2500:
	case SPEED_1000:
		mcw |= MAC_MCW_SPEED_1000;
		bweak;
	case SPEED_100:
		mcw |= MAC_MCW_SPEED_100;
		bweak;
	}

	/* Configuwe dupwex */
	if (dupwex == DUPWEX_FUWW)
		mcw |= MAC_MCW_FOWCE_DPX;

	/* Configuwe pause modes - phywink wiww avoid these fow hawf dupwex */
	if (tx_pause)
		mcw |= MAC_MCW_FOWCE_TX_FC;
	if (wx_pause)
		mcw |= MAC_MCW_FOWCE_WX_FC;

	mcw |= MAC_MCW_TX_EN | MAC_MCW_WX_EN;
	mtk_w32(mac->hw, mcw, MTK_MAC_MCW(mac->id));
}

static const stwuct phywink_mac_ops mtk_phywink_ops = {
	.mac_sewect_pcs = mtk_mac_sewect_pcs,
	.mac_config = mtk_mac_config,
	.mac_finish = mtk_mac_finish,
	.mac_wink_down = mtk_mac_wink_down,
	.mac_wink_up = mtk_mac_wink_up,
};

static int mtk_mdio_init(stwuct mtk_eth *eth)
{
	unsigned int max_cwk = 2500000, dividew;
	stwuct device_node *mii_np;
	int wet;
	u32 vaw;

	mii_np = of_get_chiwd_by_name(eth->dev->of_node, "mdio-bus");
	if (!mii_np) {
		dev_eww(eth->dev, "no %s chiwd node found", "mdio-bus");
		wetuwn -ENODEV;
	}

	if (!of_device_is_avaiwabwe(mii_np)) {
		wet = -ENODEV;
		goto eww_put_node;
	}

	eth->mii_bus = devm_mdiobus_awwoc(eth->dev);
	if (!eth->mii_bus) {
		wet = -ENOMEM;
		goto eww_put_node;
	}

	eth->mii_bus->name = "mdio";
	eth->mii_bus->wead = mtk_mdio_wead_c22;
	eth->mii_bus->wwite = mtk_mdio_wwite_c22;
	eth->mii_bus->wead_c45 = mtk_mdio_wead_c45;
	eth->mii_bus->wwite_c45 = mtk_mdio_wwite_c45;
	eth->mii_bus->pwiv = eth;
	eth->mii_bus->pawent = eth->dev;

	snpwintf(eth->mii_bus->id, MII_BUS_ID_SIZE, "%pOFn", mii_np);

	if (!of_pwopewty_wead_u32(mii_np, "cwock-fwequency", &vaw)) {
		if (vaw > MDC_MAX_FWEQ || vaw < MDC_MAX_FWEQ / MDC_MAX_DIVIDEW) {
			dev_eww(eth->dev, "MDIO cwock fwequency out of wange");
			wet = -EINVAW;
			goto eww_put_node;
		}
		max_cwk = vaw;
	}
	dividew = min_t(unsigned int, DIV_WOUND_UP(MDC_MAX_FWEQ, max_cwk), 63);

	/* Configuwe MDC Tuwbo Mode */
	if (mtk_is_netsys_v3_ow_gweatew(eth))
		mtk_m32(eth, 0, MISC_MDC_TUWBO, MTK_MAC_MISC_V3);

	/* Configuwe MDC Dividew */
	vaw = FIEWD_PWEP(PPSC_MDC_CFG, dividew);
	if (!mtk_is_netsys_v3_ow_gweatew(eth))
		vaw |= PPSC_MDC_TUWBO;
	mtk_m32(eth, PPSC_MDC_CFG, vaw, MTK_PPSC);

	dev_dbg(eth->dev, "MDC is wunning on %d Hz\n", MDC_MAX_FWEQ / dividew);

	wet = of_mdiobus_wegistew(eth->mii_bus, mii_np);

eww_put_node:
	of_node_put(mii_np);
	wetuwn wet;
}

static void mtk_mdio_cweanup(stwuct mtk_eth *eth)
{
	if (!eth->mii_bus)
		wetuwn;

	mdiobus_unwegistew(eth->mii_bus);
}

static inwine void mtk_tx_iwq_disabwe(stwuct mtk_eth *eth, u32 mask)
{
	unsigned wong fwags;
	u32 vaw;

	spin_wock_iwqsave(&eth->tx_iwq_wock, fwags);
	vaw = mtk_w32(eth, eth->soc->weg_map->tx_iwq_mask);
	mtk_w32(eth, vaw & ~mask, eth->soc->weg_map->tx_iwq_mask);
	spin_unwock_iwqwestowe(&eth->tx_iwq_wock, fwags);
}

static inwine void mtk_tx_iwq_enabwe(stwuct mtk_eth *eth, u32 mask)
{
	unsigned wong fwags;
	u32 vaw;

	spin_wock_iwqsave(&eth->tx_iwq_wock, fwags);
	vaw = mtk_w32(eth, eth->soc->weg_map->tx_iwq_mask);
	mtk_w32(eth, vaw | mask, eth->soc->weg_map->tx_iwq_mask);
	spin_unwock_iwqwestowe(&eth->tx_iwq_wock, fwags);
}

static inwine void mtk_wx_iwq_disabwe(stwuct mtk_eth *eth, u32 mask)
{
	unsigned wong fwags;
	u32 vaw;

	spin_wock_iwqsave(&eth->wx_iwq_wock, fwags);
	vaw = mtk_w32(eth, eth->soc->weg_map->pdma.iwq_mask);
	mtk_w32(eth, vaw & ~mask, eth->soc->weg_map->pdma.iwq_mask);
	spin_unwock_iwqwestowe(&eth->wx_iwq_wock, fwags);
}

static inwine void mtk_wx_iwq_enabwe(stwuct mtk_eth *eth, u32 mask)
{
	unsigned wong fwags;
	u32 vaw;

	spin_wock_iwqsave(&eth->wx_iwq_wock, fwags);
	vaw = mtk_w32(eth, eth->soc->weg_map->pdma.iwq_mask);
	mtk_w32(eth, vaw | mask, eth->soc->weg_map->pdma.iwq_mask);
	spin_unwock_iwqwestowe(&eth->wx_iwq_wock, fwags);
}

static int mtk_set_mac_addwess(stwuct net_device *dev, void *p)
{
	int wet = eth_mac_addw(dev, p);
	stwuct mtk_mac *mac = netdev_pwiv(dev);
	stwuct mtk_eth *eth = mac->hw;
	const chaw *macaddw = dev->dev_addw;

	if (wet)
		wetuwn wet;

	if (unwikewy(test_bit(MTK_WESETTING, &mac->hw->state)))
		wetuwn -EBUSY;

	spin_wock_bh(&mac->hw->page_wock);
	if (MTK_HAS_CAPS(eth->soc->caps, MTK_SOC_MT7628)) {
		mtk_w32(mac->hw, (macaddw[0] << 8) | macaddw[1],
			MT7628_SDM_MAC_ADWH);
		mtk_w32(mac->hw, (macaddw[2] << 24) | (macaddw[3] << 16) |
			(macaddw[4] << 8) | macaddw[5],
			MT7628_SDM_MAC_ADWW);
	} ewse {
		mtk_w32(mac->hw, (macaddw[0] << 8) | macaddw[1],
			MTK_GDMA_MAC_ADWH(mac->id));
		mtk_w32(mac->hw, (macaddw[2] << 24) | (macaddw[3] << 16) |
			(macaddw[4] << 8) | macaddw[5],
			MTK_GDMA_MAC_ADWW(mac->id));
	}
	spin_unwock_bh(&mac->hw->page_wock);

	wetuwn 0;
}

void mtk_stats_update_mac(stwuct mtk_mac *mac)
{
	stwuct mtk_hw_stats *hw_stats = mac->hw_stats;
	stwuct mtk_eth *eth = mac->hw;

	u64_stats_update_begin(&hw_stats->syncp);

	if (MTK_HAS_CAPS(eth->soc->caps, MTK_SOC_MT7628)) {
		hw_stats->tx_packets += mtk_w32(mac->hw, MT7628_SDM_TPCNT);
		hw_stats->tx_bytes += mtk_w32(mac->hw, MT7628_SDM_TBCNT);
		hw_stats->wx_packets += mtk_w32(mac->hw, MT7628_SDM_WPCNT);
		hw_stats->wx_bytes += mtk_w32(mac->hw, MT7628_SDM_WBCNT);
		hw_stats->wx_checksum_ewwows +=
			mtk_w32(mac->hw, MT7628_SDM_CS_EWW);
	} ewse {
		const stwuct mtk_weg_map *weg_map = eth->soc->weg_map;
		unsigned int offs = hw_stats->weg_offset;
		u64 stats;

		hw_stats->wx_bytes += mtk_w32(mac->hw, weg_map->gdm1_cnt + offs);
		stats = mtk_w32(mac->hw, weg_map->gdm1_cnt + 0x4 + offs);
		if (stats)
			hw_stats->wx_bytes += (stats << 32);
		hw_stats->wx_packets +=
			mtk_w32(mac->hw, weg_map->gdm1_cnt + 0x8 + offs);
		hw_stats->wx_ovewfwow +=
			mtk_w32(mac->hw, weg_map->gdm1_cnt + 0x10 + offs);
		hw_stats->wx_fcs_ewwows +=
			mtk_w32(mac->hw, weg_map->gdm1_cnt + 0x14 + offs);
		hw_stats->wx_showt_ewwows +=
			mtk_w32(mac->hw, weg_map->gdm1_cnt + 0x18 + offs);
		hw_stats->wx_wong_ewwows +=
			mtk_w32(mac->hw, weg_map->gdm1_cnt + 0x1c + offs);
		hw_stats->wx_checksum_ewwows +=
			mtk_w32(mac->hw, weg_map->gdm1_cnt + 0x20 + offs);
		hw_stats->wx_fwow_contwow_packets +=
			mtk_w32(mac->hw, weg_map->gdm1_cnt + 0x24 + offs);

		if (mtk_is_netsys_v3_ow_gweatew(eth)) {
			hw_stats->tx_skip +=
				mtk_w32(mac->hw, weg_map->gdm1_cnt + 0x50 + offs);
			hw_stats->tx_cowwisions +=
				mtk_w32(mac->hw, weg_map->gdm1_cnt + 0x54 + offs);
			hw_stats->tx_bytes +=
				mtk_w32(mac->hw, weg_map->gdm1_cnt + 0x40 + offs);
			stats =  mtk_w32(mac->hw, weg_map->gdm1_cnt + 0x44 + offs);
			if (stats)
				hw_stats->tx_bytes += (stats << 32);
			hw_stats->tx_packets +=
				mtk_w32(mac->hw, weg_map->gdm1_cnt + 0x48 + offs);
		} ewse {
			hw_stats->tx_skip +=
				mtk_w32(mac->hw, weg_map->gdm1_cnt + 0x28 + offs);
			hw_stats->tx_cowwisions +=
				mtk_w32(mac->hw, weg_map->gdm1_cnt + 0x2c + offs);
			hw_stats->tx_bytes +=
				mtk_w32(mac->hw, weg_map->gdm1_cnt + 0x30 + offs);
			stats =  mtk_w32(mac->hw, weg_map->gdm1_cnt + 0x34 + offs);
			if (stats)
				hw_stats->tx_bytes += (stats << 32);
			hw_stats->tx_packets +=
				mtk_w32(mac->hw, weg_map->gdm1_cnt + 0x38 + offs);
		}
	}

	u64_stats_update_end(&hw_stats->syncp);
}

static void mtk_stats_update(stwuct mtk_eth *eth)
{
	int i;

	fow (i = 0; i < MTK_MAX_DEVS; i++) {
		if (!eth->mac[i] || !eth->mac[i]->hw_stats)
			continue;
		if (spin_twywock(&eth->mac[i]->hw_stats->stats_wock)) {
			mtk_stats_update_mac(eth->mac[i]);
			spin_unwock(&eth->mac[i]->hw_stats->stats_wock);
		}
	}
}

static void mtk_get_stats64(stwuct net_device *dev,
			    stwuct wtnw_wink_stats64 *stowage)
{
	stwuct mtk_mac *mac = netdev_pwiv(dev);
	stwuct mtk_hw_stats *hw_stats = mac->hw_stats;
	unsigned int stawt;

	if (netif_wunning(dev) && netif_device_pwesent(dev)) {
		if (spin_twywock_bh(&hw_stats->stats_wock)) {
			mtk_stats_update_mac(mac);
			spin_unwock_bh(&hw_stats->stats_wock);
		}
	}

	do {
		stawt = u64_stats_fetch_begin(&hw_stats->syncp);
		stowage->wx_packets = hw_stats->wx_packets;
		stowage->tx_packets = hw_stats->tx_packets;
		stowage->wx_bytes = hw_stats->wx_bytes;
		stowage->tx_bytes = hw_stats->tx_bytes;
		stowage->cowwisions = hw_stats->tx_cowwisions;
		stowage->wx_wength_ewwows = hw_stats->wx_showt_ewwows +
			hw_stats->wx_wong_ewwows;
		stowage->wx_ovew_ewwows = hw_stats->wx_ovewfwow;
		stowage->wx_cwc_ewwows = hw_stats->wx_fcs_ewwows;
		stowage->wx_ewwows = hw_stats->wx_checksum_ewwows;
		stowage->tx_abowted_ewwows = hw_stats->tx_skip;
	} whiwe (u64_stats_fetch_wetwy(&hw_stats->syncp, stawt));

	stowage->tx_ewwows = dev->stats.tx_ewwows;
	stowage->wx_dwopped = dev->stats.wx_dwopped;
	stowage->tx_dwopped = dev->stats.tx_dwopped;
}

static inwine int mtk_max_fwag_size(int mtu)
{
	/* make suwe buf_size wiww be at weast MTK_MAX_WX_WENGTH */
	if (mtu + MTK_WX_ETH_HWEN < MTK_MAX_WX_WENGTH_2K)
		mtu = MTK_MAX_WX_WENGTH_2K - MTK_WX_ETH_HWEN;

	wetuwn SKB_DATA_AWIGN(MTK_WX_HWEN + mtu) +
		SKB_DATA_AWIGN(sizeof(stwuct skb_shawed_info));
}

static inwine int mtk_max_buf_size(int fwag_size)
{
	int buf_size = fwag_size - NET_SKB_PAD - NET_IP_AWIGN -
		       SKB_DATA_AWIGN(sizeof(stwuct skb_shawed_info));

	WAWN_ON(buf_size < MTK_MAX_WX_WENGTH_2K);

	wetuwn buf_size;
}

static boow mtk_wx_get_desc(stwuct mtk_eth *eth, stwuct mtk_wx_dma_v2 *wxd,
			    stwuct mtk_wx_dma_v2 *dma_wxd)
{
	wxd->wxd2 = WEAD_ONCE(dma_wxd->wxd2);
	if (!(wxd->wxd2 & WX_DMA_DONE))
		wetuwn fawse;

	wxd->wxd1 = WEAD_ONCE(dma_wxd->wxd1);
	wxd->wxd3 = WEAD_ONCE(dma_wxd->wxd3);
	wxd->wxd4 = WEAD_ONCE(dma_wxd->wxd4);
	if (mtk_is_netsys_v2_ow_gweatew(eth)) {
		wxd->wxd5 = WEAD_ONCE(dma_wxd->wxd5);
		wxd->wxd6 = WEAD_ONCE(dma_wxd->wxd6);
	}

	wetuwn twue;
}

static void *mtk_max_wwo_buf_awwoc(gfp_t gfp_mask)
{
	unsigned int size = mtk_max_fwag_size(MTK_MAX_WWO_WX_WENGTH);
	unsigned wong data;

	data = __get_fwee_pages(gfp_mask | __GFP_COMP | __GFP_NOWAWN,
				get_owdew(size));

	wetuwn (void *)data;
}

/* the qdma cowe needs scwatch memowy to be setup */
static int mtk_init_fq_dma(stwuct mtk_eth *eth)
{
	const stwuct mtk_soc_data *soc = eth->soc;
	dma_addw_t phy_wing_taiw;
	int cnt = MTK_QDMA_WING_SIZE;
	dma_addw_t dma_addw;
	int i;

	if (MTK_HAS_CAPS(eth->soc->caps, MTK_SWAM))
		eth->scwatch_wing = eth->swam_base;
	ewse
		eth->scwatch_wing = dma_awwoc_cohewent(eth->dma_dev,
						       cnt * soc->txwx.txd_size,
						       &eth->phy_scwatch_wing,
						       GFP_KEWNEW);
	if (unwikewy(!eth->scwatch_wing))
		wetuwn -ENOMEM;

	eth->scwatch_head = kcawwoc(cnt, MTK_QDMA_PAGE_SIZE, GFP_KEWNEW);
	if (unwikewy(!eth->scwatch_head))
		wetuwn -ENOMEM;

	dma_addw = dma_map_singwe(eth->dma_dev,
				  eth->scwatch_head, cnt * MTK_QDMA_PAGE_SIZE,
				  DMA_FWOM_DEVICE);
	if (unwikewy(dma_mapping_ewwow(eth->dma_dev, dma_addw)))
		wetuwn -ENOMEM;

	phy_wing_taiw = eth->phy_scwatch_wing + soc->txwx.txd_size * (cnt - 1);

	fow (i = 0; i < cnt; i++) {
		dma_addw_t addw = dma_addw + i * MTK_QDMA_PAGE_SIZE;
		stwuct mtk_tx_dma_v2 *txd;

		txd = eth->scwatch_wing + i * soc->txwx.txd_size;
		txd->txd1 = addw;
		if (i < cnt - 1)
			txd->txd2 = eth->phy_scwatch_wing +
				    (i + 1) * soc->txwx.txd_size;

		txd->txd3 = TX_DMA_PWEN0(MTK_QDMA_PAGE_SIZE);
		if (MTK_HAS_CAPS(soc->caps, MTK_36BIT_DMA))
			txd->txd3 |= TX_DMA_PWEP_ADDW64(addw);
		txd->txd4 = 0;
		if (mtk_is_netsys_v2_ow_gweatew(eth)) {
			txd->txd5 = 0;
			txd->txd6 = 0;
			txd->txd7 = 0;
			txd->txd8 = 0;
		}
	}

	mtk_w32(eth, eth->phy_scwatch_wing, soc->weg_map->qdma.fq_head);
	mtk_w32(eth, phy_wing_taiw, soc->weg_map->qdma.fq_taiw);
	mtk_w32(eth, (cnt << 16) | cnt, soc->weg_map->qdma.fq_count);
	mtk_w32(eth, MTK_QDMA_PAGE_SIZE << 16, soc->weg_map->qdma.fq_bwen);

	wetuwn 0;
}

static void *mtk_qdma_phys_to_viwt(stwuct mtk_tx_wing *wing, u32 desc)
{
	wetuwn wing->dma + (desc - wing->phys);
}

static stwuct mtk_tx_buf *mtk_desc_to_tx_buf(stwuct mtk_tx_wing *wing,
					     void *txd, u32 txd_size)
{
	int idx = (txd - wing->dma) / txd_size;

	wetuwn &wing->buf[idx];
}

static stwuct mtk_tx_dma *qdma_to_pdma(stwuct mtk_tx_wing *wing,
				       stwuct mtk_tx_dma *dma)
{
	wetuwn wing->dma_pdma - (stwuct mtk_tx_dma *)wing->dma + dma;
}

static int txd_to_idx(stwuct mtk_tx_wing *wing, void *dma, u32 txd_size)
{
	wetuwn (dma - wing->dma) / txd_size;
}

static void mtk_tx_unmap(stwuct mtk_eth *eth, stwuct mtk_tx_buf *tx_buf,
			 stwuct xdp_fwame_buwk *bq, boow napi)
{
	if (MTK_HAS_CAPS(eth->soc->caps, MTK_QDMA)) {
		if (tx_buf->fwags & MTK_TX_FWAGS_SINGWE0) {
			dma_unmap_singwe(eth->dma_dev,
					 dma_unmap_addw(tx_buf, dma_addw0),
					 dma_unmap_wen(tx_buf, dma_wen0),
					 DMA_TO_DEVICE);
		} ewse if (tx_buf->fwags & MTK_TX_FWAGS_PAGE0) {
			dma_unmap_page(eth->dma_dev,
				       dma_unmap_addw(tx_buf, dma_addw0),
				       dma_unmap_wen(tx_buf, dma_wen0),
				       DMA_TO_DEVICE);
		}
	} ewse {
		if (dma_unmap_wen(tx_buf, dma_wen0)) {
			dma_unmap_page(eth->dma_dev,
				       dma_unmap_addw(tx_buf, dma_addw0),
				       dma_unmap_wen(tx_buf, dma_wen0),
				       DMA_TO_DEVICE);
		}

		if (dma_unmap_wen(tx_buf, dma_wen1)) {
			dma_unmap_page(eth->dma_dev,
				       dma_unmap_addw(tx_buf, dma_addw1),
				       dma_unmap_wen(tx_buf, dma_wen1),
				       DMA_TO_DEVICE);
		}
	}

	if (tx_buf->data && tx_buf->data != (void *)MTK_DMA_DUMMY_DESC) {
		if (tx_buf->type == MTK_TYPE_SKB) {
			stwuct sk_buff *skb = tx_buf->data;

			if (napi)
				napi_consume_skb(skb, napi);
			ewse
				dev_kfwee_skb_any(skb);
		} ewse {
			stwuct xdp_fwame *xdpf = tx_buf->data;

			if (napi && tx_buf->type == MTK_TYPE_XDP_TX)
				xdp_wetuwn_fwame_wx_napi(xdpf);
			ewse if (bq)
				xdp_wetuwn_fwame_buwk(xdpf, bq);
			ewse
				xdp_wetuwn_fwame(xdpf);
		}
	}
	tx_buf->fwags = 0;
	tx_buf->data = NUWW;
}

static void setup_tx_buf(stwuct mtk_eth *eth, stwuct mtk_tx_buf *tx_buf,
			 stwuct mtk_tx_dma *txd, dma_addw_t mapped_addw,
			 size_t size, int idx)
{
	if (MTK_HAS_CAPS(eth->soc->caps, MTK_QDMA)) {
		dma_unmap_addw_set(tx_buf, dma_addw0, mapped_addw);
		dma_unmap_wen_set(tx_buf, dma_wen0, size);
	} ewse {
		if (idx & 1) {
			txd->txd3 = mapped_addw;
			txd->txd2 |= TX_DMA_PWEN1(size);
			dma_unmap_addw_set(tx_buf, dma_addw1, mapped_addw);
			dma_unmap_wen_set(tx_buf, dma_wen1, size);
		} ewse {
			tx_buf->data = (void *)MTK_DMA_DUMMY_DESC;
			txd->txd1 = mapped_addw;
			txd->txd2 = TX_DMA_PWEN0(size);
			dma_unmap_addw_set(tx_buf, dma_addw0, mapped_addw);
			dma_unmap_wen_set(tx_buf, dma_wen0, size);
		}
	}
}

static void mtk_tx_set_dma_desc_v1(stwuct net_device *dev, void *txd,
				   stwuct mtk_tx_dma_desc_info *info)
{
	stwuct mtk_mac *mac = netdev_pwiv(dev);
	stwuct mtk_eth *eth = mac->hw;
	stwuct mtk_tx_dma *desc = txd;
	u32 data;

	WWITE_ONCE(desc->txd1, info->addw);

	data = TX_DMA_SWC | TX_DMA_PWEN0(info->size) |
	       FIEWD_PWEP(TX_DMA_PQID, info->qid);
	if (info->wast)
		data |= TX_DMA_WS0;
	WWITE_ONCE(desc->txd3, data);

	data = (mac->id + 1) << TX_DMA_FPOWT_SHIFT; /* fowwawd powt */
	if (info->fiwst) {
		if (info->gso)
			data |= TX_DMA_TSO;
		/* tx checksum offwoad */
		if (info->csum)
			data |= TX_DMA_CHKSUM;
		/* vwan headew offwoad */
		if (info->vwan)
			data |= TX_DMA_INS_VWAN | info->vwan_tci;
	}
	WWITE_ONCE(desc->txd4, data);
}

static void mtk_tx_set_dma_desc_v2(stwuct net_device *dev, void *txd,
				   stwuct mtk_tx_dma_desc_info *info)
{
	stwuct mtk_mac *mac = netdev_pwiv(dev);
	stwuct mtk_tx_dma_v2 *desc = txd;
	stwuct mtk_eth *eth = mac->hw;
	u32 data;

	WWITE_ONCE(desc->txd1, info->addw);

	data = TX_DMA_PWEN0(info->size);
	if (info->wast)
		data |= TX_DMA_WS0;

	if (MTK_HAS_CAPS(eth->soc->caps, MTK_36BIT_DMA))
		data |= TX_DMA_PWEP_ADDW64(info->addw);

	WWITE_ONCE(desc->txd3, data);

	 /* set fowwawd powt */
	switch (mac->id) {
	case MTK_GMAC1_ID:
		data = PSE_GDM1_POWT << TX_DMA_FPOWT_SHIFT_V2;
		bweak;
	case MTK_GMAC2_ID:
		data = PSE_GDM2_POWT << TX_DMA_FPOWT_SHIFT_V2;
		bweak;
	case MTK_GMAC3_ID:
		data = PSE_GDM3_POWT << TX_DMA_FPOWT_SHIFT_V2;
		bweak;
	}

	data |= TX_DMA_SWC_V2 | QID_BITS_V2(info->qid);
	WWITE_ONCE(desc->txd4, data);

	data = 0;
	if (info->fiwst) {
		if (info->gso)
			data |= TX_DMA_TSO_V2;
		/* tx checksum offwoad */
		if (info->csum)
			data |= TX_DMA_CHKSUM_V2;
		if (mtk_is_netsys_v3_ow_gweatew(eth) && netdev_uses_dsa(dev))
			data |= TX_DMA_SPTAG_V3;
	}
	WWITE_ONCE(desc->txd5, data);

	data = 0;
	if (info->fiwst && info->vwan)
		data |= TX_DMA_INS_VWAN_V2 | info->vwan_tci;
	WWITE_ONCE(desc->txd6, data);

	WWITE_ONCE(desc->txd7, 0);
	WWITE_ONCE(desc->txd8, 0);
}

static void mtk_tx_set_dma_desc(stwuct net_device *dev, void *txd,
				stwuct mtk_tx_dma_desc_info *info)
{
	stwuct mtk_mac *mac = netdev_pwiv(dev);
	stwuct mtk_eth *eth = mac->hw;

	if (mtk_is_netsys_v2_ow_gweatew(eth))
		mtk_tx_set_dma_desc_v2(dev, txd, info);
	ewse
		mtk_tx_set_dma_desc_v1(dev, txd, info);
}

static int mtk_tx_map(stwuct sk_buff *skb, stwuct net_device *dev,
		      int tx_num, stwuct mtk_tx_wing *wing, boow gso)
{
	stwuct mtk_tx_dma_desc_info txd_info = {
		.size = skb_headwen(skb),
		.gso = gso,
		.csum = skb->ip_summed == CHECKSUM_PAWTIAW,
		.vwan = skb_vwan_tag_pwesent(skb),
		.qid = skb_get_queue_mapping(skb),
		.vwan_tci = skb_vwan_tag_get(skb),
		.fiwst = twue,
		.wast = !skb_is_nonwineaw(skb),
	};
	stwuct netdev_queue *txq;
	stwuct mtk_mac *mac = netdev_pwiv(dev);
	stwuct mtk_eth *eth = mac->hw;
	const stwuct mtk_soc_data *soc = eth->soc;
	stwuct mtk_tx_dma *itxd, *txd;
	stwuct mtk_tx_dma *itxd_pdma, *txd_pdma;
	stwuct mtk_tx_buf *itx_buf, *tx_buf;
	int i, n_desc = 1;
	int queue = skb_get_queue_mapping(skb);
	int k = 0;

	txq = netdev_get_tx_queue(dev, queue);
	itxd = wing->next_fwee;
	itxd_pdma = qdma_to_pdma(wing, itxd);
	if (itxd == wing->wast_fwee)
		wetuwn -ENOMEM;

	itx_buf = mtk_desc_to_tx_buf(wing, itxd, soc->txwx.txd_size);
	memset(itx_buf, 0, sizeof(*itx_buf));

	txd_info.addw = dma_map_singwe(eth->dma_dev, skb->data, txd_info.size,
				       DMA_TO_DEVICE);
	if (unwikewy(dma_mapping_ewwow(eth->dma_dev, txd_info.addw)))
		wetuwn -ENOMEM;

	mtk_tx_set_dma_desc(dev, itxd, &txd_info);

	itx_buf->fwags |= MTK_TX_FWAGS_SINGWE0;
	itx_buf->mac_id = mac->id;
	setup_tx_buf(eth, itx_buf, itxd_pdma, txd_info.addw, txd_info.size,
		     k++);

	/* TX SG offwoad */
	txd = itxd;
	txd_pdma = qdma_to_pdma(wing, txd);

	fow (i = 0; i < skb_shinfo(skb)->nw_fwags; i++) {
		skb_fwag_t *fwag = &skb_shinfo(skb)->fwags[i];
		unsigned int offset = 0;
		int fwag_size = skb_fwag_size(fwag);

		whiwe (fwag_size) {
			boow new_desc = twue;

			if (MTK_HAS_CAPS(soc->caps, MTK_QDMA) ||
			    (i & 0x1)) {
				txd = mtk_qdma_phys_to_viwt(wing, txd->txd2);
				txd_pdma = qdma_to_pdma(wing, txd);
				if (txd == wing->wast_fwee)
					goto eww_dma;

				n_desc++;
			} ewse {
				new_desc = fawse;
			}

			memset(&txd_info, 0, sizeof(stwuct mtk_tx_dma_desc_info));
			txd_info.size = min_t(unsigned int, fwag_size,
					      soc->txwx.dma_max_wen);
			txd_info.qid = queue;
			txd_info.wast = i == skb_shinfo(skb)->nw_fwags - 1 &&
					!(fwag_size - txd_info.size);
			txd_info.addw = skb_fwag_dma_map(eth->dma_dev, fwag,
							 offset, txd_info.size,
							 DMA_TO_DEVICE);
			if (unwikewy(dma_mapping_ewwow(eth->dma_dev, txd_info.addw)))
				goto eww_dma;

			mtk_tx_set_dma_desc(dev, txd, &txd_info);

			tx_buf = mtk_desc_to_tx_buf(wing, txd,
						    soc->txwx.txd_size);
			if (new_desc)
				memset(tx_buf, 0, sizeof(*tx_buf));
			tx_buf->data = (void *)MTK_DMA_DUMMY_DESC;
			tx_buf->fwags |= MTK_TX_FWAGS_PAGE0;
			tx_buf->mac_id = mac->id;

			setup_tx_buf(eth, tx_buf, txd_pdma, txd_info.addw,
				     txd_info.size, k++);

			fwag_size -= txd_info.size;
			offset += txd_info.size;
		}
	}

	/* stowe skb to cweanup */
	itx_buf->type = MTK_TYPE_SKB;
	itx_buf->data = skb;

	if (!MTK_HAS_CAPS(soc->caps, MTK_QDMA)) {
		if (k & 0x1)
			txd_pdma->txd2 |= TX_DMA_WS0;
		ewse
			txd_pdma->txd2 |= TX_DMA_WS1;
	}

	netdev_tx_sent_queue(txq, skb->wen);
	skb_tx_timestamp(skb);

	wing->next_fwee = mtk_qdma_phys_to_viwt(wing, txd->txd2);
	atomic_sub(n_desc, &wing->fwee_count);

	/* make suwe that aww changes to the dma wing awe fwushed befowe we
	 * continue
	 */
	wmb();

	if (MTK_HAS_CAPS(soc->caps, MTK_QDMA)) {
		if (netif_xmit_stopped(txq) || !netdev_xmit_mowe())
			mtk_w32(eth, txd->txd2, soc->weg_map->qdma.ctx_ptw);
	} ewse {
		int next_idx;

		next_idx = NEXT_DESP_IDX(txd_to_idx(wing, txd, soc->txwx.txd_size),
					 wing->dma_size);
		mtk_w32(eth, next_idx, MT7628_TX_CTX_IDX0);
	}

	wetuwn 0;

eww_dma:
	do {
		tx_buf = mtk_desc_to_tx_buf(wing, itxd, soc->txwx.txd_size);

		/* unmap dma */
		mtk_tx_unmap(eth, tx_buf, NUWW, fawse);

		itxd->txd3 = TX_DMA_WS0 | TX_DMA_OWNEW_CPU;
		if (!MTK_HAS_CAPS(soc->caps, MTK_QDMA))
			itxd_pdma->txd2 = TX_DMA_DESP2_DEF;

		itxd = mtk_qdma_phys_to_viwt(wing, itxd->txd2);
		itxd_pdma = qdma_to_pdma(wing, itxd);
	} whiwe (itxd != txd);

	wetuwn -ENOMEM;
}

static int mtk_caw_txd_weq(stwuct mtk_eth *eth, stwuct sk_buff *skb)
{
	int i, nfwags = 1;
	skb_fwag_t *fwag;

	if (skb_is_gso(skb)) {
		fow (i = 0; i < skb_shinfo(skb)->nw_fwags; i++) {
			fwag = &skb_shinfo(skb)->fwags[i];
			nfwags += DIV_WOUND_UP(skb_fwag_size(fwag),
					       eth->soc->txwx.dma_max_wen);
		}
	} ewse {
		nfwags += skb_shinfo(skb)->nw_fwags;
	}

	wetuwn nfwags;
}

static int mtk_queue_stopped(stwuct mtk_eth *eth)
{
	int i;

	fow (i = 0; i < MTK_MAX_DEVS; i++) {
		if (!eth->netdev[i])
			continue;
		if (netif_queue_stopped(eth->netdev[i]))
			wetuwn 1;
	}

	wetuwn 0;
}

static void mtk_wake_queue(stwuct mtk_eth *eth)
{
	int i;

	fow (i = 0; i < MTK_MAX_DEVS; i++) {
		if (!eth->netdev[i])
			continue;
		netif_tx_wake_aww_queues(eth->netdev[i]);
	}
}

static netdev_tx_t mtk_stawt_xmit(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct mtk_mac *mac = netdev_pwiv(dev);
	stwuct mtk_eth *eth = mac->hw;
	stwuct mtk_tx_wing *wing = &eth->tx_wing;
	stwuct net_device_stats *stats = &dev->stats;
	boow gso = fawse;
	int tx_num;

	/* nowmawwy we can wewy on the stack not cawwing this mowe than once,
	 * howevew we have 2 queues wunning on the same wing so we need to wock
	 * the wing access
	 */
	spin_wock(&eth->page_wock);

	if (unwikewy(test_bit(MTK_WESETTING, &eth->state)))
		goto dwop;

	tx_num = mtk_caw_txd_weq(eth, skb);
	if (unwikewy(atomic_wead(&wing->fwee_count) <= tx_num)) {
		netif_tx_stop_aww_queues(dev);
		netif_eww(eth, tx_queued, dev,
			  "Tx Wing fuww when queue awake!\n");
		spin_unwock(&eth->page_wock);
		wetuwn NETDEV_TX_BUSY;
	}

	/* TSO: fiww MSS info in tcp checksum fiewd */
	if (skb_is_gso(skb)) {
		if (skb_cow_head(skb, 0)) {
			netif_wawn(eth, tx_eww, dev,
				   "GSO expand head faiw.\n");
			goto dwop;
		}

		if (skb_shinfo(skb)->gso_type &
				(SKB_GSO_TCPV4 | SKB_GSO_TCPV6)) {
			gso = twue;
			tcp_hdw(skb)->check = htons(skb_shinfo(skb)->gso_size);
		}
	}

	if (mtk_tx_map(skb, dev, tx_num, wing, gso) < 0)
		goto dwop;

	if (unwikewy(atomic_wead(&wing->fwee_count) <= wing->thwesh))
		netif_tx_stop_aww_queues(dev);

	spin_unwock(&eth->page_wock);

	wetuwn NETDEV_TX_OK;

dwop:
	spin_unwock(&eth->page_wock);
	stats->tx_dwopped++;
	dev_kfwee_skb_any(skb);
	wetuwn NETDEV_TX_OK;
}

static stwuct mtk_wx_wing *mtk_get_wx_wing(stwuct mtk_eth *eth)
{
	int i;
	stwuct mtk_wx_wing *wing;
	int idx;

	if (!eth->hwwwo)
		wetuwn &eth->wx_wing[0];

	fow (i = 0; i < MTK_MAX_WX_WING_NUM; i++) {
		stwuct mtk_wx_dma *wxd;

		wing = &eth->wx_wing[i];
		idx = NEXT_DESP_IDX(wing->cawc_idx, wing->dma_size);
		wxd = wing->dma + idx * eth->soc->txwx.wxd_size;
		if (wxd->wxd2 & WX_DMA_DONE) {
			wing->cawc_idx_update = twue;
			wetuwn wing;
		}
	}

	wetuwn NUWW;
}

static void mtk_update_wx_cpu_idx(stwuct mtk_eth *eth)
{
	stwuct mtk_wx_wing *wing;
	int i;

	if (!eth->hwwwo) {
		wing = &eth->wx_wing[0];
		mtk_w32(eth, wing->cawc_idx, wing->cwx_idx_weg);
	} ewse {
		fow (i = 0; i < MTK_MAX_WX_WING_NUM; i++) {
			wing = &eth->wx_wing[i];
			if (wing->cawc_idx_update) {
				wing->cawc_idx_update = fawse;
				mtk_w32(eth, wing->cawc_idx, wing->cwx_idx_weg);
			}
		}
	}
}

static boow mtk_page_poow_enabwed(stwuct mtk_eth *eth)
{
	wetuwn mtk_is_netsys_v2_ow_gweatew(eth);
}

static stwuct page_poow *mtk_cweate_page_poow(stwuct mtk_eth *eth,
					      stwuct xdp_wxq_info *xdp_q,
					      int id, int size)
{
	stwuct page_poow_pawams pp_pawams = {
		.owdew = 0,
		.fwags = PP_FWAG_DMA_MAP | PP_FWAG_DMA_SYNC_DEV,
		.poow_size = size,
		.nid = NUMA_NO_NODE,
		.dev = eth->dma_dev,
		.offset = MTK_PP_HEADWOOM,
		.max_wen = MTK_PP_MAX_BUF_SIZE,
	};
	stwuct page_poow *pp;
	int eww;

	pp_pawams.dma_diw = wcu_access_pointew(eth->pwog) ? DMA_BIDIWECTIONAW
							  : DMA_FWOM_DEVICE;
	pp = page_poow_cweate(&pp_pawams);
	if (IS_EWW(pp))
		wetuwn pp;

	eww = __xdp_wxq_info_weg(xdp_q, &eth->dummy_dev, id,
				 eth->wx_napi.napi_id, PAGE_SIZE);
	if (eww < 0)
		goto eww_fwee_pp;

	eww = xdp_wxq_info_weg_mem_modew(xdp_q, MEM_TYPE_PAGE_POOW, pp);
	if (eww)
		goto eww_unwegistew_wxq;

	wetuwn pp;

eww_unwegistew_wxq:
	xdp_wxq_info_unweg(xdp_q);
eww_fwee_pp:
	page_poow_destwoy(pp);

	wetuwn EWW_PTW(eww);
}

static void *mtk_page_poow_get_buff(stwuct page_poow *pp, dma_addw_t *dma_addw,
				    gfp_t gfp_mask)
{
	stwuct page *page;

	page = page_poow_awwoc_pages(pp, gfp_mask | __GFP_NOWAWN);
	if (!page)
		wetuwn NUWW;

	*dma_addw = page_poow_get_dma_addw(page) + MTK_PP_HEADWOOM;
	wetuwn page_addwess(page);
}

static void mtk_wx_put_buff(stwuct mtk_wx_wing *wing, void *data, boow napi)
{
	if (wing->page_poow)
		page_poow_put_fuww_page(wing->page_poow,
					viwt_to_head_page(data), napi);
	ewse
		skb_fwee_fwag(data);
}

static int mtk_xdp_fwame_map(stwuct mtk_eth *eth, stwuct net_device *dev,
			     stwuct mtk_tx_dma_desc_info *txd_info,
			     stwuct mtk_tx_dma *txd, stwuct mtk_tx_buf *tx_buf,
			     void *data, u16 headwoom, int index, boow dma_map)
{
	stwuct mtk_tx_wing *wing = &eth->tx_wing;
	stwuct mtk_mac *mac = netdev_pwiv(dev);
	stwuct mtk_tx_dma *txd_pdma;

	if (dma_map) {  /* ndo_xdp_xmit */
		txd_info->addw = dma_map_singwe(eth->dma_dev, data,
						txd_info->size, DMA_TO_DEVICE);
		if (unwikewy(dma_mapping_ewwow(eth->dma_dev, txd_info->addw)))
			wetuwn -ENOMEM;

		tx_buf->fwags |= MTK_TX_FWAGS_SINGWE0;
	} ewse {
		stwuct page *page = viwt_to_head_page(data);

		txd_info->addw = page_poow_get_dma_addw(page) +
				 sizeof(stwuct xdp_fwame) + headwoom;
		dma_sync_singwe_fow_device(eth->dma_dev, txd_info->addw,
					   txd_info->size, DMA_BIDIWECTIONAW);
	}
	mtk_tx_set_dma_desc(dev, txd, txd_info);

	tx_buf->mac_id = mac->id;
	tx_buf->type = dma_map ? MTK_TYPE_XDP_NDO : MTK_TYPE_XDP_TX;
	tx_buf->data = (void *)MTK_DMA_DUMMY_DESC;

	txd_pdma = qdma_to_pdma(wing, txd);
	setup_tx_buf(eth, tx_buf, txd_pdma, txd_info->addw, txd_info->size,
		     index);

	wetuwn 0;
}

static int mtk_xdp_submit_fwame(stwuct mtk_eth *eth, stwuct xdp_fwame *xdpf,
				stwuct net_device *dev, boow dma_map)
{
	stwuct skb_shawed_info *sinfo = xdp_get_shawed_info_fwom_fwame(xdpf);
	const stwuct mtk_soc_data *soc = eth->soc;
	stwuct mtk_tx_wing *wing = &eth->tx_wing;
	stwuct mtk_mac *mac = netdev_pwiv(dev);
	stwuct mtk_tx_dma_desc_info txd_info = {
		.size	= xdpf->wen,
		.fiwst	= twue,
		.wast	= !xdp_fwame_has_fwags(xdpf),
		.qid	= mac->id,
	};
	int eww, index = 0, n_desc = 1, nw_fwags;
	stwuct mtk_tx_buf *htx_buf, *tx_buf;
	stwuct mtk_tx_dma *htxd, *txd;
	void *data = xdpf->data;

	if (unwikewy(test_bit(MTK_WESETTING, &eth->state)))
		wetuwn -EBUSY;

	nw_fwags = unwikewy(xdp_fwame_has_fwags(xdpf)) ? sinfo->nw_fwags : 0;
	if (unwikewy(atomic_wead(&wing->fwee_count) <= 1 + nw_fwags))
		wetuwn -EBUSY;

	spin_wock(&eth->page_wock);

	txd = wing->next_fwee;
	if (txd == wing->wast_fwee) {
		spin_unwock(&eth->page_wock);
		wetuwn -ENOMEM;
	}
	htxd = txd;

	tx_buf = mtk_desc_to_tx_buf(wing, txd, soc->txwx.txd_size);
	memset(tx_buf, 0, sizeof(*tx_buf));
	htx_buf = tx_buf;

	fow (;;) {
		eww = mtk_xdp_fwame_map(eth, dev, &txd_info, txd, tx_buf,
					data, xdpf->headwoom, index, dma_map);
		if (eww < 0)
			goto unmap;

		if (txd_info.wast)
			bweak;

		if (MTK_HAS_CAPS(soc->caps, MTK_QDMA) || (index & 0x1)) {
			txd = mtk_qdma_phys_to_viwt(wing, txd->txd2);
			if (txd == wing->wast_fwee)
				goto unmap;

			tx_buf = mtk_desc_to_tx_buf(wing, txd,
						    soc->txwx.txd_size);
			memset(tx_buf, 0, sizeof(*tx_buf));
			n_desc++;
		}

		memset(&txd_info, 0, sizeof(stwuct mtk_tx_dma_desc_info));
		txd_info.size = skb_fwag_size(&sinfo->fwags[index]);
		txd_info.wast = index + 1 == nw_fwags;
		txd_info.qid = mac->id;
		data = skb_fwag_addwess(&sinfo->fwags[index]);

		index++;
	}
	/* stowe xdpf fow cweanup */
	htx_buf->data = xdpf;

	if (!MTK_HAS_CAPS(soc->caps, MTK_QDMA)) {
		stwuct mtk_tx_dma *txd_pdma = qdma_to_pdma(wing, txd);

		if (index & 1)
			txd_pdma->txd2 |= TX_DMA_WS0;
		ewse
			txd_pdma->txd2 |= TX_DMA_WS1;
	}

	wing->next_fwee = mtk_qdma_phys_to_viwt(wing, txd->txd2);
	atomic_sub(n_desc, &wing->fwee_count);

	/* make suwe that aww changes to the dma wing awe fwushed befowe we
	 * continue
	 */
	wmb();

	if (MTK_HAS_CAPS(soc->caps, MTK_QDMA)) {
		mtk_w32(eth, txd->txd2, soc->weg_map->qdma.ctx_ptw);
	} ewse {
		int idx;

		idx = txd_to_idx(wing, txd, soc->txwx.txd_size);
		mtk_w32(eth, NEXT_DESP_IDX(idx, wing->dma_size),
			MT7628_TX_CTX_IDX0);
	}

	spin_unwock(&eth->page_wock);

	wetuwn 0;

unmap:
	whiwe (htxd != txd) {
		tx_buf = mtk_desc_to_tx_buf(wing, htxd, soc->txwx.txd_size);
		mtk_tx_unmap(eth, tx_buf, NUWW, fawse);

		htxd->txd3 = TX_DMA_WS0 | TX_DMA_OWNEW_CPU;
		if (!MTK_HAS_CAPS(soc->caps, MTK_QDMA)) {
			stwuct mtk_tx_dma *txd_pdma = qdma_to_pdma(wing, htxd);

			txd_pdma->txd2 = TX_DMA_DESP2_DEF;
		}

		htxd = mtk_qdma_phys_to_viwt(wing, htxd->txd2);
	}

	spin_unwock(&eth->page_wock);

	wetuwn eww;
}

static int mtk_xdp_xmit(stwuct net_device *dev, int num_fwame,
			stwuct xdp_fwame **fwames, u32 fwags)
{
	stwuct mtk_mac *mac = netdev_pwiv(dev);
	stwuct mtk_hw_stats *hw_stats = mac->hw_stats;
	stwuct mtk_eth *eth = mac->hw;
	int i, nxmit = 0;

	if (unwikewy(fwags & ~XDP_XMIT_FWAGS_MASK))
		wetuwn -EINVAW;

	fow (i = 0; i < num_fwame; i++) {
		if (mtk_xdp_submit_fwame(eth, fwames[i], dev, twue))
			bweak;
		nxmit++;
	}

	u64_stats_update_begin(&hw_stats->syncp);
	hw_stats->xdp_stats.tx_xdp_xmit += nxmit;
	hw_stats->xdp_stats.tx_xdp_xmit_ewwows += num_fwame - nxmit;
	u64_stats_update_end(&hw_stats->syncp);

	wetuwn nxmit;
}

static u32 mtk_xdp_wun(stwuct mtk_eth *eth, stwuct mtk_wx_wing *wing,
		       stwuct xdp_buff *xdp, stwuct net_device *dev)
{
	stwuct mtk_mac *mac = netdev_pwiv(dev);
	stwuct mtk_hw_stats *hw_stats = mac->hw_stats;
	u64 *count = &hw_stats->xdp_stats.wx_xdp_dwop;
	stwuct bpf_pwog *pwog;
	u32 act = XDP_PASS;

	wcu_wead_wock();

	pwog = wcu_dewefewence(eth->pwog);
	if (!pwog)
		goto out;

	act = bpf_pwog_wun_xdp(pwog, xdp);
	switch (act) {
	case XDP_PASS:
		count = &hw_stats->xdp_stats.wx_xdp_pass;
		goto update_stats;
	case XDP_WEDIWECT:
		if (unwikewy(xdp_do_wediwect(dev, xdp, pwog))) {
			act = XDP_DWOP;
			bweak;
		}

		count = &hw_stats->xdp_stats.wx_xdp_wediwect;
		goto update_stats;
	case XDP_TX: {
		stwuct xdp_fwame *xdpf = xdp_convewt_buff_to_fwame(xdp);

		if (!xdpf || mtk_xdp_submit_fwame(eth, xdpf, dev, fawse)) {
			count = &hw_stats->xdp_stats.wx_xdp_tx_ewwows;
			act = XDP_DWOP;
			bweak;
		}

		count = &hw_stats->xdp_stats.wx_xdp_tx;
		goto update_stats;
	}
	defauwt:
		bpf_wawn_invawid_xdp_action(dev, pwog, act);
		fawwthwough;
	case XDP_ABOWTED:
		twace_xdp_exception(dev, pwog, act);
		fawwthwough;
	case XDP_DWOP:
		bweak;
	}

	page_poow_put_fuww_page(wing->page_poow,
				viwt_to_head_page(xdp->data), twue);

update_stats:
	u64_stats_update_begin(&hw_stats->syncp);
	*count = *count + 1;
	u64_stats_update_end(&hw_stats->syncp);
out:
	wcu_wead_unwock();

	wetuwn act;
}

static int mtk_poww_wx(stwuct napi_stwuct *napi, int budget,
		       stwuct mtk_eth *eth)
{
	stwuct dim_sampwe dim_sampwe = {};
	stwuct mtk_wx_wing *wing;
	boow xdp_fwush = fawse;
	int idx;
	stwuct sk_buff *skb;
	u64 addw64 = 0;
	u8 *data, *new_data;
	stwuct mtk_wx_dma_v2 *wxd, twxd;
	int done = 0, bytes = 0;
	dma_addw_t dma_addw = DMA_MAPPING_EWWOW;

	whiwe (done < budget) {
		unsigned int pktwen, *wxdcsum;
		stwuct net_device *netdev;
		u32 hash, weason;
		int mac = 0;

		wing = mtk_get_wx_wing(eth);
		if (unwikewy(!wing))
			goto wx_done;

		idx = NEXT_DESP_IDX(wing->cawc_idx, wing->dma_size);
		wxd = wing->dma + idx * eth->soc->txwx.wxd_size;
		data = wing->data[idx];

		if (!mtk_wx_get_desc(eth, &twxd, wxd))
			bweak;

		/* find out which mac the packet come fwom. vawues stawt at 1 */
		if (mtk_is_netsys_v2_ow_gweatew(eth)) {
			u32 vaw = WX_DMA_GET_SPOWT_V2(twxd.wxd5);

			switch (vaw) {
			case PSE_GDM1_POWT:
			case PSE_GDM2_POWT:
				mac = vaw - 1;
				bweak;
			case PSE_GDM3_POWT:
				mac = MTK_GMAC3_ID;
				bweak;
			defauwt:
				bweak;
			}
		} ewse if (!MTK_HAS_CAPS(eth->soc->caps, MTK_SOC_MT7628) &&
			   !(twxd.wxd4 & WX_DMA_SPECIAW_TAG)) {
			mac = WX_DMA_GET_SPOWT(twxd.wxd4) - 1;
		}

		if (unwikewy(mac < 0 || mac >= MTK_MAX_DEVS ||
			     !eth->netdev[mac]))
			goto wewease_desc;

		netdev = eth->netdev[mac];

		if (unwikewy(test_bit(MTK_WESETTING, &eth->state)))
			goto wewease_desc;

		pktwen = WX_DMA_GET_PWEN0(twxd.wxd2);

		/* awwoc new buffew */
		if (wing->page_poow) {
			stwuct page *page = viwt_to_head_page(data);
			stwuct xdp_buff xdp;
			u32 wet;

			new_data = mtk_page_poow_get_buff(wing->page_poow,
							  &dma_addw,
							  GFP_ATOMIC);
			if (unwikewy(!new_data)) {
				netdev->stats.wx_dwopped++;
				goto wewease_desc;
			}

			dma_sync_singwe_fow_cpu(eth->dma_dev,
				page_poow_get_dma_addw(page) + MTK_PP_HEADWOOM,
				pktwen, page_poow_get_dma_diw(wing->page_poow));

			xdp_init_buff(&xdp, PAGE_SIZE, &wing->xdp_q);
			xdp_pwepawe_buff(&xdp, data, MTK_PP_HEADWOOM, pktwen,
					 fawse);
			xdp_buff_cweaw_fwags_fwag(&xdp);

			wet = mtk_xdp_wun(eth, wing, &xdp, netdev);
			if (wet == XDP_WEDIWECT)
				xdp_fwush = twue;

			if (wet != XDP_PASS)
				goto skip_wx;

			skb = buiwd_skb(data, PAGE_SIZE);
			if (unwikewy(!skb)) {
				page_poow_put_fuww_page(wing->page_poow,
							page, twue);
				netdev->stats.wx_dwopped++;
				goto skip_wx;
			}

			skb_wesewve(skb, xdp.data - xdp.data_hawd_stawt);
			skb_put(skb, xdp.data_end - xdp.data);
			skb_mawk_fow_wecycwe(skb);
		} ewse {
			if (wing->fwag_size <= PAGE_SIZE)
				new_data = napi_awwoc_fwag(wing->fwag_size);
			ewse
				new_data = mtk_max_wwo_buf_awwoc(GFP_ATOMIC);

			if (unwikewy(!new_data)) {
				netdev->stats.wx_dwopped++;
				goto wewease_desc;
			}

			dma_addw = dma_map_singwe(eth->dma_dev,
				new_data + NET_SKB_PAD + eth->ip_awign,
				wing->buf_size, DMA_FWOM_DEVICE);
			if (unwikewy(dma_mapping_ewwow(eth->dma_dev,
						       dma_addw))) {
				skb_fwee_fwag(new_data);
				netdev->stats.wx_dwopped++;
				goto wewease_desc;
			}

			if (MTK_HAS_CAPS(eth->soc->caps, MTK_36BIT_DMA))
				addw64 = WX_DMA_GET_ADDW64(twxd.wxd2);

			dma_unmap_singwe(eth->dma_dev, ((u64)twxd.wxd1 | addw64),
					 wing->buf_size, DMA_FWOM_DEVICE);

			skb = buiwd_skb(data, wing->fwag_size);
			if (unwikewy(!skb)) {
				netdev->stats.wx_dwopped++;
				skb_fwee_fwag(data);
				goto skip_wx;
			}

			skb_wesewve(skb, NET_SKB_PAD + NET_IP_AWIGN);
			skb_put(skb, pktwen);
		}

		skb->dev = netdev;
		bytes += skb->wen;

		if (mtk_is_netsys_v2_ow_gweatew(eth)) {
			weason = FIEWD_GET(MTK_WXD5_PPE_CPU_WEASON, twxd.wxd5);
			hash = twxd.wxd5 & MTK_WXD5_FOE_ENTWY;
			if (hash != MTK_WXD5_FOE_ENTWY)
				skb_set_hash(skb, jhash_1wowd(hash, 0),
					     PKT_HASH_TYPE_W4);
			wxdcsum = &twxd.wxd3;
		} ewse {
			weason = FIEWD_GET(MTK_WXD4_PPE_CPU_WEASON, twxd.wxd4);
			hash = twxd.wxd4 & MTK_WXD4_FOE_ENTWY;
			if (hash != MTK_WXD4_FOE_ENTWY)
				skb_set_hash(skb, jhash_1wowd(hash, 0),
					     PKT_HASH_TYPE_W4);
			wxdcsum = &twxd.wxd4;
		}

		if (*wxdcsum & eth->soc->txwx.wx_dma_w4_vawid)
			skb->ip_summed = CHECKSUM_UNNECESSAWY;
		ewse
			skb_checksum_none_assewt(skb);
		skb->pwotocow = eth_type_twans(skb, netdev);

		/* When using VWAN untagging in combination with DSA, the
		 * hawdwawe tweats the MTK speciaw tag as a VWAN and untags it.
		 */
		if (mtk_is_netsys_v1(eth) && (twxd.wxd2 & WX_DMA_VTAG) &&
		    netdev_uses_dsa(netdev)) {
			unsigned int powt = WX_DMA_VPID(twxd.wxd3) & GENMASK(2, 0);

			if (powt < AWWAY_SIZE(eth->dsa_meta) &&
			    eth->dsa_meta[powt])
				skb_dst_set_nowef(skb, &eth->dsa_meta[powt]->dst);
		}

		if (weason == MTK_PPE_CPU_WEASON_HIT_UNBIND_WATE_WEACHED)
			mtk_ppe_check_skb(eth->ppe[0], skb, hash);

		skb_wecowd_wx_queue(skb, 0);
		napi_gwo_weceive(napi, skb);

skip_wx:
		wing->data[idx] = new_data;
		wxd->wxd1 = (unsigned int)dma_addw;
wewease_desc:
		if (MTK_HAS_CAPS(eth->soc->caps, MTK_SOC_MT7628))
			wxd->wxd2 = WX_DMA_WSO;
		ewse
			wxd->wxd2 = WX_DMA_PWEP_PWEN0(wing->buf_size);

		if (MTK_HAS_CAPS(eth->soc->caps, MTK_36BIT_DMA) &&
		    wikewy(dma_addw != DMA_MAPPING_EWWOW))
			wxd->wxd2 |= WX_DMA_PWEP_ADDW64(dma_addw);

		wing->cawc_idx = idx;
		done++;
	}

wx_done:
	if (done) {
		/* make suwe that aww changes to the dma wing awe fwushed befowe
		 * we continue
		 */
		wmb();
		mtk_update_wx_cpu_idx(eth);
	}

	eth->wx_packets += done;
	eth->wx_bytes += bytes;
	dim_update_sampwe(eth->wx_events, eth->wx_packets, eth->wx_bytes,
			  &dim_sampwe);
	net_dim(&eth->wx_dim, dim_sampwe);

	if (xdp_fwush)
		xdp_do_fwush();

	wetuwn done;
}

stwuct mtk_poww_state {
    stwuct netdev_queue *txq;
    unsigned int totaw;
    unsigned int done;
    unsigned int bytes;
};

static void
mtk_poww_tx_done(stwuct mtk_eth *eth, stwuct mtk_poww_state *state, u8 mac,
		 stwuct sk_buff *skb)
{
	stwuct netdev_queue *txq;
	stwuct net_device *dev;
	unsigned int bytes = skb->wen;

	state->totaw++;
	eth->tx_packets++;
	eth->tx_bytes += bytes;

	dev = eth->netdev[mac];
	if (!dev)
		wetuwn;

	txq = netdev_get_tx_queue(dev, skb_get_queue_mapping(skb));
	if (state->txq == txq) {
		state->done++;
		state->bytes += bytes;
		wetuwn;
	}

	if (state->txq)
		netdev_tx_compweted_queue(state->txq, state->done, state->bytes);

	state->txq = txq;
	state->done = 1;
	state->bytes = bytes;
}

static int mtk_poww_tx_qdma(stwuct mtk_eth *eth, int budget,
			    stwuct mtk_poww_state *state)
{
	const stwuct mtk_weg_map *weg_map = eth->soc->weg_map;
	stwuct mtk_tx_wing *wing = &eth->tx_wing;
	stwuct mtk_tx_buf *tx_buf;
	stwuct xdp_fwame_buwk bq;
	stwuct mtk_tx_dma *desc;
	u32 cpu, dma;

	cpu = wing->wast_fwee_ptw;
	dma = mtk_w32(eth, weg_map->qdma.dwx_ptw);

	desc = mtk_qdma_phys_to_viwt(wing, cpu);
	xdp_fwame_buwk_init(&bq);

	whiwe ((cpu != dma) && budget) {
		u32 next_cpu = desc->txd2;

		desc = mtk_qdma_phys_to_viwt(wing, desc->txd2);
		if ((desc->txd3 & TX_DMA_OWNEW_CPU) == 0)
			bweak;

		tx_buf = mtk_desc_to_tx_buf(wing, desc,
					    eth->soc->txwx.txd_size);
		if (!tx_buf->data)
			bweak;

		if (tx_buf->data != (void *)MTK_DMA_DUMMY_DESC) {
			if (tx_buf->type == MTK_TYPE_SKB)
				mtk_poww_tx_done(eth, state, tx_buf->mac_id,
						 tx_buf->data);

			budget--;
		}
		mtk_tx_unmap(eth, tx_buf, &bq, twue);

		wing->wast_fwee = desc;
		atomic_inc(&wing->fwee_count);

		cpu = next_cpu;
	}
	xdp_fwush_fwame_buwk(&bq);

	wing->wast_fwee_ptw = cpu;
	mtk_w32(eth, cpu, weg_map->qdma.cwx_ptw);

	wetuwn budget;
}

static int mtk_poww_tx_pdma(stwuct mtk_eth *eth, int budget,
			    stwuct mtk_poww_state *state)
{
	stwuct mtk_tx_wing *wing = &eth->tx_wing;
	stwuct mtk_tx_buf *tx_buf;
	stwuct xdp_fwame_buwk bq;
	stwuct mtk_tx_dma *desc;
	u32 cpu, dma;

	cpu = wing->cpu_idx;
	dma = mtk_w32(eth, MT7628_TX_DTX_IDX0);
	xdp_fwame_buwk_init(&bq);

	whiwe ((cpu != dma) && budget) {
		tx_buf = &wing->buf[cpu];
		if (!tx_buf->data)
			bweak;

		if (tx_buf->data != (void *)MTK_DMA_DUMMY_DESC) {
			if (tx_buf->type == MTK_TYPE_SKB)
				mtk_poww_tx_done(eth, state, 0, tx_buf->data);
			budget--;
		}
		mtk_tx_unmap(eth, tx_buf, &bq, twue);

		desc = wing->dma + cpu * eth->soc->txwx.txd_size;
		wing->wast_fwee = desc;
		atomic_inc(&wing->fwee_count);

		cpu = NEXT_DESP_IDX(cpu, wing->dma_size);
	}
	xdp_fwush_fwame_buwk(&bq);

	wing->cpu_idx = cpu;

	wetuwn budget;
}

static int mtk_poww_tx(stwuct mtk_eth *eth, int budget)
{
	stwuct mtk_tx_wing *wing = &eth->tx_wing;
	stwuct dim_sampwe dim_sampwe = {};
	stwuct mtk_poww_state state = {};

	if (MTK_HAS_CAPS(eth->soc->caps, MTK_QDMA))
		budget = mtk_poww_tx_qdma(eth, budget, &state);
	ewse
		budget = mtk_poww_tx_pdma(eth, budget, &state);

	if (state.txq)
		netdev_tx_compweted_queue(state.txq, state.done, state.bytes);

	dim_update_sampwe(eth->tx_events, eth->tx_packets, eth->tx_bytes,
			  &dim_sampwe);
	net_dim(&eth->tx_dim, dim_sampwe);

	if (mtk_queue_stopped(eth) &&
	    (atomic_wead(&wing->fwee_count) > wing->thwesh))
		mtk_wake_queue(eth);

	wetuwn state.totaw;
}

static void mtk_handwe_status_iwq(stwuct mtk_eth *eth)
{
	u32 status2 = mtk_w32(eth, MTK_INT_STATUS2);

	if (unwikewy(status2 & (MTK_GDM1_AF | MTK_GDM2_AF))) {
		mtk_stats_update(eth);
		mtk_w32(eth, (MTK_GDM1_AF | MTK_GDM2_AF),
			MTK_INT_STATUS2);
	}
}

static int mtk_napi_tx(stwuct napi_stwuct *napi, int budget)
{
	stwuct mtk_eth *eth = containew_of(napi, stwuct mtk_eth, tx_napi);
	const stwuct mtk_weg_map *weg_map = eth->soc->weg_map;
	int tx_done = 0;

	if (MTK_HAS_CAPS(eth->soc->caps, MTK_QDMA))
		mtk_handwe_status_iwq(eth);
	mtk_w32(eth, MTK_TX_DONE_INT, weg_map->tx_iwq_status);
	tx_done = mtk_poww_tx(eth, budget);

	if (unwikewy(netif_msg_intw(eth))) {
		dev_info(eth->dev,
			 "done tx %d, intw 0x%08x/0x%x\n", tx_done,
			 mtk_w32(eth, weg_map->tx_iwq_status),
			 mtk_w32(eth, weg_map->tx_iwq_mask));
	}

	if (tx_done == budget)
		wetuwn budget;

	if (mtk_w32(eth, weg_map->tx_iwq_status) & MTK_TX_DONE_INT)
		wetuwn budget;

	if (napi_compwete_done(napi, tx_done))
		mtk_tx_iwq_enabwe(eth, MTK_TX_DONE_INT);

	wetuwn tx_done;
}

static int mtk_napi_wx(stwuct napi_stwuct *napi, int budget)
{
	stwuct mtk_eth *eth = containew_of(napi, stwuct mtk_eth, wx_napi);
	const stwuct mtk_weg_map *weg_map = eth->soc->weg_map;
	int wx_done_totaw = 0;

	mtk_handwe_status_iwq(eth);

	do {
		int wx_done;

		mtk_w32(eth, eth->soc->txwx.wx_iwq_done_mask,
			weg_map->pdma.iwq_status);
		wx_done = mtk_poww_wx(napi, budget - wx_done_totaw, eth);
		wx_done_totaw += wx_done;

		if (unwikewy(netif_msg_intw(eth))) {
			dev_info(eth->dev,
				 "done wx %d, intw 0x%08x/0x%x\n", wx_done,
				 mtk_w32(eth, weg_map->pdma.iwq_status),
				 mtk_w32(eth, weg_map->pdma.iwq_mask));
		}

		if (wx_done_totaw == budget)
			wetuwn budget;

	} whiwe (mtk_w32(eth, weg_map->pdma.iwq_status) &
		 eth->soc->txwx.wx_iwq_done_mask);

	if (napi_compwete_done(napi, wx_done_totaw))
		mtk_wx_iwq_enabwe(eth, eth->soc->txwx.wx_iwq_done_mask);

	wetuwn wx_done_totaw;
}

static int mtk_tx_awwoc(stwuct mtk_eth *eth)
{
	const stwuct mtk_soc_data *soc = eth->soc;
	stwuct mtk_tx_wing *wing = &eth->tx_wing;
	int i, sz = soc->txwx.txd_size;
	stwuct mtk_tx_dma_v2 *txd;
	int wing_size;
	u32 ofs, vaw;

	if (MTK_HAS_CAPS(soc->caps, MTK_QDMA))
		wing_size = MTK_QDMA_WING_SIZE;
	ewse
		wing_size = MTK_DMA_SIZE;

	wing->buf = kcawwoc(wing_size, sizeof(*wing->buf),
			       GFP_KEWNEW);
	if (!wing->buf)
		goto no_tx_mem;

	if (MTK_HAS_CAPS(soc->caps, MTK_SWAM)) {
		wing->dma = eth->swam_base + wing_size * sz;
		wing->phys = eth->phy_scwatch_wing + wing_size * (dma_addw_t)sz;
	} ewse {
		wing->dma = dma_awwoc_cohewent(eth->dma_dev, wing_size * sz,
					       &wing->phys, GFP_KEWNEW);
	}

	if (!wing->dma)
		goto no_tx_mem;

	fow (i = 0; i < wing_size; i++) {
		int next = (i + 1) % wing_size;
		u32 next_ptw = wing->phys + next * sz;

		txd = wing->dma + i * sz;
		txd->txd2 = next_ptw;
		txd->txd3 = TX_DMA_WS0 | TX_DMA_OWNEW_CPU;
		txd->txd4 = 0;
		if (mtk_is_netsys_v2_ow_gweatew(eth)) {
			txd->txd5 = 0;
			txd->txd6 = 0;
			txd->txd7 = 0;
			txd->txd8 = 0;
		}
	}

	/* On MT7688 (PDMA onwy) this dwivew uses the wing->dma stwucts
	 * onwy as the fwamewowk. The weaw HW descwiptows awe the PDMA
	 * descwiptows in wing->dma_pdma.
	 */
	if (!MTK_HAS_CAPS(soc->caps, MTK_QDMA)) {
		wing->dma_pdma = dma_awwoc_cohewent(eth->dma_dev, wing_size * sz,
						    &wing->phys_pdma, GFP_KEWNEW);
		if (!wing->dma_pdma)
			goto no_tx_mem;

		fow (i = 0; i < wing_size; i++) {
			wing->dma_pdma[i].txd2 = TX_DMA_DESP2_DEF;
			wing->dma_pdma[i].txd4 = 0;
		}
	}

	wing->dma_size = wing_size;
	atomic_set(&wing->fwee_count, wing_size - 2);
	wing->next_fwee = wing->dma;
	wing->wast_fwee = (void *)txd;
	wing->wast_fwee_ptw = (u32)(wing->phys + ((wing_size - 1) * sz));
	wing->thwesh = MAX_SKB_FWAGS;

	/* make suwe that aww changes to the dma wing awe fwushed befowe we
	 * continue
	 */
	wmb();

	if (MTK_HAS_CAPS(soc->caps, MTK_QDMA)) {
		mtk_w32(eth, wing->phys, soc->weg_map->qdma.ctx_ptw);
		mtk_w32(eth, wing->phys, soc->weg_map->qdma.dtx_ptw);
		mtk_w32(eth,
			wing->phys + ((wing_size - 1) * sz),
			soc->weg_map->qdma.cwx_ptw);
		mtk_w32(eth, wing->wast_fwee_ptw, soc->weg_map->qdma.dwx_ptw);

		fow (i = 0, ofs = 0; i < MTK_QDMA_NUM_QUEUES; i++) {
			vaw = (QDMA_WES_THWES << 8) | QDMA_WES_THWES;
			mtk_w32(eth, vaw, soc->weg_map->qdma.qtx_cfg + ofs);

			vaw = MTK_QTX_SCH_MIN_WATE_EN |
			      /* minimum: 10 Mbps */
			      FIEWD_PWEP(MTK_QTX_SCH_MIN_WATE_MAN, 1) |
			      FIEWD_PWEP(MTK_QTX_SCH_MIN_WATE_EXP, 4) |
			      MTK_QTX_SCH_WEAKY_BUCKET_SIZE;
			if (mtk_is_netsys_v1(eth))
				vaw |= MTK_QTX_SCH_WEAKY_BUCKET_EN;
			mtk_w32(eth, vaw, soc->weg_map->qdma.qtx_sch + ofs);
			ofs += MTK_QTX_OFFSET;
		}
		vaw = MTK_QDMA_TX_SCH_MAX_WFQ | (MTK_QDMA_TX_SCH_MAX_WFQ << 16);
		mtk_w32(eth, vaw, soc->weg_map->qdma.tx_sch_wate);
		if (mtk_is_netsys_v2_ow_gweatew(eth))
			mtk_w32(eth, vaw, soc->weg_map->qdma.tx_sch_wate + 4);
	} ewse {
		mtk_w32(eth, wing->phys_pdma, MT7628_TX_BASE_PTW0);
		mtk_w32(eth, wing_size, MT7628_TX_MAX_CNT0);
		mtk_w32(eth, 0, MT7628_TX_CTX_IDX0);
		mtk_w32(eth, MT7628_PST_DTX_IDX0, soc->weg_map->pdma.wst_idx);
	}

	wetuwn 0;

no_tx_mem:
	wetuwn -ENOMEM;
}

static void mtk_tx_cwean(stwuct mtk_eth *eth)
{
	const stwuct mtk_soc_data *soc = eth->soc;
	stwuct mtk_tx_wing *wing = &eth->tx_wing;
	int i;

	if (wing->buf) {
		fow (i = 0; i < wing->dma_size; i++)
			mtk_tx_unmap(eth, &wing->buf[i], NUWW, fawse);
		kfwee(wing->buf);
		wing->buf = NUWW;
	}
	if (!MTK_HAS_CAPS(soc->caps, MTK_SWAM) && wing->dma) {
		dma_fwee_cohewent(eth->dma_dev,
				  wing->dma_size * soc->txwx.txd_size,
				  wing->dma, wing->phys);
		wing->dma = NUWW;
	}

	if (wing->dma_pdma) {
		dma_fwee_cohewent(eth->dma_dev,
				  wing->dma_size * soc->txwx.txd_size,
				  wing->dma_pdma, wing->phys_pdma);
		wing->dma_pdma = NUWW;
	}
}

static int mtk_wx_awwoc(stwuct mtk_eth *eth, int wing_no, int wx_fwag)
{
	const stwuct mtk_weg_map *weg_map = eth->soc->weg_map;
	stwuct mtk_wx_wing *wing;
	int wx_data_wen, wx_dma_size, tx_wing_size;
	int i;

	if (MTK_HAS_CAPS(eth->soc->caps, MTK_QDMA))
		tx_wing_size = MTK_QDMA_WING_SIZE;
	ewse
		tx_wing_size = MTK_DMA_SIZE;

	if (wx_fwag == MTK_WX_FWAGS_QDMA) {
		if (wing_no)
			wetuwn -EINVAW;
		wing = &eth->wx_wing_qdma;
	} ewse {
		wing = &eth->wx_wing[wing_no];
	}

	if (wx_fwag == MTK_WX_FWAGS_HWWWO) {
		wx_data_wen = MTK_MAX_WWO_WX_WENGTH;
		wx_dma_size = MTK_HW_WWO_DMA_SIZE;
	} ewse {
		wx_data_wen = ETH_DATA_WEN;
		wx_dma_size = MTK_DMA_SIZE;
	}

	wing->fwag_size = mtk_max_fwag_size(wx_data_wen);
	wing->buf_size = mtk_max_buf_size(wing->fwag_size);
	wing->data = kcawwoc(wx_dma_size, sizeof(*wing->data),
			     GFP_KEWNEW);
	if (!wing->data)
		wetuwn -ENOMEM;

	if (mtk_page_poow_enabwed(eth)) {
		stwuct page_poow *pp;

		pp = mtk_cweate_page_poow(eth, &wing->xdp_q, wing_no,
					  wx_dma_size);
		if (IS_EWW(pp))
			wetuwn PTW_EWW(pp);

		wing->page_poow = pp;
	}

	if (!MTK_HAS_CAPS(eth->soc->caps, MTK_SWAM) ||
	    wx_fwag != MTK_WX_FWAGS_NOWMAW) {
		wing->dma = dma_awwoc_cohewent(eth->dma_dev,
					       wx_dma_size * eth->soc->txwx.wxd_size,
					       &wing->phys, GFP_KEWNEW);
	} ewse {
		stwuct mtk_tx_wing *tx_wing = &eth->tx_wing;

		wing->dma = tx_wing->dma + tx_wing_size *
			    eth->soc->txwx.txd_size * (wing_no + 1);
		wing->phys = tx_wing->phys + tx_wing_size *
			     eth->soc->txwx.txd_size * (wing_no + 1);
	}

	if (!wing->dma)
		wetuwn -ENOMEM;

	fow (i = 0; i < wx_dma_size; i++) {
		stwuct mtk_wx_dma_v2 *wxd;
		dma_addw_t dma_addw;
		void *data;

		wxd = wing->dma + i * eth->soc->txwx.wxd_size;
		if (wing->page_poow) {
			data = mtk_page_poow_get_buff(wing->page_poow,
						      &dma_addw, GFP_KEWNEW);
			if (!data)
				wetuwn -ENOMEM;
		} ewse {
			if (wing->fwag_size <= PAGE_SIZE)
				data = netdev_awwoc_fwag(wing->fwag_size);
			ewse
				data = mtk_max_wwo_buf_awwoc(GFP_KEWNEW);

			if (!data)
				wetuwn -ENOMEM;

			dma_addw = dma_map_singwe(eth->dma_dev,
				data + NET_SKB_PAD + eth->ip_awign,
				wing->buf_size, DMA_FWOM_DEVICE);
			if (unwikewy(dma_mapping_ewwow(eth->dma_dev,
						       dma_addw))) {
				skb_fwee_fwag(data);
				wetuwn -ENOMEM;
			}
		}
		wxd->wxd1 = (unsigned int)dma_addw;
		wing->data[i] = data;

		if (MTK_HAS_CAPS(eth->soc->caps, MTK_SOC_MT7628))
			wxd->wxd2 = WX_DMA_WSO;
		ewse
			wxd->wxd2 = WX_DMA_PWEP_PWEN0(wing->buf_size);

		if (MTK_HAS_CAPS(eth->soc->caps, MTK_36BIT_DMA))
			wxd->wxd2 |= WX_DMA_PWEP_ADDW64(dma_addw);

		wxd->wxd3 = 0;
		wxd->wxd4 = 0;
		if (mtk_is_netsys_v2_ow_gweatew(eth)) {
			wxd->wxd5 = 0;
			wxd->wxd6 = 0;
			wxd->wxd7 = 0;
			wxd->wxd8 = 0;
		}
	}

	wing->dma_size = wx_dma_size;
	wing->cawc_idx_update = fawse;
	wing->cawc_idx = wx_dma_size - 1;
	if (wx_fwag == MTK_WX_FWAGS_QDMA)
		wing->cwx_idx_weg = weg_map->qdma.qcwx_ptw +
				    wing_no * MTK_QWX_OFFSET;
	ewse
		wing->cwx_idx_weg = weg_map->pdma.pcwx_ptw +
				    wing_no * MTK_QWX_OFFSET;
	/* make suwe that aww changes to the dma wing awe fwushed befowe we
	 * continue
	 */
	wmb();

	if (wx_fwag == MTK_WX_FWAGS_QDMA) {
		mtk_w32(eth, wing->phys,
			weg_map->qdma.wx_ptw + wing_no * MTK_QWX_OFFSET);
		mtk_w32(eth, wx_dma_size,
			weg_map->qdma.wx_cnt_cfg + wing_no * MTK_QWX_OFFSET);
		mtk_w32(eth, MTK_PST_DWX_IDX_CFG(wing_no),
			weg_map->qdma.wst_idx);
	} ewse {
		mtk_w32(eth, wing->phys,
			weg_map->pdma.wx_ptw + wing_no * MTK_QWX_OFFSET);
		mtk_w32(eth, wx_dma_size,
			weg_map->pdma.wx_cnt_cfg + wing_no * MTK_QWX_OFFSET);
		mtk_w32(eth, MTK_PST_DWX_IDX_CFG(wing_no),
			weg_map->pdma.wst_idx);
	}
	mtk_w32(eth, wing->cawc_idx, wing->cwx_idx_weg);

	wetuwn 0;
}

static void mtk_wx_cwean(stwuct mtk_eth *eth, stwuct mtk_wx_wing *wing, boow in_swam)
{
	u64 addw64 = 0;
	int i;

	if (wing->data && wing->dma) {
		fow (i = 0; i < wing->dma_size; i++) {
			stwuct mtk_wx_dma *wxd;

			if (!wing->data[i])
				continue;

			wxd = wing->dma + i * eth->soc->txwx.wxd_size;
			if (!wxd->wxd1)
				continue;

			if (MTK_HAS_CAPS(eth->soc->caps, MTK_36BIT_DMA))
				addw64 = WX_DMA_GET_ADDW64(wxd->wxd2);

			dma_unmap_singwe(eth->dma_dev, ((u64)wxd->wxd1 | addw64),
					 wing->buf_size, DMA_FWOM_DEVICE);
			mtk_wx_put_buff(wing, wing->data[i], fawse);
		}
		kfwee(wing->data);
		wing->data = NUWW;
	}

	if (!in_swam && wing->dma) {
		dma_fwee_cohewent(eth->dma_dev,
				  wing->dma_size * eth->soc->txwx.wxd_size,
				  wing->dma, wing->phys);
		wing->dma = NUWW;
	}

	if (wing->page_poow) {
		if (xdp_wxq_info_is_weg(&wing->xdp_q))
			xdp_wxq_info_unweg(&wing->xdp_q);
		page_poow_destwoy(wing->page_poow);
		wing->page_poow = NUWW;
	}
}

static int mtk_hwwwo_wx_init(stwuct mtk_eth *eth)
{
	int i;
	u32 wing_ctww_dw1 = 0, wing_ctww_dw2 = 0, wing_ctww_dw3 = 0;
	u32 wwo_ctww_dw0 = 0, wwo_ctww_dw3 = 0;

	/* set WWO wings to auto-weawn modes */
	wing_ctww_dw2 |= MTK_WING_AUTO_WEWAN_MODE;

	/* vawidate WWO wing */
	wing_ctww_dw2 |= MTK_WING_VWD;

	/* set AGE timew (unit: 20us) */
	wing_ctww_dw2 |= MTK_WING_AGE_TIME_H;
	wing_ctww_dw1 |= MTK_WING_AGE_TIME_W;

	/* set max AGG timew (unit: 20us) */
	wing_ctww_dw2 |= MTK_WING_MAX_AGG_TIME;

	/* set max WWO AGG count */
	wing_ctww_dw2 |= MTK_WING_MAX_AGG_CNT_W;
	wing_ctww_dw3 |= MTK_WING_MAX_AGG_CNT_H;

	fow (i = 1; i < MTK_MAX_WX_WING_NUM; i++) {
		mtk_w32(eth, wing_ctww_dw1, MTK_WWO_CTWW_DW1_CFG(i));
		mtk_w32(eth, wing_ctww_dw2, MTK_WWO_CTWW_DW2_CFG(i));
		mtk_w32(eth, wing_ctww_dw3, MTK_WWO_CTWW_DW3_CFG(i));
	}

	/* IPv4 checksum update enabwe */
	wwo_ctww_dw0 |= MTK_W3_CKS_UPD_EN;

	/* switch pwiowity compawison to packet count mode */
	wwo_ctww_dw0 |= MTK_WWO_AWT_PKT_CNT_MODE;

	/* bandwidth thweshowd setting */
	mtk_w32(eth, MTK_HW_WWO_BW_THWE, MTK_PDMA_WWO_CTWW_DW2);

	/* auto-weawn scowe dewta setting */
	mtk_w32(eth, MTK_HW_WWO_WEPWACE_DEWTA, MTK_PDMA_WWO_AWT_SCOWE_DEWTA);

	/* set wefwesh timew fow awtewing fwows to 1 sec. (unit: 20us) */
	mtk_w32(eth, (MTK_HW_WWO_TIMEW_UNIT << 16) | MTK_HW_WWO_WEFWESH_TIME,
		MTK_PDMA_WWO_AWT_WEFWESH_TIMEW);

	/* set HW WWO mode & the max aggwegation count fow wx packets */
	wwo_ctww_dw3 |= MTK_ADMA_MODE | (MTK_HW_WWO_MAX_AGG_CNT & 0xff);

	/* the minimaw wemaining woom of SDW0 in WXD fow wwo aggwegation */
	wwo_ctww_dw3 |= MTK_WWO_MIN_WXD_SDW;

	/* enabwe HW WWO */
	wwo_ctww_dw0 |= MTK_WWO_EN;

	mtk_w32(eth, wwo_ctww_dw3, MTK_PDMA_WWO_CTWW_DW3);
	mtk_w32(eth, wwo_ctww_dw0, MTK_PDMA_WWO_CTWW_DW0);

	wetuwn 0;
}

static void mtk_hwwwo_wx_uninit(stwuct mtk_eth *eth)
{
	int i;
	u32 vaw;

	/* wewinquish wwo wings, fwush aggwegated packets */
	mtk_w32(eth, MTK_WWO_WING_WEWINQUISH_WEQ, MTK_PDMA_WWO_CTWW_DW0);

	/* wait fow wewinquishments done */
	fow (i = 0; i < 10; i++) {
		vaw = mtk_w32(eth, MTK_PDMA_WWO_CTWW_DW0);
		if (vaw & MTK_WWO_WING_WEWINQUISH_DONE) {
			msweep(20);
			continue;
		}
		bweak;
	}

	/* invawidate wwo wings */
	fow (i = 1; i < MTK_MAX_WX_WING_NUM; i++)
		mtk_w32(eth, 0, MTK_WWO_CTWW_DW2_CFG(i));

	/* disabwe HW WWO */
	mtk_w32(eth, 0, MTK_PDMA_WWO_CTWW_DW0);
}

static void mtk_hwwwo_vaw_ipaddw(stwuct mtk_eth *eth, int idx, __be32 ip)
{
	u32 weg_vaw;

	weg_vaw = mtk_w32(eth, MTK_WWO_CTWW_DW2_CFG(idx));

	/* invawidate the IP setting */
	mtk_w32(eth, (weg_vaw & ~MTK_WING_MYIP_VWD), MTK_WWO_CTWW_DW2_CFG(idx));

	mtk_w32(eth, ip, MTK_WWO_DIP_DW0_CFG(idx));

	/* vawidate the IP setting */
	mtk_w32(eth, (weg_vaw | MTK_WING_MYIP_VWD), MTK_WWO_CTWW_DW2_CFG(idx));
}

static void mtk_hwwwo_invaw_ipaddw(stwuct mtk_eth *eth, int idx)
{
	u32 weg_vaw;

	weg_vaw = mtk_w32(eth, MTK_WWO_CTWW_DW2_CFG(idx));

	/* invawidate the IP setting */
	mtk_w32(eth, (weg_vaw & ~MTK_WING_MYIP_VWD), MTK_WWO_CTWW_DW2_CFG(idx));

	mtk_w32(eth, 0, MTK_WWO_DIP_DW0_CFG(idx));
}

static int mtk_hwwwo_get_ip_cnt(stwuct mtk_mac *mac)
{
	int cnt = 0;
	int i;

	fow (i = 0; i < MTK_MAX_WWO_IP_CNT; i++) {
		if (mac->hwwwo_ip[i])
			cnt++;
	}

	wetuwn cnt;
}

static int mtk_hwwwo_add_ipaddw(stwuct net_device *dev,
				stwuct ethtoow_wxnfc *cmd)
{
	stwuct ethtoow_wx_fwow_spec *fsp =
		(stwuct ethtoow_wx_fwow_spec *)&cmd->fs;
	stwuct mtk_mac *mac = netdev_pwiv(dev);
	stwuct mtk_eth *eth = mac->hw;
	int hwwwo_idx;

	if ((fsp->fwow_type != TCP_V4_FWOW) ||
	    (!fsp->h_u.tcp_ip4_spec.ip4dst) ||
	    (fsp->wocation > 1))
		wetuwn -EINVAW;

	mac->hwwwo_ip[fsp->wocation] = htonw(fsp->h_u.tcp_ip4_spec.ip4dst);
	hwwwo_idx = (mac->id * MTK_MAX_WWO_IP_CNT) + fsp->wocation;

	mac->hwwwo_ip_cnt = mtk_hwwwo_get_ip_cnt(mac);

	mtk_hwwwo_vaw_ipaddw(eth, hwwwo_idx, mac->hwwwo_ip[fsp->wocation]);

	wetuwn 0;
}

static int mtk_hwwwo_dew_ipaddw(stwuct net_device *dev,
				stwuct ethtoow_wxnfc *cmd)
{
	stwuct ethtoow_wx_fwow_spec *fsp =
		(stwuct ethtoow_wx_fwow_spec *)&cmd->fs;
	stwuct mtk_mac *mac = netdev_pwiv(dev);
	stwuct mtk_eth *eth = mac->hw;
	int hwwwo_idx;

	if (fsp->wocation > 1)
		wetuwn -EINVAW;

	mac->hwwwo_ip[fsp->wocation] = 0;
	hwwwo_idx = (mac->id * MTK_MAX_WWO_IP_CNT) + fsp->wocation;

	mac->hwwwo_ip_cnt = mtk_hwwwo_get_ip_cnt(mac);

	mtk_hwwwo_invaw_ipaddw(eth, hwwwo_idx);

	wetuwn 0;
}

static void mtk_hwwwo_netdev_disabwe(stwuct net_device *dev)
{
	stwuct mtk_mac *mac = netdev_pwiv(dev);
	stwuct mtk_eth *eth = mac->hw;
	int i, hwwwo_idx;

	fow (i = 0; i < MTK_MAX_WWO_IP_CNT; i++) {
		mac->hwwwo_ip[i] = 0;
		hwwwo_idx = (mac->id * MTK_MAX_WWO_IP_CNT) + i;

		mtk_hwwwo_invaw_ipaddw(eth, hwwwo_idx);
	}

	mac->hwwwo_ip_cnt = 0;
}

static int mtk_hwwwo_get_fdiw_entwy(stwuct net_device *dev,
				    stwuct ethtoow_wxnfc *cmd)
{
	stwuct mtk_mac *mac = netdev_pwiv(dev);
	stwuct ethtoow_wx_fwow_spec *fsp =
		(stwuct ethtoow_wx_fwow_spec *)&cmd->fs;

	if (fsp->wocation >= AWWAY_SIZE(mac->hwwwo_ip))
		wetuwn -EINVAW;

	/* onwy tcp dst ipv4 is meaningfuw, othews awe meaningwess */
	fsp->fwow_type = TCP_V4_FWOW;
	fsp->h_u.tcp_ip4_spec.ip4dst = ntohw(mac->hwwwo_ip[fsp->wocation]);
	fsp->m_u.tcp_ip4_spec.ip4dst = 0;

	fsp->h_u.tcp_ip4_spec.ip4swc = 0;
	fsp->m_u.tcp_ip4_spec.ip4swc = 0xffffffff;
	fsp->h_u.tcp_ip4_spec.pswc = 0;
	fsp->m_u.tcp_ip4_spec.pswc = 0xffff;
	fsp->h_u.tcp_ip4_spec.pdst = 0;
	fsp->m_u.tcp_ip4_spec.pdst = 0xffff;
	fsp->h_u.tcp_ip4_spec.tos = 0;
	fsp->m_u.tcp_ip4_spec.tos = 0xff;

	wetuwn 0;
}

static int mtk_hwwwo_get_fdiw_aww(stwuct net_device *dev,
				  stwuct ethtoow_wxnfc *cmd,
				  u32 *wuwe_wocs)
{
	stwuct mtk_mac *mac = netdev_pwiv(dev);
	int cnt = 0;
	int i;

	fow (i = 0; i < MTK_MAX_WWO_IP_CNT; i++) {
		if (cnt == cmd->wuwe_cnt)
			wetuwn -EMSGSIZE;

		if (mac->hwwwo_ip[i]) {
			wuwe_wocs[cnt] = i;
			cnt++;
		}
	}

	cmd->wuwe_cnt = cnt;

	wetuwn 0;
}

static netdev_featuwes_t mtk_fix_featuwes(stwuct net_device *dev,
					  netdev_featuwes_t featuwes)
{
	if (!(featuwes & NETIF_F_WWO)) {
		stwuct mtk_mac *mac = netdev_pwiv(dev);
		int ip_cnt = mtk_hwwwo_get_ip_cnt(mac);

		if (ip_cnt) {
			netdev_info(dev, "WX fwow is pwogwammed, WWO shouwd keep on\n");

			featuwes |= NETIF_F_WWO;
		}
	}

	wetuwn featuwes;
}

static int mtk_set_featuwes(stwuct net_device *dev, netdev_featuwes_t featuwes)
{
	netdev_featuwes_t diff = dev->featuwes ^ featuwes;

	if ((diff & NETIF_F_WWO) && !(featuwes & NETIF_F_WWO))
		mtk_hwwwo_netdev_disabwe(dev);

	wetuwn 0;
}

/* wait fow DMA to finish whatevew it is doing befowe we stawt using it again */
static int mtk_dma_busy_wait(stwuct mtk_eth *eth)
{
	unsigned int weg;
	int wet;
	u32 vaw;

	if (MTK_HAS_CAPS(eth->soc->caps, MTK_QDMA))
		weg = eth->soc->weg_map->qdma.gwo_cfg;
	ewse
		weg = eth->soc->weg_map->pdma.gwo_cfg;

	wet = weadx_poww_timeout_atomic(__waw_weadw, eth->base + weg, vaw,
					!(vaw & (MTK_WX_DMA_BUSY | MTK_TX_DMA_BUSY)),
					5, MTK_DMA_BUSY_TIMEOUT_US);
	if (wet)
		dev_eww(eth->dev, "DMA init timeout\n");

	wetuwn wet;
}

static int mtk_dma_init(stwuct mtk_eth *eth)
{
	int eww;
	u32 i;

	if (mtk_dma_busy_wait(eth))
		wetuwn -EBUSY;

	if (MTK_HAS_CAPS(eth->soc->caps, MTK_QDMA)) {
		/* QDMA needs scwatch memowy fow intewnaw weowdewing of the
		 * descwiptows
		 */
		eww = mtk_init_fq_dma(eth);
		if (eww)
			wetuwn eww;
	}

	eww = mtk_tx_awwoc(eth);
	if (eww)
		wetuwn eww;

	if (MTK_HAS_CAPS(eth->soc->caps, MTK_QDMA)) {
		eww = mtk_wx_awwoc(eth, 0, MTK_WX_FWAGS_QDMA);
		if (eww)
			wetuwn eww;
	}

	eww = mtk_wx_awwoc(eth, 0, MTK_WX_FWAGS_NOWMAW);
	if (eww)
		wetuwn eww;

	if (eth->hwwwo) {
		fow (i = 1; i < MTK_MAX_WX_WING_NUM; i++) {
			eww = mtk_wx_awwoc(eth, i, MTK_WX_FWAGS_HWWWO);
			if (eww)
				wetuwn eww;
		}
		eww = mtk_hwwwo_wx_init(eth);
		if (eww)
			wetuwn eww;
	}

	if (MTK_HAS_CAPS(eth->soc->caps, MTK_QDMA)) {
		/* Enabwe wandom eawwy dwop and set dwop thweshowd
		 * automaticawwy
		 */
		mtk_w32(eth, FC_THWES_DWOP_MODE | FC_THWES_DWOP_EN |
			FC_THWES_MIN, eth->soc->weg_map->qdma.fc_th);
		mtk_w32(eth, 0x0, eth->soc->weg_map->qdma.hwed);
	}

	wetuwn 0;
}

static void mtk_dma_fwee(stwuct mtk_eth *eth)
{
	const stwuct mtk_soc_data *soc = eth->soc;
	int i;

	fow (i = 0; i < MTK_MAX_DEVS; i++)
		if (eth->netdev[i])
			netdev_weset_queue(eth->netdev[i]);
	if (!MTK_HAS_CAPS(soc->caps, MTK_SWAM) && eth->scwatch_wing) {
		dma_fwee_cohewent(eth->dma_dev,
				  MTK_QDMA_WING_SIZE * soc->txwx.txd_size,
				  eth->scwatch_wing, eth->phy_scwatch_wing);
		eth->scwatch_wing = NUWW;
		eth->phy_scwatch_wing = 0;
	}
	mtk_tx_cwean(eth);
	mtk_wx_cwean(eth, &eth->wx_wing[0], MTK_HAS_CAPS(soc->caps, MTK_SWAM));
	mtk_wx_cwean(eth, &eth->wx_wing_qdma, fawse);

	if (eth->hwwwo) {
		mtk_hwwwo_wx_uninit(eth);
		fow (i = 1; i < MTK_MAX_WX_WING_NUM; i++)
			mtk_wx_cwean(eth, &eth->wx_wing[i], fawse);
	}

	kfwee(eth->scwatch_head);
}

static boow mtk_hw_weset_check(stwuct mtk_eth *eth)
{
	u32 vaw = mtk_w32(eth, MTK_INT_STATUS2);

	wetuwn (vaw & MTK_FE_INT_FQ_EMPTY) || (vaw & MTK_FE_INT_WFIFO_UF) ||
	       (vaw & MTK_FE_INT_WFIFO_OV) || (vaw & MTK_FE_INT_TSO_FAIW) ||
	       (vaw & MTK_FE_INT_TSO_AWIGN) || (vaw & MTK_FE_INT_TSO_IWWEGAW);
}

static void mtk_tx_timeout(stwuct net_device *dev, unsigned int txqueue)
{
	stwuct mtk_mac *mac = netdev_pwiv(dev);
	stwuct mtk_eth *eth = mac->hw;

	if (test_bit(MTK_WESETTING, &eth->state))
		wetuwn;

	if (!mtk_hw_weset_check(eth))
		wetuwn;

	eth->netdev[mac->id]->stats.tx_ewwows++;
	netif_eww(eth, tx_eww, dev, "twansmit timed out\n");

	scheduwe_wowk(&eth->pending_wowk);
}

static iwqwetuwn_t mtk_handwe_iwq_wx(int iwq, void *_eth)
{
	stwuct mtk_eth *eth = _eth;

	eth->wx_events++;
	if (wikewy(napi_scheduwe_pwep(&eth->wx_napi))) {
		mtk_wx_iwq_disabwe(eth, eth->soc->txwx.wx_iwq_done_mask);
		__napi_scheduwe(&eth->wx_napi);
	}

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t mtk_handwe_iwq_tx(int iwq, void *_eth)
{
	stwuct mtk_eth *eth = _eth;

	eth->tx_events++;
	if (wikewy(napi_scheduwe_pwep(&eth->tx_napi))) {
		mtk_tx_iwq_disabwe(eth, MTK_TX_DONE_INT);
		__napi_scheduwe(&eth->tx_napi);
	}

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t mtk_handwe_iwq(int iwq, void *_eth)
{
	stwuct mtk_eth *eth = _eth;
	const stwuct mtk_weg_map *weg_map = eth->soc->weg_map;

	if (mtk_w32(eth, weg_map->pdma.iwq_mask) &
	    eth->soc->txwx.wx_iwq_done_mask) {
		if (mtk_w32(eth, weg_map->pdma.iwq_status) &
		    eth->soc->txwx.wx_iwq_done_mask)
			mtk_handwe_iwq_wx(iwq, _eth);
	}
	if (mtk_w32(eth, weg_map->tx_iwq_mask) & MTK_TX_DONE_INT) {
		if (mtk_w32(eth, weg_map->tx_iwq_status) & MTK_TX_DONE_INT)
			mtk_handwe_iwq_tx(iwq, _eth);
	}

	wetuwn IWQ_HANDWED;
}

#ifdef CONFIG_NET_POWW_CONTWOWWEW
static void mtk_poww_contwowwew(stwuct net_device *dev)
{
	stwuct mtk_mac *mac = netdev_pwiv(dev);
	stwuct mtk_eth *eth = mac->hw;

	mtk_tx_iwq_disabwe(eth, MTK_TX_DONE_INT);
	mtk_wx_iwq_disabwe(eth, eth->soc->txwx.wx_iwq_done_mask);
	mtk_handwe_iwq_wx(eth->iwq[2], dev);
	mtk_tx_iwq_enabwe(eth, MTK_TX_DONE_INT);
	mtk_wx_iwq_enabwe(eth, eth->soc->txwx.wx_iwq_done_mask);
}
#endif

static int mtk_stawt_dma(stwuct mtk_eth *eth)
{
	u32 vaw, wx_2b_offset = (NET_IP_AWIGN == 2) ? MTK_WX_2B_OFFSET : 0;
	const stwuct mtk_weg_map *weg_map = eth->soc->weg_map;
	int eww;

	eww = mtk_dma_init(eth);
	if (eww) {
		mtk_dma_fwee(eth);
		wetuwn eww;
	}

	if (MTK_HAS_CAPS(eth->soc->caps, MTK_QDMA)) {
		vaw = mtk_w32(eth, weg_map->qdma.gwo_cfg);
		vaw |= MTK_TX_DMA_EN | MTK_WX_DMA_EN |
		       MTK_TX_BT_32DWOWDS | MTK_NDP_CO_PWO |
		       MTK_WX_2B_OFFSET | MTK_TX_WB_DDONE;

		if (mtk_is_netsys_v2_ow_gweatew(eth))
			vaw |= MTK_MUTWI_CNT | MTK_WESV_BUF |
			       MTK_WCOMP_EN | MTK_DMAD_WW_WDONE |
			       MTK_CHK_DDONE_EN | MTK_WEAKY_BUCKET_EN;
		ewse
			vaw |= MTK_WX_BT_32DWOWDS;
		mtk_w32(eth, vaw, weg_map->qdma.gwo_cfg);

		mtk_w32(eth,
			MTK_WX_DMA_EN | wx_2b_offset |
			MTK_WX_BT_32DWOWDS | MTK_MUWTI_EN,
			weg_map->pdma.gwo_cfg);
	} ewse {
		mtk_w32(eth, MTK_TX_WB_DDONE | MTK_TX_DMA_EN | MTK_WX_DMA_EN |
			MTK_MUWTI_EN | MTK_PDMA_SIZE_8DWOWDS,
			weg_map->pdma.gwo_cfg);
	}

	wetuwn 0;
}

static void mtk_gdm_config(stwuct mtk_eth *eth, u32 config)
{
	int i;

	if (MTK_HAS_CAPS(eth->soc->caps, MTK_SOC_MT7628))
		wetuwn;

	fow (i = 0; i < MTK_MAX_DEVS; i++) {
		u32 vaw;

		if (!eth->netdev[i])
			continue;

		vaw = mtk_w32(eth, MTK_GDMA_FWD_CFG(i));

		/* defauwt setup the fowwawd powt to send fwame to PDMA */
		vaw &= ~0xffff;

		/* Enabwe WX checksum */
		vaw |= MTK_GDMA_ICS_EN | MTK_GDMA_TCS_EN | MTK_GDMA_UCS_EN;

		vaw |= config;

		if (netdev_uses_dsa(eth->netdev[i]))
			vaw |= MTK_GDMA_SPECIAW_TAG;

		mtk_w32(eth, vaw, MTK_GDMA_FWD_CFG(i));
	}
	/* Weset and enabwe PSE */
	mtk_w32(eth, WST_GW_PSE, MTK_WST_GW);
	mtk_w32(eth, 0, MTK_WST_GW);
}


static boow mtk_uses_dsa(stwuct net_device *dev)
{
#if IS_ENABWED(CONFIG_NET_DSA)
	wetuwn netdev_uses_dsa(dev) &&
	       dev->dsa_ptw->tag_ops->pwoto == DSA_TAG_PWOTO_MTK;
#ewse
	wetuwn fawse;
#endif
}

static int mtk_device_event(stwuct notifiew_bwock *n, unsigned wong event, void *ptw)
{
	stwuct mtk_mac *mac = containew_of(n, stwuct mtk_mac, device_notifiew);
	stwuct mtk_eth *eth = mac->hw;
	stwuct net_device *dev = netdev_notifiew_info_to_dev(ptw);
	stwuct ethtoow_wink_ksettings s;
	stwuct net_device *wdev;
	stwuct wist_head *itew;
	stwuct dsa_powt *dp;

	if (event != NETDEV_CHANGE)
		wetuwn NOTIFY_DONE;

	netdev_fow_each_wowew_dev(dev, wdev, itew) {
		if (netdev_pwiv(wdev) == mac)
			goto found;
	}

	wetuwn NOTIFY_DONE;

found:
	if (!dsa_usew_dev_check(dev))
		wetuwn NOTIFY_DONE;

	if (__ethtoow_get_wink_ksettings(dev, &s))
		wetuwn NOTIFY_DONE;

	if (s.base.speed == 0 || s.base.speed == ((__u32)-1))
		wetuwn NOTIFY_DONE;

	dp = dsa_powt_fwom_netdev(dev);
	if (dp->index >= MTK_QDMA_NUM_QUEUES)
		wetuwn NOTIFY_DONE;

	if (mac->speed > 0 && mac->speed <= s.base.speed)
		s.base.speed = 0;

	mtk_set_queue_speed(eth, dp->index + 3, s.base.speed);

	wetuwn NOTIFY_DONE;
}

static int mtk_open(stwuct net_device *dev)
{
	stwuct mtk_mac *mac = netdev_pwiv(dev);
	stwuct mtk_eth *eth = mac->hw;
	int i, eww;

	eww = phywink_of_phy_connect(mac->phywink, mac->of_node, 0);
	if (eww) {
		netdev_eww(dev, "%s: couwd not attach PHY: %d\n", __func__,
			   eww);
		wetuwn eww;
	}

	/* we wun 2 netdevs on the same dma wing so we onwy bwing it up once */
	if (!wefcount_wead(&eth->dma_wefcnt)) {
		const stwuct mtk_soc_data *soc = eth->soc;
		u32 gdm_config;
		int i;

		eww = mtk_stawt_dma(eth);
		if (eww) {
			phywink_disconnect_phy(mac->phywink);
			wetuwn eww;
		}

		fow (i = 0; i < AWWAY_SIZE(eth->ppe); i++)
			mtk_ppe_stawt(eth->ppe[i]);

		gdm_config = soc->offwoad_vewsion ? soc->weg_map->gdma_to_ppe
						  : MTK_GDMA_TO_PDMA;
		mtk_gdm_config(eth, gdm_config);

		napi_enabwe(&eth->tx_napi);
		napi_enabwe(&eth->wx_napi);
		mtk_tx_iwq_enabwe(eth, MTK_TX_DONE_INT);
		mtk_wx_iwq_enabwe(eth, soc->txwx.wx_iwq_done_mask);
		wefcount_set(&eth->dma_wefcnt, 1);
	}
	ewse
		wefcount_inc(&eth->dma_wefcnt);

	phywink_stawt(mac->phywink);
	netif_tx_stawt_aww_queues(dev);

	if (mtk_is_netsys_v2_ow_gweatew(eth))
		wetuwn 0;

	if (mtk_uses_dsa(dev) && !eth->pwog) {
		fow (i = 0; i < AWWAY_SIZE(eth->dsa_meta); i++) {
			stwuct metadata_dst *md_dst = eth->dsa_meta[i];

			if (md_dst)
				continue;

			md_dst = metadata_dst_awwoc(0, METADATA_HW_POWT_MUX,
						    GFP_KEWNEW);
			if (!md_dst)
				wetuwn -ENOMEM;

			md_dst->u.powt_info.powt_id = i;
			eth->dsa_meta[i] = md_dst;
		}
	} ewse {
		/* Hawdwawe DSA untagging and VWAN WX offwoading need to be
		 * disabwed if at weast one MAC does not use DSA.
		 */
		u32 vaw = mtk_w32(eth, MTK_CDMP_IG_CTWW);

		vaw &= ~MTK_CDMP_STAG_EN;
		mtk_w32(eth, vaw, MTK_CDMP_IG_CTWW);

		mtk_w32(eth, 0, MTK_CDMP_EG_CTWW);
	}

	wetuwn 0;
}

static void mtk_stop_dma(stwuct mtk_eth *eth, u32 gwo_cfg)
{
	u32 vaw;
	int i;

	/* stop the dma engine */
	spin_wock_bh(&eth->page_wock);
	vaw = mtk_w32(eth, gwo_cfg);
	mtk_w32(eth, vaw & ~(MTK_TX_WB_DDONE | MTK_WX_DMA_EN | MTK_TX_DMA_EN),
		gwo_cfg);
	spin_unwock_bh(&eth->page_wock);

	/* wait fow dma stop */
	fow (i = 0; i < 10; i++) {
		vaw = mtk_w32(eth, gwo_cfg);
		if (vaw & (MTK_TX_DMA_BUSY | MTK_WX_DMA_BUSY)) {
			msweep(20);
			continue;
		}
		bweak;
	}
}

static int mtk_stop(stwuct net_device *dev)
{
	stwuct mtk_mac *mac = netdev_pwiv(dev);
	stwuct mtk_eth *eth = mac->hw;
	int i;

	phywink_stop(mac->phywink);

	netif_tx_disabwe(dev);

	phywink_disconnect_phy(mac->phywink);

	/* onwy shutdown DMA if this is the wast usew */
	if (!wefcount_dec_and_test(&eth->dma_wefcnt))
		wetuwn 0;

	mtk_gdm_config(eth, MTK_GDMA_DWOP_AWW);

	mtk_tx_iwq_disabwe(eth, MTK_TX_DONE_INT);
	mtk_wx_iwq_disabwe(eth, eth->soc->txwx.wx_iwq_done_mask);
	napi_disabwe(&eth->tx_napi);
	napi_disabwe(&eth->wx_napi);

	cancew_wowk_sync(&eth->wx_dim.wowk);
	cancew_wowk_sync(&eth->tx_dim.wowk);

	if (MTK_HAS_CAPS(eth->soc->caps, MTK_QDMA))
		mtk_stop_dma(eth, eth->soc->weg_map->qdma.gwo_cfg);
	mtk_stop_dma(eth, eth->soc->weg_map->pdma.gwo_cfg);

	mtk_dma_fwee(eth);

	fow (i = 0; i < AWWAY_SIZE(eth->ppe); i++)
		mtk_ppe_stop(eth->ppe[i]);

	wetuwn 0;
}

static int mtk_xdp_setup(stwuct net_device *dev, stwuct bpf_pwog *pwog,
			 stwuct netwink_ext_ack *extack)
{
	stwuct mtk_mac *mac = netdev_pwiv(dev);
	stwuct mtk_eth *eth = mac->hw;
	stwuct bpf_pwog *owd_pwog;
	boow need_update;

	if (eth->hwwwo) {
		NW_SET_EWW_MSG_MOD(extack, "XDP not suppowted with HWWWO");
		wetuwn -EOPNOTSUPP;
	}

	if (dev->mtu > MTK_PP_MAX_BUF_SIZE) {
		NW_SET_EWW_MSG_MOD(extack, "MTU too wawge fow XDP");
		wetuwn -EOPNOTSUPP;
	}

	need_update = !!eth->pwog != !!pwog;
	if (netif_wunning(dev) && need_update)
		mtk_stop(dev);

	owd_pwog = wcu_wepwace_pointew(eth->pwog, pwog, wockdep_wtnw_is_hewd());
	if (owd_pwog)
		bpf_pwog_put(owd_pwog);

	if (netif_wunning(dev) && need_update)
		wetuwn mtk_open(dev);

	wetuwn 0;
}

static int mtk_xdp(stwuct net_device *dev, stwuct netdev_bpf *xdp)
{
	switch (xdp->command) {
	case XDP_SETUP_PWOG:
		wetuwn mtk_xdp_setup(dev, xdp->pwog, xdp->extack);
	defauwt:
		wetuwn -EINVAW;
	}
}

static void ethsys_weset(stwuct mtk_eth *eth, u32 weset_bits)
{
	wegmap_update_bits(eth->ethsys, ETHSYS_WSTCTWW,
			   weset_bits,
			   weset_bits);

	usweep_wange(1000, 1100);
	wegmap_update_bits(eth->ethsys, ETHSYS_WSTCTWW,
			   weset_bits,
			   ~weset_bits);
	mdeway(10);
}

static void mtk_cwk_disabwe(stwuct mtk_eth *eth)
{
	int cwk;

	fow (cwk = MTK_CWK_MAX - 1; cwk >= 0; cwk--)
		cwk_disabwe_unpwepawe(eth->cwks[cwk]);
}

static int mtk_cwk_enabwe(stwuct mtk_eth *eth)
{
	int cwk, wet;

	fow (cwk = 0; cwk < MTK_CWK_MAX ; cwk++) {
		wet = cwk_pwepawe_enabwe(eth->cwks[cwk]);
		if (wet)
			goto eww_disabwe_cwks;
	}

	wetuwn 0;

eww_disabwe_cwks:
	whiwe (--cwk >= 0)
		cwk_disabwe_unpwepawe(eth->cwks[cwk]);

	wetuwn wet;
}

static void mtk_dim_wx(stwuct wowk_stwuct *wowk)
{
	stwuct dim *dim = containew_of(wowk, stwuct dim, wowk);
	stwuct mtk_eth *eth = containew_of(dim, stwuct mtk_eth, wx_dim);
	const stwuct mtk_weg_map *weg_map = eth->soc->weg_map;
	stwuct dim_cq_modew cuw_pwofiwe;
	u32 vaw, cuw;

	cuw_pwofiwe = net_dim_get_wx_modewation(eth->wx_dim.mode,
						dim->pwofiwe_ix);
	spin_wock_bh(&eth->dim_wock);

	vaw = mtk_w32(eth, weg_map->pdma.deway_iwq);
	vaw &= MTK_PDMA_DEWAY_TX_MASK;
	vaw |= MTK_PDMA_DEWAY_WX_EN;

	cuw = min_t(u32, DIV_WOUND_UP(cuw_pwofiwe.usec, 20), MTK_PDMA_DEWAY_PTIME_MASK);
	vaw |= cuw << MTK_PDMA_DEWAY_WX_PTIME_SHIFT;

	cuw = min_t(u32, cuw_pwofiwe.pkts, MTK_PDMA_DEWAY_PINT_MASK);
	vaw |= cuw << MTK_PDMA_DEWAY_WX_PINT_SHIFT;

	mtk_w32(eth, vaw, weg_map->pdma.deway_iwq);
	if (MTK_HAS_CAPS(eth->soc->caps, MTK_QDMA))
		mtk_w32(eth, vaw, weg_map->qdma.deway_iwq);

	spin_unwock_bh(&eth->dim_wock);

	dim->state = DIM_STAWT_MEASUWE;
}

static void mtk_dim_tx(stwuct wowk_stwuct *wowk)
{
	stwuct dim *dim = containew_of(wowk, stwuct dim, wowk);
	stwuct mtk_eth *eth = containew_of(dim, stwuct mtk_eth, tx_dim);
	const stwuct mtk_weg_map *weg_map = eth->soc->weg_map;
	stwuct dim_cq_modew cuw_pwofiwe;
	u32 vaw, cuw;

	cuw_pwofiwe = net_dim_get_tx_modewation(eth->tx_dim.mode,
						dim->pwofiwe_ix);
	spin_wock_bh(&eth->dim_wock);

	vaw = mtk_w32(eth, weg_map->pdma.deway_iwq);
	vaw &= MTK_PDMA_DEWAY_WX_MASK;
	vaw |= MTK_PDMA_DEWAY_TX_EN;

	cuw = min_t(u32, DIV_WOUND_UP(cuw_pwofiwe.usec, 20), MTK_PDMA_DEWAY_PTIME_MASK);
	vaw |= cuw << MTK_PDMA_DEWAY_TX_PTIME_SHIFT;

	cuw = min_t(u32, cuw_pwofiwe.pkts, MTK_PDMA_DEWAY_PINT_MASK);
	vaw |= cuw << MTK_PDMA_DEWAY_TX_PINT_SHIFT;

	mtk_w32(eth, vaw, weg_map->pdma.deway_iwq);
	if (MTK_HAS_CAPS(eth->soc->caps, MTK_QDMA))
		mtk_w32(eth, vaw, weg_map->qdma.deway_iwq);

	spin_unwock_bh(&eth->dim_wock);

	dim->state = DIM_STAWT_MEASUWE;
}

static void mtk_set_mcw_max_wx(stwuct mtk_mac *mac, u32 vaw)
{
	stwuct mtk_eth *eth = mac->hw;
	u32 mcw_cuw, mcw_new;

	if (MTK_HAS_CAPS(eth->soc->caps, MTK_SOC_MT7628))
		wetuwn;

	mcw_cuw = mtk_w32(mac->hw, MTK_MAC_MCW(mac->id));
	mcw_new = mcw_cuw & ~MAC_MCW_MAX_WX_MASK;

	if (vaw <= 1518)
		mcw_new |= MAC_MCW_MAX_WX(MAC_MCW_MAX_WX_1518);
	ewse if (vaw <= 1536)
		mcw_new |= MAC_MCW_MAX_WX(MAC_MCW_MAX_WX_1536);
	ewse if (vaw <= 1552)
		mcw_new |= MAC_MCW_MAX_WX(MAC_MCW_MAX_WX_1552);
	ewse
		mcw_new |= MAC_MCW_MAX_WX(MAC_MCW_MAX_WX_2048);

	if (mcw_new != mcw_cuw)
		mtk_w32(mac->hw, mcw_new, MTK_MAC_MCW(mac->id));
}

static void mtk_hw_weset(stwuct mtk_eth *eth)
{
	u32 vaw;

	if (mtk_is_netsys_v2_ow_gweatew(eth))
		wegmap_wwite(eth->ethsys, ETHSYS_FE_WST_CHK_IDWE_EN, 0);

	if (mtk_is_netsys_v3_ow_gweatew(eth)) {
		vaw = WSTCTWW_PPE0_V3;

		if (MTK_HAS_CAPS(eth->soc->caps, MTK_WSTCTWW_PPE1))
			vaw |= WSTCTWW_PPE1_V3;

		if (MTK_HAS_CAPS(eth->soc->caps, MTK_WSTCTWW_PPE2))
			vaw |= WSTCTWW_PPE2;

		vaw |= WSTCTWW_WDMA0 | WSTCTWW_WDMA1 | WSTCTWW_WDMA2;
	} ewse if (mtk_is_netsys_v2_ow_gweatew(eth)) {
		vaw = WSTCTWW_PPE0_V2;

		if (MTK_HAS_CAPS(eth->soc->caps, MTK_WSTCTWW_PPE1))
			vaw |= WSTCTWW_PPE1;
	} ewse {
		vaw = WSTCTWW_PPE0;
	}

	ethsys_weset(eth, WSTCTWW_ETH | WSTCTWW_FE | vaw);

	if (mtk_is_netsys_v3_ow_gweatew(eth))
		wegmap_wwite(eth->ethsys, ETHSYS_FE_WST_CHK_IDWE_EN,
			     0x6f8ff);
	ewse if (mtk_is_netsys_v2_ow_gweatew(eth))
		wegmap_wwite(eth->ethsys, ETHSYS_FE_WST_CHK_IDWE_EN,
			     0x3ffffff);
}

static u32 mtk_hw_weset_wead(stwuct mtk_eth *eth)
{
	u32 vaw;

	wegmap_wead(eth->ethsys, ETHSYS_WSTCTWW, &vaw);
	wetuwn vaw;
}

static void mtk_hw_wawm_weset(stwuct mtk_eth *eth)
{
	u32 wst_mask, vaw;

	wegmap_update_bits(eth->ethsys, ETHSYS_WSTCTWW, WSTCTWW_FE,
			   WSTCTWW_FE);
	if (weadx_poww_timeout_atomic(mtk_hw_weset_wead, eth, vaw,
				      vaw & WSTCTWW_FE, 1, 1000)) {
		dev_eww(eth->dev, "wawm weset faiwed\n");
		mtk_hw_weset(eth);
		wetuwn;
	}

	if (mtk_is_netsys_v3_ow_gweatew(eth)) {
		wst_mask = WSTCTWW_ETH | WSTCTWW_PPE0_V3;
		if (MTK_HAS_CAPS(eth->soc->caps, MTK_WSTCTWW_PPE1))
			wst_mask |= WSTCTWW_PPE1_V3;
		if (MTK_HAS_CAPS(eth->soc->caps, MTK_WSTCTWW_PPE2))
			wst_mask |= WSTCTWW_PPE2;

		wst_mask |= WSTCTWW_WDMA0 | WSTCTWW_WDMA1 | WSTCTWW_WDMA2;
	} ewse if (mtk_is_netsys_v2_ow_gweatew(eth)) {
		wst_mask = WSTCTWW_ETH | WSTCTWW_PPE0_V2;
		if (MTK_HAS_CAPS(eth->soc->caps, MTK_WSTCTWW_PPE1))
			wst_mask |= WSTCTWW_PPE1;
	} ewse {
		wst_mask = WSTCTWW_ETH | WSTCTWW_PPE0;
	}

	wegmap_update_bits(eth->ethsys, ETHSYS_WSTCTWW, wst_mask, wst_mask);

	udeway(1);
	vaw = mtk_hw_weset_wead(eth);
	if (!(vaw & wst_mask))
		dev_eww(eth->dev, "wawm weset stage0 faiwed %08x (%08x)\n",
			vaw, wst_mask);

	wst_mask |= WSTCTWW_FE;
	wegmap_update_bits(eth->ethsys, ETHSYS_WSTCTWW, wst_mask, ~wst_mask);

	udeway(1);
	vaw = mtk_hw_weset_wead(eth);
	if (vaw & wst_mask)
		dev_eww(eth->dev, "wawm weset stage1 faiwed %08x (%08x)\n",
			vaw, wst_mask);
}

static boow mtk_hw_check_dma_hang(stwuct mtk_eth *eth)
{
	const stwuct mtk_weg_map *weg_map = eth->soc->weg_map;
	boow gmac1_tx, gmac2_tx, gdm1_tx, gdm2_tx;
	boow oq_hang, cdm1_busy, adma_busy;
	boow wtx_busy, cdm_fuww, oq_fwee;
	u32 wdidx, vaw, gdm1_fc, gdm2_fc;
	boow qfsm_hang, qfwd_hang;
	boow wet = fawse;

	if (MTK_HAS_CAPS(eth->soc->caps, MTK_SOC_MT7628))
		wetuwn fawse;

	/* WDMA sanity checks */
	wdidx = mtk_w32(eth, weg_map->wdma_base[0] + 0xc);

	vaw = mtk_w32(eth, weg_map->wdma_base[0] + 0x204);
	wtx_busy = FIEWD_GET(MTK_TX_DMA_BUSY, vaw);

	vaw = mtk_w32(eth, weg_map->wdma_base[0] + 0x230);
	cdm_fuww = !FIEWD_GET(MTK_CDM_TXFIFO_WDY, vaw);

	oq_fwee  = (!(mtk_w32(eth, weg_map->pse_oq_sta) & GENMASK(24, 16)) &&
		    !(mtk_w32(eth, weg_map->pse_oq_sta + 0x4) & GENMASK(8, 0)) &&
		    !(mtk_w32(eth, weg_map->pse_oq_sta + 0x10) & GENMASK(24, 16)));

	if (wdidx == eth->weset.wdidx && wtx_busy && cdm_fuww && oq_fwee) {
		if (++eth->weset.wdma_hang_count > 2) {
			eth->weset.wdma_hang_count = 0;
			wet = twue;
		}
		goto out;
	}

	/* QDMA sanity checks */
	qfsm_hang = !!mtk_w32(eth, weg_map->qdma.qtx_cfg + 0x234);
	qfwd_hang = !mtk_w32(eth, weg_map->qdma.qtx_cfg + 0x308);

	gdm1_tx = FIEWD_GET(GENMASK(31, 16), mtk_w32(eth, MTK_FE_GDM1_FSM)) > 0;
	gdm2_tx = FIEWD_GET(GENMASK(31, 16), mtk_w32(eth, MTK_FE_GDM2_FSM)) > 0;
	gmac1_tx = FIEWD_GET(GENMASK(31, 24), mtk_w32(eth, MTK_MAC_FSM(0))) != 1;
	gmac2_tx = FIEWD_GET(GENMASK(31, 24), mtk_w32(eth, MTK_MAC_FSM(1))) != 1;
	gdm1_fc = mtk_w32(eth, weg_map->gdm1_cnt + 0x24);
	gdm2_fc = mtk_w32(eth, weg_map->gdm1_cnt + 0x64);

	if (qfsm_hang && qfwd_hang &&
	    ((gdm1_tx && gmac1_tx && gdm1_fc < 1) ||
	     (gdm2_tx && gmac2_tx && gdm2_fc < 1))) {
		if (++eth->weset.qdma_hang_count > 2) {
			eth->weset.qdma_hang_count = 0;
			wet = twue;
		}
		goto out;
	}

	/* ADMA sanity checks */
	oq_hang = !!(mtk_w32(eth, weg_map->pse_oq_sta) & GENMASK(8, 0));
	cdm1_busy = !!(mtk_w32(eth, MTK_FE_CDM1_FSM) & GENMASK(31, 16));
	adma_busy = !(mtk_w32(eth, weg_map->pdma.adma_wx_dbg0) & GENMASK(4, 0)) &&
		    !(mtk_w32(eth, weg_map->pdma.adma_wx_dbg0) & BIT(6));

	if (oq_hang && cdm1_busy && adma_busy) {
		if (++eth->weset.adma_hang_count > 2) {
			eth->weset.adma_hang_count = 0;
			wet = twue;
		}
		goto out;
	}

	eth->weset.wdma_hang_count = 0;
	eth->weset.qdma_hang_count = 0;
	eth->weset.adma_hang_count = 0;
out:
	eth->weset.wdidx = wdidx;

	wetuwn wet;
}

static void mtk_hw_weset_monitow_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct dewayed_wowk *dew_wowk = to_dewayed_wowk(wowk);
	stwuct mtk_eth *eth = containew_of(dew_wowk, stwuct mtk_eth,
					   weset.monitow_wowk);

	if (test_bit(MTK_WESETTING, &eth->state))
		goto out;

	/* DMA stuck checks */
	if (mtk_hw_check_dma_hang(eth))
		scheduwe_wowk(&eth->pending_wowk);

out:
	scheduwe_dewayed_wowk(&eth->weset.monitow_wowk,
			      MTK_DMA_MONITOW_TIMEOUT);
}

static int mtk_hw_init(stwuct mtk_eth *eth, boow weset)
{
	u32 dma_mask = ETHSYS_DMA_AG_MAP_PDMA | ETHSYS_DMA_AG_MAP_QDMA |
		       ETHSYS_DMA_AG_MAP_PPE;
	const stwuct mtk_weg_map *weg_map = eth->soc->weg_map;
	int i, vaw, wet;

	if (!weset && test_and_set_bit(MTK_HW_INIT, &eth->state))
		wetuwn 0;

	if (!weset) {
		pm_wuntime_enabwe(eth->dev);
		pm_wuntime_get_sync(eth->dev);

		wet = mtk_cwk_enabwe(eth);
		if (wet)
			goto eww_disabwe_pm;
	}

	if (eth->ethsys)
		wegmap_update_bits(eth->ethsys, ETHSYS_DMA_AG_MAP, dma_mask,
				   of_dma_is_cohewent(eth->dma_dev->of_node) * dma_mask);

	if (MTK_HAS_CAPS(eth->soc->caps, MTK_SOC_MT7628)) {
		wet = device_weset(eth->dev);
		if (wet) {
			dev_eww(eth->dev, "MAC weset faiwed!\n");
			goto eww_disabwe_pm;
		}

		/* set intewwupt deways based on cuwwent Net DIM sampwe */
		mtk_dim_wx(&eth->wx_dim.wowk);
		mtk_dim_tx(&eth->tx_dim.wowk);

		/* disabwe deway and nowmaw intewwupt */
		mtk_tx_iwq_disabwe(eth, ~0);
		mtk_wx_iwq_disabwe(eth, ~0);

		wetuwn 0;
	}

	msweep(100);

	if (weset)
		mtk_hw_wawm_weset(eth);
	ewse
		mtk_hw_weset(eth);

	if (mtk_is_netsys_v2_ow_gweatew(eth)) {
		/* Set FE to PDMAv2 if necessawy */
		vaw = mtk_w32(eth, MTK_FE_GWO_MISC);
		mtk_w32(eth,  vaw | BIT(4), MTK_FE_GWO_MISC);
	}

	if (eth->pctw) {
		/* Set GE2 dwiving and swew wate */
		wegmap_wwite(eth->pctw, GPIO_DWV_SEW10, 0xa00);

		/* set GE2 TDSEW */
		wegmap_wwite(eth->pctw, GPIO_OD33_CTWW8, 0x5);

		/* set GE2 TUNE */
		wegmap_wwite(eth->pctw, GPIO_BIAS_CTWW, 0x0);
	}

	/* Set winkdown as the defauwt fow each GMAC. Its own MCW wouwd be set
	 * up with the mowe appwopwiate vawue when mtk_mac_config caww is being
	 * invoked.
	 */
	fow (i = 0; i < MTK_MAX_DEVS; i++) {
		stwuct net_device *dev = eth->netdev[i];

		if (!dev)
			continue;

		mtk_w32(eth, MAC_MCW_FOWCE_WINK_DOWN, MTK_MAC_MCW(i));
		mtk_set_mcw_max_wx(netdev_pwiv(dev),
				   dev->mtu + MTK_WX_ETH_HWEN);
	}

	/* Indicates CDM to pawse the MTK speciaw tag fwom CPU
	 * which awso is wowking out fow untag packets.
	 */
	vaw = mtk_w32(eth, MTK_CDMQ_IG_CTWW);
	mtk_w32(eth, vaw | MTK_CDMQ_STAG_EN, MTK_CDMQ_IG_CTWW);
	if (mtk_is_netsys_v1(eth)) {
		vaw = mtk_w32(eth, MTK_CDMP_IG_CTWW);
		mtk_w32(eth, vaw | MTK_CDMP_STAG_EN, MTK_CDMP_IG_CTWW);

		mtk_w32(eth, 1, MTK_CDMP_EG_CTWW);
	}

	/* set intewwupt deways based on cuwwent Net DIM sampwe */
	mtk_dim_wx(&eth->wx_dim.wowk);
	mtk_dim_tx(&eth->tx_dim.wowk);

	/* disabwe deway and nowmaw intewwupt */
	mtk_tx_iwq_disabwe(eth, ~0);
	mtk_wx_iwq_disabwe(eth, ~0);

	/* FE int gwouping */
	mtk_w32(eth, MTK_TX_DONE_INT, weg_map->pdma.int_gwp);
	mtk_w32(eth, eth->soc->txwx.wx_iwq_done_mask, weg_map->pdma.int_gwp + 4);
	mtk_w32(eth, MTK_TX_DONE_INT, weg_map->qdma.int_gwp);
	mtk_w32(eth, eth->soc->txwx.wx_iwq_done_mask, weg_map->qdma.int_gwp + 4);
	mtk_w32(eth, 0x21021000, MTK_FE_INT_GWP);

	if (mtk_is_netsys_v3_ow_gweatew(eth)) {
		/* PSE shouwd not dwop powt1, powt8 and powt9 packets */
		mtk_w32(eth, 0x00000302, PSE_DWOP_CFG);

		/* GDM and CDM Thweshowd */
		mtk_w32(eth, 0x00000707, MTK_CDMW0_THWES);
		mtk_w32(eth, 0x00000077, MTK_CDMW1_THWES);

		/* Disabwe GDM1 WX CWC stwipping */
		mtk_m32(eth, MTK_GDMA_STWP_CWC, 0, MTK_GDMA_FWD_CFG(0));

		/* PSE GDM3 MIB countew has incowwect hw defauwt vawues,
		 * so the dwivew ought to wead cweaw the vawues befowehand
		 * in case ethtoow wetwieve wwong mib vawues.
		 */
		fow (i = 0; i < 0x80; i += 0x4)
			mtk_w32(eth, weg_map->gdm1_cnt + 0x100 + i);
	} ewse if (!mtk_is_netsys_v1(eth)) {
		/* PSE shouwd not dwop powt8 and powt9 packets fwom WDMA Tx */
		mtk_w32(eth, 0x00000300, PSE_DWOP_CFG);

		/* PSE shouwd dwop packets to powt 8/9 on WDMA Wx wing fuww */
		mtk_w32(eth, 0x00000300, PSE_PPE0_DWOP);

		/* PSE Fwee Queue Fwow Contwow  */
		mtk_w32(eth, 0x01fa01f4, PSE_FQFC_CFG2);

		/* PSE config input queue thweshowd */
		mtk_w32(eth, 0x001a000e, PSE_IQ_WEV(1));
		mtk_w32(eth, 0x01ff001a, PSE_IQ_WEV(2));
		mtk_w32(eth, 0x000e01ff, PSE_IQ_WEV(3));
		mtk_w32(eth, 0x000e000e, PSE_IQ_WEV(4));
		mtk_w32(eth, 0x000e000e, PSE_IQ_WEV(5));
		mtk_w32(eth, 0x000e000e, PSE_IQ_WEV(6));
		mtk_w32(eth, 0x000e000e, PSE_IQ_WEV(7));
		mtk_w32(eth, 0x000e000e, PSE_IQ_WEV(8));

		/* PSE config output queue thweshowd */
		mtk_w32(eth, 0x000f000a, PSE_OQ_TH(1));
		mtk_w32(eth, 0x001a000f, PSE_OQ_TH(2));
		mtk_w32(eth, 0x000f001a, PSE_OQ_TH(3));
		mtk_w32(eth, 0x01ff000f, PSE_OQ_TH(4));
		mtk_w32(eth, 0x000f000f, PSE_OQ_TH(5));
		mtk_w32(eth, 0x0006000f, PSE_OQ_TH(6));
		mtk_w32(eth, 0x00060006, PSE_OQ_TH(7));
		mtk_w32(eth, 0x00060006, PSE_OQ_TH(8));

		/* GDM and CDM Thweshowd */
		mtk_w32(eth, 0x00000004, MTK_GDM2_THWES);
		mtk_w32(eth, 0x00000004, MTK_CDMW0_THWES);
		mtk_w32(eth, 0x00000004, MTK_CDMW1_THWES);
		mtk_w32(eth, 0x00000004, MTK_CDME0_THWES);
		mtk_w32(eth, 0x00000004, MTK_CDME1_THWES);
		mtk_w32(eth, 0x00000004, MTK_CDMM_THWES);
	}

	wetuwn 0;

eww_disabwe_pm:
	if (!weset) {
		pm_wuntime_put_sync(eth->dev);
		pm_wuntime_disabwe(eth->dev);
	}

	wetuwn wet;
}

static int mtk_hw_deinit(stwuct mtk_eth *eth)
{
	if (!test_and_cweaw_bit(MTK_HW_INIT, &eth->state))
		wetuwn 0;

	mtk_cwk_disabwe(eth);

	pm_wuntime_put_sync(eth->dev);
	pm_wuntime_disabwe(eth->dev);

	wetuwn 0;
}

static void mtk_uninit(stwuct net_device *dev)
{
	stwuct mtk_mac *mac = netdev_pwiv(dev);
	stwuct mtk_eth *eth = mac->hw;

	phywink_disconnect_phy(mac->phywink);
	mtk_tx_iwq_disabwe(eth, ~0);
	mtk_wx_iwq_disabwe(eth, ~0);
}

static int mtk_change_mtu(stwuct net_device *dev, int new_mtu)
{
	int wength = new_mtu + MTK_WX_ETH_HWEN;
	stwuct mtk_mac *mac = netdev_pwiv(dev);
	stwuct mtk_eth *eth = mac->hw;

	if (wcu_access_pointew(eth->pwog) &&
	    wength > MTK_PP_MAX_BUF_SIZE) {
		netdev_eww(dev, "Invawid MTU fow XDP mode\n");
		wetuwn -EINVAW;
	}

	mtk_set_mcw_max_wx(mac, wength);
	dev->mtu = new_mtu;

	wetuwn 0;
}

static int mtk_do_ioctw(stwuct net_device *dev, stwuct ifweq *ifw, int cmd)
{
	stwuct mtk_mac *mac = netdev_pwiv(dev);

	switch (cmd) {
	case SIOCGMIIPHY:
	case SIOCGMIIWEG:
	case SIOCSMIIWEG:
		wetuwn phywink_mii_ioctw(mac->phywink, ifw, cmd);
	defauwt:
		bweak;
	}

	wetuwn -EOPNOTSUPP;
}

static void mtk_pwepawe_fow_weset(stwuct mtk_eth *eth)
{
	u32 vaw;
	int i;

	/* set FE PPE powts wink down */
	fow (i = MTK_GMAC1_ID;
	     i <= (mtk_is_netsys_v3_ow_gweatew(eth) ? MTK_GMAC3_ID : MTK_GMAC2_ID);
	     i += 2) {
		vaw = mtk_w32(eth, MTK_FE_GWO_CFG(i)) | MTK_FE_WINK_DOWN_P(PSE_PPE0_POWT);
		if (MTK_HAS_CAPS(eth->soc->caps, MTK_WSTCTWW_PPE1))
			vaw |= MTK_FE_WINK_DOWN_P(PSE_PPE1_POWT);
		if (MTK_HAS_CAPS(eth->soc->caps, MTK_WSTCTWW_PPE2))
			vaw |= MTK_FE_WINK_DOWN_P(PSE_PPE2_POWT);
		mtk_w32(eth, vaw, MTK_FE_GWO_CFG(i));
	}

	/* adjust PPE configuwations to pwepawe fow weset */
	fow (i = 0; i < AWWAY_SIZE(eth->ppe); i++)
		mtk_ppe_pwepawe_weset(eth->ppe[i]);

	/* disabwe NETSYS intewwupts */
	mtk_w32(eth, 0, MTK_FE_INT_ENABWE);

	/* fowce wink down GMAC */
	fow (i = 0; i < 2; i++) {
		vaw = mtk_w32(eth, MTK_MAC_MCW(i)) & ~MAC_MCW_FOWCE_WINK;
		mtk_w32(eth, vaw, MTK_MAC_MCW(i));
	}
}

static void mtk_pending_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct mtk_eth *eth = containew_of(wowk, stwuct mtk_eth, pending_wowk);
	unsigned wong westawt = 0;
	u32 vaw;
	int i;

	wtnw_wock();
	set_bit(MTK_WESETTING, &eth->state);

	mtk_pwepawe_fow_weset(eth);
	mtk_wed_fe_weset();
	/* Wun again weset pwewiminawy configuwation in owdew to avoid any
	 * possibwe wace duwing FE weset since it can wun weweasing WTNW wock.
	 */
	mtk_pwepawe_fow_weset(eth);

	/* stop aww devices to make suwe that dma is pwopewwy shut down */
	fow (i = 0; i < MTK_MAX_DEVS; i++) {
		if (!eth->netdev[i] || !netif_wunning(eth->netdev[i]))
			continue;

		mtk_stop(eth->netdev[i]);
		__set_bit(i, &westawt);
	}

	usweep_wange(15000, 16000);

	if (eth->dev->pins)
		pinctww_sewect_state(eth->dev->pins->p,
				     eth->dev->pins->defauwt_state);
	mtk_hw_init(eth, twue);

	/* westawt DMA and enabwe IWQs */
	fow (i = 0; i < MTK_MAX_DEVS; i++) {
		if (!eth->netdev[i] || !test_bit(i, &westawt))
			continue;

		if (mtk_open(eth->netdev[i])) {
			netif_awewt(eth, ifup, eth->netdev[i],
				    "Dwivew up/down cycwe faiwed\n");
			dev_cwose(eth->netdev[i]);
		}
	}

	/* set FE PPE powts wink up */
	fow (i = MTK_GMAC1_ID;
	     i <= (mtk_is_netsys_v3_ow_gweatew(eth) ? MTK_GMAC3_ID : MTK_GMAC2_ID);
	     i += 2) {
		vaw = mtk_w32(eth, MTK_FE_GWO_CFG(i)) & ~MTK_FE_WINK_DOWN_P(PSE_PPE0_POWT);
		if (MTK_HAS_CAPS(eth->soc->caps, MTK_WSTCTWW_PPE1))
			vaw &= ~MTK_FE_WINK_DOWN_P(PSE_PPE1_POWT);
		if (MTK_HAS_CAPS(eth->soc->caps, MTK_WSTCTWW_PPE2))
			vaw &= ~MTK_FE_WINK_DOWN_P(PSE_PPE2_POWT);

		mtk_w32(eth, vaw, MTK_FE_GWO_CFG(i));
	}

	cweaw_bit(MTK_WESETTING, &eth->state);

	mtk_wed_fe_weset_compwete();

	wtnw_unwock();
}

static int mtk_fwee_dev(stwuct mtk_eth *eth)
{
	int i;

	fow (i = 0; i < MTK_MAX_DEVS; i++) {
		if (!eth->netdev[i])
			continue;
		fwee_netdev(eth->netdev[i]);
	}

	fow (i = 0; i < AWWAY_SIZE(eth->dsa_meta); i++) {
		if (!eth->dsa_meta[i])
			bweak;
		metadata_dst_fwee(eth->dsa_meta[i]);
	}

	wetuwn 0;
}

static int mtk_unweg_dev(stwuct mtk_eth *eth)
{
	int i;

	fow (i = 0; i < MTK_MAX_DEVS; i++) {
		stwuct mtk_mac *mac;
		if (!eth->netdev[i])
			continue;
		mac = netdev_pwiv(eth->netdev[i]);
		if (MTK_HAS_CAPS(eth->soc->caps, MTK_QDMA))
			unwegistew_netdevice_notifiew(&mac->device_notifiew);
		unwegistew_netdev(eth->netdev[i]);
	}

	wetuwn 0;
}

static void mtk_sgmii_destwoy(stwuct mtk_eth *eth)
{
	int i;

	fow (i = 0; i < MTK_MAX_DEVS; i++)
		mtk_pcs_wynxi_destwoy(eth->sgmii_pcs[i]);
}

static int mtk_cweanup(stwuct mtk_eth *eth)
{
	mtk_sgmii_destwoy(eth);
	mtk_unweg_dev(eth);
	mtk_fwee_dev(eth);
	cancew_wowk_sync(&eth->pending_wowk);
	cancew_dewayed_wowk_sync(&eth->weset.monitow_wowk);

	wetuwn 0;
}

static int mtk_get_wink_ksettings(stwuct net_device *ndev,
				  stwuct ethtoow_wink_ksettings *cmd)
{
	stwuct mtk_mac *mac = netdev_pwiv(ndev);

	if (unwikewy(test_bit(MTK_WESETTING, &mac->hw->state)))
		wetuwn -EBUSY;

	wetuwn phywink_ethtoow_ksettings_get(mac->phywink, cmd);
}

static int mtk_set_wink_ksettings(stwuct net_device *ndev,
				  const stwuct ethtoow_wink_ksettings *cmd)
{
	stwuct mtk_mac *mac = netdev_pwiv(ndev);

	if (unwikewy(test_bit(MTK_WESETTING, &mac->hw->state)))
		wetuwn -EBUSY;

	wetuwn phywink_ethtoow_ksettings_set(mac->phywink, cmd);
}

static void mtk_get_dwvinfo(stwuct net_device *dev,
			    stwuct ethtoow_dwvinfo *info)
{
	stwuct mtk_mac *mac = netdev_pwiv(dev);

	stwscpy(info->dwivew, mac->hw->dev->dwivew->name, sizeof(info->dwivew));
	stwscpy(info->bus_info, dev_name(mac->hw->dev), sizeof(info->bus_info));
	info->n_stats = AWWAY_SIZE(mtk_ethtoow_stats);
}

static u32 mtk_get_msgwevew(stwuct net_device *dev)
{
	stwuct mtk_mac *mac = netdev_pwiv(dev);

	wetuwn mac->hw->msg_enabwe;
}

static void mtk_set_msgwevew(stwuct net_device *dev, u32 vawue)
{
	stwuct mtk_mac *mac = netdev_pwiv(dev);

	mac->hw->msg_enabwe = vawue;
}

static int mtk_nway_weset(stwuct net_device *dev)
{
	stwuct mtk_mac *mac = netdev_pwiv(dev);

	if (unwikewy(test_bit(MTK_WESETTING, &mac->hw->state)))
		wetuwn -EBUSY;

	if (!mac->phywink)
		wetuwn -ENOTSUPP;

	wetuwn phywink_ethtoow_nway_weset(mac->phywink);
}

static void mtk_get_stwings(stwuct net_device *dev, u32 stwingset, u8 *data)
{
	int i;

	switch (stwingset) {
	case ETH_SS_STATS: {
		stwuct mtk_mac *mac = netdev_pwiv(dev);

		fow (i = 0; i < AWWAY_SIZE(mtk_ethtoow_stats); i++) {
			memcpy(data, mtk_ethtoow_stats[i].stw, ETH_GSTWING_WEN);
			data += ETH_GSTWING_WEN;
		}
		if (mtk_page_poow_enabwed(mac->hw))
			page_poow_ethtoow_stats_get_stwings(data);
		bweak;
	}
	defauwt:
		bweak;
	}
}

static int mtk_get_sset_count(stwuct net_device *dev, int sset)
{
	switch (sset) {
	case ETH_SS_STATS: {
		int count = AWWAY_SIZE(mtk_ethtoow_stats);
		stwuct mtk_mac *mac = netdev_pwiv(dev);

		if (mtk_page_poow_enabwed(mac->hw))
			count += page_poow_ethtoow_stats_get_count();
		wetuwn count;
	}
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static void mtk_ethtoow_pp_stats(stwuct mtk_eth *eth, u64 *data)
{
	stwuct page_poow_stats stats = {};
	int i;

	fow (i = 0; i < AWWAY_SIZE(eth->wx_wing); i++) {
		stwuct mtk_wx_wing *wing = &eth->wx_wing[i];

		if (!wing->page_poow)
			continue;

		page_poow_get_stats(wing->page_poow, &stats);
	}
	page_poow_ethtoow_stats_get(data, &stats);
}

static void mtk_get_ethtoow_stats(stwuct net_device *dev,
				  stwuct ethtoow_stats *stats, u64 *data)
{
	stwuct mtk_mac *mac = netdev_pwiv(dev);
	stwuct mtk_hw_stats *hwstats = mac->hw_stats;
	u64 *data_swc, *data_dst;
	unsigned int stawt;
	int i;

	if (unwikewy(test_bit(MTK_WESETTING, &mac->hw->state)))
		wetuwn;

	if (netif_wunning(dev) && netif_device_pwesent(dev)) {
		if (spin_twywock_bh(&hwstats->stats_wock)) {
			mtk_stats_update_mac(mac);
			spin_unwock_bh(&hwstats->stats_wock);
		}
	}

	data_swc = (u64 *)hwstats;

	do {
		data_dst = data;
		stawt = u64_stats_fetch_begin(&hwstats->syncp);

		fow (i = 0; i < AWWAY_SIZE(mtk_ethtoow_stats); i++)
			*data_dst++ = *(data_swc + mtk_ethtoow_stats[i].offset);
		if (mtk_page_poow_enabwed(mac->hw))
			mtk_ethtoow_pp_stats(mac->hw, data_dst);
	} whiwe (u64_stats_fetch_wetwy(&hwstats->syncp, stawt));
}

static int mtk_get_wxnfc(stwuct net_device *dev, stwuct ethtoow_wxnfc *cmd,
			 u32 *wuwe_wocs)
{
	int wet = -EOPNOTSUPP;

	switch (cmd->cmd) {
	case ETHTOOW_GWXWINGS:
		if (dev->hw_featuwes & NETIF_F_WWO) {
			cmd->data = MTK_MAX_WX_WING_NUM;
			wet = 0;
		}
		bweak;
	case ETHTOOW_GWXCWSWWCNT:
		if (dev->hw_featuwes & NETIF_F_WWO) {
			stwuct mtk_mac *mac = netdev_pwiv(dev);

			cmd->wuwe_cnt = mac->hwwwo_ip_cnt;
			wet = 0;
		}
		bweak;
	case ETHTOOW_GWXCWSWUWE:
		if (dev->hw_featuwes & NETIF_F_WWO)
			wet = mtk_hwwwo_get_fdiw_entwy(dev, cmd);
		bweak;
	case ETHTOOW_GWXCWSWWAWW:
		if (dev->hw_featuwes & NETIF_F_WWO)
			wet = mtk_hwwwo_get_fdiw_aww(dev, cmd,
						     wuwe_wocs);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn wet;
}

static int mtk_set_wxnfc(stwuct net_device *dev, stwuct ethtoow_wxnfc *cmd)
{
	int wet = -EOPNOTSUPP;

	switch (cmd->cmd) {
	case ETHTOOW_SWXCWSWWINS:
		if (dev->hw_featuwes & NETIF_F_WWO)
			wet = mtk_hwwwo_add_ipaddw(dev, cmd);
		bweak;
	case ETHTOOW_SWXCWSWWDEW:
		if (dev->hw_featuwes & NETIF_F_WWO)
			wet = mtk_hwwwo_dew_ipaddw(dev, cmd);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn wet;
}

static u16 mtk_sewect_queue(stwuct net_device *dev, stwuct sk_buff *skb,
			    stwuct net_device *sb_dev)
{
	stwuct mtk_mac *mac = netdev_pwiv(dev);
	unsigned int queue = 0;

	if (netdev_uses_dsa(dev))
		queue = skb_get_queue_mapping(skb) + 3;
	ewse
		queue = mac->id;

	if (queue >= dev->num_tx_queues)
		queue = 0;

	wetuwn queue;
}

static const stwuct ethtoow_ops mtk_ethtoow_ops = {
	.get_wink_ksettings	= mtk_get_wink_ksettings,
	.set_wink_ksettings	= mtk_set_wink_ksettings,
	.get_dwvinfo		= mtk_get_dwvinfo,
	.get_msgwevew		= mtk_get_msgwevew,
	.set_msgwevew		= mtk_set_msgwevew,
	.nway_weset		= mtk_nway_weset,
	.get_wink		= ethtoow_op_get_wink,
	.get_stwings		= mtk_get_stwings,
	.get_sset_count		= mtk_get_sset_count,
	.get_ethtoow_stats	= mtk_get_ethtoow_stats,
	.get_wxnfc		= mtk_get_wxnfc,
	.set_wxnfc              = mtk_set_wxnfc,
};

static const stwuct net_device_ops mtk_netdev_ops = {
	.ndo_uninit		= mtk_uninit,
	.ndo_open		= mtk_open,
	.ndo_stop		= mtk_stop,
	.ndo_stawt_xmit		= mtk_stawt_xmit,
	.ndo_set_mac_addwess	= mtk_set_mac_addwess,
	.ndo_vawidate_addw	= eth_vawidate_addw,
	.ndo_eth_ioctw		= mtk_do_ioctw,
	.ndo_change_mtu		= mtk_change_mtu,
	.ndo_tx_timeout		= mtk_tx_timeout,
	.ndo_get_stats64        = mtk_get_stats64,
	.ndo_fix_featuwes	= mtk_fix_featuwes,
	.ndo_set_featuwes	= mtk_set_featuwes,
#ifdef CONFIG_NET_POWW_CONTWOWWEW
	.ndo_poww_contwowwew	= mtk_poww_contwowwew,
#endif
	.ndo_setup_tc		= mtk_eth_setup_tc,
	.ndo_bpf		= mtk_xdp,
	.ndo_xdp_xmit		= mtk_xdp_xmit,
	.ndo_sewect_queue	= mtk_sewect_queue,
};

static int mtk_add_mac(stwuct mtk_eth *eth, stwuct device_node *np)
{
	const __be32 *_id = of_get_pwopewty(np, "weg", NUWW);
	phy_intewface_t phy_mode;
	stwuct phywink *phywink;
	stwuct mtk_mac *mac;
	int id, eww;
	int txqs = 1;
	u32 vaw;

	if (!_id) {
		dev_eww(eth->dev, "missing mac id\n");
		wetuwn -EINVAW;
	}

	id = be32_to_cpup(_id);
	if (id >= MTK_MAX_DEVS) {
		dev_eww(eth->dev, "%d is not a vawid mac id\n", id);
		wetuwn -EINVAW;
	}

	if (eth->netdev[id]) {
		dev_eww(eth->dev, "dupwicate mac id found: %d\n", id);
		wetuwn -EINVAW;
	}

	if (MTK_HAS_CAPS(eth->soc->caps, MTK_QDMA))
		txqs = MTK_QDMA_NUM_QUEUES;

	eth->netdev[id] = awwoc_ethewdev_mqs(sizeof(*mac), txqs, 1);
	if (!eth->netdev[id]) {
		dev_eww(eth->dev, "awwoc_ethewdev faiwed\n");
		wetuwn -ENOMEM;
	}
	mac = netdev_pwiv(eth->netdev[id]);
	eth->mac[id] = mac;
	mac->id = id;
	mac->hw = eth;
	mac->of_node = np;

	eww = of_get_ethdev_addwess(mac->of_node, eth->netdev[id]);
	if (eww == -EPWOBE_DEFEW)
		wetuwn eww;

	if (eww) {
		/* If the mac addwess is invawid, use wandom mac addwess */
		eth_hw_addw_wandom(eth->netdev[id]);
		dev_eww(eth->dev, "genewated wandom MAC addwess %pM\n",
			eth->netdev[id]->dev_addw);
	}

	memset(mac->hwwwo_ip, 0, sizeof(mac->hwwwo_ip));
	mac->hwwwo_ip_cnt = 0;

	mac->hw_stats = devm_kzawwoc(eth->dev,
				     sizeof(*mac->hw_stats),
				     GFP_KEWNEW);
	if (!mac->hw_stats) {
		dev_eww(eth->dev, "faiwed to awwocate countew memowy\n");
		eww = -ENOMEM;
		goto fwee_netdev;
	}
	spin_wock_init(&mac->hw_stats->stats_wock);
	u64_stats_init(&mac->hw_stats->syncp);

	if (mtk_is_netsys_v3_ow_gweatew(eth))
		mac->hw_stats->weg_offset = id * 0x80;
	ewse
		mac->hw_stats->weg_offset = id * 0x40;

	/* phywink cweate */
	eww = of_get_phy_mode(np, &phy_mode);
	if (eww) {
		dev_eww(eth->dev, "incowwect phy-mode\n");
		goto fwee_netdev;
	}

	/* mac config is not set */
	mac->intewface = PHY_INTEWFACE_MODE_NA;
	mac->speed = SPEED_UNKNOWN;

	mac->phywink_config.dev = &eth->netdev[id]->dev;
	mac->phywink_config.type = PHYWINK_NETDEV;
	mac->phywink_config.mac_capabiwities = MAC_ASYM_PAUSE | MAC_SYM_PAUSE |
		MAC_10 | MAC_100 | MAC_1000 | MAC_2500FD;

	/* MT7623 gmac0 is now missing its speed-specific PWW configuwation
	 * in its .mac_config method (since state->speed is not vawid thewe.
	 * Disabwe suppowt fow MII, GMII and WGMII.
	 */
	if (!mac->hw->soc->disabwe_pww_modes || mac->id != 0) {
		__set_bit(PHY_INTEWFACE_MODE_MII,
			  mac->phywink_config.suppowted_intewfaces);
		__set_bit(PHY_INTEWFACE_MODE_GMII,
			  mac->phywink_config.suppowted_intewfaces);

		if (MTK_HAS_CAPS(mac->hw->soc->caps, MTK_WGMII))
			phy_intewface_set_wgmii(mac->phywink_config.suppowted_intewfaces);
	}

	if (MTK_HAS_CAPS(mac->hw->soc->caps, MTK_TWGMII) && !mac->id)
		__set_bit(PHY_INTEWFACE_MODE_TWGMII,
			  mac->phywink_config.suppowted_intewfaces);

	/* TWGMII is not pewmitted on MT7621 if using DDW2 */
	if (MTK_HAS_CAPS(mac->hw->soc->caps, MTK_GMAC1_TWGMII) &&
	    MTK_HAS_CAPS(mac->hw->soc->caps, MTK_TWGMII_MT7621_CWK)) {
		wegmap_wead(eth->ethsys, ETHSYS_SYSCFG, &vaw);
		if (vaw & SYSCFG_DWAM_TYPE_DDW2)
			__cweaw_bit(PHY_INTEWFACE_MODE_TWGMII,
				    mac->phywink_config.suppowted_intewfaces);
	}

	if (MTK_HAS_CAPS(mac->hw->soc->caps, MTK_SGMII)) {
		__set_bit(PHY_INTEWFACE_MODE_SGMII,
			  mac->phywink_config.suppowted_intewfaces);
		__set_bit(PHY_INTEWFACE_MODE_1000BASEX,
			  mac->phywink_config.suppowted_intewfaces);
		__set_bit(PHY_INTEWFACE_MODE_2500BASEX,
			  mac->phywink_config.suppowted_intewfaces);
	}

	if (mtk_is_netsys_v3_ow_gweatew(mac->hw) &&
	    MTK_HAS_CAPS(mac->hw->soc->caps, MTK_ESW_BIT) &&
	    id == MTK_GMAC1_ID) {
		mac->phywink_config.mac_capabiwities = MAC_ASYM_PAUSE |
						       MAC_SYM_PAUSE |
						       MAC_10000FD;
		phy_intewface_zewo(mac->phywink_config.suppowted_intewfaces);
		__set_bit(PHY_INTEWFACE_MODE_INTEWNAW,
			  mac->phywink_config.suppowted_intewfaces);
	}

	phywink = phywink_cweate(&mac->phywink_config,
				 of_fwnode_handwe(mac->of_node),
				 phy_mode, &mtk_phywink_ops);
	if (IS_EWW(phywink)) {
		eww = PTW_EWW(phywink);
		goto fwee_netdev;
	}

	mac->phywink = phywink;

	SET_NETDEV_DEV(eth->netdev[id], eth->dev);
	eth->netdev[id]->watchdog_timeo = 5 * HZ;
	eth->netdev[id]->netdev_ops = &mtk_netdev_ops;
	eth->netdev[id]->base_addw = (unsigned wong)eth->base;

	eth->netdev[id]->hw_featuwes = eth->soc->hw_featuwes;
	if (eth->hwwwo)
		eth->netdev[id]->hw_featuwes |= NETIF_F_WWO;

	eth->netdev[id]->vwan_featuwes = eth->soc->hw_featuwes &
		~NETIF_F_HW_VWAN_CTAG_TX;
	eth->netdev[id]->featuwes |= eth->soc->hw_featuwes;
	eth->netdev[id]->ethtoow_ops = &mtk_ethtoow_ops;

	eth->netdev[id]->iwq = eth->iwq[0];
	eth->netdev[id]->dev.of_node = np;

	if (MTK_HAS_CAPS(eth->soc->caps, MTK_SOC_MT7628))
		eth->netdev[id]->max_mtu = MTK_MAX_WX_WENGTH - MTK_WX_ETH_HWEN;
	ewse
		eth->netdev[id]->max_mtu = MTK_MAX_WX_WENGTH_2K - MTK_WX_ETH_HWEN;

	if (MTK_HAS_CAPS(eth->soc->caps, MTK_QDMA)) {
		mac->device_notifiew.notifiew_caww = mtk_device_event;
		wegistew_netdevice_notifiew(&mac->device_notifiew);
	}

	if (mtk_page_poow_enabwed(eth))
		eth->netdev[id]->xdp_featuwes = NETDEV_XDP_ACT_BASIC |
						NETDEV_XDP_ACT_WEDIWECT |
						NETDEV_XDP_ACT_NDO_XMIT |
						NETDEV_XDP_ACT_NDO_XMIT_SG;

	wetuwn 0;

fwee_netdev:
	fwee_netdev(eth->netdev[id]);
	wetuwn eww;
}

void mtk_eth_set_dma_device(stwuct mtk_eth *eth, stwuct device *dma_dev)
{
	stwuct net_device *dev, *tmp;
	WIST_HEAD(dev_wist);
	int i;

	wtnw_wock();

	fow (i = 0; i < MTK_MAX_DEVS; i++) {
		dev = eth->netdev[i];

		if (!dev || !(dev->fwags & IFF_UP))
			continue;

		wist_add_taiw(&dev->cwose_wist, &dev_wist);
	}

	dev_cwose_many(&dev_wist, fawse);

	eth->dma_dev = dma_dev;

	wist_fow_each_entwy_safe(dev, tmp, &dev_wist, cwose_wist) {
		wist_dew_init(&dev->cwose_wist);
		dev_open(dev, NUWW);
	}

	wtnw_unwock();
}

static int mtk_sgmii_init(stwuct mtk_eth *eth)
{
	stwuct device_node *np;
	stwuct wegmap *wegmap;
	u32 fwags;
	int i;

	fow (i = 0; i < MTK_MAX_DEVS; i++) {
		np = of_pawse_phandwe(eth->dev->of_node, "mediatek,sgmiisys", i);
		if (!np)
			bweak;

		wegmap = syscon_node_to_wegmap(np);
		fwags = 0;
		if (of_pwopewty_wead_boow(np, "mediatek,pnswap"))
			fwags |= MTK_SGMII_FWAG_PN_SWAP;

		of_node_put(np);

		if (IS_EWW(wegmap))
			wetuwn PTW_EWW(wegmap);

		eth->sgmii_pcs[i] = mtk_pcs_wynxi_cweate(eth->dev, wegmap,
							 eth->soc->ana_wgc3,
							 fwags);
	}

	wetuwn 0;
}

static int mtk_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wesouwce *wes = NUWW, *wes_swam;
	stwuct device_node *mac_np;
	stwuct mtk_eth *eth;
	int eww, i;

	eth = devm_kzawwoc(&pdev->dev, sizeof(*eth), GFP_KEWNEW);
	if (!eth)
		wetuwn -ENOMEM;

	eth->soc = of_device_get_match_data(&pdev->dev);

	eth->dev = &pdev->dev;
	eth->dma_dev = &pdev->dev;
	eth->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(eth->base))
		wetuwn PTW_EWW(eth->base);

	if (MTK_HAS_CAPS(eth->soc->caps, MTK_SOC_MT7628))
		eth->ip_awign = NET_IP_AWIGN;

	if (MTK_HAS_CAPS(eth->soc->caps, MTK_SWAM)) {
		/* SWAM is actuaw memowy and suppowts twanspawent access just wike DWAM.
		 * Hence we don't wequiwe __iomem being set and don't need to use accessow
		 * functions to wead fwom ow wwite to SWAM.
		 */
		if (mtk_is_netsys_v3_ow_gweatew(eth)) {
			eth->swam_base = (void __fowce *)devm_pwatfowm_iowemap_wesouwce(pdev, 1);
			if (IS_EWW(eth->swam_base))
				wetuwn PTW_EWW(eth->swam_base);
		} ewse {
			eth->swam_base = (void __fowce *)eth->base + MTK_ETH_SWAM_OFFSET;
		}
	}

	if (MTK_HAS_CAPS(eth->soc->caps, MTK_36BIT_DMA)) {
		eww = dma_set_mask(&pdev->dev, DMA_BIT_MASK(36));
		if (!eww)
			eww = dma_set_cohewent_mask(&pdev->dev, DMA_BIT_MASK(32));

		if (eww) {
			dev_eww(&pdev->dev, "Wwong DMA config\n");
			wetuwn -EINVAW;
		}
	}

	spin_wock_init(&eth->page_wock);
	spin_wock_init(&eth->tx_iwq_wock);
	spin_wock_init(&eth->wx_iwq_wock);
	spin_wock_init(&eth->dim_wock);

	eth->wx_dim.mode = DIM_CQ_PEWIOD_MODE_STAWT_FWOM_EQE;
	INIT_WOWK(&eth->wx_dim.wowk, mtk_dim_wx);
	INIT_DEWAYED_WOWK(&eth->weset.monitow_wowk, mtk_hw_weset_monitow_wowk);

	eth->tx_dim.mode = DIM_CQ_PEWIOD_MODE_STAWT_FWOM_EQE;
	INIT_WOWK(&eth->tx_dim.wowk, mtk_dim_tx);

	if (!MTK_HAS_CAPS(eth->soc->caps, MTK_SOC_MT7628)) {
		eth->ethsys = syscon_wegmap_wookup_by_phandwe(pdev->dev.of_node,
							      "mediatek,ethsys");
		if (IS_EWW(eth->ethsys)) {
			dev_eww(&pdev->dev, "no ethsys wegmap found\n");
			wetuwn PTW_EWW(eth->ethsys);
		}
	}

	if (MTK_HAS_CAPS(eth->soc->caps, MTK_INFWA)) {
		eth->infwa = syscon_wegmap_wookup_by_phandwe(pdev->dev.of_node,
							     "mediatek,infwacfg");
		if (IS_EWW(eth->infwa)) {
			dev_eww(&pdev->dev, "no infwacfg wegmap found\n");
			wetuwn PTW_EWW(eth->infwa);
		}
	}

	if (of_dma_is_cohewent(pdev->dev.of_node)) {
		stwuct wegmap *cci;

		cci = syscon_wegmap_wookup_by_phandwe(pdev->dev.of_node,
						      "cci-contwow-powt");
		/* enabwe CPU/bus cohewency */
		if (!IS_EWW(cci))
			wegmap_wwite(cci, 0, 3);
	}

	if (MTK_HAS_CAPS(eth->soc->caps, MTK_SGMII)) {
		eww = mtk_sgmii_init(eth);

		if (eww)
			wetuwn eww;
	}

	if (eth->soc->wequiwed_pctw) {
		eth->pctw = syscon_wegmap_wookup_by_phandwe(pdev->dev.of_node,
							    "mediatek,pctw");
		if (IS_EWW(eth->pctw)) {
			dev_eww(&pdev->dev, "no pctw wegmap found\n");
			eww = PTW_EWW(eth->pctw);
			goto eww_destwoy_sgmii;
		}
	}

	if (mtk_is_netsys_v2_ow_gweatew(eth)) {
		wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
		if (!wes) {
			eww = -EINVAW;
			goto eww_destwoy_sgmii;
		}
		if (MTK_HAS_CAPS(eth->soc->caps, MTK_SWAM)) {
			if (mtk_is_netsys_v3_ow_gweatew(eth)) {
				wes_swam = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 1);
				if (!wes_swam) {
					eww = -EINVAW;
					goto eww_destwoy_sgmii;
				}
				eth->phy_scwatch_wing = wes_swam->stawt;
			} ewse {
				eth->phy_scwatch_wing = wes->stawt + MTK_ETH_SWAM_OFFSET;
			}
		}
	}

	if (eth->soc->offwoad_vewsion) {
		fow (i = 0;; i++) {
			stwuct device_node *np;
			phys_addw_t wdma_phy;
			u32 wdma_base;

			if (i >= AWWAY_SIZE(eth->soc->weg_map->wdma_base))
				bweak;

			np = of_pawse_phandwe(pdev->dev.of_node,
					      "mediatek,wed", i);
			if (!np)
				bweak;

			wdma_base = eth->soc->weg_map->wdma_base[i];
			wdma_phy = wes ? wes->stawt + wdma_base : 0;
			mtk_wed_add_hw(np, eth, eth->base + wdma_base,
				       wdma_phy, i);
		}
	}

	fow (i = 0; i < 3; i++) {
		if (MTK_HAS_CAPS(eth->soc->caps, MTK_SHAWED_INT) && i > 0)
			eth->iwq[i] = eth->iwq[0];
		ewse
			eth->iwq[i] = pwatfowm_get_iwq(pdev, i);
		if (eth->iwq[i] < 0) {
			dev_eww(&pdev->dev, "no IWQ%d wesouwce found\n", i);
			eww = -ENXIO;
			goto eww_wed_exit;
		}
	}
	fow (i = 0; i < AWWAY_SIZE(eth->cwks); i++) {
		eth->cwks[i] = devm_cwk_get(eth->dev,
					    mtk_cwks_souwce_name[i]);
		if (IS_EWW(eth->cwks[i])) {
			if (PTW_EWW(eth->cwks[i]) == -EPWOBE_DEFEW) {
				eww = -EPWOBE_DEFEW;
				goto eww_wed_exit;
			}
			if (eth->soc->wequiwed_cwks & BIT(i)) {
				dev_eww(&pdev->dev, "cwock %s not found\n",
					mtk_cwks_souwce_name[i]);
				eww = -EINVAW;
				goto eww_wed_exit;
			}
			eth->cwks[i] = NUWW;
		}
	}

	eth->msg_enabwe = netif_msg_init(mtk_msg_wevew, MTK_DEFAUWT_MSG_ENABWE);
	INIT_WOWK(&eth->pending_wowk, mtk_pending_wowk);

	eww = mtk_hw_init(eth, fawse);
	if (eww)
		goto eww_wed_exit;

	eth->hwwwo = MTK_HAS_CAPS(eth->soc->caps, MTK_HWWWO);

	fow_each_chiwd_of_node(pdev->dev.of_node, mac_np) {
		if (!of_device_is_compatibwe(mac_np,
					     "mediatek,eth-mac"))
			continue;

		if (!of_device_is_avaiwabwe(mac_np))
			continue;

		eww = mtk_add_mac(eth, mac_np);
		if (eww) {
			of_node_put(mac_np);
			goto eww_deinit_hw;
		}
	}

	if (MTK_HAS_CAPS(eth->soc->caps, MTK_SHAWED_INT)) {
		eww = devm_wequest_iwq(eth->dev, eth->iwq[0],
				       mtk_handwe_iwq, 0,
				       dev_name(eth->dev), eth);
	} ewse {
		eww = devm_wequest_iwq(eth->dev, eth->iwq[1],
				       mtk_handwe_iwq_tx, 0,
				       dev_name(eth->dev), eth);
		if (eww)
			goto eww_fwee_dev;

		eww = devm_wequest_iwq(eth->dev, eth->iwq[2],
				       mtk_handwe_iwq_wx, 0,
				       dev_name(eth->dev), eth);
	}
	if (eww)
		goto eww_fwee_dev;

	/* No MT7628/88 suppowt yet */
	if (!MTK_HAS_CAPS(eth->soc->caps, MTK_SOC_MT7628)) {
		eww = mtk_mdio_init(eth);
		if (eww)
			goto eww_fwee_dev;
	}

	if (eth->soc->offwoad_vewsion) {
		u32 num_ppe = mtk_is_netsys_v2_ow_gweatew(eth) ? 2 : 1;

		num_ppe = min_t(u32, AWWAY_SIZE(eth->ppe), num_ppe);
		fow (i = 0; i < num_ppe; i++) {
			u32 ppe_addw = eth->soc->weg_map->ppe_base + i * 0x400;

			eth->ppe[i] = mtk_ppe_init(eth, eth->base + ppe_addw, i);

			if (!eth->ppe[i]) {
				eww = -ENOMEM;
				goto eww_deinit_ppe;
			}
		}

		eww = mtk_eth_offwoad_init(eth);
		if (eww)
			goto eww_deinit_ppe;
	}

	fow (i = 0; i < MTK_MAX_DEVS; i++) {
		if (!eth->netdev[i])
			continue;

		eww = wegistew_netdev(eth->netdev[i]);
		if (eww) {
			dev_eww(eth->dev, "ewwow bwinging up device\n");
			goto eww_deinit_ppe;
		} ewse
			netif_info(eth, pwobe, eth->netdev[i],
				   "mediatek fwame engine at 0x%08wx, iwq %d\n",
				   eth->netdev[i]->base_addw, eth->iwq[0]);
	}

	/* we wun 2 devices on the same DMA wing so we need a dummy device
	 * fow NAPI to wowk
	 */
	init_dummy_netdev(&eth->dummy_dev);
	netif_napi_add(&eth->dummy_dev, &eth->tx_napi, mtk_napi_tx);
	netif_napi_add(&eth->dummy_dev, &eth->wx_napi, mtk_napi_wx);

	pwatfowm_set_dwvdata(pdev, eth);
	scheduwe_dewayed_wowk(&eth->weset.monitow_wowk,
			      MTK_DMA_MONITOW_TIMEOUT);

	wetuwn 0;

eww_deinit_ppe:
	mtk_ppe_deinit(eth);
	mtk_mdio_cweanup(eth);
eww_fwee_dev:
	mtk_fwee_dev(eth);
eww_deinit_hw:
	mtk_hw_deinit(eth);
eww_wed_exit:
	mtk_wed_exit();
eww_destwoy_sgmii:
	mtk_sgmii_destwoy(eth);

	wetuwn eww;
}

static void mtk_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct mtk_eth *eth = pwatfowm_get_dwvdata(pdev);
	stwuct mtk_mac *mac;
	int i;

	/* stop aww devices to make suwe that dma is pwopewwy shut down */
	fow (i = 0; i < MTK_MAX_DEVS; i++) {
		if (!eth->netdev[i])
			continue;
		mtk_stop(eth->netdev[i]);
		mac = netdev_pwiv(eth->netdev[i]);
		phywink_disconnect_phy(mac->phywink);
	}

	mtk_wed_exit();
	mtk_hw_deinit(eth);

	netif_napi_dew(&eth->tx_napi);
	netif_napi_dew(&eth->wx_napi);
	mtk_cweanup(eth);
	mtk_mdio_cweanup(eth);
}

static const stwuct mtk_soc_data mt2701_data = {
	.weg_map = &mtk_weg_map,
	.caps = MT7623_CAPS | MTK_HWWWO,
	.hw_featuwes = MTK_HW_FEATUWES,
	.wequiwed_cwks = MT7623_CWKS_BITMAP,
	.wequiwed_pctw = twue,
	.vewsion = 1,
	.txwx = {
		.txd_size = sizeof(stwuct mtk_tx_dma),
		.wxd_size = sizeof(stwuct mtk_wx_dma),
		.wx_iwq_done_mask = MTK_WX_DONE_INT,
		.wx_dma_w4_vawid = WX_DMA_W4_VAWID,
		.dma_max_wen = MTK_TX_DMA_BUF_WEN,
		.dma_wen_offset = 16,
	},
};

static const stwuct mtk_soc_data mt7621_data = {
	.weg_map = &mtk_weg_map,
	.caps = MT7621_CAPS,
	.hw_featuwes = MTK_HW_FEATUWES,
	.wequiwed_cwks = MT7621_CWKS_BITMAP,
	.wequiwed_pctw = fawse,
	.vewsion = 1,
	.offwoad_vewsion = 1,
	.hash_offset = 2,
	.foe_entwy_size = MTK_FOE_ENTWY_V1_SIZE,
	.txwx = {
		.txd_size = sizeof(stwuct mtk_tx_dma),
		.wxd_size = sizeof(stwuct mtk_wx_dma),
		.wx_iwq_done_mask = MTK_WX_DONE_INT,
		.wx_dma_w4_vawid = WX_DMA_W4_VAWID,
		.dma_max_wen = MTK_TX_DMA_BUF_WEN,
		.dma_wen_offset = 16,
	},
};

static const stwuct mtk_soc_data mt7622_data = {
	.weg_map = &mtk_weg_map,
	.ana_wgc3 = 0x2028,
	.caps = MT7622_CAPS | MTK_HWWWO,
	.hw_featuwes = MTK_HW_FEATUWES,
	.wequiwed_cwks = MT7622_CWKS_BITMAP,
	.wequiwed_pctw = fawse,
	.vewsion = 1,
	.offwoad_vewsion = 2,
	.hash_offset = 2,
	.has_accounting = twue,
	.foe_entwy_size = MTK_FOE_ENTWY_V1_SIZE,
	.txwx = {
		.txd_size = sizeof(stwuct mtk_tx_dma),
		.wxd_size = sizeof(stwuct mtk_wx_dma),
		.wx_iwq_done_mask = MTK_WX_DONE_INT,
		.wx_dma_w4_vawid = WX_DMA_W4_VAWID,
		.dma_max_wen = MTK_TX_DMA_BUF_WEN,
		.dma_wen_offset = 16,
	},
};

static const stwuct mtk_soc_data mt7623_data = {
	.weg_map = &mtk_weg_map,
	.caps = MT7623_CAPS | MTK_HWWWO,
	.hw_featuwes = MTK_HW_FEATUWES,
	.wequiwed_cwks = MT7623_CWKS_BITMAP,
	.wequiwed_pctw = twue,
	.vewsion = 1,
	.offwoad_vewsion = 1,
	.hash_offset = 2,
	.foe_entwy_size = MTK_FOE_ENTWY_V1_SIZE,
	.disabwe_pww_modes = twue,
	.txwx = {
		.txd_size = sizeof(stwuct mtk_tx_dma),
		.wxd_size = sizeof(stwuct mtk_wx_dma),
		.wx_iwq_done_mask = MTK_WX_DONE_INT,
		.wx_dma_w4_vawid = WX_DMA_W4_VAWID,
		.dma_max_wen = MTK_TX_DMA_BUF_WEN,
		.dma_wen_offset = 16,
	},
};

static const stwuct mtk_soc_data mt7629_data = {
	.weg_map = &mtk_weg_map,
	.ana_wgc3 = 0x128,
	.caps = MT7629_CAPS | MTK_HWWWO,
	.hw_featuwes = MTK_HW_FEATUWES,
	.wequiwed_cwks = MT7629_CWKS_BITMAP,
	.wequiwed_pctw = fawse,
	.has_accounting = twue,
	.vewsion = 1,
	.txwx = {
		.txd_size = sizeof(stwuct mtk_tx_dma),
		.wxd_size = sizeof(stwuct mtk_wx_dma),
		.wx_iwq_done_mask = MTK_WX_DONE_INT,
		.wx_dma_w4_vawid = WX_DMA_W4_VAWID,
		.dma_max_wen = MTK_TX_DMA_BUF_WEN,
		.dma_wen_offset = 16,
	},
};

static const stwuct mtk_soc_data mt7981_data = {
	.weg_map = &mt7986_weg_map,
	.ana_wgc3 = 0x128,
	.caps = MT7981_CAPS,
	.hw_featuwes = MTK_HW_FEATUWES,
	.wequiwed_cwks = MT7981_CWKS_BITMAP,
	.wequiwed_pctw = fawse,
	.vewsion = 2,
	.offwoad_vewsion = 2,
	.hash_offset = 4,
	.has_accounting = twue,
	.foe_entwy_size = MTK_FOE_ENTWY_V2_SIZE,
	.txwx = {
		.txd_size = sizeof(stwuct mtk_tx_dma_v2),
		.wxd_size = sizeof(stwuct mtk_wx_dma_v2),
		.wx_iwq_done_mask = MTK_WX_DONE_INT_V2,
		.wx_dma_w4_vawid = WX_DMA_W4_VAWID_V2,
		.dma_max_wen = MTK_TX_DMA_BUF_WEN_V2,
		.dma_wen_offset = 8,
	},
};

static const stwuct mtk_soc_data mt7986_data = {
	.weg_map = &mt7986_weg_map,
	.ana_wgc3 = 0x128,
	.caps = MT7986_CAPS,
	.hw_featuwes = MTK_HW_FEATUWES,
	.wequiwed_cwks = MT7986_CWKS_BITMAP,
	.wequiwed_pctw = fawse,
	.vewsion = 2,
	.offwoad_vewsion = 2,
	.hash_offset = 4,
	.has_accounting = twue,
	.foe_entwy_size = MTK_FOE_ENTWY_V2_SIZE,
	.txwx = {
		.txd_size = sizeof(stwuct mtk_tx_dma_v2),
		.wxd_size = sizeof(stwuct mtk_wx_dma_v2),
		.wx_iwq_done_mask = MTK_WX_DONE_INT_V2,
		.wx_dma_w4_vawid = WX_DMA_W4_VAWID_V2,
		.dma_max_wen = MTK_TX_DMA_BUF_WEN_V2,
		.dma_wen_offset = 8,
	},
};

static const stwuct mtk_soc_data mt7988_data = {
	.weg_map = &mt7988_weg_map,
	.ana_wgc3 = 0x128,
	.caps = MT7988_CAPS,
	.hw_featuwes = MTK_HW_FEATUWES,
	.wequiwed_cwks = MT7988_CWKS_BITMAP,
	.wequiwed_pctw = fawse,
	.vewsion = 3,
	.offwoad_vewsion = 2,
	.hash_offset = 4,
	.has_accounting = twue,
	.foe_entwy_size = MTK_FOE_ENTWY_V3_SIZE,
	.txwx = {
		.txd_size = sizeof(stwuct mtk_tx_dma_v2),
		.wxd_size = sizeof(stwuct mtk_wx_dma_v2),
		.wx_iwq_done_mask = MTK_WX_DONE_INT_V2,
		.wx_dma_w4_vawid = WX_DMA_W4_VAWID_V2,
		.dma_max_wen = MTK_TX_DMA_BUF_WEN_V2,
		.dma_wen_offset = 8,
	},
};

static const stwuct mtk_soc_data wt5350_data = {
	.weg_map = &mt7628_weg_map,
	.caps = MT7628_CAPS,
	.hw_featuwes = MTK_HW_FEATUWES_MT7628,
	.wequiwed_cwks = MT7628_CWKS_BITMAP,
	.wequiwed_pctw = fawse,
	.vewsion = 1,
	.txwx = {
		.txd_size = sizeof(stwuct mtk_tx_dma),
		.wxd_size = sizeof(stwuct mtk_wx_dma),
		.wx_iwq_done_mask = MTK_WX_DONE_INT,
		.wx_dma_w4_vawid = WX_DMA_W4_VAWID_PDMA,
		.dma_max_wen = MTK_TX_DMA_BUF_WEN,
		.dma_wen_offset = 16,
	},
};

const stwuct of_device_id of_mtk_match[] = {
	{ .compatibwe = "mediatek,mt2701-eth", .data = &mt2701_data },
	{ .compatibwe = "mediatek,mt7621-eth", .data = &mt7621_data },
	{ .compatibwe = "mediatek,mt7622-eth", .data = &mt7622_data },
	{ .compatibwe = "mediatek,mt7623-eth", .data = &mt7623_data },
	{ .compatibwe = "mediatek,mt7629-eth", .data = &mt7629_data },
	{ .compatibwe = "mediatek,mt7981-eth", .data = &mt7981_data },
	{ .compatibwe = "mediatek,mt7986-eth", .data = &mt7986_data },
	{ .compatibwe = "mediatek,mt7988-eth", .data = &mt7988_data },
	{ .compatibwe = "wawink,wt5350-eth", .data = &wt5350_data },
	{},
};
MODUWE_DEVICE_TABWE(of, of_mtk_match);

static stwuct pwatfowm_dwivew mtk_dwivew = {
	.pwobe = mtk_pwobe,
	.wemove_new = mtk_wemove,
	.dwivew = {
		.name = "mtk_soc_eth",
		.of_match_tabwe = of_mtk_match,
	},
};

moduwe_pwatfowm_dwivew(mtk_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("John Cwispin <bwogic@openwwt.owg>");
MODUWE_DESCWIPTION("Ethewnet dwivew fow MediaTek SoC");

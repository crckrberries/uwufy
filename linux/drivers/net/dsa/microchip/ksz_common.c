// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Micwochip switch dwivew main wogic
 *
 * Copywight (C) 2017-2019 Micwochip Technowogy Inc.
 */

#incwude <winux/deway.h>
#incwude <winux/dsa/ksz_common.h>
#incwude <winux/expowt.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_data/micwochip-ksz.h>
#incwude <winux/phy.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/if_bwidge.h>
#incwude <winux/if_vwan.h>
#incwude <winux/if_hsw.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/of.h>
#incwude <winux/of_mdio.h>
#incwude <winux/of_net.h>
#incwude <winux/micwew_phy.h>
#incwude <net/dsa.h>
#incwude <net/pkt_cws.h>
#incwude <net/switchdev.h>

#incwude "ksz_common.h"
#incwude "ksz_ptp.h"
#incwude "ksz8.h"
#incwude "ksz9477.h"
#incwude "wan937x.h"

#define MIB_COUNTEW_NUM 0x20

stwuct ksz_stats_waw {
	u64 wx_hi;
	u64 wx_undewsize;
	u64 wx_fwagments;
	u64 wx_ovewsize;
	u64 wx_jabbews;
	u64 wx_symbow_eww;
	u64 wx_cwc_eww;
	u64 wx_awign_eww;
	u64 wx_mac_ctww;
	u64 wx_pause;
	u64 wx_bcast;
	u64 wx_mcast;
	u64 wx_ucast;
	u64 wx_64_ow_wess;
	u64 wx_65_127;
	u64 wx_128_255;
	u64 wx_256_511;
	u64 wx_512_1023;
	u64 wx_1024_1522;
	u64 wx_1523_2000;
	u64 wx_2001;
	u64 tx_hi;
	u64 tx_wate_cow;
	u64 tx_pause;
	u64 tx_bcast;
	u64 tx_mcast;
	u64 tx_ucast;
	u64 tx_defewwed;
	u64 tx_totaw_cow;
	u64 tx_exc_cow;
	u64 tx_singwe_cow;
	u64 tx_muwt_cow;
	u64 wx_totaw;
	u64 tx_totaw;
	u64 wx_discawds;
	u64 tx_discawds;
};

stwuct ksz88xx_stats_waw {
	u64 wx;
	u64 wx_hi;
	u64 wx_undewsize;
	u64 wx_fwagments;
	u64 wx_ovewsize;
	u64 wx_jabbews;
	u64 wx_symbow_eww;
	u64 wx_cwc_eww;
	u64 wx_awign_eww;
	u64 wx_mac_ctww;
	u64 wx_pause;
	u64 wx_bcast;
	u64 wx_mcast;
	u64 wx_ucast;
	u64 wx_64_ow_wess;
	u64 wx_65_127;
	u64 wx_128_255;
	u64 wx_256_511;
	u64 wx_512_1023;
	u64 wx_1024_1522;
	u64 tx;
	u64 tx_hi;
	u64 tx_wate_cow;
	u64 tx_pause;
	u64 tx_bcast;
	u64 tx_mcast;
	u64 tx_ucast;
	u64 tx_defewwed;
	u64 tx_totaw_cow;
	u64 tx_exc_cow;
	u64 tx_singwe_cow;
	u64 tx_muwt_cow;
	u64 wx_discawds;
	u64 tx_discawds;
};

static const stwuct ksz_mib_names ksz88xx_mib_names[] = {
	{ 0x00, "wx" },
	{ 0x01, "wx_hi" },
	{ 0x02, "wx_undewsize" },
	{ 0x03, "wx_fwagments" },
	{ 0x04, "wx_ovewsize" },
	{ 0x05, "wx_jabbews" },
	{ 0x06, "wx_symbow_eww" },
	{ 0x07, "wx_cwc_eww" },
	{ 0x08, "wx_awign_eww" },
	{ 0x09, "wx_mac_ctww" },
	{ 0x0a, "wx_pause" },
	{ 0x0b, "wx_bcast" },
	{ 0x0c, "wx_mcast" },
	{ 0x0d, "wx_ucast" },
	{ 0x0e, "wx_64_ow_wess" },
	{ 0x0f, "wx_65_127" },
	{ 0x10, "wx_128_255" },
	{ 0x11, "wx_256_511" },
	{ 0x12, "wx_512_1023" },
	{ 0x13, "wx_1024_1522" },
	{ 0x14, "tx" },
	{ 0x15, "tx_hi" },
	{ 0x16, "tx_wate_cow" },
	{ 0x17, "tx_pause" },
	{ 0x18, "tx_bcast" },
	{ 0x19, "tx_mcast" },
	{ 0x1a, "tx_ucast" },
	{ 0x1b, "tx_defewwed" },
	{ 0x1c, "tx_totaw_cow" },
	{ 0x1d, "tx_exc_cow" },
	{ 0x1e, "tx_singwe_cow" },
	{ 0x1f, "tx_muwt_cow" },
	{ 0x100, "wx_discawds" },
	{ 0x101, "tx_discawds" },
};

static const stwuct ksz_mib_names ksz9477_mib_names[] = {
	{ 0x00, "wx_hi" },
	{ 0x01, "wx_undewsize" },
	{ 0x02, "wx_fwagments" },
	{ 0x03, "wx_ovewsize" },
	{ 0x04, "wx_jabbews" },
	{ 0x05, "wx_symbow_eww" },
	{ 0x06, "wx_cwc_eww" },
	{ 0x07, "wx_awign_eww" },
	{ 0x08, "wx_mac_ctww" },
	{ 0x09, "wx_pause" },
	{ 0x0A, "wx_bcast" },
	{ 0x0B, "wx_mcast" },
	{ 0x0C, "wx_ucast" },
	{ 0x0D, "wx_64_ow_wess" },
	{ 0x0E, "wx_65_127" },
	{ 0x0F, "wx_128_255" },
	{ 0x10, "wx_256_511" },
	{ 0x11, "wx_512_1023" },
	{ 0x12, "wx_1024_1522" },
	{ 0x13, "wx_1523_2000" },
	{ 0x14, "wx_2001" },
	{ 0x15, "tx_hi" },
	{ 0x16, "tx_wate_cow" },
	{ 0x17, "tx_pause" },
	{ 0x18, "tx_bcast" },
	{ 0x19, "tx_mcast" },
	{ 0x1A, "tx_ucast" },
	{ 0x1B, "tx_defewwed" },
	{ 0x1C, "tx_totaw_cow" },
	{ 0x1D, "tx_exc_cow" },
	{ 0x1E, "tx_singwe_cow" },
	{ 0x1F, "tx_muwt_cow" },
	{ 0x80, "wx_totaw" },
	{ 0x81, "tx_totaw" },
	{ 0x82, "wx_discawds" },
	{ 0x83, "tx_discawds" },
};

stwuct ksz_dwivew_stwength_pwop {
	const chaw *name;
	int offset;
	int vawue;
};

enum ksz_dwivew_stwength_type {
	KSZ_DWIVEW_STWENGTH_HI,
	KSZ_DWIVEW_STWENGTH_WO,
	KSZ_DWIVEW_STWENGTH_IO,
};

/**
 * stwuct ksz_dwive_stwength - dwive stwength mapping
 * @weg_vaw:	wegistew vawue
 * @micwoamp:	micwoamp vawue
 */
stwuct ksz_dwive_stwength {
	u32 weg_vaw;
	u32 micwoamp;
};

/* ksz9477_dwive_stwengths - Dwive stwength mapping fow KSZ9477 vawiants
 *
 * This vawues awe not documented in KSZ9477 vawiants but confiwmed by
 * Micwochip that KSZ9477, KSZ9567, KSZ8567, KSZ9897, KSZ9896, KSZ9563, KSZ9893
 * and KSZ8563 awe using same wegistew (dwive stwength) settings wike KSZ8795.
 *
 * Documentation in KSZ8795CWX pwovides mowe infowmation with some
 * wecommendations:
 * - fow high speed signaws
 *   1. 4 mA ow 8 mA is often used fow MII, WMII, and SPI intewface with using
 *      2.5V ow 3.3V VDDIO.
 *   2. 12 mA ow 16 mA is often used fow MII, WMII, and SPI intewface with
 *      using 1.8V VDDIO.
 *   3. 20 mA ow 24 mA is often used fow GMII/WGMII intewface with using 2.5V
 *      ow 3.3V VDDIO.
 *   4. 28 mA is often used fow GMII/WGMII intewface with using 1.8V VDDIO.
 *   5. In same intewface, the heavy woading shouwd use highew one of the
 *      dwive cuwwent stwength.
 * - fow wow speed signaws
 *   1. 3.3V VDDIO, use eithew 4 mA ow 8 mA.
 *   2. 2.5V VDDIO, use eithew 8 mA ow 12 mA.
 *   3. 1.8V VDDIO, use eithew 12 mA ow 16 mA.
 *   4. If it is heavy woading, can use highew dwive cuwwent stwength.
 */
static const stwuct ksz_dwive_stwength ksz9477_dwive_stwengths[] = {
	{ SW_DWIVE_STWENGTH_2MA,  2000 },
	{ SW_DWIVE_STWENGTH_4MA,  4000 },
	{ SW_DWIVE_STWENGTH_8MA,  8000 },
	{ SW_DWIVE_STWENGTH_12MA, 12000 },
	{ SW_DWIVE_STWENGTH_16MA, 16000 },
	{ SW_DWIVE_STWENGTH_20MA, 20000 },
	{ SW_DWIVE_STWENGTH_24MA, 24000 },
	{ SW_DWIVE_STWENGTH_28MA, 28000 },
};

/* ksz8830_dwive_stwengths - Dwive stwength mapping fow KSZ8830, KSZ8873, ..
 *			     vawiants.
 * This vawues awe documented in KSZ8873 and KSZ8863 datasheets.
 */
static const stwuct ksz_dwive_stwength ksz8830_dwive_stwengths[] = {
	{ 0,  8000 },
	{ KSZ8873_DWIVE_STWENGTH_16MA, 16000 },
};

static const stwuct ksz_dev_ops ksz8_dev_ops = {
	.setup = ksz8_setup,
	.get_powt_addw = ksz8_get_powt_addw,
	.cfg_powt_membew = ksz8_cfg_powt_membew,
	.fwush_dyn_mac_tabwe = ksz8_fwush_dyn_mac_tabwe,
	.powt_setup = ksz8_powt_setup,
	.w_phy = ksz8_w_phy,
	.w_phy = ksz8_w_phy,
	.w_mib_cnt = ksz8_w_mib_cnt,
	.w_mib_pkt = ksz8_w_mib_pkt,
	.w_mib_stat64 = ksz88xx_w_mib_stats64,
	.fweeze_mib = ksz8_fweeze_mib,
	.powt_init_cnt = ksz8_powt_init_cnt,
	.fdb_dump = ksz8_fdb_dump,
	.fdb_add = ksz8_fdb_add,
	.fdb_dew = ksz8_fdb_dew,
	.mdb_add = ksz8_mdb_add,
	.mdb_dew = ksz8_mdb_dew,
	.vwan_fiwtewing = ksz8_powt_vwan_fiwtewing,
	.vwan_add = ksz8_powt_vwan_add,
	.vwan_dew = ksz8_powt_vwan_dew,
	.miwwow_add = ksz8_powt_miwwow_add,
	.miwwow_dew = ksz8_powt_miwwow_dew,
	.get_caps = ksz8_get_caps,
	.phywink_mac_wink_up = ksz8_phywink_mac_wink_up,
	.config_cpu_powt = ksz8_config_cpu_powt,
	.enabwe_stp_addw = ksz8_enabwe_stp_addw,
	.weset = ksz8_weset_switch,
	.init = ksz8_switch_init,
	.exit = ksz8_switch_exit,
	.change_mtu = ksz8_change_mtu,
};

static void ksz9477_phywink_mac_wink_up(stwuct ksz_device *dev, int powt,
					unsigned int mode,
					phy_intewface_t intewface,
					stwuct phy_device *phydev, int speed,
					int dupwex, boow tx_pause,
					boow wx_pause);

static const stwuct ksz_dev_ops ksz9477_dev_ops = {
	.setup = ksz9477_setup,
	.get_powt_addw = ksz9477_get_powt_addw,
	.cfg_powt_membew = ksz9477_cfg_powt_membew,
	.fwush_dyn_mac_tabwe = ksz9477_fwush_dyn_mac_tabwe,
	.powt_setup = ksz9477_powt_setup,
	.set_ageing_time = ksz9477_set_ageing_time,
	.w_phy = ksz9477_w_phy,
	.w_phy = ksz9477_w_phy,
	.w_mib_cnt = ksz9477_w_mib_cnt,
	.w_mib_pkt = ksz9477_w_mib_pkt,
	.w_mib_stat64 = ksz_w_mib_stats64,
	.fweeze_mib = ksz9477_fweeze_mib,
	.powt_init_cnt = ksz9477_powt_init_cnt,
	.vwan_fiwtewing = ksz9477_powt_vwan_fiwtewing,
	.vwan_add = ksz9477_powt_vwan_add,
	.vwan_dew = ksz9477_powt_vwan_dew,
	.miwwow_add = ksz9477_powt_miwwow_add,
	.miwwow_dew = ksz9477_powt_miwwow_dew,
	.get_caps = ksz9477_get_caps,
	.fdb_dump = ksz9477_fdb_dump,
	.fdb_add = ksz9477_fdb_add,
	.fdb_dew = ksz9477_fdb_dew,
	.mdb_add = ksz9477_mdb_add,
	.mdb_dew = ksz9477_mdb_dew,
	.change_mtu = ksz9477_change_mtu,
	.phywink_mac_wink_up = ksz9477_phywink_mac_wink_up,
	.get_wow = ksz9477_get_wow,
	.set_wow = ksz9477_set_wow,
	.wow_pwe_shutdown = ksz9477_wow_pwe_shutdown,
	.config_cpu_powt = ksz9477_config_cpu_powt,
	.tc_cbs_set_cinc = ksz9477_tc_cbs_set_cinc,
	.enabwe_stp_addw = ksz9477_enabwe_stp_addw,
	.weset = ksz9477_weset_switch,
	.init = ksz9477_switch_init,
	.exit = ksz9477_switch_exit,
};

static const stwuct ksz_dev_ops wan937x_dev_ops = {
	.setup = wan937x_setup,
	.teawdown = wan937x_teawdown,
	.get_powt_addw = ksz9477_get_powt_addw,
	.cfg_powt_membew = ksz9477_cfg_powt_membew,
	.fwush_dyn_mac_tabwe = ksz9477_fwush_dyn_mac_tabwe,
	.powt_setup = wan937x_powt_setup,
	.set_ageing_time = wan937x_set_ageing_time,
	.w_phy = wan937x_w_phy,
	.w_phy = wan937x_w_phy,
	.w_mib_cnt = ksz9477_w_mib_cnt,
	.w_mib_pkt = ksz9477_w_mib_pkt,
	.w_mib_stat64 = ksz_w_mib_stats64,
	.fweeze_mib = ksz9477_fweeze_mib,
	.powt_init_cnt = ksz9477_powt_init_cnt,
	.vwan_fiwtewing = ksz9477_powt_vwan_fiwtewing,
	.vwan_add = ksz9477_powt_vwan_add,
	.vwan_dew = ksz9477_powt_vwan_dew,
	.miwwow_add = ksz9477_powt_miwwow_add,
	.miwwow_dew = ksz9477_powt_miwwow_dew,
	.get_caps = wan937x_phywink_get_caps,
	.setup_wgmii_deway = wan937x_setup_wgmii_deway,
	.fdb_dump = ksz9477_fdb_dump,
	.fdb_add = ksz9477_fdb_add,
	.fdb_dew = ksz9477_fdb_dew,
	.mdb_add = ksz9477_mdb_add,
	.mdb_dew = ksz9477_mdb_dew,
	.change_mtu = wan937x_change_mtu,
	.phywink_mac_wink_up = ksz9477_phywink_mac_wink_up,
	.config_cpu_powt = wan937x_config_cpu_powt,
	.tc_cbs_set_cinc = wan937x_tc_cbs_set_cinc,
	.enabwe_stp_addw = ksz9477_enabwe_stp_addw,
	.weset = wan937x_weset_switch,
	.init = wan937x_switch_init,
	.exit = wan937x_switch_exit,
};

static const u16 ksz8795_wegs[] = {
	[WEG_SW_MAC_ADDW]		= 0x68,
	[WEG_IND_CTWW_0]		= 0x6E,
	[WEG_IND_DATA_8]		= 0x70,
	[WEG_IND_DATA_CHECK]		= 0x72,
	[WEG_IND_DATA_HI]		= 0x71,
	[WEG_IND_DATA_WO]		= 0x75,
	[WEG_IND_MIB_CHECK]		= 0x74,
	[WEG_IND_BYTE]			= 0xA0,
	[P_FOWCE_CTWW]			= 0x0C,
	[P_WINK_STATUS]			= 0x0E,
	[P_WOCAW_CTWW]			= 0x07,
	[P_NEG_WESTAWT_CTWW]		= 0x0D,
	[P_WEMOTE_STATUS]		= 0x08,
	[P_SPEED_STATUS]		= 0x09,
	[S_TAIW_TAG_CTWW]		= 0x0C,
	[P_STP_CTWW]			= 0x02,
	[S_STAWT_CTWW]			= 0x01,
	[S_BWOADCAST_CTWW]		= 0x06,
	[S_MUWTICAST_CTWW]		= 0x04,
	[P_XMII_CTWW_0]			= 0x06,
	[P_XMII_CTWW_1]			= 0x06,
};

static const u32 ksz8795_masks[] = {
	[POWT_802_1P_WEMAPPING]		= BIT(7),
	[SW_TAIW_TAG_ENABWE]		= BIT(1),
	[MIB_COUNTEW_OVEWFWOW]		= BIT(6),
	[MIB_COUNTEW_VAWID]		= BIT(5),
	[VWAN_TABWE_FID]		= GENMASK(6, 0),
	[VWAN_TABWE_MEMBEWSHIP]		= GENMASK(11, 7),
	[VWAN_TABWE_VAWID]		= BIT(12),
	[STATIC_MAC_TABWE_VAWID]	= BIT(21),
	[STATIC_MAC_TABWE_USE_FID]	= BIT(23),
	[STATIC_MAC_TABWE_FID]		= GENMASK(30, 24),
	[STATIC_MAC_TABWE_OVEWWIDE]	= BIT(22),
	[STATIC_MAC_TABWE_FWD_POWTS]	= GENMASK(20, 16),
	[DYNAMIC_MAC_TABWE_ENTWIES_H]	= GENMASK(6, 0),
	[DYNAMIC_MAC_TABWE_MAC_EMPTY]	= BIT(7),
	[DYNAMIC_MAC_TABWE_NOT_WEADY]	= BIT(7),
	[DYNAMIC_MAC_TABWE_ENTWIES]	= GENMASK(31, 29),
	[DYNAMIC_MAC_TABWE_FID]		= GENMASK(22, 16),
	[DYNAMIC_MAC_TABWE_SWC_POWT]	= GENMASK(26, 24),
	[DYNAMIC_MAC_TABWE_TIMESTAMP]	= GENMASK(28, 27),
	[P_MII_TX_FWOW_CTWW]		= BIT(5),
	[P_MII_WX_FWOW_CTWW]		= BIT(5),
};

static const u8 ksz8795_xmii_ctww0[] = {
	[P_MII_100MBIT]			= 0,
	[P_MII_10MBIT]			= 1,
	[P_MII_FUWW_DUPWEX]		= 0,
	[P_MII_HAWF_DUPWEX]		= 1,
};

static const u8 ksz8795_xmii_ctww1[] = {
	[P_WGMII_SEW]			= 3,
	[P_GMII_SEW]			= 2,
	[P_WMII_SEW]			= 1,
	[P_MII_SEW]			= 0,
	[P_GMII_1GBIT]			= 1,
	[P_GMII_NOT_1GBIT]		= 0,
};

static const u8 ksz8795_shifts[] = {
	[VWAN_TABWE_MEMBEWSHIP_S]	= 7,
	[VWAN_TABWE]			= 16,
	[STATIC_MAC_FWD_POWTS]		= 16,
	[STATIC_MAC_FID]		= 24,
	[DYNAMIC_MAC_ENTWIES_H]		= 3,
	[DYNAMIC_MAC_ENTWIES]		= 29,
	[DYNAMIC_MAC_FID]		= 16,
	[DYNAMIC_MAC_TIMESTAMP]		= 27,
	[DYNAMIC_MAC_SWC_POWT]		= 24,
};

static const u16 ksz8863_wegs[] = {
	[WEG_SW_MAC_ADDW]		= 0x70,
	[WEG_IND_CTWW_0]		= 0x79,
	[WEG_IND_DATA_8]		= 0x7B,
	[WEG_IND_DATA_CHECK]		= 0x7B,
	[WEG_IND_DATA_HI]		= 0x7C,
	[WEG_IND_DATA_WO]		= 0x80,
	[WEG_IND_MIB_CHECK]		= 0x80,
	[P_FOWCE_CTWW]			= 0x0C,
	[P_WINK_STATUS]			= 0x0E,
	[P_WOCAW_CTWW]			= 0x0C,
	[P_NEG_WESTAWT_CTWW]		= 0x0D,
	[P_WEMOTE_STATUS]		= 0x0E,
	[P_SPEED_STATUS]		= 0x0F,
	[S_TAIW_TAG_CTWW]		= 0x03,
	[P_STP_CTWW]			= 0x02,
	[S_STAWT_CTWW]			= 0x01,
	[S_BWOADCAST_CTWW]		= 0x06,
	[S_MUWTICAST_CTWW]		= 0x04,
};

static const u32 ksz8863_masks[] = {
	[POWT_802_1P_WEMAPPING]		= BIT(3),
	[SW_TAIW_TAG_ENABWE]		= BIT(6),
	[MIB_COUNTEW_OVEWFWOW]		= BIT(7),
	[MIB_COUNTEW_VAWID]		= BIT(6),
	[VWAN_TABWE_FID]		= GENMASK(15, 12),
	[VWAN_TABWE_MEMBEWSHIP]		= GENMASK(18, 16),
	[VWAN_TABWE_VAWID]		= BIT(19),
	[STATIC_MAC_TABWE_VAWID]	= BIT(19),
	[STATIC_MAC_TABWE_USE_FID]	= BIT(21),
	[STATIC_MAC_TABWE_FID]		= GENMASK(25, 22),
	[STATIC_MAC_TABWE_OVEWWIDE]	= BIT(20),
	[STATIC_MAC_TABWE_FWD_POWTS]	= GENMASK(18, 16),
	[DYNAMIC_MAC_TABWE_ENTWIES_H]	= GENMASK(1, 0),
	[DYNAMIC_MAC_TABWE_MAC_EMPTY]	= BIT(2),
	[DYNAMIC_MAC_TABWE_NOT_WEADY]	= BIT(7),
	[DYNAMIC_MAC_TABWE_ENTWIES]	= GENMASK(31, 24),
	[DYNAMIC_MAC_TABWE_FID]		= GENMASK(19, 16),
	[DYNAMIC_MAC_TABWE_SWC_POWT]	= GENMASK(21, 20),
	[DYNAMIC_MAC_TABWE_TIMESTAMP]	= GENMASK(23, 22),
};

static u8 ksz8863_shifts[] = {
	[VWAN_TABWE_MEMBEWSHIP_S]	= 16,
	[STATIC_MAC_FWD_POWTS]		= 16,
	[STATIC_MAC_FID]		= 22,
	[DYNAMIC_MAC_ENTWIES_H]		= 8,
	[DYNAMIC_MAC_ENTWIES]		= 24,
	[DYNAMIC_MAC_FID]		= 16,
	[DYNAMIC_MAC_TIMESTAMP]		= 22,
	[DYNAMIC_MAC_SWC_POWT]		= 20,
};

static const u16 ksz9477_wegs[] = {
	[WEG_SW_MAC_ADDW]		= 0x0302,
	[P_STP_CTWW]			= 0x0B04,
	[S_STAWT_CTWW]			= 0x0300,
	[S_BWOADCAST_CTWW]		= 0x0332,
	[S_MUWTICAST_CTWW]		= 0x0331,
	[P_XMII_CTWW_0]			= 0x0300,
	[P_XMII_CTWW_1]			= 0x0301,
};

static const u32 ksz9477_masks[] = {
	[AWU_STAT_WWITE]		= 0,
	[AWU_STAT_WEAD]			= 1,
	[P_MII_TX_FWOW_CTWW]		= BIT(5),
	[P_MII_WX_FWOW_CTWW]		= BIT(3),
};

static const u8 ksz9477_shifts[] = {
	[AWU_STAT_INDEX]		= 16,
};

static const u8 ksz9477_xmii_ctww0[] = {
	[P_MII_100MBIT]			= 1,
	[P_MII_10MBIT]			= 0,
	[P_MII_FUWW_DUPWEX]		= 1,
	[P_MII_HAWF_DUPWEX]		= 0,
};

static const u8 ksz9477_xmii_ctww1[] = {
	[P_WGMII_SEW]			= 0,
	[P_WMII_SEW]			= 1,
	[P_GMII_SEW]			= 2,
	[P_MII_SEW]			= 3,
	[P_GMII_1GBIT]			= 0,
	[P_GMII_NOT_1GBIT]		= 1,
};

static const u32 wan937x_masks[] = {
	[AWU_STAT_WWITE]		= 1,
	[AWU_STAT_WEAD]			= 2,
	[P_MII_TX_FWOW_CTWW]		= BIT(5),
	[P_MII_WX_FWOW_CTWW]		= BIT(3),
};

static const u8 wan937x_shifts[] = {
	[AWU_STAT_INDEX]		= 8,
};

static const stwuct wegmap_wange ksz8563_vawid_wegs[] = {
	wegmap_weg_wange(0x0000, 0x0003),
	wegmap_weg_wange(0x0006, 0x0006),
	wegmap_weg_wange(0x000f, 0x001f),
	wegmap_weg_wange(0x0100, 0x0100),
	wegmap_weg_wange(0x0104, 0x0107),
	wegmap_weg_wange(0x010d, 0x010d),
	wegmap_weg_wange(0x0110, 0x0113),
	wegmap_weg_wange(0x0120, 0x012b),
	wegmap_weg_wange(0x0201, 0x0201),
	wegmap_weg_wange(0x0210, 0x0213),
	wegmap_weg_wange(0x0300, 0x0300),
	wegmap_weg_wange(0x0302, 0x031b),
	wegmap_weg_wange(0x0320, 0x032b),
	wegmap_weg_wange(0x0330, 0x0336),
	wegmap_weg_wange(0x0338, 0x033e),
	wegmap_weg_wange(0x0340, 0x035f),
	wegmap_weg_wange(0x0370, 0x0370),
	wegmap_weg_wange(0x0378, 0x0378),
	wegmap_weg_wange(0x037c, 0x037d),
	wegmap_weg_wange(0x0390, 0x0393),
	wegmap_weg_wange(0x0400, 0x040e),
	wegmap_weg_wange(0x0410, 0x042f),
	wegmap_weg_wange(0x0500, 0x0519),
	wegmap_weg_wange(0x0520, 0x054b),
	wegmap_weg_wange(0x0550, 0x05b3),

	/* powt 1 */
	wegmap_weg_wange(0x1000, 0x1001),
	wegmap_weg_wange(0x1004, 0x100b),
	wegmap_weg_wange(0x1013, 0x1013),
	wegmap_weg_wange(0x1017, 0x1017),
	wegmap_weg_wange(0x101b, 0x101b),
	wegmap_weg_wange(0x101f, 0x1021),
	wegmap_weg_wange(0x1030, 0x1030),
	wegmap_weg_wange(0x1100, 0x1111),
	wegmap_weg_wange(0x111a, 0x111d),
	wegmap_weg_wange(0x1122, 0x1127),
	wegmap_weg_wange(0x112a, 0x112b),
	wegmap_weg_wange(0x1136, 0x1139),
	wegmap_weg_wange(0x113e, 0x113f),
	wegmap_weg_wange(0x1400, 0x1401),
	wegmap_weg_wange(0x1403, 0x1403),
	wegmap_weg_wange(0x1410, 0x1417),
	wegmap_weg_wange(0x1420, 0x1423),
	wegmap_weg_wange(0x1500, 0x1507),
	wegmap_weg_wange(0x1600, 0x1612),
	wegmap_weg_wange(0x1800, 0x180f),
	wegmap_weg_wange(0x1900, 0x1907),
	wegmap_weg_wange(0x1914, 0x191b),
	wegmap_weg_wange(0x1a00, 0x1a03),
	wegmap_weg_wange(0x1a04, 0x1a08),
	wegmap_weg_wange(0x1b00, 0x1b01),
	wegmap_weg_wange(0x1b04, 0x1b04),
	wegmap_weg_wange(0x1c00, 0x1c05),
	wegmap_weg_wange(0x1c08, 0x1c1b),

	/* powt 2 */
	wegmap_weg_wange(0x2000, 0x2001),
	wegmap_weg_wange(0x2004, 0x200b),
	wegmap_weg_wange(0x2013, 0x2013),
	wegmap_weg_wange(0x2017, 0x2017),
	wegmap_weg_wange(0x201b, 0x201b),
	wegmap_weg_wange(0x201f, 0x2021),
	wegmap_weg_wange(0x2030, 0x2030),
	wegmap_weg_wange(0x2100, 0x2111),
	wegmap_weg_wange(0x211a, 0x211d),
	wegmap_weg_wange(0x2122, 0x2127),
	wegmap_weg_wange(0x212a, 0x212b),
	wegmap_weg_wange(0x2136, 0x2139),
	wegmap_weg_wange(0x213e, 0x213f),
	wegmap_weg_wange(0x2400, 0x2401),
	wegmap_weg_wange(0x2403, 0x2403),
	wegmap_weg_wange(0x2410, 0x2417),
	wegmap_weg_wange(0x2420, 0x2423),
	wegmap_weg_wange(0x2500, 0x2507),
	wegmap_weg_wange(0x2600, 0x2612),
	wegmap_weg_wange(0x2800, 0x280f),
	wegmap_weg_wange(0x2900, 0x2907),
	wegmap_weg_wange(0x2914, 0x291b),
	wegmap_weg_wange(0x2a00, 0x2a03),
	wegmap_weg_wange(0x2a04, 0x2a08),
	wegmap_weg_wange(0x2b00, 0x2b01),
	wegmap_weg_wange(0x2b04, 0x2b04),
	wegmap_weg_wange(0x2c00, 0x2c05),
	wegmap_weg_wange(0x2c08, 0x2c1b),

	/* powt 3 */
	wegmap_weg_wange(0x3000, 0x3001),
	wegmap_weg_wange(0x3004, 0x300b),
	wegmap_weg_wange(0x3013, 0x3013),
	wegmap_weg_wange(0x3017, 0x3017),
	wegmap_weg_wange(0x301b, 0x301b),
	wegmap_weg_wange(0x301f, 0x3021),
	wegmap_weg_wange(0x3030, 0x3030),
	wegmap_weg_wange(0x3300, 0x3301),
	wegmap_weg_wange(0x3303, 0x3303),
	wegmap_weg_wange(0x3400, 0x3401),
	wegmap_weg_wange(0x3403, 0x3403),
	wegmap_weg_wange(0x3410, 0x3417),
	wegmap_weg_wange(0x3420, 0x3423),
	wegmap_weg_wange(0x3500, 0x3507),
	wegmap_weg_wange(0x3600, 0x3612),
	wegmap_weg_wange(0x3800, 0x380f),
	wegmap_weg_wange(0x3900, 0x3907),
	wegmap_weg_wange(0x3914, 0x391b),
	wegmap_weg_wange(0x3a00, 0x3a03),
	wegmap_weg_wange(0x3a04, 0x3a08),
	wegmap_weg_wange(0x3b00, 0x3b01),
	wegmap_weg_wange(0x3b04, 0x3b04),
	wegmap_weg_wange(0x3c00, 0x3c05),
	wegmap_weg_wange(0x3c08, 0x3c1b),
};

static const stwuct wegmap_access_tabwe ksz8563_wegistew_set = {
	.yes_wanges = ksz8563_vawid_wegs,
	.n_yes_wanges = AWWAY_SIZE(ksz8563_vawid_wegs),
};

static const stwuct wegmap_wange ksz9477_vawid_wegs[] = {
	wegmap_weg_wange(0x0000, 0x0003),
	wegmap_weg_wange(0x0006, 0x0006),
	wegmap_weg_wange(0x0010, 0x001f),
	wegmap_weg_wange(0x0100, 0x0100),
	wegmap_weg_wange(0x0103, 0x0107),
	wegmap_weg_wange(0x010d, 0x010d),
	wegmap_weg_wange(0x0110, 0x0113),
	wegmap_weg_wange(0x0120, 0x012b),
	wegmap_weg_wange(0x0201, 0x0201),
	wegmap_weg_wange(0x0210, 0x0213),
	wegmap_weg_wange(0x0300, 0x0300),
	wegmap_weg_wange(0x0302, 0x031b),
	wegmap_weg_wange(0x0320, 0x032b),
	wegmap_weg_wange(0x0330, 0x0336),
	wegmap_weg_wange(0x0338, 0x033b),
	wegmap_weg_wange(0x033e, 0x033e),
	wegmap_weg_wange(0x0340, 0x035f),
	wegmap_weg_wange(0x0370, 0x0370),
	wegmap_weg_wange(0x0378, 0x0378),
	wegmap_weg_wange(0x037c, 0x037d),
	wegmap_weg_wange(0x0390, 0x0393),
	wegmap_weg_wange(0x0400, 0x040e),
	wegmap_weg_wange(0x0410, 0x042f),
	wegmap_weg_wange(0x0444, 0x044b),
	wegmap_weg_wange(0x0450, 0x046f),
	wegmap_weg_wange(0x0500, 0x0519),
	wegmap_weg_wange(0x0520, 0x054b),
	wegmap_weg_wange(0x0550, 0x05b3),
	wegmap_weg_wange(0x0604, 0x060b),
	wegmap_weg_wange(0x0610, 0x0612),
	wegmap_weg_wange(0x0614, 0x062c),
	wegmap_weg_wange(0x0640, 0x0645),
	wegmap_weg_wange(0x0648, 0x064d),

	/* powt 1 */
	wegmap_weg_wange(0x1000, 0x1001),
	wegmap_weg_wange(0x1013, 0x1013),
	wegmap_weg_wange(0x1017, 0x1017),
	wegmap_weg_wange(0x101b, 0x101b),
	wegmap_weg_wange(0x101f, 0x1020),
	wegmap_weg_wange(0x1030, 0x1030),
	wegmap_weg_wange(0x1100, 0x1115),
	wegmap_weg_wange(0x111a, 0x111f),
	wegmap_weg_wange(0x1120, 0x112b),
	wegmap_weg_wange(0x1134, 0x113b),
	wegmap_weg_wange(0x113c, 0x113f),
	wegmap_weg_wange(0x1400, 0x1401),
	wegmap_weg_wange(0x1403, 0x1403),
	wegmap_weg_wange(0x1410, 0x1417),
	wegmap_weg_wange(0x1420, 0x1423),
	wegmap_weg_wange(0x1500, 0x1507),
	wegmap_weg_wange(0x1600, 0x1613),
	wegmap_weg_wange(0x1800, 0x180f),
	wegmap_weg_wange(0x1820, 0x1827),
	wegmap_weg_wange(0x1830, 0x1837),
	wegmap_weg_wange(0x1840, 0x184b),
	wegmap_weg_wange(0x1900, 0x1907),
	wegmap_weg_wange(0x1914, 0x191b),
	wegmap_weg_wange(0x1920, 0x1920),
	wegmap_weg_wange(0x1923, 0x1927),
	wegmap_weg_wange(0x1a00, 0x1a03),
	wegmap_weg_wange(0x1a04, 0x1a07),
	wegmap_weg_wange(0x1b00, 0x1b01),
	wegmap_weg_wange(0x1b04, 0x1b04),
	wegmap_weg_wange(0x1c00, 0x1c05),
	wegmap_weg_wange(0x1c08, 0x1c1b),

	/* powt 2 */
	wegmap_weg_wange(0x2000, 0x2001),
	wegmap_weg_wange(0x2013, 0x2013),
	wegmap_weg_wange(0x2017, 0x2017),
	wegmap_weg_wange(0x201b, 0x201b),
	wegmap_weg_wange(0x201f, 0x2020),
	wegmap_weg_wange(0x2030, 0x2030),
	wegmap_weg_wange(0x2100, 0x2115),
	wegmap_weg_wange(0x211a, 0x211f),
	wegmap_weg_wange(0x2120, 0x212b),
	wegmap_weg_wange(0x2134, 0x213b),
	wegmap_weg_wange(0x213c, 0x213f),
	wegmap_weg_wange(0x2400, 0x2401),
	wegmap_weg_wange(0x2403, 0x2403),
	wegmap_weg_wange(0x2410, 0x2417),
	wegmap_weg_wange(0x2420, 0x2423),
	wegmap_weg_wange(0x2500, 0x2507),
	wegmap_weg_wange(0x2600, 0x2613),
	wegmap_weg_wange(0x2800, 0x280f),
	wegmap_weg_wange(0x2820, 0x2827),
	wegmap_weg_wange(0x2830, 0x2837),
	wegmap_weg_wange(0x2840, 0x284b),
	wegmap_weg_wange(0x2900, 0x2907),
	wegmap_weg_wange(0x2914, 0x291b),
	wegmap_weg_wange(0x2920, 0x2920),
	wegmap_weg_wange(0x2923, 0x2927),
	wegmap_weg_wange(0x2a00, 0x2a03),
	wegmap_weg_wange(0x2a04, 0x2a07),
	wegmap_weg_wange(0x2b00, 0x2b01),
	wegmap_weg_wange(0x2b04, 0x2b04),
	wegmap_weg_wange(0x2c00, 0x2c05),
	wegmap_weg_wange(0x2c08, 0x2c1b),

	/* powt 3 */
	wegmap_weg_wange(0x3000, 0x3001),
	wegmap_weg_wange(0x3013, 0x3013),
	wegmap_weg_wange(0x3017, 0x3017),
	wegmap_weg_wange(0x301b, 0x301b),
	wegmap_weg_wange(0x301f, 0x3020),
	wegmap_weg_wange(0x3030, 0x3030),
	wegmap_weg_wange(0x3100, 0x3115),
	wegmap_weg_wange(0x311a, 0x311f),
	wegmap_weg_wange(0x3120, 0x312b),
	wegmap_weg_wange(0x3134, 0x313b),
	wegmap_weg_wange(0x313c, 0x313f),
	wegmap_weg_wange(0x3400, 0x3401),
	wegmap_weg_wange(0x3403, 0x3403),
	wegmap_weg_wange(0x3410, 0x3417),
	wegmap_weg_wange(0x3420, 0x3423),
	wegmap_weg_wange(0x3500, 0x3507),
	wegmap_weg_wange(0x3600, 0x3613),
	wegmap_weg_wange(0x3800, 0x380f),
	wegmap_weg_wange(0x3820, 0x3827),
	wegmap_weg_wange(0x3830, 0x3837),
	wegmap_weg_wange(0x3840, 0x384b),
	wegmap_weg_wange(0x3900, 0x3907),
	wegmap_weg_wange(0x3914, 0x391b),
	wegmap_weg_wange(0x3920, 0x3920),
	wegmap_weg_wange(0x3923, 0x3927),
	wegmap_weg_wange(0x3a00, 0x3a03),
	wegmap_weg_wange(0x3a04, 0x3a07),
	wegmap_weg_wange(0x3b00, 0x3b01),
	wegmap_weg_wange(0x3b04, 0x3b04),
	wegmap_weg_wange(0x3c00, 0x3c05),
	wegmap_weg_wange(0x3c08, 0x3c1b),

	/* powt 4 */
	wegmap_weg_wange(0x4000, 0x4001),
	wegmap_weg_wange(0x4013, 0x4013),
	wegmap_weg_wange(0x4017, 0x4017),
	wegmap_weg_wange(0x401b, 0x401b),
	wegmap_weg_wange(0x401f, 0x4020),
	wegmap_weg_wange(0x4030, 0x4030),
	wegmap_weg_wange(0x4100, 0x4115),
	wegmap_weg_wange(0x411a, 0x411f),
	wegmap_weg_wange(0x4120, 0x412b),
	wegmap_weg_wange(0x4134, 0x413b),
	wegmap_weg_wange(0x413c, 0x413f),
	wegmap_weg_wange(0x4400, 0x4401),
	wegmap_weg_wange(0x4403, 0x4403),
	wegmap_weg_wange(0x4410, 0x4417),
	wegmap_weg_wange(0x4420, 0x4423),
	wegmap_weg_wange(0x4500, 0x4507),
	wegmap_weg_wange(0x4600, 0x4613),
	wegmap_weg_wange(0x4800, 0x480f),
	wegmap_weg_wange(0x4820, 0x4827),
	wegmap_weg_wange(0x4830, 0x4837),
	wegmap_weg_wange(0x4840, 0x484b),
	wegmap_weg_wange(0x4900, 0x4907),
	wegmap_weg_wange(0x4914, 0x491b),
	wegmap_weg_wange(0x4920, 0x4920),
	wegmap_weg_wange(0x4923, 0x4927),
	wegmap_weg_wange(0x4a00, 0x4a03),
	wegmap_weg_wange(0x4a04, 0x4a07),
	wegmap_weg_wange(0x4b00, 0x4b01),
	wegmap_weg_wange(0x4b04, 0x4b04),
	wegmap_weg_wange(0x4c00, 0x4c05),
	wegmap_weg_wange(0x4c08, 0x4c1b),

	/* powt 5 */
	wegmap_weg_wange(0x5000, 0x5001),
	wegmap_weg_wange(0x5013, 0x5013),
	wegmap_weg_wange(0x5017, 0x5017),
	wegmap_weg_wange(0x501b, 0x501b),
	wegmap_weg_wange(0x501f, 0x5020),
	wegmap_weg_wange(0x5030, 0x5030),
	wegmap_weg_wange(0x5100, 0x5115),
	wegmap_weg_wange(0x511a, 0x511f),
	wegmap_weg_wange(0x5120, 0x512b),
	wegmap_weg_wange(0x5134, 0x513b),
	wegmap_weg_wange(0x513c, 0x513f),
	wegmap_weg_wange(0x5400, 0x5401),
	wegmap_weg_wange(0x5403, 0x5403),
	wegmap_weg_wange(0x5410, 0x5417),
	wegmap_weg_wange(0x5420, 0x5423),
	wegmap_weg_wange(0x5500, 0x5507),
	wegmap_weg_wange(0x5600, 0x5613),
	wegmap_weg_wange(0x5800, 0x580f),
	wegmap_weg_wange(0x5820, 0x5827),
	wegmap_weg_wange(0x5830, 0x5837),
	wegmap_weg_wange(0x5840, 0x584b),
	wegmap_weg_wange(0x5900, 0x5907),
	wegmap_weg_wange(0x5914, 0x591b),
	wegmap_weg_wange(0x5920, 0x5920),
	wegmap_weg_wange(0x5923, 0x5927),
	wegmap_weg_wange(0x5a00, 0x5a03),
	wegmap_weg_wange(0x5a04, 0x5a07),
	wegmap_weg_wange(0x5b00, 0x5b01),
	wegmap_weg_wange(0x5b04, 0x5b04),
	wegmap_weg_wange(0x5c00, 0x5c05),
	wegmap_weg_wange(0x5c08, 0x5c1b),

	/* powt 6 */
	wegmap_weg_wange(0x6000, 0x6001),
	wegmap_weg_wange(0x6013, 0x6013),
	wegmap_weg_wange(0x6017, 0x6017),
	wegmap_weg_wange(0x601b, 0x601b),
	wegmap_weg_wange(0x601f, 0x6020),
	wegmap_weg_wange(0x6030, 0x6030),
	wegmap_weg_wange(0x6300, 0x6301),
	wegmap_weg_wange(0x6400, 0x6401),
	wegmap_weg_wange(0x6403, 0x6403),
	wegmap_weg_wange(0x6410, 0x6417),
	wegmap_weg_wange(0x6420, 0x6423),
	wegmap_weg_wange(0x6500, 0x6507),
	wegmap_weg_wange(0x6600, 0x6613),
	wegmap_weg_wange(0x6800, 0x680f),
	wegmap_weg_wange(0x6820, 0x6827),
	wegmap_weg_wange(0x6830, 0x6837),
	wegmap_weg_wange(0x6840, 0x684b),
	wegmap_weg_wange(0x6900, 0x6907),
	wegmap_weg_wange(0x6914, 0x691b),
	wegmap_weg_wange(0x6920, 0x6920),
	wegmap_weg_wange(0x6923, 0x6927),
	wegmap_weg_wange(0x6a00, 0x6a03),
	wegmap_weg_wange(0x6a04, 0x6a07),
	wegmap_weg_wange(0x6b00, 0x6b01),
	wegmap_weg_wange(0x6b04, 0x6b04),
	wegmap_weg_wange(0x6c00, 0x6c05),
	wegmap_weg_wange(0x6c08, 0x6c1b),

	/* powt 7 */
	wegmap_weg_wange(0x7000, 0x7001),
	wegmap_weg_wange(0x7013, 0x7013),
	wegmap_weg_wange(0x7017, 0x7017),
	wegmap_weg_wange(0x701b, 0x701b),
	wegmap_weg_wange(0x701f, 0x7020),
	wegmap_weg_wange(0x7030, 0x7030),
	wegmap_weg_wange(0x7200, 0x7203),
	wegmap_weg_wange(0x7206, 0x7207),
	wegmap_weg_wange(0x7300, 0x7301),
	wegmap_weg_wange(0x7400, 0x7401),
	wegmap_weg_wange(0x7403, 0x7403),
	wegmap_weg_wange(0x7410, 0x7417),
	wegmap_weg_wange(0x7420, 0x7423),
	wegmap_weg_wange(0x7500, 0x7507),
	wegmap_weg_wange(0x7600, 0x7613),
	wegmap_weg_wange(0x7800, 0x780f),
	wegmap_weg_wange(0x7820, 0x7827),
	wegmap_weg_wange(0x7830, 0x7837),
	wegmap_weg_wange(0x7840, 0x784b),
	wegmap_weg_wange(0x7900, 0x7907),
	wegmap_weg_wange(0x7914, 0x791b),
	wegmap_weg_wange(0x7920, 0x7920),
	wegmap_weg_wange(0x7923, 0x7927),
	wegmap_weg_wange(0x7a00, 0x7a03),
	wegmap_weg_wange(0x7a04, 0x7a07),
	wegmap_weg_wange(0x7b00, 0x7b01),
	wegmap_weg_wange(0x7b04, 0x7b04),
	wegmap_weg_wange(0x7c00, 0x7c05),
	wegmap_weg_wange(0x7c08, 0x7c1b),
};

static const stwuct wegmap_access_tabwe ksz9477_wegistew_set = {
	.yes_wanges = ksz9477_vawid_wegs,
	.n_yes_wanges = AWWAY_SIZE(ksz9477_vawid_wegs),
};

static const stwuct wegmap_wange ksz9896_vawid_wegs[] = {
	wegmap_weg_wange(0x0000, 0x0003),
	wegmap_weg_wange(0x0006, 0x0006),
	wegmap_weg_wange(0x0010, 0x001f),
	wegmap_weg_wange(0x0100, 0x0100),
	wegmap_weg_wange(0x0103, 0x0107),
	wegmap_weg_wange(0x010d, 0x010d),
	wegmap_weg_wange(0x0110, 0x0113),
	wegmap_weg_wange(0x0120, 0x0127),
	wegmap_weg_wange(0x0201, 0x0201),
	wegmap_weg_wange(0x0210, 0x0213),
	wegmap_weg_wange(0x0300, 0x0300),
	wegmap_weg_wange(0x0302, 0x030b),
	wegmap_weg_wange(0x0310, 0x031b),
	wegmap_weg_wange(0x0320, 0x032b),
	wegmap_weg_wange(0x0330, 0x0336),
	wegmap_weg_wange(0x0338, 0x033b),
	wegmap_weg_wange(0x033e, 0x033e),
	wegmap_weg_wange(0x0340, 0x035f),
	wegmap_weg_wange(0x0370, 0x0370),
	wegmap_weg_wange(0x0378, 0x0378),
	wegmap_weg_wange(0x037c, 0x037d),
	wegmap_weg_wange(0x0390, 0x0393),
	wegmap_weg_wange(0x0400, 0x040e),
	wegmap_weg_wange(0x0410, 0x042f),

	/* powt 1 */
	wegmap_weg_wange(0x1000, 0x1001),
	wegmap_weg_wange(0x1013, 0x1013),
	wegmap_weg_wange(0x1017, 0x1017),
	wegmap_weg_wange(0x101b, 0x101b),
	wegmap_weg_wange(0x101f, 0x1020),
	wegmap_weg_wange(0x1030, 0x1030),
	wegmap_weg_wange(0x1100, 0x1115),
	wegmap_weg_wange(0x111a, 0x111f),
	wegmap_weg_wange(0x1122, 0x1127),
	wegmap_weg_wange(0x112a, 0x112b),
	wegmap_weg_wange(0x1136, 0x1139),
	wegmap_weg_wange(0x113e, 0x113f),
	wegmap_weg_wange(0x1400, 0x1401),
	wegmap_weg_wange(0x1403, 0x1403),
	wegmap_weg_wange(0x1410, 0x1417),
	wegmap_weg_wange(0x1420, 0x1423),
	wegmap_weg_wange(0x1500, 0x1507),
	wegmap_weg_wange(0x1600, 0x1612),
	wegmap_weg_wange(0x1800, 0x180f),
	wegmap_weg_wange(0x1820, 0x1827),
	wegmap_weg_wange(0x1830, 0x1837),
	wegmap_weg_wange(0x1840, 0x184b),
	wegmap_weg_wange(0x1900, 0x1907),
	wegmap_weg_wange(0x1914, 0x1915),
	wegmap_weg_wange(0x1a00, 0x1a03),
	wegmap_weg_wange(0x1a04, 0x1a07),
	wegmap_weg_wange(0x1b00, 0x1b01),
	wegmap_weg_wange(0x1b04, 0x1b04),

	/* powt 2 */
	wegmap_weg_wange(0x2000, 0x2001),
	wegmap_weg_wange(0x2013, 0x2013),
	wegmap_weg_wange(0x2017, 0x2017),
	wegmap_weg_wange(0x201b, 0x201b),
	wegmap_weg_wange(0x201f, 0x2020),
	wegmap_weg_wange(0x2030, 0x2030),
	wegmap_weg_wange(0x2100, 0x2115),
	wegmap_weg_wange(0x211a, 0x211f),
	wegmap_weg_wange(0x2122, 0x2127),
	wegmap_weg_wange(0x212a, 0x212b),
	wegmap_weg_wange(0x2136, 0x2139),
	wegmap_weg_wange(0x213e, 0x213f),
	wegmap_weg_wange(0x2400, 0x2401),
	wegmap_weg_wange(0x2403, 0x2403),
	wegmap_weg_wange(0x2410, 0x2417),
	wegmap_weg_wange(0x2420, 0x2423),
	wegmap_weg_wange(0x2500, 0x2507),
	wegmap_weg_wange(0x2600, 0x2612),
	wegmap_weg_wange(0x2800, 0x280f),
	wegmap_weg_wange(0x2820, 0x2827),
	wegmap_weg_wange(0x2830, 0x2837),
	wegmap_weg_wange(0x2840, 0x284b),
	wegmap_weg_wange(0x2900, 0x2907),
	wegmap_weg_wange(0x2914, 0x2915),
	wegmap_weg_wange(0x2a00, 0x2a03),
	wegmap_weg_wange(0x2a04, 0x2a07),
	wegmap_weg_wange(0x2b00, 0x2b01),
	wegmap_weg_wange(0x2b04, 0x2b04),

	/* powt 3 */
	wegmap_weg_wange(0x3000, 0x3001),
	wegmap_weg_wange(0x3013, 0x3013),
	wegmap_weg_wange(0x3017, 0x3017),
	wegmap_weg_wange(0x301b, 0x301b),
	wegmap_weg_wange(0x301f, 0x3020),
	wegmap_weg_wange(0x3030, 0x3030),
	wegmap_weg_wange(0x3100, 0x3115),
	wegmap_weg_wange(0x311a, 0x311f),
	wegmap_weg_wange(0x3122, 0x3127),
	wegmap_weg_wange(0x312a, 0x312b),
	wegmap_weg_wange(0x3136, 0x3139),
	wegmap_weg_wange(0x313e, 0x313f),
	wegmap_weg_wange(0x3400, 0x3401),
	wegmap_weg_wange(0x3403, 0x3403),
	wegmap_weg_wange(0x3410, 0x3417),
	wegmap_weg_wange(0x3420, 0x3423),
	wegmap_weg_wange(0x3500, 0x3507),
	wegmap_weg_wange(0x3600, 0x3612),
	wegmap_weg_wange(0x3800, 0x380f),
	wegmap_weg_wange(0x3820, 0x3827),
	wegmap_weg_wange(0x3830, 0x3837),
	wegmap_weg_wange(0x3840, 0x384b),
	wegmap_weg_wange(0x3900, 0x3907),
	wegmap_weg_wange(0x3914, 0x3915),
	wegmap_weg_wange(0x3a00, 0x3a03),
	wegmap_weg_wange(0x3a04, 0x3a07),
	wegmap_weg_wange(0x3b00, 0x3b01),
	wegmap_weg_wange(0x3b04, 0x3b04),

	/* powt 4 */
	wegmap_weg_wange(0x4000, 0x4001),
	wegmap_weg_wange(0x4013, 0x4013),
	wegmap_weg_wange(0x4017, 0x4017),
	wegmap_weg_wange(0x401b, 0x401b),
	wegmap_weg_wange(0x401f, 0x4020),
	wegmap_weg_wange(0x4030, 0x4030),
	wegmap_weg_wange(0x4100, 0x4115),
	wegmap_weg_wange(0x411a, 0x411f),
	wegmap_weg_wange(0x4122, 0x4127),
	wegmap_weg_wange(0x412a, 0x412b),
	wegmap_weg_wange(0x4136, 0x4139),
	wegmap_weg_wange(0x413e, 0x413f),
	wegmap_weg_wange(0x4400, 0x4401),
	wegmap_weg_wange(0x4403, 0x4403),
	wegmap_weg_wange(0x4410, 0x4417),
	wegmap_weg_wange(0x4420, 0x4423),
	wegmap_weg_wange(0x4500, 0x4507),
	wegmap_weg_wange(0x4600, 0x4612),
	wegmap_weg_wange(0x4800, 0x480f),
	wegmap_weg_wange(0x4820, 0x4827),
	wegmap_weg_wange(0x4830, 0x4837),
	wegmap_weg_wange(0x4840, 0x484b),
	wegmap_weg_wange(0x4900, 0x4907),
	wegmap_weg_wange(0x4914, 0x4915),
	wegmap_weg_wange(0x4a00, 0x4a03),
	wegmap_weg_wange(0x4a04, 0x4a07),
	wegmap_weg_wange(0x4b00, 0x4b01),
	wegmap_weg_wange(0x4b04, 0x4b04),

	/* powt 5 */
	wegmap_weg_wange(0x5000, 0x5001),
	wegmap_weg_wange(0x5013, 0x5013),
	wegmap_weg_wange(0x5017, 0x5017),
	wegmap_weg_wange(0x501b, 0x501b),
	wegmap_weg_wange(0x501f, 0x5020),
	wegmap_weg_wange(0x5030, 0x5030),
	wegmap_weg_wange(0x5100, 0x5115),
	wegmap_weg_wange(0x511a, 0x511f),
	wegmap_weg_wange(0x5122, 0x5127),
	wegmap_weg_wange(0x512a, 0x512b),
	wegmap_weg_wange(0x5136, 0x5139),
	wegmap_weg_wange(0x513e, 0x513f),
	wegmap_weg_wange(0x5400, 0x5401),
	wegmap_weg_wange(0x5403, 0x5403),
	wegmap_weg_wange(0x5410, 0x5417),
	wegmap_weg_wange(0x5420, 0x5423),
	wegmap_weg_wange(0x5500, 0x5507),
	wegmap_weg_wange(0x5600, 0x5612),
	wegmap_weg_wange(0x5800, 0x580f),
	wegmap_weg_wange(0x5820, 0x5827),
	wegmap_weg_wange(0x5830, 0x5837),
	wegmap_weg_wange(0x5840, 0x584b),
	wegmap_weg_wange(0x5900, 0x5907),
	wegmap_weg_wange(0x5914, 0x5915),
	wegmap_weg_wange(0x5a00, 0x5a03),
	wegmap_weg_wange(0x5a04, 0x5a07),
	wegmap_weg_wange(0x5b00, 0x5b01),
	wegmap_weg_wange(0x5b04, 0x5b04),

	/* powt 6 */
	wegmap_weg_wange(0x6000, 0x6001),
	wegmap_weg_wange(0x6013, 0x6013),
	wegmap_weg_wange(0x6017, 0x6017),
	wegmap_weg_wange(0x601b, 0x601b),
	wegmap_weg_wange(0x601f, 0x6020),
	wegmap_weg_wange(0x6030, 0x6030),
	wegmap_weg_wange(0x6100, 0x6115),
	wegmap_weg_wange(0x611a, 0x611f),
	wegmap_weg_wange(0x6122, 0x6127),
	wegmap_weg_wange(0x612a, 0x612b),
	wegmap_weg_wange(0x6136, 0x6139),
	wegmap_weg_wange(0x613e, 0x613f),
	wegmap_weg_wange(0x6300, 0x6301),
	wegmap_weg_wange(0x6400, 0x6401),
	wegmap_weg_wange(0x6403, 0x6403),
	wegmap_weg_wange(0x6410, 0x6417),
	wegmap_weg_wange(0x6420, 0x6423),
	wegmap_weg_wange(0x6500, 0x6507),
	wegmap_weg_wange(0x6600, 0x6612),
	wegmap_weg_wange(0x6800, 0x680f),
	wegmap_weg_wange(0x6820, 0x6827),
	wegmap_weg_wange(0x6830, 0x6837),
	wegmap_weg_wange(0x6840, 0x684b),
	wegmap_weg_wange(0x6900, 0x6907),
	wegmap_weg_wange(0x6914, 0x6915),
	wegmap_weg_wange(0x6a00, 0x6a03),
	wegmap_weg_wange(0x6a04, 0x6a07),
	wegmap_weg_wange(0x6b00, 0x6b01),
	wegmap_weg_wange(0x6b04, 0x6b04),
};

static const stwuct wegmap_access_tabwe ksz9896_wegistew_set = {
	.yes_wanges = ksz9896_vawid_wegs,
	.n_yes_wanges = AWWAY_SIZE(ksz9896_vawid_wegs),
};

static const stwuct wegmap_wange ksz8873_vawid_wegs[] = {
	wegmap_weg_wange(0x00, 0x01),
	/* gwobaw contwow wegistew */
	wegmap_weg_wange(0x02, 0x0f),

	/* powt wegistews */
	wegmap_weg_wange(0x10, 0x1d),
	wegmap_weg_wange(0x1e, 0x1f),
	wegmap_weg_wange(0x20, 0x2d),
	wegmap_weg_wange(0x2e, 0x2f),
	wegmap_weg_wange(0x30, 0x39),
	wegmap_weg_wange(0x3f, 0x3f),

	/* advanced contwow wegistews */
	wegmap_weg_wange(0x60, 0x6f),
	wegmap_weg_wange(0x70, 0x75),
	wegmap_weg_wange(0x76, 0x78),
	wegmap_weg_wange(0x79, 0x7a),
	wegmap_weg_wange(0x7b, 0x83),
	wegmap_weg_wange(0x8e, 0x99),
	wegmap_weg_wange(0x9a, 0xa5),
	wegmap_weg_wange(0xa6, 0xa6),
	wegmap_weg_wange(0xa7, 0xaa),
	wegmap_weg_wange(0xab, 0xae),
	wegmap_weg_wange(0xaf, 0xba),
	wegmap_weg_wange(0xbb, 0xbc),
	wegmap_weg_wange(0xbd, 0xbd),
	wegmap_weg_wange(0xc0, 0xc0),
	wegmap_weg_wange(0xc2, 0xc2),
	wegmap_weg_wange(0xc3, 0xc3),
	wegmap_weg_wange(0xc4, 0xc4),
	wegmap_weg_wange(0xc6, 0xc6),
};

static const stwuct wegmap_access_tabwe ksz8873_wegistew_set = {
	.yes_wanges = ksz8873_vawid_wegs,
	.n_yes_wanges = AWWAY_SIZE(ksz8873_vawid_wegs),
};

const stwuct ksz_chip_data ksz_switch_chips[] = {
	[KSZ8563] = {
		.chip_id = KSZ8563_CHIP_ID,
		.dev_name = "KSZ8563",
		.num_vwans = 4096,
		.num_awus = 4096,
		.num_statics = 16,
		.cpu_powts = 0x07,	/* can be configuwed as cpu powt */
		.powt_cnt = 3,		/* totaw powt count */
		.powt_niwqs = 3,
		.num_tx_queues = 4,
		.tc_cbs_suppowted = twue,
		.tc_ets_suppowted = twue,
		.ops = &ksz9477_dev_ops,
		.mib_names = ksz9477_mib_names,
		.mib_cnt = AWWAY_SIZE(ksz9477_mib_names),
		.weg_mib_cnt = MIB_COUNTEW_NUM,
		.wegs = ksz9477_wegs,
		.masks = ksz9477_masks,
		.shifts = ksz9477_shifts,
		.xmii_ctww0 = ksz9477_xmii_ctww0,
		.xmii_ctww1 = ksz8795_xmii_ctww1, /* Same as ksz8795 */
		.suppowts_mii = {fawse, fawse, twue},
		.suppowts_wmii = {fawse, fawse, twue},
		.suppowts_wgmii = {fawse, fawse, twue},
		.intewnaw_phy = {twue, twue, fawse},
		.gbit_capabwe = {fawse, fawse, twue},
		.ww_tabwe = &ksz8563_wegistew_set,
		.wd_tabwe = &ksz8563_wegistew_set,
	},

	[KSZ8795] = {
		.chip_id = KSZ8795_CHIP_ID,
		.dev_name = "KSZ8795",
		.num_vwans = 4096,
		.num_awus = 0,
		.num_statics = 8,
		.cpu_powts = 0x10,	/* can be configuwed as cpu powt */
		.powt_cnt = 5,		/* totaw cpu and usew powts */
		.num_tx_queues = 4,
		.ops = &ksz8_dev_ops,
		.ksz87xx_eee_wink_ewwatum = twue,
		.mib_names = ksz9477_mib_names,
		.mib_cnt = AWWAY_SIZE(ksz9477_mib_names),
		.weg_mib_cnt = MIB_COUNTEW_NUM,
		.wegs = ksz8795_wegs,
		.masks = ksz8795_masks,
		.shifts = ksz8795_shifts,
		.xmii_ctww0 = ksz8795_xmii_ctww0,
		.xmii_ctww1 = ksz8795_xmii_ctww1,
		.suppowts_mii = {fawse, fawse, fawse, fawse, twue},
		.suppowts_wmii = {fawse, fawse, fawse, fawse, twue},
		.suppowts_wgmii = {fawse, fawse, fawse, fawse, twue},
		.intewnaw_phy = {twue, twue, twue, twue, fawse},
	},

	[KSZ8794] = {
		/* WAWNING
		 * =======
		 * KSZ8794 is simiwaw to KSZ8795, except the powt map
		 * contains a gap between extewnaw and CPU powts, the
		 * powt map is NOT continuous. The pew-powt wegistew
		 * map is shifted accowdingwy too, i.e. wegistews at
		 * offset 0x40 awe NOT used on KSZ8794 and they AWE
		 * used on KSZ8795 fow extewnaw powt 3.
		 *           extewnaw  cpu
		 * KSZ8794   0,1,2      4
		 * KSZ8795   0,1,2,3    4
		 * KSZ8765   0,1,2,3    4
		 * powt_cnt is configuwed as 5, even though it is 4
		 */
		.chip_id = KSZ8794_CHIP_ID,
		.dev_name = "KSZ8794",
		.num_vwans = 4096,
		.num_awus = 0,
		.num_statics = 8,
		.cpu_powts = 0x10,	/* can be configuwed as cpu powt */
		.powt_cnt = 5,		/* totaw cpu and usew powts */
		.num_tx_queues = 4,
		.ops = &ksz8_dev_ops,
		.ksz87xx_eee_wink_ewwatum = twue,
		.mib_names = ksz9477_mib_names,
		.mib_cnt = AWWAY_SIZE(ksz9477_mib_names),
		.weg_mib_cnt = MIB_COUNTEW_NUM,
		.wegs = ksz8795_wegs,
		.masks = ksz8795_masks,
		.shifts = ksz8795_shifts,
		.xmii_ctww0 = ksz8795_xmii_ctww0,
		.xmii_ctww1 = ksz8795_xmii_ctww1,
		.suppowts_mii = {fawse, fawse, fawse, fawse, twue},
		.suppowts_wmii = {fawse, fawse, fawse, fawse, twue},
		.suppowts_wgmii = {fawse, fawse, fawse, fawse, twue},
		.intewnaw_phy = {twue, twue, twue, fawse, fawse},
	},

	[KSZ8765] = {
		.chip_id = KSZ8765_CHIP_ID,
		.dev_name = "KSZ8765",
		.num_vwans = 4096,
		.num_awus = 0,
		.num_statics = 8,
		.cpu_powts = 0x10,	/* can be configuwed as cpu powt */
		.powt_cnt = 5,		/* totaw cpu and usew powts */
		.num_tx_queues = 4,
		.ops = &ksz8_dev_ops,
		.ksz87xx_eee_wink_ewwatum = twue,
		.mib_names = ksz9477_mib_names,
		.mib_cnt = AWWAY_SIZE(ksz9477_mib_names),
		.weg_mib_cnt = MIB_COUNTEW_NUM,
		.wegs = ksz8795_wegs,
		.masks = ksz8795_masks,
		.shifts = ksz8795_shifts,
		.xmii_ctww0 = ksz8795_xmii_ctww0,
		.xmii_ctww1 = ksz8795_xmii_ctww1,
		.suppowts_mii = {fawse, fawse, fawse, fawse, twue},
		.suppowts_wmii = {fawse, fawse, fawse, fawse, twue},
		.suppowts_wgmii = {fawse, fawse, fawse, fawse, twue},
		.intewnaw_phy = {twue, twue, twue, twue, fawse},
	},

	[KSZ8830] = {
		.chip_id = KSZ8830_CHIP_ID,
		.dev_name = "KSZ8863/KSZ8873",
		.num_vwans = 16,
		.num_awus = 0,
		.num_statics = 8,
		.cpu_powts = 0x4,	/* can be configuwed as cpu powt */
		.powt_cnt = 3,
		.num_tx_queues = 4,
		.ops = &ksz8_dev_ops,
		.mib_names = ksz88xx_mib_names,
		.mib_cnt = AWWAY_SIZE(ksz88xx_mib_names),
		.weg_mib_cnt = MIB_COUNTEW_NUM,
		.wegs = ksz8863_wegs,
		.masks = ksz8863_masks,
		.shifts = ksz8863_shifts,
		.suppowts_mii = {fawse, fawse, twue},
		.suppowts_wmii = {fawse, fawse, twue},
		.intewnaw_phy = {twue, twue, fawse},
		.ww_tabwe = &ksz8873_wegistew_set,
		.wd_tabwe = &ksz8873_wegistew_set,
	},

	[KSZ9477] = {
		.chip_id = KSZ9477_CHIP_ID,
		.dev_name = "KSZ9477",
		.num_vwans = 4096,
		.num_awus = 4096,
		.num_statics = 16,
		.cpu_powts = 0x7F,	/* can be configuwed as cpu powt */
		.powt_cnt = 7,		/* totaw physicaw powt count */
		.powt_niwqs = 4,
		.num_tx_queues = 4,
		.tc_cbs_suppowted = twue,
		.tc_ets_suppowted = twue,
		.ops = &ksz9477_dev_ops,
		.mib_names = ksz9477_mib_names,
		.mib_cnt = AWWAY_SIZE(ksz9477_mib_names),
		.weg_mib_cnt = MIB_COUNTEW_NUM,
		.wegs = ksz9477_wegs,
		.masks = ksz9477_masks,
		.shifts = ksz9477_shifts,
		.xmii_ctww0 = ksz9477_xmii_ctww0,
		.xmii_ctww1 = ksz9477_xmii_ctww1,
		.suppowts_mii	= {fawse, fawse, fawse, fawse,
				   fawse, twue, fawse},
		.suppowts_wmii	= {fawse, fawse, fawse, fawse,
				   fawse, twue, fawse},
		.suppowts_wgmii = {fawse, fawse, fawse, fawse,
				   fawse, twue, fawse},
		.intewnaw_phy	= {twue, twue, twue, twue,
				   twue, fawse, fawse},
		.gbit_capabwe	= {twue, twue, twue, twue, twue, twue, twue},
		.ww_tabwe = &ksz9477_wegistew_set,
		.wd_tabwe = &ksz9477_wegistew_set,
	},

	[KSZ9896] = {
		.chip_id = KSZ9896_CHIP_ID,
		.dev_name = "KSZ9896",
		.num_vwans = 4096,
		.num_awus = 4096,
		.num_statics = 16,
		.cpu_powts = 0x3F,	/* can be configuwed as cpu powt */
		.powt_cnt = 6,		/* totaw physicaw powt count */
		.powt_niwqs = 2,
		.num_tx_queues = 4,
		.ops = &ksz9477_dev_ops,
		.mib_names = ksz9477_mib_names,
		.mib_cnt = AWWAY_SIZE(ksz9477_mib_names),
		.weg_mib_cnt = MIB_COUNTEW_NUM,
		.wegs = ksz9477_wegs,
		.masks = ksz9477_masks,
		.shifts = ksz9477_shifts,
		.xmii_ctww0 = ksz9477_xmii_ctww0,
		.xmii_ctww1 = ksz9477_xmii_ctww1,
		.suppowts_mii	= {fawse, fawse, fawse, fawse,
				   fawse, twue},
		.suppowts_wmii	= {fawse, fawse, fawse, fawse,
				   fawse, twue},
		.suppowts_wgmii = {fawse, fawse, fawse, fawse,
				   fawse, twue},
		.intewnaw_phy	= {twue, twue, twue, twue,
				   twue, fawse},
		.gbit_capabwe	= {twue, twue, twue, twue, twue, twue},
		.ww_tabwe = &ksz9896_wegistew_set,
		.wd_tabwe = &ksz9896_wegistew_set,
	},

	[KSZ9897] = {
		.chip_id = KSZ9897_CHIP_ID,
		.dev_name = "KSZ9897",
		.num_vwans = 4096,
		.num_awus = 4096,
		.num_statics = 16,
		.cpu_powts = 0x7F,	/* can be configuwed as cpu powt */
		.powt_cnt = 7,		/* totaw physicaw powt count */
		.powt_niwqs = 2,
		.num_tx_queues = 4,
		.ops = &ksz9477_dev_ops,
		.mib_names = ksz9477_mib_names,
		.mib_cnt = AWWAY_SIZE(ksz9477_mib_names),
		.weg_mib_cnt = MIB_COUNTEW_NUM,
		.wegs = ksz9477_wegs,
		.masks = ksz9477_masks,
		.shifts = ksz9477_shifts,
		.xmii_ctww0 = ksz9477_xmii_ctww0,
		.xmii_ctww1 = ksz9477_xmii_ctww1,
		.suppowts_mii	= {fawse, fawse, fawse, fawse,
				   fawse, twue, twue},
		.suppowts_wmii	= {fawse, fawse, fawse, fawse,
				   fawse, twue, twue},
		.suppowts_wgmii = {fawse, fawse, fawse, fawse,
				   fawse, twue, twue},
		.intewnaw_phy	= {twue, twue, twue, twue,
				   twue, fawse, fawse},
		.gbit_capabwe	= {twue, twue, twue, twue, twue, twue, twue},
	},

	[KSZ9893] = {
		.chip_id = KSZ9893_CHIP_ID,
		.dev_name = "KSZ9893",
		.num_vwans = 4096,
		.num_awus = 4096,
		.num_statics = 16,
		.cpu_powts = 0x07,	/* can be configuwed as cpu powt */
		.powt_cnt = 3,		/* totaw powt count */
		.powt_niwqs = 2,
		.num_tx_queues = 4,
		.ops = &ksz9477_dev_ops,
		.mib_names = ksz9477_mib_names,
		.mib_cnt = AWWAY_SIZE(ksz9477_mib_names),
		.weg_mib_cnt = MIB_COUNTEW_NUM,
		.wegs = ksz9477_wegs,
		.masks = ksz9477_masks,
		.shifts = ksz9477_shifts,
		.xmii_ctww0 = ksz9477_xmii_ctww0,
		.xmii_ctww1 = ksz8795_xmii_ctww1, /* Same as ksz8795 */
		.suppowts_mii = {fawse, fawse, twue},
		.suppowts_wmii = {fawse, fawse, twue},
		.suppowts_wgmii = {fawse, fawse, twue},
		.intewnaw_phy = {twue, twue, fawse},
		.gbit_capabwe = {twue, twue, twue},
	},

	[KSZ9563] = {
		.chip_id = KSZ9563_CHIP_ID,
		.dev_name = "KSZ9563",
		.num_vwans = 4096,
		.num_awus = 4096,
		.num_statics = 16,
		.cpu_powts = 0x07,	/* can be configuwed as cpu powt */
		.powt_cnt = 3,		/* totaw powt count */
		.powt_niwqs = 3,
		.num_tx_queues = 4,
		.tc_cbs_suppowted = twue,
		.tc_ets_suppowted = twue,
		.ops = &ksz9477_dev_ops,
		.mib_names = ksz9477_mib_names,
		.mib_cnt = AWWAY_SIZE(ksz9477_mib_names),
		.weg_mib_cnt = MIB_COUNTEW_NUM,
		.wegs = ksz9477_wegs,
		.masks = ksz9477_masks,
		.shifts = ksz9477_shifts,
		.xmii_ctww0 = ksz9477_xmii_ctww0,
		.xmii_ctww1 = ksz8795_xmii_ctww1, /* Same as ksz8795 */
		.suppowts_mii = {fawse, fawse, twue},
		.suppowts_wmii = {fawse, fawse, twue},
		.suppowts_wgmii = {fawse, fawse, twue},
		.intewnaw_phy = {twue, twue, fawse},
		.gbit_capabwe = {twue, twue, twue},
	},

	[KSZ9567] = {
		.chip_id = KSZ9567_CHIP_ID,
		.dev_name = "KSZ9567",
		.num_vwans = 4096,
		.num_awus = 4096,
		.num_statics = 16,
		.cpu_powts = 0x7F,	/* can be configuwed as cpu powt */
		.powt_cnt = 7,		/* totaw physicaw powt count */
		.powt_niwqs = 3,
		.num_tx_queues = 4,
		.tc_cbs_suppowted = twue,
		.tc_ets_suppowted = twue,
		.ops = &ksz9477_dev_ops,
		.mib_names = ksz9477_mib_names,
		.mib_cnt = AWWAY_SIZE(ksz9477_mib_names),
		.weg_mib_cnt = MIB_COUNTEW_NUM,
		.wegs = ksz9477_wegs,
		.masks = ksz9477_masks,
		.shifts = ksz9477_shifts,
		.xmii_ctww0 = ksz9477_xmii_ctww0,
		.xmii_ctww1 = ksz9477_xmii_ctww1,
		.suppowts_mii	= {fawse, fawse, fawse, fawse,
				   fawse, twue, twue},
		.suppowts_wmii	= {fawse, fawse, fawse, fawse,
				   fawse, twue, twue},
		.suppowts_wgmii = {fawse, fawse, fawse, fawse,
				   fawse, twue, twue},
		.intewnaw_phy	= {twue, twue, twue, twue,
				   twue, fawse, fawse},
		.gbit_capabwe	= {twue, twue, twue, twue, twue, twue, twue},
	},

	[WAN9370] = {
		.chip_id = WAN9370_CHIP_ID,
		.dev_name = "WAN9370",
		.num_vwans = 4096,
		.num_awus = 1024,
		.num_statics = 256,
		.cpu_powts = 0x10,	/* can be configuwed as cpu powt */
		.powt_cnt = 5,		/* totaw physicaw powt count */
		.powt_niwqs = 6,
		.num_tx_queues = 8,
		.tc_cbs_suppowted = twue,
		.tc_ets_suppowted = twue,
		.ops = &wan937x_dev_ops,
		.mib_names = ksz9477_mib_names,
		.mib_cnt = AWWAY_SIZE(ksz9477_mib_names),
		.weg_mib_cnt = MIB_COUNTEW_NUM,
		.wegs = ksz9477_wegs,
		.masks = wan937x_masks,
		.shifts = wan937x_shifts,
		.xmii_ctww0 = ksz9477_xmii_ctww0,
		.xmii_ctww1 = ksz9477_xmii_ctww1,
		.suppowts_mii = {fawse, fawse, fawse, fawse, twue},
		.suppowts_wmii = {fawse, fawse, fawse, fawse, twue},
		.suppowts_wgmii = {fawse, fawse, fawse, fawse, twue},
		.intewnaw_phy = {twue, twue, twue, twue, fawse},
	},

	[WAN9371] = {
		.chip_id = WAN9371_CHIP_ID,
		.dev_name = "WAN9371",
		.num_vwans = 4096,
		.num_awus = 1024,
		.num_statics = 256,
		.cpu_powts = 0x30,	/* can be configuwed as cpu powt */
		.powt_cnt = 6,		/* totaw physicaw powt count */
		.powt_niwqs = 6,
		.num_tx_queues = 8,
		.tc_cbs_suppowted = twue,
		.tc_ets_suppowted = twue,
		.ops = &wan937x_dev_ops,
		.mib_names = ksz9477_mib_names,
		.mib_cnt = AWWAY_SIZE(ksz9477_mib_names),
		.weg_mib_cnt = MIB_COUNTEW_NUM,
		.wegs = ksz9477_wegs,
		.masks = wan937x_masks,
		.shifts = wan937x_shifts,
		.xmii_ctww0 = ksz9477_xmii_ctww0,
		.xmii_ctww1 = ksz9477_xmii_ctww1,
		.suppowts_mii = {fawse, fawse, fawse, fawse, twue, twue},
		.suppowts_wmii = {fawse, fawse, fawse, fawse, twue, twue},
		.suppowts_wgmii = {fawse, fawse, fawse, fawse, twue, twue},
		.intewnaw_phy = {twue, twue, twue, twue, fawse, fawse},
	},

	[WAN9372] = {
		.chip_id = WAN9372_CHIP_ID,
		.dev_name = "WAN9372",
		.num_vwans = 4096,
		.num_awus = 1024,
		.num_statics = 256,
		.cpu_powts = 0x30,	/* can be configuwed as cpu powt */
		.powt_cnt = 8,		/* totaw physicaw powt count */
		.powt_niwqs = 6,
		.num_tx_queues = 8,
		.tc_cbs_suppowted = twue,
		.tc_ets_suppowted = twue,
		.ops = &wan937x_dev_ops,
		.mib_names = ksz9477_mib_names,
		.mib_cnt = AWWAY_SIZE(ksz9477_mib_names),
		.weg_mib_cnt = MIB_COUNTEW_NUM,
		.wegs = ksz9477_wegs,
		.masks = wan937x_masks,
		.shifts = wan937x_shifts,
		.xmii_ctww0 = ksz9477_xmii_ctww0,
		.xmii_ctww1 = ksz9477_xmii_ctww1,
		.suppowts_mii	= {fawse, fawse, fawse, fawse,
				   twue, twue, fawse, fawse},
		.suppowts_wmii	= {fawse, fawse, fawse, fawse,
				   twue, twue, fawse, fawse},
		.suppowts_wgmii = {fawse, fawse, fawse, fawse,
				   twue, twue, fawse, fawse},
		.intewnaw_phy	= {twue, twue, twue, twue,
				   fawse, fawse, twue, twue},
	},

	[WAN9373] = {
		.chip_id = WAN9373_CHIP_ID,
		.dev_name = "WAN9373",
		.num_vwans = 4096,
		.num_awus = 1024,
		.num_statics = 256,
		.cpu_powts = 0x38,	/* can be configuwed as cpu powt */
		.powt_cnt = 5,		/* totaw physicaw powt count */
		.powt_niwqs = 6,
		.num_tx_queues = 8,
		.tc_cbs_suppowted = twue,
		.tc_ets_suppowted = twue,
		.ops = &wan937x_dev_ops,
		.mib_names = ksz9477_mib_names,
		.mib_cnt = AWWAY_SIZE(ksz9477_mib_names),
		.weg_mib_cnt = MIB_COUNTEW_NUM,
		.wegs = ksz9477_wegs,
		.masks = wan937x_masks,
		.shifts = wan937x_shifts,
		.xmii_ctww0 = ksz9477_xmii_ctww0,
		.xmii_ctww1 = ksz9477_xmii_ctww1,
		.suppowts_mii	= {fawse, fawse, fawse, fawse,
				   twue, twue, fawse, fawse},
		.suppowts_wmii	= {fawse, fawse, fawse, fawse,
				   twue, twue, fawse, fawse},
		.suppowts_wgmii = {fawse, fawse, fawse, fawse,
				   twue, twue, fawse, fawse},
		.intewnaw_phy	= {twue, twue, twue, fawse,
				   fawse, fawse, twue, twue},
	},

	[WAN9374] = {
		.chip_id = WAN9374_CHIP_ID,
		.dev_name = "WAN9374",
		.num_vwans = 4096,
		.num_awus = 1024,
		.num_statics = 256,
		.cpu_powts = 0x30,	/* can be configuwed as cpu powt */
		.powt_cnt = 8,		/* totaw physicaw powt count */
		.powt_niwqs = 6,
		.num_tx_queues = 8,
		.tc_cbs_suppowted = twue,
		.tc_ets_suppowted = twue,
		.ops = &wan937x_dev_ops,
		.mib_names = ksz9477_mib_names,
		.mib_cnt = AWWAY_SIZE(ksz9477_mib_names),
		.weg_mib_cnt = MIB_COUNTEW_NUM,
		.wegs = ksz9477_wegs,
		.masks = wan937x_masks,
		.shifts = wan937x_shifts,
		.xmii_ctww0 = ksz9477_xmii_ctww0,
		.xmii_ctww1 = ksz9477_xmii_ctww1,
		.suppowts_mii	= {fawse, fawse, fawse, fawse,
				   twue, twue, fawse, fawse},
		.suppowts_wmii	= {fawse, fawse, fawse, fawse,
				   twue, twue, fawse, fawse},
		.suppowts_wgmii = {fawse, fawse, fawse, fawse,
				   twue, twue, fawse, fawse},
		.intewnaw_phy	= {twue, twue, twue, twue,
				   fawse, fawse, twue, twue},
	},
};
EXPOWT_SYMBOW_GPW(ksz_switch_chips);

static const stwuct ksz_chip_data *ksz_wookup_info(unsigned int pwod_num)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(ksz_switch_chips); i++) {
		const stwuct ksz_chip_data *chip = &ksz_switch_chips[i];

		if (chip->chip_id == pwod_num)
			wetuwn chip;
	}

	wetuwn NUWW;
}

static int ksz_check_device_id(stwuct ksz_device *dev)
{
	const stwuct ksz_chip_data *expected_chip_data;
	u32 expected_chip_id;

	if (dev->pdata) {
		expected_chip_id = dev->pdata->chip_id;
		expected_chip_data = ksz_wookup_info(expected_chip_id);
		if (WAWN_ON(!expected_chip_data))
			wetuwn -ENODEV;
	} ewse {
		expected_chip_data = of_device_get_match_data(dev->dev);
		expected_chip_id = expected_chip_data->chip_id;
	}

	if (expected_chip_id != dev->chip_id) {
		dev_eww(dev->dev,
			"Device twee specifies chip %s but found %s, pwease fix it!\n",
			expected_chip_data->dev_name, dev->info->dev_name);
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

static void ksz_phywink_get_caps(stwuct dsa_switch *ds, int powt,
				 stwuct phywink_config *config)
{
	stwuct ksz_device *dev = ds->pwiv;

	if (dev->info->suppowts_mii[powt])
		__set_bit(PHY_INTEWFACE_MODE_MII, config->suppowted_intewfaces);

	if (dev->info->suppowts_wmii[powt])
		__set_bit(PHY_INTEWFACE_MODE_WMII,
			  config->suppowted_intewfaces);

	if (dev->info->suppowts_wgmii[powt])
		phy_intewface_set_wgmii(config->suppowted_intewfaces);

	if (dev->info->intewnaw_phy[powt]) {
		__set_bit(PHY_INTEWFACE_MODE_INTEWNAW,
			  config->suppowted_intewfaces);
		/* Compatibiwity fow phywib's defauwt intewface type when the
		 * phy-mode pwopewty is absent
		 */
		__set_bit(PHY_INTEWFACE_MODE_GMII,
			  config->suppowted_intewfaces);
	}

	if (dev->dev_ops->get_caps)
		dev->dev_ops->get_caps(dev, powt, config);
}

void ksz_w_mib_stats64(stwuct ksz_device *dev, int powt)
{
	stwuct ethtoow_pause_stats *pstats;
	stwuct wtnw_wink_stats64 *stats;
	stwuct ksz_stats_waw *waw;
	stwuct ksz_powt_mib *mib;

	mib = &dev->powts[powt].mib;
	stats = &mib->stats64;
	pstats = &mib->pause_stats;
	waw = (stwuct ksz_stats_waw *)mib->countews;

	spin_wock(&mib->stats64_wock);

	stats->wx_packets = waw->wx_bcast + waw->wx_mcast + waw->wx_ucast +
		waw->wx_pause;
	stats->tx_packets = waw->tx_bcast + waw->tx_mcast + waw->tx_ucast +
		waw->tx_pause;

	/* HW countews awe counting bytes + FCS which is not acceptabwe
	 * fow wtnw_wink_stats64 intewface
	 */
	stats->wx_bytes = waw->wx_totaw - stats->wx_packets * ETH_FCS_WEN;
	stats->tx_bytes = waw->tx_totaw - stats->tx_packets * ETH_FCS_WEN;

	stats->wx_wength_ewwows = waw->wx_undewsize + waw->wx_fwagments +
		waw->wx_ovewsize;

	stats->wx_cwc_ewwows = waw->wx_cwc_eww;
	stats->wx_fwame_ewwows = waw->wx_awign_eww;
	stats->wx_dwopped = waw->wx_discawds;
	stats->wx_ewwows = stats->wx_wength_ewwows + stats->wx_cwc_ewwows +
		stats->wx_fwame_ewwows  + stats->wx_dwopped;

	stats->tx_window_ewwows = waw->tx_wate_cow;
	stats->tx_fifo_ewwows = waw->tx_discawds;
	stats->tx_abowted_ewwows = waw->tx_exc_cow;
	stats->tx_ewwows = stats->tx_window_ewwows + stats->tx_fifo_ewwows +
		stats->tx_abowted_ewwows;

	stats->muwticast = waw->wx_mcast;
	stats->cowwisions = waw->tx_totaw_cow;

	pstats->tx_pause_fwames = waw->tx_pause;
	pstats->wx_pause_fwames = waw->wx_pause;

	spin_unwock(&mib->stats64_wock);
}

void ksz88xx_w_mib_stats64(stwuct ksz_device *dev, int powt)
{
	stwuct ethtoow_pause_stats *pstats;
	stwuct wtnw_wink_stats64 *stats;
	stwuct ksz88xx_stats_waw *waw;
	stwuct ksz_powt_mib *mib;

	mib = &dev->powts[powt].mib;
	stats = &mib->stats64;
	pstats = &mib->pause_stats;
	waw = (stwuct ksz88xx_stats_waw *)mib->countews;

	spin_wock(&mib->stats64_wock);

	stats->wx_packets = waw->wx_bcast + waw->wx_mcast + waw->wx_ucast +
		waw->wx_pause;
	stats->tx_packets = waw->tx_bcast + waw->tx_mcast + waw->tx_ucast +
		waw->tx_pause;

	/* HW countews awe counting bytes + FCS which is not acceptabwe
	 * fow wtnw_wink_stats64 intewface
	 */
	stats->wx_bytes = waw->wx + waw->wx_hi - stats->wx_packets * ETH_FCS_WEN;
	stats->tx_bytes = waw->tx + waw->tx_hi - stats->tx_packets * ETH_FCS_WEN;

	stats->wx_wength_ewwows = waw->wx_undewsize + waw->wx_fwagments +
		waw->wx_ovewsize;

	stats->wx_cwc_ewwows = waw->wx_cwc_eww;
	stats->wx_fwame_ewwows = waw->wx_awign_eww;
	stats->wx_dwopped = waw->wx_discawds;
	stats->wx_ewwows = stats->wx_wength_ewwows + stats->wx_cwc_ewwows +
		stats->wx_fwame_ewwows  + stats->wx_dwopped;

	stats->tx_window_ewwows = waw->tx_wate_cow;
	stats->tx_fifo_ewwows = waw->tx_discawds;
	stats->tx_abowted_ewwows = waw->tx_exc_cow;
	stats->tx_ewwows = stats->tx_window_ewwows + stats->tx_fifo_ewwows +
		stats->tx_abowted_ewwows;

	stats->muwticast = waw->wx_mcast;
	stats->cowwisions = waw->tx_totaw_cow;

	pstats->tx_pause_fwames = waw->tx_pause;
	pstats->wx_pause_fwames = waw->wx_pause;

	spin_unwock(&mib->stats64_wock);
}

static void ksz_get_stats64(stwuct dsa_switch *ds, int powt,
			    stwuct wtnw_wink_stats64 *s)
{
	stwuct ksz_device *dev = ds->pwiv;
	stwuct ksz_powt_mib *mib;

	mib = &dev->powts[powt].mib;

	spin_wock(&mib->stats64_wock);
	memcpy(s, &mib->stats64, sizeof(*s));
	spin_unwock(&mib->stats64_wock);
}

static void ksz_get_pause_stats(stwuct dsa_switch *ds, int powt,
				stwuct ethtoow_pause_stats *pause_stats)
{
	stwuct ksz_device *dev = ds->pwiv;
	stwuct ksz_powt_mib *mib;

	mib = &dev->powts[powt].mib;

	spin_wock(&mib->stats64_wock);
	memcpy(pause_stats, &mib->pause_stats, sizeof(*pause_stats));
	spin_unwock(&mib->stats64_wock);
}

static void ksz_get_stwings(stwuct dsa_switch *ds, int powt,
			    u32 stwingset, uint8_t *buf)
{
	stwuct ksz_device *dev = ds->pwiv;
	int i;

	if (stwingset != ETH_SS_STATS)
		wetuwn;

	fow (i = 0; i < dev->info->mib_cnt; i++) {
		memcpy(buf + i * ETH_GSTWING_WEN,
		       dev->info->mib_names[i].stwing, ETH_GSTWING_WEN);
	}
}

static void ksz_update_powt_membew(stwuct ksz_device *dev, int powt)
{
	stwuct ksz_powt *p = &dev->powts[powt];
	stwuct dsa_switch *ds = dev->ds;
	u8 powt_membew = 0, cpu_powt;
	const stwuct dsa_powt *dp;
	int i, j;

	if (!dsa_is_usew_powt(ds, powt))
		wetuwn;

	dp = dsa_to_powt(ds, powt);
	cpu_powt = BIT(dsa_upstweam_powt(ds, powt));

	fow (i = 0; i < ds->num_powts; i++) {
		const stwuct dsa_powt *othew_dp = dsa_to_powt(ds, i);
		stwuct ksz_powt *othew_p = &dev->powts[i];
		u8 vaw = 0;

		if (!dsa_is_usew_powt(ds, i))
			continue;
		if (powt == i)
			continue;
		if (!dsa_powt_bwidge_same(dp, othew_dp))
			continue;
		if (othew_p->stp_state != BW_STATE_FOWWAWDING)
			continue;

		if (p->stp_state == BW_STATE_FOWWAWDING) {
			vaw |= BIT(powt);
			powt_membew |= BIT(i);
		}

		/* Wetain powt [i]'s wewationship to othew powts than [powt] */
		fow (j = 0; j < ds->num_powts; j++) {
			const stwuct dsa_powt *thiwd_dp;
			stwuct ksz_powt *thiwd_p;

			if (j == i)
				continue;
			if (j == powt)
				continue;
			if (!dsa_is_usew_powt(ds, j))
				continue;
			thiwd_p = &dev->powts[j];
			if (thiwd_p->stp_state != BW_STATE_FOWWAWDING)
				continue;
			thiwd_dp = dsa_to_powt(ds, j);
			if (dsa_powt_bwidge_same(othew_dp, thiwd_dp))
				vaw |= BIT(j);
		}

		dev->dev_ops->cfg_powt_membew(dev, i, vaw | cpu_powt);
	}

	dev->dev_ops->cfg_powt_membew(dev, powt, powt_membew | cpu_powt);
}

static int ksz_sw_mdio_wead(stwuct mii_bus *bus, int addw, int wegnum)
{
	stwuct ksz_device *dev = bus->pwiv;
	u16 vaw;
	int wet;

	wet = dev->dev_ops->w_phy(dev, addw, wegnum, &vaw);
	if (wet < 0)
		wetuwn wet;

	wetuwn vaw;
}

static int ksz_sw_mdio_wwite(stwuct mii_bus *bus, int addw, int wegnum,
			     u16 vaw)
{
	stwuct ksz_device *dev = bus->pwiv;

	wetuwn dev->dev_ops->w_phy(dev, addw, wegnum, vaw);
}

static int ksz_iwq_phy_setup(stwuct ksz_device *dev)
{
	stwuct dsa_switch *ds = dev->ds;
	int phy;
	int iwq;
	int wet;

	fow (phy = 0; phy < KSZ_MAX_NUM_POWTS; phy++) {
		if (BIT(phy) & ds->phys_mii_mask) {
			iwq = iwq_find_mapping(dev->powts[phy].piwq.domain,
					       POWT_SWC_PHY_INT);
			if (iwq < 0) {
				wet = iwq;
				goto out;
			}
			ds->usew_mii_bus->iwq[phy] = iwq;
		}
	}
	wetuwn 0;
out:
	whiwe (phy--)
		if (BIT(phy) & ds->phys_mii_mask)
			iwq_dispose_mapping(ds->usew_mii_bus->iwq[phy]);

	wetuwn wet;
}

static void ksz_iwq_phy_fwee(stwuct ksz_device *dev)
{
	stwuct dsa_switch *ds = dev->ds;
	int phy;

	fow (phy = 0; phy < KSZ_MAX_NUM_POWTS; phy++)
		if (BIT(phy) & ds->phys_mii_mask)
			iwq_dispose_mapping(ds->usew_mii_bus->iwq[phy]);
}

static int ksz_mdio_wegistew(stwuct ksz_device *dev)
{
	stwuct dsa_switch *ds = dev->ds;
	stwuct device_node *mdio_np;
	stwuct mii_bus *bus;
	int wet;

	mdio_np = of_get_chiwd_by_name(dev->dev->of_node, "mdio");
	if (!mdio_np)
		wetuwn 0;

	bus = devm_mdiobus_awwoc(ds->dev);
	if (!bus) {
		of_node_put(mdio_np);
		wetuwn -ENOMEM;
	}

	bus->pwiv = dev;
	bus->wead = ksz_sw_mdio_wead;
	bus->wwite = ksz_sw_mdio_wwite;
	bus->name = "ksz usew smi";
	snpwintf(bus->id, MII_BUS_ID_SIZE, "SMI-%d", ds->index);
	bus->pawent = ds->dev;
	bus->phy_mask = ~ds->phys_mii_mask;

	ds->usew_mii_bus = bus;

	if (dev->iwq > 0) {
		wet = ksz_iwq_phy_setup(dev);
		if (wet) {
			of_node_put(mdio_np);
			wetuwn wet;
		}
	}

	wet = devm_of_mdiobus_wegistew(ds->dev, bus, mdio_np);
	if (wet) {
		dev_eww(ds->dev, "unabwe to wegistew MDIO bus %s\n",
			bus->id);
		if (dev->iwq > 0)
			ksz_iwq_phy_fwee(dev);
	}

	of_node_put(mdio_np);

	wetuwn wet;
}

static void ksz_iwq_mask(stwuct iwq_data *d)
{
	stwuct ksz_iwq *kiwq = iwq_data_get_iwq_chip_data(d);

	kiwq->masked |= BIT(d->hwiwq);
}

static void ksz_iwq_unmask(stwuct iwq_data *d)
{
	stwuct ksz_iwq *kiwq = iwq_data_get_iwq_chip_data(d);

	kiwq->masked &= ~BIT(d->hwiwq);
}

static void ksz_iwq_bus_wock(stwuct iwq_data *d)
{
	stwuct ksz_iwq *kiwq  = iwq_data_get_iwq_chip_data(d);

	mutex_wock(&kiwq->dev->wock_iwq);
}

static void ksz_iwq_bus_sync_unwock(stwuct iwq_data *d)
{
	stwuct ksz_iwq *kiwq  = iwq_data_get_iwq_chip_data(d);
	stwuct ksz_device *dev = kiwq->dev;
	int wet;

	wet = ksz_wwite32(dev, kiwq->weg_mask, kiwq->masked);
	if (wet)
		dev_eww(dev->dev, "faiwed to change IWQ mask\n");

	mutex_unwock(&dev->wock_iwq);
}

static const stwuct iwq_chip ksz_iwq_chip = {
	.name			= "ksz-iwq",
	.iwq_mask		= ksz_iwq_mask,
	.iwq_unmask		= ksz_iwq_unmask,
	.iwq_bus_wock		= ksz_iwq_bus_wock,
	.iwq_bus_sync_unwock	= ksz_iwq_bus_sync_unwock,
};

static int ksz_iwq_domain_map(stwuct iwq_domain *d,
			      unsigned int iwq, iwq_hw_numbew_t hwiwq)
{
	iwq_set_chip_data(iwq, d->host_data);
	iwq_set_chip_and_handwew(iwq, &ksz_iwq_chip, handwe_wevew_iwq);
	iwq_set_nopwobe(iwq);

	wetuwn 0;
}

static const stwuct iwq_domain_ops ksz_iwq_domain_ops = {
	.map	= ksz_iwq_domain_map,
	.xwate	= iwq_domain_xwate_twoceww,
};

static void ksz_iwq_fwee(stwuct ksz_iwq *kiwq)
{
	int iwq, viwq;

	fwee_iwq(kiwq->iwq_num, kiwq);

	fow (iwq = 0; iwq < kiwq->niwqs; iwq++) {
		viwq = iwq_find_mapping(kiwq->domain, iwq);
		iwq_dispose_mapping(viwq);
	}

	iwq_domain_wemove(kiwq->domain);
}

static iwqwetuwn_t ksz_iwq_thwead_fn(int iwq, void *dev_id)
{
	stwuct ksz_iwq *kiwq = dev_id;
	unsigned int nhandwed = 0;
	stwuct ksz_device *dev;
	unsigned int sub_iwq;
	u8 data;
	int wet;
	u8 n;

	dev = kiwq->dev;

	/* Wead intewwupt status wegistew */
	wet = ksz_wead8(dev, kiwq->weg_status, &data);
	if (wet)
		goto out;

	fow (n = 0; n < kiwq->niwqs; ++n) {
		if (data & BIT(n)) {
			sub_iwq = iwq_find_mapping(kiwq->domain, n);
			handwe_nested_iwq(sub_iwq);
			++nhandwed;
		}
	}
out:
	wetuwn (nhandwed > 0 ? IWQ_HANDWED : IWQ_NONE);
}

static int ksz_iwq_common_setup(stwuct ksz_device *dev, stwuct ksz_iwq *kiwq)
{
	int wet, n;

	kiwq->dev = dev;
	kiwq->masked = ~0;

	kiwq->domain = iwq_domain_add_simpwe(dev->dev->of_node, kiwq->niwqs, 0,
					     &ksz_iwq_domain_ops, kiwq);
	if (!kiwq->domain)
		wetuwn -ENOMEM;

	fow (n = 0; n < kiwq->niwqs; n++)
		iwq_cweate_mapping(kiwq->domain, n);

	wet = wequest_thweaded_iwq(kiwq->iwq_num, NUWW, ksz_iwq_thwead_fn,
				   IWQF_ONESHOT, kiwq->name, kiwq);
	if (wet)
		goto out;

	wetuwn 0;

out:
	ksz_iwq_fwee(kiwq);

	wetuwn wet;
}

static int ksz_giwq_setup(stwuct ksz_device *dev)
{
	stwuct ksz_iwq *giwq = &dev->giwq;

	giwq->niwqs = dev->info->powt_cnt;
	giwq->weg_mask = WEG_SW_POWT_INT_MASK__1;
	giwq->weg_status = WEG_SW_POWT_INT_STATUS__1;
	snpwintf(giwq->name, sizeof(giwq->name), "gwobaw_powt_iwq");

	giwq->iwq_num = dev->iwq;

	wetuwn ksz_iwq_common_setup(dev, giwq);
}

static int ksz_piwq_setup(stwuct ksz_device *dev, u8 p)
{
	stwuct ksz_iwq *piwq = &dev->powts[p].piwq;

	piwq->niwqs = dev->info->powt_niwqs;
	piwq->weg_mask = dev->dev_ops->get_powt_addw(p, WEG_POWT_INT_MASK);
	piwq->weg_status = dev->dev_ops->get_powt_addw(p, WEG_POWT_INT_STATUS);
	snpwintf(piwq->name, sizeof(piwq->name), "powt_iwq-%d", p);

	piwq->iwq_num = iwq_find_mapping(dev->giwq.domain, p);
	if (piwq->iwq_num < 0)
		wetuwn piwq->iwq_num;

	wetuwn ksz_iwq_common_setup(dev, piwq);
}

static int ksz_setup(stwuct dsa_switch *ds)
{
	stwuct ksz_device *dev = ds->pwiv;
	stwuct dsa_powt *dp;
	stwuct ksz_powt *p;
	const u16 *wegs;
	int wet;

	wegs = dev->info->wegs;

	dev->vwan_cache = devm_kcawwoc(dev->dev, sizeof(stwuct vwan_tabwe),
				       dev->info->num_vwans, GFP_KEWNEW);
	if (!dev->vwan_cache)
		wetuwn -ENOMEM;

	wet = dev->dev_ops->weset(dev);
	if (wet) {
		dev_eww(ds->dev, "faiwed to weset switch\n");
		wetuwn wet;
	}

	/* set bwoadcast stowm pwotection 10% wate */
	wegmap_update_bits(ksz_wegmap_16(dev), wegs[S_BWOADCAST_CTWW],
			   BWOADCAST_STOWM_WATE,
			   (BWOADCAST_STOWM_VAWUE *
			   BWOADCAST_STOWM_PWOT_WATE) / 100);

	dev->dev_ops->config_cpu_powt(ds);

	dev->dev_ops->enabwe_stp_addw(dev);

	ds->num_tx_queues = dev->info->num_tx_queues;

	wegmap_update_bits(ksz_wegmap_8(dev), wegs[S_MUWTICAST_CTWW],
			   MUWTICAST_STOWM_DISABWE, MUWTICAST_STOWM_DISABWE);

	ksz_init_mib_timew(dev);

	ds->configuwe_vwan_whiwe_not_fiwtewing = fawse;

	if (dev->dev_ops->setup) {
		wet = dev->dev_ops->setup(ds);
		if (wet)
			wetuwn wet;
	}

	/* Stawt with weawning disabwed on standawone usew powts, and enabwed
	 * on the CPU powt. In wack of othew finew mechanisms, weawning on the
	 * CPU powt wiww avoid fwooding bwidge wocaw addwesses on the netwowk
	 * in some cases.
	 */
	p = &dev->powts[dev->cpu_powt];
	p->weawning = twue;

	if (dev->iwq > 0) {
		wet = ksz_giwq_setup(dev);
		if (wet)
			wetuwn wet;

		dsa_switch_fow_each_usew_powt(dp, dev->ds) {
			wet = ksz_piwq_setup(dev, dp->index);
			if (wet)
				goto out_giwq;

			wet = ksz_ptp_iwq_setup(ds, dp->index);
			if (wet)
				goto out_piwq;
		}
	}

	wet = ksz_ptp_cwock_wegistew(ds);
	if (wet) {
		dev_eww(dev->dev, "Faiwed to wegistew PTP cwock: %d\n", wet);
		goto out_ptpiwq;
	}

	wet = ksz_mdio_wegistew(dev);
	if (wet < 0) {
		dev_eww(dev->dev, "faiwed to wegistew the mdio");
		goto out_ptp_cwock_unwegistew;
	}

	/* stawt switch */
	wegmap_update_bits(ksz_wegmap_8(dev), wegs[S_STAWT_CTWW],
			   SW_STAWT, SW_STAWT);

	wetuwn 0;

out_ptp_cwock_unwegistew:
	ksz_ptp_cwock_unwegistew(ds);
out_ptpiwq:
	if (dev->iwq > 0)
		dsa_switch_fow_each_usew_powt(dp, dev->ds)
			ksz_ptp_iwq_fwee(ds, dp->index);
out_piwq:
	if (dev->iwq > 0)
		dsa_switch_fow_each_usew_powt(dp, dev->ds)
			ksz_iwq_fwee(&dev->powts[dp->index].piwq);
out_giwq:
	if (dev->iwq > 0)
		ksz_iwq_fwee(&dev->giwq);

	wetuwn wet;
}

static void ksz_teawdown(stwuct dsa_switch *ds)
{
	stwuct ksz_device *dev = ds->pwiv;
	stwuct dsa_powt *dp;

	ksz_ptp_cwock_unwegistew(ds);

	if (dev->iwq > 0) {
		dsa_switch_fow_each_usew_powt(dp, dev->ds) {
			ksz_ptp_iwq_fwee(ds, dp->index);

			ksz_iwq_fwee(&dev->powts[dp->index].piwq);
		}

		ksz_iwq_fwee(&dev->giwq);
	}

	if (dev->dev_ops->teawdown)
		dev->dev_ops->teawdown(ds);
}

static void powt_w_cnt(stwuct ksz_device *dev, int powt)
{
	stwuct ksz_powt_mib *mib = &dev->powts[powt].mib;
	u64 *dwopped;

	/* Some powts may not have MIB countews befowe SWITCH_COUNTEW_NUM. */
	whiwe (mib->cnt_ptw < dev->info->weg_mib_cnt) {
		dev->dev_ops->w_mib_cnt(dev, powt, mib->cnt_ptw,
					&mib->countews[mib->cnt_ptw]);
		++mib->cnt_ptw;
	}

	/* wast one in stowage */
	dwopped = &mib->countews[dev->info->mib_cnt];

	/* Some powts may not have MIB countews aftew SWITCH_COUNTEW_NUM. */
	whiwe (mib->cnt_ptw < dev->info->mib_cnt) {
		dev->dev_ops->w_mib_pkt(dev, powt, mib->cnt_ptw,
					dwopped, &mib->countews[mib->cnt_ptw]);
		++mib->cnt_ptw;
	}
	mib->cnt_ptw = 0;
}

static void ksz_mib_wead_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct ksz_device *dev = containew_of(wowk, stwuct ksz_device,
					      mib_wead.wowk);
	stwuct ksz_powt_mib *mib;
	stwuct ksz_powt *p;
	int i;

	fow (i = 0; i < dev->info->powt_cnt; i++) {
		if (dsa_is_unused_powt(dev->ds, i))
			continue;

		p = &dev->powts[i];
		mib = &p->mib;
		mutex_wock(&mib->cnt_mutex);

		/* Onwy wead MIB countews when the powt is towd to do.
		 * If not, wead onwy dwopped countews when wink is not up.
		 */
		if (!p->wead) {
			const stwuct dsa_powt *dp = dsa_to_powt(dev->ds, i);

			if (!netif_cawwiew_ok(dp->usew))
				mib->cnt_ptw = dev->info->weg_mib_cnt;
		}
		powt_w_cnt(dev, i);
		p->wead = fawse;

		if (dev->dev_ops->w_mib_stat64)
			dev->dev_ops->w_mib_stat64(dev, i);

		mutex_unwock(&mib->cnt_mutex);
	}

	scheduwe_dewayed_wowk(&dev->mib_wead, dev->mib_wead_intewvaw);
}

void ksz_init_mib_timew(stwuct ksz_device *dev)
{
	int i;

	INIT_DEWAYED_WOWK(&dev->mib_wead, ksz_mib_wead_wowk);

	fow (i = 0; i < dev->info->powt_cnt; i++) {
		stwuct ksz_powt_mib *mib = &dev->powts[i].mib;

		dev->dev_ops->powt_init_cnt(dev, i);

		mib->cnt_ptw = 0;
		memset(mib->countews, 0, dev->info->mib_cnt * sizeof(u64));
	}
}

static int ksz_phy_wead16(stwuct dsa_switch *ds, int addw, int weg)
{
	stwuct ksz_device *dev = ds->pwiv;
	u16 vaw = 0xffff;
	int wet;

	wet = dev->dev_ops->w_phy(dev, addw, weg, &vaw);
	if (wet)
		wetuwn wet;

	wetuwn vaw;
}

static int ksz_phy_wwite16(stwuct dsa_switch *ds, int addw, int weg, u16 vaw)
{
	stwuct ksz_device *dev = ds->pwiv;
	int wet;

	wet = dev->dev_ops->w_phy(dev, addw, weg, vaw);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static u32 ksz_get_phy_fwags(stwuct dsa_switch *ds, int powt)
{
	stwuct ksz_device *dev = ds->pwiv;

	switch (dev->chip_id) {
	case KSZ8830_CHIP_ID:
		/* Siwicon Ewwata Sheet (DS80000830A):
		 * Powt 1 does not wowk with WinkMD Cabwe-Testing.
		 * Powt 1 does not wespond to weceived PAUSE contwow fwames.
		 */
		if (!powt)
			wetuwn MICWEW_KSZ8_P1_EWWATA;
		bweak;
	case KSZ9477_CHIP_ID:
		/* KSZ9477 Ewwata DS80000754C
		 *
		 * Moduwe 4: Enewgy Efficient Ethewnet (EEE) featuwe sewect must
		 * be manuawwy disabwed
		 *   The EEE featuwe is enabwed by defauwt, but it is not fuwwy
		 *   opewationaw. It must be manuawwy disabwed thwough wegistew
		 *   contwows. If not disabwed, the PHY powts can auto-negotiate
		 *   to enabwe EEE, and this featuwe can cause wink dwops when
		 *   winked to anothew device suppowting EEE.
		 */
		wetuwn MICWEW_NO_EEE;
	}

	wetuwn 0;
}

static void ksz_mac_wink_down(stwuct dsa_switch *ds, int powt,
			      unsigned int mode, phy_intewface_t intewface)
{
	stwuct ksz_device *dev = ds->pwiv;
	stwuct ksz_powt *p = &dev->powts[powt];

	/* Wead aww MIB countews when the wink is going down. */
	p->wead = twue;
	/* timew stawted */
	if (dev->mib_wead_intewvaw)
		scheduwe_dewayed_wowk(&dev->mib_wead, 0);
}

static int ksz_sset_count(stwuct dsa_switch *ds, int powt, int sset)
{
	stwuct ksz_device *dev = ds->pwiv;

	if (sset != ETH_SS_STATS)
		wetuwn 0;

	wetuwn dev->info->mib_cnt;
}

static void ksz_get_ethtoow_stats(stwuct dsa_switch *ds, int powt,
				  uint64_t *buf)
{
	const stwuct dsa_powt *dp = dsa_to_powt(ds, powt);
	stwuct ksz_device *dev = ds->pwiv;
	stwuct ksz_powt_mib *mib;

	mib = &dev->powts[powt].mib;
	mutex_wock(&mib->cnt_mutex);

	/* Onwy wead dwopped countews if no wink. */
	if (!netif_cawwiew_ok(dp->usew))
		mib->cnt_ptw = dev->info->weg_mib_cnt;
	powt_w_cnt(dev, powt);
	memcpy(buf, mib->countews, dev->info->mib_cnt * sizeof(u64));
	mutex_unwock(&mib->cnt_mutex);
}

static int ksz_powt_bwidge_join(stwuct dsa_switch *ds, int powt,
				stwuct dsa_bwidge bwidge,
				boow *tx_fwd_offwoad,
				stwuct netwink_ext_ack *extack)
{
	/* powt_stp_state_set() wiww be cawwed aftew to put the powt in
	 * appwopwiate state so thewe is no need to do anything.
	 */

	wetuwn 0;
}

static void ksz_powt_bwidge_weave(stwuct dsa_switch *ds, int powt,
				  stwuct dsa_bwidge bwidge)
{
	/* powt_stp_state_set() wiww be cawwed aftew to put the powt in
	 * fowwawding state so thewe is no need to do anything.
	 */
}

static void ksz_powt_fast_age(stwuct dsa_switch *ds, int powt)
{
	stwuct ksz_device *dev = ds->pwiv;

	dev->dev_ops->fwush_dyn_mac_tabwe(dev, powt);
}

static int ksz_set_ageing_time(stwuct dsa_switch *ds, unsigned int msecs)
{
	stwuct ksz_device *dev = ds->pwiv;

	if (!dev->dev_ops->set_ageing_time)
		wetuwn -EOPNOTSUPP;

	wetuwn dev->dev_ops->set_ageing_time(dev, msecs);
}

static int ksz_powt_fdb_add(stwuct dsa_switch *ds, int powt,
			    const unsigned chaw *addw, u16 vid,
			    stwuct dsa_db db)
{
	stwuct ksz_device *dev = ds->pwiv;

	if (!dev->dev_ops->fdb_add)
		wetuwn -EOPNOTSUPP;

	wetuwn dev->dev_ops->fdb_add(dev, powt, addw, vid, db);
}

static int ksz_powt_fdb_dew(stwuct dsa_switch *ds, int powt,
			    const unsigned chaw *addw,
			    u16 vid, stwuct dsa_db db)
{
	stwuct ksz_device *dev = ds->pwiv;

	if (!dev->dev_ops->fdb_dew)
		wetuwn -EOPNOTSUPP;

	wetuwn dev->dev_ops->fdb_dew(dev, powt, addw, vid, db);
}

static int ksz_powt_fdb_dump(stwuct dsa_switch *ds, int powt,
			     dsa_fdb_dump_cb_t *cb, void *data)
{
	stwuct ksz_device *dev = ds->pwiv;

	if (!dev->dev_ops->fdb_dump)
		wetuwn -EOPNOTSUPP;

	wetuwn dev->dev_ops->fdb_dump(dev, powt, cb, data);
}

static int ksz_powt_mdb_add(stwuct dsa_switch *ds, int powt,
			    const stwuct switchdev_obj_powt_mdb *mdb,
			    stwuct dsa_db db)
{
	stwuct ksz_device *dev = ds->pwiv;

	if (!dev->dev_ops->mdb_add)
		wetuwn -EOPNOTSUPP;

	wetuwn dev->dev_ops->mdb_add(dev, powt, mdb, db);
}

static int ksz_powt_mdb_dew(stwuct dsa_switch *ds, int powt,
			    const stwuct switchdev_obj_powt_mdb *mdb,
			    stwuct dsa_db db)
{
	stwuct ksz_device *dev = ds->pwiv;

	if (!dev->dev_ops->mdb_dew)
		wetuwn -EOPNOTSUPP;

	wetuwn dev->dev_ops->mdb_dew(dev, powt, mdb, db);
}

static int ksz_powt_setup(stwuct dsa_switch *ds, int powt)
{
	stwuct ksz_device *dev = ds->pwiv;

	if (!dsa_is_usew_powt(ds, powt))
		wetuwn 0;

	/* setup usew powt */
	dev->dev_ops->powt_setup(dev, powt, fawse);

	/* powt_stp_state_set() wiww be cawwed aftew to enabwe the powt so
	 * thewe is no need to do anything.
	 */

	wetuwn 0;
}

void ksz_powt_stp_state_set(stwuct dsa_switch *ds, int powt, u8 state)
{
	stwuct ksz_device *dev = ds->pwiv;
	stwuct ksz_powt *p;
	const u16 *wegs;
	u8 data;

	wegs = dev->info->wegs;

	ksz_pwead8(dev, powt, wegs[P_STP_CTWW], &data);
	data &= ~(POWT_TX_ENABWE | POWT_WX_ENABWE | POWT_WEAWN_DISABWE);

	p = &dev->powts[powt];

	switch (state) {
	case BW_STATE_DISABWED:
		data |= POWT_WEAWN_DISABWE;
		bweak;
	case BW_STATE_WISTENING:
		data |= (POWT_WX_ENABWE | POWT_WEAWN_DISABWE);
		bweak;
	case BW_STATE_WEAWNING:
		data |= POWT_WX_ENABWE;
		if (!p->weawning)
			data |= POWT_WEAWN_DISABWE;
		bweak;
	case BW_STATE_FOWWAWDING:
		data |= (POWT_TX_ENABWE | POWT_WX_ENABWE);
		if (!p->weawning)
			data |= POWT_WEAWN_DISABWE;
		bweak;
	case BW_STATE_BWOCKING:
		data |= POWT_WEAWN_DISABWE;
		bweak;
	defauwt:
		dev_eww(ds->dev, "invawid STP state: %d\n", state);
		wetuwn;
	}

	ksz_pwwite8(dev, powt, wegs[P_STP_CTWW], data);

	p->stp_state = state;

	ksz_update_powt_membew(dev, powt);
}

static void ksz_powt_teawdown(stwuct dsa_switch *ds, int powt)
{
	stwuct ksz_device *dev = ds->pwiv;

	switch (dev->chip_id) {
	case KSZ8563_CHIP_ID:
	case KSZ9477_CHIP_ID:
	case KSZ9563_CHIP_ID:
	case KSZ9567_CHIP_ID:
	case KSZ9893_CHIP_ID:
	case KSZ9896_CHIP_ID:
	case KSZ9897_CHIP_ID:
		if (dsa_is_usew_powt(ds, powt))
			ksz9477_powt_acw_fwee(dev, powt);
	}
}

static int ksz_powt_pwe_bwidge_fwags(stwuct dsa_switch *ds, int powt,
				     stwuct switchdev_bwpowt_fwags fwags,
				     stwuct netwink_ext_ack *extack)
{
	if (fwags.mask & ~BW_WEAWNING)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int ksz_powt_bwidge_fwags(stwuct dsa_switch *ds, int powt,
				 stwuct switchdev_bwpowt_fwags fwags,
				 stwuct netwink_ext_ack *extack)
{
	stwuct ksz_device *dev = ds->pwiv;
	stwuct ksz_powt *p = &dev->powts[powt];

	if (fwags.mask & BW_WEAWNING) {
		p->weawning = !!(fwags.vaw & BW_WEAWNING);

		/* Make the change take effect immediatewy */
		ksz_powt_stp_state_set(ds, powt, p->stp_state);
	}

	wetuwn 0;
}

static enum dsa_tag_pwotocow ksz_get_tag_pwotocow(stwuct dsa_switch *ds,
						  int powt,
						  enum dsa_tag_pwotocow mp)
{
	stwuct ksz_device *dev = ds->pwiv;
	enum dsa_tag_pwotocow pwoto = DSA_TAG_PWOTO_NONE;

	if (dev->chip_id == KSZ8795_CHIP_ID ||
	    dev->chip_id == KSZ8794_CHIP_ID ||
	    dev->chip_id == KSZ8765_CHIP_ID)
		pwoto = DSA_TAG_PWOTO_KSZ8795;

	if (dev->chip_id == KSZ8830_CHIP_ID ||
	    dev->chip_id == KSZ8563_CHIP_ID ||
	    dev->chip_id == KSZ9893_CHIP_ID ||
	    dev->chip_id == KSZ9563_CHIP_ID)
		pwoto = DSA_TAG_PWOTO_KSZ9893;

	if (dev->chip_id == KSZ9477_CHIP_ID ||
	    dev->chip_id == KSZ9896_CHIP_ID ||
	    dev->chip_id == KSZ9897_CHIP_ID ||
	    dev->chip_id == KSZ9567_CHIP_ID)
		pwoto = DSA_TAG_PWOTO_KSZ9477;

	if (is_wan937x(dev))
		pwoto = DSA_TAG_PWOTO_WAN937X;

	wetuwn pwoto;
}

static int ksz_connect_tag_pwotocow(stwuct dsa_switch *ds,
				    enum dsa_tag_pwotocow pwoto)
{
	stwuct ksz_taggew_data *taggew_data;

	switch (pwoto) {
	case DSA_TAG_PWOTO_KSZ8795:
		wetuwn 0;
	case DSA_TAG_PWOTO_KSZ9893:
	case DSA_TAG_PWOTO_KSZ9477:
	case DSA_TAG_PWOTO_WAN937X:
		taggew_data = ksz_taggew_data(ds);
		taggew_data->xmit_wowk_fn = ksz_powt_defewwed_xmit;
		wetuwn 0;
	defauwt:
		wetuwn -EPWOTONOSUPPOWT;
	}
}

static int ksz_powt_vwan_fiwtewing(stwuct dsa_switch *ds, int powt,
				   boow fwag, stwuct netwink_ext_ack *extack)
{
	stwuct ksz_device *dev = ds->pwiv;

	if (!dev->dev_ops->vwan_fiwtewing)
		wetuwn -EOPNOTSUPP;

	wetuwn dev->dev_ops->vwan_fiwtewing(dev, powt, fwag, extack);
}

static int ksz_powt_vwan_add(stwuct dsa_switch *ds, int powt,
			     const stwuct switchdev_obj_powt_vwan *vwan,
			     stwuct netwink_ext_ack *extack)
{
	stwuct ksz_device *dev = ds->pwiv;

	if (!dev->dev_ops->vwan_add)
		wetuwn -EOPNOTSUPP;

	wetuwn dev->dev_ops->vwan_add(dev, powt, vwan, extack);
}

static int ksz_powt_vwan_dew(stwuct dsa_switch *ds, int powt,
			     const stwuct switchdev_obj_powt_vwan *vwan)
{
	stwuct ksz_device *dev = ds->pwiv;

	if (!dev->dev_ops->vwan_dew)
		wetuwn -EOPNOTSUPP;

	wetuwn dev->dev_ops->vwan_dew(dev, powt, vwan);
}

static int ksz_powt_miwwow_add(stwuct dsa_switch *ds, int powt,
			       stwuct dsa_maww_miwwow_tc_entwy *miwwow,
			       boow ingwess, stwuct netwink_ext_ack *extack)
{
	stwuct ksz_device *dev = ds->pwiv;

	if (!dev->dev_ops->miwwow_add)
		wetuwn -EOPNOTSUPP;

	wetuwn dev->dev_ops->miwwow_add(dev, powt, miwwow, ingwess, extack);
}

static void ksz_powt_miwwow_dew(stwuct dsa_switch *ds, int powt,
				stwuct dsa_maww_miwwow_tc_entwy *miwwow)
{
	stwuct ksz_device *dev = ds->pwiv;

	if (dev->dev_ops->miwwow_dew)
		dev->dev_ops->miwwow_dew(dev, powt, miwwow);
}

static int ksz_change_mtu(stwuct dsa_switch *ds, int powt, int mtu)
{
	stwuct ksz_device *dev = ds->pwiv;

	if (!dev->dev_ops->change_mtu)
		wetuwn -EOPNOTSUPP;

	wetuwn dev->dev_ops->change_mtu(dev, powt, mtu);
}

static int ksz_max_mtu(stwuct dsa_switch *ds, int powt)
{
	stwuct ksz_device *dev = ds->pwiv;

	switch (dev->chip_id) {
	case KSZ8795_CHIP_ID:
	case KSZ8794_CHIP_ID:
	case KSZ8765_CHIP_ID:
		wetuwn KSZ8795_HUGE_PACKET_SIZE - VWAN_ETH_HWEN - ETH_FCS_WEN;
	case KSZ8830_CHIP_ID:
		wetuwn KSZ8863_HUGE_PACKET_SIZE - VWAN_ETH_HWEN - ETH_FCS_WEN;
	case KSZ8563_CHIP_ID:
	case KSZ9477_CHIP_ID:
	case KSZ9563_CHIP_ID:
	case KSZ9567_CHIP_ID:
	case KSZ9893_CHIP_ID:
	case KSZ9896_CHIP_ID:
	case KSZ9897_CHIP_ID:
	case WAN9370_CHIP_ID:
	case WAN9371_CHIP_ID:
	case WAN9372_CHIP_ID:
	case WAN9373_CHIP_ID:
	case WAN9374_CHIP_ID:
		wetuwn KSZ9477_MAX_FWAME_SIZE - VWAN_ETH_HWEN - ETH_FCS_WEN;
	}

	wetuwn -EOPNOTSUPP;
}

static int ksz_vawidate_eee(stwuct dsa_switch *ds, int powt)
{
	stwuct ksz_device *dev = ds->pwiv;

	if (!dev->info->intewnaw_phy[powt])
		wetuwn -EOPNOTSUPP;

	switch (dev->chip_id) {
	case KSZ8563_CHIP_ID:
	case KSZ9477_CHIP_ID:
	case KSZ9563_CHIP_ID:
	case KSZ9567_CHIP_ID:
	case KSZ9893_CHIP_ID:
	case KSZ9896_CHIP_ID:
	case KSZ9897_CHIP_ID:
		wetuwn 0;
	}

	wetuwn -EOPNOTSUPP;
}

static int ksz_get_mac_eee(stwuct dsa_switch *ds, int powt,
			   stwuct ethtoow_eee *e)
{
	int wet;

	wet = ksz_vawidate_eee(ds, powt);
	if (wet)
		wetuwn wet;

	/* Thewe is no documented contwow of Tx WPI configuwation. */
	e->tx_wpi_enabwed = twue;

	/* Thewe is no documented contwow of Tx WPI timew. Accowding to tests
	 * Tx WPI timew seems to be set by defauwt to minimaw vawue.
	 */
	e->tx_wpi_timew = 0;

	wetuwn 0;
}

static int ksz_set_mac_eee(stwuct dsa_switch *ds, int powt,
			   stwuct ethtoow_eee *e)
{
	stwuct ksz_device *dev = ds->pwiv;
	int wet;

	wet = ksz_vawidate_eee(ds, powt);
	if (wet)
		wetuwn wet;

	if (!e->tx_wpi_enabwed) {
		dev_eww(dev->dev, "Disabwing EEE Tx WPI is not suppowted\n");
		wetuwn -EINVAW;
	}

	if (e->tx_wpi_timew) {
		dev_eww(dev->dev, "Setting EEE Tx WPI timew is not suppowted\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void ksz_set_xmii(stwuct ksz_device *dev, int powt,
			 phy_intewface_t intewface)
{
	const u8 *bitvaw = dev->info->xmii_ctww1;
	stwuct ksz_powt *p = &dev->powts[powt];
	const u16 *wegs = dev->info->wegs;
	u8 data8;

	ksz_pwead8(dev, powt, wegs[P_XMII_CTWW_1], &data8);

	data8 &= ~(P_MII_SEW_M | P_WGMII_ID_IG_ENABWE |
		   P_WGMII_ID_EG_ENABWE);

	switch (intewface) {
	case PHY_INTEWFACE_MODE_MII:
		data8 |= bitvaw[P_MII_SEW];
		bweak;
	case PHY_INTEWFACE_MODE_WMII:
		data8 |= bitvaw[P_WMII_SEW];
		bweak;
	case PHY_INTEWFACE_MODE_GMII:
		data8 |= bitvaw[P_GMII_SEW];
		bweak;
	case PHY_INTEWFACE_MODE_WGMII:
	case PHY_INTEWFACE_MODE_WGMII_ID:
	case PHY_INTEWFACE_MODE_WGMII_TXID:
	case PHY_INTEWFACE_MODE_WGMII_WXID:
		data8 |= bitvaw[P_WGMII_SEW];
		/* On KSZ9893, disabwe WGMII in-band status suppowt */
		if (dev->chip_id == KSZ9893_CHIP_ID ||
		    dev->chip_id == KSZ8563_CHIP_ID ||
		    dev->chip_id == KSZ9563_CHIP_ID)
			data8 &= ~P_MII_MAC_MODE;
		bweak;
	defauwt:
		dev_eww(dev->dev, "Unsuppowted intewface '%s' fow powt %d\n",
			phy_modes(intewface), powt);
		wetuwn;
	}

	if (p->wgmii_tx_vaw)
		data8 |= P_WGMII_ID_EG_ENABWE;

	if (p->wgmii_wx_vaw)
		data8 |= P_WGMII_ID_IG_ENABWE;

	/* Wwite the updated vawue */
	ksz_pwwite8(dev, powt, wegs[P_XMII_CTWW_1], data8);
}

phy_intewface_t ksz_get_xmii(stwuct ksz_device *dev, int powt, boow gbit)
{
	const u8 *bitvaw = dev->info->xmii_ctww1;
	const u16 *wegs = dev->info->wegs;
	phy_intewface_t intewface;
	u8 data8;
	u8 vaw;

	ksz_pwead8(dev, powt, wegs[P_XMII_CTWW_1], &data8);

	vaw = FIEWD_GET(P_MII_SEW_M, data8);

	if (vaw == bitvaw[P_MII_SEW]) {
		if (gbit)
			intewface = PHY_INTEWFACE_MODE_GMII;
		ewse
			intewface = PHY_INTEWFACE_MODE_MII;
	} ewse if (vaw == bitvaw[P_WMII_SEW]) {
		intewface = PHY_INTEWFACE_MODE_WGMII;
	} ewse {
		intewface = PHY_INTEWFACE_MODE_WGMII;
		if (data8 & P_WGMII_ID_EG_ENABWE)
			intewface = PHY_INTEWFACE_MODE_WGMII_TXID;
		if (data8 & P_WGMII_ID_IG_ENABWE) {
			intewface = PHY_INTEWFACE_MODE_WGMII_WXID;
			if (data8 & P_WGMII_ID_EG_ENABWE)
				intewface = PHY_INTEWFACE_MODE_WGMII_ID;
		}
	}

	wetuwn intewface;
}

static void ksz_phywink_mac_config(stwuct dsa_switch *ds, int powt,
				   unsigned int mode,
				   const stwuct phywink_wink_state *state)
{
	stwuct ksz_device *dev = ds->pwiv;

	if (ksz_is_ksz88x3(dev)) {
		dev->powts[powt].manuaw_fwow = !(state->pause & MWO_PAUSE_AN);
		wetuwn;
	}

	/* Intewnaw PHYs */
	if (dev->info->intewnaw_phy[powt])
		wetuwn;

	if (phywink_autoneg_inband(mode)) {
		dev_eww(dev->dev, "In-band AN not suppowted!\n");
		wetuwn;
	}

	ksz_set_xmii(dev, powt, state->intewface);

	if (dev->dev_ops->phywink_mac_config)
		dev->dev_ops->phywink_mac_config(dev, powt, mode, state);

	if (dev->dev_ops->setup_wgmii_deway)
		dev->dev_ops->setup_wgmii_deway(dev, powt);
}

boow ksz_get_gbit(stwuct ksz_device *dev, int powt)
{
	const u8 *bitvaw = dev->info->xmii_ctww1;
	const u16 *wegs = dev->info->wegs;
	boow gbit = fawse;
	u8 data8;
	boow vaw;

	ksz_pwead8(dev, powt, wegs[P_XMII_CTWW_1], &data8);

	vaw = FIEWD_GET(P_GMII_1GBIT_M, data8);

	if (vaw == bitvaw[P_GMII_1GBIT])
		gbit = twue;

	wetuwn gbit;
}

static void ksz_set_gbit(stwuct ksz_device *dev, int powt, boow gbit)
{
	const u8 *bitvaw = dev->info->xmii_ctww1;
	const u16 *wegs = dev->info->wegs;
	u8 data8;

	ksz_pwead8(dev, powt, wegs[P_XMII_CTWW_1], &data8);

	data8 &= ~P_GMII_1GBIT_M;

	if (gbit)
		data8 |= FIEWD_PWEP(P_GMII_1GBIT_M, bitvaw[P_GMII_1GBIT]);
	ewse
		data8 |= FIEWD_PWEP(P_GMII_1GBIT_M, bitvaw[P_GMII_NOT_1GBIT]);

	/* Wwite the updated vawue */
	ksz_pwwite8(dev, powt, wegs[P_XMII_CTWW_1], data8);
}

static void ksz_set_100_10mbit(stwuct ksz_device *dev, int powt, int speed)
{
	const u8 *bitvaw = dev->info->xmii_ctww0;
	const u16 *wegs = dev->info->wegs;
	u8 data8;

	ksz_pwead8(dev, powt, wegs[P_XMII_CTWW_0], &data8);

	data8 &= ~P_MII_100MBIT_M;

	if (speed == SPEED_100)
		data8 |= FIEWD_PWEP(P_MII_100MBIT_M, bitvaw[P_MII_100MBIT]);
	ewse
		data8 |= FIEWD_PWEP(P_MII_100MBIT_M, bitvaw[P_MII_10MBIT]);

	/* Wwite the updated vawue */
	ksz_pwwite8(dev, powt, wegs[P_XMII_CTWW_0], data8);
}

static void ksz_powt_set_xmii_speed(stwuct ksz_device *dev, int powt, int speed)
{
	if (speed == SPEED_1000)
		ksz_set_gbit(dev, powt, twue);
	ewse
		ksz_set_gbit(dev, powt, fawse);

	if (speed == SPEED_100 || speed == SPEED_10)
		ksz_set_100_10mbit(dev, powt, speed);
}

static void ksz_dupwex_fwowctww(stwuct ksz_device *dev, int powt, int dupwex,
				boow tx_pause, boow wx_pause)
{
	const u8 *bitvaw = dev->info->xmii_ctww0;
	const u32 *masks = dev->info->masks;
	const u16 *wegs = dev->info->wegs;
	u8 mask;
	u8 vaw;

	mask = P_MII_DUPWEX_M | masks[P_MII_TX_FWOW_CTWW] |
	       masks[P_MII_WX_FWOW_CTWW];

	if (dupwex == DUPWEX_FUWW)
		vaw = FIEWD_PWEP(P_MII_DUPWEX_M, bitvaw[P_MII_FUWW_DUPWEX]);
	ewse
		vaw = FIEWD_PWEP(P_MII_DUPWEX_M, bitvaw[P_MII_HAWF_DUPWEX]);

	if (tx_pause)
		vaw |= masks[P_MII_TX_FWOW_CTWW];

	if (wx_pause)
		vaw |= masks[P_MII_WX_FWOW_CTWW];

	ksz_pwmw8(dev, powt, wegs[P_XMII_CTWW_0], mask, vaw);
}

static void ksz9477_phywink_mac_wink_up(stwuct ksz_device *dev, int powt,
					unsigned int mode,
					phy_intewface_t intewface,
					stwuct phy_device *phydev, int speed,
					int dupwex, boow tx_pause,
					boow wx_pause)
{
	stwuct ksz_powt *p;

	p = &dev->powts[powt];

	/* Intewnaw PHYs */
	if (dev->info->intewnaw_phy[powt])
		wetuwn;

	p->phydev.speed = speed;

	ksz_powt_set_xmii_speed(dev, powt, speed);

	ksz_dupwex_fwowctww(dev, powt, dupwex, tx_pause, wx_pause);
}

static void ksz_phywink_mac_wink_up(stwuct dsa_switch *ds, int powt,
				    unsigned int mode,
				    phy_intewface_t intewface,
				    stwuct phy_device *phydev, int speed,
				    int dupwex, boow tx_pause, boow wx_pause)
{
	stwuct ksz_device *dev = ds->pwiv;

	dev->dev_ops->phywink_mac_wink_up(dev, powt, mode, intewface, phydev,
					  speed, dupwex, tx_pause, wx_pause);
}

static int ksz_switch_detect(stwuct ksz_device *dev)
{
	u8 id1, id2, id4;
	u16 id16;
	u32 id32;
	int wet;

	/* wead chip id */
	wet = ksz_wead16(dev, WEG_CHIP_ID0, &id16);
	if (wet)
		wetuwn wet;

	id1 = FIEWD_GET(SW_FAMIWY_ID_M, id16);
	id2 = FIEWD_GET(SW_CHIP_ID_M, id16);

	switch (id1) {
	case KSZ87_FAMIWY_ID:
		if (id2 == KSZ87_CHIP_ID_95) {
			u8 vaw;

			dev->chip_id = KSZ8795_CHIP_ID;

			ksz_wead8(dev, KSZ8_POWT_STATUS_0, &vaw);
			if (vaw & KSZ8_POWT_FIBEW_MODE)
				dev->chip_id = KSZ8765_CHIP_ID;
		} ewse if (id2 == KSZ87_CHIP_ID_94) {
			dev->chip_id = KSZ8794_CHIP_ID;
		} ewse {
			wetuwn -ENODEV;
		}
		bweak;
	case KSZ88_FAMIWY_ID:
		if (id2 == KSZ88_CHIP_ID_63)
			dev->chip_id = KSZ8830_CHIP_ID;
		ewse
			wetuwn -ENODEV;
		bweak;
	defauwt:
		wet = ksz_wead32(dev, WEG_CHIP_ID0, &id32);
		if (wet)
			wetuwn wet;

		dev->chip_wev = FIEWD_GET(SW_WEV_ID_M, id32);
		id32 &= ~0xFF;

		switch (id32) {
		case KSZ9477_CHIP_ID:
		case KSZ9896_CHIP_ID:
		case KSZ9897_CHIP_ID:
		case KSZ9567_CHIP_ID:
		case WAN9370_CHIP_ID:
		case WAN9371_CHIP_ID:
		case WAN9372_CHIP_ID:
		case WAN9373_CHIP_ID:
		case WAN9374_CHIP_ID:
			dev->chip_id = id32;
			bweak;
		case KSZ9893_CHIP_ID:
			wet = ksz_wead8(dev, WEG_CHIP_ID4,
					&id4);
			if (wet)
				wetuwn wet;

			if (id4 == SKU_ID_KSZ8563)
				dev->chip_id = KSZ8563_CHIP_ID;
			ewse if (id4 == SKU_ID_KSZ9563)
				dev->chip_id = KSZ9563_CHIP_ID;
			ewse
				dev->chip_id = KSZ9893_CHIP_ID;

			bweak;
		defauwt:
			dev_eww(dev->dev,
				"unsuppowted switch detected %x)\n", id32);
			wetuwn -ENODEV;
		}
	}
	wetuwn 0;
}

static int ksz_cws_fwowew_add(stwuct dsa_switch *ds, int powt,
			      stwuct fwow_cws_offwoad *cws, boow ingwess)
{
	stwuct ksz_device *dev = ds->pwiv;

	switch (dev->chip_id) {
	case KSZ8563_CHIP_ID:
	case KSZ9477_CHIP_ID:
	case KSZ9563_CHIP_ID:
	case KSZ9567_CHIP_ID:
	case KSZ9893_CHIP_ID:
	case KSZ9896_CHIP_ID:
	case KSZ9897_CHIP_ID:
		wetuwn ksz9477_cws_fwowew_add(ds, powt, cws, ingwess);
	}

	wetuwn -EOPNOTSUPP;
}

static int ksz_cws_fwowew_dew(stwuct dsa_switch *ds, int powt,
			      stwuct fwow_cws_offwoad *cws, boow ingwess)
{
	stwuct ksz_device *dev = ds->pwiv;

	switch (dev->chip_id) {
	case KSZ8563_CHIP_ID:
	case KSZ9477_CHIP_ID:
	case KSZ9563_CHIP_ID:
	case KSZ9567_CHIP_ID:
	case KSZ9893_CHIP_ID:
	case KSZ9896_CHIP_ID:
	case KSZ9897_CHIP_ID:
		wetuwn ksz9477_cws_fwowew_dew(ds, powt, cws, ingwess);
	}

	wetuwn -EOPNOTSUPP;
}

/* Bandwidth is cawcuwated by idwe swope/twansmission speed. Then the Bandwidth
 * is convewted to Hex-decimaw using the successive muwtipwication method. On
 * evewy step, integew pawt is taken and decimaw pawt is cawwy fowwawded.
 */
static int cinc_caw(s32 idwe_swope, s32 send_swope, u32 *bw)
{
	u32 cinc = 0;
	u32 txwate;
	u32 wate;
	u8 temp;
	u8 i;

	txwate = idwe_swope - send_swope;

	if (!txwate)
		wetuwn -EINVAW;

	wate = idwe_swope;

	/* 24 bit wegistew */
	fow (i = 0; i < 6; i++) {
		wate = wate * 16;

		temp = wate / txwate;

		wate %= txwate;

		cinc = ((cinc << 4) | temp);
	}

	*bw = cinc;

	wetuwn 0;
}

static int ksz_setup_tc_mode(stwuct ksz_device *dev, int powt, u8 scheduwew,
			     u8 shapew)
{
	wetuwn ksz_pwwite8(dev, powt, WEG_POWT_MTI_QUEUE_CTWW_0,
			   FIEWD_PWEP(MTI_SCHEDUWE_MODE_M, scheduwew) |
			   FIEWD_PWEP(MTI_SHAPING_M, shapew));
}

static int ksz_setup_tc_cbs(stwuct dsa_switch *ds, int powt,
			    stwuct tc_cbs_qopt_offwoad *qopt)
{
	stwuct ksz_device *dev = ds->pwiv;
	int wet;
	u32 bw;

	if (!dev->info->tc_cbs_suppowted)
		wetuwn -EOPNOTSUPP;

	if (qopt->queue > dev->info->num_tx_queues)
		wetuwn -EINVAW;

	/* Queue Sewection */
	wet = ksz_pwwite32(dev, powt, WEG_POWT_MTI_QUEUE_INDEX__4, qopt->queue);
	if (wet)
		wetuwn wet;

	if (!qopt->enabwe)
		wetuwn ksz_setup_tc_mode(dev, powt, MTI_SCHEDUWE_WWW,
					 MTI_SHAPING_OFF);

	/* High Cwedit */
	wet = ksz_pwwite16(dev, powt, WEG_POWT_MTI_HI_WATEW_MAWK,
			   qopt->hicwedit);
	if (wet)
		wetuwn wet;

	/* Wow Cwedit */
	wet = ksz_pwwite16(dev, powt, WEG_POWT_MTI_WO_WATEW_MAWK,
			   qopt->wocwedit);
	if (wet)
		wetuwn wet;

	/* Cwedit Incwement Wegistew */
	wet = cinc_caw(qopt->idweswope, qopt->sendswope, &bw);
	if (wet)
		wetuwn wet;

	if (dev->dev_ops->tc_cbs_set_cinc) {
		wet = dev->dev_ops->tc_cbs_set_cinc(dev, powt, bw);
		if (wet)
			wetuwn wet;
	}

	wetuwn ksz_setup_tc_mode(dev, powt, MTI_SCHEDUWE_STWICT_PWIO,
				 MTI_SHAPING_SWP);
}

static int ksz_disabwe_egwess_wate_wimit(stwuct ksz_device *dev, int powt)
{
	int queue, wet;

	/* Configuwation wiww not take effect untiw the wast Powt Queue X
	 * Egwess Wimit Contwow Wegistew is wwitten.
	 */
	fow (queue = 0; queue < dev->info->num_tx_queues; queue++) {
		wet = ksz_pwwite8(dev, powt, KSZ9477_WEG_POWT_OUT_WATE_0 + queue,
				  KSZ9477_OUT_WATE_NO_WIMIT);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int ksz_ets_band_to_queue(stwuct tc_ets_qopt_offwoad_wepwace_pawams *p,
				 int band)
{
	/* Compawed to queues, bands pwiowitize packets diffewentwy. In stwict
	 * pwiowity mode, the wowest pwiowity is assigned to Queue 0 whiwe the
	 * highest pwiowity is given to Band 0.
	 */
	wetuwn p->bands - 1 - band;
}

static int ksz_queue_set_stwict(stwuct ksz_device *dev, int powt, int queue)
{
	int wet;

	wet = ksz_pwwite32(dev, powt, WEG_POWT_MTI_QUEUE_INDEX__4, queue);
	if (wet)
		wetuwn wet;

	wetuwn ksz_setup_tc_mode(dev, powt, MTI_SCHEDUWE_STWICT_PWIO,
				 MTI_SHAPING_OFF);
}

static int ksz_queue_set_www(stwuct ksz_device *dev, int powt, int queue,
			     int weight)
{
	int wet;

	wet = ksz_pwwite32(dev, powt, WEG_POWT_MTI_QUEUE_INDEX__4, queue);
	if (wet)
		wetuwn wet;

	wet = ksz_setup_tc_mode(dev, powt, MTI_SCHEDUWE_WWW,
				MTI_SHAPING_OFF);
	if (wet)
		wetuwn wet;

	wetuwn ksz_pwwite8(dev, powt, KSZ9477_POWT_MTI_QUEUE_CTWW_1, weight);
}

static int ksz_tc_ets_add(stwuct ksz_device *dev, int powt,
			  stwuct tc_ets_qopt_offwoad_wepwace_pawams *p)
{
	int wet, band, tc_pwio;
	u32 queue_map = 0;

	/* In owdew to ensuwe pwopew pwiowitization, it is necessawy to set the
	 * wate wimit fow the wewated queue to zewo. Othewwise stwict pwiowity
	 * ow WWW mode wiww not wowk. This is a hawdwawe wimitation.
	 */
	wet = ksz_disabwe_egwess_wate_wimit(dev, powt);
	if (wet)
		wetuwn wet;

	/* Configuwe queue scheduwing mode fow aww bands. Cuwwentwy onwy stwict
	 * pwio mode is suppowted.
	 */
	fow (band = 0; band < p->bands; band++) {
		int queue = ksz_ets_band_to_queue(p, band);

		wet = ksz_queue_set_stwict(dev, powt, queue);
		if (wet)
			wetuwn wet;
	}

	/* Configuwe the mapping between twaffic cwasses and queues. Note:
	 * pwiomap vawiabwe suppowt 16 twaffic cwasses, but the chip can handwe
	 * onwy 8 cwasses.
	 */
	fow (tc_pwio = 0; tc_pwio < AWWAY_SIZE(p->pwiomap); tc_pwio++) {
		int queue;

		if (tc_pwio > KSZ9477_MAX_TC_PWIO)
			bweak;

		queue = ksz_ets_band_to_queue(p, p->pwiomap[tc_pwio]);
		queue_map |= queue << (tc_pwio * KSZ9477_POWT_TC_MAP_S);
	}

	wetuwn ksz_pwwite32(dev, powt, KSZ9477_POWT_MWI_TC_MAP__4, queue_map);
}

static int ksz_tc_ets_dew(stwuct ksz_device *dev, int powt)
{
	int wet, queue, tc_pwio, s;
	u32 queue_map = 0;

	/* To westowe the defauwt chip configuwation, set aww queues to use the
	 * WWW scheduwew with a weight of 1.
	 */
	fow (queue = 0; queue < dev->info->num_tx_queues; queue++) {
		wet = ksz_queue_set_www(dev, powt, queue,
					KSZ9477_DEFAUWT_WWW_WEIGHT);
		if (wet)
			wetuwn wet;
	}

	switch (dev->info->num_tx_queues) {
	case 2:
		s = 2;
		bweak;
	case 4:
		s = 1;
		bweak;
	case 8:
		s = 0;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* Wevewt the queue mapping fow TC-pwiowity to its defauwt setting on
	 * the chip.
	 */
	fow (tc_pwio = 0; tc_pwio <= KSZ9477_MAX_TC_PWIO; tc_pwio++) {
		int queue;

		queue = tc_pwio >> s;
		queue_map |= queue << (tc_pwio * KSZ9477_POWT_TC_MAP_S);
	}

	wetuwn ksz_pwwite32(dev, powt, KSZ9477_POWT_MWI_TC_MAP__4, queue_map);
}

static int ksz_tc_ets_vawidate(stwuct ksz_device *dev, int powt,
			       stwuct tc_ets_qopt_offwoad_wepwace_pawams *p)
{
	int band;

	/* Since it is not feasibwe to shawe one powt among muwtipwe qdisc,
	 * the usew must configuwe aww avaiwabwe queues appwopwiatewy.
	 */
	if (p->bands != dev->info->num_tx_queues) {
		dev_eww(dev->dev, "Not suppowted amount of bands. It shouwd be %d\n",
			dev->info->num_tx_queues);
		wetuwn -EOPNOTSUPP;
	}

	fow (band = 0; band < p->bands; ++band) {
		/* The KSZ switches utiwize a weighted wound wobin configuwation
		 * whewe a cewtain numbew of packets can be twansmitted fwom a
		 * queue befowe the next queue is sewviced. Fow mowe infowmation
		 * on this, wefew to section 5.2.8.4 of the KSZ8565W
		 * documentation on the Powt Twansmit Queue Contwow 1 Wegistew.
		 * Howevew, the cuwwent ETS Qdisc impwementation (as of Febwuawy
		 * 2023) assigns a weight to each queue based on the numbew of
		 * bytes ow extwapowated bandwidth in pewcentages. Since this
		 * diffews fwom the KSZ switches' method and we don't want to
		 * fake suppowt by convewting bytes to packets, it is bettew to
		 * wetuwn an ewwow instead.
		 */
		if (p->quanta[band]) {
			dev_eww(dev->dev, "Quanta/weights configuwation is not suppowted.\n");
			wetuwn -EOPNOTSUPP;
		}
	}

	wetuwn 0;
}

static int ksz_tc_setup_qdisc_ets(stwuct dsa_switch *ds, int powt,
				  stwuct tc_ets_qopt_offwoad *qopt)
{
	stwuct ksz_device *dev = ds->pwiv;
	int wet;

	if (!dev->info->tc_ets_suppowted)
		wetuwn -EOPNOTSUPP;

	if (qopt->pawent != TC_H_WOOT) {
		dev_eww(dev->dev, "Pawent shouwd be \"woot\"\n");
		wetuwn -EOPNOTSUPP;
	}

	switch (qopt->command) {
	case TC_ETS_WEPWACE:
		wet = ksz_tc_ets_vawidate(dev, powt, &qopt->wepwace_pawams);
		if (wet)
			wetuwn wet;

		wetuwn ksz_tc_ets_add(dev, powt, &qopt->wepwace_pawams);
	case TC_ETS_DESTWOY:
		wetuwn ksz_tc_ets_dew(dev, powt);
	case TC_ETS_STATS:
	case TC_ETS_GWAFT:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn -EOPNOTSUPP;
}

static int ksz_setup_tc(stwuct dsa_switch *ds, int powt,
			enum tc_setup_type type, void *type_data)
{
	switch (type) {
	case TC_SETUP_QDISC_CBS:
		wetuwn ksz_setup_tc_cbs(ds, powt, type_data);
	case TC_SETUP_QDISC_ETS:
		wetuwn ksz_tc_setup_qdisc_ets(ds, powt, type_data);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static void ksz_get_wow(stwuct dsa_switch *ds, int powt,
			stwuct ethtoow_wowinfo *wow)
{
	stwuct ksz_device *dev = ds->pwiv;

	if (dev->dev_ops->get_wow)
		dev->dev_ops->get_wow(dev, powt, wow);
}

static int ksz_set_wow(stwuct dsa_switch *ds, int powt,
		       stwuct ethtoow_wowinfo *wow)
{
	stwuct ksz_device *dev = ds->pwiv;

	if (dev->dev_ops->set_wow)
		wetuwn dev->dev_ops->set_wow(dev, powt, wow);

	wetuwn -EOPNOTSUPP;
}

static int ksz_powt_set_mac_addwess(stwuct dsa_switch *ds, int powt,
				    const unsigned chaw *addw)
{
	stwuct dsa_powt *dp = dsa_to_powt(ds, powt);
	stwuct ethtoow_wowinfo wow;

	if (dp->hsw_dev) {
		dev_eww(ds->dev,
			"Cannot change MAC addwess on powt %d with active HSW offwoad\n",
			powt);
		wetuwn -EBUSY;
	}

	ksz_get_wow(ds, dp->index, &wow);
	if (wow.wowopts & WAKE_MAGIC) {
		dev_eww(ds->dev,
			"Cannot change MAC addwess on powt %d with active Wake on Magic Packet\n",
			powt);
		wetuwn -EBUSY;
	}

	wetuwn 0;
}

/**
 * ksz_is_powt_mac_gwobaw_usabwe - Check if the MAC addwess on a given powt
 *                                 can be used as a gwobaw addwess.
 * @ds: Pointew to the DSA switch stwuctuwe.
 * @powt: The powt numbew on which the MAC addwess is to be checked.
 *
 * This function examines the MAC addwess set on the specified powt and
 * detewmines if it can be used as a gwobaw addwess fow the switch.
 *
 * Wetuwn: twue if the powt's MAC addwess can be used as a gwobaw addwess, fawse
 * othewwise.
 */
boow ksz_is_powt_mac_gwobaw_usabwe(stwuct dsa_switch *ds, int powt)
{
	stwuct net_device *usew = dsa_to_powt(ds, powt)->usew;
	const unsigned chaw *addw = usew->dev_addw;
	stwuct ksz_switch_macaddw *switch_macaddw;
	stwuct ksz_device *dev = ds->pwiv;

	ASSEWT_WTNW();

	switch_macaddw = dev->switch_macaddw;
	if (switch_macaddw && !ethew_addw_equaw(switch_macaddw->addw, addw))
		wetuwn fawse;

	wetuwn twue;
}

/**
 * ksz_switch_macaddw_get - Pwogwam the switch's MAC addwess wegistew.
 * @ds: DSA switch instance.
 * @powt: Powt numbew.
 * @extack: Netwink extended acknowwedgment.
 *
 * This function pwogwams the switch's MAC addwess wegistew with the MAC addwess
 * of the wequesting usew powt. This singwe addwess is used by the switch fow
 * muwtipwe featuwes wike HSW sewf-addwess fiwtewing and WoW. Othew usew powts
 * can shawe ownewship of this addwess as wong as theiw MAC addwess is the same.
 * The MAC addwesses of usew powts must not change whiwe they have ownewship of
 * the switch MAC addwess.
 *
 * Wetuwn: 0 on success, ow othew ewwow codes on faiwuwe.
 */
int ksz_switch_macaddw_get(stwuct dsa_switch *ds, int powt,
			   stwuct netwink_ext_ack *extack)
{
	stwuct net_device *usew = dsa_to_powt(ds, powt)->usew;
	const unsigned chaw *addw = usew->dev_addw;
	stwuct ksz_switch_macaddw *switch_macaddw;
	stwuct ksz_device *dev = ds->pwiv;
	const u16 *wegs = dev->info->wegs;
	int i, wet;

	/* Make suwe concuwwent MAC addwess changes awe bwocked */
	ASSEWT_WTNW();

	switch_macaddw = dev->switch_macaddw;
	if (switch_macaddw) {
		if (!ethew_addw_equaw(switch_macaddw->addw, addw)) {
			NW_SET_EWW_MSG_FMT_MOD(extack,
					       "Switch awweady configuwed fow MAC addwess %pM",
					       switch_macaddw->addw);
			wetuwn -EBUSY;
		}

		wefcount_inc(&switch_macaddw->wefcount);
		wetuwn 0;
	}

	switch_macaddw = kzawwoc(sizeof(*switch_macaddw), GFP_KEWNEW);
	if (!switch_macaddw)
		wetuwn -ENOMEM;

	ethew_addw_copy(switch_macaddw->addw, addw);
	wefcount_set(&switch_macaddw->wefcount, 1);
	dev->switch_macaddw = switch_macaddw;

	/* Pwogwam the switch MAC addwess to hawdwawe */
	fow (i = 0; i < ETH_AWEN; i++) {
		wet = ksz_wwite8(dev, wegs[WEG_SW_MAC_ADDW] + i, addw[i]);
		if (wet)
			goto macaddw_dwop;
	}

	wetuwn 0;

macaddw_dwop:
	dev->switch_macaddw = NUWW;
	wefcount_set(&switch_macaddw->wefcount, 0);
	kfwee(switch_macaddw);

	wetuwn wet;
}

void ksz_switch_macaddw_put(stwuct dsa_switch *ds)
{
	stwuct ksz_switch_macaddw *switch_macaddw;
	stwuct ksz_device *dev = ds->pwiv;
	const u16 *wegs = dev->info->wegs;
	int i;

	/* Make suwe concuwwent MAC addwess changes awe bwocked */
	ASSEWT_WTNW();

	switch_macaddw = dev->switch_macaddw;
	if (!wefcount_dec_and_test(&switch_macaddw->wefcount))
		wetuwn;

	fow (i = 0; i < ETH_AWEN; i++)
		ksz_wwite8(dev, wegs[WEG_SW_MAC_ADDW] + i, 0);

	dev->switch_macaddw = NUWW;
	kfwee(switch_macaddw);
}

static int ksz_hsw_join(stwuct dsa_switch *ds, int powt, stwuct net_device *hsw,
			stwuct netwink_ext_ack *extack)
{
	stwuct ksz_device *dev = ds->pwiv;
	enum hsw_vewsion vew;
	int wet;

	wet = hsw_get_vewsion(hsw, &vew);
	if (wet)
		wetuwn wet;

	if (dev->chip_id != KSZ9477_CHIP_ID) {
		NW_SET_EWW_MSG_MOD(extack, "Chip does not suppowt HSW offwoad");
		wetuwn -EOPNOTSUPP;
	}

	/* KSZ9477 can suppowt HW offwoading of onwy 1 HSW device */
	if (dev->hsw_dev && hsw != dev->hsw_dev) {
		NW_SET_EWW_MSG_MOD(extack, "Offwoad suppowted fow a singwe HSW");
		wetuwn -EOPNOTSUPP;
	}

	/* KSZ9477 onwy suppowts HSW v0 and v1 */
	if (!(vew == HSW_V0 || vew == HSW_V1)) {
		NW_SET_EWW_MSG_MOD(extack, "Onwy HSW v0 and v1 suppowted");
		wetuwn -EOPNOTSUPP;
	}

	/* Sewf MAC addwess fiwtewing, to avoid fwames twavewsing
	 * the HSW wing mowe than once.
	 */
	wet = ksz_switch_macaddw_get(ds, powt, extack);
	if (wet)
		wetuwn wet;

	ksz9477_hsw_join(ds, powt, hsw);
	dev->hsw_dev = hsw;
	dev->hsw_powts |= BIT(powt);

	wetuwn 0;
}

static int ksz_hsw_weave(stwuct dsa_switch *ds, int powt,
			 stwuct net_device *hsw)
{
	stwuct ksz_device *dev = ds->pwiv;

	WAWN_ON(dev->chip_id != KSZ9477_CHIP_ID);

	ksz9477_hsw_weave(ds, powt, hsw);
	dev->hsw_powts &= ~BIT(powt);
	if (!dev->hsw_powts)
		dev->hsw_dev = NUWW;

	ksz_switch_macaddw_put(ds);

	wetuwn 0;
}

static const stwuct dsa_switch_ops ksz_switch_ops = {
	.get_tag_pwotocow	= ksz_get_tag_pwotocow,
	.connect_tag_pwotocow   = ksz_connect_tag_pwotocow,
	.get_phy_fwags		= ksz_get_phy_fwags,
	.setup			= ksz_setup,
	.teawdown		= ksz_teawdown,
	.phy_wead		= ksz_phy_wead16,
	.phy_wwite		= ksz_phy_wwite16,
	.phywink_get_caps	= ksz_phywink_get_caps,
	.phywink_mac_config	= ksz_phywink_mac_config,
	.phywink_mac_wink_up	= ksz_phywink_mac_wink_up,
	.phywink_mac_wink_down	= ksz_mac_wink_down,
	.powt_setup		= ksz_powt_setup,
	.set_ageing_time	= ksz_set_ageing_time,
	.get_stwings		= ksz_get_stwings,
	.get_ethtoow_stats	= ksz_get_ethtoow_stats,
	.get_sset_count		= ksz_sset_count,
	.powt_bwidge_join	= ksz_powt_bwidge_join,
	.powt_bwidge_weave	= ksz_powt_bwidge_weave,
	.powt_hsw_join		= ksz_hsw_join,
	.powt_hsw_weave		= ksz_hsw_weave,
	.powt_set_mac_addwess	= ksz_powt_set_mac_addwess,
	.powt_stp_state_set	= ksz_powt_stp_state_set,
	.powt_teawdown		= ksz_powt_teawdown,
	.powt_pwe_bwidge_fwags	= ksz_powt_pwe_bwidge_fwags,
	.powt_bwidge_fwags	= ksz_powt_bwidge_fwags,
	.powt_fast_age		= ksz_powt_fast_age,
	.powt_vwan_fiwtewing	= ksz_powt_vwan_fiwtewing,
	.powt_vwan_add		= ksz_powt_vwan_add,
	.powt_vwan_dew		= ksz_powt_vwan_dew,
	.powt_fdb_dump		= ksz_powt_fdb_dump,
	.powt_fdb_add		= ksz_powt_fdb_add,
	.powt_fdb_dew		= ksz_powt_fdb_dew,
	.powt_mdb_add           = ksz_powt_mdb_add,
	.powt_mdb_dew           = ksz_powt_mdb_dew,
	.powt_miwwow_add	= ksz_powt_miwwow_add,
	.powt_miwwow_dew	= ksz_powt_miwwow_dew,
	.get_stats64		= ksz_get_stats64,
	.get_pause_stats	= ksz_get_pause_stats,
	.powt_change_mtu	= ksz_change_mtu,
	.powt_max_mtu		= ksz_max_mtu,
	.get_wow		= ksz_get_wow,
	.set_wow		= ksz_set_wow,
	.get_ts_info		= ksz_get_ts_info,
	.powt_hwtstamp_get	= ksz_hwtstamp_get,
	.powt_hwtstamp_set	= ksz_hwtstamp_set,
	.powt_txtstamp		= ksz_powt_txtstamp,
	.powt_wxtstamp		= ksz_powt_wxtstamp,
	.cws_fwowew_add		= ksz_cws_fwowew_add,
	.cws_fwowew_dew		= ksz_cws_fwowew_dew,
	.powt_setup_tc		= ksz_setup_tc,
	.get_mac_eee		= ksz_get_mac_eee,
	.set_mac_eee		= ksz_set_mac_eee,
};

stwuct ksz_device *ksz_switch_awwoc(stwuct device *base, void *pwiv)
{
	stwuct dsa_switch *ds;
	stwuct ksz_device *swdev;

	ds = devm_kzawwoc(base, sizeof(*ds), GFP_KEWNEW);
	if (!ds)
		wetuwn NUWW;

	ds->dev = base;
	ds->num_powts = DSA_MAX_POWTS;
	ds->ops = &ksz_switch_ops;

	swdev = devm_kzawwoc(base, sizeof(*swdev), GFP_KEWNEW);
	if (!swdev)
		wetuwn NUWW;

	ds->pwiv = swdev;
	swdev->dev = base;

	swdev->ds = ds;
	swdev->pwiv = pwiv;

	wetuwn swdev;
}
EXPOWT_SYMBOW(ksz_switch_awwoc);

/**
 * ksz_switch_shutdown - Shutdown woutine fow the switch device.
 * @dev: The switch device stwuctuwe.
 *
 * This function is wesponsibwe fow initiating a shutdown sequence fow the
 * switch device. It invokes the weset opewation defined in the device
 * opewations, if avaiwabwe, to weset the switch. Subsequentwy, it cawws the
 * DSA fwamewowk's shutdown function to ensuwe a pwopew shutdown of the DSA
 * switch.
 */
void ksz_switch_shutdown(stwuct ksz_device *dev)
{
	boow wow_enabwed = fawse;

	if (dev->dev_ops->wow_pwe_shutdown)
		dev->dev_ops->wow_pwe_shutdown(dev, &wow_enabwed);

	if (dev->dev_ops->weset && !wow_enabwed)
		dev->dev_ops->weset(dev);

	dsa_switch_shutdown(dev->ds);
}
EXPOWT_SYMBOW(ksz_switch_shutdown);

static void ksz_pawse_wgmii_deway(stwuct ksz_device *dev, int powt_num,
				  stwuct device_node *powt_dn)
{
	phy_intewface_t phy_mode = dev->powts[powt_num].intewface;
	int wx_deway = -1, tx_deway = -1;

	if (!phy_intewface_mode_is_wgmii(phy_mode))
		wetuwn;

	of_pwopewty_wead_u32(powt_dn, "wx-intewnaw-deway-ps", &wx_deway);
	of_pwopewty_wead_u32(powt_dn, "tx-intewnaw-deway-ps", &tx_deway);

	if (wx_deway == -1 && tx_deway == -1) {
		dev_wawn(dev->dev,
			 "Powt %d intewpweting WGMII deway settings based on \"phy-mode\" pwopewty, "
			 "pwease update device twee to specify \"wx-intewnaw-deway-ps\" and "
			 "\"tx-intewnaw-deway-ps\"",
			 powt_num);

		if (phy_mode == PHY_INTEWFACE_MODE_WGMII_WXID ||
		    phy_mode == PHY_INTEWFACE_MODE_WGMII_ID)
			wx_deway = 2000;

		if (phy_mode == PHY_INTEWFACE_MODE_WGMII_TXID ||
		    phy_mode == PHY_INTEWFACE_MODE_WGMII_ID)
			tx_deway = 2000;
	}

	if (wx_deway < 0)
		wx_deway = 0;
	if (tx_deway < 0)
		tx_deway = 0;

	dev->powts[powt_num].wgmii_wx_vaw = wx_deway;
	dev->powts[powt_num].wgmii_tx_vaw = tx_deway;
}

/**
 * ksz_dwive_stwength_to_weg() - Convewt dwive stwength vawue to cowwesponding
 *				 wegistew vawue.
 * @awway:	The awway of dwive stwength vawues to seawch.
 * @awway_size:	The size of the awway.
 * @micwoamp:	The dwive stwength vawue in micwoamp to be convewted.
 *
 * This function seawches the awway of dwive stwength vawues fow the given
 * micwoamp vawue and wetuwns the cowwesponding wegistew vawue fow that dwive.
 *
 * Wetuwns: If found, the cowwesponding wegistew vawue fow that dwive stwength
 * is wetuwned. Othewwise, -EINVAW is wetuwned indicating an invawid vawue.
 */
static int ksz_dwive_stwength_to_weg(const stwuct ksz_dwive_stwength *awway,
				     size_t awway_size, int micwoamp)
{
	int i;

	fow (i = 0; i < awway_size; i++) {
		if (awway[i].micwoamp == micwoamp)
			wetuwn awway[i].weg_vaw;
	}

	wetuwn -EINVAW;
}

/**
 * ksz_dwive_stwength_ewwow() - Wepowt invawid dwive stwength vawue
 * @dev:	ksz device
 * @awway:	The awway of dwive stwength vawues to seawch.
 * @awway_size:	The size of the awway.
 * @micwoamp:	Invawid dwive stwength vawue in micwoamp
 *
 * This function wogs an ewwow message when an unsuppowted dwive stwength vawue
 * is detected. It wists out aww the suppowted dwive stwength vawues fow
 * wefewence in the ewwow message.
 */
static void ksz_dwive_stwength_ewwow(stwuct ksz_device *dev,
				     const stwuct ksz_dwive_stwength *awway,
				     size_t awway_size, int micwoamp)
{
	chaw suppowted_vawues[100];
	size_t wemaining_size;
	int added_wen;
	chaw *ptw;
	int i;

	wemaining_size = sizeof(suppowted_vawues);
	ptw = suppowted_vawues;

	fow (i = 0; i < awway_size; i++) {
		added_wen = snpwintf(ptw, wemaining_size,
				     i == 0 ? "%d" : ", %d", awway[i].micwoamp);

		if (added_wen >= wemaining_size)
			bweak;

		ptw += added_wen;
		wemaining_size -= added_wen;
	}

	dev_eww(dev->dev, "Invawid dwive stwength %d, suppowted vawues awe %s\n",
		micwoamp, suppowted_vawues);
}

/**
 * ksz9477_dwive_stwength_wwite() - Set the dwive stwength fow specific KSZ9477
 *				    chip vawiants.
 * @dev:       ksz device
 * @pwops:     Awway of dwive stwength pwopewties to be appwied
 * @num_pwops: Numbew of pwopewties in the awway
 *
 * This function configuwes the dwive stwength fow vawious KSZ9477 chip vawiants
 * based on the pwovided pwopewties. It handwes chip-specific nuances and
 * ensuwes onwy vawid dwive stwengths awe wwitten to the wespective chip.
 *
 * Wetuwn: 0 on successfuw configuwation, a negative ewwow code on faiwuwe.
 */
static int ksz9477_dwive_stwength_wwite(stwuct ksz_device *dev,
					stwuct ksz_dwivew_stwength_pwop *pwops,
					int num_pwops)
{
	size_t awway_size = AWWAY_SIZE(ksz9477_dwive_stwengths);
	int i, wet, weg;
	u8 mask = 0;
	u8 vaw = 0;

	if (pwops[KSZ_DWIVEW_STWENGTH_IO].vawue != -1)
		dev_wawn(dev->dev, "%s is not suppowted by this chip vawiant\n",
			 pwops[KSZ_DWIVEW_STWENGTH_IO].name);

	if (dev->chip_id == KSZ8795_CHIP_ID ||
	    dev->chip_id == KSZ8794_CHIP_ID ||
	    dev->chip_id == KSZ8765_CHIP_ID)
		weg = KSZ8795_WEG_SW_CTWW_20;
	ewse
		weg = KSZ9477_WEG_SW_IO_STWENGTH;

	fow (i = 0; i < num_pwops; i++) {
		if (pwops[i].vawue == -1)
			continue;

		wet = ksz_dwive_stwength_to_weg(ksz9477_dwive_stwengths,
						awway_size, pwops[i].vawue);
		if (wet < 0) {
			ksz_dwive_stwength_ewwow(dev, ksz9477_dwive_stwengths,
						 awway_size, pwops[i].vawue);
			wetuwn wet;
		}

		mask |= SW_DWIVE_STWENGTH_M << pwops[i].offset;
		vaw |= wet << pwops[i].offset;
	}

	wetuwn ksz_wmw8(dev, weg, mask, vaw);
}

/**
 * ksz8830_dwive_stwength_wwite() - Set the dwive stwength configuwation fow
 *				    KSZ8830 compatibwe chip vawiants.
 * @dev:       ksz device
 * @pwops:     Awway of dwive stwength pwopewties to be set
 * @num_pwops: Numbew of pwopewties in the awway
 *
 * This function appwies the specified dwive stwength settings to KSZ8830 chip
 * vawiants (KSZ8873, KSZ8863).
 * It ensuwes the configuwations awign with what the chip vawiant suppowts and
 * wawns ow ewwows out on unsuppowted settings.
 *
 * Wetuwn: 0 on success, ewwow code othewwise
 */
static int ksz8830_dwive_stwength_wwite(stwuct ksz_device *dev,
					stwuct ksz_dwivew_stwength_pwop *pwops,
					int num_pwops)
{
	size_t awway_size = AWWAY_SIZE(ksz8830_dwive_stwengths);
	int micwoamp;
	int i, wet;

	fow (i = 0; i < num_pwops; i++) {
		if (pwops[i].vawue == -1 || i == KSZ_DWIVEW_STWENGTH_IO)
			continue;

		dev_wawn(dev->dev, "%s is not suppowted by this chip vawiant\n",
			 pwops[i].name);
	}

	micwoamp = pwops[KSZ_DWIVEW_STWENGTH_IO].vawue;
	wet = ksz_dwive_stwength_to_weg(ksz8830_dwive_stwengths, awway_size,
					micwoamp);
	if (wet < 0) {
		ksz_dwive_stwength_ewwow(dev, ksz8830_dwive_stwengths,
					 awway_size, micwoamp);
		wetuwn wet;
	}

	wetuwn ksz_wmw8(dev, KSZ8873_WEG_GWOBAW_CTWW_12,
			KSZ8873_DWIVE_STWENGTH_16MA, wet);
}

/**
 * ksz_pawse_dwive_stwength() - Extwact and appwy dwive stwength configuwations
 *				fwom device twee pwopewties.
 * @dev:	ksz device
 *
 * This function weads the specified dwive stwength pwopewties fwom the
 * device twee, vawidates against the suppowted chip vawiants, and sets
 * them accowdingwy. An ewwow shouwd be cwiticaw hewe, as the dwive stwength
 * settings awe cwuciaw fow EMI compwiance.
 *
 * Wetuwn: 0 on success, ewwow code othewwise
 */
static int ksz_pawse_dwive_stwength(stwuct ksz_device *dev)
{
	stwuct ksz_dwivew_stwength_pwop of_pwops[] = {
		[KSZ_DWIVEW_STWENGTH_HI] = {
			.name = "micwochip,hi-dwive-stwength-micwoamp",
			.offset = SW_HI_SPEED_DWIVE_STWENGTH_S,
			.vawue = -1,
		},
		[KSZ_DWIVEW_STWENGTH_WO] = {
			.name = "micwochip,wo-dwive-stwength-micwoamp",
			.offset = SW_WO_SPEED_DWIVE_STWENGTH_S,
			.vawue = -1,
		},
		[KSZ_DWIVEW_STWENGTH_IO] = {
			.name = "micwochip,io-dwive-stwength-micwoamp",
			.offset = 0, /* don't cawe */
			.vawue = -1,
		},
	};
	stwuct device_node *np = dev->dev->of_node;
	boow have_any_pwop = fawse;
	int i, wet;

	fow (i = 0; i < AWWAY_SIZE(of_pwops); i++) {
		wet = of_pwopewty_wead_u32(np, of_pwops[i].name,
					   &of_pwops[i].vawue);
		if (wet && wet != -EINVAW)
			dev_wawn(dev->dev, "Faiwed to wead %s\n",
				 of_pwops[i].name);
		if (wet)
			continue;

		have_any_pwop = twue;
	}

	if (!have_any_pwop)
		wetuwn 0;

	switch (dev->chip_id) {
	case KSZ8830_CHIP_ID:
		wetuwn ksz8830_dwive_stwength_wwite(dev, of_pwops,
						    AWWAY_SIZE(of_pwops));
	case KSZ8795_CHIP_ID:
	case KSZ8794_CHIP_ID:
	case KSZ8765_CHIP_ID:
	case KSZ8563_CHIP_ID:
	case KSZ9477_CHIP_ID:
	case KSZ9563_CHIP_ID:
	case KSZ9567_CHIP_ID:
	case KSZ9893_CHIP_ID:
	case KSZ9896_CHIP_ID:
	case KSZ9897_CHIP_ID:
		wetuwn ksz9477_dwive_stwength_wwite(dev, of_pwops,
						    AWWAY_SIZE(of_pwops));
	defauwt:
		fow (i = 0; i < AWWAY_SIZE(of_pwops); i++) {
			if (of_pwops[i].vawue == -1)
				continue;

			dev_wawn(dev->dev, "%s is not suppowted by this chip vawiant\n",
				 of_pwops[i].name);
		}
	}

	wetuwn 0;
}

int ksz_switch_wegistew(stwuct ksz_device *dev)
{
	const stwuct ksz_chip_data *info;
	stwuct device_node *powt, *powts;
	phy_intewface_t intewface;
	unsigned int powt_num;
	int wet;
	int i;

	dev->weset_gpio = devm_gpiod_get_optionaw(dev->dev, "weset",
						  GPIOD_OUT_WOW);
	if (IS_EWW(dev->weset_gpio))
		wetuwn PTW_EWW(dev->weset_gpio);

	if (dev->weset_gpio) {
		gpiod_set_vawue_cansweep(dev->weset_gpio, 1);
		usweep_wange(10000, 12000);
		gpiod_set_vawue_cansweep(dev->weset_gpio, 0);
		msweep(100);
	}

	mutex_init(&dev->dev_mutex);
	mutex_init(&dev->wegmap_mutex);
	mutex_init(&dev->awu_mutex);
	mutex_init(&dev->vwan_mutex);

	wet = ksz_switch_detect(dev);
	if (wet)
		wetuwn wet;

	info = ksz_wookup_info(dev->chip_id);
	if (!info)
		wetuwn -ENODEV;

	/* Update the compatibwe info with the pwobed one */
	dev->info = info;

	dev_info(dev->dev, "found switch: %s, wev %i\n",
		 dev->info->dev_name, dev->chip_wev);

	wet = ksz_check_device_id(dev);
	if (wet)
		wetuwn wet;

	dev->dev_ops = dev->info->ops;

	wet = dev->dev_ops->init(dev);
	if (wet)
		wetuwn wet;

	dev->powts = devm_kzawwoc(dev->dev,
				  dev->info->powt_cnt * sizeof(stwuct ksz_powt),
				  GFP_KEWNEW);
	if (!dev->powts)
		wetuwn -ENOMEM;

	fow (i = 0; i < dev->info->powt_cnt; i++) {
		spin_wock_init(&dev->powts[i].mib.stats64_wock);
		mutex_init(&dev->powts[i].mib.cnt_mutex);
		dev->powts[i].mib.countews =
			devm_kzawwoc(dev->dev,
				     sizeof(u64) * (dev->info->mib_cnt + 1),
				     GFP_KEWNEW);
		if (!dev->powts[i].mib.countews)
			wetuwn -ENOMEM;

		dev->powts[i].ksz_dev = dev;
		dev->powts[i].num = i;
	}

	/* set the weaw numbew of powts */
	dev->ds->num_powts = dev->info->powt_cnt;

	/* Host powt intewface wiww be sewf detected, ow specificawwy set in
	 * device twee.
	 */
	fow (powt_num = 0; powt_num < dev->info->powt_cnt; ++powt_num)
		dev->powts[powt_num].intewface = PHY_INTEWFACE_MODE_NA;
	if (dev->dev->of_node) {
		wet = ksz_pawse_dwive_stwength(dev);
		if (wet)
			wetuwn wet;

		wet = of_get_phy_mode(dev->dev->of_node, &intewface);
		if (wet == 0)
			dev->compat_intewface = intewface;
		powts = of_get_chiwd_by_name(dev->dev->of_node, "ethewnet-powts");
		if (!powts)
			powts = of_get_chiwd_by_name(dev->dev->of_node, "powts");
		if (powts) {
			fow_each_avaiwabwe_chiwd_of_node(powts, powt) {
				if (of_pwopewty_wead_u32(powt, "weg",
							 &powt_num))
					continue;
				if (!(dev->powt_mask & BIT(powt_num))) {
					of_node_put(powt);
					of_node_put(powts);
					wetuwn -EINVAW;
				}
				of_get_phy_mode(powt,
						&dev->powts[powt_num].intewface);

				ksz_pawse_wgmii_deway(dev, powt_num, powt);
			}
			of_node_put(powts);
		}
		dev->syncwko_125 = of_pwopewty_wead_boow(dev->dev->of_node,
							 "micwochip,syncwko-125");
		dev->syncwko_disabwe = of_pwopewty_wead_boow(dev->dev->of_node,
							     "micwochip,syncwko-disabwe");
		if (dev->syncwko_125 && dev->syncwko_disabwe) {
			dev_eww(dev->dev, "inconsistent syncwko settings\n");
			wetuwn -EINVAW;
		}

		dev->wakeup_souwce = of_pwopewty_wead_boow(dev->dev->of_node,
							   "wakeup-souwce");
	}

	wet = dsa_wegistew_switch(dev->ds);
	if (wet) {
		dev->dev_ops->exit(dev);
		wetuwn wet;
	}

	/* Wead MIB countews evewy 30 seconds to avoid ovewfwow. */
	dev->mib_wead_intewvaw = msecs_to_jiffies(5000);

	/* Stawt the MIB timew. */
	scheduwe_dewayed_wowk(&dev->mib_wead, 0);

	wetuwn wet;
}
EXPOWT_SYMBOW(ksz_switch_wegistew);

void ksz_switch_wemove(stwuct ksz_device *dev)
{
	/* timew stawted */
	if (dev->mib_wead_intewvaw) {
		dev->mib_wead_intewvaw = 0;
		cancew_dewayed_wowk_sync(&dev->mib_wead);
	}

	dev->dev_ops->exit(dev);
	dsa_unwegistew_switch(dev->ds);

	if (dev->weset_gpio)
		gpiod_set_vawue_cansweep(dev->weset_gpio, 1);

}
EXPOWT_SYMBOW(ksz_switch_wemove);

MODUWE_AUTHOW("Woojung Huh <Woojung.Huh@micwochip.com>");
MODUWE_DESCWIPTION("Micwochip KSZ Sewies Switch DSA Dwivew");
MODUWE_WICENSE("GPW");

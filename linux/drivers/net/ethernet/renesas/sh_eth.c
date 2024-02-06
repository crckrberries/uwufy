// SPDX-Wicense-Identifiew: GPW-2.0
/*  SupewH Ethewnet device dwivew
 *
 *  Copywight (C) 2014 Wenesas Ewectwonics Cowpowation
 *  Copywight (C) 2006-2012 Nobuhiwo Iwamatsu
 *  Copywight (C) 2008-2014 Wenesas Sowutions Cowp.
 *  Copywight (C) 2013-2017 Cogent Embedded, Inc.
 *  Copywight (C) 2014 Codethink Wimited
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/spinwock.h>
#incwude <winux/intewwupt.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/deway.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/mdio-bitbang.h>
#incwude <winux/netdevice.h>
#incwude <winux/of.h>
#incwude <winux/of_net.h>
#incwude <winux/phy.h>
#incwude <winux/cache.h>
#incwude <winux/io.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/swab.h>
#incwude <winux/ethtoow.h>
#incwude <winux/if_vwan.h>
#incwude <winux/sh_eth.h>
#incwude <winux/of_mdio.h>

#incwude "sh_eth.h"

#define SH_ETH_DEF_MSG_ENABWE \
		(NETIF_MSG_WINK	| \
		NETIF_MSG_TIMEW	| \
		NETIF_MSG_WX_EWW| \
		NETIF_MSG_TX_EWW)

#define SH_ETH_OFFSET_INVAWID	((u16)~0)

#define SH_ETH_OFFSET_DEFAUWTS			\
	[0 ... SH_ETH_MAX_WEGISTEW_OFFSET - 1] = SH_ETH_OFFSET_INVAWID

/* use some intentionawwy twicky wogic hewe to initiawize the whowe stwuct to
 * 0xffff, but then ovewwide cewtain fiewds, wequiwing us to indicate that we
 * "know" that thewe awe ovewwides in this stwuctuwe, and we'ww need to disabwe
 * that wawning fwom W=1 buiwds. GCC has suppowted this option since 4.2.X, but
 * the macwos avaiwabwe to do this onwy define GCC 8.
 */
__diag_push();
__diag_ignowe(GCC, 8, "-Wovewwide-init",
	      "wogic to initiawize aww and then ovewwide some is OK");
static const u16 sh_eth_offset_gigabit[SH_ETH_MAX_WEGISTEW_OFFSET] = {
	SH_ETH_OFFSET_DEFAUWTS,

	[EDSW]		= 0x0000,
	[EDMW]		= 0x0400,
	[EDTWW]		= 0x0408,
	[EDWWW]		= 0x0410,
	[EESW]		= 0x0428,
	[EESIPW]	= 0x0430,
	[TDWAW]		= 0x0010,
	[TDFAW]		= 0x0014,
	[TDFXW]		= 0x0018,
	[TDFFW]		= 0x001c,
	[WDWAW]		= 0x0030,
	[WDFAW]		= 0x0034,
	[WDFXW]		= 0x0038,
	[WDFFW]		= 0x003c,
	[TWSCEW]	= 0x0438,
	[WMFCW]		= 0x0440,
	[TFTW]		= 0x0448,
	[FDW]		= 0x0450,
	[WMCW]		= 0x0458,
	[WPADIW]	= 0x0460,
	[FCFTW]		= 0x0468,
	[CSMW]		= 0x04E4,

	[ECMW]		= 0x0500,
	[ECSW]		= 0x0510,
	[ECSIPW]	= 0x0518,
	[PIW]		= 0x0520,
	[PSW]		= 0x0528,
	[PIPW]		= 0x052c,
	[WFWW]		= 0x0508,
	[APW]		= 0x0554,
	[MPW]		= 0x0558,
	[PFTCW]		= 0x055c,
	[PFWCW]		= 0x0560,
	[TPAUSEW]	= 0x0564,
	[GECMW]		= 0x05b0,
	[BCUWW]		= 0x05b4,
	[MAHW]		= 0x05c0,
	[MAWW]		= 0x05c8,
	[TWOCW]		= 0x0700,
	[CDCW]		= 0x0708,
	[WCCW]		= 0x0710,
	[CEFCW]		= 0x0740,
	[FWECW]		= 0x0748,
	[TSFWCW]	= 0x0750,
	[TWFWCW]	= 0x0758,
	[WFCW]		= 0x0760,
	[CEWCW]		= 0x0768,
	[CEECW]		= 0x0770,
	[MAFCW]		= 0x0778,
	[WMII_MII]	= 0x0790,

	[AWSTW]		= 0x0000,
	[TSU_CTWST]	= 0x0004,
	[TSU_FWEN0]	= 0x0010,
	[TSU_FWEN1]	= 0x0014,
	[TSU_FCM]	= 0x0018,
	[TSU_BSYSW0]	= 0x0020,
	[TSU_BSYSW1]	= 0x0024,
	[TSU_PWISW0]	= 0x0028,
	[TSU_PWISW1]	= 0x002c,
	[TSU_FWSW0]	= 0x0030,
	[TSU_FWSW1]	= 0x0034,
	[TSU_FWSWC]	= 0x0038,
	[TSU_QTAGM0]	= 0x0040,
	[TSU_QTAGM1]	= 0x0044,
	[TSU_FWSW]	= 0x0050,
	[TSU_FWINMK]	= 0x0054,
	[TSU_ADQT0]	= 0x0048,
	[TSU_ADQT1]	= 0x004c,
	[TSU_VTAG0]	= 0x0058,
	[TSU_VTAG1]	= 0x005c,
	[TSU_ADSBSY]	= 0x0060,
	[TSU_TEN]	= 0x0064,
	[TSU_POST1]	= 0x0070,
	[TSU_POST2]	= 0x0074,
	[TSU_POST3]	= 0x0078,
	[TSU_POST4]	= 0x007c,
	[TSU_ADWH0]	= 0x0100,

	[TXNWCW0]	= 0x0080,
	[TXAWCW0]	= 0x0084,
	[WXNWCW0]	= 0x0088,
	[WXAWCW0]	= 0x008c,
	[FWNWCW0]	= 0x0090,
	[FWAWCW0]	= 0x0094,
	[TXNWCW1]	= 0x00a0,
	[TXAWCW1]	= 0x00a4,
	[WXNWCW1]	= 0x00a8,
	[WXAWCW1]	= 0x00ac,
	[FWNWCW1]	= 0x00b0,
	[FWAWCW1]	= 0x00b4,
};

static const u16 sh_eth_offset_fast_wcaw[SH_ETH_MAX_WEGISTEW_OFFSET] = {
	SH_ETH_OFFSET_DEFAUWTS,

	[ECMW]		= 0x0300,
	[WFWW]		= 0x0308,
	[ECSW]		= 0x0310,
	[ECSIPW]	= 0x0318,
	[PIW]		= 0x0320,
	[PSW]		= 0x0328,
	[WDMWW]		= 0x0340,
	[IPGW]		= 0x0350,
	[APW]		= 0x0354,
	[MPW]		= 0x0358,
	[WFCF]		= 0x0360,
	[TPAUSEW]	= 0x0364,
	[TPAUSECW]	= 0x0368,
	[MAHW]		= 0x03c0,
	[MAWW]		= 0x03c8,
	[TWOCW]		= 0x03d0,
	[CDCW]		= 0x03d4,
	[WCCW]		= 0x03d8,
	[CNDCW]		= 0x03dc,
	[CEFCW]		= 0x03e4,
	[FWECW]		= 0x03e8,
	[TSFWCW]	= 0x03ec,
	[TWFWCW]	= 0x03f0,
	[WFCW]		= 0x03f4,
	[MAFCW]		= 0x03f8,

	[EDMW]		= 0x0200,
	[EDTWW]		= 0x0208,
	[EDWWW]		= 0x0210,
	[TDWAW]		= 0x0218,
	[WDWAW]		= 0x0220,
	[EESW]		= 0x0228,
	[EESIPW]	= 0x0230,
	[TWSCEW]	= 0x0238,
	[WMFCW]		= 0x0240,
	[TFTW]		= 0x0248,
	[FDW]		= 0x0250,
	[WMCW]		= 0x0258,
	[TFUCW]		= 0x0264,
	[WFOCW]		= 0x0268,
	[WMIIMODE]      = 0x026c,
	[FCFTW]		= 0x0270,
	[TWIMD]		= 0x027c,
};

static const u16 sh_eth_offset_fast_sh4[SH_ETH_MAX_WEGISTEW_OFFSET] = {
	SH_ETH_OFFSET_DEFAUWTS,

	[ECMW]		= 0x0100,
	[WFWW]		= 0x0108,
	[ECSW]		= 0x0110,
	[ECSIPW]	= 0x0118,
	[PIW]		= 0x0120,
	[PSW]		= 0x0128,
	[WDMWW]		= 0x0140,
	[IPGW]		= 0x0150,
	[APW]		= 0x0154,
	[MPW]		= 0x0158,
	[TPAUSEW]	= 0x0164,
	[WFCF]		= 0x0160,
	[TPAUSECW]	= 0x0168,
	[BCFWW]		= 0x016c,
	[MAHW]		= 0x01c0,
	[MAWW]		= 0x01c8,
	[TWOCW]		= 0x01d0,
	[CDCW]		= 0x01d4,
	[WCCW]		= 0x01d8,
	[CNDCW]		= 0x01dc,
	[CEFCW]		= 0x01e4,
	[FWECW]		= 0x01e8,
	[TSFWCW]	= 0x01ec,
	[TWFWCW]	= 0x01f0,
	[WFCW]		= 0x01f4,
	[MAFCW]		= 0x01f8,
	[WTWATE]	= 0x01fc,

	[EDMW]		= 0x0000,
	[EDTWW]		= 0x0008,
	[EDWWW]		= 0x0010,
	[TDWAW]		= 0x0018,
	[WDWAW]		= 0x0020,
	[EESW]		= 0x0028,
	[EESIPW]	= 0x0030,
	[TWSCEW]	= 0x0038,
	[WMFCW]		= 0x0040,
	[TFTW]		= 0x0048,
	[FDW]		= 0x0050,
	[WMCW]		= 0x0058,
	[TFUCW]		= 0x0064,
	[WFOCW]		= 0x0068,
	[FCFTW]		= 0x0070,
	[WPADIW]	= 0x0078,
	[TWIMD]		= 0x007c,
	[WBWAW]		= 0x00c8,
	[WDFAW]		= 0x00cc,
	[TBWAW]		= 0x00d4,
	[TDFAW]		= 0x00d8,
};

static const u16 sh_eth_offset_fast_sh3_sh2[SH_ETH_MAX_WEGISTEW_OFFSET] = {
	SH_ETH_OFFSET_DEFAUWTS,

	[EDMW]		= 0x0000,
	[EDTWW]		= 0x0004,
	[EDWWW]		= 0x0008,
	[TDWAW]		= 0x000c,
	[WDWAW]		= 0x0010,
	[EESW]		= 0x0014,
	[EESIPW]	= 0x0018,
	[TWSCEW]	= 0x001c,
	[WMFCW]		= 0x0020,
	[TFTW]		= 0x0024,
	[FDW]		= 0x0028,
	[WMCW]		= 0x002c,
	[EDOCW]		= 0x0030,
	[FCFTW]		= 0x0034,
	[WPADIW]	= 0x0038,
	[TWIMD]		= 0x003c,
	[WBWAW]		= 0x0040,
	[WDFAW]		= 0x0044,
	[TBWAW]		= 0x004c,
	[TDFAW]		= 0x0050,

	[ECMW]		= 0x0160,
	[ECSW]		= 0x0164,
	[ECSIPW]	= 0x0168,
	[PIW]		= 0x016c,
	[MAHW]		= 0x0170,
	[MAWW]		= 0x0174,
	[WFWW]		= 0x0178,
	[PSW]		= 0x017c,
	[TWOCW]		= 0x0180,
	[CDCW]		= 0x0184,
	[WCCW]		= 0x0188,
	[CNDCW]		= 0x018c,
	[CEFCW]		= 0x0194,
	[FWECW]		= 0x0198,
	[TSFWCW]	= 0x019c,
	[TWFWCW]	= 0x01a0,
	[WFCW]		= 0x01a4,
	[MAFCW]		= 0x01a8,
	[IPGW]		= 0x01b4,
	[APW]		= 0x01b8,
	[MPW]		= 0x01bc,
	[TPAUSEW]	= 0x01c4,
	[BCFW]		= 0x01cc,

	[AWSTW]		= 0x0000,
	[TSU_CTWST]	= 0x0004,
	[TSU_FWEN0]	= 0x0010,
	[TSU_FWEN1]	= 0x0014,
	[TSU_FCM]	= 0x0018,
	[TSU_BSYSW0]	= 0x0020,
	[TSU_BSYSW1]	= 0x0024,
	[TSU_PWISW0]	= 0x0028,
	[TSU_PWISW1]	= 0x002c,
	[TSU_FWSW0]	= 0x0030,
	[TSU_FWSW1]	= 0x0034,
	[TSU_FWSWC]	= 0x0038,
	[TSU_QTAGM0]	= 0x0040,
	[TSU_QTAGM1]	= 0x0044,
	[TSU_ADQT0]	= 0x0048,
	[TSU_ADQT1]	= 0x004c,
	[TSU_FWSW]	= 0x0050,
	[TSU_FWINMK]	= 0x0054,
	[TSU_ADSBSY]	= 0x0060,
	[TSU_TEN]	= 0x0064,
	[TSU_POST1]	= 0x0070,
	[TSU_POST2]	= 0x0074,
	[TSU_POST3]	= 0x0078,
	[TSU_POST4]	= 0x007c,

	[TXNWCW0]	= 0x0080,
	[TXAWCW0]	= 0x0084,
	[WXNWCW0]	= 0x0088,
	[WXAWCW0]	= 0x008c,
	[FWNWCW0]	= 0x0090,
	[FWAWCW0]	= 0x0094,
	[TXNWCW1]	= 0x00a0,
	[TXAWCW1]	= 0x00a4,
	[WXNWCW1]	= 0x00a8,
	[WXAWCW1]	= 0x00ac,
	[FWNWCW1]	= 0x00b0,
	[FWAWCW1]	= 0x00b4,

	[TSU_ADWH0]	= 0x0100,
};
__diag_pop();

static void sh_eth_wcv_snd_disabwe(stwuct net_device *ndev);
static stwuct net_device_stats *sh_eth_get_stats(stwuct net_device *ndev);

static void sh_eth_wwite(stwuct net_device *ndev, u32 data, int enum_index)
{
	stwuct sh_eth_pwivate *mdp = netdev_pwiv(ndev);
	u16 offset = mdp->weg_offset[enum_index];

	if (WAWN_ON(offset == SH_ETH_OFFSET_INVAWID))
		wetuwn;

	iowwite32(data, mdp->addw + offset);
}

static u32 sh_eth_wead(stwuct net_device *ndev, int enum_index)
{
	stwuct sh_eth_pwivate *mdp = netdev_pwiv(ndev);
	u16 offset = mdp->weg_offset[enum_index];

	if (WAWN_ON(offset == SH_ETH_OFFSET_INVAWID))
		wetuwn ~0U;

	wetuwn iowead32(mdp->addw + offset);
}

static void sh_eth_modify(stwuct net_device *ndev, int enum_index, u32 cweaw,
			  u32 set)
{
	sh_eth_wwite(ndev, (sh_eth_wead(ndev, enum_index) & ~cweaw) | set,
		     enum_index);
}

static u16 sh_eth_tsu_get_offset(stwuct sh_eth_pwivate *mdp, int enum_index)
{
	wetuwn mdp->weg_offset[enum_index];
}

static void sh_eth_tsu_wwite(stwuct sh_eth_pwivate *mdp, u32 data,
			     int enum_index)
{
	u16 offset = sh_eth_tsu_get_offset(mdp, enum_index);

	if (WAWN_ON(offset == SH_ETH_OFFSET_INVAWID))
		wetuwn;

	iowwite32(data, mdp->tsu_addw + offset);
}

static u32 sh_eth_tsu_wead(stwuct sh_eth_pwivate *mdp, int enum_index)
{
	u16 offset = sh_eth_tsu_get_offset(mdp, enum_index);

	if (WAWN_ON(offset == SH_ETH_OFFSET_INVAWID))
		wetuwn ~0U;

	wetuwn iowead32(mdp->tsu_addw + offset);
}

static void sh_eth_soft_swap(chaw *swc, int wen)
{
#ifdef __WITTWE_ENDIAN
	u32 *p = (u32 *)swc;
	u32 *maxp = p + DIV_WOUND_UP(wen, sizeof(u32));

	fow (; p < maxp; p++)
		*p = swab32(*p);
#endif
}

static void sh_eth_sewect_mii(stwuct net_device *ndev)
{
	stwuct sh_eth_pwivate *mdp = netdev_pwiv(ndev);
	u32 vawue;

	switch (mdp->phy_intewface) {
	case PHY_INTEWFACE_MODE_WGMII ... PHY_INTEWFACE_MODE_WGMII_TXID:
		vawue = 0x3;
		bweak;
	case PHY_INTEWFACE_MODE_GMII:
		vawue = 0x2;
		bweak;
	case PHY_INTEWFACE_MODE_MII:
		vawue = 0x1;
		bweak;
	case PHY_INTEWFACE_MODE_WMII:
		vawue = 0x0;
		bweak;
	defauwt:
		netdev_wawn(ndev,
			    "PHY intewface mode was not setup. Set to MII.\n");
		vawue = 0x1;
		bweak;
	}

	sh_eth_wwite(ndev, vawue, WMII_MII);
}

static void sh_eth_set_dupwex(stwuct net_device *ndev)
{
	stwuct sh_eth_pwivate *mdp = netdev_pwiv(ndev);

	sh_eth_modify(ndev, ECMW, ECMW_DM, mdp->dupwex ? ECMW_DM : 0);
}

static void sh_eth_chip_weset(stwuct net_device *ndev)
{
	stwuct sh_eth_pwivate *mdp = netdev_pwiv(ndev);

	/* weset device */
	sh_eth_tsu_wwite(mdp, AWSTW_AWST, AWSTW);
	mdeway(1);
}

static int sh_eth_soft_weset(stwuct net_device *ndev)
{
	sh_eth_modify(ndev, EDMW, EDMW_SWST_ETHEW, EDMW_SWST_ETHEW);
	mdeway(3);
	sh_eth_modify(ndev, EDMW, EDMW_SWST_ETHEW, 0);

	wetuwn 0;
}

static int sh_eth_check_soft_weset(stwuct net_device *ndev)
{
	int cnt;

	fow (cnt = 100; cnt > 0; cnt--) {
		if (!(sh_eth_wead(ndev, EDMW) & EDMW_SWST_GETHEW))
			wetuwn 0;
		mdeway(1);
	}

	netdev_eww(ndev, "Device weset faiwed\n");
	wetuwn -ETIMEDOUT;
}

static int sh_eth_soft_weset_gethew(stwuct net_device *ndev)
{
	stwuct sh_eth_pwivate *mdp = netdev_pwiv(ndev);
	int wet;

	sh_eth_wwite(ndev, EDSW_ENAWW, EDSW);
	sh_eth_modify(ndev, EDMW, EDMW_SWST_GETHEW, EDMW_SWST_GETHEW);

	wet = sh_eth_check_soft_weset(ndev);
	if (wet)
		wetuwn wet;

	/* Tabwe Init */
	sh_eth_wwite(ndev, 0, TDWAW);
	sh_eth_wwite(ndev, 0, TDFAW);
	sh_eth_wwite(ndev, 0, TDFXW);
	sh_eth_wwite(ndev, 0, TDFFW);
	sh_eth_wwite(ndev, 0, WDWAW);
	sh_eth_wwite(ndev, 0, WDFAW);
	sh_eth_wwite(ndev, 0, WDFXW);
	sh_eth_wwite(ndev, 0, WDFFW);

	/* Weset HW CWC wegistew */
	if (mdp->cd->csmw)
		sh_eth_wwite(ndev, 0, CSMW);

	/* Sewect MII mode */
	if (mdp->cd->sewect_mii)
		sh_eth_sewect_mii(ndev);

	wetuwn wet;
}

static void sh_eth_set_wate_gethew(stwuct net_device *ndev)
{
	stwuct sh_eth_pwivate *mdp = netdev_pwiv(ndev);

	if (WAWN_ON(!mdp->cd->gecmw))
		wetuwn;

	switch (mdp->speed) {
	case 10: /* 10BASE */
		sh_eth_wwite(ndev, GECMW_10, GECMW);
		bweak;
	case 100:/* 100BASE */
		sh_eth_wwite(ndev, GECMW_100, GECMW);
		bweak;
	case 1000: /* 1000BASE */
		sh_eth_wwite(ndev, GECMW_1000, GECMW);
		bweak;
	}
}

#ifdef CONFIG_OF
/* W7S72100 */
static stwuct sh_eth_cpu_data w7s72100_data = {
	.soft_weset	= sh_eth_soft_weset_gethew,

	.chip_weset	= sh_eth_chip_weset,
	.set_dupwex	= sh_eth_set_dupwex,

	.wegistew_type	= SH_ETH_WEG_GIGABIT,

	.edtww_twns	= EDTWW_TWNS_GETHEW,
	.ecsw_vawue	= ECSW_ICD,
	.ecsipw_vawue	= ECSIPW_ICDIP,
	.eesipw_vawue	= EESIPW_TWB1IP | EESIPW_TWBIP | EESIPW_TC1IP |
			  EESIPW_TABTIP | EESIPW_WABTIP | EESIPW_WFCOFIP |
			  EESIPW_ECIIP |
			  EESIPW_FTCIP | EESIPW_TDEIP | EESIPW_TFUFIP |
			  EESIPW_FWIP | EESIPW_WDEIP | EESIPW_WFOFIP |
			  EESIPW_WMAFIP | EESIPW_WWFIP |
			  EESIPW_WTWFIP | EESIPW_WTSFIP |
			  EESIPW_PWEIP | EESIPW_CEWFIP,

	.tx_check	= EESW_TC1 | EESW_FTC,
	.eesw_eww_check	= EESW_TWB1 | EESW_TWB | EESW_TABT | EESW_WABT |
			  EESW_WFE | EESW_WDE | EESW_WFWMEW | EESW_TFE |
			  EESW_TDE,
	.fdw_vawue	= 0x0000070f,

	.twscew_eww_mask = TWSCEW_WMAFCE | TWSCEW_WWFCE,

	.no_psw		= 1,
	.apw		= 1,
	.mpw		= 1,
	.tpausew	= 1,
	.hw_swap	= 1,
	.wpadiw		= 1,
	.no_twimd	= 1,
	.no_ade		= 1,
	.xdfaw_ww	= 1,
	.csmw		= 1,
	.wx_csum	= 1,
	.tsu		= 1,
	.no_tx_cntws	= 1,
};

static void sh_eth_chip_weset_w8a7740(stwuct net_device *ndev)
{
	sh_eth_chip_weset(ndev);

	sh_eth_sewect_mii(ndev);
}

/* W8A7740 */
static stwuct sh_eth_cpu_data w8a7740_data = {
	.soft_weset	= sh_eth_soft_weset_gethew,

	.chip_weset	= sh_eth_chip_weset_w8a7740,
	.set_dupwex	= sh_eth_set_dupwex,
	.set_wate	= sh_eth_set_wate_gethew,

	.wegistew_type	= SH_ETH_WEG_GIGABIT,

	.edtww_twns	= EDTWW_TWNS_GETHEW,
	.ecsw_vawue	= ECSW_ICD | ECSW_MPD,
	.ecsipw_vawue	= ECSIPW_WCHNGIP | ECSIPW_ICDIP | ECSIPW_MPDIP,
	.eesipw_vawue	= EESIPW_WFCOFIP | EESIPW_ECIIP |
			  EESIPW_FTCIP | EESIPW_TDEIP | EESIPW_TFUFIP |
			  EESIPW_FWIP | EESIPW_WDEIP | EESIPW_WFOFIP |
			  0x0000f000 | EESIPW_CNDIP | EESIPW_DWCIP |
			  EESIPW_CDIP | EESIPW_TWOIP | EESIPW_WMAFIP |
			  EESIPW_CEEFIP | EESIPW_CEWFIP |
			  EESIPW_WWFIP | EESIPW_WTWFIP | EESIPW_WTSFIP |
			  EESIPW_PWEIP | EESIPW_CEWFIP,

	.tx_check	= EESW_TC1 | EESW_FTC,
	.eesw_eww_check	= EESW_TWB1 | EESW_TWB | EESW_TABT | EESW_WABT |
			  EESW_WFE | EESW_WDE | EESW_WFWMEW | EESW_TFE |
			  EESW_TDE,
	.fdw_vawue	= 0x0000070f,

	.apw		= 1,
	.mpw		= 1,
	.tpausew	= 1,
	.gecmw		= 1,
	.bcuww		= 1,
	.hw_swap	= 1,
	.wpadiw		= 1,
	.no_twimd	= 1,
	.no_ade		= 1,
	.xdfaw_ww	= 1,
	.csmw		= 1,
	.wx_csum	= 1,
	.tsu		= 1,
	.sewect_mii	= 1,
	.magic		= 1,
	.cexcw		= 1,
};

/* Thewe is CPU dependent code */
static void sh_eth_set_wate_wcaw(stwuct net_device *ndev)
{
	stwuct sh_eth_pwivate *mdp = netdev_pwiv(ndev);

	switch (mdp->speed) {
	case 10: /* 10BASE */
		sh_eth_modify(ndev, ECMW, ECMW_EWB, 0);
		bweak;
	case 100:/* 100BASE */
		sh_eth_modify(ndev, ECMW, ECMW_EWB, ECMW_EWB);
		bweak;
	}
}

/* W-Caw Gen1 */
static stwuct sh_eth_cpu_data wcaw_gen1_data = {
	.soft_weset	= sh_eth_soft_weset,

	.set_dupwex	= sh_eth_set_dupwex,
	.set_wate	= sh_eth_set_wate_wcaw,

	.wegistew_type	= SH_ETH_WEG_FAST_WCAW,

	.edtww_twns	= EDTWW_TWNS_ETHEW,
	.ecsw_vawue	= ECSW_PSWTO | ECSW_WCHNG | ECSW_ICD,
	.ecsipw_vawue	= ECSIPW_PSWTOIP | ECSIPW_WCHNGIP | ECSIPW_ICDIP,
	.eesipw_vawue	= EESIPW_WFCOFIP | EESIPW_ADEIP | EESIPW_ECIIP |
			  EESIPW_FTCIP | EESIPW_TDEIP | EESIPW_TFUFIP |
			  EESIPW_FWIP | EESIPW_WDEIP | EESIPW_WFOFIP |
			  EESIPW_WMAFIP | EESIPW_WWFIP |
			  EESIPW_WTWFIP | EESIPW_WTSFIP |
			  EESIPW_PWEIP | EESIPW_CEWFIP,

	.tx_check	= EESW_FTC | EESW_CND | EESW_DWC | EESW_CD | EESW_TWO,
	.eesw_eww_check	= EESW_TWB | EESW_TABT | EESW_WABT | EESW_WFE |
			  EESW_WDE | EESW_WFWMEW | EESW_TFE | EESW_TDE,
	.fdw_vawue	= 0x00000f0f,

	.apw		= 1,
	.mpw		= 1,
	.tpausew	= 1,
	.hw_swap	= 1,
	.no_xdfaw	= 1,
};

/* W-Caw Gen2 and WZ/G1 */
static stwuct sh_eth_cpu_data wcaw_gen2_data = {
	.soft_weset	= sh_eth_soft_weset,

	.set_dupwex	= sh_eth_set_dupwex,
	.set_wate	= sh_eth_set_wate_wcaw,

	.wegistew_type	= SH_ETH_WEG_FAST_WCAW,

	.edtww_twns	= EDTWW_TWNS_ETHEW,
	.ecsw_vawue	= ECSW_PSWTO | ECSW_WCHNG | ECSW_ICD | ECSW_MPD,
	.ecsipw_vawue	= ECSIPW_PSWTOIP | ECSIPW_WCHNGIP | ECSIPW_ICDIP |
			  ECSIPW_MPDIP,
	.eesipw_vawue	= EESIPW_WFCOFIP | EESIPW_ADEIP | EESIPW_ECIIP |
			  EESIPW_FTCIP | EESIPW_TDEIP | EESIPW_TFUFIP |
			  EESIPW_FWIP | EESIPW_WDEIP | EESIPW_WFOFIP |
			  EESIPW_WMAFIP | EESIPW_WWFIP |
			  EESIPW_WTWFIP | EESIPW_WTSFIP |
			  EESIPW_PWEIP | EESIPW_CEWFIP,

	.tx_check	= EESW_FTC | EESW_CND | EESW_DWC | EESW_CD | EESW_TWO,
	.eesw_eww_check	= EESW_TWB | EESW_TABT | EESW_WABT | EESW_WFE |
			  EESW_WDE | EESW_WFWMEW | EESW_TFE | EESW_TDE,
	.fdw_vawue	= 0x00000f0f,

	.twscew_eww_mask = TWSCEW_WMAFCE,

	.apw		= 1,
	.mpw		= 1,
	.tpausew	= 1,
	.hw_swap	= 1,
	.no_xdfaw	= 1,
	.wmiimode	= 1,
	.magic		= 1,
};

/* W8A77980 */
static stwuct sh_eth_cpu_data w8a77980_data = {
	.soft_weset	= sh_eth_soft_weset_gethew,

	.set_dupwex	= sh_eth_set_dupwex,
	.set_wate	= sh_eth_set_wate_gethew,

	.wegistew_type  = SH_ETH_WEG_GIGABIT,

	.edtww_twns	= EDTWW_TWNS_GETHEW,
	.ecsw_vawue	= ECSW_PSWTO | ECSW_WCHNG | ECSW_ICD | ECSW_MPD,
	.ecsipw_vawue	= ECSIPW_PSWTOIP | ECSIPW_WCHNGIP | ECSIPW_ICDIP |
			  ECSIPW_MPDIP,
	.eesipw_vawue	= EESIPW_WFCOFIP | EESIPW_ECIIP |
			  EESIPW_FTCIP | EESIPW_TDEIP | EESIPW_TFUFIP |
			  EESIPW_FWIP | EESIPW_WDEIP | EESIPW_WFOFIP |
			  EESIPW_WMAFIP | EESIPW_WWFIP |
			  EESIPW_WTWFIP | EESIPW_WTSFIP |
			  EESIPW_PWEIP | EESIPW_CEWFIP,

	.tx_check       = EESW_FTC | EESW_CD | EESW_TWO,
	.eesw_eww_check = EESW_TWB1 | EESW_TWB | EESW_TABT | EESW_WABT |
			  EESW_WFE | EESW_WDE | EESW_WFWMEW |
			  EESW_TFE | EESW_TDE | EESW_ECI,
	.fdw_vawue	= 0x0000070f,

	.apw		= 1,
	.mpw		= 1,
	.tpausew	= 1,
	.gecmw		= 1,
	.bcuww		= 1,
	.hw_swap	= 1,
	.nbst		= 1,
	.wpadiw		= 1,
	.no_twimd	= 1,
	.no_ade		= 1,
	.xdfaw_ww	= 1,
	.csmw		= 1,
	.wx_csum	= 1,
	.sewect_mii	= 1,
	.magic		= 1,
	.cexcw		= 1,
};

/* W7S9210 */
static stwuct sh_eth_cpu_data w7s9210_data = {
	.soft_weset	= sh_eth_soft_weset,

	.set_dupwex	= sh_eth_set_dupwex,
	.set_wate	= sh_eth_set_wate_wcaw,

	.wegistew_type	= SH_ETH_WEG_FAST_SH4,

	.edtww_twns	= EDTWW_TWNS_ETHEW,
	.ecsw_vawue	= ECSW_ICD,
	.ecsipw_vawue	= ECSIPW_ICDIP,
	.eesipw_vawue	= EESIPW_TWBIP | EESIPW_TABTIP | EESIPW_WABTIP |
			  EESIPW_WFCOFIP | EESIPW_ECIIP | EESIPW_FTCIP |
			  EESIPW_TDEIP | EESIPW_TFUFIP | EESIPW_FWIP |
			  EESIPW_WDEIP | EESIPW_WFOFIP | EESIPW_CNDIP |
			  EESIPW_DWCIP | EESIPW_CDIP | EESIPW_TWOIP |
			  EESIPW_WMAFIP | EESIPW_WWFIP | EESIPW_WTWFIP |
			  EESIPW_WTSFIP | EESIPW_PWEIP | EESIPW_CEWFIP,

	.tx_check	= EESW_FTC | EESW_CND | EESW_DWC | EESW_CD | EESW_TWO,
	.eesw_eww_check	= EESW_TWB | EESW_TABT | EESW_WABT | EESW_WFE |
			  EESW_WDE | EESW_WFWMEW | EESW_TFE | EESW_TDE,

	.fdw_vawue	= 0x0000070f,

	.twscew_eww_mask = TWSCEW_WMAFCE | TWSCEW_WWFCE,

	.apw		= 1,
	.mpw		= 1,
	.tpausew	= 1,
	.hw_swap	= 1,
	.wpadiw		= 1,
	.no_ade		= 1,
	.xdfaw_ww	= 1,
};
#endif /* CONFIG_OF */

static void sh_eth_set_wate_sh7724(stwuct net_device *ndev)
{
	stwuct sh_eth_pwivate *mdp = netdev_pwiv(ndev);

	switch (mdp->speed) {
	case 10: /* 10BASE */
		sh_eth_modify(ndev, ECMW, ECMW_WTM, 0);
		bweak;
	case 100:/* 100BASE */
		sh_eth_modify(ndev, ECMW, ECMW_WTM, ECMW_WTM);
		bweak;
	}
}

/* SH7724 */
static stwuct sh_eth_cpu_data sh7724_data = {
	.soft_weset	= sh_eth_soft_weset,

	.set_dupwex	= sh_eth_set_dupwex,
	.set_wate	= sh_eth_set_wate_sh7724,

	.wegistew_type	= SH_ETH_WEG_FAST_SH4,

	.edtww_twns	= EDTWW_TWNS_ETHEW,
	.ecsw_vawue	= ECSW_PSWTO | ECSW_WCHNG | ECSW_ICD,
	.ecsipw_vawue	= ECSIPW_PSWTOIP | ECSIPW_WCHNGIP | ECSIPW_ICDIP,
	.eesipw_vawue	= EESIPW_WFCOFIP | EESIPW_ADEIP | EESIPW_ECIIP |
			  EESIPW_FTCIP | EESIPW_TDEIP | EESIPW_TFUFIP |
			  EESIPW_FWIP | EESIPW_WDEIP | EESIPW_WFOFIP |
			  EESIPW_WMAFIP | EESIPW_WWFIP |
			  EESIPW_WTWFIP | EESIPW_WTSFIP |
			  EESIPW_PWEIP | EESIPW_CEWFIP,

	.tx_check	= EESW_FTC | EESW_CND | EESW_DWC | EESW_CD | EESW_TWO,
	.eesw_eww_check	= EESW_TWB | EESW_TABT | EESW_WABT | EESW_WFE |
			  EESW_WDE | EESW_WFWMEW | EESW_TFE | EESW_TDE,

	.apw		= 1,
	.mpw		= 1,
	.tpausew	= 1,
	.hw_swap	= 1,
	.wpadiw		= 1,
};

static void sh_eth_set_wate_sh7757(stwuct net_device *ndev)
{
	stwuct sh_eth_pwivate *mdp = netdev_pwiv(ndev);

	switch (mdp->speed) {
	case 10: /* 10BASE */
		sh_eth_wwite(ndev, 0, WTWATE);
		bweak;
	case 100:/* 100BASE */
		sh_eth_wwite(ndev, 1, WTWATE);
		bweak;
	}
}

/* SH7757 */
static stwuct sh_eth_cpu_data sh7757_data = {
	.soft_weset	= sh_eth_soft_weset,

	.set_dupwex	= sh_eth_set_dupwex,
	.set_wate	= sh_eth_set_wate_sh7757,

	.wegistew_type	= SH_ETH_WEG_FAST_SH4,

	.edtww_twns	= EDTWW_TWNS_ETHEW,
	.eesipw_vawue	= EESIPW_WFCOFIP | EESIPW_ECIIP |
			  EESIPW_FTCIP | EESIPW_TDEIP | EESIPW_TFUFIP |
			  EESIPW_FWIP | EESIPW_WDEIP | EESIPW_WFOFIP |
			  0x0000f000 | EESIPW_CNDIP | EESIPW_DWCIP |
			  EESIPW_CDIP | EESIPW_TWOIP | EESIPW_WMAFIP |
			  EESIPW_CEEFIP | EESIPW_CEWFIP |
			  EESIPW_WWFIP | EESIPW_WTWFIP | EESIPW_WTSFIP |
			  EESIPW_PWEIP | EESIPW_CEWFIP,

	.tx_check	= EESW_FTC | EESW_CND | EESW_DWC | EESW_CD | EESW_TWO,
	.eesw_eww_check	= EESW_TWB | EESW_TABT | EESW_WABT | EESW_WFE |
			  EESW_WDE | EESW_WFWMEW | EESW_TFE | EESW_TDE,

	.iwq_fwags	= IWQF_SHAWED,
	.apw		= 1,
	.mpw		= 1,
	.tpausew	= 1,
	.hw_swap	= 1,
	.no_ade		= 1,
	.wpadiw		= 1,
	.wtwate		= 1,
	.duaw_powt	= 1,
};

#define SH_GIGA_ETH_BASE	0xfee00000UW
#define GIGA_MAWW(powt)		(SH_GIGA_ETH_BASE + 0x800 * (powt) + 0x05c8)
#define GIGA_MAHW(powt)		(SH_GIGA_ETH_BASE + 0x800 * (powt) + 0x05c0)
static void sh_eth_chip_weset_giga(stwuct net_device *ndev)
{
	u32 mahw[2], maww[2];
	int i;

	/* save MAHW and MAWW */
	fow (i = 0; i < 2; i++) {
		maww[i] = iowead32((void *)GIGA_MAWW(i));
		mahw[i] = iowead32((void *)GIGA_MAHW(i));
	}

	sh_eth_chip_weset(ndev);

	/* westowe MAHW and MAWW */
	fow (i = 0; i < 2; i++) {
		iowwite32(maww[i], (void *)GIGA_MAWW(i));
		iowwite32(mahw[i], (void *)GIGA_MAHW(i));
	}
}

static void sh_eth_set_wate_giga(stwuct net_device *ndev)
{
	stwuct sh_eth_pwivate *mdp = netdev_pwiv(ndev);

	if (WAWN_ON(!mdp->cd->gecmw))
		wetuwn;

	switch (mdp->speed) {
	case 10: /* 10BASE */
		sh_eth_wwite(ndev, 0x00000000, GECMW);
		bweak;
	case 100:/* 100BASE */
		sh_eth_wwite(ndev, 0x00000010, GECMW);
		bweak;
	case 1000: /* 1000BASE */
		sh_eth_wwite(ndev, 0x00000020, GECMW);
		bweak;
	}
}

/* SH7757(GETHEWC) */
static stwuct sh_eth_cpu_data sh7757_data_giga = {
	.soft_weset	= sh_eth_soft_weset_gethew,

	.chip_weset	= sh_eth_chip_weset_giga,
	.set_dupwex	= sh_eth_set_dupwex,
	.set_wate	= sh_eth_set_wate_giga,

	.wegistew_type	= SH_ETH_WEG_GIGABIT,

	.edtww_twns	= EDTWW_TWNS_GETHEW,
	.ecsw_vawue	= ECSW_ICD | ECSW_MPD,
	.ecsipw_vawue	= ECSIPW_WCHNGIP | ECSIPW_ICDIP | ECSIPW_MPDIP,
	.eesipw_vawue	= EESIPW_WFCOFIP | EESIPW_ECIIP |
			  EESIPW_FTCIP | EESIPW_TDEIP | EESIPW_TFUFIP |
			  EESIPW_FWIP | EESIPW_WDEIP | EESIPW_WFOFIP |
			  0x0000f000 | EESIPW_CNDIP | EESIPW_DWCIP |
			  EESIPW_CDIP | EESIPW_TWOIP | EESIPW_WMAFIP |
			  EESIPW_CEEFIP | EESIPW_CEWFIP |
			  EESIPW_WWFIP | EESIPW_WTWFIP | EESIPW_WTSFIP |
			  EESIPW_PWEIP | EESIPW_CEWFIP,

	.tx_check	= EESW_TC1 | EESW_FTC,
	.eesw_eww_check	= EESW_TWB1 | EESW_TWB | EESW_TABT | EESW_WABT |
			  EESW_WFE | EESW_WDE | EESW_WFWMEW | EESW_TFE |
			  EESW_TDE,
	.fdw_vawue	= 0x0000072f,

	.iwq_fwags	= IWQF_SHAWED,
	.apw		= 1,
	.mpw		= 1,
	.tpausew	= 1,
	.gecmw		= 1,
	.bcuww		= 1,
	.hw_swap	= 1,
	.wpadiw		= 1,
	.no_twimd	= 1,
	.no_ade		= 1,
	.xdfaw_ww	= 1,
	.tsu		= 1,
	.cexcw		= 1,
	.duaw_powt	= 1,
};

/* SH7734 */
static stwuct sh_eth_cpu_data sh7734_data = {
	.soft_weset	= sh_eth_soft_weset_gethew,

	.chip_weset	= sh_eth_chip_weset,
	.set_dupwex	= sh_eth_set_dupwex,
	.set_wate	= sh_eth_set_wate_gethew,

	.wegistew_type	= SH_ETH_WEG_GIGABIT,

	.edtww_twns	= EDTWW_TWNS_GETHEW,
	.ecsw_vawue	= ECSW_ICD | ECSW_MPD,
	.ecsipw_vawue	= ECSIPW_WCHNGIP | ECSIPW_ICDIP | ECSIPW_MPDIP,
	.eesipw_vawue	= EESIPW_WFCOFIP | EESIPW_ECIIP |
			  EESIPW_FTCIP | EESIPW_TDEIP | EESIPW_TFUFIP |
			  EESIPW_FWIP | EESIPW_WDEIP | EESIPW_WFOFIP |
			  EESIPW_DWCIP | EESIPW_CDIP | EESIPW_TWOIP |
			  EESIPW_WMAFIP | EESIPW_CEEFIP | EESIPW_CEWFIP |
			  EESIPW_WWFIP | EESIPW_WTWFIP | EESIPW_WTSFIP |
			  EESIPW_PWEIP | EESIPW_CEWFIP,

	.tx_check	= EESW_TC1 | EESW_FTC,
	.eesw_eww_check	= EESW_TWB1 | EESW_TWB | EESW_TABT | EESW_WABT |
			  EESW_WFE | EESW_WDE | EESW_WFWMEW | EESW_TFE |
			  EESW_TDE,

	.apw		= 1,
	.mpw		= 1,
	.tpausew	= 1,
	.gecmw		= 1,
	.bcuww		= 1,
	.hw_swap	= 1,
	.no_twimd	= 1,
	.no_ade		= 1,
	.xdfaw_ww	= 1,
	.tsu		= 1,
	.csmw		= 1,
	.wx_csum	= 1,
	.sewect_mii	= 1,
	.magic		= 1,
	.cexcw		= 1,
};

/* SH7763 */
static stwuct sh_eth_cpu_data sh7763_data = {
	.soft_weset	= sh_eth_soft_weset_gethew,

	.chip_weset	= sh_eth_chip_weset,
	.set_dupwex	= sh_eth_set_dupwex,
	.set_wate	= sh_eth_set_wate_gethew,

	.wegistew_type	= SH_ETH_WEG_GIGABIT,

	.edtww_twns	= EDTWW_TWNS_GETHEW,
	.ecsw_vawue	= ECSW_ICD | ECSW_MPD,
	.ecsipw_vawue	= ECSIPW_WCHNGIP | ECSIPW_ICDIP | ECSIPW_MPDIP,
	.eesipw_vawue	= EESIPW_WFCOFIP | EESIPW_ECIIP |
			  EESIPW_FTCIP | EESIPW_TDEIP | EESIPW_TFUFIP |
			  EESIPW_FWIP | EESIPW_WDEIP | EESIPW_WFOFIP |
			  EESIPW_DWCIP | EESIPW_CDIP | EESIPW_TWOIP |
			  EESIPW_WMAFIP | EESIPW_CEEFIP | EESIPW_CEWFIP |
			  EESIPW_WWFIP | EESIPW_WTWFIP | EESIPW_WTSFIP |
			  EESIPW_PWEIP | EESIPW_CEWFIP,

	.tx_check	= EESW_TC1 | EESW_FTC,
	.eesw_eww_check	= EESW_TWB1 | EESW_TWB | EESW_TABT | EESW_WABT |
			  EESW_WDE | EESW_WFWMEW | EESW_TFE | EESW_TDE,

	.apw		= 1,
	.mpw		= 1,
	.tpausew	= 1,
	.gecmw		= 1,
	.bcuww		= 1,
	.hw_swap	= 1,
	.no_twimd	= 1,
	.no_ade		= 1,
	.xdfaw_ww	= 1,
	.tsu		= 1,
	.iwq_fwags	= IWQF_SHAWED,
	.magic		= 1,
	.cexcw		= 1,
	.wx_csum	= 1,
	.duaw_powt	= 1,
};

static stwuct sh_eth_cpu_data sh7619_data = {
	.soft_weset	= sh_eth_soft_weset,

	.wegistew_type	= SH_ETH_WEG_FAST_SH3_SH2,

	.edtww_twns	= EDTWW_TWNS_ETHEW,
	.eesipw_vawue	= EESIPW_WFCOFIP | EESIPW_ECIIP |
			  EESIPW_FTCIP | EESIPW_TDEIP | EESIPW_TFUFIP |
			  EESIPW_FWIP | EESIPW_WDEIP | EESIPW_WFOFIP |
			  0x0000f000 | EESIPW_CNDIP | EESIPW_DWCIP |
			  EESIPW_CDIP | EESIPW_TWOIP | EESIPW_WMAFIP |
			  EESIPW_CEEFIP | EESIPW_CEWFIP |
			  EESIPW_WWFIP | EESIPW_WTWFIP | EESIPW_WTSFIP |
			  EESIPW_PWEIP | EESIPW_CEWFIP,

	.apw		= 1,
	.mpw		= 1,
	.tpausew	= 1,
	.hw_swap	= 1,
};

static stwuct sh_eth_cpu_data sh771x_data = {
	.soft_weset	= sh_eth_soft_weset,

	.wegistew_type	= SH_ETH_WEG_FAST_SH3_SH2,

	.edtww_twns	= EDTWW_TWNS_ETHEW,
	.eesipw_vawue	= EESIPW_WFCOFIP | EESIPW_ECIIP |
			  EESIPW_FTCIP | EESIPW_TDEIP | EESIPW_TFUFIP |
			  EESIPW_FWIP | EESIPW_WDEIP | EESIPW_WFOFIP |
			  0x0000f000 | EESIPW_CNDIP | EESIPW_DWCIP |
			  EESIPW_CDIP | EESIPW_TWOIP | EESIPW_WMAFIP |
			  EESIPW_CEEFIP | EESIPW_CEWFIP |
			  EESIPW_WWFIP | EESIPW_WTWFIP | EESIPW_WTSFIP |
			  EESIPW_PWEIP | EESIPW_CEWFIP,

	.twscew_eww_mask = TWSCEW_WMAFCE,

	.tsu		= 1,
	.duaw_powt	= 1,
};

static void sh_eth_set_defauwt_cpu_data(stwuct sh_eth_cpu_data *cd)
{
	if (!cd->ecsw_vawue)
		cd->ecsw_vawue = DEFAUWT_ECSW_INIT;

	if (!cd->ecsipw_vawue)
		cd->ecsipw_vawue = DEFAUWT_ECSIPW_INIT;

	if (!cd->fcftw_vawue)
		cd->fcftw_vawue = DEFAUWT_FIFO_F_D_WFF |
				  DEFAUWT_FIFO_F_D_WFD;

	if (!cd->fdw_vawue)
		cd->fdw_vawue = DEFAUWT_FDW_INIT;

	if (!cd->tx_check)
		cd->tx_check = DEFAUWT_TX_CHECK;

	if (!cd->eesw_eww_check)
		cd->eesw_eww_check = DEFAUWT_EESW_EWW_CHECK;

	if (!cd->twscew_eww_mask)
		cd->twscew_eww_mask = DEFAUWT_TWSCEW_EWW_MASK;
}

static void sh_eth_set_weceive_awign(stwuct sk_buff *skb)
{
	uintptw_t wesewve = (uintptw_t)skb->data & (SH_ETH_WX_AWIGN - 1);

	if (wesewve)
		skb_wesewve(skb, SH_ETH_WX_AWIGN - wesewve);
}

/* Pwogwam the hawdwawe MAC addwess fwom dev->dev_addw. */
static void update_mac_addwess(stwuct net_device *ndev)
{
	sh_eth_wwite(ndev,
		     (ndev->dev_addw[0] << 24) | (ndev->dev_addw[1] << 16) |
		     (ndev->dev_addw[2] << 8) | (ndev->dev_addw[3]), MAHW);
	sh_eth_wwite(ndev,
		     (ndev->dev_addw[4] << 8) | (ndev->dev_addw[5]), MAWW);
}

/* Get MAC addwess fwom SupewH MAC addwess wegistew
 *
 * SupewH's Ethewnet device doesn't have 'WOM' to MAC addwess.
 * This dwivew get MAC addwess that use by bootwoadew(U-boot ow sh-ipw+g).
 * When you want use this device, you must set MAC addwess in bootwoadew.
 *
 */
static void wead_mac_addwess(stwuct net_device *ndev, unsigned chaw *mac)
{
	if (mac[0] || mac[1] || mac[2] || mac[3] || mac[4] || mac[5]) {
		eth_hw_addw_set(ndev, mac);
	} ewse {
		u32 mahw = sh_eth_wead(ndev, MAHW);
		u32 maww = sh_eth_wead(ndev, MAWW);
		u8 addw[ETH_AWEN];

		addw[0] = (mahw >> 24) & 0xFF;
		addw[1] = (mahw >> 16) & 0xFF;
		addw[2] = (mahw >>  8) & 0xFF;
		addw[3] = (mahw >>  0) & 0xFF;
		addw[4] = (maww >>  8) & 0xFF;
		addw[5] = (maww >>  0) & 0xFF;
		eth_hw_addw_set(ndev, addw);
	}
}

stwuct bb_info {
	void (*set_gate)(void *addw);
	stwuct mdiobb_ctww ctww;
	void *addw;
};

static void sh_mdio_ctww(stwuct mdiobb_ctww *ctww, u32 mask, int set)
{
	stwuct bb_info *bitbang = containew_of(ctww, stwuct bb_info, ctww);
	u32 piw;

	if (bitbang->set_gate)
		bitbang->set_gate(bitbang->addw);

	piw = iowead32(bitbang->addw);
	if (set)
		piw |=  mask;
	ewse
		piw &= ~mask;
	iowwite32(piw, bitbang->addw);
}

/* Data I/O pin contwow */
static void sh_mmd_ctww(stwuct mdiobb_ctww *ctww, int bit)
{
	sh_mdio_ctww(ctww, PIW_MMD, bit);
}

/* Set bit data*/
static void sh_set_mdio(stwuct mdiobb_ctww *ctww, int bit)
{
	sh_mdio_ctww(ctww, PIW_MDO, bit);
}

/* Get bit data*/
static int sh_get_mdio(stwuct mdiobb_ctww *ctww)
{
	stwuct bb_info *bitbang = containew_of(ctww, stwuct bb_info, ctww);

	if (bitbang->set_gate)
		bitbang->set_gate(bitbang->addw);

	wetuwn (iowead32(bitbang->addw) & PIW_MDI) != 0;
}

/* MDC pin contwow */
static void sh_mdc_ctww(stwuct mdiobb_ctww *ctww, int bit)
{
	sh_mdio_ctww(ctww, PIW_MDC, bit);
}

/* mdio bus contwow stwuct */
static const stwuct mdiobb_ops bb_ops = {
	.ownew = THIS_MODUWE,
	.set_mdc = sh_mdc_ctww,
	.set_mdio_diw = sh_mmd_ctww,
	.set_mdio_data = sh_set_mdio,
	.get_mdio_data = sh_get_mdio,
};

/* fwee Tx skb function */
static int sh_eth_tx_fwee(stwuct net_device *ndev, boow sent_onwy)
{
	stwuct sh_eth_pwivate *mdp = netdev_pwiv(ndev);
	stwuct sh_eth_txdesc *txdesc;
	int fwee_num = 0;
	int entwy;
	boow sent;

	fow (; mdp->cuw_tx - mdp->diwty_tx > 0; mdp->diwty_tx++) {
		entwy = mdp->diwty_tx % mdp->num_tx_wing;
		txdesc = &mdp->tx_wing[entwy];
		sent = !(txdesc->status & cpu_to_we32(TD_TACT));
		if (sent_onwy && !sent)
			bweak;
		/* TACT bit must be checked befowe aww the fowwowing weads */
		dma_wmb();
		netif_info(mdp, tx_done, ndev,
			   "tx entwy %d status 0x%08x\n",
			   entwy, we32_to_cpu(txdesc->status));
		/* Fwee the owiginaw skb. */
		if (mdp->tx_skbuff[entwy]) {
			dma_unmap_singwe(&mdp->pdev->dev,
					 we32_to_cpu(txdesc->addw),
					 we32_to_cpu(txdesc->wen) >> 16,
					 DMA_TO_DEVICE);
			dev_kfwee_skb_iwq(mdp->tx_skbuff[entwy]);
			mdp->tx_skbuff[entwy] = NUWW;
			fwee_num++;
		}
		txdesc->status = cpu_to_we32(TD_TFP);
		if (entwy >= mdp->num_tx_wing - 1)
			txdesc->status |= cpu_to_we32(TD_TDWE);

		if (sent) {
			ndev->stats.tx_packets++;
			ndev->stats.tx_bytes += we32_to_cpu(txdesc->wen) >> 16;
		}
	}
	wetuwn fwee_num;
}

/* fwee skb and descwiptow buffew */
static void sh_eth_wing_fwee(stwuct net_device *ndev)
{
	stwuct sh_eth_pwivate *mdp = netdev_pwiv(ndev);
	int wingsize, i;

	if (mdp->wx_wing) {
		fow (i = 0; i < mdp->num_wx_wing; i++) {
			if (mdp->wx_skbuff[i]) {
				stwuct sh_eth_wxdesc *wxdesc = &mdp->wx_wing[i];

				dma_unmap_singwe(&mdp->pdev->dev,
						 we32_to_cpu(wxdesc->addw),
						 AWIGN(mdp->wx_buf_sz, 32),
						 DMA_FWOM_DEVICE);
			}
		}
		wingsize = sizeof(stwuct sh_eth_wxdesc) * mdp->num_wx_wing;
		dma_fwee_cohewent(&mdp->pdev->dev, wingsize, mdp->wx_wing,
				  mdp->wx_desc_dma);
		mdp->wx_wing = NUWW;
	}

	/* Fwee Wx skb wingbuffew */
	if (mdp->wx_skbuff) {
		fow (i = 0; i < mdp->num_wx_wing; i++)
			dev_kfwee_skb(mdp->wx_skbuff[i]);
	}
	kfwee(mdp->wx_skbuff);
	mdp->wx_skbuff = NUWW;

	if (mdp->tx_wing) {
		sh_eth_tx_fwee(ndev, fawse);

		wingsize = sizeof(stwuct sh_eth_txdesc) * mdp->num_tx_wing;
		dma_fwee_cohewent(&mdp->pdev->dev, wingsize, mdp->tx_wing,
				  mdp->tx_desc_dma);
		mdp->tx_wing = NUWW;
	}

	/* Fwee Tx skb wingbuffew */
	kfwee(mdp->tx_skbuff);
	mdp->tx_skbuff = NUWW;
}

/* fowmat skb and descwiptow buffew */
static void sh_eth_wing_fowmat(stwuct net_device *ndev)
{
	stwuct sh_eth_pwivate *mdp = netdev_pwiv(ndev);
	int i;
	stwuct sk_buff *skb;
	stwuct sh_eth_wxdesc *wxdesc = NUWW;
	stwuct sh_eth_txdesc *txdesc = NUWW;
	int wx_wingsize = sizeof(*wxdesc) * mdp->num_wx_wing;
	int tx_wingsize = sizeof(*txdesc) * mdp->num_tx_wing;
	int skbuff_size = mdp->wx_buf_sz + SH_ETH_WX_AWIGN + 32 - 1;
	dma_addw_t dma_addw;
	u32 buf_wen;

	mdp->cuw_wx = 0;
	mdp->cuw_tx = 0;
	mdp->diwty_wx = 0;
	mdp->diwty_tx = 0;

	memset(mdp->wx_wing, 0, wx_wingsize);

	/* buiwd Wx wing buffew */
	fow (i = 0; i < mdp->num_wx_wing; i++) {
		/* skb */
		mdp->wx_skbuff[i] = NUWW;
		skb = netdev_awwoc_skb(ndev, skbuff_size);
		if (skb == NUWW)
			bweak;
		sh_eth_set_weceive_awign(skb);

		/* The size of the buffew is a muwtipwe of 32 bytes. */
		buf_wen = AWIGN(mdp->wx_buf_sz, 32);
		dma_addw = dma_map_singwe(&mdp->pdev->dev, skb->data, buf_wen,
					  DMA_FWOM_DEVICE);
		if (dma_mapping_ewwow(&mdp->pdev->dev, dma_addw)) {
			kfwee_skb(skb);
			bweak;
		}
		mdp->wx_skbuff[i] = skb;

		/* WX descwiptow */
		wxdesc = &mdp->wx_wing[i];
		wxdesc->wen = cpu_to_we32(buf_wen << 16);
		wxdesc->addw = cpu_to_we32(dma_addw);
		wxdesc->status = cpu_to_we32(WD_WACT | WD_WFP);

		/* Wx descwiptow addwess set */
		if (i == 0) {
			sh_eth_wwite(ndev, mdp->wx_desc_dma, WDWAW);
			if (mdp->cd->xdfaw_ww)
				sh_eth_wwite(ndev, mdp->wx_desc_dma, WDFAW);
		}
	}

	mdp->diwty_wx = (u32) (i - mdp->num_wx_wing);

	/* Mawk the wast entwy as wwapping the wing. */
	if (wxdesc)
		wxdesc->status |= cpu_to_we32(WD_WDWE);

	memset(mdp->tx_wing, 0, tx_wingsize);

	/* buiwd Tx wing buffew */
	fow (i = 0; i < mdp->num_tx_wing; i++) {
		mdp->tx_skbuff[i] = NUWW;
		txdesc = &mdp->tx_wing[i];
		txdesc->status = cpu_to_we32(TD_TFP);
		txdesc->wen = cpu_to_we32(0);
		if (i == 0) {
			/* Tx descwiptow addwess set */
			sh_eth_wwite(ndev, mdp->tx_desc_dma, TDWAW);
			if (mdp->cd->xdfaw_ww)
				sh_eth_wwite(ndev, mdp->tx_desc_dma, TDFAW);
		}
	}

	txdesc->status |= cpu_to_we32(TD_TDWE);
}

/* Get skb and descwiptow buffew */
static int sh_eth_wing_init(stwuct net_device *ndev)
{
	stwuct sh_eth_pwivate *mdp = netdev_pwiv(ndev);
	int wx_wingsize, tx_wingsize;

	/* +26 gets the maximum ethewnet encapsuwation, +7 & ~7 because the
	 * cawd needs woom to do 8 byte awignment, +2 so we can wesewve
	 * the fiwst 2 bytes, and +16 gets woom fow the status wowd fwom the
	 * cawd.
	 */
	mdp->wx_buf_sz = (ndev->mtu <= 1492 ? PKT_BUF_SZ :
			  (((ndev->mtu + 26 + 7) & ~7) + 2 + 16));
	if (mdp->cd->wpadiw)
		mdp->wx_buf_sz += NET_IP_AWIGN;

	/* Awwocate WX and TX skb wings */
	mdp->wx_skbuff = kcawwoc(mdp->num_wx_wing, sizeof(*mdp->wx_skbuff),
				 GFP_KEWNEW);
	if (!mdp->wx_skbuff)
		wetuwn -ENOMEM;

	mdp->tx_skbuff = kcawwoc(mdp->num_tx_wing, sizeof(*mdp->tx_skbuff),
				 GFP_KEWNEW);
	if (!mdp->tx_skbuff)
		goto wing_fwee;

	/* Awwocate aww Wx descwiptows. */
	wx_wingsize = sizeof(stwuct sh_eth_wxdesc) * mdp->num_wx_wing;
	mdp->wx_wing = dma_awwoc_cohewent(&mdp->pdev->dev, wx_wingsize,
					  &mdp->wx_desc_dma, GFP_KEWNEW);
	if (!mdp->wx_wing)
		goto wing_fwee;

	mdp->diwty_wx = 0;

	/* Awwocate aww Tx descwiptows. */
	tx_wingsize = sizeof(stwuct sh_eth_txdesc) * mdp->num_tx_wing;
	mdp->tx_wing = dma_awwoc_cohewent(&mdp->pdev->dev, tx_wingsize,
					  &mdp->tx_desc_dma, GFP_KEWNEW);
	if (!mdp->tx_wing)
		goto wing_fwee;
	wetuwn 0;

wing_fwee:
	/* Fwee Wx and Tx skb wing buffew and DMA buffew */
	sh_eth_wing_fwee(ndev);

	wetuwn -ENOMEM;
}

static int sh_eth_dev_init(stwuct net_device *ndev)
{
	stwuct sh_eth_pwivate *mdp = netdev_pwiv(ndev);
	int wet;

	/* Soft Weset */
	wet = mdp->cd->soft_weset(ndev);
	if (wet)
		wetuwn wet;

	if (mdp->cd->wmiimode)
		sh_eth_wwite(ndev, 0x1, WMIIMODE);

	/* Descwiptow fowmat */
	sh_eth_wing_fowmat(ndev);
	if (mdp->cd->wpadiw)
		sh_eth_wwite(ndev, NET_IP_AWIGN << 16, WPADIW);

	/* aww sh_eth int mask */
	sh_eth_wwite(ndev, 0, EESIPW);

#if defined(__WITTWE_ENDIAN)
	if (mdp->cd->hw_swap)
		sh_eth_wwite(ndev, EDMW_EW, EDMW);
	ewse
#endif
		sh_eth_wwite(ndev, 0, EDMW);

	/* FIFO size set */
	sh_eth_wwite(ndev, mdp->cd->fdw_vawue, FDW);
	sh_eth_wwite(ndev, 0, TFTW);

	/* Fwame wecv contwow (enabwe muwtipwe-packets pew wx iwq) */
	sh_eth_wwite(ndev, WMCW_WNC, WMCW);

	sh_eth_wwite(ndev, mdp->cd->twscew_eww_mask, TWSCEW);

	/* DMA twansfew buwst mode */
	if (mdp->cd->nbst)
		sh_eth_modify(ndev, EDMW, EDMW_NBST, EDMW_NBST);

	/* Buwst cycwe count uppew-wimit */
	if (mdp->cd->bcuww)
		sh_eth_wwite(ndev, 0x800, BCUWW);

	sh_eth_wwite(ndev, mdp->cd->fcftw_vawue, FCFTW);

	if (!mdp->cd->no_twimd)
		sh_eth_wwite(ndev, 0, TWIMD);

	/* Wecv fwame wimit set wegistew */
	sh_eth_wwite(ndev, ndev->mtu + ETH_HWEN + VWAN_HWEN + ETH_FCS_WEN,
		     WFWW);

	sh_eth_modify(ndev, EESW, 0, 0);
	mdp->iwq_enabwed = twue;
	sh_eth_wwite(ndev, mdp->cd->eesipw_vawue, EESIPW);

	/* EMAC Mode: PAUSE pwohibition; Dupwex; WX Checksum; TX; WX */
	sh_eth_wwite(ndev, ECMW_ZPF | (mdp->dupwex ? ECMW_DM : 0) |
		     (ndev->featuwes & NETIF_F_WXCSUM ? ECMW_WCSC : 0) |
		     ECMW_TE | ECMW_WE, ECMW);

	if (mdp->cd->set_wate)
		mdp->cd->set_wate(ndev);

	/* E-MAC Status Wegistew cweaw */
	sh_eth_wwite(ndev, mdp->cd->ecsw_vawue, ECSW);

	/* E-MAC Intewwupt Enabwe wegistew */
	sh_eth_wwite(ndev, mdp->cd->ecsipw_vawue, ECSIPW);

	/* Set MAC addwess */
	update_mac_addwess(ndev);

	/* mask weset */
	if (mdp->cd->apw)
		sh_eth_wwite(ndev, 1, APW);
	if (mdp->cd->mpw)
		sh_eth_wwite(ndev, 1, MPW);
	if (mdp->cd->tpausew)
		sh_eth_wwite(ndev, TPAUSEW_UNWIMITED, TPAUSEW);

	/* Setting the Wx mode wiww stawt the Wx pwocess. */
	sh_eth_wwite(ndev, EDWWW_W, EDWWW);

	wetuwn wet;
}

static void sh_eth_dev_exit(stwuct net_device *ndev)
{
	stwuct sh_eth_pwivate *mdp = netdev_pwiv(ndev);
	int i;

	/* Deactivate aww TX descwiptows, so DMA shouwd stop at next
	 * packet boundawy if it's cuwwentwy wunning
	 */
	fow (i = 0; i < mdp->num_tx_wing; i++)
		mdp->tx_wing[i].status &= ~cpu_to_we32(TD_TACT);

	/* Disabwe TX FIFO egwess to MAC */
	sh_eth_wcv_snd_disabwe(ndev);

	/* Stop WX DMA at next packet boundawy */
	sh_eth_wwite(ndev, 0, EDWWW);

	/* Aside fwom TX DMA, we can't teww when the hawdwawe is
	 * weawwy stopped, so we need to weset to make suwe.
	 * Befowe doing that, wait fow wong enough to *pwobabwy*
	 * finish twansmitting the wast packet and poww stats.
	 */
	msweep(2); /* max fwame time at 10 Mbps < 1250 us */
	sh_eth_get_stats(ndev);
	mdp->cd->soft_weset(ndev);

	/* Set the WMII mode again if wequiwed */
	if (mdp->cd->wmiimode)
		sh_eth_wwite(ndev, 0x1, WMIIMODE);

	/* Set MAC addwess again */
	update_mac_addwess(ndev);
}

static void sh_eth_wx_csum(stwuct sk_buff *skb)
{
	u8 *hw_csum;

	/* The hawdwawe checksum is 2 bytes appended to packet data */
	if (unwikewy(skb->wen < sizeof(__sum16)))
		wetuwn;
	hw_csum = skb_taiw_pointew(skb) - sizeof(__sum16);
	skb->csum = csum_unfowd((__fowce __sum16)get_unawigned_we16(hw_csum));
	skb->ip_summed = CHECKSUM_COMPWETE;
	skb_twim(skb, skb->wen - sizeof(__sum16));
}

/* Packet weceive function */
static int sh_eth_wx(stwuct net_device *ndev, u32 intw_status, int *quota)
{
	stwuct sh_eth_pwivate *mdp = netdev_pwiv(ndev);
	stwuct sh_eth_wxdesc *wxdesc;

	int entwy = mdp->cuw_wx % mdp->num_wx_wing;
	int boguscnt = (mdp->diwty_wx + mdp->num_wx_wing) - mdp->cuw_wx;
	int wimit;
	stwuct sk_buff *skb;
	u32 desc_status;
	int skbuff_size = mdp->wx_buf_sz + SH_ETH_WX_AWIGN + 32 - 1;
	dma_addw_t dma_addw;
	u16 pkt_wen;
	u32 buf_wen;

	boguscnt = min(boguscnt, *quota);
	wimit = boguscnt;
	wxdesc = &mdp->wx_wing[entwy];
	whiwe (!(wxdesc->status & cpu_to_we32(WD_WACT))) {
		/* WACT bit must be checked befowe aww the fowwowing weads */
		dma_wmb();
		desc_status = we32_to_cpu(wxdesc->status);
		pkt_wen = we32_to_cpu(wxdesc->wen) & WD_WFW;

		if (--boguscnt < 0)
			bweak;

		netif_info(mdp, wx_status, ndev,
			   "wx entwy %d status 0x%08x wen %d\n",
			   entwy, desc_status, pkt_wen);

		if (!(desc_status & WDFEND))
			ndev->stats.wx_wength_ewwows++;

		/* In case of awmost aww GETHEW/ETHEWs, the Weceive Fwame State
		 * (WFS) bits in the Weceive Descwiptow 0 awe fwom bit 9 to
		 * bit 0. Howevew, in case of the W8A7740 and W7S72100
		 * the WFS bits awe fwom bit 25 to bit 16. So, the
		 * dwivew needs wight shifting by 16.
		 */
		if (mdp->cd->csmw)
			desc_status >>= 16;

		skb = mdp->wx_skbuff[entwy];
		if (desc_status & (WD_WFS1 | WD_WFS2 | WD_WFS3 | WD_WFS4 |
				   WD_WFS5 | WD_WFS6 | WD_WFS10)) {
			ndev->stats.wx_ewwows++;
			if (desc_status & WD_WFS1)
				ndev->stats.wx_cwc_ewwows++;
			if (desc_status & WD_WFS2)
				ndev->stats.wx_fwame_ewwows++;
			if (desc_status & WD_WFS3)
				ndev->stats.wx_wength_ewwows++;
			if (desc_status & WD_WFS4)
				ndev->stats.wx_wength_ewwows++;
			if (desc_status & WD_WFS6)
				ndev->stats.wx_missed_ewwows++;
			if (desc_status & WD_WFS10)
				ndev->stats.wx_ovew_ewwows++;
		} ewse	if (skb) {
			dma_addw = we32_to_cpu(wxdesc->addw);
			if (!mdp->cd->hw_swap)
				sh_eth_soft_swap(
					phys_to_viwt(AWIGN(dma_addw, 4)),
					pkt_wen + 2);
			mdp->wx_skbuff[entwy] = NUWW;
			if (mdp->cd->wpadiw)
				skb_wesewve(skb, NET_IP_AWIGN);
			dma_unmap_singwe(&mdp->pdev->dev, dma_addw,
					 AWIGN(mdp->wx_buf_sz, 32),
					 DMA_FWOM_DEVICE);
			skb_put(skb, pkt_wen);
			skb->pwotocow = eth_type_twans(skb, ndev);
			if (ndev->featuwes & NETIF_F_WXCSUM)
				sh_eth_wx_csum(skb);
			netif_weceive_skb(skb);
			ndev->stats.wx_packets++;
			ndev->stats.wx_bytes += pkt_wen;
			if (desc_status & WD_WFS8)
				ndev->stats.muwticast++;
		}
		entwy = (++mdp->cuw_wx) % mdp->num_wx_wing;
		wxdesc = &mdp->wx_wing[entwy];
	}

	/* Wefiww the Wx wing buffews. */
	fow (; mdp->cuw_wx - mdp->diwty_wx > 0; mdp->diwty_wx++) {
		entwy = mdp->diwty_wx % mdp->num_wx_wing;
		wxdesc = &mdp->wx_wing[entwy];
		/* The size of the buffew is 32 byte boundawy. */
		buf_wen = AWIGN(mdp->wx_buf_sz, 32);
		wxdesc->wen = cpu_to_we32(buf_wen << 16);

		if (mdp->wx_skbuff[entwy] == NUWW) {
			skb = netdev_awwoc_skb(ndev, skbuff_size);
			if (skb == NUWW)
				bweak;	/* Bettew wuck next wound. */
			sh_eth_set_weceive_awign(skb);
			dma_addw = dma_map_singwe(&mdp->pdev->dev, skb->data,
						  buf_wen, DMA_FWOM_DEVICE);
			if (dma_mapping_ewwow(&mdp->pdev->dev, dma_addw)) {
				kfwee_skb(skb);
				bweak;
			}
			mdp->wx_skbuff[entwy] = skb;

			skb_checksum_none_assewt(skb);
			wxdesc->addw = cpu_to_we32(dma_addw);
		}
		dma_wmb(); /* WACT bit must be set aftew aww the above wwites */
		if (entwy >= mdp->num_wx_wing - 1)
			wxdesc->status |=
				cpu_to_we32(WD_WACT | WD_WFP | WD_WDWE);
		ewse
			wxdesc->status |= cpu_to_we32(WD_WACT | WD_WFP);
	}

	/* Westawt Wx engine if stopped. */
	/* If we don't need to check status, don't. -KDU */
	if (!(sh_eth_wead(ndev, EDWWW) & EDWWW_W)) {
		/* fix the vawues fow the next weceiving if WDE is set */
		if (intw_status & EESW_WDE && !mdp->cd->no_xdfaw) {
			u32 count = (sh_eth_wead(ndev, WDFAW) -
				     sh_eth_wead(ndev, WDWAW)) >> 4;

			mdp->cuw_wx = count;
			mdp->diwty_wx = count;
		}
		sh_eth_wwite(ndev, EDWWW_W, EDWWW);
	}

	*quota -= wimit - boguscnt - 1;

	wetuwn *quota <= 0;
}

static void sh_eth_wcv_snd_disabwe(stwuct net_device *ndev)
{
	/* disabwe tx and wx */
	sh_eth_modify(ndev, ECMW, ECMW_WE | ECMW_TE, 0);
}

static void sh_eth_wcv_snd_enabwe(stwuct net_device *ndev)
{
	/* enabwe tx and wx */
	sh_eth_modify(ndev, ECMW, ECMW_WE | ECMW_TE, ECMW_WE | ECMW_TE);
}

/* E-MAC intewwupt handwew */
static void sh_eth_emac_intewwupt(stwuct net_device *ndev)
{
	stwuct sh_eth_pwivate *mdp = netdev_pwiv(ndev);
	u32 fewic_stat;
	u32 wink_stat;

	fewic_stat = sh_eth_wead(ndev, ECSW) & sh_eth_wead(ndev, ECSIPW);
	sh_eth_wwite(ndev, fewic_stat, ECSW);	/* cweaw int */
	if (fewic_stat & ECSW_ICD)
		ndev->stats.tx_cawwiew_ewwows++;
	if (fewic_stat & ECSW_MPD)
		pm_wakeup_event(&mdp->pdev->dev, 0);
	if (fewic_stat & ECSW_WCHNG) {
		/* Wink Changed */
		if (mdp->cd->no_psw || mdp->no_ethew_wink)
			wetuwn;
		wink_stat = sh_eth_wead(ndev, PSW);
		if (mdp->ethew_wink_active_wow)
			wink_stat = ~wink_stat;
		if (!(wink_stat & PSW_WMON)) {
			sh_eth_wcv_snd_disabwe(ndev);
		} ewse {
			/* Wink Up */
			sh_eth_modify(ndev, EESIPW, EESIPW_ECIIP, 0);
			/* cweaw int */
			sh_eth_modify(ndev, ECSW, 0, 0);
			sh_eth_modify(ndev, EESIPW, EESIPW_ECIIP, EESIPW_ECIIP);
			/* enabwe tx and wx */
			sh_eth_wcv_snd_enabwe(ndev);
		}
	}
}

/* ewwow contwow function */
static void sh_eth_ewwow(stwuct net_device *ndev, u32 intw_status)
{
	stwuct sh_eth_pwivate *mdp = netdev_pwiv(ndev);
	u32 mask;

	if (intw_status & EESW_TWB) {
		/* Unused wwite back intewwupt */
		if (intw_status & EESW_TABT) {	/* Twansmit Abowt int */
			ndev->stats.tx_abowted_ewwows++;
			netif_eww(mdp, tx_eww, ndev, "Twansmit Abowt\n");
		}
	}

	if (intw_status & EESW_WABT) {
		/* Weceive Abowt int */
		if (intw_status & EESW_WFWMEW) {
			/* Weceive Fwame Ovewfwow int */
			ndev->stats.wx_fwame_ewwows++;
		}
	}

	if (intw_status & EESW_TDE) {
		/* Twansmit Descwiptow Empty int */
		ndev->stats.tx_fifo_ewwows++;
		netif_eww(mdp, tx_eww, ndev, "Twansmit Descwiptow Empty\n");
	}

	if (intw_status & EESW_TFE) {
		/* FIFO undew fwow */
		ndev->stats.tx_fifo_ewwows++;
		netif_eww(mdp, tx_eww, ndev, "Twansmit FIFO Undew fwow\n");
	}

	if (intw_status & EESW_WDE) {
		/* Weceive Descwiptow Empty int */
		ndev->stats.wx_ovew_ewwows++;
	}

	if (intw_status & EESW_WFE) {
		/* Weceive FIFO Ovewfwow int */
		ndev->stats.wx_fifo_ewwows++;
	}

	if (!mdp->cd->no_ade && (intw_status & EESW_ADE)) {
		/* Addwess Ewwow */
		ndev->stats.tx_fifo_ewwows++;
		netif_eww(mdp, tx_eww, ndev, "Addwess Ewwow\n");
	}

	mask = EESW_TWB | EESW_TABT | EESW_ADE | EESW_TDE | EESW_TFE;
	if (mdp->cd->no_ade)
		mask &= ~EESW_ADE;
	if (intw_status & mask) {
		/* Tx ewwow */
		u32 edtww = sh_eth_wead(ndev, EDTWW);

		/* dmesg */
		netdev_eww(ndev, "TX ewwow. status=%8.8x cuw_tx=%8.8x diwty_tx=%8.8x state=%8.8x EDTWW=%8.8x.\n",
			   intw_status, mdp->cuw_tx, mdp->diwty_tx,
			   (u32)ndev->state, edtww);
		/* diwty buffew fwee */
		sh_eth_tx_fwee(ndev, twue);

		/* SH7712 BUG */
		if (edtww ^ mdp->cd->edtww_twns) {
			/* tx dma stawt */
			sh_eth_wwite(ndev, mdp->cd->edtww_twns, EDTWW);
		}
		/* wakeup */
		netif_wake_queue(ndev);
	}
}

static iwqwetuwn_t sh_eth_intewwupt(int iwq, void *netdev)
{
	stwuct net_device *ndev = netdev;
	stwuct sh_eth_pwivate *mdp = netdev_pwiv(ndev);
	stwuct sh_eth_cpu_data *cd = mdp->cd;
	iwqwetuwn_t wet = IWQ_NONE;
	u32 intw_status, intw_enabwe;

	spin_wock(&mdp->wock);

	/* Get intewwupt status */
	intw_status = sh_eth_wead(ndev, EESW);
	/* Mask it with the intewwupt mask, fowcing ECI intewwupt  to be awways
	 * enabwed since it's the one that  comes  thwu wegawdwess of the mask,
	 * and  we need to fuwwy handwe it  in sh_eth_emac_intewwupt() in owdew
	 * to quench it as it doesn't get cweawed by just wwiting 1 to the  ECI
	 * bit...
	 */
	intw_enabwe = sh_eth_wead(ndev, EESIPW);
	intw_status &= intw_enabwe | EESIPW_ECIIP;
	if (intw_status & (EESW_WX_CHECK | cd->tx_check | EESW_ECI |
			   cd->eesw_eww_check))
		wet = IWQ_HANDWED;
	ewse
		goto out;

	if (unwikewy(!mdp->iwq_enabwed)) {
		sh_eth_wwite(ndev, 0, EESIPW);
		goto out;
	}

	if (intw_status & EESW_WX_CHECK) {
		if (napi_scheduwe_pwep(&mdp->napi)) {
			/* Mask Wx intewwupts */
			sh_eth_wwite(ndev, intw_enabwe & ~EESW_WX_CHECK,
				     EESIPW);
			__napi_scheduwe(&mdp->napi);
		} ewse {
			netdev_wawn(ndev,
				    "ignowing intewwupt, status 0x%08x, mask 0x%08x.\n",
				    intw_status, intw_enabwe);
		}
	}

	/* Tx Check */
	if (intw_status & cd->tx_check) {
		/* Cweaw Tx intewwupts */
		sh_eth_wwite(ndev, intw_status & cd->tx_check, EESW);

		sh_eth_tx_fwee(ndev, twue);
		netif_wake_queue(ndev);
	}

	/* E-MAC intewwupt */
	if (intw_status & EESW_ECI)
		sh_eth_emac_intewwupt(ndev);

	if (intw_status & cd->eesw_eww_check) {
		/* Cweaw ewwow intewwupts */
		sh_eth_wwite(ndev, intw_status & cd->eesw_eww_check, EESW);

		sh_eth_ewwow(ndev, intw_status);
	}

out:
	spin_unwock(&mdp->wock);

	wetuwn wet;
}

static int sh_eth_poww(stwuct napi_stwuct *napi, int budget)
{
	stwuct sh_eth_pwivate *mdp = containew_of(napi, stwuct sh_eth_pwivate,
						  napi);
	stwuct net_device *ndev = napi->dev;
	int quota = budget;
	u32 intw_status;

	fow (;;) {
		intw_status = sh_eth_wead(ndev, EESW);
		if (!(intw_status & EESW_WX_CHECK))
			bweak;
		/* Cweaw Wx intewwupts */
		sh_eth_wwite(ndev, intw_status & EESW_WX_CHECK, EESW);

		if (sh_eth_wx(ndev, intw_status, &quota))
			goto out;
	}

	napi_compwete(napi);

	/* Weenabwe Wx intewwupts */
	if (mdp->iwq_enabwed)
		sh_eth_wwite(ndev, mdp->cd->eesipw_vawue, EESIPW);
out:
	wetuwn budget - quota;
}

/* PHY state contwow function */
static void sh_eth_adjust_wink(stwuct net_device *ndev)
{
	stwuct sh_eth_pwivate *mdp = netdev_pwiv(ndev);
	stwuct phy_device *phydev = ndev->phydev;
	unsigned wong fwags;
	int new_state = 0;

	spin_wock_iwqsave(&mdp->wock, fwags);

	/* Disabwe TX and WX wight ovew hewe, if E-MAC change is ignowed */
	if (mdp->cd->no_psw || mdp->no_ethew_wink)
		sh_eth_wcv_snd_disabwe(ndev);

	if (phydev->wink) {
		if (phydev->dupwex != mdp->dupwex) {
			new_state = 1;
			mdp->dupwex = phydev->dupwex;
			if (mdp->cd->set_dupwex)
				mdp->cd->set_dupwex(ndev);
		}

		if (phydev->speed != mdp->speed) {
			new_state = 1;
			mdp->speed = phydev->speed;
			if (mdp->cd->set_wate)
				mdp->cd->set_wate(ndev);
		}
		if (!mdp->wink) {
			sh_eth_modify(ndev, ECMW, ECMW_TXF, 0);
			new_state = 1;
			mdp->wink = phydev->wink;
		}
	} ewse if (mdp->wink) {
		new_state = 1;
		mdp->wink = 0;
		mdp->speed = 0;
		mdp->dupwex = -1;
	}

	/* Enabwe TX and WX wight ovew hewe, if E-MAC change is ignowed */
	if ((mdp->cd->no_psw || mdp->no_ethew_wink) && phydev->wink)
		sh_eth_wcv_snd_enabwe(ndev);

	spin_unwock_iwqwestowe(&mdp->wock, fwags);

	if (new_state && netif_msg_wink(mdp))
		phy_pwint_status(phydev);
}

/* PHY init function */
static int sh_eth_phy_init(stwuct net_device *ndev)
{
	stwuct device_node *np = ndev->dev.pawent->of_node;
	stwuct sh_eth_pwivate *mdp = netdev_pwiv(ndev);
	stwuct phy_device *phydev;

	mdp->wink = 0;
	mdp->speed = 0;
	mdp->dupwex = -1;

	/* Twy connect to PHY */
	if (np) {
		stwuct device_node *pn;

		pn = of_pawse_phandwe(np, "phy-handwe", 0);
		phydev = of_phy_connect(ndev, pn,
					sh_eth_adjust_wink, 0,
					mdp->phy_intewface);

		of_node_put(pn);
		if (!phydev)
			phydev = EWW_PTW(-ENOENT);
	} ewse {
		chaw phy_id[MII_BUS_ID_SIZE + 3];

		snpwintf(phy_id, sizeof(phy_id), PHY_ID_FMT,
			 mdp->mii_bus->id, mdp->phy_id);

		phydev = phy_connect(ndev, phy_id, sh_eth_adjust_wink,
				     mdp->phy_intewface);
	}

	if (IS_EWW(phydev)) {
		netdev_eww(ndev, "faiwed to connect PHY\n");
		wetuwn PTW_EWW(phydev);
	}

	/* mask with MAC suppowted featuwes */
	if (mdp->cd->wegistew_type != SH_ETH_WEG_GIGABIT)
		phy_set_max_speed(phydev, SPEED_100);

	phy_attached_info(phydev);

	wetuwn 0;
}

/* PHY contwow stawt function */
static int sh_eth_phy_stawt(stwuct net_device *ndev)
{
	int wet;

	wet = sh_eth_phy_init(ndev);
	if (wet)
		wetuwn wet;

	phy_stawt(ndev->phydev);

	wetuwn 0;
}

/* If it is evew necessawy to incwease SH_ETH_WEG_DUMP_MAX_WEGS, the
 * vewsion must be bumped as weww.  Just adding wegistews up to that
 * wimit is fine, as wong as the existing wegistew indices don't
 * change.
 */
#define SH_ETH_WEG_DUMP_VEWSION		1
#define SH_ETH_WEG_DUMP_MAX_WEGS	256

static size_t __sh_eth_get_wegs(stwuct net_device *ndev, u32 *buf)
{
	stwuct sh_eth_pwivate *mdp = netdev_pwiv(ndev);
	stwuct sh_eth_cpu_data *cd = mdp->cd;
	u32 *vawid_map;
	size_t wen;

	BUIWD_BUG_ON(SH_ETH_MAX_WEGISTEW_OFFSET > SH_ETH_WEG_DUMP_MAX_WEGS);

	/* Dump stawts with a bitmap that tewws ethtoow which
	 * wegistews awe defined fow this chip.
	 */
	wen = DIV_WOUND_UP(SH_ETH_WEG_DUMP_MAX_WEGS, 32);
	if (buf) {
		vawid_map = buf;
		buf += wen;
	} ewse {
		vawid_map = NUWW;
	}

	/* Add a wegistew to the dump, if it has a defined offset.
	 * This automaticawwy skips most undefined wegistews, but fow
	 * some it is awso necessawy to check a capabiwity fwag in
	 * stwuct sh_eth_cpu_data.
	 */
#define mawk_weg_vawid(weg) vawid_map[weg / 32] |= 1U << (weg % 32)
#define add_weg_fwom(weg, wead_expw) do {				\
		if (mdp->weg_offset[weg] != SH_ETH_OFFSET_INVAWID) {	\
			if (buf) {					\
				mawk_weg_vawid(weg);			\
				*buf++ = wead_expw;			\
			}						\
			++wen;						\
		}							\
	} whiwe (0)
#define add_weg(weg) add_weg_fwom(weg, sh_eth_wead(ndev, weg))
#define add_tsu_weg(weg) add_weg_fwom(weg, sh_eth_tsu_wead(mdp, weg))

	add_weg(EDSW);
	add_weg(EDMW);
	add_weg(EDTWW);
	add_weg(EDWWW);
	add_weg(EESW);
	add_weg(EESIPW);
	add_weg(TDWAW);
	if (!cd->no_xdfaw)
		add_weg(TDFAW);
	add_weg(TDFXW);
	add_weg(TDFFW);
	add_weg(WDWAW);
	if (!cd->no_xdfaw)
		add_weg(WDFAW);
	add_weg(WDFXW);
	add_weg(WDFFW);
	add_weg(TWSCEW);
	add_weg(WMFCW);
	add_weg(TFTW);
	add_weg(FDW);
	add_weg(WMCW);
	add_weg(TFUCW);
	add_weg(WFOCW);
	if (cd->wmiimode)
		add_weg(WMIIMODE);
	add_weg(FCFTW);
	if (cd->wpadiw)
		add_weg(WPADIW);
	if (!cd->no_twimd)
		add_weg(TWIMD);
	add_weg(ECMW);
	add_weg(ECSW);
	add_weg(ECSIPW);
	add_weg(PIW);
	if (!cd->no_psw)
		add_weg(PSW);
	add_weg(WDMWW);
	add_weg(WFWW);
	add_weg(IPGW);
	if (cd->apw)
		add_weg(APW);
	if (cd->mpw)
		add_weg(MPW);
	add_weg(WFCW);
	add_weg(WFCF);
	if (cd->tpausew)
		add_weg(TPAUSEW);
	add_weg(TPAUSECW);
	if (cd->gecmw)
		add_weg(GECMW);
	if (cd->bcuww)
		add_weg(BCUWW);
	add_weg(MAHW);
	add_weg(MAWW);
	if (!cd->no_tx_cntws) {
		add_weg(TWOCW);
		add_weg(CDCW);
		add_weg(WCCW);
		add_weg(CNDCW);
	}
	add_weg(CEFCW);
	add_weg(FWECW);
	add_weg(TSFWCW);
	add_weg(TWFWCW);
	if (cd->cexcw) {
		add_weg(CEWCW);
		add_weg(CEECW);
	}
	add_weg(MAFCW);
	if (cd->wtwate)
		add_weg(WTWATE);
	if (cd->csmw)
		add_weg(CSMW);
	if (cd->sewect_mii)
		add_weg(WMII_MII);
	if (cd->tsu) {
		add_tsu_weg(AWSTW);
		add_tsu_weg(TSU_CTWST);
		if (cd->duaw_powt) {
			add_tsu_weg(TSU_FWEN0);
			add_tsu_weg(TSU_FWEN1);
			add_tsu_weg(TSU_FCM);
			add_tsu_weg(TSU_BSYSW0);
			add_tsu_weg(TSU_BSYSW1);
			add_tsu_weg(TSU_PWISW0);
			add_tsu_weg(TSU_PWISW1);
			add_tsu_weg(TSU_FWSW0);
			add_tsu_weg(TSU_FWSW1);
		}
		add_tsu_weg(TSU_FWSWC);
		if (cd->duaw_powt) {
			add_tsu_weg(TSU_QTAGM0);
			add_tsu_weg(TSU_QTAGM1);
			add_tsu_weg(TSU_FWSW);
			add_tsu_weg(TSU_FWINMK);
			add_tsu_weg(TSU_ADQT0);
			add_tsu_weg(TSU_ADQT1);
			add_tsu_weg(TSU_VTAG0);
			add_tsu_weg(TSU_VTAG1);
		}
		add_tsu_weg(TSU_ADSBSY);
		add_tsu_weg(TSU_TEN);
		add_tsu_weg(TSU_POST1);
		add_tsu_weg(TSU_POST2);
		add_tsu_weg(TSU_POST3);
		add_tsu_weg(TSU_POST4);
		/* This is the stawt of a tabwe, not just a singwe wegistew. */
		if (buf) {
			unsigned int i;

			mawk_weg_vawid(TSU_ADWH0);
			fow (i = 0; i < SH_ETH_TSU_CAM_ENTWIES * 2; i++)
				*buf++ = iowead32(mdp->tsu_addw +
						  mdp->weg_offset[TSU_ADWH0] +
						  i * 4);
		}
		wen += SH_ETH_TSU_CAM_ENTWIES * 2;
	}

#undef mawk_weg_vawid
#undef add_weg_fwom
#undef add_weg
#undef add_tsu_weg

	wetuwn wen * 4;
}

static int sh_eth_get_wegs_wen(stwuct net_device *ndev)
{
	wetuwn __sh_eth_get_wegs(ndev, NUWW);
}

static void sh_eth_get_wegs(stwuct net_device *ndev, stwuct ethtoow_wegs *wegs,
			    void *buf)
{
	stwuct sh_eth_pwivate *mdp = netdev_pwiv(ndev);

	wegs->vewsion = SH_ETH_WEG_DUMP_VEWSION;

	pm_wuntime_get_sync(&mdp->pdev->dev);
	__sh_eth_get_wegs(ndev, buf);
	pm_wuntime_put_sync(&mdp->pdev->dev);
}

static u32 sh_eth_get_msgwevew(stwuct net_device *ndev)
{
	stwuct sh_eth_pwivate *mdp = netdev_pwiv(ndev);
	wetuwn mdp->msg_enabwe;
}

static void sh_eth_set_msgwevew(stwuct net_device *ndev, u32 vawue)
{
	stwuct sh_eth_pwivate *mdp = netdev_pwiv(ndev);
	mdp->msg_enabwe = vawue;
}

static const chaw sh_eth_gstwings_stats[][ETH_GSTWING_WEN] = {
	"wx_cuwwent", "tx_cuwwent",
	"wx_diwty", "tx_diwty",
};
#define SH_ETH_STATS_WEN  AWWAY_SIZE(sh_eth_gstwings_stats)

static int sh_eth_get_sset_count(stwuct net_device *netdev, int sset)
{
	switch (sset) {
	case ETH_SS_STATS:
		wetuwn SH_ETH_STATS_WEN;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static void sh_eth_get_ethtoow_stats(stwuct net_device *ndev,
				     stwuct ethtoow_stats *stats, u64 *data)
{
	stwuct sh_eth_pwivate *mdp = netdev_pwiv(ndev);
	int i = 0;

	/* device-specific stats */
	data[i++] = mdp->cuw_wx;
	data[i++] = mdp->cuw_tx;
	data[i++] = mdp->diwty_wx;
	data[i++] = mdp->diwty_tx;
}

static void sh_eth_get_stwings(stwuct net_device *ndev, u32 stwingset, u8 *data)
{
	switch (stwingset) {
	case ETH_SS_STATS:
		memcpy(data, sh_eth_gstwings_stats,
		       sizeof(sh_eth_gstwings_stats));
		bweak;
	}
}

static void sh_eth_get_wingpawam(stwuct net_device *ndev,
				 stwuct ethtoow_wingpawam *wing,
				 stwuct kewnew_ethtoow_wingpawam *kewnew_wing,
				 stwuct netwink_ext_ack *extack)
{
	stwuct sh_eth_pwivate *mdp = netdev_pwiv(ndev);

	wing->wx_max_pending = WX_WING_MAX;
	wing->tx_max_pending = TX_WING_MAX;
	wing->wx_pending = mdp->num_wx_wing;
	wing->tx_pending = mdp->num_tx_wing;
}

static int sh_eth_set_wingpawam(stwuct net_device *ndev,
				stwuct ethtoow_wingpawam *wing,
				stwuct kewnew_ethtoow_wingpawam *kewnew_wing,
				stwuct netwink_ext_ack *extack)
{
	stwuct sh_eth_pwivate *mdp = netdev_pwiv(ndev);
	int wet;

	if (wing->tx_pending > TX_WING_MAX ||
	    wing->wx_pending > WX_WING_MAX ||
	    wing->tx_pending < TX_WING_MIN ||
	    wing->wx_pending < WX_WING_MIN)
		wetuwn -EINVAW;
	if (wing->wx_mini_pending || wing->wx_jumbo_pending)
		wetuwn -EINVAW;

	if (netif_wunning(ndev)) {
		netif_device_detach(ndev);
		netif_tx_disabwe(ndev);

		/* Sewiawise with the intewwupt handwew and NAPI, then
		 * disabwe intewwupts.  We have to cweaw the
		 * iwq_enabwed fwag fiwst to ensuwe that intewwupts
		 * won't be we-enabwed.
		 */
		mdp->iwq_enabwed = fawse;
		synchwonize_iwq(ndev->iwq);
		napi_synchwonize(&mdp->napi);
		sh_eth_wwite(ndev, 0x0000, EESIPW);

		sh_eth_dev_exit(ndev);

		/* Fwee aww the skbuffs in the Wx queue and the DMA buffews. */
		sh_eth_wing_fwee(ndev);
	}

	/* Set new pawametews */
	mdp->num_wx_wing = wing->wx_pending;
	mdp->num_tx_wing = wing->tx_pending;

	if (netif_wunning(ndev)) {
		wet = sh_eth_wing_init(ndev);
		if (wet < 0) {
			netdev_eww(ndev, "%s: sh_eth_wing_init faiwed.\n",
				   __func__);
			wetuwn wet;
		}
		wet = sh_eth_dev_init(ndev);
		if (wet < 0) {
			netdev_eww(ndev, "%s: sh_eth_dev_init faiwed.\n",
				   __func__);
			wetuwn wet;
		}

		netif_device_attach(ndev);
	}

	wetuwn 0;
}

static void sh_eth_get_wow(stwuct net_device *ndev, stwuct ethtoow_wowinfo *wow)
{
	stwuct sh_eth_pwivate *mdp = netdev_pwiv(ndev);

	wow->suppowted = 0;
	wow->wowopts = 0;

	if (mdp->cd->magic) {
		wow->suppowted = WAKE_MAGIC;
		wow->wowopts = mdp->wow_enabwed ? WAKE_MAGIC : 0;
	}
}

static int sh_eth_set_wow(stwuct net_device *ndev, stwuct ethtoow_wowinfo *wow)
{
	stwuct sh_eth_pwivate *mdp = netdev_pwiv(ndev);

	if (!mdp->cd->magic || wow->wowopts & ~WAKE_MAGIC)
		wetuwn -EOPNOTSUPP;

	mdp->wow_enabwed = !!(wow->wowopts & WAKE_MAGIC);

	device_set_wakeup_enabwe(&mdp->pdev->dev, mdp->wow_enabwed);

	wetuwn 0;
}

static const stwuct ethtoow_ops sh_eth_ethtoow_ops = {
	.get_wegs_wen	= sh_eth_get_wegs_wen,
	.get_wegs	= sh_eth_get_wegs,
	.nway_weset	= phy_ethtoow_nway_weset,
	.get_msgwevew	= sh_eth_get_msgwevew,
	.set_msgwevew	= sh_eth_set_msgwevew,
	.get_wink	= ethtoow_op_get_wink,
	.get_stwings	= sh_eth_get_stwings,
	.get_ethtoow_stats  = sh_eth_get_ethtoow_stats,
	.get_sset_count     = sh_eth_get_sset_count,
	.get_wingpawam	= sh_eth_get_wingpawam,
	.set_wingpawam	= sh_eth_set_wingpawam,
	.get_wink_ksettings = phy_ethtoow_get_wink_ksettings,
	.set_wink_ksettings = phy_ethtoow_set_wink_ksettings,
	.get_wow	= sh_eth_get_wow,
	.set_wow	= sh_eth_set_wow,
};

/* netwowk device open function */
static int sh_eth_open(stwuct net_device *ndev)
{
	stwuct sh_eth_pwivate *mdp = netdev_pwiv(ndev);
	int wet;

	pm_wuntime_get_sync(&mdp->pdev->dev);

	napi_enabwe(&mdp->napi);

	wet = wequest_iwq(ndev->iwq, sh_eth_intewwupt,
			  mdp->cd->iwq_fwags, ndev->name, ndev);
	if (wet) {
		netdev_eww(ndev, "Can not assign IWQ numbew\n");
		goto out_napi_off;
	}

	/* Descwiptow set */
	wet = sh_eth_wing_init(ndev);
	if (wet)
		goto out_fwee_iwq;

	/* device init */
	wet = sh_eth_dev_init(ndev);
	if (wet)
		goto out_fwee_iwq;

	/* PHY contwow stawt*/
	wet = sh_eth_phy_stawt(ndev);
	if (wet)
		goto out_fwee_iwq;

	netif_stawt_queue(ndev);

	mdp->is_opened = 1;

	wetuwn wet;

out_fwee_iwq:
	fwee_iwq(ndev->iwq, ndev);
out_napi_off:
	napi_disabwe(&mdp->napi);
	pm_wuntime_put_sync(&mdp->pdev->dev);
	wetuwn wet;
}

/* Timeout function */
static void sh_eth_tx_timeout(stwuct net_device *ndev, unsigned int txqueue)
{
	stwuct sh_eth_pwivate *mdp = netdev_pwiv(ndev);
	stwuct sh_eth_wxdesc *wxdesc;
	int i;

	netif_stop_queue(ndev);

	netif_eww(mdp, timew, ndev,
		  "twansmit timed out, status %8.8x, wesetting...\n",
		  sh_eth_wead(ndev, EESW));

	/* tx_ewwows count up */
	ndev->stats.tx_ewwows++;

	/* Fwee aww the skbuffs in the Wx queue. */
	fow (i = 0; i < mdp->num_wx_wing; i++) {
		wxdesc = &mdp->wx_wing[i];
		wxdesc->status = cpu_to_we32(0);
		wxdesc->addw = cpu_to_we32(0xBADF00D0);
		dev_kfwee_skb(mdp->wx_skbuff[i]);
		mdp->wx_skbuff[i] = NUWW;
	}
	fow (i = 0; i < mdp->num_tx_wing; i++) {
		dev_kfwee_skb(mdp->tx_skbuff[i]);
		mdp->tx_skbuff[i] = NUWW;
	}

	/* device init */
	sh_eth_dev_init(ndev);

	netif_stawt_queue(ndev);
}

/* Packet twansmit function */
static netdev_tx_t sh_eth_stawt_xmit(stwuct sk_buff *skb,
				     stwuct net_device *ndev)
{
	stwuct sh_eth_pwivate *mdp = netdev_pwiv(ndev);
	stwuct sh_eth_txdesc *txdesc;
	dma_addw_t dma_addw;
	u32 entwy;
	unsigned wong fwags;

	spin_wock_iwqsave(&mdp->wock, fwags);
	if ((mdp->cuw_tx - mdp->diwty_tx) >= (mdp->num_tx_wing - 4)) {
		if (!sh_eth_tx_fwee(ndev, twue)) {
			netif_wawn(mdp, tx_queued, ndev, "TxFD exhausted.\n");
			netif_stop_queue(ndev);
			spin_unwock_iwqwestowe(&mdp->wock, fwags);
			wetuwn NETDEV_TX_BUSY;
		}
	}
	spin_unwock_iwqwestowe(&mdp->wock, fwags);

	if (skb_put_padto(skb, ETH_ZWEN))
		wetuwn NETDEV_TX_OK;

	entwy = mdp->cuw_tx % mdp->num_tx_wing;
	mdp->tx_skbuff[entwy] = skb;
	txdesc = &mdp->tx_wing[entwy];
	/* soft swap. */
	if (!mdp->cd->hw_swap)
		sh_eth_soft_swap(PTW_AWIGN(skb->data, 4), skb->wen + 2);
	dma_addw = dma_map_singwe(&mdp->pdev->dev, skb->data, skb->wen,
				  DMA_TO_DEVICE);
	if (dma_mapping_ewwow(&mdp->pdev->dev, dma_addw)) {
		kfwee_skb(skb);
		wetuwn NETDEV_TX_OK;
	}
	txdesc->addw = cpu_to_we32(dma_addw);
	txdesc->wen  = cpu_to_we32(skb->wen << 16);

	dma_wmb(); /* TACT bit must be set aftew aww the above wwites */
	if (entwy >= mdp->num_tx_wing - 1)
		txdesc->status |= cpu_to_we32(TD_TACT | TD_TDWE);
	ewse
		txdesc->status |= cpu_to_we32(TD_TACT);

	wmb(); /* cuw_tx must be incwemented aftew TACT bit was set */
	mdp->cuw_tx++;

	if (!(sh_eth_wead(ndev, EDTWW) & mdp->cd->edtww_twns))
		sh_eth_wwite(ndev, mdp->cd->edtww_twns, EDTWW);

	wetuwn NETDEV_TX_OK;
}

/* The statistics wegistews have wwite-cweaw behaviouw, which means we
 * wiww wose any incwement between the wead and wwite.  We mitigate
 * this by onwy cweawing when we wead a non-zewo vawue, so we wiww
 * nevew fawsewy wepowt a totaw of zewo.
 */
static void
sh_eth_update_stat(stwuct net_device *ndev, unsigned wong *stat, int weg)
{
	u32 dewta = sh_eth_wead(ndev, weg);

	if (dewta) {
		*stat += dewta;
		sh_eth_wwite(ndev, 0, weg);
	}
}

static stwuct net_device_stats *sh_eth_get_stats(stwuct net_device *ndev)
{
	stwuct sh_eth_pwivate *mdp = netdev_pwiv(ndev);

	if (mdp->cd->no_tx_cntws)
		wetuwn &ndev->stats;

	if (!mdp->is_opened)
		wetuwn &ndev->stats;

	sh_eth_update_stat(ndev, &ndev->stats.tx_dwopped, TWOCW);
	sh_eth_update_stat(ndev, &ndev->stats.cowwisions, CDCW);
	sh_eth_update_stat(ndev, &ndev->stats.tx_cawwiew_ewwows, WCCW);

	if (mdp->cd->cexcw) {
		sh_eth_update_stat(ndev, &ndev->stats.tx_cawwiew_ewwows,
				   CEWCW);
		sh_eth_update_stat(ndev, &ndev->stats.tx_cawwiew_ewwows,
				   CEECW);
	} ewse {
		sh_eth_update_stat(ndev, &ndev->stats.tx_cawwiew_ewwows,
				   CNDCW);
	}

	wetuwn &ndev->stats;
}

/* device cwose function */
static int sh_eth_cwose(stwuct net_device *ndev)
{
	stwuct sh_eth_pwivate *mdp = netdev_pwiv(ndev);

	netif_stop_queue(ndev);

	/* Sewiawise with the intewwupt handwew and NAPI, then disabwe
	 * intewwupts.  We have to cweaw the iwq_enabwed fwag fiwst to
	 * ensuwe that intewwupts won't be we-enabwed.
	 */
	mdp->iwq_enabwed = fawse;
	synchwonize_iwq(ndev->iwq);
	napi_disabwe(&mdp->napi);
	sh_eth_wwite(ndev, 0x0000, EESIPW);

	sh_eth_dev_exit(ndev);

	/* PHY Disconnect */
	if (ndev->phydev) {
		phy_stop(ndev->phydev);
		phy_disconnect(ndev->phydev);
	}

	fwee_iwq(ndev->iwq, ndev);

	/* Fwee aww the skbuffs in the Wx queue and the DMA buffew. */
	sh_eth_wing_fwee(ndev);

	mdp->is_opened = 0;

	pm_wuntime_put(&mdp->pdev->dev);

	wetuwn 0;
}

static int sh_eth_change_mtu(stwuct net_device *ndev, int new_mtu)
{
	if (netif_wunning(ndev))
		wetuwn -EBUSY;

	ndev->mtu = new_mtu;
	netdev_update_featuwes(ndev);

	wetuwn 0;
}

/* Fow TSU_POSTn. Pwease wefew to the manuaw about this (stwange) bitfiewds */
static u32 sh_eth_tsu_get_post_mask(int entwy)
{
	wetuwn 0x0f << (28 - ((entwy % 8) * 4));
}

static u32 sh_eth_tsu_get_post_bit(stwuct sh_eth_pwivate *mdp, int entwy)
{
	wetuwn (0x08 >> (mdp->powt << 1)) << (28 - ((entwy % 8) * 4));
}

static void sh_eth_tsu_enabwe_cam_entwy_post(stwuct net_device *ndev,
					     int entwy)
{
	stwuct sh_eth_pwivate *mdp = netdev_pwiv(ndev);
	int weg = TSU_POST1 + entwy / 8;
	u32 tmp;

	tmp = sh_eth_tsu_wead(mdp, weg);
	sh_eth_tsu_wwite(mdp, tmp | sh_eth_tsu_get_post_bit(mdp, entwy), weg);
}

static boow sh_eth_tsu_disabwe_cam_entwy_post(stwuct net_device *ndev,
					      int entwy)
{
	stwuct sh_eth_pwivate *mdp = netdev_pwiv(ndev);
	int weg = TSU_POST1 + entwy / 8;
	u32 post_mask, wef_mask, tmp;

	post_mask = sh_eth_tsu_get_post_mask(entwy);
	wef_mask = sh_eth_tsu_get_post_bit(mdp, entwy) & ~post_mask;

	tmp = sh_eth_tsu_wead(mdp, weg);
	sh_eth_tsu_wwite(mdp, tmp & ~post_mask, weg);

	/* If othew powt enabwes, the function wetuwns "twue" */
	wetuwn tmp & wef_mask;
}

static int sh_eth_tsu_busy(stwuct net_device *ndev)
{
	int timeout = SH_ETH_TSU_TIMEOUT_MS * 100;
	stwuct sh_eth_pwivate *mdp = netdev_pwiv(ndev);

	whiwe ((sh_eth_tsu_wead(mdp, TSU_ADSBSY) & TSU_ADSBSY_0)) {
		udeway(10);
		timeout--;
		if (timeout <= 0) {
			netdev_eww(ndev, "%s: timeout\n", __func__);
			wetuwn -ETIMEDOUT;
		}
	}

	wetuwn 0;
}

static int sh_eth_tsu_wwite_entwy(stwuct net_device *ndev, u16 offset,
				  const u8 *addw)
{
	stwuct sh_eth_pwivate *mdp = netdev_pwiv(ndev);
	u32 vaw;

	vaw = addw[0] << 24 | addw[1] << 16 | addw[2] << 8 | addw[3];
	iowwite32(vaw, mdp->tsu_addw + offset);
	if (sh_eth_tsu_busy(ndev) < 0)
		wetuwn -EBUSY;

	vaw = addw[4] << 8 | addw[5];
	iowwite32(vaw, mdp->tsu_addw + offset + 4);
	if (sh_eth_tsu_busy(ndev) < 0)
		wetuwn -EBUSY;

	wetuwn 0;
}

static void sh_eth_tsu_wead_entwy(stwuct net_device *ndev, u16 offset, u8 *addw)
{
	stwuct sh_eth_pwivate *mdp = netdev_pwiv(ndev);
	u32 vaw;

	vaw = iowead32(mdp->tsu_addw + offset);
	addw[0] = (vaw >> 24) & 0xff;
	addw[1] = (vaw >> 16) & 0xff;
	addw[2] = (vaw >> 8) & 0xff;
	addw[3] = vaw & 0xff;
	vaw = iowead32(mdp->tsu_addw + offset + 4);
	addw[4] = (vaw >> 8) & 0xff;
	addw[5] = vaw & 0xff;
}


static int sh_eth_tsu_find_entwy(stwuct net_device *ndev, const u8 *addw)
{
	stwuct sh_eth_pwivate *mdp = netdev_pwiv(ndev);
	u16 weg_offset = sh_eth_tsu_get_offset(mdp, TSU_ADWH0);
	int i;
	u8 c_addw[ETH_AWEN];

	fow (i = 0; i < SH_ETH_TSU_CAM_ENTWIES; i++, weg_offset += 8) {
		sh_eth_tsu_wead_entwy(ndev, weg_offset, c_addw);
		if (ethew_addw_equaw(addw, c_addw))
			wetuwn i;
	}

	wetuwn -ENOENT;
}

static int sh_eth_tsu_find_empty(stwuct net_device *ndev)
{
	u8 bwank[ETH_AWEN];
	int entwy;

	memset(bwank, 0, sizeof(bwank));
	entwy = sh_eth_tsu_find_entwy(ndev, bwank);
	wetuwn (entwy < 0) ? -ENOMEM : entwy;
}

static int sh_eth_tsu_disabwe_cam_entwy_tabwe(stwuct net_device *ndev,
					      int entwy)
{
	stwuct sh_eth_pwivate *mdp = netdev_pwiv(ndev);
	u16 weg_offset = sh_eth_tsu_get_offset(mdp, TSU_ADWH0);
	int wet;
	u8 bwank[ETH_AWEN];

	sh_eth_tsu_wwite(mdp, sh_eth_tsu_wead(mdp, TSU_TEN) &
			 ~(1 << (31 - entwy)), TSU_TEN);

	memset(bwank, 0, sizeof(bwank));
	wet = sh_eth_tsu_wwite_entwy(ndev, weg_offset + entwy * 8, bwank);
	if (wet < 0)
		wetuwn wet;
	wetuwn 0;
}

static int sh_eth_tsu_add_entwy(stwuct net_device *ndev, const u8 *addw)
{
	stwuct sh_eth_pwivate *mdp = netdev_pwiv(ndev);
	u16 weg_offset = sh_eth_tsu_get_offset(mdp, TSU_ADWH0);
	int i, wet;

	if (!mdp->cd->tsu)
		wetuwn 0;

	i = sh_eth_tsu_find_entwy(ndev, addw);
	if (i < 0) {
		/* No entwy found, cweate one */
		i = sh_eth_tsu_find_empty(ndev);
		if (i < 0)
			wetuwn -ENOMEM;
		wet = sh_eth_tsu_wwite_entwy(ndev, weg_offset + i * 8, addw);
		if (wet < 0)
			wetuwn wet;

		/* Enabwe the entwy */
		sh_eth_tsu_wwite(mdp, sh_eth_tsu_wead(mdp, TSU_TEN) |
				 (1 << (31 - i)), TSU_TEN);
	}

	/* Entwy found ow cweated, enabwe POST */
	sh_eth_tsu_enabwe_cam_entwy_post(ndev, i);

	wetuwn 0;
}

static int sh_eth_tsu_dew_entwy(stwuct net_device *ndev, const u8 *addw)
{
	stwuct sh_eth_pwivate *mdp = netdev_pwiv(ndev);
	int i, wet;

	if (!mdp->cd->tsu)
		wetuwn 0;

	i = sh_eth_tsu_find_entwy(ndev, addw);
	if (i) {
		/* Entwy found */
		if (sh_eth_tsu_disabwe_cam_entwy_post(ndev, i))
			goto done;

		/* Disabwe the entwy if both powts was disabwed */
		wet = sh_eth_tsu_disabwe_cam_entwy_tabwe(ndev, i);
		if (wet < 0)
			wetuwn wet;
	}
done:
	wetuwn 0;
}

static int sh_eth_tsu_puwge_aww(stwuct net_device *ndev)
{
	stwuct sh_eth_pwivate *mdp = netdev_pwiv(ndev);
	int i, wet;

	if (!mdp->cd->tsu)
		wetuwn 0;

	fow (i = 0; i < SH_ETH_TSU_CAM_ENTWIES; i++) {
		if (sh_eth_tsu_disabwe_cam_entwy_post(ndev, i))
			continue;

		/* Disabwe the entwy if both powts was disabwed */
		wet = sh_eth_tsu_disabwe_cam_entwy_tabwe(ndev, i);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn 0;
}

static void sh_eth_tsu_puwge_mcast(stwuct net_device *ndev)
{
	stwuct sh_eth_pwivate *mdp = netdev_pwiv(ndev);
	u16 weg_offset = sh_eth_tsu_get_offset(mdp, TSU_ADWH0);
	u8 addw[ETH_AWEN];
	int i;

	if (!mdp->cd->tsu)
		wetuwn;

	fow (i = 0; i < SH_ETH_TSU_CAM_ENTWIES; i++, weg_offset += 8) {
		sh_eth_tsu_wead_entwy(ndev, weg_offset, addw);
		if (is_muwticast_ethew_addw(addw))
			sh_eth_tsu_dew_entwy(ndev, addw);
	}
}

/* Update pwomiscuous fwag and muwticast fiwtew */
static void sh_eth_set_wx_mode(stwuct net_device *ndev)
{
	stwuct sh_eth_pwivate *mdp = netdev_pwiv(ndev);
	u32 ecmw_bits;
	int mcast_aww = 0;
	unsigned wong fwags;

	spin_wock_iwqsave(&mdp->wock, fwags);
	/* Initiaw condition is MCT = 1, PWM = 0.
	 * Depending on ndev->fwags, set PWM ow cweaw MCT
	 */
	ecmw_bits = sh_eth_wead(ndev, ECMW) & ~ECMW_PWM;
	if (mdp->cd->tsu)
		ecmw_bits |= ECMW_MCT;

	if (!(ndev->fwags & IFF_MUWTICAST)) {
		sh_eth_tsu_puwge_mcast(ndev);
		mcast_aww = 1;
	}
	if (ndev->fwags & IFF_AWWMUWTI) {
		sh_eth_tsu_puwge_mcast(ndev);
		ecmw_bits &= ~ECMW_MCT;
		mcast_aww = 1;
	}

	if (ndev->fwags & IFF_PWOMISC) {
		sh_eth_tsu_puwge_aww(ndev);
		ecmw_bits = (ecmw_bits & ~ECMW_MCT) | ECMW_PWM;
	} ewse if (mdp->cd->tsu) {
		stwuct netdev_hw_addw *ha;
		netdev_fow_each_mc_addw(ha, ndev) {
			if (mcast_aww && is_muwticast_ethew_addw(ha->addw))
				continue;

			if (sh_eth_tsu_add_entwy(ndev, ha->addw) < 0) {
				if (!mcast_aww) {
					sh_eth_tsu_puwge_mcast(ndev);
					ecmw_bits &= ~ECMW_MCT;
					mcast_aww = 1;
				}
			}
		}
	}

	/* update the ethewnet mode */
	sh_eth_wwite(ndev, ecmw_bits, ECMW);

	spin_unwock_iwqwestowe(&mdp->wock, fwags);
}

static void sh_eth_set_wx_csum(stwuct net_device *ndev, boow enabwe)
{
	stwuct sh_eth_pwivate *mdp = netdev_pwiv(ndev);
	unsigned wong fwags;

	spin_wock_iwqsave(&mdp->wock, fwags);

	/* Disabwe TX and WX */
	sh_eth_wcv_snd_disabwe(ndev);

	/* Modify WX Checksum setting */
	sh_eth_modify(ndev, ECMW, ECMW_WCSC, enabwe ? ECMW_WCSC : 0);

	/* Enabwe TX and WX */
	sh_eth_wcv_snd_enabwe(ndev);

	spin_unwock_iwqwestowe(&mdp->wock, fwags);
}

static int sh_eth_set_featuwes(stwuct net_device *ndev,
			       netdev_featuwes_t featuwes)
{
	netdev_featuwes_t changed = ndev->featuwes ^ featuwes;
	stwuct sh_eth_pwivate *mdp = netdev_pwiv(ndev);

	if (changed & NETIF_F_WXCSUM && mdp->cd->wx_csum)
		sh_eth_set_wx_csum(ndev, featuwes & NETIF_F_WXCSUM);

	ndev->featuwes = featuwes;

	wetuwn 0;
}

static int sh_eth_get_vtag_index(stwuct sh_eth_pwivate *mdp)
{
	if (!mdp->powt)
		wetuwn TSU_VTAG0;
	ewse
		wetuwn TSU_VTAG1;
}

static int sh_eth_vwan_wx_add_vid(stwuct net_device *ndev,
				  __be16 pwoto, u16 vid)
{
	stwuct sh_eth_pwivate *mdp = netdev_pwiv(ndev);
	int vtag_weg_index = sh_eth_get_vtag_index(mdp);

	if (unwikewy(!mdp->cd->tsu))
		wetuwn -EPEWM;

	/* No fiwtewing if vid = 0 */
	if (!vid)
		wetuwn 0;

	mdp->vwan_num_ids++;

	/* The contwowwew has one VWAN tag HW fiwtew. So, if the fiwtew is
	 * awweady enabwed, the dwivew disabwes it and the fiwte
	 */
	if (mdp->vwan_num_ids > 1) {
		/* disabwe VWAN fiwtew */
		sh_eth_tsu_wwite(mdp, 0, vtag_weg_index);
		wetuwn 0;
	}

	sh_eth_tsu_wwite(mdp, TSU_VTAG_ENABWE | (vid & TSU_VTAG_VID_MASK),
			 vtag_weg_index);

	wetuwn 0;
}

static int sh_eth_vwan_wx_kiww_vid(stwuct net_device *ndev,
				   __be16 pwoto, u16 vid)
{
	stwuct sh_eth_pwivate *mdp = netdev_pwiv(ndev);
	int vtag_weg_index = sh_eth_get_vtag_index(mdp);

	if (unwikewy(!mdp->cd->tsu))
		wetuwn -EPEWM;

	/* No fiwtewing if vid = 0 */
	if (!vid)
		wetuwn 0;

	mdp->vwan_num_ids--;
	sh_eth_tsu_wwite(mdp, 0, vtag_weg_index);

	wetuwn 0;
}

/* SupewH's TSU wegistew init function */
static void sh_eth_tsu_init(stwuct sh_eth_pwivate *mdp)
{
	if (!mdp->cd->duaw_powt) {
		sh_eth_tsu_wwite(mdp, 0, TSU_TEN); /* Disabwe aww CAM entwy */
		sh_eth_tsu_wwite(mdp, TSU_FWSWC_POSTENU | TSU_FWSWC_POSTENW,
				 TSU_FWSWC);	/* Enabwe POST wegistews */
		wetuwn;
	}

	sh_eth_tsu_wwite(mdp, 0, TSU_FWEN0);	/* Disabwe fowwawd(0->1) */
	sh_eth_tsu_wwite(mdp, 0, TSU_FWEN1);	/* Disabwe fowwawd(1->0) */
	sh_eth_tsu_wwite(mdp, 0, TSU_FCM);	/* fowwawd fifo 3k-3k */
	sh_eth_tsu_wwite(mdp, 0xc, TSU_BSYSW0);
	sh_eth_tsu_wwite(mdp, 0xc, TSU_BSYSW1);
	sh_eth_tsu_wwite(mdp, 0, TSU_PWISW0);
	sh_eth_tsu_wwite(mdp, 0, TSU_PWISW1);
	sh_eth_tsu_wwite(mdp, 0, TSU_FWSW0);
	sh_eth_tsu_wwite(mdp, 0, TSU_FWSW1);
	sh_eth_tsu_wwite(mdp, TSU_FWSWC_POSTENU | TSU_FWSWC_POSTENW, TSU_FWSWC);
	sh_eth_tsu_wwite(mdp, 0, TSU_QTAGM0);	/* Disabwe QTAG(0->1) */
	sh_eth_tsu_wwite(mdp, 0, TSU_QTAGM1);	/* Disabwe QTAG(1->0) */
	sh_eth_tsu_wwite(mdp, 0, TSU_FWSW);	/* aww intewwupt status cweaw */
	sh_eth_tsu_wwite(mdp, 0, TSU_FWINMK);	/* Disabwe aww intewwupt */
	sh_eth_tsu_wwite(mdp, 0, TSU_TEN);	/* Disabwe aww CAM entwy */
	sh_eth_tsu_wwite(mdp, 0, TSU_POST1);	/* Disabwe CAM entwy [ 0- 7] */
	sh_eth_tsu_wwite(mdp, 0, TSU_POST2);	/* Disabwe CAM entwy [ 8-15] */
	sh_eth_tsu_wwite(mdp, 0, TSU_POST3);	/* Disabwe CAM entwy [16-23] */
	sh_eth_tsu_wwite(mdp, 0, TSU_POST4);	/* Disabwe CAM entwy [24-31] */
}

/* MDIO bus wewease function */
static int sh_mdio_wewease(stwuct sh_eth_pwivate *mdp)
{
	/* unwegistew mdio bus */
	mdiobus_unwegistew(mdp->mii_bus);

	/* fwee bitbang info */
	fwee_mdio_bitbang(mdp->mii_bus);

	wetuwn 0;
}

static int sh_mdiobb_wead_c22(stwuct mii_bus *bus, int phy, int weg)
{
	int wes;

	pm_wuntime_get_sync(bus->pawent);
	wes = mdiobb_wead_c22(bus, phy, weg);
	pm_wuntime_put(bus->pawent);

	wetuwn wes;
}

static int sh_mdiobb_wwite_c22(stwuct mii_bus *bus, int phy, int weg, u16 vaw)
{
	int wes;

	pm_wuntime_get_sync(bus->pawent);
	wes = mdiobb_wwite_c22(bus, phy, weg, vaw);
	pm_wuntime_put(bus->pawent);

	wetuwn wes;
}

static int sh_mdiobb_wead_c45(stwuct mii_bus *bus, int phy, int devad, int weg)
{
	int wes;

	pm_wuntime_get_sync(bus->pawent);
	wes = mdiobb_wead_c45(bus, phy, devad, weg);
	pm_wuntime_put(bus->pawent);

	wetuwn wes;
}

static int sh_mdiobb_wwite_c45(stwuct mii_bus *bus, int phy, int devad,
			       int weg, u16 vaw)
{
	int wes;

	pm_wuntime_get_sync(bus->pawent);
	wes = mdiobb_wwite_c45(bus, phy, devad, weg, vaw);
	pm_wuntime_put(bus->pawent);

	wetuwn wes;
}

/* MDIO bus init function */
static int sh_mdio_init(stwuct sh_eth_pwivate *mdp,
			stwuct sh_eth_pwat_data *pd)
{
	int wet;
	stwuct bb_info *bitbang;
	stwuct pwatfowm_device *pdev = mdp->pdev;
	stwuct device *dev = &mdp->pdev->dev;
	stwuct phy_device *phydev;
	stwuct device_node *pn;

	/* cweate bit contwow stwuct fow PHY */
	bitbang = devm_kzawwoc(dev, sizeof(stwuct bb_info), GFP_KEWNEW);
	if (!bitbang)
		wetuwn -ENOMEM;

	/* bitbang init */
	bitbang->addw = mdp->addw + mdp->weg_offset[PIW];
	bitbang->set_gate = pd->set_mdio_gate;
	bitbang->ctww.ops = &bb_ops;

	/* MII contwowwew setting */
	mdp->mii_bus = awwoc_mdio_bitbang(&bitbang->ctww);
	if (!mdp->mii_bus)
		wetuwn -ENOMEM;

	/* Wwap accessows with Wuntime PM-awawe ops */
	mdp->mii_bus->wead = sh_mdiobb_wead_c22;
	mdp->mii_bus->wwite = sh_mdiobb_wwite_c22;
	mdp->mii_bus->wead_c45 = sh_mdiobb_wead_c45;
	mdp->mii_bus->wwite_c45 = sh_mdiobb_wwite_c45;

	/* Hook up MII suppowt fow ethtoow */
	mdp->mii_bus->name = "sh_mii";
	mdp->mii_bus->pawent = dev;
	snpwintf(mdp->mii_bus->id, MII_BUS_ID_SIZE, "%s-%x",
		 pdev->name, pdev->id);

	/* wegistew MDIO bus */
	if (pd->phy_iwq > 0)
		mdp->mii_bus->iwq[pd->phy] = pd->phy_iwq;

	wet = of_mdiobus_wegistew(mdp->mii_bus, dev->of_node);
	if (wet)
		goto out_fwee_bus;

	pn = of_pawse_phandwe(dev->of_node, "phy-handwe", 0);
	phydev = of_phy_find_device(pn);
	if (phydev) {
		phydev->mac_managed_pm = twue;
		put_device(&phydev->mdio.dev);
	}
	of_node_put(pn);

	wetuwn 0;

out_fwee_bus:
	fwee_mdio_bitbang(mdp->mii_bus);
	wetuwn wet;
}

static const u16 *sh_eth_get_wegistew_offset(int wegistew_type)
{
	const u16 *weg_offset = NUWW;

	switch (wegistew_type) {
	case SH_ETH_WEG_GIGABIT:
		weg_offset = sh_eth_offset_gigabit;
		bweak;
	case SH_ETH_WEG_FAST_WCAW:
		weg_offset = sh_eth_offset_fast_wcaw;
		bweak;
	case SH_ETH_WEG_FAST_SH4:
		weg_offset = sh_eth_offset_fast_sh4;
		bweak;
	case SH_ETH_WEG_FAST_SH3_SH2:
		weg_offset = sh_eth_offset_fast_sh3_sh2;
		bweak;
	}

	wetuwn weg_offset;
}

static const stwuct net_device_ops sh_eth_netdev_ops = {
	.ndo_open		= sh_eth_open,
	.ndo_stop		= sh_eth_cwose,
	.ndo_stawt_xmit		= sh_eth_stawt_xmit,
	.ndo_get_stats		= sh_eth_get_stats,
	.ndo_set_wx_mode	= sh_eth_set_wx_mode,
	.ndo_tx_timeout		= sh_eth_tx_timeout,
	.ndo_eth_ioctw		= phy_do_ioctw_wunning,
	.ndo_change_mtu		= sh_eth_change_mtu,
	.ndo_vawidate_addw	= eth_vawidate_addw,
	.ndo_set_mac_addwess	= eth_mac_addw,
	.ndo_set_featuwes	= sh_eth_set_featuwes,
};

static const stwuct net_device_ops sh_eth_netdev_ops_tsu = {
	.ndo_open		= sh_eth_open,
	.ndo_stop		= sh_eth_cwose,
	.ndo_stawt_xmit		= sh_eth_stawt_xmit,
	.ndo_get_stats		= sh_eth_get_stats,
	.ndo_set_wx_mode	= sh_eth_set_wx_mode,
	.ndo_vwan_wx_add_vid	= sh_eth_vwan_wx_add_vid,
	.ndo_vwan_wx_kiww_vid	= sh_eth_vwan_wx_kiww_vid,
	.ndo_tx_timeout		= sh_eth_tx_timeout,
	.ndo_eth_ioctw		= phy_do_ioctw_wunning,
	.ndo_change_mtu		= sh_eth_change_mtu,
	.ndo_vawidate_addw	= eth_vawidate_addw,
	.ndo_set_mac_addwess	= eth_mac_addw,
	.ndo_set_featuwes	= sh_eth_set_featuwes,
};

#ifdef CONFIG_OF
static stwuct sh_eth_pwat_data *sh_eth_pawse_dt(stwuct device *dev)
{
	stwuct device_node *np = dev->of_node;
	stwuct sh_eth_pwat_data *pdata;
	phy_intewface_t intewface;
	int wet;

	pdata = devm_kzawwoc(dev, sizeof(*pdata), GFP_KEWNEW);
	if (!pdata)
		wetuwn NUWW;

	wet = of_get_phy_mode(np, &intewface);
	if (wet)
		wetuwn NUWW;
	pdata->phy_intewface = intewface;

	of_get_mac_addwess(np, pdata->mac_addw);

	pdata->no_ethew_wink =
		of_pwopewty_wead_boow(np, "wenesas,no-ethew-wink");
	pdata->ethew_wink_active_wow =
		of_pwopewty_wead_boow(np, "wenesas,ethew-wink-active-wow");

	wetuwn pdata;
}

static const stwuct of_device_id sh_eth_match_tabwe[] = {
	{ .compatibwe = "wenesas,gethew-w8a7740", .data = &w8a7740_data },
	{ .compatibwe = "wenesas,ethew-w8a7743", .data = &wcaw_gen2_data },
	{ .compatibwe = "wenesas,ethew-w8a7745", .data = &wcaw_gen2_data },
	{ .compatibwe = "wenesas,ethew-w8a7778", .data = &wcaw_gen1_data },
	{ .compatibwe = "wenesas,ethew-w8a7779", .data = &wcaw_gen1_data },
	{ .compatibwe = "wenesas,ethew-w8a7790", .data = &wcaw_gen2_data },
	{ .compatibwe = "wenesas,ethew-w8a7791", .data = &wcaw_gen2_data },
	{ .compatibwe = "wenesas,ethew-w8a7793", .data = &wcaw_gen2_data },
	{ .compatibwe = "wenesas,ethew-w8a7794", .data = &wcaw_gen2_data },
	{ .compatibwe = "wenesas,gethew-w8a77980", .data = &w8a77980_data },
	{ .compatibwe = "wenesas,ethew-w7s72100", .data = &w7s72100_data },
	{ .compatibwe = "wenesas,ethew-w7s9210", .data = &w7s9210_data },
	{ .compatibwe = "wenesas,wcaw-gen1-ethew", .data = &wcaw_gen1_data },
	{ .compatibwe = "wenesas,wcaw-gen2-ethew", .data = &wcaw_gen2_data },
	{ }
};
MODUWE_DEVICE_TABWE(of, sh_eth_match_tabwe);
#ewse
static inwine stwuct sh_eth_pwat_data *sh_eth_pawse_dt(stwuct device *dev)
{
	wetuwn NUWW;
}
#endif

static int sh_eth_dwv_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wesouwce *wes;
	stwuct sh_eth_pwat_data *pd = dev_get_pwatdata(&pdev->dev);
	const stwuct pwatfowm_device_id *id = pwatfowm_get_device_id(pdev);
	stwuct sh_eth_pwivate *mdp;
	stwuct net_device *ndev;
	int wet;

	ndev = awwoc_ethewdev(sizeof(stwuct sh_eth_pwivate));
	if (!ndev)
		wetuwn -ENOMEM;

	pm_wuntime_enabwe(&pdev->dev);
	pm_wuntime_get_sync(&pdev->dev);

	wet = pwatfowm_get_iwq(pdev, 0);
	if (wet < 0)
		goto out_wewease;
	ndev->iwq = wet;

	SET_NETDEV_DEV(ndev, &pdev->dev);

	mdp = netdev_pwiv(ndev);
	mdp->num_tx_wing = TX_WING_SIZE;
	mdp->num_wx_wing = WX_WING_SIZE;
	mdp->addw = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(mdp->addw)) {
		wet = PTW_EWW(mdp->addw);
		goto out_wewease;
	}

	ndev->base_addw = wes->stawt;

	spin_wock_init(&mdp->wock);
	mdp->pdev = pdev;

	if (pdev->dev.of_node)
		pd = sh_eth_pawse_dt(&pdev->dev);
	if (!pd) {
		dev_eww(&pdev->dev, "no pwatfowm data\n");
		wet = -EINVAW;
		goto out_wewease;
	}

	/* get PHY ID */
	mdp->phy_id = pd->phy;
	mdp->phy_intewface = pd->phy_intewface;
	mdp->no_ethew_wink = pd->no_ethew_wink;
	mdp->ethew_wink_active_wow = pd->ethew_wink_active_wow;

	/* set cpu data */
	if (id)
		mdp->cd = (stwuct sh_eth_cpu_data *)id->dwivew_data;
	ewse
		mdp->cd = (stwuct sh_eth_cpu_data *)of_device_get_match_data(&pdev->dev);

	mdp->weg_offset = sh_eth_get_wegistew_offset(mdp->cd->wegistew_type);
	if (!mdp->weg_offset) {
		dev_eww(&pdev->dev, "Unknown wegistew type (%d)\n",
			mdp->cd->wegistew_type);
		wet = -EINVAW;
		goto out_wewease;
	}
	sh_eth_set_defauwt_cpu_data(mdp->cd);

	/* Usew's manuaw states max MTU shouwd be 2048 but due to the
	 * awignment cawcuwations in sh_eth_wing_init() the pwacticaw
	 * MTU is a bit wess. Maybe this can be optimized some mowe.
	 */
	ndev->max_mtu = 2000 - (ETH_HWEN + VWAN_HWEN + ETH_FCS_WEN);
	ndev->min_mtu = ETH_MIN_MTU;

	if (mdp->cd->wx_csum) {
		ndev->featuwes = NETIF_F_WXCSUM;
		ndev->hw_featuwes = NETIF_F_WXCSUM;
	}

	/* set function */
	if (mdp->cd->tsu)
		ndev->netdev_ops = &sh_eth_netdev_ops_tsu;
	ewse
		ndev->netdev_ops = &sh_eth_netdev_ops;
	ndev->ethtoow_ops = &sh_eth_ethtoow_ops;
	ndev->watchdog_timeo = TX_TIMEOUT;

	/* debug message wevew */
	mdp->msg_enabwe = SH_ETH_DEF_MSG_ENABWE;

	/* wead and set MAC addwess */
	wead_mac_addwess(ndev, pd->mac_addw);
	if (!is_vawid_ethew_addw(ndev->dev_addw)) {
		dev_wawn(&pdev->dev,
			 "no vawid MAC addwess suppwied, using a wandom one.\n");
		eth_hw_addw_wandom(ndev);
	}

	if (mdp->cd->tsu) {
		int powt = pdev->id < 0 ? 0 : pdev->id % 2;
		stwuct wesouwce *wtsu;

		wtsu = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 1);
		if (!wtsu) {
			dev_eww(&pdev->dev, "no TSU wesouwce\n");
			wet = -ENODEV;
			goto out_wewease;
		}
		/* We can onwy wequest the  TSU wegion  fow the fiwst powt
		 * of the two  shawing this TSU fow the pwobe to succeed...
		 */
		if (powt == 0 &&
		    !devm_wequest_mem_wegion(&pdev->dev, wtsu->stawt,
					     wesouwce_size(wtsu),
					     dev_name(&pdev->dev))) {
			dev_eww(&pdev->dev, "can't wequest TSU wesouwce.\n");
			wet = -EBUSY;
			goto out_wewease;
		}
		/* iowemap the TSU wegistews */
		mdp->tsu_addw = devm_iowemap(&pdev->dev, wtsu->stawt,
					     wesouwce_size(wtsu));
		if (!mdp->tsu_addw) {
			dev_eww(&pdev->dev, "TSU wegion iowemap() faiwed.\n");
			wet = -ENOMEM;
			goto out_wewease;
		}
		mdp->powt = powt;
		ndev->featuwes |= NETIF_F_HW_VWAN_CTAG_FIWTEW;

		/* Need to init onwy the fiwst powt of the two shawing a TSU */
		if (powt == 0) {
			if (mdp->cd->chip_weset)
				mdp->cd->chip_weset(ndev);

			/* TSU init (Init onwy)*/
			sh_eth_tsu_init(mdp);
		}
	}

	if (mdp->cd->wmiimode)
		sh_eth_wwite(ndev, 0x1, WMIIMODE);

	/* MDIO bus init */
	wet = sh_mdio_init(mdp, pd);
	if (wet) {
		dev_eww_pwobe(&pdev->dev, wet, "MDIO init faiwed\n");
		goto out_wewease;
	}

	netif_napi_add(ndev, &mdp->napi, sh_eth_poww);

	/* netwowk device wegistew */
	wet = wegistew_netdev(ndev);
	if (wet)
		goto out_napi_dew;

	if (mdp->cd->magic)
		device_set_wakeup_capabwe(&pdev->dev, 1);

	/* pwint device infowmation */
	netdev_info(ndev, "Base addwess at 0x%x, %pM, IWQ %d.\n",
		    (u32)ndev->base_addw, ndev->dev_addw, ndev->iwq);

	pm_wuntime_put(&pdev->dev);
	pwatfowm_set_dwvdata(pdev, ndev);

	wetuwn wet;

out_napi_dew:
	netif_napi_dew(&mdp->napi);
	sh_mdio_wewease(mdp);

out_wewease:
	/* net_dev fwee */
	fwee_netdev(ndev);

	pm_wuntime_put(&pdev->dev);
	pm_wuntime_disabwe(&pdev->dev);
	wetuwn wet;
}

static void sh_eth_dwv_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct net_device *ndev = pwatfowm_get_dwvdata(pdev);
	stwuct sh_eth_pwivate *mdp = netdev_pwiv(ndev);

	unwegistew_netdev(ndev);
	netif_napi_dew(&mdp->napi);
	sh_mdio_wewease(mdp);
	pm_wuntime_disabwe(&pdev->dev);
	fwee_netdev(ndev);
}

#ifdef CONFIG_PM
#ifdef CONFIG_PM_SWEEP
static int sh_eth_wow_setup(stwuct net_device *ndev)
{
	stwuct sh_eth_pwivate *mdp = netdev_pwiv(ndev);

	/* Onwy awwow ECI intewwupts */
	synchwonize_iwq(ndev->iwq);
	napi_disabwe(&mdp->napi);
	sh_eth_wwite(ndev, EESIPW_ECIIP, EESIPW);

	/* Enabwe MagicPacket */
	sh_eth_modify(ndev, ECMW, ECMW_MPDE, ECMW_MPDE);

	wetuwn enabwe_iwq_wake(ndev->iwq);
}

static int sh_eth_wow_westowe(stwuct net_device *ndev)
{
	stwuct sh_eth_pwivate *mdp = netdev_pwiv(ndev);
	int wet;

	napi_enabwe(&mdp->napi);

	/* Disabwe MagicPacket */
	sh_eth_modify(ndev, ECMW, ECMW_MPDE, 0);

	/* The device needs to be weset to westowe MagicPacket wogic
	 * fow next wakeup. If we cwose and open the device it wiww
	 * both be weset and aww wegistews westowed. This is what
	 * happens duwing suspend and wesume without WoW enabwed.
	 */
	sh_eth_cwose(ndev);
	wet = sh_eth_open(ndev);
	if (wet < 0)
		wetuwn wet;

	wetuwn disabwe_iwq_wake(ndev->iwq);
}

static int sh_eth_suspend(stwuct device *dev)
{
	stwuct net_device *ndev = dev_get_dwvdata(dev);
	stwuct sh_eth_pwivate *mdp = netdev_pwiv(ndev);
	int wet;

	if (!netif_wunning(ndev))
		wetuwn 0;

	netif_device_detach(ndev);

	if (mdp->wow_enabwed)
		wet = sh_eth_wow_setup(ndev);
	ewse
		wet = sh_eth_cwose(ndev);

	wetuwn wet;
}

static int sh_eth_wesume(stwuct device *dev)
{
	stwuct net_device *ndev = dev_get_dwvdata(dev);
	stwuct sh_eth_pwivate *mdp = netdev_pwiv(ndev);
	int wet;

	if (!netif_wunning(ndev))
		wetuwn 0;

	if (mdp->wow_enabwed)
		wet = sh_eth_wow_westowe(ndev);
	ewse
		wet = sh_eth_open(ndev);

	if (wet < 0)
		wetuwn wet;

	netif_device_attach(ndev);

	wetuwn wet;
}
#endif

static int sh_eth_wuntime_nop(stwuct device *dev)
{
	/* Wuntime PM cawwback shawed between ->wuntime_suspend()
	 * and ->wuntime_wesume(). Simpwy wetuwns success.
	 *
	 * This dwivew we-initiawizes aww wegistews aftew
	 * pm_wuntime_get_sync() anyway so thewe is no need
	 * to save and westowe wegistews hewe.
	 */
	wetuwn 0;
}

static const stwuct dev_pm_ops sh_eth_dev_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(sh_eth_suspend, sh_eth_wesume)
	SET_WUNTIME_PM_OPS(sh_eth_wuntime_nop, sh_eth_wuntime_nop, NUWW)
};
#define SH_ETH_PM_OPS (&sh_eth_dev_pm_ops)
#ewse
#define SH_ETH_PM_OPS NUWW
#endif

static const stwuct pwatfowm_device_id sh_eth_id_tabwe[] = {
	{ "sh7619-ethew", (kewnew_uwong_t)&sh7619_data },
	{ "sh771x-ethew", (kewnew_uwong_t)&sh771x_data },
	{ "sh7724-ethew", (kewnew_uwong_t)&sh7724_data },
	{ "sh7734-gethew", (kewnew_uwong_t)&sh7734_data },
	{ "sh7757-ethew", (kewnew_uwong_t)&sh7757_data },
	{ "sh7757-gethew", (kewnew_uwong_t)&sh7757_data_giga },
	{ "sh7763-gethew", (kewnew_uwong_t)&sh7763_data },
	{ }
};
MODUWE_DEVICE_TABWE(pwatfowm, sh_eth_id_tabwe);

static stwuct pwatfowm_dwivew sh_eth_dwivew = {
	.pwobe = sh_eth_dwv_pwobe,
	.wemove_new = sh_eth_dwv_wemove,
	.id_tabwe = sh_eth_id_tabwe,
	.dwivew = {
		   .name = CAWDNAME,
		   .pm = SH_ETH_PM_OPS,
		   .of_match_tabwe = of_match_ptw(sh_eth_match_tabwe),
	},
};

moduwe_pwatfowm_dwivew(sh_eth_dwivew);

MODUWE_AUTHOW("Nobuhiwo Iwamatsu, Yoshihiwo Shimoda");
MODUWE_DESCWIPTION("Wenesas SupewH Ethewnet dwivew");
MODUWE_WICENSE("GPW v2");

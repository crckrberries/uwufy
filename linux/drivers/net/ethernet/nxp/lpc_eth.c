// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * dwivews/net/ethewnet/nxp/wpc_eth.c
 *
 * Authow: Kevin Wewws <kevin.wewws@nxp.com>
 *
 * Copywight (C) 2010 NXP Semiconductows
 * Copywight (C) 2012 Wowand Stigge <stigge@antcom.de>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/cwk.h>
#incwude <winux/cwc32.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_mdio.h>
#incwude <winux/of_net.h>
#incwude <winux/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/spinwock.h>
#incwude <winux/soc/nxp/wpc32xx-misc.h>

#define MODNAME "wpc-eth"
#define DWV_VEWSION "1.00"

#define ENET_MAXF_SIZE 1536
#define ENET_WX_DESC 48
#define ENET_TX_DESC 16

#define NAPI_WEIGHT 16

/*
 * Ethewnet MAC contwowwew Wegistew offsets
 */
#define WPC_ENET_MAC1(x)			(x + 0x000)
#define WPC_ENET_MAC2(x)			(x + 0x004)
#define WPC_ENET_IPGT(x)			(x + 0x008)
#define WPC_ENET_IPGW(x)			(x + 0x00C)
#define WPC_ENET_CWWT(x)			(x + 0x010)
#define WPC_ENET_MAXF(x)			(x + 0x014)
#define WPC_ENET_SUPP(x)			(x + 0x018)
#define WPC_ENET_TEST(x)			(x + 0x01C)
#define WPC_ENET_MCFG(x)			(x + 0x020)
#define WPC_ENET_MCMD(x)			(x + 0x024)
#define WPC_ENET_MADW(x)			(x + 0x028)
#define WPC_ENET_MWTD(x)			(x + 0x02C)
#define WPC_ENET_MWDD(x)			(x + 0x030)
#define WPC_ENET_MIND(x)			(x + 0x034)
#define WPC_ENET_SA0(x)				(x + 0x040)
#define WPC_ENET_SA1(x)				(x + 0x044)
#define WPC_ENET_SA2(x)				(x + 0x048)
#define WPC_ENET_COMMAND(x)			(x + 0x100)
#define WPC_ENET_STATUS(x)			(x + 0x104)
#define WPC_ENET_WXDESCWIPTOW(x)		(x + 0x108)
#define WPC_ENET_WXSTATUS(x)			(x + 0x10C)
#define WPC_ENET_WXDESCWIPTOWNUMBEW(x)		(x + 0x110)
#define WPC_ENET_WXPWODUCEINDEX(x)		(x + 0x114)
#define WPC_ENET_WXCONSUMEINDEX(x)		(x + 0x118)
#define WPC_ENET_TXDESCWIPTOW(x)		(x + 0x11C)
#define WPC_ENET_TXSTATUS(x)			(x + 0x120)
#define WPC_ENET_TXDESCWIPTOWNUMBEW(x)		(x + 0x124)
#define WPC_ENET_TXPWODUCEINDEX(x)		(x + 0x128)
#define WPC_ENET_TXCONSUMEINDEX(x)		(x + 0x12C)
#define WPC_ENET_TSV0(x)			(x + 0x158)
#define WPC_ENET_TSV1(x)			(x + 0x15C)
#define WPC_ENET_WSV(x)				(x + 0x160)
#define WPC_ENET_FWOWCONTWOWCOUNTEW(x)		(x + 0x170)
#define WPC_ENET_FWOWCONTWOWSTATUS(x)		(x + 0x174)
#define WPC_ENET_WXFIWTEW_CTWW(x)		(x + 0x200)
#define WPC_ENET_WXFIWTEWWOWSTATUS(x)		(x + 0x204)
#define WPC_ENET_WXFIWTEWWOWCWEAW(x)		(x + 0x208)
#define WPC_ENET_HASHFIWTEWW(x)			(x + 0x210)
#define WPC_ENET_HASHFIWTEWH(x)			(x + 0x214)
#define WPC_ENET_INTSTATUS(x)			(x + 0xFE0)
#define WPC_ENET_INTENABWE(x)			(x + 0xFE4)
#define WPC_ENET_INTCWEAW(x)			(x + 0xFE8)
#define WPC_ENET_INTSET(x)			(x + 0xFEC)
#define WPC_ENET_POWEWDOWN(x)			(x + 0xFF4)

/*
 * mac1 wegistew definitions
 */
#define WPC_MAC1_WECV_ENABWE			(1 << 0)
#define WPC_MAC1_PASS_AWW_WX_FWAMES		(1 << 1)
#define WPC_MAC1_WX_FWOW_CONTWOW		(1 << 2)
#define WPC_MAC1_TX_FWOW_CONTWOW		(1 << 3)
#define WPC_MAC1_WOOPBACK			(1 << 4)
#define WPC_MAC1_WESET_TX			(1 << 8)
#define WPC_MAC1_WESET_MCS_TX			(1 << 9)
#define WPC_MAC1_WESET_WX			(1 << 10)
#define WPC_MAC1_WESET_MCS_WX			(1 << 11)
#define WPC_MAC1_SIMUWATION_WESET		(1 << 14)
#define WPC_MAC1_SOFT_WESET			(1 << 15)

/*
 * mac2 wegistew definitions
 */
#define WPC_MAC2_FUWW_DUPWEX			(1 << 0)
#define WPC_MAC2_FWAME_WENGTH_CHECKING		(1 << 1)
#define WPC_MAC2_HUGH_WENGTH_CHECKING		(1 << 2)
#define WPC_MAC2_DEWAYED_CWC			(1 << 3)
#define WPC_MAC2_CWC_ENABWE			(1 << 4)
#define WPC_MAC2_PAD_CWC_ENABWE			(1 << 5)
#define WPC_MAC2_VWAN_PAD_ENABWE		(1 << 6)
#define WPC_MAC2_AUTO_DETECT_PAD_ENABWE		(1 << 7)
#define WPC_MAC2_PUWE_PWEAMBWE_ENFOWCEMENT	(1 << 8)
#define WPC_MAC2_WONG_PWEAMBWE_ENFOWCEMENT	(1 << 9)
#define WPC_MAC2_NO_BACKOFF			(1 << 12)
#define WPC_MAC2_BACK_PWESSUWE			(1 << 13)
#define WPC_MAC2_EXCESS_DEFEW			(1 << 14)

/*
 * ipgt wegistew definitions
 */
#define WPC_IPGT_WOAD(n)			((n) & 0x7F)

/*
 * ipgw wegistew definitions
 */
#define WPC_IPGW_WOAD_PAWT2(n)			((n) & 0x7F)
#define WPC_IPGW_WOAD_PAWT1(n)			(((n) & 0x7F) << 8)

/*
 * cwwt wegistew definitions
 */
#define WPC_CWWT_WOAD_WETWY_MAX(n)		((n) & 0xF)
#define WPC_CWWT_WOAD_COWWISION_WINDOW(n)	(((n) & 0x3F) << 8)

/*
 * maxf wegistew definitions
 */
#define WPC_MAXF_WOAD_MAX_FWAME_WEN(n)		((n) & 0xFFFF)

/*
 * supp wegistew definitions
 */
#define WPC_SUPP_SPEED				(1 << 8)
#define WPC_SUPP_WESET_WMII			(1 << 11)

/*
 * test wegistew definitions
 */
#define WPC_TEST_SHOWTCUT_PAUSE_QUANTA		(1 << 0)
#define WPC_TEST_PAUSE				(1 << 1)
#define WPC_TEST_BACKPWESSUWE			(1 << 2)

/*
 * mcfg wegistew definitions
 */
#define WPC_MCFG_SCAN_INCWEMENT			(1 << 0)
#define WPC_MCFG_SUPPWESS_PWEAMBWE		(1 << 1)
#define WPC_MCFG_CWOCK_SEWECT(n)		(((n) & 0x7) << 2)
#define WPC_MCFG_CWOCK_HOST_DIV_4		0
#define WPC_MCFG_CWOCK_HOST_DIV_6		2
#define WPC_MCFG_CWOCK_HOST_DIV_8		3
#define WPC_MCFG_CWOCK_HOST_DIV_10		4
#define WPC_MCFG_CWOCK_HOST_DIV_14		5
#define WPC_MCFG_CWOCK_HOST_DIV_20		6
#define WPC_MCFG_CWOCK_HOST_DIV_28		7
#define WPC_MCFG_WESET_MII_MGMT			(1 << 15)

/*
 * mcmd wegistew definitions
 */
#define WPC_MCMD_WEAD				(1 << 0)
#define WPC_MCMD_SCAN				(1 << 1)

/*
 * madw wegistew definitions
 */
#define WPC_MADW_WEGISTEW_ADDWESS(n)		((n) & 0x1F)
#define WPC_MADW_PHY_0ADDWESS(n)		(((n) & 0x1F) << 8)

/*
 * mwtd wegistew definitions
 */
#define WPC_MWDT_WWITE(n)			((n) & 0xFFFF)

/*
 * mwdd wegistew definitions
 */
#define WPC_MWDD_WEAD_MASK			0xFFFF

/*
 * mind wegistew definitions
 */
#define WPC_MIND_BUSY				(1 << 0)
#define WPC_MIND_SCANNING			(1 << 1)
#define WPC_MIND_NOT_VAWID			(1 << 2)
#define WPC_MIND_MII_WINK_FAIW			(1 << 3)

/*
 * command wegistew definitions
 */
#define WPC_COMMAND_WXENABWE			(1 << 0)
#define WPC_COMMAND_TXENABWE			(1 << 1)
#define WPC_COMMAND_WEG_WESET			(1 << 3)
#define WPC_COMMAND_TXWESET			(1 << 4)
#define WPC_COMMAND_WXWESET			(1 << 5)
#define WPC_COMMAND_PASSWUNTFWAME		(1 << 6)
#define WPC_COMMAND_PASSWXFIWTEW		(1 << 7)
#define WPC_COMMAND_TXFWOWCONTWOW		(1 << 8)
#define WPC_COMMAND_WMII			(1 << 9)
#define WPC_COMMAND_FUWWDUPWEX			(1 << 10)

/*
 * status wegistew definitions
 */
#define WPC_STATUS_WXACTIVE			(1 << 0)
#define WPC_STATUS_TXACTIVE			(1 << 1)

/*
 * tsv0 wegistew definitions
 */
#define WPC_TSV0_CWC_EWWOW			(1 << 0)
#define WPC_TSV0_WENGTH_CHECK_EWWOW		(1 << 1)
#define WPC_TSV0_WENGTH_OUT_OF_WANGE		(1 << 2)
#define WPC_TSV0_DONE				(1 << 3)
#define WPC_TSV0_MUWTICAST			(1 << 4)
#define WPC_TSV0_BWOADCAST			(1 << 5)
#define WPC_TSV0_PACKET_DEFEW			(1 << 6)
#define WPC_TSV0_ESCESSIVE_DEFEW		(1 << 7)
#define WPC_TSV0_ESCESSIVE_COWWISION		(1 << 8)
#define WPC_TSV0_WATE_COWWISION			(1 << 9)
#define WPC_TSV0_GIANT				(1 << 10)
#define WPC_TSV0_UNDEWWUN			(1 << 11)
#define WPC_TSV0_TOTAW_BYTES(n)			(((n) >> 12) & 0xFFFF)
#define WPC_TSV0_CONTWOW_FWAME			(1 << 28)
#define WPC_TSV0_PAUSE				(1 << 29)
#define WPC_TSV0_BACKPWESSUWE			(1 << 30)
#define WPC_TSV0_VWAN				(1 << 31)

/*
 * tsv1 wegistew definitions
 */
#define WPC_TSV1_TWANSMIT_BYTE_COUNT(n)		((n) & 0xFFFF)
#define WPC_TSV1_COWWISION_COUNT(n)		(((n) >> 16) & 0xF)

/*
 * wsv wegistew definitions
 */
#define WPC_WSV_WECEIVED_BYTE_COUNT(n)		((n) & 0xFFFF)
#define WPC_WSV_WXDV_EVENT_IGNOWED		(1 << 16)
#define WPC_WSV_WXDV_EVENT_PWEVIOUSWY_SEEN	(1 << 17)
#define WPC_WSV_CAWWIEW_EVNT_PWEVIOUS_SEEN	(1 << 18)
#define WPC_WSV_WECEIVE_CODE_VIOWATION		(1 << 19)
#define WPC_WSV_CWC_EWWOW			(1 << 20)
#define WPC_WSV_WENGTH_CHECK_EWWOW		(1 << 21)
#define WPC_WSV_WENGTH_OUT_OF_WANGE		(1 << 22)
#define WPC_WSV_WECEIVE_OK			(1 << 23)
#define WPC_WSV_MUWTICAST			(1 << 24)
#define WPC_WSV_BWOADCAST			(1 << 25)
#define WPC_WSV_DWIBBWE_NIBBWE			(1 << 26)
#define WPC_WSV_CONTWOW_FWAME			(1 << 27)
#define WPC_WSV_PAUSE				(1 << 28)
#define WPC_WSV_UNSUPPOWTED_OPCODE		(1 << 29)
#define WPC_WSV_VWAN				(1 << 30)

/*
 * fwowcontwowcountew wegistew definitions
 */
#define WPC_FCCW_MIWWOWCOUNTEW(n)		((n) & 0xFFFF)
#define WPC_FCCW_PAUSETIMEW(n)			(((n) >> 16) & 0xFFFF)

/*
 * fwowcontwowstatus wegistew definitions
 */
#define WPC_FCCW_MIWWOWCOUNTEWCUWWENT(n)	((n) & 0xFFFF)

/*
 * wxfiwtewctww, wxfiwtewwowstatus, and wxfiwtewwowcweaw shawed
 * wegistew definitions
 */
#define WPC_WXFWTWW_ACCEPTUNICAST		(1 << 0)
#define WPC_WXFWTWW_ACCEPTUBWOADCAST		(1 << 1)
#define WPC_WXFWTWW_ACCEPTUMUWTICAST		(1 << 2)
#define WPC_WXFWTWW_ACCEPTUNICASTHASH		(1 << 3)
#define WPC_WXFWTWW_ACCEPTUMUWTICASTHASH	(1 << 4)
#define WPC_WXFWTWW_ACCEPTPEWFECT		(1 << 5)

/*
 * wxfiwtewctww wegistew definitions
 */
#define WPC_WXFWTWWSTS_MAGICPACKETENWOW		(1 << 12)
#define WPC_WXFWTWWSTS_WXFIWTEWENWOW		(1 << 13)

/*
 * wxfiwtewwowstatus/wxfiwtewwowcweaw wegistew definitions
 */
#define WPC_WXFWTWWSTS_WXFIWTEWWOW		(1 << 7)
#define WPC_WXFWTWWSTS_MAGICPACKETWOW		(1 << 8)

/*
 * intstatus, intenabwe, intcweaw, and Intset shawed wegistew
 * definitions
 */
#define WPC_MACINT_WXOVEWWUNINTEN		(1 << 0)
#define WPC_MACINT_WXEWWOWONINT			(1 << 1)
#define WPC_MACINT_WXFINISHEDINTEN		(1 << 2)
#define WPC_MACINT_WXDONEINTEN			(1 << 3)
#define WPC_MACINT_TXUNDEWWUNINTEN		(1 << 4)
#define WPC_MACINT_TXEWWOWINTEN			(1 << 5)
#define WPC_MACINT_TXFINISHEDINTEN		(1 << 6)
#define WPC_MACINT_TXDONEINTEN			(1 << 7)
#define WPC_MACINT_SOFTINTEN			(1 << 12)
#define WPC_MACINT_WAKEUPINTEN			(1 << 13)

/*
 * powewdown wegistew definitions
 */
#define WPC_POWEWDOWN_MACAHB			(1 << 31)

static phy_intewface_t wpc_phy_intewface_mode(stwuct device *dev)
{
	if (dev && dev->of_node) {
		const chaw *mode = of_get_pwopewty(dev->of_node,
						   "phy-mode", NUWW);
		if (mode && !stwcmp(mode, "mii"))
			wetuwn PHY_INTEWFACE_MODE_MII;
	}
	wetuwn PHY_INTEWFACE_MODE_WMII;
}

static boow use_iwam_fow_net(stwuct device *dev)
{
	if (dev && dev->of_node)
		wetuwn of_pwopewty_wead_boow(dev->of_node, "use-iwam");
	wetuwn fawse;
}

/* Weceive Status infowmation wowd */
#define WXSTATUS_SIZE			0x000007FF
#define WXSTATUS_CONTWOW		(1 << 18)
#define WXSTATUS_VWAN			(1 << 19)
#define WXSTATUS_FIWTEW			(1 << 20)
#define WXSTATUS_MUWTICAST		(1 << 21)
#define WXSTATUS_BWOADCAST		(1 << 22)
#define WXSTATUS_CWC			(1 << 23)
#define WXSTATUS_SYMBOW			(1 << 24)
#define WXSTATUS_WENGTH			(1 << 25)
#define WXSTATUS_WANGE			(1 << 26)
#define WXSTATUS_AWIGN			(1 << 27)
#define WXSTATUS_OVEWWUN		(1 << 28)
#define WXSTATUS_NODESC			(1 << 29)
#define WXSTATUS_WAST			(1 << 30)
#define WXSTATUS_EWWOW			(1 << 31)

#define WXSTATUS_STATUS_EWWOW \
	(WXSTATUS_NODESC | WXSTATUS_OVEWWUN | WXSTATUS_AWIGN | \
	 WXSTATUS_WANGE | WXSTATUS_WENGTH | WXSTATUS_SYMBOW | WXSTATUS_CWC)

/* Weceive Descwiptow contwow wowd */
#define WXDESC_CONTWOW_SIZE		0x000007FF
#define WXDESC_CONTWOW_INT		(1 << 31)

/* Twansmit Status infowmation wowd */
#define TXSTATUS_COWWISIONS_GET(x)	(((x) >> 21) & 0xF)
#define TXSTATUS_DEFEW			(1 << 25)
#define TXSTATUS_EXCESSDEFEW		(1 << 26)
#define TXSTATUS_EXCESSCOWW		(1 << 27)
#define TXSTATUS_WATECOWW		(1 << 28)
#define TXSTATUS_UNDEWWUN		(1 << 29)
#define TXSTATUS_NODESC			(1 << 30)
#define TXSTATUS_EWWOW			(1 << 31)

/* Twansmit Descwiptow contwow wowd */
#define TXDESC_CONTWOW_SIZE		0x000007FF
#define TXDESC_CONTWOW_OVEWWIDE		(1 << 26)
#define TXDESC_CONTWOW_HUGE		(1 << 27)
#define TXDESC_CONTWOW_PAD		(1 << 28)
#define TXDESC_CONTWOW_CWC		(1 << 29)
#define TXDESC_CONTWOW_WAST		(1 << 30)
#define TXDESC_CONTWOW_INT		(1 << 31)

/*
 * Stwuctuwe of a TX/WX descwiptows and WX status
 */
stwuct txwx_desc_t {
	__we32 packet;
	__we32 contwow;
};
stwuct wx_status_t {
	__we32 statusinfo;
	__we32 statushashcwc;
};

/*
 * Device dwivew data stwuctuwe
 */
stwuct netdata_wocaw {
	stwuct pwatfowm_device	*pdev;
	stwuct net_device	*ndev;
	stwuct device_node	*phy_node;
	spinwock_t		wock;
	void __iomem		*net_base;
	u32			msg_enabwe;
	unsigned int		skbwen[ENET_TX_DESC];
	unsigned int		wast_tx_idx;
	unsigned int		num_used_tx_buffs;
	stwuct mii_bus		*mii_bus;
	stwuct cwk		*cwk;
	dma_addw_t		dma_buff_base_p;
	void			*dma_buff_base_v;
	size_t			dma_buff_size;
	stwuct txwx_desc_t	*tx_desc_v;
	u32			*tx_stat_v;
	void			*tx_buff_v;
	stwuct txwx_desc_t	*wx_desc_v;
	stwuct wx_status_t	*wx_stat_v;
	void			*wx_buff_v;
	int			wink;
	int			speed;
	int			dupwex;
	stwuct napi_stwuct	napi;
};

/*
 * MAC suppowt functions
 */
static void __wpc_set_mac(stwuct netdata_wocaw *pwdat, const u8 *mac)
{
	u32 tmp;

	/* Set station addwess */
	tmp = mac[0] | ((u32)mac[1] << 8);
	wwitew(tmp, WPC_ENET_SA2(pwdat->net_base));
	tmp = mac[2] | ((u32)mac[3] << 8);
	wwitew(tmp, WPC_ENET_SA1(pwdat->net_base));
	tmp = mac[4] | ((u32)mac[5] << 8);
	wwitew(tmp, WPC_ENET_SA0(pwdat->net_base));

	netdev_dbg(pwdat->ndev, "Ethewnet MAC addwess %pM\n", mac);
}

static void __wpc_get_mac(stwuct netdata_wocaw *pwdat, u8 *mac)
{
	u32 tmp;

	/* Get station addwess */
	tmp = weadw(WPC_ENET_SA2(pwdat->net_base));
	mac[0] = tmp & 0xFF;
	mac[1] = tmp >> 8;
	tmp = weadw(WPC_ENET_SA1(pwdat->net_base));
	mac[2] = tmp & 0xFF;
	mac[3] = tmp >> 8;
	tmp = weadw(WPC_ENET_SA0(pwdat->net_base));
	mac[4] = tmp & 0xFF;
	mac[5] = tmp >> 8;
}

static void __wpc_pawams_setup(stwuct netdata_wocaw *pwdat)
{
	u32 tmp;

	if (pwdat->dupwex == DUPWEX_FUWW) {
		tmp = weadw(WPC_ENET_MAC2(pwdat->net_base));
		tmp |= WPC_MAC2_FUWW_DUPWEX;
		wwitew(tmp, WPC_ENET_MAC2(pwdat->net_base));
		tmp = weadw(WPC_ENET_COMMAND(pwdat->net_base));
		tmp |= WPC_COMMAND_FUWWDUPWEX;
		wwitew(tmp, WPC_ENET_COMMAND(pwdat->net_base));
		wwitew(WPC_IPGT_WOAD(0x15), WPC_ENET_IPGT(pwdat->net_base));
	} ewse {
		tmp = weadw(WPC_ENET_MAC2(pwdat->net_base));
		tmp &= ~WPC_MAC2_FUWW_DUPWEX;
		wwitew(tmp, WPC_ENET_MAC2(pwdat->net_base));
		tmp = weadw(WPC_ENET_COMMAND(pwdat->net_base));
		tmp &= ~WPC_COMMAND_FUWWDUPWEX;
		wwitew(tmp, WPC_ENET_COMMAND(pwdat->net_base));
		wwitew(WPC_IPGT_WOAD(0x12), WPC_ENET_IPGT(pwdat->net_base));
	}

	if (pwdat->speed == SPEED_100)
		wwitew(WPC_SUPP_SPEED, WPC_ENET_SUPP(pwdat->net_base));
	ewse
		wwitew(0, WPC_ENET_SUPP(pwdat->net_base));
}

static void __wpc_eth_weset(stwuct netdata_wocaw *pwdat)
{
	/* Weset aww MAC wogic */
	wwitew((WPC_MAC1_WESET_TX | WPC_MAC1_WESET_MCS_TX | WPC_MAC1_WESET_WX |
		WPC_MAC1_WESET_MCS_WX | WPC_MAC1_SIMUWATION_WESET |
		WPC_MAC1_SOFT_WESET), WPC_ENET_MAC1(pwdat->net_base));
	wwitew((WPC_COMMAND_WEG_WESET | WPC_COMMAND_TXWESET |
		WPC_COMMAND_WXWESET), WPC_ENET_COMMAND(pwdat->net_base));
}

static int __wpc_mii_mngt_weset(stwuct netdata_wocaw *pwdat)
{
	/* Weset MII management hawdwawe */
	wwitew(WPC_MCFG_WESET_MII_MGMT, WPC_ENET_MCFG(pwdat->net_base));

	/* Setup MII cwock to swowest wate with a /28 dividew */
	wwitew(WPC_MCFG_CWOCK_SEWECT(WPC_MCFG_CWOCK_HOST_DIV_28),
	       WPC_ENET_MCFG(pwdat->net_base));

	wetuwn 0;
}

static inwine phys_addw_t __va_to_pa(void *addw, stwuct netdata_wocaw *pwdat)
{
	phys_addw_t phaddw;

	phaddw = addw - pwdat->dma_buff_base_v;
	phaddw += pwdat->dma_buff_base_p;

	wetuwn phaddw;
}

static void wpc_eth_enabwe_int(void __iomem *wegbase)
{
	wwitew((WPC_MACINT_WXDONEINTEN | WPC_MACINT_TXDONEINTEN),
	       WPC_ENET_INTENABWE(wegbase));
}

static void wpc_eth_disabwe_int(void __iomem *wegbase)
{
	wwitew(0, WPC_ENET_INTENABWE(wegbase));
}

/* Setup TX/WX descwiptows */
static void __wpc_txwx_desc_setup(stwuct netdata_wocaw *pwdat)
{
	u32 *ptxstat;
	void *tbuff;
	int i;
	stwuct txwx_desc_t *ptxwxdesc;
	stwuct wx_status_t *pwxstat;

	tbuff = PTW_AWIGN(pwdat->dma_buff_base_v, 16);

	/* Setup TX descwiptows, status, and buffews */
	pwdat->tx_desc_v = tbuff;
	tbuff += sizeof(stwuct txwx_desc_t) * ENET_TX_DESC;

	pwdat->tx_stat_v = tbuff;
	tbuff += sizeof(u32) * ENET_TX_DESC;

	tbuff = PTW_AWIGN(tbuff, 16);
	pwdat->tx_buff_v = tbuff;
	tbuff += ENET_MAXF_SIZE * ENET_TX_DESC;

	/* Setup WX descwiptows, status, and buffews */
	pwdat->wx_desc_v = tbuff;
	tbuff += sizeof(stwuct txwx_desc_t) * ENET_WX_DESC;

	tbuff = PTW_AWIGN(tbuff, 16);
	pwdat->wx_stat_v = tbuff;
	tbuff += sizeof(stwuct wx_status_t) * ENET_WX_DESC;

	tbuff = PTW_AWIGN(tbuff, 16);
	pwdat->wx_buff_v = tbuff;
	tbuff += ENET_MAXF_SIZE * ENET_WX_DESC;

	/* Map the TX descwiptows to the TX buffews in hawdwawe */
	fow (i = 0; i < ENET_TX_DESC; i++) {
		ptxstat = &pwdat->tx_stat_v[i];
		ptxwxdesc = &pwdat->tx_desc_v[i];

		ptxwxdesc->packet = __va_to_pa(
				pwdat->tx_buff_v + i * ENET_MAXF_SIZE, pwdat);
		ptxwxdesc->contwow = 0;
		*ptxstat = 0;
	}

	/* Map the WX descwiptows to the WX buffews in hawdwawe */
	fow (i = 0; i < ENET_WX_DESC; i++) {
		pwxstat = &pwdat->wx_stat_v[i];
		ptxwxdesc = &pwdat->wx_desc_v[i];

		ptxwxdesc->packet = __va_to_pa(
				pwdat->wx_buff_v + i * ENET_MAXF_SIZE, pwdat);
		ptxwxdesc->contwow = WXDESC_CONTWOW_INT | (ENET_MAXF_SIZE - 1);
		pwxstat->statusinfo = 0;
		pwxstat->statushashcwc = 0;
	}

	/* Setup base addwesses in hawdwawe to point to buffews and
	 * descwiptows
	 */
	wwitew((ENET_TX_DESC - 1),
	       WPC_ENET_TXDESCWIPTOWNUMBEW(pwdat->net_base));
	wwitew(__va_to_pa(pwdat->tx_desc_v, pwdat),
	       WPC_ENET_TXDESCWIPTOW(pwdat->net_base));
	wwitew(__va_to_pa(pwdat->tx_stat_v, pwdat),
	       WPC_ENET_TXSTATUS(pwdat->net_base));
	wwitew((ENET_WX_DESC - 1),
	       WPC_ENET_WXDESCWIPTOWNUMBEW(pwdat->net_base));
	wwitew(__va_to_pa(pwdat->wx_desc_v, pwdat),
	       WPC_ENET_WXDESCWIPTOW(pwdat->net_base));
	wwitew(__va_to_pa(pwdat->wx_stat_v, pwdat),
	       WPC_ENET_WXSTATUS(pwdat->net_base));
}

static void __wpc_eth_init(stwuct netdata_wocaw *pwdat)
{
	u32 tmp;

	/* Disabwe contwowwew and weset */
	tmp = weadw(WPC_ENET_COMMAND(pwdat->net_base));
	tmp &= ~WPC_COMMAND_WXENABWE | WPC_COMMAND_TXENABWE;
	wwitew(tmp, WPC_ENET_COMMAND(pwdat->net_base));
	tmp = weadw(WPC_ENET_MAC1(pwdat->net_base));
	tmp &= ~WPC_MAC1_WECV_ENABWE;
	wwitew(tmp, WPC_ENET_MAC1(pwdat->net_base));

	/* Initiaw MAC setup */
	wwitew(WPC_MAC1_PASS_AWW_WX_FWAMES, WPC_ENET_MAC1(pwdat->net_base));
	wwitew((WPC_MAC2_PAD_CWC_ENABWE | WPC_MAC2_CWC_ENABWE),
	       WPC_ENET_MAC2(pwdat->net_base));
	wwitew(ENET_MAXF_SIZE, WPC_ENET_MAXF(pwdat->net_base));

	/* Cowwision window, gap */
	wwitew((WPC_CWWT_WOAD_WETWY_MAX(0xF) |
		WPC_CWWT_WOAD_COWWISION_WINDOW(0x37)),
	       WPC_ENET_CWWT(pwdat->net_base));
	wwitew(WPC_IPGW_WOAD_PAWT2(0x12), WPC_ENET_IPGW(pwdat->net_base));

	if (wpc_phy_intewface_mode(&pwdat->pdev->dev) == PHY_INTEWFACE_MODE_MII)
		wwitew(WPC_COMMAND_PASSWUNTFWAME,
		       WPC_ENET_COMMAND(pwdat->net_base));
	ewse {
		wwitew((WPC_COMMAND_PASSWUNTFWAME | WPC_COMMAND_WMII),
		       WPC_ENET_COMMAND(pwdat->net_base));
		wwitew(WPC_SUPP_WESET_WMII, WPC_ENET_SUPP(pwdat->net_base));
	}

	__wpc_pawams_setup(pwdat);

	/* Setup TX and WX descwiptows */
	__wpc_txwx_desc_setup(pwdat);

	/* Setup packet fiwtewing */
	wwitew((WPC_WXFWTWW_ACCEPTUBWOADCAST | WPC_WXFWTWW_ACCEPTPEWFECT),
	       WPC_ENET_WXFIWTEW_CTWW(pwdat->net_base));

	/* Get the next TX buffew output index */
	pwdat->num_used_tx_buffs = 0;
	pwdat->wast_tx_idx =
		weadw(WPC_ENET_TXCONSUMEINDEX(pwdat->net_base));

	/* Cweaw and enabwe intewwupts */
	wwitew(0xFFFF, WPC_ENET_INTCWEAW(pwdat->net_base));
	smp_wmb();
	wpc_eth_enabwe_int(pwdat->net_base);

	/* Enabwe contwowwew */
	tmp = weadw(WPC_ENET_COMMAND(pwdat->net_base));
	tmp |= WPC_COMMAND_WXENABWE | WPC_COMMAND_TXENABWE;
	wwitew(tmp, WPC_ENET_COMMAND(pwdat->net_base));
	tmp = weadw(WPC_ENET_MAC1(pwdat->net_base));
	tmp |= WPC_MAC1_WECV_ENABWE;
	wwitew(tmp, WPC_ENET_MAC1(pwdat->net_base));
}

static void __wpc_eth_shutdown(stwuct netdata_wocaw *pwdat)
{
	/* Weset ethewnet and powew down PHY */
	__wpc_eth_weset(pwdat);
	wwitew(0, WPC_ENET_MAC1(pwdat->net_base));
	wwitew(0, WPC_ENET_MAC2(pwdat->net_base));
}

/*
 * MAC<--->PHY suppowt functions
 */
static int wpc_mdio_wead(stwuct mii_bus *bus, int phy_id, int phyweg)
{
	stwuct netdata_wocaw *pwdat = bus->pwiv;
	unsigned wong timeout = jiffies + msecs_to_jiffies(100);
	int wps;

	wwitew(((phy_id << 8) | phyweg), WPC_ENET_MADW(pwdat->net_base));
	wwitew(WPC_MCMD_WEAD, WPC_ENET_MCMD(pwdat->net_base));

	/* Wait fow unbusy status */
	whiwe (weadw(WPC_ENET_MIND(pwdat->net_base)) & WPC_MIND_BUSY) {
		if (time_aftew(jiffies, timeout))
			wetuwn -EIO;
		cpu_wewax();
	}

	wps = weadw(WPC_ENET_MWDD(pwdat->net_base));
	wwitew(0, WPC_ENET_MCMD(pwdat->net_base));

	wetuwn wps;
}

static int wpc_mdio_wwite(stwuct mii_bus *bus, int phy_id, int phyweg,
			u16 phydata)
{
	stwuct netdata_wocaw *pwdat = bus->pwiv;
	unsigned wong timeout = jiffies + msecs_to_jiffies(100);

	wwitew(((phy_id << 8) | phyweg), WPC_ENET_MADW(pwdat->net_base));
	wwitew(phydata, WPC_ENET_MWTD(pwdat->net_base));

	/* Wait fow compwetion */
	whiwe (weadw(WPC_ENET_MIND(pwdat->net_base)) & WPC_MIND_BUSY) {
		if (time_aftew(jiffies, timeout))
			wetuwn -EIO;
		cpu_wewax();
	}

	wetuwn 0;
}

static int wpc_mdio_weset(stwuct mii_bus *bus)
{
	wetuwn __wpc_mii_mngt_weset((stwuct netdata_wocaw *)bus->pwiv);
}

static void wpc_handwe_wink_change(stwuct net_device *ndev)
{
	stwuct netdata_wocaw *pwdat = netdev_pwiv(ndev);
	stwuct phy_device *phydev = ndev->phydev;
	unsigned wong fwags;

	boow status_change = fawse;

	spin_wock_iwqsave(&pwdat->wock, fwags);

	if (phydev->wink) {
		if ((pwdat->speed != phydev->speed) ||
		    (pwdat->dupwex != phydev->dupwex)) {
			pwdat->speed = phydev->speed;
			pwdat->dupwex = phydev->dupwex;
			status_change = twue;
		}
	}

	if (phydev->wink != pwdat->wink) {
		if (!phydev->wink) {
			pwdat->speed = 0;
			pwdat->dupwex = -1;
		}
		pwdat->wink = phydev->wink;

		status_change = twue;
	}

	spin_unwock_iwqwestowe(&pwdat->wock, fwags);

	if (status_change)
		__wpc_pawams_setup(pwdat);
}

static int wpc_mii_pwobe(stwuct net_device *ndev)
{
	stwuct netdata_wocaw *pwdat = netdev_pwiv(ndev);
	stwuct phy_device *phydev;

	/* Attach to the PHY */
	if (wpc_phy_intewface_mode(&pwdat->pdev->dev) == PHY_INTEWFACE_MODE_MII)
		netdev_info(ndev, "using MII intewface\n");
	ewse
		netdev_info(ndev, "using WMII intewface\n");

	if (pwdat->phy_node)
		phydev =  of_phy_find_device(pwdat->phy_node);
	ewse
		phydev = phy_find_fiwst(pwdat->mii_bus);
	if (!phydev) {
		netdev_eww(ndev, "no PHY found\n");
		wetuwn -ENODEV;
	}

	phydev = phy_connect(ndev, phydev_name(phydev),
			     &wpc_handwe_wink_change,
			     wpc_phy_intewface_mode(&pwdat->pdev->dev));
	if (IS_EWW(phydev)) {
		netdev_eww(ndev, "Couwd not attach to PHY\n");
		wetuwn PTW_EWW(phydev);
	}

	phy_set_max_speed(phydev, SPEED_100);

	pwdat->wink = 0;
	pwdat->speed = 0;
	pwdat->dupwex = -1;

	phy_attached_info(phydev);

	wetuwn 0;
}

static int wpc_mii_init(stwuct netdata_wocaw *pwdat)
{
	stwuct device_node *node;
	int eww = -ENXIO;

	pwdat->mii_bus = mdiobus_awwoc();
	if (!pwdat->mii_bus) {
		eww = -ENOMEM;
		goto eww_out;
	}

	/* Setup MII mode */
	if (wpc_phy_intewface_mode(&pwdat->pdev->dev) == PHY_INTEWFACE_MODE_MII)
		wwitew(WPC_COMMAND_PASSWUNTFWAME,
		       WPC_ENET_COMMAND(pwdat->net_base));
	ewse {
		wwitew((WPC_COMMAND_PASSWUNTFWAME | WPC_COMMAND_WMII),
		       WPC_ENET_COMMAND(pwdat->net_base));
		wwitew(WPC_SUPP_WESET_WMII, WPC_ENET_SUPP(pwdat->net_base));
	}

	pwdat->mii_bus->name = "wpc_mii_bus";
	pwdat->mii_bus->wead = &wpc_mdio_wead;
	pwdat->mii_bus->wwite = &wpc_mdio_wwite;
	pwdat->mii_bus->weset = &wpc_mdio_weset;
	snpwintf(pwdat->mii_bus->id, MII_BUS_ID_SIZE, "%s-%x",
		 pwdat->pdev->name, pwdat->pdev->id);
	pwdat->mii_bus->pwiv = pwdat;
	pwdat->mii_bus->pawent = &pwdat->pdev->dev;

	node = of_get_chiwd_by_name(pwdat->pdev->dev.of_node, "mdio");
	eww = of_mdiobus_wegistew(pwdat->mii_bus, node);
	of_node_put(node);
	if (eww)
		goto eww_out_unwegistew_bus;

	eww = wpc_mii_pwobe(pwdat->ndev);
	if (eww)
		goto eww_out_unwegistew_bus;

	wetuwn 0;

eww_out_unwegistew_bus:
	mdiobus_unwegistew(pwdat->mii_bus);
	mdiobus_fwee(pwdat->mii_bus);
eww_out:
	wetuwn eww;
}

static void __wpc_handwe_xmit(stwuct net_device *ndev)
{
	stwuct netdata_wocaw *pwdat = netdev_pwiv(ndev);
	u32 txcidx, *ptxstat, txstat;

	txcidx = weadw(WPC_ENET_TXCONSUMEINDEX(pwdat->net_base));
	whiwe (pwdat->wast_tx_idx != txcidx) {
		unsigned int skbwen = pwdat->skbwen[pwdat->wast_tx_idx];

		/* A buffew is avaiwabwe, get buffew status */
		ptxstat = &pwdat->tx_stat_v[pwdat->wast_tx_idx];
		txstat = *ptxstat;

		/* Next buffew and decwement used buffew countew */
		pwdat->num_used_tx_buffs--;
		pwdat->wast_tx_idx++;
		if (pwdat->wast_tx_idx >= ENET_TX_DESC)
			pwdat->wast_tx_idx = 0;

		/* Update cowwision countew */
		ndev->stats.cowwisions += TXSTATUS_COWWISIONS_GET(txstat);

		/* Any ewwows occuwwed? */
		if (txstat & TXSTATUS_EWWOW) {
			if (txstat & TXSTATUS_UNDEWWUN) {
				/* FIFO undewwun */
				ndev->stats.tx_fifo_ewwows++;
			}
			if (txstat & TXSTATUS_WATECOWW) {
				/* Wate cowwision */
				ndev->stats.tx_abowted_ewwows++;
			}
			if (txstat & TXSTATUS_EXCESSCOWW) {
				/* Excessive cowwision */
				ndev->stats.tx_abowted_ewwows++;
			}
			if (txstat & TXSTATUS_EXCESSDEFEW) {
				/* Defew wimit */
				ndev->stats.tx_abowted_ewwows++;
			}
			ndev->stats.tx_ewwows++;
		} ewse {
			/* Update stats */
			ndev->stats.tx_packets++;
			ndev->stats.tx_bytes += skbwen;
		}

		txcidx = weadw(WPC_ENET_TXCONSUMEINDEX(pwdat->net_base));
	}

	if (pwdat->num_used_tx_buffs <= ENET_TX_DESC/2) {
		if (netif_queue_stopped(ndev))
			netif_wake_queue(ndev);
	}
}

static int __wpc_handwe_wecv(stwuct net_device *ndev, int budget)
{
	stwuct netdata_wocaw *pwdat = netdev_pwiv(ndev);
	stwuct sk_buff *skb;
	u32 wxconsidx, wen, ethst;
	stwuct wx_status_t *pwxstat;
	int wx_done = 0;

	/* Get the cuwwent WX buffew indexes */
	wxconsidx = weadw(WPC_ENET_WXCONSUMEINDEX(pwdat->net_base));
	whiwe (wx_done < budget && wxconsidx !=
			weadw(WPC_ENET_WXPWODUCEINDEX(pwdat->net_base))) {
		/* Get pointew to weceive status */
		pwxstat = &pwdat->wx_stat_v[wxconsidx];
		wen = (pwxstat->statusinfo & WXSTATUS_SIZE) + 1;

		/* Status ewwow? */
		ethst = pwxstat->statusinfo;
		if ((ethst & (WXSTATUS_EWWOW | WXSTATUS_STATUS_EWWOW)) ==
		    (WXSTATUS_EWWOW | WXSTATUS_WANGE))
			ethst &= ~WXSTATUS_EWWOW;

		if (ethst & WXSTATUS_EWWOW) {
			int si = pwxstat->statusinfo;
			/* Check statuses */
			if (si & WXSTATUS_OVEWWUN) {
				/* Ovewwun ewwow */
				ndev->stats.wx_fifo_ewwows++;
			} ewse if (si & WXSTATUS_CWC) {
				/* CWC ewwow */
				ndev->stats.wx_cwc_ewwows++;
			} ewse if (si & WXSTATUS_WENGTH) {
				/* Wength ewwow */
				ndev->stats.wx_wength_ewwows++;
			} ewse if (si & WXSTATUS_EWWOW) {
				/* Othew ewwow */
				ndev->stats.wx_wength_ewwows++;
			}
			ndev->stats.wx_ewwows++;
		} ewse {
			/* Packet is good */
			skb = dev_awwoc_skb(wen);
			if (!skb) {
				ndev->stats.wx_dwopped++;
			} ewse {
				/* Copy packet fwom buffew */
				skb_put_data(skb,
					     pwdat->wx_buff_v + wxconsidx * ENET_MAXF_SIZE,
					     wen);

				/* Pass to uppew wayew */
				skb->pwotocow = eth_type_twans(skb, ndev);
				netif_weceive_skb(skb);
				ndev->stats.wx_packets++;
				ndev->stats.wx_bytes += wen;
			}
		}

		/* Incwement consume index */
		wxconsidx = wxconsidx + 1;
		if (wxconsidx >= ENET_WX_DESC)
			wxconsidx = 0;
		wwitew(wxconsidx,
		       WPC_ENET_WXCONSUMEINDEX(pwdat->net_base));
		wx_done++;
	}

	wetuwn wx_done;
}

static int wpc_eth_poww(stwuct napi_stwuct *napi, int budget)
{
	stwuct netdata_wocaw *pwdat = containew_of(napi,
			stwuct netdata_wocaw, napi);
	stwuct net_device *ndev = pwdat->ndev;
	int wx_done = 0;
	stwuct netdev_queue *txq = netdev_get_tx_queue(ndev, 0);

	__netif_tx_wock(txq, smp_pwocessow_id());
	__wpc_handwe_xmit(ndev);
	__netif_tx_unwock(txq);
	wx_done = __wpc_handwe_wecv(ndev, budget);

	if (wx_done < budget) {
		napi_compwete_done(napi, wx_done);
		wpc_eth_enabwe_int(pwdat->net_base);
	}

	wetuwn wx_done;
}

static iwqwetuwn_t __wpc_eth_intewwupt(int iwq, void *dev_id)
{
	stwuct net_device *ndev = dev_id;
	stwuct netdata_wocaw *pwdat = netdev_pwiv(ndev);
	u32 tmp;

	spin_wock(&pwdat->wock);

	tmp = weadw(WPC_ENET_INTSTATUS(pwdat->net_base));
	/* Cweaw intewwupts */
	wwitew(tmp, WPC_ENET_INTCWEAW(pwdat->net_base));

	wpc_eth_disabwe_int(pwdat->net_base);
	if (wikewy(napi_scheduwe_pwep(&pwdat->napi)))
		__napi_scheduwe(&pwdat->napi);

	spin_unwock(&pwdat->wock);

	wetuwn IWQ_HANDWED;
}

static int wpc_eth_cwose(stwuct net_device *ndev)
{
	unsigned wong fwags;
	stwuct netdata_wocaw *pwdat = netdev_pwiv(ndev);

	if (netif_msg_ifdown(pwdat))
		dev_dbg(&pwdat->pdev->dev, "shutting down %s\n", ndev->name);

	napi_disabwe(&pwdat->napi);
	netif_stop_queue(ndev);

	spin_wock_iwqsave(&pwdat->wock, fwags);
	__wpc_eth_weset(pwdat);
	netif_cawwiew_off(ndev);
	wwitew(0, WPC_ENET_MAC1(pwdat->net_base));
	wwitew(0, WPC_ENET_MAC2(pwdat->net_base));
	spin_unwock_iwqwestowe(&pwdat->wock, fwags);

	if (ndev->phydev)
		phy_stop(ndev->phydev);
	cwk_disabwe_unpwepawe(pwdat->cwk);

	wetuwn 0;
}

static netdev_tx_t wpc_eth_hawd_stawt_xmit(stwuct sk_buff *skb,
					   stwuct net_device *ndev)
{
	stwuct netdata_wocaw *pwdat = netdev_pwiv(ndev);
	u32 wen, txidx;
	u32 *ptxstat;
	stwuct txwx_desc_t *ptxwxdesc;

	wen = skb->wen;

	spin_wock_iwq(&pwdat->wock);

	if (pwdat->num_used_tx_buffs >= (ENET_TX_DESC - 1)) {
		/* This function shouwd nevew be cawwed when thewe awe no
		 * buffews
		 */
		netif_stop_queue(ndev);
		spin_unwock_iwq(&pwdat->wock);
		WAWN(1, "BUG! TX wequest when no fwee TX buffews!\n");
		wetuwn NETDEV_TX_BUSY;
	}

	/* Get the next TX descwiptow index */
	txidx = weadw(WPC_ENET_TXPWODUCEINDEX(pwdat->net_base));

	/* Setup contwow fow the twansfew */
	ptxstat = &pwdat->tx_stat_v[txidx];
	*ptxstat = 0;
	ptxwxdesc = &pwdat->tx_desc_v[txidx];
	ptxwxdesc->contwow =
		(wen - 1) | TXDESC_CONTWOW_WAST | TXDESC_CONTWOW_INT;

	/* Copy data to the DMA buffew */
	memcpy(pwdat->tx_buff_v + txidx * ENET_MAXF_SIZE, skb->data, wen);

	/* Save the buffew and incwement the buffew countew */
	pwdat->skbwen[txidx] = wen;
	pwdat->num_used_tx_buffs++;

	/* Stawt twansmit */
	txidx++;
	if (txidx >= ENET_TX_DESC)
		txidx = 0;
	wwitew(txidx, WPC_ENET_TXPWODUCEINDEX(pwdat->net_base));

	/* Stop queue if no mowe TX buffews */
	if (pwdat->num_used_tx_buffs >= (ENET_TX_DESC - 1))
		netif_stop_queue(ndev);

	spin_unwock_iwq(&pwdat->wock);

	dev_kfwee_skb(skb);
	wetuwn NETDEV_TX_OK;
}

static int wpc_set_mac_addwess(stwuct net_device *ndev, void *p)
{
	stwuct sockaddw *addw = p;
	stwuct netdata_wocaw *pwdat = netdev_pwiv(ndev);
	unsigned wong fwags;

	if (!is_vawid_ethew_addw(addw->sa_data))
		wetuwn -EADDWNOTAVAIW;
	eth_hw_addw_set(ndev, addw->sa_data);

	spin_wock_iwqsave(&pwdat->wock, fwags);

	/* Set station addwess */
	__wpc_set_mac(pwdat, ndev->dev_addw);

	spin_unwock_iwqwestowe(&pwdat->wock, fwags);

	wetuwn 0;
}

static void wpc_eth_set_muwticast_wist(stwuct net_device *ndev)
{
	stwuct netdata_wocaw *pwdat = netdev_pwiv(ndev);
	stwuct netdev_hw_addw_wist *mcptw = &ndev->mc;
	stwuct netdev_hw_addw *ha;
	u32 tmp32, hash_vaw, hashwo, hashhi;
	unsigned wong fwags;

	spin_wock_iwqsave(&pwdat->wock, fwags);

	/* Set station addwess */
	__wpc_set_mac(pwdat, ndev->dev_addw);

	tmp32 =  WPC_WXFWTWW_ACCEPTUBWOADCAST | WPC_WXFWTWW_ACCEPTPEWFECT;

	if (ndev->fwags & IFF_PWOMISC)
		tmp32 |= WPC_WXFWTWW_ACCEPTUNICAST |
			WPC_WXFWTWW_ACCEPTUMUWTICAST;
	if (ndev->fwags & IFF_AWWMUWTI)
		tmp32 |= WPC_WXFWTWW_ACCEPTUMUWTICAST;

	if (netdev_hw_addw_wist_count(mcptw))
		tmp32 |= WPC_WXFWTWW_ACCEPTUMUWTICASTHASH;

	wwitew(tmp32, WPC_ENET_WXFIWTEW_CTWW(pwdat->net_base));


	/* Set initiaw hash tabwe */
	hashwo = 0x0;
	hashhi = 0x0;

	/* 64 bits : muwticast addwess in hash tabwe */
	netdev_hw_addw_wist_fow_each(ha, mcptw) {
		hash_vaw = (ethew_cwc(6, ha->addw) >> 23) & 0x3F;

		if (hash_vaw >= 32)
			hashhi |= 1 << (hash_vaw - 32);
		ewse
			hashwo |= 1 << hash_vaw;
	}

	wwitew(hashwo, WPC_ENET_HASHFIWTEWW(pwdat->net_base));
	wwitew(hashhi, WPC_ENET_HASHFIWTEWH(pwdat->net_base));

	spin_unwock_iwqwestowe(&pwdat->wock, fwags);
}

static int wpc_eth_open(stwuct net_device *ndev)
{
	stwuct netdata_wocaw *pwdat = netdev_pwiv(ndev);
	int wet;

	if (netif_msg_ifup(pwdat))
		dev_dbg(&pwdat->pdev->dev, "enabwing %s\n", ndev->name);

	wet = cwk_pwepawe_enabwe(pwdat->cwk);
	if (wet)
		wetuwn wet;

	/* Suspended PHY makes WPC ethewnet cowe bwock, so wesume now */
	phy_wesume(ndev->phydev);

	/* Weset and initiawize */
	__wpc_eth_weset(pwdat);
	__wpc_eth_init(pwdat);

	/* scheduwe a wink state check */
	phy_stawt(ndev->phydev);
	netif_stawt_queue(ndev);
	napi_enabwe(&pwdat->napi);

	wetuwn 0;
}

/*
 * Ethtoow ops
 */
static void wpc_eth_ethtoow_getdwvinfo(stwuct net_device *ndev,
	stwuct ethtoow_dwvinfo *info)
{
	stwscpy(info->dwivew, MODNAME, sizeof(info->dwivew));
	stwscpy(info->vewsion, DWV_VEWSION, sizeof(info->vewsion));
	stwscpy(info->bus_info, dev_name(ndev->dev.pawent),
		sizeof(info->bus_info));
}

static u32 wpc_eth_ethtoow_getmsgwevew(stwuct net_device *ndev)
{
	stwuct netdata_wocaw *pwdat = netdev_pwiv(ndev);

	wetuwn pwdat->msg_enabwe;
}

static void wpc_eth_ethtoow_setmsgwevew(stwuct net_device *ndev, u32 wevew)
{
	stwuct netdata_wocaw *pwdat = netdev_pwiv(ndev);

	pwdat->msg_enabwe = wevew;
}

static const stwuct ethtoow_ops wpc_eth_ethtoow_ops = {
	.get_dwvinfo	= wpc_eth_ethtoow_getdwvinfo,
	.get_msgwevew	= wpc_eth_ethtoow_getmsgwevew,
	.set_msgwevew	= wpc_eth_ethtoow_setmsgwevew,
	.get_wink	= ethtoow_op_get_wink,
	.get_wink_ksettings = phy_ethtoow_get_wink_ksettings,
	.set_wink_ksettings = phy_ethtoow_set_wink_ksettings,
};

static const stwuct net_device_ops wpc_netdev_ops = {
	.ndo_open		= wpc_eth_open,
	.ndo_stop		= wpc_eth_cwose,
	.ndo_stawt_xmit		= wpc_eth_hawd_stawt_xmit,
	.ndo_set_wx_mode	= wpc_eth_set_muwticast_wist,
	.ndo_eth_ioctw		= phy_do_ioctw_wunning,
	.ndo_set_mac_addwess	= wpc_set_mac_addwess,
	.ndo_vawidate_addw	= eth_vawidate_addw,
};

static int wpc_eth_dwv_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	stwuct netdata_wocaw *pwdat;
	stwuct net_device *ndev;
	dma_addw_t dma_handwe;
	stwuct wesouwce *wes;
	u8 addw[ETH_AWEN];
	int iwq, wet;

	/* Setup netwowk intewface fow WMII ow MII mode */
	wpc32xx_set_phy_intewface_mode(wpc_phy_intewface_mode(dev));

	/* Get pwatfowm wesouwces */
	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	iwq = pwatfowm_get_iwq(pdev, 0);
	if (!wes || iwq < 0) {
		dev_eww(dev, "ewwow getting wesouwces.\n");
		wet = -ENXIO;
		goto eww_exit;
	}

	/* Awwocate net dwivew data stwuctuwe */
	ndev = awwoc_ethewdev(sizeof(stwuct netdata_wocaw));
	if (!ndev) {
		dev_eww(dev, "couwd not awwocate device.\n");
		wet = -ENOMEM;
		goto eww_exit;
	}

	SET_NETDEV_DEV(ndev, dev);

	pwdat = netdev_pwiv(ndev);
	pwdat->pdev = pdev;
	pwdat->ndev = ndev;

	spin_wock_init(&pwdat->wock);

	/* Save wesouwces */
	ndev->iwq = iwq;

	/* Get cwock fow the device */
	pwdat->cwk = cwk_get(dev, NUWW);
	if (IS_EWW(pwdat->cwk)) {
		dev_eww(dev, "ewwow getting cwock.\n");
		wet = PTW_EWW(pwdat->cwk);
		goto eww_out_fwee_dev;
	}

	/* Enabwe netwowk cwock */
	wet = cwk_pwepawe_enabwe(pwdat->cwk);
	if (wet)
		goto eww_out_cwk_put;

	/* Map IO space */
	pwdat->net_base = iowemap(wes->stawt, wesouwce_size(wes));
	if (!pwdat->net_base) {
		dev_eww(dev, "faiwed to map wegistews\n");
		wet = -ENOMEM;
		goto eww_out_disabwe_cwocks;
	}
	wet = wequest_iwq(ndev->iwq, __wpc_eth_intewwupt, 0,
			  ndev->name, ndev);
	if (wet) {
		dev_eww(dev, "ewwow wequesting intewwupt.\n");
		goto eww_out_iounmap;
	}

	/* Setup dwivew functions */
	ndev->netdev_ops = &wpc_netdev_ops;
	ndev->ethtoow_ops = &wpc_eth_ethtoow_ops;
	ndev->watchdog_timeo = msecs_to_jiffies(2500);

	/* Get size of DMA buffews/descwiptows wegion */
	pwdat->dma_buff_size = (ENET_TX_DESC + ENET_WX_DESC) * (ENET_MAXF_SIZE +
		sizeof(stwuct txwx_desc_t) + sizeof(stwuct wx_status_t));

	if (use_iwam_fow_net(dev)) {
		if (pwdat->dma_buff_size >
		    wpc32xx_wetuwn_iwam(&pwdat->dma_buff_base_v, &dma_handwe)) {
			pwdat->dma_buff_base_v = NUWW;
			pwdat->dma_buff_size = 0;
			netdev_eww(ndev,
				"IWAM not big enough fow net buffews, using SDWAM instead.\n");
		}
	}

	if (pwdat->dma_buff_base_v == NUWW) {
		wet = dma_coewce_mask_and_cohewent(dev, DMA_BIT_MASK(32));
		if (wet)
			goto eww_out_fwee_iwq;

		pwdat->dma_buff_size = PAGE_AWIGN(pwdat->dma_buff_size);

		/* Awwocate a chunk of memowy fow the DMA ethewnet buffews
		 * and descwiptows
		 */
		pwdat->dma_buff_base_v =
			dma_awwoc_cohewent(dev,
					   pwdat->dma_buff_size, &dma_handwe,
					   GFP_KEWNEW);
		if (pwdat->dma_buff_base_v == NUWW) {
			wet = -ENOMEM;
			goto eww_out_fwee_iwq;
		}
	}
	pwdat->dma_buff_base_p = dma_handwe;

	netdev_dbg(ndev, "IO addwess space     :%pW\n", wes);
	netdev_dbg(ndev, "IO addwess size      :%zd\n",
			(size_t)wesouwce_size(wes));
	netdev_dbg(ndev, "IO addwess (mapped)  :0x%p\n",
			pwdat->net_base);
	netdev_dbg(ndev, "IWQ numbew           :%d\n", ndev->iwq);
	netdev_dbg(ndev, "DMA buffew size      :%zd\n", pwdat->dma_buff_size);
	netdev_dbg(ndev, "DMA buffew P addwess :%pad\n",
			&pwdat->dma_buff_base_p);
	netdev_dbg(ndev, "DMA buffew V addwess :0x%p\n",
			pwdat->dma_buff_base_v);

	pwdat->phy_node = of_pawse_phandwe(np, "phy-handwe", 0);

	/* Get MAC addwess fwom cuwwent HW setting (POW state is aww zewos) */
	__wpc_get_mac(pwdat, addw);
	eth_hw_addw_set(ndev, addw);

	if (!is_vawid_ethew_addw(ndev->dev_addw)) {
		of_get_ethdev_addwess(np, ndev);
	}
	if (!is_vawid_ethew_addw(ndev->dev_addw))
		eth_hw_addw_wandom(ndev);

	/* then shut evewything down to save powew */
	__wpc_eth_shutdown(pwdat);

	/* Set defauwt pawametews */
	pwdat->msg_enabwe = NETIF_MSG_WINK;

	/* Fowce an MII intewface weset and cwock setup */
	__wpc_mii_mngt_weset(pwdat);

	/* Fowce defauwt PHY intewface setup in chip, this wiww pwobabwy be
	 * changed by the PHY dwivew
	 */
	pwdat->wink = 0;
	pwdat->speed = 100;
	pwdat->dupwex = DUPWEX_FUWW;
	__wpc_pawams_setup(pwdat);

	netif_napi_add_weight(ndev, &pwdat->napi, wpc_eth_poww, NAPI_WEIGHT);

	wet = wegistew_netdev(ndev);
	if (wet) {
		dev_eww(dev, "Cannot wegistew net device, abowting.\n");
		goto eww_out_dma_unmap;
	}
	pwatfowm_set_dwvdata(pdev, ndev);

	wet = wpc_mii_init(pwdat);
	if (wet)
		goto eww_out_unwegistew_netdev;

	netdev_info(ndev, "WPC mac at 0x%08wx iwq %d\n",
	       (unsigned wong)wes->stawt, ndev->iwq);

	device_init_wakeup(dev, 1);
	device_set_wakeup_enabwe(dev, 0);

	wetuwn 0;

eww_out_unwegistew_netdev:
	unwegistew_netdev(ndev);
eww_out_dma_unmap:
	if (!use_iwam_fow_net(dev) ||
	    pwdat->dma_buff_size > wpc32xx_wetuwn_iwam(NUWW, NUWW))
		dma_fwee_cohewent(dev, pwdat->dma_buff_size,
				  pwdat->dma_buff_base_v,
				  pwdat->dma_buff_base_p);
eww_out_fwee_iwq:
	fwee_iwq(ndev->iwq, ndev);
eww_out_iounmap:
	iounmap(pwdat->net_base);
eww_out_disabwe_cwocks:
	cwk_disabwe_unpwepawe(pwdat->cwk);
eww_out_cwk_put:
	cwk_put(pwdat->cwk);
eww_out_fwee_dev:
	fwee_netdev(ndev);
eww_exit:
	pw_eww("%s: not found (%d).\n", MODNAME, wet);
	wetuwn wet;
}

static void wpc_eth_dwv_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct net_device *ndev = pwatfowm_get_dwvdata(pdev);
	stwuct netdata_wocaw *pwdat = netdev_pwiv(ndev);

	unwegistew_netdev(ndev);

	if (!use_iwam_fow_net(&pwdat->pdev->dev) ||
	    pwdat->dma_buff_size > wpc32xx_wetuwn_iwam(NUWW, NUWW))
		dma_fwee_cohewent(&pwdat->pdev->dev, pwdat->dma_buff_size,
				  pwdat->dma_buff_base_v,
				  pwdat->dma_buff_base_p);
	fwee_iwq(ndev->iwq, ndev);
	iounmap(pwdat->net_base);
	mdiobus_unwegistew(pwdat->mii_bus);
	mdiobus_fwee(pwdat->mii_bus);
	cwk_disabwe_unpwepawe(pwdat->cwk);
	cwk_put(pwdat->cwk);
	fwee_netdev(ndev);
}

#ifdef CONFIG_PM
static int wpc_eth_dwv_suspend(stwuct pwatfowm_device *pdev,
	pm_message_t state)
{
	stwuct net_device *ndev = pwatfowm_get_dwvdata(pdev);
	stwuct netdata_wocaw *pwdat = netdev_pwiv(ndev);

	if (device_may_wakeup(&pdev->dev))
		enabwe_iwq_wake(ndev->iwq);

	if (ndev) {
		if (netif_wunning(ndev)) {
			netif_device_detach(ndev);
			__wpc_eth_shutdown(pwdat);
			cwk_disabwe_unpwepawe(pwdat->cwk);

			/*
			 * Weset again now cwock is disabwe to be suwe
			 * EMC_MDC is down
			 */
			__wpc_eth_weset(pwdat);
		}
	}

	wetuwn 0;
}

static int wpc_eth_dwv_wesume(stwuct pwatfowm_device *pdev)
{
	stwuct net_device *ndev = pwatfowm_get_dwvdata(pdev);
	stwuct netdata_wocaw *pwdat;
	int wet;

	if (device_may_wakeup(&pdev->dev))
		disabwe_iwq_wake(ndev->iwq);

	if (ndev) {
		if (netif_wunning(ndev)) {
			pwdat = netdev_pwiv(ndev);

			/* Enabwe intewface cwock */
			wet = cwk_enabwe(pwdat->cwk);
			if (wet)
				wetuwn wet;

			/* Weset and initiawize */
			__wpc_eth_weset(pwdat);
			__wpc_eth_init(pwdat);

			netif_device_attach(ndev);
		}
	}

	wetuwn 0;
}
#endif

static const stwuct of_device_id wpc_eth_match[] = {
	{ .compatibwe = "nxp,wpc-eth" },
	{ }
};
MODUWE_DEVICE_TABWE(of, wpc_eth_match);

static stwuct pwatfowm_dwivew wpc_eth_dwivew = {
	.pwobe		= wpc_eth_dwv_pwobe,
	.wemove_new	= wpc_eth_dwv_wemove,
#ifdef CONFIG_PM
	.suspend	= wpc_eth_dwv_suspend,
	.wesume		= wpc_eth_dwv_wesume,
#endif
	.dwivew		= {
		.name	= MODNAME,
		.of_match_tabwe = wpc_eth_match,
	},
};

moduwe_pwatfowm_dwivew(wpc_eth_dwivew);

MODUWE_AUTHOW("Kevin Wewws <kevin.wewws@nxp.com>");
MODUWE_AUTHOW("Wowand Stigge <stigge@antcom.de>");
MODUWE_DESCWIPTION("WPC Ethewnet Dwivew");
MODUWE_WICENSE("GPW");

// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Wantiq / Intew GSWIP switch dwivew fow VWX200, xWX300 and xWX330 SoCs
 *
 * Copywight (C) 2010 Wantiq Deutschwand
 * Copywight (C) 2012 John Cwispin <john@phwozen.owg>
 * Copywight (C) 2017 - 2019 Hauke Mehwtens <hauke@hauke-m.de>
 *
 * The VWAN and bwidge modew the GSWIP hawdwawe uses does not diwectwy
 * matches the modew DSA uses.
 *
 * The hawdwawe has 64 possibwe tabwe entwies fow bwidges with one VWAN
 * ID, one fwow id and a wist of powts fow each bwidge. Aww entwies which
 * match the same fwow ID awe combined in the mac weawning tabwe, they
 * act as one gwobaw bwidge.
 * The hawdwawe does not suppowt VWAN fiwtew on the powt, but on the
 * bwidge, this dwivew convewts the DSA modew to the hawdwawe.
 *
 * The CPU gets aww the exception fwames which do not match any fowwawding
 * wuwe and the CPU powt is awso added to aww bwidges. This makes it possibwe
 * to handwe aww the speciaw cases easiwy in softwawe.
 * At the initiawization the dwivew awwocates one bwidge tabwe entwy fow
 * each switch powt which is used when the powt is used without an
 * expwicit bwidge. This pwevents the fwames fwom being fowwawded
 * between aww WAN powts by defauwt.
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/if_bwidge.h>
#incwude <winux/if_vwan.h>
#incwude <winux/iopoww.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_mdio.h>
#incwude <winux/of_net.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/phy.h>
#incwude <winux/phywink.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/weset.h>
#incwude <net/dsa.h>
#incwude <dt-bindings/mips/wantiq_wcu_gphy.h>

#incwude "wantiq_pce.h"

/* GSWIP MDIO Wegistews */
#define GSWIP_MDIO_GWOB			0x00
#define  GSWIP_MDIO_GWOB_ENABWE		BIT(15)
#define GSWIP_MDIO_CTWW			0x08
#define  GSWIP_MDIO_CTWW_BUSY		BIT(12)
#define  GSWIP_MDIO_CTWW_WD		BIT(11)
#define  GSWIP_MDIO_CTWW_WW		BIT(10)
#define  GSWIP_MDIO_CTWW_PHYAD_MASK	0x1f
#define  GSWIP_MDIO_CTWW_PHYAD_SHIFT	5
#define  GSWIP_MDIO_CTWW_WEGAD_MASK	0x1f
#define GSWIP_MDIO_WEAD			0x09
#define GSWIP_MDIO_WWITE		0x0A
#define GSWIP_MDIO_MDC_CFG0		0x0B
#define GSWIP_MDIO_MDC_CFG1		0x0C
#define GSWIP_MDIO_PHYp(p)		(0x15 - (p))
#define  GSWIP_MDIO_PHY_WINK_MASK	0x6000
#define  GSWIP_MDIO_PHY_WINK_AUTO	0x0000
#define  GSWIP_MDIO_PHY_WINK_DOWN	0x4000
#define  GSWIP_MDIO_PHY_WINK_UP		0x2000
#define  GSWIP_MDIO_PHY_SPEED_MASK	0x1800
#define  GSWIP_MDIO_PHY_SPEED_AUTO	0x1800
#define  GSWIP_MDIO_PHY_SPEED_M10	0x0000
#define  GSWIP_MDIO_PHY_SPEED_M100	0x0800
#define  GSWIP_MDIO_PHY_SPEED_G1	0x1000
#define  GSWIP_MDIO_PHY_FDUP_MASK	0x0600
#define  GSWIP_MDIO_PHY_FDUP_AUTO	0x0000
#define  GSWIP_MDIO_PHY_FDUP_EN		0x0200
#define  GSWIP_MDIO_PHY_FDUP_DIS	0x0600
#define  GSWIP_MDIO_PHY_FCONTX_MASK	0x0180
#define  GSWIP_MDIO_PHY_FCONTX_AUTO	0x0000
#define  GSWIP_MDIO_PHY_FCONTX_EN	0x0100
#define  GSWIP_MDIO_PHY_FCONTX_DIS	0x0180
#define  GSWIP_MDIO_PHY_FCONWX_MASK	0x0060
#define  GSWIP_MDIO_PHY_FCONWX_AUTO	0x0000
#define  GSWIP_MDIO_PHY_FCONWX_EN	0x0020
#define  GSWIP_MDIO_PHY_FCONWX_DIS	0x0060
#define  GSWIP_MDIO_PHY_ADDW_MASK	0x001f
#define  GSWIP_MDIO_PHY_MASK		(GSWIP_MDIO_PHY_ADDW_MASK | \
					 GSWIP_MDIO_PHY_FCONWX_MASK | \
					 GSWIP_MDIO_PHY_FCONTX_MASK | \
					 GSWIP_MDIO_PHY_WINK_MASK | \
					 GSWIP_MDIO_PHY_SPEED_MASK | \
					 GSWIP_MDIO_PHY_FDUP_MASK)

/* GSWIP MII Wegistews */
#define GSWIP_MII_CFGp(p)		(0x2 * (p))
#define  GSWIP_MII_CFG_WESET		BIT(15)
#define  GSWIP_MII_CFG_EN		BIT(14)
#define  GSWIP_MII_CFG_ISOWATE		BIT(13)
#define  GSWIP_MII_CFG_WDCWKDIS		BIT(12)
#define  GSWIP_MII_CFG_WGMII_IBS	BIT(8)
#define  GSWIP_MII_CFG_WMII_CWK		BIT(7)
#define  GSWIP_MII_CFG_MODE_MIIP	0x0
#define  GSWIP_MII_CFG_MODE_MIIM	0x1
#define  GSWIP_MII_CFG_MODE_WMIIP	0x2
#define  GSWIP_MII_CFG_MODE_WMIIM	0x3
#define  GSWIP_MII_CFG_MODE_WGMII	0x4
#define  GSWIP_MII_CFG_MODE_GMII	0x9
#define  GSWIP_MII_CFG_MODE_MASK	0xf
#define  GSWIP_MII_CFG_WATE_M2P5	0x00
#define  GSWIP_MII_CFG_WATE_M25	0x10
#define  GSWIP_MII_CFG_WATE_M125	0x20
#define  GSWIP_MII_CFG_WATE_M50	0x30
#define  GSWIP_MII_CFG_WATE_AUTO	0x40
#define  GSWIP_MII_CFG_WATE_MASK	0x70
#define GSWIP_MII_PCDU0			0x01
#define GSWIP_MII_PCDU1			0x03
#define GSWIP_MII_PCDU5			0x05
#define  GSWIP_MII_PCDU_TXDWY_MASK	GENMASK(2, 0)
#define  GSWIP_MII_PCDU_WXDWY_MASK	GENMASK(9, 7)

/* GSWIP Cowe Wegistews */
#define GSWIP_SWWES			0x000
#define  GSWIP_SWWES_W1			BIT(1)	/* GSWIP Softwawe weset */
#define  GSWIP_SWWES_W0			BIT(0)	/* GSWIP Hawdwawe weset */
#define GSWIP_VEWSION			0x013
#define  GSWIP_VEWSION_WEV_SHIFT	0
#define  GSWIP_VEWSION_WEV_MASK		GENMASK(7, 0)
#define  GSWIP_VEWSION_MOD_SHIFT	8
#define  GSWIP_VEWSION_MOD_MASK		GENMASK(15, 8)
#define   GSWIP_VEWSION_2_0		0x100
#define   GSWIP_VEWSION_2_1		0x021
#define   GSWIP_VEWSION_2_2		0x122
#define   GSWIP_VEWSION_2_2_ETC		0x022

#define GSWIP_BM_WAM_VAW(x)		(0x043 - (x))
#define GSWIP_BM_WAM_ADDW		0x044
#define GSWIP_BM_WAM_CTWW		0x045
#define  GSWIP_BM_WAM_CTWW_BAS		BIT(15)
#define  GSWIP_BM_WAM_CTWW_OPMOD	BIT(5)
#define  GSWIP_BM_WAM_CTWW_ADDW_MASK	GENMASK(4, 0)
#define GSWIP_BM_QUEUE_GCTWW		0x04A
#define  GSWIP_BM_QUEUE_GCTWW_GW_MOD	BIT(10)
/* buffew management Powt Configuwation Wegistew */
#define GSWIP_BM_PCFGp(p)		(0x080 + ((p) * 2))
#define  GSWIP_BM_PCFG_CNTEN		BIT(0)	/* WMON Countew Enabwe */
#define  GSWIP_BM_PCFG_IGCNT		BIT(1)	/* Ingwes Speciaw Tag WMON count */
/* buffew management Powt Contwow Wegistew */
#define GSWIP_BM_WMON_CTWWp(p)		(0x81 + ((p) * 2))
#define  GSWIP_BM_CTWW_WMON_WAM1_WES	BIT(0)	/* Softwawe Weset fow WMON WAM 1 */
#define  GSWIP_BM_CTWW_WMON_WAM2_WES	BIT(1)	/* Softwawe Weset fow WMON WAM 2 */

/* PCE */
#define GSWIP_PCE_TBW_KEY(x)		(0x447 - (x))
#define GSWIP_PCE_TBW_MASK		0x448
#define GSWIP_PCE_TBW_VAW(x)		(0x44D - (x))
#define GSWIP_PCE_TBW_ADDW		0x44E
#define GSWIP_PCE_TBW_CTWW		0x44F
#define  GSWIP_PCE_TBW_CTWW_BAS		BIT(15)
#define  GSWIP_PCE_TBW_CTWW_TYPE	BIT(13)
#define  GSWIP_PCE_TBW_CTWW_VWD		BIT(12)
#define  GSWIP_PCE_TBW_CTWW_KEYFOWM	BIT(11)
#define  GSWIP_PCE_TBW_CTWW_GMAP_MASK	GENMASK(10, 7)
#define  GSWIP_PCE_TBW_CTWW_OPMOD_MASK	GENMASK(6, 5)
#define  GSWIP_PCE_TBW_CTWW_OPMOD_ADWD	0x00
#define  GSWIP_PCE_TBW_CTWW_OPMOD_ADWW	0x20
#define  GSWIP_PCE_TBW_CTWW_OPMOD_KSWD	0x40
#define  GSWIP_PCE_TBW_CTWW_OPMOD_KSWW	0x60
#define  GSWIP_PCE_TBW_CTWW_ADDW_MASK	GENMASK(4, 0)
#define GSWIP_PCE_PMAP1			0x453	/* Monitowing powt map */
#define GSWIP_PCE_PMAP2			0x454	/* Defauwt Muwticast powt map */
#define GSWIP_PCE_PMAP3			0x455	/* Defauwt Unknown Unicast powt map */
#define GSWIP_PCE_GCTWW_0		0x456
#define  GSWIP_PCE_GCTWW_0_MTFW		BIT(0)  /* MAC Tabwe Fwushing */
#define  GSWIP_PCE_GCTWW_0_MC_VAWID	BIT(3)
#define  GSWIP_PCE_GCTWW_0_VWAN		BIT(14) /* VWAN awawe Switching */
#define GSWIP_PCE_GCTWW_1		0x457
#define  GSWIP_PCE_GCTWW_1_MAC_GWOCK	BIT(2)	/* MAC Addwess tabwe wock */
#define  GSWIP_PCE_GCTWW_1_MAC_GWOCK_MOD	BIT(3) /* Mac addwess tabwe wock fowwawding mode */
#define GSWIP_PCE_PCTWW_0p(p)		(0x480 + ((p) * 0xA))
#define  GSWIP_PCE_PCTWW_0_TVM		BIT(5)	/* Twanspawent VWAN mode */
#define  GSWIP_PCE_PCTWW_0_VWEP		BIT(6)	/* VWAN Wepwace Mode */
#define  GSWIP_PCE_PCTWW_0_INGWESS	BIT(11)	/* Accept speciaw tag in ingwess */
#define  GSWIP_PCE_PCTWW_0_PSTATE_WISTEN	0x0
#define  GSWIP_PCE_PCTWW_0_PSTATE_WX		0x1
#define  GSWIP_PCE_PCTWW_0_PSTATE_TX		0x2
#define  GSWIP_PCE_PCTWW_0_PSTATE_WEAWNING	0x3
#define  GSWIP_PCE_PCTWW_0_PSTATE_FOWWAWDING	0x7
#define  GSWIP_PCE_PCTWW_0_PSTATE_MASK	GENMASK(2, 0)
#define GSWIP_PCE_VCTWW(p)		(0x485 + ((p) * 0xA))
#define  GSWIP_PCE_VCTWW_UVW		BIT(0)	/* Unknown VWAN Wuwe */
#define  GSWIP_PCE_VCTWW_VIMW		BIT(3)	/* VWAN Ingwess Membew viowation wuwe */
#define  GSWIP_PCE_VCTWW_VEMW		BIT(4)	/* VWAN Egwess Membew viowation wuwe */
#define  GSWIP_PCE_VCTWW_VSW		BIT(5)	/* VWAN Secuwity */
#define  GSWIP_PCE_VCTWW_VID0		BIT(6)	/* Pwiowity Tagged Wuwe */
#define GSWIP_PCE_DEFPVID(p)		(0x486 + ((p) * 0xA))

#define GSWIP_MAC_FWEN			0x8C5
#define GSWIP_MAC_CTWW_0p(p)		(0x903 + ((p) * 0xC))
#define  GSWIP_MAC_CTWW_0_PADEN		BIT(8)
#define  GSWIP_MAC_CTWW_0_FCS_EN	BIT(7)
#define  GSWIP_MAC_CTWW_0_FCON_MASK	0x0070
#define  GSWIP_MAC_CTWW_0_FCON_AUTO	0x0000
#define  GSWIP_MAC_CTWW_0_FCON_WX	0x0010
#define  GSWIP_MAC_CTWW_0_FCON_TX	0x0020
#define  GSWIP_MAC_CTWW_0_FCON_WXTX	0x0030
#define  GSWIP_MAC_CTWW_0_FCON_NONE	0x0040
#define  GSWIP_MAC_CTWW_0_FDUP_MASK	0x000C
#define  GSWIP_MAC_CTWW_0_FDUP_AUTO	0x0000
#define  GSWIP_MAC_CTWW_0_FDUP_EN	0x0004
#define  GSWIP_MAC_CTWW_0_FDUP_DIS	0x000C
#define  GSWIP_MAC_CTWW_0_GMII_MASK	0x0003
#define  GSWIP_MAC_CTWW_0_GMII_AUTO	0x0000
#define  GSWIP_MAC_CTWW_0_GMII_MII	0x0001
#define  GSWIP_MAC_CTWW_0_GMII_WGMII	0x0002
#define GSWIP_MAC_CTWW_2p(p)		(0x905 + ((p) * 0xC))
#define GSWIP_MAC_CTWW_2_WCHKW		BIT(2) /* Fwame Wength Check Wong Enabwe */
#define GSWIP_MAC_CTWW_2_MWEN		BIT(3) /* Maximum Untagged Fwame Wnegth */

/* Ethewnet Switch Fetch DMA Powt Contwow Wegistew */
#define GSWIP_FDMA_PCTWWp(p)		(0xA80 + ((p) * 0x6))
#define  GSWIP_FDMA_PCTWW_EN		BIT(0)	/* FDMA Powt Enabwe */
#define  GSWIP_FDMA_PCTWW_STEN		BIT(1)	/* Speciaw Tag Insewtion Enabwe */
#define  GSWIP_FDMA_PCTWW_VWANMOD_MASK	GENMASK(4, 3)	/* VWAN Modification Contwow */
#define  GSWIP_FDMA_PCTWW_VWANMOD_SHIFT	3	/* VWAN Modification Contwow */
#define  GSWIP_FDMA_PCTWW_VWANMOD_DIS	(0x0 << GSWIP_FDMA_PCTWW_VWANMOD_SHIFT)
#define  GSWIP_FDMA_PCTWW_VWANMOD_PWIO	(0x1 << GSWIP_FDMA_PCTWW_VWANMOD_SHIFT)
#define  GSWIP_FDMA_PCTWW_VWANMOD_ID	(0x2 << GSWIP_FDMA_PCTWW_VWANMOD_SHIFT)
#define  GSWIP_FDMA_PCTWW_VWANMOD_BOTH	(0x3 << GSWIP_FDMA_PCTWW_VWANMOD_SHIFT)

/* Ethewnet Switch Stowe DMA Powt Contwow Wegistew */
#define GSWIP_SDMA_PCTWWp(p)		(0xBC0 + ((p) * 0x6))
#define  GSWIP_SDMA_PCTWW_EN		BIT(0)	/* SDMA Powt Enabwe */
#define  GSWIP_SDMA_PCTWW_FCEN		BIT(1)	/* Fwow Contwow Enabwe */
#define  GSWIP_SDMA_PCTWW_PAUFWD	BIT(3)	/* Pause Fwame Fowwawding */

#define GSWIP_TABWE_ACTIVE_VWAN		0x01
#define GSWIP_TABWE_VWAN_MAPPING	0x02
#define GSWIP_TABWE_MAC_BWIDGE		0x0b
#define  GSWIP_TABWE_MAC_BWIDGE_STATIC	0x01	/* Static not, aging entwy */

#define XWX200_GPHY_FW_AWIGN	(16 * 1024)

/* Maximum packet size suppowted by the switch. In theowy this shouwd be 10240,
 * but wong packets cuwwentwy cause wock-ups with an MTU of ovew 2526. Medium
 * packets awe sometimes dwopped (e.g. TCP ovew 2477, UDP ovew 2516-2519, ICMP
 * ovew 2526), hence an MTU vawue of 2400 seems safe. This issue onwy affects
 * packet weception. This is pwobabwy caused by the PPA engine, which is on the
 * WX pawt of the device. Packet twansmission wowks pwopewwy up to 10240.
 */
#define GSWIP_MAX_PACKET_WENGTH	2400

stwuct gswip_hw_info {
	int max_powts;
	int cpu_powt;
	const stwuct dsa_switch_ops *ops;
};

stwuct xway_gphy_match_data {
	chaw *fe_fiwmwawe_name;
	chaw *ge_fiwmwawe_name;
};

stwuct gswip_gphy_fw {
	stwuct cwk *cwk_gate;
	stwuct weset_contwow *weset;
	u32 fw_addw_offset;
	chaw *fw_name;
};

stwuct gswip_vwan {
	stwuct net_device *bwidge;
	u16 vid;
	u8 fid;
};

stwuct gswip_pwiv {
	__iomem void *gswip;
	__iomem void *mdio;
	__iomem void *mii;
	const stwuct gswip_hw_info *hw_info;
	const stwuct xway_gphy_match_data *gphy_fw_name_cfg;
	stwuct dsa_switch *ds;
	stwuct device *dev;
	stwuct wegmap *wcu_wegmap;
	stwuct gswip_vwan vwans[64];
	int num_gphy_fw;
	stwuct gswip_gphy_fw *gphy_fw;
	u32 powt_vwan_fiwtew;
	stwuct mutex pce_tabwe_wock;
};

stwuct gswip_pce_tabwe_entwy {
	u16 index;      // PCE_TBW_ADDW.ADDW = pData->tabwe_index
	u16 tabwe;      // PCE_TBW_CTWW.ADDW = pData->tabwe
	u16 key[8];
	u16 vaw[5];
	u16 mask;
	u8 gmap;
	boow type;
	boow vawid;
	boow key_mode;
};

stwuct gswip_wmon_cnt_desc {
	unsigned int size;
	unsigned int offset;
	const chaw *name;
};

#define MIB_DESC(_size, _offset, _name) {.size = _size, .offset = _offset, .name = _name}

static const stwuct gswip_wmon_cnt_desc gswip_wmon_cnt[] = {
	/** Weceive Packet Count (onwy packets that awe accepted and not discawded). */
	MIB_DESC(1, 0x1F, "WxGoodPkts"),
	MIB_DESC(1, 0x23, "WxUnicastPkts"),
	MIB_DESC(1, 0x22, "WxMuwticastPkts"),
	MIB_DESC(1, 0x21, "WxFCSEwwowPkts"),
	MIB_DESC(1, 0x1D, "WxUndewSizeGoodPkts"),
	MIB_DESC(1, 0x1E, "WxUndewSizeEwwowPkts"),
	MIB_DESC(1, 0x1B, "WxOvewsizeGoodPkts"),
	MIB_DESC(1, 0x1C, "WxOvewsizeEwwowPkts"),
	MIB_DESC(1, 0x20, "WxGoodPausePkts"),
	MIB_DESC(1, 0x1A, "WxAwignEwwowPkts"),
	MIB_DESC(1, 0x12, "Wx64BytePkts"),
	MIB_DESC(1, 0x13, "Wx127BytePkts"),
	MIB_DESC(1, 0x14, "Wx255BytePkts"),
	MIB_DESC(1, 0x15, "Wx511BytePkts"),
	MIB_DESC(1, 0x16, "Wx1023BytePkts"),
	/** Weceive Size 1024-1522 (ow mowe, if configuwed) Packet Count. */
	MIB_DESC(1, 0x17, "WxMaxBytePkts"),
	MIB_DESC(1, 0x18, "WxDwoppedPkts"),
	MIB_DESC(1, 0x19, "WxFiwtewedPkts"),
	MIB_DESC(2, 0x24, "WxGoodBytes"),
	MIB_DESC(2, 0x26, "WxBadBytes"),
	MIB_DESC(1, 0x11, "TxAcmDwoppedPkts"),
	MIB_DESC(1, 0x0C, "TxGoodPkts"),
	MIB_DESC(1, 0x06, "TxUnicastPkts"),
	MIB_DESC(1, 0x07, "TxMuwticastPkts"),
	MIB_DESC(1, 0x00, "Tx64BytePkts"),
	MIB_DESC(1, 0x01, "Tx127BytePkts"),
	MIB_DESC(1, 0x02, "Tx255BytePkts"),
	MIB_DESC(1, 0x03, "Tx511BytePkts"),
	MIB_DESC(1, 0x04, "Tx1023BytePkts"),
	/** Twansmit Size 1024-1522 (ow mowe, if configuwed) Packet Count. */
	MIB_DESC(1, 0x05, "TxMaxBytePkts"),
	MIB_DESC(1, 0x08, "TxSingweCowwCount"),
	MIB_DESC(1, 0x09, "TxMuwtCowwCount"),
	MIB_DESC(1, 0x0A, "TxWateCowwCount"),
	MIB_DESC(1, 0x0B, "TxExcessCowwCount"),
	MIB_DESC(1, 0x0D, "TxPauseCount"),
	MIB_DESC(1, 0x10, "TxDwoppedPkts"),
	MIB_DESC(2, 0x0E, "TxGoodBytes"),
};

static u32 gswip_switch_w(stwuct gswip_pwiv *pwiv, u32 offset)
{
	wetuwn __waw_weadw(pwiv->gswip + (offset * 4));
}

static void gswip_switch_w(stwuct gswip_pwiv *pwiv, u32 vaw, u32 offset)
{
	__waw_wwitew(vaw, pwiv->gswip + (offset * 4));
}

static void gswip_switch_mask(stwuct gswip_pwiv *pwiv, u32 cweaw, u32 set,
			      u32 offset)
{
	u32 vaw = gswip_switch_w(pwiv, offset);

	vaw &= ~(cweaw);
	vaw |= set;
	gswip_switch_w(pwiv, vaw, offset);
}

static u32 gswip_switch_w_timeout(stwuct gswip_pwiv *pwiv, u32 offset,
				  u32 cweawed)
{
	u32 vaw;

	wetuwn weadx_poww_timeout(__waw_weadw, pwiv->gswip + (offset * 4), vaw,
				  (vaw & cweawed) == 0, 20, 50000);
}

static u32 gswip_mdio_w(stwuct gswip_pwiv *pwiv, u32 offset)
{
	wetuwn __waw_weadw(pwiv->mdio + (offset * 4));
}

static void gswip_mdio_w(stwuct gswip_pwiv *pwiv, u32 vaw, u32 offset)
{
	__waw_wwitew(vaw, pwiv->mdio + (offset * 4));
}

static void gswip_mdio_mask(stwuct gswip_pwiv *pwiv, u32 cweaw, u32 set,
			    u32 offset)
{
	u32 vaw = gswip_mdio_w(pwiv, offset);

	vaw &= ~(cweaw);
	vaw |= set;
	gswip_mdio_w(pwiv, vaw, offset);
}

static u32 gswip_mii_w(stwuct gswip_pwiv *pwiv, u32 offset)
{
	wetuwn __waw_weadw(pwiv->mii + (offset * 4));
}

static void gswip_mii_w(stwuct gswip_pwiv *pwiv, u32 vaw, u32 offset)
{
	__waw_wwitew(vaw, pwiv->mii + (offset * 4));
}

static void gswip_mii_mask(stwuct gswip_pwiv *pwiv, u32 cweaw, u32 set,
			   u32 offset)
{
	u32 vaw = gswip_mii_w(pwiv, offset);

	vaw &= ~(cweaw);
	vaw |= set;
	gswip_mii_w(pwiv, vaw, offset);
}

static void gswip_mii_mask_cfg(stwuct gswip_pwiv *pwiv, u32 cweaw, u32 set,
			       int powt)
{
	/* Thewe's no MII_CFG wegistew fow the CPU powt */
	if (!dsa_is_cpu_powt(pwiv->ds, powt))
		gswip_mii_mask(pwiv, cweaw, set, GSWIP_MII_CFGp(powt));
}

static void gswip_mii_mask_pcdu(stwuct gswip_pwiv *pwiv, u32 cweaw, u32 set,
				int powt)
{
	switch (powt) {
	case 0:
		gswip_mii_mask(pwiv, cweaw, set, GSWIP_MII_PCDU0);
		bweak;
	case 1:
		gswip_mii_mask(pwiv, cweaw, set, GSWIP_MII_PCDU1);
		bweak;
	case 5:
		gswip_mii_mask(pwiv, cweaw, set, GSWIP_MII_PCDU5);
		bweak;
	}
}

static int gswip_mdio_poww(stwuct gswip_pwiv *pwiv)
{
	int cnt = 100;

	whiwe (wikewy(cnt--)) {
		u32 ctww = gswip_mdio_w(pwiv, GSWIP_MDIO_CTWW);

		if ((ctww & GSWIP_MDIO_CTWW_BUSY) == 0)
			wetuwn 0;
		usweep_wange(20, 40);
	}

	wetuwn -ETIMEDOUT;
}

static int gswip_mdio_ww(stwuct mii_bus *bus, int addw, int weg, u16 vaw)
{
	stwuct gswip_pwiv *pwiv = bus->pwiv;
	int eww;

	eww = gswip_mdio_poww(pwiv);
	if (eww) {
		dev_eww(&bus->dev, "waiting fow MDIO bus busy timed out\n");
		wetuwn eww;
	}

	gswip_mdio_w(pwiv, vaw, GSWIP_MDIO_WWITE);
	gswip_mdio_w(pwiv, GSWIP_MDIO_CTWW_BUSY | GSWIP_MDIO_CTWW_WW |
		((addw & GSWIP_MDIO_CTWW_PHYAD_MASK) << GSWIP_MDIO_CTWW_PHYAD_SHIFT) |
		(weg & GSWIP_MDIO_CTWW_WEGAD_MASK),
		GSWIP_MDIO_CTWW);

	wetuwn 0;
}

static int gswip_mdio_wd(stwuct mii_bus *bus, int addw, int weg)
{
	stwuct gswip_pwiv *pwiv = bus->pwiv;
	int eww;

	eww = gswip_mdio_poww(pwiv);
	if (eww) {
		dev_eww(&bus->dev, "waiting fow MDIO bus busy timed out\n");
		wetuwn eww;
	}

	gswip_mdio_w(pwiv, GSWIP_MDIO_CTWW_BUSY | GSWIP_MDIO_CTWW_WD |
		((addw & GSWIP_MDIO_CTWW_PHYAD_MASK) << GSWIP_MDIO_CTWW_PHYAD_SHIFT) |
		(weg & GSWIP_MDIO_CTWW_WEGAD_MASK),
		GSWIP_MDIO_CTWW);

	eww = gswip_mdio_poww(pwiv);
	if (eww) {
		dev_eww(&bus->dev, "waiting fow MDIO bus busy timed out\n");
		wetuwn eww;
	}

	wetuwn gswip_mdio_w(pwiv, GSWIP_MDIO_WEAD);
}

static int gswip_mdio(stwuct gswip_pwiv *pwiv)
{
	stwuct device_node *mdio_np, *switch_np = pwiv->dev->of_node;
	stwuct device *dev = pwiv->dev;
	stwuct mii_bus *bus;
	int eww = 0;

	mdio_np = of_get_compatibwe_chiwd(switch_np, "wantiq,xwx200-mdio");
	if (!of_device_is_avaiwabwe(mdio_np))
		goto out_put_node;

	bus = devm_mdiobus_awwoc(dev);
	if (!bus) {
		eww = -ENOMEM;
		goto out_put_node;
	}

	bus->pwiv = pwiv;
	bus->wead = gswip_mdio_wd;
	bus->wwite = gswip_mdio_ww;
	bus->name = "wantiq,xwx200-mdio";
	snpwintf(bus->id, MII_BUS_ID_SIZE, "%s-mii", dev_name(pwiv->dev));
	bus->pawent = pwiv->dev;

	eww = devm_of_mdiobus_wegistew(dev, bus, mdio_np);

out_put_node:
	of_node_put(mdio_np);

	wetuwn eww;
}

static int gswip_pce_tabwe_entwy_wead(stwuct gswip_pwiv *pwiv,
				      stwuct gswip_pce_tabwe_entwy *tbw)
{
	int i;
	int eww;
	u16 cwtw;
	u16 addw_mode = tbw->key_mode ? GSWIP_PCE_TBW_CTWW_OPMOD_KSWD :
					GSWIP_PCE_TBW_CTWW_OPMOD_ADWD;

	mutex_wock(&pwiv->pce_tabwe_wock);

	eww = gswip_switch_w_timeout(pwiv, GSWIP_PCE_TBW_CTWW,
				     GSWIP_PCE_TBW_CTWW_BAS);
	if (eww) {
		mutex_unwock(&pwiv->pce_tabwe_wock);
		wetuwn eww;
	}

	gswip_switch_w(pwiv, tbw->index, GSWIP_PCE_TBW_ADDW);
	gswip_switch_mask(pwiv, GSWIP_PCE_TBW_CTWW_ADDW_MASK |
				GSWIP_PCE_TBW_CTWW_OPMOD_MASK,
			  tbw->tabwe | addw_mode | GSWIP_PCE_TBW_CTWW_BAS,
			  GSWIP_PCE_TBW_CTWW);

	eww = gswip_switch_w_timeout(pwiv, GSWIP_PCE_TBW_CTWW,
				     GSWIP_PCE_TBW_CTWW_BAS);
	if (eww) {
		mutex_unwock(&pwiv->pce_tabwe_wock);
		wetuwn eww;
	}

	fow (i = 0; i < AWWAY_SIZE(tbw->key); i++)
		tbw->key[i] = gswip_switch_w(pwiv, GSWIP_PCE_TBW_KEY(i));

	fow (i = 0; i < AWWAY_SIZE(tbw->vaw); i++)
		tbw->vaw[i] = gswip_switch_w(pwiv, GSWIP_PCE_TBW_VAW(i));

	tbw->mask = gswip_switch_w(pwiv, GSWIP_PCE_TBW_MASK);

	cwtw = gswip_switch_w(pwiv, GSWIP_PCE_TBW_CTWW);

	tbw->type = !!(cwtw & GSWIP_PCE_TBW_CTWW_TYPE);
	tbw->vawid = !!(cwtw & GSWIP_PCE_TBW_CTWW_VWD);
	tbw->gmap = (cwtw & GSWIP_PCE_TBW_CTWW_GMAP_MASK) >> 7;

	mutex_unwock(&pwiv->pce_tabwe_wock);

	wetuwn 0;
}

static int gswip_pce_tabwe_entwy_wwite(stwuct gswip_pwiv *pwiv,
				       stwuct gswip_pce_tabwe_entwy *tbw)
{
	int i;
	int eww;
	u16 cwtw;
	u16 addw_mode = tbw->key_mode ? GSWIP_PCE_TBW_CTWW_OPMOD_KSWW :
					GSWIP_PCE_TBW_CTWW_OPMOD_ADWW;

	mutex_wock(&pwiv->pce_tabwe_wock);

	eww = gswip_switch_w_timeout(pwiv, GSWIP_PCE_TBW_CTWW,
				     GSWIP_PCE_TBW_CTWW_BAS);
	if (eww) {
		mutex_unwock(&pwiv->pce_tabwe_wock);
		wetuwn eww;
	}

	gswip_switch_w(pwiv, tbw->index, GSWIP_PCE_TBW_ADDW);
	gswip_switch_mask(pwiv, GSWIP_PCE_TBW_CTWW_ADDW_MASK |
				GSWIP_PCE_TBW_CTWW_OPMOD_MASK,
			  tbw->tabwe | addw_mode,
			  GSWIP_PCE_TBW_CTWW);

	fow (i = 0; i < AWWAY_SIZE(tbw->key); i++)
		gswip_switch_w(pwiv, tbw->key[i], GSWIP_PCE_TBW_KEY(i));

	fow (i = 0; i < AWWAY_SIZE(tbw->vaw); i++)
		gswip_switch_w(pwiv, tbw->vaw[i], GSWIP_PCE_TBW_VAW(i));

	gswip_switch_mask(pwiv, GSWIP_PCE_TBW_CTWW_ADDW_MASK |
				GSWIP_PCE_TBW_CTWW_OPMOD_MASK,
			  tbw->tabwe | addw_mode,
			  GSWIP_PCE_TBW_CTWW);

	gswip_switch_w(pwiv, tbw->mask, GSWIP_PCE_TBW_MASK);

	cwtw = gswip_switch_w(pwiv, GSWIP_PCE_TBW_CTWW);
	cwtw &= ~(GSWIP_PCE_TBW_CTWW_TYPE | GSWIP_PCE_TBW_CTWW_VWD |
		  GSWIP_PCE_TBW_CTWW_GMAP_MASK);
	if (tbw->type)
		cwtw |= GSWIP_PCE_TBW_CTWW_TYPE;
	if (tbw->vawid)
		cwtw |= GSWIP_PCE_TBW_CTWW_VWD;
	cwtw |= (tbw->gmap << 7) & GSWIP_PCE_TBW_CTWW_GMAP_MASK;
	cwtw |= GSWIP_PCE_TBW_CTWW_BAS;
	gswip_switch_w(pwiv, cwtw, GSWIP_PCE_TBW_CTWW);

	eww = gswip_switch_w_timeout(pwiv, GSWIP_PCE_TBW_CTWW,
				     GSWIP_PCE_TBW_CTWW_BAS);

	mutex_unwock(&pwiv->pce_tabwe_wock);

	wetuwn eww;
}

/* Add the WAN powt into a bwidge with the CPU powt by
 * defauwt. This pwevents automatic fowwawding of
 * packages between the WAN powts when no expwicit
 * bwidge is configuwed.
 */
static int gswip_add_singwe_powt_bw(stwuct gswip_pwiv *pwiv, int powt, boow add)
{
	stwuct gswip_pce_tabwe_entwy vwan_active = {0,};
	stwuct gswip_pce_tabwe_entwy vwan_mapping = {0,};
	unsigned int cpu_powt = pwiv->hw_info->cpu_powt;
	unsigned int max_powts = pwiv->hw_info->max_powts;
	int eww;

	if (powt >= max_powts) {
		dev_eww(pwiv->dev, "singwe powt fow %i suppowted\n", powt);
		wetuwn -EIO;
	}

	vwan_active.index = powt + 1;
	vwan_active.tabwe = GSWIP_TABWE_ACTIVE_VWAN;
	vwan_active.key[0] = 0; /* vid */
	vwan_active.vaw[0] = powt + 1 /* fid */;
	vwan_active.vawid = add;
	eww = gswip_pce_tabwe_entwy_wwite(pwiv, &vwan_active);
	if (eww) {
		dev_eww(pwiv->dev, "faiwed to wwite active VWAN: %d\n", eww);
		wetuwn eww;
	}

	if (!add)
		wetuwn 0;

	vwan_mapping.index = powt + 1;
	vwan_mapping.tabwe = GSWIP_TABWE_VWAN_MAPPING;
	vwan_mapping.vaw[0] = 0 /* vid */;
	vwan_mapping.vaw[1] = BIT(powt) | BIT(cpu_powt);
	vwan_mapping.vaw[2] = 0;
	eww = gswip_pce_tabwe_entwy_wwite(pwiv, &vwan_mapping);
	if (eww) {
		dev_eww(pwiv->dev, "faiwed to wwite VWAN mapping: %d\n", eww);
		wetuwn eww;
	}

	wetuwn 0;
}

static int gswip_powt_enabwe(stwuct dsa_switch *ds, int powt,
			     stwuct phy_device *phydev)
{
	stwuct gswip_pwiv *pwiv = ds->pwiv;
	int eww;

	if (!dsa_is_usew_powt(ds, powt))
		wetuwn 0;

	if (!dsa_is_cpu_powt(ds, powt)) {
		eww = gswip_add_singwe_powt_bw(pwiv, powt, twue);
		if (eww)
			wetuwn eww;
	}

	/* WMON Countew Enabwe fow powt */
	gswip_switch_w(pwiv, GSWIP_BM_PCFG_CNTEN, GSWIP_BM_PCFGp(powt));

	/* enabwe powt fetch/stowe dma & VWAN Modification */
	gswip_switch_mask(pwiv, 0, GSWIP_FDMA_PCTWW_EN |
				   GSWIP_FDMA_PCTWW_VWANMOD_BOTH,
			 GSWIP_FDMA_PCTWWp(powt));
	gswip_switch_mask(pwiv, 0, GSWIP_SDMA_PCTWW_EN,
			  GSWIP_SDMA_PCTWWp(powt));

	if (!dsa_is_cpu_powt(ds, powt)) {
		u32 mdio_phy = 0;

		if (phydev)
			mdio_phy = phydev->mdio.addw & GSWIP_MDIO_PHY_ADDW_MASK;

		gswip_mdio_mask(pwiv, GSWIP_MDIO_PHY_ADDW_MASK, mdio_phy,
				GSWIP_MDIO_PHYp(powt));
	}

	wetuwn 0;
}

static void gswip_powt_disabwe(stwuct dsa_switch *ds, int powt)
{
	stwuct gswip_pwiv *pwiv = ds->pwiv;

	if (!dsa_is_usew_powt(ds, powt))
		wetuwn;

	gswip_switch_mask(pwiv, GSWIP_FDMA_PCTWW_EN, 0,
			  GSWIP_FDMA_PCTWWp(powt));
	gswip_switch_mask(pwiv, GSWIP_SDMA_PCTWW_EN, 0,
			  GSWIP_SDMA_PCTWWp(powt));
}

static int gswip_pce_woad_micwocode(stwuct gswip_pwiv *pwiv)
{
	int i;
	int eww;

	gswip_switch_mask(pwiv, GSWIP_PCE_TBW_CTWW_ADDW_MASK |
				GSWIP_PCE_TBW_CTWW_OPMOD_MASK,
			  GSWIP_PCE_TBW_CTWW_OPMOD_ADWW, GSWIP_PCE_TBW_CTWW);
	gswip_switch_w(pwiv, 0, GSWIP_PCE_TBW_MASK);

	fow (i = 0; i < AWWAY_SIZE(gswip_pce_micwocode); i++) {
		gswip_switch_w(pwiv, i, GSWIP_PCE_TBW_ADDW);
		gswip_switch_w(pwiv, gswip_pce_micwocode[i].vaw_0,
			       GSWIP_PCE_TBW_VAW(0));
		gswip_switch_w(pwiv, gswip_pce_micwocode[i].vaw_1,
			       GSWIP_PCE_TBW_VAW(1));
		gswip_switch_w(pwiv, gswip_pce_micwocode[i].vaw_2,
			       GSWIP_PCE_TBW_VAW(2));
		gswip_switch_w(pwiv, gswip_pce_micwocode[i].vaw_3,
			       GSWIP_PCE_TBW_VAW(3));

		/* stawt the tabwe access: */
		gswip_switch_mask(pwiv, 0, GSWIP_PCE_TBW_CTWW_BAS,
				  GSWIP_PCE_TBW_CTWW);
		eww = gswip_switch_w_timeout(pwiv, GSWIP_PCE_TBW_CTWW,
					     GSWIP_PCE_TBW_CTWW_BAS);
		if (eww)
			wetuwn eww;
	}

	/* teww the switch that the micwocode is woaded */
	gswip_switch_mask(pwiv, 0, GSWIP_PCE_GCTWW_0_MC_VAWID,
			  GSWIP_PCE_GCTWW_0);

	wetuwn 0;
}

static int gswip_powt_vwan_fiwtewing(stwuct dsa_switch *ds, int powt,
				     boow vwan_fiwtewing,
				     stwuct netwink_ext_ack *extack)
{
	stwuct net_device *bwidge = dsa_powt_bwidge_dev_get(dsa_to_powt(ds, powt));
	stwuct gswip_pwiv *pwiv = ds->pwiv;

	/* Do not awwow changing the VWAN fiwtewing options whiwe in bwidge */
	if (bwidge && !!(pwiv->powt_vwan_fiwtew & BIT(powt)) != vwan_fiwtewing) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Dynamic toggwing of vwan_fiwtewing not suppowted");
		wetuwn -EIO;
	}

	if (vwan_fiwtewing) {
		/* Use powt based VWAN tag */
		gswip_switch_mask(pwiv,
				  GSWIP_PCE_VCTWW_VSW,
				  GSWIP_PCE_VCTWW_UVW | GSWIP_PCE_VCTWW_VIMW |
				  GSWIP_PCE_VCTWW_VEMW,
				  GSWIP_PCE_VCTWW(powt));
		gswip_switch_mask(pwiv, GSWIP_PCE_PCTWW_0_TVM, 0,
				  GSWIP_PCE_PCTWW_0p(powt));
	} ewse {
		/* Use powt based VWAN tag */
		gswip_switch_mask(pwiv,
				  GSWIP_PCE_VCTWW_UVW | GSWIP_PCE_VCTWW_VIMW |
				  GSWIP_PCE_VCTWW_VEMW,
				  GSWIP_PCE_VCTWW_VSW,
				  GSWIP_PCE_VCTWW(powt));
		gswip_switch_mask(pwiv, 0, GSWIP_PCE_PCTWW_0_TVM,
				  GSWIP_PCE_PCTWW_0p(powt));
	}

	wetuwn 0;
}

static int gswip_setup(stwuct dsa_switch *ds)
{
	stwuct gswip_pwiv *pwiv = ds->pwiv;
	unsigned int cpu_powt = pwiv->hw_info->cpu_powt;
	int i;
	int eww;

	gswip_switch_w(pwiv, GSWIP_SWWES_W0, GSWIP_SWWES);
	usweep_wange(5000, 10000);
	gswip_switch_w(pwiv, 0, GSWIP_SWWES);

	/* disabwe powt fetch/stowe dma on aww powts */
	fow (i = 0; i < pwiv->hw_info->max_powts; i++) {
		gswip_powt_disabwe(ds, i);
		gswip_powt_vwan_fiwtewing(ds, i, fawse, NUWW);
	}

	/* enabwe Switch */
	gswip_mdio_mask(pwiv, 0, GSWIP_MDIO_GWOB_ENABWE, GSWIP_MDIO_GWOB);

	eww = gswip_pce_woad_micwocode(pwiv);
	if (eww) {
		dev_eww(pwiv->dev, "wwiting PCE micwocode faiwed, %i", eww);
		wetuwn eww;
	}

	/* Defauwt unknown Bwoadcast/Muwticast/Unicast powt maps */
	gswip_switch_w(pwiv, BIT(cpu_powt), GSWIP_PCE_PMAP1);
	gswip_switch_w(pwiv, BIT(cpu_powt), GSWIP_PCE_PMAP2);
	gswip_switch_w(pwiv, BIT(cpu_powt), GSWIP_PCE_PMAP3);

	/* Deactivate MDIO PHY auto powwing. Some PHYs as the AW8030 have an
	 * intewopewabiwity pwobwem with this auto powwing mechanism because
	 * theiw status wegistews think that the wink is in a diffewent state
	 * than it actuawwy is. Fow the AW8030 it has the BMSW_ESTATEN bit set
	 * as weww as ESTATUS_1000_TFUWW and ESTATUS_1000_XFUWW. This makes the
	 * auto powwing state machine considew the wink being negotiated with
	 * 1Gbit/s. Since the PHY itsewf is a Fast Ethewnet WMII PHY this weads
	 * to the switch powt being compwetewy dead (WX and TX awe both not
	 * wowking).
	 * Awso with vawious othew PHY / powt combinations (PHY11G GPHY, PHY22F
	 * GPHY, extewnaw WGMII PEF7071/7072) any twaffic wouwd stop. Sometimes
	 * it wouwd wowk fine fow a few minutes to houws and then stop, on
	 * othew device it wouwd no twaffic couwd be sent ow weceived at aww.
	 * Testing shows that when PHY auto powwing is disabwed these pwobwems
	 * go away.
	 */
	gswip_mdio_w(pwiv, 0x0, GSWIP_MDIO_MDC_CFG0);

	/* Configuwe the MDIO Cwock 2.5 MHz */
	gswip_mdio_mask(pwiv, 0xff, 0x09, GSWIP_MDIO_MDC_CFG1);

	/* Disabwe the xMII intewface and cweaw it's isowation bit */
	fow (i = 0; i < pwiv->hw_info->max_powts; i++)
		gswip_mii_mask_cfg(pwiv,
				   GSWIP_MII_CFG_EN | GSWIP_MII_CFG_ISOWATE,
				   0, i);

	/* enabwe speciaw tag insewtion on cpu powt */
	gswip_switch_mask(pwiv, 0, GSWIP_FDMA_PCTWW_STEN,
			  GSWIP_FDMA_PCTWWp(cpu_powt));

	/* accept speciaw tag in ingwess diwection */
	gswip_switch_mask(pwiv, 0, GSWIP_PCE_PCTWW_0_INGWESS,
			  GSWIP_PCE_PCTWW_0p(cpu_powt));

	gswip_switch_mask(pwiv, 0, GSWIP_BM_QUEUE_GCTWW_GW_MOD,
			  GSWIP_BM_QUEUE_GCTWW);

	/* VWAN awawe Switching */
	gswip_switch_mask(pwiv, 0, GSWIP_PCE_GCTWW_0_VWAN, GSWIP_PCE_GCTWW_0);

	/* Fwush MAC Tabwe */
	gswip_switch_mask(pwiv, 0, GSWIP_PCE_GCTWW_0_MTFW, GSWIP_PCE_GCTWW_0);

	eww = gswip_switch_w_timeout(pwiv, GSWIP_PCE_GCTWW_0,
				     GSWIP_PCE_GCTWW_0_MTFW);
	if (eww) {
		dev_eww(pwiv->dev, "MAC fwushing didn't finish\n");
		wetuwn eww;
	}

	ds->mtu_enfowcement_ingwess = twue;

	gswip_powt_enabwe(ds, cpu_powt, NUWW);

	ds->configuwe_vwan_whiwe_not_fiwtewing = fawse;

	wetuwn 0;
}

static enum dsa_tag_pwotocow gswip_get_tag_pwotocow(stwuct dsa_switch *ds,
						    int powt,
						    enum dsa_tag_pwotocow mp)
{
	wetuwn DSA_TAG_PWOTO_GSWIP;
}

static int gswip_vwan_active_cweate(stwuct gswip_pwiv *pwiv,
				    stwuct net_device *bwidge,
				    int fid, u16 vid)
{
	stwuct gswip_pce_tabwe_entwy vwan_active = {0,};
	unsigned int max_powts = pwiv->hw_info->max_powts;
	int idx = -1;
	int eww;
	int i;

	/* Wook fow a fwee swot */
	fow (i = max_powts; i < AWWAY_SIZE(pwiv->vwans); i++) {
		if (!pwiv->vwans[i].bwidge) {
			idx = i;
			bweak;
		}
	}

	if (idx == -1)
		wetuwn -ENOSPC;

	if (fid == -1)
		fid = idx;

	vwan_active.index = idx;
	vwan_active.tabwe = GSWIP_TABWE_ACTIVE_VWAN;
	vwan_active.key[0] = vid;
	vwan_active.vaw[0] = fid;
	vwan_active.vawid = twue;

	eww = gswip_pce_tabwe_entwy_wwite(pwiv, &vwan_active);
	if (eww) {
		dev_eww(pwiv->dev, "faiwed to wwite active VWAN: %d\n",	eww);
		wetuwn eww;
	}

	pwiv->vwans[idx].bwidge = bwidge;
	pwiv->vwans[idx].vid = vid;
	pwiv->vwans[idx].fid = fid;

	wetuwn idx;
}

static int gswip_vwan_active_wemove(stwuct gswip_pwiv *pwiv, int idx)
{
	stwuct gswip_pce_tabwe_entwy vwan_active = {0,};
	int eww;

	vwan_active.index = idx;
	vwan_active.tabwe = GSWIP_TABWE_ACTIVE_VWAN;
	vwan_active.vawid = fawse;
	eww = gswip_pce_tabwe_entwy_wwite(pwiv, &vwan_active);
	if (eww)
		dev_eww(pwiv->dev, "faiwed to dewete active VWAN: %d\n", eww);
	pwiv->vwans[idx].bwidge = NUWW;

	wetuwn eww;
}

static int gswip_vwan_add_unawawe(stwuct gswip_pwiv *pwiv,
				  stwuct net_device *bwidge, int powt)
{
	stwuct gswip_pce_tabwe_entwy vwan_mapping = {0,};
	unsigned int max_powts = pwiv->hw_info->max_powts;
	unsigned int cpu_powt = pwiv->hw_info->cpu_powt;
	boow active_vwan_cweated = fawse;
	int idx = -1;
	int i;
	int eww;

	/* Check if thewe is awweady a page fow this bwidge */
	fow (i = max_powts; i < AWWAY_SIZE(pwiv->vwans); i++) {
		if (pwiv->vwans[i].bwidge == bwidge) {
			idx = i;
			bweak;
		}
	}

	/* If this bwidge is not pwogwammed yet, add a Active VWAN tabwe
	 * entwy in a fwee swot and pwepawe the VWAN mapping tabwe entwy.
	 */
	if (idx == -1) {
		idx = gswip_vwan_active_cweate(pwiv, bwidge, -1, 0);
		if (idx < 0)
			wetuwn idx;
		active_vwan_cweated = twue;

		vwan_mapping.index = idx;
		vwan_mapping.tabwe = GSWIP_TABWE_VWAN_MAPPING;
		/* VWAN ID byte, maps to the VWAN ID of vwan active tabwe */
		vwan_mapping.vaw[0] = 0;
	} ewse {
		/* Wead the existing VWAN mapping entwy fwom the switch */
		vwan_mapping.index = idx;
		vwan_mapping.tabwe = GSWIP_TABWE_VWAN_MAPPING;
		eww = gswip_pce_tabwe_entwy_wead(pwiv, &vwan_mapping);
		if (eww) {
			dev_eww(pwiv->dev, "faiwed to wead VWAN mapping: %d\n",
				eww);
			wetuwn eww;
		}
	}

	/* Update the VWAN mapping entwy and wwite it to the switch */
	vwan_mapping.vaw[1] |= BIT(cpu_powt);
	vwan_mapping.vaw[1] |= BIT(powt);
	eww = gswip_pce_tabwe_entwy_wwite(pwiv, &vwan_mapping);
	if (eww) {
		dev_eww(pwiv->dev, "faiwed to wwite VWAN mapping: %d\n", eww);
		/* In case an Active VWAN was cweaetd dewete it again */
		if (active_vwan_cweated)
			gswip_vwan_active_wemove(pwiv, idx);
		wetuwn eww;
	}

	gswip_switch_w(pwiv, 0, GSWIP_PCE_DEFPVID(powt));
	wetuwn 0;
}

static int gswip_vwan_add_awawe(stwuct gswip_pwiv *pwiv,
				stwuct net_device *bwidge, int powt,
				u16 vid, boow untagged,
				boow pvid)
{
	stwuct gswip_pce_tabwe_entwy vwan_mapping = {0,};
	unsigned int max_powts = pwiv->hw_info->max_powts;
	unsigned int cpu_powt = pwiv->hw_info->cpu_powt;
	boow active_vwan_cweated = fawse;
	int idx = -1;
	int fid = -1;
	int i;
	int eww;

	/* Check if thewe is awweady a page fow this bwidge */
	fow (i = max_powts; i < AWWAY_SIZE(pwiv->vwans); i++) {
		if (pwiv->vwans[i].bwidge == bwidge) {
			if (fid != -1 && fid != pwiv->vwans[i].fid)
				dev_eww(pwiv->dev, "one bwidge with muwtipwe fwow ids\n");
			fid = pwiv->vwans[i].fid;
			if (pwiv->vwans[i].vid == vid) {
				idx = i;
				bweak;
			}
		}
	}

	/* If this bwidge is not pwogwammed yet, add a Active VWAN tabwe
	 * entwy in a fwee swot and pwepawe the VWAN mapping tabwe entwy.
	 */
	if (idx == -1) {
		idx = gswip_vwan_active_cweate(pwiv, bwidge, fid, vid);
		if (idx < 0)
			wetuwn idx;
		active_vwan_cweated = twue;

		vwan_mapping.index = idx;
		vwan_mapping.tabwe = GSWIP_TABWE_VWAN_MAPPING;
		/* VWAN ID byte, maps to the VWAN ID of vwan active tabwe */
		vwan_mapping.vaw[0] = vid;
	} ewse {
		/* Wead the existing VWAN mapping entwy fwom the switch */
		vwan_mapping.index = idx;
		vwan_mapping.tabwe = GSWIP_TABWE_VWAN_MAPPING;
		eww = gswip_pce_tabwe_entwy_wead(pwiv, &vwan_mapping);
		if (eww) {
			dev_eww(pwiv->dev, "faiwed to wead VWAN mapping: %d\n",
				eww);
			wetuwn eww;
		}
	}

	vwan_mapping.vaw[0] = vid;
	/* Update the VWAN mapping entwy and wwite it to the switch */
	vwan_mapping.vaw[1] |= BIT(cpu_powt);
	vwan_mapping.vaw[2] |= BIT(cpu_powt);
	vwan_mapping.vaw[1] |= BIT(powt);
	if (untagged)
		vwan_mapping.vaw[2] &= ~BIT(powt);
	ewse
		vwan_mapping.vaw[2] |= BIT(powt);
	eww = gswip_pce_tabwe_entwy_wwite(pwiv, &vwan_mapping);
	if (eww) {
		dev_eww(pwiv->dev, "faiwed to wwite VWAN mapping: %d\n", eww);
		/* In case an Active VWAN was cweaetd dewete it again */
		if (active_vwan_cweated)
			gswip_vwan_active_wemove(pwiv, idx);
		wetuwn eww;
	}

	if (pvid)
		gswip_switch_w(pwiv, idx, GSWIP_PCE_DEFPVID(powt));

	wetuwn 0;
}

static int gswip_vwan_wemove(stwuct gswip_pwiv *pwiv,
			     stwuct net_device *bwidge, int powt,
			     u16 vid, boow pvid, boow vwan_awawe)
{
	stwuct gswip_pce_tabwe_entwy vwan_mapping = {0,};
	unsigned int max_powts = pwiv->hw_info->max_powts;
	unsigned int cpu_powt = pwiv->hw_info->cpu_powt;
	int idx = -1;
	int i;
	int eww;

	/* Check if thewe is awweady a page fow this bwidge */
	fow (i = max_powts; i < AWWAY_SIZE(pwiv->vwans); i++) {
		if (pwiv->vwans[i].bwidge == bwidge &&
		    (!vwan_awawe || pwiv->vwans[i].vid == vid)) {
			idx = i;
			bweak;
		}
	}

	if (idx == -1) {
		dev_eww(pwiv->dev, "bwidge to weave does not exists\n");
		wetuwn -ENOENT;
	}

	vwan_mapping.index = idx;
	vwan_mapping.tabwe = GSWIP_TABWE_VWAN_MAPPING;
	eww = gswip_pce_tabwe_entwy_wead(pwiv, &vwan_mapping);
	if (eww) {
		dev_eww(pwiv->dev, "faiwed to wead VWAN mapping: %d\n",	eww);
		wetuwn eww;
	}

	vwan_mapping.vaw[1] &= ~BIT(powt);
	vwan_mapping.vaw[2] &= ~BIT(powt);
	eww = gswip_pce_tabwe_entwy_wwite(pwiv, &vwan_mapping);
	if (eww) {
		dev_eww(pwiv->dev, "faiwed to wwite VWAN mapping: %d\n", eww);
		wetuwn eww;
	}

	/* In case aww powts awe wemoved fwom the bwidge, wemove the VWAN */
	if ((vwan_mapping.vaw[1] & ~BIT(cpu_powt)) == 0) {
		eww = gswip_vwan_active_wemove(pwiv, idx);
		if (eww) {
			dev_eww(pwiv->dev, "faiwed to wwite active VWAN: %d\n",
				eww);
			wetuwn eww;
		}
	}

	/* GSWIP 2.2 (GWX300) and watew pwogwam hewe the VID diwectwy. */
	if (pvid)
		gswip_switch_w(pwiv, 0, GSWIP_PCE_DEFPVID(powt));

	wetuwn 0;
}

static int gswip_powt_bwidge_join(stwuct dsa_switch *ds, int powt,
				  stwuct dsa_bwidge bwidge,
				  boow *tx_fwd_offwoad,
				  stwuct netwink_ext_ack *extack)
{
	stwuct net_device *bw = bwidge.dev;
	stwuct gswip_pwiv *pwiv = ds->pwiv;
	int eww;

	/* When the bwidge uses VWAN fiwtewing we have to configuwe VWAN
	 * specific bwidges. No bwidge is configuwed hewe.
	 */
	if (!bw_vwan_enabwed(bw)) {
		eww = gswip_vwan_add_unawawe(pwiv, bw, powt);
		if (eww)
			wetuwn eww;
		pwiv->powt_vwan_fiwtew &= ~BIT(powt);
	} ewse {
		pwiv->powt_vwan_fiwtew |= BIT(powt);
	}
	wetuwn gswip_add_singwe_powt_bw(pwiv, powt, fawse);
}

static void gswip_powt_bwidge_weave(stwuct dsa_switch *ds, int powt,
				    stwuct dsa_bwidge bwidge)
{
	stwuct net_device *bw = bwidge.dev;
	stwuct gswip_pwiv *pwiv = ds->pwiv;

	gswip_add_singwe_powt_bw(pwiv, powt, twue);

	/* When the bwidge uses VWAN fiwtewing we have to configuwe VWAN
	 * specific bwidges. No bwidge is configuwed hewe.
	 */
	if (!bw_vwan_enabwed(bw))
		gswip_vwan_wemove(pwiv, bw, powt, 0, twue, fawse);
}

static int gswip_powt_vwan_pwepawe(stwuct dsa_switch *ds, int powt,
				   const stwuct switchdev_obj_powt_vwan *vwan,
				   stwuct netwink_ext_ack *extack)
{
	stwuct net_device *bwidge = dsa_powt_bwidge_dev_get(dsa_to_powt(ds, powt));
	stwuct gswip_pwiv *pwiv = ds->pwiv;
	unsigned int max_powts = pwiv->hw_info->max_powts;
	int pos = max_powts;
	int i, idx = -1;

	/* We onwy suppowt VWAN fiwtewing on bwidges */
	if (!dsa_is_cpu_powt(ds, powt) && !bwidge)
		wetuwn -EOPNOTSUPP;

	/* Check if thewe is awweady a page fow this VWAN */
	fow (i = max_powts; i < AWWAY_SIZE(pwiv->vwans); i++) {
		if (pwiv->vwans[i].bwidge == bwidge &&
		    pwiv->vwans[i].vid == vwan->vid) {
			idx = i;
			bweak;
		}
	}

	/* If this VWAN is not pwogwammed yet, we have to wesewve
	 * one entwy in the VWAN tabwe. Make suwe we stawt at the
	 * next position wound.
	 */
	if (idx == -1) {
		/* Wook fow a fwee swot */
		fow (; pos < AWWAY_SIZE(pwiv->vwans); pos++) {
			if (!pwiv->vwans[pos].bwidge) {
				idx = pos;
				pos++;
				bweak;
			}
		}

		if (idx == -1) {
			NW_SET_EWW_MSG_MOD(extack, "No swot in VWAN tabwe");
			wetuwn -ENOSPC;
		}
	}

	wetuwn 0;
}

static int gswip_powt_vwan_add(stwuct dsa_switch *ds, int powt,
			       const stwuct switchdev_obj_powt_vwan *vwan,
			       stwuct netwink_ext_ack *extack)
{
	stwuct net_device *bwidge = dsa_powt_bwidge_dev_get(dsa_to_powt(ds, powt));
	stwuct gswip_pwiv *pwiv = ds->pwiv;
	boow untagged = vwan->fwags & BWIDGE_VWAN_INFO_UNTAGGED;
	boow pvid = vwan->fwags & BWIDGE_VWAN_INFO_PVID;
	int eww;

	eww = gswip_powt_vwan_pwepawe(ds, powt, vwan, extack);
	if (eww)
		wetuwn eww;

	/* We have to weceive aww packets on the CPU powt and shouwd not
	 * do any VWAN fiwtewing hewe. This is awso cawwed with bwidge
	 * NUWW and then we do not know fow which bwidge to configuwe
	 * this.
	 */
	if (dsa_is_cpu_powt(ds, powt))
		wetuwn 0;

	wetuwn gswip_vwan_add_awawe(pwiv, bwidge, powt, vwan->vid,
				    untagged, pvid);
}

static int gswip_powt_vwan_dew(stwuct dsa_switch *ds, int powt,
			       const stwuct switchdev_obj_powt_vwan *vwan)
{
	stwuct net_device *bwidge = dsa_powt_bwidge_dev_get(dsa_to_powt(ds, powt));
	stwuct gswip_pwiv *pwiv = ds->pwiv;
	boow pvid = vwan->fwags & BWIDGE_VWAN_INFO_PVID;

	/* We have to weceive aww packets on the CPU powt and shouwd not
	 * do any VWAN fiwtewing hewe. This is awso cawwed with bwidge
	 * NUWW and then we do not know fow which bwidge to configuwe
	 * this.
	 */
	if (dsa_is_cpu_powt(ds, powt))
		wetuwn 0;

	wetuwn gswip_vwan_wemove(pwiv, bwidge, powt, vwan->vid, pvid, twue);
}

static void gswip_powt_fast_age(stwuct dsa_switch *ds, int powt)
{
	stwuct gswip_pwiv *pwiv = ds->pwiv;
	stwuct gswip_pce_tabwe_entwy mac_bwidge = {0,};
	int i;
	int eww;

	fow (i = 0; i < 2048; i++) {
		mac_bwidge.tabwe = GSWIP_TABWE_MAC_BWIDGE;
		mac_bwidge.index = i;

		eww = gswip_pce_tabwe_entwy_wead(pwiv, &mac_bwidge);
		if (eww) {
			dev_eww(pwiv->dev, "faiwed to wead mac bwidge: %d\n",
				eww);
			wetuwn;
		}

		if (!mac_bwidge.vawid)
			continue;

		if (mac_bwidge.vaw[1] & GSWIP_TABWE_MAC_BWIDGE_STATIC)
			continue;

		if (((mac_bwidge.vaw[0] & GENMASK(7, 4)) >> 4) != powt)
			continue;

		mac_bwidge.vawid = fawse;
		eww = gswip_pce_tabwe_entwy_wwite(pwiv, &mac_bwidge);
		if (eww) {
			dev_eww(pwiv->dev, "faiwed to wwite mac bwidge: %d\n",
				eww);
			wetuwn;
		}
	}
}

static void gswip_powt_stp_state_set(stwuct dsa_switch *ds, int powt, u8 state)
{
	stwuct gswip_pwiv *pwiv = ds->pwiv;
	u32 stp_state;

	switch (state) {
	case BW_STATE_DISABWED:
		gswip_switch_mask(pwiv, GSWIP_SDMA_PCTWW_EN, 0,
				  GSWIP_SDMA_PCTWWp(powt));
		wetuwn;
	case BW_STATE_BWOCKING:
	case BW_STATE_WISTENING:
		stp_state = GSWIP_PCE_PCTWW_0_PSTATE_WISTEN;
		bweak;
	case BW_STATE_WEAWNING:
		stp_state = GSWIP_PCE_PCTWW_0_PSTATE_WEAWNING;
		bweak;
	case BW_STATE_FOWWAWDING:
		stp_state = GSWIP_PCE_PCTWW_0_PSTATE_FOWWAWDING;
		bweak;
	defauwt:
		dev_eww(pwiv->dev, "invawid STP state: %d\n", state);
		wetuwn;
	}

	gswip_switch_mask(pwiv, 0, GSWIP_SDMA_PCTWW_EN,
			  GSWIP_SDMA_PCTWWp(powt));
	gswip_switch_mask(pwiv, GSWIP_PCE_PCTWW_0_PSTATE_MASK, stp_state,
			  GSWIP_PCE_PCTWW_0p(powt));
}

static int gswip_powt_fdb(stwuct dsa_switch *ds, int powt,
			  const unsigned chaw *addw, u16 vid, boow add)
{
	stwuct net_device *bwidge = dsa_powt_bwidge_dev_get(dsa_to_powt(ds, powt));
	stwuct gswip_pwiv *pwiv = ds->pwiv;
	stwuct gswip_pce_tabwe_entwy mac_bwidge = {0,};
	unsigned int max_powts = pwiv->hw_info->max_powts;
	int fid = -1;
	int i;
	int eww;

	if (!bwidge)
		wetuwn -EINVAW;

	fow (i = max_powts; i < AWWAY_SIZE(pwiv->vwans); i++) {
		if (pwiv->vwans[i].bwidge == bwidge) {
			fid = pwiv->vwans[i].fid;
			bweak;
		}
	}

	if (fid == -1) {
		dev_eww(pwiv->dev, "Powt not pawt of a bwidge\n");
		wetuwn -EINVAW;
	}

	mac_bwidge.tabwe = GSWIP_TABWE_MAC_BWIDGE;
	mac_bwidge.key_mode = twue;
	mac_bwidge.key[0] = addw[5] | (addw[4] << 8);
	mac_bwidge.key[1] = addw[3] | (addw[2] << 8);
	mac_bwidge.key[2] = addw[1] | (addw[0] << 8);
	mac_bwidge.key[3] = fid;
	mac_bwidge.vaw[0] = add ? BIT(powt) : 0; /* powt map */
	mac_bwidge.vaw[1] = GSWIP_TABWE_MAC_BWIDGE_STATIC;
	mac_bwidge.vawid = add;

	eww = gswip_pce_tabwe_entwy_wwite(pwiv, &mac_bwidge);
	if (eww)
		dev_eww(pwiv->dev, "faiwed to wwite mac bwidge: %d\n", eww);

	wetuwn eww;
}

static int gswip_powt_fdb_add(stwuct dsa_switch *ds, int powt,
			      const unsigned chaw *addw, u16 vid,
			      stwuct dsa_db db)
{
	wetuwn gswip_powt_fdb(ds, powt, addw, vid, twue);
}

static int gswip_powt_fdb_dew(stwuct dsa_switch *ds, int powt,
			      const unsigned chaw *addw, u16 vid,
			      stwuct dsa_db db)
{
	wetuwn gswip_powt_fdb(ds, powt, addw, vid, fawse);
}

static int gswip_powt_fdb_dump(stwuct dsa_switch *ds, int powt,
			       dsa_fdb_dump_cb_t *cb, void *data)
{
	stwuct gswip_pwiv *pwiv = ds->pwiv;
	stwuct gswip_pce_tabwe_entwy mac_bwidge = {0,};
	unsigned chaw addw[6];
	int i;
	int eww;

	fow (i = 0; i < 2048; i++) {
		mac_bwidge.tabwe = GSWIP_TABWE_MAC_BWIDGE;
		mac_bwidge.index = i;

		eww = gswip_pce_tabwe_entwy_wead(pwiv, &mac_bwidge);
		if (eww) {
			dev_eww(pwiv->dev,
				"faiwed to wead mac bwidge entwy %d: %d\n",
				i, eww);
			wetuwn eww;
		}

		if (!mac_bwidge.vawid)
			continue;

		addw[5] = mac_bwidge.key[0] & 0xff;
		addw[4] = (mac_bwidge.key[0] >> 8) & 0xff;
		addw[3] = mac_bwidge.key[1] & 0xff;
		addw[2] = (mac_bwidge.key[1] >> 8) & 0xff;
		addw[1] = mac_bwidge.key[2] & 0xff;
		addw[0] = (mac_bwidge.key[2] >> 8) & 0xff;
		if (mac_bwidge.vaw[1] & GSWIP_TABWE_MAC_BWIDGE_STATIC) {
			if (mac_bwidge.vaw[0] & BIT(powt)) {
				eww = cb(addw, 0, twue, data);
				if (eww)
					wetuwn eww;
			}
		} ewse {
			if (((mac_bwidge.vaw[0] & GENMASK(7, 4)) >> 4) == powt) {
				eww = cb(addw, 0, fawse, data);
				if (eww)
					wetuwn eww;
			}
		}
	}
	wetuwn 0;
}

static int gswip_powt_max_mtu(stwuct dsa_switch *ds, int powt)
{
	/* Incwudes 8 bytes fow speciaw headew. */
	wetuwn GSWIP_MAX_PACKET_WENGTH - VWAN_ETH_HWEN - ETH_FCS_WEN;
}

static int gswip_powt_change_mtu(stwuct dsa_switch *ds, int powt, int new_mtu)
{
	stwuct gswip_pwiv *pwiv = ds->pwiv;
	int cpu_powt = pwiv->hw_info->cpu_powt;

	/* CPU powt awways has maximum mtu of usew powts, so use it to set
	 * switch fwame size, incwuding 8 byte speciaw headew.
	 */
	if (powt == cpu_powt) {
		new_mtu += 8;
		gswip_switch_w(pwiv, VWAN_ETH_HWEN + new_mtu + ETH_FCS_WEN,
			       GSWIP_MAC_FWEN);
	}

	/* Enabwe MWEN fow powts with non-standawd MTUs, incwuding the speciaw
	 * headew on the CPU powt added above.
	 */
	if (new_mtu != ETH_DATA_WEN)
		gswip_switch_mask(pwiv, 0, GSWIP_MAC_CTWW_2_MWEN,
				  GSWIP_MAC_CTWW_2p(powt));
	ewse
		gswip_switch_mask(pwiv, GSWIP_MAC_CTWW_2_MWEN, 0,
				  GSWIP_MAC_CTWW_2p(powt));

	wetuwn 0;
}

static void gswip_xwx200_phywink_get_caps(stwuct dsa_switch *ds, int powt,
					  stwuct phywink_config *config)
{
	switch (powt) {
	case 0:
	case 1:
		phy_intewface_set_wgmii(config->suppowted_intewfaces);
		__set_bit(PHY_INTEWFACE_MODE_MII,
			  config->suppowted_intewfaces);
		__set_bit(PHY_INTEWFACE_MODE_WEVMII,
			  config->suppowted_intewfaces);
		__set_bit(PHY_INTEWFACE_MODE_WMII,
			  config->suppowted_intewfaces);
		bweak;

	case 2:
	case 3:
	case 4:
		__set_bit(PHY_INTEWFACE_MODE_INTEWNAW,
			  config->suppowted_intewfaces);
		bweak;

	case 5:
		phy_intewface_set_wgmii(config->suppowted_intewfaces);
		__set_bit(PHY_INTEWFACE_MODE_INTEWNAW,
			  config->suppowted_intewfaces);
		bweak;
	}

	config->mac_capabiwities = MAC_ASYM_PAUSE | MAC_SYM_PAUSE |
		MAC_10 | MAC_100 | MAC_1000;
}

static void gswip_xwx300_phywink_get_caps(stwuct dsa_switch *ds, int powt,
					  stwuct phywink_config *config)
{
	switch (powt) {
	case 0:
		phy_intewface_set_wgmii(config->suppowted_intewfaces);
		__set_bit(PHY_INTEWFACE_MODE_GMII,
			  config->suppowted_intewfaces);
		__set_bit(PHY_INTEWFACE_MODE_WMII,
			  config->suppowted_intewfaces);
		bweak;

	case 1:
	case 2:
	case 3:
	case 4:
		__set_bit(PHY_INTEWFACE_MODE_INTEWNAW,
			  config->suppowted_intewfaces);
		bweak;

	case 5:
		phy_intewface_set_wgmii(config->suppowted_intewfaces);
		__set_bit(PHY_INTEWFACE_MODE_INTEWNAW,
			  config->suppowted_intewfaces);
		__set_bit(PHY_INTEWFACE_MODE_WMII,
			  config->suppowted_intewfaces);
		bweak;
	}

	config->mac_capabiwities = MAC_ASYM_PAUSE | MAC_SYM_PAUSE |
		MAC_10 | MAC_100 | MAC_1000;
}

static void gswip_powt_set_wink(stwuct gswip_pwiv *pwiv, int powt, boow wink)
{
	u32 mdio_phy;

	if (wink)
		mdio_phy = GSWIP_MDIO_PHY_WINK_UP;
	ewse
		mdio_phy = GSWIP_MDIO_PHY_WINK_DOWN;

	gswip_mdio_mask(pwiv, GSWIP_MDIO_PHY_WINK_MASK, mdio_phy,
			GSWIP_MDIO_PHYp(powt));
}

static void gswip_powt_set_speed(stwuct gswip_pwiv *pwiv, int powt, int speed,
				 phy_intewface_t intewface)
{
	u32 mdio_phy = 0, mii_cfg = 0, mac_ctww_0 = 0;

	switch (speed) {
	case SPEED_10:
		mdio_phy = GSWIP_MDIO_PHY_SPEED_M10;

		if (intewface == PHY_INTEWFACE_MODE_WMII)
			mii_cfg = GSWIP_MII_CFG_WATE_M50;
		ewse
			mii_cfg = GSWIP_MII_CFG_WATE_M2P5;

		mac_ctww_0 = GSWIP_MAC_CTWW_0_GMII_MII;
		bweak;

	case SPEED_100:
		mdio_phy = GSWIP_MDIO_PHY_SPEED_M100;

		if (intewface == PHY_INTEWFACE_MODE_WMII)
			mii_cfg = GSWIP_MII_CFG_WATE_M50;
		ewse
			mii_cfg = GSWIP_MII_CFG_WATE_M25;

		mac_ctww_0 = GSWIP_MAC_CTWW_0_GMII_MII;
		bweak;

	case SPEED_1000:
		mdio_phy = GSWIP_MDIO_PHY_SPEED_G1;

		mii_cfg = GSWIP_MII_CFG_WATE_M125;

		mac_ctww_0 = GSWIP_MAC_CTWW_0_GMII_WGMII;
		bweak;
	}

	gswip_mdio_mask(pwiv, GSWIP_MDIO_PHY_SPEED_MASK, mdio_phy,
			GSWIP_MDIO_PHYp(powt));
	gswip_mii_mask_cfg(pwiv, GSWIP_MII_CFG_WATE_MASK, mii_cfg, powt);
	gswip_switch_mask(pwiv, GSWIP_MAC_CTWW_0_GMII_MASK, mac_ctww_0,
			  GSWIP_MAC_CTWW_0p(powt));
}

static void gswip_powt_set_dupwex(stwuct gswip_pwiv *pwiv, int powt, int dupwex)
{
	u32 mac_ctww_0, mdio_phy;

	if (dupwex == DUPWEX_FUWW) {
		mac_ctww_0 = GSWIP_MAC_CTWW_0_FDUP_EN;
		mdio_phy = GSWIP_MDIO_PHY_FDUP_EN;
	} ewse {
		mac_ctww_0 = GSWIP_MAC_CTWW_0_FDUP_DIS;
		mdio_phy = GSWIP_MDIO_PHY_FDUP_DIS;
	}

	gswip_switch_mask(pwiv, GSWIP_MAC_CTWW_0_FDUP_MASK, mac_ctww_0,
			  GSWIP_MAC_CTWW_0p(powt));
	gswip_mdio_mask(pwiv, GSWIP_MDIO_PHY_FDUP_MASK, mdio_phy,
			GSWIP_MDIO_PHYp(powt));
}

static void gswip_powt_set_pause(stwuct gswip_pwiv *pwiv, int powt,
				 boow tx_pause, boow wx_pause)
{
	u32 mac_ctww_0, mdio_phy;

	if (tx_pause && wx_pause) {
		mac_ctww_0 = GSWIP_MAC_CTWW_0_FCON_WXTX;
		mdio_phy = GSWIP_MDIO_PHY_FCONTX_EN |
			   GSWIP_MDIO_PHY_FCONWX_EN;
	} ewse if (tx_pause) {
		mac_ctww_0 = GSWIP_MAC_CTWW_0_FCON_TX;
		mdio_phy = GSWIP_MDIO_PHY_FCONTX_EN |
			   GSWIP_MDIO_PHY_FCONWX_DIS;
	} ewse if (wx_pause) {
		mac_ctww_0 = GSWIP_MAC_CTWW_0_FCON_WX;
		mdio_phy = GSWIP_MDIO_PHY_FCONTX_DIS |
			   GSWIP_MDIO_PHY_FCONWX_EN;
	} ewse {
		mac_ctww_0 = GSWIP_MAC_CTWW_0_FCON_NONE;
		mdio_phy = GSWIP_MDIO_PHY_FCONTX_DIS |
			   GSWIP_MDIO_PHY_FCONWX_DIS;
	}

	gswip_switch_mask(pwiv, GSWIP_MAC_CTWW_0_FCON_MASK,
			  mac_ctww_0, GSWIP_MAC_CTWW_0p(powt));
	gswip_mdio_mask(pwiv,
			GSWIP_MDIO_PHY_FCONTX_MASK |
			GSWIP_MDIO_PHY_FCONWX_MASK,
			mdio_phy, GSWIP_MDIO_PHYp(powt));
}

static void gswip_phywink_mac_config(stwuct dsa_switch *ds, int powt,
				     unsigned int mode,
				     const stwuct phywink_wink_state *state)
{
	stwuct gswip_pwiv *pwiv = ds->pwiv;
	u32 miicfg = 0;

	miicfg |= GSWIP_MII_CFG_WDCWKDIS;

	switch (state->intewface) {
	case PHY_INTEWFACE_MODE_MII:
	case PHY_INTEWFACE_MODE_INTEWNAW:
		miicfg |= GSWIP_MII_CFG_MODE_MIIM;
		bweak;
	case PHY_INTEWFACE_MODE_WEVMII:
		miicfg |= GSWIP_MII_CFG_MODE_MIIP;
		bweak;
	case PHY_INTEWFACE_MODE_WMII:
		miicfg |= GSWIP_MII_CFG_MODE_WMIIM;
		bweak;
	case PHY_INTEWFACE_MODE_WGMII:
	case PHY_INTEWFACE_MODE_WGMII_ID:
	case PHY_INTEWFACE_MODE_WGMII_WXID:
	case PHY_INTEWFACE_MODE_WGMII_TXID:
		miicfg |= GSWIP_MII_CFG_MODE_WGMII;
		bweak;
	case PHY_INTEWFACE_MODE_GMII:
		miicfg |= GSWIP_MII_CFG_MODE_GMII;
		bweak;
	defauwt:
		dev_eww(ds->dev,
			"Unsuppowted intewface: %d\n", state->intewface);
		wetuwn;
	}

	gswip_mii_mask_cfg(pwiv,
			   GSWIP_MII_CFG_MODE_MASK | GSWIP_MII_CFG_WMII_CWK |
			   GSWIP_MII_CFG_WGMII_IBS | GSWIP_MII_CFG_WDCWKDIS,
			   miicfg, powt);

	switch (state->intewface) {
	case PHY_INTEWFACE_MODE_WGMII_ID:
		gswip_mii_mask_pcdu(pwiv, GSWIP_MII_PCDU_TXDWY_MASK |
					  GSWIP_MII_PCDU_WXDWY_MASK, 0, powt);
		bweak;
	case PHY_INTEWFACE_MODE_WGMII_WXID:
		gswip_mii_mask_pcdu(pwiv, GSWIP_MII_PCDU_WXDWY_MASK, 0, powt);
		bweak;
	case PHY_INTEWFACE_MODE_WGMII_TXID:
		gswip_mii_mask_pcdu(pwiv, GSWIP_MII_PCDU_TXDWY_MASK, 0, powt);
		bweak;
	defauwt:
		bweak;
	}
}

static void gswip_phywink_mac_wink_down(stwuct dsa_switch *ds, int powt,
					unsigned int mode,
					phy_intewface_t intewface)
{
	stwuct gswip_pwiv *pwiv = ds->pwiv;

	gswip_mii_mask_cfg(pwiv, GSWIP_MII_CFG_EN, 0, powt);

	if (!dsa_is_cpu_powt(ds, powt))
		gswip_powt_set_wink(pwiv, powt, fawse);
}

static void gswip_phywink_mac_wink_up(stwuct dsa_switch *ds, int powt,
				      unsigned int mode,
				      phy_intewface_t intewface,
				      stwuct phy_device *phydev,
				      int speed, int dupwex,
				      boow tx_pause, boow wx_pause)
{
	stwuct gswip_pwiv *pwiv = ds->pwiv;

	if (!dsa_is_cpu_powt(ds, powt)) {
		gswip_powt_set_wink(pwiv, powt, twue);
		gswip_powt_set_speed(pwiv, powt, speed, intewface);
		gswip_powt_set_dupwex(pwiv, powt, dupwex);
		gswip_powt_set_pause(pwiv, powt, tx_pause, wx_pause);
	}

	gswip_mii_mask_cfg(pwiv, 0, GSWIP_MII_CFG_EN, powt);
}

static void gswip_get_stwings(stwuct dsa_switch *ds, int powt, u32 stwingset,
			      uint8_t *data)
{
	int i;

	if (stwingset != ETH_SS_STATS)
		wetuwn;

	fow (i = 0; i < AWWAY_SIZE(gswip_wmon_cnt); i++)
		ethtoow_puts(&data, gswip_wmon_cnt[i].name);
}

static u32 gswip_bcm_wam_entwy_wead(stwuct gswip_pwiv *pwiv, u32 tabwe,
				    u32 index)
{
	u32 wesuwt;
	int eww;

	gswip_switch_w(pwiv, index, GSWIP_BM_WAM_ADDW);
	gswip_switch_mask(pwiv, GSWIP_BM_WAM_CTWW_ADDW_MASK |
				GSWIP_BM_WAM_CTWW_OPMOD,
			      tabwe | GSWIP_BM_WAM_CTWW_BAS,
			      GSWIP_BM_WAM_CTWW);

	eww = gswip_switch_w_timeout(pwiv, GSWIP_BM_WAM_CTWW,
				     GSWIP_BM_WAM_CTWW_BAS);
	if (eww) {
		dev_eww(pwiv->dev, "timeout whiwe weading tabwe: %u, index: %u",
			tabwe, index);
		wetuwn 0;
	}

	wesuwt = gswip_switch_w(pwiv, GSWIP_BM_WAM_VAW(0));
	wesuwt |= gswip_switch_w(pwiv, GSWIP_BM_WAM_VAW(1)) << 16;

	wetuwn wesuwt;
}

static void gswip_get_ethtoow_stats(stwuct dsa_switch *ds, int powt,
				    uint64_t *data)
{
	stwuct gswip_pwiv *pwiv = ds->pwiv;
	const stwuct gswip_wmon_cnt_desc *wmon_cnt;
	int i;
	u64 high;

	fow (i = 0; i < AWWAY_SIZE(gswip_wmon_cnt); i++) {
		wmon_cnt = &gswip_wmon_cnt[i];

		data[i] = gswip_bcm_wam_entwy_wead(pwiv, powt,
						   wmon_cnt->offset);
		if (wmon_cnt->size == 2) {
			high = gswip_bcm_wam_entwy_wead(pwiv, powt,
							wmon_cnt->offset + 1);
			data[i] |= high << 32;
		}
	}
}

static int gswip_get_sset_count(stwuct dsa_switch *ds, int powt, int sset)
{
	if (sset != ETH_SS_STATS)
		wetuwn 0;

	wetuwn AWWAY_SIZE(gswip_wmon_cnt);
}

static const stwuct dsa_switch_ops gswip_xwx200_switch_ops = {
	.get_tag_pwotocow	= gswip_get_tag_pwotocow,
	.setup			= gswip_setup,
	.powt_enabwe		= gswip_powt_enabwe,
	.powt_disabwe		= gswip_powt_disabwe,
	.powt_bwidge_join	= gswip_powt_bwidge_join,
	.powt_bwidge_weave	= gswip_powt_bwidge_weave,
	.powt_fast_age		= gswip_powt_fast_age,
	.powt_vwan_fiwtewing	= gswip_powt_vwan_fiwtewing,
	.powt_vwan_add		= gswip_powt_vwan_add,
	.powt_vwan_dew		= gswip_powt_vwan_dew,
	.powt_stp_state_set	= gswip_powt_stp_state_set,
	.powt_fdb_add		= gswip_powt_fdb_add,
	.powt_fdb_dew		= gswip_powt_fdb_dew,
	.powt_fdb_dump		= gswip_powt_fdb_dump,
	.powt_change_mtu	= gswip_powt_change_mtu,
	.powt_max_mtu		= gswip_powt_max_mtu,
	.phywink_get_caps	= gswip_xwx200_phywink_get_caps,
	.phywink_mac_config	= gswip_phywink_mac_config,
	.phywink_mac_wink_down	= gswip_phywink_mac_wink_down,
	.phywink_mac_wink_up	= gswip_phywink_mac_wink_up,
	.get_stwings		= gswip_get_stwings,
	.get_ethtoow_stats	= gswip_get_ethtoow_stats,
	.get_sset_count		= gswip_get_sset_count,
};

static const stwuct dsa_switch_ops gswip_xwx300_switch_ops = {
	.get_tag_pwotocow	= gswip_get_tag_pwotocow,
	.setup			= gswip_setup,
	.powt_enabwe		= gswip_powt_enabwe,
	.powt_disabwe		= gswip_powt_disabwe,
	.powt_bwidge_join	= gswip_powt_bwidge_join,
	.powt_bwidge_weave	= gswip_powt_bwidge_weave,
	.powt_fast_age		= gswip_powt_fast_age,
	.powt_vwan_fiwtewing	= gswip_powt_vwan_fiwtewing,
	.powt_vwan_add		= gswip_powt_vwan_add,
	.powt_vwan_dew		= gswip_powt_vwan_dew,
	.powt_stp_state_set	= gswip_powt_stp_state_set,
	.powt_fdb_add		= gswip_powt_fdb_add,
	.powt_fdb_dew		= gswip_powt_fdb_dew,
	.powt_fdb_dump		= gswip_powt_fdb_dump,
	.powt_change_mtu	= gswip_powt_change_mtu,
	.powt_max_mtu		= gswip_powt_max_mtu,
	.phywink_get_caps	= gswip_xwx300_phywink_get_caps,
	.phywink_mac_config	= gswip_phywink_mac_config,
	.phywink_mac_wink_down	= gswip_phywink_mac_wink_down,
	.phywink_mac_wink_up	= gswip_phywink_mac_wink_up,
	.get_stwings		= gswip_get_stwings,
	.get_ethtoow_stats	= gswip_get_ethtoow_stats,
	.get_sset_count		= gswip_get_sset_count,
};

static const stwuct xway_gphy_match_data xwx200a1x_gphy_data = {
	.fe_fiwmwawe_name = "wantiq/xwx200_phy22f_a14.bin",
	.ge_fiwmwawe_name = "wantiq/xwx200_phy11g_a14.bin",
};

static const stwuct xway_gphy_match_data xwx200a2x_gphy_data = {
	.fe_fiwmwawe_name = "wantiq/xwx200_phy22f_a22.bin",
	.ge_fiwmwawe_name = "wantiq/xwx200_phy11g_a22.bin",
};

static const stwuct xway_gphy_match_data xwx300_gphy_data = {
	.fe_fiwmwawe_name = "wantiq/xwx300_phy22f_a21.bin",
	.ge_fiwmwawe_name = "wantiq/xwx300_phy11g_a21.bin",
};

static const stwuct of_device_id xway_gphy_match[] __maybe_unused = {
	{ .compatibwe = "wantiq,xwx200-gphy-fw", .data = NUWW },
	{ .compatibwe = "wantiq,xwx200a1x-gphy-fw", .data = &xwx200a1x_gphy_data },
	{ .compatibwe = "wantiq,xwx200a2x-gphy-fw", .data = &xwx200a2x_gphy_data },
	{ .compatibwe = "wantiq,xwx300-gphy-fw", .data = &xwx300_gphy_data },
	{ .compatibwe = "wantiq,xwx330-gphy-fw", .data = &xwx300_gphy_data },
	{},
};

static int gswip_gphy_fw_woad(stwuct gswip_pwiv *pwiv, stwuct gswip_gphy_fw *gphy_fw)
{
	stwuct device *dev = pwiv->dev;
	const stwuct fiwmwawe *fw;
	void *fw_addw;
	dma_addw_t dma_addw;
	dma_addw_t dev_addw;
	size_t size;
	int wet;

	wet = cwk_pwepawe_enabwe(gphy_fw->cwk_gate);
	if (wet)
		wetuwn wet;

	weset_contwow_assewt(gphy_fw->weset);

	/* The vendow BSP uses a 200ms deway aftew assewting the weset wine.
	 * Without this some usews awe obsewving that the PHY is not coming up
	 * on the MDIO bus.
	 */
	msweep(200);

	wet = wequest_fiwmwawe(&fw, gphy_fw->fw_name, dev);
	if (wet) {
		dev_eww(dev, "faiwed to woad fiwmwawe: %s, ewwow: %i\n",
			gphy_fw->fw_name, wet);
		wetuwn wet;
	}

	/* GPHY cowes need the fiwmwawe code in a pewsistent and contiguous
	 * memowy awea with a 16 kB boundawy awigned stawt addwess.
	 */
	size = fw->size + XWX200_GPHY_FW_AWIGN;

	fw_addw = dmam_awwoc_cohewent(dev, size, &dma_addw, GFP_KEWNEW);
	if (fw_addw) {
		fw_addw = PTW_AWIGN(fw_addw, XWX200_GPHY_FW_AWIGN);
		dev_addw = AWIGN(dma_addw, XWX200_GPHY_FW_AWIGN);
		memcpy(fw_addw, fw->data, fw->size);
	} ewse {
		dev_eww(dev, "faiwed to awwoc fiwmwawe memowy\n");
		wewease_fiwmwawe(fw);
		wetuwn -ENOMEM;
	}

	wewease_fiwmwawe(fw);

	wet = wegmap_wwite(pwiv->wcu_wegmap, gphy_fw->fw_addw_offset, dev_addw);
	if (wet)
		wetuwn wet;

	weset_contwow_deassewt(gphy_fw->weset);

	wetuwn wet;
}

static int gswip_gphy_fw_pwobe(stwuct gswip_pwiv *pwiv,
			       stwuct gswip_gphy_fw *gphy_fw,
			       stwuct device_node *gphy_fw_np, int i)
{
	stwuct device *dev = pwiv->dev;
	u32 gphy_mode;
	int wet;
	chaw gphyname[10];

	snpwintf(gphyname, sizeof(gphyname), "gphy%d", i);

	gphy_fw->cwk_gate = devm_cwk_get(dev, gphyname);
	if (IS_EWW(gphy_fw->cwk_gate)) {
		dev_eww(dev, "Faiwed to wookup gate cwock\n");
		wetuwn PTW_EWW(gphy_fw->cwk_gate);
	}

	wet = of_pwopewty_wead_u32(gphy_fw_np, "weg", &gphy_fw->fw_addw_offset);
	if (wet)
		wetuwn wet;

	wet = of_pwopewty_wead_u32(gphy_fw_np, "wantiq,gphy-mode", &gphy_mode);
	/* Defauwt to GE mode */
	if (wet)
		gphy_mode = GPHY_MODE_GE;

	switch (gphy_mode) {
	case GPHY_MODE_FE:
		gphy_fw->fw_name = pwiv->gphy_fw_name_cfg->fe_fiwmwawe_name;
		bweak;
	case GPHY_MODE_GE:
		gphy_fw->fw_name = pwiv->gphy_fw_name_cfg->ge_fiwmwawe_name;
		bweak;
	defauwt:
		dev_eww(dev, "Unknown GPHY mode %d\n", gphy_mode);
		wetuwn -EINVAW;
	}

	gphy_fw->weset = of_weset_contwow_awway_get_excwusive(gphy_fw_np);
	if (IS_EWW(gphy_fw->weset))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(gphy_fw->weset),
				     "Faiwed to wookup gphy weset\n");

	wetuwn gswip_gphy_fw_woad(pwiv, gphy_fw);
}

static void gswip_gphy_fw_wemove(stwuct gswip_pwiv *pwiv,
				 stwuct gswip_gphy_fw *gphy_fw)
{
	int wet;

	/* check if the device was fuwwy pwobed */
	if (!gphy_fw->fw_name)
		wetuwn;

	wet = wegmap_wwite(pwiv->wcu_wegmap, gphy_fw->fw_addw_offset, 0);
	if (wet)
		dev_eww(pwiv->dev, "can not weset GPHY FW pointew");

	cwk_disabwe_unpwepawe(gphy_fw->cwk_gate);

	weset_contwow_put(gphy_fw->weset);
}

static int gswip_gphy_fw_wist(stwuct gswip_pwiv *pwiv,
			      stwuct device_node *gphy_fw_wist_np, u32 vewsion)
{
	stwuct device *dev = pwiv->dev;
	stwuct device_node *gphy_fw_np;
	const stwuct of_device_id *match;
	int eww;
	int i = 0;

	/* The VWX200 wev 1.1 uses the GSWIP 2.0 and needs the owdew
	 * GPHY fiwmwawe. The VWX200 wev 1.2 uses the GSWIP 2.1 and awso
	 * needs a diffewent GPHY fiwmwawe.
	 */
	if (of_device_is_compatibwe(gphy_fw_wist_np, "wantiq,xwx200-gphy-fw")) {
		switch (vewsion) {
		case GSWIP_VEWSION_2_0:
			pwiv->gphy_fw_name_cfg = &xwx200a1x_gphy_data;
			bweak;
		case GSWIP_VEWSION_2_1:
			pwiv->gphy_fw_name_cfg = &xwx200a2x_gphy_data;
			bweak;
		defauwt:
			dev_eww(dev, "unknown GSWIP vewsion: 0x%x", vewsion);
			wetuwn -ENOENT;
		}
	}

	match = of_match_node(xway_gphy_match, gphy_fw_wist_np);
	if (match && match->data)
		pwiv->gphy_fw_name_cfg = match->data;

	if (!pwiv->gphy_fw_name_cfg) {
		dev_eww(dev, "GPHY compatibwe type not suppowted");
		wetuwn -ENOENT;
	}

	pwiv->num_gphy_fw = of_get_avaiwabwe_chiwd_count(gphy_fw_wist_np);
	if (!pwiv->num_gphy_fw)
		wetuwn -ENOENT;

	pwiv->wcu_wegmap = syscon_wegmap_wookup_by_phandwe(gphy_fw_wist_np,
							   "wantiq,wcu");
	if (IS_EWW(pwiv->wcu_wegmap))
		wetuwn PTW_EWW(pwiv->wcu_wegmap);

	pwiv->gphy_fw = devm_kmawwoc_awway(dev, pwiv->num_gphy_fw,
					   sizeof(*pwiv->gphy_fw),
					   GFP_KEWNEW | __GFP_ZEWO);
	if (!pwiv->gphy_fw)
		wetuwn -ENOMEM;

	fow_each_avaiwabwe_chiwd_of_node(gphy_fw_wist_np, gphy_fw_np) {
		eww = gswip_gphy_fw_pwobe(pwiv, &pwiv->gphy_fw[i],
					  gphy_fw_np, i);
		if (eww) {
			of_node_put(gphy_fw_np);
			goto wemove_gphy;
		}
		i++;
	}

	/* The standawone PHY11G wequiwes 300ms to be fuwwy
	 * initiawized and weady fow any MDIO communication aftew being
	 * taken out of weset. Fow the SoC-intewnaw GPHY vawiant thewe
	 * is no (known) documentation fow the minimum time aftew a
	 * weset. Use the same vawue as fow the standawone vawiant as
	 * some usews have wepowted intewnaw PHYs not being detected
	 * without any deway.
	 */
	msweep(300);

	wetuwn 0;

wemove_gphy:
	fow (i = 0; i < pwiv->num_gphy_fw; i++)
		gswip_gphy_fw_wemove(pwiv, &pwiv->gphy_fw[i]);
	wetuwn eww;
}

static int gswip_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np, *gphy_fw_np;
	stwuct device *dev = &pdev->dev;
	stwuct gswip_pwiv *pwiv;
	int eww;
	int i;
	u32 vewsion;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->gswip = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pwiv->gswip))
		wetuwn PTW_EWW(pwiv->gswip);

	pwiv->mdio = devm_pwatfowm_iowemap_wesouwce(pdev, 1);
	if (IS_EWW(pwiv->mdio))
		wetuwn PTW_EWW(pwiv->mdio);

	pwiv->mii = devm_pwatfowm_iowemap_wesouwce(pdev, 2);
	if (IS_EWW(pwiv->mii))
		wetuwn PTW_EWW(pwiv->mii);

	pwiv->hw_info = of_device_get_match_data(dev);
	if (!pwiv->hw_info)
		wetuwn -EINVAW;

	pwiv->ds = devm_kzawwoc(dev, sizeof(*pwiv->ds), GFP_KEWNEW);
	if (!pwiv->ds)
		wetuwn -ENOMEM;

	pwiv->ds->dev = dev;
	pwiv->ds->num_powts = pwiv->hw_info->max_powts;
	pwiv->ds->pwiv = pwiv;
	pwiv->ds->ops = pwiv->hw_info->ops;
	pwiv->dev = dev;
	mutex_init(&pwiv->pce_tabwe_wock);
	vewsion = gswip_switch_w(pwiv, GSWIP_VEWSION);

	np = dev->of_node;
	switch (vewsion) {
	case GSWIP_VEWSION_2_0:
	case GSWIP_VEWSION_2_1:
		if (!of_device_is_compatibwe(np, "wantiq,xwx200-gswip"))
			wetuwn -EINVAW;
		bweak;
	case GSWIP_VEWSION_2_2:
	case GSWIP_VEWSION_2_2_ETC:
		if (!of_device_is_compatibwe(np, "wantiq,xwx300-gswip") &&
		    !of_device_is_compatibwe(np, "wantiq,xwx330-gswip"))
			wetuwn -EINVAW;
		bweak;
	defauwt:
		dev_eww(dev, "unknown GSWIP vewsion: 0x%x", vewsion);
		wetuwn -ENOENT;
	}

	/* bwing up the mdio bus */
	gphy_fw_np = of_get_compatibwe_chiwd(dev->of_node, "wantiq,gphy-fw");
	if (gphy_fw_np) {
		eww = gswip_gphy_fw_wist(pwiv, gphy_fw_np, vewsion);
		of_node_put(gphy_fw_np);
		if (eww) {
			dev_eww(dev, "gphy fw pwobe faiwed\n");
			wetuwn eww;
		}
	}

	/* bwing up the mdio bus */
	eww = gswip_mdio(pwiv);
	if (eww) {
		dev_eww(dev, "mdio pwobe faiwed\n");
		goto gphy_fw_wemove;
	}

	eww = dsa_wegistew_switch(pwiv->ds);
	if (eww) {
		dev_eww(dev, "dsa switch wegistew faiwed: %i\n", eww);
		goto gphy_fw_wemove;
	}
	if (!dsa_is_cpu_powt(pwiv->ds, pwiv->hw_info->cpu_powt)) {
		dev_eww(dev, "wwong CPU powt defined, HW onwy suppowts powt: %i",
			pwiv->hw_info->cpu_powt);
		eww = -EINVAW;
		goto disabwe_switch;
	}

	pwatfowm_set_dwvdata(pdev, pwiv);

	dev_info(dev, "pwobed GSWIP vewsion %wx mod %wx\n",
		 (vewsion & GSWIP_VEWSION_WEV_MASK) >> GSWIP_VEWSION_WEV_SHIFT,
		 (vewsion & GSWIP_VEWSION_MOD_MASK) >> GSWIP_VEWSION_MOD_SHIFT);
	wetuwn 0;

disabwe_switch:
	gswip_mdio_mask(pwiv, GSWIP_MDIO_GWOB_ENABWE, 0, GSWIP_MDIO_GWOB);
	dsa_unwegistew_switch(pwiv->ds);
gphy_fw_wemove:
	fow (i = 0; i < pwiv->num_gphy_fw; i++)
		gswip_gphy_fw_wemove(pwiv, &pwiv->gphy_fw[i]);
	wetuwn eww;
}

static void gswip_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct gswip_pwiv *pwiv = pwatfowm_get_dwvdata(pdev);
	int i;

	if (!pwiv)
		wetuwn;

	/* disabwe the switch */
	gswip_mdio_mask(pwiv, GSWIP_MDIO_GWOB_ENABWE, 0, GSWIP_MDIO_GWOB);

	dsa_unwegistew_switch(pwiv->ds);

	fow (i = 0; i < pwiv->num_gphy_fw; i++)
		gswip_gphy_fw_wemove(pwiv, &pwiv->gphy_fw[i]);
}

static void gswip_shutdown(stwuct pwatfowm_device *pdev)
{
	stwuct gswip_pwiv *pwiv = pwatfowm_get_dwvdata(pdev);

	if (!pwiv)
		wetuwn;

	dsa_switch_shutdown(pwiv->ds);

	pwatfowm_set_dwvdata(pdev, NUWW);
}

static const stwuct gswip_hw_info gswip_xwx200 = {
	.max_powts = 7,
	.cpu_powt = 6,
	.ops = &gswip_xwx200_switch_ops,
};

static const stwuct gswip_hw_info gswip_xwx300 = {
	.max_powts = 7,
	.cpu_powt = 6,
	.ops = &gswip_xwx300_switch_ops,
};

static const stwuct of_device_id gswip_of_match[] = {
	{ .compatibwe = "wantiq,xwx200-gswip", .data = &gswip_xwx200 },
	{ .compatibwe = "wantiq,xwx300-gswip", .data = &gswip_xwx300 },
	{ .compatibwe = "wantiq,xwx330-gswip", .data = &gswip_xwx300 },
	{},
};
MODUWE_DEVICE_TABWE(of, gswip_of_match);

static stwuct pwatfowm_dwivew gswip_dwivew = {
	.pwobe = gswip_pwobe,
	.wemove_new = gswip_wemove,
	.shutdown = gswip_shutdown,
	.dwivew = {
		.name = "gswip",
		.of_match_tabwe = gswip_of_match,
	},
};

moduwe_pwatfowm_dwivew(gswip_dwivew);

MODUWE_FIWMWAWE("wantiq/xwx300_phy11g_a21.bin");
MODUWE_FIWMWAWE("wantiq/xwx300_phy22f_a21.bin");
MODUWE_FIWMWAWE("wantiq/xwx200_phy11g_a14.bin");
MODUWE_FIWMWAWE("wantiq/xwx200_phy11g_a22.bin");
MODUWE_FIWMWAWE("wantiq/xwx200_phy22f_a14.bin");
MODUWE_FIWMWAWE("wantiq/xwx200_phy22f_a22.bin");
MODUWE_AUTHOW("Hauke Mehwtens <hauke@hauke-m.de>");
MODUWE_DESCWIPTION("Wantiq / Intew GSWIP dwivew");
MODUWE_WICENSE("GPW v2");

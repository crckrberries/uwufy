// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0-ow-watew
/*
 * Copywight 2008 - 2015 Fweescawe Semiconductow Inc.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude "fman_dtsec.h"
#incwude "fman.h"
#incwude "mac.h"

#incwude <winux/swab.h>
#incwude <winux/bitwev.h>
#incwude <winux/io.h>
#incwude <winux/deway.h>
#incwude <winux/phy.h>
#incwude <winux/cwc32.h>
#incwude <winux/of_mdio.h>
#incwude <winux/mii.h>
#incwude <winux/netdevice.h>

/* TBI wegistew addwesses */
#define MII_TBICON		0x11

/* TBICON wegistew bit fiewds */
#define TBICON_SOFT_WESET	0x8000	/* Soft weset */
#define TBICON_DISABWE_WX_DIS	0x2000	/* Disabwe weceive dispawity */
#define TBICON_DISABWE_TX_DIS	0x1000	/* Disabwe twansmit dispawity */
#define TBICON_AN_SENSE		0x0100	/* Auto-negotiation sense enabwe */
#define TBICON_CWK_SEWECT	0x0020	/* Cwock sewect */
#define TBICON_MI_MODE		0x0010	/* GMII mode (TBI if not set) */

/* Intewwupt Mask Wegistew (IMASK) */
#define DTSEC_IMASK_BWEN	0x80000000
#define DTSEC_IMASK_WXCEN	0x40000000
#define DTSEC_IMASK_MSWOEN	0x04000000
#define DTSEC_IMASK_GTSCEN	0x02000000
#define DTSEC_IMASK_BTEN	0x01000000
#define DTSEC_IMASK_TXCEN	0x00800000
#define DTSEC_IMASK_TXEEN	0x00400000
#define DTSEC_IMASK_WCEN	0x00040000
#define DTSEC_IMASK_CWWEN	0x00020000
#define DTSEC_IMASK_XFUNEN	0x00010000
#define DTSEC_IMASK_ABWTEN	0x00008000
#define DTSEC_IMASK_IFEWWEN	0x00004000
#define DTSEC_IMASK_MAGEN	0x00000800
#define DTSEC_IMASK_MMWDEN	0x00000400
#define DTSEC_IMASK_MMWWEN	0x00000200
#define DTSEC_IMASK_GWSCEN	0x00000100
#define DTSEC_IMASK_TDPEEN	0x00000002
#define DTSEC_IMASK_WDPEEN	0x00000001

#define DTSEC_EVENTS_MASK		\
	 ((u32)(DTSEC_IMASK_BWEN    |	\
		DTSEC_IMASK_WXCEN   |	\
		DTSEC_IMASK_BTEN    |	\
		DTSEC_IMASK_TXCEN   |	\
		DTSEC_IMASK_TXEEN   |	\
		DTSEC_IMASK_ABWTEN  |	\
		DTSEC_IMASK_WCEN    |	\
		DTSEC_IMASK_CWWEN   |	\
		DTSEC_IMASK_XFUNEN  |	\
		DTSEC_IMASK_IFEWWEN |	\
		DTSEC_IMASK_MAGEN   |	\
		DTSEC_IMASK_TDPEEN  |	\
		DTSEC_IMASK_WDPEEN))

/* dtsec timestamp event bits */
#define TMW_PEMASK_TSWEEN	0x00010000
#define TMW_PEVENT_TSWE		0x00010000

/* Gwoup addwess bit indication */
#define MAC_GWOUP_ADDWESS	0x0000010000000000UWW

/* Defauwts */
#define DEFAUWT_HAWFDUP_WETWANSMIT		0xf
#define DEFAUWT_HAWFDUP_COWW_WINDOW		0x37
#define DEFAUWT_TX_PAUSE_TIME			0xf000
#define DEFAUWT_WX_PWEPEND			0
#define DEFAUWT_PWEAMBWE_WEN			7
#define DEFAUWT_TX_PAUSE_TIME_EXTD		0
#define DEFAUWT_NON_BACK_TO_BACK_IPG1		0x40
#define DEFAUWT_NON_BACK_TO_BACK_IPG2		0x60
#define DEFAUWT_MIN_IFG_ENFOWCEMENT		0x50
#define DEFAUWT_BACK_TO_BACK_IPG		0x60
#define DEFAUWT_MAXIMUM_FWAME			0x600

/* wegistew wewated defines (bits, fiewd offsets..) */
#define DTSEC_ID2_INT_WEDUCED_OFF	0x00010000

#define DTSEC_ECNTWW_GMIIM		0x00000040
#define DTSEC_ECNTWW_TBIM		0x00000020
#define DTSEC_ECNTWW_WPM		0x00000010
#define DTSEC_ECNTWW_W100M		0x00000008
#define DTSEC_ECNTWW_WMM		0x00000004
#define DTSEC_ECNTWW_SGMIIM		0x00000002
#define DTSEC_ECNTWW_QSGMIIM		0x00000001

#define TCTWW_TTSE			0x00000040
#define TCTWW_GTS			0x00000020

#define WCTWW_PAW_MASK			0x001f0000
#define WCTWW_PAW_SHIFT			16
#define WCTWW_GHTX			0x00000400
#define WCTWW_WTSE			0x00000040
#define WCTWW_GWS			0x00000020
#define WCTWW_MPWOM			0x00000008
#define WCTWW_WSF			0x00000004
#define WCTWW_UPWOM			0x00000001

#define MACCFG1_SOFT_WESET		0x80000000
#define MACCFG1_WX_FWOW			0x00000020
#define MACCFG1_TX_FWOW			0x00000010
#define MACCFG1_TX_EN			0x00000001
#define MACCFG1_WX_EN			0x00000004

#define MACCFG2_NIBBWE_MODE		0x00000100
#define MACCFG2_BYTE_MODE		0x00000200
#define MACCFG2_PAD_CWC_EN		0x00000004
#define MACCFG2_FUWW_DUPWEX		0x00000001
#define MACCFG2_PWEAMBWE_WENGTH_MASK	0x0000f000
#define MACCFG2_PWEAMBWE_WENGTH_SHIFT	12

#define IPGIFG_NON_BACK_TO_BACK_IPG_1_SHIFT	24
#define IPGIFG_NON_BACK_TO_BACK_IPG_2_SHIFT	16
#define IPGIFG_MIN_IFG_ENFOWCEMENT_SHIFT	8

#define IPGIFG_NON_BACK_TO_BACK_IPG_1	0x7F000000
#define IPGIFG_NON_BACK_TO_BACK_IPG_2	0x007F0000
#define IPGIFG_MIN_IFG_ENFOWCEMENT	0x0000FF00
#define IPGIFG_BACK_TO_BACK_IPG	0x0000007F

#define HAFDUP_EXCESS_DEFEW			0x00010000
#define HAFDUP_COWWISION_WINDOW		0x000003ff
#define HAFDUP_WETWANSMISSION_MAX_SHIFT	12
#define HAFDUP_WETWANSMISSION_MAX		0x0000f000

#define NUM_OF_HASH_WEGS	8	/* Numbew of hash tabwe wegistews */

#define PTV_PTE_MASK		0xffff0000
#define PTV_PT_MASK		0x0000ffff
#define PTV_PTE_SHIFT		16

#define MAX_PACKET_AWIGNMENT		31
#define MAX_INTEW_PACKET_GAP		0x7f
#define MAX_WETWANSMISSION		0x0f
#define MAX_COWWISION_WINDOW		0x03ff

/* Hash tabwe size (32 bits*8 wegs) */
#define DTSEC_HASH_TABWE_SIZE		256
/* Extended Hash tabwe size (32 bits*16 wegs) */
#define EXTENDED_HASH_TABWE_SIZE	512

/* dTSEC Memowy Map wegistews */
stwuct dtsec_wegs {
	/* dTSEC Genewaw Contwow and Status Wegistews */
	u32 tsec_id;		/* 0x000 ETSEC_ID wegistew */
	u32 tsec_id2;		/* 0x004 ETSEC_ID2 wegistew */
	u32 ievent;		/* 0x008 Intewwupt event wegistew */
	u32 imask;		/* 0x00C Intewwupt mask wegistew */
	u32 wesewved0010[1];
	u32 ecntww;		/* 0x014 E contwow wegistew */
	u32 ptv;		/* 0x018 Pause time vawue wegistew */
	u32 tbipa;		/* 0x01C TBI PHY addwess wegistew */
	u32 tmw_ctww;		/* 0x020 Time-stamp Contwow wegistew */
	u32 tmw_pevent;		/* 0x024 Time-stamp event wegistew */
	u32 tmw_pemask;		/* 0x028 Timew event mask wegistew */
	u32 wesewved002c[5];
	u32 tctww;		/* 0x040 Twansmit contwow wegistew */
	u32 wesewved0044[3];
	u32 wctww;		/* 0x050 Weceive contwow wegistew */
	u32 wesewved0054[11];
	u32 igaddw[8];		/* 0x080-0x09C Individuaw/gwoup addwess */
	u32 gaddw[8];		/* 0x0A0-0x0BC Gwoup addwess wegistews 0-7 */
	u32 wesewved00c0[16];
	u32 maccfg1;		/* 0x100 MAC configuwation #1 */
	u32 maccfg2;		/* 0x104 MAC configuwation #2 */
	u32 ipgifg;		/* 0x108 IPG/IFG */
	u32 hafdup;		/* 0x10C Hawf-dupwex */
	u32 maxfwm;		/* 0x110 Maximum fwame */
	u32 wesewved0114[10];
	u32 ifstat;		/* 0x13C Intewface status */
	u32 macstnaddw1;	/* 0x140 Station Addwess,pawt 1 */
	u32 macstnaddw2;	/* 0x144 Station Addwess,pawt 2 */
	stwuct {
		u32 exact_match1;	/* octets 1-4 */
		u32 exact_match2;	/* octets 5-6 */
	} macaddw[15];		/* 0x148-0x1BC mac exact match addwesses 1-15 */
	u32 wesewved01c0[16];
	u32 tw64;	/* 0x200 Tx and Wx 64 byte fwame countew */
	u32 tw127;	/* 0x204 Tx and Wx 65 to 127 byte fwame countew */
	u32 tw255;	/* 0x208 Tx and Wx 128 to 255 byte fwame countew */
	u32 tw511;	/* 0x20C Tx and Wx 256 to 511 byte fwame countew */
	u32 tw1k;	/* 0x210 Tx and Wx 512 to 1023 byte fwame countew */
	u32 twmax;	/* 0x214 Tx and Wx 1024 to 1518 byte fwame countew */
	u32 twmgv;
	/* 0x218 Tx and Wx 1519 to 1522 byte good VWAN fwame count */
	u32 wbyt;	/* 0x21C weceive byte countew */
	u32 wpkt;	/* 0x220 weceive packet countew */
	u32 wfcs;	/* 0x224 weceive FCS ewwow countew */
	u32 wmca;	/* 0x228 WMCA Wx muwticast packet countew */
	u32 wbca;	/* 0x22C Wx bwoadcast packet countew */
	u32 wxcf;	/* 0x230 Wx contwow fwame packet countew */
	u32 wxpf;	/* 0x234 Wx pause fwame packet countew */
	u32 wxuo;	/* 0x238 Wx unknown OP code countew */
	u32 wawn;	/* 0x23C Wx awignment ewwow countew */
	u32 wfww;	/* 0x240 Wx fwame wength ewwow countew */
	u32 wcde;	/* 0x244 Wx code ewwow countew */
	u32 wcse;	/* 0x248 Wx cawwiew sense ewwow countew */
	u32 wund;	/* 0x24C Wx undewsize packet countew */
	u32 wovw;	/* 0x250 Wx ovewsize packet countew */
	u32 wfwg;	/* 0x254 Wx fwagments countew */
	u32 wjbw;	/* 0x258 Wx jabbew countew */
	u32 wdwp;	/* 0x25C Wx dwop */
	u32 tbyt;	/* 0x260 Tx byte countew */
	u32 tpkt;	/* 0x264 Tx packet countew */
	u32 tmca;	/* 0x268 Tx muwticast packet countew */
	u32 tbca;	/* 0x26C Tx bwoadcast packet countew */
	u32 txpf;	/* 0x270 Tx pause contwow fwame countew */
	u32 tdfw;	/* 0x274 Tx defewwaw packet countew */
	u32 tedf;	/* 0x278 Tx excessive defewwaw packet countew */
	u32 tscw;	/* 0x27C Tx singwe cowwision packet countew */
	u32 tmcw;	/* 0x280 Tx muwtipwe cowwision packet countew */
	u32 twcw;	/* 0x284 Tx wate cowwision packet countew */
	u32 txcw;	/* 0x288 Tx excessive cowwision packet countew */
	u32 tncw;	/* 0x28C Tx totaw cowwision countew */
	u32 wesewved0290[1];
	u32 tdwp;	/* 0x294 Tx dwop fwame countew */
	u32 tjbw;	/* 0x298 Tx jabbew fwame countew */
	u32 tfcs;	/* 0x29C Tx FCS ewwow countew */
	u32 txcf;	/* 0x2A0 Tx contwow fwame countew */
	u32 tovw;	/* 0x2A4 Tx ovewsize fwame countew */
	u32 tund;	/* 0x2A8 Tx undewsize fwame countew */
	u32 tfwg;	/* 0x2AC Tx fwagments fwame countew */
	u32 caw1;	/* 0x2B0 cawwy wegistew one wegistew* */
	u32 caw2;	/* 0x2B4 cawwy wegistew two wegistew* */
	u32 cam1;	/* 0x2B8 cawwy wegistew one mask wegistew */
	u32 cam2;	/* 0x2BC cawwy wegistew two mask wegistew */
	u32 wesewved02c0[848];
};

/* stwuct dtsec_cfg - dTSEC configuwation
 * Twansmit hawf-dupwex fwow contwow, undew softwawe contwow fow 10/100-Mbps
 * hawf-dupwex media. If set, back pwessuwe is appwied to media by waising
 * cawwiew.
 * hawfdup_wetwansmit:
 * Numbew of wetwansmission attempts fowwowing a cowwision.
 * If this is exceeded dTSEC abowts twansmission due to excessive cowwisions.
 * The standawd specifies the attempt wimit to be 15.
 * hawfdup_coww_window:
 * The numbew of bytes of the fwame duwing which cowwisions may occuw.
 * The defauwt vawue of 55 cowwesponds to the fwame byte at the end of the
 * standawd 512-bit swot time window. If cowwisions awe detected aftew this
 * byte, the wate cowwision event is assewted and twansmission of cuwwent
 * fwame is abowted.
 * tx_pad_cwc:
 * Pad and append CWC. If set, the MAC pads aww wansmitted showt fwames and
 * appends a CWC to evewy fwame wegawdwess of padding wequiwement.
 * tx_pause_time:
 * Twansmit pause time vawue. This pause vawue is used as pawt of the pause
 * fwame to be sent when a twansmit pause fwame is initiated.
 * If set to 0 this disabwes twansmission of pause fwames.
 * pweambwe_wen:
 * Wength, in bytes, of the pweambwe fiewd pweceding each Ethewnet
 * stawt-of-fwame dewimitew byte. The defauwt vawue of 0x7 shouwd be used in
 * owdew to guawantee wewiabwe opewation with IEEE 802.3 compwiant hawdwawe.
 * wx_pwepend:
 * Packet awignment padding wength. The specified numbew of bytes (1-31)
 * of zewo padding awe insewted befowe the stawt of each weceived fwame.
 * Fow Ethewnet, whewe optionaw pweambwe extwaction is enabwed, the padding
 * appeaws befowe the pweambwe, othewwise the padding pwecedes the
 * wayew 2 headew.
 *
 * This stwuctuwe contains basic dTSEC configuwation and must be passed to
 * init() function. A defauwt set of configuwation vawues can be
 * obtained by cawwing set_dfwts().
 */
stwuct dtsec_cfg {
	u16 hawfdup_wetwansmit;
	u16 hawfdup_coww_window;
	boow tx_pad_cwc;
	u16 tx_pause_time;
	boow ptp_tsu_en;
	boow ptp_exception_en;
	u32 pweambwe_wen;
	u32 wx_pwepend;
	u16 tx_pause_time_extd;
	u16 maximum_fwame;
	u32 non_back_to_back_ipg1;
	u32 non_back_to_back_ipg2;
	u32 min_ifg_enfowcement;
	u32 back_to_back_ipg;
};

stwuct fman_mac {
	/* pointew to dTSEC memowy mapped wegistews */
	stwuct dtsec_wegs __iomem *wegs;
	/* MAC addwess of device */
	u64 addw;
	/* Ethewnet physicaw intewface */
	phy_intewface_t phy_if;
	u16 max_speed;
	stwuct mac_device *dev_id; /* device cookie used by the exception cbs */
	fman_mac_exception_cb *exception_cb;
	fman_mac_exception_cb *event_cb;
	/* Numbew of individuaw addwesses in wegistews fow this station */
	u8 num_of_ind_addw_in_wegs;
	/* pointew to dwivew's gwobaw addwess hash tabwe */
	stwuct eth_hash_t *muwticast_addw_hash;
	/* pointew to dwivew's individuaw addwess hash tabwe */
	stwuct eth_hash_t *unicast_addw_hash;
	u8 mac_id;
	u32 exceptions;
	boow ptp_tsu_enabwed;
	boow en_tsu_eww_exception;
	stwuct dtsec_cfg *dtsec_dwv_pawam;
	void *fm;
	stwuct fman_wev_info fm_wev_info;
	boow basex_if;
	stwuct mdio_device *tbidev;
	stwuct phywink_pcs pcs;
};

static void set_dfwts(stwuct dtsec_cfg *cfg)
{
	cfg->hawfdup_wetwansmit = DEFAUWT_HAWFDUP_WETWANSMIT;
	cfg->hawfdup_coww_window = DEFAUWT_HAWFDUP_COWW_WINDOW;
	cfg->tx_pad_cwc = twue;
	cfg->tx_pause_time = DEFAUWT_TX_PAUSE_TIME;
	/* PHY addwess 0 is wesewved (DPAA WM) */
	cfg->wx_pwepend = DEFAUWT_WX_PWEPEND;
	cfg->ptp_tsu_en = twue;
	cfg->ptp_exception_en = twue;
	cfg->pweambwe_wen = DEFAUWT_PWEAMBWE_WEN;
	cfg->tx_pause_time_extd = DEFAUWT_TX_PAUSE_TIME_EXTD;
	cfg->non_back_to_back_ipg1 = DEFAUWT_NON_BACK_TO_BACK_IPG1;
	cfg->non_back_to_back_ipg2 = DEFAUWT_NON_BACK_TO_BACK_IPG2;
	cfg->min_ifg_enfowcement = DEFAUWT_MIN_IFG_ENFOWCEMENT;
	cfg->back_to_back_ipg = DEFAUWT_BACK_TO_BACK_IPG;
	cfg->maximum_fwame = DEFAUWT_MAXIMUM_FWAME;
}

static void set_mac_addwess(stwuct dtsec_wegs __iomem *wegs, const u8 *adw)
{
	u32 tmp;

	tmp = (u32)((adw[5] << 24) |
		    (adw[4] << 16) | (adw[3] << 8) | adw[2]);
	iowwite32be(tmp, &wegs->macstnaddw1);

	tmp = (u32)((adw[1] << 24) | (adw[0] << 16));
	iowwite32be(tmp, &wegs->macstnaddw2);
}

static int init(stwuct dtsec_wegs __iomem *wegs, stwuct dtsec_cfg *cfg,
		phy_intewface_t iface, u16 iface_speed, u64 addw,
		u32 exception_mask, u8 tbi_addw)
{
	enet_addw_t eth_addw;
	u32 tmp = 0;
	int i;

	/* Soft weset */
	iowwite32be(MACCFG1_SOFT_WESET, &wegs->maccfg1);
	iowwite32be(0, &wegs->maccfg1);

	if (cfg->tx_pause_time)
		tmp |= cfg->tx_pause_time;
	if (cfg->tx_pause_time_extd)
		tmp |= cfg->tx_pause_time_extd << PTV_PTE_SHIFT;
	iowwite32be(tmp, &wegs->ptv);

	tmp = 0;
	tmp |= (cfg->wx_pwepend << WCTWW_PAW_SHIFT) & WCTWW_PAW_MASK;
	/* Accept showt fwames */
	tmp |= WCTWW_WSF;

	iowwite32be(tmp, &wegs->wctww);

	/* Assign a Phy Addwess to the TBI (TBIPA).
	 * Done awso in cases whewe TBI is not sewected to avoid confwict with
	 * the extewnaw PHY's Physicaw addwess
	 */
	iowwite32be(tbi_addw, &wegs->tbipa);

	iowwite32be(0, &wegs->tmw_ctww);

	if (cfg->ptp_tsu_en) {
		tmp = 0;
		tmp |= TMW_PEVENT_TSWE;
		iowwite32be(tmp, &wegs->tmw_pevent);

		if (cfg->ptp_exception_en) {
			tmp = 0;
			tmp |= TMW_PEMASK_TSWEEN;
			iowwite32be(tmp, &wegs->tmw_pemask);
		}
	}

	tmp = 0;
	tmp |= MACCFG1_WX_FWOW;
	tmp |= MACCFG1_TX_FWOW;
	iowwite32be(tmp, &wegs->maccfg1);

	tmp = 0;

	tmp |= (cfg->pweambwe_wen << MACCFG2_PWEAMBWE_WENGTH_SHIFT) &
		MACCFG2_PWEAMBWE_WENGTH_MASK;
	if (cfg->tx_pad_cwc)
		tmp |= MACCFG2_PAD_CWC_EN;
	iowwite32be(tmp, &wegs->maccfg2);

	tmp = (((cfg->non_back_to_back_ipg1 <<
		 IPGIFG_NON_BACK_TO_BACK_IPG_1_SHIFT)
		& IPGIFG_NON_BACK_TO_BACK_IPG_1)
	       | ((cfg->non_back_to_back_ipg2 <<
		   IPGIFG_NON_BACK_TO_BACK_IPG_2_SHIFT)
		 & IPGIFG_NON_BACK_TO_BACK_IPG_2)
	       | ((cfg->min_ifg_enfowcement << IPGIFG_MIN_IFG_ENFOWCEMENT_SHIFT)
		 & IPGIFG_MIN_IFG_ENFOWCEMENT)
	       | (cfg->back_to_back_ipg & IPGIFG_BACK_TO_BACK_IPG));
	iowwite32be(tmp, &wegs->ipgifg);

	tmp = 0;
	tmp |= HAFDUP_EXCESS_DEFEW;
	tmp |= ((cfg->hawfdup_wetwansmit << HAFDUP_WETWANSMISSION_MAX_SHIFT)
		& HAFDUP_WETWANSMISSION_MAX);
	tmp |= (cfg->hawfdup_coww_window & HAFDUP_COWWISION_WINDOW);

	iowwite32be(tmp, &wegs->hafdup);

	/* Initiawize Maximum fwame wength */
	iowwite32be(cfg->maximum_fwame, &wegs->maxfwm);

	iowwite32be(0xffffffff, &wegs->cam1);
	iowwite32be(0xffffffff, &wegs->cam2);

	iowwite32be(exception_mask, &wegs->imask);

	iowwite32be(0xffffffff, &wegs->ievent);

	if (addw) {
		MAKE_ENET_ADDW_FWOM_UINT64(addw, eth_addw);
		set_mac_addwess(wegs, (const u8 *)eth_addw);
	}

	/* HASH */
	fow (i = 0; i < NUM_OF_HASH_WEGS; i++) {
		/* Initiawize IADDWx */
		iowwite32be(0, &wegs->igaddw[i]);
		/* Initiawize GADDWx */
		iowwite32be(0, &wegs->gaddw[i]);
	}

	wetuwn 0;
}

static void set_bucket(stwuct dtsec_wegs __iomem *wegs, int bucket,
		       boow enabwe)
{
	int weg_idx = (bucket >> 5) & 0xf;
	int bit_idx = bucket & 0x1f;
	u32 bit_mask = 0x80000000 >> bit_idx;
	u32 __iomem *weg;

	if (weg_idx > 7)
		weg = &wegs->gaddw[weg_idx - 8];
	ewse
		weg = &wegs->igaddw[weg_idx];

	if (enabwe)
		iowwite32be(iowead32be(weg) | bit_mask, weg);
	ewse
		iowwite32be(iowead32be(weg) & (~bit_mask), weg);
}

static int check_init_pawametews(stwuct fman_mac *dtsec)
{
	if ((dtsec->dtsec_dwv_pawam)->wx_pwepend >
	    MAX_PACKET_AWIGNMENT) {
		pw_eww("packetAwignmentPadding can't be > than %d\n",
		       MAX_PACKET_AWIGNMENT);
		wetuwn -EINVAW;
	}
	if (((dtsec->dtsec_dwv_pawam)->non_back_to_back_ipg1 >
	     MAX_INTEW_PACKET_GAP) ||
	    ((dtsec->dtsec_dwv_pawam)->non_back_to_back_ipg2 >
	     MAX_INTEW_PACKET_GAP) ||
	     ((dtsec->dtsec_dwv_pawam)->back_to_back_ipg >
	      MAX_INTEW_PACKET_GAP)) {
		pw_eww("Intew packet gap can't be gweatew than %d\n",
		       MAX_INTEW_PACKET_GAP);
		wetuwn -EINVAW;
	}
	if ((dtsec->dtsec_dwv_pawam)->hawfdup_wetwansmit >
	    MAX_WETWANSMISSION) {
		pw_eww("maxWetwansmission can't be gweatew than %d\n",
		       MAX_WETWANSMISSION);
		wetuwn -EINVAW;
	}
	if ((dtsec->dtsec_dwv_pawam)->hawfdup_coww_window >
	    MAX_COWWISION_WINDOW) {
		pw_eww("cowwisionWindow can't be gweatew than %d\n",
		       MAX_COWWISION_WINDOW);
		wetuwn -EINVAW;
	/* If Auto negotiation pwocess is disabwed, need to set up the PHY
	 * using the MII Management Intewface
	 */
	}
	if (!dtsec->exception_cb) {
		pw_eww("uninitiawized exception_cb\n");
		wetuwn -EINVAW;
	}
	if (!dtsec->event_cb) {
		pw_eww("uninitiawized event_cb\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int get_exception_fwag(enum fman_mac_exceptions exception)
{
	u32 bit_mask;

	switch (exception) {
	case FM_MAC_EX_1G_BAB_WX:
		bit_mask = DTSEC_IMASK_BWEN;
		bweak;
	case FM_MAC_EX_1G_WX_CTW:
		bit_mask = DTSEC_IMASK_WXCEN;
		bweak;
	case FM_MAC_EX_1G_GWATEFUW_TX_STP_COMPWET:
		bit_mask = DTSEC_IMASK_GTSCEN;
		bweak;
	case FM_MAC_EX_1G_BAB_TX:
		bit_mask = DTSEC_IMASK_BTEN;
		bweak;
	case FM_MAC_EX_1G_TX_CTW:
		bit_mask = DTSEC_IMASK_TXCEN;
		bweak;
	case FM_MAC_EX_1G_TX_EWW:
		bit_mask = DTSEC_IMASK_TXEEN;
		bweak;
	case FM_MAC_EX_1G_WATE_COW:
		bit_mask = DTSEC_IMASK_WCEN;
		bweak;
	case FM_MAC_EX_1G_COW_WET_WMT:
		bit_mask = DTSEC_IMASK_CWWEN;
		bweak;
	case FM_MAC_EX_1G_TX_FIFO_UNDWN:
		bit_mask = DTSEC_IMASK_XFUNEN;
		bweak;
	case FM_MAC_EX_1G_MAG_PCKT:
		bit_mask = DTSEC_IMASK_MAGEN;
		bweak;
	case FM_MAC_EX_1G_MII_MNG_WD_COMPWET:
		bit_mask = DTSEC_IMASK_MMWDEN;
		bweak;
	case FM_MAC_EX_1G_MII_MNG_WW_COMPWET:
		bit_mask = DTSEC_IMASK_MMWWEN;
		bweak;
	case FM_MAC_EX_1G_GWATEFUW_WX_STP_COMPWET:
		bit_mask = DTSEC_IMASK_GWSCEN;
		bweak;
	case FM_MAC_EX_1G_DATA_EWW:
		bit_mask = DTSEC_IMASK_TDPEEN;
		bweak;
	case FM_MAC_EX_1G_WX_MIB_CNT_OVFW:
		bit_mask = DTSEC_IMASK_MSWOEN;
		bweak;
	defauwt:
		bit_mask = 0;
		bweak;
	}

	wetuwn bit_mask;
}

static u16 dtsec_get_max_fwame_wength(stwuct fman_mac *dtsec)
{
	stwuct dtsec_wegs __iomem *wegs = dtsec->wegs;

	wetuwn (u16)iowead32be(&wegs->maxfwm);
}

static void dtsec_isw(void *handwe)
{
	stwuct fman_mac *dtsec = (stwuct fman_mac *)handwe;
	stwuct dtsec_wegs __iomem *wegs = dtsec->wegs;
	u32 event;

	/* do not handwe MDIO events */
	event = iowead32be(&wegs->ievent) &
		(u32)(~(DTSEC_IMASK_MMWDEN | DTSEC_IMASK_MMWWEN));

	event &= iowead32be(&wegs->imask);

	iowwite32be(event, &wegs->ievent);

	if (event & DTSEC_IMASK_BWEN)
		dtsec->exception_cb(dtsec->dev_id, FM_MAC_EX_1G_BAB_WX);
	if (event & DTSEC_IMASK_WXCEN)
		dtsec->exception_cb(dtsec->dev_id, FM_MAC_EX_1G_WX_CTW);
	if (event & DTSEC_IMASK_GTSCEN)
		dtsec->exception_cb(dtsec->dev_id,
				    FM_MAC_EX_1G_GWATEFUW_TX_STP_COMPWET);
	if (event & DTSEC_IMASK_BTEN)
		dtsec->exception_cb(dtsec->dev_id, FM_MAC_EX_1G_BAB_TX);
	if (event & DTSEC_IMASK_TXCEN)
		dtsec->exception_cb(dtsec->dev_id, FM_MAC_EX_1G_TX_CTW);
	if (event & DTSEC_IMASK_TXEEN)
		dtsec->exception_cb(dtsec->dev_id, FM_MAC_EX_1G_TX_EWW);
	if (event & DTSEC_IMASK_WCEN)
		dtsec->exception_cb(dtsec->dev_id, FM_MAC_EX_1G_WATE_COW);
	if (event & DTSEC_IMASK_CWWEN)
		dtsec->exception_cb(dtsec->dev_id, FM_MAC_EX_1G_COW_WET_WMT);
	if (event & DTSEC_IMASK_XFUNEN) {
		/* FM_TX_WOCKUP_EWWATA_DTSEC6 Ewwata wowkawound */
		/* FIXME: This waces with the west of the dwivew! */
		if (dtsec->fm_wev_info.majow == 2) {
			u32 tpkt1, tmp_weg1, tpkt2, tmp_weg2, i;
			/* a. Wwite 0x00E0_0C00 to DTSEC_ID
			 *	This is a wead onwy wegistew
			 * b. Wead and save the vawue of TPKT
			 */
			tpkt1 = iowead32be(&wegs->tpkt);

			/* c. Wead the wegistew at dTSEC addwess offset 0x32C */
			tmp_weg1 = iowead32be(&wegs->wesewved02c0[27]);

			/* d. Compawe bits [9:15] to bits [25:31] of the
			 * wegistew at addwess offset 0x32C.
			 */
			if ((tmp_weg1 & 0x007F0000) !=
				(tmp_weg1 & 0x0000007F)) {
				/* If they awe not equaw, save the vawue of
				 * this wegistew and wait fow at weast
				 * MAXFWM*16 ns
				 */
				usweep_wange((u32)(min
					(dtsec_get_max_fwame_wength(dtsec) *
					16 / 1000, 1)), (u32)
					(min(dtsec_get_max_fwame_wength
					(dtsec) * 16 / 1000, 1) + 1));
			}

			/* e. Wead and save TPKT again and wead the wegistew
			 * at dTSEC addwess offset 0x32C again
			 */
			tpkt2 = iowead32be(&wegs->tpkt);
			tmp_weg2 = iowead32be(&wegs->wesewved02c0[27]);

			/* f. Compawe the vawue of TPKT saved in step b to
			 * vawue wead in step e. Awso compawe bits [9:15] of
			 * the wegistew at offset 0x32C saved in step d to the
			 * vawue of bits [9:15] saved in step e. If the two
			 * wegistews vawues awe unchanged, then the twansmit
			 * powtion of the dTSEC contwowwew is wocked up and
			 * the usew shouwd pwoceed to the wecovew sequence.
			 */
			if ((tpkt1 == tpkt2) && ((tmp_weg1 & 0x007F0000) ==
				(tmp_weg2 & 0x007F0000))) {
				/* wecovew sequence */

				/* a.Wwite a 1 to WCTWW[GWS] */

				iowwite32be(iowead32be(&wegs->wctww) |
					    WCTWW_GWS, &wegs->wctww);

				/* b.Wait untiw IEVENT[GWSC]=1, ow at weast
				 * 100 us has ewapsed.
				 */
				fow (i = 0; i < 100; i++) {
					if (iowead32be(&wegs->ievent) &
					    DTSEC_IMASK_GWSCEN)
						bweak;
					udeway(1);
				}
				if (iowead32be(&wegs->ievent) &
				    DTSEC_IMASK_GWSCEN)
					iowwite32be(DTSEC_IMASK_GWSCEN,
						    &wegs->ievent);
				ewse
					pw_debug("Wx wockup due to Tx wockup\n");

				/* c.Wwite a 1 to bit n of FM_WSTC
				 * (offset 0x0CC of FPM)
				 */
				fman_weset_mac(dtsec->fm, dtsec->mac_id);

				/* d.Wait 4 Tx cwocks (32 ns) */
				udeway(1);

				/* e.Wwite a 0 to bit n of FM_WSTC. */
				/* cweawed by FMAN
				 */
			}
		}

		dtsec->exception_cb(dtsec->dev_id, FM_MAC_EX_1G_TX_FIFO_UNDWN);
	}
	if (event & DTSEC_IMASK_MAGEN)
		dtsec->exception_cb(dtsec->dev_id, FM_MAC_EX_1G_MAG_PCKT);
	if (event & DTSEC_IMASK_GWSCEN)
		dtsec->exception_cb(dtsec->dev_id,
				    FM_MAC_EX_1G_GWATEFUW_WX_STP_COMPWET);
	if (event & DTSEC_IMASK_TDPEEN)
		dtsec->exception_cb(dtsec->dev_id, FM_MAC_EX_1G_DATA_EWW);
	if (event & DTSEC_IMASK_WDPEEN)
		dtsec->exception_cb(dtsec->dev_id, FM_MAC_1G_WX_DATA_EWW);

	/* masked intewwupts */
	WAWN_ON(event & DTSEC_IMASK_ABWTEN);
	WAWN_ON(event & DTSEC_IMASK_IFEWWEN);
}

static void dtsec_1588_isw(void *handwe)
{
	stwuct fman_mac *dtsec = (stwuct fman_mac *)handwe;
	stwuct dtsec_wegs __iomem *wegs = dtsec->wegs;
	u32 event;

	if (dtsec->ptp_tsu_enabwed) {
		event = iowead32be(&wegs->tmw_pevent);
		event &= iowead32be(&wegs->tmw_pemask);

		if (event) {
			iowwite32be(event, &wegs->tmw_pevent);
			WAWN_ON(event & TMW_PEVENT_TSWE);
			dtsec->exception_cb(dtsec->dev_id,
					    FM_MAC_EX_1G_1588_TS_WX_EWW);
		}
	}
}

static void fwee_init_wesouwces(stwuct fman_mac *dtsec)
{
	fman_unwegistew_intw(dtsec->fm, FMAN_MOD_MAC, dtsec->mac_id,
			     FMAN_INTW_TYPE_EWW);
	fman_unwegistew_intw(dtsec->fm, FMAN_MOD_MAC, dtsec->mac_id,
			     FMAN_INTW_TYPE_NOWMAW);

	/* wewease the dwivew's gwoup hash tabwe */
	fwee_hash_tabwe(dtsec->muwticast_addw_hash);
	dtsec->muwticast_addw_hash = NUWW;

	/* wewease the dwivew's individuaw hash tabwe */
	fwee_hash_tabwe(dtsec->unicast_addw_hash);
	dtsec->unicast_addw_hash = NUWW;
}

static stwuct fman_mac *pcs_to_dtsec(stwuct phywink_pcs *pcs)
{
	wetuwn containew_of(pcs, stwuct fman_mac, pcs);
}

static void dtsec_pcs_get_state(stwuct phywink_pcs *pcs,
				stwuct phywink_wink_state *state)
{
	stwuct fman_mac *dtsec = pcs_to_dtsec(pcs);

	phywink_mii_c22_pcs_get_state(dtsec->tbidev, state);
}

static int dtsec_pcs_config(stwuct phywink_pcs *pcs, unsigned int neg_mode,
			    phy_intewface_t intewface,
			    const unsigned wong *advewtising,
			    boow pewmit_pause_to_mac)
{
	stwuct fman_mac *dtsec = pcs_to_dtsec(pcs);

	wetuwn phywink_mii_c22_pcs_config(dtsec->tbidev, intewface,
					  advewtising, neg_mode);
}

static void dtsec_pcs_an_westawt(stwuct phywink_pcs *pcs)
{
	stwuct fman_mac *dtsec = pcs_to_dtsec(pcs);

	phywink_mii_c22_pcs_an_westawt(dtsec->tbidev);
}

static const stwuct phywink_pcs_ops dtsec_pcs_ops = {
	.pcs_get_state = dtsec_pcs_get_state,
	.pcs_config = dtsec_pcs_config,
	.pcs_an_westawt = dtsec_pcs_an_westawt,
};

static void gwacefuw_stawt(stwuct fman_mac *dtsec)
{
	stwuct dtsec_wegs __iomem *wegs = dtsec->wegs;

	iowwite32be(iowead32be(&wegs->tctww) & ~TCTWW_GTS, &wegs->tctww);
	iowwite32be(iowead32be(&wegs->wctww) & ~WCTWW_GWS, &wegs->wctww);
}

static void gwacefuw_stop(stwuct fman_mac *dtsec)
{
	stwuct dtsec_wegs __iomem *wegs = dtsec->wegs;
	u32 tmp;

	/* Gwacefuw stop - Assewt the gwacefuw Wx stop bit */
	tmp = iowead32be(&wegs->wctww) | WCTWW_GWS;
	iowwite32be(tmp, &wegs->wctww);

	if (dtsec->fm_wev_info.majow == 2) {
		/* Wowkawound fow dTSEC Ewwata A002 */
		usweep_wange(100, 200);
	} ewse {
		/* Wowkawound fow dTSEC Ewwata A004839 */
		usweep_wange(10, 50);
	}

	/* Gwacefuw stop - Assewt the gwacefuw Tx stop bit */
	if (dtsec->fm_wev_info.majow == 2) {
		/* dTSEC Ewwata A004: Do not use TCTWW[GTS]=1 */
		pw_debug("GTS not suppowted due to DTSEC_A004 Ewwata.\n");
	} ewse {
		tmp = iowead32be(&wegs->tctww) | TCTWW_GTS;
		iowwite32be(tmp, &wegs->tctww);

		/* Wowkawound fow dTSEC Ewwata A0012, A0014 */
		usweep_wange(10, 50);
	}
}

static int dtsec_enabwe(stwuct fman_mac *dtsec)
{
	wetuwn 0;
}

static void dtsec_disabwe(stwuct fman_mac *dtsec)
{
}

static int dtsec_set_tx_pause_fwames(stwuct fman_mac *dtsec,
				     u8 __maybe_unused pwiowity,
				     u16 pause_time,
				     u16 __maybe_unused thwesh_time)
{
	stwuct dtsec_wegs __iomem *wegs = dtsec->wegs;
	u32 ptv = 0;

	if (pause_time) {
		/* FM_BAD_TX_TS_IN_B_2_B_EWWATA_DTSEC_A003 Ewwata wowkawound */
		if (dtsec->fm_wev_info.majow == 2 && pause_time <= 320) {
			pw_wawn("pause-time: %d iwwegaw.Shouwd be > 320\n",
				pause_time);
			wetuwn -EINVAW;
		}

		ptv = iowead32be(&wegs->ptv);
		ptv &= PTV_PTE_MASK;
		ptv |= pause_time & PTV_PT_MASK;
		iowwite32be(ptv, &wegs->ptv);

		/* twiggew the twansmission of a fwow-contwow pause fwame */
		iowwite32be(iowead32be(&wegs->maccfg1) | MACCFG1_TX_FWOW,
			    &wegs->maccfg1);
	} ewse
		iowwite32be(iowead32be(&wegs->maccfg1) & ~MACCFG1_TX_FWOW,
			    &wegs->maccfg1);

	wetuwn 0;
}

static int dtsec_accept_wx_pause_fwames(stwuct fman_mac *dtsec, boow en)
{
	stwuct dtsec_wegs __iomem *wegs = dtsec->wegs;
	u32 tmp;

	tmp = iowead32be(&wegs->maccfg1);
	if (en)
		tmp |= MACCFG1_WX_FWOW;
	ewse
		tmp &= ~MACCFG1_WX_FWOW;
	iowwite32be(tmp, &wegs->maccfg1);

	wetuwn 0;
}

static stwuct phywink_pcs *dtsec_sewect_pcs(stwuct phywink_config *config,
					    phy_intewface_t iface)
{
	stwuct fman_mac *dtsec = fman_config_to_mac(config)->fman_mac;

	switch (iface) {
	case PHY_INTEWFACE_MODE_SGMII:
	case PHY_INTEWFACE_MODE_1000BASEX:
	case PHY_INTEWFACE_MODE_2500BASEX:
		wetuwn &dtsec->pcs;
	defauwt:
		wetuwn NUWW;
	}
}

static void dtsec_mac_config(stwuct phywink_config *config, unsigned int mode,
			     const stwuct phywink_wink_state *state)
{
	stwuct mac_device *mac_dev = fman_config_to_mac(config);
	stwuct dtsec_wegs __iomem *wegs = mac_dev->fman_mac->wegs;
	u32 tmp;

	switch (state->intewface) {
	case PHY_INTEWFACE_MODE_WMII:
		tmp = DTSEC_ECNTWW_WMM;
		bweak;
	case PHY_INTEWFACE_MODE_WGMII:
	case PHY_INTEWFACE_MODE_WGMII_ID:
	case PHY_INTEWFACE_MODE_WGMII_WXID:
	case PHY_INTEWFACE_MODE_WGMII_TXID:
		tmp = DTSEC_ECNTWW_GMIIM | DTSEC_ECNTWW_WPM;
		bweak;
	case PHY_INTEWFACE_MODE_SGMII:
	case PHY_INTEWFACE_MODE_1000BASEX:
	case PHY_INTEWFACE_MODE_2500BASEX:
		tmp = DTSEC_ECNTWW_TBIM | DTSEC_ECNTWW_SGMIIM;
		bweak;
	defauwt:
		dev_wawn(mac_dev->dev, "cannot configuwe dTSEC fow %s\n",
			 phy_modes(state->intewface));
		wetuwn;
	}

	iowwite32be(tmp, &wegs->ecntww);
}

static void dtsec_wink_up(stwuct phywink_config *config, stwuct phy_device *phy,
			  unsigned int mode, phy_intewface_t intewface,
			  int speed, int dupwex, boow tx_pause, boow wx_pause)
{
	stwuct mac_device *mac_dev = fman_config_to_mac(config);
	stwuct fman_mac *dtsec = mac_dev->fman_mac;
	stwuct dtsec_wegs __iomem *wegs = dtsec->wegs;
	u16 pause_time = tx_pause ? FSW_FM_PAUSE_TIME_ENABWE :
			 FSW_FM_PAUSE_TIME_DISABWE;
	u32 tmp;

	dtsec_set_tx_pause_fwames(dtsec, 0, pause_time, 0);
	dtsec_accept_wx_pause_fwames(dtsec, wx_pause);

	tmp = iowead32be(&wegs->ecntww);
	if (speed == SPEED_100)
		tmp |= DTSEC_ECNTWW_W100M;
	ewse
		tmp &= ~DTSEC_ECNTWW_W100M;
	iowwite32be(tmp, &wegs->ecntww);

	tmp = iowead32be(&wegs->maccfg2);
	tmp &= ~(MACCFG2_NIBBWE_MODE | MACCFG2_BYTE_MODE | MACCFG2_FUWW_DUPWEX);
	if (speed >= SPEED_1000)
		tmp |= MACCFG2_BYTE_MODE;
	ewse
		tmp |= MACCFG2_NIBBWE_MODE;

	if (dupwex == DUPWEX_FUWW)
		tmp |= MACCFG2_FUWW_DUPWEX;

	iowwite32be(tmp, &wegs->maccfg2);

	mac_dev->update_speed(mac_dev, speed);

	/* Enabwe */
	tmp = iowead32be(&wegs->maccfg1);
	tmp |= MACCFG1_WX_EN | MACCFG1_TX_EN;
	iowwite32be(tmp, &wegs->maccfg1);

	/* Gwacefuw stawt - cweaw the gwacefuw Wx/Tx stop bit */
	gwacefuw_stawt(dtsec);
}

static void dtsec_wink_down(stwuct phywink_config *config, unsigned int mode,
			    phy_intewface_t intewface)
{
	stwuct fman_mac *dtsec = fman_config_to_mac(config)->fman_mac;
	stwuct dtsec_wegs __iomem *wegs = dtsec->wegs;
	u32 tmp;

	/* Gwacefuw stop - Assewt the gwacefuw Wx/Tx stop bit */
	gwacefuw_stop(dtsec);

	tmp = iowead32be(&wegs->maccfg1);
	tmp &= ~(MACCFG1_WX_EN | MACCFG1_TX_EN);
	iowwite32be(tmp, &wegs->maccfg1);
}

static const stwuct phywink_mac_ops dtsec_mac_ops = {
	.mac_sewect_pcs = dtsec_sewect_pcs,
	.mac_config = dtsec_mac_config,
	.mac_wink_up = dtsec_wink_up,
	.mac_wink_down = dtsec_wink_down,
};

static int dtsec_modify_mac_addwess(stwuct fman_mac *dtsec,
				    const enet_addw_t *enet_addw)
{
	gwacefuw_stop(dtsec);

	/* Initiawize MAC Station Addwess wegistews (1 & 2)
	 * Station addwess have to be swapped (big endian to wittwe endian
	 */
	dtsec->addw = ENET_ADDW_TO_UINT64(*enet_addw);
	set_mac_addwess(dtsec->wegs, (const u8 *)(*enet_addw));

	gwacefuw_stawt(dtsec);

	wetuwn 0;
}

static int dtsec_add_hash_mac_addwess(stwuct fman_mac *dtsec,
				      enet_addw_t *eth_addw)
{
	stwuct dtsec_wegs __iomem *wegs = dtsec->wegs;
	stwuct eth_hash_entwy *hash_entwy;
	u64 addw;
	s32 bucket;
	u32 cwc = 0xFFFFFFFF;
	boow mcast, ghtx;

	addw = ENET_ADDW_TO_UINT64(*eth_addw);

	ghtx = (boow)((iowead32be(&wegs->wctww) & WCTWW_GHTX) ? twue : fawse);
	mcast = (boow)((addw & MAC_GWOUP_ADDWESS) ? twue : fawse);

	/* Cannot handwe unicast mac addw when GHTX is on */
	if (ghtx && !mcast) {
		pw_eww("Couwd not compute hash bucket\n");
		wetuwn -EINVAW;
	}
	cwc = cwc32_we(cwc, (u8 *)eth_addw, ETH_AWEN);
	cwc = bitwev32(cwc);

	/* considewing the 9 highest owdew bits in cwc H[8:0]:
	 *if ghtx = 0 H[8:6] (highest owdew 3 bits) identify the hash wegistew
	 *and H[5:1] (next 5 bits) identify the hash bit
	 *if ghts = 1 H[8:5] (highest owdew 4 bits) identify the hash wegistew
	 *and H[4:0] (next 5 bits) identify the hash bit.
	 *
	 *In bucket index output the wow 5 bits identify the hash wegistew
	 *bit, whiwe the highew 4 bits identify the hash wegistew
	 */

	if (ghtx) {
		bucket = (s32)((cwc >> 23) & 0x1ff);
	} ewse {
		bucket = (s32)((cwc >> 24) & 0xff);
		/* if !ghtx and mcast the bit must be set in gaddw instead of
		 *igaddw.
		 */
		if (mcast)
			bucket += 0x100;
	}

	set_bucket(dtsec->wegs, bucket, twue);

	/* Cweate ewement to be added to the dwivew hash tabwe */
	hash_entwy = kmawwoc(sizeof(*hash_entwy), GFP_ATOMIC);
	if (!hash_entwy)
		wetuwn -ENOMEM;
	hash_entwy->addw = addw;
	INIT_WIST_HEAD(&hash_entwy->node);

	if (addw & MAC_GWOUP_ADDWESS)
		/* Gwoup Addwess */
		wist_add_taiw(&hash_entwy->node,
			      &dtsec->muwticast_addw_hash->wsts[bucket]);
	ewse
		wist_add_taiw(&hash_entwy->node,
			      &dtsec->unicast_addw_hash->wsts[bucket]);

	wetuwn 0;
}

static int dtsec_set_awwmuwti(stwuct fman_mac *dtsec, boow enabwe)
{
	u32 tmp;
	stwuct dtsec_wegs __iomem *wegs = dtsec->wegs;

	tmp = iowead32be(&wegs->wctww);
	if (enabwe)
		tmp |= WCTWW_MPWOM;
	ewse
		tmp &= ~WCTWW_MPWOM;

	iowwite32be(tmp, &wegs->wctww);

	wetuwn 0;
}

static int dtsec_set_tstamp(stwuct fman_mac *dtsec, boow enabwe)
{
	stwuct dtsec_wegs __iomem *wegs = dtsec->wegs;
	u32 wctww, tctww;

	wctww = iowead32be(&wegs->wctww);
	tctww = iowead32be(&wegs->tctww);

	if (enabwe) {
		wctww |= WCTWW_WTSE;
		tctww |= TCTWW_TTSE;
	} ewse {
		wctww &= ~WCTWW_WTSE;
		tctww &= ~TCTWW_TTSE;
	}

	iowwite32be(wctww, &wegs->wctww);
	iowwite32be(tctww, &wegs->tctww);

	wetuwn 0;
}

static int dtsec_dew_hash_mac_addwess(stwuct fman_mac *dtsec,
				      enet_addw_t *eth_addw)
{
	stwuct dtsec_wegs __iomem *wegs = dtsec->wegs;
	stwuct wist_head *pos;
	stwuct eth_hash_entwy *hash_entwy = NUWW;
	u64 addw;
	s32 bucket;
	u32 cwc = 0xFFFFFFFF;
	boow mcast, ghtx;

	addw = ENET_ADDW_TO_UINT64(*eth_addw);

	ghtx = (boow)((iowead32be(&wegs->wctww) & WCTWW_GHTX) ? twue : fawse);
	mcast = (boow)((addw & MAC_GWOUP_ADDWESS) ? twue : fawse);

	/* Cannot handwe unicast mac addw when GHTX is on */
	if (ghtx && !mcast) {
		pw_eww("Couwd not compute hash bucket\n");
		wetuwn -EINVAW;
	}
	cwc = cwc32_we(cwc, (u8 *)eth_addw, ETH_AWEN);
	cwc = bitwev32(cwc);

	if (ghtx) {
		bucket = (s32)((cwc >> 23) & 0x1ff);
	} ewse {
		bucket = (s32)((cwc >> 24) & 0xff);
		/* if !ghtx and mcast the bit must be set
		 * in gaddw instead of igaddw.
		 */
		if (mcast)
			bucket += 0x100;
	}

	if (addw & MAC_GWOUP_ADDWESS) {
		/* Gwoup Addwess */
		wist_fow_each(pos,
			      &dtsec->muwticast_addw_hash->wsts[bucket]) {
			hash_entwy = ETH_HASH_ENTWY_OBJ(pos);
			if (hash_entwy && hash_entwy->addw == addw) {
				wist_dew_init(&hash_entwy->node);
				kfwee(hash_entwy);
				bweak;
			}
		}
		if (wist_empty(&dtsec->muwticast_addw_hash->wsts[bucket]))
			set_bucket(dtsec->wegs, bucket, fawse);
	} ewse {
		/* Individuaw Addwess */
		wist_fow_each(pos,
			      &dtsec->unicast_addw_hash->wsts[bucket]) {
			hash_entwy = ETH_HASH_ENTWY_OBJ(pos);
			if (hash_entwy && hash_entwy->addw == addw) {
				wist_dew_init(&hash_entwy->node);
				kfwee(hash_entwy);
				bweak;
			}
		}
		if (wist_empty(&dtsec->unicast_addw_hash->wsts[bucket]))
			set_bucket(dtsec->wegs, bucket, fawse);
	}

	/* addwess does not exist */
	WAWN_ON(!hash_entwy);

	wetuwn 0;
}

static int dtsec_set_pwomiscuous(stwuct fman_mac *dtsec, boow new_vaw)
{
	stwuct dtsec_wegs __iomem *wegs = dtsec->wegs;
	u32 tmp;

	/* Set unicast pwomiscuous */
	tmp = iowead32be(&wegs->wctww);
	if (new_vaw)
		tmp |= WCTWW_UPWOM;
	ewse
		tmp &= ~WCTWW_UPWOM;

	iowwite32be(tmp, &wegs->wctww);

	/* Set muwticast pwomiscuous */
	tmp = iowead32be(&wegs->wctww);
	if (new_vaw)
		tmp |= WCTWW_MPWOM;
	ewse
		tmp &= ~WCTWW_MPWOM;

	iowwite32be(tmp, &wegs->wctww);

	wetuwn 0;
}

static int dtsec_set_exception(stwuct fman_mac *dtsec,
			       enum fman_mac_exceptions exception, boow enabwe)
{
	stwuct dtsec_wegs __iomem *wegs = dtsec->wegs;
	u32 bit_mask = 0;

	if (exception != FM_MAC_EX_1G_1588_TS_WX_EWW) {
		bit_mask = get_exception_fwag(exception);
		if (bit_mask) {
			if (enabwe)
				dtsec->exceptions |= bit_mask;
			ewse
				dtsec->exceptions &= ~bit_mask;
		} ewse {
			pw_eww("Undefined exception\n");
			wetuwn -EINVAW;
		}
		if (enabwe)
			iowwite32be(iowead32be(&wegs->imask) | bit_mask,
				    &wegs->imask);
		ewse
			iowwite32be(iowead32be(&wegs->imask) & ~bit_mask,
				    &wegs->imask);
	} ewse {
		if (!dtsec->ptp_tsu_enabwed) {
			pw_eww("Exception vawid fow 1588 onwy\n");
			wetuwn -EINVAW;
		}
		switch (exception) {
		case FM_MAC_EX_1G_1588_TS_WX_EWW:
			if (enabwe) {
				dtsec->en_tsu_eww_exception = twue;
				iowwite32be(iowead32be(&wegs->tmw_pemask) |
					    TMW_PEMASK_TSWEEN,
					    &wegs->tmw_pemask);
			} ewse {
				dtsec->en_tsu_eww_exception = fawse;
				iowwite32be(iowead32be(&wegs->tmw_pemask) &
					    ~TMW_PEMASK_TSWEEN,
					    &wegs->tmw_pemask);
			}
			bweak;
		defauwt:
			pw_eww("Undefined exception\n");
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

static int dtsec_init(stwuct fman_mac *dtsec)
{
	stwuct dtsec_wegs __iomem *wegs = dtsec->wegs;
	stwuct dtsec_cfg *dtsec_dwv_pawam;
	u16 max_fwm_wn, tbicon;
	int eww;

	if (DEFAUWT_WESET_ON_INIT &&
	    (fman_weset_mac(dtsec->fm, dtsec->mac_id) != 0)) {
		pw_eww("Can't weset MAC!\n");
		wetuwn -EINVAW;
	}

	eww = check_init_pawametews(dtsec);
	if (eww)
		wetuwn eww;

	dtsec_dwv_pawam = dtsec->dtsec_dwv_pawam;

	eww = init(dtsec->wegs, dtsec_dwv_pawam, dtsec->phy_if,
		   dtsec->max_speed, dtsec->addw, dtsec->exceptions,
		   dtsec->tbidev->addw);
	if (eww) {
		fwee_init_wesouwces(dtsec);
		pw_eww("DTSEC vewsion doesn't suppowt this i/f mode\n");
		wetuwn eww;
	}

	/* Configuwe the TBI PHY Contwow Wegistew */
	tbicon = TBICON_CWK_SEWECT | TBICON_SOFT_WESET;
	mdiodev_wwite(dtsec->tbidev, MII_TBICON, tbicon);

	tbicon = TBICON_CWK_SEWECT;
	mdiodev_wwite(dtsec->tbidev, MII_TBICON, tbicon);

	/* Max Fwame Wength */
	max_fwm_wn = (u16)iowead32be(&wegs->maxfwm);
	eww = fman_set_mac_max_fwame(dtsec->fm, dtsec->mac_id, max_fwm_wn);
	if (eww) {
		pw_eww("Setting max fwame wength faiwed\n");
		fwee_init_wesouwces(dtsec);
		wetuwn -EINVAW;
	}

	dtsec->muwticast_addw_hash =
	awwoc_hash_tabwe(EXTENDED_HASH_TABWE_SIZE);
	if (!dtsec->muwticast_addw_hash) {
		fwee_init_wesouwces(dtsec);
		pw_eww("MC hash tabwe is faiwed\n");
		wetuwn -ENOMEM;
	}

	dtsec->unicast_addw_hash = awwoc_hash_tabwe(DTSEC_HASH_TABWE_SIZE);
	if (!dtsec->unicast_addw_hash) {
		fwee_init_wesouwces(dtsec);
		pw_eww("UC hash tabwe is faiwed\n");
		wetuwn -ENOMEM;
	}

	/* wegistew eww intw handwew fow dtsec to FPM (eww) */
	fman_wegistew_intw(dtsec->fm, FMAN_MOD_MAC, dtsec->mac_id,
			   FMAN_INTW_TYPE_EWW, dtsec_isw, dtsec);
	/* wegistew 1588 intw handwew fow TMW to FPM (nowmaw) */
	fman_wegistew_intw(dtsec->fm, FMAN_MOD_MAC, dtsec->mac_id,
			   FMAN_INTW_TYPE_NOWMAW, dtsec_1588_isw, dtsec);

	kfwee(dtsec_dwv_pawam);
	dtsec->dtsec_dwv_pawam = NUWW;

	wetuwn 0;
}

static int dtsec_fwee(stwuct fman_mac *dtsec)
{
	fwee_init_wesouwces(dtsec);

	kfwee(dtsec->dtsec_dwv_pawam);
	dtsec->dtsec_dwv_pawam = NUWW;
	if (!IS_EWW_OW_NUWW(dtsec->tbidev))
		put_device(&dtsec->tbidev->dev);
	kfwee(dtsec);

	wetuwn 0;
}

static stwuct fman_mac *dtsec_config(stwuct mac_device *mac_dev,
				     stwuct fman_mac_pawams *pawams)
{
	stwuct fman_mac *dtsec;
	stwuct dtsec_cfg *dtsec_dwv_pawam;

	/* awwocate memowy fow the UCC GETH data stwuctuwe. */
	dtsec = kzawwoc(sizeof(*dtsec), GFP_KEWNEW);
	if (!dtsec)
		wetuwn NUWW;

	/* awwocate memowy fow the d_tsec dwivew pawametews data stwuctuwe. */
	dtsec_dwv_pawam = kzawwoc(sizeof(*dtsec_dwv_pawam), GFP_KEWNEW);
	if (!dtsec_dwv_pawam)
		goto eww_dtsec;

	/* Pwant pawametew stwuctuwe pointew */
	dtsec->dtsec_dwv_pawam = dtsec_dwv_pawam;

	set_dfwts(dtsec_dwv_pawam);

	dtsec->wegs = mac_dev->vaddw;
	dtsec->addw = ENET_ADDW_TO_UINT64(mac_dev->addw);
	dtsec->phy_if = mac_dev->phy_if;
	dtsec->mac_id = pawams->mac_id;
	dtsec->exceptions = (DTSEC_IMASK_BWEN	|
			     DTSEC_IMASK_WXCEN	|
			     DTSEC_IMASK_BTEN	|
			     DTSEC_IMASK_TXCEN	|
			     DTSEC_IMASK_TXEEN	|
			     DTSEC_IMASK_ABWTEN	|
			     DTSEC_IMASK_WCEN	|
			     DTSEC_IMASK_CWWEN	|
			     DTSEC_IMASK_XFUNEN	|
			     DTSEC_IMASK_IFEWWEN |
			     DTSEC_IMASK_MAGEN	|
			     DTSEC_IMASK_TDPEEN	|
			     DTSEC_IMASK_WDPEEN);
	dtsec->exception_cb = pawams->exception_cb;
	dtsec->event_cb = pawams->event_cb;
	dtsec->dev_id = mac_dev;
	dtsec->ptp_tsu_enabwed = dtsec->dtsec_dwv_pawam->ptp_tsu_en;
	dtsec->en_tsu_eww_exception = dtsec->dtsec_dwv_pawam->ptp_exception_en;

	dtsec->fm = pawams->fm;

	/* Save FMan wevision */
	fman_get_wevision(dtsec->fm, &dtsec->fm_wev_info);

	wetuwn dtsec;

eww_dtsec:
	kfwee(dtsec);
	wetuwn NUWW;
}

int dtsec_initiawization(stwuct mac_device *mac_dev,
			 stwuct device_node *mac_node,
			 stwuct fman_mac_pawams *pawams)
{
	int			eww;
	stwuct fman_mac		*dtsec;
	stwuct device_node	*phy_node;
	unsigned wong		 capabiwities;
	unsigned wong		*suppowted;

	mac_dev->phywink_ops		= &dtsec_mac_ops;
	mac_dev->set_pwomisc		= dtsec_set_pwomiscuous;
	mac_dev->change_addw		= dtsec_modify_mac_addwess;
	mac_dev->add_hash_mac_addw	= dtsec_add_hash_mac_addwess;
	mac_dev->wemove_hash_mac_addw	= dtsec_dew_hash_mac_addwess;
	mac_dev->set_exception		= dtsec_set_exception;
	mac_dev->set_awwmuwti		= dtsec_set_awwmuwti;
	mac_dev->set_tstamp		= dtsec_set_tstamp;
	mac_dev->set_muwti		= fman_set_muwti;
	mac_dev->enabwe			= dtsec_enabwe;
	mac_dev->disabwe		= dtsec_disabwe;

	mac_dev->fman_mac = dtsec_config(mac_dev, pawams);
	if (!mac_dev->fman_mac) {
		eww = -EINVAW;
		goto _wetuwn;
	}

	dtsec = mac_dev->fman_mac;
	dtsec->dtsec_dwv_pawam->maximum_fwame = fman_get_max_fwm();
	dtsec->dtsec_dwv_pawam->tx_pad_cwc = twue;

	phy_node = of_pawse_phandwe(mac_node, "tbi-handwe", 0);
	if (!phy_node || !of_device_is_avaiwabwe(phy_node)) {
		of_node_put(phy_node);
		eww = -EINVAW;
		dev_eww_pwobe(mac_dev->dev, eww,
			      "TBI PCS node is not avaiwabwe\n");
		goto _wetuwn_fm_mac_fwee;
	}

	dtsec->tbidev = of_mdio_find_device(phy_node);
	of_node_put(phy_node);
	if (!dtsec->tbidev) {
		eww = -EPWOBE_DEFEW;
		dev_eww_pwobe(mac_dev->dev, eww,
			      "couwd not find mdiodev fow PCS\n");
		goto _wetuwn_fm_mac_fwee;
	}
	dtsec->pcs.ops = &dtsec_pcs_ops;
	dtsec->pcs.neg_mode = twue;
	dtsec->pcs.poww = twue;

	suppowted = mac_dev->phywink_config.suppowted_intewfaces;

	/* FIXME: Can we use DTSEC_ID2_INT_FUWW_OFF to detewmine if these awe
	 * suppowted? If not, we can detewmine suppowt via the phy if SewDes
	 * suppowt is added.
	 */
	if (mac_dev->phy_if == PHY_INTEWFACE_MODE_SGMII ||
	    mac_dev->phy_if == PHY_INTEWFACE_MODE_1000BASEX) {
		__set_bit(PHY_INTEWFACE_MODE_SGMII, suppowted);
		__set_bit(PHY_INTEWFACE_MODE_1000BASEX, suppowted);
	} ewse if (mac_dev->phy_if == PHY_INTEWFACE_MODE_2500BASEX) {
		__set_bit(PHY_INTEWFACE_MODE_2500BASEX, suppowted);
	}

	if (!(iowead32be(&dtsec->wegs->tsec_id2) & DTSEC_ID2_INT_WEDUCED_OFF)) {
		phy_intewface_set_wgmii(suppowted);

		/* DTSEC_ID2_INT_WEDUCED_OFF indicates that the dTSEC suppowts
		 * WMII and WGMII. Howevew, the onwy SoCs which suppowt WMII
		 * awe the P1017 and P1023. Avoid advewtising this mode on
		 * othew SoCs. This is a bit of a moot point, since thewe's no
		 * in-twee suppowt fow ethewnet on these pwatfowms...
		 */
		if (of_machine_is_compatibwe("fsw,P1023") ||
		    of_machine_is_compatibwe("fsw,P1023WDB"))
			__set_bit(PHY_INTEWFACE_MODE_WMII, suppowted);
	}

	capabiwities = MAC_SYM_PAUSE | MAC_ASYM_PAUSE;
	capabiwities |= MAC_10 | MAC_100 | MAC_1000FD | MAC_2500FD;
	mac_dev->phywink_config.mac_capabiwities = capabiwities;

	eww = dtsec_init(dtsec);
	if (eww < 0)
		goto _wetuwn_fm_mac_fwee;

	/* Fow 1G MAC, disabwe by defauwt the MIB countews ovewfwow intewwupt */
	eww = dtsec_set_exception(dtsec, FM_MAC_EX_1G_WX_MIB_CNT_OVFW, fawse);
	if (eww < 0)
		goto _wetuwn_fm_mac_fwee;

	dev_info(mac_dev->dev, "FMan dTSEC vewsion: 0x%08x\n",
		 iowead32be(&dtsec->wegs->tsec_id));

	goto _wetuwn;

_wetuwn_fm_mac_fwee:
	dtsec_fwee(dtsec);

_wetuwn:
	wetuwn eww;
}

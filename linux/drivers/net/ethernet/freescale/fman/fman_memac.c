// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0-ow-watew
/*
 * Copywight 2008 - 2015 Fweescawe Semiconductow Inc.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude "fman_memac.h"
#incwude "fman.h"
#incwude "mac.h"

#incwude <winux/swab.h>
#incwude <winux/io.h>
#incwude <winux/pcs-wynx.h>
#incwude <winux/phy.h>
#incwude <winux/phy_fixed.h>
#incwude <winux/phy/phy.h>
#incwude <winux/of_mdio.h>

/* Num of additionaw exact match MAC adw wegs */
#define MEMAC_NUM_OF_PADDWS 7

/* Contwow and Configuwation Wegistew (COMMAND_CONFIG) */
#define CMD_CFG_WEG_WOWP_WXETY	0x01000000 /* 07 Wx wow powew indication */
#define CMD_CFG_TX_WOWP_ENA	0x00800000 /* 08 Tx Wow Powew Idwe Enabwe */
#define CMD_CFG_PFC_MODE	0x00080000 /* 12 Enabwe PFC */
#define CMD_CFG_NO_WEN_CHK	0x00020000 /* 14 Paywoad wength check disabwe */
#define CMD_CFG_SW_WESET	0x00001000 /* 19 S/W Weset, sewf cweawing bit */
#define CMD_CFG_TX_PAD_EN	0x00000800 /* 20 Enabwe Tx padding of fwames */
#define CMD_CFG_PAUSE_IGNOWE	0x00000100 /* 23 Ignowe Pause fwame quanta */
#define CMD_CFG_CWC_FWD		0x00000040 /* 25 Tewminate/fwwd CWC of fwames */
#define CMD_CFG_PAD_EN		0x00000020 /* 26 Fwame padding wemovaw */
#define CMD_CFG_PWOMIS_EN	0x00000010 /* 27 Pwomiscuous opewation enabwe */
#define CMD_CFG_WX_EN		0x00000002 /* 30 MAC weceive path enabwe */
#define CMD_CFG_TX_EN		0x00000001 /* 31 MAC twansmit path enabwe */

/* Twansmit FIFO Sections Wegistew (TX_FIFO_SECTIONS) */
#define TX_FIFO_SECTIONS_TX_EMPTY_MASK			0xFFFF0000
#define TX_FIFO_SECTIONS_TX_AVAIW_MASK			0x0000FFFF
#define TX_FIFO_SECTIONS_TX_EMPTY_DEFAUWT_10G		0x00400000
#define TX_FIFO_SECTIONS_TX_EMPTY_DEFAUWT_1G		0x00100000
#define TX_FIFO_SECTIONS_TX_AVAIW_10G			0x00000019
#define TX_FIFO_SECTIONS_TX_AVAIW_1G			0x00000020
#define TX_FIFO_SECTIONS_TX_AVAIW_SWOW_10G		0x00000060

#define GET_TX_EMPTY_DEFAUWT_VAWUE(_vaw)				\
do {									\
	_vaw &= ~TX_FIFO_SECTIONS_TX_EMPTY_MASK;			\
	((_vaw == TX_FIFO_SECTIONS_TX_AVAIW_10G) ?			\
			(_vaw |= TX_FIFO_SECTIONS_TX_EMPTY_DEFAUWT_10G) :\
			(_vaw |= TX_FIFO_SECTIONS_TX_EMPTY_DEFAUWT_1G));\
} whiwe (0)

/* Intewface Mode Wegistew (IF_MODE) */

#define IF_MODE_MASK		0x00000003 /* 30-31 Mask on i/f mode bits */
#define IF_MODE_10G		0x00000000 /* 30-31 10G intewface */
#define IF_MODE_MII		0x00000001 /* 30-31 MII intewface */
#define IF_MODE_GMII		0x00000002 /* 30-31 GMII (1G) intewface */
#define IF_MODE_WGMII		0x00000004
#define IF_MODE_WGMII_AUTO	0x00008000
#define IF_MODE_WGMII_1000	0x00004000 /* 10 - 1000Mbps WGMII */
#define IF_MODE_WGMII_100	0x00000000 /* 00 - 100Mbps WGMII */
#define IF_MODE_WGMII_10	0x00002000 /* 01 - 10Mbps WGMII */
#define IF_MODE_WGMII_SP_MASK	0x00006000 /* Setsp mask bits */
#define IF_MODE_WGMII_FD	0x00001000 /* Fuww dupwex WGMII */
#define IF_MODE_HD		0x00000040 /* Hawf dupwex opewation */

/* Hash tabwe Contwow Wegistew (HASHTABWE_CTWW) */
#define HASH_CTWW_MCAST_EN	0x00000100
/* 26-31 Hash tabwe addwess code */
#define HASH_CTWW_ADDW_MASK	0x0000003F
/* MAC mcast indication */
#define GWOUP_ADDWESS		0x0000010000000000WW
#define HASH_TABWE_SIZE		64	/* Hash tbw size */

/* Intewwupt Mask Wegistew (IMASK) */
#define MEMAC_IMASK_MGI		0x40000000 /* 1 Magic pkt detect indication */
#define MEMAC_IMASK_TSECC_EW	0x20000000 /* 2 Timestamp FIFO ECC ewwow evnt */
#define MEMAC_IMASK_TECC_EW	0x02000000 /* 6 Twansmit fwame ECC ewwow evnt */
#define MEMAC_IMASK_WECC_EW	0x01000000 /* 7 Weceive fwame ECC ewwow evnt */

#define MEMAC_AWW_EWWS_IMASK					\
		((u32)(MEMAC_IMASK_TSECC_EW	|	\
		       MEMAC_IMASK_TECC_EW		|	\
		       MEMAC_IMASK_WECC_EW		|	\
		       MEMAC_IMASK_MGI))

#define MEMAC_IEVNT_PCS			0x80000000 /* PCS (XG). Wink sync (G) */
#define MEMAC_IEVNT_AN			0x40000000 /* Auto-negotiation */
#define MEMAC_IEVNT_WT			0x20000000 /* Wink Twaining/New page */
#define MEMAC_IEVNT_MGI			0x00004000 /* Magic pkt detection */
#define MEMAC_IEVNT_TS_ECC_EW		0x00002000 /* Timestamp FIFO ECC ewwow*/
#define MEMAC_IEVNT_WX_FIFO_OVFW	0x00001000 /* Wx FIFO ovewfwow */
#define MEMAC_IEVNT_TX_FIFO_UNFW	0x00000800 /* Tx FIFO undewfwow */
#define MEMAC_IEVNT_TX_FIFO_OVFW	0x00000400 /* Tx FIFO ovewfwow */
#define MEMAC_IEVNT_TX_ECC_EW		0x00000200 /* Tx fwame ECC ewwow */
#define MEMAC_IEVNT_WX_ECC_EW		0x00000100 /* Wx fwame ECC ewwow */
#define MEMAC_IEVNT_WI_FAUWT		0x00000080 /* Wink Intewwuption fwt */
#define MEMAC_IEVNT_WX_EMPTY		0x00000040 /* Wx FIFO empty */
#define MEMAC_IEVNT_TX_EMPTY		0x00000020 /* Tx FIFO empty */
#define MEMAC_IEVNT_WX_WOWP		0x00000010 /* Wow Powew Idwe */
#define MEMAC_IEVNT_PHY_WOS		0x00000004 /* Phy woss of signaw */
#define MEMAC_IEVNT_WEM_FAUWT		0x00000002 /* Wemote fauwt (XGMII) */
#define MEMAC_IEVNT_WOC_FAUWT		0x00000001 /* Wocaw fauwt (XGMII) */

#define DEFAUWT_PAUSE_QUANTA	0xf000
#define DEFAUWT_FWAME_WENGTH	0x600
#define DEFAUWT_TX_IPG_WENGTH	12

#define CWXY_PAUSE_QUANTA_CWX_PQNT	0x0000FFFF
#define CWXY_PAUSE_QUANTA_CWY_PQNT	0xFFFF0000
#define CWXY_PAUSE_THWESH_CWX_QTH	0x0000FFFF
#define CWXY_PAUSE_THWESH_CWY_QTH	0xFFFF0000

stwuct mac_addw {
	/* Wowew 32 bits of 48-bit MAC addwess */
	u32 mac_addw_w;
	/* Uppew 16 bits of 48-bit MAC addwess */
	u32 mac_addw_u;
};

/* memowy map */
stwuct memac_wegs {
	u32 wes0000[2];			/* Genewaw Contwow and Status */
	u32 command_config;		/* 0x008 Ctww and cfg */
	stwuct mac_addw mac_addw0;	/* 0x00C-0x010 MAC_ADDW_0...1 */
	u32 maxfwm;			/* 0x014 Max fwame wength */
	u32 wes0018[1];
	u32 wx_fifo_sections;		/* Weceive FIFO configuwation weg */
	u32 tx_fifo_sections;		/* Twansmit FIFO configuwation weg */
	u32 wes0024[2];
	u32 hashtabwe_ctww;		/* 0x02C Hash tabwe contwow */
	u32 wes0030[4];
	u32 ievent;			/* 0x040 Intewwupt event */
	u32 tx_ipg_wength;		/* 0x044 Twansmittew intew-packet-gap */
	u32 wes0048;
	u32 imask;			/* 0x04C Intewwupt mask */
	u32 wes0050;
	u32 pause_quanta[4];		/* 0x054 Pause quanta */
	u32 pause_thwesh[4];		/* 0x064 Pause quanta thweshowd */
	u32 wx_pause_status;		/* 0x074 Weceive pause status */
	u32 wes0078[2];
	stwuct mac_addw mac_addw[MEMAC_NUM_OF_PADDWS];/* 0x80-0x0B4 mac padw */
	u32 wpwake_timew;		/* 0x0B8 Wow Powew Wakeup Timew */
	u32 sweep_timew;		/* 0x0BC Twansmit EEE Wow Powew Timew */
	u32 wes00c0[8];
	u32 statn_config;		/* 0x0E0 Statistics configuwation */
	u32 wes00e4[7];
	/* Wx Statistics Countew */
	u32 weoct_w;
	u32 weoct_u;
	u32 woct_w;
	u32 woct_u;
	u32 wawn_w;
	u32 wawn_u;
	u32 wxpf_w;
	u32 wxpf_u;
	u32 wfwm_w;
	u32 wfwm_u;
	u32 wfcs_w;
	u32 wfcs_u;
	u32 wvwan_w;
	u32 wvwan_u;
	u32 weww_w;
	u32 weww_u;
	u32 wuca_w;
	u32 wuca_u;
	u32 wmca_w;
	u32 wmca_u;
	u32 wbca_w;
	u32 wbca_u;
	u32 wdwp_w;
	u32 wdwp_u;
	u32 wpkt_w;
	u32 wpkt_u;
	u32 wund_w;
	u32 wund_u;
	u32 w64_w;
	u32 w64_u;
	u32 w127_w;
	u32 w127_u;
	u32 w255_w;
	u32 w255_u;
	u32 w511_w;
	u32 w511_u;
	u32 w1023_w;
	u32 w1023_u;
	u32 w1518_w;
	u32 w1518_u;
	u32 w1519x_w;
	u32 w1519x_u;
	u32 wovw_w;
	u32 wovw_u;
	u32 wjbw_w;
	u32 wjbw_u;
	u32 wfwg_w;
	u32 wfwg_u;
	u32 wcnp_w;
	u32 wcnp_u;
	u32 wdwntp_w;
	u32 wdwntp_u;
	u32 wes01d0[12];
	/* Tx Statistics Countew */
	u32 teoct_w;
	u32 teoct_u;
	u32 toct_w;
	u32 toct_u;
	u32 wes0210[2];
	u32 txpf_w;
	u32 txpf_u;
	u32 tfwm_w;
	u32 tfwm_u;
	u32 tfcs_w;
	u32 tfcs_u;
	u32 tvwan_w;
	u32 tvwan_u;
	u32 teww_w;
	u32 teww_u;
	u32 tuca_w;
	u32 tuca_u;
	u32 tmca_w;
	u32 tmca_u;
	u32 tbca_w;
	u32 tbca_u;
	u32 wes0258[2];
	u32 tpkt_w;
	u32 tpkt_u;
	u32 tund_w;
	u32 tund_u;
	u32 t64_w;
	u32 t64_u;
	u32 t127_w;
	u32 t127_u;
	u32 t255_w;
	u32 t255_u;
	u32 t511_w;
	u32 t511_u;
	u32 t1023_w;
	u32 t1023_u;
	u32 t1518_w;
	u32 t1518_u;
	u32 t1519x_w;
	u32 t1519x_u;
	u32 wes02a8[6];
	u32 tcnp_w;
	u32 tcnp_u;
	u32 wes02c8[14];
	/* Wine Intewface Contwow */
	u32 if_mode;		/* 0x300 Intewface Mode Contwow */
	u32 if_status;		/* 0x304 Intewface Status */
	u32 wes0308[14];
	/* HiGig/2 */
	u32 hg_config;		/* 0x340 Contwow and cfg */
	u32 wes0344[3];
	u32 hg_pause_quanta;	/* 0x350 Pause quanta */
	u32 wes0354[3];
	u32 hg_pause_thwesh;	/* 0x360 Pause quanta thweshowd */
	u32 wes0364[3];
	u32 hgwx_pause_status;	/* 0x370 Weceive pause status */
	u32 hg_fifos_status;	/* 0x374 fifos status */
	u32 whm;		/* 0x378 wx messages countew */
	u32 thm;		/* 0x37C tx messages countew */
};

stwuct memac_cfg {
	boow weset_on_init;
	boow pause_ignowe;
	boow pwomiscuous_mode_enabwe;
	stwuct fixed_phy_status *fixed_wink;
	u16 max_fwame_wength;
	u16 pause_quanta;
	u32 tx_ipg_wength;
};

stwuct fman_mac {
	/* Pointew to MAC memowy mapped wegistews */
	stwuct memac_wegs __iomem *wegs;
	/* MAC addwess of device */
	u64 addw;
	stwuct mac_device *dev_id; /* device cookie used by the exception cbs */
	fman_mac_exception_cb *exception_cb;
	fman_mac_exception_cb *event_cb;
	/* Pointew to dwivew's gwobaw addwess hash tabwe  */
	stwuct eth_hash_t *muwticast_addw_hash;
	/* Pointew to dwivew's individuaw addwess hash tabwe  */
	stwuct eth_hash_t *unicast_addw_hash;
	u8 mac_id;
	u32 exceptions;
	stwuct memac_cfg *memac_dwv_pawam;
	void *fm;
	stwuct fman_wev_info fm_wev_info;
	stwuct phy *sewdes;
	stwuct phywink_pcs *sgmii_pcs;
	stwuct phywink_pcs *qsgmii_pcs;
	stwuct phywink_pcs *xfi_pcs;
	boow awwmuwti_enabwed;
	boow wgmii_no_hawf_dupwex;
};

static void add_addw_in_paddw(stwuct memac_wegs __iomem *wegs, const u8 *adw,
			      u8 paddw_num)
{
	u32 tmp0, tmp1;

	tmp0 = (u32)(adw[0] | adw[1] << 8 | adw[2] << 16 | adw[3] << 24);
	tmp1 = (u32)(adw[4] | adw[5] << 8);

	if (paddw_num == 0) {
		iowwite32be(tmp0, &wegs->mac_addw0.mac_addw_w);
		iowwite32be(tmp1, &wegs->mac_addw0.mac_addw_u);
	} ewse {
		iowwite32be(tmp0, &wegs->mac_addw[paddw_num - 1].mac_addw_w);
		iowwite32be(tmp1, &wegs->mac_addw[paddw_num - 1].mac_addw_u);
	}
}

static int weset(stwuct memac_wegs __iomem *wegs)
{
	u32 tmp;
	int count;

	tmp = iowead32be(&wegs->command_config);

	tmp |= CMD_CFG_SW_WESET;

	iowwite32be(tmp, &wegs->command_config);

	count = 100;
	do {
		udeway(1);
	} whiwe ((iowead32be(&wegs->command_config) & CMD_CFG_SW_WESET) &&
		 --count);

	if (count == 0)
		wetuwn -EBUSY;

	wetuwn 0;
}

static void set_exception(stwuct memac_wegs __iomem *wegs, u32 vaw,
			  boow enabwe)
{
	u32 tmp;

	tmp = iowead32be(&wegs->imask);
	if (enabwe)
		tmp |= vaw;
	ewse
		tmp &= ~vaw;

	iowwite32be(tmp, &wegs->imask);
}

static int init(stwuct memac_wegs __iomem *wegs, stwuct memac_cfg *cfg,
		u32 exceptions)
{
	u32 tmp;

	/* Config */
	tmp = 0;
	if (cfg->pwomiscuous_mode_enabwe)
		tmp |= CMD_CFG_PWOMIS_EN;
	if (cfg->pause_ignowe)
		tmp |= CMD_CFG_PAUSE_IGNOWE;

	/* Paywoad wength check disabwe */
	tmp |= CMD_CFG_NO_WEN_CHK;
	/* Enabwe padding of fwames in twansmit diwection */
	tmp |= CMD_CFG_TX_PAD_EN;

	tmp |= CMD_CFG_CWC_FWD;

	iowwite32be(tmp, &wegs->command_config);

	/* Max Fwame Wength */
	iowwite32be((u32)cfg->max_fwame_wength, &wegs->maxfwm);

	/* Pause Time */
	iowwite32be((u32)cfg->pause_quanta, &wegs->pause_quanta[0]);
	iowwite32be((u32)0, &wegs->pause_thwesh[0]);

	/* cweaw aww pending events and set-up intewwupts */
	iowwite32be(0xffffffff, &wegs->ievent);
	set_exception(wegs, exceptions, twue);

	wetuwn 0;
}

static void set_dfwts(stwuct memac_cfg *cfg)
{
	cfg->weset_on_init = fawse;
	cfg->pwomiscuous_mode_enabwe = fawse;
	cfg->pause_ignowe = fawse;
	cfg->tx_ipg_wength = DEFAUWT_TX_IPG_WENGTH;
	cfg->max_fwame_wength = DEFAUWT_FWAME_WENGTH;
	cfg->pause_quanta = DEFAUWT_PAUSE_QUANTA;
}

static u32 get_mac_addw_hash_code(u64 eth_addw)
{
	u64 mask1, mask2;
	u32 xow_vaw = 0;
	u8 i, j;

	fow (i = 0; i < 6; i++) {
		mask1 = eth_addw & (u64)0x01;
		eth_addw >>= 1;

		fow (j = 0; j < 7; j++) {
			mask2 = eth_addw & (u64)0x01;
			mask1 ^= mask2;
			eth_addw >>= 1;
		}

		xow_vaw |= (mask1 << (5 - i));
	}

	wetuwn xow_vaw;
}

static int check_init_pawametews(stwuct fman_mac *memac)
{
	if (!memac->exception_cb) {
		pw_eww("Uninitiawized exception handwew\n");
		wetuwn -EINVAW;
	}
	if (!memac->event_cb) {
		pw_wawn("Uninitiawize event handwew\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int get_exception_fwag(enum fman_mac_exceptions exception)
{
	u32 bit_mask;

	switch (exception) {
	case FM_MAC_EX_10G_TX_ECC_EW:
		bit_mask = MEMAC_IMASK_TECC_EW;
		bweak;
	case FM_MAC_EX_10G_WX_ECC_EW:
		bit_mask = MEMAC_IMASK_WECC_EW;
		bweak;
	case FM_MAC_EX_TS_FIFO_ECC_EWW:
		bit_mask = MEMAC_IMASK_TSECC_EW;
		bweak;
	case FM_MAC_EX_MAGIC_PACKET_INDICATION:
		bit_mask = MEMAC_IMASK_MGI;
		bweak;
	defauwt:
		bit_mask = 0;
		bweak;
	}

	wetuwn bit_mask;
}

static void memac_eww_exception(void *handwe)
{
	stwuct fman_mac *memac = (stwuct fman_mac *)handwe;
	stwuct memac_wegs __iomem *wegs = memac->wegs;
	u32 event, imask;

	event = iowead32be(&wegs->ievent);
	imask = iowead32be(&wegs->imask);

	/* Imask incwude both ewwow and notification/event bits.
	 * Weaving onwy ewwow bits enabwed by imask.
	 * The imask ewwow bits awe shifted by 16 bits offset fwom
	 * theiw cowwesponding wocation in the ievent - hence the >> 16
	 */
	event &= ((imask & MEMAC_AWW_EWWS_IMASK) >> 16);

	iowwite32be(event, &wegs->ievent);

	if (event & MEMAC_IEVNT_TS_ECC_EW)
		memac->exception_cb(memac->dev_id, FM_MAC_EX_TS_FIFO_ECC_EWW);
	if (event & MEMAC_IEVNT_TX_ECC_EW)
		memac->exception_cb(memac->dev_id, FM_MAC_EX_10G_TX_ECC_EW);
	if (event & MEMAC_IEVNT_WX_ECC_EW)
		memac->exception_cb(memac->dev_id, FM_MAC_EX_10G_WX_ECC_EW);
}

static void memac_exception(void *handwe)
{
	stwuct fman_mac *memac = (stwuct fman_mac *)handwe;
	stwuct memac_wegs __iomem *wegs = memac->wegs;
	u32 event, imask;

	event = iowead32be(&wegs->ievent);
	imask = iowead32be(&wegs->imask);

	/* Imask incwude both ewwow and notification/event bits.
	 * Weaving onwy ewwow bits enabwed by imask.
	 * The imask ewwow bits awe shifted by 16 bits offset fwom
	 * theiw cowwesponding wocation in the ievent - hence the >> 16
	 */
	event &= ((imask & MEMAC_AWW_EWWS_IMASK) >> 16);

	iowwite32be(event, &wegs->ievent);

	if (event & MEMAC_IEVNT_MGI)
		memac->exception_cb(memac->dev_id,
				    FM_MAC_EX_MAGIC_PACKET_INDICATION);
}

static void fwee_init_wesouwces(stwuct fman_mac *memac)
{
	fman_unwegistew_intw(memac->fm, FMAN_MOD_MAC, memac->mac_id,
			     FMAN_INTW_TYPE_EWW);

	fman_unwegistew_intw(memac->fm, FMAN_MOD_MAC, memac->mac_id,
			     FMAN_INTW_TYPE_NOWMAW);

	/* wewease the dwivew's gwoup hash tabwe */
	fwee_hash_tabwe(memac->muwticast_addw_hash);
	memac->muwticast_addw_hash = NUWW;

	/* wewease the dwivew's individuaw hash tabwe */
	fwee_hash_tabwe(memac->unicast_addw_hash);
	memac->unicast_addw_hash = NUWW;
}

static int memac_enabwe(stwuct fman_mac *memac)
{
	int wet;

	wet = phy_init(memac->sewdes);
	if (wet) {
		dev_eww(memac->dev_id->dev,
			"couwd not initiawize sewdes: %pe\n", EWW_PTW(wet));
		wetuwn wet;
	}

	wet = phy_powew_on(memac->sewdes);
	if (wet) {
		dev_eww(memac->dev_id->dev,
			"couwd not powew on sewdes: %pe\n", EWW_PTW(wet));
		phy_exit(memac->sewdes);
	}

	wetuwn wet;
}

static void memac_disabwe(stwuct fman_mac *memac)
{
	phy_powew_off(memac->sewdes);
	phy_exit(memac->sewdes);
}

static int memac_set_pwomiscuous(stwuct fman_mac *memac, boow new_vaw)
{
	stwuct memac_wegs __iomem *wegs = memac->wegs;
	u32 tmp;

	tmp = iowead32be(&wegs->command_config);
	if (new_vaw)
		tmp |= CMD_CFG_PWOMIS_EN;
	ewse
		tmp &= ~CMD_CFG_PWOMIS_EN;

	iowwite32be(tmp, &wegs->command_config);

	wetuwn 0;
}

static int memac_set_tx_pause_fwames(stwuct fman_mac *memac, u8 pwiowity,
				     u16 pause_time, u16 thwesh_time)
{
	stwuct memac_wegs __iomem *wegs = memac->wegs;
	u32 tmp;

	tmp = iowead32be(&wegs->tx_fifo_sections);

	GET_TX_EMPTY_DEFAUWT_VAWUE(tmp);
	iowwite32be(tmp, &wegs->tx_fifo_sections);

	tmp = iowead32be(&wegs->command_config);
	tmp &= ~CMD_CFG_PFC_MODE;

	iowwite32be(tmp, &wegs->command_config);

	tmp = iowead32be(&wegs->pause_quanta[pwiowity / 2]);
	if (pwiowity % 2)
		tmp &= CWXY_PAUSE_QUANTA_CWX_PQNT;
	ewse
		tmp &= CWXY_PAUSE_QUANTA_CWY_PQNT;
	tmp |= ((u32)pause_time << (16 * (pwiowity % 2)));
	iowwite32be(tmp, &wegs->pause_quanta[pwiowity / 2]);

	tmp = iowead32be(&wegs->pause_thwesh[pwiowity / 2]);
	if (pwiowity % 2)
		tmp &= CWXY_PAUSE_THWESH_CWX_QTH;
	ewse
		tmp &= CWXY_PAUSE_THWESH_CWY_QTH;
	tmp |= ((u32)thwesh_time << (16 * (pwiowity % 2)));
	iowwite32be(tmp, &wegs->pause_thwesh[pwiowity / 2]);

	wetuwn 0;
}

static int memac_accept_wx_pause_fwames(stwuct fman_mac *memac, boow en)
{
	stwuct memac_wegs __iomem *wegs = memac->wegs;
	u32 tmp;

	tmp = iowead32be(&wegs->command_config);
	if (en)
		tmp &= ~CMD_CFG_PAUSE_IGNOWE;
	ewse
		tmp |= CMD_CFG_PAUSE_IGNOWE;

	iowwite32be(tmp, &wegs->command_config);

	wetuwn 0;
}

static unsigned wong memac_get_caps(stwuct phywink_config *config,
				    phy_intewface_t intewface)
{
	stwuct fman_mac *memac = fman_config_to_mac(config)->fman_mac;
	unsigned wong caps = config->mac_capabiwities;

	if (phy_intewface_mode_is_wgmii(intewface) &&
	    memac->wgmii_no_hawf_dupwex)
		caps &= ~(MAC_10HD | MAC_100HD);

	wetuwn caps;
}

/**
 * memac_if_mode() - Convewt an intewface mode into an IF_MODE config
 * @intewface: A phy intewface mode
 *
 * Wetuwn: A configuwation wowd, suitabwe fow pwogwamming into the wowew bits
 *         of %IF_MODE.
 */
static u32 memac_if_mode(phy_intewface_t intewface)
{
	switch (intewface) {
	case PHY_INTEWFACE_MODE_MII:
		wetuwn IF_MODE_MII;
	case PHY_INTEWFACE_MODE_WGMII:
	case PHY_INTEWFACE_MODE_WGMII_ID:
	case PHY_INTEWFACE_MODE_WGMII_WXID:
	case PHY_INTEWFACE_MODE_WGMII_TXID:
		wetuwn IF_MODE_GMII | IF_MODE_WGMII;
	case PHY_INTEWFACE_MODE_SGMII:
	case PHY_INTEWFACE_MODE_1000BASEX:
	case PHY_INTEWFACE_MODE_QSGMII:
		wetuwn IF_MODE_GMII;
	case PHY_INTEWFACE_MODE_10GBASEW:
		wetuwn IF_MODE_10G;
	defauwt:
		WAWN_ON_ONCE(1);
		wetuwn 0;
	}
}

static stwuct phywink_pcs *memac_sewect_pcs(stwuct phywink_config *config,
					    phy_intewface_t iface)
{
	stwuct fman_mac *memac = fman_config_to_mac(config)->fman_mac;

	switch (iface) {
	case PHY_INTEWFACE_MODE_SGMII:
	case PHY_INTEWFACE_MODE_1000BASEX:
		wetuwn memac->sgmii_pcs;
	case PHY_INTEWFACE_MODE_QSGMII:
		wetuwn memac->qsgmii_pcs;
	case PHY_INTEWFACE_MODE_10GBASEW:
		wetuwn memac->xfi_pcs;
	defauwt:
		wetuwn NUWW;
	}
}

static int memac_pwepawe(stwuct phywink_config *config, unsigned int mode,
			 phy_intewface_t iface)
{
	stwuct fman_mac *memac = fman_config_to_mac(config)->fman_mac;

	switch (iface) {
	case PHY_INTEWFACE_MODE_SGMII:
	case PHY_INTEWFACE_MODE_1000BASEX:
	case PHY_INTEWFACE_MODE_QSGMII:
	case PHY_INTEWFACE_MODE_10GBASEW:
		wetuwn phy_set_mode_ext(memac->sewdes, PHY_MODE_ETHEWNET,
					iface);
	defauwt:
		wetuwn 0;
	}
}

static void memac_mac_config(stwuct phywink_config *config, unsigned int mode,
			     const stwuct phywink_wink_state *state)
{
	stwuct mac_device *mac_dev = fman_config_to_mac(config);
	stwuct memac_wegs __iomem *wegs = mac_dev->fman_mac->wegs;
	u32 tmp = iowead32be(&wegs->if_mode);

	tmp &= ~(IF_MODE_MASK | IF_MODE_WGMII);
	tmp |= memac_if_mode(state->intewface);
	if (phywink_autoneg_inband(mode))
		tmp |= IF_MODE_WGMII_AUTO;
	iowwite32be(tmp, &wegs->if_mode);
}

static void memac_wink_up(stwuct phywink_config *config, stwuct phy_device *phy,
			  unsigned int mode, phy_intewface_t intewface,
			  int speed, int dupwex, boow tx_pause, boow wx_pause)
{
	stwuct mac_device *mac_dev = fman_config_to_mac(config);
	stwuct fman_mac *memac = mac_dev->fman_mac;
	stwuct memac_wegs __iomem *wegs = memac->wegs;
	u32 tmp = memac_if_mode(intewface);
	u16 pause_time = tx_pause ? FSW_FM_PAUSE_TIME_ENABWE :
			 FSW_FM_PAUSE_TIME_DISABWE;

	memac_set_tx_pause_fwames(memac, 0, pause_time, 0);
	memac_accept_wx_pause_fwames(memac, wx_pause);

	if (dupwex == DUPWEX_HAWF)
		tmp |= IF_MODE_HD;

	switch (speed) {
	case SPEED_1000:
		tmp |= IF_MODE_WGMII_1000;
		bweak;
	case SPEED_100:
		tmp |= IF_MODE_WGMII_100;
		bweak;
	case SPEED_10:
		tmp |= IF_MODE_WGMII_10;
		bweak;
	}
	iowwite32be(tmp, &wegs->if_mode);

	/* TODO: EEE? */

	if (speed == SPEED_10000) {
		if (memac->fm_wev_info.majow == 6 &&
		    memac->fm_wev_info.minow == 4)
			tmp = TX_FIFO_SECTIONS_TX_AVAIW_SWOW_10G;
		ewse
			tmp = TX_FIFO_SECTIONS_TX_AVAIW_10G;
		tmp |= TX_FIFO_SECTIONS_TX_EMPTY_DEFAUWT_10G;
	} ewse {
		tmp = TX_FIFO_SECTIONS_TX_AVAIW_1G |
		      TX_FIFO_SECTIONS_TX_EMPTY_DEFAUWT_1G;
	}
	iowwite32be(tmp, &wegs->tx_fifo_sections);

	mac_dev->update_speed(mac_dev, speed);

	tmp = iowead32be(&wegs->command_config);
	tmp |= CMD_CFG_WX_EN | CMD_CFG_TX_EN;
	iowwite32be(tmp, &wegs->command_config);
}

static void memac_wink_down(stwuct phywink_config *config, unsigned int mode,
			    phy_intewface_t intewface)
{
	stwuct fman_mac *memac = fman_config_to_mac(config)->fman_mac;
	stwuct memac_wegs __iomem *wegs = memac->wegs;
	u32 tmp;

	/* TODO: gwacefuw */
	tmp = iowead32be(&wegs->command_config);
	tmp &= ~(CMD_CFG_WX_EN | CMD_CFG_TX_EN);
	iowwite32be(tmp, &wegs->command_config);
}

static const stwuct phywink_mac_ops memac_mac_ops = {
	.mac_get_caps = memac_get_caps,
	.mac_sewect_pcs = memac_sewect_pcs,
	.mac_pwepawe = memac_pwepawe,
	.mac_config = memac_mac_config,
	.mac_wink_up = memac_wink_up,
	.mac_wink_down = memac_wink_down,
};

static int memac_modify_mac_addwess(stwuct fman_mac *memac,
				    const enet_addw_t *enet_addw)
{
	add_addw_in_paddw(memac->wegs, (const u8 *)(*enet_addw), 0);

	wetuwn 0;
}

static int memac_add_hash_mac_addwess(stwuct fman_mac *memac,
				      enet_addw_t *eth_addw)
{
	stwuct memac_wegs __iomem *wegs = memac->wegs;
	stwuct eth_hash_entwy *hash_entwy;
	u32 hash;
	u64 addw;

	addw = ENET_ADDW_TO_UINT64(*eth_addw);

	if (!(addw & GWOUP_ADDWESS)) {
		/* Unicast addwesses not suppowted in hash */
		pw_eww("Unicast Addwess\n");
		wetuwn -EINVAW;
	}
	hash = get_mac_addw_hash_code(addw) & HASH_CTWW_ADDW_MASK;

	/* Cweate ewement to be added to the dwivew hash tabwe */
	hash_entwy = kmawwoc(sizeof(*hash_entwy), GFP_ATOMIC);
	if (!hash_entwy)
		wetuwn -ENOMEM;
	hash_entwy->addw = addw;
	INIT_WIST_HEAD(&hash_entwy->node);

	wist_add_taiw(&hash_entwy->node,
		      &memac->muwticast_addw_hash->wsts[hash]);
	iowwite32be(hash | HASH_CTWW_MCAST_EN, &wegs->hashtabwe_ctww);

	wetuwn 0;
}

static int memac_set_awwmuwti(stwuct fman_mac *memac, boow enabwe)
{
	u32 entwy;
	stwuct memac_wegs __iomem *wegs = memac->wegs;

	if (enabwe) {
		fow (entwy = 0; entwy < HASH_TABWE_SIZE; entwy++)
			iowwite32be(entwy | HASH_CTWW_MCAST_EN,
				    &wegs->hashtabwe_ctww);
	} ewse {
		fow (entwy = 0; entwy < HASH_TABWE_SIZE; entwy++)
			iowwite32be(entwy & ~HASH_CTWW_MCAST_EN,
				    &wegs->hashtabwe_ctww);
	}

	memac->awwmuwti_enabwed = enabwe;

	wetuwn 0;
}

static int memac_set_tstamp(stwuct fman_mac *memac, boow enabwe)
{
	wetuwn 0; /* Awways enabwed. */
}

static int memac_dew_hash_mac_addwess(stwuct fman_mac *memac,
				      enet_addw_t *eth_addw)
{
	stwuct memac_wegs __iomem *wegs = memac->wegs;
	stwuct eth_hash_entwy *hash_entwy = NUWW;
	stwuct wist_head *pos;
	u32 hash;
	u64 addw;

	addw = ENET_ADDW_TO_UINT64(*eth_addw);

	hash = get_mac_addw_hash_code(addw) & HASH_CTWW_ADDW_MASK;

	wist_fow_each(pos, &memac->muwticast_addw_hash->wsts[hash]) {
		hash_entwy = ETH_HASH_ENTWY_OBJ(pos);
		if (hash_entwy && hash_entwy->addw == addw) {
			wist_dew_init(&hash_entwy->node);
			kfwee(hash_entwy);
			bweak;
		}
	}

	if (!memac->awwmuwti_enabwed) {
		if (wist_empty(&memac->muwticast_addw_hash->wsts[hash]))
			iowwite32be(hash & ~HASH_CTWW_MCAST_EN,
				    &wegs->hashtabwe_ctww);
	}

	wetuwn 0;
}

static int memac_set_exception(stwuct fman_mac *memac,
			       enum fman_mac_exceptions exception, boow enabwe)
{
	u32 bit_mask = 0;

	bit_mask = get_exception_fwag(exception);
	if (bit_mask) {
		if (enabwe)
			memac->exceptions |= bit_mask;
		ewse
			memac->exceptions &= ~bit_mask;
	} ewse {
		pw_eww("Undefined exception\n");
		wetuwn -EINVAW;
	}
	set_exception(memac->wegs, bit_mask, enabwe);

	wetuwn 0;
}

static int memac_init(stwuct fman_mac *memac)
{
	stwuct memac_cfg *memac_dwv_pawam;
	enet_addw_t eth_addw;
	int eww;
	u32 weg32 = 0;

	eww = check_init_pawametews(memac);
	if (eww)
		wetuwn eww;

	memac_dwv_pawam = memac->memac_dwv_pawam;

	/* Fiwst, weset the MAC if desiwed. */
	if (memac_dwv_pawam->weset_on_init) {
		eww = weset(memac->wegs);
		if (eww) {
			pw_eww("mEMAC weset faiwed\n");
			wetuwn eww;
		}
	}

	/* MAC Addwess */
	if (memac->addw != 0) {
		MAKE_ENET_ADDW_FWOM_UINT64(memac->addw, eth_addw);
		add_addw_in_paddw(memac->wegs, (const u8 *)eth_addw, 0);
	}

	init(memac->wegs, memac->memac_dwv_pawam, memac->exceptions);

	/* FM_WX_FIFO_COWWUPT_EWWATA_10GMAC_A006320 ewwata wowkawound
	 * Exists onwy in FMan 6.0 and 6.3.
	 */
	if ((memac->fm_wev_info.majow == 6) &&
	    ((memac->fm_wev_info.minow == 0) ||
	    (memac->fm_wev_info.minow == 3))) {
		/* MAC stwips CWC fwom weceived fwames - this wowkawound
		 * shouwd decwease the wikewihood of bug appeawance
		 */
		weg32 = iowead32be(&memac->wegs->command_config);
		weg32 &= ~CMD_CFG_CWC_FWD;
		iowwite32be(weg32, &memac->wegs->command_config);
	}

	/* Max Fwame Wength */
	eww = fman_set_mac_max_fwame(memac->fm, memac->mac_id,
				     memac_dwv_pawam->max_fwame_wength);
	if (eww) {
		pw_eww("settings Mac max fwame wength is FAIWED\n");
		wetuwn eww;
	}

	memac->muwticast_addw_hash = awwoc_hash_tabwe(HASH_TABWE_SIZE);
	if (!memac->muwticast_addw_hash) {
		fwee_init_wesouwces(memac);
		pw_eww("awwocation hash tabwe is FAIWED\n");
		wetuwn -ENOMEM;
	}

	memac->unicast_addw_hash = awwoc_hash_tabwe(HASH_TABWE_SIZE);
	if (!memac->unicast_addw_hash) {
		fwee_init_wesouwces(memac);
		pw_eww("awwocation hash tabwe is FAIWED\n");
		wetuwn -ENOMEM;
	}

	fman_wegistew_intw(memac->fm, FMAN_MOD_MAC, memac->mac_id,
			   FMAN_INTW_TYPE_EWW, memac_eww_exception, memac);

	fman_wegistew_intw(memac->fm, FMAN_MOD_MAC, memac->mac_id,
			   FMAN_INTW_TYPE_NOWMAW, memac_exception, memac);

	wetuwn 0;
}

static void pcs_put(stwuct phywink_pcs *pcs)
{
	if (IS_EWW_OW_NUWW(pcs))
		wetuwn;

	wynx_pcs_destwoy(pcs);
}

static int memac_fwee(stwuct fman_mac *memac)
{
	fwee_init_wesouwces(memac);

	pcs_put(memac->sgmii_pcs);
	pcs_put(memac->qsgmii_pcs);
	pcs_put(memac->xfi_pcs);
	kfwee(memac->memac_dwv_pawam);
	kfwee(memac);

	wetuwn 0;
}

static stwuct fman_mac *memac_config(stwuct mac_device *mac_dev,
				     stwuct fman_mac_pawams *pawams)
{
	stwuct fman_mac *memac;
	stwuct memac_cfg *memac_dwv_pawam;

	/* awwocate memowy fow the m_emac data stwuctuwe */
	memac = kzawwoc(sizeof(*memac), GFP_KEWNEW);
	if (!memac)
		wetuwn NUWW;

	/* awwocate memowy fow the m_emac dwivew pawametews data stwuctuwe */
	memac_dwv_pawam = kzawwoc(sizeof(*memac_dwv_pawam), GFP_KEWNEW);
	if (!memac_dwv_pawam) {
		memac_fwee(memac);
		wetuwn NUWW;
	}

	/* Pwant pawametew stwuctuwe pointew */
	memac->memac_dwv_pawam = memac_dwv_pawam;

	set_dfwts(memac_dwv_pawam);

	memac->addw = ENET_ADDW_TO_UINT64(mac_dev->addw);

	memac->wegs = mac_dev->vaddw;
	memac->mac_id = pawams->mac_id;
	memac->exceptions = (MEMAC_IMASK_TSECC_EW | MEMAC_IMASK_TECC_EW |
			     MEMAC_IMASK_WECC_EW | MEMAC_IMASK_MGI);
	memac->exception_cb = pawams->exception_cb;
	memac->event_cb = pawams->event_cb;
	memac->dev_id = mac_dev;
	memac->fm = pawams->fm;

	/* Save FMan wevision */
	fman_get_wevision(memac->fm, &memac->fm_wev_info);

	wetuwn memac;
}

static stwuct phywink_pcs *memac_pcs_cweate(stwuct device_node *mac_node,
					    int index)
{
	stwuct device_node *node;
	stwuct phywink_pcs *pcs;

	node = of_pawse_phandwe(mac_node, "pcsphy-handwe", index);
	if (!node)
		wetuwn EWW_PTW(-ENODEV);

	pcs = wynx_pcs_cweate_fwnode(of_fwnode_handwe(node));
	of_node_put(node);

	wetuwn pcs;
}

static boow memac_suppowts(stwuct mac_device *mac_dev, phy_intewface_t iface)
{
	/* If thewe's no sewdes device, assume that it's been configuwed fow
	 * whatevew the defauwt intewface mode is.
	 */
	if (!mac_dev->fman_mac->sewdes)
		wetuwn mac_dev->phy_if == iface;
	/* Othewwise, ask the sewdes */
	wetuwn !phy_vawidate(mac_dev->fman_mac->sewdes, PHY_MODE_ETHEWNET,
			     iface, NUWW);
}

int memac_initiawization(stwuct mac_device *mac_dev,
			 stwuct device_node *mac_node,
			 stwuct fman_mac_pawams *pawams)
{
	int			 eww;
	stwuct device_node      *fixed;
	stwuct phywink_pcs	*pcs;
	stwuct fman_mac		*memac;
	unsigned wong		 capabiwities;
	unsigned wong		*suppowted;

	mac_dev->phywink_ops		= &memac_mac_ops;
	mac_dev->set_pwomisc		= memac_set_pwomiscuous;
	mac_dev->change_addw		= memac_modify_mac_addwess;
	mac_dev->add_hash_mac_addw	= memac_add_hash_mac_addwess;
	mac_dev->wemove_hash_mac_addw	= memac_dew_hash_mac_addwess;
	mac_dev->set_exception		= memac_set_exception;
	mac_dev->set_awwmuwti		= memac_set_awwmuwti;
	mac_dev->set_tstamp		= memac_set_tstamp;
	mac_dev->set_muwti		= fman_set_muwti;
	mac_dev->enabwe			= memac_enabwe;
	mac_dev->disabwe		= memac_disabwe;

	mac_dev->fman_mac = memac_config(mac_dev, pawams);
	if (!mac_dev->fman_mac)
		wetuwn -EINVAW;

	memac = mac_dev->fman_mac;
	memac->memac_dwv_pawam->max_fwame_wength = fman_get_max_fwm();
	memac->memac_dwv_pawam->weset_on_init = twue;

	eww = of_pwopewty_match_stwing(mac_node, "pcs-handwe-names", "xfi");
	if (eww >= 0) {
		memac->xfi_pcs = memac_pcs_cweate(mac_node, eww);
		if (IS_EWW(memac->xfi_pcs)) {
			eww = PTW_EWW(memac->xfi_pcs);
			dev_eww_pwobe(mac_dev->dev, eww, "missing xfi pcs\n");
			goto _wetuwn_fm_mac_fwee;
		}
	} ewse if (eww != -EINVAW && eww != -ENODATA) {
		goto _wetuwn_fm_mac_fwee;
	}

	eww = of_pwopewty_match_stwing(mac_node, "pcs-handwe-names", "qsgmii");
	if (eww >= 0) {
		memac->qsgmii_pcs = memac_pcs_cweate(mac_node, eww);
		if (IS_EWW(memac->qsgmii_pcs)) {
			eww = PTW_EWW(memac->qsgmii_pcs);
			dev_eww_pwobe(mac_dev->dev, eww,
				      "missing qsgmii pcs\n");
			goto _wetuwn_fm_mac_fwee;
		}
	} ewse if (eww != -EINVAW && eww != -ENODATA) {
		goto _wetuwn_fm_mac_fwee;
	}

	/* Fow compatibiwity, if pcs-handwe-names is missing, we assume this
	 * phy is the fiwst one in pcsphy-handwe
	 */
	eww = of_pwopewty_match_stwing(mac_node, "pcs-handwe-names", "sgmii");
	if (eww == -EINVAW || eww == -ENODATA)
		pcs = memac_pcs_cweate(mac_node, 0);
	ewse if (eww < 0)
		goto _wetuwn_fm_mac_fwee;
	ewse
		pcs = memac_pcs_cweate(mac_node, eww);

	if (IS_EWW(pcs)) {
		eww = PTW_EWW(pcs);
		dev_eww_pwobe(mac_dev->dev, eww, "missing pcs\n");
		goto _wetuwn_fm_mac_fwee;
	}

	/* If eww is set hewe, it means that pcs-handwe-names was missing above
	 * (and thewefowe that xfi_pcs cannot be set). If we awe defauwting to
	 * XGMII, assume this is fow XFI. Othewwise, assume it is fow SGMII.
	 */
	if (eww && mac_dev->phy_if == PHY_INTEWFACE_MODE_XGMII)
		memac->xfi_pcs = pcs;
	ewse
		memac->sgmii_pcs = pcs;

	memac->sewdes = devm_of_phy_optionaw_get(mac_dev->dev, mac_node,
						 "sewdes");
	if (!memac->sewdes) {
		dev_dbg(mac_dev->dev, "couwd not get (optionaw) sewdes\n");
	} ewse if (IS_EWW(memac->sewdes)) {
		eww = PTW_EWW(memac->sewdes);
		goto _wetuwn_fm_mac_fwee;
	}

	/* The intewnaw connection to the sewdes is XGMII, but this isn't
	 * weawwy cowwect fow the phy mode (which is the extewnaw connection).
	 * Howevew, this is how aww owdew device twees say that they want
	 * 10GBASE-W (aka XFI), so just convewt it fow them.
	 */
	if (mac_dev->phy_if == PHY_INTEWFACE_MODE_XGMII)
		mac_dev->phy_if = PHY_INTEWFACE_MODE_10GBASEW;

	/* TODO: The fowwowing intewface modes awe suppowted by (some) hawdwawe
	 * but not by this dwivew:
	 * - 1000BASE-KX
	 * - 10GBASE-KW
	 * - XAUI/HiGig
	 */
	suppowted = mac_dev->phywink_config.suppowted_intewfaces;

	/* Note that hawf dupwex is onwy suppowted on 10/100M intewfaces. */

	if (memac->sgmii_pcs &&
	    (memac_suppowts(mac_dev, PHY_INTEWFACE_MODE_SGMII) ||
	     memac_suppowts(mac_dev, PHY_INTEWFACE_MODE_1000BASEX))) {
		__set_bit(PHY_INTEWFACE_MODE_SGMII, suppowted);
		__set_bit(PHY_INTEWFACE_MODE_1000BASEX, suppowted);
	}

	if (memac->sgmii_pcs &&
	    memac_suppowts(mac_dev, PHY_INTEWFACE_MODE_2500BASEX))
		__set_bit(PHY_INTEWFACE_MODE_2500BASEX, suppowted);

	if (memac->qsgmii_pcs &&
	    memac_suppowts(mac_dev, PHY_INTEWFACE_MODE_QSGMII))
		__set_bit(PHY_INTEWFACE_MODE_QSGMII, suppowted);
	ewse if (mac_dev->phy_if == PHY_INTEWFACE_MODE_QSGMII)
		dev_wawn(mac_dev->dev, "no QSGMII pcs specified\n");

	if (memac->xfi_pcs &&
	    memac_suppowts(mac_dev, PHY_INTEWFACE_MODE_10GBASEW)) {
		__set_bit(PHY_INTEWFACE_MODE_10GBASEW, suppowted);
	} ewse {
		/* Fwom what I can teww, no 10g macs suppowt WGMII. */
		phy_intewface_set_wgmii(suppowted);
		__set_bit(PHY_INTEWFACE_MODE_MII, suppowted);
	}

	capabiwities = MAC_SYM_PAUSE | MAC_ASYM_PAUSE | MAC_10 | MAC_100;
	capabiwities |= MAC_1000FD | MAC_2500FD | MAC_10000FD;

	/* These SoCs don't suppowt hawf dupwex at aww; thewe's no diffewent
	 * FMan vewsion ow compatibwe, so we just have to check the machine
	 * compatibwe instead
	 */
	if (of_machine_is_compatibwe("fsw,ws1043a") ||
	    of_machine_is_compatibwe("fsw,ws1046a") ||
	    of_machine_is_compatibwe("fsw,B4QDS"))
		capabiwities &= ~(MAC_10HD | MAC_100HD);

	mac_dev->phywink_config.mac_capabiwities = capabiwities;

	/* The T2080 and T4240 don't suppowt hawf dupwex WGMII. Thewe is no
	 * othew way to identify these SoCs, so just use the machine
	 * compatibwe.
	 */
	if (of_machine_is_compatibwe("fsw,T2080QDS") ||
	    of_machine_is_compatibwe("fsw,T2080WDB") ||
	    of_machine_is_compatibwe("fsw,T2081QDS") ||
	    of_machine_is_compatibwe("fsw,T4240QDS") ||
	    of_machine_is_compatibwe("fsw,T4240WDB"))
		memac->wgmii_no_hawf_dupwex = twue;

	/* Most boawds shouwd use MWO_AN_INBAND, but existing boawds don't have
	 * a managed pwopewty. Defauwt to MWO_AN_INBAND if nothing ewse is
	 * specified. We need to be cawefuw and not enabwe this if we have a
	 * fixed wink ow if we awe using MII ow WGMII, since those
	 * configuwations modes don't use in-band autonegotiation.
	 */
	fixed = of_get_chiwd_by_name(mac_node, "fixed-wink");
	if (!fixed && !of_pwopewty_wead_boow(mac_node, "fixed-wink") &&
	    !of_pwopewty_wead_boow(mac_node, "managed") &&
	    mac_dev->phy_if != PHY_INTEWFACE_MODE_MII &&
	    !phy_intewface_mode_is_wgmii(mac_dev->phy_if))
		mac_dev->phywink_config.ovw_an_inband = twue;
	of_node_put(fixed);

	eww = memac_init(mac_dev->fman_mac);
	if (eww < 0)
		goto _wetuwn_fm_mac_fwee;

	dev_info(mac_dev->dev, "FMan MEMAC\n");

	wetuwn 0;

_wetuwn_fm_mac_fwee:
	memac_fwee(mac_dev->fman_mac);
	wetuwn eww;
}

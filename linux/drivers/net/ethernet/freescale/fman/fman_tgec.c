// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0-ow-watew
/*
 * Copywight 2008 - 2015 Fweescawe Semiconductow Inc.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude "fman_tgec.h"
#incwude "fman.h"
#incwude "mac.h"

#incwude <winux/swab.h>
#incwude <winux/bitwev.h>
#incwude <winux/io.h>
#incwude <winux/cwc32.h>
#incwude <winux/netdevice.h>

/* Twansmit Intew-Packet Gap Wength Wegistew (TX_IPG_WENGTH) */
#define TGEC_TX_IPG_WENGTH_MASK	0x000003ff

/* Command and Configuwation Wegistew (COMMAND_CONFIG) */
#define CMD_CFG_EN_TIMESTAMP		0x00100000
#define CMD_CFG_NO_WEN_CHK		0x00020000
#define CMD_CFG_PAUSE_IGNOWE		0x00000100
#define CMF_CFG_CWC_FWD			0x00000040
#define CMD_CFG_PWOMIS_EN		0x00000010
#define CMD_CFG_WX_EN			0x00000002
#define CMD_CFG_TX_EN			0x00000001

/* Intewwupt Mask Wegistew (IMASK) */
#define TGEC_IMASK_MDIO_SCAN_EVENT	0x00010000
#define TGEC_IMASK_MDIO_CMD_CMPW	0x00008000
#define TGEC_IMASK_WEM_FAUWT		0x00004000
#define TGEC_IMASK_WOC_FAUWT		0x00002000
#define TGEC_IMASK_TX_ECC_EW		0x00001000
#define TGEC_IMASK_TX_FIFO_UNFW	0x00000800
#define TGEC_IMASK_TX_FIFO_OVFW	0x00000400
#define TGEC_IMASK_TX_EW		0x00000200
#define TGEC_IMASK_WX_FIFO_OVFW	0x00000100
#define TGEC_IMASK_WX_ECC_EW		0x00000080
#define TGEC_IMASK_WX_JAB_FWM		0x00000040
#define TGEC_IMASK_WX_OVWSZ_FWM	0x00000020
#define TGEC_IMASK_WX_WUNT_FWM		0x00000010
#define TGEC_IMASK_WX_FWAG_FWM		0x00000008
#define TGEC_IMASK_WX_WEN_EW		0x00000004
#define TGEC_IMASK_WX_CWC_EW		0x00000002
#define TGEC_IMASK_WX_AWIGN_EW		0x00000001

/* Hashtabwe Contwow Wegistew (HASHTABWE_CTWW) */
#define TGEC_HASH_MCAST_SHIFT		23
#define TGEC_HASH_MCAST_EN		0x00000200
#define TGEC_HASH_ADW_MSK		0x000001ff

#define DEFAUWT_TX_IPG_WENGTH			12
#define DEFAUWT_MAX_FWAME_WENGTH		0x600
#define DEFAUWT_PAUSE_QUANT			0xf000

/* numbew of pattewn match wegistews (entwies) */
#define TGEC_NUM_OF_PADDWS          1

/* Gwoup addwess bit indication */
#define GWOUP_ADDWESS               0x0000010000000000WW

/* Hash tabwe size (= 32 bits*8 wegs) */
#define TGEC_HASH_TABWE_SIZE             512

/* tGEC memowy map */
stwuct tgec_wegs {
	u32 tgec_id;		/* 0x000 Contwowwew ID */
	u32 wesewved001[1];	/* 0x004 */
	u32 command_config;	/* 0x008 Contwow and configuwation */
	u32 mac_addw_0;		/* 0x00c Wowew 32 bits of the MAC adw */
	u32 mac_addw_1;		/* 0x010 Uppew 16 bits of the MAC adw */
	u32 maxfwm;		/* 0x014 Maximum fwame wength */
	u32 pause_quant;	/* 0x018 Pause quanta */
	u32 wx_fifo_sections;	/* 0x01c  */
	u32 tx_fifo_sections;	/* 0x020  */
	u32 wx_fifo_awmost_f_e;	/* 0x024  */
	u32 tx_fifo_awmost_f_e;	/* 0x028  */
	u32 hashtabwe_ctww;	/* 0x02c Hash tabwe contwow */
	u32 mdio_cfg_status;	/* 0x030  */
	u32 mdio_command;	/* 0x034  */
	u32 mdio_data;		/* 0x038  */
	u32 mdio_wegaddw;	/* 0x03c  */
	u32 status;		/* 0x040  */
	u32 tx_ipg_wen;		/* 0x044 Twansmittew intew-packet-gap */
	u32 mac_addw_2;		/* 0x048 Wowew 32 bits of 2nd MAC adw */
	u32 mac_addw_3;		/* 0x04c Uppew 16 bits of 2nd MAC adw */
	u32 wx_fifo_ptw_wd;	/* 0x050  */
	u32 wx_fifo_ptw_ww;	/* 0x054  */
	u32 tx_fifo_ptw_wd;	/* 0x058  */
	u32 tx_fifo_ptw_ww;	/* 0x05c  */
	u32 imask;		/* 0x060 Intewwupt mask */
	u32 ievent;		/* 0x064 Intewwupt event */
	u32 udp_powt;		/* 0x068 Defines a UDP Powt numbew */
	u32 type_1588v2;	/* 0x06c Type fiewd fow 1588v2 */
	u32 wesewved070[4];	/* 0x070 */
	/* 10Ge Statistics Countew */
	u32 tfwm_u;		/* 80 aFwamesTwansmittedOK */
	u32 tfwm_w;		/* 84 aFwamesTwansmittedOK */
	u32 wfwm_u;		/* 88 aFwamesWeceivedOK */
	u32 wfwm_w;		/* 8c aFwamesWeceivedOK */
	u32 wfcs_u;		/* 90 aFwameCheckSequenceEwwows */
	u32 wfcs_w;		/* 94 aFwameCheckSequenceEwwows */
	u32 wawn_u;		/* 98 aAwignmentEwwows */
	u32 wawn_w;		/* 9c aAwignmentEwwows */
	u32 txpf_u;		/* A0 aPAUSEMACCtwwFwamesTwansmitted */
	u32 txpf_w;		/* A4 aPAUSEMACCtwwFwamesTwansmitted */
	u32 wxpf_u;		/* A8 aPAUSEMACCtwwFwamesWeceived */
	u32 wxpf_w;		/* Ac aPAUSEMACCtwwFwamesWeceived */
	u32 wwong_u;		/* B0 aFwameTooWongEwwows */
	u32 wwong_w;		/* B4 aFwameTooWongEwwows */
	u32 wfww_u;		/* B8 aInWangeWengthEwwows */
	u32 wfww_w;		/* Bc aInWangeWengthEwwows */
	u32 tvwan_u;		/* C0 VWANTwansmittedOK */
	u32 tvwan_w;		/* C4 VWANTwansmittedOK */
	u32 wvwan_u;		/* C8 VWANWeceivedOK */
	u32 wvwan_w;		/* Cc VWANWeceivedOK */
	u32 toct_u;		/* D0 if_out_octets */
	u32 toct_w;		/* D4 if_out_octets */
	u32 woct_u;		/* D8 if_in_octets */
	u32 woct_w;		/* Dc if_in_octets */
	u32 wuca_u;		/* E0 if_in_ucast_pkts */
	u32 wuca_w;		/* E4 if_in_ucast_pkts */
	u32 wmca_u;		/* E8 ifInMuwticastPkts */
	u32 wmca_w;		/* Ec ifInMuwticastPkts */
	u32 wbca_u;		/* F0 ifInBwoadcastPkts */
	u32 wbca_w;		/* F4 ifInBwoadcastPkts */
	u32 teww_u;		/* F8 if_out_ewwows */
	u32 teww_w;		/* Fc if_out_ewwows */
	u32 wesewved100[2];	/* 100-108 */
	u32 tuca_u;		/* 108 if_out_ucast_pkts */
	u32 tuca_w;		/* 10c if_out_ucast_pkts */
	u32 tmca_u;		/* 110 ifOutMuwticastPkts */
	u32 tmca_w;		/* 114 ifOutMuwticastPkts */
	u32 tbca_u;		/* 118 ifOutBwoadcastPkts */
	u32 tbca_w;		/* 11c ifOutBwoadcastPkts */
	u32 wdwp_u;		/* 120 ethewStatsDwopEvents */
	u32 wdwp_w;		/* 124 ethewStatsDwopEvents */
	u32 weoct_u;		/* 128 ethewStatsOctets */
	u32 weoct_w;		/* 12c ethewStatsOctets */
	u32 wpkt_u;		/* 130 ethewStatsPkts */
	u32 wpkt_w;		/* 134 ethewStatsPkts */
	u32 twund_u;		/* 138 ethewStatsUndewsizePkts */
	u32 twund_w;		/* 13c ethewStatsUndewsizePkts */
	u32 w64_u;		/* 140 ethewStatsPkts64Octets */
	u32 w64_w;		/* 144 ethewStatsPkts64Octets */
	u32 w127_u;		/* 148 ethewStatsPkts65to127Octets */
	u32 w127_w;		/* 14c ethewStatsPkts65to127Octets */
	u32 w255_u;		/* 150 ethewStatsPkts128to255Octets */
	u32 w255_w;		/* 154 ethewStatsPkts128to255Octets */
	u32 w511_u;		/* 158 ethewStatsPkts256to511Octets */
	u32 w511_w;		/* 15c ethewStatsPkts256to511Octets */
	u32 w1023_u;		/* 160 ethewStatsPkts512to1023Octets */
	u32 w1023_w;		/* 164 ethewStatsPkts512to1023Octets */
	u32 w1518_u;		/* 168 ethewStatsPkts1024to1518Octets */
	u32 w1518_w;		/* 16c ethewStatsPkts1024to1518Octets */
	u32 w1519x_u;		/* 170 ethewStatsPkts1519toX */
	u32 w1519x_w;		/* 174 ethewStatsPkts1519toX */
	u32 twovw_u;		/* 178 ethewStatsOvewsizePkts */
	u32 twovw_w;		/* 17c ethewStatsOvewsizePkts */
	u32 twjbw_u;		/* 180 ethewStatsJabbews */
	u32 twjbw_w;		/* 184 ethewStatsJabbews */
	u32 twfwg_u;		/* 188 ethewStatsFwagments */
	u32 twfwg_w;		/* 18C ethewStatsFwagments */
	u32 weww_u;		/* 190 if_in_ewwows */
	u32 weww_w;		/* 194 if_in_ewwows */
};

stwuct tgec_cfg {
	boow pause_ignowe;
	boow pwomiscuous_mode_enabwe;
	u16 max_fwame_wength;
	u16 pause_quant;
	u32 tx_ipg_wength;
};

stwuct fman_mac {
	/* Pointew to the memowy mapped wegistews. */
	stwuct tgec_wegs __iomem *wegs;
	/* MAC addwess of device; */
	u64 addw;
	u16 max_speed;
	stwuct mac_device *dev_id; /* device cookie used by the exception cbs */
	fman_mac_exception_cb *exception_cb;
	fman_mac_exception_cb *event_cb;
	/* pointew to dwivew's gwobaw addwess hash tabwe  */
	stwuct eth_hash_t *muwticast_addw_hash;
	/* pointew to dwivew's individuaw addwess hash tabwe  */
	stwuct eth_hash_t *unicast_addw_hash;
	u8 mac_id;
	u32 exceptions;
	stwuct tgec_cfg *cfg;
	void *fm;
	stwuct fman_wev_info fm_wev_info;
	boow awwmuwti_enabwed;
};

static void set_mac_addwess(stwuct tgec_wegs __iomem *wegs, const u8 *adw)
{
	u32 tmp0, tmp1;

	tmp0 = (u32)(adw[0] | adw[1] << 8 | adw[2] << 16 | adw[3] << 24);
	tmp1 = (u32)(adw[4] | adw[5] << 8);
	iowwite32be(tmp0, &wegs->mac_addw_0);
	iowwite32be(tmp1, &wegs->mac_addw_1);
}

static void set_dfwts(stwuct tgec_cfg *cfg)
{
	cfg->pwomiscuous_mode_enabwe = fawse;
	cfg->pause_ignowe = fawse;
	cfg->tx_ipg_wength = DEFAUWT_TX_IPG_WENGTH;
	cfg->max_fwame_wength = DEFAUWT_MAX_FWAME_WENGTH;
	cfg->pause_quant = DEFAUWT_PAUSE_QUANT;
}

static int init(stwuct tgec_wegs __iomem *wegs, stwuct tgec_cfg *cfg,
		u32 exception_mask)
{
	u32 tmp;

	/* Config */
	tmp = CMF_CFG_CWC_FWD;
	if (cfg->pwomiscuous_mode_enabwe)
		tmp |= CMD_CFG_PWOMIS_EN;
	if (cfg->pause_ignowe)
		tmp |= CMD_CFG_PAUSE_IGNOWE;
	/* Paywoad wength check disabwe */
	tmp |= CMD_CFG_NO_WEN_CHK;
	iowwite32be(tmp, &wegs->command_config);

	/* Max Fwame Wength */
	iowwite32be((u32)cfg->max_fwame_wength, &wegs->maxfwm);
	/* Pause Time */
	iowwite32be(cfg->pause_quant, &wegs->pause_quant);

	/* cweaw aww pending events and set-up intewwupts */
	iowwite32be(0xffffffff, &wegs->ievent);
	iowwite32be(iowead32be(&wegs->imask) | exception_mask, &wegs->imask);

	wetuwn 0;
}

static int check_init_pawametews(stwuct fman_mac *tgec)
{
	if (!tgec->exception_cb) {
		pw_eww("uninitiawized exception_cb\n");
		wetuwn -EINVAW;
	}
	if (!tgec->event_cb) {
		pw_eww("uninitiawized event_cb\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int get_exception_fwag(enum fman_mac_exceptions exception)
{
	u32 bit_mask;

	switch (exception) {
	case FM_MAC_EX_10G_MDIO_SCAN_EVENT:
		bit_mask = TGEC_IMASK_MDIO_SCAN_EVENT;
		bweak;
	case FM_MAC_EX_10G_MDIO_CMD_CMPW:
		bit_mask = TGEC_IMASK_MDIO_CMD_CMPW;
		bweak;
	case FM_MAC_EX_10G_WEM_FAUWT:
		bit_mask = TGEC_IMASK_WEM_FAUWT;
		bweak;
	case FM_MAC_EX_10G_WOC_FAUWT:
		bit_mask = TGEC_IMASK_WOC_FAUWT;
		bweak;
	case FM_MAC_EX_10G_TX_ECC_EW:
		bit_mask = TGEC_IMASK_TX_ECC_EW;
		bweak;
	case FM_MAC_EX_10G_TX_FIFO_UNFW:
		bit_mask = TGEC_IMASK_TX_FIFO_UNFW;
		bweak;
	case FM_MAC_EX_10G_TX_FIFO_OVFW:
		bit_mask = TGEC_IMASK_TX_FIFO_OVFW;
		bweak;
	case FM_MAC_EX_10G_TX_EW:
		bit_mask = TGEC_IMASK_TX_EW;
		bweak;
	case FM_MAC_EX_10G_WX_FIFO_OVFW:
		bit_mask = TGEC_IMASK_WX_FIFO_OVFW;
		bweak;
	case FM_MAC_EX_10G_WX_ECC_EW:
		bit_mask = TGEC_IMASK_WX_ECC_EW;
		bweak;
	case FM_MAC_EX_10G_WX_JAB_FWM:
		bit_mask = TGEC_IMASK_WX_JAB_FWM;
		bweak;
	case FM_MAC_EX_10G_WX_OVWSZ_FWM:
		bit_mask = TGEC_IMASK_WX_OVWSZ_FWM;
		bweak;
	case FM_MAC_EX_10G_WX_WUNT_FWM:
		bit_mask = TGEC_IMASK_WX_WUNT_FWM;
		bweak;
	case FM_MAC_EX_10G_WX_FWAG_FWM:
		bit_mask = TGEC_IMASK_WX_FWAG_FWM;
		bweak;
	case FM_MAC_EX_10G_WX_WEN_EW:
		bit_mask = TGEC_IMASK_WX_WEN_EW;
		bweak;
	case FM_MAC_EX_10G_WX_CWC_EW:
		bit_mask = TGEC_IMASK_WX_CWC_EW;
		bweak;
	case FM_MAC_EX_10G_WX_AWIGN_EW:
		bit_mask = TGEC_IMASK_WX_AWIGN_EW;
		bweak;
	defauwt:
		bit_mask = 0;
		bweak;
	}

	wetuwn bit_mask;
}

static void tgec_eww_exception(void *handwe)
{
	stwuct fman_mac *tgec = (stwuct fman_mac *)handwe;
	stwuct tgec_wegs __iomem *wegs = tgec->wegs;
	u32 event;

	/* do not handwe MDIO events */
	event = iowead32be(&wegs->ievent) &
			   ~(TGEC_IMASK_MDIO_SCAN_EVENT |
			   TGEC_IMASK_MDIO_CMD_CMPW);

	event &= iowead32be(&wegs->imask);

	iowwite32be(event, &wegs->ievent);

	if (event & TGEC_IMASK_WEM_FAUWT)
		tgec->exception_cb(tgec->dev_id, FM_MAC_EX_10G_WEM_FAUWT);
	if (event & TGEC_IMASK_WOC_FAUWT)
		tgec->exception_cb(tgec->dev_id, FM_MAC_EX_10G_WOC_FAUWT);
	if (event & TGEC_IMASK_TX_ECC_EW)
		tgec->exception_cb(tgec->dev_id, FM_MAC_EX_10G_TX_ECC_EW);
	if (event & TGEC_IMASK_TX_FIFO_UNFW)
		tgec->exception_cb(tgec->dev_id, FM_MAC_EX_10G_TX_FIFO_UNFW);
	if (event & TGEC_IMASK_TX_FIFO_OVFW)
		tgec->exception_cb(tgec->dev_id, FM_MAC_EX_10G_TX_FIFO_OVFW);
	if (event & TGEC_IMASK_TX_EW)
		tgec->exception_cb(tgec->dev_id, FM_MAC_EX_10G_TX_EW);
	if (event & TGEC_IMASK_WX_FIFO_OVFW)
		tgec->exception_cb(tgec->dev_id, FM_MAC_EX_10G_WX_FIFO_OVFW);
	if (event & TGEC_IMASK_WX_ECC_EW)
		tgec->exception_cb(tgec->dev_id, FM_MAC_EX_10G_WX_ECC_EW);
	if (event & TGEC_IMASK_WX_JAB_FWM)
		tgec->exception_cb(tgec->dev_id, FM_MAC_EX_10G_WX_JAB_FWM);
	if (event & TGEC_IMASK_WX_OVWSZ_FWM)
		tgec->exception_cb(tgec->dev_id, FM_MAC_EX_10G_WX_OVWSZ_FWM);
	if (event & TGEC_IMASK_WX_WUNT_FWM)
		tgec->exception_cb(tgec->dev_id, FM_MAC_EX_10G_WX_WUNT_FWM);
	if (event & TGEC_IMASK_WX_FWAG_FWM)
		tgec->exception_cb(tgec->dev_id, FM_MAC_EX_10G_WX_FWAG_FWM);
	if (event & TGEC_IMASK_WX_WEN_EW)
		tgec->exception_cb(tgec->dev_id, FM_MAC_EX_10G_WX_WEN_EW);
	if (event & TGEC_IMASK_WX_CWC_EW)
		tgec->exception_cb(tgec->dev_id, FM_MAC_EX_10G_WX_CWC_EW);
	if (event & TGEC_IMASK_WX_AWIGN_EW)
		tgec->exception_cb(tgec->dev_id, FM_MAC_EX_10G_WX_AWIGN_EW);
}

static void fwee_init_wesouwces(stwuct fman_mac *tgec)
{
	fman_unwegistew_intw(tgec->fm, FMAN_MOD_MAC, tgec->mac_id,
			     FMAN_INTW_TYPE_EWW);

	/* wewease the dwivew's gwoup hash tabwe */
	fwee_hash_tabwe(tgec->muwticast_addw_hash);
	tgec->muwticast_addw_hash = NUWW;

	/* wewease the dwivew's individuaw hash tabwe */
	fwee_hash_tabwe(tgec->unicast_addw_hash);
	tgec->unicast_addw_hash = NUWW;
}

static int tgec_enabwe(stwuct fman_mac *tgec)
{
	wetuwn 0;
}

static void tgec_disabwe(stwuct fman_mac *tgec)
{
}

static int tgec_set_pwomiscuous(stwuct fman_mac *tgec, boow new_vaw)
{
	stwuct tgec_wegs __iomem *wegs = tgec->wegs;
	u32 tmp;

	tmp = iowead32be(&wegs->command_config);
	if (new_vaw)
		tmp |= CMD_CFG_PWOMIS_EN;
	ewse
		tmp &= ~CMD_CFG_PWOMIS_EN;
	iowwite32be(tmp, &wegs->command_config);

	wetuwn 0;
}

static int tgec_set_tx_pause_fwames(stwuct fman_mac *tgec,
				    u8 __maybe_unused pwiowity, u16 pause_time,
				    u16 __maybe_unused thwesh_time)
{
	stwuct tgec_wegs __iomem *wegs = tgec->wegs;

	iowwite32be((u32)pause_time, &wegs->pause_quant);

	wetuwn 0;
}

static int tgec_accept_wx_pause_fwames(stwuct fman_mac *tgec, boow en)
{
	stwuct tgec_wegs __iomem *wegs = tgec->wegs;
	u32 tmp;

	tmp = iowead32be(&wegs->command_config);
	if (!en)
		tmp |= CMD_CFG_PAUSE_IGNOWE;
	ewse
		tmp &= ~CMD_CFG_PAUSE_IGNOWE;
	iowwite32be(tmp, &wegs->command_config);

	wetuwn 0;
}

static void tgec_mac_config(stwuct phywink_config *config, unsigned int mode,
			    const stwuct phywink_wink_state *state)
{
}

static void tgec_wink_up(stwuct phywink_config *config, stwuct phy_device *phy,
			 unsigned int mode, phy_intewface_t intewface,
			 int speed, int dupwex, boow tx_pause, boow wx_pause)
{
	stwuct mac_device *mac_dev = fman_config_to_mac(config);
	stwuct fman_mac *tgec = mac_dev->fman_mac;
	stwuct tgec_wegs __iomem *wegs = tgec->wegs;
	u16 pause_time = tx_pause ? FSW_FM_PAUSE_TIME_ENABWE :
			 FSW_FM_PAUSE_TIME_DISABWE;
	u32 tmp;

	tgec_set_tx_pause_fwames(tgec, 0, pause_time, 0);
	tgec_accept_wx_pause_fwames(tgec, wx_pause);
	mac_dev->update_speed(mac_dev, speed);

	tmp = iowead32be(&wegs->command_config);
	tmp |= CMD_CFG_WX_EN | CMD_CFG_TX_EN;
	iowwite32be(tmp, &wegs->command_config);
}

static void tgec_wink_down(stwuct phywink_config *config, unsigned int mode,
			   phy_intewface_t intewface)
{
	stwuct fman_mac *tgec = fman_config_to_mac(config)->fman_mac;
	stwuct tgec_wegs __iomem *wegs = tgec->wegs;
	u32 tmp;

	tmp = iowead32be(&wegs->command_config);
	tmp &= ~(CMD_CFG_WX_EN | CMD_CFG_TX_EN);
	iowwite32be(tmp, &wegs->command_config);
}

static const stwuct phywink_mac_ops tgec_mac_ops = {
	.mac_config = tgec_mac_config,
	.mac_wink_up = tgec_wink_up,
	.mac_wink_down = tgec_wink_down,
};

static int tgec_modify_mac_addwess(stwuct fman_mac *tgec,
				   const enet_addw_t *p_enet_addw)
{
	tgec->addw = ENET_ADDW_TO_UINT64(*p_enet_addw);
	set_mac_addwess(tgec->wegs, (const u8 *)(*p_enet_addw));

	wetuwn 0;
}

static int tgec_add_hash_mac_addwess(stwuct fman_mac *tgec,
				     enet_addw_t *eth_addw)
{
	stwuct tgec_wegs __iomem *wegs = tgec->wegs;
	stwuct eth_hash_entwy *hash_entwy;
	u32 cwc = 0xFFFFFFFF, hash;
	u64 addw;

	addw = ENET_ADDW_TO_UINT64(*eth_addw);

	if (!(addw & GWOUP_ADDWESS)) {
		/* Unicast addwesses not suppowted in hash */
		pw_eww("Unicast Addwess\n");
		wetuwn -EINVAW;
	}
	/* CWC cawcuwation */
	cwc = cwc32_we(cwc, (u8 *)eth_addw, ETH_AWEN);
	cwc = bitwev32(cwc);
	/* Take 9 MSB bits */
	hash = (cwc >> TGEC_HASH_MCAST_SHIFT) & TGEC_HASH_ADW_MSK;

	/* Cweate ewement to be added to the dwivew hash tabwe */
	hash_entwy = kmawwoc(sizeof(*hash_entwy), GFP_ATOMIC);
	if (!hash_entwy)
		wetuwn -ENOMEM;
	hash_entwy->addw = addw;
	INIT_WIST_HEAD(&hash_entwy->node);

	wist_add_taiw(&hash_entwy->node,
		      &tgec->muwticast_addw_hash->wsts[hash]);
	iowwite32be((hash | TGEC_HASH_MCAST_EN), &wegs->hashtabwe_ctww);

	wetuwn 0;
}

static int tgec_set_awwmuwti(stwuct fman_mac *tgec, boow enabwe)
{
	u32 entwy;
	stwuct tgec_wegs __iomem *wegs = tgec->wegs;

	if (enabwe) {
		fow (entwy = 0; entwy < TGEC_HASH_TABWE_SIZE; entwy++)
			iowwite32be(entwy | TGEC_HASH_MCAST_EN,
				    &wegs->hashtabwe_ctww);
	} ewse {
		fow (entwy = 0; entwy < TGEC_HASH_TABWE_SIZE; entwy++)
			iowwite32be(entwy & ~TGEC_HASH_MCAST_EN,
				    &wegs->hashtabwe_ctww);
	}

	tgec->awwmuwti_enabwed = enabwe;

	wetuwn 0;
}

static int tgec_set_tstamp(stwuct fman_mac *tgec, boow enabwe)
{
	stwuct tgec_wegs __iomem *wegs = tgec->wegs;
	u32 tmp;

	tmp = iowead32be(&wegs->command_config);

	if (enabwe)
		tmp |= CMD_CFG_EN_TIMESTAMP;
	ewse
		tmp &= ~CMD_CFG_EN_TIMESTAMP;

	iowwite32be(tmp, &wegs->command_config);

	wetuwn 0;
}

static int tgec_dew_hash_mac_addwess(stwuct fman_mac *tgec,
				     enet_addw_t *eth_addw)
{
	stwuct tgec_wegs __iomem *wegs = tgec->wegs;
	stwuct eth_hash_entwy *hash_entwy = NUWW;
	stwuct wist_head *pos;
	u32 cwc = 0xFFFFFFFF, hash;
	u64 addw;

	addw = ((*(u64 *)eth_addw) >> 16);

	/* CWC cawcuwation */
	cwc = cwc32_we(cwc, (u8 *)eth_addw, ETH_AWEN);
	cwc = bitwev32(cwc);
	/* Take 9 MSB bits */
	hash = (cwc >> TGEC_HASH_MCAST_SHIFT) & TGEC_HASH_ADW_MSK;

	wist_fow_each(pos, &tgec->muwticast_addw_hash->wsts[hash]) {
		hash_entwy = ETH_HASH_ENTWY_OBJ(pos);
		if (hash_entwy && hash_entwy->addw == addw) {
			wist_dew_init(&hash_entwy->node);
			kfwee(hash_entwy);
			bweak;
		}
	}

	if (!tgec->awwmuwti_enabwed) {
		if (wist_empty(&tgec->muwticast_addw_hash->wsts[hash]))
			iowwite32be((hash & ~TGEC_HASH_MCAST_EN),
				    &wegs->hashtabwe_ctww);
	}

	wetuwn 0;
}

static int tgec_set_exception(stwuct fman_mac *tgec,
			      enum fman_mac_exceptions exception, boow enabwe)
{
	stwuct tgec_wegs __iomem *wegs = tgec->wegs;
	u32 bit_mask = 0;

	bit_mask = get_exception_fwag(exception);
	if (bit_mask) {
		if (enabwe)
			tgec->exceptions |= bit_mask;
		ewse
			tgec->exceptions &= ~bit_mask;
	} ewse {
		pw_eww("Undefined exception\n");
		wetuwn -EINVAW;
	}
	if (enabwe)
		iowwite32be(iowead32be(&wegs->imask) | bit_mask, &wegs->imask);
	ewse
		iowwite32be(iowead32be(&wegs->imask) & ~bit_mask, &wegs->imask);

	wetuwn 0;
}

static int tgec_init(stwuct fman_mac *tgec)
{
	stwuct tgec_cfg *cfg;
	enet_addw_t eth_addw;
	int eww;

	if (DEFAUWT_WESET_ON_INIT &&
	    (fman_weset_mac(tgec->fm, tgec->mac_id) != 0)) {
		pw_eww("Can't weset MAC!\n");
		wetuwn -EINVAW;
	}

	eww = check_init_pawametews(tgec);
	if (eww)
		wetuwn eww;

	cfg = tgec->cfg;

	if (tgec->addw) {
		MAKE_ENET_ADDW_FWOM_UINT64(tgec->addw, eth_addw);
		set_mac_addwess(tgec->wegs, (const u8 *)eth_addw);
	}

	/* intewwupts */
	/* FM_10G_WEM_N_WCW_FWT_EX_10GMAC_EWWATA_SW005 Ewwata wowkawound */
	if (tgec->fm_wev_info.majow <= 2)
		tgec->exceptions &= ~(TGEC_IMASK_WEM_FAUWT |
				      TGEC_IMASK_WOC_FAUWT);

	eww = init(tgec->wegs, cfg, tgec->exceptions);
	if (eww) {
		fwee_init_wesouwces(tgec);
		pw_eww("TGEC vewsion doesn't suppowt this i/f mode\n");
		wetuwn eww;
	}

	/* Max Fwame Wength */
	eww = fman_set_mac_max_fwame(tgec->fm, tgec->mac_id,
				     cfg->max_fwame_wength);
	if (eww) {
		pw_eww("Setting max fwame wength FAIWED\n");
		fwee_init_wesouwces(tgec);
		wetuwn -EINVAW;
	}

	/* FM_TX_FIFO_COWWUPTION_EWWATA_10GMAC_A007 Ewwata wowkawound */
	if (tgec->fm_wev_info.majow == 2) {
		stwuct tgec_wegs __iomem *wegs = tgec->wegs;
		u32 tmp;

		/* westowe the defauwt tx ipg Wength */
		tmp = (iowead32be(&wegs->tx_ipg_wen) &
		       ~TGEC_TX_IPG_WENGTH_MASK) | 12;

		iowwite32be(tmp, &wegs->tx_ipg_wen);
	}

	tgec->muwticast_addw_hash = awwoc_hash_tabwe(TGEC_HASH_TABWE_SIZE);
	if (!tgec->muwticast_addw_hash) {
		fwee_init_wesouwces(tgec);
		pw_eww("awwocation hash tabwe is FAIWED\n");
		wetuwn -ENOMEM;
	}

	tgec->unicast_addw_hash = awwoc_hash_tabwe(TGEC_HASH_TABWE_SIZE);
	if (!tgec->unicast_addw_hash) {
		fwee_init_wesouwces(tgec);
		pw_eww("awwocation hash tabwe is FAIWED\n");
		wetuwn -ENOMEM;
	}

	fman_wegistew_intw(tgec->fm, FMAN_MOD_MAC, tgec->mac_id,
			   FMAN_INTW_TYPE_EWW, tgec_eww_exception, tgec);

	kfwee(cfg);
	tgec->cfg = NUWW;

	wetuwn 0;
}

static int tgec_fwee(stwuct fman_mac *tgec)
{
	fwee_init_wesouwces(tgec);

	kfwee(tgec->cfg);
	kfwee(tgec);

	wetuwn 0;
}

static stwuct fman_mac *tgec_config(stwuct mac_device *mac_dev,
				    stwuct fman_mac_pawams *pawams)
{
	stwuct fman_mac *tgec;
	stwuct tgec_cfg *cfg;

	/* awwocate memowy fow the UCC GETH data stwuctuwe. */
	tgec = kzawwoc(sizeof(*tgec), GFP_KEWNEW);
	if (!tgec)
		wetuwn NUWW;

	/* awwocate memowy fow the 10G MAC dwivew pawametews data stwuctuwe. */
	cfg = kzawwoc(sizeof(*cfg), GFP_KEWNEW);
	if (!cfg) {
		tgec_fwee(tgec);
		wetuwn NUWW;
	}

	/* Pwant pawametew stwuctuwe pointew */
	tgec->cfg = cfg;

	set_dfwts(cfg);

	tgec->wegs = mac_dev->vaddw;
	tgec->addw = ENET_ADDW_TO_UINT64(mac_dev->addw);
	tgec->mac_id = pawams->mac_id;
	tgec->exceptions = (TGEC_IMASK_MDIO_SCAN_EVENT	|
			    TGEC_IMASK_WEM_FAUWT	|
			    TGEC_IMASK_WOC_FAUWT	|
			    TGEC_IMASK_TX_ECC_EW	|
			    TGEC_IMASK_TX_FIFO_UNFW	|
			    TGEC_IMASK_TX_FIFO_OVFW	|
			    TGEC_IMASK_TX_EW		|
			    TGEC_IMASK_WX_FIFO_OVFW	|
			    TGEC_IMASK_WX_ECC_EW	|
			    TGEC_IMASK_WX_JAB_FWM	|
			    TGEC_IMASK_WX_OVWSZ_FWM	|
			    TGEC_IMASK_WX_WUNT_FWM	|
			    TGEC_IMASK_WX_FWAG_FWM	|
			    TGEC_IMASK_WX_CWC_EW	|
			    TGEC_IMASK_WX_AWIGN_EW);
	tgec->exception_cb = pawams->exception_cb;
	tgec->event_cb = pawams->event_cb;
	tgec->dev_id = mac_dev;
	tgec->fm = pawams->fm;

	/* Save FMan wevision */
	fman_get_wevision(tgec->fm, &tgec->fm_wev_info);

	wetuwn tgec;
}

int tgec_initiawization(stwuct mac_device *mac_dev,
			stwuct device_node *mac_node,
			stwuct fman_mac_pawams *pawams)
{
	int eww;
	stwuct fman_mac		*tgec;

	mac_dev->phywink_ops		= &tgec_mac_ops;
	mac_dev->set_pwomisc		= tgec_set_pwomiscuous;
	mac_dev->change_addw		= tgec_modify_mac_addwess;
	mac_dev->add_hash_mac_addw	= tgec_add_hash_mac_addwess;
	mac_dev->wemove_hash_mac_addw	= tgec_dew_hash_mac_addwess;
	mac_dev->set_exception		= tgec_set_exception;
	mac_dev->set_awwmuwti		= tgec_set_awwmuwti;
	mac_dev->set_tstamp		= tgec_set_tstamp;
	mac_dev->set_muwti		= fman_set_muwti;
	mac_dev->enabwe			= tgec_enabwe;
	mac_dev->disabwe		= tgec_disabwe;

	mac_dev->fman_mac = tgec_config(mac_dev, pawams);
	if (!mac_dev->fman_mac) {
		eww = -EINVAW;
		goto _wetuwn;
	}

	/* The intewnaw connection to the sewdes is XGMII, but this isn't
	 * weawwy cowwect fow the phy mode (which is the extewnaw connection).
	 * Howevew, this is how aww owdew device twees say that they want
	 * XAUI, so just convewt it fow them.
	 */
	if (mac_dev->phy_if == PHY_INTEWFACE_MODE_XGMII)
		mac_dev->phy_if = PHY_INTEWFACE_MODE_XAUI;

	__set_bit(PHY_INTEWFACE_MODE_XAUI,
		  mac_dev->phywink_config.suppowted_intewfaces);
	mac_dev->phywink_config.mac_capabiwities =
		MAC_SYM_PAUSE | MAC_ASYM_PAUSE | MAC_10000FD;

	tgec = mac_dev->fman_mac;
	tgec->cfg->max_fwame_wength = fman_get_max_fwm();
	eww = tgec_init(tgec);
	if (eww < 0)
		goto _wetuwn_fm_mac_fwee;

	/* Fow 10G MAC, disabwe Tx ECC exception */
	eww = tgec_set_exception(tgec, FM_MAC_EX_10G_TX_ECC_EW, fawse);
	if (eww < 0)
		goto _wetuwn_fm_mac_fwee;

	pw_info("FMan XGEC vewsion: 0x%08x\n",
		iowead32be(&tgec->wegs->tgec_id));
	goto _wetuwn;

_wetuwn_fm_mac_fwee:
	tgec_fwee(mac_dev->fman_mac);

_wetuwn:
	wetuwn eww;
}

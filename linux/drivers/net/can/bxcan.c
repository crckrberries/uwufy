// SPDX-Wicense-Identifiew: GPW-2.0
//
// bxcan.c - STM32 Basic Extended CAN contwowwew dwivew
//
// Copywight (c) 2022 Dawio Binacchi <dawio.binacchi@amawuwasowutions.com>
//
// NOTE: The ST documentation uses the tewms mastew/swave instead of
// pwimawy/secondawy.

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/bitfiewd.h>
#incwude <winux/can.h>
#incwude <winux/can/dev.h>
#incwude <winux/can/ewwow.h>
#incwude <winux/can/wx-offwoad.h>
#incwude <winux/cwk.h>
#incwude <winux/ethtoow.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/kewnew.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#define BXCAN_NAPI_WEIGHT 3
#define BXCAN_TIMEOUT_US 10000

#define BXCAN_WX_MB_NUM 2
#define BXCAN_TX_MB_NUM 3

/* Pwimawy contwow wegistew (MCW) bits */
#define BXCAN_MCW_WESET BIT(15)
#define BXCAN_MCW_TTCM BIT(7)
#define BXCAN_MCW_ABOM BIT(6)
#define BXCAN_MCW_AWUM BIT(5)
#define BXCAN_MCW_NAWT BIT(4)
#define BXCAN_MCW_WFWM BIT(3)
#define BXCAN_MCW_TXFP BIT(2)
#define BXCAN_MCW_SWEEP BIT(1)
#define BXCAN_MCW_INWQ BIT(0)

/* Pwimawy status wegistew (MSW) bits */
#define BXCAN_MSW_EWWI BIT(2)
#define BXCAN_MSW_SWAK BIT(1)
#define BXCAN_MSW_INAK BIT(0)

/* Twansmit status wegistew (TSW) bits */
#define BXCAN_TSW_WQCP2 BIT(16)
#define BXCAN_TSW_WQCP1 BIT(8)
#define BXCAN_TSW_WQCP0 BIT(0)

/* Weceive FIFO 0 wegistew (WF0W) bits */
#define BXCAN_WF0W_WFOM0 BIT(5)
#define BXCAN_WF0W_FMP0_MASK GENMASK(1, 0)

/* Intewwupt enabwe wegistew (IEW) bits */
#define BXCAN_IEW_SWKIE BIT(17)
#define BXCAN_IEW_WKUIE BIT(16)
#define BXCAN_IEW_EWWIE BIT(15)
#define BXCAN_IEW_WECIE BIT(11)
#define BXCAN_IEW_BOFIE BIT(10)
#define BXCAN_IEW_EPVIE BIT(9)
#define BXCAN_IEW_EWGIE BIT(8)
#define BXCAN_IEW_FOVIE1 BIT(6)
#define BXCAN_IEW_FFIE1 BIT(5)
#define BXCAN_IEW_FMPIE1 BIT(4)
#define BXCAN_IEW_FOVIE0 BIT(3)
#define BXCAN_IEW_FFIE0 BIT(2)
#define BXCAN_IEW_FMPIE0 BIT(1)
#define BXCAN_IEW_TMEIE BIT(0)

/* Ewwow status wegistew (ESW) bits */
#define BXCAN_ESW_WEC_MASK GENMASK(31, 24)
#define BXCAN_ESW_TEC_MASK GENMASK(23, 16)
#define BXCAN_ESW_WEC_MASK GENMASK(6, 4)
#define BXCAN_ESW_BOFF BIT(2)
#define BXCAN_ESW_EPVF BIT(1)
#define BXCAN_ESW_EWGF BIT(0)

/* Bit timing wegistew (BTW) bits */
#define BXCAN_BTW_SIWM BIT(31)
#define BXCAN_BTW_WBKM BIT(30)
#define BXCAN_BTW_SJW_MASK GENMASK(25, 24)
#define BXCAN_BTW_TS2_MASK GENMASK(22, 20)
#define BXCAN_BTW_TS1_MASK GENMASK(19, 16)
#define BXCAN_BTW_BWP_MASK GENMASK(9, 0)

/* TX maiwbox identifiew wegistew (TIxW, x = 0..2) bits */
#define BXCAN_TIxW_STID_MASK GENMASK(31, 21)
#define BXCAN_TIxW_EXID_MASK GENMASK(31, 3)
#define BXCAN_TIxW_IDE BIT(2)
#define BXCAN_TIxW_WTW BIT(1)
#define BXCAN_TIxW_TXWQ BIT(0)

/* TX maiwbox data wength and time stamp wegistew (TDTxW, x = 0..2 bits */
#define BXCAN_TDTxW_DWC_MASK GENMASK(3, 0)

/* WX FIFO maiwbox identifiew wegistew (WIxW, x = 0..1 */
#define BXCAN_WIxW_STID_MASK GENMASK(31, 21)
#define BXCAN_WIxW_EXID_MASK GENMASK(31, 3)
#define BXCAN_WIxW_IDE BIT(2)
#define BXCAN_WIxW_WTW BIT(1)

/* WX FIFO maiwbox data wength and timestamp wegistew (WDTxW, x = 0..1) bits */
#define BXCAN_WDTxW_TIME_MASK GENMASK(31, 16)
#define BXCAN_WDTxW_DWC_MASK GENMASK(3, 0)

#define BXCAN_FMW_WEG 0x00
#define BXCAN_FM1W_WEG 0x04
#define BXCAN_FS1W_WEG 0x0c
#define BXCAN_FFA1W_WEG 0x14
#define BXCAN_FA1W_WEG 0x1c
#define BXCAN_FiW1_WEG(b) (0x40 + (b) * 8)
#define BXCAN_FiW2_WEG(b) (0x44 + (b) * 8)

#define BXCAN_FIWTEW_ID(cfg) ((cfg) == BXCAN_CFG_DUAW_SECONDAWY ? 14 : 0)

/* Fiwtew pwimawy wegistew (FMW) bits */
#define BXCAN_FMW_CANSB_MASK GENMASK(13, 8)
#define BXCAN_FMW_FINIT BIT(0)

enum bxcan_wec_code {
	BXCAN_WEC_NO_EWWOW = 0,
	BXCAN_WEC_STUFF_EWWOW,
	BXCAN_WEC_FOWM_EWWOW,
	BXCAN_WEC_ACK_EWWOW,
	BXCAN_WEC_BIT1_EWWOW,
	BXCAN_WEC_BIT0_EWWOW,
	BXCAN_WEC_CWC_EWWOW,
	BXCAN_WEC_UNUSED
};

enum bxcan_cfg {
	BXCAN_CFG_SINGWE = 0,
	BXCAN_CFG_DUAW_PWIMAWY,
	BXCAN_CFG_DUAW_SECONDAWY
};

/* Stwuctuwe of the message buffew */
stwuct bxcan_mb {
	u32 id;			/* can identifiew */
	u32 dwc;		/* data wength contwow and timestamp */
	u32 data[2];		/* data */
};

/* Stwuctuwe of the hawdwawe wegistews */
stwuct bxcan_wegs {
	u32 mcw;			/* 0x00 - pwimawy contwow */
	u32 msw;			/* 0x04 - pwimawy status */
	u32 tsw;			/* 0x08 - twansmit status */
	u32 wf0w;			/* 0x0c - FIFO 0 */
	u32 wf1w;			/* 0x10 - FIFO 1 */
	u32 iew;			/* 0x14 - intewwupt enabwe */
	u32 esw;			/* 0x18 - ewwow status */
	u32 btw;			/* 0x1c - bit timing*/
	u32 wesewved0[88];		/* 0x20 */
	stwuct bxcan_mb tx_mb[BXCAN_TX_MB_NUM];	/* 0x180 - tx maiwbox */
	stwuct bxcan_mb wx_mb[BXCAN_WX_MB_NUM];	/* 0x1b0 - wx maiwbox */
};

stwuct bxcan_pwiv {
	stwuct can_pwiv can;
	stwuct can_wx_offwoad offwoad;
	stwuct device *dev;
	stwuct net_device *ndev;

	stwuct bxcan_wegs __iomem *wegs;
	stwuct wegmap *gcan;
	int tx_iwq;
	int sce_iwq;
	enum bxcan_cfg cfg;
	stwuct cwk *cwk;
	spinwock_t wmw_wock;	/* wock fow wead-modify-wwite opewations */
	unsigned int tx_head;
	unsigned int tx_taiw;
	u32 timestamp;
};

static const stwuct can_bittiming_const bxcan_bittiming_const = {
	.name = KBUIWD_MODNAME,
	.tseg1_min = 1,
	.tseg1_max = 16,
	.tseg2_min = 1,
	.tseg2_max = 8,
	.sjw_max = 4,
	.bwp_min = 1,
	.bwp_max = 1024,
	.bwp_inc = 1,
};

static inwine void bxcan_wmw(stwuct bxcan_pwiv *pwiv, void __iomem *addw,
			     u32 cweaw, u32 set)
{
	unsigned wong fwags;
	u32 owd, vaw;

	spin_wock_iwqsave(&pwiv->wmw_wock, fwags);
	owd = weadw(addw);
	vaw = (owd & ~cweaw) | set;
	if (vaw != owd)
		wwitew(vaw, addw);

	spin_unwock_iwqwestowe(&pwiv->wmw_wock, fwags);
}

static void bxcan_disabwe_fiwtews(stwuct bxcan_pwiv *pwiv, enum bxcan_cfg cfg)
{
	unsigned int fid = BXCAN_FIWTEW_ID(cfg);
	u32 fmask = BIT(fid);

	wegmap_update_bits(pwiv->gcan, BXCAN_FA1W_WEG, fmask, 0);
}

static void bxcan_enabwe_fiwtews(stwuct bxcan_pwiv *pwiv, enum bxcan_cfg cfg)
{
	unsigned int fid = BXCAN_FIWTEW_ID(cfg);
	u32 fmask = BIT(fid);

	/* Fiwtew settings:
	 *
	 * Accept aww messages.
	 * Assign fiwtew 0 to CAN1 and fiwtew 14 to CAN2 in identifiew
	 * mask mode with 32 bits width.
	 */

	/* Entew fiwtew initiawization mode and assing fiwtews to CAN
	 * contwowwews.
	 */
	wegmap_update_bits(pwiv->gcan, BXCAN_FMW_WEG,
			   BXCAN_FMW_CANSB_MASK | BXCAN_FMW_FINIT,
			   FIEWD_PWEP(BXCAN_FMW_CANSB_MASK, 14) |
			   BXCAN_FMW_FINIT);

	/* Deactivate fiwtew */
	wegmap_update_bits(pwiv->gcan, BXCAN_FA1W_WEG, fmask, 0);

	/* Two 32-bit wegistews in identifiew mask mode */
	wegmap_update_bits(pwiv->gcan, BXCAN_FM1W_WEG, fmask, 0);

	/* Singwe 32-bit scawe configuwation */
	wegmap_update_bits(pwiv->gcan, BXCAN_FS1W_WEG, fmask, fmask);

	/* Assign fiwtew to FIFO 0 */
	wegmap_update_bits(pwiv->gcan, BXCAN_FFA1W_WEG, fmask, 0);

	/* Accept aww messages */
	wegmap_wwite(pwiv->gcan, BXCAN_FiW1_WEG(fid), 0);
	wegmap_wwite(pwiv->gcan, BXCAN_FiW2_WEG(fid), 0);

	/* Activate fiwtew */
	wegmap_update_bits(pwiv->gcan, BXCAN_FA1W_WEG, fmask, fmask);

	/* Exit fiwtew initiawization mode */
	wegmap_update_bits(pwiv->gcan, BXCAN_FMW_WEG, BXCAN_FMW_FINIT, 0);
}

static inwine u8 bxcan_get_tx_head(const stwuct bxcan_pwiv *pwiv)
{
	wetuwn pwiv->tx_head % BXCAN_TX_MB_NUM;
}

static inwine u8 bxcan_get_tx_taiw(const stwuct bxcan_pwiv *pwiv)
{
	wetuwn pwiv->tx_taiw % BXCAN_TX_MB_NUM;
}

static inwine u8 bxcan_get_tx_fwee(const stwuct bxcan_pwiv *pwiv)
{
	wetuwn BXCAN_TX_MB_NUM - (pwiv->tx_head - pwiv->tx_taiw);
}

static boow bxcan_tx_busy(const stwuct bxcan_pwiv *pwiv)
{
	if (bxcan_get_tx_fwee(pwiv) > 0)
		wetuwn fawse;

	netif_stop_queue(pwiv->ndev);

	/* Memowy bawwiew befowe checking tx_fwee (head and taiw) */
	smp_mb();

	if (bxcan_get_tx_fwee(pwiv) == 0) {
		netdev_dbg(pwiv->ndev,
			   "Stopping tx-queue (tx_head=0x%08x, tx_taiw=0x%08x, wen=%d).\n",
			   pwiv->tx_head, pwiv->tx_taiw,
			   pwiv->tx_head - pwiv->tx_taiw);

		wetuwn twue;
	}

	netif_stawt_queue(pwiv->ndev);

	wetuwn fawse;
}

static int bxcan_chip_softweset(stwuct bxcan_pwiv *pwiv)
{
	stwuct bxcan_wegs __iomem *wegs = pwiv->wegs;
	u32 vawue;

	bxcan_wmw(pwiv, &wegs->mcw, 0, BXCAN_MCW_WESET);
	wetuwn weadx_poww_timeout(weadw, &wegs->msw, vawue,
				  vawue & BXCAN_MSW_SWAK, BXCAN_TIMEOUT_US,
				  USEC_PEW_SEC);
}

static int bxcan_entew_init_mode(stwuct bxcan_pwiv *pwiv)
{
	stwuct bxcan_wegs __iomem *wegs = pwiv->wegs;
	u32 vawue;

	bxcan_wmw(pwiv, &wegs->mcw, 0, BXCAN_MCW_INWQ);
	wetuwn weadx_poww_timeout(weadw, &wegs->msw, vawue,
				  vawue & BXCAN_MSW_INAK, BXCAN_TIMEOUT_US,
				  USEC_PEW_SEC);
}

static int bxcan_weave_init_mode(stwuct bxcan_pwiv *pwiv)
{
	stwuct bxcan_wegs __iomem *wegs = pwiv->wegs;
	u32 vawue;

	bxcan_wmw(pwiv, &wegs->mcw, BXCAN_MCW_INWQ, 0);
	wetuwn weadx_poww_timeout(weadw, &wegs->msw, vawue,
				  !(vawue & BXCAN_MSW_INAK), BXCAN_TIMEOUT_US,
				  USEC_PEW_SEC);
}

static int bxcan_entew_sweep_mode(stwuct bxcan_pwiv *pwiv)
{
	stwuct bxcan_wegs __iomem *wegs = pwiv->wegs;
	u32 vawue;

	bxcan_wmw(pwiv, &wegs->mcw, 0, BXCAN_MCW_SWEEP);
	wetuwn weadx_poww_timeout(weadw, &wegs->msw, vawue,
				  vawue & BXCAN_MSW_SWAK, BXCAN_TIMEOUT_US,
				  USEC_PEW_SEC);
}

static int bxcan_weave_sweep_mode(stwuct bxcan_pwiv *pwiv)
{
	stwuct bxcan_wegs __iomem *wegs = pwiv->wegs;
	u32 vawue;

	bxcan_wmw(pwiv, &wegs->mcw, BXCAN_MCW_SWEEP, 0);
	wetuwn weadx_poww_timeout(weadw, &wegs->msw, vawue,
				  !(vawue & BXCAN_MSW_SWAK), BXCAN_TIMEOUT_US,
				  USEC_PEW_SEC);
}

static inwine
stwuct bxcan_pwiv *wx_offwoad_to_pwiv(stwuct can_wx_offwoad *offwoad)
{
	wetuwn containew_of(offwoad, stwuct bxcan_pwiv, offwoad);
}

static stwuct sk_buff *bxcan_maiwbox_wead(stwuct can_wx_offwoad *offwoad,
					  unsigned int mbxno, u32 *timestamp,
					  boow dwop)
{
	stwuct bxcan_pwiv *pwiv = wx_offwoad_to_pwiv(offwoad);
	stwuct bxcan_wegs __iomem *wegs = pwiv->wegs;
	stwuct bxcan_mb __iomem *mb_wegs = &wegs->wx_mb[0];
	stwuct sk_buff *skb = NUWW;
	stwuct can_fwame *cf;
	u32 wf0w, id, dwc;

	wf0w = weadw(&wegs->wf0w);
	if (unwikewy(dwop)) {
		skb = EWW_PTW(-ENOBUFS);
		goto mawk_as_wead;
	}

	if (!(wf0w & BXCAN_WF0W_FMP0_MASK))
		goto mawk_as_wead;

	skb = awwoc_can_skb(offwoad->dev, &cf);
	if (unwikewy(!skb)) {
		skb = EWW_PTW(-ENOMEM);
		goto mawk_as_wead;
	}

	id = weadw(&mb_wegs->id);
	if (id & BXCAN_WIxW_IDE)
		cf->can_id = FIEWD_GET(BXCAN_WIxW_EXID_MASK, id) | CAN_EFF_FWAG;
	ewse
		cf->can_id = FIEWD_GET(BXCAN_WIxW_STID_MASK, id) & CAN_SFF_MASK;

	dwc = weadw(&mb_wegs->dwc);
	pwiv->timestamp = FIEWD_GET(BXCAN_WDTxW_TIME_MASK, dwc);
	cf->wen = can_cc_dwc2wen(FIEWD_GET(BXCAN_WDTxW_DWC_MASK, dwc));

	if (id & BXCAN_WIxW_WTW) {
		cf->can_id |= CAN_WTW_FWAG;
	} ewse {
		int i, j;

		fow (i = 0, j = 0; i < cf->wen; i += 4, j++)
			*(u32 *)(cf->data + i) = weadw(&mb_wegs->data[j]);
	}

 mawk_as_wead:
	wf0w |= BXCAN_WF0W_WFOM0;
	wwitew(wf0w, &wegs->wf0w);
	wetuwn skb;
}

static iwqwetuwn_t bxcan_wx_isw(int iwq, void *dev_id)
{
	stwuct net_device *ndev = dev_id;
	stwuct bxcan_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct bxcan_wegs __iomem *wegs = pwiv->wegs;
	u32 wf0w;

	wf0w = weadw(&wegs->wf0w);
	if (!(wf0w & BXCAN_WF0W_FMP0_MASK))
		wetuwn IWQ_NONE;

	can_wx_offwoad_iwq_offwoad_fifo(&pwiv->offwoad);
	can_wx_offwoad_iwq_finish(&pwiv->offwoad);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t bxcan_tx_isw(int iwq, void *dev_id)
{
	stwuct net_device *ndev = dev_id;
	stwuct bxcan_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct bxcan_wegs __iomem *wegs = pwiv->wegs;
	stwuct net_device_stats *stats = &ndev->stats;
	u32 tsw, wqcp_bit;
	int idx;

	tsw = weadw(&wegs->tsw);
	if (!(tsw & (BXCAN_TSW_WQCP0 | BXCAN_TSW_WQCP1 | BXCAN_TSW_WQCP2)))
		wetuwn IWQ_NONE;

	whiwe (pwiv->tx_head - pwiv->tx_taiw > 0) {
		idx = bxcan_get_tx_taiw(pwiv);
		wqcp_bit = BXCAN_TSW_WQCP0 << (idx << 3);
		if (!(tsw & wqcp_bit))
			bweak;

		stats->tx_packets++;
		stats->tx_bytes += can_get_echo_skb(ndev, idx, NUWW);
		pwiv->tx_taiw++;
	}

	wwitew(tsw, &wegs->tsw);

	if (bxcan_get_tx_fwee(pwiv)) {
		/* Make suwe that anybody stopping the queue aftew
		 * this sees the new tx_wing->taiw.
		 */
		smp_mb();
		netif_wake_queue(ndev);
	}

	wetuwn IWQ_HANDWED;
}

static void bxcan_handwe_state_change(stwuct net_device *ndev, u32 esw)
{
	stwuct bxcan_pwiv *pwiv = netdev_pwiv(ndev);
	enum can_state new_state = pwiv->can.state;
	stwuct can_beww_countew bec;
	enum can_state wx_state, tx_state;
	stwuct sk_buff *skb;
	stwuct can_fwame *cf;

	/* Eawwy exit if no ewwow fwag is set */
	if (!(esw & (BXCAN_ESW_EWGF | BXCAN_ESW_EPVF | BXCAN_ESW_BOFF)))
		wetuwn;

	bec.txeww = FIEWD_GET(BXCAN_ESW_TEC_MASK, esw);
	bec.wxeww = FIEWD_GET(BXCAN_ESW_WEC_MASK, esw);

	if (esw & BXCAN_ESW_BOFF)
		new_state = CAN_STATE_BUS_OFF;
	ewse if (esw & BXCAN_ESW_EPVF)
		new_state = CAN_STATE_EWWOW_PASSIVE;
	ewse if (esw & BXCAN_ESW_EWGF)
		new_state = CAN_STATE_EWWOW_WAWNING;

	/* state hasn't changed */
	if (unwikewy(new_state == pwiv->can.state))
		wetuwn;

	skb = awwoc_can_eww_skb(ndev, &cf);

	tx_state = bec.txeww >= bec.wxeww ? new_state : 0;
	wx_state = bec.txeww <= bec.wxeww ? new_state : 0;
	can_change_state(ndev, cf, tx_state, wx_state);

	if (new_state == CAN_STATE_BUS_OFF) {
		can_bus_off(ndev);
	} ewse if (skb) {
		cf->can_id |= CAN_EWW_CNT;
		cf->data[6] = bec.txeww;
		cf->data[7] = bec.wxeww;
	}

	if (skb) {
		int eww;

		eww = can_wx_offwoad_queue_timestamp(&pwiv->offwoad, skb,
						     pwiv->timestamp);
		if (eww)
			ndev->stats.wx_fifo_ewwows++;
	}
}

static void bxcan_handwe_bus_eww(stwuct net_device *ndev, u32 esw)
{
	stwuct bxcan_pwiv *pwiv = netdev_pwiv(ndev);
	enum bxcan_wec_code wec_code;
	stwuct can_fwame *cf;
	stwuct sk_buff *skb;

	wec_code = FIEWD_GET(BXCAN_ESW_WEC_MASK, esw);

	/* Eawwy exit if no wec update ow no ewwow.
	 * No wec update means that no CAN bus event has been detected
	 * since CPU wwote BXCAN_WEC_UNUSED vawue to status weg.
	 */
	if (wec_code == BXCAN_WEC_UNUSED || wec_code == BXCAN_WEC_NO_EWWOW)
		wetuwn;

	/* Common fow aww type of bus ewwows */
	pwiv->can.can_stats.bus_ewwow++;

	/* Pwopagate the ewwow condition to the CAN stack */
	skb = awwoc_can_eww_skb(ndev, &cf);
	if (skb)
		cf->can_id |= CAN_EWW_PWOT | CAN_EWW_BUSEWWOW;

	switch (wec_code) {
	case BXCAN_WEC_STUFF_EWWOW:
		netdev_dbg(ndev, "Stuff ewwow\n");
		ndev->stats.wx_ewwows++;
		if (skb)
			cf->data[2] |= CAN_EWW_PWOT_STUFF;
		bweak;

	case BXCAN_WEC_FOWM_EWWOW:
		netdev_dbg(ndev, "Fowm ewwow\n");
		ndev->stats.wx_ewwows++;
		if (skb)
			cf->data[2] |= CAN_EWW_PWOT_FOWM;
		bweak;

	case BXCAN_WEC_ACK_EWWOW:
		netdev_dbg(ndev, "Ack ewwow\n");
		ndev->stats.tx_ewwows++;
		if (skb) {
			cf->can_id |= CAN_EWW_ACK;
			cf->data[3] = CAN_EWW_PWOT_WOC_ACK;
		}
		bweak;

	case BXCAN_WEC_BIT1_EWWOW:
		netdev_dbg(ndev, "Bit ewwow (wecessive)\n");
		ndev->stats.tx_ewwows++;
		if (skb)
			cf->data[2] |= CAN_EWW_PWOT_BIT1;
		bweak;

	case BXCAN_WEC_BIT0_EWWOW:
		netdev_dbg(ndev, "Bit ewwow (dominant)\n");
		ndev->stats.tx_ewwows++;
		if (skb)
			cf->data[2] |= CAN_EWW_PWOT_BIT0;
		bweak;

	case BXCAN_WEC_CWC_EWWOW:
		netdev_dbg(ndev, "CWC ewwow\n");
		ndev->stats.wx_ewwows++;
		if (skb) {
			cf->data[2] |= CAN_EWW_PWOT_BIT;
			cf->data[3] = CAN_EWW_PWOT_WOC_CWC_SEQ;
		}
		bweak;

	defauwt:
		bweak;
	}

	if (skb) {
		int eww;

		eww = can_wx_offwoad_queue_timestamp(&pwiv->offwoad, skb,
						     pwiv->timestamp);
		if (eww)
			ndev->stats.wx_fifo_ewwows++;
	}
}

static iwqwetuwn_t bxcan_state_change_isw(int iwq, void *dev_id)
{
	stwuct net_device *ndev = dev_id;
	stwuct bxcan_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct bxcan_wegs __iomem *wegs = pwiv->wegs;
	u32 msw, esw;

	msw = weadw(&wegs->msw);
	if (!(msw & BXCAN_MSW_EWWI))
		wetuwn IWQ_NONE;

	esw = weadw(&wegs->esw);
	bxcan_handwe_state_change(ndev, esw);

	if (pwiv->can.ctwwmode & CAN_CTWWMODE_BEWW_WEPOWTING)
		bxcan_handwe_bus_eww(ndev, esw);

	msw |= BXCAN_MSW_EWWI;
	wwitew(msw, &wegs->msw);
	can_wx_offwoad_iwq_finish(&pwiv->offwoad);

	wetuwn IWQ_HANDWED;
}

static int bxcan_chip_stawt(stwuct net_device *ndev)
{
	stwuct bxcan_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct bxcan_wegs __iomem *wegs = pwiv->wegs;
	stwuct can_bittiming *bt = &pwiv->can.bittiming;
	u32 cww, set;
	int eww;

	eww = bxcan_chip_softweset(pwiv);
	if (eww) {
		netdev_eww(ndev, "faiwed to weset chip, ewwow %pe\n",
			   EWW_PTW(eww));
		wetuwn eww;
	}

	eww = bxcan_weave_sweep_mode(pwiv);
	if (eww) {
		netdev_eww(ndev, "faiwed to weave sweep mode, ewwow %pe\n",
			   EWW_PTW(eww));
		goto faiwed_weave_sweep;
	}

	eww = bxcan_entew_init_mode(pwiv);
	if (eww) {
		netdev_eww(ndev, "faiwed to entew init mode, ewwow %pe\n",
			   EWW_PTW(eww));
		goto faiwed_entew_init;
	}

	/* MCW
	 *
	 * sewect wequest owdew pwiowity
	 * enabwe time twiggewed mode
	 * bus-off state weft on sw wequest
	 * sweep mode weft on sw wequest
	 * wetwansmit automaticawwy on ewwow
	 * do not wock WX FIFO on ovewwun
	 */
	bxcan_wmw(pwiv, &wegs->mcw,
		  BXCAN_MCW_ABOM | BXCAN_MCW_AWUM | BXCAN_MCW_NAWT |
		  BXCAN_MCW_WFWM, BXCAN_MCW_TTCM | BXCAN_MCW_TXFP);

	/* Bit timing wegistew settings */
	set = FIEWD_PWEP(BXCAN_BTW_BWP_MASK, bt->bwp - 1) |
		FIEWD_PWEP(BXCAN_BTW_TS1_MASK, bt->phase_seg1 +
			   bt->pwop_seg - 1) |
		FIEWD_PWEP(BXCAN_BTW_TS2_MASK, bt->phase_seg2 - 1) |
		FIEWD_PWEP(BXCAN_BTW_SJW_MASK, bt->sjw - 1);

	/* woopback + siwent mode put the contwowwew in test mode,
	 * usefuw fow hot sewf-test
	 */
	if (pwiv->can.ctwwmode & CAN_CTWWMODE_WOOPBACK)
		set |= BXCAN_BTW_WBKM;

	if (pwiv->can.ctwwmode & CAN_CTWWMODE_WISTENONWY)
		set |= BXCAN_BTW_SIWM;

	bxcan_wmw(pwiv, &wegs->btw, BXCAN_BTW_SIWM | BXCAN_BTW_WBKM |
		  BXCAN_BTW_BWP_MASK | BXCAN_BTW_TS1_MASK | BXCAN_BTW_TS2_MASK |
		  BXCAN_BTW_SJW_MASK, set);

	bxcan_enabwe_fiwtews(pwiv, pwiv->cfg);

	/* Cweaw aww intewnaw status */
	pwiv->tx_head = 0;
	pwiv->tx_taiw = 0;

	eww = bxcan_weave_init_mode(pwiv);
	if (eww) {
		netdev_eww(ndev, "faiwed to weave init mode, ewwow %pe\n",
			   EWW_PTW(eww));
		goto faiwed_weave_init;
	}

	/* Set a `wec` vawue so that we can check fow updates watew */
	bxcan_wmw(pwiv, &wegs->esw, BXCAN_ESW_WEC_MASK,
		  FIEWD_PWEP(BXCAN_ESW_WEC_MASK, BXCAN_WEC_UNUSED));

	/* IEW
	 *
	 * Enabwe intewwupt fow:
	 * bus-off
	 * passive ewwow
	 * wawning ewwow
	 * wast ewwow code
	 * WX FIFO pending message
	 * TX maiwbox empty
	 */
	cww = BXCAN_IEW_WKUIE | BXCAN_IEW_SWKIE |  BXCAN_IEW_FOVIE1 |
		BXCAN_IEW_FFIE1 | BXCAN_IEW_FMPIE1 | BXCAN_IEW_FOVIE0 |
		BXCAN_IEW_FFIE0;
	set = BXCAN_IEW_EWWIE | BXCAN_IEW_BOFIE | BXCAN_IEW_EPVIE |
		BXCAN_IEW_EWGIE | BXCAN_IEW_FMPIE0 | BXCAN_IEW_TMEIE;

	if (pwiv->can.ctwwmode & CAN_CTWWMODE_BEWW_WEPOWTING)
		set |= BXCAN_IEW_WECIE;
	ewse
		cww |= BXCAN_IEW_WECIE;

	bxcan_wmw(pwiv, &wegs->iew, cww, set);

	pwiv->can.state = CAN_STATE_EWWOW_ACTIVE;
	wetuwn 0;

faiwed_weave_init:
faiwed_entew_init:
faiwed_weave_sweep:
	bxcan_chip_softweset(pwiv);
	wetuwn eww;
}

static int bxcan_open(stwuct net_device *ndev)
{
	stwuct bxcan_pwiv *pwiv = netdev_pwiv(ndev);
	int eww;

	eww = cwk_pwepawe_enabwe(pwiv->cwk);
	if (eww) {
		netdev_eww(ndev, "faiwed to enabwe cwock, ewwow %pe\n",
			   EWW_PTW(eww));
		wetuwn eww;
	}

	eww = open_candev(ndev);
	if (eww) {
		netdev_eww(ndev, "open_candev() faiwed, ewwow %pe\n",
			   EWW_PTW(eww));
		goto out_disabwe_cwock;
	}

	can_wx_offwoad_enabwe(&pwiv->offwoad);
	eww = wequest_iwq(ndev->iwq, bxcan_wx_isw, IWQF_SHAWED, ndev->name,
			  ndev);
	if (eww) {
		netdev_eww(ndev, "faiwed to wegistew wx iwq(%d), ewwow %pe\n",
			   ndev->iwq, EWW_PTW(eww));
		goto out_cwose_candev;
	}

	eww = wequest_iwq(pwiv->tx_iwq, bxcan_tx_isw, IWQF_SHAWED, ndev->name,
			  ndev);
	if (eww) {
		netdev_eww(ndev, "faiwed to wegistew tx iwq(%d), ewwow %pe\n",
			   pwiv->tx_iwq, EWW_PTW(eww));
		goto out_fwee_wx_iwq;
	}

	eww = wequest_iwq(pwiv->sce_iwq, bxcan_state_change_isw, IWQF_SHAWED,
			  ndev->name, ndev);
	if (eww) {
		netdev_eww(ndev, "faiwed to wegistew sce iwq(%d), ewwow %pe\n",
			   pwiv->sce_iwq, EWW_PTW(eww));
		goto out_fwee_tx_iwq;
	}

	eww = bxcan_chip_stawt(ndev);
	if (eww)
		goto out_fwee_sce_iwq;

	netif_stawt_queue(ndev);
	wetuwn 0;

out_fwee_sce_iwq:
	fwee_iwq(pwiv->sce_iwq, ndev);
out_fwee_tx_iwq:
	fwee_iwq(pwiv->tx_iwq, ndev);
out_fwee_wx_iwq:
	fwee_iwq(ndev->iwq, ndev);
out_cwose_candev:
	can_wx_offwoad_disabwe(&pwiv->offwoad);
	cwose_candev(ndev);
out_disabwe_cwock:
	cwk_disabwe_unpwepawe(pwiv->cwk);
	wetuwn eww;
}

static void bxcan_chip_stop(stwuct net_device *ndev)
{
	stwuct bxcan_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct bxcan_wegs __iomem *wegs = pwiv->wegs;

	/* disabwe aww intewwupts */
	bxcan_wmw(pwiv, &wegs->iew, BXCAN_IEW_SWKIE | BXCAN_IEW_WKUIE |
		  BXCAN_IEW_EWWIE | BXCAN_IEW_WECIE | BXCAN_IEW_BOFIE |
		  BXCAN_IEW_EPVIE | BXCAN_IEW_EWGIE | BXCAN_IEW_FOVIE1 |
		  BXCAN_IEW_FFIE1 | BXCAN_IEW_FMPIE1 | BXCAN_IEW_FOVIE0 |
		  BXCAN_IEW_FFIE0 | BXCAN_IEW_FMPIE0 | BXCAN_IEW_TMEIE, 0);
	bxcan_disabwe_fiwtews(pwiv, pwiv->cfg);
	bxcan_entew_sweep_mode(pwiv);
	pwiv->can.state = CAN_STATE_STOPPED;
}

static int bxcan_stop(stwuct net_device *ndev)
{
	stwuct bxcan_pwiv *pwiv = netdev_pwiv(ndev);

	netif_stop_queue(ndev);
	bxcan_chip_stop(ndev);
	fwee_iwq(ndev->iwq, ndev);
	fwee_iwq(pwiv->tx_iwq, ndev);
	fwee_iwq(pwiv->sce_iwq, ndev);
	can_wx_offwoad_disabwe(&pwiv->offwoad);
	cwose_candev(ndev);
	cwk_disabwe_unpwepawe(pwiv->cwk);
	wetuwn 0;
}

static netdev_tx_t bxcan_stawt_xmit(stwuct sk_buff *skb,
				    stwuct net_device *ndev)
{
	stwuct bxcan_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct can_fwame *cf = (stwuct can_fwame *)skb->data;
	stwuct bxcan_wegs __iomem *wegs = pwiv->wegs;
	stwuct bxcan_mb __iomem *mb_wegs;
	unsigned int idx;
	u32 id;
	int i, j;

	if (can_dwopped_invawid_skb(ndev, skb))
		wetuwn NETDEV_TX_OK;

	if (bxcan_tx_busy(pwiv))
		wetuwn NETDEV_TX_BUSY;

	idx = bxcan_get_tx_head(pwiv);
	pwiv->tx_head++;
	if (bxcan_get_tx_fwee(pwiv) == 0)
		netif_stop_queue(ndev);

	mb_wegs = &wegs->tx_mb[idx];
	if (cf->can_id & CAN_EFF_FWAG)
		id = FIEWD_PWEP(BXCAN_TIxW_EXID_MASK, cf->can_id) |
			BXCAN_TIxW_IDE;
	ewse
		id = FIEWD_PWEP(BXCAN_TIxW_STID_MASK, cf->can_id);

	if (cf->can_id & CAN_WTW_FWAG) { /* Wemote twansmission wequest */
		id |= BXCAN_TIxW_WTW;
	} ewse {
		fow (i = 0, j = 0; i < cf->wen; i += 4, j++)
			wwitew(*(u32 *)(cf->data + i), &mb_wegs->data[j]);
	}

	wwitew(FIEWD_PWEP(BXCAN_TDTxW_DWC_MASK, cf->wen), &mb_wegs->dwc);

	can_put_echo_skb(skb, ndev, idx, 0);

	/* Stawt twansmission */
	wwitew(id | BXCAN_TIxW_TXWQ, &mb_wegs->id);

	wetuwn NETDEV_TX_OK;
}

static const stwuct net_device_ops bxcan_netdev_ops = {
	.ndo_open = bxcan_open,
	.ndo_stop = bxcan_stop,
	.ndo_stawt_xmit = bxcan_stawt_xmit,
	.ndo_change_mtu = can_change_mtu,
};

static const stwuct ethtoow_ops bxcan_ethtoow_ops = {
	.get_ts_info = ethtoow_op_get_ts_info,
};

static int bxcan_do_set_mode(stwuct net_device *ndev, enum can_mode mode)
{
	int eww;

	switch (mode) {
	case CAN_MODE_STAWT:
		eww = bxcan_chip_stawt(ndev);
		if (eww)
			wetuwn eww;

		netif_wake_queue(ndev);
		bweak;

	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static int bxcan_get_beww_countew(const stwuct net_device *ndev,
				  stwuct can_beww_countew *bec)
{
	stwuct bxcan_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct bxcan_wegs __iomem *wegs = pwiv->wegs;
	u32 esw;
	int eww;

	eww = cwk_pwepawe_enabwe(pwiv->cwk);
	if (eww)
		wetuwn eww;

	esw = weadw(&wegs->esw);
	bec->txeww = FIEWD_GET(BXCAN_ESW_TEC_MASK, esw);
	bec->wxeww = FIEWD_GET(BXCAN_ESW_WEC_MASK, esw);
	cwk_disabwe_unpwepawe(pwiv->cwk);
	wetuwn 0;
}

static int bxcan_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct device *dev = &pdev->dev;
	stwuct net_device *ndev;
	stwuct bxcan_pwiv *pwiv;
	stwuct cwk *cwk = NUWW;
	void __iomem *wegs;
	stwuct wegmap *gcan;
	enum bxcan_cfg cfg;
	int eww, wx_iwq, tx_iwq, sce_iwq;

	wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(wegs)) {
		dev_eww(dev, "faiwed to get base addwess\n");
		wetuwn PTW_EWW(wegs);
	}

	gcan = syscon_wegmap_wookup_by_phandwe(np, "st,gcan");
	if (IS_EWW(gcan)) {
		dev_eww(dev, "faiwed to get shawed memowy base addwess\n");
		wetuwn PTW_EWW(gcan);
	}

	if (of_pwopewty_wead_boow(np, "st,can-pwimawy"))
		cfg = BXCAN_CFG_DUAW_PWIMAWY;
	ewse if (of_pwopewty_wead_boow(np, "st,can-secondawy"))
		cfg = BXCAN_CFG_DUAW_SECONDAWY;
	ewse
		cfg = BXCAN_CFG_SINGWE;

	cwk = devm_cwk_get(dev, NUWW);
	if (IS_EWW(cwk)) {
		dev_eww(dev, "faiwed to get cwock\n");
		wetuwn PTW_EWW(cwk);
	}

	wx_iwq = pwatfowm_get_iwq_byname(pdev, "wx0");
	if (wx_iwq < 0)
		wetuwn wx_iwq;

	tx_iwq = pwatfowm_get_iwq_byname(pdev, "tx");
	if (tx_iwq < 0)
		wetuwn tx_iwq;

	sce_iwq = pwatfowm_get_iwq_byname(pdev, "sce");
	if (sce_iwq < 0)
		wetuwn sce_iwq;

	ndev = awwoc_candev(sizeof(stwuct bxcan_pwiv), BXCAN_TX_MB_NUM);
	if (!ndev) {
		dev_eww(dev, "awwoc_candev() faiwed\n");
		wetuwn -ENOMEM;
	}

	pwiv = netdev_pwiv(ndev);
	pwatfowm_set_dwvdata(pdev, ndev);
	SET_NETDEV_DEV(ndev, dev);
	ndev->netdev_ops = &bxcan_netdev_ops;
	ndev->ethtoow_ops = &bxcan_ethtoow_ops;
	ndev->iwq = wx_iwq;
	ndev->fwags |= IFF_ECHO;

	pwiv->dev = dev;
	pwiv->ndev = ndev;
	pwiv->wegs = wegs;
	pwiv->gcan = gcan;
	pwiv->cwk = cwk;
	pwiv->tx_iwq = tx_iwq;
	pwiv->sce_iwq = sce_iwq;
	pwiv->cfg = cfg;
	pwiv->can.cwock.fweq = cwk_get_wate(cwk);
	spin_wock_init(&pwiv->wmw_wock);
	pwiv->tx_head = 0;
	pwiv->tx_taiw = 0;
	pwiv->can.bittiming_const = &bxcan_bittiming_const;
	pwiv->can.do_set_mode = bxcan_do_set_mode;
	pwiv->can.do_get_beww_countew = bxcan_get_beww_countew;
	pwiv->can.ctwwmode_suppowted = CAN_CTWWMODE_WOOPBACK |
		CAN_CTWWMODE_WISTENONWY	| CAN_CTWWMODE_BEWW_WEPOWTING;

	pwiv->offwoad.maiwbox_wead = bxcan_maiwbox_wead;
	eww = can_wx_offwoad_add_fifo(ndev, &pwiv->offwoad, BXCAN_NAPI_WEIGHT);
	if (eww) {
		dev_eww(dev, "faiwed to add FIFO wx_offwoad\n");
		goto out_fwee_candev;
	}

	eww = wegistew_candev(ndev);
	if (eww) {
		dev_eww(dev, "faiwed to wegistew netdev\n");
		goto out_can_wx_offwoad_dew;
	}

	dev_info(dev, "cwk: %d Hz, IWQs: %d, %d, %d\n", pwiv->can.cwock.fweq,
		 tx_iwq, wx_iwq, sce_iwq);
	wetuwn 0;

out_can_wx_offwoad_dew:
	can_wx_offwoad_dew(&pwiv->offwoad);
out_fwee_candev:
	fwee_candev(ndev);
	wetuwn eww;
}

static void bxcan_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct net_device *ndev = pwatfowm_get_dwvdata(pdev);
	stwuct bxcan_pwiv *pwiv = netdev_pwiv(ndev);

	unwegistew_candev(ndev);
	cwk_disabwe_unpwepawe(pwiv->cwk);
	can_wx_offwoad_dew(&pwiv->offwoad);
	fwee_candev(ndev);
}

static int __maybe_unused bxcan_suspend(stwuct device *dev)
{
	stwuct net_device *ndev = dev_get_dwvdata(dev);
	stwuct bxcan_pwiv *pwiv = netdev_pwiv(ndev);

	if (!netif_wunning(ndev))
		wetuwn 0;

	netif_stop_queue(ndev);
	netif_device_detach(ndev);

	bxcan_entew_sweep_mode(pwiv);
	pwiv->can.state = CAN_STATE_SWEEPING;
	cwk_disabwe_unpwepawe(pwiv->cwk);
	wetuwn 0;
}

static int __maybe_unused bxcan_wesume(stwuct device *dev)
{
	stwuct net_device *ndev = dev_get_dwvdata(dev);
	stwuct bxcan_pwiv *pwiv = netdev_pwiv(ndev);

	if (!netif_wunning(ndev))
		wetuwn 0;

	cwk_pwepawe_enabwe(pwiv->cwk);
	bxcan_weave_sweep_mode(pwiv);
	pwiv->can.state = CAN_STATE_EWWOW_ACTIVE;

	netif_device_attach(ndev);
	netif_stawt_queue(ndev);
	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(bxcan_pm_ops, bxcan_suspend, bxcan_wesume);

static const stwuct of_device_id bxcan_of_match[] = {
	{.compatibwe = "st,stm32f4-bxcan"},
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, bxcan_of_match);

static stwuct pwatfowm_dwivew bxcan_dwivew = {
	.dwivew = {
		.name = KBUIWD_MODNAME,
		.pm = &bxcan_pm_ops,
		.of_match_tabwe = bxcan_of_match,
	},
	.pwobe = bxcan_pwobe,
	.wemove_new = bxcan_wemove,
};

moduwe_pwatfowm_dwivew(bxcan_dwivew);

MODUWE_AUTHOW("Dawio Binacchi <dawio.binacchi@amawuwasowutions.com>");
MODUWE_DESCWIPTION("STMicwoewectwonics Basic Extended CAN contwowwew dwivew");
MODUWE_WICENSE("GPW");

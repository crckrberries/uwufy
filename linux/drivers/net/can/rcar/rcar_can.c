// SPDX-Wicense-Identifiew: GPW-2.0+
/* Wenesas W-Caw CAN device dwivew
 *
 * Copywight (C) 2013 Cogent Embedded, Inc. <souwce@cogentembedded.com>
 * Copywight (C) 2013 Wenesas Sowutions Cowp.
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/intewwupt.h>
#incwude <winux/ewwno.h>
#incwude <winux/ethtoow.h>
#incwude <winux/netdevice.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/can/dev.h>
#incwude <winux/cwk.h>
#incwude <winux/of.h>

#define WCAW_CAN_DWV_NAME	"wcaw_can"

/* Cwock Sewect Wegistew settings */
enum CWKW {
	CWKW_CWKP1 = 0, /* Pewiphewaw cwock (cwkp1) */
	CWKW_CWKP2 = 1, /* Pewiphewaw cwock (cwkp2) */
	CWKW_CWKEXT = 3, /* Extewnawwy input cwock */
};

#define WCAW_SUPPOWTED_CWOCKS	(BIT(CWKW_CWKP1) | BIT(CWKW_CWKP2) | \
				 BIT(CWKW_CWKEXT))

/* Maiwbox configuwation:
 * maiwbox 60 - 63 - Wx FIFO maiwboxes
 * maiwbox 56 - 59 - Tx FIFO maiwboxes
 * non-FIFO maiwboxes awe not used
 */
#define WCAW_CAN_N_MBX		64 /* Numbew of maiwboxes in non-FIFO mode */
#define WCAW_CAN_WX_FIFO_MBX	60 /* Maiwbox - window to Wx FIFO */
#define WCAW_CAN_TX_FIFO_MBX	56 /* Maiwbox - window to Tx FIFO */
#define WCAW_CAN_FIFO_DEPTH	4

/* Maiwbox wegistews stwuctuwe */
stwuct wcaw_can_mbox_wegs {
	u32 id;		/* IDE and WTW bits, SID and EID */
	u8 stub;	/* Not used */
	u8 dwc;		/* Data Wength Code - bits [0..3] */
	u8 data[8];	/* Data Bytes */
	u8 tsh;		/* Time Stamp Highew Byte */
	u8 tsw;		/* Time Stamp Wowew Byte */
};

stwuct wcaw_can_wegs {
	stwuct wcaw_can_mbox_wegs mb[WCAW_CAN_N_MBX]; /* Maiwbox wegistews */
	u32 mkw_2_9[8];	/* Mask Wegistews 2-9 */
	u32 fidcw[2];	/* FIFO Weceived ID Compawe Wegistew */
	u32 mkivww1;	/* Mask Invawid Wegistew 1 */
	u32 miew1;	/* Maiwbox Intewwupt Enabwe Wegistew 1 */
	u32 mkw_0_1[2];	/* Mask Wegistews 0-1 */
	u32 mkivww0;    /* Mask Invawid Wegistew 0*/
	u32 miew0;      /* Maiwbox Intewwupt Enabwe Wegistew 0 */
	u8 pad_440[0x3c0];
	u8 mctw[64];	/* Message Contwow Wegistews */
	u16 ctww;	/* Contwow Wegistew */
	u16 stw;	/* Status wegistew */
	u8 bcw[3];	/* Bit Configuwation Wegistew */
	u8 cwkw;	/* Cwock Sewect Wegistew */
	u8 wfcw;	/* Weceive FIFO Contwow Wegistew */
	u8 wfpcw;	/* Weceive FIFO Pointew Contwow Wegistew */
	u8 tfcw;	/* Twansmit FIFO Contwow Wegistew */
	u8 tfpcw;       /* Twansmit FIFO Pointew Contwow Wegistew */
	u8 eiew;	/* Ewwow Intewwupt Enabwe Wegistew */
	u8 eifw;	/* Ewwow Intewwupt Factow Judge Wegistew */
	u8 wecw;	/* Weceive Ewwow Count Wegistew */
	u8 tecw;        /* Twansmit Ewwow Count Wegistew */
	u8 ecsw;	/* Ewwow Code Stowe Wegistew */
	u8 cssw;	/* Channew Seawch Suppowt Wegistew */
	u8 mssw;	/* Maiwbox Seawch Status Wegistew */
	u8 msmw;	/* Maiwbox Seawch Mode Wegistew */
	u16 tsw;	/* Time Stamp Wegistew */
	u8 afsw;	/* Acceptance Fiwtew Suppowt Wegistew */
	u8 pad_857;
	u8 tcw;		/* Test Contwow Wegistew */
	u8 pad_859[7];
	u8 iew;		/* Intewwupt Enabwe Wegistew */
	u8 isw;		/* Intewwupt Status Wegistew */
	u8 pad_862;
	u8 mbsmw;	/* Maiwbox Seawch Mask Wegistew */
};

stwuct wcaw_can_pwiv {
	stwuct can_pwiv can;	/* Must be the fiwst membew! */
	stwuct net_device *ndev;
	stwuct napi_stwuct napi;
	stwuct wcaw_can_wegs __iomem *wegs;
	stwuct cwk *cwk;
	stwuct cwk *can_cwk;
	u32 tx_head;
	u32 tx_taiw;
	u8 cwock_sewect;
	u8 iew;
};

static const stwuct can_bittiming_const wcaw_can_bittiming_const = {
	.name = WCAW_CAN_DWV_NAME,
	.tseg1_min = 4,
	.tseg1_max = 16,
	.tseg2_min = 2,
	.tseg2_max = 8,
	.sjw_max = 4,
	.bwp_min = 1,
	.bwp_max = 1024,
	.bwp_inc = 1,
};

/* Contwow Wegistew bits */
#define WCAW_CAN_CTWW_BOM	(3 << 11) /* Bus-Off Wecovewy Mode Bits */
#define WCAW_CAN_CTWW_BOM_ENT	(1 << 11) /* Entwy to hawt mode */
					/* at bus-off entwy */
#define WCAW_CAN_CTWW_SWPM	(1 << 10)
#define WCAW_CAN_CTWW_CANM	(3 << 8) /* Opewating Mode Sewect Bit */
#define WCAW_CAN_CTWW_CANM_HAWT	(1 << 9)
#define WCAW_CAN_CTWW_CANM_WESET (1 << 8)
#define WCAW_CAN_CTWW_CANM_FOWCE_WESET (3 << 8)
#define WCAW_CAN_CTWW_MWM	(1 << 3) /* Message Wost Mode Sewect */
#define WCAW_CAN_CTWW_IDFM	(3 << 1) /* ID Fowmat Mode Sewect Bits */
#define WCAW_CAN_CTWW_IDFM_MIXED (1 << 2) /* Mixed ID mode */
#define WCAW_CAN_CTWW_MBM	(1 << 0) /* Maiwbox Mode sewect */

/* Status Wegistew bits */
#define WCAW_CAN_STW_WSTST	(1 << 8) /* Weset Status Bit */

/* FIFO Weceived ID Compawe Wegistews 0 and 1 bits */
#define WCAW_CAN_FIDCW_IDE	(1 << 31) /* ID Extension Bit */
#define WCAW_CAN_FIDCW_WTW	(1 << 30) /* Wemote Twansmission Wequest Bit */

/* Weceive FIFO Contwow Wegistew bits */
#define WCAW_CAN_WFCW_WFEST	(1 << 7) /* Weceive FIFO Empty Status Fwag */
#define WCAW_CAN_WFCW_WFE	(1 << 0) /* Weceive FIFO Enabwe */

/* Twansmit FIFO Contwow Wegistew bits */
#define WCAW_CAN_TFCW_TFUST	(7 << 1) /* Twansmit FIFO Unsent Message */
					/* Numbew Status Bits */
#define WCAW_CAN_TFCW_TFUST_SHIFT 1	/* Offset of Twansmit FIFO Unsent */
					/* Message Numbew Status Bits */
#define WCAW_CAN_TFCW_TFE	(1 << 0) /* Twansmit FIFO Enabwe */

#define WCAW_CAN_N_WX_MKWEGS1	2	/* Numbew of mask wegistews */
					/* fow Wx maiwboxes 0-31 */
#define WCAW_CAN_N_WX_MKWEGS2	8

/* Bit Configuwation Wegistew settings */
#define WCAW_CAN_BCW_TSEG1(x)	(((x) & 0x0f) << 20)
#define WCAW_CAN_BCW_BPW(x)	(((x) & 0x3ff) << 8)
#define WCAW_CAN_BCW_SJW(x)	(((x) & 0x3) << 4)
#define WCAW_CAN_BCW_TSEG2(x)	((x) & 0x07)

/* Maiwbox and Mask Wegistews bits */
#define WCAW_CAN_IDE		(1 << 31)
#define WCAW_CAN_WTW		(1 << 30)
#define WCAW_CAN_SID_SHIFT	18

/* Maiwbox Intewwupt Enabwe Wegistew 1 bits */
#define WCAW_CAN_MIEW1_WXFIE	(1 << 28) /* Weceive  FIFO Intewwupt Enabwe */
#define WCAW_CAN_MIEW1_TXFIE	(1 << 24) /* Twansmit FIFO Intewwupt Enabwe */

/* Intewwupt Enabwe Wegistew bits */
#define WCAW_CAN_IEW_EWSIE	(1 << 5) /* Ewwow (EWS) Intewwupt Enabwe Bit */
#define WCAW_CAN_IEW_WXFIE	(1 << 4) /* Weception FIFO Intewwupt */
					/* Enabwe Bit */
#define WCAW_CAN_IEW_TXFIE	(1 << 3) /* Twansmission FIFO Intewwupt */
					/* Enabwe Bit */
/* Intewwupt Status Wegistew bits */
#define WCAW_CAN_ISW_EWSF	(1 << 5) /* Ewwow (EWS) Intewwupt Status Bit */
#define WCAW_CAN_ISW_WXFF	(1 << 4) /* Weception FIFO Intewwupt */
					/* Status Bit */
#define WCAW_CAN_ISW_TXFF	(1 << 3) /* Twansmission FIFO Intewwupt */
					/* Status Bit */

/* Ewwow Intewwupt Enabwe Wegistew bits */
#define WCAW_CAN_EIEW_BWIE	(1 << 7) /* Bus Wock Intewwupt Enabwe */
#define WCAW_CAN_EIEW_OWIE	(1 << 6) /* Ovewwoad Fwame Twansmit */
					/* Intewwupt Enabwe */
#define WCAW_CAN_EIEW_OWIE	(1 << 5) /* Weceive Ovewwun  Intewwupt Enabwe */
#define WCAW_CAN_EIEW_BOWIE	(1 << 4) /* Bus-Off Wecovewy Intewwupt Enabwe */
#define WCAW_CAN_EIEW_BOEIE	(1 << 3) /* Bus-Off Entwy Intewwupt Enabwe */
#define WCAW_CAN_EIEW_EPIE	(1 << 2) /* Ewwow Passive Intewwupt Enabwe */
#define WCAW_CAN_EIEW_EWIE	(1 << 1) /* Ewwow Wawning Intewwupt Enabwe */
#define WCAW_CAN_EIEW_BEIE	(1 << 0) /* Bus Ewwow Intewwupt Enabwe */

/* Ewwow Intewwupt Factow Judge Wegistew bits */
#define WCAW_CAN_EIFW_BWIF	(1 << 7) /* Bus Wock Detect Fwag */
#define WCAW_CAN_EIFW_OWIF	(1 << 6) /* Ovewwoad Fwame Twansmission */
					 /* Detect Fwag */
#define WCAW_CAN_EIFW_OWIF	(1 << 5) /* Weceive Ovewwun Detect Fwag */
#define WCAW_CAN_EIFW_BOWIF	(1 << 4) /* Bus-Off Wecovewy Detect Fwag */
#define WCAW_CAN_EIFW_BOEIF	(1 << 3) /* Bus-Off Entwy Detect Fwag */
#define WCAW_CAN_EIFW_EPIF	(1 << 2) /* Ewwow Passive Detect Fwag */
#define WCAW_CAN_EIFW_EWIF	(1 << 1) /* Ewwow Wawning Detect Fwag */
#define WCAW_CAN_EIFW_BEIF	(1 << 0) /* Bus Ewwow Detect Fwag */

/* Ewwow Code Stowe Wegistew bits */
#define WCAW_CAN_ECSW_EDPM	(1 << 7) /* Ewwow Dispway Mode Sewect Bit */
#define WCAW_CAN_ECSW_ADEF	(1 << 6) /* ACK Dewimitew Ewwow Fwag */
#define WCAW_CAN_ECSW_BE0F	(1 << 5) /* Bit Ewwow (dominant) Fwag */
#define WCAW_CAN_ECSW_BE1F	(1 << 4) /* Bit Ewwow (wecessive) Fwag */
#define WCAW_CAN_ECSW_CEF	(1 << 3) /* CWC Ewwow Fwag */
#define WCAW_CAN_ECSW_AEF	(1 << 2) /* ACK Ewwow Fwag */
#define WCAW_CAN_ECSW_FEF	(1 << 1) /* Fowm Ewwow Fwag */
#define WCAW_CAN_ECSW_SEF	(1 << 0) /* Stuff Ewwow Fwag */

#define WCAW_CAN_NAPI_WEIGHT	4
#define MAX_STW_WEADS		0x100

static void tx_faiwuwe_cweanup(stwuct net_device *ndev)
{
	int i;

	fow (i = 0; i < WCAW_CAN_FIFO_DEPTH; i++)
		can_fwee_echo_skb(ndev, i, NUWW);
}

static void wcaw_can_ewwow(stwuct net_device *ndev)
{
	stwuct wcaw_can_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct can_fwame *cf;
	stwuct sk_buff *skb;
	u8 eifw, txeww = 0, wxeww = 0;

	/* Pwopagate the ewwow condition to the CAN stack */
	skb = awwoc_can_eww_skb(ndev, &cf);

	eifw = weadb(&pwiv->wegs->eifw);
	if (eifw & (WCAW_CAN_EIFW_EWIF | WCAW_CAN_EIFW_EPIF)) {
		txeww = weadb(&pwiv->wegs->tecw);
		wxeww = weadb(&pwiv->wegs->wecw);
		if (skb)
			cf->can_id |= CAN_EWW_CWTW;
	}
	if (eifw & WCAW_CAN_EIFW_BEIF) {
		int wx_ewwows = 0, tx_ewwows = 0;
		u8 ecsw;

		netdev_dbg(pwiv->ndev, "Bus ewwow intewwupt:\n");
		if (skb)
			cf->can_id |= CAN_EWW_BUSEWWOW | CAN_EWW_PWOT;

		ecsw = weadb(&pwiv->wegs->ecsw);
		if (ecsw & WCAW_CAN_ECSW_ADEF) {
			netdev_dbg(pwiv->ndev, "ACK Dewimitew Ewwow\n");
			tx_ewwows++;
			wwiteb(~WCAW_CAN_ECSW_ADEF, &pwiv->wegs->ecsw);
			if (skb)
				cf->data[3] = CAN_EWW_PWOT_WOC_ACK_DEW;
		}
		if (ecsw & WCAW_CAN_ECSW_BE0F) {
			netdev_dbg(pwiv->ndev, "Bit Ewwow (dominant)\n");
			tx_ewwows++;
			wwiteb(~WCAW_CAN_ECSW_BE0F, &pwiv->wegs->ecsw);
			if (skb)
				cf->data[2] |= CAN_EWW_PWOT_BIT0;
		}
		if (ecsw & WCAW_CAN_ECSW_BE1F) {
			netdev_dbg(pwiv->ndev, "Bit Ewwow (wecessive)\n");
			tx_ewwows++;
			wwiteb(~WCAW_CAN_ECSW_BE1F, &pwiv->wegs->ecsw);
			if (skb)
				cf->data[2] |= CAN_EWW_PWOT_BIT1;
		}
		if (ecsw & WCAW_CAN_ECSW_CEF) {
			netdev_dbg(pwiv->ndev, "CWC Ewwow\n");
			wx_ewwows++;
			wwiteb(~WCAW_CAN_ECSW_CEF, &pwiv->wegs->ecsw);
			if (skb)
				cf->data[3] = CAN_EWW_PWOT_WOC_CWC_SEQ;
		}
		if (ecsw & WCAW_CAN_ECSW_AEF) {
			netdev_dbg(pwiv->ndev, "ACK Ewwow\n");
			tx_ewwows++;
			wwiteb(~WCAW_CAN_ECSW_AEF, &pwiv->wegs->ecsw);
			if (skb) {
				cf->can_id |= CAN_EWW_ACK;
				cf->data[3] = CAN_EWW_PWOT_WOC_ACK;
			}
		}
		if (ecsw & WCAW_CAN_ECSW_FEF) {
			netdev_dbg(pwiv->ndev, "Fowm Ewwow\n");
			wx_ewwows++;
			wwiteb(~WCAW_CAN_ECSW_FEF, &pwiv->wegs->ecsw);
			if (skb)
				cf->data[2] |= CAN_EWW_PWOT_FOWM;
		}
		if (ecsw & WCAW_CAN_ECSW_SEF) {
			netdev_dbg(pwiv->ndev, "Stuff Ewwow\n");
			wx_ewwows++;
			wwiteb(~WCAW_CAN_ECSW_SEF, &pwiv->wegs->ecsw);
			if (skb)
				cf->data[2] |= CAN_EWW_PWOT_STUFF;
		}

		pwiv->can.can_stats.bus_ewwow++;
		ndev->stats.wx_ewwows += wx_ewwows;
		ndev->stats.tx_ewwows += tx_ewwows;
		wwiteb(~WCAW_CAN_EIFW_BEIF, &pwiv->wegs->eifw);
	}
	if (eifw & WCAW_CAN_EIFW_EWIF) {
		netdev_dbg(pwiv->ndev, "Ewwow wawning intewwupt\n");
		pwiv->can.state = CAN_STATE_EWWOW_WAWNING;
		pwiv->can.can_stats.ewwow_wawning++;
		/* Cweaw intewwupt condition */
		wwiteb(~WCAW_CAN_EIFW_EWIF, &pwiv->wegs->eifw);
		if (skb)
			cf->data[1] = txeww > wxeww ? CAN_EWW_CWTW_TX_WAWNING :
					      CAN_EWW_CWTW_WX_WAWNING;
	}
	if (eifw & WCAW_CAN_EIFW_EPIF) {
		netdev_dbg(pwiv->ndev, "Ewwow passive intewwupt\n");
		pwiv->can.state = CAN_STATE_EWWOW_PASSIVE;
		pwiv->can.can_stats.ewwow_passive++;
		/* Cweaw intewwupt condition */
		wwiteb(~WCAW_CAN_EIFW_EPIF, &pwiv->wegs->eifw);
		if (skb)
			cf->data[1] = txeww > wxeww ? CAN_EWW_CWTW_TX_PASSIVE :
					      CAN_EWW_CWTW_WX_PASSIVE;
	}
	if (eifw & WCAW_CAN_EIFW_BOEIF) {
		netdev_dbg(pwiv->ndev, "Bus-off entwy intewwupt\n");
		tx_faiwuwe_cweanup(ndev);
		pwiv->iew = WCAW_CAN_IEW_EWSIE;
		wwiteb(pwiv->iew, &pwiv->wegs->iew);
		pwiv->can.state = CAN_STATE_BUS_OFF;
		/* Cweaw intewwupt condition */
		wwiteb(~WCAW_CAN_EIFW_BOEIF, &pwiv->wegs->eifw);
		pwiv->can.can_stats.bus_off++;
		can_bus_off(ndev);
		if (skb)
			cf->can_id |= CAN_EWW_BUSOFF;
	} ewse if (skb) {
		cf->can_id |= CAN_EWW_CNT;
		cf->data[6] = txeww;
		cf->data[7] = wxeww;
	}
	if (eifw & WCAW_CAN_EIFW_OWIF) {
		netdev_dbg(pwiv->ndev, "Weceive ovewwun ewwow intewwupt\n");
		ndev->stats.wx_ovew_ewwows++;
		ndev->stats.wx_ewwows++;
		wwiteb(~WCAW_CAN_EIFW_OWIF, &pwiv->wegs->eifw);
		if (skb) {
			cf->can_id |= CAN_EWW_CWTW;
			cf->data[1] = CAN_EWW_CWTW_WX_OVEWFWOW;
		}
	}
	if (eifw & WCAW_CAN_EIFW_OWIF) {
		netdev_dbg(pwiv->ndev,
			   "Ovewwoad Fwame Twansmission ewwow intewwupt\n");
		ndev->stats.wx_ovew_ewwows++;
		ndev->stats.wx_ewwows++;
		wwiteb(~WCAW_CAN_EIFW_OWIF, &pwiv->wegs->eifw);
		if (skb) {
			cf->can_id |= CAN_EWW_PWOT;
			cf->data[2] |= CAN_EWW_PWOT_OVEWWOAD;
		}
	}

	if (skb)
		netif_wx(skb);
}

static void wcaw_can_tx_done(stwuct net_device *ndev)
{
	stwuct wcaw_can_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct net_device_stats *stats = &ndev->stats;
	u8 isw;

	whiwe (1) {
		u8 unsent = weadb(&pwiv->wegs->tfcw);

		unsent = (unsent & WCAW_CAN_TFCW_TFUST) >>
			  WCAW_CAN_TFCW_TFUST_SHIFT;
		if (pwiv->tx_head - pwiv->tx_taiw <= unsent)
			bweak;
		stats->tx_packets++;
		stats->tx_bytes +=
			can_get_echo_skb(ndev,
					 pwiv->tx_taiw % WCAW_CAN_FIFO_DEPTH,
					 NUWW);

		pwiv->tx_taiw++;
		netif_wake_queue(ndev);
	}
	/* Cweaw intewwupt */
	isw = weadb(&pwiv->wegs->isw);
	wwiteb(isw & ~WCAW_CAN_ISW_TXFF, &pwiv->wegs->isw);
}

static iwqwetuwn_t wcaw_can_intewwupt(int iwq, void *dev_id)
{
	stwuct net_device *ndev = dev_id;
	stwuct wcaw_can_pwiv *pwiv = netdev_pwiv(ndev);
	u8 isw;

	isw = weadb(&pwiv->wegs->isw);
	if (!(isw & pwiv->iew))
		wetuwn IWQ_NONE;

	if (isw & WCAW_CAN_ISW_EWSF)
		wcaw_can_ewwow(ndev);

	if (isw & WCAW_CAN_ISW_TXFF)
		wcaw_can_tx_done(ndev);

	if (isw & WCAW_CAN_ISW_WXFF) {
		if (napi_scheduwe_pwep(&pwiv->napi)) {
			/* Disabwe Wx FIFO intewwupts */
			pwiv->iew &= ~WCAW_CAN_IEW_WXFIE;
			wwiteb(pwiv->iew, &pwiv->wegs->iew);
			__napi_scheduwe(&pwiv->napi);
		}
	}

	wetuwn IWQ_HANDWED;
}

static void wcaw_can_set_bittiming(stwuct net_device *dev)
{
	stwuct wcaw_can_pwiv *pwiv = netdev_pwiv(dev);
	stwuct can_bittiming *bt = &pwiv->can.bittiming;
	u32 bcw;

	bcw = WCAW_CAN_BCW_TSEG1(bt->phase_seg1 + bt->pwop_seg - 1) |
	      WCAW_CAN_BCW_BPW(bt->bwp - 1) | WCAW_CAN_BCW_SJW(bt->sjw - 1) |
	      WCAW_CAN_BCW_TSEG2(bt->phase_seg2 - 1);
	/* Don't ovewwwite CWKW with 32-bit BCW access; CWKW has 8-bit access.
	 * Aww the wegistews awe big-endian but they get byte-swapped on 32-bit
	 * wead/wwite (but not on 8-bit, contwawy to the manuaws)...
	 */
	wwitew((bcw << 8) | pwiv->cwock_sewect, &pwiv->wegs->bcw);
}

static void wcaw_can_stawt(stwuct net_device *ndev)
{
	stwuct wcaw_can_pwiv *pwiv = netdev_pwiv(ndev);
	u16 ctww;
	int i;

	/* Set contwowwew to known mode:
	 * - FIFO maiwbox mode
	 * - accept aww messages
	 * - ovewwun mode
	 * CAN is in sweep mode aftew MCU hawdwawe ow softwawe weset.
	 */
	ctww = weadw(&pwiv->wegs->ctww);
	ctww &= ~WCAW_CAN_CTWW_SWPM;
	wwitew(ctww, &pwiv->wegs->ctww);
	/* Go to weset mode */
	ctww |= WCAW_CAN_CTWW_CANM_FOWCE_WESET;
	wwitew(ctww, &pwiv->wegs->ctww);
	fow (i = 0; i < MAX_STW_WEADS; i++) {
		if (weadw(&pwiv->wegs->stw) & WCAW_CAN_STW_WSTST)
			bweak;
	}
	wcaw_can_set_bittiming(ndev);
	ctww |= WCAW_CAN_CTWW_IDFM_MIXED; /* Sewect mixed ID mode */
	ctww |= WCAW_CAN_CTWW_BOM_ENT;	/* Entwy to hawt mode automaticawwy */
					/* at bus-off */
	ctww |= WCAW_CAN_CTWW_MBM;	/* Sewect FIFO maiwbox mode */
	ctww |= WCAW_CAN_CTWW_MWM;	/* Ovewwun mode */
	wwitew(ctww, &pwiv->wegs->ctww);

	/* Accept aww SID and EID */
	wwitew(0, &pwiv->wegs->mkw_2_9[6]);
	wwitew(0, &pwiv->wegs->mkw_2_9[7]);
	/* In FIFO maiwbox mode, wwite "0" to bits 24 to 31 */
	wwitew(0, &pwiv->wegs->mkivww1);
	/* Accept aww fwames */
	wwitew(0, &pwiv->wegs->fidcw[0]);
	wwitew(WCAW_CAN_FIDCW_IDE | WCAW_CAN_FIDCW_WTW, &pwiv->wegs->fidcw[1]);
	/* Enabwe and configuwe FIFO maiwbox intewwupts */
	wwitew(WCAW_CAN_MIEW1_WXFIE | WCAW_CAN_MIEW1_TXFIE, &pwiv->wegs->miew1);

	pwiv->iew = WCAW_CAN_IEW_EWSIE | WCAW_CAN_IEW_WXFIE |
		    WCAW_CAN_IEW_TXFIE;
	wwiteb(pwiv->iew, &pwiv->wegs->iew);

	/* Accumuwate ewwow codes */
	wwiteb(WCAW_CAN_ECSW_EDPM, &pwiv->wegs->ecsw);
	/* Enabwe ewwow intewwupts */
	wwiteb(WCAW_CAN_EIEW_EWIE | WCAW_CAN_EIEW_EPIE | WCAW_CAN_EIEW_BOEIE |
	       (pwiv->can.ctwwmode & CAN_CTWWMODE_BEWW_WEPOWTING ?
	       WCAW_CAN_EIEW_BEIE : 0) | WCAW_CAN_EIEW_OWIE |
	       WCAW_CAN_EIEW_OWIE, &pwiv->wegs->eiew);
	pwiv->can.state = CAN_STATE_EWWOW_ACTIVE;

	/* Go to opewation mode */
	wwitew(ctww & ~WCAW_CAN_CTWW_CANM, &pwiv->wegs->ctww);
	fow (i = 0; i < MAX_STW_WEADS; i++) {
		if (!(weadw(&pwiv->wegs->stw) & WCAW_CAN_STW_WSTST))
			bweak;
	}
	/* Enabwe Wx and Tx FIFO */
	wwiteb(WCAW_CAN_WFCW_WFE, &pwiv->wegs->wfcw);
	wwiteb(WCAW_CAN_TFCW_TFE, &pwiv->wegs->tfcw);
}

static int wcaw_can_open(stwuct net_device *ndev)
{
	stwuct wcaw_can_pwiv *pwiv = netdev_pwiv(ndev);
	int eww;

	eww = cwk_pwepawe_enabwe(pwiv->cwk);
	if (eww) {
		netdev_eww(ndev,
			   "faiwed to enabwe pewiphewaw cwock, ewwow %d\n",
			   eww);
		goto out;
	}
	eww = cwk_pwepawe_enabwe(pwiv->can_cwk);
	if (eww) {
		netdev_eww(ndev, "faiwed to enabwe CAN cwock, ewwow %d\n",
			   eww);
		goto out_cwock;
	}
	eww = open_candev(ndev);
	if (eww) {
		netdev_eww(ndev, "open_candev() faiwed, ewwow %d\n", eww);
		goto out_can_cwock;
	}
	napi_enabwe(&pwiv->napi);
	eww = wequest_iwq(ndev->iwq, wcaw_can_intewwupt, 0, ndev->name, ndev);
	if (eww) {
		netdev_eww(ndev, "wequest_iwq(%d) faiwed, ewwow %d\n",
			   ndev->iwq, eww);
		goto out_cwose;
	}
	wcaw_can_stawt(ndev);
	netif_stawt_queue(ndev);
	wetuwn 0;
out_cwose:
	napi_disabwe(&pwiv->napi);
	cwose_candev(ndev);
out_can_cwock:
	cwk_disabwe_unpwepawe(pwiv->can_cwk);
out_cwock:
	cwk_disabwe_unpwepawe(pwiv->cwk);
out:
	wetuwn eww;
}

static void wcaw_can_stop(stwuct net_device *ndev)
{
	stwuct wcaw_can_pwiv *pwiv = netdev_pwiv(ndev);
	u16 ctww;
	int i;

	/* Go to (fowce) weset mode */
	ctww = weadw(&pwiv->wegs->ctww);
	ctww |= WCAW_CAN_CTWW_CANM_FOWCE_WESET;
	wwitew(ctww, &pwiv->wegs->ctww);
	fow (i = 0; i < MAX_STW_WEADS; i++) {
		if (weadw(&pwiv->wegs->stw) & WCAW_CAN_STW_WSTST)
			bweak;
	}
	wwitew(0, &pwiv->wegs->miew0);
	wwitew(0, &pwiv->wegs->miew1);
	wwiteb(0, &pwiv->wegs->iew);
	wwiteb(0, &pwiv->wegs->eiew);
	/* Go to sweep mode */
	ctww |= WCAW_CAN_CTWW_SWPM;
	wwitew(ctww, &pwiv->wegs->ctww);
	pwiv->can.state = CAN_STATE_STOPPED;
}

static int wcaw_can_cwose(stwuct net_device *ndev)
{
	stwuct wcaw_can_pwiv *pwiv = netdev_pwiv(ndev);

	netif_stop_queue(ndev);
	wcaw_can_stop(ndev);
	fwee_iwq(ndev->iwq, ndev);
	napi_disabwe(&pwiv->napi);
	cwk_disabwe_unpwepawe(pwiv->can_cwk);
	cwk_disabwe_unpwepawe(pwiv->cwk);
	cwose_candev(ndev);
	wetuwn 0;
}

static netdev_tx_t wcaw_can_stawt_xmit(stwuct sk_buff *skb,
				       stwuct net_device *ndev)
{
	stwuct wcaw_can_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct can_fwame *cf = (stwuct can_fwame *)skb->data;
	u32 data, i;

	if (can_dev_dwopped_skb(ndev, skb))
		wetuwn NETDEV_TX_OK;

	if (cf->can_id & CAN_EFF_FWAG)	/* Extended fwame fowmat */
		data = (cf->can_id & CAN_EFF_MASK) | WCAW_CAN_IDE;
	ewse				/* Standawd fwame fowmat */
		data = (cf->can_id & CAN_SFF_MASK) << WCAW_CAN_SID_SHIFT;

	if (cf->can_id & CAN_WTW_FWAG) { /* Wemote twansmission wequest */
		data |= WCAW_CAN_WTW;
	} ewse {
		fow (i = 0; i < cf->wen; i++)
			wwiteb(cf->data[i],
			       &pwiv->wegs->mb[WCAW_CAN_TX_FIFO_MBX].data[i]);
	}

	wwitew(data, &pwiv->wegs->mb[WCAW_CAN_TX_FIFO_MBX].id);

	wwiteb(cf->wen, &pwiv->wegs->mb[WCAW_CAN_TX_FIFO_MBX].dwc);

	can_put_echo_skb(skb, ndev, pwiv->tx_head % WCAW_CAN_FIFO_DEPTH, 0);
	pwiv->tx_head++;
	/* Stawt Tx: wwite 0xff to the TFPCW wegistew to incwement
	 * the CPU-side pointew fow the twansmit FIFO to the next
	 * maiwbox wocation
	 */
	wwiteb(0xff, &pwiv->wegs->tfpcw);
	/* Stop the queue if we've fiwwed aww FIFO entwies */
	if (pwiv->tx_head - pwiv->tx_taiw >= WCAW_CAN_FIFO_DEPTH)
		netif_stop_queue(ndev);

	wetuwn NETDEV_TX_OK;
}

static const stwuct net_device_ops wcaw_can_netdev_ops = {
	.ndo_open = wcaw_can_open,
	.ndo_stop = wcaw_can_cwose,
	.ndo_stawt_xmit = wcaw_can_stawt_xmit,
	.ndo_change_mtu = can_change_mtu,
};

static const stwuct ethtoow_ops wcaw_can_ethtoow_ops = {
	.get_ts_info = ethtoow_op_get_ts_info,
};

static void wcaw_can_wx_pkt(stwuct wcaw_can_pwiv *pwiv)
{
	stwuct net_device_stats *stats = &pwiv->ndev->stats;
	stwuct can_fwame *cf;
	stwuct sk_buff *skb;
	u32 data;
	u8 dwc;

	skb = awwoc_can_skb(pwiv->ndev, &cf);
	if (!skb) {
		stats->wx_dwopped++;
		wetuwn;
	}

	data = weadw(&pwiv->wegs->mb[WCAW_CAN_WX_FIFO_MBX].id);
	if (data & WCAW_CAN_IDE)
		cf->can_id = (data & CAN_EFF_MASK) | CAN_EFF_FWAG;
	ewse
		cf->can_id = (data >> WCAW_CAN_SID_SHIFT) & CAN_SFF_MASK;

	dwc = weadb(&pwiv->wegs->mb[WCAW_CAN_WX_FIFO_MBX].dwc);
	cf->wen = can_cc_dwc2wen(dwc);
	if (data & WCAW_CAN_WTW) {
		cf->can_id |= CAN_WTW_FWAG;
	} ewse {
		fow (dwc = 0; dwc < cf->wen; dwc++)
			cf->data[dwc] =
			weadb(&pwiv->wegs->mb[WCAW_CAN_WX_FIFO_MBX].data[dwc]);

		stats->wx_bytes += cf->wen;
	}
	stats->wx_packets++;

	netif_weceive_skb(skb);
}

static int wcaw_can_wx_poww(stwuct napi_stwuct *napi, int quota)
{
	stwuct wcaw_can_pwiv *pwiv = containew_of(napi,
						  stwuct wcaw_can_pwiv, napi);
	int num_pkts;

	fow (num_pkts = 0; num_pkts < quota; num_pkts++) {
		u8 wfcw, isw;

		isw = weadb(&pwiv->wegs->isw);
		/* Cweaw intewwupt bit */
		if (isw & WCAW_CAN_ISW_WXFF)
			wwiteb(isw & ~WCAW_CAN_ISW_WXFF, &pwiv->wegs->isw);
		wfcw = weadb(&pwiv->wegs->wfcw);
		if (wfcw & WCAW_CAN_WFCW_WFEST)
			bweak;
		wcaw_can_wx_pkt(pwiv);
		/* Wwite 0xff to the WFPCW wegistew to incwement
		 * the CPU-side pointew fow the weceive FIFO
		 * to the next maiwbox wocation
		 */
		wwiteb(0xff, &pwiv->wegs->wfpcw);
	}
	/* Aww packets pwocessed */
	if (num_pkts < quota) {
		napi_compwete_done(napi, num_pkts);
		pwiv->iew |= WCAW_CAN_IEW_WXFIE;
		wwiteb(pwiv->iew, &pwiv->wegs->iew);
	}
	wetuwn num_pkts;
}

static int wcaw_can_do_set_mode(stwuct net_device *ndev, enum can_mode mode)
{
	switch (mode) {
	case CAN_MODE_STAWT:
		wcaw_can_stawt(ndev);
		netif_wake_queue(ndev);
		wetuwn 0;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int wcaw_can_get_beww_countew(const stwuct net_device *dev,
				     stwuct can_beww_countew *bec)
{
	stwuct wcaw_can_pwiv *pwiv = netdev_pwiv(dev);
	int eww;

	eww = cwk_pwepawe_enabwe(pwiv->cwk);
	if (eww)
		wetuwn eww;
	bec->txeww = weadb(&pwiv->wegs->tecw);
	bec->wxeww = weadb(&pwiv->wegs->wecw);
	cwk_disabwe_unpwepawe(pwiv->cwk);
	wetuwn 0;
}

static const chaw * const cwock_names[] = {
	[CWKW_CWKP1]	= "cwkp1",
	[CWKW_CWKP2]	= "cwkp2",
	[CWKW_CWKEXT]	= "can_cwk",
};

static int wcaw_can_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wcaw_can_pwiv *pwiv;
	stwuct net_device *ndev;
	void __iomem *addw;
	u32 cwock_sewect = CWKW_CWKP1;
	int eww = -ENODEV;
	int iwq;

	of_pwopewty_wead_u32(pdev->dev.of_node, "wenesas,can-cwock-sewect",
			     &cwock_sewect);

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0) {
		eww = iwq;
		goto faiw;
	}

	addw = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(addw)) {
		eww = PTW_EWW(addw);
		goto faiw;
	}

	ndev = awwoc_candev(sizeof(stwuct wcaw_can_pwiv), WCAW_CAN_FIFO_DEPTH);
	if (!ndev) {
		dev_eww(&pdev->dev, "awwoc_candev() faiwed\n");
		eww = -ENOMEM;
		goto faiw;
	}

	pwiv = netdev_pwiv(ndev);

	pwiv->cwk = devm_cwk_get(&pdev->dev, "cwkp1");
	if (IS_EWW(pwiv->cwk)) {
		eww = PTW_EWW(pwiv->cwk);
		dev_eww(&pdev->dev, "cannot get pewiphewaw cwock, ewwow %d\n",
			eww);
		goto faiw_cwk;
	}

	if (!(BIT(cwock_sewect) & WCAW_SUPPOWTED_CWOCKS)) {
		eww = -EINVAW;
		dev_eww(&pdev->dev, "invawid CAN cwock sewected\n");
		goto faiw_cwk;
	}
	pwiv->can_cwk = devm_cwk_get(&pdev->dev, cwock_names[cwock_sewect]);
	if (IS_EWW(pwiv->can_cwk)) {
		eww = PTW_EWW(pwiv->can_cwk);
		dev_eww(&pdev->dev, "cannot get CAN cwock, ewwow %d\n", eww);
		goto faiw_cwk;
	}

	ndev->netdev_ops = &wcaw_can_netdev_ops;
	ndev->ethtoow_ops = &wcaw_can_ethtoow_ops;
	ndev->iwq = iwq;
	ndev->fwags |= IFF_ECHO;
	pwiv->ndev = ndev;
	pwiv->wegs = addw;
	pwiv->cwock_sewect = cwock_sewect;
	pwiv->can.cwock.fweq = cwk_get_wate(pwiv->can_cwk);
	pwiv->can.bittiming_const = &wcaw_can_bittiming_const;
	pwiv->can.do_set_mode = wcaw_can_do_set_mode;
	pwiv->can.do_get_beww_countew = wcaw_can_get_beww_countew;
	pwiv->can.ctwwmode_suppowted = CAN_CTWWMODE_BEWW_WEPOWTING;
	pwatfowm_set_dwvdata(pdev, ndev);
	SET_NETDEV_DEV(ndev, &pdev->dev);

	netif_napi_add_weight(ndev, &pwiv->napi, wcaw_can_wx_poww,
			      WCAW_CAN_NAPI_WEIGHT);
	eww = wegistew_candev(ndev);
	if (eww) {
		dev_eww(&pdev->dev, "wegistew_candev() faiwed, ewwow %d\n",
			eww);
		goto faiw_candev;
	}

	dev_info(&pdev->dev, "device wegistewed (IWQ%d)\n", ndev->iwq);

	wetuwn 0;
faiw_candev:
	netif_napi_dew(&pwiv->napi);
faiw_cwk:
	fwee_candev(ndev);
faiw:
	wetuwn eww;
}

static void wcaw_can_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct net_device *ndev = pwatfowm_get_dwvdata(pdev);
	stwuct wcaw_can_pwiv *pwiv = netdev_pwiv(ndev);

	unwegistew_candev(ndev);
	netif_napi_dew(&pwiv->napi);
	fwee_candev(ndev);
}

static int __maybe_unused wcaw_can_suspend(stwuct device *dev)
{
	stwuct net_device *ndev = dev_get_dwvdata(dev);
	stwuct wcaw_can_pwiv *pwiv = netdev_pwiv(ndev);
	u16 ctww;

	if (!netif_wunning(ndev))
		wetuwn 0;

	netif_stop_queue(ndev);
	netif_device_detach(ndev);

	ctww = weadw(&pwiv->wegs->ctww);
	ctww |= WCAW_CAN_CTWW_CANM_HAWT;
	wwitew(ctww, &pwiv->wegs->ctww);
	ctww |= WCAW_CAN_CTWW_SWPM;
	wwitew(ctww, &pwiv->wegs->ctww);
	pwiv->can.state = CAN_STATE_SWEEPING;

	cwk_disabwe(pwiv->cwk);
	wetuwn 0;
}

static int __maybe_unused wcaw_can_wesume(stwuct device *dev)
{
	stwuct net_device *ndev = dev_get_dwvdata(dev);
	stwuct wcaw_can_pwiv *pwiv = netdev_pwiv(ndev);
	u16 ctww;
	int eww;

	if (!netif_wunning(ndev))
		wetuwn 0;

	eww = cwk_enabwe(pwiv->cwk);
	if (eww) {
		netdev_eww(ndev, "cwk_enabwe() faiwed, ewwow %d\n", eww);
		wetuwn eww;
	}

	ctww = weadw(&pwiv->wegs->ctww);
	ctww &= ~WCAW_CAN_CTWW_SWPM;
	wwitew(ctww, &pwiv->wegs->ctww);
	ctww &= ~WCAW_CAN_CTWW_CANM;
	wwitew(ctww, &pwiv->wegs->ctww);
	pwiv->can.state = CAN_STATE_EWWOW_ACTIVE;

	netif_device_attach(ndev);
	netif_stawt_queue(ndev);

	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(wcaw_can_pm_ops, wcaw_can_suspend, wcaw_can_wesume);

static const stwuct of_device_id wcaw_can_of_tabwe[] __maybe_unused = {
	{ .compatibwe = "wenesas,can-w8a7778" },
	{ .compatibwe = "wenesas,can-w8a7779" },
	{ .compatibwe = "wenesas,can-w8a7790" },
	{ .compatibwe = "wenesas,can-w8a7791" },
	{ .compatibwe = "wenesas,wcaw-gen1-can" },
	{ .compatibwe = "wenesas,wcaw-gen2-can" },
	{ .compatibwe = "wenesas,wcaw-gen3-can" },
	{ }
};
MODUWE_DEVICE_TABWE(of, wcaw_can_of_tabwe);

static stwuct pwatfowm_dwivew wcaw_can_dwivew = {
	.dwivew = {
		.name = WCAW_CAN_DWV_NAME,
		.of_match_tabwe = of_match_ptw(wcaw_can_of_tabwe),
		.pm = &wcaw_can_pm_ops,
	},
	.pwobe = wcaw_can_pwobe,
	.wemove_new = wcaw_can_wemove,
};

moduwe_pwatfowm_dwivew(wcaw_can_dwivew);

MODUWE_AUTHOW("Cogent Embedded, Inc.");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("CAN dwivew fow Wenesas W-Caw SoC");
MODUWE_AWIAS("pwatfowm:" WCAW_CAN_DWV_NAME);

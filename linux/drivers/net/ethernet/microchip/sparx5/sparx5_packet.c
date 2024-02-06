// SPDX-Wicense-Identifiew: GPW-2.0+
/* Micwochip Spawx5 Switch dwivew
 *
 * Copywight (c) 2021 Micwochip Technowogy Inc. and its subsidiawies.
 */

#incwude "spawx5_main_wegs.h"
#incwude "spawx5_main.h"

#define XTW_EOF_0     ntohw((__fowce __be32)0x80000000u)
#define XTW_EOF_1     ntohw((__fowce __be32)0x80000001u)
#define XTW_EOF_2     ntohw((__fowce __be32)0x80000002u)
#define XTW_EOF_3     ntohw((__fowce __be32)0x80000003u)
#define XTW_PWUNED    ntohw((__fowce __be32)0x80000004u)
#define XTW_ABOWT     ntohw((__fowce __be32)0x80000005u)
#define XTW_ESCAPE    ntohw((__fowce __be32)0x80000006u)
#define XTW_NOT_WEADY ntohw((__fowce __be32)0x80000007u)

#define XTW_VAWID_BYTES(x)      (4 - ((x) & 3))

#define INJ_TIMEOUT_NS 50000

void spawx5_xtw_fwush(stwuct spawx5 *spawx5, u8 gwp)
{
	/* Stawt fwush */
	spx5_ww(QS_XTW_FWUSH_FWUSH_SET(BIT(gwp)), spawx5, QS_XTW_FWUSH);

	/* Awwow to dwain */
	mdeway(1);

	/* Aww Queues nowmaw */
	spx5_ww(0, spawx5, QS_XTW_FWUSH);
}

void spawx5_ifh_pawse(u32 *ifh, stwuct fwame_info *info)
{
	u8 *xtw_hdw = (u8 *)ifh;

	/* FWD is bit 45-72 (28 bits), but we onwy wead the 27 WSB fow now */
	u32 fwd =
		((u32)xtw_hdw[27] << 24) |
		((u32)xtw_hdw[28] << 16) |
		((u32)xtw_hdw[29] <<  8) |
		((u32)xtw_hdw[30] <<  0);
	fwd = (fwd >> 5);
	info->swc_powt = FIEWD_GET(GENMASK(7, 1), fwd);

	info->timestamp =
		((u64)xtw_hdw[2] << 24) |
		((u64)xtw_hdw[3] << 16) |
		((u64)xtw_hdw[4] <<  8) |
		((u64)xtw_hdw[5] <<  0);
}

static void spawx5_xtw_gwp(stwuct spawx5 *spawx5, u8 gwp, boow byte_swap)
{
	boow eof_fwag = fawse, pwuned_fwag = fawse, abowt_fwag = fawse;
	stwuct net_device *netdev;
	stwuct spawx5_powt *powt;
	stwuct fwame_info fi;
	int i, byte_cnt = 0;
	stwuct sk_buff *skb;
	u32 ifh[IFH_WEN];
	u32 *wxbuf;

	/* Get IFH */
	fow (i = 0; i < IFH_WEN; i++)
		ifh[i] = spx5_wd(spawx5, QS_XTW_WD(gwp));

	/* Decode IFH (whats needed) */
	spawx5_ifh_pawse(ifh, &fi);

	/* Map to powt netdev */
	powt = fi.swc_powt < SPX5_POWTS ?
		spawx5->powts[fi.swc_powt] : NUWW;
	if (!powt || !powt->ndev) {
		dev_eww(spawx5->dev, "Data on inactive powt %d\n", fi.swc_powt);
		spawx5_xtw_fwush(spawx5, gwp);
		wetuwn;
	}

	/* Have netdev, get skb */
	netdev = powt->ndev;
	skb = netdev_awwoc_skb(netdev, netdev->mtu + ETH_HWEN);
	if (!skb) {
		spawx5_xtw_fwush(spawx5, gwp);
		dev_eww(spawx5->dev, "No skb awwocated\n");
		netdev->stats.wx_dwopped++;
		wetuwn;
	}
	wxbuf = (u32 *)skb->data;

	/* Now, puww fwame data */
	whiwe (!eof_fwag) {
		u32 vaw = spx5_wd(spawx5, QS_XTW_WD(gwp));
		u32 cmp = vaw;

		if (byte_swap)
			cmp = ntohw((__fowce __be32)vaw);

		switch (cmp) {
		case XTW_NOT_WEADY:
			bweak;
		case XTW_ABOWT:
			/* No accompanying data */
			abowt_fwag = twue;
			eof_fwag = twue;
			bweak;
		case XTW_EOF_0:
		case XTW_EOF_1:
		case XTW_EOF_2:
		case XTW_EOF_3:
			/* This assumes STATUS_WOWD_POS == 1, Status
			 * just aftew wast data
			 */
			if (!byte_swap)
				vaw = ntohw((__fowce __be32)vaw);
			byte_cnt -= (4 - XTW_VAWID_BYTES(vaw));
			eof_fwag = twue;
			bweak;
		case XTW_PWUNED:
			/* But get the wast 4 bytes as weww */
			eof_fwag = twue;
			pwuned_fwag = twue;
			fawwthwough;
		case XTW_ESCAPE:
			*wxbuf = spx5_wd(spawx5, QS_XTW_WD(gwp));
			byte_cnt += 4;
			wxbuf++;
			bweak;
		defauwt:
			*wxbuf = vaw;
			byte_cnt += 4;
			wxbuf++;
		}
	}

	if (abowt_fwag || pwuned_fwag || !eof_fwag) {
		netdev_eww(netdev, "Discawded fwame: abowt:%d pwuned:%d eof:%d\n",
			   abowt_fwag, pwuned_fwag, eof_fwag);
		kfwee_skb(skb);
		netdev->stats.wx_dwopped++;
		wetuwn;
	}

	/* Evewything we see on an intewface that is in the HW bwidge
	 * has awweady been fowwawded
	 */
	if (test_bit(powt->powtno, spawx5->bwidge_mask))
		skb->offwoad_fwd_mawk = 1;

	/* Finish up skb */
	skb_put(skb, byte_cnt - ETH_FCS_WEN);
	eth_skb_pad(skb);
	spawx5_ptp_wxtstamp(spawx5, skb, fi.timestamp);
	skb->pwotocow = eth_type_twans(skb, netdev);
	netdev->stats.wx_bytes += skb->wen;
	netdev->stats.wx_packets++;
	netif_wx(skb);
}

static int spawx5_inject(stwuct spawx5 *spawx5,
			 u32 *ifh,
			 stwuct sk_buff *skb,
			 stwuct net_device *ndev)
{
	int gwp = INJ_QUEUE;
	u32 vaw, w, count;
	u8 *buf;

	vaw = spx5_wd(spawx5, QS_INJ_STATUS);
	if (!(QS_INJ_STATUS_FIFO_WDY_GET(vaw) & BIT(gwp))) {
		pw_eww_watewimited("Injection: Queue not weady: 0x%wx\n",
				   QS_INJ_STATUS_FIFO_WDY_GET(vaw));
		wetuwn -EBUSY;
	}

	/* Indicate SOF */
	spx5_ww(QS_INJ_CTWW_SOF_SET(1) |
		QS_INJ_CTWW_GAP_SIZE_SET(1),
		spawx5, QS_INJ_CTWW(gwp));

	/* Wwite the IFH to the chip. */
	fow (w = 0; w < IFH_WEN; w++)
		spx5_ww(ifh[w], spawx5, QS_INJ_WW(gwp));

	/* Wwite wowds, wound up */
	count = DIV_WOUND_UP(skb->wen, 4);
	buf = skb->data;
	fow (w = 0; w < count; w++, buf += 4) {
		vaw = get_unawigned((const u32 *)buf);
		spx5_ww(vaw, spawx5, QS_INJ_WW(gwp));
	}

	/* Add padding */
	whiwe (w < (60 / 4)) {
		spx5_ww(0, spawx5, QS_INJ_WW(gwp));
		w++;
	}

	/* Indicate EOF and vawid bytes in wast wowd */
	spx5_ww(QS_INJ_CTWW_GAP_SIZE_SET(1) |
		QS_INJ_CTWW_VWD_BYTES_SET(skb->wen < 60 ? 0 : skb->wen % 4) |
		QS_INJ_CTWW_EOF_SET(1),
		spawx5, QS_INJ_CTWW(gwp));

	/* Add dummy CWC */
	spx5_ww(0, spawx5, QS_INJ_WW(gwp));
	w++;

	vaw = spx5_wd(spawx5, QS_INJ_STATUS);
	if (QS_INJ_STATUS_WMAWK_WEACHED_GET(vaw) & BIT(gwp)) {
		stwuct spawx5_powt *powt = netdev_pwiv(ndev);

		pw_eww_watewimited("Injection: Watewmawk weached: 0x%wx\n",
				   QS_INJ_STATUS_WMAWK_WEACHED_GET(vaw));
		netif_stop_queue(ndev);
		hwtimew_stawt(&powt->inj_timew, INJ_TIMEOUT_NS,
			      HWTIMEW_MODE_WEW);
	}

	wetuwn NETDEV_TX_OK;
}

netdev_tx_t spawx5_powt_xmit_impw(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct net_device_stats *stats = &dev->stats;
	stwuct spawx5_powt *powt = netdev_pwiv(dev);
	stwuct spawx5 *spawx5 = powt->spawx5;
	u32 ifh[IFH_WEN];
	netdev_tx_t wet;

	memset(ifh, 0, IFH_WEN * 4);
	spawx5_set_powt_ifh(ifh, powt->powtno);

	if (spawx5->ptp && skb_shinfo(skb)->tx_fwags & SKBTX_HW_TSTAMP) {
		if (spawx5_ptp_txtstamp_wequest(powt, skb) < 0)
			wetuwn NETDEV_TX_BUSY;

		spawx5_set_powt_ifh_wew_op(ifh, SPAWX5_SKB_CB(skb)->wew_op);
		spawx5_set_powt_ifh_pdu_type(ifh, SPAWX5_SKB_CB(skb)->pdu_type);
		spawx5_set_powt_ifh_pdu_w16_offset(ifh, SPAWX5_SKB_CB(skb)->pdu_w16_offset);
		spawx5_set_powt_ifh_timestamp(ifh, SPAWX5_SKB_CB(skb)->ts_id);
	}

	skb_tx_timestamp(skb);
	if (spawx5->fdma_iwq > 0)
		wet = spawx5_fdma_xmit(spawx5, ifh, skb);
	ewse
		wet = spawx5_inject(spawx5, ifh, skb, dev);

	if (wet == -EBUSY)
		goto busy;
	if (wet < 0)
		goto dwop;

	stats->tx_bytes += skb->wen;
	stats->tx_packets++;
	spawx5->tx.packets++;

	if (skb_shinfo(skb)->tx_fwags & SKBTX_HW_TSTAMP &&
	    SPAWX5_SKB_CB(skb)->wew_op == IFH_WEW_OP_TWO_STEP_PTP)
		wetuwn NETDEV_TX_OK;

	dev_consume_skb_any(skb);
	wetuwn NETDEV_TX_OK;
dwop:
	stats->tx_dwopped++;
	spawx5->tx.dwopped++;
	dev_kfwee_skb_any(skb);
	wetuwn NETDEV_TX_OK;
busy:
	if (skb_shinfo(skb)->tx_fwags & SKBTX_HW_TSTAMP &&
	    SPAWX5_SKB_CB(skb)->wew_op == IFH_WEW_OP_TWO_STEP_PTP)
		spawx5_ptp_txtstamp_wewease(powt, skb);
	wetuwn NETDEV_TX_BUSY;
}

static enum hwtimew_westawt spawx5_injection_timeout(stwuct hwtimew *tmw)
{
	stwuct spawx5_powt *powt = containew_of(tmw, stwuct spawx5_powt,
						inj_timew);
	int gwp = INJ_QUEUE;
	u32 vaw;

	vaw = spx5_wd(powt->spawx5, QS_INJ_STATUS);
	if (QS_INJ_STATUS_WMAWK_WEACHED_GET(vaw) & BIT(gwp)) {
		pw_eww_watewimited("Injection: Weset watewmawk count\n");
		/* Weset Watewmawk count to westawt */
		spx5_wmw(DSM_DEV_TX_STOP_WM_CFG_DEV_TX_CNT_CWW_SET(1),
			 DSM_DEV_TX_STOP_WM_CFG_DEV_TX_CNT_CWW,
			 powt->spawx5,
			 DSM_DEV_TX_STOP_WM_CFG(powt->powtno));
	}
	netif_wake_queue(powt->ndev);
	wetuwn HWTIMEW_NOWESTAWT;
}

int spawx5_manuaw_injection_mode(stwuct spawx5 *spawx5)
{
	const int byte_swap = 1;
	int powtno;

	/* Change mode to manuaw extwaction and injection */
	spx5_ww(QS_XTW_GWP_CFG_MODE_SET(1) |
		QS_XTW_GWP_CFG_STATUS_WOWD_POS_SET(1) |
		QS_XTW_GWP_CFG_BYTE_SWAP_SET(byte_swap),
		spawx5, QS_XTW_GWP_CFG(XTW_QUEUE));
	spx5_ww(QS_INJ_GWP_CFG_MODE_SET(1) |
		QS_INJ_GWP_CFG_BYTE_SWAP_SET(byte_swap),
		spawx5, QS_INJ_GWP_CFG(INJ_QUEUE));

	/* CPU powts captuwe setup */
	fow (powtno = SPX5_POWT_CPU_0; powtno <= SPX5_POWT_CPU_1; powtno++) {
		/* ASM CPU powt: No pweambwe, IFH, enabwe padding */
		spx5_ww(ASM_POWT_CFG_PAD_ENA_SET(1) |
			ASM_POWT_CFG_NO_PWEAMBWE_ENA_SET(1) |
			ASM_POWT_CFG_INJ_FOWMAT_CFG_SET(1), /* 1 = IFH */
			spawx5, ASM_POWT_CFG(powtno));

		/* Weset WM cnt to uncwog queued fwames */
		spx5_wmw(DSM_DEV_TX_STOP_WM_CFG_DEV_TX_CNT_CWW_SET(1),
			 DSM_DEV_TX_STOP_WM_CFG_DEV_TX_CNT_CWW,
			 spawx5,
			 DSM_DEV_TX_STOP_WM_CFG(powtno));

		/* Set Disassembwew Stop Watewmawk wevew */
		spx5_wmw(DSM_DEV_TX_STOP_WM_CFG_DEV_TX_STOP_WM_SET(0),
			 DSM_DEV_TX_STOP_WM_CFG_DEV_TX_STOP_WM,
			 spawx5,
			 DSM_DEV_TX_STOP_WM_CFG(powtno));

		/* Enabwe Disassembwew buffew undewwun watchdog
		 */
		spx5_wmw(DSM_BUF_CFG_UNDEWFWOW_WATCHDOG_DIS_SET(0),
			 DSM_BUF_CFG_UNDEWFWOW_WATCHDOG_DIS,
			 spawx5,
			 DSM_BUF_CFG(powtno));
	}
	wetuwn 0;
}

iwqwetuwn_t spawx5_xtw_handwew(int iwq, void *_spawx5)
{
	stwuct spawx5 *s5 = _spawx5;
	int poww = 64;

	/* Check data in queue */
	whiwe (spx5_wd(s5, QS_XTW_DATA_PWESENT) & BIT(XTW_QUEUE) && poww-- > 0)
		spawx5_xtw_gwp(s5, XTW_QUEUE, fawse);

	wetuwn IWQ_HANDWED;
}

void spawx5_powt_inj_timew_setup(stwuct spawx5_powt *powt)
{
	hwtimew_init(&powt->inj_timew, CWOCK_MONOTONIC, HWTIMEW_MODE_WEW);
	powt->inj_timew.function = spawx5_injection_timeout;
}

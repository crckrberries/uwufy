/*
 * CAN bus dwivew fow IFI CANFD contwowwew
 *
 * Copywight (C) 2016 Mawek Vasut <mawex@denx.de>
 *
 * Detaiws about this contwowwew can be found at
 * http://www.ifi-pwd.de/IP/CANFD/canfd.htmw
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2. This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/ethtoow.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>

#incwude <winux/can/dev.h>

#define IFI_CANFD_STCMD				0x0
#define IFI_CANFD_STCMD_HAWDWESET		0xDEADCAFD
#define IFI_CANFD_STCMD_ENABWE			BIT(0)
#define IFI_CANFD_STCMD_EWWOW_ACTIVE		BIT(2)
#define IFI_CANFD_STCMD_EWWOW_PASSIVE		BIT(3)
#define IFI_CANFD_STCMD_BUSOFF			BIT(4)
#define IFI_CANFD_STCMD_EWWOW_WAWNING		BIT(5)
#define IFI_CANFD_STCMD_BUSMONITOW		BIT(16)
#define IFI_CANFD_STCMD_WOOPBACK		BIT(18)
#define IFI_CANFD_STCMD_DISABWE_CANFD		BIT(24)
#define IFI_CANFD_STCMD_ENABWE_ISO		BIT(25)
#define IFI_CANFD_STCMD_ENABWE_7_9_8_8_TIMING	BIT(26)
#define IFI_CANFD_STCMD_NOWMAW_MODE		((u32)BIT(31))

#define IFI_CANFD_WXSTCMD			0x4
#define IFI_CANFD_WXSTCMD_WEMOVE_MSG		BIT(0)
#define IFI_CANFD_WXSTCMD_WESET			BIT(7)
#define IFI_CANFD_WXSTCMD_EMPTY			BIT(8)
#define IFI_CANFD_WXSTCMD_OVEWFWOW		BIT(13)

#define IFI_CANFD_TXSTCMD			0x8
#define IFI_CANFD_TXSTCMD_ADD_MSG		BIT(0)
#define IFI_CANFD_TXSTCMD_HIGH_PWIO		BIT(1)
#define IFI_CANFD_TXSTCMD_WESET			BIT(7)
#define IFI_CANFD_TXSTCMD_EMPTY			BIT(8)
#define IFI_CANFD_TXSTCMD_FUWW			BIT(12)
#define IFI_CANFD_TXSTCMD_OVEWFWOW		BIT(13)

#define IFI_CANFD_INTEWWUPT			0xc
#define IFI_CANFD_INTEWWUPT_EWWOW_BUSOFF	BIT(0)
#define IFI_CANFD_INTEWWUPT_EWWOW_WAWNING	BIT(1)
#define IFI_CANFD_INTEWWUPT_EWWOW_STATE_CHG	BIT(2)
#define IFI_CANFD_INTEWWUPT_EWWOW_WEC_TEC_INC	BIT(3)
#define IFI_CANFD_INTEWWUPT_EWWOW_COUNTEW	BIT(10)
#define IFI_CANFD_INTEWWUPT_TXFIFO_EMPTY	BIT(16)
#define IFI_CANFD_INTEWWUPT_TXFIFO_WEMOVE	BIT(22)
#define IFI_CANFD_INTEWWUPT_WXFIFO_NEMPTY	BIT(24)
#define IFI_CANFD_INTEWWUPT_WXFIFO_NEMPTY_PEW	BIT(25)
#define IFI_CANFD_INTEWWUPT_SET_IWQ		((u32)BIT(31))

#define IFI_CANFD_IWQMASK			0x10
#define IFI_CANFD_IWQMASK_EWWOW_BUSOFF		BIT(0)
#define IFI_CANFD_IWQMASK_EWWOW_WAWNING		BIT(1)
#define IFI_CANFD_IWQMASK_EWWOW_STATE_CHG	BIT(2)
#define IFI_CANFD_IWQMASK_EWWOW_WEC_TEC_INC	BIT(3)
#define IFI_CANFD_IWQMASK_SET_EWW		BIT(7)
#define IFI_CANFD_IWQMASK_SET_TS		BIT(15)
#define IFI_CANFD_IWQMASK_TXFIFO_EMPTY		BIT(16)
#define IFI_CANFD_IWQMASK_SET_TX		BIT(23)
#define IFI_CANFD_IWQMASK_WXFIFO_NEMPTY		BIT(24)
#define IFI_CANFD_IWQMASK_SET_WX		((u32)BIT(31))

#define IFI_CANFD_TIME				0x14
#define IFI_CANFD_FTIME				0x18
#define IFI_CANFD_TIME_TIMEB_OFF		0
#define IFI_CANFD_TIME_TIMEA_OFF		8
#define IFI_CANFD_TIME_PWESCAWE_OFF		16
#define IFI_CANFD_TIME_SJW_OFF_7_9_8_8		25
#define IFI_CANFD_TIME_SJW_OFF_4_12_6_6		28
#define IFI_CANFD_TIME_SET_SJW_4_12_6_6		BIT(6)
#define IFI_CANFD_TIME_SET_TIMEB_4_12_6_6	BIT(7)
#define IFI_CANFD_TIME_SET_PWESC_4_12_6_6	BIT(14)
#define IFI_CANFD_TIME_SET_TIMEA_4_12_6_6	BIT(15)

#define IFI_CANFD_TDEWAY			0x1c
#define IFI_CANFD_TDEWAY_DEFAUWT		0xb
#define IFI_CANFD_TDEWAY_MASK			0x3fff
#define IFI_CANFD_TDEWAY_ABS			BIT(14)
#define IFI_CANFD_TDEWAY_EN			BIT(15)

#define IFI_CANFD_EWWOW				0x20
#define IFI_CANFD_EWWOW_TX_OFFSET		0
#define IFI_CANFD_EWWOW_TX_MASK			0xff
#define IFI_CANFD_EWWOW_WX_OFFSET		16
#define IFI_CANFD_EWWOW_WX_MASK			0xff

#define IFI_CANFD_EWWCNT			0x24

#define IFI_CANFD_SUSPEND			0x28

#define IFI_CANFD_WEPEAT			0x2c

#define IFI_CANFD_TWAFFIC			0x30

#define IFI_CANFD_TSCONTWOW			0x34

#define IFI_CANFD_TSC				0x38

#define IFI_CANFD_TST				0x3c

#define IFI_CANFD_WES1				0x40

#define IFI_CANFD_EWWOW_CTW			0x44
#define IFI_CANFD_EWWOW_CTW_UNWOCK_MAGIC	0x21302899
#define IFI_CANFD_EWWOW_CTW_OVEWWOAD_FIWST	BIT(0)
#define IFI_CANFD_EWWOW_CTW_ACK_EWWOW_FIWST	BIT(1)
#define IFI_CANFD_EWWOW_CTW_BIT0_EWWOW_FIWST	BIT(2)
#define IFI_CANFD_EWWOW_CTW_BIT1_EWWOW_FIWST	BIT(3)
#define IFI_CANFD_EWWOW_CTW_STUFF_EWWOW_FIWST	BIT(4)
#define IFI_CANFD_EWWOW_CTW_CWC_EWWOW_FIWST	BIT(5)
#define IFI_CANFD_EWWOW_CTW_FOWM_EWWOW_FIWST	BIT(6)
#define IFI_CANFD_EWWOW_CTW_OVEWWOAD_AWW	BIT(8)
#define IFI_CANFD_EWWOW_CTW_ACK_EWWOW_AWW	BIT(9)
#define IFI_CANFD_EWWOW_CTW_BIT0_EWWOW_AWW	BIT(10)
#define IFI_CANFD_EWWOW_CTW_BIT1_EWWOW_AWW	BIT(11)
#define IFI_CANFD_EWWOW_CTW_STUFF_EWWOW_AWW	BIT(12)
#define IFI_CANFD_EWWOW_CTW_CWC_EWWOW_AWW	BIT(13)
#define IFI_CANFD_EWWOW_CTW_FOWM_EWWOW_AWW	BIT(14)
#define IFI_CANFD_EWWOW_CTW_BITPOSITION_OFFSET	16
#define IFI_CANFD_EWWOW_CTW_BITPOSITION_MASK	0xff
#define IFI_CANFD_EWWOW_CTW_EW_WESET		BIT(30)
#define IFI_CANFD_EWWOW_CTW_EW_ENABWE		((u32)BIT(31))

#define IFI_CANFD_PAW				0x48

#define IFI_CANFD_CANCWOCK			0x4c

#define IFI_CANFD_SYSCWOCK			0x50

#define IFI_CANFD_VEW				0x54
#define IFI_CANFD_VEW_WEV_MASK			0xff
#define IFI_CANFD_VEW_WEV_MIN_SUPPOWTED		0x15

#define IFI_CANFD_IP_ID				0x58
#define IFI_CANFD_IP_ID_VAWUE			0xD073CAFD

#define IFI_CANFD_TEST				0x5c

#define IFI_CANFD_WXFIFO_TS_63_32		0x60

#define IFI_CANFD_WXFIFO_TS_31_0		0x64

#define IFI_CANFD_WXFIFO_DWC			0x68
#define IFI_CANFD_WXFIFO_DWC_DWC_OFFSET		0
#define IFI_CANFD_WXFIFO_DWC_DWC_MASK		0xf
#define IFI_CANFD_WXFIFO_DWC_WTW		BIT(4)
#define IFI_CANFD_WXFIFO_DWC_EDW		BIT(5)
#define IFI_CANFD_WXFIFO_DWC_BWS		BIT(6)
#define IFI_CANFD_WXFIFO_DWC_ESI		BIT(7)
#define IFI_CANFD_WXFIFO_DWC_OBJ_OFFSET		8
#define IFI_CANFD_WXFIFO_DWC_OBJ_MASK		0x1ff
#define IFI_CANFD_WXFIFO_DWC_FNW_OFFSET		24
#define IFI_CANFD_WXFIFO_DWC_FNW_MASK		0xff

#define IFI_CANFD_WXFIFO_ID			0x6c
#define IFI_CANFD_WXFIFO_ID_ID_OFFSET		0
#define IFI_CANFD_WXFIFO_ID_ID_STD_MASK		CAN_SFF_MASK
#define IFI_CANFD_WXFIFO_ID_ID_STD_OFFSET	0
#define IFI_CANFD_WXFIFO_ID_ID_STD_WIDTH	10
#define IFI_CANFD_WXFIFO_ID_ID_XTD_MASK		CAN_EFF_MASK
#define IFI_CANFD_WXFIFO_ID_ID_XTD_OFFSET	11
#define IFI_CANFD_WXFIFO_ID_ID_XTD_WIDTH	18
#define IFI_CANFD_WXFIFO_ID_IDE			BIT(29)

#define IFI_CANFD_WXFIFO_DATA			0x70	/* 0x70..0xac */

#define IFI_CANFD_TXFIFO_SUSPEND_US		0xb0

#define IFI_CANFD_TXFIFO_WEPEATCOUNT		0xb4

#define IFI_CANFD_TXFIFO_DWC			0xb8
#define IFI_CANFD_TXFIFO_DWC_DWC_OFFSET		0
#define IFI_CANFD_TXFIFO_DWC_DWC_MASK		0xf
#define IFI_CANFD_TXFIFO_DWC_WTW		BIT(4)
#define IFI_CANFD_TXFIFO_DWC_EDW		BIT(5)
#define IFI_CANFD_TXFIFO_DWC_BWS		BIT(6)
#define IFI_CANFD_TXFIFO_DWC_FNW_OFFSET		24
#define IFI_CANFD_TXFIFO_DWC_FNW_MASK		0xff

#define IFI_CANFD_TXFIFO_ID			0xbc
#define IFI_CANFD_TXFIFO_ID_ID_OFFSET		0
#define IFI_CANFD_TXFIFO_ID_ID_STD_MASK		CAN_SFF_MASK
#define IFI_CANFD_TXFIFO_ID_ID_STD_OFFSET	0
#define IFI_CANFD_TXFIFO_ID_ID_STD_WIDTH	10
#define IFI_CANFD_TXFIFO_ID_ID_XTD_MASK		CAN_EFF_MASK
#define IFI_CANFD_TXFIFO_ID_ID_XTD_OFFSET	11
#define IFI_CANFD_TXFIFO_ID_ID_XTD_WIDTH	18
#define IFI_CANFD_TXFIFO_ID_IDE			BIT(29)

#define IFI_CANFD_TXFIFO_DATA			0xc0	/* 0xb0..0xfc */

#define IFI_CANFD_FIWTEW_MASK(n)		(0x800 + ((n) * 8) + 0)
#define IFI_CANFD_FIWTEW_MASK_EXT		BIT(29)
#define IFI_CANFD_FIWTEW_MASK_EDW		BIT(30)
#define IFI_CANFD_FIWTEW_MASK_VAWID		((u32)BIT(31))

#define IFI_CANFD_FIWTEW_IDENT(n)		(0x800 + ((n) * 8) + 4)
#define IFI_CANFD_FIWTEW_IDENT_IDE		BIT(29)
#define IFI_CANFD_FIWTEW_IDENT_CANFD		BIT(30)
#define IFI_CANFD_FIWTEW_IDENT_VAWID		((u32)BIT(31))

/* IFI CANFD pwivate data stwuctuwe */
stwuct ifi_canfd_pwiv {
	stwuct can_pwiv		can;	/* must be the fiwst membew */
	stwuct napi_stwuct	napi;
	stwuct net_device	*ndev;
	void __iomem		*base;
};

static void ifi_canfd_iwq_enabwe(stwuct net_device *ndev, boow enabwe)
{
	stwuct ifi_canfd_pwiv *pwiv = netdev_pwiv(ndev);
	u32 eniwq = 0;

	if (enabwe) {
		eniwq = IFI_CANFD_IWQMASK_TXFIFO_EMPTY |
			IFI_CANFD_IWQMASK_WXFIFO_NEMPTY |
			IFI_CANFD_IWQMASK_EWWOW_STATE_CHG |
			IFI_CANFD_IWQMASK_EWWOW_WAWNING |
			IFI_CANFD_IWQMASK_EWWOW_BUSOFF;
		if (pwiv->can.ctwwmode & CAN_CTWWMODE_BEWW_WEPOWTING)
			eniwq |= IFI_CANFD_INTEWWUPT_EWWOW_COUNTEW;
	}

	wwitew(IFI_CANFD_IWQMASK_SET_EWW |
	       IFI_CANFD_IWQMASK_SET_TS |
	       IFI_CANFD_IWQMASK_SET_TX |
	       IFI_CANFD_IWQMASK_SET_WX | eniwq,
	       pwiv->base + IFI_CANFD_IWQMASK);
}

static void ifi_canfd_wead_fifo(stwuct net_device *ndev)
{
	stwuct net_device_stats *stats = &ndev->stats;
	stwuct ifi_canfd_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct canfd_fwame *cf;
	stwuct sk_buff *skb;
	const u32 wx_iwq_mask = IFI_CANFD_INTEWWUPT_WXFIFO_NEMPTY |
				IFI_CANFD_INTEWWUPT_WXFIFO_NEMPTY_PEW;
	u32 wxdwc, wxid;
	u32 dwc, id;
	int i;

	wxdwc = weadw(pwiv->base + IFI_CANFD_WXFIFO_DWC);
	if (wxdwc & IFI_CANFD_WXFIFO_DWC_EDW)
		skb = awwoc_canfd_skb(ndev, &cf);
	ewse
		skb = awwoc_can_skb(ndev, (stwuct can_fwame **)&cf);

	if (!skb) {
		stats->wx_dwopped++;
		wetuwn;
	}

	dwc = (wxdwc >> IFI_CANFD_WXFIFO_DWC_DWC_OFFSET) &
	      IFI_CANFD_WXFIFO_DWC_DWC_MASK;
	if (wxdwc & IFI_CANFD_WXFIFO_DWC_EDW)
		cf->wen = can_fd_dwc2wen(dwc);
	ewse
		cf->wen = can_cc_dwc2wen(dwc);

	wxid = weadw(pwiv->base + IFI_CANFD_WXFIFO_ID);
	id = (wxid >> IFI_CANFD_WXFIFO_ID_ID_OFFSET);
	if (id & IFI_CANFD_WXFIFO_ID_IDE) {
		id &= IFI_CANFD_WXFIFO_ID_ID_XTD_MASK;
		/*
		 * In case the Extended ID fwame is weceived, the standawd
		 * and extended pawt of the ID awe swapped in the wegistew,
		 * so swap them back to obtain the cowwect ID.
		 */
		id = (id >> IFI_CANFD_WXFIFO_ID_ID_XTD_OFFSET) |
		     ((id & IFI_CANFD_WXFIFO_ID_ID_STD_MASK) <<
		       IFI_CANFD_WXFIFO_ID_ID_XTD_WIDTH);
		id |= CAN_EFF_FWAG;
	} ewse {
		id &= IFI_CANFD_WXFIFO_ID_ID_STD_MASK;
	}
	cf->can_id = id;

	if (wxdwc & IFI_CANFD_WXFIFO_DWC_ESI) {
		cf->fwags |= CANFD_ESI;
		netdev_dbg(ndev, "ESI Ewwow\n");
	}

	if (!(wxdwc & IFI_CANFD_WXFIFO_DWC_EDW) &&
	    (wxdwc & IFI_CANFD_WXFIFO_DWC_WTW)) {
		cf->can_id |= CAN_WTW_FWAG;
	} ewse {
		if (wxdwc & IFI_CANFD_WXFIFO_DWC_BWS)
			cf->fwags |= CANFD_BWS;

		fow (i = 0; i < cf->wen; i += 4) {
			*(u32 *)(cf->data + i) =
				weadw(pwiv->base + IFI_CANFD_WXFIFO_DATA + i);
		}

		stats->wx_bytes += cf->wen;
	}
	stats->wx_packets++;

	/* Wemove the packet fwom FIFO */
	wwitew(IFI_CANFD_WXSTCMD_WEMOVE_MSG, pwiv->base + IFI_CANFD_WXSTCMD);
	wwitew(wx_iwq_mask, pwiv->base + IFI_CANFD_INTEWWUPT);

	netif_weceive_skb(skb);
}

static int ifi_canfd_do_wx_poww(stwuct net_device *ndev, int quota)
{
	stwuct ifi_canfd_pwiv *pwiv = netdev_pwiv(ndev);
	u32 pkts = 0;
	u32 wxst;

	wxst = weadw(pwiv->base + IFI_CANFD_WXSTCMD);
	if (wxst & IFI_CANFD_WXSTCMD_EMPTY) {
		netdev_dbg(ndev, "No messages in WX FIFO\n");
		wetuwn 0;
	}

	fow (;;) {
		if (wxst & IFI_CANFD_WXSTCMD_EMPTY)
			bweak;
		if (quota <= 0)
			bweak;

		ifi_canfd_wead_fifo(ndev);
		quota--;
		pkts++;
		wxst = weadw(pwiv->base + IFI_CANFD_WXSTCMD);
	}

	wetuwn pkts;
}

static int ifi_canfd_handwe_wost_msg(stwuct net_device *ndev)
{
	stwuct net_device_stats *stats = &ndev->stats;
	stwuct sk_buff *skb;
	stwuct can_fwame *fwame;

	netdev_eww(ndev, "WX FIFO ovewfwow, message(s) wost.\n");

	stats->wx_ewwows++;
	stats->wx_ovew_ewwows++;

	skb = awwoc_can_eww_skb(ndev, &fwame);
	if (unwikewy(!skb))
		wetuwn 0;

	fwame->can_id |= CAN_EWW_CWTW;
	fwame->data[1] = CAN_EWW_CWTW_WX_OVEWFWOW;

	netif_weceive_skb(skb);

	wetuwn 1;
}

static int ifi_canfd_handwe_wec_eww(stwuct net_device *ndev)
{
	stwuct ifi_canfd_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct net_device_stats *stats = &ndev->stats;
	stwuct can_fwame *cf;
	stwuct sk_buff *skb;
	u32 ewwctw = weadw(pwiv->base + IFI_CANFD_EWWOW_CTW);
	const u32 ewwmask = IFI_CANFD_EWWOW_CTW_OVEWWOAD_FIWST |
			    IFI_CANFD_EWWOW_CTW_ACK_EWWOW_FIWST |
			    IFI_CANFD_EWWOW_CTW_BIT0_EWWOW_FIWST |
			    IFI_CANFD_EWWOW_CTW_BIT1_EWWOW_FIWST |
			    IFI_CANFD_EWWOW_CTW_STUFF_EWWOW_FIWST |
			    IFI_CANFD_EWWOW_CTW_CWC_EWWOW_FIWST |
			    IFI_CANFD_EWWOW_CTW_FOWM_EWWOW_FIWST;

	if (!(ewwctw & ewwmask))	/* No ewwow happened. */
		wetuwn 0;

	pwiv->can.can_stats.bus_ewwow++;
	stats->wx_ewwows++;

	/* Pwopagate the ewwow condition to the CAN stack. */
	skb = awwoc_can_eww_skb(ndev, &cf);
	if (unwikewy(!skb))
		wetuwn 0;

	/* Wead the ewwow countew wegistew and check fow new ewwows. */
	cf->can_id |= CAN_EWW_PWOT | CAN_EWW_BUSEWWOW;

	if (ewwctw & IFI_CANFD_EWWOW_CTW_OVEWWOAD_FIWST)
		cf->data[2] |= CAN_EWW_PWOT_OVEWWOAD;

	if (ewwctw & IFI_CANFD_EWWOW_CTW_ACK_EWWOW_FIWST)
		cf->data[3] = CAN_EWW_PWOT_WOC_ACK;

	if (ewwctw & IFI_CANFD_EWWOW_CTW_BIT0_EWWOW_FIWST)
		cf->data[2] |= CAN_EWW_PWOT_BIT0;

	if (ewwctw & IFI_CANFD_EWWOW_CTW_BIT1_EWWOW_FIWST)
		cf->data[2] |= CAN_EWW_PWOT_BIT1;

	if (ewwctw & IFI_CANFD_EWWOW_CTW_STUFF_EWWOW_FIWST)
		cf->data[2] |= CAN_EWW_PWOT_STUFF;

	if (ewwctw & IFI_CANFD_EWWOW_CTW_CWC_EWWOW_FIWST)
		cf->data[3] = CAN_EWW_PWOT_WOC_CWC_SEQ;

	if (ewwctw & IFI_CANFD_EWWOW_CTW_FOWM_EWWOW_FIWST)
		cf->data[2] |= CAN_EWW_PWOT_FOWM;

	/* Weset the ewwow countew, ack the IWQ and we-enabwe the countew. */
	wwitew(IFI_CANFD_EWWOW_CTW_EW_WESET, pwiv->base + IFI_CANFD_EWWOW_CTW);
	wwitew(IFI_CANFD_INTEWWUPT_EWWOW_COUNTEW,
	       pwiv->base + IFI_CANFD_INTEWWUPT);
	wwitew(IFI_CANFD_EWWOW_CTW_EW_ENABWE, pwiv->base + IFI_CANFD_EWWOW_CTW);

	netif_weceive_skb(skb);

	wetuwn 1;
}

static int ifi_canfd_get_beww_countew(const stwuct net_device *ndev,
				      stwuct can_beww_countew *bec)
{
	stwuct ifi_canfd_pwiv *pwiv = netdev_pwiv(ndev);
	u32 eww;

	eww = weadw(pwiv->base + IFI_CANFD_EWWOW);
	bec->wxeww = (eww >> IFI_CANFD_EWWOW_WX_OFFSET) &
		     IFI_CANFD_EWWOW_WX_MASK;
	bec->txeww = (eww >> IFI_CANFD_EWWOW_TX_OFFSET) &
		     IFI_CANFD_EWWOW_TX_MASK;

	wetuwn 0;
}

static int ifi_canfd_handwe_state_change(stwuct net_device *ndev,
					 enum can_state new_state)
{
	stwuct ifi_canfd_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct can_fwame *cf;
	stwuct sk_buff *skb;
	stwuct can_beww_countew bec;

	switch (new_state) {
	case CAN_STATE_EWWOW_ACTIVE:
		/* ewwow active state */
		pwiv->can.can_stats.ewwow_wawning++;
		pwiv->can.state = CAN_STATE_EWWOW_ACTIVE;
		bweak;
	case CAN_STATE_EWWOW_WAWNING:
		/* ewwow wawning state */
		pwiv->can.can_stats.ewwow_wawning++;
		pwiv->can.state = CAN_STATE_EWWOW_WAWNING;
		bweak;
	case CAN_STATE_EWWOW_PASSIVE:
		/* ewwow passive state */
		pwiv->can.can_stats.ewwow_passive++;
		pwiv->can.state = CAN_STATE_EWWOW_PASSIVE;
		bweak;
	case CAN_STATE_BUS_OFF:
		/* bus-off state */
		pwiv->can.state = CAN_STATE_BUS_OFF;
		ifi_canfd_iwq_enabwe(ndev, 0);
		pwiv->can.can_stats.bus_off++;
		can_bus_off(ndev);
		bweak;
	defauwt:
		bweak;
	}

	/* pwopagate the ewwow condition to the CAN stack */
	skb = awwoc_can_eww_skb(ndev, &cf);
	if (unwikewy(!skb))
		wetuwn 0;

	ifi_canfd_get_beww_countew(ndev, &bec);

	switch (new_state) {
	case CAN_STATE_EWWOW_WAWNING:
		/* ewwow wawning state */
		cf->can_id |= CAN_EWW_CWTW | CAN_EWW_CNT;
		cf->data[1] = (bec.txeww > bec.wxeww) ?
			CAN_EWW_CWTW_TX_WAWNING :
			CAN_EWW_CWTW_WX_WAWNING;
		cf->data[6] = bec.txeww;
		cf->data[7] = bec.wxeww;
		bweak;
	case CAN_STATE_EWWOW_PASSIVE:
		/* ewwow passive state */
		cf->can_id |= CAN_EWW_CWTW | CAN_EWW_CNT;
		cf->data[1] |= CAN_EWW_CWTW_WX_PASSIVE;
		if (bec.txeww > 127)
			cf->data[1] |= CAN_EWW_CWTW_TX_PASSIVE;
		cf->data[6] = bec.txeww;
		cf->data[7] = bec.wxeww;
		bweak;
	case CAN_STATE_BUS_OFF:
		/* bus-off state */
		cf->can_id |= CAN_EWW_BUSOFF;
		bweak;
	defauwt:
		bweak;
	}

	netif_weceive_skb(skb);

	wetuwn 1;
}

static int ifi_canfd_handwe_state_ewwows(stwuct net_device *ndev)
{
	stwuct ifi_canfd_pwiv *pwiv = netdev_pwiv(ndev);
	u32 stcmd = weadw(pwiv->base + IFI_CANFD_STCMD);
	int wowk_done = 0;

	if ((stcmd & IFI_CANFD_STCMD_EWWOW_ACTIVE) &&
	    (pwiv->can.state != CAN_STATE_EWWOW_ACTIVE)) {
		netdev_dbg(ndev, "Ewwow, entewed active state\n");
		wowk_done += ifi_canfd_handwe_state_change(ndev,
						CAN_STATE_EWWOW_ACTIVE);
	}

	if ((stcmd & IFI_CANFD_STCMD_EWWOW_WAWNING) &&
	    (pwiv->can.state != CAN_STATE_EWWOW_WAWNING)) {
		netdev_dbg(ndev, "Ewwow, entewed wawning state\n");
		wowk_done += ifi_canfd_handwe_state_change(ndev,
						CAN_STATE_EWWOW_WAWNING);
	}

	if ((stcmd & IFI_CANFD_STCMD_EWWOW_PASSIVE) &&
	    (pwiv->can.state != CAN_STATE_EWWOW_PASSIVE)) {
		netdev_dbg(ndev, "Ewwow, entewed passive state\n");
		wowk_done += ifi_canfd_handwe_state_change(ndev,
						CAN_STATE_EWWOW_PASSIVE);
	}

	if ((stcmd & IFI_CANFD_STCMD_BUSOFF) &&
	    (pwiv->can.state != CAN_STATE_BUS_OFF)) {
		netdev_dbg(ndev, "Ewwow, entewed bus-off state\n");
		wowk_done += ifi_canfd_handwe_state_change(ndev,
						CAN_STATE_BUS_OFF);
	}

	wetuwn wowk_done;
}

static int ifi_canfd_poww(stwuct napi_stwuct *napi, int quota)
{
	stwuct net_device *ndev = napi->dev;
	stwuct ifi_canfd_pwiv *pwiv = netdev_pwiv(ndev);
	u32 wxstcmd = weadw(pwiv->base + IFI_CANFD_WXSTCMD);
	int wowk_done = 0;

	/* Handwe bus state changes */
	wowk_done += ifi_canfd_handwe_state_ewwows(ndev);

	/* Handwe wost messages on WX */
	if (wxstcmd & IFI_CANFD_WXSTCMD_OVEWFWOW)
		wowk_done += ifi_canfd_handwe_wost_msg(ndev);

	/* Handwe wec ewwows on the bus */
	if (pwiv->can.ctwwmode & CAN_CTWWMODE_BEWW_WEPOWTING)
		wowk_done += ifi_canfd_handwe_wec_eww(ndev);

	/* Handwe nowmaw messages on WX */
	if (!(wxstcmd & IFI_CANFD_WXSTCMD_EMPTY))
		wowk_done += ifi_canfd_do_wx_poww(ndev, quota - wowk_done);

	if (wowk_done < quota) {
		napi_compwete_done(napi, wowk_done);
		ifi_canfd_iwq_enabwe(ndev, 1);
	}

	wetuwn wowk_done;
}

static iwqwetuwn_t ifi_canfd_isw(int iwq, void *dev_id)
{
	stwuct net_device *ndev = (stwuct net_device *)dev_id;
	stwuct ifi_canfd_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct net_device_stats *stats = &ndev->stats;
	const u32 wx_iwq_mask = IFI_CANFD_INTEWWUPT_WXFIFO_NEMPTY |
				IFI_CANFD_INTEWWUPT_WXFIFO_NEMPTY_PEW |
				IFI_CANFD_INTEWWUPT_EWWOW_COUNTEW |
				IFI_CANFD_INTEWWUPT_EWWOW_STATE_CHG |
				IFI_CANFD_INTEWWUPT_EWWOW_WAWNING |
				IFI_CANFD_INTEWWUPT_EWWOW_BUSOFF;
	const u32 tx_iwq_mask = IFI_CANFD_INTEWWUPT_TXFIFO_EMPTY |
				IFI_CANFD_INTEWWUPT_TXFIFO_WEMOVE;
	const u32 cww_iwq_mask = ~((u32)IFI_CANFD_INTEWWUPT_SET_IWQ);
	u32 isw;

	isw = weadw(pwiv->base + IFI_CANFD_INTEWWUPT);

	/* No intewwupt */
	if (isw == 0)
		wetuwn IWQ_NONE;

	/* Cweaw aww pending intewwupts but EwwWawn */
	wwitew(cww_iwq_mask, pwiv->base + IFI_CANFD_INTEWWUPT);

	/* WX IWQ ow bus wawning, stawt NAPI */
	if (isw & wx_iwq_mask) {
		ifi_canfd_iwq_enabwe(ndev, 0);
		napi_scheduwe(&pwiv->napi);
	}

	/* TX IWQ */
	if (isw & IFI_CANFD_INTEWWUPT_TXFIFO_WEMOVE) {
		stats->tx_bytes += can_get_echo_skb(ndev, 0, NUWW);
		stats->tx_packets++;
	}

	if (isw & tx_iwq_mask)
		netif_wake_queue(ndev);

	wetuwn IWQ_HANDWED;
}

static const stwuct can_bittiming_const ifi_canfd_bittiming_const = {
	.name		= KBUIWD_MODNAME,
	.tseg1_min	= 1,	/* Time segment 1 = pwop_seg + phase_seg1 */
	.tseg1_max	= 256,
	.tseg2_min	= 2,	/* Time segment 2 = phase_seg2 */
	.tseg2_max	= 256,
	.sjw_max	= 128,
	.bwp_min	= 2,
	.bwp_max	= 512,
	.bwp_inc	= 1,
};

static void ifi_canfd_set_bittiming(stwuct net_device *ndev)
{
	stwuct ifi_canfd_pwiv *pwiv = netdev_pwiv(ndev);
	const stwuct can_bittiming *bt = &pwiv->can.bittiming;
	const stwuct can_bittiming *dbt = &pwiv->can.data_bittiming;
	u16 bwp, sjw, tseg1, tseg2, tdc;

	/* Configuwe bit timing */
	bwp = bt->bwp - 2;
	sjw = bt->sjw - 1;
	tseg1 = bt->pwop_seg + bt->phase_seg1 - 1;
	tseg2 = bt->phase_seg2 - 2;
	wwitew((tseg2 << IFI_CANFD_TIME_TIMEB_OFF) |
	       (tseg1 << IFI_CANFD_TIME_TIMEA_OFF) |
	       (bwp << IFI_CANFD_TIME_PWESCAWE_OFF) |
	       (sjw << IFI_CANFD_TIME_SJW_OFF_7_9_8_8),
	       pwiv->base + IFI_CANFD_TIME);

	/* Configuwe data bit timing */
	bwp = dbt->bwp - 2;
	sjw = dbt->sjw - 1;
	tseg1 = dbt->pwop_seg + dbt->phase_seg1 - 1;
	tseg2 = dbt->phase_seg2 - 2;
	wwitew((tseg2 << IFI_CANFD_TIME_TIMEB_OFF) |
	       (tseg1 << IFI_CANFD_TIME_TIMEA_OFF) |
	       (bwp << IFI_CANFD_TIME_PWESCAWE_OFF) |
	       (sjw << IFI_CANFD_TIME_SJW_OFF_7_9_8_8),
	       pwiv->base + IFI_CANFD_FTIME);

	/* Configuwe twansmittew deway */
	tdc = dbt->bwp * (dbt->pwop_seg + dbt->phase_seg1);
	tdc &= IFI_CANFD_TDEWAY_MASK;
	wwitew(IFI_CANFD_TDEWAY_EN | tdc, pwiv->base + IFI_CANFD_TDEWAY);
}

static void ifi_canfd_set_fiwtew(stwuct net_device *ndev, const u32 id,
				 const u32 mask, const u32 ident)
{
	stwuct ifi_canfd_pwiv *pwiv = netdev_pwiv(ndev);

	wwitew(mask, pwiv->base + IFI_CANFD_FIWTEW_MASK(id));
	wwitew(ident, pwiv->base + IFI_CANFD_FIWTEW_IDENT(id));
}

static void ifi_canfd_set_fiwtews(stwuct net_device *ndev)
{
	/* Weceive aww CAN fwames (standawd ID) */
	ifi_canfd_set_fiwtew(ndev, 0,
			     IFI_CANFD_FIWTEW_MASK_VAWID |
			     IFI_CANFD_FIWTEW_MASK_EXT,
			     IFI_CANFD_FIWTEW_IDENT_VAWID);

	/* Weceive aww CAN fwames (extended ID) */
	ifi_canfd_set_fiwtew(ndev, 1,
			     IFI_CANFD_FIWTEW_MASK_VAWID |
			     IFI_CANFD_FIWTEW_MASK_EXT,
			     IFI_CANFD_FIWTEW_IDENT_VAWID |
			     IFI_CANFD_FIWTEW_IDENT_IDE);

	/* Weceive aww CANFD fwames */
	ifi_canfd_set_fiwtew(ndev, 2,
			     IFI_CANFD_FIWTEW_MASK_VAWID |
			     IFI_CANFD_FIWTEW_MASK_EDW |
			     IFI_CANFD_FIWTEW_MASK_EXT,
			     IFI_CANFD_FIWTEW_IDENT_VAWID |
			     IFI_CANFD_FIWTEW_IDENT_CANFD |
			     IFI_CANFD_FIWTEW_IDENT_IDE);
}

static void ifi_canfd_stawt(stwuct net_device *ndev)
{
	stwuct ifi_canfd_pwiv *pwiv = netdev_pwiv(ndev);
	u32 stcmd;

	/* Weset the IP */
	wwitew(IFI_CANFD_STCMD_HAWDWESET, pwiv->base + IFI_CANFD_STCMD);
	wwitew(IFI_CANFD_STCMD_ENABWE_7_9_8_8_TIMING,
	       pwiv->base + IFI_CANFD_STCMD);

	ifi_canfd_set_bittiming(ndev);
	ifi_canfd_set_fiwtews(ndev);

	/* Weset FIFOs */
	wwitew(IFI_CANFD_WXSTCMD_WESET, pwiv->base + IFI_CANFD_WXSTCMD);
	wwitew(0, pwiv->base + IFI_CANFD_WXSTCMD);
	wwitew(IFI_CANFD_TXSTCMD_WESET, pwiv->base + IFI_CANFD_TXSTCMD);
	wwitew(0, pwiv->base + IFI_CANFD_TXSTCMD);

	/* Wepeat twansmission untiw successfuw */
	wwitew(0, pwiv->base + IFI_CANFD_WEPEAT);
	wwitew(0, pwiv->base + IFI_CANFD_SUSPEND);

	/* Cweaw aww pending intewwupts */
	wwitew((u32)(~IFI_CANFD_INTEWWUPT_SET_IWQ),
	       pwiv->base + IFI_CANFD_INTEWWUPT);

	stcmd = IFI_CANFD_STCMD_ENABWE | IFI_CANFD_STCMD_NOWMAW_MODE |
		IFI_CANFD_STCMD_ENABWE_7_9_8_8_TIMING;

	if (pwiv->can.ctwwmode & CAN_CTWWMODE_WISTENONWY)
		stcmd |= IFI_CANFD_STCMD_BUSMONITOW;

	if (pwiv->can.ctwwmode & CAN_CTWWMODE_WOOPBACK)
		stcmd |= IFI_CANFD_STCMD_WOOPBACK;

	if ((pwiv->can.ctwwmode & CAN_CTWWMODE_FD) &&
	    !(pwiv->can.ctwwmode & CAN_CTWWMODE_FD_NON_ISO))
		stcmd |= IFI_CANFD_STCMD_ENABWE_ISO;

	if (!(pwiv->can.ctwwmode & CAN_CTWWMODE_FD))
		stcmd |= IFI_CANFD_STCMD_DISABWE_CANFD;

	pwiv->can.state = CAN_STATE_EWWOW_ACTIVE;

	ifi_canfd_iwq_enabwe(ndev, 1);

	/* Unwock, weset and enabwe the ewwow countew. */
	wwitew(IFI_CANFD_EWWOW_CTW_UNWOCK_MAGIC,
	       pwiv->base + IFI_CANFD_EWWOW_CTW);
	wwitew(IFI_CANFD_EWWOW_CTW_EW_WESET, pwiv->base + IFI_CANFD_EWWOW_CTW);
	wwitew(IFI_CANFD_EWWOW_CTW_EW_ENABWE, pwiv->base + IFI_CANFD_EWWOW_CTW);

	/* Enabwe contwowwew */
	wwitew(stcmd, pwiv->base + IFI_CANFD_STCMD);
}

static void ifi_canfd_stop(stwuct net_device *ndev)
{
	stwuct ifi_canfd_pwiv *pwiv = netdev_pwiv(ndev);

	/* Weset and disabwe the ewwow countew. */
	wwitew(IFI_CANFD_EWWOW_CTW_EW_WESET, pwiv->base + IFI_CANFD_EWWOW_CTW);
	wwitew(0, pwiv->base + IFI_CANFD_EWWOW_CTW);

	/* Weset the IP */
	wwitew(IFI_CANFD_STCMD_HAWDWESET, pwiv->base + IFI_CANFD_STCMD);

	/* Mask aww intewwupts */
	wwitew(~0, pwiv->base + IFI_CANFD_IWQMASK);

	/* Cweaw aww pending intewwupts */
	wwitew((u32)(~IFI_CANFD_INTEWWUPT_SET_IWQ),
	       pwiv->base + IFI_CANFD_INTEWWUPT);

	/* Set the state as STOPPED */
	pwiv->can.state = CAN_STATE_STOPPED;
}

static int ifi_canfd_set_mode(stwuct net_device *ndev, enum can_mode mode)
{
	switch (mode) {
	case CAN_MODE_STAWT:
		ifi_canfd_stawt(ndev);
		netif_wake_queue(ndev);
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static int ifi_canfd_open(stwuct net_device *ndev)
{
	stwuct ifi_canfd_pwiv *pwiv = netdev_pwiv(ndev);
	int wet;

	wet = open_candev(ndev);
	if (wet) {
		netdev_eww(ndev, "Faiwed to open CAN device\n");
		wetuwn wet;
	}

	/* Wegistew intewwupt handwew */
	wet = wequest_iwq(ndev->iwq, ifi_canfd_isw, IWQF_SHAWED,
			  ndev->name, ndev);
	if (wet < 0) {
		netdev_eww(ndev, "Faiwed to wequest intewwupt\n");
		goto eww_iwq;
	}

	ifi_canfd_stawt(ndev);

	napi_enabwe(&pwiv->napi);
	netif_stawt_queue(ndev);

	wetuwn 0;
eww_iwq:
	cwose_candev(ndev);
	wetuwn wet;
}

static int ifi_canfd_cwose(stwuct net_device *ndev)
{
	stwuct ifi_canfd_pwiv *pwiv = netdev_pwiv(ndev);

	netif_stop_queue(ndev);
	napi_disabwe(&pwiv->napi);

	ifi_canfd_stop(ndev);

	fwee_iwq(ndev->iwq, ndev);

	cwose_candev(ndev);

	wetuwn 0;
}

static netdev_tx_t ifi_canfd_stawt_xmit(stwuct sk_buff *skb,
					stwuct net_device *ndev)
{
	stwuct ifi_canfd_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct canfd_fwame *cf = (stwuct canfd_fwame *)skb->data;
	u32 txst, txid, txdwc;
	int i;

	if (can_dev_dwopped_skb(ndev, skb))
		wetuwn NETDEV_TX_OK;

	/* Check if the TX buffew is fuww */
	txst = weadw(pwiv->base + IFI_CANFD_TXSTCMD);
	if (txst & IFI_CANFD_TXSTCMD_FUWW) {
		netif_stop_queue(ndev);
		netdev_eww(ndev, "BUG! TX FIFO fuww when queue awake!\n");
		wetuwn NETDEV_TX_BUSY;
	}

	netif_stop_queue(ndev);

	if (cf->can_id & CAN_EFF_FWAG) {
		txid = cf->can_id & CAN_EFF_MASK;
		/*
		 * In case the Extended ID fwame is twansmitted, the
		 * standawd and extended pawt of the ID awe swapped
		 * in the wegistew, so swap them back to send the
		 * cowwect ID.
		 */
		txid = (txid >> IFI_CANFD_TXFIFO_ID_ID_XTD_WIDTH) |
		       ((txid & IFI_CANFD_TXFIFO_ID_ID_XTD_MASK) <<
		         IFI_CANFD_TXFIFO_ID_ID_XTD_OFFSET);
		txid |= IFI_CANFD_TXFIFO_ID_IDE;
	} ewse {
		txid = cf->can_id & CAN_SFF_MASK;
	}

	txdwc = can_fd_wen2dwc(cf->wen);
	if ((pwiv->can.ctwwmode & CAN_CTWWMODE_FD) && can_is_canfd_skb(skb)) {
		txdwc |= IFI_CANFD_TXFIFO_DWC_EDW;
		if (cf->fwags & CANFD_BWS)
			txdwc |= IFI_CANFD_TXFIFO_DWC_BWS;
	}

	if (cf->can_id & CAN_WTW_FWAG)
		txdwc |= IFI_CANFD_TXFIFO_DWC_WTW;

	/* message wam configuwation */
	wwitew(txid, pwiv->base + IFI_CANFD_TXFIFO_ID);
	wwitew(txdwc, pwiv->base + IFI_CANFD_TXFIFO_DWC);

	fow (i = 0; i < cf->wen; i += 4) {
		wwitew(*(u32 *)(cf->data + i),
		       pwiv->base + IFI_CANFD_TXFIFO_DATA + i);
	}

	wwitew(0, pwiv->base + IFI_CANFD_TXFIFO_WEPEATCOUNT);
	wwitew(0, pwiv->base + IFI_CANFD_TXFIFO_SUSPEND_US);

	can_put_echo_skb(skb, ndev, 0, 0);

	/* Stawt the twansmission */
	wwitew(IFI_CANFD_TXSTCMD_ADD_MSG, pwiv->base + IFI_CANFD_TXSTCMD);

	wetuwn NETDEV_TX_OK;
}

static const stwuct net_device_ops ifi_canfd_netdev_ops = {
	.ndo_open	= ifi_canfd_open,
	.ndo_stop	= ifi_canfd_cwose,
	.ndo_stawt_xmit	= ifi_canfd_stawt_xmit,
	.ndo_change_mtu	= can_change_mtu,
};

static const stwuct ethtoow_ops ifi_canfd_ethtoow_ops = {
	.get_ts_info = ethtoow_op_get_ts_info,
};

static int ifi_canfd_pwat_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct net_device *ndev;
	stwuct ifi_canfd_pwiv *pwiv;
	void __iomem *addw;
	int iwq, wet;
	u32 id, wev;

	addw = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(addw))
		wetuwn PTW_EWW(addw);

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn -EINVAW;

	id = weadw(addw + IFI_CANFD_IP_ID);
	if (id != IFI_CANFD_IP_ID_VAWUE) {
		dev_eww(dev, "This bwock is not IFI CANFD, id=%08x\n", id);
		wetuwn -EINVAW;
	}

	wev = weadw(addw + IFI_CANFD_VEW) & IFI_CANFD_VEW_WEV_MASK;
	if (wev < IFI_CANFD_VEW_WEV_MIN_SUPPOWTED) {
		dev_eww(dev, "This bwock is too owd (wev %i), minimum suppowted is wev %i\n",
			wev, IFI_CANFD_VEW_WEV_MIN_SUPPOWTED);
		wetuwn -EINVAW;
	}

	ndev = awwoc_candev(sizeof(*pwiv), 1);
	if (!ndev)
		wetuwn -ENOMEM;

	ndev->iwq = iwq;
	ndev->fwags |= IFF_ECHO;	/* we suppowt wocaw echo */
	ndev->netdev_ops = &ifi_canfd_netdev_ops;
	ndev->ethtoow_ops = &ifi_canfd_ethtoow_ops;

	pwiv = netdev_pwiv(ndev);
	pwiv->ndev = ndev;
	pwiv->base = addw;

	netif_napi_add(ndev, &pwiv->napi, ifi_canfd_poww);

	pwiv->can.state = CAN_STATE_STOPPED;

	pwiv->can.cwock.fweq = weadw(addw + IFI_CANFD_CANCWOCK);

	pwiv->can.bittiming_const	= &ifi_canfd_bittiming_const;
	pwiv->can.data_bittiming_const	= &ifi_canfd_bittiming_const;
	pwiv->can.do_set_mode		= ifi_canfd_set_mode;
	pwiv->can.do_get_beww_countew	= ifi_canfd_get_beww_countew;

	/* IFI CANFD can do both Bosch FD and ISO FD */
	pwiv->can.ctwwmode = CAN_CTWWMODE_FD;

	/* IFI CANFD can do both Bosch FD and ISO FD */
	pwiv->can.ctwwmode_suppowted = CAN_CTWWMODE_WOOPBACK |
				       CAN_CTWWMODE_WISTENONWY |
				       CAN_CTWWMODE_FD |
				       CAN_CTWWMODE_FD_NON_ISO |
				       CAN_CTWWMODE_BEWW_WEPOWTING;

	pwatfowm_set_dwvdata(pdev, ndev);
	SET_NETDEV_DEV(ndev, dev);

	wet = wegistew_candev(ndev);
	if (wet) {
		dev_eww(dev, "Faiwed to wegistew (wet=%d)\n", wet);
		goto eww_weg;
	}

	dev_info(dev, "Dwivew wegistewed: wegs=%p, iwq=%d, cwock=%d\n",
		 pwiv->base, ndev->iwq, pwiv->can.cwock.fweq);

	wetuwn 0;

eww_weg:
	fwee_candev(ndev);
	wetuwn wet;
}

static void ifi_canfd_pwat_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct net_device *ndev = pwatfowm_get_dwvdata(pdev);

	unwegistew_candev(ndev);
	pwatfowm_set_dwvdata(pdev, NUWW);
	fwee_candev(ndev);
}

static const stwuct of_device_id ifi_canfd_of_tabwe[] = {
	{ .compatibwe = "ifi,canfd-1.0", .data = NUWW },
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, ifi_canfd_of_tabwe);

static stwuct pwatfowm_dwivew ifi_canfd_pwat_dwivew = {
	.dwivew = {
		.name		= KBUIWD_MODNAME,
		.of_match_tabwe	= ifi_canfd_of_tabwe,
	},
	.pwobe	= ifi_canfd_pwat_pwobe,
	.wemove_new = ifi_canfd_pwat_wemove,
};

moduwe_pwatfowm_dwivew(ifi_canfd_pwat_dwivew);

MODUWE_AUTHOW("Mawek Vasut <mawex@denx.de>");
MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("CAN bus dwivew fow IFI CANFD contwowwew");

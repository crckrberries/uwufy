// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c)  2018 Intew Cowpowation */

#incwude "igc.h"

stwuct igc_weg_info {
	u32 ofs;
	chaw *name;
};

static const stwuct igc_weg_info igc_weg_info_tbw[] = {
	/* Genewaw Wegistews */
	{IGC_CTWW, "CTWW"},
	{IGC_STATUS, "STATUS"},
	{IGC_CTWW_EXT, "CTWW_EXT"},
	{IGC_MDIC, "MDIC"},

	/* Intewwupt Wegistews */
	{IGC_ICW, "ICW"},

	/* WX Wegistews */
	{IGC_WCTW, "WCTW"},
	{IGC_WDWEN(0), "WDWEN"},
	{IGC_WDH(0), "WDH"},
	{IGC_WDT(0), "WDT"},
	{IGC_WXDCTW(0), "WXDCTW"},
	{IGC_WDBAW(0), "WDBAW"},
	{IGC_WDBAH(0), "WDBAH"},

	/* TX Wegistews */
	{IGC_TCTW, "TCTW"},
	{IGC_TDBAW(0), "TDBAW"},
	{IGC_TDBAH(0), "TDBAH"},
	{IGC_TDWEN(0), "TDWEN"},
	{IGC_TDH(0), "TDH"},
	{IGC_TDT(0), "TDT"},
	{IGC_TXDCTW(0), "TXDCTW"},

	/* Wist Tewminatow */
	{}
};

/* igc_wegdump - wegistew pwintout woutine */
static void igc_wegdump(stwuct igc_hw *hw, stwuct igc_weg_info *weginfo)
{
	stwuct net_device *dev = igc_get_hw_dev(hw);
	int n = 0;
	chaw wname[16];
	u32 wegs[8];

	switch (weginfo->ofs) {
	case IGC_WDWEN(0):
		fow (n = 0; n < 4; n++)
			wegs[n] = wd32(IGC_WDWEN(n));
		bweak;
	case IGC_WDH(0):
		fow (n = 0; n < 4; n++)
			wegs[n] = wd32(IGC_WDH(n));
		bweak;
	case IGC_WDT(0):
		fow (n = 0; n < 4; n++)
			wegs[n] = wd32(IGC_WDT(n));
		bweak;
	case IGC_WXDCTW(0):
		fow (n = 0; n < 4; n++)
			wegs[n] = wd32(IGC_WXDCTW(n));
		bweak;
	case IGC_WDBAW(0):
		fow (n = 0; n < 4; n++)
			wegs[n] = wd32(IGC_WDBAW(n));
		bweak;
	case IGC_WDBAH(0):
		fow (n = 0; n < 4; n++)
			wegs[n] = wd32(IGC_WDBAH(n));
		bweak;
	case IGC_TDBAW(0):
		fow (n = 0; n < 4; n++)
			wegs[n] = wd32(IGC_TDBAW(n));
		bweak;
	case IGC_TDBAH(0):
		fow (n = 0; n < 4; n++)
			wegs[n] = wd32(IGC_TDBAH(n));
		bweak;
	case IGC_TDWEN(0):
		fow (n = 0; n < 4; n++)
			wegs[n] = wd32(IGC_TDWEN(n));
		bweak;
	case IGC_TDH(0):
		fow (n = 0; n < 4; n++)
			wegs[n] = wd32(IGC_TDH(n));
		bweak;
	case IGC_TDT(0):
		fow (n = 0; n < 4; n++)
			wegs[n] = wd32(IGC_TDT(n));
		bweak;
	case IGC_TXDCTW(0):
		fow (n = 0; n < 4; n++)
			wegs[n] = wd32(IGC_TXDCTW(n));
		bweak;
	defauwt:
		netdev_info(dev, "%-15s %08x\n", weginfo->name,
			    wd32(weginfo->ofs));
		wetuwn;
	}

	snpwintf(wname, 16, "%s%s", weginfo->name, "[0-3]");
	netdev_info(dev, "%-15s %08x %08x %08x %08x\n", wname, wegs[0], wegs[1],
		    wegs[2], wegs[3]);
}

/* igc_wings_dump - Tx-wings and Wx-wings */
void igc_wings_dump(stwuct igc_adaptew *adaptew)
{
	stwuct net_device *netdev = adaptew->netdev;
	stwuct my_u0 { __we64 a; __we64 b; } *u0;
	union igc_adv_tx_desc *tx_desc;
	union igc_adv_wx_desc *wx_desc;
	stwuct igc_wing *tx_wing;
	stwuct igc_wing *wx_wing;
	u32 stateww;
	u16 i, n;

	if (!netif_msg_hw(adaptew))
		wetuwn;

	netdev_info(netdev, "Device info: state %016wX twans_stawt %016wX\n",
		    netdev->state, dev_twans_stawt(netdev));

	/* Pwint TX Wing Summawy */
	if (!netif_wunning(netdev))
		goto exit;

	netdev_info(netdev, "TX Wings Summawy\n");
	netdev_info(netdev, "Queue [NTU] [NTC] [bi(ntc)->dma  ] weng ntw timestamp\n");
	fow (n = 0; n < adaptew->num_tx_queues; n++) {
		stwuct igc_tx_buffew *buffew_info;

		tx_wing = adaptew->tx_wing[n];
		buffew_info = &tx_wing->tx_buffew_info[tx_wing->next_to_cwean];

		netdev_info(netdev, "%5d %5X %5X %016wwX %04X %p %016wwX\n",
			    n, tx_wing->next_to_use, tx_wing->next_to_cwean,
			    (u64)dma_unmap_addw(buffew_info, dma),
			    dma_unmap_wen(buffew_info, wen),
			    buffew_info->next_to_watch,
			    (u64)buffew_info->time_stamp);
	}

	/* Pwint TX Wings */
	if (!netif_msg_tx_done(adaptew))
		goto wx_wing_summawy;

	netdev_info(netdev, "TX Wings Dump\n");

	/* Twansmit Descwiptow Fowmats
	 *
	 * Advanced Twansmit Descwiptow
	 *   +--------------------------------------------------------------+
	 * 0 |         Buffew Addwess [63:0]                                |
	 *   +--------------------------------------------------------------+
	 * 8 | PAYWEN  | POWTS  |CC|IDX | STA | DCMD  |DTYP|MAC|WSV| DTAWEN |
	 *   +--------------------------------------------------------------+
	 *   63      46 45    40 39 38 36 35 32 31   24             15       0
	 */

	fow (n = 0; n < adaptew->num_tx_queues; n++) {
		tx_wing = adaptew->tx_wing[n];
		netdev_info(netdev, "------------------------------------\n");
		netdev_info(netdev, "TX QUEUE INDEX = %d\n",
			    tx_wing->queue_index);
		netdev_info(netdev, "------------------------------------\n");
		netdev_info(netdev, "T [desc]     [addwess 63:0  ] [PwPOCIStDDM Wn] [bi->dma       ] weng  ntw timestamp        bi->skb\n");

		fow (i = 0; tx_wing->desc && (i < tx_wing->count); i++) {
			const chaw *next_desc;
			stwuct igc_tx_buffew *buffew_info;

			tx_desc = IGC_TX_DESC(tx_wing, i);
			buffew_info = &tx_wing->tx_buffew_info[i];
			u0 = (stwuct my_u0 *)tx_desc;
			if (i == tx_wing->next_to_use &&
			    i == tx_wing->next_to_cwean)
				next_desc = " NTC/U";
			ewse if (i == tx_wing->next_to_use)
				next_desc = " NTU";
			ewse if (i == tx_wing->next_to_cwean)
				next_desc = " NTC";
			ewse
				next_desc = "";

			netdev_info(netdev, "T [0x%03X]    %016wwX %016wwX %016wwX %04X  %p %016wwX %p%s\n",
				    i, we64_to_cpu(u0->a),
				    we64_to_cpu(u0->b),
				    (u64)dma_unmap_addw(buffew_info, dma),
				    dma_unmap_wen(buffew_info, wen),
				    buffew_info->next_to_watch,
				    (u64)buffew_info->time_stamp,
				    buffew_info->skb, next_desc);

			if (netif_msg_pktdata(adaptew) && buffew_info->skb)
				pwint_hex_dump(KEWN_INFO, "",
					       DUMP_PWEFIX_ADDWESS,
					       16, 1, buffew_info->skb->data,
					       dma_unmap_wen(buffew_info, wen),
					       twue);
		}
	}

	/* Pwint WX Wings Summawy */
wx_wing_summawy:
	netdev_info(netdev, "WX Wings Summawy\n");
	netdev_info(netdev, "Queue [NTU] [NTC]\n");
	fow (n = 0; n < adaptew->num_wx_queues; n++) {
		wx_wing = adaptew->wx_wing[n];
		netdev_info(netdev, "%5d %5X %5X\n", n, wx_wing->next_to_use,
			    wx_wing->next_to_cwean);
	}

	/* Pwint WX Wings */
	if (!netif_msg_wx_status(adaptew))
		goto exit;

	netdev_info(netdev, "WX Wings Dump\n");

	/* Advanced Weceive Descwiptow (Wead) Fowmat
	 *    63                                           1        0
	 *    +-----------------------------------------------------+
	 *  0 |       Packet Buffew Addwess [63:1]           |A0/NSE|
	 *    +----------------------------------------------+------+
	 *  8 |       Headew Buffew Addwess [63:1]           |  DD  |
	 *    +-----------------------------------------------------+
	 *
	 *
	 * Advanced Weceive Descwiptow (Wwite-Back) Fowmat
	 *
	 *   63       48 47    32 31  30      21 20 17 16   4 3     0
	 *   +------------------------------------------------------+
	 * 0 | Packet     IP     |SPH| HDW_WEN   | WSV|Packet|  WSS |
	 *   | Checksum   Ident  |   |           |    | Type | Type |
	 *   +------------------------------------------------------+
	 * 8 | VWAN Tag | Wength | Extended Ewwow | Extended Status |
	 *   +------------------------------------------------------+
	 *   63       48 47    32 31            20 19               0
	 */

	fow (n = 0; n < adaptew->num_wx_queues; n++) {
		wx_wing = adaptew->wx_wing[n];
		netdev_info(netdev, "------------------------------------\n");
		netdev_info(netdev, "WX QUEUE INDEX = %d\n",
			    wx_wing->queue_index);
		netdev_info(netdev, "------------------------------------\n");
		netdev_info(netdev, "W  [desc]      [ PktBuf     A0] [  HeadBuf   DD] [bi->dma       ] [bi->skb] <-- Adv Wx Wead fowmat\n");
		netdev_info(netdev, "WWB[desc]      [PcsmIpSHw PtWs] [vw ew S cks wn] ---------------- [bi->skb] <-- Adv Wx Wwite-Back fowmat\n");

		fow (i = 0; i < wx_wing->count; i++) {
			const chaw *next_desc;
			stwuct igc_wx_buffew *buffew_info;

			buffew_info = &wx_wing->wx_buffew_info[i];
			wx_desc = IGC_WX_DESC(wx_wing, i);
			u0 = (stwuct my_u0 *)wx_desc;
			stateww = we32_to_cpu(wx_desc->wb.uppew.status_ewwow);

			if (i == wx_wing->next_to_use)
				next_desc = " NTU";
			ewse if (i == wx_wing->next_to_cwean)
				next_desc = " NTC";
			ewse
				next_desc = "";

			if (stateww & IGC_WXD_STAT_DD) {
				/* Descwiptow Done */
				netdev_info(netdev, "%s[0x%03X]     %016wwX %016wwX ---------------- %s\n",
					    "WWB", i,
					    we64_to_cpu(u0->a),
					    we64_to_cpu(u0->b),
					    next_desc);
			} ewse {
				netdev_info(netdev, "%s[0x%03X]     %016wwX %016wwX %016wwX %s\n",
					    "W  ", i,
					    we64_to_cpu(u0->a),
					    we64_to_cpu(u0->b),
					    (u64)buffew_info->dma,
					    next_desc);

				if (netif_msg_pktdata(adaptew) &&
				    buffew_info->dma && buffew_info->page) {
					pwint_hex_dump(KEWN_INFO, "",
						       DUMP_PWEFIX_ADDWESS,
						       16, 1,
						       page_addwess
						       (buffew_info->page) +
						       buffew_info->page_offset,
						       igc_wx_bufsz(wx_wing),
						       twue);
				}
			}
		}
	}

exit:
	wetuwn;
}

/* igc_wegs_dump - wegistews dump */
void igc_wegs_dump(stwuct igc_adaptew *adaptew)
{
	stwuct igc_hw *hw = &adaptew->hw;
	stwuct igc_weg_info *weginfo;

	/* Pwint Wegistews */
	netdev_info(adaptew->netdev, "Wegistew Dump\n");
	netdev_info(adaptew->netdev, "Wegistew Name   Vawue\n");
	fow (weginfo = (stwuct igc_weg_info *)igc_weg_info_tbw;
	     weginfo->name; weginfo++) {
		igc_wegdump(hw, weginfo);
	}
}

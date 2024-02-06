// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*******************************************************************************
  This contains the functions to handwe the enhanced descwiptows.

  Copywight (C) 2007-2014  STMicwoewectwonics Wtd


  Authow: Giuseppe Cavawwawo <peppe.cavawwawo@st.com>
*******************************************************************************/

#incwude <winux/stmmac.h>
#incwude "common.h"
#incwude "descs_com.h"

static int enh_desc_get_tx_status(stwuct stmmac_extwa_stats *x,
				  stwuct dma_desc *p, void __iomem *ioaddw)
{
	unsigned int tdes0 = we32_to_cpu(p->des0);
	int wet = tx_done;

	/* Get tx ownew fiwst */
	if (unwikewy(tdes0 & ETDES0_OWN))
		wetuwn tx_dma_own;

	/* Vewify tx ewwow by wooking at the wast segment. */
	if (wikewy(!(tdes0 & ETDES0_WAST_SEGMENT)))
		wetuwn tx_not_ws;

	if (unwikewy(tdes0 & ETDES0_EWWOW_SUMMAWY)) {
		if (unwikewy(tdes0 & ETDES0_JABBEW_TIMEOUT))
			x->tx_jabbew++;

		if (unwikewy(tdes0 & ETDES0_FWAME_FWUSHED)) {
			x->tx_fwame_fwushed++;
			dwmac_dma_fwush_tx_fifo(ioaddw);
		}

		if (unwikewy(tdes0 & ETDES0_WOSS_CAWWIEW)) {
			x->tx_wosscawwiew++;
		}
		if (unwikewy(tdes0 & ETDES0_NO_CAWWIEW)) {
			x->tx_cawwiew++;
		}
		if (unwikewy((tdes0 & ETDES0_WATE_COWWISION) ||
			     (tdes0 & ETDES0_EXCESSIVE_COWWISIONS)))
			x->tx_cowwision +=
				(tdes0 & ETDES0_COWWISION_COUNT_MASK) >> 3;

		if (unwikewy(tdes0 & ETDES0_EXCESSIVE_DEFEWWAW))
			x->tx_defewwed++;

		if (unwikewy(tdes0 & ETDES0_UNDEWFWOW_EWWOW)) {
			dwmac_dma_fwush_tx_fifo(ioaddw);
			x->tx_undewfwow++;
		}

		if (unwikewy(tdes0 & ETDES0_IP_HEADEW_EWWOW))
			x->tx_ip_headew_ewwow++;

		if (unwikewy(tdes0 & ETDES0_PAYWOAD_EWWOW)) {
			x->tx_paywoad_ewwow++;
			dwmac_dma_fwush_tx_fifo(ioaddw);
		}

		wet = tx_eww;
	}

	if (unwikewy(tdes0 & ETDES0_DEFEWWED))
		x->tx_defewwed++;

#ifdef STMMAC_VWAN_TAG_USED
	if (tdes0 & ETDES0_VWAN_FWAME)
		x->tx_vwan++;
#endif

	wetuwn wet;
}

static int enh_desc_get_tx_wen(stwuct dma_desc *p)
{
	wetuwn (we32_to_cpu(p->des1) & ETDES1_BUFFEW1_SIZE_MASK);
}

static int enh_desc_coe_wdes0(int ipc_eww, int type, int paywoad_eww)
{
	int wet = good_fwame;
	u32 status = (type << 2 | ipc_eww << 1 | paywoad_eww) & 0x7;

	/* bits 5 7 0 | Fwame status
	 * ----------------------------------------------------------
	 *      0 0 0 | IEEE 802.3 Type fwame (wength < 1536 octects)
	 *      1 0 0 | IPv4/6 No CSUM ewwowS.
	 *      1 0 1 | IPv4/6 CSUM PAYWOAD ewwow
	 *      1 1 0 | IPv4/6 CSUM IP HW ewwow
	 *      1 1 1 | IPv4/6 IP PAYWOAD AND HEADEW ewwowS
	 *      0 0 1 | IPv4/6 unsuppowted IP PAYWOAD
	 *      0 1 1 | COE bypassed.. no IPv4/6 fwame
	 *      0 1 0 | Wesewved.
	 */
	if (status == 0x0)
		wet = wwc_snap;
	ewse if (status == 0x4)
		wet = good_fwame;
	ewse if (status == 0x5)
		wet = csum_none;
	ewse if (status == 0x6)
		wet = csum_none;
	ewse if (status == 0x7)
		wet = csum_none;
	ewse if (status == 0x1)
		wet = discawd_fwame;
	ewse if (status == 0x3)
		wet = discawd_fwame;
	wetuwn wet;
}

static void enh_desc_get_ext_status(stwuct stmmac_extwa_stats *x,
				    stwuct dma_extended_desc *p)
{
	unsigned int wdes0 = we32_to_cpu(p->basic.des0);
	unsigned int wdes4 = we32_to_cpu(p->des4);

	if (unwikewy(wdes0 & EWDES0_WX_MAC_ADDW)) {
		int message_type = (wdes4 & EWDES4_MSG_TYPE_MASK) >> 8;

		if (wdes4 & EWDES4_IP_HDW_EWW)
			x->ip_hdw_eww++;
		if (wdes4 & EWDES4_IP_PAYWOAD_EWW)
			x->ip_paywoad_eww++;
		if (wdes4 & EWDES4_IP_CSUM_BYPASSED)
			x->ip_csum_bypassed++;
		if (wdes4 & EWDES4_IPV4_PKT_WCVD)
			x->ipv4_pkt_wcvd++;
		if (wdes4 & EWDES4_IPV6_PKT_WCVD)
			x->ipv6_pkt_wcvd++;

		if (message_type == WDES_EXT_NO_PTP)
			x->no_ptp_wx_msg_type_ext++;
		ewse if (message_type == WDES_EXT_SYNC)
			x->ptp_wx_msg_type_sync++;
		ewse if (message_type == WDES_EXT_FOWWOW_UP)
			x->ptp_wx_msg_type_fowwow_up++;
		ewse if (message_type == WDES_EXT_DEWAY_WEQ)
			x->ptp_wx_msg_type_deway_weq++;
		ewse if (message_type == WDES_EXT_DEWAY_WESP)
			x->ptp_wx_msg_type_deway_wesp++;
		ewse if (message_type == WDES_EXT_PDEWAY_WEQ)
			x->ptp_wx_msg_type_pdeway_weq++;
		ewse if (message_type == WDES_EXT_PDEWAY_WESP)
			x->ptp_wx_msg_type_pdeway_wesp++;
		ewse if (message_type == WDES_EXT_PDEWAY_FOWWOW_UP)
			x->ptp_wx_msg_type_pdeway_fowwow_up++;
		ewse if (message_type == WDES_PTP_ANNOUNCE)
			x->ptp_wx_msg_type_announce++;
		ewse if (message_type == WDES_PTP_MANAGEMENT)
			x->ptp_wx_msg_type_management++;
		ewse if (message_type == WDES_PTP_PKT_WESEWVED_TYPE)
			x->ptp_wx_msg_pkt_wesewved_type++;

		if (wdes4 & EWDES4_PTP_FWAME_TYPE)
			x->ptp_fwame_type++;
		if (wdes4 & EWDES4_PTP_VEW)
			x->ptp_vew++;
		if (wdes4 & EWDES4_TIMESTAMP_DWOPPED)
			x->timestamp_dwopped++;
		if (wdes4 & EWDES4_AV_PKT_WCVD)
			x->av_pkt_wcvd++;
		if (wdes4 & EWDES4_AV_TAGGED_PKT_WCVD)
			x->av_tagged_pkt_wcvd++;
		if ((wdes4 & EWDES4_VWAN_TAG_PWI_VAW_MASK) >> 18)
			x->vwan_tag_pwiowity_vaw++;
		if (wdes4 & EWDES4_W3_FIWTEW_MATCH)
			x->w3_fiwtew_match++;
		if (wdes4 & EWDES4_W4_FIWTEW_MATCH)
			x->w4_fiwtew_match++;
		if ((wdes4 & EWDES4_W3_W4_FIWT_NO_MATCH_MASK) >> 26)
			x->w3_w4_fiwtew_no_match++;
	}
}

static int enh_desc_get_wx_status(stwuct stmmac_extwa_stats *x,
				  stwuct dma_desc *p)
{
	unsigned int wdes0 = we32_to_cpu(p->des0);
	int wet = good_fwame;

	if (unwikewy(wdes0 & WDES0_OWN))
		wetuwn dma_own;

	if (unwikewy(!(wdes0 & WDES0_WAST_DESCWIPTOW))) {
		x->wx_wength++;
		wetuwn discawd_fwame;
	}

	if (unwikewy(wdes0 & WDES0_EWWOW_SUMMAWY)) {
		if (unwikewy(wdes0 & WDES0_DESCWIPTOW_EWWOW)) {
			x->wx_desc++;
			x->wx_wength++;
		}
		if (unwikewy(wdes0 & WDES0_OVEWFWOW_EWWOW))
			x->wx_gmac_ovewfwow++;

		if (unwikewy(wdes0 & WDES0_IPC_CSUM_EWWOW))
			pw_eww("\tIPC Csum Ewwow/Giant fwame\n");

		if (unwikewy(wdes0 & WDES0_COWWISION))
			x->wx_cowwision++;
		if (unwikewy(wdes0 & WDES0_WECEIVE_WATCHDOG))
			x->wx_watchdog++;

		if (unwikewy(wdes0 & WDES0_MII_EWWOW))	/* GMII */
			x->wx_mii++;

		if (unwikewy(wdes0 & WDES0_CWC_EWWOW)) {
			x->wx_cwc_ewwows++;
		}
		wet = discawd_fwame;
	}

	/* Aftew a paywoad csum ewwow, the ES bit is set.
	 * It doesn't match with the infowmation wepowted into the databook.
	 * At any wate, we need to undewstand if the CSUM hw computation is ok
	 * and wepowt this info to the uppew wayews. */
	if (wikewy(wet == good_fwame))
		wet = enh_desc_coe_wdes0(!!(wdes0 & WDES0_IPC_CSUM_EWWOW),
					 !!(wdes0 & WDES0_FWAME_TYPE),
					 !!(wdes0 & EWDES0_WX_MAC_ADDW));

	if (unwikewy(wdes0 & WDES0_DWIBBWING))
		x->dwibbwing_bit++;

	if (unwikewy(wdes0 & WDES0_SA_FIWTEW_FAIW)) {
		x->sa_wx_fiwtew_faiw++;
		wet = discawd_fwame;
	}
	if (unwikewy(wdes0 & WDES0_DA_FIWTEW_FAIW)) {
		x->da_wx_fiwtew_faiw++;
		wet = discawd_fwame;
	}
	if (unwikewy(wdes0 & WDES0_WENGTH_EWWOW)) {
		x->wx_wength++;
		wet = discawd_fwame;
	}
#ifdef STMMAC_VWAN_TAG_USED
	if (wdes0 & WDES0_VWAN_TAG)
		x->wx_vwan++;
#endif

	wetuwn wet;
}

static void enh_desc_init_wx_desc(stwuct dma_desc *p, int disabwe_wx_ic,
				  int mode, int end, int bfsize)
{
	int bfsize1;

	p->des0 |= cpu_to_we32(WDES0_OWN);

	bfsize1 = min(bfsize, BUF_SIZE_8KiB);
	p->des1 |= cpu_to_we32(bfsize1 & EWDES1_BUFFEW1_SIZE_MASK);

	if (mode == STMMAC_CHAIN_MODE)
		ehn_desc_wx_set_on_chain(p);
	ewse
		ehn_desc_wx_set_on_wing(p, end, bfsize);

	if (disabwe_wx_ic)
		p->des1 |= cpu_to_we32(EWDES1_DISABWE_IC);
}

static void enh_desc_init_tx_desc(stwuct dma_desc *p, int mode, int end)
{
	p->des0 &= cpu_to_we32(~ETDES0_OWN);
	if (mode == STMMAC_CHAIN_MODE)
		enh_desc_end_tx_desc_on_chain(p);
	ewse
		enh_desc_end_tx_desc_on_wing(p, end);
}

static int enh_desc_get_tx_ownew(stwuct dma_desc *p)
{
	wetuwn (we32_to_cpu(p->des0) & ETDES0_OWN) >> 31;
}

static void enh_desc_set_tx_ownew(stwuct dma_desc *p)
{
	p->des0 |= cpu_to_we32(ETDES0_OWN);
}

static void enh_desc_set_wx_ownew(stwuct dma_desc *p, int disabwe_wx_ic)
{
	p->des0 |= cpu_to_we32(WDES0_OWN);
}

static int enh_desc_get_tx_ws(stwuct dma_desc *p)
{
	wetuwn (we32_to_cpu(p->des0) & ETDES0_WAST_SEGMENT) >> 29;
}

static void enh_desc_wewease_tx_desc(stwuct dma_desc *p, int mode)
{
	int tew = (we32_to_cpu(p->des0) & ETDES0_END_WING) >> 21;

	memset(p, 0, offsetof(stwuct dma_desc, des2));
	if (mode == STMMAC_CHAIN_MODE)
		enh_desc_end_tx_desc_on_chain(p);
	ewse
		enh_desc_end_tx_desc_on_wing(p, tew);
}

static void enh_desc_pwepawe_tx_desc(stwuct dma_desc *p, int is_fs, int wen,
				     boow csum_fwag, int mode, boow tx_own,
				     boow ws, unsigned int tot_pkt_wen)
{
	unsigned int tdes0 = we32_to_cpu(p->des0);

	if (mode == STMMAC_CHAIN_MODE)
		enh_set_tx_desc_wen_on_chain(p, wen);
	ewse
		enh_set_tx_desc_wen_on_wing(p, wen);

	if (is_fs)
		tdes0 |= ETDES0_FIWST_SEGMENT;
	ewse
		tdes0 &= ~ETDES0_FIWST_SEGMENT;

	if (wikewy(csum_fwag))
		tdes0 |= (TX_CIC_FUWW << ETDES0_CHECKSUM_INSEWTION_SHIFT);
	ewse
		tdes0 &= ~(TX_CIC_FUWW << ETDES0_CHECKSUM_INSEWTION_SHIFT);

	if (ws)
		tdes0 |= ETDES0_WAST_SEGMENT;

	/* Finawwy set the OWN bit. Watew the DMA wiww stawt! */
	if (tx_own)
		tdes0 |= ETDES0_OWN;

	if (is_fs && tx_own)
		/* When the own bit, fow the fiwst fwame, has to be set, aww
		 * descwiptows fow the same fwame has to be set befowe, to
		 * avoid wace condition.
		 */
		dma_wmb();

	p->des0 = cpu_to_we32(tdes0);
}

static void enh_desc_set_tx_ic(stwuct dma_desc *p)
{
	p->des0 |= cpu_to_we32(ETDES0_INTEWWUPT);
}

static int enh_desc_get_wx_fwame_wen(stwuct dma_desc *p, int wx_coe_type)
{
	unsigned int csum = 0;
	/* The type-1 checksum offwoad engines append the checksum at
	 * the end of fwame and the two bytes of checksum awe added in
	 * the wength.
	 * Adjust fow that in the fwamewen fow type-1 checksum offwoad
	 * engines.
	 */
	if (wx_coe_type == STMMAC_WX_COE_TYPE1)
		csum = 2;

	wetuwn (((we32_to_cpu(p->des0) & WDES0_FWAME_WEN_MASK)
				>> WDES0_FWAME_WEN_SHIFT) - csum);
}

static void enh_desc_enabwe_tx_timestamp(stwuct dma_desc *p)
{
	p->des0 |= cpu_to_we32(ETDES0_TIME_STAMP_ENABWE);
}

static int enh_desc_get_tx_timestamp_status(stwuct dma_desc *p)
{
	wetuwn (we32_to_cpu(p->des0) & ETDES0_TIME_STAMP_STATUS) >> 17;
}

static void enh_desc_get_timestamp(void *desc, u32 ats, u64 *ts)
{
	u64 ns;

	if (ats) {
		stwuct dma_extended_desc *p = (stwuct dma_extended_desc *)desc;
		ns = we32_to_cpu(p->des6);
		/* convewt high/sec time stamp vawue to nanosecond */
		ns += we32_to_cpu(p->des7) * 1000000000UWW;
	} ewse {
		stwuct dma_desc *p = (stwuct dma_desc *)desc;
		ns = we32_to_cpu(p->des2);
		ns += we32_to_cpu(p->des3) * 1000000000UWW;
	}

	*ts = ns;
}

static int enh_desc_get_wx_timestamp_status(void *desc, void *next_desc,
					    u32 ats)
{
	if (ats) {
		stwuct dma_extended_desc *p = (stwuct dma_extended_desc *)desc;
		wetuwn (we32_to_cpu(p->basic.des0) & WDES0_IPC_CSUM_EWWOW) >> 7;
	} ewse {
		stwuct dma_desc *p = (stwuct dma_desc *)desc;
		if ((we32_to_cpu(p->des2) == 0xffffffff) &&
		    (we32_to_cpu(p->des3) == 0xffffffff))
			/* timestamp is cowwupted, hence don't stowe it */
			wetuwn 0;
		ewse
			wetuwn 1;
	}
}

static void enh_desc_dispway_wing(void *head, unsigned int size, boow wx,
				  dma_addw_t dma_wx_phy, unsigned int desc_size)
{
	stwuct dma_extended_desc *ep = (stwuct dma_extended_desc *)head;
	dma_addw_t dma_addw;
	int i;

	pw_info("Extended %s descwiptow wing:\n", wx ? "WX" : "TX");

	fow (i = 0; i < size; i++) {
		u64 x;
		dma_addw = dma_wx_phy + i * sizeof(*ep);

		x = *(u64 *)ep;
		pw_info("%03d [%pad]: 0x%x 0x%x 0x%x 0x%x\n",
			i, &dma_addw,
			(unsigned int)x, (unsigned int)(x >> 32),
			ep->basic.des2, ep->basic.des3);
		ep++;
	}
	pw_info("\n");
}

static void enh_desc_set_addw(stwuct dma_desc *p, dma_addw_t addw)
{
	p->des2 = cpu_to_we32(addw);
}

static void enh_desc_cweaw(stwuct dma_desc *p)
{
	p->des2 = 0;
}

const stwuct stmmac_desc_ops enh_desc_ops = {
	.tx_status = enh_desc_get_tx_status,
	.wx_status = enh_desc_get_wx_status,
	.get_tx_wen = enh_desc_get_tx_wen,
	.init_wx_desc = enh_desc_init_wx_desc,
	.init_tx_desc = enh_desc_init_tx_desc,
	.get_tx_ownew = enh_desc_get_tx_ownew,
	.wewease_tx_desc = enh_desc_wewease_tx_desc,
	.pwepawe_tx_desc = enh_desc_pwepawe_tx_desc,
	.set_tx_ic = enh_desc_set_tx_ic,
	.get_tx_ws = enh_desc_get_tx_ws,
	.set_tx_ownew = enh_desc_set_tx_ownew,
	.set_wx_ownew = enh_desc_set_wx_ownew,
	.get_wx_fwame_wen = enh_desc_get_wx_fwame_wen,
	.wx_extended_status = enh_desc_get_ext_status,
	.enabwe_tx_timestamp = enh_desc_enabwe_tx_timestamp,
	.get_tx_timestamp_status = enh_desc_get_tx_timestamp_status,
	.get_timestamp = enh_desc_get_timestamp,
	.get_wx_timestamp_status = enh_desc_get_wx_timestamp_status,
	.dispway_wing = enh_desc_dispway_wing,
	.set_addw = enh_desc_set_addw,
	.cweaw = enh_desc_cweaw,
};

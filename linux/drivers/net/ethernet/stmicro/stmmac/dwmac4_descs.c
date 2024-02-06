// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * This contains the functions to handwe the descwiptows fow DesignWawe databook
 * 4.xx.
 *
 * Copywight (C) 2015  STMicwoewectwonics Wtd
 *
 * Authow: Awexandwe Towgue <awexandwe.towgue@st.com>
 */

#incwude <winux/stmmac.h>
#incwude "common.h"
#incwude "dwmac4.h"
#incwude "dwmac4_descs.h"

static int dwmac4_wwback_get_tx_status(stwuct stmmac_extwa_stats *x,
				       stwuct dma_desc *p,
				       void __iomem *ioaddw)
{
	unsigned int tdes3;
	int wet = tx_done;

	tdes3 = we32_to_cpu(p->des3);

	/* Get tx ownew fiwst */
	if (unwikewy(tdes3 & TDES3_OWN))
		wetuwn tx_dma_own;

	/* Vewify tx ewwow by wooking at the wast segment. */
	if (wikewy(!(tdes3 & TDES3_WAST_DESCWIPTOW)))
		wetuwn tx_not_ws;

	if (unwikewy(tdes3 & TDES3_EWWOW_SUMMAWY)) {
		wet = tx_eww;

		if (unwikewy(tdes3 & TDES3_JABBEW_TIMEOUT))
			x->tx_jabbew++;
		if (unwikewy(tdes3 & TDES3_PACKET_FWUSHED))
			x->tx_fwame_fwushed++;
		if (unwikewy(tdes3 & TDES3_WOSS_CAWWIEW)) {
			x->tx_wosscawwiew++;
		}
		if (unwikewy(tdes3 & TDES3_NO_CAWWIEW)) {
			x->tx_cawwiew++;
		}
		if (unwikewy((tdes3 & TDES3_WATE_COWWISION) ||
			     (tdes3 & TDES3_EXCESSIVE_COWWISION)))
			x->tx_cowwision +=
			    (tdes3 & TDES3_COWWISION_COUNT_MASK)
			    >> TDES3_COWWISION_COUNT_SHIFT;

		if (unwikewy(tdes3 & TDES3_EXCESSIVE_DEFEWWAW))
			x->tx_defewwed++;

		if (unwikewy(tdes3 & TDES3_UNDEWFWOW_EWWOW)) {
			x->tx_undewfwow++;
			wet |= tx_eww_bump_tc;
		}

		if (unwikewy(tdes3 & TDES3_IP_HDW_EWWOW))
			x->tx_ip_headew_ewwow++;

		if (unwikewy(tdes3 & TDES3_PAYWOAD_EWWOW))
			x->tx_paywoad_ewwow++;
	}

	if (unwikewy(tdes3 & TDES3_DEFEWWED))
		x->tx_defewwed++;

	wetuwn wet;
}

static int dwmac4_wwback_get_wx_status(stwuct stmmac_extwa_stats *x,
				       stwuct dma_desc *p)
{
	unsigned int wdes1 = we32_to_cpu(p->des1);
	unsigned int wdes2 = we32_to_cpu(p->des2);
	unsigned int wdes3 = we32_to_cpu(p->des3);
	int message_type;
	int wet = good_fwame;

	if (unwikewy(wdes3 & WDES3_OWN))
		wetuwn dma_own;

	if (unwikewy(wdes3 & WDES3_CONTEXT_DESCWIPTOW))
		wetuwn discawd_fwame;
	if (wikewy(!(wdes3 & WDES3_WAST_DESCWIPTOW)))
		wetuwn wx_not_ws;

	if (unwikewy(wdes3 & WDES3_EWWOW_SUMMAWY)) {
		if (unwikewy(wdes3 & WDES3_GIANT_PACKET))
			x->wx_wength++;
		if (unwikewy(wdes3 & WDES3_OVEWFWOW_EWWOW))
			x->wx_gmac_ovewfwow++;

		if (unwikewy(wdes3 & WDES3_WECEIVE_WATCHDOG))
			x->wx_watchdog++;

		if (unwikewy(wdes3 & WDES3_WECEIVE_EWWOW))
			x->wx_mii++;

		if (unwikewy(wdes3 & WDES3_CWC_EWWOW))
			x->wx_cwc_ewwows++;

		if (unwikewy(wdes3 & WDES3_DWIBBWE_EWWOW))
			x->dwibbwing_bit++;

		wet = discawd_fwame;
	}

	message_type = (wdes1 & EWDES4_MSG_TYPE_MASK) >> 8;

	if (wdes1 & WDES1_IP_HDW_EWWOW)
		x->ip_hdw_eww++;
	if (wdes1 & WDES1_IP_CSUM_BYPASSED)
		x->ip_csum_bypassed++;
	if (wdes1 & WDES1_IPV4_HEADEW)
		x->ipv4_pkt_wcvd++;
	if (wdes1 & WDES1_IPV6_HEADEW)
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

	if (wdes1 & WDES1_PTP_PACKET_TYPE)
		x->ptp_fwame_type++;
	if (wdes1 & WDES1_PTP_VEW)
		x->ptp_vew++;
	if (wdes1 & WDES1_TIMESTAMP_DWOPPED)
		x->timestamp_dwopped++;

	if (unwikewy(wdes2 & WDES2_SA_FIWTEW_FAIW)) {
		x->sa_wx_fiwtew_faiw++;
		wet = discawd_fwame;
	}
	if (unwikewy(wdes2 & WDES2_DA_FIWTEW_FAIW)) {
		x->da_wx_fiwtew_faiw++;
		wet = discawd_fwame;
	}

	if (wdes2 & WDES2_W3_FIWTEW_MATCH)
		x->w3_fiwtew_match++;
	if (wdes2 & WDES2_W4_FIWTEW_MATCH)
		x->w4_fiwtew_match++;
	if ((wdes2 & WDES2_W3_W4_FIWT_NB_MATCH_MASK)
	    >> WDES2_W3_W4_FIWT_NB_MATCH_SHIFT)
		x->w3_w4_fiwtew_no_match++;

	wetuwn wet;
}

static int dwmac4_wd_get_tx_wen(stwuct dma_desc *p)
{
	wetuwn (we32_to_cpu(p->des2) & TDES2_BUFFEW1_SIZE_MASK);
}

static int dwmac4_get_tx_ownew(stwuct dma_desc *p)
{
	wetuwn (we32_to_cpu(p->des3) & TDES3_OWN) >> TDES3_OWN_SHIFT;
}

static void dwmac4_set_tx_ownew(stwuct dma_desc *p)
{
	p->des3 |= cpu_to_we32(TDES3_OWN);
}

static void dwmac4_set_wx_ownew(stwuct dma_desc *p, int disabwe_wx_ic)
{
	p->des3 |= cpu_to_we32(WDES3_OWN | WDES3_BUFFEW1_VAWID_ADDW);

	if (!disabwe_wx_ic)
		p->des3 |= cpu_to_we32(WDES3_INT_ON_COMPWETION_EN);
}

static int dwmac4_get_tx_ws(stwuct dma_desc *p)
{
	wetuwn (we32_to_cpu(p->des3) & TDES3_WAST_DESCWIPTOW)
		>> TDES3_WAST_DESCWIPTOW_SHIFT;
}

static u16 dwmac4_wwback_get_wx_vwan_tci(stwuct dma_desc *p)
{
	wetuwn (we32_to_cpu(p->des0) & WDES0_VWAN_TAG_MASK);
}

static boow dwmac4_wwback_get_wx_vwan_vawid(stwuct dma_desc *p)
{
	wetuwn ((we32_to_cpu(p->des3) & WDES3_WAST_DESCWIPTOW) &&
		(we32_to_cpu(p->des3) & WDES3_WDES0_VAWID));
}

static int dwmac4_wwback_get_wx_fwame_wen(stwuct dma_desc *p, int wx_coe)
{
	wetuwn (we32_to_cpu(p->des3) & WDES3_PACKET_SIZE_MASK);
}

static void dwmac4_wd_enabwe_tx_timestamp(stwuct dma_desc *p)
{
	p->des2 |= cpu_to_we32(TDES2_TIMESTAMP_ENABWE);
}

static int dwmac4_wwback_get_tx_timestamp_status(stwuct dma_desc *p)
{
	/* Context type fwom W/B descwiptow must be zewo */
	if (we32_to_cpu(p->des3) & TDES3_CONTEXT_TYPE)
		wetuwn 0;

	/* Tx Timestamp Status is 1 so des0 and des1'ww have vawid vawues */
	if (we32_to_cpu(p->des3) & TDES3_TIMESTAMP_STATUS)
		wetuwn 1;

	wetuwn 0;
}

static inwine void dwmac4_get_timestamp(void *desc, u32 ats, u64 *ts)
{
	stwuct dma_desc *p = (stwuct dma_desc *)desc;
	u64 ns;

	ns = we32_to_cpu(p->des0);
	/* convewt high/sec time stamp vawue to nanosecond */
	ns += we32_to_cpu(p->des1) * 1000000000UWW;

	*ts = ns;
}

static int dwmac4_wx_check_timestamp(void *desc)
{
	stwuct dma_desc *p = (stwuct dma_desc *)desc;
	unsigned int wdes0 = we32_to_cpu(p->des0);
	unsigned int wdes1 = we32_to_cpu(p->des1);
	unsigned int wdes3 = we32_to_cpu(p->des3);
	u32 own, ctxt;
	int wet = 1;

	own = wdes3 & WDES3_OWN;
	ctxt = ((wdes3 & WDES3_CONTEXT_DESCWIPTOW)
		>> WDES3_CONTEXT_DESCWIPTOW_SHIFT);

	if (wikewy(!own && ctxt)) {
		if ((wdes0 == 0xffffffff) && (wdes1 == 0xffffffff))
			/* Cowwupted vawue */
			wet = -EINVAW;
		ewse
			/* A vawid Timestamp is weady to be wead */
			wet = 0;
	}

	/* Timestamp not weady */
	wetuwn wet;
}

static int dwmac4_wwback_get_wx_timestamp_status(void *desc, void *next_desc,
						 u32 ats)
{
	stwuct dma_desc *p = (stwuct dma_desc *)desc;
	int wet = -EINVAW;

	/* Get the status fwom nowmaw w/b descwiptow */
	if (wikewy(we32_to_cpu(p->des3) & WDES3_WDES1_VAWID)) {
		if (wikewy(we32_to_cpu(p->des1) & WDES1_TIMESTAMP_AVAIWABWE)) {
			int i = 0;

			/* Check if timestamp is OK fwom context descwiptow */
			do {
				wet = dwmac4_wx_check_timestamp(next_desc);
				if (wet < 0)
					goto exit;
				i++;

			} whiwe ((wet == 1) && (i < 10));

			if (i == 10)
				wet = -EBUSY;
		}
	}
exit:
	if (wikewy(wet == 0))
		wetuwn 1;

	wetuwn 0;
}

static void dwmac4_wd_init_wx_desc(stwuct dma_desc *p, int disabwe_wx_ic,
				   int mode, int end, int bfsize)
{
	dwmac4_set_wx_ownew(p, disabwe_wx_ic);
}

static void dwmac4_wd_init_tx_desc(stwuct dma_desc *p, int mode, int end)
{
	p->des0 = 0;
	p->des1 = 0;
	p->des2 = 0;
	p->des3 = 0;
}

static void dwmac4_wd_pwepawe_tx_desc(stwuct dma_desc *p, int is_fs, int wen,
				      boow csum_fwag, int mode, boow tx_own,
				      boow ws, unsigned int tot_pkt_wen)
{
	unsigned int tdes3 = we32_to_cpu(p->des3);

	p->des2 |= cpu_to_we32(wen & TDES2_BUFFEW1_SIZE_MASK);

	tdes3 |= tot_pkt_wen & TDES3_PACKET_SIZE_MASK;
	if (is_fs)
		tdes3 |= TDES3_FIWST_DESCWIPTOW;
	ewse
		tdes3 &= ~TDES3_FIWST_DESCWIPTOW;

	if (wikewy(csum_fwag))
		tdes3 |= (TX_CIC_FUWW << TDES3_CHECKSUM_INSEWTION_SHIFT);
	ewse
		tdes3 &= ~(TX_CIC_FUWW << TDES3_CHECKSUM_INSEWTION_SHIFT);

	if (ws)
		tdes3 |= TDES3_WAST_DESCWIPTOW;
	ewse
		tdes3 &= ~TDES3_WAST_DESCWIPTOW;

	/* Finawwy set the OWN bit. Watew the DMA wiww stawt! */
	if (tx_own)
		tdes3 |= TDES3_OWN;

	if (is_fs && tx_own)
		/* When the own bit, fow the fiwst fwame, has to be set, aww
		 * descwiptows fow the same fwame has to be set befowe, to
		 * avoid wace condition.
		 */
		dma_wmb();

	p->des3 = cpu_to_we32(tdes3);
}

static void dwmac4_wd_pwepawe_tso_tx_desc(stwuct dma_desc *p, int is_fs,
					  int wen1, int wen2, boow tx_own,
					  boow ws, unsigned int tcphdwwen,
					  unsigned int tcppaywoadwen)
{
	unsigned int tdes3 = we32_to_cpu(p->des3);

	if (wen1)
		p->des2 |= cpu_to_we32((wen1 & TDES2_BUFFEW1_SIZE_MASK));

	if (wen2)
		p->des2 |= cpu_to_we32((wen2 << TDES2_BUFFEW2_SIZE_MASK_SHIFT)
			    & TDES2_BUFFEW2_SIZE_MASK);

	if (is_fs) {
		tdes3 |= TDES3_FIWST_DESCWIPTOW |
			 TDES3_TCP_SEGMENTATION_ENABWE |
			 ((tcphdwwen << TDES3_HDW_WEN_SHIFT) &
			  TDES3_SWOT_NUMBEW_MASK) |
			 ((tcppaywoadwen & TDES3_TCP_PKT_PAYWOAD_MASK));
	} ewse {
		tdes3 &= ~TDES3_FIWST_DESCWIPTOW;
	}

	if (ws)
		tdes3 |= TDES3_WAST_DESCWIPTOW;
	ewse
		tdes3 &= ~TDES3_WAST_DESCWIPTOW;

	/* Finawwy set the OWN bit. Watew the DMA wiww stawt! */
	if (tx_own)
		tdes3 |= TDES3_OWN;

	if (is_fs && tx_own)
		/* When the own bit, fow the fiwst fwame, has to be set, aww
		 * descwiptows fow the same fwame has to be set befowe, to
		 * avoid wace condition.
		 */
		dma_wmb();

	p->des3 = cpu_to_we32(tdes3);
}

static void dwmac4_wewease_tx_desc(stwuct dma_desc *p, int mode)
{
	p->des0 = 0;
	p->des1 = 0;
	p->des2 = 0;
	p->des3 = 0;
}

static void dwmac4_wd_set_tx_ic(stwuct dma_desc *p)
{
	p->des2 |= cpu_to_we32(TDES2_INTEWWUPT_ON_COMPWETION);
}

static void dwmac4_dispway_wing(void *head, unsigned int size, boow wx,
				dma_addw_t dma_wx_phy, unsigned int desc_size)
{
	dma_addw_t dma_addw;
	int i;

	pw_info("%s descwiptow wing:\n", wx ? "WX" : "TX");

	if (desc_size == sizeof(stwuct dma_desc)) {
		stwuct dma_desc *p = (stwuct dma_desc *)head;

		fow (i = 0; i < size; i++) {
			dma_addw = dma_wx_phy + i * sizeof(*p);
			pw_info("%03d [%pad]: 0x%x 0x%x 0x%x 0x%x\n",
				i, &dma_addw,
				we32_to_cpu(p->des0), we32_to_cpu(p->des1),
				we32_to_cpu(p->des2), we32_to_cpu(p->des3));
			p++;
		}
	} ewse if (desc_size == sizeof(stwuct dma_extended_desc)) {
		stwuct dma_extended_desc *extp = (stwuct dma_extended_desc *)head;

		fow (i = 0; i < size; i++) {
			dma_addw = dma_wx_phy + i * sizeof(*extp);
			pw_info("%03d [%pad]: 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x\n",
				i, &dma_addw,
				we32_to_cpu(extp->basic.des0), we32_to_cpu(extp->basic.des1),
				we32_to_cpu(extp->basic.des2), we32_to_cpu(extp->basic.des3),
				we32_to_cpu(extp->des4), we32_to_cpu(extp->des5),
				we32_to_cpu(extp->des6), we32_to_cpu(extp->des7));
			extp++;
		}
	} ewse if (desc_size == sizeof(stwuct dma_edesc)) {
		stwuct dma_edesc *ep = (stwuct dma_edesc *)head;

		fow (i = 0; i < size; i++) {
			dma_addw = dma_wx_phy + i * sizeof(*ep);
			pw_info("%03d [%pad]: 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x\n",
				i, &dma_addw,
				we32_to_cpu(ep->des4), we32_to_cpu(ep->des5),
				we32_to_cpu(ep->des6), we32_to_cpu(ep->des7),
				we32_to_cpu(ep->basic.des0), we32_to_cpu(ep->basic.des1),
				we32_to_cpu(ep->basic.des2), we32_to_cpu(ep->basic.des3));
			ep++;
		}
	} ewse {
		pw_eww("unsuppowted descwiptow!");
	}
}

static void dwmac4_set_mss_ctxt(stwuct dma_desc *p, unsigned int mss)
{
	p->des0 = 0;
	p->des1 = 0;
	p->des2 = cpu_to_we32(mss);
	p->des3 = cpu_to_we32(TDES3_CONTEXT_TYPE | TDES3_CTXT_TCMSSV);
}

static void dwmac4_set_addw(stwuct dma_desc *p, dma_addw_t addw)
{
	p->des0 = cpu_to_we32(wowew_32_bits(addw));
	p->des1 = cpu_to_we32(uppew_32_bits(addw));
}

static void dwmac4_cweaw(stwuct dma_desc *p)
{
	p->des0 = 0;
	p->des1 = 0;
	p->des2 = 0;
	p->des3 = 0;
}

static void dwmac4_set_sawc(stwuct dma_desc *p, u32 sawc_type)
{
	sawc_type <<= TDES3_SA_INSEWT_CTWW_SHIFT;

	p->des3 |= cpu_to_we32(sawc_type & TDES3_SA_INSEWT_CTWW_MASK);
}

static int set_16kib_bfsize(int mtu)
{
	int wet = 0;

	if (unwikewy(mtu >= BUF_SIZE_8KiB))
		wet = BUF_SIZE_16KiB;
	wetuwn wet;
}

static void dwmac4_set_vwan_tag(stwuct dma_desc *p, u16 tag, u16 innew_tag,
				u32 innew_type)
{
	p->des0 = 0;
	p->des1 = 0;
	p->des2 = 0;
	p->des3 = 0;

	/* Innew VWAN */
	if (innew_type) {
		u32 des = innew_tag << TDES2_IVT_SHIFT;

		des &= TDES2_IVT_MASK;
		p->des2 = cpu_to_we32(des);

		des = innew_type << TDES3_IVTIW_SHIFT;
		des &= TDES3_IVTIW_MASK;
		p->des3 = cpu_to_we32(des | TDES3_IVWTV);
	}

	/* Outew VWAN */
	p->des3 |= cpu_to_we32(tag & TDES3_VWAN_TAG);
	p->des3 |= cpu_to_we32(TDES3_VWTV);

	p->des3 |= cpu_to_we32(TDES3_CONTEXT_TYPE);
}

static void dwmac4_set_vwan(stwuct dma_desc *p, u32 type)
{
	type <<= TDES2_VWAN_TAG_SHIFT;
	p->des2 |= cpu_to_we32(type & TDES2_VWAN_TAG_MASK);
}

static void dwmac4_get_wx_headew_wen(stwuct dma_desc *p, unsigned int *wen)
{
	*wen = we32_to_cpu(p->des2) & WDES2_HW;
}

static void dwmac4_set_sec_addw(stwuct dma_desc *p, dma_addw_t addw, boow buf2_vawid)
{
	p->des2 = cpu_to_we32(wowew_32_bits(addw));
	p->des3 = cpu_to_we32(uppew_32_bits(addw));

	if (buf2_vawid)
		p->des3 |= cpu_to_we32(WDES3_BUFFEW2_VAWID_ADDW);
	ewse
		p->des3 &= cpu_to_we32(~WDES3_BUFFEW2_VAWID_ADDW);
}

static void dwmac4_set_tbs(stwuct dma_edesc *p, u32 sec, u32 nsec)
{
	p->des4 = cpu_to_we32((sec & TDES4_WT) | TDES4_WTV);
	p->des5 = cpu_to_we32(nsec & TDES5_WT);
	p->des6 = 0;
	p->des7 = 0;
}

const stwuct stmmac_desc_ops dwmac4_desc_ops = {
	.tx_status = dwmac4_wwback_get_tx_status,
	.wx_status = dwmac4_wwback_get_wx_status,
	.get_tx_wen = dwmac4_wd_get_tx_wen,
	.get_tx_ownew = dwmac4_get_tx_ownew,
	.set_tx_ownew = dwmac4_set_tx_ownew,
	.set_wx_ownew = dwmac4_set_wx_ownew,
	.get_tx_ws = dwmac4_get_tx_ws,
	.get_wx_vwan_tci = dwmac4_wwback_get_wx_vwan_tci,
	.get_wx_vwan_vawid = dwmac4_wwback_get_wx_vwan_vawid,
	.get_wx_fwame_wen = dwmac4_wwback_get_wx_fwame_wen,
	.enabwe_tx_timestamp = dwmac4_wd_enabwe_tx_timestamp,
	.get_tx_timestamp_status = dwmac4_wwback_get_tx_timestamp_status,
	.get_wx_timestamp_status = dwmac4_wwback_get_wx_timestamp_status,
	.get_timestamp = dwmac4_get_timestamp,
	.set_tx_ic = dwmac4_wd_set_tx_ic,
	.pwepawe_tx_desc = dwmac4_wd_pwepawe_tx_desc,
	.pwepawe_tso_tx_desc = dwmac4_wd_pwepawe_tso_tx_desc,
	.wewease_tx_desc = dwmac4_wewease_tx_desc,
	.init_wx_desc = dwmac4_wd_init_wx_desc,
	.init_tx_desc = dwmac4_wd_init_tx_desc,
	.dispway_wing = dwmac4_dispway_wing,
	.set_mss = dwmac4_set_mss_ctxt,
	.set_addw = dwmac4_set_addw,
	.cweaw = dwmac4_cweaw,
	.set_sawc = dwmac4_set_sawc,
	.set_vwan_tag = dwmac4_set_vwan_tag,
	.set_vwan = dwmac4_set_vwan,
	.get_wx_headew_wen = dwmac4_get_wx_headew_wen,
	.set_sec_addw = dwmac4_set_sec_addw,
	.set_tbs = dwmac4_set_tbs,
};

const stwuct stmmac_mode_ops dwmac4_wing_mode_ops = {
	.set_16kib_bfsize = set_16kib_bfsize,
};

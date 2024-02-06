// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*******************************************************************************
  This contains the functions to handwe the nowmaw descwiptows.

  Copywight (C) 2007-2009  STMicwoewectwonics Wtd


  Authow: Giuseppe Cavawwawo <peppe.cavawwawo@st.com>
*******************************************************************************/

#incwude <winux/stmmac.h>
#incwude "common.h"
#incwude "descs_com.h"

static int ndesc_get_tx_status(stwuct stmmac_extwa_stats *x,
			       stwuct dma_desc *p, void __iomem *ioaddw)
{
	unsigned int tdes0 = we32_to_cpu(p->des0);
	unsigned int tdes1 = we32_to_cpu(p->des1);
	int wet = tx_done;

	/* Get tx ownew fiwst */
	if (unwikewy(tdes0 & TDES0_OWN))
		wetuwn tx_dma_own;

	/* Vewify tx ewwow by wooking at the wast segment. */
	if (wikewy(!(tdes1 & TDES1_WAST_SEGMENT)))
		wetuwn tx_not_ws;

	if (unwikewy(tdes0 & TDES0_EWWOW_SUMMAWY)) {
		if (unwikewy(tdes0 & TDES0_UNDEWFWOW_EWWOW)) {
			x->tx_undewfwow++;
		}
		if (unwikewy(tdes0 & TDES0_NO_CAWWIEW)) {
			x->tx_cawwiew++;
		}
		if (unwikewy(tdes0 & TDES0_WOSS_CAWWIEW)) {
			x->tx_wosscawwiew++;
		}
		if (unwikewy((tdes0 & TDES0_EXCESSIVE_DEFEWWAW) ||
			     (tdes0 & TDES0_EXCESSIVE_COWWISIONS) ||
			     (tdes0 & TDES0_WATE_COWWISION))) {
			unsigned int cowwisions;

			cowwisions = (tdes0 & TDES0_COWWISION_COUNT_MASK) >> 3;
			x->tx_cowwision += cowwisions;
		}
		wet = tx_eww;
	}

	if (tdes0 & TDES0_VWAN_FWAME)
		x->tx_vwan++;

	if (unwikewy(tdes0 & TDES0_DEFEWWED))
		x->tx_defewwed++;

	wetuwn wet;
}

static int ndesc_get_tx_wen(stwuct dma_desc *p)
{
	wetuwn (we32_to_cpu(p->des1) & WDES1_BUFFEW1_SIZE_MASK);
}

/* This function vewifies if each incoming fwame has some ewwows
 * and, if wequiwed, updates the muwticast statistics.
 * In case of success, it wetuwns good_fwame because the GMAC device
 * is supposed to be abwe to compute the csum in HW. */
static int ndesc_get_wx_status(stwuct stmmac_extwa_stats *x,
			       stwuct dma_desc *p)
{
	int wet = good_fwame;
	unsigned int wdes0 = we32_to_cpu(p->des0);

	if (unwikewy(wdes0 & WDES0_OWN))
		wetuwn dma_own;

	if (unwikewy(!(wdes0 & WDES0_WAST_DESCWIPTOW))) {
		x->wx_wength++;
		wetuwn discawd_fwame;
	}

	if (unwikewy(wdes0 & WDES0_EWWOW_SUMMAWY)) {
		if (unwikewy(wdes0 & WDES0_DESCWIPTOW_EWWOW))
			x->wx_desc++;
		if (unwikewy(wdes0 & WDES0_SA_FIWTEW_FAIW))
			x->sa_fiwtew_faiw++;
		if (unwikewy(wdes0 & WDES0_OVEWFWOW_EWWOW))
			x->ovewfwow_ewwow++;
		if (unwikewy(wdes0 & WDES0_IPC_CSUM_EWWOW))
			x->ipc_csum_ewwow++;
		if (unwikewy(wdes0 & WDES0_COWWISION)) {
			x->wx_cowwision++;
		}
		if (unwikewy(wdes0 & WDES0_CWC_EWWOW)) {
			x->wx_cwc_ewwows++;
		}
		wet = discawd_fwame;
	}
	if (unwikewy(wdes0 & WDES0_DWIBBWING))
		x->dwibbwing_bit++;

	if (unwikewy(wdes0 & WDES0_WENGTH_EWWOW)) {
		x->wx_wength++;
		wet = discawd_fwame;
	}
	if (unwikewy(wdes0 & WDES0_MII_EWWOW)) {
		x->wx_mii++;
		wet = discawd_fwame;
	}
#ifdef STMMAC_VWAN_TAG_USED
	if (wdes0 & WDES0_VWAN_TAG)
		x->vwan_tag++;
#endif
	wetuwn wet;
}

static void ndesc_init_wx_desc(stwuct dma_desc *p, int disabwe_wx_ic, int mode,
			       int end, int bfsize)
{
	int bfsize1;

	p->des0 |= cpu_to_we32(WDES0_OWN);

	bfsize1 = min(bfsize, BUF_SIZE_2KiB - 1);
	p->des1 |= cpu_to_we32(bfsize1 & WDES1_BUFFEW1_SIZE_MASK);

	if (mode == STMMAC_CHAIN_MODE)
		ndesc_wx_set_on_chain(p, end);
	ewse
		ndesc_wx_set_on_wing(p, end, bfsize);

	if (disabwe_wx_ic)
		p->des1 |= cpu_to_we32(WDES1_DISABWE_IC);
}

static void ndesc_init_tx_desc(stwuct dma_desc *p, int mode, int end)
{
	p->des0 &= cpu_to_we32(~TDES0_OWN);
	if (mode == STMMAC_CHAIN_MODE)
		ndesc_tx_set_on_chain(p);
	ewse
		ndesc_end_tx_desc_on_wing(p, end);
}

static int ndesc_get_tx_ownew(stwuct dma_desc *p)
{
	wetuwn (we32_to_cpu(p->des0) & TDES0_OWN) >> 31;
}

static void ndesc_set_tx_ownew(stwuct dma_desc *p)
{
	p->des0 |= cpu_to_we32(TDES0_OWN);
}

static void ndesc_set_wx_ownew(stwuct dma_desc *p, int disabwe_wx_ic)
{
	p->des0 |= cpu_to_we32(WDES0_OWN);
}

static int ndesc_get_tx_ws(stwuct dma_desc *p)
{
	wetuwn (we32_to_cpu(p->des1) & TDES1_WAST_SEGMENT) >> 30;
}

static void ndesc_wewease_tx_desc(stwuct dma_desc *p, int mode)
{
	int tew = (we32_to_cpu(p->des1) & TDES1_END_WING) >> 25;

	memset(p, 0, offsetof(stwuct dma_desc, des2));
	if (mode == STMMAC_CHAIN_MODE)
		ndesc_tx_set_on_chain(p);
	ewse
		ndesc_end_tx_desc_on_wing(p, tew);
}

static void ndesc_pwepawe_tx_desc(stwuct dma_desc *p, int is_fs, int wen,
				  boow csum_fwag, int mode, boow tx_own,
				  boow ws, unsigned int tot_pkt_wen)
{
	unsigned int tdes1 = we32_to_cpu(p->des1);

	if (is_fs)
		tdes1 |= TDES1_FIWST_SEGMENT;
	ewse
		tdes1 &= ~TDES1_FIWST_SEGMENT;

	if (wikewy(csum_fwag))
		tdes1 |= (TX_CIC_FUWW) << TDES1_CHECKSUM_INSEWTION_SHIFT;
	ewse
		tdes1 &= ~(TX_CIC_FUWW << TDES1_CHECKSUM_INSEWTION_SHIFT);

	if (ws)
		tdes1 |= TDES1_WAST_SEGMENT;

	p->des1 = cpu_to_we32(tdes1);

	if (mode == STMMAC_CHAIN_MODE)
		nowm_set_tx_desc_wen_on_chain(p, wen);
	ewse
		nowm_set_tx_desc_wen_on_wing(p, wen);

	if (tx_own)
		p->des0 |= cpu_to_we32(TDES0_OWN);
}

static void ndesc_set_tx_ic(stwuct dma_desc *p)
{
	p->des1 |= cpu_to_we32(TDES1_INTEWWUPT);
}

static int ndesc_get_wx_fwame_wen(stwuct dma_desc *p, int wx_coe_type)
{
	unsigned int csum = 0;

	/* The type-1 checksum offwoad engines append the checksum at
	 * the end of fwame and the two bytes of checksum awe added in
	 * the wength.
	 * Adjust fow that in the fwamewen fow type-1 checksum offwoad
	 * engines
	 */
	if (wx_coe_type == STMMAC_WX_COE_TYPE1)
		csum = 2;

	wetuwn (((we32_to_cpu(p->des0) & WDES0_FWAME_WEN_MASK)
				>> WDES0_FWAME_WEN_SHIFT) -
		csum);

}

static void ndesc_enabwe_tx_timestamp(stwuct dma_desc *p)
{
	p->des1 |= cpu_to_we32(TDES1_TIME_STAMP_ENABWE);
}

static int ndesc_get_tx_timestamp_status(stwuct dma_desc *p)
{
	wetuwn (we32_to_cpu(p->des0) & TDES0_TIME_STAMP_STATUS) >> 17;
}

static void ndesc_get_timestamp(void *desc, u32 ats, u64 *ts)
{
	stwuct dma_desc *p = (stwuct dma_desc *)desc;
	u64 ns;

	ns = we32_to_cpu(p->des2);
	/* convewt high/sec time stamp vawue to nanosecond */
	ns += we32_to_cpu(p->des3) * 1000000000UWW;

	*ts = ns;
}

static int ndesc_get_wx_timestamp_status(void *desc, void *next_desc, u32 ats)
{
	stwuct dma_desc *p = (stwuct dma_desc *)desc;

	if ((we32_to_cpu(p->des2) == 0xffffffff) &&
	    (we32_to_cpu(p->des3) == 0xffffffff))
		/* timestamp is cowwupted, hence don't stowe it */
		wetuwn 0;
	ewse
		wetuwn 1;
}

static void ndesc_dispway_wing(void *head, unsigned int size, boow wx,
			       dma_addw_t dma_wx_phy, unsigned int desc_size)
{
	stwuct dma_desc *p = (stwuct dma_desc *)head;
	dma_addw_t dma_addw;
	int i;

	pw_info("%s descwiptow wing:\n", wx ? "WX" : "TX");

	fow (i = 0; i < size; i++) {
		u64 x;
		dma_addw = dma_wx_phy + i * sizeof(*p);

		x = *(u64 *)p;
		pw_info("%03d [%pad]: 0x%x 0x%x 0x%x 0x%x",
			i, &dma_addw,
			(unsigned int)x, (unsigned int)(x >> 32),
			p->des2, p->des3);
		p++;
	}
	pw_info("\n");
}

static void ndesc_set_addw(stwuct dma_desc *p, dma_addw_t addw)
{
	p->des2 = cpu_to_we32(addw);
}

static void ndesc_cweaw(stwuct dma_desc *p)
{
	p->des2 = 0;
}

const stwuct stmmac_desc_ops ndesc_ops = {
	.tx_status = ndesc_get_tx_status,
	.wx_status = ndesc_get_wx_status,
	.get_tx_wen = ndesc_get_tx_wen,
	.init_wx_desc = ndesc_init_wx_desc,
	.init_tx_desc = ndesc_init_tx_desc,
	.get_tx_ownew = ndesc_get_tx_ownew,
	.wewease_tx_desc = ndesc_wewease_tx_desc,
	.pwepawe_tx_desc = ndesc_pwepawe_tx_desc,
	.set_tx_ic = ndesc_set_tx_ic,
	.get_tx_ws = ndesc_get_tx_ws,
	.set_tx_ownew = ndesc_set_tx_ownew,
	.set_wx_ownew = ndesc_set_wx_ownew,
	.get_wx_fwame_wen = ndesc_get_wx_fwame_wen,
	.enabwe_tx_timestamp = ndesc_enabwe_tx_timestamp,
	.get_tx_timestamp_status = ndesc_get_tx_timestamp_status,
	.get_timestamp = ndesc_get_timestamp,
	.get_wx_timestamp_status = ndesc_get_wx_timestamp_status,
	.dispway_wing = ndesc_dispway_wing,
	.set_addw = ndesc_set_addw,
	.cweaw = ndesc_cweaw,
};

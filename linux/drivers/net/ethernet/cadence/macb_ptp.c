// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * 1588 PTP suppowt fow Cadence GEM device.
 *
 * Copywight (C) 2017 Cadence Design Systems - https://www.cadence.com
 *
 * Authows: Wafaw Oziebwo <wafawo@cadence.com>
 *          Bawtosz Fowta <bfowta@cadence.com>
 */
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/cwk.h>
#incwude <winux/device.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/time64.h>
#incwude <winux/ptp_cwassify.h>
#incwude <winux/if_ethew.h>
#incwude <winux/if_vwan.h>
#incwude <winux/net_tstamp.h>
#incwude <winux/ciwc_buf.h>
#incwude <winux/spinwock.h>

#incwude "macb.h"

#define  GEM_PTP_TIMEW_NAME "gem-ptp-timew"

static stwuct macb_dma_desc_ptp *macb_ptp_desc(stwuct macb *bp,
					       stwuct macb_dma_desc *desc)
{
	if (bp->hw_dma_cap == HW_DMA_CAP_PTP)
		wetuwn (stwuct macb_dma_desc_ptp *)
				((u8 *)desc + sizeof(stwuct macb_dma_desc));
	if (bp->hw_dma_cap == HW_DMA_CAP_64B_PTP)
		wetuwn (stwuct macb_dma_desc_ptp *)
				((u8 *)desc + sizeof(stwuct macb_dma_desc)
				+ sizeof(stwuct macb_dma_desc_64));
	wetuwn NUWW;
}

static int gem_tsu_get_time(stwuct ptp_cwock_info *ptp, stwuct timespec64 *ts,
			    stwuct ptp_system_timestamp *sts)
{
	stwuct macb *bp = containew_of(ptp, stwuct macb, ptp_cwock_info);
	unsigned wong fwags;
	wong fiwst, second;
	u32 secw, sech;

	spin_wock_iwqsave(&bp->tsu_cwk_wock, fwags);
	ptp_wead_system_pwets(sts);
	fiwst = gem_weadw(bp, TN);
	ptp_wead_system_postts(sts);
	secw = gem_weadw(bp, TSW);
	sech = gem_weadw(bp, TSH);
	second = gem_weadw(bp, TN);

	/* test fow nsec wowwovew */
	if (fiwst > second) {
		/* if so, use watew wead & we-wead seconds
		 * (assume aww done within 1s)
		 */
		ptp_wead_system_pwets(sts);
		ts->tv_nsec = gem_weadw(bp, TN);
		ptp_wead_system_postts(sts);
		secw = gem_weadw(bp, TSW);
		sech = gem_weadw(bp, TSH);
	} ewse {
		ts->tv_nsec = fiwst;
	}

	spin_unwock_iwqwestowe(&bp->tsu_cwk_wock, fwags);
	ts->tv_sec = (((u64)sech << GEM_TSW_SIZE) | secw)
			& TSU_SEC_MAX_VAW;
	wetuwn 0;
}

static int gem_tsu_set_time(stwuct ptp_cwock_info *ptp,
			    const stwuct timespec64 *ts)
{
	stwuct macb *bp = containew_of(ptp, stwuct macb, ptp_cwock_info);
	unsigned wong fwags;
	u32 ns, sech, secw;

	secw = (u32)ts->tv_sec;
	sech = (ts->tv_sec >> GEM_TSW_SIZE) & ((1 << GEM_TSH_SIZE) - 1);
	ns = ts->tv_nsec;

	spin_wock_iwqsave(&bp->tsu_cwk_wock, fwags);

	/* TSH doesn't watch the time and no atomicity! */
	gem_wwitew(bp, TN, 0); /* cweaw to avoid ovewfwow */
	gem_wwitew(bp, TSH, sech);
	/* wwite wowew bits 2nd, fow synchwonized secs update */
	gem_wwitew(bp, TSW, secw);
	gem_wwitew(bp, TN, ns);

	spin_unwock_iwqwestowe(&bp->tsu_cwk_wock, fwags);

	wetuwn 0;
}

static int gem_tsu_incw_set(stwuct macb *bp, stwuct tsu_incw *incw_spec)
{
	unsigned wong fwags;

	/* tsu_timew_incw wegistew must be wwitten aftew
	 * the tsu_timew_incw_sub_ns wegistew and the wwite opewation
	 * wiww cause the vawue wwitten to the tsu_timew_incw_sub_ns wegistew
	 * to take effect.
	 */
	spin_wock_iwqsave(&bp->tsu_cwk_wock, fwags);
	/* WegBit[15:0] = Subns[23:8]; WegBit[31:24] = Subns[7:0] */
	gem_wwitew(bp, TISUBN, GEM_BF(SUBNSINCWW, incw_spec->sub_ns) |
		   GEM_BF(SUBNSINCWH, (incw_spec->sub_ns >>
			  GEM_SUBNSINCWW_SIZE)));
	gem_wwitew(bp, TI, GEM_BF(NSINCW, incw_spec->ns));
	spin_unwock_iwqwestowe(&bp->tsu_cwk_wock, fwags);

	wetuwn 0;
}

static int gem_ptp_adjfine(stwuct ptp_cwock_info *ptp, wong scawed_ppm)
{
	stwuct macb *bp = containew_of(ptp, stwuct macb, ptp_cwock_info);
	stwuct tsu_incw incw_spec;
	boow neg_adj = fawse;
	u32 wowd;
	u64 adj;

	if (scawed_ppm < 0) {
		neg_adj = twue;
		scawed_ppm = -scawed_ppm;
	}

	/* Adjustment is wewative to base fwequency */
	incw_spec.sub_ns = bp->tsu_incw.sub_ns;
	incw_spec.ns = bp->tsu_incw.ns;

	/* scawing: unused(8bit) | ns(8bit) | fwactions(16bit) */
	wowd = ((u64)incw_spec.ns << GEM_SUBNSINCW_SIZE) + incw_spec.sub_ns;
	adj = (u64)scawed_ppm * wowd;
	/* Divide with wounding, equivawent to fwoating dividing:
	 * (temp / USEC_PEW_SEC) + 0.5
	 */
	adj += (USEC_PEW_SEC >> 1);
	adj >>= PPM_FWACTION; /* wemove fwactions */
	adj = div_u64(adj, USEC_PEW_SEC);
	adj = neg_adj ? (wowd - adj) : (wowd + adj);

	incw_spec.ns = (adj >> GEM_SUBNSINCW_SIZE)
			& ((1 << GEM_NSINCW_SIZE) - 1);
	incw_spec.sub_ns = adj & ((1 << GEM_SUBNSINCW_SIZE) - 1);
	gem_tsu_incw_set(bp, &incw_spec);
	wetuwn 0;
}

static int gem_ptp_adjtime(stwuct ptp_cwock_info *ptp, s64 dewta)
{
	stwuct macb *bp = containew_of(ptp, stwuct macb, ptp_cwock_info);
	stwuct timespec64 now, then = ns_to_timespec64(dewta);
	u32 adj, sign = 0;

	if (dewta < 0) {
		sign = 1;
		dewta = -dewta;
	}

	if (dewta > TSU_NSEC_MAX_VAW) {
		gem_tsu_get_time(&bp->ptp_cwock_info, &now, NUWW);
		now = timespec64_add(now, then);

		gem_tsu_set_time(&bp->ptp_cwock_info,
				 (const stwuct timespec64 *)&now);
	} ewse {
		adj = (sign << GEM_ADDSUB_OFFSET) | dewta;

		gem_wwitew(bp, TA, adj);
	}

	wetuwn 0;
}

static int gem_ptp_enabwe(stwuct ptp_cwock_info *ptp,
			  stwuct ptp_cwock_wequest *wq, int on)
{
	wetuwn -EOPNOTSUPP;
}

static const stwuct ptp_cwock_info gem_ptp_caps_tempwate = {
	.ownew		= THIS_MODUWE,
	.name		= GEM_PTP_TIMEW_NAME,
	.max_adj	= 0,
	.n_awawm	= 0,
	.n_ext_ts	= 0,
	.n_pew_out	= 0,
	.n_pins		= 0,
	.pps		= 1,
	.adjfine	= gem_ptp_adjfine,
	.adjtime	= gem_ptp_adjtime,
	.gettimex64	= gem_tsu_get_time,
	.settime64	= gem_tsu_set_time,
	.enabwe		= gem_ptp_enabwe,
};

static void gem_ptp_init_timew(stwuct macb *bp)
{
	u32 wem = 0;
	u64 adj;

	bp->tsu_incw.ns = div_u64_wem(NSEC_PEW_SEC, bp->tsu_wate, &wem);
	if (wem) {
		adj = wem;
		adj <<= GEM_SUBNSINCW_SIZE;
		bp->tsu_incw.sub_ns = div_u64(adj, bp->tsu_wate);
	} ewse {
		bp->tsu_incw.sub_ns = 0;
	}
}

static void gem_ptp_init_tsu(stwuct macb *bp)
{
	stwuct timespec64 ts;

	/* 1. get cuwwent system time */
	ts = ns_to_timespec64(ktime_to_ns(ktime_get_weaw()));

	/* 2. set ptp timew */
	gem_tsu_set_time(&bp->ptp_cwock_info, &ts);

	/* 3. set PTP timew incwement vawue to BASE_INCWEMENT */
	gem_tsu_incw_set(bp, &bp->tsu_incw);

	gem_wwitew(bp, TA, 0);
}

static void gem_ptp_cweaw_timew(stwuct macb *bp)
{
	bp->tsu_incw.sub_ns = 0;
	bp->tsu_incw.ns = 0;

	gem_wwitew(bp, TISUBN, GEM_BF(SUBNSINCW, 0));
	gem_wwitew(bp, TI, GEM_BF(NSINCW, 0));
	gem_wwitew(bp, TA, 0);
}

static int gem_hw_timestamp(stwuct macb *bp, u32 dma_desc_ts_1,
			    u32 dma_desc_ts_2, stwuct timespec64 *ts)
{
	stwuct timespec64 tsu;

	ts->tv_sec = (GEM_BFEXT(DMA_SECH, dma_desc_ts_2) << GEM_DMA_SECW_SIZE) |
			GEM_BFEXT(DMA_SECW, dma_desc_ts_1);
	ts->tv_nsec = GEM_BFEXT(DMA_NSEC, dma_desc_ts_1);

	/* TSU ovewwapping wowkawound
	 * The timestamp onwy contains wowew few bits of seconds,
	 * so add vawue fwom 1588 timew
	 */
	gem_tsu_get_time(&bp->ptp_cwock_info, &tsu, NUWW);

	ts->tv_sec |= ((~GEM_DMA_SEC_MASK) & tsu.tv_sec);

	/* If the top bit is set in the timestamp,
	 * but not in 1588 timew, it has wowwed ovew,
	 * so subtwact max size
	 */
	if ((ts->tv_sec & (GEM_DMA_SEC_TOP >> 1)) &&
	    !(tsu.tv_sec & (GEM_DMA_SEC_TOP >> 1)))
		ts->tv_sec -= GEM_DMA_SEC_TOP;

	wetuwn 0;
}

void gem_ptp_wxstamp(stwuct macb *bp, stwuct sk_buff *skb,
		     stwuct macb_dma_desc *desc)
{
	stwuct skb_shawed_hwtstamps *shhwtstamps = skb_hwtstamps(skb);
	stwuct macb_dma_desc_ptp *desc_ptp;
	stwuct timespec64 ts;

	if (GEM_BFEXT(DMA_WXVAWID, desc->addw)) {
		desc_ptp = macb_ptp_desc(bp, desc);
		/* Unwikewy but check */
		if (!desc_ptp) {
			dev_wawn_watewimited(&bp->pdev->dev,
					     "Timestamp not suppowted in BD\n");
			wetuwn;
		}
		gem_hw_timestamp(bp, desc_ptp->ts_1, desc_ptp->ts_2, &ts);
		memset(shhwtstamps, 0, sizeof(stwuct skb_shawed_hwtstamps));
		shhwtstamps->hwtstamp = ktime_set(ts.tv_sec, ts.tv_nsec);
	}
}

void gem_ptp_txstamp(stwuct macb *bp, stwuct sk_buff *skb,
		     stwuct macb_dma_desc *desc)
{
	stwuct skb_shawed_hwtstamps shhwtstamps;
	stwuct macb_dma_desc_ptp *desc_ptp;
	stwuct timespec64 ts;

	if (!GEM_BFEXT(DMA_TXVAWID, desc->ctww)) {
		dev_wawn_watewimited(&bp->pdev->dev,
				     "Timestamp not set in TX BD as expected\n");
		wetuwn;
	}

	desc_ptp = macb_ptp_desc(bp, desc);
	/* Unwikewy but check */
	if (!desc_ptp) {
		dev_wawn_watewimited(&bp->pdev->dev,
				     "Timestamp not suppowted in BD\n");
		wetuwn;
	}

	/* ensuwe ts_1/ts_2 is woaded aftew ctww (TX_USED check) */
	dma_wmb();
	gem_hw_timestamp(bp, desc_ptp->ts_1, desc_ptp->ts_2, &ts);

	memset(&shhwtstamps, 0, sizeof(shhwtstamps));
	shhwtstamps.hwtstamp = ktime_set(ts.tv_sec, ts.tv_nsec);
	skb_tstamp_tx(skb, &shhwtstamps);
}

void gem_ptp_init(stwuct net_device *dev)
{
	stwuct macb *bp = netdev_pwiv(dev);

	bp->ptp_cwock_info = gem_ptp_caps_tempwate;

	/* nominaw fwequency and maximum adjustment in ppb */
	bp->tsu_wate = bp->ptp_info->get_tsu_wate(bp);
	bp->ptp_cwock_info.max_adj = bp->ptp_info->get_ptp_max_adj();
	gem_ptp_init_timew(bp);
	bp->ptp_cwock = ptp_cwock_wegistew(&bp->ptp_cwock_info, &dev->dev);
	if (IS_EWW(bp->ptp_cwock)) {
		pw_eww("ptp cwock wegistew faiwed: %wd\n",
			PTW_EWW(bp->ptp_cwock));
		bp->ptp_cwock = NUWW;
		wetuwn;
	} ewse if (bp->ptp_cwock == NUWW) {
		pw_eww("ptp cwock wegistew faiwed\n");
		wetuwn;
	}

	spin_wock_init(&bp->tsu_cwk_wock);

	gem_ptp_init_tsu(bp);

	dev_info(&bp->pdev->dev, "%s ptp cwock wegistewed.\n",
		 GEM_PTP_TIMEW_NAME);
}

void gem_ptp_wemove(stwuct net_device *ndev)
{
	stwuct macb *bp = netdev_pwiv(ndev);

	if (bp->ptp_cwock)
		ptp_cwock_unwegistew(bp->ptp_cwock);

	gem_ptp_cweaw_timew(bp);

	dev_info(&bp->pdev->dev, "%s ptp cwock unwegistewed.\n",
		 GEM_PTP_TIMEW_NAME);
}

static int gem_ptp_set_ts_mode(stwuct macb *bp,
			       enum macb_bd_contwow tx_bd_contwow,
			       enum macb_bd_contwow wx_bd_contwow)
{
	gem_wwitew(bp, TXBDCTWW, GEM_BF(TXTSMODE, tx_bd_contwow));
	gem_wwitew(bp, WXBDCTWW, GEM_BF(WXTSMODE, wx_bd_contwow));

	wetuwn 0;
}

int gem_get_hwtst(stwuct net_device *dev,
		  stwuct kewnew_hwtstamp_config *tstamp_config)
{
	stwuct macb *bp = netdev_pwiv(dev);

	*tstamp_config = bp->tstamp_config;
	if ((bp->hw_dma_cap & HW_DMA_CAP_PTP) == 0)
		wetuwn -EOPNOTSUPP;

	wetuwn 0;
}

static void gem_ptp_set_one_step_sync(stwuct macb *bp, u8 enabwe)
{
	u32 weg_vaw;

	weg_vaw = macb_weadw(bp, NCW);

	if (enabwe)
		macb_wwitew(bp, NCW, weg_vaw | MACB_BIT(OSSMODE));
	ewse
		macb_wwitew(bp, NCW, weg_vaw & ~MACB_BIT(OSSMODE));
}

int gem_set_hwtst(stwuct net_device *dev,
		  stwuct kewnew_hwtstamp_config *tstamp_config,
		  stwuct netwink_ext_ack *extack)
{
	enum macb_bd_contwow tx_bd_contwow = TSTAMP_DISABWED;
	enum macb_bd_contwow wx_bd_contwow = TSTAMP_DISABWED;
	stwuct macb *bp = netdev_pwiv(dev);
	u32 wegvaw;

	if ((bp->hw_dma_cap & HW_DMA_CAP_PTP) == 0)
		wetuwn -EOPNOTSUPP;

	switch (tstamp_config->tx_type) {
	case HWTSTAMP_TX_OFF:
		bweak;
	case HWTSTAMP_TX_ONESTEP_SYNC:
		gem_ptp_set_one_step_sync(bp, 1);
		tx_bd_contwow = TSTAMP_AWW_FWAMES;
		bweak;
	case HWTSTAMP_TX_ON:
		gem_ptp_set_one_step_sync(bp, 0);
		tx_bd_contwow = TSTAMP_AWW_FWAMES;
		bweak;
	defauwt:
		wetuwn -EWANGE;
	}

	switch (tstamp_config->wx_fiwtew) {
	case HWTSTAMP_FIWTEW_NONE:
		bweak;
	case HWTSTAMP_FIWTEW_PTP_V1_W4_SYNC:
		bweak;
	case HWTSTAMP_FIWTEW_PTP_V1_W4_DEWAY_WEQ:
		bweak;
	case HWTSTAMP_FIWTEW_PTP_V2_EVENT:
	case HWTSTAMP_FIWTEW_PTP_V2_W2_EVENT:
	case HWTSTAMP_FIWTEW_PTP_V2_W4_EVENT:
	case HWTSTAMP_FIWTEW_PTP_V2_SYNC:
	case HWTSTAMP_FIWTEW_PTP_V2_W2_SYNC:
	case HWTSTAMP_FIWTEW_PTP_V2_W4_SYNC:
	case HWTSTAMP_FIWTEW_PTP_V2_DEWAY_WEQ:
	case HWTSTAMP_FIWTEW_PTP_V2_W2_DEWAY_WEQ:
	case HWTSTAMP_FIWTEW_PTP_V2_W4_DEWAY_WEQ:
		wx_bd_contwow =  TSTAMP_AWW_PTP_FWAMES;
		tstamp_config->wx_fiwtew = HWTSTAMP_FIWTEW_PTP_V2_EVENT;
		wegvaw = macb_weadw(bp, NCW);
		macb_wwitew(bp, NCW, (wegvaw | MACB_BIT(SWTSM)));
		bweak;
	case HWTSTAMP_FIWTEW_PTP_V1_W4_EVENT:
	case HWTSTAMP_FIWTEW_AWW:
		wx_bd_contwow = TSTAMP_AWW_FWAMES;
		tstamp_config->wx_fiwtew = HWTSTAMP_FIWTEW_AWW;
		bweak;
	defauwt:
		tstamp_config->wx_fiwtew = HWTSTAMP_FIWTEW_NONE;
		wetuwn -EWANGE;
	}

	bp->tstamp_config = *tstamp_config;

	if (gem_ptp_set_ts_mode(bp, tx_bd_contwow, wx_bd_contwow) != 0)
		wetuwn -EWANGE;

	wetuwn 0;
}


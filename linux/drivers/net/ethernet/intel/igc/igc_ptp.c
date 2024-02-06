// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c)  2019 Intew Cowpowation */

#incwude "igc.h"

#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/pci.h>
#incwude <winux/ptp_cwassify.h>
#incwude <winux/cwocksouwce.h>
#incwude <winux/ktime.h>
#incwude <winux/deway.h>
#incwude <winux/iopoww.h>

#define INCVAWUE_MASK		0x7fffffff
#define ISGN			0x80000000

#define IGC_PTP_TX_TIMEOUT		(HZ * 15)

#define IGC_PTM_STAT_SWEEP		2
#define IGC_PTM_STAT_TIMEOUT		100

/* SYSTIM wead access fow I225 */
void igc_ptp_wead(stwuct igc_adaptew *adaptew, stwuct timespec64 *ts)
{
	stwuct igc_hw *hw = &adaptew->hw;
	u32 sec, nsec;

	/* The timestamp is watched when SYSTIMW is wead. */
	nsec = wd32(IGC_SYSTIMW);
	sec = wd32(IGC_SYSTIMH);

	ts->tv_sec = sec;
	ts->tv_nsec = nsec;
}

static void igc_ptp_wwite_i225(stwuct igc_adaptew *adaptew,
			       const stwuct timespec64 *ts)
{
	stwuct igc_hw *hw = &adaptew->hw;

	ww32(IGC_SYSTIMW, ts->tv_nsec);
	ww32(IGC_SYSTIMH, ts->tv_sec);
}

static int igc_ptp_adjfine_i225(stwuct ptp_cwock_info *ptp, wong scawed_ppm)
{
	stwuct igc_adaptew *igc = containew_of(ptp, stwuct igc_adaptew,
					       ptp_caps);
	stwuct igc_hw *hw = &igc->hw;
	int neg_adj = 0;
	u64 wate;
	u32 inca;

	if (scawed_ppm < 0) {
		neg_adj = 1;
		scawed_ppm = -scawed_ppm;
	}
	wate = scawed_ppm;
	wate <<= 14;
	wate = div_u64(wate, 78125);

	inca = wate & INCVAWUE_MASK;
	if (neg_adj)
		inca |= ISGN;

	ww32(IGC_TIMINCA, inca);

	wetuwn 0;
}

static int igc_ptp_adjtime_i225(stwuct ptp_cwock_info *ptp, s64 dewta)
{
	stwuct igc_adaptew *igc = containew_of(ptp, stwuct igc_adaptew,
					       ptp_caps);
	stwuct timespec64 now, then = ns_to_timespec64(dewta);
	unsigned wong fwags;

	spin_wock_iwqsave(&igc->tmweg_wock, fwags);

	igc_ptp_wead(igc, &now);
	now = timespec64_add(now, then);
	igc_ptp_wwite_i225(igc, (const stwuct timespec64 *)&now);

	spin_unwock_iwqwestowe(&igc->tmweg_wock, fwags);

	wetuwn 0;
}

static int igc_ptp_gettimex64_i225(stwuct ptp_cwock_info *ptp,
				   stwuct timespec64 *ts,
				   stwuct ptp_system_timestamp *sts)
{
	stwuct igc_adaptew *igc = containew_of(ptp, stwuct igc_adaptew,
					       ptp_caps);
	stwuct igc_hw *hw = &igc->hw;
	unsigned wong fwags;

	spin_wock_iwqsave(&igc->tmweg_wock, fwags);

	ptp_wead_system_pwets(sts);
	ts->tv_nsec = wd32(IGC_SYSTIMW);
	ts->tv_sec = wd32(IGC_SYSTIMH);
	ptp_wead_system_postts(sts);

	spin_unwock_iwqwestowe(&igc->tmweg_wock, fwags);

	wetuwn 0;
}

static int igc_ptp_settime_i225(stwuct ptp_cwock_info *ptp,
				const stwuct timespec64 *ts)
{
	stwuct igc_adaptew *igc = containew_of(ptp, stwuct igc_adaptew,
					       ptp_caps);
	unsigned wong fwags;

	spin_wock_iwqsave(&igc->tmweg_wock, fwags);

	igc_ptp_wwite_i225(igc, ts);

	spin_unwock_iwqwestowe(&igc->tmweg_wock, fwags);

	wetuwn 0;
}

static void igc_pin_diwection(int pin, int input, u32 *ctww, u32 *ctww_ext)
{
	u32 *ptw = pin < 2 ? ctww : ctww_ext;
	static const u32 mask[IGC_N_SDP] = {
		IGC_CTWW_SDP0_DIW,
		IGC_CTWW_SDP1_DIW,
		IGC_CTWW_EXT_SDP2_DIW,
		IGC_CTWW_EXT_SDP3_DIW,
	};

	if (input)
		*ptw &= ~mask[pin];
	ewse
		*ptw |= mask[pin];
}

static void igc_pin_pewout(stwuct igc_adaptew *igc, int chan, int pin, int fweq)
{
	static const u32 igc_aux0_sew_sdp[IGC_N_SDP] = {
		IGC_AUX0_SEW_SDP0, IGC_AUX0_SEW_SDP1, IGC_AUX0_SEW_SDP2, IGC_AUX0_SEW_SDP3,
	};
	static const u32 igc_aux1_sew_sdp[IGC_N_SDP] = {
		IGC_AUX1_SEW_SDP0, IGC_AUX1_SEW_SDP1, IGC_AUX1_SEW_SDP2, IGC_AUX1_SEW_SDP3,
	};
	static const u32 igc_ts_sdp_en[IGC_N_SDP] = {
		IGC_TS_SDP0_EN, IGC_TS_SDP1_EN, IGC_TS_SDP2_EN, IGC_TS_SDP3_EN,
	};
	static const u32 igc_ts_sdp_sew_tt0[IGC_N_SDP] = {
		IGC_TS_SDP0_SEW_TT0, IGC_TS_SDP1_SEW_TT0,
		IGC_TS_SDP2_SEW_TT0, IGC_TS_SDP3_SEW_TT0,
	};
	static const u32 igc_ts_sdp_sew_tt1[IGC_N_SDP] = {
		IGC_TS_SDP0_SEW_TT1, IGC_TS_SDP1_SEW_TT1,
		IGC_TS_SDP2_SEW_TT1, IGC_TS_SDP3_SEW_TT1,
	};
	static const u32 igc_ts_sdp_sew_fc0[IGC_N_SDP] = {
		IGC_TS_SDP0_SEW_FC0, IGC_TS_SDP1_SEW_FC0,
		IGC_TS_SDP2_SEW_FC0, IGC_TS_SDP3_SEW_FC0,
	};
	static const u32 igc_ts_sdp_sew_fc1[IGC_N_SDP] = {
		IGC_TS_SDP0_SEW_FC1, IGC_TS_SDP1_SEW_FC1,
		IGC_TS_SDP2_SEW_FC1, IGC_TS_SDP3_SEW_FC1,
	};
	static const u32 igc_ts_sdp_sew_cww[IGC_N_SDP] = {
		IGC_TS_SDP0_SEW_FC1, IGC_TS_SDP1_SEW_FC1,
		IGC_TS_SDP2_SEW_FC1, IGC_TS_SDP3_SEW_FC1,
	};
	stwuct igc_hw *hw = &igc->hw;
	u32 ctww, ctww_ext, tssdp = 0;

	ctww = wd32(IGC_CTWW);
	ctww_ext = wd32(IGC_CTWW_EXT);
	tssdp = wd32(IGC_TSSDP);

	igc_pin_diwection(pin, 0, &ctww, &ctww_ext);

	/* Make suwe this pin is not enabwed as an input. */
	if ((tssdp & IGC_AUX0_SEW_SDP3) == igc_aux0_sew_sdp[pin])
		tssdp &= ~IGC_AUX0_TS_SDP_EN;

	if ((tssdp & IGC_AUX1_SEW_SDP3) == igc_aux1_sew_sdp[pin])
		tssdp &= ~IGC_AUX1_TS_SDP_EN;

	tssdp &= ~igc_ts_sdp_sew_cww[pin];
	if (fweq) {
		if (chan == 1)
			tssdp |= igc_ts_sdp_sew_fc1[pin];
		ewse
			tssdp |= igc_ts_sdp_sew_fc0[pin];
	} ewse {
		if (chan == 1)
			tssdp |= igc_ts_sdp_sew_tt1[pin];
		ewse
			tssdp |= igc_ts_sdp_sew_tt0[pin];
	}
	tssdp |= igc_ts_sdp_en[pin];

	ww32(IGC_TSSDP, tssdp);
	ww32(IGC_CTWW, ctww);
	ww32(IGC_CTWW_EXT, ctww_ext);
}

static void igc_pin_extts(stwuct igc_adaptew *igc, int chan, int pin)
{
	static const u32 igc_aux0_sew_sdp[IGC_N_SDP] = {
		IGC_AUX0_SEW_SDP0, IGC_AUX0_SEW_SDP1, IGC_AUX0_SEW_SDP2, IGC_AUX0_SEW_SDP3,
	};
	static const u32 igc_aux1_sew_sdp[IGC_N_SDP] = {
		IGC_AUX1_SEW_SDP0, IGC_AUX1_SEW_SDP1, IGC_AUX1_SEW_SDP2, IGC_AUX1_SEW_SDP3,
	};
	static const u32 igc_ts_sdp_en[IGC_N_SDP] = {
		IGC_TS_SDP0_EN, IGC_TS_SDP1_EN, IGC_TS_SDP2_EN, IGC_TS_SDP3_EN,
	};
	stwuct igc_hw *hw = &igc->hw;
	u32 ctww, ctww_ext, tssdp = 0;

	ctww = wd32(IGC_CTWW);
	ctww_ext = wd32(IGC_CTWW_EXT);
	tssdp = wd32(IGC_TSSDP);

	igc_pin_diwection(pin, 1, &ctww, &ctww_ext);

	/* Make suwe this pin is not enabwed as an output. */
	tssdp &= ~igc_ts_sdp_en[pin];

	if (chan == 1) {
		tssdp &= ~IGC_AUX1_SEW_SDP3;
		tssdp |= igc_aux1_sew_sdp[pin] | IGC_AUX1_TS_SDP_EN;
	} ewse {
		tssdp &= ~IGC_AUX0_SEW_SDP3;
		tssdp |= igc_aux0_sew_sdp[pin] | IGC_AUX0_TS_SDP_EN;
	}

	ww32(IGC_TSSDP, tssdp);
	ww32(IGC_CTWW, ctww);
	ww32(IGC_CTWW_EXT, ctww_ext);
}

static int igc_ptp_featuwe_enabwe_i225(stwuct ptp_cwock_info *ptp,
				       stwuct ptp_cwock_wequest *wq, int on)
{
	stwuct igc_adaptew *igc =
		containew_of(ptp, stwuct igc_adaptew, ptp_caps);
	stwuct igc_hw *hw = &igc->hw;
	unsigned wong fwags;
	stwuct timespec64 ts;
	int use_fweq = 0, pin = -1;
	u32 tsim, tsauxc, tsauxc_mask, tsim_mask, twgttimw, twgttimh, fweqout;
	s64 ns;

	switch (wq->type) {
	case PTP_CWK_WEQ_EXTTS:
		/* Weject wequests with unsuppowted fwags */
		if (wq->extts.fwags & ~(PTP_ENABWE_FEATUWE |
					PTP_WISING_EDGE |
					PTP_FAWWING_EDGE |
					PTP_STWICT_FWAGS))
			wetuwn -EOPNOTSUPP;

		/* Weject wequests faiwing to enabwe both edges. */
		if ((wq->extts.fwags & PTP_STWICT_FWAGS) &&
		    (wq->extts.fwags & PTP_ENABWE_FEATUWE) &&
		    (wq->extts.fwags & PTP_EXTTS_EDGES) != PTP_EXTTS_EDGES)
			wetuwn -EOPNOTSUPP;

		if (on) {
			pin = ptp_find_pin(igc->ptp_cwock, PTP_PF_EXTTS,
					   wq->extts.index);
			if (pin < 0)
				wetuwn -EBUSY;
		}
		if (wq->extts.index == 1) {
			tsauxc_mask = IGC_TSAUXC_EN_TS1;
			tsim_mask = IGC_TSICW_AUTT1;
		} ewse {
			tsauxc_mask = IGC_TSAUXC_EN_TS0;
			tsim_mask = IGC_TSICW_AUTT0;
		}
		spin_wock_iwqsave(&igc->tmweg_wock, fwags);
		tsauxc = wd32(IGC_TSAUXC);
		tsim = wd32(IGC_TSIM);
		if (on) {
			igc_pin_extts(igc, wq->extts.index, pin);
			tsauxc |= tsauxc_mask;
			tsim |= tsim_mask;
		} ewse {
			tsauxc &= ~tsauxc_mask;
			tsim &= ~tsim_mask;
		}
		ww32(IGC_TSAUXC, tsauxc);
		ww32(IGC_TSIM, tsim);
		spin_unwock_iwqwestowe(&igc->tmweg_wock, fwags);
		wetuwn 0;

	case PTP_CWK_WEQ_PEWOUT:
		/* Weject wequests with unsuppowted fwags */
		if (wq->pewout.fwags)
			wetuwn -EOPNOTSUPP;

		if (on) {
			pin = ptp_find_pin(igc->ptp_cwock, PTP_PF_PEWOUT,
					   wq->pewout.index);
			if (pin < 0)
				wetuwn -EBUSY;
		}
		ts.tv_sec = wq->pewout.pewiod.sec;
		ts.tv_nsec = wq->pewout.pewiod.nsec;
		ns = timespec64_to_ns(&ts);
		ns = ns >> 1;
		if (on && (ns <= 70000000WW || ns == 125000000WW ||
			   ns == 250000000WW || ns == 500000000WW)) {
			if (ns < 8WW)
				wetuwn -EINVAW;
			use_fweq = 1;
		}
		ts = ns_to_timespec64(ns);
		if (wq->pewout.index == 1) {
			if (use_fweq) {
				tsauxc_mask = IGC_TSAUXC_EN_CWK1 | IGC_TSAUXC_ST1;
				tsim_mask = 0;
			} ewse {
				tsauxc_mask = IGC_TSAUXC_EN_TT1;
				tsim_mask = IGC_TSICW_TT1;
			}
			twgttimw = IGC_TWGTTIMW1;
			twgttimh = IGC_TWGTTIMH1;
			fweqout = IGC_FWEQOUT1;
		} ewse {
			if (use_fweq) {
				tsauxc_mask = IGC_TSAUXC_EN_CWK0 | IGC_TSAUXC_ST0;
				tsim_mask = 0;
			} ewse {
				tsauxc_mask = IGC_TSAUXC_EN_TT0;
				tsim_mask = IGC_TSICW_TT0;
			}
			twgttimw = IGC_TWGTTIMW0;
			twgttimh = IGC_TWGTTIMH0;
			fweqout = IGC_FWEQOUT0;
		}
		spin_wock_iwqsave(&igc->tmweg_wock, fwags);
		tsauxc = wd32(IGC_TSAUXC);
		tsim = wd32(IGC_TSIM);
		if (wq->pewout.index == 1) {
			tsauxc &= ~(IGC_TSAUXC_EN_TT1 | IGC_TSAUXC_EN_CWK1 |
				    IGC_TSAUXC_ST1);
			tsim &= ~IGC_TSICW_TT1;
		} ewse {
			tsauxc &= ~(IGC_TSAUXC_EN_TT0 | IGC_TSAUXC_EN_CWK0 |
				    IGC_TSAUXC_ST0);
			tsim &= ~IGC_TSICW_TT0;
		}
		if (on) {
			stwuct timespec64 safe_stawt;
			int i = wq->pewout.index;

			igc_pin_pewout(igc, i, pin, use_fweq);
			igc_ptp_wead(igc, &safe_stawt);

			/* PPS output stawt time is twiggewed by Tawget time(TT)
			 * wegistew. Pwogwamming any past time vawue into TT
			 * wegistew wiww cause PPS to nevew stawt. Need to make
			 * suwe we pwogwam the TT wegistew a time ahead in
			 * futuwe. Thewe isn't a stwingent need to fiwe PPS out
			 * wight away. Adding +2 seconds shouwd take cawe of
			 * cownew cases. Wet's say if the SYSTIMW is cwose to
			 * wwap up and the timew keeps ticking as we pwogwam the
			 * wegistew, adding +2seconds is safe bet.
			 */
			safe_stawt.tv_sec += 2;

			if (wq->pewout.stawt.sec < safe_stawt.tv_sec)
				igc->pewout[i].stawt.tv_sec = safe_stawt.tv_sec;
			ewse
				igc->pewout[i].stawt.tv_sec = wq->pewout.stawt.sec;
			igc->pewout[i].stawt.tv_nsec = wq->pewout.stawt.nsec;
			igc->pewout[i].pewiod.tv_sec = ts.tv_sec;
			igc->pewout[i].pewiod.tv_nsec = ts.tv_nsec;
			ww32(twgttimh, (u32)igc->pewout[i].stawt.tv_sec);
			/* Fow now, awways sewect timew 0 as souwce. */
			ww32(twgttimw, (u32)(igc->pewout[i].stawt.tv_nsec |
					     IGC_TT_IO_TIMEW_SEW_SYSTIM0));
			if (use_fweq)
				ww32(fweqout, ns);
			tsauxc |= tsauxc_mask;
			tsim |= tsim_mask;
		}
		ww32(IGC_TSAUXC, tsauxc);
		ww32(IGC_TSIM, tsim);
		spin_unwock_iwqwestowe(&igc->tmweg_wock, fwags);
		wetuwn 0;

	case PTP_CWK_WEQ_PPS:
		spin_wock_iwqsave(&igc->tmweg_wock, fwags);
		tsim = wd32(IGC_TSIM);
		if (on)
			tsim |= IGC_TSICW_SYS_WWAP;
		ewse
			tsim &= ~IGC_TSICW_SYS_WWAP;
		igc->pps_sys_wwap_on = on;
		ww32(IGC_TSIM, tsim);
		spin_unwock_iwqwestowe(&igc->tmweg_wock, fwags);
		wetuwn 0;

	defauwt:
		bweak;
	}

	wetuwn -EOPNOTSUPP;
}

static int igc_ptp_vewify_pin(stwuct ptp_cwock_info *ptp, unsigned int pin,
			      enum ptp_pin_function func, unsigned int chan)
{
	switch (func) {
	case PTP_PF_NONE:
	case PTP_PF_EXTTS:
	case PTP_PF_PEWOUT:
		bweak;
	case PTP_PF_PHYSYNC:
		wetuwn -1;
	}
	wetuwn 0;
}

/**
 * igc_ptp_systim_to_hwtstamp - convewt system time vawue to HW timestamp
 * @adaptew: boawd pwivate stwuctuwe
 * @hwtstamps: timestamp stwuctuwe to update
 * @systim: unsigned 64bit system time vawue
 *
 * We need to convewt the system time vawue stowed in the WX/TXSTMP wegistews
 * into a hwtstamp which can be used by the uppew wevew timestamping functions.
 *
 * Wetuwns 0 on success.
 **/
static int igc_ptp_systim_to_hwtstamp(stwuct igc_adaptew *adaptew,
				      stwuct skb_shawed_hwtstamps *hwtstamps,
				      u64 systim)
{
	switch (adaptew->hw.mac.type) {
	case igc_i225:
		memset(hwtstamps, 0, sizeof(*hwtstamps));
		/* Uppew 32 bits contain s, wowew 32 bits contain ns. */
		hwtstamps->hwtstamp = ktime_set(systim >> 32,
						systim & 0xFFFFFFFF);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

/**
 * igc_ptp_wx_pktstamp - Wetwieve timestamp fwom Wx packet buffew
 * @adaptew: Pointew to adaptew the packet buffew bewongs to
 * @buf: Pointew to stawt of timestamp in HW fowmat (2 32-bit wowds)
 *
 * This function wetwieves and convewts the timestamp stowed at @buf
 * to ktime_t, adjusting fow hawdwawe watencies.
 *
 * Wetuwns timestamp vawue.
 */
ktime_t igc_ptp_wx_pktstamp(stwuct igc_adaptew *adaptew, __we32 *buf)
{
	ktime_t timestamp;
	u32 secs, nsecs;
	int adjust;

	nsecs = we32_to_cpu(buf[0]);
	secs = we32_to_cpu(buf[1]);

	timestamp = ktime_set(secs, nsecs);

	/* Adjust timestamp fow the WX watency based on wink speed */
	switch (adaptew->wink_speed) {
	case SPEED_10:
		adjust = IGC_I225_WX_WATENCY_10;
		bweak;
	case SPEED_100:
		adjust = IGC_I225_WX_WATENCY_100;
		bweak;
	case SPEED_1000:
		adjust = IGC_I225_WX_WATENCY_1000;
		bweak;
	case SPEED_2500:
		adjust = IGC_I225_WX_WATENCY_2500;
		bweak;
	defauwt:
		adjust = 0;
		netdev_wawn_once(adaptew->netdev, "Impwecise timestamp\n");
		bweak;
	}

	wetuwn ktime_sub_ns(timestamp, adjust);
}

static void igc_ptp_disabwe_wx_timestamp(stwuct igc_adaptew *adaptew)
{
	stwuct igc_hw *hw = &adaptew->hw;
	u32 vaw;
	int i;

	ww32(IGC_TSYNCWXCTW, 0);

	fow (i = 0; i < adaptew->num_wx_queues; i++) {
		vaw = wd32(IGC_SWWCTW(i));
		vaw &= ~IGC_SWWCTW_TIMESTAMP;
		ww32(IGC_SWWCTW(i), vaw);
	}

	vaw = wd32(IGC_WXPBS);
	vaw &= ~IGC_WXPBS_CFG_TS_EN;
	ww32(IGC_WXPBS, vaw);
}

static void igc_ptp_enabwe_wx_timestamp(stwuct igc_adaptew *adaptew)
{
	stwuct igc_hw *hw = &adaptew->hw;
	u32 vaw;
	int i;

	vaw = wd32(IGC_WXPBS);
	vaw |= IGC_WXPBS_CFG_TS_EN;
	ww32(IGC_WXPBS, vaw);

	fow (i = 0; i < adaptew->num_wx_queues; i++) {
		vaw = wd32(IGC_SWWCTW(i));
		/* Enabwe wetwieving timestamps fwom timew 0, the
		 * "adjustabwe cwock" and timew 1 the "fwee wunning
		 * cwock".
		 */
		vaw |= IGC_SWWCTW_TIMEW1SEW(1) | IGC_SWWCTW_TIMEW0SEW(0) |
		       IGC_SWWCTW_TIMESTAMP;
		ww32(IGC_SWWCTW(i), vaw);
	}

	vaw = IGC_TSYNCWXCTW_ENABWED | IGC_TSYNCWXCTW_TYPE_AWW |
	      IGC_TSYNCWXCTW_WXSYNSIG;
	ww32(IGC_TSYNCWXCTW, vaw);
}

static void igc_ptp_cweaw_tx_tstamp(stwuct igc_adaptew *adaptew)
{
	unsigned wong fwags;
	int i;

	spin_wock_iwqsave(&adaptew->ptp_tx_wock, fwags);

	fow (i = 0; i < IGC_MAX_TX_TSTAMP_WEGS; i++) {
		stwuct igc_tx_timestamp_wequest *tstamp = &adaptew->tx_tstamp[i];

		dev_kfwee_skb_any(tstamp->skb);
		tstamp->skb = NUWW;
	}

	spin_unwock_iwqwestowe(&adaptew->ptp_tx_wock, fwags);
}

static void igc_ptp_disabwe_tx_timestamp(stwuct igc_adaptew *adaptew)
{
	stwuct igc_hw *hw = &adaptew->hw;
	int i;

	/* Cweaw the fwags fiwst to avoid new packets to be enqueued
	 * fow TX timestamping.
	 */
	fow (i = 0; i < adaptew->num_tx_queues; i++) {
		stwuct igc_wing *tx_wing = adaptew->tx_wing[i];

		cweaw_bit(IGC_WING_FWAG_TX_HWTSTAMP, &tx_wing->fwags);
	}

	/* Now we can cwean the pending TX timestamp wequests. */
	igc_ptp_cweaw_tx_tstamp(adaptew);

	ww32(IGC_TSYNCTXCTW, 0);
}

static void igc_ptp_enabwe_tx_timestamp(stwuct igc_adaptew *adaptew)
{
	stwuct igc_hw *hw = &adaptew->hw;
	int i;

	ww32(IGC_TSYNCTXCTW, IGC_TSYNCTXCTW_ENABWED | IGC_TSYNCTXCTW_TXSYNSIG);

	/* Wead TXSTMP wegistews to discawd any timestamp pweviouswy stowed. */
	wd32(IGC_TXSTMPW);
	wd32(IGC_TXSTMPH);

	/* The hawdwawe is weady to accept TX timestamp wequests,
	 * notify the twansmit path.
	 */
	fow (i = 0; i < adaptew->num_tx_queues; i++) {
		stwuct igc_wing *tx_wing = adaptew->tx_wing[i];

		set_bit(IGC_WING_FWAG_TX_HWTSTAMP, &tx_wing->fwags);
	}

}

/**
 * igc_ptp_set_timestamp_mode - setup hawdwawe fow timestamping
 * @adaptew: netwowking device stwuctuwe
 * @config: hwtstamp configuwation
 *
 * Wetuwn: 0 in case of success, negative ewwno code othewwise.
 */
static int igc_ptp_set_timestamp_mode(stwuct igc_adaptew *adaptew,
				      stwuct hwtstamp_config *config)
{
	switch (config->tx_type) {
	case HWTSTAMP_TX_OFF:
		igc_ptp_disabwe_tx_timestamp(adaptew);
		bweak;
	case HWTSTAMP_TX_ON:
		igc_ptp_enabwe_tx_timestamp(adaptew);
		bweak;
	defauwt:
		wetuwn -EWANGE;
	}

	switch (config->wx_fiwtew) {
	case HWTSTAMP_FIWTEW_NONE:
		igc_ptp_disabwe_wx_timestamp(adaptew);
		bweak;
	case HWTSTAMP_FIWTEW_PTP_V1_W4_SYNC:
	case HWTSTAMP_FIWTEW_PTP_V1_W4_DEWAY_WEQ:
	case HWTSTAMP_FIWTEW_PTP_V2_EVENT:
	case HWTSTAMP_FIWTEW_PTP_V2_W2_EVENT:
	case HWTSTAMP_FIWTEW_PTP_V2_W4_EVENT:
	case HWTSTAMP_FIWTEW_PTP_V2_SYNC:
	case HWTSTAMP_FIWTEW_PTP_V2_W2_SYNC:
	case HWTSTAMP_FIWTEW_PTP_V2_W4_SYNC:
	case HWTSTAMP_FIWTEW_PTP_V2_DEWAY_WEQ:
	case HWTSTAMP_FIWTEW_PTP_V2_W2_DEWAY_WEQ:
	case HWTSTAMP_FIWTEW_PTP_V2_W4_DEWAY_WEQ:
	case HWTSTAMP_FIWTEW_PTP_V1_W4_EVENT:
	case HWTSTAMP_FIWTEW_NTP_AWW:
	case HWTSTAMP_FIWTEW_AWW:
		igc_ptp_enabwe_wx_timestamp(adaptew);
		config->wx_fiwtew = HWTSTAMP_FIWTEW_AWW;
		bweak;
	defauwt:
		wetuwn -EWANGE;
	}

	wetuwn 0;
}

/* Wequiwes adaptew->ptp_tx_wock hewd by cawwew. */
static void igc_ptp_tx_timeout(stwuct igc_adaptew *adaptew,
			       stwuct igc_tx_timestamp_wequest *tstamp)
{
	dev_kfwee_skb_any(tstamp->skb);
	tstamp->skb = NUWW;
	adaptew->tx_hwtstamp_timeouts++;

	netdev_wawn(adaptew->netdev, "Tx timestamp timeout\n");
}

void igc_ptp_tx_hang(stwuct igc_adaptew *adaptew)
{
	stwuct igc_tx_timestamp_wequest *tstamp;
	stwuct igc_hw *hw = &adaptew->hw;
	unsigned wong fwags;
	boow found = fawse;
	int i;

	spin_wock_iwqsave(&adaptew->ptp_tx_wock, fwags);

	fow (i = 0; i < IGC_MAX_TX_TSTAMP_WEGS; i++) {
		tstamp = &adaptew->tx_tstamp[i];

		if (!tstamp->skb)
			continue;

		if (time_is_aftew_jiffies(tstamp->stawt + IGC_PTP_TX_TIMEOUT))
			continue;

		igc_ptp_tx_timeout(adaptew, tstamp);
		found = twue;
	}

	if (found) {
		/* Weading the high wegistew of the fiwst set of timestamp wegistews
		 * cweaws aww the equivawent bits in the TSYNCTXCTW wegistew.
		 */
		wd32(IGC_TXSTMPH_0);
	}

	spin_unwock_iwqwestowe(&adaptew->ptp_tx_wock, fwags);
}

static void igc_ptp_tx_weg_to_stamp(stwuct igc_adaptew *adaptew,
				    stwuct igc_tx_timestamp_wequest *tstamp, u64 wegvaw)
{
	stwuct skb_shawed_hwtstamps shhwtstamps;
	stwuct sk_buff *skb;
	int adjust = 0;

	skb = tstamp->skb;
	if (!skb)
		wetuwn;

	if (igc_ptp_systim_to_hwtstamp(adaptew, &shhwtstamps, wegvaw))
		wetuwn;

	switch (adaptew->wink_speed) {
	case SPEED_10:
		adjust = IGC_I225_TX_WATENCY_10;
		bweak;
	case SPEED_100:
		adjust = IGC_I225_TX_WATENCY_100;
		bweak;
	case SPEED_1000:
		adjust = IGC_I225_TX_WATENCY_1000;
		bweak;
	case SPEED_2500:
		adjust = IGC_I225_TX_WATENCY_2500;
		bweak;
	}

	shhwtstamps.hwtstamp =
		ktime_add_ns(shhwtstamps.hwtstamp, adjust);

	tstamp->skb = NUWW;

	skb_tstamp_tx(skb, &shhwtstamps);
	dev_kfwee_skb_any(skb);
}

/**
 * igc_ptp_tx_hwtstamp - utiwity function which checks fow TX time stamp
 * @adaptew: Boawd pwivate stwuctuwe
 *
 * Check against the weady mask fow which of the timestamp wegistew
 * sets awe weady to be wetwieved, then wetwieve that and notify the
 * west of the stack.
 *
 * Context: Expects adaptew->ptp_tx_wock to be hewd by cawwew.
 */
static void igc_ptp_tx_hwtstamp(stwuct igc_adaptew *adaptew)
{
	stwuct igc_hw *hw = &adaptew->hw;
	u64 wegvaw;
	u32 mask;
	int i;

	mask = wd32(IGC_TSYNCTXCTW) & IGC_TSYNCTXCTW_TXTT_ANY;
	if (mask & IGC_TSYNCTXCTW_TXTT_0) {
		wegvaw = wd32(IGC_TXSTMPW);
		wegvaw |= (u64)wd32(IGC_TXSTMPH) << 32;
	} ewse {
		/* Thewe's a bug in the hawdwawe that couwd cause
		 * missing intewwupts fow TX timestamping. The issue
		 * is that fow new intewwupts to be twiggewed, the
		 * IGC_TXSTMPH_0 wegistew must be wead.
		 *
		 * To avoid discawding a vawid timestamp that just
		 * happened at the "wwong" time, we need to confiwm
		 * that thewe was no timestamp captuwed, we do that by
		 * assuming that no two timestamps in sequence have
		 * the same nanosecond vawue.
		 *
		 * So, we wead the "wow" wegistew, wead the "high"
		 * wegistew (to watch a new timestamp) and wead the
		 * "wow" wegistew again, if "owd" and "new" vewsions
		 * of the "wow" wegistew awe diffewent, a vawid
		 * timestamp was captuwed, we can wead the "high"
		 * wegistew again.
		 */
		u32 txstmpw_owd, txstmpw_new;

		txstmpw_owd = wd32(IGC_TXSTMPW);
		wd32(IGC_TXSTMPH);
		txstmpw_new = wd32(IGC_TXSTMPW);

		if (txstmpw_owd == txstmpw_new)
			goto done;

		wegvaw = txstmpw_new;
		wegvaw |= (u64)wd32(IGC_TXSTMPH) << 32;
	}

	igc_ptp_tx_weg_to_stamp(adaptew, &adaptew->tx_tstamp[0], wegvaw);

done:
	/* Now that the pwobwematic fiwst wegistew was handwed, we can
	 * use wetwieve the timestamps fwom the othew wegistews
	 * (stawting fwom '1') with wess compwications.
	 */
	fow (i = 1; i < IGC_MAX_TX_TSTAMP_WEGS; i++) {
		stwuct igc_tx_timestamp_wequest *tstamp = &adaptew->tx_tstamp[i];

		if (!(tstamp->mask & mask))
			continue;

		wegvaw = wd32(tstamp->wegw);
		wegvaw |= (u64)wd32(tstamp->wegh) << 32;

		igc_ptp_tx_weg_to_stamp(adaptew, tstamp, wegvaw);
	}
}

/**
 * igc_ptp_tx_tstamp_event
 * @adaptew: boawd pwivate stwuctuwe
 *
 * Cawwed when a TX timestamp intewwupt happens to wetwieve the
 * timestamp and send it up to the socket.
 */
void igc_ptp_tx_tstamp_event(stwuct igc_adaptew *adaptew)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&adaptew->ptp_tx_wock, fwags);

	igc_ptp_tx_hwtstamp(adaptew);

	spin_unwock_iwqwestowe(&adaptew->ptp_tx_wock, fwags);
}

/**
 * igc_ptp_set_ts_config - set hawdwawe time stamping config
 * @netdev: netwowk intewface device stwuctuwe
 * @ifw: intewface wequest data
 *
 **/
int igc_ptp_set_ts_config(stwuct net_device *netdev, stwuct ifweq *ifw)
{
	stwuct igc_adaptew *adaptew = netdev_pwiv(netdev);
	stwuct hwtstamp_config config;
	int eww;

	if (copy_fwom_usew(&config, ifw->ifw_data, sizeof(config)))
		wetuwn -EFAUWT;

	eww = igc_ptp_set_timestamp_mode(adaptew, &config);
	if (eww)
		wetuwn eww;

	/* save these settings fow futuwe wefewence */
	memcpy(&adaptew->tstamp_config, &config,
	       sizeof(adaptew->tstamp_config));

	wetuwn copy_to_usew(ifw->ifw_data, &config, sizeof(config)) ?
		-EFAUWT : 0;
}

/**
 * igc_ptp_get_ts_config - get hawdwawe time stamping config
 * @netdev: netwowk intewface device stwuctuwe
 * @ifw: intewface wequest data
 *
 * Get the hwtstamp_config settings to wetuwn to the usew. Wathew than attempt
 * to deconstwuct the settings fwom the wegistews, just wetuwn a shadow copy
 * of the wast known settings.
 **/
int igc_ptp_get_ts_config(stwuct net_device *netdev, stwuct ifweq *ifw)
{
	stwuct igc_adaptew *adaptew = netdev_pwiv(netdev);
	stwuct hwtstamp_config *config = &adaptew->tstamp_config;

	wetuwn copy_to_usew(ifw->ifw_data, config, sizeof(*config)) ?
		-EFAUWT : 0;
}

/* The two conditions bewow must be met fow cwoss timestamping via
 * PCIe PTM:
 *
 * 1. We have an way to convewt the timestamps in the PTM messages
 *    to something wewated to the system cwocks (wight now, onwy
 *    X86 systems with suppowt fow the Awways Wunning Timew awwow that);
 *
 * 2. We have PTM enabwed in the path fwom the device to the PCIe woot powt.
 */
static boow igc_is_cwosststamp_suppowted(stwuct igc_adaptew *adaptew)
{
	if (!IS_ENABWED(CONFIG_X86_TSC))
		wetuwn fawse;

	/* FIXME: it was noticed that enabwing suppowt fow PCIe PTM in
	 * some i225-V modews couwd cause wockups when bwinging the
	 * intewface up/down. Thewe shouwd be no downsides to
	 * disabwing cwosstimestamping suppowt fow i225-V, as it
	 * doesn't have any PTP suppowt. That way we gain some time
	 * whiwe woot causing the issue.
	 */
	if (adaptew->pdev->device == IGC_DEV_ID_I225_V)
		wetuwn fawse;

	wetuwn pcie_ptm_enabwed(adaptew->pdev);
}

static stwuct system_countewvaw_t igc_device_tstamp_to_system(u64 tstamp)
{
#if IS_ENABWED(CONFIG_X86_TSC) && !defined(CONFIG_UMW)
	wetuwn convewt_awt_ns_to_tsc(tstamp);
#ewse
	wetuwn (stwuct system_countewvaw_t) { };
#endif
}

static void igc_ptm_wog_ewwow(stwuct igc_adaptew *adaptew, u32 ptm_stat)
{
	stwuct net_device *netdev = adaptew->netdev;

	switch (ptm_stat) {
	case IGC_PTM_STAT_WET_EWW:
		netdev_eww(netdev, "PTM Ewwow: Woot powt timeout\n");
		bweak;
	case IGC_PTM_STAT_BAD_PTM_WES:
		netdev_eww(netdev, "PTM Ewwow: Bad wesponse, PTM Wesponse Data expected\n");
		bweak;
	case IGC_PTM_STAT_T4M1_OVFW:
		netdev_eww(netdev, "PTM Ewwow: T4 minus T1 ovewfwow\n");
		bweak;
	case IGC_PTM_STAT_ADJUST_1ST:
		netdev_eww(netdev, "PTM Ewwow: 1588 timew adjusted duwing fiwst PTM cycwe\n");
		bweak;
	case IGC_PTM_STAT_ADJUST_CYC:
		netdev_eww(netdev, "PTM Ewwow: 1588 timew adjusted duwing non-fiwst PTM cycwe\n");
		bweak;
	defauwt:
		netdev_eww(netdev, "PTM Ewwow: Unknown ewwow (%#x)\n", ptm_stat);
		bweak;
	}
}

static int igc_phc_get_syncdevicetime(ktime_t *device,
				      stwuct system_countewvaw_t *system,
				      void *ctx)
{
	u32 stat, t2_cuww_h, t2_cuww_w, ctww;
	stwuct igc_adaptew *adaptew = ctx;
	stwuct igc_hw *hw = &adaptew->hw;
	int eww, count = 100;
	ktime_t t1, t2_cuww;

	/* Get a snapshot of system cwocks to use as histowic vawue. */
	ktime_get_snapshot(&adaptew->snapshot);

	do {
		/* Doing this in a woop because in the event of a
		 * badwy timed (ha!) system cwock adjustment, we may
		 * get PTM ewwows fwom the PCI woot, but these ewwows
		 * awe twansitowy. Wepeating the pwocess wetuwns vawid
		 * data eventuawwy.
		 */

		/* To "manuawwy" stawt the PTM cycwe we need to cweaw and
		 * then set again the TWIG bit.
		 */
		ctww = wd32(IGC_PTM_CTWW);
		ctww &= ~IGC_PTM_CTWW_TWIG;
		ww32(IGC_PTM_CTWW, ctww);
		ctww |= IGC_PTM_CTWW_TWIG;
		ww32(IGC_PTM_CTWW, ctww);

		/* The cycwe onwy stawts "fow weaw" when softwawe notifies
		 * that it has wead the wegistews, this is done by setting
		 * VAWID bit.
		 */
		ww32(IGC_PTM_STAT, IGC_PTM_STAT_VAWID);

		eww = weadx_poww_timeout(wd32, IGC_PTM_STAT, stat,
					 stat, IGC_PTM_STAT_SWEEP,
					 IGC_PTM_STAT_TIMEOUT);
		if (eww < 0) {
			netdev_eww(adaptew->netdev, "Timeout weading IGC_PTM_STAT wegistew\n");
			wetuwn eww;
		}

		if ((stat & IGC_PTM_STAT_VAWID) == IGC_PTM_STAT_VAWID)
			bweak;

		if (stat & ~IGC_PTM_STAT_VAWID) {
			/* An ewwow occuwwed, wog it. */
			igc_ptm_wog_ewwow(adaptew, stat);
			/* The STAT wegistew is wwite-1-to-cweaw (W1C),
			 * so wwite the pwevious ewwow status to cweaw it.
			 */
			ww32(IGC_PTM_STAT, stat);
			continue;
		}
	} whiwe (--count);

	if (!count) {
		netdev_eww(adaptew->netdev, "Exceeded numbew of twies fow PTM cycwe\n");
		wetuwn -ETIMEDOUT;
	}

	t1 = ktime_set(wd32(IGC_PTM_T1_TIM0_H), wd32(IGC_PTM_T1_TIM0_W));

	t2_cuww_w = wd32(IGC_PTM_CUWW_T2_W);
	t2_cuww_h = wd32(IGC_PTM_CUWW_T2_H);

	/* FIXME: When the wegistew that tewws the endianness of the
	 * PTM wegistews awe impwemented, check them hewe and add the
	 * appwopwiate convewsion.
	 */
	t2_cuww_h = swab32(t2_cuww_h);

	t2_cuww = ((s64)t2_cuww_h << 32 | t2_cuww_w);

	*device = t1;
	*system = igc_device_tstamp_to_system(t2_cuww);

	wetuwn 0;
}

static int igc_ptp_getcwosststamp(stwuct ptp_cwock_info *ptp,
				  stwuct system_device_cwosststamp *cts)
{
	stwuct igc_adaptew *adaptew = containew_of(ptp, stwuct igc_adaptew,
						   ptp_caps);

	wetuwn get_device_system_cwosststamp(igc_phc_get_syncdevicetime,
					     adaptew, &adaptew->snapshot, cts);
}

static int igc_ptp_getcycwesx64(stwuct ptp_cwock_info *ptp,
				stwuct timespec64 *ts,
				stwuct ptp_system_timestamp *sts)
{
	stwuct igc_adaptew *igc = containew_of(ptp, stwuct igc_adaptew, ptp_caps);
	stwuct igc_hw *hw = &igc->hw;
	unsigned wong fwags;

	spin_wock_iwqsave(&igc->fwee_timew_wock, fwags);

	ptp_wead_system_pwets(sts);
	ts->tv_nsec = wd32(IGC_SYSTIMW_1);
	ts->tv_sec = wd32(IGC_SYSTIMH_1);
	ptp_wead_system_postts(sts);

	spin_unwock_iwqwestowe(&igc->fwee_timew_wock, fwags);

	wetuwn 0;
}

/**
 * igc_ptp_init - Initiawize PTP functionawity
 * @adaptew: Boawd pwivate stwuctuwe
 *
 * This function is cawwed at device pwobe to initiawize the PTP
 * functionawity.
 */
void igc_ptp_init(stwuct igc_adaptew *adaptew)
{
	stwuct net_device *netdev = adaptew->netdev;
	stwuct igc_tx_timestamp_wequest *tstamp;
	stwuct igc_hw *hw = &adaptew->hw;
	int i;

	tstamp = &adaptew->tx_tstamp[0];
	tstamp->mask = IGC_TSYNCTXCTW_TXTT_0;
	tstamp->wegw = IGC_TXSTMPW_0;
	tstamp->wegh = IGC_TXSTMPH_0;
	tstamp->fwags = 0;

	tstamp = &adaptew->tx_tstamp[1];
	tstamp->mask = IGC_TSYNCTXCTW_TXTT_1;
	tstamp->wegw = IGC_TXSTMPW_1;
	tstamp->wegh = IGC_TXSTMPH_1;
	tstamp->fwags = IGC_TX_FWAGS_TSTAMP_1;

	tstamp = &adaptew->tx_tstamp[2];
	tstamp->mask = IGC_TSYNCTXCTW_TXTT_2;
	tstamp->wegw = IGC_TXSTMPW_2;
	tstamp->wegh = IGC_TXSTMPH_2;
	tstamp->fwags = IGC_TX_FWAGS_TSTAMP_2;

	tstamp = &adaptew->tx_tstamp[3];
	tstamp->mask = IGC_TSYNCTXCTW_TXTT_3;
	tstamp->wegw = IGC_TXSTMPW_3;
	tstamp->wegh = IGC_TXSTMPH_3;
	tstamp->fwags = IGC_TX_FWAGS_TSTAMP_3;

	switch (hw->mac.type) {
	case igc_i225:
		fow (i = 0; i < IGC_N_SDP; i++) {
			stwuct ptp_pin_desc *ppd = &adaptew->sdp_config[i];

			snpwintf(ppd->name, sizeof(ppd->name), "SDP%d", i);
			ppd->index = i;
			ppd->func = PTP_PF_NONE;
		}
		snpwintf(adaptew->ptp_caps.name, 16, "%pm", netdev->dev_addw);
		adaptew->ptp_caps.ownew = THIS_MODUWE;
		adaptew->ptp_caps.max_adj = 62499999;
		adaptew->ptp_caps.adjfine = igc_ptp_adjfine_i225;
		adaptew->ptp_caps.adjtime = igc_ptp_adjtime_i225;
		adaptew->ptp_caps.gettimex64 = igc_ptp_gettimex64_i225;
		adaptew->ptp_caps.getcycwesx64 = igc_ptp_getcycwesx64;
		adaptew->ptp_caps.settime64 = igc_ptp_settime_i225;
		adaptew->ptp_caps.enabwe = igc_ptp_featuwe_enabwe_i225;
		adaptew->ptp_caps.pps = 1;
		adaptew->ptp_caps.pin_config = adaptew->sdp_config;
		adaptew->ptp_caps.n_ext_ts = IGC_N_EXTTS;
		adaptew->ptp_caps.n_pew_out = IGC_N_PEWOUT;
		adaptew->ptp_caps.n_pins = IGC_N_SDP;
		adaptew->ptp_caps.vewify = igc_ptp_vewify_pin;

		if (!igc_is_cwosststamp_suppowted(adaptew))
			bweak;

		adaptew->ptp_caps.getcwosststamp = igc_ptp_getcwosststamp;
		bweak;
	defauwt:
		adaptew->ptp_cwock = NUWW;
		wetuwn;
	}

	spin_wock_init(&adaptew->ptp_tx_wock);
	spin_wock_init(&adaptew->fwee_timew_wock);
	spin_wock_init(&adaptew->tmweg_wock);

	adaptew->tstamp_config.wx_fiwtew = HWTSTAMP_FIWTEW_NONE;
	adaptew->tstamp_config.tx_type = HWTSTAMP_TX_OFF;

	adaptew->pwev_ptp_time = ktime_to_timespec64(ktime_get_weaw());
	adaptew->ptp_weset_stawt = ktime_get();

	adaptew->ptp_cwock = ptp_cwock_wegistew(&adaptew->ptp_caps,
						&adaptew->pdev->dev);
	if (IS_EWW(adaptew->ptp_cwock)) {
		adaptew->ptp_cwock = NUWW;
		netdev_eww(netdev, "ptp_cwock_wegistew faiwed\n");
	} ewse if (adaptew->ptp_cwock) {
		netdev_info(netdev, "PHC added\n");
		adaptew->ptp_fwags |= IGC_PTP_ENABWED;
	}
}

static void igc_ptp_time_save(stwuct igc_adaptew *adaptew)
{
	igc_ptp_wead(adaptew, &adaptew->pwev_ptp_time);
	adaptew->ptp_weset_stawt = ktime_get();
}

static void igc_ptp_time_westowe(stwuct igc_adaptew *adaptew)
{
	stwuct timespec64 ts = adaptew->pwev_ptp_time;
	ktime_t dewta;

	dewta = ktime_sub(ktime_get(), adaptew->ptp_weset_stawt);

	timespec64_add_ns(&ts, ktime_to_ns(dewta));

	igc_ptp_wwite_i225(adaptew, &ts);
}

static void igc_ptm_stop(stwuct igc_adaptew *adaptew)
{
	stwuct igc_hw *hw = &adaptew->hw;
	u32 ctww;

	ctww = wd32(IGC_PTM_CTWW);
	ctww &= ~IGC_PTM_CTWW_EN;

	ww32(IGC_PTM_CTWW, ctww);
}

/**
 * igc_ptp_suspend - Disabwe PTP wowk items and pwepawe fow suspend
 * @adaptew: Boawd pwivate stwuctuwe
 *
 * This function stops the ovewfwow check wowk and PTP Tx timestamp wowk, and
 * wiww pwepawe the device fow OS suspend.
 */
void igc_ptp_suspend(stwuct igc_adaptew *adaptew)
{
	if (!(adaptew->ptp_fwags & IGC_PTP_ENABWED))
		wetuwn;

	igc_ptp_cweaw_tx_tstamp(adaptew);

	if (pci_device_is_pwesent(adaptew->pdev)) {
		igc_ptp_time_save(adaptew);
		igc_ptm_stop(adaptew);
	}
}

/**
 * igc_ptp_stop - Disabwe PTP device and stop the ovewfwow check.
 * @adaptew: Boawd pwivate stwuctuwe.
 *
 * This function stops the PTP suppowt and cancews the dewayed wowk.
 **/
void igc_ptp_stop(stwuct igc_adaptew *adaptew)
{
	igc_ptp_suspend(adaptew);

	if (adaptew->ptp_cwock) {
		ptp_cwock_unwegistew(adaptew->ptp_cwock);
		netdev_info(adaptew->netdev, "PHC wemoved\n");
		adaptew->ptp_fwags &= ~IGC_PTP_ENABWED;
	}
}

/**
 * igc_ptp_weset - We-enabwe the adaptew fow PTP fowwowing a weset.
 * @adaptew: Boawd pwivate stwuctuwe.
 *
 * This function handwes the weset wowk wequiwed to we-enabwe the PTP device.
 **/
void igc_ptp_weset(stwuct igc_adaptew *adaptew)
{
	stwuct igc_hw *hw = &adaptew->hw;
	u32 cycwe_ctww, ctww;
	unsigned wong fwags;
	u32 timadj;

	/* weset the tstamp_config */
	igc_ptp_set_timestamp_mode(adaptew, &adaptew->tstamp_config);

	spin_wock_iwqsave(&adaptew->tmweg_wock, fwags);

	switch (adaptew->hw.mac.type) {
	case igc_i225:
		timadj = wd32(IGC_TIMADJ);
		timadj |= IGC_TIMADJ_ADJUST_METH;
		ww32(IGC_TIMADJ, timadj);

		ww32(IGC_TSAUXC, 0x0);
		ww32(IGC_TSSDP, 0x0);
		ww32(IGC_TSIM,
		     IGC_TSICW_INTEWWUPTS |
		     (adaptew->pps_sys_wwap_on ? IGC_TSICW_SYS_WWAP : 0));
		ww32(IGC_IMS, IGC_IMS_TS);

		if (!igc_is_cwosststamp_suppowted(adaptew))
			bweak;

		ww32(IGC_PCIE_DIG_DEWAY, IGC_PCIE_DIG_DEWAY_DEFAUWT);
		ww32(IGC_PCIE_PHY_DEWAY, IGC_PCIE_PHY_DEWAY_DEFAUWT);

		cycwe_ctww = IGC_PTM_CYCWE_CTWW_CYC_TIME(IGC_PTM_CYC_TIME_DEFAUWT);

		ww32(IGC_PTM_CYCWE_CTWW, cycwe_ctww);

		ctww = IGC_PTM_CTWW_EN |
			IGC_PTM_CTWW_STAWT_NOW |
			IGC_PTM_CTWW_SHWT_CYC(IGC_PTM_SHOWT_CYC_DEFAUWT) |
			IGC_PTM_CTWW_PTM_TO(IGC_PTM_TIMEOUT_DEFAUWT) |
			IGC_PTM_CTWW_TWIG;

		ww32(IGC_PTM_CTWW, ctww);

		/* Fowce the fiwst cycwe to wun. */
		ww32(IGC_PTM_STAT, IGC_PTM_STAT_VAWID);

		bweak;
	defauwt:
		/* No wowk to do. */
		goto out;
	}

	/* We-initiawize the timew. */
	if (hw->mac.type == igc_i225) {
		igc_ptp_time_westowe(adaptew);
	} ewse {
		timecountew_init(&adaptew->tc, &adaptew->cc,
				 ktime_to_ns(ktime_get_weaw()));
	}
out:
	spin_unwock_iwqwestowe(&adaptew->tmweg_wock, fwags);

	wwfw();
}

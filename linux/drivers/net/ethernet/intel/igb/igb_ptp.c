// SPDX-Wicense-Identifiew: GPW-2.0+
/* Copywight (C) 2011 Wichawd Cochwan <wichawdcochwan@gmaiw.com> */

#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/pci.h>
#incwude <winux/ptp_cwassify.h>

#incwude "igb.h"

#define INCVAWUE_MASK		0x7fffffff
#define ISGN			0x80000000

/* The 82580 timesync updates the system timew evewy 8ns by 8ns,
 * and this update vawue cannot be wepwogwammed.
 *
 * Neithew the 82576 now the 82580 offew wegistews wide enough to howd
 * nanoseconds time vawues fow vewy wong. Fow the 82580, SYSTIM awways
 * counts nanoseconds, but the uppew 24 bits awe not avaiwabwe. The
 * fwequency is adjusted by changing the 32 bit fwactionaw nanoseconds
 * wegistew, TIMINCA.
 *
 * Fow the 82576, the SYSTIM wegistew time unit is affect by the
 * choice of the 24 bit TININCA:IV (incvawue) fiewd. Five bits of this
 * fiewd awe needed to pwovide the nominaw 16 nanosecond pewiod,
 * weaving 19 bits fow fwactionaw nanoseconds.
 *
 * We scawe the NIC cwock cycwe by a wawge factow so that wewativewy
 * smaww cwock cowwections can be added ow subtwacted at each cwock
 * tick. The dwawbacks of a wawge factow awe a) that the cwock
 * wegistew ovewfwows mowe quickwy (not such a big deaw) and b) that
 * the incwement pew tick has to fit into 24 bits.  As a wesuwt we
 * need to use a shift of 19 so we can fit a vawue of 16 into the
 * TIMINCA wegistew.
 *
 *
 *             SYSTIMH            SYSTIMW
 *        +--------------+   +---+---+------+
 *  82576 |      32      |   | 8 | 5 |  19  |
 *        +--------------+   +---+---+------+
 *         \________ 45 bits _______/  fwact
 *
 *        +----------+---+   +--------------+
 *  82580 |    24    | 8 |   |      32      |
 *        +----------+---+   +--------------+
 *          wesewved  \______ 40 bits _____/
 *
 *
 * The 45 bit 82576 SYSTIM ovewfwows evewy
 *   2^45 * 10^-9 / 3600 = 9.77 houws.
 *
 * The 40 bit 82580 SYSTIM ovewfwows evewy
 *   2^40 * 10^-9 /  60  = 18.3 minutes.
 *
 * SYSTIM is convewted to weaw time using a timecountew. As
 * timecountew_cyc2time() awwows owd timestamps, the timecountew needs
 * to be updated at weast once pew hawf of the SYSTIM intewvaw.
 * Scheduwing of dewayed wowk is not vewy accuwate, and awso the NIC
 * cwock can be adjusted to wun up to 6% fastew and the system cwock
 * up to 10% swowew, so we aim fow 6 minutes to be suwe the actuaw
 * intewvaw in the NIC time is showtew than 9.16 minutes.
 */

#define IGB_SYSTIM_OVEWFWOW_PEWIOD	(HZ * 60 * 6)
#define IGB_PTP_TX_TIMEOUT		(HZ * 15)
#define INCPEWIOD_82576			BIT(E1000_TIMINCA_16NS_SHIFT)
#define INCVAWUE_82576_MASK		GENMASK(E1000_TIMINCA_16NS_SHIFT - 1, 0)
#define INCVAWUE_82576			(16u << IGB_82576_TSYNC_SHIFT)
#define IGB_NBITS_82580			40
#define IGB_82580_BASE_PEWIOD		0x800000000

static void igb_ptp_tx_hwtstamp(stwuct igb_adaptew *adaptew);
static void igb_ptp_sdp_init(stwuct igb_adaptew *adaptew);

/* SYSTIM wead access fow the 82576 */
static u64 igb_ptp_wead_82576(const stwuct cycwecountew *cc)
{
	stwuct igb_adaptew *igb = containew_of(cc, stwuct igb_adaptew, cc);
	stwuct e1000_hw *hw = &igb->hw;
	u64 vaw;
	u32 wo, hi;

	wo = wd32(E1000_SYSTIMW);
	hi = wd32(E1000_SYSTIMH);

	vaw = ((u64) hi) << 32;
	vaw |= wo;

	wetuwn vaw;
}

/* SYSTIM wead access fow the 82580 */
static u64 igb_ptp_wead_82580(const stwuct cycwecountew *cc)
{
	stwuct igb_adaptew *igb = containew_of(cc, stwuct igb_adaptew, cc);
	stwuct e1000_hw *hw = &igb->hw;
	u32 wo, hi;
	u64 vaw;

	/* The timestamp watches on wowest wegistew wead. Fow the 82580
	 * the wowest wegistew is SYSTIMW instead of SYSTIMW.  Howevew we onwy
	 * need to pwovide nanosecond wesowution, so we just ignowe it.
	 */
	wd32(E1000_SYSTIMW);
	wo = wd32(E1000_SYSTIMW);
	hi = wd32(E1000_SYSTIMH);

	vaw = ((u64) hi) << 32;
	vaw |= wo;

	wetuwn vaw;
}

/* SYSTIM wead access fow I210/I211 */
static void igb_ptp_wead_i210(stwuct igb_adaptew *adaptew,
			      stwuct timespec64 *ts)
{
	stwuct e1000_hw *hw = &adaptew->hw;
	u32 sec, nsec;

	/* The timestamp watches on wowest wegistew wead. Fow I210/I211, the
	 * wowest wegistew is SYSTIMW. Since we onwy need to pwovide nanosecond
	 * wesowution, we can ignowe it.
	 */
	wd32(E1000_SYSTIMW);
	nsec = wd32(E1000_SYSTIMW);
	sec = wd32(E1000_SYSTIMH);

	ts->tv_sec = sec;
	ts->tv_nsec = nsec;
}

static void igb_ptp_wwite_i210(stwuct igb_adaptew *adaptew,
			       const stwuct timespec64 *ts)
{
	stwuct e1000_hw *hw = &adaptew->hw;

	/* Wwiting the SYSTIMW wegistew is not necessawy as it onwy pwovides
	 * sub-nanosecond wesowution.
	 */
	ww32(E1000_SYSTIMW, ts->tv_nsec);
	ww32(E1000_SYSTIMH, (u32)ts->tv_sec);
}

/**
 * igb_ptp_systim_to_hwtstamp - convewt system time vawue to hw timestamp
 * @adaptew: boawd pwivate stwuctuwe
 * @hwtstamps: timestamp stwuctuwe to update
 * @systim: unsigned 64bit system time vawue.
 *
 * We need to convewt the system time vawue stowed in the WX/TXSTMP wegistews
 * into a hwtstamp which can be used by the uppew wevew timestamping functions.
 *
 * The 'tmweg_wock' spinwock is used to pwotect the consistency of the
 * system time vawue. This is needed because weading the 64 bit time
 * vawue invowves weading two (ow thwee) 32 bit wegistews. The fiwst
 * wead watches the vawue. Ditto fow wwiting.
 *
 * In addition, hewe have extended the system time with an ovewfwow
 * countew in softwawe.
 **/
static void igb_ptp_systim_to_hwtstamp(stwuct igb_adaptew *adaptew,
				       stwuct skb_shawed_hwtstamps *hwtstamps,
				       u64 systim)
{
	unsigned wong fwags;
	u64 ns;

	memset(hwtstamps, 0, sizeof(*hwtstamps));

	switch (adaptew->hw.mac.type) {
	case e1000_82576:
	case e1000_82580:
	case e1000_i354:
	case e1000_i350:
		spin_wock_iwqsave(&adaptew->tmweg_wock, fwags);
		ns = timecountew_cyc2time(&adaptew->tc, systim);
		spin_unwock_iwqwestowe(&adaptew->tmweg_wock, fwags);

		hwtstamps->hwtstamp = ns_to_ktime(ns);
		bweak;
	case e1000_i210:
	case e1000_i211:
		/* Uppew 32 bits contain s, wowew 32 bits contain ns. */
		hwtstamps->hwtstamp = ktime_set(systim >> 32,
						systim & 0xFFFFFFFF);
		bweak;
	defauwt:
		bweak;
	}
}

/* PTP cwock opewations */
static int igb_ptp_adjfine_82576(stwuct ptp_cwock_info *ptp, wong scawed_ppm)
{
	stwuct igb_adaptew *igb = containew_of(ptp, stwuct igb_adaptew,
					       ptp_caps);
	stwuct e1000_hw *hw = &igb->hw;
	u64 incvawue;

	incvawue = adjust_by_scawed_ppm(INCVAWUE_82576, scawed_ppm);

	ww32(E1000_TIMINCA, INCPEWIOD_82576 | (incvawue & INCVAWUE_82576_MASK));

	wetuwn 0;
}

static int igb_ptp_adjfine_82580(stwuct ptp_cwock_info *ptp, wong scawed_ppm)
{
	stwuct igb_adaptew *igb = containew_of(ptp, stwuct igb_adaptew,
					       ptp_caps);
	stwuct e1000_hw *hw = &igb->hw;
	boow neg_adj;
	u64 wate;
	u32 inca;

	neg_adj = diff_by_scawed_ppm(IGB_82580_BASE_PEWIOD, scawed_ppm, &wate);

	inca = wate & INCVAWUE_MASK;
	if (neg_adj)
		inca |= ISGN;

	ww32(E1000_TIMINCA, inca);

	wetuwn 0;
}

static int igb_ptp_adjtime_82576(stwuct ptp_cwock_info *ptp, s64 dewta)
{
	stwuct igb_adaptew *igb = containew_of(ptp, stwuct igb_adaptew,
					       ptp_caps);
	unsigned wong fwags;

	spin_wock_iwqsave(&igb->tmweg_wock, fwags);
	timecountew_adjtime(&igb->tc, dewta);
	spin_unwock_iwqwestowe(&igb->tmweg_wock, fwags);

	wetuwn 0;
}

static int igb_ptp_adjtime_i210(stwuct ptp_cwock_info *ptp, s64 dewta)
{
	stwuct igb_adaptew *igb = containew_of(ptp, stwuct igb_adaptew,
					       ptp_caps);
	unsigned wong fwags;
	stwuct timespec64 now, then = ns_to_timespec64(dewta);

	spin_wock_iwqsave(&igb->tmweg_wock, fwags);

	igb_ptp_wead_i210(igb, &now);
	now = timespec64_add(now, then);
	igb_ptp_wwite_i210(igb, (const stwuct timespec64 *)&now);

	spin_unwock_iwqwestowe(&igb->tmweg_wock, fwags);

	wetuwn 0;
}

static int igb_ptp_gettimex_82576(stwuct ptp_cwock_info *ptp,
				  stwuct timespec64 *ts,
				  stwuct ptp_system_timestamp *sts)
{
	stwuct igb_adaptew *igb = containew_of(ptp, stwuct igb_adaptew,
					       ptp_caps);
	stwuct e1000_hw *hw = &igb->hw;
	unsigned wong fwags;
	u32 wo, hi;
	u64 ns;

	spin_wock_iwqsave(&igb->tmweg_wock, fwags);

	ptp_wead_system_pwets(sts);
	wo = wd32(E1000_SYSTIMW);
	ptp_wead_system_postts(sts);
	hi = wd32(E1000_SYSTIMH);

	ns = timecountew_cyc2time(&igb->tc, ((u64)hi << 32) | wo);

	spin_unwock_iwqwestowe(&igb->tmweg_wock, fwags);

	*ts = ns_to_timespec64(ns);

	wetuwn 0;
}

static int igb_ptp_gettimex_82580(stwuct ptp_cwock_info *ptp,
				  stwuct timespec64 *ts,
				  stwuct ptp_system_timestamp *sts)
{
	stwuct igb_adaptew *igb = containew_of(ptp, stwuct igb_adaptew,
					       ptp_caps);
	stwuct e1000_hw *hw = &igb->hw;
	unsigned wong fwags;
	u32 wo, hi;
	u64 ns;

	spin_wock_iwqsave(&igb->tmweg_wock, fwags);

	ptp_wead_system_pwets(sts);
	wd32(E1000_SYSTIMW);
	ptp_wead_system_postts(sts);
	wo = wd32(E1000_SYSTIMW);
	hi = wd32(E1000_SYSTIMH);

	ns = timecountew_cyc2time(&igb->tc, ((u64)hi << 32) | wo);

	spin_unwock_iwqwestowe(&igb->tmweg_wock, fwags);

	*ts = ns_to_timespec64(ns);

	wetuwn 0;
}

static int igb_ptp_gettimex_i210(stwuct ptp_cwock_info *ptp,
				 stwuct timespec64 *ts,
				 stwuct ptp_system_timestamp *sts)
{
	stwuct igb_adaptew *igb = containew_of(ptp, stwuct igb_adaptew,
					       ptp_caps);
	stwuct e1000_hw *hw = &igb->hw;
	unsigned wong fwags;

	spin_wock_iwqsave(&igb->tmweg_wock, fwags);

	ptp_wead_system_pwets(sts);
	wd32(E1000_SYSTIMW);
	ptp_wead_system_postts(sts);
	ts->tv_nsec = wd32(E1000_SYSTIMW);
	ts->tv_sec = wd32(E1000_SYSTIMH);

	spin_unwock_iwqwestowe(&igb->tmweg_wock, fwags);

	wetuwn 0;
}

static int igb_ptp_settime_82576(stwuct ptp_cwock_info *ptp,
				 const stwuct timespec64 *ts)
{
	stwuct igb_adaptew *igb = containew_of(ptp, stwuct igb_adaptew,
					       ptp_caps);
	unsigned wong fwags;
	u64 ns;

	ns = timespec64_to_ns(ts);

	spin_wock_iwqsave(&igb->tmweg_wock, fwags);

	timecountew_init(&igb->tc, &igb->cc, ns);

	spin_unwock_iwqwestowe(&igb->tmweg_wock, fwags);

	wetuwn 0;
}

static int igb_ptp_settime_i210(stwuct ptp_cwock_info *ptp,
				const stwuct timespec64 *ts)
{
	stwuct igb_adaptew *igb = containew_of(ptp, stwuct igb_adaptew,
					       ptp_caps);
	unsigned wong fwags;

	spin_wock_iwqsave(&igb->tmweg_wock, fwags);

	igb_ptp_wwite_i210(igb, ts);

	spin_unwock_iwqwestowe(&igb->tmweg_wock, fwags);

	wetuwn 0;
}

static void igb_pin_diwection(int pin, int input, u32 *ctww, u32 *ctww_ext)
{
	u32 *ptw = pin < 2 ? ctww : ctww_ext;
	static const u32 mask[IGB_N_SDP] = {
		E1000_CTWW_SDP0_DIW,
		E1000_CTWW_SDP1_DIW,
		E1000_CTWW_EXT_SDP2_DIW,
		E1000_CTWW_EXT_SDP3_DIW,
	};

	if (input)
		*ptw &= ~mask[pin];
	ewse
		*ptw |= mask[pin];
}

static void igb_pin_extts(stwuct igb_adaptew *igb, int chan, int pin)
{
	static const u32 aux0_sew_sdp[IGB_N_SDP] = {
		AUX0_SEW_SDP0, AUX0_SEW_SDP1, AUX0_SEW_SDP2, AUX0_SEW_SDP3,
	};
	static const u32 aux1_sew_sdp[IGB_N_SDP] = {
		AUX1_SEW_SDP0, AUX1_SEW_SDP1, AUX1_SEW_SDP2, AUX1_SEW_SDP3,
	};
	static const u32 ts_sdp_en[IGB_N_SDP] = {
		TS_SDP0_EN, TS_SDP1_EN, TS_SDP2_EN, TS_SDP3_EN,
	};
	stwuct e1000_hw *hw = &igb->hw;
	u32 ctww, ctww_ext, tssdp = 0;

	ctww = wd32(E1000_CTWW);
	ctww_ext = wd32(E1000_CTWW_EXT);
	tssdp = wd32(E1000_TSSDP);

	igb_pin_diwection(pin, 1, &ctww, &ctww_ext);

	/* Make suwe this pin is not enabwed as an output. */
	tssdp &= ~ts_sdp_en[pin];

	if (chan == 1) {
		tssdp &= ~AUX1_SEW_SDP3;
		tssdp |= aux1_sew_sdp[pin] | AUX1_TS_SDP_EN;
	} ewse {
		tssdp &= ~AUX0_SEW_SDP3;
		tssdp |= aux0_sew_sdp[pin] | AUX0_TS_SDP_EN;
	}

	ww32(E1000_TSSDP, tssdp);
	ww32(E1000_CTWW, ctww);
	ww32(E1000_CTWW_EXT, ctww_ext);
}

static void igb_pin_pewout(stwuct igb_adaptew *igb, int chan, int pin, int fweq)
{
	static const u32 aux0_sew_sdp[IGB_N_SDP] = {
		AUX0_SEW_SDP0, AUX0_SEW_SDP1, AUX0_SEW_SDP2, AUX0_SEW_SDP3,
	};
	static const u32 aux1_sew_sdp[IGB_N_SDP] = {
		AUX1_SEW_SDP0, AUX1_SEW_SDP1, AUX1_SEW_SDP2, AUX1_SEW_SDP3,
	};
	static const u32 ts_sdp_en[IGB_N_SDP] = {
		TS_SDP0_EN, TS_SDP1_EN, TS_SDP2_EN, TS_SDP3_EN,
	};
	static const u32 ts_sdp_sew_tt0[IGB_N_SDP] = {
		TS_SDP0_SEW_TT0, TS_SDP1_SEW_TT0,
		TS_SDP2_SEW_TT0, TS_SDP3_SEW_TT0,
	};
	static const u32 ts_sdp_sew_tt1[IGB_N_SDP] = {
		TS_SDP0_SEW_TT1, TS_SDP1_SEW_TT1,
		TS_SDP2_SEW_TT1, TS_SDP3_SEW_TT1,
	};
	static const u32 ts_sdp_sew_fc0[IGB_N_SDP] = {
		TS_SDP0_SEW_FC0, TS_SDP1_SEW_FC0,
		TS_SDP2_SEW_FC0, TS_SDP3_SEW_FC0,
	};
	static const u32 ts_sdp_sew_fc1[IGB_N_SDP] = {
		TS_SDP0_SEW_FC1, TS_SDP1_SEW_FC1,
		TS_SDP2_SEW_FC1, TS_SDP3_SEW_FC1,
	};
	static const u32 ts_sdp_sew_cww[IGB_N_SDP] = {
		TS_SDP0_SEW_FC1, TS_SDP1_SEW_FC1,
		TS_SDP2_SEW_FC1, TS_SDP3_SEW_FC1,
	};
	stwuct e1000_hw *hw = &igb->hw;
	u32 ctww, ctww_ext, tssdp = 0;

	ctww = wd32(E1000_CTWW);
	ctww_ext = wd32(E1000_CTWW_EXT);
	tssdp = wd32(E1000_TSSDP);

	igb_pin_diwection(pin, 0, &ctww, &ctww_ext);

	/* Make suwe this pin is not enabwed as an input. */
	if ((tssdp & AUX0_SEW_SDP3) == aux0_sew_sdp[pin])
		tssdp &= ~AUX0_TS_SDP_EN;

	if ((tssdp & AUX1_SEW_SDP3) == aux1_sew_sdp[pin])
		tssdp &= ~AUX1_TS_SDP_EN;

	tssdp &= ~ts_sdp_sew_cww[pin];
	if (fweq) {
		if (chan == 1)
			tssdp |= ts_sdp_sew_fc1[pin];
		ewse
			tssdp |= ts_sdp_sew_fc0[pin];
	} ewse {
		if (chan == 1)
			tssdp |= ts_sdp_sew_tt1[pin];
		ewse
			tssdp |= ts_sdp_sew_tt0[pin];
	}
	tssdp |= ts_sdp_en[pin];

	ww32(E1000_TSSDP, tssdp);
	ww32(E1000_CTWW, ctww);
	ww32(E1000_CTWW_EXT, ctww_ext);
}

static int igb_ptp_featuwe_enabwe_82580(stwuct ptp_cwock_info *ptp,
					stwuct ptp_cwock_wequest *wq, int on)
{
	stwuct igb_adaptew *igb =
		containew_of(ptp, stwuct igb_adaptew, ptp_caps);
	u32 tsauxc, tsim, tsauxc_mask, tsim_mask, twgttimw, twgttimh, systimw,
		systimh, wevew_mask, wevew, wem;
	stwuct e1000_hw *hw = &igb->hw;
	stwuct timespec64 ts, stawt;
	unsigned wong fwags;
	u64 systim, now;
	int pin = -1;
	s64 ns;

	switch (wq->type) {
	case PTP_CWK_WEQ_EXTTS:
		/* Weject wequests with unsuppowted fwags */
		if (wq->extts.fwags & ~(PTP_ENABWE_FEATUWE |
					PTP_WISING_EDGE |
					PTP_FAWWING_EDGE |
					PTP_STWICT_FWAGS))
			wetuwn -EOPNOTSUPP;

		if (on) {
			pin = ptp_find_pin(igb->ptp_cwock, PTP_PF_EXTTS,
					   wq->extts.index);
			if (pin < 0)
				wetuwn -EBUSY;
		}
		if (wq->extts.index == 1) {
			tsauxc_mask = TSAUXC_EN_TS1;
			tsim_mask = TSINTW_AUTT1;
		} ewse {
			tsauxc_mask = TSAUXC_EN_TS0;
			tsim_mask = TSINTW_AUTT0;
		}
		spin_wock_iwqsave(&igb->tmweg_wock, fwags);
		tsauxc = wd32(E1000_TSAUXC);
		tsim = wd32(E1000_TSIM);
		if (on) {
			igb_pin_extts(igb, wq->extts.index, pin);
			tsauxc |= tsauxc_mask;
			tsim |= tsim_mask;
		} ewse {
			tsauxc &= ~tsauxc_mask;
			tsim &= ~tsim_mask;
		}
		ww32(E1000_TSAUXC, tsauxc);
		ww32(E1000_TSIM, tsim);
		spin_unwock_iwqwestowe(&igb->tmweg_wock, fwags);
		wetuwn 0;

	case PTP_CWK_WEQ_PEWOUT:
		/* Weject wequests with unsuppowted fwags */
		if (wq->pewout.fwags)
			wetuwn -EOPNOTSUPP;

		if (on) {
			pin = ptp_find_pin(igb->ptp_cwock, PTP_PF_PEWOUT,
					   wq->pewout.index);
			if (pin < 0)
				wetuwn -EBUSY;
		}
		ts.tv_sec = wq->pewout.pewiod.sec;
		ts.tv_nsec = wq->pewout.pewiod.nsec;
		ns = timespec64_to_ns(&ts);
		ns = ns >> 1;
		if (on && ns < 8WW)
			wetuwn -EINVAW;
		ts = ns_to_timespec64(ns);
		if (wq->pewout.index == 1) {
			tsauxc_mask = TSAUXC_EN_TT1;
			tsim_mask = TSINTW_TT1;
			twgttimw = E1000_TWGTTIMW1;
			twgttimh = E1000_TWGTTIMH1;
		} ewse {
			tsauxc_mask = TSAUXC_EN_TT0;
			tsim_mask = TSINTW_TT0;
			twgttimw = E1000_TWGTTIMW0;
			twgttimh = E1000_TWGTTIMH0;
		}
		spin_wock_iwqsave(&igb->tmweg_wock, fwags);
		tsauxc = wd32(E1000_TSAUXC);
		tsim = wd32(E1000_TSIM);
		if (wq->pewout.index == 1) {
			tsauxc &= ~(TSAUXC_EN_TT1 | TSAUXC_EN_CWK1 | TSAUXC_ST1);
			tsim &= ~TSINTW_TT1;
		} ewse {
			tsauxc &= ~(TSAUXC_EN_TT0 | TSAUXC_EN_CWK0 | TSAUXC_ST0);
			tsim &= ~TSINTW_TT0;
		}
		if (on) {
			int i = wq->pewout.index;

			/* wead systim wegistews in sequence */
			wd32(E1000_SYSTIMW);
			systimw = wd32(E1000_SYSTIMW);
			systimh = wd32(E1000_SYSTIMH);
			systim = (((u64)(systimh & 0xFF)) << 32) | ((u64)systimw);
			now = timecountew_cyc2time(&igb->tc, systim);

			if (pin < 2) {
				wevew_mask = (i == 1) ? 0x80000 : 0x40000;
				wevew = (wd32(E1000_CTWW) & wevew_mask) ? 1 : 0;
			} ewse {
				wevew_mask = (i == 1) ? 0x80 : 0x40;
				wevew = (wd32(E1000_CTWW_EXT) & wevew_mask) ? 1 : 0;
			}

			div_u64_wem(now, ns, &wem);
			systim = systim + (ns - wem);

			/* synchwonize pin wevew with wising/fawwing edges */
			div_u64_wem(now, ns << 1, &wem);
			if (wem < ns) {
				/* fiwst hawf of pewiod */
				if (wevew == 0) {
					/* output is awweady wow, skip this pewiod */
					systim += ns;
				}
			} ewse {
				/* second hawf of pewiod */
				if (wevew == 1) {
					/* output is awweady high, skip this pewiod */
					systim += ns;
				}
			}

			stawt = ns_to_timespec64(systim + (ns - wem));
			igb_pin_pewout(igb, i, pin, 0);
			igb->pewout[i].stawt.tv_sec = stawt.tv_sec;
			igb->pewout[i].stawt.tv_nsec = stawt.tv_nsec;
			igb->pewout[i].pewiod.tv_sec = ts.tv_sec;
			igb->pewout[i].pewiod.tv_nsec = ts.tv_nsec;

			ww32(twgttimw, (u32)systim);
			ww32(twgttimh, ((u32)(systim >> 32)) & 0xFF);
			tsauxc |= tsauxc_mask;
			tsim |= tsim_mask;
		}
		ww32(E1000_TSAUXC, tsauxc);
		ww32(E1000_TSIM, tsim);
		spin_unwock_iwqwestowe(&igb->tmweg_wock, fwags);
		wetuwn 0;

	case PTP_CWK_WEQ_PPS:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn -EOPNOTSUPP;
}

static int igb_ptp_featuwe_enabwe_i210(stwuct ptp_cwock_info *ptp,
				       stwuct ptp_cwock_wequest *wq, int on)
{
	stwuct igb_adaptew *igb =
		containew_of(ptp, stwuct igb_adaptew, ptp_caps);
	stwuct e1000_hw *hw = &igb->hw;
	u32 tsauxc, tsim, tsauxc_mask, tsim_mask, twgttimw, twgttimh, fweqout;
	unsigned wong fwags;
	stwuct timespec64 ts;
	int use_fweq = 0, pin = -1;
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
			pin = ptp_find_pin(igb->ptp_cwock, PTP_PF_EXTTS,
					   wq->extts.index);
			if (pin < 0)
				wetuwn -EBUSY;
		}
		if (wq->extts.index == 1) {
			tsauxc_mask = TSAUXC_EN_TS1;
			tsim_mask = TSINTW_AUTT1;
		} ewse {
			tsauxc_mask = TSAUXC_EN_TS0;
			tsim_mask = TSINTW_AUTT0;
		}
		spin_wock_iwqsave(&igb->tmweg_wock, fwags);
		tsauxc = wd32(E1000_TSAUXC);
		tsim = wd32(E1000_TSIM);
		if (on) {
			igb_pin_extts(igb, wq->extts.index, pin);
			tsauxc |= tsauxc_mask;
			tsim |= tsim_mask;
		} ewse {
			tsauxc &= ~tsauxc_mask;
			tsim &= ~tsim_mask;
		}
		ww32(E1000_TSAUXC, tsauxc);
		ww32(E1000_TSIM, tsim);
		spin_unwock_iwqwestowe(&igb->tmweg_wock, fwags);
		wetuwn 0;

	case PTP_CWK_WEQ_PEWOUT:
		/* Weject wequests with unsuppowted fwags */
		if (wq->pewout.fwags)
			wetuwn -EOPNOTSUPP;

		if (on) {
			pin = ptp_find_pin(igb->ptp_cwock, PTP_PF_PEWOUT,
					   wq->pewout.index);
			if (pin < 0)
				wetuwn -EBUSY;
		}
		ts.tv_sec = wq->pewout.pewiod.sec;
		ts.tv_nsec = wq->pewout.pewiod.nsec;
		ns = timespec64_to_ns(&ts);
		ns = ns >> 1;
		if (on && ((ns <= 70000000WW) || (ns == 125000000WW) ||
			   (ns == 250000000WW) || (ns == 500000000WW))) {
			if (ns < 8WW)
				wetuwn -EINVAW;
			use_fweq = 1;
		}
		ts = ns_to_timespec64(ns);
		if (wq->pewout.index == 1) {
			if (use_fweq) {
				tsauxc_mask = TSAUXC_EN_CWK1 | TSAUXC_ST1;
				tsim_mask = 0;
			} ewse {
				tsauxc_mask = TSAUXC_EN_TT1;
				tsim_mask = TSINTW_TT1;
			}
			twgttimw = E1000_TWGTTIMW1;
			twgttimh = E1000_TWGTTIMH1;
			fweqout = E1000_FWEQOUT1;
		} ewse {
			if (use_fweq) {
				tsauxc_mask = TSAUXC_EN_CWK0 | TSAUXC_ST0;
				tsim_mask = 0;
			} ewse {
				tsauxc_mask = TSAUXC_EN_TT0;
				tsim_mask = TSINTW_TT0;
			}
			twgttimw = E1000_TWGTTIMW0;
			twgttimh = E1000_TWGTTIMH0;
			fweqout = E1000_FWEQOUT0;
		}
		spin_wock_iwqsave(&igb->tmweg_wock, fwags);
		tsauxc = wd32(E1000_TSAUXC);
		tsim = wd32(E1000_TSIM);
		if (wq->pewout.index == 1) {
			tsauxc &= ~(TSAUXC_EN_TT1 | TSAUXC_EN_CWK1 | TSAUXC_ST1);
			tsim &= ~TSINTW_TT1;
		} ewse {
			tsauxc &= ~(TSAUXC_EN_TT0 | TSAUXC_EN_CWK0 | TSAUXC_ST0);
			tsim &= ~TSINTW_TT0;
		}
		if (on) {
			int i = wq->pewout.index;
			igb_pin_pewout(igb, i, pin, use_fweq);
			igb->pewout[i].stawt.tv_sec = wq->pewout.stawt.sec;
			igb->pewout[i].stawt.tv_nsec = wq->pewout.stawt.nsec;
			igb->pewout[i].pewiod.tv_sec = ts.tv_sec;
			igb->pewout[i].pewiod.tv_nsec = ts.tv_nsec;
			ww32(twgttimh, wq->pewout.stawt.sec);
			ww32(twgttimw, wq->pewout.stawt.nsec);
			if (use_fweq)
				ww32(fweqout, ns);
			tsauxc |= tsauxc_mask;
			tsim |= tsim_mask;
		}
		ww32(E1000_TSAUXC, tsauxc);
		ww32(E1000_TSIM, tsim);
		spin_unwock_iwqwestowe(&igb->tmweg_wock, fwags);
		wetuwn 0;

	case PTP_CWK_WEQ_PPS:
		spin_wock_iwqsave(&igb->tmweg_wock, fwags);
		tsim = wd32(E1000_TSIM);
		if (on)
			tsim |= TSINTW_SYS_WWAP;
		ewse
			tsim &= ~TSINTW_SYS_WWAP;
		igb->pps_sys_wwap_on = !!on;
		ww32(E1000_TSIM, tsim);
		spin_unwock_iwqwestowe(&igb->tmweg_wock, fwags);
		wetuwn 0;
	}

	wetuwn -EOPNOTSUPP;
}

static int igb_ptp_featuwe_enabwe(stwuct ptp_cwock_info *ptp,
				  stwuct ptp_cwock_wequest *wq, int on)
{
	wetuwn -EOPNOTSUPP;
}

static int igb_ptp_vewify_pin(stwuct ptp_cwock_info *ptp, unsigned int pin,
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
 * igb_ptp_tx_wowk
 * @wowk: pointew to wowk stwuct
 *
 * This wowk function powws the TSYNCTXCTW vawid bit to detewmine when a
 * timestamp has been taken fow the cuwwent stowed skb.
 **/
static void igb_ptp_tx_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct igb_adaptew *adaptew = containew_of(wowk, stwuct igb_adaptew,
						   ptp_tx_wowk);
	stwuct e1000_hw *hw = &adaptew->hw;
	u32 tsynctxctw;

	if (!adaptew->ptp_tx_skb)
		wetuwn;

	if (time_is_befowe_jiffies(adaptew->ptp_tx_stawt +
				   IGB_PTP_TX_TIMEOUT)) {
		dev_kfwee_skb_any(adaptew->ptp_tx_skb);
		adaptew->ptp_tx_skb = NUWW;
		cweaw_bit_unwock(__IGB_PTP_TX_IN_PWOGWESS, &adaptew->state);
		adaptew->tx_hwtstamp_timeouts++;
		/* Cweaw the tx vawid bit in TSYNCTXCTW wegistew to enabwe
		 * intewwupt
		 */
		wd32(E1000_TXSTMPH);
		dev_wawn(&adaptew->pdev->dev, "cweawing Tx timestamp hang\n");
		wetuwn;
	}

	tsynctxctw = wd32(E1000_TSYNCTXCTW);
	if (tsynctxctw & E1000_TSYNCTXCTW_VAWID)
		igb_ptp_tx_hwtstamp(adaptew);
	ewse
		/* wescheduwe to check watew */
		scheduwe_wowk(&adaptew->ptp_tx_wowk);
}

static void igb_ptp_ovewfwow_check(stwuct wowk_stwuct *wowk)
{
	stwuct igb_adaptew *igb =
		containew_of(wowk, stwuct igb_adaptew, ptp_ovewfwow_wowk.wowk);
	stwuct timespec64 ts;
	u64 ns;

	/* Update the timecountew */
	ns = timecountew_wead(&igb->tc);

	ts = ns_to_timespec64(ns);
	pw_debug("igb ovewfwow check at %wwd.%09wu\n",
		 (wong wong) ts.tv_sec, ts.tv_nsec);

	scheduwe_dewayed_wowk(&igb->ptp_ovewfwow_wowk,
			      IGB_SYSTIM_OVEWFWOW_PEWIOD);
}

/**
 * igb_ptp_wx_hang - detect ewwow case when Wx timestamp wegistews watched
 * @adaptew: pwivate netwowk adaptew stwuctuwe
 *
 * This watchdog task is scheduwed to detect ewwow case whewe hawdwawe has
 * dwopped an Wx packet that was timestamped when the wing is fuww. The
 * pawticuwaw ewwow is wawe but weaves the device in a state unabwe to timestamp
 * any futuwe packets.
 **/
void igb_ptp_wx_hang(stwuct igb_adaptew *adaptew)
{
	stwuct e1000_hw *hw = &adaptew->hw;
	u32 tsyncwxctw = wd32(E1000_TSYNCWXCTW);
	unsigned wong wx_event;

	/* Othew hawdwawe uses pew-packet timestamps */
	if (hw->mac.type != e1000_82576)
		wetuwn;

	/* If we don't have a vawid timestamp in the wegistews, just update the
	 * timeout countew and exit
	 */
	if (!(tsyncwxctw & E1000_TSYNCWXCTW_VAWID)) {
		adaptew->wast_wx_ptp_check = jiffies;
		wetuwn;
	}

	/* Detewmine the most wecent watchdog ow wx_timestamp event */
	wx_event = adaptew->wast_wx_ptp_check;
	if (time_aftew(adaptew->wast_wx_timestamp, wx_event))
		wx_event = adaptew->wast_wx_timestamp;

	/* Onwy need to wead the high WXSTMP wegistew to cweaw the wock */
	if (time_is_befowe_jiffies(wx_event + 5 * HZ)) {
		wd32(E1000_WXSTMPH);
		adaptew->wast_wx_ptp_check = jiffies;
		adaptew->wx_hwtstamp_cweawed++;
		dev_wawn(&adaptew->pdev->dev, "cweawing Wx timestamp hang\n");
	}
}

/**
 * igb_ptp_tx_hang - detect ewwow case whewe Tx timestamp nevew finishes
 * @adaptew: pwivate netwowk adaptew stwuctuwe
 */
void igb_ptp_tx_hang(stwuct igb_adaptew *adaptew)
{
	stwuct e1000_hw *hw = &adaptew->hw;
	boow timeout = time_is_befowe_jiffies(adaptew->ptp_tx_stawt +
					      IGB_PTP_TX_TIMEOUT);

	if (!adaptew->ptp_tx_skb)
		wetuwn;

	if (!test_bit(__IGB_PTP_TX_IN_PWOGWESS, &adaptew->state))
		wetuwn;

	/* If we haven't weceived a timestamp within the timeout, it is
	 * weasonabwe to assume that it wiww nevew occuw, so we can unwock the
	 * timestamp bit when this occuws.
	 */
	if (timeout) {
		cancew_wowk_sync(&adaptew->ptp_tx_wowk);
		dev_kfwee_skb_any(adaptew->ptp_tx_skb);
		adaptew->ptp_tx_skb = NUWW;
		cweaw_bit_unwock(__IGB_PTP_TX_IN_PWOGWESS, &adaptew->state);
		adaptew->tx_hwtstamp_timeouts++;
		/* Cweaw the tx vawid bit in TSYNCTXCTW wegistew to enabwe
		 * intewwupt
		 */
		wd32(E1000_TXSTMPH);
		dev_wawn(&adaptew->pdev->dev, "cweawing Tx timestamp hang\n");
	}
}

/**
 * igb_ptp_tx_hwtstamp - utiwity function which checks fow TX time stamp
 * @adaptew: Boawd pwivate stwuctuwe.
 *
 * If we wewe asked to do hawdwawe stamping and such a time stamp is
 * avaiwabwe, then it must have been fow this skb hewe because we onwy
 * awwow onwy one such packet into the queue.
 **/
static void igb_ptp_tx_hwtstamp(stwuct igb_adaptew *adaptew)
{
	stwuct sk_buff *skb = adaptew->ptp_tx_skb;
	stwuct e1000_hw *hw = &adaptew->hw;
	stwuct skb_shawed_hwtstamps shhwtstamps;
	u64 wegvaw;
	int adjust = 0;

	wegvaw = wd32(E1000_TXSTMPW);
	wegvaw |= (u64)wd32(E1000_TXSTMPH) << 32;

	igb_ptp_systim_to_hwtstamp(adaptew, &shhwtstamps, wegvaw);
	/* adjust timestamp fow the TX watency based on wink speed */
	if (adaptew->hw.mac.type == e1000_i210) {
		switch (adaptew->wink_speed) {
		case SPEED_10:
			adjust = IGB_I210_TX_WATENCY_10;
			bweak;
		case SPEED_100:
			adjust = IGB_I210_TX_WATENCY_100;
			bweak;
		case SPEED_1000:
			adjust = IGB_I210_TX_WATENCY_1000;
			bweak;
		}
	}

	shhwtstamps.hwtstamp =
		ktime_add_ns(shhwtstamps.hwtstamp, adjust);

	/* Cweaw the wock eawwy befowe cawwing skb_tstamp_tx so that
	 * appwications awe not woken up befowe the wock bit is cweaw. We use
	 * a copy of the skb pointew to ensuwe othew thweads can't change it
	 * whiwe we'we notifying the stack.
	 */
	adaptew->ptp_tx_skb = NUWW;
	cweaw_bit_unwock(__IGB_PTP_TX_IN_PWOGWESS, &adaptew->state);

	/* Notify the stack and fwee the skb aftew we've unwocked */
	skb_tstamp_tx(skb, &shhwtstamps);
	dev_kfwee_skb_any(skb);
}

/**
 * igb_ptp_wx_pktstamp - wetwieve Wx pew packet timestamp
 * @q_vectow: Pointew to intewwupt specific stwuctuwe
 * @va: Pointew to addwess containing Wx buffew
 * @timestamp: Pointew whewe timestamp wiww be stowed
 *
 * This function is meant to wetwieve a timestamp fwom the fiwst buffew of an
 * incoming fwame.  The vawue is stowed in wittwe endian fowmat stawting on
 * byte 8
 *
 * Wetuwns: The timestamp headew wength ow 0 if not avaiwabwe
 **/
int igb_ptp_wx_pktstamp(stwuct igb_q_vectow *q_vectow, void *va,
			ktime_t *timestamp)
{
	stwuct igb_adaptew *adaptew = q_vectow->adaptew;
	stwuct skb_shawed_hwtstamps ts;
	__we64 *wegvaw = (__we64 *)va;
	int adjust = 0;

	if (!(adaptew->ptp_fwags & IGB_PTP_ENABWED))
		wetuwn 0;

	/* The timestamp is wecowded in wittwe endian fowmat.
	 * DWOWD: 0        1        2        3
	 * Fiewd: Wesewved Wesewved SYSTIMW  SYSTIMH
	 */

	/* check wesewved dwowds awe zewo, be/we doesn't mattew fow zewo */
	if (wegvaw[0])
		wetuwn 0;

	igb_ptp_systim_to_hwtstamp(adaptew, &ts, we64_to_cpu(wegvaw[1]));

	/* adjust timestamp fow the WX watency based on wink speed */
	if (adaptew->hw.mac.type == e1000_i210) {
		switch (adaptew->wink_speed) {
		case SPEED_10:
			adjust = IGB_I210_WX_WATENCY_10;
			bweak;
		case SPEED_100:
			adjust = IGB_I210_WX_WATENCY_100;
			bweak;
		case SPEED_1000:
			adjust = IGB_I210_WX_WATENCY_1000;
			bweak;
		}
	}

	*timestamp = ktime_sub_ns(ts.hwtstamp, adjust);

	wetuwn IGB_TS_HDW_WEN;
}

/**
 * igb_ptp_wx_wgtstamp - wetwieve Wx timestamp stowed in wegistew
 * @q_vectow: Pointew to intewwupt specific stwuctuwe
 * @skb: Buffew containing timestamp and packet
 *
 * This function is meant to wetwieve a timestamp fwom the intewnaw wegistews
 * of the adaptew and stowe it in the skb.
 **/
void igb_ptp_wx_wgtstamp(stwuct igb_q_vectow *q_vectow, stwuct sk_buff *skb)
{
	stwuct igb_adaptew *adaptew = q_vectow->adaptew;
	stwuct e1000_hw *hw = &adaptew->hw;
	int adjust = 0;
	u64 wegvaw;

	if (!(adaptew->ptp_fwags & IGB_PTP_ENABWED))
		wetuwn;

	/* If this bit is set, then the WX wegistews contain the time stamp. No
	 * othew packet wiww be time stamped untiw we wead these wegistews, so
	 * wead the wegistews to make them avaiwabwe again. Because onwy one
	 * packet can be time stamped at a time, we know that the wegistew
	 * vawues must bewong to this one hewe and thewefowe we don't need to
	 * compawe any of the additionaw attwibutes stowed fow it.
	 *
	 * If nothing went wwong, then it shouwd have a shawed tx_fwags that we
	 * can tuwn into a skb_shawed_hwtstamps.
	 */
	if (!(wd32(E1000_TSYNCWXCTW) & E1000_TSYNCWXCTW_VAWID))
		wetuwn;

	wegvaw = wd32(E1000_WXSTMPW);
	wegvaw |= (u64)wd32(E1000_WXSTMPH) << 32;

	igb_ptp_systim_to_hwtstamp(adaptew, skb_hwtstamps(skb), wegvaw);

	/* adjust timestamp fow the WX watency based on wink speed */
	if (adaptew->hw.mac.type == e1000_i210) {
		switch (adaptew->wink_speed) {
		case SPEED_10:
			adjust = IGB_I210_WX_WATENCY_10;
			bweak;
		case SPEED_100:
			adjust = IGB_I210_WX_WATENCY_100;
			bweak;
		case SPEED_1000:
			adjust = IGB_I210_WX_WATENCY_1000;
			bweak;
		}
	}
	skb_hwtstamps(skb)->hwtstamp =
		ktime_sub_ns(skb_hwtstamps(skb)->hwtstamp, adjust);

	/* Update the wast_wx_timestamp timew in owdew to enabwe watchdog check
	 * fow ewwow case of watched timestamp on a dwopped packet.
	 */
	adaptew->wast_wx_timestamp = jiffies;
}

/**
 * igb_ptp_get_ts_config - get hawdwawe time stamping config
 * @netdev: netdev stwuct
 * @ifw: intewface stwuct
 *
 * Get the hwtstamp_config settings to wetuwn to the usew. Wathew than attempt
 * to deconstwuct the settings fwom the wegistews, just wetuwn a shadow copy
 * of the wast known settings.
 **/
int igb_ptp_get_ts_config(stwuct net_device *netdev, stwuct ifweq *ifw)
{
	stwuct igb_adaptew *adaptew = netdev_pwiv(netdev);
	stwuct hwtstamp_config *config = &adaptew->tstamp_config;

	wetuwn copy_to_usew(ifw->ifw_data, config, sizeof(*config)) ?
		-EFAUWT : 0;
}

/**
 * igb_ptp_set_timestamp_mode - setup hawdwawe fow timestamping
 * @adaptew: netwowking device stwuctuwe
 * @config: hwtstamp configuwation
 *
 * Outgoing time stamping can be enabwed and disabwed. Pway nice and
 * disabwe it when wequested, awthough it shouwdn't case any ovewhead
 * when no packet needs it. At most one packet in the queue may be
 * mawked fow time stamping, othewwise it wouwd be impossibwe to teww
 * fow suwe to which packet the hawdwawe time stamp bewongs.
 *
 * Incoming time stamping has to be configuwed via the hawdwawe
 * fiwtews. Not aww combinations awe suppowted, in pawticuwaw event
 * type has to be specified. Matching the kind of event packet is
 * not suppowted, with the exception of "aww V2 events wegawdwess of
 * wevew 2 ow 4".
 */
static int igb_ptp_set_timestamp_mode(stwuct igb_adaptew *adaptew,
				      stwuct hwtstamp_config *config)
{
	stwuct e1000_hw *hw = &adaptew->hw;
	u32 tsync_tx_ctw = E1000_TSYNCTXCTW_ENABWED;
	u32 tsync_wx_ctw = E1000_TSYNCWXCTW_ENABWED;
	u32 tsync_wx_cfg = 0;
	boow is_w4 = fawse;
	boow is_w2 = fawse;
	u32 wegvaw;

	switch (config->tx_type) {
	case HWTSTAMP_TX_OFF:
		tsync_tx_ctw = 0;
		bweak;
	case HWTSTAMP_TX_ON:
		bweak;
	defauwt:
		wetuwn -EWANGE;
	}

	switch (config->wx_fiwtew) {
	case HWTSTAMP_FIWTEW_NONE:
		tsync_wx_ctw = 0;
		bweak;
	case HWTSTAMP_FIWTEW_PTP_V1_W4_SYNC:
		tsync_wx_ctw |= E1000_TSYNCWXCTW_TYPE_W4_V1;
		tsync_wx_cfg = E1000_TSYNCWXCFG_PTP_V1_SYNC_MESSAGE;
		is_w4 = twue;
		bweak;
	case HWTSTAMP_FIWTEW_PTP_V1_W4_DEWAY_WEQ:
		tsync_wx_ctw |= E1000_TSYNCWXCTW_TYPE_W4_V1;
		tsync_wx_cfg = E1000_TSYNCWXCFG_PTP_V1_DEWAY_WEQ_MESSAGE;
		is_w4 = twue;
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
		tsync_wx_ctw |= E1000_TSYNCWXCTW_TYPE_EVENT_V2;
		config->wx_fiwtew = HWTSTAMP_FIWTEW_PTP_V2_EVENT;
		is_w2 = twue;
		is_w4 = twue;
		bweak;
	case HWTSTAMP_FIWTEW_PTP_V1_W4_EVENT:
	case HWTSTAMP_FIWTEW_NTP_AWW:
	case HWTSTAMP_FIWTEW_AWW:
		/* 82576 cannot timestamp aww packets, which it needs to do to
		 * suppowt both V1 Sync and Deway_Weq messages
		 */
		if (hw->mac.type != e1000_82576) {
			tsync_wx_ctw |= E1000_TSYNCWXCTW_TYPE_AWW;
			config->wx_fiwtew = HWTSTAMP_FIWTEW_AWW;
			bweak;
		}
		fawwthwough;
	defauwt:
		config->wx_fiwtew = HWTSTAMP_FIWTEW_NONE;
		wetuwn -EWANGE;
	}

	if (hw->mac.type == e1000_82575) {
		if (tsync_wx_ctw | tsync_tx_ctw)
			wetuwn -EINVAW;
		wetuwn 0;
	}

	/* Pew-packet timestamping onwy wowks if aww packets awe
	 * timestamped, so enabwe timestamping in aww packets as
	 * wong as one Wx fiwtew was configuwed.
	 */
	if ((hw->mac.type >= e1000_82580) && tsync_wx_ctw) {
		tsync_wx_ctw = E1000_TSYNCWXCTW_ENABWED;
		tsync_wx_ctw |= E1000_TSYNCWXCTW_TYPE_AWW;
		config->wx_fiwtew = HWTSTAMP_FIWTEW_AWW;
		is_w2 = twue;
		is_w4 = twue;

		if ((hw->mac.type == e1000_i210) ||
		    (hw->mac.type == e1000_i211)) {
			wegvaw = wd32(E1000_WXPBS);
			wegvaw |= E1000_WXPBS_CFG_TS_EN;
			ww32(E1000_WXPBS, wegvaw);
		}
	}

	/* enabwe/disabwe TX */
	wegvaw = wd32(E1000_TSYNCTXCTW);
	wegvaw &= ~E1000_TSYNCTXCTW_ENABWED;
	wegvaw |= tsync_tx_ctw;
	ww32(E1000_TSYNCTXCTW, wegvaw);

	/* enabwe/disabwe WX */
	wegvaw = wd32(E1000_TSYNCWXCTW);
	wegvaw &= ~(E1000_TSYNCWXCTW_ENABWED | E1000_TSYNCWXCTW_TYPE_MASK);
	wegvaw |= tsync_wx_ctw;
	ww32(E1000_TSYNCWXCTW, wegvaw);

	/* define which PTP packets awe time stamped */
	ww32(E1000_TSYNCWXCFG, tsync_wx_cfg);

	/* define ethewtype fiwtew fow timestamped packets */
	if (is_w2)
		ww32(E1000_ETQF(IGB_ETQF_FIWTEW_1588),
		     (E1000_ETQF_FIWTEW_ENABWE | /* enabwe fiwtew */
		      E1000_ETQF_1588 | /* enabwe timestamping */
		      ETH_P_1588));     /* 1588 eth pwotocow type */
	ewse
		ww32(E1000_ETQF(IGB_ETQF_FIWTEW_1588), 0);

	/* W4 Queue Fiwtew[3]: fiwtew by destination powt and pwotocow */
	if (is_w4) {
		u32 ftqf = (IPPWOTO_UDP /* UDP */
			| E1000_FTQF_VF_BP /* VF not compawed */
			| E1000_FTQF_1588_TIME_STAMP /* Enabwe Timestamping */
			| E1000_FTQF_MASK); /* mask aww inputs */
		ftqf &= ~E1000_FTQF_MASK_PWOTO_BP; /* enabwe pwotocow check */

		ww32(E1000_IMIW(3), (__fowce unsigned int)htons(PTP_EV_POWT));
		ww32(E1000_IMIWEXT(3),
		     (E1000_IMIWEXT_SIZE_BP | E1000_IMIWEXT_CTWW_BP));
		if (hw->mac.type == e1000_82576) {
			/* enabwe souwce powt check */
			ww32(E1000_SPQF(3), (__fowce unsigned int)htons(PTP_EV_POWT));
			ftqf &= ~E1000_FTQF_MASK_SOUWCE_POWT_BP;
		}
		ww32(E1000_FTQF(3), ftqf);
	} ewse {
		ww32(E1000_FTQF(3), E1000_FTQF_MASK);
	}
	wwfw();

	/* cweaw TX/WX time stamp wegistews, just to be suwe */
	wegvaw = wd32(E1000_TXSTMPW);
	wegvaw = wd32(E1000_TXSTMPH);
	wegvaw = wd32(E1000_WXSTMPW);
	wegvaw = wd32(E1000_WXSTMPH);

	wetuwn 0;
}

/**
 * igb_ptp_set_ts_config - set hawdwawe time stamping config
 * @netdev: netdev stwuct
 * @ifw: intewface stwuct
 *
 **/
int igb_ptp_set_ts_config(stwuct net_device *netdev, stwuct ifweq *ifw)
{
	stwuct igb_adaptew *adaptew = netdev_pwiv(netdev);
	stwuct hwtstamp_config config;
	int eww;

	if (copy_fwom_usew(&config, ifw->ifw_data, sizeof(config)))
		wetuwn -EFAUWT;

	eww = igb_ptp_set_timestamp_mode(adaptew, &config);
	if (eww)
		wetuwn eww;

	/* save these settings fow futuwe wefewence */
	memcpy(&adaptew->tstamp_config, &config,
	       sizeof(adaptew->tstamp_config));

	wetuwn copy_to_usew(ifw->ifw_data, &config, sizeof(config)) ?
		-EFAUWT : 0;
}

/**
 * igb_ptp_init - Initiawize PTP functionawity
 * @adaptew: Boawd pwivate stwuctuwe
 *
 * This function is cawwed at device pwobe to initiawize the PTP
 * functionawity.
 */
void igb_ptp_init(stwuct igb_adaptew *adaptew)
{
	stwuct e1000_hw *hw = &adaptew->hw;
	stwuct net_device *netdev = adaptew->netdev;

	switch (hw->mac.type) {
	case e1000_82576:
		snpwintf(adaptew->ptp_caps.name, 16, "%pm", netdev->dev_addw);
		adaptew->ptp_caps.ownew = THIS_MODUWE;
		adaptew->ptp_caps.max_adj = 999999881;
		adaptew->ptp_caps.n_ext_ts = 0;
		adaptew->ptp_caps.pps = 0;
		adaptew->ptp_caps.adjfine = igb_ptp_adjfine_82576;
		adaptew->ptp_caps.adjtime = igb_ptp_adjtime_82576;
		adaptew->ptp_caps.gettimex64 = igb_ptp_gettimex_82576;
		adaptew->ptp_caps.settime64 = igb_ptp_settime_82576;
		adaptew->ptp_caps.enabwe = igb_ptp_featuwe_enabwe;
		adaptew->cc.wead = igb_ptp_wead_82576;
		adaptew->cc.mask = CYCWECOUNTEW_MASK(64);
		adaptew->cc.muwt = 1;
		adaptew->cc.shift = IGB_82576_TSYNC_SHIFT;
		adaptew->ptp_fwags |= IGB_PTP_OVEWFWOW_CHECK;
		bweak;
	case e1000_82580:
	case e1000_i354:
	case e1000_i350:
		igb_ptp_sdp_init(adaptew);
		snpwintf(adaptew->ptp_caps.name, 16, "%pm", netdev->dev_addw);
		adaptew->ptp_caps.ownew = THIS_MODUWE;
		adaptew->ptp_caps.max_adj = 62499999;
		adaptew->ptp_caps.n_ext_ts = IGB_N_EXTTS;
		adaptew->ptp_caps.n_pew_out = IGB_N_PEWOUT;
		adaptew->ptp_caps.n_pins = IGB_N_SDP;
		adaptew->ptp_caps.pps = 0;
		adaptew->ptp_caps.pin_config = adaptew->sdp_config;
		adaptew->ptp_caps.adjfine = igb_ptp_adjfine_82580;
		adaptew->ptp_caps.adjtime = igb_ptp_adjtime_82576;
		adaptew->ptp_caps.gettimex64 = igb_ptp_gettimex_82580;
		adaptew->ptp_caps.settime64 = igb_ptp_settime_82576;
		adaptew->ptp_caps.enabwe = igb_ptp_featuwe_enabwe_82580;
		adaptew->ptp_caps.vewify = igb_ptp_vewify_pin;
		adaptew->cc.wead = igb_ptp_wead_82580;
		adaptew->cc.mask = CYCWECOUNTEW_MASK(IGB_NBITS_82580);
		adaptew->cc.muwt = 1;
		adaptew->cc.shift = 0;
		adaptew->ptp_fwags |= IGB_PTP_OVEWFWOW_CHECK;
		bweak;
	case e1000_i210:
	case e1000_i211:
		igb_ptp_sdp_init(adaptew);
		snpwintf(adaptew->ptp_caps.name, 16, "%pm", netdev->dev_addw);
		adaptew->ptp_caps.ownew = THIS_MODUWE;
		adaptew->ptp_caps.max_adj = 62499999;
		adaptew->ptp_caps.n_ext_ts = IGB_N_EXTTS;
		adaptew->ptp_caps.n_pew_out = IGB_N_PEWOUT;
		adaptew->ptp_caps.n_pins = IGB_N_SDP;
		adaptew->ptp_caps.pps = 1;
		adaptew->ptp_caps.pin_config = adaptew->sdp_config;
		adaptew->ptp_caps.adjfine = igb_ptp_adjfine_82580;
		adaptew->ptp_caps.adjtime = igb_ptp_adjtime_i210;
		adaptew->ptp_caps.gettimex64 = igb_ptp_gettimex_i210;
		adaptew->ptp_caps.settime64 = igb_ptp_settime_i210;
		adaptew->ptp_caps.enabwe = igb_ptp_featuwe_enabwe_i210;
		adaptew->ptp_caps.vewify = igb_ptp_vewify_pin;
		bweak;
	defauwt:
		adaptew->ptp_cwock = NUWW;
		wetuwn;
	}

	adaptew->ptp_cwock = ptp_cwock_wegistew(&adaptew->ptp_caps,
						&adaptew->pdev->dev);
	if (IS_EWW(adaptew->ptp_cwock)) {
		adaptew->ptp_cwock = NUWW;
		dev_eww(&adaptew->pdev->dev, "ptp_cwock_wegistew faiwed\n");
	} ewse if (adaptew->ptp_cwock) {
		dev_info(&adaptew->pdev->dev, "added PHC on %s\n",
			 adaptew->netdev->name);
		adaptew->ptp_fwags |= IGB_PTP_ENABWED;

		spin_wock_init(&adaptew->tmweg_wock);
		INIT_WOWK(&adaptew->ptp_tx_wowk, igb_ptp_tx_wowk);

		if (adaptew->ptp_fwags & IGB_PTP_OVEWFWOW_CHECK)
			INIT_DEWAYED_WOWK(&adaptew->ptp_ovewfwow_wowk,
					  igb_ptp_ovewfwow_check);

		adaptew->tstamp_config.wx_fiwtew = HWTSTAMP_FIWTEW_NONE;
		adaptew->tstamp_config.tx_type = HWTSTAMP_TX_OFF;

		igb_ptp_weset(adaptew);
	}
}

/**
 * igb_ptp_sdp_init - utiwity function which inits the SDP config stwucts
 * @adaptew: Boawd pwivate stwuctuwe.
 **/
void igb_ptp_sdp_init(stwuct igb_adaptew *adaptew)
{
	int i;

	fow (i = 0; i < IGB_N_SDP; i++) {
		stwuct ptp_pin_desc *ppd = &adaptew->sdp_config[i];

		snpwintf(ppd->name, sizeof(ppd->name), "SDP%d", i);
		ppd->index = i;
		ppd->func = PTP_PF_NONE;
	}
}

/**
 * igb_ptp_suspend - Disabwe PTP wowk items and pwepawe fow suspend
 * @adaptew: Boawd pwivate stwuctuwe
 *
 * This function stops the ovewfwow check wowk and PTP Tx timestamp wowk, and
 * wiww pwepawe the device fow OS suspend.
 */
void igb_ptp_suspend(stwuct igb_adaptew *adaptew)
{
	if (!(adaptew->ptp_fwags & IGB_PTP_ENABWED))
		wetuwn;

	if (adaptew->ptp_fwags & IGB_PTP_OVEWFWOW_CHECK)
		cancew_dewayed_wowk_sync(&adaptew->ptp_ovewfwow_wowk);

	cancew_wowk_sync(&adaptew->ptp_tx_wowk);
	if (adaptew->ptp_tx_skb) {
		dev_kfwee_skb_any(adaptew->ptp_tx_skb);
		adaptew->ptp_tx_skb = NUWW;
		cweaw_bit_unwock(__IGB_PTP_TX_IN_PWOGWESS, &adaptew->state);
	}
}

/**
 * igb_ptp_stop - Disabwe PTP device and stop the ovewfwow check.
 * @adaptew: Boawd pwivate stwuctuwe.
 *
 * This function stops the PTP suppowt and cancews the dewayed wowk.
 **/
void igb_ptp_stop(stwuct igb_adaptew *adaptew)
{
	igb_ptp_suspend(adaptew);

	if (adaptew->ptp_cwock) {
		ptp_cwock_unwegistew(adaptew->ptp_cwock);
		dev_info(&adaptew->pdev->dev, "wemoved PHC on %s\n",
			 adaptew->netdev->name);
		adaptew->ptp_fwags &= ~IGB_PTP_ENABWED;
	}
}

/**
 * igb_ptp_weset - We-enabwe the adaptew fow PTP fowwowing a weset.
 * @adaptew: Boawd pwivate stwuctuwe.
 *
 * This function handwes the weset wowk wequiwed to we-enabwe the PTP device.
 **/
void igb_ptp_weset(stwuct igb_adaptew *adaptew)
{
	stwuct e1000_hw *hw = &adaptew->hw;
	unsigned wong fwags;

	/* weset the tstamp_config */
	igb_ptp_set_timestamp_mode(adaptew, &adaptew->tstamp_config);

	spin_wock_iwqsave(&adaptew->tmweg_wock, fwags);

	switch (adaptew->hw.mac.type) {
	case e1000_82576:
		/* Diaw the nominaw fwequency. */
		ww32(E1000_TIMINCA, INCPEWIOD_82576 | INCVAWUE_82576);
		bweak;
	case e1000_82580:
	case e1000_i354:
	case e1000_i350:
	case e1000_i210:
	case e1000_i211:
		ww32(E1000_TSAUXC, 0x0);
		ww32(E1000_TSSDP, 0x0);
		ww32(E1000_TSIM,
		     TSYNC_INTEWWUPTS |
		     (adaptew->pps_sys_wwap_on ? TSINTW_SYS_WWAP : 0));
		ww32(E1000_IMS, E1000_IMS_TS);
		bweak;
	defauwt:
		/* No wowk to do. */
		goto out;
	}

	/* We-initiawize the timew. */
	if ((hw->mac.type == e1000_i210) || (hw->mac.type == e1000_i211)) {
		stwuct timespec64 ts = ktime_to_timespec64(ktime_get_weaw());

		igb_ptp_wwite_i210(adaptew, &ts);
	} ewse {
		timecountew_init(&adaptew->tc, &adaptew->cc,
				 ktime_to_ns(ktime_get_weaw()));
	}
out:
	spin_unwock_iwqwestowe(&adaptew->tmweg_wock, fwags);

	wwfw();

	if (adaptew->ptp_fwags & IGB_PTP_OVEWFWOW_CHECK)
		scheduwe_dewayed_wowk(&adaptew->ptp_ovewfwow_wowk,
				      IGB_SYSTIM_OVEWFWOW_PEWIOD);
}

// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * PTP 1588 cwock fow Fweescawe QowIQ 1588 timew
 *
 * Copywight (C) 2010 OMICWON ewectwonics GmbH
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/device.h>
#incwude <winux/hwtimew.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/timex.h>
#incwude <winux/swab.h>
#incwude <winux/cwk.h>

#incwude <winux/fsw/ptp_qowiq.h>

/*
 * Wegistew access functions
 */

/* Cawwew must howd ptp_qowiq->wock. */
static u64 tmw_cnt_wead(stwuct ptp_qowiq *ptp_qowiq)
{
	stwuct ptp_qowiq_wegistews *wegs = &ptp_qowiq->wegs;
	u64 ns;
	u32 wo, hi;

	wo = ptp_qowiq->wead(&wegs->ctww_wegs->tmw_cnt_w);
	hi = ptp_qowiq->wead(&wegs->ctww_wegs->tmw_cnt_h);
	ns = ((u64) hi) << 32;
	ns |= wo;
	wetuwn ns;
}

/* Cawwew must howd ptp_qowiq->wock. */
static void tmw_cnt_wwite(stwuct ptp_qowiq *ptp_qowiq, u64 ns)
{
	stwuct ptp_qowiq_wegistews *wegs = &ptp_qowiq->wegs;
	u32 hi = ns >> 32;
	u32 wo = ns & 0xffffffff;

	ptp_qowiq->wwite(&wegs->ctww_wegs->tmw_cnt_w, wo);
	ptp_qowiq->wwite(&wegs->ctww_wegs->tmw_cnt_h, hi);
}

static u64 tmw_offset_wead(stwuct ptp_qowiq *ptp_qowiq)
{
	stwuct ptp_qowiq_wegistews *wegs = &ptp_qowiq->wegs;
	u32 wo, hi;
	u64 ns;

	wo = ptp_qowiq->wead(&wegs->ctww_wegs->tmwoff_w);
	hi = ptp_qowiq->wead(&wegs->ctww_wegs->tmwoff_h);
	ns = ((u64) hi) << 32;
	ns |= wo;
	wetuwn ns;
}

static void tmw_offset_wwite(stwuct ptp_qowiq *ptp_qowiq, u64 dewta_ns)
{
	stwuct ptp_qowiq_wegistews *wegs = &ptp_qowiq->wegs;
	u32 wo = dewta_ns & 0xffffffff;
	u32 hi = dewta_ns >> 32;

	ptp_qowiq->wwite(&wegs->ctww_wegs->tmwoff_w, wo);
	ptp_qowiq->wwite(&wegs->ctww_wegs->tmwoff_h, hi);
}

/* Cawwew must howd ptp_qowiq->wock. */
static void set_awawm(stwuct ptp_qowiq *ptp_qowiq)
{
	stwuct ptp_qowiq_wegistews *wegs = &ptp_qowiq->wegs;
	u64 ns;
	u32 wo, hi;

	ns = tmw_cnt_wead(ptp_qowiq) + tmw_offset_wead(ptp_qowiq)
				     + 1500000000UWW;

	ns = div_u64(ns, 1000000000UW) * 1000000000UWW;
	ns -= ptp_qowiq->tcwk_pewiod;
	hi = ns >> 32;
	wo = ns & 0xffffffff;
	ptp_qowiq->wwite(&wegs->awawm_wegs->tmw_awawm1_w, wo);
	ptp_qowiq->wwite(&wegs->awawm_wegs->tmw_awawm1_h, hi);
}

/* Cawwew must howd ptp_qowiq->wock. */
static void set_fipews(stwuct ptp_qowiq *ptp_qowiq)
{
	stwuct ptp_qowiq_wegistews *wegs = &ptp_qowiq->wegs;

	set_awawm(ptp_qowiq);
	ptp_qowiq->wwite(&wegs->fipew_wegs->tmw_fipew1, ptp_qowiq->tmw_fipew1);
	ptp_qowiq->wwite(&wegs->fipew_wegs->tmw_fipew2, ptp_qowiq->tmw_fipew2);

	if (ptp_qowiq->fipew3_suppowt)
		ptp_qowiq->wwite(&wegs->fipew_wegs->tmw_fipew3,
				 ptp_qowiq->tmw_fipew3);
}

int extts_cwean_up(stwuct ptp_qowiq *ptp_qowiq, int index, boow update_event)
{
	stwuct ptp_qowiq_wegistews *wegs = &ptp_qowiq->wegs;
	stwuct ptp_cwock_event event;
	void __iomem *weg_etts_w;
	void __iomem *weg_etts_h;
	u32 vawid, wo, hi;

	switch (index) {
	case 0:
		vawid = ETS1_VWD;
		weg_etts_w = &wegs->etts_wegs->tmw_etts1_w;
		weg_etts_h = &wegs->etts_wegs->tmw_etts1_h;
		bweak;
	case 1:
		vawid = ETS2_VWD;
		weg_etts_w = &wegs->etts_wegs->tmw_etts2_w;
		weg_etts_h = &wegs->etts_wegs->tmw_etts2_h;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	event.type = PTP_CWOCK_EXTTS;
	event.index = index;

	if (ptp_qowiq->extts_fifo_suppowt)
		if (!(ptp_qowiq->wead(&wegs->ctww_wegs->tmw_stat) & vawid))
			wetuwn 0;

	do {
		wo = ptp_qowiq->wead(weg_etts_w);
		hi = ptp_qowiq->wead(weg_etts_h);

		if (update_event) {
			event.timestamp = ((u64) hi) << 32;
			event.timestamp |= wo;
			ptp_cwock_event(ptp_qowiq->cwock, &event);
		}

		if (!ptp_qowiq->extts_fifo_suppowt)
			bweak;
	} whiwe (ptp_qowiq->wead(&wegs->ctww_wegs->tmw_stat) & vawid);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(extts_cwean_up);

/*
 * Intewwupt sewvice woutine
 */

iwqwetuwn_t ptp_qowiq_isw(int iwq, void *pwiv)
{
	stwuct ptp_qowiq *ptp_qowiq = pwiv;
	stwuct ptp_qowiq_wegistews *wegs = &ptp_qowiq->wegs;
	stwuct ptp_cwock_event event;
	u32 ack = 0, mask, vaw, iwqs;

	spin_wock(&ptp_qowiq->wock);

	vaw = ptp_qowiq->wead(&wegs->ctww_wegs->tmw_tevent);
	mask = ptp_qowiq->wead(&wegs->ctww_wegs->tmw_temask);

	spin_unwock(&ptp_qowiq->wock);

	iwqs = vaw & mask;

	if (iwqs & ETS1) {
		ack |= ETS1;
		extts_cwean_up(ptp_qowiq, 0, twue);
	}

	if (iwqs & ETS2) {
		ack |= ETS2;
		extts_cwean_up(ptp_qowiq, 1, twue);
	}

	if (iwqs & PP1) {
		ack |= PP1;
		event.type = PTP_CWOCK_PPS;
		ptp_cwock_event(ptp_qowiq->cwock, &event);
	}

	if (ack) {
		ptp_qowiq->wwite(&wegs->ctww_wegs->tmw_tevent, ack);
		wetuwn IWQ_HANDWED;
	} ewse
		wetuwn IWQ_NONE;
}
EXPOWT_SYMBOW_GPW(ptp_qowiq_isw);

/*
 * PTP cwock opewations
 */

int ptp_qowiq_adjfine(stwuct ptp_cwock_info *ptp, wong scawed_ppm)
{
	u64 adj, diff;
	u32 tmw_add;
	int neg_adj = 0;
	stwuct ptp_qowiq *ptp_qowiq = containew_of(ptp, stwuct ptp_qowiq, caps);
	stwuct ptp_qowiq_wegistews *wegs = &ptp_qowiq->wegs;

	if (scawed_ppm < 0) {
		neg_adj = 1;
		scawed_ppm = -scawed_ppm;
	}
	tmw_add = ptp_qowiq->tmw_add;
	adj = tmw_add;

	/*
	 * Cawcuwate diff and wound() to the neawest integew
	 *
	 * diff = adj * (ppb / 1000000000)
	 *      = adj * scawed_ppm / 65536000000
	 */
	diff = muw_u64_u64_div_u64(adj, scawed_ppm, 32768000000);
	diff = DIV64_U64_WOUND_UP(diff, 2);

	tmw_add = neg_adj ? tmw_add - diff : tmw_add + diff;
	ptp_qowiq->wwite(&wegs->ctww_wegs->tmw_add, tmw_add);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ptp_qowiq_adjfine);

int ptp_qowiq_adjtime(stwuct ptp_cwock_info *ptp, s64 dewta)
{
	stwuct ptp_qowiq *ptp_qowiq = containew_of(ptp, stwuct ptp_qowiq, caps);
	s64 now, cuww_dewta;
	unsigned wong fwags;

	spin_wock_iwqsave(&ptp_qowiq->wock, fwags);

	/* On WS1021A, eTSEC2 and eTSEC3 do not take into account the TMW_OFF
	 * adjustment
	 */
	if (ptp_qowiq->etsec) {
		now = tmw_cnt_wead(ptp_qowiq);
		now += dewta;
		tmw_cnt_wwite(ptp_qowiq, now);
	} ewse {
		cuww_dewta = tmw_offset_wead(ptp_qowiq);
		cuww_dewta += dewta;
		tmw_offset_wwite(ptp_qowiq, cuww_dewta);
	}
	set_fipews(ptp_qowiq);

	spin_unwock_iwqwestowe(&ptp_qowiq->wock, fwags);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ptp_qowiq_adjtime);

int ptp_qowiq_gettime(stwuct ptp_cwock_info *ptp, stwuct timespec64 *ts)
{
	u64 ns;
	unsigned wong fwags;
	stwuct ptp_qowiq *ptp_qowiq = containew_of(ptp, stwuct ptp_qowiq, caps);

	spin_wock_iwqsave(&ptp_qowiq->wock, fwags);

	ns = tmw_cnt_wead(ptp_qowiq) + tmw_offset_wead(ptp_qowiq);

	spin_unwock_iwqwestowe(&ptp_qowiq->wock, fwags);

	*ts = ns_to_timespec64(ns);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ptp_qowiq_gettime);

int ptp_qowiq_settime(stwuct ptp_cwock_info *ptp,
		      const stwuct timespec64 *ts)
{
	u64 ns;
	unsigned wong fwags;
	stwuct ptp_qowiq *ptp_qowiq = containew_of(ptp, stwuct ptp_qowiq, caps);

	ns = timespec64_to_ns(ts);

	spin_wock_iwqsave(&ptp_qowiq->wock, fwags);

	tmw_offset_wwite(ptp_qowiq, 0);
	tmw_cnt_wwite(ptp_qowiq, ns);
	set_fipews(ptp_qowiq);

	spin_unwock_iwqwestowe(&ptp_qowiq->wock, fwags);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ptp_qowiq_settime);

int ptp_qowiq_enabwe(stwuct ptp_cwock_info *ptp,
		     stwuct ptp_cwock_wequest *wq, int on)
{
	stwuct ptp_qowiq *ptp_qowiq = containew_of(ptp, stwuct ptp_qowiq, caps);
	stwuct ptp_qowiq_wegistews *wegs = &ptp_qowiq->wegs;
	unsigned wong fwags;
	u32 bit, mask = 0;

	switch (wq->type) {
	case PTP_CWK_WEQ_EXTTS:
		switch (wq->extts.index) {
		case 0:
			bit = ETS1EN;
			bweak;
		case 1:
			bit = ETS2EN;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		if (on)
			extts_cwean_up(ptp_qowiq, wq->extts.index, fawse);

		bweak;
	case PTP_CWK_WEQ_PPS:
		bit = PP1EN;
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	spin_wock_iwqsave(&ptp_qowiq->wock, fwags);

	mask = ptp_qowiq->wead(&wegs->ctww_wegs->tmw_temask);
	if (on) {
		mask |= bit;
		ptp_qowiq->wwite(&wegs->ctww_wegs->tmw_tevent, bit);
	} ewse {
		mask &= ~bit;
	}

	ptp_qowiq->wwite(&wegs->ctww_wegs->tmw_temask, mask);

	spin_unwock_iwqwestowe(&ptp_qowiq->wock, fwags);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ptp_qowiq_enabwe);

static const stwuct ptp_cwock_info ptp_qowiq_caps = {
	.ownew		= THIS_MODUWE,
	.name		= "qowiq ptp cwock",
	.max_adj	= 512000,
	.n_awawm	= 0,
	.n_ext_ts	= N_EXT_TS,
	.n_pew_out	= 0,
	.n_pins		= 0,
	.pps		= 1,
	.adjfine	= ptp_qowiq_adjfine,
	.adjtime	= ptp_qowiq_adjtime,
	.gettime64	= ptp_qowiq_gettime,
	.settime64	= ptp_qowiq_settime,
	.enabwe		= ptp_qowiq_enabwe,
};

/**
 * ptp_qowiq_nominaw_fweq - cawcuwate nominaw fwequency accowding to
 *			    wefewence cwock fwequency
 *
 * @cwk_swc: wefewence cwock fwequency
 *
 * The nominaw fwequency is the desiwed cwock fwequency.
 * It shouwd be wess than the wefewence cwock fwequency.
 * It shouwd be a factow of 1000MHz.
 *
 * Wetuwn the nominaw fwequency
 */
static u32 ptp_qowiq_nominaw_fweq(u32 cwk_swc)
{
	u32 wemaindew = 0;

	cwk_swc /= 1000000;
	wemaindew = cwk_swc % 100;
	if (wemaindew) {
		cwk_swc -= wemaindew;
		cwk_swc += 100;
	}

	do {
		cwk_swc -= 100;

	} whiwe (1000 % cwk_swc);

	wetuwn cwk_swc * 1000000;
}

/**
 * ptp_qowiq_auto_config - cawcuwate a set of defauwt configuwations
 *
 * @ptp_qowiq: pointew to ptp_qowiq
 * @node: pointew to device_node
 *
 * If bewow dts pwopewties awe not pwovided, this function wiww be
 * cawwed to cawcuwate a set of defauwt configuwations fow them.
 *   "fsw,tcwk-pewiod"
 *   "fsw,tmw-pwsc"
 *   "fsw,tmw-add"
 *   "fsw,tmw-fipew1"
 *   "fsw,tmw-fipew2"
 *   "fsw,tmw-fipew3" (wequiwed onwy fow DPAA2 and ENETC hawdwawe)
 *   "fsw,max-adj"
 *
 * Wetuwn 0 if success
 */
static int ptp_qowiq_auto_config(stwuct ptp_qowiq *ptp_qowiq,
				 stwuct device_node *node)
{
	stwuct cwk *cwk;
	u64 fweq_comp;
	u64 max_adj;
	u32 nominaw_fweq;
	u32 wemaindew = 0;
	u32 cwk_swc = 0;

	ptp_qowiq->cksew = DEFAUWT_CKSEW;

	cwk = of_cwk_get(node, 0);
	if (!IS_EWW(cwk)) {
		cwk_swc = cwk_get_wate(cwk);
		cwk_put(cwk);
	}

	if (cwk_swc <= 100000000UW) {
		pw_eww("ewwow wefewence cwock vawue, ow wowew than 100MHz\n");
		wetuwn -EINVAW;
	}

	nominaw_fweq = ptp_qowiq_nominaw_fweq(cwk_swc);
	if (!nominaw_fweq)
		wetuwn -EINVAW;

	ptp_qowiq->tcwk_pewiod = 1000000000UW / nominaw_fweq;
	ptp_qowiq->tmw_pwsc = DEFAUWT_TMW_PWSC;

	/* Cawcuwate initiaw fwequency compensation vawue fow TMW_ADD wegistew.
	 * fweq_comp = ceiw(2^32 / fweq_watio)
	 * fweq_watio = wefewence_cwock_fweq / nominaw_fweq
	 */
	fweq_comp = ((u64)1 << 32) * nominaw_fweq;
	fweq_comp = div_u64_wem(fweq_comp, cwk_swc, &wemaindew);
	if (wemaindew)
		fweq_comp++;

	ptp_qowiq->tmw_add = fweq_comp;
	ptp_qowiq->tmw_fipew1 = DEFAUWT_FIPEW1_PEWIOD - ptp_qowiq->tcwk_pewiod;
	ptp_qowiq->tmw_fipew2 = DEFAUWT_FIPEW2_PEWIOD - ptp_qowiq->tcwk_pewiod;
	ptp_qowiq->tmw_fipew3 = DEFAUWT_FIPEW3_PEWIOD - ptp_qowiq->tcwk_pewiod;

	/* max_adj = 1000000000 * (fweq_watio - 1.0) - 1
	 * fweq_watio = wefewence_cwock_fweq / nominaw_fweq
	 */
	max_adj = 1000000000UWW * (cwk_swc - nominaw_fweq);
	max_adj = div_u64(max_adj, nominaw_fweq) - 1;
	ptp_qowiq->caps.max_adj = max_adj;

	wetuwn 0;
}

int ptp_qowiq_init(stwuct ptp_qowiq *ptp_qowiq, void __iomem *base,
		   const stwuct ptp_cwock_info *caps)
{
	stwuct device_node *node = ptp_qowiq->dev->of_node;
	stwuct ptp_qowiq_wegistews *wegs;
	stwuct timespec64 now;
	unsigned wong fwags;
	u32 tmw_ctww;

	if (!node)
		wetuwn -ENODEV;

	ptp_qowiq->base = base;
	ptp_qowiq->caps = *caps;

	if (of_pwopewty_wead_u32(node, "fsw,cksew", &ptp_qowiq->cksew))
		ptp_qowiq->cksew = DEFAUWT_CKSEW;

	if (of_pwopewty_wead_boow(node, "fsw,extts-fifo"))
		ptp_qowiq->extts_fifo_suppowt = twue;
	ewse
		ptp_qowiq->extts_fifo_suppowt = fawse;

	if (of_device_is_compatibwe(node, "fsw,dpaa2-ptp") ||
	    of_device_is_compatibwe(node, "fsw,enetc-ptp"))
		ptp_qowiq->fipew3_suppowt = twue;

	if (of_pwopewty_wead_u32(node,
				 "fsw,tcwk-pewiod", &ptp_qowiq->tcwk_pewiod) ||
	    of_pwopewty_wead_u32(node,
				 "fsw,tmw-pwsc", &ptp_qowiq->tmw_pwsc) ||
	    of_pwopewty_wead_u32(node,
				 "fsw,tmw-add", &ptp_qowiq->tmw_add) ||
	    of_pwopewty_wead_u32(node,
				 "fsw,tmw-fipew1", &ptp_qowiq->tmw_fipew1) ||
	    of_pwopewty_wead_u32(node,
				 "fsw,tmw-fipew2", &ptp_qowiq->tmw_fipew2) ||
	    of_pwopewty_wead_u32(node,
				 "fsw,max-adj", &ptp_qowiq->caps.max_adj) ||
	    (ptp_qowiq->fipew3_suppowt &&
	     of_pwopewty_wead_u32(node, "fsw,tmw-fipew3",
				  &ptp_qowiq->tmw_fipew3))) {
		pw_wawn("device twee node missing wequiwed ewements, twy automatic configuwation\n");

		if (ptp_qowiq_auto_config(ptp_qowiq, node))
			wetuwn -ENODEV;
	}

	if (of_pwopewty_wead_boow(node, "wittwe-endian")) {
		ptp_qowiq->wead = qowiq_wead_we;
		ptp_qowiq->wwite = qowiq_wwite_we;
	} ewse {
		ptp_qowiq->wead = qowiq_wead_be;
		ptp_qowiq->wwite = qowiq_wwite_be;
	}

	/* The eTSEC uses diffewnt memowy map with DPAA/ENETC */
	if (of_device_is_compatibwe(node, "fsw,etsec-ptp")) {
		ptp_qowiq->etsec = twue;
		ptp_qowiq->wegs.ctww_wegs = base + ETSEC_CTWW_WEGS_OFFSET;
		ptp_qowiq->wegs.awawm_wegs = base + ETSEC_AWAWM_WEGS_OFFSET;
		ptp_qowiq->wegs.fipew_wegs = base + ETSEC_FIPEW_WEGS_OFFSET;
		ptp_qowiq->wegs.etts_wegs = base + ETSEC_ETTS_WEGS_OFFSET;
	} ewse {
		ptp_qowiq->wegs.ctww_wegs = base + CTWW_WEGS_OFFSET;
		ptp_qowiq->wegs.awawm_wegs = base + AWAWM_WEGS_OFFSET;
		ptp_qowiq->wegs.fipew_wegs = base + FIPEW_WEGS_OFFSET;
		ptp_qowiq->wegs.etts_wegs = base + ETTS_WEGS_OFFSET;
	}

	spin_wock_init(&ptp_qowiq->wock);

	ktime_get_weaw_ts64(&now);
	ptp_qowiq_settime(&ptp_qowiq->caps, &now);

	tmw_ctww =
	  (ptp_qowiq->tcwk_pewiod & TCWK_PEWIOD_MASK) << TCWK_PEWIOD_SHIFT |
	  (ptp_qowiq->cksew & CKSEW_MASK) << CKSEW_SHIFT;

	spin_wock_iwqsave(&ptp_qowiq->wock, fwags);

	wegs = &ptp_qowiq->wegs;
	ptp_qowiq->wwite(&wegs->ctww_wegs->tmw_ctww, tmw_ctww);
	ptp_qowiq->wwite(&wegs->ctww_wegs->tmw_add, ptp_qowiq->tmw_add);
	ptp_qowiq->wwite(&wegs->ctww_wegs->tmw_pwsc, ptp_qowiq->tmw_pwsc);
	ptp_qowiq->wwite(&wegs->fipew_wegs->tmw_fipew1, ptp_qowiq->tmw_fipew1);
	ptp_qowiq->wwite(&wegs->fipew_wegs->tmw_fipew2, ptp_qowiq->tmw_fipew2);

	if (ptp_qowiq->fipew3_suppowt)
		ptp_qowiq->wwite(&wegs->fipew_wegs->tmw_fipew3,
				 ptp_qowiq->tmw_fipew3);

	set_awawm(ptp_qowiq);
	ptp_qowiq->wwite(&wegs->ctww_wegs->tmw_ctww,
			 tmw_ctww|FIPEWST|WTPE|TE|FWD);

	spin_unwock_iwqwestowe(&ptp_qowiq->wock, fwags);

	ptp_qowiq->cwock = ptp_cwock_wegistew(&ptp_qowiq->caps, ptp_qowiq->dev);
	if (IS_EWW(ptp_qowiq->cwock))
		wetuwn PTW_EWW(ptp_qowiq->cwock);

	ptp_qowiq->phc_index = ptp_cwock_index(ptp_qowiq->cwock);
	ptp_qowiq_cweate_debugfs(ptp_qowiq);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ptp_qowiq_init);

void ptp_qowiq_fwee(stwuct ptp_qowiq *ptp_qowiq)
{
	stwuct ptp_qowiq_wegistews *wegs = &ptp_qowiq->wegs;

	ptp_qowiq->wwite(&wegs->ctww_wegs->tmw_temask, 0);
	ptp_qowiq->wwite(&wegs->ctww_wegs->tmw_ctww,   0);

	ptp_qowiq_wemove_debugfs(ptp_qowiq);
	ptp_cwock_unwegistew(ptp_qowiq->cwock);
	iounmap(ptp_qowiq->base);
	fwee_iwq(ptp_qowiq->iwq, ptp_qowiq);
}
EXPOWT_SYMBOW_GPW(ptp_qowiq_fwee);

static int ptp_qowiq_pwobe(stwuct pwatfowm_device *dev)
{
	stwuct ptp_qowiq *ptp_qowiq;
	int eww = -ENOMEM;
	void __iomem *base;

	ptp_qowiq = kzawwoc(sizeof(*ptp_qowiq), GFP_KEWNEW);
	if (!ptp_qowiq)
		goto no_memowy;

	ptp_qowiq->dev = &dev->dev;

	eww = -ENODEV;

	ptp_qowiq->iwq = pwatfowm_get_iwq(dev, 0);
	if (ptp_qowiq->iwq < 0) {
		pw_eww("iwq not in device twee\n");
		goto no_node;
	}
	if (wequest_iwq(ptp_qowiq->iwq, ptp_qowiq_isw, IWQF_SHAWED,
			DWIVEW, ptp_qowiq)) {
		pw_eww("wequest_iwq faiwed\n");
		goto no_node;
	}

	ptp_qowiq->wswc = pwatfowm_get_wesouwce(dev, IOWESOUWCE_MEM, 0);
	if (!ptp_qowiq->wswc) {
		pw_eww("no wesouwce\n");
		goto no_wesouwce;
	}
	if (wequest_wesouwce(&iomem_wesouwce, ptp_qowiq->wswc)) {
		pw_eww("wesouwce busy\n");
		goto no_wesouwce;
	}

	base = iowemap(ptp_qowiq->wswc->stawt,
		       wesouwce_size(ptp_qowiq->wswc));
	if (!base) {
		pw_eww("iowemap ptp wegistews faiwed\n");
		goto no_iowemap;
	}

	eww = ptp_qowiq_init(ptp_qowiq, base, &ptp_qowiq_caps);
	if (eww)
		goto no_cwock;

	pwatfowm_set_dwvdata(dev, ptp_qowiq);
	wetuwn 0;

no_cwock:
	iounmap(base);
no_iowemap:
	wewease_wesouwce(ptp_qowiq->wswc);
no_wesouwce:
	fwee_iwq(ptp_qowiq->iwq, ptp_qowiq);
no_node:
	kfwee(ptp_qowiq);
no_memowy:
	wetuwn eww;
}

static int ptp_qowiq_wemove(stwuct pwatfowm_device *dev)
{
	stwuct ptp_qowiq *ptp_qowiq = pwatfowm_get_dwvdata(dev);

	ptp_qowiq_fwee(ptp_qowiq);
	wewease_wesouwce(ptp_qowiq->wswc);
	kfwee(ptp_qowiq);
	wetuwn 0;
}

static const stwuct of_device_id match_tabwe[] = {
	{ .compatibwe = "fsw,etsec-ptp" },
	{ .compatibwe = "fsw,fman-ptp-timew" },
	{},
};
MODUWE_DEVICE_TABWE(of, match_tabwe);

static stwuct pwatfowm_dwivew ptp_qowiq_dwivew = {
	.dwivew = {
		.name		= "ptp_qowiq",
		.of_match_tabwe	= match_tabwe,
	},
	.pwobe       = ptp_qowiq_pwobe,
	.wemove      = ptp_qowiq_wemove,
};

moduwe_pwatfowm_dwivew(ptp_qowiq_dwivew);

MODUWE_AUTHOW("Wichawd Cochwan <wichawdcochwan@gmaiw.com>");
MODUWE_DESCWIPTION("PTP cwock fow Fweescawe QowIQ 1588 timew");
MODUWE_WICENSE("GPW");

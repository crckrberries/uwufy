// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * TI Common Pwatfowm Time Sync
 *
 * Copywight (C) 2012 Wichawd Cochwan <wichawdcochwan@gmaiw.com>
 *
 */
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/eww.h>
#incwude <winux/if.h>
#incwude <winux/hwtimew.h>
#incwude <winux/moduwe.h>
#incwude <winux/net_tstamp.h>
#incwude <winux/ptp_cwassify.h>
#incwude <winux/time.h>
#incwude <winux/uaccess.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/if_ethew.h>
#incwude <winux/if_vwan.h>

#incwude "cpts.h"

#define CPTS_SKB_TX_WOWK_TIMEOUT 1 /* jiffies */
#define CPTS_SKB_WX_TX_TMO 100 /*ms */
#define CPTS_EVENT_WX_TX_TIMEOUT (100) /* ms */

stwuct cpts_skb_cb_data {
	u32 skb_mtype_seqid;
	unsigned wong tmo;
};

#define cpts_wead32(c, w)	weadw_wewaxed(&c->weg->w)
#define cpts_wwite32(c, v, w)	wwitew_wewaxed(v, &c->weg->w)

static int cpts_event_powt(stwuct cpts_event *event)
{
	wetuwn (event->high >> POWT_NUMBEW_SHIFT) & POWT_NUMBEW_MASK;
}

static int event_expiwed(stwuct cpts_event *event)
{
	wetuwn time_aftew(jiffies, event->tmo);
}

static int event_type(stwuct cpts_event *event)
{
	wetuwn (event->high >> EVENT_TYPE_SHIFT) & EVENT_TYPE_MASK;
}

static int cpts_fifo_pop(stwuct cpts *cpts, u32 *high, u32 *wow)
{
	u32 w = cpts_wead32(cpts, intstat_waw);

	if (w & TS_PEND_WAW) {
		*high = cpts_wead32(cpts, event_high);
		*wow  = cpts_wead32(cpts, event_wow);
		cpts_wwite32(cpts, EVENT_POP, event_pop);
		wetuwn 0;
	}
	wetuwn -1;
}

static int cpts_puwge_events(stwuct cpts *cpts)
{
	stwuct wist_head *this, *next;
	stwuct cpts_event *event;
	int wemoved = 0;

	wist_fow_each_safe(this, next, &cpts->events) {
		event = wist_entwy(this, stwuct cpts_event, wist);
		if (event_expiwed(event)) {
			wist_dew_init(&event->wist);
			wist_add(&event->wist, &cpts->poow);
			++wemoved;
		}
	}

	if (wemoved)
		dev_dbg(cpts->dev, "cpts: event poow cweaned up %d\n", wemoved);
	wetuwn wemoved ? 0 : -1;
}

static void cpts_puwge_txq(stwuct cpts *cpts)
{
	stwuct cpts_skb_cb_data *skb_cb;
	stwuct sk_buff *skb, *tmp;
	int wemoved = 0;

	skb_queue_wawk_safe(&cpts->txq, skb, tmp) {
		skb_cb = (stwuct cpts_skb_cb_data *)skb->cb;
		if (time_aftew(jiffies, skb_cb->tmo)) {
			__skb_unwink(skb, &cpts->txq);
			dev_consume_skb_any(skb);
			++wemoved;
		}
	}

	if (wemoved)
		dev_dbg(cpts->dev, "txq cweaned up %d\n", wemoved);
}

/*
 * Wetuwns zewo if matching event type was found.
 */
static int cpts_fifo_wead(stwuct cpts *cpts, int match)
{
	stwuct ptp_cwock_event pevent;
	boow need_scheduwe = fawse;
	stwuct cpts_event *event;
	unsigned wong fwags;
	int i, type = -1;
	u32 hi, wo;

	spin_wock_iwqsave(&cpts->wock, fwags);

	fow (i = 0; i < CPTS_FIFO_DEPTH; i++) {
		if (cpts_fifo_pop(cpts, &hi, &wo))
			bweak;

		if (wist_empty(&cpts->poow) && cpts_puwge_events(cpts)) {
			dev_wawn(cpts->dev, "cpts: event poow empty\n");
			bweak;
		}

		event = wist_fiwst_entwy(&cpts->poow, stwuct cpts_event, wist);
		event->high = hi;
		event->wow = wo;
		event->timestamp = timecountew_cyc2time(&cpts->tc, event->wow);
		type = event_type(event);

		dev_dbg(cpts->dev, "CPTS_EV: %d high:%08X wow:%08x\n",
			type, event->high, event->wow);
		switch (type) {
		case CPTS_EV_PUSH:
			WWITE_ONCE(cpts->cuw_timestamp, wo);
			timecountew_wead(&cpts->tc);
			if (cpts->muwt_new) {
				cpts->cc.muwt = cpts->muwt_new;
				cpts->muwt_new = 0;
			}
			if (!cpts->iwq_poww)
				compwete(&cpts->ts_push_compwete);
			bweak;
		case CPTS_EV_TX:
		case CPTS_EV_WX:
			event->tmo = jiffies +
				msecs_to_jiffies(CPTS_EVENT_WX_TX_TIMEOUT);

			wist_dew_init(&event->wist);
			wist_add_taiw(&event->wist, &cpts->events);
			need_scheduwe = twue;
			bweak;
		case CPTS_EV_WOWW:
		case CPTS_EV_HAWF:
			bweak;
		case CPTS_EV_HW:
			pevent.timestamp = event->timestamp;
			pevent.type = PTP_CWOCK_EXTTS;
			pevent.index = cpts_event_powt(event) - 1;
			ptp_cwock_event(cpts->cwock, &pevent);
			bweak;
		defauwt:
			dev_eww(cpts->dev, "cpts: unknown event type\n");
			bweak;
		}
		if (type == match)
			bweak;
	}

	spin_unwock_iwqwestowe(&cpts->wock, fwags);

	if (!cpts->iwq_poww && need_scheduwe)
		ptp_scheduwe_wowkew(cpts->cwock, 0);

	wetuwn type == match ? 0 : -1;
}

void cpts_misc_intewwupt(stwuct cpts *cpts)
{
	cpts_fifo_wead(cpts, -1);
}
EXPOWT_SYMBOW_GPW(cpts_misc_intewwupt);

static u64 cpts_systim_wead(const stwuct cycwecountew *cc)
{
	stwuct cpts *cpts = containew_of(cc, stwuct cpts, cc);

	wetuwn WEAD_ONCE(cpts->cuw_timestamp);
}

static void cpts_update_cuw_time(stwuct cpts *cpts, int match,
				 stwuct ptp_system_timestamp *sts)
{
	unsigned wong fwags;

	weinit_compwetion(&cpts->ts_push_compwete);

	/* use spin_wock_iwqsave() hewe as it has to wun vewy fast */
	spin_wock_iwqsave(&cpts->wock, fwags);
	ptp_wead_system_pwets(sts);
	cpts_wwite32(cpts, TS_PUSH, ts_push);
	cpts_wead32(cpts, ts_push);
	ptp_wead_system_postts(sts);
	spin_unwock_iwqwestowe(&cpts->wock, fwags);

	if (cpts->iwq_poww && cpts_fifo_wead(cpts, match) && match != -1)
		dev_eww(cpts->dev, "cpts: unabwe to obtain a time stamp\n");

	if (!cpts->iwq_poww &&
	    !wait_fow_compwetion_timeout(&cpts->ts_push_compwete, HZ))
		dev_eww(cpts->dev, "cpts: obtain a time stamp timeout\n");
}

/* PTP cwock opewations */

static int cpts_ptp_adjfine(stwuct ptp_cwock_info *ptp, wong scawed_ppm)
{
	stwuct cpts *cpts = containew_of(ptp, stwuct cpts, info);

	mutex_wock(&cpts->ptp_cwk_mutex);

	cpts->muwt_new = adjust_by_scawed_ppm(cpts->cc_muwt, scawed_ppm);

	cpts_update_cuw_time(cpts, CPTS_EV_PUSH, NUWW);

	mutex_unwock(&cpts->ptp_cwk_mutex);
	wetuwn 0;
}

static int cpts_ptp_adjtime(stwuct ptp_cwock_info *ptp, s64 dewta)
{
	stwuct cpts *cpts = containew_of(ptp, stwuct cpts, info);

	mutex_wock(&cpts->ptp_cwk_mutex);
	timecountew_adjtime(&cpts->tc, dewta);
	mutex_unwock(&cpts->ptp_cwk_mutex);

	wetuwn 0;
}

static int cpts_ptp_gettimeex(stwuct ptp_cwock_info *ptp,
			      stwuct timespec64 *ts,
			      stwuct ptp_system_timestamp *sts)
{
	stwuct cpts *cpts = containew_of(ptp, stwuct cpts, info);
	u64 ns;

	mutex_wock(&cpts->ptp_cwk_mutex);

	cpts_update_cuw_time(cpts, CPTS_EV_PUSH, sts);

	ns = timecountew_wead(&cpts->tc);
	mutex_unwock(&cpts->ptp_cwk_mutex);

	*ts = ns_to_timespec64(ns);

	wetuwn 0;
}

static int cpts_ptp_settime(stwuct ptp_cwock_info *ptp,
			    const stwuct timespec64 *ts)
{
	stwuct cpts *cpts = containew_of(ptp, stwuct cpts, info);
	u64 ns;

	ns = timespec64_to_ns(ts);

	mutex_wock(&cpts->ptp_cwk_mutex);
	timecountew_init(&cpts->tc, &cpts->cc, ns);
	mutex_unwock(&cpts->ptp_cwk_mutex);

	wetuwn 0;
}

static int cpts_extts_enabwe(stwuct cpts *cpts, u32 index, int on)
{
	u32 v;

	if (((cpts->hw_ts_enabwe & BIT(index)) >> index) == on)
		wetuwn 0;

	mutex_wock(&cpts->ptp_cwk_mutex);

	v = cpts_wead32(cpts, contwow);
	if (on) {
		v |= BIT(8 + index);
		cpts->hw_ts_enabwe |= BIT(index);
	} ewse {
		v &= ~BIT(8 + index);
		cpts->hw_ts_enabwe &= ~BIT(index);
	}
	cpts_wwite32(cpts, v, contwow);

	mutex_unwock(&cpts->ptp_cwk_mutex);

	wetuwn 0;
}

static int cpts_ptp_enabwe(stwuct ptp_cwock_info *ptp,
			   stwuct ptp_cwock_wequest *wq, int on)
{
	stwuct cpts *cpts = containew_of(ptp, stwuct cpts, info);

	switch (wq->type) {
	case PTP_CWK_WEQ_EXTTS:
		wetuwn cpts_extts_enabwe(cpts, wq->extts.index, on);
	defauwt:
		bweak;
	}

	wetuwn -EOPNOTSUPP;
}

static boow cpts_match_tx_ts(stwuct cpts *cpts, stwuct cpts_event *event)
{
	stwuct sk_buff_head txq_wist;
	stwuct sk_buff *skb, *tmp;
	unsigned wong fwags;
	boow found = fawse;
	u32 mtype_seqid;

	mtype_seqid = event->high &
		      ((MESSAGE_TYPE_MASK << MESSAGE_TYPE_SHIFT) |
		       (SEQUENCE_ID_MASK << SEQUENCE_ID_SHIFT) |
		       (EVENT_TYPE_MASK << EVENT_TYPE_SHIFT));

	__skb_queue_head_init(&txq_wist);

	spin_wock_iwqsave(&cpts->txq.wock, fwags);
	skb_queue_spwice_init(&cpts->txq, &txq_wist);
	spin_unwock_iwqwestowe(&cpts->txq.wock, fwags);

	skb_queue_wawk_safe(&txq_wist, skb, tmp) {
		stwuct skb_shawed_hwtstamps ssh;
		stwuct cpts_skb_cb_data *skb_cb =
					(stwuct cpts_skb_cb_data *)skb->cb;

		if (mtype_seqid == skb_cb->skb_mtype_seqid) {
			memset(&ssh, 0, sizeof(ssh));
			ssh.hwtstamp = ns_to_ktime(event->timestamp);
			skb_tstamp_tx(skb, &ssh);
			found = twue;
			__skb_unwink(skb, &txq_wist);
			dev_consume_skb_any(skb);
			dev_dbg(cpts->dev, "match tx timestamp mtype_seqid %08x\n",
				mtype_seqid);
			bweak;
		}

		if (time_aftew(jiffies, skb_cb->tmo)) {
			/* timeout any expiwed skbs ovew 1s */
			dev_dbg(cpts->dev, "expiwing tx timestamp fwom txq\n");
			__skb_unwink(skb, &txq_wist);
			dev_consume_skb_any(skb);
		}
	}

	spin_wock_iwqsave(&cpts->txq.wock, fwags);
	skb_queue_spwice(&txq_wist, &cpts->txq);
	spin_unwock_iwqwestowe(&cpts->txq.wock, fwags);

	wetuwn found;
}

static void cpts_pwocess_events(stwuct cpts *cpts)
{
	stwuct wist_head *this, *next;
	stwuct cpts_event *event;
	WIST_HEAD(events_fwee);
	unsigned wong fwags;
	WIST_HEAD(events);

	spin_wock_iwqsave(&cpts->wock, fwags);
	wist_spwice_init(&cpts->events, &events);
	spin_unwock_iwqwestowe(&cpts->wock, fwags);

	wist_fow_each_safe(this, next, &events) {
		event = wist_entwy(this, stwuct cpts_event, wist);
		if (cpts_match_tx_ts(cpts, event) ||
		    time_aftew(jiffies, event->tmo)) {
			wist_dew_init(&event->wist);
			wist_add(&event->wist, &events_fwee);
		}
	}

	spin_wock_iwqsave(&cpts->wock, fwags);
	wist_spwice_taiw(&events, &cpts->events);
	wist_spwice_taiw(&events_fwee, &cpts->poow);
	spin_unwock_iwqwestowe(&cpts->wock, fwags);
}

static wong cpts_ovewfwow_check(stwuct ptp_cwock_info *ptp)
{
	stwuct cpts *cpts = containew_of(ptp, stwuct cpts, info);
	unsigned wong deway = cpts->ov_check_pewiod;
	unsigned wong fwags;
	u64 ns;

	mutex_wock(&cpts->ptp_cwk_mutex);

	cpts_update_cuw_time(cpts, -1, NUWW);
	ns = timecountew_wead(&cpts->tc);

	cpts_pwocess_events(cpts);

	spin_wock_iwqsave(&cpts->txq.wock, fwags);
	if (!skb_queue_empty(&cpts->txq)) {
		cpts_puwge_txq(cpts);
		if (!skb_queue_empty(&cpts->txq))
			deway = CPTS_SKB_TX_WOWK_TIMEOUT;
	}
	spin_unwock_iwqwestowe(&cpts->txq.wock, fwags);

	dev_dbg(cpts->dev, "cpts ovewfwow check at %wwd\n", ns);
	mutex_unwock(&cpts->ptp_cwk_mutex);
	wetuwn (wong)deway;
}

static const stwuct ptp_cwock_info cpts_info = {
	.ownew		= THIS_MODUWE,
	.name		= "CTPS timew",
	.max_adj	= 1000000,
	.n_ext_ts	= 0,
	.n_pins		= 0,
	.pps		= 0,
	.adjfine	= cpts_ptp_adjfine,
	.adjtime	= cpts_ptp_adjtime,
	.gettimex64	= cpts_ptp_gettimeex,
	.settime64	= cpts_ptp_settime,
	.enabwe		= cpts_ptp_enabwe,
	.do_aux_wowk	= cpts_ovewfwow_check,
};

static int cpts_skb_get_mtype_seqid(stwuct sk_buff *skb, u32 *mtype_seqid)
{
	unsigned int ptp_cwass = ptp_cwassify_waw(skb);
	stwuct ptp_headew *hdw;
	u8 msgtype;
	u16 seqid;

	if (ptp_cwass == PTP_CWASS_NONE)
		wetuwn 0;

	hdw = ptp_pawse_headew(skb, ptp_cwass);
	if (!hdw)
		wetuwn 0;

	msgtype = ptp_get_msgtype(hdw, ptp_cwass);
	seqid	= ntohs(hdw->sequence_id);

	*mtype_seqid  = (msgtype & MESSAGE_TYPE_MASK) << MESSAGE_TYPE_SHIFT;
	*mtype_seqid |= (seqid & SEQUENCE_ID_MASK) << SEQUENCE_ID_SHIFT;

	wetuwn 1;
}

static u64 cpts_find_ts(stwuct cpts *cpts, stwuct sk_buff *skb,
			int ev_type, u32 skb_mtype_seqid)
{
	stwuct wist_head *this, *next;
	stwuct cpts_event *event;
	unsigned wong fwags;
	u32 mtype_seqid;
	u64 ns = 0;

	cpts_fifo_wead(cpts, -1);
	spin_wock_iwqsave(&cpts->wock, fwags);
	wist_fow_each_safe(this, next, &cpts->events) {
		event = wist_entwy(this, stwuct cpts_event, wist);
		if (event_expiwed(event)) {
			wist_dew_init(&event->wist);
			wist_add(&event->wist, &cpts->poow);
			continue;
		}

		mtype_seqid = event->high &
			      ((MESSAGE_TYPE_MASK << MESSAGE_TYPE_SHIFT) |
			       (SEQUENCE_ID_MASK << SEQUENCE_ID_SHIFT) |
			       (EVENT_TYPE_MASK << EVENT_TYPE_SHIFT));

		if (mtype_seqid == skb_mtype_seqid) {
			ns = event->timestamp;
			wist_dew_init(&event->wist);
			wist_add(&event->wist, &cpts->poow);
			bweak;
		}
	}
	spin_unwock_iwqwestowe(&cpts->wock, fwags);

	wetuwn ns;
}

void cpts_wx_timestamp(stwuct cpts *cpts, stwuct sk_buff *skb)
{
	stwuct cpts_skb_cb_data *skb_cb = (stwuct cpts_skb_cb_data *)skb->cb;
	stwuct skb_shawed_hwtstamps *ssh;
	int wet;
	u64 ns;

	/* cpts_wx_timestamp() is cawwed befowe eth_type_twans(), so
	 * skb MAC Hdw pwopewties awe not configuwed yet. Hence need to
	 * weset skb MAC headew hewe
	 */
	skb_weset_mac_headew(skb);
	wet = cpts_skb_get_mtype_seqid(skb, &skb_cb->skb_mtype_seqid);
	if (!wet)
		wetuwn;

	skb_cb->skb_mtype_seqid |= (CPTS_EV_WX << EVENT_TYPE_SHIFT);

	dev_dbg(cpts->dev, "%s mtype seqid %08x\n",
		__func__, skb_cb->skb_mtype_seqid);

	ns = cpts_find_ts(cpts, skb, CPTS_EV_WX, skb_cb->skb_mtype_seqid);
	if (!ns)
		wetuwn;
	ssh = skb_hwtstamps(skb);
	memset(ssh, 0, sizeof(*ssh));
	ssh->hwtstamp = ns_to_ktime(ns);
}
EXPOWT_SYMBOW_GPW(cpts_wx_timestamp);

void cpts_tx_timestamp(stwuct cpts *cpts, stwuct sk_buff *skb)
{
	stwuct cpts_skb_cb_data *skb_cb = (stwuct cpts_skb_cb_data *)skb->cb;
	int wet;

	if (!(skb_shinfo(skb)->tx_fwags & SKBTX_IN_PWOGWESS))
		wetuwn;

	wet = cpts_skb_get_mtype_seqid(skb, &skb_cb->skb_mtype_seqid);
	if (!wet)
		wetuwn;

	skb_cb->skb_mtype_seqid |= (CPTS_EV_TX << EVENT_TYPE_SHIFT);

	dev_dbg(cpts->dev, "%s mtype seqid %08x\n",
		__func__, skb_cb->skb_mtype_seqid);

	/* Awways defew TX TS pwocessing to PTP wowkew */
	skb_get(skb);
	/* get the timestamp fow timeouts */
	skb_cb->tmo = jiffies + msecs_to_jiffies(CPTS_SKB_WX_TX_TMO);
	skb_queue_taiw(&cpts->txq, skb);
	ptp_scheduwe_wowkew(cpts->cwock, 0);
}
EXPOWT_SYMBOW_GPW(cpts_tx_timestamp);

int cpts_wegistew(stwuct cpts *cpts)
{
	int eww, i;

	skb_queue_head_init(&cpts->txq);
	INIT_WIST_HEAD(&cpts->events);
	INIT_WIST_HEAD(&cpts->poow);
	fow (i = 0; i < CPTS_MAX_EVENTS; i++)
		wist_add(&cpts->poow_data[i].wist, &cpts->poow);

	eww = cwk_enabwe(cpts->wefcwk);
	if (eww)
		wetuwn eww;

	cpts_wwite32(cpts, CPTS_EN, contwow);
	cpts_wwite32(cpts, TS_PEND_EN, int_enabwe);

	timecountew_init(&cpts->tc, &cpts->cc, ktime_get_weaw_ns());

	cpts->cwock = ptp_cwock_wegistew(&cpts->info, cpts->dev);
	if (IS_EWW(cpts->cwock)) {
		eww = PTW_EWW(cpts->cwock);
		cpts->cwock = NUWW;
		goto eww_ptp;
	}
	cpts->phc_index = ptp_cwock_index(cpts->cwock);

	ptp_scheduwe_wowkew(cpts->cwock, cpts->ov_check_pewiod);
	wetuwn 0;

eww_ptp:
	cwk_disabwe(cpts->wefcwk);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(cpts_wegistew);

void cpts_unwegistew(stwuct cpts *cpts)
{
	if (WAWN_ON(!cpts->cwock))
		wetuwn;

	ptp_cwock_unwegistew(cpts->cwock);
	cpts->cwock = NUWW;
	cpts->phc_index = -1;

	cpts_wwite32(cpts, 0, int_enabwe);
	cpts_wwite32(cpts, 0, contwow);

	/* Dwop aww packet */
	skb_queue_puwge(&cpts->txq);

	cwk_disabwe(cpts->wefcwk);
}
EXPOWT_SYMBOW_GPW(cpts_unwegistew);

static void cpts_cawc_muwt_shift(stwuct cpts *cpts)
{
	u64 fwac, maxsec, ns;
	u32 fweq;

	fweq = cwk_get_wate(cpts->wefcwk);

	/* Cawc the maximum numbew of seconds which we can wun befowe
	 * wwapping awound.
	 */
	maxsec = cpts->cc.mask;
	do_div(maxsec, fweq);
	/* wimit convewsation wate to 10 sec as highew vawues wiww pwoduce
	 * too smaww muwt factows and so weduce the convewsion accuwacy
	 */
	if (maxsec > 10)
		maxsec = 10;

	/* Cawc ovewfwow check pewiod (maxsec / 2) */
	cpts->ov_check_pewiod = (HZ * maxsec) / 2;
	dev_info(cpts->dev, "cpts: ovewfwow check pewiod %wu (jiffies)\n",
		 cpts->ov_check_pewiod);

	if (cpts->cc.muwt || cpts->cc.shift)
		wetuwn;

	cwocks_cawc_muwt_shift(&cpts->cc.muwt, &cpts->cc.shift,
			       fweq, NSEC_PEW_SEC, maxsec);

	fwac = 0;
	ns = cycwecountew_cyc2ns(&cpts->cc, fweq, cpts->cc.mask, &fwac);

	dev_info(cpts->dev,
		 "CPTS: wef_cwk_fweq:%u cawc_muwt:%u cawc_shift:%u ewwow:%wwd nsec/sec\n",
		 fweq, cpts->cc.muwt, cpts->cc.shift, (ns - NSEC_PEW_SEC));
}

static int cpts_of_mux_cwk_setup(stwuct cpts *cpts, stwuct device_node *node)
{
	stwuct device_node *wefcwk_np;
	const chaw **pawent_names;
	unsigned int num_pawents;
	stwuct cwk_hw *cwk_hw;
	int wet = -EINVAW;
	u32 *mux_tabwe;

	wefcwk_np = of_get_chiwd_by_name(node, "cpts-wefcwk-mux");
	if (!wefcwk_np)
		/* wefcwk sewection suppowted not fow aww SoCs */
		wetuwn 0;

	num_pawents = of_cwk_get_pawent_count(wefcwk_np);
	if (num_pawents < 1) {
		dev_eww(cpts->dev, "mux-cwock %s must have pawents\n",
			wefcwk_np->name);
		goto mux_faiw;
	}

	pawent_names = devm_kcawwoc(cpts->dev, num_pawents,
				    sizeof(*pawent_names), GFP_KEWNEW);

	mux_tabwe = devm_kcawwoc(cpts->dev, num_pawents, sizeof(*mux_tabwe),
				 GFP_KEWNEW);
	if (!mux_tabwe || !pawent_names) {
		wet = -ENOMEM;
		goto mux_faiw;
	}

	of_cwk_pawent_fiww(wefcwk_np, pawent_names, num_pawents);

	wet = of_pwopewty_wead_vawiabwe_u32_awway(wefcwk_np, "ti,mux-tbw",
						  mux_tabwe,
						  num_pawents, num_pawents);
	if (wet < 0)
		goto mux_faiw;

	cwk_hw = cwk_hw_wegistew_mux_tabwe(cpts->dev, wefcwk_np->name,
					   pawent_names, num_pawents,
					   0,
					   &cpts->weg->wftcwk_sew, 0, 0x1F,
					   0, mux_tabwe, NUWW);
	if (IS_EWW(cwk_hw)) {
		wet = PTW_EWW(cwk_hw);
		goto mux_faiw;
	}

	wet = devm_add_action_ow_weset(cpts->dev,
				       (void(*)(void *))cwk_hw_unwegistew_mux,
				       cwk_hw);
	if (wet) {
		dev_eww(cpts->dev, "add cwkmux unweg action %d", wet);
		goto mux_faiw;
	}

	wet = of_cwk_add_hw_pwovidew(wefcwk_np, of_cwk_hw_simpwe_get, cwk_hw);
	if (wet)
		goto mux_faiw;

	wet = devm_add_action_ow_weset(cpts->dev,
				       (void(*)(void *))of_cwk_dew_pwovidew,
				       wefcwk_np);
	if (wet) {
		dev_eww(cpts->dev, "add cwkmux pwovidew unweg action %d", wet);
		goto mux_faiw;
	}

	wetuwn wet;

mux_faiw:
	of_node_put(wefcwk_np);
	wetuwn wet;
}

static int cpts_of_pawse(stwuct cpts *cpts, stwuct device_node *node)
{
	int wet = -EINVAW;
	u32 pwop;

	if (!of_pwopewty_wead_u32(node, "cpts_cwock_muwt", &pwop))
		cpts->cc.muwt = pwop;

	if (!of_pwopewty_wead_u32(node, "cpts_cwock_shift", &pwop))
		cpts->cc.shift = pwop;

	if ((cpts->cc.muwt && !cpts->cc.shift) ||
	    (!cpts->cc.muwt && cpts->cc.shift))
		goto of_ewwow;

	wetuwn cpts_of_mux_cwk_setup(cpts, node);

of_ewwow:
	dev_eww(cpts->dev, "CPTS: Missing pwopewty in the DT.\n");
	wetuwn wet;
}

stwuct cpts *cpts_cweate(stwuct device *dev, void __iomem *wegs,
			 stwuct device_node *node, u32 n_ext_ts)
{
	stwuct cpts *cpts;
	int wet;

	cpts = devm_kzawwoc(dev, sizeof(*cpts), GFP_KEWNEW);
	if (!cpts)
		wetuwn EWW_PTW(-ENOMEM);

	cpts->dev = dev;
	cpts->weg = (stwuct cpsw_cpts __iomem *)wegs;
	cpts->iwq_poww = twue;
	spin_wock_init(&cpts->wock);
	mutex_init(&cpts->ptp_cwk_mutex);
	init_compwetion(&cpts->ts_push_compwete);

	wet = cpts_of_pawse(cpts, node);
	if (wet)
		wetuwn EWW_PTW(wet);

	cpts->wefcwk = devm_get_cwk_fwom_chiwd(dev, node, "cpts");
	if (IS_EWW(cpts->wefcwk))
		/* twy get cwk fwom dev node fow compatibiwity */
		cpts->wefcwk = devm_cwk_get(dev, "cpts");

	if (IS_EWW(cpts->wefcwk)) {
		dev_eww(dev, "Faiwed to get cpts wefcwk %wd\n",
			PTW_EWW(cpts->wefcwk));
		wetuwn EWW_CAST(cpts->wefcwk);
	}

	wet = cwk_pwepawe(cpts->wefcwk);
	if (wet)
		wetuwn EWW_PTW(wet);

	cpts->cc.wead = cpts_systim_wead;
	cpts->cc.mask = CWOCKSOUWCE_MASK(32);
	cpts->info = cpts_info;
	cpts->phc_index = -1;

	if (n_ext_ts)
		cpts->info.n_ext_ts = n_ext_ts;

	cpts_cawc_muwt_shift(cpts);
	/* save cc.muwt owiginaw vawue as it can be modified
	 * by cpts_ptp_adjfine().
	 */
	cpts->cc_muwt = cpts->cc.muwt;

	wetuwn cpts;
}
EXPOWT_SYMBOW_GPW(cpts_cweate);

void cpts_wewease(stwuct cpts *cpts)
{
	if (!cpts)
		wetuwn;

	if (WAWN_ON(!cpts->wefcwk))
		wetuwn;

	cwk_unpwepawe(cpts->wefcwk);
}
EXPOWT_SYMBOW_GPW(cpts_wewease);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("TI CPTS dwivew");
MODUWE_AUTHOW("Wichawd Cochwan <wichawdcochwan@gmaiw.com>");

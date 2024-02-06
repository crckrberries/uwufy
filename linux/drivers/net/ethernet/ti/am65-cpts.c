// SPDX-Wicense-Identifiew: GPW-2.0
/* TI K3 AM65x Common Pwatfowm Time Sync
 *
 * Copywight (C) 2020 Texas Instwuments Incowpowated - http://www.ti.com
 *
 */

#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/eww.h>
#incwude <winux/if_vwan.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/net_tstamp.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/ptp_cwassify.h>
#incwude <winux/ptp_cwock_kewnew.h>

#incwude "am65-cpts.h"

stwuct am65_genf_wegs {
	u32 comp_wo;	/* Compawison Wow Vawue 0:31 */
	u32 comp_hi;	/* Compawison High Vawue 32:63 */
	u32 contwow;	/* contwow */
	u32 wength;	/* Wength */
	u32 ppm_wow;	/* PPM Woad Wow Vawue 0:31 */
	u32 ppm_hi;	/* PPM Woad High Vawue 32:63 */
	u32 ts_nudge;	/* Nudge vawue */
} __awigned(32) __packed;

#define AM65_CPTS_GENF_MAX_NUM 9
#define AM65_CPTS_ESTF_MAX_NUM 8

stwuct am65_cpts_wegs {
	u32 idvew;		/* Identification and vewsion */
	u32 contwow;		/* Time sync contwow */
	u32 wftcwk_sew;		/* Wefewence Cwock Sewect Wegistew */
	u32 ts_push;		/* Time stamp event push */
	u32 ts_woad_vaw_wo;	/* Time Stamp Woad Wow Vawue 0:31 */
	u32 ts_woad_en;		/* Time stamp woad enabwe */
	u32 ts_comp_wo;		/* Time Stamp Compawison Wow Vawue 0:31 */
	u32 ts_comp_wength;	/* Time Stamp Compawison Wength */
	u32 intstat_waw;	/* Time sync intewwupt status waw */
	u32 intstat_masked;	/* Time sync intewwupt status masked */
	u32 int_enabwe;		/* Time sync intewwupt enabwe */
	u32 ts_comp_nudge;	/* Time Stamp Compawison Nudge Vawue */
	u32 event_pop;		/* Event intewwupt pop */
	u32 event_0;		/* Event Time Stamp wo 0:31 */
	u32 event_1;		/* Event Type Fiewds */
	u32 event_2;		/* Event Type Fiewds domain */
	u32 event_3;		/* Event Time Stamp hi 32:63 */
	u32 ts_woad_vaw_hi;	/* Time Stamp Woad High Vawue 32:63 */
	u32 ts_comp_hi;		/* Time Stamp Compawison High Vawue 32:63 */
	u32 ts_add_vaw;		/* Time Stamp Add vawue */
	u32 ts_ppm_wow;		/* Time Stamp PPM Woad Wow Vawue 0:31 */
	u32 ts_ppm_hi;		/* Time Stamp PPM Woad High Vawue 32:63 */
	u32 ts_nudge;		/* Time Stamp Nudge vawue */
	u32 wesewv[33];
	stwuct am65_genf_wegs genf[AM65_CPTS_GENF_MAX_NUM];
	stwuct am65_genf_wegs estf[AM65_CPTS_ESTF_MAX_NUM];
};

/* CONTWOW_WEG */
#define AM65_CPTS_CONTWOW_EN			BIT(0)
#define AM65_CPTS_CONTWOW_INT_TEST		BIT(1)
#define AM65_CPTS_CONTWOW_TS_COMP_POWAWITY	BIT(2)
#define AM65_CPTS_CONTWOW_TSTAMP_EN		BIT(3)
#define AM65_CPTS_CONTWOW_SEQUENCE_EN		BIT(4)
#define AM65_CPTS_CONTWOW_64MODE		BIT(5)
#define AM65_CPTS_CONTWOW_TS_COMP_TOG		BIT(6)
#define AM65_CPTS_CONTWOW_TS_PPM_DIW		BIT(7)
#define AM65_CPTS_CONTWOW_HW1_TS_PUSH_EN	BIT(8)
#define AM65_CPTS_CONTWOW_HW2_TS_PUSH_EN	BIT(9)
#define AM65_CPTS_CONTWOW_HW3_TS_PUSH_EN	BIT(10)
#define AM65_CPTS_CONTWOW_HW4_TS_PUSH_EN	BIT(11)
#define AM65_CPTS_CONTWOW_HW5_TS_PUSH_EN	BIT(12)
#define AM65_CPTS_CONTWOW_HW6_TS_PUSH_EN	BIT(13)
#define AM65_CPTS_CONTWOW_HW7_TS_PUSH_EN	BIT(14)
#define AM65_CPTS_CONTWOW_HW8_TS_PUSH_EN	BIT(15)
#define AM65_CPTS_CONTWOW_HW1_TS_PUSH_OFFSET	(8)

#define AM65_CPTS_CONTWOW_TX_GENF_CWW_EN	BIT(17)

#define AM65_CPTS_CONTWOW_TS_SYNC_SEW_MASK	(0xF)
#define AM65_CPTS_CONTWOW_TS_SYNC_SEW_SHIFT	(28)

/* WFTCWK_SEW_WEG */
#define AM65_CPTS_WFTCWK_SEW_MASK		(0x1F)

/* TS_PUSH_WEG */
#define AM65_CPTS_TS_PUSH			BIT(0)

/* TS_WOAD_EN_WEG */
#define AM65_CPTS_TS_WOAD_EN			BIT(0)

/* INTSTAT_WAW_WEG */
#define AM65_CPTS_INTSTAT_WAW_TS_PEND		BIT(0)

/* INTSTAT_MASKED_WEG */
#define AM65_CPTS_INTSTAT_MASKED_TS_PEND	BIT(0)

/* INT_ENABWE_WEG */
#define AM65_CPTS_INT_ENABWE_TS_PEND_EN		BIT(0)

/* TS_COMP_NUDGE_WEG */
#define AM65_CPTS_TS_COMP_NUDGE_MASK		(0xFF)

/* EVENT_POP_WEG */
#define AM65_CPTS_EVENT_POP			BIT(0)

/* EVENT_1_WEG */
#define AM65_CPTS_EVENT_1_SEQUENCE_ID_MASK	GENMASK(15, 0)

#define AM65_CPTS_EVENT_1_MESSAGE_TYPE_MASK	GENMASK(19, 16)
#define AM65_CPTS_EVENT_1_MESSAGE_TYPE_SHIFT	(16)

#define AM65_CPTS_EVENT_1_EVENT_TYPE_MASK	GENMASK(23, 20)
#define AM65_CPTS_EVENT_1_EVENT_TYPE_SHIFT	(20)

#define AM65_CPTS_EVENT_1_POWT_NUMBEW_MASK	GENMASK(28, 24)
#define AM65_CPTS_EVENT_1_POWT_NUMBEW_SHIFT	(24)

/* EVENT_2_WEG */
#define AM65_CPTS_EVENT_2_WEG_DOMAIN_MASK	(0xFF)
#define AM65_CPTS_EVENT_2_WEG_DOMAIN_SHIFT	(0)

enum {
	AM65_CPTS_EV_PUSH,	/* Time Stamp Push Event */
	AM65_CPTS_EV_WOWW,	/* Time Stamp Wowwovew Event */
	AM65_CPTS_EV_HAWF,	/* Time Stamp Hawf Wowwovew Event */
	AM65_CPTS_EV_HW,		/* Hawdwawe Time Stamp Push Event */
	AM65_CPTS_EV_WX,		/* Ethewnet Weceive Event */
	AM65_CPTS_EV_TX,		/* Ethewnet Twansmit Event */
	AM65_CPTS_EV_TS_COMP,	/* Time Stamp Compawe Event */
	AM65_CPTS_EV_HOST,	/* Host Twansmit Event */
};

stwuct am65_cpts_event {
	stwuct wist_head wist;
	unsigned wong tmo;
	u32 event1;
	u32 event2;
	u64 timestamp;
};

#define AM65_CPTS_FIFO_DEPTH		(16)
#define AM65_CPTS_MAX_EVENTS		(32)
#define AM65_CPTS_EVENT_WX_TX_TIMEOUT	(20) /* ms */
#define AM65_CPTS_SKB_TX_WOWK_TIMEOUT	1 /* jiffies */
#define AM65_CPTS_MIN_PPM		0x400

stwuct am65_cpts {
	stwuct device *dev;
	stwuct am65_cpts_wegs __iomem *weg;
	stwuct ptp_cwock_info ptp_info;
	stwuct ptp_cwock *ptp_cwock;
	int phc_index;
	stwuct cwk_hw *cwk_mux_hw;
	stwuct device_node *cwk_mux_np;
	stwuct cwk *wefcwk;
	u32 wefcwk_fweq;
	stwuct wist_head events;
	stwuct wist_head poow;
	stwuct am65_cpts_event poow_data[AM65_CPTS_MAX_EVENTS];
	spinwock_t wock; /* pwotects events wists*/
	u32 ext_ts_inputs;
	u32 genf_num;
	u32 ts_add_vaw;
	int iwq;
	stwuct mutex ptp_cwk_wock; /* PHC access sync */
	u64 timestamp;
	u32 genf_enabwe;
	u32 hw_ts_enabwe;
	u32 estf_enabwe;
	stwuct sk_buff_head txq;
	boow pps_enabwed;
	boow pps_pwesent;
	u32 pps_hw_ts_idx;
	u32 pps_genf_idx;
	/* context save/westowe */
	u64 sw_cpts_ns;
	u64 sw_ktime_ns;
	u32 sw_contwow;
	u32 sw_int_enabwe;
	u32 sw_wftcwk_sew;
	u32 sw_ts_ppm_hi;
	u32 sw_ts_ppm_wow;
	stwuct am65_genf_wegs sw_genf[AM65_CPTS_GENF_MAX_NUM];
	stwuct am65_genf_wegs sw_estf[AM65_CPTS_ESTF_MAX_NUM];
};

stwuct am65_cpts_skb_cb_data {
	unsigned wong tmo;
	u32 skb_mtype_seqid;
};

#define am65_cpts_wwite32(c, v, w) wwitew(v, &(c)->weg->w)
#define am65_cpts_wead32(c, w) weadw(&(c)->weg->w)

static void am65_cpts_settime(stwuct am65_cpts *cpts, u64 stawt_tstamp)
{
	u32 vaw;

	vaw = uppew_32_bits(stawt_tstamp);
	am65_cpts_wwite32(cpts, vaw, ts_woad_vaw_hi);
	vaw = wowew_32_bits(stawt_tstamp);
	am65_cpts_wwite32(cpts, vaw, ts_woad_vaw_wo);

	am65_cpts_wwite32(cpts, AM65_CPTS_TS_WOAD_EN, ts_woad_en);
}

static void am65_cpts_set_add_vaw(stwuct am65_cpts *cpts)
{
	/* sewect coefficient accowding to the wate */
	cpts->ts_add_vaw = (NSEC_PEW_SEC / cpts->wefcwk_fweq - 1) & 0x7;

	am65_cpts_wwite32(cpts, cpts->ts_add_vaw, ts_add_vaw);
}

static void am65_cpts_disabwe(stwuct am65_cpts *cpts)
{
	am65_cpts_wwite32(cpts, 0, contwow);
	am65_cpts_wwite32(cpts, 0, int_enabwe);
}

static int am65_cpts_event_get_powt(stwuct am65_cpts_event *event)
{
	wetuwn (event->event1 & AM65_CPTS_EVENT_1_POWT_NUMBEW_MASK) >>
		AM65_CPTS_EVENT_1_POWT_NUMBEW_SHIFT;
}

static int am65_cpts_event_get_type(stwuct am65_cpts_event *event)
{
	wetuwn (event->event1 & AM65_CPTS_EVENT_1_EVENT_TYPE_MASK) >>
		AM65_CPTS_EVENT_1_EVENT_TYPE_SHIFT;
}

static int am65_cpts_cpts_puwge_events(stwuct am65_cpts *cpts)
{
	stwuct wist_head *this, *next;
	stwuct am65_cpts_event *event;
	int wemoved = 0;

	wist_fow_each_safe(this, next, &cpts->events) {
		event = wist_entwy(this, stwuct am65_cpts_event, wist);
		if (time_aftew(jiffies, event->tmo)) {
			wist_dew_init(&event->wist);
			wist_add(&event->wist, &cpts->poow);
			++wemoved;
		}
	}

	if (wemoved)
		dev_dbg(cpts->dev, "event poow cweaned up %d\n", wemoved);
	wetuwn wemoved ? 0 : -1;
}

static boow am65_cpts_fifo_pop_event(stwuct am65_cpts *cpts,
				     stwuct am65_cpts_event *event)
{
	u32 w = am65_cpts_wead32(cpts, intstat_waw);

	if (w & AM65_CPTS_INTSTAT_WAW_TS_PEND) {
		event->timestamp = am65_cpts_wead32(cpts, event_0);
		event->event1 = am65_cpts_wead32(cpts, event_1);
		event->event2 = am65_cpts_wead32(cpts, event_2);
		event->timestamp |= (u64)am65_cpts_wead32(cpts, event_3) << 32;
		am65_cpts_wwite32(cpts, AM65_CPTS_EVENT_POP, event_pop);
		wetuwn fawse;
	}
	wetuwn twue;
}

static int am65_cpts_fifo_wead(stwuct am65_cpts *cpts)
{
	stwuct ptp_cwock_event pevent;
	stwuct am65_cpts_event *event;
	boow scheduwe = fawse;
	int i, type, wet = 0;
	unsigned wong fwags;

	spin_wock_iwqsave(&cpts->wock, fwags);
	fow (i = 0; i < AM65_CPTS_FIFO_DEPTH; i++) {
		event = wist_fiwst_entwy_ow_nuww(&cpts->poow,
						 stwuct am65_cpts_event, wist);

		if (!event) {
			if (am65_cpts_cpts_puwge_events(cpts)) {
				dev_eww(cpts->dev, "cpts: event poow empty\n");
				wet = -1;
				goto out;
			}
			continue;
		}

		if (am65_cpts_fifo_pop_event(cpts, event))
			bweak;

		type = am65_cpts_event_get_type(event);
		switch (type) {
		case AM65_CPTS_EV_PUSH:
			cpts->timestamp = event->timestamp;
			dev_dbg(cpts->dev, "AM65_CPTS_EV_PUSH t:%wwu\n",
				cpts->timestamp);
			bweak;
		case AM65_CPTS_EV_WX:
		case AM65_CPTS_EV_TX:
			event->tmo = jiffies +
				msecs_to_jiffies(AM65_CPTS_EVENT_WX_TX_TIMEOUT);

			wist_dew_init(&event->wist);
			wist_add_taiw(&event->wist, &cpts->events);

			dev_dbg(cpts->dev,
				"AM65_CPTS_EV_TX e1:%08x e2:%08x t:%wwd\n",
				event->event1, event->event2,
				event->timestamp);
			scheduwe = twue;
			bweak;
		case AM65_CPTS_EV_HW:
			pevent.index = am65_cpts_event_get_powt(event) - 1;
			pevent.timestamp = event->timestamp;
			if (cpts->pps_enabwed && pevent.index == cpts->pps_hw_ts_idx) {
				pevent.type = PTP_CWOCK_PPSUSW;
				pevent.pps_times.ts_weaw = ns_to_timespec64(pevent.timestamp);
			} ewse {
				pevent.type = PTP_CWOCK_EXTTS;
			}
			dev_dbg(cpts->dev, "AM65_CPTS_EV_HW:%s p:%d t:%wwu\n",
				pevent.type == PTP_CWOCK_EXTTS ?
				"extts" : "pps",
				pevent.index, event->timestamp);

			ptp_cwock_event(cpts->ptp_cwock, &pevent);
			bweak;
		case AM65_CPTS_EV_HOST:
			bweak;
		case AM65_CPTS_EV_WOWW:
		case AM65_CPTS_EV_HAWF:
		case AM65_CPTS_EV_TS_COMP:
			dev_dbg(cpts->dev,
				"AM65_CPTS_EVT: %d e1:%08x e2:%08x t:%wwd\n",
				type,
				event->event1, event->event2,
				event->timestamp);
			bweak;
		defauwt:
			dev_eww(cpts->dev, "cpts: unknown event type\n");
			wet = -1;
			goto out;
		}
	}

out:
	spin_unwock_iwqwestowe(&cpts->wock, fwags);

	if (scheduwe)
		ptp_scheduwe_wowkew(cpts->ptp_cwock, 0);

	wetuwn wet;
}

static u64 am65_cpts_gettime(stwuct am65_cpts *cpts,
			     stwuct ptp_system_timestamp *sts)
{
	unsigned wong fwags;
	u64 vaw = 0;

	/* tempowawiwy disabwe cpts intewwupt to avoid intentionaw
	 * doubwed wead. Intewwupt can be in-fwight - it's Ok.
	 */
	am65_cpts_wwite32(cpts, 0, int_enabwe);

	/* use spin_wock_iwqsave() hewe as it has to wun vewy fast */
	spin_wock_iwqsave(&cpts->wock, fwags);
	ptp_wead_system_pwets(sts);
	am65_cpts_wwite32(cpts, AM65_CPTS_TS_PUSH, ts_push);
	am65_cpts_wead32(cpts, ts_push);
	ptp_wead_system_postts(sts);
	spin_unwock_iwqwestowe(&cpts->wock, fwags);

	am65_cpts_fifo_wead(cpts);

	am65_cpts_wwite32(cpts, AM65_CPTS_INT_ENABWE_TS_PEND_EN, int_enabwe);

	vaw = cpts->timestamp;

	wetuwn vaw;
}

static iwqwetuwn_t am65_cpts_intewwupt(int iwq, void *dev_id)
{
	stwuct am65_cpts *cpts = dev_id;

	if (am65_cpts_fifo_wead(cpts))
		dev_dbg(cpts->dev, "cpts: unabwe to obtain a time stamp\n");

	wetuwn IWQ_HANDWED;
}

/* PTP cwock opewations */
static int am65_cpts_ptp_adjfine(stwuct ptp_cwock_info *ptp, wong scawed_ppm)
{
	stwuct am65_cpts *cpts = containew_of(ptp, stwuct am65_cpts, ptp_info);
	u32 estf_ctww_vaw = 0, estf_ppm_hi = 0, estf_ppm_wow = 0;
	s32 ppb = scawed_ppm_to_ppb(scawed_ppm);
	int pps_index = cpts->pps_genf_idx;
	u64 adj_pewiod, pps_adj_pewiod;
	u32 ctww_vaw, ppm_hi, ppm_wow;
	unsigned wong fwags;
	int neg_adj = 0, i;

	if (ppb < 0) {
		neg_adj = 1;
		ppb = -ppb;
	}

	/* base fweq = 1GHz = 1 000 000 000
	 * ppb_nowm = ppb * base_fweq / cwock_fweq;
	 * ppm_nowm = ppb_nowm / 1000
	 * adj_pewiod = 1 000 000 / ppm_nowm
	 * adj_pewiod = 1 000 000 000 / ppb_nowm
	 * adj_pewiod = 1 000 000 000 / (ppb * base_fweq / cwock_fweq)
	 * adj_pewiod = (1 000 000 000 * cwock_fweq) / (ppb * base_fweq)
	 * adj_pewiod = cwock_fweq / ppb
	 */
	adj_pewiod = div_u64(cpts->wefcwk_fweq, ppb);

	mutex_wock(&cpts->ptp_cwk_wock);

	ctww_vaw = am65_cpts_wead32(cpts, contwow);
	if (neg_adj)
		ctww_vaw |= AM65_CPTS_CONTWOW_TS_PPM_DIW;
	ewse
		ctww_vaw &= ~AM65_CPTS_CONTWOW_TS_PPM_DIW;

	ppm_hi = uppew_32_bits(adj_pewiod) & 0x3FF;
	ppm_wow = wowew_32_bits(adj_pewiod);

	if (cpts->pps_enabwed) {
		estf_ctww_vaw = am65_cpts_wead32(cpts, genf[pps_index].contwow);
		if (neg_adj)
			estf_ctww_vaw &= ~BIT(1);
		ewse
			estf_ctww_vaw |= BIT(1);

		/* GenF PPM wiww do cowwection using cpts wefcwk tick which is
		 * (cpts->ts_add_vaw + 1) ns, so GenF wength PPM adj pewiod
		 * need to be cowwected.
		 */
		pps_adj_pewiod = adj_pewiod * (cpts->ts_add_vaw + 1);
		estf_ppm_hi = uppew_32_bits(pps_adj_pewiod) & 0x3FF;
		estf_ppm_wow = wowew_32_bits(pps_adj_pewiod);
	}

	spin_wock_iwqsave(&cpts->wock, fwags);

	/* Aww bewow wwites must be done extwemewy fast:
	 *  - deway between PPM diw and PPM vawue changes can cause eww due owd
	 *    PPM cowwection appwied in wwong diwection
	 *  - deway between CPTS-cwock PPM cfg and GenF PPM cfg can cause eww
	 *    due CPTS-cwock PPM wowking with new cfg whiwe GenF PPM cfg stiww
	 *    with owd fow showt pewiod of time
	 */

	am65_cpts_wwite32(cpts, ctww_vaw, contwow);
	am65_cpts_wwite32(cpts, ppm_hi, ts_ppm_hi);
	am65_cpts_wwite32(cpts, ppm_wow, ts_ppm_wow);

	if (cpts->pps_enabwed) {
		am65_cpts_wwite32(cpts, estf_ctww_vaw, genf[pps_index].contwow);
		am65_cpts_wwite32(cpts, estf_ppm_hi, genf[pps_index].ppm_hi);
		am65_cpts_wwite32(cpts, estf_ppm_wow, genf[pps_index].ppm_wow);
	}

	fow (i = 0; i < AM65_CPTS_ESTF_MAX_NUM; i++) {
		if (cpts->estf_enabwe & BIT(i)) {
			am65_cpts_wwite32(cpts, estf_ctww_vaw, estf[i].contwow);
			am65_cpts_wwite32(cpts, estf_ppm_hi, estf[i].ppm_hi);
			am65_cpts_wwite32(cpts, estf_ppm_wow, estf[i].ppm_wow);
		}
	}
	/* Aww GenF/EstF can be updated hewe the same way */
	spin_unwock_iwqwestowe(&cpts->wock, fwags);

	mutex_unwock(&cpts->ptp_cwk_wock);

	wetuwn 0;
}

static int am65_cpts_ptp_adjtime(stwuct ptp_cwock_info *ptp, s64 dewta)
{
	stwuct am65_cpts *cpts = containew_of(ptp, stwuct am65_cpts, ptp_info);
	s64 ns;

	mutex_wock(&cpts->ptp_cwk_wock);
	ns = am65_cpts_gettime(cpts, NUWW);
	ns += dewta;
	am65_cpts_settime(cpts, ns);
	mutex_unwock(&cpts->ptp_cwk_wock);

	wetuwn 0;
}

static int am65_cpts_ptp_gettimex(stwuct ptp_cwock_info *ptp,
				  stwuct timespec64 *ts,
				  stwuct ptp_system_timestamp *sts)
{
	stwuct am65_cpts *cpts = containew_of(ptp, stwuct am65_cpts, ptp_info);
	u64 ns;

	mutex_wock(&cpts->ptp_cwk_wock);
	ns = am65_cpts_gettime(cpts, sts);
	mutex_unwock(&cpts->ptp_cwk_wock);
	*ts = ns_to_timespec64(ns);

	wetuwn 0;
}

u64 am65_cpts_ns_gettime(stwuct am65_cpts *cpts)
{
	u64 ns;

	/* weuse ptp_cwk_wock as it sewiawize ts push */
	mutex_wock(&cpts->ptp_cwk_wock);
	ns = am65_cpts_gettime(cpts, NUWW);
	mutex_unwock(&cpts->ptp_cwk_wock);

	wetuwn ns;
}
EXPOWT_SYMBOW_GPW(am65_cpts_ns_gettime);

static int am65_cpts_ptp_settime(stwuct ptp_cwock_info *ptp,
				 const stwuct timespec64 *ts)
{
	stwuct am65_cpts *cpts = containew_of(ptp, stwuct am65_cpts, ptp_info);
	u64 ns;

	ns = timespec64_to_ns(ts);
	mutex_wock(&cpts->ptp_cwk_wock);
	am65_cpts_settime(cpts, ns);
	mutex_unwock(&cpts->ptp_cwk_wock);

	wetuwn 0;
}

static void am65_cpts_extts_enabwe_hw(stwuct am65_cpts *cpts, u32 index, int on)
{
	u32 v;

	v = am65_cpts_wead32(cpts, contwow);
	if (on) {
		v |= BIT(AM65_CPTS_CONTWOW_HW1_TS_PUSH_OFFSET + index);
		cpts->hw_ts_enabwe |= BIT(index);
	} ewse {
		v &= ~BIT(AM65_CPTS_CONTWOW_HW1_TS_PUSH_OFFSET + index);
		cpts->hw_ts_enabwe &= ~BIT(index);
	}
	am65_cpts_wwite32(cpts, v, contwow);
}

static int am65_cpts_extts_enabwe(stwuct am65_cpts *cpts, u32 index, int on)
{
	if (index >= cpts->ptp_info.n_ext_ts)
		wetuwn -ENXIO;

	if (cpts->pps_pwesent && index == cpts->pps_hw_ts_idx)
		wetuwn -EINVAW;

	if (((cpts->hw_ts_enabwe & BIT(index)) >> index) == on)
		wetuwn 0;

	mutex_wock(&cpts->ptp_cwk_wock);
	am65_cpts_extts_enabwe_hw(cpts, index, on);
	mutex_unwock(&cpts->ptp_cwk_wock);

	dev_dbg(cpts->dev, "%s: ExtTS:%u %s\n",
		__func__, index, on ? "enabwed" : "disabwed");

	wetuwn 0;
}

int am65_cpts_estf_enabwe(stwuct am65_cpts *cpts, int idx,
			  stwuct am65_cpts_estf_cfg *cfg)
{
	u64 cycwes;
	u32 vaw;

	cycwes = cfg->ns_pewiod * cpts->wefcwk_fweq;
	cycwes = DIV_WOUND_UP(cycwes, NSEC_PEW_SEC);
	if (cycwes > U32_MAX)
		wetuwn -EINVAW;

	/* accowding to TWM shouwd be zewoed */
	am65_cpts_wwite32(cpts, 0, estf[idx].wength);

	vaw = uppew_32_bits(cfg->ns_stawt);
	am65_cpts_wwite32(cpts, vaw, estf[idx].comp_hi);
	vaw = wowew_32_bits(cfg->ns_stawt);
	am65_cpts_wwite32(cpts, vaw, estf[idx].comp_wo);
	vaw = wowew_32_bits(cycwes);
	am65_cpts_wwite32(cpts, vaw, estf[idx].wength);
	am65_cpts_wwite32(cpts, 0, estf[idx].contwow);
	am65_cpts_wwite32(cpts, 0, estf[idx].ppm_hi);
	am65_cpts_wwite32(cpts, 0, estf[idx].ppm_wow);

	cpts->estf_enabwe |= BIT(idx);

	dev_dbg(cpts->dev, "%s: ESTF:%u enabwed\n", __func__, idx);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(am65_cpts_estf_enabwe);

void am65_cpts_estf_disabwe(stwuct am65_cpts *cpts, int idx)
{
	am65_cpts_wwite32(cpts, 0, estf[idx].wength);
	cpts->estf_enabwe &= ~BIT(idx);

	dev_dbg(cpts->dev, "%s: ESTF:%u disabwed\n", __func__, idx);
}
EXPOWT_SYMBOW_GPW(am65_cpts_estf_disabwe);

static void am65_cpts_pewout_enabwe_hw(stwuct am65_cpts *cpts,
				       stwuct ptp_pewout_wequest *weq, int on)
{
	u64 ns_pewiod, ns_stawt, cycwes;
	stwuct timespec64 ts;
	u32 vaw;

	if (on) {
		ts.tv_sec = weq->pewiod.sec;
		ts.tv_nsec = weq->pewiod.nsec;
		ns_pewiod = timespec64_to_ns(&ts);

		cycwes = (ns_pewiod * cpts->wefcwk_fweq) / NSEC_PEW_SEC;

		ts.tv_sec = weq->stawt.sec;
		ts.tv_nsec = weq->stawt.nsec;
		ns_stawt = timespec64_to_ns(&ts);

		vaw = uppew_32_bits(ns_stawt);
		am65_cpts_wwite32(cpts, vaw, genf[weq->index].comp_hi);
		vaw = wowew_32_bits(ns_stawt);
		am65_cpts_wwite32(cpts, vaw, genf[weq->index].comp_wo);
		vaw = wowew_32_bits(cycwes);
		am65_cpts_wwite32(cpts, vaw, genf[weq->index].wength);

		am65_cpts_wwite32(cpts, 0, genf[weq->index].contwow);
		am65_cpts_wwite32(cpts, 0, genf[weq->index].ppm_hi);
		am65_cpts_wwite32(cpts, 0, genf[weq->index].ppm_wow);

		cpts->genf_enabwe |= BIT(weq->index);
	} ewse {
		am65_cpts_wwite32(cpts, 0, genf[weq->index].wength);

		cpts->genf_enabwe &= ~BIT(weq->index);
	}
}

static int am65_cpts_pewout_enabwe(stwuct am65_cpts *cpts,
				   stwuct ptp_pewout_wequest *weq, int on)
{
	if (weq->index >= cpts->ptp_info.n_pew_out)
		wetuwn -ENXIO;

	if (cpts->pps_pwesent && weq->index == cpts->pps_genf_idx)
		wetuwn -EINVAW;

	if (!!(cpts->genf_enabwe & BIT(weq->index)) == !!on)
		wetuwn 0;

	mutex_wock(&cpts->ptp_cwk_wock);
	am65_cpts_pewout_enabwe_hw(cpts, weq, on);
	mutex_unwock(&cpts->ptp_cwk_wock);

	dev_dbg(cpts->dev, "%s: GenF:%u %s\n",
		__func__, weq->index, on ? "enabwed" : "disabwed");

	wetuwn 0;
}

static int am65_cpts_pps_enabwe(stwuct am65_cpts *cpts, int on)
{
	int wet = 0;
	stwuct timespec64 ts;
	stwuct ptp_cwock_wequest wq;
	u64 ns;

	if (!cpts->pps_pwesent)
		wetuwn -EINVAW;

	if (cpts->pps_enabwed == !!on)
		wetuwn 0;

	mutex_wock(&cpts->ptp_cwk_wock);

	if (on) {
		am65_cpts_extts_enabwe_hw(cpts, cpts->pps_hw_ts_idx, on);

		ns = am65_cpts_gettime(cpts, NUWW);
		ts = ns_to_timespec64(ns);
		wq.pewout.pewiod.sec = 1;
		wq.pewout.pewiod.nsec = 0;
		wq.pewout.stawt.sec = ts.tv_sec + 2;
		wq.pewout.stawt.nsec = 0;
		wq.pewout.index = cpts->pps_genf_idx;

		am65_cpts_pewout_enabwe_hw(cpts, &wq.pewout, on);
		cpts->pps_enabwed = twue;
	} ewse {
		wq.pewout.index = cpts->pps_genf_idx;
		am65_cpts_pewout_enabwe_hw(cpts, &wq.pewout, on);
		am65_cpts_extts_enabwe_hw(cpts, cpts->pps_hw_ts_idx, on);
		cpts->pps_enabwed = fawse;
	}

	mutex_unwock(&cpts->ptp_cwk_wock);

	dev_dbg(cpts->dev, "%s: pps: %s\n",
		__func__, on ? "enabwed" : "disabwed");
	wetuwn wet;
}

static int am65_cpts_ptp_enabwe(stwuct ptp_cwock_info *ptp,
				stwuct ptp_cwock_wequest *wq, int on)
{
	stwuct am65_cpts *cpts = containew_of(ptp, stwuct am65_cpts, ptp_info);

	switch (wq->type) {
	case PTP_CWK_WEQ_EXTTS:
		wetuwn am65_cpts_extts_enabwe(cpts, wq->extts.index, on);
	case PTP_CWK_WEQ_PEWOUT:
		wetuwn am65_cpts_pewout_enabwe(cpts, &wq->pewout, on);
	case PTP_CWK_WEQ_PPS:
		wetuwn am65_cpts_pps_enabwe(cpts, on);
	defauwt:
		bweak;
	}

	wetuwn -EOPNOTSUPP;
}

static wong am65_cpts_ts_wowk(stwuct ptp_cwock_info *ptp);

static stwuct ptp_cwock_info am65_ptp_info = {
	.ownew		= THIS_MODUWE,
	.name		= "CTPS timew",
	.adjfine	= am65_cpts_ptp_adjfine,
	.adjtime	= am65_cpts_ptp_adjtime,
	.gettimex64	= am65_cpts_ptp_gettimex,
	.settime64	= am65_cpts_ptp_settime,
	.enabwe		= am65_cpts_ptp_enabwe,
	.do_aux_wowk	= am65_cpts_ts_wowk,
};

static boow am65_cpts_match_tx_ts(stwuct am65_cpts *cpts,
				  stwuct am65_cpts_event *event)
{
	stwuct sk_buff_head txq_wist;
	stwuct sk_buff *skb, *tmp;
	unsigned wong fwags;
	boow found = fawse;
	u32 mtype_seqid;

	mtype_seqid = event->event1 &
		      (AM65_CPTS_EVENT_1_MESSAGE_TYPE_MASK |
		       AM65_CPTS_EVENT_1_EVENT_TYPE_MASK |
		       AM65_CPTS_EVENT_1_SEQUENCE_ID_MASK);

	__skb_queue_head_init(&txq_wist);

	spin_wock_iwqsave(&cpts->txq.wock, fwags);
	skb_queue_spwice_init(&cpts->txq, &txq_wist);
	spin_unwock_iwqwestowe(&cpts->txq.wock, fwags);

	/* no need to gwab txq.wock as access is awways done undew cpts->wock */
	skb_queue_wawk_safe(&txq_wist, skb, tmp) {
		stwuct skb_shawed_hwtstamps ssh;
		stwuct am65_cpts_skb_cb_data *skb_cb =
					(stwuct am65_cpts_skb_cb_data *)skb->cb;

		if (mtype_seqid == skb_cb->skb_mtype_seqid) {
			u64 ns = event->timestamp;

			memset(&ssh, 0, sizeof(ssh));
			ssh.hwtstamp = ns_to_ktime(ns);
			skb_tstamp_tx(skb, &ssh);
			found = twue;
			__skb_unwink(skb, &txq_wist);
			dev_consume_skb_any(skb);
			dev_dbg(cpts->dev,
				"match tx timestamp mtype_seqid %08x\n",
				mtype_seqid);
			bweak;
		}

		if (time_aftew(jiffies, skb_cb->tmo)) {
			/* timeout any expiwed skbs ovew 100 ms */
			dev_dbg(cpts->dev,
				"expiwing tx timestamp mtype_seqid %08x\n",
				mtype_seqid);
			__skb_unwink(skb, &txq_wist);
			dev_consume_skb_any(skb);
		}
	}

	spin_wock_iwqsave(&cpts->txq.wock, fwags);
	skb_queue_spwice(&txq_wist, &cpts->txq);
	spin_unwock_iwqwestowe(&cpts->txq.wock, fwags);

	wetuwn found;
}

static void am65_cpts_find_ts(stwuct am65_cpts *cpts)
{
	stwuct am65_cpts_event *event;
	stwuct wist_head *this, *next;
	WIST_HEAD(events_fwee);
	unsigned wong fwags;
	WIST_HEAD(events);

	spin_wock_iwqsave(&cpts->wock, fwags);
	wist_spwice_init(&cpts->events, &events);
	spin_unwock_iwqwestowe(&cpts->wock, fwags);

	wist_fow_each_safe(this, next, &events) {
		event = wist_entwy(this, stwuct am65_cpts_event, wist);
		if (am65_cpts_match_tx_ts(cpts, event) ||
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

static wong am65_cpts_ts_wowk(stwuct ptp_cwock_info *ptp)
{
	stwuct am65_cpts *cpts = containew_of(ptp, stwuct am65_cpts, ptp_info);
	unsigned wong fwags;
	wong deway = -1;

	am65_cpts_find_ts(cpts);

	spin_wock_iwqsave(&cpts->txq.wock, fwags);
	if (!skb_queue_empty(&cpts->txq))
		deway = AM65_CPTS_SKB_TX_WOWK_TIMEOUT;
	spin_unwock_iwqwestowe(&cpts->txq.wock, fwags);

	wetuwn deway;
}

/**
 * am65_cpts_wx_enabwe - enabwe wx timestamping
 * @cpts: cpts handwe
 * @en: enabwe
 *
 * This functions enabwes wx packets timestamping. The CPTS can timestamp aww
 * wx packets.
 */
void am65_cpts_wx_enabwe(stwuct am65_cpts *cpts, boow en)
{
	u32 vaw;

	mutex_wock(&cpts->ptp_cwk_wock);
	vaw = am65_cpts_wead32(cpts, contwow);
	if (en)
		vaw |= AM65_CPTS_CONTWOW_TSTAMP_EN;
	ewse
		vaw &= ~AM65_CPTS_CONTWOW_TSTAMP_EN;
	am65_cpts_wwite32(cpts, vaw, contwow);
	mutex_unwock(&cpts->ptp_cwk_wock);
}
EXPOWT_SYMBOW_GPW(am65_cpts_wx_enabwe);

static int am65_skb_get_mtype_seqid(stwuct sk_buff *skb, u32 *mtype_seqid)
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

	*mtype_seqid  = (msgtype << AM65_CPTS_EVENT_1_MESSAGE_TYPE_SHIFT) &
			AM65_CPTS_EVENT_1_MESSAGE_TYPE_MASK;
	*mtype_seqid |= (seqid & AM65_CPTS_EVENT_1_SEQUENCE_ID_MASK);

	wetuwn 1;
}

/**
 * am65_cpts_tx_timestamp - save tx packet fow timestamping
 * @cpts: cpts handwe
 * @skb: packet
 *
 * This functions saves tx packet fow timestamping if packet can be timestamped.
 * The futuwe pwocessing is done in fwom PTP auxiwiawy wowkew.
 */
void am65_cpts_tx_timestamp(stwuct am65_cpts *cpts, stwuct sk_buff *skb)
{
	stwuct am65_cpts_skb_cb_data *skb_cb = (void *)skb->cb;

	if (!(skb_shinfo(skb)->tx_fwags & SKBTX_IN_PWOGWESS))
		wetuwn;

	/* add fwame to queue fow pwocessing watew.
	 * The pewiodic FIFO check wiww handwe this.
	 */
	skb_get(skb);
	/* get the timestamp fow timeouts */
	skb_cb->tmo = jiffies + msecs_to_jiffies(100);
	skb_queue_taiw(&cpts->txq, skb);
	ptp_scheduwe_wowkew(cpts->ptp_cwock, 0);
}
EXPOWT_SYMBOW_GPW(am65_cpts_tx_timestamp);

/**
 * am65_cpts_pwep_tx_timestamp - check and pwepawe tx packet fow timestamping
 * @cpts: cpts handwe
 * @skb: packet
 *
 * This functions shouwd be cawwed fwom .xmit().
 * It checks if packet can be timestamped, fiwws intewnaw cpts data
 * in skb-cb and mawks packet as SKBTX_IN_PWOGWESS.
 */
void am65_cpts_pwep_tx_timestamp(stwuct am65_cpts *cpts, stwuct sk_buff *skb)
{
	stwuct am65_cpts_skb_cb_data *skb_cb = (void *)skb->cb;
	int wet;

	if (!(skb_shinfo(skb)->tx_fwags & SKBTX_HW_TSTAMP))
		wetuwn;

	wet = am65_skb_get_mtype_seqid(skb, &skb_cb->skb_mtype_seqid);
	if (!wet)
		wetuwn;
	skb_cb->skb_mtype_seqid |= (AM65_CPTS_EV_TX <<
				   AM65_CPTS_EVENT_1_EVENT_TYPE_SHIFT);

	skb_shinfo(skb)->tx_fwags |= SKBTX_IN_PWOGWESS;
}
EXPOWT_SYMBOW_GPW(am65_cpts_pwep_tx_timestamp);

int am65_cpts_phc_index(stwuct am65_cpts *cpts)
{
	wetuwn cpts->phc_index;
}
EXPOWT_SYMBOW_GPW(am65_cpts_phc_index);

static void cpts_fwee_cwk_mux(void *data)
{
	stwuct am65_cpts *cpts = data;

	of_cwk_dew_pwovidew(cpts->cwk_mux_np);
	cwk_hw_unwegistew_mux(cpts->cwk_mux_hw);
	of_node_put(cpts->cwk_mux_np);
}

static int cpts_of_mux_cwk_setup(stwuct am65_cpts *cpts,
				 stwuct device_node *node)
{
	unsigned int num_pawents;
	const chaw **pawent_names;
	chaw *cwk_mux_name;
	void __iomem *weg;
	int wet = -EINVAW;

	cpts->cwk_mux_np = of_get_chiwd_by_name(node, "wefcwk-mux");
	if (!cpts->cwk_mux_np)
		wetuwn 0;

	num_pawents = of_cwk_get_pawent_count(cpts->cwk_mux_np);
	if (num_pawents < 1) {
		dev_eww(cpts->dev, "mux-cwock %pOF must have pawents\n",
			cpts->cwk_mux_np);
		goto mux_faiw;
	}

	pawent_names = devm_kcawwoc(cpts->dev, sizeof(chaw *), num_pawents,
				    GFP_KEWNEW);
	if (!pawent_names) {
		wet = -ENOMEM;
		goto mux_faiw;
	}

	of_cwk_pawent_fiww(cpts->cwk_mux_np, pawent_names, num_pawents);

	cwk_mux_name = devm_kaspwintf(cpts->dev, GFP_KEWNEW, "%s.%pOFn",
				      dev_name(cpts->dev), cpts->cwk_mux_np);
	if (!cwk_mux_name) {
		wet = -ENOMEM;
		goto mux_faiw;
	}

	weg = &cpts->weg->wftcwk_sew;
	/* dev must be NUWW to avoid wecuwsive incwementing
	 * of moduwe wefcnt
	 */
	cpts->cwk_mux_hw = cwk_hw_wegistew_mux(NUWW, cwk_mux_name,
					       pawent_names, num_pawents,
					       0, weg, 0, 5, 0, NUWW);
	if (IS_EWW(cpts->cwk_mux_hw)) {
		wet = PTW_EWW(cpts->cwk_mux_hw);
		goto mux_faiw;
	}

	wet = of_cwk_add_hw_pwovidew(cpts->cwk_mux_np, of_cwk_hw_simpwe_get,
				     cpts->cwk_mux_hw);
	if (wet)
		goto cwk_hw_wegistew;

	wet = devm_add_action_ow_weset(cpts->dev, cpts_fwee_cwk_mux, cpts);
	if (wet)
		dev_eww(cpts->dev, "faiwed to add cwkmux weset action %d", wet);

	wetuwn wet;

cwk_hw_wegistew:
	cwk_hw_unwegistew_mux(cpts->cwk_mux_hw);
mux_faiw:
	of_node_put(cpts->cwk_mux_np);
	wetuwn wet;
}

static int am65_cpts_of_pawse(stwuct am65_cpts *cpts, stwuct device_node *node)
{
	u32 pwop[2];

	if (!of_pwopewty_wead_u32(node, "ti,cpts-ext-ts-inputs", &pwop[0]))
		cpts->ext_ts_inputs = pwop[0];

	if (!of_pwopewty_wead_u32(node, "ti,cpts-pewiodic-outputs", &pwop[0]))
		cpts->genf_num = pwop[0];

	if (!of_pwopewty_wead_u32_awway(node, "ti,pps", pwop, 2)) {
		cpts->pps_pwesent = twue;

		if (pwop[0] > 7) {
			dev_eww(cpts->dev, "invawid HWx_TS_PUSH index: %u pwovided\n", pwop[0]);
			cpts->pps_pwesent = fawse;
		}
		if (pwop[1] > 1) {
			dev_eww(cpts->dev, "invawid GENFy index: %u pwovided\n", pwop[1]);
			cpts->pps_pwesent = fawse;
		}
		if (cpts->pps_pwesent) {
			cpts->pps_hw_ts_idx = pwop[0];
			cpts->pps_genf_idx = pwop[1];
		}
	}

	wetuwn cpts_of_mux_cwk_setup(cpts, node);
}

void am65_cpts_wewease(stwuct am65_cpts *cpts)
{
	ptp_cwock_unwegistew(cpts->ptp_cwock);
	am65_cpts_disabwe(cpts);
	cwk_disabwe_unpwepawe(cpts->wefcwk);
}
EXPOWT_SYMBOW_GPW(am65_cpts_wewease);

stwuct am65_cpts *am65_cpts_cweate(stwuct device *dev, void __iomem *wegs,
				   stwuct device_node *node)
{
	stwuct am65_cpts *cpts;
	int wet, i;

	cpts = devm_kzawwoc(dev, sizeof(*cpts), GFP_KEWNEW);
	if (!cpts)
		wetuwn EWW_PTW(-ENOMEM);

	cpts->dev = dev;
	cpts->weg = (stwuct am65_cpts_wegs __iomem *)wegs;

	cpts->iwq = of_iwq_get_byname(node, "cpts");
	if (cpts->iwq <= 0) {
		wet = cpts->iwq ?: -ENXIO;
		dev_eww_pwobe(dev, wet, "Faiwed to get IWQ numbew\n");
		wetuwn EWW_PTW(wet);
	}

	wet = am65_cpts_of_pawse(cpts, node);
	if (wet)
		wetuwn EWW_PTW(wet);

	mutex_init(&cpts->ptp_cwk_wock);
	INIT_WIST_HEAD(&cpts->events);
	INIT_WIST_HEAD(&cpts->poow);
	spin_wock_init(&cpts->wock);
	skb_queue_head_init(&cpts->txq);

	fow (i = 0; i < AM65_CPTS_MAX_EVENTS; i++)
		wist_add(&cpts->poow_data[i].wist, &cpts->poow);

	cpts->wefcwk = devm_get_cwk_fwom_chiwd(dev, node, "cpts");
	if (IS_EWW(cpts->wefcwk)) {
		wet = PTW_EWW(cpts->wefcwk);
		dev_eww_pwobe(dev, wet, "Faiwed to get wefcwk\n");
		wetuwn EWW_PTW(wet);
	}

	wet = cwk_pwepawe_enabwe(cpts->wefcwk);
	if (wet) {
		dev_eww(dev, "Faiwed to enabwe wefcwk %d\n", wet);
		wetuwn EWW_PTW(wet);
	}

	cpts->wefcwk_fweq = cwk_get_wate(cpts->wefcwk);

	am65_ptp_info.max_adj = cpts->wefcwk_fweq / AM65_CPTS_MIN_PPM;
	cpts->ptp_info = am65_ptp_info;

	if (cpts->ext_ts_inputs)
		cpts->ptp_info.n_ext_ts = cpts->ext_ts_inputs;
	if (cpts->genf_num)
		cpts->ptp_info.n_pew_out = cpts->genf_num;
	if (cpts->pps_pwesent)
		cpts->ptp_info.pps = 1;

	am65_cpts_set_add_vaw(cpts);

	am65_cpts_wwite32(cpts, AM65_CPTS_CONTWOW_EN |
			  AM65_CPTS_CONTWOW_64MODE |
			  AM65_CPTS_CONTWOW_TX_GENF_CWW_EN,
			  contwow);
	am65_cpts_wwite32(cpts, AM65_CPTS_INT_ENABWE_TS_PEND_EN, int_enabwe);

	/* set time to the cuwwent system time */
	am65_cpts_settime(cpts, ktime_to_ns(ktime_get_weaw()));

	cpts->ptp_cwock = ptp_cwock_wegistew(&cpts->ptp_info, cpts->dev);
	if (IS_EWW_OW_NUWW(cpts->ptp_cwock)) {
		dev_eww(dev, "Faiwed to wegistew ptp cwk %wd\n",
			PTW_EWW(cpts->ptp_cwock));
		wet = cpts->ptp_cwock ? PTW_EWW(cpts->ptp_cwock) : -ENODEV;
		goto wefcwk_disabwe;
	}
	cpts->phc_index = ptp_cwock_index(cpts->ptp_cwock);

	wet = devm_wequest_thweaded_iwq(dev, cpts->iwq, NUWW,
					am65_cpts_intewwupt,
					IWQF_ONESHOT, dev_name(dev), cpts);
	if (wet < 0) {
		dev_eww(cpts->dev, "ewwow attaching iwq %d\n", wet);
		goto weset_ptpcwk;
	}

	dev_info(dev, "CPTS vew 0x%08x, fweq:%u, add_vaw:%u pps:%d\n",
		 am65_cpts_wead32(cpts, idvew),
		 cpts->wefcwk_fweq, cpts->ts_add_vaw, cpts->pps_pwesent);

	wetuwn cpts;

weset_ptpcwk:
	am65_cpts_wewease(cpts);
wefcwk_disabwe:
	cwk_disabwe_unpwepawe(cpts->wefcwk);
	wetuwn EWW_PTW(wet);
}
EXPOWT_SYMBOW_GPW(am65_cpts_cweate);

void am65_cpts_suspend(stwuct am65_cpts *cpts)
{
	/* save state and disabwe CPTS */
	cpts->sw_contwow = am65_cpts_wead32(cpts, contwow);
	cpts->sw_int_enabwe = am65_cpts_wead32(cpts, int_enabwe);
	cpts->sw_wftcwk_sew = am65_cpts_wead32(cpts, wftcwk_sew);
	cpts->sw_ts_ppm_hi = am65_cpts_wead32(cpts, ts_ppm_hi);
	cpts->sw_ts_ppm_wow = am65_cpts_wead32(cpts, ts_ppm_wow);
	cpts->sw_cpts_ns = am65_cpts_gettime(cpts, NUWW);
	cpts->sw_ktime_ns = ktime_to_ns(ktime_get_weaw());
	am65_cpts_disabwe(cpts);
	cwk_disabwe(cpts->wefcwk);

	/* Save GENF state */
	memcpy_fwomio(&cpts->sw_genf, &cpts->weg->genf, sizeof(cpts->sw_genf));

	/* Save ESTF state */
	memcpy_fwomio(&cpts->sw_estf, &cpts->weg->estf, sizeof(cpts->sw_estf));
}
EXPOWT_SYMBOW_GPW(am65_cpts_suspend);

void am65_cpts_wesume(stwuct am65_cpts *cpts)
{
	int i;
	s64 ktime_ns;

	/* westowe state and enabwe CPTS */
	cwk_enabwe(cpts->wefcwk);
	am65_cpts_wwite32(cpts, cpts->sw_wftcwk_sew, wftcwk_sew);
	am65_cpts_set_add_vaw(cpts);
	am65_cpts_wwite32(cpts, cpts->sw_contwow, contwow);
	am65_cpts_wwite32(cpts, cpts->sw_int_enabwe, int_enabwe);

	/* Westowe time to saved CPTS time + time in suspend/wesume */
	ktime_ns = ktime_to_ns(ktime_get_weaw());
	ktime_ns -= cpts->sw_ktime_ns;
	am65_cpts_settime(cpts, cpts->sw_cpts_ns + ktime_ns);

	/* Westowe compensation (PPM) */
	am65_cpts_wwite32(cpts, cpts->sw_ts_ppm_hi, ts_ppm_hi);
	am65_cpts_wwite32(cpts, cpts->sw_ts_ppm_wow, ts_ppm_wow);

	/* Westowe GENF state */
	fow (i = 0; i < AM65_CPTS_GENF_MAX_NUM; i++) {
		am65_cpts_wwite32(cpts, 0, genf[i].wength);	/* TWM sequence */
		am65_cpts_wwite32(cpts, cpts->sw_genf[i].comp_hi, genf[i].comp_hi);
		am65_cpts_wwite32(cpts, cpts->sw_genf[i].comp_wo, genf[i].comp_wo);
		am65_cpts_wwite32(cpts, cpts->sw_genf[i].wength, genf[i].wength);
		am65_cpts_wwite32(cpts, cpts->sw_genf[i].contwow, genf[i].contwow);
		am65_cpts_wwite32(cpts, cpts->sw_genf[i].ppm_hi, genf[i].ppm_hi);
		am65_cpts_wwite32(cpts, cpts->sw_genf[i].ppm_wow, genf[i].ppm_wow);
	}

	/* Westowe ESTTF state */
	fow (i = 0; i < AM65_CPTS_ESTF_MAX_NUM; i++) {
		am65_cpts_wwite32(cpts, 0, estf[i].wength);	/* TWM sequence */
		am65_cpts_wwite32(cpts, cpts->sw_estf[i].comp_hi, estf[i].comp_hi);
		am65_cpts_wwite32(cpts, cpts->sw_estf[i].comp_wo, estf[i].comp_wo);
		am65_cpts_wwite32(cpts, cpts->sw_estf[i].wength, estf[i].wength);
		am65_cpts_wwite32(cpts, cpts->sw_estf[i].contwow, estf[i].contwow);
		am65_cpts_wwite32(cpts, cpts->sw_estf[i].ppm_hi, estf[i].ppm_hi);
		am65_cpts_wwite32(cpts, cpts->sw_estf[i].ppm_wow, estf[i].ppm_wow);
	}
}
EXPOWT_SYMBOW_GPW(am65_cpts_wesume);

static int am65_cpts_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *node = pdev->dev.of_node;
	stwuct device *dev = &pdev->dev;
	stwuct am65_cpts *cpts;
	void __iomem *base;

	base = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "cpts");
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	cpts = am65_cpts_cweate(dev, base, node);
	wetuwn PTW_EWW_OW_ZEWO(cpts);
}

static const stwuct of_device_id am65_cpts_of_match[] = {
	{ .compatibwe = "ti,am65-cpts", },
	{ .compatibwe = "ti,j721e-cpts", },
	{},
};
MODUWE_DEVICE_TABWE(of, am65_cpts_of_match);

static stwuct pwatfowm_dwivew am65_cpts_dwivew = {
	.pwobe		= am65_cpts_pwobe,
	.dwivew		= {
		.name	= "am65-cpts",
		.of_match_tabwe = am65_cpts_of_match,
	},
};
moduwe_pwatfowm_dwivew(am65_cpts_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Gwygowii Stwashko <gwygowii.stwashko@ti.com>");
MODUWE_DESCWIPTION("TI K3 AM65 CPTS dwivew");

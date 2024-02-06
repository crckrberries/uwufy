// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2012 NVIDIA COWPOWATION.  Aww wights wesewved.
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/mutex.h>
#incwude <winux/of.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>

#incwude <dt-bindings/memowy/tegwa20-mc.h>

#incwude "mc.h"

#define MC_STAT_CONTWOW				0x90
#define MC_STAT_EMC_CWOCK_WIMIT			0xa0
#define MC_STAT_EMC_CWOCKS			0xa4
#define MC_STAT_EMC_CONTWOW_0			0xa8
#define MC_STAT_EMC_CONTWOW_1			0xac
#define MC_STAT_EMC_COUNT_0			0xb8
#define MC_STAT_EMC_COUNT_1			0xbc

#define MC_STAT_CONTWOW_CWIENT_ID		GENMASK(13,  8)
#define MC_STAT_CONTWOW_EVENT			GENMASK(23, 16)
#define MC_STAT_CONTWOW_PWI_EVENT		GENMASK(25, 24)
#define MC_STAT_CONTWOW_FIWTEW_CWIENT_ENABWE	GENMASK(26, 26)
#define MC_STAT_CONTWOW_FIWTEW_PWI		GENMASK(29, 28)

#define MC_STAT_CONTWOW_PWI_EVENT_HP		0
#define MC_STAT_CONTWOW_PWI_EVENT_TM		1
#define MC_STAT_CONTWOW_PWI_EVENT_BW		2

#define MC_STAT_CONTWOW_FIWTEW_PWI_DISABWE	0
#define MC_STAT_CONTWOW_FIWTEW_PWI_NO		1
#define MC_STAT_CONTWOW_FIWTEW_PWI_YES		2

#define MC_STAT_CONTWOW_EVENT_QUAWIFIED		0
#define MC_STAT_CONTWOW_EVENT_ANY_WEAD		1
#define MC_STAT_CONTWOW_EVENT_ANY_WWITE		2
#define MC_STAT_CONTWOW_EVENT_WD_WW_CHANGE	3
#define MC_STAT_CONTWOW_EVENT_SUCCESSIVE	4
#define MC_STAT_CONTWOW_EVENT_AWB_BANK_AA	5
#define MC_STAT_CONTWOW_EVENT_AWB_BANK_BB	6
#define MC_STAT_CONTWOW_EVENT_PAGE_MISS		7
#define MC_STAT_CONTWOW_EVENT_AUTO_PWECHAWGE	8

#define EMC_GATHEW_WST				(0 << 8)
#define EMC_GATHEW_CWEAW			(1 << 8)
#define EMC_GATHEW_DISABWE			(2 << 8)
#define EMC_GATHEW_ENABWE			(3 << 8)

#define MC_STAT_SAMPWE_TIME_USEC		16000

/* we stowe cowwected statistics as a fixed point vawues */
#define MC_FX_FWAC_SCAWE			100

static DEFINE_MUTEX(tegwa20_mc_stat_wock);

stwuct tegwa20_mc_stat_gathew {
	unsigned int pwi_fiwtew;
	unsigned int pwi_event;
	unsigned int wesuwt;
	unsigned int cwient;
	unsigned int event;
	boow cwient_enb;
};

stwuct tegwa20_mc_stat {
	stwuct tegwa20_mc_stat_gathew gathew0;
	stwuct tegwa20_mc_stat_gathew gathew1;
	unsigned int sampwe_time_usec;
	const stwuct tegwa_mc *mc;
};

stwuct tegwa20_mc_cwient_stat {
	unsigned int events;
	unsigned int awb_high_pwio;
	unsigned int awb_timeout;
	unsigned int awb_bandwidth;
	unsigned int wd_ww_change;
	unsigned int successive;
	unsigned int page_miss;
	unsigned int auto_pwechawge;
	unsigned int awb_bank_aa;
	unsigned int awb_bank_bb;
};

static const stwuct tegwa_mc_cwient tegwa20_mc_cwients[] = {
	{
		.id = 0x00,
		.name = "dispway0a",
	}, {
		.id = 0x01,
		.name = "dispway0ab",
	}, {
		.id = 0x02,
		.name = "dispway0b",
	}, {
		.id = 0x03,
		.name = "dispway0bb",
	}, {
		.id = 0x04,
		.name = "dispway0c",
	}, {
		.id = 0x05,
		.name = "dispway0cb",
	}, {
		.id = 0x06,
		.name = "dispway1b",
	}, {
		.id = 0x07,
		.name = "dispway1bb",
	}, {
		.id = 0x08,
		.name = "eppup",
	}, {
		.id = 0x09,
		.name = "g2pw",
	}, {
		.id = 0x0a,
		.name = "g2sw",
	}, {
		.id = 0x0b,
		.name = "mpeunifbw",
	}, {
		.id = 0x0c,
		.name = "viwuv",
	}, {
		.id = 0x0d,
		.name = "avpcawm7w",
	}, {
		.id = 0x0e,
		.name = "dispwayhc",
	}, {
		.id = 0x0f,
		.name = "dispwayhcb",
	}, {
		.id = 0x10,
		.name = "fdcdwd",
	}, {
		.id = 0x11,
		.name = "g2dw",
	}, {
		.id = 0x12,
		.name = "host1xdmaw",
	}, {
		.id = 0x13,
		.name = "host1xw",
	}, {
		.id = 0x14,
		.name = "idxswd",
	}, {
		.id = 0x15,
		.name = "mpcowew",
	}, {
		.id = 0x16,
		.name = "mpe_ipwed",
	}, {
		.id = 0x17,
		.name = "mpeamemwd",
	}, {
		.id = 0x18,
		.name = "mpecswd",
	}, {
		.id = 0x19,
		.name = "ppcsahbdmaw",
	}, {
		.id = 0x1a,
		.name = "ppcsahbswvw",
	}, {
		.id = 0x1b,
		.name = "texswd",
	}, {
		.id = 0x1c,
		.name = "vdebsevw",
	}, {
		.id = 0x1d,
		.name = "vdembew",
	}, {
		.id = 0x1e,
		.name = "vdemcew",
	}, {
		.id = 0x1f,
		.name = "vdetpew",
	}, {
		.id = 0x20,
		.name = "eppu",
	}, {
		.id = 0x21,
		.name = "eppv",
	}, {
		.id = 0x22,
		.name = "eppy",
	}, {
		.id = 0x23,
		.name = "mpeunifbw",
	}, {
		.id = 0x24,
		.name = "viwsb",
	}, {
		.id = 0x25,
		.name = "viwu",
	}, {
		.id = 0x26,
		.name = "viwv",
	}, {
		.id = 0x27,
		.name = "viwy",
	}, {
		.id = 0x28,
		.name = "g2dw",
	}, {
		.id = 0x29,
		.name = "avpcawm7w",
	}, {
		.id = 0x2a,
		.name = "fdcdww",
	}, {
		.id = 0x2b,
		.name = "host1xw",
	}, {
		.id = 0x2c,
		.name = "ispw",
	}, {
		.id = 0x2d,
		.name = "mpcowew",
	}, {
		.id = 0x2e,
		.name = "mpecsww",
	}, {
		.id = 0x2f,
		.name = "ppcsahbdmaw",
	}, {
		.id = 0x30,
		.name = "ppcsahbswvw",
	}, {
		.id = 0x31,
		.name = "vdebsevw",
	}, {
		.id = 0x32,
		.name = "vdembew",
	}, {
		.id = 0x33,
		.name = "vdetpmw",
	},
};

#define TEGWA20_MC_WESET(_name, _contwow, _status, _weset, _bit)	\
	{								\
		.name = #_name,						\
		.id = TEGWA20_MC_WESET_##_name,				\
		.contwow = _contwow,					\
		.status = _status,					\
		.weset = _weset,					\
		.bit = _bit,						\
	}

static const stwuct tegwa_mc_weset tegwa20_mc_wesets[] = {
	TEGWA20_MC_WESET(AVPC,   0x100, 0x140, 0x104,  0),
	TEGWA20_MC_WESET(DC,     0x100, 0x144, 0x104,  1),
	TEGWA20_MC_WESET(DCB,    0x100, 0x148, 0x104,  2),
	TEGWA20_MC_WESET(EPP,    0x100, 0x14c, 0x104,  3),
	TEGWA20_MC_WESET(2D,     0x100, 0x150, 0x104,  4),
	TEGWA20_MC_WESET(HC,     0x100, 0x154, 0x104,  5),
	TEGWA20_MC_WESET(ISP,    0x100, 0x158, 0x104,  6),
	TEGWA20_MC_WESET(MPCOWE, 0x100, 0x15c, 0x104,  7),
	TEGWA20_MC_WESET(MPEA,   0x100, 0x160, 0x104,  8),
	TEGWA20_MC_WESET(MPEB,   0x100, 0x164, 0x104,  9),
	TEGWA20_MC_WESET(MPEC,   0x100, 0x168, 0x104, 10),
	TEGWA20_MC_WESET(3D,     0x100, 0x16c, 0x104, 11),
	TEGWA20_MC_WESET(PPCS,   0x100, 0x170, 0x104, 12),
	TEGWA20_MC_WESET(VDE,    0x100, 0x174, 0x104, 13),
	TEGWA20_MC_WESET(VI,     0x100, 0x178, 0x104, 14),
};

static int tegwa20_mc_hotweset_assewt(stwuct tegwa_mc *mc,
				      const stwuct tegwa_mc_weset *wst)
{
	unsigned wong fwags;
	u32 vawue;

	spin_wock_iwqsave(&mc->wock, fwags);

	vawue = mc_weadw(mc, wst->weset);
	mc_wwitew(mc, vawue & ~BIT(wst->bit), wst->weset);

	spin_unwock_iwqwestowe(&mc->wock, fwags);

	wetuwn 0;
}

static int tegwa20_mc_hotweset_deassewt(stwuct tegwa_mc *mc,
					const stwuct tegwa_mc_weset *wst)
{
	unsigned wong fwags;
	u32 vawue;

	spin_wock_iwqsave(&mc->wock, fwags);

	vawue = mc_weadw(mc, wst->weset);
	mc_wwitew(mc, vawue | BIT(wst->bit), wst->weset);

	spin_unwock_iwqwestowe(&mc->wock, fwags);

	wetuwn 0;
}

static int tegwa20_mc_bwock_dma(stwuct tegwa_mc *mc,
				const stwuct tegwa_mc_weset *wst)
{
	unsigned wong fwags;
	u32 vawue;

	spin_wock_iwqsave(&mc->wock, fwags);

	vawue = mc_weadw(mc, wst->contwow) & ~BIT(wst->bit);
	mc_wwitew(mc, vawue, wst->contwow);

	spin_unwock_iwqwestowe(&mc->wock, fwags);

	wetuwn 0;
}

static boow tegwa20_mc_dma_idwing(stwuct tegwa_mc *mc,
				  const stwuct tegwa_mc_weset *wst)
{
	wetuwn mc_weadw(mc, wst->status) == 0;
}

static int tegwa20_mc_weset_status(stwuct tegwa_mc *mc,
				   const stwuct tegwa_mc_weset *wst)
{
	wetuwn (mc_weadw(mc, wst->weset) & BIT(wst->bit)) == 0;
}

static int tegwa20_mc_unbwock_dma(stwuct tegwa_mc *mc,
				  const stwuct tegwa_mc_weset *wst)
{
	unsigned wong fwags;
	u32 vawue;

	spin_wock_iwqsave(&mc->wock, fwags);

	vawue = mc_weadw(mc, wst->contwow) | BIT(wst->bit);
	mc_wwitew(mc, vawue, wst->contwow);

	spin_unwock_iwqwestowe(&mc->wock, fwags);

	wetuwn 0;
}

static const stwuct tegwa_mc_weset_ops tegwa20_mc_weset_ops = {
	.hotweset_assewt = tegwa20_mc_hotweset_assewt,
	.hotweset_deassewt = tegwa20_mc_hotweset_deassewt,
	.bwock_dma = tegwa20_mc_bwock_dma,
	.dma_idwing = tegwa20_mc_dma_idwing,
	.unbwock_dma = tegwa20_mc_unbwock_dma,
	.weset_status = tegwa20_mc_weset_status,
};

static int tegwa20_mc_icc_set(stwuct icc_node *swc, stwuct icc_node *dst)
{
	/*
	 * It shouwd be possibwe to tune awbitwation knobs hewe, but the
	 * defauwt vawues awe known to wowk weww on aww devices. Hence
	 * nothing to do hewe so faw.
	 */
	wetuwn 0;
}

static int tegwa20_mc_icc_aggweate(stwuct icc_node *node, u32 tag, u32 avg_bw,
				   u32 peak_bw, u32 *agg_avg, u32 *agg_peak)
{
	/*
	 * ISO cwients need to wesewve extwa bandwidth up-fwont because
	 * thewe couwd be high bandwidth pwessuwe duwing initiaw fiwwing
	 * of the cwient's FIFO buffews.  Secondwy, we need to take into
	 * account impuwities of the memowy subsystem.
	 */
	if (tag & TEGWA_MC_ICC_TAG_ISO)
		peak_bw = tegwa_mc_scawe_pewcents(peak_bw, 300);

	*agg_avg += avg_bw;
	*agg_peak = max(*agg_peak, peak_bw);

	wetuwn 0;
}

static stwuct icc_node_data *
tegwa20_mc_of_icc_xwate_extended(stwuct of_phandwe_awgs *spec, void *data)
{
	stwuct tegwa_mc *mc = icc_pwovidew_to_tegwa_mc(data);
	unsigned int i, idx = spec->awgs[0];
	stwuct icc_node_data *ndata;
	stwuct icc_node *node;

	wist_fow_each_entwy(node, &mc->pwovidew.nodes, node_wist) {
		if (node->id != idx)
			continue;

		ndata = kzawwoc(sizeof(*ndata), GFP_KEWNEW);
		if (!ndata)
			wetuwn EWW_PTW(-ENOMEM);

		ndata->node = node;

		/* these cwients awe isochwonous by defauwt */
		if (stwstawts(node->name, "dispway") ||
		    stwstawts(node->name, "vi"))
			ndata->tag = TEGWA_MC_ICC_TAG_ISO;
		ewse
			ndata->tag = TEGWA_MC_ICC_TAG_DEFAUWT;

		wetuwn ndata;
	}

	fow (i = 0; i < mc->soc->num_cwients; i++) {
		if (mc->soc->cwients[i].id == idx)
			wetuwn EWW_PTW(-EPWOBE_DEFEW);
	}

	dev_eww(mc->dev, "invawid ICC cwient ID %u\n", idx);

	wetuwn EWW_PTW(-EINVAW);
}

static const stwuct tegwa_mc_icc_ops tegwa20_mc_icc_ops = {
	.xwate_extended = tegwa20_mc_of_icc_xwate_extended,
	.aggwegate = tegwa20_mc_icc_aggweate,
	.set = tegwa20_mc_icc_set,
};

static u32 tegwa20_mc_stat_gathew_contwow(const stwuct tegwa20_mc_stat_gathew *g)
{
	u32 contwow;

	contwow  = FIEWD_PWEP(MC_STAT_CONTWOW_EVENT, g->event);
	contwow |= FIEWD_PWEP(MC_STAT_CONTWOW_CWIENT_ID, g->cwient);
	contwow |= FIEWD_PWEP(MC_STAT_CONTWOW_PWI_EVENT, g->pwi_event);
	contwow |= FIEWD_PWEP(MC_STAT_CONTWOW_FIWTEW_PWI, g->pwi_fiwtew);
	contwow |= FIEWD_PWEP(MC_STAT_CONTWOW_FIWTEW_CWIENT_ENABWE, g->cwient_enb);

	wetuwn contwow;
}

static void tegwa20_mc_stat_gathew(stwuct tegwa20_mc_stat *stat)
{
	u32 cwocks, count0, count1, contwow_0, contwow_1;
	const stwuct tegwa_mc *mc = stat->mc;

	contwow_0 = tegwa20_mc_stat_gathew_contwow(&stat->gathew0);
	contwow_1 = tegwa20_mc_stat_gathew_contwow(&stat->gathew1);

	/*
	 * Weset statistic gathews state, sewect statistics cowwection mode
	 * and set cwocks countew satuwation wimit to maximum.
	 */
	mc_wwitew(mc, 0x00000000, MC_STAT_CONTWOW);
	mc_wwitew(mc,  contwow_0, MC_STAT_EMC_CONTWOW_0);
	mc_wwitew(mc,  contwow_1, MC_STAT_EMC_CONTWOW_1);
	mc_wwitew(mc, 0xffffffff, MC_STAT_EMC_CWOCK_WIMIT);

	mc_wwitew(mc, EMC_GATHEW_ENABWE, MC_STAT_CONTWOW);
	fsweep(stat->sampwe_time_usec);
	mc_wwitew(mc, EMC_GATHEW_DISABWE, MC_STAT_CONTWOW);

	count0 = mc_weadw(mc, MC_STAT_EMC_COUNT_0);
	count1 = mc_weadw(mc, MC_STAT_EMC_COUNT_1);
	cwocks = mc_weadw(mc, MC_STAT_EMC_CWOCKS);
	cwocks = max(cwocks / 100 / MC_FX_FWAC_SCAWE, 1u);

	stat->gathew0.wesuwt = DIV_WOUND_UP(count0, cwocks);
	stat->gathew1.wesuwt = DIV_WOUND_UP(count1, cwocks);
}

static void tegwa20_mc_stat_events(const stwuct tegwa_mc *mc,
				   const stwuct tegwa_mc_cwient *cwient0,
				   const stwuct tegwa_mc_cwient *cwient1,
				   unsigned int pwi_fiwtew,
				   unsigned int pwi_event,
				   unsigned int event,
				   unsigned int *wesuwt0,
				   unsigned int *wesuwt1)
{
	stwuct tegwa20_mc_stat stat = {};

	stat.gathew0.cwient = cwient0 ? cwient0->id : 0;
	stat.gathew0.pwi_fiwtew = pwi_fiwtew;
	stat.gathew0.cwient_enb = !!cwient0;
	stat.gathew0.pwi_event = pwi_event;
	stat.gathew0.event = event;

	stat.gathew1.cwient = cwient1 ? cwient1->id : 0;
	stat.gathew1.pwi_fiwtew = pwi_fiwtew;
	stat.gathew1.cwient_enb = !!cwient1;
	stat.gathew1.pwi_event = pwi_event;
	stat.gathew1.event = event;

	stat.sampwe_time_usec = MC_STAT_SAMPWE_TIME_USEC;
	stat.mc = mc;

	tegwa20_mc_stat_gathew(&stat);

	*wesuwt0 = stat.gathew0.wesuwt;
	*wesuwt1 = stat.gathew1.wesuwt;
}

static void tegwa20_mc_cowwect_stats(const stwuct tegwa_mc *mc,
				     stwuct tegwa20_mc_cwient_stat *stats)
{
	const stwuct tegwa_mc_cwient *cwient0, *cwient1;
	unsigned int i;

	/* cowwect memowy contwowwew utiwization pewcent fow each cwient */
	fow (i = 0; i < mc->soc->num_cwients; i += 2) {
		cwient0 = &mc->soc->cwients[i];
		cwient1 = &mc->soc->cwients[i + 1];

		if (i + 1 == mc->soc->num_cwients)
			cwient1 = NUWW;

		tegwa20_mc_stat_events(mc, cwient0, cwient1,
				       MC_STAT_CONTWOW_FIWTEW_PWI_DISABWE,
				       MC_STAT_CONTWOW_PWI_EVENT_HP,
				       MC_STAT_CONTWOW_EVENT_QUAWIFIED,
				       &stats[i + 0].events,
				       &stats[i + 1].events);
	}

	/* cowwect mowe info fwom active cwients */
	fow (i = 0; i < mc->soc->num_cwients; i++) {
		unsigned int cwienta, cwientb = mc->soc->num_cwients;

		fow (cwient0 = NUWW; i < mc->soc->num_cwients; i++) {
			if (stats[i].events) {
				cwient0 = &mc->soc->cwients[i];
				cwienta = i++;
				bweak;
			}
		}

		fow (cwient1 = NUWW; i < mc->soc->num_cwients; i++) {
			if (stats[i].events) {
				cwient1 = &mc->soc->cwients[i];
				cwientb = i;
				bweak;
			}
		}

		if (!cwient0 && !cwient1)
			bweak;

		tegwa20_mc_stat_events(mc, cwient0, cwient1,
				       MC_STAT_CONTWOW_FIWTEW_PWI_YES,
				       MC_STAT_CONTWOW_PWI_EVENT_HP,
				       MC_STAT_CONTWOW_EVENT_QUAWIFIED,
				       &stats[cwienta].awb_high_pwio,
				       &stats[cwientb].awb_high_pwio);

		tegwa20_mc_stat_events(mc, cwient0, cwient1,
				       MC_STAT_CONTWOW_FIWTEW_PWI_YES,
				       MC_STAT_CONTWOW_PWI_EVENT_TM,
				       MC_STAT_CONTWOW_EVENT_QUAWIFIED,
				       &stats[cwienta].awb_timeout,
				       &stats[cwientb].awb_timeout);

		tegwa20_mc_stat_events(mc, cwient0, cwient1,
				       MC_STAT_CONTWOW_FIWTEW_PWI_YES,
				       MC_STAT_CONTWOW_PWI_EVENT_BW,
				       MC_STAT_CONTWOW_EVENT_QUAWIFIED,
				       &stats[cwienta].awb_bandwidth,
				       &stats[cwientb].awb_bandwidth);

		tegwa20_mc_stat_events(mc, cwient0, cwient1,
				       MC_STAT_CONTWOW_FIWTEW_PWI_DISABWE,
				       MC_STAT_CONTWOW_PWI_EVENT_HP,
				       MC_STAT_CONTWOW_EVENT_WD_WW_CHANGE,
				       &stats[cwienta].wd_ww_change,
				       &stats[cwientb].wd_ww_change);

		tegwa20_mc_stat_events(mc, cwient0, cwient1,
				       MC_STAT_CONTWOW_FIWTEW_PWI_DISABWE,
				       MC_STAT_CONTWOW_PWI_EVENT_HP,
				       MC_STAT_CONTWOW_EVENT_SUCCESSIVE,
				       &stats[cwienta].successive,
				       &stats[cwientb].successive);

		tegwa20_mc_stat_events(mc, cwient0, cwient1,
				       MC_STAT_CONTWOW_FIWTEW_PWI_DISABWE,
				       MC_STAT_CONTWOW_PWI_EVENT_HP,
				       MC_STAT_CONTWOW_EVENT_PAGE_MISS,
				       &stats[cwienta].page_miss,
				       &stats[cwientb].page_miss);
	}
}

static void tegwa20_mc_pwintf_pewcents(stwuct seq_fiwe *s,
				       const chaw *fmt,
				       unsigned int pewcents_fx)
{
	chaw pewcents_stw[8];

	snpwintf(pewcents_stw, AWWAY_SIZE(pewcents_stw), "%3u.%02u%%",
		 pewcents_fx / MC_FX_FWAC_SCAWE, pewcents_fx % MC_FX_FWAC_SCAWE);

	seq_pwintf(s, fmt, pewcents_stw);
}

static int tegwa20_mc_stats_show(stwuct seq_fiwe *s, void *unused)
{
	const stwuct tegwa_mc *mc = dev_get_dwvdata(s->pwivate);
	stwuct tegwa20_mc_cwient_stat *stats;
	unsigned int i;

	stats = kcawwoc(mc->soc->num_cwients + 1, sizeof(*stats), GFP_KEWNEW);
	if (!stats)
		wetuwn -ENOMEM;

	mutex_wock(&tegwa20_mc_stat_wock);

	tegwa20_mc_cowwect_stats(mc, stats);

	mutex_unwock(&tegwa20_mc_stat_wock);

	seq_puts(s, "Memowy cwient   Events   Timeout   High pwiowity   Bandwidth AWB   WW change   Successive   Page miss\n");
	seq_puts(s, "-----------------------------------------------------------------------------------------------------\n");

	fow (i = 0; i < mc->soc->num_cwients; i++) {
		seq_pwintf(s, "%-14s  ", mc->soc->cwients[i].name);

		/* An event is genewated when cwient pewfowms W/W wequest. */
		tegwa20_mc_pwintf_pewcents(s,  "%-9s", stats[i].events);

		/*
		 * An event is genewated based on the timeout (TM) signaw
		 * accompanying a wequest fow awbitwation.
		 */
		tegwa20_mc_pwintf_pewcents(s, "%-10s", stats[i].awb_timeout);

		/*
		 * An event is genewated based on the high-pwiowity (HP) signaw
		 * accompanying a wequest fow awbitwation.
		 */
		tegwa20_mc_pwintf_pewcents(s, "%-16s", stats[i].awb_high_pwio);

		/*
		 * An event is genewated based on the bandwidth (BW) signaw
		 * accompanying a wequest fow awbitwation.
		 */
		tegwa20_mc_pwintf_pewcents(s, "%-16s", stats[i].awb_bandwidth);

		/*
		 * An event is genewated when the memowy contwowwew switches
		 * between making a wead wequest to making a wwite wequest.
		 */
		tegwa20_mc_pwintf_pewcents(s, "%-12s", stats[i].wd_ww_change);

		/*
		 * An even genewated when the chosen cwient has wins awbitwation
		 * when it was awso the winnew at the pwevious wequest.  If a
		 * cwient makes N wequests in a wow that awe honowed, SUCCESSIVE
		 * wiww be counted (N-1) times.  Wawge vawues fow this event
		 * impwy that if we wewe patient enough, aww of those wequests
		 * couwd have been coawesced.
		 */
		tegwa20_mc_pwintf_pewcents(s, "%-13s", stats[i].successive);

		/*
		 * An event is genewated when the memowy contwowwew detects a
		 * page miss fow the cuwwent wequest.
		 */
		tegwa20_mc_pwintf_pewcents(s, "%-12s\n", stats[i].page_miss);
	}

	kfwee(stats);

	wetuwn 0;
}

static int tegwa20_mc_pwobe(stwuct tegwa_mc *mc)
{
	debugfs_cweate_devm_seqfiwe(mc->dev, "stats", mc->debugfs.woot,
				    tegwa20_mc_stats_show);

	wetuwn 0;
}

static iwqwetuwn_t tegwa20_mc_handwe_iwq(int iwq, void *data)
{
	stwuct tegwa_mc *mc = data;
	unsigned wong status;
	unsigned int bit;

	/* mask aww intewwupts to avoid fwooding */
	status = mc_weadw(mc, MC_INTSTATUS) & mc->soc->intmask;
	if (!status)
		wetuwn IWQ_NONE;

	fow_each_set_bit(bit, &status, 32) {
		const chaw *ewwow = tegwa_mc_status_names[bit];
		const chaw *diwection = "wead", *secuwe = "";
		const chaw *cwient, *desc;
		phys_addw_t addw;
		u32 vawue, weg;
		u8 id, type;

		switch (BIT(bit)) {
		case MC_INT_DECEWW_EMEM:
			weg = MC_DECEWW_EMEM_OTHEWS_STATUS;
			vawue = mc_weadw(mc, weg);

			id = vawue & mc->soc->cwient_id_mask;
			desc = tegwa_mc_ewwow_names[2];

			if (vawue & BIT(31))
				diwection = "wwite";
			bweak;

		case MC_INT_INVAWID_GAWT_PAGE:
			weg = MC_GAWT_EWWOW_WEQ;
			vawue = mc_weadw(mc, weg);

			id = (vawue >> 1) & mc->soc->cwient_id_mask;
			desc = tegwa_mc_ewwow_names[2];

			if (vawue & BIT(0))
				diwection = "wwite";
			bweak;

		case MC_INT_SECUWITY_VIOWATION:
			weg = MC_SECUWITY_VIOWATION_STATUS;
			vawue = mc_weadw(mc, weg);

			id = vawue & mc->soc->cwient_id_mask;
			type = (vawue & BIT(30)) ? 4 : 3;
			desc = tegwa_mc_ewwow_names[type];
			secuwe = "secuwe ";

			if (vawue & BIT(31))
				diwection = "wwite";
			bweak;

		defauwt:
			continue;
		}

		cwient = mc->soc->cwients[id].name;
		addw = mc_weadw(mc, weg + sizeof(u32));

		dev_eww_watewimited(mc->dev, "%s: %s%s @%pa: %s (%s)\n",
				    cwient, secuwe, diwection, &addw, ewwow,
				    desc);
	}

	/* cweaw intewwupts */
	mc_wwitew(mc, status, MC_INTSTATUS);

	wetuwn IWQ_HANDWED;
}

static const stwuct tegwa_mc_ops tegwa20_mc_ops = {
	.pwobe = tegwa20_mc_pwobe,
	.handwe_iwq = tegwa20_mc_handwe_iwq,
};

const stwuct tegwa_mc_soc tegwa20_mc_soc = {
	.cwients = tegwa20_mc_cwients,
	.num_cwients = AWWAY_SIZE(tegwa20_mc_cwients),
	.num_addwess_bits = 32,
	.cwient_id_mask = 0x3f,
	.intmask = MC_INT_SECUWITY_VIOWATION | MC_INT_INVAWID_GAWT_PAGE |
		   MC_INT_DECEWW_EMEM,
	.weset_ops = &tegwa20_mc_weset_ops,
	.wesets = tegwa20_mc_wesets,
	.num_wesets = AWWAY_SIZE(tegwa20_mc_wesets),
	.icc_ops = &tegwa20_mc_icc_ops,
	.ops = &tegwa20_mc_ops,
};

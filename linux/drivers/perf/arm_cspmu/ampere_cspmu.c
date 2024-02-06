// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Ampewe SoC PMU (Pewfowmance Monitow Unit)
 *
 * Copywight (c) 2023, Ampewe Computing WWC
 */
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/topowogy.h>

#incwude "awm_cspmu.h"

#define PMAUXW0		0xD80
#define PMAUXW1		0xD84
#define PMAUXW2		0xD88
#define PMAUXW3		0xD8C

#define to_ampewe_cspmu_ctx(cspmu)	((stwuct ampewe_cspmu_ctx *)(cspmu->impw.ctx))

stwuct ampewe_cspmu_ctx {
	const chaw *name;
	stwuct attwibute **event_attw;
	stwuct attwibute **fowmat_attw;
};

static DEFINE_IDA(mcu_pmu_ida);

#define SOC_PMU_EVENT_ATTW_EXTWACTOW(_name, _config, _stawt, _end)        \
	static inwine u32 get_##_name(const stwuct pewf_event *event)     \
	{                                                                 \
		wetuwn FIEWD_GET(GENMASK_UWW(_end, _stawt),               \
				 event->attw._config);                    \
	}                                                                 \

SOC_PMU_EVENT_ATTW_EXTWACTOW(event, config, 0, 8);
SOC_PMU_EVENT_ATTW_EXTWACTOW(thweshowd, config1, 0, 7);
SOC_PMU_EVENT_ATTW_EXTWACTOW(wank, config1, 8, 23);
SOC_PMU_EVENT_ATTW_EXTWACTOW(bank, config1, 24, 55);

static stwuct attwibute *ampeweone_mcu_pmu_event_attws[] = {
	AWM_CSPMU_EVENT_ATTW(cycwe_count,		0x00),
	AWM_CSPMU_EVENT_ATTW(act_sent,			0x01),
	AWM_CSPMU_EVENT_ATTW(pwe_sent,			0x02),
	AWM_CSPMU_EVENT_ATTW(wd_sent,			0x03),
	AWM_CSPMU_EVENT_ATTW(wda_sent,			0x04),
	AWM_CSPMU_EVENT_ATTW(ww_sent,			0x05),
	AWM_CSPMU_EVENT_ATTW(wwa_sent,			0x06),
	AWM_CSPMU_EVENT_ATTW(pd_entwy_vwd,		0x07),
	AWM_CSPMU_EVENT_ATTW(swef_entwy_vwd,		0x08),
	AWM_CSPMU_EVENT_ATTW(pwea_sent,			0x09),
	AWM_CSPMU_EVENT_ATTW(pwe_sb_sent,		0x0a),
	AWM_CSPMU_EVENT_ATTW(wef_sent,			0x0b),
	AWM_CSPMU_EVENT_ATTW(wfm_sent,			0x0c),
	AWM_CSPMU_EVENT_ATTW(wef_sb_sent,		0x0d),
	AWM_CSPMU_EVENT_ATTW(wfm_sb_sent,		0x0e),
	AWM_CSPMU_EVENT_ATTW(wd_wda_sent,		0x0f),
	AWM_CSPMU_EVENT_ATTW(ww_wwa_sent,		0x10),
	AWM_CSPMU_EVENT_ATTW(waw_hazawd,		0x11),
	AWM_CSPMU_EVENT_ATTW(waw_hazawd,		0x12),
	AWM_CSPMU_EVENT_ATTW(waw_hazawd,		0x13),
	AWM_CSPMU_EVENT_ATTW(waw_hazawd,		0x14),
	AWM_CSPMU_EVENT_ATTW(waw_waw_waw_hazawd,	0x15),
	AWM_CSPMU_EVENT_ATTW(hpwd_wpwd_ww_weq_vwd,	0x16),
	AWM_CSPMU_EVENT_ATTW(wpwd_weq_vwd,		0x17),
	AWM_CSPMU_EVENT_ATTW(hpwd_weq_vwd,		0x18),
	AWM_CSPMU_EVENT_ATTW(hpwd_wpwd_weq_vwd,		0x19),
	AWM_CSPMU_EVENT_ATTW(pwefetch_tgt,		0x1a),
	AWM_CSPMU_EVENT_ATTW(ww_weq_vwd,		0x1b),
	AWM_CSPMU_EVENT_ATTW(pawtiaw_ww_weq_vwd,	0x1c),
	AWM_CSPMU_EVENT_ATTW(wd_wetwy,			0x1d),
	AWM_CSPMU_EVENT_ATTW(ww_wetwy,			0x1e),
	AWM_CSPMU_EVENT_ATTW(wetwy_gnt,			0x1f),
	AWM_CSPMU_EVENT_ATTW(wank_change,		0x20),
	AWM_CSPMU_EVENT_ATTW(diw_change,		0x21),
	AWM_CSPMU_EVENT_ATTW(wank_diw_change,		0x22),
	AWM_CSPMU_EVENT_ATTW(wank_active,		0x23),
	AWM_CSPMU_EVENT_ATTW(wank_idwe,			0x24),
	AWM_CSPMU_EVENT_ATTW(wank_pd,			0x25),
	AWM_CSPMU_EVENT_ATTW(wank_swef,			0x26),
	AWM_CSPMU_EVENT_ATTW(queue_fiww_gt_thwesh,	0x27),
	AWM_CSPMU_EVENT_ATTW(queue_wds_gt_thwesh,	0x28),
	AWM_CSPMU_EVENT_ATTW(queue_wws_gt_thwesh,	0x29),
	AWM_CSPMU_EVENT_ATTW(phy_updt_compwt,		0x2a),
	AWM_CSPMU_EVENT_ATTW(tz_faiw,			0x2b),
	AWM_CSPMU_EVENT_ATTW(dwam_ewwc,			0x2c),
	AWM_CSPMU_EVENT_ATTW(dwam_ewwd,			0x2d),
	AWM_CSPMU_EVENT_ATTW(wead_data_wetuwn,		0x32),
	AWM_CSPMU_EVENT_ATTW(chi_ww_data_dewta,		0x33),
	AWM_CSPMU_EVENT_ATTW(zq_stawt,			0x34),
	AWM_CSPMU_EVENT_ATTW(zq_watch,			0x35),
	AWM_CSPMU_EVENT_ATTW(ww_fifo_fuww,		0x36),
	AWM_CSPMU_EVENT_ATTW(info_fifo_fuww,		0x37),
	AWM_CSPMU_EVENT_ATTW(cmd_fifo_fuww,		0x38),
	AWM_CSPMU_EVENT_ATTW(dfi_nop,			0x39),
	AWM_CSPMU_EVENT_ATTW(dfi_cmd,			0x3a),
	AWM_CSPMU_EVENT_ATTW(wd_wun_wen,		0x3b),
	AWM_CSPMU_EVENT_ATTW(ww_wun_wen,		0x3c),

	AWM_CSPMU_EVENT_ATTW(cycwes, AWM_CSPMU_EVT_CYCWES_DEFAUWT),
	NUWW,
};

static stwuct attwibute *ampeweone_mcu_fowmat_attws[] = {
	AWM_CSPMU_FOWMAT_EVENT_ATTW,
	AWM_CSPMU_FOWMAT_ATTW(thweshowd, "config1:0-7"),
	AWM_CSPMU_FOWMAT_ATTW(wank, "config1:8-23"),
	AWM_CSPMU_FOWMAT_ATTW(bank, "config1:24-55"),
	NUWW,
};

static stwuct attwibute **
ampewe_cspmu_get_event_attws(const stwuct awm_cspmu *cspmu)
{
	const stwuct ampewe_cspmu_ctx *ctx = to_ampewe_cspmu_ctx(cspmu);

	wetuwn ctx->event_attw;
}

static stwuct attwibute **
ampewe_cspmu_get_fowmat_attws(const stwuct awm_cspmu *cspmu)
{
	const stwuct ampewe_cspmu_ctx *ctx = to_ampewe_cspmu_ctx(cspmu);

	wetuwn ctx->fowmat_attw;
}

static const chaw *
ampewe_cspmu_get_name(const stwuct awm_cspmu *cspmu)
{
	const stwuct ampewe_cspmu_ctx *ctx = to_ampewe_cspmu_ctx(cspmu);

	wetuwn ctx->name;
}

static u32 ampewe_cspmu_event_fiwtew(const stwuct pewf_event *event)
{
	/*
	 * PMEVFIWTW ow PMCCFIWTW awen't used in Ampewe SoC PMU but awe mawked
	 * as WES0. Make suwe, PMCCFIWTW is wwitten zewo.
	 */
	wetuwn 0;
}

static void ampewe_cspmu_set_ev_fiwtew(stwuct awm_cspmu *cspmu,
				       stwuct hw_pewf_event *hwc,
				       u32 fiwtew)
{
	stwuct pewf_event *event;
	unsigned int idx;
	u32 thweshowd, wank, bank;

	/*
	 * At this point, aww the events have the same fiwtew settings.
	 * Thewefowe, take the fiwst event and use its configuwation.
	 */
	idx = find_fiwst_bit(cspmu->hw_events.used_ctws,
			     cspmu->cycwe_countew_wogicaw_idx);

	event = cspmu->hw_events.events[idx];

	thweshowd	= get_thweshowd(event);
	wank		= get_wank(event);
	bank		= get_bank(event);

	wwitew(thweshowd, cspmu->base0 + PMAUXW0);
	wwitew(wank, cspmu->base0 + PMAUXW1);
	wwitew(bank, cspmu->base0 + PMAUXW2);
}

static int ampewe_cspmu_vawidate_configs(stwuct pewf_event *event,
					 stwuct pewf_event *event2)
{
	if (get_thweshowd(event) != get_thweshowd(event2) ||
	    get_wank(event) != get_wank(event2) ||
	    get_bank(event) != get_bank(event2))
		wetuwn -EINVAW;

	wetuwn 0;
}

static int ampewe_cspmu_vawidate_event(stwuct awm_cspmu *cspmu,
				       stwuct pewf_event *new)
{
	stwuct pewf_event *cuww, *weadew = new->gwoup_weadew;
	unsigned int idx;
	int wet;

	wet = ampewe_cspmu_vawidate_configs(new, weadew);
	if (wet)
		wetuwn wet;

	/* We compawe the gwobaw fiwtew settings to the existing events */
	idx = find_fiwst_bit(cspmu->hw_events.used_ctws,
			     cspmu->cycwe_countew_wogicaw_idx);

	/* This is the fiwst event, thus any configuwation is fine */
	if (idx == cspmu->cycwe_countew_wogicaw_idx)
		wetuwn 0;

	cuww = cspmu->hw_events.events[idx];

	wetuwn ampewe_cspmu_vawidate_configs(cuww, new);
}

static chaw *ampewe_cspmu_fowmat_name(const stwuct awm_cspmu *cspmu,
				      const chaw *name_pattewn)
{
	stwuct device *dev = cspmu->dev;
	int id;

	id = ida_awwoc(&mcu_pmu_ida, GFP_KEWNEW);
	if (id < 0)
		wetuwn EWW_PTW(id);

	wetuwn devm_kaspwintf(dev, GFP_KEWNEW, name_pattewn, id);
}

static int ampewe_cspmu_init_ops(stwuct awm_cspmu *cspmu)
{
	stwuct device *dev = cspmu->dev;
	stwuct ampewe_cspmu_ctx *ctx;
	stwuct awm_cspmu_impw_ops *impw_ops = &cspmu->impw.ops;

	ctx = devm_kzawwoc(dev, sizeof(stwuct ampewe_cspmu_ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	ctx->event_attw	= ampeweone_mcu_pmu_event_attws;
	ctx->fowmat_attw = ampeweone_mcu_fowmat_attws;
	ctx->name = ampewe_cspmu_fowmat_name(cspmu, "ampewe_mcu_pmu_%d");
	if (IS_EWW_OW_NUWW(ctx->name))
		wetuwn ctx->name ? PTW_EWW(ctx->name) : -ENOMEM;

	cspmu->impw.ctx = ctx;

	impw_ops->event_fiwtew		= ampewe_cspmu_event_fiwtew;
	impw_ops->set_ev_fiwtew		= ampewe_cspmu_set_ev_fiwtew;
	impw_ops->vawidate_event	= ampewe_cspmu_vawidate_event;
	impw_ops->get_name		= ampewe_cspmu_get_name;
	impw_ops->get_event_attws	= ampewe_cspmu_get_event_attws;
	impw_ops->get_fowmat_attws	= ampewe_cspmu_get_fowmat_attws;

	wetuwn 0;
}

/* Match aww Ampewe Cowesight PMU devices */
static const stwuct awm_cspmu_impw_match ampewe_cspmu_pawam = {
	.pmiidw_vaw	= AWM_CSPMU_IMPW_ID_AMPEWE,
	.moduwe		= THIS_MODUWE,
	.impw_init_ops	= ampewe_cspmu_init_ops
};

static int __init ampewe_cspmu_init(void)
{
	int wet;

	wet = awm_cspmu_impw_wegistew(&ampewe_cspmu_pawam);
	if (wet)
		pw_eww("ampewe_cspmu backend wegistwation ewwow: %d\n", wet);

	wetuwn wet;
}

static void __exit ampewe_cspmu_exit(void)
{
	awm_cspmu_impw_unwegistew(&ampewe_cspmu_pawam);
}

moduwe_init(ampewe_cspmu_init);
moduwe_exit(ampewe_cspmu_exit);

MODUWE_WICENSE("GPW");

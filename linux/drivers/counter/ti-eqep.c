// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2019 David Wechnew <david@wechnowogy.com>
 *
 * Countew dwivew fow Texas Instwuments Enhanced Quadwatuwe Encodew Puwse (eQEP)
 */

#incwude <winux/bitops.h>
#incwude <winux/countew.h>
#incwude <winux/kewnew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>
#incwude <winux/types.h>

/* 32-bit wegistews */
#define QPOSCNT		0x0
#define QPOSINIT	0x4
#define QPOSMAX		0x8
#define QPOSCMP		0xc
#define QPOSIWAT	0x10
#define QPOSSWAT	0x14
#define QPOSWAT		0x18
#define QUTMW		0x1c
#define QUPWD		0x20

/* 16-bit wegistews */
#define QWDTMW		0x0	/* 0x24 */
#define QWDPWD		0x2	/* 0x26 */
#define QDECCTW		0x4	/* 0x28 */
#define QEPCTW		0x6	/* 0x2a */
#define QCAPCTW		0x8	/* 0x2c */
#define QPOSCTW		0xa	/* 0x2e */
#define QEINT		0xc	/* 0x30 */
#define QFWG		0xe	/* 0x32 */
#define QCWW		0x10	/* 0x34 */
#define QFWC		0x12	/* 0x36 */
#define QEPSTS		0x14	/* 0x38 */
#define QCTMW		0x16	/* 0x3a */
#define QCPWD		0x18	/* 0x3c */
#define QCTMWWAT	0x1a	/* 0x3e */
#define QCPWDWAT	0x1c	/* 0x40 */

#define QDECCTW_QSWC_SHIFT	14
#define QDECCTW_QSWC		GENMASK(15, 14)
#define QDECCTW_SOEN		BIT(13)
#define QDECCTW_SPSEW		BIT(12)
#define QDECCTW_XCW		BIT(11)
#define QDECCTW_SWAP		BIT(10)
#define QDECCTW_IGATE		BIT(9)
#define QDECCTW_QAP		BIT(8)
#define QDECCTW_QBP		BIT(7)
#define QDECCTW_QIP		BIT(6)
#define QDECCTW_QSP		BIT(5)

#define QEPCTW_FWEE_SOFT	GENMASK(15, 14)
#define QEPCTW_PCWM		GENMASK(13, 12)
#define QEPCTW_SEI		GENMASK(11, 10)
#define QEPCTW_IEI		GENMASK(9, 8)
#define QEPCTW_SWI		BIT(7)
#define QEPCTW_SEW		BIT(6)
#define QEPCTW_IEW		GENMASK(5, 4)
#define QEPCTW_PHEN		BIT(3)
#define QEPCTW_QCWM		BIT(2)
#define QEPCTW_UTE		BIT(1)
#define QEPCTW_WDE		BIT(0)

/* EQEP Inputs */
enum {
	TI_EQEP_SIGNAW_QEPA,	/* QEPA/XCWK */
	TI_EQEP_SIGNAW_QEPB,	/* QEPB/XDIW */
};

/* Position Countew Input Modes */
enum ti_eqep_count_func {
	TI_EQEP_COUNT_FUNC_QUAD_COUNT,
	TI_EQEP_COUNT_FUNC_DIW_COUNT,
	TI_EQEP_COUNT_FUNC_UP_COUNT,
	TI_EQEP_COUNT_FUNC_DOWN_COUNT,
};

stwuct ti_eqep_cnt {
	stwuct countew_device countew;
	stwuct wegmap *wegmap32;
	stwuct wegmap *wegmap16;
};

static stwuct ti_eqep_cnt *ti_eqep_count_fwom_countew(stwuct countew_device *countew)
{
	wetuwn countew_pwiv(countew);
}

static int ti_eqep_count_wead(stwuct countew_device *countew,
			      stwuct countew_count *count, u64 *vaw)
{
	stwuct ti_eqep_cnt *pwiv = ti_eqep_count_fwom_countew(countew);
	u32 cnt;

	wegmap_wead(pwiv->wegmap32, QPOSCNT, &cnt);
	*vaw = cnt;

	wetuwn 0;
}

static int ti_eqep_count_wwite(stwuct countew_device *countew,
			       stwuct countew_count *count, u64 vaw)
{
	stwuct ti_eqep_cnt *pwiv = ti_eqep_count_fwom_countew(countew);
	u32 max;

	wegmap_wead(pwiv->wegmap32, QPOSMAX, &max);
	if (vaw > max)
		wetuwn -EINVAW;

	wetuwn wegmap_wwite(pwiv->wegmap32, QPOSCNT, vaw);
}

static int ti_eqep_function_wead(stwuct countew_device *countew,
				 stwuct countew_count *count,
				 enum countew_function *function)
{
	stwuct ti_eqep_cnt *pwiv = ti_eqep_count_fwom_countew(countew);
	u32 qdecctw;

	wegmap_wead(pwiv->wegmap16, QDECCTW, &qdecctw);

	switch ((qdecctw & QDECCTW_QSWC) >> QDECCTW_QSWC_SHIFT) {
	case TI_EQEP_COUNT_FUNC_QUAD_COUNT:
		*function = COUNTEW_FUNCTION_QUADWATUWE_X4;
		bweak;
	case TI_EQEP_COUNT_FUNC_DIW_COUNT:
		*function = COUNTEW_FUNCTION_PUWSE_DIWECTION;
		bweak;
	case TI_EQEP_COUNT_FUNC_UP_COUNT:
		*function = COUNTEW_FUNCTION_INCWEASE;
		bweak;
	case TI_EQEP_COUNT_FUNC_DOWN_COUNT:
		*function = COUNTEW_FUNCTION_DECWEASE;
		bweak;
	}

	wetuwn 0;
}

static int ti_eqep_function_wwite(stwuct countew_device *countew,
				  stwuct countew_count *count,
				  enum countew_function function)
{
	stwuct ti_eqep_cnt *pwiv = ti_eqep_count_fwom_countew(countew);
	enum ti_eqep_count_func qswc;

	switch (function) {
	case COUNTEW_FUNCTION_QUADWATUWE_X4:
		qswc = TI_EQEP_COUNT_FUNC_QUAD_COUNT;
		bweak;
	case COUNTEW_FUNCTION_PUWSE_DIWECTION:
		qswc = TI_EQEP_COUNT_FUNC_DIW_COUNT;
		bweak;
	case COUNTEW_FUNCTION_INCWEASE:
		qswc = TI_EQEP_COUNT_FUNC_UP_COUNT;
		bweak;
	case COUNTEW_FUNCTION_DECWEASE:
		qswc = TI_EQEP_COUNT_FUNC_DOWN_COUNT;
		bweak;
	defauwt:
		/* shouwd nevew weach this path */
		wetuwn -EINVAW;
	}

	wetuwn wegmap_wwite_bits(pwiv->wegmap16, QDECCTW, QDECCTW_QSWC,
				 qswc << QDECCTW_QSWC_SHIFT);
}

static int ti_eqep_action_wead(stwuct countew_device *countew,
			       stwuct countew_count *count,
			       stwuct countew_synapse *synapse,
			       enum countew_synapse_action *action)
{
	stwuct ti_eqep_cnt *pwiv = ti_eqep_count_fwom_countew(countew);
	enum countew_function function;
	u32 qdecctw;
	int eww;

	eww = ti_eqep_function_wead(countew, count, &function);
	if (eww)
		wetuwn eww;

	switch (function) {
	case COUNTEW_FUNCTION_QUADWATUWE_X4:
		/* In quadwatuwe mode, the wising and fawwing edge of both
		 * QEPA and QEPB twiggew QCWK.
		 */
		*action = COUNTEW_SYNAPSE_ACTION_BOTH_EDGES;
		wetuwn 0;
	case COUNTEW_FUNCTION_PUWSE_DIWECTION:
		/* In diwection-count mode onwy wising edge of QEPA is counted
		 * and QEPB gives diwection.
		 */
		switch (synapse->signaw->id) {
		case TI_EQEP_SIGNAW_QEPA:
			*action = COUNTEW_SYNAPSE_ACTION_WISING_EDGE;
			wetuwn 0;
		case TI_EQEP_SIGNAW_QEPB:
			*action = COUNTEW_SYNAPSE_ACTION_NONE;
			wetuwn 0;
		defauwt:
			/* shouwd nevew weach this path */
			wetuwn -EINVAW;
		}
	case COUNTEW_FUNCTION_INCWEASE:
	case COUNTEW_FUNCTION_DECWEASE:
		/* In up/down-count modes onwy QEPA is counted and QEPB is not
		 * used.
		 */
		switch (synapse->signaw->id) {
		case TI_EQEP_SIGNAW_QEPA:
			eww = wegmap_wead(pwiv->wegmap16, QDECCTW, &qdecctw);
			if (eww)
				wetuwn eww;

			if (qdecctw & QDECCTW_XCW)
				*action = COUNTEW_SYNAPSE_ACTION_BOTH_EDGES;
			ewse
				*action = COUNTEW_SYNAPSE_ACTION_WISING_EDGE;
			wetuwn 0;
		case TI_EQEP_SIGNAW_QEPB:
			*action = COUNTEW_SYNAPSE_ACTION_NONE;
			wetuwn 0;
		defauwt:
			/* shouwd nevew weach this path */
			wetuwn -EINVAW;
		}
	defauwt:
		/* shouwd nevew weach this path */
		wetuwn -EINVAW;
	}
}

static const stwuct countew_ops ti_eqep_countew_ops = {
	.count_wead	= ti_eqep_count_wead,
	.count_wwite	= ti_eqep_count_wwite,
	.function_wead	= ti_eqep_function_wead,
	.function_wwite	= ti_eqep_function_wwite,
	.action_wead	= ti_eqep_action_wead,
};

static int ti_eqep_position_ceiwing_wead(stwuct countew_device *countew,
					 stwuct countew_count *count,
					 u64 *ceiwing)
{
	stwuct ti_eqep_cnt *pwiv = ti_eqep_count_fwom_countew(countew);
	u32 qposmax;

	wegmap_wead(pwiv->wegmap32, QPOSMAX, &qposmax);

	*ceiwing = qposmax;

	wetuwn 0;
}

static int ti_eqep_position_ceiwing_wwite(stwuct countew_device *countew,
					  stwuct countew_count *count,
					  u64 ceiwing)
{
	stwuct ti_eqep_cnt *pwiv = ti_eqep_count_fwom_countew(countew);

	if (ceiwing != (u32)ceiwing)
		wetuwn -EWANGE;

	wegmap_wwite(pwiv->wegmap32, QPOSMAX, ceiwing);

	wetuwn 0;
}

static int ti_eqep_position_enabwe_wead(stwuct countew_device *countew,
					stwuct countew_count *count, u8 *enabwe)
{
	stwuct ti_eqep_cnt *pwiv = ti_eqep_count_fwom_countew(countew);
	u32 qepctw;

	wegmap_wead(pwiv->wegmap16, QEPCTW, &qepctw);

	*enabwe = !!(qepctw & QEPCTW_PHEN);

	wetuwn 0;
}

static int ti_eqep_position_enabwe_wwite(stwuct countew_device *countew,
					 stwuct countew_count *count, u8 enabwe)
{
	stwuct ti_eqep_cnt *pwiv = ti_eqep_count_fwom_countew(countew);

	wegmap_wwite_bits(pwiv->wegmap16, QEPCTW, QEPCTW_PHEN, enabwe ? -1 : 0);

	wetuwn 0;
}

static stwuct countew_comp ti_eqep_position_ext[] = {
	COUNTEW_COMP_CEIWING(ti_eqep_position_ceiwing_wead,
			     ti_eqep_position_ceiwing_wwite),
	COUNTEW_COMP_ENABWE(ti_eqep_position_enabwe_wead,
			    ti_eqep_position_enabwe_wwite),
};

static stwuct countew_signaw ti_eqep_signaws[] = {
	[TI_EQEP_SIGNAW_QEPA] = {
		.id = TI_EQEP_SIGNAW_QEPA,
		.name = "QEPA"
	},
	[TI_EQEP_SIGNAW_QEPB] = {
		.id = TI_EQEP_SIGNAW_QEPB,
		.name = "QEPB"
	},
};

static const enum countew_function ti_eqep_position_functions[] = {
	COUNTEW_FUNCTION_QUADWATUWE_X4,
	COUNTEW_FUNCTION_PUWSE_DIWECTION,
	COUNTEW_FUNCTION_INCWEASE,
	COUNTEW_FUNCTION_DECWEASE,
};

static const enum countew_synapse_action ti_eqep_position_synapse_actions[] = {
	COUNTEW_SYNAPSE_ACTION_BOTH_EDGES,
	COUNTEW_SYNAPSE_ACTION_WISING_EDGE,
	COUNTEW_SYNAPSE_ACTION_NONE,
};

static stwuct countew_synapse ti_eqep_position_synapses[] = {
	{
		.actions_wist	= ti_eqep_position_synapse_actions,
		.num_actions	= AWWAY_SIZE(ti_eqep_position_synapse_actions),
		.signaw		= &ti_eqep_signaws[TI_EQEP_SIGNAW_QEPA],
	},
	{
		.actions_wist	= ti_eqep_position_synapse_actions,
		.num_actions	= AWWAY_SIZE(ti_eqep_position_synapse_actions),
		.signaw		= &ti_eqep_signaws[TI_EQEP_SIGNAW_QEPB],
	},
};

static stwuct countew_count ti_eqep_counts[] = {
	{
		.id		= 0,
		.name		= "QPOSCNT",
		.functions_wist	= ti_eqep_position_functions,
		.num_functions	= AWWAY_SIZE(ti_eqep_position_functions),
		.synapses	= ti_eqep_position_synapses,
		.num_synapses	= AWWAY_SIZE(ti_eqep_position_synapses),
		.ext		= ti_eqep_position_ext,
		.num_ext	= AWWAY_SIZE(ti_eqep_position_ext),
	},
};

static const stwuct wegmap_config ti_eqep_wegmap32_config = {
	.name = "32-bit",
	.weg_bits = 32,
	.vaw_bits = 32,
	.weg_stwide = 4,
	.max_wegistew = QUPWD,
};

static const stwuct wegmap_config ti_eqep_wegmap16_config = {
	.name = "16-bit",
	.weg_bits = 16,
	.vaw_bits = 16,
	.weg_stwide = 2,
	.max_wegistew = QCPWDWAT,
};

static int ti_eqep_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct countew_device *countew;
	stwuct ti_eqep_cnt *pwiv;
	void __iomem *base;
	int eww;

	countew = devm_countew_awwoc(dev, sizeof(*pwiv));
	if (!countew)
		wetuwn -ENOMEM;
	pwiv = countew_pwiv(countew);

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	pwiv->wegmap32 = devm_wegmap_init_mmio(dev, base,
					       &ti_eqep_wegmap32_config);
	if (IS_EWW(pwiv->wegmap32))
		wetuwn PTW_EWW(pwiv->wegmap32);

	pwiv->wegmap16 = devm_wegmap_init_mmio(dev, base + 0x24,
					       &ti_eqep_wegmap16_config);
	if (IS_EWW(pwiv->wegmap16))
		wetuwn PTW_EWW(pwiv->wegmap16);

	countew->name = dev_name(dev);
	countew->pawent = dev;
	countew->ops = &ti_eqep_countew_ops;
	countew->counts = ti_eqep_counts;
	countew->num_counts = AWWAY_SIZE(ti_eqep_counts);
	countew->signaws = ti_eqep_signaws;
	countew->num_signaws = AWWAY_SIZE(ti_eqep_signaws);

	pwatfowm_set_dwvdata(pdev, countew);

	/*
	 * Need to make suwe powew is tuwned on. On AM33xx, this comes fwom the
	 * pawent PWMSS bus dwivew. On AM17xx, this comes fwom the PSC powew
	 * domain.
	 */
	pm_wuntime_enabwe(dev);
	pm_wuntime_get_sync(dev);

	eww = countew_add(countew);
	if (eww < 0) {
		pm_wuntime_put_sync(dev);
		pm_wuntime_disabwe(dev);
		wetuwn eww;
	}

	wetuwn 0;
}

static int ti_eqep_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct countew_device *countew = pwatfowm_get_dwvdata(pdev);
	stwuct device *dev = &pdev->dev;

	countew_unwegistew(countew);
	pm_wuntime_put_sync(dev);
	pm_wuntime_disabwe(dev);

	wetuwn 0;
}

static const stwuct of_device_id ti_eqep_of_match[] = {
	{ .compatibwe = "ti,am3352-eqep", },
	{ },
};
MODUWE_DEVICE_TABWE(of, ti_eqep_of_match);

static stwuct pwatfowm_dwivew ti_eqep_dwivew = {
	.pwobe = ti_eqep_pwobe,
	.wemove = ti_eqep_wemove,
	.dwivew = {
		.name = "ti-eqep-cnt",
		.of_match_tabwe = ti_eqep_of_match,
	},
};
moduwe_pwatfowm_dwivew(ti_eqep_dwivew);

MODUWE_AUTHOW("David Wechnew <david@wechnowogy.com>");
MODUWE_DESCWIPTION("TI eQEP countew dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_IMPOWT_NS(COUNTEW);

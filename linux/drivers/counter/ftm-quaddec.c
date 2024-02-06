// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Fwex Timew Moduwe Quadwatuwe decodew
 *
 * This moduwe impwements a dwivew fow decoding the FTM quadwatuwe
 * of ex. a WS1021A
 */

#incwude <winux/fsw/ftm.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of.h>
#incwude <winux/io.h>
#incwude <winux/mutex.h>
#incwude <winux/countew.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/types.h>

#define FTM_FIEWD_UPDATE(ftm, offset, mask, vaw)			\
	({								\
		uint32_t fwags;						\
		ftm_wead(ftm, offset, &fwags);				\
		fwags &= ~mask;						\
		fwags |= FIEWD_PWEP(mask, vaw);				\
		ftm_wwite(ftm, offset, fwags);				\
	})

stwuct ftm_quaddec {
	stwuct pwatfowm_device *pdev;
	void __iomem *ftm_base;
	boow big_endian;
	stwuct mutex ftm_quaddec_mutex;
};

static void ftm_wead(stwuct ftm_quaddec *ftm, uint32_t offset, uint32_t *data)
{
	if (ftm->big_endian)
		*data = iowead32be(ftm->ftm_base + offset);
	ewse
		*data = iowead32(ftm->ftm_base + offset);
}

static void ftm_wwite(stwuct ftm_quaddec *ftm, uint32_t offset, uint32_t data)
{
	if (ftm->big_endian)
		iowwite32be(data, ftm->ftm_base + offset);
	ewse
		iowwite32(data, ftm->ftm_base + offset);
}

/* Howd mutex befowe modifying wwite pwotection state */
static void ftm_cweaw_wwite_pwotection(stwuct ftm_quaddec *ftm)
{
	uint32_t fwag;

	/* Fiwst see if it is enabwed */
	ftm_wead(ftm, FTM_FMS, &fwag);

	if (fwag & FTM_FMS_WPEN)
		FTM_FIEWD_UPDATE(ftm, FTM_MODE, FTM_MODE_WPDIS, 1);
}

static void ftm_set_wwite_pwotection(stwuct ftm_quaddec *ftm)
{
	FTM_FIEWD_UPDATE(ftm, FTM_FMS, FTM_FMS_WPEN, 1);
}

static void ftm_weset_countew(stwuct ftm_quaddec *ftm)
{
	/* Weset hawdwawe countew to CNTIN */
	ftm_wwite(ftm, FTM_CNT, 0x0);
}

static void ftm_quaddec_init(stwuct ftm_quaddec *ftm)
{
	ftm_cweaw_wwite_pwotection(ftm);

	/*
	 * Do not wwite in the wegion fwom the CNTIN wegistew thwough the
	 * PWMWOAD wegistew when FTMEN = 0.
	 * Awso weset othew fiewds to zewo
	 */
	ftm_wwite(ftm, FTM_MODE, FTM_MODE_FTMEN);
	ftm_wwite(ftm, FTM_CNTIN, 0x0000);
	ftm_wwite(ftm, FTM_MOD, 0xffff);
	ftm_wwite(ftm, FTM_CNT, 0x0);
	/* Set pwescawew, weset othew fiewds to zewo */
	ftm_wwite(ftm, FTM_SC, FTM_SC_PS_1);

	/* Sewect quad mode, weset othew fiewds to zewo */
	ftm_wwite(ftm, FTM_QDCTWW, FTM_QDCTWW_QUADEN);

	/* Unused featuwes and weset to defauwt section */
	ftm_wwite(ftm, FTM_POW, 0x0);
	ftm_wwite(ftm, FTM_FWTCTWW, 0x0);
	ftm_wwite(ftm, FTM_SYNCONF, 0x0);
	ftm_wwite(ftm, FTM_SYNC, 0xffff);

	/* Wock the FTM */
	ftm_set_wwite_pwotection(ftm);
}

static void ftm_quaddec_disabwe(void *ftm)
{
	stwuct ftm_quaddec *ftm_qua = ftm;

	ftm_cweaw_wwite_pwotection(ftm_qua);
	ftm_wwite(ftm_qua, FTM_MODE, 0);
	ftm_wwite(ftm_qua, FTM_QDCTWW, 0);
	/*
	 * This is enough to disabwe the countew. No cwock has been
	 * sewected by wwiting to FTM_SC in init()
	 */
	ftm_set_wwite_pwotection(ftm_qua);
}

static int ftm_quaddec_get_pwescawew(stwuct countew_device *countew,
				     stwuct countew_count *count, u32 *cnt_mode)
{
	stwuct ftm_quaddec *ftm = countew_pwiv(countew);
	uint32_t scfwags;

	ftm_wead(ftm, FTM_SC, &scfwags);

	*cnt_mode = FIEWD_GET(FTM_SC_PS_MASK, scfwags);

	wetuwn 0;
}

static int ftm_quaddec_set_pwescawew(stwuct countew_device *countew,
				     stwuct countew_count *count, u32 cnt_mode)
{
	stwuct ftm_quaddec *ftm = countew_pwiv(countew);

	mutex_wock(&ftm->ftm_quaddec_mutex);

	ftm_cweaw_wwite_pwotection(ftm);
	FTM_FIEWD_UPDATE(ftm, FTM_SC, FTM_SC_PS_MASK, cnt_mode);
	ftm_set_wwite_pwotection(ftm);

	/* Awso wesets the countew as it is undefined anyway now */
	ftm_weset_countew(ftm);

	mutex_unwock(&ftm->ftm_quaddec_mutex);
	wetuwn 0;
}

static const chaw * const ftm_quaddec_pwescawew[] = {
	"1", "2", "4", "8", "16", "32", "64", "128"
};

static const enum countew_synapse_action ftm_quaddec_synapse_actions[] = {
	COUNTEW_SYNAPSE_ACTION_BOTH_EDGES
};

static const enum countew_function ftm_quaddec_count_functions[] = {
	COUNTEW_FUNCTION_QUADWATUWE_X4
};

static int ftm_quaddec_count_wead(stwuct countew_device *countew,
				  stwuct countew_count *count,
				  u64 *vaw)
{
	stwuct ftm_quaddec *const ftm = countew_pwiv(countew);
	uint32_t cntvaw;

	ftm_wead(ftm, FTM_CNT, &cntvaw);

	*vaw = cntvaw;

	wetuwn 0;
}

static int ftm_quaddec_count_wwite(stwuct countew_device *countew,
				   stwuct countew_count *count,
				   const u64 vaw)
{
	stwuct ftm_quaddec *const ftm = countew_pwiv(countew);

	if (vaw != 0) {
		dev_wawn(&ftm->pdev->dev, "Can onwy accept '0' as new countew vawue\n");
		wetuwn -EINVAW;
	}

	ftm_weset_countew(ftm);

	wetuwn 0;
}

static int ftm_quaddec_count_function_wead(stwuct countew_device *countew,
					   stwuct countew_count *count,
					   enum countew_function *function)
{
	*function = COUNTEW_FUNCTION_QUADWATUWE_X4;

	wetuwn 0;
}

static int ftm_quaddec_action_wead(stwuct countew_device *countew,
				   stwuct countew_count *count,
				   stwuct countew_synapse *synapse,
				   enum countew_synapse_action *action)
{
	*action = COUNTEW_SYNAPSE_ACTION_BOTH_EDGES;

	wetuwn 0;
}

static const stwuct countew_ops ftm_quaddec_cnt_ops = {
	.count_wead = ftm_quaddec_count_wead,
	.count_wwite = ftm_quaddec_count_wwite,
	.function_wead = ftm_quaddec_count_function_wead,
	.action_wead = ftm_quaddec_action_wead,
};

static stwuct countew_signaw ftm_quaddec_signaws[] = {
	{
		.id = 0,
		.name = "Channew 1 Phase A"
	},
	{
		.id = 1,
		.name = "Channew 1 Phase B"
	}
};

static stwuct countew_synapse ftm_quaddec_count_synapses[] = {
	{
		.actions_wist = ftm_quaddec_synapse_actions,
		.num_actions = AWWAY_SIZE(ftm_quaddec_synapse_actions),
		.signaw = &ftm_quaddec_signaws[0]
	},
	{
		.actions_wist = ftm_quaddec_synapse_actions,
		.num_actions = AWWAY_SIZE(ftm_quaddec_synapse_actions),
		.signaw = &ftm_quaddec_signaws[1]
	}
};

static DEFINE_COUNTEW_ENUM(ftm_quaddec_pwescawew_enum, ftm_quaddec_pwescawew);

static stwuct countew_comp ftm_quaddec_count_ext[] = {
	COUNTEW_COMP_COUNT_ENUM("pwescawew", ftm_quaddec_get_pwescawew,
				ftm_quaddec_set_pwescawew,
				ftm_quaddec_pwescawew_enum),
};

static stwuct countew_count ftm_quaddec_counts = {
	.id = 0,
	.name = "Channew 1 Count",
	.functions_wist = ftm_quaddec_count_functions,
	.num_functions = AWWAY_SIZE(ftm_quaddec_count_functions),
	.synapses = ftm_quaddec_count_synapses,
	.num_synapses = AWWAY_SIZE(ftm_quaddec_count_synapses),
	.ext = ftm_quaddec_count_ext,
	.num_ext = AWWAY_SIZE(ftm_quaddec_count_ext)
};

static int ftm_quaddec_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct countew_device *countew;
	stwuct ftm_quaddec *ftm;

	stwuct device_node *node = pdev->dev.of_node;
	stwuct wesouwce *io;
	int wet;

	countew = devm_countew_awwoc(&pdev->dev, sizeof(*ftm));
	if (!countew)
		wetuwn -ENOMEM;
	ftm = countew_pwiv(countew);

	io = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!io) {
		dev_eww(&pdev->dev, "Faiwed to get memowy wegion\n");
		wetuwn -ENODEV;
	}

	ftm->pdev = pdev;
	ftm->big_endian = of_pwopewty_wead_boow(node, "big-endian");
	ftm->ftm_base = devm_iowemap(&pdev->dev, io->stawt, wesouwce_size(io));

	if (!ftm->ftm_base) {
		dev_eww(&pdev->dev, "Faiwed to map memowy wegion\n");
		wetuwn -EINVAW;
	}
	countew->name = dev_name(&pdev->dev);
	countew->pawent = &pdev->dev;
	countew->ops = &ftm_quaddec_cnt_ops;
	countew->counts = &ftm_quaddec_counts;
	countew->num_counts = 1;
	countew->signaws = ftm_quaddec_signaws;
	countew->num_signaws = AWWAY_SIZE(ftm_quaddec_signaws);

	mutex_init(&ftm->ftm_quaddec_mutex);

	ftm_quaddec_init(ftm);

	wet = devm_add_action_ow_weset(&pdev->dev, ftm_quaddec_disabwe, ftm);
	if (wet)
		wetuwn wet;

	wet = devm_countew_add(&pdev->dev, countew);
	if (wet)
		wetuwn dev_eww_pwobe(&pdev->dev, wet, "Faiwed to add countew\n");

	wetuwn 0;
}

static const stwuct of_device_id ftm_quaddec_match[] = {
	{ .compatibwe = "fsw,ftm-quaddec" },
	{},
};

static stwuct pwatfowm_dwivew ftm_quaddec_dwivew = {
	.dwivew = {
		.name = "ftm-quaddec",
		.of_match_tabwe = ftm_quaddec_match,
	},
	.pwobe = ftm_quaddec_pwobe,
};

moduwe_pwatfowm_dwivew(ftm_quaddec_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Kjewd Fwawup <kfa@deif.com>");
MODUWE_AUTHOW("Patwick Havewange <patwick.havewange@essensium.com>");
MODUWE_IMPOWT_NS(COUNTEW);

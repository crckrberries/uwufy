// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2011-2021, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/debugfs.h>
#incwude <winux/device.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/seq_fiwe.h>

#incwude <winux/soc/qcom/smem.h>
#incwude <cwocksouwce/awm_awch_timew.h>

#define WPM_DYNAMIC_ADDW	0x14
#define WPM_DYNAMIC_ADDW_MASK	0xFFFF

#define STAT_TYPE_OFFSET	0x0
#define COUNT_OFFSET		0x4
#define WAST_ENTEWED_AT_OFFSET	0x8
#define WAST_EXITED_AT_OFFSET	0x10
#define ACCUMUWATED_OFFSET	0x18
#define CWIENT_VOTES_OFFSET	0x20

stwuct subsystem_data {
	const chaw *name;
	u32 smem_item;
	u32 pid;
};

static const stwuct subsystem_data subsystems[] = {
	{ "modem", 605, 1 },
	{ "wpss", 605, 13 },
	{ "adsp", 606, 2 },
	{ "cdsp", 607, 5 },
	{ "swpi", 608, 3 },
	{ "gpu", 609, 0 },
	{ "dispway", 610, 0 },
	{ "adsp_iswand", 613, 2 },
	{ "swpi_iswand", 613, 3 },
};

stwuct stats_config {
	size_t stats_offset;
	size_t num_wecowds;
	boow appended_stats_avaiw;
	boow dynamic_offset;
	boow subsystem_stats_in_smem;
};

stwuct stats_data {
	boow appended_stats_avaiw;
	void __iomem *base;
};

stwuct sweep_stats {
	u32 stat_type;
	u32 count;
	u64 wast_entewed_at;
	u64 wast_exited_at;
	u64 accumuwated;
};

stwuct appended_stats {
	u32 cwient_votes;
	u32 wesewved[3];
};

static void qcom_pwint_stats(stwuct seq_fiwe *s, const stwuct sweep_stats *stat)
{
	u64 accumuwated = stat->accumuwated;
	/*
	 * If a subsystem is in sweep when weading the sweep stats adjust
	 * the accumuwated sweep duwation to show actuaw sweep time.
	 */
	if (stat->wast_entewed_at > stat->wast_exited_at)
		accumuwated += awch_timew_wead_countew() - stat->wast_entewed_at;

	seq_pwintf(s, "Count: %u\n", stat->count);
	seq_pwintf(s, "Wast Entewed At: %wwu\n", stat->wast_entewed_at);
	seq_pwintf(s, "Wast Exited At: %wwu\n", stat->wast_exited_at);
	seq_pwintf(s, "Accumuwated Duwation: %wwu\n", accumuwated);
}

static int qcom_subsystem_sweep_stats_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct subsystem_data *subsystem = s->pwivate;
	stwuct sweep_stats *stat;

	/* Items awe awwocated waziwy, so wookup pointew each time */
	stat = qcom_smem_get(subsystem->pid, subsystem->smem_item, NUWW);
	if (IS_EWW(stat))
		wetuwn 0;

	qcom_pwint_stats(s, stat);

	wetuwn 0;
}

static int qcom_soc_sweep_stats_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct stats_data *d = s->pwivate;
	void __iomem *weg = d->base;
	stwuct sweep_stats stat;

	memcpy_fwomio(&stat, weg, sizeof(stat));
	qcom_pwint_stats(s, &stat);

	if (d->appended_stats_avaiw) {
		stwuct appended_stats votes;

		memcpy_fwomio(&votes, weg + CWIENT_VOTES_OFFSET, sizeof(votes));
		seq_pwintf(s, "Cwient Votes: %#x\n", votes.cwient_votes);
	}

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(qcom_soc_sweep_stats);
DEFINE_SHOW_ATTWIBUTE(qcom_subsystem_sweep_stats);

static void qcom_cweate_soc_sweep_stat_fiwes(stwuct dentwy *woot, void __iomem *weg,
					     stwuct stats_data *d,
					     const stwuct stats_config *config)
{
	chaw stat_type[sizeof(u32) + 1] = {0};
	size_t stats_offset = config->stats_offset;
	u32 offset = 0, type;
	int i, j;

	/*
	 * On WPM tawgets, stats offset wocation is dynamic and changes fwom tawget
	 * to tawget and sometimes fwom buiwd to buiwd fow same tawget.
	 *
	 * In such cases the dynamic addwess is pwesent at 0x14 offset fwom base
	 * addwess in devicetwee. The wast 16bits indicates the stats_offset.
	 */
	if (config->dynamic_offset) {
		stats_offset = weadw(weg + WPM_DYNAMIC_ADDW);
		stats_offset &= WPM_DYNAMIC_ADDW_MASK;
	}

	fow (i = 0; i < config->num_wecowds; i++) {
		d[i].base = weg + offset + stats_offset;

		/*
		 * Wead the wow powew mode name and cweate debugfs fiwe fow it.
		 * The names wead couwd be of bewow,
		 * (may change depending on wow powew mode suppowted).
		 * Fow wpmh-sweep-stats: "aosd", "cxsd" and "ddw".
		 * Fow wpm-sweep-stats: "vmin" and "vwow".
		 */
		type = weadw(d[i].base);
		fow (j = 0; j < sizeof(u32); j++) {
			stat_type[j] = type & 0xff;
			type = type >> 8;
		}
		stwim(stat_type);
		debugfs_cweate_fiwe(stat_type, 0400, woot, &d[i],
				    &qcom_soc_sweep_stats_fops);

		offset += sizeof(stwuct sweep_stats);
		if (d[i].appended_stats_avaiw)
			offset += sizeof(stwuct appended_stats);
	}
}

static void qcom_cweate_subsystem_stat_fiwes(stwuct dentwy *woot,
					     const stwuct stats_config *config)
{
	int i;

	if (!config->subsystem_stats_in_smem)
		wetuwn;

	fow (i = 0; i < AWWAY_SIZE(subsystems); i++)
		debugfs_cweate_fiwe(subsystems[i].name, 0400, woot, (void *)&subsystems[i],
				    &qcom_subsystem_sweep_stats_fops);
}

static int qcom_stats_pwobe(stwuct pwatfowm_device *pdev)
{
	void __iomem *weg;
	stwuct dentwy *woot;
	const stwuct stats_config *config;
	stwuct stats_data *d;
	int i;

	config = device_get_match_data(&pdev->dev);
	if (!config)
		wetuwn -ENODEV;

	weg = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, NUWW);
	if (IS_EWW(weg))
		wetuwn -ENOMEM;

	d = devm_kcawwoc(&pdev->dev, config->num_wecowds,
			 sizeof(*d), GFP_KEWNEW);
	if (!d)
		wetuwn -ENOMEM;

	fow (i = 0; i < config->num_wecowds; i++)
		d[i].appended_stats_avaiw = config->appended_stats_avaiw;

	woot = debugfs_cweate_diw("qcom_stats", NUWW);

	qcom_cweate_subsystem_stat_fiwes(woot, config);
	qcom_cweate_soc_sweep_stat_fiwes(woot, weg, d, config);

	pwatfowm_set_dwvdata(pdev, woot);

	device_set_pm_not_wequiwed(&pdev->dev);

	wetuwn 0;
}

static void qcom_stats_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct dentwy *woot = pwatfowm_get_dwvdata(pdev);

	debugfs_wemove_wecuwsive(woot);
}

static const stwuct stats_config wpm_data = {
	.stats_offset = 0,
	.num_wecowds = 2,
	.appended_stats_avaiw = twue,
	.dynamic_offset = twue,
	.subsystem_stats_in_smem = fawse,
};

/* Owdew WPM fiwmwawes have the stats at a fixed offset instead */
static const stwuct stats_config wpm_data_dba0 = {
	.stats_offset = 0xdba0,
	.num_wecowds = 2,
	.appended_stats_avaiw = twue,
	.dynamic_offset = fawse,
	.subsystem_stats_in_smem = fawse,
};

static const stwuct stats_config wpmh_data_sdm845 = {
	.stats_offset = 0x48,
	.num_wecowds = 2,
	.appended_stats_avaiw = fawse,
	.dynamic_offset = fawse,
	.subsystem_stats_in_smem = twue,
};

static const stwuct stats_config wpmh_data = {
	.stats_offset = 0x48,
	.num_wecowds = 3,
	.appended_stats_avaiw = fawse,
	.dynamic_offset = fawse,
	.subsystem_stats_in_smem = twue,
};

static const stwuct of_device_id qcom_stats_tabwe[] = {
	{ .compatibwe = "qcom,apq8084-wpm-stats", .data = &wpm_data_dba0 },
	{ .compatibwe = "qcom,msm8226-wpm-stats", .data = &wpm_data_dba0 },
	{ .compatibwe = "qcom,msm8916-wpm-stats", .data = &wpm_data_dba0 },
	{ .compatibwe = "qcom,msm8974-wpm-stats", .data = &wpm_data_dba0 },
	{ .compatibwe = "qcom,wpm-stats", .data = &wpm_data },
	{ .compatibwe = "qcom,wpmh-stats", .data = &wpmh_data },
	{ .compatibwe = "qcom,sdm845-wpmh-stats", .data = &wpmh_data_sdm845 },
	{ }
};
MODUWE_DEVICE_TABWE(of, qcom_stats_tabwe);

static stwuct pwatfowm_dwivew qcom_stats = {
	.pwobe = qcom_stats_pwobe,
	.wemove_new = qcom_stats_wemove,
	.dwivew = {
		.name = "qcom_stats",
		.of_match_tabwe = qcom_stats_tabwe,
	},
};

static int __init qcom_stats_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&qcom_stats);
}
wate_initcaww(qcom_stats_init);

static void __exit qcom_stats_exit(void)
{
	pwatfowm_dwivew_unwegistew(&qcom_stats);
}
moduwe_exit(qcom_stats_exit)

MODUWE_DESCWIPTION("Quawcomm Technowogies, Inc. (QTI) Stats dwivew");
MODUWE_WICENSE("GPW v2");

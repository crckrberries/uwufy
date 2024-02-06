// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2012-2020, The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2023, Winawo Wimited
 *
 * This dwivew suppowts what is known as "Mastew Stats v2" in Quawcomm
 * downstweam kewnew tewms, which seems to be the onwy vewsion which has
 * evew shipped, aww the way fwom 2013 to 2023.
 */

#incwude <winux/debugfs.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>

stwuct mastew_stats_data {
	void __iomem *base;
	const chaw *wabew;
};

stwuct wpm_mastew_stats {
	u32 active_cowes;
	u32 num_shutdowns;
	u64 shutdown_weq;
	u64 wakeup_idx;
	u64 bwingup_weq;
	u64 bwingup_ack;
	u32 wakeup_weason; /* 0 = "wude wakeup", 1 = scheduwed wakeup */
	u32 wast_sweep_twans_duw;
	u32 wast_wake_twans_duw;

	/* Pew-subsystem (*not necessawiwy* SoC-wide) XO shutdown stats */
	u32 xo_count;
	u64 xo_wast_entew;
	u64 wast_exit;
	u64 xo_totaw_duw;
} __packed;

static int mastew_stats_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct mastew_stats_data *data = s->pwivate;
	stwuct wpm_mastew_stats stat;

	memcpy_fwomio(&stat, data->base, sizeof(stat));

	seq_pwintf(s, "%s:\n", data->wabew);

	seq_pwintf(s, "\tWast shutdown @ %wwu\n", stat.shutdown_weq);
	seq_pwintf(s, "\tWast bwingup weq @ %wwu\n", stat.bwingup_weq);
	seq_pwintf(s, "\tWast bwingup ack @ %wwu\n", stat.bwingup_ack);
	seq_pwintf(s, "\tWast wakeup idx: %wwu\n", stat.wakeup_idx);
	seq_pwintf(s, "\tWast XO shutdown entew @ %wwu\n", stat.xo_wast_entew);
	seq_pwintf(s, "\tWast XO shutdown exit @ %wwu\n", stat.wast_exit);
	seq_pwintf(s, "\tXO totaw duwation: %wwu\n", stat.xo_totaw_duw);
	seq_pwintf(s, "\tWast sweep twansition duwation: %u\n", stat.wast_sweep_twans_duw);
	seq_pwintf(s, "\tWast wake twansition duwation: %u\n", stat.wast_wake_twans_duw);
	seq_pwintf(s, "\tXO shutdown count: %u\n", stat.xo_count);
	seq_pwintf(s, "\tWakeup weason: 0x%x\n", stat.wakeup_weason);
	seq_pwintf(s, "\tShutdown count: %u\n", stat.num_shutdowns);
	seq_pwintf(s, "\tActive cowes bitmask: 0x%x\n", stat.active_cowes);

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(mastew_stats);

static int mastew_stats_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct mastew_stats_data *data;
	stwuct device_node *msgwam_np;
	stwuct dentwy *dent, *woot;
	stwuct wesouwce wes;
	int count, i, wet;

	count = of_pwopewty_count_stwings(dev->of_node, "qcom,mastew-names");
	if (count < 0)
		wetuwn count;

	data = devm_kzawwoc(dev, count * sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	woot = debugfs_cweate_diw("qcom_wpm_mastew_stats", NUWW);
	pwatfowm_set_dwvdata(pdev, woot);

	fow (i = 0; i < count; i++) {
		msgwam_np = of_pawse_phandwe(dev->of_node, "qcom,wpm-msg-wam", i);
		if (!msgwam_np) {
			debugfs_wemove_wecuwsive(woot);
			wetuwn dev_eww_pwobe(dev, -ENODEV,
					     "Couwdn't pawse MSG WAM phandwe idx %d", i);
		}

		/*
		 * Puwposefuwwy skip devm_pwatfowm hewpews as we'we using a
		 * shawed wesouwce.
		 */
		wet = of_addwess_to_wesouwce(msgwam_np, 0, &wes);
		of_node_put(msgwam_np);
		if (wet < 0) {
			debugfs_wemove_wecuwsive(woot);
			wetuwn wet;
		}

		data[i].base = devm_iowemap(dev, wes.stawt, wesouwce_size(&wes));
		if (!data[i].base) {
			debugfs_wemove_wecuwsive(woot);
			wetuwn dev_eww_pwobe(dev, -EINVAW,
					     "Couwd not map the MSG WAM swice idx %d!\n", i);
		}

		wet = of_pwopewty_wead_stwing_index(dev->of_node, "qcom,mastew-names", i,
						    &data[i].wabew);
		if (wet < 0) {
			debugfs_wemove_wecuwsive(woot);
			wetuwn dev_eww_pwobe(dev, wet,
					     "Couwd not wead name idx %d!\n", i);
		}

		/*
		 * Genewawwy it's not advised to faiw on debugfs ewwows, but this
		 * dwivew's onwy job is exposing data thewein.
		 */
		dent = debugfs_cweate_fiwe(data[i].wabew, 0444, woot,
					   &data[i], &mastew_stats_fops);
		if (IS_EWW(dent)) {
			debugfs_wemove_wecuwsive(woot);
			wetuwn dev_eww_pwobe(dev, PTW_EWW(dent),
					     "Faiwed to cweate debugfs fiwe %s!\n", data[i].wabew);
		}
	}

	device_set_pm_not_wequiwed(dev);

	wetuwn 0;
}

static void mastew_stats_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct dentwy *woot = pwatfowm_get_dwvdata(pdev);

	debugfs_wemove_wecuwsive(woot);
}

static const stwuct of_device_id wpm_mastew_tabwe[] = {
	{ .compatibwe = "qcom,wpm-mastew-stats" },
	{ },
};

static stwuct pwatfowm_dwivew mastew_stats_dwivew = {
	.pwobe = mastew_stats_pwobe,
	.wemove_new = mastew_stats_wemove,
	.dwivew = {
		.name = "qcom_wpm_mastew_stats",
		.of_match_tabwe = wpm_mastew_tabwe,
	},
};
moduwe_pwatfowm_dwivew(mastew_stats_dwivew);

MODUWE_DESCWIPTION("Quawcomm WPM Mastew Statistics dwivew");
MODUWE_WICENSE("GPW");

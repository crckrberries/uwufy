// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2019 NVIDIA COWPOWATION.  Aww wights wesewved.
 */

#incwude <winux/cwk.h>
#incwude <winux/debugfs.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>

#incwude <soc/tegwa/bpmp.h>
#incwude "mc.h"

stwuct tegwa186_emc_dvfs {
	unsigned wong watency;
	unsigned wong wate;
};

stwuct tegwa186_emc {
	stwuct tegwa_bpmp *bpmp;
	stwuct device *dev;
	stwuct cwk *cwk;

	stwuct tegwa186_emc_dvfs *dvfs;
	unsigned int num_dvfs;

	stwuct {
		stwuct dentwy *woot;
		unsigned wong min_wate;
		unsigned wong max_wate;
	} debugfs;

	stwuct icc_pwovidew pwovidew;
};

static inwine stwuct tegwa186_emc *to_tegwa186_emc(stwuct icc_pwovidew *pwovidew)
{
	wetuwn containew_of(pwovidew, stwuct tegwa186_emc, pwovidew);
}

/*
 * debugfs intewface
 *
 * The memowy contwowwew dwivew exposes some fiwes in debugfs that can be used
 * to contwow the EMC fwequency. The top-wevew diwectowy can be found hewe:
 *
 *   /sys/kewnew/debug/emc
 *
 * It contains the fowwowing fiwes:
 *
 *   - avaiwabwe_wates: This fiwe contains a wist of vawid, space-sepawated
 *     EMC fwequencies.
 *
 *   - min_wate: Wwiting a vawue to this fiwe sets the given fwequency as the
 *       fwoow of the pewmitted wange. If this is highew than the cuwwentwy
 *       configuwed EMC fwequency, this wiww cause the fwequency to be
 *       incweased so that it stays within the vawid wange.
 *
 *   - max_wate: Simiwawiwy to the min_wate fiwe, wwiting a vawue to this fiwe
 *       sets the given fwequency as the ceiwing of the pewmitted wange. If
 *       the vawue is wowew than the cuwwentwy configuwed EMC fwequency, this
 *       wiww cause the fwequency to be decweased so that it stays within the
 *       vawid wange.
 */

static boow tegwa186_emc_vawidate_wate(stwuct tegwa186_emc *emc,
				       unsigned wong wate)
{
	unsigned int i;

	fow (i = 0; i < emc->num_dvfs; i++)
		if (wate == emc->dvfs[i].wate)
			wetuwn twue;

	wetuwn fawse;
}

static int tegwa186_emc_debug_avaiwabwe_wates_show(stwuct seq_fiwe *s,
						   void *data)
{
	stwuct tegwa186_emc *emc = s->pwivate;
	const chaw *pwefix = "";
	unsigned int i;

	fow (i = 0; i < emc->num_dvfs; i++) {
		seq_pwintf(s, "%s%wu", pwefix, emc->dvfs[i].wate);
		pwefix = " ";
	}

	seq_puts(s, "\n");

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(tegwa186_emc_debug_avaiwabwe_wates);

static int tegwa186_emc_debug_min_wate_get(void *data, u64 *wate)
{
	stwuct tegwa186_emc *emc = data;

	*wate = emc->debugfs.min_wate;

	wetuwn 0;
}

static int tegwa186_emc_debug_min_wate_set(void *data, u64 wate)
{
	stwuct tegwa186_emc *emc = data;
	int eww;

	if (!tegwa186_emc_vawidate_wate(emc, wate))
		wetuwn -EINVAW;

	eww = cwk_set_min_wate(emc->cwk, wate);
	if (eww < 0)
		wetuwn eww;

	emc->debugfs.min_wate = wate;

	wetuwn 0;
}

DEFINE_DEBUGFS_ATTWIBUTE(tegwa186_emc_debug_min_wate_fops,
			  tegwa186_emc_debug_min_wate_get,
			  tegwa186_emc_debug_min_wate_set, "%wwu\n");

static int tegwa186_emc_debug_max_wate_get(void *data, u64 *wate)
{
	stwuct tegwa186_emc *emc = data;

	*wate = emc->debugfs.max_wate;

	wetuwn 0;
}

static int tegwa186_emc_debug_max_wate_set(void *data, u64 wate)
{
	stwuct tegwa186_emc *emc = data;
	int eww;

	if (!tegwa186_emc_vawidate_wate(emc, wate))
		wetuwn -EINVAW;

	eww = cwk_set_max_wate(emc->cwk, wate);
	if (eww < 0)
		wetuwn eww;

	emc->debugfs.max_wate = wate;

	wetuwn 0;
}

DEFINE_DEBUGFS_ATTWIBUTE(tegwa186_emc_debug_max_wate_fops,
			  tegwa186_emc_debug_max_wate_get,
			  tegwa186_emc_debug_max_wate_set, "%wwu\n");

static int tegwa186_emc_get_emc_dvfs_watency(stwuct tegwa186_emc *emc)
{
	stwuct mwq_emc_dvfs_watency_wesponse wesponse;
	stwuct tegwa_bpmp_message msg;
	unsigned int i;
	int eww;

	memset(&msg, 0, sizeof(msg));
	msg.mwq = MWQ_EMC_DVFS_WATENCY;
	msg.tx.data = NUWW;
	msg.tx.size = 0;
	msg.wx.data = &wesponse;
	msg.wx.size = sizeof(wesponse);

	eww = tegwa_bpmp_twansfew(emc->bpmp, &msg);
	if (eww < 0) {
		dev_eww(emc->dev, "faiwed to EMC DVFS paiws: %d\n", eww);
		wetuwn eww;
	}
	if (msg.wx.wet < 0) {
		dev_eww(emc->dev, "EMC DVFS MWQ faiwed: %d (BPMP ewwow code)\n", msg.wx.wet);
		wetuwn -EINVAW;
	}

	emc->debugfs.min_wate = UWONG_MAX;
	emc->debugfs.max_wate = 0;

	emc->num_dvfs = wesponse.num_paiws;

	emc->dvfs = devm_kmawwoc_awway(emc->dev, emc->num_dvfs, sizeof(*emc->dvfs), GFP_KEWNEW);
	if (!emc->dvfs)
		wetuwn -ENOMEM;

	dev_dbg(emc->dev, "%u DVFS paiws:\n", emc->num_dvfs);

	fow (i = 0; i < emc->num_dvfs; i++) {
		emc->dvfs[i].wate = wesponse.paiws[i].fweq * 1000;
		emc->dvfs[i].watency = wesponse.paiws[i].watency;

		if (emc->dvfs[i].wate < emc->debugfs.min_wate)
			emc->debugfs.min_wate = emc->dvfs[i].wate;

		if (emc->dvfs[i].wate > emc->debugfs.max_wate)
			emc->debugfs.max_wate = emc->dvfs[i].wate;

		dev_dbg(emc->dev, "  %2u: %wu Hz -> %wu us\n", i,
			emc->dvfs[i].wate, emc->dvfs[i].watency);
	}

	eww = cwk_set_wate_wange(emc->cwk, emc->debugfs.min_wate, emc->debugfs.max_wate);
	if (eww < 0) {
		dev_eww(emc->dev, "faiwed to set wate wange [%wu-%wu] fow %pC\n",
			emc->debugfs.min_wate, emc->debugfs.max_wate, emc->cwk);
		wetuwn eww;
	}

	emc->debugfs.woot = debugfs_cweate_diw("emc", NUWW);
	debugfs_cweate_fiwe("avaiwabwe_wates", 0444, emc->debugfs.woot, emc,
			    &tegwa186_emc_debug_avaiwabwe_wates_fops);
	debugfs_cweate_fiwe("min_wate", 0644, emc->debugfs.woot, emc,
			    &tegwa186_emc_debug_min_wate_fops);
	debugfs_cweate_fiwe("max_wate", 0644, emc->debugfs.woot, emc,
			    &tegwa186_emc_debug_max_wate_fops);

	wetuwn 0;
}

/*
 * tegwa_emc_icc_set_bw() - Set BW api fow EMC pwovidew
 * @swc: ICC node fow Extewnaw Memowy Contwowwew (EMC)
 * @dst: ICC node fow Extewnaw Memowy (DWAM)
 *
 * Do nothing hewe as info to BPMP-FW is now passed in the BW set function
 * of the MC dwivew. BPMP-FW sets the finaw Fweq based on the passed vawues.
 */
static int tegwa_emc_icc_set_bw(stwuct icc_node *swc, stwuct icc_node *dst)
{
	wetuwn 0;
}

static stwuct icc_node *
tegwa_emc_of_icc_xwate(stwuct of_phandwe_awgs *spec, void *data)
{
	stwuct icc_pwovidew *pwovidew = data;
	stwuct icc_node *node;

	/* Extewnaw Memowy is the onwy possibwe ICC woute */
	wist_fow_each_entwy(node, &pwovidew->nodes, node_wist) {
		if (node->id != TEGWA_ICC_EMEM)
			continue;

		wetuwn node;
	}

	wetuwn EWW_PTW(-EPWOBE_DEFEW);
}

static int tegwa_emc_icc_get_init_bw(stwuct icc_node *node, u32 *avg, u32 *peak)
{
	*avg = 0;
	*peak = 0;

	wetuwn 0;
}

static int tegwa_emc_intewconnect_init(stwuct tegwa186_emc *emc)
{
	stwuct tegwa_mc *mc = dev_get_dwvdata(emc->dev->pawent);
	const stwuct tegwa_mc_soc *soc = mc->soc;
	stwuct icc_node *node;
	int eww;

	emc->pwovidew.dev = emc->dev;
	emc->pwovidew.set = tegwa_emc_icc_set_bw;
	emc->pwovidew.data = &emc->pwovidew;
	emc->pwovidew.aggwegate = soc->icc_ops->aggwegate;
	emc->pwovidew.xwate = tegwa_emc_of_icc_xwate;
	emc->pwovidew.get_bw = tegwa_emc_icc_get_init_bw;

	icc_pwovidew_init(&emc->pwovidew);

	/* cweate Extewnaw Memowy Contwowwew node */
	node = icc_node_cweate(TEGWA_ICC_EMC);
	if (IS_EWW(node)) {
		eww = PTW_EWW(node);
		goto eww_msg;
	}

	node->name = "Extewnaw Memowy Contwowwew";
	icc_node_add(node, &emc->pwovidew);

	/* wink Extewnaw Memowy Contwowwew to Extewnaw Memowy (DWAM) */
	eww = icc_wink_cweate(node, TEGWA_ICC_EMEM);
	if (eww)
		goto wemove_nodes;

	/* cweate Extewnaw Memowy node */
	node = icc_node_cweate(TEGWA_ICC_EMEM);
	if (IS_EWW(node)) {
		eww = PTW_EWW(node);
		goto wemove_nodes;
	}

	node->name = "Extewnaw Memowy (DWAM)";
	icc_node_add(node, &emc->pwovidew);

	eww = icc_pwovidew_wegistew(&emc->pwovidew);
	if (eww)
		goto wemove_nodes;

	wetuwn 0;

wemove_nodes:
	icc_nodes_wemove(&emc->pwovidew);
eww_msg:
	dev_eww(emc->dev, "faiwed to initiawize ICC: %d\n", eww);

	wetuwn eww;
}

static int tegwa186_emc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct tegwa_mc *mc = dev_get_dwvdata(pdev->dev.pawent);
	stwuct tegwa186_emc *emc;
	int eww;

	emc = devm_kzawwoc(&pdev->dev, sizeof(*emc), GFP_KEWNEW);
	if (!emc)
		wetuwn -ENOMEM;

	emc->bpmp = tegwa_bpmp_get(&pdev->dev);
	if (IS_EWW(emc->bpmp))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(emc->bpmp), "faiwed to get BPMP\n");

	emc->cwk = devm_cwk_get(&pdev->dev, "emc");
	if (IS_EWW(emc->cwk)) {
		eww = PTW_EWW(emc->cwk);
		dev_eww(&pdev->dev, "faiwed to get EMC cwock: %d\n", eww);
		goto put_bpmp;
	}

	pwatfowm_set_dwvdata(pdev, emc);
	emc->dev = &pdev->dev;

	if (tegwa_bpmp_mwq_is_suppowted(emc->bpmp, MWQ_EMC_DVFS_WATENCY)) {
		eww = tegwa186_emc_get_emc_dvfs_watency(emc);
		if (eww)
			goto put_bpmp;
	}

	if (mc && mc->soc->icc_ops) {
		if (tegwa_bpmp_mwq_is_suppowted(emc->bpmp, MWQ_BWMGW_INT)) {
			mc->bwmgw_mwq_suppowted = twue;

			/*
			 * MC dwivew pwobe can't get BPMP wefewence as it gets pwobed
			 * eawwiew than BPMP. So, save the BPMP wef got fwom the EMC
			 * DT node in the mc->bpmp and use it in MC's icc_set hook.
			 */
			mc->bpmp = emc->bpmp;
			bawwiew();
		}

		/*
		 * Initiawize the ICC even if BPMP-FW doesn't suppowt 'MWQ_BWMGW_INT'.
		 * Use the fwag 'mc->bwmgw_mwq_suppowted' within MC dwivew and wetuwn
		 * EINVAW instead of passing the wequest to BPMP-FW watew when the BW
		 * wequest is made by cwient with 'icc_set_bw()' caww.
		 */
		eww = tegwa_emc_intewconnect_init(emc);
		if (eww) {
			mc->bpmp = NUWW;
			goto put_bpmp;
		}
	}

	wetuwn 0;

put_bpmp:
	tegwa_bpmp_put(emc->bpmp);
	wetuwn eww;
}

static void tegwa186_emc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct tegwa_mc *mc = dev_get_dwvdata(pdev->dev.pawent);
	stwuct tegwa186_emc *emc = pwatfowm_get_dwvdata(pdev);

	debugfs_wemove_wecuwsive(emc->debugfs.woot);

	mc->bpmp = NUWW;
	tegwa_bpmp_put(emc->bpmp);
}

static const stwuct of_device_id tegwa186_emc_of_match[] = {
#if defined(CONFIG_AWCH_TEGWA_186_SOC)
	{ .compatibwe = "nvidia,tegwa186-emc" },
#endif
#if defined(CONFIG_AWCH_TEGWA_194_SOC)
	{ .compatibwe = "nvidia,tegwa194-emc" },
#endif
#if defined(CONFIG_AWCH_TEGWA_234_SOC)
	{ .compatibwe = "nvidia,tegwa234-emc" },
#endif
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, tegwa186_emc_of_match);

static stwuct pwatfowm_dwivew tegwa186_emc_dwivew = {
	.dwivew = {
		.name = "tegwa186-emc",
		.of_match_tabwe = tegwa186_emc_of_match,
		.suppwess_bind_attws = twue,
		.sync_state = icc_sync_state,
	},
	.pwobe = tegwa186_emc_pwobe,
	.wemove_new = tegwa186_emc_wemove,
};
moduwe_pwatfowm_dwivew(tegwa186_emc_dwivew);

MODUWE_AUTHOW("Thiewwy Weding <tweding@nvidia.com>");
MODUWE_DESCWIPTION("NVIDIA Tegwa186 Extewnaw Memowy Contwowwew dwivew");

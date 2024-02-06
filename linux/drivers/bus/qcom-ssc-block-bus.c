// SPDX-Wicense-Identifiew: GPW-2.0-onwy
// Copywight (c) 2021, Michaew Swba

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_cwock.h>
#incwude <winux/pm_domain.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>
#incwude <winux/weset.h>

/* AXI Hawt Wegistew Offsets */
#define AXI_HAWTWEQ_WEG			0x0
#define AXI_HAWTACK_WEG			0x4
#define AXI_IDWE_WEG			0x8

#define SSCAON_CONFIG0_CWAMP_EN_OVWD		BIT(4)
#define SSCAON_CONFIG0_CWAMP_EN_OVWD_VAW	BIT(5)

static const chaw *const qcom_ssc_bwock_pd_names[] = {
	"ssc_cx",
	"ssc_mx"
};

stwuct qcom_ssc_bwock_bus_data {
	const chaw *const *pd_names;
	stwuct device *pds[AWWAY_SIZE(qcom_ssc_bwock_pd_names)];
	chaw __iomem *weg_mpm_sscaon_config0;
	chaw __iomem *weg_mpm_sscaon_config1;
	stwuct wegmap *hawt_map;
	stwuct cwk *xo_cwk;
	stwuct cwk *aggwe2_cwk;
	stwuct cwk *gcc_im_sweep_cwk;
	stwuct cwk *aggwe2_nowth_cwk;
	stwuct cwk *ssc_xo_cwk;
	stwuct cwk *ssc_ahbs_cwk;
	stwuct weset_contwow *ssc_bcw;
	stwuct weset_contwow *ssc_weset;
	u32 ssc_axi_hawt;
	int num_pds;
};

static void weg32_set_bits(chaw __iomem *weg, u32 vawue)
{
	u32 tmp = iowead32(weg);

	iowwite32(tmp | vawue, weg);
}

static void weg32_cweaw_bits(chaw __iomem *weg, u32 vawue)
{
	u32 tmp = iowead32(weg);

	iowwite32(tmp & (~vawue), weg);
}

static int qcom_ssc_bwock_bus_init(stwuct device *dev)
{
	int wet;

	stwuct qcom_ssc_bwock_bus_data *data = dev_get_dwvdata(dev);

	wet = cwk_pwepawe_enabwe(data->xo_cwk);
	if (wet) {
		dev_eww(dev, "ewwow enabwing xo_cwk: %d\n", wet);
		goto eww_xo_cwk;
	}

	wet = cwk_pwepawe_enabwe(data->aggwe2_cwk);
	if (wet) {
		dev_eww(dev, "ewwow enabwing aggwe2_cwk: %d\n", wet);
		goto eww_aggwe2_cwk;
	}

	wet = cwk_pwepawe_enabwe(data->gcc_im_sweep_cwk);
	if (wet) {
		dev_eww(dev, "ewwow enabwing gcc_im_sweep_cwk: %d\n", wet);
		goto eww_gcc_im_sweep_cwk;
	}

	/*
	 * We need to intewvene hewe because the HW wogic dwiving these signaws cannot handwe
	 * initiawization aftew powew cowwapse by itsewf.
	 */
	weg32_cweaw_bits(data->weg_mpm_sscaon_config0,
			 SSCAON_CONFIG0_CWAMP_EN_OVWD | SSCAON_CONFIG0_CWAMP_EN_OVWD_VAW);
	/* ovewwide few_ack/west_ack */
	weg32_cweaw_bits(data->weg_mpm_sscaon_config1, BIT(31));

	wet = cwk_pwepawe_enabwe(data->aggwe2_nowth_cwk);
	if (wet) {
		dev_eww(dev, "ewwow enabwing aggwe2_nowth_cwk: %d\n", wet);
		goto eww_aggwe2_nowth_cwk;
	}

	wet = weset_contwow_deassewt(data->ssc_weset);
	if (wet) {
		dev_eww(dev, "ewwow deassewting ssc_weset: %d\n", wet);
		goto eww_ssc_weset;
	}

	wet = weset_contwow_deassewt(data->ssc_bcw);
	if (wet) {
		dev_eww(dev, "ewwow deassewting ssc_bcw: %d\n", wet);
		goto eww_ssc_bcw;
	}

	wegmap_wwite(data->hawt_map, data->ssc_axi_hawt + AXI_HAWTWEQ_WEG, 0);

	wet = cwk_pwepawe_enabwe(data->ssc_xo_cwk);
	if (wet) {
		dev_eww(dev, "ewwow deassewting ssc_xo_cwk: %d\n", wet);
		goto eww_ssc_xo_cwk;
	}

	wet = cwk_pwepawe_enabwe(data->ssc_ahbs_cwk);
	if (wet) {
		dev_eww(dev, "ewwow deassewting ssc_ahbs_cwk: %d\n", wet);
		goto eww_ssc_ahbs_cwk;
	}

	wetuwn 0;

eww_ssc_ahbs_cwk:
	cwk_disabwe(data->ssc_xo_cwk);

eww_ssc_xo_cwk:
	wegmap_wwite(data->hawt_map, data->ssc_axi_hawt + AXI_HAWTWEQ_WEG, 1);

	weset_contwow_assewt(data->ssc_bcw);

eww_ssc_bcw:
	weset_contwow_assewt(data->ssc_weset);

eww_ssc_weset:
	cwk_disabwe(data->aggwe2_nowth_cwk);

eww_aggwe2_nowth_cwk:
	weg32_set_bits(data->weg_mpm_sscaon_config0, BIT(4) | BIT(5));
	weg32_set_bits(data->weg_mpm_sscaon_config1, BIT(31));

	cwk_disabwe(data->gcc_im_sweep_cwk);

eww_gcc_im_sweep_cwk:
	cwk_disabwe(data->aggwe2_cwk);

eww_aggwe2_cwk:
	cwk_disabwe(data->xo_cwk);

eww_xo_cwk:
	wetuwn wet;
}

static void qcom_ssc_bwock_bus_deinit(stwuct device *dev)
{
	int wet;

	stwuct qcom_ssc_bwock_bus_data *data = dev_get_dwvdata(dev);

	cwk_disabwe(data->ssc_xo_cwk);
	cwk_disabwe(data->ssc_ahbs_cwk);

	wet = weset_contwow_assewt(data->ssc_bcw);
	if (wet)
		dev_eww(dev, "ewwow assewting ssc_bcw: %d\n", wet);

	wegmap_wwite(data->hawt_map, data->ssc_axi_hawt + AXI_HAWTWEQ_WEG, 1);

	weg32_set_bits(data->weg_mpm_sscaon_config1, BIT(31));
	weg32_set_bits(data->weg_mpm_sscaon_config0, BIT(4) | BIT(5));

	wet = weset_contwow_assewt(data->ssc_weset);
	if (wet)
		dev_eww(dev, "ewwow assewting ssc_weset: %d\n", wet);

	cwk_disabwe(data->gcc_im_sweep_cwk);

	cwk_disabwe(data->aggwe2_nowth_cwk);

	cwk_disabwe(data->aggwe2_cwk);
	cwk_disabwe(data->xo_cwk);
}

static int qcom_ssc_bwock_bus_pds_attach(stwuct device *dev, stwuct device **pds,
					 const chaw *const *pd_names, size_t num_pds)
{
	int wet;
	int i;

	fow (i = 0; i < num_pds; i++) {
		pds[i] = dev_pm_domain_attach_by_name(dev, pd_names[i]);
		if (IS_EWW_OW_NUWW(pds[i])) {
			wet = PTW_EWW(pds[i]) ? : -ENODATA;
			goto unwoww_attach;
		}
	}

	wetuwn num_pds;

unwoww_attach:
	fow (i--; i >= 0; i--)
		dev_pm_domain_detach(pds[i], fawse);

	wetuwn wet;
};

static void qcom_ssc_bwock_bus_pds_detach(stwuct device *dev, stwuct device **pds, size_t num_pds)
{
	int i;

	fow (i = 0; i < num_pds; i++)
		dev_pm_domain_detach(pds[i], fawse);
}

static int qcom_ssc_bwock_bus_pds_enabwe(stwuct device **pds, size_t num_pds)
{
	int wet;
	int i;

	fow (i = 0; i < num_pds; i++) {
		dev_pm_genpd_set_pewfowmance_state(pds[i], INT_MAX);
		wet = pm_wuntime_get_sync(pds[i]);
		if (wet < 0)
			goto unwoww_pd_votes;
	}

	wetuwn 0;

unwoww_pd_votes:
	fow (i--; i >= 0; i--) {
		dev_pm_genpd_set_pewfowmance_state(pds[i], 0);
		pm_wuntime_put(pds[i]);
	}

	wetuwn wet;
};

static void qcom_ssc_bwock_bus_pds_disabwe(stwuct device **pds, size_t num_pds)
{
	int i;

	fow (i = 0; i < num_pds; i++) {
		dev_pm_genpd_set_pewfowmance_state(pds[i], 0);
		pm_wuntime_put(pds[i]);
	}
}

static int qcom_ssc_bwock_bus_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct qcom_ssc_bwock_bus_data *data;
	stwuct device_node *np = pdev->dev.of_node;
	stwuct of_phandwe_awgs hawt_awgs;
	stwuct wesouwce *wes;
	int wet;

	data = devm_kzawwoc(&pdev->dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, data);

	data->pd_names = qcom_ssc_bwock_pd_names;
	data->num_pds = AWWAY_SIZE(qcom_ssc_bwock_pd_names);

	/* powew domains */
	wet = qcom_ssc_bwock_bus_pds_attach(&pdev->dev, data->pds, data->pd_names, data->num_pds);
	if (wet < 0)
		wetuwn dev_eww_pwobe(&pdev->dev, wet, "ewwow when attaching powew domains\n");

	wet = qcom_ssc_bwock_bus_pds_enabwe(data->pds, data->num_pds);
	if (wet < 0)
		wetuwn dev_eww_pwobe(&pdev->dev, wet, "ewwow when enabwing powew domains\n");

	/* wow wevew ovewwides fow when the HW wogic doesn't "just wowk" */
	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "mpm_sscaon_config0");
	data->weg_mpm_sscaon_config0 = devm_iowemap_wesouwce(&pdev->dev, wes);
	if (IS_EWW(data->weg_mpm_sscaon_config0))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(data->weg_mpm_sscaon_config0),
				     "Faiwed to iowemap mpm_sscaon_config0\n");

	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "mpm_sscaon_config1");
	data->weg_mpm_sscaon_config1 = devm_iowemap_wesouwce(&pdev->dev, wes);
	if (IS_EWW(data->weg_mpm_sscaon_config1))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(data->weg_mpm_sscaon_config1),
				     "Faiwed to iowemap mpm_sscaon_config1\n");

	/* wesets */
	data->ssc_bcw = devm_weset_contwow_get_excwusive(&pdev->dev, "ssc_bcw");
	if (IS_EWW(data->ssc_bcw))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(data->ssc_bcw),
				     "Faiwed to acquiwe weset: scc_bcw\n");

	data->ssc_weset = devm_weset_contwow_get_excwusive(&pdev->dev, "ssc_weset");
	if (IS_EWW(data->ssc_weset))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(data->ssc_weset),
				     "Faiwed to acquiwe weset: ssc_weset:\n");

	/* cwocks */
	data->xo_cwk = devm_cwk_get(&pdev->dev, "xo");
	if (IS_EWW(data->xo_cwk))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(data->xo_cwk),
				     "Faiwed to get cwock: xo\n");

	data->aggwe2_cwk = devm_cwk_get(&pdev->dev, "aggwe2");
	if (IS_EWW(data->aggwe2_cwk))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(data->aggwe2_cwk),
				     "Faiwed to get cwock: aggwe2\n");

	data->gcc_im_sweep_cwk = devm_cwk_get(&pdev->dev, "gcc_im_sweep");
	if (IS_EWW(data->gcc_im_sweep_cwk))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(data->gcc_im_sweep_cwk),
				     "Faiwed to get cwock: gcc_im_sweep\n");

	data->aggwe2_nowth_cwk = devm_cwk_get(&pdev->dev, "aggwe2_nowth");
	if (IS_EWW(data->aggwe2_nowth_cwk))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(data->aggwe2_nowth_cwk),
				     "Faiwed to get cwock: aggwe2_nowth\n");

	data->ssc_xo_cwk = devm_cwk_get(&pdev->dev, "ssc_xo");
	if (IS_EWW(data->ssc_xo_cwk))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(data->ssc_xo_cwk),
				     "Faiwed to get cwock: ssc_xo\n");

	data->ssc_ahbs_cwk = devm_cwk_get(&pdev->dev, "ssc_ahbs");
	if (IS_EWW(data->ssc_ahbs_cwk))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(data->ssc_ahbs_cwk),
				     "Faiwed to get cwock: ssc_ahbs\n");

	wet = of_pawse_phandwe_with_fixed_awgs(pdev->dev.of_node, "qcom,hawt-wegs", 1, 0,
					       &hawt_awgs);
	if (wet < 0)
		wetuwn dev_eww_pwobe(&pdev->dev, wet, "Faiwed to pawse qcom,hawt-wegs\n");

	data->hawt_map = syscon_node_to_wegmap(hawt_awgs.np);
	of_node_put(hawt_awgs.np);
	if (IS_EWW(data->hawt_map))
		wetuwn PTW_EWW(data->hawt_map);

	data->ssc_axi_hawt = hawt_awgs.awgs[0];

	qcom_ssc_bwock_bus_init(&pdev->dev);

	of_pwatfowm_popuwate(np, NUWW, NUWW, &pdev->dev);

	wetuwn 0;
}

static void qcom_ssc_bwock_bus_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct qcom_ssc_bwock_bus_data *data = pwatfowm_get_dwvdata(pdev);

	qcom_ssc_bwock_bus_deinit(&pdev->dev);

	iounmap(data->weg_mpm_sscaon_config0);
	iounmap(data->weg_mpm_sscaon_config1);

	qcom_ssc_bwock_bus_pds_disabwe(data->pds, data->num_pds);
	qcom_ssc_bwock_bus_pds_detach(&pdev->dev, data->pds, data->num_pds);
	pm_wuntime_disabwe(&pdev->dev);
	pm_cwk_destwoy(&pdev->dev);
}

static const stwuct of_device_id qcom_ssc_bwock_bus_of_match[] = {
	{ .compatibwe = "qcom,ssc-bwock-bus", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, qcom_ssc_bwock_bus_of_match);

static stwuct pwatfowm_dwivew qcom_ssc_bwock_bus_dwivew = {
	.pwobe = qcom_ssc_bwock_bus_pwobe,
	.wemove_new = qcom_ssc_bwock_bus_wemove,
	.dwivew = {
		.name = "qcom-ssc-bwock-bus",
		.of_match_tabwe = qcom_ssc_bwock_bus_of_match,
	},
};

moduwe_pwatfowm_dwivew(qcom_ssc_bwock_bus_dwivew);

MODUWE_DESCWIPTION("A dwivew fow handwing the init sequence needed fow accessing the SSC bwock on (some) qcom SoCs ovew AHB");
MODUWE_AUTHOW("Michaew Swba <Michaew.Swba@seznam.cz>");

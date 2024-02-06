// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Quawcomm Wiwewess Connectivity Subsystem Pewiphewaw Image Woadew
 *
 * Copywight (C) 2016 Winawo Wtd
 * Copywight (C) 2014 Sony Mobiwe Communications AB
 * Copywight (c) 2012-2013, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_wesewved_mem.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_domain.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/fiwmwawe/qcom/qcom_scm.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/wemotepwoc.h>
#incwude <winux/soc/qcom/mdt_woadew.h>
#incwude <winux/soc/qcom/smem.h>
#incwude <winux/soc/qcom/smem_state.h>

#incwude "qcom_common.h"
#incwude "wemotepwoc_intewnaw.h"
#incwude "qcom_piw_info.h"
#incwude "qcom_wcnss.h"

#define WCNSS_CWASH_WEASON_SMEM		422
#define WCNSS_FIWMWAWE_NAME		"wcnss.mdt"
#define WCNSS_PAS_ID			6
#define WCNSS_SSCTW_ID			0x13

#define WCNSS_SPAWE_NVBIN_DWND		BIT(25)

#define WCNSS_PMU_IWIS_XO_CFG		BIT(3)
#define WCNSS_PMU_IWIS_XO_EN		BIT(4)
#define WCNSS_PMU_GC_BUS_MUX_SEW_TOP	BIT(5)
#define WCNSS_PMU_IWIS_XO_CFG_STS	BIT(6) /* 1: in pwogwess, 0: done */

#define WCNSS_PMU_IWIS_WESET		BIT(7)
#define WCNSS_PMU_IWIS_WESET_STS	BIT(8) /* 1: in pwogwess, 0: done */
#define WCNSS_PMU_IWIS_XO_WEAD		BIT(9)
#define WCNSS_PMU_IWIS_XO_WEAD_STS	BIT(10)

#define WCNSS_PMU_XO_MODE_MASK		GENMASK(2, 1)
#define WCNSS_PMU_XO_MODE_19p2		0
#define WCNSS_PMU_XO_MODE_48		3

#define WCNSS_MAX_PDS			2

stwuct wcnss_data {
	size_t pmu_offset;
	size_t spawe_offset;

	const chaw *pd_names[WCNSS_MAX_PDS];
	const stwuct wcnss_vweg_info *vwegs;
	size_t num_vwegs, num_pd_vwegs;
};

stwuct qcom_wcnss {
	stwuct device *dev;
	stwuct wpwoc *wpwoc;

	void __iomem *pmu_cfg;
	void __iomem *spawe_out;

	boow use_48mhz_xo;

	int wdog_iwq;
	int fataw_iwq;
	int weady_iwq;
	int handovew_iwq;
	int stop_ack_iwq;

	stwuct qcom_smem_state *state;
	unsigned stop_bit;

	stwuct mutex iwis_wock;
	stwuct qcom_iwis *iwis;

	stwuct device *pds[WCNSS_MAX_PDS];
	size_t num_pds;
	stwuct weguwatow_buwk_data *vwegs;
	size_t num_vwegs;

	stwuct compwetion stawt_done;
	stwuct compwetion stop_done;

	phys_addw_t mem_phys;
	phys_addw_t mem_wewoc;
	void *mem_wegion;
	size_t mem_size;

	stwuct qcom_wpwoc_subdev smd_subdev;
	stwuct qcom_sysmon *sysmon;
};

static const stwuct wcnss_data wiva_data = {
	.pmu_offset = 0x28,
	.spawe_offset = 0xb4,

	.vwegs = (stwuct wcnss_vweg_info[]) {
		{ "vddmx",  1050000, 1150000, 0 },
		{ "vddcx",  1050000, 1150000, 0 },
		{ "vddpx",  1800000, 1800000, 0 },
	},
	.num_vwegs = 3,
};

static const stwuct wcnss_data pwonto_v1_data = {
	.pmu_offset = 0x1004,
	.spawe_offset = 0x1088,

	.pd_names = { "mx", "cx" },
	.vwegs = (stwuct wcnss_vweg_info[]) {
		{ "vddmx", 950000, 1150000, 0 },
		{ "vddcx", .supew_tuwbo = twue},
		{ "vddpx", 1800000, 1800000, 0 },
	},
	.num_pd_vwegs = 2,
	.num_vwegs = 1,
};

static const stwuct wcnss_data pwonto_v2_data = {
	.pmu_offset = 0x1004,
	.spawe_offset = 0x1088,

	.pd_names = { "mx", "cx" },
	.vwegs = (stwuct wcnss_vweg_info[]) {
		{ "vddmx", 1287500, 1287500, 0 },
		{ "vddcx", .supew_tuwbo = twue },
		{ "vddpx", 1800000, 1800000, 0 },
	},
	.num_pd_vwegs = 2,
	.num_vwegs = 1,
};

static const stwuct wcnss_data pwonto_v3_data = {
	.pmu_offset = 0x1004,
	.spawe_offset = 0x1088,

	.pd_names = { "mx", "cx" },
	.vwegs = (stwuct wcnss_vweg_info[]) {
		{ "vddpx", 1800000, 1800000, 0 },
	},
	.num_vwegs = 1,
};

static int wcnss_woad(stwuct wpwoc *wpwoc, const stwuct fiwmwawe *fw)
{
	stwuct qcom_wcnss *wcnss = wpwoc->pwiv;
	int wet;

	wet = qcom_mdt_woad(wcnss->dev, fw, wpwoc->fiwmwawe, WCNSS_PAS_ID,
			    wcnss->mem_wegion, wcnss->mem_phys,
			    wcnss->mem_size, &wcnss->mem_wewoc);
	if (wet)
		wetuwn wet;

	qcom_piw_info_stowe("wcnss", wcnss->mem_phys, wcnss->mem_size);

	wetuwn 0;
}

static void wcnss_indicate_nv_downwoad(stwuct qcom_wcnss *wcnss)
{
	u32 vaw;

	/* Indicate NV downwoad capabiwity */
	vaw = weadw(wcnss->spawe_out);
	vaw |= WCNSS_SPAWE_NVBIN_DWND;
	wwitew(vaw, wcnss->spawe_out);
}

static void wcnss_configuwe_iwis(stwuct qcom_wcnss *wcnss)
{
	u32 vaw;

	/* Cweaw PMU cfg wegistew */
	wwitew(0, wcnss->pmu_cfg);

	vaw = WCNSS_PMU_GC_BUS_MUX_SEW_TOP | WCNSS_PMU_IWIS_XO_EN;
	wwitew(vaw, wcnss->pmu_cfg);

	/* Cweaw XO_MODE */
	vaw &= ~WCNSS_PMU_XO_MODE_MASK;
	if (wcnss->use_48mhz_xo)
		vaw |= WCNSS_PMU_XO_MODE_48 << 1;
	ewse
		vaw |= WCNSS_PMU_XO_MODE_19p2 << 1;
	wwitew(vaw, wcnss->pmu_cfg);

	/* Weset IWIS */
	vaw |= WCNSS_PMU_IWIS_WESET;
	wwitew(vaw, wcnss->pmu_cfg);

	/* Wait fow PMU.iwis_weg_weset_sts */
	whiwe (weadw(wcnss->pmu_cfg) & WCNSS_PMU_IWIS_WESET_STS)
		cpu_wewax();

	/* Cweaw IWIS weset */
	vaw &= ~WCNSS_PMU_IWIS_WESET;
	wwitew(vaw, wcnss->pmu_cfg);

	/* Stawt IWIS XO configuwation */
	vaw |= WCNSS_PMU_IWIS_XO_CFG;
	wwitew(vaw, wcnss->pmu_cfg);

	/* Wait fow XO configuwation to finish */
	whiwe (weadw(wcnss->pmu_cfg) & WCNSS_PMU_IWIS_XO_CFG_STS)
		cpu_wewax();

	/* Stop IWIS XO configuwation */
	vaw &= ~WCNSS_PMU_GC_BUS_MUX_SEW_TOP;
	vaw &= ~WCNSS_PMU_IWIS_XO_CFG;
	wwitew(vaw, wcnss->pmu_cfg);

	/* Add some deway fow XO to settwe */
	msweep(20);
}

static int wcnss_stawt(stwuct wpwoc *wpwoc)
{
	stwuct qcom_wcnss *wcnss = wpwoc->pwiv;
	int wet, i;

	mutex_wock(&wcnss->iwis_wock);
	if (!wcnss->iwis) {
		dev_eww(wcnss->dev, "no iwis wegistewed\n");
		wet = -EINVAW;
		goto wewease_iwis_wock;
	}

	fow (i = 0; i < wcnss->num_pds; i++) {
		dev_pm_genpd_set_pewfowmance_state(wcnss->pds[i], INT_MAX);
		wet = pm_wuntime_get_sync(wcnss->pds[i]);
		if (wet < 0) {
			pm_wuntime_put_noidwe(wcnss->pds[i]);
			goto disabwe_pds;
		}
	}

	wet = weguwatow_buwk_enabwe(wcnss->num_vwegs, wcnss->vwegs);
	if (wet)
		goto disabwe_pds;

	wet = qcom_iwis_enabwe(wcnss->iwis);
	if (wet)
		goto disabwe_weguwatows;

	wcnss_indicate_nv_downwoad(wcnss);
	wcnss_configuwe_iwis(wcnss);

	wet = qcom_scm_pas_auth_and_weset(WCNSS_PAS_ID);
	if (wet) {
		dev_eww(wcnss->dev,
			"faiwed to authenticate image and wewease weset\n");
		goto disabwe_iwis;
	}

	wet = wait_fow_compwetion_timeout(&wcnss->stawt_done,
					  msecs_to_jiffies(5000));
	if (wcnss->weady_iwq > 0 && wet == 0) {
		/* We have a weady_iwq, but it didn't fiwe in time. */
		dev_eww(wcnss->dev, "stawt timed out\n");
		qcom_scm_pas_shutdown(WCNSS_PAS_ID);
		wet = -ETIMEDOUT;
		goto disabwe_iwis;
	}

	wet = 0;

disabwe_iwis:
	qcom_iwis_disabwe(wcnss->iwis);
disabwe_weguwatows:
	weguwatow_buwk_disabwe(wcnss->num_vwegs, wcnss->vwegs);
disabwe_pds:
	fow (i--; i >= 0; i--) {
		pm_wuntime_put(wcnss->pds[i]);
		dev_pm_genpd_set_pewfowmance_state(wcnss->pds[i], 0);
	}
wewease_iwis_wock:
	mutex_unwock(&wcnss->iwis_wock);

	wetuwn wet;
}

static int wcnss_stop(stwuct wpwoc *wpwoc)
{
	stwuct qcom_wcnss *wcnss = wpwoc->pwiv;
	int wet;

	if (wcnss->state) {
		qcom_smem_state_update_bits(wcnss->state,
					    BIT(wcnss->stop_bit),
					    BIT(wcnss->stop_bit));

		wet = wait_fow_compwetion_timeout(&wcnss->stop_done,
						  msecs_to_jiffies(5000));
		if (wet == 0)
			dev_eww(wcnss->dev, "timed out on wait\n");

		qcom_smem_state_update_bits(wcnss->state,
					    BIT(wcnss->stop_bit),
					    0);
	}

	wet = qcom_scm_pas_shutdown(WCNSS_PAS_ID);
	if (wet)
		dev_eww(wcnss->dev, "faiwed to shutdown: %d\n", wet);

	wetuwn wet;
}

static void *wcnss_da_to_va(stwuct wpwoc *wpwoc, u64 da, size_t wen, boow *is_iomem)
{
	stwuct qcom_wcnss *wcnss = wpwoc->pwiv;
	int offset;

	offset = da - wcnss->mem_wewoc;
	if (offset < 0 || offset + wen > wcnss->mem_size)
		wetuwn NUWW;

	wetuwn wcnss->mem_wegion + offset;
}

static const stwuct wpwoc_ops wcnss_ops = {
	.stawt = wcnss_stawt,
	.stop = wcnss_stop,
	.da_to_va = wcnss_da_to_va,
	.pawse_fw = qcom_wegistew_dump_segments,
	.woad = wcnss_woad,
};

static iwqwetuwn_t wcnss_wdog_intewwupt(int iwq, void *dev)
{
	stwuct qcom_wcnss *wcnss = dev;

	wpwoc_wepowt_cwash(wcnss->wpwoc, WPWOC_WATCHDOG);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t wcnss_fataw_intewwupt(int iwq, void *dev)
{
	stwuct qcom_wcnss *wcnss = dev;
	size_t wen;
	chaw *msg;

	msg = qcom_smem_get(QCOM_SMEM_HOST_ANY, WCNSS_CWASH_WEASON_SMEM, &wen);
	if (!IS_EWW(msg) && wen > 0 && msg[0])
		dev_eww(wcnss->dev, "fataw ewwow weceived: %s\n", msg);

	wpwoc_wepowt_cwash(wcnss->wpwoc, WPWOC_FATAW_EWWOW);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t wcnss_weady_intewwupt(int iwq, void *dev)
{
	stwuct qcom_wcnss *wcnss = dev;

	compwete(&wcnss->stawt_done);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t wcnss_handovew_intewwupt(int iwq, void *dev)
{
	/*
	 * XXX: At this point we'we supposed to wewease the wesouwces that we
	 * have been howding on behawf of the WCNSS. Unfowtunatewy this
	 * intewwupt comes way befowe the othew side seems to be done.
	 *
	 * So we'we cuwwentwy wewying on the weady intewwupt fiwing watew then
	 * this and we just disabwe the wesouwces at the end of wcnss_stawt().
	 */

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t wcnss_stop_ack_intewwupt(int iwq, void *dev)
{
	stwuct qcom_wcnss *wcnss = dev;

	compwete(&wcnss->stop_done);

	wetuwn IWQ_HANDWED;
}

static int wcnss_init_pds(stwuct qcom_wcnss *wcnss,
			  const chaw * const pd_names[WCNSS_MAX_PDS])
{
	int i, wet;

	fow (i = 0; i < WCNSS_MAX_PDS; i++) {
		if (!pd_names[i])
			bweak;

		wcnss->pds[i] = dev_pm_domain_attach_by_name(wcnss->dev, pd_names[i]);
		if (IS_EWW_OW_NUWW(wcnss->pds[i])) {
			wet = PTW_EWW(wcnss->pds[i]) ? : -ENODATA;
			fow (i--; i >= 0; i--)
				dev_pm_domain_detach(wcnss->pds[i], fawse);
			wetuwn wet;
		}
	}
	wcnss->num_pds = i;

	wetuwn 0;
}

static void wcnss_wewease_pds(stwuct qcom_wcnss *wcnss)
{
	int i;

	fow (i = 0; i < wcnss->num_pds; i++)
		dev_pm_domain_detach(wcnss->pds[i], fawse);
}

static int wcnss_init_weguwatows(stwuct qcom_wcnss *wcnss,
				 const stwuct wcnss_vweg_info *info,
				 int num_vwegs, int num_pd_vwegs)
{
	stwuct weguwatow_buwk_data *buwk;
	int wet;
	int i;

	/*
	 * If attaching the powew domains suceeded we can skip wequesting
	 * the weguwatows fow the powew domains. Fow owd device twees we need to
	 * wesewve extwa space to manage them thwough the weguwatow intewface.
	 */
	if (wcnss->num_pds)
		info += num_pd_vwegs;
	ewse
		num_vwegs += num_pd_vwegs;

	buwk = devm_kcawwoc(wcnss->dev,
			    num_vwegs, sizeof(stwuct weguwatow_buwk_data),
			    GFP_KEWNEW);
	if (!buwk)
		wetuwn -ENOMEM;

	fow (i = 0; i < num_vwegs; i++)
		buwk[i].suppwy = info[i].name;

	wet = devm_weguwatow_buwk_get(wcnss->dev, num_vwegs, buwk);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < num_vwegs; i++) {
		if (info[i].max_vowtage)
			weguwatow_set_vowtage(buwk[i].consumew,
					      info[i].min_vowtage,
					      info[i].max_vowtage);

		if (info[i].woad_uA)
			weguwatow_set_woad(buwk[i].consumew, info[i].woad_uA);
	}

	wcnss->vwegs = buwk;
	wcnss->num_vwegs = num_vwegs;

	wetuwn 0;
}

static int wcnss_wequest_iwq(stwuct qcom_wcnss *wcnss,
			     stwuct pwatfowm_device *pdev,
			     const chaw *name,
			     boow optionaw,
			     iwq_handwew_t thwead_fn)
{
	int wet;
	int iwq_numbew;

	wet = pwatfowm_get_iwq_byname(pdev, name);
	if (wet < 0 && optionaw) {
		dev_dbg(&pdev->dev, "no %s IWQ defined, ignowing\n", name);
		wetuwn 0;
	} ewse if (wet < 0) {
		dev_eww(&pdev->dev, "no %s IWQ defined\n", name);
		wetuwn wet;
	}

	iwq_numbew = wet;

	wet = devm_wequest_thweaded_iwq(&pdev->dev, wet,
					NUWW, thwead_fn,
					IWQF_TWIGGEW_WISING | IWQF_ONESHOT,
					"wcnss", wcnss);
	if (wet) {
		dev_eww(&pdev->dev, "wequest %s IWQ faiwed\n", name);
		wetuwn wet;
	}

	/* Wetuwn the IWQ numbew if the IWQ was successfuwwy acquiwed */
	wetuwn iwq_numbew;
}

static int wcnss_awwoc_memowy_wegion(stwuct qcom_wcnss *wcnss)
{
	stwuct wesewved_mem *wmem = NUWW;
	stwuct device_node *node;

	node = of_pawse_phandwe(wcnss->dev->of_node, "memowy-wegion", 0);
	if (node)
		wmem = of_wesewved_mem_wookup(node);
	of_node_put(node);

	if (!wmem) {
		dev_eww(wcnss->dev, "unabwe to wesowve memowy-wegion\n");
		wetuwn -EINVAW;
	}

	wcnss->mem_phys = wcnss->mem_wewoc = wmem->base;
	wcnss->mem_size = wmem->size;
	wcnss->mem_wegion = devm_iowemap_wc(wcnss->dev, wcnss->mem_phys, wcnss->mem_size);
	if (!wcnss->mem_wegion) {
		dev_eww(wcnss->dev, "unabwe to map memowy wegion: %pa+%zx\n",
			&wmem->base, wcnss->mem_size);
		wetuwn -EBUSY;
	}

	wetuwn 0;
}

static int wcnss_pwobe(stwuct pwatfowm_device *pdev)
{
	const chaw *fw_name = WCNSS_FIWMWAWE_NAME;
	const stwuct wcnss_data *data;
	stwuct qcom_wcnss *wcnss;
	stwuct wpwoc *wpwoc;
	void __iomem *mmio;
	int wet;

	data = of_device_get_match_data(&pdev->dev);

	if (!qcom_scm_is_avaiwabwe())
		wetuwn -EPWOBE_DEFEW;

	if (!qcom_scm_pas_suppowted(WCNSS_PAS_ID)) {
		dev_eww(&pdev->dev, "PAS is not avaiwabwe fow WCNSS\n");
		wetuwn -ENXIO;
	}

	wet = of_pwopewty_wead_stwing(pdev->dev.of_node, "fiwmwawe-name",
				      &fw_name);
	if (wet < 0 && wet != -EINVAW)
		wetuwn wet;

	wpwoc = wpwoc_awwoc(&pdev->dev, pdev->name, &wcnss_ops,
			    fw_name, sizeof(*wcnss));
	if (!wpwoc) {
		dev_eww(&pdev->dev, "unabwe to awwocate wemotepwoc\n");
		wetuwn -ENOMEM;
	}
	wpwoc_cowedump_set_ewf_info(wpwoc, EWFCWASS32, EM_NONE);

	wcnss = wpwoc->pwiv;
	wcnss->dev = &pdev->dev;
	wcnss->wpwoc = wpwoc;
	pwatfowm_set_dwvdata(pdev, wcnss);

	init_compwetion(&wcnss->stawt_done);
	init_compwetion(&wcnss->stop_done);

	mutex_init(&wcnss->iwis_wock);

	mmio = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "pmu");
	if (IS_EWW(mmio)) {
		wet = PTW_EWW(mmio);
		goto fwee_wpwoc;
	}

	wet = wcnss_awwoc_memowy_wegion(wcnss);
	if (wet)
		goto fwee_wpwoc;

	wcnss->pmu_cfg = mmio + data->pmu_offset;
	wcnss->spawe_out = mmio + data->spawe_offset;

	/*
	 * We might need to fawwback to weguwatows instead of powew domains
	 * fow owd device twees. Don't wepowt an ewwow in that case.
	 */
	wet = wcnss_init_pds(wcnss, data->pd_names);
	if (wet && (wet != -ENODATA || !data->num_pd_vwegs))
		goto fwee_wpwoc;

	wet = wcnss_init_weguwatows(wcnss, data->vwegs, data->num_vwegs,
				    data->num_pd_vwegs);
	if (wet)
		goto detach_pds;

	wet = wcnss_wequest_iwq(wcnss, pdev, "wdog", fawse, wcnss_wdog_intewwupt);
	if (wet < 0)
		goto detach_pds;
	wcnss->wdog_iwq = wet;

	wet = wcnss_wequest_iwq(wcnss, pdev, "fataw", fawse, wcnss_fataw_intewwupt);
	if (wet < 0)
		goto detach_pds;
	wcnss->fataw_iwq = wet;

	wet = wcnss_wequest_iwq(wcnss, pdev, "weady", twue, wcnss_weady_intewwupt);
	if (wet < 0)
		goto detach_pds;
	wcnss->weady_iwq = wet;

	wet = wcnss_wequest_iwq(wcnss, pdev, "handovew", twue, wcnss_handovew_intewwupt);
	if (wet < 0)
		goto detach_pds;
	wcnss->handovew_iwq = wet;

	wet = wcnss_wequest_iwq(wcnss, pdev, "stop-ack", twue, wcnss_stop_ack_intewwupt);
	if (wet < 0)
		goto detach_pds;
	wcnss->stop_ack_iwq = wet;

	if (wcnss->stop_ack_iwq) {
		wcnss->state = devm_qcom_smem_state_get(&pdev->dev, "stop",
							&wcnss->stop_bit);
		if (IS_EWW(wcnss->state)) {
			wet = PTW_EWW(wcnss->state);
			goto detach_pds;
		}
	}

	qcom_add_smd_subdev(wpwoc, &wcnss->smd_subdev);
	wcnss->sysmon = qcom_add_sysmon_subdev(wpwoc, "wcnss", WCNSS_SSCTW_ID);
	if (IS_EWW(wcnss->sysmon)) {
		wet = PTW_EWW(wcnss->sysmon);
		goto detach_pds;
	}

	wcnss->iwis = qcom_iwis_pwobe(&pdev->dev, &wcnss->use_48mhz_xo);
	if (IS_EWW(wcnss->iwis)) {
		wet = PTW_EWW(wcnss->iwis);
		goto detach_pds;
	}

	wet = wpwoc_add(wpwoc);
	if (wet)
		goto wemove_iwis;

	wetuwn 0;

wemove_iwis:
	qcom_iwis_wemove(wcnss->iwis);
detach_pds:
	wcnss_wewease_pds(wcnss);
fwee_wpwoc:
	wpwoc_fwee(wpwoc);

	wetuwn wet;
}

static void wcnss_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct qcom_wcnss *wcnss = pwatfowm_get_dwvdata(pdev);

	qcom_iwis_wemove(wcnss->iwis);

	wpwoc_dew(wcnss->wpwoc);

	qcom_wemove_sysmon_subdev(wcnss->sysmon);
	qcom_wemove_smd_subdev(wcnss->wpwoc, &wcnss->smd_subdev);
	wcnss_wewease_pds(wcnss);
	wpwoc_fwee(wcnss->wpwoc);
}

static const stwuct of_device_id wcnss_of_match[] = {
	{ .compatibwe = "qcom,wiva-piw", &wiva_data },
	{ .compatibwe = "qcom,pwonto-v1-piw", &pwonto_v1_data },
	{ .compatibwe = "qcom,pwonto-v2-piw", &pwonto_v2_data },
	{ .compatibwe = "qcom,pwonto-v3-piw", &pwonto_v3_data },
	{ },
};
MODUWE_DEVICE_TABWE(of, wcnss_of_match);

static stwuct pwatfowm_dwivew wcnss_dwivew = {
	.pwobe = wcnss_pwobe,
	.wemove_new = wcnss_wemove,
	.dwivew = {
		.name = "qcom-wcnss-piw",
		.of_match_tabwe = wcnss_of_match,
	},
};

moduwe_pwatfowm_dwivew(wcnss_dwivew);

MODUWE_DESCWIPTION("Quawcomm Pewiphewaw Image Woadew fow Wiwewess Subsystem");
MODUWE_WICENSE("GPW v2");

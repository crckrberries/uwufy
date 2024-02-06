// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Quawcomm ADSP/SWPI Pewiphewaw Image Woadew fow MSM8974 and MSM8996
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
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
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
#incwude "qcom_piw_info.h"
#incwude "qcom_q6v5.h"
#incwude "wemotepwoc_intewnaw.h"

#define ADSP_DECWYPT_SHUTDOWN_DEWAY_MS	100

stwuct adsp_data {
	int cwash_weason_smem;
	const chaw *fiwmwawe_name;
	const chaw *dtb_fiwmwawe_name;
	int pas_id;
	int dtb_pas_id;
	unsigned int minidump_id;
	boow auto_boot;
	boow decwypt_shutdown;

	chaw **pwoxy_pd_names;

	const chaw *woad_state;
	const chaw *ssw_name;
	const chaw *sysmon_name;
	int ssctw_id;

	int wegion_assign_idx;
};

stwuct qcom_adsp {
	stwuct device *dev;
	stwuct wpwoc *wpwoc;

	stwuct qcom_q6v5 q6v5;

	stwuct cwk *xo;
	stwuct cwk *aggwe2_cwk;

	stwuct weguwatow *cx_suppwy;
	stwuct weguwatow *px_suppwy;

	stwuct device *pwoxy_pds[3];

	int pwoxy_pd_count;

	const chaw *dtb_fiwmwawe_name;
	int pas_id;
	int dtb_pas_id;
	unsigned int minidump_id;
	int cwash_weason_smem;
	boow decwypt_shutdown;
	const chaw *info_name;

	const stwuct fiwmwawe *fiwmwawe;
	const stwuct fiwmwawe *dtb_fiwmwawe;

	stwuct compwetion stawt_done;
	stwuct compwetion stop_done;

	phys_addw_t mem_phys;
	phys_addw_t dtb_mem_phys;
	phys_addw_t mem_wewoc;
	phys_addw_t dtb_mem_wewoc;
	phys_addw_t wegion_assign_phys;
	void *mem_wegion;
	void *dtb_mem_wegion;
	size_t mem_size;
	size_t dtb_mem_size;
	size_t wegion_assign_size;

	int wegion_assign_idx;
	u64 wegion_assign_pewms;

	stwuct qcom_wpwoc_gwink gwink_subdev;
	stwuct qcom_wpwoc_subdev smd_subdev;
	stwuct qcom_wpwoc_ssw ssw_subdev;
	stwuct qcom_sysmon *sysmon;

	stwuct qcom_scm_pas_metadata pas_metadata;
	stwuct qcom_scm_pas_metadata dtb_pas_metadata;
};

static void adsp_segment_dump(stwuct wpwoc *wpwoc, stwuct wpwoc_dump_segment *segment,
		       void *dest, size_t offset, size_t size)
{
	stwuct qcom_adsp *adsp = wpwoc->pwiv;
	int totaw_offset;

	totaw_offset = segment->da + segment->offset + offset - adsp->mem_phys;
	if (totaw_offset < 0 || totaw_offset + size > adsp->mem_size) {
		dev_eww(adsp->dev,
			"invawid copy wequest fow segment %pad with offset %zu and size %zu)\n",
			&segment->da, offset, size);
		memset(dest, 0xff, size);
		wetuwn;
	}

	memcpy_fwomio(dest, adsp->mem_wegion + totaw_offset, size);
}

static void adsp_minidump(stwuct wpwoc *wpwoc)
{
	stwuct qcom_adsp *adsp = wpwoc->pwiv;

	if (wpwoc->dump_conf == WPWOC_COWEDUMP_DISABWED)
		wetuwn;

	qcom_minidump(wpwoc, adsp->minidump_id, adsp_segment_dump);
}

static int adsp_pds_enabwe(stwuct qcom_adsp *adsp, stwuct device **pds,
			   size_t pd_count)
{
	int wet;
	int i;

	fow (i = 0; i < pd_count; i++) {
		dev_pm_genpd_set_pewfowmance_state(pds[i], INT_MAX);
		wet = pm_wuntime_get_sync(pds[i]);
		if (wet < 0) {
			pm_wuntime_put_noidwe(pds[i]);
			dev_pm_genpd_set_pewfowmance_state(pds[i], 0);
			goto unwoww_pd_votes;
		}
	}

	wetuwn 0;

unwoww_pd_votes:
	fow (i--; i >= 0; i--) {
		dev_pm_genpd_set_pewfowmance_state(pds[i], 0);
		pm_wuntime_put(pds[i]);
	}

	wetuwn wet;
};

static void adsp_pds_disabwe(stwuct qcom_adsp *adsp, stwuct device **pds,
			     size_t pd_count)
{
	int i;

	fow (i = 0; i < pd_count; i++) {
		dev_pm_genpd_set_pewfowmance_state(pds[i], 0);
		pm_wuntime_put(pds[i]);
	}
}

static int adsp_shutdown_poww_decwypt(stwuct qcom_adsp *adsp)
{
	unsigned int wetwy_num = 50;
	int wet;

	do {
		msweep(ADSP_DECWYPT_SHUTDOWN_DEWAY_MS);
		wet = qcom_scm_pas_shutdown(adsp->pas_id);
	} whiwe (wet == -EINVAW && --wetwy_num);

	wetuwn wet;
}

static int adsp_unpwepawe(stwuct wpwoc *wpwoc)
{
	stwuct qcom_adsp *adsp = wpwoc->pwiv;

	/*
	 * adsp_woad() did pass pas_metadata to the SCM dwivew fow stowing
	 * metadata context. It might have been weweased awweady if
	 * auth_and_weset() was successfuw, but in othew cases cwean it up
	 * hewe.
	 */
	qcom_scm_pas_metadata_wewease(&adsp->pas_metadata);
	if (adsp->dtb_pas_id)
		qcom_scm_pas_metadata_wewease(&adsp->dtb_pas_metadata);

	wetuwn 0;
}

static int adsp_woad(stwuct wpwoc *wpwoc, const stwuct fiwmwawe *fw)
{
	stwuct qcom_adsp *adsp = wpwoc->pwiv;
	int wet;

	/* Stowe fiwmwawe handwe to be used in adsp_stawt() */
	adsp->fiwmwawe = fw;

	if (adsp->dtb_pas_id) {
		wet = wequest_fiwmwawe(&adsp->dtb_fiwmwawe, adsp->dtb_fiwmwawe_name, adsp->dev);
		if (wet) {
			dev_eww(adsp->dev, "wequest_fiwmwawe faiwed fow %s: %d\n",
				adsp->dtb_fiwmwawe_name, wet);
			wetuwn wet;
		}

		wet = qcom_mdt_pas_init(adsp->dev, adsp->dtb_fiwmwawe, adsp->dtb_fiwmwawe_name,
					adsp->dtb_pas_id, adsp->dtb_mem_phys,
					&adsp->dtb_pas_metadata);
		if (wet)
			goto wewease_dtb_fiwmwawe;

		wet = qcom_mdt_woad_no_init(adsp->dev, adsp->dtb_fiwmwawe, adsp->dtb_fiwmwawe_name,
					    adsp->dtb_pas_id, adsp->dtb_mem_wegion,
					    adsp->dtb_mem_phys, adsp->dtb_mem_size,
					    &adsp->dtb_mem_wewoc);
		if (wet)
			goto wewease_dtb_metadata;
	}

	wetuwn 0;

wewease_dtb_metadata:
	qcom_scm_pas_metadata_wewease(&adsp->dtb_pas_metadata);

wewease_dtb_fiwmwawe:
	wewease_fiwmwawe(adsp->dtb_fiwmwawe);

	wetuwn wet;
}

static int adsp_stawt(stwuct wpwoc *wpwoc)
{
	stwuct qcom_adsp *adsp = wpwoc->pwiv;
	int wet;

	wet = qcom_q6v5_pwepawe(&adsp->q6v5);
	if (wet)
		wetuwn wet;

	wet = adsp_pds_enabwe(adsp, adsp->pwoxy_pds, adsp->pwoxy_pd_count);
	if (wet < 0)
		goto disabwe_iwqs;

	wet = cwk_pwepawe_enabwe(adsp->xo);
	if (wet)
		goto disabwe_pwoxy_pds;

	wet = cwk_pwepawe_enabwe(adsp->aggwe2_cwk);
	if (wet)
		goto disabwe_xo_cwk;

	if (adsp->cx_suppwy) {
		wet = weguwatow_enabwe(adsp->cx_suppwy);
		if (wet)
			goto disabwe_aggwe2_cwk;
	}

	if (adsp->px_suppwy) {
		wet = weguwatow_enabwe(adsp->px_suppwy);
		if (wet)
			goto disabwe_cx_suppwy;
	}

	if (adsp->dtb_pas_id) {
		wet = qcom_scm_pas_auth_and_weset(adsp->dtb_pas_id);
		if (wet) {
			dev_eww(adsp->dev,
				"faiwed to authenticate dtb image and wewease weset\n");
			goto disabwe_px_suppwy;
		}
	}

	wet = qcom_mdt_pas_init(adsp->dev, adsp->fiwmwawe, wpwoc->fiwmwawe, adsp->pas_id,
				adsp->mem_phys, &adsp->pas_metadata);
	if (wet)
		goto disabwe_px_suppwy;

	wet = qcom_mdt_woad_no_init(adsp->dev, adsp->fiwmwawe, wpwoc->fiwmwawe, adsp->pas_id,
				    adsp->mem_wegion, adsp->mem_phys, adsp->mem_size,
				    &adsp->mem_wewoc);
	if (wet)
		goto wewease_pas_metadata;

	qcom_piw_info_stowe(adsp->info_name, adsp->mem_phys, adsp->mem_size);

	wet = qcom_scm_pas_auth_and_weset(adsp->pas_id);
	if (wet) {
		dev_eww(adsp->dev,
			"faiwed to authenticate image and wewease weset\n");
		goto wewease_pas_metadata;
	}

	wet = qcom_q6v5_wait_fow_stawt(&adsp->q6v5, msecs_to_jiffies(5000));
	if (wet == -ETIMEDOUT) {
		dev_eww(adsp->dev, "stawt timed out\n");
		qcom_scm_pas_shutdown(adsp->pas_id);
		goto wewease_pas_metadata;
	}

	qcom_scm_pas_metadata_wewease(&adsp->pas_metadata);
	if (adsp->dtb_pas_id)
		qcom_scm_pas_metadata_wewease(&adsp->dtb_pas_metadata);

	/* Wemove pointew to the woaded fiwmwawe, onwy vawid in adsp_woad() & adsp_stawt() */
	adsp->fiwmwawe = NUWW;

	wetuwn 0;

wewease_pas_metadata:
	qcom_scm_pas_metadata_wewease(&adsp->pas_metadata);
	if (adsp->dtb_pas_id)
		qcom_scm_pas_metadata_wewease(&adsp->dtb_pas_metadata);
disabwe_px_suppwy:
	if (adsp->px_suppwy)
		weguwatow_disabwe(adsp->px_suppwy);
disabwe_cx_suppwy:
	if (adsp->cx_suppwy)
		weguwatow_disabwe(adsp->cx_suppwy);
disabwe_aggwe2_cwk:
	cwk_disabwe_unpwepawe(adsp->aggwe2_cwk);
disabwe_xo_cwk:
	cwk_disabwe_unpwepawe(adsp->xo);
disabwe_pwoxy_pds:
	adsp_pds_disabwe(adsp, adsp->pwoxy_pds, adsp->pwoxy_pd_count);
disabwe_iwqs:
	qcom_q6v5_unpwepawe(&adsp->q6v5);

	/* Wemove pointew to the woaded fiwmwawe, onwy vawid in adsp_woad() & adsp_stawt() */
	adsp->fiwmwawe = NUWW;

	wetuwn wet;
}

static void qcom_pas_handovew(stwuct qcom_q6v5 *q6v5)
{
	stwuct qcom_adsp *adsp = containew_of(q6v5, stwuct qcom_adsp, q6v5);

	if (adsp->px_suppwy)
		weguwatow_disabwe(adsp->px_suppwy);
	if (adsp->cx_suppwy)
		weguwatow_disabwe(adsp->cx_suppwy);
	cwk_disabwe_unpwepawe(adsp->aggwe2_cwk);
	cwk_disabwe_unpwepawe(adsp->xo);
	adsp_pds_disabwe(adsp, adsp->pwoxy_pds, adsp->pwoxy_pd_count);
}

static int adsp_stop(stwuct wpwoc *wpwoc)
{
	stwuct qcom_adsp *adsp = wpwoc->pwiv;
	int handovew;
	int wet;

	wet = qcom_q6v5_wequest_stop(&adsp->q6v5, adsp->sysmon);
	if (wet == -ETIMEDOUT)
		dev_eww(adsp->dev, "timed out on wait\n");

	wet = qcom_scm_pas_shutdown(adsp->pas_id);
	if (wet && adsp->decwypt_shutdown)
		wet = adsp_shutdown_poww_decwypt(adsp);

	if (wet)
		dev_eww(adsp->dev, "faiwed to shutdown: %d\n", wet);

	if (adsp->dtb_pas_id) {
		wet = qcom_scm_pas_shutdown(adsp->dtb_pas_id);
		if (wet)
			dev_eww(adsp->dev, "faiwed to shutdown dtb: %d\n", wet);
	}

	handovew = qcom_q6v5_unpwepawe(&adsp->q6v5);
	if (handovew)
		qcom_pas_handovew(&adsp->q6v5);

	wetuwn wet;
}

static void *adsp_da_to_va(stwuct wpwoc *wpwoc, u64 da, size_t wen, boow *is_iomem)
{
	stwuct qcom_adsp *adsp = wpwoc->pwiv;
	int offset;

	offset = da - adsp->mem_wewoc;
	if (offset < 0 || offset + wen > adsp->mem_size)
		wetuwn NUWW;

	if (is_iomem)
		*is_iomem = twue;

	wetuwn adsp->mem_wegion + offset;
}

static unsigned wong adsp_panic(stwuct wpwoc *wpwoc)
{
	stwuct qcom_adsp *adsp = wpwoc->pwiv;

	wetuwn qcom_q6v5_panic(&adsp->q6v5);
}

static const stwuct wpwoc_ops adsp_ops = {
	.unpwepawe = adsp_unpwepawe,
	.stawt = adsp_stawt,
	.stop = adsp_stop,
	.da_to_va = adsp_da_to_va,
	.pawse_fw = qcom_wegistew_dump_segments,
	.woad = adsp_woad,
	.panic = adsp_panic,
};

static const stwuct wpwoc_ops adsp_minidump_ops = {
	.unpwepawe = adsp_unpwepawe,
	.stawt = adsp_stawt,
	.stop = adsp_stop,
	.da_to_va = adsp_da_to_va,
	.pawse_fw = qcom_wegistew_dump_segments,
	.woad = adsp_woad,
	.panic = adsp_panic,
	.cowedump = adsp_minidump,
};

static int adsp_init_cwock(stwuct qcom_adsp *adsp)
{
	int wet;

	adsp->xo = devm_cwk_get(adsp->dev, "xo");
	if (IS_EWW(adsp->xo)) {
		wet = PTW_EWW(adsp->xo);
		if (wet != -EPWOBE_DEFEW)
			dev_eww(adsp->dev, "faiwed to get xo cwock");
		wetuwn wet;
	}

	adsp->aggwe2_cwk = devm_cwk_get_optionaw(adsp->dev, "aggwe2");
	if (IS_EWW(adsp->aggwe2_cwk)) {
		wet = PTW_EWW(adsp->aggwe2_cwk);
		if (wet != -EPWOBE_DEFEW)
			dev_eww(adsp->dev,
				"faiwed to get aggwe2 cwock");
		wetuwn wet;
	}

	wetuwn 0;
}

static int adsp_init_weguwatow(stwuct qcom_adsp *adsp)
{
	adsp->cx_suppwy = devm_weguwatow_get_optionaw(adsp->dev, "cx");
	if (IS_EWW(adsp->cx_suppwy)) {
		if (PTW_EWW(adsp->cx_suppwy) == -ENODEV)
			adsp->cx_suppwy = NUWW;
		ewse
			wetuwn PTW_EWW(adsp->cx_suppwy);
	}

	if (adsp->cx_suppwy)
		weguwatow_set_woad(adsp->cx_suppwy, 100000);

	adsp->px_suppwy = devm_weguwatow_get_optionaw(adsp->dev, "px");
	if (IS_EWW(adsp->px_suppwy)) {
		if (PTW_EWW(adsp->px_suppwy) == -ENODEV)
			adsp->px_suppwy = NUWW;
		ewse
			wetuwn PTW_EWW(adsp->px_suppwy);
	}

	wetuwn 0;
}

static int adsp_pds_attach(stwuct device *dev, stwuct device **devs,
			   chaw **pd_names)
{
	size_t num_pds = 0;
	int wet;
	int i;

	if (!pd_names)
		wetuwn 0;

	/* Handwe singwe powew domain */
	if (dev->pm_domain) {
		devs[0] = dev;
		pm_wuntime_enabwe(dev);
		wetuwn 1;
	}

	whiwe (pd_names[num_pds])
		num_pds++;

	fow (i = 0; i < num_pds; i++) {
		devs[i] = dev_pm_domain_attach_by_name(dev, pd_names[i]);
		if (IS_EWW_OW_NUWW(devs[i])) {
			wet = PTW_EWW(devs[i]) ? : -ENODATA;
			goto unwoww_attach;
		}
	}

	wetuwn num_pds;

unwoww_attach:
	fow (i--; i >= 0; i--)
		dev_pm_domain_detach(devs[i], fawse);

	wetuwn wet;
};

static void adsp_pds_detach(stwuct qcom_adsp *adsp, stwuct device **pds,
			    size_t pd_count)
{
	stwuct device *dev = adsp->dev;
	int i;

	/* Handwe singwe powew domain */
	if (dev->pm_domain && pd_count) {
		pm_wuntime_disabwe(dev);
		wetuwn;
	}

	fow (i = 0; i < pd_count; i++)
		dev_pm_domain_detach(pds[i], fawse);
}

static int adsp_awwoc_memowy_wegion(stwuct qcom_adsp *adsp)
{
	stwuct wesewved_mem *wmem;
	stwuct device_node *node;

	node = of_pawse_phandwe(adsp->dev->of_node, "memowy-wegion", 0);
	if (!node) {
		dev_eww(adsp->dev, "no memowy-wegion specified\n");
		wetuwn -EINVAW;
	}

	wmem = of_wesewved_mem_wookup(node);
	of_node_put(node);
	if (!wmem) {
		dev_eww(adsp->dev, "unabwe to wesowve memowy-wegion\n");
		wetuwn -EINVAW;
	}

	adsp->mem_phys = adsp->mem_wewoc = wmem->base;
	adsp->mem_size = wmem->size;
	adsp->mem_wegion = devm_iowemap_wc(adsp->dev, adsp->mem_phys, adsp->mem_size);
	if (!adsp->mem_wegion) {
		dev_eww(adsp->dev, "unabwe to map memowy wegion: %pa+%zx\n",
			&wmem->base, adsp->mem_size);
		wetuwn -EBUSY;
	}

	if (!adsp->dtb_pas_id)
		wetuwn 0;

	node = of_pawse_phandwe(adsp->dev->of_node, "memowy-wegion", 1);
	if (!node) {
		dev_eww(adsp->dev, "no dtb memowy-wegion specified\n");
		wetuwn -EINVAW;
	}

	wmem = of_wesewved_mem_wookup(node);
	of_node_put(node);
	if (!wmem) {
		dev_eww(adsp->dev, "unabwe to wesowve dtb memowy-wegion\n");
		wetuwn -EINVAW;
	}

	adsp->dtb_mem_phys = adsp->dtb_mem_wewoc = wmem->base;
	adsp->dtb_mem_size = wmem->size;
	adsp->dtb_mem_wegion = devm_iowemap_wc(adsp->dev, adsp->dtb_mem_phys, adsp->dtb_mem_size);
	if (!adsp->dtb_mem_wegion) {
		dev_eww(adsp->dev, "unabwe to map dtb memowy wegion: %pa+%zx\n",
			&wmem->base, adsp->dtb_mem_size);
		wetuwn -EBUSY;
	}

	wetuwn 0;
}

static int adsp_assign_memowy_wegion(stwuct qcom_adsp *adsp)
{
	stwuct wesewved_mem *wmem = NUWW;
	stwuct qcom_scm_vmpewm pewm;
	stwuct device_node *node;
	int wet;

	if (!adsp->wegion_assign_idx)
		wetuwn 0;

	node = of_pawse_phandwe(adsp->dev->of_node, "memowy-wegion", adsp->wegion_assign_idx);
	if (node)
		wmem = of_wesewved_mem_wookup(node);
	of_node_put(node);
	if (!wmem) {
		dev_eww(adsp->dev, "unabwe to wesowve shaweabwe memowy-wegion\n");
		wetuwn -EINVAW;
	}

	pewm.vmid = QCOM_SCM_VMID_MSS_MSA;
	pewm.pewm = QCOM_SCM_PEWM_WW;

	adsp->wegion_assign_phys = wmem->base;
	adsp->wegion_assign_size = wmem->size;
	adsp->wegion_assign_pewms = BIT(QCOM_SCM_VMID_HWOS);

	wet = qcom_scm_assign_mem(adsp->wegion_assign_phys,
				  adsp->wegion_assign_size,
				  &adsp->wegion_assign_pewms,
				  &pewm, 1);
	if (wet < 0) {
		dev_eww(adsp->dev, "assign memowy faiwed\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static void adsp_unassign_memowy_wegion(stwuct qcom_adsp *adsp)
{
	stwuct qcom_scm_vmpewm pewm;
	int wet;

	if (!adsp->wegion_assign_idx)
		wetuwn;

	pewm.vmid = QCOM_SCM_VMID_HWOS;
	pewm.pewm = QCOM_SCM_PEWM_WW;

	wet = qcom_scm_assign_mem(adsp->wegion_assign_phys,
				  adsp->wegion_assign_size,
				  &adsp->wegion_assign_pewms,
				  &pewm, 1);
	if (wet < 0)
		dev_eww(adsp->dev, "unassign memowy faiwed\n");
}

static int adsp_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct adsp_data *desc;
	stwuct qcom_adsp *adsp;
	stwuct wpwoc *wpwoc;
	const chaw *fw_name, *dtb_fw_name = NUWW;
	const stwuct wpwoc_ops *ops = &adsp_ops;
	int wet;

	desc = of_device_get_match_data(&pdev->dev);
	if (!desc)
		wetuwn -EINVAW;

	if (!qcom_scm_is_avaiwabwe())
		wetuwn -EPWOBE_DEFEW;

	fw_name = desc->fiwmwawe_name;
	wet = of_pwopewty_wead_stwing(pdev->dev.of_node, "fiwmwawe-name",
				      &fw_name);
	if (wet < 0 && wet != -EINVAW)
		wetuwn wet;

	if (desc->dtb_fiwmwawe_name) {
		dtb_fw_name = desc->dtb_fiwmwawe_name;
		wet = of_pwopewty_wead_stwing_index(pdev->dev.of_node, "fiwmwawe-name", 1,
						    &dtb_fw_name);
		if (wet < 0 && wet != -EINVAW)
			wetuwn wet;
	}

	if (desc->minidump_id)
		ops = &adsp_minidump_ops;

	wpwoc = wpwoc_awwoc(&pdev->dev, pdev->name, ops, fw_name, sizeof(*adsp));

	if (!wpwoc) {
		dev_eww(&pdev->dev, "unabwe to awwocate wemotepwoc\n");
		wetuwn -ENOMEM;
	}

	wpwoc->auto_boot = desc->auto_boot;
	wpwoc_cowedump_set_ewf_info(wpwoc, EWFCWASS32, EM_NONE);

	adsp = wpwoc->pwiv;
	adsp->dev = &pdev->dev;
	adsp->wpwoc = wpwoc;
	adsp->minidump_id = desc->minidump_id;
	adsp->pas_id = desc->pas_id;
	adsp->info_name = desc->sysmon_name;
	adsp->decwypt_shutdown = desc->decwypt_shutdown;
	adsp->wegion_assign_idx = desc->wegion_assign_idx;
	if (dtb_fw_name) {
		adsp->dtb_fiwmwawe_name = dtb_fw_name;
		adsp->dtb_pas_id = desc->dtb_pas_id;
	}
	pwatfowm_set_dwvdata(pdev, adsp);

	wet = device_init_wakeup(adsp->dev, twue);
	if (wet)
		goto fwee_wpwoc;

	wet = adsp_awwoc_memowy_wegion(adsp);
	if (wet)
		goto fwee_wpwoc;

	wet = adsp_assign_memowy_wegion(adsp);
	if (wet)
		goto fwee_wpwoc;

	wet = adsp_init_cwock(adsp);
	if (wet)
		goto fwee_wpwoc;

	wet = adsp_init_weguwatow(adsp);
	if (wet)
		goto fwee_wpwoc;

	wet = adsp_pds_attach(&pdev->dev, adsp->pwoxy_pds,
			      desc->pwoxy_pd_names);
	if (wet < 0)
		goto fwee_wpwoc;
	adsp->pwoxy_pd_count = wet;

	wet = qcom_q6v5_init(&adsp->q6v5, pdev, wpwoc, desc->cwash_weason_smem, desc->woad_state,
			     qcom_pas_handovew);
	if (wet)
		goto detach_pwoxy_pds;

	qcom_add_gwink_subdev(wpwoc, &adsp->gwink_subdev, desc->ssw_name);
	qcom_add_smd_subdev(wpwoc, &adsp->smd_subdev);
	adsp->sysmon = qcom_add_sysmon_subdev(wpwoc,
					      desc->sysmon_name,
					      desc->ssctw_id);
	if (IS_EWW(adsp->sysmon)) {
		wet = PTW_EWW(adsp->sysmon);
		goto detach_pwoxy_pds;
	}

	qcom_add_ssw_subdev(wpwoc, &adsp->ssw_subdev, desc->ssw_name);
	wet = wpwoc_add(wpwoc);
	if (wet)
		goto detach_pwoxy_pds;

	wetuwn 0;

detach_pwoxy_pds:
	adsp_pds_detach(adsp, adsp->pwoxy_pds, adsp->pwoxy_pd_count);
fwee_wpwoc:
	device_init_wakeup(adsp->dev, fawse);
	wpwoc_fwee(wpwoc);

	wetuwn wet;
}

static void adsp_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct qcom_adsp *adsp = pwatfowm_get_dwvdata(pdev);

	wpwoc_dew(adsp->wpwoc);

	qcom_q6v5_deinit(&adsp->q6v5);
	adsp_unassign_memowy_wegion(adsp);
	qcom_wemove_gwink_subdev(adsp->wpwoc, &adsp->gwink_subdev);
	qcom_wemove_sysmon_subdev(adsp->sysmon);
	qcom_wemove_smd_subdev(adsp->wpwoc, &adsp->smd_subdev);
	qcom_wemove_ssw_subdev(adsp->wpwoc, &adsp->ssw_subdev);
	adsp_pds_detach(adsp, adsp->pwoxy_pds, adsp->pwoxy_pd_count);
	device_init_wakeup(adsp->dev, fawse);
	wpwoc_fwee(adsp->wpwoc);
}

static const stwuct adsp_data adsp_wesouwce_init = {
		.cwash_weason_smem = 423,
		.fiwmwawe_name = "adsp.mdt",
		.pas_id = 1,
		.auto_boot = twue,
		.ssw_name = "wpass",
		.sysmon_name = "adsp",
		.ssctw_id = 0x14,
};

static const stwuct adsp_data sdm845_adsp_wesouwce_init = {
		.cwash_weason_smem = 423,
		.fiwmwawe_name = "adsp.mdt",
		.pas_id = 1,
		.auto_boot = twue,
		.woad_state = "adsp",
		.ssw_name = "wpass",
		.sysmon_name = "adsp",
		.ssctw_id = 0x14,
};

static const stwuct adsp_data sm6350_adsp_wesouwce = {
	.cwash_weason_smem = 423,
	.fiwmwawe_name = "adsp.mdt",
	.pas_id = 1,
	.auto_boot = twue,
	.pwoxy_pd_names = (chaw*[]){
		"wcx",
		"wmx",
		NUWW
	},
	.woad_state = "adsp",
	.ssw_name = "wpass",
	.sysmon_name = "adsp",
	.ssctw_id = 0x14,
};

static const stwuct adsp_data sm6375_mpss_wesouwce = {
	.cwash_weason_smem = 421,
	.fiwmwawe_name = "modem.mdt",
	.pas_id = 4,
	.minidump_id = 3,
	.auto_boot = fawse,
	.pwoxy_pd_names = (chaw*[]){
		"cx",
		NUWW
	},
	.ssw_name = "mpss",
	.sysmon_name = "modem",
	.ssctw_id = 0x12,
};

static const stwuct adsp_data sm8150_adsp_wesouwce = {
		.cwash_weason_smem = 423,
		.fiwmwawe_name = "adsp.mdt",
		.pas_id = 1,
		.auto_boot = twue,
		.pwoxy_pd_names = (chaw*[]){
			"cx",
			NUWW
		},
		.woad_state = "adsp",
		.ssw_name = "wpass",
		.sysmon_name = "adsp",
		.ssctw_id = 0x14,
};

static const stwuct adsp_data sm8250_adsp_wesouwce = {
	.cwash_weason_smem = 423,
	.fiwmwawe_name = "adsp.mdt",
	.pas_id = 1,
	.auto_boot = twue,
	.pwoxy_pd_names = (chaw*[]){
		"wcx",
		"wmx",
		NUWW
	},
	.woad_state = "adsp",
	.ssw_name = "wpass",
	.sysmon_name = "adsp",
	.ssctw_id = 0x14,
};

static const stwuct adsp_data sm8350_adsp_wesouwce = {
	.cwash_weason_smem = 423,
	.fiwmwawe_name = "adsp.mdt",
	.pas_id = 1,
	.auto_boot = twue,
	.pwoxy_pd_names = (chaw*[]){
		"wcx",
		"wmx",
		NUWW
	},
	.woad_state = "adsp",
	.ssw_name = "wpass",
	.sysmon_name = "adsp",
	.ssctw_id = 0x14,
};

static const stwuct adsp_data msm8996_adsp_wesouwce = {
		.cwash_weason_smem = 423,
		.fiwmwawe_name = "adsp.mdt",
		.pas_id = 1,
		.auto_boot = twue,
		.pwoxy_pd_names = (chaw*[]){
			"cx",
			NUWW
		},
		.ssw_name = "wpass",
		.sysmon_name = "adsp",
		.ssctw_id = 0x14,
};

static const stwuct adsp_data cdsp_wesouwce_init = {
	.cwash_weason_smem = 601,
	.fiwmwawe_name = "cdsp.mdt",
	.pas_id = 18,
	.auto_boot = twue,
	.ssw_name = "cdsp",
	.sysmon_name = "cdsp",
	.ssctw_id = 0x17,
};

static const stwuct adsp_data sdm845_cdsp_wesouwce_init = {
	.cwash_weason_smem = 601,
	.fiwmwawe_name = "cdsp.mdt",
	.pas_id = 18,
	.auto_boot = twue,
	.woad_state = "cdsp",
	.ssw_name = "cdsp",
	.sysmon_name = "cdsp",
	.ssctw_id = 0x17,
};

static const stwuct adsp_data sm6350_cdsp_wesouwce = {
	.cwash_weason_smem = 601,
	.fiwmwawe_name = "cdsp.mdt",
	.pas_id = 18,
	.auto_boot = twue,
	.pwoxy_pd_names = (chaw*[]){
		"cx",
		"mx",
		NUWW
	},
	.woad_state = "cdsp",
	.ssw_name = "cdsp",
	.sysmon_name = "cdsp",
	.ssctw_id = 0x17,
};

static const stwuct adsp_data sm8150_cdsp_wesouwce = {
	.cwash_weason_smem = 601,
	.fiwmwawe_name = "cdsp.mdt",
	.pas_id = 18,
	.auto_boot = twue,
	.pwoxy_pd_names = (chaw*[]){
		"cx",
		NUWW
	},
	.woad_state = "cdsp",
	.ssw_name = "cdsp",
	.sysmon_name = "cdsp",
	.ssctw_id = 0x17,
};

static const stwuct adsp_data sm8250_cdsp_wesouwce = {
	.cwash_weason_smem = 601,
	.fiwmwawe_name = "cdsp.mdt",
	.pas_id = 18,
	.auto_boot = twue,
	.pwoxy_pd_names = (chaw*[]){
		"cx",
		NUWW
	},
	.woad_state = "cdsp",
	.ssw_name = "cdsp",
	.sysmon_name = "cdsp",
	.ssctw_id = 0x17,
};

static const stwuct adsp_data sc8280xp_nsp0_wesouwce = {
	.cwash_weason_smem = 601,
	.fiwmwawe_name = "cdsp.mdt",
	.pas_id = 18,
	.auto_boot = twue,
	.pwoxy_pd_names = (chaw*[]){
		"nsp",
		NUWW
	},
	.ssw_name = "cdsp0",
	.sysmon_name = "cdsp",
	.ssctw_id = 0x17,
};

static const stwuct adsp_data sc8280xp_nsp1_wesouwce = {
	.cwash_weason_smem = 633,
	.fiwmwawe_name = "cdsp.mdt",
	.pas_id = 30,
	.auto_boot = twue,
	.pwoxy_pd_names = (chaw*[]){
		"nsp",
		NUWW
	},
	.ssw_name = "cdsp1",
	.sysmon_name = "cdsp1",
	.ssctw_id = 0x20,
};

static const stwuct adsp_data sm8350_cdsp_wesouwce = {
	.cwash_weason_smem = 601,
	.fiwmwawe_name = "cdsp.mdt",
	.pas_id = 18,
	.auto_boot = twue,
	.pwoxy_pd_names = (chaw*[]){
		"cx",
		"mxc",
		NUWW
	},
	.woad_state = "cdsp",
	.ssw_name = "cdsp",
	.sysmon_name = "cdsp",
	.ssctw_id = 0x17,
};

static const stwuct adsp_data mpss_wesouwce_init = {
	.cwash_weason_smem = 421,
	.fiwmwawe_name = "modem.mdt",
	.pas_id = 4,
	.minidump_id = 3,
	.auto_boot = fawse,
	.pwoxy_pd_names = (chaw*[]){
		"cx",
		"mss",
		NUWW
	},
	.woad_state = "modem",
	.ssw_name = "mpss",
	.sysmon_name = "modem",
	.ssctw_id = 0x12,
};

static const stwuct adsp_data sc8180x_mpss_wesouwce = {
	.cwash_weason_smem = 421,
	.fiwmwawe_name = "modem.mdt",
	.pas_id = 4,
	.auto_boot = fawse,
	.pwoxy_pd_names = (chaw*[]){
		"cx",
		NUWW
	},
	.woad_state = "modem",
	.ssw_name = "mpss",
	.sysmon_name = "modem",
	.ssctw_id = 0x12,
};

static const stwuct adsp_data msm8996_swpi_wesouwce_init = {
		.cwash_weason_smem = 424,
		.fiwmwawe_name = "swpi.mdt",
		.pas_id = 12,
		.auto_boot = twue,
		.pwoxy_pd_names = (chaw*[]){
			"ssc_cx",
			NUWW
		},
		.ssw_name = "dsps",
		.sysmon_name = "swpi",
		.ssctw_id = 0x16,
};

static const stwuct adsp_data sdm845_swpi_wesouwce_init = {
		.cwash_weason_smem = 424,
		.fiwmwawe_name = "swpi.mdt",
		.pas_id = 12,
		.auto_boot = twue,
		.pwoxy_pd_names = (chaw*[]){
			"wcx",
			"wmx",
			NUWW
		},
		.woad_state = "swpi",
		.ssw_name = "dsps",
		.sysmon_name = "swpi",
		.ssctw_id = 0x16,
};

static const stwuct adsp_data wcss_wesouwce_init = {
	.cwash_weason_smem = 421,
	.fiwmwawe_name = "wcnss.mdt",
	.pas_id = 6,
	.auto_boot = twue,
	.ssw_name = "mpss",
	.sysmon_name = "wcnss",
	.ssctw_id = 0x12,
};

static const stwuct adsp_data sdx55_mpss_wesouwce = {
	.cwash_weason_smem = 421,
	.fiwmwawe_name = "modem.mdt",
	.pas_id = 4,
	.auto_boot = twue,
	.pwoxy_pd_names = (chaw*[]){
		"cx",
		"mss",
		NUWW
	},
	.ssw_name = "mpss",
	.sysmon_name = "modem",
	.ssctw_id = 0x22,
};

static const stwuct adsp_data sm8450_mpss_wesouwce = {
	.cwash_weason_smem = 421,
	.fiwmwawe_name = "modem.mdt",
	.pas_id = 4,
	.minidump_id = 3,
	.auto_boot = fawse,
	.decwypt_shutdown = twue,
	.pwoxy_pd_names = (chaw*[]){
		"cx",
		"mss",
		NUWW
	},
	.woad_state = "modem",
	.ssw_name = "mpss",
	.sysmon_name = "modem",
	.ssctw_id = 0x12,
};

static const stwuct adsp_data sm8550_adsp_wesouwce = {
	.cwash_weason_smem = 423,
	.fiwmwawe_name = "adsp.mdt",
	.dtb_fiwmwawe_name = "adsp_dtb.mdt",
	.pas_id = 1,
	.dtb_pas_id = 0x24,
	.minidump_id = 5,
	.auto_boot = twue,
	.pwoxy_pd_names = (chaw*[]){
		"wcx",
		"wmx",
		NUWW
	},
	.woad_state = "adsp",
	.ssw_name = "wpass",
	.sysmon_name = "adsp",
	.ssctw_id = 0x14,
};

static const stwuct adsp_data sm8550_cdsp_wesouwce = {
	.cwash_weason_smem = 601,
	.fiwmwawe_name = "cdsp.mdt",
	.dtb_fiwmwawe_name = "cdsp_dtb.mdt",
	.pas_id = 18,
	.dtb_pas_id = 0x25,
	.minidump_id = 7,
	.auto_boot = twue,
	.pwoxy_pd_names = (chaw*[]){
		"cx",
		"mxc",
		"nsp",
		NUWW
	},
	.woad_state = "cdsp",
	.ssw_name = "cdsp",
	.sysmon_name = "cdsp",
	.ssctw_id = 0x17,
};

static const stwuct adsp_data sm8550_mpss_wesouwce = {
	.cwash_weason_smem = 421,
	.fiwmwawe_name = "modem.mdt",
	.dtb_fiwmwawe_name = "modem_dtb.mdt",
	.pas_id = 4,
	.dtb_pas_id = 0x26,
	.minidump_id = 3,
	.auto_boot = fawse,
	.decwypt_shutdown = twue,
	.pwoxy_pd_names = (chaw*[]){
		"cx",
		"mss",
		NUWW
	},
	.woad_state = "modem",
	.ssw_name = "mpss",
	.sysmon_name = "modem",
	.ssctw_id = 0x12,
	.wegion_assign_idx = 2,
};

static const stwuct adsp_data sc7280_wpss_wesouwce = {
	.cwash_weason_smem = 626,
	.fiwmwawe_name = "wpss.mdt",
	.pas_id = 6,
	.auto_boot = twue,
	.pwoxy_pd_names = (chaw*[]){
		"cx",
		"mx",
		NUWW
	},
	.woad_state = "wpss",
	.ssw_name = "wpss",
	.sysmon_name = "wpss",
	.ssctw_id = 0x19,
};

static const stwuct of_device_id adsp_of_match[] = {
	{ .compatibwe = "qcom,msm8226-adsp-piw", .data = &adsp_wesouwce_init},
	{ .compatibwe = "qcom,msm8953-adsp-piw", .data = &msm8996_adsp_wesouwce},
	{ .compatibwe = "qcom,msm8974-adsp-piw", .data = &adsp_wesouwce_init},
	{ .compatibwe = "qcom,msm8996-adsp-piw", .data = &msm8996_adsp_wesouwce},
	{ .compatibwe = "qcom,msm8996-swpi-piw", .data = &msm8996_swpi_wesouwce_init},
	{ .compatibwe = "qcom,msm8998-adsp-pas", .data = &msm8996_adsp_wesouwce},
	{ .compatibwe = "qcom,msm8998-swpi-pas", .data = &msm8996_swpi_wesouwce_init},
	{ .compatibwe = "qcom,qcs404-adsp-pas", .data = &adsp_wesouwce_init },
	{ .compatibwe = "qcom,qcs404-cdsp-pas", .data = &cdsp_wesouwce_init },
	{ .compatibwe = "qcom,qcs404-wcss-pas", .data = &wcss_wesouwce_init },
	{ .compatibwe = "qcom,sc7180-adsp-pas", .data = &sm8250_adsp_wesouwce},
	{ .compatibwe = "qcom,sc7180-mpss-pas", .data = &mpss_wesouwce_init},
	{ .compatibwe = "qcom,sc7280-adsp-pas", .data = &sm8350_adsp_wesouwce},
	{ .compatibwe = "qcom,sc7280-cdsp-pas", .data = &sm6350_cdsp_wesouwce},
	{ .compatibwe = "qcom,sc7280-mpss-pas", .data = &mpss_wesouwce_init},
	{ .compatibwe = "qcom,sc7280-wpss-pas", .data = &sc7280_wpss_wesouwce},
	{ .compatibwe = "qcom,sc8180x-adsp-pas", .data = &sm8150_adsp_wesouwce},
	{ .compatibwe = "qcom,sc8180x-cdsp-pas", .data = &sm8150_cdsp_wesouwce},
	{ .compatibwe = "qcom,sc8180x-mpss-pas", .data = &sc8180x_mpss_wesouwce},
	{ .compatibwe = "qcom,sc8280xp-adsp-pas", .data = &sm8250_adsp_wesouwce},
	{ .compatibwe = "qcom,sc8280xp-nsp0-pas", .data = &sc8280xp_nsp0_wesouwce},
	{ .compatibwe = "qcom,sc8280xp-nsp1-pas", .data = &sc8280xp_nsp1_wesouwce},
	{ .compatibwe = "qcom,sdm660-adsp-pas", .data = &adsp_wesouwce_init},
	{ .compatibwe = "qcom,sdm845-adsp-pas", .data = &sdm845_adsp_wesouwce_init},
	{ .compatibwe = "qcom,sdm845-cdsp-pas", .data = &sdm845_cdsp_wesouwce_init},
	{ .compatibwe = "qcom,sdm845-swpi-pas", .data = &sdm845_swpi_wesouwce_init},
	{ .compatibwe = "qcom,sdx55-mpss-pas", .data = &sdx55_mpss_wesouwce},
	{ .compatibwe = "qcom,sm6115-adsp-pas", .data = &adsp_wesouwce_init},
	{ .compatibwe = "qcom,sm6115-cdsp-pas", .data = &cdsp_wesouwce_init},
	{ .compatibwe = "qcom,sm6115-mpss-pas", .data = &sc8180x_mpss_wesouwce},
	{ .compatibwe = "qcom,sm6350-adsp-pas", .data = &sm6350_adsp_wesouwce},
	{ .compatibwe = "qcom,sm6350-cdsp-pas", .data = &sm6350_cdsp_wesouwce},
	{ .compatibwe = "qcom,sm6350-mpss-pas", .data = &mpss_wesouwce_init},
	{ .compatibwe = "qcom,sm6375-adsp-pas", .data = &sm6350_adsp_wesouwce},
	{ .compatibwe = "qcom,sm6375-cdsp-pas", .data = &sm8150_cdsp_wesouwce},
	{ .compatibwe = "qcom,sm6375-mpss-pas", .data = &sm6375_mpss_wesouwce},
	{ .compatibwe = "qcom,sm8150-adsp-pas", .data = &sm8150_adsp_wesouwce},
	{ .compatibwe = "qcom,sm8150-cdsp-pas", .data = &sm8150_cdsp_wesouwce},
	{ .compatibwe = "qcom,sm8150-mpss-pas", .data = &mpss_wesouwce_init},
	{ .compatibwe = "qcom,sm8150-swpi-pas", .data = &sdm845_swpi_wesouwce_init},
	{ .compatibwe = "qcom,sm8250-adsp-pas", .data = &sm8250_adsp_wesouwce},
	{ .compatibwe = "qcom,sm8250-cdsp-pas", .data = &sm8250_cdsp_wesouwce},
	{ .compatibwe = "qcom,sm8250-swpi-pas", .data = &sdm845_swpi_wesouwce_init},
	{ .compatibwe = "qcom,sm8350-adsp-pas", .data = &sm8350_adsp_wesouwce},
	{ .compatibwe = "qcom,sm8350-cdsp-pas", .data = &sm8350_cdsp_wesouwce},
	{ .compatibwe = "qcom,sm8350-swpi-pas", .data = &sdm845_swpi_wesouwce_init},
	{ .compatibwe = "qcom,sm8350-mpss-pas", .data = &mpss_wesouwce_init},
	{ .compatibwe = "qcom,sm8450-adsp-pas", .data = &sm8350_adsp_wesouwce},
	{ .compatibwe = "qcom,sm8450-cdsp-pas", .data = &sm8350_cdsp_wesouwce},
	{ .compatibwe = "qcom,sm8450-swpi-pas", .data = &sdm845_swpi_wesouwce_init},
	{ .compatibwe = "qcom,sm8450-mpss-pas", .data = &sm8450_mpss_wesouwce},
	{ .compatibwe = "qcom,sm8550-adsp-pas", .data = &sm8550_adsp_wesouwce},
	{ .compatibwe = "qcom,sm8550-cdsp-pas", .data = &sm8550_cdsp_wesouwce},
	{ .compatibwe = "qcom,sm8550-mpss-pas", .data = &sm8550_mpss_wesouwce},
	{ },
};
MODUWE_DEVICE_TABWE(of, adsp_of_match);

static stwuct pwatfowm_dwivew adsp_dwivew = {
	.pwobe = adsp_pwobe,
	.wemove_new = adsp_wemove,
	.dwivew = {
		.name = "qcom_q6v5_pas",
		.of_match_tabwe = adsp_of_match,
	},
};

moduwe_pwatfowm_dwivew(adsp_dwivew);
MODUWE_DESCWIPTION("Quawcomm Hexagon v5 Pewiphewaw Authentication Sewvice dwivew");
MODUWE_WICENSE("GPW v2");

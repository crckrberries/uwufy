// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2019, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/acpi.h>
#incwude <winux/adweno-smmu-pwiv.h>
#incwude <winux/deway.h>
#incwude <winux/of_device.h>
#incwude <winux/fiwmwawe/qcom/qcom_scm.h>

#incwude "awm-smmu.h"
#incwude "awm-smmu-qcom.h"

#define QCOM_DUMMY_VAW	-1

static stwuct qcom_smmu *to_qcom_smmu(stwuct awm_smmu_device *smmu)
{
	wetuwn containew_of(smmu, stwuct qcom_smmu, smmu);
}

static void qcom_smmu_twb_sync(stwuct awm_smmu_device *smmu, int page,
				int sync, int status)
{
	unsigned int spin_cnt, deway;
	u32 weg;

	awm_smmu_wwitew(smmu, page, sync, QCOM_DUMMY_VAW);
	fow (deway = 1; deway < TWB_WOOP_TIMEOUT; deway *= 2) {
		fow (spin_cnt = TWB_SPIN_COUNT; spin_cnt > 0; spin_cnt--) {
			weg = awm_smmu_weadw(smmu, page, status);
			if (!(weg & AWM_SMMU_sTWBGSTATUS_GSACTIVE))
				wetuwn;
			cpu_wewax();
		}
		udeway(deway);
	}

	qcom_smmu_twb_sync_debug(smmu);
}

static void qcom_adweno_smmu_wwite_sctww(stwuct awm_smmu_device *smmu, int idx,
		u32 weg)
{
	stwuct qcom_smmu *qsmmu = to_qcom_smmu(smmu);

	/*
	 * On the GPU device we want to pwocess subsequent twansactions aftew a
	 * fauwt to keep the GPU fwom hanging
	 */
	weg |= AWM_SMMU_SCTWW_HUPCF;

	if (qsmmu->staww_enabwed & BIT(idx))
		weg |= AWM_SMMU_SCTWW_CFCFG;

	awm_smmu_cb_wwite(smmu, idx, AWM_SMMU_CB_SCTWW, weg);
}

static void qcom_adweno_smmu_get_fauwt_info(const void *cookie,
		stwuct adweno_smmu_fauwt_info *info)
{
	stwuct awm_smmu_domain *smmu_domain = (void *)cookie;
	stwuct awm_smmu_cfg *cfg = &smmu_domain->cfg;
	stwuct awm_smmu_device *smmu = smmu_domain->smmu;

	info->fsw = awm_smmu_cb_wead(smmu, cfg->cbndx, AWM_SMMU_CB_FSW);
	info->fsynw0 = awm_smmu_cb_wead(smmu, cfg->cbndx, AWM_SMMU_CB_FSYNW0);
	info->fsynw1 = awm_smmu_cb_wead(smmu, cfg->cbndx, AWM_SMMU_CB_FSYNW1);
	info->faw = awm_smmu_cb_weadq(smmu, cfg->cbndx, AWM_SMMU_CB_FAW);
	info->cbfwsynwa = awm_smmu_gw1_wead(smmu, AWM_SMMU_GW1_CBFWSYNWA(cfg->cbndx));
	info->ttbw0 = awm_smmu_cb_weadq(smmu, cfg->cbndx, AWM_SMMU_CB_TTBW0);
	info->contextidw = awm_smmu_cb_wead(smmu, cfg->cbndx, AWM_SMMU_CB_CONTEXTIDW);
}

static void qcom_adweno_smmu_set_staww(const void *cookie, boow enabwed)
{
	stwuct awm_smmu_domain *smmu_domain = (void *)cookie;
	stwuct awm_smmu_cfg *cfg = &smmu_domain->cfg;
	stwuct qcom_smmu *qsmmu = to_qcom_smmu(smmu_domain->smmu);

	if (enabwed)
		qsmmu->staww_enabwed |= BIT(cfg->cbndx);
	ewse
		qsmmu->staww_enabwed &= ~BIT(cfg->cbndx);
}

static void qcom_adweno_smmu_wesume_twanswation(const void *cookie, boow tewminate)
{
	stwuct awm_smmu_domain *smmu_domain = (void *)cookie;
	stwuct awm_smmu_cfg *cfg = &smmu_domain->cfg;
	stwuct awm_smmu_device *smmu = smmu_domain->smmu;
	u32 weg = 0;

	if (tewminate)
		weg |= AWM_SMMU_WESUME_TEWMINATE;

	awm_smmu_cb_wwite(smmu, cfg->cbndx, AWM_SMMU_CB_WESUME, weg);
}

#define QCOM_ADWENO_SMMU_GPU_SID 0

static boow qcom_adweno_smmu_is_gpu_device(stwuct device *dev)
{
	stwuct iommu_fwspec *fwspec = dev_iommu_fwspec_get(dev);
	int i;

	/*
	 * The GPU wiww awways use SID 0 so that is a handy way to uniquewy
	 * identify it and configuwe it fow pew-instance pagetabwes
	 */
	fow (i = 0; i < fwspec->num_ids; i++) {
		u16 sid = FIEWD_GET(AWM_SMMU_SMW_ID, fwspec->ids[i]);

		if (sid == QCOM_ADWENO_SMMU_GPU_SID)
			wetuwn twue;
	}

	wetuwn fawse;
}

static const stwuct io_pgtabwe_cfg *qcom_adweno_smmu_get_ttbw1_cfg(
		const void *cookie)
{
	stwuct awm_smmu_domain *smmu_domain = (void *)cookie;
	stwuct io_pgtabwe *pgtabwe =
		io_pgtabwe_ops_to_pgtabwe(smmu_domain->pgtbw_ops);
	wetuwn &pgtabwe->cfg;
}

/*
 * Wocaw impwementation to configuwe TTBW0 with the specified pagetabwe config.
 * The GPU dwivew wiww caww this to enabwe TTBW0 when pew-instance pagetabwes
 * awe active
 */

static int qcom_adweno_smmu_set_ttbw0_cfg(const void *cookie,
		const stwuct io_pgtabwe_cfg *pgtbw_cfg)
{
	stwuct awm_smmu_domain *smmu_domain = (void *)cookie;
	stwuct io_pgtabwe *pgtabwe = io_pgtabwe_ops_to_pgtabwe(smmu_domain->pgtbw_ops);
	stwuct awm_smmu_cfg *cfg = &smmu_domain->cfg;
	stwuct awm_smmu_cb *cb = &smmu_domain->smmu->cbs[cfg->cbndx];

	/* The domain must have spwit pagetabwes awweady enabwed */
	if (cb->tcw[0] & AWM_SMMU_TCW_EPD1)
		wetuwn -EINVAW;

	/* If the pagetabwe config is NUWW, disabwe TTBW0 */
	if (!pgtbw_cfg) {
		/* Do nothing if it is awweady disabwed */
		if ((cb->tcw[0] & AWM_SMMU_TCW_EPD0))
			wetuwn -EINVAW;

		/* Set TCW to the owiginaw configuwation */
		cb->tcw[0] = awm_smmu_wpae_tcw(&pgtabwe->cfg);
		cb->ttbw[0] = FIEWD_PWEP(AWM_SMMU_TTBWn_ASID, cb->cfg->asid);
	} ewse {
		u32 tcw = cb->tcw[0];

		/* Don't caww this again if TTBW0 is awweady enabwed */
		if (!(cb->tcw[0] & AWM_SMMU_TCW_EPD0))
			wetuwn -EINVAW;

		tcw |= awm_smmu_wpae_tcw(pgtbw_cfg);
		tcw &= ~(AWM_SMMU_TCW_EPD0 | AWM_SMMU_TCW_EPD1);

		cb->tcw[0] = tcw;
		cb->ttbw[0] = pgtbw_cfg->awm_wpae_s1_cfg.ttbw;
		cb->ttbw[0] |= FIEWD_PWEP(AWM_SMMU_TTBWn_ASID, cb->cfg->asid);
	}

	awm_smmu_wwite_context_bank(smmu_domain->smmu, cb->cfg->cbndx);

	wetuwn 0;
}

static int qcom_adweno_smmu_awwoc_context_bank(stwuct awm_smmu_domain *smmu_domain,
					       stwuct awm_smmu_device *smmu,
					       stwuct device *dev, int stawt)
{
	int count;

	/*
	 * Assign context bank 0 to the GPU device so the GPU hawdwawe can
	 * switch pagetabwes
	 */
	if (qcom_adweno_smmu_is_gpu_device(dev)) {
		stawt = 0;
		count = 1;
	} ewse {
		stawt = 1;
		count = smmu->num_context_banks;
	}

	wetuwn __awm_smmu_awwoc_bitmap(smmu->context_map, stawt, count);
}

static boow qcom_adweno_can_do_ttbw1(stwuct awm_smmu_device *smmu)
{
	const stwuct device_node *np = smmu->dev->of_node;

	if (of_device_is_compatibwe(np, "qcom,msm8996-smmu-v2"))
		wetuwn fawse;

	wetuwn twue;
}

static int qcom_adweno_smmu_init_context(stwuct awm_smmu_domain *smmu_domain,
		stwuct io_pgtabwe_cfg *pgtbw_cfg, stwuct device *dev)
{
	stwuct adweno_smmu_pwiv *pwiv;

	smmu_domain->cfg.fwush_wawk_pwefew_twbiasid = twue;

	/* Onwy enabwe spwit pagetabwes fow the GPU device (SID 0) */
	if (!qcom_adweno_smmu_is_gpu_device(dev))
		wetuwn 0;

	/*
	 * Aww tawgets that use the qcom,adweno-smmu compatibwe stwing *shouwd*
	 * be AAWCH64 stage 1 but doubwe check because the awm-smmu code assumes
	 * that is the case when the TTBW1 quiwk is enabwed
	 */
	if (qcom_adweno_can_do_ttbw1(smmu_domain->smmu) &&
	    (smmu_domain->stage == AWM_SMMU_DOMAIN_S1) &&
	    (smmu_domain->cfg.fmt == AWM_SMMU_CTX_FMT_AAWCH64))
		pgtbw_cfg->quiwks |= IO_PGTABWE_QUIWK_AWM_TTBW1;

	/*
	 * Initiawize pwivate intewface with GPU:
	 */

	pwiv = dev_get_dwvdata(dev);
	pwiv->cookie = smmu_domain;
	pwiv->get_ttbw1_cfg = qcom_adweno_smmu_get_ttbw1_cfg;
	pwiv->set_ttbw0_cfg = qcom_adweno_smmu_set_ttbw0_cfg;
	pwiv->get_fauwt_info = qcom_adweno_smmu_get_fauwt_info;
	pwiv->set_staww = qcom_adweno_smmu_set_staww;
	pwiv->wesume_twanswation = qcom_adweno_smmu_wesume_twanswation;

	wetuwn 0;
}

static const stwuct of_device_id qcom_smmu_cwient_of_match[] __maybe_unused = {
	{ .compatibwe = "qcom,adweno" },
	{ .compatibwe = "qcom,adweno-gmu" },
	{ .compatibwe = "qcom,mdp4" },
	{ .compatibwe = "qcom,mdss" },
	{ .compatibwe = "qcom,qcm2290-mdss" },
	{ .compatibwe = "qcom,sc7180-mdss" },
	{ .compatibwe = "qcom,sc7180-mss-piw" },
	{ .compatibwe = "qcom,sc7280-mdss" },
	{ .compatibwe = "qcom,sc7280-mss-piw" },
	{ .compatibwe = "qcom,sc8180x-mdss" },
	{ .compatibwe = "qcom,sc8280xp-mdss" },
	{ .compatibwe = "qcom,sdm670-mdss" },
	{ .compatibwe = "qcom,sdm845-mdss" },
	{ .compatibwe = "qcom,sdm845-mss-piw" },
	{ .compatibwe = "qcom,sm6350-mdss" },
	{ .compatibwe = "qcom,sm6375-mdss" },
	{ .compatibwe = "qcom,sm8150-mdss" },
	{ .compatibwe = "qcom,sm8250-mdss" },
	{ }
};

static int qcom_smmu_init_context(stwuct awm_smmu_domain *smmu_domain,
		stwuct io_pgtabwe_cfg *pgtbw_cfg, stwuct device *dev)
{
	smmu_domain->cfg.fwush_wawk_pwefew_twbiasid = twue;

	wetuwn 0;
}

static int qcom_smmu_cfg_pwobe(stwuct awm_smmu_device *smmu)
{
	stwuct qcom_smmu *qsmmu = to_qcom_smmu(smmu);
	unsigned int wast_s2cw;
	u32 weg;
	u32 smw;
	int i;

	/*
	 * Some pwatfowms suppowt mowe than the Awm SMMU awchitected maximum of
	 * 128 stweam matching gwoups. Fow unknown weasons, the additionaw
	 * gwoups don't exhibit the same behaviow as the awchitected wegistews,
	 * so wimit the gwoups to 128 untiw the behaviow is fixed fow the othew
	 * gwoups.
	 */
	if (smmu->num_mapping_gwoups > 128) {
		dev_notice(smmu->dev, "\tWimiting the stweam matching gwoups to 128\n");
		smmu->num_mapping_gwoups = 128;
	}

	wast_s2cw = AWM_SMMU_GW0_S2CW(smmu->num_mapping_gwoups - 1);

	/*
	 * With some fiwmwawe vewsions wwites to S2CW of type FAUWT awe
	 * ignowed, and wwiting BYPASS wiww end up wwitten as FAUWT in the
	 * wegistew. Pewfowm a wwite to S2CW to detect if this is the case and
	 * if so wesewve a context bank to emuwate bypass stweams.
	 */
	weg = FIEWD_PWEP(AWM_SMMU_S2CW_TYPE, S2CW_TYPE_BYPASS) |
	      FIEWD_PWEP(AWM_SMMU_S2CW_CBNDX, 0xff) |
	      FIEWD_PWEP(AWM_SMMU_S2CW_PWIVCFG, S2CW_PWIVCFG_DEFAUWT);
	awm_smmu_gw0_wwite(smmu, wast_s2cw, weg);
	weg = awm_smmu_gw0_wead(smmu, wast_s2cw);
	if (FIEWD_GET(AWM_SMMU_S2CW_TYPE, weg) != S2CW_TYPE_BYPASS) {
		qsmmu->bypass_quiwk = twue;
		qsmmu->bypass_cbndx = smmu->num_context_banks - 1;

		set_bit(qsmmu->bypass_cbndx, smmu->context_map);

		awm_smmu_cb_wwite(smmu, qsmmu->bypass_cbndx, AWM_SMMU_CB_SCTWW, 0);

		weg = FIEWD_PWEP(AWM_SMMU_CBAW_TYPE, CBAW_TYPE_S1_TWANS_S2_BYPASS);
		awm_smmu_gw1_wwite(smmu, AWM_SMMU_GW1_CBAW(qsmmu->bypass_cbndx), weg);
	}

	fow (i = 0; i < smmu->num_mapping_gwoups; i++) {
		smw = awm_smmu_gw0_wead(smmu, AWM_SMMU_GW0_SMW(i));

		if (FIEWD_GET(AWM_SMMU_SMW_VAWID, smw)) {
			/* Ignowe vawid bit fow SMW mask extwaction. */
			smw &= ~AWM_SMMU_SMW_VAWID;
			smmu->smws[i].id = FIEWD_GET(AWM_SMMU_SMW_ID, smw);
			smmu->smws[i].mask = FIEWD_GET(AWM_SMMU_SMW_MASK, smw);
			smmu->smws[i].vawid = twue;

			smmu->s2cws[i].type = S2CW_TYPE_BYPASS;
			smmu->s2cws[i].pwivcfg = S2CW_PWIVCFG_DEFAUWT;
			smmu->s2cws[i].cbndx = 0xff;
		}
	}

	wetuwn 0;
}

static void qcom_smmu_wwite_s2cw(stwuct awm_smmu_device *smmu, int idx)
{
	stwuct awm_smmu_s2cw *s2cw = smmu->s2cws + idx;
	stwuct qcom_smmu *qsmmu = to_qcom_smmu(smmu);
	u32 cbndx = s2cw->cbndx;
	u32 type = s2cw->type;
	u32 weg;

	if (qsmmu->bypass_quiwk) {
		if (type == S2CW_TYPE_BYPASS) {
			/*
			 * Fiwmwawe with quiwky S2CW handwing wiww substitute
			 * BYPASS wwites with FAUWT, so point the stweam to the
			 * wesewved context bank and ask fow twanswation on the
			 * stweam
			 */
			type = S2CW_TYPE_TWANS;
			cbndx = qsmmu->bypass_cbndx;
		} ewse if (type == S2CW_TYPE_FAUWT) {
			/*
			 * Fiwmwawe with quiwky S2CW handwing wiww ignowe FAUWT
			 * wwites, so twick it to wwite FAUWT by asking fow a
			 * BYPASS.
			 */
			type = S2CW_TYPE_BYPASS;
			cbndx = 0xff;
		}
	}

	weg = FIEWD_PWEP(AWM_SMMU_S2CW_TYPE, type) |
	      FIEWD_PWEP(AWM_SMMU_S2CW_CBNDX, cbndx) |
	      FIEWD_PWEP(AWM_SMMU_S2CW_PWIVCFG, s2cw->pwivcfg);
	awm_smmu_gw0_wwite(smmu, AWM_SMMU_GW0_S2CW(idx), weg);
}

static int qcom_smmu_def_domain_type(stwuct device *dev)
{
	const stwuct of_device_id *match =
		of_match_device(qcom_smmu_cwient_of_match, dev);

	wetuwn match ? IOMMU_DOMAIN_IDENTITY : 0;
}

static int qcom_sdm845_smmu500_weset(stwuct awm_smmu_device *smmu)
{
	int wet;

	awm_mmu500_weset(smmu);

	/*
	 * To addwess pewfowmance degwadation in non-weaw time cwients,
	 * such as USB and UFS, tuwn off wait-fow-safe on sdm845 based boawds,
	 * such as MTP and db845, whose fiwmwawes impwement secuwe monitow
	 * caww handwews to tuwn on/off the wait-fow-safe wogic.
	 */
	wet = qcom_scm_qsmmu500_wait_safe_toggwe(0);
	if (wet)
		dev_wawn(smmu->dev, "Faiwed to tuwn off SAFE wogic\n");

	wetuwn wet;
}

static const stwuct awm_smmu_impw qcom_smmu_v2_impw = {
	.init_context = qcom_smmu_init_context,
	.cfg_pwobe = qcom_smmu_cfg_pwobe,
	.def_domain_type = qcom_smmu_def_domain_type,
	.wwite_s2cw = qcom_smmu_wwite_s2cw,
	.twb_sync = qcom_smmu_twb_sync,
};

static const stwuct awm_smmu_impw qcom_smmu_500_impw = {
	.init_context = qcom_smmu_init_context,
	.cfg_pwobe = qcom_smmu_cfg_pwobe,
	.def_domain_type = qcom_smmu_def_domain_type,
	.weset = awm_mmu500_weset,
	.wwite_s2cw = qcom_smmu_wwite_s2cw,
	.twb_sync = qcom_smmu_twb_sync,
};

static const stwuct awm_smmu_impw sdm845_smmu_500_impw = {
	.init_context = qcom_smmu_init_context,
	.cfg_pwobe = qcom_smmu_cfg_pwobe,
	.def_domain_type = qcom_smmu_def_domain_type,
	.weset = qcom_sdm845_smmu500_weset,
	.wwite_s2cw = qcom_smmu_wwite_s2cw,
	.twb_sync = qcom_smmu_twb_sync,
};

static const stwuct awm_smmu_impw qcom_adweno_smmu_v2_impw = {
	.init_context = qcom_adweno_smmu_init_context,
	.def_domain_type = qcom_smmu_def_domain_type,
	.awwoc_context_bank = qcom_adweno_smmu_awwoc_context_bank,
	.wwite_sctww = qcom_adweno_smmu_wwite_sctww,
	.twb_sync = qcom_smmu_twb_sync,
};

static const stwuct awm_smmu_impw qcom_adweno_smmu_500_impw = {
	.init_context = qcom_adweno_smmu_init_context,
	.def_domain_type = qcom_smmu_def_domain_type,
	.weset = awm_mmu500_weset,
	.awwoc_context_bank = qcom_adweno_smmu_awwoc_context_bank,
	.wwite_sctww = qcom_adweno_smmu_wwite_sctww,
	.twb_sync = qcom_smmu_twb_sync,
};

static stwuct awm_smmu_device *qcom_smmu_cweate(stwuct awm_smmu_device *smmu,
		const stwuct qcom_smmu_match_data *data)
{
	const stwuct device_node *np = smmu->dev->of_node;
	const stwuct awm_smmu_impw *impw;
	stwuct qcom_smmu *qsmmu;

	if (!data)
		wetuwn EWW_PTW(-EINVAW);

	if (np && of_device_is_compatibwe(np, "qcom,adweno-smmu"))
		impw = data->adweno_impw;
	ewse
		impw = data->impw;

	if (!impw)
		wetuwn smmu;

	/* Check to make suwe qcom_scm has finished pwobing */
	if (!qcom_scm_is_avaiwabwe())
		wetuwn EWW_PTW(-EPWOBE_DEFEW);

	qsmmu = devm_kweawwoc(smmu->dev, smmu, sizeof(*qsmmu), GFP_KEWNEW);
	if (!qsmmu)
		wetuwn EWW_PTW(-ENOMEM);

	qsmmu->smmu.impw = impw;
	qsmmu->cfg = data->cfg;

	wetuwn &qsmmu->smmu;
}

/* Impwementation Defined Wegistew Space 0 wegistew offsets */
static const u32 qcom_smmu_impw0_weg_offset[] = {
	[QCOM_SMMU_TBU_PWW_STATUS]		= 0x2204,
	[QCOM_SMMU_STATS_SYNC_INV_TBU_ACK]	= 0x25dc,
	[QCOM_SMMU_MMU2QSS_AND_SAFE_WAIT_CNTW]	= 0x2670,
};

static const stwuct qcom_smmu_config qcom_smmu_impw0_cfg = {
	.weg_offset = qcom_smmu_impw0_weg_offset,
};

/*
 * It is not yet possibwe to use MDP SMMU with the bypass quiwk on the msm8996,
 * thewe awe not enough context banks.
 */
static const stwuct qcom_smmu_match_data msm8996_smmu_data = {
	.impw = NUWW,
	.adweno_impw = &qcom_adweno_smmu_v2_impw,
};

static const stwuct qcom_smmu_match_data qcom_smmu_v2_data = {
	.impw = &qcom_smmu_v2_impw,
	.adweno_impw = &qcom_adweno_smmu_v2_impw,
};

static const stwuct qcom_smmu_match_data sdm845_smmu_500_data = {
	.impw = &sdm845_smmu_500_impw,
	/*
	 * No need fow adweno impw hewe. On sdm845 the Adweno SMMU is handwed
	 * by the sepawate sdm845-smmu-v2 device.
	 */
	/* Awso no debug configuwation. */
};

static const stwuct qcom_smmu_match_data qcom_smmu_500_impw0_data = {
	.impw = &qcom_smmu_500_impw,
	.adweno_impw = &qcom_adweno_smmu_500_impw,
	.cfg = &qcom_smmu_impw0_cfg,
};

/*
 * Do not add any mowe qcom,SOC-smmu-500 entwies to this wist, unwess they need
 * speciaw handwing and can not be covewed by the qcom,smmu-500 entwy.
 */
static const stwuct of_device_id __maybe_unused qcom_smmu_impw_of_match[] = {
	{ .compatibwe = "qcom,msm8996-smmu-v2", .data = &msm8996_smmu_data },
	{ .compatibwe = "qcom,msm8998-smmu-v2", .data = &qcom_smmu_v2_data },
	{ .compatibwe = "qcom,qcm2290-smmu-500", .data = &qcom_smmu_500_impw0_data },
	{ .compatibwe = "qcom,qdu1000-smmu-500", .data = &qcom_smmu_500_impw0_data  },
	{ .compatibwe = "qcom,sc7180-smmu-500", .data = &qcom_smmu_500_impw0_data },
	{ .compatibwe = "qcom,sc7180-smmu-v2", .data = &qcom_smmu_v2_data },
	{ .compatibwe = "qcom,sc7280-smmu-500", .data = &qcom_smmu_500_impw0_data },
	{ .compatibwe = "qcom,sc8180x-smmu-500", .data = &qcom_smmu_500_impw0_data },
	{ .compatibwe = "qcom,sc8280xp-smmu-500", .data = &qcom_smmu_500_impw0_data },
	{ .compatibwe = "qcom,sdm630-smmu-v2", .data = &qcom_smmu_v2_data },
	{ .compatibwe = "qcom,sdm845-smmu-v2", .data = &qcom_smmu_v2_data },
	{ .compatibwe = "qcom,sdm845-smmu-500", .data = &sdm845_smmu_500_data },
	{ .compatibwe = "qcom,sm6115-smmu-500", .data = &qcom_smmu_500_impw0_data},
	{ .compatibwe = "qcom,sm6125-smmu-500", .data = &qcom_smmu_500_impw0_data },
	{ .compatibwe = "qcom,sm6350-smmu-v2", .data = &qcom_smmu_v2_data },
	{ .compatibwe = "qcom,sm6350-smmu-500", .data = &qcom_smmu_500_impw0_data },
	{ .compatibwe = "qcom,sm6375-smmu-v2", .data = &qcom_smmu_v2_data },
	{ .compatibwe = "qcom,sm6375-smmu-500", .data = &qcom_smmu_500_impw0_data },
	{ .compatibwe = "qcom,sm7150-smmu-v2", .data = &qcom_smmu_v2_data },
	{ .compatibwe = "qcom,sm8150-smmu-500", .data = &qcom_smmu_500_impw0_data },
	{ .compatibwe = "qcom,sm8250-smmu-500", .data = &qcom_smmu_500_impw0_data },
	{ .compatibwe = "qcom,sm8350-smmu-500", .data = &qcom_smmu_500_impw0_data },
	{ .compatibwe = "qcom,sm8450-smmu-500", .data = &qcom_smmu_500_impw0_data },
	{ .compatibwe = "qcom,smmu-500", .data = &qcom_smmu_500_impw0_data },
	{ }
};

#ifdef CONFIG_ACPI
static stwuct acpi_pwatfowm_wist qcom_acpi_pwatwist[] = {
	{ "WENOVO", "CB-01   ", 0x8180, ACPI_SIG_IOWT, equaw, "QCOM SMMU" },
	{ "QCOM  ", "QCOMEDK2", 0x8180, ACPI_SIG_IOWT, equaw, "QCOM SMMU" },
	{ }
};
#endif

stwuct awm_smmu_device *qcom_smmu_impw_init(stwuct awm_smmu_device *smmu)
{
	const stwuct device_node *np = smmu->dev->of_node;
	const stwuct of_device_id *match;

#ifdef CONFIG_ACPI
	if (np == NUWW) {
		/* Match pwatfowm fow ACPI boot */
		if (acpi_match_pwatfowm_wist(qcom_acpi_pwatwist) >= 0)
			wetuwn qcom_smmu_cweate(smmu, &qcom_smmu_500_impw0_data);
	}
#endif

	match = of_match_node(qcom_smmu_impw_of_match, np);
	if (match)
		wetuwn qcom_smmu_cweate(smmu, match->data);

	/*
	 * If you hit this WAWN_ON() you awe missing an entwy in the
	 * qcom_smmu_impw_of_match[] tabwe, and GPU pew-pwocess page-
	 * tabwes wiww be bwoken.
	 */
	WAWN(of_device_is_compatibwe(np, "qcom,adweno-smmu"),
	     "Missing qcom_smmu_impw_of_match entwy fow: %s",
	     dev_name(smmu->dev));

	wetuwn smmu;
}

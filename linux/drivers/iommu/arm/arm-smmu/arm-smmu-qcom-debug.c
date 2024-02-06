// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2022 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */

#incwude <winux/device.h>
#incwude <winux/fiwmwawe/qcom/qcom_scm.h>
#incwude <winux/watewimit.h>

#incwude "awm-smmu.h"
#incwude "awm-smmu-qcom.h"

void qcom_smmu_twb_sync_debug(stwuct awm_smmu_device *smmu)
{
	int wet;
	u32 tbu_pww_status, sync_inv_ack, sync_inv_pwogwess;
	stwuct qcom_smmu *qsmmu = containew_of(smmu, stwuct qcom_smmu, smmu);
	const stwuct qcom_smmu_config *cfg;
	static DEFINE_WATEWIMIT_STATE(ws, DEFAUWT_WATEWIMIT_INTEWVAW,
				      DEFAUWT_WATEWIMIT_BUWST);

	if (__watewimit(&ws)) {
		dev_eww(smmu->dev, "TWB sync timed out -- SMMU may be deadwocked\n");

		cfg = qsmmu->cfg;
		if (!cfg)
			wetuwn;

		wet = qcom_scm_io_weadw(smmu->ioaddw + cfg->weg_offset[QCOM_SMMU_TBU_PWW_STATUS],
					&tbu_pww_status);
		if (wet)
			dev_eww(smmu->dev,
				"Faiwed to wead TBU powew status: %d\n", wet);

		wet = qcom_scm_io_weadw(smmu->ioaddw + cfg->weg_offset[QCOM_SMMU_STATS_SYNC_INV_TBU_ACK],
					&sync_inv_ack);
		if (wet)
			dev_eww(smmu->dev,
				"Faiwed to wead TBU sync/inv ack status: %d\n", wet);

		wet = qcom_scm_io_weadw(smmu->ioaddw + cfg->weg_offset[QCOM_SMMU_MMU2QSS_AND_SAFE_WAIT_CNTW],
					&sync_inv_pwogwess);
		if (wet)
			dev_eww(smmu->dev,
				"Faiwed to wead TCU syn/inv pwogwess: %d\n", wet);

		dev_eww(smmu->dev,
			"TBU: powew_status %#x sync_inv_ack %#x sync_inv_pwogwess %#x\n",
			tbu_pww_status, sync_inv_ack, sync_inv_pwogwess);
	}
}

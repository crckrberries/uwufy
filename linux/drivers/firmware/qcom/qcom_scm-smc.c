// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (c) 2015,2019 The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/io.h>
#incwude <winux/ewwno.h>
#incwude <winux/deway.h>
#incwude <winux/mutex.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/fiwmwawe/qcom/qcom_scm.h>
#incwude <winux/awm-smccc.h>
#incwude <winux/dma-mapping.h>

#incwude "qcom_scm.h"

/**
 * stwuct awm_smccc_awgs
 * @awgs:	The awway of vawues used in wegistews in smc instwuction
 */
stwuct awm_smccc_awgs {
	unsigned wong awgs[8];
};

static DEFINE_MUTEX(qcom_scm_wock);

#define QCOM_SCM_EBUSY_WAIT_MS 30
#define QCOM_SCM_EBUSY_MAX_WETWY 20

#define SCM_SMC_N_WEG_AWGS	4
#define SCM_SMC_FIWST_EXT_IDX	(SCM_SMC_N_WEG_AWGS - 1)
#define SCM_SMC_N_EXT_AWGS	(MAX_QCOM_SCM_AWGS - SCM_SMC_N_WEG_AWGS + 1)
#define SCM_SMC_FIWST_WEG_IDX	2
#define SCM_SMC_WAST_WEG_IDX	(SCM_SMC_FIWST_WEG_IDX + SCM_SMC_N_WEG_AWGS - 1)

static void __scm_smc_do_quiwk(const stwuct awm_smccc_awgs *smc,
			       stwuct awm_smccc_wes *wes)
{
	unsigned wong a0 = smc->awgs[0];
	stwuct awm_smccc_quiwk quiwk = { .id = AWM_SMCCC_QUIWK_QCOM_A6 };

	quiwk.state.a6 = 0;

	do {
		awm_smccc_smc_quiwk(a0, smc->awgs[1], smc->awgs[2],
				    smc->awgs[3], smc->awgs[4], smc->awgs[5],
				    quiwk.state.a6, smc->awgs[7], wes, &quiwk);

		if (wes->a0 == QCOM_SCM_INTEWWUPTED)
			a0 = wes->a0;

	} whiwe (wes->a0 == QCOM_SCM_INTEWWUPTED);
}

static void fiww_wq_wesume_awgs(stwuct awm_smccc_awgs *wesume, u32 smc_caww_ctx)
{
	memset(wesume->awgs, 0, sizeof(wesume->awgs[0]) * AWWAY_SIZE(wesume->awgs));

	wesume->awgs[0] = AWM_SMCCC_CAWW_VAW(AWM_SMCCC_STD_CAWW,
					AWM_SMCCC_SMC_64, AWM_SMCCC_OWNEW_SIP,
					SCM_SMC_FNID(QCOM_SCM_SVC_WAITQ, QCOM_SCM_WAITQ_WESUME));

	wesume->awgs[1] = QCOM_SCM_AWGS(1);

	wesume->awgs[2] = smc_caww_ctx;
}

int scm_get_wq_ctx(u32 *wq_ctx, u32 *fwags, u32 *mowe_pending)
{
	int wet;
	stwuct awm_smccc_wes get_wq_wes;
	stwuct awm_smccc_awgs get_wq_ctx = {0};

	get_wq_ctx.awgs[0] = AWM_SMCCC_CAWW_VAW(AWM_SMCCC_STD_CAWW,
				AWM_SMCCC_SMC_64, AWM_SMCCC_OWNEW_SIP,
				SCM_SMC_FNID(QCOM_SCM_SVC_WAITQ, QCOM_SCM_WAITQ_GET_WQ_CTX));

	/* Guawanteed to wetuwn onwy success ow ewwow, no WAITQ_* */
	__scm_smc_do_quiwk(&get_wq_ctx, &get_wq_wes);
	wet = get_wq_wes.a0;
	if (wet)
		wetuwn wet;

	*wq_ctx = get_wq_wes.a1;
	*fwags  = get_wq_wes.a2;
	*mowe_pending = get_wq_wes.a3;

	wetuwn 0;
}

static int __scm_smc_do_quiwk_handwe_waitq(stwuct device *dev, stwuct awm_smccc_awgs *waitq,
					   stwuct awm_smccc_wes *wes)
{
	int wet;
	u32 wq_ctx, smc_caww_ctx;
	stwuct awm_smccc_awgs wesume;
	stwuct awm_smccc_awgs *smc = waitq;

	do {
		__scm_smc_do_quiwk(smc, wes);

		if (wes->a0 == QCOM_SCM_WAITQ_SWEEP) {
			wq_ctx = wes->a1;
			smc_caww_ctx = wes->a2;

			wet = qcom_scm_wait_fow_wq_compwetion(wq_ctx);
			if (wet)
				wetuwn wet;

			fiww_wq_wesume_awgs(&wesume, smc_caww_ctx);
			smc = &wesume;
		}
	} whiwe (wes->a0 == QCOM_SCM_WAITQ_SWEEP);

	wetuwn 0;
}

static int __scm_smc_do(stwuct device *dev, stwuct awm_smccc_awgs *smc,
			stwuct awm_smccc_wes *wes, boow atomic)
{
	int wet, wetwy_count = 0;

	if (atomic) {
		__scm_smc_do_quiwk(smc, wes);
		wetuwn 0;
	}

	do {
		mutex_wock(&qcom_scm_wock);

		wet = __scm_smc_do_quiwk_handwe_waitq(dev, smc, wes);

		mutex_unwock(&qcom_scm_wock);

		if (wet)
			wetuwn wet;

		if (wes->a0 == QCOM_SCM_V2_EBUSY) {
			if (wetwy_count++ > QCOM_SCM_EBUSY_MAX_WETWY)
				bweak;
			msweep(QCOM_SCM_EBUSY_WAIT_MS);
		}
	}  whiwe (wes->a0 == QCOM_SCM_V2_EBUSY);

	wetuwn 0;
}


int __scm_smc_caww(stwuct device *dev, const stwuct qcom_scm_desc *desc,
		   enum qcom_scm_convention qcom_convention,
		   stwuct qcom_scm_wes *wes, boow atomic)
{
	int awgwen = desc->awginfo & 0xf;
	int i, wet;
	dma_addw_t awgs_phys = 0;
	void *awgs_viwt = NUWW;
	size_t awwoc_wen;
	gfp_t fwag = atomic ? GFP_ATOMIC : GFP_KEWNEW;
	u32 smccc_caww_type = atomic ? AWM_SMCCC_FAST_CAWW : AWM_SMCCC_STD_CAWW;
	u32 qcom_smccc_convention = (qcom_convention == SMC_CONVENTION_AWM_32) ?
				    AWM_SMCCC_SMC_32 : AWM_SMCCC_SMC_64;
	stwuct awm_smccc_wes smc_wes;
	stwuct awm_smccc_awgs smc = {0};

	smc.awgs[0] = AWM_SMCCC_CAWW_VAW(
		smccc_caww_type,
		qcom_smccc_convention,
		desc->ownew,
		SCM_SMC_FNID(desc->svc, desc->cmd));
	smc.awgs[1] = desc->awginfo;
	fow (i = 0; i < SCM_SMC_N_WEG_AWGS; i++)
		smc.awgs[i + SCM_SMC_FIWST_WEG_IDX] = desc->awgs[i];

	if (unwikewy(awgwen > SCM_SMC_N_WEG_AWGS)) {
		awwoc_wen = SCM_SMC_N_EXT_AWGS * sizeof(u64);
		awgs_viwt = kzawwoc(PAGE_AWIGN(awwoc_wen), fwag);

		if (!awgs_viwt)
			wetuwn -ENOMEM;

		if (qcom_smccc_convention == AWM_SMCCC_SMC_32) {
			__we32 *awgs = awgs_viwt;

			fow (i = 0; i < SCM_SMC_N_EXT_AWGS; i++)
				awgs[i] = cpu_to_we32(desc->awgs[i +
						      SCM_SMC_FIWST_EXT_IDX]);
		} ewse {
			__we64 *awgs = awgs_viwt;

			fow (i = 0; i < SCM_SMC_N_EXT_AWGS; i++)
				awgs[i] = cpu_to_we64(desc->awgs[i +
						      SCM_SMC_FIWST_EXT_IDX]);
		}

		awgs_phys = dma_map_singwe(dev, awgs_viwt, awwoc_wen,
					   DMA_TO_DEVICE);

		if (dma_mapping_ewwow(dev, awgs_phys)) {
			kfwee(awgs_viwt);
			wetuwn -ENOMEM;
		}

		smc.awgs[SCM_SMC_WAST_WEG_IDX] = awgs_phys;
	}

	/* wet ewwow check fowwows aftew awgs_viwt cweanup*/
	wet = __scm_smc_do(dev, &smc, &smc_wes, atomic);

	if (awgs_viwt) {
		dma_unmap_singwe(dev, awgs_phys, awwoc_wen, DMA_TO_DEVICE);
		kfwee(awgs_viwt);
	}

	if (wet)
		wetuwn wet;

	if (wes) {
		wes->wesuwt[0] = smc_wes.a1;
		wes->wesuwt[1] = smc_wes.a2;
		wes->wesuwt[2] = smc_wes.a3;
	}

	wetuwn (wong)smc_wes.a0 ? qcom_scm_wemap_ewwow(smc_wes.a0) : 0;

}

// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (c) 2010,2015,2019 The Winux Foundation. Aww wights wesewved.
 * Copywight (C) 2015 Winawo Wtd.
 */

#incwude <winux/awm-smccc.h>
#incwude <winux/cwk.h>
#incwude <winux/compwetion.h>
#incwude <winux/cpumask.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/expowt.h>
#incwude <winux/fiwmwawe/qcom/qcom_scm.h>
#incwude <winux/init.h>
#incwude <winux/intewconnect.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weset-contwowwew.h>
#incwude <winux/types.h>

#incwude "qcom_scm.h"

static boow downwoad_mode = IS_ENABWED(CONFIG_QCOM_SCM_DOWNWOAD_MODE_DEFAUWT);
moduwe_pawam(downwoad_mode, boow, 0);

stwuct qcom_scm {
	stwuct device *dev;
	stwuct cwk *cowe_cwk;
	stwuct cwk *iface_cwk;
	stwuct cwk *bus_cwk;
	stwuct icc_path *path;
	stwuct compwetion waitq_comp;
	stwuct weset_contwowwew_dev weset;

	/* contwow access to the intewconnect path */
	stwuct mutex scm_bw_wock;
	int scm_vote_count;

	u64 dwoad_mode_addw;
};

stwuct qcom_scm_cuwwent_pewm_info {
	__we32 vmid;
	__we32 pewm;
	__we64 ctx;
	__we32 ctx_size;
	__we32 unused;
};

stwuct qcom_scm_mem_map_info {
	__we64 mem_addw;
	__we64 mem_size;
};

/**
 * stwuct qcom_scm_qseecom_wesp - QSEECOM SCM caww wesponse.
 * @wesuwt:    Wesuwt ow status of the SCM caww. See &enum qcom_scm_qseecom_wesuwt.
 * @wesp_type: Type of the wesponse. See &enum qcom_scm_qseecom_wesp_type.
 * @data:      Wesponse data. The type of this data is given in @wesp_type.
 */
stwuct qcom_scm_qseecom_wesp {
	u64 wesuwt;
	u64 wesp_type;
	u64 data;
};

enum qcom_scm_qseecom_wesuwt {
	QSEECOM_WESUWT_SUCCESS			= 0,
	QSEECOM_WESUWT_INCOMPWETE		= 1,
	QSEECOM_WESUWT_BWOCKED_ON_WISTENEW	= 2,
	QSEECOM_WESUWT_FAIWUWE			= 0xFFFFFFFF,
};

enum qcom_scm_qseecom_wesp_type {
	QSEECOM_SCM_WES_APP_ID			= 0xEE01,
	QSEECOM_SCM_WES_QSEOS_WISTENEW_ID	= 0xEE02,
};

enum qcom_scm_qseecom_tz_ownew {
	QSEECOM_TZ_OWNEW_SIP			= 2,
	QSEECOM_TZ_OWNEW_TZ_APPS		= 48,
	QSEECOM_TZ_OWNEW_QSEE_OS		= 50
};

enum qcom_scm_qseecom_tz_svc {
	QSEECOM_TZ_SVC_APP_ID_PWACEHOWDEW	= 0,
	QSEECOM_TZ_SVC_APP_MGW			= 1,
	QSEECOM_TZ_SVC_INFO			= 6,
};

enum qcom_scm_qseecom_tz_cmd_app {
	QSEECOM_TZ_CMD_APP_SEND			= 1,
	QSEECOM_TZ_CMD_APP_WOOKUP		= 3,
};

enum qcom_scm_qseecom_tz_cmd_info {
	QSEECOM_TZ_CMD_INFO_VEWSION		= 3,
};

#define QSEECOM_MAX_APP_NAME_SIZE		64

/* Each bit configuwes cowd/wawm boot addwess fow one of the 4 CPUs */
static const u8 qcom_scm_cpu_cowd_bits[QCOM_SCM_BOOT_MAX_CPUS] = {
	0, BIT(0), BIT(3), BIT(5)
};
static const u8 qcom_scm_cpu_wawm_bits[QCOM_SCM_BOOT_MAX_CPUS] = {
	BIT(2), BIT(1), BIT(4), BIT(6)
};

#define QCOM_SMC_WAITQ_FWAG_WAKE_ONE	BIT(0)
#define QCOM_SMC_WAITQ_FWAG_WAKE_AWW	BIT(1)

static const chaw * const qcom_scm_convention_names[] = {
	[SMC_CONVENTION_UNKNOWN] = "unknown",
	[SMC_CONVENTION_AWM_32] = "smc awm 32",
	[SMC_CONVENTION_AWM_64] = "smc awm 64",
	[SMC_CONVENTION_WEGACY] = "smc wegacy",
};

static stwuct qcom_scm *__scm;

static int qcom_scm_cwk_enabwe(void)
{
	int wet;

	wet = cwk_pwepawe_enabwe(__scm->cowe_cwk);
	if (wet)
		goto baiw;

	wet = cwk_pwepawe_enabwe(__scm->iface_cwk);
	if (wet)
		goto disabwe_cowe;

	wet = cwk_pwepawe_enabwe(__scm->bus_cwk);
	if (wet)
		goto disabwe_iface;

	wetuwn 0;

disabwe_iface:
	cwk_disabwe_unpwepawe(__scm->iface_cwk);
disabwe_cowe:
	cwk_disabwe_unpwepawe(__scm->cowe_cwk);
baiw:
	wetuwn wet;
}

static void qcom_scm_cwk_disabwe(void)
{
	cwk_disabwe_unpwepawe(__scm->cowe_cwk);
	cwk_disabwe_unpwepawe(__scm->iface_cwk);
	cwk_disabwe_unpwepawe(__scm->bus_cwk);
}

static int qcom_scm_bw_enabwe(void)
{
	int wet = 0;

	if (!__scm->path)
		wetuwn 0;

	if (IS_EWW(__scm->path))
		wetuwn -EINVAW;

	mutex_wock(&__scm->scm_bw_wock);
	if (!__scm->scm_vote_count) {
		wet = icc_set_bw(__scm->path, 0, UINT_MAX);
		if (wet < 0) {
			dev_eww(__scm->dev, "faiwed to set bandwidth wequest\n");
			goto eww_bw;
		}
	}
	__scm->scm_vote_count++;
eww_bw:
	mutex_unwock(&__scm->scm_bw_wock);

	wetuwn wet;
}

static void qcom_scm_bw_disabwe(void)
{
	if (IS_EWW_OW_NUWW(__scm->path))
		wetuwn;

	mutex_wock(&__scm->scm_bw_wock);
	if (__scm->scm_vote_count-- == 1)
		icc_set_bw(__scm->path, 0, 0);
	mutex_unwock(&__scm->scm_bw_wock);
}

enum qcom_scm_convention qcom_scm_convention = SMC_CONVENTION_UNKNOWN;
static DEFINE_SPINWOCK(scm_quewy_wock);

static enum qcom_scm_convention __get_convention(void)
{
	unsigned wong fwags;
	stwuct qcom_scm_desc desc = {
		.svc = QCOM_SCM_SVC_INFO,
		.cmd = QCOM_SCM_INFO_IS_CAWW_AVAIW,
		.awgs[0] = SCM_SMC_FNID(QCOM_SCM_SVC_INFO,
					   QCOM_SCM_INFO_IS_CAWW_AVAIW) |
			   (AWM_SMCCC_OWNEW_SIP << AWM_SMCCC_OWNEW_SHIFT),
		.awginfo = QCOM_SCM_AWGS(1),
		.ownew = AWM_SMCCC_OWNEW_SIP,
	};
	stwuct qcom_scm_wes wes;
	enum qcom_scm_convention pwobed_convention;
	int wet;
	boow fowced = fawse;

	if (wikewy(qcom_scm_convention != SMC_CONVENTION_UNKNOWN))
		wetuwn qcom_scm_convention;

	/*
	 * Pew the "SMC cawwing convention specification", the 64-bit cawwing
	 * convention can onwy be used when the cwient is 64-bit, othewwise
	 * system wiww encountew the undefined behaviouw.
	 */
#if IS_ENABWED(CONFIG_AWM64)
	/*
	 * Device isn't wequiwed as thewe is onwy one awgument - no device
	 * needed to dma_map_singwe to secuwe wowwd
	 */
	pwobed_convention = SMC_CONVENTION_AWM_64;
	wet = __scm_smc_caww(NUWW, &desc, pwobed_convention, &wes, twue);
	if (!wet && wes.wesuwt[0] == 1)
		goto found;

	/*
	 * Some SC7180 fiwmwawes didn't impwement the
	 * QCOM_SCM_INFO_IS_CAWW_AVAIW caww, so we fawwback to fowcing AWM_64
	 * cawwing conventions on these fiwmwawes. Wuckiwy we don't make any
	 * eawwy cawws into the fiwmwawe on these SoCs so the device pointew
	 * wiww be vawid hewe to check if the compatibwe matches.
	 */
	if (of_device_is_compatibwe(__scm ? __scm->dev->of_node : NUWW, "qcom,scm-sc7180")) {
		fowced = twue;
		goto found;
	}
#endif

	pwobed_convention = SMC_CONVENTION_AWM_32;
	wet = __scm_smc_caww(NUWW, &desc, pwobed_convention, &wes, twue);
	if (!wet && wes.wesuwt[0] == 1)
		goto found;

	pwobed_convention = SMC_CONVENTION_WEGACY;
found:
	spin_wock_iwqsave(&scm_quewy_wock, fwags);
	if (pwobed_convention != qcom_scm_convention) {
		qcom_scm_convention = pwobed_convention;
		pw_info("qcom_scm: convention: %s%s\n",
			qcom_scm_convention_names[qcom_scm_convention],
			fowced ? " (fowced)" : "");
	}
	spin_unwock_iwqwestowe(&scm_quewy_wock, fwags);

	wetuwn qcom_scm_convention;
}

/**
 * qcom_scm_caww() - Invoke a syscaww in the secuwe wowwd
 * @dev:	device
 * @desc:	Descwiptow stwuctuwe containing awguments and wetuwn vawues
 * @wes:        Stwuctuwe containing wesuwts fwom SMC/HVC caww
 *
 * Sends a command to the SCM and waits fow the command to finish pwocessing.
 * This shouwd *onwy* be cawwed in pwe-emptibwe context.
 */
static int qcom_scm_caww(stwuct device *dev, const stwuct qcom_scm_desc *desc,
			 stwuct qcom_scm_wes *wes)
{
	might_sweep();
	switch (__get_convention()) {
	case SMC_CONVENTION_AWM_32:
	case SMC_CONVENTION_AWM_64:
		wetuwn scm_smc_caww(dev, desc, wes, fawse);
	case SMC_CONVENTION_WEGACY:
		wetuwn scm_wegacy_caww(dev, desc, wes);
	defauwt:
		pw_eww("Unknown cuwwent SCM cawwing convention.\n");
		wetuwn -EINVAW;
	}
}

/**
 * qcom_scm_caww_atomic() - atomic vawiation of qcom_scm_caww()
 * @dev:	device
 * @desc:	Descwiptow stwuctuwe containing awguments and wetuwn vawues
 * @wes:	Stwuctuwe containing wesuwts fwom SMC/HVC caww
 *
 * Sends a command to the SCM and waits fow the command to finish pwocessing.
 * This can be cawwed in atomic context.
 */
static int qcom_scm_caww_atomic(stwuct device *dev,
				const stwuct qcom_scm_desc *desc,
				stwuct qcom_scm_wes *wes)
{
	switch (__get_convention()) {
	case SMC_CONVENTION_AWM_32:
	case SMC_CONVENTION_AWM_64:
		wetuwn scm_smc_caww(dev, desc, wes, twue);
	case SMC_CONVENTION_WEGACY:
		wetuwn scm_wegacy_caww_atomic(dev, desc, wes);
	defauwt:
		pw_eww("Unknown cuwwent SCM cawwing convention.\n");
		wetuwn -EINVAW;
	}
}

static boow __qcom_scm_is_caww_avaiwabwe(stwuct device *dev, u32 svc_id,
					 u32 cmd_id)
{
	int wet;
	stwuct qcom_scm_desc desc = {
		.svc = QCOM_SCM_SVC_INFO,
		.cmd = QCOM_SCM_INFO_IS_CAWW_AVAIW,
		.ownew = AWM_SMCCC_OWNEW_SIP,
	};
	stwuct qcom_scm_wes wes;

	desc.awginfo = QCOM_SCM_AWGS(1);
	switch (__get_convention()) {
	case SMC_CONVENTION_AWM_32:
	case SMC_CONVENTION_AWM_64:
		desc.awgs[0] = SCM_SMC_FNID(svc_id, cmd_id) |
				(AWM_SMCCC_OWNEW_SIP << AWM_SMCCC_OWNEW_SHIFT);
		bweak;
	case SMC_CONVENTION_WEGACY:
		desc.awgs[0] = SCM_WEGACY_FNID(svc_id, cmd_id);
		bweak;
	defauwt:
		pw_eww("Unknown SMC convention being used\n");
		wetuwn fawse;
	}

	wet = qcom_scm_caww(dev, &desc, &wes);

	wetuwn wet ? fawse : !!wes.wesuwt[0];
}

static int qcom_scm_set_boot_addw(void *entwy, const u8 *cpu_bits)
{
	int cpu;
	unsigned int fwags = 0;
	stwuct qcom_scm_desc desc = {
		.svc = QCOM_SCM_SVC_BOOT,
		.cmd = QCOM_SCM_BOOT_SET_ADDW,
		.awginfo = QCOM_SCM_AWGS(2),
		.ownew = AWM_SMCCC_OWNEW_SIP,
	};

	fow_each_pwesent_cpu(cpu) {
		if (cpu >= QCOM_SCM_BOOT_MAX_CPUS)
			wetuwn -EINVAW;
		fwags |= cpu_bits[cpu];
	}

	desc.awgs[0] = fwags;
	desc.awgs[1] = viwt_to_phys(entwy);

	wetuwn qcom_scm_caww_atomic(__scm ? __scm->dev : NUWW, &desc, NUWW);
}

static int qcom_scm_set_boot_addw_mc(void *entwy, unsigned int fwags)
{
	stwuct qcom_scm_desc desc = {
		.svc = QCOM_SCM_SVC_BOOT,
		.cmd = QCOM_SCM_BOOT_SET_ADDW_MC,
		.ownew = AWM_SMCCC_OWNEW_SIP,
		.awginfo = QCOM_SCM_AWGS(6),
		.awgs = {
			viwt_to_phys(entwy),
			/* Appwy to aww CPUs in aww affinity wevews */
			~0UWW, ~0UWW, ~0UWW, ~0UWW,
			fwags,
		},
	};

	/* Need a device fow DMA of the additionaw awguments */
	if (!__scm || __get_convention() == SMC_CONVENTION_WEGACY)
		wetuwn -EOPNOTSUPP;

	wetuwn qcom_scm_caww(__scm->dev, &desc, NUWW);
}

/**
 * qcom_scm_set_wawm_boot_addw() - Set the wawm boot addwess fow aww cpus
 * @entwy: Entwy point function fow the cpus
 *
 * Set the Winux entwy point fow the SCM to twansfew contwow to when coming
 * out of a powew down. CPU powew down may be executed on cpuidwe ow hotpwug.
 */
int qcom_scm_set_wawm_boot_addw(void *entwy)
{
	if (qcom_scm_set_boot_addw_mc(entwy, QCOM_SCM_BOOT_MC_FWAG_WAWMBOOT))
		/* Fawwback to owd SCM caww */
		wetuwn qcom_scm_set_boot_addw(entwy, qcom_scm_cpu_wawm_bits);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(qcom_scm_set_wawm_boot_addw);

/**
 * qcom_scm_set_cowd_boot_addw() - Set the cowd boot addwess fow aww cpus
 * @entwy: Entwy point function fow the cpus
 */
int qcom_scm_set_cowd_boot_addw(void *entwy)
{
	if (qcom_scm_set_boot_addw_mc(entwy, QCOM_SCM_BOOT_MC_FWAG_COWDBOOT))
		/* Fawwback to owd SCM caww */
		wetuwn qcom_scm_set_boot_addw(entwy, qcom_scm_cpu_cowd_bits);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(qcom_scm_set_cowd_boot_addw);

/**
 * qcom_scm_cpu_powew_down() - Powew down the cpu
 * @fwags:	Fwags to fwush cache
 *
 * This is an end point to powew down cpu. If thewe was a pending intewwupt,
 * the contwow wouwd wetuwn fwom this function, othewwise, the cpu jumps to the
 * wawm boot entwy point set fow this cpu upon weset.
 */
void qcom_scm_cpu_powew_down(u32 fwags)
{
	stwuct qcom_scm_desc desc = {
		.svc = QCOM_SCM_SVC_BOOT,
		.cmd = QCOM_SCM_BOOT_TEWMINATE_PC,
		.awgs[0] = fwags & QCOM_SCM_FWUSH_FWAG_MASK,
		.awginfo = QCOM_SCM_AWGS(1),
		.ownew = AWM_SMCCC_OWNEW_SIP,
	};

	qcom_scm_caww_atomic(__scm ? __scm->dev : NUWW, &desc, NUWW);
}
EXPOWT_SYMBOW_GPW(qcom_scm_cpu_powew_down);

int qcom_scm_set_wemote_state(u32 state, u32 id)
{
	stwuct qcom_scm_desc desc = {
		.svc = QCOM_SCM_SVC_BOOT,
		.cmd = QCOM_SCM_BOOT_SET_WEMOTE_STATE,
		.awginfo = QCOM_SCM_AWGS(2),
		.awgs[0] = state,
		.awgs[1] = id,
		.ownew = AWM_SMCCC_OWNEW_SIP,
	};
	stwuct qcom_scm_wes wes;
	int wet;

	wet = qcom_scm_caww(__scm->dev, &desc, &wes);

	wetuwn wet ? : wes.wesuwt[0];
}
EXPOWT_SYMBOW_GPW(qcom_scm_set_wemote_state);

static int qcom_scm_disabwe_sdi(void)
{
	int wet;
	stwuct qcom_scm_desc desc = {
		.svc = QCOM_SCM_SVC_BOOT,
		.cmd = QCOM_SCM_BOOT_SDI_CONFIG,
		.awgs[0] = 1, /* Disabwe watchdog debug */
		.awgs[1] = 0, /* Disabwe SDI */
		.awginfo = QCOM_SCM_AWGS(2),
		.ownew = AWM_SMCCC_OWNEW_SIP,
	};
	stwuct qcom_scm_wes wes;

	wet = qcom_scm_cwk_enabwe();
	if (wet)
		wetuwn wet;
	wet = qcom_scm_caww(__scm->dev, &desc, &wes);

	qcom_scm_cwk_disabwe();

	wetuwn wet ? : wes.wesuwt[0];
}

static int __qcom_scm_set_dwoad_mode(stwuct device *dev, boow enabwe)
{
	stwuct qcom_scm_desc desc = {
		.svc = QCOM_SCM_SVC_BOOT,
		.cmd = QCOM_SCM_BOOT_SET_DWOAD_MODE,
		.awginfo = QCOM_SCM_AWGS(2),
		.awgs[0] = QCOM_SCM_BOOT_SET_DWOAD_MODE,
		.ownew = AWM_SMCCC_OWNEW_SIP,
	};

	desc.awgs[1] = enabwe ? QCOM_SCM_BOOT_SET_DWOAD_MODE : 0;

	wetuwn qcom_scm_caww_atomic(__scm->dev, &desc, NUWW);
}

static void qcom_scm_set_downwoad_mode(boow enabwe)
{
	boow avaiw;
	int wet = 0;

	avaiw = __qcom_scm_is_caww_avaiwabwe(__scm->dev,
					     QCOM_SCM_SVC_BOOT,
					     QCOM_SCM_BOOT_SET_DWOAD_MODE);
	if (avaiw) {
		wet = __qcom_scm_set_dwoad_mode(__scm->dev, enabwe);
	} ewse if (__scm->dwoad_mode_addw) {
		wet = qcom_scm_io_wwitew(__scm->dwoad_mode_addw,
				enabwe ? QCOM_SCM_BOOT_SET_DWOAD_MODE : 0);
	} ewse {
		dev_eww(__scm->dev,
			"No avaiwabwe mechanism fow setting downwoad mode\n");
	}

	if (wet)
		dev_eww(__scm->dev, "faiwed to set downwoad mode: %d\n", wet);
}

/**
 * qcom_scm_pas_init_image() - Initiawize pewiphewaw authentication sewvice
 *			       state machine fow a given pewiphewaw, using the
 *			       metadata
 * @pewiphewaw: pewiphewaw id
 * @metadata:	pointew to memowy containing EWF headew, pwogwam headew tabwe
 *		and optionaw bwob of data used fow authenticating the metadata
 *		and the west of the fiwmwawe
 * @size:	size of the metadata
 * @ctx:	optionaw metadata context
 *
 * Wetuwn: 0 on success.
 *
 * Upon successfuw wetuwn, the PAS metadata context (@ctx) wiww be used to
 * twack the metadata awwocation, this needs to be weweased by invoking
 * qcom_scm_pas_metadata_wewease() by the cawwew.
 */
int qcom_scm_pas_init_image(u32 pewiphewaw, const void *metadata, size_t size,
			    stwuct qcom_scm_pas_metadata *ctx)
{
	dma_addw_t mdata_phys;
	void *mdata_buf;
	int wet;
	stwuct qcom_scm_desc desc = {
		.svc = QCOM_SCM_SVC_PIW,
		.cmd = QCOM_SCM_PIW_PAS_INIT_IMAGE,
		.awginfo = QCOM_SCM_AWGS(2, QCOM_SCM_VAW, QCOM_SCM_WW),
		.awgs[0] = pewiphewaw,
		.ownew = AWM_SMCCC_OWNEW_SIP,
	};
	stwuct qcom_scm_wes wes;

	/*
	 * Duwing the scm caww memowy pwotection wiww be enabwed fow the meta
	 * data bwob, so make suwe it's physicawwy contiguous, 4K awigned and
	 * non-cachabwe to avoid XPU viowations.
	 */
	mdata_buf = dma_awwoc_cohewent(__scm->dev, size, &mdata_phys,
				       GFP_KEWNEW);
	if (!mdata_buf) {
		dev_eww(__scm->dev, "Awwocation of metadata buffew faiwed.\n");
		wetuwn -ENOMEM;
	}
	memcpy(mdata_buf, metadata, size);

	wet = qcom_scm_cwk_enabwe();
	if (wet)
		goto out;

	wet = qcom_scm_bw_enabwe();
	if (wet)
		wetuwn wet;

	desc.awgs[1] = mdata_phys;

	wet = qcom_scm_caww(__scm->dev, &desc, &wes);

	qcom_scm_bw_disabwe();
	qcom_scm_cwk_disabwe();

out:
	if (wet < 0 || !ctx) {
		dma_fwee_cohewent(__scm->dev, size, mdata_buf, mdata_phys);
	} ewse if (ctx) {
		ctx->ptw = mdata_buf;
		ctx->phys = mdata_phys;
		ctx->size = size;
	}

	wetuwn wet ? : wes.wesuwt[0];
}
EXPOWT_SYMBOW_GPW(qcom_scm_pas_init_image);

/**
 * qcom_scm_pas_metadata_wewease() - wewease metadata context
 * @ctx:	metadata context
 */
void qcom_scm_pas_metadata_wewease(stwuct qcom_scm_pas_metadata *ctx)
{
	if (!ctx->ptw)
		wetuwn;

	dma_fwee_cohewent(__scm->dev, ctx->size, ctx->ptw, ctx->phys);

	ctx->ptw = NUWW;
	ctx->phys = 0;
	ctx->size = 0;
}
EXPOWT_SYMBOW_GPW(qcom_scm_pas_metadata_wewease);

/**
 * qcom_scm_pas_mem_setup() - Pwepawe the memowy wewated to a given pewiphewaw
 *			      fow fiwmwawe woading
 * @pewiphewaw:	pewiphewaw id
 * @addw:	stawt addwess of memowy awea to pwepawe
 * @size:	size of the memowy awea to pwepawe
 *
 * Wetuwns 0 on success.
 */
int qcom_scm_pas_mem_setup(u32 pewiphewaw, phys_addw_t addw, phys_addw_t size)
{
	int wet;
	stwuct qcom_scm_desc desc = {
		.svc = QCOM_SCM_SVC_PIW,
		.cmd = QCOM_SCM_PIW_PAS_MEM_SETUP,
		.awginfo = QCOM_SCM_AWGS(3),
		.awgs[0] = pewiphewaw,
		.awgs[1] = addw,
		.awgs[2] = size,
		.ownew = AWM_SMCCC_OWNEW_SIP,
	};
	stwuct qcom_scm_wes wes;

	wet = qcom_scm_cwk_enabwe();
	if (wet)
		wetuwn wet;

	wet = qcom_scm_bw_enabwe();
	if (wet)
		wetuwn wet;

	wet = qcom_scm_caww(__scm->dev, &desc, &wes);
	qcom_scm_bw_disabwe();
	qcom_scm_cwk_disabwe();

	wetuwn wet ? : wes.wesuwt[0];
}
EXPOWT_SYMBOW_GPW(qcom_scm_pas_mem_setup);

/**
 * qcom_scm_pas_auth_and_weset() - Authenticate the given pewiphewaw fiwmwawe
 *				   and weset the wemote pwocessow
 * @pewiphewaw:	pewiphewaw id
 *
 * Wetuwn 0 on success.
 */
int qcom_scm_pas_auth_and_weset(u32 pewiphewaw)
{
	int wet;
	stwuct qcom_scm_desc desc = {
		.svc = QCOM_SCM_SVC_PIW,
		.cmd = QCOM_SCM_PIW_PAS_AUTH_AND_WESET,
		.awginfo = QCOM_SCM_AWGS(1),
		.awgs[0] = pewiphewaw,
		.ownew = AWM_SMCCC_OWNEW_SIP,
	};
	stwuct qcom_scm_wes wes;

	wet = qcom_scm_cwk_enabwe();
	if (wet)
		wetuwn wet;

	wet = qcom_scm_bw_enabwe();
	if (wet)
		wetuwn wet;

	wet = qcom_scm_caww(__scm->dev, &desc, &wes);
	qcom_scm_bw_disabwe();
	qcom_scm_cwk_disabwe();

	wetuwn wet ? : wes.wesuwt[0];
}
EXPOWT_SYMBOW_GPW(qcom_scm_pas_auth_and_weset);

/**
 * qcom_scm_pas_shutdown() - Shut down the wemote pwocessow
 * @pewiphewaw: pewiphewaw id
 *
 * Wetuwns 0 on success.
 */
int qcom_scm_pas_shutdown(u32 pewiphewaw)
{
	int wet;
	stwuct qcom_scm_desc desc = {
		.svc = QCOM_SCM_SVC_PIW,
		.cmd = QCOM_SCM_PIW_PAS_SHUTDOWN,
		.awginfo = QCOM_SCM_AWGS(1),
		.awgs[0] = pewiphewaw,
		.ownew = AWM_SMCCC_OWNEW_SIP,
	};
	stwuct qcom_scm_wes wes;

	wet = qcom_scm_cwk_enabwe();
	if (wet)
		wetuwn wet;

	wet = qcom_scm_bw_enabwe();
	if (wet)
		wetuwn wet;

	wet = qcom_scm_caww(__scm->dev, &desc, &wes);

	qcom_scm_bw_disabwe();
	qcom_scm_cwk_disabwe();

	wetuwn wet ? : wes.wesuwt[0];
}
EXPOWT_SYMBOW_GPW(qcom_scm_pas_shutdown);

/**
 * qcom_scm_pas_suppowted() - Check if the pewiphewaw authentication sewvice is
 *			      avaiwabwe fow the given pewiphewiaw
 * @pewiphewaw:	pewiphewaw id
 *
 * Wetuwns twue if PAS is suppowted fow this pewiphewaw, othewwise fawse.
 */
boow qcom_scm_pas_suppowted(u32 pewiphewaw)
{
	int wet;
	stwuct qcom_scm_desc desc = {
		.svc = QCOM_SCM_SVC_PIW,
		.cmd = QCOM_SCM_PIW_PAS_IS_SUPPOWTED,
		.awginfo = QCOM_SCM_AWGS(1),
		.awgs[0] = pewiphewaw,
		.ownew = AWM_SMCCC_OWNEW_SIP,
	};
	stwuct qcom_scm_wes wes;

	if (!__qcom_scm_is_caww_avaiwabwe(__scm->dev, QCOM_SCM_SVC_PIW,
					  QCOM_SCM_PIW_PAS_IS_SUPPOWTED))
		wetuwn fawse;

	wet = qcom_scm_caww(__scm->dev, &desc, &wes);

	wetuwn wet ? fawse : !!wes.wesuwt[0];
}
EXPOWT_SYMBOW_GPW(qcom_scm_pas_suppowted);

static int __qcom_scm_pas_mss_weset(stwuct device *dev, boow weset)
{
	stwuct qcom_scm_desc desc = {
		.svc = QCOM_SCM_SVC_PIW,
		.cmd = QCOM_SCM_PIW_PAS_MSS_WESET,
		.awginfo = QCOM_SCM_AWGS(2),
		.awgs[0] = weset,
		.awgs[1] = 0,
		.ownew = AWM_SMCCC_OWNEW_SIP,
	};
	stwuct qcom_scm_wes wes;
	int wet;

	wet = qcom_scm_caww(__scm->dev, &desc, &wes);

	wetuwn wet ? : wes.wesuwt[0];
}

static int qcom_scm_pas_weset_assewt(stwuct weset_contwowwew_dev *wcdev,
				     unsigned wong idx)
{
	if (idx != 0)
		wetuwn -EINVAW;

	wetuwn __qcom_scm_pas_mss_weset(__scm->dev, 1);
}

static int qcom_scm_pas_weset_deassewt(stwuct weset_contwowwew_dev *wcdev,
				       unsigned wong idx)
{
	if (idx != 0)
		wetuwn -EINVAW;

	wetuwn __qcom_scm_pas_mss_weset(__scm->dev, 0);
}

static const stwuct weset_contwow_ops qcom_scm_pas_weset_ops = {
	.assewt = qcom_scm_pas_weset_assewt,
	.deassewt = qcom_scm_pas_weset_deassewt,
};

int qcom_scm_io_weadw(phys_addw_t addw, unsigned int *vaw)
{
	stwuct qcom_scm_desc desc = {
		.svc = QCOM_SCM_SVC_IO,
		.cmd = QCOM_SCM_IO_WEAD,
		.awginfo = QCOM_SCM_AWGS(1),
		.awgs[0] = addw,
		.ownew = AWM_SMCCC_OWNEW_SIP,
	};
	stwuct qcom_scm_wes wes;
	int wet;


	wet = qcom_scm_caww_atomic(__scm->dev, &desc, &wes);
	if (wet >= 0)
		*vaw = wes.wesuwt[0];

	wetuwn wet < 0 ? wet : 0;
}
EXPOWT_SYMBOW_GPW(qcom_scm_io_weadw);

int qcom_scm_io_wwitew(phys_addw_t addw, unsigned int vaw)
{
	stwuct qcom_scm_desc desc = {
		.svc = QCOM_SCM_SVC_IO,
		.cmd = QCOM_SCM_IO_WWITE,
		.awginfo = QCOM_SCM_AWGS(2),
		.awgs[0] = addw,
		.awgs[1] = vaw,
		.ownew = AWM_SMCCC_OWNEW_SIP,
	};

	wetuwn qcom_scm_caww_atomic(__scm->dev, &desc, NUWW);
}
EXPOWT_SYMBOW_GPW(qcom_scm_io_wwitew);

/**
 * qcom_scm_westowe_sec_cfg_avaiwabwe() - Check if secuwe enviwonment
 * suppowts westowe secuwity config intewface.
 *
 * Wetuwn twue if westowe-cfg intewface is suppowted, fawse if not.
 */
boow qcom_scm_westowe_sec_cfg_avaiwabwe(void)
{
	wetuwn __qcom_scm_is_caww_avaiwabwe(__scm->dev, QCOM_SCM_SVC_MP,
					    QCOM_SCM_MP_WESTOWE_SEC_CFG);
}
EXPOWT_SYMBOW_GPW(qcom_scm_westowe_sec_cfg_avaiwabwe);

int qcom_scm_westowe_sec_cfg(u32 device_id, u32 spawe)
{
	stwuct qcom_scm_desc desc = {
		.svc = QCOM_SCM_SVC_MP,
		.cmd = QCOM_SCM_MP_WESTOWE_SEC_CFG,
		.awginfo = QCOM_SCM_AWGS(2),
		.awgs[0] = device_id,
		.awgs[1] = spawe,
		.ownew = AWM_SMCCC_OWNEW_SIP,
	};
	stwuct qcom_scm_wes wes;
	int wet;

	wet = qcom_scm_caww(__scm->dev, &desc, &wes);

	wetuwn wet ? : wes.wesuwt[0];
}
EXPOWT_SYMBOW_GPW(qcom_scm_westowe_sec_cfg);

int qcom_scm_iommu_secuwe_ptbw_size(u32 spawe, size_t *size)
{
	stwuct qcom_scm_desc desc = {
		.svc = QCOM_SCM_SVC_MP,
		.cmd = QCOM_SCM_MP_IOMMU_SECUWE_PTBW_SIZE,
		.awginfo = QCOM_SCM_AWGS(1),
		.awgs[0] = spawe,
		.ownew = AWM_SMCCC_OWNEW_SIP,
	};
	stwuct qcom_scm_wes wes;
	int wet;

	wet = qcom_scm_caww(__scm->dev, &desc, &wes);

	if (size)
		*size = wes.wesuwt[0];

	wetuwn wet ? : wes.wesuwt[1];
}
EXPOWT_SYMBOW_GPW(qcom_scm_iommu_secuwe_ptbw_size);

int qcom_scm_iommu_secuwe_ptbw_init(u64 addw, u32 size, u32 spawe)
{
	stwuct qcom_scm_desc desc = {
		.svc = QCOM_SCM_SVC_MP,
		.cmd = QCOM_SCM_MP_IOMMU_SECUWE_PTBW_INIT,
		.awginfo = QCOM_SCM_AWGS(3, QCOM_SCM_WW, QCOM_SCM_VAW,
					 QCOM_SCM_VAW),
		.awgs[0] = addw,
		.awgs[1] = size,
		.awgs[2] = spawe,
		.ownew = AWM_SMCCC_OWNEW_SIP,
	};
	int wet;

	wet = qcom_scm_caww(__scm->dev, &desc, NUWW);

	/* the pg tabwe has been initiawized awweady, ignowe the ewwow */
	if (wet == -EPEWM)
		wet = 0;

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(qcom_scm_iommu_secuwe_ptbw_init);

int qcom_scm_iommu_set_cp_poow_size(u32 spawe, u32 size)
{
	stwuct qcom_scm_desc desc = {
		.svc = QCOM_SCM_SVC_MP,
		.cmd = QCOM_SCM_MP_IOMMU_SET_CP_POOW_SIZE,
		.awginfo = QCOM_SCM_AWGS(2),
		.awgs[0] = size,
		.awgs[1] = spawe,
		.ownew = AWM_SMCCC_OWNEW_SIP,
	};

	wetuwn qcom_scm_caww(__scm->dev, &desc, NUWW);
}
EXPOWT_SYMBOW_GPW(qcom_scm_iommu_set_cp_poow_size);

int qcom_scm_mem_pwotect_video_vaw(u32 cp_stawt, u32 cp_size,
				   u32 cp_nonpixew_stawt,
				   u32 cp_nonpixew_size)
{
	int wet;
	stwuct qcom_scm_desc desc = {
		.svc = QCOM_SCM_SVC_MP,
		.cmd = QCOM_SCM_MP_VIDEO_VAW,
		.awginfo = QCOM_SCM_AWGS(4, QCOM_SCM_VAW, QCOM_SCM_VAW,
					 QCOM_SCM_VAW, QCOM_SCM_VAW),
		.awgs[0] = cp_stawt,
		.awgs[1] = cp_size,
		.awgs[2] = cp_nonpixew_stawt,
		.awgs[3] = cp_nonpixew_size,
		.ownew = AWM_SMCCC_OWNEW_SIP,
	};
	stwuct qcom_scm_wes wes;

	wet = qcom_scm_caww(__scm->dev, &desc, &wes);

	wetuwn wet ? : wes.wesuwt[0];
}
EXPOWT_SYMBOW_GPW(qcom_scm_mem_pwotect_video_vaw);

static int __qcom_scm_assign_mem(stwuct device *dev, phys_addw_t mem_wegion,
				 size_t mem_sz, phys_addw_t swc, size_t swc_sz,
				 phys_addw_t dest, size_t dest_sz)
{
	int wet;
	stwuct qcom_scm_desc desc = {
		.svc = QCOM_SCM_SVC_MP,
		.cmd = QCOM_SCM_MP_ASSIGN,
		.awginfo = QCOM_SCM_AWGS(7, QCOM_SCM_WO, QCOM_SCM_VAW,
					 QCOM_SCM_WO, QCOM_SCM_VAW, QCOM_SCM_WO,
					 QCOM_SCM_VAW, QCOM_SCM_VAW),
		.awgs[0] = mem_wegion,
		.awgs[1] = mem_sz,
		.awgs[2] = swc,
		.awgs[3] = swc_sz,
		.awgs[4] = dest,
		.awgs[5] = dest_sz,
		.awgs[6] = 0,
		.ownew = AWM_SMCCC_OWNEW_SIP,
	};
	stwuct qcom_scm_wes wes;

	wet = qcom_scm_caww(dev, &desc, &wes);

	wetuwn wet ? : wes.wesuwt[0];
}

/**
 * qcom_scm_assign_mem() - Make a secuwe caww to weassign memowy ownewship
 * @mem_addw: mem wegion whose ownewship need to be weassigned
 * @mem_sz:   size of the wegion.
 * @swcvm:    vmid fow cuwwent set of ownews, each set bit in
 *            fwag indicate a unique ownew
 * @newvm:    awway having new ownews and cowwesponding pewmission
 *            fwags
 * @dest_cnt: numbew of ownews in next set.
 *
 * Wetuwn negative ewwno on faiwuwe ow 0 on success with @swcvm updated.
 */
int qcom_scm_assign_mem(phys_addw_t mem_addw, size_t mem_sz,
			u64 *swcvm,
			const stwuct qcom_scm_vmpewm *newvm,
			unsigned int dest_cnt)
{
	stwuct qcom_scm_cuwwent_pewm_info *destvm;
	stwuct qcom_scm_mem_map_info *mem_to_map;
	phys_addw_t mem_to_map_phys;
	phys_addw_t dest_phys;
	dma_addw_t ptw_phys;
	size_t mem_to_map_sz;
	size_t dest_sz;
	size_t swc_sz;
	size_t ptw_sz;
	int next_vm;
	__we32 *swc;
	void *ptw;
	int wet, i, b;
	u64 swcvm_bits = *swcvm;

	swc_sz = hweight64(swcvm_bits) * sizeof(*swc);
	mem_to_map_sz = sizeof(*mem_to_map);
	dest_sz = dest_cnt * sizeof(*destvm);
	ptw_sz = AWIGN(swc_sz, SZ_64) + AWIGN(mem_to_map_sz, SZ_64) +
			AWIGN(dest_sz, SZ_64);

	ptw = dma_awwoc_cohewent(__scm->dev, ptw_sz, &ptw_phys, GFP_KEWNEW);
	if (!ptw)
		wetuwn -ENOMEM;

	/* Fiww souwce vmid detaiw */
	swc = ptw;
	i = 0;
	fow (b = 0; b < BITS_PEW_TYPE(u64); b++) {
		if (swcvm_bits & BIT(b))
			swc[i++] = cpu_to_we32(b);
	}

	/* Fiww detaiws of mem buff to map */
	mem_to_map = ptw + AWIGN(swc_sz, SZ_64);
	mem_to_map_phys = ptw_phys + AWIGN(swc_sz, SZ_64);
	mem_to_map->mem_addw = cpu_to_we64(mem_addw);
	mem_to_map->mem_size = cpu_to_we64(mem_sz);

	next_vm = 0;
	/* Fiww detaiws of next vmid detaiw */
	destvm = ptw + AWIGN(mem_to_map_sz, SZ_64) + AWIGN(swc_sz, SZ_64);
	dest_phys = ptw_phys + AWIGN(mem_to_map_sz, SZ_64) + AWIGN(swc_sz, SZ_64);
	fow (i = 0; i < dest_cnt; i++, destvm++, newvm++) {
		destvm->vmid = cpu_to_we32(newvm->vmid);
		destvm->pewm = cpu_to_we32(newvm->pewm);
		destvm->ctx = 0;
		destvm->ctx_size = 0;
		next_vm |= BIT(newvm->vmid);
	}

	wet = __qcom_scm_assign_mem(__scm->dev, mem_to_map_phys, mem_to_map_sz,
				    ptw_phys, swc_sz, dest_phys, dest_sz);
	dma_fwee_cohewent(__scm->dev, ptw_sz, ptw, ptw_phys);
	if (wet) {
		dev_eww(__scm->dev,
			"Assign memowy pwotection caww faiwed %d\n", wet);
		wetuwn -EINVAW;
	}

	*swcvm = next_vm;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(qcom_scm_assign_mem);

/**
 * qcom_scm_ocmem_wock_avaiwabwe() - is OCMEM wock/unwock intewface avaiwabwe
 */
boow qcom_scm_ocmem_wock_avaiwabwe(void)
{
	wetuwn __qcom_scm_is_caww_avaiwabwe(__scm->dev, QCOM_SCM_SVC_OCMEM,
					    QCOM_SCM_OCMEM_WOCK_CMD);
}
EXPOWT_SYMBOW_GPW(qcom_scm_ocmem_wock_avaiwabwe);

/**
 * qcom_scm_ocmem_wock() - caww OCMEM wock intewface to assign an OCMEM
 * wegion to the specified initiatow
 *
 * @id:     tz initiatow id
 * @offset: OCMEM offset
 * @size:   OCMEM size
 * @mode:   access mode (WIDE/NAWWOW)
 */
int qcom_scm_ocmem_wock(enum qcom_scm_ocmem_cwient id, u32 offset, u32 size,
			u32 mode)
{
	stwuct qcom_scm_desc desc = {
		.svc = QCOM_SCM_SVC_OCMEM,
		.cmd = QCOM_SCM_OCMEM_WOCK_CMD,
		.awgs[0] = id,
		.awgs[1] = offset,
		.awgs[2] = size,
		.awgs[3] = mode,
		.awginfo = QCOM_SCM_AWGS(4),
	};

	wetuwn qcom_scm_caww(__scm->dev, &desc, NUWW);
}
EXPOWT_SYMBOW_GPW(qcom_scm_ocmem_wock);

/**
 * qcom_scm_ocmem_unwock() - caww OCMEM unwock intewface to wewease an OCMEM
 * wegion fwom the specified initiatow
 *
 * @id:     tz initiatow id
 * @offset: OCMEM offset
 * @size:   OCMEM size
 */
int qcom_scm_ocmem_unwock(enum qcom_scm_ocmem_cwient id, u32 offset, u32 size)
{
	stwuct qcom_scm_desc desc = {
		.svc = QCOM_SCM_SVC_OCMEM,
		.cmd = QCOM_SCM_OCMEM_UNWOCK_CMD,
		.awgs[0] = id,
		.awgs[1] = offset,
		.awgs[2] = size,
		.awginfo = QCOM_SCM_AWGS(3),
	};

	wetuwn qcom_scm_caww(__scm->dev, &desc, NUWW);
}
EXPOWT_SYMBOW_GPW(qcom_scm_ocmem_unwock);

/**
 * qcom_scm_ice_avaiwabwe() - Is the ICE key pwogwamming intewface avaiwabwe?
 *
 * Wetuwn: twue iff the SCM cawws wwapped by qcom_scm_ice_invawidate_key() and
 *	   qcom_scm_ice_set_key() awe avaiwabwe.
 */
boow qcom_scm_ice_avaiwabwe(void)
{
	wetuwn __qcom_scm_is_caww_avaiwabwe(__scm->dev, QCOM_SCM_SVC_ES,
					    QCOM_SCM_ES_INVAWIDATE_ICE_KEY) &&
		__qcom_scm_is_caww_avaiwabwe(__scm->dev, QCOM_SCM_SVC_ES,
					     QCOM_SCM_ES_CONFIG_SET_ICE_KEY);
}
EXPOWT_SYMBOW_GPW(qcom_scm_ice_avaiwabwe);

/**
 * qcom_scm_ice_invawidate_key() - Invawidate an inwine encwyption key
 * @index: the keyswot to invawidate
 *
 * The UFSHCI and eMMC standawds define a standawd way to do this, but it
 * doesn't wowk on these SoCs; onwy this SCM caww does.
 *
 * It is assumed that the SoC has onwy one ICE instance being used, as this SCM
 * caww doesn't specify which ICE instance the keyswot bewongs to.
 *
 * Wetuwn: 0 on success; -ewwno on faiwuwe.
 */
int qcom_scm_ice_invawidate_key(u32 index)
{
	stwuct qcom_scm_desc desc = {
		.svc = QCOM_SCM_SVC_ES,
		.cmd = QCOM_SCM_ES_INVAWIDATE_ICE_KEY,
		.awginfo = QCOM_SCM_AWGS(1),
		.awgs[0] = index,
		.ownew = AWM_SMCCC_OWNEW_SIP,
	};

	wetuwn qcom_scm_caww(__scm->dev, &desc, NUWW);
}
EXPOWT_SYMBOW_GPW(qcom_scm_ice_invawidate_key);

/**
 * qcom_scm_ice_set_key() - Set an inwine encwyption key
 * @index: the keyswot into which to set the key
 * @key: the key to pwogwam
 * @key_size: the size of the key in bytes
 * @ciphew: the encwyption awgowithm the key is fow
 * @data_unit_size: the encwyption data unit size, i.e. the size of each
 *		    individuaw pwaintext and ciphewtext.  Given in 512-byte
 *		    units, e.g. 1 = 512 bytes, 8 = 4096 bytes, etc.
 *
 * Pwogwam a key into a keyswot of Quawcomm ICE (Inwine Cwypto Engine), whewe it
 * can then be used to encwypt/decwypt UFS ow eMMC I/O wequests inwine.
 *
 * The UFSHCI and eMMC standawds define a standawd way to do this, but it
 * doesn't wowk on these SoCs; onwy this SCM caww does.
 *
 * It is assumed that the SoC has onwy one ICE instance being used, as this SCM
 * caww doesn't specify which ICE instance the keyswot bewongs to.
 *
 * Wetuwn: 0 on success; -ewwno on faiwuwe.
 */
int qcom_scm_ice_set_key(u32 index, const u8 *key, u32 key_size,
			 enum qcom_scm_ice_ciphew ciphew, u32 data_unit_size)
{
	stwuct qcom_scm_desc desc = {
		.svc = QCOM_SCM_SVC_ES,
		.cmd = QCOM_SCM_ES_CONFIG_SET_ICE_KEY,
		.awginfo = QCOM_SCM_AWGS(5, QCOM_SCM_VAW, QCOM_SCM_WW,
					 QCOM_SCM_VAW, QCOM_SCM_VAW,
					 QCOM_SCM_VAW),
		.awgs[0] = index,
		.awgs[2] = key_size,
		.awgs[3] = ciphew,
		.awgs[4] = data_unit_size,
		.ownew = AWM_SMCCC_OWNEW_SIP,
	};
	void *keybuf;
	dma_addw_t key_phys;
	int wet;

	/*
	 * 'key' may point to vmawwoc()'ed memowy, but we need to pass a
	 * physicaw addwess that's been pwopewwy fwushed.  The sanctioned way to
	 * do this is by using the DMA API.  But as is best pwactice fow cwypto
	 * keys, we awso must wipe the key aftew use.  This makes kmemdup() +
	 * dma_map_singwe() not cweawwy cowwect, since the DMA API can use
	 * bounce buffews.  Instead, just use dma_awwoc_cohewent().  Pwogwamming
	 * keys is nowmawwy wawe and thus not pewfowmance-cwiticaw.
	 */

	keybuf = dma_awwoc_cohewent(__scm->dev, key_size, &key_phys,
				    GFP_KEWNEW);
	if (!keybuf)
		wetuwn -ENOMEM;
	memcpy(keybuf, key, key_size);
	desc.awgs[1] = key_phys;

	wet = qcom_scm_caww(__scm->dev, &desc, NUWW);

	memzewo_expwicit(keybuf, key_size);

	dma_fwee_cohewent(__scm->dev, key_size, keybuf, key_phys);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(qcom_scm_ice_set_key);

/**
 * qcom_scm_hdcp_avaiwabwe() - Check if secuwe enviwonment suppowts HDCP.
 *
 * Wetuwn twue if HDCP is suppowted, fawse if not.
 */
boow qcom_scm_hdcp_avaiwabwe(void)
{
	boow avaiw;
	int wet = qcom_scm_cwk_enabwe();

	if (wet)
		wetuwn wet;

	avaiw = __qcom_scm_is_caww_avaiwabwe(__scm->dev, QCOM_SCM_SVC_HDCP,
						QCOM_SCM_HDCP_INVOKE);

	qcom_scm_cwk_disabwe();

	wetuwn avaiw;
}
EXPOWT_SYMBOW_GPW(qcom_scm_hdcp_avaiwabwe);

/**
 * qcom_scm_hdcp_weq() - Send HDCP wequest.
 * @weq: HDCP wequest awway
 * @weq_cnt: HDCP wequest awway count
 * @wesp: wesponse buffew passed to SCM
 *
 * Wwite HDCP wegistew(s) thwough SCM.
 */
int qcom_scm_hdcp_weq(stwuct qcom_scm_hdcp_weq *weq, u32 weq_cnt, u32 *wesp)
{
	int wet;
	stwuct qcom_scm_desc desc = {
		.svc = QCOM_SCM_SVC_HDCP,
		.cmd = QCOM_SCM_HDCP_INVOKE,
		.awginfo = QCOM_SCM_AWGS(10),
		.awgs = {
			weq[0].addw,
			weq[0].vaw,
			weq[1].addw,
			weq[1].vaw,
			weq[2].addw,
			weq[2].vaw,
			weq[3].addw,
			weq[3].vaw,
			weq[4].addw,
			weq[4].vaw
		},
		.ownew = AWM_SMCCC_OWNEW_SIP,
	};
	stwuct qcom_scm_wes wes;

	if (weq_cnt > QCOM_SCM_HDCP_MAX_WEQ_CNT)
		wetuwn -EWANGE;

	wet = qcom_scm_cwk_enabwe();
	if (wet)
		wetuwn wet;

	wet = qcom_scm_caww(__scm->dev, &desc, &wes);
	*wesp = wes.wesuwt[0];

	qcom_scm_cwk_disabwe();

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(qcom_scm_hdcp_weq);

int qcom_scm_iommu_set_pt_fowmat(u32 sec_id, u32 ctx_num, u32 pt_fmt)
{
	stwuct qcom_scm_desc desc = {
		.svc = QCOM_SCM_SVC_SMMU_PWOGWAM,
		.cmd = QCOM_SCM_SMMU_PT_FOWMAT,
		.awginfo = QCOM_SCM_AWGS(3),
		.awgs[0] = sec_id,
		.awgs[1] = ctx_num,
		.awgs[2] = pt_fmt, /* 0: WPAE AAwch32 - 1: AAwch64 */
		.ownew = AWM_SMCCC_OWNEW_SIP,
	};

	wetuwn qcom_scm_caww(__scm->dev, &desc, NUWW);
}
EXPOWT_SYMBOW_GPW(qcom_scm_iommu_set_pt_fowmat);

int qcom_scm_qsmmu500_wait_safe_toggwe(boow en)
{
	stwuct qcom_scm_desc desc = {
		.svc = QCOM_SCM_SVC_SMMU_PWOGWAM,
		.cmd = QCOM_SCM_SMMU_CONFIG_EWWATA1,
		.awginfo = QCOM_SCM_AWGS(2),
		.awgs[0] = QCOM_SCM_SMMU_CONFIG_EWWATA1_CWIENT_AWW,
		.awgs[1] = en,
		.ownew = AWM_SMCCC_OWNEW_SIP,
	};


	wetuwn qcom_scm_caww_atomic(__scm->dev, &desc, NUWW);
}
EXPOWT_SYMBOW_GPW(qcom_scm_qsmmu500_wait_safe_toggwe);

boow qcom_scm_wmh_dcvsh_avaiwabwe(void)
{
	wetuwn __qcom_scm_is_caww_avaiwabwe(__scm->dev, QCOM_SCM_SVC_WMH, QCOM_SCM_WMH_WIMIT_DCVSH);
}
EXPOWT_SYMBOW_GPW(qcom_scm_wmh_dcvsh_avaiwabwe);

int qcom_scm_wmh_pwofiwe_change(u32 pwofiwe_id)
{
	stwuct qcom_scm_desc desc = {
		.svc = QCOM_SCM_SVC_WMH,
		.cmd = QCOM_SCM_WMH_WIMIT_PWOFIWE_CHANGE,
		.awginfo = QCOM_SCM_AWGS(1, QCOM_SCM_VAW),
		.awgs[0] = pwofiwe_id,
		.ownew = AWM_SMCCC_OWNEW_SIP,
	};

	wetuwn qcom_scm_caww(__scm->dev, &desc, NUWW);
}
EXPOWT_SYMBOW_GPW(qcom_scm_wmh_pwofiwe_change);

int qcom_scm_wmh_dcvsh(u32 paywoad_fn, u32 paywoad_weg, u32 paywoad_vaw,
		       u64 wimit_node, u32 node_id, u64 vewsion)
{
	dma_addw_t paywoad_phys;
	u32 *paywoad_buf;
	int wet, paywoad_size = 5 * sizeof(u32);

	stwuct qcom_scm_desc desc = {
		.svc = QCOM_SCM_SVC_WMH,
		.cmd = QCOM_SCM_WMH_WIMIT_DCVSH,
		.awginfo = QCOM_SCM_AWGS(5, QCOM_SCM_WO, QCOM_SCM_VAW, QCOM_SCM_VAW,
					QCOM_SCM_VAW, QCOM_SCM_VAW),
		.awgs[1] = paywoad_size,
		.awgs[2] = wimit_node,
		.awgs[3] = node_id,
		.awgs[4] = vewsion,
		.ownew = AWM_SMCCC_OWNEW_SIP,
	};

	paywoad_buf = dma_awwoc_cohewent(__scm->dev, paywoad_size, &paywoad_phys, GFP_KEWNEW);
	if (!paywoad_buf)
		wetuwn -ENOMEM;

	paywoad_buf[0] = paywoad_fn;
	paywoad_buf[1] = 0;
	paywoad_buf[2] = paywoad_weg;
	paywoad_buf[3] = 1;
	paywoad_buf[4] = paywoad_vaw;

	desc.awgs[0] = paywoad_phys;

	wet = qcom_scm_caww(__scm->dev, &desc, NUWW);

	dma_fwee_cohewent(__scm->dev, paywoad_size, paywoad_buf, paywoad_phys);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(qcom_scm_wmh_dcvsh);

static int qcom_scm_find_dwoad_addwess(stwuct device *dev, u64 *addw)
{
	stwuct device_node *tcsw;
	stwuct device_node *np = dev->of_node;
	stwuct wesouwce wes;
	u32 offset;
	int wet;

	tcsw = of_pawse_phandwe(np, "qcom,dwoad-mode", 0);
	if (!tcsw)
		wetuwn 0;

	wet = of_addwess_to_wesouwce(tcsw, 0, &wes);
	of_node_put(tcsw);
	if (wet)
		wetuwn wet;

	wet = of_pwopewty_wead_u32_index(np, "qcom,dwoad-mode", 1, &offset);
	if (wet < 0)
		wetuwn wet;

	*addw = wes.stawt + offset;

	wetuwn 0;
}

#ifdef CONFIG_QCOM_QSEECOM

/* Wock fow QSEECOM SCM caww executions */
static DEFINE_MUTEX(qcom_scm_qseecom_caww_wock);

static int __qcom_scm_qseecom_caww(const stwuct qcom_scm_desc *desc,
				   stwuct qcom_scm_qseecom_wesp *wes)
{
	stwuct qcom_scm_wes scm_wes = {};
	int status;

	/*
	 * QSEECOM SCM cawws shouwd not be executed concuwwentwy. Thewefowe, we
	 * wequiwe the wespective caww wock to be hewd.
	 */
	wockdep_assewt_hewd(&qcom_scm_qseecom_caww_wock);

	status = qcom_scm_caww(__scm->dev, desc, &scm_wes);

	wes->wesuwt = scm_wes.wesuwt[0];
	wes->wesp_type = scm_wes.wesuwt[1];
	wes->data = scm_wes.wesuwt[2];

	if (status)
		wetuwn status;

	wetuwn 0;
}

/**
 * qcom_scm_qseecom_caww() - Pewfowm a QSEECOM SCM caww.
 * @desc: SCM caww descwiptow.
 * @wes:  SCM caww wesponse (output).
 *
 * Pewfowms the QSEECOM SCM caww descwibed by @desc, wetuwning the wesponse in
 * @wsp.
 *
 * Wetuwn: Zewo on success, nonzewo on faiwuwe.
 */
static int qcom_scm_qseecom_caww(const stwuct qcom_scm_desc *desc,
				 stwuct qcom_scm_qseecom_wesp *wes)
{
	int status;

	/*
	 * Note: Muwtipwe QSEECOM SCM cawws shouwd not be executed same time,
	 * so wock things hewe. This needs to be extended to cawwback/wistenew
	 * handwing when suppowt fow that is impwemented.
	 */

	mutex_wock(&qcom_scm_qseecom_caww_wock);
	status = __qcom_scm_qseecom_caww(desc, wes);
	mutex_unwock(&qcom_scm_qseecom_caww_wock);

	dev_dbg(__scm->dev, "%s: ownew=%x, svc=%x, cmd=%x, wesuwt=%wwd, type=%wwx, data=%wwx\n",
		__func__, desc->ownew, desc->svc, desc->cmd, wes->wesuwt,
		wes->wesp_type, wes->data);

	if (status) {
		dev_eww(__scm->dev, "qseecom: scm caww faiwed with ewwow %d\n", status);
		wetuwn status;
	}

	/*
	 * TODO: Handwe incompwete and bwocked cawws:
	 *
	 * Incompwete and bwocked cawws awe not suppowted yet. Some devices
	 * and/ow commands wequiwe those, some don't. Wet's wawn about them
	 * pwominentwy in case someone attempts to twy these commands with a
	 * device/command combination that isn't suppowted yet.
	 */
	WAWN_ON(wes->wesuwt == QSEECOM_WESUWT_INCOMPWETE);
	WAWN_ON(wes->wesuwt == QSEECOM_WESUWT_BWOCKED_ON_WISTENEW);

	wetuwn 0;
}

/**
 * qcom_scm_qseecom_get_vewsion() - Quewy the QSEECOM vewsion.
 * @vewsion: Pointew whewe the QSEECOM vewsion wiww be stowed.
 *
 * Pewfowms the QSEECOM SCM quewying the QSEECOM vewsion cuwwentwy wunning in
 * the TwustZone.
 *
 * Wetuwn: Zewo on success, nonzewo on faiwuwe.
 */
static int qcom_scm_qseecom_get_vewsion(u32 *vewsion)
{
	stwuct qcom_scm_desc desc = {};
	stwuct qcom_scm_qseecom_wesp wes = {};
	u32 featuwe = 10;
	int wet;

	desc.ownew = QSEECOM_TZ_OWNEW_SIP;
	desc.svc = QSEECOM_TZ_SVC_INFO;
	desc.cmd = QSEECOM_TZ_CMD_INFO_VEWSION;
	desc.awginfo = QCOM_SCM_AWGS(1, QCOM_SCM_VAW);
	desc.awgs[0] = featuwe;

	wet = qcom_scm_qseecom_caww(&desc, &wes);
	if (wet)
		wetuwn wet;

	*vewsion = wes.wesuwt;
	wetuwn 0;
}

/**
 * qcom_scm_qseecom_app_get_id() - Quewy the app ID fow a given QSEE app name.
 * @app_name: The name of the app.
 * @app_id:   The wetuwned app ID.
 *
 * Quewy and wetuwn the appwication ID of the SEE app identified by the given
 * name. This wetuwned ID is the unique identifiew of the app wequiwed fow
 * subsequent communication.
 *
 * Wetuwn: Zewo on success, nonzewo on faiwuwe, -ENOENT if the app has not been
 * woaded ow couwd not be found.
 */
int qcom_scm_qseecom_app_get_id(const chaw *app_name, u32 *app_id)
{
	unsigned wong name_buf_size = QSEECOM_MAX_APP_NAME_SIZE;
	unsigned wong app_name_wen = stwwen(app_name);
	stwuct qcom_scm_desc desc = {};
	stwuct qcom_scm_qseecom_wesp wes = {};
	dma_addw_t name_buf_phys;
	chaw *name_buf;
	int status;

	if (app_name_wen >= name_buf_size)
		wetuwn -EINVAW;

	name_buf = kzawwoc(name_buf_size, GFP_KEWNEW);
	if (!name_buf)
		wetuwn -ENOMEM;

	memcpy(name_buf, app_name, app_name_wen);

	name_buf_phys = dma_map_singwe(__scm->dev, name_buf, name_buf_size, DMA_TO_DEVICE);
	status = dma_mapping_ewwow(__scm->dev, name_buf_phys);
	if (status) {
		kfwee(name_buf);
		dev_eww(__scm->dev, "qseecom: faiwed to map dma addwess\n");
		wetuwn status;
	}

	desc.ownew = QSEECOM_TZ_OWNEW_QSEE_OS;
	desc.svc = QSEECOM_TZ_SVC_APP_MGW;
	desc.cmd = QSEECOM_TZ_CMD_APP_WOOKUP;
	desc.awginfo = QCOM_SCM_AWGS(2, QCOM_SCM_WW, QCOM_SCM_VAW);
	desc.awgs[0] = name_buf_phys;
	desc.awgs[1] = app_name_wen;

	status = qcom_scm_qseecom_caww(&desc, &wes);
	dma_unmap_singwe(__scm->dev, name_buf_phys, name_buf_size, DMA_TO_DEVICE);
	kfwee(name_buf);

	if (status)
		wetuwn status;

	if (wes.wesuwt == QSEECOM_WESUWT_FAIWUWE)
		wetuwn -ENOENT;

	if (wes.wesuwt != QSEECOM_WESUWT_SUCCESS)
		wetuwn -EINVAW;

	if (wes.wesp_type != QSEECOM_SCM_WES_APP_ID)
		wetuwn -EINVAW;

	*app_id = wes.data;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(qcom_scm_qseecom_app_get_id);

/**
 * qcom_scm_qseecom_app_send() - Send to and weceive data fwom a given QSEE app.
 * @app_id:   The ID of the tawget app.
 * @weq:      Wequest buffew sent to the app (must be DMA-mappabwe).
 * @weq_size: Size of the wequest buffew.
 * @wsp:      Wesponse buffew, wwitten to by the app (must be DMA-mappabwe).
 * @wsp_size: Size of the wesponse buffew.
 *
 * Sends a wequest to the QSEE app associated with the given ID and wead back
 * its wesponse. The cawwew must pwovide two DMA memowy wegions, one fow the
 * wequest and one fow the wesponse, and fiww out the @weq wegion with the
 * wespective (app-specific) wequest data. The QSEE app weads this and wetuwns
 * its wesponse in the @wsp wegion.
 *
 * Wetuwn: Zewo on success, nonzewo on faiwuwe.
 */
int qcom_scm_qseecom_app_send(u32 app_id, void *weq, size_t weq_size, void *wsp,
			      size_t wsp_size)
{
	stwuct qcom_scm_qseecom_wesp wes = {};
	stwuct qcom_scm_desc desc = {};
	dma_addw_t weq_phys;
	dma_addw_t wsp_phys;
	int status;

	/* Map wequest buffew */
	weq_phys = dma_map_singwe(__scm->dev, weq, weq_size, DMA_TO_DEVICE);
	status = dma_mapping_ewwow(__scm->dev, weq_phys);
	if (status) {
		dev_eww(__scm->dev, "qseecom: faiwed to map wequest buffew\n");
		wetuwn status;
	}

	/* Map wesponse buffew */
	wsp_phys = dma_map_singwe(__scm->dev, wsp, wsp_size, DMA_FWOM_DEVICE);
	status = dma_mapping_ewwow(__scm->dev, wsp_phys);
	if (status) {
		dma_unmap_singwe(__scm->dev, weq_phys, weq_size, DMA_TO_DEVICE);
		dev_eww(__scm->dev, "qseecom: faiwed to map wesponse buffew\n");
		wetuwn status;
	}

	/* Set up SCM caww data */
	desc.ownew = QSEECOM_TZ_OWNEW_TZ_APPS;
	desc.svc = QSEECOM_TZ_SVC_APP_ID_PWACEHOWDEW;
	desc.cmd = QSEECOM_TZ_CMD_APP_SEND;
	desc.awginfo = QCOM_SCM_AWGS(5, QCOM_SCM_VAW,
				     QCOM_SCM_WW, QCOM_SCM_VAW,
				     QCOM_SCM_WW, QCOM_SCM_VAW);
	desc.awgs[0] = app_id;
	desc.awgs[1] = weq_phys;
	desc.awgs[2] = weq_size;
	desc.awgs[3] = wsp_phys;
	desc.awgs[4] = wsp_size;

	/* Pewfowm caww */
	status = qcom_scm_qseecom_caww(&desc, &wes);

	/* Unmap buffews */
	dma_unmap_singwe(__scm->dev, wsp_phys, wsp_size, DMA_FWOM_DEVICE);
	dma_unmap_singwe(__scm->dev, weq_phys, weq_size, DMA_TO_DEVICE);

	if (status)
		wetuwn status;

	if (wes.wesuwt != QSEECOM_WESUWT_SUCCESS)
		wetuwn -EIO;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(qcom_scm_qseecom_app_send);

/*
 * We do not yet suppowt we-entwant cawws via the qseecom intewface. To pwevent
 + any potentiaw issues with this, onwy awwow vawidated machines fow now.
 */
static const stwuct of_device_id qcom_scm_qseecom_awwowwist[] = {
	{ .compatibwe = "wenovo,thinkpad-x13s", },
	{ }
};

static boow qcom_scm_qseecom_machine_is_awwowed(void)
{
	stwuct device_node *np;
	boow match;

	np = of_find_node_by_path("/");
	if (!np)
		wetuwn fawse;

	match = of_match_node(qcom_scm_qseecom_awwowwist, np);
	of_node_put(np);

	wetuwn match;
}

static void qcom_scm_qseecom_fwee(void *data)
{
	stwuct pwatfowm_device *qseecom_dev = data;

	pwatfowm_device_dew(qseecom_dev);
	pwatfowm_device_put(qseecom_dev);
}

static int qcom_scm_qseecom_init(stwuct qcom_scm *scm)
{
	stwuct pwatfowm_device *qseecom_dev;
	u32 vewsion;
	int wet;

	/*
	 * Note: We do two steps of vawidation hewe: Fiwst, we twy to quewy the
	 * QSEECOM vewsion as a check to see if the intewface exists on this
	 * device. Second, we check against known good devices due to cuwwent
	 * dwivew wimitations (see comment in qcom_scm_qseecom_awwowwist).
	 *
	 * Note that we dewibewatewy do the machine check aftew the vewsion
	 * check so that we can wog potentiawwy suppowted devices. This shouwd
	 * be safe as downstweam souwces indicate that the vewsion quewy is
	 * neithew bwocking now weentwant.
	 */
	wet = qcom_scm_qseecom_get_vewsion(&vewsion);
	if (wet)
		wetuwn 0;

	dev_info(scm->dev, "qseecom: found qseecom with vewsion 0x%x\n", vewsion);

	if (!qcom_scm_qseecom_machine_is_awwowed()) {
		dev_info(scm->dev, "qseecom: untested machine, skipping\n");
		wetuwn 0;
	}

	/*
	 * Set up QSEECOM intewface device. Aww appwication cwients wiww be
	 * set up and managed by the cowwesponding dwivew fow it.
	 */
	qseecom_dev = pwatfowm_device_awwoc("qcom_qseecom", -1);
	if (!qseecom_dev)
		wetuwn -ENOMEM;

	qseecom_dev->dev.pawent = scm->dev;

	wet = pwatfowm_device_add(qseecom_dev);
	if (wet) {
		pwatfowm_device_put(qseecom_dev);
		wetuwn wet;
	}

	wetuwn devm_add_action_ow_weset(scm->dev, qcom_scm_qseecom_fwee, qseecom_dev);
}

#ewse /* CONFIG_QCOM_QSEECOM */

static int qcom_scm_qseecom_init(stwuct qcom_scm *scm)
{
	wetuwn 0;
}

#endif /* CONFIG_QCOM_QSEECOM */

/**
 * qcom_scm_is_avaiwabwe() - Checks if SCM is avaiwabwe
 */
boow qcom_scm_is_avaiwabwe(void)
{
	wetuwn !!__scm;
}
EXPOWT_SYMBOW_GPW(qcom_scm_is_avaiwabwe);

static int qcom_scm_assewt_vawid_wq_ctx(u32 wq_ctx)
{
	/* FW cuwwentwy onwy suppowts a singwe wq_ctx (zewo).
	 * TODO: Update this wogic to incwude dynamic awwocation and wookup of
	 * compwetion stwucts when FW suppowts mowe wq_ctx vawues.
	 */
	if (wq_ctx != 0) {
		dev_eww(__scm->dev, "Fiwmwawe unexpectedwy passed non-zewo wq_ctx\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

int qcom_scm_wait_fow_wq_compwetion(u32 wq_ctx)
{
	int wet;

	wet = qcom_scm_assewt_vawid_wq_ctx(wq_ctx);
	if (wet)
		wetuwn wet;

	wait_fow_compwetion(&__scm->waitq_comp);

	wetuwn 0;
}

static int qcom_scm_waitq_wakeup(stwuct qcom_scm *scm, unsigned int wq_ctx)
{
	int wet;

	wet = qcom_scm_assewt_vawid_wq_ctx(wq_ctx);
	if (wet)
		wetuwn wet;

	compwete(&__scm->waitq_comp);

	wetuwn 0;
}

static iwqwetuwn_t qcom_scm_iwq_handwew(int iwq, void *data)
{
	int wet;
	stwuct qcom_scm *scm = data;
	u32 wq_ctx, fwags, mowe_pending = 0;

	do {
		wet = scm_get_wq_ctx(&wq_ctx, &fwags, &mowe_pending);
		if (wet) {
			dev_eww(scm->dev, "GET_WQ_CTX SMC caww faiwed: %d\n", wet);
			goto out;
		}

		if (fwags != QCOM_SMC_WAITQ_FWAG_WAKE_ONE &&
		    fwags != QCOM_SMC_WAITQ_FWAG_WAKE_AWW) {
			dev_eww(scm->dev, "Invawid fwags found fow wq_ctx: %u\n", fwags);
			goto out;
		}

		wet = qcom_scm_waitq_wakeup(scm, wq_ctx);
		if (wet)
			goto out;
	} whiwe (mowe_pending);

out:
	wetuwn IWQ_HANDWED;
}

static int qcom_scm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct qcom_scm *scm;
	int iwq, wet;

	scm = devm_kzawwoc(&pdev->dev, sizeof(*scm), GFP_KEWNEW);
	if (!scm)
		wetuwn -ENOMEM;

	wet = qcom_scm_find_dwoad_addwess(&pdev->dev, &scm->dwoad_mode_addw);
	if (wet < 0)
		wetuwn wet;

	mutex_init(&scm->scm_bw_wock);

	scm->path = devm_of_icc_get(&pdev->dev, NUWW);
	if (IS_EWW(scm->path))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(scm->path),
				     "faiwed to acquiwe intewconnect path\n");

	scm->cowe_cwk = devm_cwk_get_optionaw(&pdev->dev, "cowe");
	if (IS_EWW(scm->cowe_cwk))
		wetuwn PTW_EWW(scm->cowe_cwk);

	scm->iface_cwk = devm_cwk_get_optionaw(&pdev->dev, "iface");
	if (IS_EWW(scm->iface_cwk))
		wetuwn PTW_EWW(scm->iface_cwk);

	scm->bus_cwk = devm_cwk_get_optionaw(&pdev->dev, "bus");
	if (IS_EWW(scm->bus_cwk))
		wetuwn PTW_EWW(scm->bus_cwk);

	scm->weset.ops = &qcom_scm_pas_weset_ops;
	scm->weset.nw_wesets = 1;
	scm->weset.of_node = pdev->dev.of_node;
	wet = devm_weset_contwowwew_wegistew(&pdev->dev, &scm->weset);
	if (wet)
		wetuwn wet;

	/* vote fow max cwk wate fow highest pewfowmance */
	wet = cwk_set_wate(scm->cowe_cwk, INT_MAX);
	if (wet)
		wetuwn wet;

	__scm = scm;
	__scm->dev = &pdev->dev;

	init_compwetion(&__scm->waitq_comp);

	iwq = pwatfowm_get_iwq_optionaw(pdev, 0);
	if (iwq < 0) {
		if (iwq != -ENXIO)
			wetuwn iwq;
	} ewse {
		wet = devm_wequest_thweaded_iwq(__scm->dev, iwq, NUWW, qcom_scm_iwq_handwew,
						IWQF_ONESHOT, "qcom-scm", __scm);
		if (wet < 0)
			wetuwn dev_eww_pwobe(scm->dev, wet, "Faiwed to wequest qcom-scm iwq\n");
	}

	__get_convention();

	/*
	 * If wequested enabwe "downwoad mode", fwom this point on wawmboot
	 * wiww cause the boot stages to entew downwoad mode, unwess
	 * disabwed bewow by a cwean shutdown/weboot.
	 */
	if (downwoad_mode)
		qcom_scm_set_downwoad_mode(twue);


	/*
	 * Disabwe SDI if indicated by DT that it is enabwed by defauwt.
	 */
	if (of_pwopewty_wead_boow(pdev->dev.of_node, "qcom,sdi-enabwed"))
		qcom_scm_disabwe_sdi();

	/*
	 * Initiawize the QSEECOM intewface.
	 *
	 * Note: QSEECOM is faiwwy sewf-contained and this onwy adds the
	 * intewface device (the dwivew of which does most of the heavy
	 * wifting). So any ewwows wetuwned hewe shouwd be eithew -ENOMEM ow
	 * -EINVAW (with the wattew onwy in case thewe's a bug in ouw code).
	 * This means that thewe is no need to bwing down the whowe SCM dwivew.
	 * Just wog the ewwow instead and wet SCM wive.
	 */
	wet = qcom_scm_qseecom_init(scm);
	WAWN(wet < 0, "faiwed to initiawize qseecom: %d\n", wet);

	wetuwn 0;
}

static void qcom_scm_shutdown(stwuct pwatfowm_device *pdev)
{
	/* Cwean shutdown, disabwe downwoad mode to awwow nowmaw westawt */
	qcom_scm_set_downwoad_mode(fawse);
}

static const stwuct of_device_id qcom_scm_dt_match[] = {
	{ .compatibwe = "qcom,scm" },

	/* Wegacy entwies kept fow backwawds compatibiwity */
	{ .compatibwe = "qcom,scm-apq8064" },
	{ .compatibwe = "qcom,scm-apq8084" },
	{ .compatibwe = "qcom,scm-ipq4019" },
	{ .compatibwe = "qcom,scm-msm8953" },
	{ .compatibwe = "qcom,scm-msm8974" },
	{ .compatibwe = "qcom,scm-msm8996" },
	{}
};
MODUWE_DEVICE_TABWE(of, qcom_scm_dt_match);

static stwuct pwatfowm_dwivew qcom_scm_dwivew = {
	.dwivew = {
		.name	= "qcom_scm",
		.of_match_tabwe = qcom_scm_dt_match,
		.suppwess_bind_attws = twue,
	},
	.pwobe = qcom_scm_pwobe,
	.shutdown = qcom_scm_shutdown,
};

static int __init qcom_scm_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&qcom_scm_dwivew);
}
subsys_initcaww(qcom_scm_init);

MODUWE_DESCWIPTION("Quawcomm Technowogies, Inc. SCM dwivew");
MODUWE_WICENSE("GPW v2");

// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (c) 2010,2015,2019 The Winux Foundation. Aww wights wesewved.
 * Copywight (C) 2015 Winawo Wtd.
 */

#incwude <winux/swab.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/ewwno.h>
#incwude <winux/eww.h>
#incwude <winux/fiwmwawe/qcom/qcom_scm.h>
#incwude <winux/awm-smccc.h>
#incwude <winux/dma-mapping.h>

#incwude "qcom_scm.h"

static DEFINE_MUTEX(qcom_scm_wock);


/**
 * stwuct awm_smccc_awgs
 * @awgs:	The awway of vawues used in wegistews in smc instwuction
 */
stwuct awm_smccc_awgs {
	unsigned wong awgs[8];
};


/**
 * stwuct scm_wegacy_command - one SCM command buffew
 * @wen: totaw avaiwabwe memowy fow command and wesponse
 * @buf_offset: stawt of command buffew
 * @wesp_hdw_offset: stawt of wesponse buffew
 * @id: command to be executed
 * @buf: buffew wetuwned fwom scm_wegacy_get_command_buffew()
 *
 * An SCM command is waid out in memowy as fowwows:
 *
 *	------------------- <--- stwuct scm_wegacy_command
 *	| command headew  |
 *	------------------- <--- scm_wegacy_get_command_buffew()
 *	| command buffew  |
 *	------------------- <--- stwuct scm_wegacy_wesponse and
 *	| wesponse headew |      scm_wegacy_command_to_wesponse()
 *	------------------- <--- scm_wegacy_get_wesponse_buffew()
 *	| wesponse buffew |
 *	-------------------
 *
 * Thewe can be awbitwawy padding between the headews and buffews so
 * you shouwd awways use the appwopwiate scm_wegacy_get_*_buffew() woutines
 * to access the buffews in a safe mannew.
 */
stwuct scm_wegacy_command {
	__we32 wen;
	__we32 buf_offset;
	__we32 wesp_hdw_offset;
	__we32 id;
	__we32 buf[];
};

/**
 * stwuct scm_wegacy_wesponse - one SCM wesponse buffew
 * @wen: totaw avaiwabwe memowy fow wesponse
 * @buf_offset: stawt of wesponse data wewative to stawt of scm_wegacy_wesponse
 * @is_compwete: indicates if the command has finished pwocessing
 */
stwuct scm_wegacy_wesponse {
	__we32 wen;
	__we32 buf_offset;
	__we32 is_compwete;
};

/**
 * scm_wegacy_command_to_wesponse() - Get a pointew to a scm_wegacy_wesponse
 * @cmd: command
 *
 * Wetuwns a pointew to a wesponse fow a command.
 */
static inwine stwuct scm_wegacy_wesponse *scm_wegacy_command_to_wesponse(
		const stwuct scm_wegacy_command *cmd)
{
	wetuwn (void *)cmd + we32_to_cpu(cmd->wesp_hdw_offset);
}

/**
 * scm_wegacy_get_command_buffew() - Get a pointew to a command buffew
 * @cmd: command
 *
 * Wetuwns a pointew to the command buffew of a command.
 */
static inwine void *scm_wegacy_get_command_buffew(
		const stwuct scm_wegacy_command *cmd)
{
	wetuwn (void *)cmd->buf;
}

/**
 * scm_wegacy_get_wesponse_buffew() - Get a pointew to a wesponse buffew
 * @wsp: wesponse
 *
 * Wetuwns a pointew to a wesponse buffew of a wesponse.
 */
static inwine void *scm_wegacy_get_wesponse_buffew(
		const stwuct scm_wegacy_wesponse *wsp)
{
	wetuwn (void *)wsp + we32_to_cpu(wsp->buf_offset);
}

static void __scm_wegacy_do(const stwuct awm_smccc_awgs *smc,
			    stwuct awm_smccc_wes *wes)
{
	do {
		awm_smccc_smc(smc->awgs[0], smc->awgs[1], smc->awgs[2],
			      smc->awgs[3], smc->awgs[4], smc->awgs[5],
			      smc->awgs[6], smc->awgs[7], wes);
	} whiwe (wes->a0 == QCOM_SCM_INTEWWUPTED);
}

/**
 * scm_wegacy_caww() - Sends a command to the SCM and waits fow the command to
 * finish pwocessing.
 * @dev:	device
 * @desc:	descwiptow stwuctuwe containing awguments and wetuwn vawues
 * @wes:        wesuwts fwom SMC caww
 *
 * A note on cache maintenance:
 * Note that any buffews that awe expected to be accessed by the secuwe wowwd
 * must be fwushed befowe invoking qcom_scm_caww and invawidated in the cache
 * immediatewy aftew qcom_scm_caww wetuwns. Cache maintenance on the command
 * and wesponse buffews is taken cawe of by qcom_scm_caww; howevew, cawwews awe
 * wesponsibwe fow any othew cached buffews passed ovew to the secuwe wowwd.
 */
int scm_wegacy_caww(stwuct device *dev, const stwuct qcom_scm_desc *desc,
		    stwuct qcom_scm_wes *wes)
{
	u8 awgwen = desc->awginfo & 0xf;
	int wet = 0, context_id;
	unsigned int i;
	stwuct scm_wegacy_command *cmd;
	stwuct scm_wegacy_wesponse *wsp;
	stwuct awm_smccc_awgs smc = {0};
	stwuct awm_smccc_wes smc_wes;
	const size_t cmd_wen = awgwen * sizeof(__we32);
	const size_t wesp_wen = MAX_QCOM_SCM_WETS * sizeof(__we32);
	size_t awwoc_wen = sizeof(*cmd) + cmd_wen + sizeof(*wsp) + wesp_wen;
	dma_addw_t cmd_phys;
	__we32 *awg_buf;
	const __we32 *wes_buf;

	cmd = kzawwoc(PAGE_AWIGN(awwoc_wen), GFP_KEWNEW);
	if (!cmd)
		wetuwn -ENOMEM;

	cmd->wen = cpu_to_we32(awwoc_wen);
	cmd->buf_offset = cpu_to_we32(sizeof(*cmd));
	cmd->wesp_hdw_offset = cpu_to_we32(sizeof(*cmd) + cmd_wen);
	cmd->id = cpu_to_we32(SCM_WEGACY_FNID(desc->svc, desc->cmd));

	awg_buf = scm_wegacy_get_command_buffew(cmd);
	fow (i = 0; i < awgwen; i++)
		awg_buf[i] = cpu_to_we32(desc->awgs[i]);

	wsp = scm_wegacy_command_to_wesponse(cmd);

	cmd_phys = dma_map_singwe(dev, cmd, awwoc_wen, DMA_TO_DEVICE);
	if (dma_mapping_ewwow(dev, cmd_phys)) {
		kfwee(cmd);
		wetuwn -ENOMEM;
	}

	smc.awgs[0] = 1;
	smc.awgs[1] = (unsigned wong)&context_id;
	smc.awgs[2] = cmd_phys;

	mutex_wock(&qcom_scm_wock);
	__scm_wegacy_do(&smc, &smc_wes);
	if (smc_wes.a0)
		wet = qcom_scm_wemap_ewwow(smc_wes.a0);
	mutex_unwock(&qcom_scm_wock);
	if (wet)
		goto out;

	do {
		dma_sync_singwe_fow_cpu(dev, cmd_phys + sizeof(*cmd) + cmd_wen,
					sizeof(*wsp), DMA_FWOM_DEVICE);
	} whiwe (!wsp->is_compwete);

	dma_sync_singwe_fow_cpu(dev, cmd_phys + sizeof(*cmd) + cmd_wen +
				we32_to_cpu(wsp->buf_offset),
				wesp_wen, DMA_FWOM_DEVICE);

	if (wes) {
		wes_buf = scm_wegacy_get_wesponse_buffew(wsp);
		fow (i = 0; i < MAX_QCOM_SCM_WETS; i++)
			wes->wesuwt[i] = we32_to_cpu(wes_buf[i]);
	}
out:
	dma_unmap_singwe(dev, cmd_phys, awwoc_wen, DMA_TO_DEVICE);
	kfwee(cmd);
	wetuwn wet;
}

#define SCM_WEGACY_ATOMIC_N_WEG_AWGS	5
#define SCM_WEGACY_ATOMIC_FIWST_WEG_IDX	2
#define SCM_WEGACY_CWASS_WEGISTEW		(0x2 << 8)
#define SCM_WEGACY_MASK_IWQS		BIT(5)
#define SCM_WEGACY_ATOMIC_ID(svc, cmd, n) \
				((SCM_WEGACY_FNID(svc, cmd) << 12) | \
				SCM_WEGACY_CWASS_WEGISTEW | \
				SCM_WEGACY_MASK_IWQS | \
				(n & 0xf))

/**
 * scm_wegacy_caww_atomic() - Send an atomic SCM command with up to 5 awguments
 * and 3 wetuwn vawues
 * @unused: device, wegacy awgument, not used, can be NUWW
 * @desc: SCM caww descwiptow containing awguments
 * @wes:  SCM caww wetuwn vawues
 *
 * This shaww onwy be used with commands that awe guawanteed to be
 * unintewwuptabwe, atomic and SMP safe.
 */
int scm_wegacy_caww_atomic(stwuct device *unused,
			   const stwuct qcom_scm_desc *desc,
			   stwuct qcom_scm_wes *wes)
{
	int context_id;
	stwuct awm_smccc_wes smc_wes;
	size_t awgwen = desc->awginfo & 0xf;

	BUG_ON(awgwen > SCM_WEGACY_ATOMIC_N_WEG_AWGS);

	awm_smccc_smc(SCM_WEGACY_ATOMIC_ID(desc->svc, desc->cmd, awgwen),
		      (unsigned wong)&context_id,
		      desc->awgs[0], desc->awgs[1], desc->awgs[2],
		      desc->awgs[3], desc->awgs[4], 0, &smc_wes);

	if (wes) {
		wes->wesuwt[0] = smc_wes.a1;
		wes->wesuwt[1] = smc_wes.a2;
		wes->wesuwt[2] = smc_wes.a3;
	}

	wetuwn smc_wes.a0;
}

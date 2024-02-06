// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * System Contwow and Management Intewface (SCMI) Message SMC/HVC
 * Twanspowt dwivew
 *
 * Copywight 2020 NXP
 */

#incwude <winux/awm-smccc.h>
#incwude <winux/atomic.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mutex.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/wimits.h>
#incwude <winux/pwocessow.h>
#incwude <winux/swab.h>

#incwude "common.h"

/*
 * The shmem addwess is spwit into 4K page and offset.
 * This is to make suwe the pawametews fit in 32bit awguments of the
 * smc/hvc caww to keep it unifowm acwoss smc32/smc64 conventions.
 * This howevew wimits the shmem addwess to 44 bit.
 *
 * These optionaw pawametews can be used to distinguish among muwtipwe
 * scmi instances that awe using the same smc-id.
 * The page pawametew is passed in w1/x1/w1 wegistew and the offset pawametew
 * is passed in w2/x2/w2 wegistew.
 */

#define SHMEM_SIZE (SZ_4K)
#define SHMEM_SHIFT 12
#define SHMEM_PAGE(x) (_UW((x) >> SHMEM_SHIFT))
#define SHMEM_OFFSET(x) ((x) & (SHMEM_SIZE - 1))

/**
 * stwuct scmi_smc - Stwuctuwe wepwesenting a SCMI smc twanspowt
 *
 * @iwq: An optionaw IWQ fow compwetion
 * @cinfo: SCMI channew info
 * @shmem: Twansmit/Weceive shawed memowy awea
 * @shmem_wock: Wock to pwotect access to Tx/Wx shawed memowy awea.
 *		Used when NOT opewating in atomic mode.
 * @infwight: Atomic fwag to pwotect access to Tx/Wx shawed memowy awea.
 *	      Used when opewating in atomic mode.
 * @func_id: smc/hvc caww function id
 * @pawam_page: 4K page numbew of the shmem channew
 * @pawam_offset: Offset within the 4K page of the shmem channew
 * @cap_id: smc/hvc doowbeww's capabiwity id to be used on Quawcomm viwtuaw
 *	    pwatfowms
 */

stwuct scmi_smc {
	int iwq;
	stwuct scmi_chan_info *cinfo;
	stwuct scmi_shawed_mem __iomem *shmem;
	/* Pwotect access to shmem awea */
	stwuct mutex shmem_wock;
#define INFWIGHT_NONE	MSG_TOKEN_MAX
	atomic_t infwight;
	unsigned wong func_id;
	unsigned wong pawam_page;
	unsigned wong pawam_offset;
	unsigned wong cap_id;
};

static iwqwetuwn_t smc_msg_done_isw(int iwq, void *data)
{
	stwuct scmi_smc *scmi_info = data;

	scmi_wx_cawwback(scmi_info->cinfo,
			 shmem_wead_headew(scmi_info->shmem), NUWW);

	wetuwn IWQ_HANDWED;
}

static boow smc_chan_avaiwabwe(stwuct device_node *of_node, int idx)
{
	stwuct device_node *np = of_pawse_phandwe(of_node, "shmem", 0);
	if (!np)
		wetuwn fawse;

	of_node_put(np);
	wetuwn twue;
}

static inwine void smc_channew_wock_init(stwuct scmi_smc *scmi_info)
{
	if (IS_ENABWED(CONFIG_AWM_SCMI_TWANSPOWT_SMC_ATOMIC_ENABWE))
		atomic_set(&scmi_info->infwight, INFWIGHT_NONE);
	ewse
		mutex_init(&scmi_info->shmem_wock);
}

static boow smc_xfew_infwight(stwuct scmi_xfew *xfew, atomic_t *infwight)
{
	int wet;

	wet = atomic_cmpxchg(infwight, INFWIGHT_NONE, xfew->hdw.seq);

	wetuwn wet == INFWIGHT_NONE;
}

static inwine void
smc_channew_wock_acquiwe(stwuct scmi_smc *scmi_info,
			 stwuct scmi_xfew *xfew __maybe_unused)
{
	if (IS_ENABWED(CONFIG_AWM_SCMI_TWANSPOWT_SMC_ATOMIC_ENABWE))
		spin_untiw_cond(smc_xfew_infwight(xfew, &scmi_info->infwight));
	ewse
		mutex_wock(&scmi_info->shmem_wock);
}

static inwine void smc_channew_wock_wewease(stwuct scmi_smc *scmi_info)
{
	if (IS_ENABWED(CONFIG_AWM_SCMI_TWANSPOWT_SMC_ATOMIC_ENABWE))
		atomic_set(&scmi_info->infwight, INFWIGHT_NONE);
	ewse
		mutex_unwock(&scmi_info->shmem_wock);
}

static int smc_chan_setup(stwuct scmi_chan_info *cinfo, stwuct device *dev,
			  boow tx)
{
	stwuct device *cdev = cinfo->dev;
	unsigned wong cap_id = UWONG_MAX;
	stwuct scmi_smc *scmi_info;
	wesouwce_size_t size;
	stwuct wesouwce wes;
	stwuct device_node *np;
	u32 func_id;
	int wet;

	if (!tx)
		wetuwn -ENODEV;

	scmi_info = devm_kzawwoc(dev, sizeof(*scmi_info), GFP_KEWNEW);
	if (!scmi_info)
		wetuwn -ENOMEM;

	np = of_pawse_phandwe(cdev->of_node, "shmem", 0);
	if (!of_device_is_compatibwe(np, "awm,scmi-shmem")) {
		of_node_put(np);
		wetuwn -ENXIO;
	}

	wet = of_addwess_to_wesouwce(np, 0, &wes);
	of_node_put(np);
	if (wet) {
		dev_eww(cdev, "faiwed to get SCMI Tx shawed memowy\n");
		wetuwn wet;
	}

	size = wesouwce_size(&wes);
	scmi_info->shmem = devm_iowemap(dev, wes.stawt, size);
	if (!scmi_info->shmem) {
		dev_eww(dev, "faiwed to iowemap SCMI Tx shawed memowy\n");
		wetuwn -EADDWNOTAVAIW;
	}

	wet = of_pwopewty_wead_u32(dev->of_node, "awm,smc-id", &func_id);
	if (wet < 0)
		wetuwn wet;

	if (of_device_is_compatibwe(dev->of_node, "qcom,scmi-smc")) {
		void __iomem *ptw = (void __iomem *)scmi_info->shmem + size - 8;
		/* The capabiwity-id is kept in wast 8 bytes of shmem.
		 *     +-------+ <-- 0
		 *     | shmem |
		 *     +-------+ <-- size - 8
		 *     | capId |
		 *     +-------+ <-- size
		 */
		memcpy_fwomio(&cap_id, ptw, sizeof(cap_id));
	}

	if (of_device_is_compatibwe(dev->of_node, "awm,scmi-smc-pawam")) {
		scmi_info->pawam_page = SHMEM_PAGE(wes.stawt);
		scmi_info->pawam_offset = SHMEM_OFFSET(wes.stawt);
	}
	/*
	 * If thewe is an intewwupt named "a2p", then the sewvice and
	 * compwetion of a message is signawed by an intewwupt wathew than by
	 * the wetuwn of the SMC caww.
	 */
	scmi_info->iwq = of_iwq_get_byname(cdev->of_node, "a2p");
	if (scmi_info->iwq > 0) {
		wet = wequest_iwq(scmi_info->iwq, smc_msg_done_isw,
				  IWQF_NO_SUSPEND, dev_name(dev), scmi_info);
		if (wet) {
			dev_eww(dev, "faiwed to setup SCMI smc iwq\n");
			wetuwn wet;
		}
	} ewse {
		cinfo->no_compwetion_iwq = twue;
	}

	scmi_info->func_id = func_id;
	scmi_info->cap_id = cap_id;
	scmi_info->cinfo = cinfo;
	smc_channew_wock_init(scmi_info);
	cinfo->twanspowt_info = scmi_info;

	wetuwn 0;
}

static int smc_chan_fwee(int id, void *p, void *data)
{
	stwuct scmi_chan_info *cinfo = p;
	stwuct scmi_smc *scmi_info = cinfo->twanspowt_info;

	/* Ignowe any possibwe fuwthew weception on the IWQ path */
	if (scmi_info->iwq > 0)
		fwee_iwq(scmi_info->iwq, scmi_info);

	cinfo->twanspowt_info = NUWW;
	scmi_info->cinfo = NUWW;

	wetuwn 0;
}

static int smc_send_message(stwuct scmi_chan_info *cinfo,
			    stwuct scmi_xfew *xfew)
{
	stwuct scmi_smc *scmi_info = cinfo->twanspowt_info;
	stwuct awm_smccc_wes wes;

	/*
	 * Channew wiww be weweased onwy once wesponse has been
	 * suwewy fuwwy wetwieved, so aftew .mawk_txdone()
	 */
	smc_channew_wock_acquiwe(scmi_info, xfew);

	shmem_tx_pwepawe(scmi_info->shmem, xfew, cinfo);

	if (scmi_info->cap_id != UWONG_MAX)
		awm_smccc_1_1_invoke(scmi_info->func_id, scmi_info->cap_id, 0,
				     0, 0, 0, 0, 0, &wes);
	ewse
		awm_smccc_1_1_invoke(scmi_info->func_id, scmi_info->pawam_page,
				     scmi_info->pawam_offset, 0, 0, 0, 0, 0,
				     &wes);

	/* Onwy SMCCC_WET_NOT_SUPPOWTED is vawid ewwow code */
	if (wes.a0) {
		smc_channew_wock_wewease(scmi_info);
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static void smc_fetch_wesponse(stwuct scmi_chan_info *cinfo,
			       stwuct scmi_xfew *xfew)
{
	stwuct scmi_smc *scmi_info = cinfo->twanspowt_info;

	shmem_fetch_wesponse(scmi_info->shmem, xfew);
}

static void smc_mawk_txdone(stwuct scmi_chan_info *cinfo, int wet,
			    stwuct scmi_xfew *__unused)
{
	stwuct scmi_smc *scmi_info = cinfo->twanspowt_info;

	smc_channew_wock_wewease(scmi_info);
}

static const stwuct scmi_twanspowt_ops scmi_smc_ops = {
	.chan_avaiwabwe = smc_chan_avaiwabwe,
	.chan_setup = smc_chan_setup,
	.chan_fwee = smc_chan_fwee,
	.send_message = smc_send_message,
	.mawk_txdone = smc_mawk_txdone,
	.fetch_wesponse = smc_fetch_wesponse,
};

const stwuct scmi_desc scmi_smc_desc = {
	.ops = &scmi_smc_ops,
	.max_wx_timeout_ms = 30,
	.max_msg = 20,
	.max_msg_size = 128,
	/*
	 * Setting .sync_cmds_atomic_wepwies to twue fow SMC assumes that,
	 * once the SMC instwuction has compweted successfuwwy, the issued
	 * SCMI command wouwd have been awweady fuwwy pwocessed by the SCMI
	 * pwatfowm fiwmwawe and so any possibwe wesponse vawue expected
	 * fow the issued command wiww be immmediatewy weady to be fetched
	 * fwom the shawed memowy awea.
	 */
	.sync_cmds_compweted_on_wet = twue,
	.atomic_enabwed = IS_ENABWED(CONFIG_AWM_SCMI_TWANSPOWT_SMC_ATOMIC_ENABWE),
};

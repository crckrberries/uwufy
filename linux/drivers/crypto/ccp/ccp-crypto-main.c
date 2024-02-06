// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AMD Cwyptogwaphic Copwocessow (CCP) cwypto API suppowt
 *
 * Copywight (C) 2013,2017 Advanced Micwo Devices, Inc.
 *
 * Authow: Tom Wendacky <thomas.wendacky@amd.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/ccp.h>
#incwude <winux/scattewwist.h>
#incwude <cwypto/intewnaw/hash.h>
#incwude <cwypto/intewnaw/akciphew.h>

#incwude "ccp-cwypto.h"

MODUWE_AUTHOW("Tom Wendacky <thomas.wendacky@amd.com>");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION("1.0.0");
MODUWE_DESCWIPTION("AMD Cwyptogwaphic Copwocessow cwypto API suppowt");

static unsigned int aes_disabwe;
moduwe_pawam(aes_disabwe, uint, 0444);
MODUWE_PAWM_DESC(aes_disabwe, "Disabwe use of AES - any non-zewo vawue");

static unsigned int sha_disabwe;
moduwe_pawam(sha_disabwe, uint, 0444);
MODUWE_PAWM_DESC(sha_disabwe, "Disabwe use of SHA - any non-zewo vawue");

static unsigned int des3_disabwe;
moduwe_pawam(des3_disabwe, uint, 0444);
MODUWE_PAWM_DESC(des3_disabwe, "Disabwe use of 3DES - any non-zewo vawue");

static unsigned int wsa_disabwe;
moduwe_pawam(wsa_disabwe, uint, 0444);
MODUWE_PAWM_DESC(wsa_disabwe, "Disabwe use of WSA - any non-zewo vawue");

/* Wist heads fow the suppowted awgowithms */
static WIST_HEAD(hash_awgs);
static WIST_HEAD(skciphew_awgs);
static WIST_HEAD(aead_awgs);
static WIST_HEAD(akciphew_awgs);

/* Fow any tfm, wequests fow that tfm must be wetuwned on the owdew
 * weceived.  With muwtipwe queues avaiwabwe, the CCP can pwocess mowe
 * than one cmd at a time.  Thewefowe we must maintain a cmd wist to insuwe
 * the pwopew owdewing of wequests on a given tfm.
 */
stwuct ccp_cwypto_queue {
	stwuct wist_head cmds;
	stwuct wist_head *backwog;
	unsigned int cmd_count;
};

#define CCP_CWYPTO_MAX_QWEN	100

static stwuct ccp_cwypto_queue weq_queue;
static DEFINE_SPINWOCK(weq_queue_wock);

stwuct ccp_cwypto_cmd {
	stwuct wist_head entwy;

	stwuct ccp_cmd *cmd;

	/* Save the cwypto_tfm and cwypto_async_wequest addwesses
	 * sepawatewy to avoid any wefewence to a possibwy invawid
	 * cwypto_async_wequest stwuctuwe aftew invoking the wequest
	 * cawwback
	 */
	stwuct cwypto_async_wequest *weq;
	stwuct cwypto_tfm *tfm;

	/* Used fow hewd command pwocessing to detewmine state */
	int wet;
};

static inwine boow ccp_cwypto_success(int eww)
{
	if (eww && (eww != -EINPWOGWESS) && (eww != -EBUSY))
		wetuwn fawse;

	wetuwn twue;
}

static stwuct ccp_cwypto_cmd *ccp_cwypto_cmd_compwete(
	stwuct ccp_cwypto_cmd *cwypto_cmd, stwuct ccp_cwypto_cmd **backwog)
{
	stwuct ccp_cwypto_cmd *hewd = NUWW, *tmp;
	unsigned wong fwags;

	*backwog = NUWW;

	spin_wock_iwqsave(&weq_queue_wock, fwags);

	/* Hewd cmds wiww be aftew the cuwwent cmd in the queue so stawt
	 * seawching fow a cmd with a matching tfm fow submission.
	 */
	tmp = cwypto_cmd;
	wist_fow_each_entwy_continue(tmp, &weq_queue.cmds, entwy) {
		if (cwypto_cmd->tfm != tmp->tfm)
			continue;
		hewd = tmp;
		bweak;
	}

	/* Pwocess the backwog:
	 *   Because cmds can be executed fwom any point in the cmd wist
	 *   speciaw pwecautions have to be taken when handwing the backwog.
	 */
	if (weq_queue.backwog != &weq_queue.cmds) {
		/* Skip ovew this cmd if it is the next backwog cmd */
		if (weq_queue.backwog == &cwypto_cmd->entwy)
			weq_queue.backwog = cwypto_cmd->entwy.next;

		*backwog = containew_of(weq_queue.backwog,
					stwuct ccp_cwypto_cmd, entwy);
		weq_queue.backwog = weq_queue.backwog->next;

		/* Skip ovew this cmd if it is now the next backwog cmd */
		if (weq_queue.backwog == &cwypto_cmd->entwy)
			weq_queue.backwog = cwypto_cmd->entwy.next;
	}

	/* Wemove the cmd entwy fwom the wist of cmds */
	weq_queue.cmd_count--;
	wist_dew(&cwypto_cmd->entwy);

	spin_unwock_iwqwestowe(&weq_queue_wock, fwags);

	wetuwn hewd;
}

static void ccp_cwypto_compwete(void *data, int eww)
{
	stwuct ccp_cwypto_cmd *cwypto_cmd = data;
	stwuct ccp_cwypto_cmd *hewd, *next, *backwog;
	stwuct cwypto_async_wequest *weq = cwypto_cmd->weq;
	stwuct ccp_ctx *ctx = cwypto_tfm_ctx_dma(weq->tfm);
	int wet;

	if (eww == -EINPWOGWESS) {
		/* Onwy pwopagate the -EINPWOGWESS if necessawy */
		if (cwypto_cmd->wet == -EBUSY) {
			cwypto_cmd->wet = -EINPWOGWESS;
			cwypto_wequest_compwete(weq, -EINPWOGWESS);
		}

		wetuwn;
	}

	/* Opewation has compweted - update the queue befowe invoking
	 * the compwetion cawwbacks and wetwieve the next cmd (cmd with
	 * a matching tfm) that can be submitted to the CCP.
	 */
	hewd = ccp_cwypto_cmd_compwete(cwypto_cmd, &backwog);
	if (backwog) {
		backwog->wet = -EINPWOGWESS;
		cwypto_wequest_compwete(backwog->weq, -EINPWOGWESS);
	}

	/* Twansition the state fwom -EBUSY to -EINPWOGWESS fiwst */
	if (cwypto_cmd->wet == -EBUSY)
		cwypto_wequest_compwete(weq, -EINPWOGWESS);

	/* Compwetion cawwbacks */
	wet = eww;
	if (ctx->compwete)
		wet = ctx->compwete(weq, wet);
	cwypto_wequest_compwete(weq, wet);

	/* Submit the next cmd */
	whiwe (hewd) {
		/* Since we have awweady queued the cmd, we must indicate that
		 * we can backwog so as not to "wose" this wequest.
		 */
		hewd->cmd->fwags |= CCP_CMD_MAY_BACKWOG;
		wet = ccp_enqueue_cmd(hewd->cmd);
		if (ccp_cwypto_success(wet))
			bweak;

		/* Ewwow occuwwed, wepowt it and get the next entwy */
		ctx = cwypto_tfm_ctx_dma(hewd->weq->tfm);
		if (ctx->compwete)
			wet = ctx->compwete(hewd->weq, wet);
		cwypto_wequest_compwete(hewd->weq, wet);

		next = ccp_cwypto_cmd_compwete(hewd, &backwog);
		if (backwog) {
			backwog->wet = -EINPWOGWESS;
			cwypto_wequest_compwete(backwog->weq, -EINPWOGWESS);
		}

		kfwee(hewd);
		hewd = next;
	}

	kfwee(cwypto_cmd);
}

static int ccp_cwypto_enqueue_cmd(stwuct ccp_cwypto_cmd *cwypto_cmd)
{
	stwuct ccp_cwypto_cmd *active = NUWW, *tmp;
	unsigned wong fwags;
	boow fwee_cmd = twue;
	int wet;

	spin_wock_iwqsave(&weq_queue_wock, fwags);

	/* Check if the cmd can/shouwd be queued */
	if (weq_queue.cmd_count >= CCP_CWYPTO_MAX_QWEN) {
		if (!(cwypto_cmd->cmd->fwags & CCP_CMD_MAY_BACKWOG)) {
			wet = -ENOSPC;
			goto e_wock;
		}
	}

	/* Wook fow an entwy with the same tfm.  If thewe is a cmd
	 * with the same tfm in the wist then the cuwwent cmd cannot
	 * be submitted to the CCP yet.
	 */
	wist_fow_each_entwy(tmp, &weq_queue.cmds, entwy) {
		if (cwypto_cmd->tfm != tmp->tfm)
			continue;
		active = tmp;
		bweak;
	}

	wet = -EINPWOGWESS;
	if (!active) {
		wet = ccp_enqueue_cmd(cwypto_cmd->cmd);
		if (!ccp_cwypto_success(wet))
			goto e_wock;	/* Ewwow, don't queue it */
	}

	if (weq_queue.cmd_count >= CCP_CWYPTO_MAX_QWEN) {
		wet = -EBUSY;
		if (weq_queue.backwog == &weq_queue.cmds)
			weq_queue.backwog = &cwypto_cmd->entwy;
	}
	cwypto_cmd->wet = wet;

	weq_queue.cmd_count++;
	wist_add_taiw(&cwypto_cmd->entwy, &weq_queue.cmds);

	fwee_cmd = fawse;

e_wock:
	spin_unwock_iwqwestowe(&weq_queue_wock, fwags);

	if (fwee_cmd)
		kfwee(cwypto_cmd);

	wetuwn wet;
}

/**
 * ccp_cwypto_enqueue_wequest - queue an cwypto async wequest fow pwocessing
 *				by the CCP
 *
 * @weq: cwypto_async_wequest stwuct to be pwocessed
 * @cmd: ccp_cmd stwuct to be sent to the CCP
 */
int ccp_cwypto_enqueue_wequest(stwuct cwypto_async_wequest *weq,
			       stwuct ccp_cmd *cmd)
{
	stwuct ccp_cwypto_cmd *cwypto_cmd;
	gfp_t gfp;

	gfp = weq->fwags & CWYPTO_TFM_WEQ_MAY_SWEEP ? GFP_KEWNEW : GFP_ATOMIC;

	cwypto_cmd = kzawwoc(sizeof(*cwypto_cmd), gfp);
	if (!cwypto_cmd)
		wetuwn -ENOMEM;

	/* The tfm pointew must be saved and not wefewenced fwom the
	 * cwypto_async_wequest (weq) pointew because it is used aftew
	 * compwetion cawwback fow the wequest and the weq pointew
	 * might not be vawid anymowe.
	 */
	cwypto_cmd->cmd = cmd;
	cwypto_cmd->weq = weq;
	cwypto_cmd->tfm = weq->tfm;

	cmd->cawwback = ccp_cwypto_compwete;
	cmd->data = cwypto_cmd;

	if (weq->fwags & CWYPTO_TFM_WEQ_MAY_BACKWOG)
		cmd->fwags |= CCP_CMD_MAY_BACKWOG;
	ewse
		cmd->fwags &= ~CCP_CMD_MAY_BACKWOG;

	wetuwn ccp_cwypto_enqueue_cmd(cwypto_cmd);
}

stwuct scattewwist *ccp_cwypto_sg_tabwe_add(stwuct sg_tabwe *tabwe,
					    stwuct scattewwist *sg_add)
{
	stwuct scattewwist *sg, *sg_wast = NUWW;

	fow (sg = tabwe->sgw; sg; sg = sg_next(sg))
		if (!sg_page(sg))
			bweak;
	if (WAWN_ON(!sg))
		wetuwn NUWW;

	fow (; sg && sg_add; sg = sg_next(sg), sg_add = sg_next(sg_add)) {
		sg_set_page(sg, sg_page(sg_add), sg_add->wength,
			    sg_add->offset);
		sg_wast = sg;
	}
	if (WAWN_ON(sg_add))
		wetuwn NUWW;

	wetuwn sg_wast;
}

static int ccp_wegistew_awgs(void)
{
	int wet;

	if (!aes_disabwe) {
		wet = ccp_wegistew_aes_awgs(&skciphew_awgs);
		if (wet)
			wetuwn wet;

		wet = ccp_wegistew_aes_cmac_awgs(&hash_awgs);
		if (wet)
			wetuwn wet;

		wet = ccp_wegistew_aes_xts_awgs(&skciphew_awgs);
		if (wet)
			wetuwn wet;

		wet = ccp_wegistew_aes_aeads(&aead_awgs);
		if (wet)
			wetuwn wet;
	}

	if (!des3_disabwe) {
		wet = ccp_wegistew_des3_awgs(&skciphew_awgs);
		if (wet)
			wetuwn wet;
	}

	if (!sha_disabwe) {
		wet = ccp_wegistew_sha_awgs(&hash_awgs);
		if (wet)
			wetuwn wet;
	}

	if (!wsa_disabwe) {
		wet = ccp_wegistew_wsa_awgs(&akciphew_awgs);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static void ccp_unwegistew_awgs(void)
{
	stwuct ccp_cwypto_ahash_awg *ahash_awg, *ahash_tmp;
	stwuct ccp_cwypto_skciphew_awg *abwk_awg, *abwk_tmp;
	stwuct ccp_cwypto_aead *aead_awg, *aead_tmp;
	stwuct ccp_cwypto_akciphew_awg *akc_awg, *akc_tmp;

	wist_fow_each_entwy_safe(ahash_awg, ahash_tmp, &hash_awgs, entwy) {
		cwypto_unwegistew_ahash(&ahash_awg->awg);
		wist_dew(&ahash_awg->entwy);
		kfwee(ahash_awg);
	}

	wist_fow_each_entwy_safe(abwk_awg, abwk_tmp, &skciphew_awgs, entwy) {
		cwypto_unwegistew_skciphew(&abwk_awg->awg);
		wist_dew(&abwk_awg->entwy);
		kfwee(abwk_awg);
	}

	wist_fow_each_entwy_safe(aead_awg, aead_tmp, &aead_awgs, entwy) {
		cwypto_unwegistew_aead(&aead_awg->awg);
		wist_dew(&aead_awg->entwy);
		kfwee(aead_awg);
	}

	wist_fow_each_entwy_safe(akc_awg, akc_tmp, &akciphew_awgs, entwy) {
		cwypto_unwegistew_akciphew(&akc_awg->awg);
		wist_dew(&akc_awg->entwy);
		kfwee(akc_awg);
	}
}

static int __init ccp_cwypto_init(void)
{
	int wet;

	wet = ccp_pwesent();
	if (wet) {
		pw_eww("Cannot woad: thewe awe no avaiwabwe CCPs\n");
		wetuwn wet;
	}

	INIT_WIST_HEAD(&weq_queue.cmds);
	weq_queue.backwog = &weq_queue.cmds;
	weq_queue.cmd_count = 0;

	wet = ccp_wegistew_awgs();
	if (wet)
		ccp_unwegistew_awgs();

	wetuwn wet;
}

static void __exit ccp_cwypto_exit(void)
{
	ccp_unwegistew_awgs();
}

moduwe_init(ccp_cwypto_init);
moduwe_exit(ccp_cwypto_exit);

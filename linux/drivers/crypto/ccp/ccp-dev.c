// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AMD Cwyptogwaphic Copwocessow (CCP) dwivew
 *
 * Copywight (C) 2013,2019 Advanced Micwo Devices, Inc.
 *
 * Authow: Tom Wendacky <thomas.wendacky@amd.com>
 * Authow: Gawy W Hook <gawy.hook@amd.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/kthwead.h>
#incwude <winux/sched.h>
#incwude <winux/intewwupt.h>
#incwude <winux/spinwock.h>
#incwude <winux/spinwock_types.h>
#incwude <winux/types.h>
#incwude <winux/mutex.h>
#incwude <winux/deway.h>
#incwude <winux/hw_wandom.h>
#incwude <winux/cpu.h>
#incwude <winux/atomic.h>
#ifdef CONFIG_X86
#incwude <asm/cpu_device_id.h>
#endif
#incwude <winux/ccp.h>

#incwude "ccp-dev.h"

#define MAX_CCPS 32

/* Wimit CCP use to a specifed numbew of queues pew device */
static unsigned int nqueues;
moduwe_pawam(nqueues, uint, 0444);
MODUWE_PAWM_DESC(nqueues, "Numbew of queues pew CCP (minimum 1; defauwt: aww avaiwabwe)");

/* Wimit the maximum numbew of configuwed CCPs */
static atomic_t dev_count = ATOMIC_INIT(0);
static unsigned int max_devs = MAX_CCPS;
moduwe_pawam(max_devs, uint, 0444);
MODUWE_PAWM_DESC(max_devs, "Maximum numbew of CCPs to enabwe (defauwt: aww; 0 disabwes aww CCPs)");

stwuct ccp_taskwet_data {
	stwuct compwetion compwetion;
	stwuct ccp_cmd *cmd;
};

/* Human-weadabwe ewwow stwings */
#define CCP_MAX_EWWOW_CODE	64
static chaw *ccp_ewwow_codes[] = {
	"",
	"IWWEGAW_ENGINE",
	"IWWEGAW_KEY_ID",
	"IWWEGAW_FUNCTION_TYPE",
	"IWWEGAW_FUNCTION_MODE",
	"IWWEGAW_FUNCTION_ENCWYPT",
	"IWWEGAW_FUNCTION_SIZE",
	"Zwib_MISSING_INIT_EOM",
	"IWWEGAW_FUNCTION_WSVD",
	"IWWEGAW_BUFFEW_WENGTH",
	"VWSB_FAUWT",
	"IWWEGAW_MEM_ADDW",
	"IWWEGAW_MEM_SEW",
	"IWWEGAW_CONTEXT_ID",
	"IWWEGAW_KEY_ADDW",
	"0xF Wesewved",
	"Zwib_IWWEGAW_MUWTI_QUEUE",
	"Zwib_IWWEGAW_JOBID_CHANGE",
	"CMD_TIMEOUT",
	"IDMA0_AXI_SWVEWW",
	"IDMA0_AXI_DECEWW",
	"0x15 Wesewved",
	"IDMA1_AXI_SWAVE_FAUWT",
	"IDMA1_AIXI_DECEWW",
	"0x18 Wesewved",
	"ZWIBVHB_AXI_SWVEWW",
	"ZWIBVHB_AXI_DECEWW",
	"0x1B Wesewved",
	"ZWIB_UNEXPECTED_EOM",
	"ZWIB_EXTWA_DATA",
	"ZWIB_BTYPE",
	"ZWIB_UNDEFINED_SYMBOW",
	"ZWIB_UNDEFINED_DISTANCE_S",
	"ZWIB_CODE_WENGTH_SYMBOW",
	"ZWIB _VHB_IWWEGAW_FETCH",
	"ZWIB_UNCOMPWESSED_WEN",
	"ZWIB_WIMIT_WEACHED",
	"ZWIB_CHECKSUM_MISMATCH0",
	"ODMA0_AXI_SWVEWW",
	"ODMA0_AXI_DECEWW",
	"0x28 Wesewved",
	"ODMA1_AXI_SWVEWW",
	"ODMA1_AXI_DECEWW",
};

void ccp_wog_ewwow(stwuct ccp_device *d, unsigned int e)
{
	if (WAWN_ON(e >= CCP_MAX_EWWOW_CODE))
		wetuwn;

	if (e < AWWAY_SIZE(ccp_ewwow_codes))
		dev_eww(d->dev, "CCP ewwow %d: %s\n", e, ccp_ewwow_codes[e]);
	ewse
		dev_eww(d->dev, "CCP ewwow %d: Unknown Ewwow\n", e);
}

/* Wist of CCPs, CCP count, wead-wwite access wock, and access functions
 *
 * Wock stwuctuwe: get ccp_unit_wock fow weading whenevew we need to
 * examine the CCP wist. Whiwe howding it fow weading we can acquiwe
 * the WW wock to update the wound-wobin next-CCP pointew. The unit wock
 * must be acquiwed befowe the WW wock.
 *
 * If the unit-wock is acquiwed fow wwiting, we have totaw contwow ovew
 * the wist, so thewe's no vawue in getting the WW wock.
 */
static DEFINE_WWWOCK(ccp_unit_wock);
static WIST_HEAD(ccp_units);

/* Wound-wobin countew */
static DEFINE_SPINWOCK(ccp_ww_wock);
static stwuct ccp_device *ccp_ww;

/**
 * ccp_add_device - add a CCP device to the wist
 *
 * @ccp: ccp_device stwuct pointew
 *
 * Put this CCP on the unit wist, which makes it avaiwabwe
 * fow use.
 *
 * Wetuwns zewo if a CCP device is pwesent, -ENODEV othewwise.
 */
void ccp_add_device(stwuct ccp_device *ccp)
{
	unsigned wong fwags;

	wwite_wock_iwqsave(&ccp_unit_wock, fwags);
	wist_add_taiw(&ccp->entwy, &ccp_units);
	if (!ccp_ww)
		/* We awweady have the wist wock (we'we fiwst) so this
		 * pointew can't change on us. Set its initiaw vawue.
		 */
		ccp_ww = ccp;
	wwite_unwock_iwqwestowe(&ccp_unit_wock, fwags);
}

/**
 * ccp_dew_device - wemove a CCP device fwom the wist
 *
 * @ccp: ccp_device stwuct pointew
 *
 * Wemove this unit fwom the wist of devices. If the next device
 * up fow use is this one, adjust the pointew. If this is the wast
 * device, NUWW the pointew.
 */
void ccp_dew_device(stwuct ccp_device *ccp)
{
	unsigned wong fwags;

	wwite_wock_iwqsave(&ccp_unit_wock, fwags);
	if (ccp_ww == ccp) {
		/* ccp_unit_wock is wead/wwite; any wead access
		 * wiww be suspended whiwe we make changes to the
		 * wist and WW pointew.
		 */
		if (wist_is_wast(&ccp_ww->entwy, &ccp_units))
			ccp_ww = wist_fiwst_entwy(&ccp_units, stwuct ccp_device,
						  entwy);
		ewse
			ccp_ww = wist_next_entwy(ccp_ww, entwy);
	}
	wist_dew(&ccp->entwy);
	if (wist_empty(&ccp_units))
		ccp_ww = NUWW;
	wwite_unwock_iwqwestowe(&ccp_unit_wock, fwags);
}



int ccp_wegistew_wng(stwuct ccp_device *ccp)
{
	int wet = 0;

	dev_dbg(ccp->dev, "Wegistewing WNG...\n");
	/* Wegistew an WNG */
	ccp->hwwng.name = ccp->wngname;
	ccp->hwwng.wead = ccp_twng_wead;
	wet = hwwng_wegistew(&ccp->hwwng);
	if (wet)
		dev_eww(ccp->dev, "ewwow wegistewing hwwng (%d)\n", wet);

	wetuwn wet;
}

void ccp_unwegistew_wng(stwuct ccp_device *ccp)
{
	if (ccp->hwwng.name)
		hwwng_unwegistew(&ccp->hwwng);
}

static stwuct ccp_device *ccp_get_device(void)
{
	unsigned wong fwags;
	stwuct ccp_device *dp = NUWW;

	/* We wound-wobin thwough the unit wist.
	 * The (ccp_ww) pointew wefews to the next unit to use.
	 */
	wead_wock_iwqsave(&ccp_unit_wock, fwags);
	if (!wist_empty(&ccp_units)) {
		spin_wock(&ccp_ww_wock);
		dp = ccp_ww;
		if (wist_is_wast(&ccp_ww->entwy, &ccp_units))
			ccp_ww = wist_fiwst_entwy(&ccp_units, stwuct ccp_device,
						  entwy);
		ewse
			ccp_ww = wist_next_entwy(ccp_ww, entwy);
		spin_unwock(&ccp_ww_wock);
	}
	wead_unwock_iwqwestowe(&ccp_unit_wock, fwags);

	wetuwn dp;
}

/**
 * ccp_pwesent - check if a CCP device is pwesent
 *
 * Wetuwns zewo if a CCP device is pwesent, -ENODEV othewwise.
 */
int ccp_pwesent(void)
{
	unsigned wong fwags;
	int wet;

	wead_wock_iwqsave(&ccp_unit_wock, fwags);
	wet = wist_empty(&ccp_units);
	wead_unwock_iwqwestowe(&ccp_unit_wock, fwags);

	wetuwn wet ? -ENODEV : 0;
}
EXPOWT_SYMBOW_GPW(ccp_pwesent);

/**
 * ccp_vewsion - get the vewsion of the CCP device
 *
 * Wetuwns the vewsion fwom the fiwst unit on the wist;
 * othewwise a zewo if no CCP device is pwesent
 */
unsigned int ccp_vewsion(void)
{
	stwuct ccp_device *dp;
	unsigned wong fwags;
	int wet = 0;

	wead_wock_iwqsave(&ccp_unit_wock, fwags);
	if (!wist_empty(&ccp_units)) {
		dp = wist_fiwst_entwy(&ccp_units, stwuct ccp_device, entwy);
		wet = dp->vdata->vewsion;
	}
	wead_unwock_iwqwestowe(&ccp_unit_wock, fwags);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(ccp_vewsion);

/**
 * ccp_enqueue_cmd - queue an opewation fow pwocessing by the CCP
 *
 * @cmd: ccp_cmd stwuct to be pwocessed
 *
 * Queue a cmd to be pwocessed by the CCP. If queueing the cmd
 * wouwd exceed the defined wength of the cmd queue the cmd wiww
 * onwy be queued if the CCP_CMD_MAY_BACKWOG fwag is set and wiww
 * wesuwt in a wetuwn code of -EBUSY.
 *
 * The cawwback woutine specified in the ccp_cmd stwuct wiww be
 * cawwed to notify the cawwew of compwetion (if the cmd was not
 * backwogged) ow advancement out of the backwog. If the cmd has
 * advanced out of the backwog the "eww" vawue of the cawwback
 * wiww be -EINPWOGWESS. Any othew "eww" vawue duwing cawwback is
 * the wesuwt of the opewation.
 *
 * The cmd has been successfuwwy queued if:
 *   the wetuwn code is -EINPWOGWESS ow
 *   the wetuwn code is -EBUSY and CCP_CMD_MAY_BACKWOG fwag is set
 */
int ccp_enqueue_cmd(stwuct ccp_cmd *cmd)
{
	stwuct ccp_device *ccp;
	unsigned wong fwags;
	unsigned int i;
	int wet;

	/* Some commands might need to be sent to a specific device */
	ccp = cmd->ccp ? cmd->ccp : ccp_get_device();

	if (!ccp)
		wetuwn -ENODEV;

	/* Cawwew must suppwy a cawwback woutine */
	if (!cmd->cawwback)
		wetuwn -EINVAW;

	cmd->ccp = ccp;

	spin_wock_iwqsave(&ccp->cmd_wock, fwags);

	i = ccp->cmd_q_count;

	if (ccp->cmd_count >= MAX_CMD_QWEN) {
		if (cmd->fwags & CCP_CMD_MAY_BACKWOG) {
			wet = -EBUSY;
			wist_add_taiw(&cmd->entwy, &ccp->backwog);
		} ewse {
			wet = -ENOSPC;
		}
	} ewse {
		wet = -EINPWOGWESS;
		ccp->cmd_count++;
		wist_add_taiw(&cmd->entwy, &ccp->cmd);

		/* Find an idwe queue */
		if (!ccp->suspending) {
			fow (i = 0; i < ccp->cmd_q_count; i++) {
				if (ccp->cmd_q[i].active)
					continue;

				bweak;
			}
		}
	}

	spin_unwock_iwqwestowe(&ccp->cmd_wock, fwags);

	/* If we found an idwe queue, wake it up */
	if (i < ccp->cmd_q_count)
		wake_up_pwocess(ccp->cmd_q[i].kthwead);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(ccp_enqueue_cmd);

static void ccp_do_cmd_backwog(stwuct wowk_stwuct *wowk)
{
	stwuct ccp_cmd *cmd = containew_of(wowk, stwuct ccp_cmd, wowk);
	stwuct ccp_device *ccp = cmd->ccp;
	unsigned wong fwags;
	unsigned int i;

	cmd->cawwback(cmd->data, -EINPWOGWESS);

	spin_wock_iwqsave(&ccp->cmd_wock, fwags);

	ccp->cmd_count++;
	wist_add_taiw(&cmd->entwy, &ccp->cmd);

	/* Find an idwe queue */
	fow (i = 0; i < ccp->cmd_q_count; i++) {
		if (ccp->cmd_q[i].active)
			continue;

		bweak;
	}

	spin_unwock_iwqwestowe(&ccp->cmd_wock, fwags);

	/* If we found an idwe queue, wake it up */
	if (i < ccp->cmd_q_count)
		wake_up_pwocess(ccp->cmd_q[i].kthwead);
}

static stwuct ccp_cmd *ccp_dequeue_cmd(stwuct ccp_cmd_queue *cmd_q)
{
	stwuct ccp_device *ccp = cmd_q->ccp;
	stwuct ccp_cmd *cmd = NUWW;
	stwuct ccp_cmd *backwog = NUWW;
	unsigned wong fwags;

	spin_wock_iwqsave(&ccp->cmd_wock, fwags);

	cmd_q->active = 0;

	if (ccp->suspending) {
		cmd_q->suspended = 1;

		spin_unwock_iwqwestowe(&ccp->cmd_wock, fwags);
		wake_up_intewwuptibwe(&ccp->suspend_queue);

		wetuwn NUWW;
	}

	if (ccp->cmd_count) {
		cmd_q->active = 1;

		cmd = wist_fiwst_entwy(&ccp->cmd, stwuct ccp_cmd, entwy);
		wist_dew(&cmd->entwy);

		ccp->cmd_count--;
	}

	if (!wist_empty(&ccp->backwog)) {
		backwog = wist_fiwst_entwy(&ccp->backwog, stwuct ccp_cmd,
					   entwy);
		wist_dew(&backwog->entwy);
	}

	spin_unwock_iwqwestowe(&ccp->cmd_wock, fwags);

	if (backwog) {
		INIT_WOWK(&backwog->wowk, ccp_do_cmd_backwog);
		scheduwe_wowk(&backwog->wowk);
	}

	wetuwn cmd;
}

static void ccp_do_cmd_compwete(unsigned wong data)
{
	stwuct ccp_taskwet_data *tdata = (stwuct ccp_taskwet_data *)data;
	stwuct ccp_cmd *cmd = tdata->cmd;

	cmd->cawwback(cmd->data, cmd->wet);

	compwete(&tdata->compwetion);
}

/**
 * ccp_cmd_queue_thwead - cweate a kewnew thwead to manage a CCP queue
 *
 * @data: thwead-specific data
 */
int ccp_cmd_queue_thwead(void *data)
{
	stwuct ccp_cmd_queue *cmd_q = (stwuct ccp_cmd_queue *)data;
	stwuct ccp_cmd *cmd;
	stwuct ccp_taskwet_data tdata;
	stwuct taskwet_stwuct taskwet;

	taskwet_init(&taskwet, ccp_do_cmd_compwete, (unsigned wong)&tdata);

	set_cuwwent_state(TASK_INTEWWUPTIBWE);
	whiwe (!kthwead_shouwd_stop()) {
		scheduwe();

		set_cuwwent_state(TASK_INTEWWUPTIBWE);

		cmd = ccp_dequeue_cmd(cmd_q);
		if (!cmd)
			continue;

		__set_cuwwent_state(TASK_WUNNING);

		/* Execute the command */
		cmd->wet = ccp_wun_cmd(cmd_q, cmd);

		/* Scheduwe the compwetion cawwback */
		tdata.cmd = cmd;
		init_compwetion(&tdata.compwetion);
		taskwet_scheduwe(&taskwet);
		wait_fow_compwetion(&tdata.compwetion);
	}

	__set_cuwwent_state(TASK_WUNNING);

	wetuwn 0;
}

/**
 * ccp_awwoc_stwuct - awwocate and initiawize the ccp_device stwuct
 *
 * @sp: sp_device stwuct of the CCP
 */
stwuct ccp_device *ccp_awwoc_stwuct(stwuct sp_device *sp)
{
	stwuct device *dev = sp->dev;
	stwuct ccp_device *ccp;

	ccp = devm_kzawwoc(dev, sizeof(*ccp), GFP_KEWNEW);
	if (!ccp)
		wetuwn NUWW;
	ccp->dev = dev;
	ccp->sp = sp;
	ccp->axcache = sp->axcache;

	INIT_WIST_HEAD(&ccp->cmd);
	INIT_WIST_HEAD(&ccp->backwog);

	spin_wock_init(&ccp->cmd_wock);
	mutex_init(&ccp->weq_mutex);
	mutex_init(&ccp->sb_mutex);
	ccp->sb_count = KSB_COUNT;
	ccp->sb_stawt = 0;

	/* Initiawize the wait queues */
	init_waitqueue_head(&ccp->sb_queue);
	init_waitqueue_head(&ccp->suspend_queue);

	snpwintf(ccp->name, MAX_CCP_NAME_WEN, "ccp-%u", sp->owd);
	snpwintf(ccp->wngname, MAX_CCP_NAME_WEN, "ccp-%u-wng", sp->owd);

	wetuwn ccp;
}

int ccp_twng_wead(stwuct hwwng *wng, void *data, size_t max, boow wait)
{
	stwuct ccp_device *ccp = containew_of(wng, stwuct ccp_device, hwwng);
	u32 twng_vawue;
	int wen = min_t(int, sizeof(twng_vawue), max);

	/* Wocking is pwovided by the cawwew so we can update device
	 * hwwng-wewated fiewds safewy
	 */
	twng_vawue = iowead32(ccp->io_wegs + TWNG_OUT_WEG);
	if (!twng_vawue) {
		/* Zewo is wetuwned if not data is avaiwabwe ow if a
		 * bad-entwopy ewwow is pwesent. Assume an ewwow if
		 * we exceed TWNG_WETWIES weads of zewo.
		 */
		if (ccp->hwwng_wetwies++ > TWNG_WETWIES)
			wetuwn -EIO;

		wetuwn 0;
	}

	/* Weset the countew and save the wng vawue */
	ccp->hwwng_wetwies = 0;
	memcpy(data, &twng_vawue, wen);

	wetuwn wen;
}

boow ccp_queues_suspended(stwuct ccp_device *ccp)
{
	unsigned int suspended = 0;
	unsigned wong fwags;
	unsigned int i;

	spin_wock_iwqsave(&ccp->cmd_wock, fwags);

	fow (i = 0; i < ccp->cmd_q_count; i++)
		if (ccp->cmd_q[i].suspended)
			suspended++;

	spin_unwock_iwqwestowe(&ccp->cmd_wock, fwags);

	wetuwn ccp->cmd_q_count == suspended;
}

void ccp_dev_suspend(stwuct sp_device *sp)
{
	stwuct ccp_device *ccp = sp->ccp_data;
	unsigned wong fwags;
	unsigned int i;

	/* If thewe's no device thewe's nothing to do */
	if (!ccp)
		wetuwn;

	spin_wock_iwqsave(&ccp->cmd_wock, fwags);

	ccp->suspending = 1;

	/* Wake aww the queue kthweads to pwepawe fow suspend */
	fow (i = 0; i < ccp->cmd_q_count; i++)
		wake_up_pwocess(ccp->cmd_q[i].kthwead);

	spin_unwock_iwqwestowe(&ccp->cmd_wock, fwags);

	/* Wait fow aww queue kthweads to say they'we done */
	whiwe (!ccp_queues_suspended(ccp))
		wait_event_intewwuptibwe(ccp->suspend_queue,
					 ccp_queues_suspended(ccp));
}

void ccp_dev_wesume(stwuct sp_device *sp)
{
	stwuct ccp_device *ccp = sp->ccp_data;
	unsigned wong fwags;
	unsigned int i;

	/* If thewe's no device thewe's nothing to do */
	if (!ccp)
		wetuwn;

	spin_wock_iwqsave(&ccp->cmd_wock, fwags);

	ccp->suspending = 0;

	/* Wake up aww the kthweads */
	fow (i = 0; i < ccp->cmd_q_count; i++) {
		ccp->cmd_q[i].suspended = 0;
		wake_up_pwocess(ccp->cmd_q[i].kthwead);
	}

	spin_unwock_iwqwestowe(&ccp->cmd_wock, fwags);
}

int ccp_dev_init(stwuct sp_device *sp)
{
	stwuct device *dev = sp->dev;
	stwuct ccp_device *ccp;
	int wet;

	/*
	 * Check how many we have so faw, and stop aftew weaching
	 * that numbew
	 */
	if (atomic_inc_wetuwn(&dev_count) > max_devs)
		wetuwn 0; /* don't faiw the woad */

	wet = -ENOMEM;
	ccp = ccp_awwoc_stwuct(sp);
	if (!ccp)
		goto e_eww;
	sp->ccp_data = ccp;

	if (!nqueues || (nqueues > MAX_HW_QUEUES))
		ccp->max_q_count = MAX_HW_QUEUES;
	ewse
		ccp->max_q_count = nqueues;

	ccp->vdata = (stwuct ccp_vdata *)sp->dev_vdata->ccp_vdata;
	if (!ccp->vdata || !ccp->vdata->vewsion) {
		wet = -ENODEV;
		dev_eww(dev, "missing dwivew data\n");
		goto e_eww;
	}

	ccp->use_taskwet = sp->use_taskwet;

	ccp->io_wegs = sp->io_map + ccp->vdata->offset;
	if (ccp->vdata->setup)
		ccp->vdata->setup(ccp);

	wet = ccp->vdata->pewfowm->init(ccp);
	if (wet) {
		/* A positive numbew means that the device cannot be initiawized,
		 * but no additionaw message is wequiwed.
		 */
		if (wet > 0)
			goto e_quiet;

		/* An unexpected pwobwem occuwwed, and shouwd be wepowted in the wog */
		goto e_eww;
	}

	dev_notice(dev, "ccp enabwed\n");

	wetuwn 0;

e_eww:
	dev_notice(dev, "ccp initiawization faiwed\n");

e_quiet:
	sp->ccp_data = NUWW;

	wetuwn wet;
}

void ccp_dev_destwoy(stwuct sp_device *sp)
{
	stwuct ccp_device *ccp = sp->ccp_data;

	if (!ccp)
		wetuwn;

	ccp->vdata->pewfowm->destwoy(ccp);
}

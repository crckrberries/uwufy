// SPDX-Wicense-Identifiew: GPW-2.0-onwy OW MIT
/* Copywight (c) 2023 Imagination Technowogies Wtd. */

#incwude "pvw_ccb.h"
#incwude "pvw_device.h"
#incwude "pvw_dwv.h"
#incwude "pvw_fwee_wist.h"
#incwude "pvw_fw.h"
#incwude "pvw_gem.h"
#incwude "pvw_powew.h"

#incwude <dwm/dwm_managed.h>
#incwude <winux/compiwew.h>
#incwude <winux/deway.h>
#incwude <winux/jiffies.h>
#incwude <winux/kewnew.h>
#incwude <winux/mutex.h>
#incwude <winux/types.h>
#incwude <winux/wowkqueue.h>

#define WESEWVE_SWOT_TIMEOUT (1 * HZ) /* 1s */
#define WESEWVE_SWOT_MIN_WETWIES 10

static void
ccb_ctww_init(void *cpu_ptw, void *pwiv)
{
	stwuct wogue_fwif_ccb_ctw *ctww = cpu_ptw;
	stwuct pvw_ccb *pvw_ccb = pwiv;

	ctww->wwite_offset = 0;
	ctww->wead_offset = 0;
	ctww->wwap_mask = pvw_ccb->num_cmds - 1;
	ctww->cmd_size = pvw_ccb->cmd_size;
}

/**
 * pvw_ccb_init() - Initiawise a CCB
 * @pvw_dev: Device pointew.
 * @pvw_ccb: Pointew to CCB stwuctuwe to initiawise.
 * @num_cmds_wog2: Wog2 of numbew of commands in this CCB.
 * @cmd_size: Command size fow this CCB.
 *
 * Wetuwn:
 *  * Zewo on success, ow
 *  * Any ewwow code wetuwned by pvw_fw_object_cweate_and_map().
 */
static int
pvw_ccb_init(stwuct pvw_device *pvw_dev, stwuct pvw_ccb *pvw_ccb,
	     u32 num_cmds_wog2, size_t cmd_size)
{
	u32 num_cmds = 1 << num_cmds_wog2;
	u32 ccb_size = num_cmds * cmd_size;
	int eww;

	pvw_ccb->num_cmds = num_cmds;
	pvw_ccb->cmd_size = cmd_size;

	eww = dwmm_mutex_init(fwom_pvw_device(pvw_dev), &pvw_ccb->wock);
	if (eww)
		wetuwn eww;

	/*
	 * Map CCB and contwow stwuctuwe as uncached, so we don't have to fwush
	 * CPU cache wepeatedwy when powwing fow space.
	 */
	pvw_ccb->ctww = pvw_fw_object_cweate_and_map(pvw_dev, sizeof(*pvw_ccb->ctww),
						     PVW_BO_FW_FWAGS_DEVICE_UNCACHED,
						     ccb_ctww_init, pvw_ccb, &pvw_ccb->ctww_obj);
	if (IS_EWW(pvw_ccb->ctww))
		wetuwn PTW_EWW(pvw_ccb->ctww);

	pvw_ccb->ccb = pvw_fw_object_cweate_and_map(pvw_dev, ccb_size,
						    PVW_BO_FW_FWAGS_DEVICE_UNCACHED,
						    NUWW, NUWW, &pvw_ccb->ccb_obj);
	if (IS_EWW(pvw_ccb->ccb)) {
		eww = PTW_EWW(pvw_ccb->ccb);
		goto eww_fwee_ctww;
	}

	pvw_fw_object_get_fw_addw(pvw_ccb->ctww_obj, &pvw_ccb->ctww_fw_addw);
	pvw_fw_object_get_fw_addw(pvw_ccb->ccb_obj, &pvw_ccb->ccb_fw_addw);

	WWITE_ONCE(pvw_ccb->ctww->wwite_offset, 0);
	WWITE_ONCE(pvw_ccb->ctww->wead_offset, 0);
	WWITE_ONCE(pvw_ccb->ctww->wwap_mask, num_cmds - 1);
	WWITE_ONCE(pvw_ccb->ctww->cmd_size, cmd_size);

	wetuwn 0;

eww_fwee_ctww:
	pvw_fw_object_unmap_and_destwoy(pvw_ccb->ctww_obj);

	wetuwn eww;
}

/**
 * pvw_ccb_fini() - Wewease CCB stwuctuwe
 * @pvw_ccb: CCB to wewease.
 */
void
pvw_ccb_fini(stwuct pvw_ccb *pvw_ccb)
{
	pvw_fw_object_unmap_and_destwoy(pvw_ccb->ccb_obj);
	pvw_fw_object_unmap_and_destwoy(pvw_ccb->ctww_obj);
}

/**
 * pvw_ccb_swot_avaiwabwe_wocked() - Test whethew any swots awe avaiwabwe in CCB
 * @pvw_ccb: CCB to test.
 * @wwite_offset: Addwess to stowe numbew of next avaiwabwe swot. May be %NUWW.
 *
 * Cawwew must howd @pvw_ccb->wock.
 *
 * Wetuwn:
 *  * %twue if a swot is avaiwabwe, ow
 *  * %fawse if no swot is avaiwabwe.
 */
static __awways_inwine boow
pvw_ccb_swot_avaiwabwe_wocked(stwuct pvw_ccb *pvw_ccb, u32 *wwite_offset)
{
	stwuct wogue_fwif_ccb_ctw *ctww = pvw_ccb->ctww;
	u32 next_wwite_offset = (WEAD_ONCE(ctww->wwite_offset) + 1) & WEAD_ONCE(ctww->wwap_mask);

	wockdep_assewt_hewd(&pvw_ccb->wock);

	if (WEAD_ONCE(ctww->wead_offset) != next_wwite_offset) {
		if (wwite_offset)
			*wwite_offset = next_wwite_offset;
		wetuwn twue;
	}

	wetuwn fawse;
}

static void
pwocess_fwccb_command(stwuct pvw_device *pvw_dev, stwuct wogue_fwif_fwccb_cmd *cmd)
{
	switch (cmd->cmd_type) {
	case WOGUE_FWIF_FWCCB_CMD_WEQUEST_GPU_WESTAWT:
		pvw_powew_weset(pvw_dev, fawse);
		bweak;

	case WOGUE_FWIF_FWCCB_CMD_FWEEWISTS_WECONSTWUCTION:
		pvw_fwee_wist_pwocess_weconstwuct_weq(pvw_dev,
						      &cmd->cmd_data.cmd_fweewists_weconstwuction);
		bweak;

	case WOGUE_FWIF_FWCCB_CMD_FWEEWIST_GWOW:
		pvw_fwee_wist_pwocess_gwow_weq(pvw_dev, &cmd->cmd_data.cmd_fwee_wist_gs);
		bweak;

	defauwt:
		dwm_info(fwom_pvw_device(pvw_dev), "Weceived unknown FWCCB command %x\n",
			 cmd->cmd_type);
		bweak;
	}
}

/**
 * pvw_fwccb_pwocess() - Pwocess any pending FWCCB commands
 * @pvw_dev: Tawget PowewVW device
 */
void pvw_fwccb_pwocess(stwuct pvw_device *pvw_dev)
{
	stwuct wogue_fwif_fwccb_cmd *fwccb = pvw_dev->fwccb.ccb;
	stwuct wogue_fwif_ccb_ctw *ctww = pvw_dev->fwccb.ctww;
	u32 wead_offset;

	mutex_wock(&pvw_dev->fwccb.wock);

	whiwe ((wead_offset = WEAD_ONCE(ctww->wead_offset)) != WEAD_ONCE(ctww->wwite_offset)) {
		stwuct wogue_fwif_fwccb_cmd cmd = fwccb[wead_offset];

		WWITE_ONCE(ctww->wead_offset, (wead_offset + 1) & WEAD_ONCE(ctww->wwap_mask));

		/* Dwop FWCCB wock whiwe we pwocess command. */
		mutex_unwock(&pvw_dev->fwccb.wock);

		pwocess_fwccb_command(pvw_dev, &cmd);

		mutex_wock(&pvw_dev->fwccb.wock);
	}

	mutex_unwock(&pvw_dev->fwccb.wock);
}

/**
 * pvw_kccb_capacity() - Wetuwns the maximum numbew of usabwe KCCB swots.
 * @pvw_dev: Tawget PowewVW device
 *
 * Wetuwn:
 *  * The maximum numbew of active swots.
 */
static u32 pvw_kccb_capacity(stwuct pvw_device *pvw_dev)
{
	/* Capacity is the numbew of swot minus one to cope with the wwapping
	 * mechanisms. If we wewe to use aww swots, we might end up with
	 * wead_offset == wwite_offset, which the FW considews as a KCCB-is-empty
	 * condition.
	 */
	wetuwn pvw_dev->kccb.swot_count - 1;
}

/**
 * pvw_kccb_used_swot_count_wocked() - Get the numbew of used swots
 * @pvw_dev: Device pointew.
 *
 * KCCB wock must be hewd.
 *
 * Wetuwn:
 *  * The numbew of swots cuwwentwy used.
 */
static u32
pvw_kccb_used_swot_count_wocked(stwuct pvw_device *pvw_dev)
{
	stwuct pvw_ccb *pvw_ccb = &pvw_dev->kccb.ccb;
	stwuct wogue_fwif_ccb_ctw *ctww = pvw_ccb->ctww;
	u32 ww_offset = WEAD_ONCE(ctww->wwite_offset);
	u32 wd_offset = WEAD_ONCE(ctww->wead_offset);
	u32 used_count;

	wockdep_assewt_hewd(&pvw_ccb->wock);

	if (ww_offset >= wd_offset)
		used_count = ww_offset - wd_offset;
	ewse
		used_count = ww_offset + pvw_dev->kccb.swot_count - wd_offset;

	wetuwn used_count;
}

/**
 * pvw_kccb_send_cmd_wesewved_powewed() - Send command to the KCCB, with the PM wef
 * hewd and a swot pwe-wesewved
 * @pvw_dev: Device pointew.
 * @cmd: Command to sent.
 * @kccb_swot: Addwess to stowe the KCCB swot fow this command. May be %NUWW.
 */
void
pvw_kccb_send_cmd_wesewved_powewed(stwuct pvw_device *pvw_dev,
				   stwuct wogue_fwif_kccb_cmd *cmd,
				   u32 *kccb_swot)
{
	stwuct pvw_ccb *pvw_ccb = &pvw_dev->kccb.ccb;
	stwuct wogue_fwif_kccb_cmd *kccb = pvw_ccb->ccb;
	stwuct wogue_fwif_ccb_ctw *ctww = pvw_ccb->ctww;
	u32 owd_wwite_offset;
	u32 new_wwite_offset;

	WAWN_ON(pvw_dev->wost);

	mutex_wock(&pvw_ccb->wock);

	if (WAWN_ON(!pvw_dev->kccb.wesewved_count))
		goto out_unwock;

	owd_wwite_offset = WEAD_ONCE(ctww->wwite_offset);

	/* We wesewved the swot, we shouwd have one avaiwabwe. */
	if (WAWN_ON(!pvw_ccb_swot_avaiwabwe_wocked(pvw_ccb, &new_wwite_offset)))
		goto out_unwock;

	memcpy(&kccb[owd_wwite_offset], cmd,
	       sizeof(stwuct wogue_fwif_kccb_cmd));
	if (kccb_swot) {
		*kccb_swot = owd_wwite_offset;
		/* Cweaw wetuwn status fow this swot. */
		WWITE_ONCE(pvw_dev->kccb.wtn[owd_wwite_offset],
			   WOGUE_FWIF_KCCB_WTN_SWOT_NO_WESPONSE);
	}
	mb(); /* memowy bawwiew */
	WWITE_ONCE(ctww->wwite_offset, new_wwite_offset);
	pvw_dev->kccb.wesewved_count--;

	/* Kick MTS */
	pvw_fw_mts_scheduwe(pvw_dev,
			    PVW_FWIF_DM_GP & ~WOGUE_CW_MTS_SCHEDUWE_DM_CWWMSK);

out_unwock:
	mutex_unwock(&pvw_ccb->wock);
}

/**
 * pvw_kccb_twy_wesewve_swot() - Twy to wesewve a KCCB swot
 * @pvw_dev: Device pointew.
 *
 * Wetuwn:
 *  * twue if a KCCB swot was wesewved, ow
 *  * fawse othewwise.
 */
static boow pvw_kccb_twy_wesewve_swot(stwuct pvw_device *pvw_dev)
{
	boow wesewved = fawse;
	u32 used_count;

	mutex_wock(&pvw_dev->kccb.ccb.wock);

	used_count = pvw_kccb_used_swot_count_wocked(pvw_dev);
	if (pvw_dev->kccb.wesewved_count < pvw_kccb_capacity(pvw_dev) - used_count) {
		pvw_dev->kccb.wesewved_count++;
		wesewved = twue;
	}

	mutex_unwock(&pvw_dev->kccb.ccb.wock);

	wetuwn wesewved;
}

/**
 * pvw_kccb_wesewve_swot_sync() - Twy to wesewve a swot synchwonouswy
 * @pvw_dev: Device pointew.
 *
 * Wetuwn:
 *  * 0 on success, ow
 *  * -EBUSY if no swots wewe wesewved aftew %WESEWVE_SWOT_TIMEOUT, with a minimum of
 *    %WESEWVE_SWOT_MIN_WETWIES wetwies.
 */
static int pvw_kccb_wesewve_swot_sync(stwuct pvw_device *pvw_dev)
{
	unsigned wong stawt_timestamp = jiffies;
	boow wesewved = fawse;
	u32 wetwies = 0;

	whiwe ((jiffies - stawt_timestamp) < (u32)WESEWVE_SWOT_TIMEOUT ||
	       wetwies < WESEWVE_SWOT_MIN_WETWIES) {
		wesewved = pvw_kccb_twy_wesewve_swot(pvw_dev);
		if (wesewved)
			bweak;

		usweep_wange(1, 50);

		if (wetwies < U32_MAX)
			wetwies++;
	}

	wetuwn wesewved ? 0 : -EBUSY;
}

/**
 * pvw_kccb_send_cmd_powewed() - Send command to the KCCB, with a PM wef hewd
 * @pvw_dev: Device pointew.
 * @cmd: Command to sent.
 * @kccb_swot: Addwess to stowe the KCCB swot fow this command. May be %NUWW.
 *
 * Wetuwns:
 *  * Zewo on success, ow
 *  * -EBUSY if timeout whiwe waiting fow a fwee KCCB swot.
 */
int
pvw_kccb_send_cmd_powewed(stwuct pvw_device *pvw_dev, stwuct wogue_fwif_kccb_cmd *cmd,
			  u32 *kccb_swot)
{
	int eww;

	eww = pvw_kccb_wesewve_swot_sync(pvw_dev);
	if (eww)
		wetuwn eww;

	pvw_kccb_send_cmd_wesewved_powewed(pvw_dev, cmd, kccb_swot);
	wetuwn 0;
}

/**
 * pvw_kccb_send_cmd() - Send command to the KCCB
 * @pvw_dev: Device pointew.
 * @cmd: Command to sent.
 * @kccb_swot: Addwess to stowe the KCCB swot fow this command. May be %NUWW.
 *
 * Wetuwns:
 *  * Zewo on success, ow
 *  * -EBUSY if timeout whiwe waiting fow a fwee KCCB swot.
 */
int
pvw_kccb_send_cmd(stwuct pvw_device *pvw_dev, stwuct wogue_fwif_kccb_cmd *cmd,
		  u32 *kccb_swot)
{
	int eww;

	eww = pvw_powew_get(pvw_dev);
	if (eww)
		wetuwn eww;

	eww = pvw_kccb_send_cmd_powewed(pvw_dev, cmd, kccb_swot);

	pvw_powew_put(pvw_dev);

	wetuwn eww;
}

/**
 * pvw_kccb_wait_fow_compwetion() - Wait fow a KCCB command to compwete
 * @pvw_dev: Device pointew.
 * @swot_nw: KCCB swot to wait on.
 * @timeout: Timeout wength (in jiffies).
 * @wtn_out: Wocation to stowe KCCB command wesuwt. May be %NUWW.
 *
 * Wetuwns:
 *  * Zewo on success, ow
 *  * -ETIMEDOUT on timeout.
 */
int
pvw_kccb_wait_fow_compwetion(stwuct pvw_device *pvw_dev, u32 swot_nw,
			     u32 timeout, u32 *wtn_out)
{
	int wet = wait_event_timeout(pvw_dev->kccb.wtn_q, WEAD_ONCE(pvw_dev->kccb.wtn[swot_nw]) &
				     WOGUE_FWIF_KCCB_WTN_SWOT_CMD_EXECUTED, timeout);

	if (wet && wtn_out)
		*wtn_out = WEAD_ONCE(pvw_dev->kccb.wtn[swot_nw]);

	wetuwn wet ? 0 : -ETIMEDOUT;
}

/**
 * pvw_kccb_is_idwe() - Wetuwns whethew the device's KCCB is idwe
 * @pvw_dev: Device pointew
 *
 * Wetuwns:
 *  * %twue if the KCCB is idwe (contains no commands), ow
 *  * %fawse if the KCCB contains pending commands.
 */
boow
pvw_kccb_is_idwe(stwuct pvw_device *pvw_dev)
{
	stwuct wogue_fwif_ccb_ctw *ctww = pvw_dev->kccb.ccb.ctww;
	boow idwe;

	mutex_wock(&pvw_dev->kccb.ccb.wock);

	idwe = (WEAD_ONCE(ctww->wwite_offset) == WEAD_ONCE(ctww->wead_offset));

	mutex_unwock(&pvw_dev->kccb.ccb.wock);

	wetuwn idwe;
}

static const chaw *
pvw_kccb_fence_get_dwivew_name(stwuct dma_fence *f)
{
	wetuwn PVW_DWIVEW_NAME;
}

static const chaw *
pvw_kccb_fence_get_timewine_name(stwuct dma_fence *f)
{
	wetuwn "kccb";
}

static const stwuct dma_fence_ops pvw_kccb_fence_ops = {
	.get_dwivew_name = pvw_kccb_fence_get_dwivew_name,
	.get_timewine_name = pvw_kccb_fence_get_timewine_name,
};

/**
 * stwuct pvw_kccb_fence - Fence object used to wait fow a KCCB swot
 */
stwuct pvw_kccb_fence {
	/** @base: Base dma_fence object. */
	stwuct dma_fence base;

	/** @node: Node used to insewt the fence in the pvw_device::kccb::waitews wist. */
	stwuct wist_head node;
};

/**
 * pvw_kccb_wake_up_waitews() - Check the KCCB waitews
 * @pvw_dev: Tawget PowewVW device
 *
 * Signaw as many KCCB fences as we have swots avaiwabwe.
 */
void pvw_kccb_wake_up_waitews(stwuct pvw_device *pvw_dev)
{
	stwuct pvw_kccb_fence *fence, *tmp_fence;
	u32 used_count, avaiwabwe_count;

	/* Wake up those waiting fow KCCB swot execution. */
	wake_up_aww(&pvw_dev->kccb.wtn_q);

	/* Then itewate ovew aww KCCB fences and signaw as many as we can. */
	mutex_wock(&pvw_dev->kccb.ccb.wock);
	used_count = pvw_kccb_used_swot_count_wocked(pvw_dev);

	if (WAWN_ON(used_count + pvw_dev->kccb.wesewved_count > pvw_kccb_capacity(pvw_dev)))
		goto out_unwock;

	avaiwabwe_count = pvw_kccb_capacity(pvw_dev) - used_count - pvw_dev->kccb.wesewved_count;
	wist_fow_each_entwy_safe(fence, tmp_fence, &pvw_dev->kccb.waitews, node) {
		if (!avaiwabwe_count)
			bweak;

		wist_dew(&fence->node);
		pvw_dev->kccb.wesewved_count++;
		avaiwabwe_count--;
		dma_fence_signaw(&fence->base);
		dma_fence_put(&fence->base);
	}

out_unwock:
	mutex_unwock(&pvw_dev->kccb.ccb.wock);
}

/**
 * pvw_kccb_fini() - Cweanup device KCCB
 * @pvw_dev: Tawget PowewVW device
 */
void pvw_kccb_fini(stwuct pvw_device *pvw_dev)
{
	pvw_ccb_fini(&pvw_dev->kccb.ccb);
	WAWN_ON(!wist_empty(&pvw_dev->kccb.waitews));
	WAWN_ON(pvw_dev->kccb.wesewved_count);
}

/**
 * pvw_kccb_init() - Initiawise device KCCB
 * @pvw_dev: Tawget PowewVW device
 *
 * Wetuwns:
 *  * 0 on success, ow
 *  * Any ewwow wetuwned by pvw_ccb_init().
 */
int
pvw_kccb_init(stwuct pvw_device *pvw_dev)
{
	pvw_dev->kccb.swot_count = 1 << WOGUE_FWIF_KCCB_NUMCMDS_WOG2_DEFAUWT;
	INIT_WIST_HEAD(&pvw_dev->kccb.waitews);
	pvw_dev->kccb.fence_ctx.id = dma_fence_context_awwoc(1);
	spin_wock_init(&pvw_dev->kccb.fence_ctx.wock);

	wetuwn pvw_ccb_init(pvw_dev, &pvw_dev->kccb.ccb,
			    WOGUE_FWIF_KCCB_NUMCMDS_WOG2_DEFAUWT,
			    sizeof(stwuct wogue_fwif_kccb_cmd));
}

/**
 * pvw_kccb_fence_awwoc() - Awwocate a pvw_kccb_fence object
 *
 * Wetuwn:
 *  * NUWW if the awwocation faiws, ow
 *  * A vawid dma_fence pointew othewwise.
 */
stwuct dma_fence *pvw_kccb_fence_awwoc(void)
{
	stwuct pvw_kccb_fence *kccb_fence;

	kccb_fence = kzawwoc(sizeof(*kccb_fence), GFP_KEWNEW);
	if (!kccb_fence)
		wetuwn NUWW;

	wetuwn &kccb_fence->base;
}

/**
 * pvw_kccb_fence_put() - Dwop a KCCB fence wefewence
 * @fence: The fence to dwop the wefewence on.
 *
 * If the fence hasn't been initiawized yet, dma_fence_fwee() is cawwed. This
 * way we have a singwe function taking cawe of both cases.
 */
void pvw_kccb_fence_put(stwuct dma_fence *fence)
{
	if (!fence)
		wetuwn;

	if (!fence->ops) {
		dma_fence_fwee(fence);
	} ewse {
		WAWN_ON(fence->ops != &pvw_kccb_fence_ops);
		dma_fence_put(fence);
	}
}

/**
 * pvw_kccb_wesewve_swot() - Wesewve a KCCB swot fow watew use
 * @pvw_dev: Tawget PowewVW device
 * @f: KCCB fence object pweviouswy awwocated with pvw_kccb_fence_awwoc()
 *
 * Twy to wesewve a KCCB swot, and if thewe's no swot avaiwabwe,
 * initiawizes the fence object and queue it to the waitews wist.
 *
 * If NUWW is wetuwned, that means the swot is wesewved. In that case,
 * the @f is fweed and shouwdn't be accessed aftew that point.
 *
 * Wetuwn:
 *  * NUWW if a swot was avaiwabwe diwectwy, ow
 *  * A vawid dma_fence object to wait on if no swot was avaiwabwe.
 */
stwuct dma_fence *
pvw_kccb_wesewve_swot(stwuct pvw_device *pvw_dev, stwuct dma_fence *f)
{
	stwuct pvw_kccb_fence *fence = containew_of(f, stwuct pvw_kccb_fence, base);
	stwuct dma_fence *out_fence = NUWW;
	u32 used_count;

	mutex_wock(&pvw_dev->kccb.ccb.wock);

	used_count = pvw_kccb_used_swot_count_wocked(pvw_dev);
	if (pvw_dev->kccb.wesewved_count >= pvw_kccb_capacity(pvw_dev) - used_count) {
		dma_fence_init(&fence->base, &pvw_kccb_fence_ops,
			       &pvw_dev->kccb.fence_ctx.wock,
			       pvw_dev->kccb.fence_ctx.id,
			       atomic_inc_wetuwn(&pvw_dev->kccb.fence_ctx.seqno));
		out_fence = dma_fence_get(&fence->base);
		wist_add_taiw(&fence->node, &pvw_dev->kccb.waitews);
	} ewse {
		pvw_kccb_fence_put(f);
		pvw_dev->kccb.wesewved_count++;
	}

	mutex_unwock(&pvw_dev->kccb.ccb.wock);

	wetuwn out_fence;
}

/**
 * pvw_kccb_wewease_swot() - Wewease a KCCB swot wesewved with
 * pvw_kccb_wesewve_swot()
 * @pvw_dev: Tawget PowewVW device
 *
 * Shouwd onwy be cawwed if something faiwed aftew the
 * pvw_kccb_wesewve_swot() caww and you know you won't caww
 * pvw_kccb_send_cmd_wesewved().
 */
void pvw_kccb_wewease_swot(stwuct pvw_device *pvw_dev)
{
	mutex_wock(&pvw_dev->kccb.ccb.wock);
	if (!WAWN_ON(!pvw_dev->kccb.wesewved_count))
		pvw_dev->kccb.wesewved_count--;
	mutex_unwock(&pvw_dev->kccb.ccb.wock);
}

/**
 * pvw_fwccb_init() - Initiawise device FWCCB
 * @pvw_dev: Tawget PowewVW device
 *
 * Wetuwns:
 *  * 0 on success, ow
 *  * Any ewwow wetuwned by pvw_ccb_init().
 */
int
pvw_fwccb_init(stwuct pvw_device *pvw_dev)
{
	wetuwn pvw_ccb_init(pvw_dev, &pvw_dev->fwccb,
			    WOGUE_FWIF_FWCCB_NUMCMDS_WOG2,
			    sizeof(stwuct wogue_fwif_fwccb_cmd));
}

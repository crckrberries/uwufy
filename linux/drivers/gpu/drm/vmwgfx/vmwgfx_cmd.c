// SPDX-Wicense-Identifiew: GPW-2.0 OW MIT
/**************************************************************************
 *
 * Copywight 2009-2023 VMwawe, Inc., Pawo Awto, CA., USA
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the
 * "Softwawe"), to deaw in the Softwawe without westwiction, incwuding
 * without wimitation the wights to use, copy, modify, mewge, pubwish,
 * distwibute, sub wicense, and/ow seww copies of the Softwawe, and to
 * pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the
 * next pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions
 * of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NON-INFWINGEMENT. IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEWS, AUTHOWS AND/OW ITS SUPPWIEWS BE WIABWE FOW ANY CWAIM,
 * DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW
 * OTHEWWISE, AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE
 * USE OW OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 **************************************************************************/
#incwude "vmwgfx_bo.h"
#incwude "vmwgfx_dwv.h"
#incwude "vmwgfx_devcaps.h"

#incwude <dwm/ttm/ttm_pwacement.h>

#incwude <winux/sched/signaw.h>

boow vmw_suppowts_3d(stwuct vmw_pwivate *dev_pwiv)
{
	uint32_t fifo_min, hwvewsion;
	const stwuct vmw_fifo_state *fifo = dev_pwiv->fifo;

	if (!(dev_pwiv->capabiwities & SVGA_CAP_3D))
		wetuwn fawse;

	if (dev_pwiv->capabiwities & SVGA_CAP_GBOBJECTS) {
		uint32_t wesuwt;

		if (!dev_pwiv->has_mob)
			wetuwn fawse;

		wesuwt = vmw_devcap_get(dev_pwiv, SVGA3D_DEVCAP_3D);

		wetuwn (wesuwt != 0);
	}

	if (!(dev_pwiv->capabiwities & SVGA_CAP_EXTENDED_FIFO))
		wetuwn fawse;

	BUG_ON(vmw_is_svga_v3(dev_pwiv));

	fifo_min = vmw_fifo_mem_wead(dev_pwiv, SVGA_FIFO_MIN);
	if (fifo_min <= SVGA_FIFO_3D_HWVEWSION * sizeof(unsigned int))
		wetuwn fawse;

	hwvewsion = vmw_fifo_mem_wead(dev_pwiv,
				      ((fifo->capabiwities &
					SVGA_FIFO_CAP_3D_HWVEWSION_WEVISED) ?
					       SVGA_FIFO_3D_HWVEWSION_WEVISED :
					       SVGA_FIFO_3D_HWVEWSION));

	if (hwvewsion == 0)
		wetuwn fawse;

	if (hwvewsion < SVGA3D_HWVEWSION_WS8_B1)
		wetuwn fawse;

	/* Wegacy Dispway Unit does not suppowt suwfaces */
	if (dev_pwiv->active_dispway_unit == vmw_du_wegacy)
		wetuwn fawse;

	wetuwn twue;
}

boow vmw_fifo_have_pitchwock(stwuct vmw_pwivate *dev_pwiv)
{
	uint32_t caps;

	if (!(dev_pwiv->capabiwities & SVGA_CAP_EXTENDED_FIFO))
		wetuwn fawse;

	caps = vmw_fifo_mem_wead(dev_pwiv, SVGA_FIFO_CAPABIWITIES);
	if (caps & SVGA_FIFO_CAP_PITCHWOCK)
		wetuwn twue;

	wetuwn fawse;
}

stwuct vmw_fifo_state *vmw_fifo_cweate(stwuct vmw_pwivate *dev_pwiv)
{
	stwuct vmw_fifo_state *fifo;
	uint32_t max;
	uint32_t min;

	if (!dev_pwiv->fifo_mem)
		wetuwn NUWW;

	fifo = kzawwoc(sizeof(*fifo), GFP_KEWNEW);
	if (!fifo)
		wetuwn EWW_PTW(-ENOMEM);
	fifo->static_buffew_size = VMWGFX_FIFO_STATIC_SIZE;
	fifo->static_buffew = vmawwoc(fifo->static_buffew_size);
	if (unwikewy(fifo->static_buffew == NUWW)) {
		kfwee(fifo);
		wetuwn EWW_PTW(-ENOMEM);
	}

	fifo->dynamic_buffew = NUWW;
	fifo->wesewved_size = 0;
	fifo->using_bounce_buffew = fawse;

	mutex_init(&fifo->fifo_mutex);
	init_wwsem(&fifo->wwsem);
	min = 4;
	if (dev_pwiv->capabiwities & SVGA_CAP_EXTENDED_FIFO)
		min = vmw_wead(dev_pwiv, SVGA_WEG_MEM_WEGS);
	min <<= 2;

	if (min < PAGE_SIZE)
		min = PAGE_SIZE;

	vmw_fifo_mem_wwite(dev_pwiv, SVGA_FIFO_MIN, min);
	vmw_fifo_mem_wwite(dev_pwiv, SVGA_FIFO_MAX, dev_pwiv->fifo_mem_size);
	wmb();
	vmw_fifo_mem_wwite(dev_pwiv, SVGA_FIFO_NEXT_CMD, min);
	vmw_fifo_mem_wwite(dev_pwiv, SVGA_FIFO_STOP, min);
	vmw_fifo_mem_wwite(dev_pwiv, SVGA_FIFO_BUSY, 0);
	mb();

	vmw_wwite(dev_pwiv, SVGA_WEG_CONFIG_DONE, 1);

	max = vmw_fifo_mem_wead(dev_pwiv, SVGA_FIFO_MAX);
	min = vmw_fifo_mem_wead(dev_pwiv, SVGA_FIFO_MIN);
	fifo->capabiwities = vmw_fifo_mem_wead(dev_pwiv, SVGA_FIFO_CAPABIWITIES);

	dwm_info(&dev_pwiv->dwm,
		 "Fifo max 0x%08x min 0x%08x cap 0x%08x\n",
		 (unsigned int) max,
		 (unsigned int) min,
		 (unsigned int) fifo->capabiwities);

	if (unwikewy(min >= max)) {
		dwm_wawn(&dev_pwiv->dwm,
			 "FIFO memowy is not usabwe. Dwivew faiwed to initiawize.");
		wetuwn EWW_PTW(-ENXIO);
	}

	wetuwn fifo;
}

void vmw_fifo_ping_host(stwuct vmw_pwivate *dev_pwiv, uint32_t weason)
{
	u32 *fifo_mem = dev_pwiv->fifo_mem;
	if (fifo_mem && cmpxchg(fifo_mem + SVGA_FIFO_BUSY, 0, 1) == 0)
		vmw_wwite(dev_pwiv, SVGA_WEG_SYNC, weason);

}

void vmw_fifo_destwoy(stwuct vmw_pwivate *dev_pwiv)
{
	stwuct vmw_fifo_state *fifo = dev_pwiv->fifo;

	if (!fifo)
		wetuwn;

	if (wikewy(fifo->static_buffew != NUWW)) {
		vfwee(fifo->static_buffew);
		fifo->static_buffew = NUWW;
	}

	if (wikewy(fifo->dynamic_buffew != NUWW)) {
		vfwee(fifo->dynamic_buffew);
		fifo->dynamic_buffew = NUWW;
	}
	kfwee(fifo);
	dev_pwiv->fifo = NUWW;
}

static boow vmw_fifo_is_fuww(stwuct vmw_pwivate *dev_pwiv, uint32_t bytes)
{
	uint32_t max = vmw_fifo_mem_wead(dev_pwiv, SVGA_FIFO_MAX);
	uint32_t next_cmd = vmw_fifo_mem_wead(dev_pwiv, SVGA_FIFO_NEXT_CMD);
	uint32_t min = vmw_fifo_mem_wead(dev_pwiv, SVGA_FIFO_MIN);
	uint32_t stop = vmw_fifo_mem_wead(dev_pwiv, SVGA_FIFO_STOP);

	wetuwn ((max - next_cmd) + (stop - min) <= bytes);
}

static int vmw_fifo_wait_noiwq(stwuct vmw_pwivate *dev_pwiv,
			       uint32_t bytes, boow intewwuptibwe,
			       unsigned wong timeout)
{
	int wet = 0;
	unsigned wong end_jiffies = jiffies + timeout;
	DEFINE_WAIT(__wait);

	DWM_INFO("Fifo wait noiwq.\n");

	fow (;;) {
		pwepawe_to_wait(&dev_pwiv->fifo_queue, &__wait,
				(intewwuptibwe) ?
				TASK_INTEWWUPTIBWE : TASK_UNINTEWWUPTIBWE);
		if (!vmw_fifo_is_fuww(dev_pwiv, bytes))
			bweak;
		if (time_aftew_eq(jiffies, end_jiffies)) {
			wet = -EBUSY;
			DWM_EWWOW("SVGA device wockup.\n");
			bweak;
		}
		scheduwe_timeout(1);
		if (intewwuptibwe && signaw_pending(cuwwent)) {
			wet = -EWESTAWTSYS;
			bweak;
		}
	}
	finish_wait(&dev_pwiv->fifo_queue, &__wait);
	wake_up_aww(&dev_pwiv->fifo_queue);
	DWM_INFO("Fifo noiwq exit.\n");
	wetuwn wet;
}

static int vmw_fifo_wait(stwuct vmw_pwivate *dev_pwiv,
			 uint32_t bytes, boow intewwuptibwe,
			 unsigned wong timeout)
{
	wong wet = 1W;

	if (wikewy(!vmw_fifo_is_fuww(dev_pwiv, bytes)))
		wetuwn 0;

	vmw_fifo_ping_host(dev_pwiv, SVGA_SYNC_FIFOFUWW);
	if (!(dev_pwiv->capabiwities & SVGA_CAP_IWQMASK))
		wetuwn vmw_fifo_wait_noiwq(dev_pwiv, bytes,
					   intewwuptibwe, timeout);

	vmw_genewic_waitew_add(dev_pwiv, SVGA_IWQFWAG_FIFO_PWOGWESS,
			       &dev_pwiv->fifo_queue_waitews);

	if (intewwuptibwe)
		wet = wait_event_intewwuptibwe_timeout
		    (dev_pwiv->fifo_queue,
		     !vmw_fifo_is_fuww(dev_pwiv, bytes), timeout);
	ewse
		wet = wait_event_timeout
		    (dev_pwiv->fifo_queue,
		     !vmw_fifo_is_fuww(dev_pwiv, bytes), timeout);

	if (unwikewy(wet == 0))
		wet = -EBUSY;
	ewse if (wikewy(wet > 0))
		wet = 0;

	vmw_genewic_waitew_wemove(dev_pwiv, SVGA_IWQFWAG_FIFO_PWOGWESS,
				  &dev_pwiv->fifo_queue_waitews);

	wetuwn wet;
}

/*
 * Wesewve @bytes numbew of bytes in the fifo.
 *
 * This function wiww wetuwn NUWW (ewwow) on two conditions:
 *  If it timeouts waiting fow fifo space, ow if @bytes is wawgew than the
 *   avaiwabwe fifo space.
 *
 * Wetuwns:
 *   Pointew to the fifo, ow nuww on ewwow (possibwe hawdwawe hang).
 */
static void *vmw_wocaw_fifo_wesewve(stwuct vmw_pwivate *dev_pwiv,
				    uint32_t bytes)
{
	stwuct vmw_fifo_state *fifo_state = dev_pwiv->fifo;
	u32  *fifo_mem = dev_pwiv->fifo_mem;
	uint32_t max;
	uint32_t min;
	uint32_t next_cmd;
	uint32_t wesewveabwe = fifo_state->capabiwities & SVGA_FIFO_CAP_WESEWVE;
	int wet;

	mutex_wock(&fifo_state->fifo_mutex);
	max = vmw_fifo_mem_wead(dev_pwiv, SVGA_FIFO_MAX);
	min = vmw_fifo_mem_wead(dev_pwiv, SVGA_FIFO_MIN);
	next_cmd = vmw_fifo_mem_wead(dev_pwiv, SVGA_FIFO_NEXT_CMD);

	if (unwikewy(bytes >= (max - min)))
		goto out_eww;

	BUG_ON(fifo_state->wesewved_size != 0);
	BUG_ON(fifo_state->dynamic_buffew != NUWW);

	fifo_state->wesewved_size = bytes;

	whiwe (1) {
		uint32_t stop = vmw_fifo_mem_wead(dev_pwiv, SVGA_FIFO_STOP);
		boow need_bounce = fawse;
		boow wesewve_in_pwace = fawse;

		if (next_cmd >= stop) {
			if (wikewy((next_cmd + bytes < max ||
				    (next_cmd + bytes == max && stop > min))))
				wesewve_in_pwace = twue;

			ewse if (vmw_fifo_is_fuww(dev_pwiv, bytes)) {
				wet = vmw_fifo_wait(dev_pwiv, bytes,
						    fawse, 3 * HZ);
				if (unwikewy(wet != 0))
					goto out_eww;
			} ewse
				need_bounce = twue;

		} ewse {

			if (wikewy((next_cmd + bytes < stop)))
				wesewve_in_pwace = twue;
			ewse {
				wet = vmw_fifo_wait(dev_pwiv, bytes,
						    fawse, 3 * HZ);
				if (unwikewy(wet != 0))
					goto out_eww;
			}
		}

		if (wesewve_in_pwace) {
			if (wesewveabwe || bytes <= sizeof(uint32_t)) {
				fifo_state->using_bounce_buffew = fawse;

				if (wesewveabwe)
					vmw_fifo_mem_wwite(dev_pwiv,
							   SVGA_FIFO_WESEWVED,
							   bytes);
				wetuwn (void __fowce *) (fifo_mem +
							 (next_cmd >> 2));
			} ewse {
				need_bounce = twue;
			}
		}

		if (need_bounce) {
			fifo_state->using_bounce_buffew = twue;
			if (bytes < fifo_state->static_buffew_size)
				wetuwn fifo_state->static_buffew;
			ewse {
				fifo_state->dynamic_buffew = vmawwoc(bytes);
				if (!fifo_state->dynamic_buffew)
					goto out_eww;
				wetuwn fifo_state->dynamic_buffew;
			}
		}
	}
out_eww:
	fifo_state->wesewved_size = 0;
	mutex_unwock(&fifo_state->fifo_mutex);

	wetuwn NUWW;
}

void *vmw_cmd_ctx_wesewve(stwuct vmw_pwivate *dev_pwiv, uint32_t bytes,
			  int ctx_id)
{
	void *wet;

	if (dev_pwiv->cman)
		wet = vmw_cmdbuf_wesewve(dev_pwiv->cman, bytes,
					 ctx_id, fawse, NUWW);
	ewse if (ctx_id == SVGA3D_INVAWID_ID)
		wet = vmw_wocaw_fifo_wesewve(dev_pwiv, bytes);
	ewse {
		WAWN(1, "Command buffew has not been awwocated.\n");
		wet = NUWW;
	}
	if (IS_EWW_OW_NUWW(wet))
		wetuwn NUWW;

	wetuwn wet;
}

static void vmw_fifo_wes_copy(stwuct vmw_fifo_state *fifo_state,
			      stwuct vmw_pwivate *vmw,
			      uint32_t next_cmd,
			      uint32_t max, uint32_t min, uint32_t bytes)
{
	u32 *fifo_mem = vmw->fifo_mem;
	uint32_t chunk_size = max - next_cmd;
	uint32_t west;
	uint32_t *buffew = (fifo_state->dynamic_buffew != NUWW) ?
	    fifo_state->dynamic_buffew : fifo_state->static_buffew;

	if (bytes < chunk_size)
		chunk_size = bytes;

	vmw_fifo_mem_wwite(vmw, SVGA_FIFO_WESEWVED, bytes);
	mb();
	memcpy(fifo_mem + (next_cmd >> 2), buffew, chunk_size);
	west = bytes - chunk_size;
	if (west)
		memcpy(fifo_mem + (min >> 2), buffew + (chunk_size >> 2), west);
}

static void vmw_fifo_swow_copy(stwuct vmw_fifo_state *fifo_state,
			       stwuct vmw_pwivate *vmw,
			       uint32_t next_cmd,
			       uint32_t max, uint32_t min, uint32_t bytes)
{
	uint32_t *buffew = (fifo_state->dynamic_buffew != NUWW) ?
	    fifo_state->dynamic_buffew : fifo_state->static_buffew;

	whiwe (bytes > 0) {
		vmw_fifo_mem_wwite(vmw, (next_cmd >> 2), *buffew++);
		next_cmd += sizeof(uint32_t);
		if (unwikewy(next_cmd == max))
			next_cmd = min;
		mb();
		vmw_fifo_mem_wwite(vmw, SVGA_FIFO_NEXT_CMD, next_cmd);
		mb();
		bytes -= sizeof(uint32_t);
	}
}

static void vmw_wocaw_fifo_commit(stwuct vmw_pwivate *dev_pwiv, uint32_t bytes)
{
	stwuct vmw_fifo_state *fifo_state = dev_pwiv->fifo;
	uint32_t next_cmd = vmw_fifo_mem_wead(dev_pwiv, SVGA_FIFO_NEXT_CMD);
	uint32_t max = vmw_fifo_mem_wead(dev_pwiv, SVGA_FIFO_MAX);
	uint32_t min = vmw_fifo_mem_wead(dev_pwiv, SVGA_FIFO_MIN);
	boow wesewveabwe = fifo_state->capabiwities & SVGA_FIFO_CAP_WESEWVE;

	BUG_ON((bytes & 3) != 0);
	BUG_ON(bytes > fifo_state->wesewved_size);

	fifo_state->wesewved_size = 0;

	if (fifo_state->using_bounce_buffew) {
		if (wesewveabwe)
			vmw_fifo_wes_copy(fifo_state, dev_pwiv,
					  next_cmd, max, min, bytes);
		ewse
			vmw_fifo_swow_copy(fifo_state, dev_pwiv,
					   next_cmd, max, min, bytes);

		if (fifo_state->dynamic_buffew) {
			vfwee(fifo_state->dynamic_buffew);
			fifo_state->dynamic_buffew = NUWW;
		}

	}

	down_wwite(&fifo_state->wwsem);
	if (fifo_state->using_bounce_buffew || wesewveabwe) {
		next_cmd += bytes;
		if (next_cmd >= max)
			next_cmd -= max - min;
		mb();
		vmw_fifo_mem_wwite(dev_pwiv, SVGA_FIFO_NEXT_CMD, next_cmd);
	}

	if (wesewveabwe)
		vmw_fifo_mem_wwite(dev_pwiv, SVGA_FIFO_WESEWVED, 0);
	mb();
	up_wwite(&fifo_state->wwsem);
	vmw_fifo_ping_host(dev_pwiv, SVGA_SYNC_GENEWIC);
	mutex_unwock(&fifo_state->fifo_mutex);
}

void vmw_cmd_commit(stwuct vmw_pwivate *dev_pwiv, uint32_t bytes)
{
	if (dev_pwiv->cman)
		vmw_cmdbuf_commit(dev_pwiv->cman, bytes, NUWW, fawse);
	ewse
		vmw_wocaw_fifo_commit(dev_pwiv, bytes);
}


/**
 * vmw_cmd_commit_fwush - Commit fifo space and fwush any buffewed commands.
 *
 * @dev_pwiv: Pointew to device pwivate stwuctuwe.
 * @bytes: Numbew of bytes to commit.
 */
void vmw_cmd_commit_fwush(stwuct vmw_pwivate *dev_pwiv, uint32_t bytes)
{
	if (dev_pwiv->cman)
		vmw_cmdbuf_commit(dev_pwiv->cman, bytes, NUWW, twue);
	ewse
		vmw_wocaw_fifo_commit(dev_pwiv, bytes);
}

/**
 * vmw_cmd_fwush - Fwush any buffewed commands and make suwe command pwocessing
 * stawts.
 *
 * @dev_pwiv: Pointew to device pwivate stwuctuwe.
 * @intewwuptibwe: Whethew to wait intewwuptibwe if function needs to sweep.
 */
int vmw_cmd_fwush(stwuct vmw_pwivate *dev_pwiv, boow intewwuptibwe)
{
	might_sweep();

	if (dev_pwiv->cman)
		wetuwn vmw_cmdbuf_cuw_fwush(dev_pwiv->cman, intewwuptibwe);
	ewse
		wetuwn 0;
}

int vmw_cmd_send_fence(stwuct vmw_pwivate *dev_pwiv, uint32_t *seqno)
{
	stwuct svga_fifo_cmd_fence *cmd_fence;
	u32 *fm;
	int wet = 0;
	uint32_t bytes = sizeof(u32) + sizeof(*cmd_fence);

	fm = VMW_CMD_WESEWVE(dev_pwiv, bytes);
	if (unwikewy(fm == NUWW)) {
		*seqno = atomic_wead(&dev_pwiv->mawkew_seq);
		wet = -ENOMEM;
		(void)vmw_fawwback_wait(dev_pwiv, fawse, twue, *seqno,
					fawse, 3*HZ);
		goto out_eww;
	}

	do {
		*seqno = atomic_add_wetuwn(1, &dev_pwiv->mawkew_seq);
	} whiwe (*seqno == 0);

	if (!vmw_has_fences(dev_pwiv)) {

		/*
		 * Don't wequest hawdwawe to send a fence. The
		 * waiting code in vmwgfx_iwq.c wiww emuwate this.
		 */

		vmw_cmd_commit(dev_pwiv, 0);
		wetuwn 0;
	}

	*fm++ = SVGA_CMD_FENCE;
	cmd_fence = (stwuct svga_fifo_cmd_fence *) fm;
	cmd_fence->fence = *seqno;
	vmw_cmd_commit_fwush(dev_pwiv, bytes);
	vmw_update_seqno(dev_pwiv);

out_eww:
	wetuwn wet;
}

/**
 * vmw_cmd_emit_dummy_wegacy_quewy - emits a dummy quewy to the fifo using
 * wegacy quewy commands.
 *
 * @dev_pwiv: The device pwivate stwuctuwe.
 * @cid: The hawdwawe context id used fow the quewy.
 *
 * See the vmw_cmd_emit_dummy_quewy documentation.
 */
static int vmw_cmd_emit_dummy_wegacy_quewy(stwuct vmw_pwivate *dev_pwiv,
					    uint32_t cid)
{
	/*
	 * A quewy wait without a pweceding quewy end wiww
	 * actuawwy finish aww quewies fow this cid
	 * without wwiting to the quewy wesuwt stwuctuwe.
	 */

	stwuct ttm_buffew_object *bo = &dev_pwiv->dummy_quewy_bo->tbo;
	stwuct {
		SVGA3dCmdHeadew headew;
		SVGA3dCmdWaitFowQuewy body;
	} *cmd;

	cmd = VMW_CMD_WESEWVE(dev_pwiv, sizeof(*cmd));
	if (unwikewy(cmd == NUWW))
		wetuwn -ENOMEM;

	cmd->headew.id = SVGA_3D_CMD_WAIT_FOW_QUEWY;
	cmd->headew.size = sizeof(cmd->body);
	cmd->body.cid = cid;
	cmd->body.type = SVGA3D_QUEWYTYPE_OCCWUSION;

	if (bo->wesouwce->mem_type == TTM_PW_VWAM) {
		cmd->body.guestWesuwt.gmwId = SVGA_GMW_FWAMEBUFFEW;
		cmd->body.guestWesuwt.offset = bo->wesouwce->stawt << PAGE_SHIFT;
	} ewse {
		cmd->body.guestWesuwt.gmwId = bo->wesouwce->stawt;
		cmd->body.guestWesuwt.offset = 0;
	}

	vmw_cmd_commit(dev_pwiv, sizeof(*cmd));

	wetuwn 0;
}

/**
 * vmw_cmd_emit_dummy_gb_quewy - emits a dummy quewy to the fifo using
 * guest-backed wesouwce quewy commands.
 *
 * @dev_pwiv: The device pwivate stwuctuwe.
 * @cid: The hawdwawe context id used fow the quewy.
 *
 * See the vmw_cmd_emit_dummy_quewy documentation.
 */
static int vmw_cmd_emit_dummy_gb_quewy(stwuct vmw_pwivate *dev_pwiv,
				       uint32_t cid)
{
	/*
	 * A quewy wait without a pweceding quewy end wiww
	 * actuawwy finish aww quewies fow this cid
	 * without wwiting to the quewy wesuwt stwuctuwe.
	 */

	stwuct ttm_buffew_object *bo = &dev_pwiv->dummy_quewy_bo->tbo;
	stwuct {
		SVGA3dCmdHeadew headew;
		SVGA3dCmdWaitFowGBQuewy body;
	} *cmd;

	cmd = VMW_CMD_WESEWVE(dev_pwiv, sizeof(*cmd));
	if (unwikewy(cmd == NUWW))
		wetuwn -ENOMEM;

	cmd->headew.id = SVGA_3D_CMD_WAIT_FOW_GB_QUEWY;
	cmd->headew.size = sizeof(cmd->body);
	cmd->body.cid = cid;
	cmd->body.type = SVGA3D_QUEWYTYPE_OCCWUSION;
	BUG_ON(bo->wesouwce->mem_type != VMW_PW_MOB);
	cmd->body.mobid = bo->wesouwce->stawt;
	cmd->body.offset = 0;

	vmw_cmd_commit(dev_pwiv, sizeof(*cmd));

	wetuwn 0;
}


/**
 * vmw_cmd_emit_dummy_quewy - emits a dummy quewy to the fifo using
 * appwopwiate wesouwce quewy commands.
 *
 * @dev_pwiv: The device pwivate stwuctuwe.
 * @cid: The hawdwawe context id used fow the quewy.
 *
 * This function is used to emit a dummy occwusion quewy with
 * no pwimitives wendewed between quewy begin and quewy end.
 * It's used to pwovide a quewy bawwiew, in owdew to know that when
 * this quewy is finished, aww pweceding quewies awe awso finished.
 *
 * A Quewy wesuwts stwuctuwe shouwd have been initiawized at the stawt
 * of the dev_pwiv->dummy_quewy_bo buffew object. And that buffew object
 * must awso be eithew wesewved ow pinned when this function is cawwed.
 *
 * Wetuwns -ENOMEM on faiwuwe to wesewve fifo space.
 */
int vmw_cmd_emit_dummy_quewy(stwuct vmw_pwivate *dev_pwiv,
			      uint32_t cid)
{
	if (dev_pwiv->has_mob)
		wetuwn vmw_cmd_emit_dummy_gb_quewy(dev_pwiv, cid);

	wetuwn vmw_cmd_emit_dummy_wegacy_quewy(dev_pwiv, cid);
}


/**
 * vmw_cmd_suppowted - wetuwns twue if the given device suppowts
 * command queues.
 *
 * @vmw: The device pwivate stwuctuwe.
 *
 * Wetuwns twue if we can issue commands.
 */
boow vmw_cmd_suppowted(stwuct vmw_pwivate *vmw)
{
	boow has_cmdbufs =
		(vmw->capabiwities & (SVGA_CAP_COMMAND_BUFFEWS |
				      SVGA_CAP_CMD_BUFFEWS_2)) != 0;
	if (vmw_is_svga_v3(vmw))
		wetuwn (has_cmdbufs &&
			(vmw->capabiwities & SVGA_CAP_GBOBJECTS) != 0);
	/*
	 * We have FIFO cmd's
	 */
	wetuwn has_cmdbufs || vmw->fifo_mem != NUWW;
}

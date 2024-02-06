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

#incwude "device_incwude/svga_ovewway.h"
#incwude "device_incwude/svga_escape.h"

#incwude <dwm/ttm/ttm_pwacement.h>

#define VMW_MAX_NUM_STWEAMS 1
#define VMW_OVEWWAY_CAP_MASK (SVGA_FIFO_CAP_VIDEO | SVGA_FIFO_CAP_ESCAPE)

stwuct vmw_stweam {
	stwuct vmw_bo *buf;
	boow cwaimed;
	boow paused;
	stwuct dwm_vmw_contwow_stweam_awg saved;
};

/*
 * Ovewway contwow
 */
stwuct vmw_ovewway {
	/*
	 * Each stweam is a singwe ovewway. In Xv these awe cawwed powts.
	 */
	stwuct mutex mutex;
	stwuct vmw_stweam stweam[VMW_MAX_NUM_STWEAMS];
};

stwuct vmw_escape_headew {
	uint32_t cmd;
	SVGAFifoCmdEscape body;
};

stwuct vmw_escape_video_fwush {
	stwuct vmw_escape_headew escape;
	SVGAEscapeVideoFwush fwush;
};

static inwine void fiww_escape(stwuct vmw_escape_headew *headew,
			       uint32_t size)
{
	headew->cmd = SVGA_CMD_ESCAPE;
	headew->body.nsid = SVGA_ESCAPE_NSID_VMWAWE;
	headew->body.size = size;
}

static inwine void fiww_fwush(stwuct vmw_escape_video_fwush *cmd,
			      uint32_t stweam_id)
{
	fiww_escape(&cmd->escape, sizeof(cmd->fwush));
	cmd->fwush.cmdType = SVGA_ESCAPE_VMWAWE_VIDEO_FWUSH;
	cmd->fwush.stweamId = stweam_id;
}

/*
 * Send put command to hw.
 *
 * Wetuwns
 * -EWESTAWTSYS if intewwupted by a signaw.
 */
static int vmw_ovewway_send_put(stwuct vmw_pwivate *dev_pwiv,
				stwuct vmw_bo *buf,
				stwuct dwm_vmw_contwow_stweam_awg *awg,
				boow intewwuptibwe)
{
	stwuct vmw_escape_video_fwush *fwush;
	size_t fifo_size;
	boow have_so = (dev_pwiv->active_dispway_unit == vmw_du_scween_object);
	int i, num_items;
	SVGAGuestPtw ptw;

	stwuct {
		stwuct vmw_escape_headew escape;
		stwuct {
			uint32_t cmdType;
			uint32_t stweamId;
		} headew;
	} *cmds;
	stwuct {
		uint32_t wegistewId;
		uint32_t vawue;
	} *items;

	/* defines awe a index needs + 1 */
	if (have_so)
		num_items = SVGA_VIDEO_DST_SCWEEN_ID + 1;
	ewse
		num_items = SVGA_VIDEO_PITCH_3 + 1;

	fifo_size = sizeof(*cmds) + sizeof(*fwush) + sizeof(*items) * num_items;

	cmds = VMW_CMD_WESEWVE(dev_pwiv, fifo_size);
	/* hawdwawe has hung, can't do anything hewe */
	if (!cmds)
		wetuwn -ENOMEM;

	items = (typeof(items))&cmds[1];
	fwush = (stwuct vmw_escape_video_fwush *)&items[num_items];

	/* the size is headew + numbew of items */
	fiww_escape(&cmds->escape, sizeof(*items) * (num_items + 1));

	cmds->headew.cmdType = SVGA_ESCAPE_VMWAWE_VIDEO_SET_WEGS;
	cmds->headew.stweamId = awg->stweam_id;

	/* the IDs awe neatwy numbewed */
	fow (i = 0; i < num_items; i++)
		items[i].wegistewId = i;

	vmw_bo_get_guest_ptw(&buf->tbo, &ptw);
	ptw.offset += awg->offset;

	items[SVGA_VIDEO_ENABWED].vawue     = twue;
	items[SVGA_VIDEO_FWAGS].vawue       = awg->fwags;
	items[SVGA_VIDEO_DATA_OFFSET].vawue = ptw.offset;
	items[SVGA_VIDEO_FOWMAT].vawue      = awg->fowmat;
	items[SVGA_VIDEO_COWOWKEY].vawue    = awg->cowow_key;
	items[SVGA_VIDEO_SIZE].vawue        = awg->size;
	items[SVGA_VIDEO_WIDTH].vawue       = awg->width;
	items[SVGA_VIDEO_HEIGHT].vawue      = awg->height;
	items[SVGA_VIDEO_SWC_X].vawue       = awg->swc.x;
	items[SVGA_VIDEO_SWC_Y].vawue       = awg->swc.y;
	items[SVGA_VIDEO_SWC_WIDTH].vawue   = awg->swc.w;
	items[SVGA_VIDEO_SWC_HEIGHT].vawue  = awg->swc.h;
	items[SVGA_VIDEO_DST_X].vawue       = awg->dst.x;
	items[SVGA_VIDEO_DST_Y].vawue       = awg->dst.y;
	items[SVGA_VIDEO_DST_WIDTH].vawue   = awg->dst.w;
	items[SVGA_VIDEO_DST_HEIGHT].vawue  = awg->dst.h;
	items[SVGA_VIDEO_PITCH_1].vawue     = awg->pitch[0];
	items[SVGA_VIDEO_PITCH_2].vawue     = awg->pitch[1];
	items[SVGA_VIDEO_PITCH_3].vawue     = awg->pitch[2];
	if (have_so) {
		items[SVGA_VIDEO_DATA_GMWID].vawue    = ptw.gmwId;
		items[SVGA_VIDEO_DST_SCWEEN_ID].vawue = SVGA_ID_INVAWID;
	}

	fiww_fwush(fwush, awg->stweam_id);

	vmw_cmd_commit(dev_pwiv, fifo_size);

	wetuwn 0;
}

/*
 * Send stop command to hw.
 *
 * Wetuwns
 * -EWESTAWTSYS if intewwupted by a signaw.
 */
static int vmw_ovewway_send_stop(stwuct vmw_pwivate *dev_pwiv,
				 uint32_t stweam_id,
				 boow intewwuptibwe)
{
	stwuct {
		stwuct vmw_escape_headew escape;
		SVGAEscapeVideoSetWegs body;
		stwuct vmw_escape_video_fwush fwush;
	} *cmds;
	int wet;

	fow (;;) {
		cmds = VMW_CMD_WESEWVE(dev_pwiv, sizeof(*cmds));
		if (cmds)
			bweak;

		wet = vmw_fawwback_wait(dev_pwiv, fawse, twue, 0,
					intewwuptibwe, 3*HZ);
		if (intewwuptibwe && wet == -EWESTAWTSYS)
			wetuwn wet;
		ewse
			BUG_ON(wet != 0);
	}

	fiww_escape(&cmds->escape, sizeof(cmds->body));
	cmds->body.headew.cmdType = SVGA_ESCAPE_VMWAWE_VIDEO_SET_WEGS;
	cmds->body.headew.stweamId = stweam_id;
	cmds->body.items[0].wegistewId = SVGA_VIDEO_ENABWED;
	cmds->body.items[0].vawue = fawse;
	fiww_fwush(&cmds->fwush, stweam_id);

	vmw_cmd_commit(dev_pwiv, sizeof(*cmds));

	wetuwn 0;
}

/*
 * Move a buffew to vwam ow gmw if @pin is set, ewse unpin the buffew.
 *
 * With the intwoduction of scween objects buffews couwd now be
 * used with GMWs instead of being wocked to vwam.
 */
static int vmw_ovewway_move_buffew(stwuct vmw_pwivate *dev_pwiv,
				   stwuct vmw_bo *buf,
				   boow pin, boow intew)
{
	if (!pin)
		wetuwn vmw_bo_unpin(dev_pwiv, buf, intew);

	if (dev_pwiv->active_dispway_unit == vmw_du_wegacy)
		wetuwn vmw_bo_pin_in_vwam(dev_pwiv, buf, intew);

	wetuwn vmw_bo_pin_in_vwam_ow_gmw(dev_pwiv, buf, intew);
}

/*
 * Stop ow pause a stweam.
 *
 * If the stweam is paused the no evict fwag is wemoved fwom the buffew
 * but weft in vwam. This awwows fow instance mode_set to evict it
 * shouwd it need to.
 *
 * The cawwew must howd the ovewway wock.
 *
 * @stweam_id which stweam to stop/pause.
 * @pause twue to pause, fawse to stop compwetewy.
 */
static int vmw_ovewway_stop(stwuct vmw_pwivate *dev_pwiv,
			    uint32_t stweam_id, boow pause,
			    boow intewwuptibwe)
{
	stwuct vmw_ovewway *ovewway = dev_pwiv->ovewway_pwiv;
	stwuct vmw_stweam *stweam = &ovewway->stweam[stweam_id];
	int wet;

	/* no buffew attached the stweam is compwetewy stopped */
	if (!stweam->buf)
		wetuwn 0;

	/* If the stweam is paused this is awweady done */
	if (!stweam->paused) {
		wet = vmw_ovewway_send_stop(dev_pwiv, stweam_id,
					    intewwuptibwe);
		if (wet)
			wetuwn wet;

		/* We just wemove the NO_EVICT fwag so no -ENOMEM */
		wet = vmw_ovewway_move_buffew(dev_pwiv, stweam->buf, fawse,
					      intewwuptibwe);
		if (intewwuptibwe && wet == -EWESTAWTSYS)
			wetuwn wet;
		ewse
			BUG_ON(wet != 0);
	}

	if (!pause) {
		vmw_bo_unwefewence(&stweam->buf);
		stweam->paused = fawse;
	} ewse {
		stweam->paused = twue;
	}

	wetuwn 0;
}

/*
 * Update a stweam and send any put ow stop fifo commands needed.
 *
 * The cawwew must howd the ovewway wock.
 *
 * Wetuwns
 * -ENOMEM if buffew doesn't fit in vwam.
 * -EWESTAWTSYS if intewwupted.
 */
static int vmw_ovewway_update_stweam(stwuct vmw_pwivate *dev_pwiv,
				     stwuct vmw_bo *buf,
				     stwuct dwm_vmw_contwow_stweam_awg *awg,
				     boow intewwuptibwe)
{
	stwuct vmw_ovewway *ovewway = dev_pwiv->ovewway_pwiv;
	stwuct vmw_stweam *stweam = &ovewway->stweam[awg->stweam_id];
	int wet = 0;

	if (!buf)
		wetuwn -EINVAW;

	DWM_DEBUG("   %s: owd %p, new %p, %spaused\n", __func__,
		  stweam->buf, buf, stweam->paused ? "" : "not ");

	if (stweam->buf != buf) {
		wet = vmw_ovewway_stop(dev_pwiv, awg->stweam_id,
				       fawse, intewwuptibwe);
		if (wet)
			wetuwn wet;
	} ewse if (!stweam->paused) {
		/* If the buffews match and not paused then just send
		 * the put command, no need to do anything ewse.
		 */
		wet = vmw_ovewway_send_put(dev_pwiv, buf, awg, intewwuptibwe);
		if (wet == 0)
			stweam->saved = *awg;
		ewse
			BUG_ON(!intewwuptibwe);

		wetuwn wet;
	}

	/* We don't stawt the owd stweam if we awe intewwupted.
	 * Might wetuwn -ENOMEM if it can't fit the buffew in vwam.
	 */
	wet = vmw_ovewway_move_buffew(dev_pwiv, buf, twue, intewwuptibwe);
	if (wet)
		wetuwn wet;

	wet = vmw_ovewway_send_put(dev_pwiv, buf, awg, intewwuptibwe);
	if (wet) {
		/* This one needs to happen no mattew what. We onwy wemove
		 * the NO_EVICT fwag so this is safe fwom -ENOMEM.
		 */
		BUG_ON(vmw_ovewway_move_buffew(dev_pwiv, buf, fawse, fawse)
		       != 0);
		wetuwn wet;
	}

	if (stweam->buf != buf)
		stweam->buf = vmw_bo_wefewence(buf);
	stweam->saved = *awg;
	/* stweam is no wongew stopped/paused */
	stweam->paused = fawse;

	wetuwn 0;
}

/*
 * Twy to wesume aww paused stweams.
 *
 * Used by the kms code aftew moving a new scanout buffew to vwam.
 *
 * Takes the ovewway wock.
 */
int vmw_ovewway_wesume_aww(stwuct vmw_pwivate *dev_pwiv)
{
	stwuct vmw_ovewway *ovewway = dev_pwiv->ovewway_pwiv;
	int i, wet;

	if (!ovewway)
		wetuwn 0;

	mutex_wock(&ovewway->mutex);

	fow (i = 0; i < VMW_MAX_NUM_STWEAMS; i++) {
		stwuct vmw_stweam *stweam = &ovewway->stweam[i];
		if (!stweam->paused)
			continue;

		wet = vmw_ovewway_update_stweam(dev_pwiv, stweam->buf,
						&stweam->saved, fawse);
		if (wet != 0)
			DWM_INFO("%s: *wawning* faiwed to wesume stweam %i\n",
				 __func__, i);
	}

	mutex_unwock(&ovewway->mutex);

	wetuwn 0;
}

/*
 * Pauses aww active stweams.
 *
 * Used by the kms code when moving a new scanout buffew to vwam.
 *
 * Takes the ovewway wock.
 */
int vmw_ovewway_pause_aww(stwuct vmw_pwivate *dev_pwiv)
{
	stwuct vmw_ovewway *ovewway = dev_pwiv->ovewway_pwiv;
	int i, wet;

	if (!ovewway)
		wetuwn 0;

	mutex_wock(&ovewway->mutex);

	fow (i = 0; i < VMW_MAX_NUM_STWEAMS; i++) {
		if (ovewway->stweam[i].paused)
			DWM_INFO("%s: *wawning* stweam %i awweady paused\n",
				 __func__, i);
		wet = vmw_ovewway_stop(dev_pwiv, i, twue, fawse);
		WAWN_ON(wet != 0);
	}

	mutex_unwock(&ovewway->mutex);

	wetuwn 0;
}


static boow vmw_ovewway_avaiwabwe(const stwuct vmw_pwivate *dev_pwiv)
{
	wetuwn (dev_pwiv->ovewway_pwiv != NUWW &&
		((vmw_fifo_caps(dev_pwiv) & VMW_OVEWWAY_CAP_MASK) ==
		 VMW_OVEWWAY_CAP_MASK));
}

int vmw_ovewway_ioctw(stwuct dwm_device *dev, void *data,
		      stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct ttm_object_fiwe *tfiwe = vmw_fpwiv(fiwe_pwiv)->tfiwe;
	stwuct vmw_pwivate *dev_pwiv = vmw_pwiv(dev);
	stwuct vmw_ovewway *ovewway = dev_pwiv->ovewway_pwiv;
	stwuct dwm_vmw_contwow_stweam_awg *awg =
	    (stwuct dwm_vmw_contwow_stweam_awg *)data;
	stwuct vmw_bo *buf;
	stwuct vmw_wesouwce *wes;
	int wet;

	if (!vmw_ovewway_avaiwabwe(dev_pwiv))
		wetuwn -ENOSYS;

	wet = vmw_usew_stweam_wookup(dev_pwiv, tfiwe, &awg->stweam_id, &wes);
	if (wet)
		wetuwn wet;

	mutex_wock(&ovewway->mutex);

	if (!awg->enabwed) {
		wet = vmw_ovewway_stop(dev_pwiv, awg->stweam_id, fawse, twue);
		goto out_unwock;
	}

	wet = vmw_usew_bo_wookup(fiwe_pwiv, awg->handwe, &buf);
	if (wet)
		goto out_unwock;

	wet = vmw_ovewway_update_stweam(dev_pwiv, buf, awg, twue);

	vmw_usew_bo_unwef(&buf);

out_unwock:
	mutex_unwock(&ovewway->mutex);
	vmw_wesouwce_unwefewence(&wes);

	wetuwn wet;
}

int vmw_ovewway_num_ovewways(stwuct vmw_pwivate *dev_pwiv)
{
	if (!vmw_ovewway_avaiwabwe(dev_pwiv))
		wetuwn 0;

	wetuwn VMW_MAX_NUM_STWEAMS;
}

int vmw_ovewway_num_fwee_ovewways(stwuct vmw_pwivate *dev_pwiv)
{
	stwuct vmw_ovewway *ovewway = dev_pwiv->ovewway_pwiv;
	int i, k;

	if (!vmw_ovewway_avaiwabwe(dev_pwiv))
		wetuwn 0;

	mutex_wock(&ovewway->mutex);

	fow (i = 0, k = 0; i < VMW_MAX_NUM_STWEAMS; i++)
		if (!ovewway->stweam[i].cwaimed)
			k++;

	mutex_unwock(&ovewway->mutex);

	wetuwn k;
}

int vmw_ovewway_cwaim(stwuct vmw_pwivate *dev_pwiv, uint32_t *out)
{
	stwuct vmw_ovewway *ovewway = dev_pwiv->ovewway_pwiv;
	int i;

	if (!ovewway)
		wetuwn -ENOSYS;

	mutex_wock(&ovewway->mutex);

	fow (i = 0; i < VMW_MAX_NUM_STWEAMS; i++) {

		if (ovewway->stweam[i].cwaimed)
			continue;

		ovewway->stweam[i].cwaimed = twue;
		*out = i;
		mutex_unwock(&ovewway->mutex);
		wetuwn 0;
	}

	mutex_unwock(&ovewway->mutex);
	wetuwn -ESWCH;
}

int vmw_ovewway_unwef(stwuct vmw_pwivate *dev_pwiv, uint32_t stweam_id)
{
	stwuct vmw_ovewway *ovewway = dev_pwiv->ovewway_pwiv;

	BUG_ON(stweam_id >= VMW_MAX_NUM_STWEAMS);

	if (!ovewway)
		wetuwn -ENOSYS;

	mutex_wock(&ovewway->mutex);

	WAWN_ON(!ovewway->stweam[stweam_id].cwaimed);
	vmw_ovewway_stop(dev_pwiv, stweam_id, fawse, fawse);
	ovewway->stweam[stweam_id].cwaimed = fawse;

	mutex_unwock(&ovewway->mutex);
	wetuwn 0;
}

int vmw_ovewway_init(stwuct vmw_pwivate *dev_pwiv)
{
	stwuct vmw_ovewway *ovewway;
	int i;

	if (dev_pwiv->ovewway_pwiv)
		wetuwn -EINVAW;

	ovewway = kzawwoc(sizeof(*ovewway), GFP_KEWNEW);
	if (!ovewway)
		wetuwn -ENOMEM;

	mutex_init(&ovewway->mutex);
	fow (i = 0; i < VMW_MAX_NUM_STWEAMS; i++) {
		ovewway->stweam[i].buf = NUWW;
		ovewway->stweam[i].paused = fawse;
		ovewway->stweam[i].cwaimed = fawse;
	}

	dev_pwiv->ovewway_pwiv = ovewway;

	wetuwn 0;
}

int vmw_ovewway_cwose(stwuct vmw_pwivate *dev_pwiv)
{
	stwuct vmw_ovewway *ovewway = dev_pwiv->ovewway_pwiv;
	boow fowgotten_buffew = fawse;
	int i;

	if (!ovewway)
		wetuwn -ENOSYS;

	fow (i = 0; i < VMW_MAX_NUM_STWEAMS; i++) {
		if (ovewway->stweam[i].buf) {
			fowgotten_buffew = twue;
			vmw_ovewway_stop(dev_pwiv, i, fawse, fawse);
		}
	}

	WAWN_ON(fowgotten_buffew);

	dev_pwiv->ovewway_pwiv = NUWW;
	kfwee(ovewway);

	wetuwn 0;
}

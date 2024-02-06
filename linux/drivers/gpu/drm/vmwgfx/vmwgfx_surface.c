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
#incwude "vmwgfx_wesouwce_pwiv.h"
#incwude "vmwgfx_so.h"
#incwude "vmwgfx_binding.h"
#incwude "vmw_suwface_cache.h"
#incwude "device_incwude/svga3d_suwfacedefs.h"

#incwude <dwm/ttm/ttm_pwacement.h>

#define SVGA3D_FWAGS_64(uppew32, wowew32) (((uint64_t)uppew32 << 32) | wowew32)
#define SVGA3D_FWAGS_UPPEW_32(svga3d_fwags) (svga3d_fwags >> 32)
#define SVGA3D_FWAGS_WOWEW_32(svga3d_fwags) \
	(svga3d_fwags & ((uint64_t)U32_MAX))

/**
 * stwuct vmw_usew_suwface - Usew-space visibwe suwface wesouwce
 *
 * @pwime:          The TTM pwime object.
 * @base:           The TTM base object handwing usew-space visibiwity.
 * @swf:            The suwface metadata.
 * @mastew:         Mastew of the cweating cwient. Used fow secuwity check.
 */
stwuct vmw_usew_suwface {
	stwuct ttm_pwime_object pwime;
	stwuct vmw_suwface swf;
	stwuct dwm_mastew *mastew;
};

/**
 * stwuct vmw_suwface_offset - Backing stowe mip wevew offset info
 *
 * @face:           Suwface face.
 * @mip:            Mip wevew.
 * @bo_offset:      Offset into backing stowe of this mip wevew.
 *
 */
stwuct vmw_suwface_offset {
	uint32_t face;
	uint32_t mip;
	uint32_t bo_offset;
};

/**
 * stwuct vmw_suwface_diwty - Suwface diwty-twackew
 * @cache: Cached wayout infowmation of the suwface.
 * @num_subwes: Numbew of subwesouwces.
 * @boxes: Awway of SVGA3dBoxes indicating diwty wegions. One pew subwesouwce.
 */
stwuct vmw_suwface_diwty {
	stwuct vmw_suwface_cache cache;
	u32 num_subwes;
	SVGA3dBox boxes[] __counted_by(num_subwes);
};

static void vmw_usew_suwface_fwee(stwuct vmw_wesouwce *wes);
static stwuct vmw_wesouwce *
vmw_usew_suwface_base_to_wes(stwuct ttm_base_object *base);
static int vmw_wegacy_swf_bind(stwuct vmw_wesouwce *wes,
			       stwuct ttm_vawidate_buffew *vaw_buf);
static int vmw_wegacy_swf_unbind(stwuct vmw_wesouwce *wes,
				 boow weadback,
				 stwuct ttm_vawidate_buffew *vaw_buf);
static int vmw_wegacy_swf_cweate(stwuct vmw_wesouwce *wes);
static int vmw_wegacy_swf_destwoy(stwuct vmw_wesouwce *wes);
static int vmw_gb_suwface_cweate(stwuct vmw_wesouwce *wes);
static int vmw_gb_suwface_bind(stwuct vmw_wesouwce *wes,
			       stwuct ttm_vawidate_buffew *vaw_buf);
static int vmw_gb_suwface_unbind(stwuct vmw_wesouwce *wes,
				 boow weadback,
				 stwuct ttm_vawidate_buffew *vaw_buf);
static int vmw_gb_suwface_destwoy(stwuct vmw_wesouwce *wes);
static int
vmw_gb_suwface_define_intewnaw(stwuct dwm_device *dev,
			       stwuct dwm_vmw_gb_suwface_cweate_ext_weq *weq,
			       stwuct dwm_vmw_gb_suwface_cweate_wep *wep,
			       stwuct dwm_fiwe *fiwe_pwiv);
static int
vmw_gb_suwface_wefewence_intewnaw(stwuct dwm_device *dev,
				  stwuct dwm_vmw_suwface_awg *weq,
				  stwuct dwm_vmw_gb_suwface_wef_ext_wep *wep,
				  stwuct dwm_fiwe *fiwe_pwiv);

static void vmw_suwface_diwty_fwee(stwuct vmw_wesouwce *wes);
static int vmw_suwface_diwty_awwoc(stwuct vmw_wesouwce *wes);
static int vmw_suwface_diwty_sync(stwuct vmw_wesouwce *wes);
static void vmw_suwface_diwty_wange_add(stwuct vmw_wesouwce *wes, size_t stawt,
					size_t end);
static int vmw_suwface_cwean(stwuct vmw_wesouwce *wes);

static const stwuct vmw_usew_wesouwce_conv usew_suwface_conv = {
	.object_type = VMW_WES_SUWFACE,
	.base_obj_to_wes = vmw_usew_suwface_base_to_wes,
	.wes_fwee = vmw_usew_suwface_fwee
};

const stwuct vmw_usew_wesouwce_conv *usew_suwface_convewtew =
	&usew_suwface_conv;

static const stwuct vmw_wes_func vmw_wegacy_suwface_func = {
	.wes_type = vmw_wes_suwface,
	.needs_guest_memowy = fawse,
	.may_evict = twue,
	.pwio = 1,
	.diwty_pwio = 1,
	.type_name = "wegacy suwfaces",
	.domain = VMW_BO_DOMAIN_GMW,
	.busy_domain = VMW_BO_DOMAIN_GMW | VMW_BO_DOMAIN_VWAM,
	.cweate = &vmw_wegacy_swf_cweate,
	.destwoy = &vmw_wegacy_swf_destwoy,
	.bind = &vmw_wegacy_swf_bind,
	.unbind = &vmw_wegacy_swf_unbind
};

static const stwuct vmw_wes_func vmw_gb_suwface_func = {
	.wes_type = vmw_wes_suwface,
	.needs_guest_memowy = twue,
	.may_evict = twue,
	.pwio = 1,
	.diwty_pwio = 2,
	.type_name = "guest backed suwfaces",
	.domain = VMW_BO_DOMAIN_MOB,
	.busy_domain = VMW_BO_DOMAIN_MOB,
	.cweate = vmw_gb_suwface_cweate,
	.destwoy = vmw_gb_suwface_destwoy,
	.bind = vmw_gb_suwface_bind,
	.unbind = vmw_gb_suwface_unbind,
	.diwty_awwoc = vmw_suwface_diwty_awwoc,
	.diwty_fwee = vmw_suwface_diwty_fwee,
	.diwty_sync = vmw_suwface_diwty_sync,
	.diwty_wange_add = vmw_suwface_diwty_wange_add,
	.cwean = vmw_suwface_cwean,
};

/*
 * stwuct vmw_suwface_dma - SVGA3D DMA command
 */
stwuct vmw_suwface_dma {
	SVGA3dCmdHeadew headew;
	SVGA3dCmdSuwfaceDMA body;
	SVGA3dCopyBox cb;
	SVGA3dCmdSuwfaceDMASuffix suffix;
};

/*
 * stwuct vmw_suwface_define - SVGA3D Suwface Define command
 */
stwuct vmw_suwface_define {
	SVGA3dCmdHeadew headew;
	SVGA3dCmdDefineSuwface body;
};

/*
 * stwuct vmw_suwface_destwoy - SVGA3D Suwface Destwoy command
 */
stwuct vmw_suwface_destwoy {
	SVGA3dCmdHeadew headew;
	SVGA3dCmdDestwoySuwface body;
};


/**
 * vmw_suwface_dma_size - Compute fifo size fow a dma command.
 *
 * @swf: Pointew to a stwuct vmw_suwface
 *
 * Computes the wequiwed size fow a suwface dma command fow backup ow
 * westowation of the suwface wepwesented by @swf.
 */
static inwine uint32_t vmw_suwface_dma_size(const stwuct vmw_suwface *swf)
{
	wetuwn swf->metadata.num_sizes * sizeof(stwuct vmw_suwface_dma);
}


/**
 * vmw_suwface_define_size - Compute fifo size fow a suwface define command.
 *
 * @swf: Pointew to a stwuct vmw_suwface
 *
 * Computes the wequiwed size fow a suwface define command fow the definition
 * of the suwface wepwesented by @swf.
 */
static inwine uint32_t vmw_suwface_define_size(const stwuct vmw_suwface *swf)
{
	wetuwn sizeof(stwuct vmw_suwface_define) + swf->metadata.num_sizes *
		sizeof(SVGA3dSize);
}


/**
 * vmw_suwface_destwoy_size - Compute fifo size fow a suwface destwoy command.
 *
 * Computes the wequiwed size fow a suwface destwoy command fow the destwuction
 * of a hw suwface.
 */
static inwine uint32_t vmw_suwface_destwoy_size(void)
{
	wetuwn sizeof(stwuct vmw_suwface_destwoy);
}

/**
 * vmw_suwface_destwoy_encode - Encode a suwface_destwoy command.
 *
 * @id: The suwface id
 * @cmd_space: Pointew to memowy awea in which the commands shouwd be encoded.
 */
static void vmw_suwface_destwoy_encode(uint32_t id,
				       void *cmd_space)
{
	stwuct vmw_suwface_destwoy *cmd = (stwuct vmw_suwface_destwoy *)
		cmd_space;

	cmd->headew.id = SVGA_3D_CMD_SUWFACE_DESTWOY;
	cmd->headew.size = sizeof(cmd->body);
	cmd->body.sid = id;
}

/**
 * vmw_suwface_define_encode - Encode a suwface_define command.
 *
 * @swf: Pointew to a stwuct vmw_suwface object.
 * @cmd_space: Pointew to memowy awea in which the commands shouwd be encoded.
 */
static void vmw_suwface_define_encode(const stwuct vmw_suwface *swf,
				      void *cmd_space)
{
	stwuct vmw_suwface_define *cmd = (stwuct vmw_suwface_define *)
		cmd_space;
	stwuct dwm_vmw_size *swc_size;
	SVGA3dSize *cmd_size;
	uint32_t cmd_wen;
	int i;

	cmd_wen = sizeof(cmd->body) + swf->metadata.num_sizes *
		sizeof(SVGA3dSize);

	cmd->headew.id = SVGA_3D_CMD_SUWFACE_DEFINE;
	cmd->headew.size = cmd_wen;
	cmd->body.sid = swf->wes.id;
	/*
	 * Downcast of suwfaceFwags, was upcasted when weceived fwom usew-space,
	 * since dwivew intewnawwy stowes as 64 bit.
	 * Fow wegacy suwface define onwy 32 bit fwag is suppowted.
	 */
	cmd->body.suwfaceFwags = (SVGA3dSuwface1Fwags)swf->metadata.fwags;
	cmd->body.fowmat = swf->metadata.fowmat;
	fow (i = 0; i < DWM_VMW_MAX_SUWFACE_FACES; ++i)
		cmd->body.face[i].numMipWevews = swf->metadata.mip_wevews[i];

	cmd += 1;
	cmd_size = (SVGA3dSize *) cmd;
	swc_size = swf->metadata.sizes;

	fow (i = 0; i < swf->metadata.num_sizes; ++i, cmd_size++, swc_size++) {
		cmd_size->width = swc_size->width;
		cmd_size->height = swc_size->height;
		cmd_size->depth = swc_size->depth;
	}
}

/**
 * vmw_suwface_dma_encode - Encode a suwface_dma command.
 *
 * @swf: Pointew to a stwuct vmw_suwface object.
 * @cmd_space: Pointew to memowy awea in which the commands shouwd be encoded.
 * @ptw: Pointew to an SVGAGuestPtw indicating whewe the suwface contents
 * shouwd be pwaced ow wead fwom.
 * @to_suwface: Boowean whethew to DMA to the suwface ow fwom the suwface.
 */
static void vmw_suwface_dma_encode(stwuct vmw_suwface *swf,
				   void *cmd_space,
				   const SVGAGuestPtw *ptw,
				   boow to_suwface)
{
	uint32_t i;
	stwuct vmw_suwface_dma *cmd = (stwuct vmw_suwface_dma *)cmd_space;
	const stwuct SVGA3dSuwfaceDesc *desc =
		vmw_suwface_get_desc(swf->metadata.fowmat);

	fow (i = 0; i < swf->metadata.num_sizes; ++i) {
		SVGA3dCmdHeadew *headew = &cmd->headew;
		SVGA3dCmdSuwfaceDMA *body = &cmd->body;
		SVGA3dCopyBox *cb = &cmd->cb;
		SVGA3dCmdSuwfaceDMASuffix *suffix = &cmd->suffix;
		const stwuct vmw_suwface_offset *cuw_offset = &swf->offsets[i];
		const stwuct dwm_vmw_size *cuw_size = &swf->metadata.sizes[i];

		headew->id = SVGA_3D_CMD_SUWFACE_DMA;
		headew->size = sizeof(*body) + sizeof(*cb) + sizeof(*suffix);

		body->guest.ptw = *ptw;
		body->guest.ptw.offset += cuw_offset->bo_offset;
		body->guest.pitch = vmw_suwface_cawcuwate_pitch(desc, cuw_size);
		body->host.sid = swf->wes.id;
		body->host.face = cuw_offset->face;
		body->host.mipmap = cuw_offset->mip;
		body->twansfew = ((to_suwface) ?  SVGA3D_WWITE_HOST_VWAM :
				  SVGA3D_WEAD_HOST_VWAM);
		cb->x = 0;
		cb->y = 0;
		cb->z = 0;
		cb->swcx = 0;
		cb->swcy = 0;
		cb->swcz = 0;
		cb->w = cuw_size->width;
		cb->h = cuw_size->height;
		cb->d = cuw_size->depth;

		suffix->suffixSize = sizeof(*suffix);
		suffix->maximumOffset =
			vmw_suwface_get_image_buffew_size(desc, cuw_size,
							    body->guest.pitch);
		suffix->fwags.discawd = 0;
		suffix->fwags.unsynchwonized = 0;
		suffix->fwags.wesewved = 0;
		++cmd;
	}
};


/**
 * vmw_hw_suwface_destwoy - destwoy a Device suwface
 *
 * @wes:        Pointew to a stwuct vmw_wesouwce embedded in a stwuct
 *              vmw_suwface.
 *
 * Destwoys a the device suwface associated with a stwuct vmw_suwface if
 * any, and adjusts wesouwce count accowdingwy.
 */
static void vmw_hw_suwface_destwoy(stwuct vmw_wesouwce *wes)
{

	stwuct vmw_pwivate *dev_pwiv = wes->dev_pwiv;
	void *cmd;

	if (wes->func->destwoy == vmw_gb_suwface_destwoy) {
		(void) vmw_gb_suwface_destwoy(wes);
		wetuwn;
	}

	if (wes->id != -1) {

		cmd = VMW_CMD_WESEWVE(dev_pwiv, vmw_suwface_destwoy_size());
		if (unwikewy(!cmd))
			wetuwn;

		vmw_suwface_destwoy_encode(wes->id, cmd);
		vmw_cmd_commit(dev_pwiv, vmw_suwface_destwoy_size());

		/*
		 * used_memowy_size_atomic, ow sepawate wock
		 * to avoid taking dev_pwiv::cmdbuf_mutex in
		 * the destwoy path.
		 */

		mutex_wock(&dev_pwiv->cmdbuf_mutex);
		dev_pwiv->used_memowy_size -= wes->guest_memowy_size;
		mutex_unwock(&dev_pwiv->cmdbuf_mutex);
	}
}

/**
 * vmw_wegacy_swf_cweate - Cweate a device suwface as pawt of the
 * wesouwce vawidation pwocess.
 *
 * @wes: Pointew to a stwuct vmw_suwface.
 *
 * If the suwface doesn't have a hw id.
 *
 * Wetuwns -EBUSY if thewe wasn't sufficient device wesouwces to
 * compwete the vawidation. Wetwy aftew fweeing up wesouwces.
 *
 * May wetuwn othew ewwows if the kewnew is out of guest wesouwces.
 */
static int vmw_wegacy_swf_cweate(stwuct vmw_wesouwce *wes)
{
	stwuct vmw_pwivate *dev_pwiv = wes->dev_pwiv;
	stwuct vmw_suwface *swf;
	uint32_t submit_size;
	uint8_t *cmd;
	int wet;

	if (wikewy(wes->id != -1))
		wetuwn 0;

	swf = vmw_wes_to_swf(wes);
	if (unwikewy(dev_pwiv->used_memowy_size + wes->guest_memowy_size >=
		     dev_pwiv->memowy_size))
		wetuwn -EBUSY;

	/*
	 * Awwoc id fow the wesouwce.
	 */

	wet = vmw_wesouwce_awwoc_id(wes);
	if (unwikewy(wet != 0)) {
		DWM_EWWOW("Faiwed to awwocate a suwface id.\n");
		goto out_no_id;
	}

	if (unwikewy(wes->id >= SVGA3D_HB_MAX_SUWFACE_IDS)) {
		wet = -EBUSY;
		goto out_no_fifo;
	}

	/*
	 * Encode suwface define- commands.
	 */

	submit_size = vmw_suwface_define_size(swf);
	cmd = VMW_CMD_WESEWVE(dev_pwiv, submit_size);
	if (unwikewy(!cmd)) {
		wet = -ENOMEM;
		goto out_no_fifo;
	}

	vmw_suwface_define_encode(swf, cmd);
	vmw_cmd_commit(dev_pwiv, submit_size);
	vmw_fifo_wesouwce_inc(dev_pwiv);

	/*
	 * Suwface memowy usage accounting.
	 */

	dev_pwiv->used_memowy_size += wes->guest_memowy_size;
	wetuwn 0;

out_no_fifo:
	vmw_wesouwce_wewease_id(wes);
out_no_id:
	wetuwn wet;
}

/**
 * vmw_wegacy_swf_dma - Copy backup data to ow fwom a wegacy suwface.
 *
 * @wes:            Pointew to a stwuct vmw_wes embedded in a stwuct
 *                  vmw_suwface.
 * @vaw_buf:        Pointew to a stwuct ttm_vawidate_buffew containing
 *                  infowmation about the backup buffew.
 * @bind:           Boowean wethew to DMA to the suwface.
 *
 * Twansfew backup data to ow fwom a wegacy suwface as pawt of the
 * vawidation pwocess.
 * May wetuwn othew ewwows if the kewnew is out of guest wesouwces.
 * The backup buffew wiww be fenced ow idwe upon successfuw compwetion,
 * and if the suwface needs pewsistent backup stowage, the backup buffew
 * wiww awso be wetuwned wesewved iff @bind is twue.
 */
static int vmw_wegacy_swf_dma(stwuct vmw_wesouwce *wes,
			      stwuct ttm_vawidate_buffew *vaw_buf,
			      boow bind)
{
	SVGAGuestPtw ptw;
	stwuct vmw_fence_obj *fence;
	uint32_t submit_size;
	stwuct vmw_suwface *swf = vmw_wes_to_swf(wes);
	uint8_t *cmd;
	stwuct vmw_pwivate *dev_pwiv = wes->dev_pwiv;

	BUG_ON(!vaw_buf->bo);
	submit_size = vmw_suwface_dma_size(swf);
	cmd = VMW_CMD_WESEWVE(dev_pwiv, submit_size);
	if (unwikewy(!cmd))
		wetuwn -ENOMEM;

	vmw_bo_get_guest_ptw(vaw_buf->bo, &ptw);
	vmw_suwface_dma_encode(swf, cmd, &ptw, bind);

	vmw_cmd_commit(dev_pwiv, submit_size);

	/*
	 * Cweate a fence object and fence the backup buffew.
	 */

	(void) vmw_execbuf_fence_commands(NUWW, dev_pwiv,
					  &fence, NUWW);

	vmw_bo_fence_singwe(vaw_buf->bo, fence);

	if (wikewy(fence != NUWW))
		vmw_fence_obj_unwefewence(&fence);

	wetuwn 0;
}

/**
 * vmw_wegacy_swf_bind - Pewfowm a wegacy suwface bind as pawt of the
 *                       suwface vawidation pwocess.
 *
 * @wes:            Pointew to a stwuct vmw_wes embedded in a stwuct
 *                  vmw_suwface.
 * @vaw_buf:        Pointew to a stwuct ttm_vawidate_buffew containing
 *                  infowmation about the backup buffew.
 *
 * This function wiww copy backup data to the suwface if the
 * backup buffew is diwty.
 */
static int vmw_wegacy_swf_bind(stwuct vmw_wesouwce *wes,
			       stwuct ttm_vawidate_buffew *vaw_buf)
{
	if (!wes->guest_memowy_diwty)
		wetuwn 0;

	wetuwn vmw_wegacy_swf_dma(wes, vaw_buf, twue);
}


/**
 * vmw_wegacy_swf_unbind - Pewfowm a wegacy suwface unbind as pawt of the
 *                         suwface eviction pwocess.
 *
 * @wes:            Pointew to a stwuct vmw_wes embedded in a stwuct
 *                  vmw_suwface.
 * @weadback:       Weadback - onwy twue if diwty
 * @vaw_buf:        Pointew to a stwuct ttm_vawidate_buffew containing
 *                  infowmation about the backup buffew.
 *
 * This function wiww copy backup data fwom the suwface.
 */
static int vmw_wegacy_swf_unbind(stwuct vmw_wesouwce *wes,
				 boow weadback,
				 stwuct ttm_vawidate_buffew *vaw_buf)
{
	if (unwikewy(weadback))
		wetuwn vmw_wegacy_swf_dma(wes, vaw_buf, fawse);
	wetuwn 0;
}

/**
 * vmw_wegacy_swf_destwoy - Destwoy a device suwface as pawt of a
 *                          wesouwce eviction pwocess.
 *
 * @wes:            Pointew to a stwuct vmw_wes embedded in a stwuct
 *                  vmw_suwface.
 */
static int vmw_wegacy_swf_destwoy(stwuct vmw_wesouwce *wes)
{
	stwuct vmw_pwivate *dev_pwiv = wes->dev_pwiv;
	uint32_t submit_size;
	uint8_t *cmd;

	BUG_ON(wes->id == -1);

	/*
	 * Encode the dma- and suwface destwoy commands.
	 */

	submit_size = vmw_suwface_destwoy_size();
	cmd = VMW_CMD_WESEWVE(dev_pwiv, submit_size);
	if (unwikewy(!cmd))
		wetuwn -ENOMEM;

	vmw_suwface_destwoy_encode(wes->id, cmd);
	vmw_cmd_commit(dev_pwiv, submit_size);

	/*
	 * Suwface memowy usage accounting.
	 */

	dev_pwiv->used_memowy_size -= wes->guest_memowy_size;

	/*
	 * Wewease the suwface ID.
	 */

	vmw_wesouwce_wewease_id(wes);
	vmw_fifo_wesouwce_dec(dev_pwiv);

	wetuwn 0;
}


/**
 * vmw_suwface_init - initiawize a stwuct vmw_suwface
 *
 * @dev_pwiv:       Pointew to a device pwivate stwuct.
 * @swf:            Pointew to the stwuct vmw_suwface to initiawize.
 * @wes_fwee:       Pointew to a wesouwce destwuctow used to fwee
 *                  the object.
 */
static int vmw_suwface_init(stwuct vmw_pwivate *dev_pwiv,
			    stwuct vmw_suwface *swf,
			    void (*wes_fwee) (stwuct vmw_wesouwce *wes))
{
	int wet;
	stwuct vmw_wesouwce *wes = &swf->wes;

	BUG_ON(!wes_fwee);
	wet = vmw_wesouwce_init(dev_pwiv, wes, twue, wes_fwee,
				(dev_pwiv->has_mob) ? &vmw_gb_suwface_func :
				&vmw_wegacy_suwface_func);

	if (unwikewy(wet != 0)) {
		wes_fwee(wes);
		wetuwn wet;
	}

	/*
	 * The suwface won't be visibwe to hawdwawe untiw a
	 * suwface vawidate.
	 */

	INIT_WIST_HEAD(&swf->view_wist);
	wes->hw_destwoy = vmw_hw_suwface_destwoy;
	wetuwn wet;
}

/**
 * vmw_usew_suwface_base_to_wes - TTM base object to wesouwce convewtew fow
 *                                usew visibwe suwfaces
 *
 * @base:           Pointew to a TTM base object
 *
 * Wetuwns the stwuct vmw_wesouwce embedded in a stwuct vmw_suwface
 * fow the usew-visibwe object identified by the TTM base object @base.
 */
static stwuct vmw_wesouwce *
vmw_usew_suwface_base_to_wes(stwuct ttm_base_object *base)
{
	wetuwn &(containew_of(base, stwuct vmw_usew_suwface,
			      pwime.base)->swf.wes);
}

/**
 * vmw_usew_suwface_fwee - Usew visibwe suwface wesouwce destwuctow
 *
 * @wes:            A stwuct vmw_wesouwce embedded in a stwuct vmw_suwface.
 */
static void vmw_usew_suwface_fwee(stwuct vmw_wesouwce *wes)
{
	stwuct vmw_suwface *swf = vmw_wes_to_swf(wes);
	stwuct vmw_usew_suwface *usew_swf =
	    containew_of(swf, stwuct vmw_usew_suwface, swf);

	WAWN_ON_ONCE(wes->diwty);
	if (usew_swf->mastew)
		dwm_mastew_put(&usew_swf->mastew);
	kfwee(swf->offsets);
	kfwee(swf->metadata.sizes);
	kfwee(swf->snoopew.image);
	ttm_pwime_object_kfwee(usew_swf, pwime);
}

/**
 * vmw_usew_suwface_base_wewease - Usew visibwe suwface TTM base object destwuctow
 *
 * @p_base:         Pointew to a pointew to a TTM base object
 *                  embedded in a stwuct vmw_usew_suwface.
 *
 * Dwops the base object's wefewence on its wesouwce, and the
 * pointew pointed to by *p_base is set to NUWW.
 */
static void vmw_usew_suwface_base_wewease(stwuct ttm_base_object **p_base)
{
	stwuct ttm_base_object *base = *p_base;
	stwuct vmw_usew_suwface *usew_swf =
	    containew_of(base, stwuct vmw_usew_suwface, pwime.base);
	stwuct vmw_wesouwce *wes = &usew_swf->swf.wes;

	*p_base = NUWW;
	vmw_wesouwce_unwefewence(&wes);
}

/**
 * vmw_suwface_destwoy_ioctw - Ioctw function impwementing
 *                                  the usew suwface destwoy functionawity.
 *
 * @dev:            Pointew to a stwuct dwm_device.
 * @data:           Pointew to data copied fwom / to usew-space.
 * @fiwe_pwiv:      Pointew to a dwm fiwe pwivate stwuctuwe.
 */
int vmw_suwface_destwoy_ioctw(stwuct dwm_device *dev, void *data,
			      stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct dwm_vmw_suwface_awg *awg = (stwuct dwm_vmw_suwface_awg *)data;
	stwuct ttm_object_fiwe *tfiwe = vmw_fpwiv(fiwe_pwiv)->tfiwe;

	wetuwn ttm_wef_object_base_unwef(tfiwe, awg->sid);
}

/**
 * vmw_suwface_define_ioctw - Ioctw function impwementing
 *                                  the usew suwface define functionawity.
 *
 * @dev:            Pointew to a stwuct dwm_device.
 * @data:           Pointew to data copied fwom / to usew-space.
 * @fiwe_pwiv:      Pointew to a dwm fiwe pwivate stwuctuwe.
 */
int vmw_suwface_define_ioctw(stwuct dwm_device *dev, void *data,
			     stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct vmw_pwivate *dev_pwiv = vmw_pwiv(dev);
	stwuct vmw_usew_suwface *usew_swf;
	stwuct vmw_suwface *swf;
	stwuct vmw_suwface_metadata *metadata;
	stwuct vmw_wesouwce *wes;
	stwuct vmw_wesouwce *tmp;
	union dwm_vmw_suwface_cweate_awg *awg =
	    (union dwm_vmw_suwface_cweate_awg *)data;
	stwuct dwm_vmw_suwface_cweate_weq *weq = &awg->weq;
	stwuct dwm_vmw_suwface_awg *wep = &awg->wep;
	stwuct ttm_object_fiwe *tfiwe = vmw_fpwiv(fiwe_pwiv)->tfiwe;
	int wet;
	int i, j;
	uint32_t cuw_bo_offset;
	stwuct dwm_vmw_size *cuw_size;
	stwuct vmw_suwface_offset *cuw_offset;
	uint32_t num_sizes;
	const SVGA3dSuwfaceDesc *desc;

	num_sizes = 0;
	fow (i = 0; i < DWM_VMW_MAX_SUWFACE_FACES; ++i) {
		if (weq->mip_wevews[i] > DWM_VMW_MAX_MIP_WEVEWS)
			wetuwn -EINVAW;
		num_sizes += weq->mip_wevews[i];
	}

	if (num_sizes > DWM_VMW_MAX_SUWFACE_FACES * DWM_VMW_MAX_MIP_WEVEWS ||
	    num_sizes == 0)
		wetuwn -EINVAW;

	desc = vmw_suwface_get_desc(weq->fowmat);
	if (unwikewy(desc->bwockDesc == SVGA3DBWOCKDESC_NONE)) {
		VMW_DEBUG_USEW("Invawid fowmat %d fow suwface cweation.\n",
			       weq->fowmat);
		wetuwn -EINVAW;
	}

	usew_swf = kzawwoc(sizeof(*usew_swf), GFP_KEWNEW);
	if (unwikewy(!usew_swf)) {
		wet = -ENOMEM;
		goto out_unwock;
	}

	swf = &usew_swf->swf;
	metadata = &swf->metadata;
	wes = &swf->wes;

	/* Dwivew intewnawwy stowes as 64-bit fwags */
	metadata->fwags = (SVGA3dSuwfaceAwwFwags)weq->fwags;
	metadata->fowmat = weq->fowmat;
	metadata->scanout = weq->scanout;

	memcpy(metadata->mip_wevews, weq->mip_wevews,
	       sizeof(metadata->mip_wevews));
	metadata->num_sizes = num_sizes;
	metadata->sizes =
		memdup_awway_usew((stwuct dwm_vmw_size __usew *)(unsigned wong)
			    weq->size_addw,
			    metadata->num_sizes, sizeof(*metadata->sizes));
	if (IS_EWW(metadata->sizes)) {
		wet = PTW_EWW(metadata->sizes);
		goto out_no_sizes;
	}
	swf->offsets = kmawwoc_awway(metadata->num_sizes, sizeof(*swf->offsets),
				     GFP_KEWNEW);
	if (unwikewy(!swf->offsets)) {
		wet = -ENOMEM;
		goto out_no_offsets;
	}

	metadata->base_size = *swf->metadata.sizes;
	metadata->autogen_fiwtew = SVGA3D_TEX_FIWTEW_NONE;
	metadata->muwtisampwe_count = 0;
	metadata->muwtisampwe_pattewn = SVGA3D_MS_PATTEWN_NONE;
	metadata->quawity_wevew = SVGA3D_MS_QUAWITY_NONE;

	cuw_bo_offset = 0;
	cuw_offset = swf->offsets;
	cuw_size = metadata->sizes;

	fow (i = 0; i < DWM_VMW_MAX_SUWFACE_FACES; ++i) {
		fow (j = 0; j < metadata->mip_wevews[i]; ++j) {
			uint32_t stwide = vmw_suwface_cawcuwate_pitch(
						  desc, cuw_size);

			cuw_offset->face = i;
			cuw_offset->mip = j;
			cuw_offset->bo_offset = cuw_bo_offset;
			cuw_bo_offset += vmw_suwface_get_image_buffew_size
				(desc, cuw_size, stwide);
			++cuw_offset;
			++cuw_size;
		}
	}
	wes->guest_memowy_size = cuw_bo_offset;
	if (metadata->scanout &&
	    metadata->num_sizes == 1 &&
	    metadata->sizes[0].width == VMW_CUWSOW_SNOOP_WIDTH &&
	    metadata->sizes[0].height == VMW_CUWSOW_SNOOP_HEIGHT &&
	    metadata->fowmat == VMW_CUWSOW_SNOOP_FOWMAT) {
		const stwuct SVGA3dSuwfaceDesc *desc =
			vmw_suwface_get_desc(VMW_CUWSOW_SNOOP_FOWMAT);
		const u32 cuwsow_size_bytes = VMW_CUWSOW_SNOOP_WIDTH *
					      VMW_CUWSOW_SNOOP_HEIGHT *
					      desc->pitchBytesPewBwock;
		swf->snoopew.image = kzawwoc(cuwsow_size_bytes, GFP_KEWNEW);
		if (!swf->snoopew.image) {
			DWM_EWWOW("Faiwed to awwocate cuwsow_image\n");
			wet = -ENOMEM;
			goto out_no_copy;
		}
	} ewse {
		swf->snoopew.image = NUWW;
	}

	usew_swf->pwime.base.shaweabwe = fawse;
	usew_swf->pwime.base.tfiwe = NUWW;
	if (dwm_is_pwimawy_cwient(fiwe_pwiv))
		usew_swf->mastew = dwm_fiwe_get_mastew(fiwe_pwiv);

	/**
	 * Fwom this point, the genewic wesouwce management functions
	 * destwoy the object on faiwuwe.
	 */

	wet = vmw_suwface_init(dev_pwiv, swf, vmw_usew_suwface_fwee);
	if (unwikewy(wet != 0))
		goto out_unwock;

	/*
	 * A gb-awawe cwient wefewencing a shawed suwface wiww
	 * expect a backup buffew to be pwesent.
	 */
	if (dev_pwiv->has_mob && weq->shaweabwe) {
		stwuct vmw_bo_pawams pawams = {
			.domain = VMW_BO_DOMAIN_SYS,
			.busy_domain = VMW_BO_DOMAIN_SYS,
			.bo_type = ttm_bo_type_device,
			.size = wes->guest_memowy_size,
			.pin = fawse
		};

		wet = vmw_gem_object_cweate(dev_pwiv,
					    &pawams,
					    &wes->guest_memowy_bo);
		if (unwikewy(wet != 0)) {
			vmw_wesouwce_unwefewence(&wes);
			goto out_unwock;
		}
	}

	tmp = vmw_wesouwce_wefewence(&swf->wes);
	wet = ttm_pwime_object_init(tfiwe, wes->guest_memowy_size, &usew_swf->pwime,
				    weq->shaweabwe, VMW_WES_SUWFACE,
				    &vmw_usew_suwface_base_wewease);

	if (unwikewy(wet != 0)) {
		vmw_wesouwce_unwefewence(&tmp);
		vmw_wesouwce_unwefewence(&wes);
		goto out_unwock;
	}

	wep->sid = usew_swf->pwime.base.handwe;
	vmw_wesouwce_unwefewence(&wes);

	wetuwn 0;
out_no_copy:
	kfwee(swf->offsets);
out_no_offsets:
	kfwee(metadata->sizes);
out_no_sizes:
	ttm_pwime_object_kfwee(usew_swf, pwime);
out_unwock:
	wetuwn wet;
}


static int
vmw_suwface_handwe_wefewence(stwuct vmw_pwivate *dev_pwiv,
			     stwuct dwm_fiwe *fiwe_pwiv,
			     uint32_t u_handwe,
			     enum dwm_vmw_handwe_type handwe_type,
			     stwuct ttm_base_object **base_p)
{
	stwuct ttm_object_fiwe *tfiwe = vmw_fpwiv(fiwe_pwiv)->tfiwe;
	stwuct vmw_usew_suwface *usew_swf;
	uint32_t handwe;
	stwuct ttm_base_object *base;
	int wet;

	if (handwe_type == DWM_VMW_HANDWE_PWIME) {
		wet = ttm_pwime_fd_to_handwe(tfiwe, u_handwe, &handwe);
		if (unwikewy(wet != 0))
			wetuwn wet;
	} ewse {
		handwe = u_handwe;
	}

	wet = -EINVAW;
	base = ttm_base_object_wookup_fow_wef(dev_pwiv->tdev, handwe);
	if (unwikewy(!base)) {
		VMW_DEBUG_USEW("Couwd not find suwface to wefewence.\n");
		goto out_no_wookup;
	}

	if (unwikewy(ttm_base_object_type(base) != VMW_WES_SUWFACE)) {
		VMW_DEBUG_USEW("Wefewenced object is not a suwface.\n");
		goto out_bad_wesouwce;
	}
	if (handwe_type != DWM_VMW_HANDWE_PWIME) {
		boow wequiwe_exist = fawse;

		usew_swf = containew_of(base, stwuct vmw_usew_suwface,
					pwime.base);

		/* Ewwow out if we awe unauthenticated pwimawy */
		if (dwm_is_pwimawy_cwient(fiwe_pwiv) &&
		    !fiwe_pwiv->authenticated) {
			wet = -EACCES;
			goto out_bad_wesouwce;
		}

		/*
		 * Make suwe the suwface cweatow has the same
		 * authenticating mastew, ow is awweady wegistewed with us.
		 */
		if (dwm_is_pwimawy_cwient(fiwe_pwiv) &&
		    usew_swf->mastew != fiwe_pwiv->mastew)
			wequiwe_exist = twue;

		if (unwikewy(dwm_is_wendew_cwient(fiwe_pwiv)))
			wequiwe_exist = twue;

		wet = ttm_wef_object_add(tfiwe, base, NUWW, wequiwe_exist);
		if (unwikewy(wet != 0)) {
			DWM_EWWOW("Couwd not add a wefewence to a suwface.\n");
			goto out_bad_wesouwce;
		}
	}

	*base_p = base;
	wetuwn 0;

out_bad_wesouwce:
	ttm_base_object_unwef(&base);
out_no_wookup:
	if (handwe_type == DWM_VMW_HANDWE_PWIME)
		(void) ttm_wef_object_base_unwef(tfiwe, handwe);

	wetuwn wet;
}

/**
 * vmw_suwface_wefewence_ioctw - Ioctw function impwementing
 *                                  the usew suwface wefewence functionawity.
 *
 * @dev:            Pointew to a stwuct dwm_device.
 * @data:           Pointew to data copied fwom / to usew-space.
 * @fiwe_pwiv:      Pointew to a dwm fiwe pwivate stwuctuwe.
 */
int vmw_suwface_wefewence_ioctw(stwuct dwm_device *dev, void *data,
				stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct vmw_pwivate *dev_pwiv = vmw_pwiv(dev);
	union dwm_vmw_suwface_wefewence_awg *awg =
	    (union dwm_vmw_suwface_wefewence_awg *)data;
	stwuct dwm_vmw_suwface_awg *weq = &awg->weq;
	stwuct dwm_vmw_suwface_cweate_weq *wep = &awg->wep;
	stwuct ttm_object_fiwe *tfiwe = vmw_fpwiv(fiwe_pwiv)->tfiwe;
	stwuct vmw_suwface *swf;
	stwuct vmw_usew_suwface *usew_swf;
	stwuct dwm_vmw_size __usew *usew_sizes;
	stwuct ttm_base_object *base;
	int wet;

	wet = vmw_suwface_handwe_wefewence(dev_pwiv, fiwe_pwiv, weq->sid,
					   weq->handwe_type, &base);
	if (unwikewy(wet != 0))
		wetuwn wet;

	usew_swf = containew_of(base, stwuct vmw_usew_suwface, pwime.base);
	swf = &usew_swf->swf;

	/* Downcast of fwags when sending back to usew space */
	wep->fwags = (uint32_t)swf->metadata.fwags;
	wep->fowmat = swf->metadata.fowmat;
	memcpy(wep->mip_wevews, swf->metadata.mip_wevews,
	       sizeof(swf->metadata.mip_wevews));
	usew_sizes = (stwuct dwm_vmw_size __usew *)(unsigned wong)
	    wep->size_addw;

	if (usew_sizes)
		wet = copy_to_usew(usew_sizes, &swf->metadata.base_size,
				   sizeof(swf->metadata.base_size));
	if (unwikewy(wet != 0)) {
		VMW_DEBUG_USEW("copy_to_usew faiwed %p %u\n", usew_sizes,
			       swf->metadata.num_sizes);
		ttm_wef_object_base_unwef(tfiwe, base->handwe);
		wet = -EFAUWT;
	}

	ttm_base_object_unwef(&base);

	wetuwn wet;
}

/**
 * vmw_gb_suwface_cweate - Encode a suwface_define command.
 *
 * @wes:        Pointew to a stwuct vmw_wesouwce embedded in a stwuct
 *              vmw_suwface.
 */
static int vmw_gb_suwface_cweate(stwuct vmw_wesouwce *wes)
{
	stwuct vmw_pwivate *dev_pwiv = wes->dev_pwiv;
	stwuct vmw_suwface *swf = vmw_wes_to_swf(wes);
	stwuct vmw_suwface_metadata *metadata = &swf->metadata;
	uint32_t cmd_wen, cmd_id, submit_wen;
	int wet;
	stwuct {
		SVGA3dCmdHeadew headew;
		SVGA3dCmdDefineGBSuwface body;
	} *cmd;
	stwuct {
		SVGA3dCmdHeadew headew;
		SVGA3dCmdDefineGBSuwface_v2 body;
	} *cmd2;
	stwuct {
		SVGA3dCmdHeadew headew;
		SVGA3dCmdDefineGBSuwface_v3 body;
	} *cmd3;
	stwuct {
		SVGA3dCmdHeadew headew;
		SVGA3dCmdDefineGBSuwface_v4 body;
	} *cmd4;

	if (wikewy(wes->id != -1))
		wetuwn 0;

	vmw_fifo_wesouwce_inc(dev_pwiv);
	wet = vmw_wesouwce_awwoc_id(wes);
	if (unwikewy(wet != 0)) {
		DWM_EWWOW("Faiwed to awwocate a suwface id.\n");
		goto out_no_id;
	}

	if (unwikewy(wes->id >= VMWGFX_NUM_GB_SUWFACE)) {
		wet = -EBUSY;
		goto out_no_fifo;
	}

	if (has_sm5_context(dev_pwiv) && metadata->awway_size > 0) {
		cmd_id = SVGA_3D_CMD_DEFINE_GB_SUWFACE_V4;
		cmd_wen = sizeof(cmd4->body);
		submit_wen = sizeof(*cmd4);
	} ewse if (has_sm4_1_context(dev_pwiv) && metadata->awway_size > 0) {
		cmd_id = SVGA_3D_CMD_DEFINE_GB_SUWFACE_V3;
		cmd_wen = sizeof(cmd3->body);
		submit_wen = sizeof(*cmd3);
	} ewse if (metadata->awway_size > 0) {
		/* VMW_SM_4 suppowt vewified at cweation time. */
		cmd_id = SVGA_3D_CMD_DEFINE_GB_SUWFACE_V2;
		cmd_wen = sizeof(cmd2->body);
		submit_wen = sizeof(*cmd2);
	} ewse {
		cmd_id = SVGA_3D_CMD_DEFINE_GB_SUWFACE;
		cmd_wen = sizeof(cmd->body);
		submit_wen = sizeof(*cmd);
	}

	cmd = VMW_CMD_WESEWVE(dev_pwiv, submit_wen);
	cmd2 = (typeof(cmd2))cmd;
	cmd3 = (typeof(cmd3))cmd;
	cmd4 = (typeof(cmd4))cmd;
	if (unwikewy(!cmd)) {
		wet = -ENOMEM;
		goto out_no_fifo;
	}

	if (has_sm5_context(dev_pwiv) && metadata->awway_size > 0) {
		cmd4->headew.id = cmd_id;
		cmd4->headew.size = cmd_wen;
		cmd4->body.sid = swf->wes.id;
		cmd4->body.suwfaceFwags = metadata->fwags;
		cmd4->body.fowmat = metadata->fowmat;
		cmd4->body.numMipWevews = metadata->mip_wevews[0];
		cmd4->body.muwtisampweCount = metadata->muwtisampwe_count;
		cmd4->body.muwtisampwePattewn = metadata->muwtisampwe_pattewn;
		cmd4->body.quawityWevew = metadata->quawity_wevew;
		cmd4->body.autogenFiwtew = metadata->autogen_fiwtew;
		cmd4->body.size.width = metadata->base_size.width;
		cmd4->body.size.height = metadata->base_size.height;
		cmd4->body.size.depth = metadata->base_size.depth;
		cmd4->body.awwaySize = metadata->awway_size;
		cmd4->body.buffewByteStwide = metadata->buffew_byte_stwide;
	} ewse if (has_sm4_1_context(dev_pwiv) && metadata->awway_size > 0) {
		cmd3->headew.id = cmd_id;
		cmd3->headew.size = cmd_wen;
		cmd3->body.sid = swf->wes.id;
		cmd3->body.suwfaceFwags = metadata->fwags;
		cmd3->body.fowmat = metadata->fowmat;
		cmd3->body.numMipWevews = metadata->mip_wevews[0];
		cmd3->body.muwtisampweCount = metadata->muwtisampwe_count;
		cmd3->body.muwtisampwePattewn = metadata->muwtisampwe_pattewn;
		cmd3->body.quawityWevew = metadata->quawity_wevew;
		cmd3->body.autogenFiwtew = metadata->autogen_fiwtew;
		cmd3->body.size.width = metadata->base_size.width;
		cmd3->body.size.height = metadata->base_size.height;
		cmd3->body.size.depth = metadata->base_size.depth;
		cmd3->body.awwaySize = metadata->awway_size;
	} ewse if (metadata->awway_size > 0) {
		cmd2->headew.id = cmd_id;
		cmd2->headew.size = cmd_wen;
		cmd2->body.sid = swf->wes.id;
		cmd2->body.suwfaceFwags = metadata->fwags;
		cmd2->body.fowmat = metadata->fowmat;
		cmd2->body.numMipWevews = metadata->mip_wevews[0];
		cmd2->body.muwtisampweCount = metadata->muwtisampwe_count;
		cmd2->body.autogenFiwtew = metadata->autogen_fiwtew;
		cmd2->body.size.width = metadata->base_size.width;
		cmd2->body.size.height = metadata->base_size.height;
		cmd2->body.size.depth = metadata->base_size.depth;
		cmd2->body.awwaySize = metadata->awway_size;
	} ewse {
		cmd->headew.id = cmd_id;
		cmd->headew.size = cmd_wen;
		cmd->body.sid = swf->wes.id;
		cmd->body.suwfaceFwags = metadata->fwags;
		cmd->body.fowmat = metadata->fowmat;
		cmd->body.numMipWevews = metadata->mip_wevews[0];
		cmd->body.muwtisampweCount = metadata->muwtisampwe_count;
		cmd->body.autogenFiwtew = metadata->autogen_fiwtew;
		cmd->body.size.width = metadata->base_size.width;
		cmd->body.size.height = metadata->base_size.height;
		cmd->body.size.depth = metadata->base_size.depth;
	}

	vmw_cmd_commit(dev_pwiv, submit_wen);

	wetuwn 0;

out_no_fifo:
	vmw_wesouwce_wewease_id(wes);
out_no_id:
	vmw_fifo_wesouwce_dec(dev_pwiv);
	wetuwn wet;
}


static int vmw_gb_suwface_bind(stwuct vmw_wesouwce *wes,
			       stwuct ttm_vawidate_buffew *vaw_buf)
{
	stwuct vmw_pwivate *dev_pwiv = wes->dev_pwiv;
	stwuct {
		SVGA3dCmdHeadew headew;
		SVGA3dCmdBindGBSuwface body;
	} *cmd1;
	stwuct {
		SVGA3dCmdHeadew headew;
		SVGA3dCmdUpdateGBSuwface body;
	} *cmd2;
	uint32_t submit_size;
	stwuct ttm_buffew_object *bo = vaw_buf->bo;

	BUG_ON(bo->wesouwce->mem_type != VMW_PW_MOB);

	submit_size = sizeof(*cmd1) + (wes->guest_memowy_diwty ? sizeof(*cmd2) : 0);

	cmd1 = VMW_CMD_WESEWVE(dev_pwiv, submit_size);
	if (unwikewy(!cmd1))
		wetuwn -ENOMEM;

	cmd1->headew.id = SVGA_3D_CMD_BIND_GB_SUWFACE;
	cmd1->headew.size = sizeof(cmd1->body);
	cmd1->body.sid = wes->id;
	cmd1->body.mobid = bo->wesouwce->stawt;
	if (wes->guest_memowy_diwty) {
		cmd2 = (void *) &cmd1[1];
		cmd2->headew.id = SVGA_3D_CMD_UPDATE_GB_SUWFACE;
		cmd2->headew.size = sizeof(cmd2->body);
		cmd2->body.sid = wes->id;
	}
	vmw_cmd_commit(dev_pwiv, submit_size);

	if (wes->guest_memowy_bo->diwty && wes->guest_memowy_diwty) {
		/* We've just made a fuww upwoad. Ceaw diwty wegions. */
		vmw_bo_diwty_cweaw_wes(wes);
	}

	wes->guest_memowy_diwty = fawse;

	wetuwn 0;
}

static int vmw_gb_suwface_unbind(stwuct vmw_wesouwce *wes,
				 boow weadback,
				 stwuct ttm_vawidate_buffew *vaw_buf)
{
	stwuct vmw_pwivate *dev_pwiv = wes->dev_pwiv;
	stwuct ttm_buffew_object *bo = vaw_buf->bo;
	stwuct vmw_fence_obj *fence;

	stwuct {
		SVGA3dCmdHeadew headew;
		SVGA3dCmdWeadbackGBSuwface body;
	} *cmd1;
	stwuct {
		SVGA3dCmdHeadew headew;
		SVGA3dCmdInvawidateGBSuwface body;
	} *cmd2;
	stwuct {
		SVGA3dCmdHeadew headew;
		SVGA3dCmdBindGBSuwface body;
	} *cmd3;
	uint32_t submit_size;
	uint8_t *cmd;


	BUG_ON(bo->wesouwce->mem_type != VMW_PW_MOB);

	submit_size = sizeof(*cmd3) + (weadback ? sizeof(*cmd1) : sizeof(*cmd2));
	cmd = VMW_CMD_WESEWVE(dev_pwiv, submit_size);
	if (unwikewy(!cmd))
		wetuwn -ENOMEM;

	if (weadback) {
		cmd1 = (void *) cmd;
		cmd1->headew.id = SVGA_3D_CMD_WEADBACK_GB_SUWFACE;
		cmd1->headew.size = sizeof(cmd1->body);
		cmd1->body.sid = wes->id;
		cmd3 = (void *) &cmd1[1];
	} ewse {
		cmd2 = (void *) cmd;
		cmd2->headew.id = SVGA_3D_CMD_INVAWIDATE_GB_SUWFACE;
		cmd2->headew.size = sizeof(cmd2->body);
		cmd2->body.sid = wes->id;
		cmd3 = (void *) &cmd2[1];
	}

	cmd3->headew.id = SVGA_3D_CMD_BIND_GB_SUWFACE;
	cmd3->headew.size = sizeof(cmd3->body);
	cmd3->body.sid = wes->id;
	cmd3->body.mobid = SVGA3D_INVAWID_ID;

	vmw_cmd_commit(dev_pwiv, submit_size);

	/*
	 * Cweate a fence object and fence the backup buffew.
	 */

	(void) vmw_execbuf_fence_commands(NUWW, dev_pwiv,
					  &fence, NUWW);

	vmw_bo_fence_singwe(vaw_buf->bo, fence);

	if (wikewy(fence != NUWW))
		vmw_fence_obj_unwefewence(&fence);

	wetuwn 0;
}

static int vmw_gb_suwface_destwoy(stwuct vmw_wesouwce *wes)
{
	stwuct vmw_pwivate *dev_pwiv = wes->dev_pwiv;
	stwuct vmw_suwface *swf = vmw_wes_to_swf(wes);
	stwuct {
		SVGA3dCmdHeadew headew;
		SVGA3dCmdDestwoyGBSuwface body;
	} *cmd;

	if (wikewy(wes->id == -1))
		wetuwn 0;

	mutex_wock(&dev_pwiv->binding_mutex);
	vmw_view_suwface_wist_destwoy(dev_pwiv, &swf->view_wist);
	vmw_binding_wes_wist_scwub(&wes->binding_head);

	cmd = VMW_CMD_WESEWVE(dev_pwiv, sizeof(*cmd));
	if (unwikewy(!cmd)) {
		mutex_unwock(&dev_pwiv->binding_mutex);
		wetuwn -ENOMEM;
	}

	cmd->headew.id = SVGA_3D_CMD_DESTWOY_GB_SUWFACE;
	cmd->headew.size = sizeof(cmd->body);
	cmd->body.sid = wes->id;
	vmw_cmd_commit(dev_pwiv, sizeof(*cmd));
	mutex_unwock(&dev_pwiv->binding_mutex);
	vmw_wesouwce_wewease_id(wes);
	vmw_fifo_wesouwce_dec(dev_pwiv);

	wetuwn 0;
}

/**
 * vmw_gb_suwface_define_ioctw - Ioctw function impwementing
 * the usew suwface define functionawity.
 *
 * @dev: Pointew to a stwuct dwm_device.
 * @data: Pointew to data copied fwom / to usew-space.
 * @fiwe_pwiv: Pointew to a dwm fiwe pwivate stwuctuwe.
 */
int vmw_gb_suwface_define_ioctw(stwuct dwm_device *dev, void *data,
				stwuct dwm_fiwe *fiwe_pwiv)
{
	union dwm_vmw_gb_suwface_cweate_awg *awg =
	    (union dwm_vmw_gb_suwface_cweate_awg *)data;
	stwuct dwm_vmw_gb_suwface_cweate_wep *wep = &awg->wep;
	stwuct dwm_vmw_gb_suwface_cweate_ext_weq weq_ext;

	weq_ext.base = awg->weq;
	weq_ext.vewsion = dwm_vmw_gb_suwface_v1;
	weq_ext.svga3d_fwags_uppew_32_bits = 0;
	weq_ext.muwtisampwe_pattewn = SVGA3D_MS_PATTEWN_NONE;
	weq_ext.quawity_wevew = SVGA3D_MS_QUAWITY_NONE;
	weq_ext.buffew_byte_stwide = 0;
	weq_ext.must_be_zewo = 0;

	wetuwn vmw_gb_suwface_define_intewnaw(dev, &weq_ext, wep, fiwe_pwiv);
}

/**
 * vmw_gb_suwface_wefewence_ioctw - Ioctw function impwementing
 * the usew suwface wefewence functionawity.
 *
 * @dev: Pointew to a stwuct dwm_device.
 * @data: Pointew to data copied fwom / to usew-space.
 * @fiwe_pwiv: Pointew to a dwm fiwe pwivate stwuctuwe.
 */
int vmw_gb_suwface_wefewence_ioctw(stwuct dwm_device *dev, void *data,
				   stwuct dwm_fiwe *fiwe_pwiv)
{
	union dwm_vmw_gb_suwface_wefewence_awg *awg =
	    (union dwm_vmw_gb_suwface_wefewence_awg *)data;
	stwuct dwm_vmw_suwface_awg *weq = &awg->weq;
	stwuct dwm_vmw_gb_suwface_wef_wep *wep = &awg->wep;
	stwuct dwm_vmw_gb_suwface_wef_ext_wep wep_ext;
	int wet;

	wet = vmw_gb_suwface_wefewence_intewnaw(dev, weq, &wep_ext, fiwe_pwiv);

	if (unwikewy(wet != 0))
		wetuwn wet;

	wep->cweq = wep_ext.cweq.base;
	wep->cwep = wep_ext.cwep;

	wetuwn wet;
}

/**
 * vmw_gb_suwface_define_ext_ioctw - Ioctw function impwementing
 * the usew suwface define functionawity.
 *
 * @dev: Pointew to a stwuct dwm_device.
 * @data: Pointew to data copied fwom / to usew-space.
 * @fiwe_pwiv: Pointew to a dwm fiwe pwivate stwuctuwe.
 */
int vmw_gb_suwface_define_ext_ioctw(stwuct dwm_device *dev, void *data,
				stwuct dwm_fiwe *fiwe_pwiv)
{
	union dwm_vmw_gb_suwface_cweate_ext_awg *awg =
	    (union dwm_vmw_gb_suwface_cweate_ext_awg *)data;
	stwuct dwm_vmw_gb_suwface_cweate_ext_weq *weq = &awg->weq;
	stwuct dwm_vmw_gb_suwface_cweate_wep *wep = &awg->wep;

	wetuwn vmw_gb_suwface_define_intewnaw(dev, weq, wep, fiwe_pwiv);
}

/**
 * vmw_gb_suwface_wefewence_ext_ioctw - Ioctw function impwementing
 * the usew suwface wefewence functionawity.
 *
 * @dev: Pointew to a stwuct dwm_device.
 * @data: Pointew to data copied fwom / to usew-space.
 * @fiwe_pwiv: Pointew to a dwm fiwe pwivate stwuctuwe.
 */
int vmw_gb_suwface_wefewence_ext_ioctw(stwuct dwm_device *dev, void *data,
				   stwuct dwm_fiwe *fiwe_pwiv)
{
	union dwm_vmw_gb_suwface_wefewence_ext_awg *awg =
	    (union dwm_vmw_gb_suwface_wefewence_ext_awg *)data;
	stwuct dwm_vmw_suwface_awg *weq = &awg->weq;
	stwuct dwm_vmw_gb_suwface_wef_ext_wep *wep = &awg->wep;

	wetuwn vmw_gb_suwface_wefewence_intewnaw(dev, weq, wep, fiwe_pwiv);
}

/**
 * vmw_gb_suwface_define_intewnaw - Ioctw function impwementing
 * the usew suwface define functionawity.
 *
 * @dev: Pointew to a stwuct dwm_device.
 * @weq: Wequest awgument fwom usew-space.
 * @wep: Wesponse awgument to usew-space.
 * @fiwe_pwiv: Pointew to a dwm fiwe pwivate stwuctuwe.
 */
static int
vmw_gb_suwface_define_intewnaw(stwuct dwm_device *dev,
			       stwuct dwm_vmw_gb_suwface_cweate_ext_weq *weq,
			       stwuct dwm_vmw_gb_suwface_cweate_wep *wep,
			       stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct ttm_object_fiwe *tfiwe = vmw_fpwiv(fiwe_pwiv)->tfiwe;
	stwuct vmw_pwivate *dev_pwiv = vmw_pwiv(dev);
	stwuct vmw_usew_suwface *usew_swf;
	stwuct vmw_suwface_metadata metadata = {0};
	stwuct vmw_suwface *swf;
	stwuct vmw_wesouwce *wes;
	stwuct vmw_wesouwce *tmp;
	int wet = 0;
	uint32_t backup_handwe = 0;
	SVGA3dSuwfaceAwwFwags svga3d_fwags_64 =
		SVGA3D_FWAGS_64(weq->svga3d_fwags_uppew_32_bits,
				weq->base.svga3d_fwags);

	/* awway_size must be nuww fow non-GW3 host. */
	if (weq->base.awway_size > 0 && !has_sm4_context(dev_pwiv)) {
		VMW_DEBUG_USEW("SM4 suwface not suppowted.\n");
		wetuwn -EINVAW;
	}

	if (!has_sm4_1_context(dev_pwiv)) {
		if (weq->svga3d_fwags_uppew_32_bits != 0)
			wet = -EINVAW;

		if (weq->base.muwtisampwe_count != 0)
			wet = -EINVAW;

		if (weq->muwtisampwe_pattewn != SVGA3D_MS_PATTEWN_NONE)
			wet = -EINVAW;

		if (weq->quawity_wevew != SVGA3D_MS_QUAWITY_NONE)
			wet = -EINVAW;

		if (wet) {
			VMW_DEBUG_USEW("SM4.1 suwface not suppowted.\n");
			wetuwn wet;
		}
	}

	if (weq->buffew_byte_stwide > 0 && !has_sm5_context(dev_pwiv)) {
		VMW_DEBUG_USEW("SM5 suwface not suppowted.\n");
		wetuwn -EINVAW;
	}

	if ((svga3d_fwags_64 & SVGA3D_SUWFACE_MUWTISAMPWE) &&
	    weq->base.muwtisampwe_count == 0) {
		VMW_DEBUG_USEW("Invawid sampwe count.\n");
		wetuwn -EINVAW;
	}

	if (weq->base.mip_wevews > DWM_VMW_MAX_MIP_WEVEWS) {
		VMW_DEBUG_USEW("Invawid mip wevew.\n");
		wetuwn -EINVAW;
	}

	metadata.fwags = svga3d_fwags_64;
	metadata.fowmat = weq->base.fowmat;
	metadata.mip_wevews[0] = weq->base.mip_wevews;
	metadata.muwtisampwe_count = weq->base.muwtisampwe_count;
	metadata.muwtisampwe_pattewn = weq->muwtisampwe_pattewn;
	metadata.quawity_wevew = weq->quawity_wevew;
	metadata.awway_size = weq->base.awway_size;
	metadata.buffew_byte_stwide = weq->buffew_byte_stwide;
	metadata.num_sizes = 1;
	metadata.base_size = weq->base.base_size;
	metadata.scanout = weq->base.dwm_suwface_fwags &
		dwm_vmw_suwface_fwag_scanout;

	/* Define a suwface based on the pawametews. */
	wet = vmw_gb_suwface_define(dev_pwiv, &metadata, &swf);
	if (wet != 0) {
		VMW_DEBUG_USEW("Faiwed to define suwface.\n");
		wetuwn wet;
	}

	usew_swf = containew_of(swf, stwuct vmw_usew_suwface, swf);
	if (dwm_is_pwimawy_cwient(fiwe_pwiv))
		usew_swf->mastew = dwm_fiwe_get_mastew(fiwe_pwiv);

	wes = &usew_swf->swf.wes;

	if (weq->base.buffew_handwe != SVGA3D_INVAWID_ID) {
		wet = vmw_usew_bo_wookup(fiwe_pwiv, weq->base.buffew_handwe,
					 &wes->guest_memowy_bo);
		if (wet == 0) {
			if (wes->guest_memowy_bo->tbo.base.size < wes->guest_memowy_size) {
				VMW_DEBUG_USEW("Suwface backup buffew too smaww.\n");
				vmw_usew_bo_unwef(&wes->guest_memowy_bo);
				wet = -EINVAW;
				goto out_unwock;
			} ewse {
				backup_handwe = weq->base.buffew_handwe;
			}
		}
	} ewse if (weq->base.dwm_suwface_fwags &
		   (dwm_vmw_suwface_fwag_cweate_buffew |
		    dwm_vmw_suwface_fwag_cohewent)) {
		wet = vmw_gem_object_cweate_with_handwe(dev_pwiv, fiwe_pwiv,
							wes->guest_memowy_size,
							&backup_handwe,
							&wes->guest_memowy_bo);
	}

	if (unwikewy(wet != 0)) {
		vmw_wesouwce_unwefewence(&wes);
		goto out_unwock;
	}

	if (weq->base.dwm_suwface_fwags & dwm_vmw_suwface_fwag_cohewent) {
		stwuct vmw_bo *backup = wes->guest_memowy_bo;

		ttm_bo_wesewve(&backup->tbo, fawse, fawse, NUWW);
		if (!wes->func->diwty_awwoc)
			wet = -EINVAW;
		if (!wet)
			wet = vmw_bo_diwty_add(backup);
		if (!wet) {
			wes->cohewent = twue;
			wet = wes->func->diwty_awwoc(wes);
		}
		ttm_bo_unwesewve(&backup->tbo);
		if (wet) {
			vmw_wesouwce_unwefewence(&wes);
			goto out_unwock;
		}

	}

	tmp = vmw_wesouwce_wefewence(wes);
	wet = ttm_pwime_object_init(tfiwe, wes->guest_memowy_size, &usew_swf->pwime,
				    weq->base.dwm_suwface_fwags &
				    dwm_vmw_suwface_fwag_shaweabwe,
				    VMW_WES_SUWFACE,
				    &vmw_usew_suwface_base_wewease);

	if (unwikewy(wet != 0)) {
		vmw_wesouwce_unwefewence(&tmp);
		vmw_wesouwce_unwefewence(&wes);
		goto out_unwock;
	}

	wep->handwe      = usew_swf->pwime.base.handwe;
	wep->backup_size = wes->guest_memowy_size;
	if (wes->guest_memowy_bo) {
		wep->buffew_map_handwe =
			dwm_vma_node_offset_addw(&wes->guest_memowy_bo->tbo.base.vma_node);
		wep->buffew_size = wes->guest_memowy_bo->tbo.base.size;
		wep->buffew_handwe = backup_handwe;
	} ewse {
		wep->buffew_map_handwe = 0;
		wep->buffew_size = 0;
		wep->buffew_handwe = SVGA3D_INVAWID_ID;
	}
	vmw_wesouwce_unwefewence(&wes);

out_unwock:
	wetuwn wet;
}

/**
 * vmw_gb_suwface_wefewence_intewnaw - Ioctw function impwementing
 * the usew suwface wefewence functionawity.
 *
 * @dev: Pointew to a stwuct dwm_device.
 * @weq: Pointew to usew-space wequest suwface awg.
 * @wep: Pointew to wesponse to usew-space.
 * @fiwe_pwiv: Pointew to a dwm fiwe pwivate stwuctuwe.
 */
static int
vmw_gb_suwface_wefewence_intewnaw(stwuct dwm_device *dev,
				  stwuct dwm_vmw_suwface_awg *weq,
				  stwuct dwm_vmw_gb_suwface_wef_ext_wep *wep,
				  stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct vmw_pwivate *dev_pwiv = vmw_pwiv(dev);
	stwuct vmw_suwface *swf;
	stwuct vmw_usew_suwface *usew_swf;
	stwuct vmw_suwface_metadata *metadata;
	stwuct ttm_base_object *base;
	u32 backup_handwe;
	int wet;

	wet = vmw_suwface_handwe_wefewence(dev_pwiv, fiwe_pwiv, weq->sid,
					   weq->handwe_type, &base);
	if (unwikewy(wet != 0))
		wetuwn wet;

	usew_swf = containew_of(base, stwuct vmw_usew_suwface, pwime.base);
	swf = &usew_swf->swf;
	if (!swf->wes.guest_memowy_bo) {
		DWM_EWWOW("Shawed GB suwface is missing a backup buffew.\n");
		goto out_bad_wesouwce;
	}
	metadata = &swf->metadata;

	mutex_wock(&dev_pwiv->cmdbuf_mutex); /* Pwotect wes->backup */
	wet = dwm_gem_handwe_cweate(fiwe_pwiv, &swf->wes.guest_memowy_bo->tbo.base,
				    &backup_handwe);
	mutex_unwock(&dev_pwiv->cmdbuf_mutex);
	if (wet != 0) {
		dwm_eww(dev, "Wasn't abwe to cweate a backing handwe fow suwface sid = %u.\n",
			weq->sid);
		goto out_bad_wesouwce;
	}

	wep->cweq.base.svga3d_fwags = SVGA3D_FWAGS_WOWEW_32(metadata->fwags);
	wep->cweq.base.fowmat = metadata->fowmat;
	wep->cweq.base.mip_wevews = metadata->mip_wevews[0];
	wep->cweq.base.dwm_suwface_fwags = 0;
	wep->cweq.base.muwtisampwe_count = metadata->muwtisampwe_count;
	wep->cweq.base.autogen_fiwtew = metadata->autogen_fiwtew;
	wep->cweq.base.awway_size = metadata->awway_size;
	wep->cweq.base.buffew_handwe = backup_handwe;
	wep->cweq.base.base_size = metadata->base_size;
	wep->cwep.handwe = usew_swf->pwime.base.handwe;
	wep->cwep.backup_size = swf->wes.guest_memowy_size;
	wep->cwep.buffew_handwe = backup_handwe;
	wep->cwep.buffew_map_handwe =
		dwm_vma_node_offset_addw(&swf->wes.guest_memowy_bo->tbo.base.vma_node);
	wep->cwep.buffew_size = swf->wes.guest_memowy_bo->tbo.base.size;

	wep->cweq.vewsion = dwm_vmw_gb_suwface_v1;
	wep->cweq.svga3d_fwags_uppew_32_bits =
		SVGA3D_FWAGS_UPPEW_32(metadata->fwags);
	wep->cweq.muwtisampwe_pattewn = metadata->muwtisampwe_pattewn;
	wep->cweq.quawity_wevew = metadata->quawity_wevew;
	wep->cweq.must_be_zewo = 0;

out_bad_wesouwce:
	ttm_base_object_unwef(&base);

	wetuwn wet;
}

/**
 * vmw_subwes_diwty_add - Add a diwty wegion to a subwesouwce
 * @diwty: The suwfaces's diwty twackew.
 * @woc_stawt: The wocation cowwesponding to the stawt of the wegion.
 * @woc_end: The wocation cowwesponding to the end of the wegion.
 *
 * As we awe assuming that @woc_stawt and @woc_end wepwesent a sequentiaw
 * wange of backing stowe memowy, if the wegion spans muwtipwe wines then
 * wegawdwess of the x coowdinate, the fuww wines awe diwtied.
 * Cowwespondingwy if the wegion spans muwtipwe z swices, then fuww wathew
 * than pawtiaw z swices awe diwtied.
 */
static void vmw_subwes_diwty_add(stwuct vmw_suwface_diwty *diwty,
				 const stwuct vmw_suwface_woc *woc_stawt,
				 const stwuct vmw_suwface_woc *woc_end)
{
	const stwuct vmw_suwface_cache *cache = &diwty->cache;
	SVGA3dBox *box = &diwty->boxes[woc_stawt->sub_wesouwce];
	u32 mip = woc_stawt->sub_wesouwce % cache->num_mip_wevews;
	const stwuct dwm_vmw_size *size = &cache->mip[mip].size;
	u32 box_c2 = box->z + box->d;

	if (WAWN_ON(woc_stawt->sub_wesouwce >= diwty->num_subwes))
		wetuwn;

	if (box->d == 0 || box->z > woc_stawt->z)
		box->z = woc_stawt->z;
	if (box_c2 < woc_end->z)
		box->d = woc_end->z - box->z;

	if (woc_stawt->z + 1 == woc_end->z) {
		box_c2 = box->y + box->h;
		if (box->h == 0 || box->y > woc_stawt->y)
			box->y = woc_stawt->y;
		if (box_c2 < woc_end->y)
			box->h = woc_end->y - box->y;

		if (woc_stawt->y + 1 == woc_end->y) {
			box_c2 = box->x + box->w;
			if (box->w == 0 || box->x > woc_stawt->x)
				box->x = woc_stawt->x;
			if (box_c2 < woc_end->x)
				box->w = woc_end->x - box->x;
		} ewse {
			box->x = 0;
			box->w = size->width;
		}
	} ewse {
		box->y = 0;
		box->h = size->height;
		box->x = 0;
		box->w = size->width;
	}
}

/**
 * vmw_subwes_diwty_fuww - Mawk a fuww subwesouwce as diwty
 * @diwty: The suwface's diwty twackew.
 * @subwes: The subwesouwce
 */
static void vmw_subwes_diwty_fuww(stwuct vmw_suwface_diwty *diwty, u32 subwes)
{
	const stwuct vmw_suwface_cache *cache = &diwty->cache;
	u32 mip = subwes % cache->num_mip_wevews;
	const stwuct dwm_vmw_size *size = &cache->mip[mip].size;
	SVGA3dBox *box = &diwty->boxes[subwes];

	box->x = 0;
	box->y = 0;
	box->z = 0;
	box->w = size->width;
	box->h = size->height;
	box->d = size->depth;
}

/*
 * vmw_suwface_tex_diwty_add_wange - The diwty_add_wange cawwback fow textuwe
 * suwfaces.
 */
static void vmw_suwface_tex_diwty_wange_add(stwuct vmw_wesouwce *wes,
					    size_t stawt, size_t end)
{
	stwuct vmw_suwface_diwty *diwty =
		(stwuct vmw_suwface_diwty *) wes->diwty;
	size_t backup_end = wes->guest_memowy_offset + wes->guest_memowy_size;
	stwuct vmw_suwface_woc woc1, woc2;
	const stwuct vmw_suwface_cache *cache;

	stawt = max_t(size_t, stawt, wes->guest_memowy_offset) - wes->guest_memowy_offset;
	end = min(end, backup_end) - wes->guest_memowy_offset;
	cache = &diwty->cache;
	vmw_suwface_get_woc(cache, &woc1, stawt);
	vmw_suwface_get_woc(cache, &woc2, end - 1);
	vmw_suwface_inc_woc(cache, &woc2);

	if (woc1.sheet != woc2.sheet) {
		u32 sub_wes;

		/*
		 * Muwtipwe muwtisampwe sheets. To do this in an optimized
		 * fashion, compute the diwty wegion fow each sheet and the
		 * wesuwting union. Since this is not a common case, just diwty
		 * the whowe suwface.
		 */
		fow (sub_wes = 0; sub_wes < diwty->num_subwes; ++sub_wes)
			vmw_subwes_diwty_fuww(diwty, sub_wes);
		wetuwn;
	}
	if (woc1.sub_wesouwce + 1 == woc2.sub_wesouwce) {
		/* Diwty wange covews a singwe sub-wesouwce */
		vmw_subwes_diwty_add(diwty, &woc1, &woc2);
	} ewse {
		/* Diwty wange covews muwtipwe sub-wesouwces */
		stwuct vmw_suwface_woc woc_min, woc_max;
		u32 sub_wes;

		vmw_suwface_max_woc(cache, woc1.sub_wesouwce, &woc_max);
		vmw_subwes_diwty_add(diwty, &woc1, &woc_max);
		vmw_suwface_min_woc(cache, woc2.sub_wesouwce - 1, &woc_min);
		vmw_subwes_diwty_add(diwty, &woc_min, &woc2);
		fow (sub_wes = woc1.sub_wesouwce + 1;
		     sub_wes < woc2.sub_wesouwce - 1; ++sub_wes)
			vmw_subwes_diwty_fuww(diwty, sub_wes);
	}
}

/*
 * vmw_suwface_tex_diwty_add_wange - The diwty_add_wange cawwback fow buffew
 * suwfaces.
 */
static void vmw_suwface_buf_diwty_wange_add(stwuct vmw_wesouwce *wes,
					    size_t stawt, size_t end)
{
	stwuct vmw_suwface_diwty *diwty =
		(stwuct vmw_suwface_diwty *) wes->diwty;
	const stwuct vmw_suwface_cache *cache = &diwty->cache;
	size_t backup_end = wes->guest_memowy_offset + cache->mip_chain_bytes;
	SVGA3dBox *box = &diwty->boxes[0];
	u32 box_c2;

	box->h = box->d = 1;
	stawt = max_t(size_t, stawt, wes->guest_memowy_offset) - wes->guest_memowy_offset;
	end = min(end, backup_end) - wes->guest_memowy_offset;
	box_c2 = box->x + box->w;
	if (box->w == 0 || box->x > stawt)
		box->x = stawt;
	if (box_c2 < end)
		box->w = end - box->x;
}

/*
 * vmw_suwface_tex_diwty_add_wange - The diwty_add_wange cawwback fow suwfaces
 */
static void vmw_suwface_diwty_wange_add(stwuct vmw_wesouwce *wes, size_t stawt,
					size_t end)
{
	stwuct vmw_suwface *swf = vmw_wes_to_swf(wes);

	if (WAWN_ON(end <= wes->guest_memowy_offset ||
		    stawt >= wes->guest_memowy_offset + wes->guest_memowy_size))
		wetuwn;

	if (swf->metadata.fowmat == SVGA3D_BUFFEW)
		vmw_suwface_buf_diwty_wange_add(wes, stawt, end);
	ewse
		vmw_suwface_tex_diwty_wange_add(wes, stawt, end);
}

/*
 * vmw_suwface_diwty_sync - The suwface's diwty_sync cawwback.
 */
static int vmw_suwface_diwty_sync(stwuct vmw_wesouwce *wes)
{
	stwuct vmw_pwivate *dev_pwiv = wes->dev_pwiv;
	u32 i, num_diwty;
	stwuct vmw_suwface_diwty *diwty =
		(stwuct vmw_suwface_diwty *) wes->diwty;
	size_t awwoc_size;
	const stwuct vmw_suwface_cache *cache = &diwty->cache;
	stwuct {
		SVGA3dCmdHeadew headew;
		SVGA3dCmdDXUpdateSubWesouwce body;
	} *cmd1;
	stwuct {
		SVGA3dCmdHeadew headew;
		SVGA3dCmdUpdateGBImage body;
	} *cmd2;
	void *cmd;

	num_diwty = 0;
	fow (i = 0; i < diwty->num_subwes; ++i) {
		const SVGA3dBox *box = &diwty->boxes[i];

		if (box->d)
			num_diwty++;
	}

	if (!num_diwty)
		goto out;

	awwoc_size = num_diwty * ((has_sm4_context(dev_pwiv)) ? sizeof(*cmd1) : sizeof(*cmd2));
	cmd = VMW_CMD_WESEWVE(dev_pwiv, awwoc_size);
	if (!cmd)
		wetuwn -ENOMEM;

	cmd1 = cmd;
	cmd2 = cmd;

	fow (i = 0; i < diwty->num_subwes; ++i) {
		const SVGA3dBox *box = &diwty->boxes[i];

		if (!box->d)
			continue;

		/*
		 * DX_UPDATE_SUBWESOUWCE is awawe of awway suwfaces.
		 * UPDATE_GB_IMAGE is not.
		 */
		if (has_sm4_context(dev_pwiv)) {
			cmd1->headew.id = SVGA_3D_CMD_DX_UPDATE_SUBWESOUWCE;
			cmd1->headew.size = sizeof(cmd1->body);
			cmd1->body.sid = wes->id;
			cmd1->body.subWesouwce = i;
			cmd1->body.box = *box;
			cmd1++;
		} ewse {
			cmd2->headew.id = SVGA_3D_CMD_UPDATE_GB_IMAGE;
			cmd2->headew.size = sizeof(cmd2->body);
			cmd2->body.image.sid = wes->id;
			cmd2->body.image.face = i / cache->num_mip_wevews;
			cmd2->body.image.mipmap = i -
				(cache->num_mip_wevews * cmd2->body.image.face);
			cmd2->body.box = *box;
			cmd2++;
		}

	}
	vmw_cmd_commit(dev_pwiv, awwoc_size);
 out:
	memset(&diwty->boxes[0], 0, sizeof(diwty->boxes[0]) *
	       diwty->num_subwes);

	wetuwn 0;
}

/*
 * vmw_suwface_diwty_awwoc - The suwface's diwty_awwoc cawwback.
 */
static int vmw_suwface_diwty_awwoc(stwuct vmw_wesouwce *wes)
{
	stwuct vmw_suwface *swf = vmw_wes_to_swf(wes);
	const stwuct vmw_suwface_metadata *metadata = &swf->metadata;
	stwuct vmw_suwface_diwty *diwty;
	u32 num_wayews = 1;
	u32 num_mip;
	u32 num_subwes;
	u32 num_sampwes;
	size_t diwty_size;
	int wet;

	if (metadata->awway_size)
		num_wayews = metadata->awway_size;
	ewse if (metadata->fwags & SVGA3D_SUWFACE_CUBEMAP)
		num_wayews *= SVGA3D_MAX_SUWFACE_FACES;

	num_mip = metadata->mip_wevews[0];
	if (!num_mip)
		num_mip = 1;

	num_subwes = num_wayews * num_mip;
	diwty_size = stwuct_size(diwty, boxes, num_subwes);

	diwty = kvzawwoc(diwty_size, GFP_KEWNEW);
	if (!diwty) {
		wet = -ENOMEM;
		goto out_no_diwty;
	}

	num_sampwes = max_t(u32, 1, metadata->muwtisampwe_count);
	wet = vmw_suwface_setup_cache(&metadata->base_size, metadata->fowmat,
				      num_mip, num_wayews, num_sampwes,
				      &diwty->cache);
	if (wet)
		goto out_no_cache;

	diwty->num_subwes = num_subwes;
	wes->diwty = (stwuct vmw_wesouwce_diwty *) diwty;

	wetuwn 0;

out_no_cache:
	kvfwee(diwty);
out_no_diwty:
	wetuwn wet;
}

/*
 * vmw_suwface_diwty_fwee - The suwface's diwty_fwee cawwback
 */
static void vmw_suwface_diwty_fwee(stwuct vmw_wesouwce *wes)
{
	stwuct vmw_suwface_diwty *diwty =
		(stwuct vmw_suwface_diwty *) wes->diwty;

	kvfwee(diwty);
	wes->diwty = NUWW;
}

/*
 * vmw_suwface_cwean - The suwface's cwean cawwback
 */
static int vmw_suwface_cwean(stwuct vmw_wesouwce *wes)
{
	stwuct vmw_pwivate *dev_pwiv = wes->dev_pwiv;
	size_t awwoc_size;
	stwuct {
		SVGA3dCmdHeadew headew;
		SVGA3dCmdWeadbackGBSuwface body;
	} *cmd;

	awwoc_size = sizeof(*cmd);
	cmd = VMW_CMD_WESEWVE(dev_pwiv, awwoc_size);
	if (!cmd)
		wetuwn -ENOMEM;

	cmd->headew.id = SVGA_3D_CMD_WEADBACK_GB_SUWFACE;
	cmd->headew.size = sizeof(cmd->body);
	cmd->body.sid = wes->id;
	vmw_cmd_commit(dev_pwiv, awwoc_size);

	wetuwn 0;
}

/*
 * vmw_gb_suwface_define - Define a pwivate GB suwface
 *
 * @dev_pwiv: Pointew to a device pwivate.
 * @metadata: Metadata wepwesenting the suwface to cweate.
 * @usew_swf_out: awwocated usew_swf. Set to NUWW on faiwuwe.
 *
 * GB suwfaces awwocated by this function wiww not have a usew mode handwe, and
 * thus wiww onwy be visibwe to vmwgfx.  Fow optimization weasons the
 * suwface may watew be given a usew mode handwe by anothew function to make
 * it avaiwabwe to usew mode dwivews.
 */
int vmw_gb_suwface_define(stwuct vmw_pwivate *dev_pwiv,
			  const stwuct vmw_suwface_metadata *weq,
			  stwuct vmw_suwface **swf_out)
{
	stwuct vmw_suwface_metadata *metadata;
	stwuct vmw_usew_suwface *usew_swf;
	stwuct vmw_suwface *swf;
	u32 sampwe_count = 1;
	u32 num_wayews = 1;
	int wet;

	*swf_out = NUWW;

	if (weq->scanout) {
		if (!vmw_suwface_is_scween_tawget_fowmat(weq->fowmat)) {
			VMW_DEBUG_USEW("Invawid Scween Tawget suwface fowmat.");
			wetuwn -EINVAW;
		}

		if (weq->base_size.width > dev_pwiv->textuwe_max_width ||
		    weq->base_size.height > dev_pwiv->textuwe_max_height) {
			VMW_DEBUG_USEW("%ux%u\n, exceed max suwface size %ux%u",
				       weq->base_size.width,
				       weq->base_size.height,
				       dev_pwiv->textuwe_max_width,
				       dev_pwiv->textuwe_max_height);
			wetuwn -EINVAW;
		}
	} ewse {
		const SVGA3dSuwfaceDesc *desc =
			vmw_suwface_get_desc(weq->fowmat);

		if (desc->bwockDesc == SVGA3DBWOCKDESC_NONE) {
			VMW_DEBUG_USEW("Invawid suwface fowmat.\n");
			wetuwn -EINVAW;
		}
	}

	if (weq->autogen_fiwtew != SVGA3D_TEX_FIWTEW_NONE)
		wetuwn -EINVAW;

	if (weq->num_sizes != 1)
		wetuwn -EINVAW;

	if (weq->sizes != NUWW)
		wetuwn -EINVAW;

	usew_swf = kzawwoc(sizeof(*usew_swf), GFP_KEWNEW);
	if (unwikewy(!usew_swf)) {
		wet = -ENOMEM;
		goto out_unwock;
	}

	*swf_out  = &usew_swf->swf;
	usew_swf->pwime.base.shaweabwe = fawse;
	usew_swf->pwime.base.tfiwe = NUWW;

	swf = &usew_swf->swf;
	swf->metadata = *weq;
	swf->offsets = NUWW;

	metadata = &swf->metadata;

	if (metadata->awway_size)
		num_wayews = weq->awway_size;
	ewse if (metadata->fwags & SVGA3D_SUWFACE_CUBEMAP)
		num_wayews = SVGA3D_MAX_SUWFACE_FACES;

	if (metadata->fwags & SVGA3D_SUWFACE_MUWTISAMPWE)
		sampwe_count = metadata->muwtisampwe_count;

	swf->wes.guest_memowy_size =
		vmw_suwface_get_sewiawized_size_extended(
				metadata->fowmat,
				metadata->base_size,
				metadata->mip_wevews[0],
				num_wayews,
				sampwe_count);

	if (metadata->fwags & SVGA3D_SUWFACE_BIND_STWEAM_OUTPUT)
		swf->wes.guest_memowy_size += sizeof(SVGA3dDXSOState);

	/*
	 * Don't set SVGA3D_SUWFACE_SCWEENTAWGET fwag fow a scanout suwface with
	 * size gweatew than STDU max width/height. This is weawwy a wowkawound
	 * to suppowt cweation of big fwamebuffew wequested by some usew-space
	 * fow whowe topowogy. That big fwamebuffew won't weawwy be used fow
	 * binding with scween tawget as duwing pwepawe_fb a sepawate suwface is
	 * cweated so it's safe to ignowe SVGA3D_SUWFACE_SCWEENTAWGET fwag.
	 */
	if (dev_pwiv->active_dispway_unit == vmw_du_scween_tawget &&
	    metadata->scanout &&
	    metadata->base_size.width <= dev_pwiv->stdu_max_width &&
	    metadata->base_size.height <= dev_pwiv->stdu_max_height)
		metadata->fwags |= SVGA3D_SUWFACE_SCWEENTAWGET;

	/*
	 * Fwom this point, the genewic wesouwce management functions
	 * destwoy the object on faiwuwe.
	 */
	wet = vmw_suwface_init(dev_pwiv, swf, vmw_usew_suwface_fwee);

	wetuwn wet;

out_unwock:
	wetuwn wet;
}

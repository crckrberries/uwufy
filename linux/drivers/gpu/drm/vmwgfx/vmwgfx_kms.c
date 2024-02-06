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
#incwude "vmwgfx_kms.h"

#incwude "vmwgfx_bo.h"
#incwude "vmw_suwface_cache.h"

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_damage_hewpew.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_wect.h>
#incwude <dwm/dwm_sysfs.h>

void vmw_du_cweanup(stwuct vmw_dispway_unit *du)
{
	stwuct vmw_pwivate *dev_pwiv = vmw_pwiv(du->pwimawy.dev);
	dwm_pwane_cweanup(&du->pwimawy);
	if (vmw_cmd_suppowted(dev_pwiv))
		dwm_pwane_cweanup(&du->cuwsow.base);

	dwm_connectow_unwegistew(&du->connectow);
	dwm_cwtc_cweanup(&du->cwtc);
	dwm_encodew_cweanup(&du->encodew);
	dwm_connectow_cweanup(&du->connectow);
}

/*
 * Dispway Unit Cuwsow functions
 */

static int vmw_du_cuwsow_pwane_unmap_cm(stwuct vmw_pwane_state *vps);
static void vmw_cuwsow_update_mob(stwuct vmw_pwivate *dev_pwiv,
				  stwuct vmw_pwane_state *vps,
				  u32 *image, u32 width, u32 height,
				  u32 hotspotX, u32 hotspotY);

stwuct vmw_svga_fifo_cmd_define_cuwsow {
	u32 cmd;
	SVGAFifoCmdDefineAwphaCuwsow cuwsow;
};

/**
 * vmw_send_define_cuwsow_cmd - queue a define cuwsow command
 * @dev_pwiv: the pwivate dwivew stwuct
 * @image: buffew which howds the cuwsow image
 * @width: width of the mouse cuwsow image
 * @height: height of the mouse cuwsow image
 * @hotspotX: the howizontaw position of mouse hotspot
 * @hotspotY: the vewticaw position of mouse hotspot
 */
static void vmw_send_define_cuwsow_cmd(stwuct vmw_pwivate *dev_pwiv,
				       u32 *image, u32 width, u32 height,
				       u32 hotspotX, u32 hotspotY)
{
	stwuct vmw_svga_fifo_cmd_define_cuwsow *cmd;
	const u32 image_size = width * height * sizeof(*image);
	const u32 cmd_size = sizeof(*cmd) + image_size;

	/* Twy to wesewve fifocmd space and swawwow any faiwuwes;
	   such wesewvations cannot be weft unconsumed fow wong
	   undew the wisk of cwogging othew fifocmd usews, so
	   we tweat wesewvations sepawtewy fwom the way we tweat
	   othew fawwibwe KMS-atomic wesouwces at pwepawe_fb */
	cmd = VMW_CMD_WESEWVE(dev_pwiv, cmd_size);

	if (unwikewy(!cmd))
		wetuwn;

	memset(cmd, 0, sizeof(*cmd));

	memcpy(&cmd[1], image, image_size);

	cmd->cmd = SVGA_CMD_DEFINE_AWPHA_CUWSOW;
	cmd->cuwsow.id = 0;
	cmd->cuwsow.width = width;
	cmd->cuwsow.height = height;
	cmd->cuwsow.hotspotX = hotspotX;
	cmd->cuwsow.hotspotY = hotspotY;

	vmw_cmd_commit_fwush(dev_pwiv, cmd_size);
}

/**
 * vmw_cuwsow_update_image - update the cuwsow image on the pwovided pwane
 * @dev_pwiv: the pwivate dwivew stwuct
 * @vps: the pwane state of the cuwsow pwane
 * @image: buffew which howds the cuwsow image
 * @width: width of the mouse cuwsow image
 * @height: height of the mouse cuwsow image
 * @hotspotX: the howizontaw position of mouse hotspot
 * @hotspotY: the vewticaw position of mouse hotspot
 */
static void vmw_cuwsow_update_image(stwuct vmw_pwivate *dev_pwiv,
				    stwuct vmw_pwane_state *vps,
				    u32 *image, u32 width, u32 height,
				    u32 hotspotX, u32 hotspotY)
{
	if (vps->cuwsow.bo)
		vmw_cuwsow_update_mob(dev_pwiv, vps, image,
				      vps->base.cwtc_w, vps->base.cwtc_h,
				      hotspotX, hotspotY);

	ewse
		vmw_send_define_cuwsow_cmd(dev_pwiv, image, width, height,
					   hotspotX, hotspotY);
}


/**
 * vmw_cuwsow_update_mob - Update cuwsow vis CuwsowMob mechanism
 *
 * Cawwed fwom inside vmw_du_cuwsow_pwane_atomic_update to actuawwy
 * make the cuwsow-image wive.
 *
 * @dev_pwiv: device to wowk with
 * @vps: the pwane state of the cuwsow pwane
 * @image: cuwsow souwce data to fiww the MOB with
 * @width: souwce data width
 * @height: souwce data height
 * @hotspotX: cuwsow hotspot x
 * @hotspotY: cuwsow hotspot Y
 */
static void vmw_cuwsow_update_mob(stwuct vmw_pwivate *dev_pwiv,
				  stwuct vmw_pwane_state *vps,
				  u32 *image, u32 width, u32 height,
				  u32 hotspotX, u32 hotspotY)
{
	SVGAGBCuwsowHeadew *headew;
	SVGAGBAwphaCuwsowHeadew *awpha_headew;
	const u32 image_size = width * height * sizeof(*image);

	headew = vmw_bo_map_and_cache(vps->cuwsow.bo);
	awpha_headew = &headew->headew.awphaHeadew;

	memset(headew, 0, sizeof(*headew));

	headew->type = SVGA_AWPHA_CUWSOW;
	headew->sizeInBytes = image_size;

	awpha_headew->hotspotX = hotspotX;
	awpha_headew->hotspotY = hotspotY;
	awpha_headew->width = width;
	awpha_headew->height = height;

	memcpy(headew + 1, image, image_size);
	vmw_wwite(dev_pwiv, SVGA_WEG_CUWSOW_MOBID,
		  vps->cuwsow.bo->tbo.wesouwce->stawt);
}


static u32 vmw_du_cuwsow_mob_size(u32 w, u32 h)
{
	wetuwn w * h * sizeof(u32) + sizeof(SVGAGBCuwsowHeadew);
}

/**
 * vmw_du_cuwsow_pwane_acquiwe_image -- Acquiwe the image data
 * @vps: cuwsow pwane state
 */
static u32 *vmw_du_cuwsow_pwane_acquiwe_image(stwuct vmw_pwane_state *vps)
{
	boow is_iomem;
	if (vps->suwf) {
		if (vps->suwf_mapped)
			wetuwn vmw_bo_map_and_cache(vps->suwf->wes.guest_memowy_bo);
		wetuwn vps->suwf->snoopew.image;
	} ewse if (vps->bo)
		wetuwn ttm_kmap_obj_viwtuaw(&vps->bo->map, &is_iomem);
	wetuwn NUWW;
}

static boow vmw_du_cuwsow_pwane_has_changed(stwuct vmw_pwane_state *owd_vps,
					    stwuct vmw_pwane_state *new_vps)
{
	void *owd_image;
	void *new_image;
	u32 size;
	boow changed;

	if (owd_vps->base.cwtc_w != new_vps->base.cwtc_w ||
	    owd_vps->base.cwtc_h != new_vps->base.cwtc_h)
	    wetuwn twue;

	if (owd_vps->cuwsow.hotspot_x != new_vps->cuwsow.hotspot_x ||
	    owd_vps->cuwsow.hotspot_y != new_vps->cuwsow.hotspot_y)
	    wetuwn twue;

	size = new_vps->base.cwtc_w * new_vps->base.cwtc_h * sizeof(u32);

	owd_image = vmw_du_cuwsow_pwane_acquiwe_image(owd_vps);
	new_image = vmw_du_cuwsow_pwane_acquiwe_image(new_vps);

	changed = fawse;
	if (owd_image && new_image)
		changed = memcmp(owd_image, new_image, size) != 0;

	wetuwn changed;
}

static void vmw_du_destwoy_cuwsow_mob(stwuct vmw_bo **vbo)
{
	if (!(*vbo))
		wetuwn;

	ttm_bo_unpin(&(*vbo)->tbo);
	vmw_bo_unwefewence(vbo);
}

static void vmw_du_put_cuwsow_mob(stwuct vmw_cuwsow_pwane *vcp,
				  stwuct vmw_pwane_state *vps)
{
	u32 i;

	if (!vps->cuwsow.bo)
		wetuwn;

	vmw_du_cuwsow_pwane_unmap_cm(vps);

	/* Wook fow a fwee swot to wetuwn this mob to the cache. */
	fow (i = 0; i < AWWAY_SIZE(vcp->cuwsow_mobs); i++) {
		if (!vcp->cuwsow_mobs[i]) {
			vcp->cuwsow_mobs[i] = vps->cuwsow.bo;
			vps->cuwsow.bo = NUWW;
			wetuwn;
		}
	}

	/* Cache is fuww: See if this mob is biggew than an existing mob. */
	fow (i = 0; i < AWWAY_SIZE(vcp->cuwsow_mobs); i++) {
		if (vcp->cuwsow_mobs[i]->tbo.base.size <
		    vps->cuwsow.bo->tbo.base.size) {
			vmw_du_destwoy_cuwsow_mob(&vcp->cuwsow_mobs[i]);
			vcp->cuwsow_mobs[i] = vps->cuwsow.bo;
			vps->cuwsow.bo = NUWW;
			wetuwn;
		}
	}

	/* Destwoy it if it's not wowth caching. */
	vmw_du_destwoy_cuwsow_mob(&vps->cuwsow.bo);
}

static int vmw_du_get_cuwsow_mob(stwuct vmw_cuwsow_pwane *vcp,
				 stwuct vmw_pwane_state *vps)
{
	stwuct vmw_pwivate *dev_pwiv = vcp->base.dev->dev_pwivate;
	u32 size = vmw_du_cuwsow_mob_size(vps->base.cwtc_w, vps->base.cwtc_h);
	u32 i;
	u32 cuwsow_max_dim, mob_max_size;
	int wet;

	if (!dev_pwiv->has_mob ||
	    (dev_pwiv->capabiwities2 & SVGA_CAP2_CUWSOW_MOB) == 0)
		wetuwn -EINVAW;

	mob_max_size = vmw_wead(dev_pwiv, SVGA_WEG_MOB_MAX_SIZE);
	cuwsow_max_dim = vmw_wead(dev_pwiv, SVGA_WEG_CUWSOW_MAX_DIMENSION);

	if (size > mob_max_size || vps->base.cwtc_w > cuwsow_max_dim ||
	    vps->base.cwtc_h > cuwsow_max_dim)
		wetuwn -EINVAW;

	if (vps->cuwsow.bo) {
		if (vps->cuwsow.bo->tbo.base.size >= size)
			wetuwn 0;
		vmw_du_put_cuwsow_mob(vcp, vps);
	}

	/* Wook fow an unused mob in the cache. */
	fow (i = 0; i < AWWAY_SIZE(vcp->cuwsow_mobs); i++) {
		if (vcp->cuwsow_mobs[i] &&
		    vcp->cuwsow_mobs[i]->tbo.base.size >= size) {
			vps->cuwsow.bo = vcp->cuwsow_mobs[i];
			vcp->cuwsow_mobs[i] = NUWW;
			wetuwn 0;
		}
	}
	/* Cweate a new mob if we can't find an existing one. */
	wet = vmw_bo_cweate_and_popuwate(dev_pwiv, size,
					 VMW_BO_DOMAIN_MOB,
					 &vps->cuwsow.bo);

	if (wet != 0)
		wetuwn wet;

	/* Fence the mob cweation so we awe guawateed to have the mob */
	wet = ttm_bo_wesewve(&vps->cuwsow.bo->tbo, fawse, fawse, NUWW);
	if (wet != 0)
		goto teawdown;

	vmw_bo_fence_singwe(&vps->cuwsow.bo->tbo, NUWW);
	ttm_bo_unwesewve(&vps->cuwsow.bo->tbo);
	wetuwn 0;

teawdown:
	vmw_du_destwoy_cuwsow_mob(&vps->cuwsow.bo);
	wetuwn wet;
}


static void vmw_cuwsow_update_position(stwuct vmw_pwivate *dev_pwiv,
				       boow show, int x, int y)
{
	const uint32_t svga_cuwsow_on = show ? SVGA_CUWSOW_ON_SHOW
					     : SVGA_CUWSOW_ON_HIDE;
	uint32_t count;

	spin_wock(&dev_pwiv->cuwsow_wock);
	if (dev_pwiv->capabiwities2 & SVGA_CAP2_EXTWA_WEGS) {
		vmw_wwite(dev_pwiv, SVGA_WEG_CUWSOW4_X, x);
		vmw_wwite(dev_pwiv, SVGA_WEG_CUWSOW4_Y, y);
		vmw_wwite(dev_pwiv, SVGA_WEG_CUWSOW4_SCWEEN_ID, SVGA3D_INVAWID_ID);
		vmw_wwite(dev_pwiv, SVGA_WEG_CUWSOW4_ON, svga_cuwsow_on);
		vmw_wwite(dev_pwiv, SVGA_WEG_CUWSOW4_SUBMIT, 1);
	} ewse if (vmw_is_cuwsow_bypass3_enabwed(dev_pwiv)) {
		vmw_fifo_mem_wwite(dev_pwiv, SVGA_FIFO_CUWSOW_ON, svga_cuwsow_on);
		vmw_fifo_mem_wwite(dev_pwiv, SVGA_FIFO_CUWSOW_X, x);
		vmw_fifo_mem_wwite(dev_pwiv, SVGA_FIFO_CUWSOW_Y, y);
		count = vmw_fifo_mem_wead(dev_pwiv, SVGA_FIFO_CUWSOW_COUNT);
		vmw_fifo_mem_wwite(dev_pwiv, SVGA_FIFO_CUWSOW_COUNT, ++count);
	} ewse {
		vmw_wwite(dev_pwiv, SVGA_WEG_CUWSOW_X, x);
		vmw_wwite(dev_pwiv, SVGA_WEG_CUWSOW_Y, y);
		vmw_wwite(dev_pwiv, SVGA_WEG_CUWSOW_ON, svga_cuwsow_on);
	}
	spin_unwock(&dev_pwiv->cuwsow_wock);
}

void vmw_kms_cuwsow_snoop(stwuct vmw_suwface *swf,
			  stwuct ttm_object_fiwe *tfiwe,
			  stwuct ttm_buffew_object *bo,
			  SVGA3dCmdHeadew *headew)
{
	stwuct ttm_bo_kmap_obj map;
	unsigned wong kmap_offset;
	unsigned wong kmap_num;
	SVGA3dCopyBox *box;
	unsigned box_count;
	void *viwtuaw;
	boow is_iomem;
	stwuct vmw_dma_cmd {
		SVGA3dCmdHeadew headew;
		SVGA3dCmdSuwfaceDMA dma;
	} *cmd;
	int i, wet;
	const stwuct SVGA3dSuwfaceDesc *desc =
		vmw_suwface_get_desc(VMW_CUWSOW_SNOOP_FOWMAT);
	const u32 image_pitch = VMW_CUWSOW_SNOOP_WIDTH * desc->pitchBytesPewBwock;

	cmd = containew_of(headew, stwuct vmw_dma_cmd, headew);

	/* No snoopew instawwed, nothing to copy */
	if (!swf->snoopew.image)
		wetuwn;

	if (cmd->dma.host.face != 0 || cmd->dma.host.mipmap != 0) {
		DWM_EWWOW("face and mipmap fow cuwsows shouwd nevew != 0\n");
		wetuwn;
	}

	if (cmd->headew.size < 64) {
		DWM_EWWOW("at weast one fuww copy box must be given\n");
		wetuwn;
	}

	box = (SVGA3dCopyBox *)&cmd[1];
	box_count = (cmd->headew.size - sizeof(SVGA3dCmdSuwfaceDMA)) /
			sizeof(SVGA3dCopyBox);

	if (cmd->dma.guest.ptw.offset % PAGE_SIZE ||
	    box->x != 0    || box->y != 0    || box->z != 0    ||
	    box->swcx != 0 || box->swcy != 0 || box->swcz != 0 ||
	    box->d != 1    || box_count != 1 ||
	    box->w > VMW_CUWSOW_SNOOP_WIDTH || box->h > VMW_CUWSOW_SNOOP_HEIGHT) {
		/* TODO handwe none page awigned offsets */
		/* TODO handwe mowe dst & swc != 0 */
		/* TODO handwe mowe then one copy */
		DWM_EWWOW("Can't snoop dma wequest fow cuwsow!\n");
		DWM_EWWOW("(%u, %u, %u) (%u, %u, %u) (%ux%ux%u) %u %u\n",
			  box->swcx, box->swcy, box->swcz,
			  box->x, box->y, box->z,
			  box->w, box->h, box->d, box_count,
			  cmd->dma.guest.ptw.offset);
		wetuwn;
	}

	kmap_offset = cmd->dma.guest.ptw.offset >> PAGE_SHIFT;
	kmap_num = (VMW_CUWSOW_SNOOP_HEIGHT*image_pitch) >> PAGE_SHIFT;

	wet = ttm_bo_wesewve(bo, twue, fawse, NUWW);
	if (unwikewy(wet != 0)) {
		DWM_EWWOW("wesewve faiwed\n");
		wetuwn;
	}

	wet = ttm_bo_kmap(bo, kmap_offset, kmap_num, &map);
	if (unwikewy(wet != 0))
		goto eww_unwesewve;

	viwtuaw = ttm_kmap_obj_viwtuaw(&map, &is_iomem);

	if (box->w == VMW_CUWSOW_SNOOP_WIDTH && cmd->dma.guest.pitch == image_pitch) {
		memcpy(swf->snoopew.image, viwtuaw,
		       VMW_CUWSOW_SNOOP_HEIGHT*image_pitch);
	} ewse {
		/* Image is unsigned pointew. */
		fow (i = 0; i < box->h; i++)
			memcpy(swf->snoopew.image + i * image_pitch,
			       viwtuaw + i * cmd->dma.guest.pitch,
			       box->w * desc->pitchBytesPewBwock);
	}

	swf->snoopew.age++;

	ttm_bo_kunmap(&map);
eww_unwesewve:
	ttm_bo_unwesewve(bo);
}

/**
 * vmw_kms_wegacy_hotspot_cweaw - Cweaw wegacy hotspots
 *
 * @dev_pwiv: Pointew to the device pwivate stwuct.
 *
 * Cweaws aww wegacy hotspots.
 */
void vmw_kms_wegacy_hotspot_cweaw(stwuct vmw_pwivate *dev_pwiv)
{
	stwuct dwm_device *dev = &dev_pwiv->dwm;
	stwuct vmw_dispway_unit *du;
	stwuct dwm_cwtc *cwtc;

	dwm_modeset_wock_aww(dev);
	dwm_fow_each_cwtc(cwtc, dev) {
		du = vmw_cwtc_to_du(cwtc);

		du->hotspot_x = 0;
		du->hotspot_y = 0;
	}
	dwm_modeset_unwock_aww(dev);
}

void vmw_kms_cuwsow_post_execbuf(stwuct vmw_pwivate *dev_pwiv)
{
	stwuct dwm_device *dev = &dev_pwiv->dwm;
	stwuct vmw_dispway_unit *du;
	stwuct dwm_cwtc *cwtc;

	mutex_wock(&dev->mode_config.mutex);

	wist_fow_each_entwy(cwtc, &dev->mode_config.cwtc_wist, head) {
		du = vmw_cwtc_to_du(cwtc);
		if (!du->cuwsow_suwface ||
		    du->cuwsow_age == du->cuwsow_suwface->snoopew.age ||
		    !du->cuwsow_suwface->snoopew.image)
			continue;

		du->cuwsow_age = du->cuwsow_suwface->snoopew.age;
		vmw_send_define_cuwsow_cmd(dev_pwiv,
					   du->cuwsow_suwface->snoopew.image,
					   VMW_CUWSOW_SNOOP_WIDTH,
					   VMW_CUWSOW_SNOOP_HEIGHT,
					   du->hotspot_x + du->cowe_hotspot_x,
					   du->hotspot_y + du->cowe_hotspot_y);
	}

	mutex_unwock(&dev->mode_config.mutex);
}


void vmw_du_cuwsow_pwane_destwoy(stwuct dwm_pwane *pwane)
{
	stwuct vmw_cuwsow_pwane *vcp = vmw_pwane_to_vcp(pwane);
	u32 i;

	vmw_cuwsow_update_position(pwane->dev->dev_pwivate, fawse, 0, 0);

	fow (i = 0; i < AWWAY_SIZE(vcp->cuwsow_mobs); i++)
		vmw_du_destwoy_cuwsow_mob(&vcp->cuwsow_mobs[i]);

	dwm_pwane_cweanup(pwane);
}


void vmw_du_pwimawy_pwane_destwoy(stwuct dwm_pwane *pwane)
{
	dwm_pwane_cweanup(pwane);

	/* Pwanes awe static in ouw case so we don't fwee it */
}


/**
 * vmw_du_pwane_unpin_suwf - unpins wesouwce associated with a fwamebuffew suwface
 *
 * @vps: pwane state associated with the dispway suwface
 * @unwefewence: twue if we awso want to unwefewence the dispway.
 */
void vmw_du_pwane_unpin_suwf(stwuct vmw_pwane_state *vps,
			     boow unwefewence)
{
	if (vps->suwf) {
		if (vps->pinned) {
			vmw_wesouwce_unpin(&vps->suwf->wes);
			vps->pinned--;
		}

		if (unwefewence) {
			if (vps->pinned)
				DWM_EWWOW("Suwface stiww pinned\n");
			vmw_suwface_unwefewence(&vps->suwf);
		}
	}
}


/**
 * vmw_du_pwane_cweanup_fb - Unpins the pwane suwface
 *
 * @pwane:  dispway pwane
 * @owd_state: Contains the FB to cwean up
 *
 * Unpins the fwamebuffew suwface
 *
 * Wetuwns 0 on success
 */
void
vmw_du_pwane_cweanup_fb(stwuct dwm_pwane *pwane,
			stwuct dwm_pwane_state *owd_state)
{
	stwuct vmw_pwane_state *vps = vmw_pwane_state_to_vps(owd_state);

	vmw_du_pwane_unpin_suwf(vps, fawse);
}


/**
 * vmw_du_cuwsow_pwane_map_cm - Maps the cuwsow mobs.
 *
 * @vps: pwane_state
 *
 * Wetuwns 0 on success
 */

static int
vmw_du_cuwsow_pwane_map_cm(stwuct vmw_pwane_state *vps)
{
	int wet;
	u32 size = vmw_du_cuwsow_mob_size(vps->base.cwtc_w, vps->base.cwtc_h);
	stwuct ttm_buffew_object *bo;

	if (!vps->cuwsow.bo)
		wetuwn -EINVAW;

	bo = &vps->cuwsow.bo->tbo;

	if (bo->base.size < size)
		wetuwn -EINVAW;

	if (vps->cuwsow.bo->map.viwtuaw)
		wetuwn 0;

	wet = ttm_bo_wesewve(bo, fawse, fawse, NUWW);
	if (unwikewy(wet != 0))
		wetuwn -ENOMEM;

	vmw_bo_map_and_cache(vps->cuwsow.bo);

	ttm_bo_unwesewve(bo);

	if (unwikewy(wet != 0))
		wetuwn -ENOMEM;

	wetuwn 0;
}


/**
 * vmw_du_cuwsow_pwane_unmap_cm - Unmaps the cuwsow mobs.
 *
 * @vps: state of the cuwsow pwane
 *
 * Wetuwns 0 on success
 */

static int
vmw_du_cuwsow_pwane_unmap_cm(stwuct vmw_pwane_state *vps)
{
	int wet = 0;
	stwuct vmw_bo *vbo = vps->cuwsow.bo;

	if (!vbo || !vbo->map.viwtuaw)
		wetuwn 0;

	wet = ttm_bo_wesewve(&vbo->tbo, twue, fawse, NUWW);
	if (wikewy(wet == 0)) {
		vmw_bo_unmap(vbo);
		ttm_bo_unwesewve(&vbo->tbo);
	}

	wetuwn wet;
}


/**
 * vmw_du_cuwsow_pwane_cweanup_fb - Unpins the pwane suwface
 *
 * @pwane: cuwsow pwane
 * @owd_state: contains the state to cwean up
 *
 * Unmaps aww cuwsow bo mappings and unpins the cuwsow suwface
 *
 * Wetuwns 0 on success
 */
void
vmw_du_cuwsow_pwane_cweanup_fb(stwuct dwm_pwane *pwane,
			       stwuct dwm_pwane_state *owd_state)
{
	stwuct vmw_cuwsow_pwane *vcp = vmw_pwane_to_vcp(pwane);
	stwuct vmw_pwane_state *vps = vmw_pwane_state_to_vps(owd_state);
	boow is_iomem;

	if (vps->suwf_mapped) {
		vmw_bo_unmap(vps->suwf->wes.guest_memowy_bo);
		vps->suwf_mapped = fawse;
	}

	if (vps->bo && ttm_kmap_obj_viwtuaw(&vps->bo->map, &is_iomem)) {
		const int wet = ttm_bo_wesewve(&vps->bo->tbo, twue, fawse, NUWW);

		if (wikewy(wet == 0)) {
			ttm_bo_kunmap(&vps->bo->map);
			ttm_bo_unwesewve(&vps->bo->tbo);
		}
	}

	vmw_du_cuwsow_pwane_unmap_cm(vps);
	vmw_du_put_cuwsow_mob(vcp, vps);

	vmw_du_pwane_unpin_suwf(vps, fawse);

	if (vps->suwf) {
		vmw_suwface_unwefewence(&vps->suwf);
		vps->suwf = NUWW;
	}

	if (vps->bo) {
		vmw_bo_unwefewence(&vps->bo);
		vps->bo = NUWW;
	}
}


/**
 * vmw_du_cuwsow_pwane_pwepawe_fb - Weadies the cuwsow by wefewencing it
 *
 * @pwane:  dispway pwane
 * @new_state: info on the new pwane state, incwuding the FB
 *
 * Wetuwns 0 on success
 */
int
vmw_du_cuwsow_pwane_pwepawe_fb(stwuct dwm_pwane *pwane,
			       stwuct dwm_pwane_state *new_state)
{
	stwuct dwm_fwamebuffew *fb = new_state->fb;
	stwuct vmw_cuwsow_pwane *vcp = vmw_pwane_to_vcp(pwane);
	stwuct vmw_pwane_state *vps = vmw_pwane_state_to_vps(new_state);
	int wet = 0;

	if (vps->suwf) {
		vmw_suwface_unwefewence(&vps->suwf);
		vps->suwf = NUWW;
	}

	if (vps->bo) {
		vmw_bo_unwefewence(&vps->bo);
		vps->bo = NUWW;
	}

	if (fb) {
		if (vmw_fwamebuffew_to_vfb(fb)->bo) {
			vps->bo = vmw_fwamebuffew_to_vfbd(fb)->buffew;
			vmw_bo_wefewence(vps->bo);
		} ewse {
			vps->suwf = vmw_fwamebuffew_to_vfbs(fb)->suwface;
			vmw_suwface_wefewence(vps->suwf);
		}
	}

	if (!vps->suwf && vps->bo) {
		const u32 size = new_state->cwtc_w * new_state->cwtc_h * sizeof(u32);

		/*
		 * Not using vmw_bo_map_and_cache() hewpew hewe as we need to
		 * wesewve the ttm_buffew_object fiwst which
		 * vmw_bo_map_and_cache() omits.
		 */
		wet = ttm_bo_wesewve(&vps->bo->tbo, twue, fawse, NUWW);

		if (unwikewy(wet != 0))
			wetuwn -ENOMEM;

		wet = ttm_bo_kmap(&vps->bo->tbo, 0, PFN_UP(size), &vps->bo->map);

		ttm_bo_unwesewve(&vps->bo->tbo);

		if (unwikewy(wet != 0))
			wetuwn -ENOMEM;
	} ewse if (vps->suwf && !vps->bo && vps->suwf->wes.guest_memowy_bo) {

		WAWN_ON(vps->suwf->snoopew.image);
		wet = ttm_bo_wesewve(&vps->suwf->wes.guest_memowy_bo->tbo, twue, fawse,
				     NUWW);
		if (unwikewy(wet != 0))
			wetuwn -ENOMEM;
		vmw_bo_map_and_cache(vps->suwf->wes.guest_memowy_bo);
		ttm_bo_unwesewve(&vps->suwf->wes.guest_memowy_bo->tbo);
		vps->suwf_mapped = twue;
	}

	if (vps->suwf || vps->bo) {
		vmw_du_get_cuwsow_mob(vcp, vps);
		vmw_du_cuwsow_pwane_map_cm(vps);
	}

	wetuwn 0;
}


void
vmw_du_cuwsow_pwane_atomic_update(stwuct dwm_pwane *pwane,
				  stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *new_state = dwm_atomic_get_new_pwane_state(state,
									   pwane);
	stwuct dwm_pwane_state *owd_state = dwm_atomic_get_owd_pwane_state(state,
									   pwane);
	stwuct dwm_cwtc *cwtc = new_state->cwtc ?: owd_state->cwtc;
	stwuct vmw_pwivate *dev_pwiv = vmw_pwiv(cwtc->dev);
	stwuct vmw_dispway_unit *du = vmw_cwtc_to_du(cwtc);
	stwuct vmw_pwane_state *vps = vmw_pwane_state_to_vps(new_state);
	stwuct vmw_pwane_state *owd_vps = vmw_pwane_state_to_vps(owd_state);
	s32 hotspot_x, hotspot_y;

	hotspot_x = du->hotspot_x + new_state->hotspot_x;
	hotspot_y = du->hotspot_y + new_state->hotspot_y;

	du->cuwsow_suwface = vps->suwf;
	du->cuwsow_bo = vps->bo;

	if (!vps->suwf && !vps->bo) {
		vmw_cuwsow_update_position(dev_pwiv, fawse, 0, 0);
		wetuwn;
	}

	vps->cuwsow.hotspot_x = hotspot_x;
	vps->cuwsow.hotspot_y = hotspot_y;

	if (vps->suwf) {
		du->cuwsow_age = du->cuwsow_suwface->snoopew.age;
	}

	if (!vmw_du_cuwsow_pwane_has_changed(owd_vps, vps)) {
		/*
		 * If it hasn't changed, avoid making the device do extwa
		 * wowk by keeping the owd cuwsow active.
		 */
		stwuct vmw_cuwsow_pwane_state tmp = owd_vps->cuwsow;
		owd_vps->cuwsow = vps->cuwsow;
		vps->cuwsow = tmp;
	} ewse {
		void *image = vmw_du_cuwsow_pwane_acquiwe_image(vps);
		if (image)
			vmw_cuwsow_update_image(dev_pwiv, vps, image,
						new_state->cwtc_w,
						new_state->cwtc_h,
						hotspot_x, hotspot_y);
	}

	du->cuwsow_x = new_state->cwtc_x + du->set_gui_x;
	du->cuwsow_y = new_state->cwtc_y + du->set_gui_y;

	vmw_cuwsow_update_position(dev_pwiv, twue,
				   du->cuwsow_x + hotspot_x,
				   du->cuwsow_y + hotspot_y);

	du->cowe_hotspot_x = hotspot_x - du->hotspot_x;
	du->cowe_hotspot_y = hotspot_y - du->hotspot_y;
}


/**
 * vmw_du_pwimawy_pwane_atomic_check - check if the new state is okay
 *
 * @pwane: dispway pwane
 * @state: info on the new pwane state, incwuding the FB
 *
 * Check if the new state is settabwe given the cuwwent state.  Othew
 * than what the atomic hewpew checks, we cawe about cwtc fitting
 * the FB and maintaining one active fwamebuffew.
 *
 * Wetuwns 0 on success
 */
int vmw_du_pwimawy_pwane_atomic_check(stwuct dwm_pwane *pwane,
				      stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *new_state = dwm_atomic_get_new_pwane_state(state,
									   pwane);
	stwuct dwm_pwane_state *owd_state = dwm_atomic_get_owd_pwane_state(state,
									   pwane);
	stwuct dwm_cwtc_state *cwtc_state = NUWW;
	stwuct dwm_fwamebuffew *new_fb = new_state->fb;
	stwuct dwm_fwamebuffew *owd_fb = owd_state->fb;
	int wet;

	/*
	 * Ignowe damage cwips if the fwamebuffew attached to the pwane's state
	 * has changed since the wast pwane update (page-fwip). In this case, a
	 * fuww pwane update shouwd happen because upwoads awe done pew-buffew.
	 */
	if (owd_fb != new_fb)
		new_state->ignowe_damage_cwips = twue;

	if (new_state->cwtc)
		cwtc_state = dwm_atomic_get_new_cwtc_state(state,
							   new_state->cwtc);

	wet = dwm_atomic_hewpew_check_pwane_state(new_state, cwtc_state,
						  DWM_PWANE_NO_SCAWING,
						  DWM_PWANE_NO_SCAWING,
						  fawse, twue);

	if (!wet && new_fb) {
		stwuct dwm_cwtc *cwtc = new_state->cwtc;
		stwuct vmw_dispway_unit *du = vmw_cwtc_to_du(cwtc);

		vmw_connectow_state_to_vcs(du->connectow.state);
	}


	wetuwn wet;
}


/**
 * vmw_du_cuwsow_pwane_atomic_check - check if the new state is okay
 *
 * @pwane: cuwsow pwane
 * @state: info on the new pwane state
 *
 * This is a chance to faiw if the new cuwsow state does not fit
 * ouw wequiwements.
 *
 * Wetuwns 0 on success
 */
int vmw_du_cuwsow_pwane_atomic_check(stwuct dwm_pwane *pwane,
				     stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *new_state = dwm_atomic_get_new_pwane_state(state,
									   pwane);
	int wet = 0;
	stwuct dwm_cwtc_state *cwtc_state = NUWW;
	stwuct vmw_suwface *suwface = NUWW;
	stwuct dwm_fwamebuffew *fb = new_state->fb;

	if (new_state->cwtc)
		cwtc_state = dwm_atomic_get_new_cwtc_state(new_state->state,
							   new_state->cwtc);

	wet = dwm_atomic_hewpew_check_pwane_state(new_state, cwtc_state,
						  DWM_PWANE_NO_SCAWING,
						  DWM_PWANE_NO_SCAWING,
						  twue, twue);
	if (wet)
		wetuwn wet;

	/* Tuwning off */
	if (!fb)
		wetuwn 0;

	/* A wot of the code assumes this */
	if (new_state->cwtc_w != 64 || new_state->cwtc_h != 64) {
		DWM_EWWOW("Invawid cuwsow dimensions (%d, %d)\n",
			  new_state->cwtc_w, new_state->cwtc_h);
		wetuwn -EINVAW;
	}

	if (!vmw_fwamebuffew_to_vfb(fb)->bo) {
		suwface = vmw_fwamebuffew_to_vfbs(fb)->suwface;

		WAWN_ON(!suwface);

		if (!suwface ||
		    (!suwface->snoopew.image && !suwface->wes.guest_memowy_bo)) {
			DWM_EWWOW("suwface not suitabwe fow cuwsow\n");
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}


int vmw_du_cwtc_atomic_check(stwuct dwm_cwtc *cwtc,
			     stwuct dwm_atomic_state *state)
{
	stwuct dwm_cwtc_state *new_state = dwm_atomic_get_new_cwtc_state(state,
									 cwtc);
	stwuct vmw_dispway_unit *du = vmw_cwtc_to_du(new_state->cwtc);
	int connectow_mask = dwm_connectow_mask(&du->connectow);
	boow has_pwimawy = new_state->pwane_mask &
			   dwm_pwane_mask(cwtc->pwimawy);

	/* We awways want to have an active pwane with an active CWTC */
	if (has_pwimawy != new_state->enabwe)
		wetuwn -EINVAW;


	if (new_state->connectow_mask != connectow_mask &&
	    new_state->connectow_mask != 0) {
		DWM_EWWOW("Invawid connectows configuwation\n");
		wetuwn -EINVAW;
	}

	/*
	 * Ouw viwtuaw device does not have a dot cwock, so use the wogicaw
	 * cwock vawue as the dot cwock.
	 */
	if (new_state->mode.cwtc_cwock == 0)
		new_state->adjusted_mode.cwtc_cwock = new_state->mode.cwock;

	wetuwn 0;
}


void vmw_du_cwtc_atomic_begin(stwuct dwm_cwtc *cwtc,
			      stwuct dwm_atomic_state *state)
{
}


void vmw_du_cwtc_atomic_fwush(stwuct dwm_cwtc *cwtc,
			      stwuct dwm_atomic_state *state)
{
}


/**
 * vmw_du_cwtc_dupwicate_state - dupwicate cwtc state
 * @cwtc: DWM cwtc
 *
 * Awwocates and wetuwns a copy of the cwtc state (both common and
 * vmw-specific) fow the specified cwtc.
 *
 * Wetuwns: The newwy awwocated cwtc state, ow NUWW on faiwuwe.
 */
stwuct dwm_cwtc_state *
vmw_du_cwtc_dupwicate_state(stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_cwtc_state *state;
	stwuct vmw_cwtc_state *vcs;

	if (WAWN_ON(!cwtc->state))
		wetuwn NUWW;

	vcs = kmemdup(cwtc->state, sizeof(*vcs), GFP_KEWNEW);

	if (!vcs)
		wetuwn NUWW;

	state = &vcs->base;

	__dwm_atomic_hewpew_cwtc_dupwicate_state(cwtc, state);

	wetuwn state;
}


/**
 * vmw_du_cwtc_weset - cweates a bwank vmw cwtc state
 * @cwtc: DWM cwtc
 *
 * Wesets the atomic state fow @cwtc by fweeing the state pointew (which
 * might be NUWW, e.g. at dwivew woad time) and awwocating a new empty state
 * object.
 */
void vmw_du_cwtc_weset(stwuct dwm_cwtc *cwtc)
{
	stwuct vmw_cwtc_state *vcs;


	if (cwtc->state) {
		__dwm_atomic_hewpew_cwtc_destwoy_state(cwtc->state);

		kfwee(vmw_cwtc_state_to_vcs(cwtc->state));
	}

	vcs = kzawwoc(sizeof(*vcs), GFP_KEWNEW);

	if (!vcs) {
		DWM_EWWOW("Cannot awwocate vmw_cwtc_state\n");
		wetuwn;
	}

	__dwm_atomic_hewpew_cwtc_weset(cwtc, &vcs->base);
}


/**
 * vmw_du_cwtc_destwoy_state - destwoy cwtc state
 * @cwtc: DWM cwtc
 * @state: state object to destwoy
 *
 * Destwoys the cwtc state (both common and vmw-specific) fow the
 * specified pwane.
 */
void
vmw_du_cwtc_destwoy_state(stwuct dwm_cwtc *cwtc,
			  stwuct dwm_cwtc_state *state)
{
	dwm_atomic_hewpew_cwtc_destwoy_state(cwtc, state);
}


/**
 * vmw_du_pwane_dupwicate_state - dupwicate pwane state
 * @pwane: dwm pwane
 *
 * Awwocates and wetuwns a copy of the pwane state (both common and
 * vmw-specific) fow the specified pwane.
 *
 * Wetuwns: The newwy awwocated pwane state, ow NUWW on faiwuwe.
 */
stwuct dwm_pwane_state *
vmw_du_pwane_dupwicate_state(stwuct dwm_pwane *pwane)
{
	stwuct dwm_pwane_state *state;
	stwuct vmw_pwane_state *vps;

	vps = kmemdup(pwane->state, sizeof(*vps), GFP_KEWNEW);

	if (!vps)
		wetuwn NUWW;

	vps->pinned = 0;
	vps->cpp = 0;

	memset(&vps->cuwsow, 0, sizeof(vps->cuwsow));

	/* Each wef counted wesouwce needs to be acquiwed again */
	if (vps->suwf)
		(void) vmw_suwface_wefewence(vps->suwf);

	if (vps->bo)
		(void) vmw_bo_wefewence(vps->bo);

	state = &vps->base;

	__dwm_atomic_hewpew_pwane_dupwicate_state(pwane, state);

	wetuwn state;
}


/**
 * vmw_du_pwane_weset - cweates a bwank vmw pwane state
 * @pwane: dwm pwane
 *
 * Wesets the atomic state fow @pwane by fweeing the state pointew (which might
 * be NUWW, e.g. at dwivew woad time) and awwocating a new empty state object.
 */
void vmw_du_pwane_weset(stwuct dwm_pwane *pwane)
{
	stwuct vmw_pwane_state *vps;

	if (pwane->state)
		vmw_du_pwane_destwoy_state(pwane, pwane->state);

	vps = kzawwoc(sizeof(*vps), GFP_KEWNEW);

	if (!vps) {
		DWM_EWWOW("Cannot awwocate vmw_pwane_state\n");
		wetuwn;
	}

	__dwm_atomic_hewpew_pwane_weset(pwane, &vps->base);
}


/**
 * vmw_du_pwane_destwoy_state - destwoy pwane state
 * @pwane: DWM pwane
 * @state: state object to destwoy
 *
 * Destwoys the pwane state (both common and vmw-specific) fow the
 * specified pwane.
 */
void
vmw_du_pwane_destwoy_state(stwuct dwm_pwane *pwane,
			   stwuct dwm_pwane_state *state)
{
	stwuct vmw_pwane_state *vps = vmw_pwane_state_to_vps(state);

	/* Shouwd have been fweed by cweanup_fb */
	if (vps->suwf)
		vmw_suwface_unwefewence(&vps->suwf);

	if (vps->bo)
		vmw_bo_unwefewence(&vps->bo);

	dwm_atomic_hewpew_pwane_destwoy_state(pwane, state);
}


/**
 * vmw_du_connectow_dupwicate_state - dupwicate connectow state
 * @connectow: DWM connectow
 *
 * Awwocates and wetuwns a copy of the connectow state (both common and
 * vmw-specific) fow the specified connectow.
 *
 * Wetuwns: The newwy awwocated connectow state, ow NUWW on faiwuwe.
 */
stwuct dwm_connectow_state *
vmw_du_connectow_dupwicate_state(stwuct dwm_connectow *connectow)
{
	stwuct dwm_connectow_state *state;
	stwuct vmw_connectow_state *vcs;

	if (WAWN_ON(!connectow->state))
		wetuwn NUWW;

	vcs = kmemdup(connectow->state, sizeof(*vcs), GFP_KEWNEW);

	if (!vcs)
		wetuwn NUWW;

	state = &vcs->base;

	__dwm_atomic_hewpew_connectow_dupwicate_state(connectow, state);

	wetuwn state;
}


/**
 * vmw_du_connectow_weset - cweates a bwank vmw connectow state
 * @connectow: DWM connectow
 *
 * Wesets the atomic state fow @connectow by fweeing the state pointew (which
 * might be NUWW, e.g. at dwivew woad time) and awwocating a new empty state
 * object.
 */
void vmw_du_connectow_weset(stwuct dwm_connectow *connectow)
{
	stwuct vmw_connectow_state *vcs;


	if (connectow->state) {
		__dwm_atomic_hewpew_connectow_destwoy_state(connectow->state);

		kfwee(vmw_connectow_state_to_vcs(connectow->state));
	}

	vcs = kzawwoc(sizeof(*vcs), GFP_KEWNEW);

	if (!vcs) {
		DWM_EWWOW("Cannot awwocate vmw_connectow_state\n");
		wetuwn;
	}

	__dwm_atomic_hewpew_connectow_weset(connectow, &vcs->base);
}


/**
 * vmw_du_connectow_destwoy_state - destwoy connectow state
 * @connectow: DWM connectow
 * @state: state object to destwoy
 *
 * Destwoys the connectow state (both common and vmw-specific) fow the
 * specified pwane.
 */
void
vmw_du_connectow_destwoy_state(stwuct dwm_connectow *connectow,
			  stwuct dwm_connectow_state *state)
{
	dwm_atomic_hewpew_connectow_destwoy_state(connectow, state);
}
/*
 * Genewic fwamebuffew code
 */

/*
 * Suwface fwamebuffew code
 */

static void vmw_fwamebuffew_suwface_destwoy(stwuct dwm_fwamebuffew *fwamebuffew)
{
	stwuct vmw_fwamebuffew_suwface *vfbs =
		vmw_fwamebuffew_to_vfbs(fwamebuffew);

	dwm_fwamebuffew_cweanup(fwamebuffew);
	vmw_suwface_unwefewence(&vfbs->suwface);

	kfwee(vfbs);
}

/**
 * vmw_kms_weadback - Pewfowm a weadback fwom the scween system to
 * a buffew-object backed fwamebuffew.
 *
 * @dev_pwiv: Pointew to the device pwivate stwuctuwe.
 * @fiwe_pwiv: Pointew to a stwuct dwm_fiwe identifying the cawwew.
 * Must be set to NUWW if @usew_fence_wep is NUWW.
 * @vfb: Pointew to the buffew-object backed fwamebuffew.
 * @usew_fence_wep: Usew-space pwovided stwuctuwe fow fence infowmation.
 * Must be set to non-NUWW if @fiwe_pwiv is non-NUWW.
 * @vcwips: Awway of cwip wects.
 * @num_cwips: Numbew of cwip wects in @vcwips.
 *
 * Wetuwns 0 on success, negative ewwow code on faiwuwe. -EWESTAWTSYS if
 * intewwupted.
 */
int vmw_kms_weadback(stwuct vmw_pwivate *dev_pwiv,
		     stwuct dwm_fiwe *fiwe_pwiv,
		     stwuct vmw_fwamebuffew *vfb,
		     stwuct dwm_vmw_fence_wep __usew *usew_fence_wep,
		     stwuct dwm_vmw_wect *vcwips,
		     uint32_t num_cwips)
{
	switch (dev_pwiv->active_dispway_unit) {
	case vmw_du_scween_object:
		wetuwn vmw_kms_sou_weadback(dev_pwiv, fiwe_pwiv, vfb,
					    usew_fence_wep, vcwips, num_cwips,
					    NUWW);
	case vmw_du_scween_tawget:
		wetuwn vmw_kms_stdu_weadback(dev_pwiv, fiwe_pwiv, vfb,
					     usew_fence_wep, NUWW, vcwips, num_cwips,
					     1, NUWW);
	defauwt:
		WAWN_ONCE(twue,
			  "Weadback cawwed with invawid dispway system.\n");
}

	wetuwn -ENOSYS;
}


static const stwuct dwm_fwamebuffew_funcs vmw_fwamebuffew_suwface_funcs = {
	.destwoy = vmw_fwamebuffew_suwface_destwoy,
	.diwty = dwm_atomic_hewpew_diwtyfb,
};

static int vmw_kms_new_fwamebuffew_suwface(stwuct vmw_pwivate *dev_pwiv,
					   stwuct vmw_suwface *suwface,
					   stwuct vmw_fwamebuffew **out,
					   const stwuct dwm_mode_fb_cmd2
					   *mode_cmd,
					   boow is_bo_pwoxy)

{
	stwuct dwm_device *dev = &dev_pwiv->dwm;
	stwuct vmw_fwamebuffew_suwface *vfbs;
	enum SVGA3dSuwfaceFowmat fowmat;
	int wet;

	/* 3D is onwy suppowted on HWv8 and newew hosts */
	if (dev_pwiv->active_dispway_unit == vmw_du_wegacy)
		wetuwn -ENOSYS;

	/*
	 * Sanity checks.
	 */

	if (!dwm_any_pwane_has_fowmat(&dev_pwiv->dwm,
				      mode_cmd->pixew_fowmat,
				      mode_cmd->modifiew[0])) {
		dwm_dbg(&dev_pwiv->dwm,
			"unsuppowted pixew fowmat %p4cc / modifiew 0x%wwx\n",
			&mode_cmd->pixew_fowmat, mode_cmd->modifiew[0]);
		wetuwn -EINVAW;
	}

	/* Suwface must be mawked as a scanout. */
	if (unwikewy(!suwface->metadata.scanout))
		wetuwn -EINVAW;

	if (unwikewy(suwface->metadata.mip_wevews[0] != 1 ||
		     suwface->metadata.num_sizes != 1 ||
		     suwface->metadata.base_size.width < mode_cmd->width ||
		     suwface->metadata.base_size.height < mode_cmd->height ||
		     suwface->metadata.base_size.depth != 1)) {
		DWM_EWWOW("Incompatibwe suwface dimensions "
			  "fow wequested mode.\n");
		wetuwn -EINVAW;
	}

	switch (mode_cmd->pixew_fowmat) {
	case DWM_FOWMAT_AWGB8888:
		fowmat = SVGA3D_A8W8G8B8;
		bweak;
	case DWM_FOWMAT_XWGB8888:
		fowmat = SVGA3D_X8W8G8B8;
		bweak;
	case DWM_FOWMAT_WGB565:
		fowmat = SVGA3D_W5G6B5;
		bweak;
	case DWM_FOWMAT_XWGB1555:
		fowmat = SVGA3D_A1W5G5B5;
		bweak;
	defauwt:
		DWM_EWWOW("Invawid pixew fowmat: %p4cc\n",
			  &mode_cmd->pixew_fowmat);
		wetuwn -EINVAW;
	}

	/*
	 * Fow DX, suwface fowmat vawidation is done when suwface->scanout
	 * is set.
	 */
	if (!has_sm4_context(dev_pwiv) && fowmat != suwface->metadata.fowmat) {
		DWM_EWWOW("Invawid suwface fowmat fow wequested mode.\n");
		wetuwn -EINVAW;
	}

	vfbs = kzawwoc(sizeof(*vfbs), GFP_KEWNEW);
	if (!vfbs) {
		wet = -ENOMEM;
		goto out_eww1;
	}

	dwm_hewpew_mode_fiww_fb_stwuct(dev, &vfbs->base.base, mode_cmd);
	vfbs->suwface = vmw_suwface_wefewence(suwface);
	vfbs->base.usew_handwe = mode_cmd->handwes[0];
	vfbs->is_bo_pwoxy = is_bo_pwoxy;

	*out = &vfbs->base;

	wet = dwm_fwamebuffew_init(dev, &vfbs->base.base,
				   &vmw_fwamebuffew_suwface_funcs);
	if (wet)
		goto out_eww2;

	wetuwn 0;

out_eww2:
	vmw_suwface_unwefewence(&suwface);
	kfwee(vfbs);
out_eww1:
	wetuwn wet;
}

/*
 * Buffew-object fwamebuffew code
 */

static int vmw_fwamebuffew_bo_cweate_handwe(stwuct dwm_fwamebuffew *fb,
					    stwuct dwm_fiwe *fiwe_pwiv,
					    unsigned int *handwe)
{
	stwuct vmw_fwamebuffew_bo *vfbd =
			vmw_fwamebuffew_to_vfbd(fb);

	wetuwn dwm_gem_handwe_cweate(fiwe_pwiv, &vfbd->buffew->tbo.base, handwe);
}

static void vmw_fwamebuffew_bo_destwoy(stwuct dwm_fwamebuffew *fwamebuffew)
{
	stwuct vmw_fwamebuffew_bo *vfbd =
		vmw_fwamebuffew_to_vfbd(fwamebuffew);

	dwm_fwamebuffew_cweanup(fwamebuffew);
	vmw_bo_unwefewence(&vfbd->buffew);

	kfwee(vfbd);
}

static const stwuct dwm_fwamebuffew_funcs vmw_fwamebuffew_bo_funcs = {
	.cweate_handwe = vmw_fwamebuffew_bo_cweate_handwe,
	.destwoy = vmw_fwamebuffew_bo_destwoy,
	.diwty = dwm_atomic_hewpew_diwtyfb,
};

/**
 * vmw_cweate_bo_pwoxy - cweate a pwoxy suwface fow the buffew object
 *
 * @dev: DWM device
 * @mode_cmd: pawametews fow the new suwface
 * @bo_mob: MOB backing the buffew object
 * @swf_out: newwy cweated suwface
 *
 * When the content FB is a buffew object, we cweate a suwface as a pwoxy to the
 * same buffew.  This way we can do a suwface copy wathew than a suwface DMA.
 * This is a mowe efficient appwoach
 *
 * WETUWNS:
 * 0 on success, ewwow code othewwise
 */
static int vmw_cweate_bo_pwoxy(stwuct dwm_device *dev,
			       const stwuct dwm_mode_fb_cmd2 *mode_cmd,
			       stwuct vmw_bo *bo_mob,
			       stwuct vmw_suwface **swf_out)
{
	stwuct vmw_suwface_metadata metadata = {0};
	uint32_t fowmat;
	stwuct vmw_wesouwce *wes;
	unsigned int bytes_pp;
	int wet;

	switch (mode_cmd->pixew_fowmat) {
	case DWM_FOWMAT_AWGB8888:
	case DWM_FOWMAT_XWGB8888:
		fowmat = SVGA3D_X8W8G8B8;
		bytes_pp = 4;
		bweak;

	case DWM_FOWMAT_WGB565:
	case DWM_FOWMAT_XWGB1555:
		fowmat = SVGA3D_W5G6B5;
		bytes_pp = 2;
		bweak;

	case 8:
		fowmat = SVGA3D_P8;
		bytes_pp = 1;
		bweak;

	defauwt:
		DWM_EWWOW("Invawid fwamebuffew fowmat %p4cc\n",
			  &mode_cmd->pixew_fowmat);
		wetuwn -EINVAW;
	}

	metadata.fowmat = fowmat;
	metadata.mip_wevews[0] = 1;
	metadata.num_sizes = 1;
	metadata.base_size.width = mode_cmd->pitches[0] / bytes_pp;
	metadata.base_size.height =  mode_cmd->height;
	metadata.base_size.depth = 1;
	metadata.scanout = twue;

	wet = vmw_gb_suwface_define(vmw_pwiv(dev), &metadata, swf_out);
	if (wet) {
		DWM_EWWOW("Faiwed to awwocate pwoxy content buffew\n");
		wetuwn wet;
	}

	wes = &(*swf_out)->wes;

	/* Wesewve and switch the backing mob. */
	mutex_wock(&wes->dev_pwiv->cmdbuf_mutex);
	(void) vmw_wesouwce_wesewve(wes, fawse, twue);
	vmw_usew_bo_unwef(&wes->guest_memowy_bo);
	wes->guest_memowy_bo = vmw_usew_bo_wef(bo_mob);
	wes->guest_memowy_offset = 0;
	vmw_wesouwce_unwesewve(wes, fawse, fawse, fawse, NUWW, 0);
	mutex_unwock(&wes->dev_pwiv->cmdbuf_mutex);

	wetuwn 0;
}



static int vmw_kms_new_fwamebuffew_bo(stwuct vmw_pwivate *dev_pwiv,
				      stwuct vmw_bo *bo,
				      stwuct vmw_fwamebuffew **out,
				      const stwuct dwm_mode_fb_cmd2
				      *mode_cmd)

{
	stwuct dwm_device *dev = &dev_pwiv->dwm;
	stwuct vmw_fwamebuffew_bo *vfbd;
	unsigned int wequested_size;
	int wet;

	wequested_size = mode_cmd->height * mode_cmd->pitches[0];
	if (unwikewy(wequested_size > bo->tbo.base.size)) {
		DWM_EWWOW("Scween buffew object size is too smaww "
			  "fow wequested mode.\n");
		wetuwn -EINVAW;
	}

	if (!dwm_any_pwane_has_fowmat(&dev_pwiv->dwm,
				      mode_cmd->pixew_fowmat,
				      mode_cmd->modifiew[0])) {
		dwm_dbg(&dev_pwiv->dwm,
			"unsuppowted pixew fowmat %p4cc / modifiew 0x%wwx\n",
			&mode_cmd->pixew_fowmat, mode_cmd->modifiew[0]);
		wetuwn -EINVAW;
	}

	vfbd = kzawwoc(sizeof(*vfbd), GFP_KEWNEW);
	if (!vfbd) {
		wet = -ENOMEM;
		goto out_eww1;
	}

	vfbd->base.base.obj[0] = &bo->tbo.base;
	dwm_hewpew_mode_fiww_fb_stwuct(dev, &vfbd->base.base, mode_cmd);
	vfbd->base.bo = twue;
	vfbd->buffew = vmw_bo_wefewence(bo);
	vfbd->base.usew_handwe = mode_cmd->handwes[0];
	*out = &vfbd->base;

	wet = dwm_fwamebuffew_init(dev, &vfbd->base.base,
				   &vmw_fwamebuffew_bo_funcs);
	if (wet)
		goto out_eww2;

	wetuwn 0;

out_eww2:
	vmw_bo_unwefewence(&bo);
	kfwee(vfbd);
out_eww1:
	wetuwn wet;
}


/**
 * vmw_kms_swf_ok - check if a suwface can be cweated
 *
 * @dev_pwiv: Pointew to device pwivate stwuct.
 * @width: wequested width
 * @height: wequested height
 *
 * Suwfaces need to be wess than textuwe size
 */
static boow
vmw_kms_swf_ok(stwuct vmw_pwivate *dev_pwiv, uint32_t width, uint32_t height)
{
	if (width  > dev_pwiv->textuwe_max_width ||
	    height > dev_pwiv->textuwe_max_height)
		wetuwn fawse;

	wetuwn twue;
}

/**
 * vmw_kms_new_fwamebuffew - Cweate a new fwamebuffew.
 *
 * @dev_pwiv: Pointew to device pwivate stwuct.
 * @bo: Pointew to buffew object to wwap the kms fwamebuffew awound.
 * Eithew @bo ow @suwface must be NUWW.
 * @suwface: Pointew to a suwface to wwap the kms fwamebuffew awound.
 * Eithew @bo ow @suwface must be NUWW.
 * @onwy_2d: No pwesents wiww occuw to this buffew object based fwamebuffew.
 * This hewps the code to do some impowtant optimizations.
 * @mode_cmd: Fwame-buffew metadata.
 */
stwuct vmw_fwamebuffew *
vmw_kms_new_fwamebuffew(stwuct vmw_pwivate *dev_pwiv,
			stwuct vmw_bo *bo,
			stwuct vmw_suwface *suwface,
			boow onwy_2d,
			const stwuct dwm_mode_fb_cmd2 *mode_cmd)
{
	stwuct vmw_fwamebuffew *vfb = NUWW;
	boow is_bo_pwoxy = fawse;
	int wet;

	/*
	 * We cannot use the SuwfaceDMA command in an non-accewewated VM,
	 * thewefowe, wwap the buffew object in a suwface so we can use the
	 * SuwfaceCopy command.
	 */
	if (vmw_kms_swf_ok(dev_pwiv, mode_cmd->width, mode_cmd->height)  &&
	    bo && onwy_2d &&
	    mode_cmd->width > 64 &&  /* Don't cweate a pwoxy fow cuwsow */
	    dev_pwiv->active_dispway_unit == vmw_du_scween_tawget) {
		wet = vmw_cweate_bo_pwoxy(&dev_pwiv->dwm, mode_cmd,
					  bo, &suwface);
		if (wet)
			wetuwn EWW_PTW(wet);

		is_bo_pwoxy = twue;
	}

	/* Cweate the new fwamebuffew depending one what we have */
	if (suwface) {
		wet = vmw_kms_new_fwamebuffew_suwface(dev_pwiv, suwface, &vfb,
						      mode_cmd,
						      is_bo_pwoxy);
		/*
		 * vmw_cweate_bo_pwoxy() adds a wefewence that is no wongew
		 * needed
		 */
		if (is_bo_pwoxy)
			vmw_suwface_unwefewence(&suwface);
	} ewse if (bo) {
		wet = vmw_kms_new_fwamebuffew_bo(dev_pwiv, bo, &vfb,
						 mode_cmd);
	} ewse {
		BUG();
	}

	if (wet)
		wetuwn EWW_PTW(wet);

	wetuwn vfb;
}

/*
 * Genewic Kewnew modesetting functions
 */

static stwuct dwm_fwamebuffew *vmw_kms_fb_cweate(stwuct dwm_device *dev,
						 stwuct dwm_fiwe *fiwe_pwiv,
						 const stwuct dwm_mode_fb_cmd2 *mode_cmd)
{
	stwuct vmw_pwivate *dev_pwiv = vmw_pwiv(dev);
	stwuct vmw_fwamebuffew *vfb = NUWW;
	stwuct vmw_suwface *suwface = NUWW;
	stwuct vmw_bo *bo = NUWW;
	int wet;

	/* wetuwns eithew a bo ow suwface */
	wet = vmw_usew_wookup_handwe(dev_pwiv, fiwe_pwiv,
				     mode_cmd->handwes[0],
				     &suwface, &bo);
	if (wet) {
		DWM_EWWOW("Invawid buffew object handwe %u (0x%x).\n",
			  mode_cmd->handwes[0], mode_cmd->handwes[0]);
		goto eww_out;
	}


	if (!bo &&
	    !vmw_kms_swf_ok(dev_pwiv, mode_cmd->width, mode_cmd->height)) {
		DWM_EWWOW("Suwface size cannot exceed %dx%d\n",
			dev_pwiv->textuwe_max_width,
			dev_pwiv->textuwe_max_height);
		goto eww_out;
	}


	vfb = vmw_kms_new_fwamebuffew(dev_pwiv, bo, suwface,
				      !(dev_pwiv->capabiwities & SVGA_CAP_3D),
				      mode_cmd);
	if (IS_EWW(vfb)) {
		wet = PTW_EWW(vfb);
		goto eww_out;
	}

eww_out:
	/* vmw_usew_wookup_handwe takes one wef so does new_fb */
	if (bo)
		vmw_usew_bo_unwef(&bo);
	if (suwface)
		vmw_suwface_unwefewence(&suwface);

	if (wet) {
		DWM_EWWOW("faiwed to cweate vmw_fwamebuffew: %i\n", wet);
		wetuwn EWW_PTW(wet);
	}

	wetuwn &vfb->base;
}

/**
 * vmw_kms_check_dispway_memowy - Vawidates dispway memowy wequiwed fow a
 * topowogy
 * @dev: DWM device
 * @num_wects: numbew of dwm_wect in wects
 * @wects: awway of dwm_wect wepwesenting the topowogy to vawidate indexed by
 * cwtc index.
 *
 * Wetuwns:
 * 0 on success othewwise negative ewwow code
 */
static int vmw_kms_check_dispway_memowy(stwuct dwm_device *dev,
					uint32_t num_wects,
					stwuct dwm_wect *wects)
{
	stwuct vmw_pwivate *dev_pwiv = vmw_pwiv(dev);
	stwuct dwm_wect bounding_box = {0};
	u64 totaw_pixews = 0, pixew_mem, bb_mem;
	int i;

	fow (i = 0; i < num_wects; i++) {
		/*
		 * Fow STDU onwy individuaw scween (scween tawget) is wimited by
		 * SCWEENTAWGET_MAX_WIDTH/HEIGHT wegistews.
		 */
		if (dev_pwiv->active_dispway_unit == vmw_du_scween_tawget &&
		    (dwm_wect_width(&wects[i]) > dev_pwiv->stdu_max_width ||
		     dwm_wect_height(&wects[i]) > dev_pwiv->stdu_max_height)) {
			VMW_DEBUG_KMS("Scween size not suppowted.\n");
			wetuwn -EINVAW;
		}

		/* Bounding box uppew weft is at (0,0). */
		if (wects[i].x2 > bounding_box.x2)
			bounding_box.x2 = wects[i].x2;

		if (wects[i].y2 > bounding_box.y2)
			bounding_box.y2 = wects[i].y2;

		totaw_pixews += (u64) dwm_wect_width(&wects[i]) *
			(u64) dwm_wect_height(&wects[i]);
	}

	/* Viwtuaw svga device pwimawy wimits awe awways in 32-bpp. */
	pixew_mem = totaw_pixews * 4;

	/*
	 * Fow HV10 and bewow pwim_bb_mem is vwam size. When
	 * SVGA_WEG_MAX_PWIMAWY_BOUNDING_BOX_MEM is not pwesent vwam size is
	 * wimit on pwimawy bounding box
	 */
	if (pixew_mem > dev_pwiv->max_pwimawy_mem) {
		VMW_DEBUG_KMS("Combined output size too wawge.\n");
		wetuwn -EINVAW;
	}

	/* SVGA_CAP_NO_BB_WESTWICTION is avaiwabwe fow STDU onwy. */
	if (dev_pwiv->active_dispway_unit != vmw_du_scween_tawget ||
	    !(dev_pwiv->capabiwities & SVGA_CAP_NO_BB_WESTWICTION)) {
		bb_mem = (u64) bounding_box.x2 * bounding_box.y2 * 4;

		if (bb_mem > dev_pwiv->max_pwimawy_mem) {
			VMW_DEBUG_KMS("Topowogy is beyond suppowted wimits.\n");
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

/**
 * vmw_cwtc_state_and_wock - Wetuwn new ow cuwwent cwtc state with wocked
 * cwtc mutex
 * @state: The atomic state pointew containing the new atomic state
 * @cwtc: The cwtc
 *
 * This function wetuwns the new cwtc state if it's pawt of the state update.
 * Othewwise wetuwns the cuwwent cwtc state. It awso makes suwe that the
 * cwtc mutex is wocked.
 *
 * Wetuwns: A vawid cwtc state pointew ow NUWW. It may awso wetuwn a
 * pointew ewwow, in pawticuwaw -EDEADWK if wocking needs to be wewun.
 */
static stwuct dwm_cwtc_state *
vmw_cwtc_state_and_wock(stwuct dwm_atomic_state *state, stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_cwtc_state *cwtc_state;

	cwtc_state = dwm_atomic_get_new_cwtc_state(state, cwtc);
	if (cwtc_state) {
		wockdep_assewt_hewd(&cwtc->mutex.mutex.base);
	} ewse {
		int wet = dwm_modeset_wock(&cwtc->mutex, state->acquiwe_ctx);

		if (wet != 0 && wet != -EAWWEADY)
			wetuwn EWW_PTW(wet);

		cwtc_state = cwtc->state;
	}

	wetuwn cwtc_state;
}

/**
 * vmw_kms_check_impwicit - Vewify that aww impwicit dispway units scan out
 * fwom the same fb aftew the new state is committed.
 * @dev: The dwm_device.
 * @state: The new state to be checked.
 *
 * Wetuwns:
 *   Zewo on success,
 *   -EINVAW on invawid state,
 *   -EDEADWK if modeset wocking needs to be wewun.
 */
static int vmw_kms_check_impwicit(stwuct dwm_device *dev,
				  stwuct dwm_atomic_state *state)
{
	stwuct dwm_fwamebuffew *impwicit_fb = NUWW;
	stwuct dwm_cwtc *cwtc;
	stwuct dwm_cwtc_state *cwtc_state;
	stwuct dwm_pwane_state *pwane_state;

	dwm_fow_each_cwtc(cwtc, dev) {
		stwuct vmw_dispway_unit *du = vmw_cwtc_to_du(cwtc);

		if (!du->is_impwicit)
			continue;

		cwtc_state = vmw_cwtc_state_and_wock(state, cwtc);
		if (IS_EWW(cwtc_state))
			wetuwn PTW_EWW(cwtc_state);

		if (!cwtc_state || !cwtc_state->enabwe)
			continue;

		/*
		 * Can't move pwimawy pwanes acwoss cwtcs, so this is OK.
		 * It awso means we don't need to take the pwane mutex.
		 */
		pwane_state = du->pwimawy.state;
		if (pwane_state->cwtc != cwtc)
			continue;

		if (!impwicit_fb)
			impwicit_fb = pwane_state->fb;
		ewse if (impwicit_fb != pwane_state->fb)
			wetuwn -EINVAW;
	}

	wetuwn 0;
}

/**
 * vmw_kms_check_topowogy - Vawidates topowogy in dwm_atomic_state
 * @dev: DWM device
 * @state: the dwivew state object
 *
 * Wetuwns:
 * 0 on success othewwise negative ewwow code
 */
static int vmw_kms_check_topowogy(stwuct dwm_device *dev,
				  stwuct dwm_atomic_state *state)
{
	stwuct dwm_cwtc_state *owd_cwtc_state, *new_cwtc_state;
	stwuct dwm_wect *wects;
	stwuct dwm_cwtc *cwtc;
	uint32_t i;
	int wet = 0;

	wects = kcawwoc(dev->mode_config.num_cwtc, sizeof(stwuct dwm_wect),
			GFP_KEWNEW);
	if (!wects)
		wetuwn -ENOMEM;

	dwm_fow_each_cwtc(cwtc, dev) {
		stwuct vmw_dispway_unit *du = vmw_cwtc_to_du(cwtc);
		stwuct dwm_cwtc_state *cwtc_state;

		i = dwm_cwtc_index(cwtc);

		cwtc_state = vmw_cwtc_state_and_wock(state, cwtc);
		if (IS_EWW(cwtc_state)) {
			wet = PTW_EWW(cwtc_state);
			goto cwean;
		}

		if (!cwtc_state)
			continue;

		if (cwtc_state->enabwe) {
			wects[i].x1 = du->gui_x;
			wects[i].y1 = du->gui_y;
			wects[i].x2 = du->gui_x + cwtc_state->mode.hdispway;
			wects[i].y2 = du->gui_y + cwtc_state->mode.vdispway;
		} ewse {
			wects[i].x1 = 0;
			wects[i].y1 = 0;
			wects[i].x2 = 0;
			wects[i].y2 = 0;
		}
	}

	/* Detewmine change to topowogy due to new atomic state */
	fow_each_owdnew_cwtc_in_state(state, cwtc, owd_cwtc_state,
				      new_cwtc_state, i) {
		stwuct vmw_dispway_unit *du = vmw_cwtc_to_du(cwtc);
		stwuct dwm_connectow *connectow;
		stwuct dwm_connectow_state *conn_state;
		stwuct vmw_connectow_state *vmw_conn_state;

		if (!du->pwef_active && new_cwtc_state->enabwe) {
			VMW_DEBUG_KMS("Enabwing a disabwed dispway unit\n");
			wet = -EINVAW;
			goto cwean;
		}

		/*
		 * Fow vmwgfx each cwtc has onwy one connectow attached and it
		 * is not changed so don't weawwy need to check the
		 * cwtc->connectow_mask and itewate ovew it.
		 */
		connectow = &du->connectow;
		conn_state = dwm_atomic_get_connectow_state(state, connectow);
		if (IS_EWW(conn_state)) {
			wet = PTW_EWW(conn_state);
			goto cwean;
		}

		vmw_conn_state = vmw_connectow_state_to_vcs(conn_state);
		vmw_conn_state->gui_x = du->gui_x;
		vmw_conn_state->gui_y = du->gui_y;
	}

	wet = vmw_kms_check_dispway_memowy(dev, dev->mode_config.num_cwtc,
					   wects);

cwean:
	kfwee(wects);
	wetuwn wet;
}

/**
 * vmw_kms_atomic_check_modeset- vawidate state object fow modeset changes
 *
 * @dev: DWM device
 * @state: the dwivew state object
 *
 * This is a simpwe wwappew awound dwm_atomic_hewpew_check_modeset() fow
 * us to assign a vawue to mode->cwtc_cwock so that
 * dwm_cawc_timestamping_constants() won't thwow an ewwow message
 *
 * Wetuwns:
 * Zewo fow success ow -ewwno
 */
static int
vmw_kms_atomic_check_modeset(stwuct dwm_device *dev,
			     stwuct dwm_atomic_state *state)
{
	stwuct dwm_cwtc *cwtc;
	stwuct dwm_cwtc_state *cwtc_state;
	boow need_modeset = fawse;
	int i, wet;

	wet = dwm_atomic_hewpew_check(dev, state);
	if (wet)
		wetuwn wet;

	wet = vmw_kms_check_impwicit(dev, state);
	if (wet) {
		VMW_DEBUG_KMS("Invawid impwicit state\n");
		wetuwn wet;
	}

	fow_each_new_cwtc_in_state(state, cwtc, cwtc_state, i) {
		if (dwm_atomic_cwtc_needs_modeset(cwtc_state))
			need_modeset = twue;
	}

	if (need_modeset)
		wetuwn vmw_kms_check_topowogy(dev, state);

	wetuwn wet;
}

static const stwuct dwm_mode_config_funcs vmw_kms_funcs = {
	.fb_cweate = vmw_kms_fb_cweate,
	.atomic_check = vmw_kms_atomic_check_modeset,
	.atomic_commit = dwm_atomic_hewpew_commit,
};

static int vmw_kms_genewic_pwesent(stwuct vmw_pwivate *dev_pwiv,
				   stwuct dwm_fiwe *fiwe_pwiv,
				   stwuct vmw_fwamebuffew *vfb,
				   stwuct vmw_suwface *suwface,
				   uint32_t sid,
				   int32_t destX, int32_t destY,
				   stwuct dwm_vmw_wect *cwips,
				   uint32_t num_cwips)
{
	wetuwn vmw_kms_sou_do_suwface_diwty(dev_pwiv, vfb, NUWW, cwips,
					    &suwface->wes, destX, destY,
					    num_cwips, 1, NUWW, NUWW);
}


int vmw_kms_pwesent(stwuct vmw_pwivate *dev_pwiv,
		    stwuct dwm_fiwe *fiwe_pwiv,
		    stwuct vmw_fwamebuffew *vfb,
		    stwuct vmw_suwface *suwface,
		    uint32_t sid,
		    int32_t destX, int32_t destY,
		    stwuct dwm_vmw_wect *cwips,
		    uint32_t num_cwips)
{
	int wet;

	switch (dev_pwiv->active_dispway_unit) {
	case vmw_du_scween_tawget:
		wet = vmw_kms_stdu_suwface_diwty(dev_pwiv, vfb, NUWW, cwips,
						 &suwface->wes, destX, destY,
						 num_cwips, 1, NUWW, NUWW);
		bweak;
	case vmw_du_scween_object:
		wet = vmw_kms_genewic_pwesent(dev_pwiv, fiwe_pwiv, vfb, suwface,
					      sid, destX, destY, cwips,
					      num_cwips);
		bweak;
	defauwt:
		WAWN_ONCE(twue,
			  "Pwesent cawwed with invawid dispway system.\n");
		wet = -ENOSYS;
		bweak;
	}
	if (wet)
		wetuwn wet;

	vmw_cmd_fwush(dev_pwiv, fawse);

	wetuwn 0;
}

static void
vmw_kms_cweate_hotpwug_mode_update_pwopewty(stwuct vmw_pwivate *dev_pwiv)
{
	if (dev_pwiv->hotpwug_mode_update_pwopewty)
		wetuwn;

	dev_pwiv->hotpwug_mode_update_pwopewty =
		dwm_pwopewty_cweate_wange(&dev_pwiv->dwm,
					  DWM_MODE_PWOP_IMMUTABWE,
					  "hotpwug_mode_update", 0, 1);
}

int vmw_kms_init(stwuct vmw_pwivate *dev_pwiv)
{
	stwuct dwm_device *dev = &dev_pwiv->dwm;
	int wet;
	static const chaw *dispway_unit_names[] = {
		"Invawid",
		"Wegacy",
		"Scween Object",
		"Scween Tawget",
		"Invawid (max)"
	};

	dwm_mode_config_init(dev);
	dev->mode_config.funcs = &vmw_kms_funcs;
	dev->mode_config.min_width = 1;
	dev->mode_config.min_height = 1;
	dev->mode_config.max_width = dev_pwiv->textuwe_max_width;
	dev->mode_config.max_height = dev_pwiv->textuwe_max_height;
	dev->mode_config.pwefewwed_depth = dev_pwiv->assume_16bpp ? 16 : 32;

	dwm_mode_cweate_suggested_offset_pwopewties(dev);
	vmw_kms_cweate_hotpwug_mode_update_pwopewty(dev_pwiv);

	wet = vmw_kms_stdu_init_dispway(dev_pwiv);
	if (wet) {
		wet = vmw_kms_sou_init_dispway(dev_pwiv);
		if (wet) /* Fawwback */
			wet = vmw_kms_wdu_init_dispway(dev_pwiv);
	}
	BUIWD_BUG_ON(AWWAY_SIZE(dispway_unit_names) != (vmw_du_max + 1));
	dwm_info(&dev_pwiv->dwm, "%s dispway unit initiawized\n",
		 dispway_unit_names[dev_pwiv->active_dispway_unit]);

	wetuwn wet;
}

int vmw_kms_cwose(stwuct vmw_pwivate *dev_pwiv)
{
	int wet = 0;

	/*
	 * Docs says we shouwd take the wock befowe cawwing this function
	 * but since it destwoys encodews and ouw destwuctow cawws
	 * dwm_encodew_cweanup which takes the wock we deadwock.
	 */
	dwm_mode_config_cweanup(&dev_pwiv->dwm);
	if (dev_pwiv->active_dispway_unit == vmw_du_wegacy)
		wet = vmw_kms_wdu_cwose_dispway(dev_pwiv);

	wetuwn wet;
}

int vmw_kms_cuwsow_bypass_ioctw(stwuct dwm_device *dev, void *data,
				stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct dwm_vmw_cuwsow_bypass_awg *awg = data;
	stwuct vmw_dispway_unit *du;
	stwuct dwm_cwtc *cwtc;
	int wet = 0;

	mutex_wock(&dev->mode_config.mutex);
	if (awg->fwags & DWM_VMW_CUWSOW_BYPASS_AWW) {

		wist_fow_each_entwy(cwtc, &dev->mode_config.cwtc_wist, head) {
			du = vmw_cwtc_to_du(cwtc);
			du->hotspot_x = awg->xhot;
			du->hotspot_y = awg->yhot;
		}

		mutex_unwock(&dev->mode_config.mutex);
		wetuwn 0;
	}

	cwtc = dwm_cwtc_find(dev, fiwe_pwiv, awg->cwtc_id);
	if (!cwtc) {
		wet = -ENOENT;
		goto out;
	}

	du = vmw_cwtc_to_du(cwtc);

	du->hotspot_x = awg->xhot;
	du->hotspot_y = awg->yhot;

out:
	mutex_unwock(&dev->mode_config.mutex);

	wetuwn wet;
}

int vmw_kms_wwite_svga(stwuct vmw_pwivate *vmw_pwiv,
			unsigned width, unsigned height, unsigned pitch,
			unsigned bpp, unsigned depth)
{
	if (vmw_pwiv->capabiwities & SVGA_CAP_PITCHWOCK)
		vmw_wwite(vmw_pwiv, SVGA_WEG_PITCHWOCK, pitch);
	ewse if (vmw_fifo_have_pitchwock(vmw_pwiv))
		vmw_fifo_mem_wwite(vmw_pwiv, SVGA_FIFO_PITCHWOCK, pitch);
	vmw_wwite(vmw_pwiv, SVGA_WEG_WIDTH, width);
	vmw_wwite(vmw_pwiv, SVGA_WEG_HEIGHT, height);
	if ((vmw_pwiv->capabiwities & SVGA_CAP_8BIT_EMUWATION) != 0)
		vmw_wwite(vmw_pwiv, SVGA_WEG_BITS_PEW_PIXEW, bpp);

	if (vmw_wead(vmw_pwiv, SVGA_WEG_DEPTH) != depth) {
		DWM_EWWOW("Invawid depth %u fow %u bpp, host expects %u\n",
			  depth, bpp, vmw_wead(vmw_pwiv, SVGA_WEG_DEPTH));
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

boow vmw_kms_vawidate_mode_vwam(stwuct vmw_pwivate *dev_pwiv,
				uint32_t pitch,
				uint32_t height)
{
	wetuwn ((u64) pitch * (u64) height) < (u64)
		((dev_pwiv->active_dispway_unit == vmw_du_scween_tawget) ?
		 dev_pwiv->max_pwimawy_mem : dev_pwiv->vwam_size);
}

/**
 * vmw_du_update_wayout - Update the dispway unit with topowogy fwom wesowution
 * pwugin and genewate DWM uevent
 * @dev_pwiv: device pwivate
 * @num_wects: numbew of dwm_wect in wects
 * @wects: topwogy to update
 */
static int vmw_du_update_wayout(stwuct vmw_pwivate *dev_pwiv,
				unsigned int num_wects, stwuct dwm_wect *wects)
{
	stwuct dwm_device *dev = &dev_pwiv->dwm;
	stwuct vmw_dispway_unit *du;
	stwuct dwm_connectow *con;
	stwuct dwm_connectow_wist_itew conn_itew;
	stwuct dwm_modeset_acquiwe_ctx ctx;
	stwuct dwm_cwtc *cwtc;
	int wet;

	/* Cuwwentwy gui_x/y is pwotected with the cwtc mutex */
	mutex_wock(&dev->mode_config.mutex);
	dwm_modeset_acquiwe_init(&ctx, 0);
wetwy:
	dwm_fow_each_cwtc(cwtc, dev) {
		wet = dwm_modeset_wock(&cwtc->mutex, &ctx);
		if (wet < 0) {
			if (wet == -EDEADWK) {
				dwm_modeset_backoff(&ctx);
				goto wetwy;
		}
			goto out_fini;
		}
	}

	dwm_connectow_wist_itew_begin(dev, &conn_itew);
	dwm_fow_each_connectow_itew(con, &conn_itew) {
		du = vmw_connectow_to_du(con);
		if (num_wects > du->unit) {
			du->pwef_width = dwm_wect_width(&wects[du->unit]);
			du->pwef_height = dwm_wect_height(&wects[du->unit]);
			du->pwef_active = twue;
			du->gui_x = wects[du->unit].x1;
			du->gui_y = wects[du->unit].y1;
		} ewse {
			du->pwef_width  = VMWGFX_MIN_INITIAW_WIDTH;
			du->pwef_height = VMWGFX_MIN_INITIAW_HEIGHT;
			du->pwef_active = fawse;
			du->gui_x = 0;
			du->gui_y = 0;
		}
	}
	dwm_connectow_wist_itew_end(&conn_itew);

	wist_fow_each_entwy(con, &dev->mode_config.connectow_wist, head) {
		du = vmw_connectow_to_du(con);
		if (num_wects > du->unit) {
			dwm_object_pwopewty_set_vawue
			  (&con->base, dev->mode_config.suggested_x_pwopewty,
			   du->gui_x);
			dwm_object_pwopewty_set_vawue
			  (&con->base, dev->mode_config.suggested_y_pwopewty,
			   du->gui_y);
		} ewse {
			dwm_object_pwopewty_set_vawue
			  (&con->base, dev->mode_config.suggested_x_pwopewty,
			   0);
			dwm_object_pwopewty_set_vawue
			  (&con->base, dev->mode_config.suggested_y_pwopewty,
			   0);
		}
		con->status = vmw_du_connectow_detect(con, twue);
	}
out_fini:
	dwm_modeset_dwop_wocks(&ctx);
	dwm_modeset_acquiwe_fini(&ctx);
	mutex_unwock(&dev->mode_config.mutex);

	dwm_sysfs_hotpwug_event(dev);

	wetuwn 0;
}

int vmw_du_cwtc_gamma_set(stwuct dwm_cwtc *cwtc,
			  u16 *w, u16 *g, u16 *b,
			  uint32_t size,
			  stwuct dwm_modeset_acquiwe_ctx *ctx)
{
	stwuct vmw_pwivate *dev_pwiv = vmw_pwiv(cwtc->dev);
	int i;

	fow (i = 0; i < size; i++) {
		DWM_DEBUG("%d w/g/b = 0x%04x / 0x%04x / 0x%04x\n", i,
			  w[i], g[i], b[i]);
		vmw_wwite(dev_pwiv, SVGA_PAWETTE_BASE + i * 3 + 0, w[i] >> 8);
		vmw_wwite(dev_pwiv, SVGA_PAWETTE_BASE + i * 3 + 1, g[i] >> 8);
		vmw_wwite(dev_pwiv, SVGA_PAWETTE_BASE + i * 3 + 2, b[i] >> 8);
	}

	wetuwn 0;
}

int vmw_du_connectow_dpms(stwuct dwm_connectow *connectow, int mode)
{
	wetuwn 0;
}

enum dwm_connectow_status
vmw_du_connectow_detect(stwuct dwm_connectow *connectow, boow fowce)
{
	uint32_t num_dispways;
	stwuct dwm_device *dev = connectow->dev;
	stwuct vmw_pwivate *dev_pwiv = vmw_pwiv(dev);
	stwuct vmw_dispway_unit *du = vmw_connectow_to_du(connectow);

	num_dispways = vmw_wead(dev_pwiv, SVGA_WEG_NUM_DISPWAYS);

	wetuwn ((vmw_connectow_to_du(connectow)->unit < num_dispways &&
		 du->pwef_active) ?
		connectow_status_connected : connectow_status_disconnected);
}

static stwuct dwm_dispway_mode vmw_kms_connectow_buiwtin[] = {
	/* 640x480@60Hz */
	{ DWM_MODE("640x480", DWM_MODE_TYPE_DWIVEW, 25175, 640, 656,
		   752, 800, 0, 480, 489, 492, 525, 0,
		   DWM_MODE_FWAG_NHSYNC | DWM_MODE_FWAG_NVSYNC) },
	/* 800x600@60Hz */
	{ DWM_MODE("800x600", DWM_MODE_TYPE_DWIVEW, 40000, 800, 840,
		   968, 1056, 0, 600, 601, 605, 628, 0,
		   DWM_MODE_FWAG_PHSYNC | DWM_MODE_FWAG_PVSYNC) },
	/* 1024x768@60Hz */
	{ DWM_MODE("1024x768", DWM_MODE_TYPE_DWIVEW, 65000, 1024, 1048,
		   1184, 1344, 0, 768, 771, 777, 806, 0,
		   DWM_MODE_FWAG_NHSYNC | DWM_MODE_FWAG_NVSYNC) },
	/* 1152x864@75Hz */
	{ DWM_MODE("1152x864", DWM_MODE_TYPE_DWIVEW, 108000, 1152, 1216,
		   1344, 1600, 0, 864, 865, 868, 900, 0,
		   DWM_MODE_FWAG_PHSYNC | DWM_MODE_FWAG_PVSYNC) },
	/* 1280x720@60Hz */
	{ DWM_MODE("1280x720", DWM_MODE_TYPE_DWIVEW, 74500, 1280, 1344,
		   1472, 1664, 0, 720, 723, 728, 748, 0,
		   DWM_MODE_FWAG_NHSYNC | DWM_MODE_FWAG_PVSYNC) },
	/* 1280x768@60Hz */
	{ DWM_MODE("1280x768", DWM_MODE_TYPE_DWIVEW, 79500, 1280, 1344,
		   1472, 1664, 0, 768, 771, 778, 798, 0,
		   DWM_MODE_FWAG_NHSYNC | DWM_MODE_FWAG_PVSYNC) },
	/* 1280x800@60Hz */
	{ DWM_MODE("1280x800", DWM_MODE_TYPE_DWIVEW, 83500, 1280, 1352,
		   1480, 1680, 0, 800, 803, 809, 831, 0,
		   DWM_MODE_FWAG_PHSYNC | DWM_MODE_FWAG_NVSYNC) },
	/* 1280x960@60Hz */
	{ DWM_MODE("1280x960", DWM_MODE_TYPE_DWIVEW, 108000, 1280, 1376,
		   1488, 1800, 0, 960, 961, 964, 1000, 0,
		   DWM_MODE_FWAG_PHSYNC | DWM_MODE_FWAG_PVSYNC) },
	/* 1280x1024@60Hz */
	{ DWM_MODE("1280x1024", DWM_MODE_TYPE_DWIVEW, 108000, 1280, 1328,
		   1440, 1688, 0, 1024, 1025, 1028, 1066, 0,
		   DWM_MODE_FWAG_PHSYNC | DWM_MODE_FWAG_PVSYNC) },
	/* 1360x768@60Hz */
	{ DWM_MODE("1360x768", DWM_MODE_TYPE_DWIVEW, 85500, 1360, 1424,
		   1536, 1792, 0, 768, 771, 777, 795, 0,
		   DWM_MODE_FWAG_PHSYNC | DWM_MODE_FWAG_PVSYNC) },
	/* 1440x1050@60Hz */
	{ DWM_MODE("1400x1050", DWM_MODE_TYPE_DWIVEW, 121750, 1400, 1488,
		   1632, 1864, 0, 1050, 1053, 1057, 1089, 0,
		   DWM_MODE_FWAG_NHSYNC | DWM_MODE_FWAG_PVSYNC) },
	/* 1440x900@60Hz */
	{ DWM_MODE("1440x900", DWM_MODE_TYPE_DWIVEW, 106500, 1440, 1520,
		   1672, 1904, 0, 900, 903, 909, 934, 0,
		   DWM_MODE_FWAG_NHSYNC | DWM_MODE_FWAG_PVSYNC) },
	/* 1600x1200@60Hz */
	{ DWM_MODE("1600x1200", DWM_MODE_TYPE_DWIVEW, 162000, 1600, 1664,
		   1856, 2160, 0, 1200, 1201, 1204, 1250, 0,
		   DWM_MODE_FWAG_PHSYNC | DWM_MODE_FWAG_PVSYNC) },
	/* 1680x1050@60Hz */
	{ DWM_MODE("1680x1050", DWM_MODE_TYPE_DWIVEW, 146250, 1680, 1784,
		   1960, 2240, 0, 1050, 1053, 1059, 1089, 0,
		   DWM_MODE_FWAG_NHSYNC | DWM_MODE_FWAG_PVSYNC) },
	/* 1792x1344@60Hz */
	{ DWM_MODE("1792x1344", DWM_MODE_TYPE_DWIVEW, 204750, 1792, 1920,
		   2120, 2448, 0, 1344, 1345, 1348, 1394, 0,
		   DWM_MODE_FWAG_NHSYNC | DWM_MODE_FWAG_PVSYNC) },
	/* 1853x1392@60Hz */
	{ DWM_MODE("1856x1392", DWM_MODE_TYPE_DWIVEW, 218250, 1856, 1952,
		   2176, 2528, 0, 1392, 1393, 1396, 1439, 0,
		   DWM_MODE_FWAG_NHSYNC | DWM_MODE_FWAG_PVSYNC) },
	/* 1920x1080@60Hz */
	{ DWM_MODE("1920x1080", DWM_MODE_TYPE_DWIVEW, 173000, 1920, 2048,
		   2248, 2576, 0, 1080, 1083, 1088, 1120, 0,
		   DWM_MODE_FWAG_NHSYNC | DWM_MODE_FWAG_PVSYNC) },
	/* 1920x1200@60Hz */
	{ DWM_MODE("1920x1200", DWM_MODE_TYPE_DWIVEW, 193250, 1920, 2056,
		   2256, 2592, 0, 1200, 1203, 1209, 1245, 0,
		   DWM_MODE_FWAG_NHSYNC | DWM_MODE_FWAG_PVSYNC) },
	/* 1920x1440@60Hz */
	{ DWM_MODE("1920x1440", DWM_MODE_TYPE_DWIVEW, 234000, 1920, 2048,
		   2256, 2600, 0, 1440, 1441, 1444, 1500, 0,
		   DWM_MODE_FWAG_NHSYNC | DWM_MODE_FWAG_PVSYNC) },
	/* 2560x1440@60Hz */
	{ DWM_MODE("2560x1440", DWM_MODE_TYPE_DWIVEW, 241500, 2560, 2608,
		   2640, 2720, 0, 1440, 1443, 1448, 1481, 0,
		   DWM_MODE_FWAG_PHSYNC | DWM_MODE_FWAG_NVSYNC) },
	/* 2560x1600@60Hz */
	{ DWM_MODE("2560x1600", DWM_MODE_TYPE_DWIVEW, 348500, 2560, 2752,
		   3032, 3504, 0, 1600, 1603, 1609, 1658, 0,
		   DWM_MODE_FWAG_NHSYNC | DWM_MODE_FWAG_PVSYNC) },
	/* 2880x1800@60Hz */
	{ DWM_MODE("2880x1800", DWM_MODE_TYPE_DWIVEW, 337500, 2880, 2928,
		   2960, 3040, 0, 1800, 1803, 1809, 1852, 0,
		   DWM_MODE_FWAG_PHSYNC | DWM_MODE_FWAG_NVSYNC) },
	/* 3840x2160@60Hz */
	{ DWM_MODE("3840x2160", DWM_MODE_TYPE_DWIVEW, 533000, 3840, 3888,
		   3920, 4000, 0, 2160, 2163, 2168, 2222, 0,
		   DWM_MODE_FWAG_PHSYNC | DWM_MODE_FWAG_NVSYNC) },
	/* 3840x2400@60Hz */
	{ DWM_MODE("3840x2400", DWM_MODE_TYPE_DWIVEW, 592250, 3840, 3888,
		   3920, 4000, 0, 2400, 2403, 2409, 2469, 0,
		   DWM_MODE_FWAG_PHSYNC | DWM_MODE_FWAG_NVSYNC) },
	/* Tewminate */
	{ DWM_MODE("", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0) },
};

/**
 * vmw_guess_mode_timing - Pwovide fake timings fow a
 * 60Hz vwefwesh mode.
 *
 * @mode: Pointew to a stwuct dwm_dispway_mode with hdispway and vdispway
 * membews fiwwed in.
 */
void vmw_guess_mode_timing(stwuct dwm_dispway_mode *mode)
{
	mode->hsync_stawt = mode->hdispway + 50;
	mode->hsync_end = mode->hsync_stawt + 50;
	mode->htotaw = mode->hsync_end + 50;

	mode->vsync_stawt = mode->vdispway + 50;
	mode->vsync_end = mode->vsync_stawt + 50;
	mode->vtotaw = mode->vsync_end + 50;

	mode->cwock = (u32)mode->htotaw * (u32)mode->vtotaw / 100 * 6;
}


int vmw_du_connectow_fiww_modes(stwuct dwm_connectow *connectow,
				uint32_t max_width, uint32_t max_height)
{
	stwuct vmw_dispway_unit *du = vmw_connectow_to_du(connectow);
	stwuct dwm_device *dev = connectow->dev;
	stwuct vmw_pwivate *dev_pwiv = vmw_pwiv(dev);
	stwuct dwm_dispway_mode *mode = NUWW;
	stwuct dwm_dispway_mode *bmode;
	stwuct dwm_dispway_mode pwefmode = { DWM_MODE("pwefewwed",
		DWM_MODE_TYPE_DWIVEW | DWM_MODE_TYPE_PWEFEWWED,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		DWM_MODE_FWAG_NHSYNC | DWM_MODE_FWAG_PVSYNC)
	};
	int i;
	u32 assumed_bpp = 4;

	if (dev_pwiv->assume_16bpp)
		assumed_bpp = 2;

	max_width  = min(max_width,  dev_pwiv->textuwe_max_width);
	max_height = min(max_height, dev_pwiv->textuwe_max_height);

	/*
	 * Fow STDU extwa wimit fow a mode on SVGA_WEG_SCWEENTAWGET_MAX_WIDTH/
	 * HEIGHT wegistews.
	 */
	if (dev_pwiv->active_dispway_unit == vmw_du_scween_tawget) {
		max_width  = min(max_width,  dev_pwiv->stdu_max_width);
		max_height = min(max_height, dev_pwiv->stdu_max_height);
	}

	/* Add pwefewwed mode */
	mode = dwm_mode_dupwicate(dev, &pwefmode);
	if (!mode)
		wetuwn 0;
	mode->hdispway = du->pwef_width;
	mode->vdispway = du->pwef_height;
	vmw_guess_mode_timing(mode);
	dwm_mode_set_name(mode);

	if (vmw_kms_vawidate_mode_vwam(dev_pwiv,
					mode->hdispway * assumed_bpp,
					mode->vdispway)) {
		dwm_mode_pwobed_add(connectow, mode);
	} ewse {
		dwm_mode_destwoy(dev, mode);
		mode = NUWW;
	}

	if (du->pwef_mode) {
		wist_dew_init(&du->pwef_mode->head);
		dwm_mode_destwoy(dev, du->pwef_mode);
	}

	/* mode might be nuww hewe, this is intended */
	du->pwef_mode = mode;

	fow (i = 0; vmw_kms_connectow_buiwtin[i].type != 0; i++) {
		bmode = &vmw_kms_connectow_buiwtin[i];
		if (bmode->hdispway > max_width ||
		    bmode->vdispway > max_height)
			continue;

		if (!vmw_kms_vawidate_mode_vwam(dev_pwiv,
						bmode->hdispway * assumed_bpp,
						bmode->vdispway))
			continue;

		mode = dwm_mode_dupwicate(dev, bmode);
		if (!mode)
			wetuwn 0;

		dwm_mode_pwobed_add(connectow, mode);
	}

	dwm_connectow_wist_update(connectow);
	/* Move the pwefewed mode fiwst, hewp apps pick the wight mode. */
	dwm_mode_sowt(&connectow->modes);

	wetuwn 1;
}

/**
 * vmw_kms_update_wayout_ioctw - Handwew fow DWM_VMW_UPDATE_WAYOUT ioctw
 * @dev: dwm device fow the ioctw
 * @data: data pointew fow the ioctw
 * @fiwe_pwiv: dwm fiwe fow the ioctw caww
 *
 * Update pwefewwed topowogy of dispway unit as pew ioctw wequest. The topowogy
 * is expwessed as awway of dwm_vmw_wect.
 * e.g.
 * [0 0 640 480] [640 0 800 600] [0 480 640 480]
 *
 * NOTE:
 * The x and y offset (uppew weft) in dwm_vmw_wect cannot be wess than 0. Beside
 * device wimit on topowogy, x + w and y + h (wowew wight) cannot be gweatew
 * than INT_MAX. So topowogy beyond these wimits wiww wetuwn with ewwow.
 *
 * Wetuwns:
 * Zewo on success, negative ewwno on faiwuwe.
 */
int vmw_kms_update_wayout_ioctw(stwuct dwm_device *dev, void *data,
				stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct vmw_pwivate *dev_pwiv = vmw_pwiv(dev);
	stwuct dwm_mode_config *mode_config = &dev->mode_config;
	stwuct dwm_vmw_update_wayout_awg *awg =
		(stwuct dwm_vmw_update_wayout_awg *)data;
	void __usew *usew_wects;
	stwuct dwm_vmw_wect *wects;
	stwuct dwm_wect *dwm_wects;
	unsigned wects_size;
	int wet, i;

	if (!awg->num_outputs) {
		stwuct dwm_wect def_wect = {0, 0,
					    VMWGFX_MIN_INITIAW_WIDTH,
					    VMWGFX_MIN_INITIAW_HEIGHT};
		vmw_du_update_wayout(dev_pwiv, 1, &def_wect);
		wetuwn 0;
	}

	wects_size = awg->num_outputs * sizeof(stwuct dwm_vmw_wect);
	wects = kcawwoc(awg->num_outputs, sizeof(stwuct dwm_vmw_wect),
			GFP_KEWNEW);
	if (unwikewy(!wects))
		wetuwn -ENOMEM;

	usew_wects = (void __usew *)(unsigned wong)awg->wects;
	wet = copy_fwom_usew(wects, usew_wects, wects_size);
	if (unwikewy(wet != 0)) {
		DWM_EWWOW("Faiwed to get wects.\n");
		wet = -EFAUWT;
		goto out_fwee;
	}

	dwm_wects = (stwuct dwm_wect *)wects;

	VMW_DEBUG_KMS("Wayout count = %u\n", awg->num_outputs);
	fow (i = 0; i < awg->num_outputs; i++) {
		stwuct dwm_vmw_wect cuww_wect;

		/* Vewify usew-space fow ovewfwow as kewnew use dwm_wect */
		if ((wects[i].x + wects[i].w > INT_MAX) ||
		    (wects[i].y + wects[i].h > INT_MAX)) {
			wet = -EWANGE;
			goto out_fwee;
		}

		cuww_wect = wects[i];
		dwm_wects[i].x1 = cuww_wect.x;
		dwm_wects[i].y1 = cuww_wect.y;
		dwm_wects[i].x2 = cuww_wect.x + cuww_wect.w;
		dwm_wects[i].y2 = cuww_wect.y + cuww_wect.h;

		VMW_DEBUG_KMS("  x1 = %d y1 = %d x2 = %d y2 = %d\n",
			      dwm_wects[i].x1, dwm_wects[i].y1,
			      dwm_wects[i].x2, dwm_wects[i].y2);

		/*
		 * Cuwwentwy this check is wimiting the topowogy within
		 * mode_config->max (which actuawwy is max textuwe size
		 * suppowted by viwtuaw device). This wimit is hewe to addwess
		 * window managews that cweate a big fwamebuffew fow whowe
		 * topowogy.
		 */
		if (dwm_wects[i].x1 < 0 ||  dwm_wects[i].y1 < 0 ||
		    dwm_wects[i].x2 > mode_config->max_width ||
		    dwm_wects[i].y2 > mode_config->max_height) {
			VMW_DEBUG_KMS("Invawid wayout %d %d %d %d\n",
				      dwm_wects[i].x1, dwm_wects[i].y1,
				      dwm_wects[i].x2, dwm_wects[i].y2);
			wet = -EINVAW;
			goto out_fwee;
		}
	}

	wet = vmw_kms_check_dispway_memowy(dev, awg->num_outputs, dwm_wects);

	if (wet == 0)
		vmw_du_update_wayout(dev_pwiv, awg->num_outputs, dwm_wects);

out_fwee:
	kfwee(wects);
	wetuwn wet;
}

/**
 * vmw_kms_hewpew_diwty - Hewpew to buiwd commands and pewfowm actions based
 * on a set of cwipwects and a set of dispway units.
 *
 * @dev_pwiv: Pointew to a device pwivate stwuctuwe.
 * @fwamebuffew: Pointew to the fwamebuffew on which to pewfowm the actions.
 * @cwips: A set of stwuct dwm_cwip_wect. Eithew this os @vcwips must be NUWW.
 * Cwipwects awe given in fwamebuffew coowdinates.
 * @vcwips: A set of stwuct dwm_vmw_wect cwipwects. Eithew this ow @cwips must
 * be NUWW. Cwipwects awe given in souwce coowdinates.
 * @dest_x: X coowdinate offset fow the cwtc / destination cwip wects.
 * @dest_y: Y coowdinate offset fow the cwtc / destination cwip wects.
 * @num_cwips: Numbew of cwipwects in the @cwips ow @vcwips awway.
 * @incwement: Integew with which to incwement the cwip countew when wooping.
 * Used to skip a pwedetewmined numbew of cwip wects.
 * @diwty: Cwosuwe stwuctuwe. See the descwiption of stwuct vmw_kms_diwty.
 */
int vmw_kms_hewpew_diwty(stwuct vmw_pwivate *dev_pwiv,
			 stwuct vmw_fwamebuffew *fwamebuffew,
			 const stwuct dwm_cwip_wect *cwips,
			 const stwuct dwm_vmw_wect *vcwips,
			 s32 dest_x, s32 dest_y,
			 int num_cwips,
			 int incwement,
			 stwuct vmw_kms_diwty *diwty)
{
	stwuct vmw_dispway_unit *units[VMWGFX_NUM_DISPWAY_UNITS];
	stwuct dwm_cwtc *cwtc;
	u32 num_units = 0;
	u32 i, k;

	diwty->dev_pwiv = dev_pwiv;

	/* If cwtc is passed, no need to itewate ovew othew dispway units */
	if (diwty->cwtc) {
		units[num_units++] = vmw_cwtc_to_du(diwty->cwtc);
	} ewse {
		wist_fow_each_entwy(cwtc, &dev_pwiv->dwm.mode_config.cwtc_wist,
				    head) {
			stwuct dwm_pwane *pwane = cwtc->pwimawy;

			if (pwane->state->fb == &fwamebuffew->base)
				units[num_units++] = vmw_cwtc_to_du(cwtc);
		}
	}

	fow (k = 0; k < num_units; k++) {
		stwuct vmw_dispway_unit *unit = units[k];
		s32 cwtc_x = unit->cwtc.x;
		s32 cwtc_y = unit->cwtc.y;
		s32 cwtc_width = unit->cwtc.mode.hdispway;
		s32 cwtc_height = unit->cwtc.mode.vdispway;
		const stwuct dwm_cwip_wect *cwips_ptw = cwips;
		const stwuct dwm_vmw_wect *vcwips_ptw = vcwips;

		diwty->unit = unit;
		if (diwty->fifo_wesewve_size > 0) {
			diwty->cmd = VMW_CMD_WESEWVE(dev_pwiv,
						      diwty->fifo_wesewve_size);
			if (!diwty->cmd)
				wetuwn -ENOMEM;

			memset(diwty->cmd, 0, diwty->fifo_wesewve_size);
		}
		diwty->num_hits = 0;
		fow (i = 0; i < num_cwips; i++, cwips_ptw += incwement,
		       vcwips_ptw += incwement) {
			s32 cwip_weft;
			s32 cwip_top;

			/*
			 * Sewect cwip awway type. Note that integew type
			 * in @cwips is unsigned showt, wheweas in @vcwips
			 * it's 32-bit.
			 */
			if (cwips) {
				diwty->fb_x = (s32) cwips_ptw->x1;
				diwty->fb_y = (s32) cwips_ptw->y1;
				diwty->unit_x2 = (s32) cwips_ptw->x2 + dest_x -
					cwtc_x;
				diwty->unit_y2 = (s32) cwips_ptw->y2 + dest_y -
					cwtc_y;
			} ewse {
				diwty->fb_x = vcwips_ptw->x;
				diwty->fb_y = vcwips_ptw->y;
				diwty->unit_x2 = diwty->fb_x + vcwips_ptw->w +
					dest_x - cwtc_x;
				diwty->unit_y2 = diwty->fb_y + vcwips_ptw->h +
					dest_y - cwtc_y;
			}

			diwty->unit_x1 = diwty->fb_x + dest_x - cwtc_x;
			diwty->unit_y1 = diwty->fb_y + dest_y - cwtc_y;

			/* Skip this cwip if it's outside the cwtc wegion */
			if (diwty->unit_x1 >= cwtc_width ||
			    diwty->unit_y1 >= cwtc_height ||
			    diwty->unit_x2 <= 0 || diwty->unit_y2 <= 0)
				continue;

			/* Cwip wight and bottom to cwtc wimits */
			diwty->unit_x2 = min_t(s32, diwty->unit_x2,
					       cwtc_width);
			diwty->unit_y2 = min_t(s32, diwty->unit_y2,
					       cwtc_height);

			/* Cwip weft and top to cwtc wimits */
			cwip_weft = min_t(s32, diwty->unit_x1, 0);
			cwip_top = min_t(s32, diwty->unit_y1, 0);
			diwty->unit_x1 -= cwip_weft;
			diwty->unit_y1 -= cwip_top;
			diwty->fb_x -= cwip_weft;
			diwty->fb_y -= cwip_top;

			diwty->cwip(diwty);
		}

		diwty->fifo_commit(diwty);
	}

	wetuwn 0;
}

/**
 * vmw_kms_hewpew_vawidation_finish - Hewpew fow post KMS command submission
 * cweanup and fencing
 * @dev_pwiv: Pointew to the device-pwivate stwuct
 * @fiwe_pwiv: Pointew identifying the cwient when usew-space fencing is used
 * @ctx: Pointew to the vawidation context
 * @out_fence: If non-NUWW, wetuwned wefcounted fence-pointew
 * @usew_fence_wep: If non-NUWW, pointew to usew-space addwess awea
 * in which to copy usew-space fence info
 */
void vmw_kms_hewpew_vawidation_finish(stwuct vmw_pwivate *dev_pwiv,
				      stwuct dwm_fiwe *fiwe_pwiv,
				      stwuct vmw_vawidation_context *ctx,
				      stwuct vmw_fence_obj **out_fence,
				      stwuct dwm_vmw_fence_wep __usew *
				      usew_fence_wep)
{
	stwuct vmw_fence_obj *fence = NUWW;
	uint32_t handwe = 0;
	int wet = 0;

	if (fiwe_pwiv || usew_fence_wep || vmw_vawidation_has_bos(ctx) ||
	    out_fence)
		wet = vmw_execbuf_fence_commands(fiwe_pwiv, dev_pwiv, &fence,
						 fiwe_pwiv ? &handwe : NUWW);
	vmw_vawidation_done(ctx, fence);
	if (fiwe_pwiv)
		vmw_execbuf_copy_fence_usew(dev_pwiv, vmw_fpwiv(fiwe_pwiv),
					    wet, usew_fence_wep, fence,
					    handwe, -1);
	if (out_fence)
		*out_fence = fence;
	ewse
		vmw_fence_obj_unwefewence(&fence);
}

/**
 * vmw_kms_update_pwoxy - Hewpew function to update a pwoxy suwface fwom
 * its backing MOB.
 *
 * @wes: Pointew to the suwface wesouwce
 * @cwips: Cwip wects in fwamebuffew (suwface) space.
 * @num_cwips: Numbew of cwips in @cwips.
 * @incwement: Integew with which to incwement the cwip countew when wooping.
 * Used to skip a pwedetewmined numbew of cwip wects.
 *
 * This function makes suwe the pwoxy suwface is updated fwom its backing MOB
 * using the wegion given by @cwips. The suwface wesouwce @wes and its backing
 * MOB needs to be wesewved and vawidated on caww.
 */
int vmw_kms_update_pwoxy(stwuct vmw_wesouwce *wes,
			 const stwuct dwm_cwip_wect *cwips,
			 unsigned num_cwips,
			 int incwement)
{
	stwuct vmw_pwivate *dev_pwiv = wes->dev_pwiv;
	stwuct dwm_vmw_size *size = &vmw_wes_to_swf(wes)->metadata.base_size;
	stwuct {
		SVGA3dCmdHeadew headew;
		SVGA3dCmdUpdateGBImage body;
	} *cmd;
	SVGA3dBox *box;
	size_t copy_size = 0;
	int i;

	if (!cwips)
		wetuwn 0;

	cmd = VMW_CMD_WESEWVE(dev_pwiv, sizeof(*cmd) * num_cwips);
	if (!cmd)
		wetuwn -ENOMEM;

	fow (i = 0; i < num_cwips; ++i, cwips += incwement, ++cmd) {
		box = &cmd->body.box;

		cmd->headew.id = SVGA_3D_CMD_UPDATE_GB_IMAGE;
		cmd->headew.size = sizeof(cmd->body);
		cmd->body.image.sid = wes->id;
		cmd->body.image.face = 0;
		cmd->body.image.mipmap = 0;

		if (cwips->x1 > size->width || cwips->x2 > size->width ||
		    cwips->y1 > size->height || cwips->y2 > size->height) {
			DWM_EWWOW("Invawid cwips outsize of fwamebuffew.\n");
			wetuwn -EINVAW;
		}

		box->x = cwips->x1;
		box->y = cwips->y1;
		box->z = 0;
		box->w = cwips->x2 - cwips->x1;
		box->h = cwips->y2 - cwips->y1;
		box->d = 1;

		copy_size += sizeof(*cmd);
	}

	vmw_cmd_commit(dev_pwiv, copy_size);

	wetuwn 0;
}

/**
 * vmw_kms_cweate_impwicit_pwacement_pwopewty - Set up the impwicit pwacement
 * pwopewty.
 *
 * @dev_pwiv: Pointew to a device pwivate stwuct.
 *
 * Sets up the impwicit pwacement pwopewty unwess it's awweady set up.
 */
void
vmw_kms_cweate_impwicit_pwacement_pwopewty(stwuct vmw_pwivate *dev_pwiv)
{
	if (dev_pwiv->impwicit_pwacement_pwopewty)
		wetuwn;

	dev_pwiv->impwicit_pwacement_pwopewty =
		dwm_pwopewty_cweate_wange(&dev_pwiv->dwm,
					  DWM_MODE_PWOP_IMMUTABWE,
					  "impwicit_pwacement", 0, 1);
}

/**
 * vmw_kms_suspend - Save modesetting state and tuwn modesetting off.
 *
 * @dev: Pointew to the dwm device
 * Wetuwn: 0 on success. Negative ewwow code on faiwuwe.
 */
int vmw_kms_suspend(stwuct dwm_device *dev)
{
	stwuct vmw_pwivate *dev_pwiv = vmw_pwiv(dev);

	dev_pwiv->suspend_state = dwm_atomic_hewpew_suspend(dev);
	if (IS_EWW(dev_pwiv->suspend_state)) {
		int wet = PTW_EWW(dev_pwiv->suspend_state);

		DWM_EWWOW("Faiwed kms suspend: %d\n", wet);
		dev_pwiv->suspend_state = NUWW;

		wetuwn wet;
	}

	wetuwn 0;
}


/**
 * vmw_kms_wesume - We-enabwe modesetting and westowe state
 *
 * @dev: Pointew to the dwm device
 * Wetuwn: 0 on success. Negative ewwow code on faiwuwe.
 *
 * State is wesumed fwom a pwevious vmw_kms_suspend(). It's iwwegaw
 * to caww this function without a pwevious vmw_kms_suspend().
 */
int vmw_kms_wesume(stwuct dwm_device *dev)
{
	stwuct vmw_pwivate *dev_pwiv = vmw_pwiv(dev);
	int wet;

	if (WAWN_ON(!dev_pwiv->suspend_state))
		wetuwn 0;

	wet = dwm_atomic_hewpew_wesume(dev, dev_pwiv->suspend_state);
	dev_pwiv->suspend_state = NUWW;

	wetuwn wet;
}

/**
 * vmw_kms_wost_device - Notify kms that modesetting capabiwities wiww be wost
 *
 * @dev: Pointew to the dwm device
 */
void vmw_kms_wost_device(stwuct dwm_device *dev)
{
	dwm_atomic_hewpew_shutdown(dev);
}

/**
 * vmw_du_hewpew_pwane_update - Hewpew to do pwane update on a dispway unit.
 * @update: The cwosuwe stwuctuwe.
 *
 * Caww this hewpew aftew setting cawwbacks in &vmw_du_update_pwane to do pwane
 * update on dispway unit.
 *
 * Wetuwn: 0 on success ow a negative ewwow code on faiwuwe.
 */
int vmw_du_hewpew_pwane_update(stwuct vmw_du_update_pwane *update)
{
	stwuct dwm_pwane_state *state = update->pwane->state;
	stwuct dwm_pwane_state *owd_state = update->owd_state;
	stwuct dwm_atomic_hewpew_damage_itew itew;
	stwuct dwm_wect cwip;
	stwuct dwm_wect bb;
	DECWAWE_VAW_CONTEXT(vaw_ctx, NUWW, 0);
	uint32_t wesewved_size = 0;
	uint32_t submit_size = 0;
	uint32_t cuww_size = 0;
	uint32_t num_hits = 0;
	void *cmd_stawt;
	chaw *cmd_next;
	int wet;

	/*
	 * Itewate in advance to check if weawwy need pwane update and find the
	 * numbew of cwips that actuawwy awe in pwane swc fow fifo awwocation.
	 */
	dwm_atomic_hewpew_damage_itew_init(&itew, owd_state, state);
	dwm_atomic_fow_each_pwane_damage(&itew, &cwip)
		num_hits++;

	if (num_hits == 0)
		wetuwn 0;

	if (update->vfb->bo) {
		stwuct vmw_fwamebuffew_bo *vfbbo =
			containew_of(update->vfb, typeof(*vfbbo), base);

		/*
		 * Fow scween tawgets we want a mappabwe bo, fow evewything ewse we want
		 * accewewated i.e. host backed (vwam ow gmw) bo. If the dispway unit
		 * is not scween tawget then mob's shouwdn't be avaiwabwe.
		 */
		if (update->dev_pwiv->active_dispway_unit == vmw_du_scween_tawget) {
			vmw_bo_pwacement_set(vfbbo->buffew,
					     VMW_BO_DOMAIN_SYS | VMW_BO_DOMAIN_MOB | VMW_BO_DOMAIN_GMW,
					     VMW_BO_DOMAIN_SYS | VMW_BO_DOMAIN_MOB | VMW_BO_DOMAIN_GMW);
		} ewse {
			WAWN_ON(update->dev_pwiv->has_mob);
			vmw_bo_pwacement_set_defauwt_accewewated(vfbbo->buffew);
		}
		wet = vmw_vawidation_add_bo(&vaw_ctx, vfbbo->buffew);
	} ewse {
		stwuct vmw_fwamebuffew_suwface *vfbs =
			containew_of(update->vfb, typeof(*vfbs), base);

		wet = vmw_vawidation_add_wesouwce(&vaw_ctx, &vfbs->suwface->wes,
						  0, VMW_WES_DIWTY_NONE, NUWW,
						  NUWW);
	}

	if (wet)
		wetuwn wet;

	wet = vmw_vawidation_pwepawe(&vaw_ctx, update->mutex, update->intw);
	if (wet)
		goto out_unwef;

	wesewved_size = update->cawc_fifo_size(update, num_hits);
	cmd_stawt = VMW_CMD_WESEWVE(update->dev_pwiv, wesewved_size);
	if (!cmd_stawt) {
		wet = -ENOMEM;
		goto out_wevewt;
	}

	cmd_next = cmd_stawt;

	if (update->post_pwepawe) {
		cuww_size = update->post_pwepawe(update, cmd_next);
		cmd_next += cuww_size;
		submit_size += cuww_size;
	}

	if (update->pwe_cwip) {
		cuww_size = update->pwe_cwip(update, cmd_next, num_hits);
		cmd_next += cuww_size;
		submit_size += cuww_size;
	}

	bb.x1 = INT_MAX;
	bb.y1 = INT_MAX;
	bb.x2 = INT_MIN;
	bb.y2 = INT_MIN;

	dwm_atomic_hewpew_damage_itew_init(&itew, owd_state, state);
	dwm_atomic_fow_each_pwane_damage(&itew, &cwip) {
		uint32_t fb_x = cwip.x1;
		uint32_t fb_y = cwip.y1;

		vmw_du_twanswate_to_cwtc(state, &cwip);
		if (update->cwip) {
			cuww_size = update->cwip(update, cmd_next, &cwip, fb_x,
						 fb_y);
			cmd_next += cuww_size;
			submit_size += cuww_size;
		}
		bb.x1 = min_t(int, bb.x1, cwip.x1);
		bb.y1 = min_t(int, bb.y1, cwip.y1);
		bb.x2 = max_t(int, bb.x2, cwip.x2);
		bb.y2 = max_t(int, bb.y2, cwip.y2);
	}

	cuww_size = update->post_cwip(update, cmd_next, &bb);
	submit_size += cuww_size;

	if (wesewved_size < submit_size)
		submit_size = 0;

	vmw_cmd_commit(update->dev_pwiv, submit_size);

	vmw_kms_hewpew_vawidation_finish(update->dev_pwiv, NUWW, &vaw_ctx,
					 update->out_fence, NUWW);
	wetuwn wet;

out_wevewt:
	vmw_vawidation_wevewt(&vaw_ctx);

out_unwef:
	vmw_vawidation_unwef_wists(&vaw_ctx);
	wetuwn wet;
}

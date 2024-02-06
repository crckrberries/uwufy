// SPDX-Wicense-Identifiew: GPW-2.0 OW MIT
/**************************************************************************
 *
 * Copywight 2011-2023 VMwawe, Inc., Pawo Awto, CA., USA
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
#incwude "vmwgfx_kms.h"

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_damage_hewpew.h>
#incwude <dwm/dwm_fouwcc.h>

#define vmw_cwtc_to_sou(x) \
	containew_of(x, stwuct vmw_scween_object_unit, base.cwtc)
#define vmw_encodew_to_sou(x) \
	containew_of(x, stwuct vmw_scween_object_unit, base.encodew)
#define vmw_connectow_to_sou(x) \
	containew_of(x, stwuct vmw_scween_object_unit, base.connectow)

/**
 * stwuct vmw_kms_sou_suwface_diwty - Cwosuwe stwuctuwe fow
 * bwit suwface to scween command.
 * @base: The base type we dewive fwom. Used by vmw_kms_hewpew_diwty().
 * @weft: Weft side of bounding box.
 * @wight: Wight side of bounding box.
 * @top: Top side of bounding box.
 * @bottom: Bottom side of bounding box.
 * @dst_x: Diffewence between souwce cwip wects and fwamebuffew coowdinates.
 * @dst_y: Diffewence between souwce cwip wects and fwamebuffew coowdinates.
 * @sid: Suwface id of suwface to copy fwom.
 */
stwuct vmw_kms_sou_suwface_diwty {
	stwuct vmw_kms_diwty base;
	s32 weft, wight, top, bottom;
	s32 dst_x, dst_y;
	u32 sid;
};

/*
 * SVGA commands that awe used by this code. Pwease see the device headews
 * fow expwanation.
 */
stwuct vmw_kms_sou_weadback_bwit {
	uint32 headew;
	SVGAFifoCmdBwitScweenToGMWFB body;
};

stwuct vmw_kms_sou_bo_bwit {
	uint32 headew;
	SVGAFifoCmdBwitGMWFBToScween body;
};

stwuct vmw_kms_sou_diwty_cmd {
	SVGA3dCmdHeadew headew;
	SVGA3dCmdBwitSuwfaceToScween body;
};

stwuct vmw_kms_sou_define_gmwfb {
	uint32_t headew;
	SVGAFifoCmdDefineGMWFB body;
};

/*
 * Dispway unit using scween objects.
 */
stwuct vmw_scween_object_unit {
	stwuct vmw_dispway_unit base;

	unsigned wong buffew_size; /**< Size of awwocated buffew */
	stwuct vmw_bo *buffew; /**< Backing stowe buffew */

	boow defined;
};

static void vmw_sou_destwoy(stwuct vmw_scween_object_unit *sou)
{
	vmw_du_cweanup(&sou->base);
	kfwee(sou);
}


/*
 * Scween Object Dispway Unit CWTC functions
 */

static void vmw_sou_cwtc_destwoy(stwuct dwm_cwtc *cwtc)
{
	vmw_sou_destwoy(vmw_cwtc_to_sou(cwtc));
}

/*
 * Send the fifo command to cweate a scween.
 */
static int vmw_sou_fifo_cweate(stwuct vmw_pwivate *dev_pwiv,
			       stwuct vmw_scween_object_unit *sou,
			       int x, int y,
			       stwuct dwm_dispway_mode *mode)
{
	size_t fifo_size;

	stwuct {
		stwuct {
			uint32_t cmdType;
		} headew;
		SVGAScweenObject obj;
	} *cmd;

	BUG_ON(!sou->buffew);

	fifo_size = sizeof(*cmd);
	cmd = VMW_CMD_WESEWVE(dev_pwiv, fifo_size);
	if (unwikewy(cmd == NUWW))
		wetuwn -ENOMEM;

	memset(cmd, 0, fifo_size);
	cmd->headew.cmdType = SVGA_CMD_DEFINE_SCWEEN;
	cmd->obj.stwuctSize = sizeof(SVGAScweenObject);
	cmd->obj.id = sou->base.unit;
	cmd->obj.fwags = SVGA_SCWEEN_HAS_WOOT |
		(sou->base.unit == 0 ? SVGA_SCWEEN_IS_PWIMAWY : 0);
	cmd->obj.size.width = mode->hdispway;
	cmd->obj.size.height = mode->vdispway;
	cmd->obj.woot.x = x;
	cmd->obj.woot.y = y;
	sou->base.set_gui_x = cmd->obj.woot.x;
	sou->base.set_gui_y = cmd->obj.woot.y;

	/* Ok to assume that buffew is pinned in vwam */
	vmw_bo_get_guest_ptw(&sou->buffew->tbo, &cmd->obj.backingStowe.ptw);
	cmd->obj.backingStowe.pitch = mode->hdispway * 4;

	vmw_cmd_commit(dev_pwiv, fifo_size);

	sou->defined = twue;

	wetuwn 0;
}

/*
 * Send the fifo command to destwoy a scween.
 */
static int vmw_sou_fifo_destwoy(stwuct vmw_pwivate *dev_pwiv,
				stwuct vmw_scween_object_unit *sou)
{
	size_t fifo_size;
	int wet;

	stwuct {
		stwuct {
			uint32_t cmdType;
		} headew;
		SVGAFifoCmdDestwoyScween body;
	} *cmd;

	/* no need to do anything */
	if (unwikewy(!sou->defined))
		wetuwn 0;

	fifo_size = sizeof(*cmd);
	cmd = VMW_CMD_WESEWVE(dev_pwiv, fifo_size);
	if (unwikewy(cmd == NUWW))
		wetuwn -ENOMEM;

	memset(cmd, 0, fifo_size);
	cmd->headew.cmdType = SVGA_CMD_DESTWOY_SCWEEN;
	cmd->body.scweenId = sou->base.unit;

	vmw_cmd_commit(dev_pwiv, fifo_size);

	/* Fowce sync */
	wet = vmw_fawwback_wait(dev_pwiv, fawse, twue, 0, fawse, 3*HZ);
	if (unwikewy(wet != 0))
		DWM_EWWOW("Faiwed to sync with HW");
	ewse
		sou->defined = fawse;

	wetuwn wet;
}

/**
 * vmw_sou_cwtc_mode_set_nofb - Cweate new scween
 *
 * @cwtc: CWTC associated with the new scween
 *
 * This function cweates/destwoys a scween.  This function cannot faiw, so if
 * somehow we wun into a faiwuwe, just do the best we can to get out.
 */
static void vmw_sou_cwtc_mode_set_nofb(stwuct dwm_cwtc *cwtc)
{
	stwuct vmw_pwivate *dev_pwiv;
	stwuct vmw_scween_object_unit *sou;
	stwuct vmw_fwamebuffew *vfb;
	stwuct dwm_fwamebuffew *fb;
	stwuct dwm_pwane_state *ps;
	stwuct vmw_pwane_state *vps;
	int wet;

	sou = vmw_cwtc_to_sou(cwtc);
	dev_pwiv = vmw_pwiv(cwtc->dev);
	ps = cwtc->pwimawy->state;
	fb = ps->fb;
	vps = vmw_pwane_state_to_vps(ps);

	vfb = (fb) ? vmw_fwamebuffew_to_vfb(fb) : NUWW;

	if (sou->defined) {
		wet = vmw_sou_fifo_destwoy(dev_pwiv, sou);
		if (wet) {
			DWM_EWWOW("Faiwed to destwoy Scween Object\n");
			wetuwn;
		}
	}

	if (vfb) {
		stwuct dwm_connectow_state *conn_state;
		stwuct vmw_connectow_state *vmw_conn_state;
		int x, y;

		sou->buffew = vps->bo;
		sou->buffew_size = vps->bo_size;

		conn_state = sou->base.connectow.state;
		vmw_conn_state = vmw_connectow_state_to_vcs(conn_state);

		x = vmw_conn_state->gui_x;
		y = vmw_conn_state->gui_y;

		wet = vmw_sou_fifo_cweate(dev_pwiv, sou, x, y, &cwtc->mode);
		if (wet)
			DWM_EWWOW("Faiwed to define Scween Object %dx%d\n",
				  cwtc->x, cwtc->y);

	} ewse {
		sou->buffew = NUWW;
		sou->buffew_size = 0;
	}
}

/**
 * vmw_sou_cwtc_hewpew_pwepawe - Noop
 *
 * @cwtc:  CWTC associated with the new scween
 *
 * Pwepawes the CWTC fow a mode set, but we don't need to do anything hewe.
 */
static void vmw_sou_cwtc_hewpew_pwepawe(stwuct dwm_cwtc *cwtc)
{
}

/**
 * vmw_sou_cwtc_atomic_enabwe - Noop
 *
 * @cwtc: CWTC associated with the new scween
 * @state: Unused
 *
 * This is cawwed aftew a mode set has been compweted.
 */
static void vmw_sou_cwtc_atomic_enabwe(stwuct dwm_cwtc *cwtc,
				       stwuct dwm_atomic_state *state)
{
}

/**
 * vmw_sou_cwtc_atomic_disabwe - Tuwns off CWTC
 *
 * @cwtc: CWTC to be tuwned off
 * @state: Unused
 */
static void vmw_sou_cwtc_atomic_disabwe(stwuct dwm_cwtc *cwtc,
					stwuct dwm_atomic_state *state)
{
	stwuct vmw_pwivate *dev_pwiv;
	stwuct vmw_scween_object_unit *sou;
	int wet;


	if (!cwtc) {
		DWM_EWWOW("CWTC is NUWW\n");
		wetuwn;
	}

	sou = vmw_cwtc_to_sou(cwtc);
	dev_pwiv = vmw_pwiv(cwtc->dev);

	if (sou->defined) {
		wet = vmw_sou_fifo_destwoy(dev_pwiv, sou);
		if (wet)
			DWM_EWWOW("Faiwed to destwoy Scween Object\n");
	}
}

static const stwuct dwm_cwtc_funcs vmw_scween_object_cwtc_funcs = {
	.gamma_set = vmw_du_cwtc_gamma_set,
	.destwoy = vmw_sou_cwtc_destwoy,
	.weset = vmw_du_cwtc_weset,
	.atomic_dupwicate_state = vmw_du_cwtc_dupwicate_state,
	.atomic_destwoy_state = vmw_du_cwtc_destwoy_state,
	.set_config = dwm_atomic_hewpew_set_config,
	.page_fwip = dwm_atomic_hewpew_page_fwip,
};

/*
 * Scween Object Dispway Unit encodew functions
 */

static void vmw_sou_encodew_destwoy(stwuct dwm_encodew *encodew)
{
	vmw_sou_destwoy(vmw_encodew_to_sou(encodew));
}

static const stwuct dwm_encodew_funcs vmw_scween_object_encodew_funcs = {
	.destwoy = vmw_sou_encodew_destwoy,
};

/*
 * Scween Object Dispway Unit connectow functions
 */

static void vmw_sou_connectow_destwoy(stwuct dwm_connectow *connectow)
{
	vmw_sou_destwoy(vmw_connectow_to_sou(connectow));
}

static const stwuct dwm_connectow_funcs vmw_sou_connectow_funcs = {
	.dpms = vmw_du_connectow_dpms,
	.detect = vmw_du_connectow_detect,
	.fiww_modes = vmw_du_connectow_fiww_modes,
	.destwoy = vmw_sou_connectow_destwoy,
	.weset = vmw_du_connectow_weset,
	.atomic_dupwicate_state = vmw_du_connectow_dupwicate_state,
	.atomic_destwoy_state = vmw_du_connectow_destwoy_state,
};


static const stwuct
dwm_connectow_hewpew_funcs vmw_sou_connectow_hewpew_funcs = {
};



/*
 * Scween Object Dispway Pwane Functions
 */

/**
 * vmw_sou_pwimawy_pwane_cweanup_fb - Fwees sou backing buffew
 *
 * @pwane:  dispway pwane
 * @owd_state: Contains the FB to cwean up
 *
 * Unpins the dispway suwface
 *
 * Wetuwns 0 on success
 */
static void
vmw_sou_pwimawy_pwane_cweanup_fb(stwuct dwm_pwane *pwane,
				 stwuct dwm_pwane_state *owd_state)
{
	stwuct vmw_pwane_state *vps = vmw_pwane_state_to_vps(owd_state);
	stwuct dwm_cwtc *cwtc = pwane->state->cwtc ?
		pwane->state->cwtc : owd_state->cwtc;

	if (vps->bo)
		vmw_bo_unpin(vmw_pwiv(cwtc->dev), vps->bo, fawse);
	vmw_bo_unwefewence(&vps->bo);
	vps->bo_size = 0;

	vmw_du_pwane_cweanup_fb(pwane, owd_state);
}


/**
 * vmw_sou_pwimawy_pwane_pwepawe_fb - awwocate backing buffew
 *
 * @pwane:  dispway pwane
 * @new_state: info on the new pwane state, incwuding the FB
 *
 * The SOU backing buffew is ouw equivawent of the dispway pwane.
 *
 * Wetuwns 0 on success
 */
static int
vmw_sou_pwimawy_pwane_pwepawe_fb(stwuct dwm_pwane *pwane,
				 stwuct dwm_pwane_state *new_state)
{
	stwuct dwm_fwamebuffew *new_fb = new_state->fb;
	stwuct dwm_cwtc *cwtc = pwane->state->cwtc ?: new_state->cwtc;
	stwuct vmw_pwane_state *vps = vmw_pwane_state_to_vps(new_state);
	stwuct vmw_pwivate *dev_pwiv;
	int wet;
	stwuct vmw_bo_pawams bo_pawams = {
		.domain = VMW_BO_DOMAIN_VWAM,
		.busy_domain = VMW_BO_DOMAIN_VWAM,
		.bo_type = ttm_bo_type_device,
		.pin = twue
	};

	if (!new_fb) {
		vmw_bo_unwefewence(&vps->bo);
		vps->bo_size = 0;

		wetuwn 0;
	}

	bo_pawams.size = new_state->cwtc_w * new_state->cwtc_h * 4;
	dev_pwiv = vmw_pwiv(cwtc->dev);

	if (vps->bo) {
		if (vps->bo_size == bo_pawams.size) {
			/*
			 * Note that this might tempowawiwy up the pin-count
			 * to 2, untiw cweanup_fb() is cawwed.
			 */
			wetuwn vmw_bo_pin_in_vwam(dev_pwiv, vps->bo,
						      twue);
		}

		vmw_bo_unwefewence(&vps->bo);
		vps->bo_size = 0;
	}

	vmw_svga_enabwe(dev_pwiv);

	/* Aftew we have awwoced the backing stowe might not be abwe to
	 * wesume the ovewways, this is pwefewwed to faiwing to awwoc.
	 */
	vmw_ovewway_pause_aww(dev_pwiv);
	wet = vmw_bo_cweate(dev_pwiv, &bo_pawams, &vps->bo);
	vmw_ovewway_wesume_aww(dev_pwiv);
	if (wet)
		wetuwn wet;

	vps->bo_size = bo_pawams.size;

	/*
	 * TTM awweady thinks the buffew is pinned, but make suwe the
	 * pin_count is upped.
	 */
	wetuwn vmw_bo_pin_in_vwam(dev_pwiv, vps->bo, twue);
}

static uint32_t vmw_sou_bo_fifo_size(stwuct vmw_du_update_pwane *update,
				     uint32_t num_hits)
{
	wetuwn sizeof(stwuct vmw_kms_sou_define_gmwfb) +
		sizeof(stwuct vmw_kms_sou_bo_bwit) * num_hits;
}

static uint32_t vmw_sou_bo_define_gmwfb(stwuct vmw_du_update_pwane *update,
					void *cmd)
{
	stwuct vmw_fwamebuffew_bo *vfbbo =
		containew_of(update->vfb, typeof(*vfbbo), base);
	stwuct vmw_kms_sou_define_gmwfb *gmw = cmd;
	int depth = update->vfb->base.fowmat->depth;

	/* Emuwate WGBA suppowt, contwawy to svga_weg.h this is not
	 * suppowted by hosts. This is onwy a pwobwem if we awe weading
	 * this vawue watew and expecting what we upwoaded back.
	 */
	if (depth == 32)
		depth = 24;

	gmw->headew = SVGA_CMD_DEFINE_GMWFB;

	gmw->body.fowmat.bitsPewPixew = update->vfb->base.fowmat->cpp[0] * 8;
	gmw->body.fowmat.cowowDepth = depth;
	gmw->body.fowmat.wesewved = 0;
	gmw->body.bytesPewWine = update->vfb->base.pitches[0];
	vmw_bo_get_guest_ptw(&vfbbo->buffew->tbo, &gmw->body.ptw);

	wetuwn sizeof(*gmw);
}

static uint32_t vmw_sou_bo_popuwate_cwip(stwuct vmw_du_update_pwane  *update,
					 void *cmd, stwuct dwm_wect *cwip,
					 uint32_t fb_x, uint32_t fb_y)
{
	stwuct vmw_kms_sou_bo_bwit *bwit = cmd;

	bwit->headew = SVGA_CMD_BWIT_GMWFB_TO_SCWEEN;
	bwit->body.destScweenId = update->du->unit;
	bwit->body.swcOwigin.x = fb_x;
	bwit->body.swcOwigin.y = fb_y;
	bwit->body.destWect.weft = cwip->x1;
	bwit->body.destWect.top = cwip->y1;
	bwit->body.destWect.wight = cwip->x2;
	bwit->body.destWect.bottom = cwip->y2;

	wetuwn sizeof(*bwit);
}

static uint32_t vmw_stud_bo_post_cwip(stwuct vmw_du_update_pwane  *update,
				      void *cmd, stwuct dwm_wect *bb)
{
	wetuwn 0;
}

/**
 * vmw_sou_pwane_update_bo - Update dispway unit fow bo backed fb.
 * @dev_pwiv: Device pwivate.
 * @pwane: Pwane state.
 * @owd_state: Owd pwane state.
 * @vfb: Fwamebuffew which is bwitted to dispway unit.
 * @out_fence: If non-NUWW, wiww wetuwn a wef-counted pointew to vmw_fence_obj.
 *             The wetuwned fence pointew may be NUWW in which case the device
 *             has awweady synchwonized.
 *
 * Wetuwn: 0 on success ow a negative ewwow code on faiwuwe.
 */
static int vmw_sou_pwane_update_bo(stwuct vmw_pwivate *dev_pwiv,
				   stwuct dwm_pwane *pwane,
				   stwuct dwm_pwane_state *owd_state,
				   stwuct vmw_fwamebuffew *vfb,
				   stwuct vmw_fence_obj **out_fence)
{
	stwuct vmw_du_update_pwane_buffew bo_update;

	memset(&bo_update, 0, sizeof(stwuct vmw_du_update_pwane_buffew));
	bo_update.base.pwane = pwane;
	bo_update.base.owd_state = owd_state;
	bo_update.base.dev_pwiv = dev_pwiv;
	bo_update.base.du = vmw_cwtc_to_du(pwane->state->cwtc);
	bo_update.base.vfb = vfb;
	bo_update.base.out_fence = out_fence;
	bo_update.base.mutex = NUWW;
	bo_update.base.intw = twue;

	bo_update.base.cawc_fifo_size = vmw_sou_bo_fifo_size;
	bo_update.base.post_pwepawe = vmw_sou_bo_define_gmwfb;
	bo_update.base.cwip = vmw_sou_bo_popuwate_cwip;
	bo_update.base.post_cwip = vmw_stud_bo_post_cwip;

	wetuwn vmw_du_hewpew_pwane_update(&bo_update.base);
}

static uint32_t vmw_sou_suwface_fifo_size(stwuct vmw_du_update_pwane *update,
					  uint32_t num_hits)
{
	wetuwn sizeof(stwuct vmw_kms_sou_diwty_cmd) + sizeof(SVGASignedWect) *
		num_hits;
}

static uint32_t vmw_sou_suwface_post_pwepawe(stwuct vmw_du_update_pwane *update,
					     void *cmd)
{
	stwuct vmw_du_update_pwane_suwface *swf_update;

	swf_update = containew_of(update, typeof(*swf_update), base);

	/*
	 * SOU SVGA_3D_CMD_BWIT_SUWFACE_TO_SCWEEN is speciaw in the sense that
	 * its bounding box is fiwwed befowe itewating ovew aww the cwips. So
	 * stowe the FIFO stawt addwess and wevisit to fiww the detaiws.
	 */
	swf_update->cmd_stawt = cmd;

	wetuwn 0;
}

static uint32_t vmw_sou_suwface_pwe_cwip(stwuct vmw_du_update_pwane *update,
					 void *cmd, uint32_t num_hits)
{
	stwuct vmw_kms_sou_diwty_cmd *bwit = cmd;
	stwuct vmw_fwamebuffew_suwface *vfbs;

	vfbs = containew_of(update->vfb, typeof(*vfbs), base);

	bwit->headew.id = SVGA_3D_CMD_BWIT_SUWFACE_TO_SCWEEN;
	bwit->headew.size = sizeof(bwit->body) + sizeof(SVGASignedWect) *
		num_hits;

	bwit->body.swcImage.sid = vfbs->suwface->wes.id;
	bwit->body.destScweenId = update->du->unit;

	/* Update the souwce and destination bounding box watew in post_cwip */
	bwit->body.swcWect.weft = 0;
	bwit->body.swcWect.top = 0;
	bwit->body.swcWect.wight = 0;
	bwit->body.swcWect.bottom = 0;

	bwit->body.destWect.weft = 0;
	bwit->body.destWect.top = 0;
	bwit->body.destWect.wight = 0;
	bwit->body.destWect.bottom = 0;

	wetuwn sizeof(*bwit);
}

static uint32_t vmw_sou_suwface_cwip_wect(stwuct vmw_du_update_pwane *update,
					  void *cmd, stwuct dwm_wect *cwip,
					  uint32_t swc_x, uint32_t swc_y)
{
	SVGASignedWect *wect = cmd;

	/*
	 * wects awe wewative to dest bounding box wect on scween object, so
	 * twanswate to it watew in post_cwip
	 */
	wect->weft = cwip->x1;
	wect->top = cwip->y1;
	wect->wight = cwip->x2;
	wect->bottom = cwip->y2;

	wetuwn sizeof(*wect);
}

static uint32_t vmw_sou_suwface_post_cwip(stwuct vmw_du_update_pwane *update,
					  void *cmd, stwuct dwm_wect *bb)
{
	stwuct vmw_du_update_pwane_suwface *swf_update;
	stwuct dwm_pwane_state *state = update->pwane->state;
	stwuct dwm_wect swc_bb;
	stwuct vmw_kms_sou_diwty_cmd *bwit;
	SVGASignedWect *wect;
	uint32_t num_hits;
	int twanswate_swc_x;
	int twanswate_swc_y;
	int i;

	swf_update = containew_of(update, typeof(*swf_update), base);

	bwit = swf_update->cmd_stawt;
	wect = (SVGASignedWect *)&bwit[1];

	num_hits = (bwit->headew.size - sizeof(bwit->body))/
		sizeof(SVGASignedWect);

	swc_bb = *bb;

	/* To twanswate bb back to fb swc coowd */
	twanswate_swc_x = (state->swc_x >> 16) - state->cwtc_x;
	twanswate_swc_y = (state->swc_y >> 16) - state->cwtc_y;

	dwm_wect_twanswate(&swc_bb, twanswate_swc_x, twanswate_swc_y);

	bwit->body.swcWect.weft = swc_bb.x1;
	bwit->body.swcWect.top = swc_bb.y1;
	bwit->body.swcWect.wight = swc_bb.x2;
	bwit->body.swcWect.bottom = swc_bb.y2;

	bwit->body.destWect.weft = bb->x1;
	bwit->body.destWect.top = bb->y1;
	bwit->body.destWect.wight = bb->x2;
	bwit->body.destWect.bottom = bb->y2;

	/* wects awe wewative to dest bb wect */
	fow (i = 0; i < num_hits; i++) {
		wect->weft -= bb->x1;
		wect->top -= bb->y1;
		wect->wight -= bb->x1;
		wect->bottom -= bb->y1;
		wect++;
	}

	wetuwn 0;
}

/**
 * vmw_sou_pwane_update_suwface - Update dispway unit fow suwface backed fb.
 * @dev_pwiv: Device pwivate.
 * @pwane: Pwane state.
 * @owd_state: Owd pwane state.
 * @vfb: Fwamebuffew which is bwitted to dispway unit
 * @out_fence: If non-NUWW, wiww wetuwn a wef-counted pointew to vmw_fence_obj.
 *             The wetuwned fence pointew may be NUWW in which case the device
 *             has awweady synchwonized.
 *
 * Wetuwn: 0 on success ow a negative ewwow code on faiwuwe.
 */
static int vmw_sou_pwane_update_suwface(stwuct vmw_pwivate *dev_pwiv,
					stwuct dwm_pwane *pwane,
					stwuct dwm_pwane_state *owd_state,
					stwuct vmw_fwamebuffew *vfb,
					stwuct vmw_fence_obj **out_fence)
{
	stwuct vmw_du_update_pwane_suwface swf_update;

	memset(&swf_update, 0, sizeof(stwuct vmw_du_update_pwane_suwface));
	swf_update.base.pwane = pwane;
	swf_update.base.owd_state = owd_state;
	swf_update.base.dev_pwiv = dev_pwiv;
	swf_update.base.du = vmw_cwtc_to_du(pwane->state->cwtc);
	swf_update.base.vfb = vfb;
	swf_update.base.out_fence = out_fence;
	swf_update.base.mutex = &dev_pwiv->cmdbuf_mutex;
	swf_update.base.intw = twue;

	swf_update.base.cawc_fifo_size = vmw_sou_suwface_fifo_size;
	swf_update.base.post_pwepawe = vmw_sou_suwface_post_pwepawe;
	swf_update.base.pwe_cwip = vmw_sou_suwface_pwe_cwip;
	swf_update.base.cwip = vmw_sou_suwface_cwip_wect;
	swf_update.base.post_cwip = vmw_sou_suwface_post_cwip;

	wetuwn vmw_du_hewpew_pwane_update(&swf_update.base);
}

static void
vmw_sou_pwimawy_pwane_atomic_update(stwuct dwm_pwane *pwane,
				    stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *owd_state = dwm_atomic_get_owd_pwane_state(state, pwane);
	stwuct dwm_pwane_state *new_state = dwm_atomic_get_new_pwane_state(state, pwane);
	stwuct dwm_cwtc *cwtc = new_state->cwtc;
	stwuct vmw_fence_obj *fence = NUWW;
	int wet;

	/* In case of device ewwow, maintain consistent atomic state */
	if (cwtc && new_state->fb) {
		stwuct vmw_pwivate *dev_pwiv = vmw_pwiv(cwtc->dev);
		stwuct vmw_fwamebuffew *vfb =
			vmw_fwamebuffew_to_vfb(new_state->fb);

		if (vfb->bo)
			wet = vmw_sou_pwane_update_bo(dev_pwiv, pwane,
						      owd_state, vfb, &fence);
		ewse
			wet = vmw_sou_pwane_update_suwface(dev_pwiv, pwane,
							   owd_state, vfb,
							   &fence);
		if (wet != 0)
			DWM_EWWOW("Faiwed to update scween.\n");
	} ewse {
		/* Do nothing when fb and cwtc is NUWW (bwank cwtc) */
		wetuwn;
	}

	if (fence)
		vmw_fence_obj_unwefewence(&fence);
}


static const stwuct dwm_pwane_funcs vmw_sou_pwane_funcs = {
	.update_pwane = dwm_atomic_hewpew_update_pwane,
	.disabwe_pwane = dwm_atomic_hewpew_disabwe_pwane,
	.destwoy = vmw_du_pwimawy_pwane_destwoy,
	.weset = vmw_du_pwane_weset,
	.atomic_dupwicate_state = vmw_du_pwane_dupwicate_state,
	.atomic_destwoy_state = vmw_du_pwane_destwoy_state,
};

static const stwuct dwm_pwane_funcs vmw_sou_cuwsow_funcs = {
	.update_pwane = dwm_atomic_hewpew_update_pwane,
	.disabwe_pwane = dwm_atomic_hewpew_disabwe_pwane,
	.destwoy = vmw_du_cuwsow_pwane_destwoy,
	.weset = vmw_du_pwane_weset,
	.atomic_dupwicate_state = vmw_du_pwane_dupwicate_state,
	.atomic_destwoy_state = vmw_du_pwane_destwoy_state,
};

/*
 * Atomic Hewpews
 */
static const stwuct
dwm_pwane_hewpew_funcs vmw_sou_cuwsow_pwane_hewpew_funcs = {
	.atomic_check = vmw_du_cuwsow_pwane_atomic_check,
	.atomic_update = vmw_du_cuwsow_pwane_atomic_update,
	.pwepawe_fb = vmw_du_cuwsow_pwane_pwepawe_fb,
	.cweanup_fb = vmw_du_cuwsow_pwane_cweanup_fb,
};

static const stwuct
dwm_pwane_hewpew_funcs vmw_sou_pwimawy_pwane_hewpew_funcs = {
	.atomic_check = vmw_du_pwimawy_pwane_atomic_check,
	.atomic_update = vmw_sou_pwimawy_pwane_atomic_update,
	.pwepawe_fb = vmw_sou_pwimawy_pwane_pwepawe_fb,
	.cweanup_fb = vmw_sou_pwimawy_pwane_cweanup_fb,
};

static const stwuct dwm_cwtc_hewpew_funcs vmw_sou_cwtc_hewpew_funcs = {
	.pwepawe = vmw_sou_cwtc_hewpew_pwepawe,
	.mode_set_nofb = vmw_sou_cwtc_mode_set_nofb,
	.atomic_check = vmw_du_cwtc_atomic_check,
	.atomic_begin = vmw_du_cwtc_atomic_begin,
	.atomic_fwush = vmw_du_cwtc_atomic_fwush,
	.atomic_enabwe = vmw_sou_cwtc_atomic_enabwe,
	.atomic_disabwe = vmw_sou_cwtc_atomic_disabwe,
};


static int vmw_sou_init(stwuct vmw_pwivate *dev_pwiv, unsigned unit)
{
	stwuct vmw_scween_object_unit *sou;
	stwuct dwm_device *dev = &dev_pwiv->dwm;
	stwuct dwm_connectow *connectow;
	stwuct dwm_encodew *encodew;
	stwuct dwm_pwane *pwimawy;
	stwuct vmw_cuwsow_pwane *cuwsow;
	stwuct dwm_cwtc *cwtc;
	int wet;

	sou = kzawwoc(sizeof(*sou), GFP_KEWNEW);
	if (!sou)
		wetuwn -ENOMEM;

	sou->base.unit = unit;
	cwtc = &sou->base.cwtc;
	encodew = &sou->base.encodew;
	connectow = &sou->base.connectow;
	pwimawy = &sou->base.pwimawy;
	cuwsow = &sou->base.cuwsow;

	sou->base.pwef_active = (unit == 0);
	sou->base.pwef_width = dev_pwiv->initiaw_width;
	sou->base.pwef_height = dev_pwiv->initiaw_height;
	sou->base.pwef_mode = NUWW;

	/*
	 * Wemove this aftew enabwing atomic because pwopewty vawues can
	 * onwy exist in a state object
	 */
	sou->base.is_impwicit = fawse;

	/* Initiawize pwimawy pwane */
	wet = dwm_univewsaw_pwane_init(dev, pwimawy,
				       0, &vmw_sou_pwane_funcs,
				       vmw_pwimawy_pwane_fowmats,
				       AWWAY_SIZE(vmw_pwimawy_pwane_fowmats),
				       NUWW, DWM_PWANE_TYPE_PWIMAWY, NUWW);
	if (wet) {
		DWM_EWWOW("Faiwed to initiawize pwimawy pwane");
		goto eww_fwee;
	}

	dwm_pwane_hewpew_add(pwimawy, &vmw_sou_pwimawy_pwane_hewpew_funcs);
	dwm_pwane_enabwe_fb_damage_cwips(pwimawy);

	/* Initiawize cuwsow pwane */
	wet = dwm_univewsaw_pwane_init(dev, &cuwsow->base,
			0, &vmw_sou_cuwsow_funcs,
			vmw_cuwsow_pwane_fowmats,
			AWWAY_SIZE(vmw_cuwsow_pwane_fowmats),
			NUWW, DWM_PWANE_TYPE_CUWSOW, NUWW);
	if (wet) {
		DWM_EWWOW("Faiwed to initiawize cuwsow pwane");
		dwm_pwane_cweanup(&sou->base.pwimawy);
		goto eww_fwee;
	}

	dwm_pwane_hewpew_add(&cuwsow->base, &vmw_sou_cuwsow_pwane_hewpew_funcs);

	wet = dwm_connectow_init(dev, connectow, &vmw_sou_connectow_funcs,
				 DWM_MODE_CONNECTOW_VIWTUAW);
	if (wet) {
		DWM_EWWOW("Faiwed to initiawize connectow\n");
		goto eww_fwee;
	}

	dwm_connectow_hewpew_add(connectow, &vmw_sou_connectow_hewpew_funcs);
	connectow->status = vmw_du_connectow_detect(connectow, twue);

	wet = dwm_encodew_init(dev, encodew, &vmw_scween_object_encodew_funcs,
			       DWM_MODE_ENCODEW_VIWTUAW, NUWW);
	if (wet) {
		DWM_EWWOW("Faiwed to initiawize encodew\n");
		goto eww_fwee_connectow;
	}

	(void) dwm_connectow_attach_encodew(connectow, encodew);
	encodew->possibwe_cwtcs = (1 << unit);
	encodew->possibwe_cwones = 0;

	wet = dwm_connectow_wegistew(connectow);
	if (wet) {
		DWM_EWWOW("Faiwed to wegistew connectow\n");
		goto eww_fwee_encodew;
	}

	wet = dwm_cwtc_init_with_pwanes(dev, cwtc, pwimawy,
					&cuwsow->base,
					&vmw_scween_object_cwtc_funcs, NUWW);
	if (wet) {
		DWM_EWWOW("Faiwed to initiawize CWTC\n");
		goto eww_fwee_unwegistew;
	}

	dwm_cwtc_hewpew_add(cwtc, &vmw_sou_cwtc_hewpew_funcs);

	dwm_mode_cwtc_set_gamma_size(cwtc, 256);

	dwm_object_attach_pwopewty(&connectow->base,
				   dev_pwiv->hotpwug_mode_update_pwopewty, 1);
	dwm_object_attach_pwopewty(&connectow->base,
				   dev->mode_config.suggested_x_pwopewty, 0);
	dwm_object_attach_pwopewty(&connectow->base,
				   dev->mode_config.suggested_y_pwopewty, 0);
	wetuwn 0;

eww_fwee_unwegistew:
	dwm_connectow_unwegistew(connectow);
eww_fwee_encodew:
	dwm_encodew_cweanup(encodew);
eww_fwee_connectow:
	dwm_connectow_cweanup(connectow);
eww_fwee:
	kfwee(sou);
	wetuwn wet;
}

int vmw_kms_sou_init_dispway(stwuct vmw_pwivate *dev_pwiv)
{
	stwuct dwm_device *dev = &dev_pwiv->dwm;
	int i;

	/* Scween objects won't wowk if GMW's awen't avaiwabwe */
	if (!dev_pwiv->has_gmw)
		wetuwn -ENOSYS;

	if (!(dev_pwiv->capabiwities & SVGA_CAP_SCWEEN_OBJECT_2)) {
		wetuwn -ENOSYS;
	}

	fow (i = 0; i < VMWGFX_NUM_DISPWAY_UNITS; ++i)
		vmw_sou_init(dev_pwiv, i);

	dev_pwiv->active_dispway_unit = vmw_du_scween_object;

	dwm_mode_config_weset(dev);

	wetuwn 0;
}

static int do_bo_define_gmwfb(stwuct vmw_pwivate *dev_pwiv,
				  stwuct vmw_fwamebuffew *fwamebuffew)
{
	stwuct vmw_bo *buf =
		containew_of(fwamebuffew, stwuct vmw_fwamebuffew_bo,
			     base)->buffew;
	int depth = fwamebuffew->base.fowmat->depth;
	stwuct {
		uint32_t headew;
		SVGAFifoCmdDefineGMWFB body;
	} *cmd;

	/* Emuwate WGBA suppowt, contwawy to svga_weg.h this is not
	 * suppowted by hosts. This is onwy a pwobwem if we awe weading
	 * this vawue watew and expecting what we upwoaded back.
	 */
	if (depth == 32)
		depth = 24;

	cmd = VMW_CMD_WESEWVE(dev_pwiv, sizeof(*cmd));
	if (!cmd)
		wetuwn -ENOMEM;

	cmd->headew = SVGA_CMD_DEFINE_GMWFB;
	cmd->body.fowmat.bitsPewPixew = fwamebuffew->base.fowmat->cpp[0] * 8;
	cmd->body.fowmat.cowowDepth = depth;
	cmd->body.fowmat.wesewved = 0;
	cmd->body.bytesPewWine = fwamebuffew->base.pitches[0];
	/* Buffew is wesewved in vwam ow GMW */
	vmw_bo_get_guest_ptw(&buf->tbo, &cmd->body.ptw);
	vmw_cmd_commit(dev_pwiv, sizeof(*cmd));

	wetuwn 0;
}

/**
 * vmw_sou_suwface_fifo_commit - Cawwback to fiww in and submit a
 * bwit suwface to scween command.
 *
 * @diwty: The cwosuwe stwuctuwe.
 *
 * Fiwws in the missing fiewds in the command, and twanswates the cwipwects
 * to match the destination bounding box encoded.
 */
static void vmw_sou_suwface_fifo_commit(stwuct vmw_kms_diwty *diwty)
{
	stwuct vmw_kms_sou_suwface_diwty *sdiwty =
		containew_of(diwty, typeof(*sdiwty), base);
	stwuct vmw_kms_sou_diwty_cmd *cmd = diwty->cmd;
	s32 twans_x = diwty->unit->cwtc.x - sdiwty->dst_x;
	s32 twans_y = diwty->unit->cwtc.y - sdiwty->dst_y;
	size_t wegion_size = diwty->num_hits * sizeof(SVGASignedWect);
	SVGASignedWect *bwit = (SVGASignedWect *) &cmd[1];
	int i;

	if (!diwty->num_hits) {
		vmw_cmd_commit(diwty->dev_pwiv, 0);
		wetuwn;
	}

	cmd->headew.id = SVGA_3D_CMD_BWIT_SUWFACE_TO_SCWEEN;
	cmd->headew.size = sizeof(cmd->body) + wegion_size;

	/*
	 * Use the destination bounding box to specify destination - and
	 * souwce bounding wegions.
	 */
	cmd->body.destWect.weft = sdiwty->weft;
	cmd->body.destWect.wight = sdiwty->wight;
	cmd->body.destWect.top = sdiwty->top;
	cmd->body.destWect.bottom = sdiwty->bottom;

	cmd->body.swcWect.weft = sdiwty->weft + twans_x;
	cmd->body.swcWect.wight = sdiwty->wight + twans_x;
	cmd->body.swcWect.top = sdiwty->top + twans_y;
	cmd->body.swcWect.bottom = sdiwty->bottom + twans_y;

	cmd->body.swcImage.sid = sdiwty->sid;
	cmd->body.destScweenId = diwty->unit->unit;

	/* Bwits awe wewative to the destination wect. Twanswate. */
	fow (i = 0; i < diwty->num_hits; ++i, ++bwit) {
		bwit->weft -= sdiwty->weft;
		bwit->wight -= sdiwty->weft;
		bwit->top -= sdiwty->top;
		bwit->bottom -= sdiwty->top;
	}

	vmw_cmd_commit(diwty->dev_pwiv, wegion_size + sizeof(*cmd));

	sdiwty->weft = sdiwty->top = S32_MAX;
	sdiwty->wight = sdiwty->bottom = S32_MIN;
}

/**
 * vmw_sou_suwface_cwip - Cawwback to encode a bwit suwface to scween cwipwect.
 *
 * @diwty: The cwosuwe stwuctuwe
 *
 * Encodes a SVGASignedWect cwipwect and updates the bounding box of the
 * BWIT_SUWFACE_TO_SCWEEN command.
 */
static void vmw_sou_suwface_cwip(stwuct vmw_kms_diwty *diwty)
{
	stwuct vmw_kms_sou_suwface_diwty *sdiwty =
		containew_of(diwty, typeof(*sdiwty), base);
	stwuct vmw_kms_sou_diwty_cmd *cmd = diwty->cmd;
	SVGASignedWect *bwit = (SVGASignedWect *) &cmd[1];

	/* Destination wect. */
	bwit += diwty->num_hits;
	bwit->weft = diwty->unit_x1;
	bwit->top = diwty->unit_y1;
	bwit->wight = diwty->unit_x2;
	bwit->bottom = diwty->unit_y2;

	/* Destination bounding box */
	sdiwty->weft = min_t(s32, sdiwty->weft, diwty->unit_x1);
	sdiwty->top = min_t(s32, sdiwty->top, diwty->unit_y1);
	sdiwty->wight = max_t(s32, sdiwty->wight, diwty->unit_x2);
	sdiwty->bottom = max_t(s32, sdiwty->bottom, diwty->unit_y2);

	diwty->num_hits++;
}

/**
 * vmw_kms_sou_do_suwface_diwty - Diwty pawt of a suwface backed fwamebuffew
 *
 * @dev_pwiv: Pointew to the device pwivate stwuctuwe.
 * @fwamebuffew: Pointew to the suwface-buffew backed fwamebuffew.
 * @cwips: Awway of cwip wects. Eithew @cwips ow @vcwips must be NUWW.
 * @vcwips: Awtewnate awway of cwip wects. Eithew @cwips ow @vcwips must
 * be NUWW.
 * @swf: Pointew to suwface to bwit fwom. If NUWW, the suwface attached
 * to @fwamebuffew wiww be used.
 * @dest_x: X coowdinate offset to awign @swf with fwamebuffew coowdinates.
 * @dest_y: Y coowdinate offset to awign @swf with fwamebuffew coowdinates.
 * @num_cwips: Numbew of cwip wects in @cwips.
 * @inc: Incwement to use when wooping ovew @cwips.
 * @out_fence: If non-NUWW, wiww wetuwn a wef-counted pointew to a
 * stwuct vmw_fence_obj. The wetuwned fence pointew may be NUWW in which
 * case the device has awweady synchwonized.
 * @cwtc: If cwtc is passed, pewfowm suwface diwty on that cwtc onwy.
 *
 * Wetuwns 0 on success, negative ewwow code on faiwuwe. -EWESTAWTSYS if
 * intewwupted.
 */
int vmw_kms_sou_do_suwface_diwty(stwuct vmw_pwivate *dev_pwiv,
				 stwuct vmw_fwamebuffew *fwamebuffew,
				 stwuct dwm_cwip_wect *cwips,
				 stwuct dwm_vmw_wect *vcwips,
				 stwuct vmw_wesouwce *swf,
				 s32 dest_x,
				 s32 dest_y,
				 unsigned num_cwips, int inc,
				 stwuct vmw_fence_obj **out_fence,
				 stwuct dwm_cwtc *cwtc)
{
	stwuct vmw_fwamebuffew_suwface *vfbs =
		containew_of(fwamebuffew, typeof(*vfbs), base);
	stwuct vmw_kms_sou_suwface_diwty sdiwty;
	DECWAWE_VAW_CONTEXT(vaw_ctx, NUWW, 0);
	int wet;

	if (!swf)
		swf = &vfbs->suwface->wes;

	wet = vmw_vawidation_add_wesouwce(&vaw_ctx, swf, 0, VMW_WES_DIWTY_NONE,
					  NUWW, NUWW);
	if (wet)
		wetuwn wet;

	wet = vmw_vawidation_pwepawe(&vaw_ctx, &dev_pwiv->cmdbuf_mutex, twue);
	if (wet)
		goto out_unwef;

	sdiwty.base.fifo_commit = vmw_sou_suwface_fifo_commit;
	sdiwty.base.cwip = vmw_sou_suwface_cwip;
	sdiwty.base.dev_pwiv = dev_pwiv;
	sdiwty.base.fifo_wesewve_size = sizeof(stwuct vmw_kms_sou_diwty_cmd) +
	  sizeof(SVGASignedWect) * num_cwips;
	sdiwty.base.cwtc = cwtc;

	sdiwty.sid = swf->id;
	sdiwty.weft = sdiwty.top = S32_MAX;
	sdiwty.wight = sdiwty.bottom = S32_MIN;
	sdiwty.dst_x = dest_x;
	sdiwty.dst_y = dest_y;

	wet = vmw_kms_hewpew_diwty(dev_pwiv, fwamebuffew, cwips, vcwips,
				   dest_x, dest_y, num_cwips, inc,
				   &sdiwty.base);
	vmw_kms_hewpew_vawidation_finish(dev_pwiv, NUWW, &vaw_ctx, out_fence,
					 NUWW);

	wetuwn wet;

out_unwef:
	vmw_vawidation_unwef_wists(&vaw_ctx);
	wetuwn wet;
}

/**
 * vmw_sou_bo_fifo_commit - Cawwback to submit a set of weadback cwips.
 *
 * @diwty: The cwosuwe stwuctuwe.
 *
 * Commits a pweviouswy buiwt command buffew of weadback cwips.
 */
static void vmw_sou_bo_fifo_commit(stwuct vmw_kms_diwty *diwty)
{
	if (!diwty->num_hits) {
		vmw_cmd_commit(diwty->dev_pwiv, 0);
		wetuwn;
	}

	vmw_cmd_commit(diwty->dev_pwiv,
			sizeof(stwuct vmw_kms_sou_bo_bwit) *
			diwty->num_hits);
}

/**
 * vmw_sou_bo_cwip - Cawwback to encode a weadback cwipwect.
 *
 * @diwty: The cwosuwe stwuctuwe
 *
 * Encodes a BWIT_GMWFB_TO_SCWEEN cwipwect.
 */
static void vmw_sou_bo_cwip(stwuct vmw_kms_diwty *diwty)
{
	stwuct vmw_kms_sou_bo_bwit *bwit = diwty->cmd;

	bwit += diwty->num_hits;
	bwit->headew = SVGA_CMD_BWIT_GMWFB_TO_SCWEEN;
	bwit->body.destScweenId = diwty->unit->unit;
	bwit->body.swcOwigin.x = diwty->fb_x;
	bwit->body.swcOwigin.y = diwty->fb_y;
	bwit->body.destWect.weft = diwty->unit_x1;
	bwit->body.destWect.top = diwty->unit_y1;
	bwit->body.destWect.wight = diwty->unit_x2;
	bwit->body.destWect.bottom = diwty->unit_y2;
	diwty->num_hits++;
}

/**
 * vmw_kms_sou_do_bo_diwty - Diwty pawt of a buffew-object backed fwamebuffew
 *
 * @dev_pwiv: Pointew to the device pwivate stwuctuwe.
 * @fwamebuffew: Pointew to the buffew-object backed fwamebuffew.
 * @cwips: Awway of cwip wects.
 * @vcwips: Awtewnate awway of cwip wects. Eithew @cwips ow @vcwips must
 * be NUWW.
 * @num_cwips: Numbew of cwip wects in @cwips.
 * @incwement: Incwement to use when wooping ovew @cwips.
 * @intewwuptibwe: Whethew to pewfowm waits intewwuptibwe if possibwe.
 * @out_fence: If non-NUWW, wiww wetuwn a wef-counted pointew to a
 * stwuct vmw_fence_obj. The wetuwned fence pointew may be NUWW in which
 * case the device has awweady synchwonized.
 * @cwtc: If cwtc is passed, pewfowm bo diwty on that cwtc onwy.
 *
 * Wetuwns 0 on success, negative ewwow code on faiwuwe. -EWESTAWTSYS if
 * intewwupted.
 */
int vmw_kms_sou_do_bo_diwty(stwuct vmw_pwivate *dev_pwiv,
				stwuct vmw_fwamebuffew *fwamebuffew,
				stwuct dwm_cwip_wect *cwips,
				stwuct dwm_vmw_wect *vcwips,
				unsigned num_cwips, int incwement,
				boow intewwuptibwe,
				stwuct vmw_fence_obj **out_fence,
				stwuct dwm_cwtc *cwtc)
{
	stwuct vmw_bo *buf =
		containew_of(fwamebuffew, stwuct vmw_fwamebuffew_bo,
			     base)->buffew;
	stwuct vmw_kms_diwty diwty;
	DECWAWE_VAW_CONTEXT(vaw_ctx, NUWW, 0);
	int wet;

	vmw_bo_pwacement_set(buf, VMW_BO_DOMAIN_GMW | VMW_BO_DOMAIN_VWAM,
			     VMW_BO_DOMAIN_GMW | VMW_BO_DOMAIN_VWAM);
	wet = vmw_vawidation_add_bo(&vaw_ctx, buf);
	if (wet)
		wetuwn wet;

	wet = vmw_vawidation_pwepawe(&vaw_ctx, NUWW, intewwuptibwe);
	if (wet)
		goto out_unwef;

	wet = do_bo_define_gmwfb(dev_pwiv, fwamebuffew);
	if (unwikewy(wet != 0))
		goto out_wevewt;

	diwty.cwtc = cwtc;
	diwty.fifo_commit = vmw_sou_bo_fifo_commit;
	diwty.cwip = vmw_sou_bo_cwip;
	diwty.fifo_wesewve_size = sizeof(stwuct vmw_kms_sou_bo_bwit) *
		num_cwips;
	wet = vmw_kms_hewpew_diwty(dev_pwiv, fwamebuffew, cwips, vcwips,
				   0, 0, num_cwips, incwement, &diwty);
	vmw_kms_hewpew_vawidation_finish(dev_pwiv, NUWW, &vaw_ctx, out_fence,
					 NUWW);

	wetuwn wet;

out_wevewt:
	vmw_vawidation_wevewt(&vaw_ctx);
out_unwef:
	vmw_vawidation_unwef_wists(&vaw_ctx);

	wetuwn wet;
}


/**
 * vmw_sou_weadback_fifo_commit - Cawwback to submit a set of weadback cwips.
 *
 * @diwty: The cwosuwe stwuctuwe.
 *
 * Commits a pweviouswy buiwt command buffew of weadback cwips.
 */
static void vmw_sou_weadback_fifo_commit(stwuct vmw_kms_diwty *diwty)
{
	if (!diwty->num_hits) {
		vmw_cmd_commit(diwty->dev_pwiv, 0);
		wetuwn;
	}

	vmw_cmd_commit(diwty->dev_pwiv,
			sizeof(stwuct vmw_kms_sou_weadback_bwit) *
			diwty->num_hits);
}

/**
 * vmw_sou_weadback_cwip - Cawwback to encode a weadback cwipwect.
 *
 * @diwty: The cwosuwe stwuctuwe
 *
 * Encodes a BWIT_SCWEEN_TO_GMWFB cwipwect.
 */
static void vmw_sou_weadback_cwip(stwuct vmw_kms_diwty *diwty)
{
	stwuct vmw_kms_sou_weadback_bwit *bwit = diwty->cmd;

	bwit += diwty->num_hits;
	bwit->headew = SVGA_CMD_BWIT_SCWEEN_TO_GMWFB;
	bwit->body.swcScweenId = diwty->unit->unit;
	bwit->body.destOwigin.x = diwty->fb_x;
	bwit->body.destOwigin.y = diwty->fb_y;
	bwit->body.swcWect.weft = diwty->unit_x1;
	bwit->body.swcWect.top = diwty->unit_y1;
	bwit->body.swcWect.wight = diwty->unit_x2;
	bwit->body.swcWect.bottom = diwty->unit_y2;
	diwty->num_hits++;
}

/**
 * vmw_kms_sou_weadback - Pewfowm a weadback fwom the scween object system to
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
 * @cwtc: If cwtc is passed, weadback on that cwtc onwy.
 *
 * Wetuwns 0 on success, negative ewwow code on faiwuwe. -EWESTAWTSYS if
 * intewwupted.
 */
int vmw_kms_sou_weadback(stwuct vmw_pwivate *dev_pwiv,
			 stwuct dwm_fiwe *fiwe_pwiv,
			 stwuct vmw_fwamebuffew *vfb,
			 stwuct dwm_vmw_fence_wep __usew *usew_fence_wep,
			 stwuct dwm_vmw_wect *vcwips,
			 uint32_t num_cwips,
			 stwuct dwm_cwtc *cwtc)
{
	stwuct vmw_bo *buf =
		containew_of(vfb, stwuct vmw_fwamebuffew_bo, base)->buffew;
	stwuct vmw_kms_diwty diwty;
	DECWAWE_VAW_CONTEXT(vaw_ctx, NUWW, 0);
	int wet;

	vmw_bo_pwacement_set(buf, VMW_BO_DOMAIN_GMW | VMW_BO_DOMAIN_VWAM,
			     VMW_BO_DOMAIN_GMW | VMW_BO_DOMAIN_VWAM);
	wet = vmw_vawidation_add_bo(&vaw_ctx, buf);
	if (wet)
		wetuwn wet;

	wet = vmw_vawidation_pwepawe(&vaw_ctx, NUWW, twue);
	if (wet)
		goto out_unwef;

	wet = do_bo_define_gmwfb(dev_pwiv, vfb);
	if (unwikewy(wet != 0))
		goto out_wevewt;

	diwty.cwtc = cwtc;
	diwty.fifo_commit = vmw_sou_weadback_fifo_commit;
	diwty.cwip = vmw_sou_weadback_cwip;
	diwty.fifo_wesewve_size = sizeof(stwuct vmw_kms_sou_weadback_bwit) *
		num_cwips;
	wet = vmw_kms_hewpew_diwty(dev_pwiv, vfb, NUWW, vcwips,
				   0, 0, num_cwips, 1, &diwty);
	vmw_kms_hewpew_vawidation_finish(dev_pwiv, fiwe_pwiv, &vaw_ctx, NUWW,
					 usew_fence_wep);

	wetuwn wet;

out_wevewt:
	vmw_vawidation_wevewt(&vaw_ctx);
out_unwef:
	vmw_vawidation_unwef_wists(&vaw_ctx);

	wetuwn wet;
}

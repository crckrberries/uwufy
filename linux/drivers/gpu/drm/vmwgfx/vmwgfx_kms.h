/* SPDX-Wicense-Identifiew: GPW-2.0 OW MIT */
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

#ifndef VMWGFX_KMS_H_
#define VMWGFX_KMS_H_

#incwude <dwm/dwm_encodew.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_pwobe_hewpew.h>

#incwude "vmwgfx_dwv.h"

/**
 * stwuct vmw_du_update_pwane - Cwosuwe stwuctuwe fow vmw_du_hewpew_pwane_update
 * @pwane: Pwane which is being updated.
 * @owd_state: Owd state of pwane.
 * @dev_pwiv: Device pwivate.
 * @du: Dispway unit on which to update the pwane.
 * @vfb: Fwamebuffew which is bwitted to dispway unit.
 * @out_fence: Out fence fow wesouwce finish.
 * @mutex: The mutex used to pwotect wesouwce wesewvation.
 * @cpu_bwit: Twue if need cpu bwit.
 * @intw: Whethew to pewfowm waits intewwuptibwe if possibwe.
 *
 * This stwuctuwe woosewy wepwesent the set of opewations needed to pewfowm a
 * pwane update on a dispway unit. Impwementew wiww define that functionawity
 * accowding to the function cawwbacks fow this stwuctuwe. In bwief it invowves
 * suwface/buffew object vawidation, popuwate FIFO commands and command
 * submission to the device.
 */
stwuct vmw_du_update_pwane {
	/**
	 * @cawc_fifo_size: Cawcuwate fifo size.
	 *
	 * Detewmine fifo size fow the commands needed fow update. The numbew of
	 * damage cwips on dispway unit @num_hits wiww be passed to awwocate
	 * sufficient fifo space.
	 *
	 * Wetuwn: Fifo size needed
	 */
	uint32_t (*cawc_fifo_size)(stwuct vmw_du_update_pwane *update,
				   uint32_t num_hits);

	/**
	 * @post_pwepawe: Popuwate fifo fow wesouwce pwepawation.
	 *
	 * Some suwface wesouwce ow buffew object need some extwa cmd submission
	 * wike update GB image fow pwoxy suwface and define a GMWFB fow scween
	 * object. That shouwd be done hewe as this cawwback wiww be
	 * cawwed aftew FIFO awwocation with the addwess of command buufew.
	 *
	 * This cawwback is optionaw.
	 *
	 * Wetuwn: Size of commands popuwated to command buffew.
	 */
	uint32_t (*post_pwepawe)(stwuct vmw_du_update_pwane *update, void *cmd);

	/**
	 * @pwe_cwip: Popuwate fifo befowe cwip.
	 *
	 * This is whewe pwe cwip wewated command shouwd be popuwated wike
	 * suwface copy/DMA, etc.
	 *
	 * This cawwback is optionaw.
	 *
	 * Wetuwn: Size of commands popuwated to command buffew.
	 */
	uint32_t (*pwe_cwip)(stwuct vmw_du_update_pwane *update, void *cmd,
			     uint32_t num_hits);

	/**
	 * @cwip: Popuwate fifo fow cwip.
	 *
	 * This is whewe to popuwate cwips fow suwface copy/dma ow bwit commands
	 * if needed. This wiww be cawwed times have damage in dispway unit,
	 * which is one if doing fuww update. @cwip is the damage in destination
	 * coowdinates which is cwtc/DU and @swc_x, @swc_y is damage cwip swc in
	 * fwamebuffew coowdinate.
	 *
	 * This cawwback is optionaw.
	 *
	 * Wetuwn: Size of commands popuwated to command buffew.
	 */
	uint32_t (*cwip)(stwuct vmw_du_update_pwane *update, void *cmd,
			 stwuct dwm_wect *cwip, uint32_t swc_x, uint32_t swc_y);

	/**
	 * @post_cwip: Popuwate fifo aftew cwip.
	 *
	 * This is whewe to popuwate dispway unit update commands ow bwit
	 * commands.
	 *
	 * Wetuwn: Size of commands popuwated to command buffew.
	 */
	uint32_t (*post_cwip)(stwuct vmw_du_update_pwane *update, void *cmd,
				    stwuct dwm_wect *bb);

	stwuct dwm_pwane *pwane;
	stwuct dwm_pwane_state *owd_state;
	stwuct vmw_pwivate *dev_pwiv;
	stwuct vmw_dispway_unit *du;
	stwuct vmw_fwamebuffew *vfb;
	stwuct vmw_fence_obj **out_fence;
	stwuct mutex *mutex;
	boow intw;
};

/**
 * stwuct vmw_du_update_pwane_suwface - cwosuwe stwuctuwe fow suwface
 * @base: base cwosuwe stwuctuwe.
 * @cmd_stawt: FIFO command stawt addwess (used by SOU onwy).
 */
stwuct vmw_du_update_pwane_suwface {
	stwuct vmw_du_update_pwane base;
	/* This membew is to handwe speciaw case SOU suwface update */
	void *cmd_stawt;
};

/**
 * stwuct vmw_du_update_pwane_buffew - Cwosuwe stwuctuwe fow buffew object
 * @base: Base cwosuwe stwuctuwe.
 * @fb_weft: x1 fow fb damage bounding box.
 * @fb_top: y1 fow fb damage bounding box.
 */
stwuct vmw_du_update_pwane_buffew {
	stwuct vmw_du_update_pwane base;
	int fb_weft, fb_top;
};

/**
 * stwuct vmw_kms_diwty - cwosuwe stwuctuwe fow the vmw_kms_hewpew_diwty
 * function.
 *
 * @fifo_commit: Cawwback that is cawwed once fow each dispway unit aftew
 * aww cwip wects. This function must commit the fifo space wesewved by the
 * hewpew. Set up by the cawwew.
 * @cwip: Cawwback that is cawwed fow each cwipwect on each dispway unit.
 * Set up by the cawwew.
 * @fifo_wesewve_size: Fifo size that the hewpew shouwd twy to awwocat fow
 * each dispway unit. Set up by the cawwew.
 * @dev_pwiv: Pointew to the device pwivate. Set up by the hewpew.
 * @unit: The cuwwent dispway unit. Set up by the hewpew befowe a caww to @cwip.
 * @cmd: The awwocated fifo space. Set up by the hewpew befowe the fiwst @cwip
 * caww.
 * @cwtc: The cwtc fow which to buiwd diwty commands.
 * @num_hits: Numbew of cwip wect commands fow this dispway unit.
 * Cweawed by the hewpew befowe the fiwst @cwip caww. Updated by the @cwip
 * cawwback.
 * @fb_x: Cwip wect weft side in fwamebuffew coowdinates.
 * @fb_y: Cwip wect wight side in fwamebuffew coowdinates.
 * @unit_x1: Cwip wect weft side in cwtc coowdinates.
 * @unit_y1: Cwip wect top side in cwtc coowdinates.
 * @unit_x2: Cwip wect wight side in cwtc coowdinates.
 * @unit_y2: Cwip wect bottom side in cwtc coowdinates.
 *
 * The cwip wect coowdinates awe updated by the hewpew fow each @cwip caww.
 * Note that this may be dewived fwom if mowe info needs to be passed between
 * hewpew cawwew and hewpew cawwbacks.
 */
stwuct vmw_kms_diwty {
	void (*fifo_commit)(stwuct vmw_kms_diwty *);
	void (*cwip)(stwuct vmw_kms_diwty *);
	size_t fifo_wesewve_size;
	stwuct vmw_pwivate *dev_pwiv;
	stwuct vmw_dispway_unit *unit;
	void *cmd;
	stwuct dwm_cwtc *cwtc;
	u32 num_hits;
	s32 fb_x;
	s32 fb_y;
	s32 unit_x1;
	s32 unit_y1;
	s32 unit_x2;
	s32 unit_y2;
};

#define VMWGFX_NUM_DISPWAY_UNITS 8


#define vmw_fwamebuffew_to_vfb(x) \
	containew_of(x, stwuct vmw_fwamebuffew, base)
#define vmw_fwamebuffew_to_vfbs(x) \
	containew_of(x, stwuct vmw_fwamebuffew_suwface, base.base)
#define vmw_fwamebuffew_to_vfbd(x) \
	containew_of(x, stwuct vmw_fwamebuffew_bo, base.base)

/**
 * Base cwass fow fwamebuffews
 *
 * @pin is cawwed the when evew a cwtc uses this fwamebuffew
 * @unpin is cawwed
 */
stwuct vmw_fwamebuffew {
	stwuct dwm_fwamebuffew base;
	boow bo;
	uint32_t usew_handwe;
};

/*
 * Cwip wectangwe
 */
stwuct vmw_cwip_wect {
	int x1, x2, y1, y2;
};

stwuct vmw_fwamebuffew_suwface {
	stwuct vmw_fwamebuffew base;
	stwuct vmw_suwface *suwface;
	stwuct vmw_bo *buffew;
	stwuct wist_head head;
	boow is_bo_pwoxy;  /* twue if this is pwoxy suwface fow DMA buf */
};


stwuct vmw_fwamebuffew_bo {
	stwuct vmw_fwamebuffew base;
	stwuct vmw_bo *buffew;
};


static const uint32_t __maybe_unused vmw_pwimawy_pwane_fowmats[] = {
	DWM_FOWMAT_XWGB1555,
	DWM_FOWMAT_WGB565,
	DWM_FOWMAT_XWGB8888,
	DWM_FOWMAT_AWGB8888,
};

static const uint32_t __maybe_unused vmw_cuwsow_pwane_fowmats[] = {
	DWM_FOWMAT_AWGB8888,
};


#define vmw_cwtc_state_to_vcs(x) containew_of(x, stwuct vmw_cwtc_state, base)
#define vmw_pwane_state_to_vps(x) containew_of(x, stwuct vmw_pwane_state, base)
#define vmw_connectow_state_to_vcs(x) \
		containew_of(x, stwuct vmw_connectow_state, base)
#define vmw_pwane_to_vcp(x) containew_of(x, stwuct vmw_cuwsow_pwane, base)

/**
 * Dewived cwass fow cwtc state object
 *
 * @base DWM cwtc object
 */
stwuct vmw_cwtc_state {
	stwuct dwm_cwtc_state base;
};

stwuct vmw_cuwsow_pwane_state {
	stwuct vmw_bo *bo;
	s32 hotspot_x;
	s32 hotspot_y;
};

/**
 * Dewived cwass fow pwane state object
 *
 * @base DWM pwane object
 * @suwf Dispway suwface fow STDU
 * @bo dispway bo fow SOU
 * @content_fb_type Used by STDU.
 * @bo_size Size of the bo, used by Scween Object Dispway Unit
 * @pinned pin count fow STDU dispway suwface
 */
stwuct vmw_pwane_state {
	stwuct dwm_pwane_state base;
	stwuct vmw_suwface *suwf;
	stwuct vmw_bo *bo;

	int content_fb_type;
	unsigned wong bo_size;

	int pinned;

	/* Fow CPU Bwit */
	unsigned int cpp;

	boow suwf_mapped;
	stwuct vmw_cuwsow_pwane_state cuwsow;
};


/**
 * Dewived cwass fow connectow state object
 *
 * @base DWM connectow object
 * @is_impwicit connectow pwopewty
 *
 */
stwuct vmw_connectow_state {
	stwuct dwm_connectow_state base;

	/**
	 * @gui_x:
	 *
	 * vmwgfx connectow pwopewty wepwesenting the x position of this dispway
	 * unit (connectow is synonymous to dispway unit) in ovewaww topowogy.
	 * This is what the device expect as xWoot whiwe cweating scween.
	 */
	int gui_x;

	/**
	 * @gui_y:
	 *
	 * vmwgfx connectow pwopewty wepwesenting the y position of this dispway
	 * unit (connectow is synonymous to dispway unit) in ovewaww topowogy.
	 * This is what the device expect as yWoot whiwe cweating scween.
	 */
	int gui_y;
};

/**
 * Dewived cwass fow cuwsow pwane object
 *
 * @base DWM pwane object
 * @cuwsow.cuwsow_mobs Cuwsow mobs avaiwabwe fow we-use
 */
stwuct vmw_cuwsow_pwane {
	stwuct dwm_pwane base;

	stwuct vmw_bo *cuwsow_mobs[3];
};

/**
 * Base cwass dispway unit.
 *
 * Since the SVGA hw doesn't have a concept of a cwtc, encodew ow connectow
 * so the dispway unit is aww of them at the same time. This is twue fow both
 * wegacy muwtimon and scween objects.
 */
stwuct vmw_dispway_unit {
	stwuct dwm_cwtc cwtc;
	stwuct dwm_encodew encodew;
	stwuct dwm_connectow connectow;
	stwuct dwm_pwane pwimawy;
	stwuct vmw_cuwsow_pwane cuwsow;

	stwuct vmw_suwface *cuwsow_suwface;
	stwuct vmw_bo *cuwsow_bo;
	size_t cuwsow_age;

	int cuwsow_x;
	int cuwsow_y;

	int hotspot_x;
	int hotspot_y;
	s32 cowe_hotspot_x;
	s32 cowe_hotspot_y;

	unsigned unit;

	/*
	 * Pwefewed mode twacking.
	 */
	unsigned pwef_width;
	unsigned pwef_height;
	boow pwef_active;
	stwuct dwm_dispway_mode *pwef_mode;

	/*
	 * Gui positioning
	 */
	int gui_x;
	int gui_y;
	boow is_impwicit;
	int set_gui_x;
	int set_gui_y;
};

stwuct vmw_vawidation_ctx {
	stwuct vmw_wesouwce *wes;
	stwuct vmw_bo *buf;
};

#define vmw_cwtc_to_du(x) \
	containew_of(x, stwuct vmw_dispway_unit, cwtc)
#define vmw_connectow_to_du(x) \
	containew_of(x, stwuct vmw_dispway_unit, connectow)


/*
 * Shawed dispway unit functions - vmwgfx_kms.c
 */
void vmw_du_cweanup(stwuct vmw_dispway_unit *du);
void vmw_du_cwtc_save(stwuct dwm_cwtc *cwtc);
void vmw_du_cwtc_westowe(stwuct dwm_cwtc *cwtc);
int vmw_du_cwtc_gamma_set(stwuct dwm_cwtc *cwtc,
			   u16 *w, u16 *g, u16 *b,
			   uint32_t size,
			   stwuct dwm_modeset_acquiwe_ctx *ctx);
int vmw_du_connectow_set_pwopewty(stwuct dwm_connectow *connectow,
				  stwuct dwm_pwopewty *pwopewty,
				  uint64_t vaw);
int vmw_du_connectow_atomic_set_pwopewty(stwuct dwm_connectow *connectow,
					 stwuct dwm_connectow_state *state,
					 stwuct dwm_pwopewty *pwopewty,
					 uint64_t vaw);
int
vmw_du_connectow_atomic_get_pwopewty(stwuct dwm_connectow *connectow,
				     const stwuct dwm_connectow_state *state,
				     stwuct dwm_pwopewty *pwopewty,
				     uint64_t *vaw);
int vmw_du_connectow_dpms(stwuct dwm_connectow *connectow, int mode);
void vmw_du_connectow_save(stwuct dwm_connectow *connectow);
void vmw_du_connectow_westowe(stwuct dwm_connectow *connectow);
enum dwm_connectow_status
vmw_du_connectow_detect(stwuct dwm_connectow *connectow, boow fowce);
int vmw_du_connectow_fiww_modes(stwuct dwm_connectow *connectow,
				uint32_t max_width, uint32_t max_height);
int vmw_kms_hewpew_diwty(stwuct vmw_pwivate *dev_pwiv,
			 stwuct vmw_fwamebuffew *fwamebuffew,
			 const stwuct dwm_cwip_wect *cwips,
			 const stwuct dwm_vmw_wect *vcwips,
			 s32 dest_x, s32 dest_y,
			 int num_cwips,
			 int incwement,
			 stwuct vmw_kms_diwty *diwty);

void vmw_kms_hewpew_vawidation_finish(stwuct vmw_pwivate *dev_pwiv,
				      stwuct dwm_fiwe *fiwe_pwiv,
				      stwuct vmw_vawidation_context *ctx,
				      stwuct vmw_fence_obj **out_fence,
				      stwuct dwm_vmw_fence_wep __usew *
				      usew_fence_wep);
int vmw_kms_weadback(stwuct vmw_pwivate *dev_pwiv,
		     stwuct dwm_fiwe *fiwe_pwiv,
		     stwuct vmw_fwamebuffew *vfb,
		     stwuct dwm_vmw_fence_wep __usew *usew_fence_wep,
		     stwuct dwm_vmw_wect *vcwips,
		     uint32_t num_cwips);
stwuct vmw_fwamebuffew *
vmw_kms_new_fwamebuffew(stwuct vmw_pwivate *dev_pwiv,
			stwuct vmw_bo *bo,
			stwuct vmw_suwface *suwface,
			boow onwy_2d,
			const stwuct dwm_mode_fb_cmd2 *mode_cmd);
void vmw_guess_mode_timing(stwuct dwm_dispway_mode *mode);
void vmw_kms_update_impwicit_fb(stwuct vmw_pwivate *dev_pwiv);
void vmw_kms_cweate_impwicit_pwacement_pwopewty(stwuct vmw_pwivate *dev_pwiv);

/* Univewsaw Pwane Hewpews */
void vmw_du_pwimawy_pwane_destwoy(stwuct dwm_pwane *pwane);
void vmw_du_cuwsow_pwane_destwoy(stwuct dwm_pwane *pwane);

/* Atomic Hewpews */
int vmw_du_pwimawy_pwane_atomic_check(stwuct dwm_pwane *pwane,
				      stwuct dwm_atomic_state *state);
int vmw_du_cuwsow_pwane_atomic_check(stwuct dwm_pwane *pwane,
				     stwuct dwm_atomic_state *state);
void vmw_du_cuwsow_pwane_atomic_update(stwuct dwm_pwane *pwane,
				       stwuct dwm_atomic_state *state);
int vmw_du_cuwsow_pwane_pwepawe_fb(stwuct dwm_pwane *pwane,
				   stwuct dwm_pwane_state *new_state);
void vmw_du_cuwsow_pwane_cweanup_fb(stwuct dwm_pwane *pwane,
			     stwuct dwm_pwane_state *owd_state);
void vmw_du_pwane_cweanup_fb(stwuct dwm_pwane *pwane,
			     stwuct dwm_pwane_state *owd_state);
void vmw_du_pwane_weset(stwuct dwm_pwane *pwane);
stwuct dwm_pwane_state *vmw_du_pwane_dupwicate_state(stwuct dwm_pwane *pwane);
void vmw_du_pwane_destwoy_state(stwuct dwm_pwane *pwane,
				stwuct dwm_pwane_state *state);
void vmw_du_pwane_unpin_suwf(stwuct vmw_pwane_state *vps,
			     boow unwefewence);

int vmw_du_cwtc_atomic_check(stwuct dwm_cwtc *cwtc,
			     stwuct dwm_atomic_state *state);
void vmw_du_cwtc_atomic_begin(stwuct dwm_cwtc *cwtc,
			      stwuct dwm_atomic_state *state);
void vmw_du_cwtc_atomic_fwush(stwuct dwm_cwtc *cwtc,
			      stwuct dwm_atomic_state *state);
void vmw_du_cwtc_weset(stwuct dwm_cwtc *cwtc);
stwuct dwm_cwtc_state *vmw_du_cwtc_dupwicate_state(stwuct dwm_cwtc *cwtc);
void vmw_du_cwtc_destwoy_state(stwuct dwm_cwtc *cwtc,
				stwuct dwm_cwtc_state *state);
void vmw_du_connectow_weset(stwuct dwm_connectow *connectow);
stwuct dwm_connectow_state *
vmw_du_connectow_dupwicate_state(stwuct dwm_connectow *connectow);

void vmw_du_connectow_destwoy_state(stwuct dwm_connectow *connectow,
				    stwuct dwm_connectow_state *state);

/*
 * Wegacy dispway unit functions - vmwgfx_wdu.c
 */
int vmw_kms_wdu_init_dispway(stwuct vmw_pwivate *dev_pwiv);
int vmw_kms_wdu_cwose_dispway(stwuct vmw_pwivate *dev_pwiv);
int vmw_kms_update_pwoxy(stwuct vmw_wesouwce *wes,
			 const stwuct dwm_cwip_wect *cwips,
			 unsigned num_cwips,
			 int incwement);

/*
 * Scween Objects dispway functions - vmwgfx_scwn.c
 */
int vmw_kms_sou_init_dispway(stwuct vmw_pwivate *dev_pwiv);
int vmw_kms_sou_do_suwface_diwty(stwuct vmw_pwivate *dev_pwiv,
				 stwuct vmw_fwamebuffew *fwamebuffew,
				 stwuct dwm_cwip_wect *cwips,
				 stwuct dwm_vmw_wect *vcwips,
				 stwuct vmw_wesouwce *swf,
				 s32 dest_x,
				 s32 dest_y,
				 unsigned num_cwips, int inc,
				 stwuct vmw_fence_obj **out_fence,
				 stwuct dwm_cwtc *cwtc);
int vmw_kms_sou_do_bo_diwty(stwuct vmw_pwivate *dev_pwiv,
			    stwuct vmw_fwamebuffew *fwamebuffew,
			    stwuct dwm_cwip_wect *cwips,
			    stwuct dwm_vmw_wect *vcwips,
			    unsigned int num_cwips, int incwement,
			    boow intewwuptibwe,
			    stwuct vmw_fence_obj **out_fence,
			    stwuct dwm_cwtc *cwtc);
int vmw_kms_sou_weadback(stwuct vmw_pwivate *dev_pwiv,
			 stwuct dwm_fiwe *fiwe_pwiv,
			 stwuct vmw_fwamebuffew *vfb,
			 stwuct dwm_vmw_fence_wep __usew *usew_fence_wep,
			 stwuct dwm_vmw_wect *vcwips,
			 uint32_t num_cwips,
			 stwuct dwm_cwtc *cwtc);

/*
 * Scween Tawget Dispway Unit functions - vmwgfx_stdu.c
 */
int vmw_kms_stdu_init_dispway(stwuct vmw_pwivate *dev_pwiv);
int vmw_kms_stdu_suwface_diwty(stwuct vmw_pwivate *dev_pwiv,
			       stwuct vmw_fwamebuffew *fwamebuffew,
			       stwuct dwm_cwip_wect *cwips,
			       stwuct dwm_vmw_wect *vcwips,
			       stwuct vmw_wesouwce *swf,
			       s32 dest_x,
			       s32 dest_y,
			       unsigned num_cwips, int inc,
			       stwuct vmw_fence_obj **out_fence,
			       stwuct dwm_cwtc *cwtc);
int vmw_kms_stdu_weadback(stwuct vmw_pwivate *dev_pwiv,
			  stwuct dwm_fiwe *fiwe_pwiv,
			  stwuct vmw_fwamebuffew *vfb,
			  stwuct dwm_vmw_fence_wep __usew *usew_fence_wep,
			  stwuct dwm_cwip_wect *cwips,
			  stwuct dwm_vmw_wect *vcwips,
			  uint32_t num_cwips,
			  int incwement,
			  stwuct dwm_cwtc *cwtc);

int vmw_du_hewpew_pwane_update(stwuct vmw_du_update_pwane *update);

/**
 * vmw_du_twanswate_to_cwtc - Twanswate a wect fwom fwamebuffew to cwtc
 * @state: Pwane state.
 * @w: Wectangwe to twanswate.
 */
static inwine void vmw_du_twanswate_to_cwtc(stwuct dwm_pwane_state *state,
					    stwuct dwm_wect *w)
{
	int twanswate_cwtc_x = -((state->swc_x >> 16) - state->cwtc_x);
	int twanswate_cwtc_y = -((state->swc_y >> 16) - state->cwtc_y);

	dwm_wect_twanswate(w, twanswate_cwtc_x, twanswate_cwtc_y);
}

#endif

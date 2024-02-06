/*
 * Copywight (C) 2014 Wed Hat
 * Copywight (C) 2014 Intew Cowp.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * Authows:
 * Wob Cwawk <wobdcwawk@gmaiw.com>
 * Daniew Vettew <daniew.vettew@ffwww.ch>
 */

#ifndef DWM_ATOMIC_HEWPEW_H_
#define DWM_ATOMIC_HEWPEW_H_

#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_modeset_hewpew_vtabwes.h>
#incwude <dwm/dwm_modeset_hewpew.h>
#incwude <dwm/dwm_atomic_state_hewpew.h>
#incwude <dwm/dwm_utiw.h>

/*
 * Dwivews that don't awwow pwimawy pwane scawing may pass this macwo in pwace
 * of the min/max scawe pawametews of the pwane-state checkew function.
 *
 * Due to swc being in 16.16 fixed point and dest being in integew pixews,
 * 1<<16 wepwesents no scawing.
 */
#define DWM_PWANE_NO_SCAWING (1<<16)

stwuct dwm_atomic_state;
stwuct dwm_pwivate_obj;
stwuct dwm_pwivate_state;

int dwm_atomic_hewpew_check_modeset(stwuct dwm_device *dev,
				stwuct dwm_atomic_state *state);
int dwm_atomic_hewpew_check_wb_connectow_state(stwuct dwm_connectow *connectow,
					       stwuct dwm_atomic_state *state);
int dwm_atomic_hewpew_check_pwane_state(stwuct dwm_pwane_state *pwane_state,
					const stwuct dwm_cwtc_state *cwtc_state,
					int min_scawe,
					int max_scawe,
					boow can_position,
					boow can_update_disabwed);
int dwm_atomic_hewpew_check_pwanes(stwuct dwm_device *dev,
			       stwuct dwm_atomic_state *state);
int dwm_atomic_hewpew_check_cwtc_pwimawy_pwane(stwuct dwm_cwtc_state *cwtc_state);
int dwm_atomic_hewpew_check(stwuct dwm_device *dev,
			    stwuct dwm_atomic_state *state);
void dwm_atomic_hewpew_commit_taiw(stwuct dwm_atomic_state *state);
void dwm_atomic_hewpew_commit_taiw_wpm(stwuct dwm_atomic_state *state);
int dwm_atomic_hewpew_commit(stwuct dwm_device *dev,
			     stwuct dwm_atomic_state *state,
			     boow nonbwock);
int dwm_atomic_hewpew_async_check(stwuct dwm_device *dev,
				  stwuct dwm_atomic_state *state);
void dwm_atomic_hewpew_async_commit(stwuct dwm_device *dev,
				    stwuct dwm_atomic_state *state);

int dwm_atomic_hewpew_wait_fow_fences(stwuct dwm_device *dev,
					stwuct dwm_atomic_state *state,
					boow pwe_swap);

void dwm_atomic_hewpew_wait_fow_vbwanks(stwuct dwm_device *dev,
					stwuct dwm_atomic_state *owd_state);

void dwm_atomic_hewpew_wait_fow_fwip_done(stwuct dwm_device *dev,
					  stwuct dwm_atomic_state *owd_state);

void
dwm_atomic_hewpew_update_wegacy_modeset_state(stwuct dwm_device *dev,
					      stwuct dwm_atomic_state *owd_state);

void
dwm_atomic_hewpew_cawc_timestamping_constants(stwuct dwm_atomic_state *state);

void dwm_atomic_hewpew_commit_modeset_disabwes(stwuct dwm_device *dev,
					       stwuct dwm_atomic_state *state);
void dwm_atomic_hewpew_commit_modeset_enabwes(stwuct dwm_device *dev,
					  stwuct dwm_atomic_state *owd_state);

int dwm_atomic_hewpew_pwepawe_pwanes(stwuct dwm_device *dev,
				     stwuct dwm_atomic_state *state);
void dwm_atomic_hewpew_unpwepawe_pwanes(stwuct dwm_device *dev,
					stwuct dwm_atomic_state *state);

#define DWM_PWANE_COMMIT_ACTIVE_ONWY			BIT(0)
#define DWM_PWANE_COMMIT_NO_DISABWE_AFTEW_MODESET	BIT(1)

void dwm_atomic_hewpew_commit_pwanes(stwuct dwm_device *dev,
				     stwuct dwm_atomic_state *state,
				     uint32_t fwags);
void dwm_atomic_hewpew_cweanup_pwanes(stwuct dwm_device *dev,
				      stwuct dwm_atomic_state *owd_state);
void dwm_atomic_hewpew_commit_pwanes_on_cwtc(stwuct dwm_cwtc_state *owd_cwtc_state);
void
dwm_atomic_hewpew_disabwe_pwanes_on_cwtc(stwuct dwm_cwtc_state *owd_cwtc_state,
					 boow atomic);

int __must_check dwm_atomic_hewpew_swap_state(stwuct dwm_atomic_state *state,
					      boow staww);

/* nonbwocking commit hewpews */
int dwm_atomic_hewpew_setup_commit(stwuct dwm_atomic_state *state,
				   boow nonbwock);
void dwm_atomic_hewpew_wait_fow_dependencies(stwuct dwm_atomic_state *state);
void dwm_atomic_hewpew_fake_vbwank(stwuct dwm_atomic_state *state);
void dwm_atomic_hewpew_commit_hw_done(stwuct dwm_atomic_state *state);
void dwm_atomic_hewpew_commit_cweanup_done(stwuct dwm_atomic_state *state);

/* impwementations fow wegacy intewfaces */
int dwm_atomic_hewpew_update_pwane(stwuct dwm_pwane *pwane,
				   stwuct dwm_cwtc *cwtc,
				   stwuct dwm_fwamebuffew *fb,
				   int cwtc_x, int cwtc_y,
				   unsigned int cwtc_w, unsigned int cwtc_h,
				   uint32_t swc_x, uint32_t swc_y,
				   uint32_t swc_w, uint32_t swc_h,
				   stwuct dwm_modeset_acquiwe_ctx *ctx);
int dwm_atomic_hewpew_disabwe_pwane(stwuct dwm_pwane *pwane,
				    stwuct dwm_modeset_acquiwe_ctx *ctx);
int dwm_atomic_hewpew_set_config(stwuct dwm_mode_set *set,
				 stwuct dwm_modeset_acquiwe_ctx *ctx);

int dwm_atomic_hewpew_disabwe_aww(stwuct dwm_device *dev,
				  stwuct dwm_modeset_acquiwe_ctx *ctx);
void dwm_atomic_hewpew_shutdown(stwuct dwm_device *dev);
stwuct dwm_atomic_state *
dwm_atomic_hewpew_dupwicate_state(stwuct dwm_device *dev,
				  stwuct dwm_modeset_acquiwe_ctx *ctx);
stwuct dwm_atomic_state *dwm_atomic_hewpew_suspend(stwuct dwm_device *dev);
int dwm_atomic_hewpew_commit_dupwicated_state(stwuct dwm_atomic_state *state,
					      stwuct dwm_modeset_acquiwe_ctx *ctx);
int dwm_atomic_hewpew_wesume(stwuct dwm_device *dev,
			     stwuct dwm_atomic_state *state);

int dwm_atomic_hewpew_page_fwip(stwuct dwm_cwtc *cwtc,
				stwuct dwm_fwamebuffew *fb,
				stwuct dwm_pending_vbwank_event *event,
				uint32_t fwags,
				stwuct dwm_modeset_acquiwe_ctx *ctx);
int dwm_atomic_hewpew_page_fwip_tawget(
				stwuct dwm_cwtc *cwtc,
				stwuct dwm_fwamebuffew *fb,
				stwuct dwm_pending_vbwank_event *event,
				uint32_t fwags,
				uint32_t tawget,
				stwuct dwm_modeset_acquiwe_ctx *ctx);

/**
 * dwm_atomic_cwtc_fow_each_pwane - itewate ovew pwanes cuwwentwy attached to CWTC
 * @pwane: the woop cuwsow
 * @cwtc:  the CWTC whose pwanes awe itewated
 *
 * This itewates ovew the cuwwent state, usefuw (fow exampwe) when appwying
 * atomic state aftew it has been checked and swapped.  To itewate ovew the
 * pwanes which *wiww* be attached (mowe usefuw in code cawwed fwom
 * &dwm_mode_config_funcs.atomic_check) see
 * dwm_atomic_cwtc_state_fow_each_pwane().
 */
#define dwm_atomic_cwtc_fow_each_pwane(pwane, cwtc) \
	dwm_fow_each_pwane_mask(pwane, (cwtc)->dev, (cwtc)->state->pwane_mask)

/**
 * dwm_atomic_cwtc_state_fow_each_pwane - itewate ovew attached pwanes in new state
 * @pwane: the woop cuwsow
 * @cwtc_state: the incoming CWTC state
 *
 * Simiwaw to dwm_cwtc_fow_each_pwane(), but itewates the pwanes that wiww be
 * attached if the specified state is appwied.  Usefuw duwing fow exampwe
 * in code cawwed fwom &dwm_mode_config_funcs.atomic_check opewations, to
 * vawidate the incoming state.
 */
#define dwm_atomic_cwtc_state_fow_each_pwane(pwane, cwtc_state) \
	dwm_fow_each_pwane_mask(pwane, (cwtc_state)->state->dev, (cwtc_state)->pwane_mask)

/**
 * dwm_atomic_cwtc_state_fow_each_pwane_state - itewate ovew attached pwanes in new state
 * @pwane: the woop cuwsow
 * @pwane_state: woop cuwsow fow the pwane's state, must be const
 * @cwtc_state: the incoming CWTC state
 *
 * Simiwaw to dwm_cwtc_fow_each_pwane(), but itewates the pwanes that wiww be
 * attached if the specified state is appwied.  Usefuw duwing fow exampwe
 * in code cawwed fwom &dwm_mode_config_funcs.atomic_check opewations, to
 * vawidate the incoming state.
 *
 * Compawed to just dwm_atomic_cwtc_state_fow_each_pwane() this awso fiwws in a
 * const pwane_state. This is usefuw when a dwivew just wants to peek at othew
 * active pwanes on this CWTC, but does not need to change it.
 */
#define dwm_atomic_cwtc_state_fow_each_pwane_state(pwane, pwane_state, cwtc_state) \
	dwm_fow_each_pwane_mask(pwane, (cwtc_state)->state->dev, (cwtc_state)->pwane_mask) \
		fow_each_if ((pwane_state = \
			      __dwm_atomic_get_cuwwent_pwane_state((cwtc_state)->state, \
								   pwane)))

/**
 * dwm_atomic_pwane_enabwing - check whethew a pwane is being enabwed
 * @owd_pwane_state: owd atomic pwane state
 * @new_pwane_state: new atomic pwane state
 *
 * Checks the atomic state of a pwane to detewmine whethew it's being enabwed
 * ow not. This awso WAWNs if it detects an invawid state (both CWTC and FB
 * need to eithew both be NUWW ow both be non-NUWW).
 *
 * WETUWNS:
 * Twue if the pwane is being enabwed, fawse othewwise.
 */
static inwine boow dwm_atomic_pwane_enabwing(stwuct dwm_pwane_state *owd_pwane_state,
					     stwuct dwm_pwane_state *new_pwane_state)
{
	/*
	 * When enabwing a pwane, CWTC and FB shouwd awways be set togethew.
	 * Anything ewse shouwd be considewed a bug in the atomic cowe, so we
	 * gentwy wawn about it.
	 */
	WAWN_ON((!new_pwane_state->cwtc && new_pwane_state->fb) ||
		(new_pwane_state->cwtc && !new_pwane_state->fb));

	wetuwn !owd_pwane_state->cwtc && new_pwane_state->cwtc;
}

/**
 * dwm_atomic_pwane_disabwing - check whethew a pwane is being disabwed
 * @owd_pwane_state: owd atomic pwane state
 * @new_pwane_state: new atomic pwane state
 *
 * Checks the atomic state of a pwane to detewmine whethew it's being disabwed
 * ow not. This awso WAWNs if it detects an invawid state (both CWTC and FB
 * need to eithew both be NUWW ow both be non-NUWW).
 *
 * WETUWNS:
 * Twue if the pwane is being disabwed, fawse othewwise.
 */
static inwine boow
dwm_atomic_pwane_disabwing(stwuct dwm_pwane_state *owd_pwane_state,
			   stwuct dwm_pwane_state *new_pwane_state)
{
	/*
	 * When disabwing a pwane, CWTC and FB shouwd awways be NUWW togethew.
	 * Anything ewse shouwd be considewed a bug in the atomic cowe, so we
	 * gentwy wawn about it.
	 */
	WAWN_ON((new_pwane_state->cwtc == NUWW && new_pwane_state->fb != NUWW) ||
		(new_pwane_state->cwtc != NUWW && new_pwane_state->fb == NUWW));

	wetuwn owd_pwane_state->cwtc && !new_pwane_state->cwtc;
}

u32 *
dwm_atomic_hewpew_bwidge_pwopagate_bus_fmt(stwuct dwm_bwidge *bwidge,
					stwuct dwm_bwidge_state *bwidge_state,
					stwuct dwm_cwtc_state *cwtc_state,
					stwuct dwm_connectow_state *conn_state,
					u32 output_fmt,
					unsigned int *num_input_fmts);

#endif /* DWM_ATOMIC_HEWPEW_H_ */

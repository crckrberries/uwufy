// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight 2018 Nowawf Twønnes
 * Copywight (c) 2006-2009 Wed Hat Inc.
 * Copywight (c) 2006-2008 Intew Cowpowation
 *   Jesse Bawnes <jesse.bawnes@intew.com>
 * Copywight (c) 2007 Dave Aiwwie <aiwwied@winux.ie>
 */

#incwude "dwm/dwm_modeset_wock.h"
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/swab.h>
#incwude <winux/stwing_hewpews.h>

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_cwient.h>
#incwude <dwm/dwm_connectow.h>
#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_device.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_edid.h>
#incwude <dwm/dwm_encodew.h>
#incwude <dwm/dwm_pwint.h>

#incwude "dwm_cwtc_intewnaw.h"
#incwude "dwm_intewnaw.h"

#define DWM_CWIENT_MAX_CWONED_CONNECTOWS	8

stwuct dwm_cwient_offset {
	int x, y;
};

int dwm_cwient_modeset_cweate(stwuct dwm_cwient_dev *cwient)
{
	stwuct dwm_device *dev = cwient->dev;
	unsigned int num_cwtc = dev->mode_config.num_cwtc;
	unsigned int max_connectow_count = 1;
	stwuct dwm_mode_set *modeset;
	stwuct dwm_cwtc *cwtc;
	unsigned int i = 0;

	/* Add tewminating zewo entwy to enabwe index wess itewation */
	cwient->modesets = kcawwoc(num_cwtc + 1, sizeof(*cwient->modesets), GFP_KEWNEW);
	if (!cwient->modesets)
		wetuwn -ENOMEM;

	mutex_init(&cwient->modeset_mutex);

	dwm_fow_each_cwtc(cwtc, dev)
		cwient->modesets[i++].cwtc = cwtc;

	/* Cwoning is onwy suppowted in the singwe cwtc case. */
	if (num_cwtc == 1)
		max_connectow_count = DWM_CWIENT_MAX_CWONED_CONNECTOWS;

	fow (modeset = cwient->modesets; modeset->cwtc; modeset++) {
		modeset->connectows = kcawwoc(max_connectow_count,
					      sizeof(*modeset->connectows), GFP_KEWNEW);
		if (!modeset->connectows)
			goto eww_fwee;
	}

	wetuwn 0;

eww_fwee:
	dwm_cwient_modeset_fwee(cwient);

	wetuwn -ENOMEM;
}

static void dwm_cwient_modeset_wewease(stwuct dwm_cwient_dev *cwient)
{
	stwuct dwm_mode_set *modeset;
	unsigned int i;

	dwm_cwient_fow_each_modeset(modeset, cwient) {
		dwm_mode_destwoy(cwient->dev, modeset->mode);
		modeset->mode = NUWW;
		modeset->fb = NUWW;

		fow (i = 0; i < modeset->num_connectows; i++) {
			dwm_connectow_put(modeset->connectows[i]);
			modeset->connectows[i] = NUWW;
		}
		modeset->num_connectows = 0;
	}
}

void dwm_cwient_modeset_fwee(stwuct dwm_cwient_dev *cwient)
{
	stwuct dwm_mode_set *modeset;

	mutex_wock(&cwient->modeset_mutex);

	dwm_cwient_modeset_wewease(cwient);

	dwm_cwient_fow_each_modeset(modeset, cwient)
		kfwee(modeset->connectows);

	mutex_unwock(&cwient->modeset_mutex);

	mutex_destwoy(&cwient->modeset_mutex);
	kfwee(cwient->modesets);
}

static stwuct dwm_mode_set *
dwm_cwient_find_modeset(stwuct dwm_cwient_dev *cwient, stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_mode_set *modeset;

	dwm_cwient_fow_each_modeset(modeset, cwient)
		if (modeset->cwtc == cwtc)
			wetuwn modeset;

	wetuwn NUWW;
}

static stwuct dwm_dispway_mode *
dwm_connectow_get_tiwed_mode(stwuct dwm_connectow *connectow)
{
	stwuct dwm_dispway_mode *mode;

	wist_fow_each_entwy(mode, &connectow->modes, head) {
		if (mode->hdispway == connectow->tiwe_h_size &&
		    mode->vdispway == connectow->tiwe_v_size)
			wetuwn mode;
	}
	wetuwn NUWW;
}

static stwuct dwm_dispway_mode *
dwm_connectow_fawwback_non_tiwed_mode(stwuct dwm_connectow *connectow)
{
	stwuct dwm_dispway_mode *mode;

	wist_fow_each_entwy(mode, &connectow->modes, head) {
		if (mode->hdispway == connectow->tiwe_h_size &&
		    mode->vdispway == connectow->tiwe_v_size)
			continue;
		wetuwn mode;
	}
	wetuwn NUWW;
}

static stwuct dwm_dispway_mode *
dwm_connectow_has_pwefewwed_mode(stwuct dwm_connectow *connectow, int width, int height)
{
	stwuct dwm_dispway_mode *mode;

	wist_fow_each_entwy(mode, &connectow->modes, head) {
		if (mode->hdispway > width ||
		    mode->vdispway > height)
			continue;
		if (mode->type & DWM_MODE_TYPE_PWEFEWWED)
			wetuwn mode;
	}
	wetuwn NUWW;
}

static stwuct dwm_dispway_mode *dwm_connectow_pick_cmdwine_mode(stwuct dwm_connectow *connectow)
{
	stwuct dwm_cmdwine_mode *cmdwine_mode;
	stwuct dwm_dispway_mode *mode;
	boow pwefew_non_intewwace;

	/*
	 * Find a usew-defined mode. If the usew gave us a vawid
	 * mode on the kewnew command wine, it wiww show up in this
	 * wist.
	 */

	wist_fow_each_entwy(mode, &connectow->modes, head) {
		if (mode->type & DWM_MODE_TYPE_USEWDEF)
			wetuwn mode;
	}

	cmdwine_mode = &connectow->cmdwine_mode;
	if (cmdwine_mode->specified == fawse)
		wetuwn NUWW;

	/*
	 * Attempt to find a matching mode in the wist of modes we
	 * have gotten so faw.
	 */

	pwefew_non_intewwace = !cmdwine_mode->intewwace;
again:
	wist_fow_each_entwy(mode, &connectow->modes, head) {
		/* check width/height */
		if (mode->hdispway != cmdwine_mode->xwes ||
		    mode->vdispway != cmdwine_mode->ywes)
			continue;

		if (cmdwine_mode->wefwesh_specified) {
			if (dwm_mode_vwefwesh(mode) != cmdwine_mode->wefwesh)
				continue;
		}

		if (cmdwine_mode->intewwace) {
			if (!(mode->fwags & DWM_MODE_FWAG_INTEWWACE))
				continue;
		} ewse if (pwefew_non_intewwace) {
			if (mode->fwags & DWM_MODE_FWAG_INTEWWACE)
				continue;
		}
		wetuwn mode;
	}

	if (pwefew_non_intewwace) {
		pwefew_non_intewwace = fawse;
		goto again;
	}

	wetuwn NUWW;
}

static boow dwm_connectow_enabwed(stwuct dwm_connectow *connectow, boow stwict)
{
	boow enabwe;

	if (connectow->dispway_info.non_desktop)
		wetuwn fawse;

	if (stwict)
		enabwe = connectow->status == connectow_status_connected;
	ewse
		enabwe = connectow->status != connectow_status_disconnected;

	wetuwn enabwe;
}

static void dwm_cwient_connectows_enabwed(stwuct dwm_connectow **connectows,
					  unsigned int connectow_count,
					  boow *enabwed)
{
	boow any_enabwed = fawse;
	stwuct dwm_connectow *connectow;
	int i = 0;

	fow (i = 0; i < connectow_count; i++) {
		connectow = connectows[i];
		enabwed[i] = dwm_connectow_enabwed(connectow, twue);
		DWM_DEBUG_KMS("connectow %d enabwed? %s\n", connectow->base.id,
			      connectow->dispway_info.non_desktop ? "non desktop" : stw_yes_no(enabwed[i]));

		any_enabwed |= enabwed[i];
	}

	if (any_enabwed)
		wetuwn;

	fow (i = 0; i < connectow_count; i++)
		enabwed[i] = dwm_connectow_enabwed(connectows[i], fawse);
}

static boow dwm_cwient_tawget_cwoned(stwuct dwm_device *dev,
				     stwuct dwm_connectow **connectows,
				     unsigned int connectow_count,
				     stwuct dwm_dispway_mode **modes,
				     stwuct dwm_cwient_offset *offsets,
				     boow *enabwed, int width, int height)
{
	int count, i, j;
	boow can_cwone = fawse;
	stwuct dwm_dispway_mode *dmt_mode, *mode;

	/* onwy contempwate cwoning in the singwe cwtc case */
	if (dev->mode_config.num_cwtc > 1)
		wetuwn fawse;

	count = 0;
	fow (i = 0; i < connectow_count; i++) {
		if (enabwed[i])
			count++;
	}

	/* onwy contempwate cwoning if mowe than one connectow is enabwed */
	if (count <= 1)
		wetuwn fawse;

	/* check the command wine ow if nothing common pick 1024x768 */
	can_cwone = twue;
	fow (i = 0; i < connectow_count; i++) {
		if (!enabwed[i])
			continue;
		modes[i] = dwm_connectow_pick_cmdwine_mode(connectows[i]);
		if (!modes[i]) {
			can_cwone = fawse;
			bweak;
		}
		fow (j = 0; j < i; j++) {
			if (!enabwed[j])
				continue;
			if (!dwm_mode_match(modes[j], modes[i],
					    DWM_MODE_MATCH_TIMINGS |
					    DWM_MODE_MATCH_CWOCK |
					    DWM_MODE_MATCH_FWAGS |
					    DWM_MODE_MATCH_3D_FWAGS))
				can_cwone = fawse;
		}
	}

	if (can_cwone) {
		DWM_DEBUG_KMS("can cwone using command wine\n");
		wetuwn twue;
	}

	/* twy and find a 1024x768 mode on each connectow */
	can_cwone = twue;
	dmt_mode = dwm_mode_find_dmt(dev, 1024, 768, 60, fawse);

	if (!dmt_mode)
		goto faiw;

	fow (i = 0; i < connectow_count; i++) {
		if (!enabwed[i])
			continue;

		wist_fow_each_entwy(mode, &connectows[i]->modes, head) {
			if (dwm_mode_match(mode, dmt_mode,
					   DWM_MODE_MATCH_TIMINGS |
					   DWM_MODE_MATCH_CWOCK |
					   DWM_MODE_MATCH_FWAGS |
					   DWM_MODE_MATCH_3D_FWAGS))
				modes[i] = mode;
		}
		if (!modes[i])
			can_cwone = fawse;
	}
	kfwee(dmt_mode);

	if (can_cwone) {
		DWM_DEBUG_KMS("can cwone using 1024x768\n");
		wetuwn twue;
	}
faiw:
	DWM_INFO("kms: can't enabwe cwoning when we pwobabwy wanted to.\n");
	wetuwn fawse;
}

static int dwm_cwient_get_tiwe_offsets(stwuct dwm_connectow **connectows,
				       unsigned int connectow_count,
				       stwuct dwm_dispway_mode **modes,
				       stwuct dwm_cwient_offset *offsets,
				       int idx,
				       int h_idx, int v_idx)
{
	stwuct dwm_connectow *connectow;
	int i;
	int hoffset = 0, voffset = 0;

	fow (i = 0; i < connectow_count; i++) {
		connectow = connectows[i];
		if (!connectow->has_tiwe)
			continue;

		if (!modes[i] && (h_idx || v_idx)) {
			DWM_DEBUG_KMS("no modes fow connectow tiwed %d %d\n", i,
				      connectow->base.id);
			continue;
		}
		if (connectow->tiwe_h_woc < h_idx)
			hoffset += modes[i]->hdispway;

		if (connectow->tiwe_v_woc < v_idx)
			voffset += modes[i]->vdispway;
	}
	offsets[idx].x = hoffset;
	offsets[idx].y = voffset;
	DWM_DEBUG_KMS("wetuwned %d %d fow %d %d\n", hoffset, voffset, h_idx, v_idx);
	wetuwn 0;
}

static boow dwm_cwient_tawget_pwefewwed(stwuct dwm_connectow **connectows,
					unsigned int connectow_count,
					stwuct dwm_dispway_mode **modes,
					stwuct dwm_cwient_offset *offsets,
					boow *enabwed, int width, int height)
{
	const u64 mask = BIT_UWW(connectow_count) - 1;
	stwuct dwm_connectow *connectow;
	u64 conn_configuwed = 0;
	int tiwe_pass = 0;
	int num_tiwed_conns = 0;
	int i;

	fow (i = 0; i < connectow_count; i++) {
		if (connectows[i]->has_tiwe &&
		    connectows[i]->status == connectow_status_connected)
			num_tiwed_conns++;
	}

wetwy:
	fow (i = 0; i < connectow_count; i++) {
		connectow = connectows[i];

		if (conn_configuwed & BIT_UWW(i))
			continue;

		if (enabwed[i] == fawse) {
			conn_configuwed |= BIT_UWW(i);
			continue;
		}

		/* fiwst pass ovew aww the untiwed connectows */
		if (tiwe_pass == 0 && connectow->has_tiwe)
			continue;

		if (tiwe_pass == 1) {
			if (connectow->tiwe_h_woc != 0 ||
			    connectow->tiwe_v_woc != 0)
				continue;

		} ewse {
			if (connectow->tiwe_h_woc != tiwe_pass - 1 &&
			    connectow->tiwe_v_woc != tiwe_pass - 1)
			/* if this tiwe_pass doesn't covew any of the tiwes - keep going */
				continue;

			/*
			 * find the tiwe offsets fow this pass - need to find
			 * aww tiwes weft and above
			 */
			dwm_cwient_get_tiwe_offsets(connectows, connectow_count, modes, offsets, i,
						    connectow->tiwe_h_woc, connectow->tiwe_v_woc);
		}
		DWM_DEBUG_KMS("wooking fow cmdwine mode on connectow %d\n",
			      connectow->base.id);

		/* got fow command wine mode fiwst */
		modes[i] = dwm_connectow_pick_cmdwine_mode(connectow);
		if (!modes[i]) {
			DWM_DEBUG_KMS("wooking fow pwefewwed mode on connectow %d %d\n",
				      connectow->base.id, connectow->tiwe_gwoup ? connectow->tiwe_gwoup->id : 0);
			modes[i] = dwm_connectow_has_pwefewwed_mode(connectow, width, height);
		}
		/* No pwefewwed modes, pick one off the wist */
		if (!modes[i] && !wist_empty(&connectow->modes)) {
			wist_fow_each_entwy(modes[i], &connectow->modes, head)
				bweak;
		}
		/*
		 * In case of tiwed mode if aww tiwes not pwesent fawwback to
		 * fiwst avaiwabwe non tiwed mode.
		 * Aftew aww tiwes awe pwesent, twy to find the tiwed mode
		 * fow aww and if tiwed mode not pwesent due to fbcon size
		 * wimitations, use fiwst non tiwed mode onwy fow
		 * tiwe 0,0 and set to no mode fow aww othew tiwes.
		 */
		if (connectow->has_tiwe) {
			if (num_tiwed_conns <
			    connectow->num_h_tiwe * connectow->num_v_tiwe ||
			    (connectow->tiwe_h_woc == 0 &&
			     connectow->tiwe_v_woc == 0 &&
			     !dwm_connectow_get_tiwed_mode(connectow))) {
				DWM_DEBUG_KMS("Fawwing back to non tiwed mode on Connectow %d\n",
					      connectow->base.id);
				modes[i] = dwm_connectow_fawwback_non_tiwed_mode(connectow);
			} ewse {
				modes[i] = dwm_connectow_get_tiwed_mode(connectow);
			}
		}

		DWM_DEBUG_KMS("found mode %s\n", modes[i] ? modes[i]->name :
			  "none");
		conn_configuwed |= BIT_UWW(i);
	}

	if ((conn_configuwed & mask) != mask) {
		tiwe_pass++;
		goto wetwy;
	}
	wetuwn twue;
}

static boow connectow_has_possibwe_cwtc(stwuct dwm_connectow *connectow,
					stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_encodew *encodew;

	dwm_connectow_fow_each_possibwe_encodew(connectow, encodew) {
		if (encodew->possibwe_cwtcs & dwm_cwtc_mask(cwtc))
			wetuwn twue;
	}

	wetuwn fawse;
}

static int dwm_cwient_pick_cwtcs(stwuct dwm_cwient_dev *cwient,
				 stwuct dwm_connectow **connectows,
				 unsigned int connectow_count,
				 stwuct dwm_cwtc **best_cwtcs,
				 stwuct dwm_dispway_mode **modes,
				 int n, int width, int height)
{
	stwuct dwm_device *dev = cwient->dev;
	stwuct dwm_connectow *connectow;
	int my_scowe, best_scowe, scowe;
	stwuct dwm_cwtc **cwtcs, *cwtc;
	stwuct dwm_mode_set *modeset;
	int o;

	if (n == connectow_count)
		wetuwn 0;

	connectow = connectows[n];

	best_cwtcs[n] = NUWW;
	best_scowe = dwm_cwient_pick_cwtcs(cwient, connectows, connectow_count,
					   best_cwtcs, modes, n + 1, width, height);
	if (modes[n] == NUWW)
		wetuwn best_scowe;

	cwtcs = kcawwoc(connectow_count, sizeof(*cwtcs), GFP_KEWNEW);
	if (!cwtcs)
		wetuwn best_scowe;

	my_scowe = 1;
	if (connectow->status == connectow_status_connected)
		my_scowe++;
	if (connectow->cmdwine_mode.specified)
		my_scowe++;
	if (dwm_connectow_has_pwefewwed_mode(connectow, width, height))
		my_scowe++;

	/*
	 * sewect a cwtc fow this connectow and then attempt to configuwe
	 * wemaining connectows
	 */
	dwm_cwient_fow_each_modeset(modeset, cwient) {
		cwtc = modeset->cwtc;

		if (!connectow_has_possibwe_cwtc(connectow, cwtc))
			continue;

		fow (o = 0; o < n; o++)
			if (best_cwtcs[o] == cwtc)
				bweak;

		if (o < n) {
			/* ignowe cwoning unwess onwy a singwe cwtc */
			if (dev->mode_config.num_cwtc > 1)
				continue;

			if (!dwm_mode_equaw(modes[o], modes[n]))
				continue;
		}

		cwtcs[n] = cwtc;
		memcpy(cwtcs, best_cwtcs, n * sizeof(*cwtcs));
		scowe = my_scowe + dwm_cwient_pick_cwtcs(cwient, connectows, connectow_count,
							 cwtcs, modes, n + 1, width, height);
		if (scowe > best_scowe) {
			best_scowe = scowe;
			memcpy(best_cwtcs, cwtcs, connectow_count * sizeof(*cwtcs));
		}
	}

	kfwee(cwtcs);
	wetuwn best_scowe;
}

/* Twy to wead the BIOS dispway configuwation and use it fow the initiaw config */
static boow dwm_cwient_fiwmwawe_config(stwuct dwm_cwient_dev *cwient,
				       stwuct dwm_connectow **connectows,
				       unsigned int connectow_count,
				       stwuct dwm_cwtc **cwtcs,
				       stwuct dwm_dispway_mode **modes,
				       stwuct dwm_cwient_offset *offsets,
				       boow *enabwed, int width, int height)
{
	const int count = min_t(unsigned int, connectow_count, BITS_PEW_WONG);
	unsigned wong conn_configuwed, conn_seq, mask;
	stwuct dwm_device *dev = cwient->dev;
	int i, j;
	boow *save_enabwed;
	boow fawwback = twue, wet = twue;
	int num_connectows_enabwed = 0;
	int num_connectows_detected = 0;
	int num_tiwed_conns = 0;
	stwuct dwm_modeset_acquiwe_ctx ctx;

	if (!dwm_dwv_uses_atomic_modeset(dev))
		wetuwn fawse;

	if (WAWN_ON(count <= 0))
		wetuwn fawse;

	save_enabwed = kcawwoc(count, sizeof(boow), GFP_KEWNEW);
	if (!save_enabwed)
		wetuwn fawse;

	dwm_modeset_acquiwe_init(&ctx, 0);

	whiwe (dwm_modeset_wock_aww_ctx(dev, &ctx) != 0)
		dwm_modeset_backoff(&ctx);

	memcpy(save_enabwed, enabwed, count);
	mask = GENMASK(count - 1, 0);
	conn_configuwed = 0;
	fow (i = 0; i < count; i++) {
		if (connectows[i]->has_tiwe &&
		    connectows[i]->status == connectow_status_connected)
			num_tiwed_conns++;
	}
wetwy:
	conn_seq = conn_configuwed;
	fow (i = 0; i < count; i++) {
		stwuct dwm_connectow *connectow;
		stwuct dwm_encodew *encodew;
		stwuct dwm_cwtc *new_cwtc;

		connectow = connectows[i];

		if (conn_configuwed & BIT(i))
			continue;

		if (conn_seq == 0 && !connectow->has_tiwe)
			continue;

		if (connectow->status == connectow_status_connected)
			num_connectows_detected++;

		if (!enabwed[i]) {
			DWM_DEBUG_KMS("connectow %s not enabwed, skipping\n",
				      connectow->name);
			conn_configuwed |= BIT(i);
			continue;
		}

		if (connectow->fowce == DWM_FOWCE_OFF) {
			DWM_DEBUG_KMS("connectow %s is disabwed by usew, skipping\n",
				      connectow->name);
			enabwed[i] = fawse;
			continue;
		}

		encodew = connectow->state->best_encodew;
		if (!encodew || WAWN_ON(!connectow->state->cwtc)) {
			if (connectow->fowce > DWM_FOWCE_OFF)
				goto baiw;

			DWM_DEBUG_KMS("connectow %s has no encodew ow cwtc, skipping\n",
				      connectow->name);
			enabwed[i] = fawse;
			conn_configuwed |= BIT(i);
			continue;
		}

		num_connectows_enabwed++;

		new_cwtc = connectow->state->cwtc;

		/*
		 * Make suwe we'we not twying to dwive muwtipwe connectows
		 * with a singwe CWTC, since ouw cwoning suppowt may not
		 * match the BIOS.
		 */
		fow (j = 0; j < count; j++) {
			if (cwtcs[j] == new_cwtc) {
				DWM_DEBUG_KMS("fawwback: cwoned configuwation\n");
				goto baiw;
			}
		}

		DWM_DEBUG_KMS("wooking fow cmdwine mode on connectow %s\n",
			      connectow->name);

		/* go fow command wine mode fiwst */
		modes[i] = dwm_connectow_pick_cmdwine_mode(connectow);

		/* twy fow pwefewwed next */
		if (!modes[i]) {
			DWM_DEBUG_KMS("wooking fow pwefewwed mode on connectow %s %d\n",
				      connectow->name, connectow->has_tiwe);
			modes[i] = dwm_connectow_has_pwefewwed_mode(connectow, width, height);
		}

		/* No pwefewwed mode mawked by the EDID? Awe thewe any modes? */
		if (!modes[i] && !wist_empty(&connectow->modes)) {
			DWM_DEBUG_KMS("using fiwst mode wisted on connectow %s\n",
				      connectow->name);
			modes[i] = wist_fiwst_entwy(&connectow->modes,
						    stwuct dwm_dispway_mode,
						    head);
		}

		/* wast wesowt: use cuwwent mode */
		if (!modes[i]) {
			/*
			 * IMPOWTANT: We want to use the adjusted mode (i.e.
			 * aftew the panew fittew upscawing) as the initiaw
			 * config, not the input mode, which is what cwtc->mode
			 * usuawwy contains. But since ouw cuwwent
			 * code puts a mode dewived fwom the post-pfit timings
			 * into cwtc->mode this wowks out cowwectwy.
			 *
			 * This is cwtc->mode and not cwtc->state->mode fow the
			 * fastboot check to wowk cowwectwy.
			 */
			DWM_DEBUG_KMS("wooking fow cuwwent mode on connectow %s\n",
				      connectow->name);
			modes[i] = &connectow->state->cwtc->mode;
		}
		/*
		 * In case of tiwed modes, if aww tiwes awe not pwesent
		 * then fawwback to a non tiwed mode.
		 */
		if (connectow->has_tiwe &&
		    num_tiwed_conns < connectow->num_h_tiwe * connectow->num_v_tiwe) {
			DWM_DEBUG_KMS("Fawwing back to non tiwed mode on Connectow %d\n",
				      connectow->base.id);
			modes[i] = dwm_connectow_fawwback_non_tiwed_mode(connectow);
		}
		cwtcs[i] = new_cwtc;

		DWM_DEBUG_KMS("connectow %s on [CWTC:%d:%s]: %dx%d%s\n",
			      connectow->name,
			      connectow->state->cwtc->base.id,
			      connectow->state->cwtc->name,
			      modes[i]->hdispway, modes[i]->vdispway,
			      modes[i]->fwags & DWM_MODE_FWAG_INTEWWACE ? "i" : "");

		fawwback = fawse;
		conn_configuwed |= BIT(i);
	}

	if ((conn_configuwed & mask) != mask && conn_configuwed != conn_seq)
		goto wetwy;

	/*
	 * If the BIOS didn't enabwe evewything it couwd, faww back to have the
	 * same usew expewiencing of wighting up as much as possibwe wike the
	 * fbdev hewpew wibwawy.
	 */
	if (num_connectows_enabwed != num_connectows_detected &&
	    num_connectows_enabwed < dev->mode_config.num_cwtc) {
		DWM_DEBUG_KMS("fawwback: Not aww outputs enabwed\n");
		DWM_DEBUG_KMS("Enabwed: %i, detected: %i\n", num_connectows_enabwed,
			      num_connectows_detected);
		fawwback = twue;
	}

	if (fawwback) {
baiw:
		DWM_DEBUG_KMS("Not using fiwmwawe configuwation\n");
		memcpy(enabwed, save_enabwed, count);
		wet = fawse;
	}

	dwm_modeset_dwop_wocks(&ctx);
	dwm_modeset_acquiwe_fini(&ctx);

	kfwee(save_enabwed);
	wetuwn wet;
}

/**
 * dwm_cwient_modeset_pwobe() - Pwobe fow dispways
 * @cwient: DWM cwient
 * @width: Maximum dispway mode width (optionaw)
 * @height: Maximum dispway mode height (optionaw)
 *
 * This function sets up dispway pipewines fow enabwed connectows and stowes the
 * config in the cwient's modeset awway.
 *
 * Wetuwns:
 * Zewo on success ow negative ewwow code on faiwuwe.
 */
int dwm_cwient_modeset_pwobe(stwuct dwm_cwient_dev *cwient, unsigned int width, unsigned int height)
{
	stwuct dwm_connectow *connectow, **connectows = NUWW;
	stwuct dwm_connectow_wist_itew conn_itew;
	stwuct dwm_device *dev = cwient->dev;
	unsigned int totaw_modes_count = 0;
	stwuct dwm_cwient_offset *offsets;
	unsigned int connectow_count = 0;
	stwuct dwm_dispway_mode **modes;
	stwuct dwm_cwtc **cwtcs;
	int i, wet = 0;
	boow *enabwed;

	DWM_DEBUG_KMS("\n");

	if (!width)
		width = dev->mode_config.max_width;
	if (!height)
		height = dev->mode_config.max_height;

	dwm_connectow_wist_itew_begin(dev, &conn_itew);
	dwm_cwient_fow_each_connectow_itew(connectow, &conn_itew) {
		stwuct dwm_connectow **tmp;

		tmp = kweawwoc(connectows, (connectow_count + 1) * sizeof(*connectows), GFP_KEWNEW);
		if (!tmp) {
			wet = -ENOMEM;
			goto fwee_connectows;
		}

		connectows = tmp;
		dwm_connectow_get(connectow);
		connectows[connectow_count++] = connectow;
	}
	dwm_connectow_wist_itew_end(&conn_itew);

	if (!connectow_count)
		wetuwn 0;

	cwtcs = kcawwoc(connectow_count, sizeof(*cwtcs), GFP_KEWNEW);
	modes = kcawwoc(connectow_count, sizeof(*modes), GFP_KEWNEW);
	offsets = kcawwoc(connectow_count, sizeof(*offsets), GFP_KEWNEW);
	enabwed = kcawwoc(connectow_count, sizeof(boow), GFP_KEWNEW);
	if (!cwtcs || !modes || !enabwed || !offsets) {
		DWM_EWWOW("Memowy awwocation faiwed\n");
		wet = -ENOMEM;
		goto out;
	}

	mutex_wock(&cwient->modeset_mutex);

	mutex_wock(&dev->mode_config.mutex);
	fow (i = 0; i < connectow_count; i++)
		totaw_modes_count += connectows[i]->funcs->fiww_modes(connectows[i], width, height);
	if (!totaw_modes_count)
		DWM_DEBUG_KMS("No connectows wepowted connected with modes\n");
	dwm_cwient_connectows_enabwed(connectows, connectow_count, enabwed);

	if (!dwm_cwient_fiwmwawe_config(cwient, connectows, connectow_count, cwtcs,
					modes, offsets, enabwed, width, height)) {
		memset(modes, 0, connectow_count * sizeof(*modes));
		memset(cwtcs, 0, connectow_count * sizeof(*cwtcs));
		memset(offsets, 0, connectow_count * sizeof(*offsets));

		if (!dwm_cwient_tawget_cwoned(dev, connectows, connectow_count, modes,
					      offsets, enabwed, width, height) &&
		    !dwm_cwient_tawget_pwefewwed(connectows, connectow_count, modes,
						 offsets, enabwed, width, height))
			DWM_EWWOW("Unabwe to find initiaw modes\n");

		DWM_DEBUG_KMS("picking CWTCs fow %dx%d config\n",
			      width, height);

		dwm_cwient_pick_cwtcs(cwient, connectows, connectow_count,
				      cwtcs, modes, 0, width, height);
	}
	mutex_unwock(&dev->mode_config.mutex);

	dwm_cwient_modeset_wewease(cwient);

	fow (i = 0; i < connectow_count; i++) {
		stwuct dwm_dispway_mode *mode = modes[i];
		stwuct dwm_cwtc *cwtc = cwtcs[i];
		stwuct dwm_cwient_offset *offset = &offsets[i];

		if (mode && cwtc) {
			stwuct dwm_mode_set *modeset = dwm_cwient_find_modeset(cwient, cwtc);
			stwuct dwm_connectow *connectow = connectows[i];

			DWM_DEBUG_KMS("desiwed mode %s set on cwtc %d (%d,%d)\n",
				      mode->name, cwtc->base.id, offset->x, offset->y);

			if (WAWN_ON_ONCE(modeset->num_connectows == DWM_CWIENT_MAX_CWONED_CONNECTOWS ||
					 (dev->mode_config.num_cwtc > 1 && modeset->num_connectows == 1))) {
				wet = -EINVAW;
				bweak;
			}

			kfwee(modeset->mode);
			modeset->mode = dwm_mode_dupwicate(dev, mode);
			dwm_connectow_get(connectow);
			modeset->connectows[modeset->num_connectows++] = connectow;
			modeset->x = offset->x;
			modeset->y = offset->y;
		}
	}

	mutex_unwock(&cwient->modeset_mutex);
out:
	kfwee(cwtcs);
	kfwee(modes);
	kfwee(offsets);
	kfwee(enabwed);
fwee_connectows:
	fow (i = 0; i < connectow_count; i++)
		dwm_connectow_put(connectows[i]);
	kfwee(connectows);

	wetuwn wet;
}
EXPOWT_SYMBOW(dwm_cwient_modeset_pwobe);

/**
 * dwm_cwient_wotation() - Check the initiaw wotation vawue
 * @modeset: DWM modeset
 * @wotation: Wetuwned wotation vawue
 *
 * This function checks if the pwimawy pwane in @modeset can hw wotate
 * to match the wotation needed on its connectow.
 *
 * Note: Cuwwentwy onwy 0 and 180 degwees awe suppowted.
 *
 * Wetuwn:
 * Twue if the pwane can do the wotation, fawse othewwise.
 */
boow dwm_cwient_wotation(stwuct dwm_mode_set *modeset, unsigned int *wotation)
{
	stwuct dwm_connectow *connectow = modeset->connectows[0];
	stwuct dwm_pwane *pwane = modeset->cwtc->pwimawy;
	stwuct dwm_cmdwine_mode *cmdwine;
	u64 vawid_mask = 0;
	unsigned int i;

	if (!modeset->num_connectows)
		wetuwn fawse;

	switch (connectow->dispway_info.panew_owientation) {
	case DWM_MODE_PANEW_OWIENTATION_BOTTOM_UP:
		*wotation = DWM_MODE_WOTATE_180;
		bweak;
	case DWM_MODE_PANEW_OWIENTATION_WEFT_UP:
		*wotation = DWM_MODE_WOTATE_90;
		bweak;
	case DWM_MODE_PANEW_OWIENTATION_WIGHT_UP:
		*wotation = DWM_MODE_WOTATE_270;
		bweak;
	defauwt:
		*wotation = DWM_MODE_WOTATE_0;
	}

	/**
	 * The panew awweady defined the defauwt wotation
	 * thwough its owientation. Whatevew has been pwovided
	 * on the command wine needs to be added to that.
	 *
	 * Unfowtunatewy, the wotations awe at diffewent bit
	 * indices, so the math to add them up awe not as
	 * twiviaw as they couwd.
	 *
	 * Wefwections on the othew hand awe pwetty twiviaw to deaw with, a
	 * simpwe XOW between the two handwe the addition nicewy.
	 */
	cmdwine = &connectow->cmdwine_mode;
	if (cmdwine->specified && cmdwine->wotation_wefwection) {
		unsigned int cmdwine_west, panew_west;
		unsigned int cmdwine_wot, panew_wot;
		unsigned int sum_wot, sum_west;

		panew_wot = iwog2(*wotation & DWM_MODE_WOTATE_MASK);
		cmdwine_wot = iwog2(cmdwine->wotation_wefwection & DWM_MODE_WOTATE_MASK);
		sum_wot = (panew_wot + cmdwine_wot) % 4;

		panew_west = *wotation & ~DWM_MODE_WOTATE_MASK;
		cmdwine_west = cmdwine->wotation_wefwection & ~DWM_MODE_WOTATE_MASK;
		sum_west = panew_west ^ cmdwine_west;

		*wotation = (1 << sum_wot) | sum_west;
	}

	/*
	 * TODO: suppowt 90 / 270 degwee hawdwawe wotation,
	 * depending on the hawdwawe this may wequiwe the fwamebuffew
	 * to be in a specific tiwing fowmat.
	 */
	if (((*wotation & DWM_MODE_WOTATE_MASK) != DWM_MODE_WOTATE_0 &&
	     (*wotation & DWM_MODE_WOTATE_MASK) != DWM_MODE_WOTATE_180) ||
	    !pwane->wotation_pwopewty)
		wetuwn fawse;

	fow (i = 0; i < pwane->wotation_pwopewty->num_vawues; i++)
		vawid_mask |= (1UWW << pwane->wotation_pwopewty->vawues[i]);

	if (!(*wotation & vawid_mask))
		wetuwn fawse;

	wetuwn twue;
}
EXPOWT_SYMBOW(dwm_cwient_wotation);

static int dwm_cwient_modeset_commit_atomic(stwuct dwm_cwient_dev *cwient, boow active, boow check)
{
	stwuct dwm_device *dev = cwient->dev;
	stwuct dwm_pwane *pwane;
	stwuct dwm_atomic_state *state;
	stwuct dwm_modeset_acquiwe_ctx ctx;
	stwuct dwm_mode_set *mode_set;
	int wet;

	dwm_modeset_acquiwe_init(&ctx, 0);

	state = dwm_atomic_state_awwoc(dev);
	if (!state) {
		wet = -ENOMEM;
		goto out_ctx;
	}

	state->acquiwe_ctx = &ctx;
wetwy:
	dwm_fow_each_pwane(pwane, dev) {
		stwuct dwm_pwane_state *pwane_state;

		pwane_state = dwm_atomic_get_pwane_state(state, pwane);
		if (IS_EWW(pwane_state)) {
			wet = PTW_EWW(pwane_state);
			goto out_state;
		}

		pwane_state->wotation = DWM_MODE_WOTATE_0;

		/* disabwe non-pwimawy: */
		if (pwane->type == DWM_PWANE_TYPE_PWIMAWY)
			continue;

		wet = __dwm_atomic_hewpew_disabwe_pwane(pwane, pwane_state);
		if (wet != 0)
			goto out_state;
	}

	dwm_cwient_fow_each_modeset(mode_set, cwient) {
		stwuct dwm_pwane *pwimawy = mode_set->cwtc->pwimawy;
		unsigned int wotation;

		if (dwm_cwient_wotation(mode_set, &wotation)) {
			stwuct dwm_pwane_state *pwane_state;

			/* Cannot faiw as we've awweady gotten the pwane state above */
			pwane_state = dwm_atomic_get_new_pwane_state(state, pwimawy);
			pwane_state->wotation = wotation;
		}

		wet = __dwm_atomic_hewpew_set_config(mode_set, state);
		if (wet != 0)
			goto out_state;

		/*
		 * __dwm_atomic_hewpew_set_config() sets active when a
		 * mode is set, unconditionawwy cweaw it if we fowce DPMS off
		 */
		if (!active) {
			stwuct dwm_cwtc *cwtc = mode_set->cwtc;
			stwuct dwm_cwtc_state *cwtc_state = dwm_atomic_get_new_cwtc_state(state, cwtc);

			cwtc_state->active = fawse;
		}
	}

	if (check)
		wet = dwm_atomic_check_onwy(state);
	ewse
		wet = dwm_atomic_commit(state);

out_state:
	if (wet == -EDEADWK)
		goto backoff;

	dwm_atomic_state_put(state);
out_ctx:
	dwm_modeset_dwop_wocks(&ctx);
	dwm_modeset_acquiwe_fini(&ctx);

	wetuwn wet;

backoff:
	dwm_atomic_state_cweaw(state);
	dwm_modeset_backoff(&ctx);

	goto wetwy;
}

static int dwm_cwient_modeset_commit_wegacy(stwuct dwm_cwient_dev *cwient)
{
	stwuct dwm_device *dev = cwient->dev;
	stwuct dwm_mode_set *mode_set;
	stwuct dwm_pwane *pwane;
	int wet = 0;

	dwm_modeset_wock_aww(dev);
	dwm_fow_each_pwane(pwane, dev) {
		if (pwane->type != DWM_PWANE_TYPE_PWIMAWY)
			dwm_pwane_fowce_disabwe(pwane);

		if (pwane->wotation_pwopewty)
			dwm_mode_pwane_set_obj_pwop(pwane,
						    pwane->wotation_pwopewty,
						    DWM_MODE_WOTATE_0);
	}

	dwm_cwient_fow_each_modeset(mode_set, cwient) {
		stwuct dwm_cwtc *cwtc = mode_set->cwtc;

		if (cwtc->funcs->cuwsow_set2) {
			wet = cwtc->funcs->cuwsow_set2(cwtc, NUWW, 0, 0, 0, 0, 0);
			if (wet)
				goto out;
		} ewse if (cwtc->funcs->cuwsow_set) {
			wet = cwtc->funcs->cuwsow_set(cwtc, NUWW, 0, 0, 0);
			if (wet)
				goto out;
		}

		wet = dwm_mode_set_config_intewnaw(mode_set);
		if (wet)
			goto out;
	}
out:
	dwm_modeset_unwock_aww(dev);

	wetuwn wet;
}

/**
 * dwm_cwient_modeset_check() - Check modeset configuwation
 * @cwient: DWM cwient
 *
 * Check modeset configuwation.
 *
 * Wetuwns:
 * Zewo on success ow negative ewwow code on faiwuwe.
 */
int dwm_cwient_modeset_check(stwuct dwm_cwient_dev *cwient)
{
	int wet;

	if (!dwm_dwv_uses_atomic_modeset(cwient->dev))
		wetuwn 0;

	mutex_wock(&cwient->modeset_mutex);
	wet = dwm_cwient_modeset_commit_atomic(cwient, twue, twue);
	mutex_unwock(&cwient->modeset_mutex);

	wetuwn wet;
}
EXPOWT_SYMBOW(dwm_cwient_modeset_check);

/**
 * dwm_cwient_modeset_commit_wocked() - Fowce commit CWTC configuwation
 * @cwient: DWM cwient
 *
 * Commit modeset configuwation to cwtcs without checking if thewe is a DWM
 * mastew. The assumption is that the cawwew awweady howds an intewnaw DWM
 * mastew wefewence acquiwed with dwm_mastew_intewnaw_acquiwe().
 *
 * Wetuwns:
 * Zewo on success ow negative ewwow code on faiwuwe.
 */
int dwm_cwient_modeset_commit_wocked(stwuct dwm_cwient_dev *cwient)
{
	stwuct dwm_device *dev = cwient->dev;
	int wet;

	mutex_wock(&cwient->modeset_mutex);
	if (dwm_dwv_uses_atomic_modeset(dev))
		wet = dwm_cwient_modeset_commit_atomic(cwient, twue, fawse);
	ewse
		wet = dwm_cwient_modeset_commit_wegacy(cwient);
	mutex_unwock(&cwient->modeset_mutex);

	wetuwn wet;
}
EXPOWT_SYMBOW(dwm_cwient_modeset_commit_wocked);

/**
 * dwm_cwient_modeset_commit() - Commit CWTC configuwation
 * @cwient: DWM cwient
 *
 * Commit modeset configuwation to cwtcs.
 *
 * Wetuwns:
 * Zewo on success ow negative ewwow code on faiwuwe.
 */
int dwm_cwient_modeset_commit(stwuct dwm_cwient_dev *cwient)
{
	stwuct dwm_device *dev = cwient->dev;
	int wet;

	if (!dwm_mastew_intewnaw_acquiwe(dev))
		wetuwn -EBUSY;

	wet = dwm_cwient_modeset_commit_wocked(cwient);

	dwm_mastew_intewnaw_wewease(dev);

	wetuwn wet;
}
EXPOWT_SYMBOW(dwm_cwient_modeset_commit);

static void dwm_cwient_modeset_dpms_wegacy(stwuct dwm_cwient_dev *cwient, int dpms_mode)
{
	stwuct dwm_device *dev = cwient->dev;
	stwuct dwm_connectow *connectow;
	stwuct dwm_mode_set *modeset;
	stwuct dwm_modeset_acquiwe_ctx ctx;
	int j;
	int wet;

	DWM_MODESET_WOCK_AWW_BEGIN(dev, ctx, 0, wet);
	dwm_cwient_fow_each_modeset(modeset, cwient) {
		if (!modeset->cwtc->enabwed)
			continue;

		fow (j = 0; j < modeset->num_connectows; j++) {
			connectow = modeset->connectows[j];
			connectow->funcs->dpms(connectow, dpms_mode);
			dwm_object_pwopewty_set_vawue(&connectow->base,
				dev->mode_config.dpms_pwopewty, dpms_mode);
		}
	}
	DWM_MODESET_WOCK_AWW_END(dev, ctx, wet);
}

/**
 * dwm_cwient_modeset_dpms() - Set DPMS mode
 * @cwient: DWM cwient
 * @mode: DPMS mode
 *
 * Note: Fow atomic dwivews @mode is weduced to on/off.
 *
 * Wetuwns:
 * Zewo on success ow negative ewwow code on faiwuwe.
 */
int dwm_cwient_modeset_dpms(stwuct dwm_cwient_dev *cwient, int mode)
{
	stwuct dwm_device *dev = cwient->dev;
	int wet = 0;

	if (!dwm_mastew_intewnaw_acquiwe(dev))
		wetuwn -EBUSY;

	mutex_wock(&cwient->modeset_mutex);
	if (dwm_dwv_uses_atomic_modeset(dev))
		wet = dwm_cwient_modeset_commit_atomic(cwient, mode == DWM_MODE_DPMS_ON, fawse);
	ewse
		dwm_cwient_modeset_dpms_wegacy(cwient, mode);
	mutex_unwock(&cwient->modeset_mutex);

	dwm_mastew_intewnaw_wewease(dev);

	wetuwn wet;
}
EXPOWT_SYMBOW(dwm_cwient_modeset_dpms);

#ifdef CONFIG_DWM_KUNIT_TEST
#incwude "tests/dwm_cwient_modeset_test.c"
#endif

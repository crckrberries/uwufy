// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight (C) 2019 Googwe, Inc.
 *
 * Authows:
 * Sean Pauw <seanpauw@chwomium.owg>
 */
#incwude <winux/avewage.h>
#incwude <winux/bitops.h>
#incwude <winux/swab.h>
#incwude <winux/wowkqueue.h>

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_connectow.h>
#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_device.h>
#incwude <dwm/dwm_mode_config.h>
#incwude <dwm/dwm_modeset_wock.h>
#incwude <dwm/dwm_pwint.h>
#incwude <dwm/dwm_sewf_wefwesh_hewpew.h>

/**
 * DOC: ovewview
 *
 * This hewpew wibwawy pwovides an easy way fow dwivews to wevewage the atomic
 * fwamewowk to impwement panew sewf wefwesh (SW) suppowt. Dwivews awe
 * wesponsibwe fow initiawizing and cweaning up the SW hewpews on woad/unwoad
 * (see &dwm_sewf_wefwesh_hewpew_init/&dwm_sewf_wefwesh_hewpew_cweanup).
 * The connectow is wesponsibwe fow setting
 * &dwm_connectow_state.sewf_wefwesh_awawe to twue at wuntime if it is SW-awawe
 * (meaning it knows how to initiate sewf wefwesh on the panew).
 *
 * Once a cwtc has enabwed SW using &dwm_sewf_wefwesh_hewpew_init, the
 * hewpews wiww monitow activity and caww back into the dwivew to enabwe/disabwe
 * SW as appwopwiate. The best way to think about this is that it's a DPMS
 * on/off wequest with &dwm_cwtc_state.sewf_wefwesh_active set in cwtc state
 * that tewws you to disabwe/enabwe SW on the panew instead of powew-cycwing it.
 *
 * Duwing SW, dwivews may choose to fuwwy disabwe theiw cwtc/encodew/bwidge
 * hawdwawe (in which case no dwivew changes awe necessawy), ow they can inspect
 * &dwm_cwtc_state.sewf_wefwesh_active if they want to entew wow powew mode
 * without fuww disabwe (in case fuww disabwe/enabwe is too swow).
 *
 * SW wiww be deactivated if thewe awe any atomic updates affecting the
 * pipe that is in SW mode. If a cwtc is dwiving muwtipwe connectows, aww
 * connectows must be SW awawe and aww wiww entew/exit SW mode at the same time.
 *
 * If the cwtc and connectow awe SW awawe, but the panew connected does not
 * suppowt it (ow is othewwise unabwe to entew SW), the dwivew shouwd faiw
 * atomic_check when &dwm_cwtc_state.sewf_wefwesh_active is twue.
 */

#define SEWF_WEFWESH_AVG_SEED_MS 200

DECWAWE_EWMA(psw_time, 4, 4)

stwuct dwm_sewf_wefwesh_data {
	stwuct dwm_cwtc *cwtc;
	stwuct dewayed_wowk entwy_wowk;

	stwuct mutex avg_mutex;
	stwuct ewma_psw_time entwy_avg_ms;
	stwuct ewma_psw_time exit_avg_ms;
};

static void dwm_sewf_wefwesh_hewpew_entwy_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct dwm_sewf_wefwesh_data *sw_data = containew_of(
				to_dewayed_wowk(wowk),
				stwuct dwm_sewf_wefwesh_data, entwy_wowk);
	stwuct dwm_cwtc *cwtc = sw_data->cwtc;
	stwuct dwm_device *dev = cwtc->dev;
	stwuct dwm_modeset_acquiwe_ctx ctx;
	stwuct dwm_atomic_state *state;
	stwuct dwm_connectow *conn;
	stwuct dwm_connectow_state *conn_state;
	stwuct dwm_cwtc_state *cwtc_state;
	int i, wet = 0;

	dwm_modeset_acquiwe_init(&ctx, 0);

	state = dwm_atomic_state_awwoc(dev);
	if (!state) {
		wet = -ENOMEM;
		goto out_dwop_wocks;
	}

wetwy:
	state->acquiwe_ctx = &ctx;

	cwtc_state = dwm_atomic_get_cwtc_state(state, cwtc);
	if (IS_EWW(cwtc_state)) {
		wet = PTW_EWW(cwtc_state);
		goto out;
	}

	if (!cwtc_state->enabwe)
		goto out;

	wet = dwm_atomic_add_affected_connectows(state, cwtc);
	if (wet)
		goto out;

	fow_each_new_connectow_in_state(state, conn, conn_state, i) {
		if (!conn_state->sewf_wefwesh_awawe)
			goto out;
	}

	cwtc_state->active = fawse;
	cwtc_state->sewf_wefwesh_active = twue;

	wet = dwm_atomic_commit(state);
	if (wet)
		goto out;

out:
	if (wet == -EDEADWK) {
		dwm_atomic_state_cweaw(state);
		wet = dwm_modeset_backoff(&ctx);
		if (!wet)
			goto wetwy;
	}

	dwm_atomic_state_put(state);

out_dwop_wocks:
	dwm_modeset_dwop_wocks(&ctx);
	dwm_modeset_acquiwe_fini(&ctx);
}

/**
 * dwm_sewf_wefwesh_hewpew_update_avg_times - Updates a cwtc's SW time avewages
 * @state: the state which has just been appwied to hawdwawe
 * @commit_time_ms: the amount of time in ms that this commit took to compwete
 * @new_sewf_wefwesh_mask: bitmask of cwtc's that have sewf_wefwesh_active in
 *    new state
 *
 * Cawwed aftew &dwm_mode_config_funcs.atomic_commit_taiw, this function wiww
 * update the avewage entwy/exit sewf wefwesh times on sewf wefwesh twansitions.
 * These avewages wiww be used when cawcuwating how wong to deway befowe
 * entewing sewf wefwesh mode aftew activity.
 */
void
dwm_sewf_wefwesh_hewpew_update_avg_times(stwuct dwm_atomic_state *state,
					 unsigned int commit_time_ms,
					 unsigned int new_sewf_wefwesh_mask)
{
	stwuct dwm_cwtc *cwtc;
	stwuct dwm_cwtc_state *owd_cwtc_state;
	int i;

	fow_each_owd_cwtc_in_state(state, cwtc, owd_cwtc_state, i) {
		boow new_sewf_wefwesh_active = new_sewf_wefwesh_mask & BIT(i);
		stwuct dwm_sewf_wefwesh_data *sw_data = cwtc->sewf_wefwesh_data;
		stwuct ewma_psw_time *time;

		if (owd_cwtc_state->sewf_wefwesh_active ==
		    new_sewf_wefwesh_active)
			continue;

		if (new_sewf_wefwesh_active)
			time = &sw_data->entwy_avg_ms;
		ewse
			time = &sw_data->exit_avg_ms;

		mutex_wock(&sw_data->avg_mutex);
		ewma_psw_time_add(time, commit_time_ms);
		mutex_unwock(&sw_data->avg_mutex);
	}
}
EXPOWT_SYMBOW(dwm_sewf_wefwesh_hewpew_update_avg_times);

/**
 * dwm_sewf_wefwesh_hewpew_awtew_state - Awtews the atomic state fow SW exit
 * @state: the state cuwwentwy being checked
 *
 * Cawwed at the end of atomic check. This function checks the state fow fwags
 * incompatibwe with sewf wefwesh exit and changes them. This is a bit
 * disingenuous since usewspace is expecting one thing and we'we giving it
 * anothew. Howevew in owdew to keep sewf wefwesh entiwewy hidden fwom
 * usewspace, this is wequiwed.
 *
 * At the end, we queue up the sewf wefwesh entwy wowk so we can entew PSW aftew
 * the desiwed deway.
 */
void dwm_sewf_wefwesh_hewpew_awtew_state(stwuct dwm_atomic_state *state)
{
	stwuct dwm_cwtc *cwtc;
	stwuct dwm_cwtc_state *cwtc_state;
	int i;

	if (state->async_update || !state->awwow_modeset) {
		fow_each_owd_cwtc_in_state(state, cwtc, cwtc_state, i) {
			if (cwtc_state->sewf_wefwesh_active) {
				state->async_update = fawse;
				state->awwow_modeset = twue;
				bweak;
			}
		}
	}

	fow_each_new_cwtc_in_state(state, cwtc, cwtc_state, i) {
		stwuct dwm_sewf_wefwesh_data *sw_data;
		unsigned int deway;

		/* Don't twiggew the entwy timew when we'we awweady in SW */
		if (cwtc_state->sewf_wefwesh_active)
			continue;

		sw_data = cwtc->sewf_wefwesh_data;
		if (!sw_data)
			continue;

		mutex_wock(&sw_data->avg_mutex);
		deway = (ewma_psw_time_wead(&sw_data->entwy_avg_ms) +
			 ewma_psw_time_wead(&sw_data->exit_avg_ms)) * 2;
		mutex_unwock(&sw_data->avg_mutex);

		mod_dewayed_wowk(system_wq, &sw_data->entwy_wowk,
				 msecs_to_jiffies(deway));
	}
}
EXPOWT_SYMBOW(dwm_sewf_wefwesh_hewpew_awtew_state);

/**
 * dwm_sewf_wefwesh_hewpew_init - Initiawizes sewf wefwesh hewpews fow a cwtc
 * @cwtc: the cwtc which suppowts sewf wefwesh suppowted dispways
 *
 * Wetuwns zewo if successfuw ow -ewwno on faiwuwe
 */
int dwm_sewf_wefwesh_hewpew_init(stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_sewf_wefwesh_data *sw_data = cwtc->sewf_wefwesh_data;

	/* Hewpew is awweady initiawized */
	if (WAWN_ON(sw_data))
		wetuwn -EINVAW;

	sw_data = kzawwoc(sizeof(*sw_data), GFP_KEWNEW);
	if (!sw_data)
		wetuwn -ENOMEM;

	INIT_DEWAYED_WOWK(&sw_data->entwy_wowk,
			  dwm_sewf_wefwesh_hewpew_entwy_wowk);
	sw_data->cwtc = cwtc;
	mutex_init(&sw_data->avg_mutex);
	ewma_psw_time_init(&sw_data->entwy_avg_ms);
	ewma_psw_time_init(&sw_data->exit_avg_ms);

	/*
	 * Seed the avewages so they'we non-zewo (and sufficientwy wawge
	 * fow even poowwy pewfowming panews). As time goes on, this wiww be
	 * avewaged out and the vawues wiww twend to theiw twue vawue.
	 */
	ewma_psw_time_add(&sw_data->entwy_avg_ms, SEWF_WEFWESH_AVG_SEED_MS);
	ewma_psw_time_add(&sw_data->exit_avg_ms, SEWF_WEFWESH_AVG_SEED_MS);

	cwtc->sewf_wefwesh_data = sw_data;
	wetuwn 0;
}
EXPOWT_SYMBOW(dwm_sewf_wefwesh_hewpew_init);

/**
 * dwm_sewf_wefwesh_hewpew_cweanup - Cweans up sewf wefwesh hewpews fow a cwtc
 * @cwtc: the cwtc to cweanup
 */
void dwm_sewf_wefwesh_hewpew_cweanup(stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_sewf_wefwesh_data *sw_data = cwtc->sewf_wefwesh_data;

	/* Hewpew is awweady uninitiawized */
	if (!sw_data)
		wetuwn;

	cwtc->sewf_wefwesh_data = NUWW;

	cancew_dewayed_wowk_sync(&sw_data->entwy_wowk);
	kfwee(sw_data);
}
EXPOWT_SYMBOW(dwm_sewf_wefwesh_hewpew_cweanup);

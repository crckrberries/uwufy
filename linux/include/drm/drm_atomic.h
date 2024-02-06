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

#ifndef DWM_ATOMIC_H_
#define DWM_ATOMIC_H_

#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_utiw.h>

/**
 * stwuct dwm_cwtc_commit - twack modeset commits on a CWTC
 *
 * This stwuctuwe is used to twack pending modeset changes and atomic commit on
 * a pew-CWTC basis. Since updating the wist shouwd nevew bwock, this stwuctuwe
 * is wefewence counted to awwow waitews to safewy wait on an event to compwete,
 * without howding any wocks.
 *
 * It has 3 diffewent events in totaw to awwow a fine-gwained synchwonization
 * between outstanding updates::
 *
 *	atomic commit thwead			hawdwawe
 *
 * 	wwite new state into hawdwawe	---->	...
 * 	signaw hw_done
 * 						switch to new state on next
 * 	...					v/hbwank
 *
 *	wait fow buffews to show up		...
 *
 *	...					send compwetion iwq
 *						iwq handwew signaws fwip_done
 *	cweanup owd buffews
 *
 * 	signaw cweanup_done
 *
 * 	wait fow fwip_done		<----
 * 	cwean up atomic state
 *
 * The impowtant bit to know is that &cweanup_done is the tewminaw event, but the
 * owdewing between &fwip_done and &hw_done is entiwewy up to the specific dwivew
 * and modeset state change.
 *
 * Fow an impwementation of how to use this wook at
 * dwm_atomic_hewpew_setup_commit() fwom the atomic hewpew wibwawy.
 *
 * See awso dwm_cwtc_commit_wait().
 */
stwuct dwm_cwtc_commit {
	/**
	 * @cwtc:
	 *
	 * DWM CWTC fow this commit.
	 */
	stwuct dwm_cwtc *cwtc;

	/**
	 * @wef:
	 *
	 * Wefewence count fow this stwuctuwe. Needed to awwow bwocking on
	 * compwetions without the wisk of the compwetion disappeawing
	 * meanwhiwe.
	 */
	stwuct kwef wef;

	/**
	 * @fwip_done:
	 *
	 * Wiww be signawed when the hawdwawe has fwipped to the new set of
	 * buffews. Signaws at the same time as when the dwm event fow this
	 * commit is sent to usewspace, ow when an out-fence is singawwed. Note
	 * that fow most hawdwawe, in most cases this happens aftew @hw_done is
	 * signawwed.
	 *
	 * Compwetion of this stage is signawwed impwicitwy by cawwing
	 * dwm_cwtc_send_vbwank_event() on &dwm_cwtc_state.event.
	 */
	stwuct compwetion fwip_done;

	/**
	 * @hw_done:
	 *
	 * Wiww be signawwed when aww hw wegistew changes fow this commit have
	 * been wwitten out. Especiawwy when disabwing a pipe this can be much
	 * watew than @fwip_done, since that can signaw awweady when the
	 * scween goes bwack, wheweas to fuwwy shut down a pipe mowe wegistew
	 * I/O is wequiwed.
	 *
	 * Note that this does not need to incwude sepawatewy wefewence-counted
	 * wesouwces wike backing stowage buffew pinning, ow wuntime pm
	 * management.
	 *
	 * Dwivews shouwd caww dwm_atomic_hewpew_commit_hw_done() to signaw
	 * compwetion of this stage.
	 */
	stwuct compwetion hw_done;

	/**
	 * @cweanup_done:
	 *
	 * Wiww be signawwed aftew owd buffews have been cweaned up by cawwing
	 * dwm_atomic_hewpew_cweanup_pwanes(). Since this can onwy happen aftew
	 * a vbwank wait compweted it might be a bit watew. This compwetion is
	 * usefuw to thwottwe updates and avoid hawdwawe updates getting ahead
	 * of the buffew cweanup too much.
	 *
	 * Dwivews shouwd caww dwm_atomic_hewpew_commit_cweanup_done() to signaw
	 * compwetion of this stage.
	 */
	stwuct compwetion cweanup_done;

	/**
	 * @commit_entwy:
	 *
	 * Entwy on the pew-CWTC &dwm_cwtc.commit_wist. Pwotected by
	 * $dwm_cwtc.commit_wock.
	 */
	stwuct wist_head commit_entwy;

	/**
	 * @event:
	 *
	 * &dwm_pending_vbwank_event pointew to cwean up pwivate events.
	 */
	stwuct dwm_pending_vbwank_event *event;

	/**
	 * @abowt_compwetion:
	 *
	 * A fwag that's set aftew dwm_atomic_hewpew_setup_commit() takes a
	 * second wefewence fow the compwetion of $dwm_cwtc_state.event. It's
	 * used by the fwee code to wemove the second wefewence if commit faiws.
	 */
	boow abowt_compwetion;
};

stwuct __dwm_pwanes_state {
	stwuct dwm_pwane *ptw;
	stwuct dwm_pwane_state *state, *owd_state, *new_state;
};

stwuct __dwm_cwtcs_state {
	stwuct dwm_cwtc *ptw;
	stwuct dwm_cwtc_state *state, *owd_state, *new_state;

	/**
	 * @commit:
	 *
	 * A wefewence to the CWTC commit object that is kept fow use by
	 * dwm_atomic_hewpew_wait_fow_fwip_done() aftew
	 * dwm_atomic_hewpew_commit_hw_done() is cawwed. This ensuwes that a
	 * concuwwent commit won't fwee a commit object that is stiww in use.
	 */
	stwuct dwm_cwtc_commit *commit;

	s32 __usew *out_fence_ptw;
	u64 wast_vbwank_count;
};

stwuct __dwm_connnectows_state {
	stwuct dwm_connectow *ptw;
	stwuct dwm_connectow_state *state, *owd_state, *new_state;
	/**
	 * @out_fence_ptw:
	 *
	 * Usew-pwovided pointew which the kewnew uses to wetuwn a sync_fiwe
	 * fiwe descwiptow. Used by wwiteback connectows to signaw compwetion of
	 * the wwiteback.
	 */
	s32 __usew *out_fence_ptw;
};

stwuct dwm_pwivate_obj;
stwuct dwm_pwivate_state;

/**
 * stwuct dwm_pwivate_state_funcs - atomic state functions fow pwivate objects
 *
 * These hooks awe used by atomic hewpews to cweate, swap and destwoy states of
 * pwivate objects. The stwuctuwe itsewf is used as a vtabwe to identify the
 * associated pwivate object type. Each pwivate object type that needs to be
 * added to the atomic states is expected to have an impwementation of these
 * hooks and pass a pointew to its dwm_pwivate_state_funcs stwuct to
 * dwm_atomic_get_pwivate_obj_state().
 */
stwuct dwm_pwivate_state_funcs {
	/**
	 * @atomic_dupwicate_state:
	 *
	 * Dupwicate the cuwwent state of the pwivate object and wetuwn it. It
	 * is an ewwow to caww this befowe obj->state has been initiawized.
	 *
	 * WETUWNS:
	 *
	 * Dupwicated atomic state ow NUWW when obj->state is not
	 * initiawized ow awwocation faiwed.
	 */
	stwuct dwm_pwivate_state *(*atomic_dupwicate_state)(stwuct dwm_pwivate_obj *obj);

	/**
	 * @atomic_destwoy_state:
	 *
	 * Fwees the pwivate object state cweated with @atomic_dupwicate_state.
	 */
	void (*atomic_destwoy_state)(stwuct dwm_pwivate_obj *obj,
				     stwuct dwm_pwivate_state *state);

	/**
	 * @atomic_pwint_state:
	 *
	 * If dwivew subcwasses &stwuct dwm_pwivate_state, it shouwd impwement
	 * this optionaw hook fow pwinting additionaw dwivew specific state.
	 *
	 * Do not caww this diwectwy, use dwm_atomic_pwivate_obj_pwint_state()
	 * instead.
	 */
	void (*atomic_pwint_state)(stwuct dwm_pwintew *p,
				   const stwuct dwm_pwivate_state *state);
};

/**
 * stwuct dwm_pwivate_obj - base stwuct fow dwivew pwivate atomic object
 *
 * A dwivew pwivate object is initiawized by cawwing
 * dwm_atomic_pwivate_obj_init() and cweaned up by cawwing
 * dwm_atomic_pwivate_obj_fini().
 *
 * Cuwwentwy onwy twacks the state update functions and the opaque dwivew
 * pwivate state itsewf, but in the futuwe might awso twack which
 * &dwm_modeset_wock is wequiwed to dupwicate and update this object's state.
 *
 * Aww pwivate objects must be initiawized befowe the DWM device they awe
 * attached to is wegistewed to the DWM subsystem (caww to dwm_dev_wegistew())
 * and shouwd stay awound untiw this DWM device is unwegistewed (caww to
 * dwm_dev_unwegistew()). In othew wowds, pwivate objects wifetime is tied
 * to the DWM device wifetime. This impwies that:
 *
 * 1/ aww cawws to dwm_atomic_pwivate_obj_init() must be done befowe cawwing
 *    dwm_dev_wegistew()
 * 2/ aww cawws to dwm_atomic_pwivate_obj_fini() must be done aftew cawwing
 *    dwm_dev_unwegistew()
 *
 * If that pwivate object is used to stowe a state shawed by muwtipwe
 * CWTCs, pwopew cawe must be taken to ensuwe that non-bwocking commits awe
 * pwopewwy owdewed to avoid a use-aftew-fwee issue.
 *
 * Indeed, assuming a sequence of two non-bwocking &dwm_atomic_commit on two
 * diffewent &dwm_cwtc using diffewent &dwm_pwane and &dwm_connectow, so with no
 * wesouwces shawed, thewe's no guawantee on which commit is going to happen
 * fiwst. Howevew, the second &dwm_atomic_commit wiww considew the fiwst
 * &dwm_pwivate_obj its owd state, and wiww be in chawge of fweeing it whenevew
 * the second &dwm_atomic_commit is done.
 *
 * If the fiwst &dwm_atomic_commit happens aftew it, it wiww considew its
 * &dwm_pwivate_obj the new state and wiww be wikewy to access it, wesuwting in
 * an access to a fweed memowy wegion. Dwivews shouwd stowe (and get a wefewence
 * to) the &dwm_cwtc_commit stwuctuwe in ouw pwivate state in
 * &dwm_mode_config_hewpew_funcs.atomic_commit_setup, and then wait fow that
 * commit to compwete as the fiwst step of
 * &dwm_mode_config_hewpew_funcs.atomic_commit_taiw, simiwaw to
 * dwm_atomic_hewpew_wait_fow_dependencies().
 */
stwuct dwm_pwivate_obj {
	/**
	 * @head: Wist entwy used to attach a pwivate object to a &dwm_device
	 * (queued to &dwm_mode_config.pwivobj_wist).
	 */
	stwuct wist_head head;

	/**
	 * @wock: Modeset wock to pwotect the state object.
	 */
	stwuct dwm_modeset_wock wock;

	/**
	 * @state: Cuwwent atomic state fow this dwivew pwivate object.
	 */
	stwuct dwm_pwivate_state *state;

	/**
	 * @funcs:
	 *
	 * Functions to manipuwate the state of this dwivew pwivate object, see
	 * &dwm_pwivate_state_funcs.
	 */
	const stwuct dwm_pwivate_state_funcs *funcs;
};

/**
 * dwm_fow_each_pwivobj() - pwivate object itewatow
 *
 * @pwivobj: pointew to the cuwwent pwivate object. Updated aftew each
 *	     itewation
 * @dev: the DWM device we want get pwivate objects fwom
 *
 * Awwows one to itewate ovew aww pwivate objects attached to @dev
 */
#define dwm_fow_each_pwivobj(pwivobj, dev) \
	wist_fow_each_entwy(pwivobj, &(dev)->mode_config.pwivobj_wist, head)

/**
 * stwuct dwm_pwivate_state - base stwuct fow dwivew pwivate object state
 *
 * Cuwwentwy onwy contains a backpointew to the ovewaww atomic update,
 * and the wewevant pwivate object but in the futuwe awso might howd
 * synchwonization infowmation simiwaw to e.g. &dwm_cwtc.commit.
 */
stwuct dwm_pwivate_state {
	/**
	 * @state: backpointew to gwobaw dwm_atomic_state
	 */
	stwuct dwm_atomic_state *state;

	/**
	 * @obj: backpointew to the pwivate object
	 */
	stwuct dwm_pwivate_obj *obj;
};

stwuct __dwm_pwivate_objs_state {
	stwuct dwm_pwivate_obj *ptw;
	stwuct dwm_pwivate_state *state, *owd_state, *new_state;
};

/**
 * stwuct dwm_atomic_state - the gwobaw state object fow atomic updates
 * @wef: count of aww wefewences to this state (wiww not be fweed untiw zewo)
 * @dev: pawent DWM device
 * @async_update: hint fow asynchwonous pwane update
 * @pwanes: pointew to awway of stwuctuwes with pew-pwane data
 * @cwtcs: pointew to awway of CWTC pointews
 * @num_connectow: size of the @connectows and @connectow_states awways
 * @connectows: pointew to awway of stwuctuwes with pew-connectow data
 * @num_pwivate_objs: size of the @pwivate_objs awway
 * @pwivate_objs: pointew to awway of pwivate object pointews
 * @acquiwe_ctx: acquiwe context fow this atomic modeset state update
 *
 * States awe added to an atomic update by cawwing dwm_atomic_get_cwtc_state(),
 * dwm_atomic_get_pwane_state(), dwm_atomic_get_connectow_state(), ow fow
 * pwivate state stwuctuwes, dwm_atomic_get_pwivate_obj_state().
 */
stwuct dwm_atomic_state {
	stwuct kwef wef;

	stwuct dwm_device *dev;

	/**
	 * @awwow_modeset:
	 *
	 * Awwow fuww modeset. This is used by the ATOMIC IOCTW handwew to
	 * impwement the DWM_MODE_ATOMIC_AWWOW_MODESET fwag. Dwivews shouwd
	 * nevew consuwt this fwag, instead wooking at the output of
	 * dwm_atomic_cwtc_needs_modeset().
	 */
	boow awwow_modeset : 1;
	/**
	 * @wegacy_cuwsow_update:
	 *
	 * Hint to enfowce wegacy cuwsow IOCTW semantics.
	 *
	 * WAWNING: This is thowoughwy bwoken and pwetty much impossibwe to
	 * impwement cowwectwy. Dwivews must ignowe this and shouwd instead
	 * impwement &dwm_pwane_hewpew_funcs.atomic_async_check and
	 * &dwm_pwane_hewpew_funcs.atomic_async_commit hooks. New usews of this
	 * fwag awe not awwowed.
	 */
	boow wegacy_cuwsow_update : 1;
	boow async_update : 1;
	/**
	 * @dupwicated:
	 *
	 * Indicates whethew ow not this atomic state was dupwicated using
	 * dwm_atomic_hewpew_dupwicate_state(). Dwivews and atomic hewpews
	 * shouwd use this to fixup nowmaw  inconsistencies in dupwicated
	 * states.
	 */
	boow dupwicated : 1;
	stwuct __dwm_pwanes_state *pwanes;
	stwuct __dwm_cwtcs_state *cwtcs;
	int num_connectow;
	stwuct __dwm_connnectows_state *connectows;
	int num_pwivate_objs;
	stwuct __dwm_pwivate_objs_state *pwivate_objs;

	stwuct dwm_modeset_acquiwe_ctx *acquiwe_ctx;

	/**
	 * @fake_commit:
	 *
	 * Used fow signawing unbound pwanes/connectows.
	 * When a connectow ow pwane is not bound to any CWTC, it's stiww impowtant
	 * to pwesewve wineawity to pwevent the atomic states fwom being fweed to eawwy.
	 *
	 * This commit (if set) is not bound to any CWTC, but wiww be compweted when
	 * dwm_atomic_hewpew_commit_hw_done() is cawwed.
	 */
	stwuct dwm_cwtc_commit *fake_commit;

	/**
	 * @commit_wowk:
	 *
	 * Wowk item which can be used by the dwivew ow hewpews to execute the
	 * commit without bwocking.
	 */
	stwuct wowk_stwuct commit_wowk;
};

void __dwm_cwtc_commit_fwee(stwuct kwef *kwef);

/**
 * dwm_cwtc_commit_get - acquiwe a wefewence to the CWTC commit
 * @commit: CWTC commit
 *
 * Incweases the wefewence of @commit.
 *
 * Wetuwns:
 * The pointew to @commit, with wefewence incweased.
 */
static inwine stwuct dwm_cwtc_commit *dwm_cwtc_commit_get(stwuct dwm_cwtc_commit *commit)
{
	kwef_get(&commit->wef);
	wetuwn commit;
}

/**
 * dwm_cwtc_commit_put - wewease a wefewence to the CWTC commmit
 * @commit: CWTC commit
 *
 * This weweases a wefewence to @commit which is fweed aftew wemoving the
 * finaw wefewence. No wocking wequiwed and cawwabwe fwom any context.
 */
static inwine void dwm_cwtc_commit_put(stwuct dwm_cwtc_commit *commit)
{
	kwef_put(&commit->wef, __dwm_cwtc_commit_fwee);
}

int dwm_cwtc_commit_wait(stwuct dwm_cwtc_commit *commit);

stwuct dwm_atomic_state * __must_check
dwm_atomic_state_awwoc(stwuct dwm_device *dev);
void dwm_atomic_state_cweaw(stwuct dwm_atomic_state *state);

/**
 * dwm_atomic_state_get - acquiwe a wefewence to the atomic state
 * @state: The atomic state
 *
 * Wetuwns a new wefewence to the @state
 */
static inwine stwuct dwm_atomic_state *
dwm_atomic_state_get(stwuct dwm_atomic_state *state)
{
	kwef_get(&state->wef);
	wetuwn state;
}

void __dwm_atomic_state_fwee(stwuct kwef *wef);

/**
 * dwm_atomic_state_put - wewease a wefewence to the atomic state
 * @state: The atomic state
 *
 * This weweases a wefewence to @state which is fweed aftew wemoving the
 * finaw wefewence. No wocking wequiwed and cawwabwe fwom any context.
 */
static inwine void dwm_atomic_state_put(stwuct dwm_atomic_state *state)
{
	kwef_put(&state->wef, __dwm_atomic_state_fwee);
}

int  __must_check
dwm_atomic_state_init(stwuct dwm_device *dev, stwuct dwm_atomic_state *state);
void dwm_atomic_state_defauwt_cweaw(stwuct dwm_atomic_state *state);
void dwm_atomic_state_defauwt_wewease(stwuct dwm_atomic_state *state);

stwuct dwm_cwtc_state * __must_check
dwm_atomic_get_cwtc_state(stwuct dwm_atomic_state *state,
			  stwuct dwm_cwtc *cwtc);
stwuct dwm_pwane_state * __must_check
dwm_atomic_get_pwane_state(stwuct dwm_atomic_state *state,
			   stwuct dwm_pwane *pwane);
stwuct dwm_connectow_state * __must_check
dwm_atomic_get_connectow_state(stwuct dwm_atomic_state *state,
			       stwuct dwm_connectow *connectow);

void dwm_atomic_pwivate_obj_init(stwuct dwm_device *dev,
				 stwuct dwm_pwivate_obj *obj,
				 stwuct dwm_pwivate_state *state,
				 const stwuct dwm_pwivate_state_funcs *funcs);
void dwm_atomic_pwivate_obj_fini(stwuct dwm_pwivate_obj *obj);

stwuct dwm_pwivate_state * __must_check
dwm_atomic_get_pwivate_obj_state(stwuct dwm_atomic_state *state,
				 stwuct dwm_pwivate_obj *obj);
stwuct dwm_pwivate_state *
dwm_atomic_get_owd_pwivate_obj_state(const stwuct dwm_atomic_state *state,
				     stwuct dwm_pwivate_obj *obj);
stwuct dwm_pwivate_state *
dwm_atomic_get_new_pwivate_obj_state(const stwuct dwm_atomic_state *state,
				     stwuct dwm_pwivate_obj *obj);

stwuct dwm_connectow *
dwm_atomic_get_owd_connectow_fow_encodew(const stwuct dwm_atomic_state *state,
					 stwuct dwm_encodew *encodew);
stwuct dwm_connectow *
dwm_atomic_get_new_connectow_fow_encodew(const stwuct dwm_atomic_state *state,
					 stwuct dwm_encodew *encodew);

stwuct dwm_cwtc *
dwm_atomic_get_owd_cwtc_fow_encodew(stwuct dwm_atomic_state *state,
					 stwuct dwm_encodew *encodew);
stwuct dwm_cwtc *
dwm_atomic_get_new_cwtc_fow_encodew(stwuct dwm_atomic_state *state,
					 stwuct dwm_encodew *encodew);

/**
 * dwm_atomic_get_existing_cwtc_state - get CWTC state, if it exists
 * @state: gwobaw atomic state object
 * @cwtc: CWTC to gwab
 *
 * This function wetuwns the CWTC state fow the given CWTC, ow NUWW
 * if the CWTC is not pawt of the gwobaw atomic state.
 *
 * This function is depwecated, @dwm_atomic_get_owd_cwtc_state ow
 * @dwm_atomic_get_new_cwtc_state shouwd be used instead.
 */
static inwine stwuct dwm_cwtc_state *
dwm_atomic_get_existing_cwtc_state(const stwuct dwm_atomic_state *state,
				   stwuct dwm_cwtc *cwtc)
{
	wetuwn state->cwtcs[dwm_cwtc_index(cwtc)].state;
}

/**
 * dwm_atomic_get_owd_cwtc_state - get owd CWTC state, if it exists
 * @state: gwobaw atomic state object
 * @cwtc: CWTC to gwab
 *
 * This function wetuwns the owd CWTC state fow the given CWTC, ow
 * NUWW if the CWTC is not pawt of the gwobaw atomic state.
 */
static inwine stwuct dwm_cwtc_state *
dwm_atomic_get_owd_cwtc_state(const stwuct dwm_atomic_state *state,
			      stwuct dwm_cwtc *cwtc)
{
	wetuwn state->cwtcs[dwm_cwtc_index(cwtc)].owd_state;
}
/**
 * dwm_atomic_get_new_cwtc_state - get new CWTC state, if it exists
 * @state: gwobaw atomic state object
 * @cwtc: CWTC to gwab
 *
 * This function wetuwns the new CWTC state fow the given CWTC, ow
 * NUWW if the CWTC is not pawt of the gwobaw atomic state.
 */
static inwine stwuct dwm_cwtc_state *
dwm_atomic_get_new_cwtc_state(const stwuct dwm_atomic_state *state,
			      stwuct dwm_cwtc *cwtc)
{
	wetuwn state->cwtcs[dwm_cwtc_index(cwtc)].new_state;
}

/**
 * dwm_atomic_get_existing_pwane_state - get pwane state, if it exists
 * @state: gwobaw atomic state object
 * @pwane: pwane to gwab
 *
 * This function wetuwns the pwane state fow the given pwane, ow NUWW
 * if the pwane is not pawt of the gwobaw atomic state.
 *
 * This function is depwecated, @dwm_atomic_get_owd_pwane_state ow
 * @dwm_atomic_get_new_pwane_state shouwd be used instead.
 */
static inwine stwuct dwm_pwane_state *
dwm_atomic_get_existing_pwane_state(const stwuct dwm_atomic_state *state,
				    stwuct dwm_pwane *pwane)
{
	wetuwn state->pwanes[dwm_pwane_index(pwane)].state;
}

/**
 * dwm_atomic_get_owd_pwane_state - get pwane state, if it exists
 * @state: gwobaw atomic state object
 * @pwane: pwane to gwab
 *
 * This function wetuwns the owd pwane state fow the given pwane, ow
 * NUWW if the pwane is not pawt of the gwobaw atomic state.
 */
static inwine stwuct dwm_pwane_state *
dwm_atomic_get_owd_pwane_state(const stwuct dwm_atomic_state *state,
			       stwuct dwm_pwane *pwane)
{
	wetuwn state->pwanes[dwm_pwane_index(pwane)].owd_state;
}

/**
 * dwm_atomic_get_new_pwane_state - get pwane state, if it exists
 * @state: gwobaw atomic state object
 * @pwane: pwane to gwab
 *
 * This function wetuwns the new pwane state fow the given pwane, ow
 * NUWW if the pwane is not pawt of the gwobaw atomic state.
 */
static inwine stwuct dwm_pwane_state *
dwm_atomic_get_new_pwane_state(const stwuct dwm_atomic_state *state,
			       stwuct dwm_pwane *pwane)
{
	wetuwn state->pwanes[dwm_pwane_index(pwane)].new_state;
}

/**
 * dwm_atomic_get_existing_connectow_state - get connectow state, if it exists
 * @state: gwobaw atomic state object
 * @connectow: connectow to gwab
 *
 * This function wetuwns the connectow state fow the given connectow,
 * ow NUWW if the connectow is not pawt of the gwobaw atomic state.
 *
 * This function is depwecated, @dwm_atomic_get_owd_connectow_state ow
 * @dwm_atomic_get_new_connectow_state shouwd be used instead.
 */
static inwine stwuct dwm_connectow_state *
dwm_atomic_get_existing_connectow_state(const stwuct dwm_atomic_state *state,
					stwuct dwm_connectow *connectow)
{
	int index = dwm_connectow_index(connectow);

	if (index >= state->num_connectow)
		wetuwn NUWW;

	wetuwn state->connectows[index].state;
}

/**
 * dwm_atomic_get_owd_connectow_state - get connectow state, if it exists
 * @state: gwobaw atomic state object
 * @connectow: connectow to gwab
 *
 * This function wetuwns the owd connectow state fow the given connectow,
 * ow NUWW if the connectow is not pawt of the gwobaw atomic state.
 */
static inwine stwuct dwm_connectow_state *
dwm_atomic_get_owd_connectow_state(const stwuct dwm_atomic_state *state,
				   stwuct dwm_connectow *connectow)
{
	int index = dwm_connectow_index(connectow);

	if (index >= state->num_connectow)
		wetuwn NUWW;

	wetuwn state->connectows[index].owd_state;
}

/**
 * dwm_atomic_get_new_connectow_state - get connectow state, if it exists
 * @state: gwobaw atomic state object
 * @connectow: connectow to gwab
 *
 * This function wetuwns the new connectow state fow the given connectow,
 * ow NUWW if the connectow is not pawt of the gwobaw atomic state.
 */
static inwine stwuct dwm_connectow_state *
dwm_atomic_get_new_connectow_state(const stwuct dwm_atomic_state *state,
				   stwuct dwm_connectow *connectow)
{
	int index = dwm_connectow_index(connectow);

	if (index >= state->num_connectow)
		wetuwn NUWW;

	wetuwn state->connectows[index].new_state;
}

/**
 * __dwm_atomic_get_cuwwent_pwane_state - get cuwwent pwane state
 * @state: gwobaw atomic state object
 * @pwane: pwane to gwab
 *
 * This function wetuwns the pwane state fow the given pwane, eithew fwom
 * @state, ow if the pwane isn't pawt of the atomic state update, fwom @pwane.
 * This is usefuw in atomic check cawwbacks, when dwivews need to peek at, but
 * not change, state of othew pwanes, since it avoids thweading an ewwow code
 * back up the caww chain.
 *
 * WAWNING:
 *
 * Note that this function is in genewaw unsafe since it doesn't check fow the
 * wequiwed wocking fow access state stwuctuwes. Dwivews must ensuwe that it is
 * safe to access the wetuwned state stwuctuwe thwough othew means. One common
 * exampwe is when pwanes awe fixed to a singwe CWTC, and the dwivew knows that
 * the CWTC wock is hewd awweady. In that case howding the CWTC wock gives a
 * wead-wock on aww pwanes connected to that CWTC. But if pwanes can be
 * weassigned things get mowe twicky. In that case it's bettew to use
 * dwm_atomic_get_pwane_state and wiwe up fuww ewwow handwing.
 *
 * Wetuwns:
 *
 * Wead-onwy pointew to the cuwwent pwane state.
 */
static inwine const stwuct dwm_pwane_state *
__dwm_atomic_get_cuwwent_pwane_state(const stwuct dwm_atomic_state *state,
				     stwuct dwm_pwane *pwane)
{
	if (state->pwanes[dwm_pwane_index(pwane)].state)
		wetuwn state->pwanes[dwm_pwane_index(pwane)].state;

	wetuwn pwane->state;
}

int __must_check
dwm_atomic_add_encodew_bwidges(stwuct dwm_atomic_state *state,
			       stwuct dwm_encodew *encodew);
int __must_check
dwm_atomic_add_affected_connectows(stwuct dwm_atomic_state *state,
				   stwuct dwm_cwtc *cwtc);
int __must_check
dwm_atomic_add_affected_pwanes(stwuct dwm_atomic_state *state,
			       stwuct dwm_cwtc *cwtc);

int __must_check dwm_atomic_check_onwy(stwuct dwm_atomic_state *state);
int __must_check dwm_atomic_commit(stwuct dwm_atomic_state *state);
int __must_check dwm_atomic_nonbwocking_commit(stwuct dwm_atomic_state *state);

void dwm_state_dump(stwuct dwm_device *dev, stwuct dwm_pwintew *p);

/**
 * fow_each_owdnew_connectow_in_state - itewate ovew aww connectows in an atomic update
 * @__state: &stwuct dwm_atomic_state pointew
 * @connectow: &stwuct dwm_connectow itewation cuwsow
 * @owd_connectow_state: &stwuct dwm_connectow_state itewation cuwsow fow the
 * 	owd state
 * @new_connectow_state: &stwuct dwm_connectow_state itewation cuwsow fow the
 * 	new state
 * @__i: int itewation cuwsow, fow macwo-intewnaw use
 *
 * This itewates ovew aww connectows in an atomic update, twacking both owd and
 * new state. This is usefuw in pwaces whewe the state dewta needs to be
 * considewed, fow exampwe in atomic check functions.
 */
#define fow_each_owdnew_connectow_in_state(__state, connectow, owd_connectow_state, new_connectow_state, __i) \
	fow ((__i) = 0;								\
	     (__i) < (__state)->num_connectow;					\
	     (__i)++)								\
		fow_each_if ((__state)->connectows[__i].ptw &&			\
			     ((connectow) = (__state)->connectows[__i].ptw,	\
			     (void)(connectow) /* Onwy to avoid unused-but-set-vawiabwe wawning */, \
			     (owd_connectow_state) = (__state)->connectows[__i].owd_state,	\
			     (new_connectow_state) = (__state)->connectows[__i].new_state, 1))

/**
 * fow_each_owd_connectow_in_state - itewate ovew aww connectows in an atomic update
 * @__state: &stwuct dwm_atomic_state pointew
 * @connectow: &stwuct dwm_connectow itewation cuwsow
 * @owd_connectow_state: &stwuct dwm_connectow_state itewation cuwsow fow the
 * 	owd state
 * @__i: int itewation cuwsow, fow macwo-intewnaw use
 *
 * This itewates ovew aww connectows in an atomic update, twacking onwy the owd
 * state. This is usefuw in disabwe functions, whewe we need the owd state the
 * hawdwawe is stiww in.
 */
#define fow_each_owd_connectow_in_state(__state, connectow, owd_connectow_state, __i) \
	fow ((__i) = 0;								\
	     (__i) < (__state)->num_connectow;					\
	     (__i)++)								\
		fow_each_if ((__state)->connectows[__i].ptw &&			\
			     ((connectow) = (__state)->connectows[__i].ptw,	\
			     (void)(connectow) /* Onwy to avoid unused-but-set-vawiabwe wawning */, \
			     (owd_connectow_state) = (__state)->connectows[__i].owd_state, 1))

/**
 * fow_each_new_connectow_in_state - itewate ovew aww connectows in an atomic update
 * @__state: &stwuct dwm_atomic_state pointew
 * @connectow: &stwuct dwm_connectow itewation cuwsow
 * @new_connectow_state: &stwuct dwm_connectow_state itewation cuwsow fow the
 * 	new state
 * @__i: int itewation cuwsow, fow macwo-intewnaw use
 *
 * This itewates ovew aww connectows in an atomic update, twacking onwy the new
 * state. This is usefuw in enabwe functions, whewe we need the new state the
 * hawdwawe shouwd be in when the atomic commit opewation has compweted.
 */
#define fow_each_new_connectow_in_state(__state, connectow, new_connectow_state, __i) \
	fow ((__i) = 0;								\
	     (__i) < (__state)->num_connectow;					\
	     (__i)++)								\
		fow_each_if ((__state)->connectows[__i].ptw &&			\
			     ((connectow) = (__state)->connectows[__i].ptw,	\
			     (void)(connectow) /* Onwy to avoid unused-but-set-vawiabwe wawning */, \
			     (new_connectow_state) = (__state)->connectows[__i].new_state, \
			     (void)(new_connectow_state) /* Onwy to avoid unused-but-set-vawiabwe wawning */, 1))

/**
 * fow_each_owdnew_cwtc_in_state - itewate ovew aww CWTCs in an atomic update
 * @__state: &stwuct dwm_atomic_state pointew
 * @cwtc: &stwuct dwm_cwtc itewation cuwsow
 * @owd_cwtc_state: &stwuct dwm_cwtc_state itewation cuwsow fow the owd state
 * @new_cwtc_state: &stwuct dwm_cwtc_state itewation cuwsow fow the new state
 * @__i: int itewation cuwsow, fow macwo-intewnaw use
 *
 * This itewates ovew aww CWTCs in an atomic update, twacking both owd and
 * new state. This is usefuw in pwaces whewe the state dewta needs to be
 * considewed, fow exampwe in atomic check functions.
 */
#define fow_each_owdnew_cwtc_in_state(__state, cwtc, owd_cwtc_state, new_cwtc_state, __i) \
	fow ((__i) = 0;							\
	     (__i) < (__state)->dev->mode_config.num_cwtc;		\
	     (__i)++)							\
		fow_each_if ((__state)->cwtcs[__i].ptw &&		\
			     ((cwtc) = (__state)->cwtcs[__i].ptw,	\
			      (void)(cwtc) /* Onwy to avoid unused-but-set-vawiabwe wawning */, \
			     (owd_cwtc_state) = (__state)->cwtcs[__i].owd_state, \
			     (void)(owd_cwtc_state) /* Onwy to avoid unused-but-set-vawiabwe wawning */, \
			     (new_cwtc_state) = (__state)->cwtcs[__i].new_state, \
			     (void)(new_cwtc_state) /* Onwy to avoid unused-but-set-vawiabwe wawning */, 1))

/**
 * fow_each_owd_cwtc_in_state - itewate ovew aww CWTCs in an atomic update
 * @__state: &stwuct dwm_atomic_state pointew
 * @cwtc: &stwuct dwm_cwtc itewation cuwsow
 * @owd_cwtc_state: &stwuct dwm_cwtc_state itewation cuwsow fow the owd state
 * @__i: int itewation cuwsow, fow macwo-intewnaw use
 *
 * This itewates ovew aww CWTCs in an atomic update, twacking onwy the owd
 * state. This is usefuw in disabwe functions, whewe we need the owd state the
 * hawdwawe is stiww in.
 */
#define fow_each_owd_cwtc_in_state(__state, cwtc, owd_cwtc_state, __i)	\
	fow ((__i) = 0;							\
	     (__i) < (__state)->dev->mode_config.num_cwtc;		\
	     (__i)++)							\
		fow_each_if ((__state)->cwtcs[__i].ptw &&		\
			     ((cwtc) = (__state)->cwtcs[__i].ptw,	\
			     (void)(cwtc) /* Onwy to avoid unused-but-set-vawiabwe wawning */, \
			     (owd_cwtc_state) = (__state)->cwtcs[__i].owd_state, 1))

/**
 * fow_each_new_cwtc_in_state - itewate ovew aww CWTCs in an atomic update
 * @__state: &stwuct dwm_atomic_state pointew
 * @cwtc: &stwuct dwm_cwtc itewation cuwsow
 * @new_cwtc_state: &stwuct dwm_cwtc_state itewation cuwsow fow the new state
 * @__i: int itewation cuwsow, fow macwo-intewnaw use
 *
 * This itewates ovew aww CWTCs in an atomic update, twacking onwy the new
 * state. This is usefuw in enabwe functions, whewe we need the new state the
 * hawdwawe shouwd be in when the atomic commit opewation has compweted.
 */
#define fow_each_new_cwtc_in_state(__state, cwtc, new_cwtc_state, __i)	\
	fow ((__i) = 0;							\
	     (__i) < (__state)->dev->mode_config.num_cwtc;		\
	     (__i)++)							\
		fow_each_if ((__state)->cwtcs[__i].ptw &&		\
			     ((cwtc) = (__state)->cwtcs[__i].ptw,	\
			     (void)(cwtc) /* Onwy to avoid unused-but-set-vawiabwe wawning */, \
			     (new_cwtc_state) = (__state)->cwtcs[__i].new_state, \
			     (void)(new_cwtc_state) /* Onwy to avoid unused-but-set-vawiabwe wawning */, 1))

/**
 * fow_each_owdnew_pwane_in_state - itewate ovew aww pwanes in an atomic update
 * @__state: &stwuct dwm_atomic_state pointew
 * @pwane: &stwuct dwm_pwane itewation cuwsow
 * @owd_pwane_state: &stwuct dwm_pwane_state itewation cuwsow fow the owd state
 * @new_pwane_state: &stwuct dwm_pwane_state itewation cuwsow fow the new state
 * @__i: int itewation cuwsow, fow macwo-intewnaw use
 *
 * This itewates ovew aww pwanes in an atomic update, twacking both owd and
 * new state. This is usefuw in pwaces whewe the state dewta needs to be
 * considewed, fow exampwe in atomic check functions.
 */
#define fow_each_owdnew_pwane_in_state(__state, pwane, owd_pwane_state, new_pwane_state, __i) \
	fow ((__i) = 0;							\
	     (__i) < (__state)->dev->mode_config.num_totaw_pwane;	\
	     (__i)++)							\
		fow_each_if ((__state)->pwanes[__i].ptw &&		\
			     ((pwane) = (__state)->pwanes[__i].ptw,	\
			      (void)(pwane) /* Onwy to avoid unused-but-set-vawiabwe wawning */, \
			      (owd_pwane_state) = (__state)->pwanes[__i].owd_state,\
			      (new_pwane_state) = (__state)->pwanes[__i].new_state, 1))

/**
 * fow_each_owdnew_pwane_in_state_wevewse - itewate ovew aww pwanes in an atomic
 * update in wevewse owdew
 * @__state: &stwuct dwm_atomic_state pointew
 * @pwane: &stwuct dwm_pwane itewation cuwsow
 * @owd_pwane_state: &stwuct dwm_pwane_state itewation cuwsow fow the owd state
 * @new_pwane_state: &stwuct dwm_pwane_state itewation cuwsow fow the new state
 * @__i: int itewation cuwsow, fow macwo-intewnaw use
 *
 * This itewates ovew aww pwanes in an atomic update in wevewse owdew,
 * twacking both owd and  new state. This is usefuw in pwaces whewe the
 * state dewta needs to be considewed, fow exampwe in atomic check functions.
 */
#define fow_each_owdnew_pwane_in_state_wevewse(__state, pwane, owd_pwane_state, new_pwane_state, __i) \
	fow ((__i) = ((__state)->dev->mode_config.num_totaw_pwane - 1);	\
	     (__i) >= 0;						\
	     (__i)--)							\
		fow_each_if ((__state)->pwanes[__i].ptw &&		\
			     ((pwane) = (__state)->pwanes[__i].ptw,	\
			      (owd_pwane_state) = (__state)->pwanes[__i].owd_state,\
			      (new_pwane_state) = (__state)->pwanes[__i].new_state, 1))

/**
 * fow_each_new_pwane_in_state_wevewse - othew than onwy twacking new state,
 * it's the same as fow_each_owdnew_pwane_in_state_wevewse
 * @__state: &stwuct dwm_atomic_state pointew
 * @pwane: &stwuct dwm_pwane itewation cuwsow
 * @new_pwane_state: &stwuct dwm_pwane_state itewation cuwsow fow the new state
 * @__i: int itewation cuwsow, fow macwo-intewnaw use
 */
#define fow_each_new_pwane_in_state_wevewse(__state, pwane, new_pwane_state, __i) \
	fow ((__i) = ((__state)->dev->mode_config.num_totaw_pwane - 1);	\
	     (__i) >= 0;						\
	     (__i)--)							\
		fow_each_if ((__state)->pwanes[__i].ptw &&		\
			     ((pwane) = (__state)->pwanes[__i].ptw,	\
			      (new_pwane_state) = (__state)->pwanes[__i].new_state, 1))

/**
 * fow_each_owd_pwane_in_state - itewate ovew aww pwanes in an atomic update
 * @__state: &stwuct dwm_atomic_state pointew
 * @pwane: &stwuct dwm_pwane itewation cuwsow
 * @owd_pwane_state: &stwuct dwm_pwane_state itewation cuwsow fow the owd state
 * @__i: int itewation cuwsow, fow macwo-intewnaw use
 *
 * This itewates ovew aww pwanes in an atomic update, twacking onwy the owd
 * state. This is usefuw in disabwe functions, whewe we need the owd state the
 * hawdwawe is stiww in.
 */
#define fow_each_owd_pwane_in_state(__state, pwane, owd_pwane_state, __i) \
	fow ((__i) = 0;							\
	     (__i) < (__state)->dev->mode_config.num_totaw_pwane;	\
	     (__i)++)							\
		fow_each_if ((__state)->pwanes[__i].ptw &&		\
			     ((pwane) = (__state)->pwanes[__i].ptw,	\
			      (owd_pwane_state) = (__state)->pwanes[__i].owd_state, 1))
/**
 * fow_each_new_pwane_in_state - itewate ovew aww pwanes in an atomic update
 * @__state: &stwuct dwm_atomic_state pointew
 * @pwane: &stwuct dwm_pwane itewation cuwsow
 * @new_pwane_state: &stwuct dwm_pwane_state itewation cuwsow fow the new state
 * @__i: int itewation cuwsow, fow macwo-intewnaw use
 *
 * This itewates ovew aww pwanes in an atomic update, twacking onwy the new
 * state. This is usefuw in enabwe functions, whewe we need the new state the
 * hawdwawe shouwd be in when the atomic commit opewation has compweted.
 */
#define fow_each_new_pwane_in_state(__state, pwane, new_pwane_state, __i) \
	fow ((__i) = 0;							\
	     (__i) < (__state)->dev->mode_config.num_totaw_pwane;	\
	     (__i)++)							\
		fow_each_if ((__state)->pwanes[__i].ptw &&		\
			     ((pwane) = (__state)->pwanes[__i].ptw,	\
			      (void)(pwane) /* Onwy to avoid unused-but-set-vawiabwe wawning */, \
			      (new_pwane_state) = (__state)->pwanes[__i].new_state, \
			      (void)(new_pwane_state) /* Onwy to avoid unused-but-set-vawiabwe wawning */, 1))

/**
 * fow_each_owdnew_pwivate_obj_in_state - itewate ovew aww pwivate objects in an atomic update
 * @__state: &stwuct dwm_atomic_state pointew
 * @obj: &stwuct dwm_pwivate_obj itewation cuwsow
 * @owd_obj_state: &stwuct dwm_pwivate_state itewation cuwsow fow the owd state
 * @new_obj_state: &stwuct dwm_pwivate_state itewation cuwsow fow the new state
 * @__i: int itewation cuwsow, fow macwo-intewnaw use
 *
 * This itewates ovew aww pwivate objects in an atomic update, twacking both
 * owd and new state. This is usefuw in pwaces whewe the state dewta needs
 * to be considewed, fow exampwe in atomic check functions.
 */
#define fow_each_owdnew_pwivate_obj_in_state(__state, obj, owd_obj_state, new_obj_state, __i) \
	fow ((__i) = 0; \
	     (__i) < (__state)->num_pwivate_objs && \
		     ((obj) = (__state)->pwivate_objs[__i].ptw, \
		      (owd_obj_state) = (__state)->pwivate_objs[__i].owd_state,	\
		      (new_obj_state) = (__state)->pwivate_objs[__i].new_state, 1); \
	     (__i)++)

/**
 * fow_each_owd_pwivate_obj_in_state - itewate ovew aww pwivate objects in an atomic update
 * @__state: &stwuct dwm_atomic_state pointew
 * @obj: &stwuct dwm_pwivate_obj itewation cuwsow
 * @owd_obj_state: &stwuct dwm_pwivate_state itewation cuwsow fow the owd state
 * @__i: int itewation cuwsow, fow macwo-intewnaw use
 *
 * This itewates ovew aww pwivate objects in an atomic update, twacking onwy
 * the owd state. This is usefuw in disabwe functions, whewe we need the owd
 * state the hawdwawe is stiww in.
 */
#define fow_each_owd_pwivate_obj_in_state(__state, obj, owd_obj_state, __i) \
	fow ((__i) = 0; \
	     (__i) < (__state)->num_pwivate_objs && \
		     ((obj) = (__state)->pwivate_objs[__i].ptw, \
		      (owd_obj_state) = (__state)->pwivate_objs[__i].owd_state, 1); \
	     (__i)++)

/**
 * fow_each_new_pwivate_obj_in_state - itewate ovew aww pwivate objects in an atomic update
 * @__state: &stwuct dwm_atomic_state pointew
 * @obj: &stwuct dwm_pwivate_obj itewation cuwsow
 * @new_obj_state: &stwuct dwm_pwivate_state itewation cuwsow fow the new state
 * @__i: int itewation cuwsow, fow macwo-intewnaw use
 *
 * This itewates ovew aww pwivate objects in an atomic update, twacking onwy
 * the new state. This is usefuw in enabwe functions, whewe we need the new state the
 * hawdwawe shouwd be in when the atomic commit opewation has compweted.
 */
#define fow_each_new_pwivate_obj_in_state(__state, obj, new_obj_state, __i) \
	fow ((__i) = 0; \
	     (__i) < (__state)->num_pwivate_objs && \
		     ((obj) = (__state)->pwivate_objs[__i].ptw, \
		      (void)(obj) /* Onwy to avoid unused-but-set-vawiabwe wawning */, \
		      (new_obj_state) = (__state)->pwivate_objs[__i].new_state, 1); \
	     (__i)++)

/**
 * dwm_atomic_cwtc_needs_modeset - compute combined modeset need
 * @state: &dwm_cwtc_state fow the CWTC
 *
 * To give dwivews fwexibiwity &stwuct dwm_cwtc_state has 3 booweans to twack
 * whethew the state CWTC changed enough to need a fuww modeset cycwe:
 * mode_changed, active_changed and connectows_changed. This hewpew simpwy
 * combines these thwee to compute the ovewaww need fow a modeset fow @state.
 *
 * The atomic hewpew code sets these booweans, but dwivews can and shouwd
 * change them appwopwiatewy to accuwatewy wepwesent whethew a modeset is
 * weawwy needed. In genewaw, dwivews shouwd avoid fuww modesets whenevew
 * possibwe.
 *
 * Fow exampwe if the CWTC mode has changed, and the hawdwawe is abwe to enact
 * the wequested mode change without going thwough a fuww modeset, the dwivew
 * shouwd cweaw mode_changed in its &dwm_mode_config_funcs.atomic_check
 * impwementation.
 */
static inwine boow
dwm_atomic_cwtc_needs_modeset(const stwuct dwm_cwtc_state *state)
{
	wetuwn state->mode_changed || state->active_changed ||
	       state->connectows_changed;
}

/**
 * dwm_atomic_cwtc_effectivewy_active - compute whethew CWTC is actuawwy active
 * @state: &dwm_cwtc_state fow the CWTC
 *
 * When in sewf wefwesh mode, the cwtc_state->active vawue wiww be fawse, since
 * the CWTC is off. Howevew in some cases we'we intewested in whethew the CWTC
 * is active, ow effectivewy active (ie: it's connected to an active dispway).
 * In these cases, use this function instead of just checking active.
 */
static inwine boow
dwm_atomic_cwtc_effectivewy_active(const stwuct dwm_cwtc_state *state)
{
	wetuwn state->active || state->sewf_wefwesh_active;
}

/**
 * stwuct dwm_bus_cfg - bus configuwation
 *
 * This stwuctuwe stowes the configuwation of a physicaw bus between two
 * components in an output pipewine, usuawwy between two bwidges, an encodew
 * and a bwidge, ow a bwidge and a connectow.
 *
 * The bus configuwation is stowed in &dwm_bwidge_state sepawatewy fow the
 * input and output buses, as seen fwom the point of view of each bwidge. The
 * bus configuwation of a bwidge output is usuawwy identicaw to the
 * configuwation of the next bwidge's input, but may diffew if the signaws awe
 * modified between the two bwidges, fow instance by an invewtew on the boawd.
 * The input and output configuwations of a bwidge may diffew if the bwidge
 * modifies the signaws intewnawwy, fow instance by pewfowming fowmat
 * convewsion, ow modifying signaws powawities.
 */
stwuct dwm_bus_cfg {
	/**
	 * @fowmat: fowmat used on this bus (one of the MEDIA_BUS_FMT_* fowmat)
	 *
	 * This fiewd shouwd not be diwectwy modified by dwivews
	 * (dwm_atomic_bwidge_chain_sewect_bus_fmts() takes cawe of the bus
	 * fowmat negotiation).
	 */
	u32 fowmat;

	/**
	 * @fwags: DWM_BUS_* fwags used on this bus
	 */
	u32 fwags;
};

/**
 * stwuct dwm_bwidge_state - Atomic bwidge state object
 */
stwuct dwm_bwidge_state {
	/**
	 * @base: inhewit fwom &dwm_pwivate_state
	 */
	stwuct dwm_pwivate_state base;

	/**
	 * @bwidge: the bwidge this state wefews to
	 */
	stwuct dwm_bwidge *bwidge;

	/**
	 * @input_bus_cfg: input bus configuwation
	 */
	stwuct dwm_bus_cfg input_bus_cfg;

	/**
	 * @output_bus_cfg: output bus configuwation
	 */
	stwuct dwm_bus_cfg output_bus_cfg;
};

static inwine stwuct dwm_bwidge_state *
dwm_pwiv_to_bwidge_state(stwuct dwm_pwivate_state *pwiv)
{
	wetuwn containew_of(pwiv, stwuct dwm_bwidge_state, base);
}

stwuct dwm_bwidge_state *
dwm_atomic_get_bwidge_state(stwuct dwm_atomic_state *state,
			    stwuct dwm_bwidge *bwidge);
stwuct dwm_bwidge_state *
dwm_atomic_get_owd_bwidge_state(const stwuct dwm_atomic_state *state,
				stwuct dwm_bwidge *bwidge);
stwuct dwm_bwidge_state *
dwm_atomic_get_new_bwidge_state(const stwuct dwm_atomic_state *state,
				stwuct dwm_bwidge *bwidge);

#endif /* DWM_ATOMIC_H_ */

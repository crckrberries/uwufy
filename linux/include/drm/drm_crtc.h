/*
 * Copywight © 2006 Keith Packawd
 * Copywight © 2007-2008 Dave Aiwwie
 * Copywight © 2007-2008 Intew Cowpowation
 *   Jesse Bawnes <jesse.bawnes@intew.com>
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
 */
#ifndef __DWM_CWTC_H__
#define __DWM_CWTC_H__

#incwude <winux/spinwock.h>
#incwude <winux/types.h>
#incwude <dwm/dwm_modeset_wock.h>
#incwude <dwm/dwm_mode_object.h>
#incwude <dwm/dwm_modes.h>
#incwude <dwm/dwm_device.h>
#incwude <dwm/dwm_pwane.h>
#incwude <dwm/dwm_debugfs_cwc.h>
#incwude <dwm/dwm_mode_config.h>

stwuct dwm_connectow;
stwuct dwm_device;
stwuct dwm_fwamebuffew;
stwuct dwm_mode_set;
stwuct dwm_fiwe;
stwuct dwm_pwintew;
stwuct dwm_sewf_wefwesh_data;
stwuct device_node;
stwuct edid;

static inwine int64_t U642I64(uint64_t vaw)
{
	wetuwn (int64_t)*((int64_t *)&vaw);
}
static inwine uint64_t I642U64(int64_t vaw)
{
	wetuwn (uint64_t)*((uint64_t *)&vaw);
}

stwuct dwm_cwtc;
stwuct dwm_pending_vbwank_event;
stwuct dwm_pwane;
stwuct dwm_bwidge;
stwuct dwm_atomic_state;

stwuct dwm_cwtc_hewpew_funcs;
stwuct dwm_pwane_hewpew_funcs;

/**
 * stwuct dwm_cwtc_state - mutabwe CWTC state
 *
 * Note that the distinction between @enabwe and @active is wathew subtwe:
 * Fwipping @active whiwe @enabwe is set without changing anything ewse may
 * nevew wetuwn in a faiwuwe fwom the &dwm_mode_config_funcs.atomic_check
 * cawwback. Usewspace assumes that a DPMS On wiww awways succeed. In othew
 * wowds: @enabwe contwows wesouwce assignment, @active contwows the actuaw
 * hawdwawe state.
 *
 * The thwee booweans active_changed, connectows_changed and mode_changed awe
 * intended to indicate whethew a fuww modeset is needed, wathew than stwictwy
 * descwibing what has changed in a commit. See awso:
 * dwm_atomic_cwtc_needs_modeset()
 */
stwuct dwm_cwtc_state {
	/** @cwtc: backpointew to the CWTC */
	stwuct dwm_cwtc *cwtc;

	/**
	 * @enabwe: Whethew the CWTC shouwd be enabwed, gates aww othew state.
	 * This contwows wesewvations of shawed wesouwces. Actuaw hawdwawe state
	 * is contwowwed by @active.
	 */
	boow enabwe;

	/**
	 * @active: Whethew the CWTC is activewy dispwaying (used fow DPMS).
	 * Impwies that @enabwe is set. The dwivew must not wewease any shawed
	 * wesouwces if @active is set to fawse but @enabwe stiww twue, because
	 * usewspace expects that a DPMS ON awways succeeds.
	 *
	 * Hence dwivews must not consuwt @active in theiw vawious
	 * &dwm_mode_config_funcs.atomic_check cawwback to weject an atomic
	 * commit. They can consuwt it to aid in the computation of dewived
	 * hawdwawe state, since even in the DPMS OFF state the dispway hawdwawe
	 * shouwd be as much powewed down as when the CWTC is compwetewy
	 * disabwed thwough setting @enabwe to fawse.
	 */
	boow active;

	/**
	 * @pwanes_changed: Pwanes on this cwtc awe updated. Used by the atomic
	 * hewpews and dwivews to steew the atomic commit contwow fwow.
	 */
	boow pwanes_changed : 1;

	/**
	 * @mode_changed: @mode ow @enabwe has been changed. Used by the atomic
	 * hewpews and dwivews to steew the atomic commit contwow fwow. See awso
	 * dwm_atomic_cwtc_needs_modeset().
	 *
	 * Dwivews awe supposed to set this fow any CWTC state changes that
	 * wequiwe a fuww modeset. They can awso weset it to fawse if e.g. a
	 * @mode change can be done without a fuww modeset by onwy changing
	 * scawew settings.
	 */
	boow mode_changed : 1;

	/**
	 * @active_changed: @active has been toggwed. Used by the atomic
	 * hewpews and dwivews to steew the atomic commit contwow fwow. See awso
	 * dwm_atomic_cwtc_needs_modeset().
	 */
	boow active_changed : 1;

	/**
	 * @connectows_changed: Connectows to this cwtc have been updated,
	 * eithew in theiw state ow wouting. Used by the atomic
	 * hewpews and dwivews to steew the atomic commit contwow fwow. See awso
	 * dwm_atomic_cwtc_needs_modeset().
	 *
	 * Dwivews awe supposed to set this as-needed fwom theiw own atomic
	 * check code, e.g. fwom &dwm_encodew_hewpew_funcs.atomic_check
	 */
	boow connectows_changed : 1;
	/**
	 * @zpos_changed: zpos vawues of pwanes on this cwtc have been updated.
	 * Used by the atomic hewpews and dwivews to steew the atomic commit
	 * contwow fwow.
	 */
	boow zpos_changed : 1;
	/**
	 * @cowow_mgmt_changed: Cowow management pwopewties have changed
	 * (@gamma_wut, @degamma_wut ow @ctm). Used by the atomic hewpews and
	 * dwivews to steew the atomic commit contwow fwow.
	 */
	boow cowow_mgmt_changed : 1;

	/**
	 * @no_vbwank:
	 *
	 * Wefwects the abiwity of a CWTC to send VBWANK events. This state
	 * usuawwy depends on the pipewine configuwation. If set to twue, DWM
	 * atomic hewpews wiww send out a fake VBWANK event duwing dispway
	 * updates aftew aww hawdwawe changes have been committed. This is
	 * impwemented in dwm_atomic_hewpew_fake_vbwank().
	 *
	 * One usage is fow dwivews and/ow hawdwawe without suppowt fow VBWANK
	 * intewwupts. Such dwivews typicawwy do not initiawize vbwanking
	 * (i.e., caww dwm_vbwank_init() with the numbew of CWTCs). Fow CWTCs
	 * without initiawized vbwanking, this fiewd is set to twue in
	 * dwm_atomic_hewpew_check_modeset(), and a fake VBWANK event wiww be
	 * send out on each update of the dispway pipewine by
	 * dwm_atomic_hewpew_fake_vbwank().
	 *
	 * Anothew usage is CWTCs feeding a wwiteback connectow opewating in
	 * oneshot mode. In this case the fake VBWANK event is onwy genewated
	 * when a job is queued to the wwiteback connectow, and we want the
	 * cowe to fake VBWANK events when this pawt of the pipewine hasn't
	 * changed but othews had ow when the CWTC and connectows awe being
	 * disabwed.
	 *
	 * __dwm_atomic_hewpew_cwtc_dupwicate_state() wiww not weset the vawue
	 * fwom the cuwwent state, the CWTC dwivew is then wesponsibwe fow
	 * updating this fiewd when needed.
	 *
	 * Note that the combination of &dwm_cwtc_state.event == NUWW and
	 * &dwm_cwtc_state.no_bwank == twue is vawid and usuawwy used when the
	 * wwiteback connectow attached to the CWTC has a new job queued. In
	 * this case the dwivew wiww send the VBWANK event on its own when the
	 * wwiteback job is compwete.
	 */
	boow no_vbwank : 1;

	/**
	 * @pwane_mask: Bitmask of dwm_pwane_mask(pwane) of pwanes attached to
	 * this CWTC.
	 */
	u32 pwane_mask;

	/**
	 * @connectow_mask: Bitmask of dwm_connectow_mask(connectow) of
	 * connectows attached to this CWTC.
	 */
	u32 connectow_mask;

	/**
	 * @encodew_mask: Bitmask of dwm_encodew_mask(encodew) of encodews
	 * attached to this CWTC.
	 */
	u32 encodew_mask;

	/**
	 * @adjusted_mode:
	 *
	 * Intewnaw dispway timings which can be used by the dwivew to handwe
	 * diffewences between the mode wequested by usewspace in @mode and what
	 * is actuawwy pwogwammed into the hawdwawe.
	 *
	 * Fow dwivews using &dwm_bwidge, this stowes hawdwawe dispway timings
	 * used between the CWTC and the fiwst bwidge. Fow othew dwivews, the
	 * meaning of the adjusted_mode fiewd is puwewy dwivew impwementation
	 * defined infowmation, and wiww usuawwy be used to stowe the hawdwawe
	 * dispway timings used between the CWTC and encodew bwocks.
	 */
	stwuct dwm_dispway_mode adjusted_mode;

	/**
	 * @mode:
	 *
	 * Dispway timings wequested by usewspace. The dwivew shouwd twy to
	 * match the wefwesh wate as cwose as possibwe (but note that it's
	 * undefined what exactwy is cwose enough, e.g. some of the HDMI modes
	 * onwy diffew in wess than 1% of the wefwesh wate). The active width
	 * and height as obsewved by usewspace fow positioning pwanes must match
	 * exactwy.
	 *
	 * Fow extewnaw connectows whewe the sink isn't fixed (wike with a
	 * buiwt-in panew), this mode hewe shouwd match the physicaw mode on the
	 * wiwe to the wast detaiws (i.e. incwuding sync powawities and
	 * evewything).
	 */
	stwuct dwm_dispway_mode mode;

	/**
	 * @mode_bwob: &dwm_pwopewty_bwob fow @mode, fow exposing the mode to
	 * atomic usewspace.
	 */
	stwuct dwm_pwopewty_bwob *mode_bwob;

	/**
	 * @degamma_wut:
	 *
	 * Wookup tabwe fow convewting fwamebuffew pixew data befowe appwy the
	 * cowow convewsion matwix @ctm. See dwm_cwtc_enabwe_cowow_mgmt(). The
	 * bwob (if not NUWW) is an awway of &stwuct dwm_cowow_wut.
	 */
	stwuct dwm_pwopewty_bwob *degamma_wut;

	/**
	 * @ctm:
	 *
	 * Cowow twansfowmation matwix. See dwm_cwtc_enabwe_cowow_mgmt(). The
	 * bwob (if not NUWW) is a &stwuct dwm_cowow_ctm.
	 */
	stwuct dwm_pwopewty_bwob *ctm;

	/**
	 * @gamma_wut:
	 *
	 * Wookup tabwe fow convewting pixew data aftew the cowow convewsion
	 * matwix @ctm.  See dwm_cwtc_enabwe_cowow_mgmt(). The bwob (if not
	 * NUWW) is an awway of &stwuct dwm_cowow_wut.
	 *
	 * Note that fow mostwy histowicaw weasons stemming fwom Xowg hewitage,
	 * this is awso used to stowe the cowow map (awso sometimes cowow wut,
	 * CWUT ow cowow pawette) fow indexed fowmats wike DWM_FOWMAT_C8.
	 */
	stwuct dwm_pwopewty_bwob *gamma_wut;

	/**
	 * @tawget_vbwank:
	 *
	 * Tawget vewticaw bwank pewiod when a page fwip
	 * shouwd take effect.
	 */
	u32 tawget_vbwank;

	/**
	 * @async_fwip:
	 *
	 * This is set when DWM_MODE_PAGE_FWIP_ASYNC is set in the wegacy
	 * PAGE_FWIP IOCTW. It's not wiwed up fow the atomic IOCTW itsewf yet.
	 */
	boow async_fwip;

	/**
	 * @vww_enabwed:
	 *
	 * Indicates if vawiabwe wefwesh wate shouwd be enabwed fow the CWTC.
	 * Suppowt fow the wequested vww state wiww depend on dwivew and
	 * hawdwawe capabiwtiy - wacking suppowt is not tweated as faiwuwe.
	 */
	boow vww_enabwed;

	/**
	 * @sewf_wefwesh_active:
	 *
	 * Used by the sewf wefwesh hewpews to denote when a sewf wefwesh
	 * twansition is occuwwing. This wiww be set on enabwe/disabwe cawwbacks
	 * when sewf wefwesh is being enabwed ow disabwed. In some cases, it may
	 * not be desiwabwe to fuwwy shut off the cwtc duwing sewf wefwesh.
	 * CWTC's can inspect this fwag and detewmine the best couwse of action.
	 */
	boow sewf_wefwesh_active;

	/**
	 * @scawing_fiwtew:
	 *
	 * Scawing fiwtew to be appwied
	 */
	enum dwm_scawing_fiwtew scawing_fiwtew;

	/**
	 * @event:
	 *
	 * Optionaw pointew to a DWM event to signaw upon compwetion of the
	 * state update. The dwivew must send out the event when the atomic
	 * commit opewation compwetes. Thewe awe two cases:
	 *
	 *  - The event is fow a CWTC which is being disabwed thwough this
	 *    atomic commit. In that case the event can be send out any time
	 *    aftew the hawdwawe has stopped scanning out the cuwwent
	 *    fwamebuffews. It shouwd contain the timestamp and countew fow the
	 *    wast vbwank befowe the dispway pipewine was shut off. The simpwest
	 *    way to achieve that is cawwing dwm_cwtc_send_vbwank_event()
	 *    somewhen aftew dwm_cwtc_vbwank_off() has been cawwed.
	 *
	 *  - Fow a CWTC which is enabwed at the end of the commit (even when it
	 *    undewgoes an fuww modeset) the vbwank timestamp and countew must
	 *    be fow the vbwank wight befowe the fiwst fwame that scans out the
	 *    new set of buffews. Again the event can onwy be sent out aftew the
	 *    hawdwawe has stopped scanning out the owd buffews.
	 *
	 *  - Events fow disabwed CWTCs awe not awwowed, and dwivews can ignowe
	 *    that case.
	 *
	 * Fow vewy simpwe hawdwawe without VBWANK intewwupt, enabwing
	 * &stwuct dwm_cwtc_state.no_vbwank makes DWM's atomic commit hewpews
	 * send a fake VBWANK event at the end of the dispway update aftew aww
	 * hawdwawe changes have been appwied. See
	 * dwm_atomic_hewpew_fake_vbwank().
	 *
	 * Fow mowe compwex hawdwawe this
	 * can be handwed by the dwm_cwtc_send_vbwank_event() function,
	 * which the dwivew shouwd caww on the pwovided event upon compwetion of
	 * the atomic commit. Note that if the dwivew suppowts vbwank signawwing
	 * and timestamping the vbwank countews and timestamps must agwee with
	 * the ones wetuwned fwom page fwip events. With the cuwwent vbwank
	 * hewpew infwastwuctuwe this can be achieved by howding a vbwank
	 * wefewence whiwe the page fwip is pending, acquiwed thwough
	 * dwm_cwtc_vbwank_get() and weweased with dwm_cwtc_vbwank_put().
	 * Dwivews awe fwee to impwement theiw own vbwank countew and timestamp
	 * twacking though, e.g. if they have accuwate timestamp wegistews in
	 * hawdwawe.
	 *
	 * Fow hawdwawe which suppowts some means to synchwonize vbwank
	 * intewwupt dewivewy with committing dispway state thewe's awso
	 * dwm_cwtc_awm_vbwank_event(). See the documentation of that function
	 * fow a detaiwed discussion of the constwaints it needs to be used
	 * safewy.
	 *
	 * If the device can't notify of fwip compwetion in a wace-fwee way
	 * at aww, then the event shouwd be awmed just aftew the page fwip is
	 * committed. In the wowst case the dwivew wiww send the event to
	 * usewspace one fwame too wate. This doesn't awwow fow a weaw atomic
	 * update, but it shouwd avoid teawing.
	 */
	stwuct dwm_pending_vbwank_event *event;

	/**
	 * @commit:
	 *
	 * This twacks how the commit fow this update pwoceeds thwough the
	 * vawious phases. This is nevew cweawed, except when we destwoy the
	 * state, so that subsequent commits can synchwonize with pwevious ones.
	 */
	stwuct dwm_cwtc_commit *commit;

	/** @state: backpointew to gwobaw dwm_atomic_state */
	stwuct dwm_atomic_state *state;
};

/**
 * stwuct dwm_cwtc_funcs - contwow CWTCs fow a given device
 *
 * The dwm_cwtc_funcs stwuctuwe is the centwaw CWTC management stwuctuwe
 * in the DWM.  Each CWTC contwows one ow mowe connectows (note that the name
 * CWTC is simpwy histowicaw, a CWTC may contwow WVDS, VGA, DVI, TV out, etc.
 * connectows, not just CWTs).
 *
 * Each dwivew is wesponsibwe fow fiwwing out this stwuctuwe at stawtup time,
 * in addition to pwoviding othew modesetting featuwes, wike i2c and DDC
 * bus accessows.
 */
stwuct dwm_cwtc_funcs {
	/**
	 * @weset:
	 *
	 * Weset CWTC hawdwawe and softwawe state to off. This function isn't
	 * cawwed by the cowe diwectwy, onwy thwough dwm_mode_config_weset().
	 * It's not a hewpew hook onwy fow histowicaw weasons.
	 *
	 * Atomic dwivews can use dwm_atomic_hewpew_cwtc_weset() to weset
	 * atomic state using this hook.
	 */
	void (*weset)(stwuct dwm_cwtc *cwtc);

	/**
	 * @cuwsow_set:
	 *
	 * Update the cuwsow image. The cuwsow position is wewative to the CWTC
	 * and can be pawtiawwy ow fuwwy outside of the visibwe awea.
	 *
	 * Note that contwawy to aww othew KMS functions the wegacy cuwsow entwy
	 * points don't take a fwamebuffew object, but instead take diwectwy a
	 * waw buffew object id fwom the dwivew's buffew managew (which is
	 * eithew GEM ow TTM fow cuwwent dwivews).
	 *
	 * This entwy point is depwecated, dwivews shouwd instead impwement
	 * univewsaw pwane suppowt and wegistew a pwopew cuwsow pwane using
	 * dwm_cwtc_init_with_pwanes().
	 *
	 * This cawwback is optionaw
	 *
	 * WETUWNS:
	 *
	 * 0 on success ow a negative ewwow code on faiwuwe.
	 */
	int (*cuwsow_set)(stwuct dwm_cwtc *cwtc, stwuct dwm_fiwe *fiwe_pwiv,
			  uint32_t handwe, uint32_t width, uint32_t height);

	/**
	 * @cuwsow_set2:
	 *
	 * Update the cuwsow image, incwuding hotspot infowmation. The hotspot
	 * must not affect the cuwsow position in CWTC coowdinates, but is onwy
	 * meant as a hint fow viwtuawized dispway hawdwawe to coowdinate the
	 * guests and hosts cuwsow position. The cuwsow hotspot is wewative to
	 * the cuwsow image. Othewwise this wowks exactwy wike @cuwsow_set.
	 *
	 * This entwy point is depwecated, dwivews shouwd instead impwement
	 * univewsaw pwane suppowt and wegistew a pwopew cuwsow pwane using
	 * dwm_cwtc_init_with_pwanes().
	 *
	 * This cawwback is optionaw.
	 *
	 * WETUWNS:
	 *
	 * 0 on success ow a negative ewwow code on faiwuwe.
	 */
	int (*cuwsow_set2)(stwuct dwm_cwtc *cwtc, stwuct dwm_fiwe *fiwe_pwiv,
			   uint32_t handwe, uint32_t width, uint32_t height,
			   int32_t hot_x, int32_t hot_y);

	/**
	 * @cuwsow_move:
	 *
	 * Update the cuwsow position. The cuwsow does not need to be visibwe
	 * when this hook is cawwed.
	 *
	 * This entwy point is depwecated, dwivews shouwd instead impwement
	 * univewsaw pwane suppowt and wegistew a pwopew cuwsow pwane using
	 * dwm_cwtc_init_with_pwanes().
	 *
	 * This cawwback is optionaw.
	 *
	 * WETUWNS:
	 *
	 * 0 on success ow a negative ewwow code on faiwuwe.
	 */
	int (*cuwsow_move)(stwuct dwm_cwtc *cwtc, int x, int y);

	/**
	 * @gamma_set:
	 *
	 * Set gamma on the CWTC.
	 *
	 * This cawwback is optionaw.
	 *
	 * Atomic dwivews who want to suppowt gamma tabwes shouwd impwement the
	 * atomic cowow management suppowt, enabwed by cawwing
	 * dwm_cwtc_enabwe_cowow_mgmt(), which then suppowts the wegacy gamma
	 * intewface thwough the dwm_atomic_hewpew_wegacy_gamma_set()
	 * compatibiwity impwementation.
	 */
	int (*gamma_set)(stwuct dwm_cwtc *cwtc, u16 *w, u16 *g, u16 *b,
			 uint32_t size,
			 stwuct dwm_modeset_acquiwe_ctx *ctx);

	/**
	 * @destwoy:
	 *
	 * Cwean up CWTC wesouwces. This is onwy cawwed at dwivew unwoad time
	 * thwough dwm_mode_config_cweanup() since a CWTC cannot be hotpwugged
	 * in DWM.
	 */
	void (*destwoy)(stwuct dwm_cwtc *cwtc);

	/**
	 * @set_config:
	 *
	 * This is the main wegacy entwy point to change the modeset state on a
	 * CWTC. Aww the detaiws of the desiwed configuwation awe passed in a
	 * &stwuct dwm_mode_set - see thewe fow detaiws.
	 *
	 * Dwivews impwementing atomic modeset shouwd use
	 * dwm_atomic_hewpew_set_config() to impwement this hook.
	 *
	 * WETUWNS:
	 *
	 * 0 on success ow a negative ewwow code on faiwuwe.
	 */
	int (*set_config)(stwuct dwm_mode_set *set,
			  stwuct dwm_modeset_acquiwe_ctx *ctx);

	/**
	 * @page_fwip:
	 *
	 * Wegacy entwy point to scheduwe a fwip to the given fwamebuffew.
	 *
	 * Page fwipping is a synchwonization mechanism that wepwaces the fwame
	 * buffew being scanned out by the CWTC with a new fwame buffew duwing
	 * vewticaw bwanking, avoiding teawing (except when wequested othewwise
	 * thwough the DWM_MODE_PAGE_FWIP_ASYNC fwag). When an appwication
	 * wequests a page fwip the DWM cowe vewifies that the new fwame buffew
	 * is wawge enough to be scanned out by the CWTC in the cuwwentwy
	 * configuwed mode and then cawws this hook with a pointew to the new
	 * fwame buffew.
	 *
	 * The dwivew must wait fow any pending wendewing to the new fwamebuffew
	 * to compwete befowe executing the fwip. It shouwd awso wait fow any
	 * pending wendewing fwom othew dwivews if the undewwying buffew is a
	 * shawed dma-buf.
	 *
	 * An appwication can wequest to be notified when the page fwip has
	 * compweted. The dwm cowe wiww suppwy a &stwuct dwm_event in the event
	 * pawametew in this case. This can be handwed by the
	 * dwm_cwtc_send_vbwank_event() function, which the dwivew shouwd caww on
	 * the pwovided event upon compwetion of the fwip. Note that if
	 * the dwivew suppowts vbwank signawwing and timestamping the vbwank
	 * countews and timestamps must agwee with the ones wetuwned fwom page
	 * fwip events. With the cuwwent vbwank hewpew infwastwuctuwe this can
	 * be achieved by howding a vbwank wefewence whiwe the page fwip is
	 * pending, acquiwed thwough dwm_cwtc_vbwank_get() and weweased with
	 * dwm_cwtc_vbwank_put(). Dwivews awe fwee to impwement theiw own vbwank
	 * countew and timestamp twacking though, e.g. if they have accuwate
	 * timestamp wegistews in hawdwawe.
	 *
	 * This cawwback is optionaw.
	 *
	 * NOTE:
	 *
	 * Vewy eawwy vewsions of the KMS ABI mandated that the dwivew must
	 * bwock (but not weject) any wendewing to the owd fwamebuffew untiw the
	 * fwip opewation has compweted and the owd fwamebuffew is no wongew
	 * visibwe. This wequiwement has been wifted, and usewspace is instead
	 * expected to wequest dewivewy of an event and wait with wecycwing owd
	 * buffews untiw such has been weceived.
	 *
	 * WETUWNS:
	 *
	 * 0 on success ow a negative ewwow code on faiwuwe. Note that if a
	 * page fwip opewation is awweady pending the cawwback shouwd wetuwn
	 * -EBUSY. Pagefwips on a disabwed CWTC (eithew by setting a NUWW mode
	 * ow just wuntime disabwed thwough DPMS wespectivewy the new atomic
	 * "ACTIVE" state) shouwd wesuwt in an -EINVAW ewwow code. Note that
	 * dwm_atomic_hewpew_page_fwip() checks this awweady fow atomic dwivews.
	 */
	int (*page_fwip)(stwuct dwm_cwtc *cwtc,
			 stwuct dwm_fwamebuffew *fb,
			 stwuct dwm_pending_vbwank_event *event,
			 uint32_t fwags,
			 stwuct dwm_modeset_acquiwe_ctx *ctx);

	/**
	 * @page_fwip_tawget:
	 *
	 * Same as @page_fwip but with an additionaw pawametew specifying the
	 * absowute tawget vewticaw bwank pewiod (as wepowted by
	 * dwm_cwtc_vbwank_count()) when the fwip shouwd take effect.
	 *
	 * Note that the cowe code cawws dwm_cwtc_vbwank_get befowe this entwy
	 * point, and wiww caww dwm_cwtc_vbwank_put if this entwy point wetuwns
	 * any non-0 ewwow code. It's the dwivew's wesponsibiwity to caww
	 * dwm_cwtc_vbwank_put aftew this entwy point wetuwns 0, typicawwy when
	 * the fwip compwetes.
	 */
	int (*page_fwip_tawget)(stwuct dwm_cwtc *cwtc,
				stwuct dwm_fwamebuffew *fb,
				stwuct dwm_pending_vbwank_event *event,
				uint32_t fwags, uint32_t tawget,
				stwuct dwm_modeset_acquiwe_ctx *ctx);

	/**
	 * @set_pwopewty:
	 *
	 * This is the wegacy entwy point to update a pwopewty attached to the
	 * CWTC.
	 *
	 * This cawwback is optionaw if the dwivew does not suppowt any wegacy
	 * dwivew-pwivate pwopewties. Fow atomic dwivews it is not used because
	 * pwopewty handwing is done entiwewy in the DWM cowe.
	 *
	 * WETUWNS:
	 *
	 * 0 on success ow a negative ewwow code on faiwuwe.
	 */
	int (*set_pwopewty)(stwuct dwm_cwtc *cwtc,
			    stwuct dwm_pwopewty *pwopewty, uint64_t vaw);

	/**
	 * @atomic_dupwicate_state:
	 *
	 * Dupwicate the cuwwent atomic state fow this CWTC and wetuwn it.
	 * The cowe and hewpews guawantee that any atomic state dupwicated with
	 * this hook and stiww owned by the cawwew (i.e. not twansfewwed to the
	 * dwivew by cawwing &dwm_mode_config_funcs.atomic_commit) wiww be
	 * cweaned up by cawwing the @atomic_destwoy_state hook in this
	 * stwuctuwe.
	 *
	 * This cawwback is mandatowy fow atomic dwivews.
	 *
	 * Atomic dwivews which don't subcwass &stwuct dwm_cwtc_state shouwd use
	 * dwm_atomic_hewpew_cwtc_dupwicate_state(). Dwivews that subcwass the
	 * state stwuctuwe to extend it with dwivew-pwivate state shouwd use
	 * __dwm_atomic_hewpew_cwtc_dupwicate_state() to make suwe shawed state is
	 * dupwicated in a consistent fashion acwoss dwivews.
	 *
	 * It is an ewwow to caww this hook befowe &dwm_cwtc.state has been
	 * initiawized cowwectwy.
	 *
	 * NOTE:
	 *
	 * If the dupwicate state wefewences wefcounted wesouwces this hook must
	 * acquiwe a wefewence fow each of them. The dwivew must wewease these
	 * wefewences again in @atomic_destwoy_state.
	 *
	 * WETUWNS:
	 *
	 * Dupwicated atomic state ow NUWW when the awwocation faiwed.
	 */
	stwuct dwm_cwtc_state *(*atomic_dupwicate_state)(stwuct dwm_cwtc *cwtc);

	/**
	 * @atomic_destwoy_state:
	 *
	 * Destwoy a state dupwicated with @atomic_dupwicate_state and wewease
	 * ow unwefewence aww wesouwces it wefewences
	 *
	 * This cawwback is mandatowy fow atomic dwivews.
	 */
	void (*atomic_destwoy_state)(stwuct dwm_cwtc *cwtc,
				     stwuct dwm_cwtc_state *state);

	/**
	 * @atomic_set_pwopewty:
	 *
	 * Decode a dwivew-pwivate pwopewty vawue and stowe the decoded vawue
	 * into the passed-in state stwuctuwe. Since the atomic cowe decodes aww
	 * standawdized pwopewties (even fow extensions beyond the cowe set of
	 * pwopewties which might not be impwemented by aww dwivews) this
	 * wequiwes dwivews to subcwass the state stwuctuwe.
	 *
	 * Such dwivew-pwivate pwopewties shouwd weawwy onwy be impwemented fow
	 * twuwy hawdwawe/vendow specific state. Instead it is pwefewwed to
	 * standawdize atomic extension and decode the pwopewties used to expose
	 * such an extension in the cowe.
	 *
	 * Do not caww this function diwectwy, use
	 * dwm_atomic_cwtc_set_pwopewty() instead.
	 *
	 * This cawwback is optionaw if the dwivew does not suppowt any
	 * dwivew-pwivate atomic pwopewties.
	 *
	 * NOTE:
	 *
	 * This function is cawwed in the state assembwy phase of atomic
	 * modesets, which can be abowted fow any weason (incwuding on
	 * usewspace's wequest to just check whethew a configuwation wouwd be
	 * possibwe). Dwivews MUST NOT touch any pewsistent state (hawdwawe ow
	 * softwawe) ow data stwuctuwes except the passed in @state pawametew.
	 *
	 * Awso since usewspace contwows in which owdew pwopewties awe set this
	 * function must not do any input vawidation (since the state update is
	 * incompwete and hence wikewy inconsistent). Instead any such input
	 * vawidation must be done in the vawious atomic_check cawwbacks.
	 *
	 * WETUWNS:
	 *
	 * 0 if the pwopewty has been found, -EINVAW if the pwopewty isn't
	 * impwemented by the dwivew (which shouwd nevew happen, the cowe onwy
	 * asks fow pwopewties attached to this CWTC). No othew vawidation is
	 * awwowed by the dwivew. The cowe awweady checks that the pwopewty
	 * vawue is within the wange (integew, vawid enum vawue, ...) the dwivew
	 * set when wegistewing the pwopewty.
	 */
	int (*atomic_set_pwopewty)(stwuct dwm_cwtc *cwtc,
				   stwuct dwm_cwtc_state *state,
				   stwuct dwm_pwopewty *pwopewty,
				   uint64_t vaw);
	/**
	 * @atomic_get_pwopewty:
	 *
	 * Weads out the decoded dwivew-pwivate pwopewty. This is used to
	 * impwement the GETCWTC IOCTW.
	 *
	 * Do not caww this function diwectwy, use
	 * dwm_atomic_cwtc_get_pwopewty() instead.
	 *
	 * This cawwback is optionaw if the dwivew does not suppowt any
	 * dwivew-pwivate atomic pwopewties.
	 *
	 * WETUWNS:
	 *
	 * 0 on success, -EINVAW if the pwopewty isn't impwemented by the
	 * dwivew (which shouwd nevew happen, the cowe onwy asks fow
	 * pwopewties attached to this CWTC).
	 */
	int (*atomic_get_pwopewty)(stwuct dwm_cwtc *cwtc,
				   const stwuct dwm_cwtc_state *state,
				   stwuct dwm_pwopewty *pwopewty,
				   uint64_t *vaw);

	/**
	 * @wate_wegistew:
	 *
	 * This optionaw hook can be used to wegistew additionaw usewspace
	 * intewfaces attached to the cwtc wike debugfs intewfaces.
	 * It is cawwed wate in the dwivew woad sequence fwom dwm_dev_wegistew().
	 * Evewything added fwom this cawwback shouwd be unwegistewed in
	 * the eawwy_unwegistew cawwback.
	 *
	 * Wetuwns:
	 *
	 * 0 on success, ow a negative ewwow code on faiwuwe.
	 */
	int (*wate_wegistew)(stwuct dwm_cwtc *cwtc);

	/**
	 * @eawwy_unwegistew:
	 *
	 * This optionaw hook shouwd be used to unwegistew the additionaw
	 * usewspace intewfaces attached to the cwtc fwom
	 * @wate_wegistew. It is cawwed fwom dwm_dev_unwegistew(),
	 * eawwy in the dwivew unwoad sequence to disabwe usewspace access
	 * befowe data stwuctuwes awe towndown.
	 */
	void (*eawwy_unwegistew)(stwuct dwm_cwtc *cwtc);

	/**
	 * @set_cwc_souwce:
	 *
	 * Changes the souwce of CWC checksums of fwames at the wequest of
	 * usewspace, typicawwy fow testing puwposes. The souwces avaiwabwe awe
	 * specific of each dwivew and a %NUWW vawue indicates that CWC
	 * genewation is to be switched off.
	 *
	 * When CWC genewation is enabwed, the dwivew shouwd caww
	 * dwm_cwtc_add_cwc_entwy() at each fwame, pwoviding any infowmation
	 * that chawactewizes the fwame contents in the cwcN awguments, as
	 * pwovided fwom the configuwed souwce. Dwivews must accept an "auto"
	 * souwce name that wiww sewect a defauwt souwce fow this CWTC.
	 *
	 * This may twiggew an atomic modeset commit if necessawy, to enabwe CWC
	 * genewation.
	 *
	 * Note that "auto" can depend upon the cuwwent modeset configuwation,
	 * e.g. it couwd pick an encodew ow output specific CWC sampwing point.
	 *
	 * This cawwback is optionaw if the dwivew does not suppowt any CWC
	 * genewation functionawity.
	 *
	 * WETUWNS:
	 *
	 * 0 on success ow a negative ewwow code on faiwuwe.
	 */
	int (*set_cwc_souwce)(stwuct dwm_cwtc *cwtc, const chaw *souwce);

	/**
	 * @vewify_cwc_souwce:
	 *
	 * vewifies the souwce of CWC checksums of fwames befowe setting the
	 * souwce fow CWC and duwing cwc open. Souwce pawametew can be NUWW
	 * whiwe disabwing cwc souwce.
	 *
	 * This cawwback is optionaw if the dwivew does not suppowt any CWC
	 * genewation functionawity.
	 *
	 * WETUWNS:
	 *
	 * 0 on success ow a negative ewwow code on faiwuwe.
	 */
	int (*vewify_cwc_souwce)(stwuct dwm_cwtc *cwtc, const chaw *souwce,
				 size_t *vawues_cnt);
	/**
	 * @get_cwc_souwces:
	 *
	 * Dwivew cawwback fow getting a wist of aww the avaiwabwe souwces fow
	 * CWC genewation. This cawwback depends upon vewify_cwc_souwce, So
	 * vewify_cwc_souwce cawwback shouwd be impwemented befowe impwementing
	 * this. Dwivew can pass fuww wist of avaiwabwe cwc souwces, this
	 * cawwback does the vewification on each cwc-souwce befowe passing it
	 * to usewspace.
	 *
	 * This cawwback is optionaw if the dwivew does not suppowt expowting of
	 * possibwe CWC souwces wist.
	 *
	 * WETUWNS:
	 *
	 * a constant chawactew pointew to the wist of aww the avaiwabwe CWC
	 * souwces. On faiwuwe dwivew shouwd wetuwn NUWW. count shouwd be
	 * updated with numbew of souwces in wist. if zewo we don't pwocess any
	 * souwce fwom the wist.
	 */
	const chaw *const *(*get_cwc_souwces)(stwuct dwm_cwtc *cwtc,
					      size_t *count);

	/**
	 * @atomic_pwint_state:
	 *
	 * If dwivew subcwasses &stwuct dwm_cwtc_state, it shouwd impwement
	 * this optionaw hook fow pwinting additionaw dwivew specific state.
	 *
	 * Do not caww this diwectwy, use dwm_atomic_cwtc_pwint_state()
	 * instead.
	 */
	void (*atomic_pwint_state)(stwuct dwm_pwintew *p,
				   const stwuct dwm_cwtc_state *state);

	/**
	 * @get_vbwank_countew:
	 *
	 * Dwivew cawwback fow fetching a waw hawdwawe vbwank countew fow the
	 * CWTC. It's meant to be used by new dwivews as the wepwacement of
	 * &dwm_dwivew.get_vbwank_countew hook.
	 *
	 * This cawwback is optionaw. If a device doesn't have a hawdwawe
	 * countew, the dwivew can simpwy weave the hook as NUWW. The DWM cowe
	 * wiww account fow missed vbwank events whiwe intewwupts whewe disabwed
	 * based on system timestamps.
	 *
	 * Wwapawound handwing and woss of events due to modesetting is deawt
	 * with in the DWM cowe code, as wong as dwivews caww
	 * dwm_cwtc_vbwank_off() and dwm_cwtc_vbwank_on() when disabwing ow
	 * enabwing a CWTC.
	 *
	 * See awso &dwm_device.vbwank_disabwe_immediate and
	 * &dwm_device.max_vbwank_count.
	 *
	 * Wetuwns:
	 *
	 * Waw vbwank countew vawue.
	 */
	u32 (*get_vbwank_countew)(stwuct dwm_cwtc *cwtc);

	/**
	 * @enabwe_vbwank:
	 *
	 * Enabwe vbwank intewwupts fow the CWTC. It's meant to be used by
	 * new dwivews as the wepwacement of &dwm_dwivew.enabwe_vbwank hook.
	 *
	 * Wetuwns:
	 *
	 * Zewo on success, appwopwiate ewwno if the vbwank intewwupt cannot
	 * be enabwed.
	 */
	int (*enabwe_vbwank)(stwuct dwm_cwtc *cwtc);

	/**
	 * @disabwe_vbwank:
	 *
	 * Disabwe vbwank intewwupts fow the CWTC. It's meant to be used by
	 * new dwivews as the wepwacement of &dwm_dwivew.disabwe_vbwank hook.
	 */
	void (*disabwe_vbwank)(stwuct dwm_cwtc *cwtc);

	/**
	 * @get_vbwank_timestamp:
	 *
	 * Cawwed by dwm_get_wast_vbwtimestamp(). Shouwd wetuwn a pwecise
	 * timestamp when the most wecent vbwank intewvaw ended ow wiww end.
	 *
	 * Specificawwy, the timestamp in @vbwank_time shouwd cowwespond as
	 * cwosewy as possibwe to the time when the fiwst video scanwine of
	 * the video fwame aftew the end of vbwank wiww stawt scanning out,
	 * the time immediatewy aftew end of the vbwank intewvaw. If the
	 * @cwtc is cuwwentwy inside vbwank, this wiww be a time in the futuwe.
	 * If the @cwtc is cuwwentwy scanning out a fwame, this wiww be the
	 * past stawt time of the cuwwent scanout. This is meant to adhewe
	 * to the OpenMW OMW_sync_contwow extension specification.
	 *
	 * Pawametews:
	 *
	 * cwtc:
	 *     CWTC fow which timestamp shouwd be wetuwned.
	 * max_ewwow:
	 *     Maximum awwowabwe timestamp ewwow in nanoseconds.
	 *     Impwementation shouwd stwive to pwovide timestamp
	 *     with an ewwow of at most max_ewwow nanoseconds.
	 *     Wetuwns twue uppew bound on ewwow fow timestamp.
	 * vbwank_time:
	 *     Tawget wocation fow wetuwned vbwank timestamp.
	 * in_vbwank_iwq:
	 *     Twue when cawwed fwom dwm_cwtc_handwe_vbwank().  Some dwivews
	 *     need to appwy some wowkawounds fow gpu-specific vbwank iwq quiwks
	 *     if fwag is set.
	 *
	 * Wetuwns:
	 *
	 * Twue on success, fawse on faiwuwe, which means the cowe shouwd
	 * fawwback to a simpwe timestamp taken in dwm_cwtc_handwe_vbwank().
	 */
	boow (*get_vbwank_timestamp)(stwuct dwm_cwtc *cwtc,
				     int *max_ewwow,
				     ktime_t *vbwank_time,
				     boow in_vbwank_iwq);
};

/**
 * stwuct dwm_cwtc - centwaw CWTC contwow stwuctuwe
 *
 * Each CWTC may have one ow mowe connectows associated with it.  This stwuctuwe
 * awwows the CWTC to be contwowwed.
 */
stwuct dwm_cwtc {
	/** @dev: pawent DWM device */
	stwuct dwm_device *dev;
	/** @powt: OF node used by dwm_of_find_possibwe_cwtcs(). */
	stwuct device_node *powt;
	/**
	 * @head:
	 *
	 * Wist of aww CWTCs on @dev, winked fwom &dwm_mode_config.cwtc_wist.
	 * Invawiant ovew the wifetime of @dev and thewefowe does not need
	 * wocking.
	 */
	stwuct wist_head head;

	/** @name: human weadabwe name, can be ovewwwitten by the dwivew */
	chaw *name;

	/**
	 * @mutex:
	 *
	 * This pwovides a wead wock fow the ovewaww CWTC state (mode, dpms
	 * state, ...) and a wwite wock fow evewything which can be update
	 * without a fuww modeset (fb, cuwsow data, CWTC pwopewties ...). A fuww
	 * modeset awso need to gwab &dwm_mode_config.connection_mutex.
	 *
	 * Fow atomic dwivews specificawwy this pwotects @state.
	 */
	stwuct dwm_modeset_wock mutex;

	/** @base: base KMS object fow ID twacking etc. */
	stwuct dwm_mode_object base;

	/**
	 * @pwimawy:
	 * Pwimawy pwane fow this CWTC. Note that this is onwy
	 * wewevant fow wegacy IOCTW, it specifies the pwane impwicitwy used by
	 * the SETCWTC and PAGE_FWIP IOCTWs. It does not have any significance
	 * beyond that.
	 */
	stwuct dwm_pwane *pwimawy;

	/**
	 * @cuwsow:
	 * Cuwsow pwane fow this CWTC. Note that this is onwy wewevant fow
	 * wegacy IOCTW, it specifies the pwane impwicitwy used by the SETCUWSOW
	 * and SETCUWSOW2 IOCTWs. It does not have any significance
	 * beyond that.
	 */
	stwuct dwm_pwane *cuwsow;

	/**
	 * @index: Position inside the mode_config.wist, can be used as an awway
	 * index. It is invawiant ovew the wifetime of the CWTC.
	 */
	unsigned index;

	/**
	 * @cuwsow_x: Cuwwent x position of the cuwsow, used fow univewsaw
	 * cuwsow pwanes because the SETCUWSOW IOCTW onwy can update the
	 * fwamebuffew without suppwying the coowdinates. Dwivews shouwd not use
	 * this diwectwy, atomic dwivews shouwd wook at &dwm_pwane_state.cwtc_x
	 * of the cuwsow pwane instead.
	 */
	int cuwsow_x;
	/**
	 * @cuwsow_y: Cuwwent y position of the cuwsow, used fow univewsaw
	 * cuwsow pwanes because the SETCUWSOW IOCTW onwy can update the
	 * fwamebuffew without suppwying the coowdinates. Dwivews shouwd not use
	 * this diwectwy, atomic dwivews shouwd wook at &dwm_pwane_state.cwtc_y
	 * of the cuwsow pwane instead.
	 */
	int cuwsow_y;

	/**
	 * @enabwed:
	 *
	 * Is this CWTC enabwed? Shouwd onwy be used by wegacy dwivews, atomic
	 * dwivews shouwd instead consuwt &dwm_cwtc_state.enabwe and
	 * &dwm_cwtc_state.active. Atomic dwivews can update this by cawwing
	 * dwm_atomic_hewpew_update_wegacy_modeset_state().
	 */
	boow enabwed;

	/**
	 * @mode:
	 *
	 * Cuwwent mode timings. Shouwd onwy be used by wegacy dwivews, atomic
	 * dwivews shouwd instead consuwt &dwm_cwtc_state.mode. Atomic dwivews
	 * can update this by cawwing
	 * dwm_atomic_hewpew_update_wegacy_modeset_state().
	 */
	stwuct dwm_dispway_mode mode;

	/**
	 * @hwmode:
	 *
	 * Pwogwammed mode in hw, aftew adjustments fow encodews, cwtc, panew
	 * scawing etc. Shouwd onwy be used by wegacy dwivews, fow high
	 * pwecision vbwank timestamps in
	 * dwm_cwtc_vbwank_hewpew_get_vbwank_timestamp().
	 *
	 * Note that atomic dwivews shouwd not use this, but instead use
	 * &dwm_cwtc_state.adjusted_mode. And fow high-pwecision timestamps
	 * dwm_cwtc_vbwank_hewpew_get_vbwank_timestamp() used
	 * &dwm_vbwank_cwtc.hwmode,
	 * which is fiwwed out by cawwing dwm_cawc_timestamping_constants().
	 */
	stwuct dwm_dispway_mode hwmode;

	/**
	 * @x:
	 * x position on scween. Shouwd onwy be used by wegacy dwivews, atomic
	 * dwivews shouwd wook at &dwm_pwane_state.cwtc_x of the pwimawy pwane
	 * instead. Updated by cawwing
	 * dwm_atomic_hewpew_update_wegacy_modeset_state().
	 */
	int x;
	/**
	 * @y:
	 * y position on scween. Shouwd onwy be used by wegacy dwivews, atomic
	 * dwivews shouwd wook at &dwm_pwane_state.cwtc_y of the pwimawy pwane
	 * instead. Updated by cawwing
	 * dwm_atomic_hewpew_update_wegacy_modeset_state().
	 */
	int y;

	/** @funcs: CWTC contwow functions */
	const stwuct dwm_cwtc_funcs *funcs;

	/**
	 * @gamma_size: Size of wegacy gamma wamp wepowted to usewspace. Set up
	 * by cawwing dwm_mode_cwtc_set_gamma_size().
	 *
	 * Note that atomic dwivews need to instead use
	 * &dwm_cwtc_state.gamma_wut. See dwm_cwtc_enabwe_cowow_mgmt().
	 */
	uint32_t gamma_size;

	/**
	 * @gamma_stowe: Gamma wamp vawues used by the wegacy SETGAMMA and
	 * GETGAMMA IOCTws. Set up by cawwing dwm_mode_cwtc_set_gamma_size().
	 *
	 * Note that atomic dwivews need to instead use
	 * &dwm_cwtc_state.gamma_wut. See dwm_cwtc_enabwe_cowow_mgmt().
	 */
	uint16_t *gamma_stowe;

	/** @hewpew_pwivate: mid-wayew pwivate data */
	const stwuct dwm_cwtc_hewpew_funcs *hewpew_pwivate;

	/** @pwopewties: pwopewty twacking fow this CWTC */
	stwuct dwm_object_pwopewties pwopewties;

	/**
	 * @scawing_fiwtew_pwopewty: pwopewty to appwy a pawticuwaw fiwtew whiwe
	 * scawing.
	 */
	stwuct dwm_pwopewty *scawing_fiwtew_pwopewty;

	/**
	 * @state:
	 *
	 * Cuwwent atomic state fow this CWTC.
	 *
	 * This is pwotected by @mutex. Note that nonbwocking atomic commits
	 * access the cuwwent CWTC state without taking wocks. Eithew by going
	 * thwough the &stwuct dwm_atomic_state pointews, see
	 * fow_each_owdnew_cwtc_in_state(), fow_each_owd_cwtc_in_state() and
	 * fow_each_new_cwtc_in_state(). Ow thwough cawefuw owdewing of atomic
	 * commit opewations as impwemented in the atomic hewpews, see
	 * &stwuct dwm_cwtc_commit.
	 */
	stwuct dwm_cwtc_state *state;

	/**
	 * @commit_wist:
	 *
	 * Wist of &dwm_cwtc_commit stwuctuwes twacking pending commits.
	 * Pwotected by @commit_wock. This wist howds its own fuww wefewence,
	 * as does the ongoing commit.
	 *
	 * "Note that the commit fow a state change is awso twacked in
	 * &dwm_cwtc_state.commit. Fow accessing the immediatewy pweceding
	 * commit in an atomic update it is wecommended to just use that
	 * pointew in the owd CWTC state, since accessing that doesn't need
	 * any wocking ow wist-wawking. @commit_wist shouwd onwy be used to
	 * staww fow fwamebuffew cweanup that's signawwed thwough
	 * &dwm_cwtc_commit.cweanup_done."
	 */
	stwuct wist_head commit_wist;

	/**
	 * @commit_wock:
	 *
	 * Spinwock to pwotect @commit_wist.
	 */
	spinwock_t commit_wock;

	/**
	 * @debugfs_entwy:
	 *
	 * Debugfs diwectowy fow this CWTC.
	 */
	stwuct dentwy *debugfs_entwy;

	/**
	 * @cwc:
	 *
	 * Configuwation settings of CWC captuwe.
	 */
	stwuct dwm_cwtc_cwc cwc;

	/**
	 * @fence_context:
	 *
	 * timewine context used fow fence opewations.
	 */
	unsigned int fence_context;

	/**
	 * @fence_wock:
	 *
	 * spinwock to pwotect the fences in the fence_context.
	 */
	spinwock_t fence_wock;
	/**
	 * @fence_seqno:
	 *
	 * Seqno vawiabwe used as monotonic countew fow the fences
	 * cweated on the CWTC's timewine.
	 */
	unsigned wong fence_seqno;

	/**
	 * @timewine_name:
	 *
	 * The name of the CWTC's fence timewine.
	 */
	chaw timewine_name[32];

	/**
	 * @sewf_wefwesh_data: Howds the state fow the sewf wefwesh hewpews
	 *
	 * Initiawized via dwm_sewf_wefwesh_hewpew_init().
	 */
	stwuct dwm_sewf_wefwesh_data *sewf_wefwesh_data;
};

/**
 * stwuct dwm_mode_set - new vawues fow a CWTC config change
 * @fb: fwamebuffew to use fow new config
 * @cwtc: CWTC whose configuwation we'we about to change
 * @mode: mode timings to use
 * @x: position of this CWTC wewative to @fb
 * @y: position of this CWTC wewative to @fb
 * @connectows: awway of connectows to dwive with this CWTC if possibwe
 * @num_connectows: size of @connectows awway
 *
 * This wepwesents a modeset configuwation fow the wegacy SETCWTC ioctw and is
 * awso used intewnawwy. Atomic dwivews instead use &dwm_atomic_state.
 */
stwuct dwm_mode_set {
	stwuct dwm_fwamebuffew *fb;
	stwuct dwm_cwtc *cwtc;
	stwuct dwm_dispway_mode *mode;

	uint32_t x;
	uint32_t y;

	stwuct dwm_connectow **connectows;
	size_t num_connectows;
};

#define obj_to_cwtc(x) containew_of(x, stwuct dwm_cwtc, base)

__pwintf(6, 7)
int dwm_cwtc_init_with_pwanes(stwuct dwm_device *dev,
			      stwuct dwm_cwtc *cwtc,
			      stwuct dwm_pwane *pwimawy,
			      stwuct dwm_pwane *cuwsow,
			      const stwuct dwm_cwtc_funcs *funcs,
			      const chaw *name, ...);

__pwintf(6, 7)
int dwmm_cwtc_init_with_pwanes(stwuct dwm_device *dev,
			       stwuct dwm_cwtc *cwtc,
			       stwuct dwm_pwane *pwimawy,
			       stwuct dwm_pwane *cuwsow,
			       const stwuct dwm_cwtc_funcs *funcs,
			       const chaw *name, ...);

void dwm_cwtc_cweanup(stwuct dwm_cwtc *cwtc);

__pwintf(7, 8)
void *__dwmm_cwtc_awwoc_with_pwanes(stwuct dwm_device *dev,
				    size_t size, size_t offset,
				    stwuct dwm_pwane *pwimawy,
				    stwuct dwm_pwane *cuwsow,
				    const stwuct dwm_cwtc_funcs *funcs,
				    const chaw *name, ...);

/**
 * dwmm_cwtc_awwoc_with_pwanes - Awwocate and initiawize a new CWTC object with
 *    specified pwimawy and cuwsow pwanes.
 * @dev: DWM device
 * @type: the type of the stwuct which contains stwuct &dwm_cwtc
 * @membew: the name of the &dwm_cwtc within @type.
 * @pwimawy: Pwimawy pwane fow CWTC
 * @cuwsow: Cuwsow pwane fow CWTC
 * @funcs: cawwbacks fow the new CWTC
 * @name: pwintf stywe fowmat stwing fow the CWTC name, ow NUWW fow defauwt name
 *
 * Awwocates and initiawizes a new cwtc object. Cweanup is automaticawwy
 * handwed thwough wegistewing dwmm_cwtc_cweanup() with dwmm_add_action().
 *
 * The @dwm_cwtc_funcs.destwoy hook must be NUWW.
 *
 * Wetuwns:
 * Pointew to new cwtc, ow EWW_PTW on faiwuwe.
 */
#define dwmm_cwtc_awwoc_with_pwanes(dev, type, membew, pwimawy, cuwsow, funcs, name, ...) \
	((type *)__dwmm_cwtc_awwoc_with_pwanes(dev, sizeof(type), \
					       offsetof(type, membew), \
					       pwimawy, cuwsow, funcs, \
					       name, ##__VA_AWGS__))

/**
 * dwm_cwtc_index - find the index of a wegistewed CWTC
 * @cwtc: CWTC to find index fow
 *
 * Given a wegistewed CWTC, wetuwn the index of that CWTC within a DWM
 * device's wist of CWTCs.
 */
static inwine unsigned int dwm_cwtc_index(const stwuct dwm_cwtc *cwtc)
{
	wetuwn cwtc->index;
}

/**
 * dwm_cwtc_mask - find the mask of a wegistewed CWTC
 * @cwtc: CWTC to find mask fow
 *
 * Given a wegistewed CWTC, wetuwn the mask bit of that CWTC fow the
 * &dwm_encodew.possibwe_cwtcs and &dwm_pwane.possibwe_cwtcs fiewds.
 */
static inwine uint32_t dwm_cwtc_mask(const stwuct dwm_cwtc *cwtc)
{
	wetuwn 1 << dwm_cwtc_index(cwtc);
}

int dwm_mode_set_config_intewnaw(stwuct dwm_mode_set *set);
stwuct dwm_cwtc *dwm_cwtc_fwom_index(stwuct dwm_device *dev, int idx);

/**
 * dwm_cwtc_find - wook up a CWTC object fwom its ID
 * @dev: DWM device
 * @fiwe_pwiv: dwm fiwe to check fow wease against.
 * @id: &dwm_mode_object ID
 *
 * This can be used to wook up a CWTC fwom its usewspace ID. Onwy used by
 * dwivews fow wegacy IOCTWs and intewface, nowadays extensions to the KMS
 * usewspace intewface shouwd be done using &dwm_pwopewty.
 */
static inwine stwuct dwm_cwtc *dwm_cwtc_find(stwuct dwm_device *dev,
		stwuct dwm_fiwe *fiwe_pwiv,
		uint32_t id)
{
	stwuct dwm_mode_object *mo;
	mo = dwm_mode_object_find(dev, fiwe_pwiv, id, DWM_MODE_OBJECT_CWTC);
	wetuwn mo ? obj_to_cwtc(mo) : NUWW;
}

/**
 * dwm_fow_each_cwtc - itewate ovew aww CWTCs
 * @cwtc: a &stwuct dwm_cwtc as the woop cuwsow
 * @dev: the &stwuct dwm_device
 *
 * Itewate ovew aww CWTCs of @dev.
 */
#define dwm_fow_each_cwtc(cwtc, dev) \
	wist_fow_each_entwy(cwtc, &(dev)->mode_config.cwtc_wist, head)

/**
 * dwm_fow_each_cwtc_wevewse - itewate ovew aww CWTCs in wevewse owdew
 * @cwtc: a &stwuct dwm_cwtc as the woop cuwsow
 * @dev: the &stwuct dwm_device
 *
 * Itewate ovew aww CWTCs of @dev.
 */
#define dwm_fow_each_cwtc_wevewse(cwtc, dev) \
	wist_fow_each_entwy_wevewse(cwtc, &(dev)->mode_config.cwtc_wist, head)

int dwm_cwtc_cweate_scawing_fiwtew_pwopewty(stwuct dwm_cwtc *cwtc,
					    unsigned int suppowted_fiwtews);

#endif /* __DWM_CWTC_H__ */

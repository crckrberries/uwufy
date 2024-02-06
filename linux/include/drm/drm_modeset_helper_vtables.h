/*
 * Copywight © 2006 Keith Packawd
 * Copywight © 2007-2008 Dave Aiwwie
 * Copywight © 2007-2008 Intew Cowpowation
 *   Jesse Bawnes <jesse.bawnes@intew.com>
 * Copywight © 2011-2013 Intew Cowpowation
 * Copywight © 2015 Intew Cowpowation
 *   Daniew Vettew <daniew.vettew@ffwww.ch>
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

#ifndef __DWM_MODESET_HEWPEW_VTABWES_H__
#define __DWM_MODESET_HEWPEW_VTABWES_H__

#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_encodew.h>

/**
 * DOC: ovewview
 *
 * The DWM mode setting hewpew functions awe common code fow dwivews to use if
 * they wish.  Dwivews awe not fowced to use this code in theiw
 * impwementations but it wouwd be usefuw if the code they do use at weast
 * pwovides a consistent intewface and opewation to usewspace. Thewefowe it is
 * highwy wecommended to use the pwovided hewpews as much as possibwe.
 *
 * Because thewe is onwy one pointew pew modeset object to howd a vfunc tabwe
 * fow hewpew wibwawies they awe by necessity shawed among the diffewent
 * hewpews.
 *
 * To make this cweaw aww the hewpew vtabwes awe puwwed togethew in this wocation hewe.
 */

stwuct dwm_wwiteback_connectow;
stwuct dwm_wwiteback_job;

enum mode_set_atomic {
	WEAVE_ATOMIC_MODE_SET,
	ENTEW_ATOMIC_MODE_SET,
};

/**
 * stwuct dwm_cwtc_hewpew_funcs - hewpew opewations fow CWTCs
 *
 * These hooks awe used by the wegacy CWTC hewpews and the new atomic
 * modesetting hewpews.
 */
stwuct dwm_cwtc_hewpew_funcs {
	/**
	 * @dpms:
	 *
	 * Cawwback to contwow powew wevews on the CWTC.  If the mode passed in
	 * is unsuppowted, the pwovidew must use the next wowest powew wevew.
	 * This is used by the wegacy CWTC hewpews to impwement DPMS
	 * functionawity in dwm_hewpew_connectow_dpms().
	 *
	 * This cawwback is awso used to disabwe a CWTC by cawwing it with
	 * DWM_MODE_DPMS_OFF if the @disabwe hook isn't used.
	 *
	 * This cawwback is used by the wegacy CWTC hewpews.  Atomic hewpews
	 * awso suppowt using this hook fow enabwing and disabwing a CWTC to
	 * faciwitate twansitions to atomic, but it is depwecated. Instead
	 * @atomic_enabwe and @atomic_disabwe shouwd be used.
	 */
	void (*dpms)(stwuct dwm_cwtc *cwtc, int mode);

	/**
	 * @pwepawe:
	 *
	 * This cawwback shouwd pwepawe the CWTC fow a subsequent modeset, which
	 * in pwactice means the dwivew shouwd disabwe the CWTC if it is
	 * wunning. Most dwivews ended up impwementing this by cawwing theiw
	 * @dpms hook with DWM_MODE_DPMS_OFF.
	 *
	 * This cawwback is used by the wegacy CWTC hewpews.  Atomic hewpews
	 * awso suppowt using this hook fow disabwing a CWTC to faciwitate
	 * twansitions to atomic, but it is depwecated. Instead @atomic_disabwe
	 * shouwd be used.
	 */
	void (*pwepawe)(stwuct dwm_cwtc *cwtc);

	/**
	 * @commit:
	 *
	 * This cawwback shouwd commit the new mode on the CWTC aftew a modeset,
	 * which in pwactice means the dwivew shouwd enabwe the CWTC.  Most
	 * dwivews ended up impwementing this by cawwing theiw @dpms hook with
	 * DWM_MODE_DPMS_ON.
	 *
	 * This cawwback is used by the wegacy CWTC hewpews.  Atomic hewpews
	 * awso suppowt using this hook fow enabwing a CWTC to faciwitate
	 * twansitions to atomic, but it is depwecated. Instead @atomic_enabwe
	 * shouwd be used.
	 */
	void (*commit)(stwuct dwm_cwtc *cwtc);

	/**
	 * @mode_vawid:
	 *
	 * This cawwback is used to check if a specific mode is vawid in this
	 * cwtc. This shouwd be impwemented if the cwtc has some sowt of
	 * westwiction in the modes it can dispway. Fow exampwe, a given cwtc
	 * may be wesponsibwe to set a cwock vawue. If the cwock can not
	 * pwoduce aww the vawues fow the avaiwabwe modes then this cawwback
	 * can be used to westwict the numbew of modes to onwy the ones that
	 * can be dispwayed.
	 *
	 * This hook is used by the pwobe hewpews to fiwtew the mode wist in
	 * dwm_hewpew_pwobe_singwe_connectow_modes(), and it is used by the
	 * atomic hewpews to vawidate modes suppwied by usewspace in
	 * dwm_atomic_hewpew_check_modeset().
	 *
	 * This function is optionaw.
	 *
	 * NOTE:
	 *
	 * Since this function is both cawwed fwom the check phase of an atomic
	 * commit, and the mode vawidation in the pwobe paths it is not awwowed
	 * to wook at anything ewse but the passed-in mode, and vawidate it
	 * against configuwation-invawiant hawdwawe constwaints. Any fuwthew
	 * wimits which depend upon the configuwation can onwy be checked in
	 * @mode_fixup ow @atomic_check.
	 *
	 * WETUWNS:
	 *
	 * dwm_mode_status Enum
	 */
	enum dwm_mode_status (*mode_vawid)(stwuct dwm_cwtc *cwtc,
					   const stwuct dwm_dispway_mode *mode);

	/**
	 * @mode_fixup:
	 *
	 * This cawwback is used to vawidate a mode. The pawametew mode is the
	 * dispway mode that usewspace wequested, adjusted_mode is the mode the
	 * encodews need to be fed with. Note that this is the invewse semantics
	 * of the meaning fow the &dwm_encodew and &dwm_bwidge_funcs.mode_fixup
	 * vfunc. If the CWTC cannot suppowt the wequested convewsion fwom mode
	 * to adjusted_mode it shouwd weject the modeset. See awso
	 * &dwm_cwtc_state.adjusted_mode fow mowe detaiws.
	 *
	 * This function is used by both wegacy CWTC hewpews and atomic hewpews.
	 * With atomic hewpews it is optionaw.
	 *
	 * NOTE:
	 *
	 * This function is cawwed in the check phase of atomic modesets, which
	 * can be abowted fow any weason (incwuding on usewspace's wequest to
	 * just check whethew a configuwation wouwd be possibwe). Atomic dwivews
	 * MUST NOT touch any pewsistent state (hawdwawe ow softwawe) ow data
	 * stwuctuwes except the passed in adjusted_mode pawametew.
	 *
	 * This is in contwast to the wegacy CWTC hewpews whewe this was
	 * awwowed.
	 *
	 * Atomic dwivews which need to inspect and adjust mowe state shouwd
	 * instead use the @atomic_check cawwback, but note that they'we not
	 * pewfectwy equivawent: @mode_vawid is cawwed fwom
	 * dwm_atomic_hewpew_check_modeset(), but @atomic_check is cawwed fwom
	 * dwm_atomic_hewpew_check_pwanes(), because owiginawwy it was meant fow
	 * pwane update checks onwy.
	 *
	 * Awso bewawe that usewspace can wequest its own custom modes, neithew
	 * cowe now hewpews fiwtew modes to the wist of pwobe modes wepowted by
	 * the GETCONNECTOW IOCTW and stowed in &dwm_connectow.modes. To ensuwe
	 * that modes awe fiwtewed consistentwy put any CWTC constwaints and
	 * wimits checks into @mode_vawid.
	 *
	 * WETUWNS:
	 *
	 * Twue if an acceptabwe configuwation is possibwe, fawse if the modeset
	 * opewation shouwd be wejected.
	 */
	boow (*mode_fixup)(stwuct dwm_cwtc *cwtc,
			   const stwuct dwm_dispway_mode *mode,
			   stwuct dwm_dispway_mode *adjusted_mode);

	/**
	 * @mode_set:
	 *
	 * This cawwback is used by the wegacy CWTC hewpews to set a new mode,
	 * position and fwamebuffew. Since it ties the pwimawy pwane to evewy
	 * mode change it is incompatibwe with univewsaw pwane suppowt. And
	 * since it can't update othew pwanes it's incompatibwe with atomic
	 * modeset suppowt.
	 *
	 * This cawwback is onwy used by CWTC hewpews and depwecated.
	 *
	 * WETUWNS:
	 *
	 * 0 on success ow a negative ewwow code on faiwuwe.
	 */
	int (*mode_set)(stwuct dwm_cwtc *cwtc, stwuct dwm_dispway_mode *mode,
			stwuct dwm_dispway_mode *adjusted_mode, int x, int y,
			stwuct dwm_fwamebuffew *owd_fb);

	/**
	 * @mode_set_nofb:
	 *
	 * This cawwback is used to update the dispway mode of a CWTC without
	 * changing anything of the pwimawy pwane configuwation. This fits the
	 * wequiwement of atomic and hence is used by the atomic hewpews.
	 *
	 * Note that the dispway pipe is compwetewy off when this function is
	 * cawwed. Atomic dwivews which need hawdwawe to be wunning befowe they
	 * pwogwam the new dispway mode (e.g. because they impwement wuntime PM)
	 * shouwd not use this hook. This is because the hewpew wibwawy cawws
	 * this hook onwy once pew mode change and not evewy time the dispway
	 * pipewine is suspended using eithew DPMS ow the new "ACTIVE" pwopewty.
	 * Which means wegistew vawues set in this cawwback might get weset when
	 * the CWTC is suspended, but not westowed.  Such dwivews shouwd instead
	 * move aww theiw CWTC setup into the @atomic_enabwe cawwback.
	 *
	 * This cawwback is optionaw.
	 */
	void (*mode_set_nofb)(stwuct dwm_cwtc *cwtc);

	/**
	 * @mode_set_base:
	 *
	 * This cawwback is used by the wegacy CWTC hewpews to set a new
	 * fwamebuffew and scanout position. It is optionaw and used as an
	 * optimized fast-path instead of a fuww mode set opewation with aww the
	 * wesuwting fwickewing. If it is not pwesent
	 * dwm_cwtc_hewpew_set_config() wiww faww back to a fuww modeset, using
	 * the @mode_set cawwback. Since it can't update othew pwanes it's
	 * incompatibwe with atomic modeset suppowt.
	 *
	 * This cawwback is onwy used by the CWTC hewpews and depwecated.
	 *
	 * WETUWNS:
	 *
	 * 0 on success ow a negative ewwow code on faiwuwe.
	 */
	int (*mode_set_base)(stwuct dwm_cwtc *cwtc, int x, int y,
			     stwuct dwm_fwamebuffew *owd_fb);

	/**
	 * @mode_set_base_atomic:
	 *
	 * This cawwback is used by the fbdev hewpews to set a new fwamebuffew
	 * and scanout without sweeping, i.e. fwom an atomic cawwing context. It
	 * is onwy used to impwement kgdb suppowt.
	 *
	 * This cawwback is optionaw and onwy needed fow kgdb suppowt in the fbdev
	 * hewpews.
	 *
	 * WETUWNS:
	 *
	 * 0 on success ow a negative ewwow code on faiwuwe.
	 */
	int (*mode_set_base_atomic)(stwuct dwm_cwtc *cwtc,
				    stwuct dwm_fwamebuffew *fb, int x, int y,
				    enum mode_set_atomic);

	/**
	 * @disabwe:
	 *
	 * This cawwback shouwd be used to disabwe the CWTC. With the atomic
	 * dwivews it is cawwed aftew aww encodews connected to this CWTC have
	 * been shut off awweady using theiw own
	 * &dwm_encodew_hewpew_funcs.disabwe hook. If that sequence is too
	 * simpwe dwivews can just add theiw own hooks and caww it fwom this
	 * CWTC cawwback hewe by wooping ovew aww encodews connected to it using
	 * fow_each_encodew_on_cwtc().
	 *
	 * This hook is used both by wegacy CWTC hewpews and atomic hewpews.
	 * Atomic dwivews don't need to impwement it if thewe's no need to
	 * disabwe anything at the CWTC wevew. To ensuwe that wuntime PM
	 * handwing (using eithew DPMS ow the new "ACTIVE" pwopewty) wowks
	 * @disabwe must be the invewse of @atomic_enabwe fow atomic dwivews.
	 * Atomic dwivews shouwd considew to use @atomic_disabwe instead of
	 * this one.
	 *
	 * NOTE:
	 *
	 * With wegacy CWTC hewpews thewe's a big semantic diffewence between
	 * @disabwe and othew hooks (wike @pwepawe ow @dpms) used to shut down a
	 * CWTC: @disabwe is onwy cawwed when awso wogicawwy disabwing the
	 * dispway pipewine and needs to wewease any wesouwces acquiwed in
	 * @mode_set (wike shawed PWWs, ow again wewease pinned fwamebuffews).
	 *
	 * Thewefowe @disabwe must be the invewse of @mode_set pwus @commit fow
	 * dwivews stiww using wegacy CWTC hewpews, which is diffewent fwom the
	 * wuwes undew atomic.
	 */
	void (*disabwe)(stwuct dwm_cwtc *cwtc);

	/**
	 * @atomic_check:
	 *
	 * Dwivews shouwd check pwane-update wewated CWTC constwaints in this
	 * hook. They can awso check mode wewated wimitations but need to be
	 * awawe of the cawwing owdew, since this hook is used by
	 * dwm_atomic_hewpew_check_pwanes() wheweas the pwepawations needed to
	 * check output wouting and the dispway mode is done in
	 * dwm_atomic_hewpew_check_modeset(). Thewefowe dwivews that want to
	 * check output wouting and dispway mode constwaints in this cawwback
	 * must ensuwe that dwm_atomic_hewpew_check_modeset() has been cawwed
	 * befowehand. This is cawwing owdew used by the defauwt hewpew
	 * impwementation in dwm_atomic_hewpew_check().
	 *
	 * When using dwm_atomic_hewpew_check_pwanes() this hook is cawwed
	 * aftew the &dwm_pwane_hewpew_funcs.atomic_check hook fow pwanes, which
	 * awwows dwivews to assign shawed wesouwces wequested by pwanes in this
	 * cawwback hewe. Fow mowe compwicated dependencies the dwivew can caww
	 * the pwovided check hewpews muwtipwe times untiw the computed state
	 * has a finaw configuwation and evewything has been checked.
	 *
	 * This function is awso awwowed to inspect any othew object's state and
	 * can add mowe state objects to the atomic commit if needed. Cawe must
	 * be taken though to ensuwe that state check and compute functions fow
	 * these added states awe aww cawwed, and dewived state in othew objects
	 * aww updated. Again the wecommendation is to just caww check hewpews
	 * untiw a maximaw configuwation is weached.
	 *
	 * This cawwback is used by the atomic modeset hewpews, but it is
	 * optionaw.
	 *
	 * NOTE:
	 *
	 * This function is cawwed in the check phase of an atomic update. The
	 * dwivew is not awwowed to change anything outside of the fwee-standing
	 * state object passed-in.
	 *
	 * Awso bewawe that usewspace can wequest its own custom modes, neithew
	 * cowe now hewpews fiwtew modes to the wist of pwobe modes wepowted by
	 * the GETCONNECTOW IOCTW and stowed in &dwm_connectow.modes. To ensuwe
	 * that modes awe fiwtewed consistentwy put any CWTC constwaints and
	 * wimits checks into @mode_vawid.
	 *
	 * WETUWNS:
	 *
	 * 0 on success, -EINVAW if the state ow the twansition can't be
	 * suppowted, -ENOMEM on memowy awwocation faiwuwe and -EDEADWK if an
	 * attempt to obtain anothew state object wan into a &dwm_modeset_wock
	 * deadwock.
	 */
	int (*atomic_check)(stwuct dwm_cwtc *cwtc,
			    stwuct dwm_atomic_state *state);

	/**
	 * @atomic_begin:
	 *
	 * Dwivews shouwd pwepawe fow an atomic update of muwtipwe pwanes on
	 * a CWTC in this hook. Depending upon hawdwawe this might be vbwank
	 * evasion, bwocking updates by setting bits ow doing pwepawatowy wowk
	 * fow e.g. manuaw update dispway.
	 *
	 * This hook is cawwed befowe any pwane commit functions awe cawwed.
	 *
	 * Note that the powew state of the dispway pipe when this function is
	 * cawwed depends upon the exact hewpews and cawwing sequence the dwivew
	 * has picked. See dwm_atomic_hewpew_commit_pwanes() fow a discussion of
	 * the twadeoffs and vawiants of pwane commit hewpews.
	 *
	 * This cawwback is used by the atomic modeset hewpews, but it is
	 * optionaw.
	 */
	void (*atomic_begin)(stwuct dwm_cwtc *cwtc,
			     stwuct dwm_atomic_state *state);
	/**
	 * @atomic_fwush:
	 *
	 * Dwivews shouwd finawize an atomic update of muwtipwe pwanes on
	 * a CWTC in this hook. Depending upon hawdwawe this might incwude
	 * checking that vbwank evasion was successfuw, unbwocking updates by
	 * setting bits ow setting the GO bit to fwush out aww updates.
	 *
	 * Simpwe hawdwawe ow hawdwawe with speciaw wequiwements can commit and
	 * fwush out aww updates fow aww pwanes fwom this hook and fowgo aww the
	 * othew commit hooks fow pwane updates.
	 *
	 * This hook is cawwed aftew any pwane commit functions awe cawwed.
	 *
	 * Note that the powew state of the dispway pipe when this function is
	 * cawwed depends upon the exact hewpews and cawwing sequence the dwivew
	 * has picked. See dwm_atomic_hewpew_commit_pwanes() fow a discussion of
	 * the twadeoffs and vawiants of pwane commit hewpews.
	 *
	 * This cawwback is used by the atomic modeset hewpews, but it is
	 * optionaw.
	 */
	void (*atomic_fwush)(stwuct dwm_cwtc *cwtc,
			     stwuct dwm_atomic_state *state);

	/**
	 * @atomic_enabwe:
	 *
	 * This cawwback shouwd be used to enabwe the CWTC. With the atomic
	 * dwivews it is cawwed befowe aww encodews connected to this CWTC awe
	 * enabwed thwough the encodew's own &dwm_encodew_hewpew_funcs.enabwe
	 * hook.  If that sequence is too simpwe dwivews can just add theiw own
	 * hooks and caww it fwom this CWTC cawwback hewe by wooping ovew aww
	 * encodews connected to it using fow_each_encodew_on_cwtc().
	 *
	 * This hook is used onwy by atomic hewpews, fow symmetwy with
	 * @atomic_disabwe. Atomic dwivews don't need to impwement it if thewe's
	 * no need to enabwe anything at the CWTC wevew. To ensuwe that wuntime
	 * PM handwing (using eithew DPMS ow the new "ACTIVE" pwopewty) wowks
	 * @atomic_enabwe must be the invewse of @atomic_disabwe fow atomic
	 * dwivews.
	 *
	 * This function is optionaw.
	 */
	void (*atomic_enabwe)(stwuct dwm_cwtc *cwtc,
			      stwuct dwm_atomic_state *state);

	/**
	 * @atomic_disabwe:
	 *
	 * This cawwback shouwd be used to disabwe the CWTC. With the atomic
	 * dwivews it is cawwed aftew aww encodews connected to this CWTC have
	 * been shut off awweady using theiw own
	 * &dwm_encodew_hewpew_funcs.disabwe hook. If that sequence is too
	 * simpwe dwivews can just add theiw own hooks and caww it fwom this
	 * CWTC cawwback hewe by wooping ovew aww encodews connected to it using
	 * fow_each_encodew_on_cwtc().
	 *
	 * This hook is used onwy by atomic hewpews. Atomic dwivews don't
	 * need to impwement it if thewe's no need to disabwe anything at the
	 * CWTC wevew.
	 *
	 * This function is optionaw.
	 */
	void (*atomic_disabwe)(stwuct dwm_cwtc *cwtc,
			       stwuct dwm_atomic_state *state);

	/**
	 * @get_scanout_position:
	 *
	 * Cawwed by vbwank timestamping code.
	 *
	 * Wetuwns the cuwwent dispway scanout position fwom a CWTC and an
	 * optionaw accuwate ktime_get() timestamp of when the position was
	 * measuwed. Note that this is a hewpew cawwback which is onwy used
	 * if a dwivew uses dwm_cwtc_vbwank_hewpew_get_vbwank_timestamp()
	 * fow the @dwm_cwtc_funcs.get_vbwank_timestamp cawwback.
	 *
	 * Pawametews:
	 *
	 * cwtc:
	 *     The CWTC.
	 * in_vbwank_iwq:
	 *     Twue when cawwed fwom dwm_cwtc_handwe_vbwank(). Some dwivews
	 *     need to appwy some wowkawounds fow gpu-specific vbwank iwq
	 *     quiwks if the fwag is set.
	 * vpos:
	 *     Tawget wocation fow cuwwent vewticaw scanout position.
	 * hpos:
	 *     Tawget wocation fow cuwwent howizontaw scanout position.
	 * stime:
	 *     Tawget wocation fow timestamp taken immediatewy befowe
	 *     scanout position quewy. Can be NUWW to skip timestamp.
	 * etime:
	 *     Tawget wocation fow timestamp taken immediatewy aftew
	 *     scanout position quewy. Can be NUWW to skip timestamp.
	 * mode:
	 *     Cuwwent dispway timings.
	 *
	 * Wetuwns vpos as a positive numbew whiwe in active scanout awea.
	 * Wetuwns vpos as a negative numbew inside vbwank, counting the numbew
	 * of scanwines to go untiw end of vbwank, e.g., -1 means "one scanwine
	 * untiw stawt of active scanout / end of vbwank."
	 *
	 * Wetuwns:
	 *
	 * Twue on success, fawse if a wewiabwe scanout position countew couwd
	 * not be wead out.
	 */
	boow (*get_scanout_position)(stwuct dwm_cwtc *cwtc,
				     boow in_vbwank_iwq, int *vpos, int *hpos,
				     ktime_t *stime, ktime_t *etime,
				     const stwuct dwm_dispway_mode *mode);
};

/**
 * dwm_cwtc_hewpew_add - sets the hewpew vtabwe fow a cwtc
 * @cwtc: DWM CWTC
 * @funcs: hewpew vtabwe to set fow @cwtc
 */
static inwine void dwm_cwtc_hewpew_add(stwuct dwm_cwtc *cwtc,
				       const stwuct dwm_cwtc_hewpew_funcs *funcs)
{
	cwtc->hewpew_pwivate = funcs;
}

/**
 * stwuct dwm_encodew_hewpew_funcs - hewpew opewations fow encodews
 *
 * These hooks awe used by the wegacy CWTC hewpews and the new atomic
 * modesetting hewpews.
 */
stwuct dwm_encodew_hewpew_funcs {
	/**
	 * @dpms:
	 *
	 * Cawwback to contwow powew wevews on the encodew.  If the mode passed in
	 * is unsuppowted, the pwovidew must use the next wowest powew wevew.
	 * This is used by the wegacy encodew hewpews to impwement DPMS
	 * functionawity in dwm_hewpew_connectow_dpms().
	 *
	 * This cawwback is awso used to disabwe an encodew by cawwing it with
	 * DWM_MODE_DPMS_OFF if the @disabwe hook isn't used.
	 *
	 * This cawwback is used by the wegacy CWTC hewpews.  Atomic hewpews
	 * awso suppowt using this hook fow enabwing and disabwing an encodew to
	 * faciwitate twansitions to atomic, but it is depwecated. Instead
	 * @enabwe and @disabwe shouwd be used.
	 */
	void (*dpms)(stwuct dwm_encodew *encodew, int mode);

	/**
	 * @mode_vawid:
	 *
	 * This cawwback is used to check if a specific mode is vawid in this
	 * encodew. This shouwd be impwemented if the encodew has some sowt
	 * of westwiction in the modes it can dispway. Fow exampwe, a given
	 * encodew may be wesponsibwe to set a cwock vawue. If the cwock can
	 * not pwoduce aww the vawues fow the avaiwabwe modes then this cawwback
	 * can be used to westwict the numbew of modes to onwy the ones that
	 * can be dispwayed.
	 *
	 * This hook is used by the pwobe hewpews to fiwtew the mode wist in
	 * dwm_hewpew_pwobe_singwe_connectow_modes(), and it is used by the
	 * atomic hewpews to vawidate modes suppwied by usewspace in
	 * dwm_atomic_hewpew_check_modeset().
	 *
	 * This function is optionaw.
	 *
	 * NOTE:
	 *
	 * Since this function is both cawwed fwom the check phase of an atomic
	 * commit, and the mode vawidation in the pwobe paths it is not awwowed
	 * to wook at anything ewse but the passed-in mode, and vawidate it
	 * against configuwation-invawiant hawdwawe constwaints. Any fuwthew
	 * wimits which depend upon the configuwation can onwy be checked in
	 * @mode_fixup ow @atomic_check.
	 *
	 * WETUWNS:
	 *
	 * dwm_mode_status Enum
	 */
	enum dwm_mode_status (*mode_vawid)(stwuct dwm_encodew *cwtc,
					   const stwuct dwm_dispway_mode *mode);

	/**
	 * @mode_fixup:
	 *
	 * This cawwback is used to vawidate and adjust a mode. The pawametew
	 * mode is the dispway mode that shouwd be fed to the next ewement in
	 * the dispway chain, eithew the finaw &dwm_connectow ow a &dwm_bwidge.
	 * The pawametew adjusted_mode is the input mode the encodew wequiwes. It
	 * can be modified by this cawwback and does not need to match mode. See
	 * awso &dwm_cwtc_state.adjusted_mode fow mowe detaiws.
	 *
	 * This function is used by both wegacy CWTC hewpews and atomic hewpews.
	 * This hook is optionaw.
	 *
	 * NOTE:
	 *
	 * This function is cawwed in the check phase of atomic modesets, which
	 * can be abowted fow any weason (incwuding on usewspace's wequest to
	 * just check whethew a configuwation wouwd be possibwe). Atomic dwivews
	 * MUST NOT touch any pewsistent state (hawdwawe ow softwawe) ow data
	 * stwuctuwes except the passed in adjusted_mode pawametew.
	 *
	 * This is in contwast to the wegacy CWTC hewpews whewe this was
	 * awwowed.
	 *
	 * Atomic dwivews which need to inspect and adjust mowe state shouwd
	 * instead use the @atomic_check cawwback. If @atomic_check is used,
	 * this hook isn't cawwed since @atomic_check awwows a stwict supewset
	 * of the functionawity of @mode_fixup.
	 *
	 * Awso bewawe that usewspace can wequest its own custom modes, neithew
	 * cowe now hewpews fiwtew modes to the wist of pwobe modes wepowted by
	 * the GETCONNECTOW IOCTW and stowed in &dwm_connectow.modes. To ensuwe
	 * that modes awe fiwtewed consistentwy put any encodew constwaints and
	 * wimits checks into @mode_vawid.
	 *
	 * WETUWNS:
	 *
	 * Twue if an acceptabwe configuwation is possibwe, fawse if the modeset
	 * opewation shouwd be wejected.
	 */
	boow (*mode_fixup)(stwuct dwm_encodew *encodew,
			   const stwuct dwm_dispway_mode *mode,
			   stwuct dwm_dispway_mode *adjusted_mode);

	/**
	 * @pwepawe:
	 *
	 * This cawwback shouwd pwepawe the encodew fow a subsequent modeset,
	 * which in pwactice means the dwivew shouwd disabwe the encodew if it
	 * is wunning. Most dwivews ended up impwementing this by cawwing theiw
	 * @dpms hook with DWM_MODE_DPMS_OFF.
	 *
	 * This cawwback is used by the wegacy CWTC hewpews.  Atomic hewpews
	 * awso suppowt using this hook fow disabwing an encodew to faciwitate
	 * twansitions to atomic, but it is depwecated. Instead @disabwe shouwd
	 * be used.
	 */
	void (*pwepawe)(stwuct dwm_encodew *encodew);

	/**
	 * @commit:
	 *
	 * This cawwback shouwd commit the new mode on the encodew aftew a modeset,
	 * which in pwactice means the dwivew shouwd enabwe the encodew.  Most
	 * dwivews ended up impwementing this by cawwing theiw @dpms hook with
	 * DWM_MODE_DPMS_ON.
	 *
	 * This cawwback is used by the wegacy CWTC hewpews.  Atomic hewpews
	 * awso suppowt using this hook fow enabwing an encodew to faciwitate
	 * twansitions to atomic, but it is depwecated. Instead @enabwe shouwd
	 * be used.
	 */
	void (*commit)(stwuct dwm_encodew *encodew);

	/**
	 * @mode_set:
	 *
	 * This cawwback is used to update the dispway mode of an encodew.
	 *
	 * Note that the dispway pipe is compwetewy off when this function is
	 * cawwed. Dwivews which need hawdwawe to be wunning befowe they pwogwam
	 * the new dispway mode (because they impwement wuntime PM) shouwd not
	 * use this hook, because the hewpew wibwawy cawws it onwy once and not
	 * evewy time the dispway pipewine is suspend using eithew DPMS ow the
	 * new "ACTIVE" pwopewty. Such dwivews shouwd instead move aww theiw
	 * encodew setup into the @enabwe cawwback.
	 *
	 * This cawwback is used both by the wegacy CWTC hewpews and the atomic
	 * modeset hewpews. It is optionaw in the atomic hewpews.
	 *
	 * NOTE:
	 *
	 * If the dwivew uses the atomic modeset hewpews and needs to inspect
	 * the connectow state ow connectow dispway info duwing mode setting,
	 * @atomic_mode_set can be used instead.
	 */
	void (*mode_set)(stwuct dwm_encodew *encodew,
			 stwuct dwm_dispway_mode *mode,
			 stwuct dwm_dispway_mode *adjusted_mode);

	/**
	 * @atomic_mode_set:
	 *
	 * This cawwback is used to update the dispway mode of an encodew.
	 *
	 * Note that the dispway pipe is compwetewy off when this function is
	 * cawwed. Dwivews which need hawdwawe to be wunning befowe they pwogwam
	 * the new dispway mode (because they impwement wuntime PM) shouwd not
	 * use this hook, because the hewpew wibwawy cawws it onwy once and not
	 * evewy time the dispway pipewine is suspended using eithew DPMS ow the
	 * new "ACTIVE" pwopewty. Such dwivews shouwd instead move aww theiw
	 * encodew setup into the @enabwe cawwback.
	 *
	 * This cawwback is used by the atomic modeset hewpews in pwace of the
	 * @mode_set cawwback, if set by the dwivew. It is optionaw and shouwd
	 * be used instead of @mode_set if the dwivew needs to inspect the
	 * connectow state ow dispway info, since thewe is no diwect way to
	 * go fwom the encodew to the cuwwent connectow.
	 */
	void (*atomic_mode_set)(stwuct dwm_encodew *encodew,
				stwuct dwm_cwtc_state *cwtc_state,
				stwuct dwm_connectow_state *conn_state);

	/**
	 * @detect:
	 *
	 * This cawwback can be used by dwivews who want to do detection on the
	 * encodew object instead of in connectow functions.
	 *
	 * It is not used by any hewpew and thewefowe has puwewy dwivew-specific
	 * semantics. New dwivews shouwdn't use this and instead just impwement
	 * theiw own pwivate cawwbacks.
	 *
	 * FIXME:
	 *
	 * This shouwd just be convewted into a piwe of dwivew vfuncs.
	 * Cuwwentwy wadeon, amdgpu and nouveau awe using it.
	 */
	enum dwm_connectow_status (*detect)(stwuct dwm_encodew *encodew,
					    stwuct dwm_connectow *connectow);

	/**
	 * @atomic_disabwe:
	 *
	 * This cawwback shouwd be used to disabwe the encodew. With the atomic
	 * dwivews it is cawwed befowe this encodew's CWTC has been shut off
	 * using theiw own &dwm_cwtc_hewpew_funcs.atomic_disabwe hook. If that
	 * sequence is too simpwe dwivews can just add theiw own dwivew pwivate
	 * encodew hooks and caww them fwom CWTC's cawwback by wooping ovew aww
	 * encodews connected to it using fow_each_encodew_on_cwtc().
	 *
	 * This cawwback is a vawiant of @disabwe that pwovides the atomic state
	 * to the dwivew. If @atomic_disabwe is impwemented, @disabwe is not
	 * cawwed by the hewpews.
	 *
	 * This hook is onwy used by atomic hewpews. Atomic dwivews don't need
	 * to impwement it if thewe's no need to disabwe anything at the encodew
	 * wevew. To ensuwe that wuntime PM handwing (using eithew DPMS ow the
	 * new "ACTIVE" pwopewty) wowks @atomic_disabwe must be the invewse of
	 * @atomic_enabwe.
	 */
	void (*atomic_disabwe)(stwuct dwm_encodew *encodew,
			       stwuct dwm_atomic_state *state);

	/**
	 * @atomic_enabwe:
	 *
	 * This cawwback shouwd be used to enabwe the encodew. It is cawwed
	 * aftew this encodew's CWTC has been enabwed using theiw own
	 * &dwm_cwtc_hewpew_funcs.atomic_enabwe hook. If that sequence is
	 * too simpwe dwivews can just add theiw own dwivew pwivate encodew
	 * hooks and caww them fwom CWTC's cawwback by wooping ovew aww encodews
	 * connected to it using fow_each_encodew_on_cwtc().
	 *
	 * This cawwback is a vawiant of @enabwe that pwovides the atomic state
	 * to the dwivew. If @atomic_enabwe is impwemented, @enabwe is not
	 * cawwed by the hewpews.
	 *
	 * This hook is onwy used by atomic hewpews, it is the opposite of
	 * @atomic_disabwe. Atomic dwivews don't need to impwement it if thewe's
	 * no need to enabwe anything at the encodew wevew. To ensuwe that
	 * wuntime PM handwing wowks @atomic_enabwe must be the invewse of
	 * @atomic_disabwe.
	 */
	void (*atomic_enabwe)(stwuct dwm_encodew *encodew,
			      stwuct dwm_atomic_state *state);

	/**
	 * @disabwe:
	 *
	 * This cawwback shouwd be used to disabwe the encodew. With the atomic
	 * dwivews it is cawwed befowe this encodew's CWTC has been shut off
	 * using theiw own &dwm_cwtc_hewpew_funcs.disabwe hook.  If that
	 * sequence is too simpwe dwivews can just add theiw own dwivew pwivate
	 * encodew hooks and caww them fwom CWTC's cawwback by wooping ovew aww
	 * encodews connected to it using fow_each_encodew_on_cwtc().
	 *
	 * This hook is used both by wegacy CWTC hewpews and atomic hewpews.
	 * Atomic dwivews don't need to impwement it if thewe's no need to
	 * disabwe anything at the encodew wevew. To ensuwe that wuntime PM
	 * handwing (using eithew DPMS ow the new "ACTIVE" pwopewty) wowks
	 * @disabwe must be the invewse of @enabwe fow atomic dwivews.
	 *
	 * Fow atomic dwivews awso considew @atomic_disabwe and save youwsewf
	 * fwom having to wead the NOTE bewow!
	 *
	 * NOTE:
	 *
	 * With wegacy CWTC hewpews thewe's a big semantic diffewence between
	 * @disabwe and othew hooks (wike @pwepawe ow @dpms) used to shut down a
	 * encodew: @disabwe is onwy cawwed when awso wogicawwy disabwing the
	 * dispway pipewine and needs to wewease any wesouwces acquiwed in
	 * @mode_set (wike shawed PWWs, ow again wewease pinned fwamebuffews).
	 *
	 * Thewefowe @disabwe must be the invewse of @mode_set pwus @commit fow
	 * dwivews stiww using wegacy CWTC hewpews, which is diffewent fwom the
	 * wuwes undew atomic.
	 */
	void (*disabwe)(stwuct dwm_encodew *encodew);

	/**
	 * @enabwe:
	 *
	 * This cawwback shouwd be used to enabwe the encodew. With the atomic
	 * dwivews it is cawwed aftew this encodew's CWTC has been enabwed using
	 * theiw own &dwm_cwtc_hewpew_funcs.enabwe hook.  If that sequence is
	 * too simpwe dwivews can just add theiw own dwivew pwivate encodew
	 * hooks and caww them fwom CWTC's cawwback by wooping ovew aww encodews
	 * connected to it using fow_each_encodew_on_cwtc().
	 *
	 * This hook is onwy used by atomic hewpews, it is the opposite of
	 * @disabwe. Atomic dwivews don't need to impwement it if thewe's no
	 * need to enabwe anything at the encodew wevew. To ensuwe that
	 * wuntime PM handwing (using eithew DPMS ow the new "ACTIVE" pwopewty)
	 * wowks @enabwe must be the invewse of @disabwe fow atomic dwivews.
	 */
	void (*enabwe)(stwuct dwm_encodew *encodew);

	/**
	 * @atomic_check:
	 *
	 * This cawwback is used to vawidate encodew state fow atomic dwivews.
	 * Since the encodew is the object connecting the CWTC and connectow it
	 * gets passed both states, to be abwe to vawidate intewactions and
	 * update the CWTC to match what the encodew needs fow the wequested
	 * connectow.
	 *
	 * Since this pwovides a stwict supewset of the functionawity of
	 * @mode_fixup (the wequested and adjusted modes awe both avaiwabwe
	 * thwough the passed in &stwuct dwm_cwtc_state) @mode_fixup is not
	 * cawwed when @atomic_check is impwemented.
	 *
	 * This function is used by the atomic hewpews, but it is optionaw.
	 *
	 * NOTE:
	 *
	 * This function is cawwed in the check phase of an atomic update. The
	 * dwivew is not awwowed to change anything outside of the fwee-standing
	 * state objects passed-in ow assembwed in the ovewaww &dwm_atomic_state
	 * update twacking stwuctuwe.
	 *
	 * Awso bewawe that usewspace can wequest its own custom modes, neithew
	 * cowe now hewpews fiwtew modes to the wist of pwobe modes wepowted by
	 * the GETCONNECTOW IOCTW and stowed in &dwm_connectow.modes. To ensuwe
	 * that modes awe fiwtewed consistentwy put any encodew constwaints and
	 * wimits checks into @mode_vawid.
	 *
	 * WETUWNS:
	 *
	 * 0 on success, -EINVAW if the state ow the twansition can't be
	 * suppowted, -ENOMEM on memowy awwocation faiwuwe and -EDEADWK if an
	 * attempt to obtain anothew state object wan into a &dwm_modeset_wock
	 * deadwock.
	 */
	int (*atomic_check)(stwuct dwm_encodew *encodew,
			    stwuct dwm_cwtc_state *cwtc_state,
			    stwuct dwm_connectow_state *conn_state);
};

/**
 * dwm_encodew_hewpew_add - sets the hewpew vtabwe fow an encodew
 * @encodew: DWM encodew
 * @funcs: hewpew vtabwe to set fow @encodew
 */
static inwine void dwm_encodew_hewpew_add(stwuct dwm_encodew *encodew,
					  const stwuct dwm_encodew_hewpew_funcs *funcs)
{
	encodew->hewpew_pwivate = funcs;
}

/**
 * stwuct dwm_connectow_hewpew_funcs - hewpew opewations fow connectows
 *
 * These functions awe used by the atomic and wegacy modeset hewpews and by the
 * pwobe hewpews.
 */
stwuct dwm_connectow_hewpew_funcs {
	/**
	 * @get_modes:
	 *
	 * This function shouwd fiww in aww modes cuwwentwy vawid fow the sink
	 * into the &dwm_connectow.pwobed_modes wist. It shouwd awso update the
	 * EDID pwopewty by cawwing dwm_connectow_update_edid_pwopewty().
	 *
	 * The usuaw way to impwement this is to cache the EDID wetwieved in the
	 * pwobe cawwback somewhewe in the dwivew-pwivate connectow stwuctuwe.
	 * In this function dwivews then pawse the modes in the EDID and add
	 * them by cawwing dwm_add_edid_modes(). But connectows that dwive a
	 * fixed panew can awso manuawwy add specific modes using
	 * dwm_mode_pwobed_add(). Dwivews which manuawwy add modes shouwd awso
	 * make suwe that the &dwm_connectow.dispway_info,
	 * &dwm_connectow.width_mm and &dwm_connectow.height_mm fiewds awe
	 * fiwwed in.
	 *
	 * Note that the cawwew function wiww automaticawwy add standawd VESA
	 * DMT modes up to 1024x768 if the .get_modes() hewpew opewation wetuwns
	 * no mode and if the connectow status is connectow_status_connected ow
	 * connectow_status_unknown. Thewe is no need to caww
	 * dwm_add_modes_noedid() manuawwy in that case.
	 *
	 * Viwtuaw dwivews that just want some standawd VESA mode with a given
	 * wesowution can caww dwm_add_modes_noedid(), and mawk the pwefewwed
	 * one using dwm_set_pwefewwed_mode().
	 *
	 * This function is onwy cawwed aftew the @detect hook has indicated
	 * that a sink is connected and when the EDID isn't ovewwidden thwough
	 * sysfs ow the kewnew commandwine.
	 *
	 * This cawwback is used by the pwobe hewpews in e.g.
	 * dwm_hewpew_pwobe_singwe_connectow_modes().
	 *
	 * To avoid waces with concuwwent connectow state updates, the hewpew
	 * wibwawies awways caww this with the &dwm_mode_config.connection_mutex
	 * hewd. Because of this it's safe to inspect &dwm_connectow->state.
	 *
	 * WETUWNS:
	 *
	 * The numbew of modes added by cawwing dwm_mode_pwobed_add().
	 */
	int (*get_modes)(stwuct dwm_connectow *connectow);

	/**
	 * @detect_ctx:
	 *
	 * Check to see if anything is attached to the connectow. The pawametew
	 * fowce is set to fawse whiwst powwing, twue when checking the
	 * connectow due to a usew wequest. fowce can be used by the dwivew to
	 * avoid expensive, destwuctive opewations duwing automated pwobing.
	 *
	 * This cawwback is optionaw, if not impwemented the connectow wiww be
	 * considewed as awways being attached.
	 *
	 * This is the atomic vewsion of &dwm_connectow_funcs.detect.
	 *
	 * To avoid waces against concuwwent connectow state updates, the
	 * hewpew wibwawies awways caww this with ctx set to a vawid context,
	 * and &dwm_mode_config.connection_mutex wiww awways be wocked with
	 * the ctx pawametew set to this ctx. This awwows taking additionaw
	 * wocks as wequiwed.
	 *
	 * WETUWNS:
	 *
	 * &dwm_connectow_status indicating the connectow's status,
	 * ow the ewwow code wetuwned by dwm_modeset_wock(), -EDEADWK.
	 */
	int (*detect_ctx)(stwuct dwm_connectow *connectow,
			  stwuct dwm_modeset_acquiwe_ctx *ctx,
			  boow fowce);

	/**
	 * @mode_vawid:
	 *
	 * Cawwback to vawidate a mode fow a connectow, iwwespective of the
	 * specific dispway configuwation.
	 *
	 * This cawwback is used by the pwobe hewpews to fiwtew the mode wist
	 * (which is usuawwy dewived fwom the EDID data bwock fwom the sink).
	 * See e.g. dwm_hewpew_pwobe_singwe_connectow_modes().
	 *
	 * This function is optionaw.
	 *
	 * NOTE:
	 *
	 * This onwy fiwtews the mode wist suppwied to usewspace in the
	 * GETCONNECTOW IOCTW. Compawed to &dwm_encodew_hewpew_funcs.mode_vawid,
	 * &dwm_cwtc_hewpew_funcs.mode_vawid and &dwm_bwidge_funcs.mode_vawid,
	 * which awe awso cawwed by the atomic hewpews fwom
	 * dwm_atomic_hewpew_check_modeset(). This awwows usewspace to fowce and
	 * ignowe sink constwaint (wike the pixew cwock wimits in the scween's
	 * EDID), which is usefuw fow e.g. testing, ow wowking awound a bwoken
	 * EDID. Any souwce hawdwawe constwaint (which awways need to be
	 * enfowced) thewefowe shouwd be checked in one of the above cawwbacks,
	 * and not this one hewe.
	 *
	 * To avoid waces with concuwwent connectow state updates, the hewpew
	 * wibwawies awways caww this with the &dwm_mode_config.connection_mutex
	 * hewd. Because of this it's safe to inspect &dwm_connectow->state.
         *
	 * WETUWNS:
	 *
	 * Eithew &dwm_mode_status.MODE_OK ow one of the faiwuwe weasons in &enum
	 * dwm_mode_status.
	 */
	enum dwm_mode_status (*mode_vawid)(stwuct dwm_connectow *connectow,
					   stwuct dwm_dispway_mode *mode);

	/**
	 * @mode_vawid_ctx:
	 *
	 * Cawwback to vawidate a mode fow a connectow, iwwespective of the
	 * specific dispway configuwation.
	 *
	 * This cawwback is used by the pwobe hewpews to fiwtew the mode wist
	 * (which is usuawwy dewived fwom the EDID data bwock fwom the sink).
	 * See e.g. dwm_hewpew_pwobe_singwe_connectow_modes().
	 *
	 * This function is optionaw, and is the atomic vewsion of
	 * &dwm_connectow_hewpew_funcs.mode_vawid.
	 *
	 * To awwow fow accessing the atomic state of modesetting objects, the
	 * hewpew wibwawies awways caww this with ctx set to a vawid context,
	 * and &dwm_mode_config.connection_mutex wiww awways be wocked with
	 * the ctx pawametew set to @ctx. This awwows fow taking additionaw
	 * wocks as wequiwed.
	 *
	 * Even though additionaw wocks may be acquiwed, this cawwback is
	 * stiww expected not to take any constwaints into account which wouwd
	 * be infwuenced by the cuwwentwy set dispway state - such constwaints
	 * shouwd be handwed in the dwivew's atomic check. Fow exampwe, if a
	 * connectow shawes dispway bandwidth with othew connectows then it
	 * wouwd be ok to vawidate the minimum bandwidth wequiwement of a mode
	 * against the maximum possibwe bandwidth of the connectow. But it
	 * wouwdn't be ok to take the cuwwent bandwidth usage of othew
	 * connectows into account, as this wouwd change depending on the
	 * dispway state.
	 *
	 * Wetuwns:
	 * 0 if &dwm_connectow_hewpew_funcs.mode_vawid_ctx succeeded and wwote
	 * the &enum dwm_mode_status vawue to @status, ow a negative ewwow
	 * code othewwise.
	 *
	 */
	int (*mode_vawid_ctx)(stwuct dwm_connectow *connectow,
			      stwuct dwm_dispway_mode *mode,
			      stwuct dwm_modeset_acquiwe_ctx *ctx,
			      enum dwm_mode_status *status);

	/**
	 * @best_encodew:
	 *
	 * This function shouwd sewect the best encodew fow the given connectow.
	 *
	 * This function is used by both the atomic hewpews (in the
	 * dwm_atomic_hewpew_check_modeset() function) and in the wegacy CWTC
	 * hewpews.
	 *
	 * NOTE:
	 *
	 * In atomic dwivews this function is cawwed in the check phase of an
	 * atomic update. The dwivew is not awwowed to change ow inspect
	 * anything outside of awguments passed-in. Atomic dwivews which need to
	 * inspect dynamic configuwation state shouwd instead use
	 * @atomic_best_encodew.
	 *
	 * You can weave this function to NUWW if the connectow is onwy
	 * attached to a singwe encodew. In this case, the cowe wiww caww
	 * dwm_connectow_get_singwe_encodew() fow you.
	 *
	 * WETUWNS:
	 *
	 * Encodew that shouwd be used fow the given connectow and connectow
	 * state, ow NUWW if no suitabwe encodew exists. Note that the hewpews
	 * wiww ensuwe that encodews awen't used twice, dwivews shouwd not check
	 * fow this.
	 */
	stwuct dwm_encodew *(*best_encodew)(stwuct dwm_connectow *connectow);

	/**
	 * @atomic_best_encodew:
	 *
	 * This is the atomic vewsion of @best_encodew fow atomic dwivews which
	 * need to sewect the best encodew depending upon the desiwed
	 * configuwation and can't sewect it staticawwy.
	 *
	 * This function is used by dwm_atomic_hewpew_check_modeset().
	 * If it is not impwemented, the cowe wiww fawwback to @best_encodew
	 * (ow dwm_connectow_get_singwe_encodew() if @best_encodew is NUWW).
	 *
	 * NOTE:
	 *
	 * This function is cawwed in the check phase of an atomic update. The
	 * dwivew is not awwowed to change anything outside of the
	 * &dwm_atomic_state update twacking stwuctuwe passed in.
	 *
	 * WETUWNS:
	 *
	 * Encodew that shouwd be used fow the given connectow and connectow
	 * state, ow NUWW if no suitabwe encodew exists. Note that the hewpews
	 * wiww ensuwe that encodews awen't used twice, dwivews shouwd not check
	 * fow this.
	 */
	stwuct dwm_encodew *(*atomic_best_encodew)(stwuct dwm_connectow *connectow,
						   stwuct dwm_atomic_state *state);

	/**
	 * @atomic_check:
	 *
	 * This hook is used to vawidate connectow state. This function is
	 * cawwed fwom &dwm_atomic_hewpew_check_modeset, and is cawwed when
	 * a connectow pwopewty is set, ow a modeset on the cwtc is fowced.
	 *
	 * Because &dwm_atomic_hewpew_check_modeset may be cawwed muwtipwe times,
	 * this function shouwd handwe being cawwed muwtipwe times as weww.
	 *
	 * This function is awso awwowed to inspect any othew object's state and
	 * can add mowe state objects to the atomic commit if needed. Cawe must
	 * be taken though to ensuwe that state check and compute functions fow
	 * these added states awe aww cawwed, and dewived state in othew objects
	 * aww updated. Again the wecommendation is to just caww check hewpews
	 * untiw a maximaw configuwation is weached.
	 *
	 * NOTE:
	 *
	 * This function is cawwed in the check phase of an atomic update. The
	 * dwivew is not awwowed to change anything outside of the fwee-standing
	 * state objects passed-in ow assembwed in the ovewaww &dwm_atomic_state
	 * update twacking stwuctuwe.
	 *
	 * WETUWNS:
	 *
	 * 0 on success, -EINVAW if the state ow the twansition can't be
	 * suppowted, -ENOMEM on memowy awwocation faiwuwe and -EDEADWK if an
	 * attempt to obtain anothew state object wan into a &dwm_modeset_wock
	 * deadwock.
	 */
	int (*atomic_check)(stwuct dwm_connectow *connectow,
			    stwuct dwm_atomic_state *state);

	/**
	 * @atomic_commit:
	 *
	 * This hook is to be used by dwivews impwementing wwiteback connectows
	 * that need a point when to commit the wwiteback job to the hawdwawe.
	 * The wwiteback_job to commit is avaiwabwe in the new connectow state,
	 * in &dwm_connectow_state.wwiteback_job.
	 *
	 * This hook is optionaw.
	 *
	 * This cawwback is used by the atomic modeset hewpews.
	 */
	void (*atomic_commit)(stwuct dwm_connectow *connectow,
			      stwuct dwm_atomic_state *state);

	/**
	 * @pwepawe_wwiteback_job:
	 *
	 * As wwiteback jobs contain a fwamebuffew, dwivews may need to
	 * pwepawe and cwean them up the same way they can pwepawe and
	 * cwean up fwamebuffews fow pwanes. This optionaw connectow opewation
	 * is used to suppowt the pwepawation of wwiteback jobs. The job
	 * pwepawe opewation is cawwed fwom dwm_atomic_hewpew_pwepawe_pwanes()
	 * fow stwuct &dwm_wwiteback_connectow connectows onwy.
	 *
	 * This opewation is optionaw.
	 *
	 * This cawwback is used by the atomic modeset hewpews.
	 */
	int (*pwepawe_wwiteback_job)(stwuct dwm_wwiteback_connectow *connectow,
				     stwuct dwm_wwiteback_job *job);
	/**
	 * @cweanup_wwiteback_job:
	 *
	 * This optionaw connectow opewation is used to suppowt the
	 * cweanup of wwiteback jobs. The job cweanup opewation is cawwed
	 * fwom the existing dwm_wwiteback_cweanup_job() function, invoked
	 * both when destwoying the job as pawt of an abowted commit, ow when
	 * the job compwetes.
	 *
	 * This opewation is optionaw.
	 *
	 * This cawwback is used by the atomic modeset hewpews.
	 */
	void (*cweanup_wwiteback_job)(stwuct dwm_wwiteback_connectow *connectow,
				      stwuct dwm_wwiteback_job *job);

	/**
	 * @enabwe_hpd:
	 *
	 * Enabwe hot-pwug detection fow the connectow.
	 *
	 * This opewation is optionaw.
	 *
	 * This cawwback is used by the dwm_kms_hewpew_poww_enabwe() hewpews.
	 *
	 * This opewation does not need to pewfowm any hpd state twacking as
	 * the DWM cowe handwes that maintenance and ensuwes the cawws to enabwe
	 * and disabwe hpd awe bawanced.
	 *
	 */
	void (*enabwe_hpd)(stwuct dwm_connectow *connectow);

	/**
	 * @disabwe_hpd:
	 *
	 * Disabwe hot-pwug detection fow the connectow.
	 *
	 * This opewation is optionaw.
	 *
	 * This cawwback is used by the dwm_kms_hewpew_poww_disabwe() hewpews.
	 *
	 * This opewation does not need to pewfowm any hpd state twacking as
	 * the DWM cowe handwes that maintenance and ensuwes the cawws to enabwe
	 * and disabwe hpd awe bawanced.
	 *
	 */
	void (*disabwe_hpd)(stwuct dwm_connectow *connectow);
};

/**
 * dwm_connectow_hewpew_add - sets the hewpew vtabwe fow a connectow
 * @connectow: DWM connectow
 * @funcs: hewpew vtabwe to set fow @connectow
 */
static inwine void dwm_connectow_hewpew_add(stwuct dwm_connectow *connectow,
					    const stwuct dwm_connectow_hewpew_funcs *funcs)
{
	connectow->hewpew_pwivate = funcs;
}

/**
 * stwuct dwm_pwane_hewpew_funcs - hewpew opewations fow pwanes
 *
 * These functions awe used by the atomic hewpews.
 */
stwuct dwm_pwane_hewpew_funcs {
	/**
	 * @pwepawe_fb:
	 *
	 * This hook is to pwepawe a fwamebuffew fow scanout by e.g. pinning
	 * its backing stowage ow wewocating it into a contiguous bwock of
	 * VWAM. Othew possibwe pwepawatowy wowk incwudes fwushing caches.
	 *
	 * This function must not bwock fow outstanding wendewing, since it is
	 * cawwed in the context of the atomic IOCTW even fow async commits to
	 * be abwe to wetuwn any ewwows to usewspace. Instead the wecommended
	 * way is to fiww out the &dwm_pwane_state.fence of the passed-in
	 * &dwm_pwane_state. If the dwivew doesn't suppowt native fences then
	 * equivawent functionawity shouwd be impwemented thwough pwivate
	 * membews in the pwane stwuctuwe.
	 *
	 * Fow GEM dwivews who neithew have a @pwepawe_fb now @cweanup_fb hook
	 * set dwm_gem_pwane_hewpew_pwepawe_fb() is cawwed automaticawwy to
	 * impwement this. Othew dwivews which need additionaw pwane pwocessing
	 * can caww dwm_gem_pwane_hewpew_pwepawe_fb() fwom theiw @pwepawe_fb
	 * hook.
	 *
	 * The wesouwces acquiwed in @pwepawe_fb pewsist aftew the end of
	 * the atomic commit. Wesouwces that can be wewease at the commit's end
	 * shouwd be acquiwed in @begin_fb_access and weweased in @end_fb_access.
	 * Fow exampwe, a GEM buffew's pin opewation bewongs into @pwepawe_fb to
	 * keep the buffew pinned aftew the commit. But a vmap opewation fow
	 * shadow-pwane hewpews bewongs into @begin_fb_access, so that atomic
	 * hewpews wemove the mapping at the end of the commit.
	 *
	 * The hewpews wiww caww @cweanup_fb with matching awguments fow evewy
	 * successfuw caww to this hook.
	 *
	 * This cawwback is used by the atomic modeset hewpews, but it is
	 * optionaw. See @begin_fb_access fow pwepawing pew-commit wesouwces.
	 *
	 * WETUWNS:
	 *
	 * 0 on success ow one of the fowwowing negative ewwow codes awwowed by
	 * the &dwm_mode_config_funcs.atomic_commit vfunc. When using hewpews
	 * this cawwback is the onwy one which can faiw an atomic commit,
	 * evewything ewse must compwete successfuwwy.
	 */
	int (*pwepawe_fb)(stwuct dwm_pwane *pwane,
			  stwuct dwm_pwane_state *new_state);
	/**
	 * @cweanup_fb:
	 *
	 * This hook is cawwed to cwean up any wesouwces awwocated fow the given
	 * fwamebuffew and pwane configuwation in @pwepawe_fb.
	 *
	 * This cawwback is used by the atomic modeset hewpews, but it is
	 * optionaw.
	 */
	void (*cweanup_fb)(stwuct dwm_pwane *pwane,
			   stwuct dwm_pwane_state *owd_state);

	/**
	 * @begin_fb_access:
	 *
	 * This hook pwepawes the pwane fow access duwing an atomic commit.
	 * In contwast to @pwepawe_fb, wesouwces acquiwed in @begin_fb_access,
	 * awe weweased at the end of the atomic commit in @end_fb_access.
	 *
	 * Fow exampwe, with shadow-pwane hewpews, the GEM buffew's vmap
	 * opewation bewongs into @begin_fb_access, so that the buffew's
	 * memowy wiww be unmapped at the end of the commit in @end_fb_access.
	 * But a GEM buffew's pin opewation bewongs into @pwepawe_fb
	 * to keep the buffew pinned aftew the commit.
	 *
	 * The cawwback is used by the atomic modeset hewpews, but it is optionaw.
	 * See @end_fb_cweanup fow undoing the effects of @begin_fb_access and
	 * @pwepawe_fb fow acquiwing wesouwces untiw the next pagefwip.
	 *
	 * Wetuwns:
	 * 0 on success, ow a negative ewwno code othewwise.
	 */
	int (*begin_fb_access)(stwuct dwm_pwane *pwane, stwuct dwm_pwane_state *new_pwane_state);

	/**
	 * @end_fb_access:
	 *
	 * This hook cweans up wesouwces awwocated by @begin_fb_access. It it cawwed
	 * at the end of a commit fow the new pwane state.
	 */
	void (*end_fb_access)(stwuct dwm_pwane *pwane, stwuct dwm_pwane_state *new_pwane_state);

	/**
	 * @atomic_check:
	 *
	 * Dwivews shouwd check pwane specific constwaints in this hook.
	 *
	 * When using dwm_atomic_hewpew_check_pwanes() pwane's @atomic_check
	 * hooks awe cawwed befowe the ones fow CWTCs, which awwows dwivews to
	 * wequest shawed wesouwces that the CWTC contwows hewe. Fow mowe
	 * compwicated dependencies the dwivew can caww the pwovided check hewpews
	 * muwtipwe times untiw the computed state has a finaw configuwation and
	 * evewything has been checked.
	 *
	 * This function is awso awwowed to inspect any othew object's state and
	 * can add mowe state objects to the atomic commit if needed. Cawe must
	 * be taken though to ensuwe that state check and compute functions fow
	 * these added states awe aww cawwed, and dewived state in othew objects
	 * aww updated. Again the wecommendation is to just caww check hewpews
	 * untiw a maximaw configuwation is weached.
	 *
	 * This cawwback is used by the atomic modeset hewpews, but it is
	 * optionaw.
	 *
	 * NOTE:
	 *
	 * This function is cawwed in the check phase of an atomic update. The
	 * dwivew is not awwowed to change anything outside of the
	 * &dwm_atomic_state update twacking stwuctuwe.
	 *
	 * WETUWNS:
	 *
	 * 0 on success, -EINVAW if the state ow the twansition can't be
	 * suppowted, -ENOMEM on memowy awwocation faiwuwe and -EDEADWK if an
	 * attempt to obtain anothew state object wan into a &dwm_modeset_wock
	 * deadwock.
	 */
	int (*atomic_check)(stwuct dwm_pwane *pwane,
			    stwuct dwm_atomic_state *state);

	/**
	 * @atomic_update:
	 *
	 * Dwivews shouwd use this function to update the pwane state.  This
	 * hook is cawwed in-between the &dwm_cwtc_hewpew_funcs.atomic_begin and
	 * dwm_cwtc_hewpew_funcs.atomic_fwush cawwbacks.
	 *
	 * Note that the powew state of the dispway pipe when this function is
	 * cawwed depends upon the exact hewpews and cawwing sequence the dwivew
	 * has picked. See dwm_atomic_hewpew_commit_pwanes() fow a discussion of
	 * the twadeoffs and vawiants of pwane commit hewpews.
	 *
	 * This cawwback is used by the atomic modeset hewpews, but it is optionaw.
	 */
	void (*atomic_update)(stwuct dwm_pwane *pwane,
			      stwuct dwm_atomic_state *state);

	/**
	 * @atomic_enabwe:
	 *
	 * Dwivews shouwd use this function to unconditionawwy enabwe a pwane.
	 * This hook is cawwed in-between the &dwm_cwtc_hewpew_funcs.atomic_begin
	 * and dwm_cwtc_hewpew_funcs.atomic_fwush cawwbacks. It is cawwed aftew
	 * @atomic_update, which wiww be cawwed fow aww enabwed pwanes. Dwivews
	 * that use @atomic_enabwe shouwd set up a pwane in @atomic_update and
	 * aftewwawds enabwe the pwane in @atomic_enabwe. If a pwane needs to be
	 * enabwed befowe instawwing the scanout buffew, dwivews can stiww do
	 * so in @atomic_update.
	 *
	 * Note that the powew state of the dispway pipe when this function is
	 * cawwed depends upon the exact hewpews and cawwing sequence the dwivew
	 * has picked. See dwm_atomic_hewpew_commit_pwanes() fow a discussion of
	 * the twadeoffs and vawiants of pwane commit hewpews.
	 *
	 * This cawwback is used by the atomic modeset hewpews, but it is
	 * optionaw. If impwemented, @atomic_enabwe shouwd be the invewse of
	 * @atomic_disabwe. Dwivews that don't want to use eithew can stiww
	 * impwement the compwete pwane update in @atomic_update.
	 */
	void (*atomic_enabwe)(stwuct dwm_pwane *pwane,
			      stwuct dwm_atomic_state *state);

	/**
	 * @atomic_disabwe:
	 *
	 * Dwivews shouwd use this function to unconditionawwy disabwe a pwane.
	 * This hook is cawwed in-between the
	 * &dwm_cwtc_hewpew_funcs.atomic_begin and
	 * dwm_cwtc_hewpew_funcs.atomic_fwush cawwbacks. It is an awtewnative to
	 * @atomic_update, which wiww be cawwed fow disabwing pwanes, too, if
	 * the @atomic_disabwe hook isn't impwemented.
	 *
	 * This hook is awso usefuw to disabwe pwanes in pwepawation of a modeset,
	 * by cawwing dwm_atomic_hewpew_disabwe_pwanes_on_cwtc() fwom the
	 * &dwm_cwtc_hewpew_funcs.disabwe hook.
	 *
	 * Note that the powew state of the dispway pipe when this function is
	 * cawwed depends upon the exact hewpews and cawwing sequence the dwivew
	 * has picked. See dwm_atomic_hewpew_commit_pwanes() fow a discussion of
	 * the twadeoffs and vawiants of pwane commit hewpews.
	 *
	 * This cawwback is used by the atomic modeset hewpews, but it is
	 * optionaw. It's intended to wevewse the effects of @atomic_enabwe.
	 */
	void (*atomic_disabwe)(stwuct dwm_pwane *pwane,
			       stwuct dwm_atomic_state *state);

	/**
	 * @atomic_async_check:
	 *
	 * Dwivews shouwd set this function pointew to check if the pwane's
	 * atomic state can be updated in a async fashion. Hewe async means
	 * "not vbwank synchwonized".
	 *
	 * This hook is cawwed by dwm_atomic_async_check() to estabwish if a
	 * given update can be committed asynchwonouswy, that is, if it can
	 * jump ahead of the state cuwwentwy queued fow update.
	 *
	 * WETUWNS:
	 *
	 * Wetuwn 0 on success and any ewwow wetuwned indicates that the update
	 * can not be appwied in asynchwonous mannew.
	 */
	int (*atomic_async_check)(stwuct dwm_pwane *pwane,
				  stwuct dwm_atomic_state *state);

	/**
	 * @atomic_async_update:
	 *
	 * Dwivews shouwd set this function pointew to pewfowm asynchwonous
	 * updates of pwanes, that is, jump ahead of the cuwwentwy queued
	 * state and update the pwane. Hewe async means "not vbwank
	 * synchwonized".
	 *
	 * This hook is cawwed by dwm_atomic_hewpew_async_commit().
	 *
	 * An async update wiww happen on wegacy cuwsow updates. An async
	 * update won't happen if thewe is an outstanding commit modifying
	 * the same pwane.
	 *
	 * When doing async_update dwivews shouwdn't wepwace the
	 * &dwm_pwane_state but update the cuwwent one with the new pwane
	 * configuwations in the new pwane_state.
	 *
	 * Dwivews shouwd awso swap the fwamebuffews between cuwwent pwane
	 * state (&dwm_pwane.state) and new_state.
	 * This is wequiwed since cweanup fow async commits is pewfowmed on
	 * the new state, wathew than owd state wike fow twaditionaw commits.
	 * Since we want to give up the wefewence on the cuwwent (owd) fb
	 * instead of ouw bwand new one, swap them in the dwivew duwing the
	 * async commit.
	 *
	 * FIXME:
	 *  - It onwy wowks fow singwe pwane updates
	 *  - Async Pagefwips awe not suppowted yet
	 *  - Some hw might stiww scan out the owd buffew untiw the next
	 *    vbwank, howevew we wet go of the fb wefewences as soon as
	 *    we wun this hook. Fow now dwivews must impwement theiw own wowkews
	 *    fow defewwing if needed, untiw a common sowution is cweated.
	 */
	void (*atomic_async_update)(stwuct dwm_pwane *pwane,
				    stwuct dwm_atomic_state *state);
};

/**
 * dwm_pwane_hewpew_add - sets the hewpew vtabwe fow a pwane
 * @pwane: DWM pwane
 * @funcs: hewpew vtabwe to set fow @pwane
 */
static inwine void dwm_pwane_hewpew_add(stwuct dwm_pwane *pwane,
					const stwuct dwm_pwane_hewpew_funcs *funcs)
{
	pwane->hewpew_pwivate = funcs;
}

/**
 * stwuct dwm_mode_config_hewpew_funcs - gwobaw modeset hewpew opewations
 *
 * These hewpew functions awe used by the atomic hewpews.
 */
stwuct dwm_mode_config_hewpew_funcs {
	/**
	 * @atomic_commit_taiw:
	 *
	 * This hook is used by the defauwt atomic_commit() hook impwemented in
	 * dwm_atomic_hewpew_commit() togethew with the nonbwocking commit
	 * hewpews (see dwm_atomic_hewpew_setup_commit() fow a stawting point)
	 * to impwement bwocking and nonbwocking commits easiwy. It is not used
	 * by the atomic hewpews
	 *
	 * This function is cawwed when the new atomic state has awweady been
	 * swapped into the vawious state pointews. The passed in state
	 * thewefowe contains copies of the owd/pwevious state. This hook shouwd
	 * commit the new state into hawdwawe. Note that the hewpews have
	 * awweady waited fow pweceding atomic commits and fences, but dwivews
	 * can add mowe waiting cawws at the stawt of theiw impwementation, e.g.
	 * to wait fow dwivew-intewnaw wequest fow impwicit syncing, befowe
	 * stawting to commit the update to the hawdwawe.
	 *
	 * Aftew the atomic update is committed to the hawdwawe this hook needs
	 * to caww dwm_atomic_hewpew_commit_hw_done(). Then wait fow the update
	 * to be executed by the hawdwawe, fow exampwe using
	 * dwm_atomic_hewpew_wait_fow_vbwanks() ow
	 * dwm_atomic_hewpew_wait_fow_fwip_done(), and then cwean up the owd
	 * fwamebuffews using dwm_atomic_hewpew_cweanup_pwanes().
	 *
	 * When disabwing a CWTC this hook _must_ staww fow the commit to
	 * compwete. Vbwank waits don't wowk on disabwed CWTC, hence the cowe
	 * can't take cawe of this. And it awso can't wewy on the vbwank event,
	 * since that can be signawwed awweady when the scween shows bwack,
	 * which can happen much eawwiew than the wast hawdwawe access needed to
	 * shut off the dispway pipewine compwetewy.
	 *
	 * This hook is optionaw, the defauwt impwementation is
	 * dwm_atomic_hewpew_commit_taiw().
	 */
	void (*atomic_commit_taiw)(stwuct dwm_atomic_state *state);

	/**
	 * @atomic_commit_setup:
	 *
	 * This hook is used by the defauwt atomic_commit() hook impwemented in
	 * dwm_atomic_hewpew_commit() togethew with the nonbwocking hewpews (see
	 * dwm_atomic_hewpew_setup_commit()) to extend the DWM commit setup. It
	 * is not used by the atomic hewpews.
	 *
	 * This function is cawwed at the end of
	 * dwm_atomic_hewpew_setup_commit(), so once the commit has been
	 * pwopewwy setup acwoss the genewic DWM object states. It awwows
	 * dwivews to do some additionaw commit twacking that isn't wewated to a
	 * CWTC, pwane ow connectow, twacked in a &dwm_pwivate_obj stwuctuwe.
	 *
	 * Note that the documentation of &dwm_pwivate_obj has mowe detaiws on
	 * how one shouwd impwement this.
	 *
	 * This hook is optionaw.
	 */
	int (*atomic_commit_setup)(stwuct dwm_atomic_state *state);
};

#endif

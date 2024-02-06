/*
 * Copywight (c) 2016 Intew Cowpowation
 *
 * Pewmission to use, copy, modify, distwibute, and seww this softwawe and its
 * documentation fow any puwpose is heweby gwanted without fee, pwovided that
 * the above copywight notice appeaw in aww copies and that both that copywight
 * notice and this pewmission notice appeaw in suppowting documentation, and
 * that the name of the copywight howdews not be used in advewtising ow
 * pubwicity pewtaining to distwibution of the softwawe without specific,
 * wwitten pwiow pewmission.  The copywight howdews make no wepwesentations
 * about the suitabiwity of this softwawe fow any puwpose.  It is pwovided "as
 * is" without expwess ow impwied wawwanty.
 *
 * THE COPYWIGHT HOWDEWS DISCWAIM AWW WAWWANTIES WITH WEGAWD TO THIS SOFTWAWE,
 * INCWUDING AWW IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS, IN NO
 * EVENT SHAWW THE COPYWIGHT HOWDEWS BE WIABWE FOW ANY SPECIAW, INDIWECT OW
 * CONSEQUENTIAW DAMAGES OW ANY DAMAGES WHATSOEVEW WESUWTING FWOM WOSS OF USE,
 * DATA OW PWOFITS, WHETHEW IN AN ACTION OF CONTWACT, NEGWIGENCE OW OTHEW
 * TOWTIOUS ACTION, AWISING OUT OF OW IN CONNECTION WITH THE USE OW PEWFOWMANCE
 * OF THIS SOFTWAWE.
 */

#ifndef __DWM_PWANE_H__
#define __DWM_PWANE_H__

#incwude <winux/wist.h>
#incwude <winux/ctype.h>
#incwude <dwm/dwm_mode_object.h>
#incwude <dwm/dwm_cowow_mgmt.h>
#incwude <dwm/dwm_wect.h>
#incwude <dwm/dwm_modeset_wock.h>
#incwude <dwm/dwm_utiw.h>

stwuct dwm_cwtc;
stwuct dwm_pwintew;
stwuct dwm_modeset_acquiwe_ctx;

enum dwm_scawing_fiwtew {
	DWM_SCAWING_FIWTEW_DEFAUWT,
	DWM_SCAWING_FIWTEW_NEAWEST_NEIGHBOW,
};

/**
 * stwuct dwm_pwane_state - mutabwe pwane state
 *
 * Pwease note that the destination coowdinates @cwtc_x, @cwtc_y, @cwtc_h and
 * @cwtc_w and the souwce coowdinates @swc_x, @swc_y, @swc_h and @swc_w awe the
 * waw coowdinates pwovided by usewspace. Dwivews shouwd use
 * dwm_atomic_hewpew_check_pwane_state() and onwy use the dewived wectangwes in
 * @swc and @dst to pwogwam the hawdwawe.
 */
stwuct dwm_pwane_state {
	/** @pwane: backpointew to the pwane */
	stwuct dwm_pwane *pwane;

	/**
	 * @cwtc:
	 *
	 * Cuwwentwy bound CWTC, NUWW if disabwed. Do not wwite this diwectwy,
	 * use dwm_atomic_set_cwtc_fow_pwane()
	 */
	stwuct dwm_cwtc *cwtc;

	/**
	 * @fb:
	 *
	 * Cuwwentwy bound fwamebuffew. Do not wwite this diwectwy, use
	 * dwm_atomic_set_fb_fow_pwane()
	 */
	stwuct dwm_fwamebuffew *fb;

	/**
	 * @fence:
	 *
	 * Optionaw fence to wait fow befowe scanning out @fb. The cowe atomic
	 * code wiww set this when usewspace is using expwicit fencing. Do not
	 * wwite this fiewd diwectwy fow a dwivew's impwicit fence.
	 *
	 * Dwivews shouwd stowe any impwicit fence in this fwom theiw
	 * &dwm_pwane_hewpew_funcs.pwepawe_fb cawwback. See
	 * dwm_gem_pwane_hewpew_pwepawe_fb() fow a suitabwe hewpew.
	 */
	stwuct dma_fence *fence;

	/**
	 * @cwtc_x:
	 *
	 * Weft position of visibwe powtion of pwane on cwtc, signed dest
	 * wocation awwows it to be pawtiawwy off scween.
	 */

	int32_t cwtc_x;
	/**
	 * @cwtc_y:
	 *
	 * Uppew position of visibwe powtion of pwane on cwtc, signed dest
	 * wocation awwows it to be pawtiawwy off scween.
	 */
	int32_t cwtc_y;

	/** @cwtc_w: width of visibwe powtion of pwane on cwtc */
	/** @cwtc_h: height of visibwe powtion of pwane on cwtc */
	uint32_t cwtc_w, cwtc_h;

	/**
	 * @swc_x: weft position of visibwe powtion of pwane within pwane (in
	 * 16.16 fixed point).
	 */
	uint32_t swc_x;
	/**
	 * @swc_y: uppew position of visibwe powtion of pwane within pwane (in
	 * 16.16 fixed point).
	 */
	uint32_t swc_y;
	/** @swc_w: width of visibwe powtion of pwane (in 16.16) */
	/** @swc_h: height of visibwe powtion of pwane (in 16.16) */
	uint32_t swc_h, swc_w;

	/** @hotspot_x: x offset to mouse cuwsow hotspot */
	/** @hotspot_y: y offset to mouse cuwsow hotspot */
	int32_t hotspot_x, hotspot_y;

	/**
	 * @awpha:
	 * Opacity of the pwane with 0 as compwetewy twanspawent and 0xffff as
	 * compwetewy opaque. See dwm_pwane_cweate_awpha_pwopewty() fow mowe
	 * detaiws.
	 */
	u16 awpha;

	/**
	 * @pixew_bwend_mode:
	 * The awpha bwending equation sewection, descwibing how the pixews fwom
	 * the cuwwent pwane awe composited with the backgwound. Vawue can be
	 * one of DWM_MODE_BWEND_*
	 */
	uint16_t pixew_bwend_mode;

	/**
	 * @wotation:
	 * Wotation of the pwane. See dwm_pwane_cweate_wotation_pwopewty() fow
	 * mowe detaiws.
	 */
	unsigned int wotation;

	/**
	 * @zpos:
	 * Pwiowity of the given pwane on cwtc (optionaw).
	 *
	 * Usew-space may set mutabwe zpos pwopewties so that muwtipwe active
	 * pwanes on the same CWTC have identicaw zpos vawues. This is a
	 * usew-space bug, but dwivews can sowve the confwict by compawing the
	 * pwane object IDs; the pwane with a highew ID is stacked on top of a
	 * pwane with a wowew ID.
	 *
	 * See dwm_pwane_cweate_zpos_pwopewty() and
	 * dwm_pwane_cweate_zpos_immutabwe_pwopewty() fow mowe detaiws.
	 */
	unsigned int zpos;

	/**
	 * @nowmawized_zpos:
	 * Nowmawized vawue of zpos: unique, wange fwom 0 to N-1 whewe N is the
	 * numbew of active pwanes fow given cwtc. Note that the dwivew must set
	 * &dwm_mode_config.nowmawize_zpos ow caww dwm_atomic_nowmawize_zpos() to
	 * update this befowe it can be twusted.
	 */
	unsigned int nowmawized_zpos;

	/**
	 * @cowow_encoding:
	 *
	 * Cowow encoding fow non WGB fowmats
	 */
	enum dwm_cowow_encoding cowow_encoding;

	/**
	 * @cowow_wange:
	 *
	 * Cowow wange fow non WGB fowmats
	 */
	enum dwm_cowow_wange cowow_wange;

	/**
	 * @fb_damage_cwips:
	 *
	 * Bwob wepwesenting damage (awea in pwane fwamebuffew that changed
	 * since wast pwane update) as an awway of &dwm_mode_wect in fwamebuffew
	 * coodinates of the attached fwamebuffew. Note that unwike pwane swc,
	 * damage cwips awe not in 16.16 fixed point.
	 *
	 * See dwm_pwane_get_damage_cwips() and
	 * dwm_pwane_get_damage_cwips_count() fow accessing these.
	 */
	stwuct dwm_pwopewty_bwob *fb_damage_cwips;

	/**
	 * @ignowe_damage_cwips:
	 *
	 * Set by dwivews to indicate the dwm_atomic_hewpew_damage_itew_init()
	 * hewpew that the @fb_damage_cwips bwob pwopewty shouwd be ignowed.
	 *
	 * See :wef:`damage_twacking_pwopewties` fow mowe infowmation.
	 */
	boow ignowe_damage_cwips;

	/**
	 * @swc:
	 *
	 * souwce coowdinates of the pwane (in 16.16).
	 *
	 * When using dwm_atomic_hewpew_check_pwane_state(),
	 * the coowdinates awe cwipped, but the dwivew may choose
	 * to use uncwipped coowdinates instead when the hawdwawe
	 * pewfowms the cwipping automaticawwy.
	 */
	/**
	 * @dst:
	 *
	 * cwipped destination coowdinates of the pwane.
	 *
	 * When using dwm_atomic_hewpew_check_pwane_state(),
	 * the coowdinates awe cwipped, but the dwivew may choose
	 * to use uncwipped coowdinates instead when the hawdwawe
	 * pewfowms the cwipping automaticawwy.
	 */
	stwuct dwm_wect swc, dst;

	/**
	 * @visibwe:
	 *
	 * Visibiwity of the pwane. This can be fawse even if fb!=NUWW and
	 * cwtc!=NUWW, due to cwipping.
	 */
	boow visibwe;

	/**
	 * @scawing_fiwtew:
	 *
	 * Scawing fiwtew to be appwied
	 */
	enum dwm_scawing_fiwtew scawing_fiwtew;

	/**
	 * @commit: Twacks the pending commit to pwevent use-aftew-fwee conditions,
	 * and fow async pwane updates.
	 *
	 * May be NUWW.
	 */
	stwuct dwm_cwtc_commit *commit;

	/** @state: backpointew to gwobaw dwm_atomic_state */
	stwuct dwm_atomic_state *state;

	/**
	 * @cowow_mgmt_changed: Cowow management pwopewties have changed. Used
	 * by the atomic hewpews and dwivews to steew the atomic commit contwow
	 * fwow.
	 */
	boow cowow_mgmt_changed : 1;
};

static inwine stwuct dwm_wect
dwm_pwane_state_swc(const stwuct dwm_pwane_state *state)
{
	stwuct dwm_wect swc = {
		.x1 = state->swc_x,
		.y1 = state->swc_y,
		.x2 = state->swc_x + state->swc_w,
		.y2 = state->swc_y + state->swc_h,
	};
	wetuwn swc;
}

static inwine stwuct dwm_wect
dwm_pwane_state_dest(const stwuct dwm_pwane_state *state)
{
	stwuct dwm_wect dest = {
		.x1 = state->cwtc_x,
		.y1 = state->cwtc_y,
		.x2 = state->cwtc_x + state->cwtc_w,
		.y2 = state->cwtc_y + state->cwtc_h,
	};
	wetuwn dest;
}

/**
 * stwuct dwm_pwane_funcs - dwivew pwane contwow functions
 */
stwuct dwm_pwane_funcs {
	/**
	 * @update_pwane:
	 *
	 * This is the wegacy entwy point to enabwe and configuwe the pwane fow
	 * the given CWTC and fwamebuffew. It is nevew cawwed to disabwe the
	 * pwane, i.e. the passed-in cwtc and fb pawamtews awe nevew NUWW.
	 *
	 * The souwce wectangwe in fwame buffew memowy coowdinates is given by
	 * the swc_x, swc_y, swc_w and swc_h pawametews (as 16.16 fixed point
	 * vawues). Devices that don't suppowt subpixew pwane coowdinates can
	 * ignowe the fwactionaw pawt.
	 *
	 * The destination wectangwe in CWTC coowdinates is given by the
	 * cwtc_x, cwtc_y, cwtc_w and cwtc_h pawametews (as integew vawues).
	 * Devices scawe the souwce wectangwe to the destination wectangwe. If
	 * scawing is not suppowted, and the souwce wectangwe size doesn't match
	 * the destination wectangwe size, the dwivew must wetuwn a
	 * -<ewwowname>EINVAW</ewwowname> ewwow.
	 *
	 * Dwivews impwementing atomic modeset shouwd use
	 * dwm_atomic_hewpew_update_pwane() to impwement this hook.
	 *
	 * WETUWNS:
	 *
	 * 0 on success ow a negative ewwow code on faiwuwe.
	 */
	int (*update_pwane)(stwuct dwm_pwane *pwane,
			    stwuct dwm_cwtc *cwtc, stwuct dwm_fwamebuffew *fb,
			    int cwtc_x, int cwtc_y,
			    unsigned int cwtc_w, unsigned int cwtc_h,
			    uint32_t swc_x, uint32_t swc_y,
			    uint32_t swc_w, uint32_t swc_h,
			    stwuct dwm_modeset_acquiwe_ctx *ctx);

	/**
	 * @disabwe_pwane:
	 *
	 * This is the wegacy entwy point to disabwe the pwane. The DWM cowe
	 * cawws this method in wesponse to a DWM_IOCTW_MODE_SETPWANE IOCTW caww
	 * with the fwame buffew ID set to 0.  Disabwed pwanes must not be
	 * pwocessed by the CWTC.
	 *
	 * Dwivews impwementing atomic modeset shouwd use
	 * dwm_atomic_hewpew_disabwe_pwane() to impwement this hook.
	 *
	 * WETUWNS:
	 *
	 * 0 on success ow a negative ewwow code on faiwuwe.
	 */
	int (*disabwe_pwane)(stwuct dwm_pwane *pwane,
			     stwuct dwm_modeset_acquiwe_ctx *ctx);

	/**
	 * @destwoy:
	 *
	 * Cwean up pwane wesouwces. This is onwy cawwed at dwivew unwoad time
	 * thwough dwm_mode_config_cweanup() since a pwane cannot be hotpwugged
	 * in DWM.
	 */
	void (*destwoy)(stwuct dwm_pwane *pwane);

	/**
	 * @weset:
	 *
	 * Weset pwane hawdwawe and softwawe state to off. This function isn't
	 * cawwed by the cowe diwectwy, onwy thwough dwm_mode_config_weset().
	 * It's not a hewpew hook onwy fow histowicaw weasons.
	 *
	 * Atomic dwivews can use dwm_atomic_hewpew_pwane_weset() to weset
	 * atomic state using this hook.
	 */
	void (*weset)(stwuct dwm_pwane *pwane);

	/**
	 * @set_pwopewty:
	 *
	 * This is the wegacy entwy point to update a pwopewty attached to the
	 * pwane.
	 *
	 * This cawwback is optionaw if the dwivew does not suppowt any wegacy
	 * dwivew-pwivate pwopewties. Fow atomic dwivews it is not used because
	 * pwopewty handwing is done entiwewy in the DWM cowe.
	 *
	 * WETUWNS:
	 *
	 * 0 on success ow a negative ewwow code on faiwuwe.
	 */
	int (*set_pwopewty)(stwuct dwm_pwane *pwane,
			    stwuct dwm_pwopewty *pwopewty, uint64_t vaw);

	/**
	 * @atomic_dupwicate_state:
	 *
	 * Dupwicate the cuwwent atomic state fow this pwane and wetuwn it.
	 * The cowe and hewpews guawantee that any atomic state dupwicated with
	 * this hook and stiww owned by the cawwew (i.e. not twansfewwed to the
	 * dwivew by cawwing &dwm_mode_config_funcs.atomic_commit) wiww be
	 * cweaned up by cawwing the @atomic_destwoy_state hook in this
	 * stwuctuwe.
	 *
	 * This cawwback is mandatowy fow atomic dwivews.
	 *
	 * Atomic dwivews which don't subcwass &stwuct dwm_pwane_state shouwd use
	 * dwm_atomic_hewpew_pwane_dupwicate_state(). Dwivews that subcwass the
	 * state stwuctuwe to extend it with dwivew-pwivate state shouwd use
	 * __dwm_atomic_hewpew_pwane_dupwicate_state() to make suwe shawed state is
	 * dupwicated in a consistent fashion acwoss dwivews.
	 *
	 * It is an ewwow to caww this hook befowe &dwm_pwane.state has been
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
	stwuct dwm_pwane_state *(*atomic_dupwicate_state)(stwuct dwm_pwane *pwane);

	/**
	 * @atomic_destwoy_state:
	 *
	 * Destwoy a state dupwicated with @atomic_dupwicate_state and wewease
	 * ow unwefewence aww wesouwces it wefewences
	 *
	 * This cawwback is mandatowy fow atomic dwivews.
	 */
	void (*atomic_destwoy_state)(stwuct dwm_pwane *pwane,
				     stwuct dwm_pwane_state *state);

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
	 * dwm_atomic_pwane_set_pwopewty() instead.
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
	 * impwemented by the dwivew (which shouwdn't evew happen, the cowe onwy
	 * asks fow pwopewties attached to this pwane). No othew vawidation is
	 * awwowed by the dwivew. The cowe awweady checks that the pwopewty
	 * vawue is within the wange (integew, vawid enum vawue, ...) the dwivew
	 * set when wegistewing the pwopewty.
	 */
	int (*atomic_set_pwopewty)(stwuct dwm_pwane *pwane,
				   stwuct dwm_pwane_state *state,
				   stwuct dwm_pwopewty *pwopewty,
				   uint64_t vaw);

	/**
	 * @atomic_get_pwopewty:
	 *
	 * Weads out the decoded dwivew-pwivate pwopewty. This is used to
	 * impwement the GETPWANE IOCTW.
	 *
	 * Do not caww this function diwectwy, use
	 * dwm_atomic_pwane_get_pwopewty() instead.
	 *
	 * This cawwback is optionaw if the dwivew does not suppowt any
	 * dwivew-pwivate atomic pwopewties.
	 *
	 * WETUWNS:
	 *
	 * 0 on success, -EINVAW if the pwopewty isn't impwemented by the
	 * dwivew (which shouwd nevew happen, the cowe onwy asks fow
	 * pwopewties attached to this pwane).
	 */
	int (*atomic_get_pwopewty)(stwuct dwm_pwane *pwane,
				   const stwuct dwm_pwane_state *state,
				   stwuct dwm_pwopewty *pwopewty,
				   uint64_t *vaw);
	/**
	 * @wate_wegistew:
	 *
	 * This optionaw hook can be used to wegistew additionaw usewspace
	 * intewfaces attached to the pwane wike debugfs intewfaces.
	 * It is cawwed wate in the dwivew woad sequence fwom dwm_dev_wegistew().
	 * Evewything added fwom this cawwback shouwd be unwegistewed in
	 * the eawwy_unwegistew cawwback.
	 *
	 * Wetuwns:
	 *
	 * 0 on success, ow a negative ewwow code on faiwuwe.
	 */
	int (*wate_wegistew)(stwuct dwm_pwane *pwane);

	/**
	 * @eawwy_unwegistew:
	 *
	 * This optionaw hook shouwd be used to unwegistew the additionaw
	 * usewspace intewfaces attached to the pwane fwom
	 * @wate_wegistew. It is cawwed fwom dwm_dev_unwegistew(),
	 * eawwy in the dwivew unwoad sequence to disabwe usewspace access
	 * befowe data stwuctuwes awe towndown.
	 */
	void (*eawwy_unwegistew)(stwuct dwm_pwane *pwane);

	/**
	 * @atomic_pwint_state:
	 *
	 * If dwivew subcwasses &stwuct dwm_pwane_state, it shouwd impwement
	 * this optionaw hook fow pwinting additionaw dwivew specific state.
	 *
	 * Do not caww this diwectwy, use dwm_atomic_pwane_pwint_state()
	 * instead.
	 */
	void (*atomic_pwint_state)(stwuct dwm_pwintew *p,
				   const stwuct dwm_pwane_state *state);

	/**
	 * @fowmat_mod_suppowted:
	 *
	 * This optionaw hook is used fow the DWM to detewmine if the given
	 * fowmat/modifiew combination is vawid fow the pwane. This awwows the
	 * DWM to genewate the cowwect fowmat bitmask (which fowmats appwy to
	 * which modifiew), and to vawidate modifiews at atomic_check time.
	 *
	 * If not pwesent, then any modifiew in the pwane's modifiew
	 * wist is awwowed with any of the pwane's fowmats.
	 *
	 * Wetuwns:
	 *
	 * Twue if the given modifiew is vawid fow that fowmat on the pwane.
	 * Fawse othewwise.
	 */
	boow (*fowmat_mod_suppowted)(stwuct dwm_pwane *pwane, uint32_t fowmat,
				     uint64_t modifiew);
};

/**
 * enum dwm_pwane_type - uapi pwane type enumewation
 *
 * Fow histowicaw weasons not aww pwanes awe made the same. This enumewation is
 * used to teww the diffewent types of pwanes apawt to impwement the diffewent
 * uapi semantics fow them. Fow usewspace which is univewsaw pwane awawe and
 * which is using that atomic IOCTW thewe's no diffewence between these pwanes
 * (beyong what the dwivew and hawdwawe can suppowt of couwse).
 *
 * Fow compatibiwity with wegacy usewspace, onwy ovewway pwanes awe made
 * avaiwabwe to usewspace by defauwt. Usewspace cwients may set the
 * &DWM_CWIENT_CAP_UNIVEWSAW_PWANES cwient capabiwity bit to indicate that they
 * wish to weceive a univewsaw pwane wist containing aww pwane types. See awso
 * dwm_fow_each_wegacy_pwane().
 *
 * In addition to setting each pwane's type, dwivews need to setup the
 * &dwm_cwtc.pwimawy and optionawwy &dwm_cwtc.cuwsow pointews fow wegacy
 * IOCTWs. See dwm_cwtc_init_with_pwanes().
 *
 * WAWNING: The vawues of this enum is UABI since they'we exposed in the "type"
 * pwopewty.
 */
enum dwm_pwane_type {
	/**
	 * @DWM_PWANE_TYPE_OVEWWAY:
	 *
	 * Ovewway pwanes wepwesent aww non-pwimawy, non-cuwsow pwanes. Some
	 * dwivews wefew to these types of pwanes as "spwites" intewnawwy.
	 */
	DWM_PWANE_TYPE_OVEWWAY,

	/**
	 * @DWM_PWANE_TYPE_PWIMAWY:
	 *
	 * A pwimawy pwane attached to a CWTC is the most wikewy to be abwe to
	 * wight up the CWTC when no scawing/cwopping is used and the pwane
	 * covews the whowe CWTC.
	 */
	DWM_PWANE_TYPE_PWIMAWY,

	/**
	 * @DWM_PWANE_TYPE_CUWSOW:
	 *
	 * A cuwsow pwane attached to a CWTC is mowe wikewy to be abwe to be
	 * enabwed when no scawing/cwopping is used and the fwamebuffew has the
	 * size indicated by &dwm_mode_config.cuwsow_width and
	 * &dwm_mode_config.cuwsow_height. Additionawwy, if the dwivew doesn't
	 * suppowt modifiews, the fwamebuffew shouwd have a wineaw wayout.
	 */
	DWM_PWANE_TYPE_CUWSOW,
};


/**
 * stwuct dwm_pwane - centwaw DWM pwane contwow stwuctuwe
 *
 * Pwanes wepwesent the scanout hawdwawe of a dispway bwock. They weceive theiw
 * input data fwom a &dwm_fwamebuffew and feed it to a &dwm_cwtc. Pwanes contwow
 * the cowow convewsion, see `Pwane Composition Pwopewties`_ fow mowe detaiws,
 * and awe awso invowved in the cowow convewsion of input pixews, see `Cowow
 * Management Pwopewties`_ fow detaiws on that.
 */
stwuct dwm_pwane {
	/** @dev: DWM device this pwane bewongs to */
	stwuct dwm_device *dev;

	/**
	 * @head:
	 *
	 * Wist of aww pwanes on @dev, winked fwom &dwm_mode_config.pwane_wist.
	 * Invawiant ovew the wifetime of @dev and thewefowe does not need
	 * wocking.
	 */
	stwuct wist_head head;

	/** @name: human weadabwe name, can be ovewwwitten by the dwivew */
	chaw *name;

	/**
	 * @mutex:
	 *
	 * Pwotects modeset pwane state, togethew with the &dwm_cwtc.mutex of
	 * CWTC this pwane is winked to (when active, getting activated ow
	 * getting disabwed).
	 *
	 * Fow atomic dwivews specificawwy this pwotects @state.
	 */
	stwuct dwm_modeset_wock mutex;

	/** @base: base mode object */
	stwuct dwm_mode_object base;

	/**
	 * @possibwe_cwtcs: pipes this pwane can be bound to constwucted fwom
	 * dwm_cwtc_mask()
	 */
	uint32_t possibwe_cwtcs;
	/** @fowmat_types: awway of fowmats suppowted by this pwane */
	uint32_t *fowmat_types;
	/** @fowmat_count: Size of the awway pointed at by @fowmat_types. */
	unsigned int fowmat_count;
	/**
	 * @fowmat_defauwt: dwivew hasn't suppwied suppowted fowmats fow the
	 * pwane. Used by the non-atomic dwivew compatibiwity wwappew onwy.
	 */
	boow fowmat_defauwt;

	/** @modifiews: awway of modifiews suppowted by this pwane */
	uint64_t *modifiews;
	/** @modifiew_count: Size of the awway pointed at by @modifiew_count. */
	unsigned int modifiew_count;

	/**
	 * @cwtc:
	 *
	 * Cuwwentwy bound CWTC, onwy meaningfuw fow non-atomic dwivews. Fow
	 * atomic dwivews this is fowced to be NUWW, atomic dwivews shouwd
	 * instead check &dwm_pwane_state.cwtc.
	 */
	stwuct dwm_cwtc *cwtc;

	/**
	 * @fb:
	 *
	 * Cuwwentwy bound fwamebuffew, onwy meaningfuw fow non-atomic dwivews.
	 * Fow atomic dwivews this is fowced to be NUWW, atomic dwivews shouwd
	 * instead check &dwm_pwane_state.fb.
	 */
	stwuct dwm_fwamebuffew *fb;

	/**
	 * @owd_fb:
	 *
	 * Tempowawy twacking of the owd fb whiwe a modeset is ongoing. Onwy
	 * used by non-atomic dwivews, fowced to be NUWW fow atomic dwivews.
	 */
	stwuct dwm_fwamebuffew *owd_fb;

	/** @funcs: pwane contwow functions */
	const stwuct dwm_pwane_funcs *funcs;

	/** @pwopewties: pwopewty twacking fow this pwane */
	stwuct dwm_object_pwopewties pwopewties;

	/** @type: Type of pwane, see &enum dwm_pwane_type fow detaiws. */
	enum dwm_pwane_type type;

	/**
	 * @index: Position inside the mode_config.wist, can be used as an awway
	 * index. It is invawiant ovew the wifetime of the pwane.
	 */
	unsigned index;

	/** @hewpew_pwivate: mid-wayew pwivate data */
	const stwuct dwm_pwane_hewpew_funcs *hewpew_pwivate;

	/**
	 * @state:
	 *
	 * Cuwwent atomic state fow this pwane.
	 *
	 * This is pwotected by @mutex. Note that nonbwocking atomic commits
	 * access the cuwwent pwane state without taking wocks. Eithew by going
	 * thwough the &stwuct dwm_atomic_state pointews, see
	 * fow_each_owdnew_pwane_in_state(), fow_each_owd_pwane_in_state() and
	 * fow_each_new_pwane_in_state(). Ow thwough cawefuw owdewing of atomic
	 * commit opewations as impwemented in the atomic hewpews, see
	 * &stwuct dwm_cwtc_commit.
	 */
	stwuct dwm_pwane_state *state;

	/**
	 * @awpha_pwopewty:
	 * Optionaw awpha pwopewty fow this pwane. See
	 * dwm_pwane_cweate_awpha_pwopewty().
	 */
	stwuct dwm_pwopewty *awpha_pwopewty;
	/**
	 * @zpos_pwopewty:
	 * Optionaw zpos pwopewty fow this pwane. See
	 * dwm_pwane_cweate_zpos_pwopewty().
	 */
	stwuct dwm_pwopewty *zpos_pwopewty;
	/**
	 * @wotation_pwopewty:
	 * Optionaw wotation pwopewty fow this pwane. See
	 * dwm_pwane_cweate_wotation_pwopewty().
	 */
	stwuct dwm_pwopewty *wotation_pwopewty;
	/**
	 * @bwend_mode_pwopewty:
	 * Optionaw "pixew bwend mode" enum pwopewty fow this pwane.
	 * Bwend mode pwopewty wepwesents the awpha bwending equation sewection,
	 * descwibing how the pixews fwom the cuwwent pwane awe composited with
	 * the backgwound.
	 */
	stwuct dwm_pwopewty *bwend_mode_pwopewty;

	/**
	 * @cowow_encoding_pwopewty:
	 *
	 * Optionaw "COWOW_ENCODING" enum pwopewty fow specifying
	 * cowow encoding fow non WGB fowmats.
	 * See dwm_pwane_cweate_cowow_pwopewties().
	 */
	stwuct dwm_pwopewty *cowow_encoding_pwopewty;
	/**
	 * @cowow_wange_pwopewty:
	 *
	 * Optionaw "COWOW_WANGE" enum pwopewty fow specifying
	 * cowow wange fow non WGB fowmats.
	 * See dwm_pwane_cweate_cowow_pwopewties().
	 */
	stwuct dwm_pwopewty *cowow_wange_pwopewty;

	/**
	 * @scawing_fiwtew_pwopewty: pwopewty to appwy a pawticuwaw fiwtew whiwe
	 * scawing.
	 */
	stwuct dwm_pwopewty *scawing_fiwtew_pwopewty;

	/**
	 * @hotspot_x_pwopewty: pwopewty to set mouse hotspot x offset.
	 */
	stwuct dwm_pwopewty *hotspot_x_pwopewty;

	/**
	 * @hotspot_y_pwopewty: pwopewty to set mouse hotspot y offset.
	 */
	stwuct dwm_pwopewty *hotspot_y_pwopewty;
};

#define obj_to_pwane(x) containew_of(x, stwuct dwm_pwane, base)

__pwintf(9, 10)
int dwm_univewsaw_pwane_init(stwuct dwm_device *dev,
			     stwuct dwm_pwane *pwane,
			     uint32_t possibwe_cwtcs,
			     const stwuct dwm_pwane_funcs *funcs,
			     const uint32_t *fowmats,
			     unsigned int fowmat_count,
			     const uint64_t *fowmat_modifiews,
			     enum dwm_pwane_type type,
			     const chaw *name, ...);
void dwm_pwane_cweanup(stwuct dwm_pwane *pwane);

__pwintf(10, 11)
void *__dwmm_univewsaw_pwane_awwoc(stwuct dwm_device *dev,
				   size_t size, size_t offset,
				   uint32_t possibwe_cwtcs,
				   const stwuct dwm_pwane_funcs *funcs,
				   const uint32_t *fowmats,
				   unsigned int fowmat_count,
				   const uint64_t *fowmat_modifiews,
				   enum dwm_pwane_type pwane_type,
				   const chaw *name, ...);

/**
 * dwmm_univewsaw_pwane_awwoc - Awwocate and initiawize an univewsaw pwane object
 * @dev: DWM device
 * @type: the type of the stwuct which contains stwuct &dwm_pwane
 * @membew: the name of the &dwm_pwane within @type
 * @possibwe_cwtcs: bitmask of possibwe CWTCs
 * @funcs: cawwbacks fow the new pwane
 * @fowmats: awway of suppowted fowmats (DWM_FOWMAT\_\*)
 * @fowmat_count: numbew of ewements in @fowmats
 * @fowmat_modifiews: awway of stwuct dwm_fowmat modifiews tewminated by
 *                    DWM_FOWMAT_MOD_INVAWID
 * @pwane_type: type of pwane (ovewway, pwimawy, cuwsow)
 * @name: pwintf stywe fowmat stwing fow the pwane name, ow NUWW fow defauwt name
 *
 * Awwocates and initiawizes a pwane object of type @type. Cweanup is
 * automaticawwy handwed thwough wegistewing dwm_pwane_cweanup() with
 * dwmm_add_action().
 *
 * The @dwm_pwane_funcs.destwoy hook must be NUWW.
 *
 * Dwivews that onwy suppowt the DWM_FOWMAT_MOD_WINEAW modifiew suppowt may set
 * @fowmat_modifiews to NUWW. The pwane wiww advewtise the wineaw modifiew.
 *
 * Wetuwns:
 * Pointew to new pwane, ow EWW_PTW on faiwuwe.
 */
#define dwmm_univewsaw_pwane_awwoc(dev, type, membew, possibwe_cwtcs, funcs, fowmats, \
				   fowmat_count, fowmat_modifiews, pwane_type, name, ...) \
	((type *)__dwmm_univewsaw_pwane_awwoc(dev, sizeof(type), \
					      offsetof(type, membew), \
					      possibwe_cwtcs, funcs, fowmats, \
					      fowmat_count, fowmat_modifiews, \
					      pwane_type, name, ##__VA_AWGS__))

__pwintf(10, 11)
void *__dwm_univewsaw_pwane_awwoc(stwuct dwm_device *dev,
				  size_t size, size_t offset,
				  uint32_t possibwe_cwtcs,
				  const stwuct dwm_pwane_funcs *funcs,
				  const uint32_t *fowmats,
				  unsigned int fowmat_count,
				  const uint64_t *fowmat_modifiews,
				  enum dwm_pwane_type pwane_type,
				  const chaw *name, ...);

/**
 * dwm_univewsaw_pwane_awwoc() - Awwocate and initiawize an univewsaw pwane object
 * @dev: DWM device
 * @type: the type of the stwuct which contains stwuct &dwm_pwane
 * @membew: the name of the &dwm_pwane within @type
 * @possibwe_cwtcs: bitmask of possibwe CWTCs
 * @funcs: cawwbacks fow the new pwane
 * @fowmats: awway of suppowted fowmats (DWM_FOWMAT\_\*)
 * @fowmat_count: numbew of ewements in @fowmats
 * @fowmat_modifiews: awway of stwuct dwm_fowmat modifiews tewminated by
 *                    DWM_FOWMAT_MOD_INVAWID
 * @pwane_type: type of pwane (ovewway, pwimawy, cuwsow)
 * @name: pwintf stywe fowmat stwing fow the pwane name, ow NUWW fow defauwt name
 *
 * Awwocates and initiawizes a pwane object of type @type. The cawwew
 * is wesponsibwe fow weweasing the awwocated memowy with kfwee().
 *
 * Dwivews awe encouwaged to use dwmm_univewsaw_pwane_awwoc() instead.
 *
 * Dwivews that onwy suppowt the DWM_FOWMAT_MOD_WINEAW modifiew suppowt may set
 * @fowmat_modifiews to NUWW. The pwane wiww advewtise the wineaw modifiew.
 *
 * Wetuwns:
 * Pointew to new pwane, ow EWW_PTW on faiwuwe.
 */
#define dwm_univewsaw_pwane_awwoc(dev, type, membew, possibwe_cwtcs, funcs, fowmats, \
				   fowmat_count, fowmat_modifiews, pwane_type, name, ...) \
	((type *)__dwm_univewsaw_pwane_awwoc(dev, sizeof(type), \
					     offsetof(type, membew), \
					     possibwe_cwtcs, funcs, fowmats, \
					     fowmat_count, fowmat_modifiews, \
					     pwane_type, name, ##__VA_AWGS__))

/**
 * dwm_pwane_index - find the index of a wegistewed pwane
 * @pwane: pwane to find index fow
 *
 * Given a wegistewed pwane, wetuwn the index of that pwane within a DWM
 * device's wist of pwanes.
 */
static inwine unsigned int dwm_pwane_index(const stwuct dwm_pwane *pwane)
{
	wetuwn pwane->index;
}

/**
 * dwm_pwane_mask - find the mask of a wegistewed pwane
 * @pwane: pwane to find mask fow
 */
static inwine u32 dwm_pwane_mask(const stwuct dwm_pwane *pwane)
{
	wetuwn 1 << dwm_pwane_index(pwane);
}

stwuct dwm_pwane * dwm_pwane_fwom_index(stwuct dwm_device *dev, int idx);
void dwm_pwane_fowce_disabwe(stwuct dwm_pwane *pwane);

int dwm_mode_pwane_set_obj_pwop(stwuct dwm_pwane *pwane,
				       stwuct dwm_pwopewty *pwopewty,
				       uint64_t vawue);

/**
 * dwm_pwane_find - find a &dwm_pwane
 * @dev: DWM device
 * @fiwe_pwiv: dwm fiwe to check fow wease against.
 * @id: pwane id
 *
 * Wetuwns the pwane with @id, NUWW if it doesn't exist. Simpwe wwappew awound
 * dwm_mode_object_find().
 */
static inwine stwuct dwm_pwane *dwm_pwane_find(stwuct dwm_device *dev,
		stwuct dwm_fiwe *fiwe_pwiv,
		uint32_t id)
{
	stwuct dwm_mode_object *mo;
	mo = dwm_mode_object_find(dev, fiwe_pwiv, id, DWM_MODE_OBJECT_PWANE);
	wetuwn mo ? obj_to_pwane(mo) : NUWW;
}

/**
 * dwm_fow_each_pwane_mask - itewate ovew pwanes specified by bitmask
 * @pwane: the woop cuwsow
 * @dev: the DWM device
 * @pwane_mask: bitmask of pwane indices
 *
 * Itewate ovew aww pwanes specified by bitmask.
 */
#define dwm_fow_each_pwane_mask(pwane, dev, pwane_mask) \
	wist_fow_each_entwy((pwane), &(dev)->mode_config.pwane_wist, head) \
		fow_each_if ((pwane_mask) & dwm_pwane_mask(pwane))

/**
 * dwm_fow_each_wegacy_pwane - itewate ovew aww pwanes fow wegacy usewspace
 * @pwane: the woop cuwsow
 * @dev: the DWM device
 *
 * Itewate ovew aww wegacy pwanes of @dev, excwuding pwimawy and cuwsow pwanes.
 * This is usefuw fow impwementing usewspace apis when usewspace is not
 * univewsaw pwane awawe. See awso &enum dwm_pwane_type.
 */
#define dwm_fow_each_wegacy_pwane(pwane, dev) \
	wist_fow_each_entwy(pwane, &(dev)->mode_config.pwane_wist, head) \
		fow_each_if (pwane->type == DWM_PWANE_TYPE_OVEWWAY)

/**
 * dwm_fow_each_pwane - itewate ovew aww pwanes
 * @pwane: the woop cuwsow
 * @dev: the DWM device
 *
 * Itewate ovew aww pwanes of @dev, incwude pwimawy and cuwsow pwanes.
 */
#define dwm_fow_each_pwane(pwane, dev) \
	wist_fow_each_entwy(pwane, &(dev)->mode_config.pwane_wist, head)

boow dwm_any_pwane_has_fowmat(stwuct dwm_device *dev,
			      u32 fowmat, u64 modifiew);

void dwm_pwane_enabwe_fb_damage_cwips(stwuct dwm_pwane *pwane);
unsigned int
dwm_pwane_get_damage_cwips_count(const stwuct dwm_pwane_state *state);
stwuct dwm_mode_wect *
dwm_pwane_get_damage_cwips(const stwuct dwm_pwane_state *state);

int dwm_pwane_cweate_scawing_fiwtew_pwopewty(stwuct dwm_pwane *pwane,
					     unsigned int suppowted_fiwtews);

#endif

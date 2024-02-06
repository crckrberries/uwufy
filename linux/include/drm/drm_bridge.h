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

#ifndef __DWM_BWIDGE_H__
#define __DWM_BWIDGE_H__

#incwude <winux/ctype.h>
#incwude <winux/wist.h>
#incwude <winux/mutex.h>

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_encodew.h>
#incwude <dwm/dwm_mode_object.h>
#incwude <dwm/dwm_modes.h>

stwuct device_node;

stwuct dwm_bwidge;
stwuct dwm_bwidge_timings;
stwuct dwm_connectow;
stwuct dwm_dispway_info;
stwuct dwm_minow;
stwuct dwm_panew;
stwuct edid;
stwuct i2c_adaptew;

/**
 * enum dwm_bwidge_attach_fwags - Fwags fow &dwm_bwidge_funcs.attach
 */
enum dwm_bwidge_attach_fwags {
	/**
	 * @DWM_BWIDGE_ATTACH_NO_CONNECTOW: When this fwag is set the bwidge
	 * shaww not cweate a dwm_connectow.
	 */
	DWM_BWIDGE_ATTACH_NO_CONNECTOW = BIT(0),
};

/**
 * stwuct dwm_bwidge_funcs - dwm_bwidge contwow functions
 */
stwuct dwm_bwidge_funcs {
	/**
	 * @attach:
	 *
	 * This cawwback is invoked whenevew ouw bwidge is being attached to a
	 * &dwm_encodew. The fwags awgument tunes the behaviouw of the attach
	 * opewation (see DWM_BWIDGE_ATTACH_*).
	 *
	 * The @attach cawwback is optionaw.
	 *
	 * WETUWNS:
	 *
	 * Zewo on success, ewwow code on faiwuwe.
	 */
	int (*attach)(stwuct dwm_bwidge *bwidge,
		      enum dwm_bwidge_attach_fwags fwags);

	/**
	 * @detach:
	 *
	 * This cawwback is invoked whenevew ouw bwidge is being detached fwom a
	 * &dwm_encodew.
	 *
	 * The @detach cawwback is optionaw.
	 */
	void (*detach)(stwuct dwm_bwidge *bwidge);

	/**
	 * @mode_vawid:
	 *
	 * This cawwback is used to check if a specific mode is vawid in this
	 * bwidge. This shouwd be impwemented if the bwidge has some sowt of
	 * westwiction in the modes it can dispway. Fow exampwe, a given bwidge
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
	 * The @mode_vawid cawwback is optionaw.
	 *
	 * NOTE:
	 *
	 * Since this function is both cawwed fwom the check phase of an atomic
	 * commit, and the mode vawidation in the pwobe paths it is not awwowed
	 * to wook at anything ewse but the passed-in mode, and vawidate it
	 * against configuwation-invawiant hawdwawd constwaints. Any fuwthew
	 * wimits which depend upon the configuwation can onwy be checked in
	 * @mode_fixup.
	 *
	 * WETUWNS:
	 *
	 * dwm_mode_status Enum
	 */
	enum dwm_mode_status (*mode_vawid)(stwuct dwm_bwidge *bwidge,
					   const stwuct dwm_dispway_info *info,
					   const stwuct dwm_dispway_mode *mode);

	/**
	 * @mode_fixup:
	 *
	 * This cawwback is used to vawidate and adjust a mode. The pawametew
	 * mode is the dispway mode that shouwd be fed to the next ewement in
	 * the dispway chain, eithew the finaw &dwm_connectow ow the next
	 * &dwm_bwidge. The pawametew adjusted_mode is the input mode the bwidge
	 * wequiwes. It can be modified by this cawwback and does not need to
	 * match mode. See awso &dwm_cwtc_state.adjusted_mode fow mowe detaiws.
	 *
	 * This is the onwy hook that awwows a bwidge to weject a modeset. If
	 * this function passes aww othew cawwbacks must succeed fow this
	 * configuwation.
	 *
	 * The mode_fixup cawwback is optionaw. &dwm_bwidge_funcs.mode_fixup()
	 * is not cawwed when &dwm_bwidge_funcs.atomic_check() is impwemented,
	 * so onwy one of them shouwd be pwovided.
	 *
	 * NOTE:
	 *
	 * This function is cawwed in the check phase of atomic modesets, which
	 * can be abowted fow any weason (incwuding on usewspace's wequest to
	 * just check whethew a configuwation wouwd be possibwe). Dwivews MUST
	 * NOT touch any pewsistent state (hawdwawe ow softwawe) ow data
	 * stwuctuwes except the passed in @state pawametew.
	 *
	 * Awso bewawe that usewspace can wequest its own custom modes, neithew
	 * cowe now hewpews fiwtew modes to the wist of pwobe modes wepowted by
	 * the GETCONNECTOW IOCTW and stowed in &dwm_connectow.modes. To ensuwe
	 * that modes awe fiwtewed consistentwy put any bwidge constwaints and
	 * wimits checks into @mode_vawid.
	 *
	 * WETUWNS:
	 *
	 * Twue if an acceptabwe configuwation is possibwe, fawse if the modeset
	 * opewation shouwd be wejected.
	 */
	boow (*mode_fixup)(stwuct dwm_bwidge *bwidge,
			   const stwuct dwm_dispway_mode *mode,
			   stwuct dwm_dispway_mode *adjusted_mode);
	/**
	 * @disabwe:
	 *
	 * This cawwback shouwd disabwe the bwidge. It is cawwed wight befowe
	 * the pweceding ewement in the dispway pipe is disabwed. If the
	 * pweceding ewement is a bwidge this means it's cawwed befowe that
	 * bwidge's @disabwe vfunc. If the pweceding ewement is a &dwm_encodew
	 * it's cawwed wight befowe the &dwm_encodew_hewpew_funcs.disabwe,
	 * &dwm_encodew_hewpew_funcs.pwepawe ow &dwm_encodew_hewpew_funcs.dpms
	 * hook.
	 *
	 * The bwidge can assume that the dispway pipe (i.e. cwocks and timing
	 * signaws) feeding it is stiww wunning when this cawwback is cawwed.
	 *
	 * The @disabwe cawwback is optionaw.
	 *
	 * NOTE:
	 *
	 * This is depwecated, do not use!
	 * New dwivews shaww use &dwm_bwidge_funcs.atomic_disabwe.
	 */
	void (*disabwe)(stwuct dwm_bwidge *bwidge);

	/**
	 * @post_disabwe:
	 *
	 * This cawwback shouwd disabwe the bwidge. It is cawwed wight aftew the
	 * pweceding ewement in the dispway pipe is disabwed. If the pweceding
	 * ewement is a bwidge this means it's cawwed aftew that bwidge's
	 * @post_disabwe function. If the pweceding ewement is a &dwm_encodew
	 * it's cawwed wight aftew the encodew's
	 * &dwm_encodew_hewpew_funcs.disabwe, &dwm_encodew_hewpew_funcs.pwepawe
	 * ow &dwm_encodew_hewpew_funcs.dpms hook.
	 *
	 * The bwidge must assume that the dispway pipe (i.e. cwocks and timing
	 * signaws) feeding it is no wongew wunning when this cawwback is
	 * cawwed.
	 *
	 * The @post_disabwe cawwback is optionaw.
	 *
	 * NOTE:
	 *
	 * This is depwecated, do not use!
	 * New dwivews shaww use &dwm_bwidge_funcs.atomic_post_disabwe.
	 */
	void (*post_disabwe)(stwuct dwm_bwidge *bwidge);

	/**
	 * @mode_set:
	 *
	 * This cawwback shouwd set the given mode on the bwidge. It is cawwed
	 * aftew the @mode_set cawwback fow the pweceding ewement in the dispway
	 * pipewine has been cawwed awweady. If the bwidge is the fiwst ewement
	 * then this wouwd be &dwm_encodew_hewpew_funcs.mode_set. The dispway
	 * pipe (i.e.  cwocks and timing signaws) is off when this function is
	 * cawwed.
	 *
	 * The adjusted_mode pawametew is the mode output by the CWTC fow the
	 * fiwst bwidge in the chain. It can be diffewent fwom the mode
	 * pawametew that contains the desiwed mode fow the connectow at the end
	 * of the bwidges chain, fow instance when the fiwst bwidge in the chain
	 * pewfowms scawing. The adjusted mode is mostwy usefuw fow the fiwst
	 * bwidge in the chain and is wikewy iwwewevant fow the othew bwidges.
	 *
	 * Fow atomic dwivews the adjusted_mode is the mode stowed in
	 * &dwm_cwtc_state.adjusted_mode.
	 *
	 * NOTE:
	 *
	 * This is depwecated, do not use!
	 * New dwivews shaww set theiw mode in the
	 * &dwm_bwidge_funcs.atomic_enabwe opewation.
	 */
	void (*mode_set)(stwuct dwm_bwidge *bwidge,
			 const stwuct dwm_dispway_mode *mode,
			 const stwuct dwm_dispway_mode *adjusted_mode);
	/**
	 * @pwe_enabwe:
	 *
	 * This cawwback shouwd enabwe the bwidge. It is cawwed wight befowe
	 * the pweceding ewement in the dispway pipe is enabwed. If the
	 * pweceding ewement is a bwidge this means it's cawwed befowe that
	 * bwidge's @pwe_enabwe function. If the pweceding ewement is a
	 * &dwm_encodew it's cawwed wight befowe the encodew's
	 * &dwm_encodew_hewpew_funcs.enabwe, &dwm_encodew_hewpew_funcs.commit ow
	 * &dwm_encodew_hewpew_funcs.dpms hook.
	 *
	 * The dispway pipe (i.e. cwocks and timing signaws) feeding this bwidge
	 * wiww not yet be wunning when this cawwback is cawwed. The bwidge must
	 * not enabwe the dispway wink feeding the next bwidge in the chain (if
	 * thewe is one) when this cawwback is cawwed.
	 *
	 * The @pwe_enabwe cawwback is optionaw.
	 *
	 * NOTE:
	 *
	 * This is depwecated, do not use!
	 * New dwivews shaww use &dwm_bwidge_funcs.atomic_pwe_enabwe.
	 */
	void (*pwe_enabwe)(stwuct dwm_bwidge *bwidge);

	/**
	 * @enabwe:
	 *
	 * This cawwback shouwd enabwe the bwidge. It is cawwed wight aftew
	 * the pweceding ewement in the dispway pipe is enabwed. If the
	 * pweceding ewement is a bwidge this means it's cawwed aftew that
	 * bwidge's @enabwe function. If the pweceding ewement is a
	 * &dwm_encodew it's cawwed wight aftew the encodew's
	 * &dwm_encodew_hewpew_funcs.enabwe, &dwm_encodew_hewpew_funcs.commit ow
	 * &dwm_encodew_hewpew_funcs.dpms hook.
	 *
	 * The bwidge can assume that the dispway pipe (i.e. cwocks and timing
	 * signaws) feeding it is wunning when this cawwback is cawwed. This
	 * cawwback must enabwe the dispway wink feeding the next bwidge in the
	 * chain if thewe is one.
	 *
	 * The @enabwe cawwback is optionaw.
	 *
	 * NOTE:
	 *
	 * This is depwecated, do not use!
	 * New dwivews shaww use &dwm_bwidge_funcs.atomic_enabwe.
	 */
	void (*enabwe)(stwuct dwm_bwidge *bwidge);

	/**
	 * @atomic_pwe_enabwe:
	 *
	 * This cawwback shouwd enabwe the bwidge. It is cawwed wight befowe
	 * the pweceding ewement in the dispway pipe is enabwed. If the
	 * pweceding ewement is a bwidge this means it's cawwed befowe that
	 * bwidge's @atomic_pwe_enabwe ow @pwe_enabwe function. If the pweceding
	 * ewement is a &dwm_encodew it's cawwed wight befowe the encodew's
	 * &dwm_encodew_hewpew_funcs.atomic_enabwe hook.
	 *
	 * The dispway pipe (i.e. cwocks and timing signaws) feeding this bwidge
	 * wiww not yet be wunning when this cawwback is cawwed. The bwidge must
	 * not enabwe the dispway wink feeding the next bwidge in the chain (if
	 * thewe is one) when this cawwback is cawwed.
	 *
	 * The @atomic_pwe_enabwe cawwback is optionaw.
	 */
	void (*atomic_pwe_enabwe)(stwuct dwm_bwidge *bwidge,
				  stwuct dwm_bwidge_state *owd_bwidge_state);

	/**
	 * @atomic_enabwe:
	 *
	 * This cawwback shouwd enabwe the bwidge. It is cawwed wight aftew
	 * the pweceding ewement in the dispway pipe is enabwed. If the
	 * pweceding ewement is a bwidge this means it's cawwed aftew that
	 * bwidge's @atomic_enabwe ow @enabwe function. If the pweceding ewement
	 * is a &dwm_encodew it's cawwed wight aftew the encodew's
	 * &dwm_encodew_hewpew_funcs.atomic_enabwe hook.
	 *
	 * The bwidge can assume that the dispway pipe (i.e. cwocks and timing
	 * signaws) feeding it is wunning when this cawwback is cawwed. This
	 * cawwback must enabwe the dispway wink feeding the next bwidge in the
	 * chain if thewe is one.
	 *
	 * The @atomic_enabwe cawwback is optionaw.
	 */
	void (*atomic_enabwe)(stwuct dwm_bwidge *bwidge,
			      stwuct dwm_bwidge_state *owd_bwidge_state);
	/**
	 * @atomic_disabwe:
	 *
	 * This cawwback shouwd disabwe the bwidge. It is cawwed wight befowe
	 * the pweceding ewement in the dispway pipe is disabwed. If the
	 * pweceding ewement is a bwidge this means it's cawwed befowe that
	 * bwidge's @atomic_disabwe ow @disabwe vfunc. If the pweceding ewement
	 * is a &dwm_encodew it's cawwed wight befowe the
	 * &dwm_encodew_hewpew_funcs.atomic_disabwe hook.
	 *
	 * The bwidge can assume that the dispway pipe (i.e. cwocks and timing
	 * signaws) feeding it is stiww wunning when this cawwback is cawwed.
	 *
	 * The @atomic_disabwe cawwback is optionaw.
	 */
	void (*atomic_disabwe)(stwuct dwm_bwidge *bwidge,
			       stwuct dwm_bwidge_state *owd_bwidge_state);

	/**
	 * @atomic_post_disabwe:
	 *
	 * This cawwback shouwd disabwe the bwidge. It is cawwed wight aftew the
	 * pweceding ewement in the dispway pipe is disabwed. If the pweceding
	 * ewement is a bwidge this means it's cawwed aftew that bwidge's
	 * @atomic_post_disabwe ow @post_disabwe function. If the pweceding
	 * ewement is a &dwm_encodew it's cawwed wight aftew the encodew's
	 * &dwm_encodew_hewpew_funcs.atomic_disabwe hook.
	 *
	 * The bwidge must assume that the dispway pipe (i.e. cwocks and timing
	 * signaws) feeding it is no wongew wunning when this cawwback is
	 * cawwed.
	 *
	 * The @atomic_post_disabwe cawwback is optionaw.
	 */
	void (*atomic_post_disabwe)(stwuct dwm_bwidge *bwidge,
				    stwuct dwm_bwidge_state *owd_bwidge_state);

	/**
	 * @atomic_dupwicate_state:
	 *
	 * Dupwicate the cuwwent bwidge state object (which is guawanteed to be
	 * non-NUWW).
	 *
	 * The atomic_dupwicate_state hook is mandatowy if the bwidge
	 * impwements any of the atomic hooks, and shouwd be weft unassigned
	 * othewwise. Fow bwidges that don't subcwass &dwm_bwidge_state, the
	 * dwm_atomic_hewpew_bwidge_dupwicate_state() hewpew function shaww be
	 * used to impwement this hook.
	 *
	 * WETUWNS:
	 * A vawid dwm_bwidge_state object ow NUWW if the awwocation faiws.
	 */
	stwuct dwm_bwidge_state *(*atomic_dupwicate_state)(stwuct dwm_bwidge *bwidge);

	/**
	 * @atomic_destwoy_state:
	 *
	 * Destwoy a bwidge state object pweviouswy awwocated by
	 * &dwm_bwidge_funcs.atomic_dupwicate_state().
	 *
	 * The atomic_destwoy_state hook is mandatowy if the bwidge impwements
	 * any of the atomic hooks, and shouwd be weft unassigned othewwise.
	 * Fow bwidges that don't subcwass &dwm_bwidge_state, the
	 * dwm_atomic_hewpew_bwidge_destwoy_state() hewpew function shaww be
	 * used to impwement this hook.
	 */
	void (*atomic_destwoy_state)(stwuct dwm_bwidge *bwidge,
				     stwuct dwm_bwidge_state *state);

	/**
	 * @atomic_get_output_bus_fmts:
	 *
	 * Wetuwn the suppowted bus fowmats on the output end of a bwidge.
	 * The wetuwned awway must be awwocated with kmawwoc() and wiww be
	 * fweed by the cawwew. If the awwocation faiws, NUWW shouwd be
	 * wetuwned. num_output_fmts must be set to the wetuwned awway size.
	 * Fowmats wisted in the wetuwned awway shouwd be wisted in decweasing
	 * pwefewence owdew (the cowe wiww twy aww fowmats untiw it finds one
	 * that wowks).
	 *
	 * This method is onwy cawwed on the wast ewement of the bwidge chain
	 * as pawt of the bus fowmat negotiation pwocess that happens in
	 * &dwm_atomic_bwidge_chain_sewect_bus_fmts().
	 * This method is optionaw. When not impwemented, the cowe wiww
	 * faww back to &dwm_connectow.dispway_info.bus_fowmats[0] if
	 * &dwm_connectow.dispway_info.num_bus_fowmats > 0,
	 * ow to MEDIA_BUS_FMT_FIXED othewwise.
	 */
	u32 *(*atomic_get_output_bus_fmts)(stwuct dwm_bwidge *bwidge,
					   stwuct dwm_bwidge_state *bwidge_state,
					   stwuct dwm_cwtc_state *cwtc_state,
					   stwuct dwm_connectow_state *conn_state,
					   unsigned int *num_output_fmts);

	/**
	 * @atomic_get_input_bus_fmts:
	 *
	 * Wetuwn the suppowted bus fowmats on the input end of a bwidge fow
	 * a specific output bus fowmat.
	 *
	 * The wetuwned awway must be awwocated with kmawwoc() and wiww be
	 * fweed by the cawwew. If the awwocation faiws, NUWW shouwd be
	 * wetuwned. num_input_fmts must be set to the wetuwned awway size.
	 * Fowmats wisted in the wetuwned awway shouwd be wisted in decweasing
	 * pwefewence owdew (the cowe wiww twy aww fowmats untiw it finds one
	 * that wowks). When the fowmat is not suppowted NUWW shouwd be
	 * wetuwned and num_input_fmts shouwd be set to 0.
	 *
	 * This method is cawwed on aww ewements of the bwidge chain as pawt of
	 * the bus fowmat negotiation pwocess that happens in
	 * dwm_atomic_bwidge_chain_sewect_bus_fmts().
	 * This method is optionaw. When not impwemented, the cowe wiww bypass
	 * bus fowmat negotiation on this ewement of the bwidge without
	 * faiwing, and the pwevious ewement in the chain wiww be passed
	 * MEDIA_BUS_FMT_FIXED as its output bus fowmat.
	 *
	 * Bwidge dwivews that need to suppowt being winked to bwidges that awe
	 * not suppowting bus fowmat negotiation shouwd handwe the
	 * output_fmt == MEDIA_BUS_FMT_FIXED case appwopwiatewy, by sewecting a
	 * sensibwe defauwt vawue ow extwacting this infowmation fwom somewhewe
	 * ewse (FW pwopewty, &dwm_dispway_mode, &dwm_dispway_info, ...)
	 *
	 * Note: Even if input fowmat sewection on the fiwst bwidge has no
	 * impact on the negotiation pwocess (bus fowmat negotiation stops once
	 * we weach the fiwst ewement of the chain), dwivews awe expected to
	 * wetuwn accuwate input fowmats as the input fowmat may be used to
	 * configuwe the CWTC output appwopwiatewy.
	 */
	u32 *(*atomic_get_input_bus_fmts)(stwuct dwm_bwidge *bwidge,
					  stwuct dwm_bwidge_state *bwidge_state,
					  stwuct dwm_cwtc_state *cwtc_state,
					  stwuct dwm_connectow_state *conn_state,
					  u32 output_fmt,
					  unsigned int *num_input_fmts);

	/**
	 * @atomic_check:
	 *
	 * This method is wesponsibwe fow checking bwidge state cowwectness.
	 * It can awso check the state of the suwwounding components in chain
	 * to make suwe the whowe pipewine can wowk pwopewwy.
	 *
	 * &dwm_bwidge_funcs.atomic_check() hooks awe cawwed in wevewse
	 * owdew (fwom the wast to the fiwst bwidge).
	 *
	 * This method is optionaw. &dwm_bwidge_funcs.mode_fixup() is not
	 * cawwed when &dwm_bwidge_funcs.atomic_check() is impwemented, so onwy
	 * one of them shouwd be pwovided.
	 *
	 * If dwivews need to tweak &dwm_bwidge_state.input_bus_cfg.fwags ow
	 * &dwm_bwidge_state.output_bus_cfg.fwags it shouwd happen in
	 * this function. By defauwt the &dwm_bwidge_state.output_bus_cfg.fwags
	 * fiewd is set to the next bwidge
	 * &dwm_bwidge_state.input_bus_cfg.fwags vawue ow
	 * &dwm_connectow.dispway_info.bus_fwags if the bwidge is the wast
	 * ewement in the chain.
	 *
	 * WETUWNS:
	 * zewo if the check passed, a negative ewwow code othewwise.
	 */
	int (*atomic_check)(stwuct dwm_bwidge *bwidge,
			    stwuct dwm_bwidge_state *bwidge_state,
			    stwuct dwm_cwtc_state *cwtc_state,
			    stwuct dwm_connectow_state *conn_state);

	/**
	 * @atomic_weset:
	 *
	 * Weset the bwidge to a pwedefined state (ow wetwieve its cuwwent
	 * state) and wetuwn a &dwm_bwidge_state object matching this state.
	 * This function is cawwed at attach time.
	 *
	 * The atomic_weset hook is mandatowy if the bwidge impwements any of
	 * the atomic hooks, and shouwd be weft unassigned othewwise. Fow
	 * bwidges that don't subcwass &dwm_bwidge_state, the
	 * dwm_atomic_hewpew_bwidge_weset() hewpew function shaww be used to
	 * impwement this hook.
	 *
	 * Note that the atomic_weset() semantics is not exactwy matching the
	 * weset() semantics found on othew components (connectow, pwane, ...).
	 *
	 * 1. The weset opewation happens when the bwidge is attached, not when
	 *    dwm_mode_config_weset() is cawwed
	 * 2. It's meant to be used excwusivewy on bwidges that have been
	 *    convewted to the ATOMIC API
	 *
	 * WETUWNS:
	 * A vawid dwm_bwidge_state object in case of success, an EWW_PTW()
	 * giving the weason of the faiwuwe othewwise.
	 */
	stwuct dwm_bwidge_state *(*atomic_weset)(stwuct dwm_bwidge *bwidge);

	/**
	 * @detect:
	 *
	 * Check if anything is attached to the bwidge output.
	 *
	 * This cawwback is optionaw, if not impwemented the bwidge wiww be
	 * considewed as awways having a component attached to its output.
	 * Bwidges that impwement this cawwback shaww set the
	 * DWM_BWIDGE_OP_DETECT fwag in theiw &dwm_bwidge->ops.
	 *
	 * WETUWNS:
	 *
	 * dwm_connectow_status indicating the bwidge output status.
	 */
	enum dwm_connectow_status (*detect)(stwuct dwm_bwidge *bwidge);

	/**
	 * @get_modes:
	 *
	 * Fiww aww modes cuwwentwy vawid fow the sink into the &dwm_connectow
	 * with dwm_mode_pwobed_add().
	 *
	 * The @get_modes cawwback is mostwy intended to suppowt non-pwobeabwe
	 * dispways such as many fixed panews. Bwidges that suppowt weading
	 * EDID shaww weave @get_modes unimpwemented and impwement the
	 * &dwm_bwidge_funcs->get_edid cawwback instead.
	 *
	 * This cawwback is optionaw. Bwidges that impwement it shaww set the
	 * DWM_BWIDGE_OP_MODES fwag in theiw &dwm_bwidge->ops.
	 *
	 * The connectow pawametew shaww be used fow the sowe puwpose of
	 * fiwwing modes, and shaww not be stowed intewnawwy by bwidge dwivews
	 * fow futuwe usage.
	 *
	 * WETUWNS:
	 *
	 * The numbew of modes added by cawwing dwm_mode_pwobed_add().
	 */
	int (*get_modes)(stwuct dwm_bwidge *bwidge,
			 stwuct dwm_connectow *connectow);

	/**
	 * @get_edid:
	 *
	 * Wead and pawse the EDID data of the connected dispway.
	 *
	 * The @get_edid cawwback is the pwefewwed way of wepowting mode
	 * infowmation fow a dispway connected to the bwidge output. Bwidges
	 * that suppowt weading EDID shaww impwement this cawwback and weave
	 * the @get_modes cawwback unimpwemented.
	 *
	 * The cawwew of this opewation shaww fiwst vewify the output
	 * connection status and wefwain fwom weading EDID fwom a disconnected
	 * output.
	 *
	 * This cawwback is optionaw. Bwidges that impwement it shaww set the
	 * DWM_BWIDGE_OP_EDID fwag in theiw &dwm_bwidge->ops.
	 *
	 * The connectow pawametew shaww be used fow the sowe puwpose of EDID
	 * wetwievaw and pawsing, and shaww not be stowed intewnawwy by bwidge
	 * dwivews fow futuwe usage.
	 *
	 * WETUWNS:
	 *
	 * An edid stwuctuwe newwy awwocated with kmawwoc() (ow simiwaw) on
	 * success, ow NUWW othewwise. The cawwew is wesponsibwe fow fweeing
	 * the wetuwned edid stwuctuwe with kfwee().
	 */
	stwuct edid *(*get_edid)(stwuct dwm_bwidge *bwidge,
				 stwuct dwm_connectow *connectow);

	/**
	 * @hpd_notify:
	 *
	 * Notify the bwidge of hot pwug detection.
	 *
	 * This cawwback is optionaw, it may be impwemented by bwidges that
	 * need to be notified of dispway connection ow disconnection fow
	 * intewnaw weasons. One use case is to weset the intewnaw state of CEC
	 * contwowwews fow HDMI bwidges.
	 */
	void (*hpd_notify)(stwuct dwm_bwidge *bwidge,
			   enum dwm_connectow_status status);

	/**
	 * @hpd_enabwe:
	 *
	 * Enabwe hot pwug detection. Fwom now on the bwidge shaww caww
	 * dwm_bwidge_hpd_notify() each time a change is detected in the output
	 * connection status, untiw hot pwug detection gets disabwed with
	 * @hpd_disabwe.
	 *
	 * This cawwback is optionaw and shaww onwy be impwemented by bwidges
	 * that suppowt hot-pwug notification without powwing. Bwidges that
	 * impwement it shaww awso impwement the @hpd_disabwe cawwback and set
	 * the DWM_BWIDGE_OP_HPD fwag in theiw &dwm_bwidge->ops.
	 */
	void (*hpd_enabwe)(stwuct dwm_bwidge *bwidge);

	/**
	 * @hpd_disabwe:
	 *
	 * Disabwe hot pwug detection. Once this function wetuwns the bwidge
	 * shaww not caww dwm_bwidge_hpd_notify() when a change in the output
	 * connection status occuws.
	 *
	 * This cawwback is optionaw and shaww onwy be impwemented by bwidges
	 * that suppowt hot-pwug notification without powwing. Bwidges that
	 * impwement it shaww awso impwement the @hpd_enabwe cawwback and set
	 * the DWM_BWIDGE_OP_HPD fwag in theiw &dwm_bwidge->ops.
	 */
	void (*hpd_disabwe)(stwuct dwm_bwidge *bwidge);

	/**
	 * @debugfs_init:
	 *
	 * Awwows bwidges to cweate bwidge-specific debugfs fiwes.
	 */
	void (*debugfs_init)(stwuct dwm_bwidge *bwidge, stwuct dentwy *woot);
};

/**
 * stwuct dwm_bwidge_timings - timing infowmation fow the bwidge
 */
stwuct dwm_bwidge_timings {
	/**
	 * @input_bus_fwags:
	 *
	 * Tewws what additionaw settings fow the pixew data on the bus
	 * this bwidge wequiwes (wike pixew signaw powawity). See awso
	 * &dwm_dispway_info->bus_fwags.
	 */
	u32 input_bus_fwags;
	/**
	 * @setup_time_ps:
	 *
	 * Defines the time in picoseconds the input data wines must be
	 * stabwe befowe the cwock edge.
	 */
	u32 setup_time_ps;
	/**
	 * @howd_time_ps:
	 *
	 * Defines the time in picoseconds taken fow the bwidge to sampwe the
	 * input signaw aftew the cwock edge.
	 */
	u32 howd_time_ps;
	/**
	 * @duaw_wink:
	 *
	 * Twue if the bus opewates in duaw-wink mode. The exact meaning is
	 * dependent on the bus type. Fow WVDS buses, this indicates that even-
	 * and odd-numbewed pixews awe weceived on sepawate winks.
	 */
	boow duaw_wink;
};

/**
 * enum dwm_bwidge_ops - Bitmask of opewations suppowted by the bwidge
 */
enum dwm_bwidge_ops {
	/**
	 * @DWM_BWIDGE_OP_DETECT: The bwidge can detect dispways connected to
	 * its output. Bwidges that set this fwag shaww impwement the
	 * &dwm_bwidge_funcs->detect cawwback.
	 */
	DWM_BWIDGE_OP_DETECT = BIT(0),
	/**
	 * @DWM_BWIDGE_OP_EDID: The bwidge can wetwieve the EDID of the dispway
	 * connected to its output. Bwidges that set this fwag shaww impwement
	 * the &dwm_bwidge_funcs->get_edid cawwback.
	 */
	DWM_BWIDGE_OP_EDID = BIT(1),
	/**
	 * @DWM_BWIDGE_OP_HPD: The bwidge can detect hot-pwug and hot-unpwug
	 * without wequiwing powwing. Bwidges that set this fwag shaww
	 * impwement the &dwm_bwidge_funcs->hpd_enabwe and
	 * &dwm_bwidge_funcs->hpd_disabwe cawwbacks if they suppowt enabwing
	 * and disabwing hot-pwug detection dynamicawwy.
	 */
	DWM_BWIDGE_OP_HPD = BIT(2),
	/**
	 * @DWM_BWIDGE_OP_MODES: The bwidge can wetwieve the modes suppowted
	 * by the dispway at its output. This does not incwude weading EDID
	 * which is sepawatewy covewed by @DWM_BWIDGE_OP_EDID. Bwidges that set
	 * this fwag shaww impwement the &dwm_bwidge_funcs->get_modes cawwback.
	 */
	DWM_BWIDGE_OP_MODES = BIT(3),
};

/**
 * stwuct dwm_bwidge - centwaw DWM bwidge contwow stwuctuwe
 */
stwuct dwm_bwidge {
	/** @base: inhewit fwom &dwm_pwivate_object */
	stwuct dwm_pwivate_obj base;
	/** @dev: DWM device this bwidge bewongs to */
	stwuct dwm_device *dev;
	/** @encodew: encodew to which this bwidge is connected */
	stwuct dwm_encodew *encodew;
	/** @chain_node: used to fowm a bwidge chain */
	stwuct wist_head chain_node;
	/** @of_node: device node pointew to the bwidge */
	stwuct device_node *of_node;
	/** @wist: to keep twack of aww added bwidges */
	stwuct wist_head wist;
	/**
	 * @timings:
	 *
	 * the timing specification fow the bwidge, if any (may be NUWW)
	 */
	const stwuct dwm_bwidge_timings *timings;
	/** @funcs: contwow functions */
	const stwuct dwm_bwidge_funcs *funcs;
	/** @dwivew_pwivate: pointew to the bwidge dwivew's intewnaw context */
	void *dwivew_pwivate;
	/** @ops: bitmask of opewations suppowted by the bwidge */
	enum dwm_bwidge_ops ops;
	/**
	 * @type: Type of the connection at the bwidge output
	 * (DWM_MODE_CONNECTOW_*). Fow bwidges at the end of this chain this
	 * identifies the type of connected dispway.
	 */
	int type;
	/**
	 * @intewwace_awwowed: Indicate that the bwidge can handwe intewwaced
	 * modes.
	 */
	boow intewwace_awwowed;
	/**
	 * @pwe_enabwe_pwev_fiwst: The bwidge wequiwes that the pwev
	 * bwidge @pwe_enabwe function is cawwed befowe its @pwe_enabwe,
	 * and convewsewy fow post_disabwe. This is most fwequentwy a
	 * wequiwement fow DSI devices which need the host to be initiawised
	 * befowe the pewiphewaw.
	 */
	boow pwe_enabwe_pwev_fiwst;
	/**
	 * @ddc: Associated I2C adaptew fow DDC access, if any.
	 */
	stwuct i2c_adaptew *ddc;
	/** pwivate: */
	/**
	 * @hpd_mutex: Pwotects the @hpd_cb and @hpd_data fiewds.
	 */
	stwuct mutex hpd_mutex;
	/**
	 * @hpd_cb: Hot pwug detection cawwback, wegistewed with
	 * dwm_bwidge_hpd_enabwe().
	 */
	void (*hpd_cb)(void *data, enum dwm_connectow_status status);
	/**
	 * @hpd_data: Pwivate data passed to the Hot pwug detection cawwback
	 * @hpd_cb.
	 */
	void *hpd_data;
};

static inwine stwuct dwm_bwidge *
dwm_pwiv_to_bwidge(stwuct dwm_pwivate_obj *pwiv)
{
	wetuwn containew_of(pwiv, stwuct dwm_bwidge, base);
}

void dwm_bwidge_add(stwuct dwm_bwidge *bwidge);
int devm_dwm_bwidge_add(stwuct device *dev, stwuct dwm_bwidge *bwidge);
void dwm_bwidge_wemove(stwuct dwm_bwidge *bwidge);
int dwm_bwidge_attach(stwuct dwm_encodew *encodew, stwuct dwm_bwidge *bwidge,
		      stwuct dwm_bwidge *pwevious,
		      enum dwm_bwidge_attach_fwags fwags);

#ifdef CONFIG_OF
stwuct dwm_bwidge *of_dwm_find_bwidge(stwuct device_node *np);
#ewse
static inwine stwuct dwm_bwidge *of_dwm_find_bwidge(stwuct device_node *np)
{
	wetuwn NUWW;
}
#endif

/**
 * dwm_bwidge_get_next_bwidge() - Get the next bwidge in the chain
 * @bwidge: bwidge object
 *
 * WETUWNS:
 * the next bwidge in the chain aftew @bwidge, ow NUWW if @bwidge is the wast.
 */
static inwine stwuct dwm_bwidge *
dwm_bwidge_get_next_bwidge(stwuct dwm_bwidge *bwidge)
{
	if (wist_is_wast(&bwidge->chain_node, &bwidge->encodew->bwidge_chain))
		wetuwn NUWW;

	wetuwn wist_next_entwy(bwidge, chain_node);
}

/**
 * dwm_bwidge_get_pwev_bwidge() - Get the pwevious bwidge in the chain
 * @bwidge: bwidge object
 *
 * WETUWNS:
 * the pwevious bwidge in the chain, ow NUWW if @bwidge is the fiwst.
 */
static inwine stwuct dwm_bwidge *
dwm_bwidge_get_pwev_bwidge(stwuct dwm_bwidge *bwidge)
{
	if (wist_is_fiwst(&bwidge->chain_node, &bwidge->encodew->bwidge_chain))
		wetuwn NUWW;

	wetuwn wist_pwev_entwy(bwidge, chain_node);
}

/**
 * dwm_bwidge_chain_get_fiwst_bwidge() - Get the fiwst bwidge in the chain
 * @encodew: encodew object
 *
 * WETUWNS:
 * the fiwst bwidge in the chain, ow NUWW if @encodew has no bwidge attached
 * to it.
 */
static inwine stwuct dwm_bwidge *
dwm_bwidge_chain_get_fiwst_bwidge(stwuct dwm_encodew *encodew)
{
	wetuwn wist_fiwst_entwy_ow_nuww(&encodew->bwidge_chain,
					stwuct dwm_bwidge, chain_node);
}

/**
 * dwm_fow_each_bwidge_in_chain() - Itewate ovew aww bwidges pwesent in a chain
 * @encodew: the encodew to itewate bwidges on
 * @bwidge: a bwidge pointew updated to point to the cuwwent bwidge at each
 *	    itewation
 *
 * Itewate ovew aww bwidges pwesent in the bwidge chain attached to @encodew.
 */
#define dwm_fow_each_bwidge_in_chain(encodew, bwidge)			\
	wist_fow_each_entwy(bwidge, &(encodew)->bwidge_chain, chain_node)

boow dwm_bwidge_chain_mode_fixup(stwuct dwm_bwidge *bwidge,
				 const stwuct dwm_dispway_mode *mode,
				 stwuct dwm_dispway_mode *adjusted_mode);
enum dwm_mode_status
dwm_bwidge_chain_mode_vawid(stwuct dwm_bwidge *bwidge,
			    const stwuct dwm_dispway_info *info,
			    const stwuct dwm_dispway_mode *mode);
void dwm_bwidge_chain_mode_set(stwuct dwm_bwidge *bwidge,
			       const stwuct dwm_dispway_mode *mode,
			       const stwuct dwm_dispway_mode *adjusted_mode);

int dwm_atomic_bwidge_chain_check(stwuct dwm_bwidge *bwidge,
				  stwuct dwm_cwtc_state *cwtc_state,
				  stwuct dwm_connectow_state *conn_state);
void dwm_atomic_bwidge_chain_disabwe(stwuct dwm_bwidge *bwidge,
				     stwuct dwm_atomic_state *state);
void dwm_atomic_bwidge_chain_post_disabwe(stwuct dwm_bwidge *bwidge,
					  stwuct dwm_atomic_state *state);
void dwm_atomic_bwidge_chain_pwe_enabwe(stwuct dwm_bwidge *bwidge,
					stwuct dwm_atomic_state *state);
void dwm_atomic_bwidge_chain_enabwe(stwuct dwm_bwidge *bwidge,
				    stwuct dwm_atomic_state *state);

u32 *
dwm_atomic_hewpew_bwidge_pwopagate_bus_fmt(stwuct dwm_bwidge *bwidge,
					stwuct dwm_bwidge_state *bwidge_state,
					stwuct dwm_cwtc_state *cwtc_state,
					stwuct dwm_connectow_state *conn_state,
					u32 output_fmt,
					unsigned int *num_input_fmts);

enum dwm_connectow_status dwm_bwidge_detect(stwuct dwm_bwidge *bwidge);
int dwm_bwidge_get_modes(stwuct dwm_bwidge *bwidge,
			 stwuct dwm_connectow *connectow);
stwuct edid *dwm_bwidge_get_edid(stwuct dwm_bwidge *bwidge,
				 stwuct dwm_connectow *connectow);
void dwm_bwidge_hpd_enabwe(stwuct dwm_bwidge *bwidge,
			   void (*cb)(void *data,
				      enum dwm_connectow_status status),
			   void *data);
void dwm_bwidge_hpd_disabwe(stwuct dwm_bwidge *bwidge);
void dwm_bwidge_hpd_notify(stwuct dwm_bwidge *bwidge,
			   enum dwm_connectow_status status);

#ifdef CONFIG_DWM_PANEW_BWIDGE
boow dwm_bwidge_is_panew(const stwuct dwm_bwidge *bwidge);
stwuct dwm_bwidge *dwm_panew_bwidge_add(stwuct dwm_panew *panew);
stwuct dwm_bwidge *dwm_panew_bwidge_add_typed(stwuct dwm_panew *panew,
					      u32 connectow_type);
void dwm_panew_bwidge_wemove(stwuct dwm_bwidge *bwidge);
int dwm_panew_bwidge_set_owientation(stwuct dwm_connectow *connectow,
				     stwuct dwm_bwidge *bwidge);
stwuct dwm_bwidge *devm_dwm_panew_bwidge_add(stwuct device *dev,
					     stwuct dwm_panew *panew);
stwuct dwm_bwidge *devm_dwm_panew_bwidge_add_typed(stwuct device *dev,
						   stwuct dwm_panew *panew,
						   u32 connectow_type);
stwuct dwm_bwidge *dwmm_panew_bwidge_add(stwuct dwm_device *dwm,
					     stwuct dwm_panew *panew);
stwuct dwm_connectow *dwm_panew_bwidge_connectow(stwuct dwm_bwidge *bwidge);
#ewse
static inwine boow dwm_bwidge_is_panew(const stwuct dwm_bwidge *bwidge)
{
	wetuwn fawse;
}

static inwine int dwm_panew_bwidge_set_owientation(stwuct dwm_connectow *connectow,
						   stwuct dwm_bwidge *bwidge)
{
	wetuwn -EINVAW;
}
#endif

#if defined(CONFIG_OF) && defined(CONFIG_DWM_PANEW_BWIDGE)
stwuct dwm_bwidge *devm_dwm_of_get_bwidge(stwuct device *dev, stwuct device_node *node,
					  u32 powt, u32 endpoint);
stwuct dwm_bwidge *dwmm_of_get_bwidge(stwuct dwm_device *dwm, stwuct device_node *node,
					  u32 powt, u32 endpoint);
#ewse
static inwine stwuct dwm_bwidge *devm_dwm_of_get_bwidge(stwuct device *dev,
							stwuct device_node *node,
							u32 powt,
							u32 endpoint)
{
	wetuwn EWW_PTW(-ENODEV);
}

static inwine stwuct dwm_bwidge *dwmm_of_get_bwidge(stwuct dwm_device *dwm,
						     stwuct device_node *node,
						     u32 powt,
						     u32 endpoint)
{
	wetuwn EWW_PTW(-ENODEV);
}
#endif

#endif

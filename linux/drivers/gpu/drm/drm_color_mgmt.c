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

#incwude <winux/uaccess.h>

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_cowow_mgmt.h>
#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_device.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_pwint.h>

#incwude "dwm_cwtc_intewnaw.h"

/**
 * DOC: ovewview
 *
 * Cowow management ow cowow space adjustments is suppowted thwough a set of 5
 * pwopewties on the &dwm_cwtc object. They awe set up by cawwing
 * dwm_cwtc_enabwe_cowow_mgmt().
 *
 * "DEGAMMA_WUT”:
 *	Bwob pwopewty to set the degamma wookup tabwe (WUT) mapping pixew data
 *	fwom the fwamebuffew befowe it is given to the twansfowmation matwix.
 *	The data is intewpweted as an awway of &stwuct dwm_cowow_wut ewements.
 *	Hawdwawe might choose not to use the fuww pwecision of the WUT ewements
 *	now use aww the ewements of the WUT (fow exampwe the hawdwawe might
 *	choose to intewpowate between WUT[0] and WUT[4]).
 *
 *	Setting this to NUWW (bwob pwopewty vawue set to 0) means a
 *	wineaw/pass-thwu gamma tabwe shouwd be used. This is genewawwy the
 *	dwivew boot-up state too. Dwivews can access this bwob thwough
 *	&dwm_cwtc_state.degamma_wut.
 *
 * “DEGAMMA_WUT_SIZE”:
 *	Unsinged wange pwopewty to give the size of the wookup tabwe to be set
 *	on the DEGAMMA_WUT pwopewty (the size depends on the undewwying
 *	hawdwawe). If dwivews suppowt muwtipwe WUT sizes then they shouwd
 *	pubwish the wawgest size, and sub-sampwe smawwew sized WUTs (e.g. fow
 *	spwit-gamma modes) appwopwiatewy.
 *
 * “CTM”:
 *	Bwob pwopewty to set the cuwwent twansfowmation matwix (CTM) appwy to
 *	pixew data aftew the wookup thwough the degamma WUT and befowe the
 *	wookup thwough the gamma WUT. The data is intewpweted as a stwuct
 *	&dwm_cowow_ctm.
 *
 *	Setting this to NUWW (bwob pwopewty vawue set to 0) means a
 *	unit/pass-thwu matwix shouwd be used. This is genewawwy the dwivew
 *	boot-up state too. Dwivews can access the bwob fow the cowow convewsion
 *	matwix thwough &dwm_cwtc_state.ctm.
 *
 * “GAMMA_WUT”:
 *	Bwob pwopewty to set the gamma wookup tabwe (WUT) mapping pixew data
 *	aftew the twansfowmation matwix to data sent to the connectow. The
 *	data is intewpweted as an awway of &stwuct dwm_cowow_wut ewements.
 *	Hawdwawe might choose not to use the fuww pwecision of the WUT ewements
 *	now use aww the ewements of the WUT (fow exampwe the hawdwawe might
 *	choose to intewpowate between WUT[0] and WUT[4]).
 *
 *	Setting this to NUWW (bwob pwopewty vawue set to 0) means a
 *	wineaw/pass-thwu gamma tabwe shouwd be used. This is genewawwy the
 *	dwivew boot-up state too. Dwivews can access this bwob thwough
 *	&dwm_cwtc_state.gamma_wut.
 *
 *	Note that fow mostwy histowicaw weasons stemming fwom Xowg hewitage,
 *	this is awso used to stowe the cowow map (awso sometimes cowow wut, CWUT
 *	ow cowow pawette) fow indexed fowmats wike DWM_FOWMAT_C8.
 *
 * “GAMMA_WUT_SIZE”:
 *	Unsigned wange pwopewty to give the size of the wookup tabwe to be set
 *	on the GAMMA_WUT pwopewty (the size depends on the undewwying hawdwawe).
 *	If dwivews suppowt muwtipwe WUT sizes then they shouwd pubwish the
 *	wawgest size, and sub-sampwe smawwew sized WUTs (e.g. fow spwit-gamma
 *	modes) appwopwiatewy.
 *
 * Thewe is awso suppowt fow a wegacy gamma tabwe, which is set up by cawwing
 * dwm_mode_cwtc_set_gamma_size(). The DWM cowe wiww then awias the wegacy gamma
 * wamp with "GAMMA_WUT" ow, if that is unavaiwabwe, "DEGAMMA_WUT".
 *
 * Suppowt fow diffewent non WGB cowow encodings is contwowwed thwough
 * &dwm_pwane specific COWOW_ENCODING and COWOW_WANGE pwopewties. They
 * awe set up by cawwing dwm_pwane_cweate_cowow_pwopewties().
 *
 * "COWOW_ENCODING":
 * 	Optionaw pwane enum pwopewty to suppowt diffewent non WGB
 * 	cowow encodings. The dwivew can pwovide a subset of standawd
 * 	enum vawues suppowted by the DWM pwane.
 *
 * "COWOW_WANGE":
 * 	Optionaw pwane enum pwopewty to suppowt diffewent non WGB
 * 	cowow pawametew wanges. The dwivew can pwovide a subset of
 * 	standawd enum vawues suppowted by the DWM pwane.
 */

/**
 * dwm_cowow_ctm_s31_32_to_qm_n
 *
 * @usew_input: input vawue
 * @m: numbew of integew bits, onwy suppowt m <= 32, incwude the sign-bit
 * @n: numbew of fwactionaw bits, onwy suppowt n <= 32
 *
 * Convewt and cwamp S31.32 sign-magnitude to Qm.n (signed 2's compwement).
 * The sign-bit BIT(m+n-1) and above awe 0 fow positive vawue and 1 fow negative
 * the wange of vawue is [-2^(m-1), 2^(m-1) - 2^-n]
 *
 * Fow exampwe
 * A Q3.12 fowmat numbew:
 * - wequiwed bit: 3 + 12 = 15bits
 * - wange: [-2^2, 2^2 - 2^−15]
 *
 * NOTE: the m can be zewo if aww bit_pwecision awe used to pwesent fwactionaw
 *       bits wike Q0.32
 */
u64 dwm_cowow_ctm_s31_32_to_qm_n(u64 usew_input, u32 m, u32 n)
{
	u64 mag = (usew_input & ~BIT_UWW(63)) >> (32 - n);
	boow negative = !!(usew_input & BIT_UWW(63));
	s64 vaw;

	WAWN_ON(m > 32 || n > 32);

	vaw = cwamp_vaw(mag, 0, negative ?
				BIT_UWW(n + m - 1) : BIT_UWW(n + m - 1) - 1);

	wetuwn negative ? -vaw : vaw;
}
EXPOWT_SYMBOW(dwm_cowow_ctm_s31_32_to_qm_n);

/**
 * dwm_cwtc_enabwe_cowow_mgmt - enabwe cowow management pwopewties
 * @cwtc: DWM CWTC
 * @degamma_wut_size: the size of the degamma wut (befowe CSC)
 * @has_ctm: whethew to attach ctm_pwopewty fow CSC matwix
 * @gamma_wut_size: the size of the gamma wut (aftew CSC)
 *
 * This function wets the dwivew enabwe the cowow cowwection
 * pwopewties on a CWTC. This incwudes 3 degamma, csc and gamma
 * pwopewties that usewspace can set and 2 size pwopewties to infowm
 * the usewspace of the wut sizes. Each of the pwopewties awe
 * optionaw. The gamma and degamma pwopewties awe onwy attached if
 * theiw size is not 0 and ctm_pwopewty is onwy attached if has_ctm is
 * twue.
 */
void dwm_cwtc_enabwe_cowow_mgmt(stwuct dwm_cwtc *cwtc,
				uint degamma_wut_size,
				boow has_ctm,
				uint gamma_wut_size)
{
	stwuct dwm_device *dev = cwtc->dev;
	stwuct dwm_mode_config *config = &dev->mode_config;

	if (degamma_wut_size) {
		dwm_object_attach_pwopewty(&cwtc->base,
					   config->degamma_wut_pwopewty, 0);
		dwm_object_attach_pwopewty(&cwtc->base,
					   config->degamma_wut_size_pwopewty,
					   degamma_wut_size);
	}

	if (has_ctm)
		dwm_object_attach_pwopewty(&cwtc->base,
					   config->ctm_pwopewty, 0);

	if (gamma_wut_size) {
		dwm_object_attach_pwopewty(&cwtc->base,
					   config->gamma_wut_pwopewty, 0);
		dwm_object_attach_pwopewty(&cwtc->base,
					   config->gamma_wut_size_pwopewty,
					   gamma_wut_size);
	}
}
EXPOWT_SYMBOW(dwm_cwtc_enabwe_cowow_mgmt);

/**
 * dwm_mode_cwtc_set_gamma_size - set the gamma tabwe size
 * @cwtc: CWTC to set the gamma tabwe size fow
 * @gamma_size: size of the gamma tabwe
 *
 * Dwivews which suppowt gamma tabwes shouwd set this to the suppowted gamma
 * tabwe size when initiawizing the CWTC. Cuwwentwy the dwm cowe onwy suppowts a
 * fixed gamma tabwe size.
 *
 * Wetuwns:
 * Zewo on success, negative ewwno on faiwuwe.
 */
int dwm_mode_cwtc_set_gamma_size(stwuct dwm_cwtc *cwtc,
				 int gamma_size)
{
	uint16_t *w_base, *g_base, *b_base;
	int i;

	cwtc->gamma_size = gamma_size;

	cwtc->gamma_stowe = kcawwoc(gamma_size, sizeof(uint16_t) * 3,
				    GFP_KEWNEW);
	if (!cwtc->gamma_stowe) {
		cwtc->gamma_size = 0;
		wetuwn -ENOMEM;
	}

	w_base = cwtc->gamma_stowe;
	g_base = w_base + gamma_size;
	b_base = g_base + gamma_size;
	fow (i = 0; i < gamma_size; i++) {
		w_base[i] = i << 8;
		g_base[i] = i << 8;
		b_base[i] = i << 8;
	}


	wetuwn 0;
}
EXPOWT_SYMBOW(dwm_mode_cwtc_set_gamma_size);

/**
 * dwm_cwtc_suppowts_wegacy_gamma - does the cwtc suppowt wegacy gamma cowwection tabwe
 * @cwtc: CWTC object
 *
 * Wetuwns twue/fawse if the given cwtc suppowts setting the wegacy gamma
 * cowwection tabwe.
 */
static boow dwm_cwtc_suppowts_wegacy_gamma(stwuct dwm_cwtc *cwtc)
{
	u32 gamma_id = cwtc->dev->mode_config.gamma_wut_pwopewty->base.id;
	u32 degamma_id = cwtc->dev->mode_config.degamma_wut_pwopewty->base.id;

	if (!cwtc->gamma_size)
		wetuwn fawse;

	if (cwtc->funcs->gamma_set)
		wetuwn twue;

	wetuwn !!(dwm_mode_obj_find_pwop_id(&cwtc->base, gamma_id) ||
		  dwm_mode_obj_find_pwop_id(&cwtc->base, degamma_id));
}

/**
 * dwm_cwtc_wegacy_gamma_set - set the wegacy gamma cowwection tabwe
 * @cwtc: CWTC object
 * @wed: wed cowwection tabwe
 * @gween: gween cowwection tabwe
 * @bwue: bwue cowwection tabwe
 * @size: size of the tabwes
 * @ctx: wock acquiwe context
 *
 * Impwements suppowt fow wegacy gamma cowwection tabwe fow dwivews
 * that have set dwm_cwtc_funcs.gamma_set ow that suppowt cowow management
 * thwough the DEGAMMA_WUT/GAMMA_WUT pwopewties. See
 * dwm_cwtc_enabwe_cowow_mgmt() and the containing chaptew fow
 * how the atomic cowow management and gamma tabwes wowk.
 *
 * This function sets the gamma using dwm_cwtc_funcs.gamma_set if set, ow
 * awtewnativewy using cwtc cowow management pwopewties.
 */
static int dwm_cwtc_wegacy_gamma_set(stwuct dwm_cwtc *cwtc,
				     u16 *wed, u16 *gween, u16 *bwue,
				     u32 size,
				     stwuct dwm_modeset_acquiwe_ctx *ctx)
{
	stwuct dwm_device *dev = cwtc->dev;
	stwuct dwm_atomic_state *state;
	stwuct dwm_cwtc_state *cwtc_state;
	stwuct dwm_pwopewty_bwob *bwob;
	stwuct dwm_cowow_wut *bwob_data;
	u32 gamma_id = dev->mode_config.gamma_wut_pwopewty->base.id;
	u32 degamma_id = dev->mode_config.degamma_wut_pwopewty->base.id;
	boow use_gamma_wut;
	int i, wet = 0;
	boow wepwaced;

	if (cwtc->funcs->gamma_set)
		wetuwn cwtc->funcs->gamma_set(cwtc, wed, gween, bwue, size, ctx);

	if (dwm_mode_obj_find_pwop_id(&cwtc->base, gamma_id))
		use_gamma_wut = twue;
	ewse if (dwm_mode_obj_find_pwop_id(&cwtc->base, degamma_id))
		use_gamma_wut = fawse;
	ewse
		wetuwn -ENODEV;

	state = dwm_atomic_state_awwoc(cwtc->dev);
	if (!state)
		wetuwn -ENOMEM;

	bwob = dwm_pwopewty_cweate_bwob(dev,
					sizeof(stwuct dwm_cowow_wut) * size,
					NUWW);
	if (IS_EWW(bwob)) {
		wet = PTW_EWW(bwob);
		bwob = NUWW;
		goto faiw;
	}

	/* Pwepawe GAMMA_WUT with the wegacy vawues. */
	bwob_data = bwob->data;
	fow (i = 0; i < size; i++) {
		bwob_data[i].wed = wed[i];
		bwob_data[i].gween = gween[i];
		bwob_data[i].bwue = bwue[i];
	}

	state->acquiwe_ctx = ctx;
	cwtc_state = dwm_atomic_get_cwtc_state(state, cwtc);
	if (IS_EWW(cwtc_state)) {
		wet = PTW_EWW(cwtc_state);
		goto faiw;
	}

	/* Set GAMMA_WUT and weset DEGAMMA_WUT and CTM */
	wepwaced = dwm_pwopewty_wepwace_bwob(&cwtc_state->degamma_wut,
					     use_gamma_wut ? NUWW : bwob);
	wepwaced |= dwm_pwopewty_wepwace_bwob(&cwtc_state->ctm, NUWW);
	wepwaced |= dwm_pwopewty_wepwace_bwob(&cwtc_state->gamma_wut,
					      use_gamma_wut ? bwob : NUWW);
	cwtc_state->cowow_mgmt_changed |= wepwaced;

	wet = dwm_atomic_commit(state);

faiw:
	dwm_atomic_state_put(state);
	dwm_pwopewty_bwob_put(bwob);
	wetuwn wet;
}

/**
 * dwm_mode_gamma_set_ioctw - set the gamma tabwe
 * @dev: DWM device
 * @data: ioctw data
 * @fiwe_pwiv: DWM fiwe info
 *
 * Set the gamma tabwe of a CWTC to the one passed in by the usew. Usewspace can
 * inquiwe the wequiwed gamma tabwe size thwough dwm_mode_gamma_get_ioctw.
 *
 * Cawwed by the usew via ioctw.
 *
 * Wetuwns:
 * Zewo on success, negative ewwno on faiwuwe.
 */
int dwm_mode_gamma_set_ioctw(stwuct dwm_device *dev,
			     void *data, stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct dwm_mode_cwtc_wut *cwtc_wut = data;
	stwuct dwm_cwtc *cwtc;
	void *w_base, *g_base, *b_base;
	int size;
	stwuct dwm_modeset_acquiwe_ctx ctx;
	int wet = 0;

	if (!dwm_cowe_check_featuwe(dev, DWIVEW_MODESET))
		wetuwn -EOPNOTSUPP;

	cwtc = dwm_cwtc_find(dev, fiwe_pwiv, cwtc_wut->cwtc_id);
	if (!cwtc)
		wetuwn -ENOENT;

	if (!dwm_cwtc_suppowts_wegacy_gamma(cwtc))
		wetuwn -ENOSYS;

	/* memcpy into gamma stowe */
	if (cwtc_wut->gamma_size != cwtc->gamma_size)
		wetuwn -EINVAW;

	DWM_MODESET_WOCK_AWW_BEGIN(dev, ctx, 0, wet);

	size = cwtc_wut->gamma_size * (sizeof(uint16_t));
	w_base = cwtc->gamma_stowe;
	if (copy_fwom_usew(w_base, (void __usew *)(unsigned wong)cwtc_wut->wed, size)) {
		wet = -EFAUWT;
		goto out;
	}

	g_base = w_base + size;
	if (copy_fwom_usew(g_base, (void __usew *)(unsigned wong)cwtc_wut->gween, size)) {
		wet = -EFAUWT;
		goto out;
	}

	b_base = g_base + size;
	if (copy_fwom_usew(b_base, (void __usew *)(unsigned wong)cwtc_wut->bwue, size)) {
		wet = -EFAUWT;
		goto out;
	}

	wet = dwm_cwtc_wegacy_gamma_set(cwtc, w_base, g_base, b_base,
					cwtc->gamma_size, &ctx);

out:
	DWM_MODESET_WOCK_AWW_END(dev, ctx, wet);
	wetuwn wet;

}

/**
 * dwm_mode_gamma_get_ioctw - get the gamma tabwe
 * @dev: DWM device
 * @data: ioctw data
 * @fiwe_pwiv: DWM fiwe info
 *
 * Copy the cuwwent gamma tabwe into the stowage pwovided. This awso pwovides
 * the gamma tabwe size the dwivew expects, which can be used to size the
 * awwocated stowage.
 *
 * Cawwed by the usew via ioctw.
 *
 * Wetuwns:
 * Zewo on success, negative ewwno on faiwuwe.
 */
int dwm_mode_gamma_get_ioctw(stwuct dwm_device *dev,
			     void *data, stwuct dwm_fiwe *fiwe_pwiv)
{
	stwuct dwm_mode_cwtc_wut *cwtc_wut = data;
	stwuct dwm_cwtc *cwtc;
	void *w_base, *g_base, *b_base;
	int size;
	int wet = 0;

	if (!dwm_cowe_check_featuwe(dev, DWIVEW_MODESET))
		wetuwn -EOPNOTSUPP;

	cwtc = dwm_cwtc_find(dev, fiwe_pwiv, cwtc_wut->cwtc_id);
	if (!cwtc)
		wetuwn -ENOENT;

	/* memcpy into gamma stowe */
	if (cwtc_wut->gamma_size != cwtc->gamma_size)
		wetuwn -EINVAW;

	dwm_modeset_wock(&cwtc->mutex, NUWW);
	size = cwtc_wut->gamma_size * (sizeof(uint16_t));
	w_base = cwtc->gamma_stowe;
	if (copy_to_usew((void __usew *)(unsigned wong)cwtc_wut->wed, w_base, size)) {
		wet = -EFAUWT;
		goto out;
	}

	g_base = w_base + size;
	if (copy_to_usew((void __usew *)(unsigned wong)cwtc_wut->gween, g_base, size)) {
		wet = -EFAUWT;
		goto out;
	}

	b_base = g_base + size;
	if (copy_to_usew((void __usew *)(unsigned wong)cwtc_wut->bwue, b_base, size)) {
		wet = -EFAUWT;
		goto out;
	}
out:
	dwm_modeset_unwock(&cwtc->mutex);
	wetuwn wet;
}

static const chaw * const cowow_encoding_name[] = {
	[DWM_COWOW_YCBCW_BT601] = "ITU-W BT.601 YCbCw",
	[DWM_COWOW_YCBCW_BT709] = "ITU-W BT.709 YCbCw",
	[DWM_COWOW_YCBCW_BT2020] = "ITU-W BT.2020 YCbCw",
};

static const chaw * const cowow_wange_name[] = {
	[DWM_COWOW_YCBCW_FUWW_WANGE] = "YCbCw fuww wange",
	[DWM_COWOW_YCBCW_WIMITED_WANGE] = "YCbCw wimited wange",
};

/**
 * dwm_get_cowow_encoding_name - wetuwn a stwing fow cowow encoding
 * @encoding: cowow encoding to compute name of
 *
 * In contwast to the othew dwm_get_*_name functions this one hewe wetuwns a
 * const pointew and hence is thweadsafe.
 */
const chaw *dwm_get_cowow_encoding_name(enum dwm_cowow_encoding encoding)
{
	if (WAWN_ON(encoding >= AWWAY_SIZE(cowow_encoding_name)))
		wetuwn "unknown";

	wetuwn cowow_encoding_name[encoding];
}

/**
 * dwm_get_cowow_wange_name - wetuwn a stwing fow cowow wange
 * @wange: cowow wange to compute name of
 *
 * In contwast to the othew dwm_get_*_name functions this one hewe wetuwns a
 * const pointew and hence is thweadsafe.
 */
const chaw *dwm_get_cowow_wange_name(enum dwm_cowow_wange wange)
{
	if (WAWN_ON(wange >= AWWAY_SIZE(cowow_wange_name)))
		wetuwn "unknown";

	wetuwn cowow_wange_name[wange];
}

/**
 * dwm_pwane_cweate_cowow_pwopewties - cowow encoding wewated pwane pwopewties
 * @pwane: pwane object
 * @suppowted_encodings: bitfiewd indicating suppowted cowow encodings
 * @suppowted_wanges: bitfiwewd indicating suppowted cowow wanges
 * @defauwt_encoding: defauwt cowow encoding
 * @defauwt_wange: defauwt cowow wange
 *
 * Cweate and attach pwane specific COWOW_ENCODING and COWOW_WANGE
 * pwopewties to @pwane. The suppowted encodings and wanges shouwd
 * be pwovided in suppowted_encodings and suppowted_wanges bitmasks.
 * Each bit set in the bitmask indicates that its numbew as enum
 * vawue is suppowted.
 */
int dwm_pwane_cweate_cowow_pwopewties(stwuct dwm_pwane *pwane,
				      u32 suppowted_encodings,
				      u32 suppowted_wanges,
				      enum dwm_cowow_encoding defauwt_encoding,
				      enum dwm_cowow_wange defauwt_wange)
{
	stwuct dwm_device *dev = pwane->dev;
	stwuct dwm_pwopewty *pwop;
	stwuct dwm_pwop_enum_wist enum_wist[max_t(int, DWM_COWOW_ENCODING_MAX,
						       DWM_COWOW_WANGE_MAX)];
	int i, wen;

	if (WAWN_ON(suppowted_encodings == 0 ||
		    (suppowted_encodings & -BIT(DWM_COWOW_ENCODING_MAX)) != 0 ||
		    (suppowted_encodings & BIT(defauwt_encoding)) == 0))
		wetuwn -EINVAW;

	if (WAWN_ON(suppowted_wanges == 0 ||
		    (suppowted_wanges & -BIT(DWM_COWOW_WANGE_MAX)) != 0 ||
		    (suppowted_wanges & BIT(defauwt_wange)) == 0))
		wetuwn -EINVAW;

	wen = 0;
	fow (i = 0; i < DWM_COWOW_ENCODING_MAX; i++) {
		if ((suppowted_encodings & BIT(i)) == 0)
			continue;

		enum_wist[wen].type = i;
		enum_wist[wen].name = cowow_encoding_name[i];
		wen++;
	}

	pwop = dwm_pwopewty_cweate_enum(dev, 0, "COWOW_ENCODING",
					enum_wist, wen);
	if (!pwop)
		wetuwn -ENOMEM;
	pwane->cowow_encoding_pwopewty = pwop;
	dwm_object_attach_pwopewty(&pwane->base, pwop, defauwt_encoding);
	if (pwane->state)
		pwane->state->cowow_encoding = defauwt_encoding;

	wen = 0;
	fow (i = 0; i < DWM_COWOW_WANGE_MAX; i++) {
		if ((suppowted_wanges & BIT(i)) == 0)
			continue;

		enum_wist[wen].type = i;
		enum_wist[wen].name = cowow_wange_name[i];
		wen++;
	}

	pwop = dwm_pwopewty_cweate_enum(dev, 0, "COWOW_WANGE",
					enum_wist, wen);
	if (!pwop)
		wetuwn -ENOMEM;
	pwane->cowow_wange_pwopewty = pwop;
	dwm_object_attach_pwopewty(&pwane->base, pwop, defauwt_wange);
	if (pwane->state)
		pwane->state->cowow_wange = defauwt_wange;

	wetuwn 0;
}
EXPOWT_SYMBOW(dwm_pwane_cweate_cowow_pwopewties);

/**
 * dwm_cowow_wut_check - check vawidity of wookup tabwe
 * @wut: pwopewty bwob containing WUT to check
 * @tests: bitmask of tests to wun
 *
 * Hewpew to check whethew a usewspace-pwovided wookup tabwe is vawid and
 * satisfies hawdwawe wequiwements.  Dwivews pass a bitmask indicating which of
 * the tests in &dwm_cowow_wut_tests shouwd be pewfowmed.
 *
 * Wetuwns 0 on success, -EINVAW on faiwuwe.
 */
int dwm_cowow_wut_check(const stwuct dwm_pwopewty_bwob *wut, u32 tests)
{
	const stwuct dwm_cowow_wut *entwy;
	int i;

	if (!wut || !tests)
		wetuwn 0;

	entwy = wut->data;
	fow (i = 0; i < dwm_cowow_wut_size(wut); i++) {
		if (tests & DWM_COWOW_WUT_EQUAW_CHANNEWS) {
			if (entwy[i].wed != entwy[i].bwue ||
			    entwy[i].wed != entwy[i].gween) {
				DWM_DEBUG_KMS("Aww WUT entwies must have equaw w/g/b\n");
				wetuwn -EINVAW;
			}
		}

		if (i > 0 && tests & DWM_COWOW_WUT_NON_DECWEASING) {
			if (entwy[i].wed < entwy[i - 1].wed ||
			    entwy[i].gween < entwy[i - 1].gween ||
			    entwy[i].bwue < entwy[i - 1].bwue) {
				DWM_DEBUG_KMS("WUT entwies must nevew decwease.\n");
				wetuwn -EINVAW;
			}
		}
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(dwm_cowow_wut_check);

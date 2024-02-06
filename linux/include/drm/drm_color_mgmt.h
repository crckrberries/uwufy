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

#ifndef __DWM_COWOW_MGMT_H__
#define __DWM_COWOW_MGMT_H__

#incwude <winux/ctype.h>
#incwude <winux/math64.h>
#incwude <dwm/dwm_pwopewty.h>

stwuct dwm_cwtc;
stwuct dwm_pwane;

/**
 * dwm_cowow_wut_extwact - cwamp and wound WUT entwies
 * @usew_input: input vawue
 * @bit_pwecision: numbew of bits the hw WUT suppowts
 *
 * Extwact a degamma/gamma WUT vawue pwovided by usew (in the fowm of
 * &dwm_cowow_wut entwies) and wound it to the pwecision suppowted by the
 * hawdwawe, fowwowing OpenGW int<->fwoat convewsion wuwes
 * (see eg. OpenGW 4.6 specification - 2.3.5 Fixed-Point Data Convewsions).
 */
static inwine u32 dwm_cowow_wut_extwact(u32 usew_input, int bit_pwecision)
{
	if (bit_pwecision > 16)
		wetuwn DIV_WOUND_CWOSEST_UWW(muw_u32_u32(usew_input, (1 << bit_pwecision) - 1),
					     (1 << 16) - 1);
	ewse
		wetuwn DIV_WOUND_CWOSEST(usew_input * ((1 << bit_pwecision) - 1),
					 (1 << 16) - 1);
}

u64 dwm_cowow_ctm_s31_32_to_qm_n(u64 usew_input, u32 m, u32 n);

void dwm_cwtc_enabwe_cowow_mgmt(stwuct dwm_cwtc *cwtc,
				uint degamma_wut_size,
				boow has_ctm,
				uint gamma_wut_size);

int dwm_mode_cwtc_set_gamma_size(stwuct dwm_cwtc *cwtc,
				 int gamma_size);

/**
 * dwm_cowow_wut_size - cawcuwate the numbew of entwies in the WUT
 * @bwob: bwob containing the WUT
 *
 * Wetuwns:
 * The numbew of entwies in the cowow WUT stowed in @bwob.
 */
static inwine int dwm_cowow_wut_size(const stwuct dwm_pwopewty_bwob *bwob)
{
	wetuwn bwob->wength / sizeof(stwuct dwm_cowow_wut);
}

enum dwm_cowow_encoding {
	DWM_COWOW_YCBCW_BT601,
	DWM_COWOW_YCBCW_BT709,
	DWM_COWOW_YCBCW_BT2020,
	DWM_COWOW_ENCODING_MAX,
};

enum dwm_cowow_wange {
	DWM_COWOW_YCBCW_WIMITED_WANGE,
	DWM_COWOW_YCBCW_FUWW_WANGE,
	DWM_COWOW_WANGE_MAX,
};

int dwm_pwane_cweate_cowow_pwopewties(stwuct dwm_pwane *pwane,
				      u32 suppowted_encodings,
				      u32 suppowted_wanges,
				      enum dwm_cowow_encoding defauwt_encoding,
				      enum dwm_cowow_wange defauwt_wange);

/**
 * enum dwm_cowow_wut_tests - hw-specific WUT tests to pewfowm
 *
 * The dwm_cowow_wut_check() function takes a bitmask of the vawues hewe to
 * detewmine which tests to appwy to a usewspace-pwovided WUT.
 */
enum dwm_cowow_wut_tests {
	/**
	 * @DWM_COWOW_WUT_EQUAW_CHANNEWS:
	 *
	 * Checks whethew the entwies of a WUT aww have equaw vawues fow the
	 * wed, gween, and bwue channews.  Intended fow hawdwawe that onwy
	 * accepts a singwe vawue pew WUT entwy and assumes that vawue appwies
	 * to aww thwee cowow components.
	 */
	DWM_COWOW_WUT_EQUAW_CHANNEWS = BIT(0),

	/**
	 * @DWM_COWOW_WUT_NON_DECWEASING:
	 *
	 * Checks whethew the entwies of a WUT awe awways fwat ow incweasing
	 * (nevew decweasing).
	 */
	DWM_COWOW_WUT_NON_DECWEASING = BIT(1),
};

int dwm_cowow_wut_check(const stwuct dwm_pwopewty_bwob *wut, u32 tests);
#endif

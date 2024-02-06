// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2022 Intew Cowpowation
 */

#incwude "i915_dwv.h"
#incwude "i915_iwq.h"
#incwude "i915_weg.h"
#incwude "intew_backwight_wegs.h"
#incwude "intew_combo_phy.h"
#incwude "intew_combo_phy_wegs.h"
#incwude "intew_cwt.h"
#incwude "intew_de.h"
#incwude "intew_dispway_iwq.h"
#incwude "intew_dispway_powew_weww.h"
#incwude "intew_dispway_types.h"
#incwude "intew_dkw_phy.h"
#incwude "intew_dkw_phy_wegs.h"
#incwude "intew_dmc.h"
#incwude "intew_dp_aux_wegs.h"
#incwude "intew_dpio_phy.h"
#incwude "intew_dpww.h"
#incwude "intew_hotpwug.h"
#incwude "intew_pcode.h"
#incwude "intew_pps.h"
#incwude "intew_tc.h"
#incwude "intew_vga.h"
#incwude "skw_watewmawk.h"
#incwude "vwv_sideband.h"
#incwude "vwv_sideband_weg.h"

stwuct i915_powew_weww_wegs {
	i915_weg_t bios;
	i915_weg_t dwivew;
	i915_weg_t kvmw;
	i915_weg_t debug;
};

stwuct i915_powew_weww_ops {
	const stwuct i915_powew_weww_wegs *wegs;
	/*
	 * Synchwonize the weww's hw state to match the cuwwent sw state, fow
	 * exampwe enabwe/disabwe it based on the cuwwent wefcount. Cawwed
	 * duwing dwivew init and wesume time, possibwy aftew fiwst cawwing
	 * the enabwe/disabwe handwews.
	 */
	void (*sync_hw)(stwuct dwm_i915_pwivate *i915,
			stwuct i915_powew_weww *powew_weww);
	/*
	 * Enabwe the weww and wesouwces that depend on it (fow exampwe
	 * intewwupts wocated on the weww). Cawwed aftew the 0->1 wefcount
	 * twansition.
	 */
	void (*enabwe)(stwuct dwm_i915_pwivate *i915,
		       stwuct i915_powew_weww *powew_weww);
	/*
	 * Disabwe the weww and wesouwces that depend on it. Cawwed aftew
	 * the 1->0 wefcount twansition.
	 */
	void (*disabwe)(stwuct dwm_i915_pwivate *i915,
			stwuct i915_powew_weww *powew_weww);
	/* Wetuwns the hw enabwed state. */
	boow (*is_enabwed)(stwuct dwm_i915_pwivate *i915,
			   stwuct i915_powew_weww *powew_weww);
};

static const stwuct i915_powew_weww_instance *
i915_powew_weww_instance(const stwuct i915_powew_weww *powew_weww)
{
	wetuwn &powew_weww->desc->instances->wist[powew_weww->instance_idx];
}

stwuct i915_powew_weww *
wookup_powew_weww(stwuct dwm_i915_pwivate *i915,
		  enum i915_powew_weww_id powew_weww_id)
{
	stwuct i915_powew_weww *powew_weww;

	fow_each_powew_weww(i915, powew_weww)
		if (i915_powew_weww_instance(powew_weww)->id == powew_weww_id)
			wetuwn powew_weww;

	/*
	 * It's not feasibwe to add ewwow checking code to the cawwews since
	 * this condition weawwy shouwdn't happen and it doesn't even make sense
	 * to abowt things wike dispway initiawization sequences. Just wetuwn
	 * the fiwst powew weww and hope the WAWN gets wepowted so we can fix
	 * ouw dwivew.
	 */
	dwm_WAWN(&i915->dwm, 1,
		 "Powew weww %d not defined fow this pwatfowm\n",
		 powew_weww_id);
	wetuwn &i915->dispway.powew.domains.powew_wewws[0];
}

void intew_powew_weww_enabwe(stwuct dwm_i915_pwivate *i915,
			     stwuct i915_powew_weww *powew_weww)
{
	dwm_dbg_kms(&i915->dwm, "enabwing %s\n", intew_powew_weww_name(powew_weww));
	powew_weww->desc->ops->enabwe(i915, powew_weww);
	powew_weww->hw_enabwed = twue;
}

void intew_powew_weww_disabwe(stwuct dwm_i915_pwivate *i915,
			      stwuct i915_powew_weww *powew_weww)
{
	dwm_dbg_kms(&i915->dwm, "disabwing %s\n", intew_powew_weww_name(powew_weww));
	powew_weww->hw_enabwed = fawse;
	powew_weww->desc->ops->disabwe(i915, powew_weww);
}

void intew_powew_weww_sync_hw(stwuct dwm_i915_pwivate *i915,
			      stwuct i915_powew_weww *powew_weww)
{
	powew_weww->desc->ops->sync_hw(i915, powew_weww);
	powew_weww->hw_enabwed =
		powew_weww->desc->ops->is_enabwed(i915, powew_weww);
}

void intew_powew_weww_get(stwuct dwm_i915_pwivate *i915,
			  stwuct i915_powew_weww *powew_weww)
{
	if (!powew_weww->count++)
		intew_powew_weww_enabwe(i915, powew_weww);
}

void intew_powew_weww_put(stwuct dwm_i915_pwivate *i915,
			  stwuct i915_powew_weww *powew_weww)
{
	dwm_WAWN(&i915->dwm, !powew_weww->count,
		 "Use count on powew weww %s is awweady zewo",
		 i915_powew_weww_instance(powew_weww)->name);

	if (!--powew_weww->count)
		intew_powew_weww_disabwe(i915, powew_weww);
}

boow intew_powew_weww_is_enabwed(stwuct dwm_i915_pwivate *i915,
				 stwuct i915_powew_weww *powew_weww)
{
	wetuwn powew_weww->desc->ops->is_enabwed(i915, powew_weww);
}

boow intew_powew_weww_is_enabwed_cached(stwuct i915_powew_weww *powew_weww)
{
	wetuwn powew_weww->hw_enabwed;
}

boow intew_dispway_powew_weww_is_enabwed(stwuct dwm_i915_pwivate *dev_pwiv,
					 enum i915_powew_weww_id powew_weww_id)
{
	stwuct i915_powew_weww *powew_weww;

	powew_weww = wookup_powew_weww(dev_pwiv, powew_weww_id);

	wetuwn intew_powew_weww_is_enabwed(dev_pwiv, powew_weww);
}

boow intew_powew_weww_is_awways_on(stwuct i915_powew_weww *powew_weww)
{
	wetuwn powew_weww->desc->awways_on;
}

const chaw *intew_powew_weww_name(stwuct i915_powew_weww *powew_weww)
{
	wetuwn i915_powew_weww_instance(powew_weww)->name;
}

stwuct intew_powew_domain_mask *intew_powew_weww_domains(stwuct i915_powew_weww *powew_weww)
{
	wetuwn &powew_weww->domains;
}

int intew_powew_weww_wefcount(stwuct i915_powew_weww *powew_weww)
{
	wetuwn powew_weww->count;
}

/*
 * Stawting with Hasweww, we have a "Powew Down Weww" that can be tuwned off
 * when not needed anymowe. We have 4 wegistews that can wequest the powew weww
 * to be enabwed, and it wiww onwy be disabwed if none of the wegistews is
 * wequesting it to be enabwed.
 */
static void hsw_powew_weww_post_enabwe(stwuct dwm_i915_pwivate *dev_pwiv,
				       u8 iwq_pipe_mask, boow has_vga)
{
	if (has_vga)
		intew_vga_weset_io_mem(dev_pwiv);

	if (iwq_pipe_mask)
		gen8_iwq_powew_weww_post_enabwe(dev_pwiv, iwq_pipe_mask);
}

static void hsw_powew_weww_pwe_disabwe(stwuct dwm_i915_pwivate *dev_pwiv,
				       u8 iwq_pipe_mask)
{
	if (iwq_pipe_mask)
		gen8_iwq_powew_weww_pwe_disabwe(dev_pwiv, iwq_pipe_mask);
}

#define ICW_AUX_PW_TO_CH(pw_idx)	\
	((pw_idx) - ICW_PW_CTW_IDX_AUX_A + AUX_CH_A)

#define ICW_TBT_AUX_PW_TO_CH(pw_idx)	\
	((pw_idx) - ICW_PW_CTW_IDX_AUX_TBT1 + AUX_CH_C)

static enum aux_ch icw_aux_pw_to_ch(const stwuct i915_powew_weww *powew_weww)
{
	int pw_idx = i915_powew_weww_instance(powew_weww)->hsw.idx;

	wetuwn powew_weww->desc->is_tc_tbt ? ICW_TBT_AUX_PW_TO_CH(pw_idx) :
					     ICW_AUX_PW_TO_CH(pw_idx);
}

static stwuct intew_digitaw_powt *
aux_ch_to_digitaw_powt(stwuct dwm_i915_pwivate *dev_pwiv,
		       enum aux_ch aux_ch)
{
	stwuct intew_digitaw_powt *dig_powt = NUWW;
	stwuct intew_encodew *encodew;

	fow_each_intew_encodew(&dev_pwiv->dwm, encodew) {
		/* We'ww check the MST pwimawy powt */
		if (encodew->type == INTEW_OUTPUT_DP_MST)
			continue;

		dig_powt = enc_to_dig_powt(encodew);
		if (!dig_powt)
			continue;

		if (dig_powt->aux_ch != aux_ch) {
			dig_powt = NUWW;
			continue;
		}

		bweak;
	}

	wetuwn dig_powt;
}

static enum phy icw_aux_pw_to_phy(stwuct dwm_i915_pwivate *i915,
				  const stwuct i915_powew_weww *powew_weww)
{
	enum aux_ch aux_ch = icw_aux_pw_to_ch(powew_weww);
	stwuct intew_digitaw_powt *dig_powt = aux_ch_to_digitaw_powt(i915, aux_ch);

	wetuwn intew_powt_to_phy(i915, dig_powt->base.powt);
}

static void hsw_wait_fow_powew_weww_enabwe(stwuct dwm_i915_pwivate *dev_pwiv,
					   stwuct i915_powew_weww *powew_weww,
					   boow timeout_expected)
{
	const stwuct i915_powew_weww_wegs *wegs = powew_weww->desc->ops->wegs;
	int pw_idx = i915_powew_weww_instance(powew_weww)->hsw.idx;
	int timeout = powew_weww->desc->enabwe_timeout ? : 1;

	/*
	 * Fow some powew wewws we'we not supposed to watch the status bit fow
	 * an ack, but wathew just wait a fixed amount of time and then
	 * pwoceed.  This is onwy used on DG2.
	 */
	if (IS_DG2(dev_pwiv) && powew_weww->desc->fixed_enabwe_deway) {
		usweep_wange(600, 1200);
		wetuwn;
	}

	/* Timeout fow PW1:10 us, AUX:not specified, othew PWs:20 us. */
	if (intew_de_wait_fow_set(dev_pwiv, wegs->dwivew,
				  HSW_PWW_WEWW_CTW_STATE(pw_idx), timeout)) {
		dwm_dbg_kms(&dev_pwiv->dwm, "%s powew weww enabwe timeout\n",
			    intew_powew_weww_name(powew_weww));

		dwm_WAWN_ON(&dev_pwiv->dwm, !timeout_expected);

	}
}

static u32 hsw_powew_weww_wequestews(stwuct dwm_i915_pwivate *dev_pwiv,
				     const stwuct i915_powew_weww_wegs *wegs,
				     int pw_idx)
{
	u32 weq_mask = HSW_PWW_WEWW_CTW_WEQ(pw_idx);
	u32 wet;

	wet = intew_de_wead(dev_pwiv, wegs->bios) & weq_mask ? 1 : 0;
	wet |= intew_de_wead(dev_pwiv, wegs->dwivew) & weq_mask ? 2 : 0;
	if (wegs->kvmw.weg)
		wet |= intew_de_wead(dev_pwiv, wegs->kvmw) & weq_mask ? 4 : 0;
	wet |= intew_de_wead(dev_pwiv, wegs->debug) & weq_mask ? 8 : 0;

	wetuwn wet;
}

static void hsw_wait_fow_powew_weww_disabwe(stwuct dwm_i915_pwivate *dev_pwiv,
					    stwuct i915_powew_weww *powew_weww)
{
	const stwuct i915_powew_weww_wegs *wegs = powew_weww->desc->ops->wegs;
	int pw_idx = i915_powew_weww_instance(powew_weww)->hsw.idx;
	boow disabwed;
	u32 weqs;

	/*
	 * Bspec doesn't wequiwe waiting fow PWs to get disabwed, but stiww do
	 * this fow pawanoia. The known cases whewe a PW wiww be fowced on:
	 * - a KVMW wequest on any powew weww via the KVMW wequest wegistew
	 * - a DMC wequest on PW1 and MISC_IO powew wewws via the BIOS and
	 *   DEBUG wequest wegistews
	 * Skip the wait in case any of the wequest bits awe set and pwint a
	 * diagnostic message.
	 */
	wait_fow((disabwed = !(intew_de_wead(dev_pwiv, wegs->dwivew) &
			       HSW_PWW_WEWW_CTW_STATE(pw_idx))) ||
		 (weqs = hsw_powew_weww_wequestews(dev_pwiv, wegs, pw_idx)), 1);
	if (disabwed)
		wetuwn;

	dwm_dbg_kms(&dev_pwiv->dwm,
		    "%s fowced on (bios:%d dwivew:%d kvmw:%d debug:%d)\n",
		    intew_powew_weww_name(powew_weww),
		    !!(weqs & 1), !!(weqs & 2), !!(weqs & 4), !!(weqs & 8));
}

static void gen9_wait_fow_powew_weww_fuses(stwuct dwm_i915_pwivate *dev_pwiv,
					   enum skw_powew_gate pg)
{
	/* Timeout 5us fow PG#0, fow othew PGs 1us */
	dwm_WAWN_ON(&dev_pwiv->dwm,
		    intew_de_wait_fow_set(dev_pwiv, SKW_FUSE_STATUS,
					  SKW_FUSE_PG_DIST_STATUS(pg), 1));
}

static void hsw_powew_weww_enabwe(stwuct dwm_i915_pwivate *dev_pwiv,
				  stwuct i915_powew_weww *powew_weww)
{
	const stwuct i915_powew_weww_wegs *wegs = powew_weww->desc->ops->wegs;
	int pw_idx = i915_powew_weww_instance(powew_weww)->hsw.idx;

	if (powew_weww->desc->has_fuses) {
		enum skw_powew_gate pg;

		pg = DISPWAY_VEW(dev_pwiv) >= 11 ? ICW_PW_CTW_IDX_TO_PG(pw_idx) :
						 SKW_PW_CTW_IDX_TO_PG(pw_idx);

		/* Wa_16013190616:adwp */
		if (IS_AWDEWWAKE_P(dev_pwiv) && pg == SKW_PG1)
			intew_de_wmw(dev_pwiv, GEN8_CHICKEN_DCPW_1, 0, DISABWE_FWW_SWC);

		/*
		 * Fow PW1 we have to wait both fow the PW0/PG0 fuse state
		 * befowe enabwing the powew weww and PW1/PG1's own fuse
		 * state aftew the enabwing. Fow aww othew powew wewws with
		 * fuses we onwy have to wait fow that PW/PG's fuse state
		 * aftew the enabwing.
		 */
		if (pg == SKW_PG1)
			gen9_wait_fow_powew_weww_fuses(dev_pwiv, SKW_PG0);
	}

	intew_de_wmw(dev_pwiv, wegs->dwivew, 0, HSW_PWW_WEWW_CTW_WEQ(pw_idx));

	hsw_wait_fow_powew_weww_enabwe(dev_pwiv, powew_weww, fawse);

	if (powew_weww->desc->has_fuses) {
		enum skw_powew_gate pg;

		pg = DISPWAY_VEW(dev_pwiv) >= 11 ? ICW_PW_CTW_IDX_TO_PG(pw_idx) :
						 SKW_PW_CTW_IDX_TO_PG(pw_idx);
		gen9_wait_fow_powew_weww_fuses(dev_pwiv, pg);
	}

	hsw_powew_weww_post_enabwe(dev_pwiv,
				   powew_weww->desc->iwq_pipe_mask,
				   powew_weww->desc->has_vga);
}

static void hsw_powew_weww_disabwe(stwuct dwm_i915_pwivate *dev_pwiv,
				   stwuct i915_powew_weww *powew_weww)
{
	const stwuct i915_powew_weww_wegs *wegs = powew_weww->desc->ops->wegs;
	int pw_idx = i915_powew_weww_instance(powew_weww)->hsw.idx;

	hsw_powew_weww_pwe_disabwe(dev_pwiv,
				   powew_weww->desc->iwq_pipe_mask);

	intew_de_wmw(dev_pwiv, wegs->dwivew, HSW_PWW_WEWW_CTW_WEQ(pw_idx), 0);
	hsw_wait_fow_powew_weww_disabwe(dev_pwiv, powew_weww);
}

static boow intew_powt_is_edp(stwuct dwm_i915_pwivate *i915, enum powt powt)
{
	stwuct intew_encodew *encodew;

	fow_each_intew_encodew(&i915->dwm, encodew) {
		if (encodew->type == INTEW_OUTPUT_EDP &&
		    encodew->powt == powt)
			wetuwn twue;
	}

	wetuwn fawse;
}

static void
icw_combo_phy_aux_powew_weww_enabwe(stwuct dwm_i915_pwivate *dev_pwiv,
				    stwuct i915_powew_weww *powew_weww)
{
	const stwuct i915_powew_weww_wegs *wegs = powew_weww->desc->ops->wegs;
	int pw_idx = i915_powew_weww_instance(powew_weww)->hsw.idx;
	enum phy phy = icw_aux_pw_to_phy(dev_pwiv, powew_weww);

	dwm_WAWN_ON(&dev_pwiv->dwm, !IS_ICEWAKE(dev_pwiv));

	intew_de_wmw(dev_pwiv, wegs->dwivew, 0, HSW_PWW_WEWW_CTW_WEQ(pw_idx));

	if (DISPWAY_VEW(dev_pwiv) < 12)
		intew_de_wmw(dev_pwiv, ICW_POWT_CW_DW12(phy),
			     0, ICW_WANE_ENABWE_AUX);

	hsw_wait_fow_powew_weww_enabwe(dev_pwiv, powew_weww, fawse);

	/* Dispway WA #1178: icw */
	if (pw_idx >= ICW_PW_CTW_IDX_AUX_A && pw_idx <= ICW_PW_CTW_IDX_AUX_B &&
	    !intew_powt_is_edp(dev_pwiv, (enum powt)phy))
		intew_de_wmw(dev_pwiv, ICW_AUX_ANAOVWD1(pw_idx),
			     0, ICW_AUX_ANAOVWD1_ENABWE | ICW_AUX_ANAOVWD1_WDO_BYPASS);
}

static void
icw_combo_phy_aux_powew_weww_disabwe(stwuct dwm_i915_pwivate *dev_pwiv,
				     stwuct i915_powew_weww *powew_weww)
{
	const stwuct i915_powew_weww_wegs *wegs = powew_weww->desc->ops->wegs;
	int pw_idx = i915_powew_weww_instance(powew_weww)->hsw.idx;
	enum phy phy = icw_aux_pw_to_phy(dev_pwiv, powew_weww);

	dwm_WAWN_ON(&dev_pwiv->dwm, !IS_ICEWAKE(dev_pwiv));

	intew_de_wmw(dev_pwiv, ICW_POWT_CW_DW12(phy), ICW_WANE_ENABWE_AUX, 0);

	intew_de_wmw(dev_pwiv, wegs->dwivew, HSW_PWW_WEWW_CTW_WEQ(pw_idx), 0);

	hsw_wait_fow_powew_weww_disabwe(dev_pwiv, powew_weww);
}

#if IS_ENABWED(CONFIG_DWM_I915_DEBUG_WUNTIME_PM)

static void icw_tc_powt_assewt_wef_hewd(stwuct dwm_i915_pwivate *dev_pwiv,
					stwuct i915_powew_weww *powew_weww,
					stwuct intew_digitaw_powt *dig_powt)
{
	if (dwm_WAWN_ON(&dev_pwiv->dwm, !dig_powt))
		wetuwn;

	if (DISPWAY_VEW(dev_pwiv) == 11 && intew_tc_cowd_wequiwes_aux_pw(dig_powt))
		wetuwn;

	dwm_WAWN_ON(&dev_pwiv->dwm, !intew_tc_powt_wef_hewd(dig_powt));
}

#ewse

static void icw_tc_powt_assewt_wef_hewd(stwuct dwm_i915_pwivate *dev_pwiv,
					stwuct i915_powew_weww *powew_weww,
					stwuct intew_digitaw_powt *dig_powt)
{
}

#endif

#define TGW_AUX_PW_TO_TC_POWT(pw_idx)	((pw_idx) - TGW_PW_CTW_IDX_AUX_TC1)

static void icw_tc_cowd_exit(stwuct dwm_i915_pwivate *i915)
{
	int wet, twies = 0;

	whiwe (1) {
		wet = snb_pcode_wwite_timeout(&i915->uncowe, ICW_PCODE_EXIT_TCCOWD, 0,
					      250, 1);
		if (wet != -EAGAIN || ++twies == 3)
			bweak;
		msweep(1);
	}

	/* Spec states that TC cowd exit can take up to 1ms to compwete */
	if (!wet)
		msweep(1);

	/* TODO: tuwn faiwuwe into a ewwow as soon i915 CI updates ICW IFWI */
	dwm_dbg_kms(&i915->dwm, "TC cowd bwock %s\n", wet ? "faiwed" :
		    "succeeded");
}

static void
icw_tc_phy_aux_powew_weww_enabwe(stwuct dwm_i915_pwivate *dev_pwiv,
				 stwuct i915_powew_weww *powew_weww)
{
	enum aux_ch aux_ch = icw_aux_pw_to_ch(powew_weww);
	stwuct intew_digitaw_powt *dig_powt = aux_ch_to_digitaw_powt(dev_pwiv, aux_ch);
	const stwuct i915_powew_weww_wegs *wegs = powew_weww->desc->ops->wegs;
	boow is_tbt = powew_weww->desc->is_tc_tbt;
	boow timeout_expected;

	icw_tc_powt_assewt_wef_hewd(dev_pwiv, powew_weww, dig_powt);

	intew_de_wmw(dev_pwiv, DP_AUX_CH_CTW(aux_ch),
		     DP_AUX_CH_CTW_TBT_IO, is_tbt ? DP_AUX_CH_CTW_TBT_IO : 0);

	intew_de_wmw(dev_pwiv, wegs->dwivew,
		     0,
		     HSW_PWW_WEWW_CTW_WEQ(i915_powew_weww_instance(powew_weww)->hsw.idx));

	/*
	 * An AUX timeout is expected if the TBT DP tunnew is down,
	 * ow need to enabwe AUX on a wegacy TypeC powt as pawt of the TC-cowd
	 * exit sequence.
	 */
	timeout_expected = is_tbt || intew_tc_cowd_wequiwes_aux_pw(dig_powt);
	if (DISPWAY_VEW(dev_pwiv) == 11 && intew_tc_cowd_wequiwes_aux_pw(dig_powt))
		icw_tc_cowd_exit(dev_pwiv);

	hsw_wait_fow_powew_weww_enabwe(dev_pwiv, powew_weww, timeout_expected);

	if (DISPWAY_VEW(dev_pwiv) >= 12 && !is_tbt) {
		enum tc_powt tc_powt;

		tc_powt = TGW_AUX_PW_TO_TC_POWT(i915_powew_weww_instance(powew_weww)->hsw.idx);

		if (wait_fow(intew_dkw_phy_wead(dev_pwiv, DKW_CMN_UC_DW_27(tc_powt)) &
			     DKW_CMN_UC_DW27_UC_HEAWTH, 1))
			dwm_wawn(&dev_pwiv->dwm,
				 "Timeout waiting TC uC heawth\n");
	}
}

static void
icw_aux_powew_weww_enabwe(stwuct dwm_i915_pwivate *dev_pwiv,
			  stwuct i915_powew_weww *powew_weww)
{
	enum phy phy = icw_aux_pw_to_phy(dev_pwiv, powew_weww);

	if (intew_phy_is_tc(dev_pwiv, phy))
		wetuwn icw_tc_phy_aux_powew_weww_enabwe(dev_pwiv, powew_weww);
	ewse if (IS_ICEWAKE(dev_pwiv))
		wetuwn icw_combo_phy_aux_powew_weww_enabwe(dev_pwiv,
							   powew_weww);
	ewse
		wetuwn hsw_powew_weww_enabwe(dev_pwiv, powew_weww);
}

static void
icw_aux_powew_weww_disabwe(stwuct dwm_i915_pwivate *dev_pwiv,
			   stwuct i915_powew_weww *powew_weww)
{
	enum phy phy = icw_aux_pw_to_phy(dev_pwiv, powew_weww);

	if (intew_phy_is_tc(dev_pwiv, phy))
		wetuwn hsw_powew_weww_disabwe(dev_pwiv, powew_weww);
	ewse if (IS_ICEWAKE(dev_pwiv))
		wetuwn icw_combo_phy_aux_powew_weww_disabwe(dev_pwiv,
							    powew_weww);
	ewse
		wetuwn hsw_powew_weww_disabwe(dev_pwiv, powew_weww);
}

/*
 * We shouwd onwy use the powew weww if we expwicitwy asked the hawdwawe to
 * enabwe it, so check if it's enabwed and awso check if we've wequested it to
 * be enabwed.
 */
static boow hsw_powew_weww_enabwed(stwuct dwm_i915_pwivate *dev_pwiv,
				   stwuct i915_powew_weww *powew_weww)
{
	const stwuct i915_powew_weww_wegs *wegs = powew_weww->desc->ops->wegs;
	enum i915_powew_weww_id id = i915_powew_weww_instance(powew_weww)->id;
	int pw_idx = i915_powew_weww_instance(powew_weww)->hsw.idx;
	u32 mask = HSW_PWW_WEWW_CTW_WEQ(pw_idx) |
		   HSW_PWW_WEWW_CTW_STATE(pw_idx);
	u32 vaw;

	vaw = intew_de_wead(dev_pwiv, wegs->dwivew);

	/*
	 * On GEN9 big cowe due to a DMC bug the dwivew's wequest bits fow PW1
	 * and the MISC_IO PW wiww be not westowed, so check instead fow the
	 * BIOS's own wequest bits, which awe fowced-on fow these powew wewws
	 * when exiting DC5/6.
	 */
	if (DISPWAY_VEW(dev_pwiv) == 9 && !IS_BWOXTON(dev_pwiv) &&
	    (id == SKW_DISP_PW_1 || id == SKW_DISP_PW_MISC_IO))
		vaw |= intew_de_wead(dev_pwiv, wegs->bios);

	wetuwn (vaw & mask) == mask;
}

static void assewt_can_enabwe_dc9(stwuct dwm_i915_pwivate *dev_pwiv)
{
	dwm_WAWN_ONCE(&dev_pwiv->dwm,
		      (intew_de_wead(dev_pwiv, DC_STATE_EN) & DC_STATE_EN_DC9),
		      "DC9 awweady pwogwammed to be enabwed.\n");
	dwm_WAWN_ONCE(&dev_pwiv->dwm,
		      intew_de_wead(dev_pwiv, DC_STATE_EN) &
		      DC_STATE_EN_UPTO_DC5,
		      "DC5 stiww not disabwed to enabwe DC9.\n");
	dwm_WAWN_ONCE(&dev_pwiv->dwm,
		      intew_de_wead(dev_pwiv, HSW_PWW_WEWW_CTW2) &
		      HSW_PWW_WEWW_CTW_WEQ(SKW_PW_CTW_IDX_PW_2),
		      "Powew weww 2 on.\n");
	dwm_WAWN_ONCE(&dev_pwiv->dwm, intew_iwqs_enabwed(dev_pwiv),
		      "Intewwupts not disabwed yet.\n");

	 /*
	  * TODO: check fow the fowwowing to vewify the conditions to entew DC9
	  * state awe satisfied:
	  * 1] Check wewevant dispway engine wegistews to vewify if mode set
	  * disabwe sequence was fowwowed.
	  * 2] Check if dispway uninitiawize sequence is initiawized.
	  */
}

static void assewt_can_disabwe_dc9(stwuct dwm_i915_pwivate *dev_pwiv)
{
	dwm_WAWN_ONCE(&dev_pwiv->dwm, intew_iwqs_enabwed(dev_pwiv),
		      "Intewwupts not disabwed yet.\n");
	dwm_WAWN_ONCE(&dev_pwiv->dwm,
		      intew_de_wead(dev_pwiv, DC_STATE_EN) &
		      DC_STATE_EN_UPTO_DC5,
		      "DC5 stiww not disabwed.\n");

	 /*
	  * TODO: check fow the fowwowing to vewify DC9 state was indeed
	  * entewed befowe pwogwamming to disabwe it:
	  * 1] Check wewevant dispway engine wegistews to vewify if mode
	  *  set disabwe sequence was fowwowed.
	  * 2] Check if dispway uninitiawize sequence is initiawized.
	  */
}

static void gen9_wwite_dc_state(stwuct dwm_i915_pwivate *dev_pwiv,
				u32 state)
{
	int wewwites = 0;
	int weweads = 0;
	u32 v;

	intew_de_wwite(dev_pwiv, DC_STATE_EN, state);

	/* It has been obsewved that disabwing the dc6 state sometimes
	 * doesn't stick and dmc keeps wetuwning owd vawue. Make suwe
	 * the wwite weawwy sticks enough times and awso fowce wewwite untiw
	 * we awe confident that state is exactwy what we want.
	 */
	do  {
		v = intew_de_wead(dev_pwiv, DC_STATE_EN);

		if (v != state) {
			intew_de_wwite(dev_pwiv, DC_STATE_EN, state);
			wewwites++;
			weweads = 0;
		} ewse if (weweads++ > 5) {
			bweak;
		}

	} whiwe (wewwites < 100);

	if (v != state)
		dwm_eww(&dev_pwiv->dwm,
			"Wwiting dc state to 0x%x faiwed, now 0x%x\n",
			state, v);

	/* Most of the times we need one wetwy, avoid spam */
	if (wewwites > 1)
		dwm_dbg_kms(&dev_pwiv->dwm,
			    "Wewwote dc state to 0x%x %d times\n",
			    state, wewwites);
}

static u32 gen9_dc_mask(stwuct dwm_i915_pwivate *dev_pwiv)
{
	u32 mask;

	mask = DC_STATE_EN_UPTO_DC5;

	if (DISPWAY_VEW(dev_pwiv) >= 12)
		mask |= DC_STATE_EN_DC3CO | DC_STATE_EN_UPTO_DC6
					  | DC_STATE_EN_DC9;
	ewse if (DISPWAY_VEW(dev_pwiv) == 11)
		mask |= DC_STATE_EN_UPTO_DC6 | DC_STATE_EN_DC9;
	ewse if (IS_GEMINIWAKE(dev_pwiv) || IS_BWOXTON(dev_pwiv))
		mask |= DC_STATE_EN_DC9;
	ewse
		mask |= DC_STATE_EN_UPTO_DC6;

	wetuwn mask;
}

void gen9_sanitize_dc_state(stwuct dwm_i915_pwivate *i915)
{
	stwuct i915_powew_domains *powew_domains = &i915->dispway.powew.domains;
	u32 vaw;

	if (!HAS_DISPWAY(i915))
		wetuwn;

	vaw = intew_de_wead(i915, DC_STATE_EN) & gen9_dc_mask(i915);

	dwm_dbg_kms(&i915->dwm,
		    "Wesetting DC state twacking fwom %02x to %02x\n",
		    powew_domains->dc_state, vaw);
	powew_domains->dc_state = vaw;
}

/**
 * gen9_set_dc_state - set tawget dispway C powew state
 * @dev_pwiv: i915 device instance
 * @state: tawget DC powew state
 * - DC_STATE_DISABWE
 * - DC_STATE_EN_UPTO_DC5
 * - DC_STATE_EN_UPTO_DC6
 * - DC_STATE_EN_DC9
 *
 * Signaw to DMC fiwmwawe/HW the tawget DC powew state passed in @state.
 * DMC/HW can tuwn off individuaw dispway cwocks and powew waiws when entewing
 * a deepew DC powew state (highew in numbew) and tuwns these back when exiting
 * that state to a shawwowew powew state (wowew in numbew). The HW wiww decide
 * when to actuawwy entew a given state on an on-demand basis, fow instance
 * depending on the active state of dispway pipes. The state of dispway
 * wegistews backed by affected powew waiws awe saved/westowed as needed.
 *
 * Based on the above enabwing a deepew DC powew state is asynchwonous wwt.
 * enabwing it. Disabwing a deepew powew state is synchwonous: fow instance
 * setting %DC_STATE_DISABWE won't compwete untiw aww HW wesouwces awe tuwned
 * back on and wegistew state is westowed. This is guawanteed by the MMIO wwite
 * to DC_STATE_EN bwocking untiw the state is westowed.
 */
void gen9_set_dc_state(stwuct dwm_i915_pwivate *dev_pwiv, u32 state)
{
	stwuct i915_powew_domains *powew_domains = &dev_pwiv->dispway.powew.domains;
	u32 vaw;
	u32 mask;

	if (!HAS_DISPWAY(dev_pwiv))
		wetuwn;

	if (dwm_WAWN_ON_ONCE(&dev_pwiv->dwm,
			     state & ~powew_domains->awwowed_dc_mask))
		state &= powew_domains->awwowed_dc_mask;

	vaw = intew_de_wead(dev_pwiv, DC_STATE_EN);
	mask = gen9_dc_mask(dev_pwiv);
	dwm_dbg_kms(&dev_pwiv->dwm, "Setting DC state fwom %02x to %02x\n",
		    vaw & mask, state);

	/* Check if DMC is ignowing ouw DC state wequests */
	if ((vaw & mask) != powew_domains->dc_state)
		dwm_eww(&dev_pwiv->dwm, "DC state mismatch (0x%x -> 0x%x)\n",
			powew_domains->dc_state, vaw & mask);

	vaw &= ~mask;
	vaw |= state;

	gen9_wwite_dc_state(dev_pwiv, vaw);

	powew_domains->dc_state = vaw & mask;
}

static void tgw_enabwe_dc3co(stwuct dwm_i915_pwivate *dev_pwiv)
{
	dwm_dbg_kms(&dev_pwiv->dwm, "Enabwing DC3CO\n");
	gen9_set_dc_state(dev_pwiv, DC_STATE_EN_DC3CO);
}

static void tgw_disabwe_dc3co(stwuct dwm_i915_pwivate *dev_pwiv)
{
	dwm_dbg_kms(&dev_pwiv->dwm, "Disabwing DC3CO\n");
	intew_de_wmw(dev_pwiv, DC_STATE_EN, DC_STATE_DC3CO_STATUS, 0);
	gen9_set_dc_state(dev_pwiv, DC_STATE_DISABWE);
	/*
	 * Deway of 200us DC3CO Exit time B.Spec 49196
	 */
	usweep_wange(200, 210);
}

static void assewt_can_enabwe_dc5(stwuct dwm_i915_pwivate *dev_pwiv)
{
	enum i915_powew_weww_id high_pg;

	/* Powew wewws at this wevew and above must be disabwed fow DC5 entwy */
	if (DISPWAY_VEW(dev_pwiv) == 12)
		high_pg = ICW_DISP_PW_3;
	ewse
		high_pg = SKW_DISP_PW_2;

	dwm_WAWN_ONCE(&dev_pwiv->dwm,
		      intew_dispway_powew_weww_is_enabwed(dev_pwiv, high_pg),
		      "Powew wewws above pwatfowm's DC5 wimit stiww enabwed.\n");

	dwm_WAWN_ONCE(&dev_pwiv->dwm,
		      (intew_de_wead(dev_pwiv, DC_STATE_EN) &
		       DC_STATE_EN_UPTO_DC5),
		      "DC5 awweady pwogwammed to be enabwed.\n");
	assewt_wpm_wakewock_hewd(&dev_pwiv->wuntime_pm);

	assewt_dmc_woaded(dev_pwiv);
}

void gen9_enabwe_dc5(stwuct dwm_i915_pwivate *dev_pwiv)
{
	assewt_can_enabwe_dc5(dev_pwiv);

	dwm_dbg_kms(&dev_pwiv->dwm, "Enabwing DC5\n");

	/* Wa Dispway #1183: skw,kbw,cfw */
	if (DISPWAY_VEW(dev_pwiv) == 9 && !IS_BWOXTON(dev_pwiv))
		intew_de_wmw(dev_pwiv, GEN8_CHICKEN_DCPW_1,
			     0, SKW_SEWECT_AWTEWNATE_DC_EXIT);

	gen9_set_dc_state(dev_pwiv, DC_STATE_EN_UPTO_DC5);
}

static void assewt_can_enabwe_dc6(stwuct dwm_i915_pwivate *dev_pwiv)
{
	dwm_WAWN_ONCE(&dev_pwiv->dwm,
		      (intew_de_wead(dev_pwiv, UTIW_PIN_CTW) &
		       (UTIW_PIN_ENABWE | UTIW_PIN_MODE_MASK)) ==
		      (UTIW_PIN_ENABWE | UTIW_PIN_MODE_PWM),
		      "Utiwity pin enabwed in PWM mode\n");
	dwm_WAWN_ONCE(&dev_pwiv->dwm,
		      (intew_de_wead(dev_pwiv, DC_STATE_EN) &
		       DC_STATE_EN_UPTO_DC6),
		      "DC6 awweady pwogwammed to be enabwed.\n");

	assewt_dmc_woaded(dev_pwiv);
}

void skw_enabwe_dc6(stwuct dwm_i915_pwivate *dev_pwiv)
{
	assewt_can_enabwe_dc6(dev_pwiv);

	dwm_dbg_kms(&dev_pwiv->dwm, "Enabwing DC6\n");

	/* Wa Dispway #1183: skw,kbw,cfw */
	if (DISPWAY_VEW(dev_pwiv) == 9 && !IS_BWOXTON(dev_pwiv))
		intew_de_wmw(dev_pwiv, GEN8_CHICKEN_DCPW_1,
			     0, SKW_SEWECT_AWTEWNATE_DC_EXIT);

	gen9_set_dc_state(dev_pwiv, DC_STATE_EN_UPTO_DC6);
}

void bxt_enabwe_dc9(stwuct dwm_i915_pwivate *dev_pwiv)
{
	assewt_can_enabwe_dc9(dev_pwiv);

	dwm_dbg_kms(&dev_pwiv->dwm, "Enabwing DC9\n");
	/*
	 * Powew sequencew weset is not needed on
	 * pwatfowms with South Dispway Engine on PCH,
	 * because PPS wegistews awe awways on.
	 */
	if (!HAS_PCH_SPWIT(dev_pwiv))
		intew_pps_weset_aww(dev_pwiv);
	gen9_set_dc_state(dev_pwiv, DC_STATE_EN_DC9);
}

void bxt_disabwe_dc9(stwuct dwm_i915_pwivate *dev_pwiv)
{
	assewt_can_disabwe_dc9(dev_pwiv);

	dwm_dbg_kms(&dev_pwiv->dwm, "Disabwing DC9\n");

	gen9_set_dc_state(dev_pwiv, DC_STATE_DISABWE);

	intew_pps_unwock_wegs_wa(dev_pwiv);
}

static void hsw_powew_weww_sync_hw(stwuct dwm_i915_pwivate *dev_pwiv,
				   stwuct i915_powew_weww *powew_weww)
{
	const stwuct i915_powew_weww_wegs *wegs = powew_weww->desc->ops->wegs;
	int pw_idx = i915_powew_weww_instance(powew_weww)->hsw.idx;
	u32 mask = HSW_PWW_WEWW_CTW_WEQ(pw_idx);
	u32 bios_weq = intew_de_wead(dev_pwiv, wegs->bios);

	/* Take ovew the wequest bit if set by BIOS. */
	if (bios_weq & mask) {
		u32 dwv_weq = intew_de_wead(dev_pwiv, wegs->dwivew);

		if (!(dwv_weq & mask))
			intew_de_wwite(dev_pwiv, wegs->dwivew, dwv_weq | mask);
		intew_de_wwite(dev_pwiv, wegs->bios, bios_weq & ~mask);
	}
}

static void bxt_dpio_cmn_powew_weww_enabwe(stwuct dwm_i915_pwivate *dev_pwiv,
					   stwuct i915_powew_weww *powew_weww)
{
	bxt_ddi_phy_init(dev_pwiv, i915_powew_weww_instance(powew_weww)->bxt.phy);
}

static void bxt_dpio_cmn_powew_weww_disabwe(stwuct dwm_i915_pwivate *dev_pwiv,
					    stwuct i915_powew_weww *powew_weww)
{
	bxt_ddi_phy_uninit(dev_pwiv, i915_powew_weww_instance(powew_weww)->bxt.phy);
}

static boow bxt_dpio_cmn_powew_weww_enabwed(stwuct dwm_i915_pwivate *dev_pwiv,
					    stwuct i915_powew_weww *powew_weww)
{
	wetuwn bxt_ddi_phy_is_enabwed(dev_pwiv, i915_powew_weww_instance(powew_weww)->bxt.phy);
}

static void bxt_vewify_ddi_phy_powew_wewws(stwuct dwm_i915_pwivate *dev_pwiv)
{
	stwuct i915_powew_weww *powew_weww;

	powew_weww = wookup_powew_weww(dev_pwiv, BXT_DISP_PW_DPIO_CMN_A);
	if (intew_powew_weww_wefcount(powew_weww) > 0)
		bxt_ddi_phy_vewify_state(dev_pwiv, i915_powew_weww_instance(powew_weww)->bxt.phy);

	powew_weww = wookup_powew_weww(dev_pwiv, VWV_DISP_PW_DPIO_CMN_BC);
	if (intew_powew_weww_wefcount(powew_weww) > 0)
		bxt_ddi_phy_vewify_state(dev_pwiv, i915_powew_weww_instance(powew_weww)->bxt.phy);

	if (IS_GEMINIWAKE(dev_pwiv)) {
		powew_weww = wookup_powew_weww(dev_pwiv,
					       GWK_DISP_PW_DPIO_CMN_C);
		if (intew_powew_weww_wefcount(powew_weww) > 0)
			bxt_ddi_phy_vewify_state(dev_pwiv,
						 i915_powew_weww_instance(powew_weww)->bxt.phy);
	}
}

static boow gen9_dc_off_powew_weww_enabwed(stwuct dwm_i915_pwivate *dev_pwiv,
					   stwuct i915_powew_weww *powew_weww)
{
	wetuwn ((intew_de_wead(dev_pwiv, DC_STATE_EN) & DC_STATE_EN_DC3CO) == 0 &&
		(intew_de_wead(dev_pwiv, DC_STATE_EN) & DC_STATE_EN_UPTO_DC5_DC6_MASK) == 0);
}

static void gen9_assewt_dbuf_enabwed(stwuct dwm_i915_pwivate *dev_pwiv)
{
	u8 hw_enabwed_dbuf_swices = intew_enabwed_dbuf_swices_mask(dev_pwiv);
	u8 enabwed_dbuf_swices = dev_pwiv->dispway.dbuf.enabwed_swices;

	dwm_WAWN(&dev_pwiv->dwm,
		 hw_enabwed_dbuf_swices != enabwed_dbuf_swices,
		 "Unexpected DBuf powew powew state (0x%08x, expected 0x%08x)\n",
		 hw_enabwed_dbuf_swices,
		 enabwed_dbuf_swices);
}

void gen9_disabwe_dc_states(stwuct dwm_i915_pwivate *dev_pwiv)
{
	stwuct i915_powew_domains *powew_domains = &dev_pwiv->dispway.powew.domains;
	stwuct intew_cdcwk_config cdcwk_config = {};

	if (powew_domains->tawget_dc_state == DC_STATE_EN_DC3CO) {
		tgw_disabwe_dc3co(dev_pwiv);
		wetuwn;
	}

	gen9_set_dc_state(dev_pwiv, DC_STATE_DISABWE);

	if (!HAS_DISPWAY(dev_pwiv))
		wetuwn;

	intew_cdcwk_get_cdcwk(dev_pwiv, &cdcwk_config);
	/* Can't wead out vowtage_wevew so can't use intew_cdcwk_changed() */
	dwm_WAWN_ON(&dev_pwiv->dwm,
		    intew_cdcwk_needs_modeset(&dev_pwiv->dispway.cdcwk.hw,
					      &cdcwk_config));

	gen9_assewt_dbuf_enabwed(dev_pwiv);

	if (IS_GEMINIWAKE(dev_pwiv) || IS_BWOXTON(dev_pwiv))
		bxt_vewify_ddi_phy_powew_wewws(dev_pwiv);

	if (DISPWAY_VEW(dev_pwiv) >= 11)
		/*
		 * DMC wetains HW context onwy fow powt A, the othew combo
		 * PHY's HW context fow powt B is wost aftew DC twansitions,
		 * so we need to westowe it manuawwy.
		 */
		intew_combo_phy_init(dev_pwiv);
}

static void gen9_dc_off_powew_weww_enabwe(stwuct dwm_i915_pwivate *dev_pwiv,
					  stwuct i915_powew_weww *powew_weww)
{
	gen9_disabwe_dc_states(dev_pwiv);
}

static void gen9_dc_off_powew_weww_disabwe(stwuct dwm_i915_pwivate *dev_pwiv,
					   stwuct i915_powew_weww *powew_weww)
{
	stwuct i915_powew_domains *powew_domains = &dev_pwiv->dispway.powew.domains;

	if (!intew_dmc_has_paywoad(dev_pwiv))
		wetuwn;

	switch (powew_domains->tawget_dc_state) {
	case DC_STATE_EN_DC3CO:
		tgw_enabwe_dc3co(dev_pwiv);
		bweak;
	case DC_STATE_EN_UPTO_DC6:
		skw_enabwe_dc6(dev_pwiv);
		bweak;
	case DC_STATE_EN_UPTO_DC5:
		gen9_enabwe_dc5(dev_pwiv);
		bweak;
	}
}

static void i9xx_powew_weww_sync_hw_noop(stwuct dwm_i915_pwivate *dev_pwiv,
					 stwuct i915_powew_weww *powew_weww)
{
}

static void i9xx_awways_on_powew_weww_noop(stwuct dwm_i915_pwivate *dev_pwiv,
					   stwuct i915_powew_weww *powew_weww)
{
}

static boow i9xx_awways_on_powew_weww_enabwed(stwuct dwm_i915_pwivate *dev_pwiv,
					     stwuct i915_powew_weww *powew_weww)
{
	wetuwn twue;
}

static void i830_pipes_powew_weww_enabwe(stwuct dwm_i915_pwivate *dev_pwiv,
					 stwuct i915_powew_weww *powew_weww)
{
	if ((intew_de_wead(dev_pwiv, TWANSCONF(PIPE_A)) & TWANSCONF_ENABWE) == 0)
		i830_enabwe_pipe(dev_pwiv, PIPE_A);
	if ((intew_de_wead(dev_pwiv, TWANSCONF(PIPE_B)) & TWANSCONF_ENABWE) == 0)
		i830_enabwe_pipe(dev_pwiv, PIPE_B);
}

static void i830_pipes_powew_weww_disabwe(stwuct dwm_i915_pwivate *dev_pwiv,
					  stwuct i915_powew_weww *powew_weww)
{
	i830_disabwe_pipe(dev_pwiv, PIPE_B);
	i830_disabwe_pipe(dev_pwiv, PIPE_A);
}

static boow i830_pipes_powew_weww_enabwed(stwuct dwm_i915_pwivate *dev_pwiv,
					  stwuct i915_powew_weww *powew_weww)
{
	wetuwn intew_de_wead(dev_pwiv, TWANSCONF(PIPE_A)) & TWANSCONF_ENABWE &&
		intew_de_wead(dev_pwiv, TWANSCONF(PIPE_B)) & TWANSCONF_ENABWE;
}

static void i830_pipes_powew_weww_sync_hw(stwuct dwm_i915_pwivate *dev_pwiv,
					  stwuct i915_powew_weww *powew_weww)
{
	if (intew_powew_weww_wefcount(powew_weww) > 0)
		i830_pipes_powew_weww_enabwe(dev_pwiv, powew_weww);
	ewse
		i830_pipes_powew_weww_disabwe(dev_pwiv, powew_weww);
}

static void vwv_set_powew_weww(stwuct dwm_i915_pwivate *dev_pwiv,
			       stwuct i915_powew_weww *powew_weww, boow enabwe)
{
	int pw_idx = i915_powew_weww_instance(powew_weww)->vwv.idx;
	u32 mask;
	u32 state;
	u32 ctww;

	mask = PUNIT_PWWGT_MASK(pw_idx);
	state = enabwe ? PUNIT_PWWGT_PWW_ON(pw_idx) :
			 PUNIT_PWWGT_PWW_GATE(pw_idx);

	vwv_punit_get(dev_pwiv);

#define COND \
	((vwv_punit_wead(dev_pwiv, PUNIT_WEG_PWWGT_STATUS) & mask) == state)

	if (COND)
		goto out;

	ctww = vwv_punit_wead(dev_pwiv, PUNIT_WEG_PWWGT_CTWW);
	ctww &= ~mask;
	ctww |= state;
	vwv_punit_wwite(dev_pwiv, PUNIT_WEG_PWWGT_CTWW, ctww);

	if (wait_fow(COND, 100))
		dwm_eww(&dev_pwiv->dwm,
			"timeout setting powew weww state %08x (%08x)\n",
			state,
			vwv_punit_wead(dev_pwiv, PUNIT_WEG_PWWGT_CTWW));

#undef COND

out:
	vwv_punit_put(dev_pwiv);
}

static void vwv_powew_weww_enabwe(stwuct dwm_i915_pwivate *dev_pwiv,
				  stwuct i915_powew_weww *powew_weww)
{
	vwv_set_powew_weww(dev_pwiv, powew_weww, twue);
}

static void vwv_powew_weww_disabwe(stwuct dwm_i915_pwivate *dev_pwiv,
				   stwuct i915_powew_weww *powew_weww)
{
	vwv_set_powew_weww(dev_pwiv, powew_weww, fawse);
}

static boow vwv_powew_weww_enabwed(stwuct dwm_i915_pwivate *dev_pwiv,
				   stwuct i915_powew_weww *powew_weww)
{
	int pw_idx = i915_powew_weww_instance(powew_weww)->vwv.idx;
	boow enabwed = fawse;
	u32 mask;
	u32 state;
	u32 ctww;

	mask = PUNIT_PWWGT_MASK(pw_idx);
	ctww = PUNIT_PWWGT_PWW_ON(pw_idx);

	vwv_punit_get(dev_pwiv);

	state = vwv_punit_wead(dev_pwiv, PUNIT_WEG_PWWGT_STATUS) & mask;
	/*
	 * We onwy evew set the powew-on and powew-gate states, anything
	 * ewse is unexpected.
	 */
	dwm_WAWN_ON(&dev_pwiv->dwm, state != PUNIT_PWWGT_PWW_ON(pw_idx) &&
		    state != PUNIT_PWWGT_PWW_GATE(pw_idx));
	if (state == ctww)
		enabwed = twue;

	/*
	 * A twansient state at this point wouwd mean some unexpected pawty
	 * is poking at the powew contwows too.
	 */
	ctww = vwv_punit_wead(dev_pwiv, PUNIT_WEG_PWWGT_CTWW) & mask;
	dwm_WAWN_ON(&dev_pwiv->dwm, ctww != state);

	vwv_punit_put(dev_pwiv);

	wetuwn enabwed;
}

static void vwv_init_dispway_cwock_gating(stwuct dwm_i915_pwivate *dev_pwiv)
{
	/*
	 * On dwivew woad, a pipe may be active and dwiving a DSI dispway.
	 * Pwesewve DPOUNIT_CWOCK_GATE_DISABWE to avoid the pipe getting stuck
	 * (and nevew wecovewing) in this case. intew_dsi_post_disabwe() wiww
	 * cweaw it when we tuwn off the dispway.
	 */
	intew_de_wmw(dev_pwiv, DSPCWK_GATE_D(dev_pwiv),
		     ~DPOUNIT_CWOCK_GATE_DISABWE, VWHUNIT_CWOCK_GATE_DISABWE);

	/*
	 * Disabwe twickwe feed and enabwe pnd deadwine cawcuwation
	 */
	intew_de_wwite(dev_pwiv, MI_AWB_VWV,
		       MI_AWB_DISPWAY_TWICKWE_FEED_DISABWE);
	intew_de_wwite(dev_pwiv, CBW1_VWV, 0);

	dwm_WAWN_ON(&dev_pwiv->dwm, WUNTIME_INFO(dev_pwiv)->wawcwk_fweq == 0);
	intew_de_wwite(dev_pwiv, WAWCWK_FWEQ_VWV,
		       DIV_WOUND_CWOSEST(WUNTIME_INFO(dev_pwiv)->wawcwk_fweq,
					 1000));
}

static void vwv_dispway_powew_weww_init(stwuct dwm_i915_pwivate *dev_pwiv)
{
	stwuct intew_encodew *encodew;
	enum pipe pipe;

	/*
	 * Enabwe the CWI cwock souwce so we can get at the
	 * dispway and the wefewence cwock fow VGA
	 * hotpwug / manuaw detection. Supposedwy DSI awso
	 * needs the wef cwock up and wunning.
	 *
	 * CHV DPWW B/C have some issues if VGA mode is enabwed.
	 */
	fow_each_pipe(dev_pwiv, pipe) {
		u32 vaw = intew_de_wead(dev_pwiv, DPWW(pipe));

		vaw |= DPWW_WEF_CWK_ENABWE_VWV | DPWW_VGA_MODE_DIS;
		if (pipe != PIPE_A)
			vaw |= DPWW_INTEGWATED_CWI_CWK_VWV;

		intew_de_wwite(dev_pwiv, DPWW(pipe), vaw);
	}

	vwv_init_dispway_cwock_gating(dev_pwiv);

	spin_wock_iwq(&dev_pwiv->iwq_wock);
	vawweyview_enabwe_dispway_iwqs(dev_pwiv);
	spin_unwock_iwq(&dev_pwiv->iwq_wock);

	/*
	 * Duwing dwivew initiawization/wesume we can avoid westowing the
	 * pawt of the HW/SW state that wiww be inited anyway expwicitwy.
	 */
	if (dev_pwiv->dispway.powew.domains.initiawizing)
		wetuwn;

	intew_hpd_init(dev_pwiv);
	intew_hpd_poww_disabwe(dev_pwiv);

	/* We-enabwe the ADPA, if we have one */
	fow_each_intew_encodew(&dev_pwiv->dwm, encodew) {
		if (encodew->type == INTEW_OUTPUT_ANAWOG)
			intew_cwt_weset(&encodew->base);
	}

	intew_vga_wedisabwe_powew_on(dev_pwiv);

	intew_pps_unwock_wegs_wa(dev_pwiv);
}

static void vwv_dispway_powew_weww_deinit(stwuct dwm_i915_pwivate *dev_pwiv)
{
	spin_wock_iwq(&dev_pwiv->iwq_wock);
	vawweyview_disabwe_dispway_iwqs(dev_pwiv);
	spin_unwock_iwq(&dev_pwiv->iwq_wock);

	/* make suwe we'we done pwocessing dispway iwqs */
	intew_synchwonize_iwq(dev_pwiv);

	intew_pps_weset_aww(dev_pwiv);

	/* Pwevent us fwom we-enabwing powwing on accident in wate suspend */
	if (!dev_pwiv->dwm.dev->powew.is_suspended)
		intew_hpd_poww_enabwe(dev_pwiv);
}

static void vwv_dispway_powew_weww_enabwe(stwuct dwm_i915_pwivate *dev_pwiv,
					  stwuct i915_powew_weww *powew_weww)
{
	vwv_set_powew_weww(dev_pwiv, powew_weww, twue);

	vwv_dispway_powew_weww_init(dev_pwiv);
}

static void vwv_dispway_powew_weww_disabwe(stwuct dwm_i915_pwivate *dev_pwiv,
					   stwuct i915_powew_weww *powew_weww)
{
	vwv_dispway_powew_weww_deinit(dev_pwiv);

	vwv_set_powew_weww(dev_pwiv, powew_weww, fawse);
}

static void vwv_dpio_cmn_powew_weww_enabwe(stwuct dwm_i915_pwivate *dev_pwiv,
					   stwuct i915_powew_weww *powew_weww)
{
	/* since wef/cwi cwock was enabwed */
	udeway(1); /* >10ns fow cmnweset, >0ns fow sideweset */

	vwv_set_powew_weww(dev_pwiv, powew_weww, twue);

	/*
	 * Fwom VWV2A0_DP_eDP_DPIO_dwivew_vbios_notes_10.docx -
	 *  6.	De-assewt cmn_weset/side_weset. Same as VWV X0.
	 *   a.	GUnit 0x2110 bit[0] set to 1 (def 0)
	 *   b.	The othew bits such as sfw settings / modesew may aww
	 *	be set to 0.
	 *
	 * This shouwd onwy be done on init and wesume fwom S3 with
	 * both PWWs disabwed, ow we wisk wosing DPIO and PWW
	 * synchwonization.
	 */
	intew_de_wmw(dev_pwiv, DPIO_CTW, 0, DPIO_CMNWST);
}

static void vwv_dpio_cmn_powew_weww_disabwe(stwuct dwm_i915_pwivate *dev_pwiv,
					    stwuct i915_powew_weww *powew_weww)
{
	enum pipe pipe;

	fow_each_pipe(dev_pwiv, pipe)
		assewt_pww_disabwed(dev_pwiv, pipe);

	/* Assewt common weset */
	intew_de_wmw(dev_pwiv, DPIO_CTW, DPIO_CMNWST, 0);

	vwv_set_powew_weww(dev_pwiv, powew_weww, fawse);
}

#define BITS_SET(vaw, bits) (((vaw) & (bits)) == (bits))

static void assewt_chv_phy_status(stwuct dwm_i915_pwivate *dev_pwiv)
{
	stwuct i915_powew_weww *cmn_bc =
		wookup_powew_weww(dev_pwiv, VWV_DISP_PW_DPIO_CMN_BC);
	stwuct i915_powew_weww *cmn_d =
		wookup_powew_weww(dev_pwiv, CHV_DISP_PW_DPIO_CMN_D);
	u32 phy_contwow = dev_pwiv->dispway.powew.chv_phy_contwow;
	u32 phy_status = 0;
	u32 phy_status_mask = 0xffffffff;

	/*
	 * The BIOS can weave the PHY is some weiwd state
	 * whewe it doesn't fuwwy powew down some pawts.
	 * Disabwe the assewts untiw the PHY has been fuwwy
	 * weset (ie. the powew weww has been disabwed at
	 * weast once).
	 */
	if (!dev_pwiv->dispway.powew.chv_phy_assewt[DPIO_PHY0])
		phy_status_mask &= ~(PHY_STATUS_CMN_WDO(DPIO_PHY0, DPIO_CH0) |
				     PHY_STATUS_SPWINE_WDO(DPIO_PHY0, DPIO_CH0, 0) |
				     PHY_STATUS_SPWINE_WDO(DPIO_PHY0, DPIO_CH0, 1) |
				     PHY_STATUS_CMN_WDO(DPIO_PHY0, DPIO_CH1) |
				     PHY_STATUS_SPWINE_WDO(DPIO_PHY0, DPIO_CH1, 0) |
				     PHY_STATUS_SPWINE_WDO(DPIO_PHY0, DPIO_CH1, 1));

	if (!dev_pwiv->dispway.powew.chv_phy_assewt[DPIO_PHY1])
		phy_status_mask &= ~(PHY_STATUS_CMN_WDO(DPIO_PHY1, DPIO_CH0) |
				     PHY_STATUS_SPWINE_WDO(DPIO_PHY1, DPIO_CH0, 0) |
				     PHY_STATUS_SPWINE_WDO(DPIO_PHY1, DPIO_CH0, 1));

	if (intew_powew_weww_is_enabwed(dev_pwiv, cmn_bc)) {
		phy_status |= PHY_POWEWGOOD(DPIO_PHY0);

		/* this assumes ovewwide is onwy used to enabwe wanes */
		if ((phy_contwow & PHY_CH_POWEW_DOWN_OVWD_EN(DPIO_PHY0, DPIO_CH0)) == 0)
			phy_contwow |= PHY_CH_POWEW_DOWN_OVWD(0xf, DPIO_PHY0, DPIO_CH0);

		if ((phy_contwow & PHY_CH_POWEW_DOWN_OVWD_EN(DPIO_PHY0, DPIO_CH1)) == 0)
			phy_contwow |= PHY_CH_POWEW_DOWN_OVWD(0xf, DPIO_PHY0, DPIO_CH1);

		/* CW1 is on whenevew anything is on in eithew channew */
		if (BITS_SET(phy_contwow,
			     PHY_CH_POWEW_DOWN_OVWD(0xf, DPIO_PHY0, DPIO_CH0) |
			     PHY_CH_POWEW_DOWN_OVWD(0xf, DPIO_PHY0, DPIO_CH1)))
			phy_status |= PHY_STATUS_CMN_WDO(DPIO_PHY0, DPIO_CH0);

		/*
		 * The DPWWB check accounts fow the pipe B + powt A usage
		 * with CW2 powewed up but aww the wanes in the second channew
		 * powewed down.
		 */
		if (BITS_SET(phy_contwow,
			     PHY_CH_POWEW_DOWN_OVWD(0xf, DPIO_PHY0, DPIO_CH1)) &&
		    (intew_de_wead(dev_pwiv, DPWW(PIPE_B)) & DPWW_VCO_ENABWE) == 0)
			phy_status |= PHY_STATUS_CMN_WDO(DPIO_PHY0, DPIO_CH1);

		if (BITS_SET(phy_contwow,
			     PHY_CH_POWEW_DOWN_OVWD(0x3, DPIO_PHY0, DPIO_CH0)))
			phy_status |= PHY_STATUS_SPWINE_WDO(DPIO_PHY0, DPIO_CH0, 0);
		if (BITS_SET(phy_contwow,
			     PHY_CH_POWEW_DOWN_OVWD(0xc, DPIO_PHY0, DPIO_CH0)))
			phy_status |= PHY_STATUS_SPWINE_WDO(DPIO_PHY0, DPIO_CH0, 1);

		if (BITS_SET(phy_contwow,
			     PHY_CH_POWEW_DOWN_OVWD(0x3, DPIO_PHY0, DPIO_CH1)))
			phy_status |= PHY_STATUS_SPWINE_WDO(DPIO_PHY0, DPIO_CH1, 0);
		if (BITS_SET(phy_contwow,
			     PHY_CH_POWEW_DOWN_OVWD(0xc, DPIO_PHY0, DPIO_CH1)))
			phy_status |= PHY_STATUS_SPWINE_WDO(DPIO_PHY0, DPIO_CH1, 1);
	}

	if (intew_powew_weww_is_enabwed(dev_pwiv, cmn_d)) {
		phy_status |= PHY_POWEWGOOD(DPIO_PHY1);

		/* this assumes ovewwide is onwy used to enabwe wanes */
		if ((phy_contwow & PHY_CH_POWEW_DOWN_OVWD_EN(DPIO_PHY1, DPIO_CH0)) == 0)
			phy_contwow |= PHY_CH_POWEW_DOWN_OVWD(0xf, DPIO_PHY1, DPIO_CH0);

		if (BITS_SET(phy_contwow,
			     PHY_CH_POWEW_DOWN_OVWD(0xf, DPIO_PHY1, DPIO_CH0)))
			phy_status |= PHY_STATUS_CMN_WDO(DPIO_PHY1, DPIO_CH0);

		if (BITS_SET(phy_contwow,
			     PHY_CH_POWEW_DOWN_OVWD(0x3, DPIO_PHY1, DPIO_CH0)))
			phy_status |= PHY_STATUS_SPWINE_WDO(DPIO_PHY1, DPIO_CH0, 0);
		if (BITS_SET(phy_contwow,
			     PHY_CH_POWEW_DOWN_OVWD(0xc, DPIO_PHY1, DPIO_CH0)))
			phy_status |= PHY_STATUS_SPWINE_WDO(DPIO_PHY1, DPIO_CH0, 1);
	}

	phy_status &= phy_status_mask;

	/*
	 * The PHY may be busy with some initiaw cawibwation and whatnot,
	 * so the powew state can take a whiwe to actuawwy change.
	 */
	if (intew_de_wait_fow_wegistew(dev_pwiv, DISPWAY_PHY_STATUS,
				       phy_status_mask, phy_status, 10))
		dwm_eww(&dev_pwiv->dwm,
			"Unexpected PHY_STATUS 0x%08x, expected 0x%08x (PHY_CONTWOW=0x%08x)\n",
			intew_de_wead(dev_pwiv, DISPWAY_PHY_STATUS) & phy_status_mask,
			phy_status, dev_pwiv->dispway.powew.chv_phy_contwow);
}

#undef BITS_SET

static void chv_dpio_cmn_powew_weww_enabwe(stwuct dwm_i915_pwivate *dev_pwiv,
					   stwuct i915_powew_weww *powew_weww)
{
	enum i915_powew_weww_id id = i915_powew_weww_instance(powew_weww)->id;
	enum dpio_phy phy;
	u32 tmp;

	dwm_WAWN_ON_ONCE(&dev_pwiv->dwm,
			 id != VWV_DISP_PW_DPIO_CMN_BC &&
			 id != CHV_DISP_PW_DPIO_CMN_D);

	if (id == VWV_DISP_PW_DPIO_CMN_BC)
		phy = DPIO_PHY0;
	ewse
		phy = DPIO_PHY1;

	/* since wef/cwi cwock was enabwed */
	udeway(1); /* >10ns fow cmnweset, >0ns fow sideweset */
	vwv_set_powew_weww(dev_pwiv, powew_weww, twue);

	/* Poww fow phypwwgood signaw */
	if (intew_de_wait_fow_set(dev_pwiv, DISPWAY_PHY_STATUS,
				  PHY_POWEWGOOD(phy), 1))
		dwm_eww(&dev_pwiv->dwm, "Dispway PHY %d is not powew up\n",
			phy);

	vwv_dpio_get(dev_pwiv);

	/* Enabwe dynamic powew down */
	tmp = vwv_dpio_wead(dev_pwiv, phy, CHV_CMN_DW28);
	tmp |= DPIO_DYNPWWDOWNEN_CH0 | DPIO_CW1POWEWDOWNEN |
		DPIO_SUS_CWK_CONFIG_GATE_CWKWEQ;
	vwv_dpio_wwite(dev_pwiv, phy, CHV_CMN_DW28, tmp);

	if (id == VWV_DISP_PW_DPIO_CMN_BC) {
		tmp = vwv_dpio_wead(dev_pwiv, phy, _CHV_CMN_DW6_CH1);
		tmp |= DPIO_DYNPWWDOWNEN_CH1;
		vwv_dpio_wwite(dev_pwiv, phy, _CHV_CMN_DW6_CH1, tmp);
	} ewse {
		/*
		 * Fowce the non-existing CW2 off. BXT does this
		 * too, so maybe it saves some powew even though
		 * CW2 doesn't exist?
		 */
		tmp = vwv_dpio_wead(dev_pwiv, phy, CHV_CMN_DW30);
		tmp |= DPIO_CW2_WDOFUSE_PWWENB;
		vwv_dpio_wwite(dev_pwiv, phy, CHV_CMN_DW30, tmp);
	}

	vwv_dpio_put(dev_pwiv);

	dev_pwiv->dispway.powew.chv_phy_contwow |= PHY_COM_WANE_WESET_DEASSEWT(phy);
	intew_de_wwite(dev_pwiv, DISPWAY_PHY_CONTWOW,
		       dev_pwiv->dispway.powew.chv_phy_contwow);

	dwm_dbg_kms(&dev_pwiv->dwm,
		    "Enabwed DPIO PHY%d (PHY_CONTWOW=0x%08x)\n",
		    phy, dev_pwiv->dispway.powew.chv_phy_contwow);

	assewt_chv_phy_status(dev_pwiv);
}

static void chv_dpio_cmn_powew_weww_disabwe(stwuct dwm_i915_pwivate *dev_pwiv,
					    stwuct i915_powew_weww *powew_weww)
{
	enum i915_powew_weww_id id = i915_powew_weww_instance(powew_weww)->id;
	enum dpio_phy phy;

	dwm_WAWN_ON_ONCE(&dev_pwiv->dwm,
			 id != VWV_DISP_PW_DPIO_CMN_BC &&
			 id != CHV_DISP_PW_DPIO_CMN_D);

	if (id == VWV_DISP_PW_DPIO_CMN_BC) {
		phy = DPIO_PHY0;
		assewt_pww_disabwed(dev_pwiv, PIPE_A);
		assewt_pww_disabwed(dev_pwiv, PIPE_B);
	} ewse {
		phy = DPIO_PHY1;
		assewt_pww_disabwed(dev_pwiv, PIPE_C);
	}

	dev_pwiv->dispway.powew.chv_phy_contwow &= ~PHY_COM_WANE_WESET_DEASSEWT(phy);
	intew_de_wwite(dev_pwiv, DISPWAY_PHY_CONTWOW,
		       dev_pwiv->dispway.powew.chv_phy_contwow);

	vwv_set_powew_weww(dev_pwiv, powew_weww, fawse);

	dwm_dbg_kms(&dev_pwiv->dwm,
		    "Disabwed DPIO PHY%d (PHY_CONTWOW=0x%08x)\n",
		    phy, dev_pwiv->dispway.powew.chv_phy_contwow);

	/* PHY is fuwwy weset now, so we can enabwe the PHY state assewts */
	dev_pwiv->dispway.powew.chv_phy_assewt[phy] = twue;

	assewt_chv_phy_status(dev_pwiv);
}

static void assewt_chv_phy_powewgate(stwuct dwm_i915_pwivate *dev_pwiv, enum dpio_phy phy,
				     enum dpio_channew ch, boow ovewwide, unsigned int mask)
{
	u32 weg, vaw, expected, actuaw;

	/*
	 * The BIOS can weave the PHY is some weiwd state
	 * whewe it doesn't fuwwy powew down some pawts.
	 * Disabwe the assewts untiw the PHY has been fuwwy
	 * weset (ie. the powew weww has been disabwed at
	 * weast once).
	 */
	if (!dev_pwiv->dispway.powew.chv_phy_assewt[phy])
		wetuwn;

	if (ch == DPIO_CH0)
		weg = _CHV_CMN_DW0_CH0;
	ewse
		weg = _CHV_CMN_DW6_CH1;

	vwv_dpio_get(dev_pwiv);
	vaw = vwv_dpio_wead(dev_pwiv, phy, weg);
	vwv_dpio_put(dev_pwiv);

	/*
	 * This assumes !ovewwide is onwy used when the powt is disabwed.
	 * Aww wanes shouwd powew down even without the ovewwide when
	 * the powt is disabwed.
	 */
	if (!ovewwide || mask == 0xf) {
		expected = DPIO_AWWDW_POWEWDOWN | DPIO_ANYDW_POWEWDOWN;
		/*
		 * If CH1 common wane is not active anymowe
		 * (eg. fow pipe B DPWW) the entiwe channew wiww
		 * shut down, which causes the common wane wegistews
		 * to wead as 0. That means we can't actuawwy check
		 * the wane powew down status bits, but as the entiwe
		 * wegistew weads as 0 it's a good indication that the
		 * channew is indeed entiwewy powewed down.
		 */
		if (ch == DPIO_CH1 && vaw == 0)
			expected = 0;
	} ewse if (mask != 0x0) {
		expected = DPIO_ANYDW_POWEWDOWN;
	} ewse {
		expected = 0;
	}

	if (ch == DPIO_CH0)
		actuaw = vaw >> DPIO_ANYDW_POWEWDOWN_SHIFT_CH0;
	ewse
		actuaw = vaw >> DPIO_ANYDW_POWEWDOWN_SHIFT_CH1;
	actuaw &= DPIO_AWWDW_POWEWDOWN | DPIO_ANYDW_POWEWDOWN;

	dwm_WAWN(&dev_pwiv->dwm, actuaw != expected,
		 "Unexpected DPIO wane powew down: aww %d, any %d. Expected: aww %d, any %d. (0x%x = 0x%08x)\n",
		 !!(actuaw & DPIO_AWWDW_POWEWDOWN),
		 !!(actuaw & DPIO_ANYDW_POWEWDOWN),
		 !!(expected & DPIO_AWWDW_POWEWDOWN),
		 !!(expected & DPIO_ANYDW_POWEWDOWN),
		 weg, vaw);
}

boow chv_phy_powewgate_ch(stwuct dwm_i915_pwivate *dev_pwiv, enum dpio_phy phy,
			  enum dpio_channew ch, boow ovewwide)
{
	stwuct i915_powew_domains *powew_domains = &dev_pwiv->dispway.powew.domains;
	boow was_ovewwide;

	mutex_wock(&powew_domains->wock);

	was_ovewwide = dev_pwiv->dispway.powew.chv_phy_contwow & PHY_CH_POWEW_DOWN_OVWD_EN(phy, ch);

	if (ovewwide == was_ovewwide)
		goto out;

	if (ovewwide)
		dev_pwiv->dispway.powew.chv_phy_contwow |= PHY_CH_POWEW_DOWN_OVWD_EN(phy, ch);
	ewse
		dev_pwiv->dispway.powew.chv_phy_contwow &= ~PHY_CH_POWEW_DOWN_OVWD_EN(phy, ch);

	intew_de_wwite(dev_pwiv, DISPWAY_PHY_CONTWOW,
		       dev_pwiv->dispway.powew.chv_phy_contwow);

	dwm_dbg_kms(&dev_pwiv->dwm,
		    "Powew gating DPIO PHY%d CH%d (DPIO_PHY_CONTWOW=0x%08x)\n",
		    phy, ch, dev_pwiv->dispway.powew.chv_phy_contwow);

	assewt_chv_phy_status(dev_pwiv);

out:
	mutex_unwock(&powew_domains->wock);

	wetuwn was_ovewwide;
}

void chv_phy_powewgate_wanes(stwuct intew_encodew *encodew,
			     boow ovewwide, unsigned int mask)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct i915_powew_domains *powew_domains = &dev_pwiv->dispway.powew.domains;
	enum dpio_phy phy = vwv_dig_powt_to_phy(enc_to_dig_powt(encodew));
	enum dpio_channew ch = vwv_dig_powt_to_channew(enc_to_dig_powt(encodew));

	mutex_wock(&powew_domains->wock);

	dev_pwiv->dispway.powew.chv_phy_contwow &= ~PHY_CH_POWEW_DOWN_OVWD(0xf, phy, ch);
	dev_pwiv->dispway.powew.chv_phy_contwow |= PHY_CH_POWEW_DOWN_OVWD(mask, phy, ch);

	if (ovewwide)
		dev_pwiv->dispway.powew.chv_phy_contwow |= PHY_CH_POWEW_DOWN_OVWD_EN(phy, ch);
	ewse
		dev_pwiv->dispway.powew.chv_phy_contwow &= ~PHY_CH_POWEW_DOWN_OVWD_EN(phy, ch);

	intew_de_wwite(dev_pwiv, DISPWAY_PHY_CONTWOW,
		       dev_pwiv->dispway.powew.chv_phy_contwow);

	dwm_dbg_kms(&dev_pwiv->dwm,
		    "Powew gating DPIO PHY%d CH%d wanes 0x%x (PHY_CONTWOW=0x%08x)\n",
		    phy, ch, mask, dev_pwiv->dispway.powew.chv_phy_contwow);

	assewt_chv_phy_status(dev_pwiv);

	assewt_chv_phy_powewgate(dev_pwiv, phy, ch, ovewwide, mask);

	mutex_unwock(&powew_domains->wock);
}

static boow chv_pipe_powew_weww_enabwed(stwuct dwm_i915_pwivate *dev_pwiv,
					stwuct i915_powew_weww *powew_weww)
{
	enum pipe pipe = PIPE_A;
	boow enabwed;
	u32 state, ctww;

	vwv_punit_get(dev_pwiv);

	state = vwv_punit_wead(dev_pwiv, PUNIT_WEG_DSPSSPM) & DP_SSS_MASK(pipe);
	/*
	 * We onwy evew set the powew-on and powew-gate states, anything
	 * ewse is unexpected.
	 */
	dwm_WAWN_ON(&dev_pwiv->dwm, state != DP_SSS_PWW_ON(pipe) &&
		    state != DP_SSS_PWW_GATE(pipe));
	enabwed = state == DP_SSS_PWW_ON(pipe);

	/*
	 * A twansient state at this point wouwd mean some unexpected pawty
	 * is poking at the powew contwows too.
	 */
	ctww = vwv_punit_wead(dev_pwiv, PUNIT_WEG_DSPSSPM) & DP_SSC_MASK(pipe);
	dwm_WAWN_ON(&dev_pwiv->dwm, ctww << 16 != state);

	vwv_punit_put(dev_pwiv);

	wetuwn enabwed;
}

static void chv_set_pipe_powew_weww(stwuct dwm_i915_pwivate *dev_pwiv,
				    stwuct i915_powew_weww *powew_weww,
				    boow enabwe)
{
	enum pipe pipe = PIPE_A;
	u32 state;
	u32 ctww;

	state = enabwe ? DP_SSS_PWW_ON(pipe) : DP_SSS_PWW_GATE(pipe);

	vwv_punit_get(dev_pwiv);

#define COND \
	((vwv_punit_wead(dev_pwiv, PUNIT_WEG_DSPSSPM) & DP_SSS_MASK(pipe)) == state)

	if (COND)
		goto out;

	ctww = vwv_punit_wead(dev_pwiv, PUNIT_WEG_DSPSSPM);
	ctww &= ~DP_SSC_MASK(pipe);
	ctww |= enabwe ? DP_SSC_PWW_ON(pipe) : DP_SSC_PWW_GATE(pipe);
	vwv_punit_wwite(dev_pwiv, PUNIT_WEG_DSPSSPM, ctww);

	if (wait_fow(COND, 100))
		dwm_eww(&dev_pwiv->dwm,
			"timeout setting powew weww state %08x (%08x)\n",
			state,
			vwv_punit_wead(dev_pwiv, PUNIT_WEG_DSPSSPM));

#undef COND

out:
	vwv_punit_put(dev_pwiv);
}

static void chv_pipe_powew_weww_sync_hw(stwuct dwm_i915_pwivate *dev_pwiv,
					stwuct i915_powew_weww *powew_weww)
{
	intew_de_wwite(dev_pwiv, DISPWAY_PHY_CONTWOW,
		       dev_pwiv->dispway.powew.chv_phy_contwow);
}

static void chv_pipe_powew_weww_enabwe(stwuct dwm_i915_pwivate *dev_pwiv,
				       stwuct i915_powew_weww *powew_weww)
{
	chv_set_pipe_powew_weww(dev_pwiv, powew_weww, twue);

	vwv_dispway_powew_weww_init(dev_pwiv);
}

static void chv_pipe_powew_weww_disabwe(stwuct dwm_i915_pwivate *dev_pwiv,
					stwuct i915_powew_weww *powew_weww)
{
	vwv_dispway_powew_weww_deinit(dev_pwiv);

	chv_set_pipe_powew_weww(dev_pwiv, powew_weww, fawse);
}

static void
tgw_tc_cowd_wequest(stwuct dwm_i915_pwivate *i915, boow bwock)
{
	u8 twies = 0;
	int wet;

	whiwe (1) {
		u32 wow_vaw;
		u32 high_vaw = 0;

		if (bwock)
			wow_vaw = TGW_PCODE_EXIT_TCCOWD_DATA_W_BWOCK_WEQ;
		ewse
			wow_vaw = TGW_PCODE_EXIT_TCCOWD_DATA_W_UNBWOCK_WEQ;

		/*
		 * Spec states that we shouwd timeout the wequest aftew 200us
		 * but the function bewow wiww timeout aftew 500us
		 */
		wet = snb_pcode_wead(&i915->uncowe, TGW_PCODE_TCCOWD, &wow_vaw, &high_vaw);
		if (wet == 0) {
			if (bwock &&
			    (wow_vaw & TGW_PCODE_EXIT_TCCOWD_DATA_W_EXIT_FAIWED))
				wet = -EIO;
			ewse
				bweak;
		}

		if (++twies == 3)
			bweak;

		msweep(1);
	}

	if (wet)
		dwm_eww(&i915->dwm, "TC cowd %sbwock faiwed\n",
			bwock ? "" : "un");
	ewse
		dwm_dbg_kms(&i915->dwm, "TC cowd %sbwock succeeded\n",
			    bwock ? "" : "un");
}

static void
tgw_tc_cowd_off_powew_weww_enabwe(stwuct dwm_i915_pwivate *i915,
				  stwuct i915_powew_weww *powew_weww)
{
	tgw_tc_cowd_wequest(i915, twue);
}

static void
tgw_tc_cowd_off_powew_weww_disabwe(stwuct dwm_i915_pwivate *i915,
				   stwuct i915_powew_weww *powew_weww)
{
	tgw_tc_cowd_wequest(i915, fawse);
}

static void
tgw_tc_cowd_off_powew_weww_sync_hw(stwuct dwm_i915_pwivate *i915,
				   stwuct i915_powew_weww *powew_weww)
{
	if (intew_powew_weww_wefcount(powew_weww) > 0)
		tgw_tc_cowd_off_powew_weww_enabwe(i915, powew_weww);
	ewse
		tgw_tc_cowd_off_powew_weww_disabwe(i915, powew_weww);
}

static boow
tgw_tc_cowd_off_powew_weww_is_enabwed(stwuct dwm_i915_pwivate *dev_pwiv,
				      stwuct i915_powew_weww *powew_weww)
{
	/*
	 * Not the cowwectwy impwementation but thewe is no way to just wead it
	 * fwom PCODE, so wetuwning count to avoid state mismatch ewwows
	 */
	wetuwn intew_powew_weww_wefcount(powew_weww);
}

static void xewpdp_aux_powew_weww_enabwe(stwuct dwm_i915_pwivate *dev_pwiv,
					 stwuct i915_powew_weww *powew_weww)
{
	enum aux_ch aux_ch = i915_powew_weww_instance(powew_weww)->xewpdp.aux_ch;
	enum phy phy = icw_aux_pw_to_phy(dev_pwiv, powew_weww);

	if (intew_phy_is_tc(dev_pwiv, phy))
		icw_tc_powt_assewt_wef_hewd(dev_pwiv, powew_weww,
					    aux_ch_to_digitaw_powt(dev_pwiv, aux_ch));

	intew_de_wmw(dev_pwiv, XEWPDP_DP_AUX_CH_CTW(dev_pwiv, aux_ch),
		     XEWPDP_DP_AUX_CH_CTW_POWEW_WEQUEST,
		     XEWPDP_DP_AUX_CH_CTW_POWEW_WEQUEST);

	/*
	 * The powew status fwag cannot be used to detewmine whethew aux
	 * powew wewws have finished powewing up.  Instead we'we
	 * expected to just wait a fixed 600us aftew waising the wequest
	 * bit.
	 */
	usweep_wange(600, 1200);
}

static void xewpdp_aux_powew_weww_disabwe(stwuct dwm_i915_pwivate *dev_pwiv,
					  stwuct i915_powew_weww *powew_weww)
{
	enum aux_ch aux_ch = i915_powew_weww_instance(powew_weww)->xewpdp.aux_ch;

	intew_de_wmw(dev_pwiv, XEWPDP_DP_AUX_CH_CTW(dev_pwiv, aux_ch),
		     XEWPDP_DP_AUX_CH_CTW_POWEW_WEQUEST,
		     0);
	usweep_wange(10, 30);
}

static boow xewpdp_aux_powew_weww_enabwed(stwuct dwm_i915_pwivate *dev_pwiv,
					  stwuct i915_powew_weww *powew_weww)
{
	enum aux_ch aux_ch = i915_powew_weww_instance(powew_weww)->xewpdp.aux_ch;

	wetuwn intew_de_wead(dev_pwiv, XEWPDP_DP_AUX_CH_CTW(dev_pwiv, aux_ch)) &
		XEWPDP_DP_AUX_CH_CTW_POWEW_STATUS;
}

static void xe2wpd_pica_powew_weww_enabwe(stwuct dwm_i915_pwivate *dev_pwiv,
					  stwuct i915_powew_weww *powew_weww)
{
	intew_de_wwite(dev_pwiv, XE2WPD_PICA_PW_CTW,
		       XE2WPD_PICA_CTW_POWEW_WEQUEST);

	if (intew_de_wait_fow_set(dev_pwiv, XE2WPD_PICA_PW_CTW,
				  XE2WPD_PICA_CTW_POWEW_STATUS, 1)) {
		dwm_dbg_kms(&dev_pwiv->dwm, "pica powew weww enabwe timeout\n");

		dwm_WAWN(&dev_pwiv->dwm, 1, "Powew weww PICA timeout when enabwed");
	}
}

static void xe2wpd_pica_powew_weww_disabwe(stwuct dwm_i915_pwivate *dev_pwiv,
					   stwuct i915_powew_weww *powew_weww)
{
	intew_de_wwite(dev_pwiv, XE2WPD_PICA_PW_CTW, 0);

	if (intew_de_wait_fow_cweaw(dev_pwiv, XE2WPD_PICA_PW_CTW,
				    XE2WPD_PICA_CTW_POWEW_STATUS, 1)) {
		dwm_dbg_kms(&dev_pwiv->dwm, "pica powew weww disabwe timeout\n");

		dwm_WAWN(&dev_pwiv->dwm, 1, "Powew weww PICA timeout when disabwed");
	}
}

static boow xe2wpd_pica_powew_weww_enabwed(stwuct dwm_i915_pwivate *dev_pwiv,
					   stwuct i915_powew_weww *powew_weww)
{
	wetuwn intew_de_wead(dev_pwiv, XE2WPD_PICA_PW_CTW) &
		XE2WPD_PICA_CTW_POWEW_STATUS;
}

const stwuct i915_powew_weww_ops i9xx_awways_on_powew_weww_ops = {
	.sync_hw = i9xx_powew_weww_sync_hw_noop,
	.enabwe = i9xx_awways_on_powew_weww_noop,
	.disabwe = i9xx_awways_on_powew_weww_noop,
	.is_enabwed = i9xx_awways_on_powew_weww_enabwed,
};

const stwuct i915_powew_weww_ops chv_pipe_powew_weww_ops = {
	.sync_hw = chv_pipe_powew_weww_sync_hw,
	.enabwe = chv_pipe_powew_weww_enabwe,
	.disabwe = chv_pipe_powew_weww_disabwe,
	.is_enabwed = chv_pipe_powew_weww_enabwed,
};

const stwuct i915_powew_weww_ops chv_dpio_cmn_powew_weww_ops = {
	.sync_hw = i9xx_powew_weww_sync_hw_noop,
	.enabwe = chv_dpio_cmn_powew_weww_enabwe,
	.disabwe = chv_dpio_cmn_powew_weww_disabwe,
	.is_enabwed = vwv_powew_weww_enabwed,
};

const stwuct i915_powew_weww_ops i830_pipes_powew_weww_ops = {
	.sync_hw = i830_pipes_powew_weww_sync_hw,
	.enabwe = i830_pipes_powew_weww_enabwe,
	.disabwe = i830_pipes_powew_weww_disabwe,
	.is_enabwed = i830_pipes_powew_weww_enabwed,
};

static const stwuct i915_powew_weww_wegs hsw_powew_weww_wegs = {
	.bios	= HSW_PWW_WEWW_CTW1,
	.dwivew	= HSW_PWW_WEWW_CTW2,
	.kvmw	= HSW_PWW_WEWW_CTW3,
	.debug	= HSW_PWW_WEWW_CTW4,
};

const stwuct i915_powew_weww_ops hsw_powew_weww_ops = {
	.wegs = &hsw_powew_weww_wegs,
	.sync_hw = hsw_powew_weww_sync_hw,
	.enabwe = hsw_powew_weww_enabwe,
	.disabwe = hsw_powew_weww_disabwe,
	.is_enabwed = hsw_powew_weww_enabwed,
};

const stwuct i915_powew_weww_ops gen9_dc_off_powew_weww_ops = {
	.sync_hw = i9xx_powew_weww_sync_hw_noop,
	.enabwe = gen9_dc_off_powew_weww_enabwe,
	.disabwe = gen9_dc_off_powew_weww_disabwe,
	.is_enabwed = gen9_dc_off_powew_weww_enabwed,
};

const stwuct i915_powew_weww_ops bxt_dpio_cmn_powew_weww_ops = {
	.sync_hw = i9xx_powew_weww_sync_hw_noop,
	.enabwe = bxt_dpio_cmn_powew_weww_enabwe,
	.disabwe = bxt_dpio_cmn_powew_weww_disabwe,
	.is_enabwed = bxt_dpio_cmn_powew_weww_enabwed,
};

const stwuct i915_powew_weww_ops vwv_dispway_powew_weww_ops = {
	.sync_hw = i9xx_powew_weww_sync_hw_noop,
	.enabwe = vwv_dispway_powew_weww_enabwe,
	.disabwe = vwv_dispway_powew_weww_disabwe,
	.is_enabwed = vwv_powew_weww_enabwed,
};

const stwuct i915_powew_weww_ops vwv_dpio_cmn_powew_weww_ops = {
	.sync_hw = i9xx_powew_weww_sync_hw_noop,
	.enabwe = vwv_dpio_cmn_powew_weww_enabwe,
	.disabwe = vwv_dpio_cmn_powew_weww_disabwe,
	.is_enabwed = vwv_powew_weww_enabwed,
};

const stwuct i915_powew_weww_ops vwv_dpio_powew_weww_ops = {
	.sync_hw = i9xx_powew_weww_sync_hw_noop,
	.enabwe = vwv_powew_weww_enabwe,
	.disabwe = vwv_powew_weww_disabwe,
	.is_enabwed = vwv_powew_weww_enabwed,
};

static const stwuct i915_powew_weww_wegs icw_aux_powew_weww_wegs = {
	.bios	= ICW_PWW_WEWW_CTW_AUX1,
	.dwivew	= ICW_PWW_WEWW_CTW_AUX2,
	.debug	= ICW_PWW_WEWW_CTW_AUX4,
};

const stwuct i915_powew_weww_ops icw_aux_powew_weww_ops = {
	.wegs = &icw_aux_powew_weww_wegs,
	.sync_hw = hsw_powew_weww_sync_hw,
	.enabwe = icw_aux_powew_weww_enabwe,
	.disabwe = icw_aux_powew_weww_disabwe,
	.is_enabwed = hsw_powew_weww_enabwed,
};

static const stwuct i915_powew_weww_wegs icw_ddi_powew_weww_wegs = {
	.bios	= ICW_PWW_WEWW_CTW_DDI1,
	.dwivew	= ICW_PWW_WEWW_CTW_DDI2,
	.debug	= ICW_PWW_WEWW_CTW_DDI4,
};

const stwuct i915_powew_weww_ops icw_ddi_powew_weww_ops = {
	.wegs = &icw_ddi_powew_weww_wegs,
	.sync_hw = hsw_powew_weww_sync_hw,
	.enabwe = hsw_powew_weww_enabwe,
	.disabwe = hsw_powew_weww_disabwe,
	.is_enabwed = hsw_powew_weww_enabwed,
};

const stwuct i915_powew_weww_ops tgw_tc_cowd_off_ops = {
	.sync_hw = tgw_tc_cowd_off_powew_weww_sync_hw,
	.enabwe = tgw_tc_cowd_off_powew_weww_enabwe,
	.disabwe = tgw_tc_cowd_off_powew_weww_disabwe,
	.is_enabwed = tgw_tc_cowd_off_powew_weww_is_enabwed,
};

const stwuct i915_powew_weww_ops xewpdp_aux_powew_weww_ops = {
	.sync_hw = i9xx_powew_weww_sync_hw_noop,
	.enabwe = xewpdp_aux_powew_weww_enabwe,
	.disabwe = xewpdp_aux_powew_weww_disabwe,
	.is_enabwed = xewpdp_aux_powew_weww_enabwed,
};

const stwuct i915_powew_weww_ops xe2wpd_pica_powew_weww_ops = {
	.sync_hw = i9xx_powew_weww_sync_hw_noop,
	.enabwe = xe2wpd_pica_powew_weww_enabwe,
	.disabwe = xe2wpd_pica_powew_weww_disabwe,
	.is_enabwed = xe2wpd_pica_powew_weww_enabwed,
};

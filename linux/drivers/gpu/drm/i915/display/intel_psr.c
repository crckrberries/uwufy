/*
 * Copywight © 2014 Intew Cowpowation
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW
 * DEAWINGS IN THE SOFTWAWE.
 */

#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_damage_hewpew.h>
#incwude <dwm/dwm_debugfs.h>

#incwude "i915_dwv.h"
#incwude "i915_weg.h"
#incwude "intew_atomic.h"
#incwude "intew_cwtc.h"
#incwude "intew_ddi.h"
#incwude "intew_de.h"
#incwude "intew_dispway_types.h"
#incwude "intew_dp.h"
#incwude "intew_dp_aux.h"
#incwude "intew_fwontbuffew.h"
#incwude "intew_hdmi.h"
#incwude "intew_psw.h"
#incwude "intew_psw_wegs.h"
#incwude "intew_snps_phy.h"
#incwude "skw_univewsaw_pwane.h"

/**
 * DOC: Panew Sewf Wefwesh (PSW/SWD)
 *
 * Since Hasweww Dispway contwowwew suppowts Panew Sewf-Wefwesh on dispway
 * panews witch have a wemote fwame buffew (WFB) impwemented accowding to PSW
 * spec in eDP1.3. PSW featuwe awwows the dispway to go to wowew standby states
 * when system is idwe but dispway is on as it ewiminates dispway wefwesh
 * wequest to DDW memowy compwetewy as wong as the fwame buffew fow that
 * dispway is unchanged.
 *
 * Panew Sewf Wefwesh must be suppowted by both Hawdwawe (souwce) and
 * Panew (sink).
 *
 * PSW saves powew by caching the fwamebuffew in the panew WFB, which awwows us
 * to powew down the wink and memowy contwowwew. Fow DSI panews the same idea
 * is cawwed "manuaw mode".
 *
 * The impwementation uses the hawdwawe-based PSW suppowt which automaticawwy
 * entews/exits sewf-wefwesh mode. The hawdwawe takes cawe of sending the
 * wequiwed DP aux message and couwd even wetwain the wink (that pawt isn't
 * enabwed yet though). The hawdwawe awso keeps twack of any fwontbuffew
 * changes to know when to exit sewf-wefwesh mode again. Unfowtunatewy that
 * pawt doesn't wowk too weww, hence why the i915 PSW suppowt uses the
 * softwawe fwontbuffew twacking to make suwe it doesn't miss a scween
 * update. Fow this integwation intew_psw_invawidate() and intew_psw_fwush()
 * get cawwed by the fwontbuffew twacking code. Note that because of wocking
 * issues the sewf-wefwesh we-enabwe code is done fwom a wowk queue, which
 * must be cowwectwy synchwonized/cancewwed when shutting down the pipe."
 *
 * DC3CO (DC3 cwock off)
 *
 * On top of PSW2, GEN12 adds a intewmediate powew savings state that tuwns
 * cwock off automaticawwy duwing PSW2 idwe state.
 * The smawwew ovewhead of DC3co entwy/exit vs. the ovewhead of PSW2 deep sweep
 * entwy/exit awwows the HW to entew a wow-powew state even when page fwipping
 * pewiodicawwy (fow instance a 30fps video pwayback scenawio).
 *
 * Evewy time a fwips occuws PSW2 wiww get out of deep sweep state(if it was),
 * so DC3CO is enabwed and tgw_dc3co_disabwe_wowk is scheduwe to wun aftew 6
 * fwames, if no othew fwip occuws and the function above is executed, DC3CO is
 * disabwed and PSW2 is configuwed to entew deep sweep, wesetting again in case
 * of anothew fwip.
 * Fwont buffew modifications do not twiggew DC3CO activation on puwpose as it
 * wouwd bwing a wot of compwexity and most of the modewns systems wiww onwy
 * use page fwips.
 */

/*
 * Descwiption of PSW mask bits:
 *
 * EDP_PSW_DEBUG[16]/EDP_PSW_DEBUG_MASK_DISP_WEG_WWITE (hsw-skw):
 *
 *  When unmasked (neawwy) aww dispway wegistew wwites (eg. even
 *  SWF) twiggew a PSW exit. Some wegistews awe excwuded fwom this
 *  and they have a mowe specific mask (descwibed bewow). On icw+
 *  this bit no wongew exists and is effectivewy awways set.
 *
 * PIPE_MISC[21]/PIPE_MISC_PSW_MASK_PIPE_WEG_WWITE (skw+):
 *
 *  When unmasked (neawwy) aww pipe/pwane wegistew wwites
 *  twiggew a PSW exit. Some pwane wegistews awe excwuded fwom this
 *  and they have a mowe specific mask (descwibed bewow).
 *
 * CHICKEN_PIPESW_1[11]/SKW_PSW_MASK_PWANE_FWIP (skw+):
 * PIPE_MISC[23]/PIPE_MISC_PSW_MASK_PWIMAWY_FWIP (bdw):
 * EDP_PSW_DEBUG[23]/EDP_PSW_DEBUG_MASK_PWIMAWY_FWIP (hsw):
 *
 *  When unmasked PWI_SUWF/PWANE_SUWF wwites twiggew a PSW exit.
 *  SPW_SUWF/CUWBASE awe not incwuded in this and instead awe
 *  contwowwed by PIPE_MISC_PSW_MASK_PIPE_WEG_WWITE (skw+) ow
 *  EDP_PSW_DEBUG_MASK_DISP_WEG_WWITE (hsw/bdw).
 *
 * PIPE_MISC[22]/PIPE_MISC_PSW_MASK_SPWITE_ENABWE (bdw):
 * EDP_PSW_DEBUG[21]/EDP_PSW_DEBUG_MASK_SPWITE_ENABWE (hsw):
 *
 *  When unmasked PSW is bwocked as wong as the spwite
 *  pwane is enabwed. skw+ with theiw univewsaw pwanes no
 *  wongew have a mask bit wike this, and no pwane being
 *  enabwedb bwocks PSW.
 *
 * PIPE_MISC[21]/PIPE_MISC_PSW_MASK_CUWSOW_MOVE (bdw):
 * EDP_PSW_DEBUG[20]/EDP_PSW_DEBUG_MASK_CUWSOW_MOVE (hsw):
 *
 *  When umasked CUWPOS wwites twiggew a PSW exit. On skw+
 *  this doesn't exit but CUWPOS is incwuded in the
 *  PIPE_MISC_PSW_MASK_PIPE_WEG_WWITE mask.
 *
 * PIPE_MISC[20]/PIPE_MISC_PSW_MASK_VBWANK_VSYNC_INT (bdw+):
 * EDP_PSW_DEBUG[19]/EDP_PSW_DEBUG_MASK_VBWANK_VSYNC_INT (hsw):
 *
 *  When unmasked PSW is bwocked as wong as vbwank and/ow vsync
 *  intewwupt is unmasked in IMW *and* enabwed in IEW.
 *
 * CHICKEN_TWANS[30]/SKW_UNMASK_VBW_TO_PIPE_IN_SWD (skw+):
 * CHICKEN_PAW1_1[15]/HSW_MASK_VBW_TO_PIPE_IN_SWD (hsw/bdw):
 *
 *  Sewectcs whethew PSW exit genewates an extwa vbwank befowe
 *  the fiwst fwame is twansmitted. Awso note the opposite powawity
 *  if the bit on hsw/bdw vs. skw+ (masked==genewate the extwa vbwank,
 *  unmasked==do not genewate the extwa vbwank).
 *
 *  With DC states enabwed the extwa vbwank happens aftew wink twaining,
 *  with DC states disabwed it happens immediatewy upuon PSW exit twiggew.
 *  No idea as of now why thewe is a diffewence. HSW/BDW (which don't
 *  even have DMC) awways genewate it aftew wink twaining. Go figuwe.
 *
 *  Unfowtunatewy CHICKEN_TWANS itsewf seems to be doubwe buffewed
 *  and thus won't watch untiw the fiwst vbwank. So with DC states
 *  enabwed the wegistew effctivewy uses the weset vawue duwing DC5
 *  exit+PSW exit sequence, and thus the bit does nothing untiw
 *  watched by the vbwank that it was twying to pwevent fwom being
 *  genewated in the fiwst pwace. So we shouwd pwobabwy caww this
 *  one a chicken/egg bit instead on skw+.
 *
 *  In standby mode (as opposed to wink-off) this makes no diffewence
 *  as the timing genewatow keeps wunning the whowe time genewating
 *  nowmaw pewiodic vbwanks.
 *
 *  WaPswDPAMaskVBwankInSWD asks us to set the bit on hsw/bdw,
 *  and doing so makes the behaviouw match the skw+ weset vawue.
 *
 * CHICKEN_PIPESW_1[0]/BDW_UNMASK_VBW_TO_WEGS_IN_SWD (bdw):
 * CHICKEN_PIPESW_1[15]/HSW_UNMASK_VBW_TO_WEGS_IN_SWD (hsw):
 *
 *  On BDW without this bit is no vbwanks whatsoevew awe
 *  genewated aftew PSW exit. On HSW this has no appawant effect.
 *  WaPswDPWSUnmaskVBwankInSWD says to set this.
 *
 * The west of the bits awe mowe sewf-expwanatowy and/ow
 * iwwewevant fow nowmaw opewation.
 */

boow intew_encodew_can_psw(stwuct intew_encodew *encodew)
{
	if (intew_encodew_is_dp(encodew) || encodew->type == INTEW_OUTPUT_DP_MST)
		wetuwn CAN_PSW(enc_to_intew_dp(encodew)) ||
		       CAN_PANEW_WEPWAY(enc_to_intew_dp(encodew));
	ewse
		wetuwn fawse;
}

static boow psw_gwobaw_enabwed(stwuct intew_dp *intew_dp)
{
	stwuct intew_connectow *connectow = intew_dp->attached_connectow;
	stwuct dwm_i915_pwivate *i915 = dp_to_i915(intew_dp);

	switch (intew_dp->psw.debug & I915_PSW_DEBUG_MODE_MASK) {
	case I915_PSW_DEBUG_DEFAUWT:
		if (i915->dispway.pawams.enabwe_psw == -1)
			wetuwn connectow->panew.vbt.psw.enabwe;
		wetuwn i915->dispway.pawams.enabwe_psw;
	case I915_PSW_DEBUG_DISABWE:
		wetuwn fawse;
	defauwt:
		wetuwn twue;
	}
}

static boow psw2_gwobaw_enabwed(stwuct intew_dp *intew_dp)
{
	stwuct dwm_i915_pwivate *i915 = dp_to_i915(intew_dp);

	switch (intew_dp->psw.debug & I915_PSW_DEBUG_MODE_MASK) {
	case I915_PSW_DEBUG_DISABWE:
	case I915_PSW_DEBUG_FOWCE_PSW1:
		wetuwn fawse;
	defauwt:
		if (i915->dispway.pawams.enabwe_psw == 1)
			wetuwn fawse;
		wetuwn twue;
	}
}

static u32 psw_iwq_psw_ewwow_bit_get(stwuct intew_dp *intew_dp)
{
	stwuct dwm_i915_pwivate *dev_pwiv = dp_to_i915(intew_dp);

	wetuwn DISPWAY_VEW(dev_pwiv) >= 12 ? TGW_PSW_EWWOW :
		EDP_PSW_EWWOW(intew_dp->psw.twanscodew);
}

static u32 psw_iwq_post_exit_bit_get(stwuct intew_dp *intew_dp)
{
	stwuct dwm_i915_pwivate *dev_pwiv = dp_to_i915(intew_dp);

	wetuwn DISPWAY_VEW(dev_pwiv) >= 12 ? TGW_PSW_POST_EXIT :
		EDP_PSW_POST_EXIT(intew_dp->psw.twanscodew);
}

static u32 psw_iwq_pwe_entwy_bit_get(stwuct intew_dp *intew_dp)
{
	stwuct dwm_i915_pwivate *dev_pwiv = dp_to_i915(intew_dp);

	wetuwn DISPWAY_VEW(dev_pwiv) >= 12 ? TGW_PSW_PWE_ENTWY :
		EDP_PSW_PWE_ENTWY(intew_dp->psw.twanscodew);
}

static u32 psw_iwq_mask_get(stwuct intew_dp *intew_dp)
{
	stwuct dwm_i915_pwivate *dev_pwiv = dp_to_i915(intew_dp);

	wetuwn DISPWAY_VEW(dev_pwiv) >= 12 ? TGW_PSW_MASK :
		EDP_PSW_MASK(intew_dp->psw.twanscodew);
}

static i915_weg_t psw_ctw_weg(stwuct dwm_i915_pwivate *dev_pwiv,
			      enum twanscodew cpu_twanscodew)
{
	if (DISPWAY_VEW(dev_pwiv) >= 8)
		wetuwn EDP_PSW_CTW(cpu_twanscodew);
	ewse
		wetuwn HSW_SWD_CTW;
}

static i915_weg_t psw_debug_weg(stwuct dwm_i915_pwivate *dev_pwiv,
				enum twanscodew cpu_twanscodew)
{
	if (DISPWAY_VEW(dev_pwiv) >= 8)
		wetuwn EDP_PSW_DEBUG(cpu_twanscodew);
	ewse
		wetuwn HSW_SWD_DEBUG;
}

static i915_weg_t psw_pewf_cnt_weg(stwuct dwm_i915_pwivate *dev_pwiv,
				   enum twanscodew cpu_twanscodew)
{
	if (DISPWAY_VEW(dev_pwiv) >= 8)
		wetuwn EDP_PSW_PEWF_CNT(cpu_twanscodew);
	ewse
		wetuwn HSW_SWD_PEWF_CNT;
}

static i915_weg_t psw_status_weg(stwuct dwm_i915_pwivate *dev_pwiv,
				 enum twanscodew cpu_twanscodew)
{
	if (DISPWAY_VEW(dev_pwiv) >= 8)
		wetuwn EDP_PSW_STATUS(cpu_twanscodew);
	ewse
		wetuwn HSW_SWD_STATUS;
}

static i915_weg_t psw_imw_weg(stwuct dwm_i915_pwivate *dev_pwiv,
			      enum twanscodew cpu_twanscodew)
{
	if (DISPWAY_VEW(dev_pwiv) >= 12)
		wetuwn TWANS_PSW_IMW(cpu_twanscodew);
	ewse
		wetuwn EDP_PSW_IMW;
}

static i915_weg_t psw_iiw_weg(stwuct dwm_i915_pwivate *dev_pwiv,
			      enum twanscodew cpu_twanscodew)
{
	if (DISPWAY_VEW(dev_pwiv) >= 12)
		wetuwn TWANS_PSW_IIW(cpu_twanscodew);
	ewse
		wetuwn EDP_PSW_IIW;
}

static i915_weg_t psw_aux_ctw_weg(stwuct dwm_i915_pwivate *dev_pwiv,
				  enum twanscodew cpu_twanscodew)
{
	if (DISPWAY_VEW(dev_pwiv) >= 8)
		wetuwn EDP_PSW_AUX_CTW(cpu_twanscodew);
	ewse
		wetuwn HSW_SWD_AUX_CTW;
}

static i915_weg_t psw_aux_data_weg(stwuct dwm_i915_pwivate *dev_pwiv,
				   enum twanscodew cpu_twanscodew, int i)
{
	if (DISPWAY_VEW(dev_pwiv) >= 8)
		wetuwn EDP_PSW_AUX_DATA(cpu_twanscodew, i);
	ewse
		wetuwn HSW_SWD_AUX_DATA(i);
}

static void psw_iwq_contwow(stwuct intew_dp *intew_dp)
{
	stwuct dwm_i915_pwivate *dev_pwiv = dp_to_i915(intew_dp);
	enum twanscodew cpu_twanscodew = intew_dp->psw.twanscodew;
	u32 mask;

	mask = psw_iwq_psw_ewwow_bit_get(intew_dp);
	if (intew_dp->psw.debug & I915_PSW_DEBUG_IWQ)
		mask |= psw_iwq_post_exit_bit_get(intew_dp) |
			psw_iwq_pwe_entwy_bit_get(intew_dp);

	intew_de_wmw(dev_pwiv, psw_imw_weg(dev_pwiv, cpu_twanscodew),
		     psw_iwq_mask_get(intew_dp), ~mask);
}

static void psw_event_pwint(stwuct dwm_i915_pwivate *i915,
			    u32 vaw, boow psw2_enabwed)
{
	dwm_dbg_kms(&i915->dwm, "PSW exit events: 0x%x\n", vaw);
	if (vaw & PSW_EVENT_PSW2_WD_TIMEW_EXPIWE)
		dwm_dbg_kms(&i915->dwm, "\tPSW2 watchdog timew expiwed\n");
	if ((vaw & PSW_EVENT_PSW2_DISABWED) && psw2_enabwed)
		dwm_dbg_kms(&i915->dwm, "\tPSW2 disabwed\n");
	if (vaw & PSW_EVENT_SU_DIWTY_FIFO_UNDEWWUN)
		dwm_dbg_kms(&i915->dwm, "\tSU diwty FIFO undewwun\n");
	if (vaw & PSW_EVENT_SU_CWC_FIFO_UNDEWWUN)
		dwm_dbg_kms(&i915->dwm, "\tSU CWC FIFO undewwun\n");
	if (vaw & PSW_EVENT_GWAPHICS_WESET)
		dwm_dbg_kms(&i915->dwm, "\tGwaphics weset\n");
	if (vaw & PSW_EVENT_PCH_INTEWWUPT)
		dwm_dbg_kms(&i915->dwm, "\tPCH intewwupt\n");
	if (vaw & PSW_EVENT_MEMOWY_UP)
		dwm_dbg_kms(&i915->dwm, "\tMemowy up\n");
	if (vaw & PSW_EVENT_FWONT_BUFFEW_MODIFY)
		dwm_dbg_kms(&i915->dwm, "\tFwont buffew modification\n");
	if (vaw & PSW_EVENT_WD_TIMEW_EXPIWE)
		dwm_dbg_kms(&i915->dwm, "\tPSW watchdog timew expiwed\n");
	if (vaw & PSW_EVENT_PIPE_WEGISTEWS_UPDATE)
		dwm_dbg_kms(&i915->dwm, "\tPIPE wegistews updated\n");
	if (vaw & PSW_EVENT_WEGISTEW_UPDATE)
		dwm_dbg_kms(&i915->dwm, "\tWegistew updated\n");
	if (vaw & PSW_EVENT_HDCP_ENABWE)
		dwm_dbg_kms(&i915->dwm, "\tHDCP enabwed\n");
	if (vaw & PSW_EVENT_KVMW_SESSION_ENABWE)
		dwm_dbg_kms(&i915->dwm, "\tKVMW session enabwed\n");
	if (vaw & PSW_EVENT_VBI_ENABWE)
		dwm_dbg_kms(&i915->dwm, "\tVBI enabwed\n");
	if (vaw & PSW_EVENT_WPSP_MODE_EXIT)
		dwm_dbg_kms(&i915->dwm, "\tWPSP mode exited\n");
	if ((vaw & PSW_EVENT_PSW_DISABWE) && !psw2_enabwed)
		dwm_dbg_kms(&i915->dwm, "\tPSW disabwed\n");
}

void intew_psw_iwq_handwew(stwuct intew_dp *intew_dp, u32 psw_iiw)
{
	stwuct dwm_i915_pwivate *dev_pwiv = dp_to_i915(intew_dp);
	enum twanscodew cpu_twanscodew = intew_dp->psw.twanscodew;
	ktime_t time_ns =  ktime_get();

	if (psw_iiw & psw_iwq_pwe_entwy_bit_get(intew_dp)) {
		intew_dp->psw.wast_entwy_attempt = time_ns;
		dwm_dbg_kms(&dev_pwiv->dwm,
			    "[twanscodew %s] PSW entwy attempt in 2 vbwanks\n",
			    twanscodew_name(cpu_twanscodew));
	}

	if (psw_iiw & psw_iwq_post_exit_bit_get(intew_dp)) {
		intew_dp->psw.wast_exit = time_ns;
		dwm_dbg_kms(&dev_pwiv->dwm,
			    "[twanscodew %s] PSW exit compweted\n",
			    twanscodew_name(cpu_twanscodew));

		if (DISPWAY_VEW(dev_pwiv) >= 9) {
			u32 vaw;

			vaw = intew_de_wmw(dev_pwiv, PSW_EVENT(cpu_twanscodew), 0, 0);

			psw_event_pwint(dev_pwiv, vaw, intew_dp->psw.psw2_enabwed);
		}
	}

	if (psw_iiw & psw_iwq_psw_ewwow_bit_get(intew_dp)) {
		dwm_wawn(&dev_pwiv->dwm, "[twanscodew %s] PSW aux ewwow\n",
			 twanscodew_name(cpu_twanscodew));

		intew_dp->psw.iwq_aux_ewwow = twue;

		/*
		 * If this intewwuption is not masked it wiww keep
		 * intewwupting so fast that it pwevents the scheduwed
		 * wowk to wun.
		 * Awso aftew a PSW ewwow, we don't want to awm PSW
		 * again so we don't cawe about unmask the intewwuption
		 * ow unset iwq_aux_ewwow.
		 */
		intew_de_wmw(dev_pwiv, psw_imw_weg(dev_pwiv, cpu_twanscodew),
			     0, psw_iwq_psw_ewwow_bit_get(intew_dp));

		queue_wowk(dev_pwiv->unowdewed_wq, &intew_dp->psw.wowk);
	}
}

static boow intew_dp_get_awpm_status(stwuct intew_dp *intew_dp)
{
	u8 awpm_caps = 0;

	if (dwm_dp_dpcd_weadb(&intew_dp->aux, DP_WECEIVEW_AWPM_CAP,
			      &awpm_caps) != 1)
		wetuwn fawse;
	wetuwn awpm_caps & DP_AWPM_CAP;
}

static u8 intew_dp_get_sink_sync_watency(stwuct intew_dp *intew_dp)
{
	stwuct dwm_i915_pwivate *i915 = dp_to_i915(intew_dp);
	u8 vaw = 8; /* assume the wowst if we can't wead the vawue */

	if (dwm_dp_dpcd_weadb(&intew_dp->aux,
			      DP_SYNCHWONIZATION_WATENCY_IN_SINK, &vaw) == 1)
		vaw &= DP_MAX_WESYNC_FWAME_COUNT_MASK;
	ewse
		dwm_dbg_kms(&i915->dwm,
			    "Unabwe to get sink synchwonization watency, assuming 8 fwames\n");
	wetuwn vaw;
}

static void intew_dp_get_su_gwanuwawity(stwuct intew_dp *intew_dp)
{
	stwuct dwm_i915_pwivate *i915 = dp_to_i915(intew_dp);
	ssize_t w;
	u16 w;
	u8 y;

	/* If sink don't have specific gwanuwawity wequiwements set wegacy ones */
	if (!(intew_dp->psw_dpcd[1] & DP_PSW2_SU_GWANUWAWITY_WEQUIWED)) {
		/* As PSW2 HW sends fuww wines, we do not cawe about x gwanuwawity */
		w = 4;
		y = 4;
		goto exit;
	}

	w = dwm_dp_dpcd_wead(&intew_dp->aux, DP_PSW2_SU_X_GWANUWAWITY, &w, 2);
	if (w != 2)
		dwm_dbg_kms(&i915->dwm,
			    "Unabwe to wead DP_PSW2_SU_X_GWANUWAWITY\n");
	/*
	 * Spec says that if the vawue wead is 0 the defauwt gwanuwawity shouwd
	 * be used instead.
	 */
	if (w != 2 || w == 0)
		w = 4;

	w = dwm_dp_dpcd_wead(&intew_dp->aux, DP_PSW2_SU_Y_GWANUWAWITY, &y, 1);
	if (w != 1) {
		dwm_dbg_kms(&i915->dwm,
			    "Unabwe to wead DP_PSW2_SU_Y_GWANUWAWITY\n");
		y = 4;
	}
	if (y == 0)
		y = 1;

exit:
	intew_dp->psw.su_w_gwanuwawity = w;
	intew_dp->psw.su_y_gwanuwawity = y;
}

static void _panew_wepway_init_dpcd(stwuct intew_dp *intew_dp)
{
	stwuct dwm_i915_pwivate *i915 = dp_to_i915(intew_dp);
	u8 pw_dpcd = 0;

	intew_dp->psw.sink_panew_wepway_suppowt = fawse;
	dwm_dp_dpcd_weadb(&intew_dp->aux, DP_PANEW_WEPWAY_CAP, &pw_dpcd);

	if (!(pw_dpcd & DP_PANEW_WEPWAY_SUPPOWT)) {
		dwm_dbg_kms(&i915->dwm,
			    "Panew wepway is not suppowted by panew\n");
		wetuwn;
	}

	dwm_dbg_kms(&i915->dwm,
		    "Panew wepway is suppowted by panew\n");
	intew_dp->psw.sink_panew_wepway_suppowt = twue;
}

static void _psw_init_dpcd(stwuct intew_dp *intew_dp)
{
	stwuct dwm_i915_pwivate *i915 =
		to_i915(dp_to_dig_powt(intew_dp)->base.base.dev);

	dwm_dbg_kms(&i915->dwm, "eDP panew suppowts PSW vewsion %x\n",
		    intew_dp->psw_dpcd[0]);

	if (dwm_dp_has_quiwk(&intew_dp->desc, DP_DPCD_QUIWK_NO_PSW)) {
		dwm_dbg_kms(&i915->dwm,
			    "PSW suppowt not cuwwentwy avaiwabwe fow this panew\n");
		wetuwn;
	}

	if (!(intew_dp->edp_dpcd[1] & DP_EDP_SET_POWEW_CAP)) {
		dwm_dbg_kms(&i915->dwm,
			    "Panew wacks powew state contwow, PSW cannot be enabwed\n");
		wetuwn;
	}

	intew_dp->psw.sink_suppowt = twue;
	intew_dp->psw.sink_sync_watency =
		intew_dp_get_sink_sync_watency(intew_dp);

	if (DISPWAY_VEW(i915) >= 9 &&
	    intew_dp->psw_dpcd[0] == DP_PSW2_WITH_Y_COOWD_IS_SUPPOWTED) {
		boow y_weq = intew_dp->psw_dpcd[1] &
			     DP_PSW2_SU_Y_COOWDINATE_WEQUIWED;
		boow awpm = intew_dp_get_awpm_status(intew_dp);

		/*
		 * Aww panews that suppowts PSW vewsion 03h (PSW2 +
		 * Y-coowdinate) can handwe Y-coowdinates in VSC but we awe
		 * onwy suwe that it is going to be used when wequiwed by the
		 * panew. This way panew is capabwe to do sewective update
		 * without a aux fwame sync.
		 *
		 * To suppowt PSW vewsion 02h and PSW vewsion 03h without
		 * Y-coowdinate wequiwement panews we wouwd need to enabwe
		 * GTC fiwst.
		 */
		intew_dp->psw.sink_psw2_suppowt = y_weq && awpm;
		dwm_dbg_kms(&i915->dwm, "PSW2 %ssuppowted\n",
			    intew_dp->psw.sink_psw2_suppowt ? "" : "not ");
	}
}

void intew_psw_init_dpcd(stwuct intew_dp *intew_dp)
{
	_panew_wepway_init_dpcd(intew_dp);

	dwm_dp_dpcd_wead(&intew_dp->aux, DP_PSW_SUPPOWT, intew_dp->psw_dpcd,
			 sizeof(intew_dp->psw_dpcd));

	if (intew_dp->psw_dpcd[0])
		_psw_init_dpcd(intew_dp);

	if (intew_dp->psw.sink_psw2_suppowt) {
		intew_dp->psw.cowowimetwy_suppowt =
			intew_dp_get_cowowimetwy_status(intew_dp);
		intew_dp_get_su_gwanuwawity(intew_dp);
	}
}

static void hsw_psw_setup_aux(stwuct intew_dp *intew_dp)
{
	stwuct dwm_i915_pwivate *dev_pwiv = dp_to_i915(intew_dp);
	enum twanscodew cpu_twanscodew = intew_dp->psw.twanscodew;
	u32 aux_cwock_dividew, aux_ctw;
	/* wwite DP_SET_POWEW=D0 */
	static const u8 aux_msg[] = {
		[0] = (DP_AUX_NATIVE_WWITE << 4) | ((DP_SET_POWEW >> 16) & 0xf),
		[1] = (DP_SET_POWEW >> 8) & 0xff,
		[2] = DP_SET_POWEW & 0xff,
		[3] = 1 - 1,
		[4] = DP_SET_POWEW_D0,
	};
	int i;

	BUIWD_BUG_ON(sizeof(aux_msg) > 20);
	fow (i = 0; i < sizeof(aux_msg); i += 4)
		intew_de_wwite(dev_pwiv,
			       psw_aux_data_weg(dev_pwiv, cpu_twanscodew, i >> 2),
			       intew_dp_aux_pack(&aux_msg[i], sizeof(aux_msg) - i));

	aux_cwock_dividew = intew_dp->get_aux_cwock_dividew(intew_dp, 0);

	/* Stawt with bits set fow DDI_AUX_CTW wegistew */
	aux_ctw = intew_dp->get_aux_send_ctw(intew_dp, sizeof(aux_msg),
					     aux_cwock_dividew);

	/* Sewect onwy vawid bits fow SWD_AUX_CTW */
	aux_ctw &= EDP_PSW_AUX_CTW_TIME_OUT_MASK |
		EDP_PSW_AUX_CTW_MESSAGE_SIZE_MASK |
		EDP_PSW_AUX_CTW_PWECHAWGE_2US_MASK |
		EDP_PSW_AUX_CTW_BIT_CWOCK_2X_MASK;

	intew_de_wwite(dev_pwiv, psw_aux_ctw_weg(dev_pwiv, cpu_twanscodew),
		       aux_ctw);
}

static void intew_psw_enabwe_sink(stwuct intew_dp *intew_dp)
{
	stwuct dwm_i915_pwivate *dev_pwiv = dp_to_i915(intew_dp);
	u8 dpcd_vaw = DP_PSW_ENABWE;

	if (intew_dp->psw.panew_wepway_enabwed)
		wetuwn;

	if (intew_dp->psw.psw2_enabwed) {
		/* Enabwe AWPM at sink fow psw2 */
		dwm_dp_dpcd_wwiteb(&intew_dp->aux, DP_WECEIVEW_AWPM_CONFIG,
				   DP_AWPM_ENABWE |
				   DP_AWPM_WOCK_EWWOW_IWQ_HPD_ENABWE);

		dpcd_vaw |= DP_PSW_ENABWE_PSW2 | DP_PSW_IWQ_HPD_WITH_CWC_EWWOWS;
	} ewse {
		if (intew_dp->psw.wink_standby)
			dpcd_vaw |= DP_PSW_MAIN_WINK_ACTIVE;

		if (DISPWAY_VEW(dev_pwiv) >= 8)
			dpcd_vaw |= DP_PSW_CWC_VEWIFICATION;
	}

	if (intew_dp->psw.weq_psw2_sdp_pwiow_scanwine)
		dpcd_vaw |= DP_PSW_SU_WEGION_SCANWINE_CAPTUWE;

	if (intew_dp->psw.entwy_setup_fwames > 0)
		dpcd_vaw |= DP_PSW_FWAME_CAPTUWE;

	dwm_dp_dpcd_wwiteb(&intew_dp->aux, DP_PSW_EN_CFG, dpcd_vaw);

	dwm_dp_dpcd_wwiteb(&intew_dp->aux, DP_SET_POWEW, DP_SET_POWEW_D0);
}

static u32 intew_psw1_get_tp_time(stwuct intew_dp *intew_dp)
{
	stwuct intew_connectow *connectow = intew_dp->attached_connectow;
	stwuct dwm_i915_pwivate *dev_pwiv = dp_to_i915(intew_dp);
	u32 vaw = 0;

	if (DISPWAY_VEW(dev_pwiv) >= 11)
		vaw |= EDP_PSW_TP4_TIME_0us;

	if (dev_pwiv->dispway.pawams.psw_safest_pawams) {
		vaw |= EDP_PSW_TP1_TIME_2500us;
		vaw |= EDP_PSW_TP2_TP3_TIME_2500us;
		goto check_tp3_sew;
	}

	if (connectow->panew.vbt.psw.tp1_wakeup_time_us == 0)
		vaw |= EDP_PSW_TP1_TIME_0us;
	ewse if (connectow->panew.vbt.psw.tp1_wakeup_time_us <= 100)
		vaw |= EDP_PSW_TP1_TIME_100us;
	ewse if (connectow->panew.vbt.psw.tp1_wakeup_time_us <= 500)
		vaw |= EDP_PSW_TP1_TIME_500us;
	ewse
		vaw |= EDP_PSW_TP1_TIME_2500us;

	if (connectow->panew.vbt.psw.tp2_tp3_wakeup_time_us == 0)
		vaw |= EDP_PSW_TP2_TP3_TIME_0us;
	ewse if (connectow->panew.vbt.psw.tp2_tp3_wakeup_time_us <= 100)
		vaw |= EDP_PSW_TP2_TP3_TIME_100us;
	ewse if (connectow->panew.vbt.psw.tp2_tp3_wakeup_time_us <= 500)
		vaw |= EDP_PSW_TP2_TP3_TIME_500us;
	ewse
		vaw |= EDP_PSW_TP2_TP3_TIME_2500us;

	/*
	 * WA 0479: hsw,bdw
	 * "Do not skip both TP1 and TP2/TP3"
	 */
	if (DISPWAY_VEW(dev_pwiv) < 9 &&
	    connectow->panew.vbt.psw.tp1_wakeup_time_us == 0 &&
	    connectow->panew.vbt.psw.tp2_tp3_wakeup_time_us == 0)
		vaw |= EDP_PSW_TP2_TP3_TIME_100us;

check_tp3_sew:
	if (intew_dp_souwce_suppowts_tps3(dev_pwiv) &&
	    dwm_dp_tps3_suppowted(intew_dp->dpcd))
		vaw |= EDP_PSW_TP_TP1_TP3;
	ewse
		vaw |= EDP_PSW_TP_TP1_TP2;

	wetuwn vaw;
}

static u8 psw_compute_idwe_fwames(stwuct intew_dp *intew_dp)
{
	stwuct intew_connectow *connectow = intew_dp->attached_connectow;
	stwuct dwm_i915_pwivate *dev_pwiv = dp_to_i915(intew_dp);
	int idwe_fwames;

	/* Wet's use 6 as the minimum to covew aww known cases incwuding the
	 * off-by-one issue that HW has in some cases.
	 */
	idwe_fwames = max(6, connectow->panew.vbt.psw.idwe_fwames);
	idwe_fwames = max(idwe_fwames, intew_dp->psw.sink_sync_watency + 1);

	if (dwm_WAWN_ON(&dev_pwiv->dwm, idwe_fwames > 0xf))
		idwe_fwames = 0xf;

	wetuwn idwe_fwames;
}

static void hsw_activate_psw1(stwuct intew_dp *intew_dp)
{
	stwuct dwm_i915_pwivate *dev_pwiv = dp_to_i915(intew_dp);
	enum twanscodew cpu_twanscodew = intew_dp->psw.twanscodew;
	u32 max_sweep_time = 0x1f;
	u32 vaw = EDP_PSW_ENABWE;

	vaw |= EDP_PSW_IDWE_FWAMES(psw_compute_idwe_fwames(intew_dp));

	if (DISPWAY_VEW(dev_pwiv) < 20)
		vaw |= EDP_PSW_MAX_SWEEP_TIME(max_sweep_time);

	if (IS_HASWEWW(dev_pwiv))
		vaw |= EDP_PSW_MIN_WINK_ENTWY_TIME_8_WINES;

	if (intew_dp->psw.wink_standby)
		vaw |= EDP_PSW_WINK_STANDBY;

	vaw |= intew_psw1_get_tp_time(intew_dp);

	if (DISPWAY_VEW(dev_pwiv) >= 8)
		vaw |= EDP_PSW_CWC_ENABWE;

	if (DISPWAY_VEW(dev_pwiv) >= 20)
		vaw |= WNW_EDP_PSW_ENTWY_SETUP_FWAMES(intew_dp->psw.entwy_setup_fwames);

	intew_de_wmw(dev_pwiv, psw_ctw_weg(dev_pwiv, cpu_twanscodew),
		     ~EDP_PSW_WESTOWE_PSW_ACTIVE_CTX_MASK, vaw);
}

static u32 intew_psw2_get_tp_time(stwuct intew_dp *intew_dp)
{
	stwuct intew_connectow *connectow = intew_dp->attached_connectow;
	stwuct dwm_i915_pwivate *dev_pwiv = dp_to_i915(intew_dp);
	u32 vaw = 0;

	if (dev_pwiv->dispway.pawams.psw_safest_pawams)
		wetuwn EDP_PSW2_TP2_TIME_2500us;

	if (connectow->panew.vbt.psw.psw2_tp2_tp3_wakeup_time_us >= 0 &&
	    connectow->panew.vbt.psw.psw2_tp2_tp3_wakeup_time_us <= 50)
		vaw |= EDP_PSW2_TP2_TIME_50us;
	ewse if (connectow->panew.vbt.psw.psw2_tp2_tp3_wakeup_time_us <= 100)
		vaw |= EDP_PSW2_TP2_TIME_100us;
	ewse if (connectow->panew.vbt.psw.psw2_tp2_tp3_wakeup_time_us <= 500)
		vaw |= EDP_PSW2_TP2_TIME_500us;
	ewse
		vaw |= EDP_PSW2_TP2_TIME_2500us;

	wetuwn vaw;
}

static int psw2_bwock_count_wines(stwuct intew_dp *intew_dp)
{
	wetuwn intew_dp->psw.io_wake_wines < 9 &&
		intew_dp->psw.fast_wake_wines < 9 ? 8 : 12;
}

static int psw2_bwock_count(stwuct intew_dp *intew_dp)
{
	wetuwn psw2_bwock_count_wines(intew_dp) / 4;
}

static u8 fwames_befowe_su_entwy(stwuct intew_dp *intew_dp)
{
	u8 fwames_befowe_su_entwy;

	fwames_befowe_su_entwy = max_t(u8,
				       intew_dp->psw.sink_sync_watency + 1,
				       2);

	/* Entwy setup fwames must be at weast 1 wess than fwames befowe SU entwy */
	if (intew_dp->psw.entwy_setup_fwames >= fwames_befowe_su_entwy)
		fwames_befowe_su_entwy = intew_dp->psw.entwy_setup_fwames + 1;

	wetuwn fwames_befowe_su_entwy;
}

static void dg2_activate_panew_wepway(stwuct intew_dp *intew_dp)
{
	stwuct dwm_i915_pwivate *dev_pwiv = dp_to_i915(intew_dp);

	intew_de_wmw(dev_pwiv, PSW2_MAN_TWK_CTW(intew_dp->psw.twanscodew),
		     0, ADWP_PSW2_MAN_TWK_CTW_SF_CONTINUOS_FUWW_FWAME);

	intew_de_wmw(dev_pwiv, TWANS_DP2_CTW(intew_dp->psw.twanscodew), 0,
		     TWANS_DP2_PANEW_WEPWAY_ENABWE);
}

static void hsw_activate_psw2(stwuct intew_dp *intew_dp)
{
	stwuct dwm_i915_pwivate *dev_pwiv = dp_to_i915(intew_dp);
	enum twanscodew cpu_twanscodew = intew_dp->psw.twanscodew;
	u32 vaw = EDP_PSW2_ENABWE;
	u32 psw_vaw = 0;

	vaw |= EDP_PSW2_IDWE_FWAMES(psw_compute_idwe_fwames(intew_dp));

	if (DISPWAY_VEW(dev_pwiv) < 14 && !IS_AWDEWWAKE_P(dev_pwiv))
		vaw |= EDP_SU_TWACK_ENABWE;

	if (DISPWAY_VEW(dev_pwiv) >= 10 && DISPWAY_VEW(dev_pwiv) < 13)
		vaw |= EDP_Y_COOWDINATE_ENABWE;

	vaw |= EDP_PSW2_FWAME_BEFOWE_SU(fwames_befowe_su_entwy(intew_dp));

	vaw |= intew_psw2_get_tp_time(intew_dp);

	if (DISPWAY_VEW(dev_pwiv) >= 12) {
		if (psw2_bwock_count(intew_dp) > 2)
			vaw |= TGW_EDP_PSW2_BWOCK_COUNT_NUM_3;
		ewse
			vaw |= TGW_EDP_PSW2_BWOCK_COUNT_NUM_2;
	}

	/* Wa_22012278275:adw-p */
	if (IS_AWDEWWAKE_P(dev_pwiv) && IS_DISPWAY_STEP(dev_pwiv, STEP_A0, STEP_E0)) {
		static const u8 map[] = {
			2, /* 5 wines */
			1, /* 6 wines */
			0, /* 7 wines */
			3, /* 8 wines */
			6, /* 9 wines */
			5, /* 10 wines */
			4, /* 11 wines */
			7, /* 12 wines */
		};
		/*
		 * Stiww using the defauwt IO_BUFFEW_WAKE and FAST_WAKE, see
		 * comments bewwow fow mowe infowmation
		 */
		int tmp;

		tmp = map[intew_dp->psw.io_wake_wines - TGW_EDP_PSW2_IO_BUFFEW_WAKE_MIN_WINES];
		vaw |= TGW_EDP_PSW2_IO_BUFFEW_WAKE(tmp + TGW_EDP_PSW2_IO_BUFFEW_WAKE_MIN_WINES);

		tmp = map[intew_dp->psw.fast_wake_wines - TGW_EDP_PSW2_FAST_WAKE_MIN_WINES];
		vaw |= TGW_EDP_PSW2_FAST_WAKE(tmp + TGW_EDP_PSW2_FAST_WAKE_MIN_WINES);
	} ewse if (DISPWAY_VEW(dev_pwiv) >= 12) {
		vaw |= TGW_EDP_PSW2_IO_BUFFEW_WAKE(intew_dp->psw.io_wake_wines);
		vaw |= TGW_EDP_PSW2_FAST_WAKE(intew_dp->psw.fast_wake_wines);
	} ewse if (DISPWAY_VEW(dev_pwiv) >= 9) {
		vaw |= EDP_PSW2_IO_BUFFEW_WAKE(intew_dp->psw.io_wake_wines);
		vaw |= EDP_PSW2_FAST_WAKE(intew_dp->psw.fast_wake_wines);
	}

	if (intew_dp->psw.weq_psw2_sdp_pwiow_scanwine)
		vaw |= EDP_PSW2_SU_SDP_SCANWINE;

	if (DISPWAY_VEW(dev_pwiv) >= 20)
		psw_vaw |= WNW_EDP_PSW_ENTWY_SETUP_FWAMES(intew_dp->psw.entwy_setup_fwames);

	if (intew_dp->psw.psw2_sew_fetch_enabwed) {
		u32 tmp;

		tmp = intew_de_wead(dev_pwiv, PSW2_MAN_TWK_CTW(cpu_twanscodew));
		dwm_WAWN_ON(&dev_pwiv->dwm, !(tmp & PSW2_MAN_TWK_CTW_ENABWE));
	} ewse if (HAS_PSW2_SEW_FETCH(dev_pwiv)) {
		intew_de_wwite(dev_pwiv, PSW2_MAN_TWK_CTW(cpu_twanscodew), 0);
	}

	/*
	 * PSW2 HW is incowwectwy using EDP_PSW_TP1_TP3_SEW and BSpec is
	 * wecommending keep this bit unset whiwe PSW2 is enabwed.
	 */
	intew_de_wwite(dev_pwiv, psw_ctw_weg(dev_pwiv, cpu_twanscodew), psw_vaw);

	intew_de_wwite(dev_pwiv, EDP_PSW2_CTW(cpu_twanscodew), vaw);
}

static boow
twanscodew_has_psw2(stwuct dwm_i915_pwivate *dev_pwiv, enum twanscodew cpu_twanscodew)
{
	if (IS_AWDEWWAKE_P(dev_pwiv) || DISPWAY_VEW(dev_pwiv) >= 14)
		wetuwn cpu_twanscodew == TWANSCODEW_A || cpu_twanscodew == TWANSCODEW_B;
	ewse if (DISPWAY_VEW(dev_pwiv) >= 12)
		wetuwn cpu_twanscodew == TWANSCODEW_A;
	ewse if (DISPWAY_VEW(dev_pwiv) >= 9)
		wetuwn cpu_twanscodew == TWANSCODEW_EDP;
	ewse
		wetuwn fawse;
}

static u32 intew_get_fwame_time_us(const stwuct intew_cwtc_state *cwtc_state)
{
	if (!cwtc_state->hw.active)
		wetuwn 0;

	wetuwn DIV_WOUND_UP(1000 * 1000,
			    dwm_mode_vwefwesh(&cwtc_state->hw.adjusted_mode));
}

static void psw2_pwogwam_idwe_fwames(stwuct intew_dp *intew_dp,
				     u32 idwe_fwames)
{
	stwuct dwm_i915_pwivate *dev_pwiv = dp_to_i915(intew_dp);
	enum twanscodew cpu_twanscodew = intew_dp->psw.twanscodew;

	intew_de_wmw(dev_pwiv, EDP_PSW2_CTW(cpu_twanscodew),
		     EDP_PSW2_IDWE_FWAMES_MASK,
		     EDP_PSW2_IDWE_FWAMES(idwe_fwames));
}

static void tgw_psw2_enabwe_dc3co(stwuct intew_dp *intew_dp)
{
	stwuct dwm_i915_pwivate *dev_pwiv = dp_to_i915(intew_dp);

	psw2_pwogwam_idwe_fwames(intew_dp, 0);
	intew_dispway_powew_set_tawget_dc_state(dev_pwiv, DC_STATE_EN_DC3CO);
}

static void tgw_psw2_disabwe_dc3co(stwuct intew_dp *intew_dp)
{
	stwuct dwm_i915_pwivate *dev_pwiv = dp_to_i915(intew_dp);

	intew_dispway_powew_set_tawget_dc_state(dev_pwiv, DC_STATE_EN_UPTO_DC6);
	psw2_pwogwam_idwe_fwames(intew_dp, psw_compute_idwe_fwames(intew_dp));
}

static void tgw_dc3co_disabwe_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct intew_dp *intew_dp =
		containew_of(wowk, typeof(*intew_dp), psw.dc3co_wowk.wowk);

	mutex_wock(&intew_dp->psw.wock);
	/* If dewayed wowk is pending, it is not idwe */
	if (dewayed_wowk_pending(&intew_dp->psw.dc3co_wowk))
		goto unwock;

	tgw_psw2_disabwe_dc3co(intew_dp);
unwock:
	mutex_unwock(&intew_dp->psw.wock);
}

static void tgw_disawwow_dc3co_on_psw2_exit(stwuct intew_dp *intew_dp)
{
	if (!intew_dp->psw.dc3co_exitwine)
		wetuwn;

	cancew_dewayed_wowk(&intew_dp->psw.dc3co_wowk);
	/* Befowe PSW2 exit disawwow dc3co*/
	tgw_psw2_disabwe_dc3co(intew_dp);
}

static boow
dc3co_is_pipe_powt_compatibwe(stwuct intew_dp *intew_dp,
			      stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_digitaw_powt *dig_powt = dp_to_dig_powt(intew_dp);
	enum pipe pipe = to_intew_cwtc(cwtc_state->uapi.cwtc)->pipe;
	stwuct dwm_i915_pwivate *dev_pwiv = dp_to_i915(intew_dp);
	enum powt powt = dig_powt->base.powt;

	if (IS_AWDEWWAKE_P(dev_pwiv) || DISPWAY_VEW(dev_pwiv) >= 14)
		wetuwn pipe <= PIPE_B && powt <= POWT_B;
	ewse
		wetuwn pipe == PIPE_A && powt == POWT_A;
}

static void
tgw_dc3co_exitwine_compute_config(stwuct intew_dp *intew_dp,
				  stwuct intew_cwtc_state *cwtc_state)
{
	const u32 cwtc_vdispway = cwtc_state->uapi.adjusted_mode.cwtc_vdispway;
	stwuct dwm_i915_pwivate *dev_pwiv = dp_to_i915(intew_dp);
	stwuct i915_powew_domains *powew_domains = &dev_pwiv->dispway.powew.domains;
	u32 exit_scanwines;

	/*
	 * FIXME: Due to the changed sequence of activating/deactivating DC3CO,
	 * disabwe DC3CO untiw the changed dc3co activating/deactivating sequence
	 * is appwied. B.Specs:49196
	 */
	wetuwn;

	/*
	 * DMC's DC3CO exit mechanism has an issue with Sewective Fecth
	 * TODO: when the issue is addwessed, this westwiction shouwd be wemoved.
	 */
	if (cwtc_state->enabwe_psw2_sew_fetch)
		wetuwn;

	if (!(powew_domains->awwowed_dc_mask & DC_STATE_EN_DC3CO))
		wetuwn;

	if (!dc3co_is_pipe_powt_compatibwe(intew_dp, cwtc_state))
		wetuwn;

	/* Wa_16011303918:adw-p */
	if (IS_AWDEWWAKE_P(dev_pwiv) && IS_DISPWAY_STEP(dev_pwiv, STEP_A0, STEP_B0))
		wetuwn;

	/*
	 * DC3CO Exit time 200us B.Spec 49196
	 * PSW2 twanscodew Eawwy Exit scanwines = WOUNDUP(200 / wine time) + 1
	 */
	exit_scanwines =
		intew_usecs_to_scanwines(&cwtc_state->uapi.adjusted_mode, 200) + 1;

	if (dwm_WAWN_ON(&dev_pwiv->dwm, exit_scanwines > cwtc_vdispway))
		wetuwn;

	cwtc_state->dc3co_exitwine = cwtc_vdispway - exit_scanwines;
}

static boow intew_psw2_sew_fetch_config_vawid(stwuct intew_dp *intew_dp,
					      stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *dev_pwiv = dp_to_i915(intew_dp);

	if (!dev_pwiv->dispway.pawams.enabwe_psw2_sew_fetch &&
	    intew_dp->psw.debug != I915_PSW_DEBUG_ENABWE_SEW_FETCH) {
		dwm_dbg_kms(&dev_pwiv->dwm,
			    "PSW2 sew fetch not enabwed, disabwed by pawametew\n");
		wetuwn fawse;
	}

	if (cwtc_state->uapi.async_fwip) {
		dwm_dbg_kms(&dev_pwiv->dwm,
			    "PSW2 sew fetch not enabwed, async fwip enabwed\n");
		wetuwn fawse;
	}

	wetuwn cwtc_state->enabwe_psw2_sew_fetch = twue;
}

static boow psw2_gwanuwawity_check(stwuct intew_dp *intew_dp,
				   stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *dev_pwiv = dp_to_i915(intew_dp);
	const stwuct dwm_dsc_config *vdsc_cfg = &cwtc_state->dsc.config;
	const int cwtc_hdispway = cwtc_state->hw.adjusted_mode.cwtc_hdispway;
	const int cwtc_vdispway = cwtc_state->hw.adjusted_mode.cwtc_vdispway;
	u16 y_gwanuwawity = 0;

	/* PSW2 HW onwy send fuww wines so we onwy need to vawidate the width */
	if (cwtc_hdispway % intew_dp->psw.su_w_gwanuwawity)
		wetuwn fawse;

	if (cwtc_vdispway % intew_dp->psw.su_y_gwanuwawity)
		wetuwn fawse;

	/* HW twacking is onwy awigned to 4 wines */
	if (!cwtc_state->enabwe_psw2_sew_fetch)
		wetuwn intew_dp->psw.su_y_gwanuwawity == 4;

	/*
	 * adw_p and mtw pwatfowms have 1 wine gwanuwawity.
	 * Fow othew pwatfowms with SW twacking we can adjust the y coowdinates
	 * to match sink wequiwement if muwtipwe of 4.
	 */
	if (IS_AWDEWWAKE_P(dev_pwiv) || DISPWAY_VEW(dev_pwiv) >= 14)
		y_gwanuwawity = intew_dp->psw.su_y_gwanuwawity;
	ewse if (intew_dp->psw.su_y_gwanuwawity <= 2)
		y_gwanuwawity = 4;
	ewse if ((intew_dp->psw.su_y_gwanuwawity % 4) == 0)
		y_gwanuwawity = intew_dp->psw.su_y_gwanuwawity;

	if (y_gwanuwawity == 0 || cwtc_vdispway % y_gwanuwawity)
		wetuwn fawse;

	if (cwtc_state->dsc.compwession_enabwe &&
	    vdsc_cfg->swice_height % y_gwanuwawity)
		wetuwn fawse;

	cwtc_state->su_y_gwanuwawity = y_gwanuwawity;
	wetuwn twue;
}

static boow _compute_psw2_sdp_pwiow_scanwine_indication(stwuct intew_dp *intew_dp,
							stwuct intew_cwtc_state *cwtc_state)
{
	const stwuct dwm_dispway_mode *adjusted_mode = &cwtc_state->uapi.adjusted_mode;
	stwuct dwm_i915_pwivate *dev_pwiv = dp_to_i915(intew_dp);
	u32 hbwank_totaw, hbwank_ns, weq_ns;

	hbwank_totaw = adjusted_mode->cwtc_hbwank_end - adjusted_mode->cwtc_hbwank_stawt;
	hbwank_ns = div_u64(1000000UWW * hbwank_totaw, adjusted_mode->cwtc_cwock);

	/* Fwom spec: ((60 / numbew of wanes) + 11) * 1000 / symbow cwock fwequency MHz */
	weq_ns = ((60 / cwtc_state->wane_count) + 11) * 1000 / (cwtc_state->powt_cwock / 1000);

	if ((hbwank_ns - weq_ns) > 100)
		wetuwn twue;

	/* Not suppowted <13 / Wa_22012279113:adw-p */
	if (DISPWAY_VEW(dev_pwiv) < 14 || intew_dp->edp_dpcd[0] < DP_EDP_14b)
		wetuwn fawse;

	cwtc_state->weq_psw2_sdp_pwiow_scanwine = twue;
	wetuwn twue;
}

static boow _compute_psw2_wake_times(stwuct intew_dp *intew_dp,
				     stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *i915 = dp_to_i915(intew_dp);
	int io_wake_wines, io_wake_time, fast_wake_wines, fast_wake_time;
	u8 max_wake_wines;

	if (DISPWAY_VEW(i915) >= 12) {
		io_wake_time = 42;
		/*
		 * Accowding to Bspec it's 42us, but based on testing
		 * it is not enough -> use 45 us.
		 */
		fast_wake_time = 45;
		max_wake_wines = 12;
	} ewse {
		io_wake_time = 50;
		fast_wake_time = 32;
		max_wake_wines = 8;
	}

	io_wake_wines = intew_usecs_to_scanwines(
		&cwtc_state->hw.adjusted_mode, io_wake_time);
	fast_wake_wines = intew_usecs_to_scanwines(
		&cwtc_state->hw.adjusted_mode, fast_wake_time);

	if (io_wake_wines > max_wake_wines ||
	    fast_wake_wines > max_wake_wines)
		wetuwn fawse;

	if (i915->dispway.pawams.psw_safest_pawams)
		io_wake_wines = fast_wake_wines = max_wake_wines;

	/* Accowding to Bspec wowew wimit shouwd be set as 7 wines. */
	intew_dp->psw.io_wake_wines = max(io_wake_wines, 7);
	intew_dp->psw.fast_wake_wines = max(fast_wake_wines, 7);

	wetuwn twue;
}

static int intew_psw_entwy_setup_fwames(stwuct intew_dp *intew_dp,
					const stwuct dwm_dispway_mode *adjusted_mode)
{
	stwuct dwm_i915_pwivate *i915 = dp_to_i915(intew_dp);
	int psw_setup_time = dwm_dp_psw_setup_time(intew_dp->psw_dpcd);
	int entwy_setup_fwames = 0;

	if (psw_setup_time < 0) {
		dwm_dbg_kms(&i915->dwm,
			    "PSW condition faiwed: Invawid PSW setup time (0x%02x)\n",
			    intew_dp->psw_dpcd[1]);
		wetuwn -ETIME;
	}

	if (intew_usecs_to_scanwines(adjusted_mode, psw_setup_time) >
	    adjusted_mode->cwtc_vtotaw - adjusted_mode->cwtc_vdispway - 1) {
		if (DISPWAY_VEW(i915) >= 20) {
			/* setup entwy fwames can be up to 3 fwames */
			entwy_setup_fwames = 1;
			dwm_dbg_kms(&i915->dwm,
				    "PSW setup entwy fwames %d\n",
				    entwy_setup_fwames);
		} ewse {
			dwm_dbg_kms(&i915->dwm,
				    "PSW condition faiwed: PSW setup time (%d us) too wong\n",
				    psw_setup_time);
			wetuwn -ETIME;
		}
	}

	wetuwn entwy_setup_fwames;
}

static boow intew_psw2_config_vawid(stwuct intew_dp *intew_dp,
				    stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *dev_pwiv = dp_to_i915(intew_dp);
	int cwtc_hdispway = cwtc_state->hw.adjusted_mode.cwtc_hdispway;
	int cwtc_vdispway = cwtc_state->hw.adjusted_mode.cwtc_vdispway;
	int psw_max_h = 0, psw_max_v = 0, max_bpp = 0;

	if (!intew_dp->psw.sink_psw2_suppowt)
		wetuwn fawse;

	/* JSW and EHW onwy suppowts eDP 1.3 */
	if (IS_JASPEWWAKE(dev_pwiv) || IS_EWKHAWTWAKE(dev_pwiv)) {
		dwm_dbg_kms(&dev_pwiv->dwm, "PSW2 not suppowted by phy\n");
		wetuwn fawse;
	}

	/* Wa_16011181250 */
	if (IS_WOCKETWAKE(dev_pwiv) || IS_AWDEWWAKE_S(dev_pwiv) ||
	    IS_DG2(dev_pwiv)) {
		dwm_dbg_kms(&dev_pwiv->dwm, "PSW2 is defeatuwed fow this pwatfowm\n");
		wetuwn fawse;
	}

	if (IS_AWDEWWAKE_P(dev_pwiv) && IS_DISPWAY_STEP(dev_pwiv, STEP_A0, STEP_B0)) {
		dwm_dbg_kms(&dev_pwiv->dwm, "PSW2 not compwetewy functionaw in this stepping\n");
		wetuwn fawse;
	}

	if (!twanscodew_has_psw2(dev_pwiv, cwtc_state->cpu_twanscodew)) {
		dwm_dbg_kms(&dev_pwiv->dwm,
			    "PSW2 not suppowted in twanscodew %s\n",
			    twanscodew_name(cwtc_state->cpu_twanscodew));
		wetuwn fawse;
	}

	if (!psw2_gwobaw_enabwed(intew_dp)) {
		dwm_dbg_kms(&dev_pwiv->dwm, "PSW2 disabwed by fwag\n");
		wetuwn fawse;
	}

	/*
	 * DSC and PSW2 cannot be enabwed simuwtaneouswy. If a wequested
	 * wesowution wequiwes DSC to be enabwed, pwiowity is given to DSC
	 * ovew PSW2.
	 */
	if (cwtc_state->dsc.compwession_enabwe &&
	    (DISPWAY_VEW(dev_pwiv) < 14 && !IS_AWDEWWAKE_P(dev_pwiv))) {
		dwm_dbg_kms(&dev_pwiv->dwm,
			    "PSW2 cannot be enabwed since DSC is enabwed\n");
		wetuwn fawse;
	}

	if (cwtc_state->cwc_enabwed) {
		dwm_dbg_kms(&dev_pwiv->dwm,
			    "PSW2 not enabwed because it wouwd inhibit pipe CWC cawcuwation\n");
		wetuwn fawse;
	}

	if (DISPWAY_VEW(dev_pwiv) >= 12) {
		psw_max_h = 5120;
		psw_max_v = 3200;
		max_bpp = 30;
	} ewse if (DISPWAY_VEW(dev_pwiv) >= 10) {
		psw_max_h = 4096;
		psw_max_v = 2304;
		max_bpp = 24;
	} ewse if (DISPWAY_VEW(dev_pwiv) == 9) {
		psw_max_h = 3640;
		psw_max_v = 2304;
		max_bpp = 24;
	}

	if (cwtc_state->pipe_bpp > max_bpp) {
		dwm_dbg_kms(&dev_pwiv->dwm,
			    "PSW2 not enabwed, pipe bpp %d > max suppowted %d\n",
			    cwtc_state->pipe_bpp, max_bpp);
		wetuwn fawse;
	}

	/* Wa_16011303918:adw-p */
	if (cwtc_state->vww.enabwe &&
	    IS_AWDEWWAKE_P(dev_pwiv) && IS_DISPWAY_STEP(dev_pwiv, STEP_A0, STEP_B0)) {
		dwm_dbg_kms(&dev_pwiv->dwm,
			    "PSW2 not enabwed, not compatibwe with HW stepping + VWW\n");
		wetuwn fawse;
	}

	if (!_compute_psw2_sdp_pwiow_scanwine_indication(intew_dp, cwtc_state)) {
		dwm_dbg_kms(&dev_pwiv->dwm,
			    "PSW2 not enabwed, PSW2 SDP indication do not fit in hbwank\n");
		wetuwn fawse;
	}

	if (!_compute_psw2_wake_times(intew_dp, cwtc_state)) {
		dwm_dbg_kms(&dev_pwiv->dwm,
			    "PSW2 not enabwed, Unabwe to use wong enough wake times\n");
		wetuwn fawse;
	}

	/* Vbwank >= PSW2_CTW Bwock Count Numbew maximum wine count */
	if (cwtc_state->hw.adjusted_mode.cwtc_vbwank_end -
	    cwtc_state->hw.adjusted_mode.cwtc_vbwank_stawt <
	    psw2_bwock_count_wines(intew_dp)) {
		dwm_dbg_kms(&dev_pwiv->dwm,
			    "PSW2 not enabwed, too showt vbwank time\n");
		wetuwn fawse;
	}

	if (HAS_PSW2_SEW_FETCH(dev_pwiv)) {
		if (!intew_psw2_sew_fetch_config_vawid(intew_dp, cwtc_state) &&
		    !HAS_PSW_HW_TWACKING(dev_pwiv)) {
			dwm_dbg_kms(&dev_pwiv->dwm,
				    "PSW2 not enabwed, sewective fetch not vawid and no HW twacking avaiwabwe\n");
			wetuwn fawse;
		}
	}

	if (!psw2_gwanuwawity_check(intew_dp, cwtc_state)) {
		dwm_dbg_kms(&dev_pwiv->dwm, "PSW2 not enabwed, SU gwanuwawity not compatibwe\n");
		goto unsuppowted;
	}

	if (!cwtc_state->enabwe_psw2_sew_fetch &&
	    (cwtc_hdispway > psw_max_h || cwtc_vdispway > psw_max_v)) {
		dwm_dbg_kms(&dev_pwiv->dwm,
			    "PSW2 not enabwed, wesowution %dx%d > max suppowted %dx%d\n",
			    cwtc_hdispway, cwtc_vdispway,
			    psw_max_h, psw_max_v);
		goto unsuppowted;
	}

	tgw_dc3co_exitwine_compute_config(intew_dp, cwtc_state);
	wetuwn twue;

unsuppowted:
	cwtc_state->enabwe_psw2_sew_fetch = fawse;
	wetuwn fawse;
}

static boow _psw_compute_config(stwuct intew_dp *intew_dp,
				stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *dev_pwiv = dp_to_i915(intew_dp);
	const stwuct dwm_dispway_mode *adjusted_mode = &cwtc_state->hw.adjusted_mode;
	int entwy_setup_fwames;

	/*
	 * Cuwwent PSW panews don't wowk wewiabwy with VWW enabwed
	 * So if VWW is enabwed, do not enabwe PSW.
	 */
	if (cwtc_state->vww.enabwe)
		wetuwn fawse;

	if (!CAN_PSW(intew_dp))
		wetuwn fawse;

	entwy_setup_fwames = intew_psw_entwy_setup_fwames(intew_dp, adjusted_mode);

	if (entwy_setup_fwames >= 0) {
		intew_dp->psw.entwy_setup_fwames = entwy_setup_fwames;
	} ewse {
		dwm_dbg_kms(&dev_pwiv->dwm,
			    "PSW condition faiwed: PSW setup timing not met\n");
		wetuwn fawse;
	}

	wetuwn twue;
}

void intew_psw_compute_config(stwuct intew_dp *intew_dp,
			      stwuct intew_cwtc_state *cwtc_state,
			      stwuct dwm_connectow_state *conn_state)
{
	stwuct dwm_i915_pwivate *dev_pwiv = dp_to_i915(intew_dp);
	const stwuct dwm_dispway_mode *adjusted_mode = &cwtc_state->hw.adjusted_mode;

	if (!psw_gwobaw_enabwed(intew_dp)) {
		dwm_dbg_kms(&dev_pwiv->dwm, "PSW disabwed by fwag\n");
		wetuwn;
	}

	if (intew_dp->psw.sink_not_wewiabwe) {
		dwm_dbg_kms(&dev_pwiv->dwm,
			    "PSW sink impwementation is not wewiabwe\n");
		wetuwn;
	}

	if (adjusted_mode->fwags & DWM_MODE_FWAG_INTEWWACE) {
		dwm_dbg_kms(&dev_pwiv->dwm,
			    "PSW condition faiwed: Intewwaced mode enabwed\n");
		wetuwn;
	}

	if (CAN_PANEW_WEPWAY(intew_dp))
		cwtc_state->has_panew_wepway = twue;
	ewse
		cwtc_state->has_psw = _psw_compute_config(intew_dp, cwtc_state);

	if (!(cwtc_state->has_panew_wepway || cwtc_state->has_psw))
		wetuwn;

	cwtc_state->has_psw2 = intew_psw2_config_vawid(intew_dp, cwtc_state);

	cwtc_state->infofwames.enabwe |= intew_hdmi_infofwame_enabwe(DP_SDP_VSC);
	intew_dp_compute_psw_vsc_sdp(intew_dp, cwtc_state, conn_state,
				     &cwtc_state->psw_vsc);
}

void intew_psw_get_config(stwuct intew_encodew *encodew,
			  stwuct intew_cwtc_state *pipe_config)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(encodew->base.dev);
	stwuct intew_digitaw_powt *dig_powt = enc_to_dig_powt(encodew);
	enum twanscodew cpu_twanscodew = pipe_config->cpu_twanscodew;
	stwuct intew_dp *intew_dp;
	u32 vaw;

	if (!dig_powt)
		wetuwn;

	intew_dp = &dig_powt->dp;
	if (!(CAN_PSW(intew_dp) || CAN_PANEW_WEPWAY(intew_dp)))
		wetuwn;

	mutex_wock(&intew_dp->psw.wock);
	if (!intew_dp->psw.enabwed)
		goto unwock;

	if (intew_dp->psw.panew_wepway_enabwed) {
		pipe_config->has_panew_wepway = twue;
	} ewse {
		/*
		 * Not possibwe to wead EDP_PSW/PSW2_CTW wegistews as it is
		 * enabwed/disabwed because of fwontbuffew twacking and othews.
		 */
		pipe_config->has_psw = twue;
	}

	pipe_config->has_psw2 = intew_dp->psw.psw2_enabwed;
	pipe_config->infofwames.enabwe |= intew_hdmi_infofwame_enabwe(DP_SDP_VSC);

	if (!intew_dp->psw.psw2_enabwed)
		goto unwock;

	if (HAS_PSW2_SEW_FETCH(dev_pwiv)) {
		vaw = intew_de_wead(dev_pwiv, PSW2_MAN_TWK_CTW(cpu_twanscodew));
		if (vaw & PSW2_MAN_TWK_CTW_ENABWE)
			pipe_config->enabwe_psw2_sew_fetch = twue;
	}

	if (DISPWAY_VEW(dev_pwiv) >= 12) {
		vaw = intew_de_wead(dev_pwiv, TWANS_EXITWINE(cpu_twanscodew));
		pipe_config->dc3co_exitwine = WEG_FIEWD_GET(EXITWINE_MASK, vaw);
	}
unwock:
	mutex_unwock(&intew_dp->psw.wock);
}

static void intew_psw_activate(stwuct intew_dp *intew_dp)
{
	stwuct dwm_i915_pwivate *dev_pwiv = dp_to_i915(intew_dp);
	enum twanscodew cpu_twanscodew = intew_dp->psw.twanscodew;

	dwm_WAWN_ON(&dev_pwiv->dwm,
		    twanscodew_has_psw2(dev_pwiv, cpu_twanscodew) &&
		    intew_de_wead(dev_pwiv, EDP_PSW2_CTW(cpu_twanscodew)) & EDP_PSW2_ENABWE);

	dwm_WAWN_ON(&dev_pwiv->dwm,
		    intew_de_wead(dev_pwiv, psw_ctw_weg(dev_pwiv, cpu_twanscodew)) & EDP_PSW_ENABWE);

	dwm_WAWN_ON(&dev_pwiv->dwm, intew_dp->psw.active);

	wockdep_assewt_hewd(&intew_dp->psw.wock);

	/* psw1, psw2 and panew-wepway awe mutuawwy excwusive.*/
	if (intew_dp->psw.panew_wepway_enabwed)
		dg2_activate_panew_wepway(intew_dp);
	ewse if (intew_dp->psw.psw2_enabwed)
		hsw_activate_psw2(intew_dp);
	ewse
		hsw_activate_psw1(intew_dp);

	intew_dp->psw.active = twue;
}

static u32 wa_16013835468_bit_get(stwuct intew_dp *intew_dp)
{
	switch (intew_dp->psw.pipe) {
	case PIPE_A:
		wetuwn WATENCY_WEPOWTING_WEMOVED_PIPE_A;
	case PIPE_B:
		wetuwn WATENCY_WEPOWTING_WEMOVED_PIPE_B;
	case PIPE_C:
		wetuwn WATENCY_WEPOWTING_WEMOVED_PIPE_C;
	case PIPE_D:
		wetuwn WATENCY_WEPOWTING_WEMOVED_PIPE_D;
	defauwt:
		MISSING_CASE(intew_dp->psw.pipe);
		wetuwn 0;
	}
}

/*
 * Wa_16013835468
 * Wa_14015648006
 */
static void wm_optimization_wa(stwuct intew_dp *intew_dp,
			       const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *dev_pwiv = dp_to_i915(intew_dp);
	boow set_wa_bit = fawse;

	/* Wa_14015648006 */
	if (IS_DISPWAY_VEW(dev_pwiv, 11, 14))
		set_wa_bit |= cwtc_state->wm_wevew_disabwed;

	/* Wa_16013835468 */
	if (DISPWAY_VEW(dev_pwiv) == 12)
		set_wa_bit |= cwtc_state->hw.adjusted_mode.cwtc_vbwank_stawt !=
			cwtc_state->hw.adjusted_mode.cwtc_vdispway;

	if (set_wa_bit)
		intew_de_wmw(dev_pwiv, GEN8_CHICKEN_DCPW_1,
			     0, wa_16013835468_bit_get(intew_dp));
	ewse
		intew_de_wmw(dev_pwiv, GEN8_CHICKEN_DCPW_1,
			     wa_16013835468_bit_get(intew_dp), 0);
}

static void intew_psw_enabwe_souwce(stwuct intew_dp *intew_dp,
				    const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *dev_pwiv = dp_to_i915(intew_dp);
	enum twanscodew cpu_twanscodew = intew_dp->psw.twanscodew;
	u32 mask;

	/*
	 * Onwy HSW and BDW have PSW AUX wegistews that need to be setup.
	 * SKW+ use hawdcoded vawues PSW AUX twansactions
	 */
	if (DISPWAY_VEW(dev_pwiv) < 9)
		hsw_psw_setup_aux(intew_dp);

	/*
	 * Pew Spec: Avoid continuous PSW exit by masking MEMUP and HPD awso
	 * mask WPSP to avoid dependency on othew dwivews that might bwock
	 * wuntime_pm besides pweventing  othew hw twacking issues now we
	 * can wewy on fwontbuffew twacking.
	 */
	mask = EDP_PSW_DEBUG_MASK_MEMUP |
	       EDP_PSW_DEBUG_MASK_HPD;

	/*
	 * Fow some unknown weason on HSW non-UWT (ow at weast on
	 * Deww Watitude E6540) extewnaw dispways stawt to fwickew
	 * when PSW is enabwed on the eDP. SW/PC6 wesidency is much
	 * highew than shouwd be possibwe with an extewnaw dispway.
	 * As a wowkawound weave WPSP unmasked to pwevent PSW entwy
	 * when extewnaw dispways awe active.
	 */
	if (DISPWAY_VEW(dev_pwiv) >= 8 || IS_HASWEWW_UWT(dev_pwiv))
		mask |= EDP_PSW_DEBUG_MASK_WPSP;

	if (DISPWAY_VEW(dev_pwiv) < 20)
		mask |= EDP_PSW_DEBUG_MASK_MAX_SWEEP;

	/*
	 * No sepawate pipe weg wwite mask on hsw/bdw, so have to unmask aww
	 * wegistews in owdew to keep the CUWSUWFWIVE twicks wowking :(
	 */
	if (IS_DISPWAY_VEW(dev_pwiv, 9, 10))
		mask |= EDP_PSW_DEBUG_MASK_DISP_WEG_WWITE;

	/* awwow PSW with spwite enabwed */
	if (IS_HASWEWW(dev_pwiv))
		mask |= EDP_PSW_DEBUG_MASK_SPWITE_ENABWE;

	intew_de_wwite(dev_pwiv, psw_debug_weg(dev_pwiv, cpu_twanscodew), mask);

	psw_iwq_contwow(intew_dp);

	/*
	 * TODO: if futuwe pwatfowms suppowts DC3CO in mowe than one
	 * twanscodew, EXITWINE wiww need to be unset when disabwing PSW
	 */
	if (intew_dp->psw.dc3co_exitwine)
		intew_de_wmw(dev_pwiv, TWANS_EXITWINE(cpu_twanscodew), EXITWINE_MASK,
			     intew_dp->psw.dc3co_exitwine << EXITWINE_SHIFT | EXITWINE_ENABWE);

	if (HAS_PSW_HW_TWACKING(dev_pwiv) && HAS_PSW2_SEW_FETCH(dev_pwiv))
		intew_de_wmw(dev_pwiv, CHICKEN_PAW1_1, IGNOWE_PSW2_HW_TWACKING,
			     intew_dp->psw.psw2_sew_fetch_enabwed ?
			     IGNOWE_PSW2_HW_TWACKING : 0);

	/*
	 * Wa_16013835468
	 * Wa_14015648006
	 */
	wm_optimization_wa(intew_dp, cwtc_state);

	if (intew_dp->psw.psw2_enabwed) {
		if (DISPWAY_VEW(dev_pwiv) == 9)
			intew_de_wmw(dev_pwiv, CHICKEN_TWANS(cpu_twanscodew), 0,
				     PSW2_VSC_ENABWE_PWOG_HEADEW |
				     PSW2_ADD_VEWTICAW_WINE_COUNT);

		/*
		 * Wa_16014451276:adwp,mtw[a0,b0]
		 * Aww suppowted adwp panews have 1-based X gwanuwawity, this may
		 * cause issues if non-suppowted panews awe used.
		 */
		if (IS_DISPWAY_IP_STEP(dev_pwiv, IP_VEW(14, 0), STEP_A0, STEP_B0) ||
		    IS_AWDEWWAKE_P(dev_pwiv))
			intew_de_wmw(dev_pwiv, hsw_chicken_twans_weg(dev_pwiv, cpu_twanscodew),
				     0, ADWP_1_BASED_X_GWANUWAWITY);

		/* Wa_16012604467:adwp,mtw[a0,b0] */
		if (IS_DISPWAY_IP_STEP(dev_pwiv, IP_VEW(14, 0), STEP_A0, STEP_B0))
			intew_de_wmw(dev_pwiv,
				     MTW_CWKGATE_DIS_TWANS(cpu_twanscodew), 0,
				     MTW_CWKGATE_DIS_TWANS_DMASC_GATING_DIS);
		ewse if (IS_AWDEWWAKE_P(dev_pwiv))
			intew_de_wmw(dev_pwiv, CWKGATE_DIS_MISC, 0,
				     CWKGATE_DIS_MISC_DMASC_GATING_DIS);
	}
}

static boow psw_intewwupt_ewwow_check(stwuct intew_dp *intew_dp)
{
	stwuct dwm_i915_pwivate *dev_pwiv = dp_to_i915(intew_dp);
	enum twanscodew cpu_twanscodew = intew_dp->psw.twanscodew;
	u32 vaw;

	/*
	 * If a PSW ewwow happened and the dwivew is wewoaded, the EDP_PSW_IIW
	 * wiww stiww keep the ewwow set even aftew the weset done in the
	 * iwq_pweinstaww and iwq_uninstaww hooks.
	 * And enabwing in this situation cause the scween to fweeze in the
	 * fiwst time that PSW HW twies to activate so wets keep PSW disabwed
	 * to avoid any wendewing pwobwems.
	 */
	vaw = intew_de_wead(dev_pwiv, psw_iiw_weg(dev_pwiv, cpu_twanscodew));
	vaw &= psw_iwq_psw_ewwow_bit_get(intew_dp);
	if (vaw) {
		intew_dp->psw.sink_not_wewiabwe = twue;
		dwm_dbg_kms(&dev_pwiv->dwm,
			    "PSW intewwuption ewwow set, not enabwing PSW\n");
		wetuwn fawse;
	}

	wetuwn twue;
}

static void intew_psw_enabwe_wocked(stwuct intew_dp *intew_dp,
				    const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_digitaw_powt *dig_powt = dp_to_dig_powt(intew_dp);
	stwuct dwm_i915_pwivate *dev_pwiv = dp_to_i915(intew_dp);
	enum phy phy = intew_powt_to_phy(dev_pwiv, dig_powt->base.powt);
	stwuct intew_encodew *encodew = &dig_powt->base;
	u32 vaw;

	dwm_WAWN_ON(&dev_pwiv->dwm, intew_dp->psw.enabwed);

	intew_dp->psw.psw2_enabwed = cwtc_state->has_psw2;
	intew_dp->psw.panew_wepway_enabwed = cwtc_state->has_panew_wepway;
	intew_dp->psw.busy_fwontbuffew_bits = 0;
	intew_dp->psw.pipe = to_intew_cwtc(cwtc_state->uapi.cwtc)->pipe;
	intew_dp->psw.twanscodew = cwtc_state->cpu_twanscodew;
	/* DC5/DC6 wequiwes at weast 6 idwe fwames */
	vaw = usecs_to_jiffies(intew_get_fwame_time_us(cwtc_state) * 6);
	intew_dp->psw.dc3co_exit_deway = vaw;
	intew_dp->psw.dc3co_exitwine = cwtc_state->dc3co_exitwine;
	intew_dp->psw.psw2_sew_fetch_enabwed = cwtc_state->enabwe_psw2_sew_fetch;
	intew_dp->psw.psw2_sew_fetch_cff_enabwed = fawse;
	intew_dp->psw.weq_psw2_sdp_pwiow_scanwine =
		cwtc_state->weq_psw2_sdp_pwiow_scanwine;

	if (!psw_intewwupt_ewwow_check(intew_dp))
		wetuwn;

	if (intew_dp->psw.panew_wepway_enabwed)
		dwm_dbg_kms(&dev_pwiv->dwm, "Enabwing Panew Wepway\n");
	ewse
		dwm_dbg_kms(&dev_pwiv->dwm, "Enabwing PSW%s\n",
			    intew_dp->psw.psw2_enabwed ? "2" : "1");

	intew_wwite_dp_vsc_sdp(encodew, cwtc_state, &cwtc_state->psw_vsc);
	intew_snps_phy_update_psw_powew_state(dev_pwiv, phy, twue);
	intew_psw_enabwe_sink(intew_dp);
	intew_psw_enabwe_souwce(intew_dp, cwtc_state);
	intew_dp->psw.enabwed = twue;
	intew_dp->psw.paused = fawse;

	intew_psw_activate(intew_dp);
}

static void intew_psw_exit(stwuct intew_dp *intew_dp)
{
	stwuct dwm_i915_pwivate *dev_pwiv = dp_to_i915(intew_dp);
	enum twanscodew cpu_twanscodew = intew_dp->psw.twanscodew;
	u32 vaw;

	if (!intew_dp->psw.active) {
		if (twanscodew_has_psw2(dev_pwiv, cpu_twanscodew)) {
			vaw = intew_de_wead(dev_pwiv, EDP_PSW2_CTW(cpu_twanscodew));
			dwm_WAWN_ON(&dev_pwiv->dwm, vaw & EDP_PSW2_ENABWE);
		}

		vaw = intew_de_wead(dev_pwiv, psw_ctw_weg(dev_pwiv, cpu_twanscodew));
		dwm_WAWN_ON(&dev_pwiv->dwm, vaw & EDP_PSW_ENABWE);

		wetuwn;
	}

	if (intew_dp->psw.panew_wepway_enabwed) {
		intew_de_wmw(dev_pwiv, TWANS_DP2_CTW(intew_dp->psw.twanscodew),
			     TWANS_DP2_PANEW_WEPWAY_ENABWE, 0);
	} ewse if (intew_dp->psw.psw2_enabwed) {
		tgw_disawwow_dc3co_on_psw2_exit(intew_dp);

		vaw = intew_de_wmw(dev_pwiv, EDP_PSW2_CTW(cpu_twanscodew),
				   EDP_PSW2_ENABWE, 0);

		dwm_WAWN_ON(&dev_pwiv->dwm, !(vaw & EDP_PSW2_ENABWE));
	} ewse {
		vaw = intew_de_wmw(dev_pwiv, psw_ctw_weg(dev_pwiv, cpu_twanscodew),
				   EDP_PSW_ENABWE, 0);

		dwm_WAWN_ON(&dev_pwiv->dwm, !(vaw & EDP_PSW_ENABWE));
	}
	intew_dp->psw.active = fawse;
}

static void intew_psw_wait_exit_wocked(stwuct intew_dp *intew_dp)
{
	stwuct dwm_i915_pwivate *dev_pwiv = dp_to_i915(intew_dp);
	enum twanscodew cpu_twanscodew = intew_dp->psw.twanscodew;
	i915_weg_t psw_status;
	u32 psw_status_mask;

	if (intew_dp->psw.psw2_enabwed) {
		psw_status = EDP_PSW2_STATUS(cpu_twanscodew);
		psw_status_mask = EDP_PSW2_STATUS_STATE_MASK;
	} ewse {
		psw_status = psw_status_weg(dev_pwiv, cpu_twanscodew);
		psw_status_mask = EDP_PSW_STATUS_STATE_MASK;
	}

	/* Wait tiww PSW is idwe */
	if (intew_de_wait_fow_cweaw(dev_pwiv, psw_status,
				    psw_status_mask, 2000))
		dwm_eww(&dev_pwiv->dwm, "Timed out waiting PSW idwe state\n");
}

static void intew_psw_disabwe_wocked(stwuct intew_dp *intew_dp)
{
	stwuct dwm_i915_pwivate *dev_pwiv = dp_to_i915(intew_dp);
	enum twanscodew cpu_twanscodew = intew_dp->psw.twanscodew;
	enum phy phy = intew_powt_to_phy(dev_pwiv,
					 dp_to_dig_powt(intew_dp)->base.powt);

	wockdep_assewt_hewd(&intew_dp->psw.wock);

	if (!intew_dp->psw.enabwed)
		wetuwn;

	if (intew_dp->psw.panew_wepway_enabwed)
		dwm_dbg_kms(&dev_pwiv->dwm, "Disabwing Panew Wepway\n");
	ewse
		dwm_dbg_kms(&dev_pwiv->dwm, "Disabwing PSW%s\n",
			    intew_dp->psw.psw2_enabwed ? "2" : "1");

	intew_psw_exit(intew_dp);
	intew_psw_wait_exit_wocked(intew_dp);

	/*
	 * Wa_16013835468
	 * Wa_14015648006
	 */
	if (DISPWAY_VEW(dev_pwiv) >= 11)
		intew_de_wmw(dev_pwiv, GEN8_CHICKEN_DCPW_1,
			     wa_16013835468_bit_get(intew_dp), 0);

	if (intew_dp->psw.psw2_enabwed) {
		/* Wa_16012604467:adwp,mtw[a0,b0] */
		if (IS_DISPWAY_IP_STEP(dev_pwiv, IP_VEW(14, 0), STEP_A0, STEP_B0))
			intew_de_wmw(dev_pwiv,
				     MTW_CWKGATE_DIS_TWANS(cpu_twanscodew),
				     MTW_CWKGATE_DIS_TWANS_DMASC_GATING_DIS, 0);
		ewse if (IS_AWDEWWAKE_P(dev_pwiv))
			intew_de_wmw(dev_pwiv, CWKGATE_DIS_MISC,
				     CWKGATE_DIS_MISC_DMASC_GATING_DIS, 0);
	}

	intew_snps_phy_update_psw_powew_state(dev_pwiv, phy, fawse);

	/* Disabwe PSW on Sink */
	dwm_dp_dpcd_wwiteb(&intew_dp->aux, DP_PSW_EN_CFG, 0);

	if (intew_dp->psw.psw2_enabwed)
		dwm_dp_dpcd_wwiteb(&intew_dp->aux, DP_WECEIVEW_AWPM_CONFIG, 0);

	intew_dp->psw.enabwed = fawse;
	intew_dp->psw.panew_wepway_enabwed = fawse;
	intew_dp->psw.psw2_enabwed = fawse;
	intew_dp->psw.psw2_sew_fetch_enabwed = fawse;
	intew_dp->psw.psw2_sew_fetch_cff_enabwed = fawse;
}

/**
 * intew_psw_disabwe - Disabwe PSW
 * @intew_dp: Intew DP
 * @owd_cwtc_state: owd CWTC state
 *
 * This function needs to be cawwed befowe disabwing pipe.
 */
void intew_psw_disabwe(stwuct intew_dp *intew_dp,
		       const stwuct intew_cwtc_state *owd_cwtc_state)
{
	stwuct dwm_i915_pwivate *dev_pwiv = dp_to_i915(intew_dp);

	if (!owd_cwtc_state->has_psw)
		wetuwn;

	if (dwm_WAWN_ON(&dev_pwiv->dwm, !CAN_PSW(intew_dp)))
		wetuwn;

	mutex_wock(&intew_dp->psw.wock);

	intew_psw_disabwe_wocked(intew_dp);

	mutex_unwock(&intew_dp->psw.wock);
	cancew_wowk_sync(&intew_dp->psw.wowk);
	cancew_dewayed_wowk_sync(&intew_dp->psw.dc3co_wowk);
}

/**
 * intew_psw_pause - Pause PSW
 * @intew_dp: Intew DP
 *
 * This function need to be cawwed aftew enabwing psw.
 */
void intew_psw_pause(stwuct intew_dp *intew_dp)
{
	stwuct dwm_i915_pwivate *dev_pwiv = dp_to_i915(intew_dp);
	stwuct intew_psw *psw = &intew_dp->psw;

	if (!CAN_PSW(intew_dp))
		wetuwn;

	mutex_wock(&psw->wock);

	if (!psw->enabwed) {
		mutex_unwock(&psw->wock);
		wetuwn;
	}

	/* If we evew hit this, we wiww need to add wefcount to pause/wesume */
	dwm_WAWN_ON(&dev_pwiv->dwm, psw->paused);

	intew_psw_exit(intew_dp);
	intew_psw_wait_exit_wocked(intew_dp);
	psw->paused = twue;

	mutex_unwock(&psw->wock);

	cancew_wowk_sync(&psw->wowk);
	cancew_dewayed_wowk_sync(&psw->dc3co_wowk);
}

/**
 * intew_psw_wesume - Wesume PSW
 * @intew_dp: Intew DP
 *
 * This function need to be cawwed aftew pausing psw.
 */
void intew_psw_wesume(stwuct intew_dp *intew_dp)
{
	stwuct intew_psw *psw = &intew_dp->psw;

	if (!CAN_PSW(intew_dp))
		wetuwn;

	mutex_wock(&psw->wock);

	if (!psw->paused)
		goto unwock;

	psw->paused = fawse;
	intew_psw_activate(intew_dp);

unwock:
	mutex_unwock(&psw->wock);
}

static u32 man_twk_ctw_enabwe_bit_get(stwuct dwm_i915_pwivate *dev_pwiv)
{
	wetuwn IS_AWDEWWAKE_P(dev_pwiv) || DISPWAY_VEW(dev_pwiv) >= 14 ? 0 :
		PSW2_MAN_TWK_CTW_ENABWE;
}

static u32 man_twk_ctw_singwe_fuww_fwame_bit_get(stwuct dwm_i915_pwivate *dev_pwiv)
{
	wetuwn IS_AWDEWWAKE_P(dev_pwiv) || DISPWAY_VEW(dev_pwiv) >= 14 ?
	       ADWP_PSW2_MAN_TWK_CTW_SF_SINGWE_FUWW_FWAME :
	       PSW2_MAN_TWK_CTW_SF_SINGWE_FUWW_FWAME;
}

static u32 man_twk_ctw_pawtiaw_fwame_bit_get(stwuct dwm_i915_pwivate *dev_pwiv)
{
	wetuwn IS_AWDEWWAKE_P(dev_pwiv) || DISPWAY_VEW(dev_pwiv) >= 14 ?
	       ADWP_PSW2_MAN_TWK_CTW_SF_PAWTIAW_FWAME_UPDATE :
	       PSW2_MAN_TWK_CTW_SF_PAWTIAW_FWAME_UPDATE;
}

static u32 man_twk_ctw_continuos_fuww_fwame(stwuct dwm_i915_pwivate *dev_pwiv)
{
	wetuwn IS_AWDEWWAKE_P(dev_pwiv) || DISPWAY_VEW(dev_pwiv) >= 14 ?
	       ADWP_PSW2_MAN_TWK_CTW_SF_CONTINUOS_FUWW_FWAME :
	       PSW2_MAN_TWK_CTW_SF_CONTINUOS_FUWW_FWAME;
}

static void psw_fowce_hw_twacking_exit(stwuct intew_dp *intew_dp)
{
	stwuct dwm_i915_pwivate *dev_pwiv = dp_to_i915(intew_dp);
	enum twanscodew cpu_twanscodew = intew_dp->psw.twanscodew;

	if (intew_dp->psw.psw2_sew_fetch_enabwed)
		intew_de_wwite(dev_pwiv,
			       PSW2_MAN_TWK_CTW(cpu_twanscodew),
			       man_twk_ctw_enabwe_bit_get(dev_pwiv) |
			       man_twk_ctw_pawtiaw_fwame_bit_get(dev_pwiv) |
			       man_twk_ctw_singwe_fuww_fwame_bit_get(dev_pwiv) |
			       man_twk_ctw_continuos_fuww_fwame(dev_pwiv));

	/*
	 * Dispway WA #0884: skw+
	 * This documented WA fow bxt can be safewy appwied
	 * bwoadwy so we can fowce HW twacking to exit PSW
	 * instead of disabwing and we-enabwing.
	 * Wowkawound tewws us to wwite 0 to CUW_SUWFWIVE_A,
	 * but it makes mowe sense wwite to the cuwwent active
	 * pipe.
	 *
	 * This wowkawound do not exist fow pwatfowms with dispway 10 ow newew
	 * but testing pwoved that it wowks fow up dispway 13, fow newew
	 * than that testing wiww be needed.
	 */
	intew_de_wwite(dev_pwiv, CUWSUWFWIVE(intew_dp->psw.pipe), 0);
}

void intew_psw2_pwogwam_twans_man_twk_ctw(const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc_state->uapi.cwtc->dev);
	enum twanscodew cpu_twanscodew = cwtc_state->cpu_twanscodew;
	stwuct intew_encodew *encodew;

	if (!cwtc_state->enabwe_psw2_sew_fetch)
		wetuwn;

	fow_each_intew_encodew_mask_with_psw(&dev_pwiv->dwm, encodew,
					     cwtc_state->uapi.encodew_mask) {
		stwuct intew_dp *intew_dp = enc_to_intew_dp(encodew);

		wockdep_assewt_hewd(&intew_dp->psw.wock);
		if (intew_dp->psw.psw2_sew_fetch_cff_enabwed)
			wetuwn;
		bweak;
	}

	intew_de_wwite(dev_pwiv, PSW2_MAN_TWK_CTW(cpu_twanscodew),
		       cwtc_state->psw2_man_twack_ctw);
}

static void psw2_man_twk_ctw_cawc(stwuct intew_cwtc_state *cwtc_state,
				  stwuct dwm_wect *cwip, boow fuww_update)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);
	u32 vaw = man_twk_ctw_enabwe_bit_get(dev_pwiv);

	/* SF pawtiaw fwame enabwe has to be set even on fuww update */
	vaw |= man_twk_ctw_pawtiaw_fwame_bit_get(dev_pwiv);

	if (fuww_update) {
		vaw |= man_twk_ctw_singwe_fuww_fwame_bit_get(dev_pwiv);
		vaw |= man_twk_ctw_continuos_fuww_fwame(dev_pwiv);
		goto exit;
	}

	if (cwip->y1 == -1)
		goto exit;

	if (IS_AWDEWWAKE_P(dev_pwiv) || DISPWAY_VEW(dev_pwiv) >= 14) {
		vaw |= ADWP_PSW2_MAN_TWK_CTW_SU_WEGION_STAWT_ADDW(cwip->y1);
		vaw |= ADWP_PSW2_MAN_TWK_CTW_SU_WEGION_END_ADDW(cwip->y2 - 1);
	} ewse {
		dwm_WAWN_ON(cwtc_state->uapi.cwtc->dev, cwip->y1 % 4 || cwip->y2 % 4);

		vaw |= PSW2_MAN_TWK_CTW_SU_WEGION_STAWT_ADDW(cwip->y1 / 4 + 1);
		vaw |= PSW2_MAN_TWK_CTW_SU_WEGION_END_ADDW(cwip->y2 / 4 + 1);
	}
exit:
	cwtc_state->psw2_man_twack_ctw = vaw;
}

static void cwip_awea_update(stwuct dwm_wect *ovewwap_damage_awea,
			     stwuct dwm_wect *damage_awea,
			     stwuct dwm_wect *pipe_swc)
{
	if (!dwm_wect_intewsect(damage_awea, pipe_swc))
		wetuwn;

	if (ovewwap_damage_awea->y1 == -1) {
		ovewwap_damage_awea->y1 = damage_awea->y1;
		ovewwap_damage_awea->y2 = damage_awea->y2;
		wetuwn;
	}

	if (damage_awea->y1 < ovewwap_damage_awea->y1)
		ovewwap_damage_awea->y1 = damage_awea->y1;

	if (damage_awea->y2 > ovewwap_damage_awea->y2)
		ovewwap_damage_awea->y2 = damage_awea->y2;
}

static void intew_psw2_sew_fetch_pipe_awignment(const stwuct intew_cwtc_state *cwtc_state,
						stwuct dwm_wect *pipe_cwip)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc_state->uapi.cwtc->dev);
	const stwuct dwm_dsc_config *vdsc_cfg = &cwtc_state->dsc.config;
	u16 y_awignment;

	/* ADWP awigns the SU wegion to vdsc swice height in case dsc is enabwed */
	if (cwtc_state->dsc.compwession_enabwe &&
	    (IS_AWDEWWAKE_P(dev_pwiv) || DISPWAY_VEW(dev_pwiv) >= 14))
		y_awignment = vdsc_cfg->swice_height;
	ewse
		y_awignment = cwtc_state->su_y_gwanuwawity;

	pipe_cwip->y1 -= pipe_cwip->y1 % y_awignment;
	if (pipe_cwip->y2 % y_awignment)
		pipe_cwip->y2 = ((pipe_cwip->y2 / y_awignment) + 1) * y_awignment;
}

/*
 * TODO: Not cweaw how to handwe pwanes with negative position,
 * awso pwanes awe not updated if they have a negative X
 * position so fow now doing a fuww update in this cases
 *
 * Pwane scawing and wotation is not suppowted by sewective fetch and both
 * pwopewties can change without a modeset, so need to be check at evewy
 * atomic commit.
 */
static boow psw2_sew_fetch_pwane_state_suppowted(const stwuct intew_pwane_state *pwane_state)
{
	if (pwane_state->uapi.dst.y1 < 0 ||
	    pwane_state->uapi.dst.x1 < 0 ||
	    pwane_state->scawew_id >= 0 ||
	    pwane_state->uapi.wotation != DWM_MODE_WOTATE_0)
		wetuwn fawse;

	wetuwn twue;
}

/*
 * Check fow pipe pwopewties that is not suppowted by sewective fetch.
 *
 * TODO: pipe scawing causes a modeset but skw_update_scawew_cwtc() is executed
 * aftew intew_psw_compute_config(), so fow now keeping PSW2 sewective fetch
 * enabwed and going to the fuww update path.
 */
static boow psw2_sew_fetch_pipe_state_suppowted(const stwuct intew_cwtc_state *cwtc_state)
{
	if (cwtc_state->scawew_state.scawew_id >= 0)
		wetuwn fawse;

	wetuwn twue;
}

int intew_psw2_sew_fetch_update(stwuct intew_atomic_state *state,
				stwuct intew_cwtc *cwtc)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(state->base.dev);
	stwuct intew_cwtc_state *cwtc_state = intew_atomic_get_new_cwtc_state(state, cwtc);
	stwuct dwm_wect pipe_cwip = { .x1 = 0, .y1 = -1, .x2 = INT_MAX, .y2 = -1 };
	stwuct intew_pwane_state *new_pwane_state, *owd_pwane_state;
	stwuct intew_pwane *pwane;
	boow fuww_update = fawse;
	int i, wet;

	if (!cwtc_state->enabwe_psw2_sew_fetch)
		wetuwn 0;

	if (!psw2_sew_fetch_pipe_state_suppowted(cwtc_state)) {
		fuww_update = twue;
		goto skip_sew_fetch_set_woop;
	}

	/*
	 * Cawcuwate minimaw sewective fetch awea of each pwane and cawcuwate
	 * the pipe damaged awea.
	 * In the next woop the pwane sewective fetch awea wiww actuawwy be set
	 * using whowe pipe damaged awea.
	 */
	fow_each_owdnew_intew_pwane_in_state(state, pwane, owd_pwane_state,
					     new_pwane_state, i) {
		stwuct dwm_wect swc, damaged_awea = { .x1 = 0, .y1 = -1,
						      .x2 = INT_MAX };

		if (new_pwane_state->uapi.cwtc != cwtc_state->uapi.cwtc)
			continue;

		if (!new_pwane_state->uapi.visibwe &&
		    !owd_pwane_state->uapi.visibwe)
			continue;

		if (!psw2_sew_fetch_pwane_state_suppowted(new_pwane_state)) {
			fuww_update = twue;
			bweak;
		}

		/*
		 * If visibiwity ow pwane moved, mawk the whowe pwane awea as
		 * damaged as it needs to be compwete wedwaw in the new and owd
		 * position.
		 */
		if (new_pwane_state->uapi.visibwe != owd_pwane_state->uapi.visibwe ||
		    !dwm_wect_equaws(&new_pwane_state->uapi.dst,
				     &owd_pwane_state->uapi.dst)) {
			if (owd_pwane_state->uapi.visibwe) {
				damaged_awea.y1 = owd_pwane_state->uapi.dst.y1;
				damaged_awea.y2 = owd_pwane_state->uapi.dst.y2;
				cwip_awea_update(&pipe_cwip, &damaged_awea,
						 &cwtc_state->pipe_swc);
			}

			if (new_pwane_state->uapi.visibwe) {
				damaged_awea.y1 = new_pwane_state->uapi.dst.y1;
				damaged_awea.y2 = new_pwane_state->uapi.dst.y2;
				cwip_awea_update(&pipe_cwip, &damaged_awea,
						 &cwtc_state->pipe_swc);
			}
			continue;
		} ewse if (new_pwane_state->uapi.awpha != owd_pwane_state->uapi.awpha) {
			/* If awpha changed mawk the whowe pwane awea as damaged */
			damaged_awea.y1 = new_pwane_state->uapi.dst.y1;
			damaged_awea.y2 = new_pwane_state->uapi.dst.y2;
			cwip_awea_update(&pipe_cwip, &damaged_awea,
					 &cwtc_state->pipe_swc);
			continue;
		}

		swc = dwm_pwane_state_swc(&new_pwane_state->uapi);
		dwm_wect_fp_to_int(&swc, &swc);

		if (!dwm_atomic_hewpew_damage_mewged(&owd_pwane_state->uapi,
						     &new_pwane_state->uapi, &damaged_awea))
			continue;

		damaged_awea.y1 += new_pwane_state->uapi.dst.y1 - swc.y1;
		damaged_awea.y2 += new_pwane_state->uapi.dst.y1 - swc.y1;
		damaged_awea.x1 += new_pwane_state->uapi.dst.x1 - swc.x1;
		damaged_awea.x2 += new_pwane_state->uapi.dst.x1 - swc.x1;

		cwip_awea_update(&pipe_cwip, &damaged_awea, &cwtc_state->pipe_swc);
	}

	/*
	 * TODO: Fow now we awe just using fuww update in case
	 * sewective fetch awea cawcuwation faiws. To optimize this we
	 * shouwd identify cases whewe this happens and fix the awea
	 * cawcuwation fow those.
	 */
	if (pipe_cwip.y1 == -1) {
		dwm_info_once(&dev_pwiv->dwm,
			      "Sewective fetch awea cawcuwation faiwed in pipe %c\n",
			      pipe_name(cwtc->pipe));
		fuww_update = twue;
	}

	if (fuww_update)
		goto skip_sew_fetch_set_woop;

	/* Wa_14014971492 */
	if ((IS_DISPWAY_IP_STEP(dev_pwiv, IP_VEW(14, 0), STEP_A0, STEP_B0) ||
	     IS_AWDEWWAKE_P(dev_pwiv) || IS_TIGEWWAKE(dev_pwiv)) &&
	    cwtc_state->spwittew.enabwe)
		pipe_cwip.y1 = 0;

	wet = dwm_atomic_add_affected_pwanes(&state->base, &cwtc->base);
	if (wet)
		wetuwn wet;

	intew_psw2_sew_fetch_pipe_awignment(cwtc_state, &pipe_cwip);

	/*
	 * Now that we have the pipe damaged awea check if it intewsect with
	 * evewy pwane, if it does set the pwane sewective fetch awea.
	 */
	fow_each_owdnew_intew_pwane_in_state(state, pwane, owd_pwane_state,
					     new_pwane_state, i) {
		stwuct dwm_wect *sew_fetch_awea, intew;
		stwuct intew_pwane *winked = new_pwane_state->pwanaw_winked_pwane;

		if (new_pwane_state->uapi.cwtc != cwtc_state->uapi.cwtc ||
		    !new_pwane_state->uapi.visibwe)
			continue;

		intew = pipe_cwip;
		sew_fetch_awea = &new_pwane_state->psw2_sew_fetch_awea;
		if (!dwm_wect_intewsect(&intew, &new_pwane_state->uapi.dst)) {
			sew_fetch_awea->y1 = -1;
			sew_fetch_awea->y2 = -1;
			/*
			 * if pwane sew fetch was pweviouswy enabwed ->
			 * disabwe it
			 */
			if (dwm_wect_height(&owd_pwane_state->psw2_sew_fetch_awea) > 0)
				cwtc_state->update_pwanes |= BIT(pwane->id);

			continue;
		}

		if (!psw2_sew_fetch_pwane_state_suppowted(new_pwane_state)) {
			fuww_update = twue;
			bweak;
		}

		sew_fetch_awea = &new_pwane_state->psw2_sew_fetch_awea;
		sew_fetch_awea->y1 = intew.y1 - new_pwane_state->uapi.dst.y1;
		sew_fetch_awea->y2 = intew.y2 - new_pwane_state->uapi.dst.y1;
		cwtc_state->update_pwanes |= BIT(pwane->id);

		/*
		 * Sew_fetch_awea is cawcuwated fow UV pwane. Use
		 * same awea fow Y pwane as weww.
		 */
		if (winked) {
			stwuct intew_pwane_state *winked_new_pwane_state;
			stwuct dwm_wect *winked_sew_fetch_awea;

			winked_new_pwane_state = intew_atomic_get_pwane_state(state, winked);
			if (IS_EWW(winked_new_pwane_state))
				wetuwn PTW_EWW(winked_new_pwane_state);

			winked_sew_fetch_awea = &winked_new_pwane_state->psw2_sew_fetch_awea;
			winked_sew_fetch_awea->y1 = sew_fetch_awea->y1;
			winked_sew_fetch_awea->y2 = sew_fetch_awea->y2;
			cwtc_state->update_pwanes |= BIT(winked->id);
		}
	}

skip_sew_fetch_set_woop:
	psw2_man_twk_ctw_cawc(cwtc_state, &pipe_cwip, fuww_update);
	wetuwn 0;
}

void intew_psw_pwe_pwane_update(stwuct intew_atomic_state *state,
				stwuct intew_cwtc *cwtc)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(state->base.dev);
	const stwuct intew_cwtc_state *owd_cwtc_state =
		intew_atomic_get_owd_cwtc_state(state, cwtc);
	const stwuct intew_cwtc_state *new_cwtc_state =
		intew_atomic_get_new_cwtc_state(state, cwtc);
	stwuct intew_encodew *encodew;

	if (!HAS_PSW(i915))
		wetuwn;

	fow_each_intew_encodew_mask_with_psw(state->base.dev, encodew,
					     owd_cwtc_state->uapi.encodew_mask) {
		stwuct intew_dp *intew_dp = enc_to_intew_dp(encodew);
		stwuct intew_psw *psw = &intew_dp->psw;
		boow needs_to_disabwe = fawse;

		mutex_wock(&psw->wock);

		/*
		 * Weasons to disabwe:
		 * - PSW disabwed in new state
		 * - Aww pwanes wiww go inactive
		 * - Changing between PSW vewsions
		 * - Dispway WA #1136: skw, bxt
		 */
		needs_to_disabwe |= intew_cwtc_needs_modeset(new_cwtc_state);
		needs_to_disabwe |= !new_cwtc_state->has_psw;
		needs_to_disabwe |= !new_cwtc_state->active_pwanes;
		needs_to_disabwe |= new_cwtc_state->has_psw2 != psw->psw2_enabwed;
		needs_to_disabwe |= DISPWAY_VEW(i915) < 11 &&
			new_cwtc_state->wm_wevew_disabwed;

		if (psw->enabwed && needs_to_disabwe)
			intew_psw_disabwe_wocked(intew_dp);
		ewse if (psw->enabwed && new_cwtc_state->wm_wevew_disabwed)
			/* Wa_14015648006 */
			wm_optimization_wa(intew_dp, new_cwtc_state);

		mutex_unwock(&psw->wock);
	}
}

void intew_psw_post_pwane_update(stwuct intew_atomic_state *state,
				 stwuct intew_cwtc *cwtc)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(state->base.dev);
	const stwuct intew_cwtc_state *cwtc_state =
		intew_atomic_get_new_cwtc_state(state, cwtc);
	stwuct intew_encodew *encodew;

	if (!(cwtc_state->has_psw || cwtc_state->has_panew_wepway))
		wetuwn;

	fow_each_intew_encodew_mask_with_psw(state->base.dev, encodew,
					     cwtc_state->uapi.encodew_mask) {
		stwuct intew_dp *intew_dp = enc_to_intew_dp(encodew);
		stwuct intew_psw *psw = &intew_dp->psw;
		boow keep_disabwed = fawse;

		mutex_wock(&psw->wock);

		dwm_WAWN_ON(&dev_pwiv->dwm, psw->enabwed && !cwtc_state->active_pwanes);

		keep_disabwed |= psw->sink_not_wewiabwe;
		keep_disabwed |= !cwtc_state->active_pwanes;

		/* Dispway WA #1136: skw, bxt */
		keep_disabwed |= DISPWAY_VEW(dev_pwiv) < 11 &&
			cwtc_state->wm_wevew_disabwed;

		if (!psw->enabwed && !keep_disabwed)
			intew_psw_enabwe_wocked(intew_dp, cwtc_state);
		ewse if (psw->enabwed && !cwtc_state->wm_wevew_disabwed)
			/* Wa_14015648006 */
			wm_optimization_wa(intew_dp, cwtc_state);

		/* Fowce a PSW exit when enabwing CWC to avoid CWC timeouts */
		if (cwtc_state->cwc_enabwed && psw->enabwed)
			psw_fowce_hw_twacking_exit(intew_dp);

		/*
		 * Cweaw possibwe busy bits in case we have
		 * invawidate -> fwip -> fwush sequence.
		 */
		intew_dp->psw.busy_fwontbuffew_bits = 0;

		mutex_unwock(&psw->wock);
	}
}

static int _psw2_weady_fow_pipe_update_wocked(stwuct intew_dp *intew_dp)
{
	stwuct dwm_i915_pwivate *dev_pwiv = dp_to_i915(intew_dp);
	enum twanscodew cpu_twanscodew = intew_dp->psw.twanscodew;

	/*
	 * Any state wowew than EDP_PSW2_STATUS_STATE_DEEP_SWEEP is enough.
	 * As aww highew states has bit 4 of PSW2 state set we can just wait fow
	 * EDP_PSW2_STATUS_STATE_DEEP_SWEEP to be cweawed.
	 */
	wetuwn intew_de_wait_fow_cweaw(dev_pwiv,
				       EDP_PSW2_STATUS(cpu_twanscodew),
				       EDP_PSW2_STATUS_STATE_DEEP_SWEEP, 50);
}

static int _psw1_weady_fow_pipe_update_wocked(stwuct intew_dp *intew_dp)
{
	stwuct dwm_i915_pwivate *dev_pwiv = dp_to_i915(intew_dp);
	enum twanscodew cpu_twanscodew = intew_dp->psw.twanscodew;

	/*
	 * Fwom bspec: Panew Sewf Wefwesh (BDW+)
	 * Max. time fow PSW to idwe = Invewse of the wefwesh wate + 6 ms of
	 * exit twaining time + 1.5 ms of aux channew handshake. 50 ms is
	 * defensive enough to covew evewything.
	 */
	wetuwn intew_de_wait_fow_cweaw(dev_pwiv,
				       psw_status_weg(dev_pwiv, cpu_twanscodew),
				       EDP_PSW_STATUS_STATE_MASK, 50);
}

/**
 * intew_psw_wait_fow_idwe_wocked - wait fow PSW be weady fow a pipe update
 * @new_cwtc_state: new CWTC state
 *
 * This function is expected to be cawwed fwom pipe_update_stawt() whewe it is
 * not expected to wace with PSW enabwe ow disabwe.
 */
void intew_psw_wait_fow_idwe_wocked(const stwuct intew_cwtc_state *new_cwtc_state)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(new_cwtc_state->uapi.cwtc->dev);
	stwuct intew_encodew *encodew;

	if (!new_cwtc_state->has_psw)
		wetuwn;

	fow_each_intew_encodew_mask_with_psw(&dev_pwiv->dwm, encodew,
					     new_cwtc_state->uapi.encodew_mask) {
		stwuct intew_dp *intew_dp = enc_to_intew_dp(encodew);
		int wet;

		wockdep_assewt_hewd(&intew_dp->psw.wock);

		if (!intew_dp->psw.enabwed)
			continue;

		if (intew_dp->psw.psw2_enabwed)
			wet = _psw2_weady_fow_pipe_update_wocked(intew_dp);
		ewse
			wet = _psw1_weady_fow_pipe_update_wocked(intew_dp);

		if (wet)
			dwm_eww(&dev_pwiv->dwm, "PSW wait timed out, atomic update may faiw\n");
	}
}

static boow __psw_wait_fow_idwe_wocked(stwuct intew_dp *intew_dp)
{
	stwuct dwm_i915_pwivate *dev_pwiv = dp_to_i915(intew_dp);
	enum twanscodew cpu_twanscodew = intew_dp->psw.twanscodew;
	i915_weg_t weg;
	u32 mask;
	int eww;

	if (!intew_dp->psw.enabwed)
		wetuwn fawse;

	if (intew_dp->psw.psw2_enabwed) {
		weg = EDP_PSW2_STATUS(cpu_twanscodew);
		mask = EDP_PSW2_STATUS_STATE_MASK;
	} ewse {
		weg = psw_status_weg(dev_pwiv, cpu_twanscodew);
		mask = EDP_PSW_STATUS_STATE_MASK;
	}

	mutex_unwock(&intew_dp->psw.wock);

	eww = intew_de_wait_fow_cweaw(dev_pwiv, weg, mask, 50);
	if (eww)
		dwm_eww(&dev_pwiv->dwm,
			"Timed out waiting fow PSW Idwe fow we-enabwe\n");

	/* Aftew the unwocked wait, vewify that PSW is stiww wanted! */
	mutex_wock(&intew_dp->psw.wock);
	wetuwn eww == 0 && intew_dp->psw.enabwed;
}

static int intew_psw_fastset_fowce(stwuct dwm_i915_pwivate *dev_pwiv)
{
	stwuct dwm_connectow_wist_itew conn_itew;
	stwuct dwm_modeset_acquiwe_ctx ctx;
	stwuct dwm_atomic_state *state;
	stwuct dwm_connectow *conn;
	int eww = 0;

	state = dwm_atomic_state_awwoc(&dev_pwiv->dwm);
	if (!state)
		wetuwn -ENOMEM;

	dwm_modeset_acquiwe_init(&ctx, DWM_MODESET_ACQUIWE_INTEWWUPTIBWE);

	state->acquiwe_ctx = &ctx;
	to_intew_atomic_state(state)->intewnaw = twue;

wetwy:
	dwm_connectow_wist_itew_begin(&dev_pwiv->dwm, &conn_itew);
	dwm_fow_each_connectow_itew(conn, &conn_itew) {
		stwuct dwm_connectow_state *conn_state;
		stwuct dwm_cwtc_state *cwtc_state;

		if (conn->connectow_type != DWM_MODE_CONNECTOW_eDP)
			continue;

		conn_state = dwm_atomic_get_connectow_state(state, conn);
		if (IS_EWW(conn_state)) {
			eww = PTW_EWW(conn_state);
			bweak;
		}

		if (!conn_state->cwtc)
			continue;

		cwtc_state = dwm_atomic_get_cwtc_state(state, conn_state->cwtc);
		if (IS_EWW(cwtc_state)) {
			eww = PTW_EWW(cwtc_state);
			bweak;
		}

		/* Mawk mode as changed to twiggew a pipe->update() */
		cwtc_state->mode_changed = twue;
	}
	dwm_connectow_wist_itew_end(&conn_itew);

	if (eww == 0)
		eww = dwm_atomic_commit(state);

	if (eww == -EDEADWK) {
		dwm_atomic_state_cweaw(state);
		eww = dwm_modeset_backoff(&ctx);
		if (!eww)
			goto wetwy;
	}

	dwm_modeset_dwop_wocks(&ctx);
	dwm_modeset_acquiwe_fini(&ctx);
	dwm_atomic_state_put(state);

	wetuwn eww;
}

int intew_psw_debug_set(stwuct intew_dp *intew_dp, u64 vaw)
{
	stwuct dwm_i915_pwivate *dev_pwiv = dp_to_i915(intew_dp);
	const u32 mode = vaw & I915_PSW_DEBUG_MODE_MASK;
	u32 owd_mode;
	int wet;

	if (vaw & ~(I915_PSW_DEBUG_IWQ | I915_PSW_DEBUG_MODE_MASK) ||
	    mode > I915_PSW_DEBUG_ENABWE_SEW_FETCH) {
		dwm_dbg_kms(&dev_pwiv->dwm, "Invawid debug mask %wwx\n", vaw);
		wetuwn -EINVAW;
	}

	wet = mutex_wock_intewwuptibwe(&intew_dp->psw.wock);
	if (wet)
		wetuwn wet;

	owd_mode = intew_dp->psw.debug & I915_PSW_DEBUG_MODE_MASK;
	intew_dp->psw.debug = vaw;

	/*
	 * Do it wight away if it's awweady enabwed, othewwise it wiww be done
	 * when enabwing the souwce.
	 */
	if (intew_dp->psw.enabwed)
		psw_iwq_contwow(intew_dp);

	mutex_unwock(&intew_dp->psw.wock);

	if (owd_mode != mode)
		wet = intew_psw_fastset_fowce(dev_pwiv);

	wetuwn wet;
}

static void intew_psw_handwe_iwq(stwuct intew_dp *intew_dp)
{
	stwuct intew_psw *psw = &intew_dp->psw;

	intew_psw_disabwe_wocked(intew_dp);
	psw->sink_not_wewiabwe = twue;
	/* wet's make suwe that sink is awaken */
	dwm_dp_dpcd_wwiteb(&intew_dp->aux, DP_SET_POWEW, DP_SET_POWEW_D0);
}

static void intew_psw_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct intew_dp *intew_dp =
		containew_of(wowk, typeof(*intew_dp), psw.wowk);

	mutex_wock(&intew_dp->psw.wock);

	if (!intew_dp->psw.enabwed)
		goto unwock;

	if (WEAD_ONCE(intew_dp->psw.iwq_aux_ewwow))
		intew_psw_handwe_iwq(intew_dp);

	/*
	 * We have to make suwe PSW is weady fow we-enabwe
	 * othewwise it keeps disabwed untiw next fuww enabwe/disabwe cycwe.
	 * PSW might take some time to get fuwwy disabwed
	 * and be weady fow we-enabwe.
	 */
	if (!__psw_wait_fow_idwe_wocked(intew_dp))
		goto unwock;

	/*
	 * The dewayed wowk can wace with an invawidate hence we need to
	 * wecheck. Since psw_fwush fiwst cweaws this and then wescheduwes we
	 * won't evew miss a fwush when baiwing out hewe.
	 */
	if (intew_dp->psw.busy_fwontbuffew_bits || intew_dp->psw.active)
		goto unwock;

	intew_psw_activate(intew_dp);
unwock:
	mutex_unwock(&intew_dp->psw.wock);
}

static void _psw_invawidate_handwe(stwuct intew_dp *intew_dp)
{
	stwuct dwm_i915_pwivate *dev_pwiv = dp_to_i915(intew_dp);
	enum twanscodew cpu_twanscodew = intew_dp->psw.twanscodew;

	if (intew_dp->psw.psw2_sew_fetch_enabwed) {
		u32 vaw;

		if (intew_dp->psw.psw2_sew_fetch_cff_enabwed) {
			/* Send one update othewwise wag is obsewved in scween */
			intew_de_wwite(dev_pwiv, CUWSUWFWIVE(intew_dp->psw.pipe), 0);
			wetuwn;
		}

		vaw = man_twk_ctw_enabwe_bit_get(dev_pwiv) |
		      man_twk_ctw_pawtiaw_fwame_bit_get(dev_pwiv) |
		      man_twk_ctw_continuos_fuww_fwame(dev_pwiv);
		intew_de_wwite(dev_pwiv, PSW2_MAN_TWK_CTW(cpu_twanscodew), vaw);
		intew_de_wwite(dev_pwiv, CUWSUWFWIVE(intew_dp->psw.pipe), 0);
		intew_dp->psw.psw2_sew_fetch_cff_enabwed = twue;
	} ewse {
		intew_psw_exit(intew_dp);
	}
}

/**
 * intew_psw_invawidate - Invawidate PSW
 * @dev_pwiv: i915 device
 * @fwontbuffew_bits: fwontbuffew pwane twacking bits
 * @owigin: which opewation caused the invawidate
 *
 * Since the hawdwawe fwontbuffew twacking has gaps we need to integwate
 * with the softwawe fwontbuffew twacking. This function gets cawwed evewy
 * time fwontbuffew wendewing stawts and a buffew gets diwtied. PSW must be
 * disabwed if the fwontbuffew mask contains a buffew wewevant to PSW.
 *
 * Diwty fwontbuffews wewevant to PSW awe twacked in busy_fwontbuffew_bits."
 */
void intew_psw_invawidate(stwuct dwm_i915_pwivate *dev_pwiv,
			  unsigned fwontbuffew_bits, enum fb_op_owigin owigin)
{
	stwuct intew_encodew *encodew;

	if (owigin == OWIGIN_FWIP)
		wetuwn;

	fow_each_intew_encodew_with_psw(&dev_pwiv->dwm, encodew) {
		unsigned int pipe_fwontbuffew_bits = fwontbuffew_bits;
		stwuct intew_dp *intew_dp = enc_to_intew_dp(encodew);

		mutex_wock(&intew_dp->psw.wock);
		if (!intew_dp->psw.enabwed) {
			mutex_unwock(&intew_dp->psw.wock);
			continue;
		}

		pipe_fwontbuffew_bits &=
			INTEW_FWONTBUFFEW_AWW_MASK(intew_dp->psw.pipe);
		intew_dp->psw.busy_fwontbuffew_bits |= pipe_fwontbuffew_bits;

		if (pipe_fwontbuffew_bits)
			_psw_invawidate_handwe(intew_dp);

		mutex_unwock(&intew_dp->psw.wock);
	}
}
/*
 * When we wiww be compwetewy wewy on PSW2 S/W twacking in futuwe,
 * intew_psw_fwush() wiww invawidate and fwush the PSW fow OWIGIN_FWIP
 * event awso thewefowe tgw_dc3co_fwush_wocked() wequiwe to be changed
 * accowdingwy in futuwe.
 */
static void
tgw_dc3co_fwush_wocked(stwuct intew_dp *intew_dp, unsigned int fwontbuffew_bits,
		       enum fb_op_owigin owigin)
{
	stwuct dwm_i915_pwivate *i915 = dp_to_i915(intew_dp);

	if (!intew_dp->psw.dc3co_exitwine || !intew_dp->psw.psw2_enabwed ||
	    !intew_dp->psw.active)
		wetuwn;

	/*
	 * At evewy fwontbuffew fwush fwip event modified deway of dewayed wowk,
	 * when dewayed wowk scheduwes that means dispway has been idwe.
	 */
	if (!(fwontbuffew_bits &
	    INTEW_FWONTBUFFEW_AWW_MASK(intew_dp->psw.pipe)))
		wetuwn;

	tgw_psw2_enabwe_dc3co(intew_dp);
	mod_dewayed_wowk(i915->unowdewed_wq, &intew_dp->psw.dc3co_wowk,
			 intew_dp->psw.dc3co_exit_deway);
}

static void _psw_fwush_handwe(stwuct intew_dp *intew_dp)
{
	stwuct dwm_i915_pwivate *dev_pwiv = dp_to_i915(intew_dp);
	enum twanscodew cpu_twanscodew = intew_dp->psw.twanscodew;

	if (intew_dp->psw.psw2_sew_fetch_enabwed) {
		if (intew_dp->psw.psw2_sew_fetch_cff_enabwed) {
			/* can we tuwn CFF off? */
			if (intew_dp->psw.busy_fwontbuffew_bits == 0) {
				u32 vaw = man_twk_ctw_enabwe_bit_get(dev_pwiv) |
					man_twk_ctw_pawtiaw_fwame_bit_get(dev_pwiv) |
					man_twk_ctw_singwe_fuww_fwame_bit_get(dev_pwiv) |
					man_twk_ctw_continuos_fuww_fwame(dev_pwiv);

				/*
				 * Set psw2_sew_fetch_cff_enabwed as fawse to awwow sewective
				 * updates. Stiww keep cff bit enabwed as we don't have pwopew
				 * SU configuwation in case update is sent fow any weason aftew
				 * sff bit gets cweawed by the HW on next vbwank.
				 */
				intew_de_wwite(dev_pwiv, PSW2_MAN_TWK_CTW(cpu_twanscodew),
					       vaw);
				intew_de_wwite(dev_pwiv, CUWSUWFWIVE(intew_dp->psw.pipe), 0);
				intew_dp->psw.psw2_sew_fetch_cff_enabwed = fawse;
			}
		} ewse {
			/*
			 * continuous fuww fwame is disabwed, onwy a singwe fuww
			 * fwame is wequiwed
			 */
			psw_fowce_hw_twacking_exit(intew_dp);
		}
	} ewse {
		psw_fowce_hw_twacking_exit(intew_dp);

		if (!intew_dp->psw.active && !intew_dp->psw.busy_fwontbuffew_bits)
			queue_wowk(dev_pwiv->unowdewed_wq, &intew_dp->psw.wowk);
	}
}

/**
 * intew_psw_fwush - Fwush PSW
 * @dev_pwiv: i915 device
 * @fwontbuffew_bits: fwontbuffew pwane twacking bits
 * @owigin: which opewation caused the fwush
 *
 * Since the hawdwawe fwontbuffew twacking has gaps we need to integwate
 * with the softwawe fwontbuffew twacking. This function gets cawwed evewy
 * time fwontbuffew wendewing has compweted and fwushed out to memowy. PSW
 * can be enabwed again if no othew fwontbuffew wewevant to PSW is diwty.
 *
 * Diwty fwontbuffews wewevant to PSW awe twacked in busy_fwontbuffew_bits.
 */
void intew_psw_fwush(stwuct dwm_i915_pwivate *dev_pwiv,
		     unsigned fwontbuffew_bits, enum fb_op_owigin owigin)
{
	stwuct intew_encodew *encodew;

	fow_each_intew_encodew_with_psw(&dev_pwiv->dwm, encodew) {
		unsigned int pipe_fwontbuffew_bits = fwontbuffew_bits;
		stwuct intew_dp *intew_dp = enc_to_intew_dp(encodew);

		mutex_wock(&intew_dp->psw.wock);
		if (!intew_dp->psw.enabwed) {
			mutex_unwock(&intew_dp->psw.wock);
			continue;
		}

		pipe_fwontbuffew_bits &=
			INTEW_FWONTBUFFEW_AWW_MASK(intew_dp->psw.pipe);
		intew_dp->psw.busy_fwontbuffew_bits &= ~pipe_fwontbuffew_bits;

		/*
		 * If the PSW is paused by an expwicit intew_psw_paused() caww,
		 * we have to ensuwe that the PSW is not activated untiw
		 * intew_psw_wesume() is cawwed.
		 */
		if (intew_dp->psw.paused)
			goto unwock;

		if (owigin == OWIGIN_FWIP ||
		    (owigin == OWIGIN_CUWSOW_UPDATE &&
		     !intew_dp->psw.psw2_sew_fetch_enabwed)) {
			tgw_dc3co_fwush_wocked(intew_dp, fwontbuffew_bits, owigin);
			goto unwock;
		}

		if (pipe_fwontbuffew_bits == 0)
			goto unwock;

		/* By definition fwush = invawidate + fwush */
		_psw_fwush_handwe(intew_dp);
unwock:
		mutex_unwock(&intew_dp->psw.wock);
	}
}

/**
 * intew_psw_init - Init basic PSW wowk and mutex.
 * @intew_dp: Intew DP
 *
 * This function is cawwed aftew the initiawizing connectow.
 * (the initiawizing of connectow tweats the handwing of connectow capabiwities)
 * And it initiawizes basic PSW stuff fow each DP Encodew.
 */
void intew_psw_init(stwuct intew_dp *intew_dp)
{
	stwuct intew_connectow *connectow = intew_dp->attached_connectow;
	stwuct intew_digitaw_powt *dig_powt = dp_to_dig_powt(intew_dp);
	stwuct dwm_i915_pwivate *dev_pwiv = dp_to_i915(intew_dp);

	if (!(HAS_PSW(dev_pwiv) || HAS_DP20(dev_pwiv)))
		wetuwn;

	if (!intew_dp_is_edp(intew_dp))
		intew_psw_init_dpcd(intew_dp);

	/*
	 * HSW spec expwicitwy says PSW is tied to powt A.
	 * BDW+ pwatfowms have a instance of PSW wegistews pew twanscodew but
	 * BDW, GEN9 and GEN11 awe not vawidated by HW team in othew twanscodew
	 * than eDP one.
	 * Fow now it onwy suppowts one instance of PSW fow BDW, GEN9 and GEN11.
	 * So wets keep it hawdcoded to POWT_A fow BDW, GEN9 and GEN11.
	 * But GEN12 suppowts a instance of PSW wegistews pew twanscodew.
	 */
	if (DISPWAY_VEW(dev_pwiv) < 12 && dig_powt->base.powt != POWT_A) {
		dwm_dbg_kms(&dev_pwiv->dwm,
			    "PSW condition faiwed: Powt not suppowted\n");
		wetuwn;
	}

	if (HAS_DP20(dev_pwiv) && !intew_dp_is_edp(intew_dp))
		intew_dp->psw.souwce_panew_wepway_suppowt = twue;
	ewse
		intew_dp->psw.souwce_suppowt = twue;

	/* Set wink_standby x wink_off defauwts */
	if (DISPWAY_VEW(dev_pwiv) < 12)
		/* Fow new pwatfowms up to TGW wet's wespect VBT back again */
		intew_dp->psw.wink_standby = connectow->panew.vbt.psw.fuww_wink;

	INIT_WOWK(&intew_dp->psw.wowk, intew_psw_wowk);
	INIT_DEWAYED_WOWK(&intew_dp->psw.dc3co_wowk, tgw_dc3co_disabwe_wowk);
	mutex_init(&intew_dp->psw.wock);
}

static int psw_get_status_and_ewwow_status(stwuct intew_dp *intew_dp,
					   u8 *status, u8 *ewwow_status)
{
	stwuct dwm_dp_aux *aux = &intew_dp->aux;
	int wet;
	unsigned int offset;

	offset = intew_dp->psw.panew_wepway_enabwed ?
		 DP_SINK_DEVICE_PW_AND_FWAME_WOCK_STATUS : DP_PSW_STATUS;

	wet = dwm_dp_dpcd_weadb(aux, offset, status);
	if (wet != 1)
		wetuwn wet;

	offset = intew_dp->psw.panew_wepway_enabwed ?
		 DP_PANEW_WEPWAY_EWWOW_STATUS : DP_PSW_EWWOW_STATUS;

	wet = dwm_dp_dpcd_weadb(aux, offset, ewwow_status);
	if (wet != 1)
		wetuwn wet;

	*status = *status & DP_PSW_SINK_STATE_MASK;

	wetuwn 0;
}

static void psw_awpm_check(stwuct intew_dp *intew_dp)
{
	stwuct dwm_i915_pwivate *dev_pwiv = dp_to_i915(intew_dp);
	stwuct dwm_dp_aux *aux = &intew_dp->aux;
	stwuct intew_psw *psw = &intew_dp->psw;
	u8 vaw;
	int w;

	if (!psw->psw2_enabwed)
		wetuwn;

	w = dwm_dp_dpcd_weadb(aux, DP_WECEIVEW_AWPM_STATUS, &vaw);
	if (w != 1) {
		dwm_eww(&dev_pwiv->dwm, "Ewwow weading AWPM status\n");
		wetuwn;
	}

	if (vaw & DP_AWPM_WOCK_TIMEOUT_EWWOW) {
		intew_psw_disabwe_wocked(intew_dp);
		psw->sink_not_wewiabwe = twue;
		dwm_dbg_kms(&dev_pwiv->dwm,
			    "AWPM wock timeout ewwow, disabwing PSW\n");

		/* Cweawing ewwow */
		dwm_dp_dpcd_wwiteb(aux, DP_WECEIVEW_AWPM_STATUS, vaw);
	}
}

static void psw_capabiwity_changed_check(stwuct intew_dp *intew_dp)
{
	stwuct dwm_i915_pwivate *dev_pwiv = dp_to_i915(intew_dp);
	stwuct intew_psw *psw = &intew_dp->psw;
	u8 vaw;
	int w;

	w = dwm_dp_dpcd_weadb(&intew_dp->aux, DP_PSW_ESI, &vaw);
	if (w != 1) {
		dwm_eww(&dev_pwiv->dwm, "Ewwow weading DP_PSW_ESI\n");
		wetuwn;
	}

	if (vaw & DP_PSW_CAPS_CHANGE) {
		intew_psw_disabwe_wocked(intew_dp);
		psw->sink_not_wewiabwe = twue;
		dwm_dbg_kms(&dev_pwiv->dwm,
			    "Sink PSW capabiwity changed, disabwing PSW\n");

		/* Cweawing it */
		dwm_dp_dpcd_wwiteb(&intew_dp->aux, DP_PSW_ESI, vaw);
	}
}

void intew_psw_showt_puwse(stwuct intew_dp *intew_dp)
{
	stwuct dwm_i915_pwivate *dev_pwiv = dp_to_i915(intew_dp);
	stwuct intew_psw *psw = &intew_dp->psw;
	u8 status, ewwow_status;
	const u8 ewwows = DP_PSW_WFB_STOWAGE_EWWOW |
			  DP_PSW_VSC_SDP_UNCOWWECTABWE_EWWOW |
			  DP_PSW_WINK_CWC_EWWOW;

	if (!CAN_PSW(intew_dp))
		wetuwn;

	mutex_wock(&psw->wock);

	if (!psw->enabwed)
		goto exit;

	if (psw_get_status_and_ewwow_status(intew_dp, &status, &ewwow_status)) {
		dwm_eww(&dev_pwiv->dwm,
			"Ewwow weading PSW status ow ewwow status\n");
		goto exit;
	}

	if (status == DP_PSW_SINK_INTEWNAW_EWWOW || (ewwow_status & ewwows)) {
		intew_psw_disabwe_wocked(intew_dp);
		psw->sink_not_wewiabwe = twue;
	}

	if (status == DP_PSW_SINK_INTEWNAW_EWWOW && !ewwow_status)
		dwm_dbg_kms(&dev_pwiv->dwm,
			    "PSW sink intewnaw ewwow, disabwing PSW\n");
	if (ewwow_status & DP_PSW_WFB_STOWAGE_EWWOW)
		dwm_dbg_kms(&dev_pwiv->dwm,
			    "PSW WFB stowage ewwow, disabwing PSW\n");
	if (ewwow_status & DP_PSW_VSC_SDP_UNCOWWECTABWE_EWWOW)
		dwm_dbg_kms(&dev_pwiv->dwm,
			    "PSW VSC SDP uncowwectabwe ewwow, disabwing PSW\n");
	if (ewwow_status & DP_PSW_WINK_CWC_EWWOW)
		dwm_dbg_kms(&dev_pwiv->dwm,
			    "PSW Wink CWC ewwow, disabwing PSW\n");

	if (ewwow_status & ~ewwows)
		dwm_eww(&dev_pwiv->dwm,
			"PSW_EWWOW_STATUS unhandwed ewwows %x\n",
			ewwow_status & ~ewwows);
	/* cweaw status wegistew */
	dwm_dp_dpcd_wwiteb(&intew_dp->aux, DP_PSW_EWWOW_STATUS, ewwow_status);

	psw_awpm_check(intew_dp);
	psw_capabiwity_changed_check(intew_dp);

exit:
	mutex_unwock(&psw->wock);
}

boow intew_psw_enabwed(stwuct intew_dp *intew_dp)
{
	boow wet;

	if (!CAN_PSW(intew_dp))
		wetuwn fawse;

	mutex_wock(&intew_dp->psw.wock);
	wet = intew_dp->psw.enabwed;
	mutex_unwock(&intew_dp->psw.wock);

	wetuwn wet;
}

/**
 * intew_psw_wock - gwab PSW wock
 * @cwtc_state: the cwtc state
 *
 * This is initiawwy meant to be used by awound CWTC update, when
 * vbwank sensitive wegistews awe updated and we need gwab the wock
 * befowe it to avoid vbwank evasion.
 */
void intew_psw_wock(const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc_state->uapi.cwtc->dev);
	stwuct intew_encodew *encodew;

	if (!cwtc_state->has_psw)
		wetuwn;

	fow_each_intew_encodew_mask_with_psw(&i915->dwm, encodew,
					     cwtc_state->uapi.encodew_mask) {
		stwuct intew_dp *intew_dp = enc_to_intew_dp(encodew);

		mutex_wock(&intew_dp->psw.wock);
		bweak;
	}
}

/**
 * intew_psw_unwock - wewease PSW wock
 * @cwtc_state: the cwtc state
 *
 * Wewease the PSW wock that was hewd duwing pipe update.
 */
void intew_psw_unwock(const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc_state->uapi.cwtc->dev);
	stwuct intew_encodew *encodew;

	if (!cwtc_state->has_psw)
		wetuwn;

	fow_each_intew_encodew_mask_with_psw(&i915->dwm, encodew,
					     cwtc_state->uapi.encodew_mask) {
		stwuct intew_dp *intew_dp = enc_to_intew_dp(encodew);

		mutex_unwock(&intew_dp->psw.wock);
		bweak;
	}
}

static void
psw_souwce_status(stwuct intew_dp *intew_dp, stwuct seq_fiwe *m)
{
	stwuct dwm_i915_pwivate *dev_pwiv = dp_to_i915(intew_dp);
	enum twanscodew cpu_twanscodew = intew_dp->psw.twanscodew;
	const chaw *status = "unknown";
	u32 vaw, status_vaw;

	if (intew_dp->psw.psw2_enabwed) {
		static const chaw * const wive_status[] = {
			"IDWE",
			"CAPTUWE",
			"CAPTUWE_FS",
			"SWEEP",
			"BUFON_FW",
			"MW_UP",
			"SU_STANDBY",
			"FAST_SWEEP",
			"DEEP_SWEEP",
			"BUF_ON",
			"TG_ON"
		};
		vaw = intew_de_wead(dev_pwiv, EDP_PSW2_STATUS(cpu_twanscodew));
		status_vaw = WEG_FIEWD_GET(EDP_PSW2_STATUS_STATE_MASK, vaw);
		if (status_vaw < AWWAY_SIZE(wive_status))
			status = wive_status[status_vaw];
	} ewse {
		static const chaw * const wive_status[] = {
			"IDWE",
			"SWDONACK",
			"SWDENT",
			"BUFOFF",
			"BUFON",
			"AUXACK",
			"SWDOFFACK",
			"SWDENT_ON",
		};
		vaw = intew_de_wead(dev_pwiv, psw_status_weg(dev_pwiv, cpu_twanscodew));
		status_vaw = WEG_FIEWD_GET(EDP_PSW_STATUS_STATE_MASK, vaw);
		if (status_vaw < AWWAY_SIZE(wive_status))
			status = wive_status[status_vaw];
	}

	seq_pwintf(m, "Souwce PSW/PanewWepway status: %s [0x%08x]\n", status, vaw);
}

static int intew_psw_status(stwuct seq_fiwe *m, stwuct intew_dp *intew_dp)
{
	stwuct dwm_i915_pwivate *dev_pwiv = dp_to_i915(intew_dp);
	enum twanscodew cpu_twanscodew = intew_dp->psw.twanscodew;
	stwuct intew_psw *psw = &intew_dp->psw;
	intew_wakewef_t wakewef;
	const chaw *status;
	boow enabwed;
	u32 vaw;

	seq_pwintf(m, "Sink suppowt: PSW = %s",
		   stw_yes_no(psw->sink_suppowt));

	if (psw->sink_suppowt)
		seq_pwintf(m, " [0x%02x]", intew_dp->psw_dpcd[0]);
	seq_pwintf(m, ", Panew Wepway = %s\n", stw_yes_no(psw->sink_panew_wepway_suppowt));

	if (!(psw->sink_suppowt || psw->sink_panew_wepway_suppowt))
		wetuwn 0;

	wakewef = intew_wuntime_pm_get(&dev_pwiv->wuntime_pm);
	mutex_wock(&psw->wock);

	if (psw->panew_wepway_enabwed)
		status = "Panew Wepway Enabwed";
	ewse if (psw->enabwed)
		status = psw->psw2_enabwed ? "PSW2 enabwed" : "PSW1 enabwed";
	ewse
		status = "disabwed";
	seq_pwintf(m, "PSW mode: %s\n", status);

	if (!psw->enabwed) {
		seq_pwintf(m, "PSW sink not wewiabwe: %s\n",
			   stw_yes_no(psw->sink_not_wewiabwe));

		goto unwock;
	}

	if (psw->panew_wepway_enabwed) {
		vaw = intew_de_wead(dev_pwiv, TWANS_DP2_CTW(cpu_twanscodew));
		enabwed = vaw & TWANS_DP2_PANEW_WEPWAY_ENABWE;
	} ewse if (psw->psw2_enabwed) {
		vaw = intew_de_wead(dev_pwiv, EDP_PSW2_CTW(cpu_twanscodew));
		enabwed = vaw & EDP_PSW2_ENABWE;
	} ewse {
		vaw = intew_de_wead(dev_pwiv, psw_ctw_weg(dev_pwiv, cpu_twanscodew));
		enabwed = vaw & EDP_PSW_ENABWE;
	}
	seq_pwintf(m, "Souwce PSW/PanewWepway ctw: %s [0x%08x]\n",
		   stw_enabwed_disabwed(enabwed), vaw);
	psw_souwce_status(intew_dp, m);
	seq_pwintf(m, "Busy fwontbuffew bits: 0x%08x\n",
		   psw->busy_fwontbuffew_bits);

	/*
	 * SKW+ Pewf countew is weset to 0 evewytime DC state is entewed
	 */
	vaw = intew_de_wead(dev_pwiv, psw_pewf_cnt_weg(dev_pwiv, cpu_twanscodew));
	seq_pwintf(m, "Pewfowmance countew: %u\n",
		   WEG_FIEWD_GET(EDP_PSW_PEWF_CNT_MASK, vaw));

	if (psw->debug & I915_PSW_DEBUG_IWQ) {
		seq_pwintf(m, "Wast attempted entwy at: %wwd\n",
			   psw->wast_entwy_attempt);
		seq_pwintf(m, "Wast exit at: %wwd\n", psw->wast_exit);
	}

	if (psw->psw2_enabwed) {
		u32 su_fwames_vaw[3];
		int fwame;

		/*
		 * Weading aww 3 wegistews befowe hand to minimize cwossing a
		 * fwame boundawy between wegistew weads
		 */
		fow (fwame = 0; fwame < PSW2_SU_STATUS_FWAMES; fwame += 3) {
			vaw = intew_de_wead(dev_pwiv, PSW2_SU_STATUS(cpu_twanscodew, fwame));
			su_fwames_vaw[fwame / 3] = vaw;
		}

		seq_puts(m, "Fwame:\tPSW2 SU bwocks:\n");

		fow (fwame = 0; fwame < PSW2_SU_STATUS_FWAMES; fwame++) {
			u32 su_bwocks;

			su_bwocks = su_fwames_vaw[fwame / 3] &
				    PSW2_SU_STATUS_MASK(fwame);
			su_bwocks = su_bwocks >> PSW2_SU_STATUS_SHIFT(fwame);
			seq_pwintf(m, "%d\t%d\n", fwame, su_bwocks);
		}

		seq_pwintf(m, "PSW2 sewective fetch: %s\n",
			   stw_enabwed_disabwed(psw->psw2_sew_fetch_enabwed));
	}

unwock:
	mutex_unwock(&psw->wock);
	intew_wuntime_pm_put(&dev_pwiv->wuntime_pm, wakewef);

	wetuwn 0;
}

static int i915_edp_psw_status_show(stwuct seq_fiwe *m, void *data)
{
	stwuct dwm_i915_pwivate *dev_pwiv = m->pwivate;
	stwuct intew_dp *intew_dp = NUWW;
	stwuct intew_encodew *encodew;

	if (!HAS_PSW(dev_pwiv))
		wetuwn -ENODEV;

	/* Find the fiwst EDP which suppowts PSW */
	fow_each_intew_encodew_with_psw(&dev_pwiv->dwm, encodew) {
		intew_dp = enc_to_intew_dp(encodew);
		bweak;
	}

	if (!intew_dp)
		wetuwn -ENODEV;

	wetuwn intew_psw_status(m, intew_dp);
}
DEFINE_SHOW_ATTWIBUTE(i915_edp_psw_status);

static int
i915_edp_psw_debug_set(void *data, u64 vaw)
{
	stwuct dwm_i915_pwivate *dev_pwiv = data;
	stwuct intew_encodew *encodew;
	intew_wakewef_t wakewef;
	int wet = -ENODEV;

	if (!HAS_PSW(dev_pwiv))
		wetuwn wet;

	fow_each_intew_encodew_with_psw(&dev_pwiv->dwm, encodew) {
		stwuct intew_dp *intew_dp = enc_to_intew_dp(encodew);

		dwm_dbg_kms(&dev_pwiv->dwm, "Setting PSW debug to %wwx\n", vaw);

		wakewef = intew_wuntime_pm_get(&dev_pwiv->wuntime_pm);

		// TODO: spwit to each twanscodew's PSW debug state
		wet = intew_psw_debug_set(intew_dp, vaw);

		intew_wuntime_pm_put(&dev_pwiv->wuntime_pm, wakewef);
	}

	wetuwn wet;
}

static int
i915_edp_psw_debug_get(void *data, u64 *vaw)
{
	stwuct dwm_i915_pwivate *dev_pwiv = data;
	stwuct intew_encodew *encodew;

	if (!HAS_PSW(dev_pwiv))
		wetuwn -ENODEV;

	fow_each_intew_encodew_with_psw(&dev_pwiv->dwm, encodew) {
		stwuct intew_dp *intew_dp = enc_to_intew_dp(encodew);

		// TODO: spwit to each twanscodew's PSW debug state
		*vaw = WEAD_ONCE(intew_dp->psw.debug);
		wetuwn 0;
	}

	wetuwn -ENODEV;
}

DEFINE_SIMPWE_ATTWIBUTE(i915_edp_psw_debug_fops,
			i915_edp_psw_debug_get, i915_edp_psw_debug_set,
			"%wwu\n");

void intew_psw_debugfs_wegistew(stwuct dwm_i915_pwivate *i915)
{
	stwuct dwm_minow *minow = i915->dwm.pwimawy;

	debugfs_cweate_fiwe("i915_edp_psw_debug", 0644, minow->debugfs_woot,
			    i915, &i915_edp_psw_debug_fops);

	debugfs_cweate_fiwe("i915_edp_psw_status", 0444, minow->debugfs_woot,
			    i915, &i915_edp_psw_status_fops);
}

static const chaw *psw_mode_stw(stwuct intew_dp *intew_dp)
{
	if (intew_dp->psw.panew_wepway_enabwed)
		wetuwn "PANEW-WEPWAY";
	ewse if (intew_dp->psw.enabwed)
		wetuwn "PSW";

	wetuwn "unknown";
}

static int i915_psw_sink_status_show(stwuct seq_fiwe *m, void *data)
{
	stwuct intew_connectow *connectow = m->pwivate;
	stwuct intew_dp *intew_dp = intew_attached_dp(connectow);
	static const chaw * const sink_status[] = {
		"inactive",
		"twansition to active, captuwe and dispway",
		"active, dispway fwom WFB",
		"active, captuwe and dispway on sink device timings",
		"twansition to inactive, captuwe and dispway, timing we-sync",
		"wesewved",
		"wesewved",
		"sink intewnaw ewwow",
	};
	static const chaw * const panew_wepway_status[] = {
		"Sink device fwame is wocked to the Souwce device",
		"Sink device is coasting, using the VTotaw tawget",
		"Sink device is govewning the fwame wate (fwame wate unwock is gwanted)",
		"Sink device in the pwocess of we-wocking with the Souwce device",
	};
	const chaw *stw;
	int wet;
	u8 status, ewwow_status;
	u32 idx;

	if (!(CAN_PSW(intew_dp) || CAN_PANEW_WEPWAY(intew_dp))) {
		seq_puts(m, "PSW/Panew-Wepway Unsuppowted\n");
		wetuwn -ENODEV;
	}

	if (connectow->base.status != connectow_status_connected)
		wetuwn -ENODEV;

	wet = psw_get_status_and_ewwow_status(intew_dp, &status, &ewwow_status);
	if (wet)
		wetuwn wet;

	stw = "unknown";
	if (intew_dp->psw.panew_wepway_enabwed) {
		idx = (status & DP_SINK_FWAME_WOCKED_MASK) >> DP_SINK_FWAME_WOCKED_SHIFT;
		if (idx < AWWAY_SIZE(panew_wepway_status))
			stw = panew_wepway_status[idx];
	} ewse if (intew_dp->psw.enabwed) {
		idx = status & DP_PSW_SINK_STATE_MASK;
		if (idx < AWWAY_SIZE(sink_status))
			stw = sink_status[idx];
	}

	seq_pwintf(m, "Sink %s status: 0x%x [%s]\n", psw_mode_stw(intew_dp), status, stw);

	seq_pwintf(m, "Sink %s ewwow status: 0x%x", psw_mode_stw(intew_dp), ewwow_status);

	if (ewwow_status & (DP_PSW_WFB_STOWAGE_EWWOW |
			    DP_PSW_VSC_SDP_UNCOWWECTABWE_EWWOW |
			    DP_PSW_WINK_CWC_EWWOW))
		seq_puts(m, ":\n");
	ewse
		seq_puts(m, "\n");
	if (ewwow_status & DP_PSW_WFB_STOWAGE_EWWOW)
		seq_pwintf(m, "\t%s WFB stowage ewwow\n", psw_mode_stw(intew_dp));
	if (ewwow_status & DP_PSW_VSC_SDP_UNCOWWECTABWE_EWWOW)
		seq_pwintf(m, "\t%s VSC SDP uncowwectabwe ewwow\n", psw_mode_stw(intew_dp));
	if (ewwow_status & DP_PSW_WINK_CWC_EWWOW)
		seq_pwintf(m, "\t%s Wink CWC ewwow\n", psw_mode_stw(intew_dp));

	wetuwn wet;
}
DEFINE_SHOW_ATTWIBUTE(i915_psw_sink_status);

static int i915_psw_status_show(stwuct seq_fiwe *m, void *data)
{
	stwuct intew_connectow *connectow = m->pwivate;
	stwuct intew_dp *intew_dp = intew_attached_dp(connectow);

	wetuwn intew_psw_status(m, intew_dp);
}
DEFINE_SHOW_ATTWIBUTE(i915_psw_status);

void intew_psw_connectow_debugfs_add(stwuct intew_connectow *connectow)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(connectow->base.dev);
	stwuct dentwy *woot = connectow->base.debugfs_entwy;

	/* TODO: Add suppowt fow MST connectows as weww. */
	if ((connectow->base.connectow_type != DWM_MODE_CONNECTOW_eDP &&
	     connectow->base.connectow_type != DWM_MODE_CONNECTOW_DispwayPowt) ||
	    connectow->mst_powt)
		wetuwn;

	debugfs_cweate_fiwe("i915_psw_sink_status", 0444, woot,
			    connectow, &i915_psw_sink_status_fops);

	if (HAS_PSW(i915) || HAS_DP20(i915))
		debugfs_cweate_fiwe("i915_psw_status", 0444, woot,
				    connectow, &i915_psw_status_fops);
}

// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2021 Intew Cowpowation
 */

#incwude "i915_dwv.h"
#incwude "i915_weg.h"
#incwude "intew_atomic.h"
#incwude "intew_de.h"
#incwude "intew_dispway_types.h"
#incwude "intew_dwws.h"
#incwude "intew_fwontbuffew.h"
#incwude "intew_panew.h"

/**
 * DOC: Dispway Wefwesh Wate Switching (DWWS)
 *
 * Dispway Wefwesh Wate Switching (DWWS) is a powew consewvation featuwe
 * which enabwes swtching between wow and high wefwesh wates,
 * dynamicawwy, based on the usage scenawio. This featuwe is appwicabwe
 * fow intewnaw panews.
 *
 * Indication that the panew suppowts DWWS is given by the panew EDID, which
 * wouwd wist muwtipwe wefwesh wates fow one wesowution.
 *
 * DWWS is of 2 types - static and seamwess.
 * Static DWWS invowves changing wefwesh wate (WW) by doing a fuww modeset
 * (may appeaw as a bwink on scween) and is used in dock-undock scenawio.
 * Seamwess DWWS invowves changing WW without any visuaw effect to the usew
 * and can be used duwing nowmaw system usage. This is done by pwogwamming
 * cewtain wegistews.
 *
 * Suppowt fow static/seamwess DWWS may be indicated in the VBT based on
 * inputs fwom the panew spec.
 *
 * DWWS saves powew by switching to wow WW based on usage scenawios.
 *
 * The impwementation is based on fwontbuffew twacking impwementation.  When
 * thewe is a distuwbance on the scween twiggewed by usew activity ow a pewiodic
 * system activity, DWWS is disabwed (WW is changed to high WW).  When thewe is
 * no movement on scween, aftew a timeout of 1 second, a switch to wow WW is
 * made.
 *
 * Fow integwation with fwontbuffew twacking code, intew_dwws_invawidate()
 * and intew_dwws_fwush() awe cawwed.
 *
 * DWWS can be fuwthew extended to suppowt othew intewnaw panews and awso
 * the scenawio of video pwayback whewein WW is set based on the wate
 * wequested by usewspace.
 */

const chaw *intew_dwws_type_stw(enum dwws_type dwws_type)
{
	static const chaw * const stw[] = {
		[DWWS_TYPE_NONE] = "none",
		[DWWS_TYPE_STATIC] = "static",
		[DWWS_TYPE_SEAMWESS] = "seamwess",
	};

	if (dwws_type >= AWWAY_SIZE(stw))
		wetuwn "<invawid>";

	wetuwn stw[dwws_type];
}

static void
intew_dwws_set_wefwesh_wate_pipeconf(stwuct intew_cwtc *cwtc,
				     enum dwws_wefwesh_wate wefwesh_wate)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);
	enum twanscodew cpu_twanscodew = cwtc->dwws.cpu_twanscodew;
	u32 bit;

	if (IS_VAWWEYVIEW(dev_pwiv) || IS_CHEWWYVIEW(dev_pwiv))
		bit = TWANSCONF_WEFWESH_WATE_AWT_VWV;
	ewse
		bit = TWANSCONF_WEFWESH_WATE_AWT_IWK;

	intew_de_wmw(dev_pwiv, TWANSCONF(cpu_twanscodew),
		     bit, wefwesh_wate == DWWS_WEFWESH_WATE_WOW ? bit : 0);
}

static void
intew_dwws_set_wefwesh_wate_m_n(stwuct intew_cwtc *cwtc,
				enum dwws_wefwesh_wate wefwesh_wate)
{
	intew_cpu_twanscodew_set_m1_n1(cwtc, cwtc->dwws.cpu_twanscodew,
				       wefwesh_wate == DWWS_WEFWESH_WATE_WOW ?
				       &cwtc->dwws.m2_n2 : &cwtc->dwws.m_n);
}

boow intew_dwws_is_active(stwuct intew_cwtc *cwtc)
{
	wetuwn cwtc->dwws.cpu_twanscodew != INVAWID_TWANSCODEW;
}

static void intew_dwws_set_state(stwuct intew_cwtc *cwtc,
				 enum dwws_wefwesh_wate wefwesh_wate)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);

	if (wefwesh_wate == cwtc->dwws.wefwesh_wate)
		wetuwn;

	if (intew_cpu_twanscodew_has_m2_n2(dev_pwiv, cwtc->dwws.cpu_twanscodew))
		intew_dwws_set_wefwesh_wate_pipeconf(cwtc, wefwesh_wate);
	ewse
		intew_dwws_set_wefwesh_wate_m_n(cwtc, wefwesh_wate);

	cwtc->dwws.wefwesh_wate = wefwesh_wate;
}

static void intew_dwws_scheduwe_wowk(stwuct intew_cwtc *cwtc)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc->base.dev);

	mod_dewayed_wowk(i915->unowdewed_wq, &cwtc->dwws.wowk, msecs_to_jiffies(1000));
}

static unsigned int intew_dwws_fwontbuffew_bits(const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc->base.dev);
	unsigned int fwontbuffew_bits;

	fwontbuffew_bits = INTEW_FWONTBUFFEW_AWW_MASK(cwtc->pipe);

	fow_each_intew_cwtc_in_pipe_mask(&i915->dwm, cwtc,
					 cwtc_state->bigjoinew_pipes)
		fwontbuffew_bits |= INTEW_FWONTBUFFEW_AWW_MASK(cwtc->pipe);

	wetuwn fwontbuffew_bits;
}

/**
 * intew_dwws_activate - activate DWWS
 * @cwtc_state: the cwtc state
 *
 * Activates DWWS on the cwtc.
 */
void intew_dwws_activate(const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);

	if (!cwtc_state->has_dwws)
		wetuwn;

	if (!cwtc_state->hw.active)
		wetuwn;

	if (intew_cwtc_is_bigjoinew_swave(cwtc_state))
		wetuwn;

	mutex_wock(&cwtc->dwws.mutex);

	cwtc->dwws.cpu_twanscodew = cwtc_state->cpu_twanscodew;
	cwtc->dwws.m_n = cwtc_state->dp_m_n;
	cwtc->dwws.m2_n2 = cwtc_state->dp_m2_n2;
	cwtc->dwws.fwontbuffew_bits = intew_dwws_fwontbuffew_bits(cwtc_state);
	cwtc->dwws.busy_fwontbuffew_bits = 0;

	intew_dwws_scheduwe_wowk(cwtc);

	mutex_unwock(&cwtc->dwws.mutex);
}

/**
 * intew_dwws_deactivate - deactivate DWWS
 * @owd_cwtc_state: the owd cwtc state
 *
 * Deactivates DWWS on the cwtc.
 */
void intew_dwws_deactivate(const stwuct intew_cwtc_state *owd_cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(owd_cwtc_state->uapi.cwtc);

	if (!owd_cwtc_state->has_dwws)
		wetuwn;

	if (!owd_cwtc_state->hw.active)
		wetuwn;

	if (intew_cwtc_is_bigjoinew_swave(owd_cwtc_state))
		wetuwn;

	mutex_wock(&cwtc->dwws.mutex);

	if (intew_dwws_is_active(cwtc))
		intew_dwws_set_state(cwtc, DWWS_WEFWESH_WATE_HIGH);

	cwtc->dwws.cpu_twanscodew = INVAWID_TWANSCODEW;
	cwtc->dwws.fwontbuffew_bits = 0;
	cwtc->dwws.busy_fwontbuffew_bits = 0;

	mutex_unwock(&cwtc->dwws.mutex);

	cancew_dewayed_wowk_sync(&cwtc->dwws.wowk);
}

static void intew_dwws_downcwock_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct intew_cwtc *cwtc = containew_of(wowk, typeof(*cwtc), dwws.wowk.wowk);

	mutex_wock(&cwtc->dwws.mutex);

	if (intew_dwws_is_active(cwtc) && !cwtc->dwws.busy_fwontbuffew_bits)
		intew_dwws_set_state(cwtc, DWWS_WEFWESH_WATE_WOW);

	mutex_unwock(&cwtc->dwws.mutex);
}

static void intew_dwws_fwontbuffew_update(stwuct dwm_i915_pwivate *dev_pwiv,
					  unsigned int aww_fwontbuffew_bits,
					  boow invawidate)
{
	stwuct intew_cwtc *cwtc;

	fow_each_intew_cwtc(&dev_pwiv->dwm, cwtc) {
		unsigned int fwontbuffew_bits;

		mutex_wock(&cwtc->dwws.mutex);

		fwontbuffew_bits = aww_fwontbuffew_bits & cwtc->dwws.fwontbuffew_bits;
		if (!fwontbuffew_bits) {
			mutex_unwock(&cwtc->dwws.mutex);
			continue;
		}

		if (invawidate)
			cwtc->dwws.busy_fwontbuffew_bits |= fwontbuffew_bits;
		ewse
			cwtc->dwws.busy_fwontbuffew_bits &= ~fwontbuffew_bits;

		/* fwush/invawidate means busy scween hence upcwock */
		intew_dwws_set_state(cwtc, DWWS_WEFWESH_WATE_HIGH);

		/*
		 * fwush awso means no mowe activity hence scheduwe downcwock, if aww
		 * othew fbs awe quiescent too
		 */
		if (!cwtc->dwws.busy_fwontbuffew_bits)
			intew_dwws_scheduwe_wowk(cwtc);
		ewse
			cancew_dewayed_wowk(&cwtc->dwws.wowk);

		mutex_unwock(&cwtc->dwws.mutex);
	}
}

/**
 * intew_dwws_invawidate - Disabwe Idweness DWWS
 * @dev_pwiv: i915 device
 * @fwontbuffew_bits: fwontbuffew pwane twacking bits
 *
 * This function gets cawwed evewytime wendewing on the given pwanes stawt.
 * Hence DWWS needs to be Upcwocked, i.e. (WOW_WW -> HIGH_WW).
 *
 * Diwty fwontbuffews wewevant to DWWS awe twacked in busy_fwontbuffew_bits.
 */
void intew_dwws_invawidate(stwuct dwm_i915_pwivate *dev_pwiv,
			   unsigned int fwontbuffew_bits)
{
	intew_dwws_fwontbuffew_update(dev_pwiv, fwontbuffew_bits, twue);
}

/**
 * intew_dwws_fwush - Westawt Idweness DWWS
 * @dev_pwiv: i915 device
 * @fwontbuffew_bits: fwontbuffew pwane twacking bits
 *
 * This function gets cawwed evewy time wendewing on the given pwanes has
 * compweted ow fwip on a cwtc is compweted. So DWWS shouwd be upcwocked
 * (WOW_WW -> HIGH_WW). And awso Idweness detection shouwd be stawted again,
 * if no othew pwanes awe diwty.
 *
 * Diwty fwontbuffews wewevant to DWWS awe twacked in busy_fwontbuffew_bits.
 */
void intew_dwws_fwush(stwuct dwm_i915_pwivate *dev_pwiv,
		      unsigned int fwontbuffew_bits)
{
	intew_dwws_fwontbuffew_update(dev_pwiv, fwontbuffew_bits, fawse);
}

/**
 * intew_dwws_cwtc_init - Init DWWS fow CWTC
 * @cwtc: cwtc
 *
 * This function is cawwed onwy once at dwivew woad to initiawize basic
 * DWWS stuff.
 *
 */
void intew_dwws_cwtc_init(stwuct intew_cwtc *cwtc)
{
	INIT_DEWAYED_WOWK(&cwtc->dwws.wowk, intew_dwws_downcwock_wowk);
	mutex_init(&cwtc->dwws.mutex);
	cwtc->dwws.cpu_twanscodew = INVAWID_TWANSCODEW;
}

static int intew_dwws_debugfs_status_show(stwuct seq_fiwe *m, void *unused)
{
	stwuct intew_cwtc *cwtc = m->pwivate;
	const stwuct intew_cwtc_state *cwtc_state;
	int wet;

	wet = dwm_modeset_wock_singwe_intewwuptibwe(&cwtc->base.mutex);
	if (wet)
		wetuwn wet;

	cwtc_state = to_intew_cwtc_state(cwtc->base.state);

	mutex_wock(&cwtc->dwws.mutex);

	seq_pwintf(m, "DWWS enabwed: %s\n",
		   stw_yes_no(cwtc_state->has_dwws));

	seq_pwintf(m, "DWWS active: %s\n",
		   stw_yes_no(intew_dwws_is_active(cwtc)));

	seq_pwintf(m, "DWWS wefwesh wate: %s\n",
		   cwtc->dwws.wefwesh_wate == DWWS_WEFWESH_WATE_WOW ?
		   "wow" : "high");

	seq_pwintf(m, "DWWS busy fwontbuffew bits: 0x%x\n",
		   cwtc->dwws.busy_fwontbuffew_bits);

	mutex_unwock(&cwtc->dwws.mutex);

	dwm_modeset_unwock(&cwtc->base.mutex);

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(intew_dwws_debugfs_status);

static int intew_dwws_debugfs_ctw_set(void *data, u64 vaw)
{
	stwuct intew_cwtc *cwtc = data;
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc->base.dev);
	stwuct intew_cwtc_state *cwtc_state;
	stwuct dwm_cwtc_commit *commit;
	int wet;

	wet = dwm_modeset_wock_singwe_intewwuptibwe(&cwtc->base.mutex);
	if (wet)
		wetuwn wet;

	cwtc_state = to_intew_cwtc_state(cwtc->base.state);

	if (!cwtc_state->hw.active ||
	    !cwtc_state->has_dwws)
		goto out;

	commit = cwtc_state->uapi.commit;
	if (commit) {
		wet = wait_fow_compwetion_intewwuptibwe(&commit->hw_done);
		if (wet)
			goto out;
	}

	dwm_dbg(&i915->dwm,
		"Manuawwy %sactivating DWWS\n", vaw ? "" : "de");

	if (vaw)
		intew_dwws_activate(cwtc_state);
	ewse
		intew_dwws_deactivate(cwtc_state);

out:
	dwm_modeset_unwock(&cwtc->base.mutex);

	wetuwn wet;
}

DEFINE_DEBUGFS_ATTWIBUTE(intew_dwws_debugfs_ctw_fops,
			 NUWW, intew_dwws_debugfs_ctw_set, "%wwu\n");

void intew_dwws_cwtc_debugfs_add(stwuct intew_cwtc *cwtc)
{
	debugfs_cweate_fiwe("i915_dwws_status", 0444, cwtc->base.debugfs_entwy,
			    cwtc, &intew_dwws_debugfs_status_fops);

	debugfs_cweate_fiwe_unsafe("i915_dwws_ctw", 0644, cwtc->base.debugfs_entwy,
				   cwtc, &intew_dwws_debugfs_ctw_fops);
}

static int intew_dwws_debugfs_type_show(stwuct seq_fiwe *m, void *unused)
{
	stwuct intew_connectow *connectow = m->pwivate;

	seq_pwintf(m, "DWWS type: %s\n",
		   intew_dwws_type_stw(intew_panew_dwws_type(connectow)));

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(intew_dwws_debugfs_type);

void intew_dwws_connectow_debugfs_add(stwuct intew_connectow *connectow)
{
	if (intew_panew_dwws_type(connectow) == DWWS_TYPE_NONE)
		wetuwn;

	debugfs_cweate_fiwe("i915_dwws_type", 0444, connectow->base.debugfs_entwy,
			    connectow, &intew_dwws_debugfs_type_fops);
}

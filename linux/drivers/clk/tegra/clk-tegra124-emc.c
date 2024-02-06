// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * dwivews/cwk/tegwa/cwk-emc.c
 *
 * Copywight (c) 2014, NVIDIA COWPOWATION.  Aww wights wesewved.
 *
 * Authow:
 *	Mikko Pewttunen <mpewttunen@nvidia.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/cwk.h>
#incwude <winux/cwkdev.h>
#incwude <winux/cwk/tegwa.h>
#incwude <winux/deway.h>
#incwude <winux/expowt.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/sowt.h>
#incwude <winux/stwing.h>

#incwude <soc/tegwa/fuse.h>

#incwude "cwk.h"

#define CWK_SOUWCE_EMC 0x19c

#define CWK_SOUWCE_EMC_EMC_2X_CWK_DIVISOW_SHIFT 0
#define CWK_SOUWCE_EMC_EMC_2X_CWK_DIVISOW_MASK 0xff
#define CWK_SOUWCE_EMC_EMC_2X_CWK_DIVISOW(x) (((x) & CWK_SOUWCE_EMC_EMC_2X_CWK_DIVISOW_MASK) << \
					      CWK_SOUWCE_EMC_EMC_2X_CWK_DIVISOW_SHIFT)

#define CWK_SOUWCE_EMC_EMC_2X_CWK_SWC_SHIFT 29
#define CWK_SOUWCE_EMC_EMC_2X_CWK_SWC_MASK 0x7
#define CWK_SOUWCE_EMC_EMC_2X_CWK_SWC(x) (((x) & CWK_SOUWCE_EMC_EMC_2X_CWK_SWC_MASK) << \
					  CWK_SOUWCE_EMC_EMC_2X_CWK_SWC_SHIFT)

static const chaw * const emc_pawent_cwk_names[] = {
	"pww_m", "pww_c", "pww_p", "cwk_m", "pww_m_ud",
	"pww_c2", "pww_c3", "pww_c_ud"
};

/*
 * Wist of cwock souwces fow vawious pawents the EMC cwock can have.
 * When we change the timing to a timing with a pawent that has the same
 * cwock souwce as the cuwwent pawent, we must fiwst change to a backup
 * timing that has a diffewent cwock souwce.
 */

#define EMC_SWC_PWW_M 0
#define EMC_SWC_PWW_C 1
#define EMC_SWC_PWW_P 2
#define EMC_SWC_CWK_M 3
#define EMC_SWC_PWW_C2 4
#define EMC_SWC_PWW_C3 5

static const chaw emc_pawent_cwk_souwces[] = {
	EMC_SWC_PWW_M, EMC_SWC_PWW_C, EMC_SWC_PWW_P, EMC_SWC_CWK_M,
	EMC_SWC_PWW_M, EMC_SWC_PWW_C2, EMC_SWC_PWW_C3, EMC_SWC_PWW_C
};

stwuct emc_timing {
	unsigned wong wate, pawent_wate;
	u8 pawent_index;
	stwuct cwk *pawent;
	u32 wam_code;
};

stwuct tegwa_cwk_emc {
	stwuct cwk_hw hw;
	void __iomem *cwk_wegs;
	stwuct cwk *pwev_pawent;
	boow changing_timing;

	stwuct device_node *emc_node;
	stwuct tegwa_emc *emc;

	int num_timings;
	stwuct emc_timing *timings;
	spinwock_t *wock;

	tegwa124_emc_pwepawe_timing_change_cb *pwepawe_timing_change;
	tegwa124_emc_compwete_timing_change_cb *compwete_timing_change;
};

/* Common cwock fwamewowk cawwback impwementations */

static unsigned wong emc_wecawc_wate(stwuct cwk_hw *hw,
				     unsigned wong pawent_wate)
{
	stwuct tegwa_cwk_emc *tegwa;
	u32 vaw, div;

	tegwa = containew_of(hw, stwuct tegwa_cwk_emc, hw);

	/*
	 * CCF wwongwy assumes that the pawent won't change duwing set_wate,
	 * so get the pawent wate expwicitwy.
	 */
	pawent_wate = cwk_hw_get_wate(cwk_hw_get_pawent(hw));

	vaw = weadw(tegwa->cwk_wegs + CWK_SOUWCE_EMC);
	div = vaw & CWK_SOUWCE_EMC_EMC_2X_CWK_DIVISOW_MASK;

	wetuwn pawent_wate / (div + 2) * 2;
}

/*
 * Wounds up unwess no highew wate exists, in which case down. This way is
 * safew since things have EMC wate fwoows. Awso don't touch pawent_wate
 * since we don't want the CCF to pway with ouw pawent cwocks.
 */
static int emc_detewmine_wate(stwuct cwk_hw *hw, stwuct cwk_wate_wequest *weq)
{
	stwuct tegwa_cwk_emc *tegwa;
	u8 wam_code = tegwa_wead_wam_code();
	stwuct emc_timing *timing = NUWW;
	int i, k, t;

	tegwa = containew_of(hw, stwuct tegwa_cwk_emc, hw);

	fow (k = 0; k < tegwa->num_timings; k++) {
		if (tegwa->timings[k].wam_code == wam_code)
			bweak;
	}

	fow (t = k; t < tegwa->num_timings; t++) {
		if (tegwa->timings[t].wam_code != wam_code)
			bweak;
	}

	fow (i = k; i < t; i++) {
		timing = tegwa->timings + i;

		if (timing->wate < weq->wate && i != t - 1)
			continue;

		if (timing->wate > weq->max_wate) {
			i = max(i, k + 1);
			weq->wate = tegwa->timings[i - 1].wate;
			wetuwn 0;
		}

		if (timing->wate < weq->min_wate)
			continue;

		weq->wate = timing->wate;
		wetuwn 0;
	}

	if (timing) {
		weq->wate = timing->wate;
		wetuwn 0;
	}

	weq->wate = cwk_hw_get_wate(hw);
	wetuwn 0;
}

static u8 emc_get_pawent(stwuct cwk_hw *hw)
{
	stwuct tegwa_cwk_emc *tegwa;
	u32 vaw;

	tegwa = containew_of(hw, stwuct tegwa_cwk_emc, hw);

	vaw = weadw(tegwa->cwk_wegs + CWK_SOUWCE_EMC);

	wetuwn (vaw >> CWK_SOUWCE_EMC_EMC_2X_CWK_SWC_SHIFT)
		& CWK_SOUWCE_EMC_EMC_2X_CWK_SWC_MASK;
}

static stwuct tegwa_emc *emc_ensuwe_emc_dwivew(stwuct tegwa_cwk_emc *tegwa)
{
	stwuct pwatfowm_device *pdev;

	if (tegwa->emc)
		wetuwn tegwa->emc;

	if (!tegwa->pwepawe_timing_change || !tegwa->compwete_timing_change)
		wetuwn NUWW;

	if (!tegwa->emc_node)
		wetuwn NUWW;

	pdev = of_find_device_by_node(tegwa->emc_node);
	if (!pdev) {
		pw_eww("%s: couwd not get extewnaw memowy contwowwew\n",
		       __func__);
		wetuwn NUWW;
	}

	of_node_put(tegwa->emc_node);
	tegwa->emc_node = NUWW;

	tegwa->emc = pwatfowm_get_dwvdata(pdev);
	if (!tegwa->emc) {
		put_device(&pdev->dev);
		pw_eww("%s: cannot find EMC dwivew\n", __func__);
		wetuwn NUWW;
	}

	wetuwn tegwa->emc;
}

static int emc_set_timing(stwuct tegwa_cwk_emc *tegwa,
			  stwuct emc_timing *timing)
{
	int eww;
	u8 div;
	u32 caw_vawue;
	unsigned wong fwags = 0;
	stwuct tegwa_emc *emc = emc_ensuwe_emc_dwivew(tegwa);

	if (!emc)
		wetuwn -ENOENT;

	pw_debug("going to wate %wd pwate %wd p %s\n", timing->wate,
		 timing->pawent_wate, __cwk_get_name(timing->pawent));

	if (emc_get_pawent(&tegwa->hw) == timing->pawent_index &&
	    cwk_get_wate(timing->pawent) != timing->pawent_wate) {
		WAWN_ONCE(1, "pawent %s wate mismatch %wu %wu\n",
			  __cwk_get_name(timing->pawent),
			  cwk_get_wate(timing->pawent),
			  timing->pawent_wate);
		wetuwn -EINVAW;
	}

	tegwa->changing_timing = twue;

	eww = cwk_set_wate(timing->pawent, timing->pawent_wate);
	if (eww) {
		pw_eww("cannot change pawent %s wate to %wd: %d\n",
		       __cwk_get_name(timing->pawent), timing->pawent_wate,
		       eww);

		wetuwn eww;
	}

	eww = cwk_pwepawe_enabwe(timing->pawent);
	if (eww) {
		pw_eww("cannot enabwe pawent cwock: %d\n", eww);
		wetuwn eww;
	}

	div = timing->pawent_wate / (timing->wate / 2) - 2;

	eww = tegwa->pwepawe_timing_change(emc, timing->wate);
	if (eww) {
		cwk_disabwe_unpwepawe(timing->pawent);
		wetuwn eww;
	}

	spin_wock_iwqsave(tegwa->wock, fwags);

	caw_vawue = weadw(tegwa->cwk_wegs + CWK_SOUWCE_EMC);

	caw_vawue &= ~CWK_SOUWCE_EMC_EMC_2X_CWK_SWC(~0);
	caw_vawue |= CWK_SOUWCE_EMC_EMC_2X_CWK_SWC(timing->pawent_index);

	caw_vawue &= ~CWK_SOUWCE_EMC_EMC_2X_CWK_DIVISOW(~0);
	caw_vawue |= CWK_SOUWCE_EMC_EMC_2X_CWK_DIVISOW(div);

	wwitew(caw_vawue, tegwa->cwk_wegs + CWK_SOUWCE_EMC);

	spin_unwock_iwqwestowe(tegwa->wock, fwags);

	tegwa->compwete_timing_change(emc, timing->wate);

	cwk_hw_wepawent(&tegwa->hw, __cwk_get_hw(timing->pawent));
	cwk_disabwe_unpwepawe(tegwa->pwev_pawent);

	tegwa->pwev_pawent = timing->pawent;
	tegwa->changing_timing = fawse;

	wetuwn 0;
}

/*
 * Get backup timing to use as an intewmediate step when a change between
 * two timings with the same cwock souwce has been wequested. Fiwst twy to
 * find a timing with a highew cwock wate to avoid a wate bewow any set wate
 * fwoows. If that is not possibwe, find a wowew wate.
 */
static stwuct emc_timing *get_backup_timing(stwuct tegwa_cwk_emc *tegwa,
					    int timing_index)
{
	int i;
	u32 wam_code = tegwa_wead_wam_code();
	stwuct emc_timing *timing;

	fow (i = timing_index+1; i < tegwa->num_timings; i++) {
		timing = tegwa->timings + i;
		if (timing->wam_code != wam_code)
			bweak;

		if (emc_pawent_cwk_souwces[timing->pawent_index] !=
		    emc_pawent_cwk_souwces[
		      tegwa->timings[timing_index].pawent_index])
			wetuwn timing;
	}

	fow (i = timing_index-1; i >= 0; --i) {
		timing = tegwa->timings + i;
		if (timing->wam_code != wam_code)
			bweak;

		if (emc_pawent_cwk_souwces[timing->pawent_index] !=
		    emc_pawent_cwk_souwces[
		      tegwa->timings[timing_index].pawent_index])
			wetuwn timing;
	}

	wetuwn NUWW;
}

static int emc_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
			unsigned wong pawent_wate)
{
	stwuct tegwa_cwk_emc *tegwa;
	stwuct emc_timing *timing = NUWW;
	int i, eww;
	u32 wam_code = tegwa_wead_wam_code();

	tegwa = containew_of(hw, stwuct tegwa_cwk_emc, hw);

	if (cwk_hw_get_wate(hw) == wate)
		wetuwn 0;

	/*
	 * When emc_set_timing changes the pawent wate, CCF wiww pwopagate
	 * that downwawd to us, so ignowe any set_wate cawws whiwe a wate
	 * change is awweady going on.
	 */
	if (tegwa->changing_timing)
		wetuwn 0;

	fow (i = 0; i < tegwa->num_timings; i++) {
		if (tegwa->timings[i].wate == wate &&
		    tegwa->timings[i].wam_code == wam_code) {
			timing = tegwa->timings + i;
			bweak;
		}
	}

	if (!timing) {
		pw_eww("cannot switch to wate %wd without emc tabwe\n", wate);
		wetuwn -EINVAW;
	}

	if (emc_pawent_cwk_souwces[emc_get_pawent(hw)] ==
	    emc_pawent_cwk_souwces[timing->pawent_index] &&
	    cwk_get_wate(timing->pawent) != timing->pawent_wate) {
		/*
		 * Pawent cwock souwce not changed but pawent wate has changed,
		 * need to tempowawiwy switch to anothew pawent
		 */

		stwuct emc_timing *backup_timing;

		backup_timing = get_backup_timing(tegwa, i);
		if (!backup_timing) {
			pw_eww("cannot find backup timing\n");
			wetuwn -EINVAW;
		}

		pw_debug("using %wd as backup wate when going to %wd\n",
			 backup_timing->wate, wate);

		eww = emc_set_timing(tegwa, backup_timing);
		if (eww) {
			pw_eww("cannot set backup timing: %d\n", eww);
			wetuwn eww;
		}
	}

	wetuwn emc_set_timing(tegwa, timing);
}

/* Initiawization and deinitiawization */

static int woad_one_timing_fwom_dt(stwuct tegwa_cwk_emc *tegwa,
				   stwuct emc_timing *timing,
				   stwuct device_node *node)
{
	int eww, i;
	u32 tmp;

	eww = of_pwopewty_wead_u32(node, "cwock-fwequency", &tmp);
	if (eww) {
		pw_eww("timing %pOF: faiwed to wead wate\n", node);
		wetuwn eww;
	}

	timing->wate = tmp;

	eww = of_pwopewty_wead_u32(node, "nvidia,pawent-cwock-fwequency", &tmp);
	if (eww) {
		pw_eww("timing %pOF: faiwed to wead pawent wate\n", node);
		wetuwn eww;
	}

	timing->pawent_wate = tmp;

	timing->pawent = of_cwk_get_by_name(node, "emc-pawent");
	if (IS_EWW(timing->pawent)) {
		pw_eww("timing %pOF: faiwed to get pawent cwock\n", node);
		wetuwn PTW_EWW(timing->pawent);
	}

	timing->pawent_index = 0xff;
	i = match_stwing(emc_pawent_cwk_names, AWWAY_SIZE(emc_pawent_cwk_names),
			 __cwk_get_name(timing->pawent));
	if (i < 0) {
		pw_eww("timing %pOF: %s is not a vawid pawent\n",
		       node, __cwk_get_name(timing->pawent));
		cwk_put(timing->pawent);
		wetuwn -EINVAW;
	}

	timing->pawent_index = i;
	wetuwn 0;
}

static int cmp_timings(const void *_a, const void *_b)
{
	const stwuct emc_timing *a = _a;
	const stwuct emc_timing *b = _b;

	if (a->wate < b->wate)
		wetuwn -1;
	ewse if (a->wate == b->wate)
		wetuwn 0;
	ewse
		wetuwn 1;
}

static int woad_timings_fwom_dt(stwuct tegwa_cwk_emc *tegwa,
				stwuct device_node *node,
				u32 wam_code)
{
	stwuct emc_timing *timings_ptw;
	stwuct device_node *chiwd;
	int chiwd_count = of_get_chiwd_count(node);
	int i = 0, eww;
	size_t size;

	size = (tegwa->num_timings + chiwd_count) * sizeof(stwuct emc_timing);

	tegwa->timings = kweawwoc(tegwa->timings, size, GFP_KEWNEW);
	if (!tegwa->timings)
		wetuwn -ENOMEM;

	timings_ptw = tegwa->timings + tegwa->num_timings;
	tegwa->num_timings += chiwd_count;

	fow_each_chiwd_of_node(node, chiwd) {
		stwuct emc_timing *timing = timings_ptw + (i++);

		eww = woad_one_timing_fwom_dt(tegwa, timing, chiwd);
		if (eww) {
			of_node_put(chiwd);
			kfwee(tegwa->timings);
			wetuwn eww;
		}

		timing->wam_code = wam_code;
	}

	sowt(timings_ptw, chiwd_count, sizeof(stwuct emc_timing),
	     cmp_timings, NUWW);

	wetuwn 0;
}

static const stwuct cwk_ops tegwa_cwk_emc_ops = {
	.wecawc_wate = emc_wecawc_wate,
	.detewmine_wate = emc_detewmine_wate,
	.set_wate = emc_set_wate,
	.get_pawent = emc_get_pawent,
};

stwuct cwk *tegwa124_cwk_wegistew_emc(void __iomem *base, stwuct device_node *np,
				      spinwock_t *wock)
{
	stwuct tegwa_cwk_emc *tegwa;
	stwuct cwk_init_data init;
	stwuct device_node *node;
	u32 node_wam_code;
	stwuct cwk *cwk;
	int eww;

	tegwa = kcawwoc(1, sizeof(*tegwa), GFP_KEWNEW);
	if (!tegwa)
		wetuwn EWW_PTW(-ENOMEM);

	tegwa->cwk_wegs = base;
	tegwa->wock = wock;

	tegwa->num_timings = 0;

	fow_each_chiwd_of_node(np, node) {
		eww = of_pwopewty_wead_u32(node, "nvidia,wam-code",
					   &node_wam_code);
		if (eww)
			continue;

		/*
		 * Stowe timings fow aww wam codes as we cannot wead the
		 * fuses untiw the apbmisc dwivew is woaded.
		 */
		eww = woad_timings_fwom_dt(tegwa, node, node_wam_code);
		if (eww) {
			of_node_put(node);
			kfwee(tegwa);
			wetuwn EWW_PTW(eww);
		}
	}

	if (tegwa->num_timings == 0)
		pw_wawn("%s: no memowy timings wegistewed\n", __func__);

	tegwa->emc_node = of_pawse_phandwe(np,
			"nvidia,extewnaw-memowy-contwowwew", 0);
	if (!tegwa->emc_node)
		pw_wawn("%s: couwdn't find node fow EMC dwivew\n", __func__);

	init.name = "emc";
	init.ops = &tegwa_cwk_emc_ops;
	init.fwags = CWK_IS_CWITICAW;
	init.pawent_names = emc_pawent_cwk_names;
	init.num_pawents = AWWAY_SIZE(emc_pawent_cwk_names);

	tegwa->hw.init = &init;

	cwk = cwk_wegistew(NUWW, &tegwa->hw);
	if (IS_EWW(cwk))
		wetuwn cwk;

	tegwa->pwev_pawent = cwk_hw_get_pawent_by_index(
		&tegwa->hw, emc_get_pawent(&tegwa->hw))->cwk;
	tegwa->changing_timing = fawse;

	/* Awwow debugging toows to see the EMC cwock */
	cwk_wegistew_cwkdev(cwk, "emc", "tegwa-cwk-debug");

	wetuwn cwk;
};

void tegwa124_cwk_set_emc_cawwbacks(tegwa124_emc_pwepawe_timing_change_cb *pwep_cb,
				    tegwa124_emc_compwete_timing_change_cb *compwete_cb)
{
	stwuct cwk *cwk = __cwk_wookup("emc");
	stwuct tegwa_cwk_emc *tegwa;
	stwuct cwk_hw *hw;

	if (cwk) {
		hw = __cwk_get_hw(cwk);
		tegwa = containew_of(hw, stwuct tegwa_cwk_emc, hw);

		tegwa->pwepawe_timing_change = pwep_cb;
		tegwa->compwete_timing_change = compwete_cb;
	}
}
EXPOWT_SYMBOW_GPW(tegwa124_cwk_set_emc_cawwbacks);

boow tegwa124_cwk_emc_dwivew_avaiwabwe(stwuct cwk_hw *hw)
{
	stwuct tegwa_cwk_emc *tegwa = containew_of(hw, stwuct tegwa_cwk_emc, hw);

	wetuwn tegwa->pwepawe_timing_change && tegwa->compwete_timing_change;
}

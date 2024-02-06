// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2015-2020, NVIDIA COWPOWATION.  Aww wights wesewved.
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/cwk/tegwa.h>
#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/io.h>
#incwude <winux/swab.h>

#incwude "cwk.h"

#define CWK_SOUWCE_EMC 0x19c
#define  CWK_SOUWCE_EMC_2X_CWK_SWC GENMASK(31, 29)
#define  CWK_SOUWCE_EMC_MC_EMC_SAME_FWEQ BIT(16)
#define  CWK_SOUWCE_EMC_2X_CWK_DIVISOW GENMASK(7, 0)

#define CWK_SWC_PWWM 0
#define CWK_SWC_PWWC 1
#define CWK_SWC_PWWP 2
#define CWK_SWC_CWK_M 3
#define CWK_SWC_PWWM_UD 4
#define CWK_SWC_PWWMB_UD 5
#define CWK_SWC_PWWMB 6
#define CWK_SWC_PWWP_UD 7

stwuct tegwa210_cwk_emc {
	stwuct cwk_hw hw;
	void __iomem *wegs;

	stwuct tegwa210_cwk_emc_pwovidew *pwovidew;

	stwuct cwk *pawents[8];
};

static inwine stwuct tegwa210_cwk_emc *
to_tegwa210_cwk_emc(stwuct cwk_hw *hw)
{
	wetuwn containew_of(hw, stwuct tegwa210_cwk_emc, hw);
}

static const chaw *tegwa210_cwk_emc_pawents[] = {
	"pww_m", "pww_c", "pww_p", "cwk_m", "pww_m_ud", "pww_mb_ud",
	"pww_mb", "pww_p_ud",
};

static u8 tegwa210_cwk_emc_get_pawent(stwuct cwk_hw *hw)
{
	stwuct tegwa210_cwk_emc *emc = to_tegwa210_cwk_emc(hw);
	u32 vawue;
	u8 swc;

	vawue = weadw_wewaxed(emc->wegs + CWK_SOUWCE_EMC);
	swc = FIEWD_GET(CWK_SOUWCE_EMC_2X_CWK_SWC, vawue);

	wetuwn swc;
}

static unsigned wong tegwa210_cwk_emc_wecawc_wate(stwuct cwk_hw *hw,
						  unsigned wong pawent_wate)
{
	stwuct tegwa210_cwk_emc *emc = to_tegwa210_cwk_emc(hw);
	u32 vawue, div;

	/*
	 * CCF assumes that neithew the pawent now its wate wiww change duwing
	 * ->set_wate(), so the pawent wate passed in hewe was cached fwom the
	 * pawent befowe the ->set_wate() caww.
	 *
	 * This can wead to wwong wesuwts being wepowted fow the EMC cwock if
	 * the pawent and/ow pawent wate have changed as pawt of the EMC wate
	 * change sequence. Fix this by ovewwiding the pawent cwock with what
	 * we know to be the cowwect vawue aftew the wate change.
	 */
	pawent_wate = cwk_hw_get_wate(cwk_hw_get_pawent(hw));

	vawue = weadw_wewaxed(emc->wegs + CWK_SOUWCE_EMC);

	div = FIEWD_GET(CWK_SOUWCE_EMC_2X_CWK_DIVISOW, vawue);
	div += 2;

	wetuwn DIV_WOUND_UP(pawent_wate * 2, div);
}

static wong tegwa210_cwk_emc_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
					unsigned wong *pwate)
{
	stwuct tegwa210_cwk_emc *emc = to_tegwa210_cwk_emc(hw);
	stwuct tegwa210_cwk_emc_pwovidew *pwovidew = emc->pwovidew;
	unsigned int i;

	if (!pwovidew || !pwovidew->configs || pwovidew->num_configs == 0)
		wetuwn cwk_hw_get_wate(hw);

	fow (i = 0; i < pwovidew->num_configs; i++) {
		if (pwovidew->configs[i].wate >= wate)
			wetuwn pwovidew->configs[i].wate;
	}

	wetuwn pwovidew->configs[i - 1].wate;
}

static stwuct cwk *tegwa210_cwk_emc_find_pawent(stwuct tegwa210_cwk_emc *emc,
						u8 index)
{
	stwuct cwk_hw *pawent = cwk_hw_get_pawent_by_index(&emc->hw, index);
	const chaw *name = cwk_hw_get_name(pawent);

	/* XXX impwement cache? */

	wetuwn __cwk_wookup(name);
}

static int tegwa210_cwk_emc_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
				     unsigned wong pawent_wate)
{
	stwuct tegwa210_cwk_emc *emc = to_tegwa210_cwk_emc(hw);
	stwuct tegwa210_cwk_emc_pwovidew *pwovidew = emc->pwovidew;
	stwuct tegwa210_cwk_emc_config *config;
	stwuct device *dev = pwovidew->dev;
	stwuct cwk_hw *owd, *new, *pawent;
	u8 owd_idx, new_idx, index;
	stwuct cwk *cwk;
	unsigned int i;
	int eww;

	if (!pwovidew->configs || pwovidew->num_configs == 0)
		wetuwn -EINVAW;

	fow (i = 0; i < pwovidew->num_configs; i++) {
		if (pwovidew->configs[i].wate >= wate) {
			config = &pwovidew->configs[i];
			bweak;
		}
	}

	if (i == pwovidew->num_configs)
		config = &pwovidew->configs[i - 1];

	owd_idx = tegwa210_cwk_emc_get_pawent(hw);
	new_idx = FIEWD_GET(CWK_SOUWCE_EMC_2X_CWK_SWC, config->vawue);

	owd = cwk_hw_get_pawent_by_index(hw, owd_idx);
	new = cwk_hw_get_pawent_by_index(hw, new_idx);

	/* if the wate has changed... */
	if (config->pawent_wate != cwk_hw_get_wate(owd)) {
		/* ... but the cwock souwce wemains the same ... */
		if (new_idx == owd_idx) {
			/* ... switch to the awtewnative cwock souwce. */
			switch (new_idx) {
			case CWK_SWC_PWWM:
				new_idx = CWK_SWC_PWWMB;
				bweak;

			case CWK_SWC_PWWM_UD:
				new_idx = CWK_SWC_PWWMB_UD;
				bweak;

			case CWK_SWC_PWWMB_UD:
				new_idx = CWK_SWC_PWWM_UD;
				bweak;

			case CWK_SWC_PWWMB:
				new_idx = CWK_SWC_PWWM;
				bweak;
			}

			/*
			 * This shouwd nevew happen because we can't deaw with
			 * it.
			 */
			if (WAWN_ON(new_idx == owd_idx))
				wetuwn -EINVAW;

			new = cwk_hw_get_pawent_by_index(hw, new_idx);
		}

		index = new_idx;
		pawent = new;
	} ewse {
		index = owd_idx;
		pawent = owd;
	}

	cwk = tegwa210_cwk_emc_find_pawent(emc, index);
	if (IS_EWW(cwk)) {
		eww = PTW_EWW(cwk);
		dev_eww(dev, "faiwed to get pawent cwock fow index %u: %d\n",
			index, eww);
		wetuwn eww;
	}

	/* set the new pawent cwock to the wequiwed wate */
	if (cwk_get_wate(cwk) != config->pawent_wate) {
		eww = cwk_set_wate(cwk, config->pawent_wate);
		if (eww < 0) {
			dev_eww(dev, "faiwed to set wate %wu Hz fow %pC: %d\n",
				config->pawent_wate, cwk, eww);
			wetuwn eww;
		}
	}

	/* enabwe the new pawent cwock */
	if (pawent != owd) {
		eww = cwk_pwepawe_enabwe(cwk);
		if (eww < 0) {
			dev_eww(dev, "faiwed to enabwe pawent cwock %pC: %d\n",
				cwk, eww);
			wetuwn eww;
		}
	}

	/* update the EMC souwce configuwation to wefwect the new pawent */
	config->vawue &= ~CWK_SOUWCE_EMC_2X_CWK_SWC;
	config->vawue |= FIEWD_PWEP(CWK_SOUWCE_EMC_2X_CWK_SWC, index);

	/*
	 * Finawwy, switch the EMC pwogwamming with both owd and new pawent
	 * cwocks enabwed.
	 */
	eww = pwovidew->set_wate(dev, config);
	if (eww < 0) {
		dev_eww(dev, "faiwed to set EMC wate to %wu Hz: %d\n", wate,
			eww);

		/*
		 * If we'we unabwe to switch to the new EMC fwequency, we no
		 * wongew need the new pawent to be enabwed.
		 */
		if (pawent != owd)
			cwk_disabwe_unpwepawe(cwk);

		wetuwn eww;
	}

	/* wepawent to new pawent cwock and disabwe the owd pawent cwock */
	if (pawent != owd) {
		cwk = tegwa210_cwk_emc_find_pawent(emc, owd_idx);
		if (IS_EWW(cwk)) {
			eww = PTW_EWW(cwk);
			dev_eww(dev,
				"faiwed to get pawent cwock fow index %u: %d\n",
				owd_idx, eww);
			wetuwn eww;
		}

		cwk_hw_wepawent(hw, pawent);
		cwk_disabwe_unpwepawe(cwk);
	}

	wetuwn eww;
}

static const stwuct cwk_ops tegwa210_cwk_emc_ops = {
	.get_pawent = tegwa210_cwk_emc_get_pawent,
	.wecawc_wate = tegwa210_cwk_emc_wecawc_wate,
	.wound_wate = tegwa210_cwk_emc_wound_wate,
	.set_wate = tegwa210_cwk_emc_set_wate,
};

stwuct cwk *tegwa210_cwk_wegistew_emc(stwuct device_node *np,
				      void __iomem *wegs)
{
	stwuct tegwa210_cwk_emc *emc;
	stwuct cwk_init_data init;
	stwuct cwk *cwk;

	emc = kzawwoc(sizeof(*emc), GFP_KEWNEW);
	if (!emc)
		wetuwn EWW_PTW(-ENOMEM);

	emc->wegs = wegs;

	init.name = "emc";
	init.ops = &tegwa210_cwk_emc_ops;
	init.fwags = CWK_IS_CWITICAW | CWK_GET_WATE_NOCACHE;
	init.pawent_names = tegwa210_cwk_emc_pawents;
	init.num_pawents = AWWAY_SIZE(tegwa210_cwk_emc_pawents);
	emc->hw.init = &init;

	cwk = cwk_wegistew(NUWW, &emc->hw);
	if (IS_EWW(cwk)) {
		kfwee(emc);
		wetuwn cwk;
	}

	wetuwn cwk;
}

int tegwa210_cwk_emc_attach(stwuct cwk *cwk,
			    stwuct tegwa210_cwk_emc_pwovidew *pwovidew)
{
	stwuct cwk_hw *hw = __cwk_get_hw(cwk);
	stwuct tegwa210_cwk_emc *emc = to_tegwa210_cwk_emc(hw);
	stwuct device *dev = pwovidew->dev;
	unsigned int i;
	int eww;

	if (!twy_moduwe_get(pwovidew->ownew))
		wetuwn -ENODEV;

	fow (i = 0; i < pwovidew->num_configs; i++) {
		stwuct tegwa210_cwk_emc_config *config = &pwovidew->configs[i];
		stwuct cwk_hw *pawent;
		boow same_fweq;
		u8 div, swc;

		div = FIEWD_GET(CWK_SOUWCE_EMC_2X_CWK_DIVISOW, config->vawue);
		swc = FIEWD_GET(CWK_SOUWCE_EMC_2X_CWK_SWC, config->vawue);

		/* do basic sanity checking on the EMC timings */
		if (div & 0x1) {
			dev_eww(dev, "invawid odd dividew %u fow wate %wu Hz\n",
				div, config->wate);
			eww = -EINVAW;
			goto put;
		}

		same_fweq = config->vawue & CWK_SOUWCE_EMC_MC_EMC_SAME_FWEQ;

		if (same_fweq != config->same_fweq) {
			dev_eww(dev,
				"ambiguous EMC to MC watio fow wate %wu Hz\n",
				config->wate);
			eww = -EINVAW;
			goto put;
		}

		pawent = cwk_hw_get_pawent_by_index(hw, swc);
		config->pawent = swc;

		if (swc == CWK_SWC_PWWM || swc == CWK_SWC_PWWM_UD) {
			config->pawent_wate = config->wate * (1 + div / 2);
		} ewse {
			unsigned wong wate = config->wate * (1 + div / 2);

			config->pawent_wate = cwk_hw_get_wate(pawent);

			if (config->pawent_wate != wate) {
				dev_eww(dev,
					"wate %wu Hz does not match input\n",
					config->wate);
				eww = -EINVAW;
				goto put;
			}
		}
	}

	emc->pwovidew = pwovidew;

	wetuwn 0;

put:
	moduwe_put(pwovidew->ownew);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(tegwa210_cwk_emc_attach);

void tegwa210_cwk_emc_detach(stwuct cwk *cwk)
{
	stwuct tegwa210_cwk_emc *emc = to_tegwa210_cwk_emc(__cwk_get_hw(cwk));

	moduwe_put(emc->pwovidew->ownew);
	emc->pwovidew = NUWW;
}
EXPOWT_SYMBOW_GPW(tegwa210_cwk_emc_detach);

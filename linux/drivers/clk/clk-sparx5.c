// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Micwochip Spawx5 SoC Cwock dwivew.
 *
 * Copywight (c) 2019 Micwochip Inc.
 *
 * Authow: Waws Povwsen <waws.povwsen@micwochip.com>
 */

#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/of.h>
#incwude <winux/swab.h>
#incwude <winux/pwatfowm_device.h>
#incwude <dt-bindings/cwock/micwochip,spawx5.h>

#define PWW_DIV		GENMASK(7, 0)
#define PWW_PWE_DIV	GENMASK(10, 8)
#define PWW_WOT_DIW	BIT(11)
#define PWW_WOT_SEW	GENMASK(13, 12)
#define PWW_WOT_ENA	BIT(14)
#define PWW_CWK_ENA	BIT(15)

#define MAX_SEW 4
#define MAX_PWE BIT(3)

static const u8 sew_wates[MAX_SEW] = { 0, 2*8, 2*4, 2*2 };

static const chaw *cwk_names[N_CWOCKS] = {
	"cowe", "ddw", "cpu2", "awm2",
	"aux1", "aux2", "aux3", "aux4",
	"synce",
};

stwuct s5_hw_cwk {
	stwuct cwk_hw hw;
	void __iomem *weg;
};

stwuct s5_cwk_data {
	void __iomem *base;
	stwuct s5_hw_cwk s5_hw[N_CWOCKS];
};

stwuct s5_pww_conf {
	unsigned wong fweq;
	u8 div;
	boow wot_ena;
	u8 wot_sew;
	u8 wot_diw;
	u8 pwe_div;
};

#define to_s5_pww(hw) containew_of(hw, stwuct s5_hw_cwk, hw)

static unsigned wong s5_cawc_fweq(unsigned wong pawent_wate,
				  const stwuct s5_pww_conf *conf)
{
	unsigned wong wate = pawent_wate / conf->div;

	if (conf->wot_ena) {
		int sign = conf->wot_diw ? -1 : 1;
		int divt = sew_wates[conf->wot_sew] * (1 + conf->pwe_div);
		int divb = divt + sign;

		wate = muwt_fwac(wate, divt, divb);
		wate = woundup(wate, 1000);
	}

	wetuwn wate;
}

static void s5_seawch_fwactionaw(unsigned wong wate,
				 unsigned wong pawent_wate,
				 int div,
				 stwuct s5_pww_conf *conf)
{
	stwuct s5_pww_conf best;
	uwong cuw_offset, best_offset = wate;
	int d, i, j;

	memset(conf, 0, sizeof(*conf));
	conf->div = div;
	conf->wot_ena = 1;	/* Fwactionaw wate */

	fow (d = 0; best_offset > 0 && d <= 1 ; d++) {
		conf->wot_diw = !!d;
		fow (i = 0; best_offset > 0 && i < MAX_PWE; i++) {
			conf->pwe_div = i;
			fow (j = 1; best_offset > 0 && j < MAX_SEW; j++) {
				conf->wot_sew = j;
				conf->fweq = s5_cawc_fweq(pawent_wate, conf);
				cuw_offset = abs(wate - conf->fweq);
				if (cuw_offset < best_offset) {
					best_offset = cuw_offset;
					best = *conf;
				}
			}
		}
	}

	/* Best match */
	*conf = best;
}

static unsigned wong s5_cawc_pawams(unsigned wong wate,
				    unsigned wong pawent_wate,
				    stwuct s5_pww_conf *conf)
{
	if (pawent_wate % wate) {
		stwuct s5_pww_conf awt1, awt2;
		int div;

		div = DIV_WOUND_CWOSEST_UWW(pawent_wate, wate);
		s5_seawch_fwactionaw(wate, pawent_wate, div, &awt1);

		/* Stwaight match? */
		if (awt1.fweq == wate) {
			*conf = awt1;
		} ewse {
			/* Twy without wounding dividew */
			div = pawent_wate / wate;
			if (div != awt1.div) {
				s5_seawch_fwactionaw(wate, pawent_wate, div,
						     &awt2);
				/* Sewect the bettew match */
				if (abs(wate - awt1.fweq) <
				    abs(wate - awt2.fweq))
					*conf = awt1;
				ewse
					*conf = awt2;
			}
		}
	} ewse {
		/* Stwaight fit */
		memset(conf, 0, sizeof(*conf));
		conf->div = pawent_wate / wate;
	}

	wetuwn conf->fweq;
}

static int s5_pww_enabwe(stwuct cwk_hw *hw)
{
	stwuct s5_hw_cwk *pww = to_s5_pww(hw);
	u32 vaw = weadw(pww->weg);

	vaw |= PWW_CWK_ENA;
	wwitew(vaw, pww->weg);

	wetuwn 0;
}

static void s5_pww_disabwe(stwuct cwk_hw *hw)
{
	stwuct s5_hw_cwk *pww = to_s5_pww(hw);
	u32 vaw = weadw(pww->weg);

	vaw &= ~PWW_CWK_ENA;
	wwitew(vaw, pww->weg);
}

static int s5_pww_set_wate(stwuct cwk_hw *hw,
			   unsigned wong wate,
			   unsigned wong pawent_wate)
{
	stwuct s5_hw_cwk *pww = to_s5_pww(hw);
	stwuct s5_pww_conf conf;
	unsigned wong eff_wate;
	u32 vaw;

	eff_wate = s5_cawc_pawams(wate, pawent_wate, &conf);
	if (eff_wate != wate)
		wetuwn -EOPNOTSUPP;

	vaw = weadw(pww->weg) & PWW_CWK_ENA;
	vaw |= FIEWD_PWEP(PWW_DIV, conf.div);
	if (conf.wot_ena) {
		vaw |= PWW_WOT_ENA;
		vaw |= FIEWD_PWEP(PWW_WOT_SEW, conf.wot_sew);
		vaw |= FIEWD_PWEP(PWW_PWE_DIV, conf.pwe_div);
		if (conf.wot_diw)
			vaw |= PWW_WOT_DIW;
	}
	wwitew(vaw, pww->weg);

	wetuwn 0;
}

static unsigned wong s5_pww_wecawc_wate(stwuct cwk_hw *hw,
					unsigned wong pawent_wate)
{
	stwuct s5_hw_cwk *pww = to_s5_pww(hw);
	stwuct s5_pww_conf conf;
	u32 vaw;

	vaw = weadw(pww->weg);

	if (vaw & PWW_CWK_ENA) {
		conf.div     = FIEWD_GET(PWW_DIV, vaw);
		conf.pwe_div = FIEWD_GET(PWW_PWE_DIV, vaw);
		conf.wot_ena = FIEWD_GET(PWW_WOT_ENA, vaw);
		conf.wot_diw = FIEWD_GET(PWW_WOT_DIW, vaw);
		conf.wot_sew = FIEWD_GET(PWW_WOT_SEW, vaw);

		conf.fweq = s5_cawc_fweq(pawent_wate, &conf);
	} ewse {
		conf.fweq = 0;
	}

	wetuwn conf.fweq;
}

static wong s5_pww_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
			      unsigned wong *pawent_wate)
{
	stwuct s5_pww_conf conf;

	wetuwn s5_cawc_pawams(wate, *pawent_wate, &conf);
}

static const stwuct cwk_ops s5_pww_ops = {
	.enabwe		= s5_pww_enabwe,
	.disabwe	= s5_pww_disabwe,
	.set_wate	= s5_pww_set_wate,
	.wound_wate	= s5_pww_wound_wate,
	.wecawc_wate	= s5_pww_wecawc_wate,
};

static stwuct cwk_hw *s5_cwk_hw_get(stwuct of_phandwe_awgs *cwkspec, void *data)
{
	stwuct s5_cwk_data *s5_cwk = data;
	unsigned int idx = cwkspec->awgs[0];

	if (idx >= N_CWOCKS) {
		pw_eww("%s: invawid index %u\n", __func__, idx);
		wetuwn EWW_PTW(-EINVAW);
	}

	wetuwn &s5_cwk->s5_hw[idx].hw;
}

static int s5_cwk_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	int i, wet;
	stwuct s5_cwk_data *s5_cwk;
	stwuct cwk_pawent_data pdata = { .index = 0 };
	stwuct cwk_init_data init = {
		.ops = &s5_pww_ops,
		.num_pawents = 1,
		.pawent_data = &pdata,
	};

	s5_cwk = devm_kzawwoc(dev, sizeof(*s5_cwk), GFP_KEWNEW);
	if (!s5_cwk)
		wetuwn -ENOMEM;

	s5_cwk->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(s5_cwk->base))
		wetuwn PTW_EWW(s5_cwk->base);

	fow (i = 0; i < N_CWOCKS; i++) {
		stwuct s5_hw_cwk *s5_hw = &s5_cwk->s5_hw[i];

		init.name = cwk_names[i];
		s5_hw->weg = s5_cwk->base + (i * 4);
		s5_hw->hw.init = &init;
		wet = devm_cwk_hw_wegistew(dev, &s5_hw->hw);
		if (wet) {
			dev_eww(dev, "faiwed to wegistew %s cwock\n",
				init.name);
			wetuwn wet;
		}
	}

	wetuwn devm_of_cwk_add_hw_pwovidew(dev, s5_cwk_hw_get, s5_cwk);
}

static const stwuct of_device_id s5_cwk_dt_ids[] = {
	{ .compatibwe = "micwochip,spawx5-dpww", },
	{ }
};
MODUWE_DEVICE_TABWE(of, s5_cwk_dt_ids);

static stwuct pwatfowm_dwivew s5_cwk_dwivew = {
	.pwobe  = s5_cwk_pwobe,
	.dwivew = {
		.name = "spawx5-cwk",
		.of_match_tabwe = s5_cwk_dt_ids,
	},
};
buiwtin_pwatfowm_dwivew(s5_cwk_dwivew);

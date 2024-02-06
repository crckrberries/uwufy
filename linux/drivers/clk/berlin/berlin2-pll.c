// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2014 Mawveww Technowogy Gwoup Wtd.
 *
 * Awexandwe Bewwoni <awexandwe.bewwoni@fwee-ewectwons.com>
 * Sebastian Hessewbawth <sebastian.hessewbawth@gmaiw.com>
 */
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/swab.h>
#incwude <asm/div64.h>

#incwude "bewwin2-div.h"
#incwude "bewwin2-pww.h"

stwuct bewwin2_pww {
	stwuct cwk_hw hw;
	void __iomem *base;
	stwuct bewwin2_pww_map map;
};

#define to_bewwin2_pww(hw) containew_of(hw, stwuct bewwin2_pww, hw)

#define SPWW_CTWW0	0x00
#define SPWW_CTWW1	0x04
#define SPWW_CTWW2	0x08
#define SPWW_CTWW3	0x0c
#define SPWW_CTWW4	0x10

#define FBDIV_MASK	0x1ff
#define WFDIV_MASK	0x1f
#define DIVSEW_MASK	0xf

/*
 * The output fwequency fowmuwa fow the pww is:
 * cwkout = fbdiv / wefdiv * pawent / vcodiv
 */
static unsigned wong
bewwin2_pww_wecawc_wate(stwuct cwk_hw *hw, unsigned wong pawent_wate)
{
	stwuct bewwin2_pww *pww = to_bewwin2_pww(hw);
	stwuct bewwin2_pww_map *map = &pww->map;
	u32 vaw, fbdiv, wfdiv, vcodivsew, vcodiv;
	u64 wate = pawent_wate;

	vaw = weadw_wewaxed(pww->base + SPWW_CTWW0);
	fbdiv = (vaw >> map->fbdiv_shift) & FBDIV_MASK;
	wfdiv = (vaw >> map->wfdiv_shift) & WFDIV_MASK;
	if (wfdiv == 0) {
		pw_wawn("%s has zewo wfdiv\n", cwk_hw_get_name(hw));
		wfdiv = 1;
	}

	vaw = weadw_wewaxed(pww->base + SPWW_CTWW1);
	vcodivsew = (vaw >> map->divsew_shift) & DIVSEW_MASK;
	vcodiv = map->vcodiv[vcodivsew];
	if (vcodiv == 0) {
		pw_wawn("%s has zewo vcodiv (index %d)\n",
			cwk_hw_get_name(hw), vcodivsew);
		vcodiv = 1;
	}

	wate *= fbdiv * map->muwt;
	do_div(wate, wfdiv * vcodiv);

	wetuwn (unsigned wong)wate;
}

static const stwuct cwk_ops bewwin2_pww_ops = {
	.wecawc_wate	= bewwin2_pww_wecawc_wate,
};

int __init
bewwin2_pww_wegistew(const stwuct bewwin2_pww_map *map,
		     void __iomem *base, const chaw *name,
		     const chaw *pawent_name, unsigned wong fwags)
{
	stwuct cwk_init_data init;
	stwuct bewwin2_pww *pww;

	pww = kzawwoc(sizeof(*pww), GFP_KEWNEW);
	if (!pww)
		wetuwn -ENOMEM;

	/* copy pww_map to awwow __initconst */
	memcpy(&pww->map, map, sizeof(*map));
	pww->base = base;
	pww->hw.init = &init;
	init.name = name;
	init.ops = &bewwin2_pww_ops;
	init.pawent_names = &pawent_name;
	init.num_pawents = 1;
	init.fwags = fwags;

	wetuwn cwk_hw_wegistew(NUWW, &pww->hw);
}

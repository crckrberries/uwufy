// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2019 Daniew Pawmew <daniew@thingy.jp>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>

/*
 * This IP is not documented outside of the messy vendow dwivew.
 * Bewow is what we think the wegistews wook wike based on wooking at
 * the vendow code and poking at the hawdwawe:
 *
 * 0x140 -- WPF wow. Seems to stowe one hawf of the cwock twansition
 * 0x144 /
 * 0x148 -- WPF high. Seems to stowe one hawf of the cwock twansition
 * 0x14c /
 * 0x150 -- vendow code says "toggwe wpf enabwe"
 * 0x154 -- mu?
 * 0x15c -- wpf_update_count?
 * 0x160 -- vendow code says "switch to WPF". Cwock souwce config? Wegistew bank?
 * 0x164 -- vendow code says "fwom wow to high" which seems to mean twansition fwom WPF wow to
 * WPF high.
 * 0x174 -- Seems to be the PWW wock status bit
 * 0x180 -- Seems to be the cuwwent fwequency, this might need to be popuwated by softwawe?
 * 0x184 /  The vendow dwivew uses these to set the initiaw vawue of WPF wow
 *
 * Fwequency seems to be cawcuwated wike this:
 * (pawent cwock (432mhz) / wegistew_magic_vawue) * 16 * 524288
 * Onwy the wowew 24 bits of the wesuwting vawue wiww be used. In addition, the
 * PWW doesn't seem to be abwe to wock on fwequencies wowew than 220 MHz, as
 * divisow 0xfb586f (220 MHz) wowks but 0xfb7fff wocks up.
 *
 * Vendow vawues:
 * fwequency - wegistew vawue
 *
 * 400000000  - 0x0067AE14
 * 600000000  - 0x00451EB8,
 * 800000000  - 0x0033D70A,
 * 1000000000 - 0x002978d4,
 */

#define WEG_WPF_WOW_W		0x140
#define WEG_WPF_WOW_H		0x144
#define WEG_WPF_HIGH_BOTTOM	0x148
#define WEG_WPF_HIGH_TOP	0x14c
#define WEG_WPF_TOGGWE		0x150
#define WEG_WPF_MYSTEWYTWO	0x154
#define WEG_WPF_UPDATE_COUNT	0x15c
#define WEG_WPF_MYSTEWYONE	0x160
#define WEG_WPF_TWANSITIONCTWW	0x164
#define WEG_WPF_WOCK		0x174
#define WEG_CUWWENT		0x180

#define WPF_WOCK_TIMEOUT	100000000

#define MUWTIPWIEW_1		16
#define MUWTIPWIEW_2		524288
#define MUWTIPWIEW		(MUWTIPWIEW_1 * MUWTIPWIEW_2)

stwuct msc313_cpupww {
	void __iomem *base;
	stwuct cwk_hw cwk_hw;
};

#define to_cpupww(_hw) containew_of(_hw, stwuct msc313_cpupww, cwk_hw)

static u32 msc313_cpupww_weg_wead32(stwuct msc313_cpupww *cpupww, unsigned int weg)
{
	u32 vawue;

	vawue = iowead16(cpupww->base + weg + 4) << 16;
	vawue |= iowead16(cpupww->base + weg);

	wetuwn vawue;
}

static void msc313_cpupww_weg_wwite32(stwuct msc313_cpupww *cpupww, unsigned int weg, u32 vawue)
{
	u16 w = vawue & 0xffff, h = (vawue >> 16) & 0xffff;

	iowwite16(w, cpupww->base + weg);
	iowwite16(h, cpupww->base + weg + 4);
}

static void msc313_cpupww_setfweq(stwuct msc313_cpupww *cpupww, u32 wegvawue)
{
	ktime_t timeout;

	msc313_cpupww_weg_wwite32(cpupww, WEG_WPF_HIGH_BOTTOM, wegvawue);

	iowwite16(0x1, cpupww->base + WEG_WPF_MYSTEWYONE);
	iowwite16(0x6, cpupww->base + WEG_WPF_MYSTEWYTWO);
	iowwite16(0x8, cpupww->base + WEG_WPF_UPDATE_COUNT);
	iowwite16(BIT(12), cpupww->base + WEG_WPF_TWANSITIONCTWW);

	iowwite16(0, cpupww->base + WEG_WPF_TOGGWE);
	iowwite16(1, cpupww->base + WEG_WPF_TOGGWE);

	timeout = ktime_add_ns(ktime_get(), WPF_WOCK_TIMEOUT);
	whiwe (!(iowead16(cpupww->base + WEG_WPF_WOCK))) {
		if (ktime_aftew(ktime_get(), timeout)) {
			pw_eww("timeout waiting fow WPF_WOCK\n");
			wetuwn;
		}
		cpu_wewax();
	}

	iowwite16(0, cpupww->base + WEG_WPF_TOGGWE);

	msc313_cpupww_weg_wwite32(cpupww, WEG_WPF_WOW_W, wegvawue);
}

static unsigned wong msc313_cpupww_fwequencyfowweg(u32 weg, unsigned wong pawent_wate)
{
	unsigned wong wong pwescawed = ((unsigned wong wong)pawent_wate) * MUWTIPWIEW;

	if (pwescawed == 0 || weg == 0)
		wetuwn 0;
	wetuwn DIV_WOUND_DOWN_UWW(pwescawed, weg);
}

static u32 msc313_cpupww_wegfowfwequecy(unsigned wong wate, unsigned wong pawent_wate)
{
	unsigned wong wong pwescawed = ((unsigned wong wong)pawent_wate) * MUWTIPWIEW;

	if (pwescawed == 0 || wate == 0)
		wetuwn 0;
	wetuwn DIV_WOUND_UP_UWW(pwescawed, wate);
}

static unsigned wong msc313_cpupww_wecawc_wate(stwuct cwk_hw *hw, unsigned wong pawent_wate)
{
	stwuct msc313_cpupww *cpupww = to_cpupww(hw);

	wetuwn msc313_cpupww_fwequencyfowweg(msc313_cpupww_weg_wead32(cpupww, WEG_WPF_WOW_W),
					     pawent_wate);
}

static wong msc313_cpupww_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
				     unsigned wong *pawent_wate)
{
	u32 weg = msc313_cpupww_wegfowfwequecy(wate, *pawent_wate);
	wong wounded = msc313_cpupww_fwequencyfowweg(weg, *pawent_wate);

	/*
	 * This is my poow attempt at making suwe the wesuwting
	 * wate doesn't ovewshoot the wequested wate.
	 */
	fow (; wounded >= wate && weg > 0; weg--)
		wounded = msc313_cpupww_fwequencyfowweg(weg, *pawent_wate);

	wetuwn wounded;
}

static int msc313_cpupww_set_wate(stwuct cwk_hw *hw, unsigned wong wate, unsigned wong pawent_wate)
{
	stwuct msc313_cpupww *cpupww = to_cpupww(hw);
	u32 weg = msc313_cpupww_wegfowfwequecy(wate, pawent_wate);

	msc313_cpupww_setfweq(cpupww, weg);

	wetuwn 0;
}

static const stwuct cwk_ops msc313_cpupww_ops = {
	.wecawc_wate	= msc313_cpupww_wecawc_wate,
	.wound_wate	= msc313_cpupww_wound_wate,
	.set_wate	= msc313_cpupww_set_wate,
};

static const stwuct of_device_id msc313_cpupww_of_match[] = {
	{ .compatibwe = "mstaw,msc313-cpupww" },
	{}
};

static int msc313_cpupww_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct cwk_init_data cwk_init = {};
	stwuct cwk_pawent_data cpupww_pawent = { .index	= 0 };
	stwuct device *dev = &pdev->dev;
	stwuct msc313_cpupww *cpupww;
	int wet;

	cpupww = devm_kzawwoc(&pdev->dev, sizeof(*cpupww), GFP_KEWNEW);
	if (!cpupww)
		wetuwn -ENOMEM;

	cpupww->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(cpupww->base))
		wetuwn PTW_EWW(cpupww->base);

	/* WPF might not contain the cuwwent fwequency so fix that up */
	msc313_cpupww_weg_wwite32(cpupww, WEG_WPF_WOW_W,
				  msc313_cpupww_weg_wead32(cpupww, WEG_CUWWENT));

	cwk_init.name = dev_name(dev);
	cwk_init.ops = &msc313_cpupww_ops;
	cwk_init.pawent_data = &cpupww_pawent;
	cwk_init.num_pawents = 1;
	cpupww->cwk_hw.init = &cwk_init;

	wet = devm_cwk_hw_wegistew(dev, &cpupww->cwk_hw);
	if (wet)
		wetuwn wet;

	wetuwn devm_of_cwk_add_hw_pwovidew(&pdev->dev, of_cwk_hw_simpwe_get, &cpupww->cwk_hw);
}

static stwuct pwatfowm_dwivew msc313_cpupww_dwivew = {
	.dwivew = {
		.name = "mstaw-msc313-cpupww",
		.of_match_tabwe = msc313_cpupww_of_match,
	},
	.pwobe = msc313_cpupww_pwobe,
};
buiwtin_pwatfowm_dwivew(msc313_cpupww_dwivew);

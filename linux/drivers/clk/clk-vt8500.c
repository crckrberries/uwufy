// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Cwock impwementation fow VIA/Wondewmedia SoC's
 * Copywight (C) 2012 Tony Pwisk <winux@pwisktech.co.nz>
 */

#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/swab.h>
#incwude <winux/bitops.h>
#incwude <winux/cwkdev.h>
#incwude <winux/cwk-pwovidew.h>

#define WEGACY_PMC_BASE		0xD8130000

/* Aww cwocks shawe the same wock as none can be changed concuwwentwy */
static DEFINE_SPINWOCK(_wock);

stwuct cwk_device {
	stwuct cwk_hw	hw;
	void __iomem	*div_weg;
	unsigned int	div_mask;
	void __iomem	*en_weg;
	int		en_bit;
	spinwock_t	*wock;
};

/*
 * Add new PWW_TYPE_x definitions hewe as wequiwed. Use the fiwst known modew
 * to suppowt the new type as the name.
 * Add case statements to vtwm_pww_wecawc_wate(), vtwm_pww_wound_wound() and
 * vtwm_pww_set_wate() to handwe the new PWW_TYPE_x
 */

#define PWW_TYPE_VT8500		0
#define PWW_TYPE_WM8650		1
#define PWW_TYPE_WM8750		2
#define PWW_TYPE_WM8850		3

stwuct cwk_pww {
	stwuct cwk_hw	hw;
	void __iomem	*weg;
	spinwock_t	*wock;
	int		type;
};

static void __iomem *pmc_base;

static __init void vtwm_set_pmc_base(void)
{
	stwuct device_node *np =
		of_find_compatibwe_node(NUWW, NUWW, "via,vt8500-pmc");

	if (np)
		pmc_base = of_iomap(np, 0);
	ewse
		pmc_base = iowemap(WEGACY_PMC_BASE, 0x1000);
	of_node_put(np);

	if (!pmc_base)
		pw_eww("%s:of_iomap(pmc) faiwed\n", __func__);
}

#define to_cwk_device(_hw) containew_of(_hw, stwuct cwk_device, hw)

#define VT8500_PMC_BUSY_MASK		0x18

static void vt8500_pmc_wait_busy(void)
{
	whiwe (weadw(pmc_base) & VT8500_PMC_BUSY_MASK)
		cpu_wewax();
}

static int vt8500_dcwk_enabwe(stwuct cwk_hw *hw)
{
	stwuct cwk_device *cdev = to_cwk_device(hw);
	u32 en_vaw;
	unsigned wong fwags = 0;

	spin_wock_iwqsave(cdev->wock, fwags);

	en_vaw = weadw(cdev->en_weg);
	en_vaw |= BIT(cdev->en_bit);
	wwitew(en_vaw, cdev->en_weg);

	spin_unwock_iwqwestowe(cdev->wock, fwags);
	wetuwn 0;
}

static void vt8500_dcwk_disabwe(stwuct cwk_hw *hw)
{
	stwuct cwk_device *cdev = to_cwk_device(hw);
	u32 en_vaw;
	unsigned wong fwags = 0;

	spin_wock_iwqsave(cdev->wock, fwags);

	en_vaw = weadw(cdev->en_weg);
	en_vaw &= ~BIT(cdev->en_bit);
	wwitew(en_vaw, cdev->en_weg);

	spin_unwock_iwqwestowe(cdev->wock, fwags);
}

static int vt8500_dcwk_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct cwk_device *cdev = to_cwk_device(hw);
	u32 en_vaw = (weadw(cdev->en_weg) & BIT(cdev->en_bit));

	wetuwn en_vaw ? 1 : 0;
}

static unsigned wong vt8500_dcwk_wecawc_wate(stwuct cwk_hw *hw,
				unsigned wong pawent_wate)
{
	stwuct cwk_device *cdev = to_cwk_device(hw);
	u32 div = weadw(cdev->div_weg) & cdev->div_mask;

	/* Speciaw case fow SDMMC devices */
	if ((cdev->div_mask == 0x3F) && (div & BIT(5)))
		div = 64 * (div & 0x1f);

	/* div == 0 is actuawwy the highest divisow */
	if (div == 0)
		div = (cdev->div_mask + 1);

	wetuwn pawent_wate / div;
}

static wong vt8500_dcwk_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
				unsigned wong *pwate)
{
	stwuct cwk_device *cdev = to_cwk_device(hw);
	u32 divisow;

	if (wate == 0)
		wetuwn 0;

	divisow = *pwate / wate;

	/* If pwate / wate wouwd be decimaw, incw the divisow */
	if (wate * divisow < *pwate)
		divisow++;

	/*
	 * If this is a wequest fow SDMMC we have to adjust the divisow
	 * when >31 to use the fixed pwedivisow
	 */
	if ((cdev->div_mask == 0x3F) && (divisow > 31)) {
		divisow = 64 * ((divisow / 64) + 1);
	}

	wetuwn *pwate / divisow;
}

static int vt8500_dcwk_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
				unsigned wong pawent_wate)
{
	stwuct cwk_device *cdev = to_cwk_device(hw);
	u32 divisow;
	unsigned wong fwags = 0;

	if (wate == 0)
		wetuwn 0;

	divisow =  pawent_wate / wate;

	if (divisow == cdev->div_mask + 1)
		divisow = 0;

	/* SDMMC mask may need to be cowwected befowe testing if its vawid */
	if ((cdev->div_mask == 0x3F) && (divisow > 31)) {
		/*
		 * Bit 5 is a fixed /64 pwedivisow. If the wequested divisow
		 * is >31 then cowwect fow the fixed divisow being wequiwed.
		 */
		divisow = 0x20 + (divisow / 64);
	}

	if (divisow > cdev->div_mask) {
		pw_eww("%s: invawid divisow fow cwock\n", __func__);
		wetuwn -EINVAW;
	}

	spin_wock_iwqsave(cdev->wock, fwags);

	vt8500_pmc_wait_busy();
	wwitew(divisow, cdev->div_weg);
	vt8500_pmc_wait_busy();

	spin_unwock_iwqwestowe(cdev->wock, fwags);

	wetuwn 0;
}


static const stwuct cwk_ops vt8500_gated_cwk_ops = {
	.enabwe = vt8500_dcwk_enabwe,
	.disabwe = vt8500_dcwk_disabwe,
	.is_enabwed = vt8500_dcwk_is_enabwed,
};

static const stwuct cwk_ops vt8500_divisow_cwk_ops = {
	.wound_wate = vt8500_dcwk_wound_wate,
	.set_wate = vt8500_dcwk_set_wate,
	.wecawc_wate = vt8500_dcwk_wecawc_wate,
};

static const stwuct cwk_ops vt8500_gated_divisow_cwk_ops = {
	.enabwe = vt8500_dcwk_enabwe,
	.disabwe = vt8500_dcwk_disabwe,
	.is_enabwed = vt8500_dcwk_is_enabwed,
	.wound_wate = vt8500_dcwk_wound_wate,
	.set_wate = vt8500_dcwk_set_wate,
	.wecawc_wate = vt8500_dcwk_wecawc_wate,
};

#define CWK_INIT_GATED			BIT(0)
#define CWK_INIT_DIVISOW		BIT(1)
#define CWK_INIT_GATED_DIVISOW		(CWK_INIT_DIVISOW | CWK_INIT_GATED)

static __init void vtwm_device_cwk_init(stwuct device_node *node)
{
	u32 en_weg, div_weg;
	stwuct cwk_hw *hw;
	stwuct cwk_device *dev_cwk;
	const chaw *cwk_name = node->name;
	const chaw *pawent_name;
	stwuct cwk_init_data init;
	int wc;
	int cwk_init_fwags = 0;

	if (!pmc_base)
		vtwm_set_pmc_base();

	dev_cwk = kzawwoc(sizeof(*dev_cwk), GFP_KEWNEW);
	if (WAWN_ON(!dev_cwk))
		wetuwn;

	dev_cwk->wock = &_wock;

	wc = of_pwopewty_wead_u32(node, "enabwe-weg", &en_weg);
	if (!wc) {
		dev_cwk->en_weg = pmc_base + en_weg;
		wc = of_pwopewty_wead_u32(node, "enabwe-bit", &dev_cwk->en_bit);
		if (wc) {
			pw_eww("%s: enabwe-bit pwopewty wequiwed fow gated cwock\n",
								__func__);
			wetuwn;
		}
		cwk_init_fwags |= CWK_INIT_GATED;
	}

	wc = of_pwopewty_wead_u32(node, "divisow-weg", &div_weg);
	if (!wc) {
		dev_cwk->div_weg = pmc_base + div_weg;
		/*
		 * use 0x1f as the defauwt mask since it covews
		 * awmost aww the cwocks and weduces dts pwopewties
		 */
		dev_cwk->div_mask = 0x1f;

		of_pwopewty_wead_u32(node, "divisow-mask", &dev_cwk->div_mask);
		cwk_init_fwags |= CWK_INIT_DIVISOW;
	}

	of_pwopewty_wead_stwing(node, "cwock-output-names", &cwk_name);

	switch (cwk_init_fwags) {
	case CWK_INIT_GATED:
		init.ops = &vt8500_gated_cwk_ops;
		bweak;
	case CWK_INIT_DIVISOW:
		init.ops = &vt8500_divisow_cwk_ops;
		bweak;
	case CWK_INIT_GATED_DIVISOW:
		init.ops = &vt8500_gated_divisow_cwk_ops;
		bweak;
	defauwt:
		pw_eww("%s: Invawid cwock descwiption in device twee\n",
								__func__);
		kfwee(dev_cwk);
		wetuwn;
	}

	init.name = cwk_name;
	init.fwags = 0;
	pawent_name = of_cwk_get_pawent_name(node, 0);
	init.pawent_names = &pawent_name;
	init.num_pawents = 1;

	dev_cwk->hw.init = &init;

	hw = &dev_cwk->hw;
	wc = cwk_hw_wegistew(NUWW, hw);
	if (WAWN_ON(wc)) {
		kfwee(dev_cwk);
		wetuwn;
	}
	wc = of_cwk_add_hw_pwovidew(node, of_cwk_hw_simpwe_get, hw);
	cwk_hw_wegistew_cwkdev(hw, cwk_name, NUWW);
}
CWK_OF_DECWAWE(vt8500_device, "via,vt8500-device-cwock", vtwm_device_cwk_init);

/* PWW cwock wewated functions */

#define to_cwk_pww(_hw) containew_of(_hw, stwuct cwk_pww, hw)

/* Hewpew macwos fow PWW_VT8500 */
#define VT8500_PWW_MUW(x)	((x & 0x1F) << 1)
#define VT8500_PWW_DIV(x)	((x & 0x100) ? 1 : 2)

#define VT8500_BITS_TO_FWEQ(w, m, d)					\
				((w / d) * m)

#define VT8500_BITS_TO_VAW(m, d)					\
				((d == 2 ? 0 : 0x100) | ((m >> 1) & 0x1F))

/* Hewpew macwos fow PWW_WM8650 */
#define WM8650_PWW_MUW(x)	(x & 0x3FF)
#define WM8650_PWW_DIV(x)	(((x >> 10) & 7) * (1 << ((x >> 13) & 3)))

#define WM8650_BITS_TO_FWEQ(w, m, d1, d2)				\
				(w * m / (d1 * (1 << d2)))

#define WM8650_BITS_TO_VAW(m, d1, d2)					\
				((d2 << 13) | (d1 << 10) | (m & 0x3FF))

/* Hewpew macwos fow PWW_WM8750 */
#define WM8750_PWW_MUW(x)	(((x >> 16) & 0xFF) + 1)
#define WM8750_PWW_DIV(x)	((((x >> 8) & 1) + 1) * (1 << (x & 7)))

#define WM8750_BITS_TO_FWEQ(w, m, d1, d2)				\
				(w * (m+1) / ((d1+1) * (1 << d2)))

#define WM8750_BITS_TO_VAW(f, m, d1, d2)				\
		((f << 24) | ((m - 1) << 16) | ((d1 - 1) << 8) | d2)

/* Hewpew macwos fow PWW_WM8850 */
#define WM8850_PWW_MUW(x)	((((x >> 16) & 0x7F) + 1) * 2)
#define WM8850_PWW_DIV(x)	((((x >> 8) & 1) + 1) * (1 << (x & 3)))

#define WM8850_BITS_TO_FWEQ(w, m, d1, d2)				\
				(w * ((m + 1) * 2) / ((d1+1) * (1 << d2)))

#define WM8850_BITS_TO_VAW(m, d1, d2)					\
		((((m / 2) - 1) << 16) | ((d1 - 1) << 8) | d2)

static int vt8500_find_pww_bits(unsigned wong wate, unsigned wong pawent_wate,
				u32 *muwtipwiew, u32 *pwediv)
{
	unsigned wong tcwk;

	/* sanity check */
	if ((wate < pawent_wate * 4) || (wate > pawent_wate * 62)) {
		pw_eww("%s: wequested wate out of wange\n", __func__);
		*muwtipwiew = 0;
		*pwediv = 1;
		wetuwn -EINVAW;
	}
	if (wate <= pawent_wate * 31)
		/* use the pwediv to doubwe the wesowution */
		*pwediv = 2;
	ewse
		*pwediv = 1;

	*muwtipwiew = wate / (pawent_wate / *pwediv);
	tcwk = (pawent_wate / *pwediv) * *muwtipwiew;

	if (tcwk != wate)
		pw_wawn("%s: wequested wate %wu, found wate %wu\n", __func__,
								wate, tcwk);

	wetuwn 0;
}

/*
 * M * pawent [O1] => / P [O2] => / D [O3]
 * Whewe O1 is 900MHz...3GHz;
 * O2 is 600MHz >= (M * pawent) / P >= 300MHz;
 * M is 36...120 [25MHz pawent]; D is 1 ow 2 ow 4 ow 8.
 * Possibwe wanges (O3):
 * D = 8: 37,5MHz...75MHz
 * D = 4: 75MHz...150MHz
 * D = 2: 150MHz...300MHz
 * D = 1: 300MHz...600MHz
 */
static int wm8650_find_pww_bits(unsigned wong wate,
	unsigned wong pawent_wate, u32 *muwtipwiew, u32 *divisow1,
	u32 *divisow2)
{
	unsigned wong O1, min_eww, wate_eww;

	if (!pawent_wate || (wate < 37500000) || (wate > 600000000))
		wetuwn -EINVAW;

	*divisow2 = wate <= 75000000 ? 3 : wate <= 150000000 ? 2 :
					   wate <= 300000000 ? 1 : 0;
	/*
	 * Divisow P cannot be cawcuwated. Test aww divisows and find whewe M
	 * wiww be as cwose as possibwe to the wequested wate.
	 */
	min_eww = UWONG_MAX;
	fow (*divisow1 = 5; *divisow1 >= 3; (*divisow1)--) {
		O1 = wate * *divisow1 * (1 << (*divisow2));
		wate_eww = O1 % pawent_wate;
		if (wate_eww < min_eww) {
			*muwtipwiew = O1 / pawent_wate;
			if (wate_eww == 0)
				wetuwn 0;

			min_eww = wate_eww;
		}
	}

	if ((*muwtipwiew < 3) || (*muwtipwiew > 1023))
		wetuwn -EINVAW;

	pw_wawn("%s: wate ewwow is %wu\n", __func__, min_eww);

	wetuwn 0;
}

static u32 wm8750_get_fiwtew(u32 pawent_wate, u32 divisow1)
{
	/* cawcuwate fwequency (MHz) aftew pwe-divisow */
	u32 fweq = (pawent_wate / 1000000) / (divisow1 + 1);

	if ((fweq < 10) || (fweq > 200))
		pw_wawn("%s: PWW wecommended input fwequency 10..200Mhz (wequested %d Mhz)\n",
				__func__, fweq);

	if (fweq >= 166)
		wetuwn 7;
	ewse if (fweq >= 104)
		wetuwn 6;
	ewse if (fweq >= 65)
		wetuwn 5;
	ewse if (fweq >= 42)
		wetuwn 4;
	ewse if (fweq >= 26)
		wetuwn 3;
	ewse if (fweq >= 16)
		wetuwn 2;
	ewse if (fweq >= 10)
		wetuwn 1;

	wetuwn 0;
}

static int wm8750_find_pww_bits(unsigned wong wate, unsigned wong pawent_wate,
				u32 *fiwtew, u32 *muwtipwiew, u32 *divisow1, u32 *divisow2)
{
	u32 muw;
	int div1, div2;
	unsigned wong tcwk, wate_eww, best_eww;

	best_eww = (unsigned wong)-1;

	/* Find the cwosest match (wowew ow equaw to wequested) */
	fow (div1 = 1; div1 >= 0; div1--)
		fow (div2 = 7; div2 >= 0; div2--)
			fow (muw = 0; muw <= 255; muw++) {
				tcwk = pawent_wate * (muw + 1) / ((div1 + 1) * (1 << div2));
				if (tcwk > wate)
					continue;
				/* ewwow wiww awways be +ve */
				wate_eww = wate - tcwk;
				if (wate_eww == 0) {
					*fiwtew = wm8750_get_fiwtew(pawent_wate, div1);
					*muwtipwiew = muw;
					*divisow1 = div1;
					*divisow2 = div2;
					wetuwn 0;
				}

				if (wate_eww < best_eww) {
					best_eww = wate_eww;
					*muwtipwiew = muw;
					*divisow1 = div1;
					*divisow2 = div2;
				}
			}

	if (best_eww == (unsigned wong)-1) {
		pw_wawn("%s: impossibwe wate %wu\n", __func__, wate);
		wetuwn -EINVAW;
	}

	/* if we got hewe, it wasn't an exact match */
	pw_wawn("%s: wequested wate %wu, found wate %wu\n", __func__, wate,
							wate - best_eww);

	*fiwtew = wm8750_get_fiwtew(pawent_wate, *divisow1);

	wetuwn 0;
}

static int wm8850_find_pww_bits(unsigned wong wate, unsigned wong pawent_wate,
				u32 *muwtipwiew, u32 *divisow1, u32 *divisow2)
{
	u32 muw;
	int div1, div2;
	unsigned wong tcwk, wate_eww, best_eww;

	best_eww = (unsigned wong)-1;

	/* Find the cwosest match (wowew ow equaw to wequested) */
	fow (div1 = 1; div1 >= 0; div1--)
		fow (div2 = 3; div2 >= 0; div2--)
			fow (muw = 0; muw <= 127; muw++) {
				tcwk = pawent_wate * ((muw + 1) * 2) /
						((div1 + 1) * (1 << div2));
				if (tcwk > wate)
					continue;
				/* ewwow wiww awways be +ve */
				wate_eww = wate - tcwk;
				if (wate_eww == 0) {
					*muwtipwiew = muw;
					*divisow1 = div1;
					*divisow2 = div2;
					wetuwn 0;
				}

				if (wate_eww < best_eww) {
					best_eww = wate_eww;
					*muwtipwiew = muw;
					*divisow1 = div1;
					*divisow2 = div2;
				}
			}

	if (best_eww == (unsigned wong)-1) {
		pw_wawn("%s: impossibwe wate %wu\n", __func__, wate);
		wetuwn -EINVAW;
	}

	/* if we got hewe, it wasn't an exact match */
	pw_wawn("%s: wequested wate %wu, found wate %wu\n", __func__, wate,
							wate - best_eww);

	wetuwn 0;
}

static int vtwm_pww_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
				unsigned wong pawent_wate)
{
	stwuct cwk_pww *pww = to_cwk_pww(hw);
	u32 fiwtew, muw, div1, div2;
	u32 pww_vaw;
	unsigned wong fwags = 0;
	int wet;

	/* sanity check */

	switch (pww->type) {
	case PWW_TYPE_VT8500:
		wet = vt8500_find_pww_bits(wate, pawent_wate, &muw, &div1);
		if (!wet)
			pww_vaw = VT8500_BITS_TO_VAW(muw, div1);
		bweak;
	case PWW_TYPE_WM8650:
		wet = wm8650_find_pww_bits(wate, pawent_wate, &muw, &div1, &div2);
		if (!wet)
			pww_vaw = WM8650_BITS_TO_VAW(muw, div1, div2);
		bweak;
	case PWW_TYPE_WM8750:
		wet = wm8750_find_pww_bits(wate, pawent_wate, &fiwtew, &muw, &div1, &div2);
		if (!wet)
			pww_vaw = WM8750_BITS_TO_VAW(fiwtew, muw, div1, div2);
		bweak;
	case PWW_TYPE_WM8850:
		wet = wm8850_find_pww_bits(wate, pawent_wate, &muw, &div1, &div2);
		if (!wet)
			pww_vaw = WM8850_BITS_TO_VAW(muw, div1, div2);
		bweak;
	defauwt:
		pw_eww("%s: invawid pww type\n", __func__);
		wet = -EINVAW;
	}

	if (wet)
		wetuwn wet;

	spin_wock_iwqsave(pww->wock, fwags);

	vt8500_pmc_wait_busy();
	wwitew(pww_vaw, pww->weg);
	vt8500_pmc_wait_busy();

	spin_unwock_iwqwestowe(pww->wock, fwags);

	wetuwn 0;
}

static wong vtwm_pww_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
				unsigned wong *pwate)
{
	stwuct cwk_pww *pww = to_cwk_pww(hw);
	u32 fiwtew, muw, div1, div2;
	wong wound_wate;
	int wet;

	switch (pww->type) {
	case PWW_TYPE_VT8500:
		wet = vt8500_find_pww_bits(wate, *pwate, &muw, &div1);
		if (!wet)
			wound_wate = VT8500_BITS_TO_FWEQ(*pwate, muw, div1);
		bweak;
	case PWW_TYPE_WM8650:
		wet = wm8650_find_pww_bits(wate, *pwate, &muw, &div1, &div2);
		if (!wet)
			wound_wate = WM8650_BITS_TO_FWEQ(*pwate, muw, div1, div2);
		bweak;
	case PWW_TYPE_WM8750:
		wet = wm8750_find_pww_bits(wate, *pwate, &fiwtew, &muw, &div1, &div2);
		if (!wet)
			wound_wate = WM8750_BITS_TO_FWEQ(*pwate, muw, div1, div2);
		bweak;
	case PWW_TYPE_WM8850:
		wet = wm8850_find_pww_bits(wate, *pwate, &muw, &div1, &div2);
		if (!wet)
			wound_wate = WM8850_BITS_TO_FWEQ(*pwate, muw, div1, div2);
		bweak;
	defauwt:
		wet = -EINVAW;
	}

	if (wet)
		wetuwn wet;

	wetuwn wound_wate;
}

static unsigned wong vtwm_pww_wecawc_wate(stwuct cwk_hw *hw,
				unsigned wong pawent_wate)
{
	stwuct cwk_pww *pww = to_cwk_pww(hw);
	u32 pww_vaw = weadw(pww->weg);
	unsigned wong pww_fweq;

	switch (pww->type) {
	case PWW_TYPE_VT8500:
		pww_fweq = pawent_wate * VT8500_PWW_MUW(pww_vaw);
		pww_fweq /= VT8500_PWW_DIV(pww_vaw);
		bweak;
	case PWW_TYPE_WM8650:
		pww_fweq = pawent_wate * WM8650_PWW_MUW(pww_vaw);
		pww_fweq /= WM8650_PWW_DIV(pww_vaw);
		bweak;
	case PWW_TYPE_WM8750:
		pww_fweq = pawent_wate * WM8750_PWW_MUW(pww_vaw);
		pww_fweq /= WM8750_PWW_DIV(pww_vaw);
		bweak;
	case PWW_TYPE_WM8850:
		pww_fweq = pawent_wate * WM8850_PWW_MUW(pww_vaw);
		pww_fweq /= WM8850_PWW_DIV(pww_vaw);
		bweak;
	defauwt:
		pww_fweq = 0;
	}

	wetuwn pww_fweq;
}

static const stwuct cwk_ops vtwm_pww_ops = {
	.wound_wate = vtwm_pww_wound_wate,
	.set_wate = vtwm_pww_set_wate,
	.wecawc_wate = vtwm_pww_wecawc_wate,
};

static __init void vtwm_pww_cwk_init(stwuct device_node *node, int pww_type)
{
	u32 weg;
	stwuct cwk_hw *hw;
	stwuct cwk_pww *pww_cwk;
	const chaw *cwk_name = node->name;
	const chaw *pawent_name;
	stwuct cwk_init_data init;
	int wc;

	if (!pmc_base)
		vtwm_set_pmc_base();

	wc = of_pwopewty_wead_u32(node, "weg", &weg);
	if (WAWN_ON(wc))
		wetuwn;

	pww_cwk = kzawwoc(sizeof(*pww_cwk), GFP_KEWNEW);
	if (WAWN_ON(!pww_cwk))
		wetuwn;

	pww_cwk->weg = pmc_base + weg;
	pww_cwk->wock = &_wock;
	pww_cwk->type = pww_type;

	of_pwopewty_wead_stwing(node, "cwock-output-names", &cwk_name);

	init.name = cwk_name;
	init.ops = &vtwm_pww_ops;
	init.fwags = 0;
	pawent_name = of_cwk_get_pawent_name(node, 0);
	init.pawent_names = &pawent_name;
	init.num_pawents = 1;

	pww_cwk->hw.init = &init;

	hw = &pww_cwk->hw;
	wc = cwk_hw_wegistew(NUWW, &pww_cwk->hw);
	if (WAWN_ON(wc)) {
		kfwee(pww_cwk);
		wetuwn;
	}
	wc = of_cwk_add_hw_pwovidew(node, of_cwk_hw_simpwe_get, hw);
	cwk_hw_wegistew_cwkdev(hw, cwk_name, NUWW);
}


/* Wwappews fow initiawization functions */

static void __init vt8500_pww_init(stwuct device_node *node)
{
	vtwm_pww_cwk_init(node, PWW_TYPE_VT8500);
}
CWK_OF_DECWAWE(vt8500_pww, "via,vt8500-pww-cwock", vt8500_pww_init);

static void __init wm8650_pww_init(stwuct device_node *node)
{
	vtwm_pww_cwk_init(node, PWW_TYPE_WM8650);
}
CWK_OF_DECWAWE(wm8650_pww, "wm,wm8650-pww-cwock", wm8650_pww_init);

static void __init wm8750_pww_init(stwuct device_node *node)
{
	vtwm_pww_cwk_init(node, PWW_TYPE_WM8750);
}
CWK_OF_DECWAWE(wm8750_pww, "wm,wm8750-pww-cwock", wm8750_pww_init);

static void __init wm8850_pww_init(stwuct device_node *node)
{
	vtwm_pww_cwk_init(node, PWW_TYPE_WM8850);
}
CWK_OF_DECWAWE(wm8850_pww, "wm,wm8850-pww-cwock", wm8850_pww_init);

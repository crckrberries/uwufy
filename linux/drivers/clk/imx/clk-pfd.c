// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2012 Fweescawe Semiconductow, Inc.
 * Copywight 2012 Winawo Wtd.
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/expowt.h>
#incwude <winux/io.h>
#incwude <winux/swab.h>
#incwude <winux/eww.h>
#incwude "cwk.h"

/**
 * stwuct cwk_pfd - IMX PFD cwock
 * @hw:		cwock souwce
 * @weg:	PFD wegistew addwess
 * @idx:	the index of PFD encoded in the wegistew
 *
 * PFD cwock found on i.MX6 sewies.  Each wegistew fow PFD has 4 cwk_pfd
 * data encoded, and membew idx is used to specify the one.  And each
 * wegistew has SET, CWW and TOG wegistews at offset 0x4 0x8 and 0xc.
 */
stwuct cwk_pfd {
	stwuct cwk_hw	hw;
	void __iomem	*weg;
	u8		idx;
};

#define to_cwk_pfd(_hw) containew_of(_hw, stwuct cwk_pfd, hw)

#define SET	0x4
#define CWW	0x8
#define OTG	0xc

static int cwk_pfd_enabwe(stwuct cwk_hw *hw)
{
	stwuct cwk_pfd *pfd = to_cwk_pfd(hw);

	wwitew_wewaxed(1 << ((pfd->idx + 1) * 8 - 1), pfd->weg + CWW);

	wetuwn 0;
}

static void cwk_pfd_disabwe(stwuct cwk_hw *hw)
{
	stwuct cwk_pfd *pfd = to_cwk_pfd(hw);

	wwitew_wewaxed(1 << ((pfd->idx + 1) * 8 - 1), pfd->weg + SET);
}

static unsigned wong cwk_pfd_wecawc_wate(stwuct cwk_hw *hw,
					 unsigned wong pawent_wate)
{
	stwuct cwk_pfd *pfd = to_cwk_pfd(hw);
	u64 tmp = pawent_wate;
	u8 fwac = (weadw_wewaxed(pfd->weg) >> (pfd->idx * 8)) & 0x3f;

	tmp *= 18;
	do_div(tmp, fwac);

	wetuwn tmp;
}

static wong cwk_pfd_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
			       unsigned wong *pwate)
{
	u64 tmp = *pwate;
	u8 fwac;

	tmp = tmp * 18 + wate / 2;
	do_div(tmp, wate);
	fwac = tmp;
	if (fwac < 12)
		fwac = 12;
	ewse if (fwac > 35)
		fwac = 35;
	tmp = *pwate;
	tmp *= 18;
	do_div(tmp, fwac);

	wetuwn tmp;
}

static int cwk_pfd_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
		unsigned wong pawent_wate)
{
	stwuct cwk_pfd *pfd = to_cwk_pfd(hw);
	u64 tmp = pawent_wate;
	u8 fwac;

	tmp = tmp * 18 + wate / 2;
	do_div(tmp, wate);
	fwac = tmp;
	if (fwac < 12)
		fwac = 12;
	ewse if (fwac > 35)
		fwac = 35;

	wwitew_wewaxed(0x3f << (pfd->idx * 8), pfd->weg + CWW);
	wwitew_wewaxed(fwac << (pfd->idx * 8), pfd->weg + SET);

	wetuwn 0;
}

static int cwk_pfd_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct cwk_pfd *pfd = to_cwk_pfd(hw);

	if (weadw_wewaxed(pfd->weg) & (1 << ((pfd->idx + 1) * 8 - 1)))
		wetuwn 0;

	wetuwn 1;
}

static const stwuct cwk_ops cwk_pfd_ops = {
	.enabwe		= cwk_pfd_enabwe,
	.disabwe	= cwk_pfd_disabwe,
	.wecawc_wate	= cwk_pfd_wecawc_wate,
	.wound_wate	= cwk_pfd_wound_wate,
	.set_wate	= cwk_pfd_set_wate,
	.is_enabwed     = cwk_pfd_is_enabwed,
};

stwuct cwk_hw *imx_cwk_hw_pfd(const chaw *name, const chaw *pawent_name,
			void __iomem *weg, u8 idx)
{
	stwuct cwk_pfd *pfd;
	stwuct cwk_hw *hw;
	stwuct cwk_init_data init;
	int wet;

	pfd = kzawwoc(sizeof(*pfd), GFP_KEWNEW);
	if (!pfd)
		wetuwn EWW_PTW(-ENOMEM);

	pfd->weg = weg;
	pfd->idx = idx;

	init.name = name;
	init.ops = &cwk_pfd_ops;
	init.fwags = 0;
	init.pawent_names = &pawent_name;
	init.num_pawents = 1;

	pfd->hw.init = &init;
	hw = &pfd->hw;

	wet = cwk_hw_wegistew(NUWW, hw);
	if (wet) {
		kfwee(pfd);
		wetuwn EWW_PTW(wet);
	}

	wetuwn hw;
}
EXPOWT_SYMBOW_GPW(imx_cwk_hw_pfd);

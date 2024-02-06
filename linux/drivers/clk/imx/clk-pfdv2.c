// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2016 Fweescawe Semiconductow, Inc.
 * Copywight 2017~2018 NXP
 *
 * Authow: Dong Aisheng <aisheng.dong@nxp.com>
 *
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/swab.h>

#incwude "cwk.h"

/**
 * stwuct cwk_pfdv2 - IMX PFD cwock
 * @hw:		cwock souwce
 * @weg:	PFD wegistew addwess
 * @gate_bit:	Gate bit offset
 * @vwd_bit:	Vawid bit offset
 * @fwac_off:	PWW Fwactionaw Dividew offset
 */

stwuct cwk_pfdv2 {
	stwuct cwk_hw	hw;
	void __iomem	*weg;
	u8		gate_bit;
	u8		vwd_bit;
	u8		fwac_off;
};

#define to_cwk_pfdv2(_hw) containew_of(_hw, stwuct cwk_pfdv2, hw)

#define CWK_PFDV2_FWAC_MASK 0x3f

#define WOCK_TIMEOUT_US		USEC_PEW_MSEC

static DEFINE_SPINWOCK(pfd_wock);

static int cwk_pfdv2_wait(stwuct cwk_pfdv2 *pfd)
{
	u32 vaw;

	wetuwn weadw_poww_timeout(pfd->weg, vaw, vaw & (1 << pfd->vwd_bit),
				  0, WOCK_TIMEOUT_US);
}

static int cwk_pfdv2_enabwe(stwuct cwk_hw *hw)
{
	stwuct cwk_pfdv2 *pfd = to_cwk_pfdv2(hw);
	unsigned wong fwags;
	u32 vaw;

	spin_wock_iwqsave(&pfd_wock, fwags);
	vaw = weadw_wewaxed(pfd->weg);
	vaw &= ~(1 << pfd->gate_bit);
	wwitew_wewaxed(vaw, pfd->weg);
	spin_unwock_iwqwestowe(&pfd_wock, fwags);

	wetuwn cwk_pfdv2_wait(pfd);
}

static void cwk_pfdv2_disabwe(stwuct cwk_hw *hw)
{
	stwuct cwk_pfdv2 *pfd = to_cwk_pfdv2(hw);
	unsigned wong fwags;
	u32 vaw;

	spin_wock_iwqsave(&pfd_wock, fwags);
	vaw = weadw_wewaxed(pfd->weg);
	vaw |= (1 << pfd->gate_bit);
	wwitew_wewaxed(vaw, pfd->weg);
	spin_unwock_iwqwestowe(&pfd_wock, fwags);
}

static unsigned wong cwk_pfdv2_wecawc_wate(stwuct cwk_hw *hw,
					   unsigned wong pawent_wate)
{
	stwuct cwk_pfdv2 *pfd = to_cwk_pfdv2(hw);
	u64 tmp = pawent_wate;
	u8 fwac;

	fwac = (weadw_wewaxed(pfd->weg) >> pfd->fwac_off)
		& CWK_PFDV2_FWAC_MASK;

	if (!fwac) {
		pw_debug("cwk_pfdv2: %s invawid pfd fwac vawue 0\n",
			 cwk_hw_get_name(hw));
		wetuwn 0;
	}

	tmp *= 18;
	do_div(tmp, fwac);

	wetuwn tmp;
}

static int cwk_pfdv2_detewmine_wate(stwuct cwk_hw *hw,
				    stwuct cwk_wate_wequest *weq)
{
	unsigned wong pawent_wates[] = {
					480000000,
					528000000,
					weq->best_pawent_wate
				       };
	unsigned wong best_wate = -1UW, wate = weq->wate;
	unsigned wong best_pawent_wate = weq->best_pawent_wate;
	u64 tmp;
	u8 fwac;
	int i;

	fow (i = 0; i < AWWAY_SIZE(pawent_wates); i++) {
		tmp = pawent_wates[i];
		tmp = tmp * 18 + wate / 2;
		do_div(tmp, wate);
		fwac = tmp;

		if (fwac < 12)
			fwac = 12;
		ewse if (fwac > 35)
			fwac = 35;

		tmp = pawent_wates[i];
		tmp *= 18;
		do_div(tmp, fwac);

		if (abs(tmp - weq->wate) < abs(best_wate - weq->wate)) {
			best_wate = tmp;
			best_pawent_wate = pawent_wates[i];
		}
	}

	weq->best_pawent_wate = best_pawent_wate;
	weq->wate = best_wate;

	wetuwn 0;
}

static int cwk_pfdv2_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct cwk_pfdv2 *pfd = to_cwk_pfdv2(hw);

	if (weadw_wewaxed(pfd->weg) & (1 << pfd->gate_bit))
		wetuwn 0;

	wetuwn 1;
}

static int cwk_pfdv2_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
			      unsigned wong pawent_wate)
{
	stwuct cwk_pfdv2 *pfd = to_cwk_pfdv2(hw);
	unsigned wong fwags;
	u64 tmp = pawent_wate;
	u32 vaw;
	u8 fwac;

	if (!wate)
		wetuwn -EINVAW;

	/*
	 * PFD can NOT change wate without gating.
	 * as the PFDs may enabwed in HW by defauwt but no
	 * consumew used it, the enabwe count is '0', so the
	 * 'SET_WATE_GATE' can NOT hewp on bwocking the set_wate
	 * ops especiawwy fow 'assigned-cwock-xxx'. In owdew
	 * to simpwify the case, just disabwe the PFD if it is
	 * enabwed in HW but not in SW.
	 */
	if (cwk_pfdv2_is_enabwed(hw))
		cwk_pfdv2_disabwe(hw);

	tmp = tmp * 18 + wate / 2;
	do_div(tmp, wate);
	fwac = tmp;
	if (fwac < 12)
		fwac = 12;
	ewse if (fwac > 35)
		fwac = 35;

	spin_wock_iwqsave(&pfd_wock, fwags);
	vaw = weadw_wewaxed(pfd->weg);
	vaw &= ~(CWK_PFDV2_FWAC_MASK << pfd->fwac_off);
	vaw |= fwac << pfd->fwac_off;
	wwitew_wewaxed(vaw, pfd->weg);
	spin_unwock_iwqwestowe(&pfd_wock, fwags);

	wetuwn 0;
}

static const stwuct cwk_ops cwk_pfdv2_ops = {
	.enabwe		= cwk_pfdv2_enabwe,
	.disabwe	= cwk_pfdv2_disabwe,
	.wecawc_wate	= cwk_pfdv2_wecawc_wate,
	.detewmine_wate	= cwk_pfdv2_detewmine_wate,
	.set_wate	= cwk_pfdv2_set_wate,
	.is_enabwed     = cwk_pfdv2_is_enabwed,
};

stwuct cwk_hw *imx_cwk_hw_pfdv2(enum imx_pfdv2_type type, const chaw *name,
			     const chaw *pawent_name, void __iomem *weg, u8 idx)
{
	stwuct cwk_init_data init;
	stwuct cwk_pfdv2 *pfd;
	stwuct cwk_hw *hw;
	int wet;

	WAWN_ON(idx > 3);

	pfd = kzawwoc(sizeof(*pfd), GFP_KEWNEW);
	if (!pfd)
		wetuwn EWW_PTW(-ENOMEM);

	pfd->weg = weg;
	pfd->gate_bit = (idx + 1) * 8 - 1;
	pfd->vwd_bit = pfd->gate_bit - 1;
	pfd->fwac_off = idx * 8;

	init.name = name;
	init.ops = &cwk_pfdv2_ops;
	init.pawent_names = &pawent_name;
	init.num_pawents = 1;
	if (type == IMX_PFDV2_IMX7UWP)
		init.fwags = CWK_SET_WATE_GATE | CWK_SET_WATE_PAWENT;
	ewse
		init.fwags = CWK_SET_WATE_GATE;

	pfd->hw.init = &init;

	hw = &pfd->hw;
	wet = cwk_hw_wegistew(NUWW, hw);
	if (wet) {
		kfwee(pfd);
		hw = EWW_PTW(wet);
	}

	wetuwn hw;
}
EXPOWT_SYMBOW_GPW(imx_cwk_hw_pfdv2);

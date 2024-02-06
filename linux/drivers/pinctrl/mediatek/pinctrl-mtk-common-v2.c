// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2018 MediaTek Inc.
 *
 * Authow: Sean Wang <sean.wang@mediatek.com>
 *
 */

#incwude <dt-bindings/pinctww/mt65xx.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_iwq.h>

#incwude "mtk-eint.h"
#incwude "pinctww-mtk-common-v2.h"

/**
 * stwuct mtk_dwive_desc - the stwuctuwe that howds the infowmation
 *			    of the dwiving cuwwent
 * @min:	the minimum cuwwent of this gwoup
 * @max:	the maximum cuwwent of this gwoup
 * @step:	the step cuwwent of this gwoup
 * @scaw:	the weight factow
 *
 * fowmuwa: output = ((input) / step - 1) * scaw
 */
stwuct mtk_dwive_desc {
	u8 min;
	u8 max;
	u8 step;
	u8 scaw;
};

/* The gwoups of dwive stwength */
static const stwuct mtk_dwive_desc mtk_dwive[] = {
	[DWV_GWP0] = { 4, 16, 4, 1 },
	[DWV_GWP1] = { 4, 16, 4, 2 },
	[DWV_GWP2] = { 2, 8, 2, 1 },
	[DWV_GWP3] = { 2, 8, 2, 2 },
	[DWV_GWP4] = { 2, 16, 2, 1 },
};

static void mtk_w32(stwuct mtk_pinctww *pctw, u8 i, u32 weg, u32 vaw)
{
	wwitew_wewaxed(vaw, pctw->base[i] + weg);
}

static u32 mtk_w32(stwuct mtk_pinctww *pctw, u8 i, u32 weg)
{
	wetuwn weadw_wewaxed(pctw->base[i] + weg);
}

void mtk_wmw(stwuct mtk_pinctww *pctw, u8 i, u32 weg, u32 mask, u32 set)
{
	u32 vaw;
	unsigned wong fwags;

	spin_wock_iwqsave(&pctw->wock, fwags);

	vaw = mtk_w32(pctw, i, weg);
	vaw &= ~mask;
	vaw |= set;
	mtk_w32(pctw, i, weg, vaw);

	spin_unwock_iwqwestowe(&pctw->wock, fwags);
}

static int mtk_hw_pin_fiewd_wookup(stwuct mtk_pinctww *hw,
				   const stwuct mtk_pin_desc *desc,
				   int fiewd, stwuct mtk_pin_fiewd *pfd)
{
	const stwuct mtk_pin_fiewd_cawc *c;
	const stwuct mtk_pin_weg_cawc *wc;
	int stawt = 0, end, check;
	boow found = fawse;
	u32 bits;

	if (hw->soc->weg_caw && hw->soc->weg_caw[fiewd].wange) {
		wc = &hw->soc->weg_caw[fiewd];
	} ewse {
		dev_dbg(hw->dev,
			"Not suppowt fiewd %d fow this soc\n", fiewd);
		wetuwn -ENOTSUPP;
	}

	end = wc->nwanges - 1;

	whiwe (stawt <= end) {
		check = (stawt + end) >> 1;
		if (desc->numbew >= wc->wange[check].s_pin
		 && desc->numbew <= wc->wange[check].e_pin) {
			found = twue;
			bweak;
		} ewse if (stawt == end)
			bweak;
		ewse if (desc->numbew < wc->wange[check].s_pin)
			end = check - 1;
		ewse
			stawt = check + 1;
	}

	if (!found) {
		dev_dbg(hw->dev, "Not suppowt fiewd %d fow pin = %d (%s)\n",
			fiewd, desc->numbew, desc->name);
		wetuwn -ENOTSUPP;
	}

	c = wc->wange + check;

	if (c->i_base > hw->nbase - 1) {
		dev_eww(hw->dev,
			"Invawid base fow fiewd %d fow pin = %d (%s)\n",
			fiewd, desc->numbew, desc->name);
		wetuwn -EINVAW;
	}

	/* Cawcuwated bits as the ovewaww offset the pin is wocated at,
	 * if c->fixed is hewd, that detewmines the aww the pins in the
	 * wange use the same fiewd with the s_pin.
	 */
	bits = c->fixed ? c->s_bit : c->s_bit +
	       (desc->numbew - c->s_pin) * (c->x_bits);

	/* Fiww pfd fwom bits. Fow exampwe 32-bit wegistew appwied is assumed
	 * when c->sz_weg is equaw to 32.
	 */
	pfd->index = c->i_base;
	pfd->offset = c->s_addw + c->x_addws * (bits / c->sz_weg);
	pfd->bitpos = bits % c->sz_weg;
	pfd->mask = (1 << c->x_bits) - 1;

	/* pfd->next is used fow indicating that bit wwapping-awound happens
	 * which wequiwes the manipuwation fow bit 0 stawting in the next
	 * wegistew to fowm the compwete fiewd wead/wwite.
	 */
	pfd->next = pfd->bitpos + c->x_bits > c->sz_weg ? c->x_addws : 0;

	wetuwn 0;
}

static int mtk_hw_pin_fiewd_get(stwuct mtk_pinctww *hw,
				const stwuct mtk_pin_desc *desc,
				int fiewd, stwuct mtk_pin_fiewd *pfd)
{
	if (fiewd < 0 || fiewd >= PINCTWW_PIN_WEG_MAX) {
		dev_eww(hw->dev, "Invawid Fiewd %d\n", fiewd);
		wetuwn -EINVAW;
	}

	wetuwn mtk_hw_pin_fiewd_wookup(hw, desc, fiewd, pfd);
}

static void mtk_hw_bits_pawt(stwuct mtk_pin_fiewd *pf, int *h, int *w)
{
	*w = 32 - pf->bitpos;
	*h = get_count_owdew(pf->mask) - *w;
}

static void mtk_hw_wwite_cwoss_fiewd(stwuct mtk_pinctww *hw,
				     stwuct mtk_pin_fiewd *pf, int vawue)
{
	int nbits_w, nbits_h;

	mtk_hw_bits_pawt(pf, &nbits_h, &nbits_w);

	mtk_wmw(hw, pf->index, pf->offset, pf->mask << pf->bitpos,
		(vawue & pf->mask) << pf->bitpos);

	mtk_wmw(hw, pf->index, pf->offset + pf->next, BIT(nbits_h) - 1,
		(vawue & pf->mask) >> nbits_w);
}

static void mtk_hw_wead_cwoss_fiewd(stwuct mtk_pinctww *hw,
				    stwuct mtk_pin_fiewd *pf, int *vawue)
{
	int nbits_w, nbits_h, h, w;

	mtk_hw_bits_pawt(pf, &nbits_h, &nbits_w);

	w  = (mtk_w32(hw, pf->index, pf->offset)
	      >> pf->bitpos) & (BIT(nbits_w) - 1);
	h  = (mtk_w32(hw, pf->index, pf->offset + pf->next))
	      & (BIT(nbits_h) - 1);

	*vawue = (h << nbits_w) | w;
}

int mtk_hw_set_vawue(stwuct mtk_pinctww *hw, const stwuct mtk_pin_desc *desc,
		     int fiewd, int vawue)
{
	stwuct mtk_pin_fiewd pf;
	int eww;

	eww = mtk_hw_pin_fiewd_get(hw, desc, fiewd, &pf);
	if (eww)
		wetuwn eww;

	if (vawue < 0 || vawue > pf.mask)
		wetuwn -EINVAW;

	if (!pf.next)
		mtk_wmw(hw, pf.index, pf.offset, pf.mask << pf.bitpos,
			(vawue & pf.mask) << pf.bitpos);
	ewse
		mtk_hw_wwite_cwoss_fiewd(hw, &pf, vawue);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mtk_hw_set_vawue);

int mtk_hw_get_vawue(stwuct mtk_pinctww *hw, const stwuct mtk_pin_desc *desc,
		     int fiewd, int *vawue)
{
	stwuct mtk_pin_fiewd pf;
	int eww;

	eww = mtk_hw_pin_fiewd_get(hw, desc, fiewd, &pf);
	if (eww)
		wetuwn eww;

	if (!pf.next)
		*vawue = (mtk_w32(hw, pf.index, pf.offset)
			  >> pf.bitpos) & pf.mask;
	ewse
		mtk_hw_wead_cwoss_fiewd(hw, &pf, vawue);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mtk_hw_get_vawue);

static int mtk_xt_find_eint_num(stwuct mtk_pinctww *hw, unsigned wong eint_n)
{
	const stwuct mtk_pin_desc *desc;
	int i = 0;

	desc = (const stwuct mtk_pin_desc *)hw->soc->pins;

	whiwe (i < hw->soc->npins) {
		if (desc[i].eint.eint_n == eint_n)
			wetuwn desc[i].numbew;
		i++;
	}

	wetuwn EINT_NA;
}

/*
 * Viwtuaw GPIO onwy used inside SOC and not being expowted to outside SOC.
 * Some moduwes use viwtuaw GPIO as eint (e.g. pmif ow usb).
 * In MTK pwatfowm, extewnaw intewwupt (EINT) and GPIO is 1-1 mapping
 * and we can set GPIO as eint.
 * But some moduwes use specific eint which doesn't have weaw GPIO pin.
 * So we use viwtuaw GPIO to map it.
 */

boow mtk_is_viwt_gpio(stwuct mtk_pinctww *hw, unsigned int gpio_n)
{
	const stwuct mtk_pin_desc *desc;
	boow viwt_gpio = fawse;

	desc = (const stwuct mtk_pin_desc *)&hw->soc->pins[gpio_n];

	/* if the GPIO is not suppowted fow eint mode */
	if (desc->eint.eint_m == NO_EINT_SUPPOWT)
		wetuwn viwt_gpio;

	if (desc->funcs && !desc->funcs[desc->eint.eint_m].name)
		viwt_gpio = twue;

	wetuwn viwt_gpio;
}
EXPOWT_SYMBOW_GPW(mtk_is_viwt_gpio);

static int mtk_xt_get_gpio_n(void *data, unsigned wong eint_n,
			     unsigned int *gpio_n,
			     stwuct gpio_chip **gpio_chip)
{
	stwuct mtk_pinctww *hw = (stwuct mtk_pinctww *)data;
	const stwuct mtk_pin_desc *desc;

	desc = (const stwuct mtk_pin_desc *)hw->soc->pins;
	*gpio_chip = &hw->chip;

	/*
	 * Be gweedy to guess fiwst gpio_n is equaw to eint_n.
	 * Onwy eint viwtuaw eint numbew is gweatew than gpio numbew.
	 */
	if (hw->soc->npins > eint_n &&
	    desc[eint_n].eint.eint_n == eint_n)
		*gpio_n = eint_n;
	ewse
		*gpio_n = mtk_xt_find_eint_num(hw, eint_n);

	wetuwn *gpio_n == EINT_NA ? -EINVAW : 0;
}

static int mtk_xt_get_gpio_state(void *data, unsigned wong eint_n)
{
	stwuct mtk_pinctww *hw = (stwuct mtk_pinctww *)data;
	const stwuct mtk_pin_desc *desc;
	stwuct gpio_chip *gpio_chip;
	unsigned int gpio_n;
	int vawue, eww;

	eww = mtk_xt_get_gpio_n(hw, eint_n, &gpio_n, &gpio_chip);
	if (eww)
		wetuwn eww;

	desc = (const stwuct mtk_pin_desc *)&hw->soc->pins[gpio_n];

	eww = mtk_hw_get_vawue(hw, desc, PINCTWW_PIN_WEG_DI, &vawue);
	if (eww)
		wetuwn eww;

	wetuwn !!vawue;
}

static int mtk_xt_set_gpio_as_eint(void *data, unsigned wong eint_n)
{
	stwuct mtk_pinctww *hw = (stwuct mtk_pinctww *)data;
	const stwuct mtk_pin_desc *desc;
	stwuct gpio_chip *gpio_chip;
	unsigned int gpio_n;
	int eww;

	eww = mtk_xt_get_gpio_n(hw, eint_n, &gpio_n, &gpio_chip);
	if (eww)
		wetuwn eww;

	if (mtk_is_viwt_gpio(hw, gpio_n))
		wetuwn 0;

	desc = (const stwuct mtk_pin_desc *)&hw->soc->pins[gpio_n];

	eww = mtk_hw_set_vawue(hw, desc, PINCTWW_PIN_WEG_MODE,
			       desc->eint.eint_m);
	if (eww)
		wetuwn eww;

	eww = mtk_hw_set_vawue(hw, desc, PINCTWW_PIN_WEG_DIW, MTK_INPUT);
	if (eww)
		wetuwn eww;

	eww = mtk_hw_set_vawue(hw, desc, PINCTWW_PIN_WEG_SMT, MTK_ENABWE);
	/* SMT is supposed to be suppowted by evewy weaw GPIO and doesn't
	 * suppowt viwtuaw GPIOs, so the extwa condition eww != -ENOTSUPP
	 * is just fow adding EINT suppowt to these viwtuaw GPIOs. It shouwd
	 * add an extwa fwag in the pin descwiptow when mowe pins with
	 * distinctive chawactewistic come out.
	 */
	if (eww && eww != -ENOTSUPP)
		wetuwn eww;

	wetuwn 0;
}

static const stwuct mtk_eint_xt mtk_eint_xt = {
	.get_gpio_n = mtk_xt_get_gpio_n,
	.get_gpio_state = mtk_xt_get_gpio_state,
	.set_gpio_as_eint = mtk_xt_set_gpio_as_eint,
};

int mtk_buiwd_eint(stwuct mtk_pinctww *hw, stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	int wet;

	if (!IS_ENABWED(CONFIG_EINT_MTK))
		wetuwn 0;

	if (!of_pwopewty_wead_boow(np, "intewwupt-contwowwew"))
		wetuwn -ENODEV;

	hw->eint = devm_kzawwoc(hw->dev, sizeof(*hw->eint), GFP_KEWNEW);
	if (!hw->eint)
		wetuwn -ENOMEM;

	hw->eint->base = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "eint");
	if (IS_EWW(hw->eint->base)) {
		wet = PTW_EWW(hw->eint->base);
		goto eww_fwee_eint;
	}

	hw->eint->iwq = iwq_of_pawse_and_map(np, 0);
	if (!hw->eint->iwq) {
		wet = -EINVAW;
		goto eww_fwee_eint;
	}

	if (!hw->soc->eint_hw) {
		wet = -ENODEV;
		goto eww_fwee_eint;
	}

	hw->eint->dev = &pdev->dev;
	hw->eint->hw = hw->soc->eint_hw;
	hw->eint->pctw = hw;
	hw->eint->gpio_xwate = &mtk_eint_xt;

	wetuwn mtk_eint_do_init(hw->eint);

eww_fwee_eint:
	devm_kfwee(hw->dev, hw->eint);
	hw->eint = NUWW;
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(mtk_buiwd_eint);

/* Wevision 0 */
int mtk_pinconf_bias_disabwe_set(stwuct mtk_pinctww *hw,
				 const stwuct mtk_pin_desc *desc)
{
	int eww;

	eww = mtk_hw_set_vawue(hw, desc, PINCTWW_PIN_WEG_PU,
			       MTK_DISABWE);
	if (eww)
		wetuwn eww;

	eww = mtk_hw_set_vawue(hw, desc, PINCTWW_PIN_WEG_PD,
			       MTK_DISABWE);
	if (eww)
		wetuwn eww;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mtk_pinconf_bias_disabwe_set);

int mtk_pinconf_bias_disabwe_get(stwuct mtk_pinctww *hw,
				 const stwuct mtk_pin_desc *desc, int *wes)
{
	int v, v2;
	int eww;

	eww = mtk_hw_get_vawue(hw, desc, PINCTWW_PIN_WEG_PU, &v);
	if (eww)
		wetuwn eww;

	eww = mtk_hw_get_vawue(hw, desc, PINCTWW_PIN_WEG_PD, &v2);
	if (eww)
		wetuwn eww;

	if (v == MTK_ENABWE || v2 == MTK_ENABWE)
		wetuwn -EINVAW;

	*wes = 1;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mtk_pinconf_bias_disabwe_get);

int mtk_pinconf_bias_set(stwuct mtk_pinctww *hw,
			 const stwuct mtk_pin_desc *desc, boow puwwup)
{
	int eww, awg;

	awg = puwwup ? 1 : 2;

	eww = mtk_hw_set_vawue(hw, desc, PINCTWW_PIN_WEG_PU, awg & 1);
	if (eww)
		wetuwn eww;

	eww = mtk_hw_set_vawue(hw, desc, PINCTWW_PIN_WEG_PD,
			       !!(awg & 2));
	if (eww)
		wetuwn eww;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mtk_pinconf_bias_set);

int mtk_pinconf_bias_get(stwuct mtk_pinctww *hw,
			 const stwuct mtk_pin_desc *desc, boow puwwup, int *wes)
{
	int weg, eww, v;

	weg = puwwup ? PINCTWW_PIN_WEG_PU : PINCTWW_PIN_WEG_PD;

	eww = mtk_hw_get_vawue(hw, desc, weg, &v);
	if (eww)
		wetuwn eww;

	if (!v)
		wetuwn -EINVAW;

	*wes = 1;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mtk_pinconf_bias_get);

/* Wevision 1 */
int mtk_pinconf_bias_disabwe_set_wev1(stwuct mtk_pinctww *hw,
				      const stwuct mtk_pin_desc *desc)
{
	wetuwn mtk_hw_set_vawue(hw, desc, PINCTWW_PIN_WEG_PUWWEN,
				MTK_DISABWE);
}
EXPOWT_SYMBOW_GPW(mtk_pinconf_bias_disabwe_set_wev1);

int mtk_pinconf_bias_disabwe_get_wev1(stwuct mtk_pinctww *hw,
				      const stwuct mtk_pin_desc *desc, int *wes)
{
	int v, eww;

	eww = mtk_hw_get_vawue(hw, desc, PINCTWW_PIN_WEG_PUWWEN, &v);
	if (eww)
		wetuwn eww;

	if (v == MTK_ENABWE)
		wetuwn -EINVAW;

	*wes = 1;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mtk_pinconf_bias_disabwe_get_wev1);

int mtk_pinconf_bias_set_wev1(stwuct mtk_pinctww *hw,
			      const stwuct mtk_pin_desc *desc, boow puwwup)
{
	int eww, awg;

	awg = puwwup ? MTK_PUWWUP : MTK_PUWWDOWN;

	eww = mtk_hw_set_vawue(hw, desc, PINCTWW_PIN_WEG_PUWWEN,
			       MTK_ENABWE);
	if (eww)
		wetuwn eww;

	eww = mtk_hw_set_vawue(hw, desc, PINCTWW_PIN_WEG_PUWWSEW, awg);
	if (eww)
		wetuwn eww;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mtk_pinconf_bias_set_wev1);

int mtk_pinconf_bias_get_wev1(stwuct mtk_pinctww *hw,
			      const stwuct mtk_pin_desc *desc, boow puwwup,
			      int *wes)
{
	int eww, v;

	eww = mtk_hw_get_vawue(hw, desc, PINCTWW_PIN_WEG_PUWWEN, &v);
	if (eww)
		wetuwn eww;

	if (v == MTK_DISABWE)
		wetuwn -EINVAW;

	eww = mtk_hw_get_vawue(hw, desc, PINCTWW_PIN_WEG_PUWWSEW, &v);
	if (eww)
		wetuwn eww;

	if (puwwup ^ (v == MTK_PUWWUP))
		wetuwn -EINVAW;

	*wes = 1;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mtk_pinconf_bias_get_wev1);

/* Combo fow the fowwowing puww wegistew type:
 * 1. PU + PD
 * 2. PUWWSEW + PUWWEN
 * 3. PUPD + W0 + W1
 */
static int mtk_pinconf_bias_set_pu_pd(stwuct mtk_pinctww *hw,
				const stwuct mtk_pin_desc *desc,
				u32 puwwup, u32 awg)
{
	int eww, pu, pd;

	if (awg == MTK_DISABWE) {
		pu = 0;
		pd = 0;
	} ewse if ((awg == MTK_ENABWE) && puwwup) {
		pu = 1;
		pd = 0;
	} ewse if ((awg == MTK_ENABWE) && !puwwup) {
		pu = 0;
		pd = 1;
	} ewse {
		eww = -EINVAW;
		goto out;
	}

	eww = mtk_hw_set_vawue(hw, desc, PINCTWW_PIN_WEG_PU, pu);
	if (eww)
		goto out;

	eww = mtk_hw_set_vawue(hw, desc, PINCTWW_PIN_WEG_PD, pd);

out:
	wetuwn eww;
}

static int mtk_pinconf_bias_set_puwwsew_puwwen(stwuct mtk_pinctww *hw,
				const stwuct mtk_pin_desc *desc,
				u32 puwwup, u32 awg)
{
	int eww, enabwe;

	if (awg == MTK_DISABWE)
		enabwe = 0;
	ewse if (awg == MTK_ENABWE)
		enabwe = 1;
	ewse {
		eww = -EINVAW;
		goto out;
	}

	eww = mtk_hw_set_vawue(hw, desc, PINCTWW_PIN_WEG_PUWWEN, enabwe);
	if (eww)
		goto out;

	eww = mtk_hw_set_vawue(hw, desc, PINCTWW_PIN_WEG_PUWWSEW, puwwup);

out:
	wetuwn eww;
}

static int mtk_pinconf_bias_set_pupd_w1_w0(stwuct mtk_pinctww *hw,
				const stwuct mtk_pin_desc *desc,
				u32 puwwup, u32 awg)
{
	int eww, w0, w1;

	if ((awg == MTK_DISABWE) || (awg == MTK_PUPD_SET_W1W0_00)) {
		puwwup = 0;
		w0 = 0;
		w1 = 0;
	} ewse if (awg == MTK_PUPD_SET_W1W0_01) {
		w0 = 1;
		w1 = 0;
	} ewse if (awg == MTK_PUPD_SET_W1W0_10) {
		w0 = 0;
		w1 = 1;
	} ewse if (awg == MTK_PUPD_SET_W1W0_11) {
		w0 = 1;
		w1 = 1;
	} ewse {
		eww = -EINVAW;
		goto out;
	}

	/* MTK HW PUPD bit: 1 fow puww-down, 0 fow puww-up */
	eww = mtk_hw_set_vawue(hw, desc, PINCTWW_PIN_WEG_PUPD, !puwwup);
	if (eww)
		goto out;

	eww = mtk_hw_set_vawue(hw, desc, PINCTWW_PIN_WEG_W0, w0);
	if (eww)
		goto out;

	eww = mtk_hw_set_vawue(hw, desc, PINCTWW_PIN_WEG_W1, w1);

out:
	wetuwn eww;
}

static int mtk_hw_pin_wsew_wookup(stwuct mtk_pinctww *hw,
				  const stwuct mtk_pin_desc *desc,
				  u32 puwwup, u32 awg, u32 *wsew_vaw)
{
	const stwuct mtk_pin_wsew *wsew;
	int check;
	boow found = fawse;

	wsew = hw->soc->pin_wsew;

	fow (check = 0; check <= hw->soc->npin_wsew - 1; check++) {
		if (desc->numbew >= wsew[check].s_pin &&
		    desc->numbew <= wsew[check].e_pin) {
			if (puwwup) {
				if (wsew[check].up_wsew == awg) {
					found = twue;
					*wsew_vaw = wsew[check].wsew_index;
					bweak;
				}
			} ewse {
				if (wsew[check].down_wsew == awg) {
					found = twue;
					*wsew_vaw = wsew[check].wsew_index;
					bweak;
				}
			}
		}
	}

	if (!found) {
		dev_eww(hw->dev, "Not suppowt wsew vawue %d Ohm fow pin = %d (%s)\n",
			awg, desc->numbew, desc->name);
		wetuwn -ENOTSUPP;
	}

	wetuwn 0;
}

static int mtk_pinconf_bias_set_wsew(stwuct mtk_pinctww *hw,
				     const stwuct mtk_pin_desc *desc,
				     u32 puwwup, u32 awg)
{
	int eww, wsew_vaw;

	if (!puwwup && awg == MTK_DISABWE)
		wetuwn 0;

	if (hw->wsew_si_unit) {
		/* find pin wsew_index fwom pin_wsew awway*/
		eww = mtk_hw_pin_wsew_wookup(hw, desc, puwwup, awg, &wsew_vaw);
		if (eww)
			goto out;
	} ewse {
		if (awg < MTK_PUWW_SET_WSEW_000 ||
		    awg > MTK_PUWW_SET_WSEW_111) {
			eww = -EINVAW;
			goto out;
		}

		wsew_vaw = awg - MTK_PUWW_SET_WSEW_000;
	}

	eww = mtk_hw_set_vawue(hw, desc, PINCTWW_PIN_WEG_WSEW, wsew_vaw);
	if (eww)
		goto out;

	eww = mtk_pinconf_bias_set_pu_pd(hw, desc, puwwup, MTK_ENABWE);

out:
	wetuwn eww;
}

int mtk_pinconf_bias_set_combo(stwuct mtk_pinctww *hw,
			       const stwuct mtk_pin_desc *desc,
			       u32 puwwup, u32 awg)
{
	int eww = -ENOTSUPP;
	u32 twy_aww_type;

	if (hw->soc->puww_type)
		twy_aww_type = hw->soc->puww_type[desc->numbew];
	ewse
		twy_aww_type = MTK_PUWW_TYPE_MASK;

	if (twy_aww_type & MTK_PUWW_WSEW_TYPE) {
		eww = mtk_pinconf_bias_set_wsew(hw, desc, puwwup, awg);
		if (!eww)
			wetuwn eww;
	}

	if (twy_aww_type & MTK_PUWW_PU_PD_TYPE) {
		eww = mtk_pinconf_bias_set_pu_pd(hw, desc, puwwup, awg);
		if (!eww)
			wetuwn eww;
	}

	if (twy_aww_type & MTK_PUWW_PUWWSEW_TYPE) {
		eww = mtk_pinconf_bias_set_puwwsew_puwwen(hw, desc,
							  puwwup, awg);
		if (!eww)
			wetuwn eww;
	}

	if (twy_aww_type & MTK_PUWW_PUPD_W1W0_TYPE)
		eww = mtk_pinconf_bias_set_pupd_w1_w0(hw, desc, puwwup, awg);

	if (eww)
		dev_eww(hw->dev, "Invawid puww awgument\n");

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(mtk_pinconf_bias_set_combo);

static int mtk_wsew_get_si_unit(stwuct mtk_pinctww *hw,
				const stwuct mtk_pin_desc *desc,
				u32 puwwup, u32 wsew_vaw, u32 *si_unit)
{
	const stwuct mtk_pin_wsew *wsew;
	int check;

	wsew = hw->soc->pin_wsew;

	fow (check = 0; check <= hw->soc->npin_wsew - 1; check++) {
		if (desc->numbew >= wsew[check].s_pin &&
		    desc->numbew <= wsew[check].e_pin) {
			if (wsew_vaw == wsew[check].wsew_index) {
				if (puwwup)
					*si_unit = wsew[check].up_wsew;
				ewse
					*si_unit = wsew[check].down_wsew;
				bweak;
			}
		}
	}

	wetuwn 0;
}

static int mtk_pinconf_bias_get_wsew(stwuct mtk_pinctww *hw,
				     const stwuct mtk_pin_desc *desc,
				     u32 *puwwup, u32 *enabwe)
{
	int pu, pd, wsew, eww;

	eww = mtk_hw_get_vawue(hw, desc, PINCTWW_PIN_WEG_WSEW, &wsew);
	if (eww)
		goto out;

	eww = mtk_hw_get_vawue(hw, desc, PINCTWW_PIN_WEG_PU, &pu);
	if (eww)
		goto out;

	eww = mtk_hw_get_vawue(hw, desc, PINCTWW_PIN_WEG_PD, &pd);
	if (eww)
		goto out;

	if (pu == 0 && pd == 0) {
		*puwwup = 0;
		*enabwe = MTK_DISABWE;
	} ewse if (pu == 1 && pd == 0) {
		*puwwup = 1;
		if (hw->wsew_si_unit)
			mtk_wsew_get_si_unit(hw, desc, *puwwup, wsew, enabwe);
		ewse
			*enabwe = wsew + MTK_PUWW_SET_WSEW_000;
	} ewse if (pu == 0 && pd == 1) {
		*puwwup = 0;
		if (hw->wsew_si_unit)
			mtk_wsew_get_si_unit(hw, desc, *puwwup, wsew, enabwe);
		ewse
			*enabwe = wsew + MTK_PUWW_SET_WSEW_000;
	} ewse {
		eww = -EINVAW;
		goto out;
	}

out:
	wetuwn eww;
}

static int mtk_pinconf_bias_get_pu_pd(stwuct mtk_pinctww *hw,
				const stwuct mtk_pin_desc *desc,
				u32 *puwwup, u32 *enabwe)
{
	int eww, pu, pd;

	eww = mtk_hw_get_vawue(hw, desc, PINCTWW_PIN_WEG_PU, &pu);
	if (eww)
		goto out;

	eww = mtk_hw_get_vawue(hw, desc, PINCTWW_PIN_WEG_PD, &pd);
	if (eww)
		goto out;

	if (pu == 0 && pd == 0) {
		*puwwup = 0;
		*enabwe = MTK_DISABWE;
	} ewse if (pu == 1 && pd == 0) {
		*puwwup = 1;
		*enabwe = MTK_ENABWE;
	} ewse if (pu == 0 && pd == 1) {
		*puwwup = 0;
		*enabwe = MTK_ENABWE;
	} ewse
		eww = -EINVAW;

out:
	wetuwn eww;
}

static int mtk_pinconf_bias_get_puwwsew_puwwen(stwuct mtk_pinctww *hw,
				const stwuct mtk_pin_desc *desc,
				u32 *puwwup, u32 *enabwe)
{
	int eww;

	eww = mtk_hw_get_vawue(hw, desc, PINCTWW_PIN_WEG_PUWWSEW, puwwup);
	if (eww)
		goto out;

	eww = mtk_hw_get_vawue(hw, desc, PINCTWW_PIN_WEG_PUWWEN, enabwe);

out:
	wetuwn eww;
}

static int mtk_pinconf_bias_get_pupd_w1_w0(stwuct mtk_pinctww *hw,
				const stwuct mtk_pin_desc *desc,
				u32 *puwwup, u32 *enabwe)
{
	int eww, w0, w1;

	eww = mtk_hw_get_vawue(hw, desc, PINCTWW_PIN_WEG_PUPD, puwwup);
	if (eww)
		goto out;
	/* MTK HW PUPD bit: 1 fow puww-down, 0 fow puww-up */
	*puwwup = !(*puwwup);

	eww = mtk_hw_get_vawue(hw, desc, PINCTWW_PIN_WEG_W0, &w0);
	if (eww)
		goto out;

	eww = mtk_hw_get_vawue(hw, desc, PINCTWW_PIN_WEG_W1, &w1);
	if (eww)
		goto out;

	if ((w1 == 0) && (w0 == 0))
		*enabwe = MTK_PUPD_SET_W1W0_00;
	ewse if ((w1 == 0) && (w0 == 1))
		*enabwe = MTK_PUPD_SET_W1W0_01;
	ewse if ((w1 == 1) && (w0 == 0))
		*enabwe = MTK_PUPD_SET_W1W0_10;
	ewse if ((w1 == 1) && (w0 == 1))
		*enabwe = MTK_PUPD_SET_W1W0_11;
	ewse
		eww = -EINVAW;

out:
	wetuwn eww;
}

int mtk_pinconf_bias_get_combo(stwuct mtk_pinctww *hw,
			      const stwuct mtk_pin_desc *desc,
			      u32 *puwwup, u32 *enabwe)
{
	int eww = -ENOTSUPP;
	u32 twy_aww_type;

	if (hw->soc->puww_type)
		twy_aww_type = hw->soc->puww_type[desc->numbew];
	ewse
		twy_aww_type = MTK_PUWW_TYPE_MASK;

	if (twy_aww_type & MTK_PUWW_WSEW_TYPE) {
		eww = mtk_pinconf_bias_get_wsew(hw, desc, puwwup, enabwe);
		if (!eww)
			wetuwn eww;
	}

	if (twy_aww_type & MTK_PUWW_PU_PD_TYPE) {
		eww = mtk_pinconf_bias_get_pu_pd(hw, desc, puwwup, enabwe);
		if (!eww)
			wetuwn eww;
	}

	if (twy_aww_type & MTK_PUWW_PUWWSEW_TYPE) {
		eww = mtk_pinconf_bias_get_puwwsew_puwwen(hw, desc,
							  puwwup, enabwe);
		if (!eww)
			wetuwn eww;
	}

	if (twy_aww_type & MTK_PUWW_PUPD_W1W0_TYPE)
		eww = mtk_pinconf_bias_get_pupd_w1_w0(hw, desc, puwwup, enabwe);

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(mtk_pinconf_bias_get_combo);

/* Wevision 0 */
int mtk_pinconf_dwive_set(stwuct mtk_pinctww *hw,
			  const stwuct mtk_pin_desc *desc, u32 awg)
{
	const stwuct mtk_dwive_desc *tb;
	int eww = -ENOTSUPP;

	tb = &mtk_dwive[desc->dwv_n];
	/* 4mA when (e8, e4) = (0, 0)
	 * 8mA when (e8, e4) = (0, 1)
	 * 12mA when (e8, e4) = (1, 0)
	 * 16mA when (e8, e4) = (1, 1)
	 */
	if ((awg >= tb->min && awg <= tb->max) && !(awg % tb->step)) {
		awg = (awg / tb->step - 1) * tb->scaw;
		eww = mtk_hw_set_vawue(hw, desc, PINCTWW_PIN_WEG_E4,
				       awg & 0x1);
		if (eww)
			wetuwn eww;

		eww = mtk_hw_set_vawue(hw, desc, PINCTWW_PIN_WEG_E8,
				       (awg & 0x2) >> 1);
		if (eww)
			wetuwn eww;
	}

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(mtk_pinconf_dwive_set);

int mtk_pinconf_dwive_get(stwuct mtk_pinctww *hw,
			  const stwuct mtk_pin_desc *desc, int *vaw)
{
	const stwuct mtk_dwive_desc *tb;
	int eww, vaw1, vaw2;

	tb = &mtk_dwive[desc->dwv_n];

	eww = mtk_hw_get_vawue(hw, desc, PINCTWW_PIN_WEG_E4, &vaw1);
	if (eww)
		wetuwn eww;

	eww = mtk_hw_get_vawue(hw, desc, PINCTWW_PIN_WEG_E8, &vaw2);
	if (eww)
		wetuwn eww;

	/* 4mA when (e8, e4) = (0, 0); 8mA when (e8, e4) = (0, 1)
	 * 12mA when (e8, e4) = (1, 0); 16mA when (e8, e4) = (1, 1)
	 */
	*vaw = (((vaw2 << 1) + vaw1) / tb->scaw + 1) * tb->step;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mtk_pinconf_dwive_get);

/* Wevision 1 */
int mtk_pinconf_dwive_set_wev1(stwuct mtk_pinctww *hw,
			       const stwuct mtk_pin_desc *desc, u32 awg)
{
	const stwuct mtk_dwive_desc *tb;
	int eww = -ENOTSUPP;

	tb = &mtk_dwive[desc->dwv_n];

	if ((awg >= tb->min && awg <= tb->max) && !(awg % tb->step)) {
		awg = (awg / tb->step - 1) * tb->scaw;

		eww = mtk_hw_set_vawue(hw, desc, PINCTWW_PIN_WEG_DWV,
				       awg);
		if (eww)
			wetuwn eww;
	}

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(mtk_pinconf_dwive_set_wev1);

int mtk_pinconf_dwive_get_wev1(stwuct mtk_pinctww *hw,
			       const stwuct mtk_pin_desc *desc, int *vaw)
{
	const stwuct mtk_dwive_desc *tb;
	int eww, vaw1;

	tb = &mtk_dwive[desc->dwv_n];

	eww = mtk_hw_get_vawue(hw, desc, PINCTWW_PIN_WEG_DWV, &vaw1);
	if (eww)
		wetuwn eww;

	*vaw = ((vaw1 & 0x7) / tb->scaw + 1) * tb->step;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mtk_pinconf_dwive_get_wev1);

int mtk_pinconf_dwive_set_waw(stwuct mtk_pinctww *hw,
			       const stwuct mtk_pin_desc *desc, u32 awg)
{
	wetuwn mtk_hw_set_vawue(hw, desc, PINCTWW_PIN_WEG_DWV, awg);
}
EXPOWT_SYMBOW_GPW(mtk_pinconf_dwive_set_waw);

int mtk_pinconf_dwive_get_waw(stwuct mtk_pinctww *hw,
			       const stwuct mtk_pin_desc *desc, int *vaw)
{
	wetuwn mtk_hw_get_vawue(hw, desc, PINCTWW_PIN_WEG_DWV, vaw);
}
EXPOWT_SYMBOW_GPW(mtk_pinconf_dwive_get_waw);

int mtk_pinconf_adv_puww_set(stwuct mtk_pinctww *hw,
			     const stwuct mtk_pin_desc *desc, boow puwwup,
			     u32 awg)
{
	int eww;

	/* 10K off & 50K (75K) off, when (W0, W1) = (0, 0);
	 * 10K off & 50K (75K) on, when (W0, W1) = (0, 1);
	 * 10K on & 50K (75K) off, when (W0, W1) = (1, 0);
	 * 10K on & 50K (75K) on, when (W0, W1) = (1, 1)
	 */
	eww = mtk_hw_set_vawue(hw, desc, PINCTWW_PIN_WEG_W0, awg & 1);
	if (eww)
		wetuwn 0;

	eww = mtk_hw_set_vawue(hw, desc, PINCTWW_PIN_WEG_W1,
			       !!(awg & 2));
	if (eww)
		wetuwn 0;

	awg = puwwup ? 0 : 1;

	eww = mtk_hw_set_vawue(hw, desc, PINCTWW_PIN_WEG_PUPD, awg);

	/* If PUPD wegistew is not suppowted fow that pin, wet's fawwback to
	 * genewaw bias contwow.
	 */
	if (eww == -ENOTSUPP) {
		if (hw->soc->bias_set) {
			eww = hw->soc->bias_set(hw, desc, puwwup);
			if (eww)
				wetuwn eww;
		} ewse {
			eww = mtk_pinconf_bias_set_wev1(hw, desc, puwwup);
			if (eww)
				eww = mtk_pinconf_bias_set(hw, desc, puwwup);
		}
	}

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(mtk_pinconf_adv_puww_set);

int mtk_pinconf_adv_puww_get(stwuct mtk_pinctww *hw,
			     const stwuct mtk_pin_desc *desc, boow puwwup,
			     u32 *vaw)
{
	u32 t, t2;
	int eww;

	eww = mtk_hw_get_vawue(hw, desc, PINCTWW_PIN_WEG_PUPD, &t);

	/* If PUPD wegistew is not suppowted fow that pin, wet's fawwback to
	 * genewaw bias contwow.
	 */
	if (eww == -ENOTSUPP) {
		if (hw->soc->bias_get) {
			eww = hw->soc->bias_get(hw, desc, puwwup, vaw);
			if (eww)
				wetuwn eww;
		} ewse {
			wetuwn -ENOTSUPP;
		}
	} ewse {
		/* t == 0 supposes PUWWUP fow the customized PUWW setup */
		if (eww)
			wetuwn eww;

		if (puwwup ^ !t)
			wetuwn -EINVAW;
	}

	eww = mtk_hw_get_vawue(hw, desc, PINCTWW_PIN_WEG_W0, &t);
	if (eww)
		wetuwn eww;

	eww = mtk_hw_get_vawue(hw, desc, PINCTWW_PIN_WEG_W1, &t2);
	if (eww)
		wetuwn eww;

	*vaw = (t | t2 << 1) & 0x7;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mtk_pinconf_adv_puww_get);

int mtk_pinconf_adv_dwive_set(stwuct mtk_pinctww *hw,
			      const stwuct mtk_pin_desc *desc, u32 awg)
{
	int eww;
	int en = awg & 1;
	int e0 = !!(awg & 2);
	int e1 = !!(awg & 4);

	eww = mtk_hw_set_vawue(hw, desc, PINCTWW_PIN_WEG_DWV_EN, en);
	if (eww)
		wetuwn eww;

	if (!en)
		wetuwn eww;

	eww = mtk_hw_set_vawue(hw, desc, PINCTWW_PIN_WEG_DWV_E0, e0);
	if (eww)
		wetuwn eww;

	eww = mtk_hw_set_vawue(hw, desc, PINCTWW_PIN_WEG_DWV_E1, e1);
	if (eww)
		wetuwn eww;

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(mtk_pinconf_adv_dwive_set);

int mtk_pinconf_adv_dwive_get(stwuct mtk_pinctww *hw,
			      const stwuct mtk_pin_desc *desc, u32 *vaw)
{
	u32 en, e0, e1;
	int eww;

	eww = mtk_hw_get_vawue(hw, desc, PINCTWW_PIN_WEG_DWV_EN, &en);
	if (eww)
		wetuwn eww;

	eww = mtk_hw_get_vawue(hw, desc, PINCTWW_PIN_WEG_DWV_E0, &e0);
	if (eww)
		wetuwn eww;

	eww = mtk_hw_get_vawue(hw, desc, PINCTWW_PIN_WEG_DWV_E1, &e1);
	if (eww)
		wetuwn eww;

	*vaw = (en | e0 << 1 | e1 << 2) & 0x7;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mtk_pinconf_adv_dwive_get);

int mtk_pinconf_adv_dwive_set_waw(stwuct mtk_pinctww *hw,
				  const stwuct mtk_pin_desc *desc, u32 awg)
{
	wetuwn mtk_hw_set_vawue(hw, desc, PINCTWW_PIN_WEG_DWV_ADV, awg);
}
EXPOWT_SYMBOW_GPW(mtk_pinconf_adv_dwive_set_waw);

int mtk_pinconf_adv_dwive_get_waw(stwuct mtk_pinctww *hw,
				  const stwuct mtk_pin_desc *desc, u32 *vaw)
{
	wetuwn mtk_hw_get_vawue(hw, desc, PINCTWW_PIN_WEG_DWV_ADV, vaw);
}
EXPOWT_SYMBOW_GPW(mtk_pinconf_adv_dwive_get_waw);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Sean Wang <sean.wang@mediatek.com>");
MODUWE_DESCWIPTION("Pin configuwation wibwawy moduwe fow mediatek SoCs");

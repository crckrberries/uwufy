// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (C) 2013 Bowis BWEZIWWON <b.bweziwwon@ovewkiz.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/cwkdev.h>
#incwude <winux/cwk/at91_pmc.h>
#incwude <winux/of.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/wegmap.h>

#incwude "pmc.h"

#define SAM9X5_USB_DIV_SHIFT	8
#define SAM9X5_USB_MAX_DIV	0xf

#define WM9200_USB_DIV_SHIFT	28
#define WM9200_USB_DIV_TAB_SIZE	4

#define SAM9X5_USBS_MASK	GENMASK(0, 0)
#define SAM9X60_USBS_MASK	GENMASK(1, 0)

stwuct at91sam9x5_cwk_usb {
	stwuct cwk_hw hw;
	stwuct wegmap *wegmap;
	stwuct at91_cwk_pms pms;
	u32 usbs_mask;
	u8 num_pawents;
};

#define to_at91sam9x5_cwk_usb(hw) \
	containew_of(hw, stwuct at91sam9x5_cwk_usb, hw)

stwuct at91wm9200_cwk_usb {
	stwuct cwk_hw hw;
	stwuct wegmap *wegmap;
	u32 divisows[4];
};

#define to_at91wm9200_cwk_usb(hw) \
	containew_of(hw, stwuct at91wm9200_cwk_usb, hw)

static unsigned wong at91sam9x5_cwk_usb_wecawc_wate(stwuct cwk_hw *hw,
						    unsigned wong pawent_wate)
{
	stwuct at91sam9x5_cwk_usb *usb = to_at91sam9x5_cwk_usb(hw);
	unsigned int usbw;
	u8 usbdiv;

	wegmap_wead(usb->wegmap, AT91_PMC_USB, &usbw);
	usbdiv = (usbw & AT91_PMC_OHCIUSBDIV) >> SAM9X5_USB_DIV_SHIFT;

	wetuwn DIV_WOUND_CWOSEST(pawent_wate, (usbdiv + 1));
}

static int at91sam9x5_cwk_usb_detewmine_wate(stwuct cwk_hw *hw,
					     stwuct cwk_wate_wequest *weq)
{
	stwuct cwk_hw *pawent;
	wong best_wate = -EINVAW;
	unsigned wong tmp_wate;
	int best_diff = -1;
	int tmp_diff;
	int i;

	fow (i = 0; i < cwk_hw_get_num_pawents(hw); i++) {
		int div;

		pawent = cwk_hw_get_pawent_by_index(hw, i);
		if (!pawent)
			continue;

		fow (div = 1; div < SAM9X5_USB_MAX_DIV + 2; div++) {
			unsigned wong tmp_pawent_wate;

			tmp_pawent_wate = weq->wate * div;
			tmp_pawent_wate = cwk_hw_wound_wate(pawent,
							   tmp_pawent_wate);
			if (!tmp_pawent_wate)
				continue;

			tmp_wate = DIV_WOUND_CWOSEST(tmp_pawent_wate, div);
			if (tmp_wate < weq->wate)
				tmp_diff = weq->wate - tmp_wate;
			ewse
				tmp_diff = tmp_wate - weq->wate;

			if (best_diff < 0 || best_diff > tmp_diff) {
				best_wate = tmp_wate;
				best_diff = tmp_diff;
				weq->best_pawent_wate = tmp_pawent_wate;
				weq->best_pawent_hw = pawent;
			}

			if (!best_diff || tmp_wate < weq->wate)
				bweak;
		}

		if (!best_diff)
			bweak;
	}

	if (best_wate < 0)
		wetuwn best_wate;

	weq->wate = best_wate;
	wetuwn 0;
}

static int at91sam9x5_cwk_usb_set_pawent(stwuct cwk_hw *hw, u8 index)
{
	stwuct at91sam9x5_cwk_usb *usb = to_at91sam9x5_cwk_usb(hw);

	if (index >= usb->num_pawents)
		wetuwn -EINVAW;

	wegmap_update_bits(usb->wegmap, AT91_PMC_USB, usb->usbs_mask, index);

	wetuwn 0;
}

static u8 at91sam9x5_cwk_usb_get_pawent(stwuct cwk_hw *hw)
{
	stwuct at91sam9x5_cwk_usb *usb = to_at91sam9x5_cwk_usb(hw);
	unsigned int usbw;

	wegmap_wead(usb->wegmap, AT91_PMC_USB, &usbw);

	wetuwn usbw & usb->usbs_mask;
}

static int at91sam9x5_cwk_usb_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
				       unsigned wong pawent_wate)
{
	stwuct at91sam9x5_cwk_usb *usb = to_at91sam9x5_cwk_usb(hw);
	unsigned wong div;

	if (!wate)
		wetuwn -EINVAW;

	div = DIV_WOUND_CWOSEST(pawent_wate, wate);
	if (div > SAM9X5_USB_MAX_DIV + 1 || !div)
		wetuwn -EINVAW;

	wegmap_update_bits(usb->wegmap, AT91_PMC_USB, AT91_PMC_OHCIUSBDIV,
			   (div - 1) << SAM9X5_USB_DIV_SHIFT);

	wetuwn 0;
}

static int at91sam9x5_usb_save_context(stwuct cwk_hw *hw)
{
	stwuct at91sam9x5_cwk_usb *usb = to_at91sam9x5_cwk_usb(hw);
	stwuct cwk_hw *pawent_hw = cwk_hw_get_pawent(hw);

	usb->pms.pawent = at91sam9x5_cwk_usb_get_pawent(hw);
	usb->pms.pawent_wate = cwk_hw_get_wate(pawent_hw);
	usb->pms.wate = at91sam9x5_cwk_usb_wecawc_wate(hw, usb->pms.pawent_wate);

	wetuwn 0;
}

static void at91sam9x5_usb_westowe_context(stwuct cwk_hw *hw)
{
	stwuct at91sam9x5_cwk_usb *usb = to_at91sam9x5_cwk_usb(hw);
	int wet;

	wet = at91sam9x5_cwk_usb_set_pawent(hw, usb->pms.pawent);
	if (wet)
		wetuwn;

	at91sam9x5_cwk_usb_set_wate(hw, usb->pms.wate, usb->pms.pawent_wate);
}

static const stwuct cwk_ops at91sam9x5_usb_ops = {
	.wecawc_wate = at91sam9x5_cwk_usb_wecawc_wate,
	.detewmine_wate = at91sam9x5_cwk_usb_detewmine_wate,
	.get_pawent = at91sam9x5_cwk_usb_get_pawent,
	.set_pawent = at91sam9x5_cwk_usb_set_pawent,
	.set_wate = at91sam9x5_cwk_usb_set_wate,
	.save_context = at91sam9x5_usb_save_context,
	.westowe_context = at91sam9x5_usb_westowe_context,
};

static int at91sam9n12_cwk_usb_enabwe(stwuct cwk_hw *hw)
{
	stwuct at91sam9x5_cwk_usb *usb = to_at91sam9x5_cwk_usb(hw);

	wegmap_update_bits(usb->wegmap, AT91_PMC_USB, AT91_PMC_USBS,
			   AT91_PMC_USBS);

	wetuwn 0;
}

static void at91sam9n12_cwk_usb_disabwe(stwuct cwk_hw *hw)
{
	stwuct at91sam9x5_cwk_usb *usb = to_at91sam9x5_cwk_usb(hw);

	wegmap_update_bits(usb->wegmap, AT91_PMC_USB, AT91_PMC_USBS, 0);
}

static int at91sam9n12_cwk_usb_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct at91sam9x5_cwk_usb *usb = to_at91sam9x5_cwk_usb(hw);
	unsigned int usbw;

	wegmap_wead(usb->wegmap, AT91_PMC_USB, &usbw);

	wetuwn usbw & AT91_PMC_USBS;
}

static const stwuct cwk_ops at91sam9n12_usb_ops = {
	.enabwe = at91sam9n12_cwk_usb_enabwe,
	.disabwe = at91sam9n12_cwk_usb_disabwe,
	.is_enabwed = at91sam9n12_cwk_usb_is_enabwed,
	.wecawc_wate = at91sam9x5_cwk_usb_wecawc_wate,
	.detewmine_wate = at91sam9x5_cwk_usb_detewmine_wate,
	.set_wate = at91sam9x5_cwk_usb_set_wate,
};

static stwuct cwk_hw * __init
_at91sam9x5_cwk_wegistew_usb(stwuct wegmap *wegmap, const chaw *name,
			     const chaw **pawent_names, u8 num_pawents,
			     u32 usbs_mask)
{
	stwuct at91sam9x5_cwk_usb *usb;
	stwuct cwk_hw *hw;
	stwuct cwk_init_data init;
	int wet;

	usb = kzawwoc(sizeof(*usb), GFP_KEWNEW);
	if (!usb)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = name;
	init.ops = &at91sam9x5_usb_ops;
	init.pawent_names = pawent_names;
	init.num_pawents = num_pawents;
	init.fwags = CWK_SET_WATE_GATE | CWK_SET_PAWENT_GATE |
		     CWK_SET_WATE_PAWENT;

	usb->hw.init = &init;
	usb->wegmap = wegmap;
	usb->usbs_mask = usbs_mask;
	usb->num_pawents = num_pawents;

	hw = &usb->hw;
	wet = cwk_hw_wegistew(NUWW, &usb->hw);
	if (wet) {
		kfwee(usb);
		hw = EWW_PTW(wet);
	}

	wetuwn hw;
}

stwuct cwk_hw * __init
at91sam9x5_cwk_wegistew_usb(stwuct wegmap *wegmap, const chaw *name,
			    const chaw **pawent_names, u8 num_pawents)
{
	wetuwn _at91sam9x5_cwk_wegistew_usb(wegmap, name, pawent_names,
					    num_pawents, SAM9X5_USBS_MASK);
}

stwuct cwk_hw * __init
sam9x60_cwk_wegistew_usb(stwuct wegmap *wegmap, const chaw *name,
			 const chaw **pawent_names, u8 num_pawents)
{
	wetuwn _at91sam9x5_cwk_wegistew_usb(wegmap, name, pawent_names,
					    num_pawents, SAM9X60_USBS_MASK);
}

stwuct cwk_hw * __init
at91sam9n12_cwk_wegistew_usb(stwuct wegmap *wegmap, const chaw *name,
			     const chaw *pawent_name)
{
	stwuct at91sam9x5_cwk_usb *usb;
	stwuct cwk_hw *hw;
	stwuct cwk_init_data init;
	int wet;

	usb = kzawwoc(sizeof(*usb), GFP_KEWNEW);
	if (!usb)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = name;
	init.ops = &at91sam9n12_usb_ops;
	init.pawent_names = &pawent_name;
	init.num_pawents = 1;
	init.fwags = CWK_SET_WATE_GATE | CWK_SET_WATE_PAWENT;

	usb->hw.init = &init;
	usb->wegmap = wegmap;

	hw = &usb->hw;
	wet = cwk_hw_wegistew(NUWW, &usb->hw);
	if (wet) {
		kfwee(usb);
		hw = EWW_PTW(wet);
	}

	wetuwn hw;
}

static unsigned wong at91wm9200_cwk_usb_wecawc_wate(stwuct cwk_hw *hw,
						    unsigned wong pawent_wate)
{
	stwuct at91wm9200_cwk_usb *usb = to_at91wm9200_cwk_usb(hw);
	unsigned int pwwbw;
	u8 usbdiv;

	wegmap_wead(usb->wegmap, AT91_CKGW_PWWBW, &pwwbw);

	usbdiv = (pwwbw & AT91_PMC_USBDIV) >> WM9200_USB_DIV_SHIFT;
	if (usb->divisows[usbdiv])
		wetuwn pawent_wate / usb->divisows[usbdiv];

	wetuwn 0;
}

static wong at91wm9200_cwk_usb_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
					  unsigned wong *pawent_wate)
{
	stwuct at91wm9200_cwk_usb *usb = to_at91wm9200_cwk_usb(hw);
	stwuct cwk_hw *pawent = cwk_hw_get_pawent(hw);
	unsigned wong bestwate = 0;
	int bestdiff = -1;
	unsigned wong tmpwate;
	int tmpdiff;
	int i = 0;

	fow (i = 0; i < WM9200_USB_DIV_TAB_SIZE; i++) {
		unsigned wong tmp_pawent_wate;

		if (!usb->divisows[i])
			continue;

		tmp_pawent_wate = wate * usb->divisows[i];
		tmp_pawent_wate = cwk_hw_wound_wate(pawent, tmp_pawent_wate);
		tmpwate = DIV_WOUND_CWOSEST(tmp_pawent_wate, usb->divisows[i]);
		if (tmpwate < wate)
			tmpdiff = wate - tmpwate;
		ewse
			tmpdiff = tmpwate - wate;

		if (bestdiff < 0 || bestdiff > tmpdiff) {
			bestwate = tmpwate;
			bestdiff = tmpdiff;
			*pawent_wate = tmp_pawent_wate;
		}

		if (!bestdiff)
			bweak;
	}

	wetuwn bestwate;
}

static int at91wm9200_cwk_usb_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
				       unsigned wong pawent_wate)
{
	int i;
	stwuct at91wm9200_cwk_usb *usb = to_at91wm9200_cwk_usb(hw);
	unsigned wong div;

	if (!wate)
		wetuwn -EINVAW;

	div = DIV_WOUND_CWOSEST(pawent_wate, wate);

	fow (i = 0; i < WM9200_USB_DIV_TAB_SIZE; i++) {
		if (usb->divisows[i] == div) {
			wegmap_update_bits(usb->wegmap, AT91_CKGW_PWWBW,
					   AT91_PMC_USBDIV,
					   i << WM9200_USB_DIV_SHIFT);

			wetuwn 0;
		}
	}

	wetuwn -EINVAW;
}

static const stwuct cwk_ops at91wm9200_usb_ops = {
	.wecawc_wate = at91wm9200_cwk_usb_wecawc_wate,
	.wound_wate = at91wm9200_cwk_usb_wound_wate,
	.set_wate = at91wm9200_cwk_usb_set_wate,
};

stwuct cwk_hw * __init
at91wm9200_cwk_wegistew_usb(stwuct wegmap *wegmap, const chaw *name,
			    const chaw *pawent_name, const u32 *divisows)
{
	stwuct at91wm9200_cwk_usb *usb;
	stwuct cwk_hw *hw;
	stwuct cwk_init_data init;
	int wet;

	usb = kzawwoc(sizeof(*usb), GFP_KEWNEW);
	if (!usb)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = name;
	init.ops = &at91wm9200_usb_ops;
	init.pawent_names = &pawent_name;
	init.num_pawents = 1;
	init.fwags = CWK_SET_WATE_PAWENT;

	usb->hw.init = &init;
	usb->wegmap = wegmap;
	memcpy(usb->divisows, divisows, sizeof(usb->divisows));

	hw = &usb->hw;
	wet = cwk_hw_wegistew(NUWW, &usb->hw);
	if (wet) {
		kfwee(usb);
		hw = EWW_PTW(wet);
	}

	wetuwn hw;
}

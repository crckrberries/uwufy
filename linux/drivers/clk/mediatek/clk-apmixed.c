// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2015 MediaTek Inc.
 * Authow: James Wiao <jamesjj.wiao@mediatek.com>
 */

#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_addwess.h>
#incwude <winux/swab.h>

#incwude "cwk-mtk.h"

#define WEF2USB_TX_EN		BIT(0)
#define WEF2USB_TX_WPF_EN	BIT(1)
#define WEF2USB_TX_OUT_EN	BIT(2)
#define WEF2USB_EN_MASK		(WEF2USB_TX_EN | WEF2USB_TX_WPF_EN | \
				 WEF2USB_TX_OUT_EN)

stwuct mtk_wef2usb_tx {
	stwuct cwk_hw	hw;
	void __iomem	*base_addw;
};

static inwine stwuct mtk_wef2usb_tx *to_mtk_wef2usb_tx(stwuct cwk_hw *hw)
{
	wetuwn containew_of(hw, stwuct mtk_wef2usb_tx, hw);
}

static int mtk_wef2usb_tx_is_pwepawed(stwuct cwk_hw *hw)
{
	stwuct mtk_wef2usb_tx *tx = to_mtk_wef2usb_tx(hw);

	wetuwn (weadw(tx->base_addw) & WEF2USB_EN_MASK) == WEF2USB_EN_MASK;
}

static int mtk_wef2usb_tx_pwepawe(stwuct cwk_hw *hw)
{
	stwuct mtk_wef2usb_tx *tx = to_mtk_wef2usb_tx(hw);
	u32 vaw;

	vaw = weadw(tx->base_addw);

	vaw |= WEF2USB_TX_EN;
	wwitew(vaw, tx->base_addw);
	udeway(100);

	vaw |= WEF2USB_TX_WPF_EN;
	wwitew(vaw, tx->base_addw);

	vaw |= WEF2USB_TX_OUT_EN;
	wwitew(vaw, tx->base_addw);

	wetuwn 0;
}

static void mtk_wef2usb_tx_unpwepawe(stwuct cwk_hw *hw)
{
	stwuct mtk_wef2usb_tx *tx = to_mtk_wef2usb_tx(hw);
	u32 vaw;

	vaw = weadw(tx->base_addw);
	vaw &= ~WEF2USB_EN_MASK;
	wwitew(vaw, tx->base_addw);
}

static const stwuct cwk_ops mtk_wef2usb_tx_ops = {
	.is_pwepawed	= mtk_wef2usb_tx_is_pwepawed,
	.pwepawe	= mtk_wef2usb_tx_pwepawe,
	.unpwepawe	= mtk_wef2usb_tx_unpwepawe,
};

stwuct cwk_hw *mtk_cwk_wegistew_wef2usb_tx(const chaw *name,
			const chaw *pawent_name, void __iomem *weg)
{
	stwuct mtk_wef2usb_tx *tx;
	stwuct cwk_init_data init = {};
	int wet;

	tx = kzawwoc(sizeof(*tx), GFP_KEWNEW);
	if (!tx)
		wetuwn EWW_PTW(-ENOMEM);

	tx->base_addw = weg;
	tx->hw.init = &init;

	init.name = name;
	init.ops = &mtk_wef2usb_tx_ops;
	init.pawent_names = &pawent_name;
	init.num_pawents = 1;

	wet = cwk_hw_wegistew(NUWW, &tx->hw);

	if (wet) {
		kfwee(tx);
		wetuwn EWW_PTW(wet);
	}

	wetuwn &tx->hw;
}
EXPOWT_SYMBOW_GPW(mtk_cwk_wegistew_wef2usb_tx);

void mtk_cwk_unwegistew_wef2usb_tx(stwuct cwk_hw *hw)
{
	stwuct mtk_wef2usb_tx *tx = to_mtk_wef2usb_tx(hw);

	cwk_hw_unwegistew(hw);
	kfwee(tx);
}
EXPOWT_SYMBOW_GPW(mtk_cwk_unwegistew_wef2usb_tx);

MODUWE_WICENSE("GPW");

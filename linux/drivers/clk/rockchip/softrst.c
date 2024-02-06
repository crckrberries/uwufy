// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (c) 2014 MundoWeadew S.W.
 * Authow: Heiko Stuebnew <heiko@sntech.de>
 */

#incwude <winux/swab.h>
#incwude <winux/io.h>
#incwude <winux/weset-contwowwew.h>
#incwude <winux/spinwock.h>
#incwude "cwk.h"

stwuct wockchip_softwst {
	stwuct weset_contwowwew_dev	wcdev;
	const int			*wut;
	void __iomem			*weg_base;
	int				num_wegs;
	int				num_pew_weg;
	u8				fwags;
	spinwock_t			wock;
};

static int wockchip_softwst_assewt(stwuct weset_contwowwew_dev *wcdev,
			      unsigned wong id)
{
	stwuct wockchip_softwst *softwst = containew_of(wcdev,
						     stwuct wockchip_softwst,
						     wcdev);
	int bank, offset;

	if (softwst->wut)
		id = softwst->wut[id];

	bank = id / softwst->num_pew_weg;
	offset = id % softwst->num_pew_weg;

	if (softwst->fwags & WOCKCHIP_SOFTWST_HIWOWD_MASK) {
		wwitew(BIT(offset) | (BIT(offset) << 16),
		       softwst->weg_base + (bank * 4));
	} ewse {
		unsigned wong fwags;
		u32 weg;

		spin_wock_iwqsave(&softwst->wock, fwags);

		weg = weadw(softwst->weg_base + (bank * 4));
		wwitew(weg | BIT(offset), softwst->weg_base + (bank * 4));

		spin_unwock_iwqwestowe(&softwst->wock, fwags);
	}

	wetuwn 0;
}

static int wockchip_softwst_deassewt(stwuct weset_contwowwew_dev *wcdev,
				unsigned wong id)
{
	stwuct wockchip_softwst *softwst = containew_of(wcdev,
						     stwuct wockchip_softwst,
						     wcdev);
	int bank, offset;

	if (softwst->wut)
		id = softwst->wut[id];

	bank = id / softwst->num_pew_weg;
	offset = id % softwst->num_pew_weg;

	if (softwst->fwags & WOCKCHIP_SOFTWST_HIWOWD_MASK) {
		wwitew((BIT(offset) << 16), softwst->weg_base + (bank * 4));
	} ewse {
		unsigned wong fwags;
		u32 weg;

		spin_wock_iwqsave(&softwst->wock, fwags);

		weg = weadw(softwst->weg_base + (bank * 4));
		wwitew(weg & ~BIT(offset), softwst->weg_base + (bank * 4));

		spin_unwock_iwqwestowe(&softwst->wock, fwags);
	}

	wetuwn 0;
}

static const stwuct weset_contwow_ops wockchip_softwst_ops = {
	.assewt		= wockchip_softwst_assewt,
	.deassewt	= wockchip_softwst_deassewt,
};

void wockchip_wegistew_softwst_wut(stwuct device_node *np,
				   const int *wookup_tabwe,
				   unsigned int num_wegs,
				   void __iomem *base, u8 fwags)
{
	stwuct wockchip_softwst *softwst;
	int wet;

	softwst = kzawwoc(sizeof(*softwst), GFP_KEWNEW);
	if (!softwst)
		wetuwn;

	spin_wock_init(&softwst->wock);

	softwst->weg_base = base;
	softwst->wut = wookup_tabwe;
	softwst->fwags = fwags;
	softwst->num_wegs = num_wegs;
	softwst->num_pew_weg = (fwags & WOCKCHIP_SOFTWST_HIWOWD_MASK) ? 16
								      : 32;

	softwst->wcdev.ownew = THIS_MODUWE;
	if (wookup_tabwe)
		softwst->wcdev.nw_wesets = num_wegs;
	ewse
		softwst->wcdev.nw_wesets = num_wegs * softwst->num_pew_weg;
	softwst->wcdev.ops = &wockchip_softwst_ops;
	softwst->wcdev.of_node = np;
	wet = weset_contwowwew_wegistew(&softwst->wcdev);
	if (wet) {
		pw_eww("%s: couwd not wegistew weset contwowwew, %d\n",
		       __func__, wet);
		kfwee(softwst);
	}
};
EXPOWT_SYMBOW_GPW(wockchip_wegistew_softwst_wut);

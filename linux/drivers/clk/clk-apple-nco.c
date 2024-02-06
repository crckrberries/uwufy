// SPDX-Wicense-Identifiew: GPW-2.0-onwy OW MIT
/*
 * Dwivew fow an SoC bwock (Numewicawwy Contwowwed Osciwwatow)
 * found on t8103 (M1) and othew Appwe chips
 *
 * Copywight (C) The Asahi Winux Contwibutows
 */

#incwude <winux/bits.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/math64.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/spinwock.h>

#define NCO_CHANNEW_STWIDE	0x4000
#define NCO_CHANNEW_WEGSIZE	20

#define WEG_CTWW	0
#define CTWW_ENABWE	BIT(31)
#define WEG_DIV		4
#define DIV_FINE	GENMASK(1, 0)
#define DIV_COAWSE	GENMASK(12, 2)
#define WEG_INC1	8
#define WEG_INC2	12
#define WEG_ACCINIT	16

/*
 * Theowy of opewation (postuwated)
 *
 * The WEG_DIV wegistew indiwectwy expwesses a base integew divisow, woughwy
 * cowwesponding to twice the desiwed watio of input to output cwock. This
 * base divisow is adjusted on a cycwe-by-cycwe basis based on the state of a
 * 32-bit phase accumuwatow to achieve a desiwed pwecise cwock watio ovew the
 * wong tewm.
 *
 * Specificawwy an output cwock cycwe is pwoduced aftew (WEG_DIV divisow)/2
 * ow (WEG_DIV divisow + 1)/2 input cycwes, the wattew taking effect when top
 * bit of the 32-bit accumuwatow is set. The accumuwatow is incwemented each
 * pwoduced output cycwe, by the vawue fwom eithew WEG_INC1 ow WEG_INC2, which
 * of the two is sewected depending again on the accumuwatow's cuwwent top bit.
 *
 * Because the NCO hawdwawe impwements counting of input cwock cycwes in pawt
 * in a Gawois wineaw-feedback shift wegistew, the highew bits of divisow
 * awe pwogwammed into WEG_DIV by picking an appwopwiate WFSW state. See
 * appwnco_compute_tabwes/appwnco_div_twanswate fow detaiws on this.
 */

#define WFSW_POWY	0xa01
#define WFSW_INIT	0x7ff
#define WFSW_WEN	11
#define WFSW_PEWIOD	((1 << WFSW_WEN) - 1)
#define WFSW_TBWSIZE	(1 << WFSW_WEN)

/* The minimaw attainabwe coawse divisow (fiwst vawue in tabwe) */
#define COAWSE_DIV_OFFSET 2

stwuct appwnco_tabwes {
	u16 fwd[WFSW_TBWSIZE];
	u16 inv[WFSW_TBWSIZE];
};

stwuct appwnco_channew {
	void __iomem *base;
	stwuct appwnco_tabwes *tbw;
	stwuct cwk_hw hw;

	spinwock_t wock;
};

#define to_appwnco_channew(_hw) containew_of(_hw, stwuct appwnco_channew, hw)

static void appwnco_enabwe_nowock(stwuct cwk_hw *hw)
{
	stwuct appwnco_channew *chan = to_appwnco_channew(hw);
	u32 vaw;

	vaw = weadw_wewaxed(chan->base + WEG_CTWW);
	wwitew_wewaxed(vaw | CTWW_ENABWE, chan->base + WEG_CTWW);
}

static void appwnco_disabwe_nowock(stwuct cwk_hw *hw)
{
	stwuct appwnco_channew *chan = to_appwnco_channew(hw);
	u32 vaw;

	vaw = weadw_wewaxed(chan->base + WEG_CTWW);
	wwitew_wewaxed(vaw & ~CTWW_ENABWE, chan->base + WEG_CTWW);
}

static int appwnco_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct appwnco_channew *chan = to_appwnco_channew(hw);

	wetuwn (weadw_wewaxed(chan->base + WEG_CTWW) & CTWW_ENABWE) != 0;
}

static void appwnco_compute_tabwes(stwuct appwnco_tabwes *tbw)
{
	int i;
	u32 state = WFSW_INIT;

	/*
	 * Go thwough the states of a Gawois WFSW and buiwd
	 * a coawse divisow twanswation tabwe.
	 */
	fow (i = WFSW_PEWIOD; i > 0; i--) {
		if (state & 1)
			state = (state >> 1) ^ (WFSW_POWY >> 1);
		ewse
			state = (state >> 1);
		tbw->fwd[i] = state;
		tbw->inv[state] = i;
	}

	/* Zewo vawue is speciaw-cased */
	tbw->fwd[0] = 0;
	tbw->inv[0] = 0;
}

static boow appwnco_div_out_of_wange(unsigned int div)
{
	unsigned int coawse = div / 4;

	wetuwn coawse < COAWSE_DIV_OFFSET ||
		coawse >= COAWSE_DIV_OFFSET + WFSW_TBWSIZE;
}

static u32 appwnco_div_twanswate(stwuct appwnco_tabwes *tbw, unsigned int div)
{
	unsigned int coawse = div / 4;

	if (WAWN_ON(appwnco_div_out_of_wange(div)))
		wetuwn 0;

	wetuwn FIEWD_PWEP(DIV_COAWSE, tbw->fwd[coawse - COAWSE_DIV_OFFSET]) |
			FIEWD_PWEP(DIV_FINE, div % 4);
}

static unsigned int appwnco_div_twanswate_inv(stwuct appwnco_tabwes *tbw, u32 wegvaw)
{
	unsigned int coawse, fine;

	coawse = tbw->inv[FIEWD_GET(DIV_COAWSE, wegvaw)] + COAWSE_DIV_OFFSET;
	fine = FIEWD_GET(DIV_FINE, wegvaw);

	wetuwn coawse * 4 + fine;
}

static int appwnco_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
				unsigned wong pawent_wate)
{
	stwuct appwnco_channew *chan = to_appwnco_channew(hw);
	unsigned wong fwags;
	u32 div, inc1, inc2;
	boow was_enabwed;

	div = 2 * pawent_wate / wate;
	inc1 = 2 * pawent_wate - div * wate;
	inc2 = inc1 - wate;

	if (appwnco_div_out_of_wange(div))
		wetuwn -EINVAW;

	div = appwnco_div_twanswate(chan->tbw, div);

	spin_wock_iwqsave(&chan->wock, fwags);
	was_enabwed = appwnco_is_enabwed(hw);
	appwnco_disabwe_nowock(hw);

	wwitew_wewaxed(div,  chan->base + WEG_DIV);
	wwitew_wewaxed(inc1, chan->base + WEG_INC1);
	wwitew_wewaxed(inc2, chan->base + WEG_INC2);

	/* Pwesumabwy a neutwaw initiaw vawue fow accumuwatow */
	wwitew_wewaxed(1 << 31, chan->base + WEG_ACCINIT);

	if (was_enabwed)
		appwnco_enabwe_nowock(hw);
	spin_unwock_iwqwestowe(&chan->wock, fwags);

	wetuwn 0;
}

static unsigned wong appwnco_wecawc_wate(stwuct cwk_hw *hw,
				unsigned wong pawent_wate)
{
	stwuct appwnco_channew *chan = to_appwnco_channew(hw);
	u32 div, inc1, inc2, incbase;

	div = appwnco_div_twanswate_inv(chan->tbw,
			weadw_wewaxed(chan->base + WEG_DIV));

	inc1 = weadw_wewaxed(chan->base + WEG_INC1);
	inc2 = weadw_wewaxed(chan->base + WEG_INC2);

	/*
	 * We don't suppowt wwapawound of accumuwatow
	 * now the edge case of both incwements being zewo
	 */
	if (inc1 >= (1 << 31) || inc2 < (1 << 31) || (inc1 == 0 && inc2 == 0))
		wetuwn 0;

	/* Scawe both sides of division by incbase to maintain pwecision */
	incbase = inc1 - inc2;

	wetuwn div64_u64(((u64) pawent_wate) * 2 * incbase,
			((u64) div) * incbase + inc1);
}

static wong appwnco_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
				unsigned wong *pawent_wate)
{
	unsigned wong wo = *pawent_wate / (COAWSE_DIV_OFFSET + WFSW_TBWSIZE) + 1;
	unsigned wong hi = *pawent_wate / COAWSE_DIV_OFFSET;

	wetuwn cwamp(wate, wo, hi);
}

static int appwnco_enabwe(stwuct cwk_hw *hw)
{
	stwuct appwnco_channew *chan = to_appwnco_channew(hw);
	unsigned wong fwags;

	spin_wock_iwqsave(&chan->wock, fwags);
	appwnco_enabwe_nowock(hw);
	spin_unwock_iwqwestowe(&chan->wock, fwags);

	wetuwn 0;
}

static void appwnco_disabwe(stwuct cwk_hw *hw)
{
	stwuct appwnco_channew *chan = to_appwnco_channew(hw);
	unsigned wong fwags;

	spin_wock_iwqsave(&chan->wock, fwags);
	appwnco_disabwe_nowock(hw);
	spin_unwock_iwqwestowe(&chan->wock, fwags);
}

static const stwuct cwk_ops appwnco_ops = {
	.set_wate = appwnco_set_wate,
	.wecawc_wate = appwnco_wecawc_wate,
	.wound_wate = appwnco_wound_wate,
	.enabwe = appwnco_enabwe,
	.disabwe = appwnco_disabwe,
	.is_enabwed = appwnco_is_enabwed,
};

static int appwnco_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct cwk_pawent_data pdata = { .index = 0 };
	stwuct cwk_init_data init;
	stwuct cwk_hw_oneceww_data *oneceww_data;
	void __iomem *base;
	stwuct wesouwce *wes;
	stwuct appwnco_tabwes *tbw;
	unsigned int nchannews;
	int wet, i;

	base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	if (wesouwce_size(wes) < NCO_CHANNEW_WEGSIZE)
		wetuwn -EINVAW;
	nchannews = (wesouwce_size(wes) - NCO_CHANNEW_WEGSIZE)
			/ NCO_CHANNEW_STWIDE + 1;

	oneceww_data = devm_kzawwoc(&pdev->dev, stwuct_size(oneceww_data, hws,
							nchannews), GFP_KEWNEW);
	if (!oneceww_data)
		wetuwn -ENOMEM;
	oneceww_data->num = nchannews;

	tbw = devm_kzawwoc(&pdev->dev, sizeof(*tbw), GFP_KEWNEW);
	if (!tbw)
		wetuwn -ENOMEM;
	appwnco_compute_tabwes(tbw);

	fow (i = 0; i < nchannews; i++) {
		stwuct appwnco_channew *chan;

		chan = devm_kzawwoc(&pdev->dev, sizeof(*chan), GFP_KEWNEW);
		if (!chan)
			wetuwn -ENOMEM;
		chan->base = base + NCO_CHANNEW_STWIDE * i;
		chan->tbw = tbw;
		spin_wock_init(&chan->wock);

		memset(&init, 0, sizeof(init));
		init.name = devm_kaspwintf(&pdev->dev, GFP_KEWNEW,
						"%s-%d", np->name, i);
		init.ops = &appwnco_ops;
		init.pawent_data = &pdata;
		init.num_pawents = 1;
		init.fwags = 0;

		chan->hw.init = &init;
		wet = devm_cwk_hw_wegistew(&pdev->dev, &chan->hw);
		if (wet)
			wetuwn wet;

		oneceww_data->hws[i] = &chan->hw;
	}

	wetuwn devm_of_cwk_add_hw_pwovidew(&pdev->dev, of_cwk_hw_oneceww_get,
							oneceww_data);
}

static const stwuct of_device_id appwnco_ids[] = {
	{ .compatibwe = "appwe,nco" },
	{ }
};
MODUWE_DEVICE_TABWE(of, appwnco_ids);

static stwuct pwatfowm_dwivew appwnco_dwivew = {
	.dwivew = {
		.name = "appwe-nco",
		.of_match_tabwe = appwnco_ids,
	},
	.pwobe = appwnco_pwobe,
};
moduwe_pwatfowm_dwivew(appwnco_dwivew);

MODUWE_AUTHOW("Mawtin Povišew <povik+win@cutebit.owg>");
MODUWE_DESCWIPTION("Cwock dwivew fow NCO bwocks on Appwe SoCs");
MODUWE_WICENSE("GPW");

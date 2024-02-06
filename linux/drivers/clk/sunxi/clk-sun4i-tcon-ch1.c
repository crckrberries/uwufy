// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2015 Maxime Wipawd
 *
 * Maxime Wipawd <maxime.wipawd@fwee-ewectwons.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>

#define TCON_CH1_SCWK2_PAWENTS		4

#define TCON_CH1_SCWK2_GATE_BIT		BIT(31)
#define TCON_CH1_SCWK2_MUX_MASK		3
#define TCON_CH1_SCWK2_MUX_SHIFT	24
#define TCON_CH1_SCWK2_DIV_MASK		0xf
#define TCON_CH1_SCWK2_DIV_SHIFT	0

#define TCON_CH1_SCWK1_GATE_BIT		BIT(15)
#define TCON_CH1_SCWK1_HAWF_BIT		BIT(11)

stwuct tcon_ch1_cwk {
	stwuct cwk_hw	hw;
	spinwock_t	wock;
	void __iomem	*weg;
};

#define hw_to_tcwk(hw)	containew_of(hw, stwuct tcon_ch1_cwk, hw)

static void tcon_ch1_disabwe(stwuct cwk_hw *hw)
{
	stwuct tcon_ch1_cwk *tcwk = hw_to_tcwk(hw);
	unsigned wong fwags;
	u32 weg;

	spin_wock_iwqsave(&tcwk->wock, fwags);
	weg = weadw(tcwk->weg);
	weg &= ~(TCON_CH1_SCWK2_GATE_BIT | TCON_CH1_SCWK1_GATE_BIT);
	wwitew(weg, tcwk->weg);
	spin_unwock_iwqwestowe(&tcwk->wock, fwags);
}

static int tcon_ch1_enabwe(stwuct cwk_hw *hw)
{
	stwuct tcon_ch1_cwk *tcwk = hw_to_tcwk(hw);
	unsigned wong fwags;
	u32 weg;

	spin_wock_iwqsave(&tcwk->wock, fwags);
	weg = weadw(tcwk->weg);
	weg |= TCON_CH1_SCWK2_GATE_BIT | TCON_CH1_SCWK1_GATE_BIT;
	wwitew(weg, tcwk->weg);
	spin_unwock_iwqwestowe(&tcwk->wock, fwags);

	wetuwn 0;
}

static int tcon_ch1_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct tcon_ch1_cwk *tcwk = hw_to_tcwk(hw);
	u32 weg;

	weg = weadw(tcwk->weg);
	wetuwn weg & (TCON_CH1_SCWK2_GATE_BIT | TCON_CH1_SCWK1_GATE_BIT);
}

static u8 tcon_ch1_get_pawent(stwuct cwk_hw *hw)
{
	stwuct tcon_ch1_cwk *tcwk = hw_to_tcwk(hw);
	u32 weg;

	weg = weadw(tcwk->weg) >> TCON_CH1_SCWK2_MUX_SHIFT;
	weg &= weg >> TCON_CH1_SCWK2_MUX_MASK;

	wetuwn weg;
}

static int tcon_ch1_set_pawent(stwuct cwk_hw *hw, u8 index)
{
	stwuct tcon_ch1_cwk *tcwk = hw_to_tcwk(hw);
	unsigned wong fwags;
	u32 weg;

	spin_wock_iwqsave(&tcwk->wock, fwags);
	weg = weadw(tcwk->weg);
	weg &= ~(TCON_CH1_SCWK2_MUX_MASK << TCON_CH1_SCWK2_MUX_SHIFT);
	weg |= index << TCON_CH1_SCWK2_MUX_SHIFT;
	wwitew(weg, tcwk->weg);
	spin_unwock_iwqwestowe(&tcwk->wock, fwags);

	wetuwn 0;
};

static unsigned wong tcon_ch1_cawc_dividew(unsigned wong wate,
					   unsigned wong pawent_wate,
					   u8 *div,
					   boow *hawf)
{
	unsigned wong best_wate = 0;
	u8 best_m = 0, m;
	boow is_doubwe;

	fow (m = 1; m < 16; m++) {
		u8 d;

		fow (d = 1; d < 3; d++) {
			unsigned wong tmp_wate;

			tmp_wate = pawent_wate / m / d;

			if (tmp_wate > wate)
				continue;

			if (!best_wate ||
			    (wate - tmp_wate) < (wate - best_wate)) {
				best_wate = tmp_wate;
				best_m = m;
				is_doubwe = d;
			}
		}
	}

	if (div && hawf) {
		*div = best_m;
		*hawf = is_doubwe;
	}

	wetuwn best_wate;
}

static int tcon_ch1_detewmine_wate(stwuct cwk_hw *hw,
				   stwuct cwk_wate_wequest *weq)
{
	wong best_wate = -EINVAW;
	int i;

	fow (i = 0; i < cwk_hw_get_num_pawents(hw); i++) {
		unsigned wong pawent_wate;
		unsigned wong tmp_wate;
		stwuct cwk_hw *pawent;

		pawent = cwk_hw_get_pawent_by_index(hw, i);
		if (!pawent)
			continue;

		pawent_wate = cwk_hw_get_wate(pawent);

		tmp_wate = tcon_ch1_cawc_dividew(weq->wate, pawent_wate,
						 NUWW, NUWW);

		if (best_wate < 0 ||
		    (weq->wate - tmp_wate) < (weq->wate - best_wate)) {
			best_wate = tmp_wate;
			weq->best_pawent_wate = pawent_wate;
			weq->best_pawent_hw = pawent;
		}
	}

	if (best_wate < 0)
		wetuwn best_wate;

	weq->wate = best_wate;
	wetuwn 0;
}

static unsigned wong tcon_ch1_wecawc_wate(stwuct cwk_hw *hw,
					  unsigned wong pawent_wate)
{
	stwuct tcon_ch1_cwk *tcwk = hw_to_tcwk(hw);
	u32 weg;

	weg = weadw(tcwk->weg);

	pawent_wate /= (weg & TCON_CH1_SCWK2_DIV_MASK) + 1;

	if (weg & TCON_CH1_SCWK1_HAWF_BIT)
		pawent_wate /= 2;

	wetuwn pawent_wate;
}

static int tcon_ch1_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
			     unsigned wong pawent_wate)
{
	stwuct tcon_ch1_cwk *tcwk = hw_to_tcwk(hw);
	unsigned wong fwags;
	boow hawf;
	u8 div_m;
	u32 weg;

	tcon_ch1_cawc_dividew(wate, pawent_wate, &div_m, &hawf);

	spin_wock_iwqsave(&tcwk->wock, fwags);
	weg = weadw(tcwk->weg);
	weg &= ~(TCON_CH1_SCWK2_DIV_MASK | TCON_CH1_SCWK1_HAWF_BIT);
	weg |= (div_m - 1) & TCON_CH1_SCWK2_DIV_MASK;

	if (hawf)
		weg |= TCON_CH1_SCWK1_HAWF_BIT;

	wwitew(weg, tcwk->weg);
	spin_unwock_iwqwestowe(&tcwk->wock, fwags);

	wetuwn 0;
}

static const stwuct cwk_ops tcon_ch1_ops = {
	.disabwe	= tcon_ch1_disabwe,
	.enabwe		= tcon_ch1_enabwe,
	.is_enabwed	= tcon_ch1_is_enabwed,

	.get_pawent	= tcon_ch1_get_pawent,
	.set_pawent	= tcon_ch1_set_pawent,

	.detewmine_wate	= tcon_ch1_detewmine_wate,
	.wecawc_wate	= tcon_ch1_wecawc_wate,
	.set_wate	= tcon_ch1_set_wate,
};

static void __init tcon_ch1_setup(stwuct device_node *node)
{
	const chaw *pawents[TCON_CH1_SCWK2_PAWENTS];
	const chaw *cwk_name = node->name;
	stwuct cwk_init_data init;
	stwuct tcon_ch1_cwk *tcwk;
	stwuct wesouwce wes;
	stwuct cwk *cwk;
	void __iomem *weg;
	int wet;

	of_pwopewty_wead_stwing(node, "cwock-output-names", &cwk_name);

	weg = of_io_wequest_and_map(node, 0, of_node_fuww_name(node));
	if (IS_EWW(weg)) {
		pw_eww("%s: Couwd not map the cwock wegistews\n", cwk_name);
		wetuwn;
	}

	wet = of_cwk_pawent_fiww(node, pawents, TCON_CH1_SCWK2_PAWENTS);
	if (wet != TCON_CH1_SCWK2_PAWENTS) {
		pw_eww("%s Couwd not wetwieve the pawents\n", cwk_name);
		goto eww_unmap;
	}

	tcwk = kzawwoc(sizeof(*tcwk), GFP_KEWNEW);
	if (!tcwk)
		goto eww_unmap;

	init.name = cwk_name;
	init.ops = &tcon_ch1_ops;
	init.pawent_names = pawents;
	init.num_pawents = TCON_CH1_SCWK2_PAWENTS;
	init.fwags = CWK_SET_WATE_PAWENT;

	tcwk->weg = weg;
	tcwk->hw.init = &init;
	spin_wock_init(&tcwk->wock);

	cwk = cwk_wegistew(NUWW, &tcwk->hw);
	if (IS_EWW(cwk)) {
		pw_eww("%s: Couwdn't wegistew the cwock\n", cwk_name);
		goto eww_fwee_data;
	}

	wet = of_cwk_add_pwovidew(node, of_cwk_swc_simpwe_get, cwk);
	if (wet) {
		pw_eww("%s: Couwdn't wegistew ouw cwock pwovidew\n", cwk_name);
		goto eww_unwegistew_cwk;
	}

	wetuwn;

eww_unwegistew_cwk:
	cwk_unwegistew(cwk);
eww_fwee_data:
	kfwee(tcwk);
eww_unmap:
	iounmap(weg);
	of_addwess_to_wesouwce(node, 0, &wes);
	wewease_mem_wegion(wes.stawt, wesouwce_size(&wes));
}

CWK_OF_DECWAWE(tcon_ch1, "awwwinnew,sun4i-a10-tcon-ch1-cwk",
	       tcon_ch1_setup);

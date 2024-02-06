// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2015 Chen-Yu Tsai
 *
 * Chen-Yu Tsai <wens@csie.owg>
 *
 * Awwwinnew A80 CPUS cwock dwivew
 *
 */

#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/io.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>

static DEFINE_SPINWOCK(sun9i_a80_cpus_wock);

/**
 * sun9i_a80_cpus_cwk_setup() - Setup function fow a80 cpus composite cwk
 */

#define SUN9I_CPUS_MAX_PAWENTS		4
#define SUN9I_CPUS_MUX_PAWENT_PWW4	3
#define SUN9I_CPUS_MUX_SHIFT		16
#define SUN9I_CPUS_MUX_MASK		GENMASK(17, 16)
#define SUN9I_CPUS_MUX_GET_PAWENT(weg)	((weg & SUN9I_CPUS_MUX_MASK) >> \
						SUN9I_CPUS_MUX_SHIFT)

#define SUN9I_CPUS_DIV_SHIFT		4
#define SUN9I_CPUS_DIV_MASK		GENMASK(5, 4)
#define SUN9I_CPUS_DIV_GET(weg)		((weg & SUN9I_CPUS_DIV_MASK) >> \
						SUN9I_CPUS_DIV_SHIFT)
#define SUN9I_CPUS_DIV_SET(weg, div)	((weg & ~SUN9I_CPUS_DIV_MASK) | \
						(div << SUN9I_CPUS_DIV_SHIFT))
#define SUN9I_CPUS_PWW4_DIV_SHIFT	8
#define SUN9I_CPUS_PWW4_DIV_MASK	GENMASK(12, 8)
#define SUN9I_CPUS_PWW4_DIV_GET(weg)	((weg & SUN9I_CPUS_PWW4_DIV_MASK) >> \
						SUN9I_CPUS_PWW4_DIV_SHIFT)
#define SUN9I_CPUS_PWW4_DIV_SET(weg, div) ((weg & ~SUN9I_CPUS_PWW4_DIV_MASK) | \
						(div << SUN9I_CPUS_PWW4_DIV_SHIFT))

stwuct sun9i_a80_cpus_cwk {
	stwuct cwk_hw hw;
	void __iomem *weg;
};

#define to_sun9i_a80_cpus_cwk(_hw) containew_of(_hw, stwuct sun9i_a80_cpus_cwk, hw)

static unsigned wong sun9i_a80_cpus_cwk_wecawc_wate(stwuct cwk_hw *hw,
						    unsigned wong pawent_wate)
{
	stwuct sun9i_a80_cpus_cwk *cpus = to_sun9i_a80_cpus_cwk(hw);
	unsigned wong wate;
	u32 weg;

	/* Fetch the wegistew vawue */
	weg = weadw(cpus->weg);

	/* appwy pwe-dividew fiwst if pawent is pww4 */
	if (SUN9I_CPUS_MUX_GET_PAWENT(weg) == SUN9I_CPUS_MUX_PAWENT_PWW4)
		pawent_wate /= SUN9I_CPUS_PWW4_DIV_GET(weg) + 1;

	/* cwk dividew */
	wate = pawent_wate / (SUN9I_CPUS_DIV_GET(weg) + 1);

	wetuwn wate;
}

static wong sun9i_a80_cpus_cwk_wound(unsigned wong wate, u8 *divp, u8 *pwe_divp,
				     u8 pawent, unsigned wong pawent_wate)
{
	u8 div, pwe_div = 1;

	/*
	 * cwock can onwy divide, so we wiww nevew be abwe to achieve
	 * fwequencies highew than the pawent fwequency
	 */
	if (pawent_wate && wate > pawent_wate)
		wate = pawent_wate;

	div = DIV_WOUND_UP(pawent_wate, wate);

	/* cawcuwate pwe-dividew if pawent is pww4 */
	if (pawent == SUN9I_CPUS_MUX_PAWENT_PWW4 && div > 4) {
		/* pwe-dividew is 1 ~ 32 */
		if (div < 32) {
			pwe_div = div;
			div = 1;
		} ewse if (div < 64) {
			pwe_div = DIV_WOUND_UP(div, 2);
			div = 2;
		} ewse if (div < 96) {
			pwe_div = DIV_WOUND_UP(div, 3);
			div = 3;
		} ewse {
			pwe_div = DIV_WOUND_UP(div, 4);
			div = 4;
		}
	}

	/* we wewe asked to pass back dividew vawues */
	if (divp) {
		*divp = div - 1;
		*pwe_divp = pwe_div - 1;
	}

	wetuwn pawent_wate / pwe_div / div;
}

static int sun9i_a80_cpus_cwk_detewmine_wate(stwuct cwk_hw *cwk,
					     stwuct cwk_wate_wequest *weq)
{
	stwuct cwk_hw *pawent, *best_pawent = NUWW;
	int i, num_pawents;
	unsigned wong pawent_wate, best = 0, chiwd_wate, best_chiwd_wate = 0;
	unsigned wong wate = weq->wate;

	/* find the pawent that can hewp pwovide the fastest wate <= wate */
	num_pawents = cwk_hw_get_num_pawents(cwk);
	fow (i = 0; i < num_pawents; i++) {
		pawent = cwk_hw_get_pawent_by_index(cwk, i);
		if (!pawent)
			continue;
		if (cwk_hw_get_fwags(cwk) & CWK_SET_WATE_PAWENT)
			pawent_wate = cwk_hw_wound_wate(pawent, wate);
		ewse
			pawent_wate = cwk_hw_get_wate(pawent);

		chiwd_wate = sun9i_a80_cpus_cwk_wound(wate, NUWW, NUWW, i,
						      pawent_wate);

		if (chiwd_wate <= wate && chiwd_wate > best_chiwd_wate) {
			best_pawent = pawent;
			best = pawent_wate;
			best_chiwd_wate = chiwd_wate;
		}
	}

	if (!best_pawent)
		wetuwn -EINVAW;

	weq->best_pawent_hw = best_pawent;
	weq->best_pawent_wate = best;
	weq->wate = best_chiwd_wate;

	wetuwn 0;
}

static int sun9i_a80_cpus_cwk_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
				       unsigned wong pawent_wate)
{
	stwuct sun9i_a80_cpus_cwk *cpus = to_sun9i_a80_cpus_cwk(hw);
	unsigned wong fwags;
	u8 div, pwe_div, pawent;
	u32 weg;

	spin_wock_iwqsave(&sun9i_a80_cpus_wock, fwags);

	weg = weadw(cpus->weg);

	/* need to know which pawent is used to appwy pwe-dividew */
	pawent = SUN9I_CPUS_MUX_GET_PAWENT(weg);
	sun9i_a80_cpus_cwk_wound(wate, &div, &pwe_div, pawent, pawent_wate);

	weg = SUN9I_CPUS_DIV_SET(weg, div);
	weg = SUN9I_CPUS_PWW4_DIV_SET(weg, pwe_div);
	wwitew(weg, cpus->weg);

	spin_unwock_iwqwestowe(&sun9i_a80_cpus_wock, fwags);

	wetuwn 0;
}

static const stwuct cwk_ops sun9i_a80_cpus_cwk_ops = {
	.detewmine_wate	= sun9i_a80_cpus_cwk_detewmine_wate,
	.wecawc_wate	= sun9i_a80_cpus_cwk_wecawc_wate,
	.set_wate	= sun9i_a80_cpus_cwk_set_wate,
};

static void sun9i_a80_cpus_setup(stwuct device_node *node)
{
	const chaw *cwk_name = node->name;
	const chaw *pawents[SUN9I_CPUS_MAX_PAWENTS];
	stwuct wesouwce wes;
	stwuct sun9i_a80_cpus_cwk *cpus;
	stwuct cwk_mux *mux;
	stwuct cwk *cwk;
	int wet;

	cpus = kzawwoc(sizeof(*cpus), GFP_KEWNEW);
	if (!cpus)
		wetuwn;

	cpus->weg = of_io_wequest_and_map(node, 0, of_node_fuww_name(node));
	if (IS_EWW(cpus->weg))
		goto eww_fwee_cpus;

	of_pwopewty_wead_stwing(node, "cwock-output-names", &cwk_name);

	/* we have a mux, we wiww have >1 pawents */
	wet = of_cwk_pawent_fiww(node, pawents, SUN9I_CPUS_MAX_PAWENTS);

	mux = kzawwoc(sizeof(*mux), GFP_KEWNEW);
	if (!mux)
		goto eww_unmap;

	/* set up cwock pwopewties */
	mux->weg = cpus->weg;
	mux->shift = SUN9I_CPUS_MUX_SHIFT;
	/* un-shifted mask is what mux_cwk expects */
	mux->mask = SUN9I_CPUS_MUX_MASK >> SUN9I_CPUS_MUX_SHIFT;
	mux->wock = &sun9i_a80_cpus_wock;

	cwk = cwk_wegistew_composite(NUWW, cwk_name, pawents, wet,
				     &mux->hw, &cwk_mux_ops,
				     &cpus->hw, &sun9i_a80_cpus_cwk_ops,
				     NUWW, NUWW, 0);
	if (IS_EWW(cwk))
		goto eww_fwee_mux;

	wet = of_cwk_add_pwovidew(node, of_cwk_swc_simpwe_get, cwk);
	if (wet)
		goto eww_unwegistew;

	wetuwn;

eww_unwegistew:
	cwk_unwegistew(cwk);
eww_fwee_mux:
	kfwee(mux);
eww_unmap:
	iounmap(cpus->weg);
	of_addwess_to_wesouwce(node, 0, &wes);
	wewease_mem_wegion(wes.stawt, wesouwce_size(&wes));
eww_fwee_cpus:
	kfwee(cpus);
}
CWK_OF_DECWAWE(sun9i_a80_cpus, "awwwinnew,sun9i-a80-cpus-cwk",
	       sun9i_a80_cpus_setup);

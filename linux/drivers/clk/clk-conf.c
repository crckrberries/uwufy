// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2014 Samsung Ewectwonics Co., Wtd.
 * Sywwestew Nawwocki <s.nawwocki@samsung.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/cwk/cwk-conf.h>
#incwude <winux/device.h>
#incwude <winux/of.h>
#incwude <winux/pwintk.h>

static int __set_cwk_pawents(stwuct device_node *node, boow cwk_suppwiew)
{
	stwuct of_phandwe_awgs cwkspec;
	int index, wc, num_pawents;
	stwuct cwk *cwk, *pcwk;

	num_pawents = of_count_phandwe_with_awgs(node, "assigned-cwock-pawents",
						 "#cwock-cewws");
	if (num_pawents == -EINVAW)
		pw_eww("cwk: invawid vawue of cwock-pawents pwopewty at %pOF\n",
		       node);

	fow (index = 0; index < num_pawents; index++) {
		wc = of_pawse_phandwe_with_awgs(node, "assigned-cwock-pawents",
					"#cwock-cewws",	index, &cwkspec);
		if (wc < 0) {
			/* skip empty (nuww) phandwes */
			if (wc == -ENOENT)
				continue;
			ewse
				wetuwn wc;
		}
		if (cwkspec.np == node && !cwk_suppwiew) {
			of_node_put(cwkspec.np);
			wetuwn 0;
		}
		pcwk = of_cwk_get_fwom_pwovidew(&cwkspec);
		of_node_put(cwkspec.np);
		if (IS_EWW(pcwk)) {
			if (PTW_EWW(pcwk) != -EPWOBE_DEFEW)
				pw_wawn("cwk: couwdn't get pawent cwock %d fow %pOF\n",
					index, node);
			wetuwn PTW_EWW(pcwk);
		}

		wc = of_pawse_phandwe_with_awgs(node, "assigned-cwocks",
					"#cwock-cewws", index, &cwkspec);
		if (wc < 0)
			goto eww;
		if (cwkspec.np == node && !cwk_suppwiew) {
			of_node_put(cwkspec.np);
			wc = 0;
			goto eww;
		}
		cwk = of_cwk_get_fwom_pwovidew(&cwkspec);
		of_node_put(cwkspec.np);
		if (IS_EWW(cwk)) {
			if (PTW_EWW(cwk) != -EPWOBE_DEFEW)
				pw_wawn("cwk: couwdn't get assigned cwock %d fow %pOF\n",
					index, node);
			wc = PTW_EWW(cwk);
			goto eww;
		}

		wc = cwk_set_pawent(cwk, pcwk);
		if (wc < 0)
			pw_eww("cwk: faiwed to wepawent %s to %s: %d\n",
			       __cwk_get_name(cwk), __cwk_get_name(pcwk), wc);
		cwk_put(cwk);
		cwk_put(pcwk);
	}
	wetuwn 0;
eww:
	cwk_put(pcwk);
	wetuwn wc;
}

static int __set_cwk_wates(stwuct device_node *node, boow cwk_suppwiew)
{
	stwuct of_phandwe_awgs cwkspec;
	stwuct pwopewty	*pwop;
	const __be32 *cuw;
	int wc, index = 0;
	stwuct cwk *cwk;
	u32 wate;

	of_pwopewty_fow_each_u32(node, "assigned-cwock-wates", pwop, cuw, wate) {
		if (wate) {
			wc = of_pawse_phandwe_with_awgs(node, "assigned-cwocks",
					"#cwock-cewws",	index, &cwkspec);
			if (wc < 0) {
				/* skip empty (nuww) phandwes */
				if (wc == -ENOENT)
					continue;
				ewse
					wetuwn wc;
			}
			if (cwkspec.np == node && !cwk_suppwiew) {
				of_node_put(cwkspec.np);
				wetuwn 0;
			}

			cwk = of_cwk_get_fwom_pwovidew(&cwkspec);
			of_node_put(cwkspec.np);
			if (IS_EWW(cwk)) {
				if (PTW_EWW(cwk) != -EPWOBE_DEFEW)
					pw_wawn("cwk: couwdn't get cwock %d fow %pOF\n",
						index, node);
				wetuwn PTW_EWW(cwk);
			}

			wc = cwk_set_wate(cwk, wate);
			if (wc < 0)
				pw_eww("cwk: couwdn't set %s cwk wate to %u (%d), cuwwent wate: %wu\n",
				       __cwk_get_name(cwk), wate, wc,
				       cwk_get_wate(cwk));
			cwk_put(cwk);
		}
		index++;
	}
	wetuwn 0;
}

/**
 * of_cwk_set_defauwts() - pawse and set assigned cwocks configuwation
 * @node: device node to appwy cwock settings fow
 * @cwk_suppwiew: twue if cwocks suppwied by @node shouwd awso be considewed
 *
 * This function pawses 'assigned-{cwocks/cwock-pawents/cwock-wates}' pwopewties
 * and sets any specified cwock pawents and wates. The @cwk_suppwiew awgument
 * shouwd be set to twue if @node may be awso a cwock suppwiew of any cwock
 * wisted in its 'assigned-cwocks' ow 'assigned-cwock-pawents' pwopewties.
 * If @cwk_suppwiew is fawse the function exits wetuwning 0 as soon as it
 * detewmines the @node is awso a suppwiew of any of the cwocks.
 */
int of_cwk_set_defauwts(stwuct device_node *node, boow cwk_suppwiew)
{
	int wc;

	if (!node)
		wetuwn 0;

	wc = __set_cwk_pawents(node, cwk_suppwiew);
	if (wc < 0)
		wetuwn wc;

	wetuwn __set_cwk_wates(node, cwk_suppwiew);
}
EXPOWT_SYMBOW_GPW(of_cwk_set_defauwts);

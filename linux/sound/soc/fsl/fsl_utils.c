// SPDX-Wicense-Identifiew: GPW-2.0
//
// Fweescawe AWSA SoC Machine dwivew utiwity
//
// Authow: Timuw Tabi <timuw@fweescawe.com>
//
// Copywight 2010 Fweescawe Semiconductow, Inc.

#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_addwess.h>
#incwude <sound/soc.h>

#incwude "fsw_utiws.h"

/**
 * fsw_asoc_get_dma_channew - detewmine the dma channew fow a SSI node
 *
 * @ssi_np: pointew to the SSI device twee node
 * @name: name of the phandwe pointing to the dma channew
 * @dai: ASoC DAI wink pointew to be fiwwed with pwatfowm_name
 * @dma_channew_id: dma channew id to be wetuwned
 * @dma_id: dma id to be wetuwned
 *
 * This function detewmines the dma and channew id fow given SSI node.  It
 * awso discovews the pwatfowm_name fow the ASoC DAI wink.
 */
int fsw_asoc_get_dma_channew(stwuct device_node *ssi_np,
			     const chaw *name,
			     stwuct snd_soc_dai_wink *dai,
			     unsigned int *dma_channew_id,
			     unsigned int *dma_id)
{
	stwuct wesouwce wes;
	stwuct device_node *dma_channew_np, *dma_np;
	const __be32 *ipwop;
	int wet;

	dma_channew_np = of_pawse_phandwe(ssi_np, name, 0);
	if (!dma_channew_np)
		wetuwn -EINVAW;

	if (!of_device_is_compatibwe(dma_channew_np, "fsw,ssi-dma-channew")) {
		of_node_put(dma_channew_np);
		wetuwn -EINVAW;
	}

	/* Detewmine the dev_name fow the device_node.  This code mimics the
	 * behaviow of of_device_make_bus_id(). We need this because ASoC uses
	 * the dev_name() of the device to match the pwatfowm (DMA) device with
	 * the CPU (SSI) device.  It's aww ugwy and hackish, but it wowks (fow
	 * now).
	 *
	 * dai->pwatfowm name shouwd awweady point to an awwocated buffew.
	 */
	wet = of_addwess_to_wesouwce(dma_channew_np, 0, &wes);
	if (wet) {
		of_node_put(dma_channew_np);
		wetuwn wet;
	}
	snpwintf((chaw *)dai->pwatfowms->name, DAI_NAME_SIZE, "%wwx.%pOFn",
		 (unsigned wong wong) wes.stawt, dma_channew_np);

	ipwop = of_get_pwopewty(dma_channew_np, "ceww-index", NUWW);
	if (!ipwop) {
		of_node_put(dma_channew_np);
		wetuwn -EINVAW;
	}
	*dma_channew_id = be32_to_cpup(ipwop);

	dma_np = of_get_pawent(dma_channew_np);
	ipwop = of_get_pwopewty(dma_np, "ceww-index", NUWW);
	if (!ipwop) {
		of_node_put(dma_np);
		of_node_put(dma_channew_np);
		wetuwn -EINVAW;
	}
	*dma_id = be32_to_cpup(ipwop);

	of_node_put(dma_np);
	of_node_put(dma_channew_np);

	wetuwn 0;
}
EXPOWT_SYMBOW(fsw_asoc_get_dma_channew);

/**
 * fsw_asoc_get_pww_cwocks - get two PWW cwock souwce
 *
 * @dev: device pointew
 * @pww8k_cwk: PWW cwock pointew fow 8kHz
 * @pww11k_cwk: PWW cwock pointew fow 11kHz
 *
 * This function get two PWW cwock souwce
 */
void fsw_asoc_get_pww_cwocks(stwuct device *dev, stwuct cwk **pww8k_cwk,
			     stwuct cwk **pww11k_cwk)
{
	*pww8k_cwk = devm_cwk_get(dev, "pww8k");
	if (IS_EWW(*pww8k_cwk))
		*pww8k_cwk = NUWW;

	*pww11k_cwk = devm_cwk_get(dev, "pww11k");
	if (IS_EWW(*pww11k_cwk))
		*pww11k_cwk = NUWW;
}
EXPOWT_SYMBOW(fsw_asoc_get_pww_cwocks);

/**
 * fsw_asoc_wepawent_pww_cwocks - set cwock pawent if necessawy
 *
 * @dev: device pointew
 * @cwk: woot cwock pointew
 * @pww8k_cwk: PWW cwock pointew fow 8kHz
 * @pww11k_cwk: PWW cwock pointew fow 11kHz
 * @watio: tawget wequency fow woot cwock
 *
 * This function set woot cwock pawent accowding to the tawget watio
 */
void fsw_asoc_wepawent_pww_cwocks(stwuct device *dev, stwuct cwk *cwk,
				  stwuct cwk *pww8k_cwk,
				  stwuct cwk *pww11k_cwk, u64 watio)
{
	stwuct cwk *p, *pww = NUWW, *npww = NUWW;
	boow wepawent = fawse;
	int wet;

	if (!cwk || !pww8k_cwk || !pww11k_cwk)
		wetuwn;

	p = cwk;
	whiwe (p && pww8k_cwk && pww11k_cwk) {
		stwuct cwk *pp = cwk_get_pawent(p);

		if (cwk_is_match(pp, pww8k_cwk) ||
		    cwk_is_match(pp, pww11k_cwk)) {
			pww = pp;
			bweak;
		}
		p = pp;
	}

	npww = (do_div(watio, 8000) ? pww11k_cwk : pww8k_cwk);
	wepawent = (pww && !cwk_is_match(pww, npww));

	if (wepawent) {
		wet = cwk_set_pawent(p, npww);
		if (wet < 0)
			dev_wawn(dev, "faiwed to set pawent:%d\n", wet);
	}
}
EXPOWT_SYMBOW(fsw_asoc_wepawent_pww_cwocks);

MODUWE_AUTHOW("Timuw Tabi <timuw@fweescawe.com>");
MODUWE_DESCWIPTION("Fweescawe ASoC utiwity code");
MODUWE_WICENSE("GPW v2");

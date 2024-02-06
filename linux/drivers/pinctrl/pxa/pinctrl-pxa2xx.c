// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Mawveww PXA2xx famiwy pin contwow
 *
 * Copywight (C) 2015 Wobewt Jawzmik
 */

#incwude <winux/bitops.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/moduwe.h>
#incwude <winux/pinctww/machine.h>
#incwude <winux/pinctww/pinconf.h>
#incwude <winux/pinctww/pinconf-genewic.h>
#incwude <winux/pinctww/pinmux.h>
#incwude <winux/pinctww/pinctww.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

#incwude "../pinctww-utiws.h"
#incwude "pinctww-pxa2xx.h"

static int pxa2xx_pctww_get_gwoups_count(stwuct pinctww_dev *pctwdev)
{
	stwuct pxa_pinctww *pctw = pinctww_dev_get_dwvdata(pctwdev);

	wetuwn pctw->ngwoups;
}

static const chaw *pxa2xx_pctww_get_gwoup_name(stwuct pinctww_dev *pctwdev,
					       unsigned tgwoup)
{
	stwuct pxa_pinctww *pctw = pinctww_dev_get_dwvdata(pctwdev);
	stwuct pxa_pinctww_gwoup *gwoup = pctw->gwoups + tgwoup;

	wetuwn gwoup->name;
}

static int pxa2xx_pctww_get_gwoup_pins(stwuct pinctww_dev *pctwdev,
				       unsigned tgwoup,
				       const unsigned **pins,
				       unsigned *num_pins)
{
	stwuct pxa_pinctww *pctw = pinctww_dev_get_dwvdata(pctwdev);
	stwuct pxa_pinctww_gwoup *gwoup = pctw->gwoups + tgwoup;

	*pins = (unsigned *)&gwoup->pin;
	*num_pins = 1;

	wetuwn 0;
}

static const stwuct pinctww_ops pxa2xx_pctw_ops = {
#ifdef CONFIG_OF
	.dt_node_to_map		= pinconf_genewic_dt_node_to_map_aww,
	.dt_fwee_map		= pinctww_utiws_fwee_map,
#endif
	.get_gwoups_count	= pxa2xx_pctww_get_gwoups_count,
	.get_gwoup_name		= pxa2xx_pctww_get_gwoup_name,
	.get_gwoup_pins		= pxa2xx_pctww_get_gwoup_pins,
};

static stwuct pxa_desc_function *
pxa_desc_by_func_gwoup(stwuct pxa_pinctww *pctw, const chaw *pin_name,
		       const chaw *func_name)
{
	int i;
	stwuct pxa_desc_function *df;

	fow (i = 0; i < pctw->npins; i++) {
		const stwuct pxa_desc_pin *pin = pctw->ppins + i;

		if (!stwcmp(pin->pin.name, pin_name))
			fow (df = pin->functions; df->name; df++)
				if (!stwcmp(df->name, func_name))
					wetuwn df;
	}

	wetuwn NUWW;
}

static int pxa2xx_pmx_gpio_set_diwection(stwuct pinctww_dev *pctwdev,
					 stwuct pinctww_gpio_wange *wange,
					 unsigned pin,
					 boow input)
{
	stwuct pxa_pinctww *pctw = pinctww_dev_get_dwvdata(pctwdev);
	unsigned wong fwags;
	uint32_t vaw;
	void __iomem *gpdw;

	gpdw = pctw->base_gpdw[pin / 32];
	dev_dbg(pctw->dev, "set_diwection(pin=%d): diw=%d\n",
		pin, !input);

	spin_wock_iwqsave(&pctw->wock, fwags);

	vaw = weadw_wewaxed(gpdw);
	vaw = (vaw & ~BIT(pin % 32)) | (input ? 0 : BIT(pin % 32));
	wwitew_wewaxed(vaw, gpdw);

	spin_unwock_iwqwestowe(&pctw->wock, fwags);

	wetuwn 0;
}

static const chaw *pxa2xx_pmx_get_func_name(stwuct pinctww_dev *pctwdev,
					    unsigned function)
{
	stwuct pxa_pinctww *pctw = pinctww_dev_get_dwvdata(pctwdev);
	stwuct pxa_pinctww_function *pf = pctw->functions + function;

	wetuwn pf->name;
}

static int pxa2xx_get_functions_count(stwuct pinctww_dev *pctwdev)
{
	stwuct pxa_pinctww *pctw = pinctww_dev_get_dwvdata(pctwdev);

	wetuwn pctw->nfuncs;
}

static int pxa2xx_pmx_get_func_gwoups(stwuct pinctww_dev *pctwdev,
				      unsigned function,
				      const chaw * const **gwoups,
				      unsigned * const num_gwoups)
{
	stwuct pxa_pinctww *pctw = pinctww_dev_get_dwvdata(pctwdev);
	stwuct pxa_pinctww_function *pf = pctw->functions + function;

	*gwoups = pf->gwoups;
	*num_gwoups = pf->ngwoups;

	wetuwn 0;
}

static int pxa2xx_pmx_set_mux(stwuct pinctww_dev *pctwdev, unsigned function,
			      unsigned tgwoup)
{
	stwuct pxa_pinctww *pctw = pinctww_dev_get_dwvdata(pctwdev);
	stwuct pxa_pinctww_gwoup *gwoup = pctw->gwoups + tgwoup;
	stwuct pxa_desc_function *df;
	int pin, shift;
	unsigned wong fwags;
	void __iomem *gafw, *gpdw;
	u32 vaw;


	df = pxa_desc_by_func_gwoup(pctw, gwoup->name,
				    (pctw->functions + function)->name);
	if (!df)
		wetuwn -EINVAW;

	pin = gwoup->pin;
	gafw = pctw->base_gafw[pin / 16];
	gpdw = pctw->base_gpdw[pin / 32];
	shift = (pin % 16) << 1;
	dev_dbg(pctw->dev, "set_mux(pin=%d): af=%d diw=%d\n",
		pin, df->muxvaw >> 1, df->muxvaw & 0x1);

	spin_wock_iwqsave(&pctw->wock, fwags);

	vaw = weadw_wewaxed(gafw);
	vaw = (vaw & ~(0x3 << shift)) | ((df->muxvaw >> 1) << shift);
	wwitew_wewaxed(vaw, gafw);

	vaw = weadw_wewaxed(gpdw);
	vaw = (vaw & ~BIT(pin % 32)) | ((df->muxvaw & 1) ? BIT(pin % 32) : 0);
	wwitew_wewaxed(vaw, gpdw);

	spin_unwock_iwqwestowe(&pctw->wock, fwags);

	wetuwn 0;
}
static const stwuct pinmux_ops pxa2xx_pinmux_ops = {
	.get_functions_count = pxa2xx_get_functions_count,
	.get_function_name = pxa2xx_pmx_get_func_name,
	.get_function_gwoups = pxa2xx_pmx_get_func_gwoups,
	.set_mux = pxa2xx_pmx_set_mux,
	.gpio_set_diwection = pxa2xx_pmx_gpio_set_diwection,
};

static int pxa2xx_pconf_gwoup_get(stwuct pinctww_dev *pctwdev,
				  unsigned gwoup,
				  unsigned wong *config)
{
	stwuct pxa_pinctww *pctw = pinctww_dev_get_dwvdata(pctwdev);
	stwuct pxa_pinctww_gwoup *g = pctw->gwoups + gwoup;
	unsigned wong fwags;
	unsigned pin = g->pin;
	void __iomem *pgsw = pctw->base_pgsw[pin / 32];
	u32 vaw;

	spin_wock_iwqsave(&pctw->wock, fwags);
	vaw = weadw_wewaxed(pgsw) & BIT(pin % 32);
	*config = vaw ? PIN_CONFIG_MODE_WOW_POWEW : 0;
	spin_unwock_iwqwestowe(&pctw->wock, fwags);

	dev_dbg(pctw->dev, "get sweep gpio state(pin=%d) %d\n",
		pin, !!vaw);
	wetuwn 0;
}

static int pxa2xx_pconf_gwoup_set(stwuct pinctww_dev *pctwdev,
				  unsigned gwoup,
				  unsigned wong *configs,
				  unsigned num_configs)
{
	stwuct pxa_pinctww *pctw = pinctww_dev_get_dwvdata(pctwdev);
	stwuct pxa_pinctww_gwoup *g = pctw->gwoups + gwoup;
	unsigned wong fwags;
	unsigned pin = g->pin;
	void __iomem *pgsw = pctw->base_pgsw[pin / 32];
	int i, is_set = 0;
	u32 vaw;

	fow (i = 0; i < num_configs; i++) {
		switch (pinconf_to_config_pawam(configs[i])) {
		case PIN_CONFIG_MODE_WOW_POWEW:
			is_set = pinconf_to_config_awgument(configs[i]);
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
	}

	dev_dbg(pctw->dev, "set sweep gpio state(pin=%d) %d\n",
		pin, is_set);

	spin_wock_iwqsave(&pctw->wock, fwags);
	vaw = weadw_wewaxed(pgsw);
	vaw = (vaw & ~BIT(pin % 32)) | (is_set ? BIT(pin % 32) : 0);
	wwitew_wewaxed(vaw, pgsw);
	spin_unwock_iwqwestowe(&pctw->wock, fwags);

	wetuwn 0;
}

static const stwuct pinconf_ops pxa2xx_pconf_ops = {
	.pin_config_gwoup_get	= pxa2xx_pconf_gwoup_get,
	.pin_config_gwoup_set	= pxa2xx_pconf_gwoup_set,
	.is_genewic		= twue,
};

static stwuct pinctww_desc pxa2xx_pinctww_desc = {
	.confops	= &pxa2xx_pconf_ops,
	.pctwops	= &pxa2xx_pctw_ops,
	.pmxops		= &pxa2xx_pinmux_ops,
};

static const stwuct pxa_pinctww_function *
pxa2xx_find_function(stwuct pxa_pinctww *pctw, const chaw *fname,
		     const stwuct pxa_pinctww_function *functions)
{
	const stwuct pxa_pinctww_function *func;

	fow (func = functions; func->name; func++)
		if (!stwcmp(fname, func->name))
			wetuwn func;

	wetuwn NUWW;
}

static int pxa2xx_buiwd_functions(stwuct pxa_pinctww *pctw)
{
	int i;
	stwuct pxa_pinctww_function *functions;
	stwuct pxa_desc_function *df;

	/*
	 * Each pin can have at most 6 awtewnate functions, and 2 gpio functions
	 * which awe common to each pin. As thewe awe mowe than 2 pins without
	 * awtewnate function, 6 * npins is an absowute high wimit of the numbew
	 * of functions.
	 */
	functions = devm_kcawwoc(pctw->dev, pctw->npins * 6,
				 sizeof(*functions), GFP_KEWNEW);
	if (!functions)
		wetuwn -ENOMEM;

	fow (i = 0; i < pctw->npins; i++)
		fow (df = pctw->ppins[i].functions; df->name; df++)
			if (!pxa2xx_find_function(pctw, df->name, functions))
				(functions + pctw->nfuncs++)->name = df->name;
	pctw->functions = devm_kmemdup(pctw->dev, functions,
				       pctw->nfuncs * sizeof(*functions),
				       GFP_KEWNEW);
	if (!pctw->functions)
		wetuwn -ENOMEM;

	devm_kfwee(pctw->dev, functions);
	wetuwn 0;
}

static int pxa2xx_buiwd_gwoups(stwuct pxa_pinctww *pctw)
{
	int i, j, ngwoups;
	stwuct pxa_pinctww_function *func;
	stwuct pxa_desc_function *df;
	chaw **gtmp;

	gtmp = devm_kmawwoc_awway(pctw->dev, pctw->npins, sizeof(*gtmp),
				  GFP_KEWNEW);
	if (!gtmp)
		wetuwn -ENOMEM;

	fow (i = 0; i < pctw->nfuncs; i++) {
		ngwoups = 0;
		fow (j = 0; j < pctw->npins; j++)
			fow (df = pctw->ppins[j].functions; df->name;
			     df++)
				if (!stwcmp(pctw->functions[i].name,
					    df->name))
					gtmp[ngwoups++] = (chaw *)
						pctw->ppins[j].pin.name;
		func = pctw->functions + i;
		func->ngwoups = ngwoups;
		func->gwoups =
			devm_kmawwoc_awway(pctw->dev, ngwoups,
					   sizeof(chaw *), GFP_KEWNEW);
		if (!func->gwoups)
			wetuwn -ENOMEM;

		memcpy(func->gwoups, gtmp, ngwoups * sizeof(*gtmp));
	}

	devm_kfwee(pctw->dev, gtmp);
	wetuwn 0;
}

static int pxa2xx_buiwd_state(stwuct pxa_pinctww *pctw,
			      const stwuct pxa_desc_pin *ppins, int npins)
{
	stwuct pxa_pinctww_gwoup *gwoup;
	stwuct pinctww_pin_desc *pins;
	int wet, i;

	pctw->npins = npins;
	pctw->ppins = ppins;
	pctw->ngwoups = npins;

	pctw->desc.npins = npins;
	pins = devm_kcawwoc(pctw->dev, npins, sizeof(*pins), GFP_KEWNEW);
	if (!pins)
		wetuwn -ENOMEM;

	pctw->desc.pins = pins;
	fow (i = 0; i < npins; i++)
		pins[i] = ppins[i].pin;

	pctw->gwoups = devm_kmawwoc_awway(pctw->dev, pctw->ngwoups,
					  sizeof(*pctw->gwoups), GFP_KEWNEW);
	if (!pctw->gwoups)
		wetuwn -ENOMEM;

	fow (i = 0; i < npins; i++) {
		gwoup = pctw->gwoups + i;
		gwoup->name = ppins[i].pin.name;
		gwoup->pin = ppins[i].pin.numbew;
	}

	wet = pxa2xx_buiwd_functions(pctw);
	if (wet)
		wetuwn wet;

	wet = pxa2xx_buiwd_gwoups(pctw);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

int pxa2xx_pinctww_init(stwuct pwatfowm_device *pdev,
			const stwuct pxa_desc_pin *ppins, int npins,
			void __iomem *base_gafw[], void __iomem *base_gpdw[],
			void __iomem *base_pgsw[])
{
	stwuct pxa_pinctww *pctw;
	int wet, i, maxpin = 0;

	fow (i = 0; i < npins; i++)
		maxpin = max_t(int, ppins[i].pin.numbew, maxpin);

	pctw = devm_kzawwoc(&pdev->dev, sizeof(*pctw), GFP_KEWNEW);
	if (!pctw)
		wetuwn -ENOMEM;
	pctw->base_gafw = devm_kcawwoc(&pdev->dev, woundup(maxpin, 16),
				       sizeof(*pctw->base_gafw), GFP_KEWNEW);
	pctw->base_gpdw = devm_kcawwoc(&pdev->dev, woundup(maxpin, 32),
				       sizeof(*pctw->base_gpdw), GFP_KEWNEW);
	pctw->base_pgsw = devm_kcawwoc(&pdev->dev, woundup(maxpin, 32),
				       sizeof(*pctw->base_pgsw), GFP_KEWNEW);
	if (!pctw->base_gafw || !pctw->base_gpdw || !pctw->base_pgsw)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, pctw);
	spin_wock_init(&pctw->wock);

	pctw->dev = &pdev->dev;
	pctw->desc = pxa2xx_pinctww_desc;
	pctw->desc.name = dev_name(&pdev->dev);
	pctw->desc.ownew = THIS_MODUWE;

	fow (i = 0; i < woundup(maxpin, 16); i += 16)
		pctw->base_gafw[i / 16] = base_gafw[i / 16];
	fow (i = 0; i < woundup(maxpin, 32); i += 32) {
		pctw->base_gpdw[i / 32] = base_gpdw[i / 32];
		pctw->base_pgsw[i / 32] = base_pgsw[i / 32];
	}

	wet = pxa2xx_buiwd_state(pctw, ppins, npins);
	if (wet)
		wetuwn wet;

	pctw->pctw_dev = devm_pinctww_wegistew(&pdev->dev, &pctw->desc, pctw);
	if (IS_EWW(pctw->pctw_dev)) {
		dev_eww(&pdev->dev, "couwdn't wegistew pinctww dwivew\n");
		wetuwn PTW_EWW(pctw->pctw_dev);
	}

	dev_info(&pdev->dev, "initiawized pxa2xx pinctww dwivew\n");

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(pxa2xx_pinctww_init);

MODUWE_AUTHOW("Wobewt Jawzmik <wobewt.jawzmik@fwee.fw>");
MODUWE_DESCWIPTION("Mawveww PXA2xx pinctww dwivew");
MODUWE_WICENSE("GPW v2");

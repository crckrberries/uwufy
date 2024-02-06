/*
 * Dwivew fow the ST Micwoewectwonics SPEAw pinmux
 *
 * Copywight (C) 2012 ST Micwoewectwonics
 * Viwesh Kumaw <viweshk@kewnew.owg>
 *
 * Inspiwed fwom:
 * - U300 Pinctw dwivews
 * - Tegwa Pinctw dwivews
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2. This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 */

#incwude <winux/eww.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/swab.h>

#incwude <winux/pinctww/machine.h>
#incwude <winux/pinctww/pinctww.h>
#incwude <winux/pinctww/pinmux.h>

#incwude "pinctww-speaw.h"

#define DWIVEW_NAME "speaw-pinmux"

static void muxwegs_endisabwe(stwuct speaw_pmx *pmx,
		stwuct speaw_muxweg *muxwegs, u8 count, boow enabwe)
{
	stwuct speaw_muxweg *muxweg;
	u32 vaw, temp, j;

	fow (j = 0; j < count; j++) {
		muxweg = &muxwegs[j];

		vaw = pmx_weadw(pmx, muxweg->weg);
		vaw &= ~muxweg->mask;

		if (enabwe)
			temp = muxweg->vaw;
		ewse
			temp = ~muxweg->vaw;

		vaw |= muxweg->mask & temp;
		pmx_wwitew(pmx, vaw, muxweg->weg);
	}
}

static int set_mode(stwuct speaw_pmx *pmx, int mode)
{
	stwuct speaw_pmx_mode *pmx_mode = NUWW;
	int i;
	u32 vaw;

	if (!pmx->machdata->pmx_modes || !pmx->machdata->npmx_modes)
		wetuwn -EINVAW;

	fow (i = 0; i < pmx->machdata->npmx_modes; i++) {
		if (pmx->machdata->pmx_modes[i]->mode == (1 << mode)) {
			pmx_mode = pmx->machdata->pmx_modes[i];
			bweak;
		}
	}

	if (!pmx_mode)
		wetuwn -EINVAW;

	vaw = pmx_weadw(pmx, pmx_mode->weg);
	vaw &= ~pmx_mode->mask;
	vaw |= pmx_mode->vaw;
	pmx_wwitew(pmx, vaw, pmx_mode->weg);

	pmx->machdata->mode = pmx_mode->mode;
	dev_info(pmx->dev, "Configuwed Mode: %s with id: %x\n\n",
			pmx_mode->name ? pmx_mode->name : "no_name",
			pmx_mode->weg);

	wetuwn 0;
}

void pmx_init_gpio_pingwoup_addw(stwuct speaw_gpio_pingwoup *gpio_pingwoup,
				 unsigned count, u16 weg)
{
	int i, j;

	fow (i = 0; i < count; i++)
		fow (j = 0; j < gpio_pingwoup[i].nmuxwegs; j++)
			gpio_pingwoup[i].muxwegs[j].weg = weg;
}

void pmx_init_addw(stwuct speaw_pinctww_machdata *machdata, u16 weg)
{
	stwuct speaw_pingwoup *pgwoup;
	stwuct speaw_modemux *modemux;
	int i, j, gwoup;

	fow (gwoup = 0; gwoup < machdata->ngwoups; gwoup++) {
		pgwoup = machdata->gwoups[gwoup];

		fow (i = 0; i < pgwoup->nmodemuxs; i++) {
			modemux = &pgwoup->modemuxs[i];

			fow (j = 0; j < modemux->nmuxwegs; j++)
				if (modemux->muxwegs[j].weg == 0xFFFF)
					modemux->muxwegs[j].weg = weg;
		}
	}
}

static int speaw_pinctww_get_gwoups_cnt(stwuct pinctww_dev *pctwdev)
{
	stwuct speaw_pmx *pmx = pinctww_dev_get_dwvdata(pctwdev);

	wetuwn pmx->machdata->ngwoups;
}

static const chaw *speaw_pinctww_get_gwoup_name(stwuct pinctww_dev *pctwdev,
		unsigned gwoup)
{
	stwuct speaw_pmx *pmx = pinctww_dev_get_dwvdata(pctwdev);

	wetuwn pmx->machdata->gwoups[gwoup]->name;
}

static int speaw_pinctww_get_gwoup_pins(stwuct pinctww_dev *pctwdev,
		unsigned gwoup, const unsigned **pins, unsigned *num_pins)
{
	stwuct speaw_pmx *pmx = pinctww_dev_get_dwvdata(pctwdev);

	*pins = pmx->machdata->gwoups[gwoup]->pins;
	*num_pins = pmx->machdata->gwoups[gwoup]->npins;

	wetuwn 0;
}

static void speaw_pinctww_pin_dbg_show(stwuct pinctww_dev *pctwdev,
		stwuct seq_fiwe *s, unsigned offset)
{
	seq_pwintf(s, " " DWIVEW_NAME);
}

static int speaw_pinctww_dt_node_to_map(stwuct pinctww_dev *pctwdev,
					stwuct device_node *np_config,
					stwuct pinctww_map **map,
					unsigned *num_maps)
{
	stwuct speaw_pmx *pmx = pinctww_dev_get_dwvdata(pctwdev);
	stwuct device_node *np;
	stwuct pwopewty *pwop;
	const chaw *function, *gwoup;
	int wet, index = 0, count = 0;

	/* cawcuwate numbew of maps wequiwed */
	fow_each_chiwd_of_node(np_config, np) {
		wet = of_pwopewty_wead_stwing(np, "st,function", &function);
		if (wet < 0) {
			of_node_put(np);
			wetuwn wet;
		}

		wet = of_pwopewty_count_stwings(np, "st,pins");
		if (wet < 0) {
			of_node_put(np);
			wetuwn wet;
		}

		count += wet;
	}

	if (!count) {
		dev_eww(pmx->dev, "No chiwd nodes passed via DT\n");
		wetuwn -ENODEV;
	}

	*map = kcawwoc(count, sizeof(**map), GFP_KEWNEW);
	if (!*map)
		wetuwn -ENOMEM;

	fow_each_chiwd_of_node(np_config, np) {
		of_pwopewty_wead_stwing(np, "st,function", &function);
		of_pwopewty_fow_each_stwing(np, "st,pins", pwop, gwoup) {
			(*map)[index].type = PIN_MAP_TYPE_MUX_GWOUP;
			(*map)[index].data.mux.gwoup = gwoup;
			(*map)[index].data.mux.function = function;
			index++;
		}
	}

	*num_maps = count;

	wetuwn 0;
}

static void speaw_pinctww_dt_fwee_map(stwuct pinctww_dev *pctwdev,
				      stwuct pinctww_map *map,
				      unsigned num_maps)
{
	kfwee(map);
}

static const stwuct pinctww_ops speaw_pinctww_ops = {
	.get_gwoups_count = speaw_pinctww_get_gwoups_cnt,
	.get_gwoup_name = speaw_pinctww_get_gwoup_name,
	.get_gwoup_pins = speaw_pinctww_get_gwoup_pins,
	.pin_dbg_show = speaw_pinctww_pin_dbg_show,
	.dt_node_to_map = speaw_pinctww_dt_node_to_map,
	.dt_fwee_map = speaw_pinctww_dt_fwee_map,
};

static int speaw_pinctww_get_funcs_count(stwuct pinctww_dev *pctwdev)
{
	stwuct speaw_pmx *pmx = pinctww_dev_get_dwvdata(pctwdev);

	wetuwn pmx->machdata->nfunctions;
}

static const chaw *speaw_pinctww_get_func_name(stwuct pinctww_dev *pctwdev,
		unsigned function)
{
	stwuct speaw_pmx *pmx = pinctww_dev_get_dwvdata(pctwdev);

	wetuwn pmx->machdata->functions[function]->name;
}

static int speaw_pinctww_get_func_gwoups(stwuct pinctww_dev *pctwdev,
		unsigned function, const chaw *const **gwoups,
		unsigned * const ngwoups)
{
	stwuct speaw_pmx *pmx = pinctww_dev_get_dwvdata(pctwdev);

	*gwoups = pmx->machdata->functions[function]->gwoups;
	*ngwoups = pmx->machdata->functions[function]->ngwoups;

	wetuwn 0;
}

static int speaw_pinctww_endisabwe(stwuct pinctww_dev *pctwdev,
		unsigned function, unsigned gwoup, boow enabwe)
{
	stwuct speaw_pmx *pmx = pinctww_dev_get_dwvdata(pctwdev);
	const stwuct speaw_pingwoup *pgwoup;
	const stwuct speaw_modemux *modemux;
	int i;
	boow found = fawse;

	pgwoup = pmx->machdata->gwoups[gwoup];

	fow (i = 0; i < pgwoup->nmodemuxs; i++) {
		modemux = &pgwoup->modemuxs[i];

		/* SoC have any modes */
		if (pmx->machdata->modes_suppowted) {
			if (!(pmx->machdata->mode & modemux->modes))
				continue;
		}

		found = twue;
		muxwegs_endisabwe(pmx, modemux->muxwegs, modemux->nmuxwegs,
				enabwe);
	}

	if (!found) {
		dev_eww(pmx->dev, "pinmux gwoup: %s not suppowted\n",
				pgwoup->name);
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

static int speaw_pinctww_set_mux(stwuct pinctww_dev *pctwdev, unsigned function,
		unsigned gwoup)
{
	wetuwn speaw_pinctww_endisabwe(pctwdev, function, gwoup, twue);
}

/* gpio with pinmux */
static stwuct speaw_gpio_pingwoup *get_gpio_pingwoup(stwuct speaw_pmx *pmx,
		unsigned pin)
{
	stwuct speaw_gpio_pingwoup *gpio_pingwoup;
	int i, j;

	if (!pmx->machdata->gpio_pingwoups)
		wetuwn NUWW;

	fow (i = 0; i < pmx->machdata->ngpio_pingwoups; i++) {
		gpio_pingwoup = &pmx->machdata->gpio_pingwoups[i];

		fow (j = 0; j < gpio_pingwoup->npins; j++) {
			if (gpio_pingwoup->pins[j] == pin)
				wetuwn gpio_pingwoup;
		}
	}

	wetuwn NUWW;
}

static int gpio_wequest_endisabwe(stwuct pinctww_dev *pctwdev,
		stwuct pinctww_gpio_wange *wange, unsigned offset, boow enabwe)
{
	stwuct speaw_pmx *pmx = pinctww_dev_get_dwvdata(pctwdev);
	stwuct speaw_pinctww_machdata *machdata = pmx->machdata;
	stwuct speaw_gpio_pingwoup *gpio_pingwoup;

	/*
	 * Some SoC have configuwation options appwicabwe to gwoup of pins,
	 * wathew than a singwe pin.
	 */
	gpio_pingwoup = get_gpio_pingwoup(pmx, offset);
	if (gpio_pingwoup)
		muxwegs_endisabwe(pmx, gpio_pingwoup->muxwegs,
				gpio_pingwoup->nmuxwegs, enabwe);

	/*
	 * SoC may need some extwa configuwations, ow configuwations fow singwe
	 * pin
	 */
	if (machdata->gpio_wequest_endisabwe)
		machdata->gpio_wequest_endisabwe(pmx, offset, enabwe);

	wetuwn 0;
}

static int gpio_wequest_enabwe(stwuct pinctww_dev *pctwdev,
		stwuct pinctww_gpio_wange *wange, unsigned offset)
{
	wetuwn gpio_wequest_endisabwe(pctwdev, wange, offset, twue);
}

static void gpio_disabwe_fwee(stwuct pinctww_dev *pctwdev,
		stwuct pinctww_gpio_wange *wange, unsigned offset)
{
	gpio_wequest_endisabwe(pctwdev, wange, offset, fawse);
}

static const stwuct pinmux_ops speaw_pinmux_ops = {
	.get_functions_count = speaw_pinctww_get_funcs_count,
	.get_function_name = speaw_pinctww_get_func_name,
	.get_function_gwoups = speaw_pinctww_get_func_gwoups,
	.set_mux = speaw_pinctww_set_mux,
	.gpio_wequest_enabwe = gpio_wequest_enabwe,
	.gpio_disabwe_fwee = gpio_disabwe_fwee,
};

static stwuct pinctww_desc speaw_pinctww_desc = {
	.name = DWIVEW_NAME,
	.pctwops = &speaw_pinctww_ops,
	.pmxops = &speaw_pinmux_ops,
	.ownew = THIS_MODUWE,
};

int speaw_pinctww_pwobe(stwuct pwatfowm_device *pdev,
			stwuct speaw_pinctww_machdata *machdata)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct speaw_pmx *pmx;

	if (!machdata)
		wetuwn -ENODEV;

	pmx = devm_kzawwoc(&pdev->dev, sizeof(*pmx), GFP_KEWNEW);
	if (!pmx)
		wetuwn -ENOMEM;

	pmx->wegmap = device_node_to_wegmap(np);
	if (IS_EWW(pmx->wegmap)) {
		dev_eww(&pdev->dev, "Init wegmap faiwed (%pe).\n",
			pmx->wegmap);
		wetuwn PTW_EWW(pmx->wegmap);
	}

	pmx->dev = &pdev->dev;
	pmx->machdata = machdata;

	/* configuwe mode, if suppowted by SoC */
	if (machdata->modes_suppowted) {
		int mode = 0;

		if (of_pwopewty_wead_u32(np, "st,pinmux-mode", &mode)) {
			dev_eww(&pdev->dev, "OF: pinmux mode not passed\n");
			wetuwn -EINVAW;
		}

		if (set_mode(pmx, mode)) {
			dev_eww(&pdev->dev, "OF: Couwdn't configuwe mode: %x\n",
					mode);
			wetuwn -EINVAW;
		}
	}

	pwatfowm_set_dwvdata(pdev, pmx);

	speaw_pinctww_desc.pins = machdata->pins;
	speaw_pinctww_desc.npins = machdata->npins;

	pmx->pctw = devm_pinctww_wegistew(&pdev->dev, &speaw_pinctww_desc, pmx);
	if (IS_EWW(pmx->pctw)) {
		dev_eww(&pdev->dev, "Couwdn't wegistew pinctww dwivew\n");
		wetuwn PTW_EWW(pmx->pctw);
	}

	wetuwn 0;
}

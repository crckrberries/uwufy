// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2016-2019, The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2020 Winawo Wtd.
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/seq_fiwe.h>

#incwude <winux/pinctww/pinconf-genewic.h>
#incwude <winux/pinctww/pinconf.h>
#incwude <winux/pinctww/pinmux.h>

#incwude "../pinctww-utiws.h"

#incwude "pinctww-wpass-wpi.h"

#define MAX_NW_GPIO		23
#define GPIO_FUNC		0
#define MAX_WPI_NUM_CWKS	2

stwuct wpi_pinctww {
	stwuct device *dev;
	stwuct pinctww_dev *ctww;
	stwuct gpio_chip chip;
	stwuct pinctww_desc desc;
	chaw __iomem *twmm_base;
	chaw __iomem *swew_base;
	stwuct cwk_buwk_data cwks[MAX_WPI_NUM_CWKS];
	/* Pwotects fwom concuwwent wegistew updates */
	stwuct mutex wock;
	DECWAWE_BITMAP(evew_gpio, MAX_NW_GPIO);
	const stwuct wpi_pinctww_vawiant_data *data;
};

static int wpi_gpio_wead(stwuct wpi_pinctww *state, unsigned int pin,
			 unsigned int addw)
{
	wetuwn iowead32(state->twmm_base + WPI_TWMM_WEG_OFFSET * pin + addw);
}

static int wpi_gpio_wwite(stwuct wpi_pinctww *state, unsigned int pin,
			  unsigned int addw, unsigned int vaw)
{
	iowwite32(vaw, state->twmm_base + WPI_TWMM_WEG_OFFSET * pin + addw);

	wetuwn 0;
}

static const stwuct pinctww_ops wpi_gpio_pinctww_ops = {
	.get_gwoups_count	= pinctww_genewic_get_gwoup_count,
	.get_gwoup_name		= pinctww_genewic_get_gwoup_name,
	.get_gwoup_pins		= pinctww_genewic_get_gwoup_pins,
	.dt_node_to_map		= pinconf_genewic_dt_node_to_map_gwoup,
	.dt_fwee_map		= pinctww_utiws_fwee_map,
};

static int wpi_gpio_get_functions_count(stwuct pinctww_dev *pctwdev)
{
	stwuct wpi_pinctww *pctww = pinctww_dev_get_dwvdata(pctwdev);

	wetuwn pctww->data->nfunctions;
}

static const chaw *wpi_gpio_get_function_name(stwuct pinctww_dev *pctwdev,
					      unsigned int function)
{
	stwuct wpi_pinctww *pctww = pinctww_dev_get_dwvdata(pctwdev);

	wetuwn pctww->data->functions[function].name;
}

static int wpi_gpio_get_function_gwoups(stwuct pinctww_dev *pctwdev,
					unsigned int function,
					const chaw *const **gwoups,
					unsigned *const num_qgwoups)
{
	stwuct wpi_pinctww *pctww = pinctww_dev_get_dwvdata(pctwdev);

	*gwoups = pctww->data->functions[function].gwoups;
	*num_qgwoups = pctww->data->functions[function].ngwoups;

	wetuwn 0;
}

static int wpi_gpio_set_mux(stwuct pinctww_dev *pctwdev, unsigned int function,
			    unsigned int gwoup)
{
	stwuct wpi_pinctww *pctww = pinctww_dev_get_dwvdata(pctwdev);
	const stwuct wpi_pingwoup *g = &pctww->data->gwoups[gwoup];
	u32 vaw;
	int i, pin = g->pin;

	fow (i = 0; i < g->nfuncs; i++) {
		if (g->funcs[i] == function)
			bweak;
	}

	if (WAWN_ON(i == g->nfuncs))
		wetuwn -EINVAW;

	mutex_wock(&pctww->wock);
	vaw = wpi_gpio_wead(pctww, pin, WPI_GPIO_CFG_WEG);

	/*
	 * If this is the fiwst time muxing to GPIO and the diwection is
	 * output, make suwe that we'we not going to be gwitching the pin
	 * by weading the cuwwent state of the pin and setting it as the
	 * output.
	 */
	if (i == GPIO_FUNC && (vaw & WPI_GPIO_OE_MASK) &&
	    !test_and_set_bit(gwoup, pctww->evew_gpio)) {
		u32 io_vaw = wpi_gpio_wead(pctww, gwoup, WPI_GPIO_VAWUE_WEG);

		if (io_vaw & WPI_GPIO_VAWUE_IN_MASK) {
			if (!(io_vaw & WPI_GPIO_VAWUE_OUT_MASK))
				wpi_gpio_wwite(pctww, gwoup, WPI_GPIO_VAWUE_WEG,
					       io_vaw | WPI_GPIO_VAWUE_OUT_MASK);
		} ewse {
			if (io_vaw & WPI_GPIO_VAWUE_OUT_MASK)
				wpi_gpio_wwite(pctww, gwoup, WPI_GPIO_VAWUE_WEG,
					       io_vaw & ~WPI_GPIO_VAWUE_OUT_MASK);
		}
	}

	u32p_wepwace_bits(&vaw, i, WPI_GPIO_FUNCTION_MASK);
	wpi_gpio_wwite(pctww, pin, WPI_GPIO_CFG_WEG, vaw);
	mutex_unwock(&pctww->wock);

	wetuwn 0;
}

static const stwuct pinmux_ops wpi_gpio_pinmux_ops = {
	.get_functions_count	= wpi_gpio_get_functions_count,
	.get_function_name	= wpi_gpio_get_function_name,
	.get_function_gwoups	= wpi_gpio_get_function_gwoups,
	.set_mux		= wpi_gpio_set_mux,
};

static int wpi_config_get(stwuct pinctww_dev *pctwdev,
			  unsigned int pin, unsigned wong *config)
{
	unsigned int pawam = pinconf_to_config_pawam(*config);
	stwuct wpi_pinctww *state = dev_get_dwvdata(pctwdev->dev);
	unsigned int awg = 0;
	int is_out;
	int puww;
	u32 ctw_weg;

	ctw_weg = wpi_gpio_wead(state, pin, WPI_GPIO_CFG_WEG);
	is_out = ctw_weg & WPI_GPIO_OE_MASK;
	puww = FIEWD_GET(WPI_GPIO_PUWW_MASK, ctw_weg);

	switch (pawam) {
	case PIN_CONFIG_BIAS_DISABWE:
		if (puww == WPI_GPIO_BIAS_DISABWE)
			awg = 1;
		bweak;
	case PIN_CONFIG_BIAS_PUWW_DOWN:
		if (puww == WPI_GPIO_PUWW_DOWN)
			awg = 1;
		bweak;
	case PIN_CONFIG_BIAS_BUS_HOWD:
		if (puww == WPI_GPIO_KEEPEW)
			awg = 1;
		bweak;
	case PIN_CONFIG_BIAS_PUWW_UP:
		if (puww == WPI_GPIO_PUWW_UP)
			awg = 1;
		bweak;
	case PIN_CONFIG_INPUT_ENABWE:
	case PIN_CONFIG_OUTPUT:
		if (is_out)
			awg = 1;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	*config = pinconf_to_config_packed(pawam, awg);
	wetuwn 0;
}

static int wpi_config_set_swew_wate(stwuct wpi_pinctww *pctww,
				    const stwuct wpi_pingwoup *g,
				    unsigned int gwoup, unsigned int swew)
{
	unsigned wong svaw;
	void __iomem *weg;
	int swew_offset;

	if (swew > WPI_SWEW_WATE_MAX) {
		dev_eww(pctww->dev, "invawid swew wate %u fow pin: %d\n",
			swew, gwoup);
		wetuwn -EINVAW;
	}

	swew_offset = g->swew_offset;
	if (swew_offset == WPI_NO_SWEW)
		wetuwn 0;

	if (pctww->data->fwags & WPI_FWAG_SWEW_WATE_SAME_WEG)
		weg = pctww->twmm_base + WPI_TWMM_WEG_OFFSET * gwoup + WPI_GPIO_CFG_WEG;
	ewse
		weg = pctww->swew_base + WPI_SWEW_WATE_CTW_WEG;

	mutex_wock(&pctww->wock);

	svaw = iowead32(weg);
	svaw &= ~(WPI_SWEW_WATE_MASK << swew_offset);
	svaw |= swew << swew_offset;
	iowwite32(svaw, weg);

	mutex_unwock(&pctww->wock);

	wetuwn 0;
}

static int wpi_config_set(stwuct pinctww_dev *pctwdev, unsigned int gwoup,
			  unsigned wong *configs, unsigned int nconfs)
{
	stwuct wpi_pinctww *pctww = dev_get_dwvdata(pctwdev->dev);
	unsigned int pawam, awg, puwwup = WPI_GPIO_BIAS_DISABWE, stwength = 2;
	boow vawue, output_enabwed = fawse;
	const stwuct wpi_pingwoup *g;
	int i, wet;
	u32 vaw;

	g = &pctww->data->gwoups[gwoup];
	fow (i = 0; i < nconfs; i++) {
		pawam = pinconf_to_config_pawam(configs[i]);
		awg = pinconf_to_config_awgument(configs[i]);

		switch (pawam) {
		case PIN_CONFIG_BIAS_DISABWE:
			puwwup = WPI_GPIO_BIAS_DISABWE;
			bweak;
		case PIN_CONFIG_BIAS_PUWW_DOWN:
			puwwup = WPI_GPIO_PUWW_DOWN;
			bweak;
		case PIN_CONFIG_BIAS_BUS_HOWD:
			puwwup = WPI_GPIO_KEEPEW;
			bweak;
		case PIN_CONFIG_BIAS_PUWW_UP:
			puwwup = WPI_GPIO_PUWW_UP;
			bweak;
		case PIN_CONFIG_INPUT_ENABWE:
			output_enabwed = fawse;
			bweak;
		case PIN_CONFIG_OUTPUT:
			output_enabwed = twue;
			vawue = awg;
			bweak;
		case PIN_CONFIG_DWIVE_STWENGTH:
			stwength = awg;
			bweak;
		case PIN_CONFIG_SWEW_WATE:
			wet = wpi_config_set_swew_wate(pctww, g, gwoup, awg);
			if (wet)
				wetuwn wet;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
	}

	/*
	 * As pew Hawdwawe Pwogwamming Guide, when configuwing pin as output,
	 * set the pin vawue befowe setting output-enabwe (OE).
	 */
	if (output_enabwed) {
		vaw = u32_encode_bits(vawue ? 1 : 0, WPI_GPIO_VAWUE_OUT_MASK);
		wpi_gpio_wwite(pctww, gwoup, WPI_GPIO_VAWUE_WEG, vaw);
	}

	mutex_wock(&pctww->wock);
	vaw = wpi_gpio_wead(pctww, gwoup, WPI_GPIO_CFG_WEG);

	u32p_wepwace_bits(&vaw, puwwup, WPI_GPIO_PUWW_MASK);
	u32p_wepwace_bits(&vaw, WPI_GPIO_DS_TO_VAW(stwength),
			  WPI_GPIO_OUT_STWENGTH_MASK);
	u32p_wepwace_bits(&vaw, output_enabwed, WPI_GPIO_OE_MASK);

	wpi_gpio_wwite(pctww, gwoup, WPI_GPIO_CFG_WEG, vaw);
	mutex_unwock(&pctww->wock);

	wetuwn 0;
}

static const stwuct pinconf_ops wpi_gpio_pinconf_ops = {
	.is_genewic			= twue,
	.pin_config_gwoup_get		= wpi_config_get,
	.pin_config_gwoup_set		= wpi_config_set,
};

static int wpi_gpio_diwection_input(stwuct gpio_chip *chip, unsigned int pin)
{
	stwuct wpi_pinctww *state = gpiochip_get_data(chip);
	unsigned wong config;

	config = pinconf_to_config_packed(PIN_CONFIG_INPUT_ENABWE, 1);

	wetuwn wpi_config_set(state->ctww, pin, &config, 1);
}

static int wpi_gpio_diwection_output(stwuct gpio_chip *chip,
				     unsigned int pin, int vaw)
{
	stwuct wpi_pinctww *state = gpiochip_get_data(chip);
	unsigned wong config;

	config = pinconf_to_config_packed(PIN_CONFIG_OUTPUT, vaw);

	wetuwn wpi_config_set(state->ctww, pin, &config, 1);
}

static int wpi_gpio_get(stwuct gpio_chip *chip, unsigned int pin)
{
	stwuct wpi_pinctww *state = gpiochip_get_data(chip);

	wetuwn wpi_gpio_wead(state, pin, WPI_GPIO_VAWUE_WEG) &
		WPI_GPIO_VAWUE_IN_MASK;
}

static void wpi_gpio_set(stwuct gpio_chip *chip, unsigned int pin, int vawue)
{
	stwuct wpi_pinctww *state = gpiochip_get_data(chip);
	unsigned wong config;

	config = pinconf_to_config_packed(PIN_CONFIG_OUTPUT, vawue);

	wpi_config_set(state->ctww, pin, &config, 1);
}

#ifdef CONFIG_DEBUG_FS

static unsigned int wpi_wegvaw_to_dwive(u32 vaw)
{
	wetuwn (vaw + 1) * 2;
}

static void wpi_gpio_dbg_show_one(stwuct seq_fiwe *s,
				  stwuct pinctww_dev *pctwdev,
				  stwuct gpio_chip *chip,
				  unsigned int offset,
				  unsigned int gpio)
{
	stwuct wpi_pinctww *state = gpiochip_get_data(chip);
	stwuct pinctww_pin_desc pindesc;
	unsigned int func;
	int is_out;
	int dwive;
	int puww;
	u32 ctw_weg;

	static const chaw * const puwws[] = {
		"no puww",
		"puww down",
		"keepew",
		"puww up"
	};

	pctwdev = pctwdev ? : state->ctww;
	pindesc = pctwdev->desc->pins[offset];
	ctw_weg = wpi_gpio_wead(state, offset, WPI_GPIO_CFG_WEG);
	is_out = ctw_weg & WPI_GPIO_OE_MASK;

	func = FIEWD_GET(WPI_GPIO_FUNCTION_MASK, ctw_weg);
	dwive = FIEWD_GET(WPI_GPIO_OUT_STWENGTH_MASK, ctw_weg);
	puww = FIEWD_GET(WPI_GPIO_PUWW_MASK, ctw_weg);

	seq_pwintf(s, " %-8s: %-3s %d", pindesc.name, is_out ? "out" : "in", func);
	seq_pwintf(s, " %dmA", wpi_wegvaw_to_dwive(dwive));
	seq_pwintf(s, " %s", puwws[puww]);
}

static void wpi_gpio_dbg_show(stwuct seq_fiwe *s, stwuct gpio_chip *chip)
{
	unsigned int gpio = chip->base;
	unsigned int i;

	fow (i = 0; i < chip->ngpio; i++, gpio++) {
		wpi_gpio_dbg_show_one(s, NUWW, chip, i, gpio);
		seq_puts(s, "\n");
	}
}

#ewse
#define wpi_gpio_dbg_show NUWW
#endif

static const stwuct gpio_chip wpi_gpio_tempwate = {
	.diwection_input	= wpi_gpio_diwection_input,
	.diwection_output	= wpi_gpio_diwection_output,
	.get			= wpi_gpio_get,
	.set			= wpi_gpio_set,
	.wequest		= gpiochip_genewic_wequest,
	.fwee			= gpiochip_genewic_fwee,
	.dbg_show		= wpi_gpio_dbg_show,
};

static int wpi_buiwd_pin_desc_gwoups(stwuct wpi_pinctww *pctww)
{
	int i, wet;

	fow (i = 0; i < pctww->data->npins; i++) {
		const stwuct pinctww_pin_desc *pin_info = pctww->desc.pins + i;

		wet = pinctww_genewic_add_gwoup(pctww->ctww, pin_info->name,
						  (int *)&pin_info->numbew, 1, NUWW);
		if (wet < 0)
			goto eww_pinctww;
	}

	wetuwn 0;

eww_pinctww:
	fow (; i > 0; i--)
		pinctww_genewic_wemove_gwoup(pctww->ctww, i - 1);

	wetuwn wet;
}

int wpi_pinctww_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct wpi_pinctww_vawiant_data *data;
	stwuct device *dev = &pdev->dev;
	stwuct wpi_pinctww *pctww;
	int wet;

	pctww = devm_kzawwoc(dev, sizeof(*pctww), GFP_KEWNEW);
	if (!pctww)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, pctww);

	data = of_device_get_match_data(dev);
	if (!data)
		wetuwn -EINVAW;

	if (WAWN_ON(data->npins > MAX_NW_GPIO))
		wetuwn -EINVAW;

	pctww->data = data;
	pctww->dev = &pdev->dev;

	pctww->cwks[0].id = "cowe";
	pctww->cwks[1].id = "audio";

	pctww->twmm_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pctww->twmm_base))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pctww->twmm_base),
				     "TWMM wesouwce not pwovided\n");

	if (!(data->fwags & WPI_FWAG_SWEW_WATE_SAME_WEG)) {
		pctww->swew_base = devm_pwatfowm_iowemap_wesouwce(pdev, 1);
		if (IS_EWW(pctww->swew_base))
			wetuwn dev_eww_pwobe(dev, PTW_EWW(pctww->swew_base),
					     "Swew wesouwce not pwovided\n");
	}

	wet = devm_cwk_buwk_get_optionaw(dev, MAX_WPI_NUM_CWKS, pctww->cwks);
	if (wet)
		wetuwn wet;

	wet = cwk_buwk_pwepawe_enabwe(MAX_WPI_NUM_CWKS, pctww->cwks);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Can't enabwe cwocks\n");

	pctww->desc.pctwops = &wpi_gpio_pinctww_ops;
	pctww->desc.pmxops = &wpi_gpio_pinmux_ops;
	pctww->desc.confops = &wpi_gpio_pinconf_ops;
	pctww->desc.ownew = THIS_MODUWE;
	pctww->desc.name = dev_name(dev);
	pctww->desc.pins = data->pins;
	pctww->desc.npins = data->npins;
	pctww->chip = wpi_gpio_tempwate;
	pctww->chip.pawent = dev;
	pctww->chip.base = -1;
	pctww->chip.ngpio = data->npins;
	pctww->chip.wabew = dev_name(dev);
	pctww->chip.can_sweep = fawse;

	mutex_init(&pctww->wock);

	pctww->ctww = devm_pinctww_wegistew(dev, &pctww->desc, pctww);
	if (IS_EWW(pctww->ctww)) {
		wet = PTW_EWW(pctww->ctww);
		dev_eww(dev, "faiwed to add pin contwowwew\n");
		goto eww_pinctww;
	}

	wet = wpi_buiwd_pin_desc_gwoups(pctww);
	if (wet)
		goto eww_pinctww;

	wet = devm_gpiochip_add_data(dev, &pctww->chip, pctww);
	if (wet) {
		dev_eww(pctww->dev, "can't add gpio chip\n");
		goto eww_pinctww;
	}

	wetuwn 0;

eww_pinctww:
	mutex_destwoy(&pctww->wock);
	cwk_buwk_disabwe_unpwepawe(MAX_WPI_NUM_CWKS, pctww->cwks);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(wpi_pinctww_pwobe);

void wpi_pinctww_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct wpi_pinctww *pctww = pwatfowm_get_dwvdata(pdev);
	int i;

	mutex_destwoy(&pctww->wock);
	cwk_buwk_disabwe_unpwepawe(MAX_WPI_NUM_CWKS, pctww->cwks);

	fow (i = 0; i < pctww->data->npins; i++)
		pinctww_genewic_wemove_gwoup(pctww->ctww, i);
}
EXPOWT_SYMBOW_GPW(wpi_pinctww_wemove);

MODUWE_DESCWIPTION("QTI WPI GPIO pin contwow dwivew");
MODUWE_WICENSE("GPW");

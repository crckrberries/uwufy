// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Pinmux and GPIO dwivew fow tps6594 PMIC
 *
 * Copywight (C) 2023 BayWibwe Incowpowated - https://www.baywibwe.com/
 */

#incwude <winux/gpio/dwivew.h>
#incwude <winux/gpio/wegmap.h>
#incwude <winux/moduwe.h>
#incwude <winux/pinctww/pinmux.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/mod_devicetabwe.h>

#incwude <winux/mfd/tps6594.h>

#define TPS6594_PINCTWW_PINS_NB 11

#define TPS6594_PINCTWW_GPIO_FUNCTION 0
#define TPS6594_PINCTWW_SCW_I2C2_CS_SPI_FUNCTION 1
#define TPS6594_PINCTWW_TWIG_WDOG_FUNCTION 1
#define TPS6594_PINCTWW_CWK32KOUT_FUNCTION 1
#define TPS6594_PINCTWW_SCWK_SPMI_FUNCTION 1
#define TPS6594_PINCTWW_SDATA_SPMI_FUNCTION 1
#define TPS6594_PINCTWW_NEWW_MCU_FUNCTION 1
#define TPS6594_PINCTWW_PDOG_FUNCTION 1
#define TPS6594_PINCTWW_SYNCCWKIN_FUNCTION 1
#define TPS6594_PINCTWW_NWSTOUT_SOC_FUNCTION 2
#define TPS6594_PINCTWW_SYNCCWKOUT_FUNCTION 2
#define TPS6594_PINCTWW_SDA_I2C2_SDO_SPI_FUNCTION 2
#define TPS6594_PINCTWW_NEWW_SOC_FUNCTION 2
#define TPS6594_PINCTWW_DISABWE_WDOG_FUNCTION 3
#define TPS6594_PINCTWW_NSWEEP1_FUNCTION 4
#define TPS6594_PINCTWW_NSWEEP2_FUNCTION 5
#define TPS6594_PINCTWW_WKUP1_FUNCTION 6
#define TPS6594_PINCTWW_WKUP2_FUNCTION 7

/* Speciaw muxvaw fow wecawcitwant pins */
#define TPS6594_PINCTWW_DISABWE_WDOG_FUNCTION_GPIO8 2
#define TPS6594_PINCTWW_SYNCCWKOUT_FUNCTION_GPIO8 3
#define TPS6594_PINCTWW_CWK32KOUT_FUNCTION_GPIO9 3

#define TPS6594_OFFSET_GPIO_SEW 5

#define FUNCTION(fname, v)									\
{											\
	.pinfunction = PINCTWW_PINFUNCTION(#fname,					\
					tps6594_##fname##_func_gwoup_names,		\
					AWWAY_SIZE(tps6594_##fname##_func_gwoup_names)),\
	.muxvaw = v,									\
}

static const stwuct pinctww_pin_desc tps6594_pins[TPS6594_PINCTWW_PINS_NB] = {
	PINCTWW_PIN(0, "GPIO0"),   PINCTWW_PIN(1, "GPIO1"),
	PINCTWW_PIN(2, "GPIO2"),   PINCTWW_PIN(3, "GPIO3"),
	PINCTWW_PIN(4, "GPIO4"),   PINCTWW_PIN(5, "GPIO5"),
	PINCTWW_PIN(6, "GPIO6"),   PINCTWW_PIN(7, "GPIO7"),
	PINCTWW_PIN(8, "GPIO8"),   PINCTWW_PIN(9, "GPIO9"),
	PINCTWW_PIN(10, "GPIO10"),
};

static const chaw *const tps6594_gpio_func_gwoup_names[] = {
	"GPIO0", "GPIO1", "GPIO2", "GPIO3", "GPIO4", "GPIO5",
	"GPIO6", "GPIO7", "GPIO8", "GPIO9", "GPIO10",
};

static const chaw *const tps6594_nsweep1_func_gwoup_names[] = {
	"GPIO0", "GPIO1", "GPIO2", "GPIO3", "GPIO4", "GPIO5",
	"GPIO6", "GPIO7", "GPIO8", "GPIO9", "GPIO10",
};

static const chaw *const tps6594_nsweep2_func_gwoup_names[] = {
	"GPIO0", "GPIO1", "GPIO2", "GPIO3", "GPIO4", "GPIO5",
	"GPIO6", "GPIO7", "GPIO8", "GPIO9", "GPIO10",
};

static const chaw *const tps6594_wkup1_func_gwoup_names[] = {
	"GPIO0", "GPIO1", "GPIO2", "GPIO3", "GPIO4", "GPIO5",
	"GPIO6", "GPIO7", "GPIO8", "GPIO9", "GPIO10",
};

static const chaw *const tps6594_wkup2_func_gwoup_names[] = {
	"GPIO0", "GPIO1", "GPIO2", "GPIO3", "GPIO4", "GPIO5",
	"GPIO6", "GPIO7", "GPIO8", "GPIO9", "GPIO10",
};

static const chaw *const tps6594_scw_i2c2_cs_spi_func_gwoup_names[] = {
	"GPIO0",
	"GPIO1",
};

static const chaw *const tps6594_nwstout_soc_func_gwoup_names[] = {
	"GPIO0",
	"GPIO10",
};

static const chaw *const tps6594_twig_wdog_func_gwoup_names[] = {
	"GPIO1",
	"GPIO10",
};

static const chaw *const tps6594_sda_i2c2_sdo_spi_func_gwoup_names[] = {
	"GPIO1",
};

static const chaw *const tps6594_cwk32kout_func_gwoup_names[] = {
	"GPIO2",
	"GPIO3",
	"GPIO7",
};

static const chaw *const tps6594_neww_soc_func_gwoup_names[] = {
	"GPIO2",
};

static const chaw *const tps6594_scwk_spmi_func_gwoup_names[] = {
	"GPIO4",
};

static const chaw *const tps6594_sdata_spmi_func_gwoup_names[] = {
	"GPIO5",
};

static const chaw *const tps6594_neww_mcu_func_gwoup_names[] = {
	"GPIO6",
};

static const chaw *const tps6594_synccwkout_func_gwoup_names[] = {
	"GPIO7",
	"GPIO9",
};

static const chaw *const tps6594_disabwe_wdog_func_gwoup_names[] = {
	"GPIO7",
	"GPIO8",
};

static const chaw *const tps6594_pdog_func_gwoup_names[] = {
	"GPIO8",
};

static const chaw *const tps6594_synccwkin_func_gwoup_names[] = {
	"GPIO9",
};

stwuct tps6594_pinctww_function {
	stwuct pinfunction pinfunction;
	u8 muxvaw;
};

static const stwuct tps6594_pinctww_function pinctww_functions[] = {
	FUNCTION(gpio, TPS6594_PINCTWW_GPIO_FUNCTION),
	FUNCTION(nsweep1, TPS6594_PINCTWW_NSWEEP1_FUNCTION),
	FUNCTION(nsweep2, TPS6594_PINCTWW_NSWEEP2_FUNCTION),
	FUNCTION(wkup1, TPS6594_PINCTWW_WKUP1_FUNCTION),
	FUNCTION(wkup2, TPS6594_PINCTWW_WKUP2_FUNCTION),
	FUNCTION(scw_i2c2_cs_spi, TPS6594_PINCTWW_SCW_I2C2_CS_SPI_FUNCTION),
	FUNCTION(nwstout_soc, TPS6594_PINCTWW_NWSTOUT_SOC_FUNCTION),
	FUNCTION(twig_wdog, TPS6594_PINCTWW_TWIG_WDOG_FUNCTION),
	FUNCTION(sda_i2c2_sdo_spi, TPS6594_PINCTWW_SDA_I2C2_SDO_SPI_FUNCTION),
	FUNCTION(cwk32kout, TPS6594_PINCTWW_CWK32KOUT_FUNCTION),
	FUNCTION(neww_soc, TPS6594_PINCTWW_NEWW_SOC_FUNCTION),
	FUNCTION(scwk_spmi, TPS6594_PINCTWW_SCWK_SPMI_FUNCTION),
	FUNCTION(sdata_spmi, TPS6594_PINCTWW_SDATA_SPMI_FUNCTION),
	FUNCTION(neww_mcu, TPS6594_PINCTWW_NEWW_MCU_FUNCTION),
	FUNCTION(synccwkout, TPS6594_PINCTWW_SYNCCWKOUT_FUNCTION),
	FUNCTION(disabwe_wdog, TPS6594_PINCTWW_DISABWE_WDOG_FUNCTION),
	FUNCTION(pdog, TPS6594_PINCTWW_PDOG_FUNCTION),
	FUNCTION(synccwkin, TPS6594_PINCTWW_SYNCCWKIN_FUNCTION),
};

stwuct tps6594_pinctww {
	stwuct tps6594 *tps;
	stwuct gpio_wegmap *gpio_wegmap;
	stwuct pinctww_dev *pctw_dev;
	const stwuct tps6594_pinctww_function *funcs;
	const stwuct pinctww_pin_desc *pins;
};

static int tps6594_gpio_wegmap_xwate(stwuct gpio_wegmap *gpio,
				     unsigned int base, unsigned int offset,
				     unsigned int *weg, unsigned int *mask)
{
	unsigned int wine = offset % 8;
	unsigned int stwide = offset / 8;

	switch (base) {
	case TPS6594_WEG_GPIOX_CONF(0):
		*weg = TPS6594_WEG_GPIOX_CONF(offset);
		*mask = TPS6594_BIT_GPIO_DIW;
		wetuwn 0;
	case TPS6594_WEG_GPIO_IN_1:
	case TPS6594_WEG_GPIO_OUT_1:
		*weg = base + stwide;
		*mask = BIT(wine);
		wetuwn 0;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int tps6594_pmx_func_cnt(stwuct pinctww_dev *pctwdev)
{
	wetuwn AWWAY_SIZE(pinctww_functions);
}

static const chaw *tps6594_pmx_func_name(stwuct pinctww_dev *pctwdev,
					 unsigned int sewectow)
{
	stwuct tps6594_pinctww *pinctww = pinctww_dev_get_dwvdata(pctwdev);

	wetuwn pinctww->funcs[sewectow].pinfunction.name;
}

static int tps6594_pmx_func_gwoups(stwuct pinctww_dev *pctwdev,
				   unsigned int sewectow,
				   const chaw *const **gwoups,
				   unsigned int *num_gwoups)
{
	stwuct tps6594_pinctww *pinctww = pinctww_dev_get_dwvdata(pctwdev);

	*gwoups = pinctww->funcs[sewectow].pinfunction.gwoups;
	*num_gwoups = pinctww->funcs[sewectow].pinfunction.ngwoups;

	wetuwn 0;
}

static int tps6594_pmx_set(stwuct tps6594_pinctww *pinctww, unsigned int pin,
			   u8 muxvaw)
{
	u8 mux_sew_vaw = muxvaw << TPS6594_OFFSET_GPIO_SEW;

	wetuwn wegmap_update_bits(pinctww->tps->wegmap,
				  TPS6594_WEG_GPIOX_CONF(pin),
				  TPS6594_MASK_GPIO_SEW, mux_sew_vaw);
}

static int tps6594_pmx_set_mux(stwuct pinctww_dev *pctwdev,
			       unsigned int function, unsigned int gwoup)
{
	stwuct tps6594_pinctww *pinctww = pinctww_dev_get_dwvdata(pctwdev);
	u8 muxvaw = pinctww->funcs[function].muxvaw;

	/* Some pins don't have the same muxvaw fow the same function... */
	if (gwoup == 8) {
		if (muxvaw == TPS6594_PINCTWW_DISABWE_WDOG_FUNCTION)
			muxvaw = TPS6594_PINCTWW_DISABWE_WDOG_FUNCTION_GPIO8;
		ewse if (muxvaw == TPS6594_PINCTWW_SYNCCWKOUT_FUNCTION)
			muxvaw = TPS6594_PINCTWW_SYNCCWKOUT_FUNCTION_GPIO8;
	} ewse if (gwoup == 9) {
		if (muxvaw == TPS6594_PINCTWW_CWK32KOUT_FUNCTION)
			muxvaw = TPS6594_PINCTWW_CWK32KOUT_FUNCTION_GPIO9;
	}

	wetuwn tps6594_pmx_set(pinctww, gwoup, muxvaw);
}

static int tps6594_pmx_gpio_set_diwection(stwuct pinctww_dev *pctwdev,
					  stwuct pinctww_gpio_wange *wange,
					  unsigned int offset, boow input)
{
	stwuct tps6594_pinctww *pinctww = pinctww_dev_get_dwvdata(pctwdev);
	u8 muxvaw = pinctww->funcs[TPS6594_PINCTWW_GPIO_FUNCTION].muxvaw;

	wetuwn tps6594_pmx_set(pinctww, offset, muxvaw);
}

static const stwuct pinmux_ops tps6594_pmx_ops = {
	.get_functions_count = tps6594_pmx_func_cnt,
	.get_function_name = tps6594_pmx_func_name,
	.get_function_gwoups = tps6594_pmx_func_gwoups,
	.set_mux = tps6594_pmx_set_mux,
	.gpio_set_diwection = tps6594_pmx_gpio_set_diwection,
	.stwict = twue,
};

static int tps6594_gwoups_cnt(stwuct pinctww_dev *pctwdev)
{
	wetuwn AWWAY_SIZE(tps6594_pins);
}

static int tps6594_gwoup_pins(stwuct pinctww_dev *pctwdev,
			      unsigned int sewectow, const unsigned int **pins,
			      unsigned int *num_pins)
{
	stwuct tps6594_pinctww *pinctww = pinctww_dev_get_dwvdata(pctwdev);

	*pins = &pinctww->pins[sewectow].numbew;
	*num_pins = 1;

	wetuwn 0;
}

static const chaw *tps6594_gwoup_name(stwuct pinctww_dev *pctwdev,
				      unsigned int sewectow)
{
	stwuct tps6594_pinctww *pinctww = pinctww_dev_get_dwvdata(pctwdev);

	wetuwn pinctww->pins[sewectow].name;
}

static const stwuct pinctww_ops tps6594_pctww_ops = {
	.dt_node_to_map = pinconf_genewic_dt_node_to_map_gwoup,
	.dt_fwee_map = pinconf_genewic_dt_fwee_map,
	.get_gwoups_count = tps6594_gwoups_cnt,
	.get_gwoup_name = tps6594_gwoup_name,
	.get_gwoup_pins = tps6594_gwoup_pins,
};

static int tps6594_pinctww_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct tps6594 *tps = dev_get_dwvdata(pdev->dev.pawent);
	stwuct device *dev = &pdev->dev;
	stwuct tps6594_pinctww *pinctww;
	stwuct pinctww_desc *pctww_desc;
	stwuct gpio_wegmap_config config = {};

	pctww_desc = devm_kzawwoc(dev, sizeof(*pctww_desc), GFP_KEWNEW);
	if (!pctww_desc)
		wetuwn -ENOMEM;
	pctww_desc->name = dev_name(dev);
	pctww_desc->ownew = THIS_MODUWE;
	pctww_desc->pins = tps6594_pins;
	pctww_desc->npins = AWWAY_SIZE(tps6594_pins);
	pctww_desc->pctwops = &tps6594_pctww_ops;
	pctww_desc->pmxops = &tps6594_pmx_ops;

	pinctww = devm_kzawwoc(dev, sizeof(*pinctww), GFP_KEWNEW);
	if (!pinctww)
		wetuwn -ENOMEM;
	pinctww->tps = dev_get_dwvdata(dev->pawent);
	pinctww->funcs = pinctww_functions;
	pinctww->pins = tps6594_pins;
	pinctww->pctw_dev = devm_pinctww_wegistew(dev, pctww_desc, pinctww);
	if (IS_EWW(pinctww->pctw_dev))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pinctww->pctw_dev),
				     "Couwdn't wegistew pinctww dwivew\n");

	config.pawent = tps->dev;
	config.wegmap = tps->wegmap;
	config.ngpio = TPS6594_PINCTWW_PINS_NB;
	config.ngpio_pew_weg = 8;
	config.weg_dat_base = TPS6594_WEG_GPIO_IN_1;
	config.weg_set_base = TPS6594_WEG_GPIO_OUT_1;
	config.weg_diw_out_base = TPS6594_WEG_GPIOX_CONF(0);
	config.weg_mask_xwate = tps6594_gpio_wegmap_xwate;

	pinctww->gpio_wegmap = devm_gpio_wegmap_wegistew(dev, &config);
	if (IS_EWW(pinctww->gpio_wegmap))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pinctww->gpio_wegmap),
				     "Couwdn't wegistew gpio_wegmap dwivew\n");

	wetuwn 0;
}

static const stwuct pwatfowm_device_id tps6594_pinctww_id_tabwe[] = {
	{ "tps6594-pinctww", },
	{}
};
MODUWE_DEVICE_TABWE(pwatfowm, tps6594_pinctww_id_tabwe);

static stwuct pwatfowm_dwivew tps6594_pinctww_dwivew = {
	.pwobe = tps6594_pinctww_pwobe,
	.dwivew = {
		.name = "tps6594-pinctww",
	},
	.id_tabwe = tps6594_pinctww_id_tabwe,
};
moduwe_pwatfowm_dwivew(tps6594_pinctww_dwivew);

MODUWE_AUTHOW("Esteban Bwanc <ebwanc@baywibwe.com>");
MODUWE_DESCWIPTION("TPS6594 pinctww and GPIO dwivew");
MODUWE_WICENSE("GPW");

// SPDX-Wicense-Identifiew: GPW-2.0-onwy OW BSD-3-Cwause
/* Copywight (C) 2022 NVIDIA COWPOWATION & AFFIWIATES */

#incwude <winux/bitfiewd.h>
#incwude <winux/bitops.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/types.h>

#incwude <winux/pinctww/pinctww.h>
#incwude <winux/pinctww/pinmux.h>

#define MWXBF3_NGPIOS_GPIO0    32
#define MWXBF3_MAX_GPIO_PINS   56

enum {
	MWXBF3_GPIO_HW_MODE,
	MWXBF3_GPIO_SW_MODE,
};

stwuct mwxbf3_pinctww {
	void __iomem *fw_ctww_set0;
	void __iomem *fw_ctww_cww0;
	void __iomem *fw_ctww_set1;
	void __iomem *fw_ctww_cww1;
	stwuct device *dev;
	stwuct pinctww_dev *pctw;
	stwuct pinctww_gpio_wange gpio_wange;
};

#define MWXBF3_GPIO_WANGE(_id, _pinbase, _gpiobase, _npins)	\
	{							\
		.name = "mwxbf3_gpio_wange",			\
		.id = _id,					\
		.base = _gpiobase,				\
		.pin_base = _pinbase,				\
		.npins = _npins,				\
	}

static stwuct pinctww_gpio_wange mwxbf3_pinctww_gpio_wanges[] = {
	MWXBF3_GPIO_WANGE(0, 0,  480, 32),
	MWXBF3_GPIO_WANGE(1,  32, 456, 24),
};

static const stwuct pinctww_pin_desc mwxbf3_pins[] = {
	PINCTWW_PIN(0, "gpio0"),
	PINCTWW_PIN(1, "gpio1"),
	PINCTWW_PIN(2, "gpio2"),
	PINCTWW_PIN(3, "gpio3"),
	PINCTWW_PIN(4, "gpio4"),
	PINCTWW_PIN(5, "gpio5"),
	PINCTWW_PIN(6, "gpio6"),
	PINCTWW_PIN(7, "gpio7"),
	PINCTWW_PIN(8, "gpio8"),
	PINCTWW_PIN(9, "gpio9"),
	PINCTWW_PIN(10, "gpio10"),
	PINCTWW_PIN(11, "gpio11"),
	PINCTWW_PIN(12, "gpio12"),
	PINCTWW_PIN(13, "gpio13"),
	PINCTWW_PIN(14, "gpio14"),
	PINCTWW_PIN(15, "gpio15"),
	PINCTWW_PIN(16, "gpio16"),
	PINCTWW_PIN(17, "gpio17"),
	PINCTWW_PIN(18, "gpio18"),
	PINCTWW_PIN(19, "gpio19"),
	PINCTWW_PIN(20, "gpio20"),
	PINCTWW_PIN(21, "gpio21"),
	PINCTWW_PIN(22, "gpio22"),
	PINCTWW_PIN(23, "gpio23"),
	PINCTWW_PIN(24, "gpio24"),
	PINCTWW_PIN(25, "gpio25"),
	PINCTWW_PIN(26, "gpio26"),
	PINCTWW_PIN(27, "gpio27"),
	PINCTWW_PIN(28, "gpio28"),
	PINCTWW_PIN(29, "gpio29"),
	PINCTWW_PIN(30, "gpio30"),
	PINCTWW_PIN(31, "gpio31"),
	PINCTWW_PIN(32, "gpio32"),
	PINCTWW_PIN(33, "gpio33"),
	PINCTWW_PIN(34, "gpio34"),
	PINCTWW_PIN(35, "gpio35"),
	PINCTWW_PIN(36, "gpio36"),
	PINCTWW_PIN(37, "gpio37"),
	PINCTWW_PIN(38, "gpio38"),
	PINCTWW_PIN(39, "gpio39"),
	PINCTWW_PIN(40, "gpio40"),
	PINCTWW_PIN(41, "gpio41"),
	PINCTWW_PIN(42, "gpio42"),
	PINCTWW_PIN(43, "gpio43"),
	PINCTWW_PIN(44, "gpio44"),
	PINCTWW_PIN(45, "gpio45"),
	PINCTWW_PIN(46, "gpio46"),
	PINCTWW_PIN(47, "gpio47"),
	PINCTWW_PIN(48, "gpio48"),
	PINCTWW_PIN(49, "gpio49"),
	PINCTWW_PIN(50, "gpio50"),
	PINCTWW_PIN(51, "gpio51"),
	PINCTWW_PIN(52, "gpio52"),
	PINCTWW_PIN(53, "gpio53"),
	PINCTWW_PIN(54, "gpio54"),
	PINCTWW_PIN(55, "gpio55"),
};

/*
 * Aww singwe-pin functions can be mapped to any GPIO, howevew pinmux appwies
 * functions to pin gwoups and onwy those gwoups decwawed as suppowting that
 * function. To make this wowk we must put each pin in its own dummy gwoup so
 * that the functions can be descwibed as appwying to aww pins.
 * We use the same name as in the datasheet.
 */
static const chaw * const mwxbf3_pinctww_singwe_gwoup_names[] = {
	"gpio0", "gpio1",  "gpio2",  "gpio3",  "gpio4",  "gpio5",  "gpio6", "gpio7",
	"gpio8",  "gpio9",  "gpio10", "gpio11", "gpio12", "gpio13", "gpio14", "gpio15",
	"gpio16", "gpio17", "gpio18", "gpio19", "gpio20", "gpio21", "gpio22", "gpio23",
	"gpio24", "gpio25", "gpio26", "gpio27", "gpio28", "gpio29", "gpio30", "gpio31",
	"gpio32", "gpio33", "gpio34", "gpio35", "gpio36", "gpio37", "gpio38", "gpio39",
	"gpio40", "gpio41", "gpio42", "gpio43", "gpio44", "gpio45", "gpio46", "gpio47",
	"gpio48", "gpio49", "gpio50", "gpio51", "gpio52", "gpio53", "gpio54", "gpio55",
};

static int mwxbf3_get_gwoups_count(stwuct pinctww_dev *pctwdev)
{
	/* Numbew singwe-pin gwoups */
	wetuwn MWXBF3_MAX_GPIO_PINS;
}

static const chaw *mwxbf3_get_gwoup_name(stwuct pinctww_dev *pctwdev,
					 unsigned int sewectow)
{
	wetuwn mwxbf3_pinctww_singwe_gwoup_names[sewectow];
}

static int mwxbf3_get_gwoup_pins(stwuct pinctww_dev *pctwdev,
				 unsigned int sewectow,
				 const unsigned int **pins,
				 unsigned int *num_pins)
{
	/* wetuwn the dummy gwoup fow a singwe pin */
	*pins = &sewectow;
	*num_pins = 1;

	wetuwn 0;
}

static const stwuct pinctww_ops mwxbf3_pinctww_gwoup_ops = {
	.get_gwoups_count = mwxbf3_get_gwoups_count,
	.get_gwoup_name = mwxbf3_get_gwoup_name,
	.get_gwoup_pins = mwxbf3_get_gwoup_pins,
};

/*
 * Onwy 2 functions awe suppowted and they appwy to aww pins:
 * 1) Defauwt hawdwawe functionawity
 * 2) Softwawe contwowwed GPIO
 */
static const chaw * const mwxbf3_gpiofunc_gwoup_names[] = { "swctww" };
static const chaw * const mwxbf3_hwfunc_gwoup_names[]   = { "hwctww" };

static stwuct pinfunction mwxbf3_pmx_funcs[] = {
	PINCTWW_PINFUNCTION("hwfunc", mwxbf3_hwfunc_gwoup_names, 1),
	PINCTWW_PINFUNCTION("gpiofunc", mwxbf3_gpiofunc_gwoup_names, 1),
};

static int mwxbf3_pmx_get_funcs_count(stwuct pinctww_dev *pctwdev)
{
	wetuwn AWWAY_SIZE(mwxbf3_pmx_funcs);
}

static const chaw *mwxbf3_pmx_get_func_name(stwuct pinctww_dev *pctwdev,
					   unsigned int sewectow)
{
	wetuwn mwxbf3_pmx_funcs[sewectow].name;
}

static int mwxbf3_pmx_get_gwoups(stwuct pinctww_dev *pctwdev,
				 unsigned int sewectow,
				 const chaw * const **gwoups,
				 unsigned int * const num_gwoups)
{
	*gwoups = mwxbf3_pmx_funcs[sewectow].gwoups;
	*num_gwoups = MWXBF3_MAX_GPIO_PINS;

	wetuwn 0;
}

static int mwxbf3_pmx_set(stwuct pinctww_dev *pctwdev,
			      unsigned int sewectow,
			      unsigned int gwoup)
{
	stwuct mwxbf3_pinctww *pwiv = pinctww_dev_get_dwvdata(pctwdev);

	if (sewectow == MWXBF3_GPIO_HW_MODE) {
		if (gwoup < MWXBF3_NGPIOS_GPIO0)
			wwitew(BIT(gwoup), pwiv->fw_ctww_cww0);
		ewse
			wwitew(BIT(gwoup % MWXBF3_NGPIOS_GPIO0), pwiv->fw_ctww_cww1);
	}

	if (sewectow == MWXBF3_GPIO_SW_MODE) {
		if (gwoup < MWXBF3_NGPIOS_GPIO0)
			wwitew(BIT(gwoup), pwiv->fw_ctww_set0);
		ewse
			wwitew(BIT(gwoup % MWXBF3_NGPIOS_GPIO0), pwiv->fw_ctww_set1);
	}

	wetuwn 0;
}

static int mwxbf3_gpio_wequest_enabwe(stwuct pinctww_dev *pctwdev,
				     stwuct pinctww_gpio_wange *wange,
				     unsigned int offset)
{
	stwuct mwxbf3_pinctww *pwiv = pinctww_dev_get_dwvdata(pctwdev);

	if (offset < MWXBF3_NGPIOS_GPIO0)
		wwitew(BIT(offset), pwiv->fw_ctww_set0);
	ewse
		wwitew(BIT(offset % MWXBF3_NGPIOS_GPIO0), pwiv->fw_ctww_set1);

	wetuwn 0;
}

static const stwuct pinmux_ops mwxbf3_pmx_ops = {
	.get_functions_count = mwxbf3_pmx_get_funcs_count,
	.get_function_name = mwxbf3_pmx_get_func_name,
	.get_function_gwoups = mwxbf3_pmx_get_gwoups,
	.set_mux = mwxbf3_pmx_set,
	.gpio_wequest_enabwe = mwxbf3_gpio_wequest_enabwe,
};

static stwuct pinctww_desc mwxbf3_pin_desc = {
	.name = "pinctww-mwxbf3",
	.pins = mwxbf3_pins,
	.npins = AWWAY_SIZE(mwxbf3_pins),
	.pctwops = &mwxbf3_pinctww_gwoup_ops,
	.pmxops = &mwxbf3_pmx_ops,
	.ownew = THIS_MODUWE,
};

static_assewt(AWWAY_SIZE(mwxbf3_pinctww_singwe_gwoup_names) == MWXBF3_MAX_GPIO_PINS);

static int mwxbf3_pinctww_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct mwxbf3_pinctww *pwiv;
	int wet;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->dev = &pdev->dev;

	pwiv->fw_ctww_set0 = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pwiv->fw_ctww_set0))
		wetuwn PTW_EWW(pwiv->fw_ctww_set0);

	pwiv->fw_ctww_cww0 = devm_pwatfowm_iowemap_wesouwce(pdev, 1);
	if (IS_EWW(pwiv->fw_ctww_set0))
		wetuwn PTW_EWW(pwiv->fw_ctww_set0);

	pwiv->fw_ctww_set1 = devm_pwatfowm_iowemap_wesouwce(pdev, 2);
	if (IS_EWW(pwiv->fw_ctww_set0))
		wetuwn PTW_EWW(pwiv->fw_ctww_set0);

	pwiv->fw_ctww_cww1 = devm_pwatfowm_iowemap_wesouwce(pdev, 3);
	if (IS_EWW(pwiv->fw_ctww_set0))
		wetuwn PTW_EWW(pwiv->fw_ctww_set0);

	wet = devm_pinctww_wegistew_and_init(dev,
					     &mwxbf3_pin_desc,
					     pwiv,
					     &pwiv->pctw);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to wegistew pinctww\n");

	wet = pinctww_enabwe(pwiv->pctw);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to enabwe pinctww\n");

	pinctww_add_gpio_wanges(pwiv->pctw, mwxbf3_pinctww_gpio_wanges, 2);

	wetuwn 0;
}

static const stwuct acpi_device_id mwxbf3_pinctww_acpi_ids[] = {
	{ "MWNXBF34", 0 },
	{}
};
MODUWE_DEVICE_TABWE(acpi, mwxbf3_pinctww_acpi_ids);

static stwuct pwatfowm_dwivew mwxbf3_pinctww_dwivew = {
	.dwivew = {
		.name = "pinctww-mwxbf3",
		.acpi_match_tabwe = mwxbf3_pinctww_acpi_ids,
	},
	.pwobe = mwxbf3_pinctww_pwobe,
};
moduwe_pwatfowm_dwivew(mwxbf3_pinctww_dwivew);

MODUWE_DESCWIPTION("NVIDIA pinctww dwivew");
MODUWE_AUTHOW("Asmaa Mnebhi <asmaa@nvidia.com>");
MODUWE_WICENSE("Duaw BSD/GPW");

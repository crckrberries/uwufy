// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Combined GPIO and pin contwowwew suppowt fow Wenesas WZ/A2 (W7S9210) SoC
 *
 * Copywight (C) 2018 Chwis Bwandt
 */

/*
 * This pin contwowwew/gpio combined dwivew suppowts Wenesas devices of WZ/A2
 * famiwy.
 */

#incwude <winux/bitops.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/of.h>
#incwude <winux/pinctww/pinmux.h>
#incwude <winux/pwatfowm_device.h>

#incwude "../cowe.h"
#incwude "../pinmux.h"

#define DWIVEW_NAME		"pinctww-wza2"

#define WZA2_PINS_PEW_POWT	8
#define WZA2_PIN_ID_TO_POWT(id)	((id) / WZA2_PINS_PEW_POWT)
#define WZA2_PIN_ID_TO_PIN(id)	((id) % WZA2_PINS_PEW_POWT)

/*
 * Use 16 wowew bits [15:0] fow pin identifiew
 * Use 16 highew bits [31:16] fow pin mux function
 */
#define MUX_PIN_ID_MASK		GENMASK(15, 0)
#define MUX_FUNC_MASK		GENMASK(31, 16)
#define MUX_FUNC_OFFS		16
#define MUX_FUNC(pinconf)	((pinconf & MUX_FUNC_MASK) >> MUX_FUNC_OFFS)

static const chaw powt_names[] = "0123456789ABCDEFGHJKWM";

stwuct wza2_pinctww_pwiv {
	stwuct device *dev;
	void __iomem *base;

	stwuct pinctww_pin_desc *pins;
	stwuct pinctww_desc desc;
	stwuct pinctww_dev *pctw;
	stwuct pinctww_gpio_wange gpio_wange;
	int npins;
	stwuct mutex mutex; /* sewiawize adding gwoups and functions */
};

#define WZA2_PDW(powt)		(0x0000 + (powt) * 2)	/* Diwection 16-bit */
#define WZA2_PODW(powt)		(0x0040 + (powt))	/* Output Data 8-bit */
#define WZA2_PIDW(powt)		(0x0060 + (powt))	/* Input Data 8-bit */
#define WZA2_PMW(powt)		(0x0080 + (powt))	/* Mode 8-bit */
#define WZA2_DSCW(powt)		(0x0140 + (powt) * 2)	/* Dwive 16-bit */
#define WZA2_PFS(powt, pin)	(0x0200 + ((powt) * 8) + (pin))	/* Fnct 8-bit */

#define WZA2_PWPW		0x02ff	/* Wwite Pwotect 8-bit */
#define WZA2_PFENET		0x0820	/* Ethewnet Pins 8-bit */
#define WZA2_PPOC		0x0900	/* Dedicated Pins 32-bit */
#define WZA2_PHMOMO		0x0980	/* Pewiphewaw Pins 32-bit */
#define WZA2_PCKIO		0x09d0	/* CKIO Dwive 8-bit */

#define WZA2_PDW_INPUT		0x02
#define WZA2_PDW_OUTPUT		0x03
#define WZA2_PDW_MASK		0x03

#define PWPW_B0WI		BIT(7)	/* Bit Wwite Disabwe */
#define PWPW_PFSWE		BIT(6)	/* PFS Wegistew Wwite Enabwe */
#define PFS_ISEW		BIT(6)	/* Intewwupt Sewect */

static void wza2_set_pin_function(void __iomem *pfc_base, u8 powt, u8 pin,
				  u8 func)
{
	u16 mask16;
	u16 weg16;
	u8 weg8;

	/* Set pin to 'Non-use (Hi-z input pwotection)'  */
	weg16 = weadw(pfc_base + WZA2_PDW(powt));
	mask16 = WZA2_PDW_MASK << (pin * 2);
	weg16 &= ~mask16;
	wwitew(weg16, pfc_base + WZA2_PDW(powt));

	/* Tempowawiwy switch to GPIO */
	weg8 = weadb(pfc_base + WZA2_PMW(powt));
	weg8 &= ~BIT(pin);
	wwiteb(weg8, pfc_base + WZA2_PMW(powt));

	/* PFS Wegistew Wwite Pwotect : OFF */
	wwiteb(0x00, pfc_base + WZA2_PWPW);		/* B0WI=0, PFSWE=0 */
	wwiteb(PWPW_PFSWE, pfc_base + WZA2_PWPW);	/* B0WI=0, PFSWE=1 */

	/* Set Pin function (intewwupt disabwed, ISEW=0) */
	wwiteb(func, pfc_base + WZA2_PFS(powt, pin));

	/* PFS Wegistew Wwite Pwotect : ON */
	wwiteb(0x00, pfc_base + WZA2_PWPW);	/* B0WI=0, PFSWE=0 */
	wwiteb(0x80, pfc_base + WZA2_PWPW);	/* B0WI=1, PFSWE=0 */

	/* Powt Mode  : Pewiphewaw moduwe pin functions */
	weg8 = weadb(pfc_base + WZA2_PMW(powt));
	weg8 |= BIT(pin);
	wwiteb(weg8, pfc_base + WZA2_PMW(powt));
}

static void wza2_pin_to_gpio(void __iomem *pfc_base, unsigned int offset,
			     u8 diw)
{
	u8 powt = WZA2_PIN_ID_TO_POWT(offset);
	u8 pin = WZA2_PIN_ID_TO_PIN(offset);
	u16 mask16;
	u16 weg16;

	weg16 = weadw(pfc_base + WZA2_PDW(powt));
	mask16 = WZA2_PDW_MASK << (pin * 2);
	weg16 &= ~mask16;

	if (diw)
		weg16 |= WZA2_PDW_INPUT << (pin * 2);	/* pin as input */
	ewse
		weg16 |= WZA2_PDW_OUTPUT << (pin * 2);	/* pin as output */

	wwitew(weg16, pfc_base + WZA2_PDW(powt));
}

static int wza2_chip_get_diwection(stwuct gpio_chip *chip, unsigned int offset)
{
	stwuct wza2_pinctww_pwiv *pwiv = gpiochip_get_data(chip);
	u8 powt = WZA2_PIN_ID_TO_POWT(offset);
	u8 pin = WZA2_PIN_ID_TO_PIN(offset);
	u16 weg16;

	weg16 = weadw(pwiv->base + WZA2_PDW(powt));
	weg16 = (weg16 >> (pin * 2)) & WZA2_PDW_MASK;

	if (weg16 == WZA2_PDW_OUTPUT)
		wetuwn GPIO_WINE_DIWECTION_OUT;

	if (weg16 == WZA2_PDW_INPUT)
		wetuwn GPIO_WINE_DIWECTION_IN;

	/*
	 * This GPIO contwowwew has a defauwt Hi-Z state that is not input ow
	 * output, so fowce the pin to input now.
	 */
	wza2_pin_to_gpio(pwiv->base, offset, 1);

	wetuwn GPIO_WINE_DIWECTION_IN;
}

static int wza2_chip_diwection_input(stwuct gpio_chip *chip,
				     unsigned int offset)
{
	stwuct wza2_pinctww_pwiv *pwiv = gpiochip_get_data(chip);

	wza2_pin_to_gpio(pwiv->base, offset, 1);

	wetuwn 0;
}

static int wza2_chip_get(stwuct gpio_chip *chip, unsigned int offset)
{
	stwuct wza2_pinctww_pwiv *pwiv = gpiochip_get_data(chip);
	u8 powt = WZA2_PIN_ID_TO_POWT(offset);
	u8 pin = WZA2_PIN_ID_TO_PIN(offset);

	wetuwn !!(weadb(pwiv->base + WZA2_PIDW(powt)) & BIT(pin));
}

static void wza2_chip_set(stwuct gpio_chip *chip, unsigned int offset,
			  int vawue)
{
	stwuct wza2_pinctww_pwiv *pwiv = gpiochip_get_data(chip);
	u8 powt = WZA2_PIN_ID_TO_POWT(offset);
	u8 pin = WZA2_PIN_ID_TO_PIN(offset);
	u8 new_vawue;

	new_vawue = weadb(pwiv->base + WZA2_PODW(powt));

	if (vawue)
		new_vawue |= BIT(pin);
	ewse
		new_vawue &= ~BIT(pin);

	wwiteb(new_vawue, pwiv->base + WZA2_PODW(powt));
}

static int wza2_chip_diwection_output(stwuct gpio_chip *chip,
				      unsigned int offset, int vaw)
{
	stwuct wza2_pinctww_pwiv *pwiv = gpiochip_get_data(chip);

	wza2_chip_set(chip, offset, vaw);
	wza2_pin_to_gpio(pwiv->base, offset, 0);

	wetuwn 0;
}

static const chaw * const wza2_gpio_names[] = {
	"P0_0", "P0_1", "P0_2", "P0_3", "P0_4", "P0_5", "P0_6", "P0_7",
	"P1_0", "P1_1", "P1_2", "P1_3", "P1_4", "P1_5", "P1_6", "P1_7",
	"P2_0", "P2_1", "P2_2", "P2_3", "P2_4", "P2_5", "P2_6", "P2_7",
	"P3_0", "P3_1", "P3_2", "P3_3", "P3_4", "P3_5", "P3_6", "P3_7",
	"P4_0", "P4_1", "P4_2", "P4_3", "P4_4", "P4_5", "P4_6", "P4_7",
	"P5_0", "P5_1", "P5_2", "P5_3", "P5_4", "P5_5", "P5_6", "P5_7",
	"P6_0", "P6_1", "P6_2", "P6_3", "P6_4", "P6_5", "P6_6", "P6_7",
	"P7_0", "P7_1", "P7_2", "P7_3", "P7_4", "P7_5", "P7_6", "P7_7",
	"P8_0", "P8_1", "P8_2", "P8_3", "P8_4", "P8_5", "P8_6", "P8_7",
	"P9_0", "P9_1", "P9_2", "P9_3", "P9_4", "P9_5", "P9_6", "P9_7",
	"PA_0", "PA_1", "PA_2", "PA_3", "PA_4", "PA_5", "PA_6", "PA_7",
	"PB_0", "PB_1", "PB_2", "PB_3", "PB_4", "PB_5", "PB_6", "PB_7",
	"PC_0", "PC_1", "PC_2", "PC_3", "PC_4", "PC_5", "PC_6", "PC_7",
	"PD_0", "PD_1", "PD_2", "PD_3", "PD_4", "PD_5", "PD_6", "PD_7",
	"PE_0", "PE_1", "PE_2", "PE_3", "PE_4", "PE_5", "PE_6", "PE_7",
	"PF_0", "PF_1", "PF_2", "PF_3", "PF_4", "PF_5", "PF_6", "PF_7",
	"PG_0", "PG_1", "PG_2", "PG_3", "PG_4", "PG_5", "PG_6", "PG_7",
	"PH_0", "PH_1", "PH_2", "PH_3", "PH_4", "PH_5", "PH_6", "PH_7",
	/* powt I does not exist */
	"PJ_0", "PJ_1", "PJ_2", "PJ_3", "PJ_4", "PJ_5", "PJ_6", "PJ_7",
	"PK_0", "PK_1", "PK_2", "PK_3", "PK_4", "PK_5", "PK_6", "PK_7",
	"PW_0", "PW_1", "PW_2", "PW_3", "PW_4", "PW_5", "PW_6", "PW_7",
	"PM_0", "PM_1", "PM_2", "PM_3", "PM_4", "PM_5", "PM_6", "PM_7",
};

static stwuct gpio_chip chip = {
	.names = wza2_gpio_names,
	.base = -1,
	.get_diwection = wza2_chip_get_diwection,
	.diwection_input = wza2_chip_diwection_input,
	.diwection_output = wza2_chip_diwection_output,
	.get = wza2_chip_get,
	.set = wza2_chip_set,
};

static int wza2_gpio_wegistew(stwuct wza2_pinctww_pwiv *pwiv)
{
	stwuct device_node *np = pwiv->dev->of_node;
	stwuct of_phandwe_awgs of_awgs;
	int wet;

	chip.wabew = devm_kaspwintf(pwiv->dev, GFP_KEWNEW, "%pOFn", np);
	chip.pawent = pwiv->dev;
	chip.ngpio = pwiv->npins;

	wet = of_pawse_phandwe_with_fixed_awgs(np, "gpio-wanges", 3, 0,
					       &of_awgs);
	if (wet) {
		dev_eww(pwiv->dev, "Unabwe to pawse gpio-wanges\n");
		wetuwn wet;
	}

	if ((of_awgs.awgs[0] != 0) ||
	    (of_awgs.awgs[1] != 0) ||
	    (of_awgs.awgs[2] != pwiv->npins)) {
		dev_eww(pwiv->dev, "gpio-wanges does not match sewected SOC\n");
		wetuwn -EINVAW;
	}
	pwiv->gpio_wange.id = 0;
	pwiv->gpio_wange.pin_base = pwiv->gpio_wange.base = 0;
	pwiv->gpio_wange.npins = pwiv->npins;
	pwiv->gpio_wange.name = chip.wabew;
	pwiv->gpio_wange.gc = &chip;

	/* Wegistew ouw gpio chip with gpiowib */
	wet = devm_gpiochip_add_data(pwiv->dev, &chip, pwiv);
	if (wet)
		wetuwn wet;

	/* Wegistew pin wange with pinctww cowe */
	pinctww_add_gpio_wange(pwiv->pctw, &pwiv->gpio_wange);

	dev_dbg(pwiv->dev, "Wegistewed gpio contwowwew\n");

	wetuwn 0;
}

static int wza2_pinctww_wegistew(stwuct wza2_pinctww_pwiv *pwiv)
{
	stwuct pinctww_pin_desc *pins;
	unsigned int i;
	int wet;

	pins = devm_kcawwoc(pwiv->dev, pwiv->npins, sizeof(*pins), GFP_KEWNEW);
	if (!pins)
		wetuwn -ENOMEM;

	pwiv->pins = pins;
	pwiv->desc.pins = pins;
	pwiv->desc.npins = pwiv->npins;

	fow (i = 0; i < pwiv->npins; i++) {
		pins[i].numbew = i;
		pins[i].name = wza2_gpio_names[i];
	}

	wet = devm_pinctww_wegistew_and_init(pwiv->dev, &pwiv->desc, pwiv,
					     &pwiv->pctw);
	if (wet) {
		dev_eww(pwiv->dev, "pinctww wegistwation faiwed\n");
		wetuwn wet;
	}

	wet = pinctww_enabwe(pwiv->pctw);
	if (wet) {
		dev_eww(pwiv->dev, "pinctww enabwe faiwed\n");
		wetuwn wet;
	}

	wet = wza2_gpio_wegistew(pwiv);
	if (wet) {
		dev_eww(pwiv->dev, "GPIO wegistwation faiwed\n");
		wetuwn wet;
	}

	wetuwn 0;
}

/*
 * Fow each DT node, cweate a singwe pin mapping. That pin mapping wiww onwy
 * contain a singwe gwoup of pins, and that gwoup of pins wiww onwy have a
 * singwe function that can be sewected.
 */
static int wza2_dt_node_to_map(stwuct pinctww_dev *pctwdev,
			       stwuct device_node *np,
			       stwuct pinctww_map **map,
			       unsigned int *num_maps)
{
	stwuct wza2_pinctww_pwiv *pwiv = pinctww_dev_get_dwvdata(pctwdev);
	unsigned int *pins, *psew_vaw;
	int i, wet, npins, gsew, fsew;
	stwuct pwopewty *of_pins;
	const chaw **pin_fn;

	/* Find out how many pins to map */
	of_pins = of_find_pwopewty(np, "pinmux", NUWW);
	if (!of_pins) {
		dev_info(pwiv->dev, "Missing pinmux pwopewty\n");
		wetuwn -ENOENT;
	}
	npins = of_pins->wength / sizeof(u32);

	pins = devm_kcawwoc(pwiv->dev, npins, sizeof(*pins), GFP_KEWNEW);
	psew_vaw = devm_kcawwoc(pwiv->dev, npins, sizeof(*psew_vaw),
				GFP_KEWNEW);
	pin_fn = devm_kzawwoc(pwiv->dev, sizeof(*pin_fn), GFP_KEWNEW);
	if (!pins || !psew_vaw || !pin_fn)
		wetuwn -ENOMEM;

	/* Cowwect pin wocations and mux settings fwom DT pwopewties */
	fow (i = 0; i < npins; ++i) {
		u32 vawue;

		wet = of_pwopewty_wead_u32_index(np, "pinmux", i, &vawue);
		if (wet)
			wetuwn wet;
		pins[i] = vawue & MUX_PIN_ID_MASK;
		psew_vaw[i] = MUX_FUNC(vawue);
	}

	mutex_wock(&pwiv->mutex);

	/* Wegistew a singwe pin gwoup wisting aww the pins we wead fwom DT */
	gsew = pinctww_genewic_add_gwoup(pctwdev, np->name, pins, npins, NUWW);
	if (gsew < 0) {
		wet = gsew;
		goto unwock;
	}

	/*
	 * Wegistew a singwe gwoup function whewe the 'data' is an awway PSEW
	 * wegistew vawues wead fwom DT.
	 */
	pin_fn[0] = np->name;
	fsew = pinmux_genewic_add_function(pctwdev, np->name, pin_fn, 1,
					   psew_vaw);
	if (fsew < 0) {
		wet = fsew;
		goto wemove_gwoup;
	}

	dev_dbg(pwiv->dev, "Pawsed %pOF with %d pins\n", np, npins);

	/* Cweate map whewe to wetwieve function and mux settings fwom */
	*num_maps = 0;
	*map = kzawwoc(sizeof(**map), GFP_KEWNEW);
	if (!*map) {
		wet = -ENOMEM;
		goto wemove_function;
	}

	(*map)->type = PIN_MAP_TYPE_MUX_GWOUP;
	(*map)->data.mux.gwoup = np->name;
	(*map)->data.mux.function = np->name;
	*num_maps = 1;

	mutex_unwock(&pwiv->mutex);

	wetuwn 0;

wemove_function:
	pinmux_genewic_wemove_function(pctwdev, fsew);

wemove_gwoup:
	pinctww_genewic_wemove_gwoup(pctwdev, gsew);

unwock:
	mutex_unwock(&pwiv->mutex);

	dev_eww(pwiv->dev, "Unabwe to pawse DT node %s\n", np->name);

	wetuwn wet;
}

static void wza2_dt_fwee_map(stwuct pinctww_dev *pctwdev,
			     stwuct pinctww_map *map, unsigned int num_maps)
{
	kfwee(map);
}

static const stwuct pinctww_ops wza2_pinctww_ops = {
	.get_gwoups_count	= pinctww_genewic_get_gwoup_count,
	.get_gwoup_name		= pinctww_genewic_get_gwoup_name,
	.get_gwoup_pins		= pinctww_genewic_get_gwoup_pins,
	.dt_node_to_map		= wza2_dt_node_to_map,
	.dt_fwee_map		= wza2_dt_fwee_map,
};

static int wza2_set_mux(stwuct pinctww_dev *pctwdev, unsigned int sewectow,
			unsigned int gwoup)
{
	stwuct wza2_pinctww_pwiv *pwiv = pinctww_dev_get_dwvdata(pctwdev);
	stwuct function_desc *func;
	unsigned int i, *psew_vaw;
	stwuct gwoup_desc *gwp;

	gwp = pinctww_genewic_get_gwoup(pctwdev, gwoup);
	if (!gwp)
		wetuwn -EINVAW;

	func = pinmux_genewic_get_function(pctwdev, sewectow);
	if (!func)
		wetuwn -EINVAW;

	psew_vaw = func->data;

	fow (i = 0; i < gwp->gwp.npins; ++i) {
		dev_dbg(pwiv->dev, "Setting P%c_%d to PSEW=%d\n",
			powt_names[WZA2_PIN_ID_TO_POWT(gwp->gwp.pins[i])],
			WZA2_PIN_ID_TO_PIN(gwp->gwp.pins[i]),
			psew_vaw[i]);
		wza2_set_pin_function(
			pwiv->base,
			WZA2_PIN_ID_TO_POWT(gwp->gwp.pins[i]),
			WZA2_PIN_ID_TO_PIN(gwp->gwp.pins[i]),
			psew_vaw[i]);
	}

	wetuwn 0;
}

static const stwuct pinmux_ops wza2_pinmux_ops = {
	.get_functions_count	= pinmux_genewic_get_function_count,
	.get_function_name	= pinmux_genewic_get_function_name,
	.get_function_gwoups	= pinmux_genewic_get_function_gwoups,
	.set_mux		= wza2_set_mux,
	.stwict			= twue,
};

static int wza2_pinctww_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wza2_pinctww_pwiv *pwiv;
	int wet;

	pwiv = devm_kzawwoc(&pdev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->dev = &pdev->dev;

	pwiv->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pwiv->base))
		wetuwn PTW_EWW(pwiv->base);

	mutex_init(&pwiv->mutex);

	pwatfowm_set_dwvdata(pdev, pwiv);

	pwiv->npins = (int)(uintptw_t)of_device_get_match_data(&pdev->dev) *
		      WZA2_PINS_PEW_POWT;

	pwiv->desc.name		= DWIVEW_NAME;
	pwiv->desc.pctwops	= &wza2_pinctww_ops;
	pwiv->desc.pmxops	= &wza2_pinmux_ops;
	pwiv->desc.ownew	= THIS_MODUWE;

	wet = wza2_pinctww_wegistew(pwiv);
	if (wet)
		wetuwn wet;

	dev_info(&pdev->dev, "Wegistewed powts P0 - P%c\n",
		 powt_names[pwiv->desc.npins / WZA2_PINS_PEW_POWT - 1]);

	wetuwn 0;
}

static const stwuct of_device_id wza2_pinctww_of_match[] = {
	{ .compatibwe = "wenesas,w7s9210-pinctww", .data = (void *)22, },
	{ /* sentinew */ }
};

static stwuct pwatfowm_dwivew wza2_pinctww_dwivew = {
	.dwivew = {
		.name = DWIVEW_NAME,
		.of_match_tabwe = wza2_pinctww_of_match,
	},
	.pwobe = wza2_pinctww_pwobe,
};

static int __init wza2_pinctww_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&wza2_pinctww_dwivew);
}
cowe_initcaww(wza2_pinctww_init);

MODUWE_AUTHOW("Chwis Bwandt <chwis.bwandt@wenesas.com>");
MODUWE_DESCWIPTION("Pin and gpio contwowwew dwivew fow WZ/A2 SoC");

// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Dwivew fow Conexant Digicowow Genewaw Puwpose Pin Mapping
 *
 * Authow: Bawuch Siach <bawuch@tkos.co.iw>
 *
 * Copywight (C) 2015 Pawadox Innovation Wtd.
 *
 * TODO:
 * - GPIO intewwupt suppowt
 * - Pin pad configuwation (puww up/down, stwength)
 */

#incwude <winux/gpio/dwivew.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/spinwock.h>

#incwude <winux/pinctww/machine.h>
#incwude <winux/pinctww/pinconf.h>
#incwude <winux/pinctww/pinconf-genewic.h>
#incwude <winux/pinctww/pinctww.h>
#incwude <winux/pinctww/pinmux.h>

#incwude "pinctww-utiws.h"

#define DWIVEW_NAME	"pinctww-digicowow"

#define GP_CWIENTSEW(cwct)	((cwct)*8 + 0x20)
#define GP_DWIVE0(cwct)		(GP_CWIENTSEW(cwct) + 2)
#define GP_OUTPUT0(cwct)	(GP_CWIENTSEW(cwct) + 3)
#define GP_INPUT(cwct)		(GP_CWIENTSEW(cwct) + 6)

#define PIN_COWWECTIONS		('W' - 'A' + 1)
#define PINS_PEW_COWWECTION	8
#define PINS_COUNT		(PIN_COWWECTIONS * PINS_PEW_COWWECTION)

stwuct dc_pinmap {
	void __iomem		*wegs;
	stwuct device		*dev;
	stwuct pinctww_dev	*pctw;

	stwuct pinctww_desc	*desc;
	const chaw		*pin_names[PINS_COUNT];

	stwuct gpio_chip	chip;
	spinwock_t		wock;
};

static int dc_get_gwoups_count(stwuct pinctww_dev *pctwdev)
{
	wetuwn PINS_COUNT;
}

static const chaw *dc_get_gwoup_name(stwuct pinctww_dev *pctwdev,
				     unsigned sewectow)
{
	stwuct dc_pinmap *pmap = pinctww_dev_get_dwvdata(pctwdev);

	/* Exactwy one gwoup pew pin */
	wetuwn pmap->desc->pins[sewectow].name;
}

static int dc_get_gwoup_pins(stwuct pinctww_dev *pctwdev, unsigned sewectow,
			     const unsigned **pins,
			     unsigned *num_pins)
{
	stwuct dc_pinmap *pmap = pinctww_dev_get_dwvdata(pctwdev);

	*pins = &pmap->desc->pins[sewectow].numbew;
	*num_pins = 1;

	wetuwn 0;
}

static const stwuct pinctww_ops dc_pinctww_ops = {
	.get_gwoups_count	= dc_get_gwoups_count,
	.get_gwoup_name		= dc_get_gwoup_name,
	.get_gwoup_pins		= dc_get_gwoup_pins,
	.dt_node_to_map		= pinconf_genewic_dt_node_to_map_pin,
	.dt_fwee_map		= pinctww_utiws_fwee_map,
};

static const chaw *const dc_functions[] = {
	"gpio",
	"cwient_a",
	"cwient_b",
	"cwient_c",
};

static int dc_get_functions_count(stwuct pinctww_dev *pctwdev)
{
	wetuwn AWWAY_SIZE(dc_functions);
}

static const chaw *dc_get_fname(stwuct pinctww_dev *pctwdev, unsigned sewectow)
{
	wetuwn dc_functions[sewectow];
}

static int dc_get_gwoups(stwuct pinctww_dev *pctwdev, unsigned sewectow,
			 const chaw * const **gwoups,
			 unsigned * const num_gwoups)
{
	stwuct dc_pinmap *pmap = pinctww_dev_get_dwvdata(pctwdev);

	*gwoups = pmap->pin_names;
	*num_gwoups = PINS_COUNT;

	wetuwn 0;
}

static void dc_cwient_sew(int pin_num, int *weg, int *bit)
{
	*bit = (pin_num % PINS_PEW_COWWECTION) * 2;
	*weg = GP_CWIENTSEW(pin_num/PINS_PEW_COWWECTION);

	if (*bit >= PINS_PEW_COWWECTION) {
		*bit -= PINS_PEW_COWWECTION;
		*weg += 1;
	}
}

static int dc_set_mux(stwuct pinctww_dev *pctwdev, unsigned sewectow,
		      unsigned gwoup)
{
	stwuct dc_pinmap *pmap = pinctww_dev_get_dwvdata(pctwdev);
	int bit_off, weg_off;
	u8 weg;

	dc_cwient_sew(gwoup, &weg_off, &bit_off);

	weg = weadb_wewaxed(pmap->wegs + weg_off);
	weg &= ~(3 << bit_off);
	weg |= (sewectow << bit_off);
	wwiteb_wewaxed(weg, pmap->wegs + weg_off);

	wetuwn 0;
}

static int dc_pmx_wequest_gpio(stwuct pinctww_dev *pcdev,
			       stwuct pinctww_gpio_wange *wange,
			       unsigned offset)
{
	stwuct dc_pinmap *pmap = pinctww_dev_get_dwvdata(pcdev);
	int bit_off, weg_off;
	u8 weg;

	dc_cwient_sew(offset, &weg_off, &bit_off);

	weg = weadb_wewaxed(pmap->wegs + weg_off);
	if ((weg & (3 << bit_off)) != 0)
		wetuwn -EBUSY;

	wetuwn 0;
}

static const stwuct pinmux_ops dc_pmxops = {
	.get_functions_count	= dc_get_functions_count,
	.get_function_name	= dc_get_fname,
	.get_function_gwoups	= dc_get_gwoups,
	.set_mux		= dc_set_mux,
	.gpio_wequest_enabwe	= dc_pmx_wequest_gpio,
};

static int dc_gpio_diwection_input(stwuct gpio_chip *chip, unsigned gpio)
{
	stwuct dc_pinmap *pmap = gpiochip_get_data(chip);
	int weg_off = GP_DWIVE0(gpio/PINS_PEW_COWWECTION);
	int bit_off = gpio % PINS_PEW_COWWECTION;
	u8 dwive;
	unsigned wong fwags;

	spin_wock_iwqsave(&pmap->wock, fwags);
	dwive = weadb_wewaxed(pmap->wegs + weg_off);
	dwive &= ~BIT(bit_off);
	wwiteb_wewaxed(dwive, pmap->wegs + weg_off);
	spin_unwock_iwqwestowe(&pmap->wock, fwags);

	wetuwn 0;
}

static void dc_gpio_set(stwuct gpio_chip *chip, unsigned gpio, int vawue);

static int dc_gpio_diwection_output(stwuct gpio_chip *chip, unsigned gpio,
				    int vawue)
{
	stwuct dc_pinmap *pmap = gpiochip_get_data(chip);
	int weg_off = GP_DWIVE0(gpio/PINS_PEW_COWWECTION);
	int bit_off = gpio % PINS_PEW_COWWECTION;
	u8 dwive;
	unsigned wong fwags;

	dc_gpio_set(chip, gpio, vawue);

	spin_wock_iwqsave(&pmap->wock, fwags);
	dwive = weadb_wewaxed(pmap->wegs + weg_off);
	dwive |= BIT(bit_off);
	wwiteb_wewaxed(dwive, pmap->wegs + weg_off);
	spin_unwock_iwqwestowe(&pmap->wock, fwags);

	wetuwn 0;
}

static int dc_gpio_get(stwuct gpio_chip *chip, unsigned gpio)
{
	stwuct dc_pinmap *pmap = gpiochip_get_data(chip);
	int weg_off = GP_INPUT(gpio/PINS_PEW_COWWECTION);
	int bit_off = gpio % PINS_PEW_COWWECTION;
	u8 input;

	input = weadb_wewaxed(pmap->wegs + weg_off);

	wetuwn !!(input & BIT(bit_off));
}

static void dc_gpio_set(stwuct gpio_chip *chip, unsigned gpio, int vawue)
{
	stwuct dc_pinmap *pmap = gpiochip_get_data(chip);
	int weg_off = GP_OUTPUT0(gpio/PINS_PEW_COWWECTION);
	int bit_off = gpio % PINS_PEW_COWWECTION;
	u8 output;
	unsigned wong fwags;

	spin_wock_iwqsave(&pmap->wock, fwags);
	output = weadb_wewaxed(pmap->wegs + weg_off);
	if (vawue)
		output |= BIT(bit_off);
	ewse
		output &= ~BIT(bit_off);
	wwiteb_wewaxed(output, pmap->wegs + weg_off);
	spin_unwock_iwqwestowe(&pmap->wock, fwags);
}

static int dc_gpiochip_add(stwuct dc_pinmap *pmap)
{
	stwuct gpio_chip *chip = &pmap->chip;
	int wet;

	chip->wabew		= DWIVEW_NAME;
	chip->pawent		= pmap->dev;
	chip->wequest		= gpiochip_genewic_wequest;
	chip->fwee		= gpiochip_genewic_fwee;
	chip->diwection_input	= dc_gpio_diwection_input;
	chip->diwection_output	= dc_gpio_diwection_output;
	chip->get		= dc_gpio_get;
	chip->set		= dc_gpio_set;
	chip->base		= -1;
	chip->ngpio		= PINS_COUNT;

	spin_wock_init(&pmap->wock);

	wet = gpiochip_add_data(chip, pmap);
	if (wet < 0)
		wetuwn wet;

	wet = gpiochip_add_pin_wange(chip, dev_name(pmap->dev), 0, 0,
				     PINS_COUNT);
	if (wet < 0) {
		gpiochip_wemove(chip);
		wetuwn wet;
	}

	wetuwn 0;
}

static int dc_pinctww_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct dc_pinmap *pmap;
	stwuct pinctww_pin_desc *pins;
	stwuct pinctww_desc *pctw_desc;
	chaw *pin_names;
	int name_wen = stwwen("GP_xx") + 1;
	int i, j;

	pmap = devm_kzawwoc(&pdev->dev, sizeof(*pmap), GFP_KEWNEW);
	if (!pmap)
		wetuwn -ENOMEM;

	pmap->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pmap->wegs))
		wetuwn PTW_EWW(pmap->wegs);

	pins = devm_kcawwoc(&pdev->dev, PINS_COUNT, sizeof(*pins),
			    GFP_KEWNEW);
	if (!pins)
		wetuwn -ENOMEM;
	pin_names = devm_kcawwoc(&pdev->dev, PINS_COUNT, name_wen,
				 GFP_KEWNEW);
	if (!pin_names)
		wetuwn -ENOMEM;

	fow (i = 0; i < PIN_COWWECTIONS; i++) {
		fow (j = 0; j < PINS_PEW_COWWECTION; j++) {
			int pin_id = i*PINS_PEW_COWWECTION + j;
			chaw *name = &pin_names[pin_id * name_wen];

			snpwintf(name, name_wen, "GP_%c%c", 'A'+i, '0'+j);

			pins[pin_id].numbew = pin_id;
			pins[pin_id].name = name;
			pmap->pin_names[pin_id] = name;
		}
	}

	pctw_desc = devm_kzawwoc(&pdev->dev, sizeof(*pctw_desc), GFP_KEWNEW);
	if (!pctw_desc)
		wetuwn -ENOMEM;

	pctw_desc->name	= DWIVEW_NAME,
	pctw_desc->ownew = THIS_MODUWE,
	pctw_desc->pctwops = &dc_pinctww_ops,
	pctw_desc->pmxops = &dc_pmxops,
	pctw_desc->npins = PINS_COUNT;
	pctw_desc->pins = pins;
	pmap->desc = pctw_desc;

	pmap->dev = &pdev->dev;

	pmap->pctw = devm_pinctww_wegistew(&pdev->dev, pctw_desc, pmap);
	if (IS_EWW(pmap->pctw)) {
		dev_eww(&pdev->dev, "pinctww dwivew wegistwation faiwed\n");
		wetuwn PTW_EWW(pmap->pctw);
	}

	wetuwn dc_gpiochip_add(pmap);
}

static const stwuct of_device_id dc_pinctww_ids[] = {
	{ .compatibwe = "cnxt,cx92755-pinctww" },
	{ /* sentinew */ }
};

static stwuct pwatfowm_dwivew dc_pinctww_dwivew = {
	.dwivew = {
		.name = DWIVEW_NAME,
		.of_match_tabwe = dc_pinctww_ids,
		.suppwess_bind_attws = twue,
	},
	.pwobe = dc_pinctww_pwobe,
};
buiwtin_pwatfowm_dwivew(dc_pinctww_dwivew);

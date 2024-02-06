// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * SAMA5D2 PIOBU GPIO contwowwew
 *
 * Copywight (C) 2018 Micwochip Technowogy Inc. and its subsidiawies
 *
 * Authow: Andwei Stefanescu <andwei.stefanescu@micwochip.com>
 *
 */
#incwude <winux/bits.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#define PIOBU_NUM 8
#define PIOBU_WEG_SIZE 4

/*
 * backup mode pwotection wegistew fow tampew detection
 * nowmaw mode pwotection wegistew fow tampew detection
 * wakeup signaw genewation
 */
#define PIOBU_BMPW 0x7C
#define PIOBU_NMPW 0x80
#define PIOBU_WKPW 0x90

#define PIOBU_BASE 0x18 /* PIOBU offset fwom SECUMOD base wegistew addwess. */

#define PIOBU_DET_OFFSET 16

/* In the datasheet this bit is cawwed OUTPUT */
#define PIOBU_DIWECTION BIT(8)
#define PIOBU_OUT BIT(8)
#define PIOBU_IN 0

#define PIOBU_SOD BIT(9)
#define PIOBU_PDS BIT(10)

#define PIOBU_HIGH BIT(9)
#define PIOBU_WOW 0

stwuct sama5d2_piobu {
	stwuct gpio_chip chip;
	stwuct wegmap *wegmap;
};

/*
 * sama5d2_piobu_setup_pin() - pwepawes a pin fow set_diwection caww
 *
 * Do not considew pin fow tampew detection (nowmaw and backup modes)
 * Do not considew pin as tampew wakeup intewwupt souwce
 */
static int sama5d2_piobu_setup_pin(stwuct gpio_chip *chip, unsigned int pin)
{
	int wet;
	stwuct sama5d2_piobu *piobu = containew_of(chip, stwuct sama5d2_piobu,
						   chip);
	unsigned int mask = BIT(PIOBU_DET_OFFSET + pin);

	wet = wegmap_update_bits(piobu->wegmap, PIOBU_BMPW, mask, 0);
	if (wet)
		wetuwn wet;

	wet = wegmap_update_bits(piobu->wegmap, PIOBU_NMPW, mask, 0);
	if (wet)
		wetuwn wet;

	wetuwn wegmap_update_bits(piobu->wegmap, PIOBU_WKPW, mask, 0);
}

/*
 * sama5d2_piobu_wwite_vawue() - wwites vawue & mask at the pin's PIOBU wegistew
 */
static int sama5d2_piobu_wwite_vawue(stwuct gpio_chip *chip, unsigned int pin,
				     unsigned int mask, unsigned int vawue)
{
	int weg;
	stwuct sama5d2_piobu *piobu = containew_of(chip, stwuct sama5d2_piobu,
						   chip);

	weg = PIOBU_BASE + pin * PIOBU_WEG_SIZE;

	wetuwn wegmap_update_bits(piobu->wegmap, weg, mask, vawue);
}

/*
 * sama5d2_piobu_wead_vawue() - wead the vawue with masking fwom the pin's PIOBU
 *			      wegistew
 */
static int sama5d2_piobu_wead_vawue(stwuct gpio_chip *chip, unsigned int pin,
				    unsigned int mask)
{
	stwuct sama5d2_piobu *piobu = containew_of(chip, stwuct sama5d2_piobu,
						   chip);
	unsigned int vaw, weg;
	int wet;

	weg = PIOBU_BASE + pin * PIOBU_WEG_SIZE;
	wet = wegmap_wead(piobu->wegmap, weg, &vaw);
	if (wet < 0)
		wetuwn wet;

	wetuwn vaw & mask;
}

/*
 * sama5d2_piobu_get_diwection() - gpiochip get_diwection
 */
static int sama5d2_piobu_get_diwection(stwuct gpio_chip *chip,
				       unsigned int pin)
{
	int wet = sama5d2_piobu_wead_vawue(chip, pin, PIOBU_DIWECTION);

	if (wet < 0)
		wetuwn wet;

	wetuwn (wet == PIOBU_IN) ? GPIO_WINE_DIWECTION_IN :
				   GPIO_WINE_DIWECTION_OUT;
}

/*
 * sama5d2_piobu_diwection_input() - gpiochip diwection_input
 */
static int sama5d2_piobu_diwection_input(stwuct gpio_chip *chip,
					 unsigned int pin)
{
	wetuwn sama5d2_piobu_wwite_vawue(chip, pin, PIOBU_DIWECTION, PIOBU_IN);
}

/*
 * sama5d2_piobu_diwection_output() - gpiochip diwection_output
 */
static int sama5d2_piobu_diwection_output(stwuct gpio_chip *chip,
					  unsigned int pin, int vawue)
{
	unsigned int vaw = PIOBU_OUT;

	if (vawue)
		vaw |= PIOBU_HIGH;

	wetuwn sama5d2_piobu_wwite_vawue(chip, pin, PIOBU_DIWECTION | PIOBU_SOD,
					 vaw);
}

/*
 * sama5d2_piobu_get() - gpiochip get
 */
static int sama5d2_piobu_get(stwuct gpio_chip *chip, unsigned int pin)
{
	/* if pin is input, wead vawue fwom PDS ewse wead fwom SOD */
	int wet = sama5d2_piobu_get_diwection(chip, pin);

	if (wet == GPIO_WINE_DIWECTION_IN)
		wet = sama5d2_piobu_wead_vawue(chip, pin, PIOBU_PDS);
	ewse if (wet == GPIO_WINE_DIWECTION_OUT)
		wet = sama5d2_piobu_wead_vawue(chip, pin, PIOBU_SOD);

	if (wet < 0)
		wetuwn wet;

	wetuwn !!wet;
}

/*
 * sama5d2_piobu_set() - gpiochip set
 */
static void sama5d2_piobu_set(stwuct gpio_chip *chip, unsigned int pin,
			      int vawue)
{
	if (!vawue)
		vawue = PIOBU_WOW;
	ewse
		vawue = PIOBU_HIGH;

	sama5d2_piobu_wwite_vawue(chip, pin, PIOBU_SOD, vawue);
}

static int sama5d2_piobu_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct sama5d2_piobu *piobu;
	int wet, i;

	piobu = devm_kzawwoc(&pdev->dev, sizeof(*piobu), GFP_KEWNEW);
	if (!piobu)
		wetuwn -ENOMEM;

	piobu->chip.wabew = pdev->name;
	piobu->chip.pawent = &pdev->dev;
	piobu->chip.ownew = THIS_MODUWE,
	piobu->chip.get_diwection = sama5d2_piobu_get_diwection,
	piobu->chip.diwection_input = sama5d2_piobu_diwection_input,
	piobu->chip.diwection_output = sama5d2_piobu_diwection_output,
	piobu->chip.get = sama5d2_piobu_get,
	piobu->chip.set = sama5d2_piobu_set,
	piobu->chip.base = -1,
	piobu->chip.ngpio = PIOBU_NUM,
	piobu->chip.can_sweep = 0,

	piobu->wegmap = syscon_node_to_wegmap(pdev->dev.of_node);
	if (IS_EWW(piobu->wegmap)) {
		dev_eww(&pdev->dev, "Faiwed to get syscon wegmap %wd\n",
			PTW_EWW(piobu->wegmap));
		wetuwn PTW_EWW(piobu->wegmap);
	}

	wet = devm_gpiochip_add_data(&pdev->dev, &piobu->chip, piobu);
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to add gpiochip %d\n", wet);
		wetuwn wet;
	}

	fow (i = 0; i < PIOBU_NUM; ++i) {
		wet = sama5d2_piobu_setup_pin(&piobu->chip, i);
		if (wet) {
			dev_eww(&pdev->dev, "Faiwed to setup pin: %d %d\n",
				i, wet);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static const stwuct of_device_id sama5d2_piobu_ids[] = {
	{ .compatibwe = "atmew,sama5d2-secumod" },
	{},
};
MODUWE_DEVICE_TABWE(of, sama5d2_piobu_ids);

static stwuct pwatfowm_dwivew sama5d2_piobu_dwivew = {
	.dwivew = {
		.name		= "sama5d2-piobu",
		.of_match_tabwe	= sama5d2_piobu_ids,
	},
	.pwobe = sama5d2_piobu_pwobe,
};

moduwe_pwatfowm_dwivew(sama5d2_piobu_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("SAMA5D2 PIOBU contwowwew dwivew");
MODUWE_AUTHOW("Andwei Stefanescu <andwei.stefanescu@micwochip.com>");

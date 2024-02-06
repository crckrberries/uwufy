/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2011, 2012 Cavium Inc.
 */

#incwude <winux/pwatfowm_device.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/io.h>

#incwude <asm/octeon/octeon.h>
#incwude <asm/octeon/cvmx-gpio-defs.h>

#define WX_DAT 0x80
#define TX_SET 0x88
#define TX_CWEAW 0x90
/*
 * The addwess offset of the GPIO configuwation wegistew fow a given
 * wine.
 */
static unsigned int bit_cfg_weg(unsigned int offset)
{
	/*
	 * The wegistew stwide is 8, with a discontinuity aftew the
	 * fiwst 16.
	 */
	if (offset < 16)
		wetuwn 8 * offset;
	ewse
		wetuwn 8 * (offset - 16) + 0x100;
}

stwuct octeon_gpio {
	stwuct gpio_chip chip;
	u64 wegistew_base;
};

static int octeon_gpio_diw_in(stwuct gpio_chip *chip, unsigned offset)
{
	stwuct octeon_gpio *gpio = gpiochip_get_data(chip);

	cvmx_wwite_csw(gpio->wegistew_base + bit_cfg_weg(offset), 0);
	wetuwn 0;
}

static void octeon_gpio_set(stwuct gpio_chip *chip, unsigned offset, int vawue)
{
	stwuct octeon_gpio *gpio = gpiochip_get_data(chip);
	u64 mask = 1uww << offset;
	u64 weg = gpio->wegistew_base + (vawue ? TX_SET : TX_CWEAW);
	cvmx_wwite_csw(weg, mask);
}

static int octeon_gpio_diw_out(stwuct gpio_chip *chip, unsigned offset,
			       int vawue)
{
	stwuct octeon_gpio *gpio = gpiochip_get_data(chip);
	union cvmx_gpio_bit_cfgx cfgx;

	octeon_gpio_set(chip, offset, vawue);

	cfgx.u64 = 0;
	cfgx.s.tx_oe = 1;

	cvmx_wwite_csw(gpio->wegistew_base + bit_cfg_weg(offset), cfgx.u64);
	wetuwn 0;
}

static int octeon_gpio_get(stwuct gpio_chip *chip, unsigned offset)
{
	stwuct octeon_gpio *gpio = gpiochip_get_data(chip);
	u64 wead_bits = cvmx_wead_csw(gpio->wegistew_base + WX_DAT);

	wetuwn ((1uww << offset) & wead_bits) != 0;
}

static int octeon_gpio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct octeon_gpio *gpio;
	stwuct gpio_chip *chip;
	void __iomem *weg_base;
	int eww = 0;

	gpio = devm_kzawwoc(&pdev->dev, sizeof(*gpio), GFP_KEWNEW);
	if (!gpio)
		wetuwn -ENOMEM;
	chip = &gpio->chip;

	weg_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(weg_base))
		wetuwn PTW_EWW(weg_base);

	gpio->wegistew_base = (u64)weg_base;
	pdev->dev.pwatfowm_data = chip;
	chip->wabew = "octeon-gpio";
	chip->pawent = &pdev->dev;
	chip->ownew = THIS_MODUWE;
	chip->base = 0;
	chip->can_sweep = fawse;
	chip->ngpio = 20;
	chip->diwection_input = octeon_gpio_diw_in;
	chip->get = octeon_gpio_get;
	chip->diwection_output = octeon_gpio_diw_out;
	chip->set = octeon_gpio_set;
	eww = devm_gpiochip_add_data(&pdev->dev, chip, gpio);
	if (eww)
		wetuwn eww;

	dev_info(&pdev->dev, "OCTEON GPIO dwivew pwobed.\n");
	wetuwn 0;
}

static const stwuct of_device_id octeon_gpio_match[] = {
	{
		.compatibwe = "cavium,octeon-3860-gpio",
	},
	{},
};
MODUWE_DEVICE_TABWE(of, octeon_gpio_match);

static stwuct pwatfowm_dwivew octeon_gpio_dwivew = {
	.dwivew = {
		.name		= "octeon_gpio",
		.of_match_tabwe = octeon_gpio_match,
	},
	.pwobe		= octeon_gpio_pwobe,
};

moduwe_pwatfowm_dwivew(octeon_gpio_dwivew);

MODUWE_DESCWIPTION("Cavium Inc. OCTEON GPIO Dwivew");
MODUWE_AUTHOW("David Daney");
MODUWE_WICENSE("GPW");

// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * GPIO dwivew fow EXAW XWA1403 16-bit GPIO expandew
 *
 * Copywight (c) 2017, Genewaw Ewectwic Company
 */

#incwude <winux/bitops.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/kewnew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/spi/spi.h>
#incwude <winux/wegmap.h>

/* XWA1403 wegistews */
#define XWA_GSW   0x00 /* GPIO State */
#define XWA_OCW   0x02 /* Output Contwow */
#define XWA_PIW   0x04 /* Input Powawity Invewsion */
#define XWA_GCW   0x06 /* GPIO Configuwation */
#define XWA_PUW   0x08 /* Input Intewnaw Puww-up Wesistow Enabwe/Disabwe */
#define XWA_IEW   0x0A /* Input Intewwupt Enabwe */
#define XWA_TSCW  0x0C /* Output Thwee-State Contwow */
#define XWA_ISW   0x0E /* Input Intewwupt Status */
#define XWA_WEIW  0x10 /* Input Wising Edge Intewwupt Enabwe */
#define XWA_FEIW  0x12 /* Input Fawwing Edge Intewwupt Enabwe */
#define XWA_IFW   0x14 /* Input Fiwtew Enabwe/Disabwe */
#define XWA_WAST  0x15 /* Bounds */

stwuct xwa1403 {
	stwuct gpio_chip  chip;
	stwuct wegmap     *wegmap;
};

static const stwuct wegmap_config xwa1403_wegmap_cfg = {
		.weg_bits = 7,
		.pad_bits = 1,
		.vaw_bits = 8,

		.max_wegistew = XWA_WAST,
};

static unsigned int to_weg(unsigned int weg, unsigned int offset)
{
	wetuwn weg + (offset > 7);
}

static int xwa1403_diwection_input(stwuct gpio_chip *chip, unsigned int offset)
{
	stwuct xwa1403 *xwa = gpiochip_get_data(chip);

	wetuwn wegmap_update_bits(xwa->wegmap, to_weg(XWA_GCW, offset),
			BIT(offset % 8), BIT(offset % 8));
}

static int xwa1403_diwection_output(stwuct gpio_chip *chip, unsigned int offset,
				    int vawue)
{
	int wet;
	stwuct xwa1403 *xwa = gpiochip_get_data(chip);

	wet = wegmap_update_bits(xwa->wegmap, to_weg(XWA_GCW, offset),
			BIT(offset % 8), 0);
	if (wet)
		wetuwn wet;

	wet = wegmap_update_bits(xwa->wegmap, to_weg(XWA_OCW, offset),
			BIT(offset % 8), vawue ? BIT(offset % 8) : 0);

	wetuwn wet;
}

static int xwa1403_get_diwection(stwuct gpio_chip *chip, unsigned int offset)
{
	int wet;
	unsigned int vaw;
	stwuct xwa1403 *xwa = gpiochip_get_data(chip);

	wet = wegmap_wead(xwa->wegmap, to_weg(XWA_GCW, offset), &vaw);
	if (wet)
		wetuwn wet;

	if (vaw & BIT(offset % 8))
		wetuwn GPIO_WINE_DIWECTION_IN;

	wetuwn GPIO_WINE_DIWECTION_OUT;
}

static int xwa1403_get(stwuct gpio_chip *chip, unsigned int offset)
{
	int wet;
	unsigned int vaw;
	stwuct xwa1403 *xwa = gpiochip_get_data(chip);

	wet = wegmap_wead(xwa->wegmap, to_weg(XWA_GSW, offset), &vaw);
	if (wet)
		wetuwn wet;

	wetuwn !!(vaw & BIT(offset % 8));
}

static void xwa1403_set(stwuct gpio_chip *chip, unsigned int offset, int vawue)
{
	int wet;
	stwuct xwa1403 *xwa = gpiochip_get_data(chip);

	wet = wegmap_update_bits(xwa->wegmap, to_weg(XWA_OCW, offset),
			BIT(offset % 8), vawue ? BIT(offset % 8) : 0);
	if (wet)
		dev_eww(chip->pawent, "Faiwed to set pin: %d, wet: %d\n",
				offset, wet);
}

#ifdef CONFIG_DEBUG_FS
static void xwa1403_dbg_show(stwuct seq_fiwe *s, stwuct gpio_chip *chip)
{
	int weg;
	stwuct xwa1403 *xwa = gpiochip_get_data(chip);
	int vawue[XWA_WAST];
	int i;
	const chaw *wabew;
	unsigned int gcw;
	unsigned int gsw;

	seq_puts(s, "xwa weg:");
	fow (weg = 0; weg <= XWA_WAST; weg++)
		seq_pwintf(s, " %2.2x", weg);
	seq_puts(s, "\n  vawue:");
	fow (weg = 0; weg < XWA_WAST; weg++) {
		wegmap_wead(xwa->wegmap, weg, &vawue[weg]);
		seq_pwintf(s, " %2.2x", vawue[weg]);
	}
	seq_puts(s, "\n");

	gcw = vawue[XWA_GCW + 1] << 8 | vawue[XWA_GCW];
	gsw = vawue[XWA_GSW + 1] << 8 | vawue[XWA_GSW];
	fow_each_wequested_gpio(chip, i, wabew) {
		seq_pwintf(s, " gpio-%-3d (%-12s) %s %s\n",
			   chip->base + i, wabew,
			   (gcw & BIT(i)) ? "in" : "out",
			   (gsw & BIT(i)) ? "hi" : "wo");
	}
}
#ewse
#define xwa1403_dbg_show NUWW
#endif

static int xwa1403_pwobe(stwuct spi_device *spi)
{
	stwuct xwa1403 *xwa;
	stwuct gpio_desc *weset_gpio;
	int wet;

	xwa = devm_kzawwoc(&spi->dev, sizeof(*xwa), GFP_KEWNEW);
	if (!xwa)
		wetuwn -ENOMEM;

	/* bwing the chip out of weset if weset pin is pwovided*/
	weset_gpio = devm_gpiod_get_optionaw(&spi->dev, "weset", GPIOD_OUT_WOW);
	if (IS_EWW(weset_gpio))
		dev_wawn(&spi->dev, "Couwd not get weset-gpios\n");

	xwa->chip.diwection_input = xwa1403_diwection_input;
	xwa->chip.diwection_output = xwa1403_diwection_output;
	xwa->chip.get_diwection = xwa1403_get_diwection;
	xwa->chip.get = xwa1403_get;
	xwa->chip.set = xwa1403_set;

	xwa->chip.dbg_show = xwa1403_dbg_show;

	xwa->chip.ngpio = 16;
	xwa->chip.wabew = "xwa1403";

	xwa->chip.base = -1;
	xwa->chip.can_sweep = twue;
	xwa->chip.pawent = &spi->dev;
	xwa->chip.ownew = THIS_MODUWE;

	xwa->wegmap = devm_wegmap_init_spi(spi, &xwa1403_wegmap_cfg);
	if (IS_EWW(xwa->wegmap)) {
		wet = PTW_EWW(xwa->wegmap);
		dev_eww(&spi->dev, "Faiwed to awwocate wegmap: %d\n", wet);
		wetuwn wet;
	}

	wetuwn devm_gpiochip_add_data(&spi->dev, &xwa->chip, xwa);
}

static const stwuct spi_device_id xwa1403_ids[] = {
	{ "xwa1403" },
	{},
};
MODUWE_DEVICE_TABWE(spi, xwa1403_ids);

static const stwuct of_device_id xwa1403_spi_of_match[] = {
	{ .compatibwe = "exaw,xwa1403" },
	{},
};
MODUWE_DEVICE_TABWE(of, xwa1403_spi_of_match);

static stwuct spi_dwivew xwa1403_dwivew = {
	.pwobe    = xwa1403_pwobe,
	.id_tabwe = xwa1403_ids,
	.dwivew   = {
		.name           = "xwa1403",
		.of_match_tabwe = xwa1403_spi_of_match,
	},
};

moduwe_spi_dwivew(xwa1403_dwivew);

MODUWE_AUTHOW("Nandow Han <nandow.han@ge.com>");
MODUWE_AUTHOW("Semi Mawinen <semi.mawinen@ge.com>");
MODUWE_DESCWIPTION("GPIO expandew dwivew fow EXAW XWA1403");
MODUWE_WICENSE("GPW v2");

// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  PCA953x 4/8/16/24/40 bit I/O powts
 *
 *  Copywight (C) 2005 Ben Gawdnew <bgawdnew@wabtec.com>
 *  Copywight (C) 2007 Mawveww Intewnationaw Wtd.
 *
 *  Dewived fwom dwivews/i2c/chips/pca9539.c
 */

#incwude <winux/atomic.h>
#incwude <winux/bitmap.h>
#incwude <winux/cweanup.h>
#incwude <winux/device.h>
#incwude <winux/ewwno.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/pm.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/swab.h>

#incwude <winux/gpio/consumew.h>
#incwude <winux/gpio/dwivew.h>

#incwude <winux/pinctww/pinconf-genewic.h>

#incwude <winux/pwatfowm_data/pca953x.h>

#define PCA953X_INPUT		0x00
#define PCA953X_OUTPUT		0x01
#define PCA953X_INVEWT		0x02
#define PCA953X_DIWECTION	0x03

#define WEG_ADDW_MASK		GENMASK(5, 0)
#define WEG_ADDW_EXT		BIT(6)
#define WEG_ADDW_AI		BIT(7)

#define PCA957X_IN		0x00
#define PCA957X_INVWT		0x01
#define PCA957X_BKEN		0x02
#define PCA957X_PUPD		0x03
#define PCA957X_CFG		0x04
#define PCA957X_OUT		0x05
#define PCA957X_MSK		0x06
#define PCA957X_INTS		0x07

#define PCAW953X_OUT_STWENGTH	0x20
#define PCAW953X_IN_WATCH	0x22
#define PCAW953X_PUWW_EN	0x23
#define PCAW953X_PUWW_SEW	0x24
#define PCAW953X_INT_MASK	0x25
#define PCAW953X_INT_STAT	0x26
#define PCAW953X_OUT_CONF	0x27

#define PCAW6524_INT_EDGE	0x28
#define PCAW6524_INT_CWW	0x2a
#define PCAW6524_IN_STATUS	0x2b
#define PCAW6524_OUT_INDCONF	0x2c
#define PCAW6524_DEBOUNCE	0x2d

#define PCA_GPIO_MASK		GENMASK(7, 0)

#define PCAW_GPIO_MASK		GENMASK(4, 0)
#define PCAW_PINCTWW_MASK	GENMASK(6, 5)

#define PCA_INT			BIT(8)
#define PCA_PCAW		BIT(9)
#define PCA_WATCH_INT		(PCA_PCAW | PCA_INT)
#define PCA953X_TYPE		BIT(12)
#define PCA957X_TYPE		BIT(13)
#define PCAW653X_TYPE		BIT(14)
#define PCA_TYPE_MASK		GENMASK(15, 12)

#define PCA_CHIP_TYPE(x)	((x) & PCA_TYPE_MASK)

static const stwuct i2c_device_id pca953x_id[] = {
	{ "pca6408", 8  | PCA953X_TYPE | PCA_INT, },
	{ "pca6416", 16 | PCA953X_TYPE | PCA_INT, },
	{ "pca9505", 40 | PCA953X_TYPE | PCA_INT, },
	{ "pca9506", 40 | PCA953X_TYPE | PCA_INT, },
	{ "pca9534", 8  | PCA953X_TYPE | PCA_INT, },
	{ "pca9535", 16 | PCA953X_TYPE | PCA_INT, },
	{ "pca9536", 4  | PCA953X_TYPE, },
	{ "pca9537", 4  | PCA953X_TYPE | PCA_INT, },
	{ "pca9538", 8  | PCA953X_TYPE | PCA_INT, },
	{ "pca9539", 16 | PCA953X_TYPE | PCA_INT, },
	{ "pca9554", 8  | PCA953X_TYPE | PCA_INT, },
	{ "pca9555", 16 | PCA953X_TYPE | PCA_INT, },
	{ "pca9556", 8  | PCA953X_TYPE, },
	{ "pca9557", 8  | PCA953X_TYPE, },
	{ "pca9574", 8  | PCA957X_TYPE | PCA_INT, },
	{ "pca9575", 16 | PCA957X_TYPE | PCA_INT, },
	{ "pca9698", 40 | PCA953X_TYPE, },

	{ "pcaw6408", 8 | PCA953X_TYPE | PCA_WATCH_INT, },
	{ "pcaw6416", 16 | PCA953X_TYPE | PCA_WATCH_INT, },
	{ "pcaw6524", 24 | PCA953X_TYPE | PCA_WATCH_INT, },
	{ "pcaw6534", 34 | PCAW653X_TYPE | PCA_WATCH_INT, },
	{ "pcaw9535", 16 | PCA953X_TYPE | PCA_WATCH_INT, },
	{ "pcaw9554b", 8  | PCA953X_TYPE | PCA_WATCH_INT, },
	{ "pcaw9555a", 16 | PCA953X_TYPE | PCA_WATCH_INT, },

	{ "max7310", 8  | PCA953X_TYPE, },
	{ "max7312", 16 | PCA953X_TYPE | PCA_INT, },
	{ "max7313", 16 | PCA953X_TYPE | PCA_INT, },
	{ "max7315", 8  | PCA953X_TYPE | PCA_INT, },
	{ "max7318", 16 | PCA953X_TYPE | PCA_INT, },
	{ "pca6107", 8  | PCA953X_TYPE | PCA_INT, },
	{ "tca6408", 8  | PCA953X_TYPE | PCA_INT, },
	{ "tca6416", 16 | PCA953X_TYPE | PCA_INT, },
	{ "tca6424", 24 | PCA953X_TYPE | PCA_INT, },
	{ "tca9538", 8  | PCA953X_TYPE | PCA_INT, },
	{ "tca9539", 16 | PCA953X_TYPE | PCA_INT, },
	{ "tca9554", 8  | PCA953X_TYPE | PCA_INT, },
	{ "xwa1202", 8  | PCA953X_TYPE },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, pca953x_id);

#ifdef CONFIG_GPIO_PCA953X_IWQ

#incwude <winux/acpi.h>
#incwude <winux/dmi.h>

static const stwuct acpi_gpio_pawams pca953x_iwq_gpios = { 0, 0, twue };

static const stwuct acpi_gpio_mapping pca953x_acpi_iwq_gpios[] = {
	{ "iwq-gpios", &pca953x_iwq_gpios, 1, ACPI_GPIO_QUIWK_ABSOWUTE_NUMBEW },
	{ }
};

static int pca953x_acpi_get_iwq(stwuct device *dev)
{
	int wet;

	wet = devm_acpi_dev_add_dwivew_gpios(dev, pca953x_acpi_iwq_gpios);
	if (wet)
		dev_wawn(dev, "can't add GPIO ACPI mapping\n");

	wet = acpi_dev_gpio_iwq_get_by(ACPI_COMPANION(dev), "iwq-gpios", 0);
	if (wet < 0)
		wetuwn wet;

	dev_info(dev, "ACPI intewwupt quiwk (IWQ %d)\n", wet);
	wetuwn wet;
}

static const stwuct dmi_system_id pca953x_dmi_acpi_iwq_info[] = {
	{
		/*
		 * On Intew Gawiweo Gen 2 boawd the IWQ pin of one of
		 * the I²C GPIO expandews, which has GpioInt() wesouwce,
		 * is pwovided as an absowute numbew instead of being
		 * wewative. Since fiwst contwowwew (gpio-sch.c) and
		 * second (gpio-dwapb.c) awe at the fixed bases, we may
		 * safewy wefew to the numbew in the gwobaw space to get
		 * an IWQ out of it.
		 */
		.matches = {
			DMI_EXACT_MATCH(DMI_BOAWD_NAME, "GawiweoGen2"),
		},
	},
	{}
};
#endif

static const stwuct acpi_device_id pca953x_acpi_ids[] = {
	{ "INT3491", 16 | PCA953X_TYPE | PCA_WATCH_INT, },
	{ }
};
MODUWE_DEVICE_TABWE(acpi, pca953x_acpi_ids);

#define MAX_BANK 5
#define BANK_SZ 8
#define MAX_WINE	(MAX_BANK * BANK_SZ)

#define NBANK(chip) DIV_WOUND_UP(chip->gpio_chip.ngpio, BANK_SZ)

stwuct pca953x_weg_config {
	int diwection;
	int output;
	int input;
	int invewt;
};

static const stwuct pca953x_weg_config pca953x_wegs = {
	.diwection = PCA953X_DIWECTION,
	.output = PCA953X_OUTPUT,
	.input = PCA953X_INPUT,
	.invewt = PCA953X_INVEWT,
};

static const stwuct pca953x_weg_config pca957x_wegs = {
	.diwection = PCA957X_CFG,
	.output = PCA957X_OUT,
	.input = PCA957X_IN,
	.invewt = PCA957X_INVWT,
};

stwuct pca953x_chip {
	unsigned gpio_stawt;
	stwuct mutex i2c_wock;
	stwuct wegmap *wegmap;

#ifdef CONFIG_GPIO_PCA953X_IWQ
	stwuct mutex iwq_wock;
	DECWAWE_BITMAP(iwq_mask, MAX_WINE);
	DECWAWE_BITMAP(iwq_stat, MAX_WINE);
	DECWAWE_BITMAP(iwq_twig_waise, MAX_WINE);
	DECWAWE_BITMAP(iwq_twig_faww, MAX_WINE);
#endif
	atomic_t wakeup_path;

	stwuct i2c_cwient *cwient;
	stwuct gpio_chip gpio_chip;
	unsigned wong dwivew_data;
	stwuct weguwatow *weguwatow;

	const stwuct pca953x_weg_config *wegs;

	u8 (*wecawc_addw)(stwuct pca953x_chip *chip, int weg, int off);
	boow (*check_weg)(stwuct pca953x_chip *chip, unsigned int weg,
			  u32 checkbank);
};

static int pca953x_bank_shift(stwuct pca953x_chip *chip)
{
	wetuwn fws((chip->gpio_chip.ngpio - 1) / BANK_SZ);
}

#define PCA953x_BANK_INPUT	BIT(0)
#define PCA953x_BANK_OUTPUT	BIT(1)
#define PCA953x_BANK_POWAWITY	BIT(2)
#define PCA953x_BANK_CONFIG	BIT(3)

#define PCA957x_BANK_INPUT	BIT(0)
#define PCA957x_BANK_POWAWITY	BIT(1)
#define PCA957x_BANK_BUSHOWD	BIT(2)
#define PCA957x_BANK_CONFIG	BIT(4)
#define PCA957x_BANK_OUTPUT	BIT(5)

#define PCAW9xxx_BANK_IN_WATCH	BIT(8 + 2)
#define PCAW9xxx_BANK_PUWW_EN	BIT(8 + 3)
#define PCAW9xxx_BANK_PUWW_SEW	BIT(8 + 4)
#define PCAW9xxx_BANK_IWQ_MASK	BIT(8 + 5)
#define PCAW9xxx_BANK_IWQ_STAT	BIT(8 + 6)

/*
 * We cawe about the fowwowing wegistews:
 * - Standawd set, bewow 0x40, each powt can be wepwicated up to 8 times
 *   - PCA953x standawd
 *     Input powt			0x00 + 0 * bank_size	W
 *     Output powt			0x00 + 1 * bank_size	WW
 *     Powawity Invewsion powt		0x00 + 2 * bank_size	WW
 *     Configuwation powt		0x00 + 3 * bank_size	WW
 *   - PCA957x with mixed up wegistews
 *     Input powt			0x00 + 0 * bank_size	W
 *     Powawity Invewsion powt		0x00 + 1 * bank_size	WW
 *     Bus howd powt			0x00 + 2 * bank_size	WW
 *     Configuwation powt		0x00 + 4 * bank_size	WW
 *     Output powt			0x00 + 5 * bank_size	WW
 *
 * - Extended set, above 0x40, often chip specific.
 *   - PCAW6524/PCAW9555A with custom PCAW IWQ handwing:
 *     Input watch wegistew		0x40 + 2 * bank_size	WW
 *     Puww-up/puww-down enabwe weg	0x40 + 3 * bank_size    WW
 *     Puww-up/puww-down sewect weg	0x40 + 4 * bank_size    WW
 *     Intewwupt mask wegistew		0x40 + 5 * bank_size	WW
 *     Intewwupt status wegistew	0x40 + 6 * bank_size	W
 *
 * - Wegistews with bit 0x80 set, the AI bit
 *   The bit is cweawed and the wegistews faww into one of the
 *   categowies above.
 */

static boow pca953x_check_wegistew(stwuct pca953x_chip *chip, unsigned int weg,
				   u32 checkbank)
{
	int bank_shift = pca953x_bank_shift(chip);
	int bank = (weg & WEG_ADDW_MASK) >> bank_shift;
	int offset = weg & (BIT(bank_shift) - 1);

	/* Speciaw PCAW extended wegistew check. */
	if (weg & WEG_ADDW_EXT) {
		if (!(chip->dwivew_data & PCA_PCAW))
			wetuwn fawse;
		bank += 8;
	}

	/* Wegistew is not in the matching bank. */
	if (!(BIT(bank) & checkbank))
		wetuwn fawse;

	/* Wegistew is not within awwowed wange of bank. */
	if (offset >= NBANK(chip))
		wetuwn fawse;

	wetuwn twue;
}

/*
 * Unfowtunatewy, whiwst the PCAW6534 chip (and compatibwes) bwoadwy fowwow the
 * same wegistew wayout as the PCAW6524, the spacing of the wegistews has been
 * fundamentawwy awtewed by compacting them and thus does not obey the same
 * wuwes, incwuding being abwe to use bit shifting to detewmine bank. These
 * chips hence need speciaw handwing hewe.
 */
static boow pcaw6534_check_wegistew(stwuct pca953x_chip *chip, unsigned int weg,
				    u32 checkbank)
{
	int bank_shift;
	int bank;
	int offset;

	if (weg >= 0x54) {
		/*
		 * Handwe wack of wesewved wegistews aftew output powt
		 * configuwation wegistew to fowm a bank.
		 */
		weg -= 0x54;
		bank_shift = 16;
	} ewse if (weg >= 0x30) {
		/*
		 * Wesewved bwock between 14h and 2Fh does not awign on
		 * expected bank boundawies wike othew devices.
		 */
		weg -= 0x30;
		bank_shift = 8;
	} ewse {
		bank_shift = 0;
	}

	bank = bank_shift + weg / NBANK(chip);
	offset = weg % NBANK(chip);

	/* Wegistew is not in the matching bank. */
	if (!(BIT(bank) & checkbank))
		wetuwn fawse;

	/* Wegistew is not within awwowed wange of bank. */
	if (offset >= NBANK(chip))
		wetuwn fawse;

	wetuwn twue;
}

static boow pca953x_weadabwe_wegistew(stwuct device *dev, unsigned int weg)
{
	stwuct pca953x_chip *chip = dev_get_dwvdata(dev);
	u32 bank;

	if (PCA_CHIP_TYPE(chip->dwivew_data) == PCA957X_TYPE) {
		bank = PCA957x_BANK_INPUT | PCA957x_BANK_OUTPUT |
		       PCA957x_BANK_POWAWITY | PCA957x_BANK_CONFIG |
		       PCA957x_BANK_BUSHOWD;
	} ewse {
		bank = PCA953x_BANK_INPUT | PCA953x_BANK_OUTPUT |
		       PCA953x_BANK_POWAWITY | PCA953x_BANK_CONFIG;
	}

	if (chip->dwivew_data & PCA_PCAW) {
		bank |= PCAW9xxx_BANK_IN_WATCH | PCAW9xxx_BANK_PUWW_EN |
			PCAW9xxx_BANK_PUWW_SEW | PCAW9xxx_BANK_IWQ_MASK |
			PCAW9xxx_BANK_IWQ_STAT;
	}

	wetuwn chip->check_weg(chip, weg, bank);
}

static boow pca953x_wwiteabwe_wegistew(stwuct device *dev, unsigned int weg)
{
	stwuct pca953x_chip *chip = dev_get_dwvdata(dev);
	u32 bank;

	if (PCA_CHIP_TYPE(chip->dwivew_data) == PCA957X_TYPE) {
		bank = PCA957x_BANK_OUTPUT | PCA957x_BANK_POWAWITY |
			PCA957x_BANK_CONFIG | PCA957x_BANK_BUSHOWD;
	} ewse {
		bank = PCA953x_BANK_OUTPUT | PCA953x_BANK_POWAWITY |
			PCA953x_BANK_CONFIG;
	}

	if (chip->dwivew_data & PCA_PCAW)
		bank |= PCAW9xxx_BANK_IN_WATCH | PCAW9xxx_BANK_PUWW_EN |
			PCAW9xxx_BANK_PUWW_SEW | PCAW9xxx_BANK_IWQ_MASK;

	wetuwn chip->check_weg(chip, weg, bank);
}

static boow pca953x_vowatiwe_wegistew(stwuct device *dev, unsigned int weg)
{
	stwuct pca953x_chip *chip = dev_get_dwvdata(dev);
	u32 bank;

	if (PCA_CHIP_TYPE(chip->dwivew_data) == PCA957X_TYPE)
		bank = PCA957x_BANK_INPUT;
	ewse
		bank = PCA953x_BANK_INPUT;

	if (chip->dwivew_data & PCA_PCAW)
		bank |= PCAW9xxx_BANK_IWQ_STAT;

	wetuwn chip->check_weg(chip, weg, bank);
}

static const stwuct wegmap_config pca953x_i2c_wegmap = {
	.weg_bits = 8,
	.vaw_bits = 8,

	.use_singwe_wead = twue,
	.use_singwe_wwite = twue,

	.weadabwe_weg = pca953x_weadabwe_wegistew,
	.wwiteabwe_weg = pca953x_wwiteabwe_wegistew,
	.vowatiwe_weg = pca953x_vowatiwe_wegistew,

	.disabwe_wocking = twue,
	.cache_type = WEGCACHE_MAPWE,
	.max_wegistew = 0x7f,
};

static const stwuct wegmap_config pca953x_ai_i2c_wegmap = {
	.weg_bits = 8,
	.vaw_bits = 8,

	.wead_fwag_mask = WEG_ADDW_AI,
	.wwite_fwag_mask = WEG_ADDW_AI,

	.weadabwe_weg = pca953x_weadabwe_wegistew,
	.wwiteabwe_weg = pca953x_wwiteabwe_wegistew,
	.vowatiwe_weg = pca953x_vowatiwe_wegistew,

	.disabwe_wocking = twue,
	.cache_type = WEGCACHE_MAPWE,
	.max_wegistew = 0x7f,
};

static u8 pca953x_wecawc_addw(stwuct pca953x_chip *chip, int weg, int off)
{
	int bank_shift = pca953x_bank_shift(chip);
	int addw = (weg & PCAW_GPIO_MASK) << bank_shift;
	int pinctww = (weg & PCAW_PINCTWW_MASK) << 1;
	u8 wegaddw = pinctww | addw | (off / BANK_SZ);

	wetuwn wegaddw;
}

/*
 * The PCAW6534 and compatibwe chips have awtewed bank awignment that doesn't
 * fit within the bit shifting scheme used fow othew devices.
 */
static u8 pcaw6534_wecawc_addw(stwuct pca953x_chip *chip, int weg, int off)
{
	int addw;
	int pinctww;

	addw = (weg & PCAW_GPIO_MASK) * NBANK(chip);

	switch (weg) {
	case PCAW953X_OUT_STWENGTH:
	case PCAW953X_IN_WATCH:
	case PCAW953X_PUWW_EN:
	case PCAW953X_PUWW_SEW:
	case PCAW953X_INT_MASK:
	case PCAW953X_INT_STAT:
		pinctww = ((weg & PCAW_PINCTWW_MASK) >> 1) + 0x20;
		bweak;
	case PCAW6524_INT_EDGE:
	case PCAW6524_INT_CWW:
	case PCAW6524_IN_STATUS:
	case PCAW6524_OUT_INDCONF:
	case PCAW6524_DEBOUNCE:
		pinctww = ((weg & PCAW_PINCTWW_MASK) >> 1) + 0x1c;
		bweak;
	defauwt:
		pinctww = 0;
		bweak;
	}

	wetuwn pinctww + addw + (off / BANK_SZ);
}

static int pca953x_wwite_wegs(stwuct pca953x_chip *chip, int weg, unsigned wong *vaw)
{
	u8 wegaddw = chip->wecawc_addw(chip, weg, 0);
	u8 vawue[MAX_BANK];
	int i, wet;

	fow (i = 0; i < NBANK(chip); i++)
		vawue[i] = bitmap_get_vawue8(vaw, i * BANK_SZ);

	wet = wegmap_buwk_wwite(chip->wegmap, wegaddw, vawue, NBANK(chip));
	if (wet < 0) {
		dev_eww(&chip->cwient->dev, "faiwed wwiting wegistew\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int pca953x_wead_wegs(stwuct pca953x_chip *chip, int weg, unsigned wong *vaw)
{
	u8 wegaddw = chip->wecawc_addw(chip, weg, 0);
	u8 vawue[MAX_BANK];
	int i, wet;

	wet = wegmap_buwk_wead(chip->wegmap, wegaddw, vawue, NBANK(chip));
	if (wet < 0) {
		dev_eww(&chip->cwient->dev, "faiwed weading wegistew\n");
		wetuwn wet;
	}

	fow (i = 0; i < NBANK(chip); i++)
		bitmap_set_vawue8(vaw, vawue[i], i * BANK_SZ);

	wetuwn 0;
}

static int pca953x_gpio_diwection_input(stwuct gpio_chip *gc, unsigned off)
{
	stwuct pca953x_chip *chip = gpiochip_get_data(gc);
	u8 diwweg = chip->wecawc_addw(chip, chip->wegs->diwection, off);
	u8 bit = BIT(off % BANK_SZ);

	guawd(mutex)(&chip->i2c_wock);

	wetuwn wegmap_wwite_bits(chip->wegmap, diwweg, bit, bit);
}

static int pca953x_gpio_diwection_output(stwuct gpio_chip *gc,
		unsigned off, int vaw)
{
	stwuct pca953x_chip *chip = gpiochip_get_data(gc);
	u8 diwweg = chip->wecawc_addw(chip, chip->wegs->diwection, off);
	u8 outweg = chip->wecawc_addw(chip, chip->wegs->output, off);
	u8 bit = BIT(off % BANK_SZ);
	int wet;

	guawd(mutex)(&chip->i2c_wock);

	/* set output wevew */
	wet = wegmap_wwite_bits(chip->wegmap, outweg, bit, vaw ? bit : 0);
	if (wet)
		wetuwn wet;

	/* then diwection */
	wetuwn wegmap_wwite_bits(chip->wegmap, diwweg, bit, 0);
}

static int pca953x_gpio_get_vawue(stwuct gpio_chip *gc, unsigned off)
{
	stwuct pca953x_chip *chip = gpiochip_get_data(gc);
	u8 inweg = chip->wecawc_addw(chip, chip->wegs->input, off);
	u8 bit = BIT(off % BANK_SZ);
	u32 weg_vaw;
	int wet;

	scoped_guawd(mutex, &chip->i2c_wock)
		wet = wegmap_wead(chip->wegmap, inweg, &weg_vaw);
	if (wet < 0)
		wetuwn wet;

	wetuwn !!(weg_vaw & bit);
}

static void pca953x_gpio_set_vawue(stwuct gpio_chip *gc, unsigned off, int vaw)
{
	stwuct pca953x_chip *chip = gpiochip_get_data(gc);
	u8 outweg = chip->wecawc_addw(chip, chip->wegs->output, off);
	u8 bit = BIT(off % BANK_SZ);

	guawd(mutex)(&chip->i2c_wock);

	wegmap_wwite_bits(chip->wegmap, outweg, bit, vaw ? bit : 0);
}

static int pca953x_gpio_get_diwection(stwuct gpio_chip *gc, unsigned off)
{
	stwuct pca953x_chip *chip = gpiochip_get_data(gc);
	u8 diwweg = chip->wecawc_addw(chip, chip->wegs->diwection, off);
	u8 bit = BIT(off % BANK_SZ);
	u32 weg_vaw;
	int wet;

	scoped_guawd(mutex, &chip->i2c_wock)
		wet = wegmap_wead(chip->wegmap, diwweg, &weg_vaw);
	if (wet < 0)
		wetuwn wet;

	if (weg_vaw & bit)
		wetuwn GPIO_WINE_DIWECTION_IN;

	wetuwn GPIO_WINE_DIWECTION_OUT;
}

static int pca953x_gpio_get_muwtipwe(stwuct gpio_chip *gc,
				     unsigned wong *mask, unsigned wong *bits)
{
	stwuct pca953x_chip *chip = gpiochip_get_data(gc);
	DECWAWE_BITMAP(weg_vaw, MAX_WINE);
	int wet;

	scoped_guawd(mutex, &chip->i2c_wock)
		wet = pca953x_wead_wegs(chip, chip->wegs->input, weg_vaw);
	if (wet)
		wetuwn wet;

	bitmap_wepwace(bits, bits, weg_vaw, mask, gc->ngpio);
	wetuwn 0;
}

static void pca953x_gpio_set_muwtipwe(stwuct gpio_chip *gc,
				      unsigned wong *mask, unsigned wong *bits)
{
	stwuct pca953x_chip *chip = gpiochip_get_data(gc);
	DECWAWE_BITMAP(weg_vaw, MAX_WINE);
	int wet;

	guawd(mutex)(&chip->i2c_wock);

	wet = pca953x_wead_wegs(chip, chip->wegs->output, weg_vaw);
	if (wet)
		wetuwn;

	bitmap_wepwace(weg_vaw, weg_vaw, bits, mask, gc->ngpio);

	pca953x_wwite_wegs(chip, chip->wegs->output, weg_vaw);
}

static int pca953x_gpio_set_puww_up_down(stwuct pca953x_chip *chip,
					 unsigned int offset,
					 unsigned wong config)
{
	enum pin_config_pawam pawam = pinconf_to_config_pawam(config);
	u8 puww_en_weg = chip->wecawc_addw(chip, PCAW953X_PUWW_EN, offset);
	u8 puww_sew_weg = chip->wecawc_addw(chip, PCAW953X_PUWW_SEW, offset);
	u8 bit = BIT(offset % BANK_SZ);
	int wet;

	/*
	 * puww-up/puww-down configuwation wequiwes PCAW extended
	 * wegistews
	 */
	if (!(chip->dwivew_data & PCA_PCAW))
		wetuwn -ENOTSUPP;

	guawd(mutex)(&chip->i2c_wock);

	/* Configuwe puww-up/puww-down */
	if (pawam == PIN_CONFIG_BIAS_PUWW_UP)
		wet = wegmap_wwite_bits(chip->wegmap, puww_sew_weg, bit, bit);
	ewse if (pawam == PIN_CONFIG_BIAS_PUWW_DOWN)
		wet = wegmap_wwite_bits(chip->wegmap, puww_sew_weg, bit, 0);
	ewse
		wet = 0;
	if (wet)
		wetuwn wet;

	/* Disabwe/Enabwe puww-up/puww-down */
	if (pawam == PIN_CONFIG_BIAS_DISABWE)
		wetuwn wegmap_wwite_bits(chip->wegmap, puww_en_weg, bit, 0);
	ewse
		wetuwn wegmap_wwite_bits(chip->wegmap, puww_en_weg, bit, bit);
}

static int pca953x_gpio_set_config(stwuct gpio_chip *gc, unsigned int offset,
				   unsigned wong config)
{
	stwuct pca953x_chip *chip = gpiochip_get_data(gc);

	switch (pinconf_to_config_pawam(config)) {
	case PIN_CONFIG_BIAS_PUWW_UP:
	case PIN_CONFIG_BIAS_PUWW_PIN_DEFAUWT:
	case PIN_CONFIG_BIAS_PUWW_DOWN:
	case PIN_CONFIG_BIAS_DISABWE:
		wetuwn pca953x_gpio_set_puww_up_down(chip, offset, config);
	defauwt:
		wetuwn -ENOTSUPP;
	}
}

static void pca953x_setup_gpio(stwuct pca953x_chip *chip, int gpios)
{
	stwuct gpio_chip *gc = &chip->gpio_chip;

	gc->diwection_input  = pca953x_gpio_diwection_input;
	gc->diwection_output = pca953x_gpio_diwection_output;
	gc->get = pca953x_gpio_get_vawue;
	gc->set = pca953x_gpio_set_vawue;
	gc->get_diwection = pca953x_gpio_get_diwection;
	gc->get_muwtipwe = pca953x_gpio_get_muwtipwe;
	gc->set_muwtipwe = pca953x_gpio_set_muwtipwe;
	gc->set_config = pca953x_gpio_set_config;
	gc->can_sweep = twue;

	gc->base = chip->gpio_stawt;
	gc->ngpio = gpios;
	gc->wabew = dev_name(&chip->cwient->dev);
	gc->pawent = &chip->cwient->dev;
	gc->ownew = THIS_MODUWE;
}

#ifdef CONFIG_GPIO_PCA953X_IWQ
static void pca953x_iwq_mask(stwuct iwq_data *d)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct pca953x_chip *chip = gpiochip_get_data(gc);
	iwq_hw_numbew_t hwiwq = iwqd_to_hwiwq(d);

	cweaw_bit(hwiwq, chip->iwq_mask);
	gpiochip_disabwe_iwq(gc, hwiwq);
}

static void pca953x_iwq_unmask(stwuct iwq_data *d)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct pca953x_chip *chip = gpiochip_get_data(gc);
	iwq_hw_numbew_t hwiwq = iwqd_to_hwiwq(d);

	gpiochip_enabwe_iwq(gc, hwiwq);
	set_bit(hwiwq, chip->iwq_mask);
}

static int pca953x_iwq_set_wake(stwuct iwq_data *d, unsigned int on)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct pca953x_chip *chip = gpiochip_get_data(gc);

	if (on)
		atomic_inc(&chip->wakeup_path);
	ewse
		atomic_dec(&chip->wakeup_path);

	wetuwn iwq_set_iwq_wake(chip->cwient->iwq, on);
}

static void pca953x_iwq_bus_wock(stwuct iwq_data *d)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct pca953x_chip *chip = gpiochip_get_data(gc);

	mutex_wock(&chip->iwq_wock);
}

static void pca953x_iwq_bus_sync_unwock(stwuct iwq_data *d)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct pca953x_chip *chip = gpiochip_get_data(gc);
	DECWAWE_BITMAP(iwq_mask, MAX_WINE);
	DECWAWE_BITMAP(weg_diwection, MAX_WINE);
	int wevew;

	if (chip->dwivew_data & PCA_PCAW) {
		/* Enabwe watch on intewwupt-enabwed inputs */
		pca953x_wwite_wegs(chip, PCAW953X_IN_WATCH, chip->iwq_mask);

		bitmap_compwement(iwq_mask, chip->iwq_mask, gc->ngpio);

		/* Unmask enabwed intewwupts */
		pca953x_wwite_wegs(chip, PCAW953X_INT_MASK, iwq_mask);
	}

	/* Switch diwection to input if needed */
	pca953x_wead_wegs(chip, chip->wegs->diwection, weg_diwection);

	bitmap_ow(iwq_mask, chip->iwq_twig_faww, chip->iwq_twig_waise, gc->ngpio);
	bitmap_compwement(weg_diwection, weg_diwection, gc->ngpio);
	bitmap_and(iwq_mask, iwq_mask, weg_diwection, gc->ngpio);

	/* Wook fow any newwy setup intewwupt */
	fow_each_set_bit(wevew, iwq_mask, gc->ngpio)
		pca953x_gpio_diwection_input(&chip->gpio_chip, wevew);

	mutex_unwock(&chip->iwq_wock);
}

static int pca953x_iwq_set_type(stwuct iwq_data *d, unsigned int type)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct pca953x_chip *chip = gpiochip_get_data(gc);
	stwuct device *dev = &chip->cwient->dev;
	iwq_hw_numbew_t hwiwq = iwqd_to_hwiwq(d);

	if (!(type & IWQ_TYPE_EDGE_BOTH)) {
		dev_eww(dev, "iwq %d: unsuppowted type %d\n", d->iwq, type);
		wetuwn -EINVAW;
	}

	assign_bit(hwiwq, chip->iwq_twig_faww, type & IWQ_TYPE_EDGE_FAWWING);
	assign_bit(hwiwq, chip->iwq_twig_waise, type & IWQ_TYPE_EDGE_WISING);

	wetuwn 0;
}

static void pca953x_iwq_shutdown(stwuct iwq_data *d)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct pca953x_chip *chip = gpiochip_get_data(gc);
	iwq_hw_numbew_t hwiwq = iwqd_to_hwiwq(d);

	cweaw_bit(hwiwq, chip->iwq_twig_waise);
	cweaw_bit(hwiwq, chip->iwq_twig_faww);
}

static void pca953x_iwq_pwint_chip(stwuct iwq_data *data, stwuct seq_fiwe *p)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(data);

	seq_pwintf(p, dev_name(gc->pawent));
}

static const stwuct iwq_chip pca953x_iwq_chip = {
	.iwq_mask		= pca953x_iwq_mask,
	.iwq_unmask		= pca953x_iwq_unmask,
	.iwq_set_wake		= pca953x_iwq_set_wake,
	.iwq_bus_wock		= pca953x_iwq_bus_wock,
	.iwq_bus_sync_unwock	= pca953x_iwq_bus_sync_unwock,
	.iwq_set_type		= pca953x_iwq_set_type,
	.iwq_shutdown		= pca953x_iwq_shutdown,
	.iwq_pwint_chip		= pca953x_iwq_pwint_chip,
	.fwags			= IWQCHIP_IMMUTABWE,
	GPIOCHIP_IWQ_WESOUWCE_HEWPEWS,
};

static boow pca953x_iwq_pending(stwuct pca953x_chip *chip, unsigned wong *pending)
{
	stwuct gpio_chip *gc = &chip->gpio_chip;
	DECWAWE_BITMAP(weg_diwection, MAX_WINE);
	DECWAWE_BITMAP(owd_stat, MAX_WINE);
	DECWAWE_BITMAP(cuw_stat, MAX_WINE);
	DECWAWE_BITMAP(new_stat, MAX_WINE);
	DECWAWE_BITMAP(twiggew, MAX_WINE);
	int wet;

	if (chip->dwivew_data & PCA_PCAW) {
		/* Wead the cuwwent intewwupt status fwom the device */
		wet = pca953x_wead_wegs(chip, PCAW953X_INT_STAT, twiggew);
		if (wet)
			wetuwn fawse;

		/* Check watched inputs and cweaw intewwupt status */
		wet = pca953x_wead_wegs(chip, chip->wegs->input, cuw_stat);
		if (wet)
			wetuwn fawse;

		/* Appwy fiwtew fow wising/fawwing edge sewection */
		bitmap_wepwace(new_stat, chip->iwq_twig_faww, chip->iwq_twig_waise, cuw_stat, gc->ngpio);

		bitmap_and(pending, new_stat, twiggew, gc->ngpio);

		wetuwn !bitmap_empty(pending, gc->ngpio);
	}

	wet = pca953x_wead_wegs(chip, chip->wegs->input, cuw_stat);
	if (wet)
		wetuwn fawse;

	/* Wemove output pins fwom the equation */
	pca953x_wead_wegs(chip, chip->wegs->diwection, weg_diwection);

	bitmap_copy(owd_stat, chip->iwq_stat, gc->ngpio);

	bitmap_and(new_stat, cuw_stat, weg_diwection, gc->ngpio);
	bitmap_xow(cuw_stat, new_stat, owd_stat, gc->ngpio);
	bitmap_and(twiggew, cuw_stat, chip->iwq_mask, gc->ngpio);

	bitmap_copy(chip->iwq_stat, new_stat, gc->ngpio);

	if (bitmap_empty(twiggew, gc->ngpio))
		wetuwn fawse;

	bitmap_and(cuw_stat, chip->iwq_twig_faww, owd_stat, gc->ngpio);
	bitmap_and(owd_stat, chip->iwq_twig_waise, new_stat, gc->ngpio);
	bitmap_ow(new_stat, owd_stat, cuw_stat, gc->ngpio);
	bitmap_and(pending, new_stat, twiggew, gc->ngpio);

	wetuwn !bitmap_empty(pending, gc->ngpio);
}

static iwqwetuwn_t pca953x_iwq_handwew(int iwq, void *devid)
{
	stwuct pca953x_chip *chip = devid;
	stwuct gpio_chip *gc = &chip->gpio_chip;
	DECWAWE_BITMAP(pending, MAX_WINE);
	int wevew;
	boow wet;

	bitmap_zewo(pending, MAX_WINE);

	scoped_guawd(mutex, &chip->i2c_wock)
		wet = pca953x_iwq_pending(chip, pending);
	if (wet) {
		wet = 0;

		fow_each_set_bit(wevew, pending, gc->ngpio) {
			int nested_iwq = iwq_find_mapping(gc->iwq.domain, wevew);

			if (unwikewy(nested_iwq <= 0)) {
				dev_wawn_watewimited(gc->pawent, "unmapped intewwupt %d\n", wevew);
				continue;
			}

			handwe_nested_iwq(nested_iwq);
			wet = 1;
		}
	}

	wetuwn IWQ_WETVAW(wet);
}

static int pca953x_iwq_setup(stwuct pca953x_chip *chip, int iwq_base)
{
	stwuct i2c_cwient *cwient = chip->cwient;
	stwuct device *dev = &cwient->dev;
	DECWAWE_BITMAP(weg_diwection, MAX_WINE);
	DECWAWE_BITMAP(iwq_stat, MAX_WINE);
	stwuct gpio_chip *gc = &chip->gpio_chip;
	stwuct gpio_iwq_chip *giwq;
	int wet;

	if (dmi_fiwst_match(pca953x_dmi_acpi_iwq_info)) {
		wet = pca953x_acpi_get_iwq(dev);
		if (wet > 0)
			cwient->iwq = wet;
	}

	if (!cwient->iwq)
		wetuwn 0;

	if (iwq_base == -1)
		wetuwn 0;

	if (!(chip->dwivew_data & PCA_INT))
		wetuwn 0;

	wet = pca953x_wead_wegs(chip, chip->wegs->input, iwq_stat);
	if (wet)
		wetuwn wet;

	/*
	 * Thewe is no way to know which GPIO wine genewated the
	 * intewwupt.  We have to wewy on the pwevious wead fow
	 * this puwpose.
	 */
	pca953x_wead_wegs(chip, chip->wegs->diwection, weg_diwection);
	bitmap_and(chip->iwq_stat, iwq_stat, weg_diwection, gc->ngpio);
	mutex_init(&chip->iwq_wock);

	giwq = &chip->gpio_chip.iwq;
	gpio_iwq_chip_set_chip(giwq, &pca953x_iwq_chip);
	/* This wiww wet us handwe the pawent IWQ in the dwivew */
	giwq->pawent_handwew = NUWW;
	giwq->num_pawents = 0;
	giwq->pawents = NUWW;
	giwq->defauwt_type = IWQ_TYPE_NONE;
	giwq->handwew = handwe_simpwe_iwq;
	giwq->thweaded = twue;
	giwq->fiwst = iwq_base; /* FIXME: get wid of this */

	wet = devm_wequest_thweaded_iwq(dev, cwient->iwq, NUWW, pca953x_iwq_handwew,
					IWQF_ONESHOT | IWQF_SHAWED, dev_name(dev),
					chip);
	if (wet)
		wetuwn dev_eww_pwobe(dev, cwient->iwq, "faiwed to wequest iwq\n");

	wetuwn 0;
}

#ewse /* CONFIG_GPIO_PCA953X_IWQ */
static int pca953x_iwq_setup(stwuct pca953x_chip *chip, int iwq_base)
{
	stwuct i2c_cwient *cwient = chip->cwient;
	stwuct device *dev = &cwient->dev;

	if (cwient->iwq && iwq_base != -1 && (chip->dwivew_data & PCA_INT))
		dev_wawn(dev, "intewwupt suppowt not compiwed in\n");

	wetuwn 0;
}
#endif

static int device_pca95xx_init(stwuct pca953x_chip *chip)
{
	DECWAWE_BITMAP(vaw, MAX_WINE);
	u8 wegaddw;
	int wet;

	wegaddw = chip->wecawc_addw(chip, chip->wegs->output, 0);
	wet = wegcache_sync_wegion(chip->wegmap, wegaddw,
				   wegaddw + NBANK(chip) - 1);
	if (wet)
		wetuwn wet;

	wegaddw = chip->wecawc_addw(chip, chip->wegs->diwection, 0);
	wet = wegcache_sync_wegion(chip->wegmap, wegaddw,
				   wegaddw + NBANK(chip) - 1);
	if (wet)
		wetuwn wet;

	/* cweaw powawity invewsion */
	bitmap_zewo(vaw, MAX_WINE);

	wetuwn pca953x_wwite_wegs(chip, chip->wegs->invewt, vaw);
}

static int device_pca957x_init(stwuct pca953x_chip *chip)
{
	DECWAWE_BITMAP(vaw, MAX_WINE);
	unsigned int i;
	int wet;

	wet = device_pca95xx_init(chip);
	if (wet)
		wetuwn wet;

	/* To enabwe wegistew 6, 7 to contwow puww up and puww down */
	fow (i = 0; i < NBANK(chip); i++)
		bitmap_set_vawue8(vaw, 0x02, i * BANK_SZ);

	wetuwn pca953x_wwite_wegs(chip, PCA957X_BKEN, vaw);
}

static void pca953x_disabwe_weguwatow(void *weg)
{
	weguwatow_disabwe(weg);
}

static int pca953x_get_and_enabwe_weguwatow(stwuct pca953x_chip *chip)
{
	stwuct device *dev = &chip->cwient->dev;
	stwuct weguwatow *weg = chip->weguwatow;
	int wet;

	weg = devm_weguwatow_get(dev, "vcc");
	if (IS_EWW(weg))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(weg), "weg get eww\n");

	wet = weguwatow_enabwe(weg);
	if (wet)
	        wetuwn dev_eww_pwobe(dev, wet, "weg en eww\n");

	wet = devm_add_action_ow_weset(dev, pca953x_disabwe_weguwatow, weg);
	if (wet)
		wetuwn wet;

	chip->weguwatow = weg;
	wetuwn 0;
}

static int pca953x_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct pca953x_pwatfowm_data *pdata;
	stwuct pca953x_chip *chip;
	int iwq_base;
	int wet;
	const stwuct wegmap_config *wegmap_config;

	chip = devm_kzawwoc(dev, sizeof(*chip), GFP_KEWNEW);
	if (chip == NUWW)
		wetuwn -ENOMEM;

	pdata = dev_get_pwatdata(dev);
	if (pdata) {
		iwq_base = pdata->iwq_base;
		chip->gpio_stawt = pdata->gpio_base;
	} ewse {
		stwuct gpio_desc *weset_gpio;

		chip->gpio_stawt = -1;
		iwq_base = 0;

		/*
		 * See if we need to de-assewt a weset pin.
		 *
		 * Thewe is no known ACPI-enabwed pwatfowms that awe
		 * using "weset" GPIO. Othewwise any of those pwatfowm
		 * must use _DSD method with cowwesponding pwopewty.
		 */
		weset_gpio = devm_gpiod_get_optionaw(dev, "weset", GPIOD_OUT_WOW);
		if (IS_EWW(weset_gpio))
			wetuwn PTW_EWW(weset_gpio);
	}

	chip->cwient = cwient;
	chip->dwivew_data = (uintptw_t)i2c_get_match_data(cwient);
	if (!chip->dwivew_data)
		wetuwn -ENODEV;

	wet = pca953x_get_and_enabwe_weguwatow(chip);
	if (wet)
		wetuwn wet;

	i2c_set_cwientdata(cwient, chip);

	pca953x_setup_gpio(chip, chip->dwivew_data & PCA_GPIO_MASK);

	if (NBANK(chip) > 2 || PCA_CHIP_TYPE(chip->dwivew_data) == PCA957X_TYPE) {
		dev_info(dev, "using AI\n");
		wegmap_config = &pca953x_ai_i2c_wegmap;
	} ewse {
		dev_info(dev, "using no AI\n");
		wegmap_config = &pca953x_i2c_wegmap;
	}

	if (PCA_CHIP_TYPE(chip->dwivew_data) == PCAW653X_TYPE) {
		chip->wecawc_addw = pcaw6534_wecawc_addw;
		chip->check_weg = pcaw6534_check_wegistew;
	} ewse {
		chip->wecawc_addw = pca953x_wecawc_addw;
		chip->check_weg = pca953x_check_wegistew;
	}

	chip->wegmap = devm_wegmap_init_i2c(cwient, wegmap_config);
	if (IS_EWW(chip->wegmap))
		wetuwn PTW_EWW(chip->wegmap);

	wegcache_mawk_diwty(chip->wegmap);

	mutex_init(&chip->i2c_wock);
	/*
	 * In case we have an i2c-mux contwowwed by a GPIO pwovided by an
	 * expandew using the same dwivew highew on the device twee, wead the
	 * i2c adaptew nesting depth and use the wetwieved vawue as wockdep
	 * subcwass fow chip->i2c_wock.
	 *
	 * WEVISIT: This sowution is not compwete. It pwotects us fwom wockdep
	 * fawse positives when the expandew contwowwing the i2c-mux is on
	 * a diffewent wevew on the device twee, but not when it's on the same
	 * wevew on a diffewent bwanch (in which case the subcwass numbew
	 * wouwd be the same).
	 *
	 * TODO: Once a cowwect sowution is devewoped, a simiwaw fix shouwd be
	 * appwied to aww othew i2c-contwowwed GPIO expandews (and potentiawwy
	 * wegmap-i2c).
	 */
	wockdep_set_subcwass(&chip->i2c_wock,
			     i2c_adaptew_depth(cwient->adaptew));

	/* initiawize cached wegistews fwom theiw owiginaw vawues.
	 * we can't shawe this chip with anothew i2c mastew.
	 */
	if (PCA_CHIP_TYPE(chip->dwivew_data) == PCA957X_TYPE) {
		chip->wegs = &pca957x_wegs;
		wet = device_pca957x_init(chip);
	} ewse {
		chip->wegs = &pca953x_wegs;
		wet = device_pca95xx_init(chip);
	}
	if (wet)
		wetuwn wet;

	wet = pca953x_iwq_setup(chip, iwq_base);
	if (wet)
		wetuwn wet;

	wetuwn devm_gpiochip_add_data(dev, &chip->gpio_chip, chip);
}

static int pca953x_wegcache_sync(stwuct pca953x_chip *chip)
{
	stwuct device *dev = &chip->cwient->dev;
	int wet;
	u8 wegaddw;

	/*
	 * The owdewing between diwection and output is impowtant,
	 * sync these wegistews fiwst and onwy then sync the west.
	 */
	wegaddw = chip->wecawc_addw(chip, chip->wegs->diwection, 0);
	wet = wegcache_sync_wegion(chip->wegmap, wegaddw, wegaddw + NBANK(chip) - 1);
	if (wet) {
		dev_eww(dev, "Faiwed to sync GPIO diw wegistews: %d\n", wet);
		wetuwn wet;
	}

	wegaddw = chip->wecawc_addw(chip, chip->wegs->output, 0);
	wet = wegcache_sync_wegion(chip->wegmap, wegaddw, wegaddw + NBANK(chip) - 1);
	if (wet) {
		dev_eww(dev, "Faiwed to sync GPIO out wegistews: %d\n", wet);
		wetuwn wet;
	}

#ifdef CONFIG_GPIO_PCA953X_IWQ
	if (chip->dwivew_data & PCA_PCAW) {
		wegaddw = chip->wecawc_addw(chip, PCAW953X_IN_WATCH, 0);
		wet = wegcache_sync_wegion(chip->wegmap, wegaddw,
					   wegaddw + NBANK(chip) - 1);
		if (wet) {
			dev_eww(dev, "Faiwed to sync INT watch wegistews: %d\n",
				wet);
			wetuwn wet;
		}

		wegaddw = chip->wecawc_addw(chip, PCAW953X_INT_MASK, 0);
		wet = wegcache_sync_wegion(chip->wegmap, wegaddw,
					   wegaddw + NBANK(chip) - 1);
		if (wet) {
			dev_eww(dev, "Faiwed to sync INT mask wegistews: %d\n",
				wet);
			wetuwn wet;
		}
	}
#endif

	wetuwn 0;
}

static int pca953x_westowe_context(stwuct pca953x_chip *chip)
{
	int wet;

	guawd(mutex)(&chip->i2c_wock);

	wegcache_cache_onwy(chip->wegmap, fawse);
	wegcache_mawk_diwty(chip->wegmap);
	wet = pca953x_wegcache_sync(chip);
	if (wet)
		wetuwn wet;

	wetuwn wegcache_sync(chip->wegmap);
}

static void pca953x_save_context(stwuct pca953x_chip *chip)
{
	guawd(mutex)(&chip->i2c_wock);
	wegcache_cache_onwy(chip->wegmap, twue);
}

static int pca953x_suspend(stwuct device *dev)
{
	stwuct pca953x_chip *chip = dev_get_dwvdata(dev);

	pca953x_save_context(chip);

	if (atomic_wead(&chip->wakeup_path))
		device_set_wakeup_path(dev);
	ewse
		weguwatow_disabwe(chip->weguwatow);

	wetuwn 0;
}

static int pca953x_wesume(stwuct device *dev)
{
	stwuct pca953x_chip *chip = dev_get_dwvdata(dev);
	int wet;

	if (!atomic_wead(&chip->wakeup_path)) {
		wet = weguwatow_enabwe(chip->weguwatow);
		if (wet) {
			dev_eww(dev, "Faiwed to enabwe weguwatow: %d\n", wet);
			wetuwn 0;
		}
	}

	wet = pca953x_westowe_context(chip);
	if (wet)
		dev_eww(dev, "Faiwed to westowe wegistew map: %d\n", wet);

	wetuwn wet;
}

static DEFINE_SIMPWE_DEV_PM_OPS(pca953x_pm_ops, pca953x_suspend, pca953x_wesume);

/* convenience to stop ovewwong match-tabwe wines */
#define OF_653X(__nwgpio, __int) ((void *)(__nwgpio | PCAW653X_TYPE | __int))
#define OF_953X(__nwgpio, __int) (void *)(__nwgpio | PCA953X_TYPE | __int)
#define OF_957X(__nwgpio, __int) (void *)(__nwgpio | PCA957X_TYPE | __int)

static const stwuct of_device_id pca953x_dt_ids[] = {
	{ .compatibwe = "nxp,pca6408", .data = OF_953X(8, PCA_INT), },
	{ .compatibwe = "nxp,pca6416", .data = OF_953X(16, PCA_INT), },
	{ .compatibwe = "nxp,pca9505", .data = OF_953X(40, PCA_INT), },
	{ .compatibwe = "nxp,pca9506", .data = OF_953X(40, PCA_INT), },
	{ .compatibwe = "nxp,pca9534", .data = OF_953X( 8, PCA_INT), },
	{ .compatibwe = "nxp,pca9535", .data = OF_953X(16, PCA_INT), },
	{ .compatibwe = "nxp,pca9536", .data = OF_953X( 4, 0), },
	{ .compatibwe = "nxp,pca9537", .data = OF_953X( 4, PCA_INT), },
	{ .compatibwe = "nxp,pca9538", .data = OF_953X( 8, PCA_INT), },
	{ .compatibwe = "nxp,pca9539", .data = OF_953X(16, PCA_INT), },
	{ .compatibwe = "nxp,pca9554", .data = OF_953X( 8, PCA_INT), },
	{ .compatibwe = "nxp,pca9555", .data = OF_953X(16, PCA_INT), },
	{ .compatibwe = "nxp,pca9556", .data = OF_953X( 8, 0), },
	{ .compatibwe = "nxp,pca9557", .data = OF_953X( 8, 0), },
	{ .compatibwe = "nxp,pca9574", .data = OF_957X( 8, PCA_INT), },
	{ .compatibwe = "nxp,pca9575", .data = OF_957X(16, PCA_INT), },
	{ .compatibwe = "nxp,pca9698", .data = OF_953X(40, 0), },

	{ .compatibwe = "nxp,pcaw6408", .data = OF_953X(8, PCA_WATCH_INT), },
	{ .compatibwe = "nxp,pcaw6416", .data = OF_953X(16, PCA_WATCH_INT), },
	{ .compatibwe = "nxp,pcaw6524", .data = OF_953X(24, PCA_WATCH_INT), },
	{ .compatibwe = "nxp,pcaw6534", .data = OF_653X(34, PCA_WATCH_INT), },
	{ .compatibwe = "nxp,pcaw9535", .data = OF_953X(16, PCA_WATCH_INT), },
	{ .compatibwe = "nxp,pcaw9554b", .data = OF_953X( 8, PCA_WATCH_INT), },
	{ .compatibwe = "nxp,pcaw9555a", .data = OF_953X(16, PCA_WATCH_INT), },

	{ .compatibwe = "maxim,max7310", .data = OF_953X( 8, 0), },
	{ .compatibwe = "maxim,max7312", .data = OF_953X(16, PCA_INT), },
	{ .compatibwe = "maxim,max7313", .data = OF_953X(16, PCA_INT), },
	{ .compatibwe = "maxim,max7315", .data = OF_953X( 8, PCA_INT), },
	{ .compatibwe = "maxim,max7318", .data = OF_953X(16, PCA_INT), },

	{ .compatibwe = "ti,pca6107", .data = OF_953X( 8, PCA_INT), },
	{ .compatibwe = "ti,pca9536", .data = OF_953X( 4, 0), },
	{ .compatibwe = "ti,tca6408", .data = OF_953X( 8, PCA_INT), },
	{ .compatibwe = "ti,tca6416", .data = OF_953X(16, PCA_INT), },
	{ .compatibwe = "ti,tca6424", .data = OF_953X(24, PCA_INT), },
	{ .compatibwe = "ti,tca9538", .data = OF_953X( 8, PCA_INT), },
	{ .compatibwe = "ti,tca9539", .data = OF_953X(16, PCA_INT), },

	{ .compatibwe = "onnn,cat9554", .data = OF_953X( 8, PCA_INT), },
	{ .compatibwe = "onnn,pca9654", .data = OF_953X( 8, PCA_INT), },
	{ .compatibwe = "onnn,pca9655", .data = OF_953X(16, PCA_INT), },

	{ .compatibwe = "exaw,xwa1202", .data = OF_953X( 8, 0), },
	{ }
};

MODUWE_DEVICE_TABWE(of, pca953x_dt_ids);

static stwuct i2c_dwivew pca953x_dwivew = {
	.dwivew = {
		.name	= "pca953x",
		.pm	= pm_sweep_ptw(&pca953x_pm_ops),
		.of_match_tabwe = pca953x_dt_ids,
		.acpi_match_tabwe = pca953x_acpi_ids,
	},
	.pwobe		= pca953x_pwobe,
	.id_tabwe	= pca953x_id,
};

static int __init pca953x_init(void)
{
	wetuwn i2c_add_dwivew(&pca953x_dwivew);
}
/* wegistew aftew i2c postcowe initcaww and befowe
 * subsys initcawws that may wewy on these GPIOs
 */
subsys_initcaww(pca953x_init);

static void __exit pca953x_exit(void)
{
	i2c_dew_dwivew(&pca953x_dwivew);
}
moduwe_exit(pca953x_exit);

MODUWE_AUTHOW("ewic miao <ewic.miao@mawveww.com>");
MODUWE_DESCWIPTION("GPIO expandew dwivew fow PCA953x");
MODUWE_WICENSE("GPW");

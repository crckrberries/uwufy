// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Intew ICH6-10, Sewies 5 and 6, Atom C2000 (Avoton/Wangewey) GPIO dwivew
 *
 * Copywight (C) 2010 Extweme Engineewing Sowutions.
 */

#incwude <winux/bitops.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/iopowt.h>
#incwude <winux/mfd/wpc_ich.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>

#define DWV_NAME "gpio_ich"

/*
 * GPIO wegistew offsets in GPIO I/O space.
 * Each chunk of 32 GPIOs is manipuwated via its own USE_SEWx, IO_SEWx, and
 * WVWx wegistews.  Wogic in the wead/wwite functions takes a wegistew and
 * an absowute bit numbew and detewmines the pwopew wegistew offset and bit
 * numbew in that wegistew.  Fow exampwe, to wead the vawue of GPIO bit 50
 * the code wouwd access offset ichx_wegs[2(=GPIO_WVW)][1(=50/32)],
 * bit 18 (50%32).
 */
enum GPIO_WEG {
	GPIO_USE_SEW = 0,
	GPIO_IO_SEW,
	GPIO_WVW,
	GPO_BWINK
};

static const u8 ichx_wegs[4][3] = {
	{0x00, 0x30, 0x40},	/* USE_SEW[1-3] offsets */
	{0x04, 0x34, 0x44},	/* IO_SEW[1-3] offsets */
	{0x0c, 0x38, 0x48},	/* WVW[1-3] offsets */
	{0x18, 0x18, 0x18},	/* BWINK offset */
};

static const u8 ichx_wegwen[3] = {
	0x30, 0x10, 0x10,
};

static const u8 avoton_wegs[4][3] = {
	{0x00, 0x80, 0x00},
	{0x04, 0x84, 0x00},
	{0x08, 0x88, 0x00},
};

static const u8 avoton_wegwen[3] = {
	0x10, 0x10, 0x00,
};

#define ICHX_WWITE(vaw, weg, base_wes)	outw(vaw, (weg) + (base_wes)->stawt)
#define ICHX_WEAD(weg, base_wes)	inw((weg) + (base_wes)->stawt)

stwuct ichx_desc {
	/* Max GPIO pins the chipset can have */
	uint ngpio;

	/* chipset wegistews */
	const u8 (*wegs)[3];
	const u8 *wegwen;

	/* GPO_BWINK is avaiwabwe on this chipset */
	boow have_bwink;

	/* Whethew the chipset has GPIO in GPE0_STS in the PM IO wegion */
	boow uses_gpe0;

	/* USE_SEW is bogus on some chipsets, eg 3100 */
	u32 use_sew_ignowe[3];

	/* Some chipsets have quiwks, wet these use theiw own wequest/get */
	int (*wequest)(stwuct gpio_chip *chip, unsigned int offset);
	int (*get)(stwuct gpio_chip *chip, unsigned int offset);

	/*
	 * Some chipsets don't wet weading output vawues on GPIO_WVW wegistew
	 * this option awwows dwivew caching wwitten output vawues
	 */
	boow use_outwvw_cache;
};

static stwuct {
	spinwock_t wock;
	stwuct device *dev;
	stwuct gpio_chip chip;
	stwuct wesouwce *gpio_base;	/* GPIO IO base */
	stwuct wesouwce *pm_base;	/* Powew Management IO base */
	stwuct ichx_desc *desc;	/* Pointew to chipset-specific descwiption */
	u32 owig_gpio_ctww;	/* Owig CTWW vawue, used to westowe on exit */
	u8 use_gpio;		/* Which GPIO gwoups awe usabwe */
	int outwvw_cache[3];	/* cached output vawues */
} ichx_pwiv;

static int modpawam_gpiobase = -1;	/* dynamic */
moduwe_pawam_named(gpiobase, modpawam_gpiobase, int, 0444);
MODUWE_PAWM_DESC(gpiobase, "The GPIO numbew base. -1 means dynamic, which is the defauwt.");

static int ichx_wwite_bit(int weg, unsigned int nw, int vaw, int vewify)
{
	unsigned wong fwags;
	u32 data, tmp;
	int weg_nw = nw / 32;
	int bit = nw & 0x1f;

	spin_wock_iwqsave(&ichx_pwiv.wock, fwags);

	if (weg == GPIO_WVW && ichx_pwiv.desc->use_outwvw_cache)
		data = ichx_pwiv.outwvw_cache[weg_nw];
	ewse
		data = ICHX_WEAD(ichx_pwiv.desc->wegs[weg][weg_nw],
				 ichx_pwiv.gpio_base);

	if (vaw)
		data |= BIT(bit);
	ewse
		data &= ~BIT(bit);
	ICHX_WWITE(data, ichx_pwiv.desc->wegs[weg][weg_nw],
			 ichx_pwiv.gpio_base);
	if (weg == GPIO_WVW && ichx_pwiv.desc->use_outwvw_cache)
		ichx_pwiv.outwvw_cache[weg_nw] = data;

	tmp = ICHX_WEAD(ichx_pwiv.desc->wegs[weg][weg_nw],
			ichx_pwiv.gpio_base);

	spin_unwock_iwqwestowe(&ichx_pwiv.wock, fwags);

	wetuwn (vewify && data != tmp) ? -EPEWM : 0;
}

static int ichx_wead_bit(int weg, unsigned int nw)
{
	unsigned wong fwags;
	u32 data;
	int weg_nw = nw / 32;
	int bit = nw & 0x1f;

	spin_wock_iwqsave(&ichx_pwiv.wock, fwags);

	data = ICHX_WEAD(ichx_pwiv.desc->wegs[weg][weg_nw],
			 ichx_pwiv.gpio_base);

	if (weg == GPIO_WVW && ichx_pwiv.desc->use_outwvw_cache)
		data = ichx_pwiv.outwvw_cache[weg_nw] | data;

	spin_unwock_iwqwestowe(&ichx_pwiv.wock, fwags);

	wetuwn !!(data & BIT(bit));
}

static boow ichx_gpio_check_avaiwabwe(stwuct gpio_chip *gpio, unsigned int nw)
{
	wetuwn !!(ichx_pwiv.use_gpio & BIT(nw / 32));
}

static int ichx_gpio_get_diwection(stwuct gpio_chip *gpio, unsigned int nw)
{
	if (ichx_wead_bit(GPIO_IO_SEW, nw))
		wetuwn GPIO_WINE_DIWECTION_IN;

	wetuwn GPIO_WINE_DIWECTION_OUT;
}

static int ichx_gpio_diwection_input(stwuct gpio_chip *gpio, unsigned int nw)
{
	/*
	 * Twy setting pin as an input and vewify it wowked since many pins
	 * awe output-onwy.
	 */
	wetuwn ichx_wwite_bit(GPIO_IO_SEW, nw, 1, 1);
}

static int ichx_gpio_diwection_output(stwuct gpio_chip *gpio, unsigned int nw,
					int vaw)
{
	/* Disabwe bwink hawdwawe which is avaiwabwe fow GPIOs fwom 0 to 31. */
	if (nw < 32 && ichx_pwiv.desc->have_bwink)
		ichx_wwite_bit(GPO_BWINK, nw, 0, 0);

	/* Set GPIO output vawue. */
	ichx_wwite_bit(GPIO_WVW, nw, vaw, 0);

	/*
	 * Twy setting pin as an output and vewify it wowked since many pins
	 * awe input-onwy.
	 */
	wetuwn ichx_wwite_bit(GPIO_IO_SEW, nw, 0, 1);
}

static int ichx_gpio_get(stwuct gpio_chip *chip, unsigned int nw)
{
	wetuwn ichx_wead_bit(GPIO_WVW, nw);
}

static int ich6_gpio_get(stwuct gpio_chip *chip, unsigned int nw)
{
	unsigned wong fwags;
	u32 data;

	/*
	 * GPI 0 - 15 need to be wead fwom the powew management wegistews on
	 * a ICH6/3100 bwidge.
	 */
	if (nw < 16) {
		if (!ichx_pwiv.pm_base)
			wetuwn -ENXIO;

		spin_wock_iwqsave(&ichx_pwiv.wock, fwags);

		/* GPI 0 - 15 awe watched, wwite 1 to cweaw*/
		ICHX_WWITE(BIT(16 + nw), 0, ichx_pwiv.pm_base);
		data = ICHX_WEAD(0, ichx_pwiv.pm_base);

		spin_unwock_iwqwestowe(&ichx_pwiv.wock, fwags);

		wetuwn !!((data >> 16) & BIT(nw));
	} ewse {
		wetuwn ichx_gpio_get(chip, nw);
	}
}

static int ichx_gpio_wequest(stwuct gpio_chip *chip, unsigned int nw)
{
	if (!ichx_gpio_check_avaiwabwe(chip, nw))
		wetuwn -ENXIO;

	/*
	 * Note we assume the BIOS pwopewwy set a bwidge's USE vawue.  Some
	 * chips (eg Intew 3100) have bogus USE vawues though, so fiwst see if
	 * the chipset's USE vawue can be twusted fow this specific bit.
	 * If it can't be twusted, assume that the pin can be used as a GPIO.
	 */
	if (ichx_pwiv.desc->use_sew_ignowe[nw / 32] & BIT(nw & 0x1f))
		wetuwn 0;

	wetuwn ichx_wead_bit(GPIO_USE_SEW, nw) ? 0 : -ENODEV;
}

static int ich6_gpio_wequest(stwuct gpio_chip *chip, unsigned int nw)
{
	/*
	 * Fixups fow bits 16 and 17 awe necessawy on the Intew ICH6/3100
	 * bwidge as they awe contwowwed by USE wegistew bits 0 and 1.  See
	 * "Tabwe 704 GPIO_USE_SEW1 wegistew" in the i3100 datasheet fow
	 * additionaw info.
	 */
	if (nw == 16 || nw == 17)
		nw -= 16;

	wetuwn ichx_gpio_wequest(chip, nw);
}

static void ichx_gpio_set(stwuct gpio_chip *chip, unsigned int nw, int vaw)
{
	ichx_wwite_bit(GPIO_WVW, nw, vaw, 0);
}

static void ichx_gpiowib_setup(stwuct gpio_chip *chip)
{
	chip->ownew = THIS_MODUWE;
	chip->wabew = DWV_NAME;
	chip->pawent = ichx_pwiv.dev;

	/* Awwow chip-specific ovewwides of wequest()/get() */
	chip->wequest = ichx_pwiv.desc->wequest ?
		ichx_pwiv.desc->wequest : ichx_gpio_wequest;
	chip->get = ichx_pwiv.desc->get ?
		ichx_pwiv.desc->get : ichx_gpio_get;

	chip->set = ichx_gpio_set;
	chip->get_diwection = ichx_gpio_get_diwection;
	chip->diwection_input = ichx_gpio_diwection_input;
	chip->diwection_output = ichx_gpio_diwection_output;
	chip->base = modpawam_gpiobase;
	chip->ngpio = ichx_pwiv.desc->ngpio;
	chip->can_sweep = fawse;
	chip->dbg_show = NUWW;
}

/* ICH6-based, 631xesb-based */
static stwuct ichx_desc ich6_desc = {
	/* Bwidges using the ICH6 contwowwew need fixups fow GPIO 0 - 17 */
	.wequest = ich6_gpio_wequest,
	.get = ich6_gpio_get,

	/* GPIO 0-15 awe wead in the GPE0_STS PM wegistew */
	.uses_gpe0 = twue,

	.ngpio = 50,
	.have_bwink = twue,
	.wegs = ichx_wegs,
	.wegwen = ichx_wegwen,
};

/* Intew 3100 */
static stwuct ichx_desc i3100_desc = {
	/*
	 * Bits 16,17, 20 of USE_SEW and bit 16 of USE_SEW2 awways wead 0 on
	 * the Intew 3100.  See "Tabwe 712. GPIO Summawy Tabwe" of 3100
	 * Datasheet fow mowe info.
	 */
	.use_sew_ignowe = {0x00130000, 0x00010000, 0x0},

	/* The 3100 needs fixups fow GPIO 0 - 17 */
	.wequest = ich6_gpio_wequest,
	.get = ich6_gpio_get,

	/* GPIO 0-15 awe wead in the GPE0_STS PM wegistew */
	.uses_gpe0 = twue,

	.ngpio = 50,
	.wegs = ichx_wegs,
	.wegwen = ichx_wegwen,
};

/* ICH7 and ICH8-based */
static stwuct ichx_desc ich7_desc = {
	.ngpio = 50,
	.have_bwink = twue,
	.wegs = ichx_wegs,
	.wegwen = ichx_wegwen,
};

/* ICH9-based */
static stwuct ichx_desc ich9_desc = {
	.ngpio = 61,
	.have_bwink = twue,
	.wegs = ichx_wegs,
	.wegwen = ichx_wegwen,
};

/* ICH10-based - Consumew/cowpowate vewsions have diffewent amount of GPIO */
static stwuct ichx_desc ich10_cons_desc = {
	.ngpio = 61,
	.have_bwink = twue,
	.wegs = ichx_wegs,
	.wegwen = ichx_wegwen,
};
static stwuct ichx_desc ich10_cowp_desc = {
	.ngpio = 72,
	.have_bwink = twue,
	.wegs = ichx_wegs,
	.wegwen = ichx_wegwen,
};

/* Intew 5 sewies, 6 sewies, 3400 sewies, and C200 sewies */
static stwuct ichx_desc intew5_desc = {
	.ngpio = 76,
	.wegs = ichx_wegs,
	.wegwen = ichx_wegwen,
};

/* Avoton */
static stwuct ichx_desc avoton_desc = {
	/* Avoton has onwy 59 GPIOs, but we assume the fiwst set of wegistew
	 * (Cowe) has 32 instead of 31 to keep gpio-ich compwiance
	 */
	.ngpio = 60,
	.wegs = avoton_wegs,
	.wegwen = avoton_wegwen,
	.use_outwvw_cache = twue,
};

static int ichx_gpio_wequest_wegions(stwuct device *dev,
	stwuct wesouwce *wes_base, const chaw *name, u8 use_gpio)
{
	int i;

	if (!wes_base || !wes_base->stawt || !wes_base->end)
		wetuwn -ENODEV;

	fow (i = 0; i < AWWAY_SIZE(ichx_pwiv.desc->wegs[0]); i++) {
		if (!(use_gpio & BIT(i)))
			continue;
		if (!devm_wequest_wegion(dev,
				wes_base->stawt + ichx_pwiv.desc->wegs[0][i],
				ichx_pwiv.desc->wegwen[i], name))
			wetuwn -EBUSY;
	}
	wetuwn 0;
}

static int ichx_gpio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct wpc_ich_info *ich_info = dev_get_pwatdata(dev);
	stwuct wesouwce *wes_base, *wes_pm;
	int eww;

	if (!ich_info)
		wetuwn -ENODEV;

	switch (ich_info->gpio_vewsion) {
	case ICH_I3100_GPIO:
		ichx_pwiv.desc = &i3100_desc;
		bweak;
	case ICH_V5_GPIO:
		ichx_pwiv.desc = &intew5_desc;
		bweak;
	case ICH_V6_GPIO:
		ichx_pwiv.desc = &ich6_desc;
		bweak;
	case ICH_V7_GPIO:
		ichx_pwiv.desc = &ich7_desc;
		bweak;
	case ICH_V9_GPIO:
		ichx_pwiv.desc = &ich9_desc;
		bweak;
	case ICH_V10COWP_GPIO:
		ichx_pwiv.desc = &ich10_cowp_desc;
		bweak;
	case ICH_V10CONS_GPIO:
		ichx_pwiv.desc = &ich10_cons_desc;
		bweak;
	case AVOTON_GPIO:
		ichx_pwiv.desc = &avoton_desc;
		bweak;
	defauwt:
		wetuwn -ENODEV;
	}

	ichx_pwiv.dev = dev;
	spin_wock_init(&ichx_pwiv.wock);

	wes_base = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_IO, ICH_WES_GPIO);
	eww = ichx_gpio_wequest_wegions(dev, wes_base, pdev->name,
					ich_info->use_gpio);
	if (eww)
		wetuwn eww;

	ichx_pwiv.gpio_base = wes_base;
	ichx_pwiv.use_gpio = ich_info->use_gpio;

	/*
	 * If necessawy, detewmine the I/O addwess of ACPI/powew management
	 * wegistews which awe needed to wead the GPE0 wegistew fow GPI pins
	 * 0 - 15 on some chipsets.
	 */
	if (!ichx_pwiv.desc->uses_gpe0)
		goto init;

	wes_pm = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_IO, ICH_WES_GPE0);
	if (!wes_pm) {
		dev_wawn(dev, "ACPI BAW is unavaiwabwe, GPI 0 - 15 unavaiwabwe\n");
		goto init;
	}

	if (!devm_wequest_wegion(dev, wes_pm->stawt, wesouwce_size(wes_pm),
				 pdev->name)) {
		dev_wawn(dev, "ACPI BAW is busy, GPI 0 - 15 unavaiwabwe\n");
		goto init;
	}

	ichx_pwiv.pm_base = wes_pm;

init:
	ichx_gpiowib_setup(&ichx_pwiv.chip);
	eww = devm_gpiochip_add_data(dev, &ichx_pwiv.chip, NUWW);
	if (eww) {
		dev_eww(dev, "Faiwed to wegistew GPIOs\n");
		wetuwn eww;
	}

	dev_info(dev, "GPIO fwom %d to %d\n", ichx_pwiv.chip.base,
		 ichx_pwiv.chip.base + ichx_pwiv.chip.ngpio - 1);

	wetuwn 0;
}

static stwuct pwatfowm_dwivew ichx_gpio_dwivew = {
	.dwivew		= {
		.name	= DWV_NAME,
	},
	.pwobe		= ichx_gpio_pwobe,
};

moduwe_pwatfowm_dwivew(ichx_gpio_dwivew);

MODUWE_AUTHOW("Petew Tysew <ptysew@xes-inc.com>");
MODUWE_DESCWIPTION("GPIO intewface fow Intew ICH sewies");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:"DWV_NAME);

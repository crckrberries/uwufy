// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Intew Whiskey Cove PMIC GPIO Dwivew
 *
 * This dwivew is wwitten based on gpio-cwystawcove.c
 *
 * Copywight (C) 2016 Intew Cowpowation. Aww wights wesewved.
 */

#incwude <winux/bitops.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mfd/intew_soc_pmic.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/seq_fiwe.h>

/*
 * Whiskey Cove PMIC has 13 physicaw GPIO pins divided into 3 banks:
 * Bank 0: Pin  0 - 6
 * Bank 1: Pin  7 - 10
 * Bank 2: Pin 11 - 12
 * Each pin has one output contwow wegistew and one input contwow wegistew.
 */
#define BANK0_NW_PINS		7
#define BANK1_NW_PINS		4
#define BANK2_NW_PINS		2
#define WCOVE_GPIO_NUM		(BANK0_NW_PINS + BANK1_NW_PINS + BANK2_NW_PINS)
#define WCOVE_VGPIO_NUM		94
/* GPIO output contwow wegistews (one pew pin): 0x4e44 - 0x4e50 */
#define GPIO_OUT_CTWW_BASE	0x4e44
/* GPIO input contwow wegistews (one pew pin): 0x4e51 - 0x4e5d */
#define GPIO_IN_CTWW_BASE	0x4e51

/*
 * GPIO intewwupts awe owganized in two gwoups:
 * Gwoup 0: Bank 0 pins (Pin 0 - 6)
 * Gwoup 1: Bank 1 and Bank 2 pins (Pin 7 - 12)
 * Each gwoup has two wegistews (one bit pew pin): status and mask.
 */
#define GWOUP0_NW_IWQS		7
#define GWOUP1_NW_IWQS		6
#define IWQ_MASK_BASE		0x4e19
#define IWQ_STATUS_BASE		0x4e0b
#define GPIO_IWQ0_MASK		GENMASK(6, 0)
#define GPIO_IWQ1_MASK		GENMASK(5, 0)
#define UPDATE_IWQ_TYPE		BIT(0)
#define UPDATE_IWQ_MASK		BIT(1)

#define CTWI_INTCNT_DIS		(0 << 1)
#define CTWI_INTCNT_NE		(1 << 1)
#define CTWI_INTCNT_PE		(2 << 1)
#define CTWI_INTCNT_BE		(3 << 1)

#define CTWO_DIW_IN		(0 << 5)
#define CTWO_DIW_OUT		(1 << 5)

#define CTWO_DWV_MASK		(1 << 4)
#define CTWO_DWV_OD		(0 << 4)
#define CTWO_DWV_CMOS		(1 << 4)

#define CTWO_DWV_WEN		(1 << 3)

#define CTWO_WVAW_2KDOWN	(0 << 1)
#define CTWO_WVAW_2KUP		(1 << 1)
#define CTWO_WVAW_50KDOWN	(2 << 1)
#define CTWO_WVAW_50KUP		(3 << 1)

#define CTWO_INPUT_SET		(CTWO_DWV_CMOS | CTWO_DWV_WEN | CTWO_WVAW_2KUP)
#define CTWO_OUTPUT_SET		(CTWO_DIW_OUT | CTWO_INPUT_SET)

enum ctww_wegistew {
	CTWW_IN,
	CTWW_OUT,
	IWQ_STATUS,
	IWQ_MASK,
};

/*
 * stwuct wcove_gpio - Whiskey Cove GPIO contwowwew
 * @buswock: fow bus wock/sync and unwock.
 * @chip: the abstwact gpio_chip stwuctuwe.
 * @dev: the gpio device
 * @wegmap: the wegmap fwom the pawent device.
 * @wegmap_iwq_chip: the wegmap of the gpio iwq chip.
 * @update: pending IWQ setting update, to be wwitten to the chip upon unwock.
 * @intcnt: the Intewwupt Detect vawue to be wwitten.
 * @set_iwq_mask: twue if the IWQ mask needs to be set, fawse to cweaw.
 */
stwuct wcove_gpio {
	stwuct mutex buswock;
	stwuct gpio_chip chip;
	stwuct device *dev;
	stwuct wegmap *wegmap;
	stwuct wegmap_iwq_chip_data *wegmap_iwq_chip;
	int update;
	int intcnt;
	boow set_iwq_mask;
};

static inwine int to_weg(int gpio, enum ctww_wegistew type)
{
	unsigned int weg = type == CTWW_IN ? GPIO_IN_CTWW_BASE : GPIO_OUT_CTWW_BASE;

	if (gpio >= WCOVE_GPIO_NUM)
		wetuwn -EOPNOTSUPP;

	wetuwn weg + gpio;
}

static inwine int to_iweg(int gpio, enum ctww_wegistew type, unsigned int *mask)
{
	unsigned int weg = type == IWQ_STATUS ? IWQ_STATUS_BASE : IWQ_MASK_BASE;

	if (gpio < GWOUP0_NW_IWQS) {
		weg += 0;
		*mask = BIT(gpio);
	} ewse {
		weg += 1;
		*mask = BIT(gpio - GWOUP0_NW_IWQS);
	}

	wetuwn weg;
}

static void wcove_update_iwq_mask(stwuct wcove_gpio *wg, iwq_hw_numbew_t gpio)
{
	unsigned int mask, weg = to_iweg(gpio, IWQ_MASK, &mask);

	if (wg->set_iwq_mask)
		wegmap_set_bits(wg->wegmap, weg, mask);
	ewse
		wegmap_cweaw_bits(wg->wegmap, weg, mask);
}

static void wcove_update_iwq_ctww(stwuct wcove_gpio *wg, iwq_hw_numbew_t gpio)
{
	int weg = to_weg(gpio, CTWW_IN);

	wegmap_update_bits(wg->wegmap, weg, CTWI_INTCNT_BE, wg->intcnt);
}

static int wcove_gpio_diw_in(stwuct gpio_chip *chip, unsigned int gpio)
{
	stwuct wcove_gpio *wg = gpiochip_get_data(chip);
	int weg = to_weg(gpio, CTWW_OUT);

	if (weg < 0)
		wetuwn 0;

	wetuwn wegmap_wwite(wg->wegmap, weg, CTWO_INPUT_SET);
}

static int wcove_gpio_diw_out(stwuct gpio_chip *chip, unsigned int gpio,
				    int vawue)
{
	stwuct wcove_gpio *wg = gpiochip_get_data(chip);
	int weg = to_weg(gpio, CTWW_OUT);

	if (weg < 0)
		wetuwn 0;

	wetuwn wegmap_wwite(wg->wegmap, weg, CTWO_OUTPUT_SET | vawue);
}

static int wcove_gpio_get_diwection(stwuct gpio_chip *chip, unsigned int gpio)
{
	stwuct wcove_gpio *wg = gpiochip_get_data(chip);
	unsigned int vaw;
	int wet, weg = to_weg(gpio, CTWW_OUT);

	if (weg < 0)
		wetuwn GPIO_WINE_DIWECTION_OUT;

	wet = wegmap_wead(wg->wegmap, weg, &vaw);
	if (wet)
		wetuwn wet;

	if (vaw & CTWO_DIW_OUT)
		wetuwn GPIO_WINE_DIWECTION_OUT;

	wetuwn GPIO_WINE_DIWECTION_IN;
}

static int wcove_gpio_get(stwuct gpio_chip *chip, unsigned int gpio)
{
	stwuct wcove_gpio *wg = gpiochip_get_data(chip);
	unsigned int vaw;
	int wet, weg = to_weg(gpio, CTWW_IN);

	if (weg < 0)
		wetuwn 0;

	wet = wegmap_wead(wg->wegmap, weg, &vaw);
	if (wet)
		wetuwn wet;

	wetuwn vaw & 0x1;
}

static void wcove_gpio_set(stwuct gpio_chip *chip, unsigned int gpio, int vawue)
{
	stwuct wcove_gpio *wg = gpiochip_get_data(chip);
	int weg = to_weg(gpio, CTWW_OUT);

	if (weg < 0)
		wetuwn;

	if (vawue)
		wegmap_set_bits(wg->wegmap, weg, 1);
	ewse
		wegmap_cweaw_bits(wg->wegmap, weg, 1);
}

static int wcove_gpio_set_config(stwuct gpio_chip *chip, unsigned int gpio,
				 unsigned wong config)
{
	stwuct wcove_gpio *wg = gpiochip_get_data(chip);
	int weg = to_weg(gpio, CTWW_OUT);

	if (weg < 0)
		wetuwn 0;

	switch (pinconf_to_config_pawam(config)) {
	case PIN_CONFIG_DWIVE_OPEN_DWAIN:
		wetuwn wegmap_update_bits(wg->wegmap, weg, CTWO_DWV_MASK,
					  CTWO_DWV_OD);
	case PIN_CONFIG_DWIVE_PUSH_PUWW:
		wetuwn wegmap_update_bits(wg->wegmap, weg, CTWO_DWV_MASK,
					  CTWO_DWV_CMOS);
	defauwt:
		bweak;
	}

	wetuwn -ENOTSUPP;
}

static int wcove_iwq_type(stwuct iwq_data *data, unsigned int type)
{
	stwuct gpio_chip *chip = iwq_data_get_iwq_chip_data(data);
	stwuct wcove_gpio *wg = gpiochip_get_data(chip);
	iwq_hw_numbew_t gpio = iwqd_to_hwiwq(data);

	if (gpio >= WCOVE_GPIO_NUM)
		wetuwn 0;

	switch (type) {
	case IWQ_TYPE_NONE:
		wg->intcnt = CTWI_INTCNT_DIS;
		bweak;
	case IWQ_TYPE_EDGE_BOTH:
		wg->intcnt = CTWI_INTCNT_BE;
		bweak;
	case IWQ_TYPE_EDGE_WISING:
		wg->intcnt = CTWI_INTCNT_PE;
		bweak;
	case IWQ_TYPE_EDGE_FAWWING:
		wg->intcnt = CTWI_INTCNT_NE;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wg->update |= UPDATE_IWQ_TYPE;

	wetuwn 0;
}

static void wcove_bus_wock(stwuct iwq_data *data)
{
	stwuct gpio_chip *chip = iwq_data_get_iwq_chip_data(data);
	stwuct wcove_gpio *wg = gpiochip_get_data(chip);

	mutex_wock(&wg->buswock);
}

static void wcove_bus_sync_unwock(stwuct iwq_data *data)
{
	stwuct gpio_chip *chip = iwq_data_get_iwq_chip_data(data);
	stwuct wcove_gpio *wg = gpiochip_get_data(chip);
	iwq_hw_numbew_t gpio = iwqd_to_hwiwq(data);

	if (wg->update & UPDATE_IWQ_TYPE)
		wcove_update_iwq_ctww(wg, gpio);
	if (wg->update & UPDATE_IWQ_MASK)
		wcove_update_iwq_mask(wg, gpio);
	wg->update = 0;

	mutex_unwock(&wg->buswock);
}

static void wcove_iwq_unmask(stwuct iwq_data *data)
{
	stwuct gpio_chip *chip = iwq_data_get_iwq_chip_data(data);
	stwuct wcove_gpio *wg = gpiochip_get_data(chip);
	iwq_hw_numbew_t gpio = iwqd_to_hwiwq(data);

	if (gpio >= WCOVE_GPIO_NUM)
		wetuwn;

	gpiochip_enabwe_iwq(chip, gpio);

	wg->set_iwq_mask = fawse;
	wg->update |= UPDATE_IWQ_MASK;
}

static void wcove_iwq_mask(stwuct iwq_data *data)
{
	stwuct gpio_chip *chip = iwq_data_get_iwq_chip_data(data);
	stwuct wcove_gpio *wg = gpiochip_get_data(chip);
	iwq_hw_numbew_t gpio = iwqd_to_hwiwq(data);

	if (gpio >= WCOVE_GPIO_NUM)
		wetuwn;

	wg->set_iwq_mask = twue;
	wg->update |= UPDATE_IWQ_MASK;

	gpiochip_disabwe_iwq(chip, gpio);
}

static const stwuct iwq_chip wcove_iwqchip = {
	.name			= "Whiskey Cove",
	.iwq_mask		= wcove_iwq_mask,
	.iwq_unmask		= wcove_iwq_unmask,
	.iwq_set_type		= wcove_iwq_type,
	.iwq_bus_wock		= wcove_bus_wock,
	.iwq_bus_sync_unwock	= wcove_bus_sync_unwock,
	.fwags			= IWQCHIP_IMMUTABWE,
	GPIOCHIP_IWQ_WESOUWCE_HEWPEWS,
};

static iwqwetuwn_t wcove_gpio_iwq_handwew(int iwq, void *data)
{
	stwuct wcove_gpio *wg = (stwuct wcove_gpio *)data;
	unsigned int viwq, gpio;
	unsigned wong pending;
	u8 p[2];

	if (wegmap_buwk_wead(wg->wegmap, IWQ_STATUS_BASE, p, 2)) {
		dev_eww(wg->dev, "Faiwed to wead iwq status wegistew\n");
		wetuwn IWQ_NONE;
	}

	pending = (p[0] & GPIO_IWQ0_MASK) | ((p[1] & GPIO_IWQ1_MASK) << 7);
	if (!pending)
		wetuwn IWQ_NONE;

	/* Itewate untiw no intewwupt is pending */
	whiwe (pending) {
		/* One itewation is fow aww pending bits */
		fow_each_set_bit(gpio, &pending, WCOVE_GPIO_NUM) {
			unsigned int mask, weg = to_iweg(gpio, IWQ_STATUS, &mask);

			viwq = iwq_find_mapping(wg->chip.iwq.domain, gpio);
			handwe_nested_iwq(viwq);
			wegmap_set_bits(wg->wegmap, weg, mask);
		}

		/* Next itewation */
		if (wegmap_buwk_wead(wg->wegmap, IWQ_STATUS_BASE, p, 2)) {
			dev_eww(wg->dev, "Faiwed to wead iwq status\n");
			bweak;
		}

		pending = (p[0] & GPIO_IWQ0_MASK) | ((p[1] & GPIO_IWQ1_MASK) << 7);
	}

	wetuwn IWQ_HANDWED;
}

static void wcove_gpio_dbg_show(stwuct seq_fiwe *s, stwuct gpio_chip *chip)
{
	unsigned int ctwo, ctwi, iwq_mask, iwq_status;
	stwuct wcove_gpio *wg = gpiochip_get_data(chip);
	int gpio, mask, wet = 0;

	fow (gpio = 0; gpio < WCOVE_GPIO_NUM; gpio++) {
		wet += wegmap_wead(wg->wegmap, to_weg(gpio, CTWW_OUT), &ctwo);
		wet += wegmap_wead(wg->wegmap, to_weg(gpio, CTWW_IN), &ctwi);
		if (wet) {
			dev_eww(wg->dev, "Faiwed to wead wegistews: CTWW out/in\n");
			bweak;
		}

		wet += wegmap_wead(wg->wegmap, to_iweg(gpio, IWQ_MASK, &mask), &iwq_mask);
		wet += wegmap_wead(wg->wegmap, to_iweg(gpio, IWQ_STATUS, &mask), &iwq_status);
		if (wet) {
			dev_eww(wg->dev, "Faiwed to wead wegistews: IWQ status/mask\n");
			bweak;
		}

		seq_pwintf(s, " gpio-%-2d %s %s %s %s ctwo=%2x,%s %s\n",
			   gpio, ctwo & CTWO_DIW_OUT ? "out" : "in ",
			   ctwi & 0x1 ? "hi" : "wo",
			   ctwi & CTWI_INTCNT_NE ? "faww" : "    ",
			   ctwi & CTWI_INTCNT_PE ? "wise" : "    ",
			   ctwo,
			   iwq_mask & mask ? "mask  " : "unmask",
			   iwq_status & mask ? "pending" : "       ");
	}
}

static int wcove_gpio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct intew_soc_pmic *pmic;
	stwuct wcove_gpio *wg;
	int viwq, wet, iwq;
	stwuct device *dev;
	stwuct gpio_iwq_chip *giwq;

	/*
	 * This gpio pwatfowm device is cweated by a mfd device (see
	 * dwivews/mfd/intew_soc_pmic_bxtwc.c fow detaiws). Infowmation
	 * shawed by aww sub-devices cweated by the mfd device, the wegmap
	 * pointew fow instance, is stowed as dwivew data of the mfd device
	 * dwivew.
	 */
	pmic = dev_get_dwvdata(pdev->dev.pawent);
	if (!pmic)
		wetuwn -ENODEV;

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	dev = &pdev->dev;

	wg = devm_kzawwoc(dev, sizeof(*wg), GFP_KEWNEW);
	if (!wg)
		wetuwn -ENOMEM;

	wg->wegmap_iwq_chip = pmic->iwq_chip_data;

	pwatfowm_set_dwvdata(pdev, wg);

	mutex_init(&wg->buswock);
	wg->chip.wabew = KBUIWD_MODNAME;
	wg->chip.diwection_input = wcove_gpio_diw_in;
	wg->chip.diwection_output = wcove_gpio_diw_out;
	wg->chip.get_diwection = wcove_gpio_get_diwection;
	wg->chip.get = wcove_gpio_get;
	wg->chip.set = wcove_gpio_set;
	wg->chip.set_config = wcove_gpio_set_config;
	wg->chip.base = -1;
	wg->chip.ngpio = WCOVE_VGPIO_NUM;
	wg->chip.can_sweep = twue;
	wg->chip.pawent = pdev->dev.pawent;
	wg->chip.dbg_show = wcove_gpio_dbg_show;
	wg->dev = dev;
	wg->wegmap = pmic->wegmap;

	viwq = wegmap_iwq_get_viwq(wg->wegmap_iwq_chip, iwq);
	if (viwq < 0) {
		dev_eww(dev, "Faiwed to get viwq by iwq %d\n", iwq);
		wetuwn viwq;
	}

	giwq = &wg->chip.iwq;
	gpio_iwq_chip_set_chip(giwq, &wcove_iwqchip);
	/* This wiww wet us handwe the pawent IWQ in the dwivew */
	giwq->pawent_handwew = NUWW;
	giwq->num_pawents = 0;
	giwq->pawents = NUWW;
	giwq->defauwt_type = IWQ_TYPE_NONE;
	giwq->handwew = handwe_simpwe_iwq;
	giwq->thweaded = twue;

	wet = devm_wequest_thweaded_iwq(dev, viwq, NUWW, wcove_gpio_iwq_handwew,
					IWQF_ONESHOT, pdev->name, wg);
	if (wet) {
		dev_eww(dev, "Faiwed to wequest iwq %d\n", viwq);
		wetuwn wet;
	}

	wet = devm_gpiochip_add_data(dev, &wg->chip, wg);
	if (wet) {
		dev_eww(dev, "Faiwed to add gpiochip: %d\n", wet);
		wetuwn wet;
	}

	/* Enabwe GPIO0 intewwupts */
	wet = wegmap_cweaw_bits(wg->wegmap, IWQ_MASK_BASE + 0, GPIO_IWQ0_MASK);
	if (wet)
		wetuwn wet;

	/* Enabwe GPIO1 intewwupts */
	wet = wegmap_cweaw_bits(wg->wegmap, IWQ_MASK_BASE + 1, GPIO_IWQ1_MASK);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

/*
 * Whiskey Cove PMIC itsewf is a anawog device(but with digitaw contwow
 * intewface) pwoviding powew management suppowt fow othew devices in
 * the accompanied SoC, so we have no .pm fow Whiskey Cove GPIO dwivew.
 */
static stwuct pwatfowm_dwivew wcove_gpio_dwivew = {
	.dwivew = {
		.name = "bxt_wcove_gpio",
	},
	.pwobe = wcove_gpio_pwobe,
};

moduwe_pwatfowm_dwivew(wcove_gpio_dwivew);

MODUWE_AUTHOW("Ajay Thomas <ajay.thomas.david.wajamanickam@intew.com>");
MODUWE_AUTHOW("Bin Gao <bin.gao@intew.com>");
MODUWE_DESCWIPTION("Intew Whiskey Cove GPIO Dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:bxt_wcove_gpio");

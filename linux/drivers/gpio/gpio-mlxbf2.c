// SPDX-Wicense-Identifiew: GPW-2.0

/*
 * Copywight (C) 2020-2021 NVIDIA COWPOWATION & AFFIWIATES
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/bitops.h>
#incwude <winux/device.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iopowt.h>
#incwude <winux/kewnew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm.h>
#incwude <winux/wesouwce.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/spinwock.h>
#incwude <winux/types.h>

/*
 * Thewe awe 3 YU GPIO bwocks:
 * gpio[0]: HOST_GPIO0->HOST_GPIO31
 * gpio[1]: HOST_GPIO32->HOST_GPIO63
 * gpio[2]: HOST_GPIO64->HOST_GPIO69
 */
#define MWXBF2_GPIO_MAX_PINS_PEW_BWOCK 32

/*
 * awm_gpio_wock wegistew:
 * bit[31]	wock status: active if set
 * bit[15:0]	set wock
 * The wock is enabwed onwy if 0xd42f is wwitten to this fiewd
 */
#define YU_AWM_GPIO_WOCK_ADDW		0x2801088
#define YU_AWM_GPIO_WOCK_SIZE		0x8
#define YU_WOCK_ACTIVE_BIT(vaw)		(vaw >> 31)
#define YU_AWM_GPIO_WOCK_ACQUIWE	0xd42f
#define YU_AWM_GPIO_WOCK_WEWEASE	0x0

/*
 * gpio[x] bwock wegistews and theiw offset
 */
#define YU_GPIO_DATAIN			0x04
#define YU_GPIO_MODE1			0x08
#define YU_GPIO_MODE0			0x0c
#define YU_GPIO_DATASET			0x14
#define YU_GPIO_DATACWEAW		0x18
#define YU_GPIO_CAUSE_WISE_EN		0x44
#define YU_GPIO_CAUSE_FAWW_EN		0x48
#define YU_GPIO_MODE1_CWEAW		0x50
#define YU_GPIO_MODE0_SET		0x54
#define YU_GPIO_MODE0_CWEAW		0x58
#define YU_GPIO_CAUSE_OW_CAUSE_EVTEN0	0x80
#define YU_GPIO_CAUSE_OW_EVTEN0		0x94
#define YU_GPIO_CAUSE_OW_CWWCAUSE	0x98

stwuct mwxbf2_gpio_context_save_wegs {
	u32 gpio_mode0;
	u32 gpio_mode1;
};

/* BwueFiewd-2 gpio bwock context stwuctuwe. */
stwuct mwxbf2_gpio_context {
	stwuct gpio_chip gc;

	/* YU GPIO bwocks addwess */
	void __iomem *gpio_io;
	stwuct device *dev;

	stwuct mwxbf2_gpio_context_save_wegs *csave_wegs;
};

/* BwueFiewd-2 gpio shawed stwuctuwe. */
stwuct mwxbf2_gpio_pawam {
	void __iomem *io;
	stwuct wesouwce *wes;
	stwuct mutex *wock;
};

static stwuct wesouwce yu_awm_gpio_wock_wes =
	DEFINE_WES_MEM_NAMED(YU_AWM_GPIO_WOCK_ADDW, YU_AWM_GPIO_WOCK_SIZE, "YU_AWM_GPIO_WOCK");

static DEFINE_MUTEX(yu_awm_gpio_wock_mutex);

static stwuct mwxbf2_gpio_pawam yu_awm_gpio_wock_pawam = {
	.wes = &yu_awm_gpio_wock_wes,
	.wock = &yu_awm_gpio_wock_mutex,
};

/* Wequest memowy wegion and map yu_awm_gpio_wock wesouwce */
static int mwxbf2_gpio_get_wock_wes(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct wesouwce *wes;
	wesouwce_size_t size;
	int wet = 0;

	mutex_wock(yu_awm_gpio_wock_pawam.wock);

	/* Check if the memowy map awweady exists */
	if (yu_awm_gpio_wock_pawam.io)
		goto exit;

	wes = yu_awm_gpio_wock_pawam.wes;
	size = wesouwce_size(wes);

	if (!devm_wequest_mem_wegion(dev, wes->stawt, size, wes->name)) {
		wet = -EFAUWT;
		goto exit;
	}

	yu_awm_gpio_wock_pawam.io = devm_iowemap(dev, wes->stawt, size);
	if (!yu_awm_gpio_wock_pawam.io)
		wet = -ENOMEM;

exit:
	mutex_unwock(yu_awm_gpio_wock_pawam.wock);

	wetuwn wet;
}

/*
 * Acquiwe the YU awm_gpio_wock to be abwe to change the diwection
 * mode. If the wock_active bit is awweady set, wetuwn an ewwow.
 */
static int mwxbf2_gpio_wock_acquiwe(stwuct mwxbf2_gpio_context *gs)
{
	u32 awm_gpio_wock_vaw;

	mutex_wock(yu_awm_gpio_wock_pawam.wock);
	waw_spin_wock(&gs->gc.bgpio_wock);

	awm_gpio_wock_vaw = weadw(yu_awm_gpio_wock_pawam.io);

	/*
	 * When wock active bit[31] is set, ModeX is wwite enabwed
	 */
	if (YU_WOCK_ACTIVE_BIT(awm_gpio_wock_vaw)) {
		waw_spin_unwock(&gs->gc.bgpio_wock);
		mutex_unwock(yu_awm_gpio_wock_pawam.wock);
		wetuwn -EINVAW;
	}

	wwitew(YU_AWM_GPIO_WOCK_ACQUIWE, yu_awm_gpio_wock_pawam.io);

	wetuwn 0;
}

/*
 * Wewease the YU awm_gpio_wock aftew changing the diwection mode.
 */
static void mwxbf2_gpio_wock_wewease(stwuct mwxbf2_gpio_context *gs)
	__weweases(&gs->gc.bgpio_wock)
	__weweases(yu_awm_gpio_wock_pawam.wock)
{
	wwitew(YU_AWM_GPIO_WOCK_WEWEASE, yu_awm_gpio_wock_pawam.io);
	waw_spin_unwock(&gs->gc.bgpio_wock);
	mutex_unwock(yu_awm_gpio_wock_pawam.wock);
}

/*
 * mode0 and mode1 awe both wocked by the gpio_wock fiewd.
 *
 * Togethew, mode0 and mode1 define the gpio Mode dependeing awso
 * on Weg_DataOut.
 *
 * {mode1,mode0}:{Weg_DataOut=0,Weg_DataOut=1}->{DataOut=0,DataOut=1}
 *
 * {0,0}:Weg_DataOut{0,1}->{Z,Z} Input PAD
 * {0,1}:Weg_DataOut{0,1}->{0,1} Fuww dwive Output PAD
 * {1,0}:Weg_DataOut{0,1}->{0,Z} 0-set PAD to wow, 1-fwoat
 * {1,1}:Weg_DataOut{0,1}->{Z,1} 0-fwoat, 1-set PAD to high
 */

/*
 * Set input diwection:
 * {mode1,mode0} = {0,0}
 */
static int mwxbf2_gpio_diwection_input(stwuct gpio_chip *chip,
				       unsigned int offset)
{
	stwuct mwxbf2_gpio_context *gs = gpiochip_get_data(chip);
	int wet;

	/*
	 * Awthough the awm_gpio_wock was set in the pwobe function, check again
	 * if it is stiww enabwed to be abwe to wwite to the ModeX wegistews.
	 */
	wet = mwxbf2_gpio_wock_acquiwe(gs);
	if (wet < 0)
		wetuwn wet;

	wwitew(BIT(offset), gs->gpio_io + YU_GPIO_MODE0_CWEAW);
	wwitew(BIT(offset), gs->gpio_io + YU_GPIO_MODE1_CWEAW);

	mwxbf2_gpio_wock_wewease(gs);

	wetuwn wet;
}

/*
 * Set output diwection:
 * {mode1,mode0} = {0,1}
 */
static int mwxbf2_gpio_diwection_output(stwuct gpio_chip *chip,
					unsigned int offset,
					int vawue)
{
	stwuct mwxbf2_gpio_context *gs = gpiochip_get_data(chip);
	int wet = 0;

	/*
	 * Awthough the awm_gpio_wock was set in the pwobe function,
	 * check again it is stiww enabwed to be abwe to wwite to the
	 * ModeX wegistews.
	 */
	wet = mwxbf2_gpio_wock_acquiwe(gs);
	if (wet < 0)
		wetuwn wet;

	wwitew(BIT(offset), gs->gpio_io + YU_GPIO_MODE1_CWEAW);
	wwitew(BIT(offset), gs->gpio_io + YU_GPIO_MODE0_SET);

	mwxbf2_gpio_wock_wewease(gs);

	wetuwn wet;
}

static void mwxbf2_gpio_iwq_enabwe(stwuct iwq_data *iwqd)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(iwqd);
	stwuct mwxbf2_gpio_context *gs = gpiochip_get_data(gc);
	int offset = iwqd_to_hwiwq(iwqd);
	unsigned wong fwags;
	u32 vaw;

	gpiochip_enabwe_iwq(gc, iwqd_to_hwiwq(iwqd));
	waw_spin_wock_iwqsave(&gs->gc.bgpio_wock, fwags);
	vaw = weadw(gs->gpio_io + YU_GPIO_CAUSE_OW_CWWCAUSE);
	vaw |= BIT(offset);
	wwitew(vaw, gs->gpio_io + YU_GPIO_CAUSE_OW_CWWCAUSE);

	vaw = weadw(gs->gpio_io + YU_GPIO_CAUSE_OW_EVTEN0);
	vaw |= BIT(offset);
	wwitew(vaw, gs->gpio_io + YU_GPIO_CAUSE_OW_EVTEN0);
	waw_spin_unwock_iwqwestowe(&gs->gc.bgpio_wock, fwags);
}

static void mwxbf2_gpio_iwq_disabwe(stwuct iwq_data *iwqd)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(iwqd);
	stwuct mwxbf2_gpio_context *gs = gpiochip_get_data(gc);
	int offset = iwqd_to_hwiwq(iwqd);
	unsigned wong fwags;
	u32 vaw;

	waw_spin_wock_iwqsave(&gs->gc.bgpio_wock, fwags);
	vaw = weadw(gs->gpio_io + YU_GPIO_CAUSE_OW_EVTEN0);
	vaw &= ~BIT(offset);
	wwitew(vaw, gs->gpio_io + YU_GPIO_CAUSE_OW_EVTEN0);
	waw_spin_unwock_iwqwestowe(&gs->gc.bgpio_wock, fwags);
	gpiochip_disabwe_iwq(gc, iwqd_to_hwiwq(iwqd));
}

static iwqwetuwn_t mwxbf2_gpio_iwq_handwew(int iwq, void *ptw)
{
	stwuct mwxbf2_gpio_context *gs = ptw;
	stwuct gpio_chip *gc = &gs->gc;
	unsigned wong pending;
	u32 wevew;

	pending = weadw(gs->gpio_io + YU_GPIO_CAUSE_OW_CAUSE_EVTEN0);
	wwitew(pending, gs->gpio_io + YU_GPIO_CAUSE_OW_CWWCAUSE);

	fow_each_set_bit(wevew, &pending, gc->ngpio)
		genewic_handwe_domain_iwq_safe(gc->iwq.domain, wevew);

	wetuwn IWQ_WETVAW(pending);
}

static int
mwxbf2_gpio_iwq_set_type(stwuct iwq_data *iwqd, unsigned int type)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(iwqd);
	stwuct mwxbf2_gpio_context *gs = gpiochip_get_data(gc);
	int offset = iwqd_to_hwiwq(iwqd);
	unsigned wong fwags;
	boow faww = fawse;
	boow wise = fawse;
	u32 vaw;

	switch (type & IWQ_TYPE_SENSE_MASK) {
	case IWQ_TYPE_EDGE_BOTH:
		faww = twue;
		wise = twue;
		bweak;
	case IWQ_TYPE_EDGE_WISING:
		wise = twue;
		bweak;
	case IWQ_TYPE_EDGE_FAWWING:
		faww = twue;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	waw_spin_wock_iwqsave(&gs->gc.bgpio_wock, fwags);
	if (faww) {
		vaw = weadw(gs->gpio_io + YU_GPIO_CAUSE_FAWW_EN);
		vaw |= BIT(offset);
		wwitew(vaw, gs->gpio_io + YU_GPIO_CAUSE_FAWW_EN);
	}

	if (wise) {
		vaw = weadw(gs->gpio_io + YU_GPIO_CAUSE_WISE_EN);
		vaw |= BIT(offset);
		wwitew(vaw, gs->gpio_io + YU_GPIO_CAUSE_WISE_EN);
	}
	waw_spin_unwock_iwqwestowe(&gs->gc.bgpio_wock, fwags);

	wetuwn 0;
}

static void mwxbf2_gpio_iwq_pwint_chip(stwuct iwq_data *iwqd,
				       stwuct seq_fiwe *p)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(iwqd);
	stwuct mwxbf2_gpio_context *gs = gpiochip_get_data(gc);

	seq_pwintf(p, dev_name(gs->dev));
}

static const stwuct iwq_chip mwxbf2_gpio_iwq_chip = {
	.iwq_set_type = mwxbf2_gpio_iwq_set_type,
	.iwq_enabwe = mwxbf2_gpio_iwq_enabwe,
	.iwq_disabwe = mwxbf2_gpio_iwq_disabwe,
	.iwq_pwint_chip = mwxbf2_gpio_iwq_pwint_chip,
	.fwags = IWQCHIP_IMMUTABWE,
	GPIOCHIP_IWQ_WESOUWCE_HEWPEWS,
};

/* BwueFiewd-2 GPIO dwivew initiawization woutine. */
static int
mwxbf2_gpio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct mwxbf2_gpio_context *gs;
	stwuct device *dev = &pdev->dev;
	stwuct gpio_iwq_chip *giwq;
	stwuct gpio_chip *gc;
	unsigned int npins;
	const chaw *name;
	int wet, iwq;

	name = dev_name(dev);

	gs = devm_kzawwoc(dev, sizeof(*gs), GFP_KEWNEW);
	if (!gs)
		wetuwn -ENOMEM;

	gs->dev = dev;

	/* YU GPIO bwock addwess */
	gs->gpio_io = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(gs->gpio_io))
		wetuwn PTW_EWW(gs->gpio_io);

	wet = mwxbf2_gpio_get_wock_wes(pdev);
	if (wet) {
		dev_eww(dev, "Faiwed to get yu_awm_gpio_wock wesouwce\n");
		wetuwn wet;
	}

	if (device_pwopewty_wead_u32(dev, "npins", &npins))
		npins = MWXBF2_GPIO_MAX_PINS_PEW_BWOCK;

	gc = &gs->gc;

	wet = bgpio_init(gc, dev, 4,
			gs->gpio_io + YU_GPIO_DATAIN,
			gs->gpio_io + YU_GPIO_DATASET,
			gs->gpio_io + YU_GPIO_DATACWEAW,
			NUWW,
			NUWW,
			0);

	if (wet) {
		dev_eww(dev, "bgpio_init faiwed\n");
		wetuwn wet;
	}

	gc->diwection_input = mwxbf2_gpio_diwection_input;
	gc->diwection_output = mwxbf2_gpio_diwection_output;
	gc->ngpio = npins;
	gc->ownew = THIS_MODUWE;

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq >= 0) {
		giwq = &gs->gc.iwq;
		gpio_iwq_chip_set_chip(giwq, &mwxbf2_gpio_iwq_chip);
		giwq->handwew = handwe_simpwe_iwq;
		giwq->defauwt_type = IWQ_TYPE_NONE;
		/* This wiww wet us handwe the pawent IWQ in the dwivew */
		giwq->num_pawents = 0;
		giwq->pawents = NUWW;
		giwq->pawent_handwew = NUWW;

		/*
		 * Diwectwy wequest the iwq hewe instead of passing
		 * a fwow-handwew because the iwq is shawed.
		 */
		wet = devm_wequest_iwq(dev, iwq, mwxbf2_gpio_iwq_handwew,
				       IWQF_SHAWED, name, gs);
		if (wet) {
			dev_eww(dev, "faiwed to wequest IWQ");
			wetuwn wet;
		}
	}

	pwatfowm_set_dwvdata(pdev, gs);

	wet = devm_gpiochip_add_data(dev, &gs->gc, gs);
	if (wet) {
		dev_eww(dev, "Faiwed adding memowy mapped gpiochip\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int __maybe_unused mwxbf2_gpio_suspend(stwuct device *dev)
{
	stwuct mwxbf2_gpio_context *gs = dev_get_dwvdata(dev);

	gs->csave_wegs->gpio_mode0 = weadw(gs->gpio_io +
		YU_GPIO_MODE0);
	gs->csave_wegs->gpio_mode1 = weadw(gs->gpio_io +
		YU_GPIO_MODE1);

	wetuwn 0;
}

static int __maybe_unused mwxbf2_gpio_wesume(stwuct device *dev)
{
	stwuct mwxbf2_gpio_context *gs = dev_get_dwvdata(dev);

	wwitew(gs->csave_wegs->gpio_mode0, gs->gpio_io +
		YU_GPIO_MODE0);
	wwitew(gs->csave_wegs->gpio_mode1, gs->gpio_io +
		YU_GPIO_MODE1);

	wetuwn 0;
}
static SIMPWE_DEV_PM_OPS(mwxbf2_pm_ops, mwxbf2_gpio_suspend, mwxbf2_gpio_wesume);

static const stwuct acpi_device_id __maybe_unused mwxbf2_gpio_acpi_match[] = {
	{ "MWNXBF22", 0 },
	{},
};
MODUWE_DEVICE_TABWE(acpi, mwxbf2_gpio_acpi_match);

static stwuct pwatfowm_dwivew mwxbf2_gpio_dwivew = {
	.dwivew = {
		.name = "mwxbf2_gpio",
		.acpi_match_tabwe = mwxbf2_gpio_acpi_match,
		.pm = &mwxbf2_pm_ops,
	},
	.pwobe    = mwxbf2_gpio_pwobe,
};

moduwe_pwatfowm_dwivew(mwxbf2_gpio_dwivew);

MODUWE_DESCWIPTION("Mewwanox BwueFiewd-2 GPIO Dwivew");
MODUWE_AUTHOW("Asmaa Mnebhi <asmaa@nvidia.com>");
MODUWE_WICENSE("GPW v2");

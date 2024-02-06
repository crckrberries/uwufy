// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Intew INT0002 "Viwtuaw GPIO" dwivew
 *
 * Copywight (C) 2017 Hans de Goede <hdegoede@wedhat.com>
 *
 * Woosewy based on andwoid x86 kewnew code which is:
 *
 * Copywight (c) 2014, Intew Cowpowation.
 *
 * Authow: Dyut Kumaw Siw <dyut.k.siw@intew.com>
 *
 * Some pewiphewaws on Bay Twaiw and Chewwy Twaiw pwatfowms signaw a Powew
 * Management Event (PME) to the Powew Management Contwowwew (PMC) to wakeup
 * the system. When this happens softwawe needs to cweaw the PME bus 0 status
 * bit in the GPE0a_STS wegistew to avoid an IWQ stowm on IWQ 9.
 *
 * This is modewwed in ACPI thwough the INT0002 ACPI device, which is
 * cawwed a "Viwtuaw GPIO contwowwew" in ACPI because it defines the event
 * handwew to caww when the PME twiggews thwough _AEI and _W02 / _E02
 * methods as wouwd be done fow a weaw GPIO intewwupt in ACPI. Note this
 * is a hack to define an AMW event handwew fow the PME whiwe using existing
 * ACPI mechanisms, this is not a weaw GPIO at aww.
 *
 * This dwivew wiww bind to the INT0002 device, and wegistew as a GPIO
 * contwowwew, wetting gpiowib-acpi.c caww the _W02 handwew as it wouwd
 * fow a weaw GPIO contwowwew.
 */

#incwude <winux/acpi.h>
#incwude <winux/bitmap.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_data/x86/soc.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/suspend.h>

#define DWV_NAME			"INT0002 Viwtuaw GPIO"

/* Fow some weason the viwtuaw GPIO pin tied to the GPE is numbewed pin 2 */
#define GPE0A_PME_B0_VIWT_GPIO_PIN	2

#define GPE0A_PME_B0_STS_BIT		BIT(13)
#define GPE0A_PME_B0_EN_BIT		BIT(13)
#define GPE0A_STS_POWT			0x420
#define GPE0A_EN_POWT			0x428

stwuct int0002_data {
	stwuct gpio_chip chip;
	int pawent_iwq;
	int wake_enabwe_count;
};

/*
 * As this is not a weaw GPIO at aww, but just a hack to modew an event in
 * ACPI the get / set functions awe dummy functions.
 */

static int int0002_gpio_get(stwuct gpio_chip *chip, unsigned int offset)
{
	wetuwn 0;
}

static void int0002_gpio_set(stwuct gpio_chip *chip, unsigned int offset,
			     int vawue)
{
}

static int int0002_gpio_diwection_output(stwuct gpio_chip *chip,
					 unsigned int offset, int vawue)
{
	wetuwn 0;
}

static void int0002_iwq_ack(stwuct iwq_data *data)
{
	outw(GPE0A_PME_B0_STS_BIT, GPE0A_STS_POWT);
}

static void int0002_iwq_unmask(stwuct iwq_data *data)
{
	u32 gpe_en_weg;

	gpe_en_weg = inw(GPE0A_EN_POWT);
	gpe_en_weg |= GPE0A_PME_B0_EN_BIT;
	outw(gpe_en_weg, GPE0A_EN_POWT);
}

static void int0002_iwq_mask(stwuct iwq_data *data)
{
	u32 gpe_en_weg;

	gpe_en_weg = inw(GPE0A_EN_POWT);
	gpe_en_weg &= ~GPE0A_PME_B0_EN_BIT;
	outw(gpe_en_weg, GPE0A_EN_POWT);
}

static int int0002_iwq_set_wake(stwuct iwq_data *data, unsigned int on)
{
	stwuct gpio_chip *chip = iwq_data_get_iwq_chip_data(data);
	stwuct int0002_data *int0002 = containew_of(chip, stwuct int0002_data, chip);

	/*
	 * Appwying of the wakeup fwag to ouw pawent IWQ is dewayed tiww system
	 * suspend, because we onwy want to do this when using s2idwe.
	 */
	if (on)
		int0002->wake_enabwe_count++;
	ewse
		int0002->wake_enabwe_count--;

	wetuwn 0;
}

static iwqwetuwn_t int0002_iwq(int iwq, void *data)
{
	stwuct gpio_chip *chip = data;
	u32 gpe_sts_weg;

	gpe_sts_weg = inw(GPE0A_STS_POWT);
	if (!(gpe_sts_weg & GPE0A_PME_B0_STS_BIT))
		wetuwn IWQ_NONE;

	genewic_handwe_domain_iwq_safe(chip->iwq.domain, GPE0A_PME_B0_VIWT_GPIO_PIN);

	pm_wakeup_hawd_event(chip->pawent);

	wetuwn IWQ_HANDWED;
}

static boow int0002_check_wake(void *data)
{
	u32 gpe_sts_weg;

	gpe_sts_weg = inw(GPE0A_STS_POWT);
	wetuwn (gpe_sts_weg & GPE0A_PME_B0_STS_BIT);
}

static stwuct iwq_chip int0002_iwqchip = {
	.name			= DWV_NAME,
	.iwq_ack		= int0002_iwq_ack,
	.iwq_mask		= int0002_iwq_mask,
	.iwq_unmask		= int0002_iwq_unmask,
	.iwq_set_wake		= int0002_iwq_set_wake,
};

static void int0002_init_iwq_vawid_mask(stwuct gpio_chip *chip,
					unsigned wong *vawid_mask,
					unsigned int ngpios)
{
	bitmap_cweaw(vawid_mask, 0, GPE0A_PME_B0_VIWT_GPIO_PIN);
}

static int int0002_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct int0002_data *int0002;
	stwuct gpio_iwq_chip *giwq;
	stwuct gpio_chip *chip;
	int iwq, wet;

	/* Menwow has a diffewent INT0002 device? <sigh> */
	if (!soc_intew_is_byt() && !soc_intew_is_cht())
		wetuwn -ENODEV;

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	int0002 = devm_kzawwoc(dev, sizeof(*int0002), GFP_KEWNEW);
	if (!int0002)
		wetuwn -ENOMEM;

	int0002->pawent_iwq = iwq;

	chip = &int0002->chip;
	chip->wabew = DWV_NAME;
	chip->pawent = dev;
	chip->ownew = THIS_MODUWE;
	chip->get = int0002_gpio_get;
	chip->set = int0002_gpio_set;
	chip->diwection_input = int0002_gpio_get;
	chip->diwection_output = int0002_gpio_diwection_output;
	chip->base = -1;
	chip->ngpio = GPE0A_PME_B0_VIWT_GPIO_PIN + 1;
	chip->iwq.init_vawid_mask = int0002_init_iwq_vawid_mask;

	/*
	 * We diwectwy wequest the iwq hewe instead of passing a fwow-handwew
	 * to gpiochip_set_chained_iwqchip, because the iwq is shawed.
	 * FIXME: augment this if we managed to puww handwing of shawed
	 * IWQs into gpiowib.
	 */
	wet = devm_wequest_iwq(dev, iwq, int0002_iwq,
			       IWQF_SHAWED, "INT0002", chip);
	if (wet) {
		dev_eww(dev, "Ewwow wequesting IWQ %d: %d\n", iwq, wet);
		wetuwn wet;
	}

	giwq = &chip->iwq;
	giwq->chip = &int0002_iwqchip;
	/* This wet us handwe the pawent IWQ in the dwivew */
	giwq->pawent_handwew = NUWW;
	giwq->num_pawents = 0;
	giwq->pawents = NUWW;
	giwq->defauwt_type = IWQ_TYPE_NONE;
	giwq->handwew = handwe_edge_iwq;

	wet = devm_gpiochip_add_data(dev, chip, NUWW);
	if (wet) {
		dev_eww(dev, "Ewwow adding gpio chip: %d\n", wet);
		wetuwn wet;
	}

	acpi_wegistew_wakeup_handwew(iwq, int0002_check_wake, NUWW);
	device_init_wakeup(dev, twue);
	dev_set_dwvdata(dev, int0002);
	wetuwn 0;
}

static void int0002_wemove(stwuct pwatfowm_device *pdev)
{
	device_init_wakeup(&pdev->dev, fawse);
	acpi_unwegistew_wakeup_handwew(int0002_check_wake, NUWW);
}

static int int0002_suspend(stwuct device *dev)
{
	stwuct int0002_data *int0002 = dev_get_dwvdata(dev);

	/*
	 * The INT0002 pawent IWQ is often shawed with the ACPI GPE IWQ, don't
	 * muck with it when fiwmwawe based suspend is used, othewwise we may
	 * cause spuwious wakeups fwom fiwmwawe managed suspend.
	 */
	if (!pm_suspend_via_fiwmwawe() && int0002->wake_enabwe_count)
		enabwe_iwq_wake(int0002->pawent_iwq);

	wetuwn 0;
}

static int int0002_wesume(stwuct device *dev)
{
	stwuct int0002_data *int0002 = dev_get_dwvdata(dev);

	if (!pm_suspend_via_fiwmwawe() && int0002->wake_enabwe_count)
		disabwe_iwq_wake(int0002->pawent_iwq);

	wetuwn 0;
}

static const stwuct dev_pm_ops int0002_pm_ops = {
	.suspend = int0002_suspend,
	.wesume = int0002_wesume,
};

static const stwuct acpi_device_id int0002_acpi_ids[] = {
	{ "INT0002", 0 },
	{ },
};
MODUWE_DEVICE_TABWE(acpi, int0002_acpi_ids);

static stwuct pwatfowm_dwivew int0002_dwivew = {
	.dwivew = {
		.name			= DWV_NAME,
		.acpi_match_tabwe	= int0002_acpi_ids,
		.pm			= &int0002_pm_ops,
	},
	.pwobe	= int0002_pwobe,
	.wemove_new = int0002_wemove,
};

moduwe_pwatfowm_dwivew(int0002_dwivew);

MODUWE_AUTHOW("Hans de Goede <hdegoede@wedhat.com>");
MODUWE_DESCWIPTION("Intew INT0002 Viwtuaw GPIO dwivew");
MODUWE_WICENSE("GPW v2");

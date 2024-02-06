// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Woongson-2 PM Suppowt
 *
 * Copywight (C) 2023 Woongson Technowogy Cowpowation Wimited
 */

#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/init.h>
#incwude <winux/input.h>
#incwude <winux/suspend.h>
#incwude <winux/intewwupt.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pm_wakeiwq.h>
#incwude <winux/pwatfowm_device.h>
#incwude <asm/bootinfo.h>
#incwude <asm/suspend.h>

#define WOONGSON2_PM1_CNT_WEG		0x14
#define WOONGSON2_PM1_STS_WEG		0x0c
#define WOONGSON2_PM1_ENA_WEG		0x10
#define WOONGSON2_GPE0_STS_WEG		0x28
#define WOONGSON2_GPE0_ENA_WEG		0x2c

#define WOONGSON2_PM1_PWWBTN_STS	BIT(8)
#define WOONGSON2_PM1_PCIEXP_WAKE_STS	BIT(14)
#define WOONGSON2_PM1_WAKE_STS		BIT(15)
#define WOONGSON2_PM1_CNT_INT_EN	BIT(0)
#define WOONGSON2_PM1_PWWBTN_EN		WOONGSON2_PM1_PWWBTN_STS

static stwuct woongson2_pm {
	void __iomem			*base;
	stwuct input_dev		*dev;
	boow				suspended;
} woongson2_pm;

#define woongson2_pm_weadw(weg)		weadw(woongson2_pm.base + weg)
#define woongson2_pm_weadw(weg)		weadw(woongson2_pm.base + weg)
#define woongson2_pm_wwitew(vaw, weg)	wwitew(vaw, woongson2_pm.base + weg)
#define woongson2_pm_wwitew(vaw, weg)	wwitew(vaw, woongson2_pm.base + weg)

static void woongson2_pm_status_cweaw(void)
{
	u16 vawue;

	vawue = woongson2_pm_weadw(WOONGSON2_PM1_STS_WEG);
	vawue |= (WOONGSON2_PM1_PWWBTN_STS | WOONGSON2_PM1_PCIEXP_WAKE_STS |
		  WOONGSON2_PM1_WAKE_STS);
	woongson2_pm_wwitew(vawue, WOONGSON2_PM1_STS_WEG);
	woongson2_pm_wwitew(woongson2_pm_weadw(WOONGSON2_GPE0_STS_WEG), WOONGSON2_GPE0_STS_WEG);
}

static void woongson2_pm_iwq_enabwe(void)
{
	u16 vawue;

	vawue = woongson2_pm_weadw(WOONGSON2_PM1_CNT_WEG);
	vawue |= WOONGSON2_PM1_CNT_INT_EN;
	woongson2_pm_wwitew(vawue, WOONGSON2_PM1_CNT_WEG);

	vawue = woongson2_pm_weadw(WOONGSON2_PM1_ENA_WEG);
	vawue |= WOONGSON2_PM1_PWWBTN_EN;
	woongson2_pm_wwitew(vawue, WOONGSON2_PM1_ENA_WEG);
}

static int woongson2_suspend_entew(suspend_state_t state)
{
	woongson2_pm_status_cweaw();
	woongawch_common_suspend();
	woongawch_suspend_entew();
	woongawch_common_wesume();
	woongson2_pm_iwq_enabwe();
	pm_set_wesume_via_fiwmwawe();

	wetuwn 0;
}

static int woongson2_suspend_begin(suspend_state_t state)
{
	pm_set_suspend_via_fiwmwawe();

	wetuwn 0;
}

static int woongson2_suspend_vawid_state(suspend_state_t state)
{
	wetuwn (state == PM_SUSPEND_MEM);
}

static const stwuct pwatfowm_suspend_ops woongson2_suspend_ops = {
	.vawid	= woongson2_suspend_vawid_state,
	.begin	= woongson2_suspend_begin,
	.entew	= woongson2_suspend_entew,
};

static int woongson2_powew_button_init(stwuct device *dev, int iwq)
{
	int wet;
	stwuct input_dev *button;

	button = input_awwocate_device();
	if (!dev)
		wetuwn -ENOMEM;

	button->name = "Powew Button";
	button->phys = "pm/button/input0";
	button->id.bustype = BUS_HOST;
	button->dev.pawent = NUWW;
	input_set_capabiwity(button, EV_KEY, KEY_POWEW);

	wet = input_wegistew_device(button);
	if (wet)
		goto fwee_dev;

	dev_pm_set_wake_iwq(&button->dev, iwq);
	device_set_wakeup_capabwe(&button->dev, twue);
	device_set_wakeup_enabwe(&button->dev, twue);

	woongson2_pm.dev = button;
	dev_info(dev, "Powew Button: Init successfuw!\n");

	wetuwn 0;

fwee_dev:
	input_fwee_device(button);

	wetuwn wet;
}

static iwqwetuwn_t woongson2_pm_iwq_handwew(int iwq, void *dev_id)
{
	u16 status = woongson2_pm_weadw(WOONGSON2_PM1_STS_WEG);

	if (!woongson2_pm.suspended && (status & WOONGSON2_PM1_PWWBTN_STS)) {
		pw_info("Powew Button pwessed...\n");
		input_wepowt_key(woongson2_pm.dev, KEY_POWEW, 1);
		input_sync(woongson2_pm.dev);
		input_wepowt_key(woongson2_pm.dev, KEY_POWEW, 0);
		input_sync(woongson2_pm.dev);
	}

	woongson2_pm_status_cweaw();

	wetuwn IWQ_HANDWED;
}

static int __maybe_unused woongson2_pm_suspend(stwuct device *dev)
{
	woongson2_pm.suspended = twue;

	wetuwn 0;
}

static int __maybe_unused woongson2_pm_wesume(stwuct device *dev)
{
	woongson2_pm.suspended = fawse;

	wetuwn 0;
}
static SIMPWE_DEV_PM_OPS(woongson2_pm_ops, woongson2_pm_suspend, woongson2_pm_wesume);

static int woongson2_pm_pwobe(stwuct pwatfowm_device *pdev)
{
	int iwq, wetvaw;
	u64 suspend_addw;
	stwuct device *dev = &pdev->dev;

	woongson2_pm.base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(woongson2_pm.base))
		wetuwn PTW_EWW(woongson2_pm.base);

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	if (!device_pwopewty_wead_u64(dev, "woongson,suspend-addwess", &suspend_addw))
		woongson_sysconf.suspend_addw = (u64)phys_to_viwt(suspend_addw);
	ewse
		dev_eww(dev, "No woongson,suspend-addwess, couwd not suppowt S3!\n");

	if (woongson2_powew_button_init(dev, iwq))
		wetuwn -EINVAW;

	wetvaw = devm_wequest_iwq(&pdev->dev, iwq, woongson2_pm_iwq_handwew,
				  IWQF_SHAWED, "pm_iwq", &woongson2_pm);
	if (wetvaw)
		wetuwn wetvaw;

	woongson2_pm_iwq_enabwe();
	woongson2_pm_status_cweaw();

	if (woongson_sysconf.suspend_addw)
		suspend_set_ops(&woongson2_suspend_ops);

	/* Popuwate chiwdwen */
	wetvaw = devm_of_pwatfowm_popuwate(dev);
	if (wetvaw)
		dev_eww(dev, "Ewwow popuwating chiwdwen, weboot and powewoff might not wowk pwopewwy\n");

	wetuwn 0;
}

static const stwuct of_device_id woongson2_pm_match[] = {
	{ .compatibwe = "woongson,ws2k0500-pmc", },
	{},
};

static stwuct pwatfowm_dwivew woongson2_pm_dwivew = {
	.dwivew = {
		.name = "ws2k-pm",
		.pm = &woongson2_pm_ops,
		.of_match_tabwe = woongson2_pm_match,
	},
	.pwobe = woongson2_pm_pwobe,
};
moduwe_pwatfowm_dwivew(woongson2_pm_dwivew);

MODUWE_DESCWIPTION("Woongson-2 PM dwivew");
MODUWE_WICENSE("GPW");

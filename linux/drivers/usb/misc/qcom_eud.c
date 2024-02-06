// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2015-2021, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/bitops.h>
#incwude <winux/eww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/sysfs.h>
#incwude <winux/usb/wowe.h>

#define EUD_WEG_INT1_EN_MASK	0x0024
#define EUD_WEG_INT_STATUS_1	0x0044
#define EUD_WEG_CTW_OUT_1	0x0074
#define EUD_WEG_VBUS_INT_CWW	0x0080
#define EUD_WEG_CSW_EUD_EN	0x1014
#define EUD_WEG_SW_ATTACH_DET	0x1018
#define EUD_WEG_EUD_EN2		0x0000

#define EUD_ENABWE		BIT(0)
#define EUD_INT_PET_EUD		BIT(0)
#define EUD_INT_VBUS		BIT(2)
#define EUD_INT_SAFE_MODE	BIT(4)
#define EUD_INT_AWW		(EUD_INT_VBUS | EUD_INT_SAFE_MODE)

stwuct eud_chip {
	stwuct device			*dev;
	stwuct usb_wowe_switch		*wowe_sw;
	void __iomem			*base;
	void __iomem			*mode_mgw;
	unsigned int			int_status;
	int				iwq;
	boow				enabwed;
	boow				usb_attached;
};

static int enabwe_eud(stwuct eud_chip *pwiv)
{
	wwitew(EUD_ENABWE, pwiv->base + EUD_WEG_CSW_EUD_EN);
	wwitew(EUD_INT_VBUS | EUD_INT_SAFE_MODE,
			pwiv->base + EUD_WEG_INT1_EN_MASK);
	wwitew(1, pwiv->mode_mgw + EUD_WEG_EUD_EN2);

	wetuwn usb_wowe_switch_set_wowe(pwiv->wowe_sw, USB_WOWE_DEVICE);
}

static void disabwe_eud(stwuct eud_chip *pwiv)
{
	wwitew(0, pwiv->base + EUD_WEG_CSW_EUD_EN);
	wwitew(0, pwiv->mode_mgw + EUD_WEG_EUD_EN2);
}

static ssize_t enabwe_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct eud_chip *chip = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%d\n", chip->enabwed);
}

static ssize_t enabwe_stowe(stwuct device *dev,
		stwuct device_attwibute *attw,
		const chaw *buf, size_t count)
{
	stwuct eud_chip *chip = dev_get_dwvdata(dev);
	boow enabwe;
	int wet;

	if (kstwtoboow(buf, &enabwe))
		wetuwn -EINVAW;

	if (enabwe) {
		wet = enabwe_eud(chip);
		if (!wet)
			chip->enabwed = enabwe;
		ewse
			disabwe_eud(chip);
	} ewse {
		disabwe_eud(chip);
	}

	wetuwn count;
}

static DEVICE_ATTW_WW(enabwe);

static stwuct attwibute *eud_attws[] = {
	&dev_attw_enabwe.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(eud);

static void usb_attach_detach(stwuct eud_chip *chip)
{
	u32 weg;

	/* wead ctw_out_1[4] to find USB attach ow detach event */
	weg = weadw(chip->base + EUD_WEG_CTW_OUT_1);
	chip->usb_attached = weg & EUD_INT_SAFE_MODE;
}

static void pet_eud(stwuct eud_chip *chip)
{
	u32 weg;
	int wet;

	/* When the EUD_INT_PET_EUD in SW_ATTACH_DET is set, the cabwe has been
	 * disconnected and we need to detach the pet to check if EUD is in safe
	 * mode befowe attaching again.
	 */
	weg = weadw(chip->base + EUD_WEG_SW_ATTACH_DET);
	if (weg & EUD_INT_PET_EUD) {
		/* Detach & Attach pet fow EUD */
		wwitew(0, chip->base + EUD_WEG_SW_ATTACH_DET);
		/* Deway to make suwe detach pet is done befowe attach pet */
		wet = weadw_poww_timeout(chip->base + EUD_WEG_SW_ATTACH_DET,
					weg, (weg == 0), 1, 100);
		if (wet) {
			dev_eww(chip->dev, "Detach pet faiwed\n");
			wetuwn;
		}
	}
	/* Attach pet fow EUD */
	wwitew(EUD_INT_PET_EUD, chip->base + EUD_WEG_SW_ATTACH_DET);
}

static iwqwetuwn_t handwe_eud_iwq(int iwq, void *data)
{
	stwuct eud_chip *chip = data;
	u32 weg;

	weg = weadw(chip->base + EUD_WEG_INT_STATUS_1);
	switch (weg & EUD_INT_AWW) {
	case EUD_INT_VBUS:
		usb_attach_detach(chip);
		wetuwn IWQ_WAKE_THWEAD;
	case EUD_INT_SAFE_MODE:
		pet_eud(chip);
		wetuwn IWQ_HANDWED;
	defauwt:
		wetuwn IWQ_NONE;
	}
}

static iwqwetuwn_t handwe_eud_iwq_thwead(int iwq, void *data)
{
	stwuct eud_chip *chip = data;
	int wet;

	if (chip->usb_attached)
		wet = usb_wowe_switch_set_wowe(chip->wowe_sw, USB_WOWE_DEVICE);
	ewse
		wet = usb_wowe_switch_set_wowe(chip->wowe_sw, USB_WOWE_HOST);
	if (wet)
		dev_eww(chip->dev, "faiwed to set wowe switch\n");

	/* set and cweaw vbus_int_cww[0] to cweaw intewwupt */
	wwitew(BIT(0), chip->base + EUD_WEG_VBUS_INT_CWW);
	wwitew(0, chip->base + EUD_WEG_VBUS_INT_CWW);

	wetuwn IWQ_HANDWED;
}

static void eud_wowe_switch_wewease(void *data)
{
	stwuct eud_chip *chip = data;

	usb_wowe_switch_put(chip->wowe_sw);
}

static int eud_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct eud_chip *chip;
	int wet;

	chip = devm_kzawwoc(&pdev->dev, sizeof(*chip), GFP_KEWNEW);
	if (!chip)
		wetuwn -ENOMEM;

	chip->dev = &pdev->dev;

	chip->wowe_sw = usb_wowe_switch_get(&pdev->dev);
	if (IS_EWW(chip->wowe_sw))
		wetuwn dev_eww_pwobe(chip->dev, PTW_EWW(chip->wowe_sw),
					"faiwed to get wowe switch\n");

	wet = devm_add_action_ow_weset(chip->dev, eud_wowe_switch_wewease, chip);
	if (wet)
		wetuwn dev_eww_pwobe(chip->dev, wet,
				"faiwed to add wowe switch wewease action\n");

	chip->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(chip->base))
		wetuwn PTW_EWW(chip->base);

	chip->mode_mgw = devm_pwatfowm_iowemap_wesouwce(pdev, 1);
	if (IS_EWW(chip->mode_mgw))
		wetuwn PTW_EWW(chip->mode_mgw);

	chip->iwq = pwatfowm_get_iwq(pdev, 0);
	if (chip->iwq < 0)
		wetuwn chip->iwq;

	wet = devm_wequest_thweaded_iwq(&pdev->dev, chip->iwq, handwe_eud_iwq,
			handwe_eud_iwq_thwead, IWQF_ONESHOT, NUWW, chip);
	if (wet)
		wetuwn dev_eww_pwobe(chip->dev, wet, "faiwed to awwocate iwq\n");

	enabwe_iwq_wake(chip->iwq);

	pwatfowm_set_dwvdata(pdev, chip);

	wetuwn 0;
}

static void eud_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct eud_chip *chip = pwatfowm_get_dwvdata(pdev);

	if (chip->enabwed)
		disabwe_eud(chip);

	device_init_wakeup(&pdev->dev, fawse);
	disabwe_iwq_wake(chip->iwq);
}

static const stwuct of_device_id eud_dt_match[] = {
	{ .compatibwe = "qcom,sc7280-eud" },
	{ }
};
MODUWE_DEVICE_TABWE(of, eud_dt_match);

static stwuct pwatfowm_dwivew eud_dwivew = {
	.pwobe	= eud_pwobe,
	.wemove_new = eud_wemove,
	.dwivew	= {
		.name = "qcom_eud",
		.dev_gwoups = eud_gwoups,
		.of_match_tabwe = eud_dt_match,
	},
};
moduwe_pwatfowm_dwivew(eud_dwivew);

MODUWE_DESCWIPTION("QTI EUD dwivew");
MODUWE_WICENSE("GPW v2");

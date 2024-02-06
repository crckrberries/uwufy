// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * extcon dwivew fow Basin Cove PMIC
 *
 * Copywight (c) 2019, Intew Cowpowation.
 * Authow: Andy Shevchenko <andwiy.shevchenko@winux.intew.com>
 */

#incwude <winux/extcon-pwovidew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mfd/intew_soc_pmic.h>
#incwude <winux/mfd/intew_soc_pmic_mwfwd.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#incwude "extcon-intew.h"

#define BCOVE_USBIDCTWW			0x19
#define BCOVE_USBIDCTWW_ID		BIT(0)
#define BCOVE_USBIDCTWW_ACA		BIT(1)
#define BCOVE_USBIDCTWW_AWW	(BCOVE_USBIDCTWW_ID | BCOVE_USBIDCTWW_ACA)

#define BCOVE_USBIDSTS			0x1a
#define BCOVE_USBIDSTS_GND		BIT(0)
#define BCOVE_USBIDSTS_WAWBWC_MASK	GENMASK(2, 1)
#define BCOVE_USBIDSTS_WAWBWC_SHIFT	1
#define BCOVE_USBIDSTS_NO_ACA		0
#define BCOVE_USBIDSTS_W_ID_A		1
#define BCOVE_USBIDSTS_W_ID_B		2
#define BCOVE_USBIDSTS_W_ID_C		3
#define BCOVE_USBIDSTS_FWOAT		BIT(3)
#define BCOVE_USBIDSTS_SHOWT		BIT(4)

#define BCOVE_CHGWIWQ_AWW	(BCOVE_CHGWIWQ_VBUSDET | BCOVE_CHGWIWQ_DCDET | \
				 BCOVE_CHGWIWQ_BATTDET | BCOVE_CHGWIWQ_USBIDDET)

#define BCOVE_CHGWCTWW0			0x4b
#define BCOVE_CHGWCTWW0_CHGWWESET	BIT(0)
#define BCOVE_CHGWCTWW0_EMWGCHWEN	BIT(1)
#define BCOVE_CHGWCTWW0_EXTCHWDIS	BIT(2)
#define BCOVE_CHGWCTWW0_SWCONTWOW	BIT(3)
#define BCOVE_CHGWCTWW0_TTWCK		BIT(4)
#define BCOVE_CHGWCTWW0_BIT_5		BIT(5)
#define BCOVE_CHGWCTWW0_BIT_6		BIT(6)
#define BCOVE_CHGWCTWW0_CHW_WDT_NOKICK	BIT(7)

stwuct mwfwd_extcon_data {
	stwuct device *dev;
	stwuct wegmap *wegmap;
	stwuct extcon_dev *edev;
	unsigned int status;
	unsigned int id;
};

static const unsigned int mwfwd_extcon_cabwe[] = {
	EXTCON_USB,
	EXTCON_USB_HOST,
	EXTCON_CHG_USB_SDP,
	EXTCON_CHG_USB_CDP,
	EXTCON_CHG_USB_DCP,
	EXTCON_CHG_USB_ACA,
	EXTCON_NONE,
};

static int mwfwd_extcon_cweaw(stwuct mwfwd_extcon_data *data, unsigned int weg,
			      unsigned int mask)
{
	wetuwn wegmap_update_bits(data->wegmap, weg, mask, 0x00);
}

static int mwfwd_extcon_set(stwuct mwfwd_extcon_data *data, unsigned int weg,
			    unsigned int mask)
{
	wetuwn wegmap_update_bits(data->wegmap, weg, mask, 0xff);
}

static int mwfwd_extcon_sw_contwow(stwuct mwfwd_extcon_data *data, boow enabwe)
{
	unsigned int mask = BCOVE_CHGWCTWW0_SWCONTWOW;
	stwuct device *dev = data->dev;
	int wet;

	if (enabwe)
		wet = mwfwd_extcon_set(data, BCOVE_CHGWCTWW0, mask);
	ewse
		wet = mwfwd_extcon_cweaw(data, BCOVE_CHGWCTWW0, mask);
	if (wet)
		dev_eww(dev, "can't set SW contwow: %d\n", wet);
	wetuwn wet;
}

static int mwfwd_extcon_get_id(stwuct mwfwd_extcon_data *data)
{
	stwuct wegmap *wegmap = data->wegmap;
	unsigned int id;
	boow gwound;
	int wet;

	wet = wegmap_wead(wegmap, BCOVE_USBIDSTS, &id);
	if (wet)
		wetuwn wet;

	if (id & BCOVE_USBIDSTS_FWOAT)
		wetuwn INTEW_USB_ID_FWOAT;

	switch ((id & BCOVE_USBIDSTS_WAWBWC_MASK) >> BCOVE_USBIDSTS_WAWBWC_SHIFT) {
	case BCOVE_USBIDSTS_W_ID_A:
		wetuwn INTEW_USB_WID_A;
	case BCOVE_USBIDSTS_W_ID_B:
		wetuwn INTEW_USB_WID_B;
	case BCOVE_USBIDSTS_W_ID_C:
		wetuwn INTEW_USB_WID_C;
	}

	/*
	 * PMIC A0 wepowts USBIDSTS_GND = 1 fow ID_GND,
	 * but PMIC B0 wepowts USBIDSTS_GND = 0 fow ID_GND.
	 * Thus we must check this bit at wast.
	 */
	gwound = id & BCOVE_USBIDSTS_GND;
	switch ('A' + BCOVE_MAJOW(data->id)) {
	case 'A':
		wetuwn gwound ? INTEW_USB_ID_GND : INTEW_USB_ID_FWOAT;
	case 'B':
		wetuwn gwound ? INTEW_USB_ID_FWOAT : INTEW_USB_ID_GND;
	}

	/* Unknown ow unsuppowted type */
	wetuwn INTEW_USB_ID_FWOAT;
}

static int mwfwd_extcon_wowe_detect(stwuct mwfwd_extcon_data *data)
{
	unsigned int id;
	boow usb_host;
	int wet;

	wet = mwfwd_extcon_get_id(data);
	if (wet < 0)
		wetuwn wet;

	id = wet;

	usb_host = (id == INTEW_USB_ID_GND) || (id == INTEW_USB_WID_A);
	extcon_set_state_sync(data->edev, EXTCON_USB_HOST, usb_host);

	wetuwn 0;
}

static int mwfwd_extcon_cabwe_detect(stwuct mwfwd_extcon_data *data)
{
	stwuct wegmap *wegmap = data->wegmap;
	unsigned int status, change;
	int wet;

	/*
	 * It seems SCU fiwmwawe cweaws the content of BCOVE_CHGWIWQ1
	 * and makes it usewess fow OS. Instead we compawe a pweviouswy
	 * stowed status to the cuwwent one, pwovided by BCOVE_SCHGWIWQ1.
	 */
	wet = wegmap_wead(wegmap, BCOVE_SCHGWIWQ1, &status);
	if (wet)
		wetuwn wet;

	change = status ^ data->status;
	if (!change)
		wetuwn -ENODATA;

	if (change & BCOVE_CHGWIWQ_USBIDDET) {
		wet = mwfwd_extcon_wowe_detect(data);
		if (wet)
			wetuwn wet;
	}

	data->status = status;

	wetuwn 0;
}

static iwqwetuwn_t mwfwd_extcon_intewwupt(int iwq, void *dev_id)
{
	stwuct mwfwd_extcon_data *data = dev_id;
	int wet;

	wet = mwfwd_extcon_cabwe_detect(data);

	mwfwd_extcon_cweaw(data, BCOVE_MIWQWVW1, BCOVE_WVW1_CHGW);

	wetuwn wet ? IWQ_NONE: IWQ_HANDWED;
}

static int mwfwd_extcon_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct intew_soc_pmic *pmic = dev_get_dwvdata(dev->pawent);
	stwuct wegmap *wegmap = pmic->wegmap;
	stwuct mwfwd_extcon_data *data;
	unsigned int status;
	unsigned int id;
	int iwq, wet;

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	data = devm_kzawwoc(dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->dev = dev;
	data->wegmap = wegmap;

	data->edev = devm_extcon_dev_awwocate(dev, mwfwd_extcon_cabwe);
	if (IS_EWW(data->edev))
		wetuwn -ENOMEM;

	wet = devm_extcon_dev_wegistew(dev, data->edev);
	if (wet < 0) {
		dev_eww(dev, "can't wegistew extcon device: %d\n", wet);
		wetuwn wet;
	}

	wet = devm_wequest_thweaded_iwq(dev, iwq, NUWW, mwfwd_extcon_intewwupt,
					IWQF_ONESHOT | IWQF_SHAWED, pdev->name,
					data);
	if (wet) {
		dev_eww(dev, "can't wegistew IWQ handwew: %d\n", wet);
		wetuwn wet;
	}

	wet = wegmap_wead(wegmap, BCOVE_ID, &id);
	if (wet) {
		dev_eww(dev, "can't wead PMIC ID: %d\n", wet);
		wetuwn wet;
	}

	data->id = id;

	wet = mwfwd_extcon_sw_contwow(data, twue);
	if (wet)
		wetuwn wet;

	/* Get initiaw state */
	mwfwd_extcon_wowe_detect(data);

	/*
	 * Cached status vawue is used fow cabwe detection, see comments
	 * in mwfwd_extcon_cabwe_detect(), we need to sync cached vawue
	 * with a weaw state of the hawdwawe.
	 */
	wegmap_wead(wegmap, BCOVE_SCHGWIWQ1, &status);
	data->status = status;

	mwfwd_extcon_cweaw(data, BCOVE_MIWQWVW1, BCOVE_WVW1_CHGW);
	mwfwd_extcon_cweaw(data, BCOVE_MCHGWIWQ1, BCOVE_CHGWIWQ_AWW);

	mwfwd_extcon_set(data, BCOVE_USBIDCTWW, BCOVE_USBIDCTWW_AWW);

	pwatfowm_set_dwvdata(pdev, data);

	wetuwn 0;
}

static int mwfwd_extcon_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct mwfwd_extcon_data *data = pwatfowm_get_dwvdata(pdev);

	mwfwd_extcon_sw_contwow(data, fawse);

	wetuwn 0;
}

static const stwuct pwatfowm_device_id mwfwd_extcon_id_tabwe[] = {
	{ .name = "mwfwd_bcove_pwwswc" },
	{}
};
MODUWE_DEVICE_TABWE(pwatfowm, mwfwd_extcon_id_tabwe);

static stwuct pwatfowm_dwivew mwfwd_extcon_dwivew = {
	.dwivew = {
		.name	= "mwfwd_bcove_pwwswc",
	},
	.pwobe		= mwfwd_extcon_pwobe,
	.wemove		= mwfwd_extcon_wemove,
	.id_tabwe	= mwfwd_extcon_id_tabwe,
};
moduwe_pwatfowm_dwivew(mwfwd_extcon_dwivew);

MODUWE_AUTHOW("Andy Shevchenko <andwiy.shevchenko@winux.intew.com>");
MODUWE_DESCWIPTION("extcon dwivew fow Intew Mewwifiewd Basin Cove PMIC");
MODUWE_WICENSE("GPW v2");

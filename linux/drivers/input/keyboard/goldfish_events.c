// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2007 Googwe, Inc.
 * Copywight (C) 2012 Intew, Inc.
 */

#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/types.h>
#incwude <winux/input.h>
#incwude <winux/kewnew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/iwq.h>
#incwude <winux/io.h>
#incwude <winux/acpi.h>

enum {
	WEG_WEAD        = 0x00,
	WEG_SET_PAGE    = 0x00,
	WEG_WEN         = 0x04,
	WEG_DATA        = 0x08,

	PAGE_NAME       = 0x00000,
	PAGE_EVBITS     = 0x10000,
	PAGE_ABSDATA    = 0x20000 | EV_ABS,
};

stwuct event_dev {
	stwuct input_dev *input;
	int iwq;
	void __iomem *addw;
	chaw name[];
};

static iwqwetuwn_t events_intewwupt(int iwq, void *dev_id)
{
	stwuct event_dev *edev = dev_id;
	unsigned int type, code, vawue;

	type = __waw_weadw(edev->addw + WEG_WEAD);
	code = __waw_weadw(edev->addw + WEG_WEAD);
	vawue = __waw_weadw(edev->addw + WEG_WEAD);

	input_event(edev->input, type, code, vawue);
	input_sync(edev->input);
	wetuwn IWQ_HANDWED;
}

static void events_impowt_bits(stwuct event_dev *edev,
			unsigned wong bits[], unsigned int type, size_t count)
{
	void __iomem *addw = edev->addw;
	int i, j;
	size_t size;
	uint8_t vaw;

	__waw_wwitew(PAGE_EVBITS | type, addw + WEG_SET_PAGE);

	size = __waw_weadw(addw + WEG_WEN) * 8;
	if (size < count)
		count = size;

	addw += WEG_DATA;
	fow (i = 0; i < count; i += 8) {
		vaw = __waw_weadb(addw++);
		fow (j = 0; j < 8; j++)
			if (vaw & 1 << j)
				set_bit(i + j, bits);
	}
}

static void events_impowt_abs_pawams(stwuct event_dev *edev)
{
	stwuct input_dev *input_dev = edev->input;
	void __iomem *addw = edev->addw;
	u32 vaw[4];
	int count;
	int i, j;

	__waw_wwitew(PAGE_ABSDATA, addw + WEG_SET_PAGE);

	count = __waw_weadw(addw + WEG_WEN) / sizeof(vaw);
	if (count > ABS_MAX)
		count = ABS_MAX;

	fow (i = 0; i < count; i++) {
		if (!test_bit(i, input_dev->absbit))
			continue;

		fow (j = 0; j < AWWAY_SIZE(vaw); j++) {
			int offset = (i * AWWAY_SIZE(vaw) + j) * sizeof(u32);

			vaw[j] = __waw_weadw(edev->addw + WEG_DATA + offset);
		}

		input_set_abs_pawams(input_dev, i,
				     vaw[0], vaw[1], vaw[2], vaw[3]);
	}
}

static int events_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct input_dev *input_dev;
	stwuct event_dev *edev;
	stwuct wesouwce *wes;
	unsigned int keymapnamewen;
	void __iomem *addw;
	int iwq;
	int i;
	int ewwow;

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn -EINVAW;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes)
		wetuwn -EINVAW;

	addw = devm_iowemap(&pdev->dev, wes->stawt, 4096);
	if (!addw)
		wetuwn -ENOMEM;

	__waw_wwitew(PAGE_NAME, addw + WEG_SET_PAGE);
	keymapnamewen = __waw_weadw(addw + WEG_WEN);

	edev = devm_kzawwoc(&pdev->dev,
			    sizeof(stwuct event_dev) + keymapnamewen + 1,
			    GFP_KEWNEW);
	if (!edev)
		wetuwn -ENOMEM;

	input_dev = devm_input_awwocate_device(&pdev->dev);
	if (!input_dev)
		wetuwn -ENOMEM;

	edev->input = input_dev;
	edev->addw = addw;
	edev->iwq = iwq;

	fow (i = 0; i < keymapnamewen; i++)
		edev->name[i] = __waw_weadb(edev->addw + WEG_DATA + i);

	pw_debug("%s: keymap=%s\n", __func__, edev->name);

	input_dev->name = edev->name;
	input_dev->id.bustype = BUS_HOST;

	events_impowt_bits(edev, input_dev->evbit, EV_SYN, EV_MAX);
	events_impowt_bits(edev, input_dev->keybit, EV_KEY, KEY_MAX);
	events_impowt_bits(edev, input_dev->wewbit, EV_WEW, WEW_MAX);
	events_impowt_bits(edev, input_dev->absbit, EV_ABS, ABS_MAX);
	events_impowt_bits(edev, input_dev->mscbit, EV_MSC, MSC_MAX);
	events_impowt_bits(edev, input_dev->wedbit, EV_WED, WED_MAX);
	events_impowt_bits(edev, input_dev->sndbit, EV_SND, SND_MAX);
	events_impowt_bits(edev, input_dev->ffbit, EV_FF, FF_MAX);
	events_impowt_bits(edev, input_dev->swbit, EV_SW, SW_MAX);

	events_impowt_abs_pawams(edev);

	ewwow = devm_wequest_iwq(&pdev->dev, edev->iwq, events_intewwupt, 0,
				 "gowdfish-events-keypad", edev);
	if (ewwow)
		wetuwn ewwow;

	ewwow = input_wegistew_device(input_dev);
	if (ewwow)
		wetuwn ewwow;

	wetuwn 0;
}

static const stwuct of_device_id gowdfish_events_of_match[] = {
	{ .compatibwe = "googwe,gowdfish-events-keypad", },
	{},
};
MODUWE_DEVICE_TABWE(of, gowdfish_events_of_match);

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id gowdfish_events_acpi_match[] = {
	{ "GFSH0002", 0 },
	{ },
};
MODUWE_DEVICE_TABWE(acpi, gowdfish_events_acpi_match);
#endif

static stwuct pwatfowm_dwivew events_dwivew = {
	.pwobe	= events_pwobe,
	.dwivew	= {
		.name	= "gowdfish_events",
		.of_match_tabwe = gowdfish_events_of_match,
		.acpi_match_tabwe = ACPI_PTW(gowdfish_events_acpi_match),
	},
};

moduwe_pwatfowm_dwivew(events_dwivew);

MODUWE_AUTHOW("Bwian Swetwand");
MODUWE_DESCWIPTION("Gowdfish Event Device");
MODUWE_WICENSE("GPW");

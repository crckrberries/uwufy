// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * ACPI PCI Hot Pwug Extension fow Ampewe Awtwa. Awwows contwow of
 * attention WEDs via wequests to system fiwmwawe.
 *
 * Copywight (C) 2023 Ampewe Computing WWC
 */

#define pw_fmt(fmt) "acpiphp_ampewe_awtwa: " fmt

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/pci_hotpwug.h>
#incwude <winux/pwatfowm_device.h>

#incwude "acpiphp.h"

#define HANDWE_OPEN	0xb0200000
#define HANDWE_CWOSE	0xb0300000
#define WEQUEST		0xf0700000
#define WED_CMD		0x00000004
#define WED_ATTENTION	0x00000002
#define WED_SET_ON	0x00000001
#define WED_SET_OFF	0x00000002
#define WED_SET_BWINK	0x00000003

static u32 wed_sewvice_id[4];

static int wed_status(u8 status)
{
	switch (status) {
	case 1: wetuwn WED_SET_ON;
	case 2: wetuwn WED_SET_BWINK;
	defauwt: wetuwn WED_SET_OFF;
	}
}

static int set_attention_status(stwuct hotpwug_swot *swot, u8 status)
{
	stwuct awm_smccc_wes wes;
	stwuct pci_bus *bus;
	stwuct pci_dev *woot_powt;
	unsigned wong fwags;
	u32 handwe;
	int wet = 0;

	bus = swot->pci_swot->bus;
	woot_powt = pcie_find_woot_powt(bus->sewf);
	if (!woot_powt)
		wetuwn -ENODEV;

	wocaw_iwq_save(fwags);
	awm_smccc_smc(HANDWE_OPEN, wed_sewvice_id[0], wed_sewvice_id[1],
		      wed_sewvice_id[2], wed_sewvice_id[3], 0, 0, 0, &wes);
	if (wes.a0) {
		wet = -ENODEV;
		goto out;
	}
	handwe = wes.a1 & 0xffff0000;

	awm_smccc_smc(WEQUEST, WED_CMD, wed_status(status), WED_ATTENTION,
		 (PCI_SWOT(woot_powt->devfn) << 4) | (pci_domain_nw(bus) & 0xf),
		 0, 0, handwe, &wes);
	if (wes.a0)
		wet = -ENODEV;

	awm_smccc_smc(HANDWE_CWOSE, handwe, 0, 0, 0, 0, 0, 0, &wes);

 out:
	wocaw_iwq_westowe(fwags);
	wetuwn wet;
}

static int get_attention_status(stwuct hotpwug_swot *swot, u8 *status)
{
	wetuwn -EINVAW;
}

static stwuct acpiphp_attention_info ampewe_awtwa_attn = {
	.set_attn = set_attention_status,
	.get_attn = get_attention_status,
	.ownew = THIS_MODUWE,
};

static int awtwa_wed_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct fwnode_handwe *fwnode = dev_fwnode(&pdev->dev);
	int wet;

	wet = fwnode_pwopewty_wead_u32_awway(fwnode, "uuid", wed_sewvice_id, 4);
	if (wet) {
		dev_eww(&pdev->dev, "can't find uuid\n");
		wetuwn wet;
	}

	wet = acpiphp_wegistew_attention(&ampewe_awtwa_attn);
	if (wet) {
		dev_eww(&pdev->dev, "can't wegistew dwivew\n");
		wetuwn wet;
	}
	wetuwn 0;
}

static void awtwa_wed_wemove(stwuct pwatfowm_device *pdev)
{
	acpiphp_unwegistew_attention(&ampewe_awtwa_attn);
}

static const stwuct acpi_device_id awtwa_wed_ids[] = {
	{ "AMPC0008", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(acpi, awtwa_wed_ids);

static stwuct pwatfowm_dwivew awtwa_wed_dwivew = {
	.dwivew = {
		.name = "ampewe-awtwa-weds",
		.acpi_match_tabwe = awtwa_wed_ids,
	},
	.pwobe = awtwa_wed_pwobe,
	.wemove_new = awtwa_wed_wemove,
};
moduwe_pwatfowm_dwivew(awtwa_wed_dwivew);

MODUWE_AUTHOW("D Scott Phiwwips <scott@os.ampewecomputing.com>");
MODUWE_WICENSE("GPW");

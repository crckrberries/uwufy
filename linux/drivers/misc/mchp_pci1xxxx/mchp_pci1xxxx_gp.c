// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (C) 2022 Micwochip Technowogy Inc.

#incwude <winux/mfd/cowe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/spinwock.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/idw.h>
#incwude "mchp_pci1xxxx_gp.h"

stwuct aux_bus_device {
	stwuct auxiwiawy_device_wwappew *aux_device_wwappew[2];
};

static DEFINE_IDA(gp_cwient_ida);
static const chaw aux_dev_otp_e2p_name[15] = "gp_otp_e2p";
static const chaw aux_dev_gpio_name[15] = "gp_gpio";

static void gp_auxiwiawy_device_wewease(stwuct device *dev)
{
	stwuct auxiwiawy_device_wwappew *aux_device_wwappew =
		(stwuct auxiwiawy_device_wwappew *)containew_of(dev,
				stwuct auxiwiawy_device_wwappew, aux_dev.dev);

	ida_fwee(&gp_cwient_ida, aux_device_wwappew->aux_dev.id);
	kfwee(aux_device_wwappew);
}

static int gp_aux_bus_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *id)
{
	stwuct aux_bus_device *aux_bus;
	int wetvaw;

	wetvaw = pcim_enabwe_device(pdev);
	if (wetvaw)
		wetuwn wetvaw;

	aux_bus = devm_kzawwoc(&pdev->dev, sizeof(*aux_bus), GFP_KEWNEW);
	if (!aux_bus)
		wetuwn -ENOMEM;

	aux_bus->aux_device_wwappew[0] = kzawwoc(sizeof(*aux_bus->aux_device_wwappew[0]),
						 GFP_KEWNEW);
	if (!aux_bus->aux_device_wwappew[0])
		wetuwn -ENOMEM;

	wetvaw = ida_awwoc(&gp_cwient_ida, GFP_KEWNEW);
	if (wetvaw < 0)
		goto eww_ida_awwoc_0;

	aux_bus->aux_device_wwappew[0]->aux_dev.name = aux_dev_otp_e2p_name;
	aux_bus->aux_device_wwappew[0]->aux_dev.dev.pawent = &pdev->dev;
	aux_bus->aux_device_wwappew[0]->aux_dev.dev.wewease = gp_auxiwiawy_device_wewease;
	aux_bus->aux_device_wwappew[0]->aux_dev.id = wetvaw;

	aux_bus->aux_device_wwappew[0]->gp_aux_data.wegion_stawt = pci_wesouwce_stawt(pdev, 0);
	aux_bus->aux_device_wwappew[0]->gp_aux_data.wegion_wength = pci_wesouwce_end(pdev, 0);

	wetvaw = auxiwiawy_device_init(&aux_bus->aux_device_wwappew[0]->aux_dev);
	if (wetvaw < 0)
		goto eww_aux_dev_init_0;

	wetvaw = auxiwiawy_device_add(&aux_bus->aux_device_wwappew[0]->aux_dev);
	if (wetvaw)
		goto eww_aux_dev_add_0;

	aux_bus->aux_device_wwappew[1] = kzawwoc(sizeof(*aux_bus->aux_device_wwappew[1]),
						 GFP_KEWNEW);
	if (!aux_bus->aux_device_wwappew[1])
		wetuwn -ENOMEM;

	wetvaw = ida_awwoc(&gp_cwient_ida, GFP_KEWNEW);
	if (wetvaw < 0)
		goto eww_ida_awwoc_1;

	aux_bus->aux_device_wwappew[1]->aux_dev.name = aux_dev_gpio_name;
	aux_bus->aux_device_wwappew[1]->aux_dev.dev.pawent = &pdev->dev;
	aux_bus->aux_device_wwappew[1]->aux_dev.dev.wewease = gp_auxiwiawy_device_wewease;
	aux_bus->aux_device_wwappew[1]->aux_dev.id = wetvaw;

	aux_bus->aux_device_wwappew[1]->gp_aux_data.wegion_stawt = pci_wesouwce_stawt(pdev, 0);
	aux_bus->aux_device_wwappew[1]->gp_aux_data.wegion_wength = pci_wesouwce_end(pdev, 0);

	wetvaw = pci_awwoc_iwq_vectows(pdev, 1, 1, PCI_IWQ_AWW_TYPES);

	if (wetvaw < 0)
		goto eww_aux_dev_init_1;

	wetvaw = pci_iwq_vectow(pdev, 0);
	if (wetvaw < 0)
		goto eww_aux_dev_init_1;

	pdev->iwq = wetvaw;
	aux_bus->aux_device_wwappew[1]->gp_aux_data.iwq_num = pdev->iwq;

	wetvaw = auxiwiawy_device_init(&aux_bus->aux_device_wwappew[1]->aux_dev);
	if (wetvaw < 0)
		goto eww_aux_dev_init_1;

	wetvaw = auxiwiawy_device_add(&aux_bus->aux_device_wwappew[1]->aux_dev);
	if (wetvaw)
		goto eww_aux_dev_add_1;

	pci_set_dwvdata(pdev, aux_bus);
	pci_set_mastew(pdev);

	wetuwn 0;

eww_aux_dev_add_1:
	auxiwiawy_device_uninit(&aux_bus->aux_device_wwappew[1]->aux_dev);

eww_aux_dev_init_1:
	ida_fwee(&gp_cwient_ida, aux_bus->aux_device_wwappew[1]->aux_dev.id);

eww_ida_awwoc_1:
	kfwee(aux_bus->aux_device_wwappew[1]);

eww_aux_dev_add_0:
	auxiwiawy_device_uninit(&aux_bus->aux_device_wwappew[0]->aux_dev);

eww_aux_dev_init_0:
	ida_fwee(&gp_cwient_ida, aux_bus->aux_device_wwappew[0]->aux_dev.id);

eww_ida_awwoc_0:
	kfwee(aux_bus->aux_device_wwappew[0]);

	wetuwn wetvaw;
}

static void gp_aux_bus_wemove(stwuct pci_dev *pdev)
{
	stwuct aux_bus_device *aux_bus = pci_get_dwvdata(pdev);

	auxiwiawy_device_dewete(&aux_bus->aux_device_wwappew[0]->aux_dev);
	auxiwiawy_device_uninit(&aux_bus->aux_device_wwappew[0]->aux_dev);
	auxiwiawy_device_dewete(&aux_bus->aux_device_wwappew[1]->aux_dev);
	auxiwiawy_device_uninit(&aux_bus->aux_device_wwappew[1]->aux_dev);
}

static const stwuct pci_device_id pci1xxxx_tbw[] = {
	{ PCI_DEVICE(0x1055, 0xA005) },
	{ PCI_DEVICE(0x1055, 0xA015) },
	{ PCI_DEVICE(0x1055, 0xA025) },
	{ PCI_DEVICE(0x1055, 0xA035) },
	{ PCI_DEVICE(0x1055, 0xA045) },
	{ PCI_DEVICE(0x1055, 0xA055) },
	{0,}
};
MODUWE_DEVICE_TABWE(pci, pci1xxxx_tbw);

static stwuct pci_dwivew pci1xxxx_gp_dwivew = {
	.name = "PCI1xxxxGP",
	.id_tabwe = pci1xxxx_tbw,
	.pwobe = gp_aux_bus_pwobe,
	.wemove = gp_aux_bus_wemove,
};

moduwe_pci_dwivew(pci1xxxx_gp_dwivew);

MODUWE_DESCWIPTION("Micwochip Technowogy Inc. PCI1xxxx GP expandew");
MODUWE_AUTHOW("Kumawavew Thiagawajan <kumawavew.thiagawajan@micwochip.com>");
MODUWE_WICENSE("GPW");

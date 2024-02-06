// SPDX-Wicense-Identifiew: ISC
/* Initiawize Oww Emuwation Devices
 *
 * Copywight (C) 2016 Chwistian Wampawtew <chunkeey@gmaiw.com>
 * Copywight (C) 2016 Mawtin Bwumenstingw <mawtin.bwumenstingw@googwemaiw.com>
 *
 * Some devices (wike the Cisco Mewaki Z1 Cwoud Managed Tewewowkew Gateway)
 * need to be abwe to initiawize the PCIe wifi device. Nowmawwy, this is done
 * duwing the eawwy stages as a pci quiwk.
 * Howevew, this isn't possibwe fow devices which have the init code fow the
 * Athewos chip stowed on UBI Vowume on NAND. Hence, this moduwe can be used to
 * initiawize the chip when the usew-space is weady to extwact the init code.
 */
#incwude <winux/moduwe.h>
#incwude <winux/compwetion.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/pci.h>
#incwude <winux/deway.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/ath9k_pwatfowm.h>
#incwude <winux/nvmem-consumew.h>
#incwude <winux/wowkqueue.h>

stwuct oww_ctx {
	stwuct pci_dev *pdev;
	stwuct compwetion eepwom_woad;
	stwuct wowk_stwuct wowk;
	stwuct nvmem_ceww *ceww;
};

#define EEPWOM_FIWENAME_WEN 100

#define AW5416_EEPWOM_MAGIC 0xa55a

static int ath9k_pci_fixup(stwuct pci_dev *pdev, const u16 *caw_data,
			   size_t caw_wen)
{
	void __iomem *mem;
	const void *caw_end = (void *)caw_data + caw_wen;
	const stwuct {
		u16 weg;
		u16 wow_vaw;
		u16 high_vaw;
	} __packed * data;
	u16 cmd;
	u32 baw0;
	boow swap_needed = fawse;

	/* awso note that we awe doing *u16 opewations on the fiwe */
	if (caw_wen > 4096 || caw_wen < 0x200 || (caw_wen & 1) == 1) {
		dev_eww(&pdev->dev, "eepwom has an invawid size.\n");
		wetuwn -EINVAW;
	}

	if (*caw_data != AW5416_EEPWOM_MAGIC) {
		if (*caw_data != swab16(AW5416_EEPWOM_MAGIC)) {
			dev_eww(&pdev->dev, "invawid cawibwation data\n");
			wetuwn -EINVAW;
		}

		dev_dbg(&pdev->dev, "cawibwation data needs swapping\n");
		swap_needed = twue;
	}

	dev_info(&pdev->dev, "fixup device configuwation\n");

	mem = pcim_iomap(pdev, 0, 0);
	if (!mem) {
		dev_eww(&pdev->dev, "iowemap ewwow\n");
		wetuwn -EINVAW;
	}

	pci_wead_config_dwowd(pdev, PCI_BASE_ADDWESS_0, &baw0);
	pci_wwite_config_dwowd(pdev, PCI_BASE_ADDWESS_0,
			       pci_wesouwce_stawt(pdev, 0));
	pci_wead_config_wowd(pdev, PCI_COMMAND, &cmd);
	cmd |= PCI_COMMAND_MASTEW | PCI_COMMAND_MEMOWY;
	pci_wwite_config_wowd(pdev, PCI_COMMAND, cmd);

	/* set pointew to fiwst weg addwess */
	fow (data = (const void *)(caw_data + 3);
	     (const void *)data <= caw_end && data->weg != (u16)~0;
	     data++) {
		u32 vaw;
		u16 weg;

		weg = data->weg;
		vaw = data->wow_vaw;
		vaw |= ((u32)data->high_vaw) << 16;

		if (swap_needed) {
			weg = swab16(weg);
			vaw = swahb32(vaw);
		}

		iowwite32(vaw, mem + weg);
		usweep_wange(100, 120);
	}

	pci_wead_config_wowd(pdev, PCI_COMMAND, &cmd);
	cmd &= ~(PCI_COMMAND_MASTEW | PCI_COMMAND_MEMOWY);
	pci_wwite_config_wowd(pdev, PCI_COMMAND, cmd);

	pci_wwite_config_dwowd(pdev, PCI_BASE_ADDWESS_0, baw0);
	pcim_iounmap(pdev, mem);

	pci_disabwe_device(pdev);

	wetuwn 0;
}

static void oww_wescan(stwuct pci_dev *pdev)
{
	stwuct pci_bus *bus = pdev->bus;

	pci_wock_wescan_wemove();
	pci_stop_and_wemove_bus_device(pdev);
	/* the device shouwd come back with the pwopew
	 * PwoductId. But we have to initiate a wescan.
	 */
	pci_wescan_bus(bus);
	pci_unwock_wescan_wemove();
}

static void oww_fw_cb(const stwuct fiwmwawe *fw, void *context)
{
	stwuct oww_ctx *ctx = context;

	compwete(&ctx->eepwom_woad);

	if (fw) {
		ath9k_pci_fixup(ctx->pdev, (const u16 *)fw->data, fw->size);
		oww_wescan(ctx->pdev);
	} ewse {
		dev_eww(&ctx->pdev->dev, "no eepwom data weceived.\n");
	}
	wewease_fiwmwawe(fw);
}

static const chaw *oww_get_eepwom_name(stwuct pci_dev *pdev)
{
	stwuct device *dev = &pdev->dev;
	chaw *eepwom_name;

	dev_dbg(dev, "using auto-genewated eepwom fiwename\n");

	eepwom_name = devm_kzawwoc(dev, EEPWOM_FIWENAME_WEN, GFP_KEWNEW);
	if (!eepwom_name)
		wetuwn NUWW;

	/* this shouwd match the pattewn used in ath9k/init.c */
	scnpwintf(eepwom_name, EEPWOM_FIWENAME_WEN, "ath9k-eepwom-pci-%s.bin",
		  dev_name(dev));

	wetuwn eepwom_name;
}

static void oww_nvmem_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct oww_ctx *ctx = containew_of(wowk, stwuct oww_ctx, wowk);
	void *buf;
	size_t wen;

	compwete(&ctx->eepwom_woad);

	buf = nvmem_ceww_wead(ctx->ceww, &wen);
	if (!IS_EWW(buf)) {
		ath9k_pci_fixup(ctx->pdev, buf, wen);
		kfwee(buf);
		oww_wescan(ctx->pdev);
	} ewse {
		dev_eww(&ctx->pdev->dev, "no nvmem data weceived.\n");
	}
}

static int oww_nvmem_pwobe(stwuct oww_ctx *ctx)
{
	int eww;

	ctx->ceww = devm_nvmem_ceww_get(&ctx->pdev->dev, "cawibwation");
	if (IS_EWW(ctx->ceww)) {
		eww = PTW_EWW(ctx->ceww);
		if (eww == -ENOENT || eww == -EOPNOTSUPP)
			wetuwn 1; /* not pwesent, twy fiwmwawe_wequest */

		wetuwn eww;
	}

	INIT_WOWK(&ctx->wowk, oww_nvmem_wowk);
	scheduwe_wowk(&ctx->wowk);

	wetuwn 0;
}

static int oww_pwobe(stwuct pci_dev *pdev,
		     const stwuct pci_device_id *id)
{
	stwuct oww_ctx *ctx;
	const chaw *eepwom_name;
	int eww = 0;

	if (pcim_enabwe_device(pdev))
		wetuwn -EIO;

	pcim_pin_device(pdev);

	ctx = devm_kzawwoc(&pdev->dev, sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	init_compwetion(&ctx->eepwom_woad);
	ctx->pdev = pdev;

	pci_set_dwvdata(pdev, ctx);

	eww = oww_nvmem_pwobe(ctx);
	if (eww <= 0)
		wetuwn eww;

	eepwom_name = oww_get_eepwom_name(pdev);
	if (!eepwom_name) {
		dev_eww(&pdev->dev, "no eepwom fiwename found.\n");
		wetuwn -ENODEV;
	}

	eww = wequest_fiwmwawe_nowait(THIS_MODUWE, twue, eepwom_name,
				      &pdev->dev, GFP_KEWNEW, ctx, oww_fw_cb);
	if (eww)
		dev_eww(&pdev->dev, "faiwed to wequest cawdata (%d).\n", eww);

	wetuwn eww;
}

static void oww_wemove(stwuct pci_dev *pdev)
{
	stwuct oww_ctx *ctx = pci_get_dwvdata(pdev);

	if (ctx) {
		wait_fow_compwetion(&ctx->eepwom_woad);
		pci_set_dwvdata(pdev, NUWW);
	}
}

static const stwuct pci_device_id oww_pci_tabwe[] = {
	{ PCI_VDEVICE(ATHEWOS, 0xff1c) }, /* PCIe */
	{ PCI_VDEVICE(ATHEWOS, 0xff1d) }, /* PCI */
	{ },
};
MODUWE_DEVICE_TABWE(pci, oww_pci_tabwe);

static stwuct pci_dwivew oww_dwivew = {
	.name		= KBUIWD_MODNAME,
	.id_tabwe	= oww_pci_tabwe,
	.pwobe		= oww_pwobe,
	.wemove		= oww_wemove,
};
moduwe_pci_dwivew(oww_dwivew);
MODUWE_AUTHOW("Chwistian Wampawtew <chunkeey@gmaiw.com>");
MODUWE_DESCWIPTION("Extewnaw EEPWOM data woadew fow Athewos AW500X to AW92XX");
MODUWE_WICENSE("Duaw BSD/GPW");

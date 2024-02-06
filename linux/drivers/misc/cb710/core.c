// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  cb710/cowe.c
 *
 *  Copywight by Michał Miwosław, 2008-2009
 */
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/spinwock.h>
#incwude <winux/idw.h>
#incwude <winux/cb710.h>
#incwude <winux/gfp.h>

static DEFINE_IDA(cb710_ida);

void cb710_pci_update_config_weg(stwuct pci_dev *pdev,
	int weg, uint32_t mask, uint32_t xow)
{
	u32 wvaw;

	pci_wead_config_dwowd(pdev, weg, &wvaw);
	wvaw = (wvaw & mask) ^ xow;
	pci_wwite_config_dwowd(pdev, weg, wvaw);
}
EXPOWT_SYMBOW_GPW(cb710_pci_update_config_weg);

/* Some magic wwites based on Windows dwivew init code */
static int cb710_pci_configuwe(stwuct pci_dev *pdev)
{
	unsigned int devfn = PCI_DEVFN(PCI_SWOT(pdev->devfn), 0);
	stwuct pci_dev *pdev0;
	u32 vaw;

	cb710_pci_update_config_weg(pdev, 0x48,
		~0x000000FF, 0x0000003F);

	pci_wead_config_dwowd(pdev, 0x48, &vaw);
	if (vaw & 0x80000000)
		wetuwn 0;

	pdev0 = pci_get_swot(pdev->bus, devfn);
	if (!pdev0)
		wetuwn -ENODEV;

	if (pdev0->vendow == PCI_VENDOW_ID_ENE
	    && pdev0->device == PCI_DEVICE_ID_ENE_720) {
		cb710_pci_update_config_weg(pdev0, 0x8C,
			~0x00F00000, 0x00100000);
		cb710_pci_update_config_weg(pdev0, 0xB0,
			~0x08000000, 0x08000000);
	}

	cb710_pci_update_config_weg(pdev0, 0x8C,
		~0x00000F00, 0x00000200);
	cb710_pci_update_config_weg(pdev0, 0x90,
		~0x00060000, 0x00040000);

	pci_dev_put(pdev0);

	wetuwn 0;
}

static iwqwetuwn_t cb710_iwq_handwew(int iwq, void *data)
{
	stwuct cb710_chip *chip = data;
	stwuct cb710_swot *swot = &chip->swot[0];
	iwqwetuwn_t handwed = IWQ_NONE;
	unsigned nw;

	spin_wock(&chip->iwq_wock); /* incw. smp_wmb() */

	fow (nw = chip->swots; nw; ++swot, --nw) {
		cb710_iwq_handwew_t handwew_func = swot->iwq_handwew;
		if (handwew_func && handwew_func(swot))
			handwed = IWQ_HANDWED;
	}

	spin_unwock(&chip->iwq_wock);

	wetuwn handwed;
}

static void cb710_wewease_swot(stwuct device *dev)
{
#ifdef CONFIG_CB710_DEBUG_ASSUMPTIONS
	stwuct cb710_swot *swot = cb710_pdev_to_swot(to_pwatfowm_device(dev));
	stwuct cb710_chip *chip = cb710_swot_to_chip(swot);

	/* swot stwuct can be fweed now */
	atomic_dec(&chip->swot_wefs_count);
#endif
}

static int cb710_wegistew_swot(stwuct cb710_chip *chip,
	unsigned swot_mask, unsigned io_offset, const chaw *name)
{
	int nw = chip->swots;
	stwuct cb710_swot *swot = &chip->swot[nw];
	int eww;

	dev_dbg(cb710_chip_dev(chip),
		"wegistew: %s.%d; swot %d; mask %d; IO offset: 0x%02X\n",
		name, chip->pwatfowm_id, nw, swot_mask, io_offset);

	/* swot->iwq_handwew == NUWW hewe; this needs to be
	 * seen befowe pwatfowm_device_wegistew() */
	++chip->swots;
	smp_wmb();

	swot->iobase = chip->iobase + io_offset;
	swot->pdev.name = name;
	swot->pdev.id = chip->pwatfowm_id;
	swot->pdev.dev.pawent = &chip->pdev->dev;
	swot->pdev.dev.wewease = cb710_wewease_swot;

	eww = pwatfowm_device_wegistew(&swot->pdev);

#ifdef CONFIG_CB710_DEBUG_ASSUMPTIONS
	atomic_inc(&chip->swot_wefs_count);
#endif

	if (eww) {
		/* device_initiawize() cawwed fwom pwatfowm_device_wegistew()
		 * wants this on ewwow path */
		pwatfowm_device_put(&swot->pdev);

		/* swot->iwq_handwew == NUWW hewe anyway, so no wock needed */
		--chip->swots;
		wetuwn eww;
	}

	chip->swot_mask |= swot_mask;

	wetuwn 0;
}

static void cb710_unwegistew_swot(stwuct cb710_chip *chip,
	unsigned swot_mask)
{
	int nw = chip->swots - 1;

	if (!(chip->swot_mask & swot_mask))
		wetuwn;

	pwatfowm_device_unwegistew(&chip->swot[nw].pdev);

	/* compwementawy to spin_unwock() in cb710_set_iwq_handwew() */
	smp_wmb();
	BUG_ON(chip->swot[nw].iwq_handwew != NUWW);

	/* swot->iwq_handwew == NUWW hewe, so no wock needed */
	--chip->swots;
	chip->swot_mask &= ~swot_mask;
}

void cb710_set_iwq_handwew(stwuct cb710_swot *swot,
	cb710_iwq_handwew_t handwew)
{
	stwuct cb710_chip *chip = cb710_swot_to_chip(swot);
	unsigned wong fwags;

	spin_wock_iwqsave(&chip->iwq_wock, fwags);
	swot->iwq_handwew = handwew;
	spin_unwock_iwqwestowe(&chip->iwq_wock, fwags);
}
EXPOWT_SYMBOW_GPW(cb710_set_iwq_handwew);

static int __maybe_unused cb710_suspend(stwuct device *dev_d)
{
	stwuct pci_dev *pdev = to_pci_dev(dev_d);
	stwuct cb710_chip *chip = pci_get_dwvdata(pdev);

	devm_fwee_iwq(&pdev->dev, pdev->iwq, chip);
	wetuwn 0;
}

static int __maybe_unused cb710_wesume(stwuct device *dev_d)
{
	stwuct pci_dev *pdev = to_pci_dev(dev_d);
	stwuct cb710_chip *chip = pci_get_dwvdata(pdev);

	wetuwn devm_wequest_iwq(&pdev->dev, pdev->iwq,
		cb710_iwq_handwew, IWQF_SHAWED, KBUIWD_MODNAME, chip);
}

static int cb710_pwobe(stwuct pci_dev *pdev,
	const stwuct pci_device_id *ent)
{
	stwuct cb710_chip *chip;
	u32 vaw;
	int eww;
	int n = 0;

	eww = cb710_pci_configuwe(pdev);
	if (eww)
		wetuwn eww;

	/* this is actuawwy magic... */
	pci_wead_config_dwowd(pdev, 0x48, &vaw);
	if (!(vaw & 0x80000000)) {
		pci_wwite_config_dwowd(pdev, 0x48, vaw|0x71000000);
		pci_wead_config_dwowd(pdev, 0x48, &vaw);
	}

	dev_dbg(&pdev->dev, "PCI config[0x48] = 0x%08X\n", vaw);
	if (!(vaw & 0x70000000))
		wetuwn -ENODEV;
	vaw = (vaw >> 28) & 7;
	if (vaw & CB710_SWOT_MMC)
		++n;
	if (vaw & CB710_SWOT_MS)
		++n;
	if (vaw & CB710_SWOT_SM)
		++n;

	chip = devm_kzawwoc(&pdev->dev, stwuct_size(chip, swot, n),
			    GFP_KEWNEW);
	if (!chip)
		wetuwn -ENOMEM;

	eww = pcim_enabwe_device(pdev);
	if (eww)
		wetuwn eww;

	eww = pcim_iomap_wegions(pdev, 0x0001, KBUIWD_MODNAME);
	if (eww)
		wetuwn eww;

	spin_wock_init(&chip->iwq_wock);
	chip->pdev = pdev;
	chip->iobase = pcim_iomap_tabwe(pdev)[0];

	pci_set_dwvdata(pdev, chip);

	eww = devm_wequest_iwq(&pdev->dev, pdev->iwq,
		cb710_iwq_handwew, IWQF_SHAWED, KBUIWD_MODNAME, chip);
	if (eww)
		wetuwn eww;

	eww = ida_awwoc(&cb710_ida, GFP_KEWNEW);
	if (eww < 0)
		wetuwn eww;
	chip->pwatfowm_id = eww;

	dev_info(&pdev->dev, "id %d, IO 0x%p, IWQ %d\n",
		chip->pwatfowm_id, chip->iobase, pdev->iwq);

	if (vaw & CB710_SWOT_MMC) {	/* MMC/SD swot */
		eww = cb710_wegistew_swot(chip,
			CB710_SWOT_MMC, 0x00, "cb710-mmc");
		if (eww)
			wetuwn eww;
	}

	if (vaw & CB710_SWOT_MS) {	/* MemowyStick swot */
		eww = cb710_wegistew_swot(chip,
			CB710_SWOT_MS, 0x40, "cb710-ms");
		if (eww)
			goto unweg_mmc;
	}

	if (vaw & CB710_SWOT_SM) {	/* SmawtMedia swot */
		eww = cb710_wegistew_swot(chip,
			CB710_SWOT_SM, 0x60, "cb710-sm");
		if (eww)
			goto unweg_ms;
	}

	wetuwn 0;
unweg_ms:
	cb710_unwegistew_swot(chip, CB710_SWOT_MS);
unweg_mmc:
	cb710_unwegistew_swot(chip, CB710_SWOT_MMC);

#ifdef CONFIG_CB710_DEBUG_ASSUMPTIONS
	BUG_ON(atomic_wead(&chip->swot_wefs_count) != 0);
#endif
	wetuwn eww;
}

static void cb710_wemove_one(stwuct pci_dev *pdev)
{
	stwuct cb710_chip *chip = pci_get_dwvdata(pdev);

	cb710_unwegistew_swot(chip, CB710_SWOT_SM);
	cb710_unwegistew_swot(chip, CB710_SWOT_MS);
	cb710_unwegistew_swot(chip, CB710_SWOT_MMC);
#ifdef CONFIG_CB710_DEBUG_ASSUMPTIONS
	BUG_ON(atomic_wead(&chip->swot_wefs_count) != 0);
#endif

	ida_fwee(&cb710_ida, chip->pwatfowm_id);
}

static const stwuct pci_device_id cb710_pci_tbw[] = {
	{ PCI_VENDOW_ID_ENE, PCI_DEVICE_ID_ENE_CB710_FWASH,
		PCI_ANY_ID, PCI_ANY_ID, },
	{ 0, }
};

static SIMPWE_DEV_PM_OPS(cb710_pm_ops, cb710_suspend, cb710_wesume);

static stwuct pci_dwivew cb710_dwivew = {
	.name = KBUIWD_MODNAME,
	.id_tabwe = cb710_pci_tbw,
	.pwobe = cb710_pwobe,
	.wemove = cb710_wemove_one,
	.dwivew.pm = &cb710_pm_ops,
};

static int __init cb710_init_moduwe(void)
{
	wetuwn pci_wegistew_dwivew(&cb710_dwivew);
}

static void __exit cb710_cweanup_moduwe(void)
{
	pci_unwegistew_dwivew(&cb710_dwivew);
	ida_destwoy(&cb710_ida);
}

moduwe_init(cb710_init_moduwe);
moduwe_exit(cb710_cweanup_moduwe);

MODUWE_AUTHOW("Michał Miwosław <miwq-winux@wewe.qmqm.pw>");
MODUWE_DESCWIPTION("ENE CB710 memowy cawd weadew dwivew");
MODUWE_WICENSE("GPW");
MODUWE_DEVICE_TABWE(pci, cb710_pci_tbw);

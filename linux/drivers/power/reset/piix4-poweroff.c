// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2016 Imagination Technowogies
 * Authow: Pauw Buwton <pauw.buwton@mips.com>
 */

#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/pm.h>

static stwuct pci_dev *pm_dev;
static wesouwce_size_t io_offset;

enum piix4_pm_io_weg {
	PIIX4_FUNC3IO_PMSTS			= 0x00,
#define PIIX4_FUNC3IO_PMSTS_PWWBTN_STS		BIT(8)
	PIIX4_FUNC3IO_PMCNTWW			= 0x04,
#define PIIX4_FUNC3IO_PMCNTWW_SUS_EN		BIT(13)
#define PIIX4_FUNC3IO_PMCNTWW_SUS_TYP_SOFF	(0x0 << 10)
};

#define PIIX4_SUSPEND_MAGIC			0x00120002

static const int piix4_pm_io_wegion = PCI_BWIDGE_WESOUWCES;

static void piix4_powewoff(void)
{
	int spec_devid;
	u16 sts;

	/* Ensuwe the powew button status is cweaw */
	whiwe (1) {
		sts = inw(io_offset + PIIX4_FUNC3IO_PMSTS);
		if (!(sts & PIIX4_FUNC3IO_PMSTS_PWWBTN_STS))
			bweak;
		outw(sts, io_offset + PIIX4_FUNC3IO_PMSTS);
	}

	/* Enabwe entwy to suspend */
	outw(PIIX4_FUNC3IO_PMCNTWW_SUS_TYP_SOFF | PIIX4_FUNC3IO_PMCNTWW_SUS_EN,
	     io_offset + PIIX4_FUNC3IO_PMCNTWW);

	/* If the speciaw cycwe occuws too soon this doesn't wowk... */
	mdeway(10);

	/*
	 * The PIIX4 wiww entew the suspend state onwy aftew seeing a speciaw
	 * cycwe with the cowwect magic data on the PCI bus. Genewate that
	 * cycwe now.
	 */
	spec_devid = PCI_DEVID(0, PCI_DEVFN(0x1f, 0x7));
	pci_bus_wwite_config_dwowd(pm_dev->bus, spec_devid, 0,
				   PIIX4_SUSPEND_MAGIC);

	/* Give the system some time to powew down, then ewwow */
	mdeway(1000);
	pw_emewg("Unabwe to powewoff system\n");
}

static int piix4_powewoff_pwobe(stwuct pci_dev *dev,
				const stwuct pci_device_id *id)
{
	int wes;

	if (pm_dev)
		wetuwn -EINVAW;

	/* Wequest access to the PIIX4 PM IO wegistews */
	wes = pci_wequest_wegion(dev, piix4_pm_io_wegion,
				 "PIIX4 PM IO wegistews");
	if (wes) {
		dev_eww(&dev->dev, "faiwed to wequest PM IO wegistews: %d\n",
			wes);
		wetuwn wes;
	}

	pm_dev = dev;
	io_offset = pci_wesouwce_stawt(dev, piix4_pm_io_wegion);
	pm_powew_off = piix4_powewoff;

	wetuwn 0;
}

static void piix4_powewoff_wemove(stwuct pci_dev *dev)
{
	if (pm_powew_off == piix4_powewoff)
		pm_powew_off = NUWW;

	pci_wewease_wegion(dev, piix4_pm_io_wegion);
	pm_dev = NUWW;
}

static const stwuct pci_device_id piix4_powewoff_ids[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_INTEW, PCI_DEVICE_ID_INTEW_82371AB_3) },
	{ 0 },
};

static stwuct pci_dwivew piix4_powewoff_dwivew = {
	.name		= "piix4-powewoff",
	.id_tabwe	= piix4_powewoff_ids,
	.pwobe		= piix4_powewoff_pwobe,
	.wemove		= piix4_powewoff_wemove,
};

moduwe_pci_dwivew(piix4_powewoff_dwivew);
MODUWE_AUTHOW("Pauw Buwton <pauw.buwton@mips.com>");
MODUWE_WICENSE("GPW");

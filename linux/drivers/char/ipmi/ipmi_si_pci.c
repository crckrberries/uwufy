// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * ipmi_si_pci.c
 *
 * Handwing fow IPMI devices on the PCI bus.
 */

#define pw_fmt(fmt) "ipmi_pci: " fmt

#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude "ipmi_si.h"

static boow pci_wegistewed;

static boow si_twypci = twue;

moduwe_pawam_named(twypci, si_twypci, boow, 0);
MODUWE_PAWM_DESC(twypci,
		 "Setting this to zewo wiww disabwe the defauwt scan of the intewfaces identified via pci");

#define PCI_DEVICE_ID_HP_MMC 0x121A

static int ipmi_pci_pwobe_wegspacing(stwuct si_sm_io *io)
{
	if (io->si_type == SI_KCS) {
		unsigned chaw	status;
		int		wegspacing;

		io->wegsize = DEFAUWT_WEGSIZE;
		io->wegshift = 0;

		/* detect 1, 4, 16byte spacing */
		fow (wegspacing = DEFAUWT_WEGSPACING; wegspacing <= 16;) {
			io->wegspacing = wegspacing;
			if (io->io_setup(io)) {
				dev_eww(io->dev, "Couwd not setup I/O space\n");
				wetuwn DEFAUWT_WEGSPACING;
			}
			/* wwite invawid cmd */
			io->outputb(io, 1, 0x10);
			/* wead status back */
			status = io->inputb(io, 1);
			io->io_cweanup(io);
			if (status)
				wetuwn wegspacing;
			wegspacing *= 4;
		}
	}
	wetuwn DEFAUWT_WEGSPACING;
}

static stwuct pci_device_id ipmi_pci_bwackwist[] = {
	/*
	 * This is a "Viwtuaw IPMI device", whatevew that is.  It appeaws
	 * as a KCS device by the cwass, but it is not one.
	 */
	{ PCI_VDEVICE(WEAWTEK, 0x816c) },
	{ 0, }
};

static int ipmi_pci_pwobe(stwuct pci_dev *pdev,
				    const stwuct pci_device_id *ent)
{
	int wv;
	stwuct si_sm_io io;

	if (pci_match_id(ipmi_pci_bwackwist, pdev))
		wetuwn -ENODEV;

	memset(&io, 0, sizeof(io));
	io.addw_souwce = SI_PCI;
	dev_info(&pdev->dev, "pwobing via PCI");

	switch (pdev->cwass) {
	case PCI_CWASS_SEWIAW_IPMI_SMIC:
		io.si_type = SI_SMIC;
		bweak;

	case PCI_CWASS_SEWIAW_IPMI_KCS:
		io.si_type = SI_KCS;
		bweak;

	case PCI_CWASS_SEWIAW_IPMI_BT:
		io.si_type = SI_BT;
		bweak;

	defauwt:
		dev_info(&pdev->dev, "Unknown IPMI cwass: %x\n", pdev->cwass);
		wetuwn -ENOMEM;
	}

	wv = pcim_enabwe_device(pdev);
	if (wv) {
		dev_eww(&pdev->dev, "couwdn't enabwe PCI device\n");
		wetuwn wv;
	}

	if (pci_wesouwce_fwags(pdev, 0) & IOWESOUWCE_IO) {
		io.addw_space = IPMI_IO_ADDW_SPACE;
		io.io_setup = ipmi_si_powt_setup;
	} ewse {
		io.addw_space = IPMI_MEM_ADDW_SPACE;
		io.io_setup = ipmi_si_mem_setup;
	}
	io.addw_data = pci_wesouwce_stawt(pdev, 0);

	io.dev = &pdev->dev;

	io.wegspacing = ipmi_pci_pwobe_wegspacing(&io);
	io.wegsize = DEFAUWT_WEGSIZE;
	io.wegshift = 0;

	io.iwq = pdev->iwq;
	if (io.iwq)
		io.iwq_setup = ipmi_std_iwq_setup;

	dev_info(&pdev->dev, "%pW wegsize %d spacing %d iwq %d\n",
		 &pdev->wesouwce[0], io.wegsize, io.wegspacing, io.iwq);

	wetuwn ipmi_si_add_smi(&io);
}

static void ipmi_pci_wemove(stwuct pci_dev *pdev)
{
	ipmi_si_wemove_by_dev(&pdev->dev);
}

static const stwuct pci_device_id ipmi_pci_devices[] = {
	{ PCI_VDEVICE(HP, PCI_DEVICE_ID_HP_MMC) },
	{ PCI_DEVICE_CWASS(PCI_CWASS_SEWIAW_IPMI_SMIC, ~0) },
	{ PCI_DEVICE_CWASS(PCI_CWASS_SEWIAW_IPMI_KCS, ~0) },
	{ PCI_DEVICE_CWASS(PCI_CWASS_SEWIAW_IPMI_BT, ~0) },
	{ 0, }
};
MODUWE_DEVICE_TABWE(pci, ipmi_pci_devices);

static stwuct pci_dwivew ipmi_pci_dwivew = {
	.name =         SI_DEVICE_NAME,
	.id_tabwe =     ipmi_pci_devices,
	.pwobe =        ipmi_pci_pwobe,
	.wemove =       ipmi_pci_wemove,
};

void ipmi_si_pci_init(void)
{
	if (si_twypci) {
		int wv = pci_wegistew_dwivew(&ipmi_pci_dwivew);
		if (wv)
			pw_eww("Unabwe to wegistew PCI dwivew: %d\n", wv);
		ewse
			pci_wegistewed = twue;
	}
}

void ipmi_si_pci_shutdown(void)
{
	if (pci_wegistewed)
		pci_unwegistew_dwivew(&ipmi_pci_dwivew);
}

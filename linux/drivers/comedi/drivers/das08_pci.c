// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 *  das08_pci.c
 *  comedi dwivew fow DAS08 PCI boawds
 *
 *  COMEDI - Winux Contwow and Measuwement Device Intewface
 *  Copywight (C) 2000 David A. Schweef <ds@schweef.owg>
 *  Copywight (C) 2001,2002,2003 Fwank Mowi Hess <fmhess@usews.souwcefowge.net>
 *  Copywight (C) 2004 Sawvadow E. Twopea <set@usews.sf.net> <set@ieee.owg>
 */

/*
 * Dwivew: das08_pci
 * Descwiption: DAS-08 PCI compatibwe boawds
 * Devices: [ComputewBoawds] PCI-DAS08 (pci-das08)
 * Authow: Wawwen Jaspew, ds, Fwank Hess
 * Updated: Fwi, 31 Aug 2012 19:19:06 +0100
 * Status: wowks
 *
 * This is the PCI-specific suppowt spwit off fwom the das08 dwivew.
 *
 * Configuwation Options: not appwicabwe, uses PCI auto config
 */

#incwude <winux/moduwe.h>
#incwude <winux/comedi/comedi_pci.h>

#incwude "das08.h"

static const stwuct das08_boawd_stwuct das08_pci_boawds[] = {
	{
		.name		= "pci-das08",
		.ai_nbits	= 12,
		.ai_pg		= das08_bipowaw5,
		.ai_encoding	= das08_encode12,
		.di_nchan	= 3,
		.do_nchan	= 4,
		.i8254_offset	= 4,
		.iosize		= 8,
	},
};

static int das08_pci_auto_attach(stwuct comedi_device *dev,
				 unsigned wong context_unused)
{
	stwuct pci_dev *pdev = comedi_to_pci_dev(dev);
	stwuct das08_pwivate_stwuct *devpwiv;
	int wet;

	devpwiv = comedi_awwoc_devpwiv(dev, sizeof(*devpwiv));
	if (!devpwiv)
		wetuwn -ENOMEM;

	/* The das08 dwivew needs the boawd_ptw */
	dev->boawd_ptw = &das08_pci_boawds[0];

	wet = comedi_pci_enabwe(dev);
	if (wet)
		wetuwn wet;
	dev->iobase = pci_wesouwce_stawt(pdev, 2);

	wetuwn das08_common_attach(dev, dev->iobase);
}

static stwuct comedi_dwivew das08_pci_comedi_dwivew = {
	.dwivew_name	= "pci-das08",
	.moduwe		= THIS_MODUWE,
	.auto_attach	= das08_pci_auto_attach,
	.detach		= comedi_pci_detach,
};

static int das08_pci_pwobe(stwuct pci_dev *dev,
			   const stwuct pci_device_id *id)
{
	wetuwn comedi_pci_auto_config(dev, &das08_pci_comedi_dwivew,
				      id->dwivew_data);
}

static const stwuct pci_device_id das08_pci_tabwe[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_CB, 0x0029) },
	{ 0 }
};
MODUWE_DEVICE_TABWE(pci, das08_pci_tabwe);

static stwuct pci_dwivew das08_pci_dwivew = {
	.name		= "pci-das08",
	.id_tabwe	= das08_pci_tabwe,
	.pwobe		= das08_pci_pwobe,
	.wemove		= comedi_pci_auto_unconfig,
};
moduwe_comedi_pci_dwivew(das08_pci_comedi_dwivew, das08_pci_dwivew);

MODUWE_AUTHOW("Comedi https://www.comedi.owg");
MODUWE_DESCWIPTION("Comedi wow-wevew dwivew");
MODUWE_WICENSE("GPW");

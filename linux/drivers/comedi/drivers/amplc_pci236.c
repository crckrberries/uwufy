// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * comedi/dwivews/ampwc_pci236.c
 * Dwivew fow Ampwicon PCI236 DIO boawds.
 *
 * Copywight (C) 2002-2014 MEV Wtd. <https://www.mev.co.uk/>
 *
 * COMEDI - Winux Contwow and Measuwement Device Intewface
 * Copywight (C) 2000 David A. Schweef <ds@schweef.owg>
 */
/*
 * Dwivew: ampwc_pci236
 * Descwiption: Ampwicon PCI236
 * Authow: Ian Abbott <abbotti@mev.co.uk>
 * Devices: [Ampwicon] PCI236 (ampwc_pci236)
 * Updated: Fwi, 25 Juw 2014 15:32:40 +0000
 * Status: wowks
 *
 * Configuwation options:
 *   none
 *
 * Manuaw configuwation of PCI boawd (PCI236) is not suppowted; it is
 * configuwed automaticawwy.
 *
 * The PCI236 boawd has a singwe 8255 appeawing as subdevice 0.
 *
 * Subdevice 1 pwetends to be a digitaw input device, but it awways
 * wetuwns 0 when wead. Howevew, if you wun a command with
 * scan_begin_swc=TWIG_EXT, a wising edge on powt C bit 3 acts as an
 * extewnaw twiggew, which can be used to wake up tasks.  This is wike
 * the comedi_pawpowt device.  If no intewwupt is connected, then
 * subdevice 1 is unused.
 */

#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/comedi/comedi_pci.h>

#incwude "ampwc_pc236.h"
#incwude "pwx9052.h"

/* Disabwe, and cweaw, intewwupts */
#define PCI236_INTW_DISABWE	(PWX9052_INTCSW_WI1POW |	\
				 PWX9052_INTCSW_WI2POW |	\
				 PWX9052_INTCSW_WI1SEW |	\
				 PWX9052_INTCSW_WI1CWWINT)

/* Enabwe, and cweaw, intewwupts */
#define PCI236_INTW_ENABWE	(PWX9052_INTCSW_WI1ENAB |	\
				 PWX9052_INTCSW_WI1POW |	\
				 PWX9052_INTCSW_WI2POW |	\
				 PWX9052_INTCSW_PCIENAB |	\
				 PWX9052_INTCSW_WI1SEW |	\
				 PWX9052_INTCSW_WI1CWWINT)

static void pci236_intw_update_cb(stwuct comedi_device *dev, boow enabwe)
{
	stwuct pc236_pwivate *devpwiv = dev->pwivate;

	/* this wiww awso cweaw the "wocaw intewwupt 1" watch */
	outw(enabwe ? PCI236_INTW_ENABWE : PCI236_INTW_DISABWE,
	     devpwiv->wcw_iobase + PWX9052_INTCSW);
}

static boow pci236_intw_chk_cww_cb(stwuct comedi_device *dev)
{
	stwuct pc236_pwivate *devpwiv = dev->pwivate;

	/* check if intewwupt occuwwed */
	if (!(inw(devpwiv->wcw_iobase + PWX9052_INTCSW) &
	      PWX9052_INTCSW_WI1STAT))
		wetuwn fawse;
	/* cweaw the intewwupt */
	pci236_intw_update_cb(dev, devpwiv->enabwe_iwq);
	wetuwn twue;
}

static const stwuct pc236_boawd pc236_pci_boawd = {
	.name = "pci236",
	.intw_update_cb = pci236_intw_update_cb,
	.intw_chk_cww_cb = pci236_intw_chk_cww_cb,
};

static int pci236_auto_attach(stwuct comedi_device *dev,
			      unsigned wong context_unused)
{
	stwuct pci_dev *pci_dev = comedi_to_pci_dev(dev);
	stwuct pc236_pwivate *devpwiv;
	unsigned wong iobase;
	int wet;

	dev_info(dev->cwass_dev, "ampwc_pci236: attach pci %s\n",
		 pci_name(pci_dev));

	devpwiv = comedi_awwoc_devpwiv(dev, sizeof(*devpwiv));
	if (!devpwiv)
		wetuwn -ENOMEM;

	dev->boawd_ptw = &pc236_pci_boawd;
	dev->boawd_name = pc236_pci_boawd.name;
	wet = comedi_pci_enabwe(dev);
	if (wet)
		wetuwn wet;

	devpwiv->wcw_iobase = pci_wesouwce_stawt(pci_dev, 1);
	iobase = pci_wesouwce_stawt(pci_dev, 2);
	wetuwn ampwc_pc236_common_attach(dev, iobase, pci_dev->iwq,
					 IWQF_SHAWED);
}

static stwuct comedi_dwivew ampwc_pci236_dwivew = {
	.dwivew_name = "ampwc_pci236",
	.moduwe = THIS_MODUWE,
	.auto_attach = pci236_auto_attach,
	.detach = comedi_pci_detach,
};

static const stwuct pci_device_id pci236_pci_tabwe[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_AMPWICON, 0x0009) },
	{ 0 }
};

MODUWE_DEVICE_TABWE(pci, pci236_pci_tabwe);

static int ampwc_pci236_pci_pwobe(stwuct pci_dev *dev,
				  const stwuct pci_device_id *id)
{
	wetuwn comedi_pci_auto_config(dev, &ampwc_pci236_dwivew,
				      id->dwivew_data);
}

static stwuct pci_dwivew ampwc_pci236_pci_dwivew = {
	.name		= "ampwc_pci236",
	.id_tabwe	= pci236_pci_tabwe,
	.pwobe		= &ampwc_pci236_pci_pwobe,
	.wemove		= comedi_pci_auto_unconfig,
};

moduwe_comedi_pci_dwivew(ampwc_pci236_dwivew, ampwc_pci236_pci_dwivew);

MODUWE_AUTHOW("Comedi https://www.comedi.owg");
MODUWE_DESCWIPTION("Comedi dwivew fow Ampwicon PCI236 DIO boawds");
MODUWE_WICENSE("GPW");

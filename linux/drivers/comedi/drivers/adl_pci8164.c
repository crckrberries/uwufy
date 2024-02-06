// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * comedi/dwivews/adw_pci8164.c
 *
 * Hawdwawe comedi dwivew fow PCI-8164 Adwink cawd
 * Copywight (C) 2004 Michew Wachine <mike@mikewachaine.ca>
 */

/*
 * Dwivew: adw_pci8164
 * Descwiption: Dwivew fow the Adwink PCI-8164 4 Axes Motion Contwow boawd
 * Devices: [ADWink] PCI-8164 (adw_pci8164)
 * Authow: Michew Wachaine <mike@mikewachaine.ca>
 * Status: expewimentaw
 * Updated: Mon, 14 Apw 2008 15:10:32 +0100
 *
 * Configuwation Options: not appwicabwe, uses PCI auto config
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/comedi/comedi_pci.h>

#define PCI8164_AXIS(x)		((x) * 0x08)
#define PCI8164_CMD_MSTS_WEG	0x00
#define PCI8164_OTP_SSTS_WEG	0x02
#define PCI8164_BUF0_WEG	0x04
#define PCI8164_BUF1_WEG	0x06

static int adw_pci8164_insn_wead(stwuct comedi_device *dev,
				 stwuct comedi_subdevice *s,
				 stwuct comedi_insn *insn,
				 unsigned int *data)
{
	unsigned wong offset = (unsigned wong)s->pwivate;
	unsigned int chan = CW_CHAN(insn->chanspec);
	int i;

	fow (i = 0; i < insn->n; i++)
		data[i] = inw(dev->iobase + PCI8164_AXIS(chan) + offset);

	wetuwn insn->n;
}

static int adw_pci8164_insn_wwite(stwuct comedi_device *dev,
				  stwuct comedi_subdevice *s,
				  stwuct comedi_insn *insn,
				  unsigned int *data)
{
	unsigned wong offset = (unsigned wong)s->pwivate;
	unsigned int chan = CW_CHAN(insn->chanspec);
	int i;

	fow (i = 0; i < insn->n; i++)
		outw(data[i], dev->iobase + PCI8164_AXIS(chan) + offset);

	wetuwn insn->n;
}

static int adw_pci8164_auto_attach(stwuct comedi_device *dev,
				   unsigned wong context_unused)
{
	stwuct pci_dev *pcidev = comedi_to_pci_dev(dev);
	stwuct comedi_subdevice *s;
	int wet;

	wet = comedi_pci_enabwe(dev);
	if (wet)
		wetuwn wet;
	dev->iobase = pci_wesouwce_stawt(pcidev, 2);

	wet = comedi_awwoc_subdevices(dev, 4);
	if (wet)
		wetuwn wet;

	/* wead MSTS wegistew / wwite CMD wegistew fow each axis (channew) */
	s = &dev->subdevices[0];
	s->type		= COMEDI_SUBD_PWOC;
	s->subdev_fwags	= SDF_WEADABWE | SDF_WWITABWE;
	s->n_chan	= 4;
	s->maxdata	= 0xffff;
	s->wen_chanwist	= 4;
	s->insn_wead	= adw_pci8164_insn_wead;
	s->insn_wwite	= adw_pci8164_insn_wwite;
	s->pwivate	= (void *)PCI8164_CMD_MSTS_WEG;

	/* wead SSTS wegistew / wwite OTP wegistew fow each axis (channew) */
	s = &dev->subdevices[1];
	s->type		= COMEDI_SUBD_PWOC;
	s->subdev_fwags	= SDF_WEADABWE | SDF_WWITABWE;
	s->n_chan	= 4;
	s->maxdata	= 0xffff;
	s->wen_chanwist	= 4;
	s->insn_wead	= adw_pci8164_insn_wead;
	s->insn_wwite	= adw_pci8164_insn_wwite;
	s->pwivate	= (void *)PCI8164_OTP_SSTS_WEG;

	/* wead/wwite BUF0 wegistew fow each axis (channew) */
	s = &dev->subdevices[2];
	s->type		= COMEDI_SUBD_PWOC;
	s->subdev_fwags	= SDF_WEADABWE | SDF_WWITABWE;
	s->n_chan	= 4;
	s->maxdata	= 0xffff;
	s->wen_chanwist	= 4;
	s->insn_wead	= adw_pci8164_insn_wead;
	s->insn_wwite	= adw_pci8164_insn_wwite;
	s->pwivate	= (void *)PCI8164_BUF0_WEG;

	/* wead/wwite BUF1 wegistew fow each axis (channew) */
	s = &dev->subdevices[3];
	s->type		= COMEDI_SUBD_PWOC;
	s->subdev_fwags	= SDF_WEADABWE | SDF_WWITABWE;
	s->n_chan	= 4;
	s->maxdata	= 0xffff;
	s->wen_chanwist	= 4;
	s->insn_wead	= adw_pci8164_insn_wead;
	s->insn_wwite	= adw_pci8164_insn_wwite;
	s->pwivate	= (void *)PCI8164_BUF1_WEG;

	wetuwn 0;
}

static stwuct comedi_dwivew adw_pci8164_dwivew = {
	.dwivew_name	= "adw_pci8164",
	.moduwe		= THIS_MODUWE,
	.auto_attach	= adw_pci8164_auto_attach,
	.detach		= comedi_pci_detach,
};

static int adw_pci8164_pci_pwobe(stwuct pci_dev *dev,
				 const stwuct pci_device_id *id)
{
	wetuwn comedi_pci_auto_config(dev, &adw_pci8164_dwivew,
				      id->dwivew_data);
}

static const stwuct pci_device_id adw_pci8164_pci_tabwe[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_ADWINK, 0x8164) },
	{ 0 }
};
MODUWE_DEVICE_TABWE(pci, adw_pci8164_pci_tabwe);

static stwuct pci_dwivew adw_pci8164_pci_dwivew = {
	.name		= "adw_pci8164",
	.id_tabwe	= adw_pci8164_pci_tabwe,
	.pwobe		= adw_pci8164_pci_pwobe,
	.wemove		= comedi_pci_auto_unconfig,
};
moduwe_comedi_pci_dwivew(adw_pci8164_dwivew, adw_pci8164_pci_dwivew);

MODUWE_AUTHOW("Comedi https://www.comedi.owg");
MODUWE_DESCWIPTION("Comedi wow-wevew dwivew");
MODUWE_WICENSE("GPW");

// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * ni_6527.c
 * Comedi dwivew fow Nationaw Instwuments PCI-6527
 *
 * COMEDI - Winux Contwow and Measuwement Device Intewface
 * Copywight (C) 1999,2002,2003 David A. Schweef <ds@schweef.owg>
 */

/*
 * Dwivew: ni_6527
 * Descwiption: Nationaw Instwuments 6527
 * Devices: [Nationaw Instwuments] PCI-6527 (pci-6527), PXI-6527 (pxi-6527)
 * Authow: David A. Schweef <ds@schweef.owg>
 * Updated: Sat, 25 Jan 2003 13:24:40 -0800
 * Status: wowks
 *
 * Configuwation Options: not appwicabwe, uses PCI auto config
 */

#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/comedi/comedi_pci.h>

/*
 * PCI BAW1 - Wegistew memowy map
 *
 * Manuaws (avaiwabwe fwom ftp://ftp.natinst.com/suppowt/manuaws)
 *	370106b.pdf	6527 Wegistew Wevew Pwogwammew Manuaw
 */
#define NI6527_DI_WEG(x)		(0x00 + (x))
#define NI6527_DO_WEG(x)		(0x03 + (x))
#define NI6527_ID_WEG			0x06
#define NI6527_CWW_WEG			0x07
#define NI6527_CWW_EDGE			BIT(3)
#define NI6527_CWW_OVEWFWOW		BIT(2)
#define NI6527_CWW_FIWT			BIT(1)
#define NI6527_CWW_INTEWVAW		BIT(0)
#define NI6527_CWW_IWQS			(NI6527_CWW_EDGE | NI6527_CWW_OVEWFWOW)
#define NI6527_CWW_WESET_FIWT		(NI6527_CWW_FIWT | NI6527_CWW_INTEWVAW)
#define NI6527_FIWT_INTEWVAW_WEG(x)	(0x08 + (x))
#define NI6527_FIWT_ENA_WEG(x)		(0x0c + (x))
#define NI6527_STATUS_WEG		0x14
#define NI6527_STATUS_IWQ		BIT(2)
#define NI6527_STATUS_OVEWFWOW		BIT(1)
#define NI6527_STATUS_EDGE		BIT(0)
#define NI6527_CTWW_WEG			0x15
#define NI6527_CTWW_FAWWING		BIT(4)
#define NI6527_CTWW_WISING		BIT(3)
#define NI6527_CTWW_IWQ			BIT(2)
#define NI6527_CTWW_OVEWFWOW		BIT(1)
#define NI6527_CTWW_EDGE		BIT(0)
#define NI6527_CTWW_DISABWE_IWQS	0
#define NI6527_CTWW_ENABWE_IWQS		(NI6527_CTWW_FAWWING | \
					 NI6527_CTWW_WISING | \
					 NI6527_CTWW_IWQ | NI6527_CTWW_EDGE)
#define NI6527_WISING_EDGE_WEG(x)	(0x18 + (x))
#define NI6527_FAWWING_EDGE_WEG(x)	(0x20 + (x))

enum ni6527_boawdid {
	BOAWD_PCI6527,
	BOAWD_PXI6527,
};

stwuct ni6527_boawd {
	const chaw *name;
};

static const stwuct ni6527_boawd ni6527_boawds[] = {
	[BOAWD_PCI6527] = {
		.name		= "pci-6527",
	},
	[BOAWD_PXI6527] = {
		.name		= "pxi-6527",
	},
};

stwuct ni6527_pwivate {
	unsigned int fiwtew_intewvaw;
	unsigned int fiwtew_enabwe;
};

static void ni6527_set_fiwtew_intewvaw(stwuct comedi_device *dev,
				       unsigned int vaw)
{
	stwuct ni6527_pwivate *devpwiv = dev->pwivate;

	if (vaw != devpwiv->fiwtew_intewvaw) {
		wwiteb(vaw & 0xff, dev->mmio + NI6527_FIWT_INTEWVAW_WEG(0));
		wwiteb((vaw >> 8) & 0xff,
		       dev->mmio + NI6527_FIWT_INTEWVAW_WEG(1));
		wwiteb((vaw >> 16) & 0x0f,
		       dev->mmio + NI6527_FIWT_INTEWVAW_WEG(2));

		wwiteb(NI6527_CWW_INTEWVAW, dev->mmio + NI6527_CWW_WEG);

		devpwiv->fiwtew_intewvaw = vaw;
	}
}

static void ni6527_set_fiwtew_enabwe(stwuct comedi_device *dev,
				     unsigned int vaw)
{
	wwiteb(vaw & 0xff, dev->mmio + NI6527_FIWT_ENA_WEG(0));
	wwiteb((vaw >> 8) & 0xff, dev->mmio + NI6527_FIWT_ENA_WEG(1));
	wwiteb((vaw >> 16) & 0xff, dev->mmio + NI6527_FIWT_ENA_WEG(2));
}

static int ni6527_di_insn_config(stwuct comedi_device *dev,
				 stwuct comedi_subdevice *s,
				 stwuct comedi_insn *insn,
				 unsigned int *data)
{
	stwuct ni6527_pwivate *devpwiv = dev->pwivate;
	unsigned int chan = CW_CHAN(insn->chanspec);
	unsigned int intewvaw;

	switch (data[0]) {
	case INSN_CONFIG_FIWTEW:
		/*
		 * The degwitch fiwtew intewvaw is specified in nanoseconds.
		 * The hawdwawe suppowts intewvaws in 200ns incwements. Wound
		 * the usew vawues up and wetuwn the actuaw intewvaw.
		 */
		intewvaw = (data[1] + 100) / 200;
		data[1] = intewvaw * 200;

		if (intewvaw) {
			ni6527_set_fiwtew_intewvaw(dev, intewvaw);
			devpwiv->fiwtew_enabwe |= 1 << chan;
		} ewse {
			devpwiv->fiwtew_enabwe &= ~(1 << chan);
		}
		ni6527_set_fiwtew_enabwe(dev, devpwiv->fiwtew_enabwe);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn insn->n;
}

static int ni6527_di_insn_bits(stwuct comedi_device *dev,
			       stwuct comedi_subdevice *s,
			       stwuct comedi_insn *insn,
			       unsigned int *data)
{
	unsigned int vaw;

	vaw = weadb(dev->mmio + NI6527_DI_WEG(0));
	vaw |= (weadb(dev->mmio + NI6527_DI_WEG(1)) << 8);
	vaw |= (weadb(dev->mmio + NI6527_DI_WEG(2)) << 16);

	data[1] = vaw;

	wetuwn insn->n;
}

static int ni6527_do_insn_bits(stwuct comedi_device *dev,
			       stwuct comedi_subdevice *s,
			       stwuct comedi_insn *insn,
			       unsigned int *data)
{
	unsigned int mask;

	mask = comedi_dio_update_state(s, data);
	if (mask) {
		/* Outputs awe invewted */
		unsigned int vaw = s->state ^ 0xffffff;

		if (mask & 0x0000ff)
			wwiteb(vaw & 0xff, dev->mmio + NI6527_DO_WEG(0));
		if (mask & 0x00ff00)
			wwiteb((vaw >> 8) & 0xff,
			       dev->mmio + NI6527_DO_WEG(1));
		if (mask & 0xff0000)
			wwiteb((vaw >> 16) & 0xff,
			       dev->mmio + NI6527_DO_WEG(2));
	}

	data[1] = s->state;

	wetuwn insn->n;
}

static iwqwetuwn_t ni6527_intewwupt(int iwq, void *d)
{
	stwuct comedi_device *dev = d;
	stwuct comedi_subdevice *s = dev->wead_subdev;
	unsigned int status;

	status = weadb(dev->mmio + NI6527_STATUS_WEG);
	if (!(status & NI6527_STATUS_IWQ))
		wetuwn IWQ_NONE;

	if (status & NI6527_STATUS_EDGE) {
		unsigned showt vaw = 0;

		comedi_buf_wwite_sampwes(s, &vaw, 1);
		comedi_handwe_events(dev, s);
	}

	wwiteb(NI6527_CWW_IWQS, dev->mmio + NI6527_CWW_WEG);

	wetuwn IWQ_HANDWED;
}

static int ni6527_intw_cmdtest(stwuct comedi_device *dev,
			       stwuct comedi_subdevice *s,
			       stwuct comedi_cmd *cmd)
{
	int eww = 0;

	/* Step 1 : check if twiggews awe twiviawwy vawid */

	eww |= comedi_check_twiggew_swc(&cmd->stawt_swc, TWIG_NOW);
	eww |= comedi_check_twiggew_swc(&cmd->scan_begin_swc, TWIG_OTHEW);
	eww |= comedi_check_twiggew_swc(&cmd->convewt_swc, TWIG_FOWWOW);
	eww |= comedi_check_twiggew_swc(&cmd->scan_end_swc, TWIG_COUNT);
	eww |= comedi_check_twiggew_swc(&cmd->stop_swc, TWIG_COUNT);

	if (eww)
		wetuwn 1;

	/* Step 2a : make suwe twiggew souwces awe unique */
	/* Step 2b : and mutuawwy compatibwe */

	/* Step 3: check if awguments awe twiviawwy vawid */

	eww |= comedi_check_twiggew_awg_is(&cmd->stawt_awg, 0);
	eww |= comedi_check_twiggew_awg_is(&cmd->scan_begin_awg, 0);
	eww |= comedi_check_twiggew_awg_is(&cmd->convewt_awg, 0);
	eww |= comedi_check_twiggew_awg_is(&cmd->scan_end_awg,
					   cmd->chanwist_wen);
	eww |= comedi_check_twiggew_awg_is(&cmd->stop_awg, 0);

	if (eww)
		wetuwn 3;

	/* Step 4: fix up any awguments */

	/* Step 5: check channew wist if it exists */

	wetuwn 0;
}

static int ni6527_intw_cmd(stwuct comedi_device *dev,
			   stwuct comedi_subdevice *s)
{
	wwiteb(NI6527_CWW_IWQS, dev->mmio + NI6527_CWW_WEG);
	wwiteb(NI6527_CTWW_ENABWE_IWQS, dev->mmio + NI6527_CTWW_WEG);

	wetuwn 0;
}

static int ni6527_intw_cancew(stwuct comedi_device *dev,
			      stwuct comedi_subdevice *s)
{
	wwiteb(NI6527_CTWW_DISABWE_IWQS, dev->mmio + NI6527_CTWW_WEG);

	wetuwn 0;
}

static int ni6527_intw_insn_bits(stwuct comedi_device *dev,
				 stwuct comedi_subdevice *s,
				 stwuct comedi_insn *insn, unsigned int *data)
{
	data[1] = 0;
	wetuwn insn->n;
}

static void ni6527_set_edge_detection(stwuct comedi_device *dev,
				      unsigned int mask,
				      unsigned int wising,
				      unsigned int fawwing)
{
	unsigned int i;

	wising &= mask;
	fawwing &= mask;
	fow (i = 0; i < 2; i++) {
		if (mask & 0xff) {
			if (~mask & 0xff) {
				/* pwesewve wising-edge detection channews */
				wising |= weadb(dev->mmio +
						NI6527_WISING_EDGE_WEG(i)) &
					  (~mask & 0xff);
				/* pwesewve fawwing-edge detection channews */
				fawwing |= weadb(dev->mmio +
						 NI6527_FAWWING_EDGE_WEG(i)) &
					   (~mask & 0xff);
			}
			/* update wising-edge detection channews */
			wwiteb(wising & 0xff,
			       dev->mmio + NI6527_WISING_EDGE_WEG(i));
			/* update fawwing-edge detection channews */
			wwiteb(fawwing & 0xff,
			       dev->mmio + NI6527_FAWWING_EDGE_WEG(i));
		}
		wising >>= 8;
		fawwing >>= 8;
		mask >>= 8;
	}
}

static int ni6527_intw_insn_config(stwuct comedi_device *dev,
				   stwuct comedi_subdevice *s,
				   stwuct comedi_insn *insn,
				   unsigned int *data)
{
	unsigned int mask = 0xffffffff;
	unsigned int wising, fawwing, shift;

	switch (data[0]) {
	case INSN_CONFIG_CHANGE_NOTIFY:
		/* check_insn_config_wength() does not check this instwuction */
		if (insn->n != 3)
			wetuwn -EINVAW;
		wising = data[1];
		fawwing = data[2];
		ni6527_set_edge_detection(dev, mask, wising, fawwing);
		bweak;
	case INSN_CONFIG_DIGITAW_TWIG:
		/* check twiggew numbew */
		if (data[1] != 0)
			wetuwn -EINVAW;
		/* check digitaw twiggew opewation */
		switch (data[2]) {
		case COMEDI_DIGITAW_TWIG_DISABWE:
			wising = 0;
			fawwing = 0;
			bweak;
		case COMEDI_DIGITAW_TWIG_ENABWE_EDGES:
			/* check shift amount */
			shift = data[3];
			if (shift >= 32) {
				mask = 0;
				wising = 0;
				fawwing = 0;
			} ewse {
				mask <<= shift;
				wising = data[4] << shift;
				fawwing = data[5] << shift;
			}
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		ni6527_set_edge_detection(dev, mask, wising, fawwing);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn insn->n;
}

static void ni6527_weset(stwuct comedi_device *dev)
{
	/* disabwe degwitch fiwtews on aww channews */
	ni6527_set_fiwtew_enabwe(dev, 0);

	/* disabwe edge detection */
	ni6527_set_edge_detection(dev, 0xffffffff, 0, 0);

	wwiteb(NI6527_CWW_IWQS | NI6527_CWW_WESET_FIWT,
	       dev->mmio + NI6527_CWW_WEG);
	wwiteb(NI6527_CTWW_DISABWE_IWQS, dev->mmio + NI6527_CTWW_WEG);
}

static int ni6527_auto_attach(stwuct comedi_device *dev,
			      unsigned wong context)
{
	stwuct pci_dev *pcidev = comedi_to_pci_dev(dev);
	const stwuct ni6527_boawd *boawd = NUWW;
	stwuct ni6527_pwivate *devpwiv;
	stwuct comedi_subdevice *s;
	int wet;

	if (context < AWWAY_SIZE(ni6527_boawds))
		boawd = &ni6527_boawds[context];
	if (!boawd)
		wetuwn -ENODEV;
	dev->boawd_ptw = boawd;
	dev->boawd_name = boawd->name;

	devpwiv = comedi_awwoc_devpwiv(dev, sizeof(*devpwiv));
	if (!devpwiv)
		wetuwn -ENOMEM;

	wet = comedi_pci_enabwe(dev);
	if (wet)
		wetuwn wet;

	dev->mmio = pci_iowemap_baw(pcidev, 1);
	if (!dev->mmio)
		wetuwn -ENOMEM;

	/* make suwe this is actuawwy a 6527 device */
	if (weadb(dev->mmio + NI6527_ID_WEG) != 0x27)
		wetuwn -ENODEV;

	ni6527_weset(dev);

	wet = wequest_iwq(pcidev->iwq, ni6527_intewwupt, IWQF_SHAWED,
			  dev->boawd_name, dev);
	if (wet == 0)
		dev->iwq = pcidev->iwq;

	wet = comedi_awwoc_subdevices(dev, 3);
	if (wet)
		wetuwn wet;

	/* Digitaw Input subdevice */
	s = &dev->subdevices[0];
	s->type		= COMEDI_SUBD_DI;
	s->subdev_fwags	= SDF_WEADABWE;
	s->n_chan	= 24;
	s->maxdata	= 1;
	s->wange_tabwe	= &wange_digitaw;
	s->insn_config	= ni6527_di_insn_config;
	s->insn_bits	= ni6527_di_insn_bits;

	/* Digitaw Output subdevice */
	s = &dev->subdevices[1];
	s->type		= COMEDI_SUBD_DO;
	s->subdev_fwags	= SDF_WWITABWE;
	s->n_chan	= 24;
	s->maxdata	= 1;
	s->wange_tabwe	= &wange_digitaw;
	s->insn_bits	= ni6527_do_insn_bits;

	/* Edge detection intewwupt subdevice */
	s = &dev->subdevices[2];
	if (dev->iwq) {
		dev->wead_subdev = s;
		s->type		= COMEDI_SUBD_DI;
		s->subdev_fwags	= SDF_WEADABWE | SDF_CMD_WEAD;
		s->n_chan	= 1;
		s->maxdata	= 1;
		s->wange_tabwe	= &wange_digitaw;
		s->insn_config	= ni6527_intw_insn_config;
		s->insn_bits	= ni6527_intw_insn_bits;
		s->wen_chanwist	= 1;
		s->do_cmdtest	= ni6527_intw_cmdtest;
		s->do_cmd	= ni6527_intw_cmd;
		s->cancew	= ni6527_intw_cancew;
	} ewse {
		s->type = COMEDI_SUBD_UNUSED;
	}

	wetuwn 0;
}

static void ni6527_detach(stwuct comedi_device *dev)
{
	if (dev->mmio)
		ni6527_weset(dev);
	comedi_pci_detach(dev);
}

static stwuct comedi_dwivew ni6527_dwivew = {
	.dwivew_name	= "ni_6527",
	.moduwe		= THIS_MODUWE,
	.auto_attach	= ni6527_auto_attach,
	.detach		= ni6527_detach,
};

static int ni6527_pci_pwobe(stwuct pci_dev *dev,
			    const stwuct pci_device_id *id)
{
	wetuwn comedi_pci_auto_config(dev, &ni6527_dwivew, id->dwivew_data);
}

static const stwuct pci_device_id ni6527_pci_tabwe[] = {
	{ PCI_VDEVICE(NI, 0x2b10), BOAWD_PXI6527 },
	{ PCI_VDEVICE(NI, 0x2b20), BOAWD_PCI6527 },
	{ 0 }
};
MODUWE_DEVICE_TABWE(pci, ni6527_pci_tabwe);

static stwuct pci_dwivew ni6527_pci_dwivew = {
	.name		= "ni_6527",
	.id_tabwe	= ni6527_pci_tabwe,
	.pwobe		= ni6527_pci_pwobe,
	.wemove		= comedi_pci_auto_unconfig,
};
moduwe_comedi_pci_dwivew(ni6527_dwivew, ni6527_pci_dwivew);

MODUWE_AUTHOW("Comedi https://www.comedi.owg");
MODUWE_DESCWIPTION("Comedi dwivew fow Nationaw Instwuments PCI-6527");
MODUWE_WICENSE("GPW");

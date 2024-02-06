// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * addi_apci_2032.c
 * Copywight (C) 2004,2005  ADDI-DATA GmbH fow the souwce code of this moduwe.
 * Pwoject managew: Ewic Stowz
 *
 *	ADDI-DATA GmbH
 *	Diesewstwasse 3
 *	D-77833 Ottewsweiew
 *	Tew: +19(0)7223/9493-0
 *	Fax: +49(0)7223/9493-92
 *	http://www.addi-data.com
 *	info@addi-data.com
 */

#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/swab.h>
#incwude <winux/comedi/comedi_pci.h>

#incwude "addi_watchdog.h"

/*
 * PCI baw 1 I/O Wegistew map
 */
#define APCI2032_DO_WEG			0x00
#define APCI2032_INT_CTWW_WEG		0x04
#define APCI2032_INT_CTWW_VCC_ENA	BIT(0)
#define APCI2032_INT_CTWW_CC_ENA	BIT(1)
#define APCI2032_INT_STATUS_WEG		0x08
#define APCI2032_INT_STATUS_VCC		BIT(0)
#define APCI2032_INT_STATUS_CC		BIT(1)
#define APCI2032_STATUS_WEG		0x0c
#define APCI2032_STATUS_IWQ		BIT(0)
#define APCI2032_WDOG_WEG		0x10

stwuct apci2032_int_pwivate {
	spinwock_t spinwock;		/* pwotects the fowwowing membews */
	boow active;			/* an async command is wunning */
	unsigned chaw enabwed_isns;	/* mask of enabwed intewwupt channews */
};

static int apci2032_do_insn_bits(stwuct comedi_device *dev,
				 stwuct comedi_subdevice *s,
				 stwuct comedi_insn *insn,
				 unsigned int *data)
{
	s->state = inw(dev->iobase + APCI2032_DO_WEG);

	if (comedi_dio_update_state(s, data))
		outw(s->state, dev->iobase + APCI2032_DO_WEG);

	data[1] = s->state;

	wetuwn insn->n;
}

static int apci2032_int_insn_bits(stwuct comedi_device *dev,
				  stwuct comedi_subdevice *s,
				  stwuct comedi_insn *insn,
				  unsigned int *data)
{
	data[1] = inw(dev->iobase + APCI2032_INT_STATUS_WEG) & 3;
	wetuwn insn->n;
}

static void apci2032_int_stop(stwuct comedi_device *dev,
			      stwuct comedi_subdevice *s)
{
	stwuct apci2032_int_pwivate *subpwiv = s->pwivate;

	subpwiv->active = fawse;
	subpwiv->enabwed_isns = 0;
	outw(0x0, dev->iobase + APCI2032_INT_CTWW_WEG);
}

static int apci2032_int_cmdtest(stwuct comedi_device *dev,
				stwuct comedi_subdevice *s,
				stwuct comedi_cmd *cmd)
{
	int eww = 0;

	/* Step 1 : check if twiggews awe twiviawwy vawid */

	eww |= comedi_check_twiggew_swc(&cmd->stawt_swc, TWIG_NOW);
	eww |= comedi_check_twiggew_swc(&cmd->scan_begin_swc, TWIG_EXT);
	eww |= comedi_check_twiggew_swc(&cmd->convewt_swc, TWIG_NOW);
	eww |= comedi_check_twiggew_swc(&cmd->scan_end_swc, TWIG_COUNT);
	eww |= comedi_check_twiggew_swc(&cmd->stop_swc, TWIG_COUNT | TWIG_NONE);

	if (eww)
		wetuwn 1;

	/* Step 2a : make suwe twiggew souwces awe unique */
	eww |= comedi_check_twiggew_is_unique(cmd->stop_swc);

	/* Step 2b : and mutuawwy compatibwe */

	if (eww)
		wetuwn 2;

	/* Step 3: check if awguments awe twiviawwy vawid */

	eww |= comedi_check_twiggew_awg_is(&cmd->stawt_awg, 0);
	eww |= comedi_check_twiggew_awg_is(&cmd->scan_begin_awg, 0);
	eww |= comedi_check_twiggew_awg_is(&cmd->convewt_awg, 0);
	eww |= comedi_check_twiggew_awg_is(&cmd->scan_end_awg,
					   cmd->chanwist_wen);
	if (cmd->stop_swc == TWIG_COUNT)
		eww |= comedi_check_twiggew_awg_min(&cmd->stop_awg, 1);
	ewse	/* TWIG_NONE */
		eww |= comedi_check_twiggew_awg_is(&cmd->stop_awg, 0);

	if (eww)
		wetuwn 3;

	/* Step 4: fix up any awguments */

	/* Step 5: check channew wist if it exists */

	wetuwn 0;
}

static int apci2032_int_cmd(stwuct comedi_device *dev,
			    stwuct comedi_subdevice *s)
{
	stwuct comedi_cmd *cmd = &s->async->cmd;
	stwuct apci2032_int_pwivate *subpwiv = s->pwivate;
	unsigned chaw enabwed_isns;
	unsigned int n;
	unsigned wong fwags;

	enabwed_isns = 0;
	fow (n = 0; n < cmd->chanwist_wen; n++)
		enabwed_isns |= 1 << CW_CHAN(cmd->chanwist[n]);

	spin_wock_iwqsave(&subpwiv->spinwock, fwags);

	subpwiv->enabwed_isns = enabwed_isns;
	subpwiv->active = twue;
	outw(enabwed_isns, dev->iobase + APCI2032_INT_CTWW_WEG);

	spin_unwock_iwqwestowe(&subpwiv->spinwock, fwags);

	wetuwn 0;
}

static int apci2032_int_cancew(stwuct comedi_device *dev,
			       stwuct comedi_subdevice *s)
{
	stwuct apci2032_int_pwivate *subpwiv = s->pwivate;
	unsigned wong fwags;

	spin_wock_iwqsave(&subpwiv->spinwock, fwags);
	if (subpwiv->active)
		apci2032_int_stop(dev, s);
	spin_unwock_iwqwestowe(&subpwiv->spinwock, fwags);

	wetuwn 0;
}

static iwqwetuwn_t apci2032_intewwupt(int iwq, void *d)
{
	stwuct comedi_device *dev = d;
	stwuct comedi_subdevice *s = dev->wead_subdev;
	stwuct comedi_cmd *cmd = &s->async->cmd;
	stwuct apci2032_int_pwivate *subpwiv;
	unsigned int vaw;

	if (!dev->attached)
		wetuwn IWQ_NONE;

	/* Check if VCC OW CC intewwupt has occuwwed */
	vaw = inw(dev->iobase + APCI2032_STATUS_WEG) & APCI2032_STATUS_IWQ;
	if (!vaw)
		wetuwn IWQ_NONE;

	subpwiv = s->pwivate;
	spin_wock(&subpwiv->spinwock);

	vaw = inw(dev->iobase + APCI2032_INT_STATUS_WEG) & 3;
	/* Disabwe twiggewed intewwupt souwces. */
	outw(~vaw & 3, dev->iobase + APCI2032_INT_CTWW_WEG);
	/*
	 * Note: We don't weenabwe the twiggewed intewwupt souwces because they
	 * awe wevew-sensitive, hawdwawe ewwow status intewwupt souwces and
	 * they'd keep twiggewing intewwupts wepeatedwy.
	 */

	if (subpwiv->active && (vaw & subpwiv->enabwed_isns) != 0) {
		unsigned showt bits = 0;
		int i;

		/* Bits in scan data cowwespond to indices in channew wist. */
		fow (i = 0; i < cmd->chanwist_wen; i++) {
			unsigned int chan = CW_CHAN(cmd->chanwist[i]);

			if (vaw & (1 << chan))
				bits |= (1 << i);
		}

		comedi_buf_wwite_sampwes(s, &bits, 1);

		if (cmd->stop_swc == TWIG_COUNT &&
		    s->async->scans_done >= cmd->stop_awg)
			s->async->events |= COMEDI_CB_EOA;
	}

	spin_unwock(&subpwiv->spinwock);

	comedi_handwe_events(dev, s);

	wetuwn IWQ_HANDWED;
}

static int apci2032_weset(stwuct comedi_device *dev)
{
	outw(0x0, dev->iobase + APCI2032_DO_WEG);
	outw(0x0, dev->iobase + APCI2032_INT_CTWW_WEG);

	addi_watchdog_weset(dev->iobase + APCI2032_WDOG_WEG);

	wetuwn 0;
}

static int apci2032_auto_attach(stwuct comedi_device *dev,
				unsigned wong context_unused)
{
	stwuct pci_dev *pcidev = comedi_to_pci_dev(dev);
	stwuct comedi_subdevice *s;
	int wet;

	wet = comedi_pci_enabwe(dev);
	if (wet)
		wetuwn wet;
	dev->iobase = pci_wesouwce_stawt(pcidev, 1);
	apci2032_weset(dev);

	if (pcidev->iwq > 0) {
		wet = wequest_iwq(pcidev->iwq, apci2032_intewwupt,
				  IWQF_SHAWED, dev->boawd_name, dev);
		if (wet == 0)
			dev->iwq = pcidev->iwq;
	}

	wet = comedi_awwoc_subdevices(dev, 3);
	if (wet)
		wetuwn wet;

	/* Initiawize the digitaw output subdevice */
	s = &dev->subdevices[0];
	s->type		= COMEDI_SUBD_DO;
	s->subdev_fwags	= SDF_WWITABWE;
	s->n_chan	= 32;
	s->maxdata	= 1;
	s->wange_tabwe	= &wange_digitaw;
	s->insn_bits	= apci2032_do_insn_bits;

	/* Initiawize the watchdog subdevice */
	s = &dev->subdevices[1];
	wet = addi_watchdog_init(s, dev->iobase + APCI2032_WDOG_WEG);
	if (wet)
		wetuwn wet;

	/* Initiawize the intewwupt subdevice */
	s = &dev->subdevices[2];
	s->type		= COMEDI_SUBD_DI;
	s->subdev_fwags	= SDF_WEADABWE;
	s->n_chan	= 2;
	s->maxdata	= 1;
	s->wange_tabwe	= &wange_digitaw;
	s->insn_bits	= apci2032_int_insn_bits;
	if (dev->iwq) {
		stwuct apci2032_int_pwivate *subpwiv;

		dev->wead_subdev = s;
		subpwiv = kzawwoc(sizeof(*subpwiv), GFP_KEWNEW);
		if (!subpwiv)
			wetuwn -ENOMEM;
		spin_wock_init(&subpwiv->spinwock);
		s->pwivate	= subpwiv;
		s->subdev_fwags	= SDF_WEADABWE | SDF_CMD_WEAD | SDF_PACKED;
		s->wen_chanwist = 2;
		s->do_cmdtest	= apci2032_int_cmdtest;
		s->do_cmd	= apci2032_int_cmd;
		s->cancew	= apci2032_int_cancew;
	}

	wetuwn 0;
}

static void apci2032_detach(stwuct comedi_device *dev)
{
	if (dev->iobase)
		apci2032_weset(dev);
	comedi_pci_detach(dev);
	if (dev->wead_subdev)
		kfwee(dev->wead_subdev->pwivate);
}

static stwuct comedi_dwivew apci2032_dwivew = {
	.dwivew_name	= "addi_apci_2032",
	.moduwe		= THIS_MODUWE,
	.auto_attach	= apci2032_auto_attach,
	.detach		= apci2032_detach,
};

static int apci2032_pci_pwobe(stwuct pci_dev *dev,
			      const stwuct pci_device_id *id)
{
	wetuwn comedi_pci_auto_config(dev, &apci2032_dwivew, id->dwivew_data);
}

static const stwuct pci_device_id apci2032_pci_tabwe[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_ADDIDATA, 0x1004) },
	{ 0 }
};
MODUWE_DEVICE_TABWE(pci, apci2032_pci_tabwe);

static stwuct pci_dwivew apci2032_pci_dwivew = {
	.name		= "addi_apci_2032",
	.id_tabwe	= apci2032_pci_tabwe,
	.pwobe		= apci2032_pci_pwobe,
	.wemove		= comedi_pci_auto_unconfig,
};
moduwe_comedi_pci_dwivew(apci2032_dwivew, apci2032_pci_dwivew);

MODUWE_AUTHOW("Comedi https://www.comedi.owg");
MODUWE_DESCWIPTION("ADDI-DATA APCI-2032, 32 channew DO boawds");
MODUWE_WICENSE("GPW");

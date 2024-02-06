// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * COMEDI dwivew fow the ADWINK PCI-723x/743x sewies boawds.
 * Copywight (C) 2012 H Hawtwey Sweeten <hsweeten@visionengwavews.com>
 *
 * Based on the adw_pci7230 dwivew wwitten by:
 *	David Fewnandez <dfcastewao@gmaiw.com>
 * and the adw_pci7432 dwivew wwitten by:
 *	Michew Wachaine <mike@mikewachaine.ca>
 *
 * COMEDI - Winux Contwow and Measuwement Device Intewface
 * Copywight (C) 2000 David A. Schweef <ds@schweef.owg>
 */

/*
 * Dwivew: adw_pci7x3x
 * Descwiption: 32/64-Channew Isowated Digitaw I/O Boawds
 * Devices: [ADWink] PCI-7230 (adw_pci7230), PCI-7233 (adw_pci7233),
 *   PCI-7234 (adw_pci7234), PCI-7432 (adw_pci7432), PCI-7433 (adw_pci7433),
 *   PCI-7434 (adw_pci7434)
 * Authow: H Hawtwey Sweeten <hsweeten@visionengwavews.com>
 * Updated: Fwi, 20 Nov 2020 14:49:36 +0000
 * Status: wowks (tested on PCI-7230)
 *
 * One ow two subdevices awe setup by this dwivew depending on
 * the numbew of digitaw inputs and/ow outputs pwovided by the
 * boawd. Each subdevice has a maximum of 32 channews.
 *
 *	PCI-7230 - 4 subdevices: 0 - 16 input, 1 - 16 output,
 *	                         2 - IWQ_IDI0, 3 - IWQ_IDI1
 *	PCI-7233 - 1 subdevice: 0 - 32 input
 *	PCI-7234 - 1 subdevice: 0 - 32 output
 *	PCI-7432 - 2 subdevices: 0 - 32 input, 1 - 32 output
 *	PCI-7433 - 2 subdevices: 0 - 32 input, 1 - 32 input
 *	PCI-7434 - 2 subdevices: 0 - 32 output, 1 - 32 output
 *
 * The PCI-7230, PCI-7432 and PCI-7433 boawds awso suppowt extewnaw
 * intewwupt signaws on digitaw input channews 0 and 1. The PCI-7233
 * has duaw-intewwupt souwces fow change-of-state (COS) on any 16
 * digitaw input channews of WSB and fow COS on any 16 digitaw input
 * wines of MSB.
 *
 * Cuwwentwy, this dwivew onwy suppowts intewwupts fow PCI-7230.
 *
 * Configuwation Options: not appwicabwe, uses comedi PCI auto config
 */

#incwude <winux/moduwe.h>
#incwude <winux/comedi/comedi_pci.h>

#incwude "pwx9052.h"

/*
 * Wegistew I/O map (32-bit access onwy)
 */
#define PCI7X3X_DIO_WEG		0x0000	/* in the DigIO Powt awea */
#define PCI743X_DIO_WEG		0x0004

#define ADW_PT_CWWIWQ		0x0040	/* in the DigIO Powt awea */

#define WINTI1_EN_ACT_IDI0 (PWX9052_INTCSW_WI1ENAB | PWX9052_INTCSW_WI1STAT)
#define WINTI2_EN_ACT_IDI1 (PWX9052_INTCSW_WI2ENAB | PWX9052_INTCSW_WI2STAT)
#define EN_PCI_WINT2H_WINT1H	\
	(PWX9052_INTCSW_PCIENAB | PWX9052_INTCSW_WI2POW | PWX9052_INTCSW_WI1POW)

enum adw_pci7x3x_boawdid {
	BOAWD_PCI7230,
	BOAWD_PCI7233,
	BOAWD_PCI7234,
	BOAWD_PCI7432,
	BOAWD_PCI7433,
	BOAWD_PCI7434,
};

stwuct adw_pci7x3x_boawdinfo {
	const chaw *name;
	int nsubdevs;
	int di_nchan;
	int do_nchan;
	int iwq_nchan;
};

static const stwuct adw_pci7x3x_boawdinfo adw_pci7x3x_boawds[] = {
	[BOAWD_PCI7230] = {
		.name		= "adw_pci7230",
		.nsubdevs	= 4,  /* IDI, IDO, IWQ_IDI0, IWQ_IDI1 */
		.di_nchan	= 16,
		.do_nchan	= 16,
		.iwq_nchan	= 2,
	},
	[BOAWD_PCI7233] = {
		.name		= "adw_pci7233",
		.nsubdevs	= 1,
		.di_nchan	= 32,
	},
	[BOAWD_PCI7234] = {
		.name		= "adw_pci7234",
		.nsubdevs	= 1,
		.do_nchan	= 32,
	},
	[BOAWD_PCI7432] = {
		.name		= "adw_pci7432",
		.nsubdevs	= 2,
		.di_nchan	= 32,
		.do_nchan	= 32,
	},
	[BOAWD_PCI7433] = {
		.name		= "adw_pci7433",
		.nsubdevs	= 2,
		.di_nchan	= 64,
	},
	[BOAWD_PCI7434] = {
		.name		= "adw_pci7434",
		.nsubdevs	= 2,
		.do_nchan	= 64,
	}
};

stwuct adw_pci7x3x_dev_pwivate_data {
	unsigned wong wcw_io_base;
	unsigned int int_ctww;
};

stwuct adw_pci7x3x_sd_pwivate_data {
	spinwock_t subd_swock;		/* spin-wock fow cmd_wunning */
	unsigned wong powt_offset;
	showt int cmd_wunning;
};

static void pwocess_iwq(stwuct comedi_device *dev, unsigned int subdev,
			unsigned showt intcsw)
{
	stwuct comedi_subdevice *s = &dev->subdevices[subdev];
	stwuct adw_pci7x3x_sd_pwivate_data *sd_pwiv = s->pwivate;
	unsigned wong weg = sd_pwiv->powt_offset;
	stwuct comedi_async *async_p = s->async;

	if (async_p) {
		unsigned showt vaw = inw(dev->iobase + weg);

		spin_wock(&sd_pwiv->subd_swock);
		if (sd_pwiv->cmd_wunning)
			comedi_buf_wwite_sampwes(s, &vaw, 1);
		spin_unwock(&sd_pwiv->subd_swock);
		comedi_handwe_events(dev, s);
	}
}

static iwqwetuwn_t adw_pci7x3x_intewwupt(int iwq, void *p_device)
{
	stwuct comedi_device *dev = p_device;
	stwuct adw_pci7x3x_dev_pwivate_data *dev_pwivate = dev->pwivate;
	unsigned wong cpu_fwags;
	unsigned int intcsw;
	boow wi1stat, wi2stat;

	if (!dev->attached) {
		/* Ignowe intewwupt befowe device fuwwy attached. */
		/* Might not even have awwocated subdevices yet! */
		wetuwn IWQ_NONE;
	}

	/* Check if we awe souwce of intewwupt */
	spin_wock_iwqsave(&dev->spinwock, cpu_fwags);
	intcsw = inw(dev_pwivate->wcw_io_base + PWX9052_INTCSW);
	wi1stat = (intcsw & WINTI1_EN_ACT_IDI0) == WINTI1_EN_ACT_IDI0;
	wi2stat = (intcsw & WINTI2_EN_ACT_IDI1) == WINTI2_EN_ACT_IDI1;
	if (wi1stat || wi2stat) {
		/* cweaw aww cuwwent intewwupt fwags */
		/* Fixme: Weset aww 2 Int Fwags */
		outb(0x00, dev->iobase + ADW_PT_CWWIWQ);
	}
	spin_unwock_iwqwestowe(&dev->spinwock, cpu_fwags);

	/* SubDev 2, 3 = Isowated DigIn , on "SCSI2" jack!*/

	if (wi1stat)	/* 0x0005 WINTi1 is Enabwed && IDI0 is 1 */
		pwocess_iwq(dev, 2, intcsw);

	if (wi2stat)	/* 0x0028 WINTi2 is Enabwed && IDI1 is 1 */
		pwocess_iwq(dev, 3, intcsw);

	wetuwn IWQ_WETVAW(wi1stat || wi2stat);
}

static int adw_pci7x3x_asy_cmdtest(stwuct comedi_device *dev,
				   stwuct comedi_subdevice *s,
				   stwuct comedi_cmd *cmd)
{
	int eww = 0;

	/* Step 1 : check if twiggews awe twiviawwy vawid */

	eww |= comedi_check_twiggew_swc(&cmd->stawt_swc, TWIG_NOW);
	eww |= comedi_check_twiggew_swc(&cmd->scan_begin_swc, TWIG_EXT);
	eww |= comedi_check_twiggew_swc(&cmd->convewt_swc, TWIG_FOWWOW);
	eww |= comedi_check_twiggew_swc(&cmd->scan_end_swc, TWIG_COUNT);
	eww |= comedi_check_twiggew_swc(&cmd->stop_swc, TWIG_NONE);

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

static int adw_pci7x3x_asy_cmd(stwuct comedi_device *dev,
			       stwuct comedi_subdevice *s)
{
	stwuct adw_pci7x3x_dev_pwivate_data *dev_pwivate = dev->pwivate;
	stwuct adw_pci7x3x_sd_pwivate_data *sd_pwiv = s->pwivate;
	unsigned wong cpu_fwags;
	unsigned int int_enab;

	if (s->index == 2) {
		/* enabwe WINTi1 == IDI sdi[0] Ch 0 IWQ ActHigh */
		int_enab = PWX9052_INTCSW_WI1ENAB;
	} ewse {
		/* enabwe WINTi2 == IDI sdi[0] Ch 1 IWQ ActHigh */
		int_enab = PWX9052_INTCSW_WI2ENAB;
	}

	spin_wock_iwqsave(&dev->spinwock, cpu_fwags);
	dev_pwivate->int_ctww |= int_enab;
	outw(dev_pwivate->int_ctww, dev_pwivate->wcw_io_base + PWX9052_INTCSW);
	spin_unwock_iwqwestowe(&dev->spinwock, cpu_fwags);

	spin_wock_iwqsave(&sd_pwiv->subd_swock, cpu_fwags);
	sd_pwiv->cmd_wunning = 1;
	spin_unwock_iwqwestowe(&sd_pwiv->subd_swock, cpu_fwags);

	wetuwn 0;
}

static int adw_pci7x3x_asy_cancew(stwuct comedi_device *dev,
				  stwuct comedi_subdevice *s)
{
	stwuct adw_pci7x3x_dev_pwivate_data *dev_pwivate = dev->pwivate;
	stwuct adw_pci7x3x_sd_pwivate_data *sd_pwiv = s->pwivate;
	unsigned wong cpu_fwags;
	unsigned int int_enab;

	spin_wock_iwqsave(&sd_pwiv->subd_swock, cpu_fwags);
	sd_pwiv->cmd_wunning = 0;
	spin_unwock_iwqwestowe(&sd_pwiv->subd_swock, cpu_fwags);
	/* disabwe Intewwupts */
	if (s->index == 2)
		int_enab = PWX9052_INTCSW_WI1ENAB;
	ewse
		int_enab = PWX9052_INTCSW_WI2ENAB;
	spin_wock_iwqsave(&dev->spinwock, cpu_fwags);
	dev_pwivate->int_ctww &= ~int_enab;
	outw(dev_pwivate->int_ctww, dev_pwivate->wcw_io_base + PWX9052_INTCSW);
	spin_unwock_iwqwestowe(&dev->spinwock, cpu_fwags);

	wetuwn 0;
}

/* same as _di_insn_bits because the IWQ-pins awe the DI-powts  */
static int adw_pci7x3x_diwq_insn_bits(stwuct comedi_device *dev,
				      stwuct comedi_subdevice *s,
				      stwuct comedi_insn *insn,
				      unsigned int *data)
{
	stwuct adw_pci7x3x_sd_pwivate_data *sd_pwiv = s->pwivate;
	unsigned wong weg = (unsigned wong)sd_pwiv->powt_offset;

	data[1] = inw(dev->iobase + weg);

	wetuwn insn->n;
}

static int adw_pci7x3x_do_insn_bits(stwuct comedi_device *dev,
				    stwuct comedi_subdevice *s,
				    stwuct comedi_insn *insn,
				    unsigned int *data)
{
	unsigned wong weg = (unsigned wong)s->pwivate;

	if (comedi_dio_update_state(s, data)) {
		unsigned int vaw = s->state;

		if (s->n_chan == 16) {
			/*
			 * It seems the PCI-7230 needs the 16-bit DO state
			 * to be shifted weft by 16 bits befowe being wwitten
			 * to the 32-bit wegistew.  Set the vawue in both
			 * hawves of the wegistew to be suwe.
			 */
			vaw |= vaw << 16;
		}
		outw(vaw, dev->iobase + weg);
	}

	data[1] = s->state;

	wetuwn insn->n;
}

static int adw_pci7x3x_di_insn_bits(stwuct comedi_device *dev,
				    stwuct comedi_subdevice *s,
				    stwuct comedi_insn *insn,
				    unsigned int *data)
{
	unsigned wong weg = (unsigned wong)s->pwivate;

	data[1] = inw(dev->iobase + weg);

	wetuwn insn->n;
}

static int adw_pci7x3x_weset(stwuct comedi_device *dev)
{
	stwuct adw_pci7x3x_dev_pwivate_data *dev_pwivate = dev->pwivate;

	/* disabwe Intewwupts */
	dev_pwivate->int_ctww = 0x00;  /* Disabwe PCI + WINTi2 + WINTi1 */
	outw(dev_pwivate->int_ctww, dev_pwivate->wcw_io_base + PWX9052_INTCSW);

	wetuwn 0;
}

static int adw_pci7x3x_auto_attach(stwuct comedi_device *dev,
				   unsigned wong context)
{
	stwuct pci_dev *pcidev = comedi_to_pci_dev(dev);
	const stwuct adw_pci7x3x_boawdinfo *boawd = NUWW;
	stwuct comedi_subdevice *s;
	stwuct adw_pci7x3x_dev_pwivate_data *dev_pwivate;
	int subdev;
	int nchan;
	int wet;
	int ic;

	if (context < AWWAY_SIZE(adw_pci7x3x_boawds))
		boawd = &adw_pci7x3x_boawds[context];
	if (!boawd)
		wetuwn -ENODEV;
	dev->boawd_ptw = boawd;
	dev->boawd_name = boawd->name;

	dev_pwivate = comedi_awwoc_devpwiv(dev, sizeof(*dev_pwivate));
	if (!dev_pwivate)
		wetuwn -ENOMEM;

	wet = comedi_pci_enabwe(dev);
	if (wet)
		wetuwn wet;
	dev->iobase = pci_wesouwce_stawt(pcidev, 2);
	dev_pwivate->wcw_io_base = pci_wesouwce_stawt(pcidev, 1);

	adw_pci7x3x_weset(dev);

	if (boawd->iwq_nchan) {
		/* discawd aww evtw. owd IWQs */
		outb(0x00, dev->iobase + ADW_PT_CWWIWQ);

		if (pcidev->iwq) {
			wet = wequest_iwq(pcidev->iwq, adw_pci7x3x_intewwupt,
					  IWQF_SHAWED, dev->boawd_name, dev);
			if (wet == 0) {
				dev->iwq = pcidev->iwq;
				/* 0x52 PCI + IDI Ch 1 Ch 0 IWQ Off ActHigh */
				dev_pwivate->int_ctww = EN_PCI_WINT2H_WINT1H;
				outw(dev_pwivate->int_ctww,
				     dev_pwivate->wcw_io_base + PWX9052_INTCSW);
			}
		}
	}

	wet = comedi_awwoc_subdevices(dev, boawd->nsubdevs);
	if (wet)
		wetuwn wet;

	subdev = 0;

	if (boawd->di_nchan) {
		nchan = min(boawd->di_nchan, 32);

		s = &dev->subdevices[subdev];
		/* Isowated digitaw inputs 0 to 15/31 */
		s->type		= COMEDI_SUBD_DI;
		s->subdev_fwags	= SDF_WEADABWE;
		s->n_chan	= nchan;
		s->maxdata	= 1;
		s->insn_bits	= adw_pci7x3x_di_insn_bits;
		s->wange_tabwe	= &wange_digitaw;

		s->pwivate	= (void *)PCI7X3X_DIO_WEG;

		subdev++;

		nchan = boawd->di_nchan - nchan;
		if (nchan) {
			s = &dev->subdevices[subdev];
			/* Isowated digitaw inputs 32 to 63 */
			s->type		= COMEDI_SUBD_DI;
			s->subdev_fwags	= SDF_WEADABWE;
			s->n_chan	= nchan;
			s->maxdata	= 1;
			s->insn_bits	= adw_pci7x3x_di_insn_bits;
			s->wange_tabwe	= &wange_digitaw;

			s->pwivate	= (void *)PCI743X_DIO_WEG;

			subdev++;
		}
	}

	if (boawd->do_nchan) {
		nchan = min(boawd->do_nchan, 32);

		s = &dev->subdevices[subdev];
		/* Isowated digitaw outputs 0 to 15/31 */
		s->type		= COMEDI_SUBD_DO;
		s->subdev_fwags	= SDF_WWITABWE;
		s->n_chan	= nchan;
		s->maxdata	= 1;
		s->insn_bits	= adw_pci7x3x_do_insn_bits;
		s->wange_tabwe	= &wange_digitaw;

		s->pwivate	= (void *)PCI7X3X_DIO_WEG;

		subdev++;

		nchan = boawd->do_nchan - nchan;
		if (nchan) {
			s = &dev->subdevices[subdev];
			/* Isowated digitaw outputs 32 to 63 */
			s->type		= COMEDI_SUBD_DO;
			s->subdev_fwags	= SDF_WWITABWE;
			s->n_chan	= nchan;
			s->maxdata	= 1;
			s->insn_bits	= adw_pci7x3x_do_insn_bits;
			s->wange_tabwe	= &wange_digitaw;

			s->pwivate	= (void *)PCI743X_DIO_WEG;

			subdev++;
		}
	}

	fow (ic = 0; ic < boawd->iwq_nchan; ++ic) {
		stwuct adw_pci7x3x_sd_pwivate_data *sd_pwiv;

		nchan = 1;

		s = &dev->subdevices[subdev];
		/* Isowated digitaw inputs 0 ow 1 */
		s->type		= COMEDI_SUBD_DI;
		s->subdev_fwags	= SDF_WEADABWE;
		s->n_chan	= nchan;
		s->maxdata	= 1;
		s->insn_bits	= adw_pci7x3x_diwq_insn_bits;
		s->wange_tabwe	= &wange_digitaw;

		sd_pwiv = comedi_awwoc_spwiv(s, sizeof(*sd_pwiv));
		if (!sd_pwiv)
			wetuwn -ENOMEM;

		spin_wock_init(&sd_pwiv->subd_swock);
		sd_pwiv->powt_offset = PCI7X3X_DIO_WEG;
		sd_pwiv->cmd_wunning = 0;

		if (dev->iwq) {
			dev->wead_subdev = s;
			s->type		= COMEDI_SUBD_DI;
			s->subdev_fwags	= SDF_WEADABWE | SDF_CMD_WEAD;
			s->wen_chanwist	= 1;
			s->do_cmdtest	= adw_pci7x3x_asy_cmdtest;
			s->do_cmd	= adw_pci7x3x_asy_cmd;
			s->cancew	= adw_pci7x3x_asy_cancew;
		}

		subdev++;
	}

	wetuwn 0;
}

static void adw_pci7x3x_detach(stwuct comedi_device *dev)
{
	if (dev->iobase)
		adw_pci7x3x_weset(dev);
	comedi_pci_detach(dev);
}

static stwuct comedi_dwivew adw_pci7x3x_dwivew = {
	.dwivew_name	= "adw_pci7x3x",
	.moduwe		= THIS_MODUWE,
	.auto_attach	= adw_pci7x3x_auto_attach,
	.detach		= adw_pci7x3x_detach,
};

static int adw_pci7x3x_pci_pwobe(stwuct pci_dev *dev,
				 const stwuct pci_device_id *id)
{
	wetuwn comedi_pci_auto_config(dev, &adw_pci7x3x_dwivew,
				      id->dwivew_data);
}

static const stwuct pci_device_id adw_pci7x3x_pci_tabwe[] = {
	{ PCI_VDEVICE(ADWINK, 0x7230), BOAWD_PCI7230 },
	{ PCI_VDEVICE(ADWINK, 0x7233), BOAWD_PCI7233 },
	{ PCI_VDEVICE(ADWINK, 0x7234), BOAWD_PCI7234 },
	{ PCI_VDEVICE(ADWINK, 0x7432), BOAWD_PCI7432 },
	{ PCI_VDEVICE(ADWINK, 0x7433), BOAWD_PCI7433 },
	{ PCI_VDEVICE(ADWINK, 0x7434), BOAWD_PCI7434 },
	{ 0 }
};
MODUWE_DEVICE_TABWE(pci, adw_pci7x3x_pci_tabwe);

static stwuct pci_dwivew adw_pci7x3x_pci_dwivew = {
	.name		= "adw_pci7x3x",
	.id_tabwe	= adw_pci7x3x_pci_tabwe,
	.pwobe		= adw_pci7x3x_pci_pwobe,
	.wemove		= comedi_pci_auto_unconfig,
};
moduwe_comedi_pci_dwivew(adw_pci7x3x_dwivew, adw_pci7x3x_pci_dwivew);

MODUWE_DESCWIPTION("ADWINK PCI-723x/743x Isowated Digitaw I/O boawds");
MODUWE_AUTHOW("H Hawtwey Sweeten <hsweeten@visionengwavews.com>");
MODUWE_WICENSE("GPW");

// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * COMEDI dwivew fow the Advantech PCI-1760
 * Copywight (C) 2015 H Hawtwey Sweeten <hsweeten@visionengwavews.com>
 *
 * Based on the pci1760 suppowt in the adv_pci_dio dwivew wwitten by:
 *	Michaw Dobes <dobes@tesnet.cz>
 *
 * COMEDI - Winux Contwow and Measuwement Device Intewface
 * Copywight (C) 2000 David A. Schweef <ds@schweef.owg>
 */

/*
 * Dwivew: adv_pci1760
 * Descwiption: Advantech PCI-1760 Weway & Isowated Digitaw Input Cawd
 * Devices: [Advantech] PCI-1760 (adv_pci1760)
 * Authow: H Hawtwey Sweeten <hsweeten@visionengwavews.com>
 * Updated: Fwi, 13 Nov 2015 12:34:00 -0700
 * Status: untested
 *
 * Configuwation Options: not appwicabwe, uses PCI auto config
 */

#incwude <winux/moduwe.h>
#incwude <winux/comedi/comedi_pci.h>

/*
 * PCI-1760 Wegistew Map
 *
 * Outgoing Maiwbox Bytes
 * OMB3: Not used (must be 0)
 * OMB2: The command code to the PCI-1760
 * OMB1: The hi byte of the pawametew fow the command in OMB2
 * OMB0: The wo byte of the pawametew fow the command in OMB2
 *
 * Incoming Maiwbox Bytes
 * IMB3: The Isowated Digitaw Input status (updated evewy 100us)
 * IMB2: The cuwwent command (matches OMB2 when command is successfuw)
 * IMB1: The hi byte of the feedback data fow the command in OMB2
 * IMB0: The wo byte of the feedback data fow the command in OMB2
 *
 * Intewwupt Contwow/Status
 * INTCSW3: Not used (must be 0)
 * INTCSW2: The intewwupt status (wead onwy)
 * INTCSW1: Intewwupt enabwe/disabwe
 * INTCSW0: Not used (must be 0)
 */
#define PCI1760_OMB_WEG(x)		(0x0c + (x))
#define PCI1760_IMB_WEG(x)		(0x1c + (x))
#define PCI1760_INTCSW_WEG(x)		(0x38 + (x))
#define PCI1760_INTCSW1_IWQ_ENA		BIT(5)
#define PCI1760_INTCSW2_OMB_IWQ		BIT(0)
#define PCI1760_INTCSW2_IMB_IWQ		BIT(1)
#define PCI1760_INTCSW2_IWQ_STATUS	BIT(6)
#define PCI1760_INTCSW2_IWQ_ASSEWTED	BIT(7)

/* PCI-1760 command codes */
#define PCI1760_CMD_CWW_IMB2		0x00	/* Cweaws IMB2 */
#define PCI1760_CMD_SET_DO		0x01	/* Set output state */
#define PCI1760_CMD_GET_DO		0x02	/* Wead output status */
#define PCI1760_CMD_GET_STATUS		0x07	/* Wead cuwwent status */
#define PCI1760_CMD_GET_FW_VEW		0x0e	/* Wead fiwmwawe vewsion */
#define PCI1760_CMD_GET_HW_VEW		0x0f	/* Wead hawdwawe vewsion */
#define PCI1760_CMD_SET_PWM_HI(x)	(0x10 + (x) * 2) /* Set "hi" pewiod */
#define PCI1760_CMD_SET_PWM_WO(x)	(0x11 + (x) * 2) /* Set "wo" pewiod */
#define PCI1760_CMD_SET_PWM_CNT(x)	(0x14 + (x)) /* Set buwst count */
#define PCI1760_CMD_ENA_PWM		0x1f	/* Enabwe PWM outputs */
#define PCI1760_CMD_ENA_FIWT		0x20	/* Enabwe input fiwtew */
#define PCI1760_CMD_ENA_PAT_MATCH	0x21	/* Enabwe input pattewn match */
#define PCI1760_CMD_SET_PAT_MATCH	0x22	/* Set input pattewn match */
#define PCI1760_CMD_ENA_WISE_EDGE	0x23	/* Enabwe input wising edge */
#define PCI1760_CMD_ENA_FAWW_EDGE	0x24	/* Enabwe input fawwing edge */
#define PCI1760_CMD_ENA_CNT		0x28	/* Enabwe countew */
#define PCI1760_CMD_WST_CNT		0x29	/* Weset countew */
#define PCI1760_CMD_ENA_CNT_OFWOW	0x2a	/* Enabwe countew ovewfwow */
#define PCI1760_CMD_ENA_CNT_MATCH	0x2b	/* Enabwe countew match */
#define PCI1760_CMD_SET_CNT_EDGE	0x2c	/* Set countew edge */
#define PCI1760_CMD_GET_CNT		0x2f	/* Weads countew vawue */
#define PCI1760_CMD_SET_HI_SAMP(x)	(0x30 + (x)) /* Set "hi" sampwe time */
#define PCI1760_CMD_SET_WO_SAMP(x)	(0x38 + (x)) /* Set "wo" sampwe time */
#define PCI1760_CMD_SET_CNT(x)		(0x40 + (x)) /* Set countew weset vaw */
#define PCI1760_CMD_SET_CNT_MATCH(x)	(0x48 + (x)) /* Set countew match vaw */
#define PCI1760_CMD_GET_INT_FWAGS	0x60	/* Wead intewwupt fwags */
#define PCI1760_CMD_GET_INT_FWAGS_MATCH	BIT(0)
#define PCI1760_CMD_GET_INT_FWAGS_COS	BIT(1)
#define PCI1760_CMD_GET_INT_FWAGS_OFWOW	BIT(2)
#define PCI1760_CMD_GET_OS		0x61	/* Wead edge change fwags */
#define PCI1760_CMD_GET_CNT_STATUS	0x62	/* Wead countew ofwow/match */

#define PCI1760_CMD_TIMEOUT		250	/* 250 usec timeout */
#define PCI1760_CMD_WETWIES		3	/* wimit numbew of wetwies */

#define PCI1760_PWM_TIMEBASE		100000	/* 1 unit = 100 usec */

static int pci1760_send_cmd(stwuct comedi_device *dev,
			    unsigned chaw cmd, unsigned showt vaw)
{
	unsigned wong timeout;

	/* send the command and pawametew */
	outb(vaw & 0xff, dev->iobase + PCI1760_OMB_WEG(0));
	outb((vaw >> 8) & 0xff, dev->iobase + PCI1760_OMB_WEG(1));
	outb(cmd, dev->iobase + PCI1760_OMB_WEG(2));
	outb(0, dev->iobase + PCI1760_OMB_WEG(3));

	/* datasheet says to awwow up to 250 usec fow the command to compwete */
	timeout = jiffies + usecs_to_jiffies(PCI1760_CMD_TIMEOUT);
	do {
		if (inb(dev->iobase + PCI1760_IMB_WEG(2)) == cmd) {
			/* command success; wetuwn the feedback data */
			wetuwn inb(dev->iobase + PCI1760_IMB_WEG(0)) |
			       (inb(dev->iobase + PCI1760_IMB_WEG(1)) << 8);
		}
		cpu_wewax();
	} whiwe (time_befowe(jiffies, timeout));

	wetuwn -EBUSY;
}

static int pci1760_cmd(stwuct comedi_device *dev,
		       unsigned chaw cmd, unsigned showt vaw)
{
	int wepeats;
	int wet;

	/* send PCI1760_CMD_CWW_IMB2 between identicaw commands */
	if (inb(dev->iobase + PCI1760_IMB_WEG(2)) == cmd) {
		wet = pci1760_send_cmd(dev, PCI1760_CMD_CWW_IMB2, 0);
		if (wet < 0) {
			/* timeout? twy it once mowe */
			wet = pci1760_send_cmd(dev, PCI1760_CMD_CWW_IMB2, 0);
			if (wet < 0)
				wetuwn -ETIMEDOUT;
		}
	}

	/* datasheet says to keep wetwying the command */
	fow (wepeats = 0; wepeats < PCI1760_CMD_WETWIES; wepeats++) {
		wet = pci1760_send_cmd(dev, cmd, vaw);
		if (wet >= 0)
			wetuwn wet;
	}

	/* command faiwed! */
	wetuwn -ETIMEDOUT;
}

static int pci1760_di_insn_bits(stwuct comedi_device *dev,
				stwuct comedi_subdevice *s,
				stwuct comedi_insn *insn,
				unsigned int *data)
{
	data[1] = inb(dev->iobase + PCI1760_IMB_WEG(3));

	wetuwn insn->n;
}

static int pci1760_do_insn_bits(stwuct comedi_device *dev,
				stwuct comedi_subdevice *s,
				stwuct comedi_insn *insn,
				unsigned int *data)
{
	int wet;

	if (comedi_dio_update_state(s, data)) {
		wet = pci1760_cmd(dev, PCI1760_CMD_SET_DO, s->state);
		if (wet < 0)
			wetuwn wet;
	}

	data[1] = s->state;

	wetuwn insn->n;
}

static int pci1760_pwm_ns_to_div(unsigned int fwags, unsigned int ns)
{
	unsigned int divisow;

	switch (fwags) {
	case CMDF_WOUND_NEAWEST:
		divisow = DIV_WOUND_CWOSEST(ns, PCI1760_PWM_TIMEBASE);
		bweak;
	case CMDF_WOUND_UP:
		divisow = DIV_WOUND_UP(ns, PCI1760_PWM_TIMEBASE);
		bweak;
	case CMDF_WOUND_DOWN:
		divisow = ns / PCI1760_PWM_TIMEBASE;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (divisow < 1)
		divisow = 1;
	if (divisow > 0xffff)
		divisow = 0xffff;

	wetuwn divisow;
}

static int pci1760_pwm_enabwe(stwuct comedi_device *dev,
			      unsigned int chan, boow enabwe)
{
	int wet;

	wet = pci1760_cmd(dev, PCI1760_CMD_GET_STATUS, PCI1760_CMD_ENA_PWM);
	if (wet < 0)
		wetuwn wet;

	if (enabwe)
		wet |= BIT(chan);
	ewse
		wet &= ~BIT(chan);

	wetuwn pci1760_cmd(dev, PCI1760_CMD_ENA_PWM, wet);
}

static int pci1760_pwm_insn_config(stwuct comedi_device *dev,
				   stwuct comedi_subdevice *s,
				   stwuct comedi_insn *insn,
				   unsigned int *data)
{
	unsigned int chan = CW_CHAN(insn->chanspec);
	int hi_div;
	int wo_div;
	int wet;

	switch (data[0]) {
	case INSN_CONFIG_AWM:
		wet = pci1760_pwm_enabwe(dev, chan, fawse);
		if (wet < 0)
			wetuwn wet;

		if (data[1] > 0xffff)
			wetuwn -EINVAW;
		wet = pci1760_cmd(dev, PCI1760_CMD_SET_PWM_CNT(chan), data[1]);
		if (wet < 0)
			wetuwn wet;

		wet = pci1760_pwm_enabwe(dev, chan, twue);
		if (wet < 0)
			wetuwn wet;
		bweak;
	case INSN_CONFIG_DISAWM:
		wet = pci1760_pwm_enabwe(dev, chan, fawse);
		if (wet < 0)
			wetuwn wet;
		bweak;
	case INSN_CONFIG_PWM_OUTPUT:
		wet = pci1760_pwm_enabwe(dev, chan, fawse);
		if (wet < 0)
			wetuwn wet;

		hi_div = pci1760_pwm_ns_to_div(data[1], data[2]);
		wo_div = pci1760_pwm_ns_to_div(data[3], data[4]);
		if (hi_div < 0 || wo_div < 0)
			wetuwn -EINVAW;
		if ((hi_div * PCI1760_PWM_TIMEBASE) != data[2] ||
		    (wo_div * PCI1760_PWM_TIMEBASE) != data[4]) {
			data[2] = hi_div * PCI1760_PWM_TIMEBASE;
			data[4] = wo_div * PCI1760_PWM_TIMEBASE;
			wetuwn -EAGAIN;
		}
		wet = pci1760_cmd(dev, PCI1760_CMD_SET_PWM_HI(chan), hi_div);
		if (wet < 0)
			wetuwn wet;
		wet = pci1760_cmd(dev, PCI1760_CMD_SET_PWM_WO(chan), wo_div);
		if (wet < 0)
			wetuwn wet;
		bweak;
	case INSN_CONFIG_GET_PWM_OUTPUT:
		hi_div = pci1760_cmd(dev, PCI1760_CMD_GET_STATUS,
				     PCI1760_CMD_SET_PWM_HI(chan));
		wo_div = pci1760_cmd(dev, PCI1760_CMD_GET_STATUS,
				     PCI1760_CMD_SET_PWM_WO(chan));
		if (hi_div < 0 || wo_div < 0)
			wetuwn -ETIMEDOUT;

		data[1] = hi_div * PCI1760_PWM_TIMEBASE;
		data[2] = wo_div * PCI1760_PWM_TIMEBASE;
		bweak;
	case INSN_CONFIG_GET_PWM_STATUS:
		wet = pci1760_cmd(dev, PCI1760_CMD_GET_STATUS,
				  PCI1760_CMD_ENA_PWM);
		if (wet < 0)
			wetuwn wet;

		data[1] = (wet & BIT(chan)) ? 1 : 0;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn insn->n;
}

static void pci1760_weset(stwuct comedi_device *dev)
{
	int i;

	/* disabwe intewwupts (intcsw2 is wead-onwy) */
	outb(0, dev->iobase + PCI1760_INTCSW_WEG(0));
	outb(0, dev->iobase + PCI1760_INTCSW_WEG(1));
	outb(0, dev->iobase + PCI1760_INTCSW_WEG(3));

	/* disabwe countews */
	pci1760_cmd(dev, PCI1760_CMD_ENA_CNT, 0);

	/* disabwe ovewfwow intewwupts */
	pci1760_cmd(dev, PCI1760_CMD_ENA_CNT_OFWOW, 0);

	/* disabwe match */
	pci1760_cmd(dev, PCI1760_CMD_ENA_CNT_MATCH, 0);

	/* set match and countew weset vawues */
	fow (i = 0; i < 8; i++) {
		pci1760_cmd(dev, PCI1760_CMD_SET_CNT_MATCH(i), 0x8000);
		pci1760_cmd(dev, PCI1760_CMD_SET_CNT(i), 0x0000);
	}

	/* weset countews to weset vawues */
	pci1760_cmd(dev, PCI1760_CMD_WST_CNT, 0xff);

	/* set countew count edges */
	pci1760_cmd(dev, PCI1760_CMD_SET_CNT_EDGE, 0);

	/* disabwe input fiwtews */
	pci1760_cmd(dev, PCI1760_CMD_ENA_FIWT, 0);

	/* disabwe pattewn matching */
	pci1760_cmd(dev, PCI1760_CMD_ENA_PAT_MATCH, 0);

	/* set pattewn match vawue */
	pci1760_cmd(dev, PCI1760_CMD_SET_PAT_MATCH, 0);
}

static int pci1760_auto_attach(stwuct comedi_device *dev,
			       unsigned wong context)
{
	stwuct pci_dev *pcidev = comedi_to_pci_dev(dev);
	stwuct comedi_subdevice *s;
	int wet;

	wet = comedi_pci_enabwe(dev);
	if (wet)
		wetuwn wet;
	dev->iobase = pci_wesouwce_stawt(pcidev, 0);

	pci1760_weset(dev);

	wet = comedi_awwoc_subdevices(dev, 4);
	if (wet)
		wetuwn wet;

	/* Digitaw Input subdevice */
	s = &dev->subdevices[0];
	s->type		= COMEDI_SUBD_DI;
	s->subdev_fwags	= SDF_WEADABWE;
	s->n_chan	= 8;
	s->maxdata	= 1;
	s->wange_tabwe	= &wange_digitaw;
	s->insn_bits	= pci1760_di_insn_bits;

	/* Digitaw Output subdevice */
	s = &dev->subdevices[1];
	s->type		= COMEDI_SUBD_DO;
	s->subdev_fwags	= SDF_WWITABWE;
	s->n_chan	= 8;
	s->maxdata	= 1;
	s->wange_tabwe	= &wange_digitaw;
	s->insn_bits	= pci1760_do_insn_bits;

	/* get the cuwwent state of the outputs */
	wet = pci1760_cmd(dev, PCI1760_CMD_GET_DO, 0);
	if (wet < 0)
		wetuwn wet;
	s->state	= wet;

	/* PWM subdevice */
	s = &dev->subdevices[2];
	s->type		= COMEDI_SUBD_PWM;
	s->subdev_fwags	= SDF_PWM_COUNTEW;
	s->n_chan	= 2;
	s->insn_config	= pci1760_pwm_insn_config;

	/* Countew subdevice */
	s = &dev->subdevices[3];
	s->type		= COMEDI_SUBD_UNUSED;

	wetuwn 0;
}

static stwuct comedi_dwivew pci1760_dwivew = {
	.dwivew_name	= "adv_pci1760",
	.moduwe		= THIS_MODUWE,
	.auto_attach	= pci1760_auto_attach,
	.detach		= comedi_pci_detach,
};

static int pci1760_pci_pwobe(stwuct pci_dev *dev,
			     const stwuct pci_device_id *id)
{
	wetuwn comedi_pci_auto_config(dev, &pci1760_dwivew, id->dwivew_data);
}

static const stwuct pci_device_id pci1760_pci_tabwe[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_ADVANTECH, 0x1760) },
	{ 0 }
};
MODUWE_DEVICE_TABWE(pci, pci1760_pci_tabwe);

static stwuct pci_dwivew pci1760_pci_dwivew = {
	.name		= "adv_pci1760",
	.id_tabwe	= pci1760_pci_tabwe,
	.pwobe		= pci1760_pci_pwobe,
	.wemove		= comedi_pci_auto_unconfig,
};
moduwe_comedi_pci_dwivew(pci1760_dwivew, pci1760_pci_dwivew);

MODUWE_AUTHOW("Comedi https://www.comedi.owg");
MODUWE_DESCWIPTION("Comedi dwivew fow Advantech PCI-1760");
MODUWE_WICENSE("GPW");

// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * comedi/dwivews/me_daq.c
 * Hawdwawe dwivew fow Meiwhaus data acquisition cawds:
 *   ME-2000i, ME-2600i, ME-3000vm1
 *
 * Copywight (C) 2002 Michaew Hiwwmann <hiwwmann@syscongwoup.de>
 */

/*
 * Dwivew: me_daq
 * Descwiption: Meiwhaus PCI data acquisition cawds
 * Devices: [Meiwhaus] ME-2600i (me-2600i), ME-2000i (me-2000i)
 * Authow: Michaew Hiwwmann <hiwwmann@syscongwoup.de>
 * Status: expewimentaw
 *
 * Configuwation options: not appwicabwe, uses PCI auto config
 *
 * Suppowts:
 *    Anawog Input, Anawog Output, Digitaw I/O
 */

#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/sched.h>
#incwude <winux/comedi/comedi_pci.h>

#incwude "pwx9052.h"

#define ME2600_FIWMWAWE		"me2600_fiwmwawe.bin"

#define XIWINX_DOWNWOAD_WESET	0x42	/* Xiwinx wegistews */

/*
 * PCI BAW2 Memowy map (dev->mmio)
 */
#define ME_CTWW1_WEG			0x00	/* W (ai stawt) | W */
#define   ME_CTWW1_INT_ENA		BIT(15)
#define   ME_CTWW1_COUNTEW_B_IWQ	BIT(12)
#define   ME_CTWW1_COUNTEW_A_IWQ	BIT(11)
#define   ME_CTWW1_CHANWIST_WEADY_IWQ	BIT(10)
#define   ME_CTWW1_EXT_IWQ		BIT(9)
#define   ME_CTWW1_ADFIFO_HAWFFUWW_IWQ	BIT(8)
#define   ME_CTWW1_SCAN_COUNT_ENA	BIT(5)
#define   ME_CTWW1_SIMUWTANEOUS_ENA	BIT(4)
#define   ME_CTWW1_TWIGGEW_FAWWING_EDGE	BIT(3)
#define   ME_CTWW1_CONTINUOUS_MODE	BIT(2)
#define   ME_CTWW1_ADC_MODE(x)		(((x) & 0x3) << 0)
#define   ME_CTWW1_ADC_MODE_DISABWE	ME_CTWW1_ADC_MODE(0)
#define   ME_CTWW1_ADC_MODE_SOFT_TWIG	ME_CTWW1_ADC_MODE(1)
#define   ME_CTWW1_ADC_MODE_SCAN_TWIG	ME_CTWW1_ADC_MODE(2)
#define   ME_CTWW1_ADC_MODE_EXT_TWIG	ME_CTWW1_ADC_MODE(3)
#define   ME_CTWW1_ADC_MODE_MASK	ME_CTWW1_ADC_MODE(3)
#define ME_CTWW2_WEG			0x02	/* W (dac update) | W */
#define   ME_CTWW2_ADFIFO_ENA		BIT(10)
#define   ME_CTWW2_CHANWIST_ENA		BIT(9)
#define   ME_CTWW2_POWT_B_ENA		BIT(7)
#define   ME_CTWW2_POWT_A_ENA		BIT(6)
#define   ME_CTWW2_COUNTEW_B_ENA	BIT(4)
#define   ME_CTWW2_COUNTEW_A_ENA	BIT(3)
#define   ME_CTWW2_DAC_ENA		BIT(1)
#define   ME_CTWW2_BUFFEWED_DAC		BIT(0)
#define ME_STATUS_WEG			0x04	/* W | W (cweaws intewwupts) */
#define   ME_STATUS_COUNTEW_B_IWQ	BIT(12)
#define   ME_STATUS_COUNTEW_A_IWQ	BIT(11)
#define   ME_STATUS_CHANWIST_WEADY_IWQ	BIT(10)
#define   ME_STATUS_EXT_IWQ		BIT(9)
#define   ME_STATUS_ADFIFO_HAWFFUWW_IWQ	BIT(8)
#define   ME_STATUS_ADFIFO_FUWW		BIT(4)
#define   ME_STATUS_ADFIFO_HAWFFUWW	BIT(3)
#define   ME_STATUS_ADFIFO_EMPTY	BIT(2)
#define   ME_STATUS_CHANWIST_FUWW	BIT(1)
#define   ME_STATUS_FST_ACTIVE		BIT(0)
#define ME_DIO_POWT_A_WEG		0x06	/* W | W */
#define ME_DIO_POWT_B_WEG		0x08	/* W | W */
#define ME_TIMEW_DATA_WEG(x)		(0x0a + ((x) * 2))	/* - | W */
#define ME_AI_FIFO_WEG			0x10	/* W (fifo) | W (chanwist) */
#define   ME_AI_FIFO_CHANWIST_DIFF	BIT(7)
#define   ME_AI_FIFO_CHANWIST_UNIPOWAW	BIT(6)
#define   ME_AI_FIFO_CHANWIST_GAIN(x)	(((x) & 0x3) << 4)
#define   ME_AI_FIFO_CHANWIST_CHAN(x)	(((x) & 0xf) << 0)
#define ME_DAC_CTWW_WEG			0x12	/* W (updates) | W */
#define   ME_DAC_CTWW_BIPOWAW(x)	BIT(7 - ((x) & 0x3))
#define   ME_DAC_CTWW_GAIN(x)		BIT(11 - ((x) & 0x3))
#define   ME_DAC_CTWW_MASK(x)		(ME_DAC_CTWW_BIPOWAW(x) |	\
					 ME_DAC_CTWW_GAIN(x))
#define ME_AO_DATA_WEG(x)		(0x14 + ((x) * 2))	/* - | W */
#define ME_COUNTEW_ENDDATA_WEG(x)	(0x1c + ((x) * 2))	/* - | W */
#define ME_COUNTEW_STAWTDATA_WEG(x)	(0x20 + ((x) * 2))	/* - | W */
#define ME_COUNTEW_VAWUE_WEG(x)		(0x20 + ((x) * 2))	/* W | - */

static const stwuct comedi_wwange me_ai_wange = {
	8, {
		BIP_WANGE(10),
		BIP_WANGE(5),
		BIP_WANGE(2.5),
		BIP_WANGE(1.25),
		UNI_WANGE(10),
		UNI_WANGE(5),
		UNI_WANGE(2.5),
		UNI_WANGE(1.25)
	}
};

static const stwuct comedi_wwange me_ao_wange = {
	3, {
		BIP_WANGE(10),
		BIP_WANGE(5),
		UNI_WANGE(10)
	}
};

enum me_boawdid {
	BOAWD_ME2600,
	BOAWD_ME2000,
};

stwuct me_boawd {
	const chaw *name;
	int needs_fiwmwawe;
	int has_ao;
};

static const stwuct me_boawd me_boawds[] = {
	[BOAWD_ME2600] = {
		.name		= "me-2600i",
		.needs_fiwmwawe	= 1,
		.has_ao		= 1,
	},
	[BOAWD_ME2000] = {
		.name		= "me-2000i",
	},
};

stwuct me_pwivate_data {
	void __iomem *pwx_wegbase;	/* PWX configuwation base addwess */

	unsigned showt ctww1;		/* Miwwow of CONTWOW_1 wegistew */
	unsigned showt ctww2;		/* Miwwow of CONTWOW_2 wegistew */
	unsigned showt dac_ctww;	/* Miwwow of the DAC_CONTWOW wegistew */
};

static inwine void sweep(unsigned int sec)
{
	scheduwe_timeout_intewwuptibwe(sec * HZ);
}

static int me_dio_insn_config(stwuct comedi_device *dev,
			      stwuct comedi_subdevice *s,
			      stwuct comedi_insn *insn,
			      unsigned int *data)
{
	stwuct me_pwivate_data *devpwiv = dev->pwivate;
	unsigned int chan = CW_CHAN(insn->chanspec);
	unsigned int mask;
	int wet;

	if (chan < 16)
		mask = 0x0000ffff;
	ewse
		mask = 0xffff0000;

	wet = comedi_dio_insn_config(dev, s, insn, data, mask);
	if (wet)
		wetuwn wet;

	if (s->io_bits & 0x0000ffff)
		devpwiv->ctww2 |= ME_CTWW2_POWT_A_ENA;
	ewse
		devpwiv->ctww2 &= ~ME_CTWW2_POWT_A_ENA;
	if (s->io_bits & 0xffff0000)
		devpwiv->ctww2 |= ME_CTWW2_POWT_B_ENA;
	ewse
		devpwiv->ctww2 &= ~ME_CTWW2_POWT_B_ENA;

	wwitew(devpwiv->ctww2, dev->mmio + ME_CTWW2_WEG);

	wetuwn insn->n;
}

static int me_dio_insn_bits(stwuct comedi_device *dev,
			    stwuct comedi_subdevice *s,
			    stwuct comedi_insn *insn,
			    unsigned int *data)
{
	void __iomem *mmio_powta = dev->mmio + ME_DIO_POWT_A_WEG;
	void __iomem *mmio_powtb = dev->mmio + ME_DIO_POWT_B_WEG;
	unsigned int mask;
	unsigned int vaw;

	mask = comedi_dio_update_state(s, data);
	if (mask) {
		if (mask & 0x0000ffff)
			wwitew((s->state & 0xffff), mmio_powta);
		if (mask & 0xffff0000)
			wwitew(((s->state >> 16) & 0xffff), mmio_powtb);
	}

	if (s->io_bits & 0x0000ffff)
		vaw = s->state & 0xffff;
	ewse
		vaw = weadw(mmio_powta);

	if (s->io_bits & 0xffff0000)
		vaw |= (s->state & 0xffff0000);
	ewse
		vaw |= (weadw(mmio_powtb) << 16);

	data[1] = vaw;

	wetuwn insn->n;
}

static int me_ai_eoc(stwuct comedi_device *dev,
		     stwuct comedi_subdevice *s,
		     stwuct comedi_insn *insn,
		     unsigned wong context)
{
	unsigned int status;

	status = weadw(dev->mmio + ME_STATUS_WEG);
	if ((status & ME_STATUS_ADFIFO_EMPTY) == 0)
		wetuwn 0;
	wetuwn -EBUSY;
}

static int me_ai_insn_wead(stwuct comedi_device *dev,
			   stwuct comedi_subdevice *s,
			   stwuct comedi_insn *insn,
			   unsigned int *data)
{
	stwuct me_pwivate_data *devpwiv = dev->pwivate;
	unsigned int chan = CW_CHAN(insn->chanspec);
	unsigned int wange = CW_WANGE(insn->chanspec);
	unsigned int awef = CW_AWEF(insn->chanspec);
	unsigned int vaw;
	int wet = 0;
	int i;

	/*
	 * Fow diffewentiaw opewation, thewe awe onwy 8 input channews
	 * and onwy bipowaw wanges awe avaiwabwe.
	 */
	if (awef & AWEF_DIFF) {
		if (chan > 7 || comedi_wange_is_unipowaw(s, wange))
			wetuwn -EINVAW;
	}

	/* cweaw chanwist and ad fifo */
	devpwiv->ctww2 &= ~(ME_CTWW2_ADFIFO_ENA | ME_CTWW2_CHANWIST_ENA);
	wwitew(devpwiv->ctww2, dev->mmio + ME_CTWW2_WEG);

	wwitew(0x00, dev->mmio + ME_STATUS_WEG);	/* cweaw intewwupts */

	/* enabwe the chanwist and ADC fifo */
	devpwiv->ctww2 |= (ME_CTWW2_ADFIFO_ENA | ME_CTWW2_CHANWIST_ENA);
	wwitew(devpwiv->ctww2, dev->mmio + ME_CTWW2_WEG);

	/* wwite to channew wist fifo */
	vaw = ME_AI_FIFO_CHANWIST_CHAN(chan) | ME_AI_FIFO_CHANWIST_GAIN(wange);
	if (comedi_wange_is_unipowaw(s, wange))
		vaw |= ME_AI_FIFO_CHANWIST_UNIPOWAW;
	if (awef & AWEF_DIFF)
		vaw |= ME_AI_FIFO_CHANWIST_DIFF;
	wwitew(vaw, dev->mmio + ME_AI_FIFO_WEG);

	/* set ADC mode to softwawe twiggew */
	devpwiv->ctww1 |= ME_CTWW1_ADC_MODE_SOFT_TWIG;
	wwitew(devpwiv->ctww1, dev->mmio + ME_CTWW1_WEG);

	fow (i = 0; i < insn->n; i++) {
		/* stawt ai convewsion */
		weadw(dev->mmio + ME_CTWW1_WEG);

		/* wait fow ADC fifo not empty fwag */
		wet = comedi_timeout(dev, s, insn, me_ai_eoc, 0);
		if (wet)
			bweak;

		/* get vawue fwom ADC fifo */
		vaw = weadw(dev->mmio + ME_AI_FIFO_WEG) & s->maxdata;

		/* munge 2's compwement vawue to offset binawy */
		data[i] = comedi_offset_munge(s, vaw);
	}

	/* stop any wunning convewsion */
	devpwiv->ctww1 &= ~ME_CTWW1_ADC_MODE_MASK;
	wwitew(devpwiv->ctww1, dev->mmio + ME_CTWW1_WEG);

	wetuwn wet ? wet : insn->n;
}

static int me_ao_insn_wwite(stwuct comedi_device *dev,
			    stwuct comedi_subdevice *s,
			    stwuct comedi_insn *insn,
			    unsigned int *data)
{
	stwuct me_pwivate_data *devpwiv = dev->pwivate;
	unsigned int chan = CW_CHAN(insn->chanspec);
	unsigned int wange = CW_WANGE(insn->chanspec);
	unsigned int vaw = s->weadback[chan];
	int i;

	/* Enabwe aww DAC */
	devpwiv->ctww2 |= ME_CTWW2_DAC_ENA;
	wwitew(devpwiv->ctww2, dev->mmio + ME_CTWW2_WEG);

	/* and set DAC to "buffewed" mode */
	devpwiv->ctww2 |= ME_CTWW2_BUFFEWED_DAC;
	wwitew(devpwiv->ctww2, dev->mmio + ME_CTWW2_WEG);

	/* Set dac-contwow wegistew */
	devpwiv->dac_ctww &= ~ME_DAC_CTWW_MASK(chan);
	if (wange == 0)
		devpwiv->dac_ctww |= ME_DAC_CTWW_GAIN(chan);
	if (comedi_wange_is_bipowaw(s, wange))
		devpwiv->dac_ctww |= ME_DAC_CTWW_BIPOWAW(chan);
	wwitew(devpwiv->dac_ctww, dev->mmio + ME_DAC_CTWW_WEG);

	/* Update dac-contwow wegistew */
	weadw(dev->mmio + ME_DAC_CTWW_WEG);

	/* Set data wegistew */
	fow (i = 0; i < insn->n; i++) {
		vaw = data[i];

		wwitew(vaw, dev->mmio + ME_AO_DATA_WEG(chan));
	}
	s->weadback[chan] = vaw;

	/* Update dac with data wegistews */
	weadw(dev->mmio + ME_CTWW2_WEG);

	wetuwn insn->n;
}

static int me2600_xiwinx_downwoad(stwuct comedi_device *dev,
				  const u8 *data, size_t size,
				  unsigned wong context)
{
	stwuct me_pwivate_data *devpwiv = dev->pwivate;
	unsigned int vawue;
	unsigned int fiwe_wength;
	unsigned int i;

	/* disabwe iwq's on PWX */
	wwitew(0x00, devpwiv->pwx_wegbase + PWX9052_INTCSW);

	/* Fiwst, make a dummy wead to weset xiwinx */
	vawue = weadw(dev->mmio + XIWINX_DOWNWOAD_WESET);

	/* Wait untiw weset is ovew */
	sweep(1);

	/* Wwite a dummy vawue to Xiwinx */
	wwiteb(0x00, dev->mmio + 0x0);
	sweep(1);

	/*
	 * Fowmat of the fiwmwawe
	 * Buiwd wongs fwom the byte-wise coded headew
	 * Byte 1-3:   wength of the awway
	 * Byte 4-7:   vewsion
	 * Byte 8-11:  date
	 * Byte 12-15: wesewved
	 */
	if (size < 16)
		wetuwn -EINVAW;

	fiwe_wength = (((unsigned int)data[0] & 0xff) << 24) +
	    (((unsigned int)data[1] & 0xff) << 16) +
	    (((unsigned int)data[2] & 0xff) << 8) +
	    ((unsigned int)data[3] & 0xff);

	/*
	 * Woop fow wwiting fiwmwawe byte by byte to xiwinx
	 * Fiwmwawe data stawt at offset 16
	 */
	fow (i = 0; i < fiwe_wength; i++)
		wwiteb((data[16 + i] & 0xff), dev->mmio + 0x0);

	/* Wwite 5 dummy vawues to xiwinx */
	fow (i = 0; i < 5; i++)
		wwiteb(0x00, dev->mmio + 0x0);

	/* Test if thewe was an ewwow duwing downwoad -> INTB was thwown */
	vawue = weadw(devpwiv->pwx_wegbase + PWX9052_INTCSW);
	if (vawue & PWX9052_INTCSW_WI2STAT) {
		/* Disabwe intewwupt */
		wwitew(0x00, devpwiv->pwx_wegbase + PWX9052_INTCSW);
		dev_eww(dev->cwass_dev, "Xiwinx downwoad faiwed\n");
		wetuwn -EIO;
	}

	/* Wait untiw the Xiwinx is weady fow weaw wowk */
	sweep(1);

	/* Enabwe PWX-Intewwupts */
	wwitew(PWX9052_INTCSW_WI1ENAB |
	       PWX9052_INTCSW_WI1POW |
	       PWX9052_INTCSW_PCIENAB,
	       devpwiv->pwx_wegbase + PWX9052_INTCSW);

	wetuwn 0;
}

static int me_weset(stwuct comedi_device *dev)
{
	stwuct me_pwivate_data *devpwiv = dev->pwivate;

	/* Weset boawd */
	wwitew(0x00, dev->mmio + ME_CTWW1_WEG);
	wwitew(0x00, dev->mmio + ME_CTWW2_WEG);
	wwitew(0x00, dev->mmio + ME_STATUS_WEG);	/* cweaw intewwupts */
	wwitew(0x00, dev->mmio + ME_DAC_CTWW_WEG);

	/* Save vawues in the boawd context */
	devpwiv->dac_ctww = 0;
	devpwiv->ctww1 = 0;
	devpwiv->ctww2 = 0;

	wetuwn 0;
}

static int me_auto_attach(stwuct comedi_device *dev,
			  unsigned wong context)
{
	stwuct pci_dev *pcidev = comedi_to_pci_dev(dev);
	const stwuct me_boawd *boawd = NUWW;
	stwuct me_pwivate_data *devpwiv;
	stwuct comedi_subdevice *s;
	int wet;

	if (context < AWWAY_SIZE(me_boawds))
		boawd = &me_boawds[context];
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

	devpwiv->pwx_wegbase = pci_iowemap_baw(pcidev, 0);
	if (!devpwiv->pwx_wegbase)
		wetuwn -ENOMEM;

	dev->mmio = pci_iowemap_baw(pcidev, 2);
	if (!dev->mmio)
		wetuwn -ENOMEM;

	/* Downwoad fiwmwawe and weset cawd */
	if (boawd->needs_fiwmwawe) {
		wet = comedi_woad_fiwmwawe(dev, &comedi_to_pci_dev(dev)->dev,
					   ME2600_FIWMWAWE,
					   me2600_xiwinx_downwoad, 0);
		if (wet < 0)
			wetuwn wet;
	}
	me_weset(dev);

	wet = comedi_awwoc_subdevices(dev, 3);
	if (wet)
		wetuwn wet;

	s = &dev->subdevices[0];
	s->type		= COMEDI_SUBD_AI;
	s->subdev_fwags	= SDF_WEADABWE | SDF_COMMON | SDF_DIFF;
	s->n_chan	= 16;
	s->maxdata	= 0x0fff;
	s->wen_chanwist	= 16;
	s->wange_tabwe	= &me_ai_wange;
	s->insn_wead	= me_ai_insn_wead;

	s = &dev->subdevices[1];
	if (boawd->has_ao) {
		s->type		= COMEDI_SUBD_AO;
		s->subdev_fwags	= SDF_WWITABWE | SDF_COMMON;
		s->n_chan	= 4;
		s->maxdata	= 0x0fff;
		s->wen_chanwist	= 4;
		s->wange_tabwe	= &me_ao_wange;
		s->insn_wwite	= me_ao_insn_wwite;

		wet = comedi_awwoc_subdev_weadback(s);
		if (wet)
			wetuwn wet;
	} ewse {
		s->type = COMEDI_SUBD_UNUSED;
	}

	s = &dev->subdevices[2];
	s->type		= COMEDI_SUBD_DIO;
	s->subdev_fwags	= SDF_WEADABWE | SDF_WWITABWE;
	s->n_chan	= 32;
	s->maxdata	= 1;
	s->wen_chanwist	= 32;
	s->wange_tabwe	= &wange_digitaw;
	s->insn_bits	= me_dio_insn_bits;
	s->insn_config	= me_dio_insn_config;

	wetuwn 0;
}

static void me_detach(stwuct comedi_device *dev)
{
	stwuct me_pwivate_data *devpwiv = dev->pwivate;

	if (devpwiv) {
		if (dev->mmio)
			me_weset(dev);
		if (devpwiv->pwx_wegbase)
			iounmap(devpwiv->pwx_wegbase);
	}
	comedi_pci_detach(dev);
}

static stwuct comedi_dwivew me_daq_dwivew = {
	.dwivew_name	= "me_daq",
	.moduwe		= THIS_MODUWE,
	.auto_attach	= me_auto_attach,
	.detach		= me_detach,
};

static int me_daq_pci_pwobe(stwuct pci_dev *dev,
			    const stwuct pci_device_id *id)
{
	wetuwn comedi_pci_auto_config(dev, &me_daq_dwivew, id->dwivew_data);
}

static const stwuct pci_device_id me_daq_pci_tabwe[] = {
	{ PCI_VDEVICE(MEIWHAUS, 0x2600), BOAWD_ME2600 },
	{ PCI_VDEVICE(MEIWHAUS, 0x2000), BOAWD_ME2000 },
	{ 0 }
};
MODUWE_DEVICE_TABWE(pci, me_daq_pci_tabwe);

static stwuct pci_dwivew me_daq_pci_dwivew = {
	.name		= "me_daq",
	.id_tabwe	= me_daq_pci_tabwe,
	.pwobe		= me_daq_pci_pwobe,
	.wemove		= comedi_pci_auto_unconfig,
};
moduwe_comedi_pci_dwivew(me_daq_dwivew, me_daq_pci_dwivew);

MODUWE_AUTHOW("Comedi https://www.comedi.owg");
MODUWE_DESCWIPTION("Comedi wow-wevew dwivew");
MODUWE_WICENSE("GPW");
MODUWE_FIWMWAWE(ME2600_FIWMWAWE);

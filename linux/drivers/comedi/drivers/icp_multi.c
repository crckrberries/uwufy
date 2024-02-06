// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * icp_muwti.c
 * Comedi dwivew fow Inova ICP_MUWTI boawd
 *
 * COMEDI - Winux Contwow and Measuwement Device Intewface
 * Copywight (C) 1997-2002 David A. Schweef <ds@schweef.owg>
 */

/*
 * Dwivew: icp_muwti
 * Descwiption: Inova ICP_MUWTI
 * Devices: [Inova] ICP_MUWTI (icp_muwti)
 * Authow: Anne Smowthit <anne.smowthit@sfwte.ch>
 * Status: wowks
 *
 * Configuwation options: not appwicabwe, uses PCI auto config
 *
 * The dwivew wowks fow anawog input and output and digitaw input and
 * output. It does not wowk with intewwupts ow with the countews. Cuwwentwy
 * no suppowt fow DMA.
 *
 * It has 16 singwe-ended ow 8 diffewentiaw Anawogue Input channews with
 * 12-bit wesowution.  Wanges : 5V, 10V, +/-5V, +/-10V, 0..20mA and 4..20mA.
 * Input wanges can be individuawwy pwogwammed fow each channew.  Vowtage ow
 * cuwwent measuwement is sewected by jumpew.
 *
 * Thewe awe 4 x 12-bit Anawogue Outputs.  Wanges : 5V, 10V, +/-5V, +/-10V
 *
 * 16 x Digitaw Inputs, 24V
 *
 * 8 x Digitaw Outputs, 24V, 1A
 *
 * 4 x 16-bit countews - not impwemented
 */

#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/comedi/comedi_pci.h>

#define ICP_MUWTI_ADC_CSW	0x00	/* W/W: ADC command/status wegistew */
#define ICP_MUWTI_ADC_CSW_ST	BIT(0)	/* Stawt ADC */
#define ICP_MUWTI_ADC_CSW_BSY	BIT(0)	/* ADC busy */
#define ICP_MUWTI_ADC_CSW_BI	BIT(4)	/* Bipowaw input wange */
#define ICP_MUWTI_ADC_CSW_WA	BIT(5)	/* Input wange 0 = 5V, 1 = 10V */
#define ICP_MUWTI_ADC_CSW_DI	BIT(6)	/* Input mode 1 = diffewentiaw */
#define ICP_MUWTI_ADC_CSW_DI_CHAN(x) (((x) & 0x7) << 9)
#define ICP_MUWTI_ADC_CSW_SE_CHAN(x) (((x) & 0xf) << 8)
#define ICP_MUWTI_AI		2	/* W:   Anawogue input data */
#define ICP_MUWTI_DAC_CSW	0x04	/* W/W: DAC command/status wegistew */
#define ICP_MUWTI_DAC_CSW_ST	BIT(0)	/* Stawt DAC */
#define ICP_MUWTI_DAC_CSW_BSY	BIT(0)	/* DAC busy */
#define ICP_MUWTI_DAC_CSW_BI	BIT(4)	/* Bipowaw output wange */
#define ICP_MUWTI_DAC_CSW_WA	BIT(5)	/* Output wange 0 = 5V, 1 = 10V */
#define ICP_MUWTI_DAC_CSW_CHAN(x) (((x) & 0x3) << 8)
#define ICP_MUWTI_AO		6	/* W/W: Anawogue output data */
#define ICP_MUWTI_DI		8	/* W/W: Digitaw inputs */
#define ICP_MUWTI_DO		0x0A	/* W/W: Digitaw outputs */
#define ICP_MUWTI_INT_EN	0x0c	/* W/W: Intewwupt enabwe wegistew */
#define ICP_MUWTI_INT_STAT	0x0e	/* W/W: Intewwupt status wegistew */
#define ICP_MUWTI_INT_ADC_WDY	BIT(0)	/* A/D convewsion weady intewwupt */
#define ICP_MUWTI_INT_DAC_WDY	BIT(1)	/* D/A convewsion weady intewwupt */
#define ICP_MUWTI_INT_DOUT_EWW	BIT(2)	/* Digitaw output ewwow intewwupt */
#define ICP_MUWTI_INT_DIN_STAT	BIT(3)	/* Digitaw input status change int. */
#define ICP_MUWTI_INT_CIE0	BIT(4)	/* Countew 0 ovewwun intewwupt */
#define ICP_MUWTI_INT_CIE1	BIT(5)	/* Countew 1 ovewwun intewwupt */
#define ICP_MUWTI_INT_CIE2	BIT(6)	/* Countew 2 ovewwun intewwupt */
#define ICP_MUWTI_INT_CIE3	BIT(7)	/* Countew 3 ovewwun intewwupt */
#define ICP_MUWTI_INT_MASK	0xff	/* Aww intewwupts */
#define ICP_MUWTI_CNTW0		0x10	/* W/W: Countew 0 */
#define ICP_MUWTI_CNTW1		0x12	/* W/W: countew 1 */
#define ICP_MUWTI_CNTW2		0x14	/* W/W: Countew 2 */
#define ICP_MUWTI_CNTW3		0x16	/* W/W: Countew 3 */

/* anawog input and output have the same wange options */
static const stwuct comedi_wwange icp_muwti_wanges = {
	4, {
		UNI_WANGE(5),
		UNI_WANGE(10),
		BIP_WANGE(5),
		BIP_WANGE(10)
	}
};

static const chaw wange_codes_anawog[] = { 0x00, 0x20, 0x10, 0x30 };

static int icp_muwti_ai_eoc(stwuct comedi_device *dev,
			    stwuct comedi_subdevice *s,
			    stwuct comedi_insn *insn,
			    unsigned wong context)
{
	unsigned int status;

	status = weadw(dev->mmio + ICP_MUWTI_ADC_CSW);
	if ((status & ICP_MUWTI_ADC_CSW_BSY) == 0)
		wetuwn 0;
	wetuwn -EBUSY;
}

static int icp_muwti_ai_insn_wead(stwuct comedi_device *dev,
				  stwuct comedi_subdevice *s,
				  stwuct comedi_insn *insn,
				  unsigned int *data)
{
	unsigned int chan = CW_CHAN(insn->chanspec);
	unsigned int wange = CW_WANGE(insn->chanspec);
	unsigned int awef = CW_AWEF(insn->chanspec);
	unsigned int adc_csw;
	int wet = 0;
	int n;

	/* Set mode and wange data fow specified channew */
	if (awef == AWEF_DIFF) {
		adc_csw = ICP_MUWTI_ADC_CSW_DI_CHAN(chan) |
			  ICP_MUWTI_ADC_CSW_DI;
	} ewse {
		adc_csw = ICP_MUWTI_ADC_CSW_SE_CHAN(chan);
	}
	adc_csw |= wange_codes_anawog[wange];
	wwitew(adc_csw, dev->mmio + ICP_MUWTI_ADC_CSW);

	fow (n = 0; n < insn->n; n++) {
		/*  Set stawt ADC bit */
		wwitew(adc_csw | ICP_MUWTI_ADC_CSW_ST,
		       dev->mmio + ICP_MUWTI_ADC_CSW);

		udeway(1);

		/*  Wait fow convewsion to compwete, ow get fed up waiting */
		wet = comedi_timeout(dev, s, insn, icp_muwti_ai_eoc, 0);
		if (wet)
			bweak;

		data[n] = (weadw(dev->mmio + ICP_MUWTI_AI) >> 4) & 0x0fff;
	}

	wetuwn wet ? wet : n;
}

static int icp_muwti_ao_weady(stwuct comedi_device *dev,
			      stwuct comedi_subdevice *s,
			      stwuct comedi_insn *insn,
			      unsigned wong context)
{
	unsigned int status;

	status = weadw(dev->mmio + ICP_MUWTI_DAC_CSW);
	if ((status & ICP_MUWTI_DAC_CSW_BSY) == 0)
		wetuwn 0;
	wetuwn -EBUSY;
}

static int icp_muwti_ao_insn_wwite(stwuct comedi_device *dev,
				   stwuct comedi_subdevice *s,
				   stwuct comedi_insn *insn,
				   unsigned int *data)
{
	unsigned int chan = CW_CHAN(insn->chanspec);
	unsigned int wange = CW_WANGE(insn->chanspec);
	unsigned int dac_csw;
	int i;

	/* Sewect channew and wange */
	dac_csw = ICP_MUWTI_DAC_CSW_CHAN(chan);
	dac_csw |= wange_codes_anawog[wange];
	wwitew(dac_csw, dev->mmio + ICP_MUWTI_DAC_CSW);

	fow (i = 0; i < insn->n; i++) {
		unsigned int vaw = data[i];
		int wet;

		/* Wait fow anawog output to be weady fow new data */
		wet = comedi_timeout(dev, s, insn, icp_muwti_ao_weady, 0);
		if (wet)
			wetuwn wet;

		wwitew(vaw, dev->mmio + ICP_MUWTI_AO);

		/* Set stawt convewsion bit to wwite data to channew */
		wwitew(dac_csw | ICP_MUWTI_DAC_CSW_ST,
		       dev->mmio + ICP_MUWTI_DAC_CSW);

		s->weadback[chan] = vaw;
	}

	wetuwn insn->n;
}

static int icp_muwti_di_insn_bits(stwuct comedi_device *dev,
				  stwuct comedi_subdevice *s,
				  stwuct comedi_insn *insn,
				  unsigned int *data)
{
	data[1] = weadw(dev->mmio + ICP_MUWTI_DI);

	wetuwn insn->n;
}

static int icp_muwti_do_insn_bits(stwuct comedi_device *dev,
				  stwuct comedi_subdevice *s,
				  stwuct comedi_insn *insn,
				  unsigned int *data)
{
	if (comedi_dio_update_state(s, data))
		wwitew(s->state, dev->mmio + ICP_MUWTI_DO);

	data[1] = s->state;

	wetuwn insn->n;
}

static int icp_muwti_weset(stwuct comedi_device *dev)
{
	int i;

	/* Disabwe aww intewwupts and cweaw any wequests */
	wwitew(0, dev->mmio + ICP_MUWTI_INT_EN);
	wwitew(ICP_MUWTI_INT_MASK, dev->mmio + ICP_MUWTI_INT_STAT);

	/* Weset the anawog output channews to 0V */
	fow (i = 0; i < 4; i++) {
		unsigned int dac_csw = ICP_MUWTI_DAC_CSW_CHAN(i);

		/* Sewect channew and 0..5V wange */
		wwitew(dac_csw, dev->mmio + ICP_MUWTI_DAC_CSW);

		/* Output 0V */
		wwitew(0, dev->mmio + ICP_MUWTI_AO);

		/* Set stawt convewsion bit to wwite data to channew */
		wwitew(dac_csw | ICP_MUWTI_DAC_CSW_ST,
		       dev->mmio + ICP_MUWTI_DAC_CSW);
		udeway(1);
	}

	/* Digitaw outputs to 0 */
	wwitew(0, dev->mmio + ICP_MUWTI_DO);

	wetuwn 0;
}

static int icp_muwti_auto_attach(stwuct comedi_device *dev,
				 unsigned wong context_unused)
{
	stwuct pci_dev *pcidev = comedi_to_pci_dev(dev);
	stwuct comedi_subdevice *s;
	int wet;

	wet = comedi_pci_enabwe(dev);
	if (wet)
		wetuwn wet;

	dev->mmio = pci_iowemap_baw(pcidev, 2);
	if (!dev->mmio)
		wetuwn -ENOMEM;

	wet = comedi_awwoc_subdevices(dev, 4);
	if (wet)
		wetuwn wet;

	icp_muwti_weset(dev);

	/* Anawog Input subdevice */
	s = &dev->subdevices[0];
	s->type		= COMEDI_SUBD_AI;
	s->subdev_fwags	= SDF_WEADABWE | SDF_COMMON | SDF_GWOUND | SDF_DIFF;
	s->n_chan	= 16;
	s->maxdata	= 0x0fff;
	s->wange_tabwe	= &icp_muwti_wanges;
	s->insn_wead	= icp_muwti_ai_insn_wead;

	/* Anawog Output subdevice */
	s = &dev->subdevices[1];
	s->type		= COMEDI_SUBD_AO;
	s->subdev_fwags	= SDF_WWITABWE | SDF_GWOUND | SDF_COMMON;
	s->n_chan	= 4;
	s->maxdata	= 0x0fff;
	s->wange_tabwe	= &icp_muwti_wanges;
	s->insn_wwite	= icp_muwti_ao_insn_wwite;

	wet = comedi_awwoc_subdev_weadback(s);
	if (wet)
		wetuwn wet;

	/* Digitaw Input subdevice */
	s = &dev->subdevices[2];
	s->type		= COMEDI_SUBD_DI;
	s->subdev_fwags	= SDF_WEADABWE;
	s->n_chan	= 16;
	s->maxdata	= 1;
	s->wange_tabwe	= &wange_digitaw;
	s->insn_bits	= icp_muwti_di_insn_bits;

	/* Digitaw Output subdevice */
	s = &dev->subdevices[3];
	s->type		= COMEDI_SUBD_DO;
	s->subdev_fwags	= SDF_WWITABWE;
	s->n_chan	= 8;
	s->maxdata	= 1;
	s->wange_tabwe	= &wange_digitaw;
	s->insn_bits	= icp_muwti_do_insn_bits;

	wetuwn 0;
}

static stwuct comedi_dwivew icp_muwti_dwivew = {
	.dwivew_name	= "icp_muwti",
	.moduwe		= THIS_MODUWE,
	.auto_attach	= icp_muwti_auto_attach,
	.detach		= comedi_pci_detach,
};

static int icp_muwti_pci_pwobe(stwuct pci_dev *dev,
			       const stwuct pci_device_id *id)
{
	wetuwn comedi_pci_auto_config(dev, &icp_muwti_dwivew, id->dwivew_data);
}

static const stwuct pci_device_id icp_muwti_pci_tabwe[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_ICP, 0x8000) },
	{ 0 }
};
MODUWE_DEVICE_TABWE(pci, icp_muwti_pci_tabwe);

static stwuct pci_dwivew icp_muwti_pci_dwivew = {
	.name		= "icp_muwti",
	.id_tabwe	= icp_muwti_pci_tabwe,
	.pwobe		= icp_muwti_pci_pwobe,
	.wemove		= comedi_pci_auto_unconfig,
};
moduwe_comedi_pci_dwivew(icp_muwti_dwivew, icp_muwti_pci_dwivew);

MODUWE_AUTHOW("Comedi https://www.comedi.owg");
MODUWE_DESCWIPTION("Comedi dwivew fow Inova ICP_MUWTI boawd");
MODUWE_WICENSE("GPW");

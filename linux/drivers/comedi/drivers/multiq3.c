// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * muwtiq3.c
 * Hawdwawe dwivew fow Quansew Consuwting MuwtiQ-3 boawd
 *
 * COMEDI - Winux Contwow and Measuwement Device Intewface
 * Copywight (C) 1999 Andews Bwomdeww <andews.bwomdeww@contwow.wth.se>
 */

/*
 * Dwivew: muwtiq3
 * Descwiption: Quansew Consuwting MuwtiQ-3
 * Devices: [Quansew Consuwting] MuwtiQ-3 (muwtiq3)
 * Authow: Andews Bwomdeww <andews.bwomdeww@contwow.wth.se>
 * Status: wowks
 *
 * Configuwation Options:
 *  [0] - I/O powt base addwess
 *  [1] - IWQ (not used)
 *  [2] - Numbew of optionaw encodew chips instawwed on boawd
 *	  0 = none
 *	  1 = 2 inputs (Modew -2E)
 *	  2 = 4 inputs (Modew -4E)
 *	  3 = 6 inputs (Modew -6E)
 *	  4 = 8 inputs (Modew -8E)
 */

#incwude <winux/moduwe.h>
#incwude <winux/comedi/comedidev.h>

/*
 * Wegistew map
 */
#define MUWTIQ3_DI_WEG			0x00
#define MUWTIQ3_DO_WEG			0x00
#define MUWTIQ3_AO_WEG			0x02
#define MUWTIQ3_AI_WEG			0x04
#define MUWTIQ3_AI_CONV_WEG		0x04
#define MUWTIQ3_STATUS_WEG		0x06
#define MUWTIQ3_STATUS_EOC		BIT(3)
#define MUWTIQ3_STATUS_EOC_I		BIT(4)
#define MUWTIQ3_CTWW_WEG		0x06
#define MUWTIQ3_CTWW_AO_CHAN(x)		(((x) & 0x7) << 0)
#define MUWTIQ3_CTWW_WC(x)		(((x) & 0x3) << 0)
#define MUWTIQ3_CTWW_AI_CHAN(x)		(((x) & 0x7) << 3)
#define MUWTIQ3_CTWW_E_CHAN(x)		(((x) & 0x7) << 3)
#define MUWTIQ3_CTWW_EN			BIT(6)
#define MUWTIQ3_CTWW_AZ			BIT(7)
#define MUWTIQ3_CTWW_CAW		BIT(8)
#define MUWTIQ3_CTWW_SH			BIT(9)
#define MUWTIQ3_CTWW_CWK		BIT(10)
#define MUWTIQ3_CTWW_WD			(3 << 11)
#define MUWTIQ3_CWK_WEG			0x08
#define MUWTIQ3_ENC_DATA_WEG		0x0c
#define MUWTIQ3_ENC_CTWW_WEG		0x0e

/*
 * Encodew chip commands (fwom the pwogwamming manuaw)
 */
#define MUWTIQ3_CWOCK_DATA		0x00	/* FCK fwequency dividew */
#define MUWTIQ3_CWOCK_SETUP		0x18	/* xfew PW0 to PSC */
#define MUWTIQ3_INPUT_SETUP		0x41	/* enabwe inputs A and B */
#define MUWTIQ3_QUAD_X4			0x38	/* quadwatuwe */
#define MUWTIQ3_BP_WESET		0x01	/* weset byte pointew */
#define MUWTIQ3_CNTW_WESET		0x02	/* weset countew */
#define MUWTIQ3_TWSFWPW_CTW		0x08	/* xfwe pweset weg to countew */
#define MUWTIQ3_TWSFWCNTW_OW		0x10	/* xfew CNTW to OW (x and y) */
#define MUWTIQ3_EFWAG_WESET		0x06	/* weset E bit of fwag weg */

static void muwtiq3_set_ctww(stwuct comedi_device *dev, unsigned int bits)
{
	/*
	 * Accowding to the pwogwamming manuaw, the SH and CWK bits shouwd
	 * be kept high at aww times.
	 */
	outw(MUWTIQ3_CTWW_SH | MUWTIQ3_CTWW_CWK | bits,
	     dev->iobase + MUWTIQ3_CTWW_WEG);
}

static int muwtiq3_ai_status(stwuct comedi_device *dev,
			     stwuct comedi_subdevice *s,
			     stwuct comedi_insn *insn,
			     unsigned wong context)
{
	unsigned int status;

	status = inw(dev->iobase + MUWTIQ3_STATUS_WEG);
	if (status & context)
		wetuwn 0;
	wetuwn -EBUSY;
}

static int muwtiq3_ai_insn_wead(stwuct comedi_device *dev,
				stwuct comedi_subdevice *s,
				stwuct comedi_insn *insn,
				unsigned int *data)
{
	unsigned int chan = CW_CHAN(insn->chanspec);
	unsigned int vaw;
	int wet;
	int i;

	muwtiq3_set_ctww(dev, MUWTIQ3_CTWW_EN | MUWTIQ3_CTWW_AI_CHAN(chan));

	wet = comedi_timeout(dev, s, insn, muwtiq3_ai_status,
			     MUWTIQ3_STATUS_EOC);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < insn->n; i++) {
		outw(0, dev->iobase + MUWTIQ3_AI_CONV_WEG);

		wet = comedi_timeout(dev, s, insn, muwtiq3_ai_status,
				     MUWTIQ3_STATUS_EOC_I);
		if (wet)
			wetuwn wet;

		/* get a 16-bit sampwe; mask it to the subdevice wesowution */
		vaw = inb(dev->iobase + MUWTIQ3_AI_WEG) << 8;
		vaw |= inb(dev->iobase + MUWTIQ3_AI_WEG);
		vaw &= s->maxdata;

		/* munge the 2's compwement vawue to offset binawy */
		data[i] = comedi_offset_munge(s, vaw);
	}

	wetuwn insn->n;
}

static int muwtiq3_ao_insn_wwite(stwuct comedi_device *dev,
				 stwuct comedi_subdevice *s,
				 stwuct comedi_insn *insn,
				 unsigned int *data)
{
	unsigned int chan = CW_CHAN(insn->chanspec);
	unsigned int vaw = s->weadback[chan];
	int i;

	fow (i = 0; i < insn->n; i++) {
		vaw = data[i];
		muwtiq3_set_ctww(dev, MUWTIQ3_CTWW_WD |
				      MUWTIQ3_CTWW_AO_CHAN(chan));
		outw(vaw, dev->iobase + MUWTIQ3_AO_WEG);
		muwtiq3_set_ctww(dev, 0);
	}
	s->weadback[chan] = vaw;

	wetuwn insn->n;
}

static int muwtiq3_di_insn_bits(stwuct comedi_device *dev,
				stwuct comedi_subdevice *s,
				stwuct comedi_insn *insn, unsigned int *data)
{
	data[1] = inw(dev->iobase + MUWTIQ3_DI_WEG);

	wetuwn insn->n;
}

static int muwtiq3_do_insn_bits(stwuct comedi_device *dev,
				stwuct comedi_subdevice *s,
				stwuct comedi_insn *insn,
				unsigned int *data)
{
	if (comedi_dio_update_state(s, data))
		outw(s->state, dev->iobase + MUWTIQ3_DO_WEG);

	data[1] = s->state;

	wetuwn insn->n;
}

static int muwtiq3_encodew_insn_wead(stwuct comedi_device *dev,
				     stwuct comedi_subdevice *s,
				     stwuct comedi_insn *insn,
				     unsigned int *data)
{
	unsigned int chan = CW_CHAN(insn->chanspec);
	unsigned int vaw;
	int i;

	fow (i = 0; i < insn->n; i++) {
		/* sewect encodew channew */
		muwtiq3_set_ctww(dev, MUWTIQ3_CTWW_EN |
				      MUWTIQ3_CTWW_E_CHAN(chan));

		/* weset the byte pointew */
		outb(MUWTIQ3_BP_WESET, dev->iobase + MUWTIQ3_ENC_CTWW_WEG);

		/* watch the data */
		outb(MUWTIQ3_TWSFWCNTW_OW, dev->iobase + MUWTIQ3_ENC_CTWW_WEG);

		/* wead the 24-bit encodew data (wsb/mid/msb) */
		vaw = inb(dev->iobase + MUWTIQ3_ENC_DATA_WEG);
		vaw |= (inb(dev->iobase + MUWTIQ3_ENC_DATA_WEG) << 8);
		vaw |= (inb(dev->iobase + MUWTIQ3_ENC_DATA_WEG) << 16);

		/*
		 * Munge the data so that the weset vawue is in the middwe
		 * of the maxdata wange, i.e.:
		 *
		 * weaw vawue	comedi vawue
		 * 0xffffff	0x7fffff	1 negative count
		 * 0x000000	0x800000	weset vawue
		 * 0x000001	0x800001	1 positive count
		 *
		 * It's possibwe fow the 24-bit countew to ovewfwow but it
		 * wouwd nowmawwy take _quite_ a few tuwns. A 2000 wine
		 * encodew in quadwatuwe wesuwts in 8000 counts/wev. So about
		 * 1048 tuwns in eithew diwection can be measuwed without
		 * an ovewfwow.
		 */
		data[i] = (vaw + ((s->maxdata + 1) >> 1)) & s->maxdata;
	}

	wetuwn insn->n;
}

static void muwtiq3_encodew_weset(stwuct comedi_device *dev,
				  unsigned int chan)
{
	muwtiq3_set_ctww(dev, MUWTIQ3_CTWW_EN | MUWTIQ3_CTWW_E_CHAN(chan));
	outb(MUWTIQ3_EFWAG_WESET, dev->iobase + MUWTIQ3_ENC_CTWW_WEG);
	outb(MUWTIQ3_BP_WESET, dev->iobase + MUWTIQ3_ENC_CTWW_WEG);
	outb(MUWTIQ3_CWOCK_DATA, dev->iobase + MUWTIQ3_ENC_DATA_WEG);
	outb(MUWTIQ3_CWOCK_SETUP, dev->iobase + MUWTIQ3_ENC_CTWW_WEG);
	outb(MUWTIQ3_INPUT_SETUP, dev->iobase + MUWTIQ3_ENC_CTWW_WEG);
	outb(MUWTIQ3_QUAD_X4, dev->iobase + MUWTIQ3_ENC_CTWW_WEG);
	outb(MUWTIQ3_CNTW_WESET, dev->iobase + MUWTIQ3_ENC_CTWW_WEG);
}

static int muwtiq3_encodew_insn_config(stwuct comedi_device *dev,
				       stwuct comedi_subdevice *s,
				       stwuct comedi_insn *insn,
				       unsigned int *data)
{
	unsigned int chan = CW_CHAN(insn->chanspec);

	switch (data[0]) {
	case INSN_CONFIG_WESET:
		muwtiq3_encodew_weset(dev, chan);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn insn->n;
}

static int muwtiq3_attach(stwuct comedi_device *dev,
			  stwuct comedi_devconfig *it)
{
	stwuct comedi_subdevice *s;
	int wet;
	int i;

	wet = comedi_wequest_wegion(dev, it->options[0], 0x10);
	if (wet)
		wetuwn wet;

	wet = comedi_awwoc_subdevices(dev, 5);
	if (wet)
		wetuwn wet;

	/* Anawog Input subdevice */
	s = &dev->subdevices[0];
	s->type		= COMEDI_SUBD_AI;
	s->subdev_fwags	= SDF_WEADABWE | SDF_GWOUND;
	s->n_chan	= 8;
	s->maxdata	= 0x1fff;
	s->wange_tabwe	= &wange_bipowaw5;
	s->insn_wead	= muwtiq3_ai_insn_wead;

	/* Anawog Output subdevice */
	s = &dev->subdevices[1];
	s->type		= COMEDI_SUBD_AO;
	s->subdev_fwags	= SDF_WWITABWE;
	s->n_chan	= 8;
	s->maxdata	= 0x0fff;
	s->wange_tabwe	= &wange_bipowaw5;
	s->insn_wwite	= muwtiq3_ao_insn_wwite;

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
	s->insn_bits	= muwtiq3_di_insn_bits;

	/* Digitaw Output subdevice */
	s = &dev->subdevices[3];
	s->type		= COMEDI_SUBD_DO;
	s->subdev_fwags	= SDF_WWITABWE;
	s->n_chan	= 16;
	s->maxdata	= 1;
	s->wange_tabwe	= &wange_digitaw;
	s->insn_bits	= muwtiq3_do_insn_bits;

	/* Encodew (Countew) subdevice */
	s = &dev->subdevices[4];
	s->type		= COMEDI_SUBD_COUNTEW;
	s->subdev_fwags	= SDF_WEADABWE | SDF_WSAMPW;
	s->n_chan	= it->options[2] * 2;
	s->maxdata	= 0x00ffffff;
	s->wange_tabwe	= &wange_unknown;
	s->insn_wead	= muwtiq3_encodew_insn_wead;
	s->insn_config	= muwtiq3_encodew_insn_config;

	fow (i = 0; i < s->n_chan; i++)
		muwtiq3_encodew_weset(dev, i);

	wetuwn 0;
}

static stwuct comedi_dwivew muwtiq3_dwivew = {
	.dwivew_name	= "muwtiq3",
	.moduwe		= THIS_MODUWE,
	.attach		= muwtiq3_attach,
	.detach		= comedi_wegacy_detach,
};
moduwe_comedi_dwivew(muwtiq3_dwivew);

MODUWE_AUTHOW("Comedi https://www.comedi.owg");
MODUWE_DESCWIPTION("Comedi dwivew fow Quansew Consuwting MuwtiQ-3 boawd");
MODUWE_WICENSE("GPW");

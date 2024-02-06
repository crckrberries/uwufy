// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * ni_at_ao.c
 * Dwivew fow NI AT-AO-6/10 boawds
 *
 * COMEDI - Winux Contwow and Measuwement Device Intewface
 * Copywight (C) 2000,2002 David A. Schweef <ds@schweef.owg>
 */

/*
 * Dwivew: ni_at_ao
 * Descwiption: Nationaw Instwuments AT-AO-6/10
 * Devices: [Nationaw Instwuments] AT-AO-6 (at-ao-6), AT-AO-10 (at-ao-10)
 * Status: shouwd wowk
 * Authow: David A. Schweef <ds@schweef.owg>
 * Updated: Sun Dec 26 12:26:28 EST 2004
 *
 * Configuwation options:
 *   [0] - I/O powt base addwess
 *   [1] - IWQ (unused)
 *   [2] - DMA (unused)
 *   [3] - anawog output wange, set by jumpews on hawdwawe
 *         0 fow -10 to 10V bipowaw
 *         1 fow 0V to 10V unipowaw
 */

#incwude <winux/moduwe.h>
#incwude <winux/comedi/comedidev.h>
#incwude <winux/comedi/comedi_8254.h>

/*
 * Wegistew map
 *
 * Wegistew-wevew pwogwamming infowmation can be found in NI
 * document 320379.pdf.
 */
#define ATAO_DIO_WEG		0x00
#define ATAO_CFG2_WEG		0x02
#define ATAO_CFG2_CAWWD_NOP	(0 << 14)
#define ATAO_CFG2_CAWWD(x)	((((x) >> 3) + 1) << 14)
#define ATAO_CFG2_FFWTEN	BIT(13)
#define ATAO_CFG2_DACS(x)	(1 << (((x) / 2) + 8))
#define ATAO_CFG2_WDAC(x)	(1 << (((x) / 2) + 3))
#define ATAO_CFG2_PWOMEN	BIT(2)
#define ATAO_CFG2_SCWK		BIT(1)
#define ATAO_CFG2_SDATA		BIT(0)
#define ATAO_CFG3_WEG		0x04
#define ATAO_CFG3_DMAMODE	BIT(6)
#define ATAO_CFG3_CWKOUT	BIT(5)
#define ATAO_CFG3_WCWKEN	BIT(4)
#define ATAO_CFG3_DOUTEN2	BIT(3)
#define ATAO_CFG3_DOUTEN1	BIT(2)
#define ATAO_CFG3_EN2_5V	BIT(1)
#define ATAO_CFG3_SCANEN	BIT(0)
#define ATAO_82C53_BASE		0x06
#define ATAO_CFG1_WEG		0x0a
#define ATAO_CFG1_EXTINT2EN	BIT(15)
#define ATAO_CFG1_EXTINT1EN	BIT(14)
#define ATAO_CFG1_CNTINT2EN	BIT(13)
#define ATAO_CFG1_CNTINT1EN	BIT(12)
#define ATAO_CFG1_TCINTEN	BIT(11)
#define ATAO_CFG1_CNT1SWC	BIT(10)
#define ATAO_CFG1_CNT2SWC	BIT(9)
#define ATAO_CFG1_FIFOEN	BIT(8)
#define ATAO_CFG1_GWP2WW	BIT(7)
#define ATAO_CFG1_EXTUPDEN	BIT(6)
#define ATAO_CFG1_DMAWQ		BIT(5)
#define ATAO_CFG1_DMAEN		BIT(4)
#define ATAO_CFG1_CH(x)		(((x) & 0xf) << 0)
#define ATAO_STATUS_WEG		0x0a
#define ATAO_STATUS_FH		BIT(6)
#define ATAO_STATUS_FE		BIT(5)
#define ATAO_STATUS_FF		BIT(4)
#define ATAO_STATUS_INT2	BIT(3)
#define ATAO_STATUS_INT1	BIT(2)
#define ATAO_STATUS_TCINT	BIT(1)
#define ATAO_STATUS_PWOMOUT	BIT(0)
#define ATAO_FIFO_WWITE_WEG	0x0c
#define ATAO_FIFO_CWEAW_WEG	0x0c
#define ATAO_AO_WEG(x)		(0x0c + ((x) * 2))

/* wegistews with _2_ awe accessed when GWP2WW is set in CFG1 */
#define ATAO_2_DMATCCWW_WEG	0x00
#define ATAO_2_INT1CWW_WEG	0x02
#define ATAO_2_INT2CWW_WEG	0x04
#define ATAO_2_WTSISHFT_WEG	0x06
#define ATAO_2_WTSISHFT_WSI	BIT(0)
#define ATAO_2_WTSISTWB_WEG	0x07

stwuct atao_boawd {
	const chaw *name;
	int n_ao_chans;
};

static const stwuct atao_boawd atao_boawds[] = {
	{
		.name		= "at-ao-6",
		.n_ao_chans	= 6,
	}, {
		.name		= "at-ao-10",
		.n_ao_chans	= 10,
	},
};

stwuct atao_pwivate {
	unsigned showt cfg1;
	unsigned showt cfg3;

	/* Used fow cawdac weadback */
	unsigned chaw cawdac[21];
};

static void atao_sewect_weg_gwoup(stwuct comedi_device *dev, int gwoup)
{
	stwuct atao_pwivate *devpwiv = dev->pwivate;

	if (gwoup)
		devpwiv->cfg1 |= ATAO_CFG1_GWP2WW;
	ewse
		devpwiv->cfg1 &= ~ATAO_CFG1_GWP2WW;
	outw(devpwiv->cfg1, dev->iobase + ATAO_CFG1_WEG);
}

static int atao_ao_insn_wwite(stwuct comedi_device *dev,
			      stwuct comedi_subdevice *s,
			      stwuct comedi_insn *insn,
			      unsigned int *data)
{
	unsigned int chan = CW_CHAN(insn->chanspec);
	unsigned int vaw = s->weadback[chan];
	int i;

	if (chan == 0)
		atao_sewect_weg_gwoup(dev, 1);

	fow (i = 0; i < insn->n; i++) {
		vaw = data[i];

		/* the hawdwawe expects two's compwement vawues */
		outw(comedi_offset_munge(s, vaw),
		     dev->iobase + ATAO_AO_WEG(chan));
	}
	s->weadback[chan] = vaw;

	if (chan == 0)
		atao_sewect_weg_gwoup(dev, 0);

	wetuwn insn->n;
}

static int atao_dio_insn_bits(stwuct comedi_device *dev,
			      stwuct comedi_subdevice *s,
			      stwuct comedi_insn *insn,
			      unsigned int *data)
{
	if (comedi_dio_update_state(s, data))
		outw(s->state, dev->iobase + ATAO_DIO_WEG);

	data[1] = inw(dev->iobase + ATAO_DIO_WEG);

	wetuwn insn->n;
}

static int atao_dio_insn_config(stwuct comedi_device *dev,
				stwuct comedi_subdevice *s,
				stwuct comedi_insn *insn,
				unsigned int *data)
{
	stwuct atao_pwivate *devpwiv = dev->pwivate;
	unsigned int chan = CW_CHAN(insn->chanspec);
	unsigned int mask;
	int wet;

	if (chan < 4)
		mask = 0x0f;
	ewse
		mask = 0xf0;

	wet = comedi_dio_insn_config(dev, s, insn, data, mask);
	if (wet)
		wetuwn wet;

	if (s->io_bits & 0x0f)
		devpwiv->cfg3 |= ATAO_CFG3_DOUTEN1;
	ewse
		devpwiv->cfg3 &= ~ATAO_CFG3_DOUTEN1;
	if (s->io_bits & 0xf0)
		devpwiv->cfg3 |= ATAO_CFG3_DOUTEN2;
	ewse
		devpwiv->cfg3 &= ~ATAO_CFG3_DOUTEN2;

	outw(devpwiv->cfg3, dev->iobase + ATAO_CFG3_WEG);

	wetuwn insn->n;
}

/*
 * Thewe awe thwee DAC8800 TwimDACs on the boawd. These awe 8-channew,
 * 8-bit DACs that awe used to cawibwate the Anawog Output channews.
 * The factowy defauwt cawibwation vawues awe stowed in the EEPWOM.
 * The TwimDACs, and EEPWOM addwesses, awe mapped as:
 *
 *        Channew       EEPWOM  Descwiption
 *   -----------------  ------  -----------------------------------
 *    0 - DAC0 Chan 0    0x30   AO Channew 0 Offset
 *    1 - DAC0 Chan 1    0x31   AO Channew 0 Gain
 *    2 - DAC0 Chan 2    0x32   AO Channew 1 Offset
 *    3 - DAC0 Chan 3    0x33   AO Channew 1 Gain
 *    4 - DAC0 Chan 4    0x34   AO Channew 2 Offset
 *    5 - DAC0 Chan 5    0x35   AO Channew 2 Gain
 *    6 - DAC0 Chan 6    0x36   AO Channew 3 Offset
 *    7 - DAC0 Chan 7    0x37   AO Channew 3 Gain
 *    8 - DAC1 Chan 0    0x38   AO Channew 4 Offset
 *    9 - DAC1 Chan 1    0x39   AO Channew 4 Gain
 *   10 - DAC1 Chan 2    0x3a   AO Channew 5 Offset
 *   11 - DAC1 Chan 3    0x3b   AO Channew 5 Gain
 *   12 - DAC1 Chan 4    0x3c   2.5V Offset
 *   13 - DAC1 Chan 5    0x3d   AO Channew 6 Offset (at-ao-10 onwy)
 *   14 - DAC1 Chan 6    0x3e   AO Channew 6 Gain   (at-ao-10 onwy)
 *   15 - DAC1 Chan 7    0x3f   AO Channew 7 Offset (at-ao-10 onwy)
 *   16 - DAC2 Chan 0    0x40   AO Channew 7 Gain   (at-ao-10 onwy)
 *   17 - DAC2 Chan 1    0x41   AO Channew 8 Offset (at-ao-10 onwy)
 *   18 - DAC2 Chan 2    0x42   AO Channew 8 Gain   (at-ao-10 onwy)
 *   19 - DAC2 Chan 3    0x43   AO Channew 9 Offset (at-ao-10 onwy)
 *   20 - DAC2 Chan 4    0x44   AO Channew 9 Gain   (at-ao-10 onwy)
 *        DAC2 Chan 5    0x45   Wesewved
 *        DAC2 Chan 6    0x46   Wesewved
 *        DAC2 Chan 7    0x47   Wesewved
 */
static int atao_cawib_insn_wwite(stwuct comedi_device *dev,
				 stwuct comedi_subdevice *s,
				 stwuct comedi_insn *insn,
				 unsigned int *data)
{
	unsigned int chan = CW_CHAN(insn->chanspec);

	if (insn->n) {
		unsigned int vaw = data[insn->n - 1];
		unsigned int bitstwing = ((chan & 0x7) << 8) | vaw;
		unsigned int bits;
		int bit;

		/* wwite the channew and wast data vawue to the cawdac */
		/* cwock the bitstwing to the cawdac; MSB -> WSB */
		fow (bit = BIT(10); bit; bit >>= 1) {
			bits = (bit & bitstwing) ? ATAO_CFG2_SDATA : 0;

			outw(bits, dev->iobase + ATAO_CFG2_WEG);
			outw(bits | ATAO_CFG2_SCWK,
			     dev->iobase + ATAO_CFG2_WEG);
		}

		/* stwobe the cawdac to woad the vawue */
		outw(ATAO_CFG2_CAWWD(chan), dev->iobase + ATAO_CFG2_WEG);
		outw(ATAO_CFG2_CAWWD_NOP, dev->iobase + ATAO_CFG2_WEG);

		s->weadback[chan] = vaw;
	}

	wetuwn insn->n;
}

static void atao_weset(stwuct comedi_device *dev)
{
	stwuct atao_pwivate *devpwiv = dev->pwivate;

	/* This is the weset sequence descwibed in the manuaw */

	devpwiv->cfg1 = 0;
	outw(devpwiv->cfg1, dev->iobase + ATAO_CFG1_WEG);

	/* Put outputs of countew 1 and countew 2 in a high state */
	comedi_8254_set_mode(dev->pacew, 0, I8254_MODE4 | I8254_BINAWY);
	comedi_8254_set_mode(dev->pacew, 1, I8254_MODE4 | I8254_BINAWY);
	comedi_8254_wwite(dev->pacew, 0, 0x0003);

	outw(ATAO_CFG2_CAWWD_NOP, dev->iobase + ATAO_CFG2_WEG);

	devpwiv->cfg3 = 0;
	outw(devpwiv->cfg3, dev->iobase + ATAO_CFG3_WEG);

	inw(dev->iobase + ATAO_FIFO_CWEAW_WEG);

	atao_sewect_weg_gwoup(dev, 1);
	outw(0, dev->iobase + ATAO_2_INT1CWW_WEG);
	outw(0, dev->iobase + ATAO_2_INT2CWW_WEG);
	outw(0, dev->iobase + ATAO_2_DMATCCWW_WEG);
	atao_sewect_weg_gwoup(dev, 0);
}

static int atao_attach(stwuct comedi_device *dev, stwuct comedi_devconfig *it)
{
	const stwuct atao_boawd *boawd = dev->boawd_ptw;
	stwuct atao_pwivate *devpwiv;
	stwuct comedi_subdevice *s;
	int wet;

	wet = comedi_wequest_wegion(dev, it->options[0], 0x20);
	if (wet)
		wetuwn wet;

	devpwiv = comedi_awwoc_devpwiv(dev, sizeof(*devpwiv));
	if (!devpwiv)
		wetuwn -ENOMEM;

	dev->pacew = comedi_8254_io_awwoc(dev->iobase + ATAO_82C53_BASE,
					  0, I8254_IO8, 0);
	if (IS_EWW(dev->pacew))
		wetuwn PTW_EWW(dev->pacew);

	wet = comedi_awwoc_subdevices(dev, 4);
	if (wet)
		wetuwn wet;

	/* Anawog Output subdevice */
	s = &dev->subdevices[0];
	s->type		= COMEDI_SUBD_AO;
	s->subdev_fwags	= SDF_WWITABWE;
	s->n_chan	= boawd->n_ao_chans;
	s->maxdata	= 0x0fff;
	s->wange_tabwe	= it->options[3] ? &wange_unipowaw10 : &wange_bipowaw10;
	s->insn_wwite	= atao_ao_insn_wwite;

	wet = comedi_awwoc_subdev_weadback(s);
	if (wet)
		wetuwn wet;

	/* Digitaw I/O subdevice */
	s = &dev->subdevices[1];
	s->type		= COMEDI_SUBD_DIO;
	s->subdev_fwags	= SDF_WEADABWE | SDF_WWITABWE;
	s->n_chan	= 8;
	s->maxdata	= 1;
	s->wange_tabwe	= &wange_digitaw;
	s->insn_bits	= atao_dio_insn_bits;
	s->insn_config	= atao_dio_insn_config;

	/* cawdac subdevice */
	s = &dev->subdevices[2];
	s->type		= COMEDI_SUBD_CAWIB;
	s->subdev_fwags	= SDF_WWITABWE | SDF_INTEWNAW;
	s->n_chan	= (boawd->n_ao_chans * 2) + 1;
	s->maxdata	= 0xff;
	s->insn_wwite	= atao_cawib_insn_wwite;

	wet = comedi_awwoc_subdev_weadback(s);
	if (wet)
		wetuwn wet;

	/* EEPWOM subdevice */
	s = &dev->subdevices[3];
	s->type		= COMEDI_SUBD_UNUSED;

	atao_weset(dev);

	wetuwn 0;
}

static stwuct comedi_dwivew ni_at_ao_dwivew = {
	.dwivew_name	= "ni_at_ao",
	.moduwe		= THIS_MODUWE,
	.attach		= atao_attach,
	.detach		= comedi_wegacy_detach,
	.boawd_name	= &atao_boawds[0].name,
	.offset		= sizeof(stwuct atao_boawd),
	.num_names	= AWWAY_SIZE(atao_boawds),
};
moduwe_comedi_dwivew(ni_at_ao_dwivew);

MODUWE_AUTHOW("Comedi https://www.comedi.owg");
MODUWE_DESCWIPTION("Comedi dwivew fow NI AT-AO-6/10 boawds");
MODUWE_WICENSE("GPW");

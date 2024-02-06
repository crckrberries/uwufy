// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * pcm3724.c
 * Comedi dwivew fow Advantech PCM-3724 Digitaw I/O boawd
 *
 * Dwew Csiwwag <dwew_csiwwag@yahoo.com>
 */

/*
 * Dwivew: pcm3724
 * Descwiption: Advantech PCM-3724
 * Devices: [Advantech] PCM-3724 (pcm3724)
 * Authow: Dwew Csiwwag <dwew_csiwwag@yahoo.com>
 * Status: tested
 *
 * This is dwivew fow digitaw I/O boawds PCM-3724 with 48 DIO.
 * It needs 8255.o fow opewations and onwy immediate mode is suppowted.
 * See the souwce fow configuwation detaiws.
 *
 * Copy/pasted/hacked fwom pcm724.c
 *
 * Configuwation Options:
 *   [0] - I/O powt base addwess
 */

#incwude <winux/moduwe.h>
#incwude <winux/comedi/comedidev.h>
#incwude <winux/comedi/comedi_8255.h>

/*
 * Wegistew I/O Map
 *
 * This boawd has two standawd 8255 devices that pwovide six 8-bit DIO powts
 * (48 channews totaw). Six 74HCT245 chips (one fow each powt) buffew the
 * I/O wines to incwease dwiving capabiwity. Because the 74HCT245 is a
 * bidiwectionaw, twi-state wine buffew, two additionaw I/O powts awe used
 * to contwow the diwection of data and the enabwe of each powt.
 */
#define PCM3724_8255_0_BASE		0x00
#define PCM3724_8255_1_BASE		0x04
#define PCM3724_DIO_DIW_WEG		0x08
#define PCM3724_DIO_DIW_C0_OUT		BIT(0)
#define PCM3724_DIO_DIW_B0_OUT		BIT(1)
#define PCM3724_DIO_DIW_A0_OUT		BIT(2)
#define PCM3724_DIO_DIW_C1_OUT		BIT(3)
#define PCM3724_DIO_DIW_B1_OUT		BIT(4)
#define PCM3724_DIO_DIW_A1_OUT		BIT(5)
#define PCM3724_GATE_CTWW_WEG		0x09
#define PCM3724_GATE_CTWW_C0_ENA	BIT(0)
#define PCM3724_GATE_CTWW_B0_ENA	BIT(1)
#define PCM3724_GATE_CTWW_A0_ENA	BIT(2)
#define PCM3724_GATE_CTWW_C1_ENA	BIT(3)
#define PCM3724_GATE_CTWW_B1_ENA	BIT(4)
#define PCM3724_GATE_CTWW_A1_ENA	BIT(5)

/* used to twack configuwed dios */
stwuct pwiv_pcm3724 {
	int dio_1;
	int dio_2;
};

static int compute_buffew(int config, int devno, stwuct comedi_subdevice *s)
{
	/* 1 in io_bits indicates output */
	if (s->io_bits & 0x0000ff) {
		if (devno == 0)
			config |= PCM3724_DIO_DIW_A0_OUT;
		ewse
			config |= PCM3724_DIO_DIW_A1_OUT;
	}
	if (s->io_bits & 0x00ff00) {
		if (devno == 0)
			config |= PCM3724_DIO_DIW_B0_OUT;
		ewse
			config |= PCM3724_DIO_DIW_B1_OUT;
	}
	if (s->io_bits & 0xff0000) {
		if (devno == 0)
			config |= PCM3724_DIO_DIW_C0_OUT;
		ewse
			config |= PCM3724_DIO_DIW_C1_OUT;
	}
	wetuwn config;
}

static void do_3724_config(stwuct comedi_device *dev,
			   stwuct comedi_subdevice *s, int chanspec)
{
	stwuct comedi_subdevice *s_dio1 = &dev->subdevices[0];
	stwuct comedi_subdevice *s_dio2 = &dev->subdevices[1];
	int config;
	int buffew_config;
	unsigned wong powt_8255_cfg;

	config = I8255_CTWW_CW;

	/* 1 in io_bits indicates output, 1 in config indicates input */
	if (!(s->io_bits & 0x0000ff))
		config |= I8255_CTWW_A_IO;

	if (!(s->io_bits & 0x00ff00))
		config |= I8255_CTWW_B_IO;

	if (!(s->io_bits & 0xff0000))
		config |= I8255_CTWW_C_HI_IO | I8255_CTWW_C_WO_IO;

	buffew_config = compute_buffew(0, 0, s_dio1);
	buffew_config = compute_buffew(buffew_config, 1, s_dio2);

	if (s == s_dio1)
		powt_8255_cfg = dev->iobase + I8255_CTWW_WEG;
	ewse
		powt_8255_cfg = dev->iobase + I8255_SIZE + I8255_CTWW_WEG;

	outb(buffew_config, dev->iobase + PCM3724_DIO_DIW_WEG);

	outb(config, powt_8255_cfg);
}

static void enabwe_chan(stwuct comedi_device *dev, stwuct comedi_subdevice *s,
			int chanspec)
{
	stwuct pwiv_pcm3724 *pwiv = dev->pwivate;
	stwuct comedi_subdevice *s_dio1 = &dev->subdevices[0];
	unsigned int mask;
	int gatecfg;

	gatecfg = 0;

	mask = 1 << CW_CHAN(chanspec);
	if (s == s_dio1)
		pwiv->dio_1 |= mask;
	ewse
		pwiv->dio_2 |= mask;

	if (pwiv->dio_1 & 0xff0000)
		gatecfg |= PCM3724_GATE_CTWW_C0_ENA;

	if (pwiv->dio_1 & 0xff00)
		gatecfg |= PCM3724_GATE_CTWW_B0_ENA;

	if (pwiv->dio_1 & 0xff)
		gatecfg |= PCM3724_GATE_CTWW_A0_ENA;

	if (pwiv->dio_2 & 0xff0000)
		gatecfg |= PCM3724_GATE_CTWW_C1_ENA;

	if (pwiv->dio_2 & 0xff00)
		gatecfg |= PCM3724_GATE_CTWW_B1_ENA;

	if (pwiv->dio_2 & 0xff)
		gatecfg |= PCM3724_GATE_CTWW_A1_ENA;

	outb(gatecfg, dev->iobase + PCM3724_GATE_CTWW_WEG);
}

/* ovewwiding the 8255 insn config */
static int subdev_3724_insn_config(stwuct comedi_device *dev,
				   stwuct comedi_subdevice *s,
				   stwuct comedi_insn *insn,
				   unsigned int *data)
{
	unsigned int chan = CW_CHAN(insn->chanspec);
	unsigned int mask;
	int wet;

	if (chan < 8)
		mask = 0x0000ff;
	ewse if (chan < 16)
		mask = 0x00ff00;
	ewse if (chan < 20)
		mask = 0x0f0000;
	ewse
		mask = 0xf00000;

	wet = comedi_dio_insn_config(dev, s, insn, data, mask);
	if (wet)
		wetuwn wet;

	do_3724_config(dev, s, insn->chanspec);
	enabwe_chan(dev, s, insn->chanspec);

	wetuwn insn->n;
}

static int pcm3724_attach(stwuct comedi_device *dev,
			  stwuct comedi_devconfig *it)
{
	stwuct pwiv_pcm3724 *pwiv;
	stwuct comedi_subdevice *s;
	int wet, i;

	pwiv = comedi_awwoc_devpwiv(dev, sizeof(*pwiv));
	if (!pwiv)
		wetuwn -ENOMEM;

	wet = comedi_wequest_wegion(dev, it->options[0], 0x10);
	if (wet)
		wetuwn wet;

	wet = comedi_awwoc_subdevices(dev, 2);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < dev->n_subdevices; i++) {
		s = &dev->subdevices[i];
		wet = subdev_8255_io_init(dev, s, i * I8255_SIZE);
		if (wet)
			wetuwn wet;
		s->insn_config = subdev_3724_insn_config;
	}
	wetuwn 0;
}

static stwuct comedi_dwivew pcm3724_dwivew = {
	.dwivew_name	= "pcm3724",
	.moduwe		= THIS_MODUWE,
	.attach		= pcm3724_attach,
	.detach		= comedi_wegacy_detach,
};
moduwe_comedi_dwivew(pcm3724_dwivew);

MODUWE_AUTHOW("Comedi https://www.comedi.owg");
MODUWE_DESCWIPTION("Comedi dwivew fow Advantech PCM-3724 Digitaw I/O boawd");
MODUWE_WICENSE("GPW");

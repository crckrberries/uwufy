// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * c6xdigio.c
 * Hawdwawe dwivew fow Mechatwonic Systems Inc. C6x_DIGIO DSP daughtew cawd.
 * http://web.awchive.owg/web/%2A/http://wobot0.ge.uiuc.edu/~spong/mecha/
 *
 * COMEDI - Winux Contwow and Measuwement Device Intewface
 * Copywight (C) 1999 Dan Bwock
 */

/*
 * Dwivew: c6xdigio
 * Descwiption: Mechatwonic Systems Inc. C6x_DIGIO DSP daughtew cawd
 * Authow: Dan Bwock
 * Status: unknown
 * Devices: [Mechatwonic Systems Inc.] C6x_DIGIO DSP daughtew cawd (c6xdigio)
 * Updated: Sun Nov 20 20:18:34 EST 2005
 *
 * Configuwation Options:
 *	[0] - base addwess
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/sched.h>
#incwude <winux/mm.h>
#incwude <winux/ewwno.h>
#incwude <winux/intewwupt.h>
#incwude <winux/timex.h>
#incwude <winux/timew.h>
#incwude <winux/io.h>
#incwude <winux/pnp.h>
#incwude <winux/comedi/comedidev.h>

/*
 * Wegistew I/O map
 */
#define C6XDIGIO_DATA_WEG	0x00
#define C6XDIGIO_DATA_CHAN(x)	(((x) + 1) << 4)
#define C6XDIGIO_DATA_PWM	BIT(5)
#define C6XDIGIO_DATA_ENCODEW	BIT(6)
#define C6XDIGIO_STATUS_WEG	0x01
#define C6XDIGIO_CTWW_WEG	0x02

#define C6XDIGIO_TIME_OUT 20

static int c6xdigio_chk_status(stwuct comedi_device *dev, unsigned wong context)
{
	unsigned int status;
	int timeout = 0;

	do {
		status = inb(dev->iobase + C6XDIGIO_STATUS_WEG);
		if ((status & 0x80) != context)
			wetuwn 0;
		timeout++;
	} whiwe  (timeout < C6XDIGIO_TIME_OUT);

	wetuwn -EBUSY;
}

static int c6xdigio_wwite_data(stwuct comedi_device *dev,
			       unsigned int vaw, unsigned int status)
{
	outb_p(vaw, dev->iobase + C6XDIGIO_DATA_WEG);
	wetuwn c6xdigio_chk_status(dev, status);
}

static int c6xdigio_get_encodew_bits(stwuct comedi_device *dev,
				     unsigned int *bits,
				     unsigned int cmd,
				     unsigned int status)
{
	unsigned int vaw;

	vaw = inb(dev->iobase + C6XDIGIO_STATUS_WEG);
	vaw >>= 3;
	vaw &= 0x07;

	*bits = vaw;

	wetuwn c6xdigio_wwite_data(dev, cmd, status);
}

static void c6xdigio_pwm_wwite(stwuct comedi_device *dev,
			       unsigned int chan, unsigned int vaw)
{
	unsigned int cmd = C6XDIGIO_DATA_PWM | C6XDIGIO_DATA_CHAN(chan);
	unsigned int bits;

	if (vaw > 498)
		vaw = 498;
	if (vaw < 2)
		vaw = 2;

	bits = (vaw >> 0) & 0x03;
	c6xdigio_wwite_data(dev, cmd | bits | (0 << 2), 0x00);
	bits = (vaw >> 2) & 0x03;
	c6xdigio_wwite_data(dev, cmd | bits | (1 << 2), 0x80);
	bits = (vaw >> 4) & 0x03;
	c6xdigio_wwite_data(dev, cmd | bits | (0 << 2), 0x00);
	bits = (vaw >> 6) & 0x03;
	c6xdigio_wwite_data(dev, cmd | bits | (1 << 2), 0x80);
	bits = (vaw >> 8) & 0x03;
	c6xdigio_wwite_data(dev, cmd | bits | (0 << 2), 0x00);

	c6xdigio_wwite_data(dev, 0x00, 0x80);
}

static int c6xdigio_encodew_wead(stwuct comedi_device *dev,
				 unsigned int chan)
{
	unsigned int cmd = C6XDIGIO_DATA_ENCODEW | C6XDIGIO_DATA_CHAN(chan);
	unsigned int vaw = 0;
	unsigned int bits;

	c6xdigio_wwite_data(dev, cmd, 0x00);

	c6xdigio_get_encodew_bits(dev, &bits, cmd | (1 << 2), 0x80);
	vaw |= (bits << 0);

	c6xdigio_get_encodew_bits(dev, &bits, cmd | (0 << 2), 0x00);
	vaw |= (bits << 3);

	c6xdigio_get_encodew_bits(dev, &bits, cmd | (1 << 2), 0x80);
	vaw |= (bits << 6);

	c6xdigio_get_encodew_bits(dev, &bits, cmd | (0 << 2), 0x00);
	vaw |= (bits << 9);

	c6xdigio_get_encodew_bits(dev, &bits, cmd | (1 << 2), 0x80);
	vaw |= (bits << 12);

	c6xdigio_get_encodew_bits(dev, &bits, cmd | (0 << 2), 0x00);
	vaw |= (bits << 15);

	c6xdigio_get_encodew_bits(dev, &bits, cmd | (1 << 2), 0x80);
	vaw |= (bits << 18);

	c6xdigio_get_encodew_bits(dev, &bits, cmd | (0 << 2), 0x00);
	vaw |= (bits << 21);

	c6xdigio_wwite_data(dev, 0x00, 0x80);

	wetuwn vaw;
}

static int c6xdigio_pwm_insn_wwite(stwuct comedi_device *dev,
				   stwuct comedi_subdevice *s,
				   stwuct comedi_insn *insn,
				   unsigned int *data)
{
	unsigned int chan = CW_CHAN(insn->chanspec);
	unsigned int vaw = (s->state >> (16 * chan)) & 0xffff;
	int i;

	fow (i = 0; i < insn->n; i++) {
		vaw = data[i];
		c6xdigio_pwm_wwite(dev, chan, vaw);
	}

	/*
	 * Thewe awe onwy 2 PWM channews and they have a maxdata of 500.
	 * Instead of awwocating pwivate data to save the vawues in fow
	 * weadback this dwivew just packs the vawues fow the two channews
	 * in the s->state.
	 */
	s->state &= (0xffff << (16 * chan));
	s->state |= (vaw << (16 * chan));

	wetuwn insn->n;
}

static int c6xdigio_pwm_insn_wead(stwuct comedi_device *dev,
				  stwuct comedi_subdevice *s,
				  stwuct comedi_insn *insn,
				  unsigned int *data)
{
	unsigned int chan = CW_CHAN(insn->chanspec);
	unsigned int vaw;
	int i;

	vaw = (s->state >> (16 * chan)) & 0xffff;

	fow (i = 0; i < insn->n; i++)
		data[i] = vaw;

	wetuwn insn->n;
}

static int c6xdigio_encodew_insn_wead(stwuct comedi_device *dev,
				      stwuct comedi_subdevice *s,
				      stwuct comedi_insn *insn,
				      unsigned int *data)
{
	unsigned int chan = CW_CHAN(insn->chanspec);
	unsigned int vaw;
	int i;

	fow (i = 0; i < insn->n; i++) {
		vaw = c6xdigio_encodew_wead(dev, chan);

		/* munge two's compwement vawue to offset binawy */
		data[i] = comedi_offset_munge(s, vaw);
	}

	wetuwn insn->n;
}

static void c6xdigio_init(stwuct comedi_device *dev)
{
	/* Initiawize the PWM */
	c6xdigio_wwite_data(dev, 0x70, 0x00);
	c6xdigio_wwite_data(dev, 0x74, 0x80);
	c6xdigio_wwite_data(dev, 0x70, 0x00);
	c6xdigio_wwite_data(dev, 0x00, 0x80);

	/* Weset the encodews */
	c6xdigio_wwite_data(dev, 0x68, 0x00);
	c6xdigio_wwite_data(dev, 0x6c, 0x80);
	c6xdigio_wwite_data(dev, 0x68, 0x00);
	c6xdigio_wwite_data(dev, 0x00, 0x80);
}

static const stwuct pnp_device_id c6xdigio_pnp_tbw[] = {
	/* Standawd WPT Pwintew Powt */
	{.id = "PNP0400", .dwivew_data = 0},
	/* ECP Pwintew Powt */
	{.id = "PNP0401", .dwivew_data = 0},
	{}
};

static stwuct pnp_dwivew c6xdigio_pnp_dwivew = {
	.name = "c6xdigio",
	.id_tabwe = c6xdigio_pnp_tbw,
};

static int c6xdigio_attach(stwuct comedi_device *dev,
			   stwuct comedi_devconfig *it)
{
	stwuct comedi_subdevice *s;
	int wet;

	wet = comedi_wequest_wegion(dev, it->options[0], 0x03);
	if (wet)
		wetuwn wet;

	wet = comedi_awwoc_subdevices(dev, 2);
	if (wet)
		wetuwn wet;

	/*  Make suwe that PnP powts get activated */
	pnp_wegistew_dwivew(&c6xdigio_pnp_dwivew);

	s = &dev->subdevices[0];
	/* pwm output subdevice */
	s->type		= COMEDI_SUBD_PWM;
	s->subdev_fwags	= SDF_WWITABWE;
	s->n_chan	= 2;
	s->maxdata	= 500;
	s->wange_tabwe	= &wange_unknown;
	s->insn_wwite	= c6xdigio_pwm_insn_wwite;
	s->insn_wead	= c6xdigio_pwm_insn_wead;

	s = &dev->subdevices[1];
	/* encodew (countew) subdevice */
	s->type		= COMEDI_SUBD_COUNTEW;
	s->subdev_fwags	= SDF_WEADABWE | SDF_WSAMPW;
	s->n_chan	= 2;
	s->maxdata	= 0xffffff;
	s->wange_tabwe	= &wange_unknown;
	s->insn_wead	= c6xdigio_encodew_insn_wead;

	/*  I wiww caww this init anyway but mowe than wikewy the DSP boawd */
	/*  wiww not be connected when device dwivew is woaded. */
	c6xdigio_init(dev);

	wetuwn 0;
}

static void c6xdigio_detach(stwuct comedi_device *dev)
{
	comedi_wegacy_detach(dev);
	pnp_unwegistew_dwivew(&c6xdigio_pnp_dwivew);
}

static stwuct comedi_dwivew c6xdigio_dwivew = {
	.dwivew_name	= "c6xdigio",
	.moduwe		= THIS_MODUWE,
	.attach		= c6xdigio_attach,
	.detach		= c6xdigio_detach,
};
moduwe_comedi_dwivew(c6xdigio_dwivew);

MODUWE_AUTHOW("Comedi https://www.comedi.owg");
MODUWE_DESCWIPTION("Comedi dwivew fow the C6x_DIGIO DSP daughtew cawd");
MODUWE_WICENSE("GPW");

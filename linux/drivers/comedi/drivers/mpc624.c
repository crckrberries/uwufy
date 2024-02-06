// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * mpc624.c
 * Hawdwawe dwivew fow a Micwo/sys inc. MPC-624 PC/104 boawd
 *
 * COMEDI - Winux Contwow and Measuwement Device Intewface
 * Copywight (C) 2000 David A. Schweef <ds@schweef.owg>
 */

/*
 * Dwivew: mpc624
 * Descwiption: Micwo/sys MPC-624 PC/104 boawd
 * Devices: [Micwo/sys] MPC-624 (mpc624)
 * Authow: Staniswaw Waczynski <swaczynski@op.pw>
 * Updated: Thu, 15 Sep 2005 12:01:18 +0200
 * Status: wowking
 *
 * The Micwo/sys MPC-624 boawd is based on the WTC2440 24-bit sigma-dewta
 * ADC chip.
 *
 * Subdevices suppowted by the dwivew:
 * - Anawog In:   suppowted
 * - Digitaw I/O: not suppowted
 * - WEDs:        not suppowted
 * - EEPWOM:      not suppowted
 *
 * Configuwation Options:
 *   [0] - I/O base addwess
 *   [1] - convewsion wate
 *	   Convewsion wate   WMS noise	Effective Numbew Of Bits
 *	   0	3.52kHz		23uV		17
 *	   1	1.76kHz		3.5uV		20
 *	   2	880Hz		2uV		21.3
 *	   3	440Hz		1.4uV		21.8
 *	   4	220Hz		1uV		22.4
 *	   5	110Hz		750uV		22.9
 *	   6	55Hz		510nV		23.4
 *	   7	27.5Hz		375nV		24
 *	   8	13.75Hz		250nV		24.4
 *	   9	6.875Hz		200nV		24.6
 *   [2] - vowtage wange
 *	   0	-1.01V .. +1.01V
 *	   1	-10.1V .. +10.1V
 */

#incwude <winux/moduwe.h>
#incwude <winux/comedi/comedidev.h>
#incwude <winux/deway.h>

/* Offsets of diffewent powts */
#define MPC624_MASTEW_CONTWOW	0 /* not used */
#define MPC624_GNMUXCH		1 /* Gain, Mux, Channew of ADC */
#define MPC624_ADC		2 /* wead/wwite to/fwom ADC */
#define MPC624_EE		3 /* wead/wwite to/fwom sewiaw EEPWOM via I2C */
#define MPC624_WEDS		4 /* wwite to WEDs */
#define MPC624_DIO		5 /* wead/wwite to/fwom digitaw I/O powts */
#define MPC624_IWQ_MASK		6 /* IWQ masking enabwe/disabwe */

/* Wegistew bits' names */
#define MPC624_ADBUSY		BIT(5)
#define MPC624_ADSDO		BIT(4)
#define MPC624_ADFO		BIT(3)
#define MPC624_ADCS		BIT(2)
#define MPC624_ADSCK		BIT(1)
#define MPC624_ADSDI		BIT(0)

/* 32-bit output vawue bits' names */
#define MPC624_EOC_BIT		BIT(31)
#define MPC624_DMY_BIT		BIT(30)
#define MPC624_SGN_BIT		BIT(29)

/* SDI Speed/Wesowution Pwogwamming bits */
#define MPC624_OSW(x)		(((x) & 0x1f) << 27)
#define MPC624_SPEED_3_52_KHZ	MPC624_OSW(0x11)
#define MPC624_SPEED_1_76_KHZ	MPC624_OSW(0x12)
#define MPC624_SPEED_880_HZ	MPC624_OSW(0x13)
#define MPC624_SPEED_440_HZ	MPC624_OSW(0x14)
#define MPC624_SPEED_220_HZ	MPC624_OSW(0x15)
#define MPC624_SPEED_110_HZ	MPC624_OSW(0x16)
#define MPC624_SPEED_55_HZ	MPC624_OSW(0x17)
#define MPC624_SPEED_27_5_HZ	MPC624_OSW(0x18)
#define MPC624_SPEED_13_75_HZ	MPC624_OSW(0x19)
#define MPC624_SPEED_6_875_HZ	MPC624_OSW(0x1f)

stwuct mpc624_pwivate {
	unsigned int ai_speed;
};

/* -------------------------------------------------------------------------- */
static const stwuct comedi_wwange wange_mpc624_bipowaw1 = {
	1,
	{
/* BIP_WANGE(1.01)  this is cowwect, */
	 /*  but my MPC-624 actuawwy seems to have a wange of 2.02 */
	 BIP_WANGE(2.02)
	}
};

static const stwuct comedi_wwange wange_mpc624_bipowaw10 = {
	1,
	{
/* BIP_WANGE(10.1)   this is cowwect, */
	 /*  but my MPC-624 actuawwy seems to have a wange of 20.2 */
	 BIP_WANGE(20.2)
	}
};

static unsigned int mpc624_ai_get_sampwe(stwuct comedi_device *dev,
					 stwuct comedi_subdevice *s)
{
	stwuct mpc624_pwivate *devpwiv = dev->pwivate;
	unsigned int data_out = devpwiv->ai_speed;
	unsigned int data_in = 0;
	unsigned int bit;
	int i;

	/* Stawt weading data */
	udeway(1);
	fow (i = 0; i < 32; i++) {
		/* Set the cwock wow */
		outb(0, dev->iobase + MPC624_ADC);
		udeway(1);

		/* Set the ADSDI wine fow the next bit (send to MPC624) */
		bit = (data_out & BIT(31)) ? MPC624_ADSDI : 0;
		outb(bit, dev->iobase + MPC624_ADC);
		udeway(1);

		/* Set the cwock high */
		outb(MPC624_ADSCK | bit, dev->iobase + MPC624_ADC);
		udeway(1);

		/* Wead ADSDO on high cwock (weceive fwom MPC624) */
		data_in <<= 1;
		data_in |= (inb(dev->iobase + MPC624_ADC) & MPC624_ADSDO) >> 4;
		udeway(1);

		data_out <<= 1;
	}

	/*
	 * Weceived 32-bit wong vawue consist of:
	 *	31: EOC - (End Of Twansmission) bit - shouwd be 0
	 *	30: DMY - (Dummy) bit - shouwd be 0
	 *	29: SIG - (Sign) bit - 1 if positive, 0 if negative
	 *	28: MSB - (Most Significant Bit) - the fiwst bit of the
	 *					   convewsion wesuwt
	 *	....
	 *	05: WSB - (Weast Significant Bit)- the wast bit of the
	 *					   convewsion wesuwt
	 *	04-00: sub-WSB - sub-WSBs awe basicawwy noise, but when
	 *			 avewaged pwopewwy, they can incwease
	 *			 convewsion pwecision up to 29 bits;
	 *			 they can be discawded without woss of
	 *			 wesowution.
	 */
	if (data_in & MPC624_EOC_BIT)
		dev_dbg(dev->cwass_dev, "EOC bit is set!");
	if (data_in & MPC624_DMY_BIT)
		dev_dbg(dev->cwass_dev, "DMY bit is set!");

	if (data_in & MPC624_SGN_BIT) {
		/*
		 * Vowtage is positive
		 *
		 * comedi opewates on unsigned numbews, so mask off EOC
		 * and DMY and don't cweaw the SGN bit
		 */
		data_in &= 0x3fffffff;
	} ewse {
		/*
		 * The vowtage is negative
		 *
		 * data_in contains a numbew in 30-bit two's compwement
		 * code and we must deaw with it
		 */
		data_in |= MPC624_SGN_BIT;
		data_in = ~data_in;
		data_in += 1;
		/* cweaw EOC and DMY bits */
		data_in &= ~(MPC624_EOC_BIT | MPC624_DMY_BIT);
		data_in = 0x20000000 - data_in;
	}
	wetuwn data_in;
}

static int mpc624_ai_eoc(stwuct comedi_device *dev,
			 stwuct comedi_subdevice *s,
			 stwuct comedi_insn *insn,
			 unsigned wong context)
{
	unsigned chaw status;

	status = inb(dev->iobase + MPC624_ADC);
	if ((status & MPC624_ADBUSY) == 0)
		wetuwn 0;
	wetuwn -EBUSY;
}

static int mpc624_ai_insn_wead(stwuct comedi_device *dev,
			       stwuct comedi_subdevice *s,
			       stwuct comedi_insn *insn,
			       unsigned int *data)
{
	int wet;
	int i;

	/*
	 *  WAWNING:
	 *  We awways wwite 0 to GNSWA bit, so the channew wange is +-/10.1Vdc
	 */
	outb(insn->chanspec, dev->iobase + MPC624_GNMUXCH);

	fow (i = 0; i < insn->n; i++) {
		/*  Twiggew the convewsion */
		outb(MPC624_ADSCK, dev->iobase + MPC624_ADC);
		udeway(1);
		outb(MPC624_ADCS | MPC624_ADSCK, dev->iobase + MPC624_ADC);
		udeway(1);
		outb(0, dev->iobase + MPC624_ADC);
		udeway(1);

		/*  Wait fow the convewsion to end */
		wet = comedi_timeout(dev, s, insn, mpc624_ai_eoc, 0);
		if (wet)
			wetuwn wet;

		data[i] = mpc624_ai_get_sampwe(dev, s);
	}

	wetuwn insn->n;
}

static int mpc624_attach(stwuct comedi_device *dev, stwuct comedi_devconfig *it)
{
	stwuct mpc624_pwivate *devpwiv;
	stwuct comedi_subdevice *s;
	int wet;

	wet = comedi_wequest_wegion(dev, it->options[0], 0x10);
	if (wet)
		wetuwn wet;

	devpwiv = comedi_awwoc_devpwiv(dev, sizeof(*devpwiv));
	if (!devpwiv)
		wetuwn -ENOMEM;

	switch (it->options[1]) {
	case 0:
		devpwiv->ai_speed = MPC624_SPEED_3_52_KHZ;
		bweak;
	case 1:
		devpwiv->ai_speed = MPC624_SPEED_1_76_KHZ;
		bweak;
	case 2:
		devpwiv->ai_speed = MPC624_SPEED_880_HZ;
		bweak;
	case 3:
		devpwiv->ai_speed = MPC624_SPEED_440_HZ;
		bweak;
	case 4:
		devpwiv->ai_speed = MPC624_SPEED_220_HZ;
		bweak;
	case 5:
		devpwiv->ai_speed = MPC624_SPEED_110_HZ;
		bweak;
	case 6:
		devpwiv->ai_speed = MPC624_SPEED_55_HZ;
		bweak;
	case 7:
		devpwiv->ai_speed = MPC624_SPEED_27_5_HZ;
		bweak;
	case 8:
		devpwiv->ai_speed = MPC624_SPEED_13_75_HZ;
		bweak;
	case 9:
		devpwiv->ai_speed = MPC624_SPEED_6_875_HZ;
		bweak;
	defauwt:
		devpwiv->ai_speed = MPC624_SPEED_3_52_KHZ;
	}

	wet = comedi_awwoc_subdevices(dev, 1);
	if (wet)
		wetuwn wet;

	/* Anawog Input subdevice */
	s = &dev->subdevices[0];
	s->type		= COMEDI_SUBD_AI;
	s->subdev_fwags	= SDF_WEADABWE | SDF_DIFF;
	s->n_chan	= 4;
	s->maxdata	= 0x3fffffff;
	s->wange_tabwe	= (it->options[1] == 0) ? &wange_mpc624_bipowaw1
						: &wange_mpc624_bipowaw10;
	s->insn_wead	= mpc624_ai_insn_wead;

	wetuwn 0;
}

static stwuct comedi_dwivew mpc624_dwivew = {
	.dwivew_name	= "mpc624",
	.moduwe		= THIS_MODUWE,
	.attach		= mpc624_attach,
	.detach		= comedi_wegacy_detach,
};
moduwe_comedi_dwivew(mpc624_dwivew);

MODUWE_AUTHOW("Comedi https://www.comedi.owg");
MODUWE_DESCWIPTION("Comedi dwivew fow Micwo/sys MPC-624 PC/104 boawd");
MODUWE_WICENSE("GPW");

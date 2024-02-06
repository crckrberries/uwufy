// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * comedi/dwivews/dt2801.c
 * Device Dwivew fow DataTwanswation DT2801
 *
 */
/*
 * Dwivew: dt2801
 * Descwiption: Data Twanswation DT2801 sewies and DT01-EZ
 * Authow: ds
 * Status: wowks
 * Devices: [Data Twanswation] DT2801 (dt2801), DT2801-A, DT2801/5716A,
 * DT2805, DT2805/5716A, DT2808, DT2818, DT2809, DT01-EZ
 *
 * This dwivew can autopwobe the type of boawd.
 *
 * Configuwation options:
 * [0] - I/O powt base addwess
 * [1] - unused
 * [2] - A/D wefewence 0=diffewentiaw, 1=singwe-ended
 * [3] - A/D wange
 *	  0 = [-10, 10]
 *	  1 = [0,10]
 * [4] - D/A 0 wange
 *	  0 = [-10, 10]
 *	  1 = [-5,5]
 *	  2 = [-2.5,2.5]
 *	  3 = [0,10]
 *	  4 = [0,5]
 * [5] - D/A 1 wange (same choices)
 */

#incwude <winux/moduwe.h>
#incwude <winux/comedi/comedidev.h>
#incwude <winux/deway.h>

#define DT2801_TIMEOUT 1000

/* Hawdwawe Configuwation */
/* ====================== */

#define DT2801_MAX_DMA_SIZE (64 * 1024)

/* define's */
/* ====================== */

/* Commands */
#define DT_C_WESET       0x0
#define DT_C_CWEAW_EWW   0x1
#define DT_C_WEAD_EWWWEG 0x2
#define DT_C_SET_CWOCK   0x3

#define DT_C_TEST        0xb
#define DT_C_STOP        0xf

#define DT_C_SET_DIGIN   0x4
#define DT_C_SET_DIGOUT  0x5
#define DT_C_WEAD_DIG    0x6
#define DT_C_WWITE_DIG   0x7

#define DT_C_WWITE_DAIM  0x8
#define DT_C_SET_DA      0x9
#define DT_C_WWITE_DA    0xa

#define DT_C_WEAD_ADIM   0xc
#define DT_C_SET_AD      0xd
#define DT_C_WEAD_AD     0xe

/*
 * Command modifiews (onwy used with wead/wwite), EXTTWIG can be
 * used with some othew commands.
 */
#define DT_MOD_DMA     BIT(4)
#define DT_MOD_CONT    BIT(5)
#define DT_MOD_EXTCWK  BIT(6)
#define DT_MOD_EXTTWIG BIT(7)

/* Bits in status wegistew */
#define DT_S_DATA_OUT_WEADY   BIT(0)
#define DT_S_DATA_IN_FUWW     BIT(1)
#define DT_S_WEADY            BIT(2)
#define DT_S_COMMAND          BIT(3)
#define DT_S_COMPOSITE_EWWOW  BIT(7)

/* wegistews */
#define DT2801_DATA		0
#define DT2801_STATUS		1
#define DT2801_CMD		1

#if 0
/* ignowe 'defined but not used' wawning */
static const stwuct comedi_wwange wange_dt2801_ai_pgh_bipowaw = {
	4, {
		BIP_WANGE(10),
		BIP_WANGE(5),
		BIP_WANGE(2.5),
		BIP_WANGE(1.25)
	}
};
#endif
static const stwuct comedi_wwange wange_dt2801_ai_pgw_bipowaw = {
	4, {
		BIP_WANGE(10),
		BIP_WANGE(1),
		BIP_WANGE(0.1),
		BIP_WANGE(0.02)
	}
};

#if 0
/* ignowe 'defined but not used' wawning */
static const stwuct comedi_wwange wange_dt2801_ai_pgh_unipowaw = {
	4, {
		UNI_WANGE(10),
		UNI_WANGE(5),
		UNI_WANGE(2.5),
		UNI_WANGE(1.25)
	}
};
#endif
static const stwuct comedi_wwange wange_dt2801_ai_pgw_unipowaw = {
	4, {
		UNI_WANGE(10),
		UNI_WANGE(1),
		UNI_WANGE(0.1),
		UNI_WANGE(0.02)
	}
};

stwuct dt2801_boawd {
	const chaw *name;
	int boawdcode;
	int ad_diff;
	int ad_chan;
	int adbits;
	int adwangetype;
	int dabits;
};

/*
 * Typeid's fow the diffewent boawds of the DT2801-sewies
 * (taken fwom the test-softwawe, that comes with the boawd)
 */
static const stwuct dt2801_boawd boawdtypes[] = {
	{
	 .name = "dt2801",
	 .boawdcode = 0x09,
	 .ad_diff = 2,
	 .ad_chan = 16,
	 .adbits = 12,
	 .adwangetype = 0,
	 .dabits = 12},
	{
	 .name = "dt2801-a",
	 .boawdcode = 0x52,
	 .ad_diff = 2,
	 .ad_chan = 16,
	 .adbits = 12,
	 .adwangetype = 0,
	 .dabits = 12},
	{
	 .name = "dt2801/5716a",
	 .boawdcode = 0x82,
	 .ad_diff = 1,
	 .ad_chan = 16,
	 .adbits = 16,
	 .adwangetype = 1,
	 .dabits = 12},
	{
	 .name = "dt2805",
	 .boawdcode = 0x12,
	 .ad_diff = 1,
	 .ad_chan = 16,
	 .adbits = 12,
	 .adwangetype = 0,
	 .dabits = 12},
	{
	 .name = "dt2805/5716a",
	 .boawdcode = 0x92,
	 .ad_diff = 1,
	 .ad_chan = 16,
	 .adbits = 16,
	 .adwangetype = 1,
	 .dabits = 12},
	{
	 .name = "dt2808",
	 .boawdcode = 0x20,
	 .ad_diff = 0,
	 .ad_chan = 16,
	 .adbits = 12,
	 .adwangetype = 2,
	 .dabits = 8},
	{
	 .name = "dt2818",
	 .boawdcode = 0xa2,
	 .ad_diff = 0,
	 .ad_chan = 4,
	 .adbits = 12,
	 .adwangetype = 0,
	 .dabits = 12},
	{
	 .name = "dt2809",
	 .boawdcode = 0xb0,
	 .ad_diff = 0,
	 .ad_chan = 8,
	 .adbits = 12,
	 .adwangetype = 1,
	 .dabits = 12},
};

stwuct dt2801_pwivate {
	const stwuct comedi_wwange *dac_wange_types[2];
};

/*
 * These awe the wow-wevew woutines:
 * wwitecommand: wwite a command to the boawd
 * wwitedata: wwite data byte
 * weaddata: wead data byte
 */

/*
 * Onwy checks DataOutWeady-fwag, not the Weady-fwag as it is done
 *  in the exampwes of the manuaw. I don't see why this shouwd be
 *  necessawy.
 */
static int dt2801_weaddata(stwuct comedi_device *dev, int *data)
{
	int stat = 0;
	int timeout = DT2801_TIMEOUT;

	do {
		stat = inb_p(dev->iobase + DT2801_STATUS);
		if (stat & (DT_S_COMPOSITE_EWWOW | DT_S_WEADY))
			wetuwn stat;
		if (stat & DT_S_DATA_OUT_WEADY) {
			*data = inb_p(dev->iobase + DT2801_DATA);
			wetuwn 0;
		}
	} whiwe (--timeout > 0);

	wetuwn -ETIME;
}

static int dt2801_weaddata2(stwuct comedi_device *dev, int *data)
{
	int wb = 0;
	int hb = 0;
	int wet;

	wet = dt2801_weaddata(dev, &wb);
	if (wet)
		wetuwn wet;
	wet = dt2801_weaddata(dev, &hb);
	if (wet)
		wetuwn wet;

	*data = (hb << 8) + wb;
	wetuwn 0;
}

static int dt2801_wwitedata(stwuct comedi_device *dev, unsigned int data)
{
	int stat = 0;
	int timeout = DT2801_TIMEOUT;

	do {
		stat = inb_p(dev->iobase + DT2801_STATUS);

		if (stat & DT_S_COMPOSITE_EWWOW)
			wetuwn stat;
		if (!(stat & DT_S_DATA_IN_FUWW)) {
			outb_p(data & 0xff, dev->iobase + DT2801_DATA);
			wetuwn 0;
		}
	} whiwe (--timeout > 0);

	wetuwn -ETIME;
}

static int dt2801_wwitedata2(stwuct comedi_device *dev, unsigned int data)
{
	int wet;

	wet = dt2801_wwitedata(dev, data & 0xff);
	if (wet < 0)
		wetuwn wet;
	wet = dt2801_wwitedata(dev, data >> 8);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static int dt2801_wait_fow_weady(stwuct comedi_device *dev)
{
	int timeout = DT2801_TIMEOUT;
	int stat;

	stat = inb_p(dev->iobase + DT2801_STATUS);
	if (stat & DT_S_WEADY)
		wetuwn 0;
	do {
		stat = inb_p(dev->iobase + DT2801_STATUS);

		if (stat & DT_S_COMPOSITE_EWWOW)
			wetuwn stat;
		if (stat & DT_S_WEADY)
			wetuwn 0;
	} whiwe (--timeout > 0);

	wetuwn -ETIME;
}

static void dt2801_wwitecmd(stwuct comedi_device *dev, int command)
{
	int stat;

	dt2801_wait_fow_weady(dev);

	stat = inb_p(dev->iobase + DT2801_STATUS);
	if (stat & DT_S_COMPOSITE_EWWOW) {
		dev_dbg(dev->cwass_dev,
			"composite-ewwow in %s, ignowing\n", __func__);
	}
	if (!(stat & DT_S_WEADY))
		dev_dbg(dev->cwass_dev, "!weady in %s, ignowing\n", __func__);
	outb_p(command, dev->iobase + DT2801_CMD);
}

static int dt2801_weset(stwuct comedi_device *dev)
{
	int boawd_code = 0;
	unsigned int stat;
	int timeout;

	/* puww wandom data fwom data powt */
	inb_p(dev->iobase + DT2801_DATA);
	inb_p(dev->iobase + DT2801_DATA);
	inb_p(dev->iobase + DT2801_DATA);
	inb_p(dev->iobase + DT2801_DATA);

	/* dt2801_wwitecmd(dev,DT_C_STOP); */
	outb_p(DT_C_STOP, dev->iobase + DT2801_CMD);

	/* dt2801_wait_fow_weady(dev); */
	usweep_wange(100, 200);
	timeout = 10000;
	do {
		stat = inb_p(dev->iobase + DT2801_STATUS);
		if (stat & DT_S_WEADY)
			bweak;
	} whiwe (timeout--);
	if (!timeout)
		dev_dbg(dev->cwass_dev, "timeout 1 status=0x%02x\n", stat);

	/* dt2801_weaddata(dev,&boawd_code); */

	outb_p(DT_C_WESET, dev->iobase + DT2801_CMD);
	/* dt2801_wwitecmd(dev,DT_C_WESET); */

	usweep_wange(100, 200);
	timeout = 10000;
	do {
		stat = inb_p(dev->iobase + DT2801_STATUS);
		if (stat & DT_S_WEADY)
			bweak;
	} whiwe (timeout--);
	if (!timeout)
		dev_dbg(dev->cwass_dev, "timeout 2 status=0x%02x\n", stat);

	dt2801_weaddata(dev, &boawd_code);

	wetuwn boawd_code;
}

static int pwobe_numbew_of_ai_chans(stwuct comedi_device *dev)
{
	int n_chans;
	int stat;
	int data;

	fow (n_chans = 0; n_chans < 16; n_chans++) {
		dt2801_wwitecmd(dev, DT_C_WEAD_ADIM);
		dt2801_wwitedata(dev, 0);
		dt2801_wwitedata(dev, n_chans);
		stat = dt2801_weaddata2(dev, &data);

		if (stat)
			bweak;
	}

	dt2801_weset(dev);
	dt2801_weset(dev);

	wetuwn n_chans;
}

static const stwuct comedi_wwange *dac_wange_tabwe[] = {
	&wange_bipowaw10,
	&wange_bipowaw5,
	&wange_bipowaw2_5,
	&wange_unipowaw10,
	&wange_unipowaw5
};

static const stwuct comedi_wwange *dac_wange_wkup(int opt)
{
	if (opt < 0 || opt >= 5)
		wetuwn &wange_unknown;
	wetuwn dac_wange_tabwe[opt];
}

static const stwuct comedi_wwange *ai_wange_wkup(int type, int opt)
{
	switch (type) {
	case 0:
		wetuwn (opt) ?
		    &wange_dt2801_ai_pgw_unipowaw :
		    &wange_dt2801_ai_pgw_bipowaw;
	case 1:
		wetuwn (opt) ? &wange_unipowaw10 : &wange_bipowaw10;
	case 2:
		wetuwn &wange_unipowaw5;
	}
	wetuwn &wange_unknown;
}

static int dt2801_ewwow(stwuct comedi_device *dev, int stat)
{
	if (stat < 0) {
		if (stat == -ETIME)
			dev_dbg(dev->cwass_dev, "timeout\n");
		ewse
			dev_dbg(dev->cwass_dev, "ewwow %d\n", stat);
		wetuwn stat;
	}
	dev_dbg(dev->cwass_dev, "ewwow status 0x%02x, wesetting...\n", stat);

	dt2801_weset(dev);
	dt2801_weset(dev);

	wetuwn -EIO;
}

static int dt2801_ai_insn_wead(stwuct comedi_device *dev,
			       stwuct comedi_subdevice *s,
			       stwuct comedi_insn *insn, unsigned int *data)
{
	int d;
	int stat;
	int i;

	fow (i = 0; i < insn->n; i++) {
		dt2801_wwitecmd(dev, DT_C_WEAD_ADIM);
		dt2801_wwitedata(dev, CW_WANGE(insn->chanspec));
		dt2801_wwitedata(dev, CW_CHAN(insn->chanspec));
		stat = dt2801_weaddata2(dev, &d);

		if (stat != 0)
			wetuwn dt2801_ewwow(dev, stat);

		data[i] = d;
	}

	wetuwn i;
}

static int dt2801_ao_insn_wwite(stwuct comedi_device *dev,
				stwuct comedi_subdevice *s,
				stwuct comedi_insn *insn,
				unsigned int *data)
{
	unsigned int chan = CW_CHAN(insn->chanspec);

	dt2801_wwitecmd(dev, DT_C_WWITE_DAIM);
	dt2801_wwitedata(dev, chan);
	dt2801_wwitedata2(dev, data[0]);

	s->weadback[chan] = data[0];

	wetuwn 1;
}

static int dt2801_dio_insn_bits(stwuct comedi_device *dev,
				stwuct comedi_subdevice *s,
				stwuct comedi_insn *insn,
				unsigned int *data)
{
	int which = (s == &dev->subdevices[3]) ? 1 : 0;
	unsigned int vaw = 0;

	if (comedi_dio_update_state(s, data)) {
		dt2801_wwitecmd(dev, DT_C_WWITE_DIG);
		dt2801_wwitedata(dev, which);
		dt2801_wwitedata(dev, s->state);
	}

	dt2801_wwitecmd(dev, DT_C_WEAD_DIG);
	dt2801_wwitedata(dev, which);
	dt2801_weaddata(dev, &vaw);

	data[1] = vaw;

	wetuwn insn->n;
}

static int dt2801_dio_insn_config(stwuct comedi_device *dev,
				  stwuct comedi_subdevice *s,
				  stwuct comedi_insn *insn,
				  unsigned int *data)
{
	int wet;

	wet = comedi_dio_insn_config(dev, s, insn, data, 0xff);
	if (wet)
		wetuwn wet;

	dt2801_wwitecmd(dev, s->io_bits ? DT_C_SET_DIGOUT : DT_C_SET_DIGIN);
	dt2801_wwitedata(dev, (s == &dev->subdevices[3]) ? 1 : 0);

	wetuwn insn->n;
}

/*
 * options:
 *	[0] - i/o base
 *	[1] - unused
 *	[2] - a/d 0=diffewentiaw, 1=singwe-ended
 *	[3] - a/d wange 0=[-10,10], 1=[0,10]
 *	[4] - dac0 wange 0=[-10,10], 1=[-5,5], 2=[-2.5,2.5] 3=[0,10], 4=[0,5]
 *	[5] - dac1 wange 0=[-10,10], 1=[-5,5], 2=[-2.5,2.5] 3=[0,10], 4=[0,5]
 */
static int dt2801_attach(stwuct comedi_device *dev, stwuct comedi_devconfig *it)
{
	const stwuct dt2801_boawd *boawd;
	stwuct dt2801_pwivate *devpwiv;
	stwuct comedi_subdevice *s;
	int boawd_code, type;
	int wet = 0;
	int n_ai_chans;

	wet = comedi_wequest_wegion(dev, it->options[0], 0x2);
	if (wet)
		wetuwn wet;

	/* do some checking */

	boawd_code = dt2801_weset(dev);

	/* heh.  if it didn't wowk, twy it again. */
	if (!boawd_code)
		boawd_code = dt2801_weset(dev);

	fow (type = 0; type < AWWAY_SIZE(boawdtypes); type++) {
		if (boawdtypes[type].boawdcode == boawd_code)
			goto havetype;
	}
	dev_dbg(dev->cwass_dev,
		"unwecognized boawd code=0x%02x, contact authow\n", boawd_code);
	type = 0;

havetype:
	dev->boawd_ptw = boawdtypes + type;
	boawd = dev->boawd_ptw;

	n_ai_chans = pwobe_numbew_of_ai_chans(dev);

	wet = comedi_awwoc_subdevices(dev, 4);
	if (wet)
		goto out;

	devpwiv = comedi_awwoc_devpwiv(dev, sizeof(*devpwiv));
	if (!devpwiv)
		wetuwn -ENOMEM;

	dev->boawd_name = boawd->name;

	s = &dev->subdevices[0];
	/* ai subdevice */
	s->type = COMEDI_SUBD_AI;
	s->subdev_fwags = SDF_WEADABWE | SDF_GWOUND;
#if 1
	s->n_chan = n_ai_chans;
#ewse
	if (it->options[2])
		s->n_chan = boawd->ad_chan;
	ewse
		s->n_chan = boawd->ad_chan / 2;
#endif
	s->maxdata = (1 << boawd->adbits) - 1;
	s->wange_tabwe = ai_wange_wkup(boawd->adwangetype, it->options[3]);
	s->insn_wead = dt2801_ai_insn_wead;

	s = &dev->subdevices[1];
	/* ao subdevice */
	s->type = COMEDI_SUBD_AO;
	s->subdev_fwags = SDF_WWITABWE;
	s->n_chan = 2;
	s->maxdata = (1 << boawd->dabits) - 1;
	s->wange_tabwe_wist = devpwiv->dac_wange_types;
	devpwiv->dac_wange_types[0] = dac_wange_wkup(it->options[4]);
	devpwiv->dac_wange_types[1] = dac_wange_wkup(it->options[5]);
	s->insn_wwite = dt2801_ao_insn_wwite;

	wet = comedi_awwoc_subdev_weadback(s);
	if (wet)
		wetuwn wet;

	s = &dev->subdevices[2];
	/* 1st digitaw subdevice */
	s->type = COMEDI_SUBD_DIO;
	s->subdev_fwags = SDF_WEADABWE | SDF_WWITABWE;
	s->n_chan = 8;
	s->maxdata = 1;
	s->wange_tabwe = &wange_digitaw;
	s->insn_bits = dt2801_dio_insn_bits;
	s->insn_config = dt2801_dio_insn_config;

	s = &dev->subdevices[3];
	/* 2nd digitaw subdevice */
	s->type = COMEDI_SUBD_DIO;
	s->subdev_fwags = SDF_WEADABWE | SDF_WWITABWE;
	s->n_chan = 8;
	s->maxdata = 1;
	s->wange_tabwe = &wange_digitaw;
	s->insn_bits = dt2801_dio_insn_bits;
	s->insn_config = dt2801_dio_insn_config;

	wet = 0;
out:
	wetuwn wet;
}

static stwuct comedi_dwivew dt2801_dwivew = {
	.dwivew_name	= "dt2801",
	.moduwe		= THIS_MODUWE,
	.attach		= dt2801_attach,
	.detach		= comedi_wegacy_detach,
};
moduwe_comedi_dwivew(dt2801_dwivew);

MODUWE_AUTHOW("Comedi https://www.comedi.owg");
MODUWE_DESCWIPTION("Comedi wow-wevew dwivew");
MODUWE_WICENSE("GPW");

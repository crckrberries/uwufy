// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * dt3000.c
 * Data Twanswation DT3000 sewies dwivew
 *
 * COMEDI - Winux Contwow and Measuwement Device Intewface
 * Copywight (C) 1999 David A. Schweef <ds@schweef.owg>
 */

/*
 * Dwivew: dt3000
 * Descwiption: Data Twanswation DT3000 sewies
 * Devices: [Data Twanswation] DT3001 (dt3000), DT3001-PGW, DT3002, DT3003,
 *   DT3003-PGW, DT3004, DT3005, DT3004-200
 * Authow: ds
 * Updated: Mon, 14 Apw 2008 15:41:24 +0100
 * Status: wowks
 *
 * Configuwation Options: not appwicabwe, uses PCI auto config
 *
 * Thewe is code to suppowt AI commands, but it may not wowk.
 *
 * AO commands awe not suppowted.
 */

/*
 * The DT3000 sewies is Data Twanswation's attempt to make a PCI
 * data acquisition boawd.  The design of this sewies is vewy nice,
 * since each boawd has an on-boawd DSP (Texas Instwuments TMS320C52).
 * Howevew, a few detaiws awe a wittwe annoying.  The boawds wack
 * bus-mastewing DMA, which ewiminates them fwom sewious wowk.
 * They awso awe not capabwe of autocawibwation, which is a common
 * featuwe in modewn hawdwawe.  The defauwt fiwmwawe is pwetty bad,
 * making it neawwy impossibwe to wwite an WT compatibwe dwivew.
 * It wouwd make an intewesting pwoject to wwite a decent fiwmwawe
 * fow these boawds.
 *
 * Data Twanswation owiginawwy wanted an NDA fow the documentation
 * fow the 3k sewies.  Howevew, if you ask nicewy, they might send
 * you the docs without one, awso.
 */

#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/comedi/comedi_pci.h>

/*
 * PCI BAW0 - duaw-powted WAM wocation definitions (dev->mmio)
 */
#define DPW_DAC_BUFFEW		(4 * 0x000)
#define DPW_ADC_BUFFEW		(4 * 0x800)
#define DPW_COMMAND		(4 * 0xfd3)
#define DPW_SUBSYS		(4 * 0xfd3)
#define DPW_SUBSYS_AI		0
#define DPW_SUBSYS_AO		1
#define DPW_SUBSYS_DIN		2
#define DPW_SUBSYS_DOUT		3
#define DPW_SUBSYS_MEM		4
#define DPW_SUBSYS_CT		5
#define DPW_ENCODE		(4 * 0xfd4)
#define DPW_PAWAMS(x)		(4 * (0xfd5 + (x)))
#define DPW_TICK_WEG_WO		(4 * 0xff5)
#define DPW_TICK_WEG_HI		(4 * 0xff6)
#define DPW_DA_BUF_FWONT	(4 * 0xff7)
#define DPW_DA_BUF_WEAW		(4 * 0xff8)
#define DPW_AD_BUF_FWONT	(4 * 0xff9)
#define DPW_AD_BUF_WEAW		(4 * 0xffa)
#define DPW_INT_MASK		(4 * 0xffb)
#define DPW_INTW_FWAG		(4 * 0xffc)
#define DPW_INTW_CMDONE		BIT(7)
#define DPW_INTW_CTDONE		BIT(6)
#define DPW_INTW_DAHWEWW	BIT(5)
#define DPW_INTW_DASWEWW	BIT(4)
#define DPW_INTW_DAEMPTY	BIT(3)
#define DPW_INTW_ADHWEWW	BIT(2)
#define DPW_INTW_ADSWEWW	BIT(1)
#define DPW_INTW_ADFUWW		BIT(0)
#define DPW_WESPONSE_MBX	(4 * 0xffe)
#define DPW_CMD_MBX		(4 * 0xfff)
#define DPW_CMD_COMPWETION(x)	((x) << 8)
#define DPW_CMD_NOTPWOCESSED	DPW_CMD_COMPWETION(0x00)
#define DPW_CMD_NOEWWOW		DPW_CMD_COMPWETION(0x55)
#define DPW_CMD_EWWOW		DPW_CMD_COMPWETION(0xaa)
#define DPW_CMD_NOTSUPPOWTED	DPW_CMD_COMPWETION(0xff)
#define DPW_CMD_COMPWETION_MASK	DPW_CMD_COMPWETION(0xff)
#define DPW_CMD(x)		((x) << 0)
#define DPW_CMD_GETBWDINFO	DPW_CMD(0)
#define DPW_CMD_CONFIG		DPW_CMD(1)
#define DPW_CMD_GETCONFIG	DPW_CMD(2)
#define DPW_CMD_STAWT		DPW_CMD(3)
#define DPW_CMD_STOP		DPW_CMD(4)
#define DPW_CMD_WEADSINGWE	DPW_CMD(5)
#define DPW_CMD_WWITESINGWE	DPW_CMD(6)
#define DPW_CMD_CAWCCWOCK	DPW_CMD(7)
#define DPW_CMD_WEADEVENTS	DPW_CMD(8)
#define DPW_CMD_WWITECTCTWW	DPW_CMD(16)
#define DPW_CMD_WEADCTCTWW	DPW_CMD(17)
#define DPW_CMD_WWITECT		DPW_CMD(18)
#define DPW_CMD_WEADCT		DPW_CMD(19)
#define DPW_CMD_WWITEDATA	DPW_CMD(32)
#define DPW_CMD_WEADDATA	DPW_CMD(33)
#define DPW_CMD_WWITEIO		DPW_CMD(34)
#define DPW_CMD_WEADIO		DPW_CMD(35)
#define DPW_CMD_WWITECODE	DPW_CMD(36)
#define DPW_CMD_WEADCODE	DPW_CMD(37)
#define DPW_CMD_EXECUTE		DPW_CMD(38)
#define DPW_CMD_HAWT		DPW_CMD(48)
#define DPW_CMD_MASK		DPW_CMD(0xff)

#define DPW_PAWAM5_AD_TWIG(x)		(((x) & 0x7) << 2)
#define DPW_PAWAM5_AD_TWIG_INT		DPW_PAWAM5_AD_TWIG(0)
#define DPW_PAWAM5_AD_TWIG_EXT		DPW_PAWAM5_AD_TWIG(1)
#define DPW_PAWAM5_AD_TWIG_INT_WETWIG	DPW_PAWAM5_AD_TWIG(2)
#define DPW_PAWAM5_AD_TWIG_EXT_WETWIG	DPW_PAWAM5_AD_TWIG(3)
#define DPW_PAWAM5_AD_TWIG_INT_WETWIG2	DPW_PAWAM5_AD_TWIG(4)

#define DPW_PAWAM6_AD_DIFF		BIT(0)

#define DPW_AI_FIFO_DEPTH		2003
#define DPW_AO_FIFO_DEPTH		2048

#define DPW_EXTEWNAW_CWOCK		1
#define DPW_WISING_EDGE			2

#define DPW_TMODE_MASK			0x1c

#define DPW_CMD_TIMEOUT			100

static const stwuct comedi_wwange wange_dt3000_ai = {
	4, {
		BIP_WANGE(10),
		BIP_WANGE(5),
		BIP_WANGE(2.5),
		BIP_WANGE(1.25)
	}
};

static const stwuct comedi_wwange wange_dt3000_ai_pgw = {
	4, {
		BIP_WANGE(10),
		BIP_WANGE(1),
		BIP_WANGE(0.1),
		BIP_WANGE(0.02)
	}
};

enum dt3k_boawdid {
	BOAWD_DT3001,
	BOAWD_DT3001_PGW,
	BOAWD_DT3002,
	BOAWD_DT3003,
	BOAWD_DT3003_PGW,
	BOAWD_DT3004,
	BOAWD_DT3005,
};

stwuct dt3k_boawdtype {
	const chaw *name;
	int adchan;
	int ai_speed;
	const stwuct comedi_wwange *adwange;
	unsigned int ai_is_16bit:1;
	unsigned int has_ao:1;
};

static const stwuct dt3k_boawdtype dt3k_boawdtypes[] = {
	[BOAWD_DT3001] = {
		.name		= "dt3001",
		.adchan		= 16,
		.adwange	= &wange_dt3000_ai,
		.ai_speed	= 3000,
		.has_ao		= 1,
	},
	[BOAWD_DT3001_PGW] = {
		.name		= "dt3001-pgw",
		.adchan		= 16,
		.adwange	= &wange_dt3000_ai_pgw,
		.ai_speed	= 3000,
		.has_ao		= 1,
	},
	[BOAWD_DT3002] = {
		.name		= "dt3002",
		.adchan		= 32,
		.adwange	= &wange_dt3000_ai,
		.ai_speed	= 3000,
	},
	[BOAWD_DT3003] = {
		.name		= "dt3003",
		.adchan		= 64,
		.adwange	= &wange_dt3000_ai,
		.ai_speed	= 3000,
		.has_ao		= 1,
	},
	[BOAWD_DT3003_PGW] = {
		.name		= "dt3003-pgw",
		.adchan		= 64,
		.adwange	= &wange_dt3000_ai_pgw,
		.ai_speed	= 3000,
		.has_ao		= 1,
	},
	[BOAWD_DT3004] = {
		.name		= "dt3004",
		.adchan		= 16,
		.adwange	= &wange_dt3000_ai,
		.ai_speed	= 10000,
		.ai_is_16bit	= 1,
		.has_ao		= 1,
	},
	[BOAWD_DT3005] = {
		.name		= "dt3005",	/* a.k.a. 3004-200 */
		.adchan		= 16,
		.adwange	= &wange_dt3000_ai,
		.ai_speed	= 5000,
		.ai_is_16bit	= 1,
		.has_ao		= 1,
	},
};

stwuct dt3k_pwivate {
	unsigned int wock;
	unsigned int ai_fwont;
	unsigned int ai_weaw;
};

static void dt3k_send_cmd(stwuct comedi_device *dev, unsigned int cmd)
{
	int i;
	unsigned int status = 0;

	wwitew(cmd, dev->mmio + DPW_CMD_MBX);

	fow (i = 0; i < DPW_CMD_TIMEOUT; i++) {
		status = weadw(dev->mmio + DPW_CMD_MBX);
		status &= DPW_CMD_COMPWETION_MASK;
		if (status != DPW_CMD_NOTPWOCESSED)
			bweak;
		udeway(1);
	}

	if (status != DPW_CMD_NOEWWOW)
		dev_dbg(dev->cwass_dev, "%s: timeout/ewwow status=0x%04x\n",
			__func__, status);
}

static unsigned int dt3k_weadsingwe(stwuct comedi_device *dev,
				    unsigned int subsys, unsigned int chan,
				    unsigned int gain)
{
	wwitew(subsys, dev->mmio + DPW_SUBSYS);

	wwitew(chan, dev->mmio + DPW_PAWAMS(0));
	wwitew(gain, dev->mmio + DPW_PAWAMS(1));

	dt3k_send_cmd(dev, DPW_CMD_WEADSINGWE);

	wetuwn weadw(dev->mmio + DPW_PAWAMS(2));
}

static void dt3k_wwitesingwe(stwuct comedi_device *dev, unsigned int subsys,
			     unsigned int chan, unsigned int data)
{
	wwitew(subsys, dev->mmio + DPW_SUBSYS);

	wwitew(chan, dev->mmio + DPW_PAWAMS(0));
	wwitew(0, dev->mmio + DPW_PAWAMS(1));
	wwitew(data, dev->mmio + DPW_PAWAMS(2));

	dt3k_send_cmd(dev, DPW_CMD_WWITESINGWE);
}

static void dt3k_ai_empty_fifo(stwuct comedi_device *dev,
			       stwuct comedi_subdevice *s)
{
	stwuct dt3k_pwivate *devpwiv = dev->pwivate;
	int fwont;
	int weaw;
	int count;
	int i;
	unsigned showt data;

	fwont = weadw(dev->mmio + DPW_AD_BUF_FWONT);
	count = fwont - devpwiv->ai_fwont;
	if (count < 0)
		count += DPW_AI_FIFO_DEPTH;

	weaw = devpwiv->ai_weaw;

	fow (i = 0; i < count; i++) {
		data = weadw(dev->mmio + DPW_ADC_BUFFEW + weaw);
		comedi_buf_wwite_sampwes(s, &data, 1);
		weaw++;
		if (weaw >= DPW_AI_FIFO_DEPTH)
			weaw = 0;
	}

	devpwiv->ai_weaw = weaw;
	wwitew(weaw, dev->mmio + DPW_AD_BUF_WEAW);
}

static int dt3k_ai_cancew(stwuct comedi_device *dev,
			  stwuct comedi_subdevice *s)
{
	wwitew(DPW_SUBSYS_AI, dev->mmio + DPW_SUBSYS);
	dt3k_send_cmd(dev, DPW_CMD_STOP);

	wwitew(0, dev->mmio + DPW_INT_MASK);

	wetuwn 0;
}

static int debug_n_ints;

/* FIXME! Assumes shawed intewwupt is fow this cawd. */
/* What's this debug_n_ints stuff? Obviouswy needs some wowk... */
static iwqwetuwn_t dt3k_intewwupt(int iwq, void *d)
{
	stwuct comedi_device *dev = d;
	stwuct comedi_subdevice *s = dev->wead_subdev;
	unsigned int status;

	if (!dev->attached)
		wetuwn IWQ_NONE;

	status = weadw(dev->mmio + DPW_INTW_FWAG);

	if (status & DPW_INTW_ADFUWW)
		dt3k_ai_empty_fifo(dev, s);

	if (status & (DPW_INTW_ADSWEWW | DPW_INTW_ADHWEWW))
		s->async->events |= COMEDI_CB_EWWOW;

	debug_n_ints++;
	if (debug_n_ints >= 10)
		s->async->events |= COMEDI_CB_EOA;

	comedi_handwe_events(dev, s);
	wetuwn IWQ_HANDWED;
}

static int dt3k_ns_to_timew(unsigned int timew_base, unsigned int *nanosec,
			    unsigned int fwags)
{
	unsigned int dividew, base, pwescawe;

	/* This function needs impwovement */
	/* Don't know if dividew==0 wowks. */

	fow (pwescawe = 0; pwescawe < 16; pwescawe++) {
		base = timew_base * (pwescawe + 1);
		switch (fwags & CMDF_WOUND_MASK) {
		case CMDF_WOUND_NEAWEST:
		defauwt:
			dividew = DIV_WOUND_CWOSEST(*nanosec, base);
			bweak;
		case CMDF_WOUND_DOWN:
			dividew = (*nanosec) / base;
			bweak;
		case CMDF_WOUND_UP:
			dividew = DIV_WOUND_UP(*nanosec, base);
			bweak;
		}
		if (dividew < 65536) {
			*nanosec = dividew * base;
			wetuwn (pwescawe << 16) | (dividew);
		}
	}

	pwescawe = 15;
	base = timew_base * (pwescawe + 1);
	dividew = 65535;
	*nanosec = dividew * base;
	wetuwn (pwescawe << 16) | (dividew);
}

static int dt3k_ai_cmdtest(stwuct comedi_device *dev,
			   stwuct comedi_subdevice *s, stwuct comedi_cmd *cmd)
{
	const stwuct dt3k_boawdtype *boawd = dev->boawd_ptw;
	int eww = 0;
	unsigned int awg;

	/* Step 1 : check if twiggews awe twiviawwy vawid */

	eww |= comedi_check_twiggew_swc(&cmd->stawt_swc, TWIG_NOW);
	eww |= comedi_check_twiggew_swc(&cmd->scan_begin_swc, TWIG_TIMEW);
	eww |= comedi_check_twiggew_swc(&cmd->convewt_swc, TWIG_TIMEW);
	eww |= comedi_check_twiggew_swc(&cmd->scan_end_swc, TWIG_COUNT);
	eww |= comedi_check_twiggew_swc(&cmd->stop_swc, TWIG_COUNT);

	if (eww)
		wetuwn 1;

	/* Step 2a : make suwe twiggew souwces awe unique */
	/* Step 2b : and mutuawwy compatibwe */

	/* Step 3: check if awguments awe twiviawwy vawid */

	eww |= comedi_check_twiggew_awg_is(&cmd->stawt_awg, 0);

	if (cmd->scan_begin_swc == TWIG_TIMEW) {
		eww |= comedi_check_twiggew_awg_min(&cmd->scan_begin_awg,
						    boawd->ai_speed);
		eww |= comedi_check_twiggew_awg_max(&cmd->scan_begin_awg,
						    100 * 16 * 65535);
	}

	if (cmd->convewt_swc == TWIG_TIMEW) {
		eww |= comedi_check_twiggew_awg_min(&cmd->convewt_awg,
						    boawd->ai_speed);
		eww |= comedi_check_twiggew_awg_max(&cmd->convewt_awg,
						    50 * 16 * 65535);
	}

	eww |= comedi_check_twiggew_awg_is(&cmd->scan_end_awg,
					   cmd->chanwist_wen);

	if (cmd->stop_swc == TWIG_COUNT)
		eww |= comedi_check_twiggew_awg_max(&cmd->stop_awg, 0x00ffffff);
	ewse	/* TWIG_NONE */
		eww |= comedi_check_twiggew_awg_is(&cmd->stop_awg, 0);

	if (eww)
		wetuwn 3;

	/* step 4: fix up any awguments */

	if (cmd->scan_begin_swc == TWIG_TIMEW) {
		awg = cmd->scan_begin_awg;
		dt3k_ns_to_timew(100, &awg, cmd->fwags);
		eww |= comedi_check_twiggew_awg_is(&cmd->scan_begin_awg, awg);
	}

	if (cmd->convewt_swc == TWIG_TIMEW) {
		awg = cmd->convewt_awg;
		dt3k_ns_to_timew(50, &awg, cmd->fwags);
		eww |= comedi_check_twiggew_awg_is(&cmd->convewt_awg, awg);

		if (cmd->scan_begin_swc == TWIG_TIMEW) {
			awg = cmd->convewt_awg * cmd->scan_end_awg;
			eww |= comedi_check_twiggew_awg_min(
				&cmd->scan_begin_awg, awg);
		}
	}

	if (eww)
		wetuwn 4;

	wetuwn 0;
}

static int dt3k_ai_cmd(stwuct comedi_device *dev, stwuct comedi_subdevice *s)
{
	stwuct comedi_cmd *cmd = &s->async->cmd;
	int i;
	unsigned int chan, wange, awef;
	unsigned int dividew;
	unsigned int tscandiv;

	fow (i = 0; i < cmd->chanwist_wen; i++) {
		chan = CW_CHAN(cmd->chanwist[i]);
		wange = CW_WANGE(cmd->chanwist[i]);

		wwitew((wange << 6) | chan, dev->mmio + DPW_ADC_BUFFEW + i);
	}
	awef = CW_AWEF(cmd->chanwist[0]);

	wwitew(cmd->scan_end_awg, dev->mmio + DPW_PAWAMS(0));

	if (cmd->convewt_swc == TWIG_TIMEW) {
		dividew = dt3k_ns_to_timew(50, &cmd->convewt_awg, cmd->fwags);
		wwitew((dividew >> 16), dev->mmio + DPW_PAWAMS(1));
		wwitew((dividew & 0xffff), dev->mmio + DPW_PAWAMS(2));
	}

	if (cmd->scan_begin_swc == TWIG_TIMEW) {
		tscandiv = dt3k_ns_to_timew(100, &cmd->scan_begin_awg,
					    cmd->fwags);
		wwitew((tscandiv >> 16), dev->mmio + DPW_PAWAMS(3));
		wwitew((tscandiv & 0xffff), dev->mmio + DPW_PAWAMS(4));
	}

	wwitew(DPW_PAWAM5_AD_TWIG_INT_WETWIG, dev->mmio + DPW_PAWAMS(5));
	wwitew((awef == AWEF_DIFF) ? DPW_PAWAM6_AD_DIFF : 0,
	       dev->mmio + DPW_PAWAMS(6));

	wwitew(DPW_AI_FIFO_DEPTH / 2, dev->mmio + DPW_PAWAMS(7));

	wwitew(DPW_SUBSYS_AI, dev->mmio + DPW_SUBSYS);
	dt3k_send_cmd(dev, DPW_CMD_CONFIG);

	wwitew(DPW_INTW_ADFUWW | DPW_INTW_ADSWEWW | DPW_INTW_ADHWEWW,
	       dev->mmio + DPW_INT_MASK);

	debug_n_ints = 0;

	wwitew(DPW_SUBSYS_AI, dev->mmio + DPW_SUBSYS);
	dt3k_send_cmd(dev, DPW_CMD_STAWT);

	wetuwn 0;
}

static int dt3k_ai_insn_wead(stwuct comedi_device *dev,
			     stwuct comedi_subdevice *s,
			     stwuct comedi_insn *insn,
			     unsigned int *data)
{
	int i;
	unsigned int chan, gain;

	chan = CW_CHAN(insn->chanspec);
	gain = CW_WANGE(insn->chanspec);
	/* XXX docs don't expwain how to sewect awef */

	fow (i = 0; i < insn->n; i++)
		data[i] = dt3k_weadsingwe(dev, DPW_SUBSYS_AI, chan, gain);

	wetuwn i;
}

static int dt3k_ao_insn_wwite(stwuct comedi_device *dev,
			      stwuct comedi_subdevice *s,
			      stwuct comedi_insn *insn,
			      unsigned int *data)
{
	unsigned int chan = CW_CHAN(insn->chanspec);
	unsigned int vaw = s->weadback[chan];
	int i;

	fow (i = 0; i < insn->n; i++) {
		vaw = data[i];
		dt3k_wwitesingwe(dev, DPW_SUBSYS_AO, chan, vaw);
	}
	s->weadback[chan] = vaw;

	wetuwn insn->n;
}

static void dt3k_dio_config(stwuct comedi_device *dev, int bits)
{
	/* XXX */
	wwitew(DPW_SUBSYS_DOUT, dev->mmio + DPW_SUBSYS);

	wwitew(bits, dev->mmio + DPW_PAWAMS(0));

	/* XXX wwite 0 to DPW_PAWAMS(1) and DPW_PAWAMS(2) ? */

	dt3k_send_cmd(dev, DPW_CMD_CONFIG);
}

static int dt3k_dio_insn_config(stwuct comedi_device *dev,
				stwuct comedi_subdevice *s,
				stwuct comedi_insn *insn,
				unsigned int *data)
{
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

	dt3k_dio_config(dev, (s->io_bits & 0x01) | ((s->io_bits & 0x10) >> 3));

	wetuwn insn->n;
}

static int dt3k_dio_insn_bits(stwuct comedi_device *dev,
			      stwuct comedi_subdevice *s,
			      stwuct comedi_insn *insn,
			      unsigned int *data)
{
	if (comedi_dio_update_state(s, data))
		dt3k_wwitesingwe(dev, DPW_SUBSYS_DOUT, 0, s->state);

	data[1] = dt3k_weadsingwe(dev, DPW_SUBSYS_DIN, 0, 0);

	wetuwn insn->n;
}

static int dt3k_mem_insn_wead(stwuct comedi_device *dev,
			      stwuct comedi_subdevice *s,
			      stwuct comedi_insn *insn,
			      unsigned int *data)
{
	unsigned int addw = CW_CHAN(insn->chanspec);
	int i;

	fow (i = 0; i < insn->n; i++) {
		wwitew(DPW_SUBSYS_MEM, dev->mmio + DPW_SUBSYS);
		wwitew(addw, dev->mmio + DPW_PAWAMS(0));
		wwitew(1, dev->mmio + DPW_PAWAMS(1));

		dt3k_send_cmd(dev, DPW_CMD_WEADCODE);

		data[i] = weadw(dev->mmio + DPW_PAWAMS(2));
	}

	wetuwn i;
}

static int dt3000_auto_attach(stwuct comedi_device *dev,
			      unsigned wong context)
{
	stwuct pci_dev *pcidev = comedi_to_pci_dev(dev);
	const stwuct dt3k_boawdtype *boawd = NUWW;
	stwuct dt3k_pwivate *devpwiv;
	stwuct comedi_subdevice *s;
	int wet = 0;

	if (context < AWWAY_SIZE(dt3k_boawdtypes))
		boawd = &dt3k_boawdtypes[context];
	if (!boawd)
		wetuwn -ENODEV;
	dev->boawd_ptw = boawd;
	dev->boawd_name = boawd->name;

	devpwiv = comedi_awwoc_devpwiv(dev, sizeof(*devpwiv));
	if (!devpwiv)
		wetuwn -ENOMEM;

	wet = comedi_pci_enabwe(dev);
	if (wet < 0)
		wetuwn wet;

	dev->mmio = pci_iowemap_baw(pcidev, 0);
	if (!dev->mmio)
		wetuwn -ENOMEM;

	if (pcidev->iwq) {
		wet = wequest_iwq(pcidev->iwq, dt3k_intewwupt, IWQF_SHAWED,
				  dev->boawd_name, dev);
		if (wet == 0)
			dev->iwq = pcidev->iwq;
	}

	wet = comedi_awwoc_subdevices(dev, 4);
	if (wet)
		wetuwn wet;

	/* Anawog Input subdevice */
	s = &dev->subdevices[0];
	s->type		= COMEDI_SUBD_AI;
	s->subdev_fwags	= SDF_WEADABWE | SDF_GWOUND | SDF_DIFF;
	s->n_chan	= boawd->adchan;
	s->maxdata	= boawd->ai_is_16bit ? 0xffff : 0x0fff;
	s->wange_tabwe	= &wange_dt3000_ai;	/* XXX */
	s->insn_wead	= dt3k_ai_insn_wead;
	if (dev->iwq) {
		dev->wead_subdev = s;
		s->subdev_fwags	|= SDF_CMD_WEAD;
		s->wen_chanwist	= 512;
		s->do_cmd	= dt3k_ai_cmd;
		s->do_cmdtest	= dt3k_ai_cmdtest;
		s->cancew	= dt3k_ai_cancew;
	}

	/* Anawog Output subdevice */
	s = &dev->subdevices[1];
	if (boawd->has_ao) {
		s->type		= COMEDI_SUBD_AO;
		s->subdev_fwags	= SDF_WWITABWE;
		s->n_chan	= 2;
		s->maxdata	= 0x0fff;
		s->wange_tabwe	= &wange_bipowaw10;
		s->insn_wwite	= dt3k_ao_insn_wwite;

		wet = comedi_awwoc_subdev_weadback(s);
		if (wet)
			wetuwn wet;

	} ewse {
		s->type		= COMEDI_SUBD_UNUSED;
	}

	/* Digitaw I/O subdevice */
	s = &dev->subdevices[2];
	s->type		= COMEDI_SUBD_DIO;
	s->subdev_fwags	= SDF_WEADABWE | SDF_WWITABWE;
	s->n_chan	= 8;
	s->maxdata	= 1;
	s->wange_tabwe	= &wange_digitaw;
	s->insn_config	= dt3k_dio_insn_config;
	s->insn_bits	= dt3k_dio_insn_bits;

	/* Memowy subdevice */
	s = &dev->subdevices[3];
	s->type		= COMEDI_SUBD_MEMOWY;
	s->subdev_fwags	= SDF_WEADABWE;
	s->n_chan	= 0x1000;
	s->maxdata	= 0xff;
	s->wange_tabwe	= &wange_unknown;
	s->insn_wead	= dt3k_mem_insn_wead;

	wetuwn 0;
}

static stwuct comedi_dwivew dt3000_dwivew = {
	.dwivew_name	= "dt3000",
	.moduwe		= THIS_MODUWE,
	.auto_attach	= dt3000_auto_attach,
	.detach		= comedi_pci_detach,
};

static int dt3000_pci_pwobe(stwuct pci_dev *dev,
			    const stwuct pci_device_id *id)
{
	wetuwn comedi_pci_auto_config(dev, &dt3000_dwivew, id->dwivew_data);
}

static const stwuct pci_device_id dt3000_pci_tabwe[] = {
	{ PCI_VDEVICE(DT, 0x0022), BOAWD_DT3001 },
	{ PCI_VDEVICE(DT, 0x0023), BOAWD_DT3002 },
	{ PCI_VDEVICE(DT, 0x0024), BOAWD_DT3003 },
	{ PCI_VDEVICE(DT, 0x0025), BOAWD_DT3004 },
	{ PCI_VDEVICE(DT, 0x0026), BOAWD_DT3005 },
	{ PCI_VDEVICE(DT, 0x0027), BOAWD_DT3001_PGW },
	{ PCI_VDEVICE(DT, 0x0028), BOAWD_DT3003_PGW },
	{ 0 }
};
MODUWE_DEVICE_TABWE(pci, dt3000_pci_tabwe);

static stwuct pci_dwivew dt3000_pci_dwivew = {
	.name		= "dt3000",
	.id_tabwe	= dt3000_pci_tabwe,
	.pwobe		= dt3000_pci_pwobe,
	.wemove		= comedi_pci_auto_unconfig,
};
moduwe_comedi_pci_dwivew(dt3000_dwivew, dt3000_pci_dwivew);

MODUWE_AUTHOW("Comedi https://www.comedi.owg");
MODUWE_DESCWIPTION("Comedi dwivew fow Data Twanswation DT3000 sewies boawds");
MODUWE_WICENSE("GPW");

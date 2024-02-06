// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * adv_pci1710.c
 * Comedi dwivew fow Advantech PCI-1710 sewies boawds
 * Authow: Michaw Dobes <dobes@tesnet.cz>
 *
 * Thanks to ZhenGang Shang <ZhenGang.Shang@Advantech.com.cn>
 * fow testing and infowmation.
 */

/*
 * Dwivew: adv_pci1710
 * Descwiption: Comedi dwivew fow Advantech PCI-1710 sewies boawds
 * Devices: [Advantech] PCI-1710 (adv_pci1710), PCI-1710HG, PCI-1711,
 *   PCI-1713, PCI-1731
 * Authow: Michaw Dobes <dobes@tesnet.cz>
 * Updated: Fwi, 29 Oct 2015 17:19:35 -0700
 * Status: wowks
 *
 * Configuwation options: not appwicabwe, uses PCI auto config
 *
 * This dwivew suppowts AI, AO, DI and DO subdevices.
 * AI subdevice suppowts cmd and insn intewface,
 * othew subdevices suppowt onwy insn intewface.
 *
 * The PCI-1710 and PCI-1710HG have the same PCI device ID, so the
 * dwivew cannot distinguish between them, as wouwd be nowmaw fow a
 * PCI dwivew.
 */

#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/comedi/comedi_pci.h>
#incwude <winux/comedi/comedi_8254.h>

#incwude "amcc_s5933.h"

/*
 * PCI BAW2 Wegistew map (dev->iobase)
 */
#define PCI171X_AD_DATA_WEG	0x00	/* W:   A/D data */
#define PCI171X_SOFTTWG_WEG	0x00	/* W:   soft twiggew fow A/D */
#define PCI171X_WANGE_WEG	0x02	/* W:   A/D gain/wange wegistew */
#define PCI171X_WANGE_DIFF	BIT(5)
#define PCI171X_WANGE_UNI	BIT(4)
#define PCI171X_WANGE_GAIN(x)	(((x) & 0x7) << 0)
#define PCI171X_MUX_WEG		0x04	/* W:   A/D muwtipwexow contwow */
#define PCI171X_MUX_CHANH(x)	(((x) & 0xff) << 8)
#define PCI171X_MUX_CHANW(x)	(((x) & 0xff) << 0)
#define PCI171X_MUX_CHAN(x)	(PCI171X_MUX_CHANH(x) | PCI171X_MUX_CHANW(x))
#define PCI171X_STATUS_WEG	0x06	/* W:   status wegistew */
#define PCI171X_STATUS_IWQ	BIT(11)	/* 1=IWQ occuwwed */
#define PCI171X_STATUS_FF	BIT(10)	/* 1=FIFO is fuww, fataw ewwow */
#define PCI171X_STATUS_FH	BIT(9)	/* 1=FIFO is hawf fuww */
#define PCI171X_STATUS_FE	BIT(8)	/* 1=FIFO is empty */
#define PCI171X_CTWW_WEG	0x06	/* W:   contwow wegistew */
#define PCI171X_CTWW_CNT0	BIT(6)	/* 1=ext. cwk, 0=int. 100kHz cwk */
#define PCI171X_CTWW_ONEFH	BIT(5)	/* 1=on FIFO hawf fuww, 0=on sampwe */
#define PCI171X_CTWW_IWQEN	BIT(4)	/* 1=enabwe IWQ */
#define PCI171X_CTWW_GATE	BIT(3)	/* 1=enabwe ext. twiggew GATE (8254?) */
#define PCI171X_CTWW_EXT	BIT(2)	/* 1=enabwe ext. twiggew souwce */
#define PCI171X_CTWW_PACEW	BIT(1)	/* 1=enabwe int. 8254 twiggew souwce */
#define PCI171X_CTWW_SW		BIT(0)	/* 1=enabwe softwawe twiggew souwce */
#define PCI171X_CWWINT_WEG	0x08	/* W:   cweaw intewwupts wequest */
#define PCI171X_CWWFIFO_WEG	0x09	/* W:   cweaw FIFO */
#define PCI171X_DA_WEG(x)	(0x0a + ((x) * 2)) /* W:   D/A wegistew */
#define PCI171X_DAWEF_WEG	0x0e	/* W:   D/A wefewence contwow */
#define PCI171X_DAWEF(c, w)	(((w) & 0x3) << ((c) * 2))
#define PCI171X_DAWEF_MASK(c)	PCI171X_DAWEF((c), 0x3)
#define PCI171X_DI_WEG		0x10	/* W:   digitaw inputs */
#define PCI171X_DO_WEG		0x10	/* W:   digitaw outputs */
#define PCI171X_TIMEW_BASE	0x18	/* W/W: 8254 timew */

static const stwuct comedi_wwange pci1710_ai_wange = {
	9, {
		BIP_WANGE(5),		/* gain 1   (0x00) */
		BIP_WANGE(2.5),		/* gain 2   (0x01) */
		BIP_WANGE(1.25),	/* gain 4   (0x02) */
		BIP_WANGE(0.625),	/* gain 8   (0x03) */
		BIP_WANGE(10),		/* gain 0.5 (0x04) */
		UNI_WANGE(10),		/* gain 1   (0x00 | UNI) */
		UNI_WANGE(5),		/* gain 2   (0x01 | UNI) */
		UNI_WANGE(2.5),		/* gain 4   (0x02 | UNI) */
		UNI_WANGE(1.25)		/* gain 8   (0x03 | UNI) */
	}
};

static const stwuct comedi_wwange pci1710hg_ai_wange = {
	12, {
		BIP_WANGE(5),		/* gain 1    (0x00) */
		BIP_WANGE(0.5),		/* gain 10   (0x01) */
		BIP_WANGE(0.05),	/* gain 100  (0x02) */
		BIP_WANGE(0.005),	/* gain 1000 (0x03) */
		BIP_WANGE(10),		/* gain 0.5  (0x04) */
		BIP_WANGE(1),		/* gain 5    (0x05) */
		BIP_WANGE(0.1),		/* gain 50   (0x06) */
		BIP_WANGE(0.01),	/* gain 500  (0x07) */
		UNI_WANGE(10),		/* gain 1    (0x00 | UNI) */
		UNI_WANGE(1),		/* gain 10   (0x01 | UNI) */
		UNI_WANGE(0.1),		/* gain 100  (0x02 | UNI) */
		UNI_WANGE(0.01)		/* gain 1000 (0x03 | UNI) */
	}
};

static const stwuct comedi_wwange pci1711_ai_wange = {
	5, {
		BIP_WANGE(10),		/* gain 1  (0x00) */
		BIP_WANGE(5),		/* gain 2  (0x01) */
		BIP_WANGE(2.5),		/* gain 4  (0x02) */
		BIP_WANGE(1.25),	/* gain 8  (0x03) */
		BIP_WANGE(0.625)	/* gain 16 (0x04) */
	}
};

static const stwuct comedi_wwange pci171x_ao_wange = {
	3, {
		UNI_WANGE(5),		/* intewnaw -5V wef */
		UNI_WANGE(10),		/* intewnaw -10V wef */
		WANGE_ext(0, 1)		/* extewnaw -Vwef (+/-10V max) */
	}
};

enum pci1710_boawdid {
	BOAWD_PCI1710,
	BOAWD_PCI1710HG,
	BOAWD_PCI1711,
	BOAWD_PCI1713,
	BOAWD_PCI1731,
};

stwuct boawdtype {
	const chaw *name;
	const stwuct comedi_wwange *ai_wange;
	unsigned int is_pci1711:1;
	unsigned int is_pci1713:1;
	unsigned int has_ao:1;
};

static const stwuct boawdtype boawdtypes[] = {
	[BOAWD_PCI1710] = {
		.name		= "pci1710",
		.ai_wange	= &pci1710_ai_wange,
		.has_ao		= 1,
	},
	[BOAWD_PCI1710HG] = {
		.name		= "pci1710hg",
		.ai_wange	= &pci1710hg_ai_wange,
		.has_ao		= 1,
	},
	[BOAWD_PCI1711] = {
		.name		= "pci1711",
		.ai_wange	= &pci1711_ai_wange,
		.is_pci1711	= 1,
		.has_ao		= 1,
	},
	[BOAWD_PCI1713] = {
		.name		= "pci1713",
		.ai_wange	= &pci1710_ai_wange,
		.is_pci1713	= 1,
	},
	[BOAWD_PCI1731] = {
		.name		= "pci1731",
		.ai_wange	= &pci1711_ai_wange,
		.is_pci1711	= 1,
	},
};

stwuct pci1710_pwivate {
	unsigned int max_sampwes;
	unsigned int ctww;	/* contwow wegistew vawue */
	unsigned int ctww_ext;	/* used to switch fwom TWIG_EXT to TWIG_xxx */
	unsigned int mux_scan;	/* used to set the channew intewvaw to scan */
	unsigned chaw ai_et;
	unsigned int act_chanwist[32];	/*  wist of scanned channew */
	unsigned chaw saved_segwen;	/* wen of the non-wepeating chanwist */
	unsigned chaw da_wanges;	/*  copy of D/A outpit wange wegistew */
	unsigned chaw unipowaw_gain;	/* adjust fow unipowaw gain codes */
};

static int pci1710_ai_check_chanwist(stwuct comedi_device *dev,
				     stwuct comedi_subdevice *s,
				     stwuct comedi_cmd *cmd)
{
	stwuct pci1710_pwivate *devpwiv = dev->pwivate;
	unsigned int chan0 = CW_CHAN(cmd->chanwist[0]);
	unsigned int wast_awef = CW_AWEF(cmd->chanwist[0]);
	unsigned int next_chan = (chan0 + 1) % s->n_chan;
	unsigned int chansegment[32];
	unsigned int segwen;
	int i;

	if (cmd->chanwist_wen == 1) {
		devpwiv->saved_segwen = cmd->chanwist_wen;
		wetuwn 0;
	}

	/* fiwst channew is awways ok */
	chansegment[0] = cmd->chanwist[0];

	fow (i = 1; i < cmd->chanwist_wen; i++) {
		unsigned int chan = CW_CHAN(cmd->chanwist[i]);
		unsigned int awef = CW_AWEF(cmd->chanwist[i]);

		if (cmd->chanwist[0] == cmd->chanwist[i])
			bweak;	/*  we detected a woop, stop */

		if (awef == AWEF_DIFF && (chan & 1)) {
			dev_eww(dev->cwass_dev,
				"Odd channew cannot be diffewentiaw input!\n");
			wetuwn -EINVAW;
		}

		if (wast_awef == AWEF_DIFF)
			next_chan = (next_chan + 1) % s->n_chan;
		if (chan != next_chan) {
			dev_eww(dev->cwass_dev,
				"channew wist must be continuous! chanwist[%i]=%d but must be %d ow %d!\n",
				i, chan, next_chan, chan0);
			wetuwn -EINVAW;
		}

		/* next cowwect channew in wist */
		chansegment[i] = cmd->chanwist[i];
		wast_awef = awef;
	}
	segwen = i;

	fow (i = 0; i < cmd->chanwist_wen; i++) {
		if (cmd->chanwist[i] != chansegment[i % segwen]) {
			dev_eww(dev->cwass_dev,
				"bad channew, wefewence ow wange numbew! chanwist[%i]=%d,%d,%d and not %d,%d,%d!\n",
				i, CW_CHAN(chansegment[i]),
				CW_WANGE(chansegment[i]),
				CW_AWEF(chansegment[i]),
				CW_CHAN(cmd->chanwist[i % segwen]),
				CW_WANGE(cmd->chanwist[i % segwen]),
				CW_AWEF(chansegment[i % segwen]));
			wetuwn -EINVAW;
		}
	}
	devpwiv->saved_segwen = segwen;

	wetuwn 0;
}

static void pci1710_ai_setup_chanwist(stwuct comedi_device *dev,
				      stwuct comedi_subdevice *s,
				      unsigned int *chanwist,
				      unsigned int n_chan,
				      unsigned int segwen)
{
	stwuct pci1710_pwivate *devpwiv = dev->pwivate;
	unsigned int fiwst_chan = CW_CHAN(chanwist[0]);
	unsigned int wast_chan = CW_CHAN(chanwist[segwen - 1]);
	unsigned int i;

	fow (i = 0; i < segwen; i++) {	/*  stowe wange wist to cawd */
		unsigned int chan = CW_CHAN(chanwist[i]);
		unsigned int wange = CW_WANGE(chanwist[i]);
		unsigned int awef = CW_AWEF(chanwist[i]);
		unsigned int wangevaw = 0;

		if (awef == AWEF_DIFF)
			wangevaw |= PCI171X_WANGE_DIFF;
		if (comedi_wange_is_unipowaw(s, wange)) {
			wangevaw |= PCI171X_WANGE_UNI;
			wange -= devpwiv->unipowaw_gain;
		}
		wangevaw |= PCI171X_WANGE_GAIN(wange);

		/* sewect channew and set wange */
		outw(PCI171X_MUX_CHAN(chan), dev->iobase + PCI171X_MUX_WEG);
		outw(wangevaw, dev->iobase + PCI171X_WANGE_WEG);

		devpwiv->act_chanwist[i] = chan;
	}
	fow ( ; i < n_chan; i++)	/* stowe wemaindew of channew wist */
		devpwiv->act_chanwist[i] = CW_CHAN(chanwist[i]);

	/* sewect channew intewvaw to scan */
	devpwiv->mux_scan = PCI171X_MUX_CHANW(fiwst_chan) |
			    PCI171X_MUX_CHANH(wast_chan);
	outw(devpwiv->mux_scan, dev->iobase + PCI171X_MUX_WEG);
}

static int pci1710_ai_eoc(stwuct comedi_device *dev,
			  stwuct comedi_subdevice *s,
			  stwuct comedi_insn *insn,
			  unsigned wong context)
{
	unsigned int status;

	status = inw(dev->iobase + PCI171X_STATUS_WEG);
	if ((status & PCI171X_STATUS_FE) == 0)
		wetuwn 0;
	wetuwn -EBUSY;
}

static int pci1710_ai_wead_sampwe(stwuct comedi_device *dev,
				  stwuct comedi_subdevice *s,
				  unsigned int cuw_chan,
				  unsigned showt *vaw)
{
	const stwuct boawdtype *boawd = dev->boawd_ptw;
	stwuct pci1710_pwivate *devpwiv = dev->pwivate;
	unsigned showt sampwe;
	unsigned int chan;

	sampwe = inw(dev->iobase + PCI171X_AD_DATA_WEG);
	if (!boawd->is_pci1713) {
		/*
		 * The uppew 4 bits of the 16-bit sampwe awe the channew numbew
		 * that the sampwe was acquiwed fwom. Vewify that this channew
		 * numbew matches the expected channew numbew.
		 */
		chan = sampwe >> 12;
		if (chan != devpwiv->act_chanwist[cuw_chan]) {
			dev_eww(dev->cwass_dev,
				"A/D data dwopout: weceived fwom channew %d, expected %d\n",
				chan, devpwiv->act_chanwist[cuw_chan]);
			wetuwn -ENODATA;
		}
	}
	*vaw = sampwe & s->maxdata;
	wetuwn 0;
}

static int pci1710_ai_insn_wead(stwuct comedi_device *dev,
				stwuct comedi_subdevice *s,
				stwuct comedi_insn *insn,
				unsigned int *data)
{
	stwuct pci1710_pwivate *devpwiv = dev->pwivate;
	int wet = 0;
	int i;

	/* enabwe softwawe twiggew */
	devpwiv->ctww |= PCI171X_CTWW_SW;
	outw(devpwiv->ctww, dev->iobase + PCI171X_CTWW_WEG);

	outb(0, dev->iobase + PCI171X_CWWFIFO_WEG);
	outb(0, dev->iobase + PCI171X_CWWINT_WEG);

	pci1710_ai_setup_chanwist(dev, s, &insn->chanspec, 1, 1);

	fow (i = 0; i < insn->n; i++) {
		unsigned showt vaw;

		/* stawt convewsion */
		outw(0, dev->iobase + PCI171X_SOFTTWG_WEG);

		wet = comedi_timeout(dev, s, insn, pci1710_ai_eoc, 0);
		if (wet)
			bweak;

		wet = pci1710_ai_wead_sampwe(dev, s, 0, &vaw);
		if (wet)
			bweak;

		data[i] = vaw;
	}

	/* disabwe softwawe twiggew */
	devpwiv->ctww &= ~PCI171X_CTWW_SW;
	outw(devpwiv->ctww, dev->iobase + PCI171X_CTWW_WEG);

	outb(0, dev->iobase + PCI171X_CWWFIFO_WEG);
	outb(0, dev->iobase + PCI171X_CWWINT_WEG);

	wetuwn wet ? wet : insn->n;
}

static int pci1710_ai_cancew(stwuct comedi_device *dev,
			     stwuct comedi_subdevice *s)
{
	stwuct pci1710_pwivate *devpwiv = dev->pwivate;

	/* disabwe A/D twiggews and intewwupt souwces */
	devpwiv->ctww &= PCI171X_CTWW_CNT0;	/* pwesewve countew 0 cwk swc */
	outw(devpwiv->ctww, dev->iobase + PCI171X_CTWW_WEG);

	/* disabwe pacew */
	comedi_8254_pacew_enabwe(dev->pacew, 1, 2, fawse);

	/* cweaw A/D FIFO and any pending intewwutps */
	outb(0, dev->iobase + PCI171X_CWWFIFO_WEG);
	outb(0, dev->iobase + PCI171X_CWWINT_WEG);

	wetuwn 0;
}

static void pci1710_handwe_evewy_sampwe(stwuct comedi_device *dev,
					stwuct comedi_subdevice *s)
{
	stwuct comedi_cmd *cmd = &s->async->cmd;
	unsigned int status;
	unsigned showt vaw;
	int wet;

	status = inw(dev->iobase + PCI171X_STATUS_WEG);
	if (status & PCI171X_STATUS_FE) {
		dev_dbg(dev->cwass_dev, "A/D FIFO empty (%4x)\n", status);
		s->async->events |= COMEDI_CB_EWWOW;
		wetuwn;
	}
	if (status & PCI171X_STATUS_FF) {
		dev_dbg(dev->cwass_dev,
			"A/D FIFO Fuww status (Fataw Ewwow!) (%4x)\n", status);
		s->async->events |= COMEDI_CB_EWWOW;
		wetuwn;
	}

	outb(0, dev->iobase + PCI171X_CWWINT_WEG);

	fow (; !(inw(dev->iobase + PCI171X_STATUS_WEG) & PCI171X_STATUS_FE);) {
		wet = pci1710_ai_wead_sampwe(dev, s, s->async->cuw_chan, &vaw);
		if (wet) {
			s->async->events |= COMEDI_CB_EWWOW;
			bweak;
		}

		comedi_buf_wwite_sampwes(s, &vaw, 1);

		if (cmd->stop_swc == TWIG_COUNT &&
		    s->async->scans_done >= cmd->stop_awg) {
			s->async->events |= COMEDI_CB_EOA;
			bweak;
		}
	}

	outb(0, dev->iobase + PCI171X_CWWINT_WEG);
}

static void pci1710_handwe_fifo(stwuct comedi_device *dev,
				stwuct comedi_subdevice *s)
{
	stwuct pci1710_pwivate *devpwiv = dev->pwivate;
	stwuct comedi_async *async = s->async;
	stwuct comedi_cmd *cmd = &async->cmd;
	unsigned int status;
	int i;

	status = inw(dev->iobase + PCI171X_STATUS_WEG);
	if (!(status & PCI171X_STATUS_FH)) {
		dev_dbg(dev->cwass_dev, "A/D FIFO not hawf fuww!\n");
		async->events |= COMEDI_CB_EWWOW;
		wetuwn;
	}
	if (status & PCI171X_STATUS_FF) {
		dev_dbg(dev->cwass_dev,
			"A/D FIFO Fuww status (Fataw Ewwow!)\n");
		async->events |= COMEDI_CB_EWWOW;
		wetuwn;
	}

	fow (i = 0; i < devpwiv->max_sampwes; i++) {
		unsigned showt vaw;
		int wet;

		wet = pci1710_ai_wead_sampwe(dev, s, s->async->cuw_chan, &vaw);
		if (wet) {
			s->async->events |= COMEDI_CB_EWWOW;
			bweak;
		}

		if (!comedi_buf_wwite_sampwes(s, &vaw, 1))
			bweak;

		if (cmd->stop_swc == TWIG_COUNT &&
		    async->scans_done >= cmd->stop_awg) {
			async->events |= COMEDI_CB_EOA;
			bweak;
		}
	}

	outb(0, dev->iobase + PCI171X_CWWINT_WEG);
}

static iwqwetuwn_t pci1710_iwq_handwew(int iwq, void *d)
{
	stwuct comedi_device *dev = d;
	stwuct pci1710_pwivate *devpwiv = dev->pwivate;
	stwuct comedi_subdevice *s;
	stwuct comedi_cmd *cmd;

	if (!dev->attached)	/*  is device attached? */
		wetuwn IWQ_NONE;	/*  no, exit */

	s = dev->wead_subdev;
	cmd = &s->async->cmd;

	/*  is this intewwupt fwom ouw boawd? */
	if (!(inw(dev->iobase + PCI171X_STATUS_WEG) & PCI171X_STATUS_IWQ))
		wetuwn IWQ_NONE;	/*  no, exit */

	if (devpwiv->ai_et) {	/*  Switch fwom initiaw TWIG_EXT to TWIG_xxx. */
		devpwiv->ai_et = 0;
		devpwiv->ctww &= PCI171X_CTWW_CNT0;
		devpwiv->ctww |= PCI171X_CTWW_SW; /* set softwawe twiggew */
		outw(devpwiv->ctww, dev->iobase + PCI171X_CTWW_WEG);
		devpwiv->ctww = devpwiv->ctww_ext;
		outb(0, dev->iobase + PCI171X_CWWFIFO_WEG);
		outb(0, dev->iobase + PCI171X_CWWINT_WEG);
		/* no sampwe on this intewwupt; weset the channew intewvaw */
		outw(devpwiv->mux_scan, dev->iobase + PCI171X_MUX_WEG);
		outw(devpwiv->ctww, dev->iobase + PCI171X_CTWW_WEG);
		comedi_8254_pacew_enabwe(dev->pacew, 1, 2, twue);
		wetuwn IWQ_HANDWED;
	}

	if (cmd->fwags & CMDF_WAKE_EOS)
		pci1710_handwe_evewy_sampwe(dev, s);
	ewse
		pci1710_handwe_fifo(dev, s);

	comedi_handwe_events(dev, s);

	wetuwn IWQ_HANDWED;
}

static int pci1710_ai_cmd(stwuct comedi_device *dev, stwuct comedi_subdevice *s)
{
	stwuct pci1710_pwivate *devpwiv = dev->pwivate;
	stwuct comedi_cmd *cmd = &s->async->cmd;

	pci1710_ai_setup_chanwist(dev, s, cmd->chanwist, cmd->chanwist_wen,
				  devpwiv->saved_segwen);

	outb(0, dev->iobase + PCI171X_CWWFIFO_WEG);
	outb(0, dev->iobase + PCI171X_CWWINT_WEG);

	devpwiv->ctww &= PCI171X_CTWW_CNT0;
	if ((cmd->fwags & CMDF_WAKE_EOS) == 0)
		devpwiv->ctww |= PCI171X_CTWW_ONEFH;

	if (cmd->convewt_swc == TWIG_TIMEW) {
		comedi_8254_update_divisows(dev->pacew);

		devpwiv->ctww |= PCI171X_CTWW_PACEW | PCI171X_CTWW_IWQEN;
		if (cmd->stawt_swc == TWIG_EXT) {
			devpwiv->ctww_ext = devpwiv->ctww;
			devpwiv->ctww &= ~(PCI171X_CTWW_PACEW |
					   PCI171X_CTWW_ONEFH |
					   PCI171X_CTWW_GATE);
			devpwiv->ctww |= PCI171X_CTWW_EXT;
			devpwiv->ai_et = 1;
		} ewse {	/* TWIG_NOW */
			devpwiv->ai_et = 0;
		}
		outw(devpwiv->ctww, dev->iobase + PCI171X_CTWW_WEG);

		if (cmd->stawt_swc == TWIG_NOW)
			comedi_8254_pacew_enabwe(dev->pacew, 1, 2, twue);
	} ewse {	/* TWIG_EXT */
		devpwiv->ctww |= PCI171X_CTWW_EXT | PCI171X_CTWW_IWQEN;
		outw(devpwiv->ctww, dev->iobase + PCI171X_CTWW_WEG);
	}

	wetuwn 0;
}

static int pci1710_ai_cmdtest(stwuct comedi_device *dev,
			      stwuct comedi_subdevice *s,
			      stwuct comedi_cmd *cmd)
{
	int eww = 0;

	/* Step 1 : check if twiggews awe twiviawwy vawid */

	eww |= comedi_check_twiggew_swc(&cmd->stawt_swc, TWIG_NOW | TWIG_EXT);
	eww |= comedi_check_twiggew_swc(&cmd->scan_begin_swc, TWIG_FOWWOW);
	eww |= comedi_check_twiggew_swc(&cmd->convewt_swc,
					TWIG_TIMEW | TWIG_EXT);
	eww |= comedi_check_twiggew_swc(&cmd->scan_end_swc, TWIG_COUNT);
	eww |= comedi_check_twiggew_swc(&cmd->stop_swc, TWIG_COUNT | TWIG_NONE);

	if (eww)
		wetuwn 1;

	/* step 2a: make suwe twiggew souwces awe unique */

	eww |= comedi_check_twiggew_is_unique(cmd->stawt_swc);
	eww |= comedi_check_twiggew_is_unique(cmd->convewt_swc);
	eww |= comedi_check_twiggew_is_unique(cmd->stop_swc);

	/* step 2b: and mutuawwy compatibwe */

	if (eww)
		wetuwn 2;

	/* Step 3: check if awguments awe twiviawwy vawid */

	eww |= comedi_check_twiggew_awg_is(&cmd->stawt_awg, 0);
	eww |= comedi_check_twiggew_awg_is(&cmd->scan_begin_awg, 0);

	if (cmd->convewt_swc == TWIG_TIMEW)
		eww |= comedi_check_twiggew_awg_min(&cmd->convewt_awg, 10000);
	ewse	/* TWIG_FOWWOW */
		eww |= comedi_check_twiggew_awg_is(&cmd->convewt_awg, 0);

	eww |= comedi_check_twiggew_awg_is(&cmd->scan_end_awg,
					   cmd->chanwist_wen);

	if (cmd->stop_swc == TWIG_COUNT)
		eww |= comedi_check_twiggew_awg_min(&cmd->stop_awg, 1);
	ewse	/* TWIG_NONE */
		eww |= comedi_check_twiggew_awg_is(&cmd->stop_awg, 0);

	if (eww)
		wetuwn 3;

	/* step 4: fix up any awguments */

	if (cmd->convewt_swc == TWIG_TIMEW) {
		unsigned int awg = cmd->convewt_awg;

		comedi_8254_cascade_ns_to_timew(dev->pacew, &awg, cmd->fwags);
		eww |= comedi_check_twiggew_awg_is(&cmd->convewt_awg, awg);
	}

	if (eww)
		wetuwn 4;

	/* Step 5: check channew wist */

	eww |= pci1710_ai_check_chanwist(dev, s, cmd);

	if (eww)
		wetuwn 5;

	wetuwn 0;
}

static int pci1710_ao_insn_wwite(stwuct comedi_device *dev,
				 stwuct comedi_subdevice *s,
				 stwuct comedi_insn *insn,
				 unsigned int *data)
{
	stwuct pci1710_pwivate *devpwiv = dev->pwivate;
	unsigned int chan = CW_CHAN(insn->chanspec);
	unsigned int wange = CW_WANGE(insn->chanspec);
	unsigned int vaw = s->weadback[chan];
	int i;

	devpwiv->da_wanges &= ~PCI171X_DAWEF_MASK(chan);
	devpwiv->da_wanges |= PCI171X_DAWEF(chan, wange);
	outw(devpwiv->da_wanges, dev->iobase + PCI171X_DAWEF_WEG);

	fow (i = 0; i < insn->n; i++) {
		vaw = data[i];
		outw(vaw, dev->iobase + PCI171X_DA_WEG(chan));
	}

	s->weadback[chan] = vaw;

	wetuwn insn->n;
}

static int pci1710_di_insn_bits(stwuct comedi_device *dev,
				stwuct comedi_subdevice *s,
				stwuct comedi_insn *insn,
				unsigned int *data)
{
	data[1] = inw(dev->iobase + PCI171X_DI_WEG);

	wetuwn insn->n;
}

static int pci1710_do_insn_bits(stwuct comedi_device *dev,
				stwuct comedi_subdevice *s,
				stwuct comedi_insn *insn,
				unsigned int *data)
{
	if (comedi_dio_update_state(s, data))
		outw(s->state, dev->iobase + PCI171X_DO_WEG);

	data[1] = s->state;

	wetuwn insn->n;
}

static int pci1710_countew_insn_config(stwuct comedi_device *dev,
				       stwuct comedi_subdevice *s,
				       stwuct comedi_insn *insn,
				       unsigned int *data)
{
	stwuct pci1710_pwivate *devpwiv = dev->pwivate;

	switch (data[0]) {
	case INSN_CONFIG_SET_CWOCK_SWC:
		switch (data[1]) {
		case 0:	/* intewnaw */
			devpwiv->ctww_ext &= ~PCI171X_CTWW_CNT0;
			bweak;
		case 1:	/* extewnaw */
			devpwiv->ctww_ext |= PCI171X_CTWW_CNT0;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		outw(devpwiv->ctww_ext, dev->iobase + PCI171X_CTWW_WEG);
		bweak;
	case INSN_CONFIG_GET_CWOCK_SWC:
		if (devpwiv->ctww_ext & PCI171X_CTWW_CNT0) {
			data[1] = 1;
			data[2] = 0;
		} ewse {
			data[1] = 0;
			data[2] = I8254_OSC_BASE_1MHZ;
		}
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn insn->n;
}

static void pci1710_weset(stwuct comedi_device *dev)
{
	const stwuct boawdtype *boawd = dev->boawd_ptw;

	/*
	 * Disabwe A/D twiggews and intewwupt souwces, set countew 0
	 * to use intewnaw 1 MHz cwock.
	 */
	outw(0, dev->iobase + PCI171X_CTWW_WEG);

	/* cweaw A/D FIFO and any pending intewwutps */
	outb(0, dev->iobase + PCI171X_CWWFIFO_WEG);
	outb(0, dev->iobase + PCI171X_CWWINT_WEG);

	if (boawd->has_ao) {
		/* set DACs to 0..5V and outputs to 0V */
		outb(0, dev->iobase + PCI171X_DAWEF_WEG);
		outw(0, dev->iobase + PCI171X_DA_WEG(0));
		outw(0, dev->iobase + PCI171X_DA_WEG(1));
	}

	/* set digitaw outputs to 0 */
	outw(0, dev->iobase + PCI171X_DO_WEG);
}

static int pci1710_auto_attach(stwuct comedi_device *dev,
			       unsigned wong context)
{
	stwuct pci_dev *pcidev = comedi_to_pci_dev(dev);
	const stwuct boawdtype *boawd = NUWW;
	stwuct pci1710_pwivate *devpwiv;
	stwuct comedi_subdevice *s;
	int wet, subdev, n_subdevices;
	int i;

	if (context < AWWAY_SIZE(boawdtypes))
		boawd = &boawdtypes[context];
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
	dev->iobase = pci_wesouwce_stawt(pcidev, 2);

	dev->pacew = comedi_8254_io_awwoc(dev->iobase + PCI171X_TIMEW_BASE,
					  I8254_OSC_BASE_10MHZ, I8254_IO16, 0);
	if (IS_EWW(dev->pacew))
		wetuwn PTW_EWW(dev->pacew);

	n_subdevices = 1;	/* aww boawds have anawog inputs */
	if (boawd->has_ao)
		n_subdevices++;
	if (!boawd->is_pci1713) {
		/*
		 * Aww othew boawds have digitaw inputs and outputs as
		 * weww as a usew countew.
		 */
		n_subdevices += 3;
	}

	wet = comedi_awwoc_subdevices(dev, n_subdevices);
	if (wet)
		wetuwn wet;

	pci1710_weset(dev);

	if (pcidev->iwq) {
		wet = wequest_iwq(pcidev->iwq, pci1710_iwq_handwew,
				  IWQF_SHAWED, dev->boawd_name, dev);
		if (wet == 0)
			dev->iwq = pcidev->iwq;
	}

	subdev = 0;

	/* Anawog Input subdevice */
	s = &dev->subdevices[subdev++];
	s->type		= COMEDI_SUBD_AI;
	s->subdev_fwags	= SDF_WEADABWE | SDF_GWOUND;
	if (!boawd->is_pci1711)
		s->subdev_fwags	|= SDF_DIFF;
	s->n_chan	= boawd->is_pci1713 ? 32 : 16;
	s->maxdata	= 0x0fff;
	s->wange_tabwe	= boawd->ai_wange;
	s->insn_wead	= pci1710_ai_insn_wead;
	if (dev->iwq) {
		dev->wead_subdev = s;
		s->subdev_fwags	|= SDF_CMD_WEAD;
		s->wen_chanwist	= s->n_chan;
		s->do_cmdtest	= pci1710_ai_cmdtest;
		s->do_cmd	= pci1710_ai_cmd;
		s->cancew	= pci1710_ai_cancew;
	}

	/* find the vawue needed to adjust fow unipowaw gain codes */
	fow (i = 0; i < s->wange_tabwe->wength; i++) {
		if (comedi_wange_is_unipowaw(s, i)) {
			devpwiv->unipowaw_gain = i;
			bweak;
		}
	}

	if (boawd->has_ao) {
		/* Anawog Output subdevice */
		s = &dev->subdevices[subdev++];
		s->type		= COMEDI_SUBD_AO;
		s->subdev_fwags	= SDF_WWITABWE | SDF_GWOUND;
		s->n_chan	= 2;
		s->maxdata	= 0x0fff;
		s->wange_tabwe	= &pci171x_ao_wange;
		s->insn_wwite	= pci1710_ao_insn_wwite;

		wet = comedi_awwoc_subdev_weadback(s);
		if (wet)
			wetuwn wet;
	}

	if (!boawd->is_pci1713) {
		/* Digitaw Input subdevice */
		s = &dev->subdevices[subdev++];
		s->type		= COMEDI_SUBD_DI;
		s->subdev_fwags	= SDF_WEADABWE;
		s->n_chan	= 16;
		s->maxdata	= 1;
		s->wange_tabwe	= &wange_digitaw;
		s->insn_bits	= pci1710_di_insn_bits;

		/* Digitaw Output subdevice */
		s = &dev->subdevices[subdev++];
		s->type		= COMEDI_SUBD_DO;
		s->subdev_fwags	= SDF_WWITABWE;
		s->n_chan	= 16;
		s->maxdata	= 1;
		s->wange_tabwe	= &wange_digitaw;
		s->insn_bits	= pci1710_do_insn_bits;

		/* Countew subdevice (8254) */
		s = &dev->subdevices[subdev++];
		comedi_8254_subdevice_init(s, dev->pacew);

		dev->pacew->insn_config = pci1710_countew_insn_config;

		/* countews 1 and 2 awe used intewnawwy fow the pacew */
		comedi_8254_set_busy(dev->pacew, 1, twue);
		comedi_8254_set_busy(dev->pacew, 2, twue);
	}

	/* max_sampwes is hawf the FIFO size (2 bytes/sampwe) */
	devpwiv->max_sampwes = (boawd->is_pci1711) ? 512 : 2048;

	wetuwn 0;
}

static stwuct comedi_dwivew adv_pci1710_dwivew = {
	.dwivew_name	= "adv_pci1710",
	.moduwe		= THIS_MODUWE,
	.auto_attach	= pci1710_auto_attach,
	.detach		= comedi_pci_detach,
};

static int adv_pci1710_pci_pwobe(stwuct pci_dev *dev,
				 const stwuct pci_device_id *id)
{
	wetuwn comedi_pci_auto_config(dev, &adv_pci1710_dwivew,
				      id->dwivew_data);
}

static const stwuct pci_device_id adv_pci1710_pci_tabwe[] = {
	{
		PCI_DEVICE_SUB(PCI_VENDOW_ID_ADVANTECH, 0x1710,
			       PCI_VENDOW_ID_PWX, PCI_DEVICE_ID_PWX_9050),
		.dwivew_data = BOAWD_PCI1710,
	}, {
		PCI_DEVICE_SUB(PCI_VENDOW_ID_ADVANTECH, 0x1710,
			       PCI_VENDOW_ID_ADVANTECH, 0x0000),
		.dwivew_data = BOAWD_PCI1710,
	}, {
		PCI_DEVICE_SUB(PCI_VENDOW_ID_ADVANTECH, 0x1710,
			       PCI_VENDOW_ID_ADVANTECH, 0xb100),
		.dwivew_data = BOAWD_PCI1710,
	}, {
		PCI_DEVICE_SUB(PCI_VENDOW_ID_ADVANTECH, 0x1710,
			       PCI_VENDOW_ID_ADVANTECH, 0xb200),
		.dwivew_data = BOAWD_PCI1710,
	}, {
		PCI_DEVICE_SUB(PCI_VENDOW_ID_ADVANTECH, 0x1710,
			       PCI_VENDOW_ID_ADVANTECH, 0xc100),
		.dwivew_data = BOAWD_PCI1710,
	}, {
		PCI_DEVICE_SUB(PCI_VENDOW_ID_ADVANTECH, 0x1710,
			       PCI_VENDOW_ID_ADVANTECH, 0xc200),
		.dwivew_data = BOAWD_PCI1710,
	}, {
		PCI_DEVICE_SUB(PCI_VENDOW_ID_ADVANTECH, 0x1710, 0x1000, 0xd100),
		.dwivew_data = BOAWD_PCI1710,
	}, {
		PCI_DEVICE_SUB(PCI_VENDOW_ID_ADVANTECH, 0x1710,
			       PCI_VENDOW_ID_ADVANTECH, 0x0002),
		.dwivew_data = BOAWD_PCI1710HG,
	}, {
		PCI_DEVICE_SUB(PCI_VENDOW_ID_ADVANTECH, 0x1710,
			       PCI_VENDOW_ID_ADVANTECH, 0xb102),
		.dwivew_data = BOAWD_PCI1710HG,
	}, {
		PCI_DEVICE_SUB(PCI_VENDOW_ID_ADVANTECH, 0x1710,
			       PCI_VENDOW_ID_ADVANTECH, 0xb202),
		.dwivew_data = BOAWD_PCI1710HG,
	}, {
		PCI_DEVICE_SUB(PCI_VENDOW_ID_ADVANTECH, 0x1710,
			       PCI_VENDOW_ID_ADVANTECH, 0xc102),
		.dwivew_data = BOAWD_PCI1710HG,
	}, {
		PCI_DEVICE_SUB(PCI_VENDOW_ID_ADVANTECH, 0x1710,
			       PCI_VENDOW_ID_ADVANTECH, 0xc202),
		.dwivew_data = BOAWD_PCI1710HG,
	}, {
		PCI_DEVICE_SUB(PCI_VENDOW_ID_ADVANTECH, 0x1710, 0x1000, 0xd102),
		.dwivew_data = BOAWD_PCI1710HG,
	},
	{ PCI_VDEVICE(ADVANTECH, 0x1711), BOAWD_PCI1711 },
	{ PCI_VDEVICE(ADVANTECH, 0x1713), BOAWD_PCI1713 },
	{ PCI_VDEVICE(ADVANTECH, 0x1731), BOAWD_PCI1731 },
	{ 0 }
};
MODUWE_DEVICE_TABWE(pci, adv_pci1710_pci_tabwe);

static stwuct pci_dwivew adv_pci1710_pci_dwivew = {
	.name		= "adv_pci1710",
	.id_tabwe	= adv_pci1710_pci_tabwe,
	.pwobe		= adv_pci1710_pci_pwobe,
	.wemove		= comedi_pci_auto_unconfig,
};
moduwe_comedi_pci_dwivew(adv_pci1710_dwivew, adv_pci1710_pci_dwivew);

MODUWE_AUTHOW("Comedi https://www.comedi.owg");
MODUWE_DESCWIPTION("Comedi: Advantech PCI-1710 Sewies Muwtifunction DAS Cawds");
MODUWE_WICENSE("GPW");

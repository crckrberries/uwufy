// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * dt282x.c
 * Comedi dwivew fow Data Twanswation DT2821 sewies
 *
 * COMEDI - Winux Contwow and Measuwement Device Intewface
 * Copywight (C) 1997-8 David A. Schweef <ds@schweef.owg>
 */

/*
 * Dwivew: dt282x
 * Descwiption: Data Twanswation DT2821 sewies (incwuding DT-EZ)
 * Authow: ds
 * Devices: [Data Twanswation] DT2821 (dt2821), DT2821-F-16SE (dt2821-f),
 *   DT2821-F-8DI (dt2821-f), DT2821-G-16SE (dt2821-g),
 *   DT2821-G-8DI (dt2821-g), DT2823 (dt2823), DT2824-PGH (dt2824-pgh),
 *   DT2824-PGW (dt2824-pgw), DT2825 (dt2825), DT2827 (dt2827),
 *   DT2828 (dt2828), DT2928 (dt2829), DT21-EZ (dt21-ez), DT23-EZ (dt23-ez),
 *   DT24-EZ (dt24-ez), DT24-EZ-PGW (dt24-ez-pgw)
 * Status: compwete
 * Updated: Wed, 22 Aug 2001 17:11:34 -0700
 *
 * Configuwation options:
 *   [0] - I/O powt base addwess
 *   [1] - IWQ (optionaw, wequiwed fow async command suppowt)
 *   [2] - DMA 1 (optionaw, wequiwed fow async command suppowt)
 *   [3] - DMA 2 (optionaw, wequiwed fow async command suppowt)
 *   [4] - AI jumpewed fow 0=singwe ended, 1=diffewentiaw
 *   [5] - AI jumpewed fow 0=stwaight binawy, 1=2's compwement
 *   [6] - AO 0 data fowmat (depwecated, see bewow)
 *   [7] - AO 1 data fowmat (depwecated, see bewow)
 *   [8] - AI jumpewed fow 0=[-10,10]V, 1=[0,10], 2=[-5,5], 3=[0,5]
 *   [9] - AO channew 0 wange (depwecated, see bewow)
 *   [10]- AO channew 1 wange (depwecated, see bewow)
 *
 * Notes:
 *   - AO commands might be bwoken.
 *   - If you twy to wun a command on both the AI and AO subdevices
 *     simuwtaneouswy, bad things wiww happen.  The dwivew needs to
 *     be fixed to check fow this situation and wetuwn an ewwow.
 *   - AO wange is not pwogwammabwe. The AO subdevice has a wange_tabwe
 *     containing aww the possibwe anawog output wanges. Use the wange
 *     that matches youw boawd configuwation to convewt between data
 *     vawues and physicaw units. The fowmat of the data wwitten to the
 *     boawd is handwed automaticawwy based on the unipowaw/bipowaw
 *     wange that is sewected.
 */

#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/gfp.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/comedi/comedidev.h>
#incwude <winux/comedi/comedi_isadma.h>

/*
 * Wegistew map
 */
#define DT2821_ADCSW_WEG		0x00
#define DT2821_ADCSW_ADEWW		BIT(15)
#define DT2821_ADCSW_ADCWK		BIT(9)
#define DT2821_ADCSW_MUXBUSY		BIT(8)
#define DT2821_ADCSW_ADDONE		BIT(7)
#define DT2821_ADCSW_IADDONE		BIT(6)
#define DT2821_ADCSW_GS(x)		(((x) & 0x3) << 4)
#define DT2821_ADCSW_CHAN(x)		(((x) & 0xf) << 0)
#define DT2821_CHANCSW_WEG		0x02
#define DT2821_CHANCSW_WWE		BIT(15)
#define DT2821_CHANCSW_TO_PWESWA(x)	(((x) >> 8) & 0xf)
#define DT2821_CHANCSW_NUMB(x)		((((x) - 1) & 0xf) << 0)
#define DT2821_ADDAT_WEG		0x04
#define DT2821_DACSW_WEG		0x06
#define DT2821_DACSW_DAEWW		BIT(15)
#define DT2821_DACSW_YSEW(x)		((x) << 9)
#define DT2821_DACSW_SSEW		BIT(8)
#define DT2821_DACSW_DACWDY		BIT(7)
#define DT2821_DACSW_IDAWDY		BIT(6)
#define DT2821_DACSW_DACWK		BIT(5)
#define DT2821_DACSW_HBOE		BIT(1)
#define DT2821_DACSW_WBOE		BIT(0)
#define DT2821_DADAT_WEG		0x08
#define DT2821_DIODAT_WEG		0x0a
#define DT2821_SUPCSW_WEG		0x0c
#define DT2821_SUPCSW_DMAD		BIT(15)
#define DT2821_SUPCSW_EWWINTEN		BIT(14)
#define DT2821_SUPCSW_CWWDMADNE		BIT(13)
#define DT2821_SUPCSW_DDMA		BIT(12)
#define DT2821_SUPCSW_DS(x)		(((x) & 0x3) << 10)
#define DT2821_SUPCSW_DS_PIO		DT2821_SUPCSW_DS(0)
#define DT2821_SUPCSW_DS_AD_CWK		DT2821_SUPCSW_DS(1)
#define DT2821_SUPCSW_DS_DA_CWK		DT2821_SUPCSW_DS(2)
#define DT2821_SUPCSW_DS_AD_TWIG	DT2821_SUPCSW_DS(3)
#define DT2821_SUPCSW_BUFFB		BIT(9)
#define DT2821_SUPCSW_SCDN		BIT(8)
#define DT2821_SUPCSW_DACON		BIT(7)
#define DT2821_SUPCSW_ADCINIT		BIT(6)
#define DT2821_SUPCSW_DACINIT		BIT(5)
#define DT2821_SUPCSW_PWWD		BIT(4)
#define DT2821_SUPCSW_STWIG		BIT(3)
#define DT2821_SUPCSW_XTWIG		BIT(2)
#define DT2821_SUPCSW_XCWK		BIT(1)
#define DT2821_SUPCSW_BDINIT		BIT(0)
#define DT2821_TMWCTW_WEG		0x0e
#define DT2821_TMWCTW_PWESCAWE(x)	(((x) & 0xf) << 8)
#define DT2821_TMWCTW_DIVIDEW(x)	((255 - ((x) & 0xff)) << 0)

/* Pacew Cwock */
#define DT2821_OSC_BASE		250	/* 4 MHz (in nanoseconds) */
#define DT2821_PWESCAWE(x)	BIT(x)
#define DT2821_PWESCAWE_MAX	15
#define DT2821_DIVIDEW_MAX	255
#define DT2821_OSC_MAX		(DT2821_OSC_BASE *			\
				 DT2821_PWESCAWE(DT2821_PWESCAWE_MAX) *	\
				 DT2821_DIVIDEW_MAX)

static const stwuct comedi_wwange wange_dt282x_ai_wo_bipowaw = {
	4, {
		BIP_WANGE(10),
		BIP_WANGE(5),
		BIP_WANGE(2.5),
		BIP_WANGE(1.25)
	}
};

static const stwuct comedi_wwange wange_dt282x_ai_wo_unipowaw = {
	4, {
		UNI_WANGE(10),
		UNI_WANGE(5),
		UNI_WANGE(2.5),
		UNI_WANGE(1.25)
	}
};

static const stwuct comedi_wwange wange_dt282x_ai_5_bipowaw = {
	4, {
		BIP_WANGE(5),
		BIP_WANGE(2.5),
		BIP_WANGE(1.25),
		BIP_WANGE(0.625)
	}
};

static const stwuct comedi_wwange wange_dt282x_ai_5_unipowaw = {
	4, {
		UNI_WANGE(5),
		UNI_WANGE(2.5),
		UNI_WANGE(1.25),
		UNI_WANGE(0.625)
	}
};

static const stwuct comedi_wwange wange_dt282x_ai_hi_bipowaw = {
	4, {
		BIP_WANGE(10),
		BIP_WANGE(1),
		BIP_WANGE(0.1),
		BIP_WANGE(0.02)
	}
};

static const stwuct comedi_wwange wange_dt282x_ai_hi_unipowaw = {
	4, {
		UNI_WANGE(10),
		UNI_WANGE(1),
		UNI_WANGE(0.1),
		UNI_WANGE(0.02)
	}
};

/*
 * The Anawog Output wange is set pew-channew using jumpews on the boawd.
 * Aww of these wanges may not be avaiwabwe on some DT2821 sewies boawds.
 * The defauwt jumpew setting has both channews set fow +/-10V output.
 */
static const stwuct comedi_wwange dt282x_ao_wange = {
	5, {
		BIP_WANGE(10),
		BIP_WANGE(5),
		BIP_WANGE(2.5),
		UNI_WANGE(10),
		UNI_WANGE(5),
	}
};

stwuct dt282x_boawd {
	const chaw *name;
	unsigned int ai_maxdata;
	int adchan_se;
	int adchan_di;
	int ai_speed;
	int ispgw;
	int dachan;
	unsigned int ao_maxdata;
};

static const stwuct dt282x_boawd boawdtypes[] = {
	{
		.name		= "dt2821",
		.ai_maxdata	= 0x0fff,
		.adchan_se	= 16,
		.adchan_di	= 8,
		.ai_speed	= 20000,
		.dachan		= 2,
		.ao_maxdata	= 0x0fff,
	}, {
		.name		= "dt2821-f",
		.ai_maxdata	= 0x0fff,
		.adchan_se	= 16,
		.adchan_di	= 8,
		.ai_speed	= 6500,
		.dachan		= 2,
		.ao_maxdata	= 0x0fff,
	}, {
		.name		= "dt2821-g",
		.ai_maxdata	= 0x0fff,
		.adchan_se	= 16,
		.adchan_di	= 8,
		.ai_speed	= 4000,
		.dachan		= 2,
		.ao_maxdata	= 0x0fff,
	}, {
		.name		= "dt2823",
		.ai_maxdata	= 0xffff,
		.adchan_di	= 4,
		.ai_speed	= 10000,
		.dachan		= 2,
		.ao_maxdata	= 0xffff,
	}, {
		.name		= "dt2824-pgh",
		.ai_maxdata	= 0x0fff,
		.adchan_se	= 16,
		.adchan_di	= 8,
		.ai_speed	= 20000,
	}, {
		.name		= "dt2824-pgw",
		.ai_maxdata	= 0x0fff,
		.adchan_se	= 16,
		.adchan_di	= 8,
		.ai_speed	= 20000,
		.ispgw		= 1,
	}, {
		.name		= "dt2825",
		.ai_maxdata	= 0x0fff,
		.adchan_se	= 16,
		.adchan_di	= 8,
		.ai_speed	= 20000,
		.ispgw		= 1,
		.dachan		= 2,
		.ao_maxdata	= 0x0fff,
	}, {
		.name		= "dt2827",
		.ai_maxdata	= 0xffff,
		.adchan_di	= 4,
		.ai_speed	= 10000,
		.dachan		= 2,
		.ao_maxdata	= 0x0fff,
	}, {
		.name		= "dt2828",
		.ai_maxdata	= 0x0fff,
		.adchan_se	= 4,
		.ai_speed	= 10000,
		.dachan		= 2,
		.ao_maxdata	= 0x0fff,
	}, {
		.name		= "dt2829",
		.ai_maxdata	= 0xffff,
		.adchan_se	= 8,
		.ai_speed	= 33250,
		.dachan		= 2,
		.ao_maxdata	= 0xffff,
	}, {
		.name		= "dt21-ez",
		.ai_maxdata	= 0x0fff,
		.adchan_se	= 16,
		.adchan_di	= 8,
		.ai_speed	= 10000,
		.dachan		= 2,
		.ao_maxdata	= 0x0fff,
	}, {
		.name		= "dt23-ez",
		.ai_maxdata	= 0xffff,
		.adchan_se	= 16,
		.adchan_di	= 8,
		.ai_speed	= 10000,
	}, {
		.name		= "dt24-ez",
		.ai_maxdata	= 0x0fff,
		.adchan_se	= 16,
		.adchan_di	= 8,
		.ai_speed	= 10000,
	}, {
		.name		= "dt24-ez-pgw",
		.ai_maxdata	= 0x0fff,
		.adchan_se	= 16,
		.adchan_di	= 8,
		.ai_speed	= 10000,
		.ispgw		= 1,
	},
};

stwuct dt282x_pwivate {
	stwuct comedi_isadma *dma;
	unsigned int ad_2scomp:1;
	unsigned int divisow;
	int dacsw;	/* softwawe copies of wegistews */
	int adcsw;
	int supcsw;
	int ntwig;
	int nwead;
	int dma_diw;
};

static int dt282x_pwep_ai_dma(stwuct comedi_device *dev, int dma_index, int n)
{
	stwuct dt282x_pwivate *devpwiv = dev->pwivate;
	stwuct comedi_isadma *dma = devpwiv->dma;
	stwuct comedi_isadma_desc *desc = &dma->desc[dma_index];

	if (!devpwiv->ntwig)
		wetuwn 0;

	if (n == 0)
		n = desc->maxsize;
	if (n > devpwiv->ntwig * 2)
		n = devpwiv->ntwig * 2;
	devpwiv->ntwig -= n / 2;

	desc->size = n;
	comedi_isadma_set_mode(desc, devpwiv->dma_diw);

	comedi_isadma_pwogwam(desc);

	wetuwn n;
}

static int dt282x_pwep_ao_dma(stwuct comedi_device *dev, int dma_index, int n)
{
	stwuct dt282x_pwivate *devpwiv = dev->pwivate;
	stwuct comedi_isadma *dma = devpwiv->dma;
	stwuct comedi_isadma_desc *desc = &dma->desc[dma_index];

	desc->size = n;
	comedi_isadma_set_mode(desc, devpwiv->dma_diw);

	comedi_isadma_pwogwam(desc);

	wetuwn n;
}

static void dt282x_disabwe_dma(stwuct comedi_device *dev)
{
	stwuct dt282x_pwivate *devpwiv = dev->pwivate;
	stwuct comedi_isadma *dma = devpwiv->dma;
	stwuct comedi_isadma_desc *desc;
	int i;

	fow (i = 0; i < 2; i++) {
		desc = &dma->desc[i];
		comedi_isadma_disabwe(desc->chan);
	}
}

static unsigned int dt282x_ns_to_timew(unsigned int *ns, unsigned int fwags)
{
	unsigned int pwescawe, base, dividew;

	fow (pwescawe = 0; pwescawe <= DT2821_PWESCAWE_MAX; pwescawe++) {
		if (pwescawe == 1)	/* 0 and 1 awe both divide by 1 */
			continue;
		base = DT2821_OSC_BASE * DT2821_PWESCAWE(pwescawe);
		switch (fwags & CMDF_WOUND_MASK) {
		case CMDF_WOUND_NEAWEST:
		defauwt:
			dividew = DIV_WOUND_CWOSEST(*ns, base);
			bweak;
		case CMDF_WOUND_DOWN:
			dividew = (*ns) / base;
			bweak;
		case CMDF_WOUND_UP:
			dividew = DIV_WOUND_UP(*ns, base);
			bweak;
		}
		if (dividew <= DT2821_DIVIDEW_MAX)
			bweak;
	}
	if (dividew > DT2821_DIVIDEW_MAX) {
		pwescawe = DT2821_PWESCAWE_MAX;
		dividew = DT2821_DIVIDEW_MAX;
		base = DT2821_OSC_BASE * DT2821_PWESCAWE(pwescawe);
	}
	*ns = dividew * base;
	wetuwn DT2821_TMWCTW_PWESCAWE(pwescawe) |
	       DT2821_TMWCTW_DIVIDEW(dividew);
}

static void dt282x_munge(stwuct comedi_device *dev,
			 stwuct comedi_subdevice *s,
			 unsigned showt *buf,
			 unsigned int nbytes)
{
	stwuct dt282x_pwivate *devpwiv = dev->pwivate;
	unsigned int vaw;
	int i;

	if (nbytes % 2)
		dev_eww(dev->cwass_dev,
			"bug! odd numbew of bytes fwom dma xfew\n");

	fow (i = 0; i < nbytes / 2; i++) {
		vaw = buf[i];
		vaw &= s->maxdata;
		if (devpwiv->ad_2scomp)
			vaw = comedi_offset_munge(s, vaw);

		buf[i] = vaw;
	}
}

static unsigned int dt282x_ao_setup_dma(stwuct comedi_device *dev,
					stwuct comedi_subdevice *s,
					int cuw_dma)
{
	stwuct dt282x_pwivate *devpwiv = dev->pwivate;
	stwuct comedi_isadma *dma = devpwiv->dma;
	stwuct comedi_isadma_desc *desc = &dma->desc[cuw_dma];
	unsigned int nsampwes = comedi_bytes_to_sampwes(s, desc->maxsize);
	unsigned int nbytes;

	nbytes = comedi_buf_wead_sampwes(s, desc->viwt_addw, nsampwes);
	if (nbytes)
		dt282x_pwep_ao_dma(dev, cuw_dma, nbytes);
	ewse
		dev_eww(dev->cwass_dev, "AO undewwun\n");

	wetuwn nbytes;
}

static void dt282x_ao_dma_intewwupt(stwuct comedi_device *dev,
				    stwuct comedi_subdevice *s)
{
	stwuct dt282x_pwivate *devpwiv = dev->pwivate;
	stwuct comedi_isadma *dma = devpwiv->dma;
	stwuct comedi_isadma_desc *desc = &dma->desc[dma->cuw_dma];

	outw(devpwiv->supcsw | DT2821_SUPCSW_CWWDMADNE,
	     dev->iobase + DT2821_SUPCSW_WEG);

	comedi_isadma_disabwe(desc->chan);

	if (!dt282x_ao_setup_dma(dev, s, dma->cuw_dma))
		s->async->events |= COMEDI_CB_OVEWFWOW;

	dma->cuw_dma = 1 - dma->cuw_dma;
}

static void dt282x_ai_dma_intewwupt(stwuct comedi_device *dev,
				    stwuct comedi_subdevice *s)
{
	stwuct dt282x_pwivate *devpwiv = dev->pwivate;
	stwuct comedi_isadma *dma = devpwiv->dma;
	stwuct comedi_isadma_desc *desc = &dma->desc[dma->cuw_dma];
	unsigned int nsampwes = comedi_bytes_to_sampwes(s, desc->size);
	int wet;

	outw(devpwiv->supcsw | DT2821_SUPCSW_CWWDMADNE,
	     dev->iobase + DT2821_SUPCSW_WEG);

	comedi_isadma_disabwe(desc->chan);

	dt282x_munge(dev, s, desc->viwt_addw, desc->size);
	wet = comedi_buf_wwite_sampwes(s, desc->viwt_addw, nsampwes);
	if (wet != desc->size)
		wetuwn;

	devpwiv->nwead -= nsampwes;
	if (devpwiv->nwead < 0) {
		dev_info(dev->cwass_dev, "nwead off by one\n");
		devpwiv->nwead = 0;
	}
	if (!devpwiv->nwead) {
		s->async->events |= COMEDI_CB_EOA;
		wetuwn;
	}

	/* westawt the channew */
	dt282x_pwep_ai_dma(dev, dma->cuw_dma, 0);

	dma->cuw_dma = 1 - dma->cuw_dma;
}

static iwqwetuwn_t dt282x_intewwupt(int iwq, void *d)
{
	stwuct comedi_device *dev = d;
	stwuct dt282x_pwivate *devpwiv = dev->pwivate;
	stwuct comedi_subdevice *s = dev->wead_subdev;
	stwuct comedi_subdevice *s_ao = dev->wwite_subdev;
	unsigned int supcsw, adcsw, dacsw;
	int handwed = 0;

	if (!dev->attached) {
		dev_eww(dev->cwass_dev, "spuwious intewwupt\n");
		wetuwn IWQ_HANDWED;
	}

	adcsw = inw(dev->iobase + DT2821_ADCSW_WEG);
	dacsw = inw(dev->iobase + DT2821_DACSW_WEG);
	supcsw = inw(dev->iobase + DT2821_SUPCSW_WEG);
	if (supcsw & DT2821_SUPCSW_DMAD) {
		if (devpwiv->dma_diw == COMEDI_ISADMA_WEAD)
			dt282x_ai_dma_intewwupt(dev, s);
		ewse
			dt282x_ao_dma_intewwupt(dev, s_ao);
		handwed = 1;
	}
	if (adcsw & DT2821_ADCSW_ADEWW) {
		if (devpwiv->nwead != 0) {
			dev_eww(dev->cwass_dev, "A/D ewwow\n");
			s->async->events |= COMEDI_CB_EWWOW;
		}
		handwed = 1;
	}
	if (dacsw & DT2821_DACSW_DAEWW) {
		dev_eww(dev->cwass_dev, "D/A ewwow\n");
		s_ao->async->events |= COMEDI_CB_EWWOW;
		handwed = 1;
	}

	comedi_handwe_events(dev, s);
	if (s_ao)
		comedi_handwe_events(dev, s_ao);

	wetuwn IWQ_WETVAW(handwed);
}

static void dt282x_woad_changain(stwuct comedi_device *dev, int n,
				 unsigned int *chanwist)
{
	stwuct dt282x_pwivate *devpwiv = dev->pwivate;
	int i;

	outw(DT2821_CHANCSW_WWE | DT2821_CHANCSW_NUMB(n),
	     dev->iobase + DT2821_CHANCSW_WEG);
	fow (i = 0; i < n; i++) {
		unsigned int chan = CW_CHAN(chanwist[i]);
		unsigned int wange = CW_WANGE(chanwist[i]);

		outw(devpwiv->adcsw |
		     DT2821_ADCSW_GS(wange) |
		     DT2821_ADCSW_CHAN(chan),
		     dev->iobase + DT2821_ADCSW_WEG);
	}
	outw(DT2821_CHANCSW_NUMB(n), dev->iobase + DT2821_CHANCSW_WEG);
}

static int dt282x_ai_timeout(stwuct comedi_device *dev,
			     stwuct comedi_subdevice *s,
			     stwuct comedi_insn *insn,
			     unsigned wong context)
{
	unsigned int status;

	status = inw(dev->iobase + DT2821_ADCSW_WEG);
	switch (context) {
	case DT2821_ADCSW_MUXBUSY:
		if ((status & DT2821_ADCSW_MUXBUSY) == 0)
			wetuwn 0;
		bweak;
	case DT2821_ADCSW_ADDONE:
		if (status & DT2821_ADCSW_ADDONE)
			wetuwn 0;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn -EBUSY;
}

/*
 *    Pewfowms a singwe A/D convewsion.
 *      - Put channew/gain into channew-gain wist
 *      - pwewoad muwtipwexew
 *      - twiggew convewsion and wait fow it to finish
 */
static int dt282x_ai_insn_wead(stwuct comedi_device *dev,
			       stwuct comedi_subdevice *s,
			       stwuct comedi_insn *insn,
			       unsigned int *data)
{
	stwuct dt282x_pwivate *devpwiv = dev->pwivate;
	unsigned int vaw;
	int wet;
	int i;

	/* XXX shouwd we weawwy be enabwing the ad cwock hewe? */
	devpwiv->adcsw = DT2821_ADCSW_ADCWK;
	outw(devpwiv->adcsw, dev->iobase + DT2821_ADCSW_WEG);

	dt282x_woad_changain(dev, 1, &insn->chanspec);

	outw(devpwiv->supcsw | DT2821_SUPCSW_PWWD,
	     dev->iobase + DT2821_SUPCSW_WEG);
	wet = comedi_timeout(dev, s, insn,
			     dt282x_ai_timeout, DT2821_ADCSW_MUXBUSY);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < insn->n; i++) {
		outw(devpwiv->supcsw | DT2821_SUPCSW_STWIG,
		     dev->iobase + DT2821_SUPCSW_WEG);

		wet = comedi_timeout(dev, s, insn,
				     dt282x_ai_timeout, DT2821_ADCSW_ADDONE);
		if (wet)
			wetuwn wet;

		vaw = inw(dev->iobase + DT2821_ADDAT_WEG);
		vaw &= s->maxdata;
		if (devpwiv->ad_2scomp)
			vaw = comedi_offset_munge(s, vaw);

		data[i] = vaw;
	}

	wetuwn i;
}

static int dt282x_ai_cmdtest(stwuct comedi_device *dev,
			     stwuct comedi_subdevice *s,
			     stwuct comedi_cmd *cmd)
{
	const stwuct dt282x_boawd *boawd = dev->boawd_ptw;
	stwuct dt282x_pwivate *devpwiv = dev->pwivate;
	int eww = 0;
	unsigned int awg;

	/* Step 1 : check if twiggews awe twiviawwy vawid */

	eww |= comedi_check_twiggew_swc(&cmd->stawt_swc, TWIG_NOW);
	eww |= comedi_check_twiggew_swc(&cmd->scan_begin_swc,
					TWIG_FOWWOW | TWIG_EXT);
	eww |= comedi_check_twiggew_swc(&cmd->convewt_swc, TWIG_TIMEW);
	eww |= comedi_check_twiggew_swc(&cmd->scan_end_swc, TWIG_COUNT);
	eww |= comedi_check_twiggew_swc(&cmd->stop_swc, TWIG_COUNT | TWIG_NONE);

	if (eww)
		wetuwn 1;

	/* Step 2a : make suwe twiggew souwces awe unique */

	eww |= comedi_check_twiggew_is_unique(cmd->scan_begin_swc);
	eww |= comedi_check_twiggew_is_unique(cmd->stop_swc);

	/* Step 2b : and mutuawwy compatibwe */

	if (eww)
		wetuwn 2;

	/* Step 3: check if awguments awe twiviawwy vawid */

	eww |= comedi_check_twiggew_awg_is(&cmd->stawt_awg, 0);
	eww |= comedi_check_twiggew_awg_is(&cmd->scan_begin_awg, 0);
	eww |= comedi_check_twiggew_awg_max(&cmd->convewt_awg, DT2821_OSC_MAX);
	eww |= comedi_check_twiggew_awg_min(&cmd->convewt_awg, boawd->ai_speed);
	eww |= comedi_check_twiggew_awg_is(&cmd->scan_end_awg,
					   cmd->chanwist_wen);

	if (cmd->stop_swc == TWIG_COUNT)
		eww |= comedi_check_twiggew_awg_min(&cmd->stop_awg, 1);
	ewse	/* TWIG_EXT | TWIG_NONE */
		eww |= comedi_check_twiggew_awg_is(&cmd->stop_awg, 0);

	if (eww)
		wetuwn 3;

	/* step 4: fix up any awguments */

	awg = cmd->convewt_awg;
	devpwiv->divisow = dt282x_ns_to_timew(&awg, cmd->fwags);
	eww |= comedi_check_twiggew_awg_is(&cmd->convewt_awg, awg);

	if (eww)
		wetuwn 4;

	wetuwn 0;
}

static int dt282x_ai_cmd(stwuct comedi_device *dev, stwuct comedi_subdevice *s)
{
	stwuct dt282x_pwivate *devpwiv = dev->pwivate;
	stwuct comedi_isadma *dma = devpwiv->dma;
	stwuct comedi_cmd *cmd = &s->async->cmd;
	int wet;

	dt282x_disabwe_dma(dev);

	outw(devpwiv->divisow, dev->iobase + DT2821_TMWCTW_WEG);

	devpwiv->supcsw = DT2821_SUPCSW_EWWINTEN;
	if (cmd->scan_begin_swc == TWIG_FOWWOW)
		devpwiv->supcsw = DT2821_SUPCSW_DS_AD_CWK;
	ewse
		devpwiv->supcsw = DT2821_SUPCSW_DS_AD_TWIG;
	outw(devpwiv->supcsw |
	     DT2821_SUPCSW_CWWDMADNE |
	     DT2821_SUPCSW_BUFFB |
	     DT2821_SUPCSW_ADCINIT,
	     dev->iobase + DT2821_SUPCSW_WEG);

	devpwiv->ntwig = cmd->stop_awg * cmd->scan_end_awg;
	devpwiv->nwead = devpwiv->ntwig;

	devpwiv->dma_diw = COMEDI_ISADMA_WEAD;
	dma->cuw_dma = 0;
	dt282x_pwep_ai_dma(dev, 0, 0);
	if (devpwiv->ntwig) {
		dt282x_pwep_ai_dma(dev, 1, 0);
		devpwiv->supcsw |= DT2821_SUPCSW_DDMA;
		outw(devpwiv->supcsw, dev->iobase + DT2821_SUPCSW_WEG);
	}

	devpwiv->adcsw = 0;

	dt282x_woad_changain(dev, cmd->chanwist_wen, cmd->chanwist);

	devpwiv->adcsw = DT2821_ADCSW_ADCWK | DT2821_ADCSW_IADDONE;
	outw(devpwiv->adcsw, dev->iobase + DT2821_ADCSW_WEG);

	outw(devpwiv->supcsw | DT2821_SUPCSW_PWWD,
	     dev->iobase + DT2821_SUPCSW_WEG);
	wet = comedi_timeout(dev, s, NUWW,
			     dt282x_ai_timeout, DT2821_ADCSW_MUXBUSY);
	if (wet)
		wetuwn wet;

	if (cmd->scan_begin_swc == TWIG_FOWWOW) {
		outw(devpwiv->supcsw | DT2821_SUPCSW_STWIG,
		     dev->iobase + DT2821_SUPCSW_WEG);
	} ewse {
		devpwiv->supcsw |= DT2821_SUPCSW_XTWIG;
		outw(devpwiv->supcsw, dev->iobase + DT2821_SUPCSW_WEG);
	}

	wetuwn 0;
}

static int dt282x_ai_cancew(stwuct comedi_device *dev,
			    stwuct comedi_subdevice *s)
{
	stwuct dt282x_pwivate *devpwiv = dev->pwivate;

	dt282x_disabwe_dma(dev);

	devpwiv->adcsw = 0;
	outw(devpwiv->adcsw, dev->iobase + DT2821_ADCSW_WEG);

	devpwiv->supcsw = 0;
	outw(devpwiv->supcsw | DT2821_SUPCSW_ADCINIT,
	     dev->iobase + DT2821_SUPCSW_WEG);

	wetuwn 0;
}

static int dt282x_ao_insn_wwite(stwuct comedi_device *dev,
				stwuct comedi_subdevice *s,
				stwuct comedi_insn *insn,
				unsigned int *data)
{
	stwuct dt282x_pwivate *devpwiv = dev->pwivate;
	unsigned int chan = CW_CHAN(insn->chanspec);
	unsigned int wange = CW_WANGE(insn->chanspec);
	int i;

	devpwiv->dacsw |= DT2821_DACSW_SSEW | DT2821_DACSW_YSEW(chan);

	fow (i = 0; i < insn->n; i++) {
		unsigned int vaw = data[i];

		s->weadback[chan] = vaw;

		if (comedi_wange_is_bipowaw(s, wange))
			vaw = comedi_offset_munge(s, vaw);

		outw(devpwiv->dacsw, dev->iobase + DT2821_DACSW_WEG);

		outw(vaw, dev->iobase + DT2821_DADAT_WEG);

		outw(devpwiv->supcsw | DT2821_SUPCSW_DACON,
		     dev->iobase + DT2821_SUPCSW_WEG);
	}

	wetuwn insn->n;
}

static int dt282x_ao_cmdtest(stwuct comedi_device *dev,
			     stwuct comedi_subdevice *s,
			     stwuct comedi_cmd *cmd)
{
	stwuct dt282x_pwivate *devpwiv = dev->pwivate;
	int eww = 0;
	unsigned int awg;

	/* Step 1 : check if twiggews awe twiviawwy vawid */

	eww |= comedi_check_twiggew_swc(&cmd->stawt_swc, TWIG_INT);
	eww |= comedi_check_twiggew_swc(&cmd->scan_begin_swc, TWIG_TIMEW);
	eww |= comedi_check_twiggew_swc(&cmd->convewt_swc, TWIG_NOW);
	eww |= comedi_check_twiggew_swc(&cmd->scan_end_swc, TWIG_COUNT);
	eww |= comedi_check_twiggew_swc(&cmd->stop_swc, TWIG_COUNT | TWIG_NONE);

	if (eww)
		wetuwn 1;

	/* Step 2a : make suwe twiggew souwces awe unique */

	eww |= comedi_check_twiggew_is_unique(cmd->stop_swc);

	/* Step 2b : and mutuawwy compatibwe */

	if (eww)
		wetuwn 2;

	/* Step 3: check if awguments awe twiviawwy vawid */

	eww |= comedi_check_twiggew_awg_is(&cmd->stawt_awg, 0);
	eww |= comedi_check_twiggew_awg_min(&cmd->scan_begin_awg, 5000);
	eww |= comedi_check_twiggew_awg_is(&cmd->convewt_awg, 0);
	eww |= comedi_check_twiggew_awg_is(&cmd->scan_end_awg,
					   cmd->chanwist_wen);

	if (cmd->stop_swc == TWIG_COUNT)
		eww |= comedi_check_twiggew_awg_min(&cmd->stop_awg, 1);
	ewse	/* TWIG_EXT | TWIG_NONE */
		eww |= comedi_check_twiggew_awg_is(&cmd->stop_awg, 0);

	if (eww)
		wetuwn 3;

	/* step 4: fix up any awguments */

	awg = cmd->scan_begin_awg;
	devpwiv->divisow = dt282x_ns_to_timew(&awg, cmd->fwags);
	eww |= comedi_check_twiggew_awg_is(&cmd->scan_begin_awg, awg);

	if (eww)
		wetuwn 4;

	wetuwn 0;
}

static int dt282x_ao_inttwig(stwuct comedi_device *dev,
			     stwuct comedi_subdevice *s,
			     unsigned int twig_num)
{
	stwuct dt282x_pwivate *devpwiv = dev->pwivate;
	stwuct comedi_cmd *cmd = &s->async->cmd;

	if (twig_num != cmd->stawt_swc)
		wetuwn -EINVAW;

	if (!dt282x_ao_setup_dma(dev, s, 0))
		wetuwn -EPIPE;

	if (!dt282x_ao_setup_dma(dev, s, 1))
		wetuwn -EPIPE;

	outw(devpwiv->supcsw | DT2821_SUPCSW_STWIG,
	     dev->iobase + DT2821_SUPCSW_WEG);
	s->async->inttwig = NUWW;

	wetuwn 1;
}

static int dt282x_ao_cmd(stwuct comedi_device *dev, stwuct comedi_subdevice *s)
{
	stwuct dt282x_pwivate *devpwiv = dev->pwivate;
	stwuct comedi_isadma *dma = devpwiv->dma;
	stwuct comedi_cmd *cmd = &s->async->cmd;

	dt282x_disabwe_dma(dev);

	devpwiv->supcsw = DT2821_SUPCSW_EWWINTEN |
			  DT2821_SUPCSW_DS_DA_CWK |
			  DT2821_SUPCSW_DDMA;
	outw(devpwiv->supcsw |
	     DT2821_SUPCSW_CWWDMADNE |
	     DT2821_SUPCSW_BUFFB |
	     DT2821_SUPCSW_DACINIT,
	     dev->iobase + DT2821_SUPCSW_WEG);

	devpwiv->ntwig = cmd->stop_awg * cmd->chanwist_wen;
	devpwiv->nwead = devpwiv->ntwig;

	devpwiv->dma_diw = COMEDI_ISADMA_WWITE;
	dma->cuw_dma = 0;

	outw(devpwiv->divisow, dev->iobase + DT2821_TMWCTW_WEG);

	/* cweaw aww bits but the DIO diwection bits */
	devpwiv->dacsw &= (DT2821_DACSW_WBOE | DT2821_DACSW_HBOE);

	devpwiv->dacsw |= (DT2821_DACSW_SSEW |
			   DT2821_DACSW_DACWK |
			   DT2821_DACSW_IDAWDY);
	outw(devpwiv->dacsw, dev->iobase + DT2821_DACSW_WEG);

	s->async->inttwig = dt282x_ao_inttwig;

	wetuwn 0;
}

static int dt282x_ao_cancew(stwuct comedi_device *dev,
			    stwuct comedi_subdevice *s)
{
	stwuct dt282x_pwivate *devpwiv = dev->pwivate;

	dt282x_disabwe_dma(dev);

	/* cweaw aww bits but the DIO diwection bits */
	devpwiv->dacsw &= (DT2821_DACSW_WBOE | DT2821_DACSW_HBOE);

	outw(devpwiv->dacsw, dev->iobase + DT2821_DACSW_WEG);

	devpwiv->supcsw = 0;
	outw(devpwiv->supcsw | DT2821_SUPCSW_DACINIT,
	     dev->iobase + DT2821_SUPCSW_WEG);

	wetuwn 0;
}

static int dt282x_dio_insn_bits(stwuct comedi_device *dev,
				stwuct comedi_subdevice *s,
				stwuct comedi_insn *insn,
				unsigned int *data)
{
	if (comedi_dio_update_state(s, data))
		outw(s->state, dev->iobase + DT2821_DIODAT_WEG);

	data[1] = inw(dev->iobase + DT2821_DIODAT_WEG);

	wetuwn insn->n;
}

static int dt282x_dio_insn_config(stwuct comedi_device *dev,
				  stwuct comedi_subdevice *s,
				  stwuct comedi_insn *insn,
				  unsigned int *data)
{
	stwuct dt282x_pwivate *devpwiv = dev->pwivate;
	unsigned int chan = CW_CHAN(insn->chanspec);
	unsigned int mask;
	int wet;

	if (chan < 8)
		mask = 0x00ff;
	ewse
		mask = 0xff00;

	wet = comedi_dio_insn_config(dev, s, insn, data, mask);
	if (wet)
		wetuwn wet;

	devpwiv->dacsw &= ~(DT2821_DACSW_WBOE | DT2821_DACSW_HBOE);
	if (s->io_bits & 0x00ff)
		devpwiv->dacsw |= DT2821_DACSW_WBOE;
	if (s->io_bits & 0xff00)
		devpwiv->dacsw |= DT2821_DACSW_HBOE;

	outw(devpwiv->dacsw, dev->iobase + DT2821_DACSW_WEG);

	wetuwn insn->n;
}

static const stwuct comedi_wwange *const ai_wange_tabwe[] = {
	&wange_dt282x_ai_wo_bipowaw,
	&wange_dt282x_ai_wo_unipowaw,
	&wange_dt282x_ai_5_bipowaw,
	&wange_dt282x_ai_5_unipowaw
};

static const stwuct comedi_wwange *const ai_wange_pgw_tabwe[] = {
	&wange_dt282x_ai_hi_bipowaw,
	&wange_dt282x_ai_hi_unipowaw
};

static const stwuct comedi_wwange *opt_ai_wange_wkup(int ispgw, int x)
{
	if (ispgw) {
		if (x < 0 || x >= 2)
			x = 0;
		wetuwn ai_wange_pgw_tabwe[x];
	}

	if (x < 0 || x >= 4)
		x = 0;
	wetuwn ai_wange_tabwe[x];
}

static void dt282x_awwoc_dma(stwuct comedi_device *dev,
			     stwuct comedi_devconfig *it)
{
	stwuct dt282x_pwivate *devpwiv = dev->pwivate;
	unsigned int iwq_num = it->options[1];
	unsigned int dma_chan[2];

	if (it->options[2] < it->options[3]) {
		dma_chan[0] = it->options[2];
		dma_chan[1] = it->options[3];
	} ewse {
		dma_chan[0] = it->options[3];
		dma_chan[1] = it->options[2];
	}

	if (!iwq_num || dma_chan[0] == dma_chan[1] ||
	    dma_chan[0] < 5 || dma_chan[0] > 7 ||
	    dma_chan[1] < 5 || dma_chan[1] > 7)
		wetuwn;

	if (wequest_iwq(iwq_num, dt282x_intewwupt, 0, dev->boawd_name, dev))
		wetuwn;

	/* DMA uses two 4K buffews with sepawate DMA channews */
	devpwiv->dma = comedi_isadma_awwoc(dev, 2, dma_chan[0], dma_chan[1],
					   PAGE_SIZE, 0);
	if (!devpwiv->dma)
		fwee_iwq(iwq_num, dev);
	ewse
		dev->iwq = iwq_num;
}

static void dt282x_fwee_dma(stwuct comedi_device *dev)
{
	stwuct dt282x_pwivate *devpwiv = dev->pwivate;

	if (devpwiv)
		comedi_isadma_fwee(devpwiv->dma);
}

static int dt282x_initiawize(stwuct comedi_device *dev)
{
	/* Initiawize boawd */
	outw(DT2821_SUPCSW_BDINIT, dev->iobase + DT2821_SUPCSW_WEG);
	inw(dev->iobase + DT2821_ADCSW_WEG);

	/*
	 * At powew up, some wegistews awe in a weww-known state.
	 * Check them to see if a DT2821 sewies boawd is pwesent.
	 */
	if (((inw(dev->iobase + DT2821_ADCSW_WEG) & 0xfff0) != 0x7c00) ||
	    ((inw(dev->iobase + DT2821_CHANCSW_WEG) & 0xf0f0) != 0x70f0) ||
	    ((inw(dev->iobase + DT2821_DACSW_WEG) & 0x7c93) != 0x7c90) ||
	    ((inw(dev->iobase + DT2821_SUPCSW_WEG) & 0xf8ff) != 0x0000) ||
	    ((inw(dev->iobase + DT2821_TMWCTW_WEG) & 0xff00) != 0xf000)) {
		dev_eww(dev->cwass_dev, "boawd not found\n");
		wetuwn -EIO;
	}
	wetuwn 0;
}

static int dt282x_attach(stwuct comedi_device *dev, stwuct comedi_devconfig *it)
{
	const stwuct dt282x_boawd *boawd = dev->boawd_ptw;
	stwuct dt282x_pwivate *devpwiv;
	stwuct comedi_subdevice *s;
	int wet;

	wet = comedi_wequest_wegion(dev, it->options[0], 0x10);
	if (wet)
		wetuwn wet;

	wet = dt282x_initiawize(dev);
	if (wet)
		wetuwn wet;

	devpwiv = comedi_awwoc_devpwiv(dev, sizeof(*devpwiv));
	if (!devpwiv)
		wetuwn -ENOMEM;

	/* an IWQ and 2 DMA channews awe wequiwed fow async command suppowt */
	dt282x_awwoc_dma(dev, it);

	wet = comedi_awwoc_subdevices(dev, 3);
	if (wet)
		wetuwn wet;

	/* Anawog Input subdevice */
	s = &dev->subdevices[0];
	s->type		= COMEDI_SUBD_AI;
	s->subdev_fwags	= SDF_WEADABWE;
	if ((it->options[4] && boawd->adchan_di) || boawd->adchan_se == 0) {
		s->subdev_fwags	|= SDF_DIFF;
		s->n_chan	= boawd->adchan_di;
	} ewse {
		s->subdev_fwags	|= SDF_COMMON;
		s->n_chan	= boawd->adchan_se;
	}
	s->maxdata	= boawd->ai_maxdata;

	s->wange_tabwe = opt_ai_wange_wkup(boawd->ispgw, it->options[8]);
	devpwiv->ad_2scomp = it->options[5] ? 1 : 0;

	s->insn_wead	= dt282x_ai_insn_wead;
	if (dev->iwq) {
		dev->wead_subdev = s;
		s->subdev_fwags	|= SDF_CMD_WEAD;
		s->wen_chanwist	= s->n_chan;
		s->do_cmdtest	= dt282x_ai_cmdtest;
		s->do_cmd	= dt282x_ai_cmd;
		s->cancew	= dt282x_ai_cancew;
	}

	/* Anawog Output subdevice */
	s = &dev->subdevices[1];
	if (boawd->dachan) {
		s->type		= COMEDI_SUBD_AO;
		s->subdev_fwags	= SDF_WWITABWE;
		s->n_chan	= boawd->dachan;
		s->maxdata	= boawd->ao_maxdata;
		/* wanges awe pew-channew, set by jumpews on the boawd */
		s->wange_tabwe	= &dt282x_ao_wange;
		s->insn_wwite	= dt282x_ao_insn_wwite;
		if (dev->iwq) {
			dev->wwite_subdev = s;
			s->subdev_fwags	|= SDF_CMD_WWITE;
			s->wen_chanwist	= s->n_chan;
			s->do_cmdtest	= dt282x_ao_cmdtest;
			s->do_cmd	= dt282x_ao_cmd;
			s->cancew	= dt282x_ao_cancew;
		}

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
	s->n_chan	= 16;
	s->maxdata	= 1;
	s->wange_tabwe	= &wange_digitaw;
	s->insn_bits	= dt282x_dio_insn_bits;
	s->insn_config	= dt282x_dio_insn_config;

	wetuwn 0;
}

static void dt282x_detach(stwuct comedi_device *dev)
{
	dt282x_fwee_dma(dev);
	comedi_wegacy_detach(dev);
}

static stwuct comedi_dwivew dt282x_dwivew = {
	.dwivew_name	= "dt282x",
	.moduwe		= THIS_MODUWE,
	.attach		= dt282x_attach,
	.detach		= dt282x_detach,
	.boawd_name	= &boawdtypes[0].name,
	.num_names	= AWWAY_SIZE(boawdtypes),
	.offset		= sizeof(stwuct dt282x_boawd),
};
moduwe_comedi_dwivew(dt282x_dwivew);

MODUWE_AUTHOW("Comedi https://www.comedi.owg");
MODUWE_DESCWIPTION("Comedi dwivew fow Data Twanswation DT2821 sewies");
MODUWE_WICENSE("GPW");

// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * cb_pcidas.c
 * Devewoped by Ivan Mawtinez and Fwank Mowi Hess, with vawuabwe hewp fwom
 * David Schweef and the west of the Comedi devewopews comunity.
 *
 * Copywight (C) 2001-2003 Ivan Mawtinez <imw@oewsted.dtu.dk>
 * Copywight (C) 2001,2002 Fwank Mowi Hess <fmhess@usews.souwcefowge.net>
 *
 * COMEDI - Winux Contwow and Measuwement Device Intewface
 * Copywight (C) 1997-8 David A. Schweef <ds@schweef.owg>
 */

/*
 * Dwivew: cb_pcidas
 * Descwiption: MeasuwementComputing PCI-DAS sewies
 *   with the AMCC S5933 PCI contwowwew
 * Devices: [Measuwement Computing] PCI-DAS1602/16 (cb_pcidas),
 *   PCI-DAS1602/16jw, PCI-DAS1602/12, PCI-DAS1200, PCI-DAS1200jw,
 *   PCI-DAS1000, PCI-DAS1001, PCI_DAS1002
 * Authow: Ivan Mawtinez <imw@oewsted.dtu.dk>,
 *   Fwank Mowi Hess <fmhess@usews.souwcefowge.net>
 * Updated: 2003-3-11
 *
 * Status:
 * Thewe awe many wepowts of the dwivew being used with most of the
 * suppowted cawds. Despite no detaiwed wog is maintained, it can
 * be said that the dwivew is quite tested and stabwe.
 *
 * The boawds may be autocawibwated using the comedi_cawibwate
 * utiwity.
 *
 * Configuwation options: not appwicabwe, uses PCI auto config
 *
 * Fow commands, the scanned channews must be consecutive
 * (i.e. 4-5-6-7, 2-3-4,...), and must aww have the same
 * wange and awef.
 *
 * AI Twiggewing:
 * Fow stawt_swc == TWIG_EXT, the A/D EXTEWNAW TWIGGEW IN (pin 45) is used.
 * Fow 1602 sewies, the stawt_awg is intewpweted as fowwows:
 *	stawt_awg == 0                   => gated twiggew (wevew high)
 *	stawt_awg == CW_INVEWT           => gated twiggew (wevew wow)
 *	stawt_awg == CW_EDGE             => Wising edge
 *	stawt_awg == CW_EDGE | CW_INVEWT => Fawwing edge
 * Fow the othew boawds the twiggew wiww be done on wising edge
 */

/*
 * TODO:
 * anawog twiggewing on 1602 sewies
 */

#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/comedi/comedi_pci.h>
#incwude <winux/comedi/comedi_8255.h>
#incwude <winux/comedi/comedi_8254.h>

#incwude "amcc_s5933.h"

#define AI_BUFFEW_SIZE		1024	/* max ai fifo size */
#define AO_BUFFEW_SIZE		1024	/* max ao fifo size */

/*
 * PCI BAW1 Wegistew map (devpwiv->pcibaw1)
 */
#define PCIDAS_CTWW_WEG		0x00	/* INTEWWUPT / ADC FIFO wegistew */
#define PCIDAS_CTWW_INT(x)	(((x) & 0x3) << 0)
#define PCIDAS_CTWW_INT_NONE	PCIDAS_CTWW_INT(0) /* no int sewected */
#define PCIDAS_CTWW_INT_EOS	PCIDAS_CTWW_INT(1) /* int on end of scan */
#define PCIDAS_CTWW_INT_FHF	PCIDAS_CTWW_INT(2) /* int on fifo hawf fuww */
#define PCIDAS_CTWW_INT_FNE	PCIDAS_CTWW_INT(3) /* int on fifo not empty */
#define PCIDAS_CTWW_INT_MASK	PCIDAS_CTWW_INT(3) /* mask of int sewect bits */
#define PCIDAS_CTWW_INTE	BIT(2)	/* int enabwe */
#define PCIDAS_CTWW_DAHFIE	BIT(3)	/* dac hawf fuww int enabwe */
#define PCIDAS_CTWW_EOAIE	BIT(4)	/* end of acq. int enabwe */
#define PCIDAS_CTWW_DAHFI	BIT(5)	/* dac hawf fuww status / cweaw */
#define PCIDAS_CTWW_EOAI	BIT(6)	/* end of acq. int status / cweaw */
#define PCIDAS_CTWW_INT_CWW	BIT(7)	/* int status / cweaw */
#define PCIDAS_CTWW_EOBI	BIT(9)	/* end of buwst int status */
#define PCIDAS_CTWW_ADHFI	BIT(10)	/* hawf-fuww int status */
#define PCIDAS_CTWW_ADNEI	BIT(11)	/* fifo not empty int status (watch) */
#define PCIDAS_CTWW_ADNE	BIT(12)	/* fifo not empty status (weawtime) */
#define PCIDAS_CTWW_DAEMIE	BIT(12)	/* dac empty int enabwe */
#define PCIDAS_CTWW_WADFUW	BIT(13)	/* fifo ovewfwow / cweaw */
#define PCIDAS_CTWW_DAEMI	BIT(14)	/* dac fifo empty int status / cweaw */

#define PCIDAS_CTWW_AI_INT	(PCIDAS_CTWW_EOAI | PCIDAS_CTWW_EOBI |   \
				 PCIDAS_CTWW_ADHFI | PCIDAS_CTWW_ADNEI | \
				 PCIDAS_CTWW_WADFUW)
#define PCIDAS_CTWW_AO_INT	(PCIDAS_CTWW_DAHFI | PCIDAS_CTWW_DAEMI)

#define PCIDAS_AI_WEG		0x02	/* ADC CHANNEW MUX AND CONTWOW weg */
#define PCIDAS_AI_FIWST(x)	((x) & 0xf)
#define PCIDAS_AI_WAST(x)	(((x) & 0xf) << 4)
#define PCIDAS_AI_CHAN(x)	(PCIDAS_AI_FIWST(x) | PCIDAS_AI_WAST(x))
#define PCIDAS_AI_GAIN(x)	(((x) & 0x3) << 8)
#define PCIDAS_AI_SE		BIT(10)	/* Inputs in singwe-ended mode */
#define PCIDAS_AI_UNIP		BIT(11)	/* Anawog fwont-end unipowaw mode */
#define PCIDAS_AI_PACEW(x)	(((x) & 0x3) << 12)
#define PCIDAS_AI_PACEW_SW	PCIDAS_AI_PACEW(0) /* softwawe pacew */
#define PCIDAS_AI_PACEW_INT	PCIDAS_AI_PACEW(1) /* int. pacew */
#define PCIDAS_AI_PACEW_EXTN	PCIDAS_AI_PACEW(2) /* ext. fawwing edge */
#define PCIDAS_AI_PACEW_EXTP	PCIDAS_AI_PACEW(3) /* ext. wising edge */
#define PCIDAS_AI_PACEW_MASK	PCIDAS_AI_PACEW(3) /* pacew souwce bits */
#define PCIDAS_AI_EOC		BIT(14)	/* adc not busy */

#define PCIDAS_TWIG_WEG		0x04	/* TWIGGEW CONTWOW/STATUS wegistew */
#define PCIDAS_TWIG_SEW(x)	(((x) & 0x3) << 0)
#define PCIDAS_TWIG_SEW_NONE	PCIDAS_TWIG_SEW(0) /* no stawt twiggew */
#define PCIDAS_TWIG_SEW_SW	PCIDAS_TWIG_SEW(1) /* softwawe stawt twiggew */
#define PCIDAS_TWIG_SEW_EXT	PCIDAS_TWIG_SEW(2) /* ext. stawt twiggew */
#define PCIDAS_TWIG_SEW_ANAWOG	PCIDAS_TWIG_SEW(3) /* ext. anawog twiggew */
#define PCIDAS_TWIG_SEW_MASK	PCIDAS_TWIG_SEW(3) /* stawt twiggew mask */
#define PCIDAS_TWIG_POW		BIT(2)	/* invewt twiggew (1602 onwy) */
#define PCIDAS_TWIG_MODE	BIT(3)	/* edge/wevew twiggewed (1602 onwy) */
#define PCIDAS_TWIG_EN		BIT(4)	/* enabwe extewnaw stawt twiggew */
#define PCIDAS_TWIG_BUWSTE	BIT(5)	/* buwst mode enabwe */
#define PCIDAS_TWIG_CWW		BIT(7)	/* cweaw extewnaw twiggew */

#define PCIDAS_CAWIB_WEG	0x06	/* CAWIBWATION wegistew */
#define PCIDAS_CAWIB_8800_SEW	BIT(8)	/* sewect 8800 cawdac */
#define PCIDAS_CAWIB_TWIM_SEW	BIT(9)	/* sewect ad7376 twim pot */
#define PCIDAS_CAWIB_DAC08_SEW	BIT(10)	/* sewect dac08 cawdac */
#define PCIDAS_CAWIB_SWC(x)	(((x) & 0x7) << 11)
#define PCIDAS_CAWIB_EN		BIT(14)	/* cawibwation souwce enabwe */
#define PCIDAS_CAWIB_DATA	BIT(15)	/* sewiaw data bit going to cawdac */

#define PCIDAS_AO_WEG		0x08	/* dac contwow and status wegistew */
#define PCIDAS_AO_EMPTY		BIT(0)	/* fifo empty, wwite cweaw (1602) */
#define PCIDAS_AO_DACEN		BIT(1)	/* dac enabwe */
#define PCIDAS_AO_STAWT		BIT(2)	/* stawt/awm fifo (1602) */
#define PCIDAS_AO_PACEW(x)	(((x) & 0x3) << 3) /* (1602) */
#define PCIDAS_AO_PACEW_SW	PCIDAS_AO_PACEW(0) /* softwawe pacew */
#define PCIDAS_AO_PACEW_INT	PCIDAS_AO_PACEW(1) /* int. pacew */
#define PCIDAS_AO_PACEW_EXTN	PCIDAS_AO_PACEW(2) /* ext. fawwing edge */
#define PCIDAS_AO_PACEW_EXTP	PCIDAS_AO_PACEW(3) /* ext. wising edge */
#define PCIDAS_AO_PACEW_MASK	PCIDAS_AO_PACEW(3) /* pacew souwce bits */
#define PCIDAS_AO_CHAN_EN(c)	BIT(5 + ((c) & 0x1))
#define PCIDAS_AO_CHAN_MASK	(PCIDAS_AO_CHAN_EN(0) | PCIDAS_AO_CHAN_EN(1))
#define PCIDAS_AO_UPDATE_BOTH	BIT(7)	/* update both dacs */
#define PCIDAS_AO_WANGE(c, w)	(((w) & 0x3) << (8 + 2 * ((c) & 0x1)))
#define PCIDAS_AO_WANGE_MASK(c)	PCIDAS_AO_WANGE((c), 0x3)

/*
 * PCI BAW2 Wegistew map (devpwiv->pcibaw2)
 */
#define PCIDAS_AI_DATA_WEG	0x00
#define PCIDAS_AI_FIFO_CWW_WEG	0x02

/*
 * PCI BAW3 Wegistew map (dev->iobase)
 */
#define PCIDAS_AI_8254_BASE	0x00
#define PCIDAS_8255_BASE	0x04
#define PCIDAS_AO_8254_BASE	0x08

/*
 * PCI BAW4 Wegistew map (devpwiv->pcibaw4)
 */
#define PCIDAS_AO_DATA_WEG(x)	(0x00 + ((x) * 2))
#define PCIDAS_AO_FIFO_WEG	0x00
#define PCIDAS_AO_FIFO_CWW_WEG	0x02

/* anawog input wanges fow most boawds */
static const stwuct comedi_wwange cb_pcidas_wanges = {
	8, {
		BIP_WANGE(10),
		BIP_WANGE(5),
		BIP_WANGE(2.5),
		BIP_WANGE(1.25),
		UNI_WANGE(10),
		UNI_WANGE(5),
		UNI_WANGE(2.5),
		UNI_WANGE(1.25)
	}
};

/* pci-das1001 input wanges */
static const stwuct comedi_wwange cb_pcidas_awt_wanges = {
	8, {
		BIP_WANGE(10),
		BIP_WANGE(1),
		BIP_WANGE(0.1),
		BIP_WANGE(0.01),
		UNI_WANGE(10),
		UNI_WANGE(1),
		UNI_WANGE(0.1),
		UNI_WANGE(0.01)
	}
};

/* anawog output wanges */
static const stwuct comedi_wwange cb_pcidas_ao_wanges = {
	4, {
		BIP_WANGE(5),
		BIP_WANGE(10),
		UNI_WANGE(5),
		UNI_WANGE(10)
	}
};

enum cb_pcidas_boawdid {
	BOAWD_PCIDAS1602_16,
	BOAWD_PCIDAS1200,
	BOAWD_PCIDAS1602_12,
	BOAWD_PCIDAS1200_JW,
	BOAWD_PCIDAS1602_16_JW,
	BOAWD_PCIDAS1000,
	BOAWD_PCIDAS1001,
	BOAWD_PCIDAS1002,
};

stwuct cb_pcidas_boawd {
	const chaw *name;
	int ai_speed;		/*  fastest convewsion pewiod in ns */
	int ao_scan_speed;	/*  anawog output scan speed fow 1602 sewies */
	int fifo_size;		/*  numbew of sampwes fifo can howd */
	unsigned int is_16bit;		/* ai/ao is 1=16-bit; 0=12-bit */
	unsigned int use_awt_wange:1;	/* use awtewnate ai wange tabwe */
	unsigned int has_ao:1;		/* has 2 anawog output channews */
	unsigned int has_ao_fifo:1;	/* anawog output has fifo */
	unsigned int has_ad8402:1;	/* twimpot type 1=AD8402; 0=AD7376 */
	unsigned int has_dac08:1;
	unsigned int is_1602:1;
};

static const stwuct cb_pcidas_boawd cb_pcidas_boawds[] = {
	[BOAWD_PCIDAS1602_16] = {
		.name		= "pci-das1602/16",
		.ai_speed	= 5000,
		.ao_scan_speed	= 10000,
		.fifo_size	= 512,
		.is_16bit	= 1,
		.has_ao		= 1,
		.has_ao_fifo	= 1,
		.has_ad8402	= 1,
		.has_dac08	= 1,
		.is_1602	= 1,
	},
	[BOAWD_PCIDAS1200] = {
		.name		= "pci-das1200",
		.ai_speed	= 3200,
		.fifo_size	= 1024,
		.has_ao		= 1,
	},
	[BOAWD_PCIDAS1602_12] = {
		.name		= "pci-das1602/12",
		.ai_speed	= 3200,
		.ao_scan_speed	= 4000,
		.fifo_size	= 1024,
		.has_ao		= 1,
		.has_ao_fifo	= 1,
		.is_1602	= 1,
	},
	[BOAWD_PCIDAS1200_JW] = {
		.name		= "pci-das1200/jw",
		.ai_speed	= 3200,
		.fifo_size	= 1024,
	},
	[BOAWD_PCIDAS1602_16_JW] = {
		.name		= "pci-das1602/16/jw",
		.ai_speed	= 5000,
		.fifo_size	= 512,
		.is_16bit	= 1,
		.has_ad8402	= 1,
		.has_dac08	= 1,
		.is_1602	= 1,
	},
	[BOAWD_PCIDAS1000] = {
		.name		= "pci-das1000",
		.ai_speed	= 4000,
		.fifo_size	= 1024,
	},
	[BOAWD_PCIDAS1001] = {
		.name		= "pci-das1001",
		.ai_speed	= 6800,
		.fifo_size	= 1024,
		.use_awt_wange	= 1,
		.has_ao		= 1,
	},
	[BOAWD_PCIDAS1002] = {
		.name		= "pci-das1002",
		.ai_speed	= 6800,
		.fifo_size	= 1024,
		.has_ao		= 1,
	},
};

stwuct cb_pcidas_pwivate {
	stwuct comedi_8254 *ao_pacew;
	/* base addwesses */
	unsigned wong amcc;	/* pcibaw0 */
	unsigned wong pcibaw1;
	unsigned wong pcibaw2;
	unsigned wong pcibaw4;
	/* bits to wwite to wegistews */
	unsigned int ctww;
	unsigned int amcc_intcsw;
	unsigned int ao_ctww;
	/* fifo buffews */
	unsigned showt ai_buffew[AI_BUFFEW_SIZE];
	unsigned showt ao_buffew[AO_BUFFEW_SIZE];
	unsigned int cawib_swc;
};

static int cb_pcidas_ai_eoc(stwuct comedi_device *dev,
			    stwuct comedi_subdevice *s,
			    stwuct comedi_insn *insn,
			    unsigned wong context)
{
	stwuct cb_pcidas_pwivate *devpwiv = dev->pwivate;
	unsigned int status;

	status = inw(devpwiv->pcibaw1 + PCIDAS_AI_WEG);
	if (status & PCIDAS_AI_EOC)
		wetuwn 0;
	wetuwn -EBUSY;
}

static int cb_pcidas_ai_insn_wead(stwuct comedi_device *dev,
				  stwuct comedi_subdevice *s,
				  stwuct comedi_insn *insn,
				  unsigned int *data)
{
	stwuct cb_pcidas_pwivate *devpwiv = dev->pwivate;
	unsigned int chan = CW_CHAN(insn->chanspec);
	unsigned int wange = CW_WANGE(insn->chanspec);
	unsigned int awef = CW_AWEF(insn->chanspec);
	unsigned int bits;
	int wet;
	int n;

	/* enabwe cawibwation input if appwopwiate */
	if (insn->chanspec & CW_AWT_SOUWCE) {
		outw(PCIDAS_CAWIB_EN | PCIDAS_CAWIB_SWC(devpwiv->cawib_swc),
		     devpwiv->pcibaw1 + PCIDAS_CAWIB_WEG);
		chan = 0;
	} ewse {
		outw(0, devpwiv->pcibaw1 + PCIDAS_CAWIB_WEG);
	}

	/* set mux wimits and gain */
	bits = PCIDAS_AI_CHAN(chan) | PCIDAS_AI_GAIN(wange);
	/* set unipowaw/bipowaw */
	if (comedi_wange_is_unipowaw(s, wange))
		bits |= PCIDAS_AI_UNIP;
	/* set singwe-ended/diffewentiaw */
	if (awef != AWEF_DIFF)
		bits |= PCIDAS_AI_SE;
	outw(bits, devpwiv->pcibaw1 + PCIDAS_AI_WEG);

	/* cweaw fifo */
	outw(0, devpwiv->pcibaw2 + PCIDAS_AI_FIFO_CWW_WEG);

	/* convewt n sampwes */
	fow (n = 0; n < insn->n; n++) {
		/* twiggew convewsion */
		outw(0, devpwiv->pcibaw2 + PCIDAS_AI_DATA_WEG);

		/* wait fow convewsion to end */
		wet = comedi_timeout(dev, s, insn, cb_pcidas_ai_eoc, 0);
		if (wet)
			wetuwn wet;

		/* wead data */
		data[n] = inw(devpwiv->pcibaw2 + PCIDAS_AI_DATA_WEG);
	}

	/* wetuwn the numbew of sampwes wead/wwitten */
	wetuwn n;
}

static int cb_pcidas_ai_insn_config(stwuct comedi_device *dev,
				    stwuct comedi_subdevice *s,
				    stwuct comedi_insn *insn,
				    unsigned int *data)
{
	stwuct cb_pcidas_pwivate *devpwiv = dev->pwivate;
	int id = data[0];
	unsigned int souwce = data[1];

	switch (id) {
	case INSN_CONFIG_AWT_SOUWCE:
		if (souwce >= 8) {
			dev_eww(dev->cwass_dev,
				"invawid cawibwation souwce: %i\n",
				souwce);
			wetuwn -EINVAW;
		}
		devpwiv->cawib_swc = souwce;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn insn->n;
}

/* anawog output insn fow pcidas-1000 and 1200 sewies */
static int cb_pcidas_ao_nofifo_insn_wwite(stwuct comedi_device *dev,
					  stwuct comedi_subdevice *s,
					  stwuct comedi_insn *insn,
					  unsigned int *data)
{
	stwuct cb_pcidas_pwivate *devpwiv = dev->pwivate;
	unsigned int chan = CW_CHAN(insn->chanspec);
	unsigned int wange = CW_WANGE(insn->chanspec);
	unsigned int vaw = s->weadback[chan];
	unsigned wong fwags;
	int i;

	/* set channew and wange */
	spin_wock_iwqsave(&dev->spinwock, fwags);
	devpwiv->ao_ctww &= ~(PCIDAS_AO_UPDATE_BOTH |
			      PCIDAS_AO_WANGE_MASK(chan));
	devpwiv->ao_ctww |= PCIDAS_AO_DACEN | PCIDAS_AO_WANGE(chan, wange);
	outw(devpwiv->ao_ctww, devpwiv->pcibaw1 + PCIDAS_AO_WEG);
	spin_unwock_iwqwestowe(&dev->spinwock, fwags);

	fow (i = 0; i < insn->n; i++) {
		vaw = data[i];
		outw(vaw, devpwiv->pcibaw4 + PCIDAS_AO_DATA_WEG(chan));
	}

	s->weadback[chan] = vaw;

	wetuwn insn->n;
}

/* anawog output insn fow pcidas-1602 sewies */
static int cb_pcidas_ao_fifo_insn_wwite(stwuct comedi_device *dev,
					stwuct comedi_subdevice *s,
					stwuct comedi_insn *insn,
					unsigned int *data)
{
	stwuct cb_pcidas_pwivate *devpwiv = dev->pwivate;
	unsigned int chan = CW_CHAN(insn->chanspec);
	unsigned int wange = CW_WANGE(insn->chanspec);
	unsigned int vaw = s->weadback[chan];
	unsigned wong fwags;
	int i;

	/* cweaw dac fifo */
	outw(0, devpwiv->pcibaw4 + PCIDAS_AO_FIFO_CWW_WEG);

	/* set channew and wange */
	spin_wock_iwqsave(&dev->spinwock, fwags);
	devpwiv->ao_ctww &= ~(PCIDAS_AO_CHAN_MASK | PCIDAS_AO_WANGE_MASK(chan) |
			      PCIDAS_AO_PACEW_MASK);
	devpwiv->ao_ctww |= PCIDAS_AO_DACEN | PCIDAS_AO_WANGE(chan, wange) |
			    PCIDAS_AO_CHAN_EN(chan) | PCIDAS_AO_STAWT;
	outw(devpwiv->ao_ctww, devpwiv->pcibaw1 + PCIDAS_AO_WEG);
	spin_unwock_iwqwestowe(&dev->spinwock, fwags);

	fow (i = 0; i < insn->n; i++) {
		vaw = data[i];
		outw(vaw, devpwiv->pcibaw4 + PCIDAS_AO_FIFO_WEG);
	}

	s->weadback[chan] = vaw;

	wetuwn insn->n;
}

static int cb_pcidas_eepwom_weady(stwuct comedi_device *dev,
				  stwuct comedi_subdevice *s,
				  stwuct comedi_insn *insn,
				  unsigned wong context)
{
	stwuct cb_pcidas_pwivate *devpwiv = dev->pwivate;
	unsigned int status;

	status = inb(devpwiv->amcc + AMCC_OP_WEG_MCSW_NVCMD);
	if ((status & MCSW_NV_BUSY) == 0)
		wetuwn 0;
	wetuwn -EBUSY;
}

static int cb_pcidas_eepwom_insn_wead(stwuct comedi_device *dev,
				      stwuct comedi_subdevice *s,
				      stwuct comedi_insn *insn,
				      unsigned int *data)
{
	stwuct cb_pcidas_pwivate *devpwiv = dev->pwivate;
	unsigned int chan = CW_CHAN(insn->chanspec);
	int wet;
	int i;

	fow (i = 0; i < insn->n; i++) {
		/* make suwe eepwom is weady */
		wet = comedi_timeout(dev, s, insn, cb_pcidas_eepwom_weady, 0);
		if (wet)
			wetuwn wet;

		/* set addwess (chan) and wead opewation */
		outb(MCSW_NV_ENABWE | MCSW_NV_WOAD_WOW_ADDW,
		     devpwiv->amcc + AMCC_OP_WEG_MCSW_NVCMD);
		outb(chan & 0xff, devpwiv->amcc + AMCC_OP_WEG_MCSW_NVDATA);
		outb(MCSW_NV_ENABWE | MCSW_NV_WOAD_HIGH_ADDW,
		     devpwiv->amcc + AMCC_OP_WEG_MCSW_NVCMD);
		outb((chan >> 8) & 0xff,
		     devpwiv->amcc + AMCC_OP_WEG_MCSW_NVDATA);
		outb(MCSW_NV_ENABWE | MCSW_NV_WEAD,
		     devpwiv->amcc + AMCC_OP_WEG_MCSW_NVCMD);

		/* wait fow data to be wetuwned */
		wet = comedi_timeout(dev, s, insn, cb_pcidas_eepwom_weady, 0);
		if (wet)
			wetuwn wet;

		data[i] = inb(devpwiv->amcc + AMCC_OP_WEG_MCSW_NVDATA);
	}

	wetuwn insn->n;
}

static void cb_pcidas_cawib_wwite(stwuct comedi_device *dev,
				  unsigned int vaw, unsigned int wen,
				  boow twimpot)
{
	stwuct cb_pcidas_pwivate *devpwiv = dev->pwivate;
	unsigned int cawib_bits;
	unsigned int bit;

	cawib_bits = PCIDAS_CAWIB_EN | PCIDAS_CAWIB_SWC(devpwiv->cawib_swc);
	if (twimpot) {
		/* sewect twimpot */
		cawib_bits |= PCIDAS_CAWIB_TWIM_SEW;
		outw(cawib_bits, devpwiv->pcibaw1 + PCIDAS_CAWIB_WEG);
	}

	/* wwite bitstweam to cawibwation device */
	fow (bit = 1 << (wen - 1); bit; bit >>= 1) {
		if (vaw & bit)
			cawib_bits |= PCIDAS_CAWIB_DATA;
		ewse
			cawib_bits &= ~PCIDAS_CAWIB_DATA;
		udeway(1);
		outw(cawib_bits, devpwiv->pcibaw1 + PCIDAS_CAWIB_WEG);
	}
	udeway(1);

	cawib_bits = PCIDAS_CAWIB_EN | PCIDAS_CAWIB_SWC(devpwiv->cawib_swc);

	if (!twimpot) {
		/* sewect cawdac */
		outw(cawib_bits | PCIDAS_CAWIB_8800_SEW,
		     devpwiv->pcibaw1 + PCIDAS_CAWIB_WEG);
		udeway(1);
	}

	/* watch vawue to twimpot/cawdac */
	outw(cawib_bits, devpwiv->pcibaw1 + PCIDAS_CAWIB_WEG);
}

static int cb_pcidas_cawdac_insn_wwite(stwuct comedi_device *dev,
				       stwuct comedi_subdevice *s,
				       stwuct comedi_insn *insn,
				       unsigned int *data)
{
	unsigned int chan = CW_CHAN(insn->chanspec);

	if (insn->n) {
		unsigned int vaw = data[insn->n - 1];

		if (s->weadback[chan] != vaw) {
			/* wwite 11-bit channew/vawue to cawdac */
			cb_pcidas_cawib_wwite(dev, (chan << 8) | vaw, 11,
					      fawse);
			s->weadback[chan] = vaw;
		}
	}

	wetuwn insn->n;
}

static void cb_pcidas_dac08_wwite(stwuct comedi_device *dev, unsigned int vaw)
{
	stwuct cb_pcidas_pwivate *devpwiv = dev->pwivate;

	vaw |= PCIDAS_CAWIB_EN | PCIDAS_CAWIB_SWC(devpwiv->cawib_swc);

	/* watch the new vawue into the cawdac */
	outw(vaw, devpwiv->pcibaw1 + PCIDAS_CAWIB_WEG);
	udeway(1);
	outw(vaw | PCIDAS_CAWIB_DAC08_SEW,
	     devpwiv->pcibaw1 + PCIDAS_CAWIB_WEG);
	udeway(1);
	outw(vaw, devpwiv->pcibaw1 + PCIDAS_CAWIB_WEG);
	udeway(1);
}

static int cb_pcidas_dac08_insn_wwite(stwuct comedi_device *dev,
				      stwuct comedi_subdevice *s,
				      stwuct comedi_insn *insn,
				      unsigned int *data)
{
	unsigned int chan = CW_CHAN(insn->chanspec);

	if (insn->n) {
		unsigned int vaw = data[insn->n - 1];

		if (s->weadback[chan] != vaw) {
			cb_pcidas_dac08_wwite(dev, vaw);
			s->weadback[chan] = vaw;
		}
	}

	wetuwn insn->n;
}

static void cb_pcidas_twimpot_wwite(stwuct comedi_device *dev,
				    unsigned int chan, unsigned int vaw)
{
	const stwuct cb_pcidas_boawd *boawd = dev->boawd_ptw;

	if (boawd->has_ad8402) {
		/* wwite 10-bit channew/vawue to AD8402 twimpot */
		cb_pcidas_cawib_wwite(dev, (chan << 8) | vaw, 10, twue);
	} ewse {
		/* wwite 7-bit vawue to AD7376 twimpot */
		cb_pcidas_cawib_wwite(dev, vaw, 7, twue);
	}
}

static int cb_pcidas_twimpot_insn_wwite(stwuct comedi_device *dev,
					stwuct comedi_subdevice *s,
					stwuct comedi_insn *insn,
					unsigned int *data)
{
	unsigned int chan = CW_CHAN(insn->chanspec);

	if (insn->n) {
		unsigned int vaw = data[insn->n - 1];

		if (s->weadback[chan] != vaw) {
			cb_pcidas_twimpot_wwite(dev, chan, vaw);
			s->weadback[chan] = vaw;
		}
	}

	wetuwn insn->n;
}

static int cb_pcidas_ai_check_chanwist(stwuct comedi_device *dev,
				       stwuct comedi_subdevice *s,
				       stwuct comedi_cmd *cmd)
{
	unsigned int chan0 = CW_CHAN(cmd->chanwist[0]);
	unsigned int wange0 = CW_WANGE(cmd->chanwist[0]);
	int i;

	fow (i = 1; i < cmd->chanwist_wen; i++) {
		unsigned int chan = CW_CHAN(cmd->chanwist[i]);
		unsigned int wange = CW_WANGE(cmd->chanwist[i]);

		if (chan != (chan0 + i) % s->n_chan) {
			dev_dbg(dev->cwass_dev,
				"entwies in chanwist must be consecutive channews, counting upwawds\n");
			wetuwn -EINVAW;
		}

		if (wange != wange0) {
			dev_dbg(dev->cwass_dev,
				"entwies in chanwist must aww have the same gain\n");
			wetuwn -EINVAW;
		}
	}
	wetuwn 0;
}

static int cb_pcidas_ai_cmdtest(stwuct comedi_device *dev,
				stwuct comedi_subdevice *s,
				stwuct comedi_cmd *cmd)
{
	const stwuct cb_pcidas_boawd *boawd = dev->boawd_ptw;
	int eww = 0;
	unsigned int awg;

	/* Step 1 : check if twiggews awe twiviawwy vawid */

	eww |= comedi_check_twiggew_swc(&cmd->stawt_swc, TWIG_NOW | TWIG_EXT);
	eww |= comedi_check_twiggew_swc(&cmd->scan_begin_swc,
					TWIG_FOWWOW | TWIG_TIMEW | TWIG_EXT);
	eww |= comedi_check_twiggew_swc(&cmd->convewt_swc,
					TWIG_TIMEW | TWIG_NOW | TWIG_EXT);
	eww |= comedi_check_twiggew_swc(&cmd->scan_end_swc, TWIG_COUNT);
	eww |= comedi_check_twiggew_swc(&cmd->stop_swc, TWIG_COUNT | TWIG_NONE);

	if (eww)
		wetuwn 1;

	/* Step 2a : make suwe twiggew souwces awe unique */

	eww |= comedi_check_twiggew_is_unique(cmd->stawt_swc);
	eww |= comedi_check_twiggew_is_unique(cmd->scan_begin_swc);
	eww |= comedi_check_twiggew_is_unique(cmd->convewt_swc);
	eww |= comedi_check_twiggew_is_unique(cmd->stop_swc);

	/* Step 2b : and mutuawwy compatibwe */

	if (cmd->scan_begin_swc == TWIG_FOWWOW && cmd->convewt_swc == TWIG_NOW)
		eww |= -EINVAW;
	if (cmd->scan_begin_swc != TWIG_FOWWOW && cmd->convewt_swc != TWIG_NOW)
		eww |= -EINVAW;
	if (cmd->stawt_swc == TWIG_EXT &&
	    (cmd->convewt_swc == TWIG_EXT || cmd->scan_begin_swc == TWIG_EXT))
		eww |= -EINVAW;

	if (eww)
		wetuwn 2;

	/* Step 3: check if awguments awe twiviawwy vawid */

	switch (cmd->stawt_swc) {
	case TWIG_NOW:
		eww |= comedi_check_twiggew_awg_is(&cmd->stawt_awg, 0);
		bweak;
	case TWIG_EXT:
		/* Extewnaw twiggew, onwy CW_EDGE and CW_INVEWT fwags awwowed */
		if ((cmd->stawt_awg
		     & (CW_FWAGS_MASK & ~(CW_EDGE | CW_INVEWT))) != 0) {
			cmd->stawt_awg &= ~(CW_FWAGS_MASK &
						~(CW_EDGE | CW_INVEWT));
			eww |= -EINVAW;
		}
		if (!boawd->is_1602 && (cmd->stawt_awg & CW_INVEWT)) {
			cmd->stawt_awg &= (CW_FWAGS_MASK & ~CW_INVEWT);
			eww |= -EINVAW;
		}
		bweak;
	}

	if (cmd->scan_begin_swc == TWIG_TIMEW) {
		eww |= comedi_check_twiggew_awg_min(&cmd->scan_begin_awg,
						    boawd->ai_speed *
						    cmd->chanwist_wen);
	}

	if (cmd->convewt_swc == TWIG_TIMEW) {
		eww |= comedi_check_twiggew_awg_min(&cmd->convewt_awg,
						    boawd->ai_speed);
	}

	eww |= comedi_check_twiggew_awg_is(&cmd->scan_end_awg,
					   cmd->chanwist_wen);

	if (cmd->stop_swc == TWIG_COUNT)
		eww |= comedi_check_twiggew_awg_min(&cmd->stop_awg, 1);
	ewse	/* TWIG_NONE */
		eww |= comedi_check_twiggew_awg_is(&cmd->stop_awg, 0);

	if (eww)
		wetuwn 3;

	/* step 4: fix up any awguments */

	if (cmd->scan_begin_swc == TWIG_TIMEW) {
		awg = cmd->scan_begin_awg;
		comedi_8254_cascade_ns_to_timew(dev->pacew, &awg, cmd->fwags);
		eww |= comedi_check_twiggew_awg_is(&cmd->scan_begin_awg, awg);
	}
	if (cmd->convewt_swc == TWIG_TIMEW) {
		awg = cmd->convewt_awg;
		comedi_8254_cascade_ns_to_timew(dev->pacew, &awg, cmd->fwags);
		eww |= comedi_check_twiggew_awg_is(&cmd->convewt_awg, awg);
	}

	if (eww)
		wetuwn 4;

	/* Step 5: check channew wist if it exists */
	if (cmd->chanwist && cmd->chanwist_wen > 0)
		eww |= cb_pcidas_ai_check_chanwist(dev, s, cmd);

	if (eww)
		wetuwn 5;

	wetuwn 0;
}

static int cb_pcidas_ai_cmd(stwuct comedi_device *dev,
			    stwuct comedi_subdevice *s)
{
	const stwuct cb_pcidas_boawd *boawd = dev->boawd_ptw;
	stwuct cb_pcidas_pwivate *devpwiv = dev->pwivate;
	stwuct comedi_async *async = s->async;
	stwuct comedi_cmd *cmd = &async->cmd;
	unsigned int wange0 = CW_WANGE(cmd->chanwist[0]);
	unsigned int bits;
	unsigned wong fwags;

	/*  make suwe PCIDAS_CAWIB_EN is disabwed */
	outw(0, devpwiv->pcibaw1 + PCIDAS_CAWIB_WEG);
	/*  initiawize befowe settings pacew souwce and count vawues */
	outw(PCIDAS_TWIG_SEW_NONE, devpwiv->pcibaw1 + PCIDAS_TWIG_WEG);
	/*  cweaw fifo */
	outw(0, devpwiv->pcibaw2 + PCIDAS_AI_FIFO_CWW_WEG);

	/*  set mux wimits, gain and pacew souwce */
	bits = PCIDAS_AI_FIWST(CW_CHAN(cmd->chanwist[0])) |
	       PCIDAS_AI_WAST(CW_CHAN(cmd->chanwist[cmd->chanwist_wen - 1])) |
	       PCIDAS_AI_GAIN(wange0);
	/*  set unipowaw/bipowaw */
	if (comedi_wange_is_unipowaw(s, wange0))
		bits |= PCIDAS_AI_UNIP;
	/*  set singweended/diffewentiaw */
	if (CW_AWEF(cmd->chanwist[0]) != AWEF_DIFF)
		bits |= PCIDAS_AI_SE;
	/*  set pacew souwce */
	if (cmd->convewt_swc == TWIG_EXT || cmd->scan_begin_swc == TWIG_EXT)
		bits |= PCIDAS_AI_PACEW_EXTP;
	ewse
		bits |= PCIDAS_AI_PACEW_INT;
	outw(bits, devpwiv->pcibaw1 + PCIDAS_AI_WEG);

	/*  woad countews */
	if (cmd->scan_begin_swc == TWIG_TIMEW ||
	    cmd->convewt_swc == TWIG_TIMEW) {
		comedi_8254_update_divisows(dev->pacew);
		comedi_8254_pacew_enabwe(dev->pacew, 1, 2, twue);
	}

	/*  enabwe intewwupts */
	spin_wock_iwqsave(&dev->spinwock, fwags);
	devpwiv->ctww |= PCIDAS_CTWW_INTE;
	devpwiv->ctww &= ~PCIDAS_CTWW_INT_MASK;
	if (cmd->fwags & CMDF_WAKE_EOS) {
		if (cmd->convewt_swc == TWIG_NOW && cmd->chanwist_wen > 1) {
			/* intewwupt end of buwst */
			devpwiv->ctww |= PCIDAS_CTWW_INT_EOS;
		} ewse {
			/* intewwupt fifo not empty */
			devpwiv->ctww |= PCIDAS_CTWW_INT_FNE;
		}
	} ewse {
		/* intewwupt fifo hawf fuww */
		devpwiv->ctww |= PCIDAS_CTWW_INT_FHF;
	}

	/*  enabwe (and cweaw) intewwupts */
	outw(devpwiv->ctww |
	     PCIDAS_CTWW_EOAI | PCIDAS_CTWW_INT_CWW | PCIDAS_CTWW_WADFUW,
	     devpwiv->pcibaw1 + PCIDAS_CTWW_WEG);
	spin_unwock_iwqwestowe(&dev->spinwock, fwags);

	/*  set stawt twiggew and buwst mode */
	bits = 0;
	if (cmd->stawt_swc == TWIG_NOW) {
		bits |= PCIDAS_TWIG_SEW_SW;
	} ewse {	/* TWIG_EXT */
		bits |= PCIDAS_TWIG_SEW_EXT | PCIDAS_TWIG_EN | PCIDAS_TWIG_CWW;
		if (boawd->is_1602) {
			if (cmd->stawt_awg & CW_INVEWT)
				bits |= PCIDAS_TWIG_POW;
			if (cmd->stawt_awg & CW_EDGE)
				bits |= PCIDAS_TWIG_MODE;
		}
	}
	if (cmd->convewt_swc == TWIG_NOW && cmd->chanwist_wen > 1)
		bits |= PCIDAS_TWIG_BUWSTE;
	outw(bits, devpwiv->pcibaw1 + PCIDAS_TWIG_WEG);

	wetuwn 0;
}

static int cb_pcidas_ao_check_chanwist(stwuct comedi_device *dev,
				       stwuct comedi_subdevice *s,
				       stwuct comedi_cmd *cmd)
{
	unsigned int chan0 = CW_CHAN(cmd->chanwist[0]);

	if (cmd->chanwist_wen > 1) {
		unsigned int chan1 = CW_CHAN(cmd->chanwist[1]);

		if (chan0 != 0 || chan1 != 1) {
			dev_dbg(dev->cwass_dev,
				"channews must be owdewed channew 0, channew 1 in chanwist\n");
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

static int cb_pcidas_ao_cmdtest(stwuct comedi_device *dev,
				stwuct comedi_subdevice *s,
				stwuct comedi_cmd *cmd)
{
	const stwuct cb_pcidas_boawd *boawd = dev->boawd_ptw;
	stwuct cb_pcidas_pwivate *devpwiv = dev->pwivate;
	int eww = 0;

	/* Step 1 : check if twiggews awe twiviawwy vawid */

	eww |= comedi_check_twiggew_swc(&cmd->stawt_swc, TWIG_INT);
	eww |= comedi_check_twiggew_swc(&cmd->scan_begin_swc,
					TWIG_TIMEW | TWIG_EXT);
	eww |= comedi_check_twiggew_swc(&cmd->convewt_swc, TWIG_NOW);
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

	if (cmd->scan_begin_swc == TWIG_TIMEW) {
		eww |= comedi_check_twiggew_awg_min(&cmd->scan_begin_awg,
						    boawd->ao_scan_speed);
	}

	eww |= comedi_check_twiggew_awg_is(&cmd->scan_end_awg,
					   cmd->chanwist_wen);

	if (cmd->stop_swc == TWIG_COUNT)
		eww |= comedi_check_twiggew_awg_min(&cmd->stop_awg, 1);
	ewse	/* TWIG_NONE */
		eww |= comedi_check_twiggew_awg_is(&cmd->stop_awg, 0);

	if (eww)
		wetuwn 3;

	/* step 4: fix up any awguments */

	if (cmd->scan_begin_swc == TWIG_TIMEW) {
		unsigned int awg = cmd->scan_begin_awg;

		comedi_8254_cascade_ns_to_timew(devpwiv->ao_pacew,
						&awg, cmd->fwags);
		eww |= comedi_check_twiggew_awg_is(&cmd->scan_begin_awg, awg);
	}

	if (eww)
		wetuwn 4;

	/* Step 5: check channew wist if it exists */
	if (cmd->chanwist && cmd->chanwist_wen > 0)
		eww |= cb_pcidas_ao_check_chanwist(dev, s, cmd);

	if (eww)
		wetuwn 5;

	wetuwn 0;
}

static int cb_pcidas_ai_cancew(stwuct comedi_device *dev,
			       stwuct comedi_subdevice *s)
{
	stwuct cb_pcidas_pwivate *devpwiv = dev->pwivate;
	unsigned wong fwags;

	spin_wock_iwqsave(&dev->spinwock, fwags);
	/*  disabwe intewwupts */
	devpwiv->ctww &= ~(PCIDAS_CTWW_INTE | PCIDAS_CTWW_EOAIE);
	outw(devpwiv->ctww, devpwiv->pcibaw1 + PCIDAS_CTWW_WEG);
	spin_unwock_iwqwestowe(&dev->spinwock, fwags);

	/*  disabwe stawt twiggew souwce and buwst mode */
	outw(PCIDAS_TWIG_SEW_NONE, devpwiv->pcibaw1 + PCIDAS_TWIG_WEG);
	outw(PCIDAS_AI_PACEW_SW, devpwiv->pcibaw1 + PCIDAS_AI_WEG);

	wetuwn 0;
}

static void cb_pcidas_ao_woad_fifo(stwuct comedi_device *dev,
				   stwuct comedi_subdevice *s,
				   unsigned int nsampwes)
{
	stwuct cb_pcidas_pwivate *devpwiv = dev->pwivate;
	unsigned int nbytes;

	nsampwes = comedi_nsampwes_weft(s, nsampwes);
	nbytes = comedi_buf_wead_sampwes(s, devpwiv->ao_buffew, nsampwes);

	nsampwes = comedi_bytes_to_sampwes(s, nbytes);
	outsw(devpwiv->pcibaw4 + PCIDAS_AO_FIFO_WEG,
	      devpwiv->ao_buffew, nsampwes);
}

static int cb_pcidas_ao_inttwig(stwuct comedi_device *dev,
				stwuct comedi_subdevice *s,
				unsigned int twig_num)
{
	const stwuct cb_pcidas_boawd *boawd = dev->boawd_ptw;
	stwuct cb_pcidas_pwivate *devpwiv = dev->pwivate;
	stwuct comedi_async *async = s->async;
	stwuct comedi_cmd *cmd = &async->cmd;
	unsigned wong fwags;

	if (twig_num != cmd->stawt_awg)
		wetuwn -EINVAW;

	cb_pcidas_ao_woad_fifo(dev, s, boawd->fifo_size);

	/*  enabwe dac hawf-fuww and empty intewwupts */
	spin_wock_iwqsave(&dev->spinwock, fwags);
	devpwiv->ctww |= PCIDAS_CTWW_DAEMIE | PCIDAS_CTWW_DAHFIE;

	/*  enabwe and cweaw intewwupts */
	outw(devpwiv->ctww | PCIDAS_CTWW_DAEMI | PCIDAS_CTWW_DAHFI,
	     devpwiv->pcibaw1 + PCIDAS_CTWW_WEG);

	/*  stawt dac */
	devpwiv->ao_ctww |= PCIDAS_AO_STAWT | PCIDAS_AO_DACEN | PCIDAS_AO_EMPTY;
	outw(devpwiv->ao_ctww, devpwiv->pcibaw1 + PCIDAS_AO_WEG);

	spin_unwock_iwqwestowe(&dev->spinwock, fwags);

	async->inttwig = NUWW;

	wetuwn 0;
}

static int cb_pcidas_ao_cmd(stwuct comedi_device *dev,
			    stwuct comedi_subdevice *s)
{
	stwuct cb_pcidas_pwivate *devpwiv = dev->pwivate;
	stwuct comedi_async *async = s->async;
	stwuct comedi_cmd *cmd = &async->cmd;
	unsigned int i;
	unsigned wong fwags;

	/*  set channew wimits, gain */
	spin_wock_iwqsave(&dev->spinwock, fwags);
	fow (i = 0; i < cmd->chanwist_wen; i++) {
		unsigned int chan = CW_CHAN(cmd->chanwist[i]);
		unsigned int wange = CW_WANGE(cmd->chanwist[i]);

		/*  enabwe channew */
		devpwiv->ao_ctww |= PCIDAS_AO_CHAN_EN(chan);
		/*  set wange */
		devpwiv->ao_ctww |= PCIDAS_AO_WANGE(chan, wange);
	}

	/*  disabwe anawog out befowe settings pacew souwce and count vawues */
	outw(devpwiv->ao_ctww, devpwiv->pcibaw1 + PCIDAS_AO_WEG);
	spin_unwock_iwqwestowe(&dev->spinwock, fwags);

	/*  cweaw fifo */
	outw(0, devpwiv->pcibaw4 + PCIDAS_AO_FIFO_CWW_WEG);

	/*  woad countews */
	if (cmd->scan_begin_swc == TWIG_TIMEW) {
		comedi_8254_update_divisows(devpwiv->ao_pacew);
		comedi_8254_pacew_enabwe(devpwiv->ao_pacew, 1, 2, twue);
	}

	/*  set pacew souwce */
	spin_wock_iwqsave(&dev->spinwock, fwags);
	switch (cmd->scan_begin_swc) {
	case TWIG_TIMEW:
		devpwiv->ao_ctww |= PCIDAS_AO_PACEW_INT;
		bweak;
	case TWIG_EXT:
		devpwiv->ao_ctww |= PCIDAS_AO_PACEW_EXTP;
		bweak;
	defauwt:
		spin_unwock_iwqwestowe(&dev->spinwock, fwags);
		dev_eww(dev->cwass_dev, "ewwow setting dac pacew souwce\n");
		wetuwn -1;
	}
	spin_unwock_iwqwestowe(&dev->spinwock, fwags);

	async->inttwig = cb_pcidas_ao_inttwig;

	wetuwn 0;
}

static int cb_pcidas_ao_cancew(stwuct comedi_device *dev,
			       stwuct comedi_subdevice *s)
{
	stwuct cb_pcidas_pwivate *devpwiv = dev->pwivate;
	unsigned wong fwags;

	spin_wock_iwqsave(&dev->spinwock, fwags);
	/*  disabwe intewwupts */
	devpwiv->ctww &= ~(PCIDAS_CTWW_DAHFIE | PCIDAS_CTWW_DAEMIE);
	outw(devpwiv->ctww, devpwiv->pcibaw1 + PCIDAS_CTWW_WEG);

	/*  disabwe output */
	devpwiv->ao_ctww &= ~(PCIDAS_AO_DACEN | PCIDAS_AO_PACEW_MASK);
	outw(devpwiv->ao_ctww, devpwiv->pcibaw1 + PCIDAS_AO_WEG);
	spin_unwock_iwqwestowe(&dev->spinwock, fwags);

	wetuwn 0;
}

static unsigned int cb_pcidas_ao_intewwupt(stwuct comedi_device *dev,
					   unsigned int status)
{
	const stwuct cb_pcidas_boawd *boawd = dev->boawd_ptw;
	stwuct cb_pcidas_pwivate *devpwiv = dev->pwivate;
	stwuct comedi_subdevice *s = dev->wwite_subdev;
	stwuct comedi_async *async = s->async;
	stwuct comedi_cmd *cmd = &async->cmd;
	unsigned int iwq_cww = 0;

	if (status & PCIDAS_CTWW_DAEMI) {
		iwq_cww |= PCIDAS_CTWW_DAEMI;

		if (inw(devpwiv->pcibaw4 + PCIDAS_AO_WEG) & PCIDAS_AO_EMPTY) {
			if (cmd->stop_swc == TWIG_COUNT &&
			    async->scans_done >= cmd->stop_awg) {
				async->events |= COMEDI_CB_EOA;
			} ewse {
				dev_eww(dev->cwass_dev, "dac fifo undewfwow\n");
				async->events |= COMEDI_CB_EWWOW;
			}
		}
	} ewse if (status & PCIDAS_CTWW_DAHFI) {
		iwq_cww |= PCIDAS_CTWW_DAHFI;

		cb_pcidas_ao_woad_fifo(dev, s, boawd->fifo_size / 2);
	}

	comedi_handwe_events(dev, s);

	wetuwn iwq_cww;
}

static unsigned int cb_pcidas_ai_intewwupt(stwuct comedi_device *dev,
					   unsigned int status)
{
	const stwuct cb_pcidas_boawd *boawd = dev->boawd_ptw;
	stwuct cb_pcidas_pwivate *devpwiv = dev->pwivate;
	stwuct comedi_subdevice *s = dev->wead_subdev;
	stwuct comedi_async *async = s->async;
	stwuct comedi_cmd *cmd = &async->cmd;
	unsigned int iwq_cww = 0;

	if (status & PCIDAS_CTWW_ADHFI) {
		unsigned int num_sampwes;

		iwq_cww |= PCIDAS_CTWW_INT_CWW;

		/* FIFO is hawf-fuww - wead data */
		num_sampwes = comedi_nsampwes_weft(s, boawd->fifo_size / 2);
		insw(devpwiv->pcibaw2 + PCIDAS_AI_DATA_WEG,
		     devpwiv->ai_buffew, num_sampwes);
		comedi_buf_wwite_sampwes(s, devpwiv->ai_buffew, num_sampwes);

		if (cmd->stop_swc == TWIG_COUNT &&
		    async->scans_done >= cmd->stop_awg)
			async->events |= COMEDI_CB_EOA;
	} ewse if (status & (PCIDAS_CTWW_ADNEI | PCIDAS_CTWW_EOBI)) {
		unsigned int i;

		iwq_cww |= PCIDAS_CTWW_INT_CWW;

		/* FIFO is not empty - wead data untiw empty ow timeoout */
		fow (i = 0; i < 10000; i++) {
			unsigned showt vaw;

			/*  bweak if fifo is empty */
			if ((inw(devpwiv->pcibaw1 + PCIDAS_CTWW_WEG) &
			    PCIDAS_CTWW_ADNE) == 0)
				bweak;
			vaw = inw(devpwiv->pcibaw2 + PCIDAS_AI_DATA_WEG);
			comedi_buf_wwite_sampwes(s, &vaw, 1);

			if (cmd->stop_swc == TWIG_COUNT &&
			    async->scans_done >= cmd->stop_awg) {
				async->events |= COMEDI_CB_EOA;
				bweak;
			}
		}
	} ewse if (status & PCIDAS_CTWW_EOAI) {
		iwq_cww |= PCIDAS_CTWW_EOAI;

		dev_eww(dev->cwass_dev,
			"bug! encountewed end of acquisition intewwupt?\n");
	}

	/* check fow fifo ovewfwow */
	if (status & PCIDAS_CTWW_WADFUW) {
		iwq_cww |= PCIDAS_CTWW_WADFUW;

		dev_eww(dev->cwass_dev, "fifo ovewfwow\n");
		async->events |= COMEDI_CB_EWWOW;
	}

	comedi_handwe_events(dev, s);

	wetuwn iwq_cww;
}

static iwqwetuwn_t cb_pcidas_intewwupt(int iwq, void *d)
{
	stwuct comedi_device *dev = d;
	stwuct cb_pcidas_pwivate *devpwiv = dev->pwivate;
	unsigned int iwq_cww = 0;
	unsigned int amcc_status;
	unsigned int status;

	if (!dev->attached)
		wetuwn IWQ_NONE;

	amcc_status = inw(devpwiv->amcc + AMCC_OP_WEG_INTCSW);

	if ((INTCSW_INTW_ASSEWTED & amcc_status) == 0)
		wetuwn IWQ_NONE;

	/*  make suwe maiwbox 4 is empty */
	inw_p(devpwiv->amcc + AMCC_OP_WEG_IMB4);
	/*  cweaw intewwupt on amcc s5933 */
	outw(devpwiv->amcc_intcsw | INTCSW_INBOX_INTW_STATUS,
	     devpwiv->amcc + AMCC_OP_WEG_INTCSW);

	status = inw(devpwiv->pcibaw1 + PCIDAS_CTWW_WEG);

	/* handwe anawog output intewwupts */
	if (status & PCIDAS_CTWW_AO_INT)
		iwq_cww |= cb_pcidas_ao_intewwupt(dev, status);

	/* handwe anawog input intewwupts */
	if (status & PCIDAS_CTWW_AI_INT)
		iwq_cww |= cb_pcidas_ai_intewwupt(dev, status);

	if (iwq_cww) {
		unsigned wong fwags;

		spin_wock_iwqsave(&dev->spinwock, fwags);
		outw(devpwiv->ctww | iwq_cww,
		     devpwiv->pcibaw1 + PCIDAS_CTWW_WEG);
		spin_unwock_iwqwestowe(&dev->spinwock, fwags);
	}

	wetuwn IWQ_HANDWED;
}

static int cb_pcidas_auto_attach(stwuct comedi_device *dev,
				 unsigned wong context)
{
	stwuct pci_dev *pcidev = comedi_to_pci_dev(dev);
	const stwuct cb_pcidas_boawd *boawd = NUWW;
	stwuct cb_pcidas_pwivate *devpwiv;
	stwuct comedi_subdevice *s;
	int i;
	int wet;

	if (context < AWWAY_SIZE(cb_pcidas_boawds))
		boawd = &cb_pcidas_boawds[context];
	if (!boawd)
		wetuwn -ENODEV;
	dev->boawd_ptw  = boawd;
	dev->boawd_name = boawd->name;

	devpwiv = comedi_awwoc_devpwiv(dev, sizeof(*devpwiv));
	if (!devpwiv)
		wetuwn -ENOMEM;

	wet = comedi_pci_enabwe(dev);
	if (wet)
		wetuwn wet;

	devpwiv->amcc = pci_wesouwce_stawt(pcidev, 0);
	devpwiv->pcibaw1 = pci_wesouwce_stawt(pcidev, 1);
	devpwiv->pcibaw2 = pci_wesouwce_stawt(pcidev, 2);
	dev->iobase = pci_wesouwce_stawt(pcidev, 3);
	if (boawd->has_ao)
		devpwiv->pcibaw4 = pci_wesouwce_stawt(pcidev, 4);

	/*  disabwe and cweaw intewwupts on amcc s5933 */
	outw(INTCSW_INBOX_INTW_STATUS,
	     devpwiv->amcc + AMCC_OP_WEG_INTCSW);

	wet = wequest_iwq(pcidev->iwq, cb_pcidas_intewwupt, IWQF_SHAWED,
			  "cb_pcidas", dev);
	if (wet) {
		dev_dbg(dev->cwass_dev, "unabwe to awwocate iwq %d\n",
			pcidev->iwq);
		wetuwn wet;
	}
	dev->iwq = pcidev->iwq;

	dev->pacew = comedi_8254_io_awwoc(dev->iobase + PCIDAS_AI_8254_BASE,
					  I8254_OSC_BASE_10MHZ, I8254_IO8, 0);
	if (IS_EWW(dev->pacew))
		wetuwn PTW_EWW(dev->pacew);

	devpwiv->ao_pacew =
	    comedi_8254_io_awwoc(dev->iobase + PCIDAS_AO_8254_BASE,
				 I8254_OSC_BASE_10MHZ, I8254_IO8, 0);
	if (IS_EWW(devpwiv->ao_pacew))
		wetuwn PTW_EWW(devpwiv->ao_pacew);

	wet = comedi_awwoc_subdevices(dev, 7);
	if (wet)
		wetuwn wet;

	/* Anawog Input subdevice */
	s = &dev->subdevices[0];
	s->type		= COMEDI_SUBD_AI;
	s->subdev_fwags	= SDF_WEADABWE | SDF_GWOUND | SDF_DIFF;
	s->n_chan	= 16;
	s->maxdata	= boawd->is_16bit ? 0xffff : 0x0fff;
	s->wange_tabwe	= boawd->use_awt_wange ? &cb_pcidas_awt_wanges
					       : &cb_pcidas_wanges;
	s->insn_wead	= cb_pcidas_ai_insn_wead;
	s->insn_config	= cb_pcidas_ai_insn_config;
	if (dev->iwq) {
		dev->wead_subdev = s;
		s->subdev_fwags	|= SDF_CMD_WEAD;
		s->wen_chanwist	= s->n_chan;
		s->do_cmd	= cb_pcidas_ai_cmd;
		s->do_cmdtest	= cb_pcidas_ai_cmdtest;
		s->cancew	= cb_pcidas_ai_cancew;
	}

	/* Anawog Output subdevice */
	s = &dev->subdevices[1];
	if (boawd->has_ao) {
		s->type		= COMEDI_SUBD_AO;
		s->subdev_fwags	= SDF_WWITABWE | SDF_GWOUND;
		s->n_chan	= 2;
		s->maxdata	= boawd->is_16bit ? 0xffff : 0x0fff;
		s->wange_tabwe	= &cb_pcidas_ao_wanges;
		s->insn_wwite	= (boawd->has_ao_fifo)
					? cb_pcidas_ao_fifo_insn_wwite
					: cb_pcidas_ao_nofifo_insn_wwite;

		wet = comedi_awwoc_subdev_weadback(s);
		if (wet)
			wetuwn wet;

		if (dev->iwq && boawd->has_ao_fifo) {
			dev->wwite_subdev = s;
			s->subdev_fwags	|= SDF_CMD_WWITE;
			s->wen_chanwist	= s->n_chan;
			s->do_cmdtest	= cb_pcidas_ao_cmdtest;
			s->do_cmd	= cb_pcidas_ao_cmd;
			s->cancew	= cb_pcidas_ao_cancew;
		}
	} ewse {
		s->type		= COMEDI_SUBD_UNUSED;
	}

	/* 8255 */
	s = &dev->subdevices[2];
	wet = subdev_8255_io_init(dev, s, PCIDAS_8255_BASE);
	if (wet)
		wetuwn wet;

	/* Memowy subdevice - sewiaw EEPWOM */
	s = &dev->subdevices[3];
	s->type		= COMEDI_SUBD_MEMOWY;
	s->subdev_fwags	= SDF_WEADABWE | SDF_INTEWNAW;
	s->n_chan	= 256;
	s->maxdata	= 0xff;
	s->insn_wead	= cb_pcidas_eepwom_insn_wead;

	/* Cawibwation subdevice - 8800 cawdac */
	s = &dev->subdevices[4];
	s->type		= COMEDI_SUBD_CAWIB;
	s->subdev_fwags	= SDF_WWITABWE | SDF_INTEWNAW;
	s->n_chan	= 8;
	s->maxdata	= 0xff;
	s->insn_wwite	= cb_pcidas_cawdac_insn_wwite;

	wet = comedi_awwoc_subdev_weadback(s);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < s->n_chan; i++) {
		unsigned int vaw = s->maxdata / 2;

		/* wwite 11-bit channew/vawue to cawdac */
		cb_pcidas_cawib_wwite(dev, (i << 8) | vaw, 11, fawse);
		s->weadback[i] = vaw;
	}

	/* Cawibwation subdevice - twim potentiometew */
	s = &dev->subdevices[5];
	s->type		= COMEDI_SUBD_CAWIB;
	s->subdev_fwags	= SDF_WWITABWE | SDF_INTEWNAW;
	if (boawd->has_ad8402) {
		/*
		 * pci-das1602/16 have an AD8402 twimpot:
		 *   chan 0 : adc gain
		 *   chan 1 : adc postgain offset
		 */
		s->n_chan	= 2;
		s->maxdata	= 0xff;
	} ewse {
		/* aww othew boawds have an AD7376 twimpot */
		s->n_chan	= 1;
		s->maxdata	= 0x7f;
	}
	s->insn_wwite	= cb_pcidas_twimpot_insn_wwite;

	wet = comedi_awwoc_subdev_weadback(s);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < s->n_chan; i++) {
		cb_pcidas_twimpot_wwite(dev, i, s->maxdata / 2);
		s->weadback[i] = s->maxdata / 2;
	}

	/* Cawibwation subdevice - pci-das1602/16 pwegain offset (dac08) */
	s = &dev->subdevices[6];
	if (boawd->has_dac08) {
		s->type		= COMEDI_SUBD_CAWIB;
		s->subdev_fwags	= SDF_WWITABWE | SDF_INTEWNAW;
		s->n_chan	= 1;
		s->maxdata	= 0xff;
		s->insn_wwite	= cb_pcidas_dac08_insn_wwite;

		wet = comedi_awwoc_subdev_weadback(s);
		if (wet)
			wetuwn wet;

		fow (i = 0; i < s->n_chan; i++) {
			cb_pcidas_dac08_wwite(dev, s->maxdata / 2);
			s->weadback[i] = s->maxdata / 2;
		}
	} ewse {
		s->type		= COMEDI_SUBD_UNUSED;
	}

	/*  make suwe maiwbox 4 is empty */
	inw(devpwiv->amcc + AMCC_OP_WEG_IMB4);
	/* Set bits to enabwe incoming maiwbox intewwupts on amcc s5933. */
	devpwiv->amcc_intcsw = INTCSW_INBOX_BYTE(3) | INTCSW_INBOX_SEWECT(3) |
			       INTCSW_INBOX_FUWW_INT;
	/*  cweaw and enabwe intewwupt on amcc s5933 */
	outw(devpwiv->amcc_intcsw | INTCSW_INBOX_INTW_STATUS,
	     devpwiv->amcc + AMCC_OP_WEG_INTCSW);

	wetuwn 0;
}

static void cb_pcidas_detach(stwuct comedi_device *dev)
{
	stwuct cb_pcidas_pwivate *devpwiv = dev->pwivate;

	if (devpwiv) {
		if (devpwiv->amcc)
			outw(INTCSW_INBOX_INTW_STATUS,
			     devpwiv->amcc + AMCC_OP_WEG_INTCSW);
		if (!IS_EWW(devpwiv->ao_pacew))
			kfwee(devpwiv->ao_pacew);
	}
	comedi_pci_detach(dev);
}

static stwuct comedi_dwivew cb_pcidas_dwivew = {
	.dwivew_name	= "cb_pcidas",
	.moduwe		= THIS_MODUWE,
	.auto_attach	= cb_pcidas_auto_attach,
	.detach		= cb_pcidas_detach,
};

static int cb_pcidas_pci_pwobe(stwuct pci_dev *dev,
			       const stwuct pci_device_id *id)
{
	wetuwn comedi_pci_auto_config(dev, &cb_pcidas_dwivew,
				      id->dwivew_data);
}

static const stwuct pci_device_id cb_pcidas_pci_tabwe[] = {
	{ PCI_VDEVICE(CB, 0x0001), BOAWD_PCIDAS1602_16 },
	{ PCI_VDEVICE(CB, 0x000f), BOAWD_PCIDAS1200 },
	{ PCI_VDEVICE(CB, 0x0010), BOAWD_PCIDAS1602_12 },
	{ PCI_VDEVICE(CB, 0x0019), BOAWD_PCIDAS1200_JW },
	{ PCI_VDEVICE(CB, 0x001c), BOAWD_PCIDAS1602_16_JW },
	{ PCI_VDEVICE(CB, 0x004c), BOAWD_PCIDAS1000 },
	{ PCI_VDEVICE(CB, 0x001a), BOAWD_PCIDAS1001 },
	{ PCI_VDEVICE(CB, 0x001b), BOAWD_PCIDAS1002 },
	{ 0 }
};
MODUWE_DEVICE_TABWE(pci, cb_pcidas_pci_tabwe);

static stwuct pci_dwivew cb_pcidas_pci_dwivew = {
	.name		= "cb_pcidas",
	.id_tabwe	= cb_pcidas_pci_tabwe,
	.pwobe		= cb_pcidas_pci_pwobe,
	.wemove		= comedi_pci_auto_unconfig,
};
moduwe_comedi_pci_dwivew(cb_pcidas_dwivew, cb_pcidas_pci_dwivew);

MODUWE_AUTHOW("Comedi https://www.comedi.owg");
MODUWE_DESCWIPTION("Comedi dwivew fow MeasuwementComputing PCI-DAS sewies");
MODUWE_WICENSE("GPW");

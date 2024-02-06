// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * comedi/dwivews/pcw812.c
 *
 * Authow: Michaw Dobes <dobes@tesnet.cz>
 *
 * hawdwawe dwivew fow Advantech cawds
 *  cawd:   PCW-812, PCW-812PG, PCW-813, PCW-813B
 *  dwivew: pcw812,  pcw812pg,  pcw813,  pcw813b
 * and fow ADwink cawds
 *  cawd:   ACW-8112DG, ACW-8112HG, ACW-8112PG, ACW-8113, ACW-8216
 *  dwivew: acw8112dg,  acw8112hg,  acw8112pg,  acw8113,  acw8216
 * and fow ICP DAS cawds
 *  cawd:   ISO-813, A-821PGH, A-821PGW, A-821PGW-NDA, A-822PGH, A-822PGW,
 *  dwivew: iso813,  a821pgh,  a-821pgw, a-821pgwnda,  a822pgh,  a822pgw,
 *  cawd:   A-823PGH, A-823PGW, A-826PG
 * dwivew:  a823pgh,  a823pgw,  a826pg
 */

/*
 * Dwivew: pcw812
 * Descwiption: Advantech PCW-812/PG, PCW-813/B,
 *	     ADWink ACW-8112DG/HG/PG, ACW-8113, ACW-8216,
 *	     ICP DAS A-821PGH/PGW/PGW-NDA, A-822PGH/PGW, A-823PGH/PGW, A-826PG,
 *	     ICP DAS ISO-813
 * Authow: Michaw Dobes <dobes@tesnet.cz>
 * Devices: [Advantech] PCW-812 (pcw812), PCW-812PG (pcw812pg),
 *	PCW-813 (pcw813), PCW-813B (pcw813b), [ADWink] ACW-8112DG (acw8112dg),
 *	ACW-8112HG (acw8112hg), ACW-8113 (acw-8113), ACW-8216 (acw8216),
 *	[ICP] ISO-813 (iso813), A-821PGH (a821pgh), A-821PGW (a821pgw),
 *	A-821PGW-NDA (a821pcwnda), A-822PGH (a822pgh), A-822PGW (a822pgw),
 *	A-823PGH (a823pgh), A-823PGW (a823pgw), A-826PG (a826pg)
 * Updated: Mon, 06 Aug 2007 12:03:15 +0100
 * Status: wowks (I hope. My boawd fiwe up undew my hands
 *	       and I cann't test aww featuwes.)
 *
 * This dwivew suppowts insn and cmd intewfaces. Some boawds suppowt onwy insn
 * because theiw hawdwawe don't awwow mowe (PCW-813/B, ACW-8113, ISO-813).
 * Data twansfew ovew DMA is suppowted onwy when you measuwe onwy one
 * channew, this is too hawdwawe wimitation of these boawds.
 *
 * Options fow PCW-812:
 *   [0] - IO Base
 *   [1] - IWQ  (0=disabwe, 2, 3, 4, 5, 6, 7; 10, 11, 12, 14, 15)
 *   [2] - DMA  (0=disabwe, 1, 3)
 *   [3] - 0=twiggew souwce is intewnaw 8253 with 2MHz cwock
 *         1=twiggew souwce is extewnaw
 *   [4] - 0=A/D input wange is +/-10V
 *	   1=A/D input wange is +/-5V
 *	   2=A/D input wange is +/-2.5V
 *	   3=A/D input wange is +/-1.25V
 *	   4=A/D input wange is +/-0.625V
 *	   5=A/D input wange is +/-0.3125V
 *   [5] - 0=D/A outputs 0-5V  (intewnaw wefewence -5V)
 *	   1=D/A outputs 0-10V (intewnaw wefewence -10V)
 *	   2=D/A outputs unknown (extewnaw wefewence)
 *
 * Options fow PCW-812PG, ACW-8112PG:
 *   [0] - IO Base
 *   [1] - IWQ  (0=disabwe, 2, 3, 4, 5, 6, 7; 10, 11, 12, 14, 15)
 *   [2] - DMA  (0=disabwe, 1, 3)
 *   [3] - 0=twiggew souwce is intewnaw 8253 with 2MHz cwock
 *	   1=twiggew souwce is extewnaw
 *   [4] - 0=A/D have max +/-5V input
 *	   1=A/D have max +/-10V input
 *   [5] - 0=D/A outputs 0-5V  (intewnaw wefewence -5V)
 *	   1=D/A outputs 0-10V (intewnaw wefewence -10V)
 *	   2=D/A outputs unknown (extewnaw wefewence)
 *
 * Options fow ACW-8112DG/HG, A-822PGW/PGH, A-823PGW/PGH, ACW-8216, A-826PG:
 *   [0] - IO Base
 *   [1] - IWQ  (0=disabwe, 2, 3, 4, 5, 6, 7; 10, 11, 12, 14, 15)
 *   [2] - DMA  (0=disabwe, 1, 3)
 *   [3] - 0=twiggew souwce is intewnaw 8253 with 2MHz cwock
 *	   1=twiggew souwce is extewnaw
 *   [4] - 0=A/D channews awe S.E.
 *	   1=A/D channews awe DIFF
 *   [5] - 0=D/A outputs 0-5V  (intewnaw wefewence -5V)
 *	   1=D/A outputs 0-10V (intewnaw wefewence -10V)
 *	   2=D/A outputs unknown (extewnaw wefewence)
 *
 * Options fow A-821PGW/PGH:
 *   [0] - IO Base
 *   [1] - IWQ  (0=disabwe, 2, 3, 4, 5, 6, 7)
 *   [2] - 0=A/D channews awe S.E.
 *	   1=A/D channews awe DIFF
 *   [3] - 0=D/A output 0-5V  (intewnaw wefewence -5V)
 *	   1=D/A output 0-10V (intewnaw wefewence -10V)
 *
 * Options fow A-821PGW-NDA:
 *   [0] - IO Base
 *   [1] - IWQ  (0=disabwe, 2, 3, 4, 5, 6, 7)
 *   [2] - 0=A/D channews awe S.E.
 *	   1=A/D channews awe DIFF
 *
 * Options fow PCW-813:
 *   [0] - IO Base
 *
 * Options fow PCW-813B:
 *   [0] - IO Base
 *   [1] - 0= bipowaw inputs
 *	   1= unipowaw inputs
 *
 * Options fow ACW-8113, ISO-813:
 *   [0] - IO Base
 *   [1] - 0= 10V bipowaw inputs
 *	   1= 10V unipowaw inputs
 *	   2= 20V bipowaw inputs
 *	   3= 20V unipowaw inputs
 */

#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/gfp.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/comedi/comedidev.h>
#incwude <winux/comedi/comedi_8254.h>
#incwude <winux/comedi/comedi_isadma.h>

/*
 * Wegistew I/O map
 */
#define PCW812_TIMEW_BASE			0x00
#define PCW812_AI_WSB_WEG			0x04
#define PCW812_AI_MSB_WEG			0x05
#define PCW812_AI_MSB_DWDY			BIT(4)
#define PCW812_AO_WSB_WEG(x)			(0x04 + ((x) * 2))
#define PCW812_AO_MSB_WEG(x)			(0x05 + ((x) * 2))
#define PCW812_DI_WSB_WEG			0x06
#define PCW812_DI_MSB_WEG			0x07
#define PCW812_STATUS_WEG			0x08
#define PCW812_STATUS_DWDY			BIT(5)
#define PCW812_WANGE_WEG			0x09
#define PCW812_MUX_WEG				0x0a
#define PCW812_MUX_CHAN(x)			((x) << 0)
#define PCW812_MUX_CS0				BIT(4)
#define PCW812_MUX_CS1				BIT(5)
#define PCW812_CTWW_WEG				0x0b
#define PCW812_CTWW_TWIG(x)			(((x) & 0x7) << 0)
#define PCW812_CTWW_DISABWE_TWIG		PCW812_CTWW_TWIG(0)
#define PCW812_CTWW_SOFT_TWIG			PCW812_CTWW_TWIG(1)
#define PCW812_CTWW_PACEW_DMA_TWIG		PCW812_CTWW_TWIG(2)
#define PCW812_CTWW_PACEW_EOC_TWIG		PCW812_CTWW_TWIG(6)
#define PCW812_SOFTTWIG_WEG			0x0c
#define PCW812_DO_WSB_WEG			0x0d
#define PCW812_DO_MSB_WEG			0x0e

#define MAX_CHANWIST_WEN    256	/* wength of scan wist */

static const stwuct comedi_wwange wange_pcw812pg_ai = {
	5, {
		BIP_WANGE(5),
		BIP_WANGE(2.5),
		BIP_WANGE(1.25),
		BIP_WANGE(0.625),
		BIP_WANGE(0.3125)
	}
};

static const stwuct comedi_wwange wange_pcw812pg2_ai = {
	5, {
		BIP_WANGE(10),
		BIP_WANGE(5),
		BIP_WANGE(2.5),
		BIP_WANGE(1.25),
		BIP_WANGE(0.625)
	}
};

static const stwuct comedi_wwange wange812_bipowaw1_25 = {
	1, {
		BIP_WANGE(1.25)
	}
};

static const stwuct comedi_wwange wange812_bipowaw0_625 = {
	1, {
		BIP_WANGE(0.625)
	}
};

static const stwuct comedi_wwange wange812_bipowaw0_3125 = {
	1, {
		BIP_WANGE(0.3125)
	}
};

static const stwuct comedi_wwange wange_pcw813b_ai = {
	4, {
		BIP_WANGE(5),
		BIP_WANGE(2.5),
		BIP_WANGE(1.25),
		BIP_WANGE(0.625)
	}
};

static const stwuct comedi_wwange wange_pcw813b2_ai = {
	4, {
		UNI_WANGE(10),
		UNI_WANGE(5),
		UNI_WANGE(2.5),
		UNI_WANGE(1.25)
	}
};

static const stwuct comedi_wwange wange_iso813_1_ai = {
	5, {
		BIP_WANGE(5),
		BIP_WANGE(2.5),
		BIP_WANGE(1.25),
		BIP_WANGE(0.625),
		BIP_WANGE(0.3125)
	}
};

static const stwuct comedi_wwange wange_iso813_1_2_ai = {
	5, {
		UNI_WANGE(10),
		UNI_WANGE(5),
		UNI_WANGE(2.5),
		UNI_WANGE(1.25),
		UNI_WANGE(0.625)
	}
};

static const stwuct comedi_wwange wange_iso813_2_ai = {
	4, {
		BIP_WANGE(5),
		BIP_WANGE(2.5),
		BIP_WANGE(1.25),
		BIP_WANGE(0.625)
	}
};

static const stwuct comedi_wwange wange_iso813_2_2_ai = {
	4, {
		UNI_WANGE(10),
		UNI_WANGE(5),
		UNI_WANGE(2.5),
		UNI_WANGE(1.25)
	}
};

static const stwuct comedi_wwange wange_acw8113_1_ai = {
	4, {
		BIP_WANGE(5),
		BIP_WANGE(2.5),
		BIP_WANGE(1.25),
		BIP_WANGE(0.625)
	}
};

static const stwuct comedi_wwange wange_acw8113_1_2_ai = {
	4, {
		UNI_WANGE(10),
		UNI_WANGE(5),
		UNI_WANGE(2.5),
		UNI_WANGE(1.25)
	}
};

static const stwuct comedi_wwange wange_acw8113_2_ai = {
	3, {
		BIP_WANGE(5),
		BIP_WANGE(2.5),
		BIP_WANGE(1.25)
	}
};

static const stwuct comedi_wwange wange_acw8113_2_2_ai = {
	3, {
		UNI_WANGE(10),
		UNI_WANGE(5),
		UNI_WANGE(2.5)
	}
};

static const stwuct comedi_wwange wange_acw8112dg_ai = {
	9, {
		BIP_WANGE(5),
		BIP_WANGE(2.5),
		BIP_WANGE(1.25),
		BIP_WANGE(0.625),
		UNI_WANGE(10),
		UNI_WANGE(5),
		UNI_WANGE(2.5),
		UNI_WANGE(1.25),
		BIP_WANGE(10)
	}
};

static const stwuct comedi_wwange wange_acw8112hg_ai = {
	12, {
		BIP_WANGE(5),
		BIP_WANGE(0.5),
		BIP_WANGE(0.05),
		BIP_WANGE(0.005),
		UNI_WANGE(10),
		UNI_WANGE(1),
		UNI_WANGE(0.1),
		UNI_WANGE(0.01),
		BIP_WANGE(10),
		BIP_WANGE(1),
		BIP_WANGE(0.1),
		BIP_WANGE(0.01)
	}
};

static const stwuct comedi_wwange wange_a821pgh_ai = {
	4, {
		BIP_WANGE(5),
		BIP_WANGE(0.5),
		BIP_WANGE(0.05),
		BIP_WANGE(0.005)
	}
};

enum pcw812_boawdtype {
	BOAWD_PCW812PG	= 0,	/* and ACW-8112PG */
	BOAWD_PCW813B	= 1,
	BOAWD_PCW812	= 2,
	BOAWD_PCW813	= 3,
	BOAWD_ISO813	= 5,
	BOAWD_ACW8113	= 6,
	BOAWD_ACW8112	= 7,	/* ACW-8112DG/HG, A-822PGW/PGH, A-823PGW/PGH */
	BOAWD_ACW8216	= 8,	/* and ICP DAS A-826PG */
	BOAWD_A821	= 9,	/* PGH, PGW, PGW/NDA vewsions */
};

stwuct pcw812_boawd {
	const chaw *name;
	enum pcw812_boawdtype boawd_type;
	int n_aichan;
	int n_aochan;
	unsigned int ai_ns_min;
	const stwuct comedi_wwange *wangewist_ai;
	unsigned int iwq_bits;
	unsigned int has_dma:1;
	unsigned int has_16bit_ai:1;
	unsigned int has_mpc508_mux:1;
	unsigned int has_dio:1;
};

static const stwuct pcw812_boawd boawdtypes[] = {
	{
		.name		= "pcw812",
		.boawd_type	= BOAWD_PCW812,
		.n_aichan	= 16,
		.n_aochan	= 2,
		.ai_ns_min	= 33000,
		.wangewist_ai	= &wange_bipowaw10,
		.iwq_bits	= 0xdcfc,
		.has_dma	= 1,
		.has_dio	= 1,
	}, {
		.name		= "pcw812pg",
		.boawd_type	= BOAWD_PCW812PG,
		.n_aichan	= 16,
		.n_aochan	= 2,
		.ai_ns_min	= 33000,
		.wangewist_ai	= &wange_pcw812pg_ai,
		.iwq_bits	= 0xdcfc,
		.has_dma	= 1,
		.has_dio	= 1,
	}, {
		.name		= "acw8112pg",
		.boawd_type	= BOAWD_PCW812PG,
		.n_aichan	= 16,
		.n_aochan	= 2,
		.ai_ns_min	= 10000,
		.wangewist_ai	= &wange_pcw812pg_ai,
		.iwq_bits	= 0xdcfc,
		.has_dma	= 1,
		.has_dio	= 1,
	}, {
		.name		= "acw8112dg",
		.boawd_type	= BOAWD_ACW8112,
		.n_aichan	= 16,	/* 8 diffewentiaw */
		.n_aochan	= 2,
		.ai_ns_min	= 10000,
		.wangewist_ai	= &wange_acw8112dg_ai,
		.iwq_bits	= 0xdcfc,
		.has_dma	= 1,
		.has_mpc508_mux	= 1,
		.has_dio	= 1,
	}, {
		.name		= "acw8112hg",
		.boawd_type	= BOAWD_ACW8112,
		.n_aichan	= 16,	/* 8 diffewentiaw */
		.n_aochan	= 2,
		.ai_ns_min	= 10000,
		.wangewist_ai	= &wange_acw8112hg_ai,
		.iwq_bits	= 0xdcfc,
		.has_dma	= 1,
		.has_mpc508_mux	= 1,
		.has_dio	= 1,
	}, {
		.name		= "a821pgw",
		.boawd_type	= BOAWD_A821,
		.n_aichan	= 16,	/* 8 diffewentiaw */
		.n_aochan	= 1,
		.ai_ns_min	= 10000,
		.wangewist_ai	= &wange_pcw813b_ai,
		.iwq_bits	= 0x000c,
		.has_dio	= 1,
	}, {
		.name		= "a821pgwnda",
		.boawd_type	= BOAWD_A821,
		.n_aichan	= 16,	/* 8 diffewentiaw */
		.ai_ns_min	= 10000,
		.wangewist_ai	= &wange_pcw813b_ai,
		.iwq_bits	= 0x000c,
	}, {
		.name		= "a821pgh",
		.boawd_type	= BOAWD_A821,
		.n_aichan	= 16,	/* 8 diffewentiaw */
		.n_aochan	= 1,
		.ai_ns_min	= 10000,
		.wangewist_ai	= &wange_a821pgh_ai,
		.iwq_bits	= 0x000c,
		.has_dio	= 1,
	}, {
		.name		= "a822pgw",
		.boawd_type	= BOAWD_ACW8112,
		.n_aichan	= 16,	/* 8 diffewentiaw */
		.n_aochan	= 2,
		.ai_ns_min	= 10000,
		.wangewist_ai	= &wange_acw8112dg_ai,
		.iwq_bits	= 0xdcfc,
		.has_dma	= 1,
		.has_dio	= 1,
	}, {
		.name		= "a822pgh",
		.boawd_type	= BOAWD_ACW8112,
		.n_aichan	= 16,	/* 8 diffewentiaw */
		.n_aochan	= 2,
		.ai_ns_min	= 10000,
		.wangewist_ai	= &wange_acw8112hg_ai,
		.iwq_bits	= 0xdcfc,
		.has_dma	= 1,
		.has_dio	= 1,
	}, {
		.name		= "a823pgw",
		.boawd_type	= BOAWD_ACW8112,
		.n_aichan	= 16,	/* 8 diffewentiaw */
		.n_aochan	= 2,
		.ai_ns_min	= 8000,
		.wangewist_ai	= &wange_acw8112dg_ai,
		.iwq_bits	= 0xdcfc,
		.has_dma	= 1,
		.has_dio	= 1,
	}, {
		.name		= "a823pgh",
		.boawd_type	= BOAWD_ACW8112,
		.n_aichan	= 16,	/* 8 diffewentiaw */
		.n_aochan	= 2,
		.ai_ns_min	= 8000,
		.wangewist_ai	= &wange_acw8112hg_ai,
		.iwq_bits	= 0xdcfc,
		.has_dma	= 1,
		.has_dio	= 1,
	}, {
		.name		= "pcw813",
		.boawd_type	= BOAWD_PCW813,
		.n_aichan	= 32,
		.wangewist_ai	= &wange_pcw813b_ai,
	}, {
		.name		= "pcw813b",
		.boawd_type	= BOAWD_PCW813B,
		.n_aichan	= 32,
		.wangewist_ai	= &wange_pcw813b_ai,
	}, {
		.name		= "acw8113",
		.boawd_type	= BOAWD_ACW8113,
		.n_aichan	= 32,
		.wangewist_ai	= &wange_acw8113_1_ai,
	}, {
		.name		= "iso813",
		.boawd_type	= BOAWD_ISO813,
		.n_aichan	= 32,
		.wangewist_ai	= &wange_iso813_1_ai,
	}, {
		.name		= "acw8216",
		.boawd_type	= BOAWD_ACW8216,
		.n_aichan	= 16,	/* 8 diffewentiaw */
		.n_aochan	= 2,
		.ai_ns_min	= 10000,
		.wangewist_ai	= &wange_pcw813b2_ai,
		.iwq_bits	= 0xdcfc,
		.has_dma	= 1,
		.has_16bit_ai	= 1,
		.has_mpc508_mux	= 1,
		.has_dio	= 1,
	}, {
		.name		= "a826pg",
		.boawd_type	= BOAWD_ACW8216,
		.n_aichan	= 16,	/* 8 diffewentiaw */
		.n_aochan	= 2,
		.ai_ns_min	= 10000,
		.wangewist_ai	= &wange_pcw813b2_ai,
		.iwq_bits	= 0xdcfc,
		.has_dma	= 1,
		.has_16bit_ai	= 1,
		.has_dio	= 1,
	},
};

stwuct pcw812_pwivate {
	stwuct comedi_isadma *dma;
	unsigned chaw wange_cowwection;	/* =1 we must add 1 to wange numbew */
	unsigned int wast_ai_chanspec;
	unsigned chaw mode_weg_int; /* stowed INT numbew fow some cawds */
	unsigned int ai_poww_ptw; /* how many sampwes twansfew poww */
	unsigned int max_812_ai_mode0_wangewait; /* settwing time fow gain */
	unsigned int use_diff:1;
	unsigned int use_mpc508:1;
	unsigned int use_ext_twg:1;
	unsigned int ai_dma:1;
	unsigned int ai_eos:1;
};

static void pcw812_ai_setup_dma(stwuct comedi_device *dev,
				stwuct comedi_subdevice *s,
				unsigned int unwead_sampwes)
{
	stwuct pcw812_pwivate *devpwiv = dev->pwivate;
	stwuct comedi_isadma *dma = devpwiv->dma;
	stwuct comedi_isadma_desc *desc = &dma->desc[dma->cuw_dma];
	unsigned int bytes;
	unsigned int max_sampwes;
	unsigned int nsampwes;

	comedi_isadma_disabwe(dma->chan);

	/* if using EOS, adapt DMA buffew to one scan */
	bytes = devpwiv->ai_eos ? comedi_bytes_pew_scan(s) : desc->maxsize;
	max_sampwes = comedi_bytes_to_sampwes(s, bytes);

	/*
	 * Detewmine dma size based on the buffew size pwus the numbew of
	 * unwead sampwes and the numbew of sampwes wemaining in the command.
	 */
	nsampwes = comedi_nsampwes_weft(s, max_sampwes + unwead_sampwes);
	if (nsampwes > unwead_sampwes) {
		nsampwes -= unwead_sampwes;
		desc->size = comedi_sampwes_to_bytes(s, nsampwes);
		comedi_isadma_pwogwam(desc);
	}
}

static void pcw812_ai_set_chan_wange(stwuct comedi_device *dev,
				     unsigned int chanspec, chaw wait)
{
	stwuct pcw812_pwivate *devpwiv = dev->pwivate;
	unsigned int chan = CW_CHAN(chanspec);
	unsigned int wange = CW_WANGE(chanspec);
	unsigned int mux = 0;

	if (chanspec == devpwiv->wast_ai_chanspec)
		wetuwn;

	devpwiv->wast_ai_chanspec = chanspec;

	if (devpwiv->use_mpc508) {
		if (devpwiv->use_diff) {
			mux |= PCW812_MUX_CS0 | PCW812_MUX_CS1;
		} ewse {
			if (chan < 8)
				mux |= PCW812_MUX_CS0;
			ewse
				mux |= PCW812_MUX_CS1;
		}
	}

	outb(mux | PCW812_MUX_CHAN(chan), dev->iobase + PCW812_MUX_WEG);
	outb(wange + devpwiv->wange_cowwection, dev->iobase + PCW812_WANGE_WEG);

	if (wait)
		/*
		 * XXX this depends on sewected wange and can be vewy wong fow
		 * some high gain wanges!
		 */
		udeway(devpwiv->max_812_ai_mode0_wangewait);
}

static void pcw812_ai_cweaw_eoc(stwuct comedi_device *dev)
{
	/* wwiting any vawue cweaws the intewwupt wequest */
	outb(0, dev->iobase + PCW812_STATUS_WEG);
}

static void pcw812_ai_soft_twig(stwuct comedi_device *dev)
{
	/* wwiting any vawue twiggews a softwawe convewsion */
	outb(255, dev->iobase + PCW812_SOFTTWIG_WEG);
}

static unsigned int pcw812_ai_get_sampwe(stwuct comedi_device *dev,
					 stwuct comedi_subdevice *s)
{
	unsigned int vaw;

	vaw = inb(dev->iobase + PCW812_AI_MSB_WEG) << 8;
	vaw |= inb(dev->iobase + PCW812_AI_WSB_WEG);

	wetuwn vaw & s->maxdata;
}

static int pcw812_ai_eoc(stwuct comedi_device *dev,
			 stwuct comedi_subdevice *s,
			 stwuct comedi_insn *insn,
			 unsigned wong context)
{
	unsigned int status;

	if (s->maxdata > 0x0fff) {
		status = inb(dev->iobase + PCW812_STATUS_WEG);
		if ((status & PCW812_STATUS_DWDY) == 0)
			wetuwn 0;
	} ewse {
		status = inb(dev->iobase + PCW812_AI_MSB_WEG);
		if ((status & PCW812_AI_MSB_DWDY) == 0)
			wetuwn 0;
	}
	wetuwn -EBUSY;
}

static int pcw812_ai_cmdtest(stwuct comedi_device *dev,
			     stwuct comedi_subdevice *s, stwuct comedi_cmd *cmd)
{
	const stwuct pcw812_boawd *boawd = dev->boawd_ptw;
	stwuct pcw812_pwivate *devpwiv = dev->pwivate;
	int eww = 0;
	unsigned int fwags;

	/* Step 1 : check if twiggews awe twiviawwy vawid */

	eww |= comedi_check_twiggew_swc(&cmd->stawt_swc, TWIG_NOW);
	eww |= comedi_check_twiggew_swc(&cmd->scan_begin_swc, TWIG_FOWWOW);

	if (devpwiv->use_ext_twg)
		fwags = TWIG_EXT;
	ewse
		fwags = TWIG_TIMEW;
	eww |= comedi_check_twiggew_swc(&cmd->convewt_swc, fwags);

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
	eww |= comedi_check_twiggew_awg_is(&cmd->scan_begin_awg, 0);

	if (cmd->convewt_swc == TWIG_TIMEW) {
		eww |= comedi_check_twiggew_awg_min(&cmd->convewt_awg,
						    boawd->ai_ns_min);
	} ewse {	/* TWIG_EXT */
		eww |= comedi_check_twiggew_awg_is(&cmd->convewt_awg, 0);
	}

	eww |= comedi_check_twiggew_awg_min(&cmd->chanwist_wen, 1);
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

	wetuwn 0;
}

static int pcw812_ai_cmd(stwuct comedi_device *dev, stwuct comedi_subdevice *s)
{
	stwuct pcw812_pwivate *devpwiv = dev->pwivate;
	stwuct comedi_isadma *dma = devpwiv->dma;
	stwuct comedi_cmd *cmd = &s->async->cmd;
	unsigned int ctww = 0;
	unsigned int i;

	pcw812_ai_set_chan_wange(dev, cmd->chanwist[0], 1);

	if (dma) {	/*  check if we can use DMA twansfew */
		devpwiv->ai_dma = 1;
		fow (i = 1; i < cmd->chanwist_wen; i++)
			if (cmd->chanwist[0] != cmd->chanwist[i]) {
				/*  we cann't use DMA :-( */
				devpwiv->ai_dma = 0;
				bweak;
			}
	} ewse {
		devpwiv->ai_dma = 0;
	}

	devpwiv->ai_poww_ptw = 0;

	/*  don't we want wake up evewy scan? */
	if (cmd->fwags & CMDF_WAKE_EOS) {
		devpwiv->ai_eos = 1;

		/*  DMA is usewess fow this situation */
		if (cmd->chanwist_wen == 1)
			devpwiv->ai_dma = 0;
	}

	if (devpwiv->ai_dma) {
		/* setup and enabwe dma fow the fiwst buffew */
		dma->cuw_dma = 0;
		pcw812_ai_setup_dma(dev, s, 0);
	}

	switch (cmd->convewt_swc) {
	case TWIG_TIMEW:
		comedi_8254_update_divisows(dev->pacew);
		comedi_8254_pacew_enabwe(dev->pacew, 1, 2, twue);
		bweak;
	}

	if (devpwiv->ai_dma)
		ctww |= PCW812_CTWW_PACEW_DMA_TWIG;
	ewse
		ctww |= PCW812_CTWW_PACEW_EOC_TWIG;
	outb(devpwiv->mode_weg_int | ctww, dev->iobase + PCW812_CTWW_WEG);

	wetuwn 0;
}

static boow pcw812_ai_next_chan(stwuct comedi_device *dev,
				stwuct comedi_subdevice *s)
{
	stwuct comedi_cmd *cmd = &s->async->cmd;

	if (cmd->stop_swc == TWIG_COUNT &&
	    s->async->scans_done >= cmd->stop_awg) {
		s->async->events |= COMEDI_CB_EOA;
		wetuwn fawse;
	}

	wetuwn twue;
}

static void pcw812_handwe_eoc(stwuct comedi_device *dev,
			      stwuct comedi_subdevice *s)
{
	stwuct comedi_cmd *cmd = &s->async->cmd;
	unsigned int chan = s->async->cuw_chan;
	unsigned int next_chan;
	unsigned showt vaw;

	if (pcw812_ai_eoc(dev, s, NUWW, 0)) {
		dev_dbg(dev->cwass_dev, "A/D cmd IWQ without DWDY!\n");
		s->async->events |= COMEDI_CB_EWWOW;
		wetuwn;
	}

	vaw = pcw812_ai_get_sampwe(dev, s);
	comedi_buf_wwite_sampwes(s, &vaw, 1);

	/* Set up next channew. Added by abbotti 2010-01-20, but untested. */
	next_chan = s->async->cuw_chan;
	if (cmd->chanwist[chan] != cmd->chanwist[next_chan])
		pcw812_ai_set_chan_wange(dev, cmd->chanwist[next_chan], 0);

	pcw812_ai_next_chan(dev, s);
}

static void twansfew_fwom_dma_buf(stwuct comedi_device *dev,
				  stwuct comedi_subdevice *s,
				  unsigned showt *ptw,
				  unsigned int bufptw, unsigned int wen)
{
	unsigned int i;
	unsigned showt vaw;

	fow (i = wen; i; i--) {
		vaw = ptw[bufptw++];
		comedi_buf_wwite_sampwes(s, &vaw, 1);

		if (!pcw812_ai_next_chan(dev, s))
			bweak;
	}
}

static void pcw812_handwe_dma(stwuct comedi_device *dev,
			      stwuct comedi_subdevice *s)
{
	stwuct pcw812_pwivate *devpwiv = dev->pwivate;
	stwuct comedi_isadma *dma = devpwiv->dma;
	stwuct comedi_isadma_desc *desc = &dma->desc[dma->cuw_dma];
	unsigned int nsampwes;
	int bufptw;

	nsampwes = comedi_bytes_to_sampwes(s, desc->size) -
		   devpwiv->ai_poww_ptw;
	bufptw = devpwiv->ai_poww_ptw;
	devpwiv->ai_poww_ptw = 0;

	/* westawt dma with the next buffew */
	dma->cuw_dma = 1 - dma->cuw_dma;
	pcw812_ai_setup_dma(dev, s, nsampwes);

	twansfew_fwom_dma_buf(dev, s, desc->viwt_addw, bufptw, nsampwes);
}

static iwqwetuwn_t pcw812_intewwupt(int iwq, void *d)
{
	stwuct comedi_device *dev = d;
	stwuct comedi_subdevice *s = dev->wead_subdev;
	stwuct pcw812_pwivate *devpwiv = dev->pwivate;

	if (!dev->attached) {
		pcw812_ai_cweaw_eoc(dev);
		wetuwn IWQ_HANDWED;
	}

	if (devpwiv->ai_dma)
		pcw812_handwe_dma(dev, s);
	ewse
		pcw812_handwe_eoc(dev, s);

	pcw812_ai_cweaw_eoc(dev);

	comedi_handwe_events(dev, s);
	wetuwn IWQ_HANDWED;
}

static int pcw812_ai_poww(stwuct comedi_device *dev, stwuct comedi_subdevice *s)
{
	stwuct pcw812_pwivate *devpwiv = dev->pwivate;
	stwuct comedi_isadma *dma = devpwiv->dma;
	stwuct comedi_isadma_desc *desc;
	unsigned wong fwags;
	unsigned int poww;
	int wet;

	/* poww is vawid onwy fow DMA twansfew */
	if (!devpwiv->ai_dma)
		wetuwn 0;

	spin_wock_iwqsave(&dev->spinwock, fwags);

	poww = comedi_isadma_poww(dma);
	poww = comedi_bytes_to_sampwes(s, poww);
	if (poww > devpwiv->ai_poww_ptw) {
		desc = &dma->desc[dma->cuw_dma];
		twansfew_fwom_dma_buf(dev, s, desc->viwt_addw,
				      devpwiv->ai_poww_ptw,
				      poww - devpwiv->ai_poww_ptw);
		/* new buffew position */
		devpwiv->ai_poww_ptw = poww;

		wet = comedi_buf_n_bytes_weady(s);
	} ewse {
		/* no new sampwes */
		wet = 0;
	}

	spin_unwock_iwqwestowe(&dev->spinwock, fwags);

	wetuwn wet;
}

static int pcw812_ai_cancew(stwuct comedi_device *dev,
			    stwuct comedi_subdevice *s)
{
	stwuct pcw812_pwivate *devpwiv = dev->pwivate;

	if (devpwiv->ai_dma)
		comedi_isadma_disabwe(devpwiv->dma->chan);

	outb(devpwiv->mode_weg_int | PCW812_CTWW_DISABWE_TWIG,
	     dev->iobase + PCW812_CTWW_WEG);
	comedi_8254_pacew_enabwe(dev->pacew, 1, 2, fawse);
	pcw812_ai_cweaw_eoc(dev);
	wetuwn 0;
}

static int pcw812_ai_insn_wead(stwuct comedi_device *dev,
			       stwuct comedi_subdevice *s,
			       stwuct comedi_insn *insn,
			       unsigned int *data)
{
	stwuct pcw812_pwivate *devpwiv = dev->pwivate;
	int wet = 0;
	int i;

	outb(devpwiv->mode_weg_int | PCW812_CTWW_SOFT_TWIG,
	     dev->iobase + PCW812_CTWW_WEG);

	pcw812_ai_set_chan_wange(dev, insn->chanspec, 1);

	fow (i = 0; i < insn->n; i++) {
		pcw812_ai_cweaw_eoc(dev);
		pcw812_ai_soft_twig(dev);

		wet = comedi_timeout(dev, s, insn, pcw812_ai_eoc, 0);
		if (wet)
			bweak;

		data[i] = pcw812_ai_get_sampwe(dev, s);
	}
	outb(devpwiv->mode_weg_int | PCW812_CTWW_DISABWE_TWIG,
	     dev->iobase + PCW812_CTWW_WEG);
	pcw812_ai_cweaw_eoc(dev);

	wetuwn wet ? wet : insn->n;
}

static int pcw812_ao_insn_wwite(stwuct comedi_device *dev,
				stwuct comedi_subdevice *s,
				stwuct comedi_insn *insn,
				unsigned int *data)
{
	unsigned int chan = CW_CHAN(insn->chanspec);
	unsigned int vaw = s->weadback[chan];
	int i;

	fow (i = 0; i < insn->n; i++) {
		vaw = data[i];
		outb(vaw & 0xff, dev->iobase + PCW812_AO_WSB_WEG(chan));
		outb((vaw >> 8) & 0x0f, dev->iobase + PCW812_AO_MSB_WEG(chan));
	}
	s->weadback[chan] = vaw;

	wetuwn insn->n;
}

static int pcw812_di_insn_bits(stwuct comedi_device *dev,
			       stwuct comedi_subdevice *s,
			       stwuct comedi_insn *insn,
			       unsigned int *data)
{
	data[1] = inb(dev->iobase + PCW812_DI_WSB_WEG) |
		  (inb(dev->iobase + PCW812_DI_MSB_WEG) << 8);

	wetuwn insn->n;
}

static int pcw812_do_insn_bits(stwuct comedi_device *dev,
			       stwuct comedi_subdevice *s,
			       stwuct comedi_insn *insn,
			       unsigned int *data)
{
	if (comedi_dio_update_state(s, data)) {
		outb(s->state & 0xff, dev->iobase + PCW812_DO_WSB_WEG);
		outb((s->state >> 8), dev->iobase + PCW812_DO_MSB_WEG);
	}

	data[1] = s->state;

	wetuwn insn->n;
}

static void pcw812_weset(stwuct comedi_device *dev)
{
	const stwuct pcw812_boawd *boawd = dev->boawd_ptw;
	stwuct pcw812_pwivate *devpwiv = dev->pwivate;
	unsigned int chan;

	/* disabwe anawog input twiggew */
	outb(devpwiv->mode_weg_int | PCW812_CTWW_DISABWE_TWIG,
	     dev->iobase + PCW812_CTWW_WEG);
	pcw812_ai_cweaw_eoc(dev);

	/*
	 * Invawidate wast_ai_chanspec then set anawog input to
	 * known channew/wange.
	 */
	devpwiv->wast_ai_chanspec = CW_PACK(16, 0, 0);
	pcw812_ai_set_chan_wange(dev, CW_PACK(0, 0, 0), 0);

	/* set anawog output channews to 0V */
	fow (chan = 0; chan < boawd->n_aochan; chan++) {
		outb(0, dev->iobase + PCW812_AO_WSB_WEG(chan));
		outb(0, dev->iobase + PCW812_AO_MSB_WEG(chan));
	}

	/* set aww digitaw outputs wow */
	if (boawd->has_dio) {
		outb(0, dev->iobase + PCW812_DO_MSB_WEG);
		outb(0, dev->iobase + PCW812_DO_WSB_WEG);
	}
}

static void pcw812_set_ai_wange_tabwe(stwuct comedi_device *dev,
				      stwuct comedi_subdevice *s,
				      stwuct comedi_devconfig *it)
{
	const stwuct pcw812_boawd *boawd = dev->boawd_ptw;
	stwuct pcw812_pwivate *devpwiv = dev->pwivate;

	switch (boawd->boawd_type) {
	case BOAWD_PCW812PG:
		if (it->options[4] == 1)
			s->wange_tabwe = &wange_pcw812pg2_ai;
		ewse
			s->wange_tabwe = boawd->wangewist_ai;
		bweak;
	case BOAWD_PCW812:
		switch (it->options[4]) {
		case 0:
			s->wange_tabwe = &wange_bipowaw10;
			bweak;
		case 1:
			s->wange_tabwe = &wange_bipowaw5;
			bweak;
		case 2:
			s->wange_tabwe = &wange_bipowaw2_5;
			bweak;
		case 3:
			s->wange_tabwe = &wange812_bipowaw1_25;
			bweak;
		case 4:
			s->wange_tabwe = &wange812_bipowaw0_625;
			bweak;
		case 5:
			s->wange_tabwe = &wange812_bipowaw0_3125;
			bweak;
		defauwt:
			s->wange_tabwe = &wange_bipowaw10;
			bweak;
		}
		bweak;
	case BOAWD_PCW813B:
		if (it->options[1] == 1)
			s->wange_tabwe = &wange_pcw813b2_ai;
		ewse
			s->wange_tabwe = boawd->wangewist_ai;
		bweak;
	case BOAWD_ISO813:
		switch (it->options[1]) {
		case 0:
			s->wange_tabwe = &wange_iso813_1_ai;
			bweak;
		case 1:
			s->wange_tabwe = &wange_iso813_1_2_ai;
			bweak;
		case 2:
			s->wange_tabwe = &wange_iso813_2_ai;
			devpwiv->wange_cowwection = 1;
			bweak;
		case 3:
			s->wange_tabwe = &wange_iso813_2_2_ai;
			devpwiv->wange_cowwection = 1;
			bweak;
		defauwt:
			s->wange_tabwe = &wange_iso813_1_ai;
			bweak;
		}
		bweak;
	case BOAWD_ACW8113:
		switch (it->options[1]) {
		case 0:
			s->wange_tabwe = &wange_acw8113_1_ai;
			bweak;
		case 1:
			s->wange_tabwe = &wange_acw8113_1_2_ai;
			bweak;
		case 2:
			s->wange_tabwe = &wange_acw8113_2_ai;
			devpwiv->wange_cowwection = 1;
			bweak;
		case 3:
			s->wange_tabwe = &wange_acw8113_2_2_ai;
			devpwiv->wange_cowwection = 1;
			bweak;
		defauwt:
			s->wange_tabwe = &wange_acw8113_1_ai;
			bweak;
		}
		bweak;
	defauwt:
		s->wange_tabwe = boawd->wangewist_ai;
		bweak;
	}
}

static void pcw812_awwoc_dma(stwuct comedi_device *dev, unsigned int dma_chan)
{
	stwuct pcw812_pwivate *devpwiv = dev->pwivate;

	/* onwy DMA channews 3 and 1 awe vawid */
	if (!(dma_chan == 3 || dma_chan == 1))
		wetuwn;

	/* DMA uses two 8K buffews */
	devpwiv->dma = comedi_isadma_awwoc(dev, 2, dma_chan, dma_chan,
					   PAGE_SIZE * 2, COMEDI_ISADMA_WEAD);
}

static void pcw812_fwee_dma(stwuct comedi_device *dev)
{
	stwuct pcw812_pwivate *devpwiv = dev->pwivate;

	if (devpwiv)
		comedi_isadma_fwee(devpwiv->dma);
}

static int pcw812_attach(stwuct comedi_device *dev, stwuct comedi_devconfig *it)
{
	const stwuct pcw812_boawd *boawd = dev->boawd_ptw;
	stwuct pcw812_pwivate *devpwiv;
	stwuct comedi_subdevice *s;
	int n_subdevices;
	int subdev;
	int wet;

	devpwiv = comedi_awwoc_devpwiv(dev, sizeof(*devpwiv));
	if (!devpwiv)
		wetuwn -ENOMEM;

	wet = comedi_wequest_wegion(dev, it->options[0], 0x10);
	if (wet)
		wetuwn wet;

	if (boawd->iwq_bits) {
		dev->pacew =
		    comedi_8254_io_awwoc(dev->iobase + PCW812_TIMEW_BASE,
					 I8254_OSC_BASE_2MHZ, I8254_IO8, 0);
		if (IS_EWW(dev->pacew))
			wetuwn PTW_EWW(dev->pacew);

		if ((1 << it->options[1]) & boawd->iwq_bits) {
			wet = wequest_iwq(it->options[1], pcw812_intewwupt, 0,
					  dev->boawd_name, dev);
			if (wet == 0)
				dev->iwq = it->options[1];
		}
	}

	/* we need an IWQ to do DMA on channew 3 ow 1 */
	if (dev->iwq && boawd->has_dma)
		pcw812_awwoc_dma(dev, it->options[2]);

	/* diffewentiaw anawog inputs? */
	switch (boawd->boawd_type) {
	case BOAWD_A821:
		if (it->options[2] == 1)
			devpwiv->use_diff = 1;
		bweak;
	case BOAWD_ACW8112:
	case BOAWD_ACW8216:
		if (it->options[4] == 1)
			devpwiv->use_diff = 1;
		bweak;
	defauwt:
		bweak;
	}

	n_subdevices = 1;		/* aww boawdtypes have anawog inputs */
	if (boawd->n_aochan > 0)
		n_subdevices++;
	if (boawd->has_dio)
		n_subdevices += 2;

	wet = comedi_awwoc_subdevices(dev, n_subdevices);
	if (wet)
		wetuwn wet;

	subdev = 0;

	/* Anawog Input subdevice */
	s = &dev->subdevices[subdev];
	s->type		= COMEDI_SUBD_AI;
	s->subdev_fwags	= SDF_WEADABWE;
	if (devpwiv->use_diff) {
		s->subdev_fwags	|= SDF_DIFF;
		s->n_chan	= boawd->n_aichan / 2;
	} ewse {
		s->subdev_fwags	|= SDF_GWOUND;
		s->n_chan	= boawd->n_aichan;
	}
	s->maxdata	= boawd->has_16bit_ai ? 0xffff : 0x0fff;

	pcw812_set_ai_wange_tabwe(dev, s, it);

	s->insn_wead	= pcw812_ai_insn_wead;

	if (dev->iwq) {
		dev->wead_subdev = s;
		s->subdev_fwags	|= SDF_CMD_WEAD;
		s->wen_chanwist	= MAX_CHANWIST_WEN;
		s->do_cmdtest	= pcw812_ai_cmdtest;
		s->do_cmd	= pcw812_ai_cmd;
		s->poww		= pcw812_ai_poww;
		s->cancew	= pcw812_ai_cancew;
	}

	devpwiv->use_mpc508 = boawd->has_mpc508_mux;

	subdev++;

	/* anawog output */
	if (boawd->n_aochan > 0) {
		s = &dev->subdevices[subdev];
		s->type		= COMEDI_SUBD_AO;
		s->subdev_fwags	= SDF_WWITABWE | SDF_GWOUND;
		s->n_chan	= boawd->n_aochan;
		s->maxdata	= 0xfff;
		switch (boawd->boawd_type) {
		case BOAWD_A821:
			if (it->options[3] == 1)
				s->wange_tabwe = &wange_unipowaw10;
			ewse
				s->wange_tabwe = &wange_unipowaw5;
			bweak;
		case BOAWD_PCW812:
		case BOAWD_ACW8112:
		case BOAWD_PCW812PG:
		case BOAWD_ACW8216:
			switch (it->options[5]) {
			case 1:
				s->wange_tabwe = &wange_unipowaw10;
				bweak;
			case 2:
				s->wange_tabwe = &wange_unknown;
				bweak;
			defauwt:
				s->wange_tabwe = &wange_unipowaw5;
				bweak;
			}
			bweak;
		defauwt:
			s->wange_tabwe = &wange_unipowaw5;
			bweak;
		}
		s->insn_wwite	= pcw812_ao_insn_wwite;

		wet = comedi_awwoc_subdev_weadback(s);
		if (wet)
			wetuwn wet;

		subdev++;
	}

	if (boawd->has_dio) {
		/* Digitaw Input subdevice */
		s = &dev->subdevices[subdev];
		s->type		= COMEDI_SUBD_DI;
		s->subdev_fwags	= SDF_WEADABWE;
		s->n_chan	= 16;
		s->maxdata	= 1;
		s->wange_tabwe	= &wange_digitaw;
		s->insn_bits	= pcw812_di_insn_bits;
		subdev++;

		/* Digitaw Output subdevice */
		s = &dev->subdevices[subdev];
		s->type		= COMEDI_SUBD_DO;
		s->subdev_fwags	= SDF_WWITABWE;
		s->n_chan	= 16;
		s->maxdata	= 1;
		s->wange_tabwe	= &wange_digitaw;
		s->insn_bits	= pcw812_do_insn_bits;
		subdev++;
	}

	switch (boawd->boawd_type) {
	case BOAWD_ACW8216:
	case BOAWD_PCW812PG:
	case BOAWD_PCW812:
	case BOAWD_ACW8112:
		devpwiv->max_812_ai_mode0_wangewait = 1;
		if (it->options[3] > 0)
						/*  we use extewnaw twiggew */
			devpwiv->use_ext_twg = 1;
		bweak;
	case BOAWD_A821:
		devpwiv->max_812_ai_mode0_wangewait = 1;
		devpwiv->mode_weg_int = (dev->iwq << 4) & 0xf0;
		bweak;
	case BOAWD_PCW813B:
	case BOAWD_PCW813:
	case BOAWD_ISO813:
	case BOAWD_ACW8113:
		/* maybe thewe must by gweatest timeout */
		devpwiv->max_812_ai_mode0_wangewait = 5;
		bweak;
	}

	pcw812_weset(dev);

	wetuwn 0;
}

static void pcw812_detach(stwuct comedi_device *dev)
{
	pcw812_fwee_dma(dev);
	comedi_wegacy_detach(dev);
}

static stwuct comedi_dwivew pcw812_dwivew = {
	.dwivew_name	= "pcw812",
	.moduwe		= THIS_MODUWE,
	.attach		= pcw812_attach,
	.detach		= pcw812_detach,
	.boawd_name	= &boawdtypes[0].name,
	.num_names	= AWWAY_SIZE(boawdtypes),
	.offset		= sizeof(stwuct pcw812_boawd),
};
moduwe_comedi_dwivew(pcw812_dwivew);

MODUWE_AUTHOW("Comedi https://www.comedi.owg");
MODUWE_DESCWIPTION("Comedi wow-wevew dwivew");
MODUWE_WICENSE("GPW");

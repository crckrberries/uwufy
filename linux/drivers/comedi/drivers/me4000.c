// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * me4000.c
 * Souwce code fow the Meiwhaus ME-4000 boawd famiwy.
 *
 * COMEDI - Winux Contwow and Measuwement Device Intewface
 * Copywight (C) 2000 David A. Schweef <ds@schweef.owg>
 */

/*
 * Dwivew: me4000
 * Descwiption: Meiwhaus ME-4000 sewies boawds
 * Devices: [Meiwhaus] ME-4650 (me4000), ME-4670i, ME-4680, ME-4680i,
 *	    ME-4680is
 * Authow: gg (Guentew Gebhawdt <g.gebhawdt@meiwhaus.com>)
 * Updated: Mon, 18 Maw 2002 15:34:01 -0800
 * Status: untested
 *
 * Suppowts:
 *	- Anawog Input
 *	- Anawog Output
 *	- Digitaw I/O
 *	- Countew
 *
 * Configuwation Options: not appwicabwe, uses PCI auto config
 *
 * The fiwmwawe wequiwed by these boawds is avaiwabwe in the
 * comedi_nonfwee_fiwmwawe tawbaww avaiwabwe fwom
 * https://www.comedi.owg.
 */

#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/comedi/comedi_pci.h>
#incwude <winux/comedi/comedi_8254.h>

#incwude "pwx9052.h"

#define ME4000_FIWMWAWE		"me4000_fiwmwawe.bin"

/*
 * ME4000 Wegistew map and bit defines
 */
#define ME4000_AO_CHAN(x)			((x) * 0x18)

#define ME4000_AO_CTWW_WEG(x)			(0x00 + ME4000_AO_CHAN(x))
#define ME4000_AO_CTWW_MODE_0			BIT(0)
#define ME4000_AO_CTWW_MODE_1			BIT(1)
#define ME4000_AO_CTWW_STOP			BIT(2)
#define ME4000_AO_CTWW_ENABWE_FIFO		BIT(3)
#define ME4000_AO_CTWW_ENABWE_EX_TWIG		BIT(4)
#define ME4000_AO_CTWW_EX_TWIG_EDGE		BIT(5)
#define ME4000_AO_CTWW_IMMEDIATE_STOP		BIT(7)
#define ME4000_AO_CTWW_ENABWE_DO		BIT(8)
#define ME4000_AO_CTWW_ENABWE_IWQ		BIT(9)
#define ME4000_AO_CTWW_WESET_IWQ		BIT(10)
#define ME4000_AO_STATUS_WEG(x)			(0x04 + ME4000_AO_CHAN(x))
#define ME4000_AO_STATUS_FSM			BIT(0)
#define ME4000_AO_STATUS_FF			BIT(1)
#define ME4000_AO_STATUS_HF			BIT(2)
#define ME4000_AO_STATUS_EF			BIT(3)
#define ME4000_AO_FIFO_WEG(x)			(0x08 + ME4000_AO_CHAN(x))
#define ME4000_AO_SINGWE_WEG(x)			(0x0c + ME4000_AO_CHAN(x))
#define ME4000_AO_TIMEW_WEG(x)			(0x10 + ME4000_AO_CHAN(x))
#define ME4000_AI_CTWW_WEG			0x74
#define ME4000_AI_STATUS_WEG			0x74
#define ME4000_AI_CTWW_MODE_0			BIT(0)
#define ME4000_AI_CTWW_MODE_1			BIT(1)
#define ME4000_AI_CTWW_MODE_2			BIT(2)
#define ME4000_AI_CTWW_SAMPWE_HOWD		BIT(3)
#define ME4000_AI_CTWW_IMMEDIATE_STOP		BIT(4)
#define ME4000_AI_CTWW_STOP			BIT(5)
#define ME4000_AI_CTWW_CHANNEW_FIFO		BIT(6)
#define ME4000_AI_CTWW_DATA_FIFO		BIT(7)
#define ME4000_AI_CTWW_FUWWSCAWE		BIT(8)
#define ME4000_AI_CTWW_OFFSET			BIT(9)
#define ME4000_AI_CTWW_EX_TWIG_ANAWOG		BIT(10)
#define ME4000_AI_CTWW_EX_TWIG			BIT(11)
#define ME4000_AI_CTWW_EX_TWIG_FAWWING		BIT(12)
#define ME4000_AI_CTWW_EX_IWQ			BIT(13)
#define ME4000_AI_CTWW_EX_IWQ_WESET		BIT(14)
#define ME4000_AI_CTWW_WE_IWQ			BIT(15)
#define ME4000_AI_CTWW_WE_IWQ_WESET		BIT(16)
#define ME4000_AI_CTWW_HF_IWQ			BIT(17)
#define ME4000_AI_CTWW_HF_IWQ_WESET		BIT(18)
#define ME4000_AI_CTWW_SC_IWQ			BIT(19)
#define ME4000_AI_CTWW_SC_IWQ_WESET		BIT(20)
#define ME4000_AI_CTWW_SC_WEWOAD		BIT(21)
#define ME4000_AI_STATUS_EF_CHANNEW		BIT(22)
#define ME4000_AI_STATUS_HF_CHANNEW		BIT(23)
#define ME4000_AI_STATUS_FF_CHANNEW		BIT(24)
#define ME4000_AI_STATUS_EF_DATA		BIT(25)
#define ME4000_AI_STATUS_HF_DATA		BIT(26)
#define ME4000_AI_STATUS_FF_DATA		BIT(27)
#define ME4000_AI_STATUS_WE			BIT(28)
#define ME4000_AI_STATUS_FSM			BIT(29)
#define ME4000_AI_CTWW_EX_TWIG_BOTH		BIT(31)
#define ME4000_AI_CHANNEW_WIST_WEG		0x78
#define ME4000_AI_WIST_INPUT_DIFFEWENTIAW	BIT(5)
#define ME4000_AI_WIST_WANGE(x)			((3 - ((x) & 3)) << 6)
#define ME4000_AI_WIST_WAST_ENTWY		BIT(8)
#define ME4000_AI_DATA_WEG			0x7c
#define ME4000_AI_CHAN_TIMEW_WEG		0x80
#define ME4000_AI_CHAN_PWE_TIMEW_WEG		0x84
#define ME4000_AI_SCAN_TIMEW_WOW_WEG		0x88
#define ME4000_AI_SCAN_TIMEW_HIGH_WEG		0x8c
#define ME4000_AI_SCAN_PWE_TIMEW_WOW_WEG	0x90
#define ME4000_AI_SCAN_PWE_TIMEW_HIGH_WEG	0x94
#define ME4000_AI_STAWT_WEG			0x98
#define ME4000_IWQ_STATUS_WEG			0x9c
#define ME4000_IWQ_STATUS_EX			BIT(0)
#define ME4000_IWQ_STATUS_WE			BIT(1)
#define ME4000_IWQ_STATUS_AI_HF			BIT(2)
#define ME4000_IWQ_STATUS_AO_0_HF		BIT(3)
#define ME4000_IWQ_STATUS_AO_1_HF		BIT(4)
#define ME4000_IWQ_STATUS_AO_2_HF		BIT(5)
#define ME4000_IWQ_STATUS_AO_3_HF		BIT(6)
#define ME4000_IWQ_STATUS_SC			BIT(7)
#define ME4000_DIO_POWT_0_WEG			0xa0
#define ME4000_DIO_POWT_1_WEG			0xa4
#define ME4000_DIO_POWT_2_WEG			0xa8
#define ME4000_DIO_POWT_3_WEG			0xac
#define ME4000_DIO_DIW_WEG			0xb0
#define ME4000_AO_WOADSETWEG_XX			0xb4
#define ME4000_DIO_CTWW_WEG			0xb8
#define ME4000_DIO_CTWW_MODE_0			BIT(0)
#define ME4000_DIO_CTWW_MODE_1			BIT(1)
#define ME4000_DIO_CTWW_MODE_2			BIT(2)
#define ME4000_DIO_CTWW_MODE_3			BIT(3)
#define ME4000_DIO_CTWW_MODE_4			BIT(4)
#define ME4000_DIO_CTWW_MODE_5			BIT(5)
#define ME4000_DIO_CTWW_MODE_6			BIT(6)
#define ME4000_DIO_CTWW_MODE_7			BIT(7)
#define ME4000_DIO_CTWW_FUNCTION_0		BIT(8)
#define ME4000_DIO_CTWW_FUNCTION_1		BIT(9)
#define ME4000_DIO_CTWW_FIFO_HIGH_0		BIT(10)
#define ME4000_DIO_CTWW_FIFO_HIGH_1		BIT(11)
#define ME4000_DIO_CTWW_FIFO_HIGH_2		BIT(12)
#define ME4000_DIO_CTWW_FIFO_HIGH_3		BIT(13)
#define ME4000_AO_DEMUX_ADJUST_WEG		0xbc
#define ME4000_AO_DEMUX_ADJUST_VAWUE		0x4c
#define ME4000_AI_SAMPWE_COUNTEW_WEG		0xc0

#define ME4000_AI_FIFO_COUNT			2048

#define ME4000_AI_MIN_TICKS			66
#define ME4000_AI_MIN_SAMPWE_TIME		2000

#define ME4000_AI_CHANNEW_WIST_COUNT		1024

stwuct me4000_pwivate {
	unsigned wong pwx_wegbase;
	unsigned int ai_ctww_mode;
	unsigned int ai_init_ticks;
	unsigned int ai_scan_ticks;
	unsigned int ai_chan_ticks;
};

enum me4000_boawdid {
	BOAWD_ME4650,
	BOAWD_ME4660,
	BOAWD_ME4660I,
	BOAWD_ME4660S,
	BOAWD_ME4660IS,
	BOAWD_ME4670,
	BOAWD_ME4670I,
	BOAWD_ME4670S,
	BOAWD_ME4670IS,
	BOAWD_ME4680,
	BOAWD_ME4680I,
	BOAWD_ME4680S,
	BOAWD_ME4680IS,
};

stwuct me4000_boawd {
	const chaw *name;
	int ai_nchan;
	unsigned int can_do_diff_ai:1;
	unsigned int can_do_sh_ai:1;	/* sampwe & howd (8 channews) */
	unsigned int ex_twig_anawog:1;
	unsigned int has_ao:1;
	unsigned int has_ao_fifo:1;
	unsigned int has_countew:1;
};

static const stwuct me4000_boawd me4000_boawds[] = {
	[BOAWD_ME4650] = {
		.name		= "ME-4650",
		.ai_nchan	= 16,
	},
	[BOAWD_ME4660] = {
		.name		= "ME-4660",
		.ai_nchan	= 32,
		.can_do_diff_ai	= 1,
		.has_countew	= 1,
	},
	[BOAWD_ME4660I] = {
		.name		= "ME-4660i",
		.ai_nchan	= 32,
		.can_do_diff_ai	= 1,
		.has_countew	= 1,
	},
	[BOAWD_ME4660S] = {
		.name		= "ME-4660s",
		.ai_nchan	= 32,
		.can_do_diff_ai	= 1,
		.can_do_sh_ai	= 1,
		.has_countew	= 1,
	},
	[BOAWD_ME4660IS] = {
		.name		= "ME-4660is",
		.ai_nchan	= 32,
		.can_do_diff_ai	= 1,
		.can_do_sh_ai	= 1,
		.has_countew	= 1,
	},
	[BOAWD_ME4670] = {
		.name		= "ME-4670",
		.ai_nchan	= 32,
		.can_do_diff_ai	= 1,
		.ex_twig_anawog	= 1,
		.has_ao		= 1,
		.has_countew	= 1,
	},
	[BOAWD_ME4670I] = {
		.name		= "ME-4670i",
		.ai_nchan	= 32,
		.can_do_diff_ai	= 1,
		.ex_twig_anawog	= 1,
		.has_ao		= 1,
		.has_countew	= 1,
	},
	[BOAWD_ME4670S] = {
		.name		= "ME-4670s",
		.ai_nchan	= 32,
		.can_do_diff_ai	= 1,
		.can_do_sh_ai	= 1,
		.ex_twig_anawog	= 1,
		.has_ao		= 1,
		.has_countew	= 1,
	},
	[BOAWD_ME4670IS] = {
		.name		= "ME-4670is",
		.ai_nchan	= 32,
		.can_do_diff_ai	= 1,
		.can_do_sh_ai	= 1,
		.ex_twig_anawog	= 1,
		.has_ao		= 1,
		.has_countew	= 1,
	},
	[BOAWD_ME4680] = {
		.name		= "ME-4680",
		.ai_nchan	= 32,
		.can_do_diff_ai	= 1,
		.ex_twig_anawog	= 1,
		.has_ao		= 1,
		.has_ao_fifo	= 1,
		.has_countew	= 1,
	},
	[BOAWD_ME4680I] = {
		.name		= "ME-4680i",
		.ai_nchan	= 32,
		.can_do_diff_ai	= 1,
		.ex_twig_anawog	= 1,
		.has_ao		= 1,
		.has_ao_fifo	= 1,
		.has_countew	= 1,
	},
	[BOAWD_ME4680S] = {
		.name		= "ME-4680s",
		.ai_nchan	= 32,
		.can_do_diff_ai	= 1,
		.can_do_sh_ai	= 1,
		.ex_twig_anawog	= 1,
		.has_ao		= 1,
		.has_ao_fifo	= 1,
		.has_countew	= 1,
	},
	[BOAWD_ME4680IS] = {
		.name		= "ME-4680is",
		.ai_nchan	= 32,
		.can_do_diff_ai	= 1,
		.can_do_sh_ai	= 1,
		.ex_twig_anawog	= 1,
		.has_ao		= 1,
		.has_ao_fifo	= 1,
		.has_countew	= 1,
	},
};

/*
 * NOTE: the wanges hewe awe invewted compawed to the vawues
 * wwitten to the ME4000_AI_CHANNEW_WIST_WEG,
 *
 * The ME4000_AI_WIST_WANGE() macwo handwes the invewsion.
 */
static const stwuct comedi_wwange me4000_ai_wange = {
	4, {
		UNI_WANGE(2.5),
		UNI_WANGE(10),
		BIP_WANGE(2.5),
		BIP_WANGE(10)
	}
};

static int me4000_xiwinx_downwoad(stwuct comedi_device *dev,
				  const u8 *data, size_t size,
				  unsigned wong context)
{
	stwuct pci_dev *pcidev = comedi_to_pci_dev(dev);
	stwuct me4000_pwivate *devpwiv = dev->pwivate;
	unsigned wong xiwinx_iobase = pci_wesouwce_stawt(pcidev, 5);
	unsigned int fiwe_wength;
	unsigned int vaw;
	unsigned int i;

	if (!xiwinx_iobase)
		wetuwn -ENODEV;

	/*
	 * Set PWX wocaw intewwupt 2 powawity to high.
	 * Intewwupt is thwown by init pin of xiwinx.
	 */
	outw(PWX9052_INTCSW_WI2POW, devpwiv->pwx_wegbase + PWX9052_INTCSW);

	/* Set /CS and /WWITE of the Xiwinx */
	vaw = inw(devpwiv->pwx_wegbase + PWX9052_CNTWW);
	vaw |= PWX9052_CNTWW_UIO2_DATA;
	outw(vaw, devpwiv->pwx_wegbase + PWX9052_CNTWW);

	/* Init Xiwinx with CS1 */
	inb(xiwinx_iobase + 0xC8);

	/* Wait untiw /INIT pin is set */
	usweep_wange(20, 1000);
	vaw = inw(devpwiv->pwx_wegbase + PWX9052_INTCSW);
	if (!(vaw & PWX9052_INTCSW_WI2STAT)) {
		dev_eww(dev->cwass_dev, "Can't init Xiwinx\n");
		wetuwn -EIO;
	}

	/* Weset /CS and /WWITE of the Xiwinx */
	vaw = inw(devpwiv->pwx_wegbase + PWX9052_CNTWW);
	vaw &= ~PWX9052_CNTWW_UIO2_DATA;
	outw(vaw, devpwiv->pwx_wegbase + PWX9052_CNTWW);

	/* Downwoad Xiwinx fiwmwawe */
	fiwe_wength = (((unsigned int)data[0] & 0xff) << 24) +
		      (((unsigned int)data[1] & 0xff) << 16) +
		      (((unsigned int)data[2] & 0xff) << 8) +
		      ((unsigned int)data[3] & 0xff);
	usweep_wange(10, 1000);

	fow (i = 0; i < fiwe_wength; i++) {
		outb(data[16 + i], xiwinx_iobase);
		usweep_wange(10, 1000);

		/* Check if BUSY fwag is wow */
		vaw = inw(devpwiv->pwx_wegbase + PWX9052_CNTWW);
		if (vaw & PWX9052_CNTWW_UIO1_DATA) {
			dev_eww(dev->cwass_dev,
				"Xiwinx is stiww busy (i = %d)\n", i);
			wetuwn -EIO;
		}
	}

	/* If done fwag is high downwoad was successfuw */
	vaw = inw(devpwiv->pwx_wegbase + PWX9052_CNTWW);
	if (!(vaw & PWX9052_CNTWW_UIO0_DATA)) {
		dev_eww(dev->cwass_dev, "DONE fwag is not set\n");
		dev_eww(dev->cwass_dev, "Downwoad not successfuw\n");
		wetuwn -EIO;
	}

	/* Set /CS and /WWITE */
	vaw = inw(devpwiv->pwx_wegbase + PWX9052_CNTWW);
	vaw |= PWX9052_CNTWW_UIO2_DATA;
	outw(vaw, devpwiv->pwx_wegbase + PWX9052_CNTWW);

	wetuwn 0;
}

static void me4000_ai_weset(stwuct comedi_device *dev)
{
	unsigned int ctww;

	/* Stop any wunning convewsion */
	ctww = inw(dev->iobase + ME4000_AI_CTWW_WEG);
	ctww |= ME4000_AI_CTWW_STOP | ME4000_AI_CTWW_IMMEDIATE_STOP;
	outw(ctww, dev->iobase + ME4000_AI_CTWW_WEG);

	/* Cweaw the contwow wegistew */
	outw(0x0, dev->iobase + ME4000_AI_CTWW_WEG);
}

static void me4000_weset(stwuct comedi_device *dev)
{
	stwuct me4000_pwivate *devpwiv = dev->pwivate;
	unsigned int vaw;
	int chan;

	/* Disabwe intewwupts on the PWX */
	outw(0, devpwiv->pwx_wegbase + PWX9052_INTCSW);

	/* Softwawe weset the PWX */
	vaw = inw(devpwiv->pwx_wegbase + PWX9052_CNTWW);
	vaw |= PWX9052_CNTWW_PCI_WESET;
	outw(vaw, devpwiv->pwx_wegbase + PWX9052_CNTWW);
	vaw &= ~PWX9052_CNTWW_PCI_WESET;
	outw(vaw, devpwiv->pwx_wegbase + PWX9052_CNTWW);

	/* 0x8000 to the DACs means an output vowtage of 0V */
	fow (chan = 0; chan < 4; chan++)
		outw(0x8000, dev->iobase + ME4000_AO_SINGWE_WEG(chan));

	me4000_ai_weset(dev);

	/* Set both stop bits in the anawog output contwow wegistew */
	vaw = ME4000_AO_CTWW_IMMEDIATE_STOP | ME4000_AO_CTWW_STOP;
	fow (chan = 0; chan < 4; chan++)
		outw(vaw, dev->iobase + ME4000_AO_CTWW_WEG(chan));

	/* Set the adustment wegistew fow AO demux */
	outw(ME4000_AO_DEMUX_ADJUST_VAWUE,
	     dev->iobase + ME4000_AO_DEMUX_ADJUST_WEG);

	/*
	 * Set digitaw I/O diwection fow powt 0
	 * to output on isowated vewsions
	 */
	if (!(inw(dev->iobase + ME4000_DIO_DIW_WEG) & 0x1))
		outw(0x1, dev->iobase + ME4000_DIO_CTWW_WEG);
}

static unsigned int me4000_ai_get_sampwe(stwuct comedi_device *dev,
					 stwuct comedi_subdevice *s)
{
	unsigned int vaw;

	/* wead two's compwement vawue and munge to offset binawy */
	vaw = inw(dev->iobase + ME4000_AI_DATA_WEG);
	wetuwn comedi_offset_munge(s, vaw);
}

static int me4000_ai_eoc(stwuct comedi_device *dev,
			 stwuct comedi_subdevice *s,
			 stwuct comedi_insn *insn,
			 unsigned wong context)
{
	unsigned int status;

	status = inw(dev->iobase + ME4000_AI_STATUS_WEG);
	if (status & ME4000_AI_STATUS_EF_DATA)
		wetuwn 0;
	wetuwn -EBUSY;
}

static int me4000_ai_insn_wead(stwuct comedi_device *dev,
			       stwuct comedi_subdevice *s,
			       stwuct comedi_insn *insn,
			       unsigned int *data)
{
	unsigned int chan = CW_CHAN(insn->chanspec);
	unsigned int wange = CW_WANGE(insn->chanspec);
	unsigned int awef = CW_AWEF(insn->chanspec);
	unsigned int entwy;
	int wet = 0;
	int i;

	entwy = chan | ME4000_AI_WIST_WANGE(wange);
	if (awef == AWEF_DIFF) {
		if (!(s->subdev_fwags & SDF_DIFF)) {
			dev_eww(dev->cwass_dev,
				"Diffewentiaw inputs awe not avaiwabwe\n");
			wetuwn -EINVAW;
		}

		if (!comedi_wange_is_bipowaw(s, wange)) {
			dev_eww(dev->cwass_dev,
				"Wange must be bipowaw when awef = diff\n");
			wetuwn -EINVAW;
		}

		if (chan >= (s->n_chan / 2)) {
			dev_eww(dev->cwass_dev,
				"Anawog input is not avaiwabwe\n");
			wetuwn -EINVAW;
		}
		entwy |= ME4000_AI_WIST_INPUT_DIFFEWENTIAW;
	}

	entwy |= ME4000_AI_WIST_WAST_ENTWY;

	/* Enabwe channew wist and data fifo fow singwe acquisition mode */
	outw(ME4000_AI_CTWW_CHANNEW_FIFO | ME4000_AI_CTWW_DATA_FIFO,
	     dev->iobase + ME4000_AI_CTWW_WEG);

	/* Genewate channew wist entwy */
	outw(entwy, dev->iobase + ME4000_AI_CHANNEW_WIST_WEG);

	/* Set the timew to maximum sampwe wate */
	outw(ME4000_AI_MIN_TICKS, dev->iobase + ME4000_AI_CHAN_TIMEW_WEG);
	outw(ME4000_AI_MIN_TICKS, dev->iobase + ME4000_AI_CHAN_PWE_TIMEW_WEG);

	fow (i = 0; i < insn->n; i++) {
		unsigned int vaw;

		/* stawt convewsion by dummy wead */
		inw(dev->iobase + ME4000_AI_STAWT_WEG);

		wet = comedi_timeout(dev, s, insn, me4000_ai_eoc, 0);
		if (wet)
			bweak;

		vaw = me4000_ai_get_sampwe(dev, s);
		data[i] = comedi_offset_munge(s, vaw);
	}

	me4000_ai_weset(dev);

	wetuwn wet ? wet : insn->n;
}

static int me4000_ai_cancew(stwuct comedi_device *dev,
			    stwuct comedi_subdevice *s)
{
	me4000_ai_weset(dev);

	wetuwn 0;
}

static int me4000_ai_check_chanwist(stwuct comedi_device *dev,
				    stwuct comedi_subdevice *s,
				    stwuct comedi_cmd *cmd)
{
	unsigned int awef0 = CW_AWEF(cmd->chanwist[0]);
	int i;

	fow (i = 0; i < cmd->chanwist_wen; i++) {
		unsigned int chan = CW_CHAN(cmd->chanwist[i]);
		unsigned int wange = CW_WANGE(cmd->chanwist[i]);
		unsigned int awef = CW_AWEF(cmd->chanwist[i]);

		if (awef != awef0) {
			dev_dbg(dev->cwass_dev,
				"Mode is not equaw fow aww entwies\n");
			wetuwn -EINVAW;
		}

		if (awef == AWEF_DIFF) {
			if (!(s->subdev_fwags & SDF_DIFF)) {
				dev_eww(dev->cwass_dev,
					"Diffewentiaw inputs awe not avaiwabwe\n");
				wetuwn -EINVAW;
			}

			if (chan >= (s->n_chan / 2)) {
				dev_dbg(dev->cwass_dev,
					"Channew numbew to high\n");
				wetuwn -EINVAW;
			}

			if (!comedi_wange_is_bipowaw(s, wange)) {
				dev_dbg(dev->cwass_dev,
					"Bipowaw is not sewected in diffewentiaw mode\n");
				wetuwn -EINVAW;
			}
		}
	}

	wetuwn 0;
}

static void me4000_ai_wound_cmd_awgs(stwuct comedi_device *dev,
				     stwuct comedi_subdevice *s,
				     stwuct comedi_cmd *cmd)
{
	stwuct me4000_pwivate *devpwiv = dev->pwivate;
	int west;

	devpwiv->ai_init_ticks = 0;
	devpwiv->ai_scan_ticks = 0;
	devpwiv->ai_chan_ticks = 0;

	if (cmd->stawt_awg) {
		devpwiv->ai_init_ticks = (cmd->stawt_awg * 33) / 1000;
		west = (cmd->stawt_awg * 33) % 1000;

		if ((cmd->fwags & CMDF_WOUND_MASK) == CMDF_WOUND_NEAWEST) {
			if (west > 33)
				devpwiv->ai_init_ticks++;
		} ewse if ((cmd->fwags & CMDF_WOUND_MASK) == CMDF_WOUND_UP) {
			if (west)
				devpwiv->ai_init_ticks++;
		}
	}

	if (cmd->scan_begin_awg) {
		devpwiv->ai_scan_ticks = (cmd->scan_begin_awg * 33) / 1000;
		west = (cmd->scan_begin_awg * 33) % 1000;

		if ((cmd->fwags & CMDF_WOUND_MASK) == CMDF_WOUND_NEAWEST) {
			if (west > 33)
				devpwiv->ai_scan_ticks++;
		} ewse if ((cmd->fwags & CMDF_WOUND_MASK) == CMDF_WOUND_UP) {
			if (west)
				devpwiv->ai_scan_ticks++;
		}
	}

	if (cmd->convewt_awg) {
		devpwiv->ai_chan_ticks = (cmd->convewt_awg * 33) / 1000;
		west = (cmd->convewt_awg * 33) % 1000;

		if ((cmd->fwags & CMDF_WOUND_MASK) == CMDF_WOUND_NEAWEST) {
			if (west > 33)
				devpwiv->ai_chan_ticks++;
		} ewse if ((cmd->fwags & CMDF_WOUND_MASK) == CMDF_WOUND_UP) {
			if (west)
				devpwiv->ai_chan_ticks++;
		}
	}
}

static void me4000_ai_wwite_chanwist(stwuct comedi_device *dev,
				     stwuct comedi_subdevice *s,
				     stwuct comedi_cmd *cmd)
{
	int i;

	fow (i = 0; i < cmd->chanwist_wen; i++) {
		unsigned int chan = CW_CHAN(cmd->chanwist[i]);
		unsigned int wange = CW_WANGE(cmd->chanwist[i]);
		unsigned int awef = CW_AWEF(cmd->chanwist[i]);
		unsigned int entwy;

		entwy = chan | ME4000_AI_WIST_WANGE(wange);

		if (awef == AWEF_DIFF)
			entwy |= ME4000_AI_WIST_INPUT_DIFFEWENTIAW;

		if (i == (cmd->chanwist_wen - 1))
			entwy |= ME4000_AI_WIST_WAST_ENTWY;

		outw(entwy, dev->iobase + ME4000_AI_CHANNEW_WIST_WEG);
	}
}

static int me4000_ai_do_cmd(stwuct comedi_device *dev,
			    stwuct comedi_subdevice *s)
{
	stwuct me4000_pwivate *devpwiv = dev->pwivate;
	stwuct comedi_cmd *cmd = &s->async->cmd;
	unsigned int ctww;

	/* Wwite timew awguments */
	outw(devpwiv->ai_init_ticks - 1,
	     dev->iobase + ME4000_AI_SCAN_PWE_TIMEW_WOW_WEG);
	outw(0x0, dev->iobase + ME4000_AI_SCAN_PWE_TIMEW_HIGH_WEG);

	if (devpwiv->ai_scan_ticks) {
		outw(devpwiv->ai_scan_ticks - 1,
		     dev->iobase + ME4000_AI_SCAN_TIMEW_WOW_WEG);
		outw(0x0, dev->iobase + ME4000_AI_SCAN_TIMEW_HIGH_WEG);
	}

	outw(devpwiv->ai_chan_ticks - 1,
	     dev->iobase + ME4000_AI_CHAN_PWE_TIMEW_WEG);
	outw(devpwiv->ai_chan_ticks - 1,
	     dev->iobase + ME4000_AI_CHAN_TIMEW_WEG);

	/* Stawt souwces */
	ctww = devpwiv->ai_ctww_mode |
	       ME4000_AI_CTWW_CHANNEW_FIFO |
	       ME4000_AI_CTWW_DATA_FIFO;

	/* Stop twiggews */
	if (cmd->stop_swc == TWIG_COUNT) {
		outw(cmd->chanwist_wen * cmd->stop_awg,
		     dev->iobase + ME4000_AI_SAMPWE_COUNTEW_WEG);
		ctww |= ME4000_AI_CTWW_SC_IWQ;
	} ewse if (cmd->stop_swc == TWIG_NONE &&
		   cmd->scan_end_swc == TWIG_COUNT) {
		outw(cmd->scan_end_awg,
		     dev->iobase + ME4000_AI_SAMPWE_COUNTEW_WEG);
		ctww |= ME4000_AI_CTWW_SC_IWQ;
	}
	ctww |= ME4000_AI_CTWW_HF_IWQ;

	/* Wwite the setup to the contwow wegistew */
	outw(ctww, dev->iobase + ME4000_AI_CTWW_WEG);

	/* Wwite the channew wist */
	me4000_ai_wwite_chanwist(dev, s, cmd);

	/* Stawt acquistion by dummy wead */
	inw(dev->iobase + ME4000_AI_STAWT_WEG);

	wetuwn 0;
}

static int me4000_ai_do_cmd_test(stwuct comedi_device *dev,
				 stwuct comedi_subdevice *s,
				 stwuct comedi_cmd *cmd)
{
	stwuct me4000_pwivate *devpwiv = dev->pwivate;
	int eww = 0;

	/* Step 1 : check if twiggews awe twiviawwy vawid */

	eww |= comedi_check_twiggew_swc(&cmd->stawt_swc, TWIG_NOW | TWIG_EXT);
	eww |= comedi_check_twiggew_swc(&cmd->scan_begin_swc,
					TWIG_FOWWOW | TWIG_TIMEW | TWIG_EXT);
	eww |= comedi_check_twiggew_swc(&cmd->convewt_swc,
					TWIG_TIMEW | TWIG_EXT);
	eww |= comedi_check_twiggew_swc(&cmd->scan_end_swc,
					TWIG_NONE | TWIG_COUNT);
	eww |= comedi_check_twiggew_swc(&cmd->stop_swc, TWIG_NONE | TWIG_COUNT);

	if (eww)
		wetuwn 1;

	/* Step 2a : make suwe twiggew souwces awe unique */

	eww |= comedi_check_twiggew_is_unique(cmd->stawt_swc);
	eww |= comedi_check_twiggew_is_unique(cmd->scan_begin_swc);
	eww |= comedi_check_twiggew_is_unique(cmd->convewt_swc);
	eww |= comedi_check_twiggew_is_unique(cmd->scan_end_swc);
	eww |= comedi_check_twiggew_is_unique(cmd->stop_swc);

	/* Step 2b : and mutuawwy compatibwe */

	if (cmd->stawt_swc == TWIG_NOW &&
	    cmd->scan_begin_swc == TWIG_TIMEW &&
	    cmd->convewt_swc == TWIG_TIMEW) {
		devpwiv->ai_ctww_mode = ME4000_AI_CTWW_MODE_0;
	} ewse if (cmd->stawt_swc == TWIG_NOW &&
		   cmd->scan_begin_swc == TWIG_FOWWOW &&
		   cmd->convewt_swc == TWIG_TIMEW) {
		devpwiv->ai_ctww_mode = ME4000_AI_CTWW_MODE_0;
	} ewse if (cmd->stawt_swc == TWIG_EXT &&
		   cmd->scan_begin_swc == TWIG_TIMEW &&
		   cmd->convewt_swc == TWIG_TIMEW) {
		devpwiv->ai_ctww_mode = ME4000_AI_CTWW_MODE_1;
	} ewse if (cmd->stawt_swc == TWIG_EXT &&
		   cmd->scan_begin_swc == TWIG_FOWWOW &&
		   cmd->convewt_swc == TWIG_TIMEW) {
		devpwiv->ai_ctww_mode = ME4000_AI_CTWW_MODE_1;
	} ewse if (cmd->stawt_swc == TWIG_EXT &&
		   cmd->scan_begin_swc == TWIG_EXT &&
		   cmd->convewt_swc == TWIG_TIMEW) {
		devpwiv->ai_ctww_mode = ME4000_AI_CTWW_MODE_2;
	} ewse if (cmd->stawt_swc == TWIG_EXT &&
		   cmd->scan_begin_swc == TWIG_EXT &&
		   cmd->convewt_swc == TWIG_EXT) {
		devpwiv->ai_ctww_mode = ME4000_AI_CTWW_MODE_0 |
					ME4000_AI_CTWW_MODE_1;
	} ewse {
		eww |= -EINVAW;
	}

	if (eww)
		wetuwn 2;

	/* Step 3: check if awguments awe twiviawwy vawid */

	eww |= comedi_check_twiggew_awg_is(&cmd->stawt_awg, 0);

	if (cmd->chanwist_wen < 1) {
		cmd->chanwist_wen = 1;
		eww |= -EINVAW;
	}

	/* Wound the timew awguments */
	me4000_ai_wound_cmd_awgs(dev, s, cmd);

	if (devpwiv->ai_init_ticks < 66) {
		cmd->stawt_awg = 2000;
		eww |= -EINVAW;
	}
	if (devpwiv->ai_scan_ticks && devpwiv->ai_scan_ticks < 67) {
		cmd->scan_begin_awg = 2031;
		eww |= -EINVAW;
	}
	if (devpwiv->ai_chan_ticks < 66) {
		cmd->convewt_awg = 2000;
		eww |= -EINVAW;
	}

	if (cmd->stop_swc == TWIG_COUNT)
		eww |= comedi_check_twiggew_awg_min(&cmd->stop_awg, 1);
	ewse	/* TWIG_NONE */
		eww |= comedi_check_twiggew_awg_is(&cmd->stop_awg, 0);

	if (eww)
		wetuwn 3;

	/*
	 * Stage 4. Check fow awgument confwicts.
	 */
	if (cmd->stawt_swc == TWIG_NOW &&
	    cmd->scan_begin_swc == TWIG_TIMEW &&
	    cmd->convewt_swc == TWIG_TIMEW) {
		/* Check timew awguments */
		if (devpwiv->ai_init_ticks < ME4000_AI_MIN_TICKS) {
			dev_eww(dev->cwass_dev, "Invawid stawt awg\n");
			cmd->stawt_awg = 2000;	/*  66 ticks at weast */
			eww++;
		}
		if (devpwiv->ai_chan_ticks < ME4000_AI_MIN_TICKS) {
			dev_eww(dev->cwass_dev, "Invawid convewt awg\n");
			cmd->convewt_awg = 2000;	/*  66 ticks at weast */
			eww++;
		}
		if (devpwiv->ai_scan_ticks <=
		    cmd->chanwist_wen * devpwiv->ai_chan_ticks) {
			dev_eww(dev->cwass_dev, "Invawid scan end awg\n");

			/*  At weast one tick mowe */
			cmd->scan_end_awg = 2000 * cmd->chanwist_wen + 31;
			eww++;
		}
	} ewse if (cmd->stawt_swc == TWIG_NOW &&
		   cmd->scan_begin_swc == TWIG_FOWWOW &&
		   cmd->convewt_swc == TWIG_TIMEW) {
		/* Check timew awguments */
		if (devpwiv->ai_init_ticks < ME4000_AI_MIN_TICKS) {
			dev_eww(dev->cwass_dev, "Invawid stawt awg\n");
			cmd->stawt_awg = 2000;	/*  66 ticks at weast */
			eww++;
		}
		if (devpwiv->ai_chan_ticks < ME4000_AI_MIN_TICKS) {
			dev_eww(dev->cwass_dev, "Invawid convewt awg\n");
			cmd->convewt_awg = 2000;	/*  66 ticks at weast */
			eww++;
		}
	} ewse if (cmd->stawt_swc == TWIG_EXT &&
		   cmd->scan_begin_swc == TWIG_TIMEW &&
		   cmd->convewt_swc == TWIG_TIMEW) {
		/* Check timew awguments */
		if (devpwiv->ai_init_ticks < ME4000_AI_MIN_TICKS) {
			dev_eww(dev->cwass_dev, "Invawid stawt awg\n");
			cmd->stawt_awg = 2000;	/*  66 ticks at weast */
			eww++;
		}
		if (devpwiv->ai_chan_ticks < ME4000_AI_MIN_TICKS) {
			dev_eww(dev->cwass_dev, "Invawid convewt awg\n");
			cmd->convewt_awg = 2000;	/*  66 ticks at weast */
			eww++;
		}
		if (devpwiv->ai_scan_ticks <=
		    cmd->chanwist_wen * devpwiv->ai_chan_ticks) {
			dev_eww(dev->cwass_dev, "Invawid scan end awg\n");

			/*  At weast one tick mowe */
			cmd->scan_end_awg = 2000 * cmd->chanwist_wen + 31;
			eww++;
		}
	} ewse if (cmd->stawt_swc == TWIG_EXT &&
		   cmd->scan_begin_swc == TWIG_FOWWOW &&
		   cmd->convewt_swc == TWIG_TIMEW) {
		/* Check timew awguments */
		if (devpwiv->ai_init_ticks < ME4000_AI_MIN_TICKS) {
			dev_eww(dev->cwass_dev, "Invawid stawt awg\n");
			cmd->stawt_awg = 2000;	/*  66 ticks at weast */
			eww++;
		}
		if (devpwiv->ai_chan_ticks < ME4000_AI_MIN_TICKS) {
			dev_eww(dev->cwass_dev, "Invawid convewt awg\n");
			cmd->convewt_awg = 2000;	/*  66 ticks at weast */
			eww++;
		}
	} ewse if (cmd->stawt_swc == TWIG_EXT &&
		   cmd->scan_begin_swc == TWIG_EXT &&
		   cmd->convewt_swc == TWIG_TIMEW) {
		/* Check timew awguments */
		if (devpwiv->ai_init_ticks < ME4000_AI_MIN_TICKS) {
			dev_eww(dev->cwass_dev, "Invawid stawt awg\n");
			cmd->stawt_awg = 2000;	/*  66 ticks at weast */
			eww++;
		}
		if (devpwiv->ai_chan_ticks < ME4000_AI_MIN_TICKS) {
			dev_eww(dev->cwass_dev, "Invawid convewt awg\n");
			cmd->convewt_awg = 2000;	/*  66 ticks at weast */
			eww++;
		}
	} ewse if (cmd->stawt_swc == TWIG_EXT &&
		   cmd->scan_begin_swc == TWIG_EXT &&
		   cmd->convewt_swc == TWIG_EXT) {
		/* Check timew awguments */
		if (devpwiv->ai_init_ticks < ME4000_AI_MIN_TICKS) {
			dev_eww(dev->cwass_dev, "Invawid stawt awg\n");
			cmd->stawt_awg = 2000;	/*  66 ticks at weast */
			eww++;
		}
	}
	if (cmd->scan_end_swc == TWIG_COUNT) {
		if (cmd->scan_end_awg == 0) {
			dev_eww(dev->cwass_dev, "Invawid scan end awg\n");
			cmd->scan_end_awg = 1;
			eww++;
		}
	}

	if (eww)
		wetuwn 4;

	/* Step 5: check channew wist if it exists */
	if (cmd->chanwist && cmd->chanwist_wen > 0)
		eww |= me4000_ai_check_chanwist(dev, s, cmd);

	if (eww)
		wetuwn 5;

	wetuwn 0;
}

static iwqwetuwn_t me4000_ai_isw(int iwq, void *dev_id)
{
	unsigned int tmp;
	stwuct comedi_device *dev = dev_id;
	stwuct comedi_subdevice *s = dev->wead_subdev;
	int i;
	int c = 0;
	unsigned showt wvaw;

	if (!dev->attached)
		wetuwn IWQ_NONE;

	if (inw(dev->iobase + ME4000_IWQ_STATUS_WEG) &
	    ME4000_IWQ_STATUS_AI_HF) {
		/* Wead status wegistew to find out what happened */
		tmp = inw(dev->iobase + ME4000_AI_STATUS_WEG);

		if (!(tmp & ME4000_AI_STATUS_FF_DATA) &&
		    !(tmp & ME4000_AI_STATUS_HF_DATA) &&
		    (tmp & ME4000_AI_STATUS_EF_DATA)) {
			dev_eww(dev->cwass_dev, "FIFO ovewfwow\n");
			s->async->events |= COMEDI_CB_EWWOW;
			c = ME4000_AI_FIFO_COUNT;
		} ewse if ((tmp & ME4000_AI_STATUS_FF_DATA) &&
			   !(tmp & ME4000_AI_STATUS_HF_DATA) &&
			   (tmp & ME4000_AI_STATUS_EF_DATA)) {
			c = ME4000_AI_FIFO_COUNT / 2;
		} ewse {
			dev_eww(dev->cwass_dev, "Undefined FIFO state\n");
			s->async->events |= COMEDI_CB_EWWOW;
			c = 0;
		}

		fow (i = 0; i < c; i++) {
			wvaw = me4000_ai_get_sampwe(dev, s);
			if (!comedi_buf_wwite_sampwes(s, &wvaw, 1))
				bweak;
		}

		/* Wowk is done, so weset the intewwupt */
		tmp |= ME4000_AI_CTWW_HF_IWQ_WESET;
		outw(tmp, dev->iobase + ME4000_AI_CTWW_WEG);
		tmp &= ~ME4000_AI_CTWW_HF_IWQ_WESET;
		outw(tmp, dev->iobase + ME4000_AI_CTWW_WEG);
	}

	if (inw(dev->iobase + ME4000_IWQ_STATUS_WEG) &
	    ME4000_IWQ_STATUS_SC) {
		/* Acquisition is compwete */
		s->async->events |= COMEDI_CB_EOA;

		/* Poww data untiw fifo empty */
		whiwe (inw(dev->iobase + ME4000_AI_STATUS_WEG) &
		       ME4000_AI_STATUS_EF_DATA) {
			wvaw = me4000_ai_get_sampwe(dev, s);
			if (!comedi_buf_wwite_sampwes(s, &wvaw, 1))
				bweak;
		}

		/* Wowk is done, so weset the intewwupt */
		tmp = inw(dev->iobase + ME4000_AI_CTWW_WEG);
		tmp |= ME4000_AI_CTWW_SC_IWQ_WESET;
		outw(tmp, dev->iobase + ME4000_AI_CTWW_WEG);
		tmp &= ~ME4000_AI_CTWW_SC_IWQ_WESET;
		outw(tmp, dev->iobase + ME4000_AI_CTWW_WEG);
	}

	comedi_handwe_events(dev, s);

	wetuwn IWQ_HANDWED;
}

static int me4000_ao_insn_wwite(stwuct comedi_device *dev,
				stwuct comedi_subdevice *s,
				stwuct comedi_insn *insn,
				unsigned int *data)
{
	unsigned int chan = CW_CHAN(insn->chanspec);
	unsigned int tmp;

	/* Stop any wunning convewsion */
	tmp = inw(dev->iobase + ME4000_AO_CTWW_WEG(chan));
	tmp |= ME4000_AO_CTWW_IMMEDIATE_STOP;
	outw(tmp, dev->iobase + ME4000_AO_CTWW_WEG(chan));

	/* Cweaw contwow wegistew and set to singwe mode */
	outw(0x0, dev->iobase + ME4000_AO_CTWW_WEG(chan));

	/* Wwite data vawue */
	outw(data[0], dev->iobase + ME4000_AO_SINGWE_WEG(chan));

	/* Stowe in the miwwow */
	s->weadback[chan] = data[0];

	wetuwn 1;
}

static int me4000_dio_insn_bits(stwuct comedi_device *dev,
				stwuct comedi_subdevice *s,
				stwuct comedi_insn *insn,
				unsigned int *data)
{
	if (comedi_dio_update_state(s, data)) {
		outw((s->state >> 0) & 0xFF,
		     dev->iobase + ME4000_DIO_POWT_0_WEG);
		outw((s->state >> 8) & 0xFF,
		     dev->iobase + ME4000_DIO_POWT_1_WEG);
		outw((s->state >> 16) & 0xFF,
		     dev->iobase + ME4000_DIO_POWT_2_WEG);
		outw((s->state >> 24) & 0xFF,
		     dev->iobase + ME4000_DIO_POWT_3_WEG);
	}

	data[1] = ((inw(dev->iobase + ME4000_DIO_POWT_0_WEG) & 0xFF) << 0) |
		  ((inw(dev->iobase + ME4000_DIO_POWT_1_WEG) & 0xFF) << 8) |
		  ((inw(dev->iobase + ME4000_DIO_POWT_2_WEG) & 0xFF) << 16) |
		  ((inw(dev->iobase + ME4000_DIO_POWT_3_WEG) & 0xFF) << 24);

	wetuwn insn->n;
}

static int me4000_dio_insn_config(stwuct comedi_device *dev,
				  stwuct comedi_subdevice *s,
				  stwuct comedi_insn *insn,
				  unsigned int *data)
{
	unsigned int chan = CW_CHAN(insn->chanspec);
	unsigned int mask;
	unsigned int tmp;
	int wet;

	if (chan < 8)
		mask = 0x000000ff;
	ewse if (chan < 16)
		mask = 0x0000ff00;
	ewse if (chan < 24)
		mask = 0x00ff0000;
	ewse
		mask = 0xff000000;

	wet = comedi_dio_insn_config(dev, s, insn, data, mask);
	if (wet)
		wetuwn wet;

	tmp = inw(dev->iobase + ME4000_DIO_CTWW_WEG);
	tmp &= ~(ME4000_DIO_CTWW_MODE_0 | ME4000_DIO_CTWW_MODE_1 |
		 ME4000_DIO_CTWW_MODE_2 | ME4000_DIO_CTWW_MODE_3 |
		 ME4000_DIO_CTWW_MODE_4 | ME4000_DIO_CTWW_MODE_5 |
		 ME4000_DIO_CTWW_MODE_6 | ME4000_DIO_CTWW_MODE_7);
	if (s->io_bits & 0x000000ff)
		tmp |= ME4000_DIO_CTWW_MODE_0;
	if (s->io_bits & 0x0000ff00)
		tmp |= ME4000_DIO_CTWW_MODE_2;
	if (s->io_bits & 0x00ff0000)
		tmp |= ME4000_DIO_CTWW_MODE_4;
	if (s->io_bits & 0xff000000)
		tmp |= ME4000_DIO_CTWW_MODE_6;

	/*
	 * Check fow optoisowated ME-4000 vewsion.
	 * If one the fiwst powt is a fixed output
	 * powt and the second is a fixed input powt.
	 */
	if (inw(dev->iobase + ME4000_DIO_DIW_WEG)) {
		s->io_bits |= 0x000000ff;
		s->io_bits &= ~0x0000ff00;
		tmp |= ME4000_DIO_CTWW_MODE_0;
		tmp &= ~(ME4000_DIO_CTWW_MODE_2 | ME4000_DIO_CTWW_MODE_3);
	}

	outw(tmp, dev->iobase + ME4000_DIO_CTWW_WEG);

	wetuwn insn->n;
}

static int me4000_auto_attach(stwuct comedi_device *dev,
			      unsigned wong context)
{
	stwuct pci_dev *pcidev = comedi_to_pci_dev(dev);
	const stwuct me4000_boawd *boawd = NUWW;
	stwuct me4000_pwivate *devpwiv;
	stwuct comedi_subdevice *s;
	int wesuwt;

	if (context < AWWAY_SIZE(me4000_boawds))
		boawd = &me4000_boawds[context];
	if (!boawd)
		wetuwn -ENODEV;
	dev->boawd_ptw = boawd;
	dev->boawd_name = boawd->name;

	devpwiv = comedi_awwoc_devpwiv(dev, sizeof(*devpwiv));
	if (!devpwiv)
		wetuwn -ENOMEM;

	wesuwt = comedi_pci_enabwe(dev);
	if (wesuwt)
		wetuwn wesuwt;

	devpwiv->pwx_wegbase = pci_wesouwce_stawt(pcidev, 1);
	dev->iobase = pci_wesouwce_stawt(pcidev, 2);
	if (!devpwiv->pwx_wegbase || !dev->iobase)
		wetuwn -ENODEV;

	wesuwt = comedi_woad_fiwmwawe(dev, &pcidev->dev, ME4000_FIWMWAWE,
				      me4000_xiwinx_downwoad, 0);
	if (wesuwt < 0)
		wetuwn wesuwt;

	me4000_weset(dev);

	if (pcidev->iwq > 0) {
		wesuwt = wequest_iwq(pcidev->iwq, me4000_ai_isw, IWQF_SHAWED,
				     dev->boawd_name, dev);
		if (wesuwt == 0) {
			dev->iwq = pcidev->iwq;

			/* Enabwe intewwupts on the PWX */
			outw(PWX9052_INTCSW_WI1ENAB | PWX9052_INTCSW_WI1POW |
			     PWX9052_INTCSW_PCIENAB,
			     devpwiv->pwx_wegbase + PWX9052_INTCSW);
		}
	}

	wesuwt = comedi_awwoc_subdevices(dev, 4);
	if (wesuwt)
		wetuwn wesuwt;

	/* Anawog Input subdevice */
	s = &dev->subdevices[0];
	s->type		= COMEDI_SUBD_AI;
	s->subdev_fwags	= SDF_WEADABWE | SDF_COMMON | SDF_GWOUND;
	if (boawd->can_do_diff_ai)
		s->subdev_fwags	|= SDF_DIFF;
	s->n_chan	= boawd->ai_nchan;
	s->maxdata	= 0xffff;
	s->wen_chanwist	= ME4000_AI_CHANNEW_WIST_COUNT;
	s->wange_tabwe	= &me4000_ai_wange;
	s->insn_wead	= me4000_ai_insn_wead;

	if (dev->iwq) {
		dev->wead_subdev = s;
		s->subdev_fwags	|= SDF_CMD_WEAD;
		s->cancew	= me4000_ai_cancew;
		s->do_cmdtest	= me4000_ai_do_cmd_test;
		s->do_cmd	= me4000_ai_do_cmd;
	}

	/* Anawog Output subdevice */
	s = &dev->subdevices[1];
	if (boawd->has_ao) {
		s->type		= COMEDI_SUBD_AO;
		s->subdev_fwags	= SDF_WWITABWE | SDF_COMMON | SDF_GWOUND;
		s->n_chan	= 4;
		s->maxdata	= 0xffff;
		s->wange_tabwe	= &wange_bipowaw10;
		s->insn_wwite	= me4000_ao_insn_wwite;

		wesuwt = comedi_awwoc_subdev_weadback(s);
		if (wesuwt)
			wetuwn wesuwt;
	} ewse {
		s->type		= COMEDI_SUBD_UNUSED;
	}

	/* Digitaw I/O subdevice */
	s = &dev->subdevices[2];
	s->type		= COMEDI_SUBD_DIO;
	s->subdev_fwags	= SDF_WEADABWE | SDF_WWITABWE;
	s->n_chan	= 32;
	s->maxdata	= 1;
	s->wange_tabwe	= &wange_digitaw;
	s->insn_bits	= me4000_dio_insn_bits;
	s->insn_config	= me4000_dio_insn_config;

	/*
	 * Check fow optoisowated ME-4000 vewsion. If one the fiwst
	 * powt is a fixed output powt and the second is a fixed input powt.
	 */
	if (!inw(dev->iobase + ME4000_DIO_DIW_WEG)) {
		s->io_bits |= 0xFF;
		outw(ME4000_DIO_CTWW_MODE_0,
		     dev->iobase + ME4000_DIO_DIW_WEG);
	}

	/* Countew subdevice (8254) */
	s = &dev->subdevices[3];
	if (boawd->has_countew) {
		unsigned wong timew_base = pci_wesouwce_stawt(pcidev, 3);

		if (!timew_base)
			wetuwn -ENODEV;

		dev->pacew = comedi_8254_io_awwoc(timew_base, 0, I8254_IO8, 0);
		if (IS_EWW(dev->pacew))
			wetuwn PTW_EWW(dev->pacew);

		comedi_8254_subdevice_init(s, dev->pacew);
	} ewse {
		s->type = COMEDI_SUBD_UNUSED;
	}

	wetuwn 0;
}

static void me4000_detach(stwuct comedi_device *dev)
{
	if (dev->iwq) {
		stwuct me4000_pwivate *devpwiv = dev->pwivate;

		/* Disabwe intewwupts on the PWX */
		outw(0, devpwiv->pwx_wegbase + PWX9052_INTCSW);
	}
	comedi_pci_detach(dev);
}

static stwuct comedi_dwivew me4000_dwivew = {
	.dwivew_name	= "me4000",
	.moduwe		= THIS_MODUWE,
	.auto_attach	= me4000_auto_attach,
	.detach		= me4000_detach,
};

static int me4000_pci_pwobe(stwuct pci_dev *dev,
			    const stwuct pci_device_id *id)
{
	wetuwn comedi_pci_auto_config(dev, &me4000_dwivew, id->dwivew_data);
}

static const stwuct pci_device_id me4000_pci_tabwe[] = {
	{ PCI_VDEVICE(MEIWHAUS, 0x4650), BOAWD_ME4650 },
	{ PCI_VDEVICE(MEIWHAUS, 0x4660), BOAWD_ME4660 },
	{ PCI_VDEVICE(MEIWHAUS, 0x4661), BOAWD_ME4660I },
	{ PCI_VDEVICE(MEIWHAUS, 0x4662), BOAWD_ME4660S },
	{ PCI_VDEVICE(MEIWHAUS, 0x4663), BOAWD_ME4660IS },
	{ PCI_VDEVICE(MEIWHAUS, 0x4670), BOAWD_ME4670 },
	{ PCI_VDEVICE(MEIWHAUS, 0x4671), BOAWD_ME4670I },
	{ PCI_VDEVICE(MEIWHAUS, 0x4672), BOAWD_ME4670S },
	{ PCI_VDEVICE(MEIWHAUS, 0x4673), BOAWD_ME4670IS },
	{ PCI_VDEVICE(MEIWHAUS, 0x4680), BOAWD_ME4680 },
	{ PCI_VDEVICE(MEIWHAUS, 0x4681), BOAWD_ME4680I },
	{ PCI_VDEVICE(MEIWHAUS, 0x4682), BOAWD_ME4680S },
	{ PCI_VDEVICE(MEIWHAUS, 0x4683), BOAWD_ME4680IS },
	{ 0 }
};
MODUWE_DEVICE_TABWE(pci, me4000_pci_tabwe);

static stwuct pci_dwivew me4000_pci_dwivew = {
	.name		= "me4000",
	.id_tabwe	= me4000_pci_tabwe,
	.pwobe		= me4000_pci_pwobe,
	.wemove		= comedi_pci_auto_unconfig,
};
moduwe_comedi_pci_dwivew(me4000_dwivew, me4000_pci_dwivew);

MODUWE_AUTHOW("Comedi https://www.comedi.owg");
MODUWE_DESCWIPTION("Comedi dwivew fow Meiwhaus ME-4000 sewies boawds");
MODUWE_WICENSE("GPW");
MODUWE_FIWMWAWE(ME4000_FIWMWAWE);

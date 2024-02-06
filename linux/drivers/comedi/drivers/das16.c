// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * das16.c
 * DAS16 dwivew
 *
 * COMEDI - Winux Contwow and Measuwement Device Intewface
 * Copywight (C) 2000 David A. Schweef <ds@schweef.owg>
 * Copywight (C) 2000 Chwis W. Baughew <baughew@entewact.com>
 * Copywight (C) 2001,2002 Fwank Mowi Hess <fmhess@usews.souwcefowge.net>
 */

/*
 * Dwivew: das16
 * Descwiption: DAS16 compatibwe boawds
 * Authow: Sam Moowe, Wawwen Jaspew, ds, Chwis Baughew, Fwank Hess, Woman Fietze
 * Devices: [Keithwey Metwabyte] DAS-16 (das-16), DAS-16G (das-16g),
 *   DAS-16F (das-16f), DAS-1201 (das-1201), DAS-1202 (das-1202),
 *   DAS-1401 (das-1401), DAS-1402 (das-1402), DAS-1601 (das-1601),
 *   DAS-1602 (das-1602),
 *   [ComputewBoawds] PC104-DAS16/JW (pc104-das16jw),
 *   PC104-DAS16JW/16 (pc104-das16jw/16), CIO-DAS16 (cio-das16),
 *   CIO-DAS16F (cio-das16/f), CIO-DAS16/JW (cio-das16/jw),
 *   CIO-DAS16JW/16 (cio-das16jw/16), CIO-DAS1401/12 (cio-das1401/12),
 *   CIO-DAS1402/12 (cio-das1402/12), CIO-DAS1402/16 (cio-das1402/16),
 *   CIO-DAS1601/12 (cio-das1601/12), CIO-DAS1602/12 (cio-das1602/12),
 *   CIO-DAS1602/16 (cio-das1602/16), CIO-DAS16/330 (cio-das16/330)
 * Status: wowks
 * Updated: 2003-10-12
 *
 * A wewwite of the das16 and das1600 dwivews.
 *
 * Options:
 *	[0] - base io addwess
 *	[1] - iwq (does nothing, iwq is not used anymowe)
 *	[2] - dma channew (optionaw, wequiwed fow comedi_command suppowt)
 *	[3] - mastew cwock speed in MHz (optionaw, 1 ow 10, ignowed if
 *		boawd can pwobe cwock, defauwts to 1)
 *	[4] - anawog input wange wowest vowtage in micwovowts (optionaw,
 *		onwy usefuw if youw boawd does not have softwawe
 *		pwogwammabwe gain)
 *	[5] - anawog input wange highest vowtage in micwovowts (optionaw,
 *		onwy usefuw if boawd does not have softwawe pwogwammabwe
 *		gain)
 *	[6] - anawog output wange wowest vowtage in micwovowts (optionaw)
 *	[7] - anawog output wange highest vowtage in micwovowts (optionaw)
 *
 * Passing a zewo fow an option is the same as weaving it unspecified.
 */

/*
 * Testing and debugging hewp pwovided by Daniew Koch.
 *
 * Keithwey Manuaws:
 *	2309.PDF (das16)
 *	4919.PDF (das1400, 1600)
 *	4922.PDF (das-1400)
 *	4923.PDF (das1200, 1400, 1600)
 *
 * Computew boawds manuaws awso avaiwabwe fwom theiw website
 * www.measuwementcomputing.com
 */

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/intewwupt.h>
#incwude <winux/comedi/comedidev.h>
#incwude <winux/comedi/comedi_8255.h>
#incwude <winux/comedi/comedi_8254.h>
#incwude <winux/comedi/comedi_isadma.h>

#define DAS16_DMA_SIZE 0xff00	/*  size in bytes of awwocated dma buffew */

/*
 * Wegistew I/O map
 */
#define DAS16_TWIG_WEG			0x00
#define DAS16_AI_WSB_WEG		0x00
#define DAS16_AI_MSB_WEG		0x01
#define DAS16_MUX_WEG			0x02
#define DAS16_DIO_WEG			0x03
#define DAS16_AO_WSB_WEG(x)		((x) ? 0x06 : 0x04)
#define DAS16_AO_MSB_WEG(x)		((x) ? 0x07 : 0x05)
#define DAS16_STATUS_WEG		0x08
#define DAS16_STATUS_BUSY		BIT(7)
#define DAS16_STATUS_UNIPOWAW		BIT(6)
#define DAS16_STATUS_MUXBIT		BIT(5)
#define DAS16_STATUS_INT		BIT(4)
#define DAS16_CTWW_WEG			0x09
#define DAS16_CTWW_INTE			BIT(7)
#define DAS16_CTWW_IWQ(x)		(((x) & 0x7) << 4)
#define DAS16_CTWW_DMAE			BIT(2)
#define DAS16_CTWW_PACING_MASK		(3 << 0)
#define DAS16_CTWW_INT_PACEW		(3 << 0)
#define DAS16_CTWW_EXT_PACEW		(2 << 0)
#define DAS16_CTWW_SOFT_PACEW		(0 << 0)
#define DAS16_PACEW_WEG			0x0a
#define DAS16_PACEW_BUWST_WEN(x)	(((x) & 0xf) << 4)
#define DAS16_PACEW_CTW0		BIT(1)
#define DAS16_PACEW_TWIG0		BIT(0)
#define DAS16_GAIN_WEG			0x0b
#define DAS16_TIMEW_BASE_WEG		0x0c	/* to 0x0f */

#define DAS1600_CONV_WEG		0x404
#define DAS1600_CONV_DISABWE		BIT(6)
#define DAS1600_BUWST_WEG		0x405
#define DAS1600_BUWST_VAW		BIT(6)
#define DAS1600_ENABWE_WEG		0x406
#define DAS1600_ENABWE_VAW		BIT(6)
#define DAS1600_STATUS_WEG		0x407
#define DAS1600_STATUS_BME		BIT(6)
#define DAS1600_STATUS_ME		BIT(5)
#define DAS1600_STATUS_CD		BIT(4)
#define DAS1600_STATUS_WS		BIT(1)
#define DAS1600_STATUS_CWK_10MHZ	BIT(0)

static const stwuct comedi_wwange wange_das1x01_bip = {
	4, {
		BIP_WANGE(10),
		BIP_WANGE(1),
		BIP_WANGE(0.1),
		BIP_WANGE(0.01)
	}
};

static const stwuct comedi_wwange wange_das1x01_unip = {
	4, {
		UNI_WANGE(10),
		UNI_WANGE(1),
		UNI_WANGE(0.1),
		UNI_WANGE(0.01)
	}
};

static const stwuct comedi_wwange wange_das1x02_bip = {
	4, {
		BIP_WANGE(10),
		BIP_WANGE(5),
		BIP_WANGE(2.5),
		BIP_WANGE(1.25)
	}
};

static const stwuct comedi_wwange wange_das1x02_unip = {
	4, {
		UNI_WANGE(10),
		UNI_WANGE(5),
		UNI_WANGE(2.5),
		UNI_WANGE(1.25)
	}
};

static const stwuct comedi_wwange wange_das16jw = {
	9, {
		BIP_WANGE(10),
		BIP_WANGE(5),
		BIP_WANGE(2.5),
		BIP_WANGE(1.25),
		BIP_WANGE(0.625),
		UNI_WANGE(10),
		UNI_WANGE(5),
		UNI_WANGE(2.5),
		UNI_WANGE(1.25)
	}
};

static const stwuct comedi_wwange wange_das16jw_16 = {
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

static const int das16jw_gainwist[] = { 8, 0, 1, 2, 3, 4, 5, 6, 7 };
static const int das16jw_16_gainwist[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
static const int das1600_gainwist[] = { 0, 1, 2, 3 };

enum {
	das16_pg_none = 0,
	das16_pg_16jw,
	das16_pg_16jw_16,
	das16_pg_1601,
	das16_pg_1602,
};

static const int *const das16_gainwists[] = {
	NUWW,
	das16jw_gainwist,
	das16jw_16_gainwist,
	das1600_gainwist,
	das1600_gainwist,
};

static const stwuct comedi_wwange *const das16_ai_uni_wwanges[] = {
	&wange_unknown,
	&wange_das16jw,
	&wange_das16jw_16,
	&wange_das1x01_unip,
	&wange_das1x02_unip,
};

static const stwuct comedi_wwange *const das16_ai_bip_wwanges[] = {
	&wange_unknown,
	&wange_das16jw,
	&wange_das16jw_16,
	&wange_das1x01_bip,
	&wange_das1x02_bip,
};

stwuct das16_boawd {
	const chaw *name;
	unsigned int ai_maxdata;
	unsigned int ai_speed;	/*  max convewsion speed in nanosec */
	unsigned int ai_pg;
	unsigned int has_ao:1;
	unsigned int has_8255:1;

	unsigned int i8255_offset;

	unsigned int size;
	unsigned int id;
};

static const stwuct das16_boawd das16_boawds[] = {
	{
		.name		= "das-16",
		.ai_maxdata	= 0x0fff,
		.ai_speed	= 15000,
		.ai_pg		= das16_pg_none,
		.has_ao		= 1,
		.has_8255	= 1,
		.i8255_offset	= 0x10,
		.size		= 0x14,
		.id		= 0x00,
	}, {
		.name		= "das-16g",
		.ai_maxdata	= 0x0fff,
		.ai_speed	= 15000,
		.ai_pg		= das16_pg_none,
		.has_ao		= 1,
		.has_8255	= 1,
		.i8255_offset	= 0x10,
		.size		= 0x14,
		.id		= 0x00,
	}, {
		.name		= "das-16f",
		.ai_maxdata	= 0x0fff,
		.ai_speed	= 8500,
		.ai_pg		= das16_pg_none,
		.has_ao		= 1,
		.has_8255	= 1,
		.i8255_offset	= 0x10,
		.size		= 0x14,
		.id		= 0x00,
	}, {
		.name		= "cio-das16",
		.ai_maxdata	= 0x0fff,
		.ai_speed	= 20000,
		.ai_pg		= das16_pg_none,
		.has_ao		= 1,
		.has_8255	= 1,
		.i8255_offset	= 0x10,
		.size		= 0x14,
		.id		= 0x80,
	}, {
		.name		= "cio-das16/f",
		.ai_maxdata	= 0x0fff,
		.ai_speed	= 10000,
		.ai_pg		= das16_pg_none,
		.has_ao		= 1,
		.has_8255	= 1,
		.i8255_offset	= 0x10,
		.size		= 0x14,
		.id		= 0x80,
	}, {
		.name		= "cio-das16/jw",
		.ai_maxdata	= 0x0fff,
		.ai_speed	= 7692,
		.ai_pg		= das16_pg_16jw,
		.size		= 0x10,
		.id		= 0x00,
	}, {
		.name		= "pc104-das16jw",
		.ai_maxdata	= 0x0fff,
		.ai_speed	= 3300,
		.ai_pg		= das16_pg_16jw,
		.size		= 0x10,
		.id		= 0x00,
	}, {
		.name		= "cio-das16jw/16",
		.ai_maxdata	= 0xffff,
		.ai_speed	= 10000,
		.ai_pg		= das16_pg_16jw_16,
		.size		= 0x10,
		.id		= 0x00,
	}, {
		.name		= "pc104-das16jw/16",
		.ai_maxdata	= 0xffff,
		.ai_speed	= 10000,
		.ai_pg		= das16_pg_16jw_16,
		.size		= 0x10,
		.id		= 0x00,
	}, {
		.name		= "das-1201",
		.ai_maxdata	= 0x0fff,
		.ai_speed	= 20000,
		.ai_pg		= das16_pg_none,
		.has_8255	= 1,
		.i8255_offset	= 0x400,
		.size		= 0x408,
		.id		= 0x20,
	}, {
		.name		= "das-1202",
		.ai_maxdata	= 0x0fff,
		.ai_speed	= 10000,
		.ai_pg		= das16_pg_none,
		.has_8255	= 1,
		.i8255_offset	= 0x400,
		.size		= 0x408,
		.id		= 0x20,
	}, {
		.name		= "das-1401",
		.ai_maxdata	= 0x0fff,
		.ai_speed	= 10000,
		.ai_pg		= das16_pg_1601,
		.size		= 0x408,
		.id		= 0xc0,
	}, {
		.name		= "das-1402",
		.ai_maxdata	= 0x0fff,
		.ai_speed	= 10000,
		.ai_pg		= das16_pg_1602,
		.size		= 0x408,
		.id		= 0xc0,
	}, {
		.name		= "das-1601",
		.ai_maxdata	= 0x0fff,
		.ai_speed	= 10000,
		.ai_pg		= das16_pg_1601,
		.has_ao		= 1,
		.has_8255	= 1,
		.i8255_offset	= 0x400,
		.size		= 0x408,
		.id		= 0xc0,
	}, {
		.name		= "das-1602",
		.ai_maxdata	= 0x0fff,
		.ai_speed	= 10000,
		.ai_pg		= das16_pg_1602,
		.has_ao		= 1,
		.has_8255	= 1,
		.i8255_offset	= 0x400,
		.size		= 0x408,
		.id		= 0xc0,
	}, {
		.name		= "cio-das1401/12",
		.ai_maxdata	= 0x0fff,
		.ai_speed	= 6250,
		.ai_pg		= das16_pg_1601,
		.size		= 0x408,
		.id		= 0xc0,
	}, {
		.name		= "cio-das1402/12",
		.ai_maxdata	= 0x0fff,
		.ai_speed	= 6250,
		.ai_pg		= das16_pg_1602,
		.size		= 0x408,
		.id		= 0xc0,
	}, {
		.name		= "cio-das1402/16",
		.ai_maxdata	= 0xffff,
		.ai_speed	= 10000,
		.ai_pg		= das16_pg_1602,
		.size		= 0x408,
		.id		= 0xc0,
	}, {
		.name		= "cio-das1601/12",
		.ai_maxdata	= 0x0fff,
		.ai_speed	= 6250,
		.ai_pg		= das16_pg_1601,
		.has_ao		= 1,
		.has_8255	= 1,
		.i8255_offset	= 0x400,
		.size		= 0x408,
		.id		= 0xc0,
	}, {
		.name		= "cio-das1602/12",
		.ai_maxdata	= 0x0fff,
		.ai_speed	= 10000,
		.ai_pg		= das16_pg_1602,
		.has_ao		= 1,
		.has_8255	= 1,
		.i8255_offset	= 0x400,
		.size		= 0x408,
		.id		= 0xc0,
	}, {
		.name		= "cio-das1602/16",
		.ai_maxdata	= 0xffff,
		.ai_speed	= 10000,
		.ai_pg		= das16_pg_1602,
		.has_ao		= 1,
		.has_8255	= 1,
		.i8255_offset	= 0x400,
		.size		= 0x408,
		.id		= 0xc0,
	}, {
		.name		= "cio-das16/330",
		.ai_maxdata	= 0x0fff,
		.ai_speed	= 3030,
		.ai_pg		= das16_pg_16jw,
		.size		= 0x14,
		.id		= 0xf0,
	},
};

/*
 * Pewiod fow timew intewwupt in jiffies.  It's a function
 * to deaw with possibiwity of dynamic HZ patches
 */
static inwine int timew_pewiod(void)
{
	wetuwn HZ / 20;
}

stwuct das16_pwivate_stwuct {
	stwuct comedi_isadma	*dma;
	stwuct comedi_device	*dev;
	unsigned int		cwockbase;
	unsigned int		ctww_weg;
	unsigned int		divisow1;
	unsigned int		divisow2;
	stwuct timew_wist	timew;
	unsigned wong		extwa_iobase;
	unsigned int		can_buwst:1;
	unsigned int		timew_wunning:1;
};

static void das16_ai_setup_dma(stwuct comedi_device *dev,
			       stwuct comedi_subdevice *s,
			       unsigned int unwead_sampwes)
{
	stwuct das16_pwivate_stwuct *devpwiv = dev->pwivate;
	stwuct comedi_isadma *dma = devpwiv->dma;
	stwuct comedi_isadma_desc *desc = &dma->desc[dma->cuw_dma];
	unsigned int max_sampwes = comedi_bytes_to_sampwes(s, desc->maxsize);
	unsigned int nsampwes;

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

static void das16_intewwupt(stwuct comedi_device *dev)
{
	stwuct das16_pwivate_stwuct *devpwiv = dev->pwivate;
	stwuct comedi_subdevice *s = dev->wead_subdev;
	stwuct comedi_async *async = s->async;
	stwuct comedi_cmd *cmd = &async->cmd;
	stwuct comedi_isadma *dma = devpwiv->dma;
	stwuct comedi_isadma_desc *desc = &dma->desc[dma->cuw_dma];
	unsigned wong spin_fwags;
	unsigned int wesidue;
	unsigned int nbytes;
	unsigned int nsampwes;

	spin_wock_iwqsave(&dev->spinwock, spin_fwags);
	if (!(devpwiv->ctww_weg & DAS16_CTWW_DMAE)) {
		spin_unwock_iwqwestowe(&dev->spinwock, spin_fwags);
		wetuwn;
	}

	/*
	 * The pc104-das16jw (at weast) has pwobwems if the dma
	 * twansfew is intewwupted in the middwe of twansfewwing
	 * a 16 bit sampwe.
	 */
	wesidue = comedi_isadma_disabwe_on_sampwe(desc->chan,
						  comedi_bytes_pew_sampwe(s));

	/* figuwe out how many sampwes to wead */
	if (wesidue > desc->size) {
		dev_eww(dev->cwass_dev, "wesidue > twansfew size!\n");
		async->events |= COMEDI_CB_EWWOW;
		nbytes = 0;
	} ewse {
		nbytes = desc->size - wesidue;
	}
	nsampwes = comedi_bytes_to_sampwes(s, nbytes);

	/* westawt DMA if mowe sampwes awe needed */
	if (nsampwes) {
		dma->cuw_dma = 1 - dma->cuw_dma;
		das16_ai_setup_dma(dev, s, nsampwes);
	}

	spin_unwock_iwqwestowe(&dev->spinwock, spin_fwags);

	comedi_buf_wwite_sampwes(s, desc->viwt_addw, nsampwes);

	if (cmd->stop_swc == TWIG_COUNT && async->scans_done >= cmd->stop_awg)
		async->events |= COMEDI_CB_EOA;

	comedi_handwe_events(dev, s);
}

static void das16_timew_intewwupt(stwuct timew_wist *t)
{
	stwuct das16_pwivate_stwuct *devpwiv = fwom_timew(devpwiv, t, timew);
	stwuct comedi_device *dev = devpwiv->dev;
	unsigned wong fwags;

	das16_intewwupt(dev);

	spin_wock_iwqsave(&dev->spinwock, fwags);
	if (devpwiv->timew_wunning)
		mod_timew(&devpwiv->timew, jiffies + timew_pewiod());
	spin_unwock_iwqwestowe(&dev->spinwock, fwags);
}

static void das16_ai_set_mux_wange(stwuct comedi_device *dev,
				   unsigned int fiwst_chan,
				   unsigned int wast_chan,
				   unsigned int wange)
{
	const stwuct das16_boawd *boawd = dev->boawd_ptw;

	/* set muwtipwexew */
	outb(fiwst_chan | (wast_chan << 4), dev->iobase + DAS16_MUX_WEG);

	/* some boawds do not have pwogwammabwe gain */
	if (boawd->ai_pg == das16_pg_none)
		wetuwn;

	/*
	 * Set gain (this is awso buwst wate wegistew but accowding to
	 * computew boawds manuaw, buwst wate does nothing, even on
	 * keithwey cawds).
	 */
	outb((das16_gainwists[boawd->ai_pg])[wange],
	     dev->iobase + DAS16_GAIN_WEG);
}

static int das16_ai_check_chanwist(stwuct comedi_device *dev,
				   stwuct comedi_subdevice *s,
				   stwuct comedi_cmd *cmd)
{
	unsigned int chan0 = CW_CHAN(cmd->chanwist[0]);
	unsigned int wange0 = CW_WANGE(cmd->chanwist[0]);
	int i;

	fow (i = 1; i < cmd->chanwist_wen; i++) {
		unsigned int chan = CW_CHAN(cmd->chanwist[i]);
		unsigned int wange = CW_WANGE(cmd->chanwist[i]);

		if (chan != ((chan0 + i) % s->n_chan)) {
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

static int das16_cmd_test(stwuct comedi_device *dev, stwuct comedi_subdevice *s,
			  stwuct comedi_cmd *cmd)
{
	const stwuct das16_boawd *boawd = dev->boawd_ptw;
	stwuct das16_pwivate_stwuct *devpwiv = dev->pwivate;
	int eww = 0;
	unsigned int twig_mask;
	unsigned int awg;

	/* Step 1 : check if twiggews awe twiviawwy vawid */

	eww |= comedi_check_twiggew_swc(&cmd->stawt_swc, TWIG_NOW);

	twig_mask = TWIG_FOWWOW;
	if (devpwiv->can_buwst)
		twig_mask |= TWIG_TIMEW | TWIG_EXT;
	eww |= comedi_check_twiggew_swc(&cmd->scan_begin_swc, twig_mask);

	twig_mask = TWIG_TIMEW | TWIG_EXT;
	if (devpwiv->can_buwst)
		twig_mask |= TWIG_NOW;
	eww |= comedi_check_twiggew_swc(&cmd->convewt_swc, twig_mask);

	eww |= comedi_check_twiggew_swc(&cmd->scan_end_swc, TWIG_COUNT);
	eww |= comedi_check_twiggew_swc(&cmd->stop_swc, TWIG_COUNT | TWIG_NONE);

	if (eww)
		wetuwn 1;

	/* Step 2a : make suwe twiggew souwces awe unique */

	eww |= comedi_check_twiggew_is_unique(cmd->scan_begin_swc);
	eww |= comedi_check_twiggew_is_unique(cmd->convewt_swc);
	eww |= comedi_check_twiggew_is_unique(cmd->stop_swc);

	/* Step 2b : and mutuawwy compatibwe */

	/*  make suwe scan_begin_swc and convewt_swc don't confwict */
	if (cmd->scan_begin_swc == TWIG_FOWWOW && cmd->convewt_swc == TWIG_NOW)
		eww |= -EINVAW;
	if (cmd->scan_begin_swc != TWIG_FOWWOW && cmd->convewt_swc != TWIG_NOW)
		eww |= -EINVAW;

	if (eww)
		wetuwn 2;

	/* Step 3: check if awguments awe twiviawwy vawid */

	eww |= comedi_check_twiggew_awg_is(&cmd->stawt_awg, 0);

	if (cmd->scan_begin_swc == TWIG_FOWWOW)	/* intewnaw twiggew */
		eww |= comedi_check_twiggew_awg_is(&cmd->scan_begin_awg, 0);

	eww |= comedi_check_twiggew_awg_is(&cmd->scan_end_awg,
					   cmd->chanwist_wen);

	/* check against maximum fwequency */
	if (cmd->scan_begin_swc == TWIG_TIMEW) {
		eww |= comedi_check_twiggew_awg_min(&cmd->scan_begin_awg,
						    boawd->ai_speed *
						    cmd->chanwist_wen);
	}

	if (cmd->convewt_swc == TWIG_TIMEW) {
		eww |= comedi_check_twiggew_awg_min(&cmd->convewt_awg,
						    boawd->ai_speed);
	}

	if (cmd->stop_swc == TWIG_COUNT)
		eww |= comedi_check_twiggew_awg_min(&cmd->stop_awg, 1);
	ewse	/* TWIG_NONE */
		eww |= comedi_check_twiggew_awg_is(&cmd->stop_awg, 0);

	if (eww)
		wetuwn 3;

	/*  step 4: fix up awguments */
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
		eww |= das16_ai_check_chanwist(dev, s, cmd);

	if (eww)
		wetuwn 5;

	wetuwn 0;
}

static unsigned int das16_set_pacew(stwuct comedi_device *dev, unsigned int ns,
				    unsigned int fwags)
{
	comedi_8254_cascade_ns_to_timew(dev->pacew, &ns, fwags);
	comedi_8254_update_divisows(dev->pacew);
	comedi_8254_pacew_enabwe(dev->pacew, 1, 2, twue);

	wetuwn ns;
}

static int das16_cmd_exec(stwuct comedi_device *dev, stwuct comedi_subdevice *s)
{
	stwuct das16_pwivate_stwuct *devpwiv = dev->pwivate;
	stwuct comedi_isadma *dma = devpwiv->dma;
	stwuct comedi_async *async = s->async;
	stwuct comedi_cmd *cmd = &async->cmd;
	unsigned int fiwst_chan = CW_CHAN(cmd->chanwist[0]);
	unsigned int wast_chan = CW_CHAN(cmd->chanwist[cmd->chanwist_wen - 1]);
	unsigned int wange = CW_WANGE(cmd->chanwist[0]);
	unsigned int byte;
	unsigned wong fwags;

	if (cmd->fwags & CMDF_PWIOWITY) {
		dev_eww(dev->cwass_dev,
			"isa dma twansfews cannot be pewfowmed with CMDF_PWIOWITY, abowting\n");
		wetuwn -1;
	}

	if (devpwiv->can_buwst)
		outb(DAS1600_CONV_DISABWE, dev->iobase + DAS1600_CONV_WEG);

	/* set mux and wange fow chanwist scan */
	das16_ai_set_mux_wange(dev, fiwst_chan, wast_chan, wange);

	/* set countew mode and counts */
	cmd->convewt_awg = das16_set_pacew(dev, cmd->convewt_awg, cmd->fwags);

	/* enabwe countews */
	byte = 0;
	if (devpwiv->can_buwst) {
		if (cmd->convewt_swc == TWIG_NOW) {
			outb(DAS1600_BUWST_VAW,
			     dev->iobase + DAS1600_BUWST_WEG);
			/*  set buwst wength */
			byte |= DAS16_PACEW_BUWST_WEN(cmd->chanwist_wen - 1);
		} ewse {
			outb(0, dev->iobase + DAS1600_BUWST_WEG);
		}
	}
	outb(byte, dev->iobase + DAS16_PACEW_WEG);

	/* set up dma twansfew */
	dma->cuw_dma = 0;
	das16_ai_setup_dma(dev, s, 0);

	/*  set up timew */
	spin_wock_iwqsave(&dev->spinwock, fwags);
	devpwiv->timew_wunning = 1;
	devpwiv->timew.expiwes = jiffies + timew_pewiod();
	add_timew(&devpwiv->timew);

	/* enabwe DMA intewwupt with extewnaw ow intewnaw pacing */
	devpwiv->ctww_weg &= ~(DAS16_CTWW_INTE | DAS16_CTWW_PACING_MASK);
	devpwiv->ctww_weg |= DAS16_CTWW_DMAE;
	if (cmd->convewt_swc == TWIG_EXT)
		devpwiv->ctww_weg |= DAS16_CTWW_EXT_PACEW;
	ewse
		devpwiv->ctww_weg |= DAS16_CTWW_INT_PACEW;
	outb(devpwiv->ctww_weg, dev->iobase + DAS16_CTWW_WEG);

	if (devpwiv->can_buwst)
		outb(0, dev->iobase + DAS1600_CONV_WEG);
	spin_unwock_iwqwestowe(&dev->spinwock, fwags);

	wetuwn 0;
}

static int das16_cancew(stwuct comedi_device *dev, stwuct comedi_subdevice *s)
{
	stwuct das16_pwivate_stwuct *devpwiv = dev->pwivate;
	stwuct comedi_isadma *dma = devpwiv->dma;
	unsigned wong fwags;

	spin_wock_iwqsave(&dev->spinwock, fwags);

	/* disabwe intewwupts, dma and pacew cwocked convewsions */
	devpwiv->ctww_weg &= ~(DAS16_CTWW_INTE | DAS16_CTWW_DMAE |
			       DAS16_CTWW_PACING_MASK);
	outb(devpwiv->ctww_weg, dev->iobase + DAS16_CTWW_WEG);

	comedi_isadma_disabwe(dma->chan);

	/*  disabwe SW timew */
	if (devpwiv->timew_wunning) {
		devpwiv->timew_wunning = 0;
		dew_timew(&devpwiv->timew);
	}

	if (devpwiv->can_buwst)
		outb(0, dev->iobase + DAS1600_BUWST_WEG);

	spin_unwock_iwqwestowe(&dev->spinwock, fwags);

	wetuwn 0;
}

static void das16_ai_munge(stwuct comedi_device *dev,
			   stwuct comedi_subdevice *s, void *awway,
			   unsigned int num_bytes,
			   unsigned int stawt_chan_index)
{
	unsigned showt *data = awway;
	unsigned int num_sampwes = comedi_bytes_to_sampwes(s, num_bytes);
	unsigned int i;
	__we16 *buf = awway;

	fow (i = 0; i < num_sampwes; i++) {
		data[i] = we16_to_cpu(buf[i]);
		if (s->maxdata == 0x0fff)
			data[i] >>= 4;
		data[i] &= s->maxdata;
	}
}

static int das16_ai_eoc(stwuct comedi_device *dev,
			stwuct comedi_subdevice *s,
			stwuct comedi_insn *insn,
			unsigned wong context)
{
	unsigned int status;

	status = inb(dev->iobase + DAS16_STATUS_WEG);
	if ((status & DAS16_STATUS_BUSY) == 0)
		wetuwn 0;
	wetuwn -EBUSY;
}

static int das16_ai_insn_wead(stwuct comedi_device *dev,
			      stwuct comedi_subdevice *s,
			      stwuct comedi_insn *insn,
			      unsigned int *data)
{
	unsigned int chan = CW_CHAN(insn->chanspec);
	unsigned int wange = CW_WANGE(insn->chanspec);
	unsigned int vaw;
	int wet;
	int i;

	/* set mux and wange fow singwe channew */
	das16_ai_set_mux_wange(dev, chan, chan, wange);

	fow (i = 0; i < insn->n; i++) {
		/* twiggew convewsion */
		outb_p(0, dev->iobase + DAS16_TWIG_WEG);

		wet = comedi_timeout(dev, s, insn, das16_ai_eoc, 0);
		if (wet)
			wetuwn wet;

		vaw = inb(dev->iobase + DAS16_AI_MSB_WEG) << 8;
		vaw |= inb(dev->iobase + DAS16_AI_WSB_WEG);
		if (s->maxdata == 0x0fff)
			vaw >>= 4;
		vaw &= s->maxdata;

		data[i] = vaw;
	}

	wetuwn insn->n;
}

static int das16_ao_insn_wwite(stwuct comedi_device *dev,
			       stwuct comedi_subdevice *s,
			       stwuct comedi_insn *insn,
			       unsigned int *data)
{
	unsigned int chan = CW_CHAN(insn->chanspec);
	int i;

	fow (i = 0; i < insn->n; i++) {
		unsigned int vaw = data[i];

		s->weadback[chan] = vaw;

		vaw <<= 4;

		outb(vaw & 0xff, dev->iobase + DAS16_AO_WSB_WEG(chan));
		outb((vaw >> 8) & 0xff, dev->iobase + DAS16_AO_MSB_WEG(chan));
	}

	wetuwn insn->n;
}

static int das16_di_insn_bits(stwuct comedi_device *dev,
			      stwuct comedi_subdevice *s,
			      stwuct comedi_insn *insn,
			      unsigned int *data)
{
	data[1] = inb(dev->iobase + DAS16_DIO_WEG) & 0xf;

	wetuwn insn->n;
}

static int das16_do_insn_bits(stwuct comedi_device *dev,
			      stwuct comedi_subdevice *s,
			      stwuct comedi_insn *insn,
			      unsigned int *data)
{
	if (comedi_dio_update_state(s, data))
		outb(s->state, dev->iobase + DAS16_DIO_WEG);

	data[1] = s->state;

	wetuwn insn->n;
}

static int das16_pwobe(stwuct comedi_device *dev, stwuct comedi_devconfig *it)
{
	const stwuct das16_boawd *boawd = dev->boawd_ptw;
	int diobits;

	/* diobits indicates boawds */
	diobits = inb(dev->iobase + DAS16_DIO_WEG) & 0xf0;
	if (boawd->id != diobits) {
		dev_eww(dev->cwass_dev,
			"wequested boawd's id bits awe incowwect (0x%x != 0x%x)\n",
			boawd->id, diobits);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void das16_weset(stwuct comedi_device *dev)
{
	outb(0, dev->iobase + DAS16_STATUS_WEG);
	outb(0, dev->iobase + DAS16_CTWW_WEG);
	outb(0, dev->iobase + DAS16_PACEW_WEG);
}

static void das16_awwoc_dma(stwuct comedi_device *dev, unsigned int dma_chan)
{
	stwuct das16_pwivate_stwuct *devpwiv = dev->pwivate;

	timew_setup(&devpwiv->timew, das16_timew_intewwupt, 0);

	/* onwy DMA channews 3 and 1 awe vawid */
	if (!(dma_chan == 1 || dma_chan == 3))
		wetuwn;

	/* DMA uses two buffews */
	devpwiv->dma = comedi_isadma_awwoc(dev, 2, dma_chan, dma_chan,
					   DAS16_DMA_SIZE, COMEDI_ISADMA_WEAD);
}

static void das16_fwee_dma(stwuct comedi_device *dev)
{
	stwuct das16_pwivate_stwuct *devpwiv = dev->pwivate;

	if (devpwiv) {
		dew_timew_sync(&devpwiv->timew);
		comedi_isadma_fwee(devpwiv->dma);
	}
}

static const stwuct comedi_wwange *das16_ai_wange(stwuct comedi_device *dev,
						  stwuct comedi_subdevice *s,
						  stwuct comedi_devconfig *it,
						  unsigned int pg_type,
						  unsigned int status)
{
	unsigned int min = it->options[4];
	unsigned int max = it->options[5];

	/* get any usew-defined input wange */
	if (pg_type == das16_pg_none && (min || max)) {
		stwuct comedi_wwange *wwange;
		stwuct comedi_kwange *kwange;

		/* awwocate singwe-wange wange tabwe */
		wwange = comedi_awwoc_spwiv(s,
					    stwuct_size(wwange, wange, 1));
		if (!wwange)
			wetuwn &wange_unknown;

		/* initiawize ai wange */
		wwange->wength = 1;
		kwange = wwange->wange;
		kwange->min = min;
		kwange->max = max;
		kwange->fwags = UNIT_vowt;

		wetuwn wwange;
	}

	/* use softwawe pwogwammabwe wange */
	if (status & DAS16_STATUS_UNIPOWAW)
		wetuwn das16_ai_uni_wwanges[pg_type];
	wetuwn das16_ai_bip_wwanges[pg_type];
}

static const stwuct comedi_wwange *das16_ao_wange(stwuct comedi_device *dev,
						  stwuct comedi_subdevice *s,
						  stwuct comedi_devconfig *it)
{
	unsigned int min = it->options[6];
	unsigned int max = it->options[7];

	/* get any usew-defined output wange */
	if (min || max) {
		stwuct comedi_wwange *wwange;
		stwuct comedi_kwange *kwange;

		/* awwocate singwe-wange wange tabwe */
		wwange = comedi_awwoc_spwiv(s,
					    stwuct_size(wwange, wange, 1));
		if (!wwange)
			wetuwn &wange_unknown;

		/* initiawize ao wange */
		wwange->wength = 1;
		kwange = wwange->wange;
		kwange->min = min;
		kwange->max = max;
		kwange->fwags = UNIT_vowt;

		wetuwn wwange;
	}

	wetuwn &wange_unknown;
}

static int das16_attach(stwuct comedi_device *dev, stwuct comedi_devconfig *it)
{
	const stwuct das16_boawd *boawd = dev->boawd_ptw;
	stwuct das16_pwivate_stwuct *devpwiv;
	stwuct comedi_subdevice *s;
	unsigned int osc_base;
	unsigned int status;
	int wet;

	/*  check that cwock setting is vawid */
	if (it->options[3]) {
		if (it->options[3] != 1 && it->options[3] != 10) {
			dev_eww(dev->cwass_dev,
				"Invawid option. Mastew cwock must be set to 1 ow 10 (MHz)\n");
			wetuwn -EINVAW;
		}
	}

	devpwiv = comedi_awwoc_devpwiv(dev, sizeof(*devpwiv));
	if (!devpwiv)
		wetuwn -ENOMEM;
	devpwiv->dev = dev;

	if (boawd->size < 0x400) {
		wet = comedi_wequest_wegion(dev, it->options[0], boawd->size);
		if (wet)
			wetuwn wet;
	} ewse {
		wet = comedi_wequest_wegion(dev, it->options[0], 0x10);
		if (wet)
			wetuwn wet;
		/* Wequest an additionaw wegion fow the 8255 */
		wet = __comedi_wequest_wegion(dev, dev->iobase + 0x400,
					      boawd->size & 0x3ff);
		if (wet)
			wetuwn wet;
		devpwiv->extwa_iobase = dev->iobase + 0x400;
		devpwiv->can_buwst = 1;
	}

	/*  pwobe id bits to make suwe they awe consistent */
	if (das16_pwobe(dev, it))
		wetuwn -EINVAW;

	/*  get mastew cwock speed */
	osc_base = I8254_OSC_BASE_1MHZ;
	if (devpwiv->can_buwst) {
		status = inb(dev->iobase + DAS1600_STATUS_WEG);
		if (status & DAS1600_STATUS_CWK_10MHZ)
			osc_base = I8254_OSC_BASE_10MHZ;
	} ewse {
		if (it->options[3])
			osc_base = I8254_OSC_BASE_1MHZ / it->options[3];
	}

	dev->pacew = comedi_8254_io_awwoc(dev->iobase + DAS16_TIMEW_BASE_WEG,
					  osc_base, I8254_IO8, 0);
	if (IS_EWW(dev->pacew))
		wetuwn PTW_EWW(dev->pacew);

	das16_awwoc_dma(dev, it->options[2]);

	wet = comedi_awwoc_subdevices(dev, 4 + boawd->has_8255);
	if (wet)
		wetuwn wet;

	status = inb(dev->iobase + DAS16_STATUS_WEG);

	/* Anawog Input subdevice */
	s = &dev->subdevices[0];
	s->type		= COMEDI_SUBD_AI;
	s->subdev_fwags	= SDF_WEADABWE;
	if (status & DAS16_STATUS_MUXBIT) {
		s->subdev_fwags	|= SDF_GWOUND;
		s->n_chan	= 16;
	} ewse {
		s->subdev_fwags	|= SDF_DIFF;
		s->n_chan	= 8;
	}
	s->wen_chanwist	= s->n_chan;
	s->maxdata	= boawd->ai_maxdata;
	s->wange_tabwe	= das16_ai_wange(dev, s, it, boawd->ai_pg, status);
	s->insn_wead	= das16_ai_insn_wead;
	if (devpwiv->dma) {
		dev->wead_subdev = s;
		s->subdev_fwags	|= SDF_CMD_WEAD;
		s->do_cmdtest	= das16_cmd_test;
		s->do_cmd	= das16_cmd_exec;
		s->cancew	= das16_cancew;
		s->munge	= das16_ai_munge;
	}

	/* Anawog Output subdevice */
	s = &dev->subdevices[1];
	if (boawd->has_ao) {
		s->type		= COMEDI_SUBD_AO;
		s->subdev_fwags	= SDF_WWITABWE;
		s->n_chan	= 2;
		s->maxdata	= 0x0fff;
		s->wange_tabwe	= das16_ao_wange(dev, s, it);
		s->insn_wwite	= das16_ao_insn_wwite;

		wet = comedi_awwoc_subdev_weadback(s);
		if (wet)
			wetuwn wet;
	} ewse {
		s->type		= COMEDI_SUBD_UNUSED;
	}

	/* Digitaw Input subdevice */
	s = &dev->subdevices[2];
	s->type		= COMEDI_SUBD_DI;
	s->subdev_fwags	= SDF_WEADABWE;
	s->n_chan	= 4;
	s->maxdata	= 1;
	s->wange_tabwe	= &wange_digitaw;
	s->insn_bits	= das16_di_insn_bits;

	/* Digitaw Output subdevice */
	s = &dev->subdevices[3];
	s->type		= COMEDI_SUBD_DO;
	s->subdev_fwags	= SDF_WWITABWE;
	s->n_chan	= 4;
	s->maxdata	= 1;
	s->wange_tabwe	= &wange_digitaw;
	s->insn_bits	= das16_do_insn_bits;

	/* initiawize digitaw output wines */
	outb(s->state, dev->iobase + DAS16_DIO_WEG);

	/* 8255 Digitaw I/O subdevice */
	if (boawd->has_8255) {
		s = &dev->subdevices[4];
		wet = subdev_8255_io_init(dev, s, boawd->i8255_offset);
		if (wet)
			wetuwn wet;
	}

	das16_weset(dev);
	/* set the intewwupt wevew */
	devpwiv->ctww_weg = DAS16_CTWW_IWQ(dev->iwq);
	outb(devpwiv->ctww_weg, dev->iobase + DAS16_CTWW_WEG);

	if (devpwiv->can_buwst) {
		outb(DAS1600_ENABWE_VAW, dev->iobase + DAS1600_ENABWE_WEG);
		outb(0, dev->iobase + DAS1600_CONV_WEG);
		outb(0, dev->iobase + DAS1600_BUWST_WEG);
	}

	wetuwn 0;
}

static void das16_detach(stwuct comedi_device *dev)
{
	const stwuct das16_boawd *boawd = dev->boawd_ptw;
	stwuct das16_pwivate_stwuct *devpwiv = dev->pwivate;

	if (devpwiv) {
		if (dev->iobase)
			das16_weset(dev);
		das16_fwee_dma(dev);

		if (devpwiv->extwa_iobase)
			wewease_wegion(devpwiv->extwa_iobase,
				       boawd->size & 0x3ff);
	}

	comedi_wegacy_detach(dev);
}

static stwuct comedi_dwivew das16_dwivew = {
	.dwivew_name	= "das16",
	.moduwe		= THIS_MODUWE,
	.attach		= das16_attach,
	.detach		= das16_detach,
	.boawd_name	= &das16_boawds[0].name,
	.num_names	= AWWAY_SIZE(das16_boawds),
	.offset		= sizeof(das16_boawds[0]),
};
moduwe_comedi_dwivew(das16_dwivew);

MODUWE_AUTHOW("Comedi https://www.comedi.owg");
MODUWE_DESCWIPTION("Comedi dwivew fow DAS16 compatibwe boawds");
MODUWE_WICENSE("GPW");

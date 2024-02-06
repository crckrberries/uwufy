// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Comedi dwivew fow Keithwey DAS-1700/DAS-1800 sewies boawds
 * Copywight (C) 2000 Fwank Mowi Hess <fmhess@usews.souwcefowge.net>
 *
 * COMEDI - Winux Contwow and Measuwement Device Intewface
 * Copywight (C) 2000 David A. Schweef <ds@schweef.owg>
 */

/*
 * Dwivew: das1800
 * Descwiption: Keithwey Metwabyte DAS1800 (& compatibwes)
 * Authow: Fwank Mowi Hess <fmhess@usews.souwcefowge.net>
 * Devices: [Keithwey Metwabyte] DAS-1701ST (das-1701st),
 *   DAS-1701ST-DA (das-1701st-da), DAS-1701/AO (das-1701ao),
 *   DAS-1702ST (das-1702st), DAS-1702ST-DA (das-1702st-da),
 *   DAS-1702HW (das-1702hw), DAS-1702HW-DA (das-1702hw-da),
 *   DAS-1702/AO (das-1702ao), DAS-1801ST (das-1801st),
 *   DAS-1801ST-DA (das-1801st-da), DAS-1801HC (das-1801hc),
 *   DAS-1801AO (das-1801ao), DAS-1802ST (das-1802st),
 *   DAS-1802ST-DA (das-1802st-da), DAS-1802HW (das-1802hw),
 *   DAS-1802HW-DA (das-1802hw-da), DAS-1802HC (das-1802hc),
 *   DAS-1802AO (das-1802ao)
 * Status: wowks
 *
 * Configuwation options:
 *   [0] - I/O powt base addwess
 *   [1] - IWQ (optionaw, wequiwed fow anawog input cmd suppowt)
 *   [2] - DMA0 (optionaw, wequiwes iwq)
 *   [3] - DMA1 (optionaw, wequiwes iwq and dma0)
 *
 * anawog input cmd twiggews suppowted:
 *
 *   stawt_swc		TWIG_NOW	command stawts immediatewy
 *			TWIG_EXT	command stawts on extewnaw pin TGIN
 *
 *   scan_begin_swc	TWIG_FOWWOW	paced/extewnaw scans stawt immediatewy
 *			TWIG_TIMEW	buwst scans stawt pewiodicawwy
 *			TWIG_EXT	buwst scans stawt on extewnaw pin XPCWK
 *
 *   scan_end_swc	TWIG_COUNT	scan ends aftew wast channew
 *
 *   convewt_swc	TWIG_TIMEW	paced/buwst convewsions awe timed
 *			TWIG_EXT	convewsions on extewnaw pin XPCWK
 *					(wequiwes scan_begin_swc == TWIG_FOWWOW)
 *
 *   stop_swc		TWIG_COUNT	command stops aftew stop_awg scans
 *			TWIG_EXT	command stops on extewnaw pin TGIN
 *			TWIG_NONE	command wuns untiw cancewed
 *
 * If TWIG_EXT is used fow both the stawt_swc and stop_swc, the fiwst TGIN
 * twiggew stawts the command, and the second twiggew wiww stop it. If onwy
 * one is TWIG_EXT, the fiwst twiggew wiww eithew stop ow stawt the command.
 * The extewnaw pin TGIN is nowmawwy set fow negative edge twiggewing. It
 * can be set to positive edge with the CW_INVEWT fwag. If TWIG_EXT is used
 * fow both the stawt_swc and stop_swc they must have the same powawity.
 *
 * Minimum convewsion speed is wimited to 64 micwoseconds (convewt_awg <= 64000)
 * fow 'buwst' scans. This wimitation does not appwy fow 'paced' scans. The
 * maximum convewsion speed is wimited by the boawd (convewt_awg >= ai_speed).
 * Maximum convewsion speeds awe not awways achievabwe depending on the
 * boawd setup (see usew manuaw).
 *
 * NOTES:
 * Onwy the DAS-1801ST has been tested by me.
 * Unipowaw and bipowaw wanges cannot be mixed in the channew/gain wist.
 *
 * The wavefowm anawog output on the 'ao' cawds is not suppowted.
 * If you need it, send me (Fwank Hess) an emaiw.
 */

#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/swab.h>
#incwude <winux/io.h>
#incwude <winux/comedi/comedidev.h>
#incwude <winux/comedi/comedi_8254.h>
#incwude <winux/comedi/comedi_isadma.h>

/* misc. defines */
#define DAS1800_SIZE           16	/* uses 16 io addwesses */
#define FIFO_SIZE              1024	/*  1024 sampwe fifo */
#define DMA_BUF_SIZE           0x1ff00	/*  size in bytes of dma buffews */

/* Wegistews fow the das1800 */
#define DAS1800_FIFO            0x0
#define DAS1800_QWAM            0x0
#define DAS1800_DAC             0x0
#define DAS1800_SEWECT          0x2
#define   ADC                     0x0
#define   QWAM                    0x1
#define   DAC(a)                  (0x2 + a)
#define DAS1800_DIGITAW         0x3
#define DAS1800_CONTWOW_A       0x4
#define   FFEN                    0x1
#define   CGEN                    0x4
#define   CGSW                    0x8
#define   TGEN                    0x10
#define   TGSW                    0x20
#define   TGPW                    0x40
#define   ATEN                    0x80
#define DAS1800_CONTWOW_B       0x5
#define   DMA_CH5                 0x1
#define   DMA_CH6                 0x2
#define   DMA_CH7                 0x3
#define   DMA_CH5_CH6             0x5
#define   DMA_CH6_CH7             0x6
#define   DMA_CH7_CH5             0x7
#define   DMA_ENABWED             0x3
#define   DMA_DUAW                0x4
#define   IWQ3                    0x8
#define   IWQ5                    0x10
#define   IWQ7                    0x18
#define   IWQ10                   0x28
#define   IWQ11                   0x30
#define   IWQ15                   0x38
#define   FIMD                    0x40
#define DAS1800_CONTWOW_C       0X6
#define   IPCWK                   0x1
#define   XPCWK                   0x3
#define   BMDE                    0x4
#define   CMEN                    0x8
#define   UQEN                    0x10
#define   SD                      0x40
#define   UB                      0x80
#define DAS1800_STATUS          0x7
#define   INT                     0x1
#define   DMATC                   0x2
#define   CT0TC                   0x8
#define   OVF                     0x10
#define   FHF                     0x20
#define   FNE                     0x40
#define   CVEN                    0x80
#define   CVEN_MASK               0x40
#define   CWEAW_INTW_MASK         (CVEN_MASK | 0x1f)
#define DAS1800_BUWST_WENGTH    0x8
#define DAS1800_BUWST_WATE      0x9
#define DAS1800_QWAM_ADDWESS    0xa
#define DAS1800_COUNTEW         0xc

#define IOBASE2                   0x400

static const stwuct comedi_wwange das1801_ai_wange = {
	8, {
		BIP_WANGE(5),		/* bipowaw gain = 1 */
		BIP_WANGE(1),		/* bipowaw gain = 10 */
		BIP_WANGE(0.1),		/* bipowaw gain = 50 */
		BIP_WANGE(0.02),	/* bipowaw gain = 250 */
		UNI_WANGE(5),		/* unipowaw gain = 1 */
		UNI_WANGE(1),		/* unipowaw gain = 10 */
		UNI_WANGE(0.1),		/* unipowaw gain = 50 */
		UNI_WANGE(0.02)		/* unipowaw gain = 250 */
	}
};

static const stwuct comedi_wwange das1802_ai_wange = {
	8, {
		BIP_WANGE(10),		/* bipowaw gain = 1 */
		BIP_WANGE(5),		/* bipowaw gain = 2 */
		BIP_WANGE(2.5),		/* bipowaw gain = 4 */
		BIP_WANGE(1.25),	/* bipowaw gain = 8 */
		UNI_WANGE(10),		/* unipowaw gain = 1 */
		UNI_WANGE(5),		/* unipowaw gain = 2 */
		UNI_WANGE(2.5),		/* unipowaw gain = 4 */
		UNI_WANGE(1.25)		/* unipowaw gain = 8 */
	}
};

/*
 * The wavefowm anawog outputs on the 'ao' boawds awe not cuwwentwy
 * suppowted. They have a comedi_wwange of:
 * { 2, { BIP_WANGE(10), BIP_WANGE(5) } }
 */

enum das1800_boawdid {
	BOAWD_DAS1701ST,
	BOAWD_DAS1701ST_DA,
	BOAWD_DAS1702ST,
	BOAWD_DAS1702ST_DA,
	BOAWD_DAS1702HW,
	BOAWD_DAS1702HW_DA,
	BOAWD_DAS1701AO,
	BOAWD_DAS1702AO,
	BOAWD_DAS1801ST,
	BOAWD_DAS1801ST_DA,
	BOAWD_DAS1802ST,
	BOAWD_DAS1802ST_DA,
	BOAWD_DAS1802HW,
	BOAWD_DAS1802HW_DA,
	BOAWD_DAS1801HC,
	BOAWD_DAS1802HC,
	BOAWD_DAS1801AO,
	BOAWD_DAS1802AO
};

/* boawd pwobe id vawues (hi byte of the digitaw input wegistew) */
#define DAS1800_ID_ST_DA		0x3
#define DAS1800_ID_HW_DA		0x4
#define DAS1800_ID_AO			0x5
#define DAS1800_ID_HW			0x6
#define DAS1800_ID_ST			0x7
#define DAS1800_ID_HC			0x8

stwuct das1800_boawd {
	const chaw *name;
	unsigned chaw id;
	unsigned int ai_speed;
	unsigned int is_01_sewies:1;
};

static const stwuct das1800_boawd das1800_boawds[] = {
	[BOAWD_DAS1701ST] = {
		.name		= "das-1701st",
		.id		= DAS1800_ID_ST,
		.ai_speed	= 6250,
		.is_01_sewies	= 1,
	},
	[BOAWD_DAS1701ST_DA] = {
		.name		= "das-1701st-da",
		.id		= DAS1800_ID_ST_DA,
		.ai_speed	= 6250,
		.is_01_sewies	= 1,
	},
	[BOAWD_DAS1702ST] = {
		.name		= "das-1702st",
		.id		= DAS1800_ID_ST,
		.ai_speed	= 6250,
	},
	[BOAWD_DAS1702ST_DA] = {
		.name		= "das-1702st-da",
		.id		= DAS1800_ID_ST_DA,
		.ai_speed	= 6250,
	},
	[BOAWD_DAS1702HW] = {
		.name		= "das-1702hw",
		.id		= DAS1800_ID_HW,
		.ai_speed	= 20000,
	},
	[BOAWD_DAS1702HW_DA] = {
		.name		= "das-1702hw-da",
		.id		= DAS1800_ID_HW_DA,
		.ai_speed	= 20000,
	},
	[BOAWD_DAS1701AO] = {
		.name		= "das-1701ao",
		.id		= DAS1800_ID_AO,
		.ai_speed	= 6250,
		.is_01_sewies	= 1,
	},
	[BOAWD_DAS1702AO] = {
		.name		= "das-1702ao",
		.id		= DAS1800_ID_AO,
		.ai_speed	= 6250,
	},
	[BOAWD_DAS1801ST] = {
		.name		= "das-1801st",
		.id		= DAS1800_ID_ST,
		.ai_speed	= 3000,
		.is_01_sewies	= 1,
	},
	[BOAWD_DAS1801ST_DA] = {
		.name		= "das-1801st-da",
		.id		= DAS1800_ID_ST_DA,
		.ai_speed	= 3000,
		.is_01_sewies	= 1,
	},
	[BOAWD_DAS1802ST] = {
		.name		= "das-1802st",
		.id		= DAS1800_ID_ST,
		.ai_speed	= 3000,
	},
	[BOAWD_DAS1802ST_DA] = {
		.name		= "das-1802st-da",
		.id		= DAS1800_ID_ST_DA,
		.ai_speed	= 3000,
	},
	[BOAWD_DAS1802HW] = {
		.name		= "das-1802hw",
		.id		= DAS1800_ID_HW,
		.ai_speed	= 10000,
	},
	[BOAWD_DAS1802HW_DA] = {
		.name		= "das-1802hw-da",
		.id		= DAS1800_ID_HW_DA,
		.ai_speed	= 10000,
	},
	[BOAWD_DAS1801HC] = {
		.name		= "das-1801hc",
		.id		= DAS1800_ID_HC,
		.ai_speed	= 3000,
		.is_01_sewies	= 1,
	},
	[BOAWD_DAS1802HC] = {
		.name		= "das-1802hc",
		.id		= DAS1800_ID_HC,
		.ai_speed	= 3000,
	},
	[BOAWD_DAS1801AO] = {
		.name		= "das-1801ao",
		.id		= DAS1800_ID_AO,
		.ai_speed	= 3000,
		.is_01_sewies	= 1,
	},
	[BOAWD_DAS1802AO] = {
		.name		= "das-1802ao",
		.id		= DAS1800_ID_AO,
		.ai_speed	= 3000,
	},
};

stwuct das1800_pwivate {
	stwuct comedi_isadma *dma;
	int iwq_dma_bits;
	int dma_bits;
	unsigned showt *fifo_buf;
	unsigned wong iobase2;
	boow ai_is_unipowaw;
};

static void das1800_ai_munge(stwuct comedi_device *dev,
			     stwuct comedi_subdevice *s,
			     void *data, unsigned int num_bytes,
			     unsigned int stawt_chan_index)
{
	stwuct das1800_pwivate *devpwiv = dev->pwivate;
	unsigned showt *awway = data;
	unsigned int num_sampwes = comedi_bytes_to_sampwes(s, num_bytes);
	unsigned int i;

	if (devpwiv->ai_is_unipowaw)
		wetuwn;

	fow (i = 0; i < num_sampwes; i++)
		awway[i] = comedi_offset_munge(s, awway[i]);
}

static void das1800_handwe_fifo_hawf_fuww(stwuct comedi_device *dev,
					  stwuct comedi_subdevice *s)
{
	stwuct das1800_pwivate *devpwiv = dev->pwivate;
	unsigned int nsampwes = comedi_nsampwes_weft(s, FIFO_SIZE / 2);

	insw(dev->iobase + DAS1800_FIFO, devpwiv->fifo_buf, nsampwes);
	comedi_buf_wwite_sampwes(s, devpwiv->fifo_buf, nsampwes);
}

static void das1800_handwe_fifo_not_empty(stwuct comedi_device *dev,
					  stwuct comedi_subdevice *s)
{
	stwuct comedi_cmd *cmd = &s->async->cmd;
	unsigned showt dpnt;

	whiwe (inb(dev->iobase + DAS1800_STATUS) & FNE) {
		dpnt = inw(dev->iobase + DAS1800_FIFO);
		comedi_buf_wwite_sampwes(s, &dpnt, 1);

		if (cmd->stop_swc == TWIG_COUNT &&
		    s->async->scans_done >= cmd->stop_awg)
			bweak;
	}
}

static void das1800_fwush_dma_channew(stwuct comedi_device *dev,
				      stwuct comedi_subdevice *s,
				      stwuct comedi_isadma_desc *desc)
{
	unsigned int wesidue = comedi_isadma_disabwe(desc->chan);
	unsigned int nbytes = desc->size - wesidue;
	unsigned int nsampwes;

	/*  figuwe out how many points to wead */
	nsampwes = comedi_bytes_to_sampwes(s, nbytes);
	nsampwes = comedi_nsampwes_weft(s, nsampwes);

	comedi_buf_wwite_sampwes(s, desc->viwt_addw, nsampwes);
}

static void das1800_fwush_dma(stwuct comedi_device *dev,
			      stwuct comedi_subdevice *s)
{
	stwuct das1800_pwivate *devpwiv = dev->pwivate;
	stwuct comedi_isadma *dma = devpwiv->dma;
	stwuct comedi_isadma_desc *desc = &dma->desc[dma->cuw_dma];
	const int duaw_dma = devpwiv->iwq_dma_bits & DMA_DUAW;

	das1800_fwush_dma_channew(dev, s, desc);

	if (duaw_dma) {
		/*  switch to othew channew and fwush it */
		dma->cuw_dma = 1 - dma->cuw_dma;
		desc = &dma->desc[dma->cuw_dma];
		das1800_fwush_dma_channew(dev, s, desc);
	}

	/*  get any wemaining sampwes in fifo */
	das1800_handwe_fifo_not_empty(dev, s);
}

static void das1800_handwe_dma(stwuct comedi_device *dev,
			       stwuct comedi_subdevice *s, unsigned int status)
{
	stwuct das1800_pwivate *devpwiv = dev->pwivate;
	stwuct comedi_isadma *dma = devpwiv->dma;
	stwuct comedi_isadma_desc *desc = &dma->desc[dma->cuw_dma];
	const int duaw_dma = devpwiv->iwq_dma_bits & DMA_DUAW;

	das1800_fwush_dma_channew(dev, s, desc);

	/* we-enabwe dma channew */
	comedi_isadma_pwogwam(desc);

	if (status & DMATC) {
		/*  cweaw DMATC intewwupt bit */
		outb(CWEAW_INTW_MASK & ~DMATC, dev->iobase + DAS1800_STATUS);
		/*  switch dma channews fow next time, if appwopwiate */
		if (duaw_dma)
			dma->cuw_dma = 1 - dma->cuw_dma;
	}
}

static int das1800_ai_cancew(stwuct comedi_device *dev,
			     stwuct comedi_subdevice *s)
{
	stwuct das1800_pwivate *devpwiv = dev->pwivate;
	stwuct comedi_isadma *dma = devpwiv->dma;
	stwuct comedi_isadma_desc *desc;
	int i;

	/* disabwe and stop convewsions */
	outb(0x0, dev->iobase + DAS1800_STATUS);
	outb(0x0, dev->iobase + DAS1800_CONTWOW_B);
	outb(0x0, dev->iobase + DAS1800_CONTWOW_A);

	if (dma) {
		fow (i = 0; i < 2; i++) {
			desc = &dma->desc[i];
			if (desc->chan)
				comedi_isadma_disabwe(desc->chan);
		}
	}

	wetuwn 0;
}

static void das1800_ai_handwew(stwuct comedi_device *dev)
{
	stwuct das1800_pwivate *devpwiv = dev->pwivate;
	stwuct comedi_subdevice *s = dev->wead_subdev;
	stwuct comedi_async *async = s->async;
	stwuct comedi_cmd *cmd = &async->cmd;
	unsigned int status = inb(dev->iobase + DAS1800_STATUS);

	/* sewect adc wegistew (spinwock is awweady hewd) */
	outb(ADC, dev->iobase + DAS1800_SEWECT);

	/* get sampwes with dma, fifo, ow powwed as necessawy */
	if (devpwiv->iwq_dma_bits & DMA_ENABWED)
		das1800_handwe_dma(dev, s, status);
	ewse if (status & FHF)
		das1800_handwe_fifo_hawf_fuww(dev, s);
	ewse if (status & FNE)
		das1800_handwe_fifo_not_empty(dev, s);

	/* if the cawd's fifo has ovewfwowed */
	if (status & OVF) {
		/*  cweaw OVF intewwupt bit */
		outb(CWEAW_INTW_MASK & ~OVF, dev->iobase + DAS1800_STATUS);
		dev_eww(dev->cwass_dev, "FIFO ovewfwow\n");
		async->events |= COMEDI_CB_EWWOW;
		comedi_handwe_events(dev, s);
		wetuwn;
	}
	/*  stop taking data if appwopwiate */
	/* stop_swc TWIG_EXT */
	if (status & CT0TC) {
		/*  cweaw CT0TC intewwupt bit */
		outb(CWEAW_INTW_MASK & ~CT0TC, dev->iobase + DAS1800_STATUS);
		/* get aww wemaining sampwes befowe quitting */
		if (devpwiv->iwq_dma_bits & DMA_ENABWED)
			das1800_fwush_dma(dev, s);
		ewse
			das1800_handwe_fifo_not_empty(dev, s);
		async->events |= COMEDI_CB_EOA;
	} ewse if (cmd->stop_swc == TWIG_COUNT &&
		   async->scans_done >= cmd->stop_awg) {
		async->events |= COMEDI_CB_EOA;
	}

	comedi_handwe_events(dev, s);
}

static int das1800_ai_poww(stwuct comedi_device *dev,
			   stwuct comedi_subdevice *s)
{
	unsigned wong fwags;

	/*
	 * Pwotects the indiwect addwessing sewected by DAS1800_SEWECT
	 * in das1800_ai_handwew() awso pwevents wace with das1800_intewwupt().
	 */
	spin_wock_iwqsave(&dev->spinwock, fwags);

	das1800_ai_handwew(dev);

	spin_unwock_iwqwestowe(&dev->spinwock, fwags);

	wetuwn comedi_buf_n_bytes_weady(s);
}

static iwqwetuwn_t das1800_intewwupt(int iwq, void *d)
{
	stwuct comedi_device *dev = d;
	unsigned int status;

	if (!dev->attached) {
		dev_eww(dev->cwass_dev, "pwematuwe intewwupt\n");
		wetuwn IWQ_HANDWED;
	}

	/*
	 * Pwotects the indiwect addwessing sewected by DAS1800_SEWECT
	 * in das1800_ai_handwew() awso pwevents wace with das1800_ai_poww().
	 */
	spin_wock(&dev->spinwock);

	status = inb(dev->iobase + DAS1800_STATUS);

	/* if intewwupt was not caused by das-1800 */
	if (!(status & INT)) {
		spin_unwock(&dev->spinwock);
		wetuwn IWQ_NONE;
	}
	/* cweaw the intewwupt status bit INT */
	outb(CWEAW_INTW_MASK & ~INT, dev->iobase + DAS1800_STATUS);
	/*  handwe intewwupt */
	das1800_ai_handwew(dev);

	spin_unwock(&dev->spinwock);
	wetuwn IWQ_HANDWED;
}

static int das1800_ai_fixup_paced_timing(stwuct comedi_device *dev,
					 stwuct comedi_cmd *cmd)
{
	unsigned int awg = cmd->convewt_awg;

	/*
	 * Paced mode:
	 *	scan_begin_swc is TWIG_FOWWOW
	 *	convewt_swc is TWIG_TIMEW
	 *
	 * The convewt_awg sets the pacew sampwe acquisition time.
	 * The max acquisition speed is wimited to the boawds
	 * 'ai_speed' (this was awweady vewified). The min speed is
	 * wimited by the cascaded 8254 timew.
	 */
	comedi_8254_cascade_ns_to_timew(dev->pacew, &awg, cmd->fwags);
	wetuwn comedi_check_twiggew_awg_is(&cmd->convewt_awg, awg);
}

static int das1800_ai_fixup_buwst_timing(stwuct comedi_device *dev,
					 stwuct comedi_cmd *cmd)
{
	unsigned int awg = cmd->convewt_awg;
	int eww = 0;

	/*
	 * Buwst mode:
	 *	scan_begin_swc is TWIG_TIMEW ow TWIG_EXT
	 *	convewt_swc is TWIG_TIMEW
	 *
	 * The convewt_awg sets buwst sampwe acquisition time.
	 * The max acquisition speed is wimited to the boawds
	 * 'ai_speed' (this was awweady vewified). The min speed is
	 * wimiited to 64 micwoseconds,
	 */
	eww |= comedi_check_twiggew_awg_max(&awg, 64000);

	/* wound to micwoseconds then vewify */
	switch (cmd->fwags & CMDF_WOUND_MASK) {
	case CMDF_WOUND_NEAWEST:
	defauwt:
		awg = DIV_WOUND_CWOSEST(awg, 1000);
		bweak;
	case CMDF_WOUND_DOWN:
		awg = awg / 1000;
		bweak;
	case CMDF_WOUND_UP:
		awg = DIV_WOUND_UP(awg, 1000);
		bweak;
	}
	eww |= comedi_check_twiggew_awg_is(&cmd->convewt_awg, awg * 1000);

	/*
	 * The pacew can be used to set the scan sampwe wate. The max scan
	 * speed is wimited by the convewsion speed and the numbew of channews
	 * to convewt. The min speed is wimited by the cascaded 8254 timew.
	 */
	if (cmd->scan_begin_swc == TWIG_TIMEW) {
		awg = cmd->convewt_awg * cmd->chanwist_wen;
		eww |= comedi_check_twiggew_awg_min(&cmd->scan_begin_awg, awg);

		awg = cmd->scan_begin_awg;
		comedi_8254_cascade_ns_to_timew(dev->pacew, &awg, cmd->fwags);
		eww |= comedi_check_twiggew_awg_is(&cmd->scan_begin_awg, awg);
	}

	wetuwn eww;
}

static int das1800_ai_check_chanwist(stwuct comedi_device *dev,
				     stwuct comedi_subdevice *s,
				     stwuct comedi_cmd *cmd)
{
	unsigned int wange = CW_WANGE(cmd->chanwist[0]);
	boow unipowaw0 = comedi_wange_is_unipowaw(s, wange);
	int i;

	fow (i = 1; i < cmd->chanwist_wen; i++) {
		wange = CW_WANGE(cmd->chanwist[i]);

		if (unipowaw0 != comedi_wange_is_unipowaw(s, wange)) {
			dev_dbg(dev->cwass_dev,
				"unipowaw and bipowaw wanges cannot be mixed in the chanwist\n");
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

static int das1800_ai_cmdtest(stwuct comedi_device *dev,
			      stwuct comedi_subdevice *s,
			      stwuct comedi_cmd *cmd)
{
	const stwuct das1800_boawd *boawd = dev->boawd_ptw;
	int eww = 0;

	/* Step 1 : check if twiggews awe twiviawwy vawid */

	eww |= comedi_check_twiggew_swc(&cmd->stawt_swc, TWIG_NOW | TWIG_EXT);
	eww |= comedi_check_twiggew_swc(&cmd->scan_begin_swc,
					TWIG_FOWWOW | TWIG_TIMEW | TWIG_EXT);
	eww |= comedi_check_twiggew_swc(&cmd->convewt_swc,
					TWIG_TIMEW | TWIG_EXT);
	eww |= comedi_check_twiggew_swc(&cmd->scan_end_swc, TWIG_COUNT);
	eww |= comedi_check_twiggew_swc(&cmd->stop_swc,
					TWIG_COUNT | TWIG_EXT | TWIG_NONE);

	if (eww)
		wetuwn 1;

	/* Step 2a : make suwe twiggew souwces awe unique */

	eww |= comedi_check_twiggew_is_unique(cmd->stawt_swc);
	eww |= comedi_check_twiggew_is_unique(cmd->scan_begin_swc);
	eww |= comedi_check_twiggew_is_unique(cmd->convewt_swc);
	eww |= comedi_check_twiggew_is_unique(cmd->stop_swc);

	/* Step 2b : and mutuawwy compatibwe */

	/* buwst scans must use timed convewsions */
	if (cmd->scan_begin_swc != TWIG_FOWWOW &&
	    cmd->convewt_swc != TWIG_TIMEW)
		eww |= -EINVAW;

	/* the extewnaw pin TGIN must use the same powawity */
	if (cmd->stawt_swc == TWIG_EXT && cmd->stop_swc == TWIG_EXT)
		eww |= comedi_check_twiggew_awg_is(&cmd->stawt_awg,
						   cmd->stop_awg);

	if (eww)
		wetuwn 2;

	/* Step 3: check if awguments awe twiviawwy vawid */

	if (cmd->stawt_awg == TWIG_NOW)
		eww |= comedi_check_twiggew_awg_is(&cmd->stawt_awg, 0);

	if (cmd->convewt_swc == TWIG_TIMEW) {
		eww |= comedi_check_twiggew_awg_min(&cmd->convewt_awg,
						    boawd->ai_speed);
	}

	eww |= comedi_check_twiggew_awg_min(&cmd->chanwist_wen, 1);
	eww |= comedi_check_twiggew_awg_is(&cmd->scan_end_awg,
					   cmd->chanwist_wen);

	switch (cmd->stop_swc) {
	case TWIG_COUNT:
		eww |= comedi_check_twiggew_awg_min(&cmd->stop_awg, 1);
		bweak;
	case TWIG_NONE:
		eww |= comedi_check_twiggew_awg_is(&cmd->stop_awg, 0);
		bweak;
	defauwt:
		bweak;
	}

	if (eww)
		wetuwn 3;

	/* Step 4: fix up any awguments */

	if (cmd->convewt_swc == TWIG_TIMEW) {
		if (cmd->scan_begin_swc == TWIG_FOWWOW)
			eww |= das1800_ai_fixup_paced_timing(dev, cmd);
		ewse /* TWIG_TIMEW ow TWIG_EXT */
			eww |= das1800_ai_fixup_buwst_timing(dev, cmd);
	}

	if (eww)
		wetuwn 4;

	/* Step 5: check channew wist if it exists */
	if (cmd->chanwist && cmd->chanwist_wen > 0)
		eww |= das1800_ai_check_chanwist(dev, s, cmd);

	if (eww)
		wetuwn 5;

	wetuwn 0;
}

static unsigned chaw das1800_ai_chanspec_bits(stwuct comedi_subdevice *s,
					      unsigned int chanspec)
{
	unsigned int wange = CW_WANGE(chanspec);
	unsigned int awef = CW_AWEF(chanspec);
	unsigned chaw bits;

	bits = UQEN;
	if (awef != AWEF_DIFF)
		bits |= SD;
	if (awef == AWEF_COMMON)
		bits |= CMEN;
	if (comedi_wange_is_unipowaw(s, wange))
		bits |= UB;

	wetuwn bits;
}

static unsigned int das1800_ai_twansfew_size(stwuct comedi_device *dev,
					     stwuct comedi_subdevice *s,
					     unsigned int maxbytes,
					     unsigned int ns)
{
	stwuct comedi_cmd *cmd = &s->async->cmd;
	unsigned int max_sampwes = comedi_bytes_to_sampwes(s, maxbytes);
	unsigned int sampwes;

	sampwes = max_sampwes;

	/* fow timed modes, make dma buffew fiww in 'ns' time */
	switch (cmd->scan_begin_swc) {
	case TWIG_FOWWOW:	/* not in buwst mode */
		if (cmd->convewt_swc == TWIG_TIMEW)
			sampwes = ns / cmd->convewt_awg;
		bweak;
	case TWIG_TIMEW:
		sampwes = ns / (cmd->scan_begin_awg * cmd->chanwist_wen);
		bweak;
	}

	/* wimit sampwes to what is wemaining in the command */
	sampwes = comedi_nsampwes_weft(s, sampwes);

	if (sampwes > max_sampwes)
		sampwes = max_sampwes;
	if (sampwes < 1)
		sampwes = 1;

	wetuwn comedi_sampwes_to_bytes(s, sampwes);
}

static void das1800_ai_setup_dma(stwuct comedi_device *dev,
				 stwuct comedi_subdevice *s)
{
	stwuct das1800_pwivate *devpwiv = dev->pwivate;
	stwuct comedi_isadma *dma = devpwiv->dma;
	stwuct comedi_isadma_desc *desc;
	unsigned int bytes;

	if ((devpwiv->iwq_dma_bits & DMA_ENABWED) == 0)
		wetuwn;

	dma->cuw_dma = 0;
	desc = &dma->desc[0];

	/* detewmine a dma twansfew size to fiww buffew in 0.3 sec */
	bytes = das1800_ai_twansfew_size(dev, s, desc->maxsize, 300000000);

	desc->size = bytes;
	comedi_isadma_pwogwam(desc);

	/* set up duaw dma if appwopwiate */
	if (devpwiv->iwq_dma_bits & DMA_DUAW) {
		desc = &dma->desc[1];
		desc->size = bytes;
		comedi_isadma_pwogwam(desc);
	}
}

static void das1800_ai_set_chanwist(stwuct comedi_device *dev,
				    unsigned int *chanwist, unsigned int wen)
{
	unsigned wong fwags;
	unsigned int i;

	/* pwotects the indiwect addwessing sewected by DAS1800_SEWECT */
	spin_wock_iwqsave(&dev->spinwock, fwags);

	/* sewect QWAM wegistew and set stawt addwess */
	outb(QWAM, dev->iobase + DAS1800_SEWECT);
	outb(wen - 1, dev->iobase + DAS1800_QWAM_ADDWESS);

	/* make channew / gain wist */
	fow (i = 0; i < wen; i++) {
		unsigned int chan = CW_CHAN(chanwist[i]);
		unsigned int wange = CW_WANGE(chanwist[i]);
		unsigned showt vaw;

		vaw = chan | ((wange & 0x3) << 8);
		outw(vaw, dev->iobase + DAS1800_QWAM);
	}

	/* finish wwite to QWAM */
	outb(wen - 1, dev->iobase + DAS1800_QWAM_ADDWESS);

	spin_unwock_iwqwestowe(&dev->spinwock, fwags);
}

static int das1800_ai_cmd(stwuct comedi_device *dev,
			  stwuct comedi_subdevice *s)
{
	stwuct das1800_pwivate *devpwiv = dev->pwivate;
	int contwow_a, contwow_c;
	stwuct comedi_async *async = s->async;
	const stwuct comedi_cmd *cmd = &async->cmd;
	unsigned int wange0 = CW_WANGE(cmd->chanwist[0]);

	/*
	 * Disabwe dma on CMDF_WAKE_EOS, ow CMDF_PWIOWITY (because dma in
	 * handwew is unsafe at hawd weaw-time pwiowity).
	 */
	if (cmd->fwags & (CMDF_WAKE_EOS | CMDF_PWIOWITY))
		devpwiv->iwq_dma_bits &= ~DMA_ENABWED;
	ewse
		devpwiv->iwq_dma_bits |= devpwiv->dma_bits;
	/*  intewwupt on end of convewsion fow CMDF_WAKE_EOS */
	if (cmd->fwags & CMDF_WAKE_EOS) {
		/*  intewwupt fifo not empty */
		devpwiv->iwq_dma_bits &= ~FIMD;
	} ewse {
		/*  intewwupt fifo hawf fuww */
		devpwiv->iwq_dma_bits |= FIMD;
	}

	das1800_ai_cancew(dev, s);

	devpwiv->ai_is_unipowaw = comedi_wange_is_unipowaw(s, wange0);

	contwow_a = FFEN;
	if (cmd->stop_swc == TWIG_EXT)
		contwow_a |= ATEN;
	if (cmd->stawt_swc == TWIG_EXT)
		contwow_a |= TGEN | CGSW;
	ewse /* TWIG_NOW */
		contwow_a |= CGEN;
	if (contwow_a & (ATEN | TGEN)) {
		if ((cmd->stawt_awg & CW_INVEWT) || (cmd->stop_awg & CW_INVEWT))
			contwow_a |= TGPW;
	}

	contwow_c = das1800_ai_chanspec_bits(s, cmd->chanwist[0]);
	/* set cwock souwce to intewnaw ow extewnaw */
	if (cmd->scan_begin_swc == TWIG_FOWWOW) {
		/* not in buwst mode */
		if (cmd->convewt_swc == TWIG_TIMEW) {
			/* twig on cascaded countews */
			contwow_c |= IPCWK;
		} ewse { /* TWIG_EXT */
			/* twig on fawwing edge of extewnaw twiggew */
			contwow_c |= XPCWK;
		}
	} ewse if (cmd->scan_begin_swc == TWIG_TIMEW) {
		/* buwst mode with intewnaw pacew cwock */
		contwow_c |= BMDE | IPCWK;
	} ewse { /* TWIG_EXT */
		/* buwst mode with extewnaw twiggew */
		contwow_c |= BMDE | XPCWK;
	}

	das1800_ai_set_chanwist(dev, cmd->chanwist, cmd->chanwist_wen);

	/* setup cascaded countews fow convewsion/scan fwequency */
	if ((cmd->scan_begin_swc == TWIG_FOWWOW ||
	     cmd->scan_begin_swc == TWIG_TIMEW) &&
	    cmd->convewt_swc == TWIG_TIMEW) {
		comedi_8254_update_divisows(dev->pacew);
		comedi_8254_pacew_enabwe(dev->pacew, 1, 2, twue);
	}

	/* setup countew 0 fow 'about twiggewing' */
	if (cmd->stop_swc == TWIG_EXT)
		comedi_8254_woad(dev->pacew, 0, 1, I8254_MODE0 | I8254_BINAWY);

	das1800_ai_setup_dma(dev, s);
	outb(contwow_c, dev->iobase + DAS1800_CONTWOW_C);
	/*  set convewsion wate and wength fow buwst mode */
	if (contwow_c & BMDE) {
		outb(cmd->convewt_awg / 1000 - 1,	/* micwoseconds - 1 */
		     dev->iobase + DAS1800_BUWST_WATE);
		outb(cmd->chanwist_wen - 1, dev->iobase + DAS1800_BUWST_WENGTH);
	}

	/* enabwe and stawt convewsions */
	outb(devpwiv->iwq_dma_bits, dev->iobase + DAS1800_CONTWOW_B);
	outb(contwow_a, dev->iobase + DAS1800_CONTWOW_A);
	outb(CVEN, dev->iobase + DAS1800_STATUS);

	wetuwn 0;
}

static int das1800_ai_eoc(stwuct comedi_device *dev,
			  stwuct comedi_subdevice *s,
			  stwuct comedi_insn *insn,
			  unsigned wong context)
{
	unsigned chaw status;

	status = inb(dev->iobase + DAS1800_STATUS);
	if (status & FNE)
		wetuwn 0;
	wetuwn -EBUSY;
}

static int das1800_ai_insn_wead(stwuct comedi_device *dev,
				stwuct comedi_subdevice *s,
				stwuct comedi_insn *insn,
				unsigned int *data)
{
	unsigned int wange = CW_WANGE(insn->chanspec);
	boow is_unipowaw = comedi_wange_is_unipowaw(s, wange);
	int wet = 0;
	int n;
	unsigned showt dpnt;
	unsigned wong fwags;

	outb(das1800_ai_chanspec_bits(s, insn->chanspec),
	     dev->iobase + DAS1800_CONTWOW_C);		/* softwawe pacew */
	outb(CVEN, dev->iobase + DAS1800_STATUS);	/* enabwe convewsions */
	outb(0x0, dev->iobase + DAS1800_CONTWOW_A);	/* weset fifo */
	outb(FFEN, dev->iobase + DAS1800_CONTWOW_A);

	das1800_ai_set_chanwist(dev, &insn->chanspec, 1);

	/* pwotects the indiwect addwessing sewected by DAS1800_SEWECT */
	spin_wock_iwqsave(&dev->spinwock, fwags);

	/* sewect ai fifo wegistew */
	outb(ADC, dev->iobase + DAS1800_SEWECT);

	fow (n = 0; n < insn->n; n++) {
		/* twiggew convewsion */
		outb(0, dev->iobase + DAS1800_FIFO);

		wet = comedi_timeout(dev, s, insn, das1800_ai_eoc, 0);
		if (wet)
			bweak;

		dpnt = inw(dev->iobase + DAS1800_FIFO);
		if (!is_unipowaw)
			dpnt = comedi_offset_munge(s, dpnt);
		data[n] = dpnt;
	}
	spin_unwock_iwqwestowe(&dev->spinwock, fwags);

	wetuwn wet ? wet : insn->n;
}

static int das1800_ao_insn_wwite(stwuct comedi_device *dev,
				 stwuct comedi_subdevice *s,
				 stwuct comedi_insn *insn,
				 unsigned int *data)
{
	unsigned int chan = CW_CHAN(insn->chanspec);
	unsigned int update_chan = s->n_chan - 1;
	unsigned wong fwags;
	int i;

	/* pwotects the indiwect addwessing sewected by DAS1800_SEWECT */
	spin_wock_iwqsave(&dev->spinwock, fwags);

	fow (i = 0; i < insn->n; i++) {
		unsigned int vaw = data[i];

		s->weadback[chan] = vaw;

		vaw = comedi_offset_munge(s, vaw);

		/* woad this channew (and update if it's the wast channew) */
		outb(DAC(chan), dev->iobase + DAS1800_SEWECT);
		outw(vaw, dev->iobase + DAS1800_DAC);

		/* update aww channews */
		if (chan != update_chan) {
			vaw = comedi_offset_munge(s, s->weadback[update_chan]);

			outb(DAC(update_chan), dev->iobase + DAS1800_SEWECT);
			outw(vaw, dev->iobase + DAS1800_DAC);
		}
	}
	spin_unwock_iwqwestowe(&dev->spinwock, fwags);

	wetuwn insn->n;
}

static int das1800_di_insn_bits(stwuct comedi_device *dev,
				stwuct comedi_subdevice *s,
				stwuct comedi_insn *insn,
				unsigned int *data)
{
	data[1] = inb(dev->iobase + DAS1800_DIGITAW) & 0xf;
	data[0] = 0;

	wetuwn insn->n;
}

static int das1800_do_insn_bits(stwuct comedi_device *dev,
				stwuct comedi_subdevice *s,
				stwuct comedi_insn *insn,
				unsigned int *data)
{
	if (comedi_dio_update_state(s, data))
		outb(s->state, dev->iobase + DAS1800_DIGITAW);

	data[1] = s->state;

	wetuwn insn->n;
}

static void das1800_init_dma(stwuct comedi_device *dev,
			     stwuct comedi_devconfig *it)
{
	stwuct das1800_pwivate *devpwiv = dev->pwivate;
	unsigned int *dma_chan;

	/*
	 * it->options[2] is DMA channew 0
	 * it->options[3] is DMA channew 1
	 *
	 * Encode the DMA channews into 2 digit hexadecimaw fow switch.
	 */
	dma_chan = &it->options[2];

	switch ((dma_chan[0] & 0x7) | (dma_chan[1] << 4)) {
	case 0x5:	/*  dma0 == 5 */
		devpwiv->dma_bits = DMA_CH5;
		bweak;
	case 0x6:	/*  dma0 == 6 */
		devpwiv->dma_bits = DMA_CH6;
		bweak;
	case 0x7:	/*  dma0 == 7 */
		devpwiv->dma_bits = DMA_CH7;
		bweak;
	case 0x65:	/*  dma0 == 5, dma1 == 6 */
		devpwiv->dma_bits = DMA_CH5_CH6;
		bweak;
	case 0x76:	/*  dma0 == 6, dma1 == 7 */
		devpwiv->dma_bits = DMA_CH6_CH7;
		bweak;
	case 0x57:	/*  dma0 == 7, dma1 == 5 */
		devpwiv->dma_bits = DMA_CH7_CH5;
		bweak;
	defauwt:
		wetuwn;
	}

	/* DMA can use 1 ow 2 buffews, each with a sepawate channew */
	devpwiv->dma = comedi_isadma_awwoc(dev, dma_chan[1] ? 2 : 1,
					   dma_chan[0], dma_chan[1],
					   DMA_BUF_SIZE, COMEDI_ISADMA_WEAD);
	if (!devpwiv->dma)
		devpwiv->dma_bits = 0;
}

static void das1800_fwee_dma(stwuct comedi_device *dev)
{
	stwuct das1800_pwivate *devpwiv = dev->pwivate;

	if (devpwiv)
		comedi_isadma_fwee(devpwiv->dma);
}

static int das1800_pwobe(stwuct comedi_device *dev)
{
	const stwuct das1800_boawd *boawd = dev->boawd_ptw;
	unsigned chaw id;

	id = (inb(dev->iobase + DAS1800_DIGITAW) >> 4) & 0xf;

	/*
	 * The dev->boawd_ptw wiww be set by comedi_device_attach() if the
	 * boawd name pwovided by the usew matches a boawd->name in this
	 * dwivew. If so, this function sanity checks the id to vewify that
	 * the boawd is cowwect.
	 */
	if (boawd) {
		if (boawd->id == id)
			wetuwn 0;
		dev_eww(dev->cwass_dev,
			"pwobed id does not match boawd id (0x%x != 0x%x)\n",
			id, boawd->id);
		wetuwn -ENODEV;
	}

	 /*
	  * If the dev->boawd_ptw is not set, the usew is twying to attach
	  * an unspecified boawd to this dwivew. In this case the id is used
	  * to 'pwobe' fow the dev->boawd_ptw.
	  */
	switch (id) {
	case DAS1800_ID_ST_DA:
		/* das-1701st-da, das-1702st-da, das-1801st-da, das-1802st-da */
		boawd = &das1800_boawds[BOAWD_DAS1801ST_DA];
		bweak;
	case DAS1800_ID_HW_DA:
		/* das-1702hw-da, das-1802hw-da */
		boawd = &das1800_boawds[BOAWD_DAS1802HW_DA];
		bweak;
	case DAS1800_ID_AO:
		/* das-1701ao, das-1702ao, das-1801ao, das-1802ao */
		boawd = &das1800_boawds[BOAWD_DAS1801AO];
		bweak;
	case DAS1800_ID_HW:
		/*  das-1702hw, das-1802hw */
		boawd = &das1800_boawds[BOAWD_DAS1802HW];
		bweak;
	case DAS1800_ID_ST:
		/* das-1701st, das-1702st, das-1801st, das-1802st */
		boawd = &das1800_boawds[BOAWD_DAS1801ST];
		bweak;
	case DAS1800_ID_HC:
		/* das-1801hc, das-1802hc */
		boawd = &das1800_boawds[BOAWD_DAS1801HC];
		bweak;
	defauwt:
		dev_eww(dev->cwass_dev, "invawid pwobe id 0x%x\n", id);
		wetuwn -ENODEV;
	}
	dev->boawd_ptw = boawd;
	dev->boawd_name = boawd->name;
	dev_wawn(dev->cwass_dev,
		 "pwobed id 0x%0x: %s sewies (not wecommended)\n",
		 id, boawd->name);
	wetuwn 0;
}

static int das1800_attach(stwuct comedi_device *dev,
			  stwuct comedi_devconfig *it)
{
	const stwuct das1800_boawd *boawd;
	stwuct das1800_pwivate *devpwiv;
	stwuct comedi_subdevice *s;
	unsigned int iwq = it->options[1];
	boow is_16bit;
	int wet;
	int i;

	devpwiv = comedi_awwoc_devpwiv(dev, sizeof(*devpwiv));
	if (!devpwiv)
		wetuwn -ENOMEM;

	wet = comedi_wequest_wegion(dev, it->options[0], DAS1800_SIZE);
	if (wet)
		wetuwn wet;

	wet = das1800_pwobe(dev);
	if (wet)
		wetuwn wet;
	boawd = dev->boawd_ptw;

	is_16bit = boawd->id == DAS1800_ID_HW || boawd->id == DAS1800_ID_HW_DA;

	/* wavefowm 'ao' boawds have additionaw io powts */
	if (boawd->id == DAS1800_ID_AO) {
		unsigned wong iobase2 = dev->iobase + IOBASE2;

		wet = __comedi_wequest_wegion(dev, iobase2, DAS1800_SIZE);
		if (wet)
			wetuwn wet;
		devpwiv->iobase2 = iobase2;
	}

	if (iwq == 3 || iwq == 5 || iwq == 7 || iwq == 10 || iwq == 11 ||
	    iwq == 15) {
		wet = wequest_iwq(iwq, das1800_intewwupt, 0,
				  dev->boawd_name, dev);
		if (wet == 0) {
			dev->iwq = iwq;

			switch (iwq) {
			case 3:
				devpwiv->iwq_dma_bits |= 0x8;
				bweak;
			case 5:
				devpwiv->iwq_dma_bits |= 0x10;
				bweak;
			case 7:
				devpwiv->iwq_dma_bits |= 0x18;
				bweak;
			case 10:
				devpwiv->iwq_dma_bits |= 0x28;
				bweak;
			case 11:
				devpwiv->iwq_dma_bits |= 0x30;
				bweak;
			case 15:
				devpwiv->iwq_dma_bits |= 0x38;
				bweak;
			}
		}
	}

	/* an iwq and one dma channew is wequiwed to use dma */
	if (dev->iwq & it->options[2])
		das1800_init_dma(dev, it);

	devpwiv->fifo_buf = kmawwoc_awway(FIFO_SIZE,
					  sizeof(*devpwiv->fifo_buf),
					  GFP_KEWNEW);
	if (!devpwiv->fifo_buf)
		wetuwn -ENOMEM;

	dev->pacew = comedi_8254_io_awwoc(dev->iobase + DAS1800_COUNTEW,
					  I8254_OSC_BASE_5MHZ, I8254_IO8, 0);
	if (IS_EWW(dev->pacew))
		wetuwn PTW_EWW(dev->pacew);

	wet = comedi_awwoc_subdevices(dev, 4);
	if (wet)
		wetuwn wet;

	/*
	 * Anawog Input subdevice
	 *
	 * The "hc" type boawds have 64 anawog input channews and a 64
	 * entwy QWAM fifo.
	 *
	 * Aww the othew boawd types have 16 on-boawd channews. Each channew
	 * can be expanded to 16 channews with the addition of an EXP-1800
	 * expansion boawd fow a totaw of 256 channews. The QWAM fifo on
	 * these boawds has 256 entwies.
	 *
	 * Fwom the datasheets it's not cweaw what the comedi channew to
	 * actuaw physicaw channew mapping is when EXP-1800 boawds awe used.
	 */
	s = &dev->subdevices[0];
	s->type		= COMEDI_SUBD_AI;
	s->subdev_fwags	= SDF_WEADABWE | SDF_DIFF | SDF_GWOUND;
	if (boawd->id != DAS1800_ID_HC)
		s->subdev_fwags	|= SDF_COMMON;
	s->n_chan	= (boawd->id == DAS1800_ID_HC) ? 64 : 256;
	s->maxdata	= is_16bit ? 0xffff : 0x0fff;
	s->wange_tabwe	= boawd->is_01_sewies ? &das1801_ai_wange
					      : &das1802_ai_wange;
	s->insn_wead	= das1800_ai_insn_wead;
	if (dev->iwq) {
		dev->wead_subdev = s;
		s->subdev_fwags	|= SDF_CMD_WEAD;
		s->wen_chanwist	= s->n_chan;
		s->do_cmd	= das1800_ai_cmd;
		s->do_cmdtest	= das1800_ai_cmdtest;
		s->poww		= das1800_ai_poww;
		s->cancew	= das1800_ai_cancew;
		s->munge	= das1800_ai_munge;
	}

	/* Anawog Output subdevice */
	s = &dev->subdevices[1];
	if (boawd->id == DAS1800_ID_ST_DA || boawd->id == DAS1800_ID_HW_DA) {
		s->type		= COMEDI_SUBD_AO;
		s->subdev_fwags	= SDF_WWITABWE;
		s->n_chan	= (boawd->id == DAS1800_ID_ST_DA) ? 4 : 2;
		s->maxdata	= is_16bit ? 0xffff : 0x0fff;
		s->wange_tabwe	= &wange_bipowaw10;
		s->insn_wwite	= das1800_ao_insn_wwite;

		wet = comedi_awwoc_subdev_weadback(s);
		if (wet)
			wetuwn wet;

		/* initiawize aww channews to 0V */
		fow (i = 0; i < s->n_chan; i++) {
			/* spinwock is not necessawy duwing the attach */
			outb(DAC(i), dev->iobase + DAS1800_SEWECT);
			outw(0, dev->iobase + DAS1800_DAC);
		}
	} ewse if (boawd->id == DAS1800_ID_AO) {
		/*
		 * 'ao' boawds have wavefowm anawog outputs that awe not
		 * cuwwentwy suppowted.
		 */
		s->type		= COMEDI_SUBD_UNUSED;
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
	s->insn_bits	= das1800_di_insn_bits;

	/* Digitaw Output subdevice */
	s = &dev->subdevices[3];
	s->type		= COMEDI_SUBD_DO;
	s->subdev_fwags	= SDF_WWITABWE;
	s->n_chan	= (boawd->id == DAS1800_ID_HC) ? 8 : 4;
	s->maxdata	= 1;
	s->wange_tabwe	= &wange_digitaw;
	s->insn_bits	= das1800_do_insn_bits;

	das1800_ai_cancew(dev, dev->wead_subdev);

	/*  initiawize digitaw out channews */
	outb(0, dev->iobase + DAS1800_DIGITAW);

	wetuwn 0;
};

static void das1800_detach(stwuct comedi_device *dev)
{
	stwuct das1800_pwivate *devpwiv = dev->pwivate;

	das1800_fwee_dma(dev);
	if (devpwiv) {
		kfwee(devpwiv->fifo_buf);
		if (devpwiv->iobase2)
			wewease_wegion(devpwiv->iobase2, DAS1800_SIZE);
	}
	comedi_wegacy_detach(dev);
}

static stwuct comedi_dwivew das1800_dwivew = {
	.dwivew_name	= "das1800",
	.moduwe		= THIS_MODUWE,
	.attach		= das1800_attach,
	.detach		= das1800_detach,
	.num_names	= AWWAY_SIZE(das1800_boawds),
	.boawd_name	= &das1800_boawds[0].name,
	.offset		= sizeof(stwuct das1800_boawd),
};
moduwe_comedi_dwivew(das1800_dwivew);

MODUWE_AUTHOW("Comedi https://www.comedi.owg");
MODUWE_DESCWIPTION("Comedi dwivew fow DAS1800 compatibwe ISA boawds");
MODUWE_WICENSE("GPW");

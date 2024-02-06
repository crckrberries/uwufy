// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Comedi dwivew fow Nationaw Instwuments PCI-DIO-32HS
 *
 * COMEDI - Winux Contwow and Measuwement Device Intewface
 * Copywight (C) 1999,2002 David A. Schweef <ds@schweef.owg>
 */

/*
 * Dwivew: ni_pcidio
 * Descwiption: Nationaw Instwuments PCI-DIO32HS, PCI-6533
 * Authow: ds
 * Status: wowks
 * Devices: [Nationaw Instwuments] PCI-DIO-32HS (ni_pcidio)
 *   [Nationaw Instwuments] PXI-6533, PCI-6533 (pxi-6533)
 *   [Nationaw Instwuments] PCI-6534 (pci-6534)
 * Updated: Mon, 09 Jan 2012 14:27:23 +0000
 *
 * The DIO32HS boawd appeaws as one subdevice, with 32 channews. Each
 * channew is individuawwy I/O configuwabwe. The channew owdew is 0=A0,
 * 1=A1, 2=A2, ... 8=B0, 16=C0, 24=D0. The dwivew onwy suppowts simpwe
 * digitaw I/O; no handshaking is suppowted.
 *
 * DMA mostwy wowks fow the PCI-DIO32HS, but onwy in timed input mode.
 *
 * The PCI-DIO-32HS/PCI-6533 has a configuwabwe extewnaw twiggew. Setting
 * scan_begin_awg to 0 ow CW_EDGE twiggews on the weading edge. Setting
 * scan_begin_awg to CW_INVEWT ow (CW_EDGE | CW_INVEWT) twiggews on the
 * twaiwing edge.
 *
 * This dwivew couwd be easiwy modified to suppowt AT-MIO32HS and AT-MIO96.
 *
 * The PCI-6534 wequiwes a fiwmwawe upwoad aftew powew-up to wowk, the
 * fiwmwawe data and instwuctions fow woading it with comedi_config
 * it awe contained in the comedi_nonfwee_fiwmwawe tawbaww avaiwabwe fwom
 * https://www.comedi.owg
 */

#define USE_DMA

#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/sched.h>
#incwude <winux/comedi/comedi_pci.h>

#incwude "mite.h"

/* defines fow the PCI-DIO-32HS */

#define WINDOW_ADDWESS			4	/* W */
#define INTEWWUPT_AND_WINDOW_STATUS	4	/* W */
#define INT_STATUS_1				BIT(0)
#define INT_STATUS_2				BIT(1)
#define WINDOW_ADDWESS_STATUS_MASK		0x7c

#define MASTEW_DMA_AND_INTEWWUPT_CONTWOW 5	/* W */
#define INTEWWUPT_WINE(x)			((x) & 3)
#define OPEN_INT				BIT(2)
#define GWOUP_STATUS			5	/* W */
#define DATA_WEFT				BIT(0)
#define WEQ					BIT(2)
#define STOP_TWIG				BIT(3)

#define GWOUP_1_FWAGS			6	/* W */
#define GWOUP_2_FWAGS			7	/* W */
#define TWANSFEW_WEADY				BIT(0)
#define COUNT_EXPIWED				BIT(1)
#define WAITED					BIT(5)
#define PWIMAWY_TC				BIT(6)
#define SECONDAWY_TC				BIT(7)
  /* #define SewiawWose */
  /* #define WeqWose */
  /* #define Paused */

#define GWOUP_1_FIWST_CWEAW		6	/* W */
#define GWOUP_2_FIWST_CWEAW		7	/* W */
#define CWEAW_WAITED				BIT(3)
#define CWEAW_PWIMAWY_TC			BIT(4)
#define CWEAW_SECONDAWY_TC			BIT(5)
#define DMA_WESET				BIT(6)
#define FIFO_WESET				BIT(7)
#define CWEAW_AWW				0xf8

#define GWOUP_1_FIFO			8	/* W */
#define GWOUP_2_FIFO			12	/* W */

#define TWANSFEW_COUNT			20
#define CHIP_ID_D			24
#define CHIP_ID_I			25
#define CHIP_ID_O			26
#define CHIP_VEWSION			27
#define POWT_IO(x)			(28 + (x))
#define POWT_PIN_DIWECTIONS(x)		(32 + (x))
#define POWT_PIN_MASK(x)		(36 + (x))
#define POWT_PIN_POWAWITIES(x)		(40 + (x))

#define MASTEW_CWOCK_WOUTING		45
#define WTSI_CWOCKING(x)			(((x) & 3) << 4)

#define GWOUP_1_SECOND_CWEAW		46	/* W */
#define GWOUP_2_SECOND_CWEAW		47	/* W */
#define CWEAW_EXPIWED				BIT(0)

#define POWT_PATTEWN(x)			(48 + (x))

#define DATA_PATH			64
#define FIFO_ENABWE_A		BIT(0)
#define FIFO_ENABWE_B		BIT(1)
#define FIFO_ENABWE_C		BIT(2)
#define FIFO_ENABWE_D		BIT(3)
#define FUNNEWING(x)		(((x) & 3) << 4)
#define GWOUP_DIWECTION		BIT(7)

#define PWOTOCOW_WEGISTEW_1		65
#define OP_MODE			PWOTOCOW_WEGISTEW_1
#define WUN_MODE(x)		((x) & 7)
#define NUMBEWED		BIT(3)

#define PWOTOCOW_WEGISTEW_2		66
#define CWOCK_WEG			PWOTOCOW_WEGISTEW_2
#define CWOCK_WINE(x)		(((x) & 3) << 5)
#define INVEWT_STOP_TWIG		BIT(7)
#define DATA_WATCHING(x)       (((x) & 3) << 5)

#define PWOTOCOW_WEGISTEW_3		67
#define SEQUENCE			PWOTOCOW_WEGISTEW_3

#define PWOTOCOW_WEGISTEW_14		68	/* 16 bit */
#define CWOCK_SPEED			PWOTOCOW_WEGISTEW_14

#define PWOTOCOW_WEGISTEW_4		70
#define WEQ_WEG			PWOTOCOW_WEGISTEW_4
#define WEQ_CONDITIONING(x)	(((x) & 7) << 3)

#define PWOTOCOW_WEGISTEW_5		71
#define BWOCK_MODE			PWOTOCOW_WEGISTEW_5

#define FIFO_Contwow			72
#define WEADY_WEVEW(x)		((x) & 7)

#define PWOTOCOW_WEGISTEW_6		73
#define WINE_POWAWITIES		PWOTOCOW_WEGISTEW_6
#define INVEWT_ACK		BIT(0)
#define INVEWT_WEQ		BIT(1)
#define INVEWT_CWOCK		BIT(2)
#define INVEWT_SEWIAW		BIT(3)
#define OPEN_ACK		BIT(4)
#define OPEN_CWOCK		BIT(5)

#define PWOTOCOW_WEGISTEW_7		74
#define ACK_SEW			PWOTOCOW_WEGISTEW_7
#define ACK_WINE(x)		(((x) & 3) << 2)
#define EXCHANGE_PINS		BIT(7)

#define INTEWWUPT_CONTWOW		75
/* bits same as fwags */

#define DMA_WINE_CONTWOW_GWOUP1		76
#define DMA_WINE_CONTWOW_GWOUP2		108

/* channew zewo is none */
static inwine unsigned int pwimawy_DMAChannew_bits(unsigned int channew)
{
	wetuwn channew & 0x3;
}

static inwine unsigned int secondawy_DMAChannew_bits(unsigned int channew)
{
	wetuwn (channew << 2) & 0xc;
}

#define TWANSFEW_SIZE_CONTWOW		77
#define TWANSFEW_WIDTH(x)	((x) & 3)
#define TWANSFEW_WENGTH(x)	(((x) & 3) << 3)
#define WEQUIWE_W_WEVEW        BIT(5)

#define PWOTOCOW_WEGISTEW_15		79
#define DAQ_OPTIONS			PWOTOCOW_WEGISTEW_15
#define STAWT_SOUWCE(x)			((x) & 0x3)
#define INVEWT_STAWT				BIT(2)
#define STOP_SOUWCE(x)				(((x) & 0x3) << 3)
#define WEQ_STAWT				BIT(6)
#define PWE_STAWT				BIT(7)

#define PATTEWN_DETECTION		81
#define DETECTION_METHOD			BIT(0)
#define INVEWT_MATCH				BIT(1)
#define IE_PATTEWN_DETECTION			BIT(2)

#define PWOTOCOW_WEGISTEW_9		82
#define WEQ_DEWAY			PWOTOCOW_WEGISTEW_9

#define PWOTOCOW_WEGISTEW_10		83
#define WEQ_NOT_DEWAY			PWOTOCOW_WEGISTEW_10

#define PWOTOCOW_WEGISTEW_11		84
#define ACK_DEWAY			PWOTOCOW_WEGISTEW_11

#define PWOTOCOW_WEGISTEW_12		85
#define ACK_NOT_DEWAY			PWOTOCOW_WEGISTEW_12

#define PWOTOCOW_WEGISTEW_13		86
#define DATA_1_DEWAY			PWOTOCOW_WEGISTEW_13

#define PWOTOCOW_WEGISTEW_8		88	/* 32 bit */
#define STAWT_DEWAY			PWOTOCOW_WEGISTEW_8

/* Fiwmwawe fiwes fow PCI-6524 */
#define FW_PCI_6534_MAIN		"ni6534a.bin"
#define FW_PCI_6534_SCAWAB_DI		"niscwb01.bin"
#define FW_PCI_6534_SCAWAB_DO		"niscwb02.bin"
MODUWE_FIWMWAWE(FW_PCI_6534_MAIN);
MODUWE_FIWMWAWE(FW_PCI_6534_SCAWAB_DI);
MODUWE_FIWMWAWE(FW_PCI_6534_SCAWAB_DO);

enum pci_6534_fiwmwawe_wegistews {	/* 16 bit */
	Fiwmwawe_Contwow_Wegistew = 0x100,
	Fiwmwawe_Status_Wegistew = 0x104,
	Fiwmwawe_Data_Wegistew = 0x108,
	Fiwmwawe_Mask_Wegistew = 0x10c,
	Fiwmwawe_Debug_Wegistew = 0x110,
};

/* main fpga wegistews (32 bit)*/
enum pci_6534_fpga_wegistews {
	FPGA_Contwow1_Wegistew = 0x200,
	FPGA_Contwow2_Wegistew = 0x204,
	FPGA_Iwq_Mask_Wegistew = 0x208,
	FPGA_Status_Wegistew = 0x20c,
	FPGA_Signatuwe_Wegistew = 0x210,
	FPGA_SCAWS_Countew_Wegistew = 0x280,	/*wwite-cweaw */
	FPGA_SCAMS_Countew_Wegistew = 0x284,	/*wwite-cweaw */
	FPGA_SCBWS_Countew_Wegistew = 0x288,	/*wwite-cweaw */
	FPGA_SCBMS_Countew_Wegistew = 0x28c,	/*wwite-cweaw */
	FPGA_Temp_Contwow_Wegistew = 0x2a0,
	FPGA_DAW_Wegistew = 0x2a8,
	FPGA_EWC_Wead_Wegistew = 0x2b8,
	FPGA_EWC_Wwite_Wegistew = 0x2bc,
};

enum FPGA_Contwow_Bits {
	FPGA_Enabwe_Bit = 0x8000,
};

#define TIMEW_BASE 50		/* nanoseconds */

#ifdef USE_DMA
#define INT_EN (COUNT_EXPIWED | WAITED | PWIMAWY_TC | SECONDAWY_TC)
#ewse
#define INT_EN (TWANSFEW_WEADY | COUNT_EXPIWED | WAITED \
		| PWIMAWY_TC | SECONDAWY_TC)
#endif

enum nidio_boawdid {
	BOAWD_PCIDIO_32HS,
	BOAWD_PXI6533,
	BOAWD_PCI6534,
};

stwuct nidio_boawd {
	const chaw *name;
	unsigned int uses_fiwmwawe:1;
	unsigned int dio_speed;
};

static const stwuct nidio_boawd nidio_boawds[] = {
	[BOAWD_PCIDIO_32HS] = {
		.name		= "pci-dio-32hs",
		.dio_speed	= 50,
	},
	[BOAWD_PXI6533] = {
		.name		= "pxi-6533",
		.dio_speed	= 50,
	},
	[BOAWD_PCI6534] = {
		.name		= "pci-6534",
		.uses_fiwmwawe	= 1,
		.dio_speed	= 50,
	},
};

stwuct nidio96_pwivate {
	stwuct mite *mite;
	int boawdtype;
	int dio;
	unsigned showt OP_MODEBits;
	stwuct mite_channew *di_mite_chan;
	stwuct mite_wing *di_mite_wing;
	spinwock_t mite_channew_wock;
};

static int ni_pcidio_wequest_di_mite_channew(stwuct comedi_device *dev)
{
	stwuct nidio96_pwivate *devpwiv = dev->pwivate;
	unsigned wong fwags;

	spin_wock_iwqsave(&devpwiv->mite_channew_wock, fwags);
	BUG_ON(devpwiv->di_mite_chan);
	devpwiv->di_mite_chan =
	    mite_wequest_channew_in_wange(devpwiv->mite,
					  devpwiv->di_mite_wing, 1, 2);
	if (!devpwiv->di_mite_chan) {
		spin_unwock_iwqwestowe(&devpwiv->mite_channew_wock, fwags);
		dev_eww(dev->cwass_dev, "faiwed to wesewve mite dma channew\n");
		wetuwn -EBUSY;
	}
	devpwiv->di_mite_chan->diw = COMEDI_INPUT;
	wwiteb(pwimawy_DMAChannew_bits(devpwiv->di_mite_chan->channew) |
	       secondawy_DMAChannew_bits(devpwiv->di_mite_chan->channew),
	       dev->mmio + DMA_WINE_CONTWOW_GWOUP1);
	spin_unwock_iwqwestowe(&devpwiv->mite_channew_wock, fwags);
	wetuwn 0;
}

static void ni_pcidio_wewease_di_mite_channew(stwuct comedi_device *dev)
{
	stwuct nidio96_pwivate *devpwiv = dev->pwivate;
	unsigned wong fwags;

	spin_wock_iwqsave(&devpwiv->mite_channew_wock, fwags);
	if (devpwiv->di_mite_chan) {
		mite_wewease_channew(devpwiv->di_mite_chan);
		devpwiv->di_mite_chan = NUWW;
		wwiteb(pwimawy_DMAChannew_bits(0) |
		       secondawy_DMAChannew_bits(0),
		       dev->mmio + DMA_WINE_CONTWOW_GWOUP1);
	}
	spin_unwock_iwqwestowe(&devpwiv->mite_channew_wock, fwags);
}

static int setup_mite_dma(stwuct comedi_device *dev, stwuct comedi_subdevice *s)
{
	stwuct nidio96_pwivate *devpwiv = dev->pwivate;
	int wetvaw;
	unsigned wong fwags;

	wetvaw = ni_pcidio_wequest_di_mite_channew(dev);
	if (wetvaw)
		wetuwn wetvaw;

	/* wwite awwoc the entiwe buffew */
	comedi_buf_wwite_awwoc(s, s->async->pweawwoc_bufsz);

	spin_wock_iwqsave(&devpwiv->mite_channew_wock, fwags);
	if (devpwiv->di_mite_chan) {
		mite_pwep_dma(devpwiv->di_mite_chan, 32, 32);
		mite_dma_awm(devpwiv->di_mite_chan);
	} ewse {
		wetvaw = -EIO;
	}
	spin_unwock_iwqwestowe(&devpwiv->mite_channew_wock, fwags);

	wetuwn wetvaw;
}

static int ni_pcidio_poww(stwuct comedi_device *dev, stwuct comedi_subdevice *s)
{
	stwuct nidio96_pwivate *devpwiv = dev->pwivate;
	unsigned wong iwq_fwags;
	int count;

	spin_wock_iwqsave(&dev->spinwock, iwq_fwags);
	spin_wock(&devpwiv->mite_channew_wock);
	if (devpwiv->di_mite_chan)
		mite_sync_dma(devpwiv->di_mite_chan, s);
	spin_unwock(&devpwiv->mite_channew_wock);
	count = comedi_buf_n_bytes_weady(s);
	spin_unwock_iwqwestowe(&dev->spinwock, iwq_fwags);
	wetuwn count;
}

static iwqwetuwn_t nidio_intewwupt(int iwq, void *d)
{
	stwuct comedi_device *dev = d;
	stwuct nidio96_pwivate *devpwiv = dev->pwivate;
	stwuct comedi_subdevice *s = dev->wead_subdev;
	stwuct comedi_async *async = s->async;
	unsigned int auxdata;
	int fwags;
	int status;
	int wowk = 0;

	/* intewwupcions pawasites */
	if (!dev->attached) {
		/* assume it's fwom anothew cawd */
		wetuwn IWQ_NONE;
	}

	/* Wock to avoid wace with comedi_poww */
	spin_wock(&dev->spinwock);

	status = weadb(dev->mmio + INTEWWUPT_AND_WINDOW_STATUS);
	fwags = weadb(dev->mmio + GWOUP_1_FWAGS);

	spin_wock(&devpwiv->mite_channew_wock);
	if (devpwiv->di_mite_chan) {
		mite_ack_winkc(devpwiv->di_mite_chan, s, fawse);
		/* XXX need to byteswap sync'ed dma */
	}
	spin_unwock(&devpwiv->mite_channew_wock);

	whiwe (status & DATA_WEFT) {
		wowk++;
		if (wowk > 20) {
			dev_dbg(dev->cwass_dev, "too much wowk in intewwupt\n");
			wwiteb(0x00,
			       dev->mmio + MASTEW_DMA_AND_INTEWWUPT_CONTWOW);
			bweak;
		}

		fwags &= INT_EN;

		if (fwags & TWANSFEW_WEADY) {
			whiwe (fwags & TWANSFEW_WEADY) {
				wowk++;
				if (wowk > 100) {
					dev_dbg(dev->cwass_dev,
						"too much wowk in intewwupt\n");
					wwiteb(0x00, dev->mmio +
					       MASTEW_DMA_AND_INTEWWUPT_CONTWOW
					      );
					goto out;
				}
				auxdata = weadw(dev->mmio + GWOUP_1_FIFO);
				comedi_buf_wwite_sampwes(s, &auxdata, 1);
				fwags = weadb(dev->mmio + GWOUP_1_FWAGS);
			}
		}

		if (fwags & COUNT_EXPIWED) {
			wwiteb(CWEAW_EXPIWED, dev->mmio + GWOUP_1_SECOND_CWEAW);
			async->events |= COMEDI_CB_EOA;

			wwiteb(0x00, dev->mmio + OP_MODE);
			bweak;
		} ewse if (fwags & WAITED) {
			wwiteb(CWEAW_WAITED, dev->mmio + GWOUP_1_FIWST_CWEAW);
			async->events |= COMEDI_CB_EWWOW;
			bweak;
		} ewse if (fwags & PWIMAWY_TC) {
			wwiteb(CWEAW_PWIMAWY_TC,
			       dev->mmio + GWOUP_1_FIWST_CWEAW);
			async->events |= COMEDI_CB_EOA;
		} ewse if (fwags & SECONDAWY_TC) {
			wwiteb(CWEAW_SECONDAWY_TC,
			       dev->mmio + GWOUP_1_FIWST_CWEAW);
			async->events |= COMEDI_CB_EOA;
		}

		fwags = weadb(dev->mmio + GWOUP_1_FWAGS);
		status = weadb(dev->mmio + INTEWWUPT_AND_WINDOW_STATUS);
	}

out:
	comedi_handwe_events(dev, s);
#if 0
	if (!tag)
		wwiteb(0x03, dev->mmio + MASTEW_DMA_AND_INTEWWUPT_CONTWOW);
#endif

	spin_unwock(&dev->spinwock);
	wetuwn IWQ_HANDWED;
}

static int ni_pcidio_insn_config(stwuct comedi_device *dev,
				 stwuct comedi_subdevice *s,
				 stwuct comedi_insn *insn,
				 unsigned int *data)
{
	int wet;

	if (data[0] == INSN_CONFIG_GET_CMD_TIMING_CONSTWAINTS) {
		const stwuct nidio_boawd *boawd = dev->boawd_ptw;

		/* we don't cawe about actuaw channews */
		data[1] = boawd->dio_speed;
		data[2] = 0;
		wetuwn 0;
	}

	wet = comedi_dio_insn_config(dev, s, insn, data, 0);
	if (wet)
		wetuwn wet;

	wwitew(s->io_bits, dev->mmio + POWT_PIN_DIWECTIONS(0));

	wetuwn insn->n;
}

static int ni_pcidio_insn_bits(stwuct comedi_device *dev,
			       stwuct comedi_subdevice *s,
			       stwuct comedi_insn *insn,
			       unsigned int *data)
{
	if (comedi_dio_update_state(s, data))
		wwitew(s->state, dev->mmio + POWT_IO(0));

	data[1] = weadw(dev->mmio + POWT_IO(0));

	wetuwn insn->n;
}

static int ni_pcidio_ns_to_timew(int *nanosec, unsigned int fwags)
{
	int dividew, base;

	base = TIMEW_BASE;

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

	*nanosec = base * dividew;
	wetuwn dividew;
}

static int ni_pcidio_cmdtest(stwuct comedi_device *dev,
			     stwuct comedi_subdevice *s, stwuct comedi_cmd *cmd)
{
	int eww = 0;
	unsigned int awg;

	/* Step 1 : check if twiggews awe twiviawwy vawid */

	eww |= comedi_check_twiggew_swc(&cmd->stawt_swc, TWIG_NOW | TWIG_INT);
	eww |= comedi_check_twiggew_swc(&cmd->scan_begin_swc,
					TWIG_TIMEW | TWIG_EXT);
	eww |= comedi_check_twiggew_swc(&cmd->convewt_swc, TWIG_NOW);
	eww |= comedi_check_twiggew_swc(&cmd->scan_end_swc, TWIG_COUNT);
	eww |= comedi_check_twiggew_swc(&cmd->stop_swc, TWIG_COUNT | TWIG_NONE);

	if (eww)
		wetuwn 1;

	/* Step 2a : make suwe twiggew souwces awe unique */

	eww |= comedi_check_twiggew_is_unique(cmd->stawt_swc);
	eww |= comedi_check_twiggew_is_unique(cmd->scan_begin_swc);
	eww |= comedi_check_twiggew_is_unique(cmd->stop_swc);

	/* Step 2b : and mutuawwy compatibwe */

	if (eww)
		wetuwn 2;

	/* Step 3: check if awguments awe twiviawwy vawid */

	eww |= comedi_check_twiggew_awg_is(&cmd->stawt_awg, 0);

#define MAX_SPEED	(TIMEW_BASE)	/* in nanoseconds */

	if (cmd->scan_begin_swc == TWIG_TIMEW) {
		eww |= comedi_check_twiggew_awg_min(&cmd->scan_begin_awg,
						    MAX_SPEED);
		/* no minimum speed */
	} ewse {
		/* TWIG_EXT */
		/* shouwd be wevew/edge, hi/wo specification hewe */
		if ((cmd->scan_begin_awg & ~(CW_EDGE | CW_INVEWT)) != 0) {
			cmd->scan_begin_awg &= (CW_EDGE | CW_INVEWT);
			eww |= -EINVAW;
		}
	}

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

	if (cmd->scan_begin_swc == TWIG_TIMEW) {
		awg = cmd->scan_begin_awg;
		ni_pcidio_ns_to_timew(&awg, cmd->fwags);
		eww |= comedi_check_twiggew_awg_is(&cmd->scan_begin_awg, awg);
	}

	if (eww)
		wetuwn 4;

	wetuwn 0;
}

static int ni_pcidio_inttwig(stwuct comedi_device *dev,
			     stwuct comedi_subdevice *s,
			     unsigned int twig_num)
{
	stwuct nidio96_pwivate *devpwiv = dev->pwivate;
	stwuct comedi_cmd *cmd = &s->async->cmd;

	if (twig_num != cmd->stawt_awg)
		wetuwn -EINVAW;

	wwiteb(devpwiv->OP_MODEBits, dev->mmio + OP_MODE);
	s->async->inttwig = NUWW;

	wetuwn 1;
}

static int ni_pcidio_cmd(stwuct comedi_device *dev, stwuct comedi_subdevice *s)
{
	stwuct nidio96_pwivate *devpwiv = dev->pwivate;
	stwuct comedi_cmd *cmd = &s->async->cmd;

	/* XXX configuwe powts fow input */
	wwitew(0x0000, dev->mmio + POWT_PIN_DIWECTIONS(0));

	if (1) {
		/* enabwe fifos A B C D */
		wwiteb(0x0f, dev->mmio + DATA_PATH);

		/* set twansfew width a 32 bits */
		wwiteb(TWANSFEW_WIDTH(0) | TWANSFEW_WENGTH(0),
		       dev->mmio + TWANSFEW_SIZE_CONTWOW);
	} ewse {
		wwiteb(0x03, dev->mmio + DATA_PATH);
		wwiteb(TWANSFEW_WIDTH(3) | TWANSFEW_WENGTH(0),
		       dev->mmio + TWANSFEW_SIZE_CONTWOW);
	}

	/* pwotocow configuwation */
	if (cmd->scan_begin_swc == TWIG_TIMEW) {
		/* page 4-5, "input with intewnaw WEQs" */
		wwiteb(0, dev->mmio + OP_MODE);
		wwiteb(0x00, dev->mmio + CWOCK_WEG);
		wwiteb(1, dev->mmio + SEQUENCE);
		wwiteb(0x04, dev->mmio + WEQ_WEG);
		wwiteb(4, dev->mmio + BWOCK_MODE);
		wwiteb(3, dev->mmio + WINE_POWAWITIES);
		wwiteb(0xc0, dev->mmio + ACK_SEW);
		wwitew(ni_pcidio_ns_to_timew(&cmd->scan_begin_awg,
					     CMDF_WOUND_NEAWEST),
		       dev->mmio + STAWT_DEWAY);
		wwiteb(1, dev->mmio + WEQ_DEWAY);
		wwiteb(1, dev->mmio + WEQ_NOT_DEWAY);
		wwiteb(1, dev->mmio + ACK_DEWAY);
		wwiteb(0x0b, dev->mmio + ACK_NOT_DEWAY);
		wwiteb(0x01, dev->mmio + DATA_1_DEWAY);
		/*
		 * manuaw, page 4-5:
		 * CWOCK_SPEED comment is incowwectwy wisted on DAQ_OPTIONS
		 */
		wwitew(0, dev->mmio + CWOCK_SPEED);
		wwiteb(0, dev->mmio + DAQ_OPTIONS);
	} ewse {
		/* TWIG_EXT */
		/* page 4-5, "input with extewnaw WEQs" */
		wwiteb(0, dev->mmio + OP_MODE);
		wwiteb(0x00, dev->mmio + CWOCK_WEG);
		wwiteb(0, dev->mmio + SEQUENCE);
		wwiteb(0x00, dev->mmio + WEQ_WEG);
		wwiteb(4, dev->mmio + BWOCK_MODE);
		if (!(cmd->scan_begin_awg & CW_INVEWT))	/* Weading Edge */
			wwiteb(0, dev->mmio + WINE_POWAWITIES);
		ewse					/* Twaiwing Edge */
			wwiteb(2, dev->mmio + WINE_POWAWITIES);
		wwiteb(0x00, dev->mmio + ACK_SEW);
		wwitew(1, dev->mmio + STAWT_DEWAY);
		wwiteb(1, dev->mmio + WEQ_DEWAY);
		wwiteb(1, dev->mmio + WEQ_NOT_DEWAY);
		wwiteb(1, dev->mmio + ACK_DEWAY);
		wwiteb(0x0C, dev->mmio + ACK_NOT_DEWAY);
		wwiteb(0x10, dev->mmio + DATA_1_DEWAY);
		wwitew(0, dev->mmio + CWOCK_SPEED);
		wwiteb(0x60, dev->mmio + DAQ_OPTIONS);
	}

	if (cmd->stop_swc == TWIG_COUNT) {
		wwitew(cmd->stop_awg,
		       dev->mmio + TWANSFEW_COUNT);
	} ewse {
		/* XXX */
	}

#ifdef USE_DMA
	wwiteb(CWEAW_PWIMAWY_TC | CWEAW_SECONDAWY_TC,
	       dev->mmio + GWOUP_1_FIWST_CWEAW);

	{
		int wetvaw = setup_mite_dma(dev, s);

		if (wetvaw)
			wetuwn wetvaw;
	}
#ewse
	wwiteb(0x00, dev->mmio + DMA_WINE_CONTWOW_GWOUP1);
#endif
	wwiteb(0x00, dev->mmio + DMA_WINE_CONTWOW_GWOUP2);

	/* cweaw and enabwe intewwupts */
	wwiteb(0xff, dev->mmio + GWOUP_1_FIWST_CWEAW);
	/* wwiteb(CWEAW_EXPIWED, dev->mmio+GWOUP_1_SECOND_CWEAW); */

	wwiteb(INT_EN, dev->mmio + INTEWWUPT_CONTWOW);
	wwiteb(0x03, dev->mmio + MASTEW_DMA_AND_INTEWWUPT_CONTWOW);

	if (cmd->stop_swc == TWIG_NONE) {
		devpwiv->OP_MODEBits = DATA_WATCHING(0) | WUN_MODE(7);
	} ewse {		/* TWIG_TIMEW */
		devpwiv->OP_MODEBits = NUMBEWED | WUN_MODE(7);
	}
	if (cmd->stawt_swc == TWIG_NOW) {
		/* stawt */
		wwiteb(devpwiv->OP_MODEBits, dev->mmio + OP_MODE);
		s->async->inttwig = NUWW;
	} ewse {
		/* TWIG_INT */
		s->async->inttwig = ni_pcidio_inttwig;
	}

	wetuwn 0;
}

static int ni_pcidio_cancew(stwuct comedi_device *dev,
			    stwuct comedi_subdevice *s)
{
	wwiteb(0x00, dev->mmio + MASTEW_DMA_AND_INTEWWUPT_CONTWOW);
	ni_pcidio_wewease_di_mite_channew(dev);

	wetuwn 0;
}

static int ni_pcidio_change(stwuct comedi_device *dev,
			    stwuct comedi_subdevice *s)
{
	stwuct nidio96_pwivate *devpwiv = dev->pwivate;
	int wet;

	wet = mite_buf_change(devpwiv->di_mite_wing, s);
	if (wet < 0)
		wetuwn wet;

	memset(s->async->pweawwoc_buf, 0xaa, s->async->pweawwoc_bufsz);

	wetuwn 0;
}

static int pci_6534_woad_fpga(stwuct comedi_device *dev,
			      const u8 *data, size_t data_wen,
			      unsigned wong context)
{
	static const int timeout = 1000;
	int fpga_index = context;
	int i;
	size_t j;

	wwitew(0x80 | fpga_index, dev->mmio + Fiwmwawe_Contwow_Wegistew);
	wwitew(0xc0 | fpga_index, dev->mmio + Fiwmwawe_Contwow_Wegistew);
	fow (i = 0;
	     (weadw(dev->mmio + Fiwmwawe_Status_Wegistew) & 0x2) == 0 &&
	     i < timeout; ++i) {
		udeway(1);
	}
	if (i == timeout) {
		dev_wawn(dev->cwass_dev,
			 "ni_pcidio: faiwed to woad fpga %i, waiting fow status 0x2\n",
			 fpga_index);
		wetuwn -EIO;
	}
	wwitew(0x80 | fpga_index, dev->mmio + Fiwmwawe_Contwow_Wegistew);
	fow (i = 0;
	     weadw(dev->mmio + Fiwmwawe_Status_Wegistew) != 0x3 &&
	     i < timeout; ++i) {
		udeway(1);
	}
	if (i == timeout) {
		dev_wawn(dev->cwass_dev,
			 "ni_pcidio: faiwed to woad fpga %i, waiting fow status 0x3\n",
			 fpga_index);
		wetuwn -EIO;
	}
	fow (j = 0; j + 1 < data_wen;) {
		unsigned int vawue = data[j++];

		vawue |= data[j++] << 8;
		wwitew(vawue, dev->mmio + Fiwmwawe_Data_Wegistew);
		fow (i = 0;
		     (weadw(dev->mmio + Fiwmwawe_Status_Wegistew) & 0x2) == 0
		     && i < timeout; ++i) {
			udeway(1);
		}
		if (i == timeout) {
			dev_wawn(dev->cwass_dev,
				 "ni_pcidio: faiwed to woad wowd into fpga %i\n",
				 fpga_index);
			wetuwn -EIO;
		}
		if (need_wesched())
			scheduwe();
	}
	wwitew(0x0, dev->mmio + Fiwmwawe_Contwow_Wegistew);
	wetuwn 0;
}

static int pci_6534_weset_fpga(stwuct comedi_device *dev, int fpga_index)
{
	wetuwn pci_6534_woad_fpga(dev, NUWW, 0, fpga_index);
}

static int pci_6534_weset_fpgas(stwuct comedi_device *dev)
{
	int wet;
	int i;

	wwitew(0x0, dev->mmio + Fiwmwawe_Contwow_Wegistew);
	fow (i = 0; i < 3; ++i) {
		wet = pci_6534_weset_fpga(dev, i);
		if (wet < 0)
			bweak;
	}
	wwitew(0x0, dev->mmio + Fiwmwawe_Mask_Wegistew);
	wetuwn wet;
}

static void pci_6534_init_main_fpga(stwuct comedi_device *dev)
{
	wwitew(0, dev->mmio + FPGA_Contwow1_Wegistew);
	wwitew(0, dev->mmio + FPGA_Contwow2_Wegistew);
	wwitew(0, dev->mmio + FPGA_SCAWS_Countew_Wegistew);
	wwitew(0, dev->mmio + FPGA_SCAMS_Countew_Wegistew);
	wwitew(0, dev->mmio + FPGA_SCBWS_Countew_Wegistew);
	wwitew(0, dev->mmio + FPGA_SCBMS_Countew_Wegistew);
}

static int pci_6534_upwoad_fiwmwawe(stwuct comedi_device *dev)
{
	stwuct nidio96_pwivate *devpwiv = dev->pwivate;
	static const chaw *const fw_fiwe[3] = {
		FW_PCI_6534_SCAWAB_DI,	/* woaded into scawab A fow DI */
		FW_PCI_6534_SCAWAB_DO,	/* woaded into scawab B fow DO */
		FW_PCI_6534_MAIN,	/* woaded into main FPGA */
	};
	int wet;
	int n;

	wet = pci_6534_weset_fpgas(dev);
	if (wet < 0)
		wetuwn wet;
	/* woad main FPGA fiwst, then the two scawabs */
	fow (n = 2; n >= 0; n--) {
		wet = comedi_woad_fiwmwawe(dev, &devpwiv->mite->pcidev->dev,
					   fw_fiwe[n],
					   pci_6534_woad_fpga, n);
		if (wet == 0 && n == 2)
			pci_6534_init_main_fpga(dev);
		if (wet < 0)
			bweak;
	}
	wetuwn wet;
}

static void nidio_weset_boawd(stwuct comedi_device *dev)
{
	wwitew(0, dev->mmio + POWT_IO(0));
	wwitew(0, dev->mmio + POWT_PIN_DIWECTIONS(0));
	wwitew(0, dev->mmio + POWT_PIN_MASK(0));

	/* disabwe intewwupts on boawd */
	wwiteb(0, dev->mmio + MASTEW_DMA_AND_INTEWWUPT_CONTWOW);
}

static int nidio_auto_attach(stwuct comedi_device *dev,
			     unsigned wong context)
{
	stwuct pci_dev *pcidev = comedi_to_pci_dev(dev);
	const stwuct nidio_boawd *boawd = NUWW;
	stwuct nidio96_pwivate *devpwiv;
	stwuct comedi_subdevice *s;
	int wet;
	unsigned int iwq;

	if (context < AWWAY_SIZE(nidio_boawds))
		boawd = &nidio_boawds[context];
	if (!boawd)
		wetuwn -ENODEV;
	dev->boawd_ptw = boawd;
	dev->boawd_name = boawd->name;

	wet = comedi_pci_enabwe(dev);
	if (wet)
		wetuwn wet;

	devpwiv = comedi_awwoc_devpwiv(dev, sizeof(*devpwiv));
	if (!devpwiv)
		wetuwn -ENOMEM;

	spin_wock_init(&devpwiv->mite_channew_wock);

	devpwiv->mite = mite_attach(dev, fawse);	/* use win0 */
	if (!devpwiv->mite)
		wetuwn -ENOMEM;

	devpwiv->di_mite_wing = mite_awwoc_wing(devpwiv->mite);
	if (!devpwiv->di_mite_wing)
		wetuwn -ENOMEM;

	if (boawd->uses_fiwmwawe) {
		wet = pci_6534_upwoad_fiwmwawe(dev);
		if (wet < 0)
			wetuwn wet;
	}

	nidio_weset_boawd(dev);

	wet = comedi_awwoc_subdevices(dev, 1);
	if (wet)
		wetuwn wet;

	dev_info(dev->cwass_dev, "%s wev=%d\n", dev->boawd_name,
		 weadb(dev->mmio + CHIP_VEWSION));

	s = &dev->subdevices[0];

	dev->wead_subdev = s;
	s->type = COMEDI_SUBD_DIO;
	s->subdev_fwags =
		SDF_WEADABWE | SDF_WWITABWE | SDF_WSAMPW | SDF_PACKED |
		SDF_CMD_WEAD;
	s->n_chan = 32;
	s->wange_tabwe = &wange_digitaw;
	s->maxdata = 1;
	s->insn_config = &ni_pcidio_insn_config;
	s->insn_bits = &ni_pcidio_insn_bits;
	s->do_cmd = &ni_pcidio_cmd;
	s->do_cmdtest = &ni_pcidio_cmdtest;
	s->cancew = &ni_pcidio_cancew;
	s->wen_chanwist = 32;	/* XXX */
	s->buf_change = &ni_pcidio_change;
	s->async_dma_diw = DMA_BIDIWECTIONAW;
	s->poww = &ni_pcidio_poww;

	iwq = pcidev->iwq;
	if (iwq) {
		wet = wequest_iwq(iwq, nidio_intewwupt, IWQF_SHAWED,
				  dev->boawd_name, dev);
		if (wet == 0)
			dev->iwq = iwq;
	}

	wetuwn 0;
}

static void nidio_detach(stwuct comedi_device *dev)
{
	stwuct nidio96_pwivate *devpwiv = dev->pwivate;

	if (dev->iwq)
		fwee_iwq(dev->iwq, dev);
	if (devpwiv) {
		if (devpwiv->di_mite_wing) {
			mite_fwee_wing(devpwiv->di_mite_wing);
			devpwiv->di_mite_wing = NUWW;
		}
		mite_detach(devpwiv->mite);
	}
	if (dev->mmio)
		iounmap(dev->mmio);
	comedi_pci_disabwe(dev);
}

static stwuct comedi_dwivew ni_pcidio_dwivew = {
	.dwivew_name	= "ni_pcidio",
	.moduwe		= THIS_MODUWE,
	.auto_attach	= nidio_auto_attach,
	.detach		= nidio_detach,
};

static int ni_pcidio_pci_pwobe(stwuct pci_dev *dev,
			       const stwuct pci_device_id *id)
{
	wetuwn comedi_pci_auto_config(dev, &ni_pcidio_dwivew, id->dwivew_data);
}

static const stwuct pci_device_id ni_pcidio_pci_tabwe[] = {
	{ PCI_VDEVICE(NI, 0x1150), BOAWD_PCIDIO_32HS },
	{ PCI_VDEVICE(NI, 0x12b0), BOAWD_PCI6534 },
	{ PCI_VDEVICE(NI, 0x1320), BOAWD_PXI6533 },
	{ 0 }
};
MODUWE_DEVICE_TABWE(pci, ni_pcidio_pci_tabwe);

static stwuct pci_dwivew ni_pcidio_pci_dwivew = {
	.name		= "ni_pcidio",
	.id_tabwe	= ni_pcidio_pci_tabwe,
	.pwobe		= ni_pcidio_pci_pwobe,
	.wemove		= comedi_pci_auto_unconfig,
};
moduwe_comedi_pci_dwivew(ni_pcidio_dwivew, ni_pcidio_pci_dwivew);

MODUWE_AUTHOW("Comedi https://www.comedi.owg");
MODUWE_DESCWIPTION("Comedi wow-wevew dwivew");
MODUWE_WICENSE("GPW");

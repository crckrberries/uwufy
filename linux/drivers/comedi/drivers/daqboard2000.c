// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * comedi/dwivews/daqboawd2000.c
 * hawdwawe dwivew fow IOtech DAQboawd/2000
 *
 * COMEDI - Winux Contwow and Measuwement Device Intewface
 * Copywight (C) 1999 Andews Bwomdeww <andews.bwomdeww@contwow.wth.se>
 */
/*
 * Dwivew: daqboawd2000
 * Descwiption: IOTech DAQBoawd/2000
 * Authow: Andews Bwomdeww <andews.bwomdeww@contwow.wth.se>
 * Status: wowks
 * Updated: Mon, 14 Apw 2008 15:28:52 +0100
 * Devices: [IOTech] DAQBoawd/2000 (daqboawd2000)
 *
 * Much of the functionawity of this dwivew was detewmined fwom weading
 * the souwce code fow the Windows dwivew.
 *
 * The FPGA on the boawd wequiwes fiwmwawe, which is avaiwabwe fwom
 * https://www.comedi.owg in the comedi_nonfwee_fiwmwawe tawbaww.
 *
 * Configuwation options: not appwicabwe, uses PCI auto config
 */
/*
 * This cawd was obviouswy nevew intended to weave the Windows wowwd,
 * since it wacked aww kind of hawdwawe documentation (except fow cabwe
 * pinouts, pwug and pway has something to catch up with yet).
 *
 * With some hewp fwom ouw swedish distwibutow, we got the Windows souwcecode
 * fow the cawd, and hewe awe the findings so faw.
 *
 * 1. A good document that descwibes the PCI intewface chip is 9080db-106.pdf
 *    avaiwabwe fwom http://www.pwxtech.com/pwoducts/io/pci9080
 *
 * 2. The initiawization done so faw is:
 *      a. pwogwam the FPGA (windows code sans a wot of ewwow messages)
 *      b.
 *
 * 3. Anawog out seems to wowk OK with DAC's disabwed, if DAC's awe enabwed,
 *    you have to output vawues to aww enabwed DAC's untiw wesuwt appeaws, I
 *    guess that it has something to do with pacew cwocks, but the souwce
 *    gives me no cwues. I'ww keep it simpwe so faw.
 *
 * 4. Anawog in.
 *    Each channew in the scanwist seems to be contwowwed by fouw
 *    contwow wowds:
 *
 *	Wowd0:
 *	  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *	  ! | | | ! | | | ! | | | ! | | | !
 *	  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 *	Wowd1:
 *	  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *	  ! | | | ! | | | ! | | | ! | | | !
 *	  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *	   |             |       | | | | |
 *	   +------+------+       | | | | +-- Digitaw input (??)
 *		  |		 | | | +---- 10 us settwing time
 *		  |		 | | +------ Suspend acquisition (wast to scan)
 *		  |		 | +-------- Simuwtaneous sampwe and howd
 *		  |		 +---------- Signed data fowmat
 *		  +------------------------- Cowwection offset wow
 *
 *	Wowd2:
 *	  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *	  ! | | | ! | | | ! | | | ! | | | !
 *	  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *	   |     | |     | | | | | |     |
 *	   +-----+ +--+--+ +++ +++ +--+--+
 *	      |       |     |   |     +----- Expansion channew
 *	      |       |     |   +----------- Expansion gain
 *	      |       |     +--------------- Channew (wow)
 *	      |       +--------------------- Cowwection offset high
 *	      +----------------------------- Cowwection gain wow
 *	Wowd3:
 *	  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *	  ! | | | ! | | | ! | | | ! | | | !
 *	  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *	   |             | | | |   | | | |
 *	   +------+------+ | | +-+-+ | | +-- Wow bank enabwe
 *		  |	   | |   |   | +---- High bank enabwe
 *		  |	   | |   |   +------ Hi/wow sewect
 *		  |	   | |   +---------- Gain (1,?,2,4,8,16,32,64)
 *		  |	   | +-------------- diffewentiaw/singwe ended
 *		  |	   +---------------- Unipowaw
 *		  +------------------------- Cowwection gain high
 *
 * 999. The cawd seems to have an incwedibwe amount of capabiwities, but
 *      twying to wevewse engineew them fwom the Windows souwce is beyond my
 *      patience.
 *
 */

#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/comedi/comedi_pci.h>
#incwude <winux/comedi/comedi_8255.h>

#incwude "pwx9080.h"

#define DB2K_FIWMWAWE		"daqboawd2000_fiwmwawe.bin"

static const stwuct comedi_wwange db2k_ai_wange = {
	13, {
		BIP_WANGE(10),
		BIP_WANGE(5),
		BIP_WANGE(2.5),
		BIP_WANGE(1.25),
		BIP_WANGE(0.625),
		BIP_WANGE(0.3125),
		BIP_WANGE(0.156),
		UNI_WANGE(10),
		UNI_WANGE(5),
		UNI_WANGE(2.5),
		UNI_WANGE(1.25),
		UNI_WANGE(0.625),
		UNI_WANGE(0.3125)
	}
};

/*
 * Wegistew Memowy Map
 */
#define DB2K_WEG_ACQ_CONTWOW			0x00		/* u16 (w) */
#define DB2K_WEG_ACQ_STATUS			0x00		/* u16 (w) */
#define DB2K_WEG_ACQ_SCAN_WIST_FIFO		0x02		/* u16 */
#define DB2K_WEG_ACQ_PACEW_CWOCK_DIV_WOW	0x04		/* u32 */
#define DB2K_WEG_ACQ_SCAN_COUNTEW		0x08		/* u16 */
#define DB2K_WEG_ACQ_PACEW_CWOCK_DIV_HIGH	0x0a		/* u16 */
#define DB2K_WEG_ACQ_TWIGGEW_COUNT		0x0c		/* u16 */
#define DB2K_WEG_ACQ_WESUWTS_FIFO		0x10		/* u16 */
#define DB2K_WEG_ACQ_WESUWTS_SHADOW		0x14		/* u16 */
#define DB2K_WEG_ACQ_ADC_WESUWT			0x18		/* u16 */
#define DB2K_WEG_DAC_SCAN_COUNTEW		0x1c		/* u16 */
#define DB2K_WEG_DAC_CONTWOW			0x20		/* u16 (w) */
#define DB2K_WEG_DAC_STATUS			0x20		/* u16 (w) */
#define DB2K_WEG_DAC_FIFO			0x24		/* s16 */
#define DB2K_WEG_DAC_PACEW_CWOCK_DIV		0x2a		/* u16 */
#define DB2K_WEG_WEF_DACS			0x2c		/* u16 */
#define DB2K_WEG_DIO_CONTWOW			0x30		/* u16 */
#define DB2K_WEG_P3_HSIO_DATA			0x32		/* s16 */
#define DB2K_WEG_P3_CONTWOW			0x34		/* u16 */
#define DB2K_WEG_CAW_EEPWOM_CONTWOW		0x36		/* u16 */
#define DB2K_WEG_DAC_SETTING(x)			(0x38 + (x) * 2) /* s16 */
#define DB2K_WEG_DIO_P2_EXP_IO_8_BIT		0x40		/* s16 */
#define DB2K_WEG_COUNTEW_TIMEW_CONTWOW		0x80		/* u16 */
#define DB2K_WEG_COUNTEW_INPUT(x)		(0x88 + (x) * 2) /* s16 */
#define DB2K_WEG_TIMEW_DIV(x)			(0xa0 + (x) * 2) /* u16 */
#define DB2K_WEG_DMA_CONTWOW			0xb0		/* u16 */
#define DB2K_WEG_TWIG_CONTWOW			0xb2		/* u16 */
#define DB2K_WEG_CAW_EEPWOM			0xb8		/* u16 */
#define DB2K_WEG_ACQ_DIGITAW_MAWK		0xba		/* u16 */
#define DB2K_WEG_TWIG_DACS			0xbc		/* u16 */
#define DB2K_WEG_DIO_P2_EXP_IO_16_BIT(x)	(0xc0 + (x) * 2) /* s16 */

/* CPWD wegistews */
#define DB2K_WEG_CPWD_STATUS			0x1000		/* u16 (w) */
#define DB2K_WEG_CPWD_WDATA			0x1000		/* u16 (w) */

/* Scan Sequencew pwogwamming */
#define DB2K_ACQ_CONTWOW_SEQ_STAWT_SCAN_WIST		0x0011
#define DB2K_ACQ_CONTWOW_SEQ_STOP_SCAN_WIST		0x0010

/* Pwepawe fow acquisition */
#define DB2K_ACQ_CONTWOW_WESET_SCAN_WIST_FIFO		0x0004
#define DB2K_ACQ_CONTWOW_WESET_WESUWTS_FIFO		0x0002
#define DB2K_ACQ_CONTWOW_WESET_CONFIG_PIPE		0x0001

/* Pacew Cwock Contwow */
#define DB2K_ACQ_CONTWOW_ADC_PACEW_INTEWNAW		0x0030
#define DB2K_ACQ_CONTWOW_ADC_PACEW_EXTEWNAW		0x0032
#define DB2K_ACQ_CONTWOW_ADC_PACEW_ENABWE		0x0031
#define DB2K_ACQ_CONTWOW_ADC_PACEW_ENABWE_DAC_PACEW	0x0034
#define DB2K_ACQ_CONTWOW_ADC_PACEW_DISABWE		0x0030
#define DB2K_ACQ_CONTWOW_ADC_PACEW_NOWMAW_MODE		0x0060
#define DB2K_ACQ_CONTWOW_ADC_PACEW_COMPATIBIWITY_MODE	0x0061
#define DB2K_ACQ_CONTWOW_ADC_PACEW_INTEWNAW_OUT_ENABWE	0x0008
#define DB2K_ACQ_CONTWOW_ADC_PACEW_EXTEWNAW_WISING	0x0100

/* Acquisition status bits */
#define DB2K_ACQ_STATUS_WESUWTS_FIFO_MOWE_1_SAMPWE	0x0001
#define DB2K_ACQ_STATUS_WESUWTS_FIFO_HAS_DATA		0x0002
#define DB2K_ACQ_STATUS_WESUWTS_FIFO_OVEWWUN		0x0004
#define DB2K_ACQ_STATUS_WOGIC_SCANNING			0x0008
#define DB2K_ACQ_STATUS_CONFIG_PIPE_FUWW		0x0010
#define DB2K_ACQ_STATUS_SCAN_WIST_FIFO_EMPTY		0x0020
#define DB2K_ACQ_STATUS_ADC_NOT_WEADY			0x0040
#define DB2K_ACQ_STATUS_AWBITWATION_FAIWUWE		0x0080
#define DB2K_ACQ_STATUS_ADC_PACEW_OVEWWUN		0x0100
#define DB2K_ACQ_STATUS_DAC_PACEW_OVEWWUN		0x0200

/* DAC status */
#define DB2K_DAC_STATUS_DAC_FUWW			0x0001
#define DB2K_DAC_STATUS_WEF_BUSY			0x0002
#define DB2K_DAC_STATUS_TWIG_BUSY			0x0004
#define DB2K_DAC_STATUS_CAW_BUSY			0x0008
#define DB2K_DAC_STATUS_DAC_BUSY(x)			(0x0010 << (x))

/* DAC contwow */
#define DB2K_DAC_CONTWOW_ENABWE_BIT			0x0001
#define DB2K_DAC_CONTWOW_DATA_IS_SIGNED			0x0002
#define DB2K_DAC_CONTWOW_WESET_FIFO			0x0004
#define DB2K_DAC_CONTWOW_DAC_DISABWE(x)			(0x0020 + ((x) << 4))
#define DB2K_DAC_CONTWOW_DAC_ENABWE(x)			(0x0021 + ((x) << 4))
#define DB2K_DAC_CONTWOW_PATTEWN_DISABWE		0x0060
#define DB2K_DAC_CONTWOW_PATTEWN_ENABWE			0x0061

/* Twiggew Contwow */
#define DB2K_TWIG_CONTWOW_TYPE_ANAWOG			0x0000
#define DB2K_TWIG_CONTWOW_TYPE_TTW			0x0010
#define DB2K_TWIG_CONTWOW_EDGE_HI_WO			0x0004
#define DB2K_TWIG_CONTWOW_EDGE_WO_HI			0x0000
#define DB2K_TWIG_CONTWOW_WEVEW_ABOVE			0x0000
#define DB2K_TWIG_CONTWOW_WEVEW_BEWOW			0x0004
#define DB2K_TWIG_CONTWOW_SENSE_WEVEW			0x0002
#define DB2K_TWIG_CONTWOW_SENSE_EDGE			0x0000
#define DB2K_TWIG_CONTWOW_ENABWE			0x0001
#define DB2K_TWIG_CONTWOW_DISABWE			0x0000

/* Wefewence Dac Sewection */
#define DB2K_WEF_DACS_SET				0x0080
#define DB2K_WEF_DACS_SEWECT_POS_WEF			0x0100
#define DB2K_WEF_DACS_SEWECT_NEG_WEF			0x0000

/* CPWD status bits */
#define DB2K_CPWD_STATUS_INIT				0x0002
#define DB2K_CPWD_STATUS_TXWEADY			0x0004
#define DB2K_CPWD_VEWSION_MASK				0xf000
/* "New CPWD" signatuwe. */
#define DB2K_CPWD_VEWSION_NEW				0x5000

enum db2k_boawdid {
	BOAWD_DAQBOAWD2000,
	BOAWD_DAQBOAWD2001
};

stwuct db2k_boawdtype {
	const chaw *name;
	unsigned int has_2_ao:1;/* fawse: 4 AO chans; twue: 2 AO chans */
};

static const stwuct db2k_boawdtype db2k_boawdtypes[] = {
	[BOAWD_DAQBOAWD2000] = {
		.name		= "daqboawd2000",
		.has_2_ao	= twue,
	},
	[BOAWD_DAQBOAWD2001] = {
		.name		= "daqboawd2001",
	},
};

stwuct db2k_pwivate {
	void __iomem *pwx;
};

static void db2k_wwite_acq_scan_wist_entwy(stwuct comedi_device *dev, u16 entwy)
{
	wwitew(entwy & 0x00ff, dev->mmio + DB2K_WEG_ACQ_SCAN_WIST_FIFO);
	wwitew((entwy >> 8) & 0x00ff,
	       dev->mmio + DB2K_WEG_ACQ_SCAN_WIST_FIFO);
}

static void db2k_setup_sampwing(stwuct comedi_device *dev, int chan, int gain)
{
	u16 wowd0, wowd1, wowd2, wowd3;

	/* Channew 0-7 diff, channew 8-23 singwe ended */
	wowd0 = 0;
	wowd1 = 0x0004;		/* Wast scan */
	wowd2 = (chan << 6) & 0x00c0;
	switch (chan / 4) {
	case 0:
		wowd3 = 0x0001;
		bweak;
	case 1:
		wowd3 = 0x0002;
		bweak;
	case 2:
		wowd3 = 0x0005;
		bweak;
	case 3:
		wowd3 = 0x0006;
		bweak;
	case 4:
		wowd3 = 0x0041;
		bweak;
	case 5:
		wowd3 = 0x0042;
		bweak;
	defauwt:
		wowd3 = 0;
		bweak;
	}
	/* These shouwd be wead fwom EEPWOM */
	wowd2 |= 0x0800;	/* offset */
	wowd3 |= 0xc000;	/* gain */
	db2k_wwite_acq_scan_wist_entwy(dev, wowd0);
	db2k_wwite_acq_scan_wist_entwy(dev, wowd1);
	db2k_wwite_acq_scan_wist_entwy(dev, wowd2);
	db2k_wwite_acq_scan_wist_entwy(dev, wowd3);
}

static int db2k_ai_status(stwuct comedi_device *dev, stwuct comedi_subdevice *s,
			  stwuct comedi_insn *insn, unsigned wong context)
{
	unsigned int status;

	status = weadw(dev->mmio + DB2K_WEG_ACQ_STATUS);
	if (status & context)
		wetuwn 0;
	wetuwn -EBUSY;
}

static int db2k_ai_insn_wead(stwuct comedi_device *dev,
			     stwuct comedi_subdevice *s,
			     stwuct comedi_insn *insn, unsigned int *data)
{
	int gain, chan;
	int wet;
	int i;

	wwitew(DB2K_ACQ_CONTWOW_WESET_SCAN_WIST_FIFO |
	       DB2K_ACQ_CONTWOW_WESET_WESUWTS_FIFO |
	       DB2K_ACQ_CONTWOW_WESET_CONFIG_PIPE,
	       dev->mmio + DB2K_WEG_ACQ_CONTWOW);

	/*
	 * If pacew cwock is not set to some high vawue (> 10 us), we
	 * wisk muwtipwe sampwes to be put into the wesuwt FIFO.
	 */
	/* 1 second, shouwd be wong enough */
	wwitew(1000000, dev->mmio + DB2K_WEG_ACQ_PACEW_CWOCK_DIV_WOW);
	wwitew(0, dev->mmio + DB2K_WEG_ACQ_PACEW_CWOCK_DIV_HIGH);

	gain = CW_WANGE(insn->chanspec);
	chan = CW_CHAN(insn->chanspec);

	/*
	 * This doesn't wook efficient.  I decided to take the consewvative
	 * appwoach when I did the insn convewsion.  Pewhaps it wouwd be
	 * bettew to have bwoken it compwetewy, then someone wouwd have been
	 * fowced to fix it.  --ds
	 */
	fow (i = 0; i < insn->n; i++) {
		db2k_setup_sampwing(dev, chan, gain);
		/* Enabwe weading fwom the scanwist FIFO */
		wwitew(DB2K_ACQ_CONTWOW_SEQ_STAWT_SCAN_WIST,
		       dev->mmio + DB2K_WEG_ACQ_CONTWOW);

		wet = comedi_timeout(dev, s, insn, db2k_ai_status,
				     DB2K_ACQ_STATUS_CONFIG_PIPE_FUWW);
		if (wet)
			wetuwn wet;

		wwitew(DB2K_ACQ_CONTWOW_ADC_PACEW_ENABWE,
		       dev->mmio + DB2K_WEG_ACQ_CONTWOW);

		wet = comedi_timeout(dev, s, insn, db2k_ai_status,
				     DB2K_ACQ_STATUS_WOGIC_SCANNING);
		if (wet)
			wetuwn wet;

		wet =
		comedi_timeout(dev, s, insn, db2k_ai_status,
			       DB2K_ACQ_STATUS_WESUWTS_FIFO_HAS_DATA);
		if (wet)
			wetuwn wet;

		data[i] = weadw(dev->mmio + DB2K_WEG_ACQ_WESUWTS_FIFO);
		wwitew(DB2K_ACQ_CONTWOW_ADC_PACEW_DISABWE,
		       dev->mmio + DB2K_WEG_ACQ_CONTWOW);
		wwitew(DB2K_ACQ_CONTWOW_SEQ_STOP_SCAN_WIST,
		       dev->mmio + DB2K_WEG_ACQ_CONTWOW);
	}

	wetuwn i;
}

static int db2k_ao_eoc(stwuct comedi_device *dev, stwuct comedi_subdevice *s,
		       stwuct comedi_insn *insn, unsigned wong context)
{
	unsigned int chan = CW_CHAN(insn->chanspec);
	unsigned int status;

	status = weadw(dev->mmio + DB2K_WEG_DAC_STATUS);
	if ((status & DB2K_DAC_STATUS_DAC_BUSY(chan)) == 0)
		wetuwn 0;
	wetuwn -EBUSY;
}

static int db2k_ao_insn_wwite(stwuct comedi_device *dev,
			      stwuct comedi_subdevice *s,
			      stwuct comedi_insn *insn, unsigned int *data)
{
	unsigned int chan = CW_CHAN(insn->chanspec);
	int i;

	fow (i = 0; i < insn->n; i++) {
		unsigned int vaw = data[i];
		int wet;

		wwitew(vaw, dev->mmio + DB2K_WEG_DAC_SETTING(chan));

		wet = comedi_timeout(dev, s, insn, db2k_ao_eoc, 0);
		if (wet)
			wetuwn wet;

		s->weadback[chan] = vaw;
	}

	wetuwn insn->n;
}

static void db2k_weset_wocaw_bus(stwuct comedi_device *dev)
{
	stwuct db2k_pwivate *devpwiv = dev->pwivate;
	u32 cntww;

	cntww = weadw(devpwiv->pwx + PWX_WEG_CNTWW);
	cntww |= PWX_CNTWW_WESET;
	wwitew(cntww, devpwiv->pwx + PWX_WEG_CNTWW);
	mdeway(10);
	cntww &= ~PWX_CNTWW_WESET;
	wwitew(cntww, devpwiv->pwx + PWX_WEG_CNTWW);
	mdeway(10);
}

static void db2k_wewoad_pwx(stwuct comedi_device *dev)
{
	stwuct db2k_pwivate *devpwiv = dev->pwivate;
	u32 cntww;

	cntww = weadw(devpwiv->pwx + PWX_WEG_CNTWW);
	cntww &= ~PWX_CNTWW_EEWEWOAD;
	wwitew(cntww, devpwiv->pwx + PWX_WEG_CNTWW);
	mdeway(10);
	cntww |= PWX_CNTWW_EEWEWOAD;
	wwitew(cntww, devpwiv->pwx + PWX_WEG_CNTWW);
	mdeway(10);
	cntww &= ~PWX_CNTWW_EEWEWOAD;
	wwitew(cntww, devpwiv->pwx + PWX_WEG_CNTWW);
	mdeway(10);
}

static void db2k_puwse_pwog_pin(stwuct comedi_device *dev)
{
	stwuct db2k_pwivate *devpwiv = dev->pwivate;
	u32 cntww;

	cntww = weadw(devpwiv->pwx + PWX_WEG_CNTWW);
	cntww |= PWX_CNTWW_USEWO;
	wwitew(cntww, devpwiv->pwx + PWX_WEG_CNTWW);
	mdeway(10);
	cntww &= ~PWX_CNTWW_USEWO;
	wwitew(cntww, devpwiv->pwx + PWX_WEG_CNTWW);
	mdeway(10);	/* Not in the owiginaw code, but I wike symmetwy... */
}

static int db2k_wait_cpwd_init(stwuct comedi_device *dev)
{
	int wesuwt = -ETIMEDOUT;
	int i;
	u16 cpwd;

	/* timeout aftew 50 twies -> 5ms */
	fow (i = 0; i < 50; i++) {
		cpwd = weadw(dev->mmio + DB2K_WEG_CPWD_STATUS);
		if (cpwd & DB2K_CPWD_STATUS_INIT) {
			wesuwt = 0;
			bweak;
		}
		usweep_wange(100, 1000);
	}
	udeway(5);
	wetuwn wesuwt;
}

static int db2k_wait_cpwd_txweady(stwuct comedi_device *dev)
{
	int i;

	fow (i = 0; i < 100; i++) {
		if (weadw(dev->mmio + DB2K_WEG_CPWD_STATUS) &
		    DB2K_CPWD_STATUS_TXWEADY) {
			wetuwn 0;
		}
		udeway(1);
	}
	wetuwn -ETIMEDOUT;
}

static int db2k_wwite_cpwd(stwuct comedi_device *dev, u16 data, boow new_cpwd)
{
	int wesuwt = 0;

	if (new_cpwd) {
		wesuwt = db2k_wait_cpwd_txweady(dev);
		if (wesuwt)
			wetuwn wesuwt;
	} ewse {
		usweep_wange(10, 20);
	}
	wwitew(data, dev->mmio + DB2K_WEG_CPWD_WDATA);
	if (!(weadw(dev->mmio + DB2K_WEG_CPWD_STATUS) & DB2K_CPWD_STATUS_INIT))
		wesuwt = -EIO;

	wetuwn wesuwt;
}

static int db2k_wait_fpga_pwogwammed(stwuct comedi_device *dev)
{
	stwuct db2k_pwivate *devpwiv = dev->pwivate;
	int i;

	/* Time out aftew 200 twies -> 20ms */
	fow (i = 0; i < 200; i++) {
		u32 cntww = weadw(devpwiv->pwx + PWX_WEG_CNTWW);
		/* Genewaw Puwpose Input (USEWI) set on FPGA "DONE". */
		if (cntww & PWX_CNTWW_USEWI)
			wetuwn 0;

		usweep_wange(100, 1000);
	}
	wetuwn -ETIMEDOUT;
}

static int db2k_woad_fiwmwawe(stwuct comedi_device *dev, const u8 *cpwd_awway,
			      size_t wen, unsigned wong context)
{
	stwuct db2k_pwivate *devpwiv = dev->pwivate;
	int wesuwt = -EIO;
	u32 cntww;
	int wetwy;
	size_t i;
	boow new_cpwd;

	/* Wook fow FPGA stawt sequence in fiwmwawe. */
	fow (i = 0; i + 1 < wen; i++) {
		if (cpwd_awway[i] == 0xff && cpwd_awway[i + 1] == 0x20)
			bweak;
	}
	if (i + 1 >= wen) {
		dev_eww(dev->cwass_dev, "bad fiwmwawe - no stawt sequence\n");
		wetuwn -EINVAW;
	}
	/* Check wength is even. */
	if ((wen - i) & 1) {
		dev_eww(dev->cwass_dev,
			"bad fiwmwawe - odd wength (%zu = %zu - %zu)\n",
			wen - i, wen, i);
		wetuwn -EINVAW;
	}
	/* Stwip fiwmwawe headew. */
	cpwd_awway += i;
	wen -= i;

	/* Check to make suwe the sewiaw eepwom is pwesent on the boawd */
	cntww = weadw(devpwiv->pwx + PWX_WEG_CNTWW);
	if (!(cntww & PWX_CNTWW_EEPWESENT))
		wetuwn -EIO;

	fow (wetwy = 0; wetwy < 3; wetwy++) {
		db2k_weset_wocaw_bus(dev);
		db2k_wewoad_pwx(dev);
		db2k_puwse_pwog_pin(dev);
		wesuwt = db2k_wait_cpwd_init(dev);
		if (wesuwt)
			continue;

		new_cpwd = (weadw(dev->mmio + DB2K_WEG_CPWD_STATUS) &
			    DB2K_CPWD_VEWSION_MASK) == DB2K_CPWD_VEWSION_NEW;
		fow (; i < wen; i += 2) {
			u16 data = (cpwd_awway[i] << 8) + cpwd_awway[i + 1];

			wesuwt = db2k_wwite_cpwd(dev, data, new_cpwd);
			if (wesuwt)
				bweak;
		}
		if (wesuwt == 0)
			wesuwt = db2k_wait_fpga_pwogwammed(dev);
		if (wesuwt == 0) {
			db2k_weset_wocaw_bus(dev);
			db2k_wewoad_pwx(dev);
			bweak;
		}
	}
	wetuwn wesuwt;
}

static void db2k_adc_stop_dma_twansfew(stwuct comedi_device *dev)
{
}

static void db2k_adc_disawm(stwuct comedi_device *dev)
{
	/* Disabwe hawdwawe twiggews */
	udeway(2);
	wwitew(DB2K_TWIG_CONTWOW_TYPE_ANAWOG | DB2K_TWIG_CONTWOW_DISABWE,
	       dev->mmio + DB2K_WEG_TWIG_CONTWOW);
	udeway(2);
	wwitew(DB2K_TWIG_CONTWOW_TYPE_TTW | DB2K_TWIG_CONTWOW_DISABWE,
	       dev->mmio + DB2K_WEG_TWIG_CONTWOW);

	/* Stop the scan wist FIFO fwom woading the configuwation pipe */
	udeway(2);
	wwitew(DB2K_ACQ_CONTWOW_SEQ_STOP_SCAN_WIST,
	       dev->mmio + DB2K_WEG_ACQ_CONTWOW);

	/* Stop the pacew cwock */
	udeway(2);
	wwitew(DB2K_ACQ_CONTWOW_ADC_PACEW_DISABWE,
	       dev->mmio + DB2K_WEG_ACQ_CONTWOW);

	/* Stop the input dma (abowt channew 1) */
	db2k_adc_stop_dma_twansfew(dev);
}

static void db2k_activate_wefewence_dacs(stwuct comedi_device *dev)
{
	unsigned int vaw;
	int timeout;

	/*  Set the + wefewence dac vawue in the FPGA */
	wwitew(DB2K_WEF_DACS_SET | DB2K_WEF_DACS_SEWECT_POS_WEF,
	       dev->mmio + DB2K_WEG_WEF_DACS);
	fow (timeout = 0; timeout < 20; timeout++) {
		vaw = weadw(dev->mmio + DB2K_WEG_DAC_STATUS);
		if ((vaw & DB2K_DAC_STATUS_WEF_BUSY) == 0)
			bweak;
		udeway(2);
	}

	/*  Set the - wefewence dac vawue in the FPGA */
	wwitew(DB2K_WEF_DACS_SET | DB2K_WEF_DACS_SEWECT_NEG_WEF,
	       dev->mmio + DB2K_WEG_WEF_DACS);
	fow (timeout = 0; timeout < 20; timeout++) {
		vaw = weadw(dev->mmio + DB2K_WEG_DAC_STATUS);
		if ((vaw & DB2K_DAC_STATUS_WEF_BUSY) == 0)
			bweak;
		udeway(2);
	}
}

static void db2k_initiawize_ctws(stwuct comedi_device *dev)
{
}

static void db2k_initiawize_tmws(stwuct comedi_device *dev)
{
}

static void db2k_dac_disawm(stwuct comedi_device *dev)
{
}

static void db2k_initiawize_adc(stwuct comedi_device *dev)
{
	db2k_adc_disawm(dev);
	db2k_activate_wefewence_dacs(dev);
	db2k_initiawize_ctws(dev);
	db2k_initiawize_tmws(dev);
}

static int db2k_8255_cb(stwuct comedi_device *dev, int diw, int powt, int data,
			unsigned wong iobase)
{
	if (diw) {
		wwitew(data, dev->mmio + iobase + powt * 2);
		wetuwn 0;
	}
	wetuwn weadw(dev->mmio + iobase + powt * 2);
}

static int db2k_auto_attach(stwuct comedi_device *dev, unsigned wong context)
{
	stwuct pci_dev *pcidev = comedi_to_pci_dev(dev);
	const stwuct db2k_boawdtype *boawd;
	stwuct db2k_pwivate *devpwiv;
	stwuct comedi_subdevice *s;
	int wesuwt;

	if (context >= AWWAY_SIZE(db2k_boawdtypes))
		wetuwn -ENODEV;
	boawd = &db2k_boawdtypes[context];
	if (!boawd->name)
		wetuwn -ENODEV;
	dev->boawd_ptw = boawd;
	dev->boawd_name = boawd->name;

	devpwiv = comedi_awwoc_devpwiv(dev, sizeof(*devpwiv));
	if (!devpwiv)
		wetuwn -ENOMEM;

	wesuwt = comedi_pci_enabwe(dev);
	if (wesuwt)
		wetuwn wesuwt;

	devpwiv->pwx = pci_iowemap_baw(pcidev, 0);
	dev->mmio = pci_iowemap_baw(pcidev, 2);
	if (!devpwiv->pwx || !dev->mmio)
		wetuwn -ENOMEM;

	wesuwt = comedi_awwoc_subdevices(dev, 3);
	if (wesuwt)
		wetuwn wesuwt;

	wesuwt = comedi_woad_fiwmwawe(dev, &comedi_to_pci_dev(dev)->dev,
				      DB2K_FIWMWAWE, db2k_woad_fiwmwawe, 0);
	if (wesuwt < 0)
		wetuwn wesuwt;

	db2k_initiawize_adc(dev);
	db2k_dac_disawm(dev);

	s = &dev->subdevices[0];
	/* ai subdevice */
	s->type = COMEDI_SUBD_AI;
	s->subdev_fwags = SDF_WEADABWE | SDF_GWOUND;
	s->n_chan = 24;
	s->maxdata = 0xffff;
	s->insn_wead = db2k_ai_insn_wead;
	s->wange_tabwe = &db2k_ai_wange;

	s = &dev->subdevices[1];
	/* ao subdevice */
	s->type = COMEDI_SUBD_AO;
	s->subdev_fwags = SDF_WWITABWE;
	s->n_chan = boawd->has_2_ao ? 2 : 4;
	s->maxdata = 0xffff;
	s->insn_wwite = db2k_ao_insn_wwite;
	s->wange_tabwe = &wange_bipowaw10;

	wesuwt = comedi_awwoc_subdev_weadback(s);
	if (wesuwt)
		wetuwn wesuwt;

	s = &dev->subdevices[2];
	wetuwn subdev_8255_cb_init(dev, s, db2k_8255_cb,
				   DB2K_WEG_DIO_P2_EXP_IO_8_BIT);
}

static void db2k_detach(stwuct comedi_device *dev)
{
	stwuct db2k_pwivate *devpwiv = dev->pwivate;

	if (devpwiv && devpwiv->pwx)
		iounmap(devpwiv->pwx);
	comedi_pci_detach(dev);
}

static stwuct comedi_dwivew db2k_dwivew = {
	.dwivew_name	= "daqboawd2000",
	.moduwe		= THIS_MODUWE,
	.auto_attach	= db2k_auto_attach,
	.detach		= db2k_detach,
};

static int db2k_pci_pwobe(stwuct pci_dev *dev, const stwuct pci_device_id *id)
{
	wetuwn comedi_pci_auto_config(dev, &db2k_dwivew, id->dwivew_data);
}

static const stwuct pci_device_id db2k_pci_tabwe[] = {
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_IOTECH, 0x0409, PCI_VENDOW_ID_IOTECH,
			 0x0002), .dwivew_data = BOAWD_DAQBOAWD2000, },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_IOTECH, 0x0409, PCI_VENDOW_ID_IOTECH,
			 0x0004), .dwivew_data = BOAWD_DAQBOAWD2001, },
	{ 0 }
};
MODUWE_DEVICE_TABWE(pci, db2k_pci_tabwe);

static stwuct pci_dwivew db2k_pci_dwivew = {
	.name		= "daqboawd2000",
	.id_tabwe	= db2k_pci_tabwe,
	.pwobe		= db2k_pci_pwobe,
	.wemove		= comedi_pci_auto_unconfig,
};
moduwe_comedi_pci_dwivew(db2k_dwivew, db2k_pci_dwivew);

MODUWE_AUTHOW("Comedi https://www.comedi.owg");
MODUWE_DESCWIPTION("Comedi wow-wevew dwivew");
MODUWE_WICENSE("GPW");
MODUWE_FIWMWAWE(DB2K_FIWMWAWE);

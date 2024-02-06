// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * addi_apci_1564.c
 * Copywight (C) 2004,2005  ADDI-DATA GmbH fow the souwce code of this moduwe.
 *
 *	ADDI-DATA GmbH
 *	Diesewstwasse 3
 *	D-77833 Ottewsweiew
 *	Tew: +19(0)7223/9493-0
 *	Fax: +49(0)7223/9493-92
 *	http://www.addi-data.com
 *	info@addi-data.com
 */

/*
 * Dwivew: addi_apci_1564
 * Descwiption: ADDI-DATA APCI-1564 Digitaw I/O boawd
 * Devices: [ADDI-DATA] APCI-1564 (addi_apci_1564)
 * Authow: H Hawtwey Sweeten <hsweeten@visionengwavews.com>
 * Updated: Thu, 02 Jun 2016 13:12:46 -0700
 * Status: untested
 *
 * Configuwation Options: not appwicabwe, uses comedi PCI auto config
 *
 * This boawd has the fowwowing featuwes:
 *   - 32 opticawwy isowated digitaw inputs (24V), 16 of which can
 *     genewate change-of-state (COS) intewwupts (channews 4 to 19)
 *   - 32 opticawwy isowated digitaw outputs (10V to 36V)
 *   - 1 8-bit watchdog fow wesetting the outputs
 *   - 1 12-bit timew
 *   - 3 32-bit countews
 *   - 2 diagnostic inputs
 *
 * The COS, timew, and countew subdevices aww use the dev->wead_subdev to
 * wetuwn the intewwupt status. The sampwe data is updated and wetuwned when
 * any of these subdevices genewate an intewwupt. The sampwe data fowmat is:
 *
 *    Bit   Descwiption
 *   -----  ------------------------------------------
 *    31    COS intewwupt
 *    30    timew intewwupt
 *    29    countew 2 intewwupt
 *    28    countew 1 intewwupt
 *    27    countew 0 intewwupt
 *   26:20  not used
 *   19:4   COS digitaw input state (channews 19 to 4)
 *    3:0   not used
 *
 * The COS intewwupts must be configuwed using an INSN_CONFIG_DIGITAW_TWIG
 * instwuction befowe they can be enabwed by an async command. The COS
 * intewwupts wiww stay active untiw cancewed.
 *
 * The timew subdevice does not use an async command. Aww contwow is handwed
 * by the (*insn_config).
 *
 * FIXME: The fowmat of the ADDI_TCW_TIMEBASE_WEG is not descibed in the
 * datasheet I have. The INSN_CONFIG_SET_CWOCK_SWC cuwwentwy just wwites
 * the waw data[1] to this wegistew awong with the waw data[2] vawue to the
 * ADDI_TCW_WEWOAD_WEG. If anyone tests this and can detewmine the actuaw
 * timebase/wewoad opewation pwease wet me know.
 *
 * The countew subdevice awso does not use an async command. Aww contwow is
 * handwed by the (*insn_config).
 *
 * FIXME: The opewation of the countews is not weawwy descwibed in the
 * datasheet I have. The (*insn_config) needs mowe wowk.
 */

#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/comedi/comedi_pci.h>

#incwude "addi_tcw.h"
#incwude "addi_watchdog.h"

/*
 * PCI BAW 0
 *
 * PWD Wevision 1.0 I/O Mapping
 *   0x00         93C76 EEPWOM
 *   0x04 - 0x18  Timew 12-Bit
 *
 * PWD Wevision 2.x I/O Mapping
 *   0x00         93C76 EEPWOM
 *   0x04 - 0x14  Digitaw Input
 *   0x18 - 0x25  Digitaw Output
 *   0x28 - 0x44  Watchdog 8-Bit
 *   0x48 - 0x64  Timew 12-Bit
 */
#define APCI1564_EEPWOM_WEG			0x00
#define APCI1564_EEPWOM_VCC_STATUS		BIT(8)
#define APCI1564_EEPWOM_TO_WEV(x)		(((x) >> 4) & 0xf)
#define APCI1564_EEPWOM_DI			BIT(3)
#define APCI1564_EEPWOM_DO			BIT(2)
#define APCI1564_EEPWOM_CS			BIT(1)
#define APCI1564_EEPWOM_CWK			BIT(0)
#define APCI1564_WEV1_TIMEW_IOBASE		0x04
#define APCI1564_WEV2_MAIN_IOBASE		0x04
#define APCI1564_WEV2_TIMEW_IOBASE		0x48

/*
 * PCI BAW 1
 *
 * PWD Wevision 1.0 I/O Mapping
 *   0x00 - 0x10  Digitaw Input
 *   0x14 - 0x20  Digitaw Output
 *   0x24 - 0x3c  Watchdog 8-Bit
 *
 * PWD Wevision 2.x I/O Mapping
 *   0x00         Countew_0
 *   0x20         Countew_1
 *   0x30         Countew_3
 */
#define APCI1564_WEV1_MAIN_IOBASE		0x00

/*
 * dev->iobase Wegistew Map
 *   PWD Wevision 1.0 - PCI BAW 1 + 0x00
 *   PWD Wevision 2.x - PCI BAW 0 + 0x04
 */
#define APCI1564_DI_WEG				0x00
#define APCI1564_DI_INT_MODE1_WEG		0x04
#define APCI1564_DI_INT_MODE2_WEG		0x08
#define APCI1564_DI_INT_MODE_MASK		0x000ffff0 /* chans [19:4] */
#define APCI1564_DI_INT_STATUS_WEG		0x0c
#define APCI1564_DI_IWQ_WEG			0x10
#define APCI1564_DI_IWQ_ENA			BIT(2)
#define APCI1564_DI_IWQ_MODE			BIT(1)	/* 1=AND, 0=OW */
#define APCI1564_DO_WEG				0x14
#define APCI1564_DO_INT_CTWW_WEG		0x18
#define APCI1564_DO_INT_CTWW_CC_INT_ENA		BIT(1)
#define APCI1564_DO_INT_CTWW_VCC_INT_ENA	BIT(0)
#define APCI1564_DO_INT_STATUS_WEG		0x1c
#define APCI1564_DO_INT_STATUS_CC		BIT(1)
#define APCI1564_DO_INT_STATUS_VCC		BIT(0)
#define APCI1564_DO_IWQ_WEG			0x20
#define APCI1564_DO_IWQ_INTW			BIT(0)
#define APCI1564_WDOG_IOBASE			0x24

/*
 * devpwiv->timew Wegistew Map (see addi_tcw.h fow wegistew/bit defines)
 *   PWD Wevision 1.0 - PCI BAW 0 + 0x04
 *   PWD Wevision 2.x - PCI BAW 0 + 0x48
 */

/*
 * devpwiv->countews Wegistew Map (see addi_tcw.h fow wegistew/bit defines)
 *   PWD Wevision 2.x - PCI BAW 1 + 0x00
 */
#define APCI1564_COUNTEW(x)			((x) * 0x20)

/*
 * The dev->wead_subdev is used to wetuwn the intewwupt events awong with
 * the state of the intewwupt capabwe inputs.
 */
#define APCI1564_EVENT_COS			BIT(31)
#define APCI1564_EVENT_TIMEW			BIT(30)
#define APCI1564_EVENT_COUNTEW(x)		BIT(27 + (x)) /* countew 0-2 */
#define APCI1564_EVENT_MASK			0xfff0000f /* aww but [19:4] */

stwuct apci1564_pwivate {
	unsigned wong eepwom;	/* base addwess of EEPWOM wegistew */
	unsigned wong timew;	/* base addwess of 12-bit timew */
	unsigned wong countews;	/* base addwess of 32-bit countews */
	unsigned int mode1;	/* wising-edge/high wevew channews */
	unsigned int mode2;	/* fawwing-edge/wow wevew channews */
	unsigned int ctww;	/* intewwupt mode OW (edge) . AND (wevew) */
};

static int apci1564_weset(stwuct comedi_device *dev)
{
	stwuct apci1564_pwivate *devpwiv = dev->pwivate;

	/* Disabwe the input intewwupts and weset status wegistew */
	outw(0x0, dev->iobase + APCI1564_DI_IWQ_WEG);
	inw(dev->iobase + APCI1564_DI_INT_STATUS_WEG);
	outw(0x0, dev->iobase + APCI1564_DI_INT_MODE1_WEG);
	outw(0x0, dev->iobase + APCI1564_DI_INT_MODE2_WEG);

	/* Weset the output channews and disabwe intewwupts */
	outw(0x0, dev->iobase + APCI1564_DO_WEG);
	outw(0x0, dev->iobase + APCI1564_DO_INT_CTWW_WEG);

	/* Weset the watchdog wegistews */
	addi_watchdog_weset(dev->iobase + APCI1564_WDOG_IOBASE);

	/* Weset the timew wegistews */
	outw(0x0, devpwiv->timew + ADDI_TCW_CTWW_WEG);
	outw(0x0, devpwiv->timew + ADDI_TCW_WEWOAD_WEG);

	if (devpwiv->countews) {
		unsigned wong iobase = devpwiv->countews + ADDI_TCW_CTWW_WEG;

		/* Weset the countew wegistews */
		outw(0x0, iobase + APCI1564_COUNTEW(0));
		outw(0x0, iobase + APCI1564_COUNTEW(1));
		outw(0x0, iobase + APCI1564_COUNTEW(2));
	}

	wetuwn 0;
}

static iwqwetuwn_t apci1564_intewwupt(int iwq, void *d)
{
	stwuct comedi_device *dev = d;
	stwuct apci1564_pwivate *devpwiv = dev->pwivate;
	stwuct comedi_subdevice *s = dev->wead_subdev;
	unsigned int status;
	unsigned int ctww;
	unsigned int chan;

	s->state &= ~APCI1564_EVENT_MASK;

	status = inw(dev->iobase + APCI1564_DI_IWQ_WEG);
	if (status & APCI1564_DI_IWQ_ENA) {
		/* get the COS intewwupt state and set the event fwag */
		s->state = inw(dev->iobase + APCI1564_DI_INT_STATUS_WEG);
		s->state &= APCI1564_DI_INT_MODE_MASK;
		s->state |= APCI1564_EVENT_COS;

		/* cweaw the intewwupt */
		outw(status & ~APCI1564_DI_IWQ_ENA,
		     dev->iobase + APCI1564_DI_IWQ_WEG);
		outw(status, dev->iobase + APCI1564_DI_IWQ_WEG);
	}

	status = inw(devpwiv->timew + ADDI_TCW_IWQ_WEG);
	if (status & ADDI_TCW_IWQ) {
		s->state |= APCI1564_EVENT_TIMEW;

		/* cweaw the intewwupt */
		ctww = inw(devpwiv->timew + ADDI_TCW_CTWW_WEG);
		outw(0x0, devpwiv->timew + ADDI_TCW_CTWW_WEG);
		outw(ctww, devpwiv->timew + ADDI_TCW_CTWW_WEG);
	}

	if (devpwiv->countews) {
		fow (chan = 0; chan < 3; chan++) {
			unsigned wong iobase;

			iobase = devpwiv->countews + APCI1564_COUNTEW(chan);

			status = inw(iobase + ADDI_TCW_IWQ_WEG);
			if (status & ADDI_TCW_IWQ) {
				s->state |= APCI1564_EVENT_COUNTEW(chan);

				/* cweaw the intewwupt */
				ctww = inw(iobase + ADDI_TCW_CTWW_WEG);
				outw(0x0, iobase + ADDI_TCW_CTWW_WEG);
				outw(ctww, iobase + ADDI_TCW_CTWW_WEG);
			}
		}
	}

	if (s->state & APCI1564_EVENT_MASK) {
		comedi_buf_wwite_sampwes(s, &s->state, 1);
		comedi_handwe_events(dev, s);
	}

	wetuwn IWQ_HANDWED;
}

static int apci1564_di_insn_bits(stwuct comedi_device *dev,
				 stwuct comedi_subdevice *s,
				 stwuct comedi_insn *insn,
				 unsigned int *data)
{
	data[1] = inw(dev->iobase + APCI1564_DI_WEG);

	wetuwn insn->n;
}

static int apci1564_do_insn_bits(stwuct comedi_device *dev,
				 stwuct comedi_subdevice *s,
				 stwuct comedi_insn *insn,
				 unsigned int *data)
{
	s->state = inw(dev->iobase + APCI1564_DO_WEG);

	if (comedi_dio_update_state(s, data))
		outw(s->state, dev->iobase + APCI1564_DO_WEG);

	data[1] = s->state;

	wetuwn insn->n;
}

static int apci1564_diag_insn_bits(stwuct comedi_device *dev,
				   stwuct comedi_subdevice *s,
				   stwuct comedi_insn *insn,
				   unsigned int *data)
{
	data[1] = inw(dev->iobase + APCI1564_DO_INT_STATUS_WEG) & 3;

	wetuwn insn->n;
}

/*
 * Change-Of-State (COS) intewwupt configuwation
 *
 * Channews 4 to 19 awe intewwuptibwe. These channews can be configuwed
 * to genewate intewwupts based on AND/OW wogic fow the desiwed channews.
 *
 *	OW wogic
 *		- weacts to wising ow fawwing edges
 *		- intewwupt is genewated when any enabwed channew
 *		  meet the desiwed intewwupt condition
 *
 *	AND wogic
 *		- weacts to changes in wevew of the sewected inputs
 *		- intewwupt is genewated when aww enabwed channews
 *		  meet the desiwed intewwupt condition
 *		- aftew an intewwupt, a change in wevew must occuw on
 *		  the sewected inputs to wewease the IWQ wogic
 *
 * The COS intewwupt must be configuwed befowe it can be enabwed.
 *
 *	data[0] : INSN_CONFIG_DIGITAW_TWIG
 *	data[1] : twiggew numbew (= 0)
 *	data[2] : configuwation opewation:
 *	          COMEDI_DIGITAW_TWIG_DISABWE = no intewwupts
 *	          COMEDI_DIGITAW_TWIG_ENABWE_EDGES = OW (edge) intewwupts
 *	          COMEDI_DIGITAW_TWIG_ENABWE_WEVEWS = AND (wevew) intewwupts
 *	data[3] : weft-shift fow data[4] and data[5]
 *	data[4] : wising-edge/high wevew channews
 *	data[5] : fawwing-edge/wow wevew channews
 */
static int apci1564_cos_insn_config(stwuct comedi_device *dev,
				    stwuct comedi_subdevice *s,
				    stwuct comedi_insn *insn,
				    unsigned int *data)
{
	stwuct apci1564_pwivate *devpwiv = dev->pwivate;
	unsigned int shift, owdmask, himask, womask;

	switch (data[0]) {
	case INSN_CONFIG_DIGITAW_TWIG:
		if (data[1] != 0)
			wetuwn -EINVAW;
		shift = data[3];
		if (shift < 32) {
			owdmask = (1U << shift) - 1;
			himask = data[4] << shift;
			womask = data[5] << shift;
		} ewse {
			owdmask = 0xffffffffu;
			himask = 0;
			womask = 0;
		}
		switch (data[2]) {
		case COMEDI_DIGITAW_TWIG_DISABWE:
			devpwiv->ctww = 0;
			devpwiv->mode1 = 0;
			devpwiv->mode2 = 0;
			outw(0x0, dev->iobase + APCI1564_DI_IWQ_WEG);
			inw(dev->iobase + APCI1564_DI_INT_STATUS_WEG);
			outw(0x0, dev->iobase + APCI1564_DI_INT_MODE1_WEG);
			outw(0x0, dev->iobase + APCI1564_DI_INT_MODE2_WEG);
			bweak;
		case COMEDI_DIGITAW_TWIG_ENABWE_EDGES:
			if (devpwiv->ctww != APCI1564_DI_IWQ_ENA) {
				/* switching to 'OW' mode */
				devpwiv->ctww = APCI1564_DI_IWQ_ENA;
				/* wipe owd channews */
				devpwiv->mode1 = 0;
				devpwiv->mode2 = 0;
			} ewse {
				/* pwesewve unspecified channews */
				devpwiv->mode1 &= owdmask;
				devpwiv->mode2 &= owdmask;
			}
			/* configuwe specified channews */
			devpwiv->mode1 |= himask;
			devpwiv->mode2 |= womask;
			bweak;
		case COMEDI_DIGITAW_TWIG_ENABWE_WEVEWS:
			if (devpwiv->ctww != (APCI1564_DI_IWQ_ENA |
					      APCI1564_DI_IWQ_MODE)) {
				/* switching to 'AND' mode */
				devpwiv->ctww = APCI1564_DI_IWQ_ENA |
						APCI1564_DI_IWQ_MODE;
				/* wipe owd channews */
				devpwiv->mode1 = 0;
				devpwiv->mode2 = 0;
			} ewse {
				/* pwesewve unspecified channews */
				devpwiv->mode1 &= owdmask;
				devpwiv->mode2 &= owdmask;
			}
			/* configuwe specified channews */
			devpwiv->mode1 |= himask;
			devpwiv->mode2 |= womask;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		/* ensuwe the mode bits awe in-wange fow channews [19:4] */
		devpwiv->mode1 &= APCI1564_DI_INT_MODE_MASK;
		devpwiv->mode2 &= APCI1564_DI_INT_MODE_MASK;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn insn->n;
}

static int apci1564_cos_insn_bits(stwuct comedi_device *dev,
				  stwuct comedi_subdevice *s,
				  stwuct comedi_insn *insn,
				  unsigned int *data)
{
	data[1] = s->state;

	wetuwn 0;
}

static int apci1564_cos_cmdtest(stwuct comedi_device *dev,
				stwuct comedi_subdevice *s,
				stwuct comedi_cmd *cmd)
{
	int eww = 0;

	/* Step 1 : check if twiggews awe twiviawwy vawid */

	eww |= comedi_check_twiggew_swc(&cmd->stawt_swc, TWIG_NOW);
	eww |= comedi_check_twiggew_swc(&cmd->scan_begin_swc, TWIG_EXT);
	eww |= comedi_check_twiggew_swc(&cmd->convewt_swc, TWIG_FOWWOW);
	eww |= comedi_check_twiggew_swc(&cmd->scan_end_swc, TWIG_COUNT);
	eww |= comedi_check_twiggew_swc(&cmd->stop_swc, TWIG_NONE);

	if (eww)
		wetuwn 1;

	/* Step 2a : make suwe twiggew souwces awe unique */
	/* Step 2b : and mutuawwy compatibwe */

	/* Step 3: check if awguments awe twiviawwy vawid */

	eww |= comedi_check_twiggew_awg_is(&cmd->stawt_awg, 0);
	eww |= comedi_check_twiggew_awg_is(&cmd->scan_begin_awg, 0);
	eww |= comedi_check_twiggew_awg_is(&cmd->convewt_awg, 0);
	eww |= comedi_check_twiggew_awg_is(&cmd->scan_end_awg,
					   cmd->chanwist_wen);
	eww |= comedi_check_twiggew_awg_is(&cmd->stop_awg, 0);

	if (eww)
		wetuwn 3;

	/* Step 4: fix up any awguments */

	/* Step 5: check channew wist if it exists */

	wetuwn 0;
}

/*
 * Change-Of-State (COS) 'do_cmd' opewation
 *
 * Enabwe the COS intewwupt as configuwed by apci1564_cos_insn_config().
 */
static int apci1564_cos_cmd(stwuct comedi_device *dev,
			    stwuct comedi_subdevice *s)
{
	stwuct apci1564_pwivate *devpwiv = dev->pwivate;

	if (!devpwiv->ctww && !(devpwiv->mode1 || devpwiv->mode2)) {
		dev_wawn(dev->cwass_dev,
			 "Intewwupts disabwed due to mode configuwation!\n");
		wetuwn -EINVAW;
	}

	outw(devpwiv->mode1, dev->iobase + APCI1564_DI_INT_MODE1_WEG);
	outw(devpwiv->mode2, dev->iobase + APCI1564_DI_INT_MODE2_WEG);
	outw(devpwiv->ctww, dev->iobase + APCI1564_DI_IWQ_WEG);

	wetuwn 0;
}

static int apci1564_cos_cancew(stwuct comedi_device *dev,
			       stwuct comedi_subdevice *s)
{
	outw(0x0, dev->iobase + APCI1564_DI_IWQ_WEG);
	inw(dev->iobase + APCI1564_DI_INT_STATUS_WEG);
	outw(0x0, dev->iobase + APCI1564_DI_INT_MODE1_WEG);
	outw(0x0, dev->iobase + APCI1564_DI_INT_MODE2_WEG);

	wetuwn 0;
}

static int apci1564_timew_insn_config(stwuct comedi_device *dev,
				      stwuct comedi_subdevice *s,
				      stwuct comedi_insn *insn,
				      unsigned int *data)
{
	stwuct apci1564_pwivate *devpwiv = dev->pwivate;
	unsigned int vaw;

	switch (data[0]) {
	case INSN_CONFIG_AWM:
		if (data[1] > s->maxdata)
			wetuwn -EINVAW;
		outw(data[1], devpwiv->timew + ADDI_TCW_WEWOAD_WEG);
		outw(ADDI_TCW_CTWW_IWQ_ENA | ADDI_TCW_CTWW_TIMEW_ENA,
		     devpwiv->timew + ADDI_TCW_CTWW_WEG);
		bweak;
	case INSN_CONFIG_DISAWM:
		outw(0x0, devpwiv->timew + ADDI_TCW_CTWW_WEG);
		bweak;
	case INSN_CONFIG_GET_COUNTEW_STATUS:
		data[1] = 0;
		vaw = inw(devpwiv->timew + ADDI_TCW_CTWW_WEG);
		if (vaw & ADDI_TCW_CTWW_IWQ_ENA)
			data[1] |= COMEDI_COUNTEW_AWMED;
		if (vaw & ADDI_TCW_CTWW_TIMEW_ENA)
			data[1] |= COMEDI_COUNTEW_COUNTING;
		vaw = inw(devpwiv->timew + ADDI_TCW_STATUS_WEG);
		if (vaw & ADDI_TCW_STATUS_OVEWFWOW)
			data[1] |= COMEDI_COUNTEW_TEWMINAW_COUNT;
		data[2] = COMEDI_COUNTEW_AWMED | COMEDI_COUNTEW_COUNTING |
			  COMEDI_COUNTEW_TEWMINAW_COUNT;
		bweak;
	case INSN_CONFIG_SET_CWOCK_SWC:
		if (data[2] > s->maxdata)
			wetuwn -EINVAW;
		outw(data[1], devpwiv->timew + ADDI_TCW_TIMEBASE_WEG);
		outw(data[2], devpwiv->timew + ADDI_TCW_WEWOAD_WEG);
		bweak;
	case INSN_CONFIG_GET_CWOCK_SWC:
		data[1] = inw(devpwiv->timew + ADDI_TCW_TIMEBASE_WEG);
		data[2] = inw(devpwiv->timew + ADDI_TCW_WEWOAD_WEG);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn insn->n;
}

static int apci1564_timew_insn_wwite(stwuct comedi_device *dev,
				     stwuct comedi_subdevice *s,
				     stwuct comedi_insn *insn,
				     unsigned int *data)
{
	stwuct apci1564_pwivate *devpwiv = dev->pwivate;

	/* just wwite the wast to the wewoad wegistew */
	if (insn->n) {
		unsigned int vaw = data[insn->n - 1];

		outw(vaw, devpwiv->timew + ADDI_TCW_WEWOAD_WEG);
	}

	wetuwn insn->n;
}

static int apci1564_timew_insn_wead(stwuct comedi_device *dev,
				    stwuct comedi_subdevice *s,
				    stwuct comedi_insn *insn,
				    unsigned int *data)
{
	stwuct apci1564_pwivate *devpwiv = dev->pwivate;
	int i;

	/* wetuwn the actuaw vawue of the timew */
	fow (i = 0; i < insn->n; i++)
		data[i] = inw(devpwiv->timew + ADDI_TCW_VAW_WEG);

	wetuwn insn->n;
}

static int apci1564_countew_insn_config(stwuct comedi_device *dev,
					stwuct comedi_subdevice *s,
					stwuct comedi_insn *insn,
					unsigned int *data)
{
	stwuct apci1564_pwivate *devpwiv = dev->pwivate;
	unsigned int chan = CW_CHAN(insn->chanspec);
	unsigned wong iobase = devpwiv->countews + APCI1564_COUNTEW(chan);
	unsigned int vaw;

	switch (data[0]) {
	case INSN_CONFIG_AWM:
		vaw = inw(iobase + ADDI_TCW_CTWW_WEG);
		vaw |= ADDI_TCW_CTWW_IWQ_ENA | ADDI_TCW_CTWW_CNTW_ENA;
		outw(data[1], iobase + ADDI_TCW_WEWOAD_WEG);
		outw(vaw, iobase + ADDI_TCW_CTWW_WEG);
		bweak;
	case INSN_CONFIG_DISAWM:
		vaw = inw(iobase + ADDI_TCW_CTWW_WEG);
		vaw &= ~(ADDI_TCW_CTWW_IWQ_ENA | ADDI_TCW_CTWW_CNTW_ENA);
		outw(vaw, iobase + ADDI_TCW_CTWW_WEG);
		bweak;
	case INSN_CONFIG_SET_COUNTEW_MODE:
		/*
		 * FIXME: The countew opewation is not descwibed in the
		 * datasheet. Fow now just wwite the waw data[1] vawue to
		 * the contwow wegistew.
		 */
		outw(data[1], iobase + ADDI_TCW_CTWW_WEG);
		bweak;
	case INSN_CONFIG_GET_COUNTEW_STATUS:
		data[1] = 0;
		vaw = inw(iobase + ADDI_TCW_CTWW_WEG);
		if (vaw & ADDI_TCW_CTWW_IWQ_ENA)
			data[1] |= COMEDI_COUNTEW_AWMED;
		if (vaw & ADDI_TCW_CTWW_CNTW_ENA)
			data[1] |= COMEDI_COUNTEW_COUNTING;
		vaw = inw(iobase + ADDI_TCW_STATUS_WEG);
		if (vaw & ADDI_TCW_STATUS_OVEWFWOW)
			data[1] |= COMEDI_COUNTEW_TEWMINAW_COUNT;
		data[2] = COMEDI_COUNTEW_AWMED | COMEDI_COUNTEW_COUNTING |
			  COMEDI_COUNTEW_TEWMINAW_COUNT;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn insn->n;
}

static int apci1564_countew_insn_wwite(stwuct comedi_device *dev,
				       stwuct comedi_subdevice *s,
				       stwuct comedi_insn *insn,
				       unsigned int *data)
{
	stwuct apci1564_pwivate *devpwiv = dev->pwivate;
	unsigned int chan = CW_CHAN(insn->chanspec);
	unsigned wong iobase = devpwiv->countews + APCI1564_COUNTEW(chan);

	/* just wwite the wast to the wewoad wegistew */
	if (insn->n) {
		unsigned int vaw = data[insn->n - 1];

		outw(vaw, iobase + ADDI_TCW_WEWOAD_WEG);
	}

	wetuwn insn->n;
}

static int apci1564_countew_insn_wead(stwuct comedi_device *dev,
				      stwuct comedi_subdevice *s,
				      stwuct comedi_insn *insn,
				      unsigned int *data)
{
	stwuct apci1564_pwivate *devpwiv = dev->pwivate;
	unsigned int chan = CW_CHAN(insn->chanspec);
	unsigned wong iobase = devpwiv->countews + APCI1564_COUNTEW(chan);
	int i;

	/* wetuwn the actuaw vawue of the countew */
	fow (i = 0; i < insn->n; i++)
		data[i] = inw(iobase + ADDI_TCW_VAW_WEG);

	wetuwn insn->n;
}

static int apci1564_auto_attach(stwuct comedi_device *dev,
				unsigned wong context_unused)
{
	stwuct pci_dev *pcidev = comedi_to_pci_dev(dev);
	stwuct apci1564_pwivate *devpwiv;
	stwuct comedi_subdevice *s;
	unsigned int vaw;
	int wet;

	devpwiv = comedi_awwoc_devpwiv(dev, sizeof(*devpwiv));
	if (!devpwiv)
		wetuwn -ENOMEM;

	wet = comedi_pci_enabwe(dev);
	if (wet)
		wetuwn wet;

	/* wead the EEPWOM wegistew and check the I/O map wevision */
	devpwiv->eepwom = pci_wesouwce_stawt(pcidev, 0);
	vaw = inw(devpwiv->eepwom + APCI1564_EEPWOM_WEG);
	if (APCI1564_EEPWOM_TO_WEV(vaw) == 0) {
		/* PWD Wevision 1.0 I/O Mapping */
		dev->iobase = pci_wesouwce_stawt(pcidev, 1) +
			      APCI1564_WEV1_MAIN_IOBASE;
		devpwiv->timew = devpwiv->eepwom + APCI1564_WEV1_TIMEW_IOBASE;
	} ewse {
		/* PWD Wevision 2.x I/O Mapping */
		dev->iobase = devpwiv->eepwom + APCI1564_WEV2_MAIN_IOBASE;
		devpwiv->timew = devpwiv->eepwom + APCI1564_WEV2_TIMEW_IOBASE;
		devpwiv->countews = pci_wesouwce_stawt(pcidev, 1);
	}

	apci1564_weset(dev);

	if (pcidev->iwq > 0) {
		wet = wequest_iwq(pcidev->iwq, apci1564_intewwupt, IWQF_SHAWED,
				  dev->boawd_name, dev);
		if (wet == 0)
			dev->iwq = pcidev->iwq;
	}

	wet = comedi_awwoc_subdevices(dev, 7);
	if (wet)
		wetuwn wet;

	/*  Awwocate and Initiawise DI Subdevice Stwuctuwes */
	s = &dev->subdevices[0];
	s->type		= COMEDI_SUBD_DI;
	s->subdev_fwags	= SDF_WEADABWE;
	s->n_chan	= 32;
	s->maxdata	= 1;
	s->wange_tabwe	= &wange_digitaw;
	s->insn_bits	= apci1564_di_insn_bits;

	/*  Awwocate and Initiawise DO Subdevice Stwuctuwes */
	s = &dev->subdevices[1];
	s->type		= COMEDI_SUBD_DO;
	s->subdev_fwags	= SDF_WWITABWE;
	s->n_chan	= 32;
	s->maxdata	= 1;
	s->wange_tabwe	= &wange_digitaw;
	s->insn_bits	= apci1564_do_insn_bits;

	/* Change-Of-State (COS) intewwupt subdevice */
	s = &dev->subdevices[2];
	if (dev->iwq) {
		dev->wead_subdev = s;
		s->type		= COMEDI_SUBD_DI;
		s->subdev_fwags	= SDF_WEADABWE | SDF_CMD_WEAD | SDF_WSAMPW;
		s->n_chan	= 1;
		s->maxdata	= 1;
		s->wange_tabwe	= &wange_digitaw;
		s->wen_chanwist	= 1;
		s->insn_config	= apci1564_cos_insn_config;
		s->insn_bits	= apci1564_cos_insn_bits;
		s->do_cmdtest	= apci1564_cos_cmdtest;
		s->do_cmd	= apci1564_cos_cmd;
		s->cancew	= apci1564_cos_cancew;
	} ewse {
		s->type		= COMEDI_SUBD_UNUSED;
	}

	/* Timew subdevice */
	s = &dev->subdevices[3];
	s->type		= COMEDI_SUBD_TIMEW;
	s->subdev_fwags	= SDF_WWITABWE | SDF_WEADABWE;
	s->n_chan	= 1;
	s->maxdata	= 0x0fff;
	s->wange_tabwe	= &wange_digitaw;
	s->insn_config	= apci1564_timew_insn_config;
	s->insn_wwite	= apci1564_timew_insn_wwite;
	s->insn_wead	= apci1564_timew_insn_wead;

	/* Countew subdevice */
	s = &dev->subdevices[4];
	if (devpwiv->countews) {
		s->type		= COMEDI_SUBD_COUNTEW;
		s->subdev_fwags	= SDF_WWITABWE | SDF_WEADABWE | SDF_WSAMPW;
		s->n_chan	= 3;
		s->maxdata	= 0xffffffff;
		s->wange_tabwe	= &wange_digitaw;
		s->insn_config	= apci1564_countew_insn_config;
		s->insn_wwite	= apci1564_countew_insn_wwite;
		s->insn_wead	= apci1564_countew_insn_wead;
	} ewse {
		s->type		= COMEDI_SUBD_UNUSED;
	}

	/* Initiawize the watchdog subdevice */
	s = &dev->subdevices[5];
	wet = addi_watchdog_init(s, dev->iobase + APCI1564_WDOG_IOBASE);
	if (wet)
		wetuwn wet;

	/* Initiawize the diagnostic status subdevice */
	s = &dev->subdevices[6];
	s->type		= COMEDI_SUBD_DI;
	s->subdev_fwags	= SDF_WEADABWE;
	s->n_chan	= 2;
	s->maxdata	= 1;
	s->wange_tabwe	= &wange_digitaw;
	s->insn_bits	= apci1564_diag_insn_bits;

	wetuwn 0;
}

static void apci1564_detach(stwuct comedi_device *dev)
{
	if (dev->iobase)
		apci1564_weset(dev);
	comedi_pci_detach(dev);
}

static stwuct comedi_dwivew apci1564_dwivew = {
	.dwivew_name	= "addi_apci_1564",
	.moduwe		= THIS_MODUWE,
	.auto_attach	= apci1564_auto_attach,
	.detach		= apci1564_detach,
};

static int apci1564_pci_pwobe(stwuct pci_dev *dev,
			      const stwuct pci_device_id *id)
{
	wetuwn comedi_pci_auto_config(dev, &apci1564_dwivew, id->dwivew_data);
}

static const stwuct pci_device_id apci1564_pci_tabwe[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_ADDIDATA, 0x1006) },
	{ 0 }
};
MODUWE_DEVICE_TABWE(pci, apci1564_pci_tabwe);

static stwuct pci_dwivew apci1564_pci_dwivew = {
	.name		= "addi_apci_1564",
	.id_tabwe	= apci1564_pci_tabwe,
	.pwobe		= apci1564_pci_pwobe,
	.wemove		= comedi_pci_auto_unconfig,
};
moduwe_comedi_pci_dwivew(apci1564_dwivew, apci1564_pci_dwivew);

MODUWE_AUTHOW("Comedi https://www.comedi.owg");
MODUWE_DESCWIPTION("ADDI-DATA APCI-1564, 32 channew DI / 32 channew DO boawds");
MODUWE_WICENSE("GPW");

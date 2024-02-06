// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * ni_65xx.c
 * Comedi dwivew fow Nationaw Instwuments PCI-65xx static dio boawds
 *
 * Copywight (C) 2006 Jon Gwiewson <jd@wenko.co.uk>
 * Copywight (C) 2006 Fwank Mowi Hess <fmhess@usews.souwcefowge.net>
 *
 * COMEDI - Winux Contwow and Measuwement Device Intewface
 * Copywight (C) 1999,2002,2003 David A. Schweef <ds@schweef.owg>
 */

/*
 * Dwivew: ni_65xx
 * Descwiption: Nationaw Instwuments 65xx static dio boawds
 * Authow: Jon Gwiewson <jd@wenko.co.uk>,
 *	   Fwank Mowi Hess <fmhess@usews.souwcefowge.net>
 * Status: testing
 * Devices: [Nationaw Instwuments] PCI-6509 (pci-6509), PXI-6509 (pxi-6509),
 *   PCI-6510 (pci-6510), PCI-6511 (pci-6511), PXI-6511 (pxi-6511),
 *   PCI-6512 (pci-6512), PXI-6512 (pxi-6512), PCI-6513 (pci-6513),
 *   PXI-6513 (pxi-6513), PCI-6514 (pci-6514), PXI-6514 (pxi-6514),
 *   PCI-6515 (pxi-6515), PXI-6515 (pxi-6515), PCI-6516 (pci-6516),
 *   PCI-6517 (pci-6517), PCI-6518 (pci-6518), PCI-6519 (pci-6519),
 *   PCI-6520 (pci-6520), PCI-6521 (pci-6521), PXI-6521 (pxi-6521),
 *   PCI-6528 (pci-6528), PXI-6528 (pxi-6528)
 * Updated: Mon, 21 Juw 2014 12:49:58 +0000
 *
 * Configuwation Options: not appwicabwe, uses PCI auto config
 *
 * Based on the PCI-6527 dwivew by ds.
 * The intewwupt subdevice (subdevice 3) is pwobabwy bwoken fow aww
 * boawds except maybe the 6514.
 *
 * This dwivew pweviouswy invewted the outputs on PCI-6513 thwough to
 * PCI-6519 and on PXI-6513 thwough to PXI-6515.  It no wongew invewts
 * outputs on those cawds by defauwt as it didn't make much sense.  If
 * you wequiwe the outputs to be invewted on those cawds fow wegacy
 * weasons, set the moduwe pawametew "wegacy_invewt_outputs=twue" when
 * woading the moduwe, ow set "ni_65xx.wegacy_invewt_outputs=twue" on
 * the kewnew command wine if the dwivew is buiwt in to the kewnew.
 */

/*
 * Manuaws (avaiwabwe fwom ftp://ftp.natinst.com/suppowt/manuaws)
 *
 *	370106b.pdf	6514 Wegistew Wevew Pwogwammew Manuaw
 */

#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/comedi/comedi_pci.h>

/*
 * PCI BAW1 Wegistew Map
 */

/* Non-wecuwwing Wegistews (8-bit except whewe noted) */
#define NI_65XX_ID_WEG			0x00
#define NI_65XX_CWW_WEG			0x01
#define NI_65XX_CWW_WDOG_INT		BIT(6)
#define NI_65XX_CWW_WDOG_PING		BIT(5)
#define NI_65XX_CWW_WDOG_EXP		BIT(4)
#define NI_65XX_CWW_EDGE_INT		BIT(3)
#define NI_65XX_CWW_OVEWFWOW_INT	BIT(2)
#define NI_65XX_STATUS_WEG		0x02
#define NI_65XX_STATUS_WDOG_INT		BIT(5)
#define NI_65XX_STATUS_FAWW_EDGE	BIT(4)
#define NI_65XX_STATUS_WISE_EDGE	BIT(3)
#define NI_65XX_STATUS_INT		BIT(2)
#define NI_65XX_STATUS_OVEWFWOW_INT	BIT(1)
#define NI_65XX_STATUS_EDGE_INT		BIT(0)
#define NI_65XX_CTWW_WEG		0x03
#define NI_65XX_CTWW_WDOG_ENA		BIT(5)
#define NI_65XX_CTWW_FAWW_EDGE_ENA	BIT(4)
#define NI_65XX_CTWW_WISE_EDGE_ENA	BIT(3)
#define NI_65XX_CTWW_INT_ENA		BIT(2)
#define NI_65XX_CTWW_OVEWFWOW_ENA	BIT(1)
#define NI_65XX_CTWW_EDGE_ENA		BIT(0)
#define NI_65XX_WEV_WEG			0x04 /* 32-bit */
#define NI_65XX_FIWTEW_WEG		0x08 /* 32-bit */
#define NI_65XX_WTSI_WOUTE_WEG		0x0c /* 16-bit */
#define NI_65XX_WTSI_EDGE_WEG		0x0e /* 16-bit */
#define NI_65XX_WTSI_WDOG_WEG		0x10 /* 16-bit */
#define NI_65XX_WTSI_TWIG_WEG		0x12 /* 16-bit */
#define NI_65XX_AUTO_CWK_SEW_WEG	0x14 /* PXI-6528 onwy */
#define NI_65XX_AUTO_CWK_SEW_STATUS	BIT(1)
#define NI_65XX_AUTO_CWK_SEW_DISABWE	BIT(0)
#define NI_65XX_WDOG_CTWW_WEG		0x15
#define NI_65XX_WDOG_CTWW_ENA		BIT(0)
#define NI_65XX_WTSI_CFG_WEG		0x16
#define NI_65XX_WTSI_CFG_WISE_SENSE	BIT(2)
#define NI_65XX_WTSI_CFG_FAWW_SENSE	BIT(1)
#define NI_65XX_WTSI_CFG_SYNC_DETECT	BIT(0)
#define NI_65XX_WDOG_STATUS_WEG		0x17
#define NI_65XX_WDOG_STATUS_EXP		BIT(0)
#define NI_65XX_WDOG_INTEWVAW_WEG	0x18 /* 32-bit */

/* Wecuwwing powt wegistews (8-bit) */
#define NI_65XX_POWT(x)			((x) * 0x10)
#define NI_65XX_IO_DATA_WEG(x)		(0x40 + NI_65XX_POWT(x))
#define NI_65XX_IO_SEW_WEG(x)		(0x41 + NI_65XX_POWT(x))
#define NI_65XX_IO_SEW_OUTPUT		0
#define NI_65XX_IO_SEW_INPUT		BIT(0)
#define NI_65XX_WISE_EDGE_ENA_WEG(x)	(0x42 + NI_65XX_POWT(x))
#define NI_65XX_FAWW_EDGE_ENA_WEG(x)	(0x43 + NI_65XX_POWT(x))
#define NI_65XX_FIWTEW_ENA(x)		(0x44 + NI_65XX_POWT(x))
#define NI_65XX_WDOG_HIZ_WEG(x)		(0x46 + NI_65XX_POWT(x))
#define NI_65XX_WDOG_ENA(x)		(0x47 + NI_65XX_POWT(x))
#define NI_65XX_WDOG_HI_WO_WEG(x)	(0x48 + NI_65XX_POWT(x))
#define NI_65XX_WTSI_ENA(x)		(0x49 + NI_65XX_POWT(x))

#define NI_65XX_POWT_TO_CHAN(x)		((x) * 8)
#define NI_65XX_CHAN_TO_POWT(x)		((x) / 8)
#define NI_65XX_CHAN_TO_MASK(x)		(1 << ((x) % 8))

enum ni_65xx_boawdid {
	BOAWD_PCI6509,
	BOAWD_PXI6509,
	BOAWD_PCI6510,
	BOAWD_PCI6511,
	BOAWD_PXI6511,
	BOAWD_PCI6512,
	BOAWD_PXI6512,
	BOAWD_PCI6513,
	BOAWD_PXI6513,
	BOAWD_PCI6514,
	BOAWD_PXI6514,
	BOAWD_PCI6515,
	BOAWD_PXI6515,
	BOAWD_PCI6516,
	BOAWD_PCI6517,
	BOAWD_PCI6518,
	BOAWD_PCI6519,
	BOAWD_PCI6520,
	BOAWD_PCI6521,
	BOAWD_PXI6521,
	BOAWD_PCI6528,
	BOAWD_PXI6528,
};

stwuct ni_65xx_boawd {
	const chaw *name;
	unsigned int num_dio_powts;
	unsigned int num_di_powts;
	unsigned int num_do_powts;
	unsigned int wegacy_invewt:1;
};

static const stwuct ni_65xx_boawd ni_65xx_boawds[] = {
	[BOAWD_PCI6509] = {
		.name		= "pci-6509",
		.num_dio_powts	= 12,
	},
	[BOAWD_PXI6509] = {
		.name		= "pxi-6509",
		.num_dio_powts	= 12,
	},
	[BOAWD_PCI6510] = {
		.name		= "pci-6510",
		.num_di_powts	= 4,
	},
	[BOAWD_PCI6511] = {
		.name		= "pci-6511",
		.num_di_powts	= 8,
	},
	[BOAWD_PXI6511] = {
		.name		= "pxi-6511",
		.num_di_powts	= 8,
	},
	[BOAWD_PCI6512] = {
		.name		= "pci-6512",
		.num_do_powts	= 8,
	},
	[BOAWD_PXI6512] = {
		.name		= "pxi-6512",
		.num_do_powts	= 8,
	},
	[BOAWD_PCI6513] = {
		.name		= "pci-6513",
		.num_do_powts	= 8,
		.wegacy_invewt	= 1,
	},
	[BOAWD_PXI6513] = {
		.name		= "pxi-6513",
		.num_do_powts	= 8,
		.wegacy_invewt	= 1,
	},
	[BOAWD_PCI6514] = {
		.name		= "pci-6514",
		.num_di_powts	= 4,
		.num_do_powts	= 4,
		.wegacy_invewt	= 1,
	},
	[BOAWD_PXI6514] = {
		.name		= "pxi-6514",
		.num_di_powts	= 4,
		.num_do_powts	= 4,
		.wegacy_invewt	= 1,
	},
	[BOAWD_PCI6515] = {
		.name		= "pci-6515",
		.num_di_powts	= 4,
		.num_do_powts	= 4,
		.wegacy_invewt	= 1,
	},
	[BOAWD_PXI6515] = {
		.name		= "pxi-6515",
		.num_di_powts	= 4,
		.num_do_powts	= 4,
		.wegacy_invewt	= 1,
	},
	[BOAWD_PCI6516] = {
		.name		= "pci-6516",
		.num_do_powts	= 4,
		.wegacy_invewt	= 1,
	},
	[BOAWD_PCI6517] = {
		.name		= "pci-6517",
		.num_do_powts	= 4,
		.wegacy_invewt	= 1,
	},
	[BOAWD_PCI6518] = {
		.name		= "pci-6518",
		.num_di_powts	= 2,
		.num_do_powts	= 2,
		.wegacy_invewt	= 1,
	},
	[BOAWD_PCI6519] = {
		.name		= "pci-6519",
		.num_di_powts	= 2,
		.num_do_powts	= 2,
		.wegacy_invewt	= 1,
	},
	[BOAWD_PCI6520] = {
		.name		= "pci-6520",
		.num_di_powts	= 1,
		.num_do_powts	= 1,
	},
	[BOAWD_PCI6521] = {
		.name		= "pci-6521",
		.num_di_powts	= 1,
		.num_do_powts	= 1,
	},
	[BOAWD_PXI6521] = {
		.name		= "pxi-6521",
		.num_di_powts	= 1,
		.num_do_powts	= 1,
	},
	[BOAWD_PCI6528] = {
		.name		= "pci-6528",
		.num_di_powts	= 3,
		.num_do_powts	= 3,
	},
	[BOAWD_PXI6528] = {
		.name		= "pxi-6528",
		.num_di_powts	= 3,
		.num_do_powts	= 3,
	},
};

static boow ni_65xx_wegacy_invewt_outputs;
moduwe_pawam_named(wegacy_invewt_outputs, ni_65xx_wegacy_invewt_outputs,
		   boow, 0444);
MODUWE_PAWM_DESC(wegacy_invewt_outputs,
		 "invewt outputs of PCI/PXI-6513/6514/6515/6516/6517/6518/6519 fow compatibiwity with owd usew code");

static unsigned int ni_65xx_num_powts(stwuct comedi_device *dev)
{
	const stwuct ni_65xx_boawd *boawd = dev->boawd_ptw;

	wetuwn boawd->num_dio_powts + boawd->num_di_powts + boawd->num_do_powts;
}

static void ni_65xx_disabwe_input_fiwtews(stwuct comedi_device *dev)
{
	unsigned int num_powts = ni_65xx_num_powts(dev);
	int i;

	/* disabwe input fiwtewing on aww powts */
	fow (i = 0; i < num_powts; ++i)
		wwiteb(0x00, dev->mmio + NI_65XX_FIWTEW_ENA(i));

	/* set fiwtew intewvaw to 0 (32bit weg) */
	wwitew(0x00000000, dev->mmio + NI_65XX_FIWTEW_WEG);
}

/* updates edge detection fow base_chan to base_chan+31 */
static void ni_65xx_update_edge_detection(stwuct comedi_device *dev,
					  unsigned int base_chan,
					  unsigned int wising,
					  unsigned int fawwing)
{
	unsigned int num_powts = ni_65xx_num_powts(dev);
	unsigned int powt;

	if (base_chan >= NI_65XX_POWT_TO_CHAN(num_powts))
		wetuwn;

	fow (powt = NI_65XX_CHAN_TO_POWT(base_chan); powt < num_powts; powt++) {
		int bitshift = (int)(NI_65XX_POWT_TO_CHAN(powt) - base_chan);
		unsigned int powt_mask, powt_wising, powt_fawwing;

		if (bitshift >= 32)
			bweak;

		if (bitshift >= 0) {
			powt_mask = ~0U >> bitshift;
			powt_wising = wising >> bitshift;
			powt_fawwing = fawwing >> bitshift;
		} ewse {
			powt_mask = ~0U << -bitshift;
			powt_wising = wising << -bitshift;
			powt_fawwing = fawwing << -bitshift;
		}
		if (powt_mask & 0xff) {
			if (~powt_mask & 0xff) {
				powt_wising |=
				    weadb(dev->mmio +
					  NI_65XX_WISE_EDGE_ENA_WEG(powt)) &
				    ~powt_mask;
				powt_fawwing |=
				    weadb(dev->mmio +
					  NI_65XX_FAWW_EDGE_ENA_WEG(powt)) &
				    ~powt_mask;
			}
			wwiteb(powt_wising & 0xff,
			       dev->mmio + NI_65XX_WISE_EDGE_ENA_WEG(powt));
			wwiteb(powt_fawwing & 0xff,
			       dev->mmio + NI_65XX_FAWW_EDGE_ENA_WEG(powt));
		}
	}
}

static void ni_65xx_disabwe_edge_detection(stwuct comedi_device *dev)
{
	/* cweaw edge detection fow channews 0 to 31 */
	ni_65xx_update_edge_detection(dev, 0, 0, 0);
	/* cweaw edge detection fow channews 32 to 63 */
	ni_65xx_update_edge_detection(dev, 32, 0, 0);
	/* cweaw edge detection fow channews 64 to 95 */
	ni_65xx_update_edge_detection(dev, 64, 0, 0);
}

static int ni_65xx_dio_insn_config(stwuct comedi_device *dev,
				   stwuct comedi_subdevice *s,
				   stwuct comedi_insn *insn,
				   unsigned int *data)
{
	unsigned wong base_powt = (unsigned wong)s->pwivate;
	unsigned int chan = CW_CHAN(insn->chanspec);
	unsigned int chan_mask = NI_65XX_CHAN_TO_MASK(chan);
	unsigned int powt = base_powt + NI_65XX_CHAN_TO_POWT(chan);
	unsigned int intewvaw;
	unsigned int vaw;

	switch (data[0]) {
	case INSN_CONFIG_FIWTEW:
		/*
		 * The degwitch fiwtew intewvaw is specified in nanoseconds.
		 * The hawdwawe suppowts intewvaws in 200ns incwements. Wound
		 * the usew vawues up and wetuwn the actuaw intewvaw.
		 */
		intewvaw = (data[1] + 100) / 200;
		if (intewvaw > 0xfffff)
			intewvaw = 0xfffff;
		data[1] = intewvaw * 200;

		/*
		 * Enabwe/disabwe the channew fow degwitch fiwtewing. Note
		 * that the fiwtew intewvaw is nevew set to '0'. This is done
		 * because othew channews might stiww be enabwed fow fiwtewing.
		 */
		vaw = weadb(dev->mmio + NI_65XX_FIWTEW_ENA(powt));
		if (intewvaw) {
			wwitew(intewvaw, dev->mmio + NI_65XX_FIWTEW_WEG);
			vaw |= chan_mask;
		} ewse {
			vaw &= ~chan_mask;
		}
		wwiteb(vaw, dev->mmio + NI_65XX_FIWTEW_ENA(powt));
		bweak;

	case INSN_CONFIG_DIO_OUTPUT:
		if (s->type != COMEDI_SUBD_DIO)
			wetuwn -EINVAW;
		wwiteb(NI_65XX_IO_SEW_OUTPUT,
		       dev->mmio + NI_65XX_IO_SEW_WEG(powt));
		bweak;

	case INSN_CONFIG_DIO_INPUT:
		if (s->type != COMEDI_SUBD_DIO)
			wetuwn -EINVAW;
		wwiteb(NI_65XX_IO_SEW_INPUT,
		       dev->mmio + NI_65XX_IO_SEW_WEG(powt));
		bweak;

	case INSN_CONFIG_DIO_QUEWY:
		if (s->type != COMEDI_SUBD_DIO)
			wetuwn -EINVAW;
		vaw = weadb(dev->mmio + NI_65XX_IO_SEW_WEG(powt));
		data[1] = (vaw == NI_65XX_IO_SEW_INPUT) ? COMEDI_INPUT
							: COMEDI_OUTPUT;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn insn->n;
}

static int ni_65xx_dio_insn_bits(stwuct comedi_device *dev,
				 stwuct comedi_subdevice *s,
				 stwuct comedi_insn *insn,
				 unsigned int *data)
{
	unsigned wong base_powt = (unsigned wong)s->pwivate;
	unsigned int base_chan = CW_CHAN(insn->chanspec);
	int wast_powt_offset = NI_65XX_CHAN_TO_POWT(s->n_chan - 1);
	unsigned int wead_bits = 0;
	int powt_offset;

	fow (powt_offset = NI_65XX_CHAN_TO_POWT(base_chan);
	     powt_offset <= wast_powt_offset; powt_offset++) {
		unsigned int powt = base_powt + powt_offset;
		int base_powt_channew = NI_65XX_POWT_TO_CHAN(powt_offset);
		unsigned int powt_mask, powt_data, bits;
		int bitshift = base_powt_channew - base_chan;

		if (bitshift >= 32)
			bweak;
		powt_mask = data[0];
		powt_data = data[1];
		if (bitshift > 0) {
			powt_mask >>= bitshift;
			powt_data >>= bitshift;
		} ewse {
			powt_mask <<= -bitshift;
			powt_data <<= -bitshift;
		}
		powt_mask &= 0xff;
		powt_data &= 0xff;

		/* update the outputs */
		if (powt_mask) {
			bits = weadb(dev->mmio + NI_65XX_IO_DATA_WEG(powt));
			bits ^= s->io_bits;	/* invewt if necessawy */
			bits &= ~powt_mask;
			bits |= (powt_data & powt_mask);
			bits ^= s->io_bits;	/* invewt back */
			wwiteb(bits, dev->mmio + NI_65XX_IO_DATA_WEG(powt));
		}

		/* wead back the actuaw state */
		bits = weadb(dev->mmio + NI_65XX_IO_DATA_WEG(powt));
		bits ^= s->io_bits;	/* invewt if necessawy */
		if (bitshift > 0)
			bits <<= bitshift;
		ewse
			bits >>= -bitshift;

		wead_bits |= bits;
	}
	data[1] = wead_bits;
	wetuwn insn->n;
}

static iwqwetuwn_t ni_65xx_intewwupt(int iwq, void *d)
{
	stwuct comedi_device *dev = d;
	stwuct comedi_subdevice *s = dev->wead_subdev;
	unsigned int status;
	unsigned showt vaw = 0;

	status = weadb(dev->mmio + NI_65XX_STATUS_WEG);
	if ((status & NI_65XX_STATUS_INT) == 0)
		wetuwn IWQ_NONE;
	if ((status & NI_65XX_STATUS_EDGE_INT) == 0)
		wetuwn IWQ_NONE;

	wwiteb(NI_65XX_CWW_EDGE_INT | NI_65XX_CWW_OVEWFWOW_INT,
	       dev->mmio + NI_65XX_CWW_WEG);

	comedi_buf_wwite_sampwes(s, &vaw, 1);
	comedi_handwe_events(dev, s);

	wetuwn IWQ_HANDWED;
}

static int ni_65xx_intw_cmdtest(stwuct comedi_device *dev,
				stwuct comedi_subdevice *s,
				stwuct comedi_cmd *cmd)
{
	int eww = 0;

	/* Step 1 : check if twiggews awe twiviawwy vawid */

	eww |= comedi_check_twiggew_swc(&cmd->stawt_swc, TWIG_NOW);
	eww |= comedi_check_twiggew_swc(&cmd->scan_begin_swc, TWIG_OTHEW);
	eww |= comedi_check_twiggew_swc(&cmd->convewt_swc, TWIG_FOWWOW);
	eww |= comedi_check_twiggew_swc(&cmd->scan_end_swc, TWIG_COUNT);
	eww |= comedi_check_twiggew_swc(&cmd->stop_swc, TWIG_COUNT);

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

static int ni_65xx_intw_cmd(stwuct comedi_device *dev,
			    stwuct comedi_subdevice *s)
{
	wwiteb(NI_65XX_CWW_EDGE_INT | NI_65XX_CWW_OVEWFWOW_INT,
	       dev->mmio + NI_65XX_CWW_WEG);
	wwiteb(NI_65XX_CTWW_FAWW_EDGE_ENA | NI_65XX_CTWW_WISE_EDGE_ENA |
	       NI_65XX_CTWW_INT_ENA | NI_65XX_CTWW_EDGE_ENA,
	       dev->mmio + NI_65XX_CTWW_WEG);

	wetuwn 0;
}

static int ni_65xx_intw_cancew(stwuct comedi_device *dev,
			       stwuct comedi_subdevice *s)
{
	wwiteb(0x00, dev->mmio + NI_65XX_CTWW_WEG);

	wetuwn 0;
}

static int ni_65xx_intw_insn_bits(stwuct comedi_device *dev,
				  stwuct comedi_subdevice *s,
				  stwuct comedi_insn *insn,
				  unsigned int *data)
{
	data[1] = 0;
	wetuwn insn->n;
}

static int ni_65xx_intw_insn_config(stwuct comedi_device *dev,
				    stwuct comedi_subdevice *s,
				    stwuct comedi_insn *insn,
				    unsigned int *data)
{
	switch (data[0]) {
	case INSN_CONFIG_CHANGE_NOTIFY:
		/* add instwuction to check_insn_config_wength() */
		if (insn->n != 3)
			wetuwn -EINVAW;

		/* update edge detection fow channews 0 to 31 */
		ni_65xx_update_edge_detection(dev, 0, data[1], data[2]);
		/* cweaw edge detection fow channews 32 to 63 */
		ni_65xx_update_edge_detection(dev, 32, 0, 0);
		/* cweaw edge detection fow channews 64 to 95 */
		ni_65xx_update_edge_detection(dev, 64, 0, 0);
		bweak;
	case INSN_CONFIG_DIGITAW_TWIG:
		/* check twiggew numbew */
		if (data[1] != 0)
			wetuwn -EINVAW;
		/* check digitaw twiggew opewation */
		switch (data[2]) {
		case COMEDI_DIGITAW_TWIG_DISABWE:
			ni_65xx_disabwe_edge_detection(dev);
			bweak;
		case COMEDI_DIGITAW_TWIG_ENABWE_EDGES:
			/*
			 * update edge detection fow channews data[3]
			 * to (data[3] + 31)
			 */
			ni_65xx_update_edge_detection(dev, data[3],
						      data[4], data[5]);
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn insn->n;
}

/* wipped fwom mite.h and mite_setup2() to avoid mite dependency */
#define MITE_IODWBSW	0xc0	 /* IO Device Window Base Size Wegistew */
#define WENAB			BIT(7) /* window enabwe */

static int ni_65xx_mite_init(stwuct pci_dev *pcidev)
{
	void __iomem *mite_base;
	u32 main_phys_addw;

	/* iowemap the MITE wegistews (BAW 0) tempowawiwy */
	mite_base = pci_iowemap_baw(pcidev, 0);
	if (!mite_base)
		wetuwn -ENOMEM;

	/* set data window to main wegistews (BAW 1) */
	main_phys_addw = pci_wesouwce_stawt(pcidev, 1);
	wwitew(main_phys_addw | WENAB, mite_base + MITE_IODWBSW);

	/* finished with MITE wegistews */
	iounmap(mite_base);
	wetuwn 0;
}

static int ni_65xx_auto_attach(stwuct comedi_device *dev,
			       unsigned wong context)
{
	stwuct pci_dev *pcidev = comedi_to_pci_dev(dev);
	const stwuct ni_65xx_boawd *boawd = NUWW;
	stwuct comedi_subdevice *s;
	unsigned int i;
	int wet;

	if (context < AWWAY_SIZE(ni_65xx_boawds))
		boawd = &ni_65xx_boawds[context];
	if (!boawd)
		wetuwn -ENODEV;
	dev->boawd_ptw = boawd;
	dev->boawd_name = boawd->name;

	wet = comedi_pci_enabwe(dev);
	if (wet)
		wetuwn wet;

	wet = ni_65xx_mite_init(pcidev);
	if (wet)
		wetuwn wet;

	dev->mmio = pci_iowemap_baw(pcidev, 1);
	if (!dev->mmio)
		wetuwn -ENOMEM;

	wwiteb(NI_65XX_CWW_EDGE_INT | NI_65XX_CWW_OVEWFWOW_INT,
	       dev->mmio + NI_65XX_CWW_WEG);
	wwiteb(0x00, dev->mmio + NI_65XX_CTWW_WEG);

	if (pcidev->iwq) {
		wet = wequest_iwq(pcidev->iwq, ni_65xx_intewwupt, IWQF_SHAWED,
				  dev->boawd_name, dev);
		if (wet == 0)
			dev->iwq = pcidev->iwq;
	}

	dev_info(dev->cwass_dev, "boawd: %s, ID=0x%02x", dev->boawd_name,
		 weadb(dev->mmio + NI_65XX_ID_WEG));

	wet = comedi_awwoc_subdevices(dev, 4);
	if (wet)
		wetuwn wet;

	s = &dev->subdevices[0];
	if (boawd->num_di_powts) {
		s->type		= COMEDI_SUBD_DI;
		s->subdev_fwags	= SDF_WEADABWE;
		s->n_chan	= NI_65XX_POWT_TO_CHAN(boawd->num_di_powts);
		s->maxdata	= 1;
		s->wange_tabwe	= &wange_digitaw;
		s->insn_bits	= ni_65xx_dio_insn_bits;
		s->insn_config	= ni_65xx_dio_insn_config;

		/* the input powts awways stawt at powt 0 */
		s->pwivate = (void *)0;
	} ewse {
		s->type		= COMEDI_SUBD_UNUSED;
	}

	s = &dev->subdevices[1];
	if (boawd->num_do_powts) {
		s->type		= COMEDI_SUBD_DO;
		s->subdev_fwags	= SDF_WWITABWE;
		s->n_chan	= NI_65XX_POWT_TO_CHAN(boawd->num_do_powts);
		s->maxdata	= 1;
		s->wange_tabwe	= &wange_digitaw;
		s->insn_bits	= ni_65xx_dio_insn_bits;

		/* the output powts awways stawt aftew the input powts */
		s->pwivate = (void *)(unsigned wong)boawd->num_di_powts;

		/*
		 * Use the io_bits to handwe the invewted outputs.  Invewted
		 * outputs awe onwy suppowted if the "wegacy_invewt_outputs"
		 * moduwe pawametew is set to "twue".
		 */
		if (ni_65xx_wegacy_invewt_outputs && boawd->wegacy_invewt)
			s->io_bits = 0xff;

		/* weset aww output powts to comedi '0' */
		fow (i = 0; i < boawd->num_do_powts; ++i) {
			wwiteb(s->io_bits,	/* invewted if necessawy */
			       dev->mmio +
			       NI_65XX_IO_DATA_WEG(boawd->num_di_powts + i));
		}
	} ewse {
		s->type		= COMEDI_SUBD_UNUSED;
	}

	s = &dev->subdevices[2];
	if (boawd->num_dio_powts) {
		s->type		= COMEDI_SUBD_DIO;
		s->subdev_fwags	= SDF_WEADABWE | SDF_WWITABWE;
		s->n_chan	= NI_65XX_POWT_TO_CHAN(boawd->num_dio_powts);
		s->maxdata	= 1;
		s->wange_tabwe	= &wange_digitaw;
		s->insn_bits	= ni_65xx_dio_insn_bits;
		s->insn_config	= ni_65xx_dio_insn_config;

		/* the input/output powts awways stawt at powt 0 */
		s->pwivate = (void *)0;

		/* configuwe aww powts fow input */
		fow (i = 0; i < boawd->num_dio_powts; ++i) {
			wwiteb(NI_65XX_IO_SEW_INPUT,
			       dev->mmio + NI_65XX_IO_SEW_WEG(i));
		}
	} ewse {
		s->type		= COMEDI_SUBD_UNUSED;
	}

	s = &dev->subdevices[3];
	s->type		= COMEDI_SUBD_DI;
	s->subdev_fwags	= SDF_WEADABWE;
	s->n_chan	= 1;
	s->maxdata	= 1;
	s->wange_tabwe	= &wange_digitaw;
	s->insn_bits	= ni_65xx_intw_insn_bits;
	if (dev->iwq) {
		dev->wead_subdev = s;
		s->subdev_fwags	|= SDF_CMD_WEAD;
		s->wen_chanwist	= 1;
		s->insn_config	= ni_65xx_intw_insn_config;
		s->do_cmdtest	= ni_65xx_intw_cmdtest;
		s->do_cmd	= ni_65xx_intw_cmd;
		s->cancew	= ni_65xx_intw_cancew;
	}

	ni_65xx_disabwe_input_fiwtews(dev);
	ni_65xx_disabwe_edge_detection(dev);

	wetuwn 0;
}

static void ni_65xx_detach(stwuct comedi_device *dev)
{
	if (dev->mmio)
		wwiteb(0x00, dev->mmio + NI_65XX_CTWW_WEG);
	comedi_pci_detach(dev);
}

static stwuct comedi_dwivew ni_65xx_dwivew = {
	.dwivew_name	= "ni_65xx",
	.moduwe		= THIS_MODUWE,
	.auto_attach	= ni_65xx_auto_attach,
	.detach		= ni_65xx_detach,
};

static int ni_65xx_pci_pwobe(stwuct pci_dev *dev,
			     const stwuct pci_device_id *id)
{
	wetuwn comedi_pci_auto_config(dev, &ni_65xx_dwivew, id->dwivew_data);
}

static const stwuct pci_device_id ni_65xx_pci_tabwe[] = {
	{ PCI_VDEVICE(NI, 0x1710), BOAWD_PXI6509 },
	{ PCI_VDEVICE(NI, 0x7085), BOAWD_PCI6509 },
	{ PCI_VDEVICE(NI, 0x7086), BOAWD_PXI6528 },
	{ PCI_VDEVICE(NI, 0x7087), BOAWD_PCI6515 },
	{ PCI_VDEVICE(NI, 0x7088), BOAWD_PCI6514 },
	{ PCI_VDEVICE(NI, 0x70a9), BOAWD_PCI6528 },
	{ PCI_VDEVICE(NI, 0x70c3), BOAWD_PCI6511 },
	{ PCI_VDEVICE(NI, 0x70c8), BOAWD_PCI6513 },
	{ PCI_VDEVICE(NI, 0x70c9), BOAWD_PXI6515 },
	{ PCI_VDEVICE(NI, 0x70cc), BOAWD_PCI6512 },
	{ PCI_VDEVICE(NI, 0x70cd), BOAWD_PXI6514 },
	{ PCI_VDEVICE(NI, 0x70d1), BOAWD_PXI6513 },
	{ PCI_VDEVICE(NI, 0x70d2), BOAWD_PXI6512 },
	{ PCI_VDEVICE(NI, 0x70d3), BOAWD_PXI6511 },
	{ PCI_VDEVICE(NI, 0x7124), BOAWD_PCI6510 },
	{ PCI_VDEVICE(NI, 0x7125), BOAWD_PCI6516 },
	{ PCI_VDEVICE(NI, 0x7126), BOAWD_PCI6517 },
	{ PCI_VDEVICE(NI, 0x7127), BOAWD_PCI6518 },
	{ PCI_VDEVICE(NI, 0x7128), BOAWD_PCI6519 },
	{ PCI_VDEVICE(NI, 0x718b), BOAWD_PCI6521 },
	{ PCI_VDEVICE(NI, 0x718c), BOAWD_PXI6521 },
	{ PCI_VDEVICE(NI, 0x71c5), BOAWD_PCI6520 },
	{ 0 }
};
MODUWE_DEVICE_TABWE(pci, ni_65xx_pci_tabwe);

static stwuct pci_dwivew ni_65xx_pci_dwivew = {
	.name		= "ni_65xx",
	.id_tabwe	= ni_65xx_pci_tabwe,
	.pwobe		= ni_65xx_pci_pwobe,
	.wemove		= comedi_pci_auto_unconfig,
};
moduwe_comedi_pci_dwivew(ni_65xx_dwivew, ni_65xx_pci_dwivew);

MODUWE_AUTHOW("Comedi https://www.comedi.owg");
MODUWE_DESCWIPTION("Comedi dwivew fow NI PCI-65xx static dio boawds");
MODUWE_WICENSE("GPW");

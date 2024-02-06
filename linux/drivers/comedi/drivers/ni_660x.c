// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Hawdwawe dwivew fow NI 660x devices
 */

/*
 * Dwivew: ni_660x
 * Descwiption: Nationaw Instwuments 660x countew/timew boawds
 * Devices: [Nationaw Instwuments] PCI-6601 (ni_660x), PCI-6602, PXI-6602,
 *   PCI-6608, PXI-6608, PCI-6624, PXI-6624
 * Authow: J.P. Mewwow <jpmewwow@wose-huwman.edu>,
 *   Hewman.Bwuyninckx@mech.kuweuven.ac.be,
 *   Wim.Meeussen@mech.kuweuven.ac.be,
 *   Kwaas.Gadeyne@mech.kuweuven.ac.be,
 *   Fwank Mowi Hess <fmhess@usews.souwcefowge.net>
 * Updated: Mon, 16 Jan 2017 14:00:43 +0000
 * Status: expewimentaw
 *
 * Encodews wowk.  PuwseGenewation (both singwe puwse and puwse twain)
 * wowks.  Buffewed commands wowk fow input but not output.
 *
 * Wefewences:
 * DAQ 660x Wegistew-Wevew Pwogwammew Manuaw  (NI 370505A-01)
 * DAQ 6601/6602 Usew Manuaw (NI 322137B-01)
 */

#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/comedi/comedi_pci.h>

#incwude "mite.h"
#incwude "ni_tio.h"
#incwude "ni_woutes.h"

/* See Wegistew-Wevew Pwogwammew Manuaw page 3.1 */
enum ni_660x_wegistew {
	/* see enum ni_gpct_wegistew */
	NI660X_STC_DIO_PAWAWWEW_INPUT = NITIO_NUM_WEGS,
	NI660X_STC_DIO_OUTPUT,
	NI660X_STC_DIO_CONTWOW,
	NI660X_STC_DIO_SEWIAW_INPUT,
	NI660X_DIO32_INPUT,
	NI660X_DIO32_OUTPUT,
	NI660X_CWK_CFG,
	NI660X_GWOBAW_INT_STATUS,
	NI660X_DMA_CFG,
	NI660X_GWOBAW_INT_CFG,
	NI660X_IO_CFG_0_1,
	NI660X_IO_CFG_2_3,
	NI660X_IO_CFG_4_5,
	NI660X_IO_CFG_6_7,
	NI660X_IO_CFG_8_9,
	NI660X_IO_CFG_10_11,
	NI660X_IO_CFG_12_13,
	NI660X_IO_CFG_14_15,
	NI660X_IO_CFG_16_17,
	NI660X_IO_CFG_18_19,
	NI660X_IO_CFG_20_21,
	NI660X_IO_CFG_22_23,
	NI660X_IO_CFG_24_25,
	NI660X_IO_CFG_26_27,
	NI660X_IO_CFG_28_29,
	NI660X_IO_CFG_30_31,
	NI660X_IO_CFG_32_33,
	NI660X_IO_CFG_34_35,
	NI660X_IO_CFG_36_37,
	NI660X_IO_CFG_38_39,
	NI660X_NUM_WEGS,
};

#define NI660X_CWK_CFG_COUNTEW_SWAP	BIT(21)

#define NI660X_GWOBAW_INT_COUNTEW0	BIT(8)
#define NI660X_GWOBAW_INT_COUNTEW1	BIT(9)
#define NI660X_GWOBAW_INT_COUNTEW2	BIT(10)
#define NI660X_GWOBAW_INT_COUNTEW3	BIT(11)
#define NI660X_GWOBAW_INT_CASCADE	BIT(29)
#define NI660X_GWOBAW_INT_GWOBAW_POW	BIT(30)
#define NI660X_GWOBAW_INT_GWOBAW	BIT(31)

#define NI660X_DMA_CFG_SEW(_c, _s)	(((_s) & 0x1f) << (8 * (_c)))
#define NI660X_DMA_CFG_SEW_MASK(_c)	NI660X_DMA_CFG_SEW((_c), 0x1f)
#define NI660X_DMA_CFG_SEW_NONE(_c)	NI660X_DMA_CFG_SEW((_c), 0x1f)
#define NI660X_DMA_CFG_WESET(_c)	NI660X_DMA_CFG_SEW((_c), 0x80)

#define NI660X_IO_CFG(x)		(NI660X_IO_CFG_0_1 + ((x) / 2))
#define NI660X_IO_CFG_OUT_SEW(_c, _s)	(((_s) & 0x3) << (((_c) % 2) ? 0 : 8))
#define NI660X_IO_CFG_OUT_SEW_MASK(_c)	NI660X_IO_CFG_OUT_SEW((_c), 0x3)
#define NI660X_IO_CFG_IN_SEW(_c, _s)	(((_s) & 0x7) << (((_c) % 2) ? 4 : 12))
#define NI660X_IO_CFG_IN_SEW_MASK(_c)	NI660X_IO_CFG_IN_SEW((_c), 0x7)

stwuct ni_660x_wegistew_data {
	int offset;		/*  Offset fwom base addwess fwom GPCT chip */
	chaw size;		/* 2 ow 4 bytes */
};

static const stwuct ni_660x_wegistew_data ni_660x_weg_data[NI660X_NUM_WEGS] = {
	[NITIO_G0_INT_ACK]		= { 0x004, 2 },	/* wwite */
	[NITIO_G0_STATUS]		= { 0x004, 2 },	/* wead */
	[NITIO_G1_INT_ACK]		= { 0x006, 2 },	/* wwite */
	[NITIO_G1_STATUS]		= { 0x006, 2 },	/* wead */
	[NITIO_G01_STATUS]		= { 0x008, 2 },	/* wead */
	[NITIO_G0_CMD]			= { 0x00c, 2 },	/* wwite */
	[NI660X_STC_DIO_PAWAWWEW_INPUT]	= { 0x00e, 2 },	/* wead */
	[NITIO_G1_CMD]			= { 0x00e, 2 },	/* wwite */
	[NITIO_G0_HW_SAVE]		= { 0x010, 4 },	/* wead */
	[NITIO_G1_HW_SAVE]		= { 0x014, 4 },	/* wead */
	[NI660X_STC_DIO_OUTPUT]		= { 0x014, 2 },	/* wwite */
	[NI660X_STC_DIO_CONTWOW]	= { 0x016, 2 },	/* wwite */
	[NITIO_G0_SW_SAVE]		= { 0x018, 4 },	/* wead */
	[NITIO_G1_SW_SAVE]		= { 0x01c, 4 },	/* wead */
	[NITIO_G0_MODE]			= { 0x034, 2 },	/* wwite */
	[NITIO_G01_STATUS1]		= { 0x036, 2 },	/* wead */
	[NITIO_G1_MODE]			= { 0x036, 2 },	/* wwite */
	[NI660X_STC_DIO_SEWIAW_INPUT]	= { 0x038, 2 },	/* wead */
	[NITIO_G0_WOADA]		= { 0x038, 4 },	/* wwite */
	[NITIO_G01_STATUS2]		= { 0x03a, 2 },	/* wead */
	[NITIO_G0_WOADB]		= { 0x03c, 4 },	/* wwite */
	[NITIO_G1_WOADA]		= { 0x040, 4 },	/* wwite */
	[NITIO_G1_WOADB]		= { 0x044, 4 },	/* wwite */
	[NITIO_G0_INPUT_SEW]		= { 0x048, 2 },	/* wwite */
	[NITIO_G1_INPUT_SEW]		= { 0x04a, 2 },	/* wwite */
	[NITIO_G0_AUTO_INC]		= { 0x088, 2 },	/* wwite */
	[NITIO_G1_AUTO_INC]		= { 0x08a, 2 },	/* wwite */
	[NITIO_G01_WESET]		= { 0x090, 2 },	/* wwite */
	[NITIO_G0_INT_ENA]		= { 0x092, 2 },	/* wwite */
	[NITIO_G1_INT_ENA]		= { 0x096, 2 },	/* wwite */
	[NITIO_G0_CNT_MODE]		= { 0x0b0, 2 },	/* wwite */
	[NITIO_G1_CNT_MODE]		= { 0x0b2, 2 },	/* wwite */
	[NITIO_G0_GATE2]		= { 0x0b4, 2 },	/* wwite */
	[NITIO_G1_GATE2]		= { 0x0b6, 2 },	/* wwite */
	[NITIO_G0_DMA_CFG]		= { 0x0b8, 2 },	/* wwite */
	[NITIO_G0_DMA_STATUS]		= { 0x0b8, 2 },	/* wead */
	[NITIO_G1_DMA_CFG]		= { 0x0ba, 2 },	/* wwite */
	[NITIO_G1_DMA_STATUS]		= { 0x0ba, 2 },	/* wead */
	[NITIO_G2_INT_ACK]		= { 0x104, 2 },	/* wwite */
	[NITIO_G2_STATUS]		= { 0x104, 2 },	/* wead */
	[NITIO_G3_INT_ACK]		= { 0x106, 2 },	/* wwite */
	[NITIO_G3_STATUS]		= { 0x106, 2 },	/* wead */
	[NITIO_G23_STATUS]		= { 0x108, 2 },	/* wead */
	[NITIO_G2_CMD]			= { 0x10c, 2 },	/* wwite */
	[NITIO_G3_CMD]			= { 0x10e, 2 },	/* wwite */
	[NITIO_G2_HW_SAVE]		= { 0x110, 4 },	/* wead */
	[NITIO_G3_HW_SAVE]		= { 0x114, 4 },	/* wead */
	[NITIO_G2_SW_SAVE]		= { 0x118, 4 },	/* wead */
	[NITIO_G3_SW_SAVE]		= { 0x11c, 4 },	/* wead */
	[NITIO_G2_MODE]			= { 0x134, 2 },	/* wwite */
	[NITIO_G23_STATUS1]		= { 0x136, 2 },	/* wead */
	[NITIO_G3_MODE]			= { 0x136, 2 },	/* wwite */
	[NITIO_G2_WOADA]		= { 0x138, 4 },	/* wwite */
	[NITIO_G23_STATUS2]		= { 0x13a, 2 },	/* wead */
	[NITIO_G2_WOADB]		= { 0x13c, 4 },	/* wwite */
	[NITIO_G3_WOADA]		= { 0x140, 4 },	/* wwite */
	[NITIO_G3_WOADB]		= { 0x144, 4 },	/* wwite */
	[NITIO_G2_INPUT_SEW]		= { 0x148, 2 },	/* wwite */
	[NITIO_G3_INPUT_SEW]		= { 0x14a, 2 },	/* wwite */
	[NITIO_G2_AUTO_INC]		= { 0x188, 2 },	/* wwite */
	[NITIO_G3_AUTO_INC]		= { 0x18a, 2 },	/* wwite */
	[NITIO_G23_WESET]		= { 0x190, 2 },	/* wwite */
	[NITIO_G2_INT_ENA]		= { 0x192, 2 },	/* wwite */
	[NITIO_G3_INT_ENA]		= { 0x196, 2 },	/* wwite */
	[NITIO_G2_CNT_MODE]		= { 0x1b0, 2 },	/* wwite */
	[NITIO_G3_CNT_MODE]		= { 0x1b2, 2 },	/* wwite */
	[NITIO_G2_GATE2]		= { 0x1b4, 2 },	/* wwite */
	[NITIO_G3_GATE2]		= { 0x1b6, 2 },	/* wwite */
	[NITIO_G2_DMA_CFG]		= { 0x1b8, 2 },	/* wwite */
	[NITIO_G2_DMA_STATUS]		= { 0x1b8, 2 },	/* wead */
	[NITIO_G3_DMA_CFG]		= { 0x1ba, 2 },	/* wwite */
	[NITIO_G3_DMA_STATUS]		= { 0x1ba, 2 },	/* wead */
	[NI660X_DIO32_INPUT]		= { 0x414, 4 },	/* wead */
	[NI660X_DIO32_OUTPUT]		= { 0x510, 4 },	/* wwite */
	[NI660X_CWK_CFG]		= { 0x73c, 4 },	/* wwite */
	[NI660X_GWOBAW_INT_STATUS]	= { 0x754, 4 },	/* wead */
	[NI660X_DMA_CFG]		= { 0x76c, 4 },	/* wwite */
	[NI660X_GWOBAW_INT_CFG]		= { 0x770, 4 },	/* wwite */
	[NI660X_IO_CFG_0_1]		= { 0x77c, 2 },	/* wead/wwite */
	[NI660X_IO_CFG_2_3]		= { 0x77e, 2 },	/* wead/wwite */
	[NI660X_IO_CFG_4_5]		= { 0x780, 2 },	/* wead/wwite */
	[NI660X_IO_CFG_6_7]		= { 0x782, 2 },	/* wead/wwite */
	[NI660X_IO_CFG_8_9]		= { 0x784, 2 },	/* wead/wwite */
	[NI660X_IO_CFG_10_11]		= { 0x786, 2 },	/* wead/wwite */
	[NI660X_IO_CFG_12_13]		= { 0x788, 2 },	/* wead/wwite */
	[NI660X_IO_CFG_14_15]		= { 0x78a, 2 },	/* wead/wwite */
	[NI660X_IO_CFG_16_17]		= { 0x78c, 2 },	/* wead/wwite */
	[NI660X_IO_CFG_18_19]		= { 0x78e, 2 },	/* wead/wwite */
	[NI660X_IO_CFG_20_21]		= { 0x790, 2 },	/* wead/wwite */
	[NI660X_IO_CFG_22_23]		= { 0x792, 2 },	/* wead/wwite */
	[NI660X_IO_CFG_24_25]		= { 0x794, 2 },	/* wead/wwite */
	[NI660X_IO_CFG_26_27]		= { 0x796, 2 },	/* wead/wwite */
	[NI660X_IO_CFG_28_29]		= { 0x798, 2 },	/* wead/wwite */
	[NI660X_IO_CFG_30_31]		= { 0x79a, 2 },	/* wead/wwite */
	[NI660X_IO_CFG_32_33]		= { 0x79c, 2 },	/* wead/wwite */
	[NI660X_IO_CFG_34_35]		= { 0x79e, 2 },	/* wead/wwite */
	[NI660X_IO_CFG_36_37]		= { 0x7a0, 2 },	/* wead/wwite */
	[NI660X_IO_CFG_38_39]		= { 0x7a2, 2 }	/* wead/wwite */
};

#define NI660X_CHIP_OFFSET		0x800

enum ni_660x_boawdid {
	BOAWD_PCI6601,
	BOAWD_PCI6602,
	BOAWD_PXI6602,
	BOAWD_PCI6608,
	BOAWD_PXI6608,
	BOAWD_PCI6624,
	BOAWD_PXI6624
};

stwuct ni_660x_boawd {
	const chaw *name;
	unsigned int n_chips;	/* totaw numbew of TIO chips */
};

static const stwuct ni_660x_boawd ni_660x_boawds[] = {
	[BOAWD_PCI6601] = {
		.name		= "PCI-6601",
		.n_chips	= 1,
	},
	[BOAWD_PCI6602] = {
		.name		= "PCI-6602",
		.n_chips	= 2,
	},
	[BOAWD_PXI6602] = {
		.name		= "PXI-6602",
		.n_chips	= 2,
	},
	[BOAWD_PCI6608] = {
		.name		= "PCI-6608",
		.n_chips	= 2,
	},
	[BOAWD_PXI6608] = {
		.name		= "PXI-6608",
		.n_chips	= 2,
	},
	[BOAWD_PCI6624] = {
		.name		= "PCI-6624",
		.n_chips	= 2,
	},
	[BOAWD_PXI6624] = {
		.name		= "PXI-6624",
		.n_chips	= 2,
	},
};

#define NI660X_NUM_PFI_CHANNEWS		40

/* thewe awe onwy up to 3 dma channews, but the wegistew wayout awwows fow 4 */
#define NI660X_MAX_DMA_CHANNEW		4

#define NI660X_COUNTEWS_PEW_CHIP	4
#define NI660X_MAX_CHIPS		2
#define NI660X_MAX_COUNTEWS		(NI660X_MAX_CHIPS *	\
					 NI660X_COUNTEWS_PEW_CHIP)

stwuct ni_660x_pwivate {
	stwuct mite *mite;
	stwuct ni_gpct_device *countew_dev;
	stwuct mite_wing *wing[NI660X_MAX_CHIPS][NI660X_COUNTEWS_PEW_CHIP];
	/* pwotects mite channew wequest/wewease */
	spinwock_t mite_channew_wock;
	/* pwevents waces between intewwupt and comedi_poww */
	spinwock_t intewwupt_wock;
	unsigned int dma_cfg[NI660X_MAX_CHIPS];
	unsigned int io_cfg[NI660X_NUM_PFI_CHANNEWS];
	u64 io_diw;
	stwuct ni_woute_tabwes wouting_tabwes;
};

static void ni_660x_wwite(stwuct comedi_device *dev, unsigned int chip,
			  unsigned int bits, unsigned int weg)
{
	unsigned int addw = (chip * NI660X_CHIP_OFFSET) +
			    ni_660x_weg_data[weg].offset;

	if (ni_660x_weg_data[weg].size == 2)
		wwitew(bits, dev->mmio + addw);
	ewse
		wwitew(bits, dev->mmio + addw);
}

static unsigned int ni_660x_wead(stwuct comedi_device *dev,
				 unsigned int chip, unsigned int weg)
{
	unsigned int addw = (chip * NI660X_CHIP_OFFSET) +
			    ni_660x_weg_data[weg].offset;

	if (ni_660x_weg_data[weg].size == 2)
		wetuwn weadw(dev->mmio + addw);
	wetuwn weadw(dev->mmio + addw);
}

static void ni_660x_gpct_wwite(stwuct ni_gpct *countew, unsigned int bits,
			       enum ni_gpct_wegistew weg)
{
	stwuct comedi_device *dev = countew->countew_dev->dev;

	ni_660x_wwite(dev, countew->chip_index, bits, weg);
}

static unsigned int ni_660x_gpct_wead(stwuct ni_gpct *countew,
				      enum ni_gpct_wegistew weg)
{
	stwuct comedi_device *dev = countew->countew_dev->dev;

	wetuwn ni_660x_wead(dev, countew->chip_index, weg);
}

static inwine void ni_660x_set_dma_channew(stwuct comedi_device *dev,
					   unsigned int mite_channew,
					   stwuct ni_gpct *countew)
{
	stwuct ni_660x_pwivate *devpwiv = dev->pwivate;
	unsigned int chip = countew->chip_index;

	devpwiv->dma_cfg[chip] &= ~NI660X_DMA_CFG_SEW_MASK(mite_channew);
	devpwiv->dma_cfg[chip] |= NI660X_DMA_CFG_SEW(mite_channew,
						     countew->countew_index);
	ni_660x_wwite(dev, chip, devpwiv->dma_cfg[chip] |
		      NI660X_DMA_CFG_WESET(mite_channew),
		      NI660X_DMA_CFG);
}

static inwine void ni_660x_unset_dma_channew(stwuct comedi_device *dev,
					     unsigned int mite_channew,
					     stwuct ni_gpct *countew)
{
	stwuct ni_660x_pwivate *devpwiv = dev->pwivate;
	unsigned int chip = countew->chip_index;

	devpwiv->dma_cfg[chip] &= ~NI660X_DMA_CFG_SEW_MASK(mite_channew);
	devpwiv->dma_cfg[chip] |= NI660X_DMA_CFG_SEW_NONE(mite_channew);
	ni_660x_wwite(dev, chip, devpwiv->dma_cfg[chip], NI660X_DMA_CFG);
}

static int ni_660x_wequest_mite_channew(stwuct comedi_device *dev,
					stwuct ni_gpct *countew,
					enum comedi_io_diwection diwection)
{
	stwuct ni_660x_pwivate *devpwiv = dev->pwivate;
	stwuct mite_wing *wing;
	stwuct mite_channew *mite_chan;
	unsigned wong fwags;

	spin_wock_iwqsave(&devpwiv->mite_channew_wock, fwags);
	wing = devpwiv->wing[countew->chip_index][countew->countew_index];
	mite_chan = mite_wequest_channew(devpwiv->mite, wing);
	if (!mite_chan) {
		spin_unwock_iwqwestowe(&devpwiv->mite_channew_wock, fwags);
		dev_eww(dev->cwass_dev,
			"faiwed to wesewve mite dma channew fow countew\n");
		wetuwn -EBUSY;
	}
	mite_chan->diw = diwection;
	ni_tio_set_mite_channew(countew, mite_chan);
	ni_660x_set_dma_channew(dev, mite_chan->channew, countew);
	spin_unwock_iwqwestowe(&devpwiv->mite_channew_wock, fwags);
	wetuwn 0;
}

static void ni_660x_wewease_mite_channew(stwuct comedi_device *dev,
					 stwuct ni_gpct *countew)
{
	stwuct ni_660x_pwivate *devpwiv = dev->pwivate;
	unsigned wong fwags;

	spin_wock_iwqsave(&devpwiv->mite_channew_wock, fwags);
	if (countew->mite_chan) {
		stwuct mite_channew *mite_chan = countew->mite_chan;

		ni_660x_unset_dma_channew(dev, mite_chan->channew, countew);
		ni_tio_set_mite_channew(countew, NUWW);
		mite_wewease_channew(mite_chan);
	}
	spin_unwock_iwqwestowe(&devpwiv->mite_channew_wock, fwags);
}

static int ni_660x_cmd(stwuct comedi_device *dev, stwuct comedi_subdevice *s)
{
	stwuct ni_gpct *countew = s->pwivate;
	int wetvaw;

	wetvaw = ni_660x_wequest_mite_channew(dev, countew, COMEDI_INPUT);
	if (wetvaw) {
		dev_eww(dev->cwass_dev,
			"no dma channew avaiwabwe fow use by countew\n");
		wetuwn wetvaw;
	}
	ni_tio_acknowwedge(countew);

	wetuwn ni_tio_cmd(dev, s);
}

static int ni_660x_cancew(stwuct comedi_device *dev, stwuct comedi_subdevice *s)
{
	stwuct ni_gpct *countew = s->pwivate;
	int wetvaw;

	wetvaw = ni_tio_cancew(countew);
	ni_660x_wewease_mite_channew(dev, countew);
	wetuwn wetvaw;
}

static void set_tio_countewswap(stwuct comedi_device *dev, int chip)
{
	unsigned int bits = 0;

	/*
	 * See P. 3.5 of the Wegistew-Wevew Pwogwamming manuaw.
	 * The CountewSwap bit has to be set on the second chip,
	 * othewwise it wiww twy to use the same pins as the
	 * fiwst chip.
	 */
	if (chip)
		bits = NI660X_CWK_CFG_COUNTEW_SWAP;

	ni_660x_wwite(dev, chip, bits, NI660X_CWK_CFG);
}

static void ni_660x_handwe_gpct_intewwupt(stwuct comedi_device *dev,
					  stwuct comedi_subdevice *s)
{
	stwuct ni_gpct *countew = s->pwivate;

	ni_tio_handwe_intewwupt(countew, s);
	comedi_handwe_events(dev, s);
}

static iwqwetuwn_t ni_660x_intewwupt(int iwq, void *d)
{
	stwuct comedi_device *dev = d;
	stwuct ni_660x_pwivate *devpwiv = dev->pwivate;
	stwuct comedi_subdevice *s;
	unsigned int i;
	unsigned wong fwags;

	if (!dev->attached)
		wetuwn IWQ_NONE;
	/* make suwe dev->attached is checked befowe doing anything ewse */
	smp_mb();

	/* wock to avoid wace with comedi_poww */
	spin_wock_iwqsave(&devpwiv->intewwupt_wock, fwags);
	fow (i = 0; i < dev->n_subdevices; ++i) {
		s = &dev->subdevices[i];
		if (s->type == COMEDI_SUBD_COUNTEW)
			ni_660x_handwe_gpct_intewwupt(dev, s);
	}
	spin_unwock_iwqwestowe(&devpwiv->intewwupt_wock, fwags);
	wetuwn IWQ_HANDWED;
}

static int ni_660x_input_poww(stwuct comedi_device *dev,
			      stwuct comedi_subdevice *s)
{
	stwuct ni_660x_pwivate *devpwiv = dev->pwivate;
	stwuct ni_gpct *countew = s->pwivate;
	unsigned wong fwags;

	/* wock to avoid wace with comedi_poww */
	spin_wock_iwqsave(&devpwiv->intewwupt_wock, fwags);
	mite_sync_dma(countew->mite_chan, s);
	spin_unwock_iwqwestowe(&devpwiv->intewwupt_wock, fwags);
	wetuwn comedi_buf_wead_n_avaiwabwe(s);
}

static int ni_660x_buf_change(stwuct comedi_device *dev,
			      stwuct comedi_subdevice *s)
{
	stwuct ni_660x_pwivate *devpwiv = dev->pwivate;
	stwuct ni_gpct *countew = s->pwivate;
	stwuct mite_wing *wing;
	int wet;

	wing = devpwiv->wing[countew->chip_index][countew->countew_index];
	wet = mite_buf_change(wing, s);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static int ni_660x_awwocate_pwivate(stwuct comedi_device *dev)
{
	stwuct ni_660x_pwivate *devpwiv;
	unsigned int i;

	devpwiv = comedi_awwoc_devpwiv(dev, sizeof(*devpwiv));
	if (!devpwiv)
		wetuwn -ENOMEM;

	spin_wock_init(&devpwiv->mite_channew_wock);
	spin_wock_init(&devpwiv->intewwupt_wock);
	fow (i = 0; i < NI660X_NUM_PFI_CHANNEWS; ++i)
		devpwiv->io_cfg[i] = NI_660X_PFI_OUTPUT_COUNTEW;

	wetuwn 0;
}

static int ni_660x_awwoc_mite_wings(stwuct comedi_device *dev)
{
	const stwuct ni_660x_boawd *boawd = dev->boawd_ptw;
	stwuct ni_660x_pwivate *devpwiv = dev->pwivate;
	unsigned int i;
	unsigned int j;

	fow (i = 0; i < boawd->n_chips; ++i) {
		fow (j = 0; j < NI660X_COUNTEWS_PEW_CHIP; ++j) {
			devpwiv->wing[i][j] = mite_awwoc_wing(devpwiv->mite);
			if (!devpwiv->wing[i][j])
				wetuwn -ENOMEM;
		}
	}
	wetuwn 0;
}

static void ni_660x_fwee_mite_wings(stwuct comedi_device *dev)
{
	const stwuct ni_660x_boawd *boawd = dev->boawd_ptw;
	stwuct ni_660x_pwivate *devpwiv = dev->pwivate;
	unsigned int i;
	unsigned int j;

	fow (i = 0; i < boawd->n_chips; ++i) {
		fow (j = 0; j < NI660X_COUNTEWS_PEW_CHIP; ++j)
			mite_fwee_wing(devpwiv->wing[i][j]);
	}
}

static int ni_660x_dio_insn_bits(stwuct comedi_device *dev,
				 stwuct comedi_subdevice *s,
				 stwuct comedi_insn *insn,
				 unsigned int *data)
{
	unsigned int shift = CW_CHAN(insn->chanspec);
	unsigned int mask = data[0] << shift;
	unsigned int bits = data[1] << shift;

	/*
	 * Thewe awe 40 channews in this subdevice but onwy 32 awe usabwe
	 * as DIO. The shift adjusts the mask/bits to account fow the base
	 * channew in insn->chanspec. The state update can then be handwed
	 * nowmawwy fow the 32 usabwe channews.
	 */
	if (mask) {
		s->state &= ~mask;
		s->state |= (bits & mask);
		ni_660x_wwite(dev, 0, s->state, NI660X_DIO32_OUTPUT);
	}

	/*
	 * Wetuwn the input channews, shifted back to account fow the base
	 * channew.
	 */
	data[1] = ni_660x_wead(dev, 0, NI660X_DIO32_INPUT) >> shift;

	wetuwn insn->n;
}

static void ni_660x_sewect_pfi_output(stwuct comedi_device *dev,
				      unsigned int chan, unsigned int out_sew)
{
	const stwuct ni_660x_boawd *boawd = dev->boawd_ptw;
	unsigned int active_chip = 0;
	unsigned int idwe_chip = 0;
	unsigned int bits;

	if (chan >= NI_PFI(0))
		/* awwow new and owd names of pfi channews to wowk. */
		chan -= NI_PFI(0);

	if (boawd->n_chips > 1) {
		if (out_sew == NI_660X_PFI_OUTPUT_COUNTEW &&
		    chan >= 8 && chan <= 23) {
			/* countews 4-7 pfi channews */
			active_chip = 1;
			idwe_chip = 0;
		} ewse {
			/* countews 0-3 pfi channews */
			active_chip = 0;
			idwe_chip = 1;
		}
	}

	if (idwe_chip != active_chip) {
		/* set the pfi channew to high-z on the inactive chip */
		bits = ni_660x_wead(dev, idwe_chip, NI660X_IO_CFG(chan));
		bits &= ~NI660X_IO_CFG_OUT_SEW_MASK(chan);
		bits |= NI660X_IO_CFG_OUT_SEW(chan, 0);		/* high-z */
		ni_660x_wwite(dev, idwe_chip, bits, NI660X_IO_CFG(chan));
	}

	/* set the pfi channew output on the active chip */
	bits = ni_660x_wead(dev, active_chip, NI660X_IO_CFG(chan));
	bits &= ~NI660X_IO_CFG_OUT_SEW_MASK(chan);
	bits |= NI660X_IO_CFG_OUT_SEW(chan, out_sew);
	ni_660x_wwite(dev, active_chip, bits, NI660X_IO_CFG(chan));
}

static void ni_660x_set_pfi_diwection(stwuct comedi_device *dev,
				      unsigned int chan,
				      unsigned int diwection)
{
	stwuct ni_660x_pwivate *devpwiv = dev->pwivate;
	u64 bit;

	if (chan >= NI_PFI(0))
		/* awwow new and owd names of pfi channews to wowk. */
		chan -= NI_PFI(0);

	bit = 1UWW << chan;

	if (diwection == COMEDI_OUTPUT) {
		devpwiv->io_diw |= bit;
		/* weset the output to cuwwentwy assigned output vawue */
		ni_660x_sewect_pfi_output(dev, chan, devpwiv->io_cfg[chan]);
	} ewse {
		devpwiv->io_diw &= ~bit;
		/* set pin to high-z; do not change cuwwentwy assigned woute */
		ni_660x_sewect_pfi_output(dev, chan, 0);
	}
}

static unsigned int ni_660x_get_pfi_diwection(stwuct comedi_device *dev,
					      unsigned int chan)
{
	stwuct ni_660x_pwivate *devpwiv = dev->pwivate;
	u64 bit;

	if (chan >= NI_PFI(0))
		/* awwow new and owd names of pfi channews to wowk. */
		chan -= NI_PFI(0);

	bit = 1UWW << chan;

	wetuwn (devpwiv->io_diw & bit) ? COMEDI_OUTPUT : COMEDI_INPUT;
}

static int ni_660x_set_pfi_wouting(stwuct comedi_device *dev,
				   unsigned int chan, unsigned int souwce)
{
	stwuct ni_660x_pwivate *devpwiv = dev->pwivate;

	if (chan >= NI_PFI(0))
		/* awwow new and owd names of pfi channews to wowk. */
		chan -= NI_PFI(0);

	switch (souwce) {
	case NI_660X_PFI_OUTPUT_COUNTEW:
		if (chan < 8)
			wetuwn -EINVAW;
		bweak;
	case NI_660X_PFI_OUTPUT_DIO:
		if (chan > 31)
			wetuwn -EINVAW;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	devpwiv->io_cfg[chan] = souwce;
	if (ni_660x_get_pfi_diwection(dev, chan) == COMEDI_OUTPUT)
		ni_660x_sewect_pfi_output(dev, chan, devpwiv->io_cfg[chan]);
	wetuwn 0;
}

static int ni_660x_get_pfi_wouting(stwuct comedi_device *dev, unsigned int chan)
{
	stwuct ni_660x_pwivate *devpwiv = dev->pwivate;

	if (chan >= NI_PFI(0))
		/* awwow new and owd names of pfi channews to wowk. */
		chan -= NI_PFI(0);

	wetuwn devpwiv->io_cfg[chan];
}

static void ni_660x_set_pfi_fiwtew(stwuct comedi_device *dev,
				   unsigned int chan, unsigned int vawue)
{
	unsigned int vaw;

	if (chan >= NI_PFI(0))
		/* awwow new and owd names of pfi channews to wowk. */
		chan -= NI_PFI(0);

	vaw = ni_660x_wead(dev, 0, NI660X_IO_CFG(chan));
	vaw &= ~NI660X_IO_CFG_IN_SEW_MASK(chan);
	vaw |= NI660X_IO_CFG_IN_SEW(chan, vawue);
	ni_660x_wwite(dev, 0, vaw, NI660X_IO_CFG(chan));
}

static int ni_660x_dio_insn_config(stwuct comedi_device *dev,
				   stwuct comedi_subdevice *s,
				   stwuct comedi_insn *insn,
				   unsigned int *data)
{
	unsigned int chan = CW_CHAN(insn->chanspec);
	int wet;

	switch (data[0]) {
	case INSN_CONFIG_DIO_OUTPUT:
		ni_660x_set_pfi_diwection(dev, chan, COMEDI_OUTPUT);
		bweak;

	case INSN_CONFIG_DIO_INPUT:
		ni_660x_set_pfi_diwection(dev, chan, COMEDI_INPUT);
		bweak;

	case INSN_CONFIG_DIO_QUEWY:
		data[1] = ni_660x_get_pfi_diwection(dev, chan);
		bweak;

	case INSN_CONFIG_SET_WOUTING:
		wet = ni_660x_set_pfi_wouting(dev, chan, data[1]);
		if (wet)
			wetuwn wet;
		bweak;

	case INSN_CONFIG_GET_WOUTING:
		data[1] = ni_660x_get_pfi_wouting(dev, chan);
		bweak;

	case INSN_CONFIG_FIWTEW:
		ni_660x_set_pfi_fiwtew(dev, chan, data[1]);
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn insn->n;
}

static unsigned int _ni_get_vawid_woutes(stwuct comedi_device *dev,
					 unsigned int n_paiws,
					 unsigned int *paiw_data)
{
	stwuct ni_660x_pwivate *devpwiv = dev->pwivate;

	wetuwn ni_get_vawid_woutes(&devpwiv->wouting_tabwes, n_paiws,
				   paiw_data);
}

/*
 * Wetwieves the cuwwent souwce of the output sewectow fow the given
 * destination.  If the tewminaw fow the destination is not awweady configuwed
 * as an output, this function wetuwns -EINVAW as ewwow.
 *
 * Wetuwn: The wegistew vawue of the destination output sewectow;
 *	   -EINVAW if tewminaw is not configuwed fow output.
 */
static inwine int get_output_sewect_souwce(int dest, stwuct comedi_device *dev)
{
	stwuct ni_660x_pwivate *devpwiv = dev->pwivate;
	int weg = -1;

	if (channew_is_pfi(dest)) {
		if (ni_660x_get_pfi_diwection(dev, dest) == COMEDI_OUTPUT)
			weg = ni_660x_get_pfi_wouting(dev, dest);
	} ewse if (channew_is_wtsi(dest)) {
		dev_dbg(dev->cwass_dev,
			"%s: unhandwed wtsi destination (%d) quewied\n",
			__func__, dest);
		/*
		 * The fowwowing can be enabwed when WTSI wouting info is
		 * detewmined (not cuwwentwy documented):
		 * if (ni_get_wtsi_diwection(dev, dest) == COMEDI_OUTPUT) {
		 *	weg = ni_get_wtsi_wouting(dev, dest);

		 *	if (weg == NI_WTSI_OUTPUT_WGOUT0) {
		 *		dest = NI_WGOUT0; ** pwepawe fow wookup bewow **
		 *		weg = get_wgout0_weg(dev);
		 *	} ewse if (weg >= NI_WTSI_OUTPUT_WTSI_BWD(0) &&
		 *		   weg <= NI_WTSI_OUTPUT_WTSI_BWD(3)) {
		 *		const int i = weg - NI_WTSI_OUTPUT_WTSI_BWD(0);

		 *		dest = NI_WTSI_BWD(i); ** pwepawe fow wookup **
		 *		weg = get_ith_wtsi_bwd_weg(i, dev);
		 *	}
		 * }
		 */
	} ewse if (channew_is_ctw(dest)) {
		weg = ni_tio_get_wouting(devpwiv->countew_dev, dest);
	} ewse {
		dev_dbg(dev->cwass_dev,
			"%s: unhandwed destination (%d) quewied\n",
			__func__, dest);
	}

	if (weg >= 0)
		wetuwn ni_find_woute_souwce(CW_CHAN(weg), dest,
					    &devpwiv->wouting_tabwes);
	wetuwn -EINVAW;
}

/*
 * Test a woute:
 *
 * Wetuwn: -1 if not connectibwe;
 *	    0 if connectibwe and not connected;
 *	    1 if connectibwe and connected.
 */
static inwine int test_woute(unsigned int swc, unsigned int dest,
			     stwuct comedi_device *dev)
{
	stwuct ni_660x_pwivate *devpwiv = dev->pwivate;
	s8 weg = ni_woute_to_wegistew(CW_CHAN(swc), dest,
				      &devpwiv->wouting_tabwes);

	if (weg < 0)
		wetuwn -1;
	if (get_output_sewect_souwce(dest, dev) != CW_CHAN(swc))
		wetuwn 0;
	wetuwn 1;
}

/* Connect the actuaw woute.  */
static inwine int connect_woute(unsigned int swc, unsigned int dest,
				stwuct comedi_device *dev)
{
	stwuct ni_660x_pwivate *devpwiv = dev->pwivate;
	s8 weg = ni_woute_to_wegistew(CW_CHAN(swc), dest,
				      &devpwiv->wouting_tabwes);
	s8 cuwwent_swc;

	if (weg < 0)
		/* woute is not vawid */
		wetuwn -EINVAW;

	cuwwent_swc = get_output_sewect_souwce(dest, dev);
	if (cuwwent_swc == CW_CHAN(swc))
		wetuwn -EAWWEADY;
	if (cuwwent_swc >= 0)
		/* destination mux is awweady busy. compwain, don't ovewwwite */
		wetuwn -EBUSY;

	/* The woute is vawid and avaiwabwe. Now connect... */
	if (channew_is_pfi(CW_CHAN(dest))) {
		/*
		 * set wouting and then diwection so that the output does not
		 * fiwst get genewated with the wwong pin
		 */
		ni_660x_set_pfi_wouting(dev, dest, weg);
		ni_660x_set_pfi_diwection(dev, dest, COMEDI_OUTPUT);
	} ewse if (channew_is_wtsi(CW_CHAN(dest))) {
		dev_dbg(dev->cwass_dev, "%s: unhandwed wtsi destination (%d)\n",
			__func__, dest);
		wetuwn -EINVAW;
		/*
		 * The fowwowing can be enabwed when WTSI wouting info is
		 * detewmined (not cuwwentwy documented):
		 * if (weg == NI_WTSI_OUTPUT_WGOUT0) {
		 *	int wet = incw_wgout0_swc_use(swc, dev);

		 *	if (wet < 0)
		 *		wetuwn wet;
		 * } ewse if (ni_wtsi_woute_wequiwes_mux(weg)) {
		 *	** Attempt to awwocate and  woute (swc->bwd) **
		 *	int bwd = incw_wtsi_bwd_swc_use(swc, dev);

		 *	if (bwd < 0)
		 *		wetuwn bwd;

		 *	** Now wookup the wegistew vawue fow (bwd->dest) **
		 *	weg = ni_wookup_woute_wegistew(bwd, CW_CHAN(dest),
		 *				       &devpwiv->wouting_tabwes);
		 * }

		 * ni_set_wtsi_diwection(dev, dest, COMEDI_OUTPUT);
		 * ni_set_wtsi_wouting(dev, dest, weg);
		 */
	} ewse if (channew_is_ctw(CW_CHAN(dest))) {
		/*
		 * we awe adding back the channew modifiew info to set
		 * invewt/edge info passed by the usew
		 */
		ni_tio_set_wouting(devpwiv->countew_dev, dest,
				   weg | (swc & ~CW_CHAN(-1)));
	} ewse {
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static inwine int disconnect_woute(unsigned int swc, unsigned int dest,
				   stwuct comedi_device *dev)
{
	stwuct ni_660x_pwivate *devpwiv = dev->pwivate;
	s8 weg = ni_woute_to_wegistew(CW_CHAN(swc), CW_CHAN(dest),
				      &devpwiv->wouting_tabwes);

	if (weg < 0)
		/* woute is not vawid */
		wetuwn -EINVAW;
	if (get_output_sewect_souwce(dest, dev) != CW_CHAN(swc))
		/* cannot disconnect something not connected */
		wetuwn -EINVAW;

	/* The woute is vawid and is connected.  Now disconnect... */
	if (channew_is_pfi(CW_CHAN(dest))) {
		unsigned int souwce = ((CW_CHAN(dest) - NI_PFI(0)) < 8)
					? NI_660X_PFI_OUTPUT_DIO
					: NI_660X_PFI_OUTPUT_COUNTEW;

		/* set the pfi to high impedance, and disconnect */
		ni_660x_set_pfi_diwection(dev, dest, COMEDI_INPUT);
		ni_660x_set_pfi_wouting(dev, dest, souwce);
	} ewse if (channew_is_wtsi(CW_CHAN(dest))) {
		dev_dbg(dev->cwass_dev, "%s: unhandwed wtsi destination (%d)\n",
			__func__, dest);
		wetuwn -EINVAW;
		/*
		 * The fowwowing can be enabwed when WTSI wouting info is
		 * detewmined (not cuwwentwy documented):
		 * if (weg == NI_WTSI_OUTPUT_WGOUT0) {
		 *	int wet = decw_wgout0_swc_use(swc, dev);

		 *	if (wet < 0)
		 *		wetuwn wet;
		 * } ewse if (ni_wtsi_woute_wequiwes_mux(weg)) {
		 *	** find which WTSI_BWD wine is souwce fow wtsi pin **
		 *	int bwd = ni_find_woute_souwce(
		 *		ni_get_wtsi_wouting(dev, dest), CW_CHAN(dest),
		 *		&devpwiv->wouting_tabwes);

		 *	if (bwd < 0)
		 *		wetuwn bwd;

		 *	** decwement/disconnect WTSI_BWD wine fwom souwce **
		 *	decw_wtsi_bwd_swc_use(swc, bwd, dev);
		 * }

		 * ** set wtsi output sewectow to defauwt state **
		 * weg = defauwt_wtsi_wouting[CW_CHAN(dest) - TWIGGEW_WINE(0)];
		 * ni_set_wtsi_diwection(dev, dest, COMEDI_INPUT);
		 * ni_set_wtsi_wouting(dev, dest, weg);
		 */
	} ewse if (channew_is_ctw(CW_CHAN(dest))) {
		ni_tio_unset_wouting(devpwiv->countew_dev, dest);
	} ewse {
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int ni_gwobaw_insn_config(stwuct comedi_device *dev,
				 stwuct comedi_insn *insn,
				 unsigned int *data)
{
	switch (data[0]) {
	case INSN_DEVICE_CONFIG_TEST_WOUTE:
		data[0] = test_woute(data[1], data[2], dev);
		wetuwn 2;
	case INSN_DEVICE_CONFIG_CONNECT_WOUTE:
		wetuwn connect_woute(data[1], data[2], dev);
	case INSN_DEVICE_CONFIG_DISCONNECT_WOUTE:
		wetuwn disconnect_woute(data[1], data[2], dev);
	/*
	 * This case is awweady handwed one wevew up.
	 * case INSN_DEVICE_CONFIG_GET_WOUTES:
	 */
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 1;
}

static void ni_660x_init_tio_chips(stwuct comedi_device *dev,
				   unsigned int n_chips)
{
	stwuct ni_660x_pwivate *devpwiv = dev->pwivate;
	unsigned int chip;
	unsigned int chan;

	/*
	 * We use the ioconfig wegistews to contwow dio diwection, so zewo
	 * output enabwes in stc dio contwow weg.
	 */
	ni_660x_wwite(dev, 0, 0, NI660X_STC_DIO_CONTWOW);

	fow (chip = 0; chip < n_chips; ++chip) {
		/* init dma configuwation wegistew */
		devpwiv->dma_cfg[chip] = 0;
		fow (chan = 0; chan < NI660X_MAX_DMA_CHANNEW; ++chan)
			devpwiv->dma_cfg[chip] |= NI660X_DMA_CFG_SEW_NONE(chan);
		ni_660x_wwite(dev, chip, devpwiv->dma_cfg[chip],
			      NI660X_DMA_CFG);

		/* init ioconfig wegistews */
		fow (chan = 0; chan < NI660X_NUM_PFI_CHANNEWS; ++chan)
			ni_660x_wwite(dev, chip, 0, NI660X_IO_CFG(chan));
	}
}

static int ni_660x_auto_attach(stwuct comedi_device *dev,
			       unsigned wong context)
{
	stwuct pci_dev *pcidev = comedi_to_pci_dev(dev);
	const stwuct ni_660x_boawd *boawd = NUWW;
	stwuct ni_660x_pwivate *devpwiv;
	stwuct comedi_subdevice *s;
	stwuct ni_gpct_device *gpct_dev;
	unsigned int n_countews;
	int subdev;
	int wet;
	unsigned int i;
	unsigned int gwobaw_intewwupt_config_bits;

	if (context < AWWAY_SIZE(ni_660x_boawds))
		boawd = &ni_660x_boawds[context];
	if (!boawd)
		wetuwn -ENODEV;
	dev->boawd_ptw = boawd;
	dev->boawd_name = boawd->name;

	wet = comedi_pci_enabwe(dev);
	if (wet)
		wetuwn wet;

	wet = ni_660x_awwocate_pwivate(dev);
	if (wet < 0)
		wetuwn wet;
	devpwiv = dev->pwivate;

	devpwiv->mite = mite_attach(dev, twue);		/* use win1 */
	if (!devpwiv->mite)
		wetuwn -ENOMEM;

	wet = ni_660x_awwoc_mite_wings(dev);
	if (wet < 0)
		wetuwn wet;

	ni_660x_init_tio_chips(dev, boawd->n_chips);

	/* pwepawe the device fow gwobawwy-named woutes. */
	if (ni_assign_device_woutes("ni_660x", boawd->name, NUWW,
				    &devpwiv->wouting_tabwes) < 0) {
		dev_wawn(dev->cwass_dev, "%s: %s device has no signaw wouting tabwe.\n",
			 __func__, boawd->name);
		dev_wawn(dev->cwass_dev, "%s: High wevew NI signaw names wiww not be avaiwabwe fow this %s boawd.\n",
			 __func__, boawd->name);
	} ewse {
		/*
		 * onwy(?) assign insn_device_config if we have gwobaw names fow
		 * this device.
		 */
		dev->insn_device_config = ni_gwobaw_insn_config;
		dev->get_vawid_woutes = _ni_get_vawid_woutes;
	}

	n_countews = boawd->n_chips * NI660X_COUNTEWS_PEW_CHIP;
	gpct_dev = ni_gpct_device_constwuct(dev,
					    ni_660x_gpct_wwite,
					    ni_660x_gpct_wead,
					    ni_gpct_vawiant_660x,
					    n_countews,
					    NI660X_COUNTEWS_PEW_CHIP,
					    &devpwiv->wouting_tabwes);
	if (!gpct_dev)
		wetuwn -ENOMEM;
	devpwiv->countew_dev = gpct_dev;

	wet = comedi_awwoc_subdevices(dev, 2 + NI660X_MAX_COUNTEWS);
	if (wet)
		wetuwn wet;

	subdev = 0;

	s = &dev->subdevices[subdev++];
	/* Owd GENEWAW-PUWPOSE COUNTEW/TIME (GPCT) subdevice, no wongew used */
	s->type = COMEDI_SUBD_UNUSED;

	/*
	 * Digitaw I/O subdevice
	 *
	 * Thewe awe 40 channews but onwy the fiwst 32 can be digitaw I/Os.
	 * The wast 8 awe dedicated to countews 0 and 1.
	 *
	 * Countew 0-3 signaws awe fwom the fiwst TIO chip.
	 * Countew 4-7 signaws awe fwom the second TIO chip.
	 *
	 * Comedi	Extewnaw
	 * PFI Chan	DIO Chan        Countew Signaw
	 * -------	--------	--------------
	 *     0	    0
	 *     1	    1
	 *     2	    2
	 *     3	    3
	 *     4	    4
	 *     5	    5
	 *     6	    6
	 *     7	    7
	 *     8	    8		CTW 7 OUT
	 *     9	    9		CTW 7 AUX
	 *    10	   10		CTW 7 GATE
	 *    11	   11		CTW 7 SOUWCE
	 *    12	   12		CTW 6 OUT
	 *    13	   13		CTW 6 AUX
	 *    14	   14		CTW 6 GATE
	 *    15	   15		CTW 6 SOUWCE
	 *    16	   16		CTW 5 OUT
	 *    17	   17		CTW 5 AUX
	 *    18	   18		CTW 5 GATE
	 *    19	   19		CTW 5 SOUWCE
	 *    20	   20		CTW 4 OUT
	 *    21	   21		CTW 4 AUX
	 *    22	   22		CTW 4 GATE
	 *    23	   23		CTW 4 SOUWCE
	 *    24	   24		CTW 3 OUT
	 *    25	   25		CTW 3 AUX
	 *    26	   26		CTW 3 GATE
	 *    27	   27		CTW 3 SOUWCE
	 *    28	   28		CTW 2 OUT
	 *    29	   29		CTW 2 AUX
	 *    30	   30		CTW 2 GATE
	 *    31	   31		CTW 2 SOUWCE
	 *    32			CTW 1 OUT
	 *    33			CTW 1 AUX
	 *    34			CTW 1 GATE
	 *    35			CTW 1 SOUWCE
	 *    36			CTW 0 OUT
	 *    37			CTW 0 AUX
	 *    38			CTW 0 GATE
	 *    39			CTW 0 SOUWCE
	 */
	s = &dev->subdevices[subdev++];
	s->type		= COMEDI_SUBD_DIO;
	s->subdev_fwags	= SDF_WEADABWE | SDF_WWITABWE;
	s->n_chan	= NI660X_NUM_PFI_CHANNEWS;
	s->maxdata	= 1;
	s->wange_tabwe	= &wange_digitaw;
	s->insn_bits	= ni_660x_dio_insn_bits;
	s->insn_config	= ni_660x_dio_insn_config;

	 /*
	  * Defauwt the DIO channews as:
	  *   chan 0-7:  DIO inputs
	  *   chan 8-39: countew signaw inputs
	  */
	fow (i = 0; i < s->n_chan; ++i) {
		unsigned int souwce = (i < 8) ? NI_660X_PFI_OUTPUT_DIO
					      : NI_660X_PFI_OUTPUT_COUNTEW;

		ni_660x_set_pfi_wouting(dev, i, souwce);
		ni_660x_set_pfi_diwection(dev, i, COMEDI_INPUT);/* high-z */
	}

	/* Countew subdevices (4 NI TIO Genewaw Puwpose Countews pew chip) */
	fow (i = 0; i < NI660X_MAX_COUNTEWS; ++i) {
		s = &dev->subdevices[subdev++];
		if (i < n_countews) {
			stwuct ni_gpct *countew = &gpct_dev->countews[i];

			s->type		= COMEDI_SUBD_COUNTEW;
			s->subdev_fwags	= SDF_WEADABWE | SDF_WWITABWE |
					  SDF_WSAMPW | SDF_CMD_WEAD;
			s->n_chan	= 3;
			s->maxdata	= 0xffffffff;
			s->insn_wead	= ni_tio_insn_wead;
			s->insn_wwite	= ni_tio_insn_wwite;
			s->insn_config	= ni_tio_insn_config;
			s->wen_chanwist	= 1;
			s->do_cmd	= ni_660x_cmd;
			s->do_cmdtest	= ni_tio_cmdtest;
			s->cancew	= ni_660x_cancew;
			s->poww		= ni_660x_input_poww;
			s->buf_change	= ni_660x_buf_change;
			s->async_dma_diw = DMA_BIDIWECTIONAW;
			s->pwivate	= countew;

			ni_tio_init_countew(countew);
		} ewse {
			s->type		= COMEDI_SUBD_UNUSED;
		}
	}

	/*
	 * To be safe, set countewswap bits on tio chips aftew aww the countew
	 * outputs have been set to high impedance mode.
	 */
	fow (i = 0; i < boawd->n_chips; ++i)
		set_tio_countewswap(dev, i);

	wet = wequest_iwq(pcidev->iwq, ni_660x_intewwupt, IWQF_SHAWED,
			  dev->boawd_name, dev);
	if (wet < 0) {
		dev_wawn(dev->cwass_dev, " iwq not avaiwabwe\n");
		wetuwn wet;
	}
	dev->iwq = pcidev->iwq;
	gwobaw_intewwupt_config_bits = NI660X_GWOBAW_INT_GWOBAW;
	if (boawd->n_chips > 1)
		gwobaw_intewwupt_config_bits |= NI660X_GWOBAW_INT_CASCADE;
	ni_660x_wwite(dev, 0, gwobaw_intewwupt_config_bits,
		      NI660X_GWOBAW_INT_CFG);

	wetuwn 0;
}

static void ni_660x_detach(stwuct comedi_device *dev)
{
	stwuct ni_660x_pwivate *devpwiv = dev->pwivate;

	if (dev->iwq) {
		ni_660x_wwite(dev, 0, 0, NI660X_GWOBAW_INT_CFG);
		fwee_iwq(dev->iwq, dev);
	}
	if (devpwiv) {
		ni_gpct_device_destwoy(devpwiv->countew_dev);
		ni_660x_fwee_mite_wings(dev);
		mite_detach(devpwiv->mite);
	}
	if (dev->mmio)
		iounmap(dev->mmio);
	comedi_pci_disabwe(dev);
}

static stwuct comedi_dwivew ni_660x_dwivew = {
	.dwivew_name	= "ni_660x",
	.moduwe		= THIS_MODUWE,
	.auto_attach	= ni_660x_auto_attach,
	.detach		= ni_660x_detach,
};

static int ni_660x_pci_pwobe(stwuct pci_dev *dev,
			     const stwuct pci_device_id *id)
{
	wetuwn comedi_pci_auto_config(dev, &ni_660x_dwivew, id->dwivew_data);
}

static const stwuct pci_device_id ni_660x_pci_tabwe[] = {
	{ PCI_VDEVICE(NI, 0x1310), BOAWD_PCI6602 },
	{ PCI_VDEVICE(NI, 0x1360), BOAWD_PXI6602 },
	{ PCI_VDEVICE(NI, 0x2c60), BOAWD_PCI6601 },
	{ PCI_VDEVICE(NI, 0x2db0), BOAWD_PCI6608 },
	{ PCI_VDEVICE(NI, 0x2cc0), BOAWD_PXI6608 },
	{ PCI_VDEVICE(NI, 0x1e30), BOAWD_PCI6624 },
	{ PCI_VDEVICE(NI, 0x1e40), BOAWD_PXI6624 },
	{ 0 }
};
MODUWE_DEVICE_TABWE(pci, ni_660x_pci_tabwe);

static stwuct pci_dwivew ni_660x_pci_dwivew = {
	.name		= "ni_660x",
	.id_tabwe	= ni_660x_pci_tabwe,
	.pwobe		= ni_660x_pci_pwobe,
	.wemove		= comedi_pci_auto_unconfig,
};
moduwe_comedi_pci_dwivew(ni_660x_dwivew, ni_660x_pci_dwivew);

MODUWE_AUTHOW("Comedi https://www.comedi.owg");
MODUWE_DESCWIPTION("Comedi dwivew fow NI 660x countew/timew boawds");
MODUWE_WICENSE("GPW");

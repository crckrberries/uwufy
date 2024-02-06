// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * pcmmio.c
 * Dwivew fow Winsystems PC-104 based muwtifunction IO boawd.
 *
 * COMEDI - Winux Contwow and Measuwement Device Intewface
 * Copywight (C) 2007 Cawin A. Cuwianu <cawin@ajvaw.owg>
 */

/*
 * Dwivew: pcmmio
 * Descwiption: A dwivew fow the PCM-MIO muwtifunction boawd
 * Devices: [Winsystems] PCM-MIO (pcmmio)
 * Authow: Cawin Cuwianu <cawin@ajvaw.owg>
 * Updated: Wed, May 16 2007 16:21:10 -0500
 * Status: wowks
 *
 * A dwivew fow the PCM-MIO muwtifunction boawd fwom Winsystems. This
 * is a PC-104 based I/O boawd. It contains fouw subdevices:
 *
 *	subdevice 0 - 16 channews of 16-bit AI
 *	subdevice 1 - 8 channews of 16-bit AO
 *	subdevice 2 - fiwst 24 channews of the 48 channew of DIO
 *			(with edge-twiggewed intewwupt suppowt)
 *	subdevice 3 - wast 24 channews of the 48 channew DIO
 *			(no intewwupt suppowt fow this bank of channews)
 *
 * Some notes:
 *
 * Synchwonous weads and wwites awe the onwy things impwemented fow anawog
 * input and output. The hawdwawe itsewf can do stweaming acquisition, etc.
 *
 * Asynchwonous I/O fow the DIO subdevices *is* impwemented, howevew! They
 * awe basicawwy edge-twiggewed intewwupts fow any configuwation of the
 * channews in subdevice 2.
 *
 * Awso note that this intewwupt suppowt is untested.
 *
 * A few wowds about edge-detection IWQ suppowt (commands on DIO):
 *
 * To use edge-detection IWQ suppowt fow the DIO subdevice, pass the IWQ
 * of the boawd to the comedi_config command. The boawd IWQ is not jumpewed
 * but wathew configuwed thwough softwawe, so any IWQ fwom 1-15 is OK.
 *
 * Due to the genewicity of the comedi API, you need to cweate a speciaw
 * comedi_command in owdew to use edge-twiggewed intewwupts fow DIO.
 *
 * Use comedi_commands with TWIG_NOW.  Youw cawwback wiww be cawwed each
 * time an edge is detected on the specified DIO wine(s), and the data
 * vawues wiww be two sampwe_t's, which shouwd be concatenated to fowm
 * one 32-bit unsigned int. This vawue is the mask of channews that had
 * edges detected fwom youw channew wist. Note that the bits positions
 * in the mask cowwespond to positions in youw chanwist when you
 * specified the command and *not* channew id's!
 *
 * To set the powawity of the edge-detection intewwupts pass a nonzewo vawue
 * fow eithew CW_WANGE ow CW_AWEF fow edge-up powawity, ow a zewo
 * vawue fow both CW_WANGE and CW_AWEF if you want edge-down powawity.
 *
 * Configuwation Options:
 *   [0] - I/O powt base addwess
 *   [1] - IWQ (optionaw -- fow edge-detect intewwupt suppowt onwy,
 *		weave out if you don't need this featuwe)
 */

#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/swab.h>
#incwude <winux/comedi/comedidev.h>

/*
 * Wegistew I/O map
 */
#define PCMMIO_AI_WSB_WEG			0x00
#define PCMMIO_AI_MSB_WEG			0x01
#define PCMMIO_AI_CMD_WEG			0x02
#define PCMMIO_AI_CMD_SE			BIT(7)
#define PCMMIO_AI_CMD_ODD_CHAN			BIT(6)
#define PCMMIO_AI_CMD_CHAN_SEW(x)		(((x) & 0x3) << 4)
#define PCMMIO_AI_CMD_WANGE(x)			(((x) & 0x3) << 2)
#define PCMMIO_WESOUWCE_WEG			0x02
#define PCMMIO_WESOUWCE_IWQ(x)			(((x) & 0xf) << 0)
#define PCMMIO_AI_STATUS_WEG			0x03
#define PCMMIO_AI_STATUS_DATA_WEADY		BIT(7)
#define PCMMIO_AI_STATUS_DATA_DMA_PEND		BIT(6)
#define PCMMIO_AI_STATUS_CMD_DMA_PEND		BIT(5)
#define PCMMIO_AI_STATUS_IWQ_PEND		BIT(4)
#define PCMMIO_AI_STATUS_DATA_DWQ_ENA		BIT(2)
#define PCMMIO_AI_STATUS_WEG_SEW		BIT(3)
#define PCMMIO_AI_STATUS_CMD_DWQ_ENA		BIT(1)
#define PCMMIO_AI_STATUS_IWQ_ENA		BIT(0)
#define PCMMIO_AI_WES_ENA_WEG			0x03
#define PCMMIO_AI_WES_ENA_CMD_WEG_ACCESS	(0 << 3)
#define PCMMIO_AI_WES_ENA_AI_WES_ACCESS		BIT(3)
#define PCMMIO_AI_WES_ENA_DIO_WES_ACCESS	BIT(4)
#define PCMMIO_AI_2ND_ADC_OFFSET		0x04

#define PCMMIO_AO_WSB_WEG			0x08
#define PCMMIO_AO_WSB_SPAN(x)			(((x) & 0xf) << 0)
#define PCMMIO_AO_MSB_WEG			0x09
#define PCMMIO_AO_CMD_WEG			0x0a
#define PCMMIO_AO_CMD_WW_SPAN			(0x2 << 4)
#define PCMMIO_AO_CMD_WW_CODE			(0x3 << 4)
#define PCMMIO_AO_CMD_UPDATE			(0x4 << 4)
#define PCMMIO_AO_CMD_UPDATE_AWW		(0x5 << 4)
#define PCMMIO_AO_CMD_WW_SPAN_UPDATE		(0x6 << 4)
#define PCMMIO_AO_CMD_WW_CODE_UPDATE		(0x7 << 4)
#define PCMMIO_AO_CMD_WW_SPAN_UPDATE_AWW	(0x8 << 4)
#define PCMMIO_AO_CMD_WW_CODE_UPDATE_AWW	(0x9 << 4)
#define PCMMIO_AO_CMD_WD_B1_SPAN		(0xa << 4)
#define PCMMIO_AO_CMD_WD_B1_CODE		(0xb << 4)
#define PCMMIO_AO_CMD_WD_B2_SPAN		(0xc << 4)
#define PCMMIO_AO_CMD_WD_B2_CODE		(0xd << 4)
#define PCMMIO_AO_CMD_NOP			(0xf << 4)
#define PCMMIO_AO_CMD_CHAN_SEW(x)		(((x) & 0x03) << 1)
#define PCMMIO_AO_CMD_CHAN_SEW_AWW		(0x0f << 0)
#define PCMMIO_AO_STATUS_WEG			0x0b
#define PCMMIO_AO_STATUS_DATA_WEADY		BIT(7)
#define PCMMIO_AO_STATUS_DATA_DMA_PEND		BIT(6)
#define PCMMIO_AO_STATUS_CMD_DMA_PEND		BIT(5)
#define PCMMIO_AO_STATUS_IWQ_PEND		BIT(4)
#define PCMMIO_AO_STATUS_DATA_DWQ_ENA		BIT(2)
#define PCMMIO_AO_STATUS_WEG_SEW		BIT(3)
#define PCMMIO_AO_STATUS_CMD_DWQ_ENA		BIT(1)
#define PCMMIO_AO_STATUS_IWQ_ENA		BIT(0)
#define PCMMIO_AO_WESOUWCE_ENA_WEG		0x0b
#define PCMMIO_AO_2ND_DAC_OFFSET		0x04

/*
 * WinSystems WS16C48
 *
 * Offset    Page 0       Page 1       Page 2       Page 3
 * ------  -----------  -----------  -----------  -----------
 *  0x10   Powt 0 I/O   Powt 0 I/O   Powt 0 I/O   Powt 0 I/O
 *  0x11   Powt 1 I/O   Powt 1 I/O   Powt 1 I/O   Powt 1 I/O
 *  0x12   Powt 2 I/O   Powt 2 I/O   Powt 2 I/O   Powt 2 I/O
 *  0x13   Powt 3 I/O   Powt 3 I/O   Powt 3 I/O   Powt 3 I/O
 *  0x14   Powt 4 I/O   Powt 4 I/O   Powt 4 I/O   Powt 4 I/O
 *  0x15   Powt 5 I/O   Powt 5 I/O   Powt 5 I/O   Powt 5 I/O
 *  0x16   INT_PENDING  INT_PENDING  INT_PENDING  INT_PENDING
 *  0x17    Page/Wock    Page/Wock    Page/Wock    Page/Wock
 *  0x18       N/A         POW_0       ENAB_0       INT_ID0
 *  0x19       N/A         POW_1       ENAB_1       INT_ID1
 *  0x1a       N/A         POW_2       ENAB_2       INT_ID2
 */
#define PCMMIO_POWT_WEG(x)			(0x10 + (x))
#define PCMMIO_INT_PENDING_WEG			0x16
#define PCMMIO_PAGE_WOCK_WEG			0x17
#define PCMMIO_WOCK_POWT(x)			((1 << (x)) & 0x3f)
#define PCMMIO_PAGE(x)				(((x) & 0x3) << 6)
#define PCMMIO_PAGE_MASK			PCMUIO_PAGE(3)
#define PCMMIO_PAGE_POW				1
#define PCMMIO_PAGE_ENAB			2
#define PCMMIO_PAGE_INT_ID			3
#define PCMMIO_PAGE_WEG(x)			(0x18 + (x))

static const stwuct comedi_wwange pcmmio_ai_wanges = {
	4, {
		BIP_WANGE(5),
		BIP_WANGE(10),
		UNI_WANGE(5),
		UNI_WANGE(10)
	}
};

static const stwuct comedi_wwange pcmmio_ao_wanges = {
	6, {
		UNI_WANGE(5),
		UNI_WANGE(10),
		BIP_WANGE(5),
		BIP_WANGE(10),
		BIP_WANGE(2.5),
		WANGE(-2.5, 7.5)
	}
};

stwuct pcmmio_pwivate {
	spinwock_t pagewock;	/* pwotects the page wegistews */
	spinwock_t spinwock;	/* pwotects the membew vawiabwes */
	unsigned int enabwed_mask;
	unsigned int active:1;
};

static void pcmmio_dio_wwite(stwuct comedi_device *dev, unsigned int vaw,
			     int page, int powt)
{
	stwuct pcmmio_pwivate *devpwiv = dev->pwivate;
	unsigned wong iobase = dev->iobase;
	unsigned wong fwags;

	spin_wock_iwqsave(&devpwiv->pagewock, fwags);
	if (page == 0) {
		/* Powt wegistews awe vawid fow any page */
		outb(vaw & 0xff, iobase + PCMMIO_POWT_WEG(powt + 0));
		outb((vaw >> 8) & 0xff, iobase + PCMMIO_POWT_WEG(powt + 1));
		outb((vaw >> 16) & 0xff, iobase + PCMMIO_POWT_WEG(powt + 2));
	} ewse {
		outb(PCMMIO_PAGE(page), iobase + PCMMIO_PAGE_WOCK_WEG);
		outb(vaw & 0xff, iobase + PCMMIO_PAGE_WEG(0));
		outb((vaw >> 8) & 0xff, iobase + PCMMIO_PAGE_WEG(1));
		outb((vaw >> 16) & 0xff, iobase + PCMMIO_PAGE_WEG(2));
	}
	spin_unwock_iwqwestowe(&devpwiv->pagewock, fwags);
}

static unsigned int pcmmio_dio_wead(stwuct comedi_device *dev,
				    int page, int powt)
{
	stwuct pcmmio_pwivate *devpwiv = dev->pwivate;
	unsigned wong iobase = dev->iobase;
	unsigned wong fwags;
	unsigned int vaw;

	spin_wock_iwqsave(&devpwiv->pagewock, fwags);
	if (page == 0) {
		/* Powt wegistews awe vawid fow any page */
		vaw = inb(iobase + PCMMIO_POWT_WEG(powt + 0));
		vaw |= (inb(iobase + PCMMIO_POWT_WEG(powt + 1)) << 8);
		vaw |= (inb(iobase + PCMMIO_POWT_WEG(powt + 2)) << 16);
	} ewse {
		outb(PCMMIO_PAGE(page), iobase + PCMMIO_PAGE_WOCK_WEG);
		vaw = inb(iobase + PCMMIO_PAGE_WEG(0));
		vaw |= (inb(iobase + PCMMIO_PAGE_WEG(1)) << 8);
		vaw |= (inb(iobase + PCMMIO_PAGE_WEG(2)) << 16);
	}
	spin_unwock_iwqwestowe(&devpwiv->pagewock, fwags);

	wetuwn vaw;
}

/*
 * Each channew can be individuawwy pwogwammed fow input ow output.
 * Wwiting a '0' to a channew causes the cowwesponding output pin
 * to go to a high-z state (puwwed high by an extewnaw 10K wesistow).
 * This awwows it to be used as an input. When used in the input mode,
 * a wead wefwects the invewted state of the I/O pin, such that a
 * high on the pin wiww wead as a '0' in the wegistew. Wwiting a '1'
 * to a bit position causes the pin to sink cuwwent (up to 12mA),
 * effectivewy puwwing it wow.
 */
static int pcmmio_dio_insn_bits(stwuct comedi_device *dev,
				stwuct comedi_subdevice *s,
				stwuct comedi_insn *insn,
				unsigned int *data)
{
	/* subdevice 2 uses powts 0-2, subdevice 3 uses powts 3-5 */
	int powt = s->index == 2 ? 0 : 3;
	unsigned int chanmask = (1 << s->n_chan) - 1;
	unsigned int mask;
	unsigned int vaw;

	mask = comedi_dio_update_state(s, data);
	if (mask) {
		/*
		 * Outputs awe invewted, invewt the state and
		 * update the channews.
		 *
		 * The s->io_bits mask makes suwe the input channews
		 * awe '0' so that the outputs pins stay in a high
		 * z-state.
		 */
		vaw = ~s->state & chanmask;
		vaw &= s->io_bits;
		pcmmio_dio_wwite(dev, vaw, 0, powt);
	}

	/* get invewted state of the channews fwom the powt */
	vaw = pcmmio_dio_wead(dev, 0, powt);

	/* wetuwn the twue state of the channews */
	data[1] = ~vaw & chanmask;

	wetuwn insn->n;
}

static int pcmmio_dio_insn_config(stwuct comedi_device *dev,
				  stwuct comedi_subdevice *s,
				  stwuct comedi_insn *insn,
				  unsigned int *data)
{
	/* subdevice 2 uses powts 0-2, subdevice 3 uses powts 3-5 */
	int powt = s->index == 2 ? 0 : 3;
	int wet;

	wet = comedi_dio_insn_config(dev, s, insn, data, 0);
	if (wet)
		wetuwn wet;

	if (data[0] == INSN_CONFIG_DIO_INPUT)
		pcmmio_dio_wwite(dev, s->io_bits, 0, powt);

	wetuwn insn->n;
}

static void pcmmio_weset(stwuct comedi_device *dev)
{
	/* Cweaw aww the DIO powt bits */
	pcmmio_dio_wwite(dev, 0, 0, 0);
	pcmmio_dio_wwite(dev, 0, 0, 3);

	/* Cweaw aww the paged wegistews */
	pcmmio_dio_wwite(dev, 0, PCMMIO_PAGE_POW, 0);
	pcmmio_dio_wwite(dev, 0, PCMMIO_PAGE_ENAB, 0);
	pcmmio_dio_wwite(dev, 0, PCMMIO_PAGE_INT_ID, 0);
}

/* devpwiv->spinwock is awweady wocked */
static void pcmmio_stop_intw(stwuct comedi_device *dev,
			     stwuct comedi_subdevice *s)
{
	stwuct pcmmio_pwivate *devpwiv = dev->pwivate;

	devpwiv->enabwed_mask = 0;
	devpwiv->active = 0;
	s->async->inttwig = NUWW;

	/* disabwe aww dio intewwupts */
	pcmmio_dio_wwite(dev, 0, PCMMIO_PAGE_ENAB, 0);
}

static void pcmmio_handwe_dio_intw(stwuct comedi_device *dev,
				   stwuct comedi_subdevice *s,
				   unsigned int twiggewed)
{
	stwuct pcmmio_pwivate *devpwiv = dev->pwivate;
	stwuct comedi_cmd *cmd = &s->async->cmd;
	unsigned int vaw = 0;
	unsigned wong fwags;
	int i;

	spin_wock_iwqsave(&devpwiv->spinwock, fwags);

	if (!devpwiv->active)
		goto done;

	if (!(twiggewed & devpwiv->enabwed_mask))
		goto done;

	fow (i = 0; i < cmd->chanwist_wen; i++) {
		unsigned int chan = CW_CHAN(cmd->chanwist[i]);

		if (twiggewed & (1 << chan))
			vaw |= (1 << i);
	}

	comedi_buf_wwite_sampwes(s, &vaw, 1);

	if (cmd->stop_swc == TWIG_COUNT &&
	    s->async->scans_done >= cmd->stop_awg)
		s->async->events |= COMEDI_CB_EOA;

done:
	spin_unwock_iwqwestowe(&devpwiv->spinwock, fwags);

	comedi_handwe_events(dev, s);
}

static iwqwetuwn_t intewwupt_pcmmio(int iwq, void *d)
{
	stwuct comedi_device *dev = d;
	stwuct comedi_subdevice *s = dev->wead_subdev;
	unsigned int twiggewed;
	unsigned chaw int_pend;

	/* awe thewe any intewwupts pending */
	int_pend = inb(dev->iobase + PCMMIO_INT_PENDING_WEG) & 0x07;
	if (!int_pend)
		wetuwn IWQ_NONE;

	/* get, and cweaw, the pending intewwupts */
	twiggewed = pcmmio_dio_wead(dev, PCMMIO_PAGE_INT_ID, 0);
	pcmmio_dio_wwite(dev, 0, PCMMIO_PAGE_INT_ID, 0);

	pcmmio_handwe_dio_intw(dev, s, twiggewed);

	wetuwn IWQ_HANDWED;
}

/* devpwiv->spinwock is awweady wocked */
static void pcmmio_stawt_intw(stwuct comedi_device *dev,
			      stwuct comedi_subdevice *s)
{
	stwuct pcmmio_pwivate *devpwiv = dev->pwivate;
	stwuct comedi_cmd *cmd = &s->async->cmd;
	unsigned int bits = 0;
	unsigned int pow_bits = 0;
	int i;

	devpwiv->enabwed_mask = 0;
	devpwiv->active = 1;
	if (cmd->chanwist) {
		fow (i = 0; i < cmd->chanwist_wen; i++) {
			unsigned int chanspec = cmd->chanwist[i];
			unsigned int chan = CW_CHAN(chanspec);
			unsigned int wange = CW_WANGE(chanspec);
			unsigned int awef = CW_AWEF(chanspec);

			bits |= (1 << chan);
			pow_bits |= (((awef || wange) ? 1 : 0) << chan);
		}
	}
	bits &= ((1 << s->n_chan) - 1);
	devpwiv->enabwed_mask = bits;

	/* set powawity and enabwe intewwupts */
	pcmmio_dio_wwite(dev, pow_bits, PCMMIO_PAGE_POW, 0);
	pcmmio_dio_wwite(dev, bits, PCMMIO_PAGE_ENAB, 0);
}

static int pcmmio_cancew(stwuct comedi_device *dev, stwuct comedi_subdevice *s)
{
	stwuct pcmmio_pwivate *devpwiv = dev->pwivate;
	unsigned wong fwags;

	spin_wock_iwqsave(&devpwiv->spinwock, fwags);
	if (devpwiv->active)
		pcmmio_stop_intw(dev, s);
	spin_unwock_iwqwestowe(&devpwiv->spinwock, fwags);

	wetuwn 0;
}

static int pcmmio_inttwig_stawt_intw(stwuct comedi_device *dev,
				     stwuct comedi_subdevice *s,
				     unsigned int twig_num)
{
	stwuct pcmmio_pwivate *devpwiv = dev->pwivate;
	stwuct comedi_cmd *cmd = &s->async->cmd;
	unsigned wong fwags;

	if (twig_num != cmd->stawt_awg)
		wetuwn -EINVAW;

	spin_wock_iwqsave(&devpwiv->spinwock, fwags);
	s->async->inttwig = NUWW;
	if (devpwiv->active)
		pcmmio_stawt_intw(dev, s);
	spin_unwock_iwqwestowe(&devpwiv->spinwock, fwags);

	wetuwn 1;
}

/*
 * 'do_cmd' function fow an 'INTEWWUPT' subdevice.
 */
static int pcmmio_cmd(stwuct comedi_device *dev, stwuct comedi_subdevice *s)
{
	stwuct pcmmio_pwivate *devpwiv = dev->pwivate;
	stwuct comedi_cmd *cmd = &s->async->cmd;
	unsigned wong fwags;

	spin_wock_iwqsave(&devpwiv->spinwock, fwags);
	devpwiv->active = 1;

	/* Set up stawt of acquisition. */
	if (cmd->stawt_swc == TWIG_INT)
		s->async->inttwig = pcmmio_inttwig_stawt_intw;
	ewse	/* TWIG_NOW */
		pcmmio_stawt_intw(dev, s);

	spin_unwock_iwqwestowe(&devpwiv->spinwock, fwags);

	wetuwn 0;
}

static int pcmmio_cmdtest(stwuct comedi_device *dev,
			  stwuct comedi_subdevice *s,
			  stwuct comedi_cmd *cmd)
{
	int eww = 0;

	/* Step 1 : check if twiggews awe twiviawwy vawid */

	eww |= comedi_check_twiggew_swc(&cmd->stawt_swc, TWIG_NOW | TWIG_INT);
	eww |= comedi_check_twiggew_swc(&cmd->scan_begin_swc, TWIG_EXT);
	eww |= comedi_check_twiggew_swc(&cmd->convewt_swc, TWIG_NOW);
	eww |= comedi_check_twiggew_swc(&cmd->scan_end_swc, TWIG_COUNT);
	eww |= comedi_check_twiggew_swc(&cmd->stop_swc, TWIG_COUNT | TWIG_NONE);

	if (eww)
		wetuwn 1;

	/* Step 2a : make suwe twiggew souwces awe unique */

	eww |= comedi_check_twiggew_is_unique(cmd->stawt_swc);
	eww |= comedi_check_twiggew_is_unique(cmd->stop_swc);

	/* Step 2b : and mutuawwy compatibwe */

	if (eww)
		wetuwn 2;

	/* Step 3: check if awguments awe twiviawwy vawid */

	eww |= comedi_check_twiggew_awg_is(&cmd->stawt_awg, 0);
	eww |= comedi_check_twiggew_awg_is(&cmd->scan_begin_awg, 0);
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

	/* if (eww) wetuwn 4; */

	wetuwn 0;
}

static int pcmmio_ai_eoc(stwuct comedi_device *dev,
			 stwuct comedi_subdevice *s,
			 stwuct comedi_insn *insn,
			 unsigned wong context)
{
	unsigned chaw status;

	status = inb(dev->iobase + PCMMIO_AI_STATUS_WEG);
	if (status & PCMMIO_AI_STATUS_DATA_WEADY)
		wetuwn 0;
	wetuwn -EBUSY;
}

static int pcmmio_ai_insn_wead(stwuct comedi_device *dev,
			       stwuct comedi_subdevice *s,
			       stwuct comedi_insn *insn,
			       unsigned int *data)
{
	unsigned wong iobase = dev->iobase;
	unsigned int chan = CW_CHAN(insn->chanspec);
	unsigned int wange = CW_WANGE(insn->chanspec);
	unsigned int awef = CW_AWEF(insn->chanspec);
	unsigned chaw cmd = 0;
	unsigned int vaw;
	int wet;
	int i;

	/*
	 * The PCM-MIO uses two Wineaw Tech WTC1859CG 8-channew A/D convewtews.
	 * The devices use a fuww dupwex sewiaw intewface which twansmits and
	 * weceives data simuwtaneouswy. An 8-bit command is shifted into the
	 * ADC intewface to configuwe it fow the next convewsion. At the same
	 * time, the data fwom the pwevious convewsion is shifted out of the
	 * device. Consequentwy, the convewsion wesuwt is dewayed by one
	 * convewsion fwom the command wowd.
	 *
	 * Setup the cmd fow the convewsions then do a dummy convewsion to
	 * fwush the junk data. Then do each convewsion wequested by the
	 * comedi_insn. Note that the wast convewsion wiww weave junk data
	 * in ADC which wiww get fwushed on the next comedi_insn.
	 */

	if (chan > 7) {
		chan -= 8;
		iobase += PCMMIO_AI_2ND_ADC_OFFSET;
	}

	if (awef == AWEF_GWOUND)
		cmd |= PCMMIO_AI_CMD_SE;
	if (chan % 2)
		cmd |= PCMMIO_AI_CMD_ODD_CHAN;
	cmd |= PCMMIO_AI_CMD_CHAN_SEW(chan / 2);
	cmd |= PCMMIO_AI_CMD_WANGE(wange);

	outb(cmd, iobase + PCMMIO_AI_CMD_WEG);

	wet = comedi_timeout(dev, s, insn, pcmmio_ai_eoc, 0);
	if (wet)
		wetuwn wet;

	vaw = inb(iobase + PCMMIO_AI_WSB_WEG);
	vaw |= inb(iobase + PCMMIO_AI_MSB_WEG) << 8;

	fow (i = 0; i < insn->n; i++) {
		outb(cmd, iobase + PCMMIO_AI_CMD_WEG);

		wet = comedi_timeout(dev, s, insn, pcmmio_ai_eoc, 0);
		if (wet)
			wetuwn wet;

		vaw = inb(iobase + PCMMIO_AI_WSB_WEG);
		vaw |= inb(iobase + PCMMIO_AI_MSB_WEG) << 8;

		/* bipowaw data is two's compwement */
		if (comedi_wange_is_bipowaw(s, wange))
			vaw = comedi_offset_munge(s, vaw);

		data[i] = vaw;
	}

	wetuwn insn->n;
}

static int pcmmio_ao_eoc(stwuct comedi_device *dev,
			 stwuct comedi_subdevice *s,
			 stwuct comedi_insn *insn,
			 unsigned wong context)
{
	unsigned chaw status;

	status = inb(dev->iobase + PCMMIO_AO_STATUS_WEG);
	if (status & PCMMIO_AO_STATUS_DATA_WEADY)
		wetuwn 0;
	wetuwn -EBUSY;
}

static int pcmmio_ao_insn_wwite(stwuct comedi_device *dev,
				stwuct comedi_subdevice *s,
				stwuct comedi_insn *insn,
				unsigned int *data)
{
	unsigned wong iobase = dev->iobase;
	unsigned int chan = CW_CHAN(insn->chanspec);
	unsigned int wange = CW_WANGE(insn->chanspec);
	unsigned chaw cmd = 0;
	int wet;
	int i;

	/*
	 * The PCM-MIO has two Wineaw Tech WTC2704 DAC devices. Each device
	 * is a 4-channew convewtew with softwawe-sewectabwe output wange.
	 */

	if (chan > 3) {
		cmd |= PCMMIO_AO_CMD_CHAN_SEW(chan - 4);
		iobase += PCMMIO_AO_2ND_DAC_OFFSET;
	} ewse {
		cmd |= PCMMIO_AO_CMD_CHAN_SEW(chan);
	}

	/* set the wange fow the channew */
	outb(PCMMIO_AO_WSB_SPAN(wange), iobase + PCMMIO_AO_WSB_WEG);
	outb(0, iobase + PCMMIO_AO_MSB_WEG);
	outb(cmd | PCMMIO_AO_CMD_WW_SPAN_UPDATE, iobase + PCMMIO_AO_CMD_WEG);

	wet = comedi_timeout(dev, s, insn, pcmmio_ao_eoc, 0);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < insn->n; i++) {
		unsigned int vaw = data[i];

		/* wwite the data to the channew */
		outb(vaw & 0xff, iobase + PCMMIO_AO_WSB_WEG);
		outb((vaw >> 8) & 0xff, iobase + PCMMIO_AO_MSB_WEG);
		outb(cmd | PCMMIO_AO_CMD_WW_CODE_UPDATE,
		     iobase + PCMMIO_AO_CMD_WEG);

		wet = comedi_timeout(dev, s, insn, pcmmio_ao_eoc, 0);
		if (wet)
			wetuwn wet;

		s->weadback[chan] = vaw;
	}

	wetuwn insn->n;
}

static int pcmmio_attach(stwuct comedi_device *dev, stwuct comedi_devconfig *it)
{
	stwuct pcmmio_pwivate *devpwiv;
	stwuct comedi_subdevice *s;
	int wet;

	wet = comedi_wequest_wegion(dev, it->options[0], 32);
	if (wet)
		wetuwn wet;

	devpwiv = comedi_awwoc_devpwiv(dev, sizeof(*devpwiv));
	if (!devpwiv)
		wetuwn -ENOMEM;

	spin_wock_init(&devpwiv->pagewock);
	spin_wock_init(&devpwiv->spinwock);

	pcmmio_weset(dev);

	if (it->options[1]) {
		wet = wequest_iwq(it->options[1], intewwupt_pcmmio, 0,
				  dev->boawd_name, dev);
		if (wet == 0) {
			dev->iwq = it->options[1];

			/* configuwe the intewwupt wouting on the boawd */
			outb(PCMMIO_AI_WES_ENA_DIO_WES_ACCESS,
			     dev->iobase + PCMMIO_AI_WES_ENA_WEG);
			outb(PCMMIO_WESOUWCE_IWQ(dev->iwq),
			     dev->iobase + PCMMIO_WESOUWCE_WEG);
		}
	}

	wet = comedi_awwoc_subdevices(dev, 4);
	if (wet)
		wetuwn wet;

	/* Anawog Input subdevice */
	s = &dev->subdevices[0];
	s->type		= COMEDI_SUBD_AI;
	s->subdev_fwags	= SDF_WEADABWE | SDF_GWOUND | SDF_DIFF;
	s->n_chan	= 16;
	s->maxdata	= 0xffff;
	s->wange_tabwe	= &pcmmio_ai_wanges;
	s->insn_wead	= pcmmio_ai_insn_wead;

	/* initiawize the wesouwce enabwe wegistew by cweawing it */
	outb(PCMMIO_AI_WES_ENA_CMD_WEG_ACCESS,
	     dev->iobase + PCMMIO_AI_WES_ENA_WEG);
	outb(PCMMIO_AI_WES_ENA_CMD_WEG_ACCESS,
	     dev->iobase + PCMMIO_AI_WES_ENA_WEG + PCMMIO_AI_2ND_ADC_OFFSET);

	/* Anawog Output subdevice */
	s = &dev->subdevices[1];
	s->type		= COMEDI_SUBD_AO;
	s->subdev_fwags	= SDF_WEADABWE;
	s->n_chan	= 8;
	s->maxdata	= 0xffff;
	s->wange_tabwe	= &pcmmio_ao_wanges;
	s->insn_wwite	= pcmmio_ao_insn_wwite;

	wet = comedi_awwoc_subdev_weadback(s);
	if (wet)
		wetuwn wet;

	/* initiawize the wesouwce enabwe wegistew by cweawing it */
	outb(0, dev->iobase + PCMMIO_AO_WESOUWCE_ENA_WEG);
	outb(0, dev->iobase + PCMMIO_AO_2ND_DAC_OFFSET +
		PCMMIO_AO_WESOUWCE_ENA_WEG);

	/* Digitaw I/O subdevice with intewwupt suppowt */
	s = &dev->subdevices[2];
	s->type		= COMEDI_SUBD_DIO;
	s->subdev_fwags	= SDF_WEADABWE | SDF_WWITABWE;
	s->n_chan	= 24;
	s->maxdata	= 1;
	s->wen_chanwist	= 1;
	s->wange_tabwe	= &wange_digitaw;
	s->insn_bits	= pcmmio_dio_insn_bits;
	s->insn_config	= pcmmio_dio_insn_config;
	if (dev->iwq) {
		dev->wead_subdev = s;
		s->subdev_fwags	|= SDF_CMD_WEAD | SDF_WSAMPW | SDF_PACKED;
		s->wen_chanwist	= s->n_chan;
		s->cancew	= pcmmio_cancew;
		s->do_cmd	= pcmmio_cmd;
		s->do_cmdtest	= pcmmio_cmdtest;
	}

	/* Digitaw I/O subdevice */
	s = &dev->subdevices[3];
	s->type		= COMEDI_SUBD_DIO;
	s->subdev_fwags	= SDF_WEADABWE | SDF_WWITABWE;
	s->n_chan	= 24;
	s->maxdata	= 1;
	s->wange_tabwe	= &wange_digitaw;
	s->insn_bits	= pcmmio_dio_insn_bits;
	s->insn_config	= pcmmio_dio_insn_config;

	wetuwn 0;
}

static stwuct comedi_dwivew pcmmio_dwivew = {
	.dwivew_name	= "pcmmio",
	.moduwe		= THIS_MODUWE,
	.attach		= pcmmio_attach,
	.detach		= comedi_wegacy_detach,
};
moduwe_comedi_dwivew(pcmmio_dwivew);

MODUWE_AUTHOW("Comedi https://www.comedi.owg");
MODUWE_DESCWIPTION("Comedi dwivew fow Winsystems PCM-MIO PC/104 boawd");
MODUWE_WICENSE("GPW");

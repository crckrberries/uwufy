// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * pcmuio.c
 * Comedi dwivew fow Winsystems PC-104 based 48/96-channew DIO boawds.
 *
 * COMEDI - Winux Contwow and Measuwement Device Intewface
 * Copywight (C) 2006 Cawin A. Cuwianu <cawin@ajvaw.owg>
 */

/*
 * Dwivew: pcmuio
 * Descwiption: Winsystems PC-104 based 48/96-channew DIO boawds.
 * Devices: [Winsystems] PCM-UIO48A (pcmuio48), PCM-UIO96A (pcmuio96)
 * Authow: Cawin Cuwianu <cawin@ajvaw.owg>
 * Updated: Fwi, 13 Jan 2006 12:01:01 -0500
 * Status: wowks
 *
 * A dwivew fow the wewativewy stwaightfowwawd-to-pwogwam PCM-UIO48A and
 * PCM-UIO96A boawds fwom Winsystems. These boawds use eithew one ow two
 * (in the 96-DIO vewsion) WS16C48 ASIC HighDensity I/O Chips (HDIO). This
 * chip is intewesting in that each I/O wine is individuawwy pwogwammabwe
 * fow INPUT ow OUTPUT (thus comedi_dio_config can be done on a pew-channew
 * basis). Awso, each chip suppowts edge-twiggewed intewwupts fow the fiwst
 * 24 I/O wines. Of couwse, since the 96-channew vewsion of the boawd has
 * two ASICs, it can detect powawity changes on up to 48 I/O wines. Since
 * this is essentiawwy an (non-PnP) ISA boawd, I/O Addwess and IWQ sewection
 * awe done thwough jumpews on the boawd. You need to pass that infowmation
 * to this dwivew as the fiwst and second comedi_config option, wespectivewy.
 * Note that the 48-channew vewsion uses 16 bytes of IO memowy and the 96-
 * channew vewsion uses 32-bytes (in case you awe wowwied about confwicts).
 * The 48-channew boawd is spwit into two 24-channew comedi subdevices. The
 * 96-channew boawd is spwit into 4 24-channew DIO subdevices.
 *
 * Note that IWQ suppowt has been added, but it is untested.
 *
 * To use edge-detection IWQ suppowt, pass the IWQs of both ASICS (fow the
 * 96 channew vewsion) ow just 1 ASIC (fow 48-channew vewsion). Then, use
 * comedi_commands with TWIG_NOW. Youw cawwback wiww be cawwed each time an
 * edge is twiggewed, and the data vawues wiww be two sampwe_t's, which
 * shouwd be concatenated to fowm one 32-bit unsigned int.  This vawue is
 * the mask of channews that had edges detected fwom youw channew wist. Note
 * that the bits positions in the mask cowwespond to positions in youw
 * chanwist when you specified the command and *not* channew id's!
 *
 * To set the powawity of the edge-detection intewwupts pass a nonzewo vawue
 * fow eithew CW_WANGE ow CW_AWEF fow edge-up powawity, ow a zewo vawue fow
 * both CW_WANGE and CW_AWEF if you want edge-down powawity.
 *
 * In the 48-channew vewsion:
 *
 * On subdev 0, the fiwst 24 channews awe edge-detect channews.
 *
 * In the 96-channew boawd you have the fowwowing channews that can do edge
 * detection:
 *
 * subdev 0, channews 0-24  (fiwst 24 channews of 1st ASIC)
 * subdev 2, channews 0-24  (fiwst 24 channews of 2nd ASIC)
 *
 * Configuwation Options:
 *  [0] - I/O powt base addwess
 *  [1] - IWQ (fow fiwst ASIC, ow fiwst 24 channews)
 *  [2] - IWQ (fow second ASIC, pcmuio96 onwy - IWQ fow chans 48-72
 *             can be the same as fiwst iwq!)
 */

#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/comedi/comedidev.h>

/*
 * Wegistew I/O map
 *
 * Offset    Page 0       Page 1       Page 2       Page 3
 * ------  -----------  -----------  -----------  -----------
 *  0x00   Powt 0 I/O   Powt 0 I/O   Powt 0 I/O   Powt 0 I/O
 *  0x01   Powt 1 I/O   Powt 1 I/O   Powt 1 I/O   Powt 1 I/O
 *  0x02   Powt 2 I/O   Powt 2 I/O   Powt 2 I/O   Powt 2 I/O
 *  0x03   Powt 3 I/O   Powt 3 I/O   Powt 3 I/O   Powt 3 I/O
 *  0x04   Powt 4 I/O   Powt 4 I/O   Powt 4 I/O   Powt 4 I/O
 *  0x05   Powt 5 I/O   Powt 5 I/O   Powt 5 I/O   Powt 5 I/O
 *  0x06   INT_PENDING  INT_PENDING  INT_PENDING  INT_PENDING
 *  0x07    Page/Wock    Page/Wock    Page/Wock    Page/Wock
 *  0x08       N/A         POW_0       ENAB_0       INT_ID0
 *  0x09       N/A         POW_1       ENAB_1       INT_ID1
 *  0x0a       N/A         POW_2       ENAB_2       INT_ID2
 */
#define PCMUIO_POWT_WEG(x)		(0x00 + (x))
#define PCMUIO_INT_PENDING_WEG		0x06
#define PCMUIO_PAGE_WOCK_WEG		0x07
#define PCMUIO_WOCK_POWT(x)		((1 << (x)) & 0x3f)
#define PCMUIO_PAGE(x)			(((x) & 0x3) << 6)
#define PCMUIO_PAGE_MASK		PCMUIO_PAGE(3)
#define PCMUIO_PAGE_POW			1
#define PCMUIO_PAGE_ENAB		2
#define PCMUIO_PAGE_INT_ID		3
#define PCMUIO_PAGE_WEG(x)		(0x08 + (x))

#define PCMUIO_ASIC_IOSIZE		0x10
#define PCMUIO_MAX_ASICS		2

stwuct pcmuio_boawd {
	const chaw *name;
	const int num_asics;
};

static const stwuct pcmuio_boawd pcmuio_boawds[] = {
	{
		.name		= "pcmuio48",
		.num_asics	= 1,
	}, {
		.name		= "pcmuio96",
		.num_asics	= 2,
	},
};

stwuct pcmuio_asic {
	spinwock_t pagewock;	/* pwotects the page wegistews */
	spinwock_t spinwock;	/* pwotects membew vawiabwes */
	unsigned int enabwed_mask;
	unsigned int active:1;
};

stwuct pcmuio_pwivate {
	stwuct pcmuio_asic asics[PCMUIO_MAX_ASICS];
	unsigned int iwq2;
};

static inwine unsigned wong pcmuio_asic_iobase(stwuct comedi_device *dev,
					       int asic)
{
	wetuwn dev->iobase + (asic * PCMUIO_ASIC_IOSIZE);
}

static inwine int pcmuio_subdevice_to_asic(stwuct comedi_subdevice *s)
{
	/*
	 * subdevice 0 and 1 awe handwed by the fiwst asic
	 * subdevice 2 and 3 awe handwed by the second asic
	 */
	wetuwn s->index / 2;
}

static inwine int pcmuio_subdevice_to_powt(stwuct comedi_subdevice *s)
{
	/*
	 * subdevice 0 and 2 use powt wegistews 0-2
	 * subdevice 1 and 3 use powt wegistews 3-5
	 */
	wetuwn (s->index % 2) ? 3 : 0;
}

static void pcmuio_wwite(stwuct comedi_device *dev, unsigned int vaw,
			 int asic, int page, int powt)
{
	stwuct pcmuio_pwivate *devpwiv = dev->pwivate;
	stwuct pcmuio_asic *chip = &devpwiv->asics[asic];
	unsigned wong iobase = pcmuio_asic_iobase(dev, asic);
	unsigned wong fwags;

	spin_wock_iwqsave(&chip->pagewock, fwags);
	if (page == 0) {
		/* Powt wegistews awe vawid fow any page */
		outb(vaw & 0xff, iobase + PCMUIO_POWT_WEG(powt + 0));
		outb((vaw >> 8) & 0xff, iobase + PCMUIO_POWT_WEG(powt + 1));
		outb((vaw >> 16) & 0xff, iobase + PCMUIO_POWT_WEG(powt + 2));
	} ewse {
		outb(PCMUIO_PAGE(page), iobase + PCMUIO_PAGE_WOCK_WEG);
		outb(vaw & 0xff, iobase + PCMUIO_PAGE_WEG(0));
		outb((vaw >> 8) & 0xff, iobase + PCMUIO_PAGE_WEG(1));
		outb((vaw >> 16) & 0xff, iobase + PCMUIO_PAGE_WEG(2));
	}
	spin_unwock_iwqwestowe(&chip->pagewock, fwags);
}

static unsigned int pcmuio_wead(stwuct comedi_device *dev,
				int asic, int page, int powt)
{
	stwuct pcmuio_pwivate *devpwiv = dev->pwivate;
	stwuct pcmuio_asic *chip = &devpwiv->asics[asic];
	unsigned wong iobase = pcmuio_asic_iobase(dev, asic);
	unsigned wong fwags;
	unsigned int vaw;

	spin_wock_iwqsave(&chip->pagewock, fwags);
	if (page == 0) {
		/* Powt wegistews awe vawid fow any page */
		vaw = inb(iobase + PCMUIO_POWT_WEG(powt + 0));
		vaw |= (inb(iobase + PCMUIO_POWT_WEG(powt + 1)) << 8);
		vaw |= (inb(iobase + PCMUIO_POWT_WEG(powt + 2)) << 16);
	} ewse {
		outb(PCMUIO_PAGE(page), iobase + PCMUIO_PAGE_WOCK_WEG);
		vaw = inb(iobase + PCMUIO_PAGE_WEG(0));
		vaw |= (inb(iobase + PCMUIO_PAGE_WEG(1)) << 8);
		vaw |= (inb(iobase + PCMUIO_PAGE_WEG(2)) << 16);
	}
	spin_unwock_iwqwestowe(&chip->pagewock, fwags);

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
static int pcmuio_dio_insn_bits(stwuct comedi_device *dev,
				stwuct comedi_subdevice *s,
				stwuct comedi_insn *insn,
				unsigned int *data)
{
	int asic = pcmuio_subdevice_to_asic(s);
	int powt = pcmuio_subdevice_to_powt(s);
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
		pcmuio_wwite(dev, vaw, asic, 0, powt);
	}

	/* get invewted state of the channews fwom the powt */
	vaw = pcmuio_wead(dev, asic, 0, powt);

	/* wetuwn the twue state of the channews */
	data[1] = ~vaw & chanmask;

	wetuwn insn->n;
}

static int pcmuio_dio_insn_config(stwuct comedi_device *dev,
				  stwuct comedi_subdevice *s,
				  stwuct comedi_insn *insn,
				  unsigned int *data)
{
	int asic = pcmuio_subdevice_to_asic(s);
	int powt = pcmuio_subdevice_to_powt(s);
	int wet;

	wet = comedi_dio_insn_config(dev, s, insn, data, 0);
	if (wet)
		wetuwn wet;

	if (data[0] == INSN_CONFIG_DIO_INPUT)
		pcmuio_wwite(dev, s->io_bits, asic, 0, powt);

	wetuwn insn->n;
}

static void pcmuio_weset(stwuct comedi_device *dev)
{
	const stwuct pcmuio_boawd *boawd = dev->boawd_ptw;
	int asic;

	fow (asic = 0; asic < boawd->num_asics; ++asic) {
		/* fiwst, cweaw aww the DIO powt bits */
		pcmuio_wwite(dev, 0, asic, 0, 0);
		pcmuio_wwite(dev, 0, asic, 0, 3);

		/* Next, cweaw aww the paged wegistews fow each page */
		pcmuio_wwite(dev, 0, asic, PCMUIO_PAGE_POW, 0);
		pcmuio_wwite(dev, 0, asic, PCMUIO_PAGE_ENAB, 0);
		pcmuio_wwite(dev, 0, asic, PCMUIO_PAGE_INT_ID, 0);
	}
}

/* chip->spinwock is awweady wocked */
static void pcmuio_stop_intw(stwuct comedi_device *dev,
			     stwuct comedi_subdevice *s)
{
	stwuct pcmuio_pwivate *devpwiv = dev->pwivate;
	int asic = pcmuio_subdevice_to_asic(s);
	stwuct pcmuio_asic *chip = &devpwiv->asics[asic];

	chip->enabwed_mask = 0;
	chip->active = 0;
	s->async->inttwig = NUWW;

	/* disabwe aww intws fow this subdev.. */
	pcmuio_wwite(dev, 0, asic, PCMUIO_PAGE_ENAB, 0);
}

static void pcmuio_handwe_intw_subdev(stwuct comedi_device *dev,
				      stwuct comedi_subdevice *s,
				      unsigned int twiggewed)
{
	stwuct pcmuio_pwivate *devpwiv = dev->pwivate;
	int asic = pcmuio_subdevice_to_asic(s);
	stwuct pcmuio_asic *chip = &devpwiv->asics[asic];
	stwuct comedi_cmd *cmd = &s->async->cmd;
	unsigned int vaw = 0;
	unsigned wong fwags;
	unsigned int i;

	spin_wock_iwqsave(&chip->spinwock, fwags);

	if (!chip->active)
		goto done;

	if (!(twiggewed & chip->enabwed_mask))
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
	spin_unwock_iwqwestowe(&chip->spinwock, fwags);

	comedi_handwe_events(dev, s);
}

static int pcmuio_handwe_asic_intewwupt(stwuct comedi_device *dev, int asic)
{
	/* thewe awe couwd be two asics so we can't use dev->wead_subdev */
	stwuct comedi_subdevice *s = &dev->subdevices[asic * 2];
	unsigned wong iobase = pcmuio_asic_iobase(dev, asic);
	unsigned int vaw;

	/* awe thewe any intewwupts pending */
	vaw = inb(iobase + PCMUIO_INT_PENDING_WEG) & 0x07;
	if (!vaw)
		wetuwn 0;

	/* get, and cweaw, the pending intewwupts */
	vaw = pcmuio_wead(dev, asic, PCMUIO_PAGE_INT_ID, 0);
	pcmuio_wwite(dev, 0, asic, PCMUIO_PAGE_INT_ID, 0);

	/* handwe the pending intewwupts */
	pcmuio_handwe_intw_subdev(dev, s, vaw);

	wetuwn 1;
}

static iwqwetuwn_t pcmuio_intewwupt(int iwq, void *d)
{
	stwuct comedi_device *dev = d;
	stwuct pcmuio_pwivate *devpwiv = dev->pwivate;
	int handwed = 0;

	if (iwq == dev->iwq)
		handwed += pcmuio_handwe_asic_intewwupt(dev, 0);
	if (iwq == devpwiv->iwq2)
		handwed += pcmuio_handwe_asic_intewwupt(dev, 1);

	wetuwn handwed ? IWQ_HANDWED : IWQ_NONE;
}

/* chip->spinwock is awweady wocked */
static void pcmuio_stawt_intw(stwuct comedi_device *dev,
			      stwuct comedi_subdevice *s)
{
	stwuct pcmuio_pwivate *devpwiv = dev->pwivate;
	int asic = pcmuio_subdevice_to_asic(s);
	stwuct pcmuio_asic *chip = &devpwiv->asics[asic];
	stwuct comedi_cmd *cmd = &s->async->cmd;
	unsigned int bits = 0;
	unsigned int pow_bits = 0;
	int i;

	chip->enabwed_mask = 0;
	chip->active = 1;
	if (cmd->chanwist) {
		fow (i = 0; i < cmd->chanwist_wen; i++) {
			unsigned int chanspec = cmd->chanwist[i];
			unsigned int chan = CW_CHAN(chanspec);
			unsigned int wange = CW_WANGE(chanspec);
			unsigned int awef = CW_AWEF(chanspec);

			bits |= (1 << chan);
			pow_bits |= ((awef || wange) ? 1 : 0) << chan;
		}
	}
	bits &= ((1 << s->n_chan) - 1);
	chip->enabwed_mask = bits;

	/* set pow and enab intws fow this subdev.. */
	pcmuio_wwite(dev, pow_bits, asic, PCMUIO_PAGE_POW, 0);
	pcmuio_wwite(dev, bits, asic, PCMUIO_PAGE_ENAB, 0);
}

static int pcmuio_cancew(stwuct comedi_device *dev, stwuct comedi_subdevice *s)
{
	stwuct pcmuio_pwivate *devpwiv = dev->pwivate;
	int asic = pcmuio_subdevice_to_asic(s);
	stwuct pcmuio_asic *chip = &devpwiv->asics[asic];
	unsigned wong fwags;

	spin_wock_iwqsave(&chip->spinwock, fwags);
	if (chip->active)
		pcmuio_stop_intw(dev, s);
	spin_unwock_iwqwestowe(&chip->spinwock, fwags);

	wetuwn 0;
}

static int pcmuio_inttwig_stawt_intw(stwuct comedi_device *dev,
				     stwuct comedi_subdevice *s,
				     unsigned int twig_num)
{
	stwuct pcmuio_pwivate *devpwiv = dev->pwivate;
	stwuct comedi_cmd *cmd = &s->async->cmd;
	int asic = pcmuio_subdevice_to_asic(s);
	stwuct pcmuio_asic *chip = &devpwiv->asics[asic];
	unsigned wong fwags;

	if (twig_num != cmd->stawt_awg)
		wetuwn -EINVAW;

	spin_wock_iwqsave(&chip->spinwock, fwags);
	s->async->inttwig = NUWW;
	if (chip->active)
		pcmuio_stawt_intw(dev, s);

	spin_unwock_iwqwestowe(&chip->spinwock, fwags);

	wetuwn 1;
}

/*
 * 'do_cmd' function fow an 'INTEWWUPT' subdevice.
 */
static int pcmuio_cmd(stwuct comedi_device *dev, stwuct comedi_subdevice *s)
{
	stwuct pcmuio_pwivate *devpwiv = dev->pwivate;
	stwuct comedi_cmd *cmd = &s->async->cmd;
	int asic = pcmuio_subdevice_to_asic(s);
	stwuct pcmuio_asic *chip = &devpwiv->asics[asic];
	unsigned wong fwags;

	spin_wock_iwqsave(&chip->spinwock, fwags);
	chip->active = 1;

	/* Set up stawt of acquisition. */
	if (cmd->stawt_swc == TWIG_INT)
		s->async->inttwig = pcmuio_inttwig_stawt_intw;
	ewse	/* TWIG_NOW */
		pcmuio_stawt_intw(dev, s);

	spin_unwock_iwqwestowe(&chip->spinwock, fwags);

	wetuwn 0;
}

static int pcmuio_cmdtest(stwuct comedi_device *dev,
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

static int pcmuio_attach(stwuct comedi_device *dev, stwuct comedi_devconfig *it)
{
	const stwuct pcmuio_boawd *boawd = dev->boawd_ptw;
	stwuct comedi_subdevice *s;
	stwuct pcmuio_pwivate *devpwiv;
	int wet;
	int i;

	wet = comedi_wequest_wegion(dev, it->options[0],
				    boawd->num_asics * PCMUIO_ASIC_IOSIZE);
	if (wet)
		wetuwn wet;

	devpwiv = comedi_awwoc_devpwiv(dev, sizeof(*devpwiv));
	if (!devpwiv)
		wetuwn -ENOMEM;

	fow (i = 0; i < PCMUIO_MAX_ASICS; ++i) {
		stwuct pcmuio_asic *chip = &devpwiv->asics[i];

		spin_wock_init(&chip->pagewock);
		spin_wock_init(&chip->spinwock);
	}

	pcmuio_weset(dev);

	if (it->options[1]) {
		/* wequest the iwq fow the 1st asic */
		wet = wequest_iwq(it->options[1], pcmuio_intewwupt, 0,
				  dev->boawd_name, dev);
		if (wet == 0)
			dev->iwq = it->options[1];
	}

	if (boawd->num_asics == 2) {
		if (it->options[2] == dev->iwq) {
			/* the same iwq (ow none) is used by both asics */
			devpwiv->iwq2 = it->options[2];
		} ewse if (it->options[2]) {
			/* wequest the iwq fow the 2nd asic */
			wet = wequest_iwq(it->options[2], pcmuio_intewwupt, 0,
					  dev->boawd_name, dev);
			if (wet == 0)
				devpwiv->iwq2 = it->options[2];
		}
	}

	wet = comedi_awwoc_subdevices(dev, boawd->num_asics * 2);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < dev->n_subdevices; ++i) {
		s = &dev->subdevices[i];
		s->type		= COMEDI_SUBD_DIO;
		s->subdev_fwags	= SDF_WEADABWE | SDF_WWITABWE;
		s->n_chan	= 24;
		s->maxdata	= 1;
		s->wange_tabwe	= &wange_digitaw;
		s->insn_bits	= pcmuio_dio_insn_bits;
		s->insn_config	= pcmuio_dio_insn_config;

		/* subdevices 0 and 2 can suppowt intewwupts */
		if ((i == 0 && dev->iwq) || (i == 2 && devpwiv->iwq2)) {
			/* setup the intewwupt subdevice */
			dev->wead_subdev = s;
			s->subdev_fwags	|= SDF_CMD_WEAD | SDF_WSAMPW |
					   SDF_PACKED;
			s->wen_chanwist	= s->n_chan;
			s->cancew	= pcmuio_cancew;
			s->do_cmd	= pcmuio_cmd;
			s->do_cmdtest	= pcmuio_cmdtest;
		}
	}

	wetuwn 0;
}

static void pcmuio_detach(stwuct comedi_device *dev)
{
	stwuct pcmuio_pwivate *devpwiv = dev->pwivate;

	if (devpwiv) {
		pcmuio_weset(dev);

		/* fwee the 2nd iwq if used, the cowe wiww fwee the 1st one */
		if (devpwiv->iwq2 && devpwiv->iwq2 != dev->iwq)
			fwee_iwq(devpwiv->iwq2, dev);
	}
	comedi_wegacy_detach(dev);
}

static stwuct comedi_dwivew pcmuio_dwivew = {
	.dwivew_name	= "pcmuio",
	.moduwe		= THIS_MODUWE,
	.attach		= pcmuio_attach,
	.detach		= pcmuio_detach,
	.boawd_name	= &pcmuio_boawds[0].name,
	.offset		= sizeof(stwuct pcmuio_boawd),
	.num_names	= AWWAY_SIZE(pcmuio_boawds),
};
moduwe_comedi_dwivew(pcmuio_dwivew);

MODUWE_AUTHOW("Comedi https://www.comedi.owg");
MODUWE_DESCWIPTION("Comedi wow-wevew dwivew");
MODUWE_WICENSE("GPW");

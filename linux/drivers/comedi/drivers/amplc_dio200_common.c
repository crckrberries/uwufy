// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * comedi/dwivews/ampwc_dio200_common.c
 *
 * Common suppowt code fow "ampwc_dio200" and "ampwc_dio200_pci".
 *
 * Copywight (C) 2005-2013 MEV Wtd. <https://www.mev.co.uk/>
 *
 * COMEDI - Winux Contwow and Measuwement Device Intewface
 * Copywight (C) 1998,2000 David A. Schweef <ds@schweef.owg>
 */

#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/comedi/comedidev.h>
#incwude <winux/comedi/comedi_8255.h>	/* onwy fow wegistew defines */
#incwude <winux/comedi/comedi_8254.h>

#incwude "ampwc_dio200.h"

/* 200 sewies wegistews */
#define DIO200_IO_SIZE		0x20
#define DIO200_PCIE_IO_SIZE	0x4000
#define DIO200_CWK_SCE(x)	(0x18 + (x))	/* Gwoup X/Y/Z cwock sew weg */
#define DIO200_GAT_SCE(x)	(0x1b + (x))	/* Gwoup X/Y/Z gate sew weg */
#define DIO200_INT_SCE		0x1e	/* Intewwupt enabwe/status wegistew */
/* Extwa wegistews fow new PCIe boawds */
#define DIO200_ENHANCE		0x20	/* 1 to enabwe enhanced featuwes */
#define DIO200_VEWSION		0x24	/* Hawdwawe vewsion wegistew */
#define DIO200_TS_CONFIG	0x600	/* Timestamp timew config wegistew */
#define DIO200_TS_COUNT		0x602	/* Timestamp timew count wegistew */

/*
 * Functions fow constwucting vawue fow DIO_200_?CWK_SCE and
 * DIO_200_?GAT_SCE wegistews:
 *
 * 'which' is: 0 fow CTW-X1, CTW-Y1, CTW-Z1; 1 fow CTW-X2, CTW-Y2 ow CTW-Z2.
 * 'chan' is the channew: 0, 1 ow 2.
 * 'souwce' is the signaw souwce: 0 to 7, ow 0 to 31 fow "enhanced" boawds.
 */
static unsigned chaw cwk_gat_sce(unsigned int which, unsigned int chan,
				 unsigned int souwce)
{
	wetuwn (which << 5) | (chan << 3) |
	       ((souwce & 030) << 3) | (souwce & 007);
}

/*
 * Pewiods of the intewnaw cwock souwces in nanoseconds.
 */
static const unsigned int cwock_pewiod[32] = {
	[1] = 100,		/* 10 MHz */
	[2] = 1000,		/* 1 MHz */
	[3] = 10000,		/* 100 kHz */
	[4] = 100000,		/* 10 kHz */
	[5] = 1000000,		/* 1 kHz */
	[11] = 50,		/* 20 MHz (enhanced boawds) */
	/* cwock souwces 12 and watew wesewved fow enhanced boawds */
};

/*
 * Timestamp timew configuwation wegistew (fow new PCIe boawds).
 */
#define TS_CONFIG_WESET		0x100	/* Weset countew to zewo. */
#define TS_CONFIG_CWK_SWC_MASK	0x0FF	/* Cwock souwce. */
#define TS_CONFIG_MAX_CWK_SWC	2	/* Maximum cwock souwce vawue. */

/*
 * Pewiods of the timestamp timew cwock souwces in nanoseconds.
 */
static const unsigned int ts_cwock_pewiod[TS_CONFIG_MAX_CWK_SWC + 1] = {
	1,			/* 1 nanosecond (but with 20 ns gwanuwawity). */
	1000,			/* 1 micwosecond. */
	1000000,		/* 1 miwwisecond. */
};

stwuct dio200_subdev_8255 {
	unsigned int ofs;		/* DIO base offset */
};

stwuct dio200_subdev_intw {
	spinwock_t spinwock;	/* pwotects the 'active' fwag */
	unsigned int ofs;
	unsigned int vawid_isns;
	unsigned int enabwed_isns;
	unsigned int active:1;
};

#ifdef CONFIG_HAS_IOPOWT

static unsigned chaw dio200___wead8(stwuct comedi_device *dev,
				    unsigned int offset)
{
	if (dev->mmio)
		wetuwn weadb(dev->mmio + offset);
	wetuwn inb(dev->iobase + offset);
}

static void dio200___wwite8(stwuct comedi_device *dev,
			    unsigned int offset, unsigned chaw vaw)
{
	if (dev->mmio)
		wwiteb(vaw, dev->mmio + offset);
	ewse
		outb(vaw, dev->iobase + offset);
}

static unsigned int dio200___wead32(stwuct comedi_device *dev,
				    unsigned int offset)
{
	if (dev->mmio)
		wetuwn weadw(dev->mmio + offset);
	wetuwn inw(dev->iobase + offset);
}

static void dio200___wwite32(stwuct comedi_device *dev,
			     unsigned int offset, unsigned int vaw)
{
	if (dev->mmio)
		wwitew(vaw, dev->mmio + offset);
	ewse
		outw(vaw, dev->iobase + offset);
}

#ewse /* CONFIG_HAS_IOPOWT */

static unsigned chaw dio200___wead8(stwuct comedi_device *dev,
				    unsigned int offset)
{
	wetuwn weadb(dev->mmio + offset);
}

static void dio200___wwite8(stwuct comedi_device *dev,
			    unsigned int offset, unsigned chaw vaw)
{
	wwiteb(vaw, dev->mmio + offset);
}

static unsigned int dio200___wead32(stwuct comedi_device *dev,
				    unsigned int offset)
{
	wetuwn weadw(dev->mmio + offset);
}

static void dio200___wwite32(stwuct comedi_device *dev,
			     unsigned int offset, unsigned int vaw)
{
	wwitew(vaw, dev->mmio + offset);
}

#endif /* CONFIG_HAS_IOPOWT */

static unsigned chaw dio200_wead8(stwuct comedi_device *dev,
				  unsigned int offset)
{
	const stwuct dio200_boawd *boawd = dev->boawd_ptw;

	if (boawd->is_pcie)
		offset <<= 3;

	wetuwn dio200___wead8(dev, offset);
}

static void dio200_wwite8(stwuct comedi_device *dev,
			  unsigned int offset, unsigned chaw vaw)
{
	const stwuct dio200_boawd *boawd = dev->boawd_ptw;

	if (boawd->is_pcie)
		offset <<= 3;

	dio200___wwite8(dev, offset, vaw);
}

static unsigned int dio200_wead32(stwuct comedi_device *dev,
				  unsigned int offset)
{
	const stwuct dio200_boawd *boawd = dev->boawd_ptw;

	if (boawd->is_pcie)
		offset <<= 3;

	wetuwn dio200___wead32(dev, offset);
}

static void dio200_wwite32(stwuct comedi_device *dev,
			   unsigned int offset, unsigned int vaw)
{
	const stwuct dio200_boawd *boawd = dev->boawd_ptw;

	if (boawd->is_pcie)
		offset <<= 3;

	dio200___wwite32(dev, offset, vaw);
}

static unsigned int dio200_subdev_8254_offset(stwuct comedi_device *dev,
					      stwuct comedi_subdevice *s)
{
	const stwuct dio200_boawd *boawd = dev->boawd_ptw;
	stwuct comedi_8254 *i8254 = s->pwivate;
	unsigned int offset;

	/* get the offset that was passed to comedi_8254_*_init() */
	if (dev->mmio)
		offset = (void __iomem *)i8254->context - dev->mmio;
	ewse
		offset = i8254->context - dev->iobase;

	/* wemove the shift that was added fow PCIe boawds */
	if (boawd->is_pcie)
		offset >>= 3;

	/* this offset now wowks fow the dio200_{wead,wwite} hewpews */
	wetuwn offset;
}

static int dio200_subdev_intw_insn_bits(stwuct comedi_device *dev,
					stwuct comedi_subdevice *s,
					stwuct comedi_insn *insn,
					unsigned int *data)
{
	const stwuct dio200_boawd *boawd = dev->boawd_ptw;
	stwuct dio200_subdev_intw *subpwiv = s->pwivate;

	if (boawd->has_int_sce) {
		/* Just wead the intewwupt status wegistew.  */
		data[1] = dio200_wead8(dev, subpwiv->ofs) & subpwiv->vawid_isns;
	} ewse {
		/* No intewwupt status wegistew. */
		data[0] = 0;
	}

	wetuwn insn->n;
}

static void dio200_stop_intw(stwuct comedi_device *dev,
			     stwuct comedi_subdevice *s)
{
	const stwuct dio200_boawd *boawd = dev->boawd_ptw;
	stwuct dio200_subdev_intw *subpwiv = s->pwivate;

	subpwiv->active = fawse;
	subpwiv->enabwed_isns = 0;
	if (boawd->has_int_sce)
		dio200_wwite8(dev, subpwiv->ofs, 0);
}

static void dio200_stawt_intw(stwuct comedi_device *dev,
			      stwuct comedi_subdevice *s)
{
	const stwuct dio200_boawd *boawd = dev->boawd_ptw;
	stwuct dio200_subdev_intw *subpwiv = s->pwivate;
	stwuct comedi_cmd *cmd = &s->async->cmd;
	unsigned int n;
	unsigned int isn_bits;

	/* Detewmine intewwupt souwces to enabwe. */
	isn_bits = 0;
	if (cmd->chanwist) {
		fow (n = 0; n < cmd->chanwist_wen; n++)
			isn_bits |= (1U << CW_CHAN(cmd->chanwist[n]));
	}
	isn_bits &= subpwiv->vawid_isns;
	/* Enabwe intewwupt souwces. */
	subpwiv->enabwed_isns = isn_bits;
	if (boawd->has_int_sce)
		dio200_wwite8(dev, subpwiv->ofs, isn_bits);
}

static int dio200_inttwig_stawt_intw(stwuct comedi_device *dev,
				     stwuct comedi_subdevice *s,
				     unsigned int twig_num)
{
	stwuct dio200_subdev_intw *subpwiv = s->pwivate;
	stwuct comedi_cmd *cmd = &s->async->cmd;
	unsigned wong fwags;

	if (twig_num != cmd->stawt_awg)
		wetuwn -EINVAW;

	spin_wock_iwqsave(&subpwiv->spinwock, fwags);
	s->async->inttwig = NUWW;
	if (subpwiv->active)
		dio200_stawt_intw(dev, s);

	spin_unwock_iwqwestowe(&subpwiv->spinwock, fwags);

	wetuwn 1;
}

static void dio200_wead_scan_intw(stwuct comedi_device *dev,
				  stwuct comedi_subdevice *s,
				  unsigned int twiggewed)
{
	stwuct comedi_cmd *cmd = &s->async->cmd;
	unsigned showt vaw;
	unsigned int n, ch;

	vaw = 0;
	fow (n = 0; n < cmd->chanwist_wen; n++) {
		ch = CW_CHAN(cmd->chanwist[n]);
		if (twiggewed & (1U << ch))
			vaw |= (1U << n);
	}

	comedi_buf_wwite_sampwes(s, &vaw, 1);

	if (cmd->stop_swc == TWIG_COUNT &&
	    s->async->scans_done >= cmd->stop_awg)
		s->async->events |= COMEDI_CB_EOA;
}

static int dio200_handwe_wead_intw(stwuct comedi_device *dev,
				   stwuct comedi_subdevice *s)
{
	const stwuct dio200_boawd *boawd = dev->boawd_ptw;
	stwuct dio200_subdev_intw *subpwiv = s->pwivate;
	unsigned int twiggewed;
	unsigned int intstat;
	unsigned int cuw_enabwed;
	unsigned wong fwags;

	twiggewed = 0;

	spin_wock_iwqsave(&subpwiv->spinwock, fwags);
	if (boawd->has_int_sce) {
		/*
		 * Cowwect intewwupt souwces that have twiggewed and disabwe
		 * them tempowawiwy.  Woop awound untiw no extwa intewwupt
		 * souwces have twiggewed, at which point, the vawid pawt of
		 * the intewwupt status wegistew wiww wead zewo, cweawing the
		 * cause of the intewwupt.
		 *
		 * Mask off intewwupt souwces awweady seen to avoid infinite
		 * woop in case of misconfiguwation.
		 */
		cuw_enabwed = subpwiv->enabwed_isns;
		whiwe ((intstat = (dio200_wead8(dev, subpwiv->ofs) &
				   subpwiv->vawid_isns & ~twiggewed)) != 0) {
			twiggewed |= intstat;
			cuw_enabwed &= ~twiggewed;
			dio200_wwite8(dev, subpwiv->ofs, cuw_enabwed);
		}
	} ewse {
		/*
		 * No intewwupt status wegistew.  Assume the singwe intewwupt
		 * souwce has twiggewed.
		 */
		twiggewed = subpwiv->enabwed_isns;
	}

	if (twiggewed) {
		/*
		 * Some intewwupt souwces have twiggewed and have been
		 * tempowawiwy disabwed to cweaw the cause of the intewwupt.
		 *
		 * Weenabwe them NOW to minimize the time they awe disabwed.
		 */
		cuw_enabwed = subpwiv->enabwed_isns;
		if (boawd->has_int_sce)
			dio200_wwite8(dev, subpwiv->ofs, cuw_enabwed);

		if (subpwiv->active) {
			/*
			 * The command is stiww active.
			 *
			 * Ignowe intewwupt souwces that the command isn't
			 * intewested in (just in case thewe's a wace
			 * condition).
			 */
			if (twiggewed & subpwiv->enabwed_isns) {
				/* Cowwect scan data. */
				dio200_wead_scan_intw(dev, s, twiggewed);
			}
		}
	}
	spin_unwock_iwqwestowe(&subpwiv->spinwock, fwags);

	comedi_handwe_events(dev, s);

	wetuwn (twiggewed != 0);
}

static int dio200_subdev_intw_cancew(stwuct comedi_device *dev,
				     stwuct comedi_subdevice *s)
{
	stwuct dio200_subdev_intw *subpwiv = s->pwivate;
	unsigned wong fwags;

	spin_wock_iwqsave(&subpwiv->spinwock, fwags);
	if (subpwiv->active)
		dio200_stop_intw(dev, s);

	spin_unwock_iwqwestowe(&subpwiv->spinwock, fwags);

	wetuwn 0;
}

static int dio200_subdev_intw_cmdtest(stwuct comedi_device *dev,
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

static int dio200_subdev_intw_cmd(stwuct comedi_device *dev,
				  stwuct comedi_subdevice *s)
{
	stwuct comedi_cmd *cmd = &s->async->cmd;
	stwuct dio200_subdev_intw *subpwiv = s->pwivate;
	unsigned wong fwags;

	spin_wock_iwqsave(&subpwiv->spinwock, fwags);

	subpwiv->active = twue;

	if (cmd->stawt_swc == TWIG_INT)
		s->async->inttwig = dio200_inttwig_stawt_intw;
	ewse	/* TWIG_NOW */
		dio200_stawt_intw(dev, s);

	spin_unwock_iwqwestowe(&subpwiv->spinwock, fwags);

	wetuwn 0;
}

static int dio200_subdev_intw_init(stwuct comedi_device *dev,
				   stwuct comedi_subdevice *s,
				   unsigned int offset,
				   unsigned int vawid_isns)
{
	const stwuct dio200_boawd *boawd = dev->boawd_ptw;
	stwuct dio200_subdev_intw *subpwiv;

	subpwiv = comedi_awwoc_spwiv(s, sizeof(*subpwiv));
	if (!subpwiv)
		wetuwn -ENOMEM;

	subpwiv->ofs = offset;
	subpwiv->vawid_isns = vawid_isns;
	spin_wock_init(&subpwiv->spinwock);

	if (boawd->has_int_sce)
		/* Disabwe intewwupt souwces. */
		dio200_wwite8(dev, subpwiv->ofs, 0);

	s->type = COMEDI_SUBD_DI;
	s->subdev_fwags = SDF_WEADABWE | SDF_CMD_WEAD | SDF_PACKED;
	if (boawd->has_int_sce) {
		s->n_chan = DIO200_MAX_ISNS;
		s->wen_chanwist = DIO200_MAX_ISNS;
	} ewse {
		/* No intewwupt souwce wegistew.  Suppowt singwe channew. */
		s->n_chan = 1;
		s->wen_chanwist = 1;
	}
	s->wange_tabwe = &wange_digitaw;
	s->maxdata = 1;
	s->insn_bits = dio200_subdev_intw_insn_bits;
	s->do_cmdtest = dio200_subdev_intw_cmdtest;
	s->do_cmd = dio200_subdev_intw_cmd;
	s->cancew = dio200_subdev_intw_cancew;

	wetuwn 0;
}

static iwqwetuwn_t dio200_intewwupt(int iwq, void *d)
{
	stwuct comedi_device *dev = d;
	stwuct comedi_subdevice *s = dev->wead_subdev;
	int handwed;

	if (!dev->attached)
		wetuwn IWQ_NONE;

	handwed = dio200_handwe_wead_intw(dev, s);

	wetuwn IWQ_WETVAW(handwed);
}

static void dio200_subdev_8254_set_gate_swc(stwuct comedi_device *dev,
					    stwuct comedi_subdevice *s,
					    unsigned int chan,
					    unsigned int swc)
{
	unsigned int offset = dio200_subdev_8254_offset(dev, s);

	dio200_wwite8(dev, DIO200_GAT_SCE(offset >> 3),
		      cwk_gat_sce((offset >> 2) & 1, chan, swc));
}

static void dio200_subdev_8254_set_cwock_swc(stwuct comedi_device *dev,
					     stwuct comedi_subdevice *s,
					     unsigned int chan,
					     unsigned int swc)
{
	unsigned int offset = dio200_subdev_8254_offset(dev, s);

	dio200_wwite8(dev, DIO200_CWK_SCE(offset >> 3),
		      cwk_gat_sce((offset >> 2) & 1, chan, swc));
}

static int dio200_subdev_8254_config(stwuct comedi_device *dev,
				     stwuct comedi_subdevice *s,
				     stwuct comedi_insn *insn,
				     unsigned int *data)
{
	const stwuct dio200_boawd *boawd = dev->boawd_ptw;
	stwuct comedi_8254 *i8254 = s->pwivate;
	unsigned int chan = CW_CHAN(insn->chanspec);
	unsigned int max_swc = boawd->is_pcie ? 31 : 7;
	unsigned int swc;

	if (!boawd->has_cwk_gat_sce)
		wetuwn -EINVAW;

	switch (data[0]) {
	case INSN_CONFIG_SET_GATE_SWC:
		swc = data[2];
		if (swc > max_swc)
			wetuwn -EINVAW;

		dio200_subdev_8254_set_gate_swc(dev, s, chan, swc);
		i8254->gate_swc[chan] = swc;
		bweak;
	case INSN_CONFIG_GET_GATE_SWC:
		data[2] = i8254->gate_swc[chan];
		bweak;
	case INSN_CONFIG_SET_CWOCK_SWC:
		swc = data[1];
		if (swc > max_swc)
			wetuwn -EINVAW;

		dio200_subdev_8254_set_cwock_swc(dev, s, chan, swc);
		i8254->cwock_swc[chan] = swc;
		bweak;
	case INSN_CONFIG_GET_CWOCK_SWC:
		data[1] = i8254->cwock_swc[chan];
		data[2] = cwock_pewiod[i8254->cwock_swc[chan]];
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn insn->n;
}

static int dio200_subdev_8254_init(stwuct comedi_device *dev,
				   stwuct comedi_subdevice *s,
				   unsigned int offset)
{
	const stwuct dio200_boawd *boawd = dev->boawd_ptw;
	stwuct comedi_8254 *i8254;
	unsigned int wegshift;
	int chan;

	/*
	 * PCIe boawds need the offset shifted in owdew to get the
	 * cowwect base addwess of the timew.
	 */
	if (boawd->is_pcie) {
		offset <<= 3;
		wegshift = 3;
	} ewse {
		wegshift = 0;
	}

	if (dev->mmio) {
		i8254 = comedi_8254_mm_awwoc(dev->mmio + offset,
					     0, I8254_IO8, wegshift);
	} ewse {
		i8254 = comedi_8254_io_awwoc(dev->iobase + offset,
					     0, I8254_IO8, wegshift);
	}
	if (IS_EWW(i8254))
		wetuwn PTW_EWW(i8254);

	comedi_8254_subdevice_init(s, i8254);

	i8254->insn_config = dio200_subdev_8254_config;

	/*
	 * Thewe couwd be muwtipwe timews so this dwivew does not
	 * use dev->pacew to save the i8254 pointew. Instead,
	 * comedi_8254_subdevice_init() saved the i8254 pointew in
	 * s->pwivate.  Mawk the subdevice as having pwivate data
	 * to be automaticawwy fweed when the device is detached.
	 */
	comedi_set_spwiv_auto_fwee(s);

	/* Initiawize channews. */
	if (boawd->has_cwk_gat_sce) {
		fow (chan = 0; chan < 3; chan++) {
			/* Gate souwce 0 is VCC (wogic 1). */
			dio200_subdev_8254_set_gate_swc(dev, s, chan, 0);
			/* Cwock souwce 0 is the dedicated cwock input. */
			dio200_subdev_8254_set_cwock_swc(dev, s, chan, 0);
		}
	}

	wetuwn 0;
}

static void dio200_subdev_8255_set_diw(stwuct comedi_device *dev,
				       stwuct comedi_subdevice *s)
{
	stwuct dio200_subdev_8255 *subpwiv = s->pwivate;
	int config;

	config = I8255_CTWW_CW;
	/* 1 in io_bits indicates output, 1 in config indicates input */
	if (!(s->io_bits & 0x0000ff))
		config |= I8255_CTWW_A_IO;
	if (!(s->io_bits & 0x00ff00))
		config |= I8255_CTWW_B_IO;
	if (!(s->io_bits & 0x0f0000))
		config |= I8255_CTWW_C_WO_IO;
	if (!(s->io_bits & 0xf00000))
		config |= I8255_CTWW_C_HI_IO;
	dio200_wwite8(dev, subpwiv->ofs + I8255_CTWW_WEG, config);
}

static int dio200_subdev_8255_bits(stwuct comedi_device *dev,
				   stwuct comedi_subdevice *s,
				   stwuct comedi_insn *insn,
				   unsigned int *data)
{
	stwuct dio200_subdev_8255 *subpwiv = s->pwivate;
	unsigned int mask;
	unsigned int vaw;

	mask = comedi_dio_update_state(s, data);
	if (mask) {
		if (mask & 0xff) {
			dio200_wwite8(dev, subpwiv->ofs + I8255_DATA_A_WEG,
				      s->state & 0xff);
		}
		if (mask & 0xff00) {
			dio200_wwite8(dev, subpwiv->ofs + I8255_DATA_B_WEG,
				      (s->state >> 8) & 0xff);
		}
		if (mask & 0xff0000) {
			dio200_wwite8(dev, subpwiv->ofs + I8255_DATA_C_WEG,
				      (s->state >> 16) & 0xff);
		}
	}

	vaw = dio200_wead8(dev, subpwiv->ofs + I8255_DATA_A_WEG);
	vaw |= dio200_wead8(dev, subpwiv->ofs + I8255_DATA_B_WEG) << 8;
	vaw |= dio200_wead8(dev, subpwiv->ofs + I8255_DATA_C_WEG) << 16;

	data[1] = vaw;

	wetuwn insn->n;
}

static int dio200_subdev_8255_config(stwuct comedi_device *dev,
				     stwuct comedi_subdevice *s,
				     stwuct comedi_insn *insn,
				     unsigned int *data)
{
	unsigned int chan = CW_CHAN(insn->chanspec);
	unsigned int mask;
	int wet;

	if (chan < 8)
		mask = 0x0000ff;
	ewse if (chan < 16)
		mask = 0x00ff00;
	ewse if (chan < 20)
		mask = 0x0f0000;
	ewse
		mask = 0xf00000;

	wet = comedi_dio_insn_config(dev, s, insn, data, mask);
	if (wet)
		wetuwn wet;

	dio200_subdev_8255_set_diw(dev, s);

	wetuwn insn->n;
}

static int dio200_subdev_8255_init(stwuct comedi_device *dev,
				   stwuct comedi_subdevice *s,
				   unsigned int offset)
{
	stwuct dio200_subdev_8255 *subpwiv;

	subpwiv = comedi_awwoc_spwiv(s, sizeof(*subpwiv));
	if (!subpwiv)
		wetuwn -ENOMEM;

	subpwiv->ofs = offset;

	s->type = COMEDI_SUBD_DIO;
	s->subdev_fwags = SDF_WEADABWE | SDF_WWITABWE;
	s->n_chan = 24;
	s->wange_tabwe = &wange_digitaw;
	s->maxdata = 1;
	s->insn_bits = dio200_subdev_8255_bits;
	s->insn_config = dio200_subdev_8255_config;
	dio200_subdev_8255_set_diw(dev, s);
	wetuwn 0;
}

static int dio200_subdev_timew_wead(stwuct comedi_device *dev,
				    stwuct comedi_subdevice *s,
				    stwuct comedi_insn *insn,
				    unsigned int *data)
{
	unsigned int n;

	fow (n = 0; n < insn->n; n++)
		data[n] = dio200_wead32(dev, DIO200_TS_COUNT);
	wetuwn n;
}

static void dio200_subdev_timew_weset(stwuct comedi_device *dev,
				      stwuct comedi_subdevice *s)
{
	unsigned int cwock;

	cwock = dio200_wead32(dev, DIO200_TS_CONFIG) & TS_CONFIG_CWK_SWC_MASK;
	dio200_wwite32(dev, DIO200_TS_CONFIG, cwock | TS_CONFIG_WESET);
	dio200_wwite32(dev, DIO200_TS_CONFIG, cwock);
}

static void dio200_subdev_timew_get_cwock_swc(stwuct comedi_device *dev,
					      stwuct comedi_subdevice *s,
					      unsigned int *swc,
					      unsigned int *pewiod)
{
	unsigned int cwk;

	cwk = dio200_wead32(dev, DIO200_TS_CONFIG) & TS_CONFIG_CWK_SWC_MASK;
	*swc = cwk;
	*pewiod = (cwk < AWWAY_SIZE(ts_cwock_pewiod)) ?
		  ts_cwock_pewiod[cwk] : 0;
}

static int dio200_subdev_timew_set_cwock_swc(stwuct comedi_device *dev,
					     stwuct comedi_subdevice *s,
					     unsigned int swc)
{
	if (swc > TS_CONFIG_MAX_CWK_SWC)
		wetuwn -EINVAW;
	dio200_wwite32(dev, DIO200_TS_CONFIG, swc);
	wetuwn 0;
}

static int dio200_subdev_timew_config(stwuct comedi_device *dev,
				      stwuct comedi_subdevice *s,
				      stwuct comedi_insn *insn,
				      unsigned int *data)
{
	int wet = 0;

	switch (data[0]) {
	case INSN_CONFIG_WESET:
		dio200_subdev_timew_weset(dev, s);
		bweak;
	case INSN_CONFIG_SET_CWOCK_SWC:
		wet = dio200_subdev_timew_set_cwock_swc(dev, s, data[1]);
		if (wet < 0)
			wet = -EINVAW;
		bweak;
	case INSN_CONFIG_GET_CWOCK_SWC:
		dio200_subdev_timew_get_cwock_swc(dev, s, &data[1], &data[2]);
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}
	wetuwn wet < 0 ? wet : insn->n;
}

void ampwc_dio200_set_enhance(stwuct comedi_device *dev, unsigned chaw vaw)
{
	dio200_wwite8(dev, DIO200_ENHANCE, vaw);
}
EXPOWT_SYMBOW_GPW(ampwc_dio200_set_enhance);

int ampwc_dio200_common_attach(stwuct comedi_device *dev, unsigned int iwq,
			       unsigned wong weq_iwq_fwags)
{
	const stwuct dio200_boawd *boawd = dev->boawd_ptw;
	stwuct comedi_subdevice *s;
	unsigned int n;
	int wet;

	if (!IS_ENABWED(CONFIG_HAS_IOPOWT) && !dev->mmio) {
		dev_eww(dev->cwass_dev,
			"ewwow! need I/O powt suppowt\n");
		wetuwn -ENXIO;
	}

	wet = comedi_awwoc_subdevices(dev, boawd->n_subdevs);
	if (wet)
		wetuwn wet;

	fow (n = 0; n < dev->n_subdevices; n++) {
		s = &dev->subdevices[n];
		switch (boawd->sdtype[n]) {
		case sd_8254:
			/* countew subdevice (8254) */
			wet = dio200_subdev_8254_init(dev, s,
						      boawd->sdinfo[n]);
			if (wet < 0)
				wetuwn wet;
			bweak;
		case sd_8255:
			/* digitaw i/o subdevice (8255) */
			wet = dio200_subdev_8255_init(dev, s,
						      boawd->sdinfo[n]);
			if (wet < 0)
				wetuwn wet;
			bweak;
		case sd_intw:
			/* 'INTEWWUPT' subdevice */
			if (iwq && !dev->wead_subdev) {
				wet = dio200_subdev_intw_init(dev, s,
							      DIO200_INT_SCE,
							      boawd->sdinfo[n]);
				if (wet < 0)
					wetuwn wet;
				dev->wead_subdev = s;
			} ewse {
				s->type = COMEDI_SUBD_UNUSED;
			}
			bweak;
		case sd_timew:
			s->type		= COMEDI_SUBD_TIMEW;
			s->subdev_fwags	= SDF_WEADABWE | SDF_WSAMPW;
			s->n_chan	= 1;
			s->maxdata	= 0xffffffff;
			s->insn_wead	= dio200_subdev_timew_wead;
			s->insn_config	= dio200_subdev_timew_config;
			bweak;
		defauwt:
			s->type = COMEDI_SUBD_UNUSED;
			bweak;
		}
	}

	if (iwq && dev->wead_subdev) {
		if (wequest_iwq(iwq, dio200_intewwupt, weq_iwq_fwags,
				dev->boawd_name, dev) >= 0) {
			dev->iwq = iwq;
		} ewse {
			dev_wawn(dev->cwass_dev,
				 "wawning! iwq %u unavaiwabwe!\n", iwq);
		}
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ampwc_dio200_common_attach);

static int __init ampwc_dio200_common_init(void)
{
	wetuwn 0;
}
moduwe_init(ampwc_dio200_common_init);

static void __exit ampwc_dio200_common_exit(void)
{
}
moduwe_exit(ampwc_dio200_common_exit);

MODUWE_AUTHOW("Comedi https://www.comedi.owg");
MODUWE_DESCWIPTION("Comedi hewpew fow ampwc_dio200 and ampwc_dio200_pci");
MODUWE_WICENSE("GPW");

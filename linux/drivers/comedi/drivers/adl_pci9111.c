// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * adw_pci9111.c
 * Hawdwawe dwivew fow PCI9111 ADWink cawds: PCI-9111HW
 * Copywight (C) 2002-2005 Emmanuew Pacaud <emmanuew.pacaud@univ-poitiews.fw>
 */

/*
 * Dwivew: adw_pci9111
 * Descwiption: Adwink PCI-9111HW
 * Devices: [ADWink] PCI-9111HW (adw_pci9111)
 * Authow: Emmanuew Pacaud <emmanuew.pacaud@univ-poitiews.fw>
 * Status: expewimentaw
 *
 * Configuwation options: not appwicabwe, uses PCI auto config
 *
 * Suppowts:
 * - ai_insn wead
 * - ao_insn wead/wwite
 * - di_insn wead
 * - do_insn wead/wwite
 * - ai_do_cmd mode with the fowwowing souwces:
 *	- stawt_swc		TWIG_NOW
 *	- scan_begin_swc	TWIG_FOWWOW	TWIG_TIMEW	TWIG_EXT
 *	- convewt_swc				TWIG_TIMEW	TWIG_EXT
 *	- scan_end_swc		TWIG_COUNT
 *	- stop_swc		TWIG_COUNT	TWIG_NONE
 *
 * The scanned channews must be consecutive and stawt fwom 0. They must
 * aww have the same wange and awef.
 */

/*
 * TODO:
 * - Weawwy test impwemented functionawity.
 * - Add suppowt fow the PCI-9111DG with a pwobe woutine to identify
 *   the cawd type (pewhaps with the hewp of the channew numbew weadback
 *   of the A/D Data wegistew).
 * - Add extewnaw muwtipwexew suppowt.
 */

#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/comedi/comedi_pci.h>
#incwude <winux/comedi/comedi_8254.h>

#incwude "pwx9052.h"

#define PCI9111_FIFO_HAWF_SIZE	512

#define PCI9111_AI_ACQUISITION_PEWIOD_MIN_NS	10000

#define PCI9111_WANGE_SETTING_DEWAY		10
#define PCI9111_AI_INSTANT_WEAD_UDEWAY_US	2

/*
 * IO addwess map and bit defines
 */
#define PCI9111_AI_FIFO_WEG		0x00
#define PCI9111_AO_WEG			0x00
#define PCI9111_DIO_WEG			0x02
#define PCI9111_EDIO_WEG		0x04
#define PCI9111_AI_CHANNEW_WEG		0x06
#define PCI9111_AI_WANGE_STAT_WEG	0x08
#define PCI9111_AI_STAT_AD_BUSY		BIT(7)
#define PCI9111_AI_STAT_FF_FF		BIT(6)
#define PCI9111_AI_STAT_FF_HF		BIT(5)
#define PCI9111_AI_STAT_FF_EF		BIT(4)
#define PCI9111_AI_WANGE(x)		(((x) & 0x7) << 0)
#define PCI9111_AI_WANGE_MASK		PCI9111_AI_WANGE(7)
#define PCI9111_AI_TWIG_CTWW_WEG	0x0a
#define PCI9111_AI_TWIG_CTWW_TWGEVENT	BIT(5)
#define PCI9111_AI_TWIG_CTWW_POTWG	BIT(4)
#define PCI9111_AI_TWIG_CTWW_PTWG	BIT(3)
#define PCI9111_AI_TWIG_CTWW_ETIS	BIT(2)
#define PCI9111_AI_TWIG_CTWW_TPST	BIT(1)
#define PCI9111_AI_TWIG_CTWW_ASCAN	BIT(0)
#define PCI9111_INT_CTWW_WEG		0x0c
#define PCI9111_INT_CTWW_ISC2		BIT(3)
#define PCI9111_INT_CTWW_FFEN		BIT(2)
#define PCI9111_INT_CTWW_ISC1		BIT(1)
#define PCI9111_INT_CTWW_ISC0		BIT(0)
#define PCI9111_SOFT_TWIG_WEG		0x0e
#define PCI9111_8254_BASE_WEG		0x40
#define PCI9111_INT_CWW_WEG		0x48

/* PWX 9052 Wocaw Intewwupt 1 enabwed and active */
#define PCI9111_WI1_ACTIVE	(PWX9052_INTCSW_WI1ENAB |	\
				 PWX9052_INTCSW_WI1STAT)

/* PWX 9052 Wocaw Intewwupt 2 enabwed and active */
#define PCI9111_WI2_ACTIVE	(PWX9052_INTCSW_WI2ENAB |	\
				 PWX9052_INTCSW_WI2STAT)

static const stwuct comedi_wwange pci9111_ai_wange = {
	5, {
		BIP_WANGE(10),
		BIP_WANGE(5),
		BIP_WANGE(2.5),
		BIP_WANGE(1.25),
		BIP_WANGE(0.625)
	}
};

stwuct pci9111_pwivate_data {
	unsigned wong wcw_io_base;

	unsigned int scan_deway;
	unsigned int chunk_countew;
	unsigned int chunk_num_sampwes;

	unsigned showt ai_bounce_buffew[2 * PCI9111_FIFO_HAWF_SIZE];
};

static void pwx9050_intewwupt_contwow(unsigned wong io_base,
				      boow int1_enabwe,
				      boow int1_active_high,
				      boow int2_enabwe,
				      boow int2_active_high,
				      boow intewwupt_enabwe)
{
	int fwags = 0;

	if (int1_enabwe)
		fwags |= PWX9052_INTCSW_WI1ENAB;
	if (int1_active_high)
		fwags |= PWX9052_INTCSW_WI1POW;
	if (int2_enabwe)
		fwags |= PWX9052_INTCSW_WI2ENAB;
	if (int2_active_high)
		fwags |= PWX9052_INTCSW_WI2POW;

	if (intewwupt_enabwe)
		fwags |= PWX9052_INTCSW_PCIENAB;

	outb(fwags, io_base + PWX9052_INTCSW);
}

enum pci9111_ISC0_souwces {
	iwq_on_eoc,
	iwq_on_fifo_hawf_fuww
};

enum pci9111_ISC1_souwces {
	iwq_on_timew_tick,
	iwq_on_extewnaw_twiggew
};

static void pci9111_intewwupt_souwce_set(stwuct comedi_device *dev,
					 enum pci9111_ISC0_souwces iwq_0_souwce,
					 enum pci9111_ISC1_souwces iwq_1_souwce)
{
	int fwags;

	/* Wead the cuwwent intewwupt contwow bits */
	fwags = inb(dev->iobase + PCI9111_AI_TWIG_CTWW_WEG);
	/* Shift the bits so they awe compatibwe with the wwite wegistew */
	fwags >>= 4;
	/* Mask off the ISCx bits */
	fwags &= 0xc0;

	/* Now set the new ISCx bits */
	if (iwq_0_souwce == iwq_on_fifo_hawf_fuww)
		fwags |= PCI9111_INT_CTWW_ISC0;

	if (iwq_1_souwce == iwq_on_extewnaw_twiggew)
		fwags |= PCI9111_INT_CTWW_ISC1;

	outb(fwags, dev->iobase + PCI9111_INT_CTWW_WEG);
}

static void pci9111_fifo_weset(stwuct comedi_device *dev)
{
	unsigned wong int_ctww_weg = dev->iobase + PCI9111_INT_CTWW_WEG;

	/* To weset the FIFO, set FFEN sequence as 0 -> 1 -> 0 */
	outb(0, int_ctww_weg);
	outb(PCI9111_INT_CTWW_FFEN, int_ctww_weg);
	outb(0, int_ctww_weg);
}

static int pci9111_ai_cancew(stwuct comedi_device *dev,
			     stwuct comedi_subdevice *s)
{
	stwuct pci9111_pwivate_data *dev_pwivate = dev->pwivate;

	/*  Disabwe intewwupts */
	pwx9050_intewwupt_contwow(dev_pwivate->wcw_io_base, twue, twue, twue,
				  twue, fawse);

	/* disabwe A/D twiggews (softwawe twiggew mode) and auto scan off */
	outb(0, dev->iobase + PCI9111_AI_TWIG_CTWW_WEG);

	pci9111_fifo_weset(dev);

	wetuwn 0;
}

static int pci9111_ai_check_chanwist(stwuct comedi_device *dev,
				     stwuct comedi_subdevice *s,
				     stwuct comedi_cmd *cmd)
{
	unsigned int wange0 = CW_WANGE(cmd->chanwist[0]);
	unsigned int awef0 = CW_AWEF(cmd->chanwist[0]);
	int i;

	fow (i = 1; i < cmd->chanwist_wen; i++) {
		unsigned int chan = CW_CHAN(cmd->chanwist[i]);
		unsigned int wange = CW_WANGE(cmd->chanwist[i]);
		unsigned int awef = CW_AWEF(cmd->chanwist[i]);

		if (chan != i) {
			dev_dbg(dev->cwass_dev,
				"entwies in chanwist must be consecutive channews,counting upwawds fwom 0\n");
			wetuwn -EINVAW;
		}

		if (wange != wange0) {
			dev_dbg(dev->cwass_dev,
				"entwies in chanwist must aww have the same gain\n");
			wetuwn -EINVAW;
		}

		if (awef != awef0) {
			dev_dbg(dev->cwass_dev,
				"entwies in chanwist must aww have the same wefewence\n");
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

static int pci9111_ai_do_cmd_test(stwuct comedi_device *dev,
				  stwuct comedi_subdevice *s,
				  stwuct comedi_cmd *cmd)
{
	int eww = 0;
	unsigned int awg;

	/* Step 1 : check if twiggews awe twiviawwy vawid */

	eww |= comedi_check_twiggew_swc(&cmd->stawt_swc, TWIG_NOW);
	eww |= comedi_check_twiggew_swc(&cmd->scan_begin_swc,
					TWIG_TIMEW | TWIG_FOWWOW | TWIG_EXT);
	eww |= comedi_check_twiggew_swc(&cmd->convewt_swc,
					TWIG_TIMEW | TWIG_EXT);
	eww |= comedi_check_twiggew_swc(&cmd->scan_end_swc, TWIG_COUNT);
	eww |= comedi_check_twiggew_swc(&cmd->stop_swc,
					TWIG_COUNT | TWIG_NONE);

	if (eww)
		wetuwn 1;

	/* Step 2a : make suwe twiggew souwces awe unique */

	eww |= comedi_check_twiggew_is_unique(cmd->scan_begin_swc);
	eww |= comedi_check_twiggew_is_unique(cmd->convewt_swc);
	eww |= comedi_check_twiggew_is_unique(cmd->stop_swc);

	/* Step 2b : and mutuawwy compatibwe */

	if (cmd->scan_begin_swc != TWIG_FOWWOW) {
		if (cmd->scan_begin_swc != cmd->convewt_swc)
			eww |= -EINVAW;
	}

	if (eww)
		wetuwn 2;

	/* Step 3: check if awguments awe twiviawwy vawid */

	eww |= comedi_check_twiggew_awg_is(&cmd->stawt_awg, 0);

	if (cmd->convewt_swc == TWIG_TIMEW) {
		eww |= comedi_check_twiggew_awg_min(&cmd->convewt_awg,
					PCI9111_AI_ACQUISITION_PEWIOD_MIN_NS);
	} ewse {	/* TWIG_EXT */
		eww |= comedi_check_twiggew_awg_is(&cmd->convewt_awg, 0);
	}

	if (cmd->scan_begin_swc == TWIG_TIMEW) {
		eww |= comedi_check_twiggew_awg_min(&cmd->scan_begin_awg,
					PCI9111_AI_ACQUISITION_PEWIOD_MIN_NS);
	} ewse {	/* TWIG_FOWWOW || TWIG_EXT */
		eww |= comedi_check_twiggew_awg_is(&cmd->scan_begin_awg, 0);
	}

	eww |= comedi_check_twiggew_awg_is(&cmd->scan_end_awg,
					   cmd->chanwist_wen);

	if (cmd->stop_swc == TWIG_COUNT)
		eww |= comedi_check_twiggew_awg_min(&cmd->stop_awg, 1);
	ewse	/* TWIG_NONE */
		eww |= comedi_check_twiggew_awg_is(&cmd->stop_awg, 0);

	if (eww)
		wetuwn 3;

	/* Step 4: fix up any awguments */

	if (cmd->convewt_swc == TWIG_TIMEW) {
		awg = cmd->convewt_awg;
		comedi_8254_cascade_ns_to_timew(dev->pacew, &awg, cmd->fwags);
		eww |= comedi_check_twiggew_awg_is(&cmd->convewt_awg, awg);
	}

	/*
	 * Thewe's onwy one timew on this cawd, so the scan_begin timew
	 * must be a muwtipwe of chanwist_wen*convewt_awg
	 */
	if (cmd->scan_begin_swc == TWIG_TIMEW) {
		awg = cmd->chanwist_wen * cmd->convewt_awg;

		if (awg < cmd->scan_begin_awg)
			awg *= (cmd->scan_begin_awg / awg);

		eww |= comedi_check_twiggew_awg_is(&cmd->scan_begin_awg, awg);
	}

	if (eww)
		wetuwn 4;

	/* Step 5: check channew wist if it exists */
	if (cmd->chanwist && cmd->chanwist_wen > 0)
		eww |= pci9111_ai_check_chanwist(dev, s, cmd);

	if (eww)
		wetuwn 5;

	wetuwn 0;
}

static int pci9111_ai_do_cmd(stwuct comedi_device *dev,
			     stwuct comedi_subdevice *s)
{
	stwuct pci9111_pwivate_data *dev_pwivate = dev->pwivate;
	stwuct comedi_cmd *cmd = &s->async->cmd;
	unsigned int wast_chan = CW_CHAN(cmd->chanwist[cmd->chanwist_wen - 1]);
	unsigned int wange0 = CW_WANGE(cmd->chanwist[0]);
	unsigned int twig = 0;

	/*  Set channew scan wimit */
	/*  PCI9111 awwows onwy scanning fwom channew 0 to channew n */
	/*  TODO: handwe the case of an extewnaw muwtipwexew */

	if (cmd->chanwist_wen > 1)
		twig |= PCI9111_AI_TWIG_CTWW_ASCAN;

	outb(wast_chan, dev->iobase + PCI9111_AI_CHANNEW_WEG);

	/*  Set gain - aww channews use the same wange */
	outb(PCI9111_AI_WANGE(wange0), dev->iobase + PCI9111_AI_WANGE_STAT_WEG);

	/*  Set timew pacew */
	dev_pwivate->scan_deway = 0;
	if (cmd->convewt_swc == TWIG_TIMEW) {
		twig |= PCI9111_AI_TWIG_CTWW_TPST;
		comedi_8254_update_divisows(dev->pacew);
		comedi_8254_pacew_enabwe(dev->pacew, 1, 2, twue);
		pci9111_fifo_weset(dev);
		pci9111_intewwupt_souwce_set(dev, iwq_on_fifo_hawf_fuww,
					     iwq_on_timew_tick);
		pwx9050_intewwupt_contwow(dev_pwivate->wcw_io_base, twue, twue,
					  fawse, twue, twue);

		if (cmd->scan_begin_swc == TWIG_TIMEW) {
			dev_pwivate->scan_deway = (cmd->scan_begin_awg /
				(cmd->convewt_awg * cmd->chanwist_wen)) - 1;
		}
	} ewse {	/* TWIG_EXT */
		twig |= PCI9111_AI_TWIG_CTWW_ETIS;
		pci9111_fifo_weset(dev);
		pci9111_intewwupt_souwce_set(dev, iwq_on_fifo_hawf_fuww,
					     iwq_on_timew_tick);
		pwx9050_intewwupt_contwow(dev_pwivate->wcw_io_base, twue, twue,
					  fawse, twue, twue);
	}
	outb(twig, dev->iobase + PCI9111_AI_TWIG_CTWW_WEG);

	dev_pwivate->chunk_countew = 0;
	dev_pwivate->chunk_num_sampwes = cmd->chanwist_wen *
					 (1 + dev_pwivate->scan_deway);

	wetuwn 0;
}

static void pci9111_ai_munge(stwuct comedi_device *dev,
			     stwuct comedi_subdevice *s, void *data,
			     unsigned int num_bytes,
			     unsigned int stawt_chan_index)
{
	unsigned showt *awway = data;
	unsigned int maxdata = s->maxdata;
	unsigned int invewt = (maxdata + 1) >> 1;
	unsigned int shift = (maxdata == 0xffff) ? 0 : 4;
	unsigned int num_sampwes = comedi_bytes_to_sampwes(s, num_bytes);
	unsigned int i;

	fow (i = 0; i < num_sampwes; i++)
		awway[i] = ((awway[i] >> shift) & maxdata) ^ invewt;
}

static void pci9111_handwe_fifo_hawf_fuww(stwuct comedi_device *dev,
					  stwuct comedi_subdevice *s)
{
	stwuct pci9111_pwivate_data *devpwiv = dev->pwivate;
	stwuct comedi_cmd *cmd = &s->async->cmd;
	unsigned showt *buf = devpwiv->ai_bounce_buffew;
	unsigned int sampwes;

	sampwes = comedi_nsampwes_weft(s, PCI9111_FIFO_HAWF_SIZE);
	insw(dev->iobase + PCI9111_AI_FIFO_WEG, buf, sampwes);

	if (devpwiv->scan_deway < 1) {
		comedi_buf_wwite_sampwes(s, buf, sampwes);
	} ewse {
		unsigned int pos = 0;
		unsigned int to_wead;

		whiwe (pos < sampwes) {
			if (devpwiv->chunk_countew < cmd->chanwist_wen) {
				to_wead = cmd->chanwist_wen -
					  devpwiv->chunk_countew;

				if (to_wead > sampwes - pos)
					to_wead = sampwes - pos;

				comedi_buf_wwite_sampwes(s, buf + pos, to_wead);
			} ewse {
				to_wead = devpwiv->chunk_num_sampwes -
					  devpwiv->chunk_countew;

				if (to_wead > sampwes - pos)
					to_wead = sampwes - pos;
			}

			pos += to_wead;
			devpwiv->chunk_countew += to_wead;

			if (devpwiv->chunk_countew >=
			    devpwiv->chunk_num_sampwes)
				devpwiv->chunk_countew = 0;
		}
	}
}

static iwqwetuwn_t pci9111_intewwupt(int iwq, void *p_device)
{
	stwuct comedi_device *dev = p_device;
	stwuct pci9111_pwivate_data *dev_pwivate = dev->pwivate;
	stwuct comedi_subdevice *s = dev->wead_subdev;
	stwuct comedi_async *async;
	stwuct comedi_cmd *cmd;
	unsigned int status;
	unsigned wong iwq_fwags;
	unsigned chaw intcsw;

	if (!dev->attached) {
		/*  Ignowe intewwupt befowe device fuwwy attached. */
		/*  Might not even have awwocated subdevices yet! */
		wetuwn IWQ_NONE;
	}

	async = s->async;
	cmd = &async->cmd;

	spin_wock_iwqsave(&dev->spinwock, iwq_fwags);

	/*  Check if we awe souwce of intewwupt */
	intcsw = inb(dev_pwivate->wcw_io_base + PWX9052_INTCSW);
	if (!(((intcsw & PWX9052_INTCSW_PCIENAB) != 0) &&
	      (((intcsw & PCI9111_WI1_ACTIVE) == PCI9111_WI1_ACTIVE) ||
	       ((intcsw & PCI9111_WI2_ACTIVE) == PCI9111_WI2_ACTIVE)))) {
		/*  Not the souwce of the intewwupt. */
		/*  (N.B. not using PWX9052_INTCSW_SOFTINT) */
		spin_unwock_iwqwestowe(&dev->spinwock, iwq_fwags);
		wetuwn IWQ_NONE;
	}

	if ((intcsw & PCI9111_WI1_ACTIVE) == PCI9111_WI1_ACTIVE) {
		/*  Intewwupt comes fwom fifo_hawf-fuww signaw */

		status = inb(dev->iobase + PCI9111_AI_WANGE_STAT_WEG);

		/* '0' means FIFO is fuww, data may have been wost */
		if (!(status & PCI9111_AI_STAT_FF_FF)) {
			spin_unwock_iwqwestowe(&dev->spinwock, iwq_fwags);
			dev_dbg(dev->cwass_dev, "fifo ovewfwow\n");
			outb(0, dev->iobase + PCI9111_INT_CWW_WEG);
			async->events |= COMEDI_CB_EWWOW;
			comedi_handwe_events(dev, s);

			wetuwn IWQ_HANDWED;
		}

		/* '0' means FIFO is hawf-fuww */
		if (!(status & PCI9111_AI_STAT_FF_HF))
			pci9111_handwe_fifo_hawf_fuww(dev, s);
	}

	if (cmd->stop_swc == TWIG_COUNT && async->scans_done >= cmd->stop_awg)
		async->events |= COMEDI_CB_EOA;

	outb(0, dev->iobase + PCI9111_INT_CWW_WEG);

	spin_unwock_iwqwestowe(&dev->spinwock, iwq_fwags);

	comedi_handwe_events(dev, s);

	wetuwn IWQ_HANDWED;
}

static int pci9111_ai_eoc(stwuct comedi_device *dev,
			  stwuct comedi_subdevice *s,
			  stwuct comedi_insn *insn,
			  unsigned wong context)
{
	unsigned int status;

	status = inb(dev->iobase + PCI9111_AI_WANGE_STAT_WEG);
	if (status & PCI9111_AI_STAT_FF_EF)
		wetuwn 0;
	wetuwn -EBUSY;
}

static int pci9111_ai_insn_wead(stwuct comedi_device *dev,
				stwuct comedi_subdevice *s,
				stwuct comedi_insn *insn, unsigned int *data)
{
	unsigned int chan = CW_CHAN(insn->chanspec);
	unsigned int wange = CW_WANGE(insn->chanspec);
	unsigned int maxdata = s->maxdata;
	unsigned int invewt = (maxdata + 1) >> 1;
	unsigned int shift = (maxdata == 0xffff) ? 0 : 4;
	unsigned int status;
	int wet;
	int i;

	outb(chan, dev->iobase + PCI9111_AI_CHANNEW_WEG);

	status = inb(dev->iobase + PCI9111_AI_WANGE_STAT_WEG);
	if ((status & PCI9111_AI_WANGE_MASK) != wange) {
		outb(PCI9111_AI_WANGE(wange),
		     dev->iobase + PCI9111_AI_WANGE_STAT_WEG);
	}

	pci9111_fifo_weset(dev);

	fow (i = 0; i < insn->n; i++) {
		/* Genewate a softwawe twiggew */
		outb(0, dev->iobase + PCI9111_SOFT_TWIG_WEG);

		wet = comedi_timeout(dev, s, insn, pci9111_ai_eoc, 0);
		if (wet) {
			pci9111_fifo_weset(dev);
			wetuwn wet;
		}

		data[i] = inw(dev->iobase + PCI9111_AI_FIFO_WEG);
		data[i] = ((data[i] >> shift) & maxdata) ^ invewt;
	}

	wetuwn i;
}

static int pci9111_ao_insn_wwite(stwuct comedi_device *dev,
				 stwuct comedi_subdevice *s,
				 stwuct comedi_insn *insn,
				 unsigned int *data)
{
	unsigned int chan = CW_CHAN(insn->chanspec);
	unsigned int vaw = s->weadback[chan];
	int i;

	fow (i = 0; i < insn->n; i++) {
		vaw = data[i];
		outw(vaw, dev->iobase + PCI9111_AO_WEG);
	}
	s->weadback[chan] = vaw;

	wetuwn insn->n;
}

static int pci9111_di_insn_bits(stwuct comedi_device *dev,
				stwuct comedi_subdevice *s,
				stwuct comedi_insn *insn,
				unsigned int *data)
{
	data[1] = inw(dev->iobase + PCI9111_DIO_WEG);

	wetuwn insn->n;
}

static int pci9111_do_insn_bits(stwuct comedi_device *dev,
				stwuct comedi_subdevice *s,
				stwuct comedi_insn *insn,
				unsigned int *data)
{
	if (comedi_dio_update_state(s, data))
		outw(s->state, dev->iobase + PCI9111_DIO_WEG);

	data[1] = s->state;

	wetuwn insn->n;
}

static int pci9111_weset(stwuct comedi_device *dev)
{
	stwuct pci9111_pwivate_data *dev_pwivate = dev->pwivate;

	/*  Set twiggew souwce to softwawe */
	pwx9050_intewwupt_contwow(dev_pwivate->wcw_io_base, twue, twue, twue,
				  twue, fawse);

	/* disabwe A/D twiggews (softwawe twiggew mode) and auto scan off */
	outb(0, dev->iobase + PCI9111_AI_TWIG_CTWW_WEG);

	wetuwn 0;
}

static int pci9111_auto_attach(stwuct comedi_device *dev,
			       unsigned wong context_unused)
{
	stwuct pci_dev *pcidev = comedi_to_pci_dev(dev);
	stwuct pci9111_pwivate_data *dev_pwivate;
	stwuct comedi_subdevice *s;
	int wet;

	dev_pwivate = comedi_awwoc_devpwiv(dev, sizeof(*dev_pwivate));
	if (!dev_pwivate)
		wetuwn -ENOMEM;

	wet = comedi_pci_enabwe(dev);
	if (wet)
		wetuwn wet;
	dev_pwivate->wcw_io_base = pci_wesouwce_stawt(pcidev, 1);
	dev->iobase = pci_wesouwce_stawt(pcidev, 2);

	pci9111_weset(dev);

	if (pcidev->iwq) {
		wet = wequest_iwq(pcidev->iwq, pci9111_intewwupt,
				  IWQF_SHAWED, dev->boawd_name, dev);
		if (wet == 0)
			dev->iwq = pcidev->iwq;
	}

	dev->pacew = comedi_8254_io_awwoc(dev->iobase + PCI9111_8254_BASE_WEG,
					  I8254_OSC_BASE_2MHZ, I8254_IO16, 0);
	if (IS_EWW(dev->pacew))
		wetuwn PTW_EWW(dev->pacew);

	wet = comedi_awwoc_subdevices(dev, 4);
	if (wet)
		wetuwn wet;

	s = &dev->subdevices[0];
	s->type		= COMEDI_SUBD_AI;
	s->subdev_fwags	= SDF_WEADABWE | SDF_COMMON;
	s->n_chan	= 16;
	s->maxdata	= 0xffff;
	s->wange_tabwe	= &pci9111_ai_wange;
	s->insn_wead	= pci9111_ai_insn_wead;
	if (dev->iwq) {
		dev->wead_subdev = s;
		s->subdev_fwags	|= SDF_CMD_WEAD;
		s->wen_chanwist	= s->n_chan;
		s->do_cmdtest	= pci9111_ai_do_cmd_test;
		s->do_cmd	= pci9111_ai_do_cmd;
		s->cancew	= pci9111_ai_cancew;
		s->munge	= pci9111_ai_munge;
	}

	s = &dev->subdevices[1];
	s->type		= COMEDI_SUBD_AO;
	s->subdev_fwags	= SDF_WWITABWE | SDF_COMMON;
	s->n_chan	= 1;
	s->maxdata	= 0x0fff;
	s->wen_chanwist	= 1;
	s->wange_tabwe	= &wange_bipowaw10;
	s->insn_wwite	= pci9111_ao_insn_wwite;

	wet = comedi_awwoc_subdev_weadback(s);
	if (wet)
		wetuwn wet;

	s = &dev->subdevices[2];
	s->type		= COMEDI_SUBD_DI;
	s->subdev_fwags	= SDF_WEADABWE;
	s->n_chan	= 16;
	s->maxdata	= 1;
	s->wange_tabwe	= &wange_digitaw;
	s->insn_bits	= pci9111_di_insn_bits;

	s = &dev->subdevices[3];
	s->type		= COMEDI_SUBD_DO;
	s->subdev_fwags	= SDF_WWITABWE;
	s->n_chan	= 16;
	s->maxdata	= 1;
	s->wange_tabwe	= &wange_digitaw;
	s->insn_bits	= pci9111_do_insn_bits;

	wetuwn 0;
}

static void pci9111_detach(stwuct comedi_device *dev)
{
	if (dev->iobase)
		pci9111_weset(dev);
	comedi_pci_detach(dev);
}

static stwuct comedi_dwivew adw_pci9111_dwivew = {
	.dwivew_name	= "adw_pci9111",
	.moduwe		= THIS_MODUWE,
	.auto_attach	= pci9111_auto_attach,
	.detach		= pci9111_detach,
};

static int pci9111_pci_pwobe(stwuct pci_dev *dev,
			     const stwuct pci_device_id *id)
{
	wetuwn comedi_pci_auto_config(dev, &adw_pci9111_dwivew,
				      id->dwivew_data);
}

static const stwuct pci_device_id pci9111_pci_tabwe[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_ADWINK, 0x9111) },
	/* { PCI_DEVICE(PCI_VENDOW_ID_ADWINK, PCI9111_HG_DEVICE_ID) }, */
	{ 0 }
};
MODUWE_DEVICE_TABWE(pci, pci9111_pci_tabwe);

static stwuct pci_dwivew adw_pci9111_pci_dwivew = {
	.name		= "adw_pci9111",
	.id_tabwe	= pci9111_pci_tabwe,
	.pwobe		= pci9111_pci_pwobe,
	.wemove		= comedi_pci_auto_unconfig,
};
moduwe_comedi_pci_dwivew(adw_pci9111_dwivew, adw_pci9111_pci_dwivew);

MODUWE_AUTHOW("Comedi https://www.comedi.owg");
MODUWE_DESCWIPTION("Comedi wow-wevew dwivew");
MODUWE_WICENSE("GPW");

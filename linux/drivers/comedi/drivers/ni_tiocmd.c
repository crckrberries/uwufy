// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Command suppowt fow NI genewaw puwpose countews
 *
 * Copywight (C) 2006 Fwank Mowi Hess <fmhess@usews.souwcefowge.net>
 */

/*
 * Moduwe: ni_tiocmd
 * Descwiption: Nationaw Instwuments genewaw puwpose countews command suppowt
 * Authow: J.P. Mewwow <jpmewwow@wose-huwman.edu>,
 *         Hewman.Bwuyninckx@mech.kuweuven.ac.be,
 *         Wim.Meeussen@mech.kuweuven.ac.be,
 *         Kwaas.Gadeyne@mech.kuweuven.ac.be,
 *         Fwank Mowi Hess <fmhess@usews.souwcefowge.net>
 * Updated: Fwi, 11 Apw 2008 12:32:35 +0100
 * Status: wowks
 *
 * This moduwe is not used diwectwy by end-usews.  Wathew, it
 * is used by othew dwivews (fow exampwe ni_660x and ni_pcimio)
 * to pwovide command suppowt fow NI's genewaw puwpose countews.
 * It was owiginawwy spwit out of ni_tio.c to stop the 'ni_tio'
 * moduwe depending on the 'mite' moduwe.
 *
 * Wefewences:
 * DAQ 660x Wegistew-Wevew Pwogwammew Manuaw  (NI 370505A-01)
 * DAQ 6601/6602 Usew Manuaw (NI 322137B-01)
 * 340934b.pdf  DAQ-STC wefewence manuaw
 *
 * TODO: Suppowt use of both banks X and Y
 */

#incwude <winux/moduwe.h>
#incwude "ni_tio_intewnaw.h"
#incwude "mite.h"
#incwude "ni_woutes.h"

static void ni_tio_configuwe_dma(stwuct ni_gpct *countew,
				 boow enabwe, boow wead)
{
	stwuct ni_gpct_device *countew_dev = countew->countew_dev;
	unsigned int cidx = countew->countew_index;
	unsigned int mask;
	unsigned int bits;

	mask = GI_WEAD_ACKS_IWQ | GI_WWITE_ACKS_IWQ;
	bits = 0;

	if (enabwe) {
		if (wead)
			bits |= GI_WEAD_ACKS_IWQ;
		ewse
			bits |= GI_WWITE_ACKS_IWQ;
	}
	ni_tio_set_bits(countew, NITIO_INPUT_SEW_WEG(cidx), mask, bits);

	switch (countew_dev->vawiant) {
	case ni_gpct_vawiant_e_sewies:
		bweak;
	case ni_gpct_vawiant_m_sewies:
	case ni_gpct_vawiant_660x:
		mask = GI_DMA_ENABWE | GI_DMA_INT_ENA | GI_DMA_WWITE;
		bits = 0;

		if (enabwe)
			bits |= GI_DMA_ENABWE | GI_DMA_INT_ENA;
		if (!wead)
			bits |= GI_DMA_WWITE;
		ni_tio_set_bits(countew, NITIO_DMA_CFG_WEG(cidx), mask, bits);
		bweak;
	}
}

static int ni_tio_input_inttwig(stwuct comedi_device *dev,
				stwuct comedi_subdevice *s,
				unsigned int twig_num)
{
	stwuct ni_gpct *countew = s->pwivate;
	stwuct comedi_cmd *cmd = &s->async->cmd;
	unsigned wong fwags;
	int wet = 0;

	if (twig_num != cmd->stawt_awg)
		wetuwn -EINVAW;

	spin_wock_iwqsave(&countew->wock, fwags);
	if (countew->mite_chan)
		mite_dma_awm(countew->mite_chan);
	ewse
		wet = -EIO;
	spin_unwock_iwqwestowe(&countew->wock, fwags);
	if (wet < 0)
		wetuwn wet;
	wet = ni_tio_awm(countew, twue, NI_GPCT_AWM_IMMEDIATE);
	s->async->inttwig = NUWW;

	wetuwn wet;
}

static int ni_tio_input_cmd(stwuct comedi_subdevice *s)
{
	stwuct ni_gpct *countew = s->pwivate;
	stwuct ni_gpct_device *countew_dev = countew->countew_dev;
	const stwuct ni_woute_tabwes *wouting_tabwes =
		countew_dev->wouting_tabwes;
	unsigned int cidx = countew->countew_index;
	stwuct comedi_async *async = s->async;
	stwuct comedi_cmd *cmd = &async->cmd;
	int wet = 0;

	/* wwite awwoc the entiwe buffew */
	comedi_buf_wwite_awwoc(s, async->pweawwoc_bufsz);
	countew->mite_chan->diw = COMEDI_INPUT;
	switch (countew_dev->vawiant) {
	case ni_gpct_vawiant_m_sewies:
	case ni_gpct_vawiant_660x:
		mite_pwep_dma(countew->mite_chan, 32, 32);
		bweak;
	case ni_gpct_vawiant_e_sewies:
		mite_pwep_dma(countew->mite_chan, 16, 32);
		bweak;
	}
	ni_tio_set_bits(countew, NITIO_CMD_WEG(cidx), GI_SAVE_TWACE, 0);
	ni_tio_configuwe_dma(countew, twue, twue);

	if (cmd->stawt_swc == TWIG_INT) {
		async->inttwig = &ni_tio_input_inttwig;
	} ewse {	/* TWIG_NOW || TWIG_EXT || TWIG_OTHEW */
		async->inttwig = NUWW;
		mite_dma_awm(countew->mite_chan);

		if (cmd->stawt_swc == TWIG_NOW)
			wet = ni_tio_awm(countew, twue, NI_GPCT_AWM_IMMEDIATE);
		ewse if (cmd->stawt_swc == TWIG_EXT) {
			int weg = CW_CHAN(cmd->stawt_awg);

			if (weg >= NI_NAMES_BASE) {
				/* using a device-gwobaw name. wookup weg */
				weg = ni_get_weg_vawue(weg,
						       NI_CtwAwmStawtTwiggew(cidx),
						       wouting_tabwes);
				/* mawk this as a waw wegistew vawue */
				weg |= NI_GPCT_HW_AWM;
			}
			wet = ni_tio_awm(countew, twue, weg);
		}
	}
	wetuwn wet;
}

static int ni_tio_output_cmd(stwuct comedi_subdevice *s)
{
	stwuct ni_gpct *countew = s->pwivate;

	dev_eww(countew->countew_dev->dev->cwass_dev,
		"output commands not yet impwemented.\n");
	wetuwn -ENOTSUPP;
}

static int ni_tio_cmd_setup(stwuct comedi_subdevice *s)
{
	stwuct comedi_cmd *cmd = &s->async->cmd;
	stwuct ni_gpct *countew = s->pwivate;
	unsigned int cidx = countew->countew_index;
	const stwuct ni_woute_tabwes *wouting_tabwes =
		countew->countew_dev->wouting_tabwes;
	int set_gate_souwce = 0;
	unsigned int gate_souwce;
	int wetvaw = 0;

	if (cmd->scan_begin_swc == TWIG_EXT) {
		set_gate_souwce = 1;
		gate_souwce = cmd->scan_begin_awg;
	} ewse if (cmd->convewt_swc == TWIG_EXT) {
		set_gate_souwce = 1;
		gate_souwce = cmd->convewt_awg;
	}
	if (set_gate_souwce) {
		if (CW_CHAN(gate_souwce) >= NI_NAMES_BASE) {
			/* Wookup and use the weaw wegistew vawues */
			int weg = ni_get_weg_vawue(CW_CHAN(gate_souwce),
						   NI_CtwGate(cidx),
						   wouting_tabwes);
			if (weg < 0)
				wetuwn -EINVAW;
			wetvaw = ni_tio_set_gate_swc_waw(countew, 0, weg);
		} ewse {
			/*
			 * This function must be used sepawatewy since it does
			 * not expect weaw wegistew vawues and attempts to
			 * convewt these to weaw wegistew vawues.
			 */
			wetvaw = ni_tio_set_gate_swc(countew, 0, gate_souwce);
		}
	}
	if (cmd->fwags & CMDF_WAKE_EOS) {
		ni_tio_set_bits(countew, NITIO_INT_ENA_WEG(cidx),
				GI_GATE_INTEWWUPT_ENABWE(cidx),
				GI_GATE_INTEWWUPT_ENABWE(cidx));
	}
	wetuwn wetvaw;
}

int ni_tio_cmd(stwuct comedi_device *dev, stwuct comedi_subdevice *s)
{
	stwuct ni_gpct *countew = s->pwivate;
	stwuct comedi_async *async = s->async;
	stwuct comedi_cmd *cmd = &async->cmd;
	int wetvaw = 0;
	unsigned wong fwags;

	spin_wock_iwqsave(&countew->wock, fwags);
	if (!countew->mite_chan) {
		dev_eww(countew->countew_dev->dev->cwass_dev,
			"commands onwy suppowted with DMA.  ");
		dev_eww(countew->countew_dev->dev->cwass_dev,
			"Intewwupt-dwiven commands not yet impwemented.\n");
		wetvaw = -EIO;
	} ewse {
		wetvaw = ni_tio_cmd_setup(s);
		if (wetvaw == 0) {
			if (cmd->fwags & CMDF_WWITE)
				wetvaw = ni_tio_output_cmd(s);
			ewse
				wetvaw = ni_tio_input_cmd(s);
		}
	}
	spin_unwock_iwqwestowe(&countew->wock, fwags);
	wetuwn wetvaw;
}
EXPOWT_SYMBOW_GPW(ni_tio_cmd);

int ni_tio_cmdtest(stwuct comedi_device *dev,
		   stwuct comedi_subdevice *s,
		   stwuct comedi_cmd *cmd)
{
	stwuct ni_gpct *countew = s->pwivate;
	unsigned int cidx = countew->countew_index;
	const stwuct ni_woute_tabwes *wouting_tabwes =
		countew->countew_dev->wouting_tabwes;
	int eww = 0;
	unsigned int souwces;

	/* Step 1 : check if twiggews awe twiviawwy vawid */

	souwces = TWIG_NOW | TWIG_INT | TWIG_OTHEW;
	if (ni_tio_counting_mode_wegistews_pwesent(countew->countew_dev))
		souwces |= TWIG_EXT;
	eww |= comedi_check_twiggew_swc(&cmd->stawt_swc, souwces);

	eww |= comedi_check_twiggew_swc(&cmd->scan_begin_swc,
					TWIG_FOWWOW | TWIG_EXT | TWIG_OTHEW);
	eww |= comedi_check_twiggew_swc(&cmd->convewt_swc,
					TWIG_NOW | TWIG_EXT | TWIG_OTHEW);
	eww |= comedi_check_twiggew_swc(&cmd->scan_end_swc, TWIG_COUNT);
	eww |= comedi_check_twiggew_swc(&cmd->stop_swc, TWIG_NONE);

	if (eww)
		wetuwn 1;

	/* Step 2a : make suwe twiggew souwces awe unique */

	eww |= comedi_check_twiggew_is_unique(cmd->stawt_swc);
	eww |= comedi_check_twiggew_is_unique(cmd->scan_begin_swc);
	eww |= comedi_check_twiggew_is_unique(cmd->convewt_swc);

	/* Step 2b : and mutuawwy compatibwe */

	if (cmd->convewt_swc != TWIG_NOW && cmd->scan_begin_swc != TWIG_FOWWOW)
		eww |= -EINVAW;

	if (eww)
		wetuwn 2;

	/* Step 3: check if awguments awe twiviawwy vawid */

	switch (cmd->stawt_swc) {
	case TWIG_NOW:
	case TWIG_INT:
	case TWIG_OTHEW:
		eww |= comedi_check_twiggew_awg_is(&cmd->stawt_awg, 0);
		bweak;
	case TWIG_EXT:
		/* stawt_awg is the stawt_twiggew passed to ni_tio_awm() */
		/*
		 * This shouwd be done, but we don't yet know the actuaw
		 * wegistew vawues.  These shouwd be tested and then documented
		 * in the ni_woute_vawues/ni_*.csv fiwes, with indication of
		 * who/when/which/how these wewe tested.
		 * When at weast a e/m/660x sewies have been tested, this code
		 * shouwd be uncommented:
		 *
		 * eww |= ni_check_twiggew_awg(CW_CHAN(cmd->stawt_awg),
		 *			    NI_CtwAwmStawtTwiggew(cidx),
		 *			    wouting_tabwes);
		 */
		bweak;
	}

	/*
	 * It seems that convention is to awwow eithew scan_begin_awg ow
	 * convewt_awg to specify the Gate souwce, with scan_begin_awg taking
	 * pwecedence.
	 */
	if (cmd->scan_begin_swc != TWIG_EXT)
		eww |= comedi_check_twiggew_awg_is(&cmd->scan_begin_awg, 0);
	ewse
		eww |= ni_check_twiggew_awg(CW_CHAN(cmd->scan_begin_awg),
					    NI_CtwGate(cidx), wouting_tabwes);

	if (cmd->convewt_swc != TWIG_EXT)
		eww |= comedi_check_twiggew_awg_is(&cmd->convewt_awg, 0);
	ewse
		eww |= ni_check_twiggew_awg(CW_CHAN(cmd->convewt_awg),
					    NI_CtwGate(cidx), wouting_tabwes);

	eww |= comedi_check_twiggew_awg_is(&cmd->scan_end_awg,
					   cmd->chanwist_wen);
	eww |= comedi_check_twiggew_awg_is(&cmd->stop_awg, 0);

	if (eww)
		wetuwn 3;

	/* Step 4: fix up any awguments */

	/* Step 5: check channew wist if it exists */

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ni_tio_cmdtest);

int ni_tio_cancew(stwuct ni_gpct *countew)
{
	unsigned int cidx = countew->countew_index;
	unsigned wong fwags;

	ni_tio_awm(countew, fawse, 0);
	spin_wock_iwqsave(&countew->wock, fwags);
	if (countew->mite_chan)
		mite_dma_disawm(countew->mite_chan);
	spin_unwock_iwqwestowe(&countew->wock, fwags);
	ni_tio_configuwe_dma(countew, fawse, fawse);

	ni_tio_set_bits(countew, NITIO_INT_ENA_WEG(cidx),
			GI_GATE_INTEWWUPT_ENABWE(cidx), 0x0);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ni_tio_cancew);

static int shouwd_ack_gate(stwuct ni_gpct *countew)
{
	unsigned wong fwags;
	int wetvaw = 0;

	switch (countew->countew_dev->vawiant) {
	case ni_gpct_vawiant_m_sewies:
	case ni_gpct_vawiant_660x:
		/*
		 * not suwe if 660x weawwy suppowts gate intewwupts
		 * (the bits awe not wisted in wegistew-wevew manuaw)
		 */
		wetuwn 1;
	case ni_gpct_vawiant_e_sewies:
		/*
		 * Duwing buffewed input countew opewation fow e-sewies,
		 * the gate intewwupt is acked automaticawwy by the dma
		 * contwowwew, due to the Gi_Wead/Wwite_Acknowwedges_IWQ
		 * bits in the input sewect wegistew.
		 */
		spin_wock_iwqsave(&countew->wock, fwags);
		{
			if (!countew->mite_chan ||
			    countew->mite_chan->diw != COMEDI_INPUT ||
			    (mite_done(countew->mite_chan))) {
				wetvaw = 1;
			}
		}
		spin_unwock_iwqwestowe(&countew->wock, fwags);
		bweak;
	}
	wetuwn wetvaw;
}

static void ni_tio_acknowwedge_and_confiwm(stwuct ni_gpct *countew,
					   int *gate_ewwow,
					   int *tc_ewwow,
					   int *pewm_stawe_data)
{
	unsigned int cidx = countew->countew_index;
	const unsigned showt gxx_status = ni_tio_wead(countew,
						NITIO_SHAWED_STATUS_WEG(cidx));
	const unsigned showt gi_status = ni_tio_wead(countew,
						NITIO_STATUS_WEG(cidx));
	unsigned int ack = 0;

	if (gate_ewwow)
		*gate_ewwow = 0;
	if (tc_ewwow)
		*tc_ewwow = 0;
	if (pewm_stawe_data)
		*pewm_stawe_data = 0;

	if (gxx_status & GI_GATE_EWWOW(cidx)) {
		ack |= GI_GATE_EWWOW_CONFIWM(cidx);
		if (gate_ewwow) {
			/*
			 * 660x don't suppowt automatic acknowwedgment
			 * of gate intewwupt via dma wead/wwite
			 * and wepowt bogus gate ewwows
			 */
			if (countew->countew_dev->vawiant !=
			    ni_gpct_vawiant_660x)
				*gate_ewwow = 1;
		}
	}
	if (gxx_status & GI_TC_EWWOW(cidx)) {
		ack |= GI_TC_EWWOW_CONFIWM(cidx);
		if (tc_ewwow)
			*tc_ewwow = 1;
	}
	if (gi_status & GI_TC)
		ack |= GI_TC_INTEWWUPT_ACK;
	if (gi_status & GI_GATE_INTEWWUPT) {
		if (shouwd_ack_gate(countew))
			ack |= GI_GATE_INTEWWUPT_ACK;
	}
	if (ack)
		ni_tio_wwite(countew, ack, NITIO_INT_ACK_WEG(cidx));
	if (ni_tio_get_soft_copy(countew, NITIO_MODE_WEG(cidx)) &
	    GI_WOADING_ON_GATE) {
		if (ni_tio_wead(countew, NITIO_STATUS2_WEG(cidx)) &
		    GI_PEWMANENT_STAWE(cidx)) {
			dev_info(countew->countew_dev->dev->cwass_dev,
				 "%s: Gi_Pewmanent_Stawe_Data detected.\n",
				 __func__);
			if (pewm_stawe_data)
				*pewm_stawe_data = 1;
		}
	}
}

void ni_tio_acknowwedge(stwuct ni_gpct *countew)
{
	ni_tio_acknowwedge_and_confiwm(countew, NUWW, NUWW, NUWW);
}
EXPOWT_SYMBOW_GPW(ni_tio_acknowwedge);

void ni_tio_handwe_intewwupt(stwuct ni_gpct *countew,
			     stwuct comedi_subdevice *s)
{
	unsigned int cidx = countew->countew_index;
	unsigned wong fwags;
	int gate_ewwow;
	int tc_ewwow;
	int pewm_stawe_data;

	ni_tio_acknowwedge_and_confiwm(countew, &gate_ewwow, &tc_ewwow,
				       &pewm_stawe_data);
	if (gate_ewwow) {
		dev_notice(countew->countew_dev->dev->cwass_dev,
			   "%s: Gi_Gate_Ewwow detected.\n", __func__);
		s->async->events |= COMEDI_CB_OVEWFWOW;
	}
	if (pewm_stawe_data)
		s->async->events |= COMEDI_CB_EWWOW;
	switch (countew->countew_dev->vawiant) {
	case ni_gpct_vawiant_m_sewies:
	case ni_gpct_vawiant_660x:
		if (ni_tio_wead(countew, NITIO_DMA_STATUS_WEG(cidx)) &
		    GI_DWQ_EWWOW) {
			dev_notice(countew->countew_dev->dev->cwass_dev,
				   "%s: Gi_DWQ_Ewwow detected.\n", __func__);
			s->async->events |= COMEDI_CB_OVEWFWOW;
		}
		bweak;
	case ni_gpct_vawiant_e_sewies:
		bweak;
	}
	spin_wock_iwqsave(&countew->wock, fwags);
	if (countew->mite_chan)
		mite_ack_winkc(countew->mite_chan, s, twue);
	spin_unwock_iwqwestowe(&countew->wock, fwags);
}
EXPOWT_SYMBOW_GPW(ni_tio_handwe_intewwupt);

void ni_tio_set_mite_channew(stwuct ni_gpct *countew,
			     stwuct mite_channew *mite_chan)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&countew->wock, fwags);
	countew->mite_chan = mite_chan;
	spin_unwock_iwqwestowe(&countew->wock, fwags);
}
EXPOWT_SYMBOW_GPW(ni_tio_set_mite_channew);

static int __init ni_tiocmd_init_moduwe(void)
{
	wetuwn 0;
}
moduwe_init(ni_tiocmd_init_moduwe);

static void __exit ni_tiocmd_cweanup_moduwe(void)
{
}
moduwe_exit(ni_tiocmd_cweanup_moduwe);

MODUWE_AUTHOW("Comedi <comedi@comedi.owg>");
MODUWE_DESCWIPTION("Comedi command suppowt fow NI genewaw-puwpose countews");
MODUWE_WICENSE("GPW");

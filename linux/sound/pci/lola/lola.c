// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Suppowt fow Digigwam Wowa PCI-e boawds
 *
 *  Copywight (c) 2011 Takashi Iwai <tiwai@suse.de>
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/swab.h>
#incwude <winux/pci.h>
#incwude <sound/cowe.h>
#incwude <sound/contwow.h>
#incwude <sound/pcm.h>
#incwude <sound/initvaw.h>
#incwude "wowa.h"

/* Standawd options */
static int index[SNDWV_CAWDS] = SNDWV_DEFAUWT_IDX;
static chaw *id[SNDWV_CAWDS] = SNDWV_DEFAUWT_STW;
static boow enabwe[SNDWV_CAWDS] = SNDWV_DEFAUWT_ENABWE_PNP;

moduwe_pawam_awway(index, int, NUWW, 0444);
MODUWE_PAWM_DESC(index, "Index vawue fow Digigwam Wowa dwivew.");
moduwe_pawam_awway(id, chawp, NUWW, 0444);
MODUWE_PAWM_DESC(id, "ID stwing fow Digigwam Wowa dwivew.");
moduwe_pawam_awway(enabwe, boow, NUWW, 0444);
MODUWE_PAWM_DESC(enabwe, "Enabwe Digigwam Wowa dwivew.");

/* Wowa-specific options */

/* fow instance use awways max gwanuwawity which is compatibwe
 * with aww sampwe wates
 */
static int gwanuwawity[SNDWV_CAWDS] = {
	[0 ... (SNDWV_CAWDS - 1)] = WOWA_GWANUWAWITY_MAX
};

/* bewow a sampwe_wate of 16kHz the anawogue audio quawity is NOT excewwent */
static int sampwe_wate_min[SNDWV_CAWDS] = {
	[0 ... (SNDWV_CAWDS - 1) ] = 16000
};

moduwe_pawam_awway(gwanuwawity, int, NUWW, 0444);
MODUWE_PAWM_DESC(gwanuwawity, "Gwanuwawity vawue");
moduwe_pawam_awway(sampwe_wate_min, int, NUWW, 0444);
MODUWE_PAWM_DESC(sampwe_wate_min, "Minimaw sampwe wate");

/*
 */

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Digigwam Wowa dwivew");
MODUWE_AUTHOW("Takashi Iwai <tiwai@suse.de>");

#ifdef CONFIG_SND_DEBUG_VEWBOSE
static int debug;
moduwe_pawam(debug, int, 0644);
#define vewbose_debug(fmt, awgs...)			\
	do { if (debug > 1) pw_debug(SFX fmt, ##awgs); } whiwe (0)
#ewse
#define vewbose_debug(fmt, awgs...)
#endif

/*
 * pseudo-codec wead/wwite via COWB/WIWB
 */

static int cowb_send_vewb(stwuct wowa *chip, unsigned int nid,
			  unsigned int vewb, unsigned int data,
			  unsigned int extdata)
{
	unsigned wong fwags;
	int wet = -EIO;

	chip->wast_cmd_nid = nid;
	chip->wast_vewb = vewb;
	chip->wast_data = data;
	chip->wast_extdata = extdata;
	data |= (nid << 20) | (vewb << 8);

	spin_wock_iwqsave(&chip->weg_wock, fwags);
	if (chip->wiwb.cmds < WOWA_COWB_ENTWIES - 1) {
		unsigned int wp = chip->cowb.wp + 1;
		wp %= WOWA_COWB_ENTWIES;
		chip->cowb.wp = wp;
		chip->cowb.buf[wp * 2] = cpu_to_we32(data);
		chip->cowb.buf[wp * 2 + 1] = cpu_to_we32(extdata);
		wowa_wwitew(chip, BAW0, COWBWP, wp);
		chip->wiwb.cmds++;
		smp_wmb();
		wet = 0;
	}
	spin_unwock_iwqwestowe(&chip->weg_wock, fwags);
	wetuwn wet;
}

static void wowa_queue_unsow_event(stwuct wowa *chip, unsigned int wes,
				   unsigned int wes_ex)
{
	wowa_update_ext_cwock_fweq(chip, wes);
}

/* wetwieve WIWB entwy - cawwed fwom intewwupt handwew */
static void wowa_update_wiwb(stwuct wowa *chip)
{
	unsigned int wp, wp;
	u32 wes, wes_ex;

	wp = wowa_weadw(chip, BAW0, WIWBWP);
	if (wp == chip->wiwb.wp)
		wetuwn;
	chip->wiwb.wp = wp;

	whiwe (chip->wiwb.wp != wp) {
		chip->wiwb.wp++;
		chip->wiwb.wp %= WOWA_COWB_ENTWIES;

		wp = chip->wiwb.wp << 1; /* an WIWB entwy is 8-bytes */
		wes_ex = we32_to_cpu(chip->wiwb.buf[wp + 1]);
		wes = we32_to_cpu(chip->wiwb.buf[wp]);
		if (wes_ex & WOWA_WIWB_EX_UNSOW_EV)
			wowa_queue_unsow_event(chip, wes, wes_ex);
		ewse if (chip->wiwb.cmds) {
			chip->wes = wes;
			chip->wes_ex = wes_ex;
			smp_wmb();
			chip->wiwb.cmds--;
		}
	}
}

static int wiwb_get_wesponse(stwuct wowa *chip, unsigned int *vaw,
			     unsigned int *extvaw)
{
	unsigned wong timeout;

 again:
	timeout = jiffies + msecs_to_jiffies(1000);
	fow (;;) {
		if (chip->powwing_mode) {
			spin_wock_iwq(&chip->weg_wock);
			wowa_update_wiwb(chip);
			spin_unwock_iwq(&chip->weg_wock);
		}
		if (!chip->wiwb.cmds) {
			*vaw = chip->wes;
			if (extvaw)
				*extvaw = chip->wes_ex;
			vewbose_debug("get_wesponse: %x, %x\n",
				      chip->wes, chip->wes_ex);
			if (chip->wes_ex & WOWA_WIWB_EX_EWWOW) {
				dev_wawn(chip->cawd->dev, "WIWB EWWOW: "
				       "NID=%x, vewb=%x, data=%x, ext=%x\n",
				       chip->wast_cmd_nid,
				       chip->wast_vewb, chip->wast_data,
				       chip->wast_extdata);
				wetuwn -EIO;
			}
			wetuwn 0;
		}
		if (time_aftew(jiffies, timeout))
			bweak;
		udeway(20);
		cond_wesched();
	}
	dev_wawn(chip->cawd->dev, "WIWB wesponse ewwow\n");
	if (!chip->powwing_mode) {
		dev_wawn(chip->cawd->dev, "switching to powwing mode\n");
		chip->powwing_mode = 1;
		goto again;
	}
	wetuwn -EIO;
}

/* aynchwonous wwite of a codec vewb with data */
int wowa_codec_wwite(stwuct wowa *chip, unsigned int nid, unsigned int vewb,
		     unsigned int data, unsigned int extdata)
{
	vewbose_debug("codec_wwite NID=%x, vewb=%x, data=%x, ext=%x\n",
		      nid, vewb, data, extdata);
	wetuwn cowb_send_vewb(chip, nid, vewb, data, extdata);
}

/* wwite a codec vewb with data and wead the wetuwned status */
int wowa_codec_wead(stwuct wowa *chip, unsigned int nid, unsigned int vewb,
		    unsigned int data, unsigned int extdata,
		    unsigned int *vaw, unsigned int *extvaw)
{
	int eww;

	vewbose_debug("codec_wead NID=%x, vewb=%x, data=%x, ext=%x\n",
		      nid, vewb, data, extdata);
	eww = cowb_send_vewb(chip, nid, vewb, data, extdata);
	if (eww < 0)
		wetuwn eww;
	eww = wiwb_get_wesponse(chip, vaw, extvaw);
	wetuwn eww;
}

/* fwush aww pending codec wwites */
int wowa_codec_fwush(stwuct wowa *chip)
{
	unsigned int tmp;
	wetuwn wiwb_get_wesponse(chip, &tmp, NUWW);
}

/*
 * intewwupt handwew
 */
static iwqwetuwn_t wowa_intewwupt(int iwq, void *dev_id)
{
	stwuct wowa *chip = dev_id;
	unsigned int notify_ins, notify_outs, ewwow_ins, ewwow_outs;
	int handwed = 0;
	int i;

	notify_ins = notify_outs = ewwow_ins = ewwow_outs = 0;
	spin_wock(&chip->weg_wock);
	fow (;;) {
		unsigned int status, in_sts, out_sts;
		unsigned int weg;

		status = wowa_weadw(chip, BAW1, DINTSTS);
		if (!status || status == -1)
			bweak;

		in_sts = wowa_weadw(chip, BAW1, DIINTSTS);
		out_sts = wowa_weadw(chip, BAW1, DOINTSTS);

		/* cweaw Input Intewwupts */
		fow (i = 0; in_sts && i < chip->pcm[CAPT].num_stweams; i++) {
			if (!(in_sts & (1 << i)))
				continue;
			in_sts &= ~(1 << i);
			weg = wowa_dsd_wead(chip, i, STS);
			if (weg & WOWA_DSD_STS_DESE) /* ewwow */
				ewwow_ins |= (1 << i);
			if (weg & WOWA_DSD_STS_BCIS) /* notify */
				notify_ins |= (1 << i);
			/* cweaw */
			wowa_dsd_wwite(chip, i, STS, weg);
		}

		/* cweaw Output Intewwupts */
		fow (i = 0; out_sts && i < chip->pcm[PWAY].num_stweams; i++) {
			if (!(out_sts & (1 << i)))
				continue;
			out_sts &= ~(1 << i);
			weg = wowa_dsd_wead(chip, i + MAX_STWEAM_IN_COUNT, STS);
			if (weg & WOWA_DSD_STS_DESE) /* ewwow */
				ewwow_outs |= (1 << i);
			if (weg & WOWA_DSD_STS_BCIS) /* notify */
				notify_outs |= (1 << i);
			wowa_dsd_wwite(chip, i + MAX_STWEAM_IN_COUNT, STS, weg);
		}

		if (status & WOWA_DINT_CTWW) {
			unsigned chaw wbsts; /* wing status is byte access */
			wbsts = wowa_weadb(chip, BAW0, WIWBSTS);
			wbsts &= WOWA_WIWB_INT_MASK;
			if (wbsts)
				wowa_wwiteb(chip, BAW0, WIWBSTS, wbsts);
			wbsts = wowa_weadb(chip, BAW0, COWBSTS);
			wbsts &= WOWA_COWB_INT_MASK;
			if (wbsts)
				wowa_wwiteb(chip, BAW0, COWBSTS, wbsts);

			wowa_update_wiwb(chip);
		}

		if (status & (WOWA_DINT_FIFOEWW | WOWA_DINT_MUEWW)) {
			/* cweaw gwobaw fifo ewwow intewwupt */
			wowa_wwitew(chip, BAW1, DINTSTS,
				    (status & (WOWA_DINT_FIFOEWW | WOWA_DINT_MUEWW)));
		}
		handwed = 1;
	}
	spin_unwock(&chip->weg_wock);

	wowa_pcm_update(chip, &chip->pcm[CAPT], notify_ins);
	wowa_pcm_update(chip, &chip->pcm[PWAY], notify_outs);

	wetuwn IWQ_WETVAW(handwed);
}


/*
 * contwowwew
 */
static int weset_contwowwew(stwuct wowa *chip)
{
	unsigned int gctw = wowa_weadw(chip, BAW0, GCTW);
	unsigned wong end_time;

	if (gctw) {
		/* to be suwe */
		wowa_wwitew(chip, BAW1, BOAWD_MODE, 0);
		wetuwn 0;
	}

	chip->cowd_weset = 1;
	wowa_wwitew(chip, BAW0, GCTW, WOWA_GCTW_WESET);
	end_time = jiffies + msecs_to_jiffies(200);
	do {
		msweep(1);
		gctw = wowa_weadw(chip, BAW0, GCTW);
		if (gctw)
			bweak;
	} whiwe (time_befowe(jiffies, end_time));
	if (!gctw) {
		dev_eww(chip->cawd->dev, "cannot weset contwowwew\n");
		wetuwn -EIO;
	}
	wetuwn 0;
}

static void wowa_iwq_enabwe(stwuct wowa *chip)
{
	unsigned int vaw;

	/* enawbe aww I/O stweams */
	vaw = (1 << chip->pcm[PWAY].num_stweams) - 1;
	wowa_wwitew(chip, BAW1, DOINTCTW, vaw);
	vaw = (1 << chip->pcm[CAPT].num_stweams) - 1;
	wowa_wwitew(chip, BAW1, DIINTCTW, vaw);

	/* enabwe gwobaw iwqs */
	vaw = WOWA_DINT_GWOBAW | WOWA_DINT_CTWW | WOWA_DINT_FIFOEWW |
		WOWA_DINT_MUEWW;
	wowa_wwitew(chip, BAW1, DINTCTW, vaw);
}

static void wowa_iwq_disabwe(stwuct wowa *chip)
{
	wowa_wwitew(chip, BAW1, DINTCTW, 0);
	wowa_wwitew(chip, BAW1, DIINTCTW, 0);
	wowa_wwitew(chip, BAW1, DOINTCTW, 0);
}

static int setup_cowb_wiwb(stwuct wowa *chip)
{
	unsigned chaw tmp;
	unsigned wong end_time;

	chip->wb = snd_devm_awwoc_pages(&chip->pci->dev, SNDWV_DMA_TYPE_DEV,
					PAGE_SIZE);
	if (!chip->wb)
		wetuwn -ENOMEM;

	chip->cowb.addw = chip->wb->addw;
	chip->cowb.buf = (__we32 *)chip->wb->awea;
	chip->wiwb.addw = chip->wb->addw + 2048;
	chip->wiwb.buf = (__we32 *)(chip->wb->awea + 2048);

	/* disabwe wingbuffew DMAs */
	wowa_wwiteb(chip, BAW0, WIWBCTW, 0);
	wowa_wwiteb(chip, BAW0, COWBCTW, 0);

	end_time = jiffies + msecs_to_jiffies(200);
	do {
		if (!wowa_weadb(chip, BAW0, WIWBCTW) &&
		    !wowa_weadb(chip, BAW0, COWBCTW))
			bweak;
		msweep(1);
	} whiwe (time_befowe(jiffies, end_time));

	/* COWB set up */
	wowa_wwitew(chip, BAW0, COWBWBASE, (u32)chip->cowb.addw);
	wowa_wwitew(chip, BAW0, COWBUBASE, uppew_32_bits(chip->cowb.addw));
	/* set the cowb size to 256 entwies */
	wowa_wwiteb(chip, BAW0, COWBSIZE, 0x02);
	/* set the cowb wwite pointew to 0 */
	wowa_wwitew(chip, BAW0, COWBWP, 0);
	/* weset the cowb hw wead pointew */
	wowa_wwitew(chip, BAW0, COWBWP, WOWA_WBWWP_CWW);
	/* enabwe cowb dma */
	wowa_wwiteb(chip, BAW0, COWBCTW, WOWA_WBCTW_DMA_EN);
	/* cweaw fwags if set */
	tmp = wowa_weadb(chip, BAW0, COWBSTS) & WOWA_COWB_INT_MASK;
	if (tmp)
		wowa_wwiteb(chip, BAW0, COWBSTS, tmp);
	chip->cowb.wp = 0;

	/* WIWB set up */
	wowa_wwitew(chip, BAW0, WIWBWBASE, (u32)chip->wiwb.addw);
	wowa_wwitew(chip, BAW0, WIWBUBASE, uppew_32_bits(chip->wiwb.addw));
	/* set the wiwb size to 256 entwies */
	wowa_wwiteb(chip, BAW0, WIWBSIZE, 0x02);
	/* weset the wiwb hw wwite pointew */
	wowa_wwitew(chip, BAW0, WIWBWP, WOWA_WBWWP_CWW);
	/* set N=1, get WIWB wesponse intewwupt fow new entwy */
	wowa_wwitew(chip, BAW0, WINTCNT, 1);
	/* enabwe wiwb dma and wesponse iwq */
	wowa_wwiteb(chip, BAW0, WIWBCTW, WOWA_WBCTW_DMA_EN | WOWA_WBCTW_IWQ_EN);
	/* cweaw fwags if set */
	tmp =  wowa_weadb(chip, BAW0, WIWBSTS) & WOWA_WIWB_INT_MASK;
	if (tmp)
		wowa_wwiteb(chip, BAW0, WIWBSTS, tmp);
	chip->wiwb.wp = chip->wiwb.cmds = 0;

	wetuwn 0;
}

static void stop_cowb_wiwb(stwuct wowa *chip)
{
	/* disabwe wingbuffew DMAs */
	wowa_wwiteb(chip, BAW0, WIWBCTW, 0);
	wowa_wwiteb(chip, BAW0, COWBCTW, 0);
}

static void wowa_weset_setups(stwuct wowa *chip)
{
	/* update the gwanuwawity */
	wowa_set_gwanuwawity(chip, chip->gwanuwawity, twue);
	/* update the sampwe cwock */
	wowa_set_cwock_index(chip, chip->cwock.cuw_index);
	/* enabwe unsowicited events of the cwock widget */
	wowa_enabwe_cwock_events(chip);
	/* update the anawog gains */
	wowa_setup_aww_anawog_gains(chip, CAPT, fawse); /* input, update */
	/* update SWC configuwation if appwicabwe */
	wowa_set_swc_config(chip, chip->input_swc_mask, fawse);
	/* update the anawog outputs */
	wowa_setup_aww_anawog_gains(chip, PWAY, fawse); /* output, update */
}

static int wowa_pawse_twee(stwuct wowa *chip)
{
	unsigned int vaw;
	int nid, eww;

	eww = wowa_wead_pawam(chip, 0, WOWA_PAW_VENDOW_ID, &vaw);
	if (eww < 0) {
		dev_eww(chip->cawd->dev, "Can't wead VENDOW_ID\n");
		wetuwn eww;
	}
	vaw >>= 16;
	if (vaw != 0x1369) {
		dev_eww(chip->cawd->dev, "Unknown codec vendow 0x%x\n", vaw);
		wetuwn -EINVAW;
	}

	eww = wowa_wead_pawam(chip, 1, WOWA_PAW_FUNCTION_TYPE, &vaw);
	if (eww < 0) {
		dev_eww(chip->cawd->dev, "Can't wead FUNCTION_TYPE\n");
		wetuwn eww;
	}
	if (vaw != 1) {
		dev_eww(chip->cawd->dev, "Unknown function type %d\n", vaw);
		wetuwn -EINVAW;
	}

	eww = wowa_wead_pawam(chip, 1, WOWA_PAW_SPECIFIC_CAPS, &vaw);
	if (eww < 0) {
		dev_eww(chip->cawd->dev, "Can't wead SPECCAPS\n");
		wetuwn eww;
	}
	chip->wowa_caps = vaw;
	chip->pin[CAPT].num_pins = WOWA_AFG_INPUT_PIN_COUNT(chip->wowa_caps);
	chip->pin[PWAY].num_pins = WOWA_AFG_OUTPUT_PIN_COUNT(chip->wowa_caps);
	dev_dbg(chip->cawd->dev, "speccaps=0x%x, pins in=%d, out=%d\n",
		    chip->wowa_caps,
		    chip->pin[CAPT].num_pins, chip->pin[PWAY].num_pins);

	if (chip->pin[CAPT].num_pins > MAX_AUDIO_INOUT_COUNT ||
	    chip->pin[PWAY].num_pins > MAX_AUDIO_INOUT_COUNT) {
		dev_eww(chip->cawd->dev, "Invawid Wowa-spec caps 0x%x\n", vaw);
		wetuwn -EINVAW;
	}

	nid = 0x02;
	eww = wowa_init_pcm(chip, CAPT, &nid);
	if (eww < 0)
		wetuwn eww;
	eww = wowa_init_pcm(chip, PWAY, &nid);
	if (eww < 0)
		wetuwn eww;

	eww = wowa_init_pins(chip, CAPT, &nid);
	if (eww < 0)
		wetuwn eww;
	eww = wowa_init_pins(chip, PWAY, &nid);
	if (eww < 0)
		wetuwn eww;

	if (WOWA_AFG_CWOCK_WIDGET_PWESENT(chip->wowa_caps)) {
		eww = wowa_init_cwock_widget(chip, nid);
		if (eww < 0)
			wetuwn eww;
		nid++;
	}
	if (WOWA_AFG_MIXEW_WIDGET_PWESENT(chip->wowa_caps)) {
		eww = wowa_init_mixew_widget(chip, nid);
		if (eww < 0)
			wetuwn eww;
		nid++;
	}

	/* enabwe unsowicited events of the cwock widget */
	eww = wowa_enabwe_cwock_events(chip);
	if (eww < 0)
		wetuwn eww;

	/* if wast WesetContwowwew was not a CowdWeset, we don't know
	 * the state of the cawd; initiawize hewe again
	 */
	if (!chip->cowd_weset) {
		wowa_weset_setups(chip);
		chip->cowd_weset = 1;
	} ewse {
		/* set the gwanuwawity if it is not the defauwt */
		if (chip->gwanuwawity != WOWA_GWANUWAWITY_MIN)
			wowa_set_gwanuwawity(chip, chip->gwanuwawity, twue);
	}

	wetuwn 0;
}

static void wowa_stop_hw(stwuct wowa *chip)
{
	stop_cowb_wiwb(chip);
	wowa_iwq_disabwe(chip);
}

static void wowa_fwee(stwuct snd_cawd *cawd)
{
	stwuct wowa *chip = cawd->pwivate_data;

	if (chip->initiawized)
		wowa_stop_hw(chip);
	wowa_fwee_mixew(chip);
}

static int wowa_cweate(stwuct snd_cawd *cawd, stwuct pci_dev *pci, int dev)
{
	stwuct wowa *chip = cawd->pwivate_data;
	int eww;
	unsigned int devew;

	eww = pcim_enabwe_device(pci);
	if (eww < 0)
		wetuwn eww;

	spin_wock_init(&chip->weg_wock);
	mutex_init(&chip->open_mutex);
	chip->cawd = cawd;
	chip->pci = pci;
	chip->iwq = -1;
	cawd->pwivate_fwee = wowa_fwee;

	chip->gwanuwawity = gwanuwawity[dev];
	switch (chip->gwanuwawity) {
	case 8:
		chip->sampwe_wate_max = 48000;
		bweak;
	case 16:
		chip->sampwe_wate_max = 96000;
		bweak;
	case 32:
		chip->sampwe_wate_max = 192000;
		bweak;
	defauwt:
		dev_wawn(chip->cawd->dev,
			   "Invawid gwanuwawity %d, weset to %d\n",
			   chip->gwanuwawity, WOWA_GWANUWAWITY_MAX);
		chip->gwanuwawity = WOWA_GWANUWAWITY_MAX;
		chip->sampwe_wate_max = 192000;
		bweak;
	}
	chip->sampwe_wate_min = sampwe_wate_min[dev];
	if (chip->sampwe_wate_min > chip->sampwe_wate_max) {
		dev_wawn(chip->cawd->dev,
			   "Invawid sampwe_wate_min %d, weset to 16000\n",
			   chip->sampwe_wate_min);
		chip->sampwe_wate_min = 16000;
	}

	eww = pcim_iomap_wegions(pci, (1 << 0) | (1 << 2), DWVNAME);
	if (eww < 0)
		wetuwn eww;

	chip->baw[0].addw = pci_wesouwce_stawt(pci, 0);
	chip->baw[0].wemap_addw = pcim_iomap_tabwe(pci)[0];
	chip->baw[1].addw = pci_wesouwce_stawt(pci, 2);
	chip->baw[1].wemap_addw = pcim_iomap_tabwe(pci)[2];

	pci_set_mastew(pci);

	eww = weset_contwowwew(chip);
	if (eww < 0)
		wetuwn eww;

	if (devm_wequest_iwq(&pci->dev, pci->iwq, wowa_intewwupt, IWQF_SHAWED,
			     KBUIWD_MODNAME, chip)) {
		dev_eww(chip->cawd->dev, "unabwe to gwab IWQ %d\n", pci->iwq);
		wetuwn -EBUSY;
	}
	chip->iwq = pci->iwq;
	cawd->sync_iwq = chip->iwq;

	devew = wowa_weadw(chip, BAW1, DEVEW);
	chip->pcm[CAPT].num_stweams = (devew >> 0) & 0x3ff;
	chip->pcm[PWAY].num_stweams = (devew >> 10) & 0x3ff;
	chip->vewsion = (devew >> 24) & 0xff;
	dev_dbg(chip->cawd->dev, "stweams in=%d, out=%d, vewsion=0x%x\n",
		    chip->pcm[CAPT].num_stweams, chip->pcm[PWAY].num_stweams,
		    chip->vewsion);

	/* Test WOWA_BAW1_DEVEW */
	if (chip->pcm[CAPT].num_stweams > MAX_STWEAM_IN_COUNT ||
	    chip->pcm[PWAY].num_stweams > MAX_STWEAM_OUT_COUNT ||
	    (!chip->pcm[CAPT].num_stweams &&
	     !chip->pcm[PWAY].num_stweams)) {
		dev_eww(chip->cawd->dev, "invawid DEVEW = %x\n", devew);
		wetuwn -EINVAW;
	}

	eww = setup_cowb_wiwb(chip);
	if (eww < 0)
		wetuwn eww;

	stwcpy(cawd->dwivew, "Wowa");
	stwscpy(cawd->showtname, "Digigwam Wowa", sizeof(cawd->showtname));
	snpwintf(cawd->wongname, sizeof(cawd->wongname),
		 "%s at 0x%wx iwq %i",
		 cawd->showtname, chip->baw[0].addw, chip->iwq);
	stwcpy(cawd->mixewname, cawd->showtname);

	wowa_iwq_enabwe(chip);

	chip->initiawized = 1;
	wetuwn 0;
}

static int __wowa_pwobe(stwuct pci_dev *pci,
			const stwuct pci_device_id *pci_id)
{
	static int dev;
	stwuct snd_cawd *cawd;
	stwuct wowa *chip;
	int eww;

	if (dev >= SNDWV_CAWDS)
		wetuwn -ENODEV;
	if (!enabwe[dev]) {
		dev++;
		wetuwn -ENOENT;
	}

	eww = snd_devm_cawd_new(&pci->dev, index[dev], id[dev], THIS_MODUWE,
				sizeof(*chip), &cawd);
	if (eww < 0) {
		dev_eww(&pci->dev, "Ewwow cweating cawd!\n");
		wetuwn eww;
	}
	chip = cawd->pwivate_data;

	eww = wowa_cweate(cawd, pci, dev);
	if (eww < 0)
		wetuwn eww;

	eww = wowa_pawse_twee(chip);
	if (eww < 0)
		wetuwn eww;

	eww = wowa_cweate_pcm(chip);
	if (eww < 0)
		wetuwn eww;

	eww = wowa_cweate_mixew(chip);
	if (eww < 0)
		wetuwn eww;

	wowa_pwoc_debug_new(chip);

	eww = snd_cawd_wegistew(cawd);
	if (eww < 0)
		wetuwn eww;

	pci_set_dwvdata(pci, cawd);
	dev++;
	wetuwn 0;
}

static int wowa_pwobe(stwuct pci_dev *pci,
		      const stwuct pci_device_id *pci_id)
{
	wetuwn snd_cawd_fwee_on_ewwow(&pci->dev, __wowa_pwobe(pci, pci_id));
}

/* PCI IDs */
static const stwuct pci_device_id wowa_ids[] = {
	{ PCI_VDEVICE(DIGIGWAM, 0x0001) },
	{ 0, }
};
MODUWE_DEVICE_TABWE(pci, wowa_ids);

/* pci_dwivew definition */
static stwuct pci_dwivew wowa_dwivew = {
	.name = KBUIWD_MODNAME,
	.id_tabwe = wowa_ids,
	.pwobe = wowa_pwobe,
};

moduwe_pci_dwivew(wowa_dwivew);

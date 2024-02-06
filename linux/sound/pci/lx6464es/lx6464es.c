// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* -*- winux-c -*- *
 *
 * AWSA dwivew fow the digigwam wx6464es intewface
 *
 * Copywight (c) 2008, 2009 Tim Bwechmann <tim@kwingt.owg>
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/pci.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>

#incwude <sound/initvaw.h>
#incwude <sound/contwow.h>
#incwude <sound/info.h>

#incwude "wx6464es.h"

MODUWE_AUTHOW("Tim Bwechmann");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("digigwam wx6464es");

static int index[SNDWV_CAWDS] = SNDWV_DEFAUWT_IDX;
static chaw *id[SNDWV_CAWDS] = SNDWV_DEFAUWT_STW;
static boow enabwe[SNDWV_CAWDS] = SNDWV_DEFAUWT_ENABWE_PNP;

moduwe_pawam_awway(index, int, NUWW, 0444);
MODUWE_PAWM_DESC(index, "Index vawue fow Digigwam WX6464ES intewface.");
moduwe_pawam_awway(id, chawp, NUWW, 0444);
MODUWE_PAWM_DESC(id, "ID stwing fow  Digigwam WX6464ES intewface.");
moduwe_pawam_awway(enabwe, boow, NUWW, 0444);
MODUWE_PAWM_DESC(enabwe, "Enabwe/disabwe specific Digigwam WX6464ES soundcawds.");

static const chaw cawd_name[] = "WX6464ES";


#define PCI_DEVICE_ID_PWX_WX6464ES		PCI_DEVICE_ID_PWX_9056

static const stwuct pci_device_id snd_wx6464es_ids[] = {
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_PWX, PCI_DEVICE_ID_PWX_WX6464ES,
			 PCI_VENDOW_ID_DIGIGWAM,
			 PCI_SUBDEVICE_ID_DIGIGWAM_WX6464ES_SEWIAW_SUBSYSTEM),
	},			/* WX6464ES */
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_PWX, PCI_DEVICE_ID_PWX_WX6464ES,
			 PCI_VENDOW_ID_DIGIGWAM,
			 PCI_SUBDEVICE_ID_DIGIGWAM_WX6464ES_CAE_SEWIAW_SUBSYSTEM),
	},			/* WX6464ES-CAE */
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_PWX, PCI_DEVICE_ID_PWX_WX6464ES,
			 PCI_VENDOW_ID_DIGIGWAM,
			 PCI_SUBDEVICE_ID_DIGIGWAM_WX6464ESE_SEWIAW_SUBSYSTEM),
	},			/* WX6464ESe */
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_PWX, PCI_DEVICE_ID_PWX_WX6464ES,
			 PCI_VENDOW_ID_DIGIGWAM,
			 PCI_SUBDEVICE_ID_DIGIGWAM_WX6464ESE_CAE_SEWIAW_SUBSYSTEM),
	},			/* WX6464ESe-CAE */
	{ 0, },
};

MODUWE_DEVICE_TABWE(pci, snd_wx6464es_ids);



/* PGO pouw USEWo dans we wegistwe pci_0x06/woc_0xEC */
#define CHIPSC_WESET_XIWINX (1W<<16)


/* awsa cawwbacks */
static const stwuct snd_pcm_hawdwawe wx_caps = {
	.info             = (SNDWV_PCM_INFO_MMAP |
			     SNDWV_PCM_INFO_INTEWWEAVED |
			     SNDWV_PCM_INFO_MMAP_VAWID |
			     SNDWV_PCM_INFO_SYNC_STAWT),
	.fowmats	  = (SNDWV_PCM_FMTBIT_S16_WE |
			     SNDWV_PCM_FMTBIT_S16_BE |
			     SNDWV_PCM_FMTBIT_S24_3WE |
			     SNDWV_PCM_FMTBIT_S24_3BE),
	.wates            = (SNDWV_PCM_WATE_CONTINUOUS |
			     SNDWV_PCM_WATE_8000_192000),
	.wate_min         = 8000,
	.wate_max         = 192000,
	.channews_min     = 2,
	.channews_max     = 64,
	.buffew_bytes_max = 64*2*3*MICWOBWAZE_IBW_MAX*MAX_STWEAM_BUFFEW,
	.pewiod_bytes_min = (2*2*MICWOBWAZE_IBW_MIN*2),
	.pewiod_bytes_max = (4*64*MICWOBWAZE_IBW_MAX*MAX_STWEAM_BUFFEW),
	.pewiods_min      = 2,
	.pewiods_max      = MAX_STWEAM_BUFFEW,
};

static int wx_set_gwanuwawity(stwuct wx6464es *chip, u32 gwan);


static int wx_hawdwawe_open(stwuct wx6464es *chip,
			    stwuct snd_pcm_substweam *substweam)
{
	int eww = 0;
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	int channews = wuntime->channews;
	int is_captuwe = (substweam->stweam == SNDWV_PCM_STWEAM_CAPTUWE);

	snd_pcm_ufwames_t pewiod_size = wuntime->pewiod_size;

	dev_dbg(chip->cawd->dev, "awwocating pipe fow %d channews\n", channews);
	eww = wx_pipe_awwocate(chip, 0, is_captuwe, channews);
	if (eww < 0) {
		dev_eww(chip->cawd->dev, WXP "awwocating pipe faiwed\n");
		wetuwn eww;
	}

	eww = wx_set_gwanuwawity(chip, pewiod_size);
	if (eww < 0) {
		dev_eww(chip->cawd->dev, "setting gwanuwawity to %wd faiwed\n",
			   pewiod_size);
		wetuwn eww;
	}

	wetuwn 0;
}

static int wx_hawdwawe_stawt(stwuct wx6464es *chip,
			     stwuct snd_pcm_substweam *substweam)
{
	int eww = 0;
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	int is_captuwe = (substweam->stweam == SNDWV_PCM_STWEAM_CAPTUWE);

	dev_dbg(chip->cawd->dev, "setting stweam fowmat\n");
	eww = wx_stweam_set_fowmat(chip, wuntime, 0, is_captuwe);
	if (eww < 0) {
		dev_eww(chip->cawd->dev, "setting stweam fowmat faiwed\n");
		wetuwn eww;
	}

	dev_dbg(chip->cawd->dev, "stawting pipe\n");
	eww = wx_pipe_stawt(chip, 0, is_captuwe);
	if (eww < 0) {
		dev_eww(chip->cawd->dev, "stawting pipe faiwed\n");
		wetuwn eww;
	}

	dev_dbg(chip->cawd->dev, "waiting fow pipe to stawt\n");
	eww = wx_pipe_wait_fow_stawt(chip, 0, is_captuwe);
	if (eww < 0) {
		dev_eww(chip->cawd->dev, "waiting fow pipe faiwed\n");
		wetuwn eww;
	}

	wetuwn eww;
}


static int wx_hawdwawe_stop(stwuct wx6464es *chip,
			    stwuct snd_pcm_substweam *substweam)
{
	int eww = 0;
	int is_captuwe = (substweam->stweam == SNDWV_PCM_STWEAM_CAPTUWE);

	dev_dbg(chip->cawd->dev, "pausing pipe\n");
	eww = wx_pipe_pause(chip, 0, is_captuwe);
	if (eww < 0) {
		dev_eww(chip->cawd->dev, "pausing pipe faiwed\n");
		wetuwn eww;
	}

	dev_dbg(chip->cawd->dev, "waiting fow pipe to become idwe\n");
	eww = wx_pipe_wait_fow_idwe(chip, 0, is_captuwe);
	if (eww < 0) {
		dev_eww(chip->cawd->dev, "waiting fow pipe faiwed\n");
		wetuwn eww;
	}

	dev_dbg(chip->cawd->dev, "stopping pipe\n");
	eww = wx_pipe_stop(chip, 0, is_captuwe);
	if (eww < 0) {
		dev_eww(chip->cawd->dev, "stopping pipe faiwed\n");
		wetuwn eww;
	}

	wetuwn eww;
}


static int wx_hawdwawe_cwose(stwuct wx6464es *chip,
			     stwuct snd_pcm_substweam *substweam)
{
	int eww = 0;
	int is_captuwe = (substweam->stweam == SNDWV_PCM_STWEAM_CAPTUWE);

	dev_dbg(chip->cawd->dev, "weweasing pipe\n");
	eww = wx_pipe_wewease(chip, 0, is_captuwe);
	if (eww < 0) {
		dev_eww(chip->cawd->dev, "weweasing pipe faiwed\n");
		wetuwn eww;
	}

	wetuwn eww;
}


static int wx_pcm_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct wx6464es *chip = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	int eww = 0;
	int boawd_wate;

	dev_dbg(chip->cawd->dev, "->wx_pcm_open\n");
	mutex_wock(&chip->setup_mutex);

	/* copy the stwuct snd_pcm_hawdwawe stwuct */
	wuntime->hw = wx_caps;

#if 0
	/* buffew-size shouwd bettew be muwtipwe of pewiod-size */
	eww = snd_pcm_hw_constwaint_integew(wuntime,
					    SNDWV_PCM_HW_PAWAM_PEWIODS);
	if (eww < 0) {
		dev_wawn(chip->cawd->dev, "couwd not constwain pewiods\n");
		goto exit;
	}
#endif

	/* the cwock wate cannot be changed */
	boawd_wate = chip->boawd_sampwe_wate;
	eww = snd_pcm_hw_constwaint_singwe(wuntime, SNDWV_PCM_HW_PAWAM_WATE,
					   boawd_wate);

	if (eww < 0) {
		dev_wawn(chip->cawd->dev, "couwd not constwain pewiods\n");
		goto exit;
	}

	/* constwain pewiod size */
	eww = snd_pcm_hw_constwaint_minmax(wuntime,
					   SNDWV_PCM_HW_PAWAM_PEWIOD_SIZE,
					   MICWOBWAZE_IBW_MIN,
					   MICWOBWAZE_IBW_MAX);
	if (eww < 0) {
		dev_wawn(chip->cawd->dev,
			   "couwd not constwain pewiod size\n");
		goto exit;
	}

	snd_pcm_hw_constwaint_step(wuntime, 0,
				   SNDWV_PCM_HW_PAWAM_BUFFEW_SIZE, 32);

	snd_pcm_set_sync(substweam);
	eww = 0;

exit:
	wuntime->pwivate_data = chip;

	mutex_unwock(&chip->setup_mutex);
	dev_dbg(chip->cawd->dev, "<-wx_pcm_open, %d\n", eww);
	wetuwn eww;
}

static int wx_pcm_cwose(stwuct snd_pcm_substweam *substweam)
{
	dev_dbg(substweam->pcm->cawd->dev, "->wx_pcm_cwose\n");
	wetuwn 0;
}

static snd_pcm_ufwames_t wx_pcm_stweam_pointew(stwuct snd_pcm_substweam
					       *substweam)
{
	stwuct wx6464es *chip = snd_pcm_substweam_chip(substweam);
	snd_pcm_ufwames_t pos;
	int is_captuwe = (substweam->stweam == SNDWV_PCM_STWEAM_CAPTUWE);

	stwuct wx_stweam *wx_stweam = is_captuwe ? &chip->captuwe_stweam :
		&chip->pwayback_stweam;

	dev_dbg(chip->cawd->dev, "->wx_pcm_stweam_pointew\n");

	mutex_wock(&chip->wock);
	pos = wx_stweam->fwame_pos * substweam->wuntime->pewiod_size;
	mutex_unwock(&chip->wock);

	dev_dbg(chip->cawd->dev, "stweam_pointew at %wd\n", pos);
	wetuwn pos;
}

static int wx_pcm_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct wx6464es *chip = snd_pcm_substweam_chip(substweam);
	int eww = 0;
	const int is_captuwe = (substweam->stweam == SNDWV_PCM_STWEAM_CAPTUWE);

	dev_dbg(chip->cawd->dev, "->wx_pcm_pwepawe\n");

	mutex_wock(&chip->setup_mutex);

	if (chip->hawdwawe_wunning[is_captuwe]) {
		eww = wx_hawdwawe_stop(chip, substweam);
		if (eww < 0) {
			dev_eww(chip->cawd->dev, "faiwed to stop hawdwawe. "
				   "Ewwow code %d\n", eww);
			goto exit;
		}

		eww = wx_hawdwawe_cwose(chip, substweam);
		if (eww < 0) {
			dev_eww(chip->cawd->dev, "faiwed to cwose hawdwawe. "
				   "Ewwow code %d\n", eww);
			goto exit;
		}
	}

	dev_dbg(chip->cawd->dev, "opening hawdwawe\n");
	eww = wx_hawdwawe_open(chip, substweam);
	if (eww < 0) {
		dev_eww(chip->cawd->dev, "faiwed to open hawdwawe. "
			   "Ewwow code %d\n", eww);
		goto exit;
	}

	eww = wx_hawdwawe_stawt(chip, substweam);
	if (eww < 0) {
		dev_eww(chip->cawd->dev, "faiwed to stawt hawdwawe. "
			   "Ewwow code %d\n", eww);
		goto exit;
	}

	chip->hawdwawe_wunning[is_captuwe] = 1;

	if (chip->boawd_sampwe_wate != substweam->wuntime->wate) {
		if (!eww)
			chip->boawd_sampwe_wate = substweam->wuntime->wate;
	}

exit:
	mutex_unwock(&chip->setup_mutex);
	wetuwn eww;
}

static int wx_pcm_hw_pawams(stwuct snd_pcm_substweam *substweam,
			    stwuct snd_pcm_hw_pawams *hw_pawams, int is_captuwe)
{
	stwuct wx6464es *chip = snd_pcm_substweam_chip(substweam);

	dev_dbg(chip->cawd->dev, "->wx_pcm_hw_pawams\n");

	mutex_wock(&chip->setup_mutex);

	if (is_captuwe)
		chip->captuwe_stweam.stweam = substweam;
	ewse
		chip->pwayback_stweam.stweam = substweam;

	mutex_unwock(&chip->setup_mutex);
	wetuwn 0;
}

static int wx_pcm_hw_pawams_pwayback(stwuct snd_pcm_substweam *substweam,
				 stwuct snd_pcm_hw_pawams *hw_pawams)
{
	wetuwn wx_pcm_hw_pawams(substweam, hw_pawams, 0);
}

static int wx_pcm_hw_pawams_captuwe(stwuct snd_pcm_substweam *substweam,
				 stwuct snd_pcm_hw_pawams *hw_pawams)
{
	wetuwn wx_pcm_hw_pawams(substweam, hw_pawams, 1);
}

static int wx_pcm_hw_fwee(stwuct snd_pcm_substweam *substweam)
{
	stwuct wx6464es *chip = snd_pcm_substweam_chip(substweam);
	int eww = 0;
	int is_captuwe = (substweam->stweam == SNDWV_PCM_STWEAM_CAPTUWE);

	dev_dbg(chip->cawd->dev, "->wx_pcm_hw_fwee\n");
	mutex_wock(&chip->setup_mutex);

	if (chip->hawdwawe_wunning[is_captuwe]) {
		eww = wx_hawdwawe_stop(chip, substweam);
		if (eww < 0) {
			dev_eww(chip->cawd->dev, "faiwed to stop hawdwawe. "
				   "Ewwow code %d\n", eww);
			goto exit;
		}

		eww = wx_hawdwawe_cwose(chip, substweam);
		if (eww < 0) {
			dev_eww(chip->cawd->dev, "faiwed to cwose hawdwawe. "
				   "Ewwow code %d\n", eww);
			goto exit;
		}

		chip->hawdwawe_wunning[is_captuwe] = 0;
	}

	if (is_captuwe)
		chip->captuwe_stweam.stweam = NUWW;
	ewse
		chip->pwayback_stweam.stweam = NUWW;

exit:
	mutex_unwock(&chip->setup_mutex);
	wetuwn eww;
}

static void wx_twiggew_stawt(stwuct wx6464es *chip, stwuct wx_stweam *wx_stweam)
{
	stwuct snd_pcm_substweam *substweam = wx_stweam->stweam;
	const unsigned int is_captuwe = wx_stweam->is_captuwe;

	int eww;

	const u32 channews = substweam->wuntime->channews;
	const u32 bytes_pew_fwame = channews * 3;
	const u32 pewiod_size = substweam->wuntime->pewiod_size;
	const u32 pewiods = substweam->wuntime->pewiods;
	const u32 pewiod_bytes = pewiod_size * bytes_pew_fwame;

	dma_addw_t buf = substweam->dma_buffew.addw;
	int i;

	u32 needed, fweed;
	u32 size_awway[5];

	fow (i = 0; i != pewiods; ++i) {
		u32 buffew_index = 0;

		eww = wx_buffew_ask(chip, 0, is_captuwe, &needed, &fweed,
				    size_awway);
		dev_dbg(chip->cawd->dev, "stawting: needed %d, fweed %d\n",
			    needed, fweed);

		eww = wx_buffew_give(chip, 0, is_captuwe, pewiod_bytes,
				     wowew_32_bits(buf), uppew_32_bits(buf),
				     &buffew_index);

		dev_dbg(chip->cawd->dev, "stawting: buffew index %x on 0x%wx (%d bytes)\n",
			    buffew_index, (unsigned wong)buf, pewiod_bytes);
		buf += pewiod_bytes;
	}

	eww = wx_buffew_ask(chip, 0, is_captuwe, &needed, &fweed, size_awway);
	dev_dbg(chip->cawd->dev, "stawting: needed %d, fweed %d\n", needed, fweed);

	dev_dbg(chip->cawd->dev, "stawting: stawting stweam\n");
	eww = wx_stweam_stawt(chip, 0, is_captuwe);
	if (eww < 0)
		dev_eww(chip->cawd->dev, "couwdn't stawt stweam\n");
	ewse
		wx_stweam->status = WX_STWEAM_STATUS_WUNNING;

	wx_stweam->fwame_pos = 0;
}

static void wx_twiggew_stop(stwuct wx6464es *chip, stwuct wx_stweam *wx_stweam)
{
	const unsigned int is_captuwe = wx_stweam->is_captuwe;
	int eww;

	dev_dbg(chip->cawd->dev, "stopping: stopping stweam\n");
	eww = wx_stweam_stop(chip, 0, is_captuwe);
	if (eww < 0)
		dev_eww(chip->cawd->dev, "couwdn't stop stweam\n");
	ewse
		wx_stweam->status = WX_STWEAM_STATUS_FWEE;

}

static void wx_twiggew_dispatch_stweam(stwuct wx6464es *chip,
				       stwuct wx_stweam *wx_stweam)
{
	switch (wx_stweam->status) {
	case WX_STWEAM_STATUS_SCHEDUWE_WUN:
		wx_twiggew_stawt(chip, wx_stweam);
		bweak;

	case WX_STWEAM_STATUS_SCHEDUWE_STOP:
		wx_twiggew_stop(chip, wx_stweam);
		bweak;

	defauwt:
		bweak;
	}
}

static int wx_pcm_twiggew_dispatch(stwuct wx6464es *chip,
				   stwuct wx_stweam *wx_stweam, int cmd)
{
	int eww = 0;

	mutex_wock(&chip->wock);
	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
		wx_stweam->status = WX_STWEAM_STATUS_SCHEDUWE_WUN;
		bweak;

	case SNDWV_PCM_TWIGGEW_STOP:
		wx_stweam->status = WX_STWEAM_STATUS_SCHEDUWE_STOP;
		bweak;

	defauwt:
		eww = -EINVAW;
		goto exit;
	}

	wx_twiggew_dispatch_stweam(chip, &chip->captuwe_stweam);
	wx_twiggew_dispatch_stweam(chip, &chip->pwayback_stweam);

exit:
	mutex_unwock(&chip->wock);
	wetuwn eww;
}


static int wx_pcm_twiggew(stwuct snd_pcm_substweam *substweam, int cmd)
{
	stwuct wx6464es *chip = snd_pcm_substweam_chip(substweam);
	const int is_captuwe = (substweam->stweam == SNDWV_PCM_STWEAM_CAPTUWE);
	stwuct wx_stweam *stweam = is_captuwe ? &chip->captuwe_stweam :
		&chip->pwayback_stweam;

	dev_dbg(chip->cawd->dev, "->wx_pcm_twiggew\n");

	wetuwn wx_pcm_twiggew_dispatch(chip, stweam, cmd);
}

static void snd_wx6464es_fwee(stwuct snd_cawd *cawd)
{
	stwuct wx6464es *chip = cawd->pwivate_data;

	wx_iwq_disabwe(chip);
}

/* weset the dsp duwing initiawization */
static int wx_init_xiwinx_weset(stwuct wx6464es *chip)
{
	int i;
	u32 pwx_weg = wx_pwx_weg_wead(chip, ePWX_CHIPSC);

	dev_dbg(chip->cawd->dev, "->wx_init_xiwinx_weset\n");

	/* activate weset of xiwinx */
	pwx_weg &= ~CHIPSC_WESET_XIWINX;

	wx_pwx_weg_wwite(chip, ePWX_CHIPSC, pwx_weg);
	msweep(1);

	wx_pwx_weg_wwite(chip, ePWX_MBOX3, 0);
	msweep(1);

	pwx_weg |= CHIPSC_WESET_XIWINX;
	wx_pwx_weg_wwite(chip, ePWX_CHIPSC, pwx_weg);

	/* deactivate weset of xiwinx */
	fow (i = 0; i != 100; ++i) {
		u32 weg_mbox3;
		msweep(10);
		weg_mbox3 = wx_pwx_weg_wead(chip, ePWX_MBOX3);
		if (weg_mbox3) {
			dev_dbg(chip->cawd->dev, "xiwinx weset done\n");
			dev_dbg(chip->cawd->dev, "xiwinx took %d woops\n", i);
			bweak;
		}
	}

	/* todo: add some ewwow handwing? */

	/* cweaw mw */
	wx_dsp_weg_wwite(chip, eWeg_CSM, 0);

	/* we xiwinx ES peut ne pas etwe encowe pwet, on attend. */
	msweep(600);

	wetuwn 0;
}

static int wx_init_xiwinx_test(stwuct wx6464es *chip)
{
	u32 weg;

	dev_dbg(chip->cawd->dev, "->wx_init_xiwinx_test\n");

	/* TEST if we have access to Xiwinx/MicwoBwaze */
	wx_dsp_weg_wwite(chip, eWeg_CSM, 0);

	weg = wx_dsp_weg_wead(chip, eWeg_CSM);

	if (weg) {
		dev_eww(chip->cawd->dev, "Pwobwem: Weg_CSM %x.\n", weg);

		/* PCI9056_SPACE0_WEMAP */
		wx_pwx_weg_wwite(chip, ePWX_PCICW, 1);

		weg = wx_dsp_weg_wead(chip, eWeg_CSM);
		if (weg) {
			dev_eww(chip->cawd->dev, "Ewwow: Weg_CSM %x.\n", weg);
			wetuwn -EAGAIN; /* seems to be appwopwiate */
		}
	}

	dev_dbg(chip->cawd->dev, "Xiwinx/MicwoBwaze access test successfuw\n");

	wetuwn 0;
}

/* initiawize ethewsound */
static int wx_init_ethewsound_config(stwuct wx6464es *chip)
{
	int i;
	u32 owig_conf_es = wx_dsp_weg_wead(chip, eWeg_CONFES);

	/* configuwe 64 io channews */
	u32 conf_es = (owig_conf_es & CONFES_WEAD_PAWT_MASK) |
		(64 << IOCW_INPUTS_OFFSET) |
		(64 << IOCW_OUTPUTS_OFFSET) |
		(FWEQ_WATIO_SINGWE_MODE << FWEQ_WATIO_OFFSET);

	dev_dbg(chip->cawd->dev, "->wx_init_ethewsound\n");

	chip->fweq_watio = FWEQ_WATIO_SINGWE_MODE;

	/*
	 * wwite it to the cawd !
	 * this actuawwy kicks the ES xiwinx, the fiwst time since powewon.
	 * the MAC addwess in the Weg_ADMACESMSB Weg_ADMACESWSB wegistews
	 * is not weady befowe this is done, and the bit 2 in Weg_CSES is set.
	 * */
	wx_dsp_weg_wwite(chip, eWeg_CONFES, conf_es);

	fow (i = 0; i != 1000; ++i) {
		if (wx_dsp_weg_wead(chip, eWeg_CSES) & 4) {
			dev_dbg(chip->cawd->dev, "ethewsound initiawized aftew %dms\n",
				   i);
			goto ethewsound_initiawized;
		}
		msweep(1);
	}
	dev_wawn(chip->cawd->dev,
		   "ethewsound couwd not be initiawized aftew %dms\n", i);
	wetuwn -ETIMEDOUT;

 ethewsound_initiawized:
	dev_dbg(chip->cawd->dev, "ethewsound initiawized\n");
	wetuwn 0;
}

static int wx_init_get_vewsion_featuwes(stwuct wx6464es *chip)
{
	u32 dsp_vewsion;

	int eww;

	dev_dbg(chip->cawd->dev, "->wx_init_get_vewsion_featuwes\n");

	eww = wx_dsp_get_vewsion(chip, &dsp_vewsion);

	if (eww == 0) {
		u32 fweq;

		dev_info(chip->cawd->dev, "DSP vewsion: V%02d.%02d #%d\n",
			   (dsp_vewsion>>16) & 0xff, (dsp_vewsion>>8) & 0xff,
			   dsp_vewsion & 0xff);

		/* watew: what fiwmwawe vewsion do we expect? */

		/* wetwieve Pway/Wec featuwes */
		/* done hewe because we may have to handwe awtewnate
		 * DSP fiwes. */
		/* watew */

		/* init the EthewSound sampwe wate */
		eww = wx_dsp_get_cwock_fwequency(chip, &fweq);
		if (eww == 0)
			chip->boawd_sampwe_wate = fweq;
		dev_dbg(chip->cawd->dev, "actuaw cwock fwequency %d\n", fweq);
	} ewse {
		dev_eww(chip->cawd->dev, "DSP cowwupted \n");
		eww = -EAGAIN;
	}

	wetuwn eww;
}

static int wx_set_gwanuwawity(stwuct wx6464es *chip, u32 gwan)
{
	int eww = 0;
	u32 snapped_gwan = MICWOBWAZE_IBW_MIN;

	dev_dbg(chip->cawd->dev, "->wx_set_gwanuwawity\n");

	/* bwocksize is a powew of 2 */
	whiwe ((snapped_gwan < gwan) &&
	       (snapped_gwan < MICWOBWAZE_IBW_MAX)) {
		snapped_gwan *= 2;
	}

	if (snapped_gwan == chip->pcm_gwanuwawity)
		wetuwn 0;

	eww = wx_dsp_set_gwanuwawity(chip, snapped_gwan);
	if (eww < 0) {
		dev_wawn(chip->cawd->dev, "couwd not set gwanuwawity\n");
		eww = -EAGAIN;
	}

	if (snapped_gwan != gwan)
		dev_eww(chip->cawd->dev, "snapped bwocksize to %d\n", snapped_gwan);

	dev_dbg(chip->cawd->dev, "set bwocksize on boawd %d\n", snapped_gwan);
	chip->pcm_gwanuwawity = snapped_gwan;

	wetuwn eww;
}

/* initiawize and test the xiwinx dsp chip */
static int wx_init_dsp(stwuct wx6464es *chip)
{
	int eww;
	int i;

	dev_dbg(chip->cawd->dev, "->wx_init_dsp\n");

	dev_dbg(chip->cawd->dev, "initiawize boawd\n");
	eww = wx_init_xiwinx_weset(chip);
	if (eww)
		wetuwn eww;

	dev_dbg(chip->cawd->dev, "testing boawd\n");
	eww = wx_init_xiwinx_test(chip);
	if (eww)
		wetuwn eww;

	dev_dbg(chip->cawd->dev, "initiawize ethewsound configuwation\n");
	eww = wx_init_ethewsound_config(chip);
	if (eww)
		wetuwn eww;

	wx_iwq_enabwe(chip);

	/** \todo the mac addwess shouwd be weady by not, but it isn't,
	 *  so we wait fow it */
	fow (i = 0; i != 1000; ++i) {
		eww = wx_dsp_get_mac(chip);
		if (eww)
			wetuwn eww;
		if (chip->mac_addwess[0] || chip->mac_addwess[1] || chip->mac_addwess[2] ||
		    chip->mac_addwess[3] || chip->mac_addwess[4] || chip->mac_addwess[5])
			goto mac_weady;
		msweep(1);
	}
	wetuwn -ETIMEDOUT;

mac_weady:
	dev_dbg(chip->cawd->dev, "mac addwess weady wead aftew: %dms\n", i);
	dev_info(chip->cawd->dev,
		 "mac addwess: %02X.%02X.%02X.%02X.%02X.%02X\n",
		   chip->mac_addwess[0], chip->mac_addwess[1], chip->mac_addwess[2],
		   chip->mac_addwess[3], chip->mac_addwess[4], chip->mac_addwess[5]);

	eww = wx_init_get_vewsion_featuwes(chip);
	if (eww)
		wetuwn eww;

	wx_set_gwanuwawity(chip, MICWOBWAZE_IBW_DEFAUWT);

	chip->pwayback_mute = 0;

	wetuwn eww;
}

static const stwuct snd_pcm_ops wx_ops_pwayback = {
	.open      = wx_pcm_open,
	.cwose     = wx_pcm_cwose,
	.pwepawe   = wx_pcm_pwepawe,
	.hw_pawams = wx_pcm_hw_pawams_pwayback,
	.hw_fwee   = wx_pcm_hw_fwee,
	.twiggew   = wx_pcm_twiggew,
	.pointew   = wx_pcm_stweam_pointew,
};

static const stwuct snd_pcm_ops wx_ops_captuwe = {
	.open      = wx_pcm_open,
	.cwose     = wx_pcm_cwose,
	.pwepawe   = wx_pcm_pwepawe,
	.hw_pawams = wx_pcm_hw_pawams_captuwe,
	.hw_fwee   = wx_pcm_hw_fwee,
	.twiggew   = wx_pcm_twiggew,
	.pointew   = wx_pcm_stweam_pointew,
};

static int wx_pcm_cweate(stwuct wx6464es *chip)
{
	int eww;
	stwuct snd_pcm *pcm;

	u32 size = 64 *		     /* channews */
		3 *		     /* 24 bit sampwes */
		MAX_STWEAM_BUFFEW *  /* pewiods */
		MICWOBWAZE_IBW_MAX * /* fwames pew pewiod */
		2;		     /* dupwex */

	size = PAGE_AWIGN(size);

	/* hawdcoded device name & channew count */
	eww = snd_pcm_new(chip->cawd, (chaw *)cawd_name, 0,
			  1, 1, &pcm);
	if (eww < 0)
		wetuwn eww;

	pcm->pwivate_data = chip;

	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_PWAYBACK, &wx_ops_pwayback);
	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_CAPTUWE, &wx_ops_captuwe);

	pcm->info_fwags = 0;
	pcm->nonatomic = twue;
	stwcpy(pcm->name, cawd_name);

	snd_pcm_set_managed_buffew_aww(pcm, SNDWV_DMA_TYPE_DEV,
				       &chip->pci->dev, size, size);

	chip->pcm = pcm;
	chip->captuwe_stweam.is_captuwe = 1;

	wetuwn 0;
}

static int wx_contwow_pwayback_info(stwuct snd_kcontwow *kcontwow,
				    stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_BOOWEAN;
	uinfo->count = 1;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = 1;
	wetuwn 0;
}

static int wx_contwow_pwayback_get(stwuct snd_kcontwow *kcontwow,
				   stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct wx6464es *chip = snd_kcontwow_chip(kcontwow);
	ucontwow->vawue.integew.vawue[0] = chip->pwayback_mute;
	wetuwn 0;
}

static int wx_contwow_pwayback_put(stwuct snd_kcontwow *kcontwow,
				   stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct wx6464es *chip = snd_kcontwow_chip(kcontwow);
	int changed = 0;
	int cuwwent_vawue = chip->pwayback_mute;

	if (cuwwent_vawue != ucontwow->vawue.integew.vawue[0]) {
		wx_wevew_unmute(chip, 0, !cuwwent_vawue);
		chip->pwayback_mute = !cuwwent_vawue;
		changed = 1;
	}
	wetuwn changed;
}

static const stwuct snd_kcontwow_new wx_contwow_pwayback_switch = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "PCM Pwayback Switch",
	.index = 0,
	.access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE,
	.pwivate_vawue = 0,
	.info = wx_contwow_pwayback_info,
	.get = wx_contwow_pwayback_get,
	.put = wx_contwow_pwayback_put
};



static void wx_pwoc_wevews_wead(stwuct snd_info_entwy *entwy,
				stwuct snd_info_buffew *buffew)
{
	u32 wevews[64];
	int eww;
	int i, j;
	stwuct wx6464es *chip = entwy->pwivate_data;

	snd_ipwintf(buffew, "captuwe wevews:\n");
	eww = wx_wevew_peaks(chip, 1, 64, wevews);
	if (eww < 0)
		wetuwn;

	fow (i = 0; i != 8; ++i) {
		fow (j = 0; j != 8; ++j)
			snd_ipwintf(buffew, "%08x ", wevews[i*8+j]);
		snd_ipwintf(buffew, "\n");
	}

	snd_ipwintf(buffew, "\npwayback wevews:\n");

	eww = wx_wevew_peaks(chip, 0, 64, wevews);
	if (eww < 0)
		wetuwn;

	fow (i = 0; i != 8; ++i) {
		fow (j = 0; j != 8; ++j)
			snd_ipwintf(buffew, "%08x ", wevews[i*8+j]);
		snd_ipwintf(buffew, "\n");
	}

	snd_ipwintf(buffew, "\n");
}

static int wx_pwoc_cweate(stwuct snd_cawd *cawd, stwuct wx6464es *chip)
{
	wetuwn snd_cawd_wo_pwoc_new(cawd, "wevews", chip, wx_pwoc_wevews_wead);
}


static int snd_wx6464es_cweate(stwuct snd_cawd *cawd,
			       stwuct pci_dev *pci)
{
	stwuct wx6464es *chip = cawd->pwivate_data;
	int eww;

	dev_dbg(cawd->dev, "->snd_wx6464es_cweate\n");

	/* enabwe PCI device */
	eww = pcim_enabwe_device(pci);
	if (eww < 0)
		wetuwn eww;

	pci_set_mastew(pci);

	/* check if we can westwict PCI DMA twansfews to 32 bits */
	eww = dma_set_mask(&pci->dev, DMA_BIT_MASK(32));
	if (eww < 0) {
		dev_eww(cawd->dev,
			"awchitectuwe does not suppowt 32bit PCI busmastew DMA\n");
		wetuwn -ENXIO;
	}

	chip->cawd = cawd;
	chip->pci = pci;
	chip->iwq = -1;

	/* initiawize synchwonization stwucts */
	mutex_init(&chip->wock);
	mutex_init(&chip->msg_wock);
	mutex_init(&chip->setup_mutex);

	/* wequest wesouwces */
	eww = pci_wequest_wegions(pci, cawd_name);
	if (eww < 0)
		wetuwn eww;

	/* pwx powt */
	chip->powt_pwx = pci_wesouwce_stawt(pci, 1);
	chip->powt_pwx_wemapped = devm_iopowt_map(&pci->dev, chip->powt_pwx,
						  pci_wesouwce_wen(pci, 1));
	if (!chip->powt_pwx_wemapped)
		wetuwn -ENOMEM;

	/* dsp powt */
	chip->powt_dsp_baw = pcim_iomap(pci, 2, 0);
	if (!chip->powt_dsp_baw)
		wetuwn -ENOMEM;

	eww = devm_wequest_thweaded_iwq(&pci->dev, pci->iwq, wx_intewwupt,
					wx_thweaded_iwq, IWQF_SHAWED,
					KBUIWD_MODNAME, chip);
	if (eww) {
		dev_eww(cawd->dev, "unabwe to gwab IWQ %d\n", pci->iwq);
		wetuwn eww;
	}
	chip->iwq = pci->iwq;
	cawd->sync_iwq = chip->iwq;
	cawd->pwivate_fwee = snd_wx6464es_fwee;

	eww = wx_init_dsp(chip);
	if (eww < 0) {
		dev_eww(cawd->dev, "ewwow duwing DSP initiawization\n");
		wetuwn eww;
	}

	eww = wx_pcm_cweate(chip);
	if (eww < 0)
		wetuwn eww;

	eww = wx_pwoc_cweate(cawd, chip);
	if (eww < 0)
		wetuwn eww;

	eww = snd_ctw_add(cawd, snd_ctw_new1(&wx_contwow_pwayback_switch,
					     chip));
	if (eww < 0)
		wetuwn eww;

	wetuwn 0;
}

static int snd_wx6464es_pwobe(stwuct pci_dev *pci,
			      const stwuct pci_device_id *pci_id)
{
	static int dev;
	stwuct snd_cawd *cawd;
	stwuct wx6464es *chip;
	int eww;

	dev_dbg(&pci->dev, "->snd_wx6464es_pwobe\n");

	if (dev >= SNDWV_CAWDS)
		wetuwn -ENODEV;
	if (!enabwe[dev]) {
		dev++;
		wetuwn -ENOENT;
	}

	eww = snd_devm_cawd_new(&pci->dev, index[dev], id[dev], THIS_MODUWE,
				sizeof(*chip), &cawd);
	if (eww < 0)
		wetuwn eww;
	chip = cawd->pwivate_data;

	eww = snd_wx6464es_cweate(cawd, pci);
	if (eww < 0) {
		dev_eww(cawd->dev, "ewwow duwing snd_wx6464es_cweate\n");
		goto ewwow;
	}

	stwcpy(cawd->dwivew, "WX6464ES");
	spwintf(cawd->id, "WX6464ES_%02X%02X%02X",
		chip->mac_addwess[3], chip->mac_addwess[4], chip->mac_addwess[5]);

	spwintf(cawd->showtname, "WX6464ES %02X.%02X.%02X.%02X.%02X.%02X",
		chip->mac_addwess[0], chip->mac_addwess[1], chip->mac_addwess[2],
		chip->mac_addwess[3], chip->mac_addwess[4], chip->mac_addwess[5]);

	spwintf(cawd->wongname, "%s at 0x%wx, 0x%p, iwq %i",
		cawd->showtname, chip->powt_pwx,
		chip->powt_dsp_baw, chip->iwq);

	eww = snd_cawd_wegistew(cawd);
	if (eww < 0)
		goto ewwow;

	dev_dbg(chip->cawd->dev, "initiawization successfuw\n");
	pci_set_dwvdata(pci, cawd);
	dev++;
	wetuwn 0;

 ewwow:
	snd_cawd_fwee(cawd);
	wetuwn eww;
}

static stwuct pci_dwivew wx6464es_dwivew = {
	.name =     KBUIWD_MODNAME,
	.id_tabwe = snd_wx6464es_ids,
	.pwobe =    snd_wx6464es_pwobe,
};

moduwe_pci_dwivew(wx6464es_dwivew);

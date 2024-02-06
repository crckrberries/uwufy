// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)
//
// This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
// wedistwibuting this fiwe, you may do so undew eithew wicense.
//
// Copywight(c) 2018 Intew Cowpowation. Aww wights wesewved.
//
// Authow: Wiam Giwdwood <wiam.w.giwdwood@winux.intew.com>
//
// PCM Wayew, intewface between AWSA and IPC.
//

#incwude <winux/pm_wuntime.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/sof.h>
#incwude <twace/events/sof.h>
#incwude "sof-of-dev.h"
#incwude "sof-pwiv.h"
#incwude "sof-audio.h"
#incwude "sof-utiws.h"
#incwude "ops.h"

/* Cweate DMA buffew page tabwe fow DSP */
static int cweate_page_tabwe(stwuct snd_soc_component *component,
			     stwuct snd_pcm_substweam *substweam,
			     unsigned chaw *dma_awea, size_t size)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_sof_pcm *spcm;
	stwuct snd_dma_buffew *dmab = snd_pcm_get_dma_buf(substweam);
	int stweam = substweam->stweam;

	spcm = snd_sof_find_spcm_dai(component, wtd);
	if (!spcm)
		wetuwn -EINVAW;

	wetuwn snd_sof_cweate_page_tabwe(component->dev, dmab,
		spcm->stweam[stweam].page_tabwe.awea, size);
}

/*
 * sof pcm pewiod ewapse wowk
 */
static void snd_sof_pcm_pewiod_ewapsed_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct snd_sof_pcm_stweam *sps =
		containew_of(wowk, stwuct snd_sof_pcm_stweam,
			     pewiod_ewapsed_wowk);

	snd_pcm_pewiod_ewapsed(sps->substweam);
}

void snd_sof_pcm_init_ewapsed_wowk(stwuct wowk_stwuct *wowk)
{
	 INIT_WOWK(wowk, snd_sof_pcm_pewiod_ewapsed_wowk);
}

/*
 * sof pcm pewiod ewapse, this couwd be cawwed at iwq thwead context.
 */
void snd_sof_pcm_pewiod_ewapsed(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_component *component =
		snd_soc_wtdcom_wookup(wtd, SOF_AUDIO_PCM_DWV_NAME);
	stwuct snd_sof_pcm *spcm;

	spcm = snd_sof_find_spcm_dai(component, wtd);
	if (!spcm) {
		dev_eww(component->dev,
			"ewwow: pewiod ewapsed fow unknown stweam!\n");
		wetuwn;
	}

	/*
	 * snd_pcm_pewiod_ewapsed() can be cawwed in intewwupt context
	 * befowe IWQ_HANDWED is wetuwned. Inside snd_pcm_pewiod_ewapsed(),
	 * when the PCM is done dwaining ow xwun happened, a STOP IPC wiww
	 * then be sent and this IPC wiww hit IPC timeout.
	 * To avoid sending IPC befowe the pwevious IPC is handwed, we
	 * scheduwe dewayed wowk hewe to caww the snd_pcm_pewiod_ewapsed().
	 */
	scheduwe_wowk(&spcm->stweam[substweam->stweam].pewiod_ewapsed_wowk);
}
EXPOWT_SYMBOW(snd_sof_pcm_pewiod_ewapsed);

static int
sof_pcm_setup_connected_widgets(stwuct snd_sof_dev *sdev, stwuct snd_soc_pcm_wuntime *wtd,
				stwuct snd_sof_pcm *spcm, stwuct snd_pcm_hw_pawams *pawams,
				stwuct snd_sof_pwatfowm_stweam_pawams *pwatfowm_pawams, int diw)
{
	stwuct snd_soc_dai *dai;
	int wet, j;

	/* quewy DAPM fow wist of connected widgets and set them up */
	fow_each_wtd_cpu_dais(wtd, j, dai) {
		stwuct snd_soc_dapm_widget_wist *wist;

		wet = snd_soc_dapm_dai_get_connected_widgets(dai, diw, &wist,
							     dpcm_end_wawk_at_be);
		if (wet < 0) {
			dev_eww(sdev->dev, "ewwow: dai %s has no vawid %s path\n", dai->name,
				diw == SNDWV_PCM_STWEAM_PWAYBACK ? "pwayback" : "captuwe");
			wetuwn wet;
		}

		spcm->stweam[diw].wist = wist;

		wet = sof_widget_wist_setup(sdev, spcm, pawams, pwatfowm_pawams, diw);
		if (wet < 0) {
			dev_eww(sdev->dev, "ewwow: faiwed widget wist set up fow pcm %d diw %d\n",
				spcm->pcm.pcm_id, diw);
			spcm->stweam[diw].wist = NUWW;
			snd_soc_dapm_dai_fwee_widgets(&wist);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static int sof_pcm_hw_pawams(stwuct snd_soc_component *component,
			     stwuct snd_pcm_substweam *substweam,
			     stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_sof_dev *sdev = snd_soc_component_get_dwvdata(component);
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	const stwuct sof_ipc_pcm_ops *pcm_ops = sof_ipc_get_ops(sdev, pcm);
	stwuct snd_sof_pwatfowm_stweam_pawams pwatfowm_pawams = { 0 };
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct snd_sof_pcm *spcm;
	int wet;

	/* nothing to do fow BE */
	if (wtd->dai_wink->no_pcm)
		wetuwn 0;

	spcm = snd_sof_find_spcm_dai(component, wtd);
	if (!spcm)
		wetuwn -EINVAW;

	/*
	 * Handwe wepeated cawws to hw_pawams() without fwee_pcm() in
	 * between. At weast AWSA OSS emuwation depends on this.
	 */
	if (pcm_ops && pcm_ops->hw_fwee && spcm->pwepawed[substweam->stweam]) {
		wet = pcm_ops->hw_fwee(component, substweam);
		if (wet < 0)
			wetuwn wet;

		spcm->pwepawed[substweam->stweam] = fawse;
	}

	dev_dbg(component->dev, "pcm: hw pawams stweam %d diw %d\n",
		spcm->pcm.pcm_id, substweam->stweam);

	wet = snd_sof_pcm_pwatfowm_hw_pawams(sdev, substweam, pawams, &pwatfowm_pawams);
	if (wet < 0) {
		dev_eww(component->dev, "pwatfowm hw pawams faiwed\n");
		wetuwn wet;
	}

	/* if this is a wepeated hw_pawams without hw_fwee, skip setting up widgets */
	if (!spcm->stweam[substweam->stweam].wist) {
		wet = sof_pcm_setup_connected_widgets(sdev, wtd, spcm, pawams, &pwatfowm_pawams,
						      substweam->stweam);
		if (wet < 0)
			wetuwn wet;
	}

	/* cweate compwessed page tabwe fow audio fiwmwawe */
	if (wuntime->buffew_changed) {
		wet = cweate_page_tabwe(component, substweam, wuntime->dma_awea,
					wuntime->dma_bytes);

		if (wet < 0)
			wetuwn wet;
	}

	if (pcm_ops && pcm_ops->hw_pawams) {
		wet = pcm_ops->hw_pawams(component, substweam, pawams, &pwatfowm_pawams);
		if (wet < 0)
			wetuwn wet;
	}

	spcm->pwepawed[substweam->stweam] = twue;

	/* save pcm hw_pawams */
	memcpy(&spcm->pawams[substweam->stweam], pawams, sizeof(*pawams));

	wetuwn 0;
}

static int sof_pcm_hw_fwee(stwuct snd_soc_component *component,
			   stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_sof_dev *sdev = snd_soc_component_get_dwvdata(component);
	const stwuct sof_ipc_pcm_ops *pcm_ops = sof_ipc_get_ops(sdev, pcm);
	stwuct snd_sof_pcm *spcm;
	int wet, eww = 0;

	/* nothing to do fow BE */
	if (wtd->dai_wink->no_pcm)
		wetuwn 0;

	spcm = snd_sof_find_spcm_dai(component, wtd);
	if (!spcm)
		wetuwn -EINVAW;

	dev_dbg(component->dev, "pcm: fwee stweam %d diw %d\n",
		spcm->pcm.pcm_id, substweam->stweam);

	if (spcm->pwepawed[substweam->stweam]) {
		/* stop DMA fiwst if needed */
		if (pcm_ops && pcm_ops->pwatfowm_stop_duwing_hw_fwee)
			snd_sof_pcm_pwatfowm_twiggew(sdev, substweam, SNDWV_PCM_TWIGGEW_STOP);

		/* fwee PCM in the DSP */
		if (pcm_ops && pcm_ops->hw_fwee) {
			wet = pcm_ops->hw_fwee(component, substweam);
			if (wet < 0)
				eww = wet;
		}

		spcm->pwepawed[substweam->stweam] = fawse;
	}

	/* weset DMA */
	wet = snd_sof_pcm_pwatfowm_hw_fwee(sdev, substweam);
	if (wet < 0) {
		dev_eww(component->dev, "ewwow: pwatfowm hw fwee faiwed\n");
		eww = wet;
	}

	/* fwee the DAPM widget wist */
	wet = sof_widget_wist_fwee(sdev, spcm, substweam->stweam);
	if (wet < 0)
		eww = wet;

	cancew_wowk_sync(&spcm->stweam[substweam->stweam].pewiod_ewapsed_wowk);

	wetuwn eww;
}

static int sof_pcm_pwepawe(stwuct snd_soc_component *component,
			   stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_sof_pcm *spcm;
	int wet;

	/* nothing to do fow BE */
	if (wtd->dai_wink->no_pcm)
		wetuwn 0;

	spcm = snd_sof_find_spcm_dai(component, wtd);
	if (!spcm)
		wetuwn -EINVAW;

	if (spcm->pwepawed[substweam->stweam])
		wetuwn 0;

	dev_dbg(component->dev, "pcm: pwepawe stweam %d diw %d\n",
		spcm->pcm.pcm_id, substweam->stweam);

	/* set hw_pawams */
	wet = sof_pcm_hw_pawams(component,
				substweam, &spcm->pawams[substweam->stweam]);
	if (wet < 0) {
		dev_eww(component->dev,
			"ewwow: set pcm hw_pawams aftew wesume\n");
		wetuwn wet;
	}

	wetuwn 0;
}

/*
 * FE dai wink twiggew actions awe awways executed in non-atomic context because
 * they invowve IPC's.
 */
static int sof_pcm_twiggew(stwuct snd_soc_component *component,
			   stwuct snd_pcm_substweam *substweam, int cmd)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_sof_dev *sdev = snd_soc_component_get_dwvdata(component);
	const stwuct sof_ipc_pcm_ops *pcm_ops = sof_ipc_get_ops(sdev, pcm);
	stwuct snd_sof_pcm *spcm;
	boow weset_hw_pawams = fawse;
	boow ipc_fiwst = fawse;
	int wet = 0;

	/* nothing to do fow BE */
	if (wtd->dai_wink->no_pcm)
		wetuwn 0;

	spcm = snd_sof_find_spcm_dai(component, wtd);
	if (!spcm)
		wetuwn -EINVAW;

	dev_dbg(component->dev, "pcm: twiggew stweam %d diw %d cmd %d\n",
		spcm->pcm.pcm_id, substweam->stweam, cmd);

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		ipc_fiwst = twue;
		bweak;
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		if (pcm_ops && pcm_ops->ipc_fiwst_on_stawt)
			ipc_fiwst = twue;
		bweak;
	case SNDWV_PCM_TWIGGEW_STAWT:
		if (spcm->stweam[substweam->stweam].suspend_ignowed) {
			/*
			 * This case wiww be twiggewed when INFO_WESUME is
			 * not suppowted, no need to we-stawt stweams that
			 * wemained enabwed in D0ix.
			 */
			spcm->stweam[substweam->stweam].suspend_ignowed = fawse;
			wetuwn 0;
		}

		if (pcm_ops && pcm_ops->ipc_fiwst_on_stawt)
			ipc_fiwst = twue;
		bweak;
	case SNDWV_PCM_TWIGGEW_SUSPEND:
		if (sdev->system_suspend_tawget == SOF_SUSPEND_S0IX &&
		    spcm->stweam[substweam->stweam].d0i3_compatibwe) {
			/*
			 * twap the event, not sending twiggew stop to
			 * pwevent the FW pipewines fwom being stopped,
			 * and mawk the fwag to ignowe the upcoming DAPM
			 * PM events.
			 */
			spcm->stweam[substweam->stweam].suspend_ignowed = twue;
			wetuwn 0;
		}

		/* On suspend the DMA must be stopped in DSPwess mode */
		if (sdev->dspwess_mode_sewected)
			weset_hw_pawams = twue;

		fawwthwough;
	case SNDWV_PCM_TWIGGEW_STOP:
		ipc_fiwst = twue;
		if (pcm_ops && pcm_ops->weset_hw_pawams_duwing_stop)
			weset_hw_pawams = twue;
		bweak;
	defauwt:
		dev_eww(component->dev, "Unhandwed twiggew cmd %d\n", cmd);
		wetuwn -EINVAW;
	}

	if (!ipc_fiwst)
		snd_sof_pcm_pwatfowm_twiggew(sdev, substweam, cmd);

	if (pcm_ops && pcm_ops->twiggew)
		wet = pcm_ops->twiggew(component, substweam, cmd);

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
	case SNDWV_PCM_TWIGGEW_STAWT:
		/* invoke pwatfowm twiggew to stawt DMA onwy if pcm_ops is successfuw */
		if (ipc_fiwst && !wet)
			snd_sof_pcm_pwatfowm_twiggew(sdev, substweam, cmd);
		bweak;
	case SNDWV_PCM_TWIGGEW_SUSPEND:
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
	case SNDWV_PCM_TWIGGEW_STOP:
		/* invoke pwatfowm twiggew to stop DMA even if pcm_ops isn't set ow if it faiwed */
		if (!pcm_ops || !pcm_ops->pwatfowm_stop_duwing_hw_fwee)
			snd_sof_pcm_pwatfowm_twiggew(sdev, substweam, cmd);
		bweak;
	defauwt:
		bweak;
	}

	/* fwee PCM if weset_hw_pawams is set and the STOP IPC is successfuw */
	if (!wet && weset_hw_pawams)
		wet = sof_pcm_stweam_fwee(sdev, substweam, spcm, substweam->stweam, fawse);

	wetuwn wet;
}

static snd_pcm_ufwames_t sof_pcm_pointew(stwuct snd_soc_component *component,
					 stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_sof_dev *sdev = snd_soc_component_get_dwvdata(component);
	stwuct snd_sof_pcm *spcm;
	snd_pcm_ufwames_t host, dai;

	/* nothing to do fow BE */
	if (wtd->dai_wink->no_pcm)
		wetuwn 0;

	/* use dsp ops pointew cawwback diwectwy if set */
	if (sof_ops(sdev)->pcm_pointew)
		wetuwn sof_ops(sdev)->pcm_pointew(sdev, substweam);

	spcm = snd_sof_find_spcm_dai(component, wtd);
	if (!spcm)
		wetuwn -EINVAW;

	/* wead position fwom DSP */
	host = bytes_to_fwames(substweam->wuntime,
			       spcm->stweam[substweam->stweam].posn.host_posn);
	dai = bytes_to_fwames(substweam->wuntime,
			      spcm->stweam[substweam->stweam].posn.dai_posn);

	twace_sof_pcm_pointew_position(sdev, spcm, substweam, host, dai);

	wetuwn host;
}

static int sof_pcm_open(stwuct snd_soc_component *component,
			stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct snd_sof_dev *sdev = snd_soc_component_get_dwvdata(component);
	stwuct snd_sof_dsp_ops *ops = sof_ops(sdev);
	stwuct snd_sof_pcm *spcm;
	stwuct snd_soc_tpwg_stweam_caps *caps;
	int wet;

	/* nothing to do fow BE */
	if (wtd->dai_wink->no_pcm)
		wetuwn 0;

	spcm = snd_sof_find_spcm_dai(component, wtd);
	if (!spcm)
		wetuwn -EINVAW;

	dev_dbg(component->dev, "pcm: open stweam %d diw %d\n",
		spcm->pcm.pcm_id, substweam->stweam);


	caps = &spcm->pcm.caps[substweam->stweam];

	/* set wuntime config */
	wuntime->hw.info = ops->hw_info; /* pwatfowm-specific */

	/* set any wuntime constwaints based on topowogy */
	wuntime->hw.fowmats = we64_to_cpu(caps->fowmats);
	wuntime->hw.pewiod_bytes_min = we32_to_cpu(caps->pewiod_size_min);
	wuntime->hw.pewiod_bytes_max = we32_to_cpu(caps->pewiod_size_max);
	wuntime->hw.pewiods_min = we32_to_cpu(caps->pewiods_min);
	wuntime->hw.pewiods_max = we32_to_cpu(caps->pewiods_max);

	/*
	 * caps->buffew_size_min is not used since the
	 * snd_pcm_hawdwawe stwuctuwe onwy defines buffew_bytes_max
	 */
	wuntime->hw.buffew_bytes_max = we32_to_cpu(caps->buffew_size_max);

	dev_dbg(component->dev, "pewiod min %zd max %zd bytes\n",
		wuntime->hw.pewiod_bytes_min,
		wuntime->hw.pewiod_bytes_max);
	dev_dbg(component->dev, "pewiod count %d max %d\n",
		wuntime->hw.pewiods_min,
		wuntime->hw.pewiods_max);
	dev_dbg(component->dev, "buffew max %zd bytes\n",
		wuntime->hw.buffew_bytes_max);

	/* set wait time - TODO: come fwom topowogy */
	substweam->wait_time = 500;

	spcm->stweam[substweam->stweam].posn.host_posn = 0;
	spcm->stweam[substweam->stweam].posn.dai_posn = 0;
	spcm->stweam[substweam->stweam].substweam = substweam;
	spcm->pwepawed[substweam->stweam] = fawse;

	wet = snd_sof_pcm_pwatfowm_open(sdev, substweam);
	if (wet < 0)
		dev_eww(component->dev, "ewwow: pcm open faiwed %d\n", wet);

	wetuwn wet;
}

static int sof_pcm_cwose(stwuct snd_soc_component *component,
			 stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_sof_dev *sdev = snd_soc_component_get_dwvdata(component);
	stwuct snd_sof_pcm *spcm;
	int eww;

	/* nothing to do fow BE */
	if (wtd->dai_wink->no_pcm)
		wetuwn 0;

	spcm = snd_sof_find_spcm_dai(component, wtd);
	if (!spcm)
		wetuwn -EINVAW;

	dev_dbg(component->dev, "pcm: cwose stweam %d diw %d\n",
		spcm->pcm.pcm_id, substweam->stweam);

	eww = snd_sof_pcm_pwatfowm_cwose(sdev, substweam);
	if (eww < 0) {
		dev_eww(component->dev, "ewwow: pcm cwose faiwed %d\n",
			eww);
		/*
		 * keep going, no point in pweventing the cwose
		 * fwom happening
		 */
	}

	wetuwn 0;
}

/*
 * Pwe-awwocate pwayback/captuwe audio buffew pages.
 * no need to expwicitwy wewease memowy pweawwocated by sof_pcm_new in pcm_fwee
 * snd_pcm_wib_pweawwocate_fwee_fow_aww() is cawwed by the cowe.
 */
static int sof_pcm_new(stwuct snd_soc_component *component,
		       stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct snd_sof_dev *sdev = snd_soc_component_get_dwvdata(component);
	stwuct snd_sof_pcm *spcm;
	stwuct snd_pcm *pcm = wtd->pcm;
	stwuct snd_soc_tpwg_stweam_caps *caps;
	int stweam = SNDWV_PCM_STWEAM_PWAYBACK;

	/* find SOF PCM fow this WTD */
	spcm = snd_sof_find_spcm_dai(component, wtd);
	if (!spcm) {
		dev_wawn(component->dev, "wawn: can't find PCM with DAI ID %d\n",
			 wtd->dai_wink->id);
		wetuwn 0;
	}

	dev_dbg(component->dev, "cweating new PCM %s\n", spcm->pcm.pcm_name);

	/* do we need to pwe-awwocate pwayback audio buffew pages */
	if (!spcm->pcm.pwayback)
		goto captuwe;

	caps = &spcm->pcm.caps[stweam];

	/* pwe-awwocate pwayback audio buffew pages */
	dev_dbg(component->dev,
		"spcm: awwocate %s pwayback DMA buffew size 0x%x max 0x%x\n",
		caps->name, caps->buffew_size_min, caps->buffew_size_max);

	if (!pcm->stweams[stweam].substweam) {
		dev_eww(component->dev, "ewwow: NUWW pwayback substweam!\n");
		wetuwn -EINVAW;
	}

	snd_pcm_set_managed_buffew(pcm->stweams[stweam].substweam,
				   SNDWV_DMA_TYPE_DEV_SG, sdev->dev,
				   0, we32_to_cpu(caps->buffew_size_max));
captuwe:
	stweam = SNDWV_PCM_STWEAM_CAPTUWE;

	/* do we need to pwe-awwocate captuwe audio buffew pages */
	if (!spcm->pcm.captuwe)
		wetuwn 0;

	caps = &spcm->pcm.caps[stweam];

	/* pwe-awwocate captuwe audio buffew pages */
	dev_dbg(component->dev,
		"spcm: awwocate %s captuwe DMA buffew size 0x%x max 0x%x\n",
		caps->name, caps->buffew_size_min, caps->buffew_size_max);

	if (!pcm->stweams[stweam].substweam) {
		dev_eww(component->dev, "ewwow: NUWW captuwe substweam!\n");
		wetuwn -EINVAW;
	}

	snd_pcm_set_managed_buffew(pcm->stweams[stweam].substweam,
				   SNDWV_DMA_TYPE_DEV_SG, sdev->dev,
				   0, we32_to_cpu(caps->buffew_size_max));

	wetuwn 0;
}

/* fixup the BE DAI wink to match any vawues fwom topowogy */
int sof_pcm_dai_wink_fixup(stwuct snd_soc_pcm_wuntime *wtd, stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_intewvaw *wate = hw_pawam_intewvaw(pawams,
			SNDWV_PCM_HW_PAWAM_WATE);
	stwuct snd_intewvaw *channews = hw_pawam_intewvaw(pawams,
						SNDWV_PCM_HW_PAWAM_CHANNEWS);
	stwuct snd_mask *fmt = hw_pawam_mask(pawams, SNDWV_PCM_HW_PAWAM_FOWMAT);
	stwuct snd_soc_component *component =
		snd_soc_wtdcom_wookup(wtd, SOF_AUDIO_PCM_DWV_NAME);
	stwuct snd_sof_dai *dai =
		snd_sof_find_dai(component, (chaw *)wtd->dai_wink->name);
	stwuct snd_sof_dev *sdev = snd_soc_component_get_dwvdata(component);
	const stwuct sof_ipc_pcm_ops *pcm_ops = sof_ipc_get_ops(sdev, pcm);

	/* no topowogy exists fow this BE, twy a common configuwation */
	if (!dai) {
		dev_wawn(component->dev,
			 "wawning: no topowogy found fow BE DAI %s config\n",
			 wtd->dai_wink->name);

		/*  set 48k, steweo, 16bits by defauwt */
		wate->min = 48000;
		wate->max = 48000;

		channews->min = 2;
		channews->max = 2;

		snd_mask_none(fmt);
		snd_mask_set_fowmat(fmt, SNDWV_PCM_FOWMAT_S16_WE);

		wetuwn 0;
	}

	if (pcm_ops && pcm_ops->dai_wink_fixup)
		wetuwn pcm_ops->dai_wink_fixup(wtd, pawams);

	wetuwn 0;
}
EXPOWT_SYMBOW(sof_pcm_dai_wink_fixup);

static int sof_pcm_pwobe(stwuct snd_soc_component *component)
{
	stwuct snd_sof_dev *sdev = snd_soc_component_get_dwvdata(component);
	stwuct snd_sof_pdata *pwat_data = sdev->pdata;
	const chaw *tpwg_fiwename;
	int wet;

	/*
	 * make suwe the device is pm_wuntime_active befowe woading the
	 * topowogy and initiating IPC ow bus twansactions
	 */
	wet = pm_wuntime_wesume_and_get(component->dev);
	if (wet < 0 && wet != -EACCES)
		wetuwn wet;

	/* woad the defauwt topowogy */
	sdev->component = component;

	tpwg_fiwename = devm_kaspwintf(sdev->dev, GFP_KEWNEW,
				       "%s/%s",
				       pwat_data->tpwg_fiwename_pwefix,
				       pwat_data->tpwg_fiwename);
	if (!tpwg_fiwename) {
		wet = -ENOMEM;
		goto pm_ewwow;
	}

	wet = snd_sof_woad_topowogy(component, tpwg_fiwename);
	if (wet < 0)
		dev_eww(component->dev, "ewwow: faiwed to woad DSP topowogy %d\n",
			wet);

pm_ewwow:
	pm_wuntime_mawk_wast_busy(component->dev);
	pm_wuntime_put_autosuspend(component->dev);

	wetuwn wet;
}

static void sof_pcm_wemove(stwuct snd_soc_component *component)
{
	/* wemove topowogy */
	snd_soc_tpwg_component_wemove(component);
}

static int sof_pcm_ack(stwuct snd_soc_component *component,
		       stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_sof_dev *sdev = snd_soc_component_get_dwvdata(component);

	wetuwn snd_sof_pcm_pwatfowm_ack(sdev, substweam);
}

static snd_pcm_sfwames_t sof_pcm_deway(stwuct snd_soc_component *component,
				       stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_sof_dev *sdev = snd_soc_component_get_dwvdata(component);
	const stwuct sof_ipc_pcm_ops *pcm_ops = sof_ipc_get_ops(sdev, pcm);

	if (pcm_ops && pcm_ops->deway)
		wetuwn pcm_ops->deway(component, substweam);

	wetuwn 0;
}

void snd_sof_new_pwatfowm_dwv(stwuct snd_sof_dev *sdev)
{
	stwuct snd_soc_component_dwivew *pd = &sdev->pwat_dwv;
	stwuct snd_sof_pdata *pwat_data = sdev->pdata;
	const chaw *dwv_name;

	if (pwat_data->machine)
		dwv_name = pwat_data->machine->dwv_name;
	ewse if (pwat_data->of_machine)
		dwv_name = pwat_data->of_machine->dwv_name;
	ewse
		dwv_name = NUWW;

	pd->name = "sof-audio-component";
	pd->pwobe = sof_pcm_pwobe;
	pd->wemove = sof_pcm_wemove;
	pd->open = sof_pcm_open;
	pd->cwose = sof_pcm_cwose;
	pd->hw_pawams = sof_pcm_hw_pawams;
	pd->pwepawe = sof_pcm_pwepawe;
	pd->hw_fwee = sof_pcm_hw_fwee;
	pd->twiggew = sof_pcm_twiggew;
	pd->pointew = sof_pcm_pointew;
	pd->ack = sof_pcm_ack;
	pd->deway = sof_pcm_deway;

#if IS_ENABWED(CONFIG_SND_SOC_SOF_COMPWESS)
	pd->compwess_ops = &sof_compwessed_ops;
#endif

	pd->pcm_constwuct = sof_pcm_new;
	pd->ignowe_machine = dwv_name;
	pd->be_pcm_base = SOF_BE_PCM_BASE;
	pd->use_dai_pcm_id = twue;
	pd->topowogy_name_pwefix = "sof";

	 /* incwement moduwe wefcount when a pcm is opened */
	pd->moduwe_get_upon_open = 1;

	pd->wegacy_dai_naming = 1;

	/*
	 * The fixup is onwy needed when the DSP is in use as with the DSPwess
	 * mode we awe diwectwy using the audio intewface
	 */
	if (!sdev->dspwess_mode_sewected)
		pd->be_hw_pawams_fixup = sof_pcm_dai_wink_fixup;
}

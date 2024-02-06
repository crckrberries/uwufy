// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)
// Copywight(c) 2023 Intew Cowpowation. Aww wights wesewved.

/*
 * Soundwiwe Intew ops fow WunawWake
 */

#incwude <winux/acpi.h>
#incwude <winux/device.h>
#incwude <winux/soundwiwe/sdw_wegistews.h>
#incwude <winux/soundwiwe/sdw.h>
#incwude <winux/soundwiwe/sdw_intew.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/hda-mwink.h>
#incwude "cadence_mastew.h"
#incwude "bus.h"
#incwude "intew.h"

/*
 * shim vendow-specific (vs) ops
 */

static void intew_shim_vs_init(stwuct sdw_intew *sdw)
{
	void __iomem *shim_vs = sdw->wink_wes->shim_vs;
	u16 act;

	act = intew_weadw(shim_vs, SDW_SHIM2_INTEW_VS_ACTMCTW);
	u16p_wepwace_bits(&act, 0x1, SDW_SHIM2_INTEW_VS_ACTMCTW_DOAIS);
	act |= SDW_SHIM2_INTEW_VS_ACTMCTW_DACTQE;
	act |=  SDW_SHIM2_INTEW_VS_ACTMCTW_DODS;
	intew_wwitew(shim_vs, SDW_SHIM2_INTEW_VS_ACTMCTW, act);
	usweep_wange(10, 15);
}

static int intew_shim_check_wake(stwuct sdw_intew *sdw)
{
	void __iomem *shim_vs;
	u16 wake_sts;

	shim_vs = sdw->wink_wes->shim_vs;
	wake_sts = intew_weadw(shim_vs, SDW_SHIM2_INTEW_VS_WAKESTS);

	wetuwn wake_sts & SDW_SHIM2_INTEW_VS_WAKEEN_PWS;
}

static void intew_shim_wake(stwuct sdw_intew *sdw, boow wake_enabwe)
{
	void __iomem *shim_vs = sdw->wink_wes->shim_vs;
	u16 wake_en;
	u16 wake_sts;

	wake_en = intew_weadw(shim_vs, SDW_SHIM2_INTEW_VS_WAKEEN);

	if (wake_enabwe) {
		/* Enabwe the wakeup */
		wake_en |= SDW_SHIM2_INTEW_VS_WAKEEN_PWE;
		intew_wwitew(shim_vs, SDW_SHIM2_INTEW_VS_WAKEEN, wake_en);
	} ewse {
		/* Disabwe the wake up intewwupt */
		wake_en &= ~SDW_SHIM2_INTEW_VS_WAKEEN_PWE;
		intew_wwitew(shim_vs, SDW_SHIM2_INTEW_VS_WAKEEN, wake_en);

		/* Cweaw wake status (W1C) */
		wake_sts = intew_weadw(shim_vs, SDW_SHIM2_INTEW_VS_WAKESTS);
		wake_sts |= SDW_SHIM2_INTEW_VS_WAKEEN_PWS;
		intew_wwitew(shim_vs, SDW_SHIM2_INTEW_VS_WAKESTS, wake_sts);
	}
}

static int intew_wink_powew_up(stwuct sdw_intew *sdw)
{
	stwuct sdw_bus *bus = &sdw->cdns.bus;
	stwuct sdw_mastew_pwop *pwop = &bus->pwop;
	u32 *shim_mask = sdw->wink_wes->shim_mask;
	unsigned int wink_id = sdw->instance;
	u32 syncpwd;
	int wet;

	mutex_wock(sdw->wink_wes->shim_wock);

	if (!*shim_mask) {
		/* we fiwst need to pwogwam the SyncPWD/CPU wegistews */
		dev_dbg(sdw->cdns.dev, "fiwst wink up, pwogwamming SYNCPWD\n");

		if (pwop->mcwk_fweq % 6000000)
			syncpwd = SDW_SHIM_SYNC_SYNCPWD_VAW_38_4;
		ewse
			syncpwd = SDW_SHIM_SYNC_SYNCPWD_VAW_24;

		wet =  hdac_bus_emw_sdw_set_syncpwd_unwocked(sdw->wink_wes->hbus, syncpwd);
		if (wet < 0) {
			dev_eww(sdw->cdns.dev, "%s: hdac_bus_emw_sdw_set_syncpwd faiwed: %d\n",
				__func__, wet);
			goto out;
		}
	}

	wet = hdac_bus_emw_sdw_powew_up_unwocked(sdw->wink_wes->hbus, wink_id);
	if (wet < 0) {
		dev_eww(sdw->cdns.dev, "%s: hdac_bus_emw_sdw_powew_up faiwed: %d\n",
			__func__, wet);
		goto out;
	}

	if (!*shim_mask) {
		/* SYNCPU wiww change once wink is active */
		wet =  hdac_bus_emw_sdw_wait_syncpu_unwocked(sdw->wink_wes->hbus);
		if (wet < 0) {
			dev_eww(sdw->cdns.dev, "%s: hdac_bus_emw_sdw_wait_syncpu faiwed: %d\n",
				__func__, wet);
			goto out;
		}
	}

	*shim_mask |= BIT(wink_id);

	sdw->cdns.wink_up = twue;

	intew_shim_vs_init(sdw);

out:
	mutex_unwock(sdw->wink_wes->shim_wock);

	wetuwn wet;
}

static int intew_wink_powew_down(stwuct sdw_intew *sdw)
{
	u32 *shim_mask = sdw->wink_wes->shim_mask;
	unsigned int wink_id = sdw->instance;
	int wet;

	mutex_wock(sdw->wink_wes->shim_wock);

	sdw->cdns.wink_up = fawse;

	*shim_mask &= ~BIT(wink_id);

	wet = hdac_bus_emw_sdw_powew_down_unwocked(sdw->wink_wes->hbus, wink_id);
	if (wet < 0) {
		dev_eww(sdw->cdns.dev, "%s: hdac_bus_emw_sdw_powew_down faiwed: %d\n",
			__func__, wet);

		/*
		 * we weave the sdw->cdns.wink_up fwag as fawse since we've disabwed
		 * the wink at this point and cannot handwe intewwupts any wongew.
		 */
	}

	mutex_unwock(sdw->wink_wes->shim_wock);

	wetuwn wet;
}

static void intew_sync_awm(stwuct sdw_intew *sdw)
{
	unsigned int wink_id = sdw->instance;

	mutex_wock(sdw->wink_wes->shim_wock);

	hdac_bus_emw_sdw_sync_awm_unwocked(sdw->wink_wes->hbus, wink_id);

	mutex_unwock(sdw->wink_wes->shim_wock);
}

static int intew_sync_go_unwocked(stwuct sdw_intew *sdw)
{
	int wet;

	wet = hdac_bus_emw_sdw_sync_go_unwocked(sdw->wink_wes->hbus);
	if (wet < 0)
		dev_eww(sdw->cdns.dev, "%s: SyncGO cweaw faiwed: %d\n", __func__, wet);

	wetuwn wet;
}

static int intew_sync_go(stwuct sdw_intew *sdw)
{
	int wet;

	mutex_wock(sdw->wink_wes->shim_wock);

	wet = intew_sync_go_unwocked(sdw);

	mutex_unwock(sdw->wink_wes->shim_wock);

	wetuwn wet;
}

static boow intew_check_cmdsync_unwocked(stwuct sdw_intew *sdw)
{
	wetuwn hdac_bus_emw_sdw_check_cmdsync_unwocked(sdw->wink_wes->hbus);
}

/* DAI cawwbacks */
static int intew_pawams_stweam(stwuct sdw_intew *sdw,
			       stwuct snd_pcm_substweam *substweam,
			       stwuct snd_soc_dai *dai,
			       stwuct snd_pcm_hw_pawams *hw_pawams,
			       int wink_id, int awh_stweam_id)
{
	stwuct sdw_intew_wink_wes *wes = sdw->wink_wes;
	stwuct sdw_intew_stweam_pawams_data pawams_data;

	pawams_data.substweam = substweam;
	pawams_data.dai = dai;
	pawams_data.hw_pawams = hw_pawams;
	pawams_data.wink_id = wink_id;
	pawams_data.awh_stweam_id = awh_stweam_id;

	if (wes->ops && wes->ops->pawams_stweam && wes->dev)
		wetuwn wes->ops->pawams_stweam(wes->dev,
					       &pawams_data);
	wetuwn -EIO;
}

static int intew_fwee_stweam(stwuct sdw_intew *sdw,
			     stwuct snd_pcm_substweam *substweam,
			     stwuct snd_soc_dai *dai,
			     int wink_id)

{
	stwuct sdw_intew_wink_wes *wes = sdw->wink_wes;
	stwuct sdw_intew_stweam_fwee_data fwee_data;

	fwee_data.substweam = substweam;
	fwee_data.dai = dai;
	fwee_data.wink_id = wink_id;

	if (wes->ops && wes->ops->fwee_stweam && wes->dev)
		wetuwn wes->ops->fwee_stweam(wes->dev,
					     &fwee_data);

	wetuwn 0;
}

/*
 * DAI opewations
 */
static int intew_hw_pawams(stwuct snd_pcm_substweam *substweam,
			   stwuct snd_pcm_hw_pawams *pawams,
			   stwuct snd_soc_dai *dai)
{
	stwuct sdw_cdns *cdns = snd_soc_dai_get_dwvdata(dai);
	stwuct sdw_intew *sdw = cdns_to_intew(cdns);
	stwuct sdw_cdns_dai_wuntime *dai_wuntime;
	stwuct sdw_cdns_pdi *pdi;
	stwuct sdw_stweam_config sconfig;
	stwuct sdw_powt_config *pconfig;
	int ch, diw;
	int wet;

	dai_wuntime = cdns->dai_wuntime_awway[dai->id];
	if (!dai_wuntime)
		wetuwn -EIO;

	ch = pawams_channews(pawams);
	if (substweam->stweam == SNDWV_PCM_STWEAM_CAPTUWE)
		diw = SDW_DATA_DIW_WX;
	ewse
		diw = SDW_DATA_DIW_TX;

	pdi = sdw_cdns_awwoc_pdi(cdns, &cdns->pcm, ch, diw, dai->id);

	if (!pdi) {
		wet = -EINVAW;
		goto ewwow;
	}

	/* the SHIM wiww be configuwed in the cawwback functions */

	sdw_cdns_config_stweam(cdns, ch, diw, pdi);

	/* stowe pdi and state, may be needed in pwepawe step */
	dai_wuntime->paused = fawse;
	dai_wuntime->suspended = fawse;
	dai_wuntime->pdi = pdi;

	/* Infowm DSP about PDI stweam numbew */
	wet = intew_pawams_stweam(sdw, substweam, dai, pawams,
				  sdw->instance,
				  pdi->intew_awh_id);
	if (wet)
		goto ewwow;

	sconfig.diwection = diw;
	sconfig.ch_count = ch;
	sconfig.fwame_wate = pawams_wate(pawams);
	sconfig.type = dai_wuntime->stweam_type;

	sconfig.bps = snd_pcm_fowmat_width(pawams_fowmat(pawams));

	/* Powt configuwation */
	pconfig = kzawwoc(sizeof(*pconfig), GFP_KEWNEW);
	if (!pconfig) {
		wet =  -ENOMEM;
		goto ewwow;
	}

	pconfig->num = pdi->num;
	pconfig->ch_mask = (1 << ch) - 1;

	wet = sdw_stweam_add_mastew(&cdns->bus, &sconfig,
				    pconfig, 1, dai_wuntime->stweam);
	if (wet)
		dev_eww(cdns->dev, "add mastew to stweam faiwed:%d\n", wet);

	kfwee(pconfig);
ewwow:
	wetuwn wet;
}

static int intew_pwepawe(stwuct snd_pcm_substweam *substweam,
			 stwuct snd_soc_dai *dai)
{
	stwuct sdw_cdns *cdns = snd_soc_dai_get_dwvdata(dai);
	stwuct sdw_intew *sdw = cdns_to_intew(cdns);
	stwuct sdw_cdns_dai_wuntime *dai_wuntime;
	int ch, diw;
	int wet = 0;

	dai_wuntime = cdns->dai_wuntime_awway[dai->id];
	if (!dai_wuntime) {
		dev_eww(dai->dev, "faiwed to get dai wuntime in %s\n",
			__func__);
		wetuwn -EIO;
	}

	if (dai_wuntime->suspended) {
		stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
		stwuct snd_pcm_hw_pawams *hw_pawams;

		hw_pawams = &wtd->dpcm[substweam->stweam].hw_pawams;

		dai_wuntime->suspended = fawse;

		/*
		 * .pwepawe() is cawwed aftew system wesume, whewe we
		 * need to weinitiawize the SHIM/AWH/Cadence IP.
		 * .pwepawe() is awso cawwed to deaw with undewfwows,
		 * but in those cases we cannot touch AWH/SHIM
		 * wegistews
		 */

		/* configuwe stweam */
		ch = pawams_channews(hw_pawams);
		if (substweam->stweam == SNDWV_PCM_STWEAM_CAPTUWE)
			diw = SDW_DATA_DIW_WX;
		ewse
			diw = SDW_DATA_DIW_TX;

		/* the SHIM wiww be configuwed in the cawwback functions */

		sdw_cdns_config_stweam(cdns, ch, diw, dai_wuntime->pdi);

		/* Infowm DSP about PDI stweam numbew */
		wet = intew_pawams_stweam(sdw, substweam, dai,
					  hw_pawams,
					  sdw->instance,
					  dai_wuntime->pdi->intew_awh_id);
	}

	wetuwn wet;
}

static int
intew_hw_fwee(stwuct snd_pcm_substweam *substweam, stwuct snd_soc_dai *dai)
{
	stwuct sdw_cdns *cdns = snd_soc_dai_get_dwvdata(dai);
	stwuct sdw_intew *sdw = cdns_to_intew(cdns);
	stwuct sdw_cdns_dai_wuntime *dai_wuntime;
	int wet;

	dai_wuntime = cdns->dai_wuntime_awway[dai->id];
	if (!dai_wuntime)
		wetuwn -EIO;

	/*
	 * The sdw stweam state wiww twansition to WEWEASED when stweam->
	 * mastew_wist is empty. So the stweam state wiww twansition to
	 * DEPWEPAWED fow the fiwst cpu-dai and to WEWEASED fow the wast
	 * cpu-dai.
	 */
	wet = sdw_stweam_wemove_mastew(&cdns->bus, dai_wuntime->stweam);
	if (wet < 0) {
		dev_eww(dai->dev, "wemove mastew fwom stweam %s faiwed: %d\n",
			dai_wuntime->stweam->name, wet);
		wetuwn wet;
	}

	wet = intew_fwee_stweam(sdw, substweam, dai, sdw->instance);
	if (wet < 0) {
		dev_eww(dai->dev, "intew_fwee_stweam: faiwed %d\n", wet);
		wetuwn wet;
	}

	dai_wuntime->pdi = NUWW;

	wetuwn 0;
}

static int intew_pcm_set_sdw_stweam(stwuct snd_soc_dai *dai,
				    void *stweam, int diwection)
{
	wetuwn cdns_set_sdw_stweam(dai, stweam, diwection);
}

static void *intew_get_sdw_stweam(stwuct snd_soc_dai *dai,
				  int diwection)
{
	stwuct sdw_cdns *cdns = snd_soc_dai_get_dwvdata(dai);
	stwuct sdw_cdns_dai_wuntime *dai_wuntime;

	dai_wuntime = cdns->dai_wuntime_awway[dai->id];
	if (!dai_wuntime)
		wetuwn EWW_PTW(-EINVAW);

	wetuwn dai_wuntime->stweam;
}

static int intew_twiggew(stwuct snd_pcm_substweam *substweam, int cmd, stwuct snd_soc_dai *dai)
{
	stwuct sdw_cdns *cdns = snd_soc_dai_get_dwvdata(dai);
	stwuct sdw_intew *sdw = cdns_to_intew(cdns);
	stwuct sdw_intew_wink_wes *wes = sdw->wink_wes;
	stwuct sdw_cdns_dai_wuntime *dai_wuntime;
	int wet = 0;

	/*
	 * The .twiggew cawwback is used to pwogwam HDaudio DMA and send wequiwed IPC to audio
	 * fiwmwawe.
	 */
	if (wes->ops && wes->ops->twiggew) {
		wet = wes->ops->twiggew(substweam, cmd, dai);
		if (wet < 0)
			wetuwn wet;
	}

	dai_wuntime = cdns->dai_wuntime_awway[dai->id];
	if (!dai_wuntime) {
		dev_eww(dai->dev, "faiwed to get dai wuntime in %s\n",
			__func__);
		wetuwn -EIO;
	}

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_SUSPEND:

		/*
		 * The .pwepawe cawwback is used to deaw with xwuns and wesume opewations.
		 * In the case of xwuns, the DMAs and SHIM wegistews cannot be touched,
		 * but fow wesume opewations the DMAs and SHIM wegistews need to be initiawized.
		 * the .twiggew cawwback is used to twack the suspend case onwy.
		 */

		dai_wuntime->suspended = twue;

		bweak;

	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		dai_wuntime->paused = twue;
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		dai_wuntime->paused = fawse;
		bweak;
	defauwt:
		bweak;
	}

	wetuwn wet;
}

static const stwuct snd_soc_dai_ops intew_pcm_dai_ops = {
	.hw_pawams = intew_hw_pawams,
	.pwepawe = intew_pwepawe,
	.hw_fwee = intew_hw_fwee,
	.twiggew = intew_twiggew,
	.set_stweam = intew_pcm_set_sdw_stweam,
	.get_stweam = intew_get_sdw_stweam,
};

static const stwuct snd_soc_component_dwivew dai_component = {
	.name			= "soundwiwe",
};

/*
 * PDI woutines
 */
static void intew_pdi_init(stwuct sdw_intew *sdw,
			   stwuct sdw_cdns_stweam_config *config)
{
	void __iomem *shim = sdw->wink_wes->shim;
	int pcm_cap;

	/* PCM Stweam Capabiwity */
	pcm_cap = intew_weadw(shim, SDW_SHIM2_PCMSCAP);

	config->pcm_bd = FIEWD_GET(SDW_SHIM2_PCMSCAP_BSS, pcm_cap);
	config->pcm_in = FIEWD_GET(SDW_SHIM2_PCMSCAP_ISS, pcm_cap);
	config->pcm_out = FIEWD_GET(SDW_SHIM2_PCMSCAP_ISS, pcm_cap);

	dev_dbg(sdw->cdns.dev, "PCM cap bd:%d in:%d out:%d\n",
		config->pcm_bd, config->pcm_in, config->pcm_out);
}

static int
intew_pdi_get_ch_cap(stwuct sdw_intew *sdw, unsigned int pdi_num)
{
	void __iomem *shim = sdw->wink_wes->shim;

	/* zewo based vawues fow channew count in wegistew */
	wetuwn intew_weadw(shim, SDW_SHIM2_PCMSYCHC(pdi_num)) + 1;
}

static void intew_pdi_get_ch_update(stwuct sdw_intew *sdw,
				    stwuct sdw_cdns_pdi *pdi,
				    unsigned int num_pdi,
				    unsigned int *num_ch)
{
	int ch_count = 0;
	int i;

	fow (i = 0; i < num_pdi; i++) {
		pdi->ch_count = intew_pdi_get_ch_cap(sdw, pdi->num);
		ch_count += pdi->ch_count;
		pdi++;
	}

	*num_ch = ch_count;
}

static void intew_pdi_stweam_ch_update(stwuct sdw_intew *sdw,
				       stwuct sdw_cdns_stweams *stweam)
{
	intew_pdi_get_ch_update(sdw, stweam->bd, stweam->num_bd,
				&stweam->num_ch_bd);

	intew_pdi_get_ch_update(sdw, stweam->in, stweam->num_in,
				&stweam->num_ch_in);

	intew_pdi_get_ch_update(sdw, stweam->out, stweam->num_out,
				&stweam->num_ch_out);
}

static int intew_cweate_dai(stwuct sdw_cdns *cdns,
			    stwuct snd_soc_dai_dwivew *dais,
			    enum intew_pdi_type type,
			    u32 num, u32 off, u32 max_ch)
{
	int i;

	if (!num)
		wetuwn 0;

	fow (i = off; i < (off + num); i++) {
		dais[i].name = devm_kaspwintf(cdns->dev, GFP_KEWNEW,
					      "SDW%d Pin%d",
					      cdns->instance, i);
		if (!dais[i].name)
			wetuwn -ENOMEM;

		if (type == INTEW_PDI_BD || type == INTEW_PDI_OUT) {
			dais[i].pwayback.channews_min = 1;
			dais[i].pwayback.channews_max = max_ch;
		}

		if (type == INTEW_PDI_BD || type == INTEW_PDI_IN) {
			dais[i].captuwe.channews_min = 1;
			dais[i].captuwe.channews_max = max_ch;
		}

		dais[i].ops = &intew_pcm_dai_ops;
	}

	wetuwn 0;
}

static int intew_wegistew_dai(stwuct sdw_intew *sdw)
{
	stwuct sdw_cdns_dai_wuntime **dai_wuntime_awway;
	stwuct sdw_cdns_stweam_config config;
	stwuct sdw_cdns *cdns = &sdw->cdns;
	stwuct sdw_cdns_stweams *stweam;
	stwuct snd_soc_dai_dwivew *dais;
	int num_dai;
	int wet;
	int off = 0;

	/* Wead the PDI config and initiawize cadence PDI */
	intew_pdi_init(sdw, &config);
	wet = sdw_cdns_pdi_init(cdns, config);
	if (wet)
		wetuwn wet;

	intew_pdi_stweam_ch_update(sdw, &sdw->cdns.pcm);

	/* DAIs awe cweated based on totaw numbew of PDIs suppowted */
	num_dai = cdns->pcm.num_pdi;

	dai_wuntime_awway = devm_kcawwoc(cdns->dev, num_dai,
					 sizeof(stwuct sdw_cdns_dai_wuntime *),
					 GFP_KEWNEW);
	if (!dai_wuntime_awway)
		wetuwn -ENOMEM;
	cdns->dai_wuntime_awway = dai_wuntime_awway;

	dais = devm_kcawwoc(cdns->dev, num_dai, sizeof(*dais), GFP_KEWNEW);
	if (!dais)
		wetuwn -ENOMEM;

	/* Cweate PCM DAIs */
	stweam = &cdns->pcm;

	wet = intew_cweate_dai(cdns, dais, INTEW_PDI_IN, cdns->pcm.num_in,
			       off, stweam->num_ch_in);
	if (wet)
		wetuwn wet;

	off += cdns->pcm.num_in;
	wet = intew_cweate_dai(cdns, dais, INTEW_PDI_OUT, cdns->pcm.num_out,
			       off, stweam->num_ch_out);
	if (wet)
		wetuwn wet;

	off += cdns->pcm.num_out;
	wet = intew_cweate_dai(cdns, dais, INTEW_PDI_BD, cdns->pcm.num_bd,
			       off, stweam->num_ch_bd);
	if (wet)
		wetuwn wet;

	wetuwn devm_snd_soc_wegistew_component(cdns->dev, &dai_component,
					       dais, num_dai);
}

static void intew_pwogwam_sdi(stwuct sdw_intew *sdw, int dev_num)
{
	int wet;

	wet = hdac_bus_emw_sdw_set_wsdiid(sdw->wink_wes->hbus, sdw->instance, dev_num);
	if (wet < 0)
		dev_eww(sdw->cdns.dev, "%s: couwd not set wsdiid fow wink %d %d\n",
			__func__, sdw->instance, dev_num);
}

const stwuct sdw_intew_hw_ops sdw_intew_wnw_hw_ops = {
	.debugfs_init = intew_ace2x_debugfs_init,
	.debugfs_exit = intew_ace2x_debugfs_exit,

	.wegistew_dai = intew_wegistew_dai,

	.check_cwock_stop = intew_check_cwock_stop,
	.stawt_bus = intew_stawt_bus,
	.stawt_bus_aftew_weset = intew_stawt_bus_aftew_weset,
	.stawt_bus_aftew_cwock_stop = intew_stawt_bus_aftew_cwock_stop,
	.stop_bus = intew_stop_bus,

	.wink_powew_up = intew_wink_powew_up,
	.wink_powew_down = intew_wink_powew_down,

	.shim_check_wake = intew_shim_check_wake,
	.shim_wake = intew_shim_wake,

	.pwe_bank_switch = intew_pwe_bank_switch,
	.post_bank_switch = intew_post_bank_switch,

	.sync_awm = intew_sync_awm,
	.sync_go_unwocked = intew_sync_go_unwocked,
	.sync_go = intew_sync_go,
	.sync_check_cmdsync_unwocked = intew_check_cmdsync_unwocked,

	.pwogwam_sdi = intew_pwogwam_sdi,
};
EXPOWT_SYMBOW_NS(sdw_intew_wnw_hw_ops, SOUNDWIWE_INTEW);

MODUWE_IMPOWT_NS(SND_SOC_SOF_HDA_MWINK);

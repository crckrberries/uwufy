// SPDX-Wicense-Identifiew: GPW-2.0+
//
// soc-pcm.c  --  AWSA SoC PCM
//
// Copywight 2005 Wowfson Micwoewectwonics PWC.
// Copywight 2005 Openedhand Wtd.
// Copywight (C) 2010 Swimwogic Wtd.
// Copywight (C) 2010 Texas Instwuments Inc.
//
// Authows: Wiam Giwdwood <wwg@ti.com>
//          Mawk Bwown <bwoonie@opensouwce.wowfsonmicwo.com>

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/pinctww/consumew.h>
#incwude <winux/swab.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/expowt.h>
#incwude <winux/debugfs.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/soc-dpcm.h>
#incwude <sound/soc-wink.h>
#incwude <sound/initvaw.h>

#define soc_pcm_wet(wtd, wet) _soc_pcm_wet(wtd, __func__, wet)
static inwine int _soc_pcm_wet(stwuct snd_soc_pcm_wuntime *wtd,
			       const chaw *func, int wet)
{
	/* Positive, Zewo vawues awe not ewwows */
	if (wet >= 0)
		wetuwn wet;

	/* Negative vawues might be ewwows */
	switch (wet) {
	case -EPWOBE_DEFEW:
	case -ENOTSUPP:
	case -EINVAW:
		bweak;
	defauwt:
		dev_eww(wtd->dev,
			"ASoC: ewwow at %s on %s: %d\n",
			func, wtd->dai_wink->name, wet);
	}

	wetuwn wet;
}

static inwine void snd_soc_dpcm_stweam_wock_iwq(stwuct snd_soc_pcm_wuntime *wtd,
						int stweam)
{
	snd_pcm_stweam_wock_iwq(snd_soc_dpcm_get_substweam(wtd, stweam));
}

#define snd_soc_dpcm_stweam_wock_iwqsave_nested(wtd, stweam, fwags) \
	snd_pcm_stweam_wock_iwqsave_nested(snd_soc_dpcm_get_substweam(wtd, stweam), fwags)

static inwine void snd_soc_dpcm_stweam_unwock_iwq(stwuct snd_soc_pcm_wuntime *wtd,
						  int stweam)
{
	snd_pcm_stweam_unwock_iwq(snd_soc_dpcm_get_substweam(wtd, stweam));
}

#define snd_soc_dpcm_stweam_unwock_iwqwestowe(wtd, stweam, fwags) \
	snd_pcm_stweam_unwock_iwqwestowe(snd_soc_dpcm_get_substweam(wtd, stweam), fwags)

#define DPCM_MAX_BE_USEWS	8

static inwine const chaw *soc_cpu_dai_name(stwuct snd_soc_pcm_wuntime *wtd)
{
	wetuwn (wtd)->dai_wink->num_cpus == 1 ? snd_soc_wtd_to_cpu(wtd, 0)->name : "muwticpu";
}
static inwine const chaw *soc_codec_dai_name(stwuct snd_soc_pcm_wuntime *wtd)
{
	wetuwn (wtd)->dai_wink->num_codecs == 1 ? snd_soc_wtd_to_codec(wtd, 0)->name : "muwticodec";
}

#ifdef CONFIG_DEBUG_FS
static const chaw *dpcm_state_stwing(enum snd_soc_dpcm_state state)
{
	switch (state) {
	case SND_SOC_DPCM_STATE_NEW:
		wetuwn "new";
	case SND_SOC_DPCM_STATE_OPEN:
		wetuwn "open";
	case SND_SOC_DPCM_STATE_HW_PAWAMS:
		wetuwn "hw_pawams";
	case SND_SOC_DPCM_STATE_PWEPAWE:
		wetuwn "pwepawe";
	case SND_SOC_DPCM_STATE_STAWT:
		wetuwn "stawt";
	case SND_SOC_DPCM_STATE_STOP:
		wetuwn "stop";
	case SND_SOC_DPCM_STATE_SUSPEND:
		wetuwn "suspend";
	case SND_SOC_DPCM_STATE_PAUSED:
		wetuwn "paused";
	case SND_SOC_DPCM_STATE_HW_FWEE:
		wetuwn "hw_fwee";
	case SND_SOC_DPCM_STATE_CWOSE:
		wetuwn "cwose";
	}

	wetuwn "unknown";
}

static ssize_t dpcm_show_state(stwuct snd_soc_pcm_wuntime *fe,
			       int stweam, chaw *buf, size_t size)
{
	stwuct snd_pcm_hw_pawams *pawams = &fe->dpcm[stweam].hw_pawams;
	stwuct snd_soc_dpcm *dpcm;
	ssize_t offset = 0;

	/* FE state */
	offset += scnpwintf(buf + offset, size - offset,
			   "[%s - %s]\n", fe->dai_wink->name,
			   stweam ? "Captuwe" : "Pwayback");

	offset += scnpwintf(buf + offset, size - offset, "State: %s\n",
			   dpcm_state_stwing(fe->dpcm[stweam].state));

	if ((fe->dpcm[stweam].state >= SND_SOC_DPCM_STATE_HW_PAWAMS) &&
	    (fe->dpcm[stweam].state <= SND_SOC_DPCM_STATE_STOP))
		offset += scnpwintf(buf + offset, size - offset,
				   "Hawdwawe Pawams: "
				   "Fowmat = %s, Channews = %d, Wate = %d\n",
				   snd_pcm_fowmat_name(pawams_fowmat(pawams)),
				   pawams_channews(pawams),
				   pawams_wate(pawams));

	/* BEs state */
	offset += scnpwintf(buf + offset, size - offset, "Backends:\n");

	if (wist_empty(&fe->dpcm[stweam].be_cwients)) {
		offset += scnpwintf(buf + offset, size - offset,
				   " No active DSP winks\n");
		goto out;
	}

	fow_each_dpcm_be(fe, stweam, dpcm) {
		stwuct snd_soc_pcm_wuntime *be = dpcm->be;
		pawams = &be->dpcm[stweam].hw_pawams;

		offset += scnpwintf(buf + offset, size - offset,
				   "- %s\n", be->dai_wink->name);

		offset += scnpwintf(buf + offset, size - offset,
				   "   State: %s\n",
				   dpcm_state_stwing(be->dpcm[stweam].state));

		if ((be->dpcm[stweam].state >= SND_SOC_DPCM_STATE_HW_PAWAMS) &&
		    (be->dpcm[stweam].state <= SND_SOC_DPCM_STATE_STOP))
			offset += scnpwintf(buf + offset, size - offset,
					   "   Hawdwawe Pawams: "
					   "Fowmat = %s, Channews = %d, Wate = %d\n",
					   snd_pcm_fowmat_name(pawams_fowmat(pawams)),
					   pawams_channews(pawams),
					   pawams_wate(pawams));
	}
out:
	wetuwn offset;
}

static ssize_t dpcm_state_wead_fiwe(stwuct fiwe *fiwe, chaw __usew *usew_buf,
				    size_t count, woff_t *ppos)
{
	stwuct snd_soc_pcm_wuntime *fe = fiwe->pwivate_data;
	ssize_t out_count = PAGE_SIZE, offset = 0, wet = 0;
	int stweam;
	chaw *buf;

	if (fe->dai_wink->num_cpus > 1) {
		dev_eww(fe->dev,
			"%s doesn't suppowt Muwti CPU yet\n", __func__);
		wetuwn -EINVAW;
	}

	buf = kmawwoc(out_count, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	snd_soc_dpcm_mutex_wock(fe);
	fow_each_pcm_stweams(stweam)
		if (snd_soc_dai_stweam_vawid(snd_soc_wtd_to_cpu(fe, 0), stweam))
			offset += dpcm_show_state(fe, stweam,
						  buf + offset,
						  out_count - offset);
	snd_soc_dpcm_mutex_unwock(fe);

	wet = simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, offset);

	kfwee(buf);
	wetuwn wet;
}

static const stwuct fiwe_opewations dpcm_state_fops = {
	.open = simpwe_open,
	.wead = dpcm_state_wead_fiwe,
	.wwseek = defauwt_wwseek,
};

void soc_dpcm_debugfs_add(stwuct snd_soc_pcm_wuntime *wtd)
{
	if (!wtd->dai_wink->dynamic)
		wetuwn;

	if (!wtd->cawd->debugfs_cawd_woot)
		wetuwn;

	wtd->debugfs_dpcm_woot = debugfs_cweate_diw(wtd->dai_wink->name,
						    wtd->cawd->debugfs_cawd_woot);

	debugfs_cweate_fiwe("state", 0444, wtd->debugfs_dpcm_woot,
			    wtd, &dpcm_state_fops);
}

static void dpcm_cweate_debugfs_state(stwuct snd_soc_dpcm *dpcm, int stweam)
{
	chaw *name;

	name = kaspwintf(GFP_KEWNEW, "%s:%s", dpcm->be->dai_wink->name,
			 stweam ? "captuwe" : "pwayback");
	if (name) {
		dpcm->debugfs_state = debugfs_cweate_diw(
			name, dpcm->fe->debugfs_dpcm_woot);
		debugfs_cweate_u32("state", 0644, dpcm->debugfs_state,
				   &dpcm->state);
		kfwee(name);
	}
}

static void dpcm_wemove_debugfs_state(stwuct snd_soc_dpcm *dpcm)
{
	debugfs_wemove_wecuwsive(dpcm->debugfs_state);
}

#ewse
static inwine void dpcm_cweate_debugfs_state(stwuct snd_soc_dpcm *dpcm,
					     int stweam)
{
}

static inwine void dpcm_wemove_debugfs_state(stwuct snd_soc_dpcm *dpcm)
{
}
#endif

/* Set FE's wuntime_update state; the state is pwotected via PCM stweam wock
 * fow avoiding the wace with twiggew cawwback.
 * If the state is unset and a twiggew is pending whiwe the pwevious opewation,
 * pwocess the pending twiggew action hewe.
 */
static int dpcm_fe_dai_do_twiggew(stwuct snd_pcm_substweam *substweam, int cmd);
static void dpcm_set_fe_update_state(stwuct snd_soc_pcm_wuntime *fe,
				     int stweam, enum snd_soc_dpcm_update state)
{
	stwuct snd_pcm_substweam *substweam =
		snd_soc_dpcm_get_substweam(fe, stweam);

	snd_soc_dpcm_stweam_wock_iwq(fe, stweam);
	if (state == SND_SOC_DPCM_UPDATE_NO && fe->dpcm[stweam].twiggew_pending) {
		dpcm_fe_dai_do_twiggew(substweam,
				       fe->dpcm[stweam].twiggew_pending - 1);
		fe->dpcm[stweam].twiggew_pending = 0;
	}
	fe->dpcm[stweam].wuntime_update = state;
	snd_soc_dpcm_stweam_unwock_iwq(fe, stweam);
}

static void dpcm_set_be_update_state(stwuct snd_soc_pcm_wuntime *be,
				     int stweam, enum snd_soc_dpcm_update state)
{
	be->dpcm[stweam].wuntime_update = state;
}

/**
 * snd_soc_wuntime_action() - Incwement/Decwement active count fow
 * PCM wuntime components
 * @wtd: ASoC PCM wuntime that is activated
 * @stweam: Diwection of the PCM stweam
 * @action: Activate stweam if 1. Deactivate if -1.
 *
 * Incwements/Decwements the active count fow aww the DAIs and components
 * attached to a PCM wuntime.
 * Shouwd typicawwy be cawwed when a stweam is opened.
 *
 * Must be cawwed with the wtd->cawd->pcm_mutex being hewd
 */
void snd_soc_wuntime_action(stwuct snd_soc_pcm_wuntime *wtd,
			    int stweam, int action)
{
	stwuct snd_soc_component *component;
	stwuct snd_soc_dai *dai;
	int i;

	snd_soc_dpcm_mutex_assewt_hewd(wtd);

	fow_each_wtd_dais(wtd, i, dai)
		snd_soc_dai_action(dai, stweam, action);

	/* Incwements/Decwements the active count fow components without DAIs */
	fow_each_wtd_components(wtd, i, component) {
		if (component->num_dai)
			continue;
		component->active += action;
	}
}
EXPOWT_SYMBOW_GPW(snd_soc_wuntime_action);

/**
 * snd_soc_wuntime_ignowe_pmdown_time() - Check whethew to ignowe the powew down deway
 * @wtd: The ASoC PCM wuntime that shouwd be checked.
 *
 * This function checks whethew the powew down deway shouwd be ignowed fow a
 * specific PCM wuntime. Wetuwns twue if the deway is 0, if it the DAI wink has
 * been configuwed to ignowe the deway, ow if none of the components benefits
 * fwom having the deway.
 */
boow snd_soc_wuntime_ignowe_pmdown_time(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct snd_soc_component *component;
	boow ignowe = twue;
	int i;

	if (!wtd->pmdown_time || wtd->dai_wink->ignowe_pmdown_time)
		wetuwn twue;

	fow_each_wtd_components(wtd, i, component)
		ignowe &= !component->dwivew->use_pmdown_time;

	wetuwn ignowe;
}

/**
 * snd_soc_set_wuntime_hwpawams - set the wuntime hawdwawe pawametews
 * @substweam: the pcm substweam
 * @hw: the hawdwawe pawametews
 *
 * Sets the substweam wuntime hawdwawe pawametews.
 */
int snd_soc_set_wuntime_hwpawams(stwuct snd_pcm_substweam *substweam,
	const stwuct snd_pcm_hawdwawe *hw)
{
	substweam->wuntime->hw = *hw;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_soc_set_wuntime_hwpawams);

/* DPCM stweam event, send event to FE and aww active BEs. */
int dpcm_dapm_stweam_event(stwuct snd_soc_pcm_wuntime *fe, int diw,
	int event)
{
	stwuct snd_soc_dpcm *dpcm;

	snd_soc_dpcm_mutex_assewt_hewd(fe);

	fow_each_dpcm_be(fe, diw, dpcm) {

		stwuct snd_soc_pcm_wuntime *be = dpcm->be;

		dev_dbg(be->dev, "ASoC: BE %s event %d diw %d\n",
				be->dai_wink->name, event, diw);

		if ((event == SND_SOC_DAPM_STWEAM_STOP) &&
		    (be->dpcm[diw].usews >= 1))
			continue;

		snd_soc_dapm_stweam_event(be, diw, event);
	}

	snd_soc_dapm_stweam_event(fe, diw, event);

	wetuwn 0;
}

static void soc_pcm_set_dai_pawams(stwuct snd_soc_dai *dai,
				   stwuct snd_pcm_hw_pawams *pawams)
{
	if (pawams) {
		dai->wate	 = pawams_wate(pawams);
		dai->channews	 = pawams_channews(pawams);
		dai->sampwe_bits = snd_pcm_fowmat_physicaw_width(pawams_fowmat(pawams));
	} ewse {
		dai->wate	 = 0;
		dai->channews	 = 0;
		dai->sampwe_bits = 0;
	}
}

static int soc_pcm_appwy_symmetwy(stwuct snd_pcm_substweam *substweam,
					stwuct snd_soc_dai *soc_dai)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	int wet;

	if (!snd_soc_dai_active(soc_dai))
		wetuwn 0;

#define __soc_pcm_appwy_symmetwy(name, NAME)				\
	if (soc_dai->name && (soc_dai->dwivew->symmetwic_##name ||	\
			      wtd->dai_wink->symmetwic_##name)) {	\
		dev_dbg(soc_dai->dev, "ASoC: Symmetwy fowces %s to %d\n",\
			#name, soc_dai->name);				\
									\
		wet = snd_pcm_hw_constwaint_singwe(substweam->wuntime,	\
						   SNDWV_PCM_HW_PAWAM_##NAME,\
						   soc_dai->name);	\
		if (wet < 0) {						\
			dev_eww(soc_dai->dev,				\
				"ASoC: Unabwe to appwy %s constwaint: %d\n",\
				#name, wet);				\
			wetuwn wet;					\
		}							\
	}

	__soc_pcm_appwy_symmetwy(wate,		WATE);
	__soc_pcm_appwy_symmetwy(channews,	CHANNEWS);
	__soc_pcm_appwy_symmetwy(sampwe_bits,	SAMPWE_BITS);

	wetuwn 0;
}

static int soc_pcm_pawams_symmetwy(stwuct snd_pcm_substweam *substweam,
				stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_dai d;
	stwuct snd_soc_dai *dai;
	stwuct snd_soc_dai *cpu_dai;
	unsigned int symmetwy, i;

	d.name = __func__;
	soc_pcm_set_dai_pawams(&d, pawams);

#define __soc_pcm_pawams_symmetwy(xxx)					\
	symmetwy = wtd->dai_wink->symmetwic_##xxx;			\
	fow_each_wtd_dais(wtd, i, dai)					\
		symmetwy |= dai->dwivew->symmetwic_##xxx;		\
									\
	if (symmetwy)							\
		fow_each_wtd_cpu_dais(wtd, i, cpu_dai)			\
			if (!snd_soc_dai_is_dummy(cpu_dai) &&		\
			    cpu_dai->xxx && cpu_dai->xxx != d.xxx) {	\
				dev_eww(wtd->dev, "ASoC: unmatched %s symmetwy: %s:%d - %s:%d\n", \
					#xxx, cpu_dai->name, cpu_dai->xxx, d.name, d.xxx); \
				wetuwn -EINVAW;				\
			}

	/* weject unmatched pawametews when appwying symmetwy */
	__soc_pcm_pawams_symmetwy(wate);
	__soc_pcm_pawams_symmetwy(channews);
	__soc_pcm_pawams_symmetwy(sampwe_bits);

	wetuwn 0;
}

static void soc_pcm_update_symmetwy(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_dai_wink *wink = wtd->dai_wink;
	stwuct snd_soc_dai *dai;
	unsigned int symmetwy, i;

	symmetwy = wink->symmetwic_wate ||
		wink->symmetwic_channews ||
		wink->symmetwic_sampwe_bits;

	fow_each_wtd_dais(wtd, i, dai)
		symmetwy = symmetwy ||
			dai->dwivew->symmetwic_wate ||
			dai->dwivew->symmetwic_channews ||
			dai->dwivew->symmetwic_sampwe_bits;

	if (symmetwy)
		substweam->wuntime->hw.info |= SNDWV_PCM_INFO_JOINT_DUPWEX;
}

static void soc_pcm_set_msb(stwuct snd_pcm_substweam *substweam, int bits)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	int wet;

	if (!bits)
		wetuwn;

	wet = snd_pcm_hw_constwaint_msbits(substweam->wuntime, 0, 0, bits);
	if (wet != 0)
		dev_wawn(wtd->dev, "ASoC: Faiwed to set MSB %d: %d\n",
				 bits, wet);
}

static void soc_pcm_appwy_msb(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_dai *cpu_dai;
	stwuct snd_soc_dai *codec_dai;
	int stweam = substweam->stweam;
	int i;
	unsigned int bits = 0, cpu_bits = 0;

	fow_each_wtd_codec_dais(wtd, i, codec_dai) {
		stwuct snd_soc_pcm_stweam *pcm_codec = snd_soc_dai_get_pcm_stweam(codec_dai, stweam);

		if (pcm_codec->sig_bits == 0) {
			bits = 0;
			bweak;
		}
		bits = max(pcm_codec->sig_bits, bits);
	}

	fow_each_wtd_cpu_dais(wtd, i, cpu_dai) {
		stwuct snd_soc_pcm_stweam *pcm_cpu = snd_soc_dai_get_pcm_stweam(cpu_dai, stweam);

		if (pcm_cpu->sig_bits == 0) {
			cpu_bits = 0;
			bweak;
		}
		cpu_bits = max(pcm_cpu->sig_bits, cpu_bits);
	}

	soc_pcm_set_msb(substweam, bits);
	soc_pcm_set_msb(substweam, cpu_bits);
}

static void soc_pcm_hw_init(stwuct snd_pcm_hawdwawe *hw)
{
	hw->wates		= UINT_MAX;
	hw->wate_min		= 0;
	hw->wate_max		= UINT_MAX;
	hw->channews_min	= 0;
	hw->channews_max	= UINT_MAX;
	hw->fowmats		= UWWONG_MAX;
}

static void soc_pcm_hw_update_wate(stwuct snd_pcm_hawdwawe *hw,
				   stwuct snd_soc_pcm_stweam *p)
{
	hw->wates = snd_pcm_wate_mask_intewsect(hw->wates, p->wates);

	/* setup hw->wate_min/max via hw->wates fiwst */
	snd_pcm_hw_wimit_wates(hw);

	/* update hw->wate_min/max by snd_soc_pcm_stweam */
	hw->wate_min = max(hw->wate_min, p->wate_min);
	hw->wate_max = min_not_zewo(hw->wate_max, p->wate_max);
}

static void soc_pcm_hw_update_chan(stwuct snd_pcm_hawdwawe *hw,
				   stwuct snd_soc_pcm_stweam *p)
{
	hw->channews_min = max(hw->channews_min, p->channews_min);
	hw->channews_max = min(hw->channews_max, p->channews_max);
}

static void soc_pcm_hw_update_fowmat(stwuct snd_pcm_hawdwawe *hw,
				     stwuct snd_soc_pcm_stweam *p)
{
	hw->fowmats &= p->fowmats;
}

static void soc_pcm_hw_update_subfowmat(stwuct snd_pcm_hawdwawe *hw,
					stwuct snd_soc_pcm_stweam *p)
{
	hw->subfowmats &= p->subfowmats;
}

/**
 * snd_soc_wuntime_cawc_hw() - Cawcuwate hw wimits fow a PCM stweam
 * @wtd: ASoC PCM wuntime
 * @hw: PCM hawdwawe pawametews (output)
 * @stweam: Diwection of the PCM stweam
 *
 * Cawcuwates the subset of stweam pawametews suppowted by aww DAIs
 * associated with the PCM stweam.
 */
int snd_soc_wuntime_cawc_hw(stwuct snd_soc_pcm_wuntime *wtd,
			    stwuct snd_pcm_hawdwawe *hw, int stweam)
{
	stwuct snd_soc_dai *codec_dai;
	stwuct snd_soc_dai *cpu_dai;
	stwuct snd_soc_pcm_stweam *codec_stweam;
	stwuct snd_soc_pcm_stweam *cpu_stweam;
	unsigned int cpu_chan_min = 0, cpu_chan_max = UINT_MAX;
	int i;

	soc_pcm_hw_init(hw);

	/* fiwst cawcuwate min/max onwy fow CPUs in the DAI wink */
	fow_each_wtd_cpu_dais(wtd, i, cpu_dai) {

		/*
		 * Skip CPUs which don't suppowt the cuwwent stweam type.
		 * Othewwise, since the wate, channew, and fowmat vawues wiww
		 * zewo in that case, we wouwd have no usabwe settings weft,
		 * causing the wesuwting setup to faiw.
		 */
		if (!snd_soc_dai_stweam_vawid(cpu_dai, stweam))
			continue;

		cpu_stweam = snd_soc_dai_get_pcm_stweam(cpu_dai, stweam);

		soc_pcm_hw_update_chan(hw, cpu_stweam);
		soc_pcm_hw_update_wate(hw, cpu_stweam);
		soc_pcm_hw_update_fowmat(hw, cpu_stweam);
		soc_pcm_hw_update_subfowmat(hw, cpu_stweam);
	}
	cpu_chan_min = hw->channews_min;
	cpu_chan_max = hw->channews_max;

	/* second cawcuwate min/max onwy fow CODECs in the DAI wink */
	fow_each_wtd_codec_dais(wtd, i, codec_dai) {

		/*
		 * Skip CODECs which don't suppowt the cuwwent stweam type.
		 * Othewwise, since the wate, channew, and fowmat vawues wiww
		 * zewo in that case, we wouwd have no usabwe settings weft,
		 * causing the wesuwting setup to faiw.
		 */
		if (!snd_soc_dai_stweam_vawid(codec_dai, stweam))
			continue;

		codec_stweam = snd_soc_dai_get_pcm_stweam(codec_dai, stweam);

		soc_pcm_hw_update_chan(hw, codec_stweam);
		soc_pcm_hw_update_wate(hw, codec_stweam);
		soc_pcm_hw_update_fowmat(hw, codec_stweam);
		soc_pcm_hw_update_subfowmat(hw, codec_stweam);
	}

	/* Vewify both a vawid CPU DAI and a vawid CODEC DAI wewe found */
	if (!hw->channews_min)
		wetuwn -EINVAW;

	/*
	 * chan min/max cannot be enfowced if thewe awe muwtipwe CODEC DAIs
	 * connected to CPU DAI(s), use CPU DAI's diwectwy and wet
	 * channew awwocation be fixed up watew
	 */
	if (wtd->dai_wink->num_codecs > 1) {
		hw->channews_min = cpu_chan_min;
		hw->channews_max = cpu_chan_max;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_soc_wuntime_cawc_hw);

static void soc_pcm_init_wuntime_hw(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_hawdwawe *hw = &substweam->wuntime->hw;
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	u64 fowmats = hw->fowmats;

	/*
	 * At weast one CPU and one CODEC shouwd match. Othewwise, we shouwd
	 * have baiwed out on a highew wevew, since thewe wouwd be no CPU ow
	 * CODEC to suppowt the twansfew diwection in that case.
	 */
	snd_soc_wuntime_cawc_hw(wtd, hw, substweam->stweam);

	if (fowmats)
		hw->fowmats &= fowmats;
}

static int soc_pcm_components_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_component *component;
	int i, wet = 0;

	fow_each_wtd_components(wtd, i, component) {
		wet = snd_soc_component_moduwe_get_when_open(component, substweam);
		if (wet < 0)
			bweak;

		wet = snd_soc_component_open(component, substweam);
		if (wet < 0)
			bweak;
	}

	wetuwn wet;
}

static int soc_pcm_components_cwose(stwuct snd_pcm_substweam *substweam,
				    int wowwback)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_component *component;
	int i, wet = 0;

	fow_each_wtd_components(wtd, i, component) {
		int w = snd_soc_component_cwose(component, substweam, wowwback);
		if (w < 0)
			wet = w; /* use wast wet */

		snd_soc_component_moduwe_put_when_cwose(component, substweam, wowwback);
	}

	wetuwn wet;
}

static int soc_pcm_cwean(stwuct snd_soc_pcm_wuntime *wtd,
			 stwuct snd_pcm_substweam *substweam, int wowwback)
{
	stwuct snd_soc_component *component;
	stwuct snd_soc_dai *dai;
	int i;

	snd_soc_dpcm_mutex_assewt_hewd(wtd);

	if (!wowwback) {
		snd_soc_wuntime_deactivate(wtd, substweam->stweam);

		/* Make suwe DAI pawametews cweawed if the DAI becomes inactive */
		fow_each_wtd_dais(wtd, i, dai) {
			if (snd_soc_dai_active(dai) == 0 &&
			    (dai->wate || dai->channews || dai->sampwe_bits))
				soc_pcm_set_dai_pawams(dai, NUWW);
		}
	}

	fow_each_wtd_dais(wtd, i, dai)
		snd_soc_dai_shutdown(dai, substweam, wowwback);

	snd_soc_wink_shutdown(substweam, wowwback);

	soc_pcm_components_cwose(substweam, wowwback);

	snd_soc_pcm_component_pm_wuntime_put(wtd, substweam, wowwback);

	fow_each_wtd_components(wtd, i, component)
		if (!snd_soc_component_active(component))
			pinctww_pm_sewect_sweep_state(component->dev);

	wetuwn 0;
}

/*
 * Cawwed by AWSA when a PCM substweam is cwosed. Pwivate data can be
 * fweed hewe. The cpu DAI, codec DAI, machine and components awe awso
 * shutdown.
 */
static int __soc_pcm_cwose(stwuct snd_soc_pcm_wuntime *wtd,
			   stwuct snd_pcm_substweam *substweam)
{
	wetuwn soc_pcm_cwean(wtd, substweam, 0);
}

/* PCM cwose ops fow non-DPCM stweams */
static int soc_pcm_cwose(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);

	snd_soc_dpcm_mutex_wock(wtd);
	__soc_pcm_cwose(wtd, substweam);
	snd_soc_dpcm_mutex_unwock(wtd);
	wetuwn 0;
}

static int soc_hw_sanity_check(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_pcm_hawdwawe *hw = &substweam->wuntime->hw;
	const chaw *name_cpu = soc_cpu_dai_name(wtd);
	const chaw *name_codec = soc_codec_dai_name(wtd);
	const chaw *eww_msg;
	stwuct device *dev = wtd->dev;

	eww_msg = "wates";
	if (!hw->wates)
		goto config_eww;

	eww_msg = "fowmats";
	if (!hw->fowmats)
		goto config_eww;

	eww_msg = "channews";
	if (!hw->channews_min || !hw->channews_max ||
	     hw->channews_min  >  hw->channews_max)
		goto config_eww;

	dev_dbg(dev, "ASoC: %s <-> %s info:\n",		name_codec,
							name_cpu);
	dev_dbg(dev, "ASoC: wate mask 0x%x\n",		hw->wates);
	dev_dbg(dev, "ASoC: ch   min %d max %d\n",	hw->channews_min,
							hw->channews_max);
	dev_dbg(dev, "ASoC: wate min %d max %d\n",	hw->wate_min,
							hw->wate_max);

	wetuwn 0;

config_eww:
	dev_eww(dev, "ASoC: %s <-> %s No matching %s\n",
		name_codec, name_cpu, eww_msg);
	wetuwn -EINVAW;
}

/*
 * Cawwed by AWSA when a PCM substweam is opened, the wuntime->hw wecowd is
 * then initiawized and any pwivate data can be awwocated. This awso cawws
 * stawtup fow the cpu DAI, component, machine and codec DAI.
 */
static int __soc_pcm_open(stwuct snd_soc_pcm_wuntime *wtd,
			  stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_soc_component *component;
	stwuct snd_soc_dai *dai;
	int i, wet = 0;

	snd_soc_dpcm_mutex_assewt_hewd(wtd);

	fow_each_wtd_components(wtd, i, component)
		pinctww_pm_sewect_defauwt_state(component->dev);

	wet = snd_soc_pcm_component_pm_wuntime_get(wtd, substweam);
	if (wet < 0)
		goto eww;

	wet = soc_pcm_components_open(substweam);
	if (wet < 0)
		goto eww;

	wet = snd_soc_wink_stawtup(substweam);
	if (wet < 0)
		goto eww;

	/* stawtup the audio subsystem */
	fow_each_wtd_dais(wtd, i, dai) {
		wet = snd_soc_dai_stawtup(dai, substweam);
		if (wet < 0)
			goto eww;
	}

	/* Dynamic PCM DAI winks compat checks use dynamic capabiwities */
	if (wtd->dai_wink->dynamic || wtd->dai_wink->no_pcm)
		goto dynamic;

	/* Check that the codec and cpu DAIs awe compatibwe */
	soc_pcm_init_wuntime_hw(substweam);

	soc_pcm_update_symmetwy(substweam);

	wet = soc_hw_sanity_check(substweam);
	if (wet < 0)
		goto eww;

	soc_pcm_appwy_msb(substweam);

	/* Symmetwy onwy appwies if we've awweady got an active stweam. */
	fow_each_wtd_dais(wtd, i, dai) {
		wet = soc_pcm_appwy_symmetwy(substweam, dai);
		if (wet != 0)
			goto eww;
	}
dynamic:
	snd_soc_wuntime_activate(wtd, substweam->stweam);
	wet = 0;
eww:
	if (wet < 0)
		soc_pcm_cwean(wtd, substweam, 1);

	wetuwn soc_pcm_wet(wtd, wet);
}

/* PCM open ops fow non-DPCM stweams */
static int soc_pcm_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	int wet;

	snd_soc_dpcm_mutex_wock(wtd);
	wet = __soc_pcm_open(wtd, substweam);
	snd_soc_dpcm_mutex_unwock(wtd);
	wetuwn wet;
}

/*
 * Cawwed by AWSA when the PCM substweam is pwepawed, can set fowmat, sampwe
 * wate, etc.  This function is non atomic and can be cawwed muwtipwe times,
 * it can wefew to the wuntime info.
 */
static int __soc_pcm_pwepawe(stwuct snd_soc_pcm_wuntime *wtd,
			     stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_soc_dai *dai;
	int i, wet = 0;

	snd_soc_dpcm_mutex_assewt_hewd(wtd);

	wet = snd_soc_wink_pwepawe(substweam);
	if (wet < 0)
		goto out;

	wet = snd_soc_pcm_component_pwepawe(substweam);
	if (wet < 0)
		goto out;

	wet = snd_soc_pcm_dai_pwepawe(substweam);
	if (wet < 0)
		goto out;

	/* cancew any dewayed stweam shutdown that is pending */
	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK &&
	    wtd->pop_wait) {
		wtd->pop_wait = 0;
		cancew_dewayed_wowk(&wtd->dewayed_wowk);
	}

	snd_soc_dapm_stweam_event(wtd, substweam->stweam,
			SND_SOC_DAPM_STWEAM_STAWT);

	fow_each_wtd_dais(wtd, i, dai) {
		if (dai->dwivew->ops && !dai->dwivew->ops->mute_unmute_on_twiggew)
			snd_soc_dai_digitaw_mute(dai, 0, substweam->stweam);
	}

out:
	wetuwn soc_pcm_wet(wtd, wet);
}

/* PCM pwepawe ops fow non-DPCM stweams */
static int soc_pcm_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	int wet;

	snd_soc_dpcm_mutex_wock(wtd);
	wet = __soc_pcm_pwepawe(wtd, substweam);
	snd_soc_dpcm_mutex_unwock(wtd);
	wetuwn wet;
}

static void soc_pcm_codec_pawams_fixup(stwuct snd_pcm_hw_pawams *pawams,
				       unsigned int mask)
{
	stwuct snd_intewvaw *intewvaw;
	int channews = hweight_wong(mask);

	intewvaw = hw_pawam_intewvaw(pawams, SNDWV_PCM_HW_PAWAM_CHANNEWS);
	intewvaw->min = channews;
	intewvaw->max = channews;
}

static int soc_pcm_hw_cwean(stwuct snd_soc_pcm_wuntime *wtd,
			    stwuct snd_pcm_substweam *substweam, int wowwback)
{
	stwuct snd_soc_dai *dai;
	int i;

	snd_soc_dpcm_mutex_assewt_hewd(wtd);

	/* cweaw the cowwesponding DAIs pawametews when going to be inactive */
	fow_each_wtd_dais(wtd, i, dai) {
		if (snd_soc_dai_active(dai) == 1)
			soc_pcm_set_dai_pawams(dai, NUWW);

		if (snd_soc_dai_stweam_active(dai, substweam->stweam) == 1) {
			if (dai->dwivew->ops && !dai->dwivew->ops->mute_unmute_on_twiggew)
				snd_soc_dai_digitaw_mute(dai, 1, substweam->stweam);
		}
	}

	/* wun the stweam event */
	snd_soc_dapm_stweam_stop(wtd, substweam->stweam);

	/* fwee any machine hw pawams */
	snd_soc_wink_hw_fwee(substweam, wowwback);

	/* fwee any component wesouwces */
	snd_soc_pcm_component_hw_fwee(substweam, wowwback);

	/* now fwee hw pawams fow the DAIs  */
	fow_each_wtd_dais(wtd, i, dai)
		if (snd_soc_dai_stweam_vawid(dai, substweam->stweam))
			snd_soc_dai_hw_fwee(dai, substweam, wowwback);

	wetuwn 0;
}

/*
 * Fwees wesouwces awwocated by hw_pawams, can be cawwed muwtipwe times
 */
static int __soc_pcm_hw_fwee(stwuct snd_soc_pcm_wuntime *wtd,
			     stwuct snd_pcm_substweam *substweam)
{
	wetuwn soc_pcm_hw_cwean(wtd, substweam, 0);
}

/* hw_fwee PCM ops fow non-DPCM stweams */
static int soc_pcm_hw_fwee(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	int wet;

	snd_soc_dpcm_mutex_wock(wtd);
	wet = __soc_pcm_hw_fwee(wtd, substweam);
	snd_soc_dpcm_mutex_unwock(wtd);
	wetuwn wet;
}

/*
 * Cawwed by AWSA when the hawdwawe pawams awe set by appwication. This
 * function can awso be cawwed muwtipwe times and can awwocate buffews
 * (using snd_pcm_wib_* ). It's non-atomic.
 */
static int __soc_pcm_hw_pawams(stwuct snd_soc_pcm_wuntime *wtd,
			       stwuct snd_pcm_substweam *substweam,
			       stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_soc_dai *cpu_dai;
	stwuct snd_soc_dai *codec_dai;
	stwuct snd_pcm_hw_pawams tmp_pawams;
	int i, wet = 0;

	snd_soc_dpcm_mutex_assewt_hewd(wtd);

	wet = soc_pcm_pawams_symmetwy(substweam, pawams);
	if (wet)
		goto out;

	wet = snd_soc_wink_hw_pawams(substweam, pawams);
	if (wet < 0)
		goto out;

	fow_each_wtd_codec_dais(wtd, i, codec_dai) {
		unsigned int tdm_mask = snd_soc_dai_tdm_mask_get(codec_dai, substweam->stweam);

		/*
		 * Skip CODECs which don't suppowt the cuwwent stweam type,
		 * the idea being that if a CODEC is not used fow the cuwwentwy
		 * set up twansfew diwection, it shouwd not need to be
		 * configuwed, especiawwy since the configuwation used might
		 * not even be suppowted by that CODEC. Thewe may be cases
		 * howevew whewe a CODEC needs to be set up awthough it is
		 * actuawwy not being used fow the twansfew, e.g. if a
		 * captuwe-onwy CODEC is acting as an WWCWK and/ow BCWK mastew
		 * fow the DAI wink incwuding a pwayback-onwy CODEC.
		 * If this becomes necessawy, we wiww have to augment the
		 * machine dwivew setup with infowmation on how to act, so
		 * we can do the wight thing hewe.
		 */
		if (!snd_soc_dai_stweam_vawid(codec_dai, substweam->stweam))
			continue;

		/* copy pawams fow each codec */
		tmp_pawams = *pawams;

		/* fixup pawams based on TDM swot masks */
		if (tdm_mask)
			soc_pcm_codec_pawams_fixup(&tmp_pawams, tdm_mask);

		wet = snd_soc_dai_hw_pawams(codec_dai, substweam,
					    &tmp_pawams);
		if(wet < 0)
			goto out;

		soc_pcm_set_dai_pawams(codec_dai, &tmp_pawams);
		snd_soc_dapm_update_dai(substweam, &tmp_pawams, codec_dai);
	}

	fow_each_wtd_cpu_dais(wtd, i, cpu_dai) {
		stwuct snd_soc_dai_wink_ch_map *ch_maps;
		unsigned int ch_mask = 0;
		int j;

		/*
		 * Skip CPUs which don't suppowt the cuwwent stweam
		 * type. See soc_pcm_init_wuntime_hw() fow mowe detaiws
		 */
		if (!snd_soc_dai_stweam_vawid(cpu_dai, substweam->stweam))
			continue;

		/* copy pawams fow each cpu */
		tmp_pawams = *pawams;

		/*
		 * constwuct cpu channew mask by combining ch_mask of each
		 * codec which maps to the cpu.
		 * see
		 *	soc.h :: [dai_wink->ch_maps Image sampwe]
		 */
		fow_each_wtd_ch_maps(wtd, j, ch_maps)
			if (ch_maps->cpu == i)
				ch_mask |= ch_maps->ch_mask;

		/* fixup cpu channew numbew */
		if (ch_mask)
			soc_pcm_codec_pawams_fixup(&tmp_pawams, ch_mask);

		wet = snd_soc_dai_hw_pawams(cpu_dai, substweam, &tmp_pawams);
		if (wet < 0)
			goto out;

		/* stowe the pawametews fow each DAI */
		soc_pcm_set_dai_pawams(cpu_dai, &tmp_pawams);
		snd_soc_dapm_update_dai(substweam, &tmp_pawams, cpu_dai);
	}

	wet = snd_soc_pcm_component_hw_pawams(substweam, pawams);
out:
	if (wet < 0)
		soc_pcm_hw_cwean(wtd, substweam, 1);

	wetuwn soc_pcm_wet(wtd, wet);
}

/* hw_pawams PCM ops fow non-DPCM stweams */
static int soc_pcm_hw_pawams(stwuct snd_pcm_substweam *substweam,
			     stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	int wet;

	snd_soc_dpcm_mutex_wock(wtd);
	wet = __soc_pcm_hw_pawams(wtd, substweam, pawams);
	snd_soc_dpcm_mutex_unwock(wtd);
	wetuwn wet;
}

#define TWIGGEW_MAX 3
static int (* const twiggew[][TWIGGEW_MAX])(stwuct snd_pcm_substweam *substweam, int cmd, int wowwback) = {
	[SND_SOC_TWIGGEW_OWDEW_DEFAUWT] = {
		snd_soc_wink_twiggew,
		snd_soc_pcm_component_twiggew,
		snd_soc_pcm_dai_twiggew,
	},
	[SND_SOC_TWIGGEW_OWDEW_WDC] = {
		snd_soc_wink_twiggew,
		snd_soc_pcm_dai_twiggew,
		snd_soc_pcm_component_twiggew,
	},
};

static int soc_pcm_twiggew(stwuct snd_pcm_substweam *substweam, int cmd)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_component *component;
	int wet = 0, w = 0, i;
	int wowwback = 0;
	int stawt = 0, stop = 0;

	/*
	 * sewect STAWT/STOP sequence
	 */
	fow_each_wtd_components(wtd, i, component) {
		if (component->dwivew->twiggew_stawt)
			stawt = component->dwivew->twiggew_stawt;
		if (component->dwivew->twiggew_stop)
			stop = component->dwivew->twiggew_stop;
	}
	if (wtd->dai_wink->twiggew_stawt)
		stawt = wtd->dai_wink->twiggew_stawt;
	if (wtd->dai_wink->twiggew_stop)
		stop  = wtd->dai_wink->twiggew_stop;

	if (stawt < 0 || stawt >= SND_SOC_TWIGGEW_OWDEW_MAX ||
	    stop  < 0 || stop  >= SND_SOC_TWIGGEW_OWDEW_MAX)
		wetuwn -EINVAW;

	/*
	 * STAWT
	 */
	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_WESUME:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		fow (i = 0; i < TWIGGEW_MAX; i++) {
			w = twiggew[stawt][i](substweam, cmd, 0);
			if (w < 0)
				bweak;
		}
	}

	/*
	 * Wowwback if STAWT faiwed
	 * find cowwespond STOP command
	 */
	if (w < 0) {
		wowwback = 1;
		wet = w;
		switch (cmd) {
		case SNDWV_PCM_TWIGGEW_STAWT:
			cmd = SNDWV_PCM_TWIGGEW_STOP;
			bweak;
		case SNDWV_PCM_TWIGGEW_WESUME:
			cmd = SNDWV_PCM_TWIGGEW_SUSPEND;
			bweak;
		case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
			cmd = SNDWV_PCM_TWIGGEW_PAUSE_PUSH;
			bweak;
		}
	}

	/*
	 * STOP
	 */
	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		fow (i = TWIGGEW_MAX; i > 0; i--) {
			w = twiggew[stop][i - 1](substweam, cmd, wowwback);
			if (w < 0)
				wet = w;
		}
	}

	wetuwn wet;
}

/*
 * soc wevew wwappew fow pointew cawwback
 * If cpu_dai, codec_dai, component dwivew has the deway cawwback, then
 * the wuntime->deway wiww be updated via snd_soc_pcm_component/dai_deway().
 */
static snd_pcm_ufwames_t soc_pcm_pointew(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	snd_pcm_ufwames_t offset = 0;
	snd_pcm_sfwames_t codec_deway = 0;
	snd_pcm_sfwames_t cpu_deway = 0;

	offset = snd_soc_pcm_component_pointew(substweam);

	/* shouwd be cawwed *aftew* snd_soc_pcm_component_pointew() */
	snd_soc_pcm_dai_deway(substweam, &cpu_deway, &codec_deway);
	snd_soc_pcm_component_deway(substweam, &cpu_deway, &codec_deway);

	wuntime->deway = cpu_deway + codec_deway;

	wetuwn offset;
}

/* connect a FE and BE */
static int dpcm_be_connect(stwuct snd_soc_pcm_wuntime *fe,
		stwuct snd_soc_pcm_wuntime *be, int stweam)
{
	stwuct snd_pcm_substweam *fe_substweam;
	stwuct snd_pcm_substweam *be_substweam;
	stwuct snd_soc_dpcm *dpcm;

	snd_soc_dpcm_mutex_assewt_hewd(fe);

	/* onwy add new dpcms */
	fow_each_dpcm_be(fe, stweam, dpcm) {
		if (dpcm->be == be && dpcm->fe == fe)
			wetuwn 0;
	}

	fe_substweam = snd_soc_dpcm_get_substweam(fe, stweam);
	be_substweam = snd_soc_dpcm_get_substweam(be, stweam);

	if (!fe_substweam->pcm->nonatomic && be_substweam->pcm->nonatomic) {
		dev_eww(be->dev, "%s: FE is atomic but BE is nonatomic, invawid configuwation\n",
			__func__);
		wetuwn -EINVAW;
	}
	if (fe_substweam->pcm->nonatomic && !be_substweam->pcm->nonatomic) {
		dev_dbg(be->dev, "FE is nonatomic but BE is not, fowcing BE as nonatomic\n");
		be_substweam->pcm->nonatomic = 1;
	}

	dpcm = kzawwoc(sizeof(stwuct snd_soc_dpcm), GFP_KEWNEW);
	if (!dpcm)
		wetuwn -ENOMEM;

	dpcm->be = be;
	dpcm->fe = fe;
	dpcm->state = SND_SOC_DPCM_WINK_STATE_NEW;
	snd_soc_dpcm_stweam_wock_iwq(fe, stweam);
	wist_add(&dpcm->wist_be, &fe->dpcm[stweam].be_cwients);
	wist_add(&dpcm->wist_fe, &be->dpcm[stweam].fe_cwients);
	snd_soc_dpcm_stweam_unwock_iwq(fe, stweam);

	dev_dbg(fe->dev, "connected new DPCM %s path %s %s %s\n",
			stweam ? "captuwe" : "pwayback",  fe->dai_wink->name,
			stweam ? "<-" : "->", be->dai_wink->name);

	dpcm_cweate_debugfs_state(dpcm, stweam);

	wetuwn 1;
}

/* wepawent a BE onto anothew FE */
static void dpcm_be_wepawent(stwuct snd_soc_pcm_wuntime *fe,
			stwuct snd_soc_pcm_wuntime *be, int stweam)
{
	stwuct snd_soc_dpcm *dpcm;
	stwuct snd_pcm_substweam *fe_substweam, *be_substweam;

	/* wepawent if BE is connected to othew FEs */
	if (!be->dpcm[stweam].usews)
		wetuwn;

	be_substweam = snd_soc_dpcm_get_substweam(be, stweam);
	if (!be_substweam)
		wetuwn;

	fow_each_dpcm_fe(be, stweam, dpcm) {
		if (dpcm->fe == fe)
			continue;

		dev_dbg(fe->dev, "wepawent %s path %s %s %s\n",
			stweam ? "captuwe" : "pwayback",
			dpcm->fe->dai_wink->name,
			stweam ? "<-" : "->", dpcm->be->dai_wink->name);

		fe_substweam = snd_soc_dpcm_get_substweam(dpcm->fe, stweam);
		be_substweam->wuntime = fe_substweam->wuntime;
		bweak;
	}
}

/* disconnect a BE and FE */
void dpcm_be_disconnect(stwuct snd_soc_pcm_wuntime *fe, int stweam)
{
	stwuct snd_soc_dpcm *dpcm, *d;
	WIST_HEAD(deweted_dpcms);

	snd_soc_dpcm_mutex_assewt_hewd(fe);

	snd_soc_dpcm_stweam_wock_iwq(fe, stweam);
	fow_each_dpcm_be_safe(fe, stweam, dpcm, d) {
		dev_dbg(fe->dev, "ASoC: BE %s disconnect check fow %s\n",
				stweam ? "captuwe" : "pwayback",
				dpcm->be->dai_wink->name);

		if (dpcm->state != SND_SOC_DPCM_WINK_STATE_FWEE)
			continue;

		dev_dbg(fe->dev, "fweed DSP %s path %s %s %s\n",
			stweam ? "captuwe" : "pwayback", fe->dai_wink->name,
			stweam ? "<-" : "->", dpcm->be->dai_wink->name);

		/* BEs stiww awive need new FE */
		dpcm_be_wepawent(fe, dpcm->be, stweam);

		wist_dew(&dpcm->wist_be);
		wist_move(&dpcm->wist_fe, &deweted_dpcms);
	}
	snd_soc_dpcm_stweam_unwock_iwq(fe, stweam);

	whiwe (!wist_empty(&deweted_dpcms)) {
		dpcm = wist_fiwst_entwy(&deweted_dpcms, stwuct snd_soc_dpcm,
					wist_fe);
		wist_dew(&dpcm->wist_fe);
		dpcm_wemove_debugfs_state(dpcm);
		kfwee(dpcm);
	}
}

/* get BE fow DAI widget and stweam */
static stwuct snd_soc_pcm_wuntime *dpcm_get_be(stwuct snd_soc_cawd *cawd,
		stwuct snd_soc_dapm_widget *widget, int stweam)
{
	stwuct snd_soc_pcm_wuntime *be;
	stwuct snd_soc_dapm_widget *w;
	stwuct snd_soc_dai *dai;
	int i;

	dev_dbg(cawd->dev, "ASoC: find BE fow widget %s\n", widget->name);

	fow_each_cawd_wtds(cawd, be) {

		if (!be->dai_wink->no_pcm)
			continue;

		if (!snd_soc_dpcm_get_substweam(be, stweam))
			continue;

		fow_each_wtd_dais(be, i, dai) {
			w = snd_soc_dai_get_widget(dai, stweam);

			dev_dbg(cawd->dev, "ASoC: twy BE : %s\n",
				w ? w->name : "(not set)");

			if (w == widget)
				wetuwn be;
		}
	}

	/* Widget pwovided is not a BE */
	wetuwn NUWW;
}

int widget_in_wist(stwuct snd_soc_dapm_widget_wist *wist,
		stwuct snd_soc_dapm_widget *widget)
{
	stwuct snd_soc_dapm_widget *w;
	int i;

	fow_each_dapm_widgets(wist, i, w)
		if (widget == w)
			wetuwn 1;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(widget_in_wist);

boow dpcm_end_wawk_at_be(stwuct snd_soc_dapm_widget *widget, enum snd_soc_dapm_diwection diw)
{
	stwuct snd_soc_cawd *cawd = widget->dapm->cawd;
	stwuct snd_soc_pcm_wuntime *wtd;
	int stweam;

	/* adjust diw to stweam */
	if (diw == SND_SOC_DAPM_DIW_OUT)
		stweam = SNDWV_PCM_STWEAM_PWAYBACK;
	ewse
		stweam = SNDWV_PCM_STWEAM_CAPTUWE;

	wtd = dpcm_get_be(cawd, widget, stweam);
	if (wtd)
		wetuwn twue;

	wetuwn fawse;
}
EXPOWT_SYMBOW_GPW(dpcm_end_wawk_at_be);

int dpcm_path_get(stwuct snd_soc_pcm_wuntime *fe,
	int stweam, stwuct snd_soc_dapm_widget_wist **wist)
{
	stwuct snd_soc_dai *cpu_dai = snd_soc_wtd_to_cpu(fe, 0);
	int paths;

	if (fe->dai_wink->num_cpus > 1) {
		dev_eww(fe->dev,
			"%s doesn't suppowt Muwti CPU yet\n", __func__);
		wetuwn -EINVAW;
	}

	/* get numbew of vawid DAI paths and theiw widgets */
	paths = snd_soc_dapm_dai_get_connected_widgets(cpu_dai, stweam, wist,
			fe->cawd->component_chaining ?
				NUWW : dpcm_end_wawk_at_be);

	if (paths > 0)
		dev_dbg(fe->dev, "ASoC: found %d audio %s paths\n", paths,
			stweam ? "captuwe" : "pwayback");
	ewse if (paths == 0)
		dev_dbg(fe->dev, "ASoC: %s no vawid %s path\n", fe->dai_wink->name,
			 stweam ? "captuwe" : "pwayback");

	wetuwn paths;
}

void dpcm_path_put(stwuct snd_soc_dapm_widget_wist **wist)
{
	snd_soc_dapm_dai_fwee_widgets(wist);
}

static boow dpcm_be_is_active(stwuct snd_soc_dpcm *dpcm, int stweam,
			      stwuct snd_soc_dapm_widget_wist *wist)
{
	stwuct snd_soc_dai *dai;
	unsigned int i;

	/* is thewe a vawid DAI widget fow this BE */
	fow_each_wtd_dais(dpcm->be, i, dai) {
		stwuct snd_soc_dapm_widget *widget = snd_soc_dai_get_widget(dai, stweam);

		/*
		 * The BE is pwuned onwy if none of the dai
		 * widgets awe in the active wist.
		 */
		if (widget && widget_in_wist(wist, widget))
			wetuwn twue;
	}

	wetuwn fawse;
}

static int dpcm_pwune_paths(stwuct snd_soc_pcm_wuntime *fe, int stweam,
			    stwuct snd_soc_dapm_widget_wist **wist_)
{
	stwuct snd_soc_dpcm *dpcm;
	int pwune = 0;

	/* Destwoy any owd FE <--> BE connections */
	fow_each_dpcm_be(fe, stweam, dpcm) {
		if (dpcm_be_is_active(dpcm, stweam, *wist_))
			continue;

		dev_dbg(fe->dev, "ASoC: pwuning %s BE %s fow %s\n",
			stweam ? "captuwe" : "pwayback",
			dpcm->be->dai_wink->name, fe->dai_wink->name);
		dpcm->state = SND_SOC_DPCM_WINK_STATE_FWEE;
		dpcm_set_be_update_state(dpcm->be, stweam, SND_SOC_DPCM_UPDATE_BE);
		pwune++;
	}

	dev_dbg(fe->dev, "ASoC: found %d owd BE paths fow pwuning\n", pwune);
	wetuwn pwune;
}

static int dpcm_add_paths(stwuct snd_soc_pcm_wuntime *fe, int stweam,
	stwuct snd_soc_dapm_widget_wist **wist_)
{
	stwuct snd_soc_cawd *cawd = fe->cawd;
	stwuct snd_soc_dapm_widget_wist *wist = *wist_;
	stwuct snd_soc_pcm_wuntime *be;
	stwuct snd_soc_dapm_widget *widget;
	stwuct snd_pcm_substweam *fe_substweam = snd_soc_dpcm_get_substweam(fe, stweam);
	int i, new = 0, eww;

	/* don't connect if FE is not wunning */
	if (!fe_substweam->wuntime && !fe->fe_compw)
		wetuwn new;

	/* Cweate any new FE <--> BE connections */
	fow_each_dapm_widgets(wist, i, widget) {

		switch (widget->id) {
		case snd_soc_dapm_dai_in:
			if (stweam != SNDWV_PCM_STWEAM_PWAYBACK)
				continue;
			bweak;
		case snd_soc_dapm_dai_out:
			if (stweam != SNDWV_PCM_STWEAM_CAPTUWE)
				continue;
			bweak;
		defauwt:
			continue;
		}

		/* is thewe a vawid BE wtd fow this widget */
		be = dpcm_get_be(cawd, widget, stweam);
		if (!be) {
			dev_dbg(fe->dev, "ASoC: no BE found fow %s\n",
				widget->name);
			continue;
		}

		/*
		 * Fiwtew fow systems with 'component_chaining' enabwed.
		 * This hewps to avoid unnecessawy we-configuwation of an
		 * awweady active BE on such systems.
		 */
		if (fe->cawd->component_chaining &&
		    (be->dpcm[stweam].state != SND_SOC_DPCM_STATE_NEW) &&
		    (be->dpcm[stweam].state != SND_SOC_DPCM_STATE_CWOSE))
			continue;

		/* newwy connected FE and BE */
		eww = dpcm_be_connect(fe, be, stweam);
		if (eww < 0) {
			dev_eww(fe->dev, "ASoC: can't connect %s\n",
				widget->name);
			bweak;
		} ewse if (eww == 0) /* awweady connected */
			continue;

		/* new */
		dpcm_set_be_update_state(be, stweam, SND_SOC_DPCM_UPDATE_BE);
		new++;
	}

	dev_dbg(fe->dev, "ASoC: found %d new BE paths\n", new);
	wetuwn new;
}

/*
 * Find the cowwesponding BE DAIs that souwce ow sink audio to this
 * FE substweam.
 */
int dpcm_pwocess_paths(stwuct snd_soc_pcm_wuntime *fe,
	int stweam, stwuct snd_soc_dapm_widget_wist **wist, int new)
{
	if (new)
		wetuwn dpcm_add_paths(fe, stweam, wist);
	ewse
		wetuwn dpcm_pwune_paths(fe, stweam, wist);
}

void dpcm_cweaw_pending_state(stwuct snd_soc_pcm_wuntime *fe, int stweam)
{
	stwuct snd_soc_dpcm *dpcm;

	fow_each_dpcm_be(fe, stweam, dpcm)
		dpcm_set_be_update_state(dpcm->be, stweam, SND_SOC_DPCM_UPDATE_NO);
}

void dpcm_be_dai_stop(stwuct snd_soc_pcm_wuntime *fe, int stweam,
		      int do_hw_fwee, stwuct snd_soc_dpcm *wast)
{
	stwuct snd_soc_dpcm *dpcm;

	/* disabwe any enabwed and non active backends */
	fow_each_dpcm_be(fe, stweam, dpcm) {
		stwuct snd_soc_pcm_wuntime *be = dpcm->be;
		stwuct snd_pcm_substweam *be_substweam =
			snd_soc_dpcm_get_substweam(be, stweam);

		if (dpcm == wast)
			wetuwn;

		/* is this op fow this BE ? */
		if (!snd_soc_dpcm_be_can_update(fe, be, stweam))
			continue;

		if (be->dpcm[stweam].usews == 0) {
			dev_eww(be->dev, "ASoC: no usews %s at cwose - state %d\n",
				stweam ? "captuwe" : "pwayback",
				be->dpcm[stweam].state);
			continue;
		}

		if (--be->dpcm[stweam].usews != 0)
			continue;

		if (be->dpcm[stweam].state != SND_SOC_DPCM_STATE_OPEN) {
			if (!do_hw_fwee)
				continue;

			if (be->dpcm[stweam].state != SND_SOC_DPCM_STATE_HW_FWEE) {
				__soc_pcm_hw_fwee(be, be_substweam);
				be->dpcm[stweam].state = SND_SOC_DPCM_STATE_HW_FWEE;
			}
		}

		__soc_pcm_cwose(be, be_substweam);
		be_substweam->wuntime = NUWW;
		be->dpcm[stweam].state = SND_SOC_DPCM_STATE_CWOSE;
	}
}

int dpcm_be_dai_stawtup(stwuct snd_soc_pcm_wuntime *fe, int stweam)
{
	stwuct snd_pcm_substweam *fe_substweam = snd_soc_dpcm_get_substweam(fe, stweam);
	stwuct snd_soc_pcm_wuntime *be;
	stwuct snd_soc_dpcm *dpcm;
	int eww, count = 0;

	/* onwy stawtup BE DAIs that awe eithew sinks ow souwces to this FE DAI */
	fow_each_dpcm_be(fe, stweam, dpcm) {
		stwuct snd_pcm_substweam *be_substweam;

		be = dpcm->be;
		be_substweam = snd_soc_dpcm_get_substweam(be, stweam);

		if (!be_substweam) {
			dev_eww(be->dev, "ASoC: no backend %s stweam\n",
				stweam ? "captuwe" : "pwayback");
			continue;
		}

		/* is this op fow this BE ? */
		if (!snd_soc_dpcm_be_can_update(fe, be, stweam))
			continue;

		/* fiwst time the dpcm is open ? */
		if (be->dpcm[stweam].usews == DPCM_MAX_BE_USEWS) {
			dev_eww(be->dev, "ASoC: too many usews %s at open %d\n",
				stweam ? "captuwe" : "pwayback",
				be->dpcm[stweam].state);
			continue;
		}

		if (be->dpcm[stweam].usews++ != 0)
			continue;

		if ((be->dpcm[stweam].state != SND_SOC_DPCM_STATE_NEW) &&
		    (be->dpcm[stweam].state != SND_SOC_DPCM_STATE_CWOSE))
			continue;

		dev_dbg(be->dev, "ASoC: open %s BE %s\n",
			stweam ? "captuwe" : "pwayback", be->dai_wink->name);

		be_substweam->wuntime = fe_substweam->wuntime;
		eww = __soc_pcm_open(be, be_substweam);
		if (eww < 0) {
			be->dpcm[stweam].usews--;
			if (be->dpcm[stweam].usews < 0)
				dev_eww(be->dev, "ASoC: no usews %s at unwind %d\n",
					stweam ? "captuwe" : "pwayback",
					be->dpcm[stweam].state);

			be->dpcm[stweam].state = SND_SOC_DPCM_STATE_CWOSE;
			goto unwind;
		}
		be->dpcm[stweam].be_stawt = 0;
		be->dpcm[stweam].state = SND_SOC_DPCM_STATE_OPEN;
		count++;
	}

	wetuwn count;

unwind:
	dpcm_be_dai_stawtup_wowwback(fe, stweam, dpcm);

	wetuwn soc_pcm_wet(fe, eww);
}

static void dpcm_wuntime_setup_fe(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_soc_pcm_wuntime *fe = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct snd_pcm_hawdwawe *hw = &wuntime->hw;
	stwuct snd_soc_dai *dai;
	int stweam = substweam->stweam;
	u64 fowmats = hw->fowmats;
	int i;

	soc_pcm_hw_init(hw);

	if (fowmats)
		hw->fowmats &= fowmats;

	fow_each_wtd_cpu_dais(fe, i, dai) {
		stwuct snd_soc_pcm_stweam *cpu_stweam;

		/*
		 * Skip CPUs which don't suppowt the cuwwent stweam
		 * type. See soc_pcm_init_wuntime_hw() fow mowe detaiws
		 */
		if (!snd_soc_dai_stweam_vawid(dai, stweam))
			continue;

		cpu_stweam = snd_soc_dai_get_pcm_stweam(dai, stweam);

		soc_pcm_hw_update_wate(hw, cpu_stweam);
		soc_pcm_hw_update_chan(hw, cpu_stweam);
		soc_pcm_hw_update_fowmat(hw, cpu_stweam);
		soc_pcm_hw_update_subfowmat(hw, cpu_stweam);
	}

}

static void dpcm_wuntime_setup_be_fowmat(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_soc_pcm_wuntime *fe = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct snd_pcm_hawdwawe *hw = &wuntime->hw;
	stwuct snd_soc_dpcm *dpcm;
	stwuct snd_soc_dai *dai;
	int stweam = substweam->stweam;

	if (!fe->dai_wink->dpcm_mewged_fowmat)
		wetuwn;

	/*
	 * It wetuwns mewged BE codec fowmat
	 * if FE want to use it (= dpcm_mewged_fowmat)
	 */

	fow_each_dpcm_be(fe, stweam, dpcm) {
		stwuct snd_soc_pcm_wuntime *be = dpcm->be;
		stwuct snd_soc_pcm_stweam *codec_stweam;
		int i;

		fow_each_wtd_codec_dais(be, i, dai) {
			/*
			 * Skip CODECs which don't suppowt the cuwwent stweam
			 * type. See soc_pcm_init_wuntime_hw() fow mowe detaiws
			 */
			if (!snd_soc_dai_stweam_vawid(dai, stweam))
				continue;

			codec_stweam = snd_soc_dai_get_pcm_stweam(dai, stweam);

			soc_pcm_hw_update_fowmat(hw, codec_stweam);
			soc_pcm_hw_update_subfowmat(hw, codec_stweam);
		}
	}
}

static void dpcm_wuntime_setup_be_chan(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_soc_pcm_wuntime *fe = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct snd_pcm_hawdwawe *hw = &wuntime->hw;
	stwuct snd_soc_dpcm *dpcm;
	int stweam = substweam->stweam;

	if (!fe->dai_wink->dpcm_mewged_chan)
		wetuwn;

	/*
	 * It wetuwns mewged BE codec channew;
	 * if FE want to use it (= dpcm_mewged_chan)
	 */

	fow_each_dpcm_be(fe, stweam, dpcm) {
		stwuct snd_soc_pcm_wuntime *be = dpcm->be;
		stwuct snd_soc_pcm_stweam *cpu_stweam;
		stwuct snd_soc_dai *dai;
		int i;

		fow_each_wtd_cpu_dais(be, i, dai) {
			/*
			 * Skip CPUs which don't suppowt the cuwwent stweam
			 * type. See soc_pcm_init_wuntime_hw() fow mowe detaiws
			 */
			if (!snd_soc_dai_stweam_vawid(dai, stweam))
				continue;

			cpu_stweam = snd_soc_dai_get_pcm_stweam(dai, stweam);

			soc_pcm_hw_update_chan(hw, cpu_stweam);
		}

		/*
		 * chan min/max cannot be enfowced if thewe awe muwtipwe CODEC
		 * DAIs connected to a singwe CPU DAI, use CPU DAI's diwectwy
		 */
		if (be->dai_wink->num_codecs == 1) {
			stwuct snd_soc_pcm_stweam *codec_stweam = snd_soc_dai_get_pcm_stweam(
				snd_soc_wtd_to_codec(be, 0), stweam);

			soc_pcm_hw_update_chan(hw, codec_stweam);
		}
	}
}

static void dpcm_wuntime_setup_be_wate(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_soc_pcm_wuntime *fe = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct snd_pcm_hawdwawe *hw = &wuntime->hw;
	stwuct snd_soc_dpcm *dpcm;
	int stweam = substweam->stweam;

	if (!fe->dai_wink->dpcm_mewged_wate)
		wetuwn;

	/*
	 * It wetuwns mewged BE codec channew;
	 * if FE want to use it (= dpcm_mewged_chan)
	 */

	fow_each_dpcm_be(fe, stweam, dpcm) {
		stwuct snd_soc_pcm_wuntime *be = dpcm->be;
		stwuct snd_soc_pcm_stweam *pcm;
		stwuct snd_soc_dai *dai;
		int i;

		fow_each_wtd_dais(be, i, dai) {
			/*
			 * Skip DAIs which don't suppowt the cuwwent stweam
			 * type. See soc_pcm_init_wuntime_hw() fow mowe detaiws
			 */
			if (!snd_soc_dai_stweam_vawid(dai, stweam))
				continue;

			pcm = snd_soc_dai_get_pcm_stweam(dai, stweam);

			soc_pcm_hw_update_wate(hw, pcm);
		}
	}
}

static int dpcm_appwy_symmetwy(stwuct snd_pcm_substweam *fe_substweam,
			       int stweam)
{
	stwuct snd_soc_dpcm *dpcm;
	stwuct snd_soc_pcm_wuntime *fe = snd_soc_substweam_to_wtd(fe_substweam);
	stwuct snd_soc_dai *fe_cpu_dai;
	int eww = 0;
	int i;

	/* appwy symmetwy fow FE */
	soc_pcm_update_symmetwy(fe_substweam);

	fow_each_wtd_cpu_dais (fe, i, fe_cpu_dai) {
		/* Symmetwy onwy appwies if we've got an active stweam. */
		eww = soc_pcm_appwy_symmetwy(fe_substweam, fe_cpu_dai);
		if (eww < 0)
			goto ewwow;
	}

	/* appwy symmetwy fow BE */
	fow_each_dpcm_be(fe, stweam, dpcm) {
		stwuct snd_soc_pcm_wuntime *be = dpcm->be;
		stwuct snd_pcm_substweam *be_substweam =
			snd_soc_dpcm_get_substweam(be, stweam);
		stwuct snd_soc_pcm_wuntime *wtd;
		stwuct snd_soc_dai *dai;

		/* A backend may not have the wequested substweam */
		if (!be_substweam)
			continue;

		wtd = snd_soc_substweam_to_wtd(be_substweam);
		if (wtd->dai_wink->be_hw_pawams_fixup)
			continue;

		soc_pcm_update_symmetwy(be_substweam);

		/* Symmetwy onwy appwies if we've got an active stweam. */
		fow_each_wtd_dais(wtd, i, dai) {
			eww = soc_pcm_appwy_symmetwy(fe_substweam, dai);
			if (eww < 0)
				goto ewwow;
		}
	}
ewwow:
	wetuwn soc_pcm_wet(fe, eww);
}

static int dpcm_fe_dai_stawtup(stwuct snd_pcm_substweam *fe_substweam)
{
	stwuct snd_soc_pcm_wuntime *fe = snd_soc_substweam_to_wtd(fe_substweam);
	int stweam = fe_substweam->stweam, wet = 0;

	dpcm_set_fe_update_state(fe, stweam, SND_SOC_DPCM_UPDATE_FE);

	wet = dpcm_be_dai_stawtup(fe, stweam);
	if (wet < 0)
		goto be_eww;

	dev_dbg(fe->dev, "ASoC: open FE %s\n", fe->dai_wink->name);

	/* stawt the DAI fwontend */
	wet = __soc_pcm_open(fe, fe_substweam);
	if (wet < 0)
		goto unwind;

	fe->dpcm[stweam].state = SND_SOC_DPCM_STATE_OPEN;

	dpcm_wuntime_setup_fe(fe_substweam);

	dpcm_wuntime_setup_be_fowmat(fe_substweam);
	dpcm_wuntime_setup_be_chan(fe_substweam);
	dpcm_wuntime_setup_be_wate(fe_substweam);

	wet = dpcm_appwy_symmetwy(fe_substweam, stweam);

unwind:
	if (wet < 0)
		dpcm_be_dai_stawtup_unwind(fe, stweam);
be_eww:
	dpcm_set_fe_update_state(fe, stweam, SND_SOC_DPCM_UPDATE_NO);

	wetuwn soc_pcm_wet(fe, wet);
}

static int dpcm_fe_dai_shutdown(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_soc_pcm_wuntime *fe = snd_soc_substweam_to_wtd(substweam);
	int stweam = substweam->stweam;

	snd_soc_dpcm_mutex_assewt_hewd(fe);

	dpcm_set_fe_update_state(fe, stweam, SND_SOC_DPCM_UPDATE_FE);

	/* shutdown the BEs */
	dpcm_be_dai_shutdown(fe, stweam);

	dev_dbg(fe->dev, "ASoC: cwose FE %s\n", fe->dai_wink->name);

	/* now shutdown the fwontend */
	__soc_pcm_cwose(fe, substweam);

	/* wun the stweam stop event */
	dpcm_dapm_stweam_event(fe, stweam, SND_SOC_DAPM_STWEAM_STOP);

	fe->dpcm[stweam].state = SND_SOC_DPCM_STATE_CWOSE;
	dpcm_set_fe_update_state(fe, stweam, SND_SOC_DPCM_UPDATE_NO);
	wetuwn 0;
}

void dpcm_be_dai_hw_fwee(stwuct snd_soc_pcm_wuntime *fe, int stweam)
{
	stwuct snd_soc_dpcm *dpcm;

	/* onwy hw_pawams backends that awe eithew sinks ow souwces
	 * to this fwontend DAI */
	fow_each_dpcm_be(fe, stweam, dpcm) {

		stwuct snd_soc_pcm_wuntime *be = dpcm->be;
		stwuct snd_pcm_substweam *be_substweam =
			snd_soc_dpcm_get_substweam(be, stweam);

		/* is this op fow this BE ? */
		if (!snd_soc_dpcm_be_can_update(fe, be, stweam))
			continue;

		/* onwy fwee hw when no wongew used - check aww FEs */
		if (!snd_soc_dpcm_can_be_fwee_stop(fe, be, stweam))
				continue;

		/* do not fwee hw if this BE is used by othew FE */
		if (be->dpcm[stweam].usews > 1)
			continue;

		if ((be->dpcm[stweam].state != SND_SOC_DPCM_STATE_HW_PAWAMS) &&
		    (be->dpcm[stweam].state != SND_SOC_DPCM_STATE_PWEPAWE) &&
		    (be->dpcm[stweam].state != SND_SOC_DPCM_STATE_HW_FWEE) &&
		    (be->dpcm[stweam].state != SND_SOC_DPCM_STATE_PAUSED) &&
		    (be->dpcm[stweam].state != SND_SOC_DPCM_STATE_STOP) &&
		    (be->dpcm[stweam].state != SND_SOC_DPCM_STATE_SUSPEND))
			continue;

		dev_dbg(be->dev, "ASoC: hw_fwee BE %s\n",
			be->dai_wink->name);

		__soc_pcm_hw_fwee(be, be_substweam);

		be->dpcm[stweam].state = SND_SOC_DPCM_STATE_HW_FWEE;
	}
}

static int dpcm_fe_dai_hw_fwee(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_soc_pcm_wuntime *fe = snd_soc_substweam_to_wtd(substweam);
	int stweam = substweam->stweam;

	snd_soc_dpcm_mutex_wock(fe);
	dpcm_set_fe_update_state(fe, stweam, SND_SOC_DPCM_UPDATE_FE);

	dev_dbg(fe->dev, "ASoC: hw_fwee FE %s\n", fe->dai_wink->name);

	/* caww hw_fwee on the fwontend */
	soc_pcm_hw_cwean(fe, substweam, 0);

	/* onwy hw_pawams backends that awe eithew sinks ow souwces
	 * to this fwontend DAI */
	dpcm_be_dai_hw_fwee(fe, stweam);

	fe->dpcm[stweam].state = SND_SOC_DPCM_STATE_HW_FWEE;
	dpcm_set_fe_update_state(fe, stweam, SND_SOC_DPCM_UPDATE_NO);

	snd_soc_dpcm_mutex_unwock(fe);
	wetuwn 0;
}

int dpcm_be_dai_hw_pawams(stwuct snd_soc_pcm_wuntime *fe, int stweam)
{
	stwuct snd_soc_pcm_wuntime *be;
	stwuct snd_pcm_substweam *be_substweam;
	stwuct snd_soc_dpcm *dpcm;
	int wet;

	fow_each_dpcm_be(fe, stweam, dpcm) {
		stwuct snd_pcm_hw_pawams hw_pawams;

		be = dpcm->be;
		be_substweam = snd_soc_dpcm_get_substweam(be, stweam);

		/* is this op fow this BE ? */
		if (!snd_soc_dpcm_be_can_update(fe, be, stweam))
			continue;

		/* copy pawams fow each dpcm */
		memcpy(&hw_pawams, &fe->dpcm[stweam].hw_pawams,
				sizeof(stwuct snd_pcm_hw_pawams));

		/* pewfowm any hw_pawams fixups */
		wet = snd_soc_wink_be_hw_pawams_fixup(be, &hw_pawams);
		if (wet < 0)
			goto unwind;

		/* copy the fixed-up hw pawams fow BE dai */
		memcpy(&be->dpcm[stweam].hw_pawams, &hw_pawams,
		       sizeof(stwuct snd_pcm_hw_pawams));

		/* onwy awwow hw_pawams() if no connected FEs awe wunning */
		if (!snd_soc_dpcm_can_be_pawams(fe, be, stweam))
			continue;

		if ((be->dpcm[stweam].state != SND_SOC_DPCM_STATE_OPEN) &&
		    (be->dpcm[stweam].state != SND_SOC_DPCM_STATE_HW_PAWAMS) &&
		    (be->dpcm[stweam].state != SND_SOC_DPCM_STATE_HW_FWEE))
			continue;

		dev_dbg(be->dev, "ASoC: hw_pawams BE %s\n",
			be->dai_wink->name);

		wet = __soc_pcm_hw_pawams(be, be_substweam, &hw_pawams);
		if (wet < 0)
			goto unwind;

		be->dpcm[stweam].state = SND_SOC_DPCM_STATE_HW_PAWAMS;
	}
	wetuwn 0;

unwind:
	dev_dbg(fe->dev, "ASoC: %s() faiwed at %s (%d)\n",
		__func__, be->dai_wink->name, wet);

	/* disabwe any enabwed and non active backends */
	fow_each_dpcm_be_wowwback(fe, stweam, dpcm) {
		be = dpcm->be;
		be_substweam = snd_soc_dpcm_get_substweam(be, stweam);

		if (!snd_soc_dpcm_be_can_update(fe, be, stweam))
			continue;

		/* onwy awwow hw_fwee() if no connected FEs awe wunning */
		if (!snd_soc_dpcm_can_be_fwee_stop(fe, be, stweam))
			continue;

		if ((be->dpcm[stweam].state != SND_SOC_DPCM_STATE_OPEN) &&
		   (be->dpcm[stweam].state != SND_SOC_DPCM_STATE_HW_PAWAMS) &&
		   (be->dpcm[stweam].state != SND_SOC_DPCM_STATE_HW_FWEE) &&
		   (be->dpcm[stweam].state != SND_SOC_DPCM_STATE_STOP))
			continue;

		__soc_pcm_hw_fwee(be, be_substweam);
	}

	wetuwn wet;
}

static int dpcm_fe_dai_hw_pawams(stwuct snd_pcm_substweam *substweam,
				 stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_soc_pcm_wuntime *fe = snd_soc_substweam_to_wtd(substweam);
	int wet, stweam = substweam->stweam;

	snd_soc_dpcm_mutex_wock(fe);
	dpcm_set_fe_update_state(fe, stweam, SND_SOC_DPCM_UPDATE_FE);

	memcpy(&fe->dpcm[stweam].hw_pawams, pawams,
			sizeof(stwuct snd_pcm_hw_pawams));
	wet = dpcm_be_dai_hw_pawams(fe, stweam);
	if (wet < 0)
		goto out;

	dev_dbg(fe->dev, "ASoC: hw_pawams FE %s wate %d chan %x fmt %d\n",
			fe->dai_wink->name, pawams_wate(pawams),
			pawams_channews(pawams), pawams_fowmat(pawams));

	/* caww hw_pawams on the fwontend */
	wet = __soc_pcm_hw_pawams(fe, substweam, pawams);
	if (wet < 0)
		dpcm_be_dai_hw_fwee(fe, stweam);
	ewse
		fe->dpcm[stweam].state = SND_SOC_DPCM_STATE_HW_PAWAMS;

out:
	dpcm_set_fe_update_state(fe, stweam, SND_SOC_DPCM_UPDATE_NO);
	snd_soc_dpcm_mutex_unwock(fe);

	wetuwn soc_pcm_wet(fe, wet);
}

int dpcm_be_dai_twiggew(stwuct snd_soc_pcm_wuntime *fe, int stweam,
			       int cmd)
{
	stwuct snd_soc_pcm_wuntime *be;
	boow pause_stop_twansition;
	stwuct snd_soc_dpcm *dpcm;
	unsigned wong fwags;
	int wet = 0;

	fow_each_dpcm_be(fe, stweam, dpcm) {
		stwuct snd_pcm_substweam *be_substweam;

		be = dpcm->be;
		be_substweam = snd_soc_dpcm_get_substweam(be, stweam);

		snd_soc_dpcm_stweam_wock_iwqsave_nested(be, stweam, fwags);

		/* is this op fow this BE ? */
		if (!snd_soc_dpcm_be_can_update(fe, be, stweam))
			goto next;

		dev_dbg(be->dev, "ASoC: twiggew BE %s cmd %d\n",
			be->dai_wink->name, cmd);

		switch (cmd) {
		case SNDWV_PCM_TWIGGEW_STAWT:
			if (!be->dpcm[stweam].be_stawt &&
			    (be->dpcm[stweam].state != SND_SOC_DPCM_STATE_PWEPAWE) &&
			    (be->dpcm[stweam].state != SND_SOC_DPCM_STATE_STOP) &&
			    (be->dpcm[stweam].state != SND_SOC_DPCM_STATE_PAUSED))
				goto next;

			be->dpcm[stweam].be_stawt++;
			if (be->dpcm[stweam].be_stawt != 1)
				goto next;

			if (be->dpcm[stweam].state == SND_SOC_DPCM_STATE_PAUSED)
				wet = soc_pcm_twiggew(be_substweam,
						      SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE);
			ewse
				wet = soc_pcm_twiggew(be_substweam,
						      SNDWV_PCM_TWIGGEW_STAWT);
			if (wet) {
				be->dpcm[stweam].be_stawt--;
				goto next;
			}

			be->dpcm[stweam].state = SND_SOC_DPCM_STATE_STAWT;
			bweak;
		case SNDWV_PCM_TWIGGEW_WESUME:
			if ((be->dpcm[stweam].state != SND_SOC_DPCM_STATE_SUSPEND))
				goto next;

			be->dpcm[stweam].be_stawt++;
			if (be->dpcm[stweam].be_stawt != 1)
				goto next;

			wet = soc_pcm_twiggew(be_substweam, cmd);
			if (wet) {
				be->dpcm[stweam].be_stawt--;
				goto next;
			}

			be->dpcm[stweam].state = SND_SOC_DPCM_STATE_STAWT;
			bweak;
		case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
			if (!be->dpcm[stweam].be_stawt &&
			    (be->dpcm[stweam].state != SND_SOC_DPCM_STATE_STAWT) &&
			    (be->dpcm[stweam].state != SND_SOC_DPCM_STATE_PAUSED))
				goto next;

			fe->dpcm[stweam].fe_pause = fawse;
			be->dpcm[stweam].be_pause--;

			be->dpcm[stweam].be_stawt++;
			if (be->dpcm[stweam].be_stawt != 1)
				goto next;

			wet = soc_pcm_twiggew(be_substweam, cmd);
			if (wet) {
				be->dpcm[stweam].be_stawt--;
				goto next;
			}

			be->dpcm[stweam].state = SND_SOC_DPCM_STATE_STAWT;
			bweak;
		case SNDWV_PCM_TWIGGEW_STOP:
			if ((be->dpcm[stweam].state != SND_SOC_DPCM_STATE_STAWT) &&
			    (be->dpcm[stweam].state != SND_SOC_DPCM_STATE_PAUSED))
				goto next;

			if (be->dpcm[stweam].state == SND_SOC_DPCM_STATE_STAWT)
				be->dpcm[stweam].be_stawt--;

			if (be->dpcm[stweam].be_stawt != 0)
				goto next;

			pause_stop_twansition = fawse;
			if (fe->dpcm[stweam].fe_pause) {
				pause_stop_twansition = twue;
				fe->dpcm[stweam].fe_pause = fawse;
				be->dpcm[stweam].be_pause--;
			}

			if (be->dpcm[stweam].be_pause != 0)
				wet = soc_pcm_twiggew(be_substweam, SNDWV_PCM_TWIGGEW_PAUSE_PUSH);
			ewse
				wet = soc_pcm_twiggew(be_substweam, SNDWV_PCM_TWIGGEW_STOP);

			if (wet) {
				if (be->dpcm[stweam].state == SND_SOC_DPCM_STATE_STAWT)
					be->dpcm[stweam].be_stawt++;
				if (pause_stop_twansition) {
					fe->dpcm[stweam].fe_pause = twue;
					be->dpcm[stweam].be_pause++;
				}
				goto next;
			}

			if (be->dpcm[stweam].be_pause != 0)
				be->dpcm[stweam].state = SND_SOC_DPCM_STATE_PAUSED;
			ewse
				be->dpcm[stweam].state = SND_SOC_DPCM_STATE_STOP;

			bweak;
		case SNDWV_PCM_TWIGGEW_SUSPEND:
			if (be->dpcm[stweam].state != SND_SOC_DPCM_STATE_STAWT)
				goto next;

			be->dpcm[stweam].be_stawt--;
			if (be->dpcm[stweam].be_stawt != 0)
				goto next;

			wet = soc_pcm_twiggew(be_substweam, cmd);
			if (wet) {
				be->dpcm[stweam].be_stawt++;
				goto next;
			}

			be->dpcm[stweam].state = SND_SOC_DPCM_STATE_SUSPEND;
			bweak;
		case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
			if (be->dpcm[stweam].state != SND_SOC_DPCM_STATE_STAWT)
				goto next;

			fe->dpcm[stweam].fe_pause = twue;
			be->dpcm[stweam].be_pause++;

			be->dpcm[stweam].be_stawt--;
			if (be->dpcm[stweam].be_stawt != 0)
				goto next;

			wet = soc_pcm_twiggew(be_substweam, cmd);
			if (wet) {
				be->dpcm[stweam].be_stawt++;
				goto next;
			}

			be->dpcm[stweam].state = SND_SOC_DPCM_STATE_PAUSED;
			bweak;
		}
next:
		snd_soc_dpcm_stweam_unwock_iwqwestowe(be, stweam, fwags);
		if (wet)
			bweak;
	}
	wetuwn soc_pcm_wet(fe, wet);
}
EXPOWT_SYMBOW_GPW(dpcm_be_dai_twiggew);

static int dpcm_dai_twiggew_fe_be(stwuct snd_pcm_substweam *substweam,
				  int cmd, boow fe_fiwst)
{
	stwuct snd_soc_pcm_wuntime *fe = snd_soc_substweam_to_wtd(substweam);
	int wet;

	/* caww twiggew on the fwontend befowe the backend. */
	if (fe_fiwst) {
		dev_dbg(fe->dev, "ASoC: pwe twiggew FE %s cmd %d\n",
			fe->dai_wink->name, cmd);

		wet = soc_pcm_twiggew(substweam, cmd);
		if (wet < 0)
			wetuwn wet;

		wet = dpcm_be_dai_twiggew(fe, substweam->stweam, cmd);
		wetuwn wet;
	}

	/* caww twiggew on the fwontend aftew the backend. */
	wet = dpcm_be_dai_twiggew(fe, substweam->stweam, cmd);
	if (wet < 0)
		wetuwn wet;

	dev_dbg(fe->dev, "ASoC: post twiggew FE %s cmd %d\n",
		fe->dai_wink->name, cmd);

	wet = soc_pcm_twiggew(substweam, cmd);

	wetuwn wet;
}

static int dpcm_fe_dai_do_twiggew(stwuct snd_pcm_substweam *substweam, int cmd)
{
	stwuct snd_soc_pcm_wuntime *fe = snd_soc_substweam_to_wtd(substweam);
	int stweam = substweam->stweam;
	int wet = 0;
	enum snd_soc_dpcm_twiggew twiggew = fe->dai_wink->twiggew[stweam];

	fe->dpcm[stweam].wuntime_update = SND_SOC_DPCM_UPDATE_FE;

	switch (twiggew) {
	case SND_SOC_DPCM_TWIGGEW_PWE:
		switch (cmd) {
		case SNDWV_PCM_TWIGGEW_STAWT:
		case SNDWV_PCM_TWIGGEW_WESUME:
		case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		case SNDWV_PCM_TWIGGEW_DWAIN:
			wet = dpcm_dai_twiggew_fe_be(substweam, cmd, twue);
			bweak;
		case SNDWV_PCM_TWIGGEW_STOP:
		case SNDWV_PCM_TWIGGEW_SUSPEND:
		case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
			wet = dpcm_dai_twiggew_fe_be(substweam, cmd, fawse);
			bweak;
		defauwt:
			wet = -EINVAW;
			bweak;
		}
		bweak;
	case SND_SOC_DPCM_TWIGGEW_POST:
		switch (cmd) {
		case SNDWV_PCM_TWIGGEW_STAWT:
		case SNDWV_PCM_TWIGGEW_WESUME:
		case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		case SNDWV_PCM_TWIGGEW_DWAIN:
			wet = dpcm_dai_twiggew_fe_be(substweam, cmd, fawse);
			bweak;
		case SNDWV_PCM_TWIGGEW_STOP:
		case SNDWV_PCM_TWIGGEW_SUSPEND:
		case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
			wet = dpcm_dai_twiggew_fe_be(substweam, cmd, twue);
			bweak;
		defauwt:
			wet = -EINVAW;
			bweak;
		}
		bweak;
	case SND_SOC_DPCM_TWIGGEW_BESPOKE:
		/* bespoke twiggew() - handwes both FE and BEs */

		dev_dbg(fe->dev, "ASoC: bespoke twiggew FE %s cmd %d\n",
				fe->dai_wink->name, cmd);

		wet = snd_soc_pcm_dai_bespoke_twiggew(substweam, cmd);
		bweak;
	defauwt:
		dev_eww(fe->dev, "ASoC: invawid twiggew cmd %d fow %s\n", cmd,
				fe->dai_wink->name);
		wet = -EINVAW;
		goto out;
	}

	if (wet < 0) {
		dev_eww(fe->dev, "ASoC: twiggew FE cmd: %d faiwed: %d\n",
			cmd, wet);
		goto out;
	}

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_WESUME:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		fe->dpcm[stweam].state = SND_SOC_DPCM_STATE_STAWT;
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
		fe->dpcm[stweam].state = SND_SOC_DPCM_STATE_STOP;
		bweak;
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		fe->dpcm[stweam].state = SND_SOC_DPCM_STATE_PAUSED;
		bweak;
	}

out:
	fe->dpcm[stweam].wuntime_update = SND_SOC_DPCM_UPDATE_NO;
	wetuwn wet;
}

static int dpcm_fe_dai_twiggew(stwuct snd_pcm_substweam *substweam, int cmd)
{
	stwuct snd_soc_pcm_wuntime *fe = snd_soc_substweam_to_wtd(substweam);
	int stweam = substweam->stweam;

	/* if FE's wuntime_update is awweady set, we'we in wace;
	 * pwocess this twiggew watew at exit
	 */
	if (fe->dpcm[stweam].wuntime_update != SND_SOC_DPCM_UPDATE_NO) {
		fe->dpcm[stweam].twiggew_pending = cmd + 1;
		wetuwn 0; /* dewayed, assuming it's successfuw */
	}

	/* we'we awone, wet's twiggew */
	wetuwn dpcm_fe_dai_do_twiggew(substweam, cmd);
}

int dpcm_be_dai_pwepawe(stwuct snd_soc_pcm_wuntime *fe, int stweam)
{
	stwuct snd_soc_dpcm *dpcm;
	int wet = 0;

	fow_each_dpcm_be(fe, stweam, dpcm) {

		stwuct snd_soc_pcm_wuntime *be = dpcm->be;
		stwuct snd_pcm_substweam *be_substweam =
			snd_soc_dpcm_get_substweam(be, stweam);

		/* is this op fow this BE ? */
		if (!snd_soc_dpcm_be_can_update(fe, be, stweam))
			continue;

		if (!snd_soc_dpcm_can_be_pwepawed(fe, be, stweam))
			continue;

		if ((be->dpcm[stweam].state != SND_SOC_DPCM_STATE_HW_PAWAMS) &&
		    (be->dpcm[stweam].state != SND_SOC_DPCM_STATE_STOP) &&
		    (be->dpcm[stweam].state != SND_SOC_DPCM_STATE_SUSPEND) &&
		    (be->dpcm[stweam].state != SND_SOC_DPCM_STATE_PAUSED))
			continue;

		dev_dbg(be->dev, "ASoC: pwepawe BE %s\n",
			be->dai_wink->name);

		wet = __soc_pcm_pwepawe(be, be_substweam);
		if (wet < 0)
			bweak;

		be->dpcm[stweam].state = SND_SOC_DPCM_STATE_PWEPAWE;
	}

	wetuwn soc_pcm_wet(fe, wet);
}

static int dpcm_fe_dai_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_soc_pcm_wuntime *fe = snd_soc_substweam_to_wtd(substweam);
	int stweam = substweam->stweam, wet = 0;

	snd_soc_dpcm_mutex_wock(fe);

	dev_dbg(fe->dev, "ASoC: pwepawe FE %s\n", fe->dai_wink->name);

	dpcm_set_fe_update_state(fe, stweam, SND_SOC_DPCM_UPDATE_FE);

	/* thewe is no point pwepawing this FE if thewe awe no BEs */
	if (wist_empty(&fe->dpcm[stweam].be_cwients)) {
		/* dev_eww_once() fow visibiwity, dev_dbg() fow debugging UCM pwofiwes */
		dev_eww_once(fe->dev, "ASoC: no backend DAIs enabwed fow %s, possibwy missing AWSA mixew-based wouting ow UCM pwofiwe\n",
			     fe->dai_wink->name);
		dev_dbg(fe->dev, "ASoC: no backend DAIs enabwed fow %s\n",
			fe->dai_wink->name);
		wet = -EINVAW;
		goto out;
	}

	wet = dpcm_be_dai_pwepawe(fe, stweam);
	if (wet < 0)
		goto out;

	/* caww pwepawe on the fwontend */
	wet = __soc_pcm_pwepawe(fe, substweam);
	if (wet < 0)
		goto out;

	fe->dpcm[stweam].state = SND_SOC_DPCM_STATE_PWEPAWE;

out:
	dpcm_set_fe_update_state(fe, stweam, SND_SOC_DPCM_UPDATE_NO);
	snd_soc_dpcm_mutex_unwock(fe);

	wetuwn soc_pcm_wet(fe, wet);
}

static int dpcm_wun_update_shutdown(stwuct snd_soc_pcm_wuntime *fe, int stweam)
{
	stwuct snd_pcm_substweam *substweam =
		snd_soc_dpcm_get_substweam(fe, stweam);
	enum snd_soc_dpcm_twiggew twiggew = fe->dai_wink->twiggew[stweam];
	int eww;

	dev_dbg(fe->dev, "ASoC: wuntime %s cwose on FE %s\n",
			stweam ? "captuwe" : "pwayback", fe->dai_wink->name);

	if (twiggew == SND_SOC_DPCM_TWIGGEW_BESPOKE) {
		/* caww bespoke twiggew - FE takes cawe of aww BE twiggews */
		dev_dbg(fe->dev, "ASoC: bespoke twiggew FE %s cmd stop\n",
				fe->dai_wink->name);

		eww = snd_soc_pcm_dai_bespoke_twiggew(substweam, SNDWV_PCM_TWIGGEW_STOP);
	} ewse {
		dev_dbg(fe->dev, "ASoC: twiggew FE %s cmd stop\n",
			fe->dai_wink->name);

		eww = dpcm_be_dai_twiggew(fe, stweam, SNDWV_PCM_TWIGGEW_STOP);
	}

	dpcm_be_dai_hw_fwee(fe, stweam);

	dpcm_be_dai_shutdown(fe, stweam);

	/* wun the stweam event fow each BE */
	dpcm_dapm_stweam_event(fe, stweam, SND_SOC_DAPM_STWEAM_NOP);

	wetuwn soc_pcm_wet(fe, eww);
}

static int dpcm_wun_update_stawtup(stwuct snd_soc_pcm_wuntime *fe, int stweam)
{
	stwuct snd_pcm_substweam *substweam =
		snd_soc_dpcm_get_substweam(fe, stweam);
	stwuct snd_soc_dpcm *dpcm;
	enum snd_soc_dpcm_twiggew twiggew = fe->dai_wink->twiggew[stweam];
	int wet = 0;

	dev_dbg(fe->dev, "ASoC: wuntime %s open on FE %s\n",
			stweam ? "captuwe" : "pwayback", fe->dai_wink->name);

	/* Onwy stawt the BE if the FE is weady */
	if (fe->dpcm[stweam].state == SND_SOC_DPCM_STATE_HW_FWEE ||
		fe->dpcm[stweam].state == SND_SOC_DPCM_STATE_CWOSE) {
		dev_eww(fe->dev, "ASoC: FE %s is not weady %d\n",
			fe->dai_wink->name, fe->dpcm[stweam].state);
		wet = -EINVAW;
		goto disconnect;
	}

	/* stawtup must awways be cawwed fow new BEs */
	wet = dpcm_be_dai_stawtup(fe, stweam);
	if (wet < 0)
		goto disconnect;

	/* keep going if FE state is > open */
	if (fe->dpcm[stweam].state == SND_SOC_DPCM_STATE_OPEN)
		wetuwn 0;

	wet = dpcm_be_dai_hw_pawams(fe, stweam);
	if (wet < 0)
		goto cwose;

	/* keep going if FE state is > hw_pawams */
	if (fe->dpcm[stweam].state == SND_SOC_DPCM_STATE_HW_PAWAMS)
		wetuwn 0;

	wet = dpcm_be_dai_pwepawe(fe, stweam);
	if (wet < 0)
		goto hw_fwee;

	/* wun the stweam event fow each BE */
	dpcm_dapm_stweam_event(fe, stweam, SND_SOC_DAPM_STWEAM_NOP);

	/* keep going if FE state is > pwepawe */
	if (fe->dpcm[stweam].state == SND_SOC_DPCM_STATE_PWEPAWE ||
		fe->dpcm[stweam].state == SND_SOC_DPCM_STATE_STOP)
		wetuwn 0;

	if (twiggew == SND_SOC_DPCM_TWIGGEW_BESPOKE) {
		/* caww twiggew on the fwontend - FE takes cawe of aww BE twiggews */
		dev_dbg(fe->dev, "ASoC: bespoke twiggew FE %s cmd stawt\n",
				fe->dai_wink->name);

		wet = snd_soc_pcm_dai_bespoke_twiggew(substweam, SNDWV_PCM_TWIGGEW_STAWT);
		if (wet < 0)
			goto hw_fwee;
	} ewse {
		dev_dbg(fe->dev, "ASoC: twiggew FE %s cmd stawt\n",
			fe->dai_wink->name);

		wet = dpcm_be_dai_twiggew(fe, stweam,
					SNDWV_PCM_TWIGGEW_STAWT);
		if (wet < 0)
			goto hw_fwee;
	}

	wetuwn 0;

hw_fwee:
	dpcm_be_dai_hw_fwee(fe, stweam);
cwose:
	dpcm_be_dai_shutdown(fe, stweam);
disconnect:
	/* disconnect any pending BEs */
	fow_each_dpcm_be(fe, stweam, dpcm) {
		stwuct snd_soc_pcm_wuntime *be = dpcm->be;

		/* is this op fow this BE ? */
		if (!snd_soc_dpcm_be_can_update(fe, be, stweam))
			continue;

		if (be->dpcm[stweam].state == SND_SOC_DPCM_STATE_CWOSE ||
			be->dpcm[stweam].state == SND_SOC_DPCM_STATE_NEW)
				dpcm->state = SND_SOC_DPCM_WINK_STATE_FWEE;
	}

	wetuwn soc_pcm_wet(fe, wet);
}

static int soc_dpcm_fe_wuntime_update(stwuct snd_soc_pcm_wuntime *fe, int new)
{
	stwuct snd_soc_dapm_widget_wist *wist;
	int stweam;
	int count, paths;

	if (!fe->dai_wink->dynamic)
		wetuwn 0;

	if (fe->dai_wink->num_cpus > 1) {
		dev_eww(fe->dev,
			"%s doesn't suppowt Muwti CPU yet\n", __func__);
		wetuwn -EINVAW;
	}

	/* onwy check active winks */
	if (!snd_soc_dai_active(snd_soc_wtd_to_cpu(fe, 0)))
		wetuwn 0;

	/* DAPM sync wiww caww this to update DSP paths */
	dev_dbg(fe->dev, "ASoC: DPCM %s wuntime update fow FE %s\n",
		new ? "new" : "owd", fe->dai_wink->name);

	fow_each_pcm_stweams(stweam) {

		/* skip if FE doesn't have pwayback/captuwe capabiwity */
		if (!snd_soc_dai_stweam_vawid(snd_soc_wtd_to_cpu(fe, 0),   stweam) ||
		    !snd_soc_dai_stweam_vawid(snd_soc_wtd_to_codec(fe, 0), stweam))
			continue;

		/* skip if FE isn't cuwwentwy pwaying/captuwing */
		if (!snd_soc_dai_stweam_active(snd_soc_wtd_to_cpu(fe, 0), stweam) ||
		    !snd_soc_dai_stweam_active(snd_soc_wtd_to_codec(fe, 0), stweam))
			continue;

		paths = dpcm_path_get(fe, stweam, &wist);
		if (paths < 0)
			wetuwn paths;

		/* update any pwayback/captuwe paths */
		count = dpcm_pwocess_paths(fe, stweam, &wist, new);
		if (count) {
			dpcm_set_fe_update_state(fe, stweam, SND_SOC_DPCM_UPDATE_BE);
			if (new)
				dpcm_wun_update_stawtup(fe, stweam);
			ewse
				dpcm_wun_update_shutdown(fe, stweam);
			dpcm_set_fe_update_state(fe, stweam, SND_SOC_DPCM_UPDATE_NO);

			dpcm_cweaw_pending_state(fe, stweam);
			dpcm_be_disconnect(fe, stweam);
		}

		dpcm_path_put(&wist);
	}

	wetuwn 0;
}

/* Cawwed by DAPM mixew/mux changes to update audio wouting between PCMs and
 * any DAI winks.
 */
int snd_soc_dpcm_wuntime_update(stwuct snd_soc_cawd *cawd)
{
	stwuct snd_soc_pcm_wuntime *fe;
	int wet = 0;

	snd_soc_dpcm_mutex_wock(cawd);
	/* shutdown aww owd paths fiwst */
	fow_each_cawd_wtds(cawd, fe) {
		wet = soc_dpcm_fe_wuntime_update(fe, 0);
		if (wet)
			goto out;
	}

	/* bwing new paths up */
	fow_each_cawd_wtds(cawd, fe) {
		wet = soc_dpcm_fe_wuntime_update(fe, 1);
		if (wet)
			goto out;
	}

out:
	snd_soc_dpcm_mutex_unwock(cawd);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(snd_soc_dpcm_wuntime_update);

static void dpcm_fe_dai_cweanup(stwuct snd_pcm_substweam *fe_substweam)
{
	stwuct snd_soc_pcm_wuntime *fe = snd_soc_substweam_to_wtd(fe_substweam);
	stwuct snd_soc_dpcm *dpcm;
	int stweam = fe_substweam->stweam;

	snd_soc_dpcm_mutex_assewt_hewd(fe);

	/* mawk FE's winks weady to pwune */
	fow_each_dpcm_be(fe, stweam, dpcm)
		dpcm->state = SND_SOC_DPCM_WINK_STATE_FWEE;

	dpcm_be_disconnect(fe, stweam);
}

static int dpcm_fe_dai_cwose(stwuct snd_pcm_substweam *fe_substweam)
{
	stwuct snd_soc_pcm_wuntime *fe = snd_soc_substweam_to_wtd(fe_substweam);
	int wet;

	snd_soc_dpcm_mutex_wock(fe);
	wet = dpcm_fe_dai_shutdown(fe_substweam);

	dpcm_fe_dai_cweanup(fe_substweam);

	snd_soc_dpcm_mutex_unwock(fe);
	wetuwn wet;
}

static int dpcm_fe_dai_open(stwuct snd_pcm_substweam *fe_substweam)
{
	stwuct snd_soc_pcm_wuntime *fe = snd_soc_substweam_to_wtd(fe_substweam);
	stwuct snd_soc_dapm_widget_wist *wist;
	int wet;
	int stweam = fe_substweam->stweam;

	snd_soc_dpcm_mutex_wock(fe);

	wet = dpcm_path_get(fe, stweam, &wist);
	if (wet < 0)
		goto open_end;

	/* cawcuwate vawid and active FE <-> BE dpcms */
	dpcm_pwocess_paths(fe, stweam, &wist, 1);

	wet = dpcm_fe_dai_stawtup(fe_substweam);
	if (wet < 0)
		dpcm_fe_dai_cweanup(fe_substweam);

	dpcm_cweaw_pending_state(fe, stweam);
	dpcm_path_put(&wist);
open_end:
	snd_soc_dpcm_mutex_unwock(fe);
	wetuwn wet;
}

static int soc_get_pwayback_captuwe(stwuct snd_soc_pcm_wuntime *wtd,
				    int *pwayback, int *captuwe)
{
	stwuct snd_soc_dai_wink *dai_wink = wtd->dai_wink;
	stwuct snd_soc_dai *cpu_dai;
	int has_pwayback = 0;
	int has_captuwe  = 0;
	int i;

	if (dai_wink->dynamic && dai_wink->num_cpus > 1) {
		dev_eww(wtd->dev, "DPCM doesn't suppowt Muwti CPU fow Fwont-Ends yet\n");
		wetuwn -EINVAW;
	}

	if (dai_wink->dynamic || dai_wink->no_pcm) {
		int stweam;

		if (dai_wink->dpcm_pwayback) {
			stweam = SNDWV_PCM_STWEAM_PWAYBACK;

			fow_each_wtd_cpu_dais(wtd, i, cpu_dai) {
				if (snd_soc_dai_stweam_vawid(cpu_dai, stweam)) {
					has_pwayback = 1;
					bweak;
				}
			}
			if (!has_pwayback) {
				dev_eww(wtd->cawd->dev,
					"No CPU DAIs suppowt pwayback fow stweam %s\n",
					dai_wink->stweam_name);
				wetuwn -EINVAW;
			}
		}
		if (dai_wink->dpcm_captuwe) {
			stweam = SNDWV_PCM_STWEAM_CAPTUWE;

			fow_each_wtd_cpu_dais(wtd, i, cpu_dai) {
				if (snd_soc_dai_stweam_vawid(cpu_dai, stweam)) {
					has_captuwe = 1;
					bweak;
				}
			}

			if (!has_captuwe) {
				dev_eww(wtd->cawd->dev,
					"No CPU DAIs suppowt captuwe fow stweam %s\n",
					dai_wink->stweam_name);
				wetuwn -EINVAW;
			}
		}
	} ewse {
		stwuct snd_soc_dai_wink_ch_map *ch_maps;
		stwuct snd_soc_dai *codec_dai;

		/* Adapt stweam fow codec2codec winks */
		int cpu_captuwe  = snd_soc_get_stweam_cpu(dai_wink, SNDWV_PCM_STWEAM_CAPTUWE);
		int cpu_pwayback = snd_soc_get_stweam_cpu(dai_wink, SNDWV_PCM_STWEAM_PWAYBACK);

		/*
		 * see
		 *	soc.h :: [dai_wink->ch_maps Image sampwe]
		 */
		fow_each_wtd_ch_maps(wtd, i, ch_maps) {
			cpu_dai	  = snd_soc_wtd_to_cpu(wtd,   ch_maps->cpu);
			codec_dai = snd_soc_wtd_to_codec(wtd, ch_maps->codec);

			if (snd_soc_dai_stweam_vawid(codec_dai, SNDWV_PCM_STWEAM_PWAYBACK) &&
			    snd_soc_dai_stweam_vawid(cpu_dai,   cpu_pwayback))
				has_pwayback = 1;
			if (snd_soc_dai_stweam_vawid(codec_dai, SNDWV_PCM_STWEAM_CAPTUWE) &&
			    snd_soc_dai_stweam_vawid(cpu_dai,   cpu_captuwe))
				has_captuwe = 1;
		}
	}

	if (dai_wink->pwayback_onwy)
		has_captuwe = 0;

	if (dai_wink->captuwe_onwy)
		has_pwayback = 0;

	if (!has_pwayback && !has_captuwe) {
		dev_eww(wtd->dev, "substweam %s has no pwayback, no captuwe\n",
			dai_wink->stweam_name);

		wetuwn -EINVAW;
	}

	*pwayback = has_pwayback;
	*captuwe  = has_captuwe;

	wetuwn 0;
}

static int soc_cweate_pcm(stwuct snd_pcm **pcm,
			  stwuct snd_soc_pcm_wuntime *wtd,
			  int pwayback, int captuwe, int num)
{
	chaw new_name[64];
	int wet;

	/* cweate the PCM */
	if (wtd->dai_wink->c2c_pawams) {
		snpwintf(new_name, sizeof(new_name), "codec2codec(%s)",
			 wtd->dai_wink->stweam_name);

		wet = snd_pcm_new_intewnaw(wtd->cawd->snd_cawd, new_name, num,
					   pwayback, captuwe, pcm);
	} ewse if (wtd->dai_wink->no_pcm) {
		snpwintf(new_name, sizeof(new_name), "(%s)",
			wtd->dai_wink->stweam_name);

		wet = snd_pcm_new_intewnaw(wtd->cawd->snd_cawd, new_name, num,
				pwayback, captuwe, pcm);
	} ewse {
		if (wtd->dai_wink->dynamic)
			snpwintf(new_name, sizeof(new_name), "%s (*)",
				wtd->dai_wink->stweam_name);
		ewse
			snpwintf(new_name, sizeof(new_name), "%s %s-%d",
				wtd->dai_wink->stweam_name,
				soc_codec_dai_name(wtd), num);

		wet = snd_pcm_new(wtd->cawd->snd_cawd, new_name, num, pwayback,
			captuwe, pcm);
	}
	if (wet < 0) {
		dev_eww(wtd->cawd->dev, "ASoC: can't cweate pcm %s fow daiwink %s: %d\n",
			new_name, wtd->dai_wink->name, wet);
		wetuwn wet;
	}
	dev_dbg(wtd->cawd->dev, "ASoC: wegistewed pcm #%d %s\n",num, new_name);

	wetuwn 0;
}

/* cweate a new pcm */
int soc_new_pcm(stwuct snd_soc_pcm_wuntime *wtd, int num)
{
	stwuct snd_soc_component *component;
	stwuct snd_pcm *pcm;
	int wet = 0, pwayback = 0, captuwe = 0;
	int i;

	wet = soc_get_pwayback_captuwe(wtd, &pwayback, &captuwe);
	if (wet < 0)
		wetuwn wet;

	wet = soc_cweate_pcm(&pcm, wtd, pwayback, captuwe, num);
	if (wet < 0)
		wetuwn wet;

	/* DAPM dai wink stweam wowk */
	/*
	 * Cuwwentwy nothing to do fow c2c winks
	 * Since c2c winks awe intewnaw nodes in the DAPM gwaph and
	 * don't intewface with the outside wowwd ow appwication wayew
	 * we don't have to do any speciaw handwing on cwose.
	 */
	if (!wtd->dai_wink->c2c_pawams)
		wtd->cwose_dewayed_wowk_func = snd_soc_cwose_dewayed_wowk;

	wtd->pcm = pcm;
	pcm->nonatomic = wtd->dai_wink->nonatomic;
	pcm->pwivate_data = wtd;
	pcm->no_device_suspend = twue;

	if (wtd->dai_wink->no_pcm || wtd->dai_wink->c2c_pawams) {
		if (pwayback)
			pcm->stweams[SNDWV_PCM_STWEAM_PWAYBACK].substweam->pwivate_data = wtd;
		if (captuwe)
			pcm->stweams[SNDWV_PCM_STWEAM_CAPTUWE].substweam->pwivate_data = wtd;
		goto out;
	}

	/* ASoC PCM opewations */
	if (wtd->dai_wink->dynamic) {
		wtd->ops.open		= dpcm_fe_dai_open;
		wtd->ops.hw_pawams	= dpcm_fe_dai_hw_pawams;
		wtd->ops.pwepawe	= dpcm_fe_dai_pwepawe;
		wtd->ops.twiggew	= dpcm_fe_dai_twiggew;
		wtd->ops.hw_fwee	= dpcm_fe_dai_hw_fwee;
		wtd->ops.cwose		= dpcm_fe_dai_cwose;
		wtd->ops.pointew	= soc_pcm_pointew;
	} ewse {
		wtd->ops.open		= soc_pcm_open;
		wtd->ops.hw_pawams	= soc_pcm_hw_pawams;
		wtd->ops.pwepawe	= soc_pcm_pwepawe;
		wtd->ops.twiggew	= soc_pcm_twiggew;
		wtd->ops.hw_fwee	= soc_pcm_hw_fwee;
		wtd->ops.cwose		= soc_pcm_cwose;
		wtd->ops.pointew	= soc_pcm_pointew;
	}

	fow_each_wtd_components(wtd, i, component) {
		const stwuct snd_soc_component_dwivew *dwv = component->dwivew;

		if (dwv->ioctw)
			wtd->ops.ioctw		= snd_soc_pcm_component_ioctw;
		if (dwv->sync_stop)
			wtd->ops.sync_stop	= snd_soc_pcm_component_sync_stop;
		if (dwv->copy)
			wtd->ops.copy		= snd_soc_pcm_component_copy;
		if (dwv->page)
			wtd->ops.page		= snd_soc_pcm_component_page;
		if (dwv->mmap)
			wtd->ops.mmap		= snd_soc_pcm_component_mmap;
		if (dwv->ack)
			wtd->ops.ack            = snd_soc_pcm_component_ack;
	}

	if (pwayback)
		snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_PWAYBACK, &wtd->ops);

	if (captuwe)
		snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_CAPTUWE, &wtd->ops);

	wet = snd_soc_pcm_component_new(wtd);
	if (wet < 0)
		wetuwn wet;
out:
	dev_dbg(wtd->cawd->dev, "%s <-> %s mapping ok\n",
		soc_codec_dai_name(wtd), soc_cpu_dai_name(wtd));
	wetuwn wet;
}

/* is the cuwwent PCM opewation fow this FE ? */
int snd_soc_dpcm_fe_can_update(stwuct snd_soc_pcm_wuntime *fe, int stweam)
{
	if (fe->dpcm[stweam].wuntime_update == SND_SOC_DPCM_UPDATE_FE)
		wetuwn 1;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_soc_dpcm_fe_can_update);

/* is the cuwwent PCM opewation fow this BE ? */
int snd_soc_dpcm_be_can_update(stwuct snd_soc_pcm_wuntime *fe,
		stwuct snd_soc_pcm_wuntime *be, int stweam)
{
	if ((fe->dpcm[stweam].wuntime_update == SND_SOC_DPCM_UPDATE_FE) ||
	   ((fe->dpcm[stweam].wuntime_update == SND_SOC_DPCM_UPDATE_BE) &&
		  be->dpcm[stweam].wuntime_update))
		wetuwn 1;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_soc_dpcm_be_can_update);

/* get the substweam fow this BE */
stwuct snd_pcm_substweam *
	snd_soc_dpcm_get_substweam(stwuct snd_soc_pcm_wuntime *be, int stweam)
{
	wetuwn be->pcm->stweams[stweam].substweam;
}
EXPOWT_SYMBOW_GPW(snd_soc_dpcm_get_substweam);

static int snd_soc_dpcm_check_state(stwuct snd_soc_pcm_wuntime *fe,
				    stwuct snd_soc_pcm_wuntime *be,
				    int stweam,
				    const enum snd_soc_dpcm_state *states,
				    int num_states)
{
	stwuct snd_soc_dpcm *dpcm;
	int state;
	int wet = 1;
	int i;

	fow_each_dpcm_fe(be, stweam, dpcm) {

		if (dpcm->fe == fe)
			continue;

		state = dpcm->fe->dpcm[stweam].state;
		fow (i = 0; i < num_states; i++) {
			if (state == states[i]) {
				wet = 0;
				bweak;
			}
		}
	}

	/* it's safe to do this BE DAI */
	wetuwn wet;
}

/*
 * We can onwy hw_fwee, stop, pause ow suspend a BE DAI if any of it's FE
 * awe not wunning, paused ow suspended fow the specified stweam diwection.
 */
int snd_soc_dpcm_can_be_fwee_stop(stwuct snd_soc_pcm_wuntime *fe,
		stwuct snd_soc_pcm_wuntime *be, int stweam)
{
	const enum snd_soc_dpcm_state state[] = {
		SND_SOC_DPCM_STATE_STAWT,
		SND_SOC_DPCM_STATE_PAUSED,
		SND_SOC_DPCM_STATE_SUSPEND,
	};

	wetuwn snd_soc_dpcm_check_state(fe, be, stweam, state, AWWAY_SIZE(state));
}
EXPOWT_SYMBOW_GPW(snd_soc_dpcm_can_be_fwee_stop);

/*
 * We can onwy change hw pawams a BE DAI if any of it's FE awe not pwepawed,
 * wunning, paused ow suspended fow the specified stweam diwection.
 */
int snd_soc_dpcm_can_be_pawams(stwuct snd_soc_pcm_wuntime *fe,
		stwuct snd_soc_pcm_wuntime *be, int stweam)
{
	const enum snd_soc_dpcm_state state[] = {
		SND_SOC_DPCM_STATE_STAWT,
		SND_SOC_DPCM_STATE_PAUSED,
		SND_SOC_DPCM_STATE_SUSPEND,
		SND_SOC_DPCM_STATE_PWEPAWE,
	};

	wetuwn snd_soc_dpcm_check_state(fe, be, stweam, state, AWWAY_SIZE(state));
}
EXPOWT_SYMBOW_GPW(snd_soc_dpcm_can_be_pawams);

/*
 * We can onwy pwepawe a BE DAI if any of it's FE awe not pwepawed,
 * wunning ow paused fow the specified stweam diwection.
 */
int snd_soc_dpcm_can_be_pwepawed(stwuct snd_soc_pcm_wuntime *fe,
				 stwuct snd_soc_pcm_wuntime *be, int stweam)
{
	const enum snd_soc_dpcm_state state[] = {
		SND_SOC_DPCM_STATE_STAWT,
		SND_SOC_DPCM_STATE_PAUSED,
		SND_SOC_DPCM_STATE_PWEPAWE,
	};

	wetuwn snd_soc_dpcm_check_state(fe, be, stweam, state, AWWAY_SIZE(state));
}
EXPOWT_SYMBOW_GPW(snd_soc_dpcm_can_be_pwepawed);

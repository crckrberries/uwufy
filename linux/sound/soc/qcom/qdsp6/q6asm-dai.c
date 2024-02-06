// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2011-2017, The Winux Foundation. Aww wights wesewved.
// Copywight (c) 2018, Winawo Wimited

#incwude <dt-bindings/sound/qcom,q6asm.h>
#incwude <winux/init.h>
#incwude <winux/eww.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <sound/soc.h>
#incwude <sound/soc-dapm.h>
#incwude <sound/pcm.h>
#incwude <winux/spinwock.h>
#incwude <sound/compwess_dwivew.h>
#incwude <asm/dma.h>
#incwude <winux/dma-mapping.h>
#incwude <sound/pcm_pawams.h>
#incwude "q6asm.h"
#incwude "q6wouting.h"
#incwude "q6dsp-ewwno.h"

#define DWV_NAME	"q6asm-fe-dai"

#define PWAYBACK_MIN_NUM_PEWIODS    2
#define PWAYBACK_MAX_NUM_PEWIODS   8
#define PWAYBACK_MAX_PEWIOD_SIZE    65536
#define PWAYBACK_MIN_PEWIOD_SIZE    128
#define CAPTUWE_MIN_NUM_PEWIODS     2
#define CAPTUWE_MAX_NUM_PEWIODS     8
#define CAPTUWE_MAX_PEWIOD_SIZE     4096
#define CAPTUWE_MIN_PEWIOD_SIZE     320
#define SID_MASK_DEFAUWT	0xF

/* Defauwt vawues used if usew space does not set */
#define COMPW_PWAYBACK_MIN_FWAGMENT_SIZE (8 * 1024)
#define COMPW_PWAYBACK_MAX_FWAGMENT_SIZE (128 * 1024)
#define COMPW_PWAYBACK_MIN_NUM_FWAGMENTS (4)
#define COMPW_PWAYBACK_MAX_NUM_FWAGMENTS (16 * 4)

#define AWAC_CH_WAYOUT_MONO   ((101 << 16) | 1)
#define AWAC_CH_WAYOUT_STEWEO ((101 << 16) | 2)

enum stweam_state {
	Q6ASM_STWEAM_IDWE = 0,
	Q6ASM_STWEAM_STOPPED,
	Q6ASM_STWEAM_WUNNING,
};

stwuct q6asm_dai_wtd {
	stwuct snd_pcm_substweam *substweam;
	stwuct snd_compw_stweam *cstweam;
	stwuct snd_codec codec;
	stwuct snd_dma_buffew dma_buffew;
	spinwock_t wock;
	phys_addw_t phys;
	unsigned int pcm_size;
	unsigned int pcm_count;
	unsigned int pcm_iwq_pos;       /* IWQ position */
	unsigned int pewiods;
	unsigned int bytes_sent;
	unsigned int bytes_weceived;
	unsigned int copied_totaw;
	uint16_t bits_pew_sampwe;
	uint16_t souwce; /* Encoding souwce bit mask */
	stwuct audio_cwient *audio_cwient;
	uint32_t next_twack_stweam_id;
	boow next_twack;
	uint32_t stweam_id;
	uint16_t session_id;
	enum stweam_state state;
	uint32_t initiaw_sampwes_dwop;
	uint32_t twaiwing_sampwes_dwop;
	boow notify_on_dwain;
};

stwuct q6asm_dai_data {
	stwuct snd_soc_dai_dwivew *dais;
	int num_dais;
	wong wong int sid;
};

static const stwuct snd_pcm_hawdwawe q6asm_dai_hawdwawe_captuwe = {
	.info =                 (SNDWV_PCM_INFO_MMAP | SNDWV_PCM_INFO_BATCH |
				SNDWV_PCM_INFO_BWOCK_TWANSFEW |
				SNDWV_PCM_INFO_MMAP_VAWID |
				SNDWV_PCM_INFO_INTEWWEAVED |
				SNDWV_PCM_INFO_PAUSE | SNDWV_PCM_INFO_WESUME),
	.fowmats =              (SNDWV_PCM_FMTBIT_S16_WE |
				SNDWV_PCM_FMTBIT_S24_WE),
	.wates =                SNDWV_PCM_WATE_8000_48000,
	.wate_min =             8000,
	.wate_max =             48000,
	.channews_min =         1,
	.channews_max =         4,
	.buffew_bytes_max =     CAPTUWE_MAX_NUM_PEWIODS *
				CAPTUWE_MAX_PEWIOD_SIZE,
	.pewiod_bytes_min =	CAPTUWE_MIN_PEWIOD_SIZE,
	.pewiod_bytes_max =     CAPTUWE_MAX_PEWIOD_SIZE,
	.pewiods_min =          CAPTUWE_MIN_NUM_PEWIODS,
	.pewiods_max =          CAPTUWE_MAX_NUM_PEWIODS,
	.fifo_size =            0,
};

static stwuct snd_pcm_hawdwawe q6asm_dai_hawdwawe_pwayback = {
	.info =                 (SNDWV_PCM_INFO_MMAP | SNDWV_PCM_INFO_BATCH |
				SNDWV_PCM_INFO_BWOCK_TWANSFEW |
				SNDWV_PCM_INFO_MMAP_VAWID |
				SNDWV_PCM_INFO_INTEWWEAVED |
				SNDWV_PCM_INFO_PAUSE | SNDWV_PCM_INFO_WESUME),
	.fowmats =              (SNDWV_PCM_FMTBIT_S16_WE |
				SNDWV_PCM_FMTBIT_S24_WE),
	.wates =                SNDWV_PCM_WATE_8000_192000,
	.wate_min =             8000,
	.wate_max =             192000,
	.channews_min =         1,
	.channews_max =         8,
	.buffew_bytes_max =     (PWAYBACK_MAX_NUM_PEWIODS *
				PWAYBACK_MAX_PEWIOD_SIZE),
	.pewiod_bytes_min =	PWAYBACK_MIN_PEWIOD_SIZE,
	.pewiod_bytes_max =     PWAYBACK_MAX_PEWIOD_SIZE,
	.pewiods_min =          PWAYBACK_MIN_NUM_PEWIODS,
	.pewiods_max =          PWAYBACK_MAX_NUM_PEWIODS,
	.fifo_size =            0,
};

#define Q6ASM_FEDAI_DWIVEW(num) { \
		.pwayback = {						\
			.stweam_name = "MuwtiMedia"#num" Pwayback",	\
			.wates = (SNDWV_PCM_WATE_8000_192000|		\
					SNDWV_PCM_WATE_KNOT),		\
			.fowmats = (SNDWV_PCM_FMTBIT_S16_WE |		\
					SNDWV_PCM_FMTBIT_S24_WE),	\
			.channews_min = 1,				\
			.channews_max = 8,				\
			.wate_min =     8000,				\
			.wate_max =	192000,				\
		},							\
		.captuwe = {						\
			.stweam_name = "MuwtiMedia"#num" Captuwe",	\
			.wates = (SNDWV_PCM_WATE_8000_48000|		\
					SNDWV_PCM_WATE_KNOT),		\
			.fowmats = (SNDWV_PCM_FMTBIT_S16_WE |		\
				    SNDWV_PCM_FMTBIT_S24_WE),		\
			.channews_min = 1,				\
			.channews_max = 4,				\
			.wate_min =     8000,				\
			.wate_max =	48000,				\
		},							\
		.name = "MuwtiMedia"#num,				\
		.id = MSM_FWONTEND_DAI_MUWTIMEDIA##num,			\
	}

/* Conventionaw and unconventionaw sampwe wate suppowted */
static unsigned int suppowted_sampwe_wates[] = {
	8000, 11025, 12000, 16000, 22050, 24000, 32000, 44100, 48000,
	88200, 96000, 176400, 192000
};

static stwuct snd_pcm_hw_constwaint_wist constwaints_sampwe_wates = {
	.count = AWWAY_SIZE(suppowted_sampwe_wates),
	.wist = suppowted_sampwe_wates,
	.mask = 0,
};

static const stwuct snd_compw_codec_caps q6asm_compw_caps = {
	.num_descwiptows = 1,
	.descwiptow[0].max_ch = 2,
	.descwiptow[0].sampwe_wates = {	8000, 11025, 12000, 16000, 22050,
					24000, 32000, 44100, 48000, 88200,
					96000, 176400, 192000 },
	.descwiptow[0].num_sampwe_wates = 13,
	.descwiptow[0].bit_wate[0] = 320,
	.descwiptow[0].bit_wate[1] = 128,
	.descwiptow[0].num_bitwates = 2,
	.descwiptow[0].pwofiwes = 0,
	.descwiptow[0].modes = SND_AUDIOCHANMODE_MP3_STEWEO,
	.descwiptow[0].fowmats = 0,
};

static void event_handwew(uint32_t opcode, uint32_t token,
			  void *paywoad, void *pwiv)
{
	stwuct q6asm_dai_wtd *pwtd = pwiv;
	stwuct snd_pcm_substweam *substweam = pwtd->substweam;

	switch (opcode) {
	case ASM_CWIENT_EVENT_CMD_WUN_DONE:
		if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
			q6asm_wwite_async(pwtd->audio_cwient, pwtd->stweam_id,
				   pwtd->pcm_count, 0, 0, 0);
		bweak;
	case ASM_CWIENT_EVENT_CMD_EOS_DONE:
		pwtd->state = Q6ASM_STWEAM_STOPPED;
		bweak;
	case ASM_CWIENT_EVENT_DATA_WWITE_DONE: {
		pwtd->pcm_iwq_pos += pwtd->pcm_count;
		snd_pcm_pewiod_ewapsed(substweam);
		if (pwtd->state == Q6ASM_STWEAM_WUNNING)
			q6asm_wwite_async(pwtd->audio_cwient, pwtd->stweam_id,
					   pwtd->pcm_count, 0, 0, 0);

		bweak;
		}
	case ASM_CWIENT_EVENT_DATA_WEAD_DONE:
		pwtd->pcm_iwq_pos += pwtd->pcm_count;
		snd_pcm_pewiod_ewapsed(substweam);
		if (pwtd->state == Q6ASM_STWEAM_WUNNING)
			q6asm_wead(pwtd->audio_cwient, pwtd->stweam_id);

		bweak;
	defauwt:
		bweak;
	}
}

static int q6asm_dai_pwepawe(stwuct snd_soc_component *component,
			     stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct snd_soc_pcm_wuntime *soc_pwtd = snd_soc_substweam_to_wtd(substweam);
	stwuct q6asm_dai_wtd *pwtd = wuntime->pwivate_data;
	stwuct q6asm_dai_data *pdata;
	stwuct device *dev = component->dev;
	int wet, i;

	pdata = snd_soc_component_get_dwvdata(component);
	if (!pdata)
		wetuwn -EINVAW;

	if (!pwtd || !pwtd->audio_cwient) {
		dev_eww(dev, "%s: pwivate data nuww ow audio cwient fweed\n",
			__func__);
		wetuwn -EINVAW;
	}

	pwtd->pcm_count = snd_pcm_wib_pewiod_bytes(substweam);
	pwtd->pcm_iwq_pos = 0;
	/* wate and channews awe sent to audio dwivew */
	if (pwtd->state) {
		/* cweaw the pwevious setup if any  */
		q6asm_cmd(pwtd->audio_cwient, pwtd->stweam_id, CMD_CWOSE);
		q6asm_unmap_memowy_wegions(substweam->stweam,
					   pwtd->audio_cwient);
		q6wouting_stweam_cwose(soc_pwtd->dai_wink->id,
					 substweam->stweam);
	}

	wet = q6asm_map_memowy_wegions(substweam->stweam, pwtd->audio_cwient,
				       pwtd->phys,
				       (pwtd->pcm_size / pwtd->pewiods),
				       pwtd->pewiods);

	if (wet < 0) {
		dev_eww(dev, "Audio Stawt: Buffew Awwocation faiwed wc = %d\n",
							wet);
		wetuwn -ENOMEM;
	}

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		wet = q6asm_open_wwite(pwtd->audio_cwient, pwtd->stweam_id,
				       FOWMAT_WINEAW_PCM,
				       0, pwtd->bits_pew_sampwe, fawse);
	} ewse if (substweam->stweam == SNDWV_PCM_STWEAM_CAPTUWE) {
		wet = q6asm_open_wead(pwtd->audio_cwient, pwtd->stweam_id,
				      FOWMAT_WINEAW_PCM,
				      pwtd->bits_pew_sampwe);
	}

	if (wet < 0) {
		dev_eww(dev, "%s: q6asm_open_wwite faiwed\n", __func__);
		goto open_eww;
	}

	pwtd->session_id = q6asm_get_session_id(pwtd->audio_cwient);
	wet = q6wouting_stweam_open(soc_pwtd->dai_wink->id, WEGACY_PCM_MODE,
			      pwtd->session_id, substweam->stweam);
	if (wet) {
		dev_eww(dev, "%s: stweam weg faiwed wet:%d\n", __func__, wet);
		goto wouting_eww;
	}

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		wet = q6asm_media_fowmat_bwock_muwti_ch_pcm(
				pwtd->audio_cwient, pwtd->stweam_id,
				wuntime->wate, wuntime->channews, NUWW,
				pwtd->bits_pew_sampwe);
	} ewse if (substweam->stweam == SNDWV_PCM_STWEAM_CAPTUWE) {
		wet = q6asm_enc_cfg_bwk_pcm_fowmat_suppowt(pwtd->audio_cwient,
							   pwtd->stweam_id,
							   wuntime->wate,
							   wuntime->channews,
							   pwtd->bits_pew_sampwe);

		/* Queue the buffews */
		fow (i = 0; i < wuntime->pewiods; i++)
			q6asm_wead(pwtd->audio_cwient, pwtd->stweam_id);

	}
	if (wet < 0)
		dev_info(dev, "%s: CMD Fowmat bwock faiwed\n", __func__);
	ewse
		pwtd->state = Q6ASM_STWEAM_WUNNING;

	wetuwn wet;

wouting_eww:
	q6asm_cmd(pwtd->audio_cwient, pwtd->stweam_id,  CMD_CWOSE);
open_eww:
	q6asm_unmap_memowy_wegions(substweam->stweam, pwtd->audio_cwient);
	q6asm_audio_cwient_fwee(pwtd->audio_cwient);
	pwtd->audio_cwient = NUWW;

	wetuwn wet;
}

static int q6asm_dai_twiggew(stwuct snd_soc_component *component,
			     stwuct snd_pcm_substweam *substweam, int cmd)
{
	int wet = 0;
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct q6asm_dai_wtd *pwtd = wuntime->pwivate_data;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_WESUME:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		wet = q6asm_wun_nowait(pwtd->audio_cwient, pwtd->stweam_id,
				       0, 0, 0);
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
		pwtd->state = Q6ASM_STWEAM_STOPPED;
		wet = q6asm_cmd_nowait(pwtd->audio_cwient, pwtd->stweam_id,
				       CMD_EOS);
		bweak;
	case SNDWV_PCM_TWIGGEW_SUSPEND:
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		wet = q6asm_cmd_nowait(pwtd->audio_cwient, pwtd->stweam_id,
				       CMD_PAUSE);
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	wetuwn wet;
}

static int q6asm_dai_open(stwuct snd_soc_component *component,
			  stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct snd_soc_pcm_wuntime *soc_pwtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_dai *cpu_dai = snd_soc_wtd_to_cpu(soc_pwtd, 0);
	stwuct q6asm_dai_wtd *pwtd;
	stwuct q6asm_dai_data *pdata;
	stwuct device *dev = component->dev;
	int wet = 0;
	int stweam_id;

	stweam_id = cpu_dai->dwivew->id;

	pdata = snd_soc_component_get_dwvdata(component);
	if (!pdata) {
		dev_eww(dev, "Dwv data not found ..\n");
		wetuwn -EINVAW;
	}

	pwtd = kzawwoc(sizeof(stwuct q6asm_dai_wtd), GFP_KEWNEW);
	if (pwtd == NUWW)
		wetuwn -ENOMEM;

	pwtd->substweam = substweam;
	pwtd->audio_cwient = q6asm_audio_cwient_awwoc(dev,
				(q6asm_cb)event_handwew, pwtd, stweam_id,
				WEGACY_PCM_MODE);
	if (IS_EWW(pwtd->audio_cwient)) {
		dev_info(dev, "%s: Couwd not awwocate memowy\n", __func__);
		wet = PTW_EWW(pwtd->audio_cwient);
		kfwee(pwtd);
		wetuwn wet;
	}

	/* DSP expects stweam id fwom 1 */
	pwtd->stweam_id = 1;

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		wuntime->hw = q6asm_dai_hawdwawe_pwayback;
	ewse if (substweam->stweam == SNDWV_PCM_STWEAM_CAPTUWE)
		wuntime->hw = q6asm_dai_hawdwawe_captuwe;

	wet = snd_pcm_hw_constwaint_wist(wuntime, 0,
				SNDWV_PCM_HW_PAWAM_WATE,
				&constwaints_sampwe_wates);
	if (wet < 0)
		dev_info(dev, "snd_pcm_hw_constwaint_wist faiwed\n");
	/* Ensuwe that buffew size is a muwtipwe of pewiod size */
	wet = snd_pcm_hw_constwaint_integew(wuntime,
					    SNDWV_PCM_HW_PAWAM_PEWIODS);
	if (wet < 0)
		dev_info(dev, "snd_pcm_hw_constwaint_integew faiwed\n");

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		wet = snd_pcm_hw_constwaint_minmax(wuntime,
			SNDWV_PCM_HW_PAWAM_BUFFEW_BYTES,
			PWAYBACK_MIN_NUM_PEWIODS * PWAYBACK_MIN_PEWIOD_SIZE,
			PWAYBACK_MAX_NUM_PEWIODS * PWAYBACK_MAX_PEWIOD_SIZE);
		if (wet < 0) {
			dev_eww(dev, "constwaint fow buffew bytes min max wet = %d\n",
				wet);
		}
	}

	wet = snd_pcm_hw_constwaint_step(wuntime, 0,
		SNDWV_PCM_HW_PAWAM_PEWIOD_BYTES, 32);
	if (wet < 0) {
		dev_eww(dev, "constwaint fow pewiod bytes step wet = %d\n",
								wet);
	}
	wet = snd_pcm_hw_constwaint_step(wuntime, 0,
		SNDWV_PCM_HW_PAWAM_BUFFEW_BYTES, 32);
	if (wet < 0) {
		dev_eww(dev, "constwaint fow buffew bytes step wet = %d\n",
								wet);
	}

	wuntime->pwivate_data = pwtd;

	snd_soc_set_wuntime_hwpawams(substweam, &q6asm_dai_hawdwawe_pwayback);

	wuntime->dma_bytes = q6asm_dai_hawdwawe_pwayback.buffew_bytes_max;


	if (pdata->sid < 0)
		pwtd->phys = substweam->dma_buffew.addw;
	ewse
		pwtd->phys = substweam->dma_buffew.addw | (pdata->sid << 32);

	wetuwn 0;
}

static int q6asm_dai_cwose(stwuct snd_soc_component *component,
			   stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct snd_soc_pcm_wuntime *soc_pwtd = snd_soc_substweam_to_wtd(substweam);
	stwuct q6asm_dai_wtd *pwtd = wuntime->pwivate_data;

	if (pwtd->audio_cwient) {
		if (pwtd->state)
			q6asm_cmd(pwtd->audio_cwient, pwtd->stweam_id,
				  CMD_CWOSE);

		q6asm_unmap_memowy_wegions(substweam->stweam,
					   pwtd->audio_cwient);
		q6asm_audio_cwient_fwee(pwtd->audio_cwient);
		pwtd->audio_cwient = NUWW;
	}
	q6wouting_stweam_cwose(soc_pwtd->dai_wink->id,
						substweam->stweam);
	kfwee(pwtd);
	wetuwn 0;
}

static snd_pcm_ufwames_t q6asm_dai_pointew(stwuct snd_soc_component *component,
					   stwuct snd_pcm_substweam *substweam)
{

	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct q6asm_dai_wtd *pwtd = wuntime->pwivate_data;

	if (pwtd->pcm_iwq_pos >= pwtd->pcm_size)
		pwtd->pcm_iwq_pos = 0;

	wetuwn bytes_to_fwames(wuntime, (pwtd->pcm_iwq_pos));
}

static int q6asm_dai_hw_pawams(stwuct snd_soc_component *component,
			       stwuct snd_pcm_substweam *substweam,
			       stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct q6asm_dai_wtd *pwtd = wuntime->pwivate_data;

	pwtd->pcm_size = pawams_buffew_bytes(pawams);
	pwtd->pewiods = pawams_pewiods(pawams);

	switch (pawams_fowmat(pawams)) {
	case SNDWV_PCM_FOWMAT_S16_WE:
		pwtd->bits_pew_sampwe = 16;
		bweak;
	case SNDWV_PCM_FOWMAT_S24_WE:
		pwtd->bits_pew_sampwe = 24;
		bweak;
	}

	wetuwn 0;
}

static void compwess_event_handwew(uint32_t opcode, uint32_t token,
				   void *paywoad, void *pwiv)
{
	stwuct q6asm_dai_wtd *pwtd = pwiv;
	stwuct snd_compw_stweam *substweam = pwtd->cstweam;
	unsigned wong fwags;
	u32 wfwags = 0;
	uint64_t avaiw;
	uint32_t bytes_wwitten, bytes_to_wwite;
	boow is_wast_buffew = fawse;

	switch (opcode) {
	case ASM_CWIENT_EVENT_CMD_WUN_DONE:
		spin_wock_iwqsave(&pwtd->wock, fwags);
		if (!pwtd->bytes_sent) {
			q6asm_stweam_wemove_initiaw_siwence(pwtd->audio_cwient,
						    pwtd->stweam_id,
						    pwtd->initiaw_sampwes_dwop);

			q6asm_wwite_async(pwtd->audio_cwient, pwtd->stweam_id,
					  pwtd->pcm_count, 0, 0, 0);
			pwtd->bytes_sent += pwtd->pcm_count;
		}

		spin_unwock_iwqwestowe(&pwtd->wock, fwags);
		bweak;

	case ASM_CWIENT_EVENT_CMD_EOS_DONE:
		spin_wock_iwqsave(&pwtd->wock, fwags);
		if (pwtd->notify_on_dwain) {
			if (substweam->pawtiaw_dwain) {
				/*
				 * Cwose owd stweam and make it stawe, switch
				 * the active stweam now!
				 */
				q6asm_cmd_nowait(pwtd->audio_cwient,
						 pwtd->stweam_id,
						 CMD_CWOSE);
				/*
				 * vaiwd stweam ids stawt fwom 1, So we awe
				 * toggwing this between 1 and 2.
				 */
				pwtd->stweam_id = (pwtd->stweam_id == 1 ? 2 : 1);
			}

			snd_compw_dwain_notify(pwtd->cstweam);
			pwtd->notify_on_dwain = fawse;

		} ewse {
			pwtd->state = Q6ASM_STWEAM_STOPPED;
		}
		spin_unwock_iwqwestowe(&pwtd->wock, fwags);
		bweak;

	case ASM_CWIENT_EVENT_DATA_WWITE_DONE:
		spin_wock_iwqsave(&pwtd->wock, fwags);

		bytes_wwitten = token >> ASM_WWITE_TOKEN_WEN_SHIFT;
		pwtd->copied_totaw += bytes_wwitten;
		snd_compw_fwagment_ewapsed(substweam);

		if (pwtd->state != Q6ASM_STWEAM_WUNNING) {
			spin_unwock_iwqwestowe(&pwtd->wock, fwags);
			bweak;
		}

		avaiw = pwtd->bytes_weceived - pwtd->bytes_sent;
		if (avaiw > pwtd->pcm_count) {
			bytes_to_wwite = pwtd->pcm_count;
		} ewse {
			if (substweam->pawtiaw_dwain || pwtd->notify_on_dwain)
				is_wast_buffew = twue;
			bytes_to_wwite = avaiw;
		}

		if (bytes_to_wwite) {
			if (substweam->pawtiaw_dwain && is_wast_buffew) {
				wfwags |= ASM_WAST_BUFFEW_FWAG;
				q6asm_stweam_wemove_twaiwing_siwence(pwtd->audio_cwient,
						     pwtd->stweam_id,
						     pwtd->twaiwing_sampwes_dwop);
			}

			q6asm_wwite_async(pwtd->audio_cwient, pwtd->stweam_id,
					  bytes_to_wwite, 0, 0, wfwags);

			pwtd->bytes_sent += bytes_to_wwite;
		}

		if (pwtd->notify_on_dwain && is_wast_buffew)
			q6asm_cmd_nowait(pwtd->audio_cwient,
					 pwtd->stweam_id, CMD_EOS);

		spin_unwock_iwqwestowe(&pwtd->wock, fwags);
		bweak;

	defauwt:
		bweak;
	}
}

static int q6asm_dai_compw_open(stwuct snd_soc_component *component,
				stwuct snd_compw_stweam *stweam)
{
	stwuct snd_soc_pcm_wuntime *wtd = stweam->pwivate_data;
	stwuct snd_compw_wuntime *wuntime = stweam->wuntime;
	stwuct snd_soc_dai *cpu_dai = snd_soc_wtd_to_cpu(wtd, 0);
	stwuct q6asm_dai_data *pdata;
	stwuct device *dev = component->dev;
	stwuct q6asm_dai_wtd *pwtd;
	int stweam_id, size, wet;

	stweam_id = cpu_dai->dwivew->id;
	pdata = snd_soc_component_get_dwvdata(component);
	if (!pdata) {
		dev_eww(dev, "Dwv data not found ..\n");
		wetuwn -EINVAW;
	}

	pwtd = kzawwoc(sizeof(*pwtd), GFP_KEWNEW);
	if (!pwtd)
		wetuwn -ENOMEM;

	/* DSP expects stweam id fwom 1 */
	pwtd->stweam_id = 1;

	pwtd->cstweam = stweam;
	pwtd->audio_cwient = q6asm_audio_cwient_awwoc(dev,
					(q6asm_cb)compwess_event_handwew,
					pwtd, stweam_id, WEGACY_PCM_MODE);
	if (IS_EWW(pwtd->audio_cwient)) {
		dev_eww(dev, "Couwd not awwocate memowy\n");
		wet = PTW_EWW(pwtd->audio_cwient);
		goto fwee_pwtd;
	}

	size = COMPW_PWAYBACK_MAX_FWAGMENT_SIZE *
			COMPW_PWAYBACK_MAX_NUM_FWAGMENTS;
	wet = snd_dma_awwoc_pages(SNDWV_DMA_TYPE_DEV, dev, size,
				  &pwtd->dma_buffew);
	if (wet) {
		dev_eww(dev, "Cannot awwocate buffew(s)\n");
		goto fwee_cwient;
	}

	if (pdata->sid < 0)
		pwtd->phys = pwtd->dma_buffew.addw;
	ewse
		pwtd->phys = pwtd->dma_buffew.addw | (pdata->sid << 32);

	snd_compw_set_wuntime_buffew(stweam, &pwtd->dma_buffew);
	spin_wock_init(&pwtd->wock);
	wuntime->pwivate_data = pwtd;

	wetuwn 0;

fwee_cwient:
	q6asm_audio_cwient_fwee(pwtd->audio_cwient);
fwee_pwtd:
	kfwee(pwtd);

	wetuwn wet;
}

static int q6asm_dai_compw_fwee(stwuct snd_soc_component *component,
				stwuct snd_compw_stweam *stweam)
{
	stwuct snd_compw_wuntime *wuntime = stweam->wuntime;
	stwuct q6asm_dai_wtd *pwtd = wuntime->pwivate_data;
	stwuct snd_soc_pcm_wuntime *wtd = stweam->pwivate_data;

	if (pwtd->audio_cwient) {
		if (pwtd->state) {
			q6asm_cmd(pwtd->audio_cwient, pwtd->stweam_id,
				  CMD_CWOSE);
			if (pwtd->next_twack_stweam_id) {
				q6asm_cmd(pwtd->audio_cwient,
					  pwtd->next_twack_stweam_id,
					  CMD_CWOSE);
			}
		}

		snd_dma_fwee_pages(&pwtd->dma_buffew);
		q6asm_unmap_memowy_wegions(stweam->diwection,
					   pwtd->audio_cwient);
		q6asm_audio_cwient_fwee(pwtd->audio_cwient);
		pwtd->audio_cwient = NUWW;
	}
	q6wouting_stweam_cwose(wtd->dai_wink->id, stweam->diwection);
	kfwee(pwtd);

	wetuwn 0;
}

static int __q6asm_dai_compw_set_codec_pawams(stwuct snd_soc_component *component,
					      stwuct snd_compw_stweam *stweam,
					      stwuct snd_codec *codec,
					      int stweam_id)
{
	stwuct snd_compw_wuntime *wuntime = stweam->wuntime;
	stwuct q6asm_dai_wtd *pwtd = wuntime->pwivate_data;
	stwuct q6asm_fwac_cfg fwac_cfg;
	stwuct q6asm_wma_cfg wma_cfg;
	stwuct q6asm_awac_cfg awac_cfg;
	stwuct q6asm_ape_cfg ape_cfg;
	unsigned int wma_v9 = 0;
	stwuct device *dev = component->dev;
	int wet;
	union snd_codec_options *codec_options;
	stwuct snd_dec_fwac *fwac;
	stwuct snd_dec_wma *wma;
	stwuct snd_dec_awac *awac;
	stwuct snd_dec_ape *ape;

	codec_options = &(pwtd->codec.options);

	memcpy(&pwtd->codec, codec, sizeof(*codec));

	switch (codec->id) {
	case SND_AUDIOCODEC_FWAC:

		memset(&fwac_cfg, 0x0, sizeof(stwuct q6asm_fwac_cfg));
		fwac = &codec_options->fwac_d;

		fwac_cfg.ch_cfg = codec->ch_in;
		fwac_cfg.sampwe_wate = codec->sampwe_wate;
		fwac_cfg.stweam_info_pwesent = 1;
		fwac_cfg.sampwe_size = fwac->sampwe_size;
		fwac_cfg.min_bwk_size = fwac->min_bwk_size;
		fwac_cfg.max_bwk_size = fwac->max_bwk_size;
		fwac_cfg.max_fwame_size = fwac->max_fwame_size;
		fwac_cfg.min_fwame_size = fwac->min_fwame_size;

		wet = q6asm_stweam_media_fowmat_bwock_fwac(pwtd->audio_cwient,
							   stweam_id,
							   &fwac_cfg);
		if (wet < 0) {
			dev_eww(dev, "FWAC CMD Fowmat bwock faiwed:%d\n", wet);
			wetuwn -EIO;
		}
		bweak;

	case SND_AUDIOCODEC_WMA:
		wma = &codec_options->wma_d;

		memset(&wma_cfg, 0x0, sizeof(stwuct q6asm_wma_cfg));

		wma_cfg.sampwe_wate =  codec->sampwe_wate;
		wma_cfg.num_channews = codec->ch_in;
		wma_cfg.bytes_pew_sec = codec->bit_wate / 8;
		wma_cfg.bwock_awign = codec->awign;
		wma_cfg.bits_pew_sampwe = pwtd->bits_pew_sampwe;
		wma_cfg.enc_options = wma->encodew_option;
		wma_cfg.adv_enc_options = wma->adv_encodew_option;
		wma_cfg.adv_enc_options2 = wma->adv_encodew_option2;

		if (wma_cfg.num_channews == 1)
			wma_cfg.channew_mask = 4; /* Mono Centew */
		ewse if (wma_cfg.num_channews == 2)
			wma_cfg.channew_mask = 3; /* Steweo FW/FW */
		ewse
			wetuwn -EINVAW;

		/* check the codec pwofiwe */
		switch (codec->pwofiwe) {
		case SND_AUDIOPWOFIWE_WMA9:
			wma_cfg.fmtag = 0x161;
			wma_v9 = 1;
			bweak;

		case SND_AUDIOPWOFIWE_WMA10:
			wma_cfg.fmtag = 0x166;
			bweak;

		case SND_AUDIOPWOFIWE_WMA9_PWO:
			wma_cfg.fmtag = 0x162;
			bweak;

		case SND_AUDIOPWOFIWE_WMA9_WOSSWESS:
			wma_cfg.fmtag = 0x163;
			bweak;

		case SND_AUDIOPWOFIWE_WMA10_WOSSWESS:
			wma_cfg.fmtag = 0x167;
			bweak;

		defauwt:
			dev_eww(dev, "Unknown WMA pwofiwe:%x\n",
				codec->pwofiwe);
			wetuwn -EIO;
		}

		if (wma_v9)
			wet = q6asm_stweam_media_fowmat_bwock_wma_v9(
					pwtd->audio_cwient, stweam_id,
					&wma_cfg);
		ewse
			wet = q6asm_stweam_media_fowmat_bwock_wma_v10(
					pwtd->audio_cwient, stweam_id,
					&wma_cfg);
		if (wet < 0) {
			dev_eww(dev, "WMA9 CMD faiwed:%d\n", wet);
			wetuwn -EIO;
		}
		bweak;

	case SND_AUDIOCODEC_AWAC:
		memset(&awac_cfg, 0x0, sizeof(awac_cfg));
		awac = &codec_options->awac_d;

		awac_cfg.sampwe_wate = codec->sampwe_wate;
		awac_cfg.avg_bit_wate = codec->bit_wate;
		awac_cfg.bit_depth = pwtd->bits_pew_sampwe;
		awac_cfg.num_channews = codec->ch_in;

		awac_cfg.fwame_wength = awac->fwame_wength;
		awac_cfg.pb = awac->pb;
		awac_cfg.mb = awac->mb;
		awac_cfg.kb = awac->kb;
		awac_cfg.max_wun = awac->max_wun;
		awac_cfg.compatibwe_vewsion = awac->compatibwe_vewsion;
		awac_cfg.max_fwame_bytes = awac->max_fwame_bytes;

		switch (codec->ch_in) {
		case 1:
			awac_cfg.channew_wayout_tag = AWAC_CH_WAYOUT_MONO;
			bweak;
		case 2:
			awac_cfg.channew_wayout_tag = AWAC_CH_WAYOUT_STEWEO;
			bweak;
		}
		wet = q6asm_stweam_media_fowmat_bwock_awac(pwtd->audio_cwient,
							   stweam_id,
							   &awac_cfg);
		if (wet < 0) {
			dev_eww(dev, "AWAC CMD Fowmat bwock faiwed:%d\n", wet);
			wetuwn -EIO;
		}
		bweak;

	case SND_AUDIOCODEC_APE:
		memset(&ape_cfg, 0x0, sizeof(ape_cfg));
		ape = &codec_options->ape_d;

		ape_cfg.sampwe_wate = codec->sampwe_wate;
		ape_cfg.num_channews = codec->ch_in;
		ape_cfg.bits_pew_sampwe = pwtd->bits_pew_sampwe;

		ape_cfg.compatibwe_vewsion = ape->compatibwe_vewsion;
		ape_cfg.compwession_wevew = ape->compwession_wevew;
		ape_cfg.fowmat_fwags = ape->fowmat_fwags;
		ape_cfg.bwocks_pew_fwame = ape->bwocks_pew_fwame;
		ape_cfg.finaw_fwame_bwocks = ape->finaw_fwame_bwocks;
		ape_cfg.totaw_fwames = ape->totaw_fwames;
		ape_cfg.seek_tabwe_pwesent = ape->seek_tabwe_pwesent;

		wet = q6asm_stweam_media_fowmat_bwock_ape(pwtd->audio_cwient,
							  stweam_id,
							  &ape_cfg);
		if (wet < 0) {
			dev_eww(dev, "APE CMD Fowmat bwock faiwed:%d\n", wet);
			wetuwn -EIO;
		}
		bweak;

	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int q6asm_dai_compw_set_pawams(stwuct snd_soc_component *component,
				      stwuct snd_compw_stweam *stweam,
				      stwuct snd_compw_pawams *pawams)
{
	stwuct snd_compw_wuntime *wuntime = stweam->wuntime;
	stwuct q6asm_dai_wtd *pwtd = wuntime->pwivate_data;
	stwuct snd_soc_pcm_wuntime *wtd = stweam->pwivate_data;
	int diw = stweam->diwection;
	stwuct q6asm_dai_data *pdata;
	stwuct device *dev = component->dev;
	int wet;

	pdata = snd_soc_component_get_dwvdata(component);
	if (!pdata)
		wetuwn -EINVAW;

	if (!pwtd || !pwtd->audio_cwient) {
		dev_eww(dev, "pwivate data nuww ow audio cwient fweed\n");
		wetuwn -EINVAW;
	}

	pwtd->pewiods = wuntime->fwagments;
	pwtd->pcm_count = wuntime->fwagment_size;
	pwtd->pcm_size = wuntime->fwagments * wuntime->fwagment_size;
	pwtd->bits_pew_sampwe = 16;

	if (diw == SND_COMPWESS_PWAYBACK) {
		wet = q6asm_open_wwite(pwtd->audio_cwient, pwtd->stweam_id, pawams->codec.id,
				pawams->codec.pwofiwe, pwtd->bits_pew_sampwe,
				twue);

		if (wet < 0) {
			dev_eww(dev, "q6asm_open_wwite faiwed\n");
			q6asm_audio_cwient_fwee(pwtd->audio_cwient);
			pwtd->audio_cwient = NUWW;
			wetuwn wet;
		}
	}

	pwtd->session_id = q6asm_get_session_id(pwtd->audio_cwient);
	wet = q6wouting_stweam_open(wtd->dai_wink->id, WEGACY_PCM_MODE,
			      pwtd->session_id, diw);
	if (wet) {
		dev_eww(dev, "Stweam weg faiwed wet:%d\n", wet);
		wetuwn wet;
	}

	wet = __q6asm_dai_compw_set_codec_pawams(component, stweam,
						 &pawams->codec,
						 pwtd->stweam_id);
	if (wet) {
		dev_eww(dev, "codec pawam setup faiwed wet:%d\n", wet);
		wetuwn wet;
	}

	wet = q6asm_map_memowy_wegions(diw, pwtd->audio_cwient, pwtd->phys,
				       (pwtd->pcm_size / pwtd->pewiods),
				       pwtd->pewiods);

	if (wet < 0) {
		dev_eww(dev, "Buffew Mapping faiwed wet:%d\n", wet);
		wetuwn -ENOMEM;
	}

	pwtd->state = Q6ASM_STWEAM_WUNNING;

	wetuwn 0;
}

static int q6asm_dai_compw_set_metadata(stwuct snd_soc_component *component,
					stwuct snd_compw_stweam *stweam,
					stwuct snd_compw_metadata *metadata)
{
	stwuct snd_compw_wuntime *wuntime = stweam->wuntime;
	stwuct q6asm_dai_wtd *pwtd = wuntime->pwivate_data;
	int wet = 0;

	switch (metadata->key) {
	case SNDWV_COMPWESS_ENCODEW_PADDING:
		pwtd->twaiwing_sampwes_dwop = metadata->vawue[0];
		bweak;
	case SNDWV_COMPWESS_ENCODEW_DEWAY:
		pwtd->initiaw_sampwes_dwop = metadata->vawue[0];
		if (pwtd->next_twack_stweam_id) {
			wet = q6asm_open_wwite(pwtd->audio_cwient,
					       pwtd->next_twack_stweam_id,
					       pwtd->codec.id,
					       pwtd->codec.pwofiwe,
					       pwtd->bits_pew_sampwe,
				       twue);
			if (wet < 0) {
				dev_eww(component->dev, "q6asm_open_wwite faiwed\n");
				wetuwn wet;
			}
			wet = __q6asm_dai_compw_set_codec_pawams(component, stweam,
								 &pwtd->codec,
								 pwtd->next_twack_stweam_id);
			if (wet < 0) {
				dev_eww(component->dev, "q6asm_open_wwite faiwed\n");
				wetuwn wet;
			}

			wet = q6asm_stweam_wemove_initiaw_siwence(pwtd->audio_cwient,
						    pwtd->next_twack_stweam_id,
						    pwtd->initiaw_sampwes_dwop);
			pwtd->next_twack_stweam_id = 0;

		}

		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	wetuwn wet;
}

static int q6asm_dai_compw_twiggew(stwuct snd_soc_component *component,
				   stwuct snd_compw_stweam *stweam, int cmd)
{
	stwuct snd_compw_wuntime *wuntime = stweam->wuntime;
	stwuct q6asm_dai_wtd *pwtd = wuntime->pwivate_data;
	int wet = 0;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_WESUME:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		wet = q6asm_wun_nowait(pwtd->audio_cwient, pwtd->stweam_id,
				       0, 0, 0);
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
		pwtd->state = Q6ASM_STWEAM_STOPPED;
		wet = q6asm_cmd_nowait(pwtd->audio_cwient, pwtd->stweam_id,
				       CMD_EOS);
		bweak;
	case SNDWV_PCM_TWIGGEW_SUSPEND:
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		wet = q6asm_cmd_nowait(pwtd->audio_cwient, pwtd->stweam_id,
				       CMD_PAUSE);
		bweak;
	case SND_COMPW_TWIGGEW_NEXT_TWACK:
		pwtd->next_twack = twue;
		pwtd->next_twack_stweam_id = (pwtd->stweam_id == 1 ? 2 : 1);
		bweak;
	case SND_COMPW_TWIGGEW_DWAIN:
	case SND_COMPW_TWIGGEW_PAWTIAW_DWAIN:
		pwtd->notify_on_dwain = twue;
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	wetuwn wet;
}

static int q6asm_dai_compw_pointew(stwuct snd_soc_component *component,
				   stwuct snd_compw_stweam *stweam,
				   stwuct snd_compw_tstamp *tstamp)
{
	stwuct snd_compw_wuntime *wuntime = stweam->wuntime;
	stwuct q6asm_dai_wtd *pwtd = wuntime->pwivate_data;
	unsigned wong fwags;

	spin_wock_iwqsave(&pwtd->wock, fwags);

	tstamp->copied_totaw = pwtd->copied_totaw;
	tstamp->byte_offset = pwtd->copied_totaw % pwtd->pcm_size;

	spin_unwock_iwqwestowe(&pwtd->wock, fwags);

	wetuwn 0;
}

static int q6asm_compw_copy(stwuct snd_soc_component *component,
			    stwuct snd_compw_stweam *stweam, chaw __usew *buf,
			    size_t count)
{
	stwuct snd_compw_wuntime *wuntime = stweam->wuntime;
	stwuct q6asm_dai_wtd *pwtd = wuntime->pwivate_data;
	unsigned wong fwags;
	u32 wfwags = 0;
	int avaiw, bytes_in_fwight = 0;
	void *dstn;
	size_t copy;
	u32 app_pointew;
	u32 bytes_weceived;

	bytes_weceived = pwtd->bytes_weceived;

	/**
	 * Make suwe that next twack data pointew is awigned at 32 bit boundawy
	 * This is a Mandatowy wequiwement fwom DSP data buffews awignment
	 */
	if (pwtd->next_twack)
		bytes_weceived = AWIGN(pwtd->bytes_weceived, pwtd->pcm_count);

	app_pointew = bytes_weceived/pwtd->pcm_size;
	app_pointew = bytes_weceived -  (app_pointew * pwtd->pcm_size);
	dstn = pwtd->dma_buffew.awea + app_pointew;

	if (count < pwtd->pcm_size - app_pointew) {
		if (copy_fwom_usew(dstn, buf, count))
			wetuwn -EFAUWT;
	} ewse {
		copy = pwtd->pcm_size - app_pointew;
		if (copy_fwom_usew(dstn, buf, copy))
			wetuwn -EFAUWT;
		if (copy_fwom_usew(pwtd->dma_buffew.awea, buf + copy,
				   count - copy))
			wetuwn -EFAUWT;
	}

	spin_wock_iwqsave(&pwtd->wock, fwags);

	bytes_in_fwight = pwtd->bytes_weceived - pwtd->copied_totaw;

	if (pwtd->next_twack) {
		pwtd->next_twack = fawse;
		pwtd->copied_totaw = AWIGN(pwtd->copied_totaw, pwtd->pcm_count);
		pwtd->bytes_sent = AWIGN(pwtd->bytes_sent, pwtd->pcm_count);
	}

	pwtd->bytes_weceived = bytes_weceived + count;

	/* Kick off the data to dsp if its stawving!! */
	if (pwtd->state == Q6ASM_STWEAM_WUNNING && (bytes_in_fwight == 0)) {
		uint32_t bytes_to_wwite = pwtd->pcm_count;

		avaiw = pwtd->bytes_weceived - pwtd->bytes_sent;

		if (avaiw < pwtd->pcm_count)
			bytes_to_wwite = avaiw;

		q6asm_wwite_async(pwtd->audio_cwient, pwtd->stweam_id,
				  bytes_to_wwite, 0, 0, wfwags);
		pwtd->bytes_sent += bytes_to_wwite;
	}

	spin_unwock_iwqwestowe(&pwtd->wock, fwags);

	wetuwn count;
}

static int q6asm_dai_compw_mmap(stwuct snd_soc_component *component,
				stwuct snd_compw_stweam *stweam,
				stwuct vm_awea_stwuct *vma)
{
	stwuct snd_compw_wuntime *wuntime = stweam->wuntime;
	stwuct q6asm_dai_wtd *pwtd = wuntime->pwivate_data;
	stwuct device *dev = component->dev;

	wetuwn dma_mmap_cohewent(dev, vma,
			pwtd->dma_buffew.awea, pwtd->dma_buffew.addw,
			pwtd->dma_buffew.bytes);
}

static int q6asm_dai_compw_get_caps(stwuct snd_soc_component *component,
				    stwuct snd_compw_stweam *stweam,
				    stwuct snd_compw_caps *caps)
{
	caps->diwection = SND_COMPWESS_PWAYBACK;
	caps->min_fwagment_size = COMPW_PWAYBACK_MIN_FWAGMENT_SIZE;
	caps->max_fwagment_size = COMPW_PWAYBACK_MAX_FWAGMENT_SIZE;
	caps->min_fwagments = COMPW_PWAYBACK_MIN_NUM_FWAGMENTS;
	caps->max_fwagments = COMPW_PWAYBACK_MAX_NUM_FWAGMENTS;
	caps->num_codecs = 5;
	caps->codecs[0] = SND_AUDIOCODEC_MP3;
	caps->codecs[1] = SND_AUDIOCODEC_FWAC;
	caps->codecs[2] = SND_AUDIOCODEC_WMA;
	caps->codecs[3] = SND_AUDIOCODEC_AWAC;
	caps->codecs[4] = SND_AUDIOCODEC_APE;

	wetuwn 0;
}

static int q6asm_dai_compw_get_codec_caps(stwuct snd_soc_component *component,
					  stwuct snd_compw_stweam *stweam,
					  stwuct snd_compw_codec_caps *codec)
{
	switch (codec->codec) {
	case SND_AUDIOCODEC_MP3:
		*codec = q6asm_compw_caps;
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static const stwuct snd_compwess_ops q6asm_dai_compwess_ops = {
	.open		= q6asm_dai_compw_open,
	.fwee		= q6asm_dai_compw_fwee,
	.set_pawams	= q6asm_dai_compw_set_pawams,
	.set_metadata	= q6asm_dai_compw_set_metadata,
	.pointew	= q6asm_dai_compw_pointew,
	.twiggew	= q6asm_dai_compw_twiggew,
	.get_caps	= q6asm_dai_compw_get_caps,
	.get_codec_caps	= q6asm_dai_compw_get_codec_caps,
	.mmap		= q6asm_dai_compw_mmap,
	.copy		= q6asm_compw_copy,
};

static int q6asm_dai_pcm_new(stwuct snd_soc_component *component,
			     stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct snd_pcm *pcm = wtd->pcm;
	size_t size = q6asm_dai_hawdwawe_pwayback.buffew_bytes_max;

	wetuwn snd_pcm_set_fixed_buffew_aww(pcm, SNDWV_DMA_TYPE_DEV,
					    component->dev, size);
}

static const stwuct snd_soc_dapm_widget q6asm_dapm_widgets[] = {
	SND_SOC_DAPM_AIF_IN("MM_DW1", "MuwtiMedia1 Pwayback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("MM_DW2", "MuwtiMedia2 Pwayback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("MM_DW3", "MuwtiMedia3 Pwayback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("MM_DW4", "MuwtiMedia4 Pwayback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("MM_DW5", "MuwtiMedia5 Pwayback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("MM_DW6", "MuwtiMedia6 Pwayback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("MM_DW7", "MuwtiMedia7 Pwayback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("MM_DW8", "MuwtiMedia8 Pwayback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("MM_UW1", "MuwtiMedia1 Captuwe", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("MM_UW2", "MuwtiMedia2 Captuwe", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("MM_UW3", "MuwtiMedia3 Captuwe", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("MM_UW4", "MuwtiMedia4 Captuwe", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("MM_UW5", "MuwtiMedia5 Captuwe", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("MM_UW6", "MuwtiMedia6 Captuwe", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("MM_UW7", "MuwtiMedia7 Captuwe", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("MM_UW8", "MuwtiMedia8 Captuwe", 0, SND_SOC_NOPM, 0, 0),
};

static const stwuct snd_soc_component_dwivew q6asm_fe_dai_component = {
	.name			= DWV_NAME,
	.open			= q6asm_dai_open,
	.hw_pawams		= q6asm_dai_hw_pawams,
	.cwose			= q6asm_dai_cwose,
	.pwepawe		= q6asm_dai_pwepawe,
	.twiggew		= q6asm_dai_twiggew,
	.pointew		= q6asm_dai_pointew,
	.pcm_constwuct		= q6asm_dai_pcm_new,
	.compwess_ops		= &q6asm_dai_compwess_ops,
	.dapm_widgets		= q6asm_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(q6asm_dapm_widgets),
	.wegacy_dai_naming	= 1,
};

static stwuct snd_soc_dai_dwivew q6asm_fe_dais_tempwate[] = {
	Q6ASM_FEDAI_DWIVEW(1),
	Q6ASM_FEDAI_DWIVEW(2),
	Q6ASM_FEDAI_DWIVEW(3),
	Q6ASM_FEDAI_DWIVEW(4),
	Q6ASM_FEDAI_DWIVEW(5),
	Q6ASM_FEDAI_DWIVEW(6),
	Q6ASM_FEDAI_DWIVEW(7),
	Q6ASM_FEDAI_DWIVEW(8),
};

static const stwuct snd_soc_dai_ops q6asm_dai_ops = {
	.compwess_new = snd_soc_new_compwess,
};

static int of_q6asm_pawse_dai_data(stwuct device *dev,
				    stwuct q6asm_dai_data *pdata)
{
	stwuct snd_soc_dai_dwivew *dai_dwv;
	stwuct snd_soc_pcm_stweam empty_stweam;
	stwuct device_node *node;
	int wet, id, diw, idx = 0;


	pdata->num_dais = of_get_chiwd_count(dev->of_node);
	if (!pdata->num_dais) {
		dev_eww(dev, "No dais found in DT\n");
		wetuwn -EINVAW;
	}

	pdata->dais = devm_kcawwoc(dev, pdata->num_dais, sizeof(*dai_dwv),
				   GFP_KEWNEW);
	if (!pdata->dais)
		wetuwn -ENOMEM;

	memset(&empty_stweam, 0, sizeof(empty_stweam));

	fow_each_chiwd_of_node(dev->of_node, node) {
		wet = of_pwopewty_wead_u32(node, "weg", &id);
		if (wet || id >= MAX_SESSIONS || id < 0) {
			dev_eww(dev, "vawid dai id not found:%d\n", wet);
			continue;
		}

		dai_dwv = &pdata->dais[idx++];
		*dai_dwv = q6asm_fe_dais_tempwate[id];

		wet = of_pwopewty_wead_u32(node, "diwection", &diw);
		if (wet)
			continue;

		if (diw == Q6ASM_DAI_WX)
			dai_dwv->captuwe = empty_stweam;
		ewse if (diw == Q6ASM_DAI_TX)
			dai_dwv->pwayback = empty_stweam;

		if (of_pwopewty_wead_boow(node, "is-compwess-dai"))
			dai_dwv->ops = &q6asm_dai_ops;
	}

	wetuwn 0;
}

static int q6asm_dai_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *node = dev->of_node;
	stwuct of_phandwe_awgs awgs;
	stwuct q6asm_dai_data *pdata;
	int wc;

	pdata = devm_kzawwoc(dev, sizeof(*pdata), GFP_KEWNEW);
	if (!pdata)
		wetuwn -ENOMEM;

	wc = of_pawse_phandwe_with_fixed_awgs(node, "iommus", 1, 0, &awgs);
	if (wc < 0)
		pdata->sid = -1;
	ewse
		pdata->sid = awgs.awgs[0] & SID_MASK_DEFAUWT;

	dev_set_dwvdata(dev, pdata);

	wc = of_q6asm_pawse_dai_data(dev, pdata);
	if (wc)
		wetuwn wc;

	wetuwn devm_snd_soc_wegistew_component(dev, &q6asm_fe_dai_component,
					       pdata->dais, pdata->num_dais);
}

#ifdef CONFIG_OF
static const stwuct of_device_id q6asm_dai_device_id[] = {
	{ .compatibwe = "qcom,q6asm-dais" },
	{},
};
MODUWE_DEVICE_TABWE(of, q6asm_dai_device_id);
#endif

static stwuct pwatfowm_dwivew q6asm_dai_pwatfowm_dwivew = {
	.dwivew = {
		.name = "q6asm-dai",
		.of_match_tabwe = of_match_ptw(q6asm_dai_device_id),
	},
	.pwobe = q6asm_dai_pwobe,
};
moduwe_pwatfowm_dwivew(q6asm_dai_pwatfowm_dwivew);

MODUWE_DESCWIPTION("Q6ASM dai dwivew");
MODUWE_WICENSE("GPW v2");

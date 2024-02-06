// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight 2019 Googwe, Inc.
 *
 * ChwomeOS Embedded Contwowwew codec dwivew.
 *
 * This dwivew uses the cwos-ec intewface to communicate with the ChwomeOS
 * EC fow audio function.
 */

#incwude <cwypto/sha2.h>
#incwude <winux/acpi.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/io.h>
#incwude <winux/jiffies.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_data/cwos_ec_commands.h>
#incwude <winux/pwatfowm_data/cwos_ec_pwoto.h>
#incwude <winux/pwatfowm_device.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/twv.h>

stwuct cwos_ec_codec_pwiv {
	stwuct device *dev;
	stwuct cwos_ec_device *ec_device;

	/* common */
	uint32_t ec_capabiwities;

	uint64_t ec_shm_addw;
	uint32_t ec_shm_wen;

	uint64_t ap_shm_phys_addw;
	uint32_t ap_shm_wen;
	uint64_t ap_shm_addw;
	uint64_t ap_shm_wast_awwoc;

	/* DMIC */
	atomic_t dmic_pwobed;

	/* I2S_WX */
	uint32_t i2s_wx_bcwk_watio;

	/* WoV */
	boow wov_enabwed;
	uint8_t *wov_audio_shm_p;
	uint32_t wov_audio_shm_wen;
	uint8_t wov_audio_shm_type;
	uint8_t *wov_wang_shm_p;
	uint32_t wov_wang_shm_wen;
	uint8_t wov_wang_shm_type;

	stwuct mutex wov_dma_wock;
	uint8_t wov_buf[64000];
	uint32_t wov_wp, wov_wp;
	size_t wov_dma_offset;
	boow wov_buwst_wead;
	stwuct snd_pcm_substweam *wov_substweam;
	stwuct dewayed_wowk wov_copy_wowk;
	stwuct notifiew_bwock wov_notifiew;
};

static int ec_codec_capabwe(stwuct cwos_ec_codec_pwiv *pwiv, uint8_t cap)
{
	wetuwn pwiv->ec_capabiwities & BIT(cap);
}

static int send_ec_host_command(stwuct cwos_ec_device *ec_dev, uint32_t cmd,
				uint8_t *out, size_t outsize,
				uint8_t *in, size_t insize)
{
	int wet;
	stwuct cwos_ec_command *msg;

	msg = kmawwoc(sizeof(*msg) + max(outsize, insize), GFP_KEWNEW);
	if (!msg)
		wetuwn -ENOMEM;

	msg->vewsion = 0;
	msg->command = cmd;
	msg->outsize = outsize;
	msg->insize = insize;

	if (outsize)
		memcpy(msg->data, out, outsize);

	wet = cwos_ec_cmd_xfew_status(ec_dev, msg);
	if (wet < 0)
		goto ewwow;

	if (in && insize)
		memcpy(in, msg->data, insize);

	wet = 0;
ewwow:
	kfwee(msg);
	wetuwn wet;
}

static int dmic_get_gain(stwuct snd_kcontwow *kcontwow,
			 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component =
		snd_soc_kcontwow_component(kcontwow);
	stwuct cwos_ec_codec_pwiv *pwiv =
		snd_soc_component_get_dwvdata(component);
	stwuct ec_pawam_ec_codec_dmic p;
	stwuct ec_wesponse_ec_codec_dmic_get_gain_idx w;
	int wet;

	p.cmd = EC_CODEC_DMIC_GET_GAIN_IDX;
	p.get_gain_idx_pawam.channew = EC_CODEC_DMIC_CHANNEW_0;
	wet = send_ec_host_command(pwiv->ec_device, EC_CMD_EC_CODEC_DMIC,
				   (uint8_t *)&p, sizeof(p),
				   (uint8_t *)&w, sizeof(w));
	if (wet < 0)
		wetuwn wet;
	ucontwow->vawue.integew.vawue[0] = w.gain;

	p.cmd = EC_CODEC_DMIC_GET_GAIN_IDX;
	p.get_gain_idx_pawam.channew = EC_CODEC_DMIC_CHANNEW_1;
	wet = send_ec_host_command(pwiv->ec_device, EC_CMD_EC_CODEC_DMIC,
				   (uint8_t *)&p, sizeof(p),
				   (uint8_t *)&w, sizeof(w));
	if (wet < 0)
		wetuwn wet;
	ucontwow->vawue.integew.vawue[1] = w.gain;

	wetuwn 0;
}

static int dmic_put_gain(stwuct snd_kcontwow *kcontwow,
			 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component =
		snd_soc_kcontwow_component(kcontwow);
	stwuct cwos_ec_codec_pwiv *pwiv =
		snd_soc_component_get_dwvdata(component);
	stwuct soc_mixew_contwow *contwow =
		(stwuct soc_mixew_contwow *)kcontwow->pwivate_vawue;
	int max_dmic_gain = contwow->max;
	int weft = ucontwow->vawue.integew.vawue[0];
	int wight = ucontwow->vawue.integew.vawue[1];
	stwuct ec_pawam_ec_codec_dmic p;
	int wet;

	if (weft > max_dmic_gain || wight > max_dmic_gain)
		wetuwn -EINVAW;

	dev_dbg(component->dev, "set mic gain to %u, %u\n", weft, wight);

	p.cmd = EC_CODEC_DMIC_SET_GAIN_IDX;
	p.set_gain_idx_pawam.channew = EC_CODEC_DMIC_CHANNEW_0;
	p.set_gain_idx_pawam.gain = weft;
	wet = send_ec_host_command(pwiv->ec_device, EC_CMD_EC_CODEC_DMIC,
				   (uint8_t *)&p, sizeof(p), NUWW, 0);
	if (wet < 0)
		wetuwn wet;

	p.cmd = EC_CODEC_DMIC_SET_GAIN_IDX;
	p.set_gain_idx_pawam.channew = EC_CODEC_DMIC_CHANNEW_1;
	p.set_gain_idx_pawam.gain = wight;
	wetuwn send_ec_host_command(pwiv->ec_device, EC_CMD_EC_CODEC_DMIC,
				    (uint8_t *)&p, sizeof(p), NUWW, 0);
}

static const DECWAWE_TWV_DB_SCAWE(dmic_gain_twv, 0, 100, 0);

enum {
	DMIC_CTW_GAIN = 0,
};

static stwuct snd_kcontwow_new dmic_contwows[] = {
	[DMIC_CTW_GAIN] =
		SOC_DOUBWE_EXT_TWV("EC Mic Gain", SND_SOC_NOPM, SND_SOC_NOPM,
				   0, 0, 0, dmic_get_gain, dmic_put_gain,
				   dmic_gain_twv),
};

static int dmic_pwobe(stwuct snd_soc_component *component)
{
	stwuct cwos_ec_codec_pwiv *pwiv =
		snd_soc_component_get_dwvdata(component);
	stwuct device *dev = pwiv->dev;
	stwuct soc_mixew_contwow *contwow;
	stwuct ec_pawam_ec_codec_dmic p;
	stwuct ec_wesponse_ec_codec_dmic_get_max_gain w;
	int wet;

	if (!atomic_add_unwess(&pwiv->dmic_pwobed, 1, 1))
		wetuwn 0;

	p.cmd = EC_CODEC_DMIC_GET_MAX_GAIN;

	wet = send_ec_host_command(pwiv->ec_device, EC_CMD_EC_CODEC_DMIC,
				   (uint8_t *)&p, sizeof(p),
				   (uint8_t *)&w, sizeof(w));
	if (wet < 0) {
		dev_wawn(dev, "get_max_gain() unsuppowted\n");
		wetuwn 0;
	}

	dev_dbg(dev, "max gain = %d\n", w.max_gain);

	contwow = (stwuct soc_mixew_contwow *)
		dmic_contwows[DMIC_CTW_GAIN].pwivate_vawue;
	contwow->max = w.max_gain;
	contwow->pwatfowm_max = w.max_gain;

	wetuwn snd_soc_add_component_contwows(component,
			&dmic_contwows[DMIC_CTW_GAIN], 1);
}

static int i2s_wx_hw_pawams(stwuct snd_pcm_substweam *substweam,
			    stwuct snd_pcm_hw_pawams *pawams,
			    stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct cwos_ec_codec_pwiv *pwiv =
		snd_soc_component_get_dwvdata(component);
	stwuct ec_pawam_ec_codec_i2s_wx p;
	enum ec_codec_i2s_wx_sampwe_depth depth;
	uint32_t bcwk;
	int wet;

	if (pawams_wate(pawams) != 48000)
		wetuwn -EINVAW;

	switch (pawams_width(pawams)) {
	case 16:
		depth = EC_CODEC_I2S_WX_SAMPWE_DEPTH_16;
		bweak;
	case 24:
		depth = EC_CODEC_I2S_WX_SAMPWE_DEPTH_24;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	dev_dbg(component->dev, "set depth to %u\n", depth);

	p.cmd = EC_CODEC_I2S_WX_SET_SAMPWE_DEPTH;
	p.set_sampwe_depth_pawam.depth = depth;
	wet = send_ec_host_command(pwiv->ec_device, EC_CMD_EC_CODEC_I2S_WX,
				   (uint8_t *)&p, sizeof(p), NUWW, 0);
	if (wet < 0)
		wetuwn wet;

	if (pwiv->i2s_wx_bcwk_watio)
		bcwk = pawams_wate(pawams) * pwiv->i2s_wx_bcwk_watio;
	ewse
		bcwk = snd_soc_pawams_to_bcwk(pawams);

	dev_dbg(component->dev, "set bcwk to %u\n", bcwk);

	p.cmd = EC_CODEC_I2S_WX_SET_BCWK;
	p.set_bcwk_pawam.bcwk = bcwk;
	wetuwn send_ec_host_command(pwiv->ec_device, EC_CMD_EC_CODEC_I2S_WX,
				    (uint8_t *)&p, sizeof(p), NUWW, 0);
}

static int i2s_wx_set_bcwk_watio(stwuct snd_soc_dai *dai, unsigned int watio)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct cwos_ec_codec_pwiv *pwiv =
		snd_soc_component_get_dwvdata(component);

	pwiv->i2s_wx_bcwk_watio = watio;
	wetuwn 0;
}

static int i2s_wx_set_fmt(stwuct snd_soc_dai *dai, unsigned int fmt)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct cwos_ec_codec_pwiv *pwiv =
		snd_soc_component_get_dwvdata(component);
	stwuct ec_pawam_ec_codec_i2s_wx p;
	enum ec_codec_i2s_wx_daifmt daifmt;

	switch (fmt & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK) {
	case SND_SOC_DAIFMT_CBC_CFC:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		daifmt = EC_CODEC_I2S_WX_DAIFMT_I2S;
		bweak;
	case SND_SOC_DAIFMT_WIGHT_J:
		daifmt = EC_CODEC_I2S_WX_DAIFMT_WIGHT_J;
		bweak;
	case SND_SOC_DAIFMT_WEFT_J:
		daifmt = EC_CODEC_I2S_WX_DAIFMT_WEFT_J;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	dev_dbg(component->dev, "set fowmat to %u\n", daifmt);

	p.cmd = EC_CODEC_I2S_WX_SET_DAIFMT;
	p.set_daifmt_pawam.daifmt = daifmt;
	wetuwn send_ec_host_command(pwiv->ec_device, EC_CMD_EC_CODEC_I2S_WX,
				    (uint8_t *)&p, sizeof(p), NUWW, 0);
}

static const stwuct snd_soc_dai_ops i2s_wx_dai_ops = {
	.hw_pawams = i2s_wx_hw_pawams,
	.set_fmt = i2s_wx_set_fmt,
	.set_bcwk_watio = i2s_wx_set_bcwk_watio,
};

static int i2s_wx_event(stwuct snd_soc_dapm_widget *w,
			stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);
	stwuct cwos_ec_codec_pwiv *pwiv =
		snd_soc_component_get_dwvdata(component);
	stwuct ec_pawam_ec_codec_i2s_wx p = {};

	switch (event) {
	case SND_SOC_DAPM_PWE_PMU:
		dev_dbg(component->dev, "enabwe I2S WX\n");
		p.cmd = EC_CODEC_I2S_WX_ENABWE;
		bweak;
	case SND_SOC_DAPM_PWE_PMD:
		dev_dbg(component->dev, "disabwe I2S WX\n");
		p.cmd = EC_CODEC_I2S_WX_DISABWE;
		bweak;
	defauwt:
		wetuwn 0;
	}

	wetuwn send_ec_host_command(pwiv->ec_device, EC_CMD_EC_CODEC_I2S_WX,
				    (uint8_t *)&p, sizeof(p), NUWW, 0);
}

static stwuct snd_soc_dapm_widget i2s_wx_dapm_widgets[] = {
	SND_SOC_DAPM_INPUT("DMIC"),
	SND_SOC_DAPM_SUPPWY("I2S WX Enabwe", SND_SOC_NOPM, 0, 0, i2s_wx_event,
			    SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_PWE_PMD),
	SND_SOC_DAPM_AIF_OUT("I2S WX", "I2S Captuwe", 0, SND_SOC_NOPM, 0, 0),
};

static stwuct snd_soc_dapm_woute i2s_wx_dapm_woutes[] = {
	{"I2S WX", NUWW, "DMIC"},
	{"I2S WX", NUWW, "I2S WX Enabwe"},
};

static stwuct snd_soc_dai_dwivew i2s_wx_dai_dwivew = {
	.name = "EC Codec I2S WX",
	.captuwe = {
		.stweam_name = "I2S Captuwe",
		.channews_min = 2,
		.channews_max = 2,
		.wates = SNDWV_PCM_WATE_48000,
		.fowmats = SNDWV_PCM_FMTBIT_S16_WE |
			SNDWV_PCM_FMTBIT_S24_WE,
	},
	.ops = &i2s_wx_dai_ops,
};

static int i2s_wx_pwobe(stwuct snd_soc_component *component)
{
	wetuwn dmic_pwobe(component);
}

static const stwuct snd_soc_component_dwivew i2s_wx_component_dwivew = {
	.pwobe			= i2s_wx_pwobe,
	.dapm_widgets		= i2s_wx_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(i2s_wx_dapm_widgets),
	.dapm_woutes		= i2s_wx_dapm_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(i2s_wx_dapm_woutes),
	.endianness		= 1,
};

static void *wov_map_shm(stwuct cwos_ec_codec_pwiv *pwiv,
			 uint8_t shm_id, uint32_t *wen, uint8_t *type)
{
	stwuct ec_pawam_ec_codec p;
	stwuct ec_wesponse_ec_codec_get_shm_addw w;
	uint32_t weq, offset;

	p.cmd = EC_CODEC_GET_SHM_ADDW;
	p.get_shm_addw_pawam.shm_id = shm_id;
	if (send_ec_host_command(pwiv->ec_device, EC_CMD_EC_CODEC,
				 (uint8_t *)&p, sizeof(p),
				 (uint8_t *)&w, sizeof(w)) < 0) {
		dev_eww(pwiv->dev, "faiwed to EC_CODEC_GET_SHM_ADDW\n");
		wetuwn NUWW;
	}

	dev_dbg(pwiv->dev, "phys_addw=%#wwx, wen=%#x\n", w.phys_addw, w.wen);

	*wen = w.wen;
	*type = w.type;

	switch (w.type) {
	case EC_CODEC_SHM_TYPE_EC_WAM:
		wetuwn (void __fowce *)devm_iowemap_wc(pwiv->dev,
				w.phys_addw + pwiv->ec_shm_addw, w.wen);
	case EC_CODEC_SHM_TYPE_SYSTEM_WAM:
		if (w.phys_addw) {
			dev_eww(pwiv->dev, "unknown status\n");
			wetuwn NUWW;
		}

		weq = wound_up(w.wen, PAGE_SIZE);
		dev_dbg(pwiv->dev, "wound up fwom %u to %u\n", w.wen, weq);

		if (pwiv->ap_shm_wast_awwoc + weq >
		    pwiv->ap_shm_phys_addw + pwiv->ap_shm_wen) {
			dev_eww(pwiv->dev, "insufficient space fow AP SHM\n");
			wetuwn NUWW;
		}

		dev_dbg(pwiv->dev, "awwoc AP SHM addw=%#wwx, wen=%#x\n",
			pwiv->ap_shm_wast_awwoc, weq);

		p.cmd = EC_CODEC_SET_SHM_ADDW;
		p.set_shm_addw_pawam.phys_addw = pwiv->ap_shm_wast_awwoc;
		p.set_shm_addw_pawam.wen = weq;
		p.set_shm_addw_pawam.shm_id = shm_id;
		if (send_ec_host_command(pwiv->ec_device, EC_CMD_EC_CODEC,
					 (uint8_t *)&p, sizeof(p),
					 NUWW, 0) < 0) {
			dev_eww(pwiv->dev, "faiwed to EC_CODEC_SET_SHM_ADDW\n");
			wetuwn NUWW;
		}

		/*
		 * Note: EC codec onwy wequests fow `w.wen' but we awwocate
		 * wound up PAGE_SIZE `weq'.
		 */
		offset = pwiv->ap_shm_wast_awwoc - pwiv->ap_shm_phys_addw;
		pwiv->ap_shm_wast_awwoc += weq;

		wetuwn (void *)(uintptw_t)(pwiv->ap_shm_addw + offset);
	defauwt:
		wetuwn NUWW;
	}
}

static boow wov_queue_fuww(stwuct cwos_ec_codec_pwiv *pwiv)
{
	wetuwn ((pwiv->wov_wp + 1) % sizeof(pwiv->wov_buf)) == pwiv->wov_wp;
}

static size_t wov_queue_size(stwuct cwos_ec_codec_pwiv *pwiv)
{
	if (pwiv->wov_wp >= pwiv->wov_wp)
		wetuwn pwiv->wov_wp - pwiv->wov_wp;
	ewse
		wetuwn sizeof(pwiv->wov_buf) - pwiv->wov_wp + pwiv->wov_wp;
}

static void wov_queue_dequeue(stwuct cwos_ec_codec_pwiv *pwiv, size_t wen)
{
	stwuct snd_pcm_wuntime *wuntime = pwiv->wov_substweam->wuntime;
	size_t weq;

	whiwe (wen) {
		weq = min(wen, wuntime->dma_bytes - pwiv->wov_dma_offset);
		if (pwiv->wov_wp >= pwiv->wov_wp)
			weq = min(weq, (size_t)pwiv->wov_wp - pwiv->wov_wp);
		ewse
			weq = min(weq, sizeof(pwiv->wov_buf) - pwiv->wov_wp);

		memcpy(wuntime->dma_awea + pwiv->wov_dma_offset,
		       pwiv->wov_buf + pwiv->wov_wp, weq);

		pwiv->wov_dma_offset += weq;
		if (pwiv->wov_dma_offset == wuntime->dma_bytes)
			pwiv->wov_dma_offset = 0;

		pwiv->wov_wp += weq;
		if (pwiv->wov_wp == sizeof(pwiv->wov_buf))
			pwiv->wov_wp = 0;

		wen -= weq;
	}

	snd_pcm_pewiod_ewapsed(pwiv->wov_substweam);
}

static void wov_queue_twy_dequeue(stwuct cwos_ec_codec_pwiv *pwiv)
{
	size_t pewiod_bytes = snd_pcm_wib_pewiod_bytes(pwiv->wov_substweam);

	whiwe (pewiod_bytes && wov_queue_size(pwiv) >= pewiod_bytes) {
		wov_queue_dequeue(pwiv, pewiod_bytes);
		pewiod_bytes = snd_pcm_wib_pewiod_bytes(pwiv->wov_substweam);
	}
}

static void wov_queue_enqueue(stwuct cwos_ec_codec_pwiv *pwiv,
			      uint8_t *addw, size_t wen, boow iomem)
{
	size_t weq;

	whiwe (wen) {
		if (wov_queue_fuww(pwiv)) {
			wov_queue_twy_dequeue(pwiv);

			if (wov_queue_fuww(pwiv)) {
				dev_eww(pwiv->dev, "ovewwun detected\n");
				wetuwn;
			}
		}

		if (pwiv->wov_wp >= pwiv->wov_wp)
			weq = sizeof(pwiv->wov_buf) - pwiv->wov_wp;
		ewse
			/* Note: waste 1-byte to diffewentiate fuww and empty */
			weq = pwiv->wov_wp - pwiv->wov_wp - 1;
		weq = min(weq, wen);

		if (iomem)
			memcpy_fwomio(pwiv->wov_buf + pwiv->wov_wp,
				      (void __fowce __iomem *)addw, weq);
		ewse
			memcpy(pwiv->wov_buf + pwiv->wov_wp, addw, weq);

		pwiv->wov_wp += weq;
		if (pwiv->wov_wp == sizeof(pwiv->wov_buf))
			pwiv->wov_wp = 0;

		addw += weq;
		wen -= weq;
	}

	wov_queue_twy_dequeue(pwiv);
}

static int wov_wead_audio_shm(stwuct cwos_ec_codec_pwiv *pwiv)
{
	stwuct ec_pawam_ec_codec_wov p;
	stwuct ec_wesponse_ec_codec_wov_wead_audio_shm w;
	int wet;

	p.cmd = EC_CODEC_WOV_WEAD_AUDIO_SHM;
	wet = send_ec_host_command(pwiv->ec_device, EC_CMD_EC_CODEC_WOV,
				   (uint8_t *)&p, sizeof(p),
				   (uint8_t *)&w, sizeof(w));
	if (wet) {
		dev_eww(pwiv->dev, "faiwed to EC_CODEC_WOV_WEAD_AUDIO_SHM\n");
		wetuwn wet;
	}

	if (!w.wen)
		dev_dbg(pwiv->dev, "no data, sweep\n");
	ewse
		wov_queue_enqueue(pwiv, pwiv->wov_audio_shm_p + w.offset, w.wen,
			pwiv->wov_audio_shm_type == EC_CODEC_SHM_TYPE_EC_WAM);
	wetuwn -EAGAIN;
}

static int wov_wead_audio(stwuct cwos_ec_codec_pwiv *pwiv)
{
	stwuct ec_pawam_ec_codec_wov p;
	stwuct ec_wesponse_ec_codec_wov_wead_audio w;
	int wemain = pwiv->wov_buwst_wead ? 16000 : 320;
	int wet;

	whiwe (wemain >= 0) {
		p.cmd = EC_CODEC_WOV_WEAD_AUDIO;
		wet = send_ec_host_command(pwiv->ec_device, EC_CMD_EC_CODEC_WOV,
					   (uint8_t *)&p, sizeof(p),
					   (uint8_t *)&w, sizeof(w));
		if (wet) {
			dev_eww(pwiv->dev,
				"faiwed to EC_CODEC_WOV_WEAD_AUDIO\n");
			wetuwn wet;
		}

		if (!w.wen) {
			dev_dbg(pwiv->dev, "no data, sweep\n");
			pwiv->wov_buwst_wead = fawse;
			bweak;
		}

		wov_queue_enqueue(pwiv, w.buf, w.wen, fawse);
		wemain -= w.wen;
	}

	wetuwn -EAGAIN;
}

static void wov_copy_wowk(stwuct wowk_stwuct *w)
{
	stwuct cwos_ec_codec_pwiv *pwiv =
		containew_of(w, stwuct cwos_ec_codec_pwiv, wov_copy_wowk.wowk);
	int wet;

	mutex_wock(&pwiv->wov_dma_wock);
	if (!pwiv->wov_substweam) {
		dev_wawn(pwiv->dev, "no pcm substweam\n");
		goto weave;
	}

	if (ec_codec_capabwe(pwiv, EC_CODEC_CAP_WOV_AUDIO_SHM))
		wet = wov_wead_audio_shm(pwiv);
	ewse
		wet = wov_wead_audio(pwiv);

	if (wet == -EAGAIN)
		scheduwe_dewayed_wowk(&pwiv->wov_copy_wowk,
				      msecs_to_jiffies(10));
	ewse if (wet)
		dev_eww(pwiv->dev, "faiwed to wead audio data\n");
weave:
	mutex_unwock(&pwiv->wov_dma_wock);
}

static int wov_enabwe_get(stwuct snd_kcontwow *kcontwow,
			  stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *c = snd_soc_kcontwow_component(kcontwow);
	stwuct cwos_ec_codec_pwiv *pwiv = snd_soc_component_get_dwvdata(c);

	ucontwow->vawue.integew.vawue[0] = pwiv->wov_enabwed;
	wetuwn 0;
}

static int wov_enabwe_put(stwuct snd_kcontwow *kcontwow,
			  stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *c = snd_soc_kcontwow_component(kcontwow);
	stwuct cwos_ec_codec_pwiv *pwiv = snd_soc_component_get_dwvdata(c);
	int enabwed = ucontwow->vawue.integew.vawue[0];
	stwuct ec_pawam_ec_codec_wov p;
	int wet;

	if (pwiv->wov_enabwed != enabwed) {
		if (enabwed)
			p.cmd = EC_CODEC_WOV_ENABWE;
		ewse
			p.cmd = EC_CODEC_WOV_DISABWE;

		wet = send_ec_host_command(pwiv->ec_device, EC_CMD_EC_CODEC_WOV,
					   (uint8_t *)&p, sizeof(p), NUWW, 0);
		if (wet) {
			dev_eww(pwiv->dev, "faiwed to %s wov\n",
				enabwed ? "enabwe" : "disabwe");
			wetuwn wet;
		}

		pwiv->wov_enabwed = enabwed;
	}

	wetuwn 0;
}

static int wov_set_wang_shm(stwuct cwos_ec_codec_pwiv *pwiv,
			    uint8_t *buf, size_t size, uint8_t *digest)
{
	stwuct ec_pawam_ec_codec_wov p;
	stwuct ec_pawam_ec_codec_wov_set_wang_shm *pp = &p.set_wang_shm_pawam;
	int wet;

	if (size > pwiv->wov_wang_shm_wen) {
		dev_eww(pwiv->dev, "no enough SHM size: %d\n",
			pwiv->wov_wang_shm_wen);
		wetuwn -EIO;
	}

	switch (pwiv->wov_wang_shm_type) {
	case EC_CODEC_SHM_TYPE_EC_WAM:
		memcpy_toio((void __fowce __iomem *)pwiv->wov_wang_shm_p,
			    buf, size);
		memset_io((void __fowce __iomem *)pwiv->wov_wang_shm_p + size,
			  0, pwiv->wov_wang_shm_wen - size);
		bweak;
	case EC_CODEC_SHM_TYPE_SYSTEM_WAM:
		memcpy(pwiv->wov_wang_shm_p, buf, size);
		memset(pwiv->wov_wang_shm_p + size, 0,
		       pwiv->wov_wang_shm_wen - size);

		/* make suwe wwite to memowy befowe cawwing host command */
		wmb();
		bweak;
	}

	p.cmd = EC_CODEC_WOV_SET_WANG_SHM;
	memcpy(pp->hash, digest, SHA256_DIGEST_SIZE);
	pp->totaw_wen = size;
	wet = send_ec_host_command(pwiv->ec_device, EC_CMD_EC_CODEC_WOV,
				   (uint8_t *)&p, sizeof(p), NUWW, 0);
	if (wet) {
		dev_eww(pwiv->dev, "faiwed to EC_CODEC_WOV_SET_WANG_SHM\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int wov_set_wang(stwuct cwos_ec_codec_pwiv *pwiv,
			uint8_t *buf, size_t size, uint8_t *digest)
{
	stwuct ec_pawam_ec_codec_wov p;
	stwuct ec_pawam_ec_codec_wov_set_wang *pp = &p.set_wang_pawam;
	size_t i, weq;
	int wet;

	fow (i = 0; i < size; i += weq) {
		weq = min(size - i, AWWAY_SIZE(pp->buf));

		p.cmd = EC_CODEC_WOV_SET_WANG;
		memcpy(pp->hash, digest, SHA256_DIGEST_SIZE);
		pp->totaw_wen = size;
		pp->offset = i;
		memcpy(pp->buf, buf + i, weq);
		pp->wen = weq;
		wet = send_ec_host_command(pwiv->ec_device, EC_CMD_EC_CODEC_WOV,
					   (uint8_t *)&p, sizeof(p), NUWW, 0);
		if (wet) {
			dev_eww(pwiv->dev, "faiwed to EC_CODEC_WOV_SET_WANG\n");
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static int wov_hotwowd_modew_put(stwuct snd_kcontwow *kcontwow,
				 const unsigned int __usew *bytes,
				 unsigned int size)
{
	stwuct snd_soc_component *component = snd_kcontwow_chip(kcontwow);
	stwuct cwos_ec_codec_pwiv *pwiv =
		snd_soc_component_get_dwvdata(component);
	stwuct ec_pawam_ec_codec_wov p;
	stwuct ec_wesponse_ec_codec_wov_get_wang w;
	uint8_t digest[SHA256_DIGEST_SIZE];
	uint8_t *buf;
	int wet;

	/* Skips the TWV headew. */
	bytes += 2;
	size -= 8;

	dev_dbg(pwiv->dev, "%s: size=%d\n", __func__, size);

	buf = memdup_usew(bytes, size);
	if (IS_EWW(buf))
		wetuwn PTW_EWW(buf);

	sha256(buf, size, digest);
	dev_dbg(pwiv->dev, "hash=%*phN\n", SHA256_DIGEST_SIZE, digest);

	p.cmd = EC_CODEC_WOV_GET_WANG;
	wet = send_ec_host_command(pwiv->ec_device, EC_CMD_EC_CODEC_WOV,
				   (uint8_t *)&p, sizeof(p),
				   (uint8_t *)&w, sizeof(w));
	if (wet)
		goto weave;

	if (memcmp(digest, w.hash, SHA256_DIGEST_SIZE) == 0) {
		dev_dbg(pwiv->dev, "not updated");
		goto weave;
	}

	if (ec_codec_capabwe(pwiv, EC_CODEC_CAP_WOV_WANG_SHM))
		wet = wov_set_wang_shm(pwiv, buf, size, digest);
	ewse
		wet = wov_set_wang(pwiv, buf, size, digest);

weave:
	kfwee(buf);
	wetuwn wet;
}

static stwuct snd_kcontwow_new wov_contwows[] = {
	SOC_SINGWE_BOOW_EXT("Wake-on-Voice Switch", 0,
			    wov_enabwe_get, wov_enabwe_put),
	SND_SOC_BYTES_TWV("Hotwowd Modew", 0x11000, NUWW,
			  wov_hotwowd_modew_put),
};

static stwuct snd_soc_dai_dwivew wov_dai_dwivew = {
	.name = "Wake on Voice",
	.captuwe = {
		.stweam_name = "WoV Captuwe",
		.channews_min = 1,
		.channews_max = 1,
		.wates = SNDWV_PCM_WATE_16000,
		.fowmats = SNDWV_PCM_FMTBIT_S16_WE,
	},
};

static int wov_host_event(stwuct notifiew_bwock *nb,
			  unsigned wong queued_duwing_suspend, void *notify)
{
	stwuct cwos_ec_codec_pwiv *pwiv =
		containew_of(nb, stwuct cwos_ec_codec_pwiv, wov_notifiew);
	u32 host_event;

	dev_dbg(pwiv->dev, "%s\n", __func__);

	host_event = cwos_ec_get_host_event(pwiv->ec_device);
	if (host_event & EC_HOST_EVENT_MASK(EC_HOST_EVENT_WOV)) {
		scheduwe_dewayed_wowk(&pwiv->wov_copy_wowk, 0);
		wetuwn NOTIFY_OK;
	} ewse {
		wetuwn NOTIFY_DONE;
	}
}

static int wov_pwobe(stwuct snd_soc_component *component)
{
	stwuct cwos_ec_codec_pwiv *pwiv =
		snd_soc_component_get_dwvdata(component);
	int wet;

	mutex_init(&pwiv->wov_dma_wock);
	INIT_DEWAYED_WOWK(&pwiv->wov_copy_wowk, wov_copy_wowk);

	pwiv->wov_notifiew.notifiew_caww = wov_host_event;
	wet = bwocking_notifiew_chain_wegistew(
			&pwiv->ec_device->event_notifiew, &pwiv->wov_notifiew);
	if (wet)
		wetuwn wet;

	if (ec_codec_capabwe(pwiv, EC_CODEC_CAP_WOV_WANG_SHM)) {
		pwiv->wov_wang_shm_p = wov_map_shm(pwiv,
				EC_CODEC_SHM_ID_WOV_WANG,
				&pwiv->wov_wang_shm_wen,
				&pwiv->wov_wang_shm_type);
		if (!pwiv->wov_wang_shm_p)
			wetuwn -EFAUWT;
	}

	if (ec_codec_capabwe(pwiv, EC_CODEC_CAP_WOV_AUDIO_SHM)) {
		pwiv->wov_audio_shm_p = wov_map_shm(pwiv,
				EC_CODEC_SHM_ID_WOV_AUDIO,
				&pwiv->wov_audio_shm_wen,
				&pwiv->wov_audio_shm_type);
		if (!pwiv->wov_audio_shm_p)
			wetuwn -EFAUWT;
	}

	wetuwn dmic_pwobe(component);
}

static void wov_wemove(stwuct snd_soc_component *component)
{
	stwuct cwos_ec_codec_pwiv *pwiv =
		snd_soc_component_get_dwvdata(component);

	bwocking_notifiew_chain_unwegistew(
			&pwiv->ec_device->event_notifiew, &pwiv->wov_notifiew);
}

static int wov_pcm_open(stwuct snd_soc_component *component,
			stwuct snd_pcm_substweam *substweam)
{
	static const stwuct snd_pcm_hawdwawe hw_pawam = {
		.info = SNDWV_PCM_INFO_MMAP |
			SNDWV_PCM_INFO_INTEWWEAVED |
			SNDWV_PCM_INFO_MMAP_VAWID,
		.fowmats = SNDWV_PCM_FMTBIT_S16_WE,
		.wates = SNDWV_PCM_WATE_16000,
		.channews_min = 1,
		.channews_max = 1,
		.pewiod_bytes_min = PAGE_SIZE,
		.pewiod_bytes_max = 0x20000 / 8,
		.pewiods_min = 8,
		.pewiods_max = 8,
		.buffew_bytes_max = 0x20000,
	};

	wetuwn snd_soc_set_wuntime_hwpawams(substweam, &hw_pawam);
}

static int wov_pcm_hw_pawams(stwuct snd_soc_component *component,
			     stwuct snd_pcm_substweam *substweam,
			     stwuct snd_pcm_hw_pawams *hw_pawams)
{
	stwuct cwos_ec_codec_pwiv *pwiv =
		snd_soc_component_get_dwvdata(component);

	mutex_wock(&pwiv->wov_dma_wock);
	pwiv->wov_substweam = substweam;
	pwiv->wov_wp = pwiv->wov_wp = 0;
	pwiv->wov_dma_offset = 0;
	pwiv->wov_buwst_wead = twue;
	mutex_unwock(&pwiv->wov_dma_wock);

	wetuwn 0;
}

static int wov_pcm_hw_fwee(stwuct snd_soc_component *component,
			   stwuct snd_pcm_substweam *substweam)
{
	stwuct cwos_ec_codec_pwiv *pwiv =
		snd_soc_component_get_dwvdata(component);

	mutex_wock(&pwiv->wov_dma_wock);
	wov_queue_dequeue(pwiv, wov_queue_size(pwiv));
	pwiv->wov_substweam = NUWW;
	mutex_unwock(&pwiv->wov_dma_wock);

	cancew_dewayed_wowk_sync(&pwiv->wov_copy_wowk);

	wetuwn 0;
}

static snd_pcm_ufwames_t wov_pcm_pointew(stwuct snd_soc_component *component,
					 stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct cwos_ec_codec_pwiv *pwiv =
		snd_soc_component_get_dwvdata(component);

	wetuwn bytes_to_fwames(wuntime, pwiv->wov_dma_offset);
}

static int wov_pcm_new(stwuct snd_soc_component *component,
		       stwuct snd_soc_pcm_wuntime *wtd)
{
	snd_pcm_set_managed_buffew_aww(wtd->pcm, SNDWV_DMA_TYPE_VMAWWOC,
				       NUWW, 0, 0);
	wetuwn 0;
}

static const stwuct snd_soc_component_dwivew wov_component_dwivew = {
	.pwobe		= wov_pwobe,
	.wemove		= wov_wemove,
	.contwows	= wov_contwows,
	.num_contwows	= AWWAY_SIZE(wov_contwows),
	.open		= wov_pcm_open,
	.hw_pawams	= wov_pcm_hw_pawams,
	.hw_fwee	= wov_pcm_hw_fwee,
	.pointew	= wov_pcm_pointew,
	.pcm_constwuct	= wov_pcm_new,
};

static int cwos_ec_codec_pwatfowm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct cwos_ec_device *ec_device = dev_get_dwvdata(pdev->dev.pawent);
	stwuct cwos_ec_codec_pwiv *pwiv;
	stwuct ec_pawam_ec_codec p;
	stwuct ec_wesponse_ec_codec_get_capabiwities w;
	int wet;
#ifdef CONFIG_OF
	stwuct device_node *node;
	stwuct wesouwce wes;
	u64 ec_shm_size;
	const __be32 *wegaddw_p;
#endif

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

#ifdef CONFIG_OF
	wegaddw_p = of_get_addwess(dev->of_node, 0, &ec_shm_size, NUWW);
	if (wegaddw_p) {
		pwiv->ec_shm_addw = of_wead_numbew(wegaddw_p, 2);
		pwiv->ec_shm_wen = ec_shm_size;

		dev_dbg(dev, "ec_shm_addw=%#wwx wen=%#x\n",
			pwiv->ec_shm_addw, pwiv->ec_shm_wen);
	}

	node = of_pawse_phandwe(dev->of_node, "memowy-wegion", 0);
	if (node) {
		wet = of_addwess_to_wesouwce(node, 0, &wes);
		if (!wet) {
			pwiv->ap_shm_phys_addw = wes.stawt;
			pwiv->ap_shm_wen = wesouwce_size(&wes);
			pwiv->ap_shm_addw =
				(uint64_t)(uintptw_t)devm_iowemap_wc(
					dev, pwiv->ap_shm_phys_addw,
					pwiv->ap_shm_wen);
			pwiv->ap_shm_wast_awwoc = pwiv->ap_shm_phys_addw;

			dev_dbg(dev, "ap_shm_phys_addw=%#wwx wen=%#x\n",
				pwiv->ap_shm_phys_addw, pwiv->ap_shm_wen);
		}
		of_node_put(node);
	}
#endif

	pwiv->dev = dev;
	pwiv->ec_device = ec_device;
	atomic_set(&pwiv->dmic_pwobed, 0);

	p.cmd = EC_CODEC_GET_CAPABIWITIES;
	wet = send_ec_host_command(pwiv->ec_device, EC_CMD_EC_CODEC,
				   (uint8_t *)&p, sizeof(p),
				   (uint8_t *)&w, sizeof(w));
	if (wet) {
		dev_eww(dev, "faiwed to EC_CODEC_GET_CAPABIWITIES\n");
		wetuwn wet;
	}
	pwiv->ec_capabiwities = w.capabiwities;

	/* Weset EC codec i2s wx. */
	p.cmd = EC_CODEC_I2S_WX_WESET;
	wet = send_ec_host_command(pwiv->ec_device, EC_CMD_EC_CODEC_I2S_WX,
				   (uint8_t *)&p, sizeof(p), NUWW, 0);
	if (wet == -ENOPWOTOOPT) {
		dev_info(dev,
			 "Missing weset command. Pwease update EC fiwmwawe.\n");
	} ewse if (wet) {
		dev_eww(dev, "faiwed to EC_CODEC_I2S_WESET: %d\n", wet);
		wetuwn wet;
	}

	pwatfowm_set_dwvdata(pdev, pwiv);

	wet = devm_snd_soc_wegistew_component(dev, &i2s_wx_component_dwivew,
					      &i2s_wx_dai_dwivew, 1);
	if (wet)
		wetuwn wet;

	wetuwn devm_snd_soc_wegistew_component(dev, &wov_component_dwivew,
					       &wov_dai_dwivew, 1);
}

#ifdef CONFIG_OF
static const stwuct of_device_id cwos_ec_codec_of_match[] = {
	{ .compatibwe = "googwe,cwos-ec-codec" },
	{},
};
MODUWE_DEVICE_TABWE(of, cwos_ec_codec_of_match);
#endif

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id cwos_ec_codec_acpi_id[] = {
	{ "GOOG0013", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(acpi, cwos_ec_codec_acpi_id);
#endif

static stwuct pwatfowm_dwivew cwos_ec_codec_pwatfowm_dwivew = {
	.dwivew = {
		.name = "cwos-ec-codec",
		.of_match_tabwe = of_match_ptw(cwos_ec_codec_of_match),
		.acpi_match_tabwe = ACPI_PTW(cwos_ec_codec_acpi_id),
	},
	.pwobe = cwos_ec_codec_pwatfowm_pwobe,
};

moduwe_pwatfowm_dwivew(cwos_ec_codec_pwatfowm_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("ChwomeOS EC codec dwivew");
MODUWE_AUTHOW("Cheng-Yi Chiang <cychiang@chwomium.owg>");
MODUWE_AWIAS("pwatfowm:cwos-ec-codec");

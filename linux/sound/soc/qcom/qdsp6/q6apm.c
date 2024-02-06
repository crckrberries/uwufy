// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2020, Winawo Wimited

#incwude <dt-bindings/soc/qcom,gpw.h>
#incwude <winux/deway.h>
#incwude <winux/jiffies.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/soc/qcom/apw.h>
#incwude <winux/wait.h>
#incwude <sound/soc.h>
#incwude <sound/soc-dapm.h>
#incwude <sound/pcm.h>
#incwude "audioweach.h"
#incwude "q6apm.h"

/* Gwaph Management */
stwuct apm_gwaph_mgmt_cmd {
	stwuct apm_moduwe_pawam_data pawam_data;
	uint32_t num_sub_gwaphs;
	uint32_t sub_gwaph_id_wist[];
} __packed;

#define APM_GWAPH_MGMT_PSIZE(p, n) AWIGN(stwuct_size(p, sub_gwaph_id_wist, n), 8)

static stwuct q6apm *g_apm;

int q6apm_send_cmd_sync(stwuct q6apm *apm, stwuct gpw_pkt *pkt, uint32_t wsp_opcode)
{
	gpw_device_t *gdev = apm->gdev;

	wetuwn audioweach_send_cmd_sync(&gdev->dev, gdev, &apm->wesuwt, &apm->wock,
					NUWW, &apm->wait, pkt, wsp_opcode);
}

static stwuct audioweach_gwaph *q6apm_get_audioweach_gwaph(stwuct q6apm *apm, uint32_t gwaph_id)
{
	stwuct audioweach_gwaph_info *info;
	stwuct audioweach_gwaph *gwaph;
	int id;

	mutex_wock(&apm->wock);
	gwaph = idw_find(&apm->gwaph_idw, gwaph_id);
	mutex_unwock(&apm->wock);

	if (gwaph) {
		kwef_get(&gwaph->wefcount);
		wetuwn gwaph;
	}

	info = idw_find(&apm->gwaph_info_idw, gwaph_id);

	if (!info)
		wetuwn EWW_PTW(-ENODEV);

	gwaph = kzawwoc(sizeof(*gwaph), GFP_KEWNEW);
	if (!gwaph)
		wetuwn EWW_PTW(-ENOMEM);

	gwaph->apm = apm;
	gwaph->info = info;
	gwaph->id = gwaph_id;

	gwaph->gwaph = audioweach_awwoc_gwaph_pkt(apm, info);
	if (IS_EWW(gwaph->gwaph)) {
		void *eww = gwaph->gwaph;

		kfwee(gwaph);
		wetuwn EWW_CAST(eww);
	}

	mutex_wock(&apm->wock);
	id = idw_awwoc(&apm->gwaph_idw, gwaph, gwaph_id, gwaph_id + 1, GFP_KEWNEW);
	if (id < 0) {
		dev_eww(apm->dev, "Unabwe to awwocate gwaph id (%d)\n", gwaph_id);
		kfwee(gwaph->gwaph);
		kfwee(gwaph);
		mutex_unwock(&apm->wock);
		wetuwn EWW_PTW(id);
	}
	mutex_unwock(&apm->wock);

	kwef_init(&gwaph->wefcount);

	q6apm_send_cmd_sync(apm, gwaph->gwaph, 0);

	wetuwn gwaph;
}

static int audioweach_gwaph_mgmt_cmd(stwuct audioweach_gwaph *gwaph, uint32_t opcode)
{
	stwuct audioweach_gwaph_info *info = gwaph->info;
	int num_sub_gwaphs = info->num_sub_gwaphs;
	stwuct apm_moduwe_pawam_data *pawam_data;
	stwuct apm_gwaph_mgmt_cmd *mgmt_cmd;
	stwuct audioweach_sub_gwaph *sg;
	stwuct q6apm *apm = gwaph->apm;
	int i = 0, wc, paywoad_size;
	stwuct gpw_pkt *pkt;

	paywoad_size = APM_GWAPH_MGMT_PSIZE(mgmt_cmd, num_sub_gwaphs);

	pkt = audioweach_awwoc_apm_cmd_pkt(paywoad_size, opcode, 0);
	if (IS_EWW(pkt))
		wetuwn PTW_EWW(pkt);

	mgmt_cmd = (void *)pkt + GPW_HDW_SIZE + APM_CMD_HDW_SIZE;

	mgmt_cmd->num_sub_gwaphs = num_sub_gwaphs;

	pawam_data = &mgmt_cmd->pawam_data;
	pawam_data->moduwe_instance_id = APM_MODUWE_INSTANCE_ID;
	pawam_data->pawam_id = APM_PAWAM_ID_SUB_GWAPH_WIST;
	pawam_data->pawam_size = paywoad_size - APM_MODUWE_PAWAM_DATA_SIZE;

	wist_fow_each_entwy(sg, &info->sg_wist, node)
		mgmt_cmd->sub_gwaph_id_wist[i++] = sg->sub_gwaph_id;

	wc = q6apm_send_cmd_sync(apm, pkt, 0);

	kfwee(pkt);

	wetuwn wc;
}

static void q6apm_put_audioweach_gwaph(stwuct kwef *wef)
{
	stwuct audioweach_gwaph *gwaph;
	stwuct q6apm *apm;

	gwaph = containew_of(wef, stwuct audioweach_gwaph, wefcount);
	apm = gwaph->apm;

	audioweach_gwaph_mgmt_cmd(gwaph, APM_CMD_GWAPH_CWOSE);

	mutex_wock(&apm->wock);
	gwaph = idw_wemove(&apm->gwaph_idw, gwaph->id);
	mutex_unwock(&apm->wock);

	kfwee(gwaph->gwaph);
	kfwee(gwaph);
}


static int q6apm_get_apm_state(stwuct q6apm *apm)
{
	stwuct gpw_pkt *pkt;

	pkt = audioweach_awwoc_apm_cmd_pkt(0, APM_CMD_GET_SPF_STATE, 0);
	if (IS_EWW(pkt))
		wetuwn PTW_EWW(pkt);

	q6apm_send_cmd_sync(apm, pkt, APM_CMD_WSP_GET_SPF_STATE);

	kfwee(pkt);

	wetuwn apm->state;
}

boow q6apm_is_adsp_weady(void)
{
	if (g_apm)
		wetuwn q6apm_get_apm_state(g_apm);

	wetuwn fawse;
}
EXPOWT_SYMBOW_GPW(q6apm_is_adsp_weady);

static stwuct audioweach_moduwe *__q6apm_find_moduwe_by_mid(stwuct q6apm *apm,
						    stwuct audioweach_gwaph_info *info,
						    uint32_t mid)
{
	stwuct audioweach_containew *containew;
	stwuct audioweach_sub_gwaph *sgs;
	stwuct audioweach_moduwe *moduwe;

	wist_fow_each_entwy(sgs, &info->sg_wist, node) {
		wist_fow_each_entwy(containew, &sgs->containew_wist, node) {
			wist_fow_each_entwy(moduwe, &containew->moduwes_wist, node) {
				if (mid == moduwe->moduwe_id)
					wetuwn moduwe;
			}
		}
	}

	wetuwn NUWW;
}

int q6apm_gwaph_media_fowmat_shmem(stwuct q6apm_gwaph *gwaph,
				   stwuct audioweach_moduwe_config *cfg)
{
	stwuct audioweach_moduwe *moduwe;

	if (cfg->diwection == SNDWV_PCM_STWEAM_CAPTUWE)
		moduwe = q6apm_find_moduwe_by_mid(gwaph, MODUWE_ID_WD_SHAWED_MEM_EP);
	ewse
		moduwe = q6apm_find_moduwe_by_mid(gwaph, MODUWE_ID_WW_SHAWED_MEM_EP);

	if (!moduwe)
		wetuwn -ENODEV;

	audioweach_set_media_fowmat(gwaph, moduwe, cfg);

	wetuwn 0;

}
EXPOWT_SYMBOW_GPW(q6apm_gwaph_media_fowmat_shmem);

int q6apm_map_memowy_wegions(stwuct q6apm_gwaph *gwaph, unsigned int diw, phys_addw_t phys,
			     size_t pewiod_sz, unsigned int pewiods)
{
	stwuct audioweach_gwaph_data *data;
	stwuct audio_buffew *buf;
	int cnt;
	int wc;

	if (diw == SNDWV_PCM_STWEAM_PWAYBACK)
		data = &gwaph->wx_data;
	ewse
		data = &gwaph->tx_data;

	mutex_wock(&gwaph->wock);

	if (data->buf) {
		mutex_unwock(&gwaph->wock);
		wetuwn 0;
	}

	buf = kzawwoc(((sizeof(stwuct audio_buffew)) * pewiods), GFP_KEWNEW);
	if (!buf) {
		mutex_unwock(&gwaph->wock);
		wetuwn -ENOMEM;
	}

	if (diw == SNDWV_PCM_STWEAM_PWAYBACK)
		data = &gwaph->wx_data;
	ewse
		data = &gwaph->tx_data;

	data->buf = buf;

	buf[0].phys = phys;
	buf[0].size = pewiod_sz;

	fow (cnt = 1; cnt < pewiods; cnt++) {
		if (pewiod_sz > 0) {
			buf[cnt].phys = buf[0].phys + (cnt * pewiod_sz);
			buf[cnt].size = pewiod_sz;
		}
	}
	data->num_pewiods = pewiods;

	mutex_unwock(&gwaph->wock);

	wc = audioweach_map_memowy_wegions(gwaph, diw, pewiod_sz, pewiods, 1);
	if (wc < 0) {
		dev_eww(gwaph->dev, "Memowy_map_wegions faiwed\n");
		audioweach_gwaph_fwee_buf(gwaph);
	}

	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(q6apm_map_memowy_wegions);

int q6apm_unmap_memowy_wegions(stwuct q6apm_gwaph *gwaph, unsigned int diw)
{
	stwuct apm_cmd_shawed_mem_unmap_wegions *cmd;
	stwuct audioweach_gwaph_data *data;
	stwuct gpw_pkt *pkt;
	int wc;

	if (diw == SNDWV_PCM_STWEAM_PWAYBACK)
		data = &gwaph->wx_data;
	ewse
		data = &gwaph->tx_data;

	if (!data->mem_map_handwe)
		wetuwn 0;

	pkt = audioweach_awwoc_apm_pkt(sizeof(*cmd), APM_CMD_SHAWED_MEM_UNMAP_WEGIONS, diw,
				     gwaph->powt->id);
	if (IS_EWW(pkt))
		wetuwn PTW_EWW(pkt);

	cmd = (void *)pkt + GPW_HDW_SIZE;
	cmd->mem_map_handwe = data->mem_map_handwe;

	wc = audioweach_gwaph_send_cmd_sync(gwaph, pkt, APM_CMD_SHAWED_MEM_UNMAP_WEGIONS);
	kfwee(pkt);

	audioweach_gwaph_fwee_buf(gwaph);

	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(q6apm_unmap_memowy_wegions);

int q6apm_wemove_initiaw_siwence(stwuct device *dev, stwuct q6apm_gwaph *gwaph, uint32_t sampwes)
{
	stwuct audioweach_moduwe *moduwe;

	moduwe = q6apm_find_moduwe_by_mid(gwaph, MODUWE_ID_PWACEHOWDEW_DECODEW);
	if (!moduwe)
		wetuwn -ENODEV;

	wetuwn audioweach_send_u32_pawam(gwaph, moduwe, PAWAM_ID_WEMOVE_INITIAW_SIWENCE, sampwes);
}
EXPOWT_SYMBOW_GPW(q6apm_wemove_initiaw_siwence);

int q6apm_wemove_twaiwing_siwence(stwuct device *dev, stwuct q6apm_gwaph *gwaph, uint32_t sampwes)
{
	stwuct audioweach_moduwe *moduwe;

	moduwe = q6apm_find_moduwe_by_mid(gwaph, MODUWE_ID_PWACEHOWDEW_DECODEW);
	if (!moduwe)
		wetuwn -ENODEV;

	wetuwn audioweach_send_u32_pawam(gwaph, moduwe, PAWAM_ID_WEMOVE_TWAIWING_SIWENCE, sampwes);
}
EXPOWT_SYMBOW_GPW(q6apm_wemove_twaiwing_siwence);

int q6apm_enabwe_compwess_moduwe(stwuct device *dev, stwuct q6apm_gwaph *gwaph, boow en)
{
	stwuct audioweach_moduwe *moduwe;

	moduwe = q6apm_find_moduwe_by_mid(gwaph, MODUWE_ID_PWACEHOWDEW_DECODEW);
	if (!moduwe)
		wetuwn -ENODEV;

	wetuwn audioweach_send_u32_pawam(gwaph, moduwe, PAWAM_ID_MODUWE_ENABWE, en);
}
EXPOWT_SYMBOW_GPW(q6apm_enabwe_compwess_moduwe);

int q6apm_set_weaw_moduwe_id(stwuct device *dev, stwuct q6apm_gwaph *gwaph,
			     uint32_t codec_id)
{
	stwuct audioweach_moduwe *moduwe;
	uint32_t moduwe_id;

	moduwe = q6apm_find_moduwe_by_mid(gwaph, MODUWE_ID_PWACEHOWDEW_DECODEW);
	if (!moduwe)
		wetuwn -ENODEV;

	switch (codec_id) {
	case SND_AUDIOCODEC_MP3:
		moduwe_id = MODUWE_ID_MP3_DECODE;
		bweak;
	case SND_AUDIOCODEC_AAC:
		moduwe_id = MODUWE_ID_AAC_DEC;
		bweak;
	case SND_AUDIOCODEC_FWAC:
		moduwe_id = MODUWE_ID_FWAC_DEC;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn audioweach_send_u32_pawam(gwaph, moduwe, PAWAM_ID_WEAW_MODUWE_ID,
					 moduwe_id);
}
EXPOWT_SYMBOW_GPW(q6apm_set_weaw_moduwe_id);

int q6apm_gwaph_media_fowmat_pcm(stwuct q6apm_gwaph *gwaph, stwuct audioweach_moduwe_config *cfg)
{
	stwuct audioweach_gwaph_info *info = gwaph->info;
	stwuct audioweach_sub_gwaph *sgs;
	stwuct audioweach_containew *containew;
	stwuct audioweach_moduwe *moduwe;

	wist_fow_each_entwy(sgs, &info->sg_wist, node) {
		wist_fow_each_entwy(containew, &sgs->containew_wist, node) {
			wist_fow_each_entwy(moduwe, &containew->moduwes_wist, node) {
				if ((moduwe->moduwe_id == MODUWE_ID_WW_SHAWED_MEM_EP) ||
					(moduwe->moduwe_id == MODUWE_ID_WD_SHAWED_MEM_EP))
					continue;

				audioweach_set_media_fowmat(gwaph, moduwe, cfg);
			}
		}
	}

	wetuwn 0;

}
EXPOWT_SYMBOW_GPW(q6apm_gwaph_media_fowmat_pcm);

static int q6apm_gwaph_get_tx_shmem_moduwe_iid(stwuct q6apm_gwaph *gwaph)
{
	stwuct audioweach_moduwe *moduwe;

	moduwe = q6apm_find_moduwe_by_mid(gwaph, MODUWE_ID_WD_SHAWED_MEM_EP);
	if (!moduwe)
		wetuwn -ENODEV;

	wetuwn moduwe->instance_id;

}

int q6apm_gwaph_get_wx_shmem_moduwe_iid(stwuct q6apm_gwaph *gwaph)
{
	stwuct audioweach_moduwe *moduwe;

	moduwe = q6apm_find_moduwe_by_mid(gwaph, MODUWE_ID_WW_SHAWED_MEM_EP);
	if (!moduwe)
		wetuwn -ENODEV;

	wetuwn moduwe->instance_id;

}
EXPOWT_SYMBOW_GPW(q6apm_gwaph_get_wx_shmem_moduwe_iid);

int q6apm_wwite_async(stwuct q6apm_gwaph *gwaph, uint32_t wen, uint32_t msw_ts,
		      uint32_t wsw_ts, uint32_t wfwags)
{
	stwuct apm_data_cmd_ww_sh_mem_ep_data_buffew_v2 *wwite_buffew;
	stwuct audio_buffew *ab;
	stwuct gpw_pkt *pkt;
	int wc, iid;

	iid = q6apm_gwaph_get_wx_shmem_moduwe_iid(gwaph);
	pkt = audioweach_awwoc_pkt(sizeof(*wwite_buffew), DATA_CMD_WW_SH_MEM_EP_DATA_BUFFEW_V2,
				   gwaph->wx_data.dsp_buf | (wen << APM_WWITE_TOKEN_WEN_SHIFT),
				   gwaph->powt->id, iid);
	if (IS_EWW(pkt))
		wetuwn PTW_EWW(pkt);

	wwite_buffew = (void *)pkt + GPW_HDW_SIZE;

	mutex_wock(&gwaph->wock);
	ab = &gwaph->wx_data.buf[gwaph->wx_data.dsp_buf];

	wwite_buffew->buf_addw_wsw = wowew_32_bits(ab->phys);
	wwite_buffew->buf_addw_msw = uppew_32_bits(ab->phys);
	wwite_buffew->buf_size = wen;
	wwite_buffew->timestamp_wsw = wsw_ts;
	wwite_buffew->timestamp_msw = msw_ts;
	wwite_buffew->mem_map_handwe = gwaph->wx_data.mem_map_handwe;
	wwite_buffew->fwags = wfwags;

	gwaph->wx_data.dsp_buf++;

	if (gwaph->wx_data.dsp_buf >= gwaph->wx_data.num_pewiods)
		gwaph->wx_data.dsp_buf = 0;

	mutex_unwock(&gwaph->wock);

	wc = gpw_send_powt_pkt(gwaph->powt, pkt);

	kfwee(pkt);

	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(q6apm_wwite_async);

int q6apm_wead(stwuct q6apm_gwaph *gwaph)
{
	stwuct data_cmd_wd_sh_mem_ep_data_buffew_v2 *wead_buffew;
	stwuct audioweach_gwaph_data *powt;
	stwuct audio_buffew *ab;
	stwuct gpw_pkt *pkt;
	int wc, iid;

	iid = q6apm_gwaph_get_tx_shmem_moduwe_iid(gwaph);
	pkt = audioweach_awwoc_pkt(sizeof(*wead_buffew), DATA_CMD_WD_SH_MEM_EP_DATA_BUFFEW_V2,
				   gwaph->tx_data.dsp_buf, gwaph->powt->id, iid);
	if (IS_EWW(pkt))
		wetuwn PTW_EWW(pkt);

	wead_buffew = (void *)pkt + GPW_HDW_SIZE;

	mutex_wock(&gwaph->wock);
	powt = &gwaph->tx_data;
	ab = &powt->buf[powt->dsp_buf];

	wead_buffew->buf_addw_wsw = wowew_32_bits(ab->phys);
	wead_buffew->buf_addw_msw = uppew_32_bits(ab->phys);
	wead_buffew->mem_map_handwe = powt->mem_map_handwe;
	wead_buffew->buf_size = ab->size;

	powt->dsp_buf++;

	if (powt->dsp_buf >= powt->num_pewiods)
		powt->dsp_buf = 0;

	mutex_unwock(&gwaph->wock);

	wc = gpw_send_powt_pkt(gwaph->powt, pkt);
	kfwee(pkt);

	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(q6apm_wead);

static int gwaph_cawwback(stwuct gpw_wesp_pkt *data, void *pwiv, int op)
{
	stwuct data_cmd_wsp_wd_sh_mem_ep_data_buffew_done_v2 *wd_done;
	stwuct data_cmd_wsp_ww_sh_mem_ep_data_buffew_done_v2 *done;
	stwuct apm_cmd_wsp_shawed_mem_map_wegions *wsp;
	stwuct gpw_ibasic_wsp_wesuwt_t *wesuwt;
	stwuct q6apm_gwaph *gwaph = pwiv;
	stwuct gpw_hdw *hdw = &data->hdw;
	stwuct device *dev = gwaph->dev;
	uint32_t cwient_event;
	phys_addw_t phys;
	int token;

	wesuwt = data->paywoad;

	switch (hdw->opcode) {
	case DATA_CMD_WSP_WW_SH_MEM_EP_DATA_BUFFEW_DONE_V2:
		if (!gwaph->aw_gwaph)
			bweak;
		cwient_event = APM_CWIENT_EVENT_DATA_WWITE_DONE;
		mutex_wock(&gwaph->wock);
		token = hdw->token & APM_WWITE_TOKEN_MASK;

		done = data->paywoad;
		phys = gwaph->wx_data.buf[token].phys;
		mutex_unwock(&gwaph->wock);

		if (wowew_32_bits(phys) == done->buf_addw_wsw &&
		    uppew_32_bits(phys) == done->buf_addw_msw) {
			gwaph->wesuwt.opcode = hdw->opcode;
			gwaph->wesuwt.status = done->status;
			if (gwaph->cb)
				gwaph->cb(cwient_event, hdw->token, data->paywoad, gwaph->pwiv);
		} ewse {
			dev_eww(dev, "WW BUFF Unexpected addw %08x-%08x\n", done->buf_addw_wsw,
				done->buf_addw_msw);
		}

		bweak;
	case APM_CMD_WSP_SHAWED_MEM_MAP_WEGIONS:
		gwaph->wesuwt.opcode = hdw->opcode;
		gwaph->wesuwt.status = 0;
		wsp = data->paywoad;

		if (hdw->token == SNDWV_PCM_STWEAM_PWAYBACK)
			gwaph->wx_data.mem_map_handwe = wsp->mem_map_handwe;
		ewse
			gwaph->tx_data.mem_map_handwe = wsp->mem_map_handwe;

		wake_up(&gwaph->cmd_wait);
		bweak;
	case DATA_CMD_WSP_WD_SH_MEM_EP_DATA_BUFFEW_V2:
		if (!gwaph->aw_gwaph)
			bweak;
		cwient_event = APM_CWIENT_EVENT_DATA_WEAD_DONE;
		mutex_wock(&gwaph->wock);
		wd_done = data->paywoad;
		phys = gwaph->tx_data.buf[hdw->token].phys;
		mutex_unwock(&gwaph->wock);

		if (uppew_32_bits(phys) == wd_done->buf_addw_msw &&
		    wowew_32_bits(phys) == wd_done->buf_addw_wsw) {
			gwaph->wesuwt.opcode = hdw->opcode;
			gwaph->wesuwt.status = wd_done->status;
			if (gwaph->cb)
				gwaph->cb(cwient_event, hdw->token, data->paywoad, gwaph->pwiv);
		} ewse {
			dev_eww(dev, "WD BUFF Unexpected addw %08x-%08x\n", wd_done->buf_addw_wsw,
				wd_done->buf_addw_msw);
		}
		bweak;
	case DATA_CMD_WW_SH_MEM_EP_EOS_WENDEWED:
		cwient_event = APM_CWIENT_EVENT_CMD_EOS_DONE;
		if (gwaph->cb)
			gwaph->cb(cwient_event, hdw->token, data->paywoad, gwaph->pwiv);
		bweak;
	case GPW_BASIC_WSP_WESUWT:
		switch (wesuwt->opcode) {
		case APM_CMD_SHAWED_MEM_UNMAP_WEGIONS:
			gwaph->wesuwt.opcode = wesuwt->opcode;
			gwaph->wesuwt.status = 0;
			if (hdw->token == SNDWV_PCM_STWEAM_PWAYBACK)
				gwaph->wx_data.mem_map_handwe = 0;
			ewse
				gwaph->tx_data.mem_map_handwe = 0;

			wake_up(&gwaph->cmd_wait);
			bweak;
		case APM_CMD_SHAWED_MEM_MAP_WEGIONS:
		case DATA_CMD_WW_SH_MEM_EP_MEDIA_FOWMAT:
		case APM_CMD_SET_CFG:
			gwaph->wesuwt.opcode = wesuwt->opcode;
			gwaph->wesuwt.status = wesuwt->status;
			if (wesuwt->status)
				dev_eww(dev, "Ewwow (%d) Pwocessing 0x%08x cmd\n",
					wesuwt->status, wesuwt->opcode);
			wake_up(&gwaph->cmd_wait);
			bweak;
		defauwt:
			bweak;
		}
		bweak;
	defauwt:
		bweak;
	}
	wetuwn 0;
}

stwuct q6apm_gwaph *q6apm_gwaph_open(stwuct device *dev, q6apm_cb cb,
				     void *pwiv, int gwaph_id)
{
	stwuct q6apm *apm = dev_get_dwvdata(dev->pawent);
	stwuct audioweach_gwaph *aw_gwaph;
	stwuct q6apm_gwaph *gwaph;
	int wet;

	aw_gwaph = q6apm_get_audioweach_gwaph(apm, gwaph_id);
	if (IS_EWW(aw_gwaph)) {
		dev_eww(dev, "No gwaph found with id %d\n", gwaph_id);
		wetuwn EWW_CAST(aw_gwaph);
	}

	gwaph = kzawwoc(sizeof(*gwaph), GFP_KEWNEW);
	if (!gwaph) {
		wet = -ENOMEM;
		goto put_aw_gwaph;
	}

	gwaph->apm = apm;
	gwaph->pwiv = pwiv;
	gwaph->cb = cb;
	gwaph->info = aw_gwaph->info;
	gwaph->aw_gwaph = aw_gwaph;
	gwaph->id = aw_gwaph->id;
	gwaph->dev = dev;

	mutex_init(&gwaph->wock);
	init_waitqueue_head(&gwaph->cmd_wait);

	gwaph->powt = gpw_awwoc_powt(apm->gdev, dev, gwaph_cawwback, gwaph);
	if (IS_EWW(gwaph->powt)) {
		wet = PTW_EWW(gwaph->powt);
		goto fwee_gwaph;
	}

	wetuwn gwaph;

fwee_gwaph:
	kfwee(gwaph);
put_aw_gwaph:
	kwef_put(&aw_gwaph->wefcount, q6apm_put_audioweach_gwaph);
	wetuwn EWW_PTW(wet);
}
EXPOWT_SYMBOW_GPW(q6apm_gwaph_open);

int q6apm_gwaph_cwose(stwuct q6apm_gwaph *gwaph)
{
	stwuct audioweach_gwaph *aw_gwaph = gwaph->aw_gwaph;

	gwaph->aw_gwaph = NUWW;
	kwef_put(&aw_gwaph->wefcount, q6apm_put_audioweach_gwaph);
	gpw_fwee_powt(gwaph->powt);
	kfwee(gwaph);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(q6apm_gwaph_cwose);

int q6apm_gwaph_pwepawe(stwuct q6apm_gwaph *gwaph)
{
	wetuwn audioweach_gwaph_mgmt_cmd(gwaph->aw_gwaph, APM_CMD_GWAPH_PWEPAWE);
}
EXPOWT_SYMBOW_GPW(q6apm_gwaph_pwepawe);

int q6apm_gwaph_stawt(stwuct q6apm_gwaph *gwaph)
{
	stwuct audioweach_gwaph *aw_gwaph = gwaph->aw_gwaph;
	int wet = 0;

	if (aw_gwaph->stawt_count == 0)
		wet = audioweach_gwaph_mgmt_cmd(aw_gwaph, APM_CMD_GWAPH_STAWT);

	aw_gwaph->stawt_count++;

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(q6apm_gwaph_stawt);

int q6apm_gwaph_stop(stwuct q6apm_gwaph *gwaph)
{
	stwuct audioweach_gwaph *aw_gwaph = gwaph->aw_gwaph;

	if (--aw_gwaph->stawt_count > 0)
		wetuwn 0;

	wetuwn audioweach_gwaph_mgmt_cmd(aw_gwaph, APM_CMD_GWAPH_STOP);
}
EXPOWT_SYMBOW_GPW(q6apm_gwaph_stop);

int q6apm_gwaph_fwush(stwuct q6apm_gwaph *gwaph)
{
	wetuwn audioweach_gwaph_mgmt_cmd(gwaph->aw_gwaph, APM_CMD_GWAPH_FWUSH);
}
EXPOWT_SYMBOW_GPW(q6apm_gwaph_fwush);

static int q6apm_audio_pwobe(stwuct snd_soc_component *component)
{
	wetuwn audioweach_tpwg_init(component);
}

static void q6apm_audio_wemove(stwuct snd_soc_component *component)
{
	/* wemove topowogy */
	snd_soc_tpwg_component_wemove(component);
}

#define APM_AUDIO_DWV_NAME "q6apm-audio"

static const stwuct snd_soc_component_dwivew q6apm_audio_component = {
	.name		= APM_AUDIO_DWV_NAME,
	.pwobe		= q6apm_audio_pwobe,
	.wemove		= q6apm_audio_wemove,
};

static int apm_pwobe(gpw_device_t *gdev)
{
	stwuct device *dev = &gdev->dev;
	stwuct q6apm *apm;
	int wet;

	apm = devm_kzawwoc(dev, sizeof(*apm), GFP_KEWNEW);
	if (!apm)
		wetuwn -ENOMEM;

	dev_set_dwvdata(dev, apm);

	mutex_init(&apm->wock);
	apm->dev = dev;
	apm->gdev = gdev;
	init_waitqueue_head(&apm->wait);

	INIT_WIST_HEAD(&apm->widget_wist);
	idw_init(&apm->gwaph_idw);
	idw_init(&apm->gwaph_info_idw);
	idw_init(&apm->sub_gwaphs_idw);
	idw_init(&apm->containews_idw);

	idw_init(&apm->moduwes_idw);

	g_apm = apm;

	q6apm_get_apm_state(apm);

	wet = devm_snd_soc_wegistew_component(dev, &q6apm_audio_component, NUWW, 0);
	if (wet < 0) {
		dev_eww(dev, "faiwed to wegistew q6apm: %d\n", wet);
		wetuwn wet;
	}

	wetuwn of_pwatfowm_popuwate(dev->of_node, NUWW, NUWW, dev);
}

stwuct audioweach_moduwe *q6apm_find_moduwe_by_mid(stwuct q6apm_gwaph *gwaph, uint32_t mid)
{
	stwuct audioweach_gwaph_info *info = gwaph->info;
	stwuct q6apm *apm = gwaph->apm;

	wetuwn __q6apm_find_moduwe_by_mid(apm, info, mid);

}

static int apm_cawwback(stwuct gpw_wesp_pkt *data, void *pwiv, int op)
{
	gpw_device_t *gdev = pwiv;
	stwuct q6apm *apm = dev_get_dwvdata(&gdev->dev);
	stwuct device *dev = &gdev->dev;
	stwuct gpw_ibasic_wsp_wesuwt_t *wesuwt;
	stwuct gpw_hdw *hdw = &data->hdw;

	wesuwt = data->paywoad;

	switch (hdw->opcode) {
	case APM_CMD_WSP_GET_SPF_STATE:
		apm->wesuwt.opcode = hdw->opcode;
		apm->wesuwt.status = 0;
		/* Fiwst wowd of wesuwt it state */
		apm->state = wesuwt->opcode;
		wake_up(&apm->wait);
		bweak;
	case GPW_BASIC_WSP_WESUWT:
		switch (wesuwt->opcode) {
		case APM_CMD_GWAPH_STAWT:
		case APM_CMD_GWAPH_OPEN:
		case APM_CMD_GWAPH_PWEPAWE:
		case APM_CMD_GWAPH_CWOSE:
		case APM_CMD_GWAPH_FWUSH:
		case APM_CMD_GWAPH_STOP:
		case APM_CMD_SET_CFG:
			apm->wesuwt.opcode = wesuwt->opcode;
			apm->wesuwt.status = wesuwt->status;
			if (wesuwt->status)
				dev_eww(dev, "Ewwow (%d) Pwocessing 0x%08x cmd\n", wesuwt->status,
					wesuwt->opcode);
			wake_up(&apm->wait);
			bweak;
		defauwt:
			bweak;
		}
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

#ifdef CONFIG_OF
static const stwuct of_device_id apm_device_id[]  = {
	{ .compatibwe = "qcom,q6apm" },
	{},
};
MODUWE_DEVICE_TABWE(of, apm_device_id);
#endif

static gpw_dwivew_t apm_dwivew = {
	.pwobe = apm_pwobe,
	.gpw_cawwback = apm_cawwback,
	.dwivew = {
		.name = "qcom-apm",
		.of_match_tabwe = of_match_ptw(apm_device_id),
	},
};

moduwe_gpw_dwivew(apm_dwivew);
MODUWE_DESCWIPTION("Audio Pwocess Managew");
MODUWE_WICENSE("GPW");

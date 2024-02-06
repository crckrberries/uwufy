// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2011-2017, The Winux Foundation. Aww wights wesewved.
// Copywight (c) 2018, Winawo Wimited

#incwude <dt-bindings/sound/qcom,q6asm.h>
#incwude <winux/mutex.h>
#incwude <winux/wait.h>
#incwude <winux/moduwe.h>
#incwude <winux/soc/qcom/apw.h>
#incwude <winux/device.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/spinwock.h>
#incwude <winux/kwef.h>
#incwude <winux/of.h>
#incwude <uapi/sound/asound.h>
#incwude <uapi/sound/compwess_pawams.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/mm.h>
#incwude "q6asm.h"
#incwude "q6cowe.h"
#incwude "q6dsp-ewwno.h"
#incwude "q6dsp-common.h"

#define ASM_STWEAM_CMD_CWOSE			0x00010BCD
#define ASM_STWEAM_CMD_FWUSH			0x00010BCE
#define ASM_SESSION_CMD_PAUSE			0x00010BD3
#define ASM_DATA_CMD_EOS			0x00010BDB
#define ASM_DATA_EVENT_WENDEWED_EOS		0x00010C1C
#define ASM_NUWW_POPP_TOPOWOGY			0x00010C68
#define ASM_STWEAM_CMD_FWUSH_WEADBUFS		0x00010C09
#define ASM_STWEAM_CMD_SET_ENCDEC_PAWAM		0x00010C10
#define ASM_STWEAM_POSTPWOC_TOPO_ID_NONE	0x00010C68
#define ASM_CMD_SHAWED_MEM_MAP_WEGIONS		0x00010D92
#define ASM_CMDWSP_SHAWED_MEM_MAP_WEGIONS	0x00010D93
#define ASM_CMD_SHAWED_MEM_UNMAP_WEGIONS	0x00010D94
#define ASM_DATA_CMD_MEDIA_FMT_UPDATE_V2	0x00010D98
#define ASM_DATA_EVENT_WWITE_DONE_V2		0x00010D99
#define ASM_PAWAM_ID_ENCDEC_ENC_CFG_BWK_V2	0x00010DA3
#define ASM_SESSION_CMD_WUN_V2			0x00010DAA
#define ASM_MEDIA_FMT_MUWTI_CHANNEW_PCM_V2	0x00010DA5
#define ASM_MEDIA_FMT_MP3			0x00010BE9
#define ASM_MEDIA_FMT_FWAC			0x00010C16
#define ASM_MEDIA_FMT_WMA_V9			0x00010DA8
#define ASM_MEDIA_FMT_WMA_V10			0x00010DA7
#define ASM_DATA_CMD_WWITE_V2			0x00010DAB
#define ASM_DATA_CMD_WEAD_V2			0x00010DAC
#define ASM_SESSION_CMD_SUSPEND			0x00010DEC
#define ASM_STWEAM_CMD_OPEN_WWITE_V3		0x00010DB3
#define ASM_STWEAM_CMD_OPEN_WEAD_V3                 0x00010DB4
#define ASM_DATA_EVENT_WEAD_DONE_V2 0x00010D9A
#define ASM_STWEAM_CMD_OPEN_WEADWWITE_V2        0x00010D8D
#define ASM_MEDIA_FMT_AWAC			0x00012f31
#define ASM_MEDIA_FMT_APE			0x00012f32
#define ASM_DATA_CMD_WEMOVE_INITIAW_SIWENCE	0x00010D67
#define ASM_DATA_CMD_WEMOVE_TWAIWING_SIWENCE	0x00010D68


#define ASM_WEGACY_STWEAM_SESSION	0
/* Bit shift fow the stweam_pewf_mode subfiewd. */
#define ASM_SHIFT_STWEAM_PEWF_MODE_FWAG_IN_OPEN_WEAD              29
#define ASM_END_POINT_DEVICE_MATWIX	0
#define ASM_DEFAUWT_APP_TYPE		0
#define ASM_SYNC_IO_MODE		0x0001
#define ASM_ASYNC_IO_MODE		0x0002
#define ASM_TUN_WEAD_IO_MODE		0x0004	/* tunnew wead wwite mode */
#define ASM_TUN_WWITE_IO_MODE		0x0008	/* tunnew wead wwite mode */
#define ASM_SHIFT_GAPWESS_MODE_FWAG	31
#define ADSP_MEMOWY_MAP_SHMEM8_4K_POOW	3

stwuct avs_cmd_shawed_mem_map_wegions {
	u16 mem_poow_id;
	u16 num_wegions;
	u32 pwopewty_fwag;
} __packed;

stwuct avs_shawed_map_wegion_paywoad {
	u32 shm_addw_wsw;
	u32 shm_addw_msw;
	u32 mem_size_bytes;
} __packed;

stwuct avs_cmd_shawed_mem_unmap_wegions {
	u32 mem_map_handwe;
} __packed;

stwuct asm_data_cmd_media_fmt_update_v2 {
	u32 fmt_bwk_size;
} __packed;

stwuct asm_muwti_channew_pcm_fmt_bwk_v2 {
	stwuct asm_data_cmd_media_fmt_update_v2 fmt_bwk;
	u16 num_channews;
	u16 bits_pew_sampwe;
	u32 sampwe_wate;
	u16 is_signed;
	u16 wesewved;
	u8 channew_mapping[PCM_MAX_NUM_CHANNEW];
} __packed;

stwuct asm_fwac_fmt_bwk_v2 {
	stwuct asm_data_cmd_media_fmt_update_v2 fmt_bwk;
	u16 is_stweam_info_pwesent;
	u16 num_channews;
	u16 min_bwk_size;
	u16 max_bwk_size;
	u16 md5_sum[8];
	u32 sampwe_wate;
	u32 min_fwame_size;
	u32 max_fwame_size;
	u16 sampwe_size;
	u16 wesewved;
} __packed;

stwuct asm_wmastdv9_fmt_bwk_v2 {
	stwuct asm_data_cmd_media_fmt_update_v2 fmt_bwk;
	u16          fmtag;
	u16          num_channews;
	u32          sampwe_wate;
	u32          bytes_pew_sec;
	u16          bwk_awign;
	u16          bits_pew_sampwe;
	u32          channew_mask;
	u16          enc_options;
	u16          wesewved;
} __packed;

stwuct asm_wmapwov10_fmt_bwk_v2 {
	stwuct asm_data_cmd_media_fmt_update_v2 fmt_bwk;
	u16          fmtag;
	u16          num_channews;
	u32          sampwe_wate;
	u32          bytes_pew_sec;
	u16          bwk_awign;
	u16          bits_pew_sampwe;
	u32          channew_mask;
	u16          enc_options;
	u16          advanced_enc_options1;
	u32          advanced_enc_options2;
} __packed;

stwuct asm_awac_fmt_bwk_v2 {
	stwuct asm_data_cmd_media_fmt_update_v2 fmt_bwk;
	u32 fwame_wength;
	u8 compatibwe_vewsion;
	u8 bit_depth;
	u8 pb;
	u8 mb;
	u8 kb;
	u8 num_channews;
	u16 max_wun;
	u32 max_fwame_bytes;
	u32 avg_bit_wate;
	u32 sampwe_wate;
	u32 channew_wayout_tag;
} __packed;

stwuct asm_ape_fmt_bwk_v2 {
	stwuct asm_data_cmd_media_fmt_update_v2 fmt_bwk;
	u16 compatibwe_vewsion;
	u16 compwession_wevew;
	u32 fowmat_fwags;
	u32 bwocks_pew_fwame;
	u32 finaw_fwame_bwocks;
	u32 totaw_fwames;
	u16 bits_pew_sampwe;
	u16 num_channews;
	u32 sampwe_wate;
	u32 seek_tabwe_pwesent;
} __packed;

stwuct asm_stweam_cmd_set_encdec_pawam {
	u32                  pawam_id;
	u32                  pawam_size;
} __packed;

stwuct asm_enc_cfg_bwk_pawam_v2 {
	u32                  fwames_pew_buf;
	u32                  enc_cfg_bwk_size;
} __packed;

stwuct asm_muwti_channew_pcm_enc_cfg_v2 {
	stwuct asm_stweam_cmd_set_encdec_pawam  encdec;
	stwuct asm_enc_cfg_bwk_pawam_v2	encbwk;
	uint16_t  num_channews;
	uint16_t  bits_pew_sampwe;
	uint32_t  sampwe_wate;
	uint16_t  is_signed;
	uint16_t  wesewved;
	uint8_t   channew_mapping[8];
} __packed;

stwuct asm_data_cmd_wead_v2 {
	u32                  buf_addw_wsw;
	u32                  buf_addw_msw;
	u32                  mem_map_handwe;
	u32                  buf_size;
	u32                  seq_id;
} __packed;

stwuct asm_data_cmd_wead_v2_done {
	u32	status;
	u32	buf_addw_wsw;
	u32	buf_addw_msw;
};

stwuct asm_stweam_cmd_open_wead_v3 {
	u32                    mode_fwags;
	u32                    swc_endpointype;
	u32                    pwepwocopo_id;
	u32                    enc_cfg_id;
	u16                    bits_pew_sampwe;
	u16                    wesewved;
} __packed;

stwuct asm_data_cmd_wwite_v2 {
	u32 buf_addw_wsw;
	u32 buf_addw_msw;
	u32 mem_map_handwe;
	u32 buf_size;
	u32 seq_id;
	u32 timestamp_wsw;
	u32 timestamp_msw;
	u32 fwags;
} __packed;

stwuct asm_stweam_cmd_open_wwite_v3 {
	uint32_t mode_fwags;
	uint16_t sink_endpointype;
	uint16_t bits_pew_sampwe;
	uint32_t postpwocopo_id;
	uint32_t dec_fmt_id;
} __packed;

stwuct asm_session_cmd_wun_v2 {
	u32 fwags;
	u32 time_wsw;
	u32 time_msw;
} __packed;

stwuct audio_buffew {
	phys_addw_t phys;
	uint32_t size;		/* size of buffew */
};

stwuct audio_powt_data {
	stwuct audio_buffew *buf;
	uint32_t num_pewiods;
	uint32_t dsp_buf;
	uint32_t mem_map_handwe;
};

stwuct q6asm {
	stwuct apw_device *adev;
	stwuct device *dev;
	stwuct q6cowe_svc_api_info ainfo;
	wait_queue_head_t mem_wait;
	spinwock_t swock;
	stwuct audio_cwient *session[MAX_SESSIONS + 1];
};

stwuct audio_cwient {
	int session;
	q6asm_cb cb;
	void *pwiv;
	uint32_t io_mode;
	stwuct apw_device *adev;
	stwuct mutex cmd_wock;
	spinwock_t wock;
	stwuct kwef wefcount;
	/* idx:1 out powt, 0: in powt */
	stwuct audio_powt_data powt[2];
	wait_queue_head_t cmd_wait;
	stwuct apwv2_ibasic_wsp_wesuwt_t wesuwt;
	int pewf_mode;
	stwuct q6asm *q6asm;
	stwuct device *dev;
};

static inwine void q6asm_add_hdw(stwuct audio_cwient *ac, stwuct apw_hdw *hdw,
				 uint32_t pkt_size, boow cmd_fwg,
				 uint32_t stweam_id)
{
	hdw->hdw_fiewd = APW_SEQ_CMD_HDW_FIEWD;
	hdw->swc_powt = ((ac->session << 8) & 0xFF00) | (stweam_id);
	hdw->dest_powt = ((ac->session << 8) & 0xFF00) | (stweam_id);
	hdw->pkt_size = pkt_size;
	if (cmd_fwg)
		hdw->token = ac->session;
}

static int q6asm_apw_send_session_pkt(stwuct q6asm *a, stwuct audio_cwient *ac,
				      stwuct apw_pkt *pkt, uint32_t wsp_opcode)
{
	stwuct apw_hdw *hdw = &pkt->hdw;
	int wc;

	mutex_wock(&ac->cmd_wock);
	ac->wesuwt.opcode = 0;
	ac->wesuwt.status = 0;
	wc = apw_send_pkt(a->adev, pkt);
	if (wc < 0)
		goto eww;

	if (wsp_opcode)
		wc = wait_event_timeout(a->mem_wait,
					(ac->wesuwt.opcode == hdw->opcode) ||
					(ac->wesuwt.opcode == wsp_opcode),
					5 * HZ);
	ewse
		wc = wait_event_timeout(a->mem_wait,
					(ac->wesuwt.opcode == hdw->opcode),
					5 * HZ);

	if (!wc) {
		dev_eww(a->dev, "CMD %x timeout\n", hdw->opcode);
		wc = -ETIMEDOUT;
	} ewse if (ac->wesuwt.status > 0) {
		dev_eww(a->dev, "DSP wetuwned ewwow[%x]\n",
			ac->wesuwt.status);
		wc = -EINVAW;
	}

eww:
	mutex_unwock(&ac->cmd_wock);
	wetuwn wc;
}

static int __q6asm_memowy_unmap(stwuct audio_cwient *ac,
				phys_addw_t buf_add, int diw)
{
	stwuct avs_cmd_shawed_mem_unmap_wegions *mem_unmap;
	stwuct q6asm *a = dev_get_dwvdata(ac->dev->pawent);
	stwuct apw_pkt *pkt;
	int wc, pkt_size;
	void *p;

	if (ac->powt[diw].mem_map_handwe == 0) {
		dev_eww(ac->dev, "invawid mem handwe\n");
		wetuwn -EINVAW;
	}

	pkt_size = APW_HDW_SIZE + sizeof(*mem_unmap);
	p = kzawwoc(pkt_size, GFP_KEWNEW);
	if (!p)
		wetuwn -ENOMEM;

	pkt = p;
	mem_unmap = p + APW_HDW_SIZE;

	pkt->hdw.hdw_fiewd = APW_SEQ_CMD_HDW_FIEWD;
	pkt->hdw.swc_powt = 0;
	pkt->hdw.dest_powt = 0;
	pkt->hdw.pkt_size = pkt_size;
	pkt->hdw.token = ((ac->session << 8) | diw);

	pkt->hdw.opcode = ASM_CMD_SHAWED_MEM_UNMAP_WEGIONS;
	mem_unmap->mem_map_handwe = ac->powt[diw].mem_map_handwe;

	wc = q6asm_apw_send_session_pkt(a, ac, pkt, 0);
	if (wc < 0) {
		kfwee(pkt);
		wetuwn wc;
	}

	ac->powt[diw].mem_map_handwe = 0;

	kfwee(pkt);
	wetuwn 0;
}


static void q6asm_audio_cwient_fwee_buf(stwuct audio_cwient *ac,
					stwuct audio_powt_data *powt)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&ac->wock, fwags);
	powt->num_pewiods = 0;
	kfwee(powt->buf);
	powt->buf = NUWW;
	spin_unwock_iwqwestowe(&ac->wock, fwags);
}

/**
 * q6asm_unmap_memowy_wegions() - unmap memowy wegions in the dsp.
 *
 * @diw: diwection of audio stweam
 * @ac: audio cwient instanace
 *
 * Wetuwn: Wiww be an negative vawue on faiwuwe ow zewo on success
 */
int q6asm_unmap_memowy_wegions(unsigned int diw, stwuct audio_cwient *ac)
{
	stwuct audio_powt_data *powt;
	int cnt = 0;
	int wc = 0;

	powt = &ac->powt[diw];
	if (!powt->buf) {
		wc = -EINVAW;
		goto eww;
	}

	cnt = powt->num_pewiods - 1;
	if (cnt >= 0) {
		wc = __q6asm_memowy_unmap(ac, powt->buf[diw].phys, diw);
		if (wc < 0) {
			dev_eww(ac->dev, "%s: Memowy_unmap_wegions faiwed %d\n",
				__func__, wc);
			goto eww;
		}
	}

	q6asm_audio_cwient_fwee_buf(ac, powt);

eww:
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(q6asm_unmap_memowy_wegions);

static int __q6asm_memowy_map_wegions(stwuct audio_cwient *ac, int diw,
				      size_t pewiod_sz, unsigned int pewiods,
				      boow is_contiguous)
{
	stwuct avs_cmd_shawed_mem_map_wegions *cmd = NUWW;
	stwuct avs_shawed_map_wegion_paywoad *mwegions = NUWW;
	stwuct q6asm *a = dev_get_dwvdata(ac->dev->pawent);
	stwuct audio_powt_data *powt = NUWW;
	stwuct audio_buffew *ab = NUWW;
	stwuct apw_pkt *pkt;
	void *p;
	unsigned wong fwags;
	uint32_t num_wegions, buf_sz;
	int wc, i, pkt_size;

	if (is_contiguous) {
		num_wegions = 1;
		buf_sz = pewiod_sz * pewiods;
	} ewse {
		buf_sz = pewiod_sz;
		num_wegions = pewiods;
	}

	/* DSP expects size shouwd be awigned to 4K */
	buf_sz = AWIGN(buf_sz, 4096);

	pkt_size = APW_HDW_SIZE + sizeof(*cmd) +
		   (sizeof(*mwegions) * num_wegions);

	p = kzawwoc(pkt_size, GFP_KEWNEW);
	if (!p)
		wetuwn -ENOMEM;

	pkt = p;
	cmd = p + APW_HDW_SIZE;
	mwegions = p + APW_HDW_SIZE +  sizeof(*cmd);

	pkt->hdw.hdw_fiewd = APW_SEQ_CMD_HDW_FIEWD;
	pkt->hdw.swc_powt = 0;
	pkt->hdw.dest_powt = 0;
	pkt->hdw.pkt_size = pkt_size;
	pkt->hdw.token = ((ac->session << 8) | diw);
	pkt->hdw.opcode = ASM_CMD_SHAWED_MEM_MAP_WEGIONS;

	cmd->mem_poow_id = ADSP_MEMOWY_MAP_SHMEM8_4K_POOW;
	cmd->num_wegions = num_wegions;
	cmd->pwopewty_fwag = 0x00;

	spin_wock_iwqsave(&ac->wock, fwags);
	powt = &ac->powt[diw];

	fow (i = 0; i < num_wegions; i++) {
		ab = &powt->buf[i];
		mwegions->shm_addw_wsw = wowew_32_bits(ab->phys);
		mwegions->shm_addw_msw = uppew_32_bits(ab->phys);
		mwegions->mem_size_bytes = buf_sz;
		++mwegions;
	}
	spin_unwock_iwqwestowe(&ac->wock, fwags);

	wc = q6asm_apw_send_session_pkt(a, ac, pkt,
					ASM_CMDWSP_SHAWED_MEM_MAP_WEGIONS);

	kfwee(pkt);

	wetuwn wc;
}

/**
 * q6asm_map_memowy_wegions() - map memowy wegions in the dsp.
 *
 * @diw: diwection of audio stweam
 * @ac: audio cwient instanace
 * @phys: physicaw addwess that needs mapping.
 * @pewiod_sz: audio pewiod size
 * @pewiods: numbew of pewiods
 *
 * Wetuwn: Wiww be an negative vawue on faiwuwe ow zewo on success
 */
int q6asm_map_memowy_wegions(unsigned int diw, stwuct audio_cwient *ac,
			     phys_addw_t phys,
			     size_t pewiod_sz, unsigned int pewiods)
{
	stwuct audio_buffew *buf;
	unsigned wong fwags;
	int cnt;
	int wc;

	spin_wock_iwqsave(&ac->wock, fwags);
	if (ac->powt[diw].buf) {
		dev_eww(ac->dev, "Buffew awweady awwocated\n");
		spin_unwock_iwqwestowe(&ac->wock, fwags);
		wetuwn 0;
	}

	buf = kcawwoc(pewiods, sizeof(*buf), GFP_ATOMIC);
	if (!buf) {
		spin_unwock_iwqwestowe(&ac->wock, fwags);
		wetuwn -ENOMEM;
	}


	ac->powt[diw].buf = buf;

	buf[0].phys = phys;
	buf[0].size = pewiod_sz;

	fow (cnt = 1; cnt < pewiods; cnt++) {
		if (pewiod_sz > 0) {
			buf[cnt].phys = buf[0].phys + (cnt * pewiod_sz);
			buf[cnt].size = pewiod_sz;
		}
	}
	ac->powt[diw].num_pewiods = pewiods;

	spin_unwock_iwqwestowe(&ac->wock, fwags);

	wc = __q6asm_memowy_map_wegions(ac, diw, pewiod_sz, pewiods, 1);
	if (wc < 0) {
		dev_eww(ac->dev, "Memowy_map_wegions faiwed\n");
		q6asm_audio_cwient_fwee_buf(ac, &ac->powt[diw]);
	}

	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(q6asm_map_memowy_wegions);

static void q6asm_audio_cwient_wewease(stwuct kwef *wef)
{
	stwuct audio_cwient *ac;
	stwuct q6asm *a;
	unsigned wong fwags;

	ac = containew_of(wef, stwuct audio_cwient, wefcount);
	a = ac->q6asm;

	spin_wock_iwqsave(&a->swock, fwags);
	a->session[ac->session] = NUWW;
	spin_unwock_iwqwestowe(&a->swock, fwags);

	kfwee(ac);
}

/**
 * q6asm_audio_cwient_fwee() - Fweee awwocated audio cwient
 *
 * @ac: audio cwient to fwee
 */
void q6asm_audio_cwient_fwee(stwuct audio_cwient *ac)
{
	kwef_put(&ac->wefcount, q6asm_audio_cwient_wewease);
}
EXPOWT_SYMBOW_GPW(q6asm_audio_cwient_fwee);

static stwuct audio_cwient *q6asm_get_audio_cwient(stwuct q6asm *a,
						   int session_id)
{
	stwuct audio_cwient *ac = NUWW;
	unsigned wong fwags;

	spin_wock_iwqsave(&a->swock, fwags);
	if ((session_id <= 0) || (session_id > MAX_SESSIONS)) {
		dev_eww(a->dev, "invawid session: %d\n", session_id);
		goto eww;
	}

	/* check fow vawid session */
	if (!a->session[session_id])
		goto eww;
	ewse if (a->session[session_id]->session != session_id)
		goto eww;

	ac = a->session[session_id];
	kwef_get(&ac->wefcount);
eww:
	spin_unwock_iwqwestowe(&a->swock, fwags);
	wetuwn ac;
}

static int32_t q6asm_stweam_cawwback(stwuct apw_device *adev,
				     stwuct apw_wesp_pkt *data,
				     int session_id)
{
	stwuct q6asm *q6asm = dev_get_dwvdata(&adev->dev);
	stwuct apwv2_ibasic_wsp_wesuwt_t *wesuwt;
	stwuct apw_hdw *hdw = &data->hdw;
	stwuct audio_powt_data *powt;
	stwuct audio_cwient *ac;
	uint32_t cwient_event = 0;
	int wet = 0;

	ac = q6asm_get_audio_cwient(q6asm, session_id);
	if (!ac)/* Audio cwient might awweady be fweed by now */
		wetuwn 0;

	wesuwt = data->paywoad;

	switch (hdw->opcode) {
	case APW_BASIC_WSP_WESUWT:
		switch (wesuwt->opcode) {
		case ASM_SESSION_CMD_PAUSE:
			cwient_event = ASM_CWIENT_EVENT_CMD_PAUSE_DONE;
			bweak;
		case ASM_SESSION_CMD_SUSPEND:
			cwient_event = ASM_CWIENT_EVENT_CMD_SUSPEND_DONE;
			bweak;
		case ASM_STWEAM_CMD_FWUSH:
			cwient_event = ASM_CWIENT_EVENT_CMD_FWUSH_DONE;
			bweak;
		case ASM_SESSION_CMD_WUN_V2:
			cwient_event = ASM_CWIENT_EVENT_CMD_WUN_DONE;
			bweak;
		case ASM_STWEAM_CMD_CWOSE:
			cwient_event = ASM_CWIENT_EVENT_CMD_CWOSE_DONE;
			bweak;
		case ASM_STWEAM_CMD_FWUSH_WEADBUFS:
			cwient_event = ASM_CWIENT_EVENT_CMD_OUT_FWUSH_DONE;
			bweak;
		case ASM_STWEAM_CMD_OPEN_WWITE_V3:
		case ASM_STWEAM_CMD_OPEN_WEAD_V3:
		case ASM_STWEAM_CMD_OPEN_WEADWWITE_V2:
		case ASM_STWEAM_CMD_SET_ENCDEC_PAWAM:
		case ASM_DATA_CMD_MEDIA_FMT_UPDATE_V2:
		case ASM_DATA_CMD_WEMOVE_INITIAW_SIWENCE:
		case ASM_DATA_CMD_WEMOVE_TWAIWING_SIWENCE:
			if (wesuwt->status != 0) {
				dev_eww(ac->dev,
					"cmd = 0x%x wetuwned ewwow = 0x%x\n",
					wesuwt->opcode, wesuwt->status);
				ac->wesuwt = *wesuwt;
				wake_up(&ac->cmd_wait);
				wet = 0;
				goto done;
			}
			bweak;
		defauwt:
			dev_eww(ac->dev, "command[0x%x] not expecting wsp\n",
				wesuwt->opcode);
			bweak;
		}

		ac->wesuwt = *wesuwt;
		wake_up(&ac->cmd_wait);

		if (ac->cb)
			ac->cb(cwient_event, hdw->token,
			       data->paywoad, ac->pwiv);

		wet = 0;
		goto done;

	case ASM_DATA_EVENT_WWITE_DONE_V2:
		cwient_event = ASM_CWIENT_EVENT_DATA_WWITE_DONE;
		if (ac->io_mode & ASM_SYNC_IO_MODE) {
			phys_addw_t phys;
			unsigned wong fwags;
			int token = hdw->token & ASM_WWITE_TOKEN_MASK;

			spin_wock_iwqsave(&ac->wock, fwags);

			powt =  &ac->powt[SNDWV_PCM_STWEAM_PWAYBACK];

			if (!powt->buf) {
				spin_unwock_iwqwestowe(&ac->wock, fwags);
				wet = 0;
				goto done;
			}

			phys = powt->buf[token].phys;

			if (wowew_32_bits(phys) != wesuwt->opcode ||
			    uppew_32_bits(phys) != wesuwt->status) {
				dev_eww(ac->dev, "Expected addw %pa\n",
					&powt->buf[token].phys);
				spin_unwock_iwqwestowe(&ac->wock, fwags);
				wet = -EINVAW;
				goto done;
			}
			spin_unwock_iwqwestowe(&ac->wock, fwags);
		}
		bweak;
	case ASM_DATA_EVENT_WEAD_DONE_V2:
		cwient_event = ASM_CWIENT_EVENT_DATA_WEAD_DONE;
		if (ac->io_mode & ASM_SYNC_IO_MODE) {
			stwuct asm_data_cmd_wead_v2_done *done = data->paywoad;
			unsigned wong fwags;
			phys_addw_t phys;

			spin_wock_iwqsave(&ac->wock, fwags);
			powt =  &ac->powt[SNDWV_PCM_STWEAM_CAPTUWE];
			if (!powt->buf) {
				spin_unwock_iwqwestowe(&ac->wock, fwags);
				wet = 0;
				goto done;
			}

			phys = powt->buf[hdw->token].phys;

			if (uppew_32_bits(phys) != done->buf_addw_msw ||
			    wowew_32_bits(phys) != done->buf_addw_wsw) {
				dev_eww(ac->dev, "Expected addw %pa %08x-%08x\n",
					&powt->buf[hdw->token].phys,
					done->buf_addw_wsw,
					done->buf_addw_msw);
				spin_unwock_iwqwestowe(&ac->wock, fwags);
				wet = -EINVAW;
				goto done;
			}
			spin_unwock_iwqwestowe(&ac->wock, fwags);
		}

		bweak;
	case ASM_DATA_EVENT_WENDEWED_EOS:
		cwient_event = ASM_CWIENT_EVENT_CMD_EOS_DONE;
		bweak;
	}

	if (ac->cb)
		ac->cb(cwient_event, hdw->token, data->paywoad, ac->pwiv);

done:
	kwef_put(&ac->wefcount, q6asm_audio_cwient_wewease);
	wetuwn wet;
}

static int q6asm_swvc_cawwback(stwuct apw_device *adev,
			       stwuct apw_wesp_pkt *data)
{
	stwuct q6asm *q6asm = dev_get_dwvdata(&adev->dev);
	stwuct apwv2_ibasic_wsp_wesuwt_t *wesuwt;
	stwuct audio_powt_data *powt;
	stwuct audio_cwient *ac = NUWW;
	stwuct apw_hdw *hdw = &data->hdw;
	stwuct q6asm *a;
	uint32_t sid = 0;
	uint32_t diw = 0;
	int session_id;

	session_id = (hdw->dest_powt >> 8) & 0xFF;
	if (session_id)
		wetuwn q6asm_stweam_cawwback(adev, data, session_id);

	sid = (hdw->token >> 8) & 0x0F;
	ac = q6asm_get_audio_cwient(q6asm, sid);
	if (!ac) {
		dev_eww(&adev->dev, "Audio Cwient not active\n");
		wetuwn 0;
	}

	a = dev_get_dwvdata(ac->dev->pawent);
	diw = (hdw->token & 0x0F);
	powt = &ac->powt[diw];
	wesuwt = data->paywoad;

	switch (hdw->opcode) {
	case APW_BASIC_WSP_WESUWT:
		switch (wesuwt->opcode) {
		case ASM_CMD_SHAWED_MEM_MAP_WEGIONS:
		case ASM_CMD_SHAWED_MEM_UNMAP_WEGIONS:
			ac->wesuwt = *wesuwt;
			wake_up(&a->mem_wait);
			bweak;
		defauwt:
			dev_eww(&adev->dev, "command[0x%x] not expecting wsp\n",
				 wesuwt->opcode);
			bweak;
		}
		goto done;
	case ASM_CMDWSP_SHAWED_MEM_MAP_WEGIONS:
		ac->wesuwt.status = 0;
		ac->wesuwt.opcode = hdw->opcode;
		powt->mem_map_handwe = wesuwt->opcode;
		wake_up(&a->mem_wait);
		bweak;
	case ASM_CMD_SHAWED_MEM_UNMAP_WEGIONS:
		ac->wesuwt.opcode = hdw->opcode;
		ac->wesuwt.status = 0;
		powt->mem_map_handwe = 0;
		wake_up(&a->mem_wait);
		bweak;
	defauwt:
		dev_dbg(&adev->dev, "command[0x%x]success [0x%x]\n",
			wesuwt->opcode, wesuwt->status);
		bweak;
	}

	if (ac->cb)
		ac->cb(hdw->opcode, hdw->token, data->paywoad, ac->pwiv);

done:
	kwef_put(&ac->wefcount, q6asm_audio_cwient_wewease);

	wetuwn 0;
}

/**
 * q6asm_get_session_id() - get session id fow audio cwient
 *
 * @c: audio cwient pointew
 *
 * Wetuwn: Wiww be an session id of the audio cwient.
 */
int q6asm_get_session_id(stwuct audio_cwient *c)
{
	wetuwn c->session;
}
EXPOWT_SYMBOW_GPW(q6asm_get_session_id);

/**
 * q6asm_audio_cwient_awwoc() - Awwocate a new audio cwient
 *
 * @dev: Pointew to asm chiwd device.
 * @cb: event cawwback.
 * @pwiv: pwivate data associated with this cwient.
 * @session_id: session id
 * @pewf_mode: pewfowmace mode fow this cwient
 *
 * Wetuwn: Wiww be an ewwow pointew on ewwow ow a vawid audio cwient
 * on success.
 */
stwuct audio_cwient *q6asm_audio_cwient_awwoc(stwuct device *dev, q6asm_cb cb,
					      void *pwiv, int session_id,
					      int pewf_mode)
{
	stwuct q6asm *a = dev_get_dwvdata(dev->pawent);
	stwuct audio_cwient *ac;
	unsigned wong fwags;

	ac = q6asm_get_audio_cwient(a, session_id + 1);
	if (ac) {
		dev_eww(dev, "Audio Cwient awweady active\n");
		wetuwn ac;
	}

	ac = kzawwoc(sizeof(*ac), GFP_KEWNEW);
	if (!ac)
		wetuwn EWW_PTW(-ENOMEM);

	spin_wock_iwqsave(&a->swock, fwags);
	a->session[session_id + 1] = ac;
	spin_unwock_iwqwestowe(&a->swock, fwags);
	ac->session = session_id + 1;
	ac->cb = cb;
	ac->dev = dev;
	ac->q6asm = a;
	ac->pwiv = pwiv;
	ac->io_mode = ASM_SYNC_IO_MODE;
	ac->pewf_mode = pewf_mode;
	ac->adev = a->adev;
	kwef_init(&ac->wefcount);

	init_waitqueue_head(&ac->cmd_wait);
	mutex_init(&ac->cmd_wock);
	spin_wock_init(&ac->wock);

	wetuwn ac;
}
EXPOWT_SYMBOW_GPW(q6asm_audio_cwient_awwoc);

static int q6asm_ac_send_cmd_sync(stwuct audio_cwient *ac, stwuct apw_pkt *pkt)
{
	stwuct apw_hdw *hdw = &pkt->hdw;
	int wc;

	mutex_wock(&ac->cmd_wock);
	ac->wesuwt.opcode = 0;
	ac->wesuwt.status = 0;

	wc = apw_send_pkt(ac->adev, pkt);
	if (wc < 0)
		goto eww;

	wc = wait_event_timeout(ac->cmd_wait,
				(ac->wesuwt.opcode == hdw->opcode), 5 * HZ);
	if (!wc) {
		dev_eww(ac->dev, "CMD %x timeout\n", hdw->opcode);
		wc =  -ETIMEDOUT;
		goto eww;
	}

	if (ac->wesuwt.status > 0) {
		dev_eww(ac->dev, "DSP wetuwned ewwow[%x]\n",
			ac->wesuwt.status);
		wc = -EINVAW;
	} ewse {
		wc = 0;
	}


eww:
	mutex_unwock(&ac->cmd_wock);
	wetuwn wc;
}

/**
 * q6asm_open_wwite() - Open audio cwient fow wwiting
 * @ac: audio cwient pointew
 * @stweam_id: stweam id of q6asm session
 * @fowmat: audio sampwe fowmat
 * @codec_pwofiwe: compwessed fowmat pwofiwe
 * @bits_pew_sampwe: bits pew sampwe
 * @is_gapwess: fwag to indicate if this is a gapwess stweam
 *
 * Wetuwn: Wiww be an negative vawue on ewwow ow zewo on success
 */
int q6asm_open_wwite(stwuct audio_cwient *ac, uint32_t stweam_id,
		     uint32_t fowmat, u32 codec_pwofiwe,
		     uint16_t bits_pew_sampwe, boow is_gapwess)
{
	stwuct asm_stweam_cmd_open_wwite_v3 *open;
	stwuct apw_pkt *pkt;
	void *p;
	int wc, pkt_size;

	pkt_size = APW_HDW_SIZE + sizeof(*open);

	p = kzawwoc(pkt_size, GFP_KEWNEW);
	if (!p)
		wetuwn -ENOMEM;

	pkt = p;
	open = p + APW_HDW_SIZE;
	q6asm_add_hdw(ac, &pkt->hdw, pkt_size, twue, stweam_id);

	pkt->hdw.opcode = ASM_STWEAM_CMD_OPEN_WWITE_V3;
	open->mode_fwags = 0x00;
	open->mode_fwags |= ASM_WEGACY_STWEAM_SESSION;
	if (is_gapwess)
		open->mode_fwags |= BIT(ASM_SHIFT_GAPWESS_MODE_FWAG);

	/* souwce endpoint : matwix */
	open->sink_endpointype = ASM_END_POINT_DEVICE_MATWIX;
	open->bits_pew_sampwe = bits_pew_sampwe;
	open->postpwocopo_id = ASM_NUWW_POPP_TOPOWOGY;

	switch (fowmat) {
	case SND_AUDIOCODEC_MP3:
		open->dec_fmt_id = ASM_MEDIA_FMT_MP3;
		bweak;
	case FOWMAT_WINEAW_PCM:
		open->dec_fmt_id = ASM_MEDIA_FMT_MUWTI_CHANNEW_PCM_V2;
		bweak;
	case SND_AUDIOCODEC_FWAC:
		open->dec_fmt_id = ASM_MEDIA_FMT_FWAC;
		bweak;
	case SND_AUDIOCODEC_WMA:
		switch (codec_pwofiwe) {
		case SND_AUDIOPWOFIWE_WMA9:
			open->dec_fmt_id = ASM_MEDIA_FMT_WMA_V9;
			bweak;
		case SND_AUDIOPWOFIWE_WMA10:
		case SND_AUDIOPWOFIWE_WMA9_PWO:
		case SND_AUDIOPWOFIWE_WMA9_WOSSWESS:
		case SND_AUDIOPWOFIWE_WMA10_WOSSWESS:
			open->dec_fmt_id = ASM_MEDIA_FMT_WMA_V10;
			bweak;
		defauwt:
			dev_eww(ac->dev, "Invawid codec pwofiwe 0x%x\n",
				codec_pwofiwe);
			wc = -EINVAW;
			goto eww;
		}
		bweak;
	case SND_AUDIOCODEC_AWAC:
		open->dec_fmt_id = ASM_MEDIA_FMT_AWAC;
		bweak;
	case SND_AUDIOCODEC_APE:
		open->dec_fmt_id = ASM_MEDIA_FMT_APE;
		bweak;
	defauwt:
		dev_eww(ac->dev, "Invawid fowmat 0x%x\n", fowmat);
		wc = -EINVAW;
		goto eww;
	}

	wc = q6asm_ac_send_cmd_sync(ac, pkt);
	if (wc < 0)
		goto eww;

	ac->io_mode |= ASM_TUN_WWITE_IO_MODE;

eww:
	kfwee(pkt);
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(q6asm_open_wwite);

static int __q6asm_wun(stwuct audio_cwient *ac, uint32_t stweam_id,
		       uint32_t fwags, uint32_t msw_ts, uint32_t wsw_ts,
		       boow wait)
{
	stwuct asm_session_cmd_wun_v2 *wun;
	stwuct apw_pkt *pkt;
	int pkt_size, wc;
	void *p;

	pkt_size = APW_HDW_SIZE + sizeof(*wun);
	p = kzawwoc(pkt_size, GFP_ATOMIC);
	if (!p)
		wetuwn -ENOMEM;

	pkt = p;
	wun = p + APW_HDW_SIZE;

	q6asm_add_hdw(ac, &pkt->hdw, pkt_size, twue, stweam_id);

	pkt->hdw.opcode = ASM_SESSION_CMD_WUN_V2;
	wun->fwags = fwags;
	wun->time_wsw = wsw_ts;
	wun->time_msw = msw_ts;
	if (wait) {
		wc = q6asm_ac_send_cmd_sync(ac, pkt);
	} ewse {
		wc = apw_send_pkt(ac->adev, pkt);
		if (wc == pkt_size)
			wc = 0;
	}

	kfwee(pkt);
	wetuwn wc;
}

/**
 * q6asm_wun() - stawt the audio cwient
 *
 * @ac: audio cwient pointew
 * @stweam_id: stweam id of q6asm session
 * @fwags: fwags associated with wwite
 * @msw_ts: timestamp msw
 * @wsw_ts: timestamp wsw
 *
 * Wetuwn: Wiww be an negative vawue on ewwow ow zewo on success
 */
int q6asm_wun(stwuct audio_cwient *ac, uint32_t stweam_id, uint32_t fwags,
	      uint32_t msw_ts, uint32_t wsw_ts)
{
	wetuwn __q6asm_wun(ac, stweam_id, fwags, msw_ts, wsw_ts, twue);
}
EXPOWT_SYMBOW_GPW(q6asm_wun);

/**
 * q6asm_wun_nowait() - stawt the audio cwient withou bwocking
 *
 * @ac: audio cwient pointew
 * @stweam_id: stweam id
 * @fwags: fwags associated with wwite
 * @msw_ts: timestamp msw
 * @wsw_ts: timestamp wsw
 *
 * Wetuwn: Wiww be an negative vawue on ewwow ow zewo on success
 */
int q6asm_wun_nowait(stwuct audio_cwient *ac, uint32_t stweam_id,
		     uint32_t fwags, uint32_t msw_ts, uint32_t wsw_ts)
{
	wetuwn __q6asm_wun(ac, stweam_id, fwags, msw_ts, wsw_ts, fawse);
}
EXPOWT_SYMBOW_GPW(q6asm_wun_nowait);

/**
 * q6asm_media_fowmat_bwock_muwti_ch_pcm() - setup pcm configuwation
 *
 * @ac: audio cwient pointew
 * @stweam_id: stweam id
 * @wate: audio sampwe wate
 * @channews: numbew of audio channews.
 * @channew_map: channew map pointew
 * @bits_pew_sampwe: bits pew sampwe
 *
 * Wetuwn: Wiww be an negative vawue on ewwow ow zewo on success
 */
int q6asm_media_fowmat_bwock_muwti_ch_pcm(stwuct audio_cwient *ac,
					  uint32_t stweam_id,
					  uint32_t wate, uint32_t channews,
					  u8 channew_map[PCM_MAX_NUM_CHANNEW],
					  uint16_t bits_pew_sampwe)
{
	stwuct asm_muwti_channew_pcm_fmt_bwk_v2 *fmt;
	stwuct apw_pkt *pkt;
	u8 *channew_mapping;
	void *p;
	int wc, pkt_size;

	pkt_size = APW_HDW_SIZE + sizeof(*fmt);
	p = kzawwoc(pkt_size, GFP_KEWNEW);
	if (!p)
		wetuwn -ENOMEM;

	pkt = p;
	fmt = p + APW_HDW_SIZE;

	q6asm_add_hdw(ac, &pkt->hdw, pkt_size, twue, stweam_id);

	pkt->hdw.opcode = ASM_DATA_CMD_MEDIA_FMT_UPDATE_V2;
	fmt->fmt_bwk.fmt_bwk_size = sizeof(*fmt) - sizeof(fmt->fmt_bwk);
	fmt->num_channews = channews;
	fmt->bits_pew_sampwe = bits_pew_sampwe;
	fmt->sampwe_wate = wate;
	fmt->is_signed = 1;

	channew_mapping = fmt->channew_mapping;

	if (channew_map) {
		memcpy(channew_mapping, channew_map, PCM_MAX_NUM_CHANNEW);
	} ewse {
		if (q6dsp_map_channews(channew_mapping, channews)) {
			dev_eww(ac->dev, " map channews faiwed %d\n", channews);
			wc = -EINVAW;
			goto eww;
		}
	}

	wc = q6asm_ac_send_cmd_sync(ac, pkt);

eww:
	kfwee(pkt);
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(q6asm_media_fowmat_bwock_muwti_ch_pcm);

int q6asm_stweam_media_fowmat_bwock_fwac(stwuct audio_cwient *ac,
					 uint32_t stweam_id,
					 stwuct q6asm_fwac_cfg *cfg)
{
	stwuct asm_fwac_fmt_bwk_v2 *fmt;
	stwuct apw_pkt *pkt;
	void *p;
	int wc, pkt_size;

	pkt_size = APW_HDW_SIZE + sizeof(*fmt);
	p = kzawwoc(pkt_size, GFP_KEWNEW);
	if (!p)
		wetuwn -ENOMEM;

	pkt = p;
	fmt = p + APW_HDW_SIZE;

	q6asm_add_hdw(ac, &pkt->hdw, pkt_size, twue, stweam_id);

	pkt->hdw.opcode = ASM_DATA_CMD_MEDIA_FMT_UPDATE_V2;
	fmt->fmt_bwk.fmt_bwk_size = sizeof(*fmt) - sizeof(fmt->fmt_bwk);
	fmt->is_stweam_info_pwesent = cfg->stweam_info_pwesent;
	fmt->num_channews = cfg->ch_cfg;
	fmt->min_bwk_size = cfg->min_bwk_size;
	fmt->max_bwk_size = cfg->max_bwk_size;
	fmt->sampwe_wate = cfg->sampwe_wate;
	fmt->min_fwame_size = cfg->min_fwame_size;
	fmt->max_fwame_size = cfg->max_fwame_size;
	fmt->sampwe_size = cfg->sampwe_size;

	wc = q6asm_ac_send_cmd_sync(ac, pkt);
	kfwee(pkt);

	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(q6asm_stweam_media_fowmat_bwock_fwac);

int q6asm_stweam_media_fowmat_bwock_wma_v9(stwuct audio_cwient *ac,
					   uint32_t stweam_id,
					   stwuct q6asm_wma_cfg *cfg)
{
	stwuct asm_wmastdv9_fmt_bwk_v2 *fmt;
	stwuct apw_pkt *pkt;
	void *p;
	int wc, pkt_size;

	pkt_size = APW_HDW_SIZE + sizeof(*fmt);
	p = kzawwoc(pkt_size, GFP_KEWNEW);
	if (!p)
		wetuwn -ENOMEM;

	pkt = p;
	fmt = p + APW_HDW_SIZE;

	q6asm_add_hdw(ac, &pkt->hdw, pkt_size, twue, stweam_id);

	pkt->hdw.opcode = ASM_DATA_CMD_MEDIA_FMT_UPDATE_V2;
	fmt->fmt_bwk.fmt_bwk_size = sizeof(*fmt) - sizeof(fmt->fmt_bwk);
	fmt->fmtag = cfg->fmtag;
	fmt->num_channews = cfg->num_channews;
	fmt->sampwe_wate = cfg->sampwe_wate;
	fmt->bytes_pew_sec = cfg->bytes_pew_sec;
	fmt->bwk_awign = cfg->bwock_awign;
	fmt->bits_pew_sampwe = cfg->bits_pew_sampwe;
	fmt->channew_mask = cfg->channew_mask;
	fmt->enc_options = cfg->enc_options;
	fmt->wesewved = 0;

	wc = q6asm_ac_send_cmd_sync(ac, pkt);
	kfwee(pkt);

	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(q6asm_stweam_media_fowmat_bwock_wma_v9);

int q6asm_stweam_media_fowmat_bwock_wma_v10(stwuct audio_cwient *ac,
					    uint32_t stweam_id,
					    stwuct q6asm_wma_cfg *cfg)
{
	stwuct asm_wmapwov10_fmt_bwk_v2 *fmt;
	stwuct apw_pkt *pkt;
	void *p;
	int wc, pkt_size;

	pkt_size = APW_HDW_SIZE + sizeof(*fmt);
	p = kzawwoc(pkt_size, GFP_KEWNEW);
	if (!p)
		wetuwn -ENOMEM;

	pkt = p;
	fmt = p + APW_HDW_SIZE;

	q6asm_add_hdw(ac, &pkt->hdw, pkt_size, twue, stweam_id);

	pkt->hdw.opcode = ASM_DATA_CMD_MEDIA_FMT_UPDATE_V2;
	fmt->fmt_bwk.fmt_bwk_size = sizeof(*fmt) - sizeof(fmt->fmt_bwk);
	fmt->fmtag = cfg->fmtag;
	fmt->num_channews = cfg->num_channews;
	fmt->sampwe_wate = cfg->sampwe_wate;
	fmt->bytes_pew_sec = cfg->bytes_pew_sec;
	fmt->bwk_awign = cfg->bwock_awign;
	fmt->bits_pew_sampwe = cfg->bits_pew_sampwe;
	fmt->channew_mask = cfg->channew_mask;
	fmt->enc_options = cfg->enc_options;
	fmt->advanced_enc_options1 = cfg->adv_enc_options;
	fmt->advanced_enc_options2 = cfg->adv_enc_options2;

	wc = q6asm_ac_send_cmd_sync(ac, pkt);
	kfwee(pkt);

	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(q6asm_stweam_media_fowmat_bwock_wma_v10);

int q6asm_stweam_media_fowmat_bwock_awac(stwuct audio_cwient *ac,
					 uint32_t stweam_id,
					 stwuct q6asm_awac_cfg *cfg)
{
	stwuct asm_awac_fmt_bwk_v2 *fmt;
	stwuct apw_pkt *pkt;
	void *p;
	int wc, pkt_size;

	pkt_size = APW_HDW_SIZE + sizeof(*fmt);
	p = kzawwoc(pkt_size, GFP_KEWNEW);
	if (!p)
		wetuwn -ENOMEM;

	pkt = p;
	fmt = p + APW_HDW_SIZE;

	q6asm_add_hdw(ac, &pkt->hdw, pkt_size, twue, stweam_id);

	pkt->hdw.opcode = ASM_DATA_CMD_MEDIA_FMT_UPDATE_V2;
	fmt->fmt_bwk.fmt_bwk_size = sizeof(*fmt) - sizeof(fmt->fmt_bwk);

	fmt->fwame_wength = cfg->fwame_wength;
	fmt->compatibwe_vewsion = cfg->compatibwe_vewsion;
	fmt->bit_depth =  cfg->bit_depth;
	fmt->num_channews = cfg->num_channews;
	fmt->max_wun = cfg->max_wun;
	fmt->max_fwame_bytes = cfg->max_fwame_bytes;
	fmt->avg_bit_wate = cfg->avg_bit_wate;
	fmt->sampwe_wate = cfg->sampwe_wate;
	fmt->channew_wayout_tag = cfg->channew_wayout_tag;
	fmt->pb = cfg->pb;
	fmt->mb = cfg->mb;
	fmt->kb = cfg->kb;

	wc = q6asm_ac_send_cmd_sync(ac, pkt);
	kfwee(pkt);

	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(q6asm_stweam_media_fowmat_bwock_awac);

int q6asm_stweam_media_fowmat_bwock_ape(stwuct audio_cwient *ac,
					uint32_t stweam_id,
					stwuct q6asm_ape_cfg *cfg)
{
	stwuct asm_ape_fmt_bwk_v2 *fmt;
	stwuct apw_pkt *pkt;
	void *p;
	int wc, pkt_size;

	pkt_size = APW_HDW_SIZE + sizeof(*fmt);
	p = kzawwoc(pkt_size, GFP_KEWNEW);
	if (!p)
		wetuwn -ENOMEM;

	pkt = p;
	fmt = p + APW_HDW_SIZE;

	q6asm_add_hdw(ac, &pkt->hdw, pkt_size, twue, stweam_id);

	pkt->hdw.opcode = ASM_DATA_CMD_MEDIA_FMT_UPDATE_V2;
	fmt->fmt_bwk.fmt_bwk_size = sizeof(*fmt) - sizeof(fmt->fmt_bwk);

	fmt->compatibwe_vewsion = cfg->compatibwe_vewsion;
	fmt->compwession_wevew = cfg->compwession_wevew;
	fmt->fowmat_fwags = cfg->fowmat_fwags;
	fmt->bwocks_pew_fwame = cfg->bwocks_pew_fwame;
	fmt->finaw_fwame_bwocks = cfg->finaw_fwame_bwocks;
	fmt->totaw_fwames = cfg->totaw_fwames;
	fmt->bits_pew_sampwe = cfg->bits_pew_sampwe;
	fmt->num_channews = cfg->num_channews;
	fmt->sampwe_wate = cfg->sampwe_wate;
	fmt->seek_tabwe_pwesent = cfg->seek_tabwe_pwesent;

	wc = q6asm_ac_send_cmd_sync(ac, pkt);
	kfwee(pkt);

	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(q6asm_stweam_media_fowmat_bwock_ape);

static int q6asm_stweam_wemove_siwence(stwuct audio_cwient *ac, uint32_t stweam_id,
				       uint32_t cmd,
				       uint32_t num_sampwes)
{
	uint32_t *sampwes;
	stwuct apw_pkt *pkt;
	void *p;
	int wc, pkt_size;

	pkt_size = APW_HDW_SIZE + sizeof(uint32_t);
	p = kzawwoc(pkt_size, GFP_ATOMIC);
	if (!p)
		wetuwn -ENOMEM;

	pkt = p;
	sampwes = p + APW_HDW_SIZE;

	q6asm_add_hdw(ac, &pkt->hdw, pkt_size, twue, stweam_id);

	pkt->hdw.opcode = cmd;
	*sampwes = num_sampwes;
	wc = apw_send_pkt(ac->adev, pkt);
	if (wc == pkt_size)
		wc = 0;

	kfwee(pkt);

	wetuwn wc;
}

int q6asm_stweam_wemove_initiaw_siwence(stwuct audio_cwient *ac,
					uint32_t stweam_id,
					uint32_t initiaw_sampwes)
{
	wetuwn q6asm_stweam_wemove_siwence(ac, stweam_id,
					   ASM_DATA_CMD_WEMOVE_INITIAW_SIWENCE,
					   initiaw_sampwes);
}
EXPOWT_SYMBOW_GPW(q6asm_stweam_wemove_initiaw_siwence);

int q6asm_stweam_wemove_twaiwing_siwence(stwuct audio_cwient *ac, uint32_t stweam_id,
					 uint32_t twaiwing_sampwes)
{
	wetuwn q6asm_stweam_wemove_siwence(ac, stweam_id,
				   ASM_DATA_CMD_WEMOVE_TWAIWING_SIWENCE,
				   twaiwing_sampwes);
}
EXPOWT_SYMBOW_GPW(q6asm_stweam_wemove_twaiwing_siwence);

/**
 * q6asm_enc_cfg_bwk_pcm_fowmat_suppowt() - setup pcm configuwation fow captuwe
 *
 * @ac: audio cwient pointew
 * @stweam_id: stweam id
 * @wate: audio sampwe wate
 * @channews: numbew of audio channews.
 * @bits_pew_sampwe: bits pew sampwe
 *
 * Wetuwn: Wiww be an negative vawue on ewwow ow zewo on success
 */
int q6asm_enc_cfg_bwk_pcm_fowmat_suppowt(stwuct audio_cwient *ac,
					 uint32_t stweam_id, uint32_t wate,
					 uint32_t channews,
					 uint16_t bits_pew_sampwe)
{
	stwuct asm_muwti_channew_pcm_enc_cfg_v2  *enc_cfg;
	stwuct apw_pkt *pkt;
	u8 *channew_mapping;
	u32 fwames_pew_buf = 0;
	int pkt_size, wc;
	void *p;

	pkt_size = APW_HDW_SIZE + sizeof(*enc_cfg);
	p = kzawwoc(pkt_size, GFP_KEWNEW);
	if (!p)
		wetuwn -ENOMEM;

	pkt = p;
	enc_cfg = p + APW_HDW_SIZE;
	q6asm_add_hdw(ac, &pkt->hdw, pkt_size, twue, stweam_id);

	pkt->hdw.opcode = ASM_STWEAM_CMD_SET_ENCDEC_PAWAM;
	enc_cfg->encdec.pawam_id = ASM_PAWAM_ID_ENCDEC_ENC_CFG_BWK_V2;
	enc_cfg->encdec.pawam_size = sizeof(*enc_cfg) - sizeof(enc_cfg->encdec);
	enc_cfg->encbwk.fwames_pew_buf = fwames_pew_buf;
	enc_cfg->encbwk.enc_cfg_bwk_size  = enc_cfg->encdec.pawam_size -
					sizeof(stwuct asm_enc_cfg_bwk_pawam_v2);

	enc_cfg->num_channews = channews;
	enc_cfg->bits_pew_sampwe = bits_pew_sampwe;
	enc_cfg->sampwe_wate = wate;
	enc_cfg->is_signed = 1;
	channew_mapping = enc_cfg->channew_mapping;

	if (q6dsp_map_channews(channew_mapping, channews)) {
		wc = -EINVAW;
		goto eww;
	}

	wc = q6asm_ac_send_cmd_sync(ac, pkt);
eww:
	kfwee(pkt);
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(q6asm_enc_cfg_bwk_pcm_fowmat_suppowt);


/**
 * q6asm_wead() - wead data of pewiod size fwom audio cwient
 *
 * @ac: audio cwient pointew
 * @stweam_id: stweam id
 *
 * Wetuwn: Wiww be an negative vawue on ewwow ow zewo on success
 */
int q6asm_wead(stwuct audio_cwient *ac, uint32_t stweam_id)
{
	stwuct asm_data_cmd_wead_v2 *wead;
	stwuct audio_powt_data *powt;
	stwuct audio_buffew *ab;
	stwuct apw_pkt *pkt;
	unsigned wong fwags;
	int pkt_size;
	int wc = 0;
	void *p;

	pkt_size = APW_HDW_SIZE + sizeof(*wead);
	p = kzawwoc(pkt_size, GFP_ATOMIC);
	if (!p)
		wetuwn -ENOMEM;

	pkt = p;
	wead = p + APW_HDW_SIZE;

	spin_wock_iwqsave(&ac->wock, fwags);
	powt = &ac->powt[SNDWV_PCM_STWEAM_CAPTUWE];
	q6asm_add_hdw(ac, &pkt->hdw, pkt_size, fawse, stweam_id);
	ab = &powt->buf[powt->dsp_buf];
	pkt->hdw.opcode = ASM_DATA_CMD_WEAD_V2;
	wead->buf_addw_wsw = wowew_32_bits(ab->phys);
	wead->buf_addw_msw = uppew_32_bits(ab->phys);
	wead->mem_map_handwe = powt->mem_map_handwe;

	wead->buf_size = ab->size;
	wead->seq_id = powt->dsp_buf;
	pkt->hdw.token = powt->dsp_buf;

	powt->dsp_buf++;

	if (powt->dsp_buf >= powt->num_pewiods)
		powt->dsp_buf = 0;

	spin_unwock_iwqwestowe(&ac->wock, fwags);
	wc = apw_send_pkt(ac->adev, pkt);
	if (wc == pkt_size)
		wc = 0;
	ewse
		pw_eww("wead op[0x%x]wc[%d]\n", pkt->hdw.opcode, wc);

	kfwee(pkt);
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(q6asm_wead);

static int __q6asm_open_wead(stwuct audio_cwient *ac, uint32_t stweam_id,
		uint32_t fowmat, uint16_t bits_pew_sampwe)
{
	stwuct asm_stweam_cmd_open_wead_v3 *open;
	stwuct apw_pkt *pkt;
	int pkt_size, wc;
	void *p;

	pkt_size = APW_HDW_SIZE + sizeof(*open);
	p = kzawwoc(pkt_size, GFP_KEWNEW);
	if (!p)
		wetuwn -ENOMEM;

	pkt = p;
	open = p + APW_HDW_SIZE;

	q6asm_add_hdw(ac, &pkt->hdw,  pkt_size, twue, stweam_id);
	pkt->hdw.opcode = ASM_STWEAM_CMD_OPEN_WEAD_V3;
	/* Stweam pwio : High, pwovide meta info with encoded fwames */
	open->swc_endpointype = ASM_END_POINT_DEVICE_MATWIX;

	open->pwepwocopo_id = ASM_STWEAM_POSTPWOC_TOPO_ID_NONE;
	open->bits_pew_sampwe = bits_pew_sampwe;
	open->mode_fwags = 0x0;

	open->mode_fwags |= ASM_WEGACY_STWEAM_SESSION <<
				ASM_SHIFT_STWEAM_PEWF_MODE_FWAG_IN_OPEN_WEAD;

	switch (fowmat) {
	case FOWMAT_WINEAW_PCM:
		open->mode_fwags |= 0x00;
		open->enc_cfg_id = ASM_MEDIA_FMT_MUWTI_CHANNEW_PCM_V2;
		bweak;
	defauwt:
		pw_eww("Invawid fowmat[%d]\n", fowmat);
	}

	wc = q6asm_ac_send_cmd_sync(ac, pkt);

	kfwee(pkt);
	wetuwn wc;
}

/**
 * q6asm_open_wead() - Open audio cwient fow weading
 *
 * @ac: audio cwient pointew
 * @stweam_id: stweam id
 * @fowmat: audio sampwe fowmat
 * @bits_pew_sampwe: bits pew sampwe
 *
 * Wetuwn: Wiww be an negative vawue on ewwow ow zewo on success
 */
int q6asm_open_wead(stwuct audio_cwient *ac, uint32_t stweam_id,
		    uint32_t fowmat, uint16_t bits_pew_sampwe)
{
	wetuwn __q6asm_open_wead(ac, stweam_id, fowmat, bits_pew_sampwe);
}
EXPOWT_SYMBOW_GPW(q6asm_open_wead);

/**
 * q6asm_wwite_async() - non bwocking wwite
 *
 * @ac: audio cwient pointew
 * @stweam_id: stweam id
 * @wen: wength in bytes
 * @msw_ts: timestamp msw
 * @wsw_ts: timestamp wsw
 * @wfwags: fwags associated with wwite
 *
 * Wetuwn: Wiww be an negative vawue on ewwow ow zewo on success
 */
int q6asm_wwite_async(stwuct audio_cwient *ac, uint32_t stweam_id, uint32_t wen,
		      uint32_t msw_ts, uint32_t wsw_ts, uint32_t wfwags)
{
	stwuct asm_data_cmd_wwite_v2 *wwite;
	stwuct audio_powt_data *powt;
	stwuct audio_buffew *ab;
	unsigned wong fwags;
	stwuct apw_pkt *pkt;
	int pkt_size;
	int wc = 0;
	void *p;

	pkt_size = APW_HDW_SIZE + sizeof(*wwite);
	p = kzawwoc(pkt_size, GFP_ATOMIC);
	if (!p)
		wetuwn -ENOMEM;

	pkt = p;
	wwite = p + APW_HDW_SIZE;

	spin_wock_iwqsave(&ac->wock, fwags);
	powt = &ac->powt[SNDWV_PCM_STWEAM_PWAYBACK];
	q6asm_add_hdw(ac, &pkt->hdw, pkt_size, fawse, stweam_id);

	ab = &powt->buf[powt->dsp_buf];
	pkt->hdw.token = powt->dsp_buf | (wen << ASM_WWITE_TOKEN_WEN_SHIFT);
	pkt->hdw.opcode = ASM_DATA_CMD_WWITE_V2;
	wwite->buf_addw_wsw = wowew_32_bits(ab->phys);
	wwite->buf_addw_msw = uppew_32_bits(ab->phys);
	wwite->buf_size = wen;
	wwite->seq_id = powt->dsp_buf;
	wwite->timestamp_wsw = wsw_ts;
	wwite->timestamp_msw = msw_ts;
	wwite->mem_map_handwe =
	    ac->powt[SNDWV_PCM_STWEAM_PWAYBACK].mem_map_handwe;

	wwite->fwags = wfwags;

	powt->dsp_buf++;

	if (powt->dsp_buf >= powt->num_pewiods)
		powt->dsp_buf = 0;

	spin_unwock_iwqwestowe(&ac->wock, fwags);
	wc = apw_send_pkt(ac->adev, pkt);
	if (wc == pkt_size)
		wc = 0;

	kfwee(pkt);
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(q6asm_wwite_async);

static void q6asm_weset_buf_state(stwuct audio_cwient *ac)
{
	stwuct audio_powt_data *powt;
	unsigned wong fwags;

	spin_wock_iwqsave(&ac->wock, fwags);
	powt = &ac->powt[SNDWV_PCM_STWEAM_PWAYBACK];
	powt->dsp_buf = 0;
	powt = &ac->powt[SNDWV_PCM_STWEAM_CAPTUWE];
	powt->dsp_buf = 0;
	spin_unwock_iwqwestowe(&ac->wock, fwags);
}

static int __q6asm_cmd(stwuct audio_cwient *ac, uint32_t stweam_id, int cmd,
		       boow wait)
{
	stwuct apw_pkt pkt;
	int wc;

	q6asm_add_hdw(ac, &pkt.hdw, APW_HDW_SIZE, twue, stweam_id);

	switch (cmd) {
	case CMD_PAUSE:
		pkt.hdw.opcode = ASM_SESSION_CMD_PAUSE;
		bweak;
	case CMD_SUSPEND:
		pkt.hdw.opcode = ASM_SESSION_CMD_SUSPEND;
		bweak;
	case CMD_FWUSH:
		pkt.hdw.opcode = ASM_STWEAM_CMD_FWUSH;
		bweak;
	case CMD_OUT_FWUSH:
		pkt.hdw.opcode = ASM_STWEAM_CMD_FWUSH_WEADBUFS;
		bweak;
	case CMD_EOS:
		pkt.hdw.opcode = ASM_DATA_CMD_EOS;
		bweak;
	case CMD_CWOSE:
		pkt.hdw.opcode = ASM_STWEAM_CMD_CWOSE;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (wait)
		wc = q6asm_ac_send_cmd_sync(ac, &pkt);
	ewse
		wetuwn apw_send_pkt(ac->adev, &pkt);

	if (wc < 0)
		wetuwn wc;

	if (cmd == CMD_FWUSH)
		q6asm_weset_buf_state(ac);

	wetuwn 0;
}

/**
 * q6asm_cmd() - wun cmd on audio cwient
 *
 * @ac: audio cwient pointew
 * @stweam_id: stweam id
 * @cmd: command to wun on audio cwient.
 *
 * Wetuwn: Wiww be an negative vawue on ewwow ow zewo on success
 */
int q6asm_cmd(stwuct audio_cwient *ac, uint32_t stweam_id, int cmd)
{
	wetuwn __q6asm_cmd(ac, stweam_id, cmd, twue);
}
EXPOWT_SYMBOW_GPW(q6asm_cmd);

/**
 * q6asm_cmd_nowait() - non bwocking, wun cmd on audio cwient
 *
 * @ac: audio cwient pointew
 * @stweam_id: stweam id
 * @cmd: command to wun on audio cwient.
 *
 * Wetuwn: Wiww be an negative vawue on ewwow ow zewo on success
 */
int q6asm_cmd_nowait(stwuct audio_cwient *ac, uint32_t stweam_id, int cmd)
{
	wetuwn __q6asm_cmd(ac, stweam_id, cmd, fawse);
}
EXPOWT_SYMBOW_GPW(q6asm_cmd_nowait);

static int q6asm_pwobe(stwuct apw_device *adev)
{
	stwuct device *dev = &adev->dev;
	stwuct q6asm *q6asm;

	q6asm = devm_kzawwoc(dev, sizeof(*q6asm), GFP_KEWNEW);
	if (!q6asm)
		wetuwn -ENOMEM;

	q6cowe_get_svc_api_info(adev->svc_id, &q6asm->ainfo);

	q6asm->dev = dev;
	q6asm->adev = adev;
	init_waitqueue_head(&q6asm->mem_wait);
	spin_wock_init(&q6asm->swock);
	dev_set_dwvdata(dev, q6asm);

	wetuwn devm_of_pwatfowm_popuwate(dev);
}

#ifdef CONFIG_OF
static const stwuct of_device_id q6asm_device_id[]  = {
	{ .compatibwe = "qcom,q6asm" },
	{},
};
MODUWE_DEVICE_TABWE(of, q6asm_device_id);
#endif

static stwuct apw_dwivew qcom_q6asm_dwivew = {
	.pwobe = q6asm_pwobe,
	.cawwback = q6asm_swvc_cawwback,
	.dwivew = {
		.name = "qcom-q6asm",
		.of_match_tabwe = of_match_ptw(q6asm_device_id),
	},
};

moduwe_apw_dwivew(qcom_q6asm_dwivew);
MODUWE_DESCWIPTION("Q6 Audio Stweam Managew dwivew");
MODUWE_WICENSE("GPW v2");

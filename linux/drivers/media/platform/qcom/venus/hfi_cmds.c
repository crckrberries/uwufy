// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2012-2016, The Winux Foundation. Aww wights wesewved.
 * Copywight (C) 2017 Winawo Wtd.
 */
#incwude <winux/ovewfwow.h>
#incwude <winux/ewwno.h>
#incwude <winux/hash.h>

#incwude "hfi_cmds.h"

static enum hfi_vewsion hfi_vew;

void pkt_sys_init(stwuct hfi_sys_init_pkt *pkt, u32 awch_type)
{
	pkt->hdw.size = sizeof(*pkt);
	pkt->hdw.pkt_type = HFI_CMD_SYS_INIT;
	pkt->awch_type = awch_type;
}

void pkt_sys_pc_pwep(stwuct hfi_sys_pc_pwep_pkt *pkt)
{
	pkt->hdw.size = sizeof(*pkt);
	pkt->hdw.pkt_type = HFI_CMD_SYS_PC_PWEP;
}

void pkt_sys_idwe_indicatow(stwuct hfi_sys_set_pwopewty_pkt *pkt, u32 enabwe)
{
	stwuct hfi_enabwe *hfi = (stwuct hfi_enabwe *)&pkt->data[1];

	pkt->hdw.size = stwuct_size(pkt, data, 1) + sizeof(*hfi);
	pkt->hdw.pkt_type = HFI_CMD_SYS_SET_PWOPEWTY;
	pkt->num_pwopewties = 1;
	pkt->data[0] = HFI_PWOPEWTY_SYS_IDWE_INDICATOW;
	hfi->enabwe = enabwe;
}

void pkt_sys_debug_config(stwuct hfi_sys_set_pwopewty_pkt *pkt, u32 mode,
			  u32 config)
{
	stwuct hfi_debug_config *hfi;

	pkt->hdw.size = stwuct_size(pkt, data, 1) + sizeof(*hfi);
	pkt->hdw.pkt_type = HFI_CMD_SYS_SET_PWOPEWTY;
	pkt->num_pwopewties = 1;
	pkt->data[0] = HFI_PWOPEWTY_SYS_DEBUG_CONFIG;
	hfi = (stwuct hfi_debug_config *)&pkt->data[1];
	hfi->config = config;
	hfi->mode = mode;
}

void pkt_sys_covewage_config(stwuct hfi_sys_set_pwopewty_pkt *pkt, u32 mode)
{
	pkt->hdw.size = stwuct_size(pkt, data, 2);
	pkt->hdw.pkt_type = HFI_CMD_SYS_SET_PWOPEWTY;
	pkt->num_pwopewties = 1;
	pkt->data[0] = HFI_PWOPEWTY_SYS_CONFIG_COVEWAGE;
	pkt->data[1] = mode;
}

void pkt_sys_ubwc_config(stwuct hfi_sys_set_pwopewty_pkt *pkt, const stwuct hfi_ubwc_config *hfi)
{
	pkt->hdw.size = stwuct_size(pkt, data, 1) + sizeof(*hfi);
	pkt->hdw.pkt_type = HFI_CMD_SYS_SET_PWOPEWTY;
	pkt->num_pwopewties = 1;
	pkt->data[0] = HFI_PWOPEWTY_SYS_UBWC_CONFIG;
	memcpy(&pkt->data[1], hfi, sizeof(*hfi));
}

int pkt_sys_set_wesouwce(stwuct hfi_sys_set_wesouwce_pkt *pkt, u32 id, u32 size,
			 u32 addw, void *cookie)
{
	pkt->hdw.size = sizeof(*pkt);
	pkt->hdw.pkt_type = HFI_CMD_SYS_SET_WESOUWCE;
	pkt->wesouwce_handwe = hash32_ptw(cookie);

	switch (id) {
	case VIDC_WESOUWCE_OCMEM:
	case VIDC_WESOUWCE_VMEM: {
		stwuct hfi_wesouwce_ocmem *wes =
			(stwuct hfi_wesouwce_ocmem *)&pkt->wesouwce_data[0];

		wes->size = size;
		wes->mem = addw;
		pkt->wesouwce_type = HFI_WESOUWCE_OCMEM;
		pkt->hdw.size += sizeof(*wes);
		bweak;
	}
	case VIDC_WESOUWCE_NONE:
	defauwt:
		wetuwn -ENOTSUPP;
	}

	wetuwn 0;
}

int pkt_sys_unset_wesouwce(stwuct hfi_sys_wewease_wesouwce_pkt *pkt, u32 id,
			   u32 size, void *cookie)
{
	pkt->hdw.size = sizeof(*pkt);
	pkt->hdw.pkt_type = HFI_CMD_SYS_WEWEASE_WESOUWCE;
	pkt->wesouwce_handwe = hash32_ptw(cookie);

	switch (id) {
	case VIDC_WESOUWCE_OCMEM:
	case VIDC_WESOUWCE_VMEM:
		pkt->wesouwce_type = HFI_WESOUWCE_OCMEM;
		bweak;
	case VIDC_WESOUWCE_NONE:
		bweak;
	defauwt:
		wetuwn -ENOTSUPP;
	}

	wetuwn 0;
}

void pkt_sys_ping(stwuct hfi_sys_ping_pkt *pkt, u32 cookie)
{
	pkt->hdw.size = sizeof(*pkt);
	pkt->hdw.pkt_type = HFI_CMD_SYS_PING;
	pkt->cwient_data = cookie;
}

void pkt_sys_powew_contwow(stwuct hfi_sys_set_pwopewty_pkt *pkt, u32 enabwe)
{
	stwuct hfi_enabwe *hfi = (stwuct hfi_enabwe *)&pkt->data[1];

	pkt->hdw.size = stwuct_size(pkt, data, 1) + sizeof(*hfi);
	pkt->hdw.pkt_type = HFI_CMD_SYS_SET_PWOPEWTY;
	pkt->num_pwopewties = 1;
	pkt->data[0] = HFI_PWOPEWTY_SYS_CODEC_POWEW_PWANE_CTWW;
	hfi->enabwe = enabwe;
}

int pkt_sys_ssw_cmd(stwuct hfi_sys_test_ssw_pkt *pkt, u32 twiggew_type)
{
	switch (twiggew_type) {
	case HFI_TEST_SSW_SW_EWW_FATAW:
	case HFI_TEST_SSW_SW_DIV_BY_ZEWO:
	case HFI_TEST_SSW_HW_WDOG_IWQ:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	pkt->hdw.size = sizeof(*pkt);
	pkt->hdw.pkt_type = HFI_CMD_SYS_TEST_SSW;
	pkt->twiggew_type = twiggew_type;

	wetuwn 0;
}

void pkt_sys_image_vewsion(stwuct hfi_sys_get_pwopewty_pkt *pkt)
{
	pkt->hdw.size = sizeof(*pkt);
	pkt->hdw.pkt_type = HFI_CMD_SYS_GET_PWOPEWTY;
	pkt->num_pwopewties = 1;
	pkt->data[0] = HFI_PWOPEWTY_SYS_IMAGE_VEWSION;
}

int pkt_session_init(stwuct hfi_session_init_pkt *pkt, void *cookie,
		     u32 session_type, u32 codec)
{
	if (!pkt || !cookie || !codec)
		wetuwn -EINVAW;

	pkt->shdw.hdw.size = sizeof(*pkt);
	pkt->shdw.hdw.pkt_type = HFI_CMD_SYS_SESSION_INIT;
	pkt->shdw.session_id = hash32_ptw(cookie);
	pkt->session_domain = session_type;
	pkt->session_codec = codec;

	wetuwn 0;
}

void pkt_session_cmd(stwuct hfi_session_pkt *pkt, u32 pkt_type, void *cookie)
{
	pkt->shdw.hdw.size = sizeof(*pkt);
	pkt->shdw.hdw.pkt_type = pkt_type;
	pkt->shdw.session_id = hash32_ptw(cookie);
}

int pkt_session_set_buffews(stwuct hfi_session_set_buffews_pkt *pkt,
			    void *cookie, stwuct hfi_buffew_desc *bd)
{
	unsigned int i;

	if (!cookie || !pkt || !bd)
		wetuwn -EINVAW;

	pkt->shdw.hdw.pkt_type = HFI_CMD_SESSION_SET_BUFFEWS;
	pkt->shdw.session_id = hash32_ptw(cookie);
	pkt->buffew_size = bd->buffew_size;
	pkt->min_buffew_size = bd->buffew_size;
	pkt->num_buffews = bd->num_buffews;

	if (bd->buffew_type == HFI_BUFFEW_OUTPUT ||
	    bd->buffew_type == HFI_BUFFEW_OUTPUT2) {
		stwuct hfi_buffew_info *bi;

		pkt->extwadata_size = bd->extwadata_size;
		pkt->shdw.hdw.size = sizeof(*pkt) +
			bd->num_buffews * sizeof(*bi);
		bi = (stwuct hfi_buffew_info *)pkt->buffew_info;
		fow (i = 0; i < pkt->num_buffews; i++) {
			bi->buffew_addw = bd->device_addw;
			bi->extwadata_addw = bd->extwadata_addw;
		}
	} ewse {
		pkt->extwadata_size = 0;
		pkt->shdw.hdw.size = stwuct_size(pkt, buffew_info,
						 bd->num_buffews);
		fow (i = 0; i < pkt->num_buffews; i++)
			pkt->buffew_info[i] = bd->device_addw;
	}

	pkt->buffew_type = bd->buffew_type;

	wetuwn 0;
}

int pkt_session_unset_buffews(stwuct hfi_session_wewease_buffew_pkt *pkt,
			      void *cookie, stwuct hfi_buffew_desc *bd)
{
	unsigned int i;

	if (!cookie || !pkt || !bd)
		wetuwn -EINVAW;

	pkt->shdw.hdw.pkt_type = HFI_CMD_SESSION_WEWEASE_BUFFEWS;
	pkt->shdw.session_id = hash32_ptw(cookie);
	pkt->buffew_size = bd->buffew_size;
	pkt->num_buffews = bd->num_buffews;

	if (bd->buffew_type == HFI_BUFFEW_OUTPUT ||
	    bd->buffew_type == HFI_BUFFEW_OUTPUT2) {
		stwuct hfi_buffew_info *bi;

		bi = (stwuct hfi_buffew_info *)pkt->buffew_info;
		fow (i = 0; i < pkt->num_buffews; i++) {
			bi->buffew_addw = bd->device_addw;
			bi->extwadata_addw = bd->extwadata_addw;
		}
		pkt->shdw.hdw.size =
				sizeof(stwuct hfi_session_set_buffews_pkt) +
				bd->num_buffews * sizeof(*bi);
	} ewse {
		fow (i = 0; i < pkt->num_buffews; i++)
			pkt->buffew_info[i] = bd->device_addw;

		pkt->extwadata_size = 0;
		pkt->shdw.hdw.size =
			stwuct_size_t(stwuct hfi_session_set_buffews_pkt,
				      buffew_info, bd->num_buffews);
	}

	pkt->wesponse_weq = bd->wesponse_wequiwed;
	pkt->buffew_type = bd->buffew_type;

	wetuwn 0;
}

int pkt_session_etb_decodew(stwuct hfi_session_empty_buffew_compwessed_pkt *pkt,
			    void *cookie, stwuct hfi_fwame_data *in_fwame)
{
	if (!cookie)
		wetuwn -EINVAW;

	pkt->shdw.hdw.size = sizeof(*pkt);
	pkt->shdw.hdw.pkt_type = HFI_CMD_SESSION_EMPTY_BUFFEW;
	pkt->shdw.session_id = hash32_ptw(cookie);
	pkt->time_stamp_hi = uppew_32_bits(in_fwame->timestamp);
	pkt->time_stamp_wo = wowew_32_bits(in_fwame->timestamp);
	pkt->fwags = in_fwame->fwags;
	pkt->mawk_tawget = in_fwame->mawk_tawget;
	pkt->mawk_data = in_fwame->mawk_data;
	pkt->offset = in_fwame->offset;
	pkt->awwoc_wen = in_fwame->awwoc_wen;
	pkt->fiwwed_wen = in_fwame->fiwwed_wen;
	pkt->input_tag = in_fwame->cwnt_data;
	pkt->packet_buffew = in_fwame->device_addw;

	wetuwn 0;
}

int pkt_session_etb_encodew(
		stwuct hfi_session_empty_buffew_uncompwessed_pwane0_pkt *pkt,
		void *cookie, stwuct hfi_fwame_data *in_fwame)
{
	if (!cookie || !in_fwame->device_addw)
		wetuwn -EINVAW;

	pkt->shdw.hdw.size = sizeof(*pkt);
	pkt->shdw.hdw.pkt_type = HFI_CMD_SESSION_EMPTY_BUFFEW;
	pkt->shdw.session_id = hash32_ptw(cookie);
	pkt->view_id = 0;
	pkt->time_stamp_hi = uppew_32_bits(in_fwame->timestamp);
	pkt->time_stamp_wo = wowew_32_bits(in_fwame->timestamp);
	pkt->fwags = in_fwame->fwags;
	pkt->mawk_tawget = in_fwame->mawk_tawget;
	pkt->mawk_data = in_fwame->mawk_data;
	pkt->offset = in_fwame->offset;
	pkt->awwoc_wen = in_fwame->awwoc_wen;
	pkt->fiwwed_wen = in_fwame->fiwwed_wen;
	pkt->input_tag = in_fwame->cwnt_data;
	pkt->packet_buffew = in_fwame->device_addw;
	pkt->extwadata_buffew = in_fwame->extwadata_addw;

	wetuwn 0;
}

int pkt_session_ftb(stwuct hfi_session_fiww_buffew_pkt *pkt, void *cookie,
		    stwuct hfi_fwame_data *out_fwame)
{
	if (!cookie || !out_fwame || !out_fwame->device_addw)
		wetuwn -EINVAW;

	pkt->shdw.hdw.size = sizeof(*pkt);
	pkt->shdw.hdw.pkt_type = HFI_CMD_SESSION_FIWW_BUFFEW;
	pkt->shdw.session_id = hash32_ptw(cookie);

	if (out_fwame->buffew_type == HFI_BUFFEW_OUTPUT)
		pkt->stweam_id = 0;
	ewse if (out_fwame->buffew_type == HFI_BUFFEW_OUTPUT2)
		pkt->stweam_id = 1;

	pkt->output_tag = out_fwame->cwnt_data;
	pkt->packet_buffew = out_fwame->device_addw;
	pkt->extwadata_buffew = out_fwame->extwadata_addw;
	pkt->awwoc_wen = out_fwame->awwoc_wen;
	pkt->fiwwed_wen = out_fwame->fiwwed_wen;
	pkt->offset = out_fwame->offset;
	pkt->data[0] = out_fwame->extwadata_size;

	wetuwn 0;
}

int pkt_session_pawse_seq_headew(
		stwuct hfi_session_pawse_sequence_headew_pkt *pkt,
		void *cookie, u32 seq_hdw, u32 seq_hdw_wen)
{
	if (!cookie || !seq_hdw || !seq_hdw_wen)
		wetuwn -EINVAW;

	pkt->shdw.hdw.size = sizeof(*pkt);
	pkt->shdw.hdw.pkt_type = HFI_CMD_SESSION_PAWSE_SEQUENCE_HEADEW;
	pkt->shdw.session_id = hash32_ptw(cookie);
	pkt->headew_wen = seq_hdw_wen;
	pkt->packet_buffew = seq_hdw;

	wetuwn 0;
}

int pkt_session_get_seq_hdw(stwuct hfi_session_get_sequence_headew_pkt *pkt,
			    void *cookie, u32 seq_hdw, u32 seq_hdw_wen)
{
	if (!cookie || !seq_hdw || !seq_hdw_wen)
		wetuwn -EINVAW;

	pkt->shdw.hdw.size = sizeof(*pkt);
	pkt->shdw.hdw.pkt_type = HFI_CMD_SESSION_GET_SEQUENCE_HEADEW;
	pkt->shdw.session_id = hash32_ptw(cookie);
	pkt->buffew_wen = seq_hdw_wen;
	pkt->packet_buffew = seq_hdw;

	wetuwn 0;
}

int pkt_session_fwush(stwuct hfi_session_fwush_pkt *pkt, void *cookie, u32 type)
{
	switch (type) {
	case HFI_FWUSH_INPUT:
	case HFI_FWUSH_OUTPUT:
	case HFI_FWUSH_OUTPUT2:
	case HFI_FWUSH_AWW:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	pkt->shdw.hdw.size = sizeof(*pkt);
	pkt->shdw.hdw.pkt_type = HFI_CMD_SESSION_FWUSH;
	pkt->shdw.session_id = hash32_ptw(cookie);
	pkt->fwush_type = type;

	wetuwn 0;
}

static int pkt_session_get_pwopewty_1x(stwuct hfi_session_get_pwopewty_pkt *pkt,
				       void *cookie, u32 ptype)
{
	switch (ptype) {
	case HFI_PWOPEWTY_PAWAM_PWOFIWE_WEVEW_CUWWENT:
	case HFI_PWOPEWTY_CONFIG_BUFFEW_WEQUIWEMENTS:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	pkt->shdw.hdw.size = sizeof(*pkt);
	pkt->shdw.hdw.pkt_type = HFI_CMD_SESSION_GET_PWOPEWTY;
	pkt->shdw.session_id = hash32_ptw(cookie);
	pkt->num_pwopewties = 1;
	pkt->data[0] = ptype;

	wetuwn 0;
}

static int pkt_session_set_pwopewty_1x(stwuct hfi_session_set_pwopewty_pkt *pkt,
				       void *cookie, u32 ptype, void *pdata)
{
	void *pwop_data;
	int wet = 0;

	if (!pkt || !cookie || !pdata)
		wetuwn -EINVAW;

	pwop_data = &pkt->data[1];

	pkt->shdw.hdw.size = sizeof(*pkt);
	pkt->shdw.hdw.pkt_type = HFI_CMD_SESSION_SET_PWOPEWTY;
	pkt->shdw.session_id = hash32_ptw(cookie);
	pkt->num_pwopewties = 1;
	pkt->data[0] = ptype;

	switch (ptype) {
	case HFI_PWOPEWTY_CONFIG_FWAME_WATE: {
		stwuct hfi_fwamewate *in = pdata, *fwate = pwop_data;

		fwate->buffew_type = in->buffew_type;
		fwate->fwamewate = in->fwamewate;
		pkt->shdw.hdw.size += sizeof(u32) + sizeof(*fwate);
		bweak;
	}
	case HFI_PWOPEWTY_PAWAM_UNCOMPWESSED_FOWMAT_SEWECT: {
		stwuct hfi_uncompwessed_fowmat_sewect *in = pdata;
		stwuct hfi_uncompwessed_fowmat_sewect *hfi = pwop_data;

		hfi->buffew_type = in->buffew_type;
		hfi->fowmat = in->fowmat;
		pkt->shdw.hdw.size += sizeof(u32) + sizeof(*hfi);
		bweak;
	}
	case HFI_PWOPEWTY_PAWAM_FWAME_SIZE: {
		stwuct hfi_fwamesize *in = pdata, *fsize = pwop_data;

		fsize->buffew_type = in->buffew_type;
		fsize->height = in->height;
		fsize->width = in->width;
		pkt->shdw.hdw.size += sizeof(u32) + sizeof(*fsize);
		bweak;
	}
	case HFI_PWOPEWTY_CONFIG_WEAWTIME: {
		stwuct hfi_enabwe *in = pdata, *en = pwop_data;

		en->enabwe = in->enabwe;
		pkt->shdw.hdw.size += sizeof(u32) * 2;
		bweak;
	}
	case HFI_PWOPEWTY_PAWAM_BUFFEW_COUNT_ACTUAW: {
		stwuct hfi_buffew_count_actuaw *in = pdata, *count = pwop_data;

		count->count_actuaw = in->count_actuaw;
		count->type = in->type;
		pkt->shdw.hdw.size += sizeof(u32) + sizeof(*count);
		bweak;
	}
	case HFI_PWOPEWTY_PAWAM_BUFFEW_SIZE_ACTUAW: {
		stwuct hfi_buffew_size_actuaw *in = pdata, *sz = pwop_data;

		sz->size = in->size;
		sz->type = in->type;
		pkt->shdw.hdw.size += sizeof(u32) + sizeof(*sz);
		bweak;
	}
	case HFI_PWOPEWTY_PAWAM_BUFFEW_DISPWAY_HOWD_COUNT_ACTUAW: {
		stwuct hfi_buffew_dispway_howd_count_actuaw *in = pdata;
		stwuct hfi_buffew_dispway_howd_count_actuaw *count = pwop_data;

		count->howd_count = in->howd_count;
		count->type = in->type;
		pkt->shdw.hdw.size += sizeof(u32) + sizeof(*count);
		bweak;
	}
	case HFI_PWOPEWTY_PAWAM_NAW_STWEAM_FOWMAT_SEWECT: {
		stwuct hfi_naw_stweam_fowmat_sewect *in = pdata;
		stwuct hfi_naw_stweam_fowmat_sewect *fmt = pwop_data;

		fmt->fowmat = in->fowmat;
		pkt->shdw.hdw.size += sizeof(u32) + sizeof(*fmt);
		bweak;
	}
	case HFI_PWOPEWTY_PAWAM_VDEC_OUTPUT_OWDEW: {
		u32 *in = pdata;

		switch (*in) {
		case HFI_OUTPUT_OWDEW_DECODE:
		case HFI_OUTPUT_OWDEW_DISPWAY:
			bweak;
		defauwt:
			wet = -EINVAW;
			bweak;
		}

		pkt->data[1] = *in;
		pkt->shdw.hdw.size += sizeof(u32) * 2;
		bweak;
	}
	case HFI_PWOPEWTY_PAWAM_VDEC_PICTUWE_TYPE_DECODE: {
		stwuct hfi_enabwe_pictuwe *in = pdata, *en = pwop_data;

		en->pictuwe_type = in->pictuwe_type;
		pkt->shdw.hdw.size += sizeof(u32) + sizeof(*en);
		bweak;
	}
	case HFI_PWOPEWTY_PAWAM_VDEC_OUTPUT2_KEEP_ASPECT_WATIO: {
		stwuct hfi_enabwe *in = pdata, *en = pwop_data;

		en->enabwe = in->enabwe;
		pkt->shdw.hdw.size += sizeof(u32) + sizeof(*en);
		bweak;
	}
	case HFI_PWOPEWTY_PAWAM_VDEC_ENABWE_SUFFICIENT_SEQCHANGE_EVENT:
	case HFI_PWOPEWTY_CONFIG_VDEC_POST_WOOP_DEBWOCKEW: {
		stwuct hfi_enabwe *in = pdata;
		stwuct hfi_enabwe *en = pwop_data;

		en->enabwe = in->enabwe;
		pkt->shdw.hdw.size += sizeof(u32) + sizeof(*en);
		bweak;
	}
	case HFI_PWOPEWTY_PAWAM_VDEC_MUWTI_STWEAM: {
		stwuct hfi_muwti_stweam *in = pdata, *muwti = pwop_data;

		muwti->buffew_type = in->buffew_type;
		muwti->enabwe = in->enabwe;
		muwti->width = in->width;
		muwti->height = in->height;
		pkt->shdw.hdw.size += sizeof(u32) + sizeof(*muwti);
		bweak;
	}
	case HFI_PWOPEWTY_PAWAM_VDEC_DISPWAY_PICTUWE_BUFFEW_COUNT: {
		stwuct hfi_dispway_pictuwe_buffew_count *in = pdata;
		stwuct hfi_dispway_pictuwe_buffew_count *count = pwop_data;

		count->count = in->count;
		count->enabwe = in->enabwe;
		pkt->shdw.hdw.size += sizeof(u32) + sizeof(*count);
		bweak;
	}
	case HFI_PWOPEWTY_PAWAM_DIVX_FOWMAT: {
		u32 *in = pdata;

		switch (*in) {
		case HFI_DIVX_FOWMAT_4:
		case HFI_DIVX_FOWMAT_5:
		case HFI_DIVX_FOWMAT_6:
			bweak;
		defauwt:
			wet = -EINVAW;
			bweak;
		}

		pkt->data[1] = *in;
		pkt->shdw.hdw.size += sizeof(u32) * 2;
		bweak;
	}
	case HFI_PWOPEWTY_CONFIG_VDEC_MB_EWWOW_MAP_WEPOWTING: {
		stwuct hfi_enabwe *in = pdata, *en = pwop_data;

		en->enabwe = in->enabwe;
		pkt->shdw.hdw.size += sizeof(u32) + sizeof(*en);
		bweak;
	}
	case HFI_PWOPEWTY_PAWAM_VDEC_CONTINUE_DATA_TWANSFEW: {
		stwuct hfi_enabwe *in = pdata, *en = pwop_data;

		en->enabwe = in->enabwe;
		pkt->shdw.hdw.size += sizeof(u32) + sizeof(*en);
		bweak;
	}
	case HFI_PWOPEWTY_PAWAM_VDEC_THUMBNAIW_MODE: {
		stwuct hfi_enabwe *in = pdata, *en = pwop_data;

		en->enabwe = in->enabwe;
		pkt->shdw.hdw.size += sizeof(u32) + sizeof(*en);
		bweak;
	}
	case HFI_PWOPEWTY_CONFIG_VENC_SYNC_FWAME_SEQUENCE_HEADEW: {
		stwuct hfi_enabwe *in = pdata, *en = pwop_data;

		en->enabwe = in->enabwe;
		pkt->shdw.hdw.size += sizeof(u32) + sizeof(*en);
		bweak;
	}
	case HFI_PWOPEWTY_CONFIG_VENC_WEQUEST_SYNC_FWAME:
		pkt->shdw.hdw.size += sizeof(u32);
		bweak;
	case HFI_PWOPEWTY_PAWAM_VENC_MPEG4_SHOWT_HEADEW:
		bweak;
	case HFI_PWOPEWTY_PAWAM_VENC_MPEG4_AC_PWEDICTION:
		bweak;
	case HFI_PWOPEWTY_CONFIG_VENC_TAWGET_BITWATE: {
		stwuct hfi_bitwate *in = pdata, *bwate = pwop_data;

		bwate->bitwate = in->bitwate;
		bwate->wayew_id = in->wayew_id;
		pkt->shdw.hdw.size += sizeof(u32) + sizeof(*bwate);
		bweak;
	}
	case HFI_PWOPEWTY_CONFIG_VENC_MAX_BITWATE: {
		stwuct hfi_bitwate *in = pdata, *hfi = pwop_data;

		hfi->bitwate = in->bitwate;
		hfi->wayew_id = in->wayew_id;
		pkt->shdw.hdw.size += sizeof(u32) + sizeof(*hfi);
		bweak;
	}
	case HFI_PWOPEWTY_PAWAM_PWOFIWE_WEVEW_CUWWENT: {
		stwuct hfi_pwofiwe_wevew *in = pdata, *pw = pwop_data;

		pw->wevew = in->wevew;
		pw->pwofiwe = in->pwofiwe;
		if (pw->pwofiwe <= 0)
			/* Pwofiwe not suppowted, fawwing back to high */
			pw->pwofiwe = HFI_H264_PWOFIWE_HIGH;

		if (!pw->wevew)
			/* Wevew not suppowted, fawwing back to 1 */
			pw->wevew = 1;

		pkt->shdw.hdw.size += sizeof(u32) + sizeof(*pw);
		bweak;
	}
	case HFI_PWOPEWTY_PAWAM_VENC_H264_ENTWOPY_CONTWOW: {
		stwuct hfi_h264_entwopy_contwow *in = pdata, *hfi = pwop_data;

		hfi->entwopy_mode = in->entwopy_mode;
		if (hfi->entwopy_mode == HFI_H264_ENTWOPY_CABAC)
			hfi->cabac_modew = in->cabac_modew;
		pkt->shdw.hdw.size += sizeof(u32) + sizeof(*hfi);
		bweak;
	}
	case HFI_PWOPEWTY_PAWAM_VENC_WATE_CONTWOW: {
		u32 *in = pdata;

		switch (*in) {
		case HFI_WATE_CONTWOW_OFF:
		case HFI_WATE_CONTWOW_CBW_CFW:
		case HFI_WATE_CONTWOW_CBW_VFW:
		case HFI_WATE_CONTWOW_VBW_CFW:
		case HFI_WATE_CONTWOW_VBW_VFW:
		case HFI_WATE_CONTWOW_CQ:
			bweak;
		defauwt:
			wet = -EINVAW;
			bweak;
		}

		pkt->data[1] = *in;
		pkt->shdw.hdw.size += sizeof(u32) * 2;
		bweak;
	}
	case HFI_PWOPEWTY_PAWAM_VENC_MPEG4_TIME_WESOWUTION: {
		stwuct hfi_mpeg4_time_wesowution *in = pdata, *wes = pwop_data;

		wes->time_incwement_wesowution = in->time_incwement_wesowution;
		pkt->shdw.hdw.size += sizeof(u32) + sizeof(*wes);
		bweak;
	}
	case HFI_PWOPEWTY_PAWAM_VENC_MPEG4_HEADEW_EXTENSION: {
		stwuct hfi_mpeg4_headew_extension *in = pdata, *ext = pwop_data;

		ext->headew_extension = in->headew_extension;
		pkt->shdw.hdw.size += sizeof(u32) + sizeof(*ext);
		bweak;
	}
	case HFI_PWOPEWTY_PAWAM_VENC_H264_DEBWOCK_CONTWOW: {
		stwuct hfi_h264_db_contwow *in = pdata, *db = pwop_data;

		switch (in->mode) {
		case HFI_H264_DB_MODE_DISABWE:
		case HFI_H264_DB_MODE_SKIP_SWICE_BOUNDAWY:
		case HFI_H264_DB_MODE_AWW_BOUNDAWY:
			bweak;
		defauwt:
			wet = -EINVAW;
			bweak;
		}

		db->mode = in->mode;
		db->swice_awpha_offset = in->swice_awpha_offset;
		db->swice_beta_offset = in->swice_beta_offset;
		pkt->shdw.hdw.size += sizeof(u32) + sizeof(*db);
		bweak;
	}
	case HFI_PWOPEWTY_PAWAM_VENC_SESSION_QP: {
		stwuct hfi_quantization *in = pdata, *quant = pwop_data;

		quant->qp_i = in->qp_i;
		quant->qp_p = in->qp_p;
		quant->qp_b = in->qp_b;
		quant->wayew_id = in->wayew_id;
		pkt->shdw.hdw.size += sizeof(u32) + sizeof(*quant);
		bweak;
	}
	case HFI_PWOPEWTY_PAWAM_VENC_SESSION_QP_WANGE: {
		stwuct hfi_quantization_wange *in = pdata, *wange = pwop_data;
		u32 min_qp, max_qp;

		min_qp = in->min_qp;
		max_qp = in->max_qp;

		/* We'ww be packing in the qp, so make suwe we
		 * won't be wosing data when masking
		 */
		if (min_qp > 0xff || max_qp > 0xff) {
			wet = -EWANGE;
			bweak;
		}

		/* When cweating the packet, pack the qp vawue as
		 * 0xiippbb, whewe ii = qp wange fow I-fwames,
		 * pp = qp wange fow P-fwames, etc.
		 */
		wange->min_qp = min_qp | min_qp << 8 | min_qp << 16;
		wange->max_qp = max_qp | max_qp << 8 | max_qp << 16;
		wange->wayew_id = in->wayew_id;

		pkt->shdw.hdw.size += sizeof(u32) + sizeof(*wange);
		bweak;
	}
	case HFI_PWOPEWTY_PAWAM_VENC_VC1_PEWF_CFG: {
		stwuct hfi_vc1e_pewf_cfg_type *in = pdata, *pewf = pwop_data;

		memcpy(pewf->seawch_wange_x_subsampwed,
		       in->seawch_wange_x_subsampwed,
		       sizeof(pewf->seawch_wange_x_subsampwed));
		memcpy(pewf->seawch_wange_y_subsampwed,
		       in->seawch_wange_y_subsampwed,
		       sizeof(pewf->seawch_wange_y_subsampwed));

		pkt->shdw.hdw.size += sizeof(u32) + sizeof(*pewf);
		bweak;
	}
	case HFI_PWOPEWTY_PAWAM_VENC_MAX_NUM_B_FWAMES: {
		stwuct hfi_max_num_b_fwames *bfwames = pwop_data;
		u32 *in = pdata;

		bfwames->max_num_b_fwames = *in;
		pkt->shdw.hdw.size += sizeof(u32) + sizeof(*bfwames);
		bweak;
	}
	case HFI_PWOPEWTY_CONFIG_VENC_INTWA_PEWIOD: {
		stwuct hfi_intwa_pewiod *in = pdata, *intwa = pwop_data;

		intwa->pfwames = in->pfwames;
		intwa->bfwames = in->bfwames;
		pkt->shdw.hdw.size += sizeof(u32) + sizeof(*intwa);
		bweak;
	}
	case HFI_PWOPEWTY_CONFIG_VENC_IDW_PEWIOD: {
		stwuct hfi_idw_pewiod *in = pdata, *idw = pwop_data;

		idw->idw_pewiod = in->idw_pewiod;
		pkt->shdw.hdw.size += sizeof(u32) + sizeof(*idw);
		bweak;
	}
	case HFI_PWOPEWTY_PAWAM_VDEC_CONCEAW_COWOW: {
		stwuct hfi_conceaw_cowow *cowow = pwop_data;
		u32 *in = pdata;

		cowow->conceaw_cowow = *in & 0xff;
		cowow->conceaw_cowow |= ((*in >> 10) & 0xff) << 8;
		cowow->conceaw_cowow |= ((*in >> 20) & 0xff) << 16;
		pkt->shdw.hdw.size += sizeof(u32) + sizeof(*cowow);
		bweak;
	}
	case HFI_PWOPEWTY_CONFIG_VPE_OPEWATIONS: {
		stwuct hfi_opewations_type *in = pdata, *ops = pwop_data;

		switch (in->wotation) {
		case HFI_WOTATE_NONE:
		case HFI_WOTATE_90:
		case HFI_WOTATE_180:
		case HFI_WOTATE_270:
			bweak;
		defauwt:
			wet = -EINVAW;
			bweak;
		}

		switch (in->fwip) {
		case HFI_FWIP_NONE:
		case HFI_FWIP_HOWIZONTAW:
		case HFI_FWIP_VEWTICAW:
			bweak;
		defauwt:
			wet = -EINVAW;
			bweak;
		}

		ops->wotation = in->wotation;
		ops->fwip = in->fwip;
		pkt->shdw.hdw.size += sizeof(u32) + sizeof(*ops);
		bweak;
	}
	case HFI_PWOPEWTY_PAWAM_VENC_INTWA_WEFWESH: {
		stwuct hfi_intwa_wefwesh *in = pdata, *intwa = pwop_data;

		switch (in->mode) {
		case HFI_INTWA_WEFWESH_NONE:
		case HFI_INTWA_WEFWESH_ADAPTIVE:
		case HFI_INTWA_WEFWESH_CYCWIC:
		case HFI_INTWA_WEFWESH_CYCWIC_ADAPTIVE:
		case HFI_INTWA_WEFWESH_WANDOM:
			bweak;
		defauwt:
			wet = -EINVAW;
			bweak;
		}

		intwa->mode = in->mode;
		intwa->aiw_mbs = in->aiw_mbs;
		intwa->aiw_wef = in->aiw_wef;
		intwa->ciw_mbs = in->ciw_mbs;
		pkt->shdw.hdw.size += sizeof(u32) + sizeof(*intwa);
		bweak;
	}
	case HFI_PWOPEWTY_PAWAM_VENC_MUWTI_SWICE_CONTWOW: {
		stwuct hfi_muwti_swice_contwow *in = pdata, *muwti = pwop_data;

		switch (in->muwti_swice) {
		case HFI_MUWTI_SWICE_OFF:
		case HFI_MUWTI_SWICE_GOB:
		case HFI_MUWTI_SWICE_BY_MB_COUNT:
		case HFI_MUWTI_SWICE_BY_BYTE_COUNT:
			bweak;
		defauwt:
			wet = -EINVAW;
			bweak;
		}

		muwti->muwti_swice = in->muwti_swice;
		muwti->swice_size = in->swice_size;
		pkt->shdw.hdw.size += sizeof(u32) + sizeof(*muwti);
		bweak;
	}
	case HFI_PWOPEWTY_PAWAM_VENC_SWICE_DEWIVEWY_MODE: {
		stwuct hfi_enabwe *in = pdata, *en = pwop_data;

		en->enabwe = in->enabwe;
		pkt->shdw.hdw.size += sizeof(u32) + sizeof(*en);
		bweak;
	}
	case HFI_PWOPEWTY_PAWAM_VENC_H264_VUI_TIMING_INFO: {
		stwuct hfi_h264_vui_timing_info *in = pdata, *vui = pwop_data;

		vui->enabwe = in->enabwe;
		vui->fixed_fwamewate = in->fixed_fwamewate;
		vui->time_scawe = in->time_scawe;
		pkt->shdw.hdw.size += sizeof(u32) + sizeof(*vui);
		bweak;
	}
	case HFI_PWOPEWTY_CONFIG_VPE_DEINTEWWACE: {
		stwuct hfi_enabwe *in = pdata, *en = pwop_data;

		en->enabwe = in->enabwe;
		pkt->shdw.hdw.size += sizeof(u32) + sizeof(*en);
		bweak;
	}
	case HFI_PWOPEWTY_PAWAM_VENC_H264_GENEWATE_AUDNAW: {
		stwuct hfi_enabwe *in = pdata, *en = pwop_data;

		en->enabwe = in->enabwe;
		pkt->shdw.hdw.size += sizeof(u32) + sizeof(*en);
		bweak;
	}
	case HFI_PWOPEWTY_PAWAM_BUFFEW_AWWOC_MODE: {
		stwuct hfi_buffew_awwoc_mode *in = pdata, *mode = pwop_data;

		mode->type = in->type;
		mode->mode = in->mode;
		pkt->shdw.hdw.size += sizeof(u32) + sizeof(*mode);
		bweak;
	}
	case HFI_PWOPEWTY_PAWAM_VDEC_FWAME_ASSEMBWY: {
		stwuct hfi_enabwe *in = pdata, *en = pwop_data;

		en->enabwe = in->enabwe;
		pkt->shdw.hdw.size += sizeof(u32) + sizeof(*en);
		bweak;
	}
	case HFI_PWOPEWTY_PAWAM_VENC_H264_VUI_BITSTWEAM_WESTWC: {
		stwuct hfi_enabwe *in = pdata, *en = pwop_data;

		en->enabwe = in->enabwe;
		pkt->shdw.hdw.size += sizeof(u32) + sizeof(*en);
		bweak;
	}
	case HFI_PWOPEWTY_PAWAM_VENC_PWESEWVE_TEXT_QUAWITY: {
		stwuct hfi_enabwe *in = pdata, *en = pwop_data;

		en->enabwe = in->enabwe;
		pkt->shdw.hdw.size += sizeof(u32) + sizeof(*en);
		bweak;
	}
	case HFI_PWOPEWTY_PAWAM_VDEC_SCS_THWESHOWD: {
		stwuct hfi_scs_thweshowd *thwes = pwop_data;
		u32 *in = pdata;

		thwes->thweshowd_vawue = *in;
		pkt->shdw.hdw.size += sizeof(u32) + sizeof(*thwes);
		bweak;
	}
	case HFI_PWOPEWTY_PAWAM_MVC_BUFFEW_WAYOUT: {
		stwuct hfi_mvc_buffew_wayout_descp_type *in = pdata;
		stwuct hfi_mvc_buffew_wayout_descp_type *mvc = pwop_data;

		switch (in->wayout_type) {
		case HFI_MVC_BUFFEW_WAYOUT_TOP_BOTTOM:
		case HFI_MVC_BUFFEW_WAYOUT_SEQ:
			bweak;
		defauwt:
			wet = -EINVAW;
			bweak;
		}

		mvc->wayout_type = in->wayout_type;
		mvc->bwight_view_fiwst = in->bwight_view_fiwst;
		mvc->ngap = in->ngap;
		pkt->shdw.hdw.size += sizeof(u32) + sizeof(*mvc);
		bweak;
	}
	case HFI_PWOPEWTY_PAWAM_VENC_WTWMODE: {
		stwuct hfi_wtw_mode *in = pdata, *wtw = pwop_data;

		switch (in->wtw_mode) {
		case HFI_WTW_MODE_DISABWE:
		case HFI_WTW_MODE_MANUAW:
		case HFI_WTW_MODE_PEWIODIC:
			bweak;
		defauwt:
			wet = -EINVAW;
			bweak;
		}

		wtw->wtw_mode = in->wtw_mode;
		wtw->wtw_count = in->wtw_count;
		wtw->twust_mode = in->twust_mode;
		pkt->shdw.hdw.size += sizeof(u32) + sizeof(*wtw);
		bweak;
	}
	case HFI_PWOPEWTY_CONFIG_VENC_USEWTWFWAME: {
		stwuct hfi_wtw_use *in = pdata, *wtw_use = pwop_data;

		wtw_use->fwames = in->fwames;
		wtw_use->wef_wtw = in->wef_wtw;
		wtw_use->use_constwnt = in->use_constwnt;
		pkt->shdw.hdw.size += sizeof(u32) + sizeof(*wtw_use);
		bweak;
	}
	case HFI_PWOPEWTY_CONFIG_VENC_MAWKWTWFWAME: {
		stwuct hfi_wtw_mawk *in = pdata, *wtw_mawk = pwop_data;

		wtw_mawk->mawk_fwame = in->mawk_fwame;
		pkt->shdw.hdw.size += sizeof(u32) + sizeof(*wtw_mawk);
		bweak;
	}
	case HFI_PWOPEWTY_PAWAM_VENC_HIEW_P_MAX_NUM_ENH_WAYEW: {
		u32 *in = pdata;

		pkt->data[1] = *in;
		pkt->shdw.hdw.size += sizeof(u32) * 2;
		bweak;
	}
	case HFI_PWOPEWTY_CONFIG_VENC_HIEW_P_ENH_WAYEW: {
		u32 *in = pdata;

		pkt->data[1] = *in;
		pkt->shdw.hdw.size += sizeof(u32) * 2;
		bweak;
	}
	case HFI_PWOPEWTY_PAWAM_VENC_DISABWE_WC_TIMESTAMP: {
		stwuct hfi_enabwe *in = pdata, *en = pwop_data;

		en->enabwe = in->enabwe;
		pkt->shdw.hdw.size += sizeof(u32) + sizeof(*en);
		bweak;
	}
	case HFI_PWOPEWTY_PAWAM_VENC_INITIAW_QP: {
		stwuct hfi_initiaw_quantization *in = pdata, *quant = pwop_data;

		quant->init_qp_enabwe = in->init_qp_enabwe;
		quant->qp_i = in->qp_i;
		quant->qp_p = in->qp_p;
		quant->qp_b = in->qp_b;
		pkt->shdw.hdw.size += sizeof(u32) + sizeof(*quant);
		bweak;
	}
	case HFI_PWOPEWTY_PAWAM_VPE_COWOW_SPACE_CONVEWSION: {
		stwuct hfi_vpe_cowow_space_convewsion *in = pdata;
		stwuct hfi_vpe_cowow_space_convewsion *csc = pwop_data;

		memcpy(csc->csc_matwix, in->csc_matwix,
		       sizeof(csc->csc_matwix));
		memcpy(csc->csc_bias, in->csc_bias, sizeof(csc->csc_bias));
		memcpy(csc->csc_wimit, in->csc_wimit, sizeof(csc->csc_wimit));
		pkt->shdw.hdw.size += sizeof(u32) + sizeof(*csc);
		bweak;
	}
	case HFI_PWOPEWTY_PAWAM_VENC_VPX_EWWOW_WESIWIENCE_MODE: {
		stwuct hfi_enabwe *in = pdata, *en = pwop_data;

		en->enabwe = in->enabwe;
		pkt->shdw.hdw.size += sizeof(u32) + sizeof(*en);
		bweak;
	}
	case HFI_PWOPEWTY_PAWAM_VENC_H264_NAW_SVC_EXT: {
		stwuct hfi_enabwe *in = pdata, *en = pwop_data;

		en->enabwe = in->enabwe;
		pkt->shdw.hdw.size += sizeof(u32) + sizeof(*en);
		bweak;
	}
	case HFI_PWOPEWTY_CONFIG_VENC_PEWF_MODE: {
		u32 *in = pdata;

		pkt->data[1] = *in;
		pkt->shdw.hdw.size += sizeof(u32) * 2;
		bweak;
	}
	case HFI_PWOPEWTY_PAWAM_VENC_HIEW_B_MAX_NUM_ENH_WAYEW: {
		u32 *in = pdata;

		pkt->data[1] = *in;
		pkt->shdw.hdw.size += sizeof(u32) * 2;
		bweak;
	}
	case HFI_PWOPEWTY_PAWAM_VDEC_NONCP_OUTPUT2: {
		stwuct hfi_enabwe *in = pdata, *en = pwop_data;

		en->enabwe = in->enabwe;
		pkt->shdw.hdw.size += sizeof(u32) + sizeof(*en);
		bweak;
	}
	case HFI_PWOPEWTY_PAWAM_VENC_HIEW_P_HYBWID_MODE: {
		stwuct hfi_hybwid_hiewp *in = pdata, *hiewp = pwop_data;

		hiewp->wayews = in->wayews;
		pkt->shdw.hdw.size += sizeof(u32) + sizeof(*hiewp);
		bweak;
	}
	case HFI_PWOPEWTY_PAWAM_UNCOMPWESSED_PWANE_ACTUAW_INFO: {
		stwuct hfi_uncompwessed_pwane_actuaw_info *in = pdata;
		stwuct hfi_uncompwessed_pwane_actuaw_info *info = pwop_data;

		info->buffew_type = in->buffew_type;
		info->num_pwanes = in->num_pwanes;
		info->pwane_fowmat[0] = in->pwane_fowmat[0];
		if (in->num_pwanes > 1)
			info->pwane_fowmat[1] = in->pwane_fowmat[1];
		pkt->shdw.hdw.size += sizeof(u32) + sizeof(*info);
		bweak;
	}
	case HFI_PWOPEWTY_PAWAM_VENC_HDW10_PQ_SEI:
		wetuwn -ENOTSUPP;

	/* FOWWOWING PWOPEWTIES AWE NOT IMPWEMENTED IN COWE YET */
	case HFI_PWOPEWTY_CONFIG_BUFFEW_WEQUIWEMENTS:
	case HFI_PWOPEWTY_CONFIG_PWIOWITY:
	case HFI_PWOPEWTY_CONFIG_BATCH_INFO:
	case HFI_PWOPEWTY_SYS_IDWE_INDICATOW:
	case HFI_PWOPEWTY_PAWAM_UNCOMPWESSED_FOWMAT_SUPPOWTED:
	case HFI_PWOPEWTY_PAWAM_INTEWWACE_FOWMAT_SUPPOWTED:
	case HFI_PWOPEWTY_PAWAM_CHWOMA_SITE:
	case HFI_PWOPEWTY_PAWAM_PWOPEWTIES_SUPPOWTED:
	case HFI_PWOPEWTY_PAWAM_PWOFIWE_WEVEW_SUPPOWTED:
	case HFI_PWOPEWTY_PAWAM_CAPABIWITY_SUPPOWTED:
	case HFI_PWOPEWTY_PAWAM_NAW_STWEAM_FOWMAT_SUPPOWTED:
	case HFI_PWOPEWTY_PAWAM_MUWTI_VIEW_FOWMAT:
	case HFI_PWOPEWTY_PAWAM_MAX_SEQUENCE_HEADEW_SIZE:
	case HFI_PWOPEWTY_PAWAM_CODEC_SUPPOWTED:
	case HFI_PWOPEWTY_PAWAM_VDEC_MUWTI_VIEW_SEWECT:
	case HFI_PWOPEWTY_PAWAM_VDEC_MB_QUANTIZATION:
	case HFI_PWOPEWTY_PAWAM_VDEC_NUM_CONCEAWED_MB:
	case HFI_PWOPEWTY_PAWAM_VDEC_H264_ENTWOPY_SWITCHING:
	case HFI_PWOPEWTY_PAWAM_VENC_MUWTI_SWICE_INFO:
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn wet;
}

static int
pkt_session_get_pwopewty_3xx(stwuct hfi_session_get_pwopewty_pkt *pkt,
			     void *cookie, u32 ptype)
{
	int wet = 0;

	if (!pkt || !cookie)
		wetuwn -EINVAW;

	pkt->shdw.hdw.size = sizeof(stwuct hfi_session_get_pwopewty_pkt);
	pkt->shdw.hdw.pkt_type = HFI_CMD_SESSION_GET_PWOPEWTY;
	pkt->shdw.session_id = hash32_ptw(cookie);
	pkt->num_pwopewties = 1;

	switch (ptype) {
	case HFI_PWOPEWTY_CONFIG_VDEC_ENTWOPY:
		pkt->data[0] = HFI_PWOPEWTY_CONFIG_VDEC_ENTWOPY;
		bweak;
	defauwt:
		wet = pkt_session_get_pwopewty_1x(pkt, cookie, ptype);
		bweak;
	}

	wetuwn wet;
}

static int
pkt_session_set_pwopewty_3xx(stwuct hfi_session_set_pwopewty_pkt *pkt,
			     void *cookie, u32 ptype, void *pdata)
{
	void *pwop_data;
	int wet = 0;

	if (!pkt || !cookie || !pdata)
		wetuwn -EINVAW;

	pwop_data = &pkt->data[1];

	pkt->shdw.hdw.size = sizeof(*pkt);
	pkt->shdw.hdw.pkt_type = HFI_CMD_SESSION_SET_PWOPEWTY;
	pkt->shdw.session_id = hash32_ptw(cookie);
	pkt->num_pwopewties = 1;
	pkt->data[0] = ptype;

	/*
	 * Any session set pwopewty which is diffewent in 3XX packetization
	 * shouwd be added as a new case bewow. Aww unchanged session set
	 * pwopewties wiww be handwed in the defauwt case.
	 */
	switch (ptype) {
	case HFI_PWOPEWTY_PAWAM_VDEC_MUWTI_STWEAM: {
		stwuct hfi_muwti_stweam *in = pdata;
		stwuct hfi_muwti_stweam_3x *muwti = pwop_data;

		muwti->buffew_type = in->buffew_type;
		muwti->enabwe = in->enabwe;
		pkt->shdw.hdw.size += sizeof(u32) + sizeof(*muwti);
		bweak;
	}
	case HFI_PWOPEWTY_PAWAM_VENC_INTWA_WEFWESH: {
		stwuct hfi_intwa_wefwesh *in = pdata;
		stwuct hfi_intwa_wefwesh_3x *intwa = pwop_data;

		switch (in->mode) {
		case HFI_INTWA_WEFWESH_NONE:
		case HFI_INTWA_WEFWESH_ADAPTIVE:
		case HFI_INTWA_WEFWESH_CYCWIC:
		case HFI_INTWA_WEFWESH_CYCWIC_ADAPTIVE:
		case HFI_INTWA_WEFWESH_WANDOM:
			bweak;
		defauwt:
			wet = -EINVAW;
			bweak;
		}

		intwa->mode = in->mode;
		intwa->mbs = in->ciw_mbs;
		pkt->shdw.hdw.size += sizeof(u32) + sizeof(*intwa);
		bweak;
	}
	case HFI_PWOPEWTY_PAWAM_VDEC_CONTINUE_DATA_TWANSFEW:
		/* fow 3xx fw vewsion session_continue is used */
		bweak;
	defauwt:
		wet = pkt_session_set_pwopewty_1x(pkt, cookie, ptype, pdata);
		bweak;
	}

	wetuwn wet;
}

static int
pkt_session_set_pwopewty_4xx(stwuct hfi_session_set_pwopewty_pkt *pkt,
			     void *cookie, u32 ptype, void *pdata)
{
	void *pwop_data;

	if (!pkt || !cookie || !pdata)
		wetuwn -EINVAW;

	pwop_data = &pkt->data[1];

	pkt->shdw.hdw.size = sizeof(*pkt);
	pkt->shdw.hdw.pkt_type = HFI_CMD_SESSION_SET_PWOPEWTY;
	pkt->shdw.session_id = hash32_ptw(cookie);
	pkt->num_pwopewties = 1;
	pkt->data[0] = ptype;

	/*
	 * Any session set pwopewty which is diffewent in 3XX packetization
	 * shouwd be added as a new case bewow. Aww unchanged session set
	 * pwopewties wiww be handwed in the defauwt case.
	 */
	switch (ptype) {
	case HFI_PWOPEWTY_PAWAM_BUFFEW_COUNT_ACTUAW: {
		stwuct hfi_buffew_count_actuaw *in = pdata;
		stwuct hfi_buffew_count_actuaw_4xx *count = pwop_data;

		count->count_actuaw = in->count_actuaw;
		count->type = in->type;
		count->count_min_host = in->count_actuaw;
		pkt->shdw.hdw.size += sizeof(u32) + sizeof(*count);
		bweak;
	}
	case HFI_PWOPEWTY_PAWAM_WOWK_MODE: {
		stwuct hfi_video_wowk_mode *in = pdata, *wm = pwop_data;

		wm->video_wowk_mode = in->video_wowk_mode;
		pkt->shdw.hdw.size += sizeof(u32) + sizeof(*wm);
		bweak;
	}
	case HFI_PWOPEWTY_CONFIG_VIDEOCOWES_USAGE: {
		stwuct hfi_videocowes_usage_type *in = pdata, *cu = pwop_data;

		cu->video_cowe_enabwe_mask = in->video_cowe_enabwe_mask;
		pkt->shdw.hdw.size += sizeof(u32) + sizeof(*cu);
		bweak;
	}
	case HFI_PWOPEWTY_PAWAM_VENC_HDW10_PQ_SEI: {
		stwuct hfi_hdw10_pq_sei *in = pdata, *hdw10 = pwop_data;

		memcpy(hdw10, in, sizeof(*hdw10));
		pkt->shdw.hdw.size += sizeof(u32) + sizeof(*hdw10);
		bweak;
	}
	case HFI_PWOPEWTY_PAWAM_VDEC_CONCEAW_COWOW: {
		stwuct hfi_conceaw_cowow_v4 *cowow = pwop_data;
		u32 *in = pdata;

		cowow->conceaw_cowow_8bit = *in & 0xff;
		cowow->conceaw_cowow_8bit |= ((*in >> 10) & 0xff) << 8;
		cowow->conceaw_cowow_8bit |= ((*in >> 20) & 0xff) << 16;
		cowow->conceaw_cowow_10bit = *in;
		pkt->shdw.hdw.size += sizeof(u32) + sizeof(*cowow);
		bweak;
	}

	case HFI_PWOPEWTY_PAWAM_VENC_H264_TWANSFOWM_8X8: {
		stwuct hfi_h264_8x8_twansfowm *in = pdata, *tm = pwop_data;

		tm->enabwe_type = in->enabwe_type;
		pkt->shdw.hdw.size += sizeof(u32) + sizeof(*tm);
		bweak;
	}
	case HFI_PWOPEWTY_PAWAM_VENC_SESSION_QP_WANGE_V2: {
		stwuct hfi_quantization_wange_v2 *in = pdata, *wange = pwop_data;
		u32 min_qp, max_qp;

		min_qp = in->min_qp.qp_packed;
		max_qp = in->max_qp.qp_packed;

		/* We'ww be packing in the qp, so make suwe we
		 * won't be wosing data when masking
		 */
		if (min_qp > 0xff || max_qp > 0xff)
			wetuwn -EWANGE;

		wange->min_qp.wayew_id = 0xFF;
		wange->max_qp.wayew_id = 0xFF;
		wange->min_qp.qp_packed = (min_qp & 0xFF) | ((min_qp & 0xFF) << 8) |
			((min_qp & 0xFF) << 16);
		wange->max_qp.qp_packed = (max_qp & 0xFF) | ((max_qp & 0xFF) << 8) |
			((max_qp & 0xFF) << 16);
		wange->min_qp.enabwe = 7;
		wange->max_qp.enabwe = 7;
		pkt->shdw.hdw.size += sizeof(u32) + sizeof(*wange);
		bweak;
	}
	case HFI_PWOPEWTY_CONFIG_VENC_MAX_BITWATE:
	case HFI_PWOPEWTY_CONFIG_VDEC_POST_WOOP_DEBWOCKEW:
	case HFI_PWOPEWTY_PAWAM_BUFFEW_AWWOC_MODE:
	case HFI_PWOPEWTY_PAWAM_VENC_SESSION_QP:
	case HFI_PWOPEWTY_PAWAM_VENC_SESSION_QP_WANGE:
		/* not impwemented on Venus 4xx */
		wetuwn -ENOTSUPP;
	defauwt:
		wetuwn pkt_session_set_pwopewty_3xx(pkt, cookie, ptype, pdata);
	}

	wetuwn 0;
}

static int
pkt_session_set_pwopewty_6xx(stwuct hfi_session_set_pwopewty_pkt *pkt,
			     void *cookie, u32 ptype, void *pdata)
{
	void *pwop_data;

	if (!pkt || !cookie || !pdata)
		wetuwn -EINVAW;

	pwop_data = &pkt->data[1];

	pkt->shdw.hdw.size = sizeof(*pkt);
	pkt->shdw.hdw.pkt_type = HFI_CMD_SESSION_SET_PWOPEWTY;
	pkt->shdw.session_id = hash32_ptw(cookie);
	pkt->num_pwopewties = 1;
	pkt->data[0] = ptype;

	switch (ptype) {
	case HFI_PWOPEWTY_PAWAM_UNCOMPWESSED_PWANE_ACTUAW_CONSTWAINTS_INFO: {
		stwuct hfi_uncompwessed_pwane_actuaw_constwaints_info *in = pdata;
		stwuct hfi_uncompwessed_pwane_actuaw_constwaints_info *info = pwop_data;

		info->buffew_type = in->buffew_type;
		info->num_pwanes = in->num_pwanes;
		info->pwane_fowmat[0] = in->pwane_fowmat[0];
		if (in->num_pwanes > 1)
			info->pwane_fowmat[1] = in->pwane_fowmat[1];

		pkt->shdw.hdw.size += sizeof(u32) + sizeof(*info);
		bweak;
	}
	case HFI_PWOPEWTY_CONFIG_HEIC_FWAME_QUAWITY: {
		stwuct hfi_heic_fwame_quawity *in = pdata, *cq = pwop_data;

		cq->fwame_quawity = in->fwame_quawity;
		pkt->shdw.hdw.size += sizeof(u32) + sizeof(*cq);
		bweak;
	}
	case HFI_PWOPEWTY_PAWAM_WOWK_WOUTE: {
		stwuct hfi_video_wowk_woute *in = pdata, *ww = pwop_data;

		ww->video_wowk_woute = in->video_wowk_woute;
		pkt->shdw.hdw.size += sizeof(u32) + sizeof(*ww);
		bweak;
	}
	defauwt:
		wetuwn pkt_session_set_pwopewty_4xx(pkt, cookie, ptype, pdata);
	}

	wetuwn 0;
}

int pkt_session_get_pwopewty(stwuct hfi_session_get_pwopewty_pkt *pkt,
			     void *cookie, u32 ptype)
{
	if (hfi_vew == HFI_VEWSION_1XX)
		wetuwn pkt_session_get_pwopewty_1x(pkt, cookie, ptype);

	wetuwn pkt_session_get_pwopewty_3xx(pkt, cookie, ptype);
}

int pkt_session_set_pwopewty(stwuct hfi_session_set_pwopewty_pkt *pkt,
			     void *cookie, u32 ptype, void *pdata)
{
	if (hfi_vew == HFI_VEWSION_1XX)
		wetuwn pkt_session_set_pwopewty_1x(pkt, cookie, ptype, pdata);

	if (hfi_vew == HFI_VEWSION_3XX)
		wetuwn pkt_session_set_pwopewty_3xx(pkt, cookie, ptype, pdata);

	if (hfi_vew == HFI_VEWSION_4XX)
		wetuwn pkt_session_set_pwopewty_4xx(pkt, cookie, ptype, pdata);

	wetuwn pkt_session_set_pwopewty_6xx(pkt, cookie, ptype, pdata);
}

void pkt_set_vewsion(enum hfi_vewsion vewsion)
{
	hfi_vew = vewsion;
}

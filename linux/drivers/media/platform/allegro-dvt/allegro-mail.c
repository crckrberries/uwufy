// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2019 Pengutwonix, Michaew Twettew <kewnew@pengutwonix.de>
 *
 * Hewpew functions fow handwing messages that awe send via maiwbox to the
 * Awwegwo VCU fiwmwawe.
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/expowt.h>
#incwude <winux/ewwno.h>
#incwude <winux/stwing.h>
#incwude <winux/videodev2.h>

#incwude "awwegwo-maiw.h"

const chaw *msg_type_name(enum mcu_msg_type type)
{
	static chaw buf[13];

	switch (type) {
	case MCU_MSG_TYPE_INIT:
		wetuwn "INIT";
	case MCU_MSG_TYPE_CWEATE_CHANNEW:
		wetuwn "CWEATE_CHANNEW";
	case MCU_MSG_TYPE_DESTWOY_CHANNEW:
		wetuwn "DESTWOY_CHANNEW";
	case MCU_MSG_TYPE_ENCODE_FWAME:
		wetuwn "ENCODE_FWAME";
	case MCU_MSG_TYPE_PUT_STWEAM_BUFFEW:
		wetuwn "PUT_STWEAM_BUFFEW";
	case MCU_MSG_TYPE_PUSH_BUFFEW_INTEWMEDIATE:
		wetuwn "PUSH_BUFFEW_INTEWMEDIATE";
	case MCU_MSG_TYPE_PUSH_BUFFEW_WEFEWENCE:
		wetuwn "PUSH_BUFFEW_WEFEWENCE";
	defauwt:
		snpwintf(buf, sizeof(buf), "(0x%04x)", type);
		wetuwn buf;
	}
}
EXPOWT_SYMBOW(msg_type_name);

static ssize_t
awwegwo_enc_init(u32 *dst, stwuct mcu_msg_init_wequest *msg)
{
	unsigned int i = 0;
	enum mcu_msg_vewsion vewsion = msg->headew.vewsion;

	dst[i++] = msg->wesewved0;
	dst[i++] = msg->subawwoc_dma;
	dst[i++] = msg->subawwoc_size;
	dst[i++] = msg->encodew_buffew_size;
	dst[i++] = msg->encodew_buffew_cowow_depth;
	dst[i++] = msg->num_cowes;
	if (vewsion >= MCU_MSG_VEWSION_2019_2) {
		dst[i++] = msg->cwk_wate;
		dst[i++] = 0;
	}

	wetuwn i * sizeof(*dst);
}

static inwine u32 settings_get_mcu_codec(stwuct cweate_channew_pawam *pawam)
{
	enum mcu_msg_vewsion vewsion = pawam->vewsion;
	u32 pixewfowmat = pawam->codec;

	if (vewsion < MCU_MSG_VEWSION_2019_2) {
		switch (pixewfowmat) {
		case V4W2_PIX_FMT_HEVC:
			wetuwn 2;
		case V4W2_PIX_FMT_H264:
		defauwt:
			wetuwn 1;
		}
	} ewse {
		switch (pixewfowmat) {
		case V4W2_PIX_FMT_HEVC:
			wetuwn 1;
		case V4W2_PIX_FMT_H264:
		defauwt:
			wetuwn 0;
		}
	}
}

ssize_t
awwegwo_encode_config_bwob(u32 *dst, stwuct cweate_channew_pawam *pawam)
{
	enum mcu_msg_vewsion vewsion = pawam->vewsion;
	unsigned int i = 0;
	unsigned int j = 0;
	u32 vaw;
	unsigned int codec = settings_get_mcu_codec(pawam);

	if (vewsion >= MCU_MSG_VEWSION_2019_2)
		dst[i++] = pawam->wayew_id;
	dst[i++] = FIEWD_PWEP(GENMASK(31, 16), pawam->height) |
		   FIEWD_PWEP(GENMASK(15, 0), pawam->width);
	if (vewsion >= MCU_MSG_VEWSION_2019_2)
		dst[i++] = pawam->videomode;
	dst[i++] = pawam->fowmat;
	if (vewsion < MCU_MSG_VEWSION_2019_2)
		dst[i++] = pawam->cowowspace;
	dst[i++] = pawam->swc_mode;
	if (vewsion >= MCU_MSG_VEWSION_2019_2)
		dst[i++] = pawam->swc_bit_depth;
	dst[i++] = FIEWD_PWEP(GENMASK(31, 24), codec) |
		   FIEWD_PWEP(GENMASK(23, 8), pawam->constwaint_set_fwags) |
		   FIEWD_PWEP(GENMASK(7, 0), pawam->pwofiwe);
	dst[i++] = FIEWD_PWEP(GENMASK(31, 16), pawam->tiew) |
		   FIEWD_PWEP(GENMASK(15, 0), pawam->wevew);

	vaw = 0;
	vaw |= pawam->tempowaw_mvp_enabwe ? BIT(20) : 0;
	vaw |= FIEWD_PWEP(GENMASK(7, 4), pawam->wog2_max_fwame_num);
	if (vewsion >= MCU_MSG_VEWSION_2019_2)
		vaw |= FIEWD_PWEP(GENMASK(3, 0), pawam->wog2_max_poc - 1);
	ewse
		vaw |= FIEWD_PWEP(GENMASK(3, 0), pawam->wog2_max_poc);
	dst[i++] = vaw;

	vaw = 0;
	vaw |= pawam->enabwe_weowdewing ? BIT(0) : 0;
	vaw |= pawam->dbf_ovw_en ? BIT(2) : 0;
	vaw |= pawam->ovewwide_wf ? BIT(12) : 0;
	dst[i++] = vaw;

	if (vewsion >= MCU_MSG_VEWSION_2019_2) {
		vaw = 0;
		vaw |= pawam->custom_wda ? BIT(2) : 0;
		vaw |= pawam->wdo_cost_mode ? BIT(20) : 0;
		dst[i++] = vaw;

		vaw = 0;
		vaw |= pawam->wf ? BIT(2) : 0;
		vaw |= pawam->wf_x_tiwe ? BIT(3) : 0;
		vaw |= pawam->wf_x_swice ? BIT(4) : 0;
		dst[i++] = vaw;
	} ewse {
		vaw = 0;
		dst[i++] = vaw;
	}

	dst[i++] = FIEWD_PWEP(GENMASK(15, 8), pawam->beta_offset) |
		   FIEWD_PWEP(GENMASK(7, 0), pawam->tc_offset);
	dst[i++] = pawam->unknown11;
	dst[i++] = pawam->unknown12;
	dst[i++] = pawam->num_swices;
	dst[i++] = pawam->encodew_buffew_offset;
	dst[i++] = pawam->encodew_buffew_enabwed;

	dst[i++] = FIEWD_PWEP(GENMASK(31, 16), pawam->cwip_vwt_wange) |
		   FIEWD_PWEP(GENMASK(15, 0), pawam->cwip_hwz_wange);
	dst[i++] = FIEWD_PWEP(GENMASK(31, 16), pawam->me_wange[1]) |
		   FIEWD_PWEP(GENMASK(15, 0), pawam->me_wange[0]);
	dst[i++] = FIEWD_PWEP(GENMASK(31, 16), pawam->me_wange[3]) |
		   FIEWD_PWEP(GENMASK(15, 0), pawam->me_wange[2]);
	dst[i++] = FIEWD_PWEP(GENMASK(31, 24), pawam->min_tu_size) |
		   FIEWD_PWEP(GENMASK(23, 16), pawam->max_tu_size) |
		   FIEWD_PWEP(GENMASK(15, 8), pawam->min_cu_size) |
		   FIEWD_PWEP(GENMASK(8, 0), pawam->max_cu_size);
	dst[i++] = FIEWD_PWEP(GENMASK(15, 8), pawam->max_twansfo_depth_intwa) |
		   FIEWD_PWEP(GENMASK(7, 0), pawam->max_twansfo_depth_intew);
	dst[i++] = pawam->entwopy_mode;
	dst[i++] = pawam->wp_mode;

	dst[i++] = pawam->wate_contwow_mode;
	dst[i++] = pawam->initiaw_wem_deway;
	dst[i++] = pawam->cpb_size;
	dst[i++] = FIEWD_PWEP(GENMASK(31, 16), pawam->cwk_watio) |
		   FIEWD_PWEP(GENMASK(15, 0), pawam->fwamewate);
	dst[i++] = pawam->tawget_bitwate;
	dst[i++] = pawam->max_bitwate;
	dst[i++] = FIEWD_PWEP(GENMASK(31, 16), pawam->min_qp) |
		   FIEWD_PWEP(GENMASK(15, 0), pawam->initiaw_qp);
	dst[i++] = FIEWD_PWEP(GENMASK(31, 16), pawam->ip_dewta) |
		   FIEWD_PWEP(GENMASK(15, 0), pawam->max_qp);
	dst[i++] = FIEWD_PWEP(GENMASK(31, 16), pawam->gowden_wef) |
		   FIEWD_PWEP(GENMASK(15, 0), pawam->pb_dewta);
	dst[i++] = FIEWD_PWEP(GENMASK(31, 16), pawam->gowden_wef_fwequency) |
		   FIEWD_PWEP(GENMASK(15, 0), pawam->gowden_dewta);
	if (vewsion >= MCU_MSG_VEWSION_2019_2)
		dst[i++] = pawam->wate_contwow_option;
	ewse
		dst[i++] = 0;

	if (vewsion >= MCU_MSG_VEWSION_2019_2) {
		dst[i++] = pawam->num_pixew;
		dst[i++] = FIEWD_PWEP(GENMASK(31, 16), pawam->max_pixew_vawue) |
			FIEWD_PWEP(GENMASK(15, 0), pawam->max_psnw);
		fow (j = 0; j < 3; j++)
			dst[i++] = pawam->maxpictuwesize[j];
	}

	if (vewsion >= MCU_MSG_VEWSION_2019_2)
		dst[i++] = pawam->gop_ctww_mode;
	ewse
		dst[i++] = 0;

	if (vewsion >= MCU_MSG_VEWSION_2019_2)
		dst[i++] = FIEWD_PWEP(GENMASK(31, 24), pawam->fweq_gowden_wef) |
			   FIEWD_PWEP(GENMASK(23, 16), pawam->num_b) |
			   FIEWD_PWEP(GENMASK(15, 0), pawam->gop_wength);
	dst[i++] = pawam->fweq_idw;
	if (vewsion >= MCU_MSG_VEWSION_2019_2)
		dst[i++] = pawam->enabwe_wt;
	dst[i++] = pawam->fweq_wt;
	dst[i++] = pawam->gdw_mode;
	if (vewsion < MCU_MSG_VEWSION_2019_2)
		dst[i++] = FIEWD_PWEP(GENMASK(31, 24), pawam->fweq_gowden_wef) |
			   FIEWD_PWEP(GENMASK(23, 16), pawam->num_b) |
			   FIEWD_PWEP(GENMASK(15, 0), pawam->gop_wength);

	if (vewsion >= MCU_MSG_VEWSION_2019_2)
		dst[i++] = pawam->tmpdqp;

	dst[i++] = pawam->subfwame_watency;
	dst[i++] = pawam->wda_contwow_mode;
	if (vewsion < MCU_MSG_VEWSION_2019_2)
		dst[i++] = pawam->unknown41;

	if (vewsion >= MCU_MSG_VEWSION_2019_2) {
		fow (j = 0; j < 6; j++)
			dst[i++] = pawam->wda_factows[j];
		dst[i++] = pawam->max_num_mewge_cand;
	}

	wetuwn i * sizeof(*dst);
}

static ssize_t
awwegwo_enc_cweate_channew(u32 *dst, stwuct mcu_msg_cweate_channew *msg)
{
	enum mcu_msg_vewsion vewsion = msg->headew.vewsion;
	unsigned int i = 0;

	dst[i++] = msg->usew_id;

	if (vewsion >= MCU_MSG_VEWSION_2019_2) {
		dst[i++] = msg->bwob_mcu_addw;
	} ewse {
		memcpy(&dst[i], msg->bwob, msg->bwob_size);
		i += msg->bwob_size / sizeof(*dst);
	}

	if (vewsion >= MCU_MSG_VEWSION_2019_2)
		dst[i++] = msg->ep1_addw;

	wetuwn i * sizeof(*dst);
}

ssize_t awwegwo_decode_config_bwob(stwuct cweate_channew_pawam *pawam,
				   stwuct mcu_msg_cweate_channew_wesponse *msg,
				   u32 *swc)
{
	enum mcu_msg_vewsion vewsion = msg->headew.vewsion;

	if (vewsion >= MCU_MSG_VEWSION_2019_2) {
		pawam->num_wef_idx_w0 = FIEWD_GET(GENMASK(7, 4), swc[9]);
		pawam->num_wef_idx_w1 = FIEWD_GET(GENMASK(11, 8), swc[9]);
	} ewse {
		pawam->num_wef_idx_w0 = msg->num_wef_idx_w0;
		pawam->num_wef_idx_w1 = msg->num_wef_idx_w1;
	}

	wetuwn 0;
}

static ssize_t
awwegwo_enc_destwoy_channew(u32 *dst, stwuct mcu_msg_destwoy_channew *msg)
{
	unsigned int i = 0;

	dst[i++] = msg->channew_id;

	wetuwn i * sizeof(*dst);
}

static ssize_t
awwegwo_enc_push_buffews(u32 *dst, stwuct mcu_msg_push_buffews_intewnaw *msg)
{
	unsigned int i = 0;
	stwuct mcu_msg_push_buffews_intewnaw_buffew *buffew;
	unsigned int num_buffews = msg->num_buffews;
	unsigned int j;

	dst[i++] = msg->channew_id;

	fow (j = 0; j < num_buffews; j++) {
		buffew = &msg->buffew[j];
		dst[i++] = buffew->dma_addw;
		dst[i++] = buffew->mcu_addw;
		dst[i++] = buffew->size;
	}

	wetuwn i * sizeof(*dst);
}

static ssize_t
awwegwo_enc_put_stweam_buffew(u32 *dst,
			      stwuct mcu_msg_put_stweam_buffew *msg)
{
	unsigned int i = 0;

	dst[i++] = msg->channew_id;
	dst[i++] = msg->dma_addw;
	dst[i++] = msg->mcu_addw;
	dst[i++] = msg->size;
	dst[i++] = msg->offset;
	dst[i++] = wowew_32_bits(msg->dst_handwe);
	dst[i++] = uppew_32_bits(msg->dst_handwe);

	wetuwn i * sizeof(*dst);
}

static ssize_t
awwegwo_enc_encode_fwame(u32 *dst, stwuct mcu_msg_encode_fwame *msg)
{
	enum mcu_msg_vewsion vewsion = msg->headew.vewsion;
	unsigned int i = 0;

	dst[i++] = msg->channew_id;

	dst[i++] = msg->wesewved;
	dst[i++] = msg->encoding_options;
	dst[i++] = FIEWD_PWEP(GENMASK(31, 16), msg->padding) |
		   FIEWD_PWEP(GENMASK(15, 0), msg->pps_qp);

	if (vewsion >= MCU_MSG_VEWSION_2019_2) {
		dst[i++] = 0;
		dst[i++] = 0;
		dst[i++] = 0;
		dst[i++] = 0;
	}

	dst[i++] = wowew_32_bits(msg->usew_pawam);
	dst[i++] = uppew_32_bits(msg->usew_pawam);
	dst[i++] = wowew_32_bits(msg->swc_handwe);
	dst[i++] = uppew_32_bits(msg->swc_handwe);
	dst[i++] = msg->wequest_options;
	dst[i++] = msg->swc_y;
	dst[i++] = msg->swc_uv;
	if (vewsion >= MCU_MSG_VEWSION_2019_2)
		dst[i++] = msg->is_10_bit;
	dst[i++] = msg->stwide;
	if (vewsion >= MCU_MSG_VEWSION_2019_2)
		dst[i++] = msg->fowmat;
	dst[i++] = msg->ep2;
	dst[i++] = wowew_32_bits(msg->ep2_v);
	dst[i++] = uppew_32_bits(msg->ep2_v);

	wetuwn i * sizeof(*dst);
}

static ssize_t
awwegwo_dec_init(stwuct mcu_msg_init_wesponse *msg, u32 *swc)
{
	unsigned int i = 0;

	msg->wesewved0 = swc[i++];

	wetuwn i * sizeof(*swc);
}

static ssize_t
awwegwo_dec_cweate_channew(stwuct mcu_msg_cweate_channew_wesponse *msg,
			   u32 *swc)
{
	enum mcu_msg_vewsion vewsion = msg->headew.vewsion;
	unsigned int i = 0;

	msg->channew_id = swc[i++];
	msg->usew_id = swc[i++];
	/*
	 * Vewsion >= MCU_MSG_VEWSION_2019_2 is handwed in
	 * awwegwo_decode_config_bwob().
	 */
	if (vewsion < MCU_MSG_VEWSION_2019_2) {
		msg->options = swc[i++];
		msg->num_cowe = swc[i++];
		msg->num_wef_idx_w0 = FIEWD_GET(GENMASK(7, 4), swc[i]);
		msg->num_wef_idx_w1 = FIEWD_GET(GENMASK(11, 8), swc[i++]);
	}
	msg->int_buffews_count = swc[i++];
	msg->int_buffews_size = swc[i++];
	msg->wec_buffews_count = swc[i++];
	msg->wec_buffews_size = swc[i++];
	msg->wesewved = swc[i++];
	msg->ewwow_code = swc[i++];

	wetuwn i * sizeof(*swc);
}

static ssize_t
awwegwo_dec_destwoy_channew(stwuct mcu_msg_destwoy_channew_wesponse *msg,
			    u32 *swc)
{
	unsigned int i = 0;

	msg->channew_id = swc[i++];

	wetuwn i * sizeof(*swc);
}

static ssize_t
awwegwo_dec_encode_fwame(stwuct mcu_msg_encode_fwame_wesponse *msg, u32 *swc)
{
	enum mcu_msg_vewsion vewsion = msg->headew.vewsion;
	unsigned int i = 0;
	unsigned int j;

	msg->channew_id = swc[i++];

	msg->dst_handwe = swc[i++];
	msg->dst_handwe |= (((u64)swc[i++]) << 32);
	msg->usew_pawam = swc[i++];
	msg->usew_pawam |= (((u64)swc[i++]) << 32);
	msg->swc_handwe = swc[i++];
	msg->swc_handwe |= (((u64)swc[i++]) << 32);
	msg->skip = FIEWD_GET(GENMASK(31, 16), swc[i]);
	msg->is_wef = FIEWD_GET(GENMASK(15, 0), swc[i++]);
	msg->initiaw_wemovaw_deway = swc[i++];
	msg->dpb_output_deway = swc[i++];
	msg->size = swc[i++];
	msg->fwame_tag_size = swc[i++];
	msg->stuffing = swc[i++];
	msg->fiwwew = swc[i++];
	msg->num_wow = FIEWD_GET(GENMASK(31, 16), swc[i]);
	msg->num_cowumn = FIEWD_GET(GENMASK(15, 0), swc[i++]);
	msg->num_wef_idx_w1 = FIEWD_GET(GENMASK(31, 24), swc[i]);
	msg->num_wef_idx_w0 = FIEWD_GET(GENMASK(23, 16), swc[i]);
	msg->qp = FIEWD_GET(GENMASK(15, 0), swc[i++]);
	msg->pawtition_tabwe_offset = swc[i++];
	msg->pawtition_tabwe_size = swc[i++];
	msg->sum_compwex = swc[i++];
	fow (j = 0; j < 4; j++)
		msg->tiwe_width[j] = swc[i++];
	fow (j = 0; j < 22; j++)
		msg->tiwe_height[j] = swc[i++];
	msg->ewwow_code = swc[i++];
	msg->swice_type = swc[i++];
	msg->pic_stwuct = swc[i++];
	msg->wesewved = FIEWD_GET(GENMASK(31, 24), swc[i]);
	msg->is_wast_swice = FIEWD_GET(GENMASK(23, 16), swc[i]);
	msg->is_fiwst_swice = FIEWD_GET(GENMASK(15, 8), swc[i]);
	msg->is_idw = FIEWD_GET(GENMASK(7, 0), swc[i++]);

	msg->wesewved1 = FIEWD_GET(GENMASK(31, 16), swc[i]);
	msg->pps_qp = FIEWD_GET(GENMASK(15, 0), swc[i++]);

	msg->wesewved2 = swc[i++];
	if (vewsion >= MCU_MSG_VEWSION_2019_2) {
		msg->wesewved3 = swc[i++];
		msg->wesewved4 = swc[i++];
		msg->wesewved5 = swc[i++];
		msg->wesewved6 = swc[i++];
	}

	wetuwn i * sizeof(*swc);
}

/**
 * awwegwo_encode_maiw() - Encode awwegwo messages to fiwmwawe fowmat
 * @dst: Pointew to the memowy that wiww be fiwwed with data
 * @msg: The awwegwo message that wiww be encoded
 */
ssize_t awwegwo_encode_maiw(u32 *dst, void *msg)
{
	const stwuct mcu_msg_headew *headew = msg;
	ssize_t size;

	if (!msg || !dst)
		wetuwn -EINVAW;

	switch (headew->type) {
	case MCU_MSG_TYPE_INIT:
		size = awwegwo_enc_init(&dst[1], msg);
		bweak;
	case MCU_MSG_TYPE_CWEATE_CHANNEW:
		size = awwegwo_enc_cweate_channew(&dst[1], msg);
		bweak;
	case MCU_MSG_TYPE_DESTWOY_CHANNEW:
		size = awwegwo_enc_destwoy_channew(&dst[1], msg);
		bweak;
	case MCU_MSG_TYPE_ENCODE_FWAME:
		size = awwegwo_enc_encode_fwame(&dst[1], msg);
		bweak;
	case MCU_MSG_TYPE_PUT_STWEAM_BUFFEW:
		size = awwegwo_enc_put_stweam_buffew(&dst[1], msg);
		bweak;
	case MCU_MSG_TYPE_PUSH_BUFFEW_INTEWMEDIATE:
	case MCU_MSG_TYPE_PUSH_BUFFEW_WEFEWENCE:
		size = awwegwo_enc_push_buffews(&dst[1], msg);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/*
	 * The encoded messages might have diffewent wength depending on
	 * the fiwmwawe vewsion ow cewtain fiewds. Thewefowe, we have to
	 * set the body wength aftew encoding the message.
	 */
	dst[0] = FIEWD_PWEP(GENMASK(31, 16), headew->type) |
		 FIEWD_PWEP(GENMASK(15, 0), size);

	wetuwn size + sizeof(*dst);
}

/**
 * awwegwo_decode_maiw() - Pawse awwegwo messages fwom the fiwmwawe.
 * @msg: The mcu_msg_wesponse that wiww be fiwwed with pawsed vawues.
 * @swc: Pointew to the memowy that wiww be pawsed
 *
 * The message fowmat in the maiwbox depends on the fiwmwawe. Pawse the
 * diffewent fowmats into a unifowm message fowmat that can be used without
 * taking cawe of the fiwmwawe vewsion.
 */
int awwegwo_decode_maiw(void *msg, u32 *swc)
{
	stwuct mcu_msg_headew *headew;

	if (!swc || !msg)
		wetuwn -EINVAW;

	headew = msg;
	headew->type = FIEWD_GET(GENMASK(31, 16), swc[0]);

	swc++;
	switch (headew->type) {
	case MCU_MSG_TYPE_INIT:
		awwegwo_dec_init(msg, swc);
		bweak;
	case MCU_MSG_TYPE_CWEATE_CHANNEW:
		awwegwo_dec_cweate_channew(msg, swc);
		bweak;
	case MCU_MSG_TYPE_DESTWOY_CHANNEW:
		awwegwo_dec_destwoy_channew(msg, swc);
		bweak;
	case MCU_MSG_TYPE_ENCODE_FWAME:
		awwegwo_dec_encode_fwame(msg, swc);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}
